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
#ifdef __INTELLISENSE__
#include "mpart-map.c"
#define DEFINE_mpart_mmap
//#define DEFINE_mpart_mmap_p
#endif /* __INTELLISENSE__ */

#include <debugger/rt.h>
#include <kernel/mman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>
#include <kernel/paging.h>
#include <sched/task.h>

#include <hybrid/align.h>

#include <assert.h>
#include <stddef.h>

DECL_BEGIN

#ifndef vector_getblockstatus
#define vector_getblockstatus(vector, i)                            \
	(((vector)[(i) / MPART_BLKST_BLOCKS_PER_WORD] >>                \
	  (((i) % MPART_BLKST_BLOCKS_PER_WORD) * MPART_BLOCK_STBITS)) & \
	 (((unsigned int)1 << MPART_BLOCK_STBITS) - 1))
#endif /* !vector_getblockstatus */


#ifdef DEFINE_mpart_mmap_p
PRIVATE NOBLOCK u16
NOTHROW(FCALL mpart_mmap_p_impl)(mpart_blkst_word_t const *bitset, unsigned int shift,
                                 physaddr_t baseaddr, PAGEDIR_PAGEALIGNED void *addr,
                                 PAGEDIR_PAGEALIGNED size_t chunk_size,
                                 PAGEDIR_PAGEALIGNED mpart_reladdr_t baseaddr_offset,
                                 u16 perm, pagedir_phys_t pdir)
#define LOCAL_mpart_mmap_p_impl(bitset, shift, baseaddr, addr, chunk_size, baseaddr_offset, perm) \
	mpart_mmap_p_impl(bitset, shift, baseaddr, addr, chunk_size, baseaddr_offset, perm, pdir)
#define LOCAL_pagedir_map(addr, num_bytes, phys, perm) \
	pagedir_map_p(pdir, addr, num_bytes, phys, perm)
#elif defined(DEFINE_mpart_mmap)
/* Same as `mpart_mmap_p()', but always map into the current page directory. */
PRIVATE NOBLOCK u16
NOTHROW(FCALL mpart_mmap_impl)(mpart_blkst_word_t const *bitset, unsigned int shift,
                               physaddr_t baseaddr, PAGEDIR_PAGEALIGNED void *addr,
                               PAGEDIR_PAGEALIGNED size_t chunk_size,
                               PAGEDIR_PAGEALIGNED mpart_reladdr_t baseaddr_offset,
                               u16 perm)
#define LOCAL_mpart_mmap_p_impl mpart_mmap_impl
#define LOCAL_pagedir_map       pagedir_map
#else /* ... */
#error "Bad configuration"
#endif /* !... */
{
	u16 result;
	size_t i;
#define getstate(i) vector_getblockstatus(bitset, i)
#define getstate_smallpages(start_block_index, blocks_per_page, retval) \
	do {                                                                \
		size_t _i;                                                      \
		(retval) = getstate(start_block_index);                         \
		for (_i = 1; _i < (blocks_per_page); ++_i) {                    \
			unsigned int _temp = getstate((start_block_index) + _i);    \
			(retval)           = MPART_BLOCK_COMMON(retval, _temp);     \
		}                                                               \
	}	__WHILE0
	if (bitset == NULL) {
		/* All blocks are implicitly marked CHNG, so we can map with full permissions! */
		result = perm;
		LOCAL_pagedir_map(addr, chunk_size, baseaddr, perm);
	} else {
		size_t page_start, page_end;
		page_start = baseaddr_offset >> PAGESHIFT;
		page_end   = (baseaddr_offset + chunk_size) >> PAGESHIFT;
		result     = perm & ~PAGEDIR_MAP_FWRITE;
#ifndef __OPTIMIZE_SIZE__
		if likely(shift == PAGESHIFT) {
			for (i = page_start; i < page_end;) {
				unsigned int st = getstate(i);
				if (st == MPART_BLOCK_ST_LOAD) {
					size_t addr_offset, endpage;
do_load_whole_pages_readonly:
					endpage = i + 1;
					while (endpage < page_end) {
						st = getstate(endpage);
						if (st == MPART_BLOCK_ST_LOAD) {
							++endpage;
						} else if (st == MPART_BLOCK_ST_CHNG &&
						           !(perm & PAGEDIR_MAP_FWRITE)) {
							++endpage;
						} else {
							break;
						}
					}
					/* Load as continuous, read-only memory. */
					addr_offset = (i - page_start) * PAGESIZE;
					LOCAL_pagedir_map((byte_t *)addr + addr_offset,
					                  (endpage - i) * PAGESIZE,
					                  baseaddr + addr_offset,
					                  perm & ~PAGEDIR_MAP_FWRITE);
					i = endpage;
				} else if (st == MPART_BLOCK_ST_CHNG) {
					size_t addr_offset, endpage;
					if (!(perm & PAGEDIR_MAP_FWRITE))
						goto do_load_whole_pages_readonly;
					endpage = i + 1;
					while (endpage < page_end &&
					       getstate(endpage) == MPART_BLOCK_ST_CHNG)
						++endpage;
					/* Load as continuous, read/write memory. */
					addr_offset = (i - page_start) * PAGESIZE;
					LOCAL_pagedir_map((byte_t *)addr + addr_offset,
					                  (endpage - i) * PAGESIZE,
					                  baseaddr + addr_offset, perm);
					result |= PAGEDIR_MAP_FWRITE;
					i = endpage;
				} else {
					++i;
				}
			}
		} else
#endif /* !__OPTIMIZE_SIZE__ */
		if (shift < PAGESHIFT) {
			/* Blocks are smaller than a single page */
			size_t blocks_per_page;
			unsigned int page_to_block_shift;
			page_to_block_shift = PAGESHIFT - shift;
			blocks_per_page     = (size_t)1 << page_to_block_shift;
			assert(blocks_per_page >= 2);
			for (i = page_start; i < page_end;) {
				unsigned int st;
				getstate_smallpages(i << page_to_block_shift,
				                    blocks_per_page, st);
				if (st == MPART_BLOCK_ST_LOAD) {
					size_t addr_offset, endpage;
do_load_small_pages_readonly:
					endpage = i + 1;
					while (endpage < page_end) {
						getstate_smallpages(endpage << page_to_block_shift,
						                    blocks_per_page, st);
						if (st == MPART_BLOCK_ST_LOAD) {
							++endpage;
						} else if (st == MPART_BLOCK_ST_CHNG &&
						           !(perm & PAGEDIR_MAP_FWRITE)) {
							++endpage;
						} else {
							break;
						}
					}
					/* Load as continuous, read-only memory. */
					addr_offset = (i - page_start) * PAGESIZE;
					LOCAL_pagedir_map((byte_t *)addr + addr_offset,
					                  (endpage - i) * PAGESIZE,
					                  baseaddr + addr_offset,
					                  perm & ~PAGEDIR_MAP_FWRITE);
					i = endpage;
				} else if (st == MPART_BLOCK_ST_CHNG) {
					size_t addr_offset, endpage;
					if (!(perm & PAGEDIR_MAP_FWRITE))
						goto do_load_small_pages_readonly;
					endpage = i + 1;
					while (endpage < page_end) {
						getstate_smallpages(endpage << page_to_block_shift,
						                    blocks_per_page, st);
						if (st != MPART_BLOCK_ST_CHNG)
							break;
						++endpage;
					}
					/* Load as continuous, read/write memory. */
					addr_offset = (i - page_start) * PAGESIZE;
					LOCAL_pagedir_map((byte_t *)addr + addr_offset,
					                  (endpage - i) * PAGESIZE,
					                  baseaddr + addr_offset, perm);
					result |= PAGEDIR_MAP_FWRITE;
					i = endpage;
				} else {
					++i;
				}
			}
		} else {
			/* Large pages */
			unsigned int block_to_page_shift;
#ifdef __OPTIMIZE_SIZE__
			assert(shift >= PAGESHIFT);
#else  /* __OPTIMIZE_SIZE__ */
			assert(shift > PAGESHIFT);
#endif /* !__OPTIMIZE_SIZE__ */
			block_to_page_shift = PAGESHIFT - shift;
			for (i = page_start; i < page_end;) {
				unsigned int st = getstate(i >> block_to_page_shift);
				if (st == MPART_BLOCK_ST_LOAD) {
					size_t addr_offset, endpage;
do_load_large_pages_readonly:
					endpage = i + 1;
					while (endpage < page_end) {
						st = getstate(endpage >> block_to_page_shift);
						if (st == MPART_BLOCK_ST_LOAD) {
							++endpage;
						} else if (st == MPART_BLOCK_ST_CHNG &&
						           !(perm & PAGEDIR_MAP_FWRITE)) {
							++endpage;
						} else {
							break;
						}
					}
					/* Load as continuous, read-only memory. */
					addr_offset = (i - page_start) * PAGESIZE;
					LOCAL_pagedir_map((byte_t *)addr + addr_offset,
					                  (endpage - i) * PAGESIZE,
					                  baseaddr + addr_offset,
					                  perm & ~PAGEDIR_MAP_FWRITE);
					i = endpage;
				} else if (st == MPART_BLOCK_ST_CHNG) {
					size_t addr_offset, endpage;
					if (!(perm & PAGEDIR_MAP_FWRITE))
						goto do_load_large_pages_readonly;
					endpage = i + 1;
					while (endpage < page_end &&
					       getstate(endpage >> block_to_page_shift) == MPART_BLOCK_ST_CHNG)
						++endpage;
					/* Load as continuous, read/write memory. */
					addr_offset = (i - page_start) * PAGESIZE;
					LOCAL_pagedir_map((byte_t *)addr + addr_offset,
					                  (endpage - i) * PAGESIZE,
					                  baseaddr + addr_offset, perm);
					result |= PAGEDIR_MAP_FWRITE;
					i = endpage;
				} else {
					++i;
				}
			}
		}
	}
	return result;
#undef getstate_smallpages
#undef getstate
}

/* (Re-)map the given mem-part into a page directory.
 * The caller must ensure:
 *   - mpart_lock_acquired(self)               (unless `self' was accessed from a hinted node,
 *                                              or the caller knows that `self' can't be accessed
 *                                              from the outside world)
 *   - pagedir_prepare_p(self, addr, size)     (was called)
 *
 * NOTES:
 *   - When mapping blocks not marked as `MPART_BLOCK_ST_CHNG',
 *     the `PAGEDIR_MAP_FWRITE' perm-flag is automatically cleared.
 *   - When mapping blocks marked as `MPART_BLOCK_ST_NDEF' or `MPART_BLOCK_ST_INIT',
 *     the `PAGEDIR_MAP_FEXEC', `PAGEDIR_MAP_FREAD' and `PAGEDIR_MAP_FWRITE' perm-
 *     flags are automatically cleared.
 *
 * @return: * : The union of permissions actually applied to all pages.
 *              This may be used to figure out if write permissions were
 *              actually given to any of the requested pages. */
#ifdef DEFINE_mpart_mmap_p
PUBLIC NOBLOCK NONNULL((1)) u16
NOTHROW(FCALL mpart_mmap_p)(struct mpart *__restrict self, pagedir_phys_t pdir,
                            PAGEDIR_PAGEALIGNED void *addr,
                            PAGEDIR_PAGEALIGNED size_t size,
                            PAGEDIR_PAGEALIGNED mpart_reladdr_t offset,
                            u16 perm)
#define LOCAL_pagedir_unmap(addr, num_bytes) \
	pagedir_unmap_p(pdir, addr, num_bytes)
#elif defined(DEFINE_mpart_mmap)

/* Same as `mpart_mmap_p()', but always map into the current page directory. */
PUBLIC NOBLOCK NONNULL((1)) u16
NOTHROW(FCALL mpart_mmap)(struct mpart *__restrict self,
                          PAGEDIR_PAGEALIGNED void *addr,
                          PAGEDIR_PAGEALIGNED size_t size,
                          PAGEDIR_PAGEALIGNED mpart_reladdr_t offset,
                          u16 perm)
#define LOCAL_pagedir_unmap pagedir_unmap
#else /* ... */
#error "Bad configuration"
#endif /* !... */
{
	u16 result;
	unsigned int shift;
	mpart_blkst_word_t const *bitset;
	assert(IS_ALIGNED((uintptr_t)addr, PAGESIZE));
	assert(IS_ALIGNED(size, PAGESIZE));
	assert(IS_ALIGNED(offset, PAGESIZE));
	assert((offset + size) >= offset);
	assert((offset + size) <= mpart_getsize(self));
	shift  = self->mp_file->mf_blockshift;
	bitset = self->mp_blkst_ptr;
	if (self->mp_flags & MPART_F_BLKST_INL)
		bitset = &self->mp_blkst_inl;
	__builtin_assume(&self->mp_blkst_inl != NULL);
	switch (__builtin_expect(self->mp_state, MPART_ST_MEM)) {

	case MPART_ST_MEM: {
		/* Simplest case: we can just directly map the proper sub-range! */
		physaddr_t baseaddr;
		baseaddr = physpage2addr(self->mp_mem.mc_start) + offset;
		result = LOCAL_mpart_mmap_p_impl(bitset, shift, baseaddr,
		                                 addr, size, offset, perm);
	}	break;

	case MPART_ST_MEM_SC: {
		size_t i;
		struct mchunk *vec;
		mpart_reladdr_t chunk_offset;
		chunk_offset = offset;
		result       = 0;
		vec          = self->mp_mem_sc.ms_v;
		for (i = 0;; ++i) {
			size_t chunk_size;
			assert(i < self->mp_mem_sc.ms_c);
			chunk_size = (size_t)vec[i].mc_size << PAGESHIFT;
			if (chunk_offset >= chunk_size) {
				/* Uninteresting chunk... */
				chunk_offset -= chunk_size;
				continue;
			}
			chunk_size -= chunk_offset;
			if (chunk_size > size)
				chunk_size = size;
			/* Map (the requested sub-range of) this chunk */
			assert(vec[i].mc_start != PHYSPAGE_INVALID);
			result |= LOCAL_mpart_mmap_p_impl(bitset, shift,
			                                  physpage2addr(vec[i].mc_start) + chunk_offset,
			                                  addr, chunk_size, offset, perm);
			if (chunk_size >= size)
				break;
			offset += chunk_size;
			addr = (byte_t *)addr + chunk_size;
			size -= chunk_size;
			chunk_offset = 0;
		}
	}	break;

	default:
		/* Other part-types can't be mapped into memory... */
		LOCAL_pagedir_unmap(addr, size);
		result = 0;
		break;
	}
	return result;
}

#undef LOCAL_mpart_mmap_p_impl
#undef LOCAL_pagedir_unmap
#undef LOCAL_pagedir_map

DECL_END

#undef DEFINE_mpart_mmap
#undef DEFINE_mpart_mmap_p
