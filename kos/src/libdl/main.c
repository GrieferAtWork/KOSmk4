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
#ifndef GUARD_LIBDL_MAIN_C
#define GUARD_LIBDL_MAIN_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#define DL_FIXED_PHDR_COUNT 1

/* Keep this one the first */
#include "dl.h"
/**/

#include <asm/intrin.h>
#include <asm/pagesize.h>
#include <kos/debugtrap.h>
#include <kos/exec/elf.h>
#include <kos/exec/library-listdef.h>
#include <kos/exec/peb.h>
#include <kos/exec/rtld.h>
#include <kos/syscalls.h>

#include <malloc.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

DECL_BEGIN

INTERN DlModule dl_rtld_module = {
	.dm_tlsoff        = 0,
	.dm_tlsinit       = NULL,
	.dm_tlsfsize      = 0,
	.dm_tlsmsize      = 0,
	.dm_tlsalign      = 0,
	.dm_tlsstoff      = 0,
	.dm_tls_init      = NULL,
	.dm_tls_fini      = NULL,
	.dm_tls_arg       = NULL,
	.dm_refcnt        = 2, /* dl_rtld_module, DlModule_GlobalList */
	.dm_modules       = LLIST_INITNODE,
	.dm_globals       = LLIST_INITNODE,
	.dm_filename      = NULL,
	.dm_file          = -1,
	.dm_flags         = RTLD_LOCAL | RTLD_NODELETE,
	.dm_loadaddr      = 0,
	.dm_loadstart     = 0,
	.dm_loadend       = (uintptr_t)0,
	.dm_finalize      = NULL,
	.dm_depcnt        = 0,
	.dm_depvec        = NULL,
	.dm_sections_lock = ATOMIC_RWLOCK_INIT,
	.dm_sections      = (DlSection **)(uintptr_t)-1,
	.dm_sections_dangling = (DlSection *)(uintptr_t)-1,
	.dm_shnum         = BUILTIN_SECTIONS_COUNT,
	.dm_ops = NULL,
	.dm_elf = {
		.de_pltgot        = NULL,
#if !ELF_ARCH_USESRELA
		.de_jmprel        = NULL,
#else /* !ELF_ARCH_USESRELA */
		{
			.de_jmprel    = NULL,
		},
#endif /* ELF_ARCH_USESRELA */
#if ELF_ARCH_LAZYINDX
		.de_jmpcount      = 0,
#else /* ELF_ARCH_LAZYINDX */
		.de_jmpsize       = 0,
#endif /* !ELF_ARCH_LAZYINDX */
		.de_dyncnt        = 0,
		.de_dynhdr        = NULL,
		.de_dynsym_tab    = NULL,
		.de_dynsym_cnt    = 0,
		.de_gnuhashtab    = NULL,
		.de_hashtab       = NULL,
		.de_dynstr        = NULL,
		.de_runpath       = NULL,
		.de_shoff         = 0,
		.de_shstrndx      = (ElfW(Half))-1,
		.de_shdr          = (ElfW(Shdr) *)(uintptr_t)-1,
		.de_shstrtab = (char *)(uintptr_t)-1,
		.de_phnum    = 1,
		.de_phdr     = {
			ELFW(PHDR_INIT)(/* type:   */ PT_LOAD,
			                /* offset: */ __ARCH_PAGESIZE,
			                /* vaddr:  */ 0,
			                /* paddr:  */ 0,
			                /* filesz: */ (ElfW(Word))0,
			                /* memsz:  */ (ElfW(Word))0,
			                /* flags:  */ PF_R | PF_X | PF_W,
			                /* align:  */ __ARCH_PAGESIZE)
		}
	}
};


PRIVATE char const ld_rtld_module_filename[] = RTLD_LIBDL;
INTERN struct process_peb *root_peb = NULL;

/* Set to true if the sys_debugtrap() system call is disabled. */
INTERN bool sys_debugtrap_disabled = false;

/* Kernel meta-information: Library listing. */
PRIVATE struct library_listdef dl_library_layout = {
	.lld_size                      = sizeof(struct library_listdef),
	.lld_sizeof_pointer            = sizeof(void *),
	.lld_flags                     = LIBRARY_LISTDEF_FPFIRST | LIBRARY_LISTDEF_FLINKLST,
	.lld_first                     = NULL, /* Filled in below */
	.lld_count                     = NULL, /* Not used. */
	.lld_module_offsetof_filename  = offsetof(DlModule, dm_filename),
	.lld_module_offsetof_loadaddr  = offsetof(DlModule, dm_loadaddr),
	.lld_module_offsetof_loadstart = offsetof(DlModule, dm_loadstart),
	.lld_entry_offsetof_next       = offsetof(DlModule, dm_modules.ln_next),
	.lld_entry_offsetof_module     = 0, /* Unused */
};


INTDEF byte_t __rtld_eh_frame_start[];
INTDEF byte_t __rtld_eh_frame_end[];
INTDEF byte_t __rtld_gcc_except_table_start[];
INTDEF byte_t __rtld_gcc_except_table_end[];

INTDEF byte_t __rtld_end[];
INTDEF byte_t __rtld_start[];


INTERN WUNUSED NONNULL((1, 3)) void *FCALL
linker_main(struct elfexec_info *__restrict info,
            uintptr_t loadaddr,
            struct process_peb *__restrict peb) {
	char *filename;
	void *result;
	REF DlModule *base_module;
	size_t rtld_size = __rtld_end - __rtld_start;

	/* Initialize globals (not done statically because we can't have relocations). */
	root_peb                    = peb;
	dl_rtld_module.dm_filename  = (char *)ld_rtld_module_filename;
	dl_rtld_module.dm_loadaddr  = info->ei_rtldaddr;
	dl_rtld_module.dm_loadstart = info->ei_rtldaddr;
	dl_rtld_module.dm_loadend   = (uintptr_t)rtld_size;
	dl_rtld_module.dm_loadend  += info->ei_rtldaddr;
	dl_rtld_module.dm_elf.de_phdr[0].p_filesz = (ElfW(Word))rtld_size;
	dl_rtld_module.dm_elf.de_phdr[0].p_memsz  = (ElfW(Word))rtld_size;
	dl_rtld_module.dm_modules.ln_pself = &DlModule_AllList;
	DlModule_AllList                   = &dl_rtld_module;

	/* Tell the kernel how it can enumerate loaded libraries in user-space. */
	dl_library_layout.lld_first = &DlModule_AllList;
	sys_set_library_listdef(&dl_library_layout);

	/* Return a pointer to `&info->ed_entry' */
	filename = elfexec_info_getfilename(info);
	result   = &elfexec_info_getentry(info);

	filename = strdup(filename);
	if unlikely(!filename) {
		dl_seterror_nomem();
		goto err;
	}

	/* Check for LD-specific environment variables. */
	dl_library_path = process_peb_getenv(peb, "LD_LIBRARY_PATH");
	if (!dl_library_path)
		dl_library_path = (char *)RTLD_LIBRARY_PATH;

	/* TODO: Support for executable formats other than ELF */
	base_module = DlModule_ElfOpenLoadedProgramHeaders(filename, info, loadaddr);
	if unlikely(!base_module)
		goto err;
	assert(base_module->dm_flags & RTLD_NOINIT);

	/* User-level initializers must be run _after_ we've initialized static TLS!
	 * NOTE: this is done in `_start32.S' by manually calling `DlModule_RunAllStaticInitializers'
	 *       just prior to jumping to the primary application's _start() function. */

	/* Initialize the static TLS table. */
	if unlikely(DlModule_InitStaticTLSBindings())
		goto err;

	{
		/* Allocate and assign the static TLS segment for the main thread. */
		void *tls = libdl_dltlsallocseg();
		if unlikely(!tls)
			goto err;
		WR_TLS_BASE_REGISTER(tls);
	}
	assert(DlModule_GlobalList == base_module);
	assert(DlModule_AllList == &dl_rtld_module);
	assert(dl_rtld_module.dm_modules.ln_next == base_module);

	/*DlModule_Decref(base_module);*/ /* Intentionally left dangling! */

	return result;
err:
	syslog(LOG_ERR, "DL Initialization failed: %s\n", libdl_dlerror());
	sys_exit_group(EXIT_FAILURE);
}


DECL_END

#endif /* !GUARD_LIBDL_MAIN_C */
