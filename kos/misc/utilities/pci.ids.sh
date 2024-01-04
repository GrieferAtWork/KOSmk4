#TEST: require_utility pci.ids "$SYSROOT_BIN_TARGET_COMMON/usr/share/hwdata/pci.ids.gz"
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

# NOTE: The pci.ids database is used by libpciaccess,
#       and it's /bin/scanpci utility. It is entirely
#       optional and is only used for cosmetics.

URL="http://pci-ids.ucw.cz/v2.2/pci.ids.gz"
SRCPATH="$KOS_ROOT/binutils/src"

cmd cd "$SRCPATH"
download_file "pci.ids.gz" "$URL"
install_file /usr/share/hwdata/pci.ids.gz "$SRCPATH/pci.ids.gz"
