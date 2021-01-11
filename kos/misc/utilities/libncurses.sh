#TEST: require_utility libncurses "$TARGET_SYSROOT/$TARGET_LIBPATH/libncursesw.so"
# Copyright (c) 2019-2021 Griefer@Work
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
#    Portions Copyright (c) 2019-2021 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.


PACKAGE_NAME=libncurses-6.1
PACKAGE_URL="ftp://ftp.gnu.org/gnu/ncurses/ncurses-6.1.tar.gz"

CONFIGURE=""
CONFIGURE="$CONFIGURE --without-ada"
CONFIGURE="$CONFIGURE --with-cxx"
CONFIGURE="$CONFIGURE --with-cxx-binding"
CONFIGURE="$CONFIGURE --disable-db-install"
CONFIGURE="$CONFIGURE --without-progs"
CONFIGURE="$CONFIGURE --without-tack"
CONFIGURE="$CONFIGURE --with-curses-h"
CONFIGURE="$CONFIGURE --with-cxx-shared"
CONFIGURE="$CONFIGURE --with-dlsym"
CONFIGURE="$CONFIGURE --disable-database"
CONFIGURE="$CONFIGURE --with-fallbacks=xterm,unknown"
CONFIGURE="$CONFIGURE --disable-big-core"
CONFIGURE="$CONFIGURE --disable-termcap"
CONFIGURE="$CONFIGURE --disable-getcap"
CONFIGURE="$CONFIGURE --disable-getcap-cache"
CONFIGURE="$CONFIGURE --disable-home-terminfo"
CONFIGURE="$CONFIGURE --enable-ext-funcs"
CONFIGURE="$CONFIGURE --enable-sp-funcs"
CONFIGURE="$CONFIGURE --disable-term-driver"
CONFIGURE="$CONFIGURE --enable-const"
CONFIGURE="$CONFIGURE --disable-ext-colors"
CONFIGURE="$CONFIGURE --enable-ext-mouse"
CONFIGURE="$CONFIGURE --enable-ext-putwin"
CONFIGURE="$CONFIGURE --disable-no-padding"
CONFIGURE="$CONFIGURE --enable-sigwinch"
CONFIGURE="$CONFIGURE --disable-tcap-names"
CONFIGURE="$CONFIGURE --without-pthread"
CONFIGURE="$CONFIGURE --disable-pthreads-eintr"
CONFIGURE="$CONFIGURE --disable-weak-symbols"
CONFIGURE="$CONFIGURE --disable-reentrant"
CONFIGURE="$CONFIGURE --disable-stripping"
#CONFIGURE="$CONFIGURE --enable-assertions"
CONFIGURE="$CONFIGURE --enable-widec"

INSTALL_SKIP=""
INSTALL_SKIP="$INSTALL_SKIP /bin/ncurses6-config"
INSTALL_SKIP="$INSTALL_SKIP /bin/ncursesw6-config"

# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"

# Install the non-*w-suffixed libraries as symlinks to the wide-enabled ones
# Note that the wide-enabled libraries still contain all of the functions that
# are exposed by system headers, and are expected by non-wide-enabled programs.
# Binary compatibility between the wide-enabled and non-wide-enabled libncurses
# doesn't matter here, because we never build the non-wide-enabled one, and
# link everything against the one with wide-character support built-in
for name in form menu ncurses++ ncurses panel; do
	install_symlink_nodisk /$TARGET_LIBPATH/lib${name}.a      lib${name}w.a
	install_symlink_nodisk /$TARGET_LIBPATH/lib${name}.so     lib${name}w.so
	install_symlink_nodisk /$TARGET_LIBPATH/lib${name}.so.6   lib${name}w.so.6
	install_symlink_nodisk /$TARGET_LIBPATH/lib${name}.so.6.1 lib${name}w.so.6.1
	install_symlink_nodisk /$TARGET_LIBPATH/lib${name}_g.a    lib${name}w_g.a
	if test x"$MODE_DRYRUN" != xno; then
		echo "> pkg_config '/usr/share/pkgconfig/${name}.pc' (alias for '/usr/share/pkgconfig/${name}w.pc')"
	else
		dst_filename="$PKG_CONFIG_PATH/${name}.pc"
		echo "Installing pkg_config file $dst_filename"
		unlink "$dst_filename" > /dev/null 2>&1
		cmd ln -s "${name}w.pc" "$dst_filename"
	fi
done

# Install convenience headers and headers that may have been missing
cmd mkdir -p "$KOS_ROOT/kos/include/ncurses"
cmd mkdir -p "$KOS_ROOT/kos/include/ncursesw"

install_header_ex() {
	install_rawfile "$KOS_ROOT/kos/include/$2" "$1"
	install_rawfile_stdin "$KOS_ROOT/kos/include/ncurses/$2" <<EOF
#include "../$2"
EOF
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
install_rawfile_stdin "$KOS_ROOT/kos/include/ncurses/ncurses.h" <<EOF
#include "../curses.h"
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


