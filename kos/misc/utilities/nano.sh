#TEST: require_utility nano "$TARGET_SYSROOT/bin/nano"
# Copyright (c) 2019-2022 Griefer@Work
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
#    Portions Copyright (c) 2019-2022 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

require_utility libncurses "$TARGET_SYSROOT/$TARGET_LIBPATH/libncursesw.so"
require_utility file       "$PKG_CONFIG_PATH/libmagic.pc"
PACKAGE_URL="https://nano-editor.org/dist/v4/nano-4.4.tar.xz"

# Additions configure options
CONFIGURE=(
	"--enable-largefile"
	"--disable-threads"
	"--enable-nls"
	"--enable-browser"
	"--enable-color"
	"--enable-comment"
	"--enable-extra"
	"--enable-help"
	"--enable-histories"
	"--enable-justify"
	"--enable-libmagic"
	"--enable-linenumbers"
	"--enable-mouse"
	"--enable-multibuffer"
	"--enable-nanorc"
	"--enable-operatingdir"
	"--enable-speller"
	"--enable-tabcomp"
	"--enable-wordcomp"
	"--enable-wrapping"
	"--disable-debug"
	"--disable-tiny"
	"--enable-utf8"
)

# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"
