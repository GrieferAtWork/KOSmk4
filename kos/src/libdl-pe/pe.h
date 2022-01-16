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
#include <nt/winnt.h>

DECL_BEGIN

/* PE loader extension for libdl */
struct dlmodule_format;
INTDEF struct dlmodule_format libpe_fmt;

/* Per-DlModule extension data for PE */
struct dlmodule_pe {
	IMAGE_NT_HEADERS                              dp_nt;    /* [const] NT file header */
	COMPILER_FLEXIBLE_ARRAY(IMAGE_SECTION_HEADER, dp_sect); /* [const] Section headers */
};

DECL_END

#include <libdl/extension.h>
#include <libdl/module.h>

DECL_BEGIN

/* DL core operator table. */
#define dl (*libpe_fmt.df_core)

/* Called by `linker_main' from `libdl.so' when a PE binary is getting executed. */
INTDEF void *FCALL
libpe_linker_main(struct peexec_info *__restrict info,
                  uintptr_t loadaddr,
                  struct process_peb *__restrict peb);


DECL_END

#endif /* !GUARD_LIBDL_PE_PE_H */
