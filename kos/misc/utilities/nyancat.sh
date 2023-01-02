#TEST: require_utility nano "$SYSROOT_BIN_TARGET_COMMON/bin/nyancat"
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

SRCPATH="$KOS_ROOT/binutils/src/nyancat-git"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/nyancat"

if ! [ -f "$SRCPATH/src/nyancat.c" ]; then
	# https://stackoverflow.com/questions/3489173/how-to-clone-git-repository-with-specific-revision-changeset
	rm -rf "$SRCPATH" > /dev/null 2>&1
	cmd mkdir -p "$SRCPATH"
	cmd cd "$SRCPATH"
	cmd git init
	cmd git remote add origin "https://github.com/klange/nyancat.git"
	cmd git fetch origin "5ffb6c5c03d0e9156db8f360599d4f0449bb16b9"
	cmd git reset --hard FETCH_HEAD
	rm -rf "$SRCPATH/.git" > /dev/null 2>&1
fi

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/nyancat" ]; then
	rm -rf "$OPTPATH" > /dev/null 2>&1
	cmd mkdir -p "$OPTPATH"
	cmd "${CROSS_PREFIX}gcc" -g -o "$OPTPATH/nyancat" "$SRCPATH/src/nyancat.c"
fi

install_file /bin/nyancat "$OPTPATH/nyancat"
