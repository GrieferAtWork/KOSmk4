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


if (($# != 1)); then
	echo "Usage: ./make_tool.sh [OPTIONS...] <TOOL_NAME>"
	echo "    OPTIONS:"
	echo "        --force-configure     Force configure to be re-executed"
	echo "        --force-make          Force make to be re-executed"
	echo "    TOOL_NAME should be one of:"
	echo "        bochs"
	exit 1
fi

TOOL_NAME="$1"

KOS_MISC="$(dirname $(readlink -f "$0"))"
cmd cd "$KOS_MISC/../../"
KOS_ROOT="$(pwd)"
KOS_BINUTILS="${KOS_ROOT}/binutils"
MAKE_PARALLEL_COUNT=$(grep -c ^processor /proc/cpuinfo)

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


case $TOOL_NAME in

	bochs | bochs-2.6.11)
		BOCHS_VERSION="2.6.11"
		cmd mkdir -p "$KOS_BINUTILS/src"
		BOCHS_BUILDPATH="$KOS_BINUTILS/build-bochs-$BOCHS_VERSION"
		BOCHS_SRCPATH="$KOS_BINUTILS/src/bochs-$BOCHS_VERSION"
		if [ "$MODE_FORCE_MAKE" == yes ] || (! [ -f "$BOCHS_BUILDPATH/bochs" ] && ! [ -f "$BOCHS_BUILDPATH/bochs.exe" ]); then
			if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$BOCHS_BUILDPATH/Makefile" ]; then
				if ! [ -f "$BOCHS_SRCPATH/configure" ]; then
					cmd cd "$KOS_BINUTILS/src"
					download_file \
						"bochs-$BOCHS_VERSION.tar.gz" \
						"https://downloads.sourceforge.net/project/bochs/bochs/$BOCHS_VERSION/bochs-$BOCHS_VERSION.tar.gz"
					cmd tar xvf "bochs-$BOCHS_VERSION.tar.gz"
				fi
				cmd mkdir -p "$BOCHS_BUILDPATH"
				cmd cd "$BOCHS_BUILDPATH"
				BOCHS_OPTIONS_ADDEND=""
				case `uname -s` in
					*CYGWIN* | *MINGW* | *mingw*)
						BOCHS_OPTIONS_ADDEND="$BOCHS_OPTIONS_ADDEND --with-win32"
						;;
					*)
						BOCHS_OPTIONS_ADDEND="$BOCHS_OPTIONS_ADDEND --with-x --with-x11"
						;;
				esac
				# --enable-x86-64  (bochs blindly writes 64-bit values in
				#                   its GDB stub when this is enabled, thus
				#                   breaking GDB when the kernel is actually
				#                   running in 32-bit mode)
				#                  -> As such, we need 2 versions of bochs,
				#                     one for i386 and one for x86_64 (and
				#                     we sadly can't use the same for both)
				# --enable-protection-keys  (requires --enable-x86-64)
				cmd bash "../src/bochs-$BOCHS_VERSION/configure" \
					--enable-cpu-level=6 \
					--enable-a20-pin \
					--enable-gdb-stub \
					--enable-all-optimizations \
					--enable-fpu \
					--enable-alignment-check \
					--enable-monitor-mwait \
					--enable-pci \
					--enable-usb \
					--enable-usb-ohci \
					--enable-usb-ehci \
					--enable-usb-xhci \
					--enable-ne2000 \
					--enable-e1000 \
					--enable-clgd54xx \
					--enable-voodoo \
					--enable-cdrom \
					--enable-sb16 \
					--enable-es1370 \
					--enable-gameport \
					--enable-busmouse \
					$BOCHS_OPTIONS_ADDEND
			fi
			apply_patch \
				"${BOCHS_SRCPATH}" \
				"$KOS_MISC/patches/bochs-$BOCHS_VERSION.patch"
			cmd cd "$BOCHS_BUILDPATH"
			cmd make -j $MAKE_PARALLEL_COUNT
		fi
		
		;;

	*)
		echo "Unknown tool '$TOOL_NAME'"
		exit 1
		;;
esac














