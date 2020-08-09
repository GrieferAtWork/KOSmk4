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

# depends: zlib

VERSION="1.6.35"
SO_VERSION_MAJOR="16"
SO_VERSION="$SO_VERSION_MAJOR.35.0"

SRCPATH="$KOS_ROOT/binutils/src/libpng-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/libpng-$VERSION"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/.libs/libpng$SO_VERSION_MAJOR.so.$SO_VERSION" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src"
			download_file \
				"v${VERSION}.tar.gz" \
				"https://github.com/glennrp/libpng/archive/v${VERSION}.tar.gz"
			cmd mv "v${VERSION}.tar.gz" "libpng-${VERSION}.tar.gz"
			cmd tar xvf "libpng-${VERSION}.tar.gz"
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
			cmd bash ../../../src/libpng-$VERSION/configure \
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
				--docdir="/usr/share/doc/libpng" \
				--htmldir="/usr/share/doc/libpng" \
				--dvidir="/usr/share/doc/libpng" \
				--pdfdir="/usr/share/doc/libpng" \
				--psdir="/usr/share/doc/libpng" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--enable-shared \
				--enable-static \
				--enable-hardware-optimizations \
				--with-gnu-ld
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# Install libraries
install_file /$TARGET_LIBPATH/libpng$SO_VERSION_MAJOR.so.$SO_VERSION_MAJOR "$OPTPATH/.libs/libpng$SO_VERSION_MAJOR.so.$SO_VERSION"
install_symlink /$TARGET_LIBPATH/libpng$SO_VERSION_MAJOR.so.$SO_VERSION libpng$SO_VERSION_MAJOR.so.$SO_VERSION_MAJOR
install_symlink /$TARGET_LIBPATH/libpng$SO_VERSION_MAJOR.so libpng$SO_VERSION_MAJOR.so.$SO_VERSION_MAJOR
install_file_nodisk /$TARGET_LIBPATH/libpng$SO_VERSION_MAJOR.a "$OPTPATH/.libs/libpng$SO_VERSION_MAJOR.a"

install_rawfile "$KOS_ROOT/kos/include/libpng/png.h" "$SRCPATH/png.h"
install_rawfile "$KOS_ROOT/kos/include/libpng/pngconf.h" "$SRCPATH/pngconf.h"
install_rawfile "$KOS_ROOT/kos/include/libpng/pnglibconf.h" "$OPTPATH/pnglibconf.h"

install_proxy_c_header() {
	if ! [ -f "$1" ]; then
		echo "Installing file $1"
		echo "#include \"$2\"" > "$1"
	else
		echo "Installing file $1 (up to date)"
	fi
}
cmd mkdir -p "$KOS_ROOT/kos/include/libpng$SO_VERSION_MAJOR"
cmd mkdir -p "$KOS_ROOT/kos/include/libpng"
install_proxy_c_header "$KOS_ROOT/kos/include/libpng$SO_VERSION_MAJOR/png.h" "../libpng/png.h"
install_proxy_c_header "$KOS_ROOT/kos/include/libpng$SO_VERSION_MAJOR/pngconf.h" "../libpng/pngconf.h"
install_proxy_c_header "$KOS_ROOT/kos/include/libpng$SO_VERSION_MAJOR/pnglibconf.h" "../libpng/pnglibconf.h"
install_proxy_c_header "$KOS_ROOT/kos/include/png.h" "libpng/png.h"
install_proxy_c_header "$KOS_ROOT/kos/include/pngconf.h" "libpng/pngconf.h"
install_proxy_c_header "$KOS_ROOT/kos/include/pnglibconf.h" "libpng/pnglibconf.h"


