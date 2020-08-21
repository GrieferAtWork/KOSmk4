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
# depends libuuid

# xorg-macros
. "$KOS_MISC/utilities/misc/xorg-macros.sh"

VERSION="1.2.1"

SO_VERSION_MAJOR="6"
SO_VERSION="$SO_VERSION_MAJOR.0.1"

SRCPATH="$KOS_ROOT/binutils/src/x/libSM-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/x/libSM-$VERSION"

require_program xsltproc

# libSM
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/src/.libs/libSM.so.$SO_VERSION" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src/x"
			cmd rm -rf "libSM-$VERSION"
			download_file \
				"libSM-$VERSION.tar.gz" \
				"https://www.x.org/releases/X11R7.7/src/everything/libSM-$VERSION.tar.gz"
			cmd tar xvf "libSM-$VERSION.tar.gz"
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
			cmd bash "../../../../src/x/libSM-$VERSION/configure" \
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
				--docdir="/usr/share/doc/libSM" \
				--htmldir="/usr/share/doc/libSM" \
				--dvidir="/usr/share/doc/libSM" \
				--pdfdir="/usr/share/doc/libSM" \
				--psdir="/usr/share/doc/libSM" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--enable-shared \
				--enable-static \
				--disable-docs \
				--enable-unix-transport \
				--disable-tcp-transport \
				--disable-ipv6 \
				--enable-local-transport \
				--with-gnu-ld \
				--without-xmlto \
				--without-fop \
				--with-libuuid
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# Install the PKG_CONFIG file
if ! [ -f "$PKG_CONFIG_PATH/sm.pc" ]; then
	cmd mkdir -p "$PKG_CONFIG_PATH"
	cat > "$PKG_CONFIG_PATH/sm.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: SM
Description: X Session Management Library
Version: $VERSION
Requires:
Requires.private: ice xproto
Cflags:
Libs: -lSM
EOF
fi

# Install libraries
install_file /$TARGET_LIBPATH/libSM.so.$SO_VERSION_MAJOR "$OPTPATH/src/.libs/libSM.so.$SO_VERSION"
install_symlink /$TARGET_LIBPATH/libSM.so.$SO_VERSION libSM.so.$SO_VERSION_MAJOR
install_symlink /$TARGET_LIBPATH/libSM.so libSM.so.$SO_VERSION_MAJOR
install_file_nodisk /$TARGET_LIBPATH/libSM.a "$OPTPATH/src/.libs/libSM.a"

# Install headers
install_header() {
	install_rawfile \
		"$KOS_ROOT/kos/include/X11/SM/$1" \
		"$SRCPATH/include/X11/SM/$1"
}
install_header "SM.h"
install_header "SMlib.h"
install_header "SMproto.h"
