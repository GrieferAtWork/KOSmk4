#TEST: require_utility libjson-c "$PKG_CONFIG_PATH/json-c.pc"
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

VERSION="0.15-20200726"

# For $CMAKE_TOOLCHAIN_FILE
. "$KOS_MISC/utilities/misc/cmake.sh"

SHLIB_VERSION_MAJOR="5"
SHLIB_VERSION="$SHLIB_VERSION_MAJOR.1.0"

SRCPATH="$KOS_ROOT/binutils/src/libjson-c-$VERSION"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/libjson-c-$VERSION"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/libjson-c.so.$SHLIB_VERSION" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/CMakeLists.txt" ]; then
			cmd mkdir -p "$KOS_ROOT/binutils/src"
			cmd cd "$KOS_ROOT/binutils/src"
			if ! [ -f "libjson-c-$VERSION.tar.gz" ]; then
				download_file \
					"json-c-$VERSION.tar.gz" \
					https://github.com/json-c/json-c/archive/json-c-$VERSION.tar.gz
				cmd mv "json-c-$VERSION.tar.gz" "libjson-c-$VERSION.tar.gz"
			fi
			cmd rm -rf "json-c-json-c-$VERSION"
			cmd tar xvf "libjson-c-$VERSION.tar.gz"
			cmd mv "json-c-json-c-$VERSION" "libjson-c-$VERSION"
		fi
		rm -rf "$OPTPATH" > /dev/null 2>&1
		cmd mkdir -p "$OPTPATH"
		cmd cd "$OPTPATH"
		cmd cmake \
			-DCMAKE_TOOLCHAIN_FILE="$CMAKE_TOOLCHAIN_FILE" \
			-S "$SRCPATH" \
			-B "$OPTPATH"
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# Install libraries
install_file           /$TARGET_LIBPATH/libjson-c.so.$SHLIB_VERSION_MAJOR "$OPTPATH/libjson-c.so.$SHLIB_VERSION"
install_symlink_nodisk /$TARGET_LIBPATH/libjson-c.so.$SHLIB_VERSION       libjson-c.so.$SHLIB_VERSION_MAJOR
install_symlink_nodisk /$TARGET_LIBPATH/libjson-c.so                      libjson-c.so.$SHLIB_VERSION_MAJOR
install_file_nodisk    /$TARGET_LIBPATH/libjson-c.a                       "$OPTPATH/libjson-c.a"

# Install headers
install_rawfile "$KOS_ROOT/kos/include/json-c/json_config.h"          "$OPTPATH/json_config.h"
install_rawfile "$KOS_ROOT/kos/include/json-c/json.h"                 "$SRCPATH/json.h"
install_rawfile "$KOS_ROOT/kos/include/json-c/arraylist.h"            "$SRCPATH/arraylist.h"
install_rawfile "$KOS_ROOT/kos/include/json-c/debug.h"                "$SRCPATH/debug.h"
install_rawfile "$KOS_ROOT/kos/include/json-c/json_c_version.h"       "$SRCPATH/json_c_version.h"
install_rawfile "$KOS_ROOT/kos/include/json-c/json_inttypes.h"        "$SRCPATH/json_inttypes.h"
install_rawfile "$KOS_ROOT/kos/include/json-c/json_object.h"          "$SRCPATH/json_object.h"
install_rawfile "$KOS_ROOT/kos/include/json-c/json_object_iterator.h" "$SRCPATH/json_object_iterator.h"
install_rawfile "$KOS_ROOT/kos/include/json-c/json_pointer.h"         "$SRCPATH/json_pointer.h"
install_rawfile "$KOS_ROOT/kos/include/json-c/json_tokener.h"         "$SRCPATH/json_tokener.h"
install_rawfile "$KOS_ROOT/kos/include/json-c/json_types.h"           "$SRCPATH/json_types.h"
install_rawfile "$KOS_ROOT/kos/include/json-c/json_util.h"            "$SRCPATH/json_util.h"
install_rawfile "$KOS_ROOT/kos/include/json-c/json_visit.h"           "$SRCPATH/json_visit.h"
install_rawfile "$KOS_ROOT/kos/include/json-c/linkhash.h"             "$SRCPATH/linkhash.h"
install_rawfile "$KOS_ROOT/kos/include/json-c/printbuf.h"             "$SRCPATH/printbuf.h"

# Install the PKG_CONFIG file
install_rawfile_stdin "$PKG_CONFIG_PATH/json-c.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: json-c
Description: A JSON implementation in C
Version: $VERSION
Requires:
Libs.private:
Libs: -ljson-c
Cflags: -I$KOS_ROOT/kos/include/json-c
EOF
