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

require_program aclocal
require_program autoreconf
require_program autoconf
require_program libtool

VERSION_XORG_MACROS="1.17"
SRCPATH_XORG_MACROS="$KOS_ROOT/binutils/src/x/xorg-macros-$VERSION_XORG_MACROS"
OPTPATH_XORG_MACROS="$BINUTILS_SYSROOT/opt/x/xorg-macros-$VERSION_XORG_MACROS"

# xorg-macros
if ! [ -f "$PKG_CONFIG_PATH/xorg-macros.pc" ]; then
	if ! [ -f "$OPTPATH_XORG_MACROS/Makefile" ]; then
		if ! [ -f "$SRCPATH_XORG_MACROS/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src/x"
			cmd rm -rf "xorg-macros-$VERSION_XORG_MACROS"
			cmd rm -rf "util-macros-$VERSION_XORG_MACROS"
			if ! [ -f "xorg-macros-$VERSION_XORG_MACROS.tar.gz" ]; then
				download_file \
					"util-macros-$VERSION_XORG_MACROS.tar.gz" \
					"https://www.x.org/releases/X11R7.7/src/everything/util-macros-$VERSION_XORG_MACROS.tar.gz"
				cmd mv \
					"util-macros-$VERSION_XORG_MACROS.tar.gz" \
					"xorg-macros-$VERSION_XORG_MACROS.tar.gz"
			fi
			cmd tar xvf "xorg-macros-$VERSION_XORG_MACROS.tar.gz"
			cmd mv "util-macros-$VERSION_XORG_MACROS" "xorg-macros-$VERSION_XORG_MACROS"
		fi
		cmd rm -rf "$OPTPATH_XORG_MACROS"
		cmd mkdir -p "$OPTPATH_XORG_MACROS"
		cmd cd "$OPTPATH_XORG_MACROS"
		(
			export CC="${CROSS_PREFIX}gcc"
			export CPP="${CROSS_PREFIX}cpp"
			export CFLAGS="-ggdb"
			export CXX="${CROSS_PREFIX}g++"
			export CXXCPP="${CROSS_PREFIX}cpp"
			export CXXFLAGS="-ggdb"
			cmd bash "../../../../src/x/xorg-macros-$VERSION_XORG_MACROS/configure" \
				--prefix="$BINUTILS_SYSROOT/usr/local" \
				--exec-prefix="$BINUTILS_SYSROOT/usr/local"
		) || exit $?
	fi
	cmd cd "$OPTPATH_XORG_MACROS"
	cmd make -j $MAKE_PARALLEL_COUNT
	cmd make -j $MAKE_PARALLEL_COUNT install

	# The actual macros file is:
	#     $BINUTILS_SYSROOT/usr/local/share/aclocal/xorg-macros.m4
	cat > "$PKG_CONFIG_PATH/xorg-macros.pc" <<EOF
prefix=$BINUTILS_SYSROOT/usr/local
exec_prefix=$BINUTILS_SYSROOT/usr/local
includedir=$KOS_ROOT/kos/include
datarootdir=$BINUTILS_SYSROOT/usr/local/share
datadir=$BINUTILS_SYSROOT/usr/local/share
PACKAGE=util-macros
# Used by XORG_INSTALL
pkgdatadir=$BINUTILS_SYSROOT/usr/local/share/util-macros
# docdir is kept for backwards compatibility with XORG_INSTALL from
# util-macros 1.4
docdir=$BINUTILS_SYSROOT/usr/local/share/util-macros

Name: X.Org Macros
Description: A set of autoconf project macros for X.Org modules
Version: $VERSION_XORG_MACROS
EOF
fi

