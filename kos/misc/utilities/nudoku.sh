#TEST: require_utility nudoku "$SYSROOT_BIN_TARGET_COMMON/bin/nudoku"
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

require_utility libncurses "$SYSROOT_BIN_TARGET_COMMON/$TARGET_LIBPATH/libncursesw.so"

if [ -z "$VERSION" ]; then VERSION="2.0.0"; fi

SRCPATH="$KOS_ROOT/binutils/src/nudoku-$VERSION"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/nudoku-$VERSION"
EXEFILE="$OPTPATH/nudoku"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$EXEFILE" ]; then
	if ! [ -f "$SRCPATH/Makefile.am" ]; then
		rm -r "$SRCPATH" > /dev/null 2>&1
		cmd cd "$KOS_ROOT/binutils/src"
		cmd git clone https://github.com/jubalh/nudoku.git
		cmd cd "$KOS_ROOT/binutils/src/nudoku"
		cmd git checkout "9badff5ab97cf6cd90d0038b103f0839651fca19" -f
		cmd cd "$KOS_ROOT/binutils/src"
		cmd mv "nudoku" "nudoku-$VERSION"
	fi
	rm -r "$OPTPATH" > /dev/null 2>&1
	cmd mkdir -p "$OPTPATH"
	for SRCFILE in main.c sudoku.c sudoku.h; do
		cmd cp "$SRCPATH/src/$SRCFILE" "$OPTPATH/$SRCFILE"
	done
	echo "#define gettext(x) x" > "$OPTPATH/gettext.h"
	cmd cd "$OPTPATH"
	set_archpath
	CFLAGS="-DVERSION=\"2.0.0\""
	TS_OBJECTS=""
	for SRCFILE in main sudoku; do
		OBJFILE="$OPTPATH/$SRCFILE.o"
		SRCFILE="$OPTPATH/$SRCFILE.c"
		TS_OBJECTS="$TS_OBJECTS $OBJFILE"
		if [ "$MODE_FORCE_MAKE" == yes ] || [ "$OBJFILE" -ot "$SRCFILE" ]; then
			echo "compile: $CC $CFLAGS -g -c -o $OBJFILE $SRCFILE"
			cmd "$CC" $CFLAGS -g -c -o "$OBJFILE" "$SRCFILE" &
		fi
	done
	cmd wait
	echo "link: $CC -g -o $EXEFILE $TS_OBJECTS -lncursesw"
	cmd "$CC" -g -o "$EXEFILE" "$TS_OBJECTS" -lncursesw
fi

# Install nudoku to disk
install_file /bin/nudoku "$EXEFILE"
