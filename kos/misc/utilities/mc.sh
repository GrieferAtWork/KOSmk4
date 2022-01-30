#TEST: require_utility mc "$TARGET_SYSROOT/bin/mc"
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

require_utility libncurses "$TARGET_SYSROOT/$TARGET_LIBPATH/libncursesw.so"
require_utility libglib    "$PKG_CONFIG_PATH/glib-2.0.pc"
require_utility libpcre    "$PKG_CONFIG_PATH/libpcre.pc"
PACKAGE_URL="http://ftp.midnight-commander.org/mc-4.8.27.tar.xz"

# Additions configure options
CONFIGURE=""
CONFIGURE="$CONFIGURE --enable-charset"
CONFIGURE="$CONFIGURE --disable-mclib"
CONFIGURE="$CONFIGURE --disable-assert"
CONFIGURE="$CONFIGURE --enable-background"
CONFIGURE="$CONFIGURE --enable-vfs-cpio"
CONFIGURE="$CONFIGURE --enable-vfs-extfs"
CONFIGURE="$CONFIGURE --enable-vfs-fish"
CONFIGURE="$CONFIGURE --enable-vfs-ftp"
CONFIGURE="$CONFIGURE --enable-vfs-sfs"
CONFIGURE="$CONFIGURE --disable-vfs-sftp"    #CONFIGURE="$CONFIGURE --enable-vfs-sftp"
CONFIGURE="$CONFIGURE --disable-vfs-smb"     #CONFIGURE="$CONFIGURE --enable-vfs-smb"
CONFIGURE="$CONFIGURE --enable-vfs-tar"
CONFIGURE="$CONFIGURE --disable-vfs-undelfs" #CONFIGURE="$CONFIGURE --enable-vfs-undelfs"
CONFIGURE="$CONFIGURE --without-glib-static"
CONFIGURE="$CONFIGURE --with-screen=ncurses"
CONFIGURE="$CONFIGURE --with-search-engine=pcre"
CONFIGURE="$CONFIGURE --with-pcre"
CONFIGURE="$CONFIGURE --with-mmap"
CONFIGURE="$CONFIGURE --with-internal-edit"
CONFIGURE="$CONFIGURE --with-diff-viewer"
CONFIGURE="$CONFIGURE --with-subshell=optional"

# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"
