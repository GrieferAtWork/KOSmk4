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

require_program aclocal
require_program autoreconf
require_program autoconf
require_program libtool

SRCPATH_XORG_MACROS="$KOS_ROOT/binutils/src/x/xorg-macros"

# xorg-macros
if ! [ -f "$SRCPATH_XORG_MACROS/.installed" ]; then
	if ! [ -f "$SRCPATH_XORG_MACROS/Makefile" ]; then
		if ! [ -f "$SRCPATH_XORG_MACROS/configure" ]; then
			if ! [ -f "$SRCPATH_XORG_MACROS/configure.ac" ]; then
				cmd rm -rf "$SRCPATH_XORG_MACROS"
				cmd mkdir -p "$KOS_ROOT/binutils/src/x"
				cmd cd "$KOS_ROOT/binutils/src/x"
				cmd git clone "https://gitlab.freedesktop.org/xorg/util/macros"
				cmd mv "macros" "xorg-macros"
			fi
			cmd cd "$SRCPATH_XORG_MACROS"
			cmd autoreconf -i
			cmd autoconf
		fi
		cmd cd "$SRCPATH_XORG_MACROS"
		cmd bash configure --prefix=/usr
	fi
	cmd cd "$SRCPATH_XORG_MACROS"
	cmd make
	cmd make install
	> "$SRCPATH_XORG_MACROS/.installed"
fi
