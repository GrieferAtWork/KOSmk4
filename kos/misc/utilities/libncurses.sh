#TEST: require_utility libncurses "$SYSROOT_BIN_TARGET_COMMON/$TARGET_LIBPATH/libncursesw.so"
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


PACKAGE_NAME=libncurses-6.3
PACKAGE_URL="https://invisible-mirror.net/archives/ncurses/ncurses-6.3.tar.gz"

CONFIGURE=(
	"--without-ada"
	"--with-cxx"
	"--with-cxx-binding"
	"--disable-db-install"
	"--without-progs"
	"--without-tack"
	"--with-curses-h"
	"--with-cxx-shared"
	"--with-dlsym"
	"--disable-database"
	"--with-fallbacks=xterm,unknown"
	"--disable-big-core"
	"--disable-termcap"
	"--disable-getcap"
	"--disable-getcap-cache"
	"--disable-home-terminfo"
	"--enable-ext-funcs"
	"--enable-sp-funcs"
	"--disable-term-driver"
	"--enable-const"
	"--disable-ext-colors"
	"--enable-ext-mouse"
	"--enable-ext-putwin"
	"--disable-no-padding"
	"--enable-sigwinch"
	"--disable-tcap-names"

	"--without-pthread"              # No need for thread-safety
	"--disable-pthreads-eintr"       # No need for thread-safety
	"--disable-reentrant"            # No need for thread-safety
	"--disable-weak-symbols"         # If you can do without weak symbols, that'd be poggers.
	"--disable-stripping"            # Retain debug info; it can be used by the builtin debugger
	"--enable-widec"                 # Wide-character support? -- Yes, please!

#	"--enable-assertions"

	"--disable-safe-sprintf"         # Enabling this causes curses to implement its own `sprintf(3)'. -- Just use the system one ;)
	"--enable-stdnoreturn"           # It's there if you want to use it...

)

case "$(uname -o)" in
Cygwin)
	# Work-around build bug if cygwin:
	# >> In file included from .../binutils/src/libncurses-6.3/ncurses/tinfo/make_keys.c:45:
	# >> ../ncurses/names.c:354:5: error: variable 'boolnames' definition is marked dllimport
	# >>   354 | DCL(boolnames) = {
	# >>       |     ^~~~~~~~~
	# >> ...
	CONFIGURE+=("--with-build-cflags=-DBUILDING_NCURSES")
	;;

**) ;;
esac

INSTALL_SKIP="
/bin/ncurses6-config
/bin/ncursesw6-config
"


# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"

# Install the non-*w-suffixed libraries as symlinks to the wide-enabled ones
# Note that the wide-enabled libraries still contain all of the functions that
# are exposed by system headers, and are expected by non-wide-enabled programs.
# Binary compatibility between the wide-enabled and non-wide-enabled libncurses
# doesn't matter here, because we never build the non-wide-enabled ones, and
# link everything against the ones with wide-character support built-in
for name in form menu ncurses++ ncurses panel; do
	install_symlink_nodisk /$TARGET_LIBPATH/lib${name}.a      lib${name}w.a
	install_symlink_nodisk /$TARGET_LIBPATH/lib${name}.so     lib${name}w.so
	install_symlink_nodisk /$TARGET_LIBPATH/lib${name}.so.6   lib${name}w.so.6
	install_symlink_nodisk /$TARGET_LIBPATH/lib${name}.so.6.3 lib${name}w.so.6.3
	install_symlink_nodisk /$TARGET_LIBPATH/lib${name}_g.a    lib${name}w_g.a
	if test x"$MODE_DRYRUN" != xno; then
		echo "> pkg_config '/usr/share/pkgconfig/${name}.pc' (alias for '/usr/share/pkgconfig/${name}w.pc')"
	else
		dst_filename="$PKG_CONFIG_PATH/${name}.pc"
		short_dst_filename="$dst_filename"
		if [[ "$short_dst_filename" == "$KOS_ROOT/"* ]]; then
			short_dst_filename="\$KOS_ROOT${short_dst_filename:${#KOS_ROOT}}"
		fi
		printf "\e[${UI_COLCFG_FILETYPE}mpkg\e[m \e[${UI_COLCFG_PATH_RAW}m%-${UI_PATHCOL_WIDTH}s\e[m [raw]" "$short_dst_filename" >&2
		if ! [ -L "$dst_filename" ]; then
			unlink "$dst_filename" > /dev/null 2>&1
			cmd ln -s "${name}w.pc" "$dst_filename"
			echo -e "\e[${UI_COLCFG_OK}m ok\e[m" >&2
		else
			echo -e "\e[${UI_COLCFG_OK}m already installed\e[m" >&2
		fi
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

# The following header is actually derived from libc4/5,
# but references curses, so we can only install it now!
install_rawfile_stdin "$KOS_ROOT/kos/include/bsd/curses.h" <<EOF
/* (#) Portability: libc4/5 (/include/bsd/curses.h) */
#include "../curses.h"
#include "../sgtty.h"
EOF




# C++ headers
install_header_ex "$SRCPATH/c++/cursesapp.h" cursesapp.h
install_header_ex "$SRCPATH/c++/cursesf.h" cursesf.h
install_header_ex "$SRCPATH/c++/cursesm.h" cursesm.h
install_header_ex "$SRCPATH/c++/cursesp.h" cursesp.h
install_header_ex "$SRCPATH/c++/cursesw.h" cursesw.h
install_header_ex "$SRCPATH/c++/cursslk.h" cursslk.h
install_header_ex "$OPTPATH/c++/etip.h" etip.h
