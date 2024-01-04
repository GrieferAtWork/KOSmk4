#TEST: require_utility python "$PKG_CONFIG_PATH/python-2.7.pc"
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

require_utility libexpat   "$PKG_CONFIG_PATH/expat.pc"
require_utility libffi     "$SYSROOT_BIN_TARGET_COMMON/$TARGET_LIBPATH/libffi.so"
require_utility libncurses "$SYSROOT_BIN_TARGET_COMMON/$TARGET_LIBPATH/libncursesw.so"
require_utility libzlib    "$PKG_CONFIG_PATH/zlib.pc"

PACKAGE_URL="https://www.python.org/ftp/python/2.7.16/Python-2.7.16.tar.xz"

# Additions configure options
CONFIGURE=(
	"--enable-ipv6"
	"--enable-unicode=ucs4"
	"--with-suffix=no"
	"--with-system-ffi=yes"
	"--with-system-expat"
	"--with-signal-module"
	"--with-threads"
	"--with-wctype-functions"
	"--with-libm=no"
	"--with-libc=-lc"
	"--with-computed-gotos"
)

_gm_hook_before_make_or_install() {
	# This is needed to appease python's annoying build system, which
	# doesn't seem to understand that due to multi-arch (which is something
	# that's quite standartized now-a-days), KOS (just like linux) has
	# multiple system include paths ('/kos/include/i386-kos/' and '/kos/include/')
	# As such, it only searches the later, and even more annoyingly, it also
	# searches it for a line that starts with `#define LIBFFI_H`...
	# Anyways. Make it happy by defining that file while we're running make...
	cat > "$KOS_ROOT/kos/include/ffi.h" <<EOF
#include <$TARGET_INCPATH/ffi.h>
#if 0
#define LIBFFI_H
#endif
EOF

	# Another annoying thing with python+libffi: Python checks which libraries
	# exist in a specific order, in which `libffi_convenience` comes before
	# the actual `libffi`. Problem here is that ffi_convenience only comes as
	# a static library, so if we let python see it, we'd end up linking libffi
	# statically (which would completely counteract the whole idea behind using
	# the system libffi, rather than python's builtin, already-static one)
	mv	"$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH/libffi_convenience.a" \
		"$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH/.libffi_convenience.a" \
		2>&1 > /dev/null
}
_gm_hook_after_mask_or_install() {
	unlink "$KOS_ROOT/kos/include/ffi.h" 2>&1 > /dev/null
	mv	"$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH/.libffi_convenience.a" \
		"$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH/libffi_convenience.a" \
		2>&1 > /dev/null
}

GM_HOOK_BEFORE_MAKE=_gm_hook_before_make_or_install
GM_HOOK_AFTER_MAKE=_gm_hook_after_mask_or_install

# Also need the same tricks during install (ugh...)
GM_HOOK_BEFORE_INSTALL=_gm_hook_before_make_or_install
GM_HOOK_AFTER_INSTALL=_gm_hook_after_mask_or_install


# build_missing_module <name> <sources...>
build_missing_module() {
	local name="$1"
	shift
	if ! [ -f "$DESTDIR/lib/python2.7/lib-dynload/$name.so" ]; then
		cmd cd "$OPTPATH"
		echo "Building module that python didn't realize it could built: $name" >&2
		vcmd "${CROSS_PREFIX}gcc" \
			-shared -fno-strict-aliasing -ggdb -DNDEBUG \
			-g -fwrapv -O3 -Wall -Wstrict-prototypes -L. \
			-I"$SRCPATH/Include" -I. \
			-o "$DESTDIR/lib/python2.7/lib-dynload/$name.so" $* \
			-lpython2.7
	else
		echo "Module was actually built: $name" >&2
	fi
}



# Get rid of some stuff which we don't want to install
HOOK_BEFORE_INSTALL_DISK=_hook_before_install_disk
_hook_before_install_disk() {
	# We don't want to install the precompiled python files
	cmd cd "$DESTDIR/lib/python2.7"
	find \( -name '*.pyc' -or -name '*.pyo' \) -print0 | xargs -0 rm -f

	# We don't want to install tests
	cmd rm -rf "$DESTDIR/lib/python2.7/test"
	cmd rm -rf "$DESTDIR/lib/python2.7/bsddb/test"
	cmd rm -rf "$DESTDIR/lib/python2.7/ctypes/test"
	cmd rm -rf "$DESTDIR/lib/python2.7/distutils/tests"
	cmd rm -rf "$DESTDIR/lib/python2.7/email/test"
	cmd rm -rf "$DESTDIR/lib/python2.7/idlelib/idle_test"
	cmd rm -rf "$DESTDIR/lib/python2.7/json/tests"
	cmd rm -rf "$DESTDIR/lib/python2.7/lib2to3/tests"
	cmd rm -rf "$DESTDIR/lib/python2.7/lib-tk/test"
	cmd rm -rf "$DESTDIR/lib/python2.7/sqlite3/test"
	cmd rm -rf "$DESTDIR/lib/python2.7/unittest/test"

	# We don't want to install the configuration (which contains a 10MiB static version of libpython)
	cmd rm -rf "$DESTDIR/$TARGET_LIBPATH/python2.7/config"


	. "$KOS_MISC/utilities/misc/target-info.sh"
	if ! test -z "$TARGET_CONFIG_ILP32"; then
		# Python doesn't want to built `imageop.so`, unless the host
		# (that is: the machine you're calling this build script from)
		# is a 32-bit machine.
		# Whilst I don't know what's the deal with this module and only
		# being meant to be built for 32-bit machines, I can't stand the
		# idea that Python once again spits the idea of cross-compiling
		# in its face, so I'm just going to built this module manually,
		# if it wasn't already built.
		if [ -f "$SRCPATH/Modules/imageop.c" ]; then
			build_missing_module imageop "$SRCPATH/Modules/imageop.c"
		fi

		# Another module that python only builds conditionally, depending
		# on host configuration (rather than target configuration)
		build_missing_module dl "$SRCPATH/Modules/dlmodule.c"
	fi
}

INSTALL_SKIP="
/bin/python2.7-config
/bin/python2-config
/bin/python-config
/lib/python2.7
/include
"

# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"

# Install modules under `/lib/python2.7/[os.py...]'
install_path_hardcopy /lib/python2.7 "$DESTDIR/lib/python2.7"

# Install config header
if [ "$TARGET_NAME" == "i386" ] || [ "$TARGET_NAME" == "x86_64" ]; then
	if [ "$TARGET_NAME" == "i386" ]; then
		install_rawfile \
			"$KOS_ROOT/kos/include/$TARGET_INCPATH/python2.7/pyconfig32.h" \
			"$OPTPATH/pyconfig.h"
	else
		install_rawfile \
			"$KOS_ROOT/kos/include/$TARGET_INCPATH/python2.7/pyconfig64.h" \
			"$OPTPATH/pyconfig.h"
	fi
	install_rawfile_stdin "$KOS_ROOT/kos/include/$TARGET_INCPATH/python2.7/pyconfig.h" <<EOF
#ifndef _I386_KOS_PYTHON27_PYCONFIG_H
#define _I386_KOS_PYTHON27_PYCONFIG_H 1

#include <hybrid/host.h>

#ifdef __x86_64__
#include "pyconfig64.h"
#else /* __x86_64__ */
#include "pyconfig32.h"
#endif /* !__x86_64__ */

#endif /* !_I386_KOS_PYTHON27_PYCONFIG_H */
EOF
else
	install_rawfile \
		"$KOS_ROOT/kos/include/$TARGET_INCPATH/python2.7/pyconfig.h" \
		"$DESTDIR/include/python2.7/pyconfig.h"
fi

install_rawfile_stdin "$KOS_ROOT/kos/include/python2.7/pyconfig.h" <<EOF
#ifndef _PYTHON27_PYCONFIG_H
#define _PYTHON27_PYCONFIG_H 1
#include <python2.7/pyconfig.h>
#endif /* !_KOS_PYTHON27_PYCONFIG_H */
EOF
