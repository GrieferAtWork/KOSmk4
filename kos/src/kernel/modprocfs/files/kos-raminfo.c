/* Copyright (c) 2019-2020 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODPROCFS_FILES_KOS_RAMINFO_C
#define GUARD_MODPROCFS_FILES_KOS_RAMINFO_C 1

#include <kernel/compiler.h>

#include <kernel/memory.h>

#include <format-printer.h>

#include "../procfs.h"

DECL_BEGIN

#if __SIZEOF_PAGEPTR_T__ == __SIZEOF_INT__
#define FMT_PAGECNT  ""
#elif __SIZEOF_PAGEPTR_T__ == __SIZEOF_POINTER__
#define FMT_PAGECNT  "I"
#elif __SIZEOF_PAGEPTR_T__ == __SIZEOF_LONG_
#define FMT_PAGECNT  "l"
#elif __SIZEOF_PAGEPTR_T__ == 1
#define FMT_PAGECNT  "I8"
#elif __SIZEOF_PAGEPTR_T__ == 2
#define FMT_PAGECNT  "I16"
#elif __SIZEOF_PAGEPTR_T__ == 4
#define FMT_PAGECNT  "I32"
#elif __SIZEOF_PAGEPTR_T__ == 8
#define FMT_PAGECNT  "I64"
#else
#error "Unsupported __SIZEOF_PAGEPTR_T__"
#endif

#define PRINT(str) (*printer)(arg, str, COMPILER_STRLEN(str))


PRIVATE NONNULL((1)) void KCALL
print_pagecount(pformatprinter printer, void *arg, pagecnt_t count) {
	pagecnt_t adjusted_count;
	char const *unit;
	if (count >= (0x100000 / PAGESIZE)) {
		adjusted_count = count / (0x100000 / PAGESIZE);
		unit           = "MiB";
	} else {
		adjusted_count = (count * PAGESIZE) / 1024;
		unit           = "KiB";
	}
	format_printf(printer, arg, "%" FMT_PAGECNT "u (%" FMT_PAGECNT "u %s)",
	              count, adjusted_count, unit);
}

INTERN NONNULL((1, 2)) ssize_t KCALL
ProcFS_Kos_RamInfo_Printer(struct regular_node *__restrict UNUSED(self),
                           pformatprinter printer, void *arg) {
	struct pmemstat st;
	unsigned int usage_percent;
	page_stat(&st);
	PRINT("free:");
	print_pagecount(printer, arg, st.ps_free);
	PRINT("\nused:");
	print_pagecount(printer, arg, st.ps_used);
	PRINT("\nzero:");
	print_pagecount(printer, arg, st.ps_zfree);
	usage_percent = (unsigned int)(((u64)st.ps_used * 100 * 100000) / (st.ps_free + st.ps_used));
	format_printf(printer, arg, "\nusage:%u.%.5u%%\n",
	              usage_percent / 100000,
	              usage_percent % 100000);
	return 0;
}


DECL_END

#endif /* !GUARD_MODPROCFS_FILES_KOS_RAMINFO_C */
