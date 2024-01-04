#TEST: require_utility libdrm "$PKG_CONFIG_PATH/libdrm.pc"
# Copyright (c) 2019-2024 Griefer@Work
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
#    Portions Copyright (c) 2019-2024 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

#require_utility libpciaccess "$PKG_CONFIG_PATH/pciaccess.pc"
# XXX: Versions startings at 2.4.101 don't use ./configure for building,
#      but some weird build system no-one else uses, and that no-one's
#      ever heard of. (So upgrading any further might be a problem...)
PACKAGE_URL="https://dri.freedesktop.org/libdrm/libdrm-2.4.100.tar.gz"

#Hacks:
# - "-fcommon":                error "multiple definition of `nouveau_debug';"
# - "-D_GLIBC_BLOAT_SOURCE=1": relies <pthread.h> including <time.h> (as it does in Glibc)
PACKAGE_CCFLAGS="-fcommon -D_GLIBC_BLOAT_SOURCE=1"

# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"

# Install some additional convenience headers
for f in "$KOS_ROOT"/kos/include/libdrm/*.h; do
	name="$(basename "$f")"
	install_rawfile_stdin "$KOS_ROOT/kos/include/drm/$name" <<EOF
#include "../libdrm/$name"
EOF
done

install_rawfile_stdin "$KOS_ROOT/kos/include/drm.h" <<EOF
#include "drm/drm.h"
EOF
