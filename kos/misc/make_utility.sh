#!/bin/bash
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


# UI configuration
UI_PATHCOL_WIDTH="60"
UI_COLCFG_ACTION="94"
UI_COLCFG_FILETYPE="94"
UI_COLCFG_PATH_RAW="90"
UI_COLCFG_PATH_DISK="97"
UI_COLCFG_PATH_NODISK="37"
UI_COLCFG_OK="32"
UI_COLCFG_ERR="31"
UI_COLCFG_NAME="97"



# Execution mode
MODE_FORCE_CONF=no
MODE_FORCE_MAKE=no
MODE_FORCE_DISK=no
MODE_INSTALL_SH=no
MODE_DRYRUN=no
MODE_RECURSIVE=no


#>> cmd <ARGV...>
cmd() {
	if test x"$MODE_INSTALL_SH" != xno; then $* 1>&2; else $*; fi || {
		local error=$?
		echo -e "\e[${UI_COLCFG_ERR}mERROR\e[m: Command failed '\e[${UI_COLCFG_NAME}m$*\e[m' -> '\e[${UI_COLCFG_NAME}m$error\e[m'" >&2
		exit $error
	}
}

#>> xcmd <ARGV...>
xcmd() {
	if test x"$MODE_INSTALL_SH" != xno; then $* 1>&2; else $*; fi || {
		local error=$?
		echo -e "\e[${UI_COLCFG_ERR}mERROR\e[m: Command failed '\e[${UI_COLCFG_NAME}m$*\e[m' -> '\e[${UI_COLCFG_NAME}m$error\e[m'" >&2
		return $error
	}
}

#>> vcmd <ARGV...>
vcmd() {
	echo "run: $*" >&2
	if test x"$MODE_INSTALL_SH" != xno; then $* 1>&2; else $*; fi || {
		local error=$?
		echo -e "\e[${UI_COLCFG_ERR}mERROR\e[m: Command failed '\e[${UI_COLCFG_NAME}m$*\e[m' -> '\e[${UI_COLCFG_NAME}m$error\e[m'" >&2
		exit $error
	}
}

#>> vxcmd <ARGV...>
vxcmd() {
	echo "run: $*" >&2
	if test x"$MODE_INSTALL_SH" != xno; then $* 1>&2; else $*; fi || {
		local error=$?
		echo -e "\e[${UI_COLCFG_ERR}mERROR\e[m: Command failed '\e[${UI_COLCFG_NAME}m$*\e[m' -> '\e[${UI_COLCFG_NAME}m$error\e[m'" >&2
		return $error
	}
}

# dirname <PATH>
dirname() {
	echo "${1%/*}"
}


# Print options for recursive calls to make_utility.sh
print_make_utility_options() {
	if test x"$MODE_FORCE_CONF" == xyes; then echo " --force-configure"; fi
	if test x"$MODE_FORCE_MAKE" == xyes; then echo " --force-make"; fi
	if test x"$MODE_FORCE_DISK" == xyes; then echo " --force-disk"; fi
	if test x"$MODE_INSTALL_SH" == xyes; then echo " --install-sh"; fi
	if test x"$MODE_DRYRUN"     == xyes; then echo " --dry-run"; fi
	if test x"$MODE_RECURSIVE"  == xyes; then echo " --recursive"; fi
}

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

	--install-sh)
		MODE_INSTALL_SH=yes
		;;

	--dry-run)
		MODE_DRYRUN=yes
		;;

	-r | --recursive)
		MODE_RECURSIVE=yes
		;;

	*)
		break
		;;
	esac
	shift
done

if (($# != 2)); then
	echo "Usage: ./make_utility.sh [OPTIONS...] <TARGET_NAME> <UTILITY_NAME>"
	echo "OPTIONS:"
	echo "    --force-configure     Force configure to be re-executed"
	echo "    --force-make          Force make to be re-executed"
	echo "    --force-disk          Force on-disk files to be updated"
	echo "    --install-sh          Don't install files, but print a shell-script to install to \$DESTDIR"
	echo "                          3rd party header files still get installed normalled when using this option"
	echo "                          Can be used to install utility to a custom location via:"
	echo "                          > bash make_utility.sh --install-sh i386 busybox | DESTDIR=/mount/kos-drive bash -x"
	echo "                          Or you can just dump the generated scripts somewhere and invoke them manually"
	echo "    --dry-run             Don't install files, but tell what would be installed"
	echo "    -r --recursive        Recursively install missing dependencies"
	echo ""
	echo "TARGET_NAME should be one of:"
	echo "i386 x86_64"
	echo ""
	echo "UTILITY_NAME should be one of:"
	cd "$(dirname $(readlink -f "$0"))/utilities"
	for name in *.sh Xorg/*.sh; do
		echo -n "${name::-3} "
	done
	echo ""
	exit 1
fi

TARGET_NAME="$1"
UTILITY_NAME="$2"
TARGET_CPUNAME="$TARGET_NAME"
TARGET_LIBPATH="lib"
TARGET_INCPATH="$TARGET_CPUNAME-kos"
KOS_MISC="$(dirname "$(readlink -f "$0")")"
KOS_PATCHES="$KOS_MISC/patches"
cmd cd "$KOS_MISC/../../"
KOS_ROOT="$(pwd)"
MTOOLS="$KOS_ROOT/binutils/misc/bin/mtools"

if [ "$TARGET_CPUNAME" == "i386" ]; then
	TARGET_CPUNAME="i686"
	# Because of multi-arch support on x86_64, /bin/i386-kos may be linked to x86_64
	# When we want to build utilities for i386 however, such linkage will result in
	# unexpected errors, so to save on the hassle: check that the symlink is valid.
	_BINDIR_LNK="$(readlink "./bin/i386-kos" 2>&1)"
	if [[ "$_BINDIR_LNK" == *x86_64* ]]; then
		echo -e "\e[${UI_COLCFG_ERR}mERROR\e[m: \e[${UI_COLCFG_NAME}mbin/i386-kos\e[m is linked against x86_64 (specifically: '\e[${UI_COLCFG_NAME}m$_BINDIR_LNK\e[m')" >&2
		echo -e "       Fix this by running '\e[${UI_COLCFG_NAME}mdeemon magic.dee --build-only --target=i386 --config=...\e[m'" >&2
		exit 1
	fi
fi
if [ "$TARGET_CPUNAME" == "x86_64" ]; then
	TARGET_INCPATH="i386-kos"
	TARGET_LIBPATH="lib64"
fi

shortname() {
	if [[ "$1" == "$KOS_ROOT/"* ]]; then
		echo "\$KOS_ROOT${1:${#KOS_ROOT}}"
	else
		echo "$1"
	fi
}

SH=${SH:-bash}
SYSROOT_BIN_TARGET_COMMON="$KOS_ROOT/bin/$TARGET_NAME-kos-common"
SYSROOT_BINUTILS_TARGET="$KOS_ROOT/binutils/$TARGET_NAME-kos"

if ! [ -d "$SYSROOT_BIN_TARGET_COMMON" ]; then
	echo -e "\e[${UI_COLCFG_ERR}mCommon system root is missing\e[m: \e[${UI_COLCFG_NAME}m$(shortname "$SYSROOT_BIN_TARGET_COMMON")\e[m (re-run '\e[${UI_COLCFG_NAME}mmake_toolchain.sh\e[m' to fix)" >&2
	exit 1
fi

# This is the path where PKG_CONFIG utilities load/install their config files
export PKG_CONFIG_LIBDIR="$SYSROOT_BINUTILS_TARGET/opt/pkg_config"
export PKG_CONFIG_PATH="$PKG_CONFIG_LIBDIR"

require_program() {
	which $1 > /dev/null 2>&1 || {
		local error=$?
		echo -e "ERROR: \e[${UI_COLCFG_ERR}mRequired program not found\e[m '\e[${UI_COLCFG_NAME}m$1\e[m' -> '\e[${UI_COLCFG_NAME}m${error}\e[m'" >&2
		echo -e "       Check if this program is installed, and make sure that it's in \$PATH" >&2
		exit $error
	}
}

# require_utility <UTILITY_NAME> <INDICATOR_FILE>
require_utility() {
	if ! [ -f "$2" ]; then
		if test x"$MODE_RECURSIVE" == xyes; then
			echo -e "Required untility not installed: \e[${UI_COLCFG_NAME}m$1\e[m (file '\e[${UI_COLCFG_NAME}m$(shortname "$2")\e[m' does't exist; install automatically)" >&2
			vcmd "$SH" "$KOS_MISC/make_utility.sh" $(print_make_utility_options) "$TARGET_NAME" "$1"
		else
			echo -e "\e[${UI_COLCFG_ERR}mRequired untility not installed\e[m: \e[${UI_COLCFG_NAME}m$1\e[m (file '\e[${UI_COLCFG_NAME}m$(shortname "$2")\e[m' does't exist)" >&2
			echo -e "Resolve this issue by running:" >&2
			echo -e "\$ \e[${UI_COLCFG_NAME}m$SH make_utility.sh $TARGET_NAME $1\e[m" >&2
			exit 1
		fi
	fi
}


#>> mtools_makedir <DISKIMAGE> <ABSOLUTE_DISK_PATH>
mtools_makedir() {
	if ! "$MTOOLS" -c mmd -i "$1" -D s "::/$2" > /dev/null 2>&1; then
		local PARENT="${2%/*}"
		if [ "$PARENT" != "$2" ]; then
			mtools_makedir "$1" "$PARENT"
		fi
		"$MTOOLS" -c mmd -i "$1" -D s "::/$2" > /dev/null 2>&1
	fi
}

#>> mtools_install_file <DISKIMAGE> <ABSOLUTE_DISK_PATH> <SOURCE>
mtools_install_file() {
	if ! "$MTOOLS" -c mcopy -i "$1" -D o "$3" "::/$2" > /dev/null 2>&1; then
		mtools_makedir "$1" "/${2%/*}"
		cmd "$MTOOLS" -c mcopy -i "$1" -D o "$3" "::/$2"
	fi
}

#>> mtools_install_path <DISKIMAGE> <ABSOLUTE_DISK_PATH> <SOURCE>
mtools_install_path() {
	if ! "$MTOOLS" -c mcopy -i "$1" -s -n -D o "$3" "::/$2" > /dev/null 2>&1; then
		mtools_makedir "$1" "/${2%/*}"
		cmd "$MTOOLS" -c mcopy -i "$1" -s -n -D o "$3" "::/$2"
	fi
}

#>> mtools_install_symlink <DISKIMAGE> <ABSOLUTE_DISK_PATH> <LINK_TEXT>
# The installed symlink uses cygwin's old format for symbolic links, that
# is: the ascii-byte-sequence "!<symlink>", followed by the text of the
# link itself, followed by a NUL-byte. Furthermore, the symlink file itself
# must have the FAT SYSTEM file attribute set.
mtools_install_symlink() {
	if ! echo -n -e "!<symlink>$3\0" | "$MTOOLS" -c mcopy -i "$1" -S -s -n -D o /dev/stdin "::/$2" > /dev/null 2>&1; then
		mtools_makedir "$1" "/${2%/*}"
		echo -n -e "!<symlink>$3\0" | "$MTOOLS" -c mcopy -i "$1" -S -s -n -D o /dev/stdin "::/$2" || {
			local error=$?
			echo -e "ERROR: \e[${UI_COLCFG_ERR}mCommand failed\e[m '\e[${UI_COLCFG_NAME}mecho -e !<symlink>$3\0 | $MTOOLS -c mcopy -i $1 -s -n -D o /dev/stdin ::/$2\e[m' -> '\e[${UI_COLCFG_NAME}m${error}\e[m'" >&2
			exit $error
		}
	fi
	# We're using a custom version of mtools, where mcopy accepts an
	# argument "-S" that already does the job of setting the system flag!
#	cmd "$MTOOLS" -c mattrib -i "$1" +S "::/$2"
}


install_sh_print_KOS_ROOT() {
	if test -z "$INSTALL_SH_PRINTED_KOS_ROOT"; then
		printf 'KOS_ROOT="${KOS_ROOT:-%s}"\n' "$KOS_ROOT"
		INSTALL_SH_PRINTED_KOS_ROOT=yes
	fi
}

install_sh_print_SRC_DESTDIR() {
	if test -z "$INSTALL_SH_PRINTED_SRC_DESTDIR"; then
		if [[ "$DESTDIR" == "$KOS_ROOT/"* ]]; then
			install_sh_print_KOS_ROOT
			printf 'SRC_DESTDIR="$KOS_ROOT%s"\n' "${DESTDIR:${#KOS_ROOT}}"
		else
			printf 'SRC_DESTDIR="%s"\n' "$DESTDIR"
		fi
		INSTALL_SH_PRINTED_SRC_DESTDIR=yes
	fi
}


#>> install_sh_raw_mkdir <DIRPATH>
INSTALL_SH_RAW_DIRS=()
install_sh_raw_mkdir() {
	if ! [[ " ${INSTALL_SH_RAW_DIRS[@]} " =~ " ${1} " ]]; then
		REL_DIRPATH="$1"
		if [[ "$1" == "$KOS_ROOT/"* ]]; then
			install_sh_print_KOS_ROOT
			REL_DIRPATH="\$KOS_ROOT${1:${#KOS_ROOT}}"
		fi
		printf '#mkdir -p "%s"\n' "$REL_DIRPATH"
		INSTALL_SH_RAW_DIRS+=("$1")
	fi
}

#>> install_sh_mkdir <DIRPATH>
INSTALL_SH_DIRS=()
install_sh_mkdir() {
	if ! [[ " ${INSTALL_SH_DIRS[@]} " =~ " ${1} " ]] && ! test -z "$1"; then
		printf 'mkdir -p "%s"\n' "\$DESTDIR$1"
		INSTALL_SH_DIRS+=("$1")
	fi
}

#>> install_sh_mkdir_com <DIRPATH>
INSTALL_SH_DIRS_COM=()
install_sh_mkdir_com() {
	if ! [[ " ${INSTALL_SH_DIRS[@]} " =~ " ${1} " ]] && \
	   ! [[ " ${INSTALL_SH_DIRS_COM[@]} " =~ " ${1} " ]] && \
	   ! test -z "$1"; then
		printf '#mkdir -p "%s"\n' "\$DESTDIR$1"
		INSTALL_SH_DIRS_COM+=("$1")
	fi
}

#>> install_rawfile <DEST> <SOURCE>
install_rawfile() {
	if test x"$MODE_DRYRUN" != xno; then
		echo "install_rawfile '$1' '$2'"
		return
	fi
	local SHORTPATH="$1"
	if [[ "$SHORTPATH" == "$KOS_ROOT/"* ]]; then
		SHORTPATH="\$KOS_ROOT${SHORTPATH:${#KOS_ROOT}}"
	fi
	printf "\e[${UI_COLCFG_FILETYPE}mreg\e[m \e[${UI_COLCFG_PATH_RAW}m%-${UI_PATHCOL_WIDTH}s\e[m [raw]" "$SHORTPATH" >&2
	if ! [ -f "$1" ]; then
		if ! cp "$2" "$1" > /dev/null 2>&1; then
			cmd mkdir -p "${1%/*}"
			cmd cp "$2" "$1"
		fi
		echo -e "\e[${UI_COLCFG_OK}m installed\e[m" >&2
	elif [ "$2" -nt "$1" ]; then
		if cmp -s "$1" "$2" > /dev/null 2>&1; then
			# Revert the last-modified timestamp of the source file
			# (since we already installed it with an earlier timestamp)
			touch -r "$1" "$2" > /dev/null 2>&1
			echo -e "\e[${UI_COLCFG_OK}m unchanged\e[m" >&2
		else
			unlink "$1" > /dev/null 2>&1
			if ! cp "$2" "$1" > /dev/null 2>&1; then
				cmd mkdir -p "${1%/*}"
				cmd cp "$2" "$1"
			fi
			echo -e "\e[${UI_COLCFG_OK}m ok\e[m" >&2
		fi
	else
		echo -e "\e[${UI_COLCFG_OK}m already installed\e[m" >&2
	fi
}

#>> install_rawfile_stdin <DEST> <<EOF ... EOF
install_rawfile_stdin() {
	if test x"$MODE_DRYRUN" != xno; then
		echo "install_rawfile_stdin '$1'"
	else
		local SHORTPATH="$1"
		if [[ "$SHORTPATH" == "$KOS_ROOT/"* ]]; then
			SHORTPATH="\$KOS_ROOT${SHORTPATH:${#KOS_ROOT}}"
		fi
		printf "\e[${UI_COLCFG_FILETYPE}mreg\e[m \e[${UI_COLCFG_PATH_RAW}m%-${UI_PATHCOL_WIDTH}s\e[m [raw]" "$SHORTPATH" >&2
		if ! [ -f "$1" ]; then
			cmd mkdir -p "${1%/*}"
			cat > "$1" < /dev/stdin
			echo -e "\e[${UI_COLCFG_OK}m ok\e[m" >&2
		else
			echo -e "\e[${UI_COLCFG_OK}m already installed\e[m" >&2
		fi
	fi
}

load_BUILD_CONFIG_NAMES() {
	if test -z "$BUILD_CONFIG_NAMES"; then
		local OLDPWD="$(pwd)"
		cmd cd "$KOS_ROOT/bin"
		local ALL_BUILD_CONFIG_NAMES=($TARGET_NAME-kos-*)
		cmd cd "$OLDPWD"
		# Remove $TARGET_NAME-kos-common from list of config names
		BUILD_CONFIG_NAMES=()
		for BUILD_CONFIG in "${ALL_BUILD_CONFIG_NAMES[@]}"; do
			if test x"$BUILD_CONFIG" != x"$TARGET_NAME-kos-common"; then
				local CONFIG_SYSROOT="$KOS_ROOT/bin/$BUILD_CONFIG"
				local DISKIMAGE="$CONFIG_SYSROOT/disk.img"
				if [ -f "$DISKIMAGE" ]; then
					BUILD_CONFIG_NAMES+=("$BUILD_CONFIG")
				fi
			fi
		done
	fi
}


#>> install_file <ABSOLUTE_DISK_PATH> <SOURCE>
install_file() {
	if test x"$MODE_INSTALL_SH" != xno; then
		REL_SRC="$2"
		if ! test -z "$DESTDIR" && [[ "$2" == "$DESTDIR/"* ]]; then
			install_sh_print_SRC_DESTDIR
			REL_SRC="\$SRC_DESTDIR${2:${#DESTDIR}}"
		elif [[ "$2" == "$KOS_ROOT/"* ]]; then
			install_sh_print_KOS_ROOT
			REL_SRC="\$KOS_ROOT${2:${#KOS_ROOT}}"
		fi
		install_sh_mkdir "${1%/*}"
		printf 'cp "%s" "$DESTDIR%s"\n' "$REL_SRC" "$1"
	elif test x"$MODE_DRYRUN" != xno; then
		echo "install_file '$1' '$2'"
	else
		local DISPATH="${1#/}"
		local TARGET_COMMON_DISPATH="$SYSROOT_BIN_TARGET_COMMON/$DISPATH"
		local DIDUPDATE="no"
		printf "\e[${UI_COLCFG_FILETYPE}mreg\e[m \e[${UI_COLCFG_PATH_DISK}m%-${UI_PATHCOL_WIDTH}s\e[m [disk]" "\$DESTDIR/$DISPATH" >&2
		if ! [ -f "$TARGET_COMMON_DISPATH" ] || [ "$2" -nt "$TARGET_COMMON_DISPATH" ]; then
			unlink "$TARGET_COMMON_DISPATH" > /dev/null 2>&1
			echo -n " common" >&2
			if ! cp "$2" "$TARGET_COMMON_DISPATH" > /dev/null 2>&1; then
				cmd mkdir -p "${TARGET_COMMON_DISPATH%/*}"
				cmd cp "$2" "$TARGET_COMMON_DISPATH"
			fi
			DIDUPDATE="yes"
		fi
		load_BUILD_CONFIG_NAMES
		for BUILD_CONFIG in "${BUILD_CONFIG_NAMES[@]}"; do
			local CONFIG_SYSROOT="$KOS_ROOT/bin/$BUILD_CONFIG"
			local CONFIG_DISPATH="$CONFIG_SYSROOT/$DISPATH"
			local DISKIMAGE="$CONFIG_SYSROOT/disk.img"
			echo -n " ${BUILD_CONFIG:${#TARGET_NAME}+5}" >&2
			if test x"$DIDUPDATE" == xyes || ! [ -f "$CONFIG_DISPATH" ] || \
			   [ "$TARGET_COMMON_DISPATH" -nt "$CONFIG_DISPATH" ]; then
				unlink "$CONFIG_DISPATH" > /dev/null 2>&1
				echo -n ":disk" >&2
				mtools_install_file "$DISKIMAGE" "$DISPATH" "$2"
				echo -n ":bin" >&2
				if ! ln -r -s "$TARGET_COMMON_DISPATH" "$CONFIG_DISPATH" > /dev/null 2>&1; then
					cmd mkdir -p "${CONFIG_DISPATH%/*}"
					cmd ln -r -s "$TARGET_COMMON_DISPATH" "$CONFIG_DISPATH"
				fi
			else
				if [ "$MODE_FORCE_DISK" == "yes" ]; then
					echo -n ":disk" >&2
					mtools_install_file "$DISKIMAGE" "$DISPATH" "$2"
				fi
			fi
		done
		echo -e "\e[${UI_COLCFG_OK}m ok\e[m" >&2
	fi
}


#>> install_file_nodisk <ABSOLUTE_DISK_PATH> <SOURCE>
install_file_nodisk() {
	if test x"$MODE_INSTALL_SH" != xno; then
		REL_SRC="$2"
		if ! test -z "$DESTDIR" && [[ "$2" == "$DESTDIR/"* ]]; then
			install_sh_print_SRC_DESTDIR
			REL_SRC="\$SRC_DESTDIR${2:${#DESTDIR}}"
		elif [[ "$2" == "$KOS_ROOT/"* ]]; then
			install_sh_print_KOS_ROOT
			REL_SRC="\$KOS_ROOT${2:${#KOS_ROOT}}"
		fi
		install_sh_mkdir_com "${1%/*}"
		printf '#cp "%s" "$DESTDIR%s"\n' "$REL_SRC" "$1"
	elif test x"$MODE_DRYRUN" != xno; then
		echo "> install_file_nodisk '$1' '$2'"
	else
		local DISPATH="${1#/}"
		local TARGET_COMMON_DISPATH="$SYSROOT_BIN_TARGET_COMMON/$DISPATH"
		local DIDUPDATE="no"
		printf "\e[${UI_COLCFG_FILETYPE}mreg\e[m \e[${UI_COLCFG_PATH_NODISK}m%-${UI_PATHCOL_WIDTH}s\e[m [nodisk]" "\$DESTDIR/$DISPATH" >&2
		if ! [ -f "$TARGET_COMMON_DISPATH" ] || [ "$TARGET_COMMON_DISPATH" -ot "$2" ]; then
			unlink "$TARGET_COMMON_DISPATH" > /dev/null 2>&1
			echo -n " common" >&2
			if ! cp "$2" "$TARGET_COMMON_DISPATH" > /dev/null 2>&1; then
				cmd mkdir -p "${TARGET_COMMON_DISPATH%/*}"
				cmd cp "$2" "$TARGET_COMMON_DISPATH"
			fi
			DIDUPDATE="yes"
		fi
		load_BUILD_CONFIG_NAMES
		for BUILD_CONFIG in "${BUILD_CONFIG_NAMES[@]}"; do
			local CONFIG_SYSROOT="$KOS_ROOT/bin/$BUILD_CONFIG"
			local CONFIG_DISPATH="$CONFIG_SYSROOT/$DISPATH"
			echo -n " ${BUILD_CONFIG:${#TARGET_NAME}+5}" >&2
			if test x"$DIDUPDATE" == xyes || ! [ -e "$CONFIG_DISPATH" ]; then
				unlink "$CONFIG_DISPATH" > /dev/null 2>&1
				echo -n ":bin" >&2
				if ! ln -r -s "$TARGET_COMMON_DISPATH" "$CONFIG_DISPATH" > /dev/null 2>&1; then
					cmd mkdir -p "${CONFIG_DISPATH%/*}"
					cmd ln -r -s "$TARGET_COMMON_DISPATH" "$CONFIG_DISPATH"
				fi
			fi
		done
		echo -e "\e[${UI_COLCFG_OK}m ok\e[m" >&2
	fi
}


#>> install_symlink <ABSOLUTE_DISK_PATH> <TEXT>
install_symlink() {
	if test x"$MODE_INSTALL_SH" != xno; then
		install_sh_mkdir "${1%/*}"
		printf 'ln -s "%s" "$DESTDIR%s"\n' "$2" "$1"
	elif test x"$MODE_DRYRUN" != xno; then
		echo "install_symlink '$1' '$2'"
	else
		local DISPATH="${1#/}"
		local TARGET_COMMON_DISPATH="$SYSROOT_BIN_TARGET_COMMON/$DISPATH"
		local DIDUPDATE="no"
		local HOST_LINKTEXT="$2"
		printf "\e[${UI_COLCFG_FILETYPE}mlnk\e[m \e[${UI_COLCFG_PATH_DISK}m%-${UI_PATHCOL_WIDTH}s\e[m [disk]" "\$DESTDIR/$DISPATH" >&2
		if [[ "$2" == "/"* ]]; then
			HOST_LINKTEXT="$SYSROOT_BIN_TARGET_COMMON$2"
		fi
		if ! [ -L "$TARGET_COMMON_DISPATH" ]; then
			unlink "$TARGET_COMMON_DISPATH" > /dev/null 2>&1
			echo -n " common" >&2
			if ! ln -s "$HOST_LINKTEXT" "$TARGET_COMMON_DISPATH" > /dev/null 2>&1; then
				cmd mkdir -p "${TARGET_COMMON_DISPATH%/*}"
				cmd ln -s "$HOST_LINKTEXT" "$TARGET_COMMON_DISPATH"
			fi
			DIDUPDATE="yes"
		fi
		load_BUILD_CONFIG_NAMES
		for BUILD_CONFIG in "${BUILD_CONFIG_NAMES[@]}"; do
			local CONFIG_SYSROOT="$KOS_ROOT/bin/$BUILD_CONFIG"
			local CONFIG_DISPATH="$CONFIG_SYSROOT/$DISPATH"
			local DISKIMAGE="$CONFIG_SYSROOT/disk.img"
			echo -n " ${BUILD_CONFIG:${#TARGET_NAME}+5}" >&2
			if test x"$DIDUPDATE" == xyes || ! [ -L "$CONFIG_DISPATH" ]; then
				unlink "$CONFIG_DISPATH" > /dev/null 2>&1
				echo -n ":disk" >&2
				mtools_install_symlink "$DISKIMAGE" "$DISPATH" "$2"
				echo -n ":bin" >&2
				if ! ln -r -s "$TARGET_COMMON_DISPATH" "$CONFIG_DISPATH" > /dev/null 2>&1; then
					cmd mkdir -p "${CONFIG_DISPATH%/*}"
					cmd ln -r -s "$TARGET_COMMON_DISPATH" "$CONFIG_DISPATH"
				fi
			else
				if [ "$MODE_FORCE_DISK" == "yes" ]; then
					echo -n ":disk" >&2
					mtools_install_symlink "$DISKIMAGE" "$DISPATH" "$2"
				fi
			fi
		done
		echo -e "\e[${UI_COLCFG_OK}m ok\e[m" >&2
	fi
}

#>> install_symlink_nodisk <ABSOLUTE_DISK_PATH> <TEXT>
install_symlink_nodisk() {
	if test x"$MODE_INSTALL_SH" != xno; then
		install_sh_mkdir_com "${1%/*}"
		printf '#ln -s "%s" "$DESTDIR%s"\n' "$2" "$1"
	elif test x"$MODE_DRYRUN" != xno; then
		echo "> install_symlink_nodisk '$1' '$2'"
	else
		local DISPATH="${1#/}"
		local TARGET_COMMON_DISPATH="$SYSROOT_BIN_TARGET_COMMON/$DISPATH"
		local DIDUPDATE="no"
		printf "\e[${UI_COLCFG_FILETYPE}mlnk\e[m \e[${UI_COLCFG_PATH_NODISK}m%-${UI_PATHCOL_WIDTH}s\e[m [nodisk]" "\$DESTDIR/$DISPATH" >&2
		if ! [ -f "$TARGET_COMMON_DISPATH" ] || \
		     [ "$(readlink "$TARGET_COMMON_DISPATH")" != "$2" ]; then
			unlink "$TARGET_COMMON_DISPATH" > /dev/null 2>&1
			echo -n " common" >&2
			if ! ln -s "$2" "$TARGET_COMMON_DISPATH" > /dev/null 2>&1; then
				cmd mkdir -p "${TARGET_COMMON_DISPATH%/*}"
				cmd ln -s "$2" "$TARGET_COMMON_DISPATH"
			fi
			DIDUPDATE="yes"
		fi
		load_BUILD_CONFIG_NAMES
		for BUILD_CONFIG in "${BUILD_CONFIG_NAMES[@]}"; do
			local CONFIG_SYSROOT="$KOS_ROOT/bin/$BUILD_CONFIG"
			local CONFIG_DISPATH="$CONFIG_SYSROOT/$DISPATH"
			echo -n " ${BUILD_CONFIG:${#TARGET_NAME}+5}" >&2
			if test x"$DIDUPDATE" == xyes || ! [ -f "$CONFIG_DISPATH" ]; then
				unlink "$CONFIG_DISPATH" > /dev/null 2>&1
				echo -n ":bin" >&2
				if ! ln -r -s "$TARGET_COMMON_DISPATH" "$CONFIG_DISPATH" > /dev/null 2>&1; then
					cmd mkdir -p "${CONFIG_DISPATH%/*}"
					cmd ln -r -s "$TARGET_COMMON_DISPATH" "$CONFIG_DISPATH"
				fi
			fi
		done
		echo -e "\e[${UI_COLCFG_OK}m ok\e[m" >&2
	fi
}

#>> install_mkdir <ABSOLUTE_DISK_PATH>
install_mkdir() {
	if test x"$MODE_INSTALL_SH" != xno; then
		install_sh_mkdir "$1"
	elif test x"$MODE_DRYRUN" != xno; then
		echo "> install_mkdir '$1'"
	else
		local DISPATH="${1#/}"
		local TARGET_COMMON_DISPATH="$SYSROOT_BIN_TARGET_COMMON/$DISPATH"
		local DIDUPDATE="no"
		printf "\e[${UI_COLCFG_FILETYPE}mdir\e[m \e[${UI_COLCFG_PATH_DISK}m%-${UI_PATHCOL_WIDTH}s\e[m [disk]" "\$DESTDIR/$DISPATH" >&2
		if ! [ -d "$TARGET_COMMON_DISPATH" ]; then
			echo -n " common" >&2
			cmd mkdir -p "$TARGET_COMMON_DISPATH"
			DIDUPDATE="yes"
		fi
		load_BUILD_CONFIG_NAMES
		for BUILD_CONFIG in "${BUILD_CONFIG_NAMES[@]}"; do
			local CONFIG_SYSROOT="$KOS_ROOT/bin/$BUILD_CONFIG"
			local CONFIG_DISPATH="$CONFIG_SYSROOT/$DISPATH"
			local DISKIMAGE="$CONFIG_SYSROOT/disk.img"
			echo -n " ${BUILD_CONFIG:${#TARGET_NAME}+5}" >&2
			if test x"$DIDUPDATE" == xyes || ! [ -d "$CONFIG_DISPATH" ]; then
				echo -n ":disk" >&2
				mtools_makedir "$DISKIMAGE" "$DISPATH"
				echo -n ":bin" >&2
				cmd mkdir -p "$CONFIG_DISPATH"
			else
				if [ "$MODE_FORCE_DISK" == "yes" ]; then
					echo -n ":disk" >&2
					mtools_makedir "$DISKIMAGE" "$DISPATH"
				fi
			fi
		done
		echo -e "\e[${UI_COLCFG_OK}m ok\e[m" >&2
	fi
}

#>> install_path <ABSOLUTE_DISK_PATH> <SOURCE>
install_path() {
	if test x"$MODE_INSTALL_SH" != xno; then
		REL_SRC="$2"
		if ! test -z "$DESTDIR" && [[ "$2" == "$DESTDIR/"* ]]; then
			install_sh_print_SRC_DESTDIR
			REL_SRC="\$SRC_DESTDIR${2:${#DESTDIR}}"
		elif [[ "$2" == "$KOS_ROOT/"* ]]; then
			install_sh_print_KOS_ROOT
			REL_SRC="\$KOS_ROOT${2:${#KOS_ROOT}}"
		fi
		install_sh_mkdir "${1%/*}"
		printf 'cp -R "%s" "$DESTDIR%s"\n' "$REL_SRC" "$1"
	elif test x"$MODE_DRYRUN" != xno; then
		echo "> install_path '$1' '$2'"
	else
		local DISPATH="${1#/}"
		local TARGET_COMMON_DISPATH="$SYSROOT_BIN_TARGET_COMMON/$DISPATH"
		local DIDUPDATE="no"
		printf "\e[${UI_COLCFG_FILETYPE}m...\e[m \e[${UI_COLCFG_PATH_DISK}m%-${UI_PATHCOL_WIDTH}s\e[m [disk]" "\$DESTDIR/$DISPATH/*" >&2
		if ! [ -L "$TARGET_COMMON_DISPATH" ]; then
			unlink "$TARGET_COMMON_DISPATH" > /dev/null 2>&1
			echo -n " common" >&2
			if ! ln -r -s "$2" "$TARGET_COMMON_DISPATH" > /dev/null 2>&1; then
				cmd mkdir -p "${TARGET_COMMON_DISPATH%/*}"
				cmd ln -r -s "$2" "$TARGET_COMMON_DISPATH"
			fi
			DIDUPDATE="yes"
		fi
		load_BUILD_CONFIG_NAMES
		for BUILD_CONFIG in "${BUILD_CONFIG_NAMES[@]}"; do
			local CONFIG_SYSROOT="$KOS_ROOT/bin/$BUILD_CONFIG"
			local CONFIG_DISPATH="$CONFIG_SYSROOT/$DISPATH"
			local DISKIMAGE="$CONFIG_SYSROOT/disk.img"
			echo -n " ${BUILD_CONFIG:${#TARGET_NAME}+5}" >&2
			if test x"$DIDUPDATE" == xyes || ! [ -L "$CONFIG_DISPATH" ]; then
				unlink "$CONFIG_DISPATH" > /dev/null 2>&1
				echo -n ":disk" >&2
				mtools_install_path "$DISKIMAGE" "$DISPATH" "$2"
				echo -n ":bin" >&2
				if ! ln -r -s "$TARGET_COMMON_DISPATH" "$CONFIG_DISPATH" > /dev/null 2>&1; then
					cmd mkdir -p "${CONFIG_DISPATH%/*}"
					cmd ln -r -s "$TARGET_COMMON_DISPATH" "$CONFIG_DISPATH"
				fi
			else
				if [ "$MODE_FORCE_DISK" == "yes" ]; then
					echo -n ":disk" >&2
					mtools_install_path "$DISKIMAGE" "$DISPATH" "$2"
				fi
			fi
		done
		echo -e "\e[${UI_COLCFG_OK}m ok\e[m" >&2
	fi
}

#>> install_path_hardcopy <ABSOLUTE_DISK_PATH> <SOURCE>
install_path_hardcopy() {
	if test x"$MODE_INSTALL_SH" != xno; then
		REL_SRC="$2"
		if ! test -z "$DESTDIR" && [[ "$2" == "$DESTDIR/"* ]]; then
			install_sh_print_SRC_DESTDIR
			REL_SRC="\$SRC_DESTDIR${2:${#DESTDIR}}"
		elif [[ "$2" == "$KOS_ROOT/"* ]]; then
			install_sh_print_KOS_ROOT
			REL_SRC="\$KOS_ROOT${2:${#KOS_ROOT}}"
		fi
		install_sh_mkdir "${1%/*}"
		printf 'cp -R "%s" "$DESTDIR%s"\n' "$REL_SRC" "$1"
	elif test x"$MODE_DRYRUN" != xno; then
		echo "> install_path_hardcopy '$1' '$2'"
	else
		local DISPATH="${1#/}"
		local TARGET_COMMON_DISPATH="$SYSROOT_BIN_TARGET_COMMON/$DISPATH"
		local DIDUPDATE="no"
		printf "\e[${UI_COLCFG_FILETYPE}m...\e[m \e[${UI_COLCFG_PATH_DISK}m%-${UI_PATHCOL_WIDTH}s\e[m [disk]" "\$DESTDIR/$DISPATH/*" >&2
		if true; then
			unlink "$TARGET_COMMON_DISPATH" > /dev/null 2>&1
			echo -n " common" >&2
			cmd mkdir -p "${TARGET_COMMON_DISPATH%/*}"
			cmd cp -R -n "$2" "$TARGET_COMMON_DISPATH"
			DIDUPDATE="yes"
		fi
		load_BUILD_CONFIG_NAMES
		for BUILD_CONFIG in "${BUILD_CONFIG_NAMES[@]}"; do
			local CONFIG_SYSROOT="$KOS_ROOT/bin/$BUILD_CONFIG"
			local CONFIG_DISPATH="$CONFIG_SYSROOT/$DISPATH"
			local DISKIMAGE="$CONFIG_SYSROOT/disk.img"
			echo -n " ${BUILD_CONFIG:${#TARGET_NAME}+5}" >&2
			if test x"$DIDUPDATE" == xyes || ! [ -L "$CONFIG_DISPATH" ]; then
				unlink "$CONFIG_DISPATH" > /dev/null 2>&1
				echo -n ":disk" >&2
				mtools_install_path "$DISKIMAGE" "$DISPATH" "$2"
				echo -n ":bin" >&2
				if ! ln -r -s "$TARGET_COMMON_DISPATH" "$CONFIG_DISPATH" > /dev/null 2>&1; then
					cmd mkdir -p "${CONFIG_DISPATH%/*}"
					cmd ln -r -s "$TARGET_COMMON_DISPATH" "$CONFIG_DISPATH"
				fi
			else
				if [ "$MODE_FORCE_DISK" == "yes" ]; then
					echo -n ":disk" >&2
					mtools_install_path "$DISKIMAGE" "$DISPATH" "$2"
				fi
			fi
		done
		echo -e "\e[${UI_COLCFG_OK}m ok\e[m" >&2
	fi
}

#>> rundeemon <ARGS...>
# Invoke `deemon $*`
rundeemon() {
	"$KOS_ROOT/binutils/deemon/deemon" "${*[@]}"
	return $?
}


#>> download_file  <DST_FILE>  <URL>
download_file() {
	if ! [ -f "$1" ]; then
		echo -e "\e[${UI_COLCFG_ACTION}mdownload\e[m: \e[${UI_COLCFG_NAME}m$2\e[m" >&2
		local OLDPWD="$(pwd)"
		local DIR="${1%/*}"
		cmd mkdir -p "$DIR"
		cmd cd "$DIR"
		cmd wget "$2"
		cmd cd "$OLDPWD"
		if ! [ -f "$1" ]; then
			echo -e "Missing file \e[${UI_COLCFG_ERR}m$1\e[m" >&2
			exit 1
		fi
	fi
}

#>> apply_patch  <DST_PATH>  <PATCH_FILE>
apply_patch() {
	if ! [ -f "$1/.kos_patched" ]; then
		echo -e "\e[${UI_COLCFG_ACTION}mpatch\e[m: \e[${UI_COLCFG_NAME}m$(shortname "$1")\e[m (\e[${UI_COLCFG_NAME}m$(shortname "$2")\e[m)" >&2
		cmd patch -d "$1" -p1 < "$2"
		> "$1/.kos_patched"
	fi
}

#>> set_archpath
# Set $PATH to include target toolchain utilities.
set_archpath() {
	export PATH="$SYSROOT_BINUTILS_TARGET/bin:$PATH"
	export CC="${CROSS_PREFIX}gcc"
	export CFLAGS="-ggdb"
	export CXX="${CROSS_PREFIX}g++"
	export CXXFLAGS="-ggdb"
	export CPP="${CROSS_PREFIX}cpp"
	export CXXCPP="${CROSS_PREFIX}cpp"
	export NM="${CROSS_PREFIX}nm"
	export LD="${CROSS_PREFIX}ld"
	export OBJCOPY="${CROSS_PREFIX}objcopy"
	export OBJDUMP="${CROSS_PREFIX}objdump"
	export READELF="${CROSS_PREFIX}readelf"
#	export SIZE="${CROSS_PREFIX}size"
	export STRIP="${CROSS_PREFIX}strip"
	export AR="${CROSS_PREFIX}ar"
}


# Configure some utilities for general-purpose cross-compiling
export CROSS_TARGET="$TARGET_NAME-elf"
export CROSS_PREFIX="$KOS_ROOT/binutils/$TARGET_NAME-kos/bin/$TARGET_CPUNAME-kos-"
export CROSS_COMPILE="$CROSS_PREFIX"
MAKE_PARALLEL_COUNT=$(grep -c ^processor /proc/cpuinfo)
HOST_SYSROOT="$KOS_ROOT/binutils/misc"

# Old-style config programs (like `pcre-config'), are put in this folder
BINUTILS_CONFIG_BIN="$SYSROOT_BINUTILS_TARGET/config-bin"
export PATH="$BINUTILS_CONFIG_BIN:$PATH"


# Handle the case where the utility name contains a "*"
case "$UTILITY_NAME" in
*\**)
	RARGS="$(print_make_utility_options) $TARGET_NAME"
	cmd cd "$KOS_ROOT/kos/misc/utilities"
	for util in $UTILITY_NAME; do
		if [[ "$util" == *".sh" ]] && [ -f "$util" ]; then
			util="${util::-3}"
			echo -e "\e[${UI_COLCFG_ACTION}mmake\e[m: \e[${UI_COLCFG_NAME}m$util\e[m" >&2
			cmd "$SH" "$KOS_MISC/make_utility.sh" $RARGS "$util"
		fi
	done
	exit 0
	;;
*)
	;;
esac

UTILITY_SCRIPT="$KOS_ROOT/kos/misc/utilities/$UTILITY_NAME.sh"
if ! [ -f "$UTILITY_SCRIPT" ]; then
	echo -e "Unknown utility \e[${UI_COLCFG_ERR}m$UTILITY_NAME\e[m" >&2
	exit 1
fi

# Include the utility-specific build-script as an inlined shell script here
. "$UTILITY_SCRIPT"
