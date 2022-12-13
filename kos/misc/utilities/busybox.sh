#TEST: require_utility busybox "$SYSROOT_BIN_TARGET_COMMON/bin/busybox"
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

if [ -z "$VERSION" ]; then VERSION="1.31.0"; fi

## Check final output binary
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/busybox-$VERSION"
SRCPATH="$KOS_ROOT/binutils/src/busybox-$VERSION"
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "${OPTPATH}/busybox_unstripped" ]; then
	## Check arch makefile
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "${OPTPATH}/Makefile" ]; then
		## Check shared (original) makefile
		if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "${SRCPATH}/Makefile" ]; then
			cmd cd "$KOS_ROOT/binutils/src"
			download_file \
				"busybox-$VERSION.tar.bz2" \
				https://www.busybox.net/downloads/busybox-$VERSION.tar.bz2
			cmd tar jxvf "busybox-$VERSION.tar.bz2"
		fi
		if [ -d "${OPTPATH}" ]; then
			cmd rm -rf "${OPTPATH}"
		fi
		cmd cp -R "${SRCPATH}" "$SYSROOT_BINUTILS_TARGET/opt/"
	fi
	apply_patch "${OPTPATH}" "$KOS_PATCHES/busybox-$VERSION.patch"
	cmd cd "${OPTPATH}"
	PATCH_CONFIG="$KOS_PATCHES/busybox.config"
	if ! [ -f ".config" ] || [ ".config" -ot "$PATCH_CONFIG" ]; then
		unlink ".config" > /dev/null 2>&1
		cmd cp "$KOS_PATCHES/busybox.config" ".config"
	fi
	cmd make -j $MAKE_PARALLEL_COUNT CONFIG_PREFIX=. CROSS_COMPILE="$CROSS_PREFIX"
fi
if ! [ -f "${OPTPATH}/busybox.links" ]; then
	cmd cd "${OPTPATH}"
	echo "Asking make to generate: '${OPTPATH}/busybox.links'"
	cmd make -j $MAKE_PARALLEL_COUNT CROSS_COMPILE="$CROSS_PREFIX" busybox.links
fi

# Install busybox in KOS. Note that we install the unstripped
# version, so-as to have debug information included, allowing
# KOS to display tracebacks through busybox!
install_file /bin/busybox "${OPTPATH}/busybox_unstripped"

SKIP_LINK="
/bin/true
/bin/false
"

# Install symbolic links
while read line; do
	text="/bin/busybox"
	if [[ "$line" == "/bin/"* ]] && ! [[ "$line" == "/bin/"*/ ]]; then
		text="busybox";
	elif [[ "$line" == "/sbin/"* ]] && ! [[ "$line" == "/sbin/"*/ ]]; then
		text="../bin/busybox";
	elif [[ "$line" == "/"* ]] && ! [[ "$line" == "/"*/ ]]; then
		text="bin/busybox";
	fi
	if ! [[ "$SKIP_LINK" == *"
$line
"* ]]; then
		install_symlink "$line" "$text"
	fi
done < "${OPTPATH}/busybox.links"

# Since busybox is kind-of needed to do anything with KOS, this
# is the perfect place to set-up some additional system paths
# within disk images
install_symlink "/etc/mtab" "/proc/mounts"
