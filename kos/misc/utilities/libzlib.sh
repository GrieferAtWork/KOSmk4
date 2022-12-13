#TEST: require_utility libzlib "$PKG_CONFIG_PATH/zlib.pc"
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

ZLIB_VERSION_MAJOR="1"
ZLIB_VERSION="$ZLIB_VERSION_MAJOR.2.11"
SRCPATH="$KOS_ROOT/binutils/src/zlib-$ZLIB_VERSION"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/zlib-$ZLIB_VERSION"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/libz.so.$ZLIB_VERSION" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src"
			download_file \
				"zlib-$ZLIB_VERSION.tar.gz" \
				https://www.zlib.net/zlib-$ZLIB_VERSION.tar.gz
			cmd tar xvf "zlib-$ZLIB_VERSION.tar.gz"
		fi
		rm -rf "$OPTPATH" > /dev/null 2>&1
		cmd mkdir -p "$OPTPATH"
		cmd cd "$OPTPATH"
		export CC="${CROSS_PREFIX}gcc"
		export CPP="${CROSS_PREFIX}cpp"
		export CXX="${CROSS_PREFIX}g++"
		export CFLAGS="-ggdb"
		export CXXFLAGS="-ggdb"
		export LDSHARED="${CROSS_PREFIX}gcc -shared"
		cmd bash ../../../src/zlib-$ZLIB_VERSION/configure \
			--prefix="/" \
			--eprefix="/" \
			--libdir="/$TARGET_LIBPATH" \
			--sharedlibdir="/$TARGET_LIBPATH" \
			--includedir="/usr/include" \
			--enable-shared
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# Install libraries
install_file           /$TARGET_LIBPATH/libz.so                     "$OPTPATH/libz.so.$ZLIB_VERSION"
install_symlink_nodisk /$TARGET_LIBPATH/libz.so.$ZLIB_VERSION       libz.so
install_symlink_nodisk /$TARGET_LIBPATH/libz.so.$ZLIB_VERSION_MAJOR libz.so
install_file_nodisk    /$TARGET_LIBPATH/libz.a                      "$OPTPATH/libz.a"

# Install headers
install_rawfile "$KOS_ROOT/kos/include/zconf.h" "$OPTPATH/zconf.h"
install_rawfile "$KOS_ROOT/kos/include/zlib.h"  "$SRCPATH/zlib.h"


# Install the PKG_CONFIG file
install_rawfile_stdin "$PKG_CONFIG_PATH/zlib.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
sharedlibdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: zlib
Description: zlib compression library
Version: $ZLIB_VERSION

Requires:
Libs: -lz
Cflags:
EOF
