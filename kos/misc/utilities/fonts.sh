#TEST: require_utility fonts "$SYSROOT_BIN_TARGET_COMMON/lib/fonts/u_vga16"
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

# Build and install KOS graphics mode fonts
cd "$KOS_ROOT"
rundeemon "kos/misc/fonts/tlft/build_u_vga16.dee"
install_file /lib/fonts/u_vga16 "$KOS_MISC/fonts/tlft/u_vga16.tlft"
