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
#define _KOS_ALTERATIONS_SOURCE 1
#define _GNU_SOURCE 1

#include "api.h"
/**/

#include "pe.h"
/**/

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/wordbits.h>

#include <kos/except.h>
#include <kos/syscalls.h>
#include <sys/ioctl.h>

#include <dlfcn.h>
#include <link.h>
#include <malloca.h>
#include <stdlib.h>
#include <syslog.h>
#include <termios.h>
#include <unistd.h>

DECL_BEGIN

INTERN char *CC dlstrdup(char const *str) {
	syslog(LOG_DEBUG, "dlstrdup(%q)\n", str);
	size_t len   = (strlen(str) + 1) * sizeof(char);
	char *result = (char *)malloc(len);
	if (result)
		result = (char *)memcpy(result, str, len);
	return result;
}

INTERN ATTR_COLD int
NOTHROW(CC dl_seterror_nomem)(void) {
	return dl.dl_seterrorf("Insufficient memory");
}


/* Wrapper for `dlsym()' that does all of the "DOS$" / "KOS$" prefix handling. */
DEFINE_PUBLIC_ALIAS(GetProcAddress, libpe_GetProcAddress);
INTERN void *ATTR_STDCALL
libpe_GetProcAddress(DlModule *self, char const *symbol_name) {
	void *result;
	char *dos_symbol_name;
	size_t symbol_name_len;

	/* Check for special case: don't try to link against DOS symbols */
	if (memcmp(symbol_name, "KOS$", 4 * sizeof(char)) == 0)
		return dlsym(self, symbol_name + 4);

	/* Firstly: try to link against "DOS$"-prefixed symbols. */
	symbol_name_len = strlen(symbol_name);
	dos_symbol_name = (char *)malloca(4 + symbol_name_len + 1, sizeof(char));
	if unlikely(!dos_symbol_name) {
		dl_seterror_nomem();
		return NULL;
	}
	{
		RAII_FINALLY { freea(dos_symbol_name); };

		/* Construct the DOS$-prefixed symbol name. */
		*(uint32_t *)dos_symbol_name = ENCODE_INT32('D', 'O', 'S', '$');
		memcpy(dos_symbol_name + 4, symbol_name, symbol_name_len + 1, sizeof(char));
		result = dlsym(self, dos_symbol_name);
	}
	if (result)
		return result;

	/* Try again with the non-prefixed name. */
	result = dlsym(self, symbol_name);
	if (result) {
		/* Clear the error message set by the initial failed `dlsym()' */
		dl.dl_error_message = NULL;
	}
	return result;
}



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

	/* Make sure that the registration was successful */
	if unlikely(libpe_fmt.df_core == NULL) {
		struct termios ios;
		char const *error = dlerror();
		syslog(LOG_ERR, "Failed to hook PE libdl-extension: %s\n", error);
		if (sys_ioctl(STDERR_FILENO, TCGETA, &ios) >= 0) {
			sys_write(STDERR_FILENO, "PE: ", 4);
			sys_write(STDERR_FILENO, error, strlen(error));
			sys_write(STDERR_FILENO, "\n", 1);
		}
		sys_exit_group(EXIT_FAILURE);
	}
}

/* Replacement for `linker_main' from `libdl.so' when a PE binary gets executed. */
DEFINE_PUBLIC_ALIAS(__linker_main, libpe_linker_main);
INTERN void *FCALL
libpe_linker_main(struct peexec_info *__restrict info,
                  uintptr_t loadaddr,
                  struct process_peb *__restrict UNUSED(peb)) {
	void *result;
	DlModule *mod;
	char *filename;
	struct peexec_data *pe = peexec_info__pi_pe(info);

#if 1
	syslog(LOG_DEBUG, "[pe] info->pi_rtldaddr                         = %p\n", info->pi_rtldaddr);
	syslog(LOG_DEBUG, "[pe] info->pi_pnum                             = %#I16x\n", info->pi_pnum);
	syslog(LOG_DEBUG, "[pe] info->pi_libdl_pe                         = %q\n", info->pi_libdl_pe);
	syslog(LOG_DEBUG, "[pe] pe->pd_nt.Signature                       = %#I32x\n", pe->pd_nt.Signature);
	syslog(LOG_DEBUG, "[pe] pe->pd_nt.FileHeader.Machine              = %#I16x\n", pe->pd_nt.FileHeader.Machine);
	syslog(LOG_DEBUG, "[pe] pe->pd_nt.FileHeader.NumberOfSections     = %#I16x\n", pe->pd_nt.FileHeader.NumberOfSections);
	syslog(LOG_DEBUG, "[pe] pe->pd_nt.FileHeader.TimeDateStamp        = %#I32x\n", pe->pd_nt.FileHeader.TimeDateStamp);
	syslog(LOG_DEBUG, "[pe] pe->pd_nt.FileHeader.PointerToSymbolTable = %#I32x\n", pe->pd_nt.FileHeader.PointerToSymbolTable);
	syslog(LOG_DEBUG, "[pe] pe->pd_nt.FileHeader.NumberOfSymbols      = %#I32x\n", pe->pd_nt.FileHeader.NumberOfSymbols);
	syslog(LOG_DEBUG, "[pe] pe->pd_nt.FileHeader.SizeOfOptionalHeader = %#I16x\n", pe->pd_nt.FileHeader.SizeOfOptionalHeader);
	syslog(LOG_DEBUG, "[pe] pe->pd_nt.FileHeader.Characteristics      = %#I16x\n", pe->pd_nt.FileHeader.Characteristics);
	syslog(LOG_DEBUG, "[pe] pe->pd_name                               = %q\n", peexec_data__pd_name(pe));
#endif

	/* TODO: Modify `dl_library_path' to include  `basename $(peexec_data__pd_name(pe))'
	 *       This is required for semantic compatibility with how dlls are loaded on NT. */

	/* Allocate the DL module descriptor for the PE binary. */
	mod = (DlModule *)malloc(offsetof(DlModule, dm_pe.dp_sect) +
	                         (pe->pd_nt.FileHeader.NumberOfSections *
	                          sizeof(IMAGE_SECTION_HEADER)));
	if unlikely(!mod)
		goto err_nomem;

	/* Duplicate the caller-given filename. */
	filename = peexec_data__pd_name(pe);
	result   = (void *)CEIL_ALIGN((uintptr_t)strend(filename), sizeof(void *));
	filename = strdup(filename);
	if unlikely(!filename)
		goto err_nomem; /* Leaks don't matter; we're only called once during init! */

	/* Initialize simple fields of the new module. */
	mod->dm_loadaddr   = loadaddr;
	mod->dm_filename   = filename; /* Inherit */
	mod->dm_dynhdr     = NULL;     /* Only exists under ELF */
	mod->dm_tlsoff     = 0;
	mod->dm_tlsinit    = NULL;
	mod->dm_tlsfsize   = 0;
	mod->dm_tlsmsize   = 0;
	mod->dm_tlsalign   = 0;
	mod->dm_tlsstoff   = 0;
	mod->dm_tls_init   = NULL;
	mod->dm_tls_fini   = NULL;
	mod->dm_tls_arg    = NULL;
	mod->dm_refcnt     = 1;
	mod->dm_weakrefcnt = 1;
	mod->dm_file       = -1;
	mod->dm_flags      = RTLD_LAZY | RTLD_NODELETE | RTLD_LOADING;
	mod->dm_loadstart  = pe->pd_loadmin;
	mod->dm_loadend    = pe->pd_loadmax + 1;
	mod->dm_finalize   = NULL;

	/* Fill in section information. */
	mod->dm_shnum = pe->pd_nt.FileHeader.NumberOfSections;
	atomic_rwlock_init(&mod->dm_sections_lock);
	mod->dm_sections = (DlSection **)calloc(mod->dm_shnum, sizeof(DlSection *));
	if unlikely(!mod->dm_sections)
		goto err_nomem; /* Leaks don't matter; we're only called once during init! */
	mod->dm_sections_dangling = NULL;
	mod->dm_ops               = &libpe_fmt;

	/* Copy over PE information. */
	{
		size_t size;
		size = offsetof(IMAGE_NT_HEADERS, OptionalHeader) + pe->pd_nt.FileHeader.SizeOfOptionalHeader;
		if unlikely(size > sizeof(IMAGE_NT_HEADERS))
			size = sizeof(IMAGE_NT_HEADERS);
		memset(mempcpy(&mod->dm_pe.dp_nt, pe, size), 0,
		       sizeof(IMAGE_NT_HEADERS) - size);
		memcpy(&mod->dm_pe.dp_sect, peexec_data__pd_sect(pe),
		       pe->pd_nt.FileHeader.NumberOfSections,
		       sizeof(IMAGE_SECTION_HEADER));
	}

	/* Fill in library dependencies */
	mod->dm_depcnt = 0;    /* TODO */
	mod->dm_depvec = NULL; /* TODO */

	/* Hook the newly created module. */
	DLIST_INSERT_TAIL(dl.DlModule_AllList, mod, dm_modules);
	LIST_INSERT_HEAD(dl.DlModule_GlobalList, mod, dm_globals); /* NOTE: _MUST_ insert at head! */

	/* TODO: Load dependencies */
	/* TODO: Apply relocations */
	asm("int3");

	/* Mark this module as having been fully loaded. */
	ATOMIC_AND(mod->dm_flags, ~RTLD_LOADING);

	/* Return a pointer to the PE program entry point. */
	return result;
err_nomem:
	dl_seterror_nomem();
	return NULL;
}

DECL_END

#endif /* !GUARD_LIBDL_PE_PE_C */
