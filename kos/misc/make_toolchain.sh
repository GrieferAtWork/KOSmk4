#!/bin/bash
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

# NOTE: Create patches using:
# $ diff -Naur gcc-9.1.0-orig gcc-9.1.0 > patches/gcc-9.1.0.patch
# NOTE: Apply patches using:
# $ patch -d src/gcc-9.1.0 -p1 < patches/gcc-9.1.0.patch

##################
# diff -Naur binutils-2.32-orig binutils-2.32 > ..\..\kos\misc\patches\binutils-2.32.patch
##################

# TODO: Option to install bochs?
# TODO: Option to install qemu?

# Don't use the latest patch, but this very specific one that
# should be usable to drive the entirety of the KOS toolchain.
#     v -- "Fix crash when disassembling an access to an external property"
DEEMON_VERSION="7ab7e8b3a1ce78b100944e1d48a3b960dcb22a17"

MAKE_PARALLEL_COUNT="$(grep -c ^processor /proc/cpuinfo)"

###############################################################
####### Version numbers for dependencies
#config: gcc-12.1.0                    (>= 20220515)
BINUTILS_VERSION_NUMBER="2.38"
GCC_VERSION_NUMBER="12.1.0"
LIBGCC_VERSION="1"
LIBGCC_VERSION_FULL="1"
LIBSTDCXX_VERSION="6"
LIBSTDCXX_VERSION_FULL="6.0.30"

##config: gcc-9.1.0                    (< 20220515)
#	BINUTILS_VERSION_NUMBER="2.32"
#	GCC_VERSION_NUMBER="9.1.0"
#	LIBGCC_VERSION="1"
#	LIBGCC_VERSION_FULL="1"
#	LIBSTDCXX_VERSION="6"
#	LIBSTDCXX_VERSION_FULL="6.0.26"
###############################################################

###############################################################
####### Version number for mtools
MTOOLS_VERSION_NUMBER="4.0.23"

# The KOS configuration used for generating libc/libm/crt0 for libgcc_s and libstdc++
KOS_CONFIG_FOR_LINKING="nOD"
CXX_COMPAT_HEADER_NAMES=(
	"assert" "ctype" "errno" "fenv" "float"
	"inttypes" "iso646" "limits" "locale"
	"math" "setjmp" "signal" "stdalign"
	"stdarg" "stdbool" "stddef" "stdint"
	"stdio" "stdlib" "string" "time" "uchar"
	"wchar" "wctype" "tgmath" "complex"
)
CXX_COMPAT_HEADER_FILES=(
	"bits/std_abs.h"
)
CXX_KOS_SPECIFIC_HEADER_FILES=(
	"atomic"
	"stdatomic.h"
)


BINUTILS_VERSION="binutils-${BINUTILS_VERSION_NUMBER}"
BINUTILS_VERSION_URL="https://ftp.gnu.org/gnu/binutils/binutils-${BINUTILS_VERSION_NUMBER}.tar.gz"
GCC_VERSION="gcc-${GCC_VERSION_NUMBER}"
GCC_VERSION_URL="https://ftp.gnu.org/gnu/gcc/gcc-${GCC_VERSION_NUMBER}/gcc-${GCC_VERSION_NUMBER}.tar.gz"
MTOOLS_VERSION="mtools-${MTOOLS_VERSION_NUMBER}"
MTOOLS_VERSION_URL="ftp://ftp.gnu.org/gnu/mtools/mtools-${MTOOLS_VERSION_NUMBER}.tar.gz"

KOS_MISC="$(dirname "$(readlink -f "$0")")"

if (($# < 1)); then
	echo "Usage: ./make_toolchain.sh <TARGET>"
	echo "	TARGET must be one of:"
	echo "		i386-kos"
	echo "		x86_64-kos"
	echo "		arm-kos"
	exit 1
fi

CONFIGURE_OPTIONS_BINUTILS=()
CONFIGURE_OPTIONS_GCC=()


############################################################################################
##  BINUTILS
############################################################################################
download_binutils() {
	echo "Checking for $BINUTILS_VERSION"
	if ! [ -f "src/$BINUTILS_VERSION/configure" ]; then
		cmd cd "src"
		if ! [ -f "$BINUTILS_VERSION.tar" ]; then
			if ! [ -f "$BINUTILS_VERSION.tar.gz" ]; then
				echo "	Downloading: $BINUTILS_VERSION_URL"
				cmd wget "$BINUTILS_VERSION_URL"
			fi
			echo "	Decompressing: $BINUTILS_VERSION.tar.gz"
			cmd gunzip "$BINUTILS_VERSION.tar.gz"
		fi
		echo "	Unpacking: $BINUTILS_VERSION.tar"
		cmd tar -xf "$BINUTILS_VERSION.tar"
		cmd cd ".."
		if ! [ -f "src/$BINUTILS_VERSION/configure" ]; then
			echo "ERROR: Missing file: src/$BINUTILS_VERSION/configure"
			exit 1
		fi
	else
		echo "	Already present"
	fi
}

patch_binutils() {
	echo "Checking if $BINUTILS_VERSION has been patched"
	if ! [ -f "$KOS_PATCHES/$BINUTILS_VERSION.patch" ]; then
		echo "	No patch file found: $KOS_PATCHES/$BINUTILS_VERSION.patch"
	elif ! [ -f "src/$BINUTILS_VERSION/.kos_patched" ]; then
		echo "	Applying patch: $KOS_PATCHES/$BINUTILS_VERSION.patch to src/$BINUTILS_VERSION"
		cmd patch -d "src/$BINUTILS_VERSION" -p1 < "$KOS_PATCHES/$BINUTILS_VERSION.patch"
		> "src/$BINUTILS_VERSION/.kos_patched"
	else
		echo "	Already patched"
	fi
}



############################################################################################
##  GCC
############################################################################################
download_gcc() {
	echo "Checking for $GCC_VERSION..."
	if ! [ -f "src/$GCC_VERSION/configure" ]; then
		cmd cd "src"
		if ! [ -f "$GCC_VERSION.tar" ]; then
			if ! [ -f "$GCC_VERSION.tar.gz" ]; then
				echo "	Downloading: $GCC_VERSION_URL"
				cmd wget "$GCC_VERSION_URL"
			fi
			echo "	Decompressing: $GCC_VERSION.tar.gz"
			cmd gunzip "$GCC_VERSION.tar.gz"
		fi
		echo "	Unpacking: $GCC_VERSION.tar"
		cmd tar -xf "$GCC_VERSION.tar"
		cmd cd ".."
		if ! [ -f "src/$GCC_VERSION/configure" ]; then
			echo "ERROR: Missing file: src/$GCC_VERSION/configure"
			exit 1
		fi
	else
		echo "	Already present"
	fi
}

patch_gcc() {
	echo "Checking if $GCC_VERSION has been patched"
	if ! [ -f "$KOS_PATCHES/$GCC_VERSION.patch" ]; then
		echo "	No patch file found: $KOS_PATCHES/$GCC_VERSION.patch"
	elif ! [ -f "src/$GCC_VERSION/.kos_patched" ]; then
		echo "	Applying patch: $KOS_PATCHES/$GCC_VERSION.patch to src/$GCC_VERSION"
		cmd patch -d "src/$GCC_VERSION" -p1 < "$KOS_PATCHES/$GCC_VERSION.patch"
		> "src/$GCC_VERSION/.kos_patched"
	else
		echo "	Already patched"
	fi
}

patch_mtools() {
	echo "Checking if $MTOOLS_VERSION has been patched"
	if ! [ -f "$KOS_PATCHES/$MTOOLS_VERSION.patch" ]; then
		echo "	No patch file found: $KOS_PATCHES/$MTOOLS_VERSION.patch"
	elif ! [ -f "src/$MTOOLS_VERSION/.kos_patched" ]; then
		echo "	Applying patch: $KOS_PATCHES/$MTOOLS_VERSION.patch to src/$MTOOLS_VERSION"
		cmd patch -d "src/$MTOOLS_VERSION" -p1 < "$KOS_PATCHES/$MTOOLS_VERSION.patch"
		> "src/$MTOOLS_VERSION/.kos_patched"
	else
		echo "	Already patched"
	fi
}



############################################################################################
##  MTOOLS
############################################################################################
download_mtool() {
	echo "Checking for $MTOOLS_VERSION..."
	if ! [ -f "src/$MTOOLS_VERSION/configure" ]; then
		cmd cd "src"
		if ! [ -f "$MTOOLS_VERSION.tar" ]; then
			if ! [ -f "$MTOOLS_VERSION.tar.gz" ]; then
				echo "	Downloading: $MTOOLS_VERSION_URL"
				cmd wget "$MTOOLS_VERSION_URL"
			fi
			echo "	Decompressing: $MTOOLS_VERSION.tar.gz"
			cmd gunzip "$MTOOLS_VERSION.tar.gz"
		fi
		echo "	Unpacking: $MTOOLS_VERSION.tar"
		cmd tar -xf "$MTOOLS_VERSION.tar"
		cmd cd ".."
		if ! [ -f "src/$MTOOLS_VERSION/configure" ]; then
			echo "ERROR: Missing file: src/$MTOOLS_VERSION/configure"
			exit 1
		fi
	else
		echo "	Already present"
	fi
}

configure_mtools() {
	echo "Checking if $MTOOLS_VERSION has been configured"
	if ! [ -f "$KOS_BINUTILS/misc/opt/$MTOOLS_VERSION/Makefile" ]; then
		echo "	Now configuring $MTOOLS_VERSION"
		cmd mkdir -p "$KOS_BINUTILS/misc/opt/$MTOOLS_VERSION"
		cmd cd "$KOS_BINUTILS/misc/opt/$MTOOLS_VERSION"
		cmd bash "$KOS_BINUTILS/src/$MTOOLS_VERSION/configure" \
			--prefix="$KOS_BINUTILS/misc"

		# Work around an issue: mtools forgets to add -liconv when
		# linking, so prevent it from making use of that stuff.
		cmd [ -f "config.h" ]
		cmd echo "#undef HAVE_ICONV_H" >> "config.h"

		cmd cd "$KOS_BINUTILS"
	else
		echo "	$MTOOLS_VERSION has already been configured"
	fi
}

build_mtools() {
	echo "Checking if $MTOOLS_VERSION has been built"
	if ! [ -f "$KOS_BINUTILS/misc/bin/mtools" ] && \
	   ! [ -f "$KOS_BINUTILS/misc/bin/mtools.exe" ]; then
		if ! [ -f "$KOS_BINUTILS/misc/opt/$MTOOLS_VERSION/mtools" ] && \
		   ! [ -f "$KOS_BINUTILS/misc/opt/$MTOOLS_VERSION/mtools.exe" ]; then
			echo "	Now building $MTOOLS_VERSION"
			cmd cd "$KOS_BINUTILS/misc/opt/$MTOOLS_VERSION"
			cmd make -j $MAKE_PARALLEL_COUNT
		else
			echo "	$MTOOLS_VERSION has already been built"
		fi
		echo "	Now installing $MTOOLS_VERSION (to '$KOS_BINUTILS/misc/')"
		cmd cd "$KOS_BINUTILS/misc/opt/$MTOOLS_VERSION"
		# The install command for mtools doesn't like it if its bin dir already exists?
		# Anyways: if may `make' here fails, we check if it did in fact install the exe
		#          already, and if so: we just act like everything worked ;)
		if ! make -j $MAKE_PARALLEL_COUNT install; then
			if ! [ -f "$KOS_BINUTILS/misc/bin/mtools" ] && \
			   ! [ -f "$KOS_BINUTILS/misc/bin/mtools.exe" ]; then
				cmd make -j $MAKE_PARALLEL_COUNT install
			fi
		fi
		cmd cd "$KOS_BINUTILS"
	else
		echo "	$MTOOLS_VERSION has already been installed"
	fi
}



cmd() {
	$* || {
		local error=$?
		echo "ERROR: Command failed '$*' -> '$error'"
		exit $error
	}
}





# Configure based on selected target.
if [[ "$1" == i?86-kos ]]; then
	TARGET_NAME="i386"
	NAME="i386-kos"
	INCLUDE_NAME="i386-kos"
	BINLIBDIRNAME="lib"
	SYSHEADER_BUILD_CONFIG_SUFFIX="32"
	export TARGET="i686-kos"
elif [[ "$1" == x86_64-kos ]]; then
	if ! [ -f "${KOS_MISC}/../../binutils/i386-kos/bin/i686-kos-gcc" ] && \
	   ! [ -f "${KOS_MISC}/../../binutils/i386-kos/bin/i686-kos-gcc.exe" ]; then
		# Because of compatibility mode, the x86_64-kos toolchain also requires i386-kos
		# in order to build stuff such as the 32-bit libdl.so driver, among others.
		cmd bash "${KOS_MISC}/make_toolchain.sh" "i386-kos"
	fi
	TARGET_NAME="x86_64"
	NAME="x86_64-kos"
	INCLUDE_NAME="i386-kos"
	BINLIBDIRNAME="lib64"
	CONFIGURE_OPTIONS_BINUTILS+=("--enable-64-bit-bfd")
	CONFIGURE_OPTIONS_GCC+=("--enable-64-bit-bfd")
	SYSHEADER_BUILD_CONFIG_SUFFIX="64"
	export TARGET="x86_64-kos"
elif [[ "$1" == arm-kos ]]; then
	TARGET_NAME="arm"
	NAME="arm-kos"
	INCLUDE_NAME="arm-kos"
	BINLIBDIRNAME="lib"
	export TARGET="arm-kos"
	CONFIGURE_OPTIONS_GCC+=("--with-arch=armv6")
	CONFIGURE_OPTIONS_GCC+=("--with-fpu=vfp")
else
	echo "Unknown target: '$1'"
	exit 1
fi


require_program() {
	which $1 > /dev/null 2>&1 || {
		local error=$?
		echo "ERROR: Required program not found '$1' -> '$error'"
		echo "	   Check if this program is installed, and make sure that it's in \$PATH"
		exit $error
	}
}

KOS_PATCHES="${KOS_MISC}/patches"
cmd cd "$KOS_MISC/../../"
KOS_ROOT="$(pwd)"

if [ -f "${KOS_ROOT}/kos/misc/tool-configs/vs-launch.vs.json" ]; then
	if [ "${KOS_ROOT}/kos/misc/tool-configs/vs-launch.vs.json" -nt "${KOS_ROOT}/kos/.vs/launch.vs.json" ]; then
		unlink "${KOS_ROOT}/kos/.vs/launch.vs.json" > /dev/null 2>&1
		cmd cp "${KOS_ROOT}/kos/misc/tool-configs/vs-launch.vs.json" "${KOS_ROOT}/kos/.vs/launch.vs.json"
		NT_KOS_ROOT="$KOS_ROOT"
		if [[ `uname -s` == *CYGWIN* ]]; then
			NT_KOS_ROOT="$(cygpath -w "$KOS_ROOT")"
		fi
		NT_KOS_ROOT="${NT_KOS_ROOT//\\/\\\\\\\\}"
		cmd sed -i -e "s?ABSOLUTE_KOS_PROJECT_ROOT?${KOS_ROOT}?g" "${KOS_ROOT}/kos/.vs/launch.vs.json"
		cmd sed -i -e "s?ABSOLUTE_KOS_NT_PROJECT_ROOT?${NT_KOS_ROOT}?g" "${KOS_ROOT}/kos/.vs/launch.vs.json"
	fi
fi

if [ -f "${KOS_ROOT}/kos/misc/tool-configs/vscode-launch.json" ]; then
	if [ "${KOS_ROOT}/kos/misc/tool-configs/vscode-launch.json" -nt "${KOS_ROOT}/kos/.vscode/launch.json" ]; then
		unlink "${KOS_ROOT}/kos/.vscode/launch.json" > /dev/null 2>&1
		cmd cp "${KOS_ROOT}/kos/misc/tool-configs/vscode-launch.json" "${KOS_ROOT}/kos/.vscode/launch.json"
		NT_KOS_ROOT="$KOS_ROOT"
		if [[ `uname -s` == *CYGWIN* ]]; then
			NT_KOS_ROOT="$(cygpath -w "$KOS_ROOT")"
		fi
		NT_KOS_ROOT="${NT_KOS_ROOT//\\/\\\\\\\\}"
		cmd sed -i -e "s?ABSOLUTE_KOS_PROJECT_ROOT?${KOS_ROOT}?g" "${KOS_ROOT}/kos/.vscode/launch.json"
		cmd sed -i -e "s?ABSOLUTE_KOS_NT_PROJECT_ROOT?${NT_KOS_ROOT}?g" "${KOS_ROOT}/kos/.vscode/launch.json"
	fi
fi

cmd mkdir -p "binutils"
cmd cd "binutils"
KOS_BINUTILS="$(pwd)"

cmd mkdir -p "$NAME"
cmd mkdir -p "src"

# Make sure that we have required programs in $PATH
require_program "make"

# If the user doesn't have deemon installed, download, configure,
# and build a version that can be used to drive the KOS toolchain.
echo "Check if deemon is installed on the machine"
echo "Check if deemon was installed under '$KOS_BINUTILS/deemon'"
if [ -f "$KOS_BINUTILS/deemon/deemon.exe" ]; then
	DEEMON="$KOS_BINUTILS/deemon/deemon.exe"
	echo "	Found deemon in '$KOS_BINUTILS/deemon/deemon.exe'"
elif [ -f "$KOS_BINUTILS/deemon/deemon" ]; then
	DEEMON="$KOS_BINUTILS/deemon/deemon"
	echo "	Found deemon in '$KOS_BINUTILS/deemon/deemon'"
else
	echo "	Deemon is missing (now downloading, configuring and building a local copy)"
	if ! [ -f "$KOS_BINUTILS/deemon/configure" ]; then
		require_program "git"
		rm -rf "$KOS_BINUTILS/deemon" > /dev/null 2>&1
		cmd mkdir -p "$KOS_BINUTILS/deemon"
		cmd cd "$KOS_BINUTILS/deemon"
		cmd git clone --recursive "https://github.com/GrieferAtWork/deemon.git" "."
		cmd git checkout -f "$DEEMON_VERSION"
	fi
	cmd cd "$KOS_BINUTILS/deemon"
	echo "Configuring deemon..."
	cmd bash "./configure"
	echo "Making deemon..."
	cmd make -j "$MAKE_PARALLEL_COUNT"
	cmd cd "$KOS_BINUTILS"
	if [ -f "$KOS_BINUTILS/deemon/deemon.exe" ]; then
		DEEMON="$KOS_BINUTILS/deemon/deemon.exe"
	else
		DEEMON="$KOS_BINUTILS/deemon/deemon"
	fi
fi

# Generate project files and configurations
echo "Updating VS/VSC configuration files..."
cmd cd ".."
cmd "$DEEMON" "kos/misc/config/files.dee"
cmd cd "binutils"

# Download sources
download_binutils
download_gcc
download_mtool

# Patch sources
patch_binutils
patch_gcc
patch_mtools


do_mkdir() {
	echo "Creating directory: $1"
	cmd mkdir -p "$1"
}
do_symlink() {
	echo "Creating symbolic link: $2 -> $1"
	unlink "$2" > /dev/null 2>&1
	cmd ln -s "$1" "$2"
}


export PREFIX="$KOS_BINUTILS/$NAME"

do_mkdir "$PREFIX"
do_mkdir "$PREFIX/binutils"
do_mkdir "$PREFIX/gcc"
do_mkdir "$PREFIX/gdb"
do_mkdir "$PREFIX/bin"
do_mkdir "$PREFIX/usr"
do_mkdir "$PREFIX/share"
do_mkdir "$PREFIX/lib"
do_mkdir "$PREFIX/opt/pkg_config"
do_mkdir "$PREFIX/$TARGET/usr"

# Make sure that our bin/lib paths were created, else GCC won't detect them...
do_mkdir "$KOS_ROOT/bin/$NAME-$KOS_CONFIG_FOR_LINKING/bin"
do_mkdir "$KOS_ROOT/bin/$NAME-$KOS_CONFIG_FOR_LINKING/$BINLIBDIRNAME"
do_mkdir "$KOS_ROOT/bin/$NAME-common/bin"
do_mkdir "$KOS_ROOT/bin/$NAME-common/$BINLIBDIRNAME"

# Also make sure that a valid KOS build configuration was been selected
do_symlink "$NAME-$KOS_CONFIG_FOR_LINKING" "$KOS_ROOT/bin/$NAME"

# Create the symlinks for GCC to detect and correctly bind our system library-
# and system header paths (note that `../../../bin/$NAME' is another symlink
# that gets automagically rotated by magic.dee depending on the last-used build
# configuration, which is a set of OPTIMIZE=y/n and DEBUG=y/n)
do_symlink "../../../bin/$NAME/bin"               "$PREFIX/usr/bin"
do_symlink "../../../bin/$NAME/$BINLIBDIRNAME"    "$PREFIX/usr/lib"
do_symlink "../../../kos/include"                 "$PREFIX/usr/include"
do_symlink "../../../../bin/$NAME/bin"            "$PREFIX/$TARGET/usr/bin"
do_symlink "../../../../bin/$NAME/$BINLIBDIRNAME" "$PREFIX/$TARGET/usr/lib"
do_symlink "../../../../kos/include"              "$PREFIX/$TARGET/usr/include"


echo "Checking if $BINUTILS_VERSION has been configured"
if ! [ -f "$PREFIX/binutils/Makefile" ]; then
	echo "	Now configuring $BINUTILS_VERSION"
	cmd cd "$PREFIX/binutils"
	cmd bash "../../src/$BINUTILS_VERSION/configure" \
		"${CONFIGURE_OPTIONS_BINUTILS[@]}" \
		"--target=$TARGET" \
		"--prefix=$PREFIX" \
		"--with-sysroot=$PREFIX" \
		"--with-headers=$PREFIX/usr/include" \
		"--disable-nls" \
		"--disable-werror" \
		"--enable-multilib"
	cmd cd "$KOS_BINUTILS"
else
	echo "	Already configured"
fi

unlink "$PREFIX/$TARGET/sys-include" > /dev/null 2>&1
rm -r "$PREFIX/$TARGET/sys-include" > /dev/null 2>&1
do_symlink "../../../kos/include" "$PREFIX/$TARGET/sys-include"

unlink "$PREFIX/$TARGET/include" > /dev/null 2>&1
rm -r "$PREFIX/$TARGET/include" > /dev/null 2>&1
do_symlink "../../../kos/include/$INCLUDE_NAME" "$PREFIX/$TARGET/include"


echo "Check if $BINUTILS_VERSION needs to be built"
if ! [ -f "$PREFIX/bin/${TARGET}-ld" ] && ! [ -f "$PREFIX/bin/${TARGET}-ld.exe" ]; then
	echo "	Making $BINUTILS_VERSION"
	cmd cd "$PREFIX/binutils"
	cmd make -j $MAKE_PARALLEL_COUNT
	cmd make -j $MAKE_PARALLEL_COUNT install
	cmd cd "$KOS_BINUTILS"
else
	echo "	Binutils $BINUTILS_VERSION has already been built"
fi



echo "Checking if $GCC_VERSION has been configured"
if ! [ -f "$PREFIX/gcc/Makefile" ]; then
	echo "	Now configuring $GCC_VERSION"
	cmd cd "$PREFIX/gcc"
	cmd bash "../../src/$GCC_VERSION/configure" \
		"${CONFIGURE_OPTIONS_GCC[@]}" \
		"--target=$TARGET" \
		"--prefix=$PREFIX" \
		"--with-sysroot=$PREFIX" \
		"--with-gnu-ld" \
		"--with-gnu-as" \
		"--with-dwarf2" \
		"--enable-gnu-unique-object" \
		"--disable-vtable-verify" \
		"--enable-threads=single" \
		"--enable-targets=all" \
		"--enable-languages=c,c++" \
		"--disable-nls" \
		"--enable-multiarch" \
		"--enable-initfini-array" \
		"--enable-__cxa_atexit" \
		"--enable-multilib" \
		"--enable-gnu-indirect-function"
	cmd cd "$KOS_BINUTILS"
else
	echo "	Already configured"
fi

echo "Check if $GCC_VERSION needs to be built"
if ! [ -f "$PREFIX/bin/${TARGET}-gcc" ] && ! [ -f "$PREFIX/bin/${TARGET}-gcc.exe" ]; then
	echo "	Making $GCC_VERSION"
	cmd cd "$PREFIX/gcc"
	cmd make -j $MAKE_PARALLEL_COUNT all-gcc
	cmd make -j $MAKE_PARALLEL_COUNT install-gcc
	cmd cd "$KOS_BINUTILS"
else
	echo "	$GCC_VERSION has already been built"
fi

remove_fixinclude() {
	echo "Checking for $1"
	if [ -f "$1" ]; then
		echo "	Removing fixinclude header file $1"
		cmd unlink "$1"
#	else
#		echo "	Already deleted"
	fi
}

delete_header_file() {
	echo "Checking for $1"
	if [ -f "$1" ]; then
		echo "	Removing header file $1"
		cmd rm "$1"
#	else
#		echo "	Already deleted"
	fi
}

remove_bad_fixinclude() {
	remove_fixinclude "$PREFIX/lib/gcc/$TARGET/$GCC_VERSION_NUMBER/include/unwind.h"
	remove_fixinclude "$PREFIX/lib/gcc/$TARGET/$GCC_VERSION_NUMBER/include/stddef.h"
	remove_fixinclude "$PREFIX/lib/gcc/$TARGET/$GCC_VERSION_NUMBER/include/stdbool.h"
	remove_fixinclude "$PREFIX/lib/gcc/$TARGET/$GCC_VERSION_NUMBER/include/stdarg.h"
	remove_fixinclude "$PREFIX/lib/gcc/$TARGET/$GCC_VERSION_NUMBER/include/stdatomic.h"
	remove_fixinclude "$PREFIX/lib/gcc/$TARGET/$GCC_VERSION_NUMBER/include/stdnoreturn.h"
	remove_fixinclude "$PREFIX/lib/gcc/$TARGET/$GCC_VERSION_NUMBER/include/stdalign.h"
	remove_fixinclude "$PREFIX/lib/gcc/$TARGET/$GCC_VERSION_NUMBER/include/float.h"
	remove_fixinclude "$PREFIX/lib/gcc/$TARGET/$GCC_VERSION_NUMBER/include/iso646.h"
	remove_fixinclude "$PREFIX/lib/gcc/$TARGET/$GCC_VERSION_NUMBER/include-fixed/limits.h"
	remove_fixinclude "$PREFIX/lib/gcc/$TARGET/$GCC_VERSION_NUMBER/include-fixed/syslimits.h"
	remove_fixinclude "$PREFIX/lib/gcc/$TARGET/$GCC_VERSION_NUMBER/include/varargs.h"
}

remove_bad_fixinclude

echo "Check if $GCC_VERSION:libgcc needs to be built"
if ! [ -f "$PREFIX/lib/gcc/$TARGET/$GCC_VERSION_NUMBER/libgcc.a" ] && \
   ! [ -f "$PREFIX/$TARGET/lib/libgcc_s.so.1" ]; then
	cmd cd "$KOS_ROOT"

	# If this is the first time that "magic.dee" is being run after the git was cloned,
	# we can make life a little bit easier for the user by skipping the step where we
	# (re-)generate system headers. -- In this case doing so should be unnecessary, as
	# (presumably) none of the related source files have yet to change.
	# For this purpose, we touch the "*.latest" files that are used to keep track of
	# the last-modified dates of the relevant component.
	[ -f "kos/misc/magicgenerator/.generate_headers.dee.latest" ] || \
		cmd touch "kos/misc/magicgenerator/.generate_headers.dee.latest"
	[ -f "kos/misc/magicgenerator/.generate_syscalls.dee.latest" ] || \
		cmd touch "kos/misc/magicgenerator/.generate_syscalls.dee.latest"
	[ -f "kos/misc/magicgenerator/.generate_syscalls.dee.$TARGET_NAME.latest" ] || \
		cmd touch "kos/misc/magicgenerator/.generate_syscalls.dee.$TARGET_NAME.latest"

	if ! [ -f "bin/$NAME-$KOS_CONFIG_FOR_LINKING/$BINLIBDIRNAME/crt0.o" ] || \
	   ! [ -f "bin/$NAME-$KOS_CONFIG_FOR_LINKING/$BINLIBDIRNAME/crt0S.o" ]; then
		echo "	Making crt0.o and crt0S.o for $GCC_VERSION:libgcc"
		cmd "$DEEMON" "magic.dee" \
			"--gen=bin/$NAME-$KOS_CONFIG_FOR_LINKING/$BINLIBDIRNAME/crt0.o" \
			"--gen=bin/$NAME-$KOS_CONFIG_FOR_LINKING/$BINLIBDIRNAME/crt0S.o" \
			"--target=$TARGET_NAME" \
			"--config=$KOS_CONFIG_FOR_LINKING"
	fi
	echo "	Making $GCC_VERSION:libgcc"
	cmd cd "$PREFIX/gcc"
	if ! make -j "$MAKE_PARALLEL_COUNT" "all-target-libgcc"; then
		echo ">>>> DON'T PANIC! -- I think I know how to fix that error ;)"

		# This is a bit hacky:
		#   - In order to build libgcc_s.so, we already need to have libc.so.
		#   - In order to build libc.so, we need to have libgcc.a
		#   - Even though the above make failed, it (should have) already created `libgcc.a'
		# With that in mind:
		#   - Temporarily install the libgcc.a it build above,
		#   - Create our libc.so
		#   - Delete the libgcc.a we installed before
		#   - Try the make command above again
		unlink "$PREFIX/lib/gcc/$TARGET/$GCC_VERSION_NUMBER/libgcc.a" > /dev/null 2>&1
		cmd cp \
			"$PREFIX/gcc/$TARGET/libgcc/libgcc.a" \
			"$PREFIX/lib/gcc/$TARGET/$GCC_VERSION_NUMBER/libgcc.a"

		# Now try to build our libc.so (and also libm.so just to be safe)
		cmd cd "$KOS_ROOT"
		remove_bad_fixinclude
		cmd "$DEEMON" "magic.dee" \
			"--gen=bin/$NAME-$KOS_CONFIG_FOR_LINKING/$BINLIBDIRNAME/libc.so" \
			"--gen=bin/$NAME-$KOS_CONFIG_FOR_LINKING/$BINLIBDIRNAME/libm.so" \
			"--target=$TARGET_NAME" \
			"--config=$KOS_CONFIG_FOR_LINKING"
		cmd cd "$PREFIX/gcc"
		unlink "$PREFIX/lib/gcc/$TARGET/$GCC_VERSION_NUMBER/libgcc.a" > /dev/null 2>&1

		# Try to build libgcc again
		cmd make -j "$MAKE_PARALLEL_COUNT" "all-target-libgcc"
	fi
	cmd make -j "$MAKE_PARALLEL_COUNT" "all-target-libgcc"
	cmd make -j "$MAKE_PARALLEL_COUNT" "install-target-libgcc"
	remove_bad_fixinclude
	cmd cd "$KOS_BINUTILS"
else
	echo "	$GCC_VERSION:libgcc has already been built"
fi


echo "Check if $GCC_VERSION:libstdc++ needs to be built"
if ! [ -f "$PREFIX/$TARGET/lib/libstdc++.so.$LIBSTDCXX_VERSION_FULL" ] || \
   ! [ -f "$PREFIX/$TARGET/include/c++/$GCC_VERSION_NUMBER/vector" ]; then
	# When building libstdc++ for i386/x86_64, with the other libstdc++ already
	# having had its headers installed, we must manually backup the arch-specific
	# portion of the existing libstdc++ installation, as the make process might
	# otherwise interfere with it. (We do however restore it later...)
	OTHER_TOOLCHAIN=""
	if [ $TARGET_NAME == "i386" ] || [ $TARGET_NAME == "x86_64" ]; then
		if [ $TARGET_NAME == "i386" ]; then
			OTHER_TOOLCHAIN="x86_64-kos"
		else
			OTHER_TOOLCHAIN="i686-kos"
		fi
		if [ -d "$PREFIX/$TARGET/include/c++/$GCC_VERSION_NUMBER/$OTHER_TOOLCHAIN" ]; then
			cmd mv \
				"$PREFIX/$TARGET/include/c++/$GCC_VERSION_NUMBER/$OTHER_TOOLCHAIN" \
				"$PREFIX/$TARGET/include/c++-backup-$GCC_VERSION_NUMBER-$OTHER_TOOLCHAIN"
		fi
	fi
	echo "	Make sure to delete any existing installation of c++ headers"
	rm -r "$PREFIX/$TARGET/include/c++/$GCC_VERSION_NUMBER"
	# Build our own libc.so and libm.so before building libstdc++, so GCC can link against our code!
	echo "	Making libc.so and libm.so for $GCC_VERSION:libstdc++"
	cmd cd "$KOS_ROOT"
	cmd "$DEEMON" "magic.dee" \
		--gen="bin/$NAME-$KOS_CONFIG_FOR_LINKING/$BINLIBDIRNAME/crt0.o" \
		--gen="bin/$NAME-$KOS_CONFIG_FOR_LINKING/$BINLIBDIRNAME/crt0S.o" \
		--gen="bin/$NAME-$KOS_CONFIG_FOR_LINKING/$BINLIBDIRNAME/libc.so" \
		--gen="bin/$NAME-$KOS_CONFIG_FOR_LINKING/$BINLIBDIRNAME/libm.so" \
		--target="$TARGET_NAME" \
		--config="$KOS_CONFIG_FOR_LINKING"
	echo "	Making $GCC_VERSION:libstdc++"
	cmd cd "$PREFIX/gcc"
	if ! make -j "$MAKE_PARALLEL_COUNT" "all-target-libstdc++-v3"; then
		echo ">>>> DON'T PANIC! -- I think I know how to fix that error ;)"

		# Yet another place where we need to be hacky with fixing up headers.
		# This time around, it's libstdc++ that only half-heartedly understands
		# the fact that KOS's system headers already define c++ functions, and
		# already place all of the required function prototypes into the `std'
		# namespace
		# e.g.: libstdc++ does understand `__CORRECT_ISO_CPP_STRING_H_PROTO',
		#       but doesn't understand us defining the c++ math functions
		#       for `isnan()', `isinf()', etc.
		# To fix this, delete libstdc++'s problematic headers and replace then
		# with symlinks to KOS's (actually working ~wow!~) headers.
		# Sadly, we can only do this once the make already failed once, since
		# the framework surrounding those headers only gets created by said
		# make command!
		# Even more importantly, libstdc++ needs `__USE_BROKEN_CCOMPAT' (s.a. <features.h>)
		LIBSTDCXX_INCLUDE_PATHS=("$PREFIX/gcc/$TARGET/libstdc++-v3/include")
		if [[ "$TARGET_NAME" == "arm" ]]; then
			LIBSTDCXX_INCLUDE_PATHS+=("$PREFIX/gcc/$TARGET/arm/autofp/v5te/fpu/libstdc++-v3/include")
			LIBSTDCXX_INCLUDE_PATHS+=("$PREFIX/gcc/$TARGET/thumb/libstdc++-v3/include")
			LIBSTDCXX_INCLUDE_PATHS+=("$PREFIX/gcc/$TARGET/thumb/autofp/v7/fpu/libstdc++-v3/include")
		fi

		# $1: header name (e.g. `stdlib')
		use_real_header() {
			for LIBSTDCXX_INCLUDE_PATH in "${LIBSTDCXX_INCLUDE_PATHS[@]}"; do
				echo "	Link real header for '${LIBSTDCXX_INCLUDE_PATH}/c$1'"
				unlink "${LIBSTDCXX_INCLUDE_PATH}/c$1" > /dev/null 2>&1
				cmd ln -s "$KOS_ROOT/kos/include/c$1" "${LIBSTDCXX_INCLUDE_PATH}/c$1"
				echo "	Link real header for '${LIBSTDCXX_INCLUDE_PATH}/$1.h'"
				unlink "${LIBSTDCXX_INCLUDE_PATH}/$1.h" > /dev/null 2>&1
				cmd ln -s "$KOS_ROOT/kos/include/$1.h" "${LIBSTDCXX_INCLUDE_PATH}/$1.h"
			done
		}
		echo "Fixup libstdc++ build-time headers"
		for HEADER_NAME in "${CXX_COMPAT_HEADER_NAMES[@]}"; do
			use_real_header "$HEADER_NAME"
		done
		for HEADER_NAME in "${CXX_COMPAT_HEADER_FILES[@]}"; do
			for LIBSTDCXX_INCLUDE_PATH in "${LIBSTDCXX_INCLUDE_PATHS[@]}"; do
				echo "	Link real header for '${LIBSTDCXX_INCLUDE_PATH}/$HEADER_NAME'"
				unlink "${LIBSTDCXX_INCLUDE_PATH}/$HEADER_NAME" > /dev/null 2>&1
				cmd ln -s "$KOS_ROOT/kos/include/$HEADER_NAME" "${LIBSTDCXX_INCLUDE_PATH}/$HEADER_NAME"
			done
		done
		cmd make -j "$MAKE_PARALLEL_COUNT" "all-target-libstdc++-v3"
	fi
	cmd make -j "$MAKE_PARALLEL_COUNT" "install-target-libstdc++-v3"
	remove_bad_fixinclude
	cmd cd "$KOS_BINUTILS"
	# Restore the arch-specific portion of the other toolchain
	if [ $OTHER_TOOLCHAIN != "" ]; then
		if [ -d "$PREFIX/$TARGET/include/c++-backup-$GCC_VERSION_NUMBER-$OTHER_TOOLCHAIN" ]; then
			cmd mv \
				"$PREFIX/$TARGET/include/c++-backup-$GCC_VERSION_NUMBER-$OTHER_TOOLCHAIN" \
				"$PREFIX/$TARGET/include/c++/$GCC_VERSION_NUMBER/$OTHER_TOOLCHAIN"
		fi
	fi
else
	echo "	$GCC_VERSION:libstdc++ has already been built"
fi

install_libstdcxx() {
	echo "Check if $GCC_VERSION:libstdc++ was installed into $1"
	if ! [ -f "$1/libstdc++.so.$LIBSTDCXX_VERSION" ]; then
		echo "	Copying $GCC_VERSION:libstdc++ into $1"
		cmd mkdir -p "$1"
		cmd cp \
			"$PREFIX/$TARGET/lib/libstdc++.so.$LIBSTDCXX_VERSION_FULL" \
			"$1/libstdc++.so.$LIBSTDCXX_VERSION"
	else
		echo "	$GCC_VERSION:libstdc++ has already installed to $1"
	fi
	echo "Check if $GCC_VERSION:libgcc_s was installed into $1"
	if ! [ -f "$1/libgcc_s.so.$LIBGCC_VERSION" ]; then
		if [ -f "$PREFIX/$TARGET/lib/libgcc_s.so.$LIBGCC_VERSION_FULL" ]; then
			echo "	Copying $GCC_VERSION:libgcc_s into $1"
			cmd mkdir -p "$1"
			cmd cp \
				"$PREFIX/$TARGET/lib/libgcc_s.so.$LIBGCC_VERSION_FULL" \
				"$1/libgcc_s.so.$LIBGCC_VERSION"
		else
			echo "	$GCC_VERSION:libgcc_s wasn't built for this architecture"
		fi
	else
		echo "	$GCC_VERSION:libgcc_s has already been installed to $1"
	fi
}

install_libstdcxx_symlinks() {
	echo "Check if $GCC_VERSION:libstdc++ was installed into $1"
	if ! [ -f "$1/libstdc++.so.$LIBSTDCXX_VERSION" ]; then
		echo "	Installing $GCC_VERSION:libstdc++ into $1"
		cmd mkdir -p "$1"
		cmd ln -s \
			"../../${NAME}-common/$BINLIBDIRNAME/libstdc++.so.$LIBSTDCXX_VERSION" \
			"$1/libstdc++.so.$LIBSTDCXX_VERSION"
	else
		echo "	$GCC_VERSION:libstdc++ has already installed to $1"
	fi
	echo "Check if $GCC_VERSION:libgcc_s was installed into $1"
	if ! [ -f "$1/libgcc_s.so.$LIBGCC_VERSION" ]; then
		if [ -f "$PREFIX/$TARGET/lib/libgcc_s.so.$LIBGCC_VERSION_FULL" ]; then
			echo "	Installing $GCC_VERSION:libgcc_s into $1"
			cmd mkdir -p "$1"
			cmd ln -s \
				"../../${NAME}-common/$BINLIBDIRNAME/libgcc_s.so.$LIBGCC_VERSION_FULL" \
				"$1/libgcc_s.so.$LIBGCC_VERSION_FULL"
		else
			echo "	$GCC_VERSION:libgcc_s wasn't built for this architecture"
		fi
	else
		echo "	$GCC_VERSION:libgcc_s has already been installed to $1"
	fi
}

install_libstdcxx "${KOS_ROOT}/bin/${NAME}-common/$BINLIBDIRNAME"
cmd cd "${KOS_ROOT}/kos/include/kos/config/configurations"
for BUILD_CONFIG in *.h; do
	BUILD_CONFIG="${BUILD_CONFIG::-2}"
	install_libstdcxx_symlinks "${KOS_ROOT}/bin/${NAME}-${BUILD_CONFIG}/$BINLIBDIRNAME"
done

# Installing libstdc++ leaves behind a bunch of unwanted overrides for system headers which
# we're already providing ourself. - Just remove those headers
for HEADER_NAME in "${CXX_COMPAT_HEADER_NAMES[@]}"; do
	delete_header_file "$PREFIX/$TARGET/include/c++/$GCC_VERSION_NUMBER/c$HEADER_NAME"
	delete_header_file "$PREFIX/$TARGET/include/c++/$GCC_VERSION_NUMBER/$HEADER_NAME.h"
done
for HEADER_NAME in "${CXX_COMPAT_HEADER_FILES[@]}"; do
	delete_header_file "$PREFIX/$TARGET/include/c++/$GCC_VERSION_NUMBER/$HEADER_NAME"
done
for HEADER_NAME in "${CXX_KOS_SPECIFIC_HEADER_FILES[@]}"; do
	delete_header_file "$PREFIX/$TARGET/include/c++/$GCC_VERSION_NUMBER/$HEADER_NAME"
done

# KOS overrides the <bits/os_defines.h> header from libstdc++, so to prevent confusion,
# simply delete that header from the installed libstdc++ headers.
delete_header_file "$PREFIX/$TARGET/include/c++/${GCC_VERSION_NUMBER}/${TARGET}/bits/os_defines.h"

# $1: .patch file
# $2: Header file path where patch should be applied
apply_libstdcxx_header_patch() {
	echo "Check if our headers for $GCC_VERSION:libstdc++ ($2) need to be patched"
	if ! [ -f "$1" ]; then
		echo "	No patch file found: $1"
	elif ! [ -f "$2/.libstdc++.kos_patched" ]; then
		echo "	Applying patch: $1 to $2"
		cmd patch -d "$2" -p1 < "$1"
		> "$2/.libstdc++.kos_patched"
	else
		echo "	Our headers for $GCC_VERSION:libstdc++ ($2) have already been patched"
	fi
}

apply_libstdcxx_header_patch \
	"$KOS_PATCHES/libstdc++-${GCC_VERSION_NUMBER}.patch" \
	"$PREFIX/$TARGET/include/c++/${GCC_VERSION_NUMBER}"

apply_libstdcxx_header_patch \
	"$KOS_PATCHES/libstdc++-${GCC_VERSION_NUMBER}-${NAME}.patch" \
	"$PREFIX/$TARGET/include/c++/${GCC_VERSION_NUMBER}/${TARGET}"

# Configure and build mtools
configure_mtools
build_mtools


# Create symbolic links for binutils programs
symlink_binutil() {
	if ! [ -f "$PREFIX/bin/$1" ] && ! [ -f "$PREFIX/bin/$1.exe" ]; then
		echo "Creating binutils utility link '$PREFIX/bin/$1'"
		if [ -f "$PREFIX/bin/${TARGET}-$1" ]; then
			cmd ln -s "${TARGET}-$1" "$PREFIX/bin/$1"
		elif [ -f "$PREFIX/bin/${TARGET}-$1.exe" ]; then
			cmd ln -s "${TARGET}-$1.exe" "$PREFIX/bin/$1.exe"
		else
			echo "WARNING: Missing binutils utility: '$PREFIX/bin/${TARGET}-$1'"
		fi
	fi
}
symlink_binutil addr2line
symlink_binutil ar
symlink_binutil as
symlink_binutil c++
symlink_binutil c++filt
symlink_binutil cpp
symlink_binutil elfedit
symlink_binutil g++
symlink_binutil gcc
symlink_binutil gcc-$GCC_VERSION_NUMBER
symlink_binutil gcc-ar
symlink_binutil gcc-nm
symlink_binutil gcc-ranlib
symlink_binutil gcov
symlink_binutil gcov-dump
symlink_binutil gcov-tool
symlink_binutil gprof
symlink_binutil ld.bfd
symlink_binutil ld
symlink_binutil nm
symlink_binutil objcopy
symlink_binutil objdump
symlink_binutil ranlib
symlink_binutil readelf
symlink_binutil size
symlink_binutil strings
symlink_binutil strip

# Create a symlink:
#   from: "$PREFIX/lib/gcc/$TARGET/$GCC_VERSION_NUMBER/include-fixed"
#   to:   "$PREFIX/cimpplify-include"
echo "Creating for cimpplify-include redirection"
unlink "$PREFIX/lib/gcc/$TARGET/$GCC_VERSION_NUMBER/include-fixed" > /dev/null 2>&1
cmd rm -rf "$PREFIX/lib/gcc/$TARGET/$GCC_VERSION_NUMBER/include-fixed"
do_mkdir "$PREFIX/cimpplify-include"
cmd ln -s "../../../../cimpplify-include" "$PREFIX/lib/gcc/$TARGET/$GCC_VERSION_NUMBER/include-fixed"


install_cat_file() {
	echo "Checking for $1"
	if ! [ -f "$1" ]; then
		echo "Creating file $1"
		cat > "$1"
	else
		echo "	File already exists"
	fi
}

# KOS includes a built-in version of libpciaccess.
# Advertise this fact such that 3rd party programs can find it.
install_cat_file "$PREFIX/opt/pkg_config/pciaccess.pc" <<EOF
prefix=/
exec_prefix=/
libdir="$KOS_ROOT/bin/$NAME/$BINLIBDIRNAME"
includedir="$KOS_ROOT/kos/include"

Name: pciaccess
Description: KOS-specific reimplementation
Version: 0.16
Cflags:
Libs: -lpciaccess
EOF

install_cat_file "$PREFIX/opt/pkg_config/libattr.pc" <<EOF
prefix=/
exec_prefix=/
libdir="$KOS_ROOT/bin/$NAME/$BINLIBDIRNAME"
includedir="$KOS_ROOT/kos/include"

Name: libattr
Description: A library for filesystem extended attribute support
Version: 2.5.1
Cflags:
Libs: -lc
EOF


# In order to ensure consistency and make certain that the libiconv
# git submodule always includes up-to-date versions of its own headers
# which are normally found in /kos/include/libiconv, we use hardlinks
# in order to have files in that folder mirror /kos/src/libiconv/include
lib_mirror_include() {
	echo "Checking for hard link: $KOS_ROOT/kos/src/$1/include/$2"
	NLINK="$(stat --printf="%h" "$KOS_ROOT/kos/src/$1/include/$2" 2>/dev/null)"
	if [[ "$NLINK" != 2 ]]; then
		unlink "$KOS_ROOT/kos/include/$1/$2" > /dev/null 2>&1
		if ln -P \
			"$KOS_ROOT/kos/src/$1/include/$2" \
			"$KOS_ROOT/kos/include/$1/$2" \
		> /dev/null 2>&1; then
			echo "	Hard link created"
		else
			# As fallback (if the filesystem doesn't support hard links), just copy back the file
			echo "	Failed to create hard link (use copy instead)"
			cmd cp \
				"$KOS_ROOT/kos/src/$1/include/$2" \
				"$KOS_ROOT/kos/include/$1/$2"
		fi
	fi
}
cmd cd "$KOS_ROOT/kos/include/libiconv"
for name in *.h; do
	lib_mirror_include "libiconv" "$name"
done
cmd cd "$KOS_ROOT/kos/include/libregex"
for name in *.h; do
	lib_mirror_include "libregex" "$name"
done

if test -z "$SYSHEADER_BUILD_CONFIG_SUFFIX"; then
	SYSHEADER_BUILD_CONFIG_SUFFIX=""
fi
cmd mkdir -p "$KOS_ROOT/kos/include/$INCLUDE_NAME/kos/config"
BUILD_CONFIG_HEADER="$KOS_ROOT/kos/include/$INCLUDE_NAME/kos/config/_toolchain${SYSHEADER_BUILD_CONFIG_SUFFIX}.h"
echo "Updating build configuration: $BUILD_CONFIG_HEADER"
DI=($(date -u +"%-s %0Y %0m %0d %0H %0M %0S %0N"))
lstrip() { echo -n "${1#"${1%%[1-9]*}"}"; }
IFS="."
PARTS_VERSION_BINUTILS=($BINUTILS_VERSION_NUMBER)
PARTS_VERSION_GCC=($GCC_VERSION_NUMBER)
unset IFS

cat > "$BUILD_CONFIG_HEADER" <<EOF
#ifndef KOS_BUILD_CONFIG_TOOLCHAIN_HOST
#define KOS_BUILD_CONFIG_TOOLCHAIN_BINUTILS_URL     "$BINUTILS_VERSION_URL"
#define KOS_BUILD_CONFIG_TOOLCHAIN_BINUTILS_VERSION "$BINUTILS_VERSION_NUMBER"
$(i=0; for part in "${PARTS_VERSION_BINUTILS[@]}"; do
	echo "#define KOS_BUILD_CONFIG_TOOLCHAIN_BINUTILS_VERSION_$i $part"
	: $((i += 1))
done)
#define KOS_BUILD_CONFIG_TOOLCHAIN_GCC_URL     "$GCC_VERSION_URL"
#define KOS_BUILD_CONFIG_TOOLCHAIN_GCC_VERSION "$GCC_VERSION_NUMBER"
$(i=0; for part in "${PARTS_VERSION_GCC[@]}"; do
	echo "#define KOS_BUILD_CONFIG_TOOLCHAIN_GCC_VERSION_$i $part"
	: $((i += 1))
done)
#define KOS_BUILD_CONFIG_TOOLCHAIN_HOST       "$(gcc -dumpmachine)"
#define KOS_BUILD_CONFIG_TOOLCHAIN_HOST_ROOT  "$KOS_ROOT"
#define KOS_BUILD_CONFIG_TOOLCHAIN_BUILD      "$TARGET_NAME-kos"
#define KOS_BUILD_CONFIG_TOOLCHAIN_BUILD_ARCH "$TARGET_NAME"
#define KOS_BUILD_CONFIG_TOOLCHAIN_BUILD_CPU  "${TARGET%%-*}"
#define KOS_BUILD_CONFIG_TOOLCHAIN_DATE_INFO  ($(lstrip ${DI[0]}),($(lstrip ${DI[1]},$(lstrip ${DI[2]},$(lstrip ${DI[3]},$(lstrip ${DI[4]},$(lstrip ${DI[5]},$(lstrip ${DI[6]},$(lstrip ${DI[7]})))))))),(${DI[1]},${DI[2]},${DI[3]},${DI[4]},${DI[5]},${DI[6]},${DI[7]}))
#endif /* !KOS_BUILD_CONFIG_TOOLCHAIN_HOST */
EOF



# On windows, try to build the gdbridge wrapper program
if [[ "$(uname -s)" == *"CYGWIN"* ]]; then
	if ! [ -f "$KOS_MISC/gdbridge/gdbridge.exe" ] || \
		 [ "$KOS_MISC/gdbridge/gdbridge.exe" -ot "$KOS_MISC/gdbridge/gdbridge.c" ]; then
		echo "Building GDBridge wrapper"
		GDBRIDGE_FLAGS=("-g" "-Wall")
		GDBRIDGE_SCRIPT="$(cygpath -w "$KOS_MISC/gdbridge/gdbridge.dee")"
		GDBRIDGE_CMDLINE="$(cygpath -w "$DEEMON")"
		GDBRIDGE_CMDLINE="$GDBRIDGE_CMDLINE \"${GDBRIDGE_SCRIPT}\""
		GDBRIDGE_CMDLINE="${GDBRIDGE_CMDLINE//\\/\\\\}"
		GDBRIDGE_CMDLINE="${GDBRIDGE_CMDLINE//\"/\\\"}"
		GDBRIDGE_CMDLINE="\"${GDBRIDGE_CMDLINE}\""
		echo "cmdline: $GDBRIDGE_CMDLINE"
		gcc "${GDBRIDGE_FLAGS[@]}" \
			"-DCMDLINE=$GDBRIDGE_CMDLINE" \
			-o "$KOS_MISC/gdbridge/gdbridge.exe" \
			"$KOS_MISC/gdbridge/gdbridge.c" \
		|| {
			local error=$?
			echo "ERROR: Command failed 'gcc ${GDBRIDGE_FLAGS[@]} -DCMDLINE=\"$GDBRIDGE_CMDLINE\" -o \"$KOS_MISC/gdbridge/gdbridge.exe\" \"$KOS_MISC/gdbridge/gdbridge.c\"' -> '$error'"
			exit $error
		}
	fi
fi


# Because this is as good'a place as any, use our
# chance here to set-up our custom git pre-commit hook.
echo "Check for git pre-commit hook"
if ! [ -d "$KOS_ROOT/.git" ]; then
	echo "	disabled: No .git folder"
else
	cmd chmod +x "$KOS_ROOT/kos/misc/git-hooks/pre-commit"
	#cmd ln -s "../../kos/misc/git-hooks/pre-commit" "$KOS_ROOT/.git/hooks/pre-commit"
	cmd git config --local core.hooksPath "kos/misc/git-hooks"
	echo "	now hooked"
fi
