#TEST: require_utility Xorg/xkeyboard-config "$PKG_CONFIG_PATH/xkeyboard-config.pc"
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

require_utility Xorg/xkbcomp "$PKG_CONFIG_PATH/xkbcomp.pc"

. "$KOS_MISC/utilities/Xorg/misc/xorg-macros.sh"

# We need a secondary version of "/bin/xkbcomp" that is compiled
# for the host machine, as the process of making xkeyboard-config
# files inbokes the xkbcomp compiler.
# This is where we download+configure+make that second variant,
# as well as modify our $PATH such that it can be found below.
# Note that despite this, KOS still needs a secondary xkbcomp
# compiler at runtime, as xorg-server will execv("/bin/xkbcomp")
# in order to compile keyboard maps.
. "$KOS_MISC/utilities/Xorg/misc/host-xkbcomp.sh"

# These two you have to install yourself on your host
# On cygwin, they're found in:
#    - intltool-update: intltool-0.51.0-1
#    - iconv:           libiconv-1.14-2
require_program intltool-update
require_program iconv

VERSION="2.31"

SRCPATH="$KOS_ROOT/binutils/src/Xorg/xkeyboard-config-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/Xorg/xkeyboard-config-$VERSION"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/rules/base" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd mkdir -p "$KOS_ROOT/binutils/src/Xorg"
			cmd cd "$KOS_ROOT/binutils/src/Xorg"
			cmd rm -rf "xkeyboard-config-$VERSION"
			download_file \
				"xkeyboard-config-$VERSION.tar.gz" \
				"https://www.x.org/releases/individual/data/xkeyboard-config/xkeyboard-config-$VERSION.tar.gz"
			cmd tar xvf "xkeyboard-config-$VERSION.tar.gz"
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
			cmd bash "../../../../src/Xorg/xkeyboard-config-$VERSION/configure" \
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
				--docdir="$XORG_CONFIGURE_DOCDIR_PREFIX/xkeyboard-config" \
				--htmldir="$XORG_CONFIGURE_HTMLDIR_PREFIX/xkeyboard-config" \
				--dvidir="$XORG_CONFIGURE_DVIDIR_PREFIX/xkeyboard-config" \
				--pdfdir="$XORG_CONFIGURE_PDFDIR_PREFIX/xkeyboard-config" \
				--psdir="$XORG_CONFIGURE_PSDIR_PREFIX/xkeyboard-config" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--with-xkb-base="$XORG_CONFIGURE_XKB_BASE" \
				--without-libiconv-prefix \
				--without-libintl-prefix \
				--with-gnu-ld
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# my_install_file WHERE [WHAT]
my_install_file() {
	DST="/usr/share/X11/xkb$1"
	SRC="$2"
	if test -z "$SRC"; then
		SRC="$SRCPATH/${1#/}"
	fi
	install_file "$DST" "$SRC"
}

my_install_files_from_folder() {
	cmd cd "$SRCPATH/$1"
	for  FILE in *; do
		if [[ $FILE == "Makefile.am" ]] || \
		   [[ $FILE == "Makefile.in" ]] \
		; then
			:
		else
			if [ -d "$SRCPATH/$1/$FILE" ]; then
				my_install_files_from_folder $1/$FILE
			else
				my_install_file /$1/$FILE
			fi
		fi
	done
}


my_install_files_from_folder compat
my_install_files_from_folder geometry
my_install_files_from_folder keycodes
my_install_files_from_folder symbols
my_install_files_from_folder types

my_install_file /rules/base                   "$OPTPATH/rules/base"
my_install_file /rules/base.lst               "$OPTPATH/rules/base.lst"
my_install_file /rules/evdev                  "$OPTPATH/rules/evdev"
my_install_file /rules/evdev.lst              "$OPTPATH/rules/evdev.lst"
my_install_file /rules/base.extras.xml        "$SRCPATH/rules/base.extras.xml"
my_install_file /rules/base.xml               "$SRCPATH/rules/base.xml"
my_install_file /rules/evdev.extras.xml       "$SRCPATH/rules/evdev.extras.xml"
my_install_file /rules/evdev.xml              "$SRCPATH/rules/evdev.xml"
my_install_file /rules/README
my_install_file /rules/xfree98
my_install_file /rules/xkb.dtd

# Install the PKG_CONFIG file
install_rawfile_stdin "$PKG_CONFIG_PATH/xkeyboard-config.pc" <<EOF
prefix=$XORG_CONFIGURE_PREFIX
datarootdir=$XORG_CONFIGURE_DATAROOTDIR
datadir=$XORG_CONFIGURE_DATADIR
xkb_base=$XORG_CONFIGURE_XKB_BASE

Name: XKeyboardConfig
Description: X Keyboard configuration data
Version: $VERSION
EOF
