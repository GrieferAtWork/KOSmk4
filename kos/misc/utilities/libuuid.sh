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

VERSION="1.0.3"
SO_VERSION_MAJOR="1"
SO_VERSION="$SO_VERSION_MAJOR.0.0"

SRCPATH="$KOS_ROOT/binutils/src/libuuid-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/libuuid-$VERSION"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/.libs/libuuid.so.$SO_VERSION" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src"
			download_file \
				"libuuid-${VERSION}.tar.gz" \
				"https://sourceforge.net/projects/libuuid/files/libuuid-$VERSION.tar.gz"
			cmd tar xvf "libuuid-${VERSION}.tar.gz"
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
			cmd bash ../../../src/libuuid-$VERSION/configure \
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
				--docdir="/usr/share/doc/libuuid" \
				--htmldir="/usr/share/doc/libuuid" \
				--dvidir="/usr/share/doc/libuuid" \
				--pdfdir="/usr/share/doc/libuuid" \
				--psdir="/usr/share/doc/libuuid" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--enable-shared \
				--enable-static \
				--with-gnu-ld
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# Install the PKG_CONFIG file
if ! [ -f "$PKG_CONFIG_PATH/uuid.pc" ]; then
	cmd mkdir -p "$PKG_CONFIG_PATH"
	cat > "$PKG_CONFIG_PATH/uuid.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: uuid
Description: Universally unique id library
Version: $VERSION
Requires:
Cflags:
Libs: -luuid
EOF
fi

# Install libraries
install_file /$TARGET_LIBPATH/libuuid.so.$SO_VERSION_MAJOR "$OPTPATH/.libs/libuuid.so.$SO_VERSION"
install_symlink /$TARGET_LIBPATH/libuuid.so.$SO_VERSION libuuid.so.$SO_VERSION_MAJOR
install_symlink /$TARGET_LIBPATH/libuuid.so libuuid.so.$SO_VERSION_MAJOR
install_file_nodisk /$TARGET_LIBPATH/libuuid.a "$OPTPATH/.libs/libuuid.a"

install_rawfile "$KOS_ROOT/kos/include/uuid/uuid.h" "$SRCPATH/uuid.h"

install_proxy_c_header() {
	if ! [ -f "$1" ]; then
		echo "Installing file $1"
		echo "#include \"$2\"" > "$1"
	else
		echo "Installing file $1 (up to date)"
	fi
}
install_proxy_c_header "$KOS_ROOT/kos/include/uuid.h" "uuid/uuid.h"
