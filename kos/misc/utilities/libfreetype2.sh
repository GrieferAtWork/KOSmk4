#TEST: require_utility libfreetype2 "$PKG_CONFIG_PATH/freetype2.pc"
# Copyright (c) 2019-2023 Griefer@Work
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
#    Portions Copyright (c) 2019-2023 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

require_utility libzlib  "$PKG_CONFIG_PATH/zlib.pc"
require_utility libbzip2 "$PKG_CONFIG_PATH/bzip2.pc"
require_utility libpng   "$PKG_CONFIG_PATH/libpng.pc"

VERSION="2.10.2"
PC_VERSION="23.2.17"
SO_VERSION_MAJOR="6"
SO_VERSION="$SO_VERSION_MAJOR.17.2"

SRCPATH="$KOS_ROOT/binutils/src/libfreetype2-$VERSION"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/libfreetype2-$VERSION"

# libfreetype2
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/objs/.libs/libfreetype.so.$SO_VERSION" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/config.status" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src"
			cmd rm -rf "freetype-$VERSION"
			cmd rm -rf "libfreetype2-$VERSION"
			if ! [ -f "libfreetype2-$VERSION.tar.gz" ]; then
				download_file \
					"freetype-$VERSION.tar.gz" \
					"https://download.savannah.gnu.org/releases/freetype/freetype-$VERSION.tar.gz"
				cmd mv "freetype-$VERSION.tar.gz" "libfreetype2-$VERSION.tar.gz"
			fi
			cmd tar xvf "libfreetype2-$VERSION.tar.gz"
			cmd mv "freetype-$VERSION" "libfreetype2-$VERSION"
		fi
		# Fix the messed-up header include system as far as that is possible
		if ! [ -f "$SRCPATH/.include_fixed" ]; then
			cmd cd "$KOS_MISC/scripts"
			cmd rundeemon \
				"libfreetype2-fix-headers.dee" \
				"$SRCPATH/include"
			> "$SRCPATH/.include_fixed"
		fi
		cmd rm -rf "$OPTPATH"
		cmd cp -R "$SRCPATH" "$SYSROOT_BINUTILS_TARGET/opt"
		cmd cd "$OPTPATH"
		(
			export CC="${CROSS_PREFIX}gcc"
			export CPP="${CROSS_PREFIX}cpp"
			export CFLAGS="-ggdb"
			export CXX="${CROSS_PREFIX}g++"
			export CXXCPP="${CROSS_PREFIX}cpp"
			export CXXFLAGS="-ggdb"
			cmd bash "configure" \
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
				--docdir="/usr/share/doc/libfreetype2" \
				--htmldir="/usr/share/doc/libfreetype2" \
				--dvidir="/usr/share/doc/libfreetype2" \
				--pdfdir="/usr/share/doc/libfreetype2" \
				--psdir="/usr/share/doc/libfreetype2" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--enable-shared \
				--enable-static \
				--with-gnu-ld \
				--with-zlib=yes \
				--with-bzip2=yes \
				--with-png=yes
			# XXX: Enable in the future? --with-harfbuzz=yes
			# XXX: Enable in the future? --with-brotli=yes
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# Install libraries
install_file           /$TARGET_LIBPATH/libfreetype.so.$SO_VERSION_MAJOR "$OPTPATH/objs/.libs/libfreetype.so.$SO_VERSION"
install_symlink_nodisk /$TARGET_LIBPATH/libfreetype.so.$SO_VERSION       "libfreetype.so.$SO_VERSION_MAJOR"
install_symlink_nodisk /$TARGET_LIBPATH/libfreetype.so                   "libfreetype.so.$SO_VERSION_MAJOR"
install_file_nodisk    /$TARGET_LIBPATH/libfreetype.a                    "$OPTPATH/objs/.libs/libfreetype.a"

# Install headers
if ! [ -f "$KOS_ROOT/kos/include/freetype/freetype.h" ]; then
	cmd rm -rf "$KOS_ROOT/kos/include/freetype"
	cmd cp -R -v "$OPTPATH/include/freetype" "$KOS_ROOT/kos/include"
fi
install_rawfile "$KOS_ROOT/kos/include/ft2build.h" "$OPTPATH/include/ft2build.h"

# Install the PKG_CONFIG file
install_rawfile_stdin "$PKG_CONFIG_PATH/freetype2.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: FreeType 2
URL: https://freetype.org
Description: A free, high-quality, and portable font engine.
Version: $PC_VERSION
Requires:
Requires.private: zlib, bzip2, libpng
Libs: -lfreetype
Libs.private:
Cflags:
EOF
