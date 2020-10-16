#TEST: require_utility Xorg/xkbcomp "$PKG_CONFIG_PATH/xkbcomp.pc"
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

require_utility Xorg/libxkbfile "$PKG_CONFIG_PATH/xkbfile.pc"

# xorg-macros
. "$KOS_MISC/utilities/Xorg/misc/xorg-macros.sh"

VERSION="1.4.3"
SRCPATH="$KOS_ROOT/binutils/src/Xorg/xkbcomp-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/Xorg/xkbcomp-$VERSION"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/xkbcomp" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd mkdir -p "$KOS_ROOT/binutils/src/Xorg"
			cmd cd "$KOS_ROOT/binutils/src/Xorg"
			cmd rm -rf "xkbcomp-$VERSION"
			download_file \
				"xkbcomp-$VERSION.tar.gz" \
				"https://www.x.org/releases/individual/app/xkbcomp-$VERSION.tar.gz"
			cmd tar xvf "xkbcomp-$VERSION.tar.gz"
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
			cmd bash "../../../../src/Xorg/xkbcomp-$VERSION/configure" \
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
				--docdir="$XORG_CONFIGURE_DOCDIR_PREFIX/xkbcomp" \
				--htmldir="$XORG_CONFIGURE_HTMLDIR_PREFIX/xkbcomp" \
				--dvidir="$XORG_CONFIGURE_DVIDIR_PREFIX/xkbcomp" \
				--pdfdir="$XORG_CONFIGURE_PDFDIR_PREFIX/xkbcomp" \
				--psdir="$XORG_CONFIGURE_PSDIR_PREFIX/xkbcomp" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--with-xkb-config-root="$XORG_CONFIGURE_XKB_CONFIG_ROOT"
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

install_file /bin/xkbcomp "$OPTPATH/xkbcomp"

# Install the PKG_CONFIG file
install_rawfile_stdin "$PKG_CONFIG_PATH/xkbcomp.pc" <<EOF
prefix=$XORG_CONFIGURE_PREFIX
exec_prefix=$XORG_CONFIGURE_EXEC_PREFIX
bindir="$XORG_CONFIGURE_BINDIR"
datarootdir=$XORG_CONFIGURE_DATAROOTDIR
datadir=$XORG_CONFIGURE_DATADIR
xkbconfigdir=$XORG_CONFIGURE_XKB_CONFIG_ROOT

Description: XKB keymap compiler
Version: $VERSION
EOF
