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

if [ -z "$VERSION" ]; then VERSION="4.4"; fi

SRCPATH="$KOS_ROOT/binutils/src/nano-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/nano-$VERSION"
if [ "$MODE_FORCE_MAKE" == yes ] || \
 ! [ -f "$OPTPATH/src/nano" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || \
	 ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src"
			download_file \
				"nano-$VERSION.tar.xz" \
				https://nano-editor.org/dist/v4/nano-$VERSION.tar.xz
			cmd tar xvf "nano-$VERSION.tar.xz"
		fi
		apply_patch \
			"$SRCPATH" \
			"$KOS_PATCHES/nano-$VERSION.patch"
		rm -rf "$OPTPATH" > /dev/null 2>&1
		cmd mkdir -p "$OPTPATH"
		cmd cd "$OPTPATH"
		export CC="${CROSS_PREFIX}gcc"
		export CPP="${CROSS_PREFIX}cpp"
		cmd bash ../../../src/nano-$VERSION/configure \
			--bindir="/bin" \
			--datarootdir="/usr/share" \
			--datadir="/usr/share" \
			--sysconfdir="/etc" \
			--localstatedir="/var" \
			--libdir="/usr/$TARGET_LIBPATH" \
			--includedir="/usr/include" \
			--oldincludedir="/usr/include" \
			--infodir="/usr/share/info" \
			--mandir="/usr/share/man" \
			--localedir="/usr/share/locale" \
			--host="$TARGET_NAME-linux-gnu" \
			--disable-threads \
			--disable-nls \
			--with-gnu-ld \
			--without-libiconv-prefix \
			--without-libintl-prefix
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

install_file /bin/nano "$OPTPATH/src/nano"



