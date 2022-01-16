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
#ifndef GUARD_LIBDL_PE_PE_C
#define GUARD_LIBDL_PE_PE_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <kos/except.h>

#include <dlfcn.h>

#include "pe.h"

DECL_BEGIN

PRIVATE NONNULL((1, 2)) REF DlModule *LIBDL_CC
libpe_v_open(byte_t const header[DL_MODULE_MAXMAGIC],
             /*inherit(on_success,HEAP)*/ char *__restrict filename,
             /*inherit(on_success)*/ fd_t fd) {
	/* TODO */
	(void)header;
	(void)filename;
	(void)fd;
	COMPILER_IMPURE();
	return DLMODULE_FORMAT_OPEN_BAD_MAGIC;
}

PRIVATE NONNULL((1)) void LIBDL_CC
libpe_v_fini(DlModule *__restrict self) {
	/* TODO */
	(void)self;
	COMPILER_IMPURE();
}

PRIVATE NONNULL((1)) bool LIBDL_CC
libpe_v_ismapped(DlModule *__restrict self,
                 uintptr_t module_relative_pointer) {
	/* TODO */
	(void)self;
	(void)module_relative_pointer;
	COMPILER_IMPURE();
	return false;
}

PRIVATE NONNULL((1, 2, 3)) int LIBDL_CC
libpe_v_dlsym(DlModule *__restrict self,
              char const *__restrict symbol_name,
              void **__restrict psymbol_addr,
              size_t *psymbol_size) {
	/* TODO */
	(void)self;
	(void)symbol_name;
	(void)psymbol_addr;
	(void)psymbol_size;
	COMPILER_IMPURE();
	return DLMODULE_FORMAT_DLSYM_ERROR;
}

PRIVATE NONNULL((1)) int LIBDL_CC
libpe_v_dladdr(DlModule *__restrict self,
               uintptr_t module_relative_pointer,
               struct __dl_info_struct *info) {
	/* TODO */
	(void)self;
	(void)module_relative_pointer;
	(void)info;
	COMPILER_IMPURE();
	return -1;
}

PRIVATE NONNULL((1, 2)) uintptr_t LIBDL_CC
libpe_v_dlsectindex(DlModule *__restrict self,
                    char const *__restrict name) {
	/* TODO */
	(void)self;
	(void)name;
	return (uintptr_t)-1;
}

PRIVATE NONNULL((1, 3)) int LIBDL_CC
libpe_v_dlsectinfo(DlModule *__restrict self, uintptr_t index,
                   struct dl_sect_info *__restrict result) {
	/* TODO */
	(void)self;
	(void)index;
	(void)result;
	return (*dl.dl_seterrorf)("Not implemented");
}

PRIVATE NONNULL((1)) char const *LIBDL_CC
libpe_v_dlsectname(DlModule *__restrict self, uintptr_t index) {
	/* TODO */
	(void)self;
	(void)index;
	(*dl.dl_seterrorf)("Not implemented");
	return NULL;
}

PRIVATE NONNULL((1, 2, 3)) int LIBDL_CC
libpe_v_lsphdrs(DlModule *__restrict self,
                struct dl_phdr_info *__restrict info,
                __dl_iterator_callback callback, void *arg) {
	/* TODO */
	(void)self;
	(void)info;
	(void)callback;
	(void)arg;
	return 0;
}


INTERN struct dlmodule_format libpe_fmt = {
	.df_magic       = { 'M', 'Z' },
	.df_magsz       = 2,
	.df_open        = &libpe_v_open,
	.df_fini        = &libpe_v_fini,
	.df_ismapped    = &libpe_v_ismapped,
	.df_dlsym       = &libpe_v_dlsym,
	.df_dladdr      = &libpe_v_dladdr,
	.df_dlsectindex = &libpe_v_dlsectindex,
	.df_dlsectinfo  = &libpe_v_dlsectinfo,
	.df_dlsectname  = &libpe_v_dlsectname,
	.df_lsphdrs     = &libpe_v_lsphdrs,
};


/* Called by `-Wl,-init=libpe_init' */
INTERN void libpe_init(void) {
	/* Register the PE loader extension for libdl */
	dlauxctrl(NULL, DLAUXCTRL_REGISTER_EXTENSION,
	          &libpe_fmt,
	          sizeof(struct dlmodule_format),
	          sizeof(struct dlcore_ops));
}



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Replacement for `linker_main' from `libdl.so' when a PE binary gets executed. */
DEFINE_PUBLIC_ALIAS(__linker_main, libpe_linker_main);
INTERN void *FCALL
libpe_linker_main(struct peexec_info *__restrict info,
                  uintptr_t loadaddr,
                  struct process_peb *__restrict peb) {
	struct peexec_data *pe = peexec_info__pi_pe(info);

	/* NOTE: We can't use printf() because that function may use
	 *       `errno', which has yet to be initialized at this point! */
	dprintf(STDOUT_FILENO, "libpe_linker_main(%p, %p, %p)\n", info, loadaddr, peb);
	dprintf(STDOUT_FILENO, "\tinfo->pi_rtldaddr                         = %p\n", info->pi_rtldaddr);
	dprintf(STDOUT_FILENO, "\tinfo->pi_pnum                             = %#I16x\n", info->pi_pnum);
	dprintf(STDOUT_FILENO, "\tinfo->pi_libdl_pe                         = %q\n", info->pi_libdl_pe);
	dprintf(STDOUT_FILENO, "\tpe->pd_nt.Signature                       = %#I32x\n", pe->pd_nt.Signature);
	dprintf(STDOUT_FILENO, "\tpe->pd_nt.FileHeader.Machine              = %#I16x\n", pe->pd_nt.FileHeader.Machine);
	dprintf(STDOUT_FILENO, "\tpe->pd_nt.FileHeader.NumberOfSections     = %#I16x\n", pe->pd_nt.FileHeader.NumberOfSections);
	dprintf(STDOUT_FILENO, "\tpe->pd_nt.FileHeader.TimeDateStamp        = %#I32x\n", pe->pd_nt.FileHeader.TimeDateStamp);
	dprintf(STDOUT_FILENO, "\tpe->pd_nt.FileHeader.PointerToSymbolTable = %#I32x\n", pe->pd_nt.FileHeader.PointerToSymbolTable);
	dprintf(STDOUT_FILENO, "\tpe->pd_nt.FileHeader.NumberOfSymbols      = %#I32x\n", pe->pd_nt.FileHeader.NumberOfSymbols);
	dprintf(STDOUT_FILENO, "\tpe->pd_nt.FileHeader.SizeOfOptionalHeader = %#I16x\n", pe->pd_nt.FileHeader.SizeOfOptionalHeader);
	dprintf(STDOUT_FILENO, "\tpe->pd_nt.FileHeader.Characteristics      = %#I16x\n", pe->pd_nt.FileHeader.Characteristics);
	dprintf(STDOUT_FILENO, "\tpe->pd_name                               = %q\n", peexec_data__pd_name(pe));
	_Exit(0);
}

DECL_END

#endif /* !GUARD_LIBDL_PE_PE_C */
