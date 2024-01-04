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

require_utility Xorg/xorg-server "$PKG_CONFIG_PATH/xorg-server.pc"
require_utility Xorg/libX11      "$PKG_CONFIG_PATH/x11.pc"
require_utility Xorg/xorgproto   "$PKG_CONFIG_PATH/xproto.pc"

PACKAGE_URL="https://www.x.org/releases/individual/app/xinit-1.4.1.tar.gz"

CONFIGURE=(
	"--with-xrdb=/bin/xrdb"
	"--with-xmodmap=/bin/xmodmap"
	"--with-twm=/bin/twm"
	"--with-xclock=/bin/xclock"
	"--with-xterm=/bin/xterm"
	"--with-xserver=/bin/Xorg"
	"--with-xauth=/bin/xauth"
	"--with-xinit=/bin/xinit"
	"--with-xinitdir=/$TARGET_LIBPATH/X11/xinit"
)

# Skip automatic install (we only install manually)
INSTALL_NONE=yes

# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"

install_file /bin/xinit "$DESTDIR/bin/xinit"
