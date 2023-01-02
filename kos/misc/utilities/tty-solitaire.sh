#TEST: require_utility tty-solitaire "$SYSROOT_BIN_TARGET_COMMON/bin/ttysolitaire"
# Copyright (c) 2019-2023 Griefer@Work
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
#    Portions Copyright (c) 2019-2023 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

require_utility libncurses "$SYSROOT_BIN_TARGET_COMMON/$TARGET_LIBPATH/libncursesw.so"

VERSION="0268d6df09990cbb85682b1ad947b8d602acb097"
SRCPATH="$KOS_ROOT/binutils/src/tty-solitaire"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/tty-solitaire"
EXEFILE="$OPTPATH/ttysolitaire"
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$EXEFILE" ]; then
	if ! [ -f "$SRCPATH/Makefile" ]; then
		cmd mkdir -p "$SRCPATH"
		cmd cd "$SRCPATH/.."
		cmd git clone https://github.com/mpereira/tty-solitaire.git
		cmd cd "$SRCPATH"
		cmd git checkout "$VERSION" -f
	fi
	cmd mkdir -p "$OPTPATH"
	apply_patch "$SRCPATH" "$KOS_PATCHES/tty-solitaire-$VERSION.patch"
	# The program's Makefile isn't designed for cross-compiling
	# But since the program is fairly simple, just compile all *.c
	# files from its /src directory, and link them together into a
	# single program
	set_archpath
	TS_OBJECTS=""
	cmd cd "$SRCPATH/src"
	CFLAGS="-g -fcommon" # Need -fcommon to prevent link errors
	for SRCFILE in *.c; do
		OBJFILE="$OPTPATH/$SRCFILE.o"
		SRCFILE="$SRCPATH/src/$SRCFILE"
		TS_OBJECTS="$TS_OBJECTS $OBJFILE"
		if [ "$MODE_FORCE_MAKE" == yes ] || [ "$OBJFILE" -ot "$SRCFILE" ]; then
			echo "compile: $CC -g -c -o $OBJFILE $SRCFILE"
			cmd "$CC" $CFLAGS -c -o "$OBJFILE" "$SRCFILE" &
		fi
	done
	cmd wait
	# Build and link against ncurses
	echo "link: $CC $CFLAGS -o $EXEFILE $TS_OBJECTS -lncursesw"
	cmd "$CC" $CFLAGS -o "$EXEFILE" "$TS_OBJECTS" -lncursesw
fi

# Install ttysolitaire to disk
install_file /bin/ttysolitaire "$EXEFILE"
