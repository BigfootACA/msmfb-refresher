DESTDIR?=
PREFIX?=/usr
BINDIR?=$(PREFIX)/bin
all: msmfb-refresher
msmfb-refresher.o: msmfb-refresher.c
msmfb-refresher: msmfb-refresher.o
install: msmfb-refresher
	install -vDm755 msmfb-refresher -t $(DESTDIR)$(BINDIR)
clean:
	rm -f *.o *.a *.out *.lib *.obj *.dll *.so *.exe msmfb-refresher
.PHONY: all clean
