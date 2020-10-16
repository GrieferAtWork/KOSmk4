#TEST: require_utility Xorg/libX11 "$PKG_CONFIG_PATH/x11.pc"
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
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/xextproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/xtrans.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/kbproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/inputproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/xf86bigfontproto.pc"
require_utility Xorg/libxcb    "$PKG_CONFIG_PATH/xcb.pc"

# xorg-macros
. "$KOS_MISC/utilities/Xorg/misc/xorg-macros.sh"

VERSION="1.6.12"

SRCPATH="$KOS_ROOT/binutils/src/Xorg/libX11-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/Xorg/libX11-$VERSION"

# libX11
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/src/.libs/libX11.so.6.3.0" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure.ac" ]; then
			cmd mkdir -p "$KOS_ROOT/binutils/src/Xorg"
			cmd cd "$KOS_ROOT/binutils/src/Xorg"
			cmd rm -rf "libX11-$VERSION"
			download_file \
				"libX11-$VERSION.tar.gz" \
				"https://www.x.org/releases/individual/lib/libX11-$VERSION.tar.gz"
			cmd tar xvf "libX11-$VERSION.tar.gz"
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
			# configure thinks that mmap isn't working without this :(
			cat > "$OPTPATH/config.site" <<EOF
ac_cv_func_mmap_fixed_mapped=yes
EOF
			export CONFIG_SITE="$OPTPATH/config.site"
			cmd bash "../../../../src/Xorg/libX11-$VERSION/configure" \
				--prefix="$XORG_CONFIGURE_PREFIX" \
				--exec-prefix="$XORG_CONFIGURE_EXEC_PREFIX" \
				--bindir="$XORG_CONFIGURE_BINDIR" \
				--sbindir="$XORG_CONFIGURE_SBINDIR" \
				--libexecdir="$XORG_CONFIGURE_LIBEXECDIR" \
				--sysconfdir="$XORG_CONFIGURE_SYSCONFDIR" \
				--sharedstatedir="$XORG_CONFIGURE_SHAREDSTATEDIR" \
				--localstatedir="$XORG_CONFIGURE_LOCALSTATEDIR" \
				--runstatedir="$XORG_CONFIGURE_RUNSTATEDIR" \
				--libdir="$XORG_CONFIGURE_LIBDIR" \
				--includedir="$XORG_CONFIGURE_INCLUDEDIR" \
				--oldincludedir="$XORG_CONFIGURE_OLDINCLUDEDIR" \
				--datarootdir="$XORG_CONFIGURE_DATAROOTDIR" \
				--datadir="$XORG_CONFIGURE_DATADIR" \
				--infodir="$XORG_CONFIGURE_INFODIR" \
				--localedir="$XORG_CONFIGURE_LOCALEDIR" \
				--mandir="$XORG_CONFIGURE_MANDIR" \
				--docdir="$XORG_CONFIGURE_DOCDIR_PREFIX/libX11" \
				--htmldir="$XORG_CONFIGURE_HTMLDIR_PREFIX/libX11" \
				--dvidir="$XORG_CONFIGURE_DVIDIR_PREFIX/libX11" \
				--pdfdir="$XORG_CONFIGURE_PDFDIR_PREFIX/libX11" \
				--psdir="$XORG_CONFIGURE_PSDIR_PREFIX/libX11" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--enable-shared \
				--enable-static \
				--enable-largefile \
				--disable-specs \
				--enable-unix-transport \
				--disable-tcp-transport \
				--disable-ipv6 \
				--enable-local-transport \
				--disable-loadable-i18n \
				--enable-loadable-xcursor \
				--enable-xthreads \
				--enable-xlocaledir \
				--enable-xf86bigfont \
				--enable-xkb \
				--disable-lint-library \
				--disable-malloc0returnsnull \
				--with-gnu-ld \
				--without-xmlto \
				--without-fop \
				--without-launchd \
				--without-lint \
				--with-locale-lib-dir="$XORG_CONFIGURE_LOCALE_LIB_DIR"
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# install_library name V1 V2 V3
install_library() {
	install_file        /$TARGET_LIBPATH/$1.so.$2                "$OPTPATH/src/.libs/$1.so.$2.$3.$4"
	install_symlink     /$TARGET_LIBPATH/$1.so.$2.$3.$4 $1.so.$2
	install_symlink     /$TARGET_LIBPATH/$1.so $1.so.$2
	install_file_nodisk /$TARGET_LIBPATH/$1.a                    "$OPTPATH/src/.libs/$1.a"
}

# Install libraries
install_library libX11     6 3 0
install_library libX11-xcb 1 0 0

# This library also installs a bunch of config files:
install_file /usr/lib/X11/Xcms.txt              "$SRCPATH/src/xcms/Xcms.txt"
install_file /usr/share/X11/XErrorDB            "$SRCPATH/src/XErrorDB"
install_file /usr/share/X11/locale/locale.dir   "$OPTPATH/nls/locale.dir"
install_file /usr/share/X11/locale/locale.alias "$OPTPATH/nls/locale.alias"
install_file /usr/share/X11/locale/compose.dir  "$OPTPATH/nls/compose.dir"

install_locale() {
	install_file /usr/share/X11/locale/$1/Compose     "$OPTPATH/nls/$1/Compose"
	install_file /usr/share/X11/locale/$1/XI18N_OBJS  "$SRCPATH/nls/$1/XI18N_OBJS"
	install_file /usr/share/X11/locale/$1/XLC_LOCALE  "$OPTPATH/nls/$1/XLC_LOCALE"
}

cmd cd "$OPTPATH/nls"
for NAME in *; do
	if [ -f "$NAME/Compose" ]; then
		install_locale "$NAME"
	fi
done

# Install headers
install_header() {
	install_rawfile                    \
		"$KOS_ROOT/kos/include/X11/$1" \
		"$SRCPATH/include/X11/$1"
}

install_rawfile                            \
	"$KOS_ROOT/kos/include/X11/XlibConf.h" \
	"$OPTPATH/include/X11/XlibConf.h"
install_header "XKBlib.h"
install_header "Xcms.h"
install_header "Xlib.h"
install_header "Xlibint.h"
install_header "Xlocale.h"
install_header "Xresource.h"
install_header "Xutil.h"
install_header "cursorfont.h"
install_header "Xregion.h"
install_header "ImUtil.h"
install_header "Xlib-xcb.h"
install_header "extensions/XKBgeom.h"


# Install the PKG_CONFIG files
install_rawfile_stdin "$PKG_CONFIG_PATH/x11-xcb.pc" <<EOF
prefix=$XORG_CONFIGURE_PREFIX
exec_prefix=$XORG_CONFIGURE_EXEC_PREFIX
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: X11 XCB
Description: X Library XCB interface
Version: $VERSION
Requires: x11 xcb
Cflags:
Libs: -lX11-xcb
EOF

install_rawfile_stdin "$PKG_CONFIG_PATH/x11.pc" <<EOF
prefix=$XORG_CONFIGURE_PREFIX
exec_prefix=$XORG_CONFIGURE_EXEC_PREFIX
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

xthreadlib=-lc

Name: X11
Description: X Library
Version: $VERSION
Requires: xproto kbproto
Requires.private: xcb >= 1.11.1
Cflags:
Libs: -lX11
Libs.private: -lc
EOF
