#TEST: require_utility Xorg/proto.xproto "$PKG_CONFIG_PATH/xproto.pc"
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

VERSION="7.0.31"
NAME="xproto"

CONFIGURE_EXTRA_ARGS="\
	--enable-function-prototypes \
	--enable-varargs-prototypes \
	--enable-const-prototypes \
	--enable-nested-prototypes \
	--enable-wide-prototypes"

. "$KOS_MISC/utilities/Xorg/misc/proto.sh"

apply_patch "$SRCPATH" "$KOS_PATCHES/xproto-$VERSION.patch"

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

# Install the PKG_CONFIG file
install_rawfile_stdin "$PKG_CONFIG_PATH/xproto.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include
includex11dir=$KOS_ROOT/kos/include/X11

Name: Xproto
Description: Xproto headers
Version: $VERSION
Cflags:
EOF
