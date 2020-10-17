#TEST: require_utility Xorg/libXmu "$PKG_CONFIG_PATH/xmu.pc"
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

require_utility Xorg/xorgproto "$PKG_CONFIG_PATH/xextproto.pc"
require_utility Xorg/libX11    "$PKG_CONFIG_PATH/x11.pc"
require_utility Xorg/libXt     "$PKG_CONFIG_PATH/xt.pc"
require_utility Xorg/libXext   "$PKG_CONFIG_PATH/xext.pc"

# xorg-macros
. "$KOS_MISC/utilities/Xorg/misc/xorg-macros.sh"

VERSION="1.1.3"

SO_VERSION_MAJOR="6"
SO_VERSION="$SO_VERSION_MAJOR.2.0"

SRCPATH="$KOS_ROOT/binutils/src/Xorg/libXmu-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/Xorg/libXmu-$VERSION"

require_program xsltproc

# libXmu
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/src/.libs/libXmu.so.$SO_VERSION" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd mkdir -p "$KOS_ROOT/binutils/src/Xorg"
			cmd cd "$KOS_ROOT/binutils/src/Xorg"
			cmd rm -rf "libXmu-$VERSION"
			download_file \
				"libXmu-$VERSION.tar.gz" \
				"https://www.x.org/releases/individual/lib/libXmu-$VERSION.tar.gz"
			cmd tar xvf "libXmu-$VERSION.tar.gz"
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
			cmd bash "../../../../src/Xorg/libXmu-$VERSION/configure" \
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
				--docdir="$XORG_CONFIGURE_DOCDIR_PREFIX/libXmu" \
				--htmldir="$XORG_CONFIGURE_HTMLDIR_PREFIX/libXmu" \
				--dvidir="$XORG_CONFIGURE_DVIDIR_PREFIX/libXmu" \
				--pdfdir="$XORG_CONFIGURE_PDFDIR_PREFIX/libXmu" \
				--psdir="$XORG_CONFIGURE_PSDIR_PREFIX/libXmu" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--enable-shared \
				--enable-static \
				--disable-docs \
				--enable-unix-transport \
				--disable-tcp-transport \
				--disable-ipv6 \
				--enable-local-transport \
				--disable-lint-library \
				--with-gnu-ld \
				--without-xmlto \
				--without-fop \
				--without-lint
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# Install libraries
install_file        /$TARGET_LIBPATH/libXmu.so.$SO_VERSION_MAJOR "$OPTPATH/src/.libs/libXmu.so.$SO_VERSION"
install_symlink     /$TARGET_LIBPATH/libXmu.so.$SO_VERSION       libXmu.so.$SO_VERSION_MAJOR
install_symlink     /$TARGET_LIBPATH/libXmu.so                   libXmu.so.$SO_VERSION_MAJOR
install_file_nodisk /$TARGET_LIBPATH/libXmu.a                    "$OPTPATH/src/.libs/libXmu.a"
install_file        /$TARGET_LIBPATH/libXmuu.so.1                "$OPTPATH/src/.libs/libXmuu.so.1.0.0"
install_symlink     /$TARGET_LIBPATH/libXmuu.so.1.0.0            libXmuu.so.1
install_symlink     /$TARGET_LIBPATH/libXmuu.so                  libXmuu.so.1
install_file_nodisk /$TARGET_LIBPATH/libXmuu.a                   "$OPTPATH/src/.libs/libXmuu.a"

# Install headers
cmd cd "$SRCPATH/include/X11/Xmu"
for FILE in *.h; do
	install_rawfile \
		"$KOS_ROOT/kos/include/X11/Xmu/$FILE" \
		"$SRCPATH/include/X11/Xmu/$FILE"
done


# Install the PKG_CONFIG files
install_rawfile_stdin "$PKG_CONFIG_PATH/xmuu.pc" <<EOF
prefix=$XORG_CONFIGURE_PREFIX
exec_prefix=$XORG_CONFIGURE_EXEC_PREFIX
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: Xmuu
Description: Mini Xmu Library
Version: $VERSION
Requires: xproto x11
Requires.private: x11
Cflags:
Libs: -lXmuu
EOF

install_rawfile_stdin "$PKG_CONFIG_PATH/xmu.pc" <<EOF
prefix=$XORG_CONFIGURE_PREFIX
exec_prefix=$XORG_CONFIGURE_EXEC_PREFIX
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: Xmu
Description: Xmu Library
Version: $VERSION
Requires: xproto x11 xt
Requires.private: x11 xt xext
Cflags:
Libs: -lXmu
EOF
