#TEST: require_utility Xorg/proto.inputproto "$PKG_CONFIG_PATH/inputproto.pc"
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

VERSION="2.3.2"
SRCPATH="$KOS_ROOT/binutils/src/Xorg/inputproto-$VERSION"

# inputproto
if ! [ -f "$SRCPATH/configure" ]; then
	cmd mkdir -p "$KOS_ROOT/binutils/src/Xorg"
	cmd cd "$KOS_ROOT/binutils/src/Xorg"
	cmd rm -rf "inputproto-$VERSION"
	download_file \
		"inputproto-$VERSION.tar.gz" \
		"https://www.x.org/releases/individual/proto/inputproto-$VERSION.tar.gz"
	cmd tar xvf "inputproto-$VERSION.tar.gz"
fi

# Install headers
install_header() {
	install_rawfile "$KOS_ROOT/kos/include/X11/extensions/$1" "$SRCPATH/$1"
}
install_header "XI.h"
install_header "XIproto.h"
install_header "XI2.h"
install_header "XI2proto.h"

# Install the PKG_CONFIG file
install_rawfile_stdin "$PKG_CONFIG_PATH/inputproto.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include
includex11dir=$KOS_ROOT/kos/include/X11

Name: InputProto
Description: Input extension headers
Version: $VERSION
Cflags:
EOF
