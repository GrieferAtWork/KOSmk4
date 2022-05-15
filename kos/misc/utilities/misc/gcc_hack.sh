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


#################################################################
# Generate some wrapper programs for binutils gcc and g++ that
# discard any -I and -L arguments that are located outside of
# the normal "$KOS_ROOT"
#
# Additionally, re-define some (environment-)variables:
#  - $CROSS_PREFIX="${CROSS_PREFIX}hack-"
#  - $CROSS_COMPILE="$CROSS_PREFIX"
#
# Note that when being first built, these wrapper programs will
# have the KOS source root hard-coded inside of them, meaning
# that this is yet another place that will prevent you from
# re-naming the path you've extracted the KOS source tree to
# after having run some of the contained tools.
#################################################################


# hackgcc_wrapper <name>
hackgcc_wrapper() {
	local HACKGCC_MASTER="${CROSS_PREFIX}hack-$1"
	if ! [ -f "$HACKGCC_MASTER" ] && ! [ -f "$HACKGCC_MASTER.exe" ]; then
		case `uname -o` in
		Cygwin)
			HACKGCC_MASTER="${HACKGCC_MASTER}.exe"
			;;
		*) ;;
		esac
		echo "Building program '$HACKGCC_MASTER'"
		local HACKGCC_SLAVE="${CROSS_PREFIX}$1"
		local HACKGCC_KOS_ROOT="${KOS_ROOT%/}/"
		cmd gcc \
			-DSLAVE="\"$HACKGCC_SLAVE\"" \
			-DKOS_ROOT="\"$HACKGCC_KOS_ROOT\"" \
			-o "$HACKGCC_MASTER" \
			"${KOS_ROOT}/kos/misc/utilities/misc/gcc_hack.c"
	fi
}

hackgcc_symlink() {
	if ! [ -L "${CROSS_PREFIX}hack-$1" ] && ! [ -L "${CROSS_PREFIX}hack-$1.exe" ]; then
		if [ -f "${CROSS_PREFIX}$1.exe" ]; then
			echo "Install symlink '${CROSS_PREFIX}hack-$1.exe' (as '$TARGET_CPUNAME-kos-$1.exe')"
			cmd ln -s "$TARGET_CPUNAME-kos-$1.exe" "${CROSS_PREFIX}hack-$1.exe"
		else
			echo "Install symlink '${CROSS_PREFIX}hack-$1' (as '$TARGET_CPUNAME-kos-$1')"
			cmd ln -s "$TARGET_CPUNAME-kos-$1" "${CROSS_PREFIX}hack-$1"
		fi
	fi
}

# Generate symlinks/wrapper programs for all of the toolchain applets.
hackgcc_symlink addr2line
hackgcc_symlink ar
hackgcc_symlink as
hackgcc_wrapper c++
hackgcc_symlink c++filt
hackgcc_wrapper cpp
hackgcc_symlink elfedit
hackgcc_wrapper g++
hackgcc_wrapper gcc
hackgcc_wrapper gcc-12.1.0
hackgcc_symlink gcc-ar
hackgcc_symlink gcc-nm
hackgcc_symlink gcc-ranlib
hackgcc_symlink gcov
hackgcc_symlink gcov-dump
hackgcc_symlink gcov-tool
hackgcc_symlink gprof
hackgcc_wrapper ld
hackgcc_wrapper ld.bfd
hackgcc_symlink nm
hackgcc_symlink objcopy
hackgcc_symlink objdump
hackgcc_symlink ranlib
hackgcc_symlink readelf
hackgcc_symlink size
hackgcc_symlink strings
hackgcc_symlink strip

# Re-export the cross-prefix
export CROSS_PREFIX="${CROSS_PREFIX}hack-"
export CROSS_COMPILE="$CROSS_PREFIX"
