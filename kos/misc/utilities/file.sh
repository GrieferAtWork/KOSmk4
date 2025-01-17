#TEST: require_utility file "$PKG_CONFIG_PATH/libmagic.pc"
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

require_utility libzlib  "$PKG_CONFIG_PATH/zlib.pc"
require_utility libbzip2 "$PKG_CONFIG_PATH/bzip2.pc"
require_utility liblzma  "$PKG_CONFIG_PATH/liblzma.pc"

PACKAGE_NAME="file-5.39"
PACKAGE_URL="https://github.com/file/file/archive/FILE5_39.tar.gz"

CONFIGURE=(
	"--enable-elf"
	"--enable-elf-core"
	"--enable-zlib"
	"--enable-bzlib"
	"--enable-xzlib"
	"--disable-libseccomp"
)


# In order to build the "file" utility, you need install same version on
# the host. Otherwise, you'll end up with an error such as the following:
# >> Cannot use the installed version of file (5.32) to
# >> cross-compile file 5.39
# >> Please install file 5.39 locally first
GM_HOOK_BEFORE_MAKE=_ensure_host_has_same_file_version
_ensure_host_has_same_file_version() {
	local host_file_version="$(file --version | sed -e s/file-// -e q)"
	if [[ "$host_file_version" != "$PACKAGE_VERSION" ]]; then
		echo "Need to build 'file'-package for host in order to cross-compile..."
		echo "	Already installed version        '$host_file_version'"
		echo "	Needed version for cross-compile '$PACKAGE_VERSION'"
		local BINUTILS_MISC="$KOS_ROOT/binutils/misc"
		if ! [ -f "$BINUTILS_MISC/bin/file" ] && ! [ -f "$BINUTILS_MISC/bin/file.exe" ]; then
			local HOST_FILE_OPTPATH="$BINUTILS_MISC/opt/$PACKAGE_NAME"
			if ! [ -f "$HOST_FILE_OPTPATH/file" ] && ! [ -f "$HOST_FILE_OPTPATH/file.exe" ]; then
				if ! [ -f "$HOST_FILE_OPTPATH/Makefile" ]; then
					rm -r "$HOST_FILE_OPTPATH" > /dev/null 2>&1
					cmd mkdir -p "$HOST_FILE_OPTPATH"
					# Configure for the host
					cmd cd "$HOST_FILE_OPTPATH"
					cmd ../../../src/$PACKAGE_NAME/configure --prefix="$BINUTILS_MISC"
				fi
				# Make for the host
				cmd cd "$HOST_FILE_OPTPATH"
				cmd make -j $MAKE_PARALLEL_COUNT
			fi
			# Install (in `<KOS>/binutils/misc/bin' for the host)
			cmd cd "$HOST_FILE_OPTPATH"
			cmd make -j $MAKE_PARALLEL_COUNT install
		fi
		# Make sure that the matching version of "file" compiled for our host is in $PATH
		export PATH="$BINUTILS_MISC/bin:$PATH"
	fi
}


# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"
