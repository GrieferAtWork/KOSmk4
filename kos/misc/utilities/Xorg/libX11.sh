#TEST: require_utility Xorg/libX11 "$PKG_CONFIG_PATH/x11.pc"
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

require_utility Xorg/xorgproto "$PKG_CONFIG_PATH/xproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/xextproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/xtrans.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/kbproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/inputproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/xf86bigfontproto.pc"
require_utility Xorg/libxcb    "$PKG_CONFIG_PATH/xcb.pc"

PACKAGE_URL="https://www.x.org/releases/individual/lib/libX11-1.6.12.tar.gz"

CONFIGURE=""
CONFIGURE="$CONFIGURE --enable-unix-transport"
CONFIGURE="$CONFIGURE --disable-tcp-transport"
CONFIGURE="$CONFIGURE --disable-ipv6"
CONFIGURE="$CONFIGURE --enable-local-transport"
CONFIGURE="$CONFIGURE --disable-loadable-i18n"
CONFIGURE="$CONFIGURE --enable-loadable-xcursor"
CONFIGURE="$CONFIGURE --enable-xthreads"
CONFIGURE="$CONFIGURE --enable-xlocaledir"
CONFIGURE="$CONFIGURE --enable-xf86bigfont"
CONFIGURE="$CONFIGURE --enable-xkb"
CONFIGURE="$CONFIGURE --with-locale-lib-dir=/$TARGET_LIBPATH/X11/locale"

# configure thinks that mmap isn't working without this :(
PACKAGE_CONFIG_SITE='
ac_cv_func_mmap_fixed_mapped=yes
'

# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"
