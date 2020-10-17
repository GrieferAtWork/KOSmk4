#TEST: require_utility Xorg/libXaw "$PKG_CONFIG_PATH/xaw7.pc"
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

require_utility Xorg/xorgproto "$PKG_CONFIG_PATH/xproto.pc"
require_utility Xorg/libX11    "$PKG_CONFIG_PATH/x11.pc"
require_utility Xorg/libXext   "$PKG_CONFIG_PATH/xext.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/xextproto.pc"
require_utility Xorg/libXt     "$PKG_CONFIG_PATH/xt.pc"
require_utility Xorg/libXmu    "$PKG_CONFIG_PATH/xmu.pc"
require_utility Xorg/libXpm    "$PKG_CONFIG_PATH/xpm.pc"

# xorg-macros
. "$KOS_MISC/utilities/Xorg/misc/xorg-macros.sh"

VERSION="1.0.13"

SRCPATH="$KOS_ROOT/binutils/src/Xorg/libXaw-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/Xorg/libXaw-$VERSION"

require_program xsltproc

# libXaw
if [ "$MODE_FORCE_MAKE" == yes ] || \
   ! [ -f "$OPTPATH/src/.libs/libXaw6.so.6.0.1" ] || \
   ! [ -f "$OPTPATH/src/.libs/libXaw7.so.7.0.0" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd mkdir -p "$KOS_ROOT/binutils/src/Xorg"
			cmd cd "$KOS_ROOT/binutils/src/Xorg"
			cmd rm -rf "libXaw-$VERSION"
			download_file \
				"libXaw-$VERSION.tar.gz" \
				"https://www.x.org/releases/individual/lib/libXaw-$VERSION.tar.gz"
			cmd tar xvf "libXaw-$VERSION.tar.gz"
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
			cmd bash "../../../../src/Xorg/libXaw-$VERSION/configure" \
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
				--docdir="$XORG_CONFIGURE_DOCDIR_PREFIX/libXaw" \
				--htmldir="$XORG_CONFIGURE_HTMLDIR_PREFIX/libXaw" \
				--dvidir="$XORG_CONFIGURE_DVIDIR_PREFIX/libXaw" \
				--pdfdir="$XORG_CONFIGURE_PDFDIR_PREFIX/libXaw" \
				--psdir="$XORG_CONFIGURE_PSDIR_PREFIX/libXaw" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--enable-shared \
				--enable-static \
				--disable-specs \
				--enable-xaw6 \
				--enable-xaw7 \
				--with-gnu-ld \
				--without-xmlto \
				--without-fop
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# Install libraries
install_file        /$TARGET_LIBPATH/libXaw6.so.6     "$OPTPATH/src/.libs/libXaw6.so.6.0.1"
install_symlink     /$TARGET_LIBPATH/libXaw6.so.6.0.1 libXaw6.so.6
install_symlink     /$TARGET_LIBPATH/libXaw6.so       libXaw6.so.6
install_file_nodisk /$TARGET_LIBPATH/libXaw6.a        "$OPTPATH/src/.libs/libXaw6.a"
install_file        /$TARGET_LIBPATH/libXaw7.so.7     "$OPTPATH/src/.libs/libXaw7.so.7.0.0"
install_symlink     /$TARGET_LIBPATH/libXaw7.so.7.0.0 libXaw7.so.7
install_symlink     /$TARGET_LIBPATH/libXaw7.so       libXaw7.so.7
install_file_nodisk /$TARGET_LIBPATH/libXaw7.a        "$OPTPATH/src/.libs/libXaw7.a"

# Install headers
cmd cd "$SRCPATH/include/X11/Xaw"
for FILE in *.h *.c; do
	install_rawfile \
		"$KOS_ROOT/kos/include/X11/Xaw/$FILE" \
		"$SRCPATH/include/X11/Xaw/$FILE"
done

# Install the PKG_CONFIG files
install_rawfile_stdin "$PKG_CONFIG_PATH/xaw6.pc" <<EOF
prefix=$XORG_CONFIGURE_PREFIX
exec_prefix=$XORG_CONFIGURE_EXEC_PREFIX
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: Xaw
Description: X Athena Widgets Library, version 6
Version: $VERSION
Requires: xproto xt
Requires.private: x11 xext xt xmu
Cflags:
Libs: -lXaw6
EOF

install_rawfile_stdin "$PKG_CONFIG_PATH/xaw7.pc" <<EOF
prefix=$XORG_CONFIGURE_PREFIX
exec_prefix=$XORG_CONFIGURE_EXEC_PREFIX
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: Xaw
Description: X Athena Widgets Library, version 7
Version: $VERSION
Requires: xproto xt
Requires.private: x11 xext xt xmu xpm
Cflags:
Libs: -lXaw7
EOF
