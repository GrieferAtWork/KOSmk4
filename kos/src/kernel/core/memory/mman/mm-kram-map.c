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

#include <kernel/driver.h>
#include <kernel/heap.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mm-kram.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/phys-access.h>
#include <kernel/mman/phys.h>

#include <hybrid/align.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

#ifndef NDEBUG
#define DBG_memset(dst, byte, num_bytes) memset(dst, byte, num_bytes)
#else /* !NDEBUG */
#define DBG_memset(dst, byte, num_bytes) (void)0
#endif /* NDEBUG */

#ifdef CONFIG_DEBUG_HEAP
PRIVATE NONNULL((1)) void KCALL
mfile_dbgheap_loadblocks(struct mfile *__restrict UNUSED(self),
                         mfile_block_t UNUSED(first_block),
                         physaddr_t buffer, size_t num_blocks) {
	PHYS_VARS;
	byte_t *map;
	assert(IS_ALIGNED(buffer, PAGESIZE));
	IF_PHYS_IDENTITY(dst, num_blocks * PAGESIZE, {
		memsetl(PHYS_TO_IDENTITY(dst),
		        DEBUGHEAP_FRESH_MEMORY,
		        num_blocks * PAGESIZE);
		return;
	});
	if unlikely(!num_blocks)
		return;
	map = phys_pushpage(buffer);
	for (;;) {
		memsetl(map, DEBUGHEAP_FRESH_MEMORY, PAGESIZE);
		--num_blocks;
		if (!num_blocks)
			break;
		buffer += PAGESIZE;
		map = phys_loadpage(buffer);
	}
	phys_pop();
}


PUBLIC_CONST struct mfile_ops const mfile_dbgheap_ops = {
	/* .mo_destroy    = */ NULL,
	/* .mo_initpart   = */ NULL,
	/* .mo_loadblocks = */ &mfile_dbgheap_loadblocks,
};

/* Special file used to initialize debug-heap memory. */
PUBLIC struct mfile mfile_dbgheap = MFILE_INIT_ANON(&mfile_dbgheap_ops, PAGESHIFT);
#endif /* CONFIG_DEBUG_HEAP */


/* Zero-initialize physical pages, but skip those with `page_iszero()' */
PRIVATE NOBLOCK void
NOTHROW(FCALL bzero_pages)(PAGEDIR_PAGEALIGNED void *vbase,
                           physpage_t pbase, physpagecnt_t count) {
	physpagecnt_t i;
	for (i = 0; i < count; ++i) {
		if (!page_iszero(pbase + i))
			bzero(vbase, PAGESIZE);
		vbase = (byte_t *)vbase + PAGESIZE;
	}
}


/* Try some things to reclaim system memory. */
PRIVATE NOBLOCK bool
NOTHROW(FCALL kram_reclaim_memory)(uintptr_t *__restrict p_cache_version,
                                   gfp_t flags) {
	if (!(flags & GFP_NOCLRC)) {
		if (system_clearcaches_s(p_cache_version))
			return true;
	}
	if (!(flags & GFP_NOSWAP)) {
		/* TODO: Try to off-load memory to swap. */
	}
	return false;
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL kram_freevec)(struct mchunk *__restrict vec,
                            size_t count) {
	while (count) {
		--count;
		page_ccfree(vec[count].mc_start,
		            vec[count].mc_size);
	}
	kfree(vec);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL kram_part_destroy)(struct mpart *__restrict self) {
	switch (self->mp_state) {

	case MPART_ST_MEM:
		page_ccfree(self->mp_mem.mc_start,
		            self->mp_mem.mc_size);
		break;

	case MPART_ST_MEM_SC:
		assert(self->mp_mem_sc.ms_c >= 1);
		kram_freevec(self->mp_mem_sc.ms_v,
		             self->mp_mem_sc.ms_c);
		break;

	default:
		break;
	}
	mpart_free(self);
}


DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_mman_map_kram
#include "mm-kram-map.c.inl"
#define DEFINE_mman_map_kram_nx
#include "mm-kram-map.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MM_KRAM_MAP_C */
