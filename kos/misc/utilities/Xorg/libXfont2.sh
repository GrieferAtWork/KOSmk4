#TEST: require_utility Xorg/libXfont2 "$PKG_CONFIG_PATH/xfont2.pc"
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

require_utility Xorg/libfontenc "$PKG_CONFIG_PATH/fontenc.pc"
require_utility Xorg/xtrans     "$PKG_CONFIG_PATH/xtrans.pc"
require_utility Xorg/xorgproto  "$PKG_CONFIG_PATH/xproto.pc"
#equire_utility Xorg/xorgproto  "$PKG_CONFIG_PATH/fontsproto.pc"
require_utility libfreetype2    "$PKG_CONFIG_PATH/freetype2.pc"
require_utility libbzip2        "$PKG_CONFIG_PATH/bzip2.pc"
require_utility libzlib         "$PKG_CONFIG_PATH/zlib.pc"

# xorg-macros
. "$KOS_MISC/utilities/Xorg/misc/xorg-macros.sh"

VERSION="2.0.4"

SO_VERSION_MAJOR="2"
SO_VERSION="$SO_VERSION_MAJOR.0.0"

SRCPATH="$KOS_ROOT/binutils/src/Xorg/libXfont2-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/Xorg/libXfont2-$VERSION"

# libXfont2
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/.libs/libXfont2.so.$SO_VERSION" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd mkdir -p "$KOS_ROOT/binutils/src/Xorg"
			cmd cd "$KOS_ROOT/binutils/src/Xorg"
			cmd rm -rf "libXfont2-$VERSION"
			download_file \
				"libXfont2-$VERSION.tar.gz" \
				"https://www.x.org/releases/X11R7.7/src/lib/libXfont2-$VERSION.tar.gz"
			cmd tar xvf "libXfont2-$VERSION.tar.gz"
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
			cmd bash "../../../../src/Xorg/libXfont2-$VERSION/configure" \
				--prefix="$XORG_CONFIGURE_PREFIX" \
				--exec-prefix="$XORG_CONFIGURE_EXEC_PREFIX" \
				--bindir="$XORG_CONFIGURE_BINDIR" \
				--sbindir="$XORG_CONFIGURE_SBINDIR" \
				--libexecdir="$XORG_CONFIGURE_LIBEXECDIR" \
				--sysconfdir="$XORG_CONFIGURE_SYSCONFDIR" \
				--sharedstatedir="$XORG_CONFIGURE_SHAREDSTATEDIR" \
				--localstatedir="$XORG_CONFIGURE_LOCALSTATEDIR" \
				--libdir="$XORG_CONFIGURE_LIBDIR" \
				--includedir="$XORG_CONFIGURE_INCLUDEDIR" \
				--oldincludedir="$XORG_CONFIGURE_OLDINCLUDEDIR" \
				--datarootdir="$XORG_CONFIGURE_DATAROOTDIR" \
				--datadir="$XORG_CONFIGURE_DATADIR" \
				--infodir="$XORG_CONFIGURE_INFODIR" \
				--localedir="$XORG_CONFIGURE_LOCALEDIR" \
				--mandir="$XORG_CONFIGURE_MANDIR" \
				--docdir="$XORG_CONFIGURE_DOCDIR_PREFIX/libXfont2" \
				--htmldir="$XORG_CONFIGURE_HTMLDIR_PREFIX/libXfont2" \
				--dvidir="$XORG_CONFIGURE_DVIDIR_PREFIX/libXfont2" \
				--pdfdir="$XORG_CONFIGURE_PDFDIR_PREFIX/libXfont2" \
				--psdir="$XORG_CONFIGURE_PSDIR_PREFIX/libXfont2" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--enable-shared \
				--enable-static \
				--disable-devel-docs \
				--enable-freetype \
				--enable-builtins \
				--enable-pcfformat \
				--enable-bdfformat \
				--enable-snfformat \
				--enable-fc \
				--enable-unix-transport \
				--disable-tcp-transport \
				--disable-ipv6 \
				--enable-local-transport \
				--with-gnu-ld \
				--without-xmlto \
				--without-fop \
				--with-bzip2
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# Install libraries
install_file /$TARGET_LIBPATH/libXfont2.so.$SO_VERSION_MAJOR "$OPTPATH/.libs/libXfont2.so.$SO_VERSION"
install_symlink /$TARGET_LIBPATH/libXfont2.so.$SO_VERSION libXfont2.so.$SO_VERSION_MAJOR
install_symlink /$TARGET_LIBPATH/libXfont2.so libXfont2.so.$SO_VERSION_MAJOR
install_file_nodisk /$TARGET_LIBPATH/libXfont2.a "$OPTPATH/.libs/libXfont2.a"

# Install headers
INCPATH="$KOS_ROOT/kos/include/X11/fonts"
install_rawfile "$INCPATH/libxfont2.h"   "$SRCPATH/include/X11/fonts/libxfont2.h"
install_rawfile "$INCPATH/bdfint.h"      "$SRCPATH/include/X11/fonts/bdfint.h"
install_rawfile "$INCPATH/bitmap.h"      "$SRCPATH/include/X11/fonts/bitmap.h"
install_rawfile "$INCPATH/bufio.h"       "$SRCPATH/include/X11/fonts/bufio.h"
install_rawfile "$INCPATH/fntfil.h"      "$SRCPATH/include/X11/fonts/fntfil.h"
install_rawfile "$INCPATH/fntfilio.h"    "$SRCPATH/include/X11/fonts/fntfilio.h"
install_rawfile "$INCPATH/fntfilst.h"    "$SRCPATH/include/X11/fonts/fntfilst.h"
install_rawfile "$INCPATH/fontencc.h"    "$SRCPATH/include/X11/fonts/fontencc.h"
install_rawfile "$INCPATH/fontmisc.h"    "$SRCPATH/include/X11/fonts/fontmisc.h"
install_rawfile "$INCPATH/fontshow.h"    "$SRCPATH/include/X11/fonts/fontshow.h"
install_rawfile "$INCPATH/fontutil.h"    "$SRCPATH/include/X11/fonts/fontutil.h"
install_rawfile "$INCPATH/fontxlfd.h"    "$SRCPATH/include/X11/fonts/fontxlfd.h"
install_rawfile "$INCPATH/pcf.h"         "$SRCPATH/include/X11/fonts/pcf.h"
install_rawfile "$INCPATH/libxfontint.h" "$SRCPATH/include/libxfontint.h"
install_rawfile "$INCPATH/ft.h"          "$SRCPATH/src/FreeType/ft.h"
install_rawfile "$INCPATH/ftfuncs.h"     "$SRCPATH/src/FreeType/ftfuncs.h"

# Install the PKG_CONFIG file
install_rawfile_stdin "$PKG_CONFIG_PATH/xfont2.pc" <<EOF
prefix=$XORG_CONFIGURE_PREFIX
exec_prefix=$XORG_CONFIGURE_EXEC_PREFIX
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: Xfont2
Description: X font Library version 2
Version: $VERSION
Requires: xproto fontsproto
Requires.private: fontenc freetype2
Cflags:
Libs: -lXfont2
Libs.private: -lz -lbz2 -lm
EOF
