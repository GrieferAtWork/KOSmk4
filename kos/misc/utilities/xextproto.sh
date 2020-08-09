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

VERSION="7.2.1"
SRCPATH="$KOS_ROOT/binutils/src/x/xextproto-$VERSION"

# xextproto
if ! [ -f "$SRCPATH/configure" ]; then
	cmd cd "$KOS_ROOT/binutils/src/x"
	cmd rm -rf "xextproto-$VERSION"
	download_file \
		"xextproto-$VERSION.tar.gz" \
		"https://www.x.org/releases/X11R7.7/src/everything/xextproto-$VERSION.tar.gz"
	cmd tar xvf "xextproto-$VERSION.tar.gz"
fi

# Install the PKG_CONFIG file
if ! [ -f "$PKG_CONFIG_PATH/xextproto.pc" ]; then
	cmd mkdir -p "$PKG_CONFIG_PATH"
	cat > "$PKG_CONFIG_PATH/xextproto.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include
includex11dir=$KOS_ROOT/kos/include/X11

Name: XExtProto
Description: XExt extension headers
Version: $VERSION
Cflags:
EOF
fi

# Install headers
install_header() {
	install_rawfile "$KOS_ROOT/kos/include/X11/extensions/$1" "$SRCPATH/$1"
}
install_header "dpmsconst.h"
install_header "dpmsproto.h"
install_header "ge.h"
install_header "geproto.h"
install_header "lbx.h"
install_header "lbxproto.h"
install_header "mitmiscconst.h"
install_header "mitmiscproto.h"
install_header "multibufconst.h"
install_header "multibufproto.h"
install_header "secur.h"
install_header "securproto.h"
install_header "shapeconst.h"
install_header "shapeproto.h"
install_header "shm.h"
install_header "shmproto.h"
install_header "syncconst.h"
install_header "syncproto.h"
install_header "ag.h"
install_header "agproto.h"
install_header "cup.h"
install_header "cupproto.h"
install_header "dbe.h"
install_header "dbeproto.h"
install_header "EVI.h"
install_header "EVIproto.h"
install_header "xtestext1proto.h"
install_header "xtestext1const.h"
install_header "xtestconst.h"
install_header "xtestproto.h"
install_header "shapestr.h"
install_header "shmstr.h"
install_header "syncstr.h"


