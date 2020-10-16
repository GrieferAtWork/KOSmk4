#TEST: require_utility Xorg/libXau "$PKG_CONFIG_PATH/xau.pc"
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

# xorg-macros
. "$KOS_MISC/utilities/Xorg/misc/xorg-macros.sh"

VERSION="1.0.9"

SO_VERSION_MAJOR="6"
SO_VERSION="$SO_VERSION_MAJOR.0.0"

SRCPATH="$KOS_ROOT/binutils/src/Xorg/libXau-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/Xorg/libXau-$VERSION"

require_program xsltproc

# libXau
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/.libs/libXau.so.$SO_VERSION" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd mkdir -p "$KOS_ROOT/binutils/src/Xorg"
			cmd cd "$KOS_ROOT/binutils/src/Xorg"
			cmd rm -rf "libXau-$VERSION"
			download_file \
				"libXau-$VERSION.tar.gz" \
				"https://www.x.org/releases/individual/lib/libXau-$VERSION.tar.gz"
			cmd tar xvf "libXau-$VERSION.tar.gz"
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
			cmd bash "../../../../src/Xorg/libXau-$VERSION/configure" \
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
				--docdir="$XORG_CONFIGURE_DOCDIR_PREFIX/libXau" \
				--htmldir="$XORG_CONFIGURE_HTMLDIR_PREFIX/libXau" \
				--dvidir="$XORG_CONFIGURE_DVIDIR_PREFIX/libXau" \
				--pdfdir="$XORG_CONFIGURE_PDFDIR_PREFIX/libXau" \
				--psdir="$XORG_CONFIGURE_PSDIR_PREFIX/libXau" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--enable-shared \
				--enable-static \
				--disable-lint-library \
				--with-gnu-ld
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# Install libraries
install_file /$TARGET_LIBPATH/libXau.so.$SO_VERSION_MAJOR "$OPTPATH/.libs/libXau.so.$SO_VERSION"
install_symlink /$TARGET_LIBPATH/libXau.so.$SO_VERSION libXau.so.$SO_VERSION_MAJOR
install_symlink /$TARGET_LIBPATH/libXau.so libXau.so.$SO_VERSION_MAJOR
install_file_nodisk /$TARGET_LIBPATH/libXau.a "$OPTPATH/.libs/libXau.a"

# Install headers
install_rawfile \
	"$KOS_ROOT/kos/include/X11/Xauth.h" \
	"$SRCPATH/include/X11/Xauth.h"


# Install the PKG_CONFIG file
install_rawfile_stdin "$PKG_CONFIG_PATH/xau.pc" <<EOF
prefix=$XORG_CONFIGURE_PREFIX
exec_prefix=$XORG_CONFIGURE_EXEC_PREFIX
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: Xau
Description: X authorization file management libary
Version: $VERSION
Requires: xproto
Cflags:
Libs: -lXau
EOF
