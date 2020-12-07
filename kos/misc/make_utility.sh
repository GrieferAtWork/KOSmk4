#!/bin/bash
# Copyright (c) 2019-2020 Griefer@Work
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
#    Portions Copyright (c) 2019-2020 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.


#>> cmd <ARGV...>
cmd() {
	$* || {
		local error=$?
		echo "ERROR: Command failed '$*' -> '$error'"
		exit $error
	}
}

#>> xcmd <ARGV...>
xcmd() {
	$* || {
		local error=$?
		echo "ERROR: Command failed '$*' -> '$error'"
		return $error
	}
}

#>> vcmd <ARGV...>
vcmd() {
	echo "run: $*"
	$* || {
		local error=$?
		echo "ERROR: Command failed '$*' -> '$error'"
		exit $error
	}
}

#>> vxcmd <ARGV...>
vxcmd() {
	echo "run: $*"
	$* || {
		local error=$?
		echo "ERROR: Command failed '$*' -> '$error'"
		return $error
	}
}

MODE_FORCE_CONF=no
MODE_FORCE_MAKE=no
MODE_FORCE_DISK=no
MODE_DRYRUN=no

while [[ $# -gt 0 ]]; do
	case $1 in

	--force-configure)
		MODE_FORCE_CONF=yes
		MODE_FORCE_MAKE=yes
		;;

	--force-make)
		MODE_FORCE_MAKE=yes
		;;

	--force-disk)
		MODE_FORCE_DISK=yes
		;;

	--dry-run)
		MODE_DRYRUN=yes
		;;

	*)
		break
		;;
	esac
	shift
done

if (($# != 2)); then
	echo "Usage: ./make_utility.sh [OPTIONS...] <TARGET_NAME> <UTILITY_NAME>"
	echo "    OPTIONS:"
	echo "        --force-configure     Force configure to be re-executed"
	echo "        --force-make          Force make to be re-executed"
	echo "        --force-disk          Force on-disk files to be updated"
	echo "    TARGET_NAME should be one of:"
	echo "        i386"
	echo "        x86_64"
	echo "    UTILITY_NAME should be one of:"
	cd "$(dirname $(readlink -f "$0"))/utilities"
	for name in *.sh; do
		echo "        ${name::-3}"
	done
	exit 1
fi

TARGET_NAME="$1"
UTILITY_NAME="$2"
TARGET_CPUNAME="$TARGET_NAME"
TARGET_LIBPATH="lib"
TARGET_INCPATH="$TARGET_CPUNAME-kos"
if [ "$TARGET_CPUNAME" == "i386" ]; then
	TARGET_CPUNAME="i686"
	TARGET_CONFIG_ILP32=1
fi
if [ "$TARGET_CPUNAME" == "x86_64" ]; then
	TARGET_INCPATH="i386-kos"
	TARGET_LIBPATH="lib64"
	TARGET_CONFIG_LP64=1
fi


KOS_MISC="$(dirname $(readlink -f "$0"))"
KOS_PATCHES="${KOS_MISC}/patches"
cmd cd "$KOS_MISC/../../"
KOS_ROOT="$(pwd)"
TARGET_SYSROOT="${KOS_ROOT}/bin/${TARGET_NAME}-kos-common"
BINUTILS_SYSROOT="${KOS_ROOT}/binutils/${TARGET_NAME}-kos"
MTOOLS="$KOS_ROOT/binutils/misc/bin/mtools"

if ! [ -d "$TARGET_SYSROOT" ]; then
	echo "Common system root ${TARGET_SYSROOT} is missing (re-run 'make_toolchain.sh' to fix)"
	exit 1
fi

# This is the path where PKG_CONFIG utilities load/install their config files
export PKG_CONFIG_PATH="$BINUTILS_SYSROOT/opt/pkg_config"
export PKG_CONFIG_LIBDIR="$PKG_CONFIG_PATH"


require_program() {
	which $1 > /dev/null 2>&1 || {
		local error=$?
		echo "ERROR: Required program not found '$1' -> '$error'"
		echo "       Check if this program is installed, and make sure that it's in \$PATH"
		exit $error
	}
}

# require_utility <UTILITY_NAME> <INDICATOR_FILE>
require_utility() {
	if ! [ -f "$2" ]; then
		echo "Required untility not installed: $1 (file '$2' does't exist)"
		echo "Resolve this issue by running:"
		echo "\$ bash make_utility.sh $TARGET_NAME $1"
		exit 1
	fi
}


#>> mtools_makedir <DISKIMAGE> <ABSOLUTE_DISK_PATH>
mtools_makedir() {
	if ! "$MTOOLS" -c mmd -i "$1" -D s "::/$2" > /dev/null 2>&1; then
		local PARENT="$(dirname "$2")"
		if [ "$PARENT" != "$2" ]; then
			mtools_makedir "$1" "$PARENT"
		fi
		"$MTOOLS" -c mmd -i "$1" -D s "::/$2" > /dev/null 2>&1
	fi
}

#>> mtools_install_file <DISKIMAGE> <ABSOLUTE_DISK_PATH> <SOURCE>
mtools_install_file() {
	if ! "$MTOOLS" -c mcopy -i "$1" -D o "$3" "::/$2" > /dev/null 2>&1; then
		mtools_makedir "$1" "$(dirname "/$2")"
		cmd "$MTOOLS" -c mcopy -i "$1" -D o "$3" "::/$2"
	fi
}

#>> mtools_install_path <DISKIMAGE> <ABSOLUTE_DISK_PATH> <SOURCE>
mtools_install_path() {
	if ! "$MTOOLS" -c mcopy -i "$1" -s -n -D o "$3" "::/$2" > /dev/null 2>&1; then
		mtools_makedir "$1" "$(dirname "/$2")"
		cmd "$MTOOLS" -c mcopy -i "$1" -s -n -D o "$3" "::/$2"
	fi
}

#>> install_rawfile <DEST> <SOURCE>
install_rawfile() {
	if test x"$MODE_DRYRUN" != xno; then
		echo "> install_rawfile '$1' '$2'"
	elif ! [ -f "$1" ] || [ "$2" -nt "$1" ]; then
		if cmp -s "$1" "$2" > /dev/null 2>&1; then
			echo "Installing file $1 (unchanged)"
		else
			unlink "$1" > /dev/null 2>&1
			echo "Installing file $1"
			if ! cp "$2" "$1" > /dev/null 2>&1; then
				cmd mkdir -p "$(dirname "$1")"
				cmd cp "$2" "$1"
			fi
		fi
	else
		echo "Installing file $1 (up to date)"
	fi
}

#>> install_rawfile_stdin <DEST> <<EOF ... EOF
install_rawfile_stdin() {
	if test x"$MODE_DRYRUN" != xno; then
		echo "> install_rawfile_stdin '$1'"
	elif ! [ -f "$1" ]; then
		echo "Installing file $1"
		cmd mkdir -p "$(dirname "$1")"
		cat > "$1" < /dev/stdin
	else
		echo "Installing file $1 (up to date)"
	fi
}


#>> install_file <ABSOLUTE_DISK_PATH> <SOURCE>
install_file() {
	if test x"$MODE_DRYRUN" != xno; then
		echo "> install_file '$1' '$2'"
	else
		DISPATH="${1#/}"
		TARGET_DISPATH="$TARGET_SYSROOT/$DISPATH"
		DIDUPDATE="no"
		if ! [ -f "$TARGET_DISPATH" ] || [ "$2" -nt "$TARGET_DISPATH" ]; then
			unlink "$TARGET_DISPATH" > /dev/null 2>&1
			echo "Installing file ${TARGET_NAME}-kos:/$DISPATH"
			DIDUPDATE="yes"
			if ! cp "$2" "$TARGET_DISPATH" > /dev/null 2>&1; then
				cmd mkdir -p "$(dirname "$TARGET_DISPATH")"
				cmd cp "$2" "$TARGET_DISPATH"
			fi
		else
			echo "Installing file ${TARGET_NAME}-kos:/$DISPATH (up to date)"
		fi
		local OLDPWD="$(pwd)"
		cmd cd "${KOS_ROOT}/bin"
		local BUILD_CONFIG_NAMES=$(echo ${TARGET_NAME}-kos-*)
		cmd cd "$OLDPWD"
		local TARGET_DISPATH_MODIFIED="$(stat -c %Y "$TARGET_DISPATH")"
		for BUILD_CONFIG in $BUILD_CONFIG_NAMES; do
			if [ "$BUILD_CONFIG" != "${TARGET_NAME}-kos-common" ]; then
				local CONFIG_SYSROOT="${KOS_ROOT}/bin/${BUILD_CONFIG}"
				local CONFIG_DISPATH="$CONFIG_SYSROOT/$DISPATH"
				local DISKIMAGE="$CONFIG_SYSROOT/disk.img"
				if [ -f "$DISKIMAGE" ]; then
					if [ "$DIDUPDATE" == yes ] || ! [ -f "$CONFIG_DISPATH" ] || \
					   [ "$TARGET_DISPATH_MODIFIED" -gt "$(stat -c %Y "$CONFIG_DISPATH")" ]; then
						echo "    Conf: '$CONFIG_SYSROOT'"
						unlink "$CONFIG_DISPATH" > /dev/null 2>&1
						if ! ln -r -s "$TARGET_DISPATH" "$CONFIG_DISPATH" > /dev/null 2>&1; then
							cmd mkdir -p "$(dirname "$CONFIG_DISPATH")"
							cmd ln -r -s "$TARGET_DISPATH" "$CONFIG_DISPATH"
						fi
						echo "        Disk: '$DISKIMAGE'"
						mtools_install_file "$DISKIMAGE" "$DISPATH" "$2"
					else
						echo "    Conf: '$CONFIG_SYSROOT' (up to date)"
						if [ "$MODE_FORCE_DISK" == "yes" ]; then
							echo "        Disk: '$DISKIMAGE' (forced)"
							mtools_install_file "$DISKIMAGE" "$DISPATH" "$2"
						fi
					fi
				fi
			fi
		done
	fi
}

#>> install_symlink <ABSOLUTE_DISK_PATH> <TEXT>
install_symlink() {
	if test x"$MODE_DRYRUN" != xno; then
		echo "> install_symlink '$1' '$2'"
	else
		DISPATH="${1#/}"
		TARGET_DISPATH="$TARGET_SYSROOT/$DISPATH"
		DIDUPDATE="no"
		if ! [ -f "$TARGET_DISPATH" ] || \
		     [ "$(readlink "$TARGET_DISPATH")" != "$2" ]; then
			unlink "$TARGET_DISPATH" > /dev/null 2>&1
			echo "Installing link ${TARGET_NAME}-kos:/$DISPATH (ln -s \"$2\")"
			DIDUPDATE="yes"
			if ! ln -s "$2" "$TARGET_DISPATH" > /dev/null 2>&1; then
				cmd mkdir -p "$(dirname "$TARGET_DISPATH")"
				cmd ln -s "$2" "$TARGET_DISPATH"
			fi
		else
			echo "Installing link ${TARGET_NAME}-kos:/$DISPATH (up to date)"
		fi
		local OLDPWD="$(pwd)"
		cmd cd "${KOS_ROOT}/bin"
		local BUILD_CONFIG_NAMES=$(echo ${TARGET_NAME}-kos-*)
		cmd cd "$OLDPWD"
		for BUILD_CONFIG in $BUILD_CONFIG_NAMES; do
			if [ "$BUILD_CONFIG" != "${TARGET_NAME}-kos-common" ]; then
				local CONFIG_SYSROOT="${KOS_ROOT}/bin/${BUILD_CONFIG}"
				local CONFIG_DISPATH="$CONFIG_SYSROOT/$DISPATH"
				if [ "$DIDUPDATE" == yes ] || ! [ -f "$CONFIG_DISPATH" ]; then
					echo "    Conf: '$CONFIG_SYSROOT'"
					unlink "$CONFIG_DISPATH" > /dev/null 2>&1
					if ! ln -r -s "$TARGET_DISPATH" "$CONFIG_DISPATH" > /dev/null 2>&1; then
						cmd mkdir -p "$(dirname "$CONFIG_DISPATH")"
						cmd ln -r -s "$TARGET_DISPATH" "$CONFIG_DISPATH"
					fi
				else
					echo "    Conf: '$CONFIG_SYSROOT' (up to date)"
				fi
			fi
		done
	fi
}

#>> install_mkdir <ABSOLUTE_DISK_PATH>
install_mkdir() {
	if test x"$MODE_DRYRUN" != xno; then
		echo "> install_mkdir '$1'"
	else
		DISPATH="${1#/}"
		TARGET_DISPATH="$TARGET_SYSROOT/$DISPATH"
		DIDUPDATE="no"
		if ! [ -d "$TARGET_DISPATH" ]; then
			echo "Installing dir ${TARGET_NAME}-kos:/$DISPATH"
			DIDUPDATE="yes"
			cmd mkdir -p "$TARGET_DISPATH"
		else
			echo "Installing dir ${TARGET_NAME}-kos:/$DISPATH (up to date)"
		fi
		local OLDPWD="$(pwd)"
		cmd cd "${KOS_ROOT}/bin"
		local BUILD_CONFIG_NAMES=$(echo ${TARGET_NAME}-kos-*)
		cmd cd "$OLDPWD"
		local TARGET_DISPATH_MODIFIED="$(stat -c %Y "$TARGET_DISPATH")"
		for BUILD_CONFIG in $BUILD_CONFIG_NAMES; do
			if [ "$BUILD_CONFIG" != "${TARGET_NAME}-kos-common" ]; then
				local CONFIG_SYSROOT="${KOS_ROOT}/bin/${BUILD_CONFIG}"
				local CONFIG_DISPATH="$CONFIG_SYSROOT/$DISPATH"
				local DISKIMAGE="$CONFIG_SYSROOT/disk.img"
				if [ -f "$DISKIMAGE" ]; then
					if [ "$DIDUPDATE" == yes ] || ! [ -d "$CONFIG_DISPATH" ]; then
						echo "    Conf: '$CONFIG_SYSROOT'"
						cmd mkdir -p "$CONFIG_DISPATH"
						echo "        Disk: '$DISKIMAGE'"
						mtools_makedir "$DISKIMAGE" "$DISPATH"
					else
						echo "    Conf: '$CONFIG_SYSROOT' (up to date)"
						if [ "$MODE_FORCE_DISK" == "yes" ]; then
							echo "        Disk: '$DISKIMAGE' (forced)"
							mtools_makedir "$DISKIMAGE" "$DISPATH"
						fi
					fi
				fi
			fi
		done
	fi
}

#>> install_file_nodisk <ABSOLUTE_DISK_PATH> <SOURCE>
install_file_nodisk() {
	if test x"$MODE_DRYRUN" != xno; then
		echo "> install_file_nodisk '$1' '$2'"
	else
		DISPATH="${1#/}"
		TARGET_DISPATH="$TARGET_SYSROOT/$DISPATH"
		DIDUPDATE="no"
		if ! [ -f "$TARGET_DISPATH" ] || [ "$TARGET_DISPATH" -ot "$2" ]; then
			unlink "$TARGET_DISPATH" > /dev/null 2>&1
			echo "Installing file ${TARGET_NAME}-kos:/$DISPATH"
			DIDUPDATE="yes"
			if ! cp "$2" "$TARGET_DISPATH" > /dev/null 2>&1; then
				cmd mkdir -p "$(dirname "$TARGET_DISPATH")"
				cmd cp "$2" "$TARGET_DISPATH"
			fi
		else
			echo "Installing file ${TARGET_NAME}-kos:/$DISPATH (up to date)"
		fi
		local OLDPWD="$(pwd)"
		cmd cd "${KOS_ROOT}/bin"
		local BUILD_CONFIG_NAMES=$(echo ${TARGET_NAME}-kos-*)
		cmd cd "$OLDPWD"
		for BUILD_CONFIG in $BUILD_CONFIG_NAMES; do
			if [ "$BUILD_CONFIG" != "${TARGET_NAME}-kos-common" ]; then
				local CONFIG_SYSROOT="${KOS_ROOT}/bin/${BUILD_CONFIG}"
				local CONFIG_DISPATH="$CONFIG_SYSROOT/$DISPATH"
				if [ "$DIDUPDATE" == yes ] || ! [ -e "$CONFIG_DISPATH" ]; then
					echo "    Conf: '$CONFIG_SYSROOT'"
					unlink "$CONFIG_DISPATH" > /dev/null 2>&1
					if ! ln -r -s "$TARGET_DISPATH" "$CONFIG_DISPATH" > /dev/null 2>&1; then
						cmd mkdir -p "$(dirname "$CONFIG_DISPATH")"
						cmd ln -r -s "$TARGET_DISPATH" "$CONFIG_DISPATH"
					fi
				else
					echo "    Conf: '$CONFIG_SYSROOT' (up to date)"
				fi
			fi
		done
	fi
}

#>> install_path <ABSOLUTE_DISK_PATH> <SOURCE>
install_path() {
	if test x"$MODE_DRYRUN" != xno; then
		echo "> install_path '$1' '$2'"
	else
		DISPATH="${1#/}"
		TARGET_DISPATH="$TARGET_SYSROOT/$DISPATH"
		if ! [ -e "$TARGET_DISPATH" ]; then
			echo "Installing path ${TARGET_NAME}-kos:/$DISPATH/*"
			if ! ln -r -s "$2" "$TARGET_DISPATH" > /dev/null 2>&1; then
				cmd mkdir -p "$(dirname "$TARGET_DISPATH")"
				cmd ln -r -s "$2" "$TARGET_DISPATH"
			fi
		else
			echo "Installing path ${TARGET_NAME}-kos:/$DISPATH/* (up to date)"
		fi
		local OLDPWD="$(pwd)"
		cmd cd "${KOS_ROOT}/bin"
		local BUILD_CONFIG_NAMES=$(echo ${TARGET_NAME}-kos-*)
		cmd cd "$OLDPWD"
		for BUILD_CONFIG in $BUILD_CONFIG_NAMES; do
			if [ "$BUILD_CONFIG" != "${TARGET_NAME}-kos-common" ]; then
				local CONFIG_SYSROOT="${KOS_ROOT}/bin/${BUILD_CONFIG}"
				local CONFIG_DISPATH="$CONFIG_SYSROOT/$DISPATH"
				local DISKIMAGE="$CONFIG_SYSROOT/disk.img"
				if [ -f "$DISKIMAGE" ]; then
					if [ "$(readlink -f "$CONFIG_DISPATH")" != \
					     "$(readlink -f "$TARGET_DISPATH")" ]; then
						echo "    Conf: '$CONFIG_SYSROOT'"
						unlink "$CONFIG_DISPATH" > /dev/null 2>&1
						if ! ln -r -s "$TARGET_DISPATH" "$CONFIG_DISPATH" > /dev/null 2>&1; then
							cmd mkdir -p "$(dirname "$CONFIG_DISPATH")"
							cmd ln -r -s "$TARGET_DISPATH" "$CONFIG_DISPATH"
						fi
					else
						echo "    Conf: '$CONFIG_SYSROOT' (up to date)"
					fi
					echo "        Disk: '$DISKIMAGE'"
					mtools_install_path "$DISKIMAGE" "$DISPATH" "$2"
				fi
			fi
		done
	fi
}

#>> install_path_hardcopy <ABSOLUTE_DISK_PATH> <SOURCE>
install_path_hardcopy() {
	if test x"$MODE_DRYRUN" != xno; then
		echo "> install_path_hardcopy '$1' '$2'"
	else
		DISPATH="${1#/}"
		TARGET_DISPATH="$TARGET_SYSROOT/$DISPATH"
		if true; then
			echo "Installing path ${TARGET_NAME}-kos:/$DISPATH/* (hardcopy)"
			cmd mkdir -p "$(dirname "$TARGET_DISPATH")"
			unlink "$TARGET_DISPATH" > /dev/null 2>&1
			cmd cp -R -n "$2" "$TARGET_DISPATH"
		fi
		local OLDPWD="$(pwd)"
		cmd cd "${KOS_ROOT}/bin"
		local BUILD_CONFIG_NAMES=$(echo ${TARGET_NAME}-kos-*)
		cmd cd "$OLDPWD"
		for BUILD_CONFIG in $BUILD_CONFIG_NAMES; do
			if [ "$BUILD_CONFIG" != "${TARGET_NAME}-kos-common" ]; then
				local CONFIG_SYSROOT="${KOS_ROOT}/bin/${BUILD_CONFIG}"
				local CONFIG_DISPATH="$CONFIG_SYSROOT/$DISPATH"
				local DISKIMAGE="$CONFIG_SYSROOT/disk.img"
				if [ -f "$DISKIMAGE" ]; then
					if [ "$(readlink -f "$CONFIG_DISPATH")" != \
					     "$(readlink -f "$TARGET_DISPATH")" ]; then
						echo "    Conf: '$CONFIG_SYSROOT'"
						unlink "$CONFIG_DISPATH" > /dev/null 2>&1
						if ! ln -r -s "$TARGET_DISPATH" "$CONFIG_DISPATH" > /dev/null 2>&1; then
							cmd mkdir -p "$(dirname "$CONFIG_DISPATH")"
							cmd ln -r -s "$TARGET_DISPATH" "$CONFIG_DISPATH"
						fi
					else
						echo "    Conf: '$CONFIG_SYSROOT' (up to date)"
					fi
					echo "    Disk: '$DISKIMAGE'"
					mtools_install_path "$DISKIMAGE" "$DISPATH" "$2"
				fi
			fi
		done
	fi
}

#>> rundeemon <ARGS...>
# Invoke `deemon $*`
rundeemon() {
	if which deemon > /dev/null 2>&1; then
		deemon $*
		return $?
	else
		"${KOS_ROOT}/binutils/deemon/deemon" $*
		return $?
	fi
}


#>> download_file  <DST_FILE>  <URL>
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

#>> apply_patch  <DST_PATH>  <PATCH_FILE>
apply_patch() {
	if ! [ -f "$1/.kos_patched" ]; then
		echo "    Applying patch: $2 to $1"
		cmd patch -d "$1" -p1 < "$2"
		> "$1/.kos_patched"
	fi
}

#>> set_archpath
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

UTILITY_SCRIPT="${KOS_ROOT}/kos/misc/utilities/${UTILITY_NAME}.sh"
if ! [ -f "$UTILITY_SCRIPT" ]; then
	echo "Unknown utility '$UTILITY_NAME'"
	exit 1
fi

# Include the utility-specific build-script as an inlined bash script here
. "$UTILITY_SCRIPT"









