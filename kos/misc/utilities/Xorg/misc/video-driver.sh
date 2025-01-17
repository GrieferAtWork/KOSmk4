# Copyright (c) 2019-2025 Griefer@Work
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
#    Portions Copyright (c) 2019-2025 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

# VERSION=2.3.1
# NAME=xf86-video-vesa
# DRIVER_NAME=vesa

# xorg-macros
. "$KOS_MISC/utilities/Xorg/misc/xorg-macros.sh"

if test -z "$DRIVER_NAME"; then
	# DRIVER_NAME = NAME.lsstrip("xf86-video-");
	DRIVER_NAME="${NAME/#xf86-video-}"
fi

SRCPATH="$KOS_ROOT/binutils/src/Xorg/$NAME-$VERSION"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/Xorg/$NAME-$VERSION"
BINFILE="$OPTPATH/src/.libs/${DRIVER_NAME}_drv.so"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$BINFILE" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd mkdir -p "$KOS_ROOT/binutils/src/Xorg"
			cmd cd "$KOS_ROOT/binutils/src/Xorg"
			cmd rm -rf "$NAME-$VERSION"
			if test -z "$URL"; then
				URL="https://www.x.org/releases/individual/driver/${NAME}-${VERSION}.tar.gz"
			fi
			download_file "$NAME-$VERSION.tar.gz" "$URL"
			cmd tar xvf "$NAME-$VERSION.tar.gz"
		fi
		cmd cd "$SRCPATH"
		if test -z "$PATCH"; then
			PATCH="$KOS_PATCHES/$NAME-$VERSION.patch"
		fi
		if [ -f "$PATCH" ]; then
			apply_patch "$SRCPATH" "$PATCH"
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
			cmd bash "../../../../src/Xorg/$NAME-$VERSION/configure" \
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
				--docdir="$XORG_CONFIGURE_DOCDIR_PREFIX/$NAME" \
				--htmldir="$XORG_CONFIGURE_HTMLDIR_PREFIX/$NAME" \
				--dvidir="$XORG_CONFIGURE_DVIDIR_PREFIX/$NAME" \
				--pdfdir="$XORG_CONFIGURE_PDFDIR_PREFIX/$NAME" \
				--psdir="$XORG_CONFIGURE_PSDIR_PREFIX/$NAME" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--disable-static \
				--enable-shared \
				--with-gnu-ld
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

install_file /$TARGET_LIBPATH/xorg/modules/drivers/${DRIVER_NAME}_drv.so "$BINFILE"
