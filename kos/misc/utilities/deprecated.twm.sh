# Copyright (c) 2019-2024 Griefer@Work
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
#    Portions Copyright (c) 2019-2024 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
exit 0

# depends xorg-server
# depends libx11
# depends libXext
# depends libXt
# depends libXmu
# depends libICE
# depends libSM
# depends xproto

# xorg-macros
. "$KOS_MISC/utilities/misc/xorg-macros.sh"

VERSION="1.0.7"
SRCPATH="$KOS_ROOT/binutils/src/x/twm-$VERSION"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/x/twm-$VERSION"

# NOTE: On cygwin, you must install `bison`
require_program yacc

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/src/twm" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src/x"
			cmd rm -rf "twm-$VERSION"
			download_file \
				"twm-$VERSION.tar.gz" \
				"https://www.x.org/archive//individual/app/twm-$VERSION.tar.gz"
			cmd tar xvf "twm-$VERSION.tar.gz"
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
			cmd bash "../../../../src/x/twm-$VERSION/configure" \
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
				--docdir="/usr/share/doc/twm" \
				--htmldir="/usr/share/doc/twm" \
				--dvidir="/usr/share/doc/twm" \
				--pdfdir="/usr/share/doc/twm" \
				--psdir="/usr/share/doc/twm" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu"
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

install_file /bin/twm "$OPTPATH/src/twm"
