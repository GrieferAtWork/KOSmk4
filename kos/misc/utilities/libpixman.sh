#TEST: require_utility libpixman "$PKG_CONFIG_PATH/pixman-1.pc"
# Copyright (c) 2019-2020 Griefer@Work
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgement (see the following) in the product
#    documentation is required:
#    Portions Copyright (c) 2019-2020 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

require_utility libzlib "$PKG_CONFIG_PATH/zlib.pc"

VERSION="0.40.0"
SO_VERSION_MAJOR="0"
SO_VERSION="$SO_VERSION_MAJOR.40.0"

SRCPATH="$KOS_ROOT/binutils/src/libpixman-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/libpixman-$VERSION"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/pixman/.libs/libpixman-1.so.$SO_VERSION" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src"
			cmd rm -rf "pixman-$VERSION"
			cmd rm -rf "libpixman-$VERSION"
			if ! [ -f "libpixman-$VERSION.tar.gz" ]; then
				download_file \
					"pixman-$VERSION.tar.gz" \
					"https://www.cairographics.org/releases/pixman-$VERSION.tar.gz"
				cmd mv "pixman-$VERSION.tar.gz" "libpixman-$VERSION.tar.gz"
			fi
			cmd tar xvf "libpixman-$VERSION.tar.gz"
			cmd mv "pixman-$VERSION" "libpixman-$VERSION"
		fi
		cmd rm -rf "$OPTPATH"
		cmd mkdir -p "$OPTPATH"
		cmd cd "$OPTPATH"
		(
			export CC="${CROSS_PREFIX}gcc"
			export CPP="${CROSS_PREFIX}cpp"
			export CFLAGS="-ggdb"
			export CXX="${CROSS_PREFIX}g++"
			export CXXCPP="${CROSS_PREFIX}cpp"
			export CXXFLAGS="-ggdb"
			cmd bash ../../../src/libpixman-$VERSION/configure \
				--prefix="/" \
				--exec-prefix="/" \
				--bindir="/bin" \
				--sbindir="/bin" \
				--libexecdir="/libexec" \
				--sysconfdir="/etc" \
				--sharedstatedir="/usr/com" \
				--localstatedir="/var" \
				--libdir="/$TARGET_LIBPATH" \
				--includedir="/usr/include" \
				--oldincludedir="/usr/include" \
				--datarootdir="/usr/share" \
				--datadir="/usr/share" \
				--infodir="/usr/share/info" \
				--localedir="/usr/share/locale" \
				--mandir="/usr/share/man" \
				--docdir="/usr/share/doc/pixman" \
				--htmldir="/usr/share/doc/pixman" \
				--dvidir="/usr/share/doc/pixman" \
				--pdfdir="/usr/share/doc/pixman" \
				--psdir="/usr/share/doc/pixman" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--disable-openmp \
				--enable-libpng \
				--with-gnu-ld
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# Install libraries
install_file /$TARGET_LIBPATH/libpixman-1.so.$SO_VERSION_MAJOR "$OPTPATH/pixman/.libs/libpixman-1.so.$SO_VERSION"
install_symlink /$TARGET_LIBPATH/libpixman-1.so.$SO_VERSION libpixman-1.so.$SO_VERSION_MAJOR
install_symlink /$TARGET_LIBPATH/libpixman-1.so libpixman-1.so.$SO_VERSION_MAJOR
install_file_nodisk /$TARGET_LIBPATH/libpixman-1.a "$OPTPATH/pixman/.libs/libpixman-1.a"

# Install headers
install_rawfile "$KOS_ROOT/kos/include/pixman-1/pixman.h"         "$SRCPATH/pixman/pixman.h"
install_rawfile "$KOS_ROOT/kos/include/pixman-1/pixman-version.h" "$OPTPATH/pixman/pixman-version.h"

install_proxy_c_header() {
	install_rawfile_stdin "$1" <<EOF
#include "$2"
EOF
}

install_proxy_c_header "$KOS_ROOT/kos/include/pixman.h"         "pixman-1/pixman.h"
install_proxy_c_header "$KOS_ROOT/kos/include/pixman-version.h" "pixman-1/pixman-version.h"

# Install the PKG_CONFIG file
install_rawfile_stdin "$PKG_CONFIG_PATH/pixman-1.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: Pixman
Description: The pixman library (version 1)
Version: $VERSION
Cflags:
Libs: -lpixman-1
EOF
