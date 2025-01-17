# Copyright (c) 2019-2025 Griefer@Work
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
#    Portions Copyright (c) 2019-2025 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
exit 0

# depends: libXext

# xorg-macros
. "$KOS_MISC/utilities/misc/xorg-macros.sh"

VERSION="1.1.3"

SO_VERSION_MAJOR="1"
SO_VERSION="$SO_VERSION_MAJOR.0.0"

SRCPATH="$KOS_ROOT/binutils/src/x/libXxf86dga-$VERSION"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/x/libXxf86dga-$VERSION"

# libXxf86dga
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/src/.libs/libXxf86dga.so.$SO_VERSION" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src/x"
			cmd rm -rf "libXxf86dga-$VERSION"
			download_file \
				"libXxf86dga-$VERSION.tar.gz" \
				"https://www.x.org/releases/X11R7.7/src/lib/libXxf86dga-$VERSION.tar.gz"
			cmd tar xvf "libXxf86dga-$VERSION.tar.gz"
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
			cmd bash "../../../../src/x/libXxf86dga-$VERSION/configure" \
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
				--docdir="/usr/share/doc/libXxf86dga" \
				--htmldir="/usr/share/doc/libXxf86dga" \
				--dvidir="/usr/share/doc/libXxf86dga" \
				--pdfdir="/usr/share/doc/libXxf86dga" \
				--psdir="/usr/share/doc/libXxf86dga" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--enable-shared \
				--enable-static \
				--disable-malloc0returnsnull \
				--with-gnu-ld
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# Install the PKG_CONFIG file
if ! [ -f "$PKG_CONFIG_PATH/xxf86dga.pc.pc" ]; then
	cmd mkdir -p "$PKG_CONFIG_PATH"
	cat > "$PKG_CONFIG_PATH/xxf86dga.pc.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: Xxf86dga
Description: XFree86 Direct Graphics Access Extension Library
Version: $VERSION
Requires: xf86dgaproto
Requires.private: x11 xext
Cflags:
Libs: -lXxf86dga
EOF
fi

# Install libraries
install_file /$TARGET_LIBPATH/libXxf86dga.so.$SO_VERSION_MAJOR "$OPTPATH/src/.libs/libXxf86dga.so.$SO_VERSION"
install_symlink_nodisk /$TARGET_LIBPATH/libXxf86dga.so.$SO_VERSION libXxf86dga.so.$SO_VERSION_MAJOR
install_symlink_nodisk /$TARGET_LIBPATH/libXxf86dga.so libXxf86dga.so.$SO_VERSION_MAJOR
install_file_nodisk /$TARGET_LIBPATH/libXxf86dga.a "$OPTPATH/src/.libs/libXxf86dga.a"

# Install headers
install_header() {
	install_rawfile \
		"$KOS_ROOT/kos/include/X11/extensions/$1" \
		"$SRCPATH/include/X11/extensions/$1"
}
install_header "Xxf86dga.h"
install_header "xf86dga1.h"
