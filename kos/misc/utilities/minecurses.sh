#TEST: require_utility myman "$SYSROOT_BIN_TARGET_COMMON/bin/myman"
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

require_utility libncurses "$SYSROOT_BIN_TARGET_COMMON/$TARGET_LIBPATH/libncursesw.so"


VERSION="dbbff0eb8bd7f5a404f0a8fa11fcafbf1d826a80";
SRCPATH="$KOS_ROOT/binutils/src/minecurses-$VERSION"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/minecurses-$VERSION"
EXEFILE="$OPTPATH/minecurses"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$EXEFILE" ]; then
	if ! [ -f "$SRCPATH/Makefile" ]; then
		cmd cd "$KOS_ROOT/binutils/src"
		rm -r "$SRCPATH" > /dev/null 2>&1
		rm -r "minecurses" > /dev/null 2>&1
		cmd git clone https://github.com/EliteTK/minecurses.git
		cmd mv "minecurses" "minecurses-$VERSION"
		cmd cd "$SRCPATH"
		cmd git checkout "$VERSION" -f
		cmd cd "$KOS_ROOT/binutils/src"
	fi
	rm -r "$OPTPATH" > /dev/null 2>&1
	cmd mkdir -p "$OPTPATH"
	SRCDIRS="src src/draw src/game"
	cmd cd "$SRCPATH"
	set_archpath
	INVOKE_CC="$CC -g"
	TS_OBJECTS=""
	for FILE in "src/"*.c; do
		OBJFILE="${FILE////-}.o"
		TS_OBJECTS="$TS_OBJECTS $OBJFILE"
		echo "Compile: $INVOKE_CC -c -o $OPTPATH/$OBJFILE $SRCPATH/$FILE"
		cmd "$INVOKE_CC" -c -o "$OPTPATH/$OBJFILE" "$SRCPATH/$FILE"
	done
	cmd wait
	cmd cd "$OPTPATH"
	echo "Link: $CC -g -o $EXEFILE $TS_OBJECTS -lncursesw"
	cmd "$CC" -g -o "$EXEFILE" "$TS_OBJECTS" -lncursesw
fi

# Install minecurses to disk
install_file /bin/minecurses "$EXEFILE"
