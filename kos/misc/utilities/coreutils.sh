#TEST: require_utility deemon "$TARGET_SYSROOT/bin/join"
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
require_utility libgmp "$PKG_CONFIG_PATH/gmp.pc"

PACKAGE_URL="https://ftp.gnu.org/gnu/coreutils/coreutils-9.1.tar.xz"
PACKAGE_NAME="coreutils-9.1"

CONFIGURE=(
	--disable-libsmack
	--without-linux-crypto
	--with-libgmp
	--without-openssl
	--enable-threads=posix
	--with-included-regex  # FIXME: KOS's libc regex is still broken
)

# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"


#TODO: Improve integration:
# checking for memset_s... no
# checking for microuptime... no
# checking for nanouptime... no
# checking for mbslen... no
# checking whether ctype.h defines __header_inline... no
# checking for arithmetic hrtime_t... no
# checking whether printf supports infinite 'long double' arguments... guessing no
# checking for copy_file_range... no
# checking for fts_open... no
# checking whether gethrtime is declared... no
# checking for getloadavg... no
# checking for kstat_open in -lkstat... no
# checking for perfstat_cpu_total in -lperfstat... no
# checking for sys/dg_sys_info.h... no
# checking for pstat_getdynamic... no
# checking for inq_stats/cpustats.h... no
# checking for sys/cpustats.h... no
# checking for mach/mach.h... no
# checking for nlist.h... no
# checking whether __argv is declared... no
# checking for isapipe... no
# checking whether mbswidth is declared in <wchar.h>... no
# checking for __mktime_internal... no
# checking for sched_getaffinity_np... no
# checking for sysmp... no
# checking for sysctl... (cached) no
# checking for getppriv... no
# checking for major_t... no
# checking for minor_t... no
# checking for cap_get_file in -lcap... no
# configure: WARNING: libcap library was not found or not usable.
# configure: WARNING: GNU coreutils will be built without capability support.
# checking for fclonefileat... no
# checking for getattrat... no
# checking for statx... no
# checking whether __sys_siglist is declared... no
