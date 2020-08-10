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

# xorg-macros
. "$KOS_MISC/utilities/misc/xorg-macros.sh"

VERSION="1.3.1"

SO_VERSION_MAJOR="6"
SO_VERSION="$SO_VERSION_MAJOR.4.0"

SRCPATH="$KOS_ROOT/binutils/src/x/libXext-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/x/libXext-$VERSION"

require_program xsltproc

# libXext
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/src/.libs/libXext.so.$SO_VERSION" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src/x"
			cmd rm -rf "libXext-$VERSION"
			download_file \
				"libXext-$VERSION.tar.gz" \
				"https://www.x.org/releases/X11R7.7/src/everything/libXext-$VERSION.tar.gz"
			cmd tar xvf "libXext-$VERSION.tar.gz"
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
			cmd bash "../../../../src/x/libXext-$VERSION/configure" \
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
				--docdir="/usr/share/doc/libXext" \
				--htmldir="/usr/share/doc/libXext" \
				--dvidir="/usr/share/doc/libXext" \
				--pdfdir="/usr/share/doc/libXext" \
				--psdir="/usr/share/doc/libXext" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--enable-shared \
				--enable-static \
				--disable-malloc0returnsnull \
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

# Install the PKG_CONFIG file
if ! [ -f "$PKG_CONFIG_PATH/xext.pc" ]; then
	cmd mkdir -p "$PKG_CONFIG_PATH"
	cat > "$PKG_CONFIG_PATH/xext.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: Xext
Description: Misc X Extension Library
Version: $VERSION
Requires: xextproto
Requires.private: x11
Cflags:
Libs: -lXext
EOF
fi

# Install libraries
install_file /$TARGET_LIBPATH/libXext.so.$SO_VERSION_MAJOR "$OPTPATH/src/.libs/libXext.so.$SO_VERSION"
install_symlink /$TARGET_LIBPATH/libXext.so.$SO_VERSION libXext.so.$SO_VERSION_MAJOR
install_symlink /$TARGET_LIBPATH/libXext.so libXext.so.$SO_VERSION_MAJOR
install_file_nodisk /$TARGET_LIBPATH/libXext.a "$OPTPATH/src/.libs/libXext.a"

# Install headers
install_header() {
	install_rawfile \
		"$KOS_ROOT/kos/include/X11/extensions/$1" \
		"$SRCPATH/include/X11/extensions/$1"
}
install_header "dpms.h"
install_header "extutil.h"
install_header "MITMisc.h"
install_header "multibuf.h"
install_header "security.h"
install_header "shape.h"
install_header "sync.h"
install_header "Xag.h"
install_header "Xcup.h"
install_header "Xdbe.h"
install_header "XEVI.h"
install_header "Xext.h"
install_header "Xge.h"
install_header "XLbx.h"
install_header "XShm.h"
install_header "xtestext1.h"
