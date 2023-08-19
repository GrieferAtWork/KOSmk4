/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_MALLOC_H
#define GUARD_KERNEL_SRC_MEMORY_MALLOC_H 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/types.h>

#include <stdbool.h>

DECL_BEGIN

/*
 * Untraced kmalloc() functions
 *
 * These  are  used  when  "nomall"  is  given  on  the  kernel  commandline,
 * or when the kernel was built with `CONFIG_NO_KERNEL_TRACE_MALLOC' defined.
 */

INTDEF ATTR_PURE WUNUSED size_t NOTHROW(KCALL untraced_kmalloc_usable_size)(void *ptr);
INTDEF ATTR_PURE WUNUSED bool NOTHROW(KCALL untraced_kmalloc_islocked)(void *ptr);
INTDEF void NOTHROW(KCALL untraced_kfree)(void *ptr);
INTDEF void NOTHROW(KCALL untraced_kffree)(void *ptr, gfp_t flags);
INTDEF NOBLOCK void NOTHROW(KCALL untraced_kmalloc_validate)(void);
INTDEF size_t KCALL untraced_kmalloc_leaks(void) THROWS(E_WOULDBLOCK);
INTDEF kmalloc_leaks_t KCALL untraced_kmalloc_leaks_collect(void) THROWS(E_WOULDBLOCK);
INTDEF ssize_t KCALL untraced_kmalloc_leaks_print(kmalloc_leaks_t leaks, __pformatprinter printer, void *arg, size_t *pnum_leaks);
INTDEF NOBLOCK ATTR_PURE WUNUSED size_t NOTHROW(KCALL untraced_kmalloc_leaks_count)(kmalloc_leaks_t leaks);
INTDEF NOBLOCK ATTR_PURE memleak_t NOTHROW(FCALL untraced_memleak_next)(kmalloc_leaks_t leaks, memleak_t prev);
INTDEF NOBLOCK ATTR_PURE void *FCALL untraced_memleak_getattr(memleak_t self, uintptr_t attr);
INTDEF NOBLOCK void NOTHROW(KCALL untraced_kmalloc_leaks_release)(kmalloc_leaks_t leaks, unsigned int now);
INTDEF NOBLOCK_IF(gfp & GFP_ATOMIC) WUNUSED void *NOTHROW(KCALL untraced_kmalloc_trace_nx)(void *base, size_t num_bytes, gfp_t gfp, unsigned int tb_skip);
INTDEF NOBLOCK_IF(gfp & GFP_ATOMIC) ATTR_RETNONNULL void *KCALL untraced_kmalloc_trace(void *base, size_t num_bytes, gfp_t gfp, unsigned int tb_skip) THROWS(E_BADALLOC, E_WOULDBLOCK);
INTDEF NOBLOCK ATTR_CONST void *NOTHROW(KCALL untraced_kmalloc_untrace)(void *ptr);
INTDEF NOBLOCK ATTR_CONST void *NOTHROW(KCALL untraced_kmalloc_untrace_n)(void *base, size_t num_bytes);
INTDEF NOBLOCK size_t NOTHROW(KCALL untraced_kmalloc_traceback)(void *ptr, /*out*/ void **tb, size_t buflen, pid_t *p_alloc_roottid);
INTDEF NOBLOCK ssize_t KCALL untraced_kmalloc_printtrace(void *ptr, __pformatprinter printer, void *arg);
INTDEF ATTR_MALLOC WUNUSED void *KCALL untraced_kmalloc_noslab(size_t n_bytes, gfp_t flags);
INTDEF ATTR_MALLOC WUNUSED void *NOTHROW(KCALL untraced_kmalloc_noslab_nx)(size_t n_bytes, gfp_t flags);
INTDEF ATTR_MALLOC WUNUSED void *KCALL untraced_kmalloc(size_t n_bytes, gfp_t flags);
INTDEF ATTR_MALLOC WUNUSED void *NOTHROW(KCALL untraced_kmalloc_nx)(size_t n_bytes, gfp_t flags);
INTDEF ATTR_MALLOC WUNUSED void *KCALL untraced_kmemalign(size_t min_alignment, size_t n_bytes, gfp_t flags);
INTDEF ATTR_MALLOC WUNUSED void *NOTHROW(KCALL untraced_kmemalign_nx)(size_t min_alignment, size_t n_bytes, gfp_t flags);
INTDEF ATTR_MALLOC WUNUSED void *KCALL untraced_kmemalign_offset(size_t min_alignment, ptrdiff_t offset, size_t n_bytes, gfp_t flags);
INTDEF ATTR_MALLOC WUNUSED void *NOTHROW(KCALL untraced_kmemalign_offset_nx)(size_t min_alignment, ptrdiff_t offset, size_t n_bytes, gfp_t flags);
INTDEF void *KCALL untraced_krealloc_in_place(void *ptr,size_t n_bytes, gfp_t flags);
INTDEF void *NOTHROW(KCALL untraced_krealloc_in_place_nx)(void *ptr,size_t n_bytes, gfp_t flags);
INTDEF void *KCALL untraced_krealloc(void *ptr, size_t n_bytes, gfp_t flags);
INTDEF void *NOTHROW(KCALL untraced_krealloc_nx)(void *ptr, size_t n_bytes, gfp_t flags);
INTDEF void *KCALL untraced_krealign(void *ptr, size_t min_alignment, size_t n_bytes, gfp_t flags);
INTDEF void *NOTHROW(KCALL untraced_krealign_nx)(void *ptr, size_t min_alignment, size_t n_bytes, gfp_t flags);
INTDEF void *KCALL untraced_krealign_offset(void *ptr, size_t min_alignment, ptrdiff_t offset, size_t n_bytes, gfp_t flags);
INTDEF void *NOTHROW(KCALL untraced_krealign_offset_nx)(void *ptr, size_t min_alignment, ptrdiff_t offset, size_t n_bytes, gfp_t flags);

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MALLOC_H */
