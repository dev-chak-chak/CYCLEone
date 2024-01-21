#!/usr/bin/env bash

set -e

SYSROOT_DIR="/usr/local"
mkdir -p ${SYSROOT_DIR}/{bin,include,lib,share}

VERSION="3.27.3"
TARGET_ARCH="x86_64"
CMAKE_SH="cmake-${VERSION}-Linux-x86_64.sh"
DOWNLOAD_LINK="https://github.com/Kitware/CMake/releases/download/v${VERSION}/${CMAKE_SH}"

wget -c "${DOWNLOAD_LINK}"

chmod a+x ${CMAKE_SH}
./${CMAKE_SH} --skip-license --prefix="${SYSROOT_DIR}"

# ln -s ${SYSROOT_DIR}/bin/cmake /usr/local/bin/cmake
# ln -s ${SYSROOT_DIR}/bin/ctest /usr/local/bin/ctest

rm -rf ${CMAKE_SH}
