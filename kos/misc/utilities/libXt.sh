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

# depends libx11
# depends xproto
# depends libICE
# depends libSM

# xorg-macros
. "$KOS_MISC/utilities/misc/xorg-macros.sh"

VERSION="1.1.3"

SO_VERSION_MAJOR="6"
SO_VERSION="$SO_VERSION_MAJOR.0.0"

SRCPATH="$KOS_ROOT/binutils/src/x/libXt-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/x/libXt-$VERSION"

require_program xsltproc

# libXt
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/src/.libs/libXt.so.$SO_VERSION" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src/x"
			cmd rm -rf "libXt-$VERSION"
			download_file \
				"libXt-$VERSION.tar.gz" \
				"https://www.x.org/releases/X11R7.7/src/everything/libXt-$VERSION.tar.gz"
			cmd tar xvf "libXt-$VERSION.tar.gz"
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
			cmd bash "../../../../src/x/libXt-$VERSION/configure" \
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
				--docdir="/usr/share/doc/libXt" \
				--htmldir="/usr/share/doc/libXt" \
				--dvidir="/usr/share/doc/libXt" \
				--pdfdir="/usr/share/doc/libXt" \
				--psdir="/usr/share/doc/libXt" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--enable-shared \
				--enable-static \
				--disable-malloc0returnsnull \
				--with-gnu-ld \
				--without-xmlto \
				--without-fop \
				--with-appdefaultdir="/usr/share/X11/app-defaults"
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# Install the PKG_CONFIG file
if ! [ -f "$PKG_CONFIG_PATH/xt.pc" ]; then
	cmd mkdir -p "$PKG_CONFIG_PATH"
	cat > "$PKG_CONFIG_PATH/xt.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include
appdefaultdir=/usr/share/X11/app-defaults

Name: Xt
Description: X Toolkit Library
Version: $VERSION
Requires: xproto x11
Requires.private: ice sm
Cflags:
Libs: -lXt
EOF
fi

# Install libraries
install_file /$TARGET_LIBPATH/libXt.so.$SO_VERSION_MAJOR "$OPTPATH/src/.libs/libXt.so.$SO_VERSION"
install_symlink /$TARGET_LIBPATH/libXt.so.$SO_VERSION libXt.so.$SO_VERSION_MAJOR
install_symlink /$TARGET_LIBPATH/libXt.so libXt.so.$SO_VERSION_MAJOR
install_file_nodisk /$TARGET_LIBPATH/libXt.a "$OPTPATH/src/.libs/libXt.a"

# Install headers
install_header() {
	install_rawfile \
		"$KOS_ROOT/kos/include/X11/$1" \
		"$SRCPATH/include/X11/$1"
}
install_rawfile "$KOS_ROOT/kos/include/X11/StringDefs.h" "$OPTPATH/include/X11/StringDefs.h"
install_rawfile "$KOS_ROOT/kos/include/X11/Shell.h"      "$OPTPATH/include/X11/Shell.h"

install_header "Composite.h"
install_header "CompositeP.h"
install_header "ConstrainP.h"
install_header "Constraint.h"
install_header "Core.h"
install_header "CoreP.h"
install_header "Intrinsic.h"
install_header "IntrinsicP.h"
install_header "Object.h"
install_header "ObjectP.h"
install_header "RectObj.h"
install_header "RectObjP.h"
install_header "ResConfigP.h"
install_header "ShellP.h"
install_header "Vendor.h"
install_header "VendorP.h"
install_header "CallbackI.h"
install_header "ConvertI.h"
install_header "CreateI.h"
install_header "EventI.h"
install_header "HookObjI.h"
install_header "InitialI.h"
install_header "IntrinsicI.h"
install_header "PassivGraI.h"
install_header "ResourceI.h"
install_header "SelectionI.h"
install_header "ShellI.h"
install_header "ThreadsI.h"
install_header "TranslateI.h"
install_header "VarargsI.h"
install_header "Xtos.h"
