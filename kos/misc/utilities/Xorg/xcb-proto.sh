#TEST: require_utility Xorg/xcb-proto "$PKG_CONFIG_PATH/xcb-proto.pc"
# Copyright (c) 2019-2025 Griefer@Work
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
#    Portions Copyright (c) 2019-2025 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

VERSION="1.14.1"
SRCPATH="$KOS_ROOT/binutils/src/Xorg/xcb-proto-$VERSION"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/Xorg/xcb-proto-$VERSION"

require_program python

# xcb-proto
if ! [ -f "$SYSROOT_BINUTILS_TARGET/usr/local/lib/python2.7/site-packages/xcbgen/__init__.py" ]; then
	if ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd mkdir -p "$KOS_ROOT/binutils/src/Xorg"
			cmd cd "$KOS_ROOT/binutils/src/Xorg"
			cmd rm -rf "xcb-proto-$VERSION"
			download_file \
				"xcb-proto-$VERSION.tar.gz" \
				"https://www.x.org/releases/individual/proto/xcb-proto-$VERSION.tar.gz"
			cmd tar xvf "xcb-proto-$VERSION.tar.gz"
		fi
		cmd rm -rf "$OPTPATH"
		cmd mkdir -p "$OPTPATH"
		cmd cd "$OPTPATH"
		cmd bash "../../../../src/Xorg/xcb-proto-$VERSION/configure" \
			--prefix="$SYSROOT_BINUTILS_TARGET/usr/local" \
			--exec-prefix="$SYSROOT_BINUTILS_TARGET/usr/local"
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
	cmd make -j $MAKE_PARALLEL_COUNT install
fi

# Install the PKG_CONFIG file
install_rawfile_stdin "$PKG_CONFIG_PATH/xcb-proto.pc" <<EOF
prefix=$SYSROOT_BINUTILS_TARGET/usr/local
exec_prefix=$SYSROOT_BINUTILS_TARGET/usr/local
datarootdir=$SYSROOT_BINUTILS_TARGET/usr/local/share
datadir=$SYSROOT_BINUTILS_TARGET/usr/local/share
libdir=$SYSROOT_BINUTILS_TARGET/usr/local/lib
xcbincludedir=$SYSROOT_BINUTILS_TARGET/usr/local/share/xcb
pythondir=$SYSROOT_BINUTILS_TARGET/usr/local/lib/python2.7/site-packages

Name: XCB Proto
Description: X protocol descriptions for XCB
Version: $VERSION
EOF
