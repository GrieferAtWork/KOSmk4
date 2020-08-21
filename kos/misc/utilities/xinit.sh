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

# depends xorg-server

# xorg-macros
. "$KOS_MISC/utilities/misc/xorg-macros.sh"

VERSION="1.3.2"
SRCPATH="$KOS_ROOT/binutils/src/x/xinit-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/x/xinit-$VERSION"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/xinit" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src/x"
			cmd rm -rf "xinit-$VERSION"
			download_file \
				"xinit-$VERSION.tar.gz" \
				"https://www.x.org/archive//individual/app/xinit-$VERSION.tar.gz"
			cmd tar xvf "xinit-$VERSION.tar.gz"
		fi
		apply_patch "$SRCPATH" "$KOS_PATCHES/xinit-$VERSION.patch"
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
			cmd bash "../../../../src/x/xinit-$VERSION/configure" \
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
				--docdir="/usr/share/doc/xinit" \
				--htmldir="/usr/share/doc/xinit" \
				--dvidir="/usr/share/doc/xinit" \
				--pdfdir="/usr/share/doc/xinit" \
				--psdir="/usr/share/doc/xinit" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--with-twm="/bin/twm" \
				--with-xserver="/bin/Xorg" \
				--with-xinit="/bin/xinit" \
				--with-xinitdir="/$TARGET_LIBPATH/X11/xinit" \
				--with-xterm="/bin/xterm" \
				--with-xclock="/bin/xclock" \
				--with-xauth="/bin/xauth" \
				--with-xrdb="/bin/xrdb" \
				--with-xmodmap="/bin/xmodmap"
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

#Usage: `xinit twm`
install_file /bin/xinit "$OPTPATH/xinit"


# xinit: /etc/X11/xinit/xinitrc
# xinit: /etc/X11/xinit/xserverrc
# xinit: /usr/bin/startx
# xinit: /usr/bin/xinit
# xinit: /usr/share/doc/xinit/NEWS.Debian.gz
# xinit: /usr/share/doc/xinit/changelog.Debian.gz
# xinit: /usr/share/doc/xinit/copyright
# xinit: /usr/share/man/man1/startx.1.gz
# xinit: /usr/share/man/man1/xinit.1.gz

