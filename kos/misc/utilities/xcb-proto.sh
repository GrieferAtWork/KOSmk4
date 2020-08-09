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

VERSION="1.7.1"
SRCPATH="$KOS_ROOT/binutils/src/x/xcb-proto-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/x/xcb-proto-$VERSION"

require_program python

# xcb-proto
if ! [ -f "$BINUTILS_SYSROOT/usr/local/lib/python2.7/site-packages/xcbgen/__init__.py" ]; then
	if ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src/x"
			cmd rm -rf "xcb-proto-$VERSION"
			download_file \
				"xcb-proto-$VERSION.tar.gz" \
				"https://www.x.org/releases/X11R7.7/src/everything/xcb-proto-$VERSION.tar.gz"
			cmd tar xvf "xcb-proto-$VERSION.tar.gz"
		fi
		cmd rm -rf "$OPTPATH"
		cmd mkdir -p "$OPTPATH"
		cmd cd "$OPTPATH"
		cmd bash "../../../../src/x/xcb-proto-$VERSION/configure" \
			--prefix="$BINUTILS_SYSROOT/usr/local" \
			--exec-prefix="$BINUTILS_SYSROOT/usr/local"
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
	cmd make -j $MAKE_PARALLEL_COUNT install
fi

# Install the PKG_CONFIG file
if ! [ -f "$PKG_CONFIG_PATH/xcb-proto.pc" ]; then
	cmd mkdir -p "$PKG_CONFIG_PATH"
	cat > "$PKG_CONFIG_PATH/xcb-proto.pc" <<EOF
prefix=$BINUTILS_SYSROOT/usr/local
exec_prefix=$BINUTILS_SYSROOT/usr/local
datarootdir=$BINUTILS_SYSROOT/usr/local/share
datadir=$BINUTILS_SYSROOT/usr/local/share
libdir=$BINUTILS_SYSROOT/usr/local/lib
xcbincludedir=$BINUTILS_SYSROOT/usr/local/share/xcb
pythondir=$BINUTILS_SYSROOT/usr/local/lib/python2.7/site-packages

Name: XCB Proto
Description: X protocol descriptions for XCB
Version: $VERSION
EOF
fi

