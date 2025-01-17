#TEST: require_utility mc "$SYSROOT_BIN_TARGET_COMMON/bin/mc"
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
require_utility libglib    "$PKG_CONFIG_PATH/glib-2.0.pc"
require_utility libpcre    "$PKG_CONFIG_PATH/libpcre.pc"
PACKAGE_URL="http://ftp.midnight-commander.org/mc-4.8.27.tar.xz"

# Additions configure options
CONFIGURE=(
	"--enable-charset"
	"--disable-mclib"
	"--disable-assert"
	"--enable-background"
	"--enable-vfs-cpio"
	"--enable-vfs-extfs"
	"--enable-vfs-fish"
	"--enable-vfs-ftp"
	"--enable-vfs-sfs"
	"--disable-vfs-sftp"    # "--enable-vfs-sftp"
	"--disable-vfs-smb"     # "--enable-vfs-smb"
	"--enable-vfs-tar"
	"--disable-vfs-undelfs" # "--enable-vfs-undelfs"
	"--without-glib-static"
	"--with-screen=ncurses"
	"--with-search-engine=pcre"
	"--with-pcre"
	"--with-mmap"
	"--with-internal-edit"
	"--with-diff-viewer"
	"--with-subshell=optional"
)

# Force-enable 64-bit time (needed because program assigns
# `struct stat::st_*tim' as-is to a `struct timespec'; and
# also because 32-bit will overflow sooner rather than later)
PACKAGE_CCFLAGS="-D_TIME_T_BITS=64"

# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"
