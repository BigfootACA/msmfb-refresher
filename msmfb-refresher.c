/**
 * Author by: BigfootACA<bigfoot@classfun.cn>
 * MSM Framebuffer Refresher for android kernel
 */
#include<stdio.h>
#include<fcntl.h>
#include<stdbool.h>
#include<unistd.h>
#include<getopt.h>
#include<signal.h>
#include<stdlib.h>
#include<linux/fb.h>
#include<sys/ioctl.h>
#define _PATH_ROOT "/"
#define _PATH_DEV _PATH_ROOT"dev"
#define _PATH_DEV_NULL _PATH_DEV"/null"
static long ts=0,lts=0,ls=0;
static int return_perror(int e,const char*msg){
	perror(msg);
	return e;
}
static int fbdev_refresher_usage(int e){
	fprintf(stderr,
		"Usage: framebuffer-refresher [options]...\n"
		"\tSend FBIOPAN_DISPLAY to fbdev.\n\n"
		"Options:\n"
		"\t--device=FBDEV,-d FBDEV  Framebuffer device.              (default: "_PATH_DEV"/fb0)\n"
		"\t--interval=USEC,-i USEC  Interval microseconds.           (default: 16666(16.6ms,60FPS))\n"
		"\t--no-exit,-k             Keep running when error happend. (default: no)\n"
		"\t--daemon,-D              Run in daemon mode.              (default: no)\n"
		"\t--foreground,-F          Run in foreground.               (default: yes)\n"
		"\t--timer,-t               Show times per second            (default: no)\n\n"
		"\t--help                   Show this help.\n"
	);
	return e;
}
static void alrm_handler(int s){
	fputc('\r',stdout);
	for(int i=0;i<ls;i++)fputc(' ',stdout);
	fputs("\r\033[K",stdout);
	ls=fprintf(stdout,"\r%ld time per second.\r",ts-lts);
	lts=ts;
	fflush(stdout);
	alarm(1);
	if(s!=SIGALRM)signal(SIGALRM,alrm_handler);
}
int main(int argc,char**argv){
	struct option opts[]={
		{"device",    required_argument,NULL,'d'},
		{"interval",  required_argument,NULL,'i'},
		{"no-exit",   no_argument,      NULL,'k'},
		{"foreground",no_argument,      NULL,'F'},
		{"daemon",    no_argument,      NULL,'D'},
		{"timer",     no_argument,      NULL,'t'},
		{"help",      no_argument,      NULL,'h'},
		{NULL,0,NULL,0}
	};
	char*device=_PATH_DEV"/fb0";
	long interval=16666;
	bool foreground=true,no_exit=false,timer=false;
	struct fb_var_screeninfo vinfo;
	int fd=-1,o;
	while((o=getopt_long(argc,argv,"d:i:kFDth",opts,NULL))!=-1)switch(o){
		case 'd':device=optarg;break;
		case 'i':interval=atol(optarg);break;
		case 'k':no_exit=true;break;
		case 'F':foreground=true;break;
		case 'D':foreground=false;break;
		case 't':timer=true;break;
		case 'h':return fbdev_refresher_usage(0);
		default:return fbdev_refresher_usage(1);
	}
	if(!device||interval<1000)return fbdev_refresher_usage(1);
	if((fd=open(device,O_RDWR))<0){
		fprintf(stderr,"open %s: %m\n",device);
		return 1;
	}
	if(ioctl(fd,FBIOGET_VSCREENINFO,&vinfo)<0)return return_perror(1,"ioctl FBIOGET_VSCREENINFO");
	printf("Screen size: %dx%d\n",vinfo.xres_virtual,vinfo.yres_virtual);
	printf("Framebuffer size: %s\n",device);
	printf("Interval: %ldus(%ldms)\n",interval,interval/1000);
	if(!foreground){
		int f=-1;
		if((f=open(_PATH_DEV_NULL,O_RDWR))<0)return return_perror(1,"open "_PATH_DEV_NULL);
		switch(fork()){
			case -1:return return_perror(1,"fork");
			case 0:break;
			default:return 0;
		}
		setsid();
		chdir(_PATH_ROOT);
		fflush(NULL);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		dup2(STDIN_FILENO,f);
		dup2(STDOUT_FILENO,f);
		dup2(STDERR_FILENO,f);
		switch(fork()){
			case -1:_exit(-1);return -1;
			case 0:break;
			default:return 0;
		}
	}
	if(timer)alrm_handler(0);
	int r=-1;
	while(true){
		r=ioctl(fd,FBIOPAN_DISPLAY,&vinfo);
		if(r<0&&!no_exit)break;
		ts++;
		usleep(interval);
	}
	close(fd);
	if(!foreground)_exit(0);
	alarm(0);
	return 0;
}