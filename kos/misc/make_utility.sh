#!/bin/bash


cmd() {
	$* || {
		local error=$?
		echo "ERROR: Command failed '$*' -> '$error'"
		exit $error
	}
}

MODE_FORCE_CONF=no
MODE_FORCE_MAKE=no

while [[ $# -gt 0 ]]; do
	case $1 in

	--force-configure)
		MODE_FORCE_CONF=yes
		;;

	--force-make)
		MODE_FORCE_MAKE=yes
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
	echo "    TARGET_NAME should be one of:"
	echo "        i386"
	echo "        x86_64"
	echo "    For a list of valid UTILITY_NAME, review the switch at the bottom of this file"
	exit 1
fi

TARGET_NAME="$1"
UTILITY_NAME="$2"
TARGET_CPUNAME="$TARGET_NAME"
TARGET_LIBPATH="lib"
if [ "$TARGET_CPUNAME" == "i386" ]; then
	TARGET_CPUNAME="i686"
fi
if [ "$TARGET_CPUNAME" == "x86_64" ]; then
	TARGET_LIBPATH="lib64"
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

## install_symlink <ABSOLUTE_DISK_PATH> <TEXT>
install_symlink() {
	DISPATH="${1#/}"
	unlink "$TARGET_SYSROOT/$DISPATH" > /dev/null 2>&1
	echo "Installing ${TARGET_NAME}-kos:/$DISPATH"
	if ! ln -s "$2" "$TARGET_SYSROOT/$DISPATH" > /dev/null 2>&1; then
		cmd mkdir -p "$(dirname "$TARGET_SYSROOT/$DISPATH")"
		cmd ln -s "$2" "$TARGET_SYSROOT/$DISPATH"
	fi
	local RELPATH=$(python -c "import os.path; print os.path.relpath('/${TARGET_NAME}-kos-common/$1', '/foo/$(dirname "/$1")')")
	for BUILD_CONFIG in $(echo $KOS_VALID_BUILD_CONFIGS); do
		local CONFIG_SYSROOT="${KOS_ROOT}/bin/${TARGET_NAME}-kos-${BUILD_CONFIG}"
		unlink "$CONFIG_SYSROOT/$DISPATH" > /dev/null 2>&1
		if ! ln -s "$RELPATH" "$CONFIG_SYSROOT/$DISPATH" > /dev/null 2>&1; then
			cmd mkdir -p "$(dirname "$CONFIG_SYSROOT/$DISPATH")"
			cmd ln -s "$RELPATH" "$CONFIG_SYSROOT/$DISPATH"
		fi
	done
}

## install_file_nodisk <ABSOLUTE_DISK_PATH> <SOURCE>
install_file_nodisk() {
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
		if [ "$(readlink -f "$CONFIG_SYSROOT/$DISPATH")" != \
		     "$(readlink -f "$TARGET_SYSROOT/$DISPATH")" ]; then
			unlink "$CONFIG_SYSROOT/$DISPATH" > /dev/null 2>&1
			if ! ln -s "$RELPATH" "$CONFIG_SYSROOT/$DISPATH" > /dev/null 2>&1; then
				cmd mkdir -p "$(dirname "$CONFIG_SYSROOT/$DISPATH")"
				cmd ln -s "$RELPATH" "$CONFIG_SYSROOT/$DISPATH"
			fi
		fi
		if [ -f "$CONFIG_SYSROOT/disk.img" ]; then
			echo "    Disk: '$CONFIG_SYSROOT/disk.img'"
			mtools_install_path "$CONFIG_SYSROOT/disk.img" "$DISPATH" "$2"
		fi
	done
}

## install_path_hardcopy <ABSOLUTE_DISK_PATH> <SOURCE>
install_path_hardcopy() {
	DISPATH="${1#/}"
	echo "Installing ${TARGET_NAME}-kos:/$DISPATH/*"
	cmd mkdir -p "$(dirname "$TARGET_SYSROOT/$DISPATH")"
	unlink "$TARGET_SYSROOT/$DISPATH" > /dev/null 2>&1
	cmd cp -R "$2" "$TARGET_SYSROOT/$DISPATH"
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

# Invoke `deemon $*`
rundeemon() {
	if which deemon > /dev/null 2>&1; then
		deemon $*
	else
		"${KOS_ROOT}/binutils/deemon/deemon" $*
	fi
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
	all)
		OPTS=""
		if [ "$MODE_FORCE_CONF" == yes ]; then OPTS="$OPTS --force-configure"; fi
		if [ "$MODE_FORCE_MAKE" == yes ]; then OPTS="$OPTS --force-make"; fi
		cmd bash "$KOS_MISC/make_utility.sh" $OPTS "$TARGET_NAME" busybox
		cmd bash "$KOS_MISC/make_utility.sh" $OPTS "$TARGET_NAME" fonts
		cmd bash "$KOS_MISC/make_utility.sh" $OPTS "$TARGET_NAME" vitetris
		cmd bash "$KOS_MISC/make_utility.sh" $OPTS "$TARGET_NAME" tcc
		cmd bash "$KOS_MISC/make_utility.sh" $OPTS "$TARGET_NAME" ncurses
		cmd bash "$KOS_MISC/make_utility.sh" $OPTS "$TARGET_NAME" nano
		cmd bash "$KOS_MISC/make_utility.sh" $OPTS "$TARGET_NAME" zlib
		cmd bash "$KOS_MISC/make_utility.sh" $OPTS "$TARGET_NAME" deemon
		cmd bash "$KOS_MISC/make_utility.sh" $OPTS "$TARGET_NAME" python
		cmd bash "$KOS_MISC/make_utility.sh" $OPTS "$TARGET_NAME" kos-headers
		cmd bash "$KOS_MISC/make_utility.sh" $OPTS "$TARGET_NAME" tty-solitaire
		;;
##############################################################################


##############################################################################
	busybox | busybox-1.31.0)
		BUSYBOX_VERISON="1.31.0"
		## Check final output binary
		OPTPATH="$BINUTILS_SYSROOT/opt/busybox-$BUSYBOX_VERISON"
		SRCPATH="$KOS_ROOT/binutils/src/busybox-$BUSYBOX_VERISON"
		if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "${OPTPATH}/busybox_unstripped" ]; then
			## Check arch makefile
			if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "${OPTPATH}/Makefile" ]; then
				## Check shared (original) makefile
				if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "${SRCPATH}/Makefile" ]; then
					cmd cd "$KOS_ROOT/binutils/src"
					download_file \
						"busybox-$BUSYBOX_VERISON.tar.bz2" \
						https://www.busybox.net/downloads/busybox-$BUSYBOX_VERISON.tar.bz2
					cmd tar jxvf "busybox-$BUSYBOX_VERISON.tar.bz2"
				fi
				if [ -d "${OPTPATH}" ]; then
					cmd rm -rf "${OPTPATH}"
				fi
				cmd cp -R "${SRCPATH}" "$BINUTILS_SYSROOT/opt/"
			fi
			apply_patch "${OPTPATH}" "$KOS_PATCHES/busybox-$BUSYBOX_VERISON.patch"
			cmd cd "${OPTPATH}"
			PATCH_CONFIG="$KOS_PATCHES/busybox.config"
			if ! [ -f ".config" ] || [ ".config" -ot "$PATCH_CONFIG" ]; then
				unlink ".config" > /dev/null 2>&1
				cmd cp "$KOS_PATCHES/busybox.config" ".config"
			fi
			cmd make -j $MAKE_PARALLEL_COUNT CROSS_COMPILE="$CROSS_PREFIX"
		fi
		# Install busybox in KOS
		install_file /bin/busybox "${OPTPATH}/busybox_unstripped"
		;;
##############################################################################


##############################################################################
	fonts)
		# Build and install KOS graphics mode fonts
		cd "$KOS_ROOT"
		rundeemon "kos/misc/fonts/tlft/build_u_vga16.dee"
		install_file /lib/fonts/u_vga16 "$KOS_MISC/fonts/tlft/u_vga16"
		;;
##############################################################################


##############################################################################
	vitetris | vitetris-0.58.0)
		VITETRIS_VERISON="0.58.0"
		SRCPATH="$KOS_ROOT/binutils/src/vitetris-$VITETRIS_VERISON"
		OPTPATH="$BINUTILS_SYSROOT/opt/vitetris-$VITETRIS_VERISON"
		if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/tetris" ]; then
			set_archpath
			if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/configure" ]; then
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
		if [ "$MODE_FORCE_MAKE" == yes ] || \
		   [ "$MODE_FORCE_CONF" == yes ] || ! \
		   [ -f "$OPTPATH/$TARGET_NAME-tcc" ]; then
			set_archpath
			if ! [ -f "$SRCPATH/configure" ]; then
				cmd cd "$KOS_ROOT/binutils/src"
				download_file \
					"tcc-$TCC_VERISON.tar.bz2" \
					http://download.savannah.gnu.org/releases/tinycc/tcc-$TCC_VERISON.tar.bz2
				cmd tar jxvf "tcc-$TCC_VERISON.tar.bz2"
			fi
			rm -rf "$OPTPATH" > /dev/null 2>&1
			cmd cp -R "$SRCPATH" "$BINUTILS_SYSROOT/opt/"
			cmd cd "$OPTPATH"
			apply_patch "$OPTPATH" "$KOS_PATCHES/tcc-$TCC_VERISON.patch"
			cmd bash configure \
				--with-libgcc \
				--with-selinux \
				--cpu="$TARGET_NAME" \
				--enable-cross \
				--cross-prefix="$CROSS_PREFIX" \
				--bindir="/bin" \
				--includedir="/usr/include" \
				--sysincludepaths="/usr/include/${TARGET_NAME}-kos:/usr/include" \
				--libpaths="/usr/$TARGET_LIBPATH:/$TARGET_LIBPATH" \
				--crtprefix="/usr/$TARGET_LIBPATH" \
				--elfinterp="/$TARGET_LIBPATH/libdl.so" \
				--config-mingw32=no
			echo 'NATIVE_DEFINES+=-DTCC_TARGET_KOS="1"' >> config.mak
			echo "NATIVE_DEFINES+=-DCONFIG_TCCDIR=\"\\\"/usr/$TARGET_LIBPATH\\\"\"" >> config.mak
			echo "NATIVE_DEFINES+=-DCONFIG_LDDIR=\"\\\"$TARGET_LIBPATH\\\"\"" >> config.mak
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
		install_file /usr/$TARGET_LIBPATH/$TARGET_NAME-libtcc1.a "$OPTPATH/$TARGET_NAME-libtcc1.a"
		install_file /usr/$TARGET_LIBPATH/crt0S.o "${KOS_ROOT}/bin/${TARGET_NAME}-kos/$TARGET_LIBPATH/crt0S.o"
		install_file /usr/$TARGET_LIBPATH/crt0.o "${KOS_ROOT}/bin/${TARGET_NAME}-kos/$TARGET_LIBPATH/crt0.o"
		install_file /usr/src/hello-world.c "$OPTPATH/hello-world.c"
		;;
##############################################################################


##############################################################################
	kos-headers | kos-headers-400)
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


##############################################################################
	ncurses | ncurses-6.1)
		NCURSES_VERISON_MAJOR="6"
		NCURSES_VERISON="$NCURSES_VERISON_MAJOR.1"
		SRCPATH="$KOS_ROOT/binutils/src/ncurses-$NCURSES_VERISON"
		OPTPATH="$BINUTILS_SYSROOT/opt/ncurses-$NCURSES_VERISON"
		if [ "$MODE_FORCE_MAKE" == yes ] || \
		 ! [ -f "$OPTPATH/lib/libncursesw.so" ]; then
			if [ "$MODE_FORCE_CONF" == yes ] || \
			 ! [ -f "$OPTPATH/Makefile" ]; then
				if ! [ -f "$SRCPATH/configure" ]; then
					cmd cd "$KOS_ROOT/binutils/src"
					download_file \
						"ncurses-$NCURSES_VERISON.tar.gz" \
						ftp://ftp.gnu.org/gnu/ncurses/ncurses-$NCURSES_VERISON.tar.gz
					cmd tar xvf "ncurses-$NCURSES_VERISON.tar.gz"
				fi
				rm -rf "$OPTPATH" > /dev/null 2>&1
				cmd mkdir -p "$OPTPATH"
				cmd cd "$OPTPATH"
				export CC="${CROSS_PREFIX}gcc"
				export CPP="${CROSS_PREFIX}cpp"
				export CXX="${CROSS_PREFIX}g++"
				export CFLAGS="-ggdb"
				export CXXFLAGS="-ggdb"
				cmd bash ../../../src/ncurses-$NCURSES_VERISON/configure \
					--bindir="/bin" \
					--datarootdir="/usr/share" \
					--datadir="/usr/share" \
					--sysconfdir="/etc" \
					--localstatedir="/var" \
					--libdir="/usr/$TARGET_LIBPATH" \
					--includedir="$KOS_ROOT/kos/include" \
					--oldincludedir="$KOS_ROOT/kos/include" \
					--infodir="/usr/share/info" \
					--mandir="/usr/share/man" \
					--host="$TARGET_NAME-linux-gnu" \
					--enable-widec \
					--without-ada \
					--disable-db-install \
					--without-progs \
					--without-tack \
					--without-tests \
					--without-manpages \
					--with-shared \
					--with-normal \
					--with-debug \
					--with-cxx-shared \
					--disable-big-core \
					--disable-database \
					--with-fallbacks=xterm,unknown \
					--enable-const \
					--enable-ext-mouse \
					--enable-sigwinch \
					--disable-stripping
			fi
			cmd cd "$OPTPATH"
			cmd make -j $MAKE_PARALLEL_COUNT
		fi
		install_ncurses_library() {
			install_file /$TARGET_LIBPATH/${1}.so.$NCURSES_VERISON_MAJOR "$OPTPATH/lib/${1}.so.$NCURSES_VERISON"
			install_symlink /$TARGET_LIBPATH/${1}.so.$NCURSES_VERISON ${1}.so.$NCURSES_VERISON_MAJOR
			install_symlink /$TARGET_LIBPATH/${1}.so ${1}.so.$NCURSES_VERISON_MAJOR
			install_file_nodisk /$TARGET_LIBPATH/${1}.a "$OPTPATH/lib/${1}.a"
			install_file_nodisk /$TARGET_LIBPATH/${1}_g.a "$OPTPATH/lib/${1}_g.a"
		}
		install_ncurses_library libformw
		install_ncurses_library libmenuw
		install_ncurses_library libncursesw
		install_ncurses_library libpanelw

		cmd mkdir -p "$KOS_ROOT/kos/include/ncursesw"
		install_header_ex() {
			echo "Installing header:/include/$2"
			unlink "$KOS_ROOT/kos/include/$2" > /dev/null 2>&1
			cmd cp "$1" "$KOS_ROOT/kos/include/$2"
			echo "#include \"../$2\"" > "$KOS_ROOT/kos/include/ncursesw/$2"
		}
		install_header() {
			install_header_ex "$OPTPATH/include/$1" "$1"
		}
		install_header eti.h
		install_header form.h
		install_header menu.h
		install_header panel.h
		install_header curses.h
		install_header ncurses_cfg.h
		install_header ncurses_def.h
		install_header_ex "$SRCPATH/include/nc_tparm.h" nc_tparm.h
		echo "Installing header:/include/ncurses.h"
		echo '#include "curses.h"' > "$KOS_ROOT/kos/include/ncurses.h"
		echo '#include "../curses.h"' > "$KOS_ROOT/kos/include/ncursesw/ncurses.h"
		install_header ncurses_dll.h
		install_header term.h
		install_header_ex "$SRCPATH/include/term_entry.h" term_entry.h
		install_header termcap.h
		install_header_ex "$SRCPATH/include/tic.h" tic.h
		install_header unctrl.h
		# C++ headers
		install_header_ex "$SRCPATH/c++/cursesapp.h" cursesapp.h
		install_header_ex "$SRCPATH/c++/cursesf.h" cursesf.h
		install_header_ex "$SRCPATH/c++/cursesm.h" cursesm.h
		install_header_ex "$SRCPATH/c++/cursesp.h" cursesp.h
		install_header_ex "$SRCPATH/c++/cursesw.h" cursesw.h
		install_header_ex "$SRCPATH/c++/cursslk.h" cursslk.h
		install_header_ex "$OPTPATH/c++/etip.h" etip.h
		;;
##############################################################################


##############################################################################
	nano | nano-4.4)
		NANO_VERISON="4.4"
		SRCPATH="$KOS_ROOT/binutils/src/nano-$NANO_VERISON"
		OPTPATH="$BINUTILS_SYSROOT/opt/nano-$NANO_VERISON"
		if [ "$MODE_FORCE_MAKE" == yes ] || \
		 ! [ -f "$OPTPATH/src/nano" ]; then
			if [ "$MODE_FORCE_CONF" == yes ] || \
			 ! [ -f "$OPTPATH/Makefile" ]; then
				if ! [ -f "$SRCPATH/configure" ]; then
					cmd cd "$KOS_ROOT/binutils/src"
					download_file \
						"nano-$NANO_VERISON.tar.xz" \
						https://nano-editor.org/dist/v4/nano-$NANO_VERISON.tar.xz
					cmd tar xvf "nano-$NANO_VERISON.tar.xz"
				fi
				apply_patch \
					"$SRCPATH" \
					"$KOS_PATCHES/nano-$NANO_VERISON.patch"
				rm -rf "$OPTPATH" > /dev/null 2>&1
				cmd mkdir -p "$OPTPATH"
				cmd cd "$OPTPATH"
				export CC="${CROSS_PREFIX}gcc"
				export CPP="${CROSS_PREFIX}cpp"
				cmd bash ../../../src/nano-$NANO_VERISON/configure \
					--bindir="/bin" \
					--datarootdir="/usr/share" \
					--datadir="/usr/share" \
					--sysconfdir="/etc" \
					--localstatedir="/var" \
					--libdir="/usr/$TARGET_LIBPATH" \
					--includedir="/usr/include" \
					--oldincludedir="/usr/include" \
					--infodir="/usr/share/info" \
					--mandir="/usr/share/man" \
					--localedir="/usr/share/locale" \
					--host="$TARGET_NAME-linux-gnu" \
					--disable-threads \
					--disable-nls \
					--with-gnu-ld \
					--without-libiconv-prefix \
					--without-libintl-prefix
			fi
			cmd cd "$OPTPATH"
			cmd make -j $MAKE_PARALLEL_COUNT
		fi
		install_file /bin/nano "$OPTPATH/src/nano"
		;;
##############################################################################


##############################################################################
	deemon | deemon-200 | deemon-latest)
		SRCPATH="$KOS_ROOT/binutils/src/deemon-git/deemon"
		if ! [ -f "$SRCPATH/configure" ]; then
			rm -rf "$KOS_ROOT/binutils/src/deemon-git" > /dev/null 2>&1
			cmd mkdir -p "$KOS_ROOT/binutils/src/deemon-git"
			cmd cd "$KOS_ROOT/binutils/src/deemon-git"
			cmd git clone "https://github.com/GrieferAtWork/deemon.git"
		fi
		cmd cd "$SRCPATH"
		DEEMON_VERSION=$(git rev-parse HEAD)
		OPTPATH="$BINUTILS_SYSROOT/opt/deemon-git-$DEEMON_VERSION"
		if [ "$MODE_FORCE_MAKE" == yes ] || \
		 ! [ -f "$OPTPATH/deemon" ]; then
			if [ "$MODE_FORCE_CONF" == yes ] || \
			 ! [ -f "$OPTPATH/Makefile" ]; then
				rm -rf "$OPTPATH" > /dev/null 2>&1
				mkdir -p "$OPTPATH"
				cmd cd "$OPTPATH"
				cmd bash "$SRCPATH/configure" \
					--cross-prefix="$CROSS_PREFIX" \
					--config-exe-extension="" \
					--config-dll-extension=".so" \
					--with-deemon-home="/usr/$TARGET_LIBPATH/deemon" \
					--with-deemon-path="/usr/$TARGET_LIBPATH/deemon" \
					--config-pthread=""
			fi
			cmd cd "$OPTPATH"
			cmd make -j $MAKE_PARALLEL_COUNT
		fi
		install_file /bin/deemon "$OPTPATH/deemon"
		# install dex modules
		for filename in $OPTPATH/lib/*.so; do
			install_file "/usr/$TARGET_LIBPATH/deemon/$(basename -- "$filename")" "$filename"
		done
		# install user-code modules
		for filename in $SRCPATH/lib/*.dee; do
			install_file "/usr/$TARGET_LIBPATH/deemon/$(basename -- "$filename")" "$filename"
		done
		for folder in _codecs net python rt; do
			for filename in $SRCPATH/lib/$folder/*.dee; do
				install_file "/usr/$TARGET_LIBPATH/deemon/$folder/$(basename -- "$filename")" "$filename"
			done
		done
		;;
##############################################################################


##############################################################################
	zlib | zlib-1.2.11)
		ZLIB_VERISON_MAJOR="1"
		ZLIB_VERISON="$ZLIB_VERISON_MAJOR.2.11"
		SRCPATH="$KOS_ROOT/binutils/src/zlib-$ZLIB_VERISON"
		OPTPATH="$BINUTILS_SYSROOT/opt/zlib-$ZLIB_VERISON"
		if [ "$MODE_FORCE_MAKE" == yes ] || \
		 ! [ -f "$OPTPATH/libz.so.$ZLIB_VERISON" ]; then
			if [ "$MODE_FORCE_CONF" == yes ] || \
			 ! [ -f "$OPTPATH/Makefile" ]; then
				if ! [ -f "$SRCPATH/configure" ]; then
					cmd cd "$KOS_ROOT/binutils/src"
					download_file \
						"zlib-$ZLIB_VERISON.tar.gz" \
						https://www.zlib.net/zlib-$ZLIB_VERISON.tar.gz
					cmd tar xvf "zlib-$ZLIB_VERISON.tar.gz"
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
				cmd bash ../../../src/zlib-$ZLIB_VERISON/configure \
					--prefix=/ \
					--eprefix=/ \
					--libdir=/$TARGET_LIBPATH \
					--sharedlibdir=/$TARGET_LIBPATH \
					--includedir=/usr/include \
					--enable-shared
			fi
			cmd cd "$OPTPATH"
			cmd make -j $MAKE_PARALLEL_COUNT
		fi
		# Install headers
		install_header() {
			echo "Installing header:/include/$2"
			unlink "$KOS_ROOT/kos/include/$2" > /dev/null 2>&1
			cmd cp "$1" "$KOS_ROOT/kos/include/$2"
		}
		install_header "$OPTPATH/zconf.h" "zconf.h"
		install_header "$SRCPATH/zlib.h"  "zlib.h"
		# Install libraries
		install_file /$TARGET_LIBPATH/libz.so "$OPTPATH/libz.so.$ZLIB_VERISON"
		install_symlink /$TARGET_LIBPATH/libz.so.$ZLIB_VERISON libz.so
		install_symlink /$TARGET_LIBPATH/libz.so.$ZLIB_VERISON_MAJOR libz.so
		install_file_nodisk /$TARGET_LIBPATH/libz.a "$OPTPATH/libz.a"
		;;
##############################################################################


##############################################################################
	python | python-2.7.16)
		PYTHON_VERISON_MAJOR="2"
		PYTHON_VERISON_MINOR="7"
		PYTHON_VERISON_PATCH="16"
		PYTHON_VERISON="$PYTHON_VERISON_MAJOR.$PYTHON_VERISON_MINOR.$PYTHON_VERISON_PATCH"
		SRCPATH="$KOS_ROOT/binutils/src/Python-$PYTHON_VERISON"
		OPTPATH="$BINUTILS_SYSROOT/opt/Python-$PYTHON_VERISON"
		if [ "$MODE_FORCE_MAKE" == yes ] || {
			! [ -f "$OPTPATH/python" ] &&
			! [ -f "$OPTPATH/python.exe" ]
		}; then
			if [ "$MODE_FORCE_CONF" == yes ] || \
			 ! [ -f "$OPTPATH/Makefile" ]; then
				if ! [ -f "$SRCPATH/configure" ]; then
					cmd cd "$KOS_ROOT/binutils/src"
					download_file \
						"Python-$PYTHON_VERISON.tar.xz" \
						https://www.python.org/ftp/python/$PYTHON_VERISON/Python-$PYTHON_VERISON.tar.xz
					cmd tar xvf "Python-$PYTHON_VERISON.tar.xz"
				fi
				rm -rf "$OPTPATH" > /dev/null 2>&1
				cmd mkdir -p "$OPTPATH"
				cmd cd "$OPTPATH"
				export CC="${CROSS_PREFIX}gcc"
				export CPP="${CROSS_PREFIX}cpp"
				export CXX="${CROSS_PREFIX}g++"
				export CFLAGS="-ggdb"
				export CXXFLAGS="-ggdb"
				cat > "$OPTPATH/config.site" <<EOF
ac_cv_file__dev_ptmx=no
ac_cv_file__dev_ptc=no
EOF
				export CONFIG_SITE="$OPTPATH/config.site"
				cmd bash ../../../src/Python-$PYTHON_VERISON/configure \
					--prefix="/" \
					--exec-prefix="/" \
					--bindir="/bin" \
					--sbindir="/bin" \
					--sysconfdir="/etc" \
					--libexecdir="/usr/libexec" \
					--sharedstatedir="/usr/com" \
					--localstatedir="/usr/var" \
					--libdir="/$TARGET_LIBPATH" \
					--includedir="/usr/include" \
					--oldincludedir="/usr/include" \
					--datarootdir="/usr/share" \
					--infodir="/usr/share/info" \
					--localedir="/usr/share/locale" \
					--mandir="/usr/share/man" \
					--build=$(gcc -dumpmachine) \
					--host="$TARGET_NAME-linux-gnu" \
					--target="$TARGET_NAME-linux-gnu" \
					--enable-shared \
					--enable-ipv6 \
					--enable-unicode=ucs4 \
					--with-suffix="" \
					--with-signal-module \
					--with-threads \
					--with-wctype-functions \
					--with-libm=-lm \
					--with-libc=-lc \
					--with-computed-gotos
			fi
			cmd cd "$OPTPATH"
			cmd make -j $MAKE_PARALLEL_COUNT
		fi
		PYTHON_EXE="$OPTPATH/python"
		if [ -f "$OPTPATH/python.exe" ]; then
			PYTHON_EXE="$OPTPATH/python.exe"
		fi
		# Install the python core
		install_file /bin/python "$PYTHON_EXE"
		PYTHON_LIB="libpython${PYTHON_VERISON_MAJOR}.${PYTHON_VERISON_MINOR}"
		install_file /$TARGET_LIBPATH/${PYTHON_LIB}.so.1.0 "$OPTPATH/${PYTHON_LIB}.so.1.0"
		install_symlink /$TARGET_LIBPATH/${PYTHON_LIB}.so ${PYTHON_LIB}.so.1.0
		install_file_nodisk /$TARGET_LIBPATH/${PYTHON_LIB}.a "$OPTPATH/${PYTHON_LIB}.a"
		# Install modules under `/lib/python2.7/[os.py...]'
		install_path_hardcopy /$TARGET_LIBPATH/python${PYTHON_VERISON_MAJOR}.${PYTHON_VERISON_MINOR} "${SRCPATH}/Lib"
		install_path /$TARGET_LIBPATH/python${PYTHON_VERISON_MAJOR}.${PYTHON_VERISON_MINOR}/lib-dynload "${OPTPATH}/build/lib.linux2-${TARGET_NAME}-${PYTHON_VERISON_MAJOR}.${PYTHON_VERISON_MINOR}"
		;;
##############################################################################


##############################################################################
	tty-solitaire | tty-solitaire-1.1.1)
		# NOTE: This program requires that you first run:
		#       $ make_utility.sh <TARGET> ncurses
		VERSION="0268d6df09990cbb85682b1ad947b8d602acb097"
		SRCPATH="$KOS_ROOT/binutils/src/tty-solitaire"
		OPTPATH="$BINUTILS_SYSROOT/opt/tty-solitaire"
		EXEFILE="$OPTPATH/ttysolitaire"
		if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$EXEFILE" ]; then
			if ! [ -f "$SRCPATH/Makefile" ]; then
				cmd mkdir -p "$SRCPATH"
				cmd cd "$SRCPATH/.."
				cmd git clone https://github.com/mpereira/tty-solitaire.git
				cmd cd "$SRCPATH"
				cmd git checkout "$VERSION" -f
			fi
			cmd mkdir -p "$OPTPATH"
			apply_patch "$SRCPATH" "$KOS_PATCHES/tty-solitaire-$VERSION.patch"
			# The program's Makefile isn't designed for cross-compiling
			# But since the program is fairly simple, just compile all *.c
			# files from its /src directory, and link them together into a
			# single program
			set_archpath
			TS_OBJECTS=""
			cmd cd "$SRCPATH/src"
			for SRCFILE in *.c; do
				OBJFILE="$OPTPATH/$SRCFILE.o"
				SRCFILE="$SRCPATH/src/$SRCFILE"
				TS_OBJECTS="$TS_OBJECTS $OBJFILE"
				if [ "$MODE_FORCE_MAKE" == yes ] || [ "$OBJFILE" -ot "$SRCFILE" ]; then
					echo "compile: $CC -c -o $OBJFILE $SRCFILE"
					cmd "$CC" -g -c -o "$OBJFILE" "$SRCFILE" &
				fi
			done
			cmd wait
			# Build and link against ncurses
			echo "link: $CC -o $EXEFILE $TS_OBJECTS -lncursesw"
			cmd "$CC" -g -o "$EXEFILE" "$TS_OBJECTS" -lncursesw
		fi
		# Install ttysolitaire to disk
		install_file /bin/ttysolitaire "$EXEFILE"
		;;
##############################################################################


	*)
		echo "Unknown utility '$UTILITY_NAME'"
		exit 1
		;;
esac









