#TEST: require_utility libglib "$PKG_CONFIG_PATH/glib-2.0.pc"
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

require_utility libpcre "$PKG_CONFIG_PATH/libpcre.pc"

PACKAGE_URL="https://download.gnome.org/sources/glib/2.70/glib-2.70.3.tar.xz"
PACKAGE_NAME="libglib-2.70.3"

GLIB_HEADER_VERSION="2.0"

CONFIGURE=(
	"-Diconv=external"
	"-Dman=false"
	"-Dgtk_doc=false"
	"-Dforce_posix_threads=true"
	"-Dtests=false"
	"-Dinstalled_tests=false"
	"-Dnls=enabled"
)

# Don't install these files the "normal" way:
INSTALL_SKIP="
/$TARGET_LIBPATH/glib-2.0/include/glibconfig.h
"

# Fix the messed-up header include system as far as that is possible
_fix_glib_relative_includes() {
	cmd cd "$KOS_MISC/scripts"
	cmd rundeemon "libglib-fix-headers.dee" \
		"$DESTDIR/usr/include/glib-$GLIB_HEADER_VERSION" \
		"$DESTDIR/usr/include/gio-unix-$GLIB_HEADER_VERSION" \
		"$DESTDIR/usr/include/gio-unix-$GLIB_HEADER_VERSION"
	cmd rundeemon "libglib-fix-headers.dee" \
		"$DESTDIR/usr/include/glib-$GLIB_HEADER_VERSION" \
		"$DESTDIR/usr/include/glib-$GLIB_HEADER_VERSION"
}
HOOK_BEFORE_INSTALL_DISK=_fix_glib_relative_includes

# Automatically build+install using meson
. "$KOS_MISC/utilities/misc/meson.sh"

# Install configure options file (in a portable manner)
if [ "$TARGET_NAME" == "i386" ] || [ "$TARGET_NAME" == "x86_64" ]; then
	if [ "$TARGET_NAME" == "i386" ]; then
		install_rawfile \
			"$KOS_ROOT/kos/include/$TARGET_INCPATH/glibconfig32.h" \
			"$DESTDIR/$TARGET_LIBPATH/glib-2.0/include/glibconfig.h"
	else
		install_rawfile \
			"$KOS_ROOT/kos/include/$TARGET_INCPATH/glibconfig64.h" \
			"$DESTDIR/$TARGET_LIBPATH/glib-2.0/include/glibconfig.h"
	fi
	install_rawfile_stdin "$KOS_ROOT/kos/include/$TARGET_INCPATH/glibconfig.h" <<EOF
#ifndef _I386_KOS_GLIBCONFIG_H
#define _I386_KOS_GLIBCONFIG_H 1

#include <hybrid/host.h>

#ifdef __x86_64__
#include "glibconfig64.h"
#else /* __x86_64__ */
#include "glibconfig32.h"
#endif /* !__x86_64__ */

#endif /* !_I386_KOS_GLIBCONFIG_H */
EOF
else
	install_rawfile \
		"$DESTDIR/$TARGET_LIBPATH/glib-2.0/include/glibconfig.h" \
		"$KOS_ROOT/kos/include/$TARGET_INCPATH/glibconfig.h"
fi

make_glib_include_warpper() {
	install_rawfile_stdin "$KOS_ROOT/kos/include/$1" <<EOF
#include "glib-$GLIB_HEADER_VERSION/$1"
EOF
}

install_rawfile_stdin "$KOS_ROOT/kos/include/glib/gmacros.h" <<EOF
#include "../glib-$GLIB_HEADER_VERSION/glib/gmacros.h"
EOF
make_glib_include_warpper "glib.h"
make_glib_include_warpper "glib-object.h"
make_glib_include_warpper "glib-unix.h"
make_glib_include_warpper "gmodule.h"
