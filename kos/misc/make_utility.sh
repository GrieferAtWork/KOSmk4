#!/bin/bash


cmd() {
	$* || {
		local error=$?
		echo "ERROR: Command failed '$*' -> '$error'"
		exit $error
	}
}

while [[ $# -gt 0 ]]; do
	case $1 in

	*)
		break
		;;
	esac
done

if (($# != 2)); then
	echo "Usage: ./make_utility.sh [OPTIONS...] <TARGET_NAME> <UTILITY_NAME>"
	echo "    OPTIONS:"
	echo "        ..."
	echo "    TARGET_NAME should be one of:"
	echo "        i386"
	echo "        x86_64"
	echo "    For a list of valid UTILITY_NAME, review the switch at the bottom of this file"
	exit 1
fi

TARGET_NAME="$1"
UTILITY_NAME="$2"
TARGET_CPUNAME="$TARGET_NAME"
if [ "$TARGET_CPUNAME" == "i386" ]; then
	TARGET_CPUNAME="i686"
fi


KOS_MISC="$(dirname $(readlink -f "$0"))"
KOS_PATCHES="${KOS_MISC}/patches"
cmd cd "$KOS_MISC/../../"
KOS_ROOT="$(pwd)"
TARGET_SYSROOT="${KOS_ROOT}/bin/${TARGET_NAME}-kos-common"
BINUTILS_SYSROOT="${KOS_ROOT}/binutils/${TARGET_NAME}-kos"
KOS_VALID_BUILD_CONFIGS="OD nOD OnD nOnD"
MTOOLS="$KOS_ROOT/binutils/build-mtools/mtools"

if ! [ -d "$TARGET_SYSROOT" ]; then
	echo "Common system root ${TARGET_SYSROOT} is missing (re-run 'make_toolchain.sh' to fix)"
	exit 1
fi


## mtools_makedir <DISKIMAGE> <ABSOLUTE_DISK_PATH>
mtools_makedir() {
	if ! "$MTOOLS" -c mmd -i "$1" -D s "::/$2" > /dev/null 2>&1; then
		local PARENT="$(dirname "$2")"
		if [ "$PARENT" != "$2" ]; then
			mtools_makedir "$1" "$PARENT"
		fi
		"$MTOOLS" -c mmd -i "$1" -D s "::/$2" > /dev/null 2>&1
	fi
}

## mtools_install_file <DISKIMAGE> <ABSOLUTE_DISK_PATH> <SOURCE>
mtools_install_file() {
	if ! "$MTOOLS" -c mcopy -i "$1" -D o "$3" "::/$2" > /dev/null 2>&1; then
		mtools_makedir "$1" "$(dirname "/$2")"
		cmd "$MTOOLS" -c mcopy -i "$1" -D o "$3" "::/$2"
	fi
}

## mtools_install_path <DISKIMAGE> <ABSOLUTE_DISK_PATH> <SOURCE>
mtools_install_path() {
	if ! "$MTOOLS" -c mcopy -i "$1" -s -n -D o "$3" "::/$2" > /dev/null 2>&1; then
		mtools_makedir "$1" "$(dirname "/$2")"
		cmd "$MTOOLS" -c mcopy -i "$1" -s -n -D o "$3" "::/$2"
	fi
}

## install_file <ABSOLUTE_DISK_PATH> <SOURCE>
install_file() {
	DISPATH="${1#/}"
	unlink "$TARGET_SYSROOT/$DISPATH" > /dev/null 2>&1
	echo "Installing ${TARGET_NAME}-kos:/$DISPATH"
	if ! cp "$2" "$TARGET_SYSROOT/$DISPATH" > /dev/null 2>&1; then
		cmd mkdir -p "$(dirname "$TARGET_SYSROOT/$DISPATH")"
		cmd cp "$2" "$TARGET_SYSROOT/$DISPATH"
	fi
	local RELPATH=$(python -c "import os.path; print os.path.relpath('/${TARGET_NAME}-kos-common/$1', '/foo/$(dirname "/$1")')")
	for BUILD_CONFIG in $(echo $KOS_VALID_BUILD_CONFIGS); do
		local CONFIG_SYSROOT="${KOS_ROOT}/bin/${TARGET_NAME}-kos-${BUILD_CONFIG}"
		unlink "$CONFIG_SYSROOT/$DISPATH" > /dev/null 2>&1
		if ! ln -s "$RELPATH" "$CONFIG_SYSROOT/$DISPATH" > /dev/null 2>&1; then
			cmd mkdir -p "$(dirname "$CONFIG_SYSROOT/$DISPATH")"
			cmd ln -s "$RELPATH" "$CONFIG_SYSROOT/$DISPATH"
		fi
		if [ -f "$CONFIG_SYSROOT/disk.img" ]; then
			echo "    Disk: '$CONFIG_SYSROOT/disk.img'"
			mtools_install_file "$CONFIG_SYSROOT/disk.img" "$DISPATH" "$2"
		fi
	done
}

## install_path <ABSOLUTE_DISK_PATH> <SOURCE>
install_path() {
	DISPATH="${1#/}"
	echo "Installing ${TARGET_NAME}-kos:/$DISPATH/*"
	cmd mkdir -p "$(dirname "$TARGET_SYSROOT/$DISPATH")"
	local RELPATH=$(python -c "import os.path; print os.path.relpath('$2', '$TARGET_SYSROOT/$(dirname "$DISPATH")')")
	unlink "$TARGET_SYSROOT/$DISPATH" > /dev/null 2>&1
	cmd ln -s "$RELPATH" "$TARGET_SYSROOT/$DISPATH"
	local RELPATH=$(python -c "import os.path; print os.path.relpath('/${TARGET_NAME}-kos-common/$1', '/foo/$(dirname "/$1")')")
	for BUILD_CONFIG in $(echo $KOS_VALID_BUILD_CONFIGS); do
		local CONFIG_SYSROOT="${KOS_ROOT}/bin/${TARGET_NAME}-kos-${BUILD_CONFIG}"
		unlink "$CONFIG_SYSROOT/$DISPATH" > /dev/null 2>&1
		if ! ln -s "$RELPATH" "$CONFIG_SYSROOT/$DISPATH" > /dev/null 2>&1; then
			cmd mkdir -p "$(dirname "$CONFIG_SYSROOT/$DISPATH")"
			cmd ln -s "$RELPATH" "$CONFIG_SYSROOT/$DISPATH"
		fi
		if [ -f "$CONFIG_SYSROOT/disk.img" ]; then
			echo "    Disk: '$CONFIG_SYSROOT/disk.img'"
			mtools_install_path "$CONFIG_SYSROOT/disk.img" "$DISPATH" "$2"
		fi
	done
}


# download_file  <DST_FILE>  <URL>
download_file() {
	echo "Checking download: $1"
	if ! [ -f "$1" ]; then
		local OLDPWD="$(pwd)"
		cmd cd "$(dirname "$1")"
		cmd wget "$2"
		cmd cd "$OLDPWD"
		if ! [ -f "$1" ]; then
			echo "Missing file '$1'"
			exit 1
		fi
	fi
}

# apply_patch  <DST_PATH>  <PATCH_FILE>
apply_patch() {
	if ! [ -f "$1/.kos_patched" ]; then
		echo "    Applying patch: $2 to $1"
		cmd patch -d "$1" -p1 < "$2"
		> "$1/.kos_patched"
	fi
}

# Set $PATH to include target toolchain utilities.
set_archpath() {
	export PATH="${BINUTILS_SYSROOT}/bin:${PATH}"
	export CC="${CROSS_PREFIX}gcc"
	export AR="${CROSS_PREFIX}ar"
}


# Configure some utilities for general-purpose cross-compiling
export CROSS_TARGET="$TARGET_NAME-elf"
export CROSS_PREFIX="$KOS_ROOT/binutils/$TARGET_NAME-kos/bin/$TARGET_CPUNAME-kos-"
export CROSS_COMPILE="$CROSS_PREFIX"
MAKE_PARALLEL_COUNT=$(grep -c ^processor /proc/cpuinfo)

case $UTILITY_NAME in

##############################################################################
	busybox | busybox-1.31.0)
		BUSYBOX_VERISON="1.31.0"
		## Check final output binary
		if ! [ -f "$BINUTILS_SYSROOT/opt/busybox-$BUSYBOX_VERISON/busybox_unstripped" ]; then
			## Check arch makefile
			if ! [ -f "$BINUTILS_SYSROOT/opt/busybox-$BUSYBOX_VERISON/Makefile" ]; then
				## Check shared (original) makefile
				if ! [ -f "$KOS_ROOT/binutils/src/busybox-$BUSYBOX_VERISON/Makefile" ]; then
					cmd cd "$KOS_ROOT/binutils/src"
					download_file \
						"busybox-$BUSYBOX_VERISON.tar.bz2" \
						https://www.busybox.net/downloads/busybox-$BUSYBOX_VERISON.tar.bz2
					cmd tar jxvf "busybox-$BUSYBOX_VERISON.tar.bz2"
				fi
				if [ -d "$BINUTILS_SYSROOT/opt/busybox-$BUSYBOX_VERISON" ]; then
					cmd rm -rf "$BINUTILS_SYSROOT/opt/busybox-$BUSYBOX_VERISON"
				fi
				cmd cp -R \
					"$KOS_ROOT/binutils/src/busybox-$BUSYBOX_VERISON" \
					"$BINUTILS_SYSROOT/opt/"
			fi
			apply_patch \
				"$BINUTILS_SYSROOT/opt/busybox-$BUSYBOX_VERISON" \
				"$KOS_ROOT/kos/misc/patches/busybox-$BUSYBOX_VERISON.patch"
			cmd cd "$BINUTILS_SYSROOT/opt/busybox-$BUSYBOX_VERISON"
			PATCH_CONFIG="$KOS_ROOT/kos/misc/patches/busybox.config"
			if ! [ -f ".config" ] || [ ".config" -ot "$PATCH_CONFIG" ]; then
				unlink ".config" > /dev/null 2>&1
				cmd cp "$KOS_ROOT/kos/misc/patches/busybox.config" ".config"
			fi
			cmd make -j $MAKE_PARALLEL_COUNT CROSS_COMPILE="$CROSS_PREFIX"
		fi
		# Install busybox in KOS
		install_file /bin/busybox  \
			"$BINUTILS_SYSROOT/opt/busybox-$BUSYBOX_VERISON/busybox_unstripped"
		;;
##############################################################################


##############################################################################
	vitetris | vitetris-0.58.0)
		VITETRIS_VERISON="0.58.0"
		SRCPATH="$KOS_ROOT/binutils/src/vitetris-$VITETRIS_VERISON"
		OPTPATH="$BINUTILS_SYSROOT/opt/vitetris-$VITETRIS_VERISON"
		if ! [ -f "$OPTPATH/tetris" ]; then
			set_archpath
			if ! [ -f "$OPTPATH/configure" ]; then
				if ! [ -f "$SRCPATH/configure" ]; then
					cmd cd "$KOS_ROOT/binutils/src"
					if ! [ -f "vitetris-$VITETRIS_VERISON.tar.gz" ]; then
						download_file \
							"v$VITETRIS_VERISON.tar.gz" \
							https://github.com/vicgeralds/vitetris/archive/v$VITETRIS_VERISON.tar.gz
						mv "v$VITETRIS_VERISON.tar.gz" "vitetris-$VITETRIS_VERISON.tar.gz"
					fi
					cmd tar xvf "vitetris-$VITETRIS_VERISON.tar.gz"
				fi
				cmd cp -R "$SRCPATH" "$BINUTILS_SYSROOT/opt/"
			fi
			cmd cd "$OPTPATH"
			cmd bash configure CC="$CC" CFLAGS="-ggdb"
			cmd make -j $MAKE_PARALLEL_COUNT
		fi
		install_file /bin/tetris  \
			"$OPTPATH/tetris"
		;;
##############################################################################


##############################################################################
	tcc | tcc-0.9.27)
		TCC_VERISON="0.9.27"
		SRCPATH="$KOS_ROOT/binutils/src/tcc-$TCC_VERISON"
		OPTPATH="$BINUTILS_SYSROOT/opt/tcc-$TCC_VERISON"
		if ! [ -f "$OPTPATH/$TARGET_NAME-tcc" ]; then
			set_archpath
			if ! [ -f "$SRCPATH/configure" ]; then
				cmd cd "$KOS_ROOT/binutils/src"
				download_file \
					"tcc-$TCC_VERISON.tar.bz2" \
					http://download.savannah.gnu.org/releases/tinycc/tcc-0.9.27.tar.bz2
				cmd tar jxvf "tcc-$TCC_VERISON.tar.bz2"
			fi
			rm -rf "$OPTPATH" > /dev/null 2>&1
			cmd cp -R "$SRCPATH" "$BINUTILS_SYSROOT/opt/"
			cmd cd "$OPTPATH"
			apply_patch "$OPTPATH" "$KOS_ROOT/kos/misc/patches/tcc-$TCC_VERISON.patch"
			cmd bash configure \
				--with-libgcc \
				--with-selinux \
				--cpu="$TARGET_NAME" \
				--enable-cross \
				--cross-prefix="$CROSS_PREFIX" \
				--bindir="/bin" \
				--includedir="/usr/include" \
				--sysincludepaths="/usr/include/${TARGET_NAME}-kos:/usr/include" \
				--libpaths="/usr/lib:/lib" \
				--crtprefix="/usr/lib" \
				--elfinterp="/lib/libdl.so" \
				--config-mingw32=no
			echo 'NATIVE_DEFINES+=-DTCC_TARGET_KOS="1"' >> config.mak
			echo 'NATIVE_DEFINES+=-DCONFIG_TCCDIR="\"/usr/lib\""' >> config.mak
			cmd make cross-$TARGET_NAME $TARGET_NAME-libtcc1-usegcc=yes
			cat > "$OPTPATH/hello-world.c" <<EOF
/* A simple hello-world example which you can compile & run from inside of KOS:
 * $ cd /usr/src
 * $ tcc hello-world.c
 * $ ./a.out
 * >> Hello World
 */
extern int printf(char const *format, ...);

int main() {
	printf("Hello %s\n", "World");
	return 0;
}
EOF
		fi
		install_file /bin/tcc "$OPTPATH/$TARGET_NAME-tcc"
		install_file /usr/lib/$TARGET_NAME-libtcc1.a "$OPTPATH/$TARGET_NAME-libtcc1.a"
		install_file /usr/lib/crt0S.o "${KOS_ROOT}/bin/${TARGET_NAME}-kos/lib/crt0S.o"
		install_file /usr/lib/crt0.o "${KOS_ROOT}/bin/${TARGET_NAME}-kos/lib/crt0.o"
		install_file /usr/src/hello-world.c "$OPTPATH/hello-world.c"
		;;
##############################################################################


##############################################################################
	kos-headers)
		install_path /usr/include "${KOS_ROOT}/kos/include"
		cmd mkdir -p "$BINUTILS_SYSROOT/opt"
		cat > "$BINUTILS_SYSROOT/opt/hello-header-temp.c" <<EOF
#include <stdio.h>

int main() {
	printf("Hello %s\n", "Header");
	return 0;
}
EOF
		install_file /usr/src/hello-header.c "$BINUTILS_SYSROOT/opt/hello-header-temp.c"
		unlink "$BINUTILS_SYSROOT/opt/hello-header-temp.c" > /dev/null 2>&1
		;;
##############################################################################


	*)
		echo "Unknown utility '$UTILITY_NAME'"
		exit 1
		;;
esac









