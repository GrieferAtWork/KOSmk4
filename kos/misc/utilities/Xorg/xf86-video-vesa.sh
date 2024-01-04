#TEST: require_utility Xorg/xf86-video-vesa "$SYSROOT_BIN_TARGET_COMMON/$TARGET_LIBPATH/xorg/modules/drivers/vesa_drv.so"
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


require_utility Xorg/xorgproto   "$PKG_CONFIG_PATH/xproto.pc"
#equire_utility Xorg/xorgproto   "$PKG_CONFIG_PATH/randrproto.pc"
#equire_utility Xorg/xorgproto   "$PKG_CONFIG_PATH/renderproto.pc"
#equire_utility Xorg/xorgproto   "$PKG_CONFIG_PATH/xextproto.pc"
#equire_utility Xorg/xorgproto   "$PKG_CONFIG_PATH/fontsproto.pc"
require_utility Xorg/xorg-server "$PKG_CONFIG_PATH/xorg-server.pc"

VERSION="2.5.0"
NAME="xf86-video-vesa"
DRIVER_NAME="vesa"

. "$KOS_MISC/utilities/Xorg/misc/video-driver.sh"
