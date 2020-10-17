#TEST: require_utility fontconfig "$PKG_CONFIG_PATH/fontconfig.pc"
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

require_utility libfreetype2 "$PKG_CONFIG_PATH/freetype2.pc"
require_utility libexpat     "$PKG_CONFIG_PATH/expat.pc"

VERSION="2.13.92"
SO_VERSION_MAJOR="1"
SO_VERSION="$SO_VERSION_MAJOR.12.0"

SRCPATH="$KOS_ROOT/binutils/src/fontconfig-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/fontconfig-$VERSION"

require_program gperf

# fontconfig
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/src/.libs/libfontconfig.so.$SO_VERSION" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/config.status" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src"
			cmd rm -rf "fontconfig-$VERSION"
			download_file \
				"fontconfig-$VERSION.tar.gz" \
				"https://www.freedesktop.org/software/fontconfig/release/fontconfig-$VERSION.tar.gz"
			cmd tar xvf "fontconfig-$VERSION.tar.gz"
		fi
		cmd cd "$SRCPATH"
		apply_patch "$SRCPATH" "$KOS_PATCHES/fontconfig-$VERSION.patch"
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
			cmd bash "../../../src/fontconfig-$VERSION/configure" \
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
				--docdir="/usr/share/doc/fontconfig" \
				--htmldir="/usr/share/doc/fontconfig" \
				--dvidir="/usr/share/doc/fontconfig" \
				--pdfdir="/usr/share/doc/fontconfig" \
				--psdir="/usr/share/doc/fontconfig" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--enable-shared \
				--enable-static \
				--enable-largefile \
				--disable-libxml2 \
				--disable-docs \
				--with-gnu-ld
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

if ! [ -f "$OPTPATH/fonts.conf" ]; then
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT fonts.conf
fi

# Install executables
install_file /bin/fc-cache    "$OPTPATH/fc-cache/fc-cache"
install_file /bin/fc-cat      "$OPTPATH/fc-cat/fc-cat"
install_file /bin/fc-conflist "$OPTPATH/fc-conflist/fc-conflist"
install_file /bin/fc-list     "$OPTPATH/fc-list/fc-list"
install_file /bin/fc-match    "$OPTPATH/fc-match/fc-match"
install_file /bin/fc-pattern  "$OPTPATH/fc-pattern/fc-pattern"
install_file /bin/fc-query    "$OPTPATH/fc-query/fc-query"
install_file /bin/fc-scan     "$OPTPATH/fc-scan/fc-scan"
install_file /bin/fc-validate "$OPTPATH/fc-validate/fc-validate"

# Install config files
install_file /etc/fonts/fonts.conf                                           "$OPTPATH/fonts.conf"
install_file /etc/fonts/conf.d/10-hinting-slight.conf                        "$SRCPATH/conf.d/10-hinting-slight.conf"
install_file /etc/fonts/conf.d/10-scale-bitmap-fonts.conf                    "$SRCPATH/conf.d/10-scale-bitmap-fonts.conf"
install_file /etc/fonts/conf.d/20-unhint-small-vera.conf                     "$SRCPATH/conf.d/20-unhint-small-vera.conf"
install_file /etc/fonts/conf.d/30-metric-aliases.conf                        "$SRCPATH/conf.d/30-metric-aliases.conf"
install_file /etc/fonts/conf.d/40-nonlatin.conf                              "$SRCPATH/conf.d/40-nonlatin.conf"
install_file /etc/fonts/conf.d/45-generic.conf                               "$SRCPATH/conf.d/45-generic.conf"
install_file /etc/fonts/conf.d/45-latin.conf                                 "$SRCPATH/conf.d/45-latin.conf"
install_file /etc/fonts/conf.d/49-sansserif.conf                             "$SRCPATH/conf.d/49-sansserif.conf"
install_file /etc/fonts/conf.d/50-user.conf                                  "$SRCPATH/conf.d/50-user.conf"
install_file /etc/fonts/conf.d/51-local.conf                                 "$SRCPATH/conf.d/51-local.conf"
install_file /etc/fonts/conf.d/60-generic.conf                               "$SRCPATH/conf.d/60-generic.conf"
install_file /etc/fonts/conf.d/60-latin.conf                                 "$SRCPATH/conf.d/60-latin.conf"
install_file /etc/fonts/conf.d/65-fonts-persian.conf                         "$SRCPATH/conf.d/65-fonts-persian.conf"
install_file /etc/fonts/conf.d/65-nonlatin.conf                              "$SRCPATH/conf.d/65-nonlatin.conf"
install_file /etc/fonts/conf.d/69-unifont.conf                               "$SRCPATH/conf.d/69-unifont.conf"
install_file /etc/fonts/conf.d/80-delicious.conf                             "$SRCPATH/conf.d/80-delicious.conf"
install_file /etc/fonts/conf.d/90-synthetic.conf                             "$SRCPATH/conf.d/90-synthetic.conf"
install_file /etc/fonts/conf.d/README                                        "$SRCPATH/conf.d/README"
install_file /usr/share/fontconfig/conf.avail/05-reset-dirs-sample.conf      "$SRCPATH/conf.d/05-reset-dirs-sample.conf"
install_file /usr/share/fontconfig/conf.avail/09-autohint-if-no-hinting.conf "$SRCPATH/conf.d/09-autohint-if-no-hinting.conf"
install_file /usr/share/fontconfig/conf.avail/10-autohint.conf               "$SRCPATH/conf.d/10-autohint.conf"
install_file /usr/share/fontconfig/conf.avail/10-hinting-full.conf           "$SRCPATH/conf.d/10-hinting-full.conf"
install_file /usr/share/fontconfig/conf.avail/10-hinting-medium.conf         "$SRCPATH/conf.d/10-hinting-medium.conf"
install_file /usr/share/fontconfig/conf.avail/10-hinting-none.conf           "$SRCPATH/conf.d/10-hinting-none.conf"
install_file /usr/share/fontconfig/conf.avail/10-hinting-slight.conf         "$SRCPATH/conf.d/10-hinting-slight.conf"
install_file /usr/share/fontconfig/conf.avail/10-no-sub-pixel.conf           "$SRCPATH/conf.d/10-no-sub-pixel.conf"
install_file /usr/share/fontconfig/conf.avail/10-scale-bitmap-fonts.conf     "$SRCPATH/conf.d/10-scale-bitmap-fonts.conf"
install_file /usr/share/fontconfig/conf.avail/10-sub-pixel-bgr.conf          "$SRCPATH/conf.d/10-sub-pixel-bgr.conf"
install_file /usr/share/fontconfig/conf.avail/10-sub-pixel-rgb.conf          "$SRCPATH/conf.d/10-sub-pixel-rgb.conf"
install_file /usr/share/fontconfig/conf.avail/10-sub-pixel-vbgr.conf         "$SRCPATH/conf.d/10-sub-pixel-vbgr.conf"
install_file /usr/share/fontconfig/conf.avail/10-sub-pixel-vrgb.conf         "$SRCPATH/conf.d/10-sub-pixel-vrgb.conf"
install_file /usr/share/fontconfig/conf.avail/10-unhinted.conf               "$SRCPATH/conf.d/10-unhinted.conf"
install_file /usr/share/fontconfig/conf.avail/11-lcdfilter-default.conf      "$SRCPATH/conf.d/11-lcdfilter-default.conf"
install_file /usr/share/fontconfig/conf.avail/11-lcdfilter-legacy.conf       "$SRCPATH/conf.d/11-lcdfilter-legacy.conf"
install_file /usr/share/fontconfig/conf.avail/11-lcdfilter-light.conf        "$SRCPATH/conf.d/11-lcdfilter-light.conf"
install_file /usr/share/fontconfig/conf.avail/20-unhint-small-vera.conf      "$SRCPATH/conf.d/20-unhint-small-vera.conf"
install_file /usr/share/fontconfig/conf.avail/25-unhint-nonlatin.conf        "$SRCPATH/conf.d/25-unhint-nonlatin.conf"
install_file /usr/share/fontconfig/conf.avail/30-metric-aliases.conf         "$SRCPATH/conf.d/30-metric-aliases.conf"
install_file /usr/share/fontconfig/conf.avail/35-lang-normalize.conf         "$OPTPATH/conf.d/35-lang-normalize.conf"
install_file /usr/share/fontconfig/conf.avail/40-nonlatin.conf               "$SRCPATH/conf.d/40-nonlatin.conf"
install_file /usr/share/fontconfig/conf.avail/45-generic.conf                "$SRCPATH/conf.d/45-generic.conf"
install_file /usr/share/fontconfig/conf.avail/45-latin.conf                  "$SRCPATH/conf.d/45-latin.conf"
install_file /usr/share/fontconfig/conf.avail/49-sansserif.conf              "$SRCPATH/conf.d/49-sansserif.conf"
install_file /usr/share/fontconfig/conf.avail/50-user.conf                   "$SRCPATH/conf.d/50-user.conf"
install_file /usr/share/fontconfig/conf.avail/51-local.conf                  "$SRCPATH/conf.d/51-local.conf"
install_file /usr/share/fontconfig/conf.avail/60-generic.conf                "$SRCPATH/conf.d/60-generic.conf"
install_file /usr/share/fontconfig/conf.avail/60-latin.conf                  "$SRCPATH/conf.d/60-latin.conf"
install_file /usr/share/fontconfig/conf.avail/65-fonts-persian.conf          "$SRCPATH/conf.d/65-fonts-persian.conf"
install_file /usr/share/fontconfig/conf.avail/65-khmer.conf                  "$SRCPATH/conf.d/65-khmer.conf"
install_file /usr/share/fontconfig/conf.avail/65-nonlatin.conf               "$SRCPATH/conf.d/65-nonlatin.conf"
install_file /usr/share/fontconfig/conf.avail/69-unifont.conf                "$SRCPATH/conf.d/69-unifont.conf"
install_file /usr/share/fontconfig/conf.avail/70-no-bitmaps.conf             "$SRCPATH/conf.d/70-no-bitmaps.conf"
install_file /usr/share/fontconfig/conf.avail/70-yes-bitmaps.conf            "$SRCPATH/conf.d/70-yes-bitmaps.conf"
install_file /usr/share/fontconfig/conf.avail/80-delicious.conf              "$SRCPATH/conf.d/80-delicious.conf"
install_file /usr/share/fontconfig/conf.avail/90-synthetic.conf              "$SRCPATH/conf.d/90-synthetic.conf"
install_file /usr/share/gettext/its/fontconfig.its                           "$SRCPATH/its/fontconfig.its"
install_file /usr/share/gettext/its/fontconfig.loc                           "$SRCPATH/its/fontconfig.loc"
install_file /usr/share/xml/fontconfig/fonts.dtd                             "$SRCPATH/fonts.dtd"
install_mkdir /var/cache/fontconfig


# Install libraries
install_file        /$TARGET_LIBPATH/libfontconfig.so.$SO_VERSION_MAJOR "$OPTPATH/src/.libs/libfontconfig.so.$SO_VERSION"
install_symlink     /$TARGET_LIBPATH/libfontconfig.so.$SO_VERSION       libfontconfig.so.$SO_VERSION_MAJOR
install_symlink     /$TARGET_LIBPATH/libfontconfig.so                   libfontconfig.so.$SO_VERSION_MAJOR
install_file_nodisk /$TARGET_LIBPATH/libfontconfig.a                    "$OPTPATH/src/.libs/libfontconfig.a"

# Install headers
install_rawfile "$KOS_ROOT/kos/include/fontconfig/fcfreetype.h" "$SRCPATH/fontconfig/fcfreetype.h"
install_rawfile "$KOS_ROOT/kos/include/fontconfig/fcprivate.h"  "$SRCPATH/fontconfig/fcprivate.h"
install_rawfile "$KOS_ROOT/kos/include/fontconfig/fontconfig.h" "$SRCPATH/fontconfig/fontconfig.h"

# Install the PKG_CONFIG file
install_rawfile_stdin "$PKG_CONFIG_PATH/fontconfig.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include
sysconfdir=/etc
localstatedir=/var
PACKAGE=fontconfig
confdir=/etc/fonts
cachedir=/var/cache/fontconfig

Name: Fontconfig
Description: Font configuration and customization library
Version: $VERSION
Requires: freetype2 >= 21.0.15
Requires.private: expat
Libs: -lfontconfig
Libs.private:
Cflags:
EOF
