#TEST: require_utility libbzip2 "$PKG_CONFIG_PATH/bzip2.pc"
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

VERSION="1.0.8"
SRCPATH="$KOS_ROOT/binutils/src/libbzip2-$VERSION"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/libbzip2-$VERSION"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/libbz2.a" ]; then
	if ! [ -f "$SRCPATH/bzlib.c" ]; then
		cmd cd "$KOS_ROOT/binutils/src"
		if ! [ -f "libbzip2-$VERSION.tar.gz" ]; then
			download_file \
				"bzip2-$VERSION.tar.gz" \
				"https://sourceware.org/pub/bzip2/bzip2-$VERSION.tar.gz"
			cmd mv "bzip2-$VERSION.tar.gz"  "libbzip2-$VERSION.tar.gz"
		fi
		cmd rm -rf "bzip2-$VERSION"
		cmd rm -rf "libbzip2-$VERSION"
		cmd tar xvf "libbzip2-$VERSION.tar.gz"
		cmd mv "bzip2-$VERSION"  "libbzip2-$VERSION"
	fi
	cmd cd "$SRCPATH"
	cmd rm -rf "$OPTPATH"
	cmd mkdir -p "$OPTPATH"
	# There is no configure script, and the standard Makefile has
	# no cross-compile options. This leaves us with 2 options:
	#   - Patch the Makefile
	#   - Compile everything directly
	# We chose the later, since that one's simpler due to the small
	# number of files that are involved.
	CFLAGS="-ggdb -O2 -D_FILE_OFFSET_BITS=64"
	SOURCES="blocksort.c huffman.c crctable.c randtable.c \
	         compress.c decompress.c bzlib.c"
	# Build the shared library
	vcmd "${CROSS_PREFIX}gcc" \
		-Wl,-soname,libbz2.so \
		-o "$OPTPATH/libbz2.so" \
		-fPIC -shared $CFLAGS $SOURCES
	# Build the static library
	for f in $SOURCES; do
		vcmd "${CROSS_PREFIX}gcc" $CFLAGS -c -o "$OPTPATH/${f/.c/.o}" $f &
	done
	cmd wait
	cmd cd "$OPTPATH"
	vcmd "${CROSS_PREFIX}ar" rcs "$OPTPATH/libbz2.a" ${SOURCES//.c/.o}
fi

# Install libraries
install_file /$TARGET_LIBPATH/libbz2.so "$OPTPATH/libbz2.so"
install_file_nodisk /$TARGET_LIBPATH/libbz2.a "$OPTPATH/libbz2.a"

# Install headers
install_rawfile "$KOS_ROOT/kos/include/bzlib.h" "$SRCPATH/bzlib.h"

# Install the PKG_CONFIG file
install_rawfile_stdin "$PKG_CONFIG_PATH/bzip2.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: bzip2
Description: The bzip2 Library
Version: $VERSION
Cflags:
Libs: -lbz2
EOF
