#TEST: require_utility libpciaccess "$PKG_CONFIG_PATH/pciaccess.pc"
# Copyright (c) 2019-2021 Griefer@Work
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
#    Portions Copyright (c) 2019-2021 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

require_utility libzlib "$PKG_CONFIG_PATH/zlib.pc"

PACKAGE_NAME="libpciaccess-0.16"
PACKAGE_GIT_URL="https://gitlab.freedesktop.org/xorg/lib/libpciaccess"
PACKAGE_GIT_COMMIT="fbd1f0fe79ba25b72635f8e36a6c33d7e0ca19f6"

CONFIGURE=""
CONFIGURE="$CONFIGURE --enable-linux-rom-fallback"
CONFIGURE="$CONFIGURE --with-pciids-path=/usr/share/hwdata"
CONFIGURE="$CONFIGURE --with-zlib"

# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"

# libpci contains a utility program `scanpci' that can be used to list
# PCI devices attached to the system. By default, this program gets built,
# but doesn't actually end up being installed automatically.
# Since I kind-of like that applet, install it manually here.
install_file /bin/scanpci   "$OPTPATH/scanpci/scanpci"
