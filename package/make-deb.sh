#!/bin/bash

PKGNAME=qmmp-plugin-ym
PKGDIST=$(lsb_release -c -s)
PKGVERS=0.5-1ubuntu1~${PKGDIST}
PKGARCH=$(dpkg --print-architecture)

if [ "${PKGDIST}" == "trusty" ] ; then
    LPATH=usr/lib/qmmp/Input
elif [ "${PKGDIST}" == "utopic" ] ; then
    LPATH=usr/lib/qmmp/Input
else
    LPATH=usr/lib/qmmp/qmmp/Input
fi

mkdir -p ${PKGNAME}_${PKGVERS}/${LPATH}/
mkdir -p ${PKGNAME}_${PKGVERS}/DEBIAN

cat >${PKGNAME}_${PKGVERS}/DEBIAN/control <<EOF
Package: ${PKGNAME}
Version: ${PKGVERS}
Section: multimedia
Priority: optional
Installed-Size: $(du ../plugin/libym.so | sed -e "s/[ \t].*//")
Architecture: ${PKGARCH}
Depends: qmmp (>=1.1.6), libqt5core5a (>=5.9.1)
Conflicts: ${PKGNAME}
Maintainer: Georges Thill <thepsr@nixda.lu>
Description: qmmp audio player - input plugin for ym music files
 Input plugin for ym music files.
 Based on YM lib files by Arnaud Carre.
EOF

#cp LICENSE ${PKGNAME}_${PKGVERS}/DEBIAN/license
cp ../plugin/libym.so ${PKGNAME}_${PKGVERS}/${LPATH}/
chmod 644 ${PKGNAME}_${PKGVERS}/${LPATH}/libym.so

# create an install package
dpkg-deb --build ${PKGNAME}_${PKGVERS} .

# clean up
rm -rf ${PKGNAME}_${PKGVERS}


