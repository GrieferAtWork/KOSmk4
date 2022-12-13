#TEST: require_utility libffi "$PKG_CONFIG_PATH/libffi.pc"
# Copyright (c) 2019-2022 Griefer@Work
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
#    Portions Copyright (c) 2019-2022 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

VERSION="3.3"
SHLIB_VERSION_MAJOR="7"
SHLIB_VERSION="$SHLIB_VERSION_MAJOR.1.0"

SRCPATH="$KOS_ROOT/binutils/src/libffi-$VERSION"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/libffi-$VERSION"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/.libs/libffi.so.$SHLIB_VERSION" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src"
			download_file \
				"libffi-$VERSION.tar.gz" \
				"https://github.com/libffi/libffi/releases/download/v$VERSION/libffi-$VERSION.tar.gz"
			cmd tar xvf "libffi-$VERSION.tar.gz"
		fi
		rm -rf "$OPTPATH" > /dev/null 2>&1
		cmd mkdir -p "$OPTPATH"
		cmd cd "$OPTPATH"
		export CC="${CROSS_PREFIX}gcc"
		export CPP="${CROSS_PREFIX}cpp"
		export CFLAGS="-ggdb"
		export CXX="${CROSS_PREFIX}g++"
		export CXXCPP="${CROSS_PREFIX}cpp"
		export CXXFLAGS="-ggdb"
		cmd bash ../../../src/libffi-$VERSION/configure \
			--prefix="/" \
			--exec-prefix="/" \
			--bindir="/bin" \
			--sbindir="/bin" \
			--sysconfdir="/etc" \
			--localstatedir="/var" \
			--libdir="/$TARGET_LIBPATH" \
			--includedir="/usr/include" \
			--oldincludedir="/usr/include" \
			--datarootdir="/usr/share" \
			--datadir="/usr/share" \
			--infodir="/usr/share/info" \
			--localedir="/usr/share/locale" \
			--mandir="/usr/share/man" \
			--docdir="/usr/share/doc/libffi" \
			--htmldir="/usr/share/doc/libffi" \
			--dvidir="/usr/share/doc/libffi" \
			--pdfdir="/usr/share/doc/libffi" \
			--psdir="/usr/share/doc/libffi" \
			--build="$(gcc -dumpmachine)" \
			--host="$TARGET_NAME-linux-gnu" \
			--target="$TARGET_NAME-linux-gnu" \
			--enable-shared \
			--disable-multi-os-directory \
			--enable-symvers=no \
			--with-gnu-ld
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# Install libraries
install_file           /$TARGET_LIBPATH/libffi.so.$SHLIB_VERSION_MAJOR "$OPTPATH/.libs/libffi.so.$SHLIB_VERSION"
install_symlink_nodisk /$TARGET_LIBPATH/libffi.so.$SHLIB_VERSION       "libffi.so.$SHLIB_VERSION_MAJOR"
install_symlink_nodisk /$TARGET_LIBPATH/libffi.so                      "libffi.so.$SHLIB_VERSION_MAJOR"
install_file_nodisk    /$TARGET_LIBPATH/libffi.a                       "$OPTPATH/.libs/libffi.a"
install_file_nodisk    /$TARGET_LIBPATH/libffi_convenience.a           "$OPTPATH/.libs/libffi_convenience.a"

# Install headers
if [ "$TARGET_NAME" == "i386" ] || [ "$TARGET_NAME" == "x86_64" ]; then
	# Required for multi-arch
	TARGET_EXT="32"
	if [ "$TARGET_NAME" == "x86_64" ]; then
		TARGET_EXT="64"
	fi
	install_rawfile "$KOS_ROOT/kos/include/$TARGET_INCPATH/_libffi/ffi${TARGET_EXT}.h" "$OPTPATH/include/ffi.h"
	install_rawfile "$KOS_ROOT/kos/include/$TARGET_INCPATH/_libffi/ffitarget${TARGET_EXT}.h" "$OPTPATH/include/ffitarget.h"
	install_rawfile_stdin "$KOS_ROOT/kos/include/$TARGET_INCPATH/ffi.h" <<EOF
#ifndef _I386_KOS_FFI_H
#define _I386_KOS_FFI_H 1

#include <hybrid/host.h>

#ifdef __x86_64__
#include "_libffi/ffi64.h"
#else /* __x86_64__ */
#include "_libffi/ffi32.h"
#endif /* !__x86_64__ */

/* Appease DIY, non-standard configure tools (*cough* python *cough*) */
#ifndef LIBFFI_H
#define LIBFFI_H
#endif /* !LIBFFI_H */
#endif /* !_I386_KOS_FFI_H */
EOF
	install_rawfile_stdin "$KOS_ROOT/kos/include/$TARGET_INCPATH/ffitarget.h" <<EOF
#ifndef _I386_KOS_FFITARGET_H
#define _I386_KOS_FFITARGET_H 1

#include <hybrid/host.h>

#ifdef __x86_64__
#include "_libffi/ffitarget64.h"
#else /* __x86_64__ */
#include "_libffi/ffitarget32.h"
#endif /* !__x86_64__ */

/* Appease DIY, non-standard configure tools */
#ifndef LIBFFI_TARGET_H
#define LIBFFI_TARGET_H
#endif /* !LIBFFI_TARGET_H */
#endif /* !_I386_KOS_FFITARGET_H */
EOF
else
	install_rawfile "$KOS_ROOT/kos/include/$TARGET_INCPATH/ffi.h"       "$OPTPATH/include/ffi.h"
	install_rawfile "$KOS_ROOT/kos/include/$TARGET_INCPATH/ffitarget.h" "$OPTPATH/include/ffitarget.h"
fi

# Install the PKG_CONFIG file
install_rawfile_stdin "$PKG_CONFIG_PATH/libffi.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
toolexeclibdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: libffi
Description: Library supporting Foreign Function Interfaces
Version: $VERSION
Libs: -lffi
Cflags:
EOF
