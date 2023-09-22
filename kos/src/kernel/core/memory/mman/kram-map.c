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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_KRAM_MAP_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_KRAM_MAP_C 1
#define __WANT_FS_INIT
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/mman/cc.h>
#include <kernel/mman/kram.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/phys-access.h>
#include <kernel/mman/phys.h>
#include <sched/task.h>

#include <hybrid/align.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
PRIVATE NONNULL((1)) void KCALL
mfile_dbgheap_loadblocks(struct mfile *__restrict UNUSED(self),
                         pos_t UNUSED(addr),
                         physaddr_t buf, size_t num_bytes,
                         struct aio_multihandle *__restrict UNUSED(aio)) {
	PHYS_VARS;
	byte_t *map;
	uint32_t pattern = DEBUGHEAP_FRESH_MEMORY;
	if (PERTASK_GET(this_task.t_flags) & _TASK_FDBGHEAPDMEM)
		pattern = DEBUGHEAP_NO_MANS_LAND;
	assert(IS_ALIGNED(buf, PAGESIZE));
	assert(IS_ALIGNED(num_bytes, PAGESIZE));
	IF_PHYS_IDENTITY(buf, num_bytes, {
		memsetl(PHYS_TO_IDENTITY(buf), pattern, num_bytes / 4);
		return;
	});
	if unlikely(!num_bytes)
		return;
	map = phys_pushpage(buf);
	for (;;) {
		memsetl(map, pattern, PAGESIZE / 4);
		if (num_bytes <= PAGESIZE)
			break;
		num_bytes -= PAGESIZE;
		buf += PAGESIZE;
		map = phys_loadpage(buf);
	}
	phys_pop();
}

PRIVATE struct mfile_ops const mfile_dbgheap_ops = {
	.mo_loadblocks = &mfile_dbgheap_loadblocks,
};

/* Special file used to initialize debug-heap memory. */
PUBLIC struct mfile mfile_dbgheap = {
	MFILE_INIT_mf_refcnt(1), /* +1: mfile_dbgheap */
	MFILE_INIT_mf_ops(&mfile_dbgheap_ops),
	MFILE_INIT_mf_lock,
	MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
	MFILE_INIT_mf_initdone,
	MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
	MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
	MFILE_INIT_mf_meta,
	MFILE_INIT_mf_flags(MFILE_F_ATTRCHANGED | MFILE_F_CHANGED |
	                    MFILE_F_NOATIME | MFILE_F_NOMTIME |
	                    MFILE_F_FIXEDFILESIZE),
	MFILE_INIT_mf_trunclock,
	MFILE_INIT_mf_filesize((uint64_t)-1),
	MFILE_INIT_mf_atime(0, 0),
	MFILE_INIT_mf_mtime(0, 0),
	MFILE_INIT_mf_ctime(0, 0),
	MFILE_INIT_mf_btime(0, 0),
	MFILE_INIT_mf_msalign(NULL),
};
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */


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
#include "kram-map.c.inl"
#define DEFINE_mman_map_kram_nx
#include "kram-map.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_KRAM_MAP_C */
