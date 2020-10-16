#TEST: require_utility libncurses "$TARGET_SYSROOT/$TARGET_LIBPATH/libncursesw.so"
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


NCURSES_VERSION_MAJOR="6"
NCURSES_VERSION="$NCURSES_VERSION_MAJOR.1"
SRCPATH="$KOS_ROOT/binutils/src/ncurses-$NCURSES_VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/ncurses-$NCURSES_VERSION"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/lib/libncursesw.so" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src"
			download_file \
				"ncurses-$NCURSES_VERSION.tar.gz" \
				ftp://ftp.gnu.org/gnu/ncurses/ncurses-$NCURSES_VERSION.tar.gz
			cmd tar xvf "ncurses-$NCURSES_VERSION.tar.gz"
		fi
		apply_patch "${SRCPATH}" "$KOS_PATCHES/ncurses-$NCURSES_VERSION.patch"
		rm -rf "$OPTPATH" > /dev/null 2>&1
		cmd mkdir -p "$OPTPATH"
		cmd cd "$OPTPATH"
		export CC="${CROSS_PREFIX}gcc"
		export CPP="${CROSS_PREFIX}cpp"
		export CXX="${CROSS_PREFIX}g++"
		export CFLAGS="-ggdb"
		export CXXFLAGS="-ggdb"
		cmd bash ../../../src/ncurses-$NCURSES_VERSION/configure \
			--bindir="/bin" \
			--datarootdir="/usr/share" \
			--datadir="/usr/share" \
			--sysconfdir="/etc" \
			--localstatedir="/var" \
			--libdir="/usr/$TARGET_LIBPATH" \
			--includedir="$KOS_ROOT/kos/include" \
			--oldincludedir="$KOS_ROOT/kos/include" \
			--infodir="/usr/share/info" \
			--mandir="/usr/share/man" \
			--host="$TARGET_NAME-linux-gnu" \
			--enable-widec \
			--without-ada \
			--disable-db-install \
			--without-progs \
			--without-tack \
			--without-tests \
			--without-manpages \
			--with-shared \
			--with-normal \
			--with-debug \
			--with-cxx-shared \
			--disable-big-core \
			--disable-database \
			--with-fallbacks=xterm,unknown \
			--enable-const \
			--enable-ext-mouse \
			--enable-sigwinch \
			--disable-stripping
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi
install_ncurses_library() {
	install_file /$TARGET_LIBPATH/${1}.so.$NCURSES_VERSION_MAJOR "$OPTPATH/lib/${1}.so.$NCURSES_VERSION"
	install_symlink /$TARGET_LIBPATH/${1}.so.$NCURSES_VERSION ${1}.so.$NCURSES_VERSION_MAJOR
	install_symlink /$TARGET_LIBPATH/${1}.so ${1}.so.$NCURSES_VERSION_MAJOR
	install_file_nodisk /$TARGET_LIBPATH/${1}.a "$OPTPATH/lib/${1}.a"
	install_file_nodisk /$TARGET_LIBPATH/${1}_g.a "$OPTPATH/lib/${1}_g.a"
}
install_ncurses_library libformw
install_ncurses_library libmenuw
install_ncurses_library libncursesw
install_ncurses_library libpanelw

cmd mkdir -p "$KOS_ROOT/kos/include/ncursesw"

install_header_ex() {
	install_rawfile "$KOS_ROOT/kos/include/$2" "$1"
	install_rawfile_stdin "$KOS_ROOT/kos/include/ncursesw/$2" <<EOF
#include "../$2"
EOF
}

install_header() {
	install_header_ex "$OPTPATH/include/$1" "$1"
}

install_header eti.h
install_header form.h
install_header menu.h
install_header panel.h
install_header curses.h
install_header ncurses_cfg.h
install_header ncurses_def.h
install_header_ex "$SRCPATH/include/nc_tparm.h" nc_tparm.h

install_rawfile_stdin "$KOS_ROOT/kos/include/ncurses.h" <<EOF
#include "curses.h"
EOF
install_rawfile_stdin "$KOS_ROOT/kos/include/ncursesw/ncurses.h" <<EOF
#include "../curses.h"
EOF
install_header ncurses_dll.h
install_header term.h
install_header_ex "$SRCPATH/include/term_entry.h" term_entry.h
install_header termcap.h
install_header_ex "$SRCPATH/include/tic.h" tic.h
install_header unctrl.h

# C++ headers
install_header_ex "$SRCPATH/c++/cursesapp.h" cursesapp.h
install_header_ex "$SRCPATH/c++/cursesf.h" cursesf.h
install_header_ex "$SRCPATH/c++/cursesm.h" cursesm.h
install_header_ex "$SRCPATH/c++/cursesp.h" cursesp.h
install_header_ex "$SRCPATH/c++/cursesw.h" cursesw.h
install_header_ex "$SRCPATH/c++/cursslk.h" cursslk.h
install_header_ex "$OPTPATH/c++/etip.h" etip.h


