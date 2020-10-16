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
# depends libICE
# depends libSM

# xorg-macros
. "$KOS_MISC/utilities/misc/xorg-macros.sh"

VERSION="1.1.1"

SO_VERSION_MAJOR="6"
SO_VERSION="$SO_VERSION_MAJOR.2.0"

SRCPATH="$KOS_ROOT/binutils/src/x/libXmu-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/x/libXmu-$VERSION"

require_program xsltproc

# libXmu
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/src/.libs/libXmu.so.$SO_VERSION" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src/x"
			cmd rm -rf "libXmu-$VERSION"
			download_file \
				"libXmu-$VERSION.tar.gz" \
				"https://www.x.org/releases/X11R7.7/src/everything/libXmu-$VERSION.tar.gz"
			cmd tar xvf "libXmu-$VERSION.tar.gz"
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
			cmd bash "../../../../src/x/libXmu-$VERSION/configure" \
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
				--docdir="/usr/share/doc/libXmu" \
				--htmldir="/usr/share/doc/libXmu" \
				--dvidir="/usr/share/doc/libXmu" \
				--pdfdir="/usr/share/doc/libXmu" \
				--psdir="/usr/share/doc/libXmu" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--enable-shared \
				--enable-static \
				--disable-docs \
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

# Install the PKG_CONFIG files
if ! [ -f "$PKG_CONFIG_PATH/xmu.pc" ]; then
	cmd mkdir -p "$PKG_CONFIG_PATH"
	cat > "$PKG_CONFIG_PATH/xmu.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: Xmu
Description: Xmu Library
Version: $VERSION
Requires: xproto x11 xt
Requires.private: x11 xt xext
Cflags:
Libs: -lXmu
EOF
fi

if ! [ -f "$PKG_CONFIG_PATH/xmuu.pc" ]; then
	cmd mkdir -p "$PKG_CONFIG_PATH"
	cat > "$PKG_CONFIG_PATH/xmuu.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: Xmuu
Description: Mini Xmu Library
Version: $VERSION
Requires: xproto x11
Requires.private: x11
Cflags:
Libs: -lXmuu
EOF
fi

# Install libraries
install_file /$TARGET_LIBPATH/libXmu.so.$SO_VERSION_MAJOR "$OPTPATH/src/.libs/libXmu.so.$SO_VERSION"
install_symlink /$TARGET_LIBPATH/libXmu.so.$SO_VERSION libXmu.so.$SO_VERSION_MAJOR
install_symlink /$TARGET_LIBPATH/libXmu.so libXmu.so.$SO_VERSION_MAJOR
install_file_nodisk /$TARGET_LIBPATH/libXmu.a "$OPTPATH/src/.libs/libXmu.a"
install_file /$TARGET_LIBPATH/libXmuu.so.1 "$OPTPATH/src/.libs/libXmuu.so.1.0.0"
install_symlink /$TARGET_LIBPATH/libXmuu.so.1.0.0 libXmuu.so.1
install_symlink /$TARGET_LIBPATH/libXmuu.so libXmuu.so.1
install_file_nodisk /$TARGET_LIBPATH/libXmuu.a "$OPTPATH/src/.libs/libXmuu.a"

# Install headers
install_header() {
	install_rawfile \
		"$KOS_ROOT/kos/include/X11/Xmu/$1" \
		"$SRCPATH/include/X11/Xmu/$1"
}
install_header "Xmu.h"
install_header "Atoms.h"
install_header "CharSet.h"
install_header "CloseHook.h"
install_header "Converters.h"
install_header "CurUtil.h"
install_header "CvtCache.h"
install_header "DisplayQue.h"
install_header "Drawing.h"
install_header "Editres.h"
install_header "EditresP.h"
install_header "Error.h"
install_header "ExtAgent.h"
install_header "Initer.h"
install_header "Lookup.h"
install_header "Misc.h"
install_header "StdSel.h"
install_header "StdCmap.h"
install_header "SysUtil.h"
install_header "WidgetNode.h"
install_header "WinUtil.h"
install_header "Xct.h"
install_header "WhitePoint.h"
