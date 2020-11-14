#TEST: require_utility Xorg/xkeyboard-config "$PKG_CONFIG_PATH/xkeyboard-config.pc"
# Copyright (c) 2019-2020 Griefer@Work
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
#    Portions Copyright (c) 2019-2020 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

require_utility Xorg/xkbcomp "$PKG_CONFIG_PATH/xkbcomp.pc"

# These two you have to install yourself on your host
# On cygwin, they're found in:
#    - intltool-update: intltool-0.51.0-1
#    - iconv:           libiconv-1.14-2
require_program intltool-update
require_program iconv

# We need a secondary version of "/bin/xkbcomp" that is compiled
# for the host machine, as the process of making xkeyboard-config
# files inbokes the xkbcomp compiler.
# This is where we download+configure+make that second variant,
# as well as modify our $PATH such that it can be found below.
# Note that despite this, KOS still needs a secondary xkbcomp
# compiler at runtime, as xorg-server will execv("/bin/xkbcomp")
# in order to compile keyboard maps.
. "$KOS_MISC/utilities/Xorg/misc/host-xkbcomp.sh"

PACKAGE_URL="https://www.x.org/releases/individual/data/xkeyboard-config/xkeyboard-config-2.31.tar.gz"

CONFIGURE=""
CONFIGURE="$CONFIGURE --with-xkb-base=/usr/share/X11/xkb"

# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"
