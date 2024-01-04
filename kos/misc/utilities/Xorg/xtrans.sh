#TEST: require_utility Xorg/xtrans "$PKG_CONFIG_PATH/xtrans.pc"
# Copyright (c) 2019-2024 Griefer@Work
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
#    Portions Copyright (c) 2019-2024 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

VERSION="1.4.0"
SRCPATH="$KOS_ROOT/binutils/src/Xorg/xtrans-$VERSION"

# xtrans
if ! [ -f "$SRCPATH/configure" ]; then
	cmd mkdir -p "$KOS_ROOT/binutils/src/Xorg"
	cmd cd "$KOS_ROOT/binutils/src/Xorg"
	cmd rm -rf "xtrans-$VERSION"
	download_file \
		"xtrans-$VERSION.tar.gz" \
		"https://www.x.org/releases/individual/lib/xtrans-$VERSION.tar.gz"
	cmd tar xvf "xtrans-$VERSION.tar.gz"
fi

apply_patch "$SRCPATH" "$KOS_PATCHES/xtrans-$VERSION.patch"

DSTPATH="$KOS_ROOT/kos/include/X11/Xtrans"
INSTALL_FILES="Xtrans.h Xtrans.c Xtransint.h Xtranslcl.c"
INSTALL_FILES="$INSTALL_FILES Xtranssock.c"
INSTALL_FILES="$INSTALL_FILES Xtransutil.c transport.c"

if [[ $VERSION == "1.2.7" ]]; then
	INSTALL_FILES="$INSTALL_FILES Xtranstli.c"
fi

# Install the header files
for f in $INSTALL_FILES; do
	install_rawfile "$KOS_ROOT/kos/include/X11/Xtrans/$f" "$SRCPATH/$f"
done

# Install the PKG_CONFIG file
install_rawfile_stdin "$PKG_CONFIG_PATH/xtrans.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: XTrans
Description: Abstract network code for X
Version: $VERSION
Cflags: -D_DEFAULT_SOURCE -D_BSD_SOURCE -DHAS_FCHOWN -DHAS_STICKY_DIR_BIT
EOF
