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

# depends: xproto
# depends: xextproto
# depends: xtrans
# depends: xcb
# depends: kbproto
# depends: inputproto
# depends: xf86bigfontproto

# xorg-macros
. "$KOS_MISC/utilities/misc/xorg-macros.sh"

VERSION="1.5.0"

SRCPATH="$KOS_ROOT/binutils/src/x/libX11-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/x/libX11-$VERSION"

# libX11
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/src/.libs/libX11.so.6.3.0" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure.ac" ]; then
			cmd cd "$KOS_ROOT/binutils/src/x"
			cmd rm -rf "libX11-$VERSION"
			download_file \
				"libX11-$VERSION.tar.gz" \
				"https://www.x.org/releases/X11R7.7/src/everything/libX11-$VERSION.tar.gz"
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
			cmd bash "../../../../src/x/libX11-$VERSION/configure" \
				--prefix="/" \
				--exec-prefix="/" \
				--bindir="/bin" \
				--sbindir="/bin" \
				--libexecdir="/libexec" \
				--sysconfdir="/etc" \
				--sharedstatedir="/usr/com" \
				--localstatedir="/var" \
				--libdir="/$TARGET_LIBPATH" \
				--includedir="/usr/include" \
				--oldincludedir="/usr/include" \
				--datarootdir="/usr/share" \
				--datadir="/usr/share" \
				--infodir="/usr/share/info" \
				--localedir="/usr/share/locale" \
				--mandir="/usr/share/man" \
				--docdir="/usr/share/doc/libX11" \
				--htmldir="/usr/share/doc/libX11" \
				--dvidir="/usr/share/doc/libX11" \
				--pdfdir="/usr/share/doc/libX11" \
				--psdir="/usr/share/doc/libX11" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--enable-shared \
				--enable-static \
				--enable-unix-transport \
				--disable-tcp-transport \
				--disable-ipv6 \
				--enable-local-transport \
				--disable-secure-rpc \
				--disable-loadable-i18n \
				--enable-loadable-xcursor \
				--enable-xthreads \
				--enable-xlocaledir \
				--enable-xf86bigfont \
				--disable-lint-library \
				--disable-malloc0returnsnull \
				--with-gnu-ld \
				--without-xmlto \
				--without-fop \
				--with-local-transport-order=TODO \
				--without-launchd \
				--without-lint
		) || exit $?
		# TODO: --enable-composecache  (requires <langinfo.h>)
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# Install the PKG_CONFIG file
if ! [ -f "$PKG_CONFIG_PATH/x11.pc" ]; then
	cmd mkdir -p "$PKG_CONFIG_PATH"
	cat > "$PKG_CONFIG_PATH/x11.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

xthreadlib=-lc

Name: X11
Description: X Library
Version: $VERSION
Requires: xproto kbproto
Requires.private: xcb >= 1.1.92
Cflags:
Libs: -lX11
Libs.private: -lc
EOF
fi

if ! [ -f "$PKG_CONFIG_PATH/x11-xcb.pc" ]; then
	cmd mkdir -p "$PKG_CONFIG_PATH"
	cat > "$PKG_CONFIG_PATH/x11-xcb.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: X11 XCB
Description: X Library XCB interface
Version: $VERSION
Requires: x11 xcb
Cflags:
Libs: -lX11-xcb
EOF
fi

# install_library name V1 V2 V3
install_library() {
	install_file /$TARGET_LIBPATH/$1.so.$2 "$OPTPATH/src/.libs/$1.so.$2.$3.$4"
	install_symlink /$TARGET_LIBPATH/$1.so.$2.$3.$4 $1.so.$2
	install_symlink /$TARGET_LIBPATH/$1.so $1.so.$2
	install_file_nodisk /$TARGET_LIBPATH/$1.a "$OPTPATH/src/.libs/$1.a"
}

# Install libraries
install_library libX11 6 3 0
install_library libX11-xcb 1 0 0

# This library also installs a bunch of config files:
install_file /usr/lib/X11/Xcms.txt "$SRCPATH/src/xcms/Xcms.txt"
install_file /usr/share/X11/XErrorDB "$SRCPATH/src/XErrorDB"
#install_file /usr/share/X11/locale/locale.dir "$OPTPATH/nls/locale.dir"
#install_file /usr/share/X11/locale/locale.alias "$OPTPATH/nls/locale.alias"
#install_file /usr/share/X11/locale/compose.dir "$OPTPATH/nls/compose.dir"
#    - /usr/share/X11/locale/*/*    (Hundreds of files)


# Install headers
install_header() {
	install_rawfile \
		"$KOS_ROOT/kos/include/X11/$1" \
		"$SRCPATH/include/X11/$1"
}
install_rawfile \
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

