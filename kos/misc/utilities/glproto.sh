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

VERSION="1.4.15"
SRCPATH="$KOS_ROOT/binutils/src/x/glproto-$VERSION"

# glproto
if ! [ -f "$SRCPATH/configure" ]; then
	cmd cd "$KOS_ROOT/binutils/src/x"
	cmd rm -rf "glproto-$VERSION"
	download_file \
		"glproto-$VERSION.tar.gz" \
		"https://www.x.org/releases/X11R7.7/src/everything/glproto-$VERSION.tar.gz"
	cmd tar xvf "glproto-$VERSION.tar.gz"
fi
apply_patch "$SRCPATH" "$KOS_PATCHES/glproto-$VERSION.patch"


# Install the PKG_CONFIG file
if ! [ -f "$PKG_CONFIG_PATH/glproto.pc" ]; then
	cmd mkdir -p "$PKG_CONFIG_PATH"
	cat > "$PKG_CONFIG_PATH/glproto.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: GLProto
Description: GL extension headers
Version: $VERSION
Cflags:
EOF
fi

# Install headers
install_rawfile "$KOS_ROOT/kos/include/GL/internal/glcore.h" "$SRCPATH/glcore.h"
install_rawfile "$KOS_ROOT/kos/include/GL/glxint.h"          "$SRCPATH/glxint.h"
install_rawfile "$KOS_ROOT/kos/include/GL/glxmd.h"           "$SRCPATH/glxmd.h"
install_rawfile "$KOS_ROOT/kos/include/GL/glxproto.h"        "$SRCPATH/glxproto.h"
install_rawfile "$KOS_ROOT/kos/include/GL/glxtokens.h"       "$SRCPATH/glxtokens.h"
