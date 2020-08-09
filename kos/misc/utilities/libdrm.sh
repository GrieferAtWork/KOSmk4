# NOTE: This file is currently excluded from the git via /.git/info/exclude!

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

# depends: libpciaccess

# xorg-macros
. "$KOS_MISC/utilities/misc/xorg-macros.sh"

VERSION="2.4.82"
SO_VERSION_MAJOR="2"
SO_VERSION="$SO_VERSION_MAJOR.4.0"

SRCPATH="$KOS_ROOT/binutils/src/x/libdrm-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/x/libdrm-$VERSION"

# libdrm
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/.libs/libdrm.so.$SO_VERSION" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			if ! [ -f "$SRCPATH/configure.ac" ]; then
				cmd cd "$KOS_ROOT/binutils/src/x"
				cmd rm -rf "libdrm-$VERSION"
				cmd rm -rf "libdrm-libdrm-$VERSION"
				download_file \
					"libdrm-$VERSION.tar.gz" \
					"https://github.com/freedreno/libdrm/archive/libdrm-$VERSION.tar.gz"
				cmd tar xvf "libdrm-$VERSION.tar.gz"
				if [ -d "libdrm-libdrm-$VERSION" ]; then
					mv "libdrm-libdrm-$VERSION" "libdrm-$VERSION"
				fi
			fi
			cmd cd "$SRCPATH"
			apply_patch \
				"$SRCPATH" \
				"$KOS_PATCHES/libdrm-$VERSION.patch"
			cmd aclocal
			cmd autoreconf -i
			cmd autoconf
		fi
		cmd rm -rf "$OPTPATH"
		cmd mkdir -p "$OPTPATH"
		cmd cd "$OPTPATH"
		(
			export CC="${CROSS_PREFIX}gcc"
			export CPP="${CROSS_PREFIX}cpp"
			export CFLAGS="-ggdb"
			export CXX="${CROSS_PREFIX}g++"
			export CXXCPP="${CROSS_PREFIX}cpp"
			export CXXFLAGS="-ggdb"
			cmd bash "../../../../src/x/libdrm-$VERSION/configure" \
				--prefix="/" \
				--exec-prefix="/" \
				--bindir="/bin" \
				--sbindir="/bin" \
				--libexecdir="/libexec" \
				--sysconfdir="/etc" \
				--sharedstatedir="/usr/com" \
				--localstatedir="/var" \
				--runstatedir="/run" \
				--libdir="/$TARGET_LIBPATH" \
				--includedir="/usr/include" \
				--oldincludedir="/usr/include" \
				--datarootdir="/usr/share" \
				--datadir="/usr/share" \
				--infodir="/usr/share/info" \
				--localedir="/usr/share/locale" \
				--mandir="/usr/share/man" \
				--docdir="/usr/share/doc/libdrm" \
				--htmldir="/usr/share/doc/libdrm" \
				--dvidir="/usr/share/doc/libdrm" \
				--pdfdir="/usr/share/doc/libdrm" \
				--psdir="/usr/share/doc/libdrm" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--disable-install-test-programs \
				--disable-cairo-tests
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# Install the PKG_CONFIG file
#     The make process above will have already created that file
#     under "$OPTPATH/libdrm.pc", however we don't actually want
#     to use that one since it contains the lines:
#     >> includedir=/usr/include
#     >> Cflags: -I${includedir}
#     Which in combination would cause the ~real~ system include
#     path to be added to include path, so we need to edit the file
if ! [ -f "$PKG_CONFIG_PATH/libdrm.pc" ]; then
	cmd mkdir -p "$PKG_CONFIG_PATH"
	cat > "$PKG_CONFIG_PATH/libdrm.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: libdrm
Description: Userspace interface to kernel DRM services
Version: $VERSION
Cflags:
Libs: -ldrm
EOF
fi

# Install libraries
install_file /$TARGET_LIBPATH/libdrm.so.$SO_VERSION_MAJOR "$OPTPATH/.libs/libdrm.so.$SO_VERSION"
install_symlink /$TARGET_LIBPATH/libdrm.so.$SO_VERSION libdrm.so.$SO_VERSION_MAJOR
install_symlink /$TARGET_LIBPATH/libdrm.so libdrm.so.$SO_VERSION_MAJOR

# Install headers
for f in "$SRCPATH"/include/drm/*.h; do
	install_rawfile "$KOS_ROOT/kos/include/drm/$(basename "$f")" "$f"
done

if ! [ -f "$KOS_ROOT/kos/include/drm.h" ]; then
	echo '#include "drm/drm.h"' > "$KOS_ROOT/kos/include/drm.h"
fi
