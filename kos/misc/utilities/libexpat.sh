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

# depends: zlib

VERSION="2.2.9"
SO_VERSION_MAJOR="1"
SO_VERSION="$SO_VERSION_MAJOR.6.11"

SRCPATH="$KOS_ROOT/binutils/src/libexpat-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/libexpat-$VERSION"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/lib/.libs/libexpat.so.$SO_VERSION" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src"
			cmd rm -rf "expat-$VERSION"
			cmd rm -rf "libexpat-$VERSION"
			if ! [ -f "libexpat-$VERSION.tar.gz" ]; then
				download_file \
					"expat-$VERSION.tar.gz" \
					"https://github.com/libexpat/libexpat/releases/download/R_${VERSION//./_}/expat-$VERSION.tar.gz"
				cmd mv "expat-$VERSION.tar.gz" "libexpat-$VERSION.tar.gz"
			fi
			cmd tar xvf "libexpat-$VERSION.tar.gz"
			cmd mv "expat-$VERSION" "libexpat-$VERSION"
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
			# configure things that mmap isn't working without this :(
			cat > "$OPTPATH/config.site" <<EOF
ac_cv_func_mmap_fixed_mapped=yes
EOF
			export CONFIG_SITE="$OPTPATH/config.site"
			cmd bash ../../../src/libexpat-$VERSION/configure \
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
				--docdir="/usr/share/doc/expat" \
				--htmldir="/usr/share/doc/expat" \
				--dvidir="/usr/share/doc/expat" \
				--pdfdir="/usr/share/doc/expat" \
				--psdir="/usr/share/doc/expat" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--enable-shared \
				--enable-static \
				--with-gnu-ld \
				--without-examples \
				--without-tests
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# Install the PKG_CONFIG file
if ! [ -f "$PKG_CONFIG_PATH/expat.pc" ]; then
	cmd mkdir -p "$PKG_CONFIG_PATH"
	cat > "$PKG_CONFIG_PATH/expat.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: expat
Version: $VERSION
Description: expat XML parser
URL: http://www.libexpat.org
Libs: -lexpat
Cflags:
EOF
fi

# Install libraries
install_file /$TARGET_LIBPATH/libexpat.so.$SO_VERSION_MAJOR "$OPTPATH/lib/.libs/libexpat.so.$SO_VERSION"
install_symlink /$TARGET_LIBPATH/libexpat.so.$SO_VERSION libexpat.so.$SO_VERSION_MAJOR
install_symlink /$TARGET_LIBPATH/libexpat.so libexpat.so.$SO_VERSION_MAJOR
install_file_nodisk /$TARGET_LIBPATH/libexpat.a "$OPTPATH/lib/.libs/libexpat.a"

# Install headers
install_rawfile "$KOS_ROOT/kos/include/expat.h" "$SRCPATH/lib/expat.h"
install_rawfile "$KOS_ROOT/kos/include/expat_external.h" "$SRCPATH/lib/expat_external.h"
install_rawfile "$KOS_ROOT/kos/include/$TARGET_INCPATH/expat_config.h" "$OPTPATH/expat_config.h"
