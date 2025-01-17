#TEST: require_utility Xorg/libXfont2 "$PKG_CONFIG_PATH/xfont2.pc"
# Copyright (c) 2019-2025 Griefer@Work
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
#    Portions Copyright (c) 2019-2025 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

require_utility Xorg/libfontenc "$PKG_CONFIG_PATH/fontenc.pc"
require_utility Xorg/xtrans     "$PKG_CONFIG_PATH/xtrans.pc"
require_utility Xorg/xorgproto  "$PKG_CONFIG_PATH/xproto.pc"
#equire_utility Xorg/xorgproto  "$PKG_CONFIG_PATH/fontsproto.pc"
require_utility libfreetype2    "$PKG_CONFIG_PATH/freetype2.pc"
require_utility libbzip2        "$PKG_CONFIG_PATH/bzip2.pc"
require_utility libzlib         "$PKG_CONFIG_PATH/zlib.pc"

PACKAGE_URL="https://www.x.org/releases/individual/lib/libXfont2-2.0.4.tar.gz"

CONFIGURE=(
	"--enable-freetype"
	"--enable-builtins"
	"--enable-pcfformat"
	"--enable-bdfformat"
	"--enable-snfformat"
	"--enable-fc"
	"--enable-unix-transport"
	"--disable-tcp-transport"
	"--disable-ipv6"
	"--enable-local-transport"
	"--with-bzip2"
)

# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"
