/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
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
#include <kos/exec/peb.h>
#include <kos/exec/rtld.h>
#include <kos/syscalls.h>
#include <linux/prctl.h>
#include <sys/ioctl.h>

#include <malloc.h>
#include <pty.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

#include "builtin.h"

DECL_BEGIN

INTERN DlModule dl_rtld_module = {
	.dm_loadaddr      = 0,
	.dm_filename      = NULL,
	.dm_dynhdr        = NULL,
	.dm_modules       = { NULL, NULL },
	.dm_tlsoff        = 0,
	.dm_tlsinit       = NULL,
	.dm_tlsfsize      = 0,
	.dm_tlsmsize      = 0,
	.dm_tlsalign      = 0,
	.dm_tlsstoff      = 0,
	.dm_tls_init      = NULL,
	.dm_tls_fini      = NULL,
	.dm_tls_arg       = NULL,
	.dm_refcnt        = 2, /* dl_rtld_module, dl_globals.dg_globallist */
	.dm_weakrefcnt    = 1,
	.dm_globals       = LIST_ENTRY_UNBOUND_INITIALIZER,
	.dm_file          = -1,
	.dm_flags         = RTLD_LOCAL | RTLD_NODELETE,
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
		.de_pltgot     = NULL,
#if !ELF_ARCH_USESRELA
		.de_jmprel     = NULL,
#else /* !ELF_ARCH_USESRELA */
		{
			.de_jmprel = NULL,
		},
#endif /* ELF_ARCH_USESRELA */
#if ELF_ARCH_LAZYINDX
		.de_jmpcount   = 0,
#else /* ELF_ARCH_LAZYINDX */
		.de_jmpsize    = 0,
#endif /* !ELF_ARCH_LAZYINDX */
		.de_dyncnt     = 0,
		.de_dynsym_tab = NULL,
		.de_dynsym_cnt = 0,
		.de_gnuhashtab = NULL,
		.de_hashtab    = NULL,
		.de_dynstr     = NULL,
		.de_runpath    = NULL,
		.de_shoff      = 0,
		.de_shstrndx   = (ElfW(Half))-1,
		.de_shdr       = (ElfW(Shdr) *)(uintptr_t)-1,
		.de_shstrtab   = (char *)(uintptr_t)-1,
		.de_shnum      = (ElfW(Half))-1, /* Uses custom handling! */
		.de_phnum      = 1,
		.de_phdr       = {
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


/* libdl global variables (as also shared with extension drivers) */
INTERN struct dlglobals dl_globals = {
	.dg_peb         = NULL, /* Initialized in `linker_main()' */
	.dg_libpath     = NULL, /* Initialized in `linker_main()' */
	.dg_errmsg      = NULL,
	.dg_globallist  = { NULL, NULL }, /* Manually initialized (would otherwise need relocations) */
	.dg_globallock  = ATOMIC_RWLOCK_INIT,
	.dg_alllist     = DLIST_HEAD_INITIALIZER(dl_globals.dg_alllist),
	.dg_alllock     = ATOMIC_RWLOCK_INIT,
};

/* Set to true if the sys_debugtrap() system call is disabled. */
INTERN bool sys_debugtrap_disabled = false;

INTDEF byte_t __rtld_end[];
INTDEF byte_t __rtld_start[];

typedef void *(FCALL *PLINKER_MAIN)(struct elfexec_info *__restrict info,
                                    uintptr_t loadaddr,
                                    struct process_peb *__restrict peb);


INTERN WUNUSED NONNULL((1, 3)) void *FCALL
linker_main(struct elfexec_info *__restrict info,
            uintptr_t loadaddr,
            struct process_peb *__restrict peb) {
	void *result;
	REF DlModule *base_module;
	size_t rtld_size = __rtld_end - __rtld_start;

	/* Initialize globals (not done statically because we can't have relocations). */
	dl_globals.dg_peb                 = peb;
	dl_globals.dg_globallist.tqh_last = &dl_globals.dg_globallist.tqh_first; /* Initialize global list. */
	dl_rtld_module.dm_filename        = (char *)RTLD_LIBDL;
	dl_rtld_module.dm_loadaddr        = info->ei_rtldaddr;
	dl_rtld_module.dm_loadstart       = info->ei_rtldaddr;
	dl_rtld_module.dm_loadend         = (uintptr_t)rtld_size;
	dl_globals.dg_alllist.dlh_first   = &dl_rtld_module;
	dl_rtld_module.dm_loadend += info->ei_rtldaddr;
	dl_rtld_module.dm_elf.de_phdr[0].p_filesz = (ElfW(Word))rtld_size;
	dl_rtld_module.dm_elf.de_phdr[0].p_memsz  = (ElfW(Word))rtld_size;

	/* Check for LD-specific environment variables. */
	dl_globals.dg_libpath = process_peb_getenv(peb, "LD_LIBRARY_PATH");
	if (dl_globals.dg_libpath == NULL) {
		dl_globals.dg_libpath = (char *)RTLD_LIBRARY_PATH;
	} else {
		/* Specs state that `LD_LIBRARY_PATH' should be ignored under AT_SECURE-mode */
		if (sys_Xprctl(PR_KOS_GET_AT_SECURE, 0, 0, 0, 0))
			dl_globals.dg_libpath = (char *)RTLD_LIBRARY_PATH;
	}

	/* Support for executable formats other than ELF */
	if (elfexec_info_usesinterpreter(info)) {
		char *int_name;
		DlModule *int_lib;
		PLINKER_MAIN int_main;
		int_name = elfexec_info_getinterpreter(info);
		int_lib  = DlModule_OpenFilename(int_name, RTLD_LAZY | RTLD_NODELETE);
		if unlikely(!int_lib)
			goto err;

		/* Custom interpreters are regular, old (ELF) libraries that  are
		 * expected to export  a symbol `__linker_main()'.  Additionally,
		 * such a library may define an INIT function which it can use to
		 * register a libdl extension.
		 *
		 * Unlike the core libdl, custom interpreters are allowed to have
		 * relocations and further dependencies, such as by using `libc'.
		 *
		 * For an example of such a library, see `/kos/src/libdl-pe' */
		*(void **)&int_main = libdl_dlsym(int_lib, "__linker_main");
		if unlikely(!int_main)
			goto err;

		/* Invoke an external linker-main function. */
		COMPILER_BARRIER();
		result = (*int_main)(info, loadaddr, peb);
		COMPILER_BARRIER();

		/* The first element of the global module list must be loaded by an extension.
		 * If it isn't,  then we must  assume that the  extension loaded above  didn't
		 * actually load anything, and if it also  didn't set a dlerror, then we  will
		 * set a fallback error indicating that the extension couldn't load the  base-
		 * application given by the kernel. */
		base_module = dlglobals_mainapp(&dl_globals);
		if unlikely(result == NULL || base_module == NULL ||
		            base_module->dm_ops == NULL) {
			if (dl_globals.dg_errmsg == NULL) {
				dl_seterrorf("Cannot load application with %q",
				             int_lib->dm_filename);
			}
			goto err;
		}
	} else {
		/* Return a pointer to `&info->ed_entry' */
		char *filename;
		filename = elfexec_info_getfilename(info);
		result   = &elfexec_info_getentry(info);
		filename = strdup(filename);
		if unlikely(!filename) {
			dl_seterror_nomem();
			goto err;
		}
		base_module = DlModule_ElfOpenLoadedProgramHeaders(filename, info, loadaddr);
		if unlikely(!base_module)
			goto err;
	}

	assert(base_module->dm_flags & RTLD_NOINIT);

	/* User-level initializers must be run _after_ we've initialized static TLS!
	 * NOTE: this  is done in  `_start32.S' by manually calling
	 *       `DlModule_RunAllStaticInitializers()'  just  prior
	 *       to jumping to the primary application's `_start()'
	 *       function. */

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
	assert(dlglobals_mainapp(&dl_globals) == base_module);
	/*decref(base_module);*/ /* Intentionally left dangling! */

	return result;
	{
		char *error;
err:
		error = libdl_dlerror();
		syslog(LOG_ERR, "DL Initialization failed: %s\n", error);
		/* If STDERR is  a tty,  also print the  error message  there.
		 * Don't  do so  when STDERR  is something  different (such as
		 * a file) in order to  not accidentally inject an  unexpected
		 * error message into an error stream that wouldn't understand
		 * such a message. */
		{
			struct termios ios;
			if (sys_ioctl(STDERR_FILENO, TCGETA, &ios) >= 0) {
				sys_write(STDERR_FILENO, "DL: ", 4);
				sys_write(STDERR_FILENO, error, strlen(error));
				sys_write(STDERR_FILENO, "\n", 1);
			}
		}
	}
	sys_exit_group(EXIT_FAILURE);
}


DECL_END

#endif /* !GUARD_LIBDL_MAIN_C */
