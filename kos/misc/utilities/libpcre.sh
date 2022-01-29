#TEST: require_utility libpcre "$PKG_CONFIG_PATH/libpcre.pc"
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

require_utility libzlib "$PKG_CONFIG_PATH/zlib.pc"
require_utility libbzip2 "$PKG_CONFIG_PATH/bzip2.pc"

PACKAGE_URL="https://sourceforge.net/projects/pcre/files/pcre/8.37/pcre-8.37.tar.bz2"
PACKAGE_NAME="libpcre-8.37"

# Additions configure options
CONFIGURE=""
CONFIGURE="$CONFIGURE --enable-utf"
CONFIGURE="$CONFIGURE --enable-newline-is-anycrlf"
CONFIGURE="$CONFIGURE --enable-pcregrep-libz"
CONFIGURE="$CONFIGURE --enable-pcregrep-libbz2"

# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"
