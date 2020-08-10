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

VERSION="1.1.2"
SRCPATH="$KOS_ROOT/binutils/src/x/bigreqsproto-$VERSION"

# bigreqsproto
if ! [ -f "$SRCPATH/configure" ]; then
	cmd cd "$KOS_ROOT/binutils/src/x"
	cmd rm -rf "bigreqsproto-$VERSION"
	download_file \
		"bigreqsproto-$VERSION.tar.gz" \
		"https://www.x.org/releases/X11R7.7/src/everything/bigreqsproto-$VERSION.tar.gz"
	cmd tar xvf "bigreqsproto-$VERSION.tar.gz"
fi

# Install the PKG_CONFIG file
if ! [ -f "$PKG_CONFIG_PATH/bigreqsproto.pc" ]; then
	cmd mkdir -p "$PKG_CONFIG_PATH"
	cat > "$PKG_CONFIG_PATH/bigreqsproto.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: BigReqsProto
Description: BigReqs extension headers
Version: $VERSION
Cflags:
EOF
fi

# Install headers
install_header() {
	install_rawfile "$KOS_ROOT/kos/include/X11/extensions/$1" "$SRCPATH/$1"
}
install_header "bigreqsproto.h"
install_header "bigreqstr.h"
