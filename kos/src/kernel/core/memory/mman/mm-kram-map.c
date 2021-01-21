/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MM_KRAM_MAP_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MM_KRAM_MAP_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/mman.h>
#include <kernel/mman/mm-kram.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/paging.h>
#include <kernel/panic.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <kos/except.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/* @param: gfp: Set of:
 *   - GFP_LOCKED:       Normal behavior
 *   - GFP_PREFLT:       Prefault everything
 *   - GFP_CALLOC:       Allocate from `mfile_zero' instead of `mfile_ndef'
 *   - GFP_ATOMIC:       Don't block when waiting to acquire any sort of lock.
 *   - GFP_NOMMAP:       Unconditionally throw `E_WOULDBLOCK_PREEMPTED'
 *   - GFP_VCBASE:       Allocate the mnode and mpart using `mcoreheap_alloc_locked_nx()'.
 *                       This also causes the `MNODE_F_COREPART' / `MPART_F_COREPART'
 *                       flags to be set for each resp. This flag is used internally
 *                       to resolve the dependency loop between this function needing
 *                       to call kmalloc() and kmalloc() needing to call this function.
 *   - GFP_MAP_32BIT:    Allocate 32-bit physical memory addresses. This flag
 *                       must be combined with `MAP_POPULATE', and should also
 *                       be combined with `GFP_LOCKED' to prevent the backing
 *                       physical memory from being altered.
 *   - GFP_MAP_PREPARED: Ensure that all mapped pages are prepared, and left as such
 *   - GFP_MAP_BELOW:    s.a. `MAP_GROWSDOWN'
 *   - GFP_MAP_ABOVE:    s.a. `MAP_GROWSUP'
 *   - GFP_MAP_NOASLR:   s.a. `MAP_NOASLR'
 *   - GFP_NOCLRC:       Don't call `system_clearcaches()' to try to free up memory
 *   - GFP_NOSWAP:       Don't move memory to swap to free up memory
 *   - Other flags are silently ignored, but will be forwarded onto
 *     other calls to kmalloc() that may need to be made internally. */
PUBLIC NOBLOCK_IF(gfp & GFP_ATOMIC) PAGEDIR_PAGEALIGNED void *FCALL
mmap_map_kernel_ram(PAGEDIR_PAGEALIGNED void *hint,
                    PAGEDIR_PAGEALIGNED size_t num_bytes,
                    gfp_t gfp, size_t min_alignment) {
	/* TODO */
	THROW(E_NOT_IMPLEMENTED_TODO);
}



/* Non-throwing version of `mmap_map_kernel_ram()'. Returns `MAP_FAILED' on error. */
PUBLIC NOBLOCK_IF(gfp & GFP_ATOMIC) PAGEDIR_PAGEALIGNED void *
NOTHROW(FCALL mmap_map_kernel_ram_nx)(PAGEDIR_PAGEALIGNED void *hint,
                                      PAGEDIR_PAGEALIGNED size_t num_bytes,
                                      gfp_t gfp, size_t min_alignment) {
	/* TODO */
	return MAP_FAILED;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MM_KRAM_MAP_C */
