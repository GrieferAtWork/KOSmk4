#TEST: require_utility 2048 "$SYSROOT_BIN_TARGET_COMMON/bin/2048"
# Copyright (c) 2019-2025 Griefer@Work
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
#    Portions Copyright (c) 2019-2025 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

VERSION="9b387c3071d962a1c923f66b5caa3f849d519a0c"
SRCPATH="$KOS_ROOT/binutils/src/2048.c"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/2048.c"
EXEFILE="$OPTPATH/2048"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$EXEFILE" ]; then
	if ! [ -f "$SRCPATH/2048.c" ]; then
		cmd mkdir -p "$SRCPATH"
		cmd cd "$SRCPATH/.."
		cmd git clone https://github.com/mevdschee/2048.c.git
		cmd cd "$SRCPATH"
		cmd git checkout "$VERSION" -f
	fi
	cmd mkdir -p "$OPTPATH"
	set_archpath
	cmd cd "$SRCPATH"
	OBJFILE="$OPTPATH/2048.o"
	SRCFILE="$SRCPATH/2048.c"

	# Build
	echo "compile: $CC -c -o $OBJFILE $SRCFILE"
	cmd "$CC" -g -c -o "$OBJFILE" "$SRCFILE"

	# Link
	echo "link: $CC -o $EXEFILE $OBJFILE"
	cmd "$CC" -g -o "$EXEFILE" "$OBJFILE"
fi

# Install 2048 to disk
install_file /bin/2048 "$EXEFILE"
