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
exit 0

# xorg-macros
. "$KOS_MISC/utilities/misc/xorg-macros.sh"

VERSION="1.6.1"
SRCPATH="$KOS_ROOT/binutils/src/x/xf86-input-keyboard-$VERSION"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/x/xf86-input-keyboard-$VERSION"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/src/.libs/kbd_drv.so" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src/x"
			cmd rm -rf "xf86-input-keyboard-$VERSION"
			download_file \
				"xf86-input-keyboard-$VERSION.tar.gz" \
				"https://www.x.org/releases/X11R7.7/src/everything/xf86-input-keyboard-$VERSION.tar.gz"
			cmd tar xvf "xf86-input-keyboard-$VERSION.tar.gz"
		fi
		apply_patch "$SRCPATH" "$KOS_PATCHES/xf86-input-keyboard-$VERSION.patch"
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
			cmd bash "../../../../src/x/xf86-input-keyboard-$VERSION/configure" \
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
				--docdir="/usr/share/doc/xf86-input-keyboard" \
				--htmldir="/usr/share/doc/xf86-input-keyboard" \
				--dvidir="/usr/share/doc/xf86-input-keyboard" \
				--pdfdir="/usr/share/doc/xf86-input-keyboard" \
				--psdir="/usr/share/doc/xf86-input-keyboard" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--with-gnu-ld \
				--with-xorg-module-dir="/$TARGET_LIBPATH/xorg/modules"
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

install_file /lib/xorg/modules/drivers/kbd_drv.so "$OPTPATH/src/.libs/kbd_drv.so"
