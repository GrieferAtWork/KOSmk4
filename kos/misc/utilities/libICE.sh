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

# depends libx11
# depends xproto

# xorg-macros
. "$KOS_MISC/utilities/misc/xorg-macros.sh"

VERSION="1.0.8"

SO_VERSION_MAJOR="6"
SO_VERSION="$SO_VERSION_MAJOR.3.0"

SRCPATH="$KOS_ROOT/binutils/src/x/libICE-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/x/libICE-$VERSION"

require_program xsltproc

# libICE
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/src/.libs/libICE.so.$SO_VERSION" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src/x"
			cmd rm -rf "libICE-$VERSION"
			download_file \
				"libICE-$VERSION.tar.gz" \
				"https://www.x.org/releases/X11R7.7/src/everything/libICE-$VERSION.tar.gz"
			cmd tar xvf "libICE-$VERSION.tar.gz"
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
			cmd bash "../../../../src/x/libICE-$VERSION/configure" \
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
				--docdir="/usr/share/doc/libICE" \
				--htmldir="/usr/share/doc/libICE" \
				--dvidir="/usr/share/doc/libICE" \
				--pdfdir="/usr/share/doc/libICE" \
				--psdir="/usr/share/doc/libICE" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--enable-shared \
				--enable-static \
				--disable-docs \
				--disable-specs \
				--enable-unix-transport \
				--disable-tcp-transport \
				--disable-ipv6 \
				--enable-local-transport \
				--disable-lint-library \
				--with-gnu-ld \
				--without-xmlto \
				--without-fop \
				--without-lint
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# Install the PKG_CONFIG file
if ! [ -f "$PKG_CONFIG_PATH/ice.pc" ]; then
	cmd mkdir -p "$PKG_CONFIG_PATH"
	cat > "$PKG_CONFIG_PATH/ice.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: ICE
Description: X Inter Client Exchange Library
Version: $VERSION
Requires: xproto
Cflags:
Libs: -lICE
EOF
fi

# Install libraries
install_file /$TARGET_LIBPATH/libICE.so.$SO_VERSION_MAJOR "$OPTPATH/src/.libs/libICE.so.$SO_VERSION"
install_symlink /$TARGET_LIBPATH/libICE.so.$SO_VERSION libICE.so.$SO_VERSION_MAJOR
install_symlink /$TARGET_LIBPATH/libICE.so libICE.so.$SO_VERSION_MAJOR
install_file_nodisk /$TARGET_LIBPATH/libICE.a "$OPTPATH/src/.libs/libICE.a"

# Install headers
install_header() {
	install_rawfile \
		"$KOS_ROOT/kos/include/X11/ICE/$1" \
		"$SRCPATH/include/X11/ICE/$1"
}

install_header "ICE.h"
install_header "ICEconn.h"
install_header "ICElib.h"
install_header "ICEmsg.h"
install_header "ICEproto.h"
install_header "ICEutil.h"
