# Maintainer: BigfootACA<bigfoot@classfun.cn>

pkgname=msmfb-refresher
pkgver=1.0
pkgrel=1
pkgdesc="MSM Framebuffer Refresher for android kernel"
arch=(x86_64 i686 aarch64 armv6 armv7)
url="https://github.com/BigfootACA/msmfb-refresher"
license=(LGPL3)
depends=(glibc)
source=(
	msmfb-refresher.c
	msmfb-refresher.service
	LICENSE
	Makefile
)
md5sums=('87c2c90955deb1865433a650edff7604'
         '50ee6a9827b3483dd47e3ba88691292d'
         '3000208d539ec061b899bce1d9ce9404'
         'e863efe327d1b6b4d56dc14b172c0158')
sha1sums=('e5ded569b39f4b5ab6fbc86e7fdeed0655b2a8fc'
          'a86adb477130fc4ed3f869ee4b963738a32f7c35'
          'a8a12e6867d7ee39c21d9b11a984066099b6fb6b'
          '49b4293a0716be9fcf1b1cbcb7fa7a1c2792c48a')
sha256sums=('344cd52a591560f715fd136c5f251368a4f07251304a4a1d50eeae4efad516a4'
            '0ef75219c982a1677c4dc28ff66d366ea29f6ba30d15ac982faf9d59d6042995'
            'e3a994d82e644b03a792a930f574002658412f62407f5fee083f2555c5f23118'
            '005fd079750df2fcf62a45b13d49db5bca03815890f6f335ae3e2e7ccce67a6c')
sha512sums=('dfa447fc7ab98209f24dcbf4f763899eb102281738f382e18b188db280d605ef597599855645d8184500473e3699d65de4c9c821e2155b3a47ea46c6af246290'
            '049dcac93ddca9230243ef2838da55007ce0ffd9d20e58e24b62d5651309192768fb5820d26bf323fe3abaf3a888dd8aece3aafb3742033f47c8801d640fa53c'
            '6a21e9f6706dacb99162dd4c70ec704e3fdf283b93ca2cc1521e08e55e0727db4c7384d027d54739f100cd26c8d3d5be717715c6b21086a9bb22efb893c34fcf'
            '049613689827810bffddf1aa26bf38cdb74948779764f26b50f469bb2777cf3d0dfe56c12b16b55aafc86d3e4f6232c7538a9fd0e2016d57792d758a9476fdd6')

build(){
	make
}

package(){
	make DESTDIR="$pkgdir" install
	install -Dm644 LICENSE -t "$pkgdir/usr/share/license/$pkgname"
	install -Dm644 msmfb-refresher.service -t "$pkgdir/usr/lib/systemd/system"
}
