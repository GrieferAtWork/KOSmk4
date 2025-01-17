#TEST: require_utility libpng "$PKG_CONFIG_PATH/libpng.pc"
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

require_utility libzlib "$PKG_CONFIG_PATH/zlib.pc"

PACKAGE_URL="https://github.com/glennrp/libpng/archive/v1.6.35.tar.gz"
PACKAGE_NAME="libpng-1.6.35"
VERSION="16"

CONFIGURE=(
	"--enable-hardware-optimizations"
)

INSTALL_SKIP="
/bin/libpng-config
/bin/libpng${VERSION}-config
/usr/include/libpng${VERSION}/pnglibconf.h
"

# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"

# Install the non-suffixed .so library name
install_symlink_nodisk /$TARGET_LIBPATH/libpng.so libpng16.so.16

# Install headers in a more portable way
install_rawfile "$KOS_ROOT/kos/include/$TARGET_INCPATH/libpng${VERSION}/pnglibconf.h" "$DESTDIR/usr/include/libpng${VERSION}/pnglibconf.h"
install_rawfile_stdin "$KOS_ROOT/kos/include/libpng${VERSION}/pnglibconf.h" <<EOF
#ifndef PNGLCONF_H
#include <libpng${VERSION}/pnglibconf.h> /* arch-specific header */
#ifndef PNGLCONF_H
#define PNGLCONF_H
#endif /* !PNGLCONF_H */
#endif /* !PNGLCONF_H */
EOF

install_proxy_c_header() {
	install_rawfile_stdin "$1" <<EOF
#include "$2"
EOF
}

cmd mkdir -p "$KOS_ROOT/kos/include/libpng"
install_proxy_c_header "$KOS_ROOT/kos/include/libpng/png.h"        "../libpng${VERSION}/png.h"
install_proxy_c_header "$KOS_ROOT/kos/include/libpng/pngconf.h"    "../libpng${VERSION}/pngconf.h"
install_proxy_c_header "$KOS_ROOT/kos/include/libpng/pnglibconf.h" "../libpng${VERSION}/pnglibconf.h"
install_proxy_c_header "$KOS_ROOT/kos/include/png.h"               "libpng${VERSION}/png.h"
install_proxy_c_header "$KOS_ROOT/kos/include/pngconf.h"           "libpng${VERSION}/pngconf.h"
install_proxy_c_header "$KOS_ROOT/kos/include/pnglibconf.h"        "libpng${VERSION}/pnglibconf.h"


# Install the PKG_CONFIG file
install_rawfile_stdin "$PKG_CONFIG_PATH/libpng.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include/libpng$SO_VERSION_MAJOR

Name: libpng
Description: Loads and saves PNG files
Version: $VERSION
Requires: zlib
Libs: -lpng$SO_VERSION_MAJOR
Cflags:
EOF
