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

VERSION="7.0.23"
SRCPATH="$KOS_ROOT/binutils/src/x/xproto-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/x/xproto-$VERSION"

# xproto
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/Xfuncproto.h" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src/x"
			cmd rm -rf "xorg-server-$VERSION"
			download_file \
				"xorg-server-$VERSION.tar.gz" \
				"https://www.x.org/releases/X11R7.7/src/lib/xproto-$VERSION.tar.gz"
			cmd tar xvf "xproto-$VERSION.tar.gz"
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
			cmd bash "../../../../src/x/xproto-$VERSION/configure" \
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
				--docdir="/usr/share/doc/xproto" \
				--htmldir="/usr/share/doc/xproto" \
				--dvidir="/usr/share/doc/xproto" \
				--pdfdir="/usr/share/doc/xproto" \
				--psdir="/usr/share/doc/xproto" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--enable-function-prototypes \
				--enable-varargs-prototypes \
				--enable-const-prototypes \
				--enable-nested-prototypes \
				--enable-wide-prototypes
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# Install headers
install_header() {
	install_rawfile "$KOS_ROOT/kos/include/X11/$1" "$SRCPATH/$1"
}
install_rawfile "$KOS_ROOT/kos/include/X11/Xpoll.h" "$OPTPATH/Xpoll.h"
install_rawfile "$KOS_ROOT/kos/include/X11/Xfuncproto.h" "$OPTPATH/Xfuncproto.h"
install_header "ap_keysym.h"
install_header "DECkeysym.h"
install_header "HPkeysym.h"
install_header "keysymdef.h"
install_header "keysym.h"
install_header "Sunkeysym.h"
install_header "Xalloca.h"
install_header "Xarch.h"
install_header "Xatom.h"
install_header "Xdefs.h"
install_header "XF86keysym.h"
install_header "Xfuncs.h"
install_header "X.h"
install_header "Xmd.h"
install_header "Xosdefs.h"
install_header "Xos.h"
install_header "Xos_r.h"
install_header "Xproto.h"
install_header "Xprotostr.h"
install_header "Xthreads.h"
install_header "Xw32defs.h"
install_header "XWDFile.h"
install_header "Xwindows.h"
install_header "Xwinsock.h"

