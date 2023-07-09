#TEST: require_utility libmpc "$SYSROOT_BIN_TARGET_COMMON/$TARGET_LIBPATH/libmpc.so.3"
# Copyright (c) 2019-2023 Griefer@Work
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
#    Portions Copyright (c) 2019-2023 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

require_utility libgmp  "$PKG_CONFIG_PATH/gmp.pc"
require_utility libmpfr "$PKG_CONFIG_PATH/mpfr.pc"

PACKAGE_URL="https://ftp.gnu.org/gnu/mpc/mpc-1.2.1.tar.gz"
PACKAGE_NAME="libmpc-1.2.1"

# Additions configure options
CONFIGURE=()

# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"
