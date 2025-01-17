#TEST: require_utility myman "$SYSROOT_BIN_TARGET_COMMON/bin/myman"
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

require_utility libncurses "$SYSROOT_BIN_TARGET_COMMON/$TARGET_LIBPATH/libncursesw.so"

if [ -z "$VERSION" ]; then VERSION="2009-10-30"; fi

SRCPATH="$KOS_ROOT/binutils/src/myman-$VERSION"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/myman-$VERSION"
EXEFILE="$OPTPATH/myman"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$EXEFILE" ]; then
	if ! [ -f "$SRCPATH/configure" ]; then
		cmd cd "$KOS_ROOT/binutils/src"
		download_file \
			"myman-wip-$VERSION.tar.gz" \
			https://sourceforge.net/projects/myman/files/myman-cvs/myman-cvs-$VERSION/myman-wip-$VERSION.tar.gz
		cmd tar xvf "myman-wip-$VERSION.tar.gz"
		cmd mv "myman-wip-$VERSION" "myman-$VERSION"
	fi
	apply_patch "${SRCPATH}" "$KOS_PATCHES/myman-$VERSION.patch"
	rm -r "$OPTPATH" > /dev/null 2>&1
	cmd mkdir -p "$OPTPATH"

	# Copy level files to opt/myman-files
	cmd mkdir -p "$OPTPATH/myman-files/lvl"
	cmd mkdir -p "$OPTPATH/myman-files/chr"
	cmd mkdir -p "$OPTPATH/myman-files/spr"

	cmd cd "$SRCPATH"
	cmd cp lvl/*.txt "$OPTPATH/myman-files/lvl"
	cmd cp chr/*.txt "$OPTPATH/myman-files/chr"
	cmd cp spr/*.txt "$OPTPATH/myman-files/spr"

	# The ./configure script of this program is insanely broken and not at all designed
	# for cross-compiling! Instead, try to piece the broken bits together ourself
	cat > "$OPTPATH/config.h" <<EOF
#ifndef MYMAN_CONFIG_H_INCLUDED
#define MYMAN_CONFIG_H_INCLUDED 1
#define MYMAN_GUESS_H_INCLUDED 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#include <hybrid/typecore.h>

/* System features */
#define HAVE_UNISTD_H 1
#define HAVE_SETENV 1
#define HAVE_PUTENV 1
#define HAVE_RAISE 1
#define HAVE_LOCALE_H 1
#define HAVE_IO_H 1
#define HAVE_UNIXIO_H 0
#define HAVE_SYS_TIME_H 1
#define HAVE_LANGINFO_H 0
#define LIT64(x) __UINT64_C(x)
#define myman_gettimeofday gettimeofday
#undef MYGETOPT_H
#undef MYGETOPT

/* Binding config */
#define USE_SDL_MIXER 0
#undef USE_SDL

/* Installation config */
#undef PRIVATEDATADIR
#define MAZEDIR      "/usr/share/myman/lvl"
#define TILEDIR      "/usr/share/myman/chr"
#define SPRITEDIR    "/usr/share/myman/spr"
#define MAZEFILE     "/usr/share/myman/lvl/maze.txt"
#define TILEFILE     "/usr/share/myman/chr/chr1.txt"
#define SPRITEFILE   "/usr/share/myman/spr/spr1.txt"
#define MYMANVERSION "0.7.1"
#define HTM_SUFFIX   ".html"
#define TXT_SUFFIX   ".txt"
#define builtin_tilefile   TILEFILE
#define builtin_spritefile SPRITEFILE
#define builtin_mazefile   MAZEFILE

#endif /* !MYMAN_CONFIG_H_INCLUDED */
EOF
	set_archpath
	INVOKE_CC="$CC -g -I$OPTPATH -I$SRCPATH/inc -DHAVE_CONFIG_H=1"
	TS_OBJECTS=""
	# Compile source files
	for SRCFILE in utils logic myman; do
		echo "Compile: $INVOKE_CC -c -o $OPTPATH/$SRCFILE.o $SRCPATH/src/$SRCFILE.c"
		cmd "$INVOKE_CC" -c -o "$OPTPATH/$SRCFILE.o" "$SRCPATH/src/$SRCFILE.c" &
		TS_OBJECTS="$TS_OBJECTS $SRCFILE.o"
	done
	cmd wait
	cmd cd "$OPTPATH"
	echo "Link: $CC -g -o $EXEFILE $TS_OBJECTS -lncursesw"
	cmd "$CC" -g -o "$EXEFILE" "$TS_OBJECTS" -lncursesw
fi

# Install myman to disk
install_file /bin/myman "$EXEFILE"
install_path_hardcopy /usr/share/myman "$OPTPATH/myman-files"
