#TEST: require_utility vitetris "$SYSROOT_BIN_TARGET_COMMON/bin/vitetris"
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

if [ -z "$VERSION" ]; then VERSION="0.58.0"; fi

SRCPATH="$KOS_ROOT/binutils/src/vitetris-$VERSION"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/vitetris-$VERSION"
EXEPATH="$OPTPATH/tetris"
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$EXEPATH" ]; then
	set_archpath
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/configure" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src"
			if ! [ -f "vitetris-$VERSION.tar.gz" ]; then
				download_file \
					"v$VERSION.tar.gz" \
					https://github.com/vicgeralds/vitetris/archive/v$VERSION.tar.gz
				mv "v$VERSION.tar.gz" "vitetris-$VERSION.tar.gz"
			fi
			cmd tar xvf "vitetris-$VERSION.tar.gz"
		fi
		cmd cp -R "$SRCPATH" "$SYSROOT_BINUTILS_TARGET/opt/"
	fi
	cmd cd "$OPTPATH"
	cmd bash configure \
		--enable-2player \
		--disable-joystick \
		--disable-network \
		--disable-curses \
		--disable-xlib \
		--disable-allegro \
		--enable-term_resizing \
		--enable-menu \
		--enable-blockstyles \
		--disable-pctimer \
		CC="$CC" \
		CFLAGS="-ggdb"
	cmd make -j $MAKE_PARALLEL_COUNT
fi
install_file /bin/vitetris "$EXEPATH"
