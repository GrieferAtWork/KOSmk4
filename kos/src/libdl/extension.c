/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBDL_EXTENSION_C
#define GUARD_LIBDL_EXTENSION_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

/* Keep this one the first */
#include "dl.h"
/**/

#include <atomic.h>

DECL_BEGIN

/* [0..1][ATOMIC(APPEND)] Chain of registered DL extensions.
 * NOTE: Once registered, a DL extension cannot be  deleted! */
INTERN struct dlmodule_format *dl_extensions = NULL;

PRIVATE struct dlcore_ops dl_coreops;

/* Heap functions used by the libdl core. */
INTDEF ATTR_MALLOC WUNUSED void *LIBCCALL dlmalloc(size_t bytes) ASMNAME("malloc");
INTDEF void LIBCCALL dlfree(void *mem) ASMNAME("free");
INTDEF ATTR_MALLOC WUNUSED void *LIBCCALL dlcalloc(size_t n_elements, size_t elem_size) ASMNAME("calloc");
INTDEF WUNUSED void *LIBCCALL dlrealloc(void *oldmem, size_t bytes) ASMNAME("realloc");
INTDEF WUNUSED void *LIBCCALL dlrealloc_in_place(void *oldmem, size_t bytes) ASMNAME("realloc_in_place");
INTDEF WUNUSED void *LIBCCALL dlmemalign(size_t alignment, size_t bytes) ASMNAME("memalign");
INTDEF ATTR_PURE WUNUSED size_t LIBCCALL dlmalloc_usable_size(void *mem) ASMNAME("malloc_usable_size");


/* Lazily initialize and return the libdl core ops V-table. */
INTERN ATTR_RETNONNULL WUNUSED struct dlcore_ops *
NOTHROW(CC dl_getcoreops)(void) {
	struct dlcore_ops *result;
	result = &dl_coreops;
	if (!result->DlModule_Destroy) {
		COMPILER_WRITE_BARRIER();
#define DL_COREOPS_SKIP_DLMODULE_DESTROY 1
#define DL_COREOP(attr, return, nothrow, cc, name, args) result->name = &name;
#define DL_COREFIELD(type, name)                         result->name = &name;
#include <libdl/coreops.def>
#undef DL_COREOPS_SKIP_DLMODULE_DESTROY
		COMPILER_WRITE_BARRIER();
		atomic_write(&result->DlModule_Destroy, &DlModule_Destroy);
	}
	return result;
}


DECL_END

#endif /* !GUARD_LIBDL_EXTENSION_C */
