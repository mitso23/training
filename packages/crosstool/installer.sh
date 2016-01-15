source ../defs.sh

VERSION=1.22.0

#wget http://crosstool-ng.org/download/crosstool-ng/crosstool-ng-${VERSION}.tar.bz2
#tar xjf crosstool-ng-${VERSION}.tar.bz2
cd crosstool-ng
./configure --prefix=/usr/local
make
make install

