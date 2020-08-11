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

# depends: libfontenc
# depends: xtrans
# depends: xproto
# depends: fontsproto
# depends: libfreetype2

# xorg-macros
. "$KOS_MISC/utilities/misc/xorg-macros.sh"

VERSION="1.4.5"
XTRANS_VERSION="1.2.7"

SO_VERSION_MAJOR="1"
SO_VERSION="$SO_VERSION_MAJOR.4.1"

SRCPATH="$KOS_ROOT/binutils/src/x/libXfont-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/x/libXfont-$VERSION"

# libXfont
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/src/.libs/libXfont.so.$SO_VERSION" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			if ! [ -f "$SRCPATH/configure.ac" ]; then
				cmd cd "$KOS_ROOT/binutils/src/x"
				cmd rm -rf "libXfont-$VERSION"
				download_file \
					"libXfont-$VERSION.tar.gz" \
					"https://www.x.org/releases/X11R7.7/src/lib/libXfont-$VERSION.tar.gz"
				cmd tar xvf "libXfont-$VERSION.tar.gz"
			fi
			cmd cd "$SRCPATH"
			export ACLOCAL="aclocal -I $KOS_ROOT/binutils/src/x/xtrans-$XTRANS_VERSION"
			xcmd $ACLOCAL      || { err=$?; unlink "$SRCPATH/configure"; exit $?; }
			xcmd autoreconf -i || { err=$?; unlink "$SRCPATH/configure"; exit $?; }
			xcmd autoconf      || { err=$?; unlink "$SRCPATH/configure"; exit $?; }
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
			cmd bash "../../../../src/x/libXfont-$VERSION/configure" \
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
				--docdir="/usr/share/doc/libXfont" \
				--htmldir="/usr/share/doc/libXfont" \
				--dvidir="/usr/share/doc/libXfont" \
				--pdfdir="/usr/share/doc/libXfont" \
				--psdir="/usr/share/doc/libXfont" \
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

# Install the PKG_CONFIG file
if ! [ -f "$PKG_CONFIG_PATH/xfont.pc" ]; then
	cmd mkdir -p "$PKG_CONFIG_PATH"
	cat > "$PKG_CONFIG_PATH/xfont.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: Xfont
Description: X font Library
Version: $VERSION
Requires: xproto fontsproto
Requires.private: fontenc freetype2
Cflags:
Libs: -lXfont
Libs.private: -lz -lbz2 -lm
EOF
fi

# Install libraries
install_file /$TARGET_LIBPATH/libXfont.so.$SO_VERSION_MAJOR "$OPTPATH/src/.libs/libXfont.so.$SO_VERSION"
install_symlink /$TARGET_LIBPATH/libXfont.so.$SO_VERSION libXfont.so.$SO_VERSION_MAJOR
install_symlink /$TARGET_LIBPATH/libXfont.so libXfont.so.$SO_VERSION_MAJOR
install_file_nodisk /$TARGET_LIBPATH/libXfont.a "$OPTPATH/src/.libs/libXfont.a"

# Install headers
INCPATH="$KOS_ROOT/kos/include/X11/fonts"
install_rawfile "$INCPATH/bdfint.h"   "$SRCPATH/include/X11/fonts/bdfint.h"
install_rawfile "$INCPATH/bitmap.h"   "$SRCPATH/include/X11/fonts/bitmap.h"
install_rawfile "$INCPATH/bufio.h"    "$SRCPATH/include/X11/fonts/bufio.h"
install_rawfile "$INCPATH/fntfil.h"   "$SRCPATH/include/X11/fonts/fntfil.h"
install_rawfile "$INCPATH/fntfilio.h" "$SRCPATH/include/X11/fonts/fntfilio.h"
install_rawfile "$INCPATH/fntfilst.h" "$SRCPATH/include/X11/fonts/fntfilst.h"
install_rawfile "$INCPATH/fontencc.h" "$SRCPATH/include/X11/fonts/fontencc.h"
install_rawfile "$INCPATH/fontmisc.h" "$SRCPATH/include/X11/fonts/fontmisc.h"
install_rawfile "$INCPATH/fontshow.h" "$SRCPATH/include/X11/fonts/fontshow.h"
install_rawfile "$INCPATH/fontutil.h" "$SRCPATH/include/X11/fonts/fontutil.h"
install_rawfile "$INCPATH/fontxlfd.h" "$SRCPATH/include/X11/fonts/fontxlfd.h"
install_rawfile "$INCPATH/pcf.h"      "$SRCPATH/include/X11/fonts/pcf.h"
install_rawfile "$INCPATH/ft.h"       "$SRCPATH/src/FreeType/ft.h"
install_rawfile "$INCPATH/ftfuncs.h"  "$SRCPATH/src/FreeType/ftfuncs.h"
install_rawfile "$INCPATH/fontconf.h" "$OPTPATH/include/X11/fonts/fontconf.h"

