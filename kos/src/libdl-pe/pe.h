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
#ifndef GUARD_LIBDL_PE_PE_H
#define GUARD_LIBDL_PE_PE_H 1

#include "api.h"
/**/

/* This one must be defined before we include <libdl/...> headers. (other than <libdl/api.h>) */
#define DL_EXTENSION_FORMAT libpe_fmt
#define STRUCT_DLMODULE_EXT struct dlmodule_pe
#define DLMODULE_EXT        dm_pe

#include <kos/exec/pe.h>
#include <nt/pe.h>

DECL_BEGIN

/* PE loader extension for libdl */
struct dlmodule_format;
INTDEF struct dlmodule_format libpe_fmt;

/* Per-DlModule extension data for PE */
struct dlmodule_pe {
	__uintptr_t                                   dp_tlsindex; /* [const] TLS index of this module (if applicable) */
	PIMAGE_TLS_CALLBACK const                    *dp_tlscalls; /* [0..1][0..1][const] TLS callback functions. */
	IMAGE_NT_HEADERS                              dp_nt;       /* [const] NT file header */
	COMPILER_FLEXIBLE_ARRAY(IMAGE_SECTION_HEADER, dp_sect);    /* [const][:dm_shnum] Section headers */
};

#define DlModule_HasOptionalHeader(self, field)             \
	((self)->dm_pe.dp_nt.FileHeader.SizeOfOptionalHeader >= \
	 COMPILER_OFFSETAFTER(IMAGE_OPTIONAL_HEADER, field))
#define DlModule_HasDataDirectory(self, id) (DlModule_HasOptionalHeader(self, DataDirectory[id]) && (self)->dm_pe.dp_nt.OptionalHeader.DataDirectory[id].Size > 0)
#define DlModule_HasExports(self)           DlModule_HasDataDirectory(self, IMAGE_DIRECTORY_ENTRY_EXPORT)
#define DlModule_GetExports(self)           (&(self)->dm_pe.dp_nt.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT])
#define DlModule_HasImports(self)           DlModule_HasDataDirectory(self, IMAGE_DIRECTORY_ENTRY_IMPORT)
#define DlModule_GetImports(self)           (&(self)->dm_pe.dp_nt.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT])
#define DlModule_HasRelocs(self)            DlModule_HasDataDirectory(self, IMAGE_DIRECTORY_ENTRY_BASERELOC)
#define DlModule_GetRelocs(self)            (&(self)->dm_pe.dp_nt.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC])
#define DlModule_HasTls(self)               DlModule_HasDataDirectory(self, IMAGE_DIRECTORY_ENTRY_TLS)
#define DlModule_GetTls(self)               (&(self)->dm_pe.dp_nt.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS])
#define DlModule_GetTlsDir(self)            ((PIMAGE_TLS_DIRECTORY)((self)->dm_loadaddr + DlModule_GetTls(self)->VirtualAddress))


DECL_END

#include <malloc.h> /* So we can override malloc() and friends */
#include <string.h> /* So we can override strdup() */

#include <libc/malloc.h> /* So we can override malloc() and friends */
#include <libdl/extension.h>
#include <libdl/module.h>

#undef __libc_malloc
#undef __libc_free
#undef __libc_calloc
#undef __libc_realloc
#undef __libc_realloc_in_place
#undef __libc_memalign
#undef __libc_strdup
#define __libc_malloc           malloc
#define __libc_free             free
#define __libc_calloc           calloc
#define __libc_realloc          realloc
#define __libc_realloc_in_place realloc_in_place
#define __libc_memalign         memalign
#define __libc_strdup           strdup

DECL_BEGIN

/* DL core operator table. */
#define dl         (*libpe_fmt.df_core)
#define dl_globals (*dl.dl_globals)

/* Even though we could, we don't want to use heap functions from libc. If we
 * did, corruption of allocations made by the hosted program would result  in
 * module information also becoming corrupt.
 *
 * Instead, we just use the same stand-alone heap implementation that's also
 * used by the core libdl (which we are extending) */
#define malloc           (*libpe_fmt.df_core->dlmalloc)
#define free             (*libpe_fmt.df_core->dlfree)
#define calloc           (*libpe_fmt.df_core->dlcalloc)
#define realloc          (*libpe_fmt.df_core->dlrealloc)
#define realloc_in_place (*libpe_fmt.df_core->dlrealloc_in_place)
#define memalign         (*libpe_fmt.df_core->dlmemalign)
#define strdup           dlstrdup
INTDEF char *CC dlstrdup(char const *str);
INTDEF ATTR_COLD int NOTHROW(CC dl_seterror_nomem)(void);


/* Called by `linker_main' from `libdl.so' when a PE binary is getting executed. */
INTDEF void *FCALL
libpe_linker_main(struct peexec_info *__restrict info,
                  uintptr_t loadaddr,
                  struct process_peb *__restrict peb);


/* Wrapper for `dlsym(3D)' that does all of the "DOS$" / "KOS$" prefix handling. */
INTDEF void *WINAPI
libpe_GetProcAddress(DlModule *self, char const *symbol_name);


DECL_END

#endif /* !GUARD_LIBDL_PE_PE_H */
