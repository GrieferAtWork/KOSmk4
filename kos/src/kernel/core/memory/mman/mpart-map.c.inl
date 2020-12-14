/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "mpart-map.c"
#define DEFINE_mpart_mmap
//#define DEFINE_mpart_mmap_p
#endif /* __INTELLISENSE__ */

#include <kernel/mman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart.h>
#include <kernel/paging.h>

#include <hybrid/align.h>

#include <assert.h>
#include <stddef.h>

DECL_BEGIN

#ifndef vector_getblockstatus
#define vector_getblockstatus(vector, i)                      \
	(((vector)[(i) / BITSET_ITEMS_PER_WORD] >>                \
	  (((i) % BITSET_ITEMS_PER_WORD) * MPART_BLOCK_STBITS)) & \
	 (((unsigned int)1 << MPART_BLOCK_STBITS) - 1))
#endif /* !vector_getblockstatus */


/* (Re-)map the given mem-part into a page directory.
 * The caller must ensure:
 *   - mpart_lock_acquired(self)
 *   - pagedir_prepare_p(self, addr, size)     (was called)
 *
 * NOTES:
 *   - When mapping blocks not marked as `MPART_BLOCK_ST_CHNG',
 *     the `PAGEDIR_MAP_FWRITE' perm-flag is automatically cleared.
 *   - When mapping blocks marked as `MPART_BLOCK_ST_NDEF' or `MPART_BLOCK_ST_INIT',
 *     the `PAGEDIR_MAP_FEXEC', `PAGEDIR_MAP_FREAD' and `PAGEDIR_MAP_FWRITE' perm-
 *     flags are automatically cleared. */
#ifdef DEFINE_mpart_mmap_p
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_mmap_p)(struct mpart *__restrict self, pagedir_phys_t pdir,
                            PAGEDIR_PAGEALIGNED void *addr,
                            PAGEDIR_PAGEALIGNED size_t size,
                            PAGEDIR_PAGEALIGNED mpart_reladdr_t offset,
                            u16 perm)
#define LOCAL_pagedir_map(addr, num_bytes, phys, perm) pagedir_map_p(pdir, addr, num_bytes, phys, perm)
#define LOCAL_pagedir_unmap(addr, num_bytes)           pagedir_unmap_p(pdir, addr, num_bytes)
#elif defined(DEFINE_mpart_mmap)

/* Same as `mpart_mmap_p()', but always map into the current page directory. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_mmap)(struct mpart *__restrict self,
                          PAGEDIR_PAGEALIGNED void *addr,
                          PAGEDIR_PAGEALIGNED size_t size,
                          PAGEDIR_PAGEALIGNED mpart_reladdr_t offset,
                          u16 perm)
#define LOCAL_pagedir_map(addr, num_bytes, phys, perm) pagedir_map(addr, num_bytes, phys, perm)
#define LOCAL_pagedir_unmap(addr, num_bytes)           pagedir_unmap(addr, num_bytes)
#else /* ... */
#error "Bad configuration"
#endif /* !... */
{
	size_t i, block_size;
	unsigned int shift;
	bitset_word_t const *bitset;
	assert(mpart_lock_acquired(self));
	assert(IS_ALIGNED((uintptr_t)addr, PAGESIZE));
	assert(IS_ALIGNED(size, PAGESIZE));
	assert(IS_ALIGNED(offset, PAGESIZE));
	assert((offset + size) <= mpart_getsize(self));
	shift      = self->mp_file->mf_blockshift;
	block_size = (size_t)1 << shift;
	bitset     = self->mp_blkst_ptr;
	if (self->mp_flags & MPART_F_BLKST_INL)
		bitset = &self->mp_blkst_inl;
#define getstate(i) vector_getblockstatus(bitset, i)
	switch (__builtin_expect(self->mp_state, MPART_ST_MEM)) {

	case MPART_ST_MEM:
		/* Simplest case: we can just directly map the proper sub-range! */
		if (bitset == NULL) {
			/* All blocks are implicitly marked CHNG, so we can map with full permissions! */
			LOCAL_pagedir_map(addr, size,
			                  physpage2addr(self->mp_mem.mc_start) + offset,
			                  perm);
		} else
#ifndef __OPTIMIZE_SIZE__
		if (shift == PAGESHIFT) {
			/* Simple case: 1 page == 1 block */
			/* TODO */
		} else
#endif /* !__OPTIMIZE_SIZE__ */
		{
			/* TODO */
		}
		break;

	case MPART_ST_MEM_SC:
		/* TODO */
		break;

	default:
		/* Default case: Cannot map anything specific, so just
		 * unmap, thus causing a #PF that will do all the correct
		 * handling of the mapping upon memory being accessed. */
		LOCAL_pagedir_unmap(addr, size);
		break;
	}
#undef getstate
}

#undef LOCAL_pagedir_map
#undef LOCAL_pagedir_unmap

DECL_END

#undef DEFINE_mpart_mmap
#undef DEFINE_mpart_mmap_p
