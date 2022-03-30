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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_KRAM_UNMAP_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_KRAM_UNMAP_C 1
#define __WANT_MPART__mp_nodlsts /* mpart_getnodlst_from_mnodeflags() */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/path.h>
#include <kernel/heap.h>
#include <kernel/mman.h>
#include <kernel/mman/kram.h>
#include <kernel/mman/mcoreheap.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/module.h>
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/sync.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/swap.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/minmax.h>

#include <kos/except.h>
#include <kos/lockop.h>

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#if 0
#include <kernel/printk.h>
#define TRACE_KRAM(...) printk(__VA_ARGS__)
#else
#define TRACE_KRAM(...) (void)0
#endif

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

STATIC_ASSERT_MSG(sizeof(struct mman_unmap_kram_job) <= PAGESIZE,
                  "There's really no reason for this to fail, but you should "
                  "be aware that code below assumes that an unmap-job can be "
                  "stored in a single page, thus allowing it to be stored in "
                  "its own unmap-area (s.a. `mman_unmap_kram()')");

#ifndef CONFIG_NO_SMP
/* Atomic counter for how many CPUs are currently initializing hinted pages (s.a. `MNODE_F_MHINT').
 * This counter behaves similar to the in-use counter found in <kos/aref.h>, and is needed in order
 * to  allow for syncing  of internal re-trace operations  in `mman_unmap_kram_locked()' with other
 * CPUs having previously started initializing hinted pages.
 *
 * For more information on the data race solved by this counter, see the detailed explanation
 * of `mman_kernel_hintinit_inuse' within `mman_unmap_kram_locked()' */
PUBLIC WEAK unsigned int mman_kernel_hintinit_inuse = 0;
#endif /* !CONFIG_NO_SMP */


PRIVATE NOBLOCK void
NOTHROW(FCALL mpart_freefun_phys)(physpage_t base,
                                  physpagecnt_t num_pages,
                                  gfp_t flags) {
	page_ffree(base, num_pages, (flags & GFP_CALLOC) != 0);
}
PRIVATE NOBLOCK void
NOTHROW(FCALL mpart_freefun_swap)(physpage_t base,
                                  physpagecnt_t num_pages,
                                  gfp_t UNUSED(flags)) {
	swap_free(base, num_pages);
}
INTERN NOBLOCK void /* used in `mpart-trim.c' */
NOTHROW(FCALL mpart_freefun_noop)(physpage_t UNUSED(base),
                                  physpagecnt_t UNUSED(num_pages),
                                  gfp_t UNUSED(flags)) {
}

typedef NOBLOCK void
/*NOTHROW*/(FCALL *freefun_t)(physpage_t base, physpagecnt_t num_pages, gfp_t flags);
INTERN ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) freefun_t /* used in `mpart-trim.c' */
NOTHROW(FCALL mpart_getfreefun)(struct mpart const *__restrict self) {
	freefun_t result;
	switch (self->mp_state) {

	case MPART_ST_SWP:
	case MPART_ST_SWP_SC:
		result = &mpart_freefun_swap;
		break;

	case MPART_ST_MEM:
	case MPART_ST_MEM_SC:
		result = &mpart_freefun_phys;
		if (self->mp_flags & MPART_F_NOFREE)
			result = &mpart_freefun_noop;
		break;

	default:
		result = &mpart_freefun_noop;
		break;
	}
	return result;
}



PRIVATE NOBLOCK NONNULL((1, 3)) void
NOTHROW(FCALL mchunkvec_truncate)(struct mchunkvec *__restrict self,
                                  physpagecnt_t total_pages,
                                  freefun_t freefun, gfp_t flags,
                                  bool maybe_hinted) {
	size_t keep, i;
	physpagecnt_t total = 0;
	assert(total_pages != 0);
	for (i = 0;; ++i) {
		assert(i < self->ms_c);
		total += self->ms_v[i].mc_size;
		if (total >= total_pages)
			break;
	}
	total -= self->ms_v[i].mc_size;
	keep = total_pages - total;
	assert(keep != 0);
	assert(keep <= self->ms_v[i].mc_size);
	if (keep < self->ms_v[i].mc_size) {
		(*freefun)(self->ms_v[i].mc_start + keep,
		           self->ms_v[i].mc_size - keep,
		           flags);
		self->ms_v[i].mc_size = keep;
	}
	++i;
	assert(i <= self->ms_c);
	if (i < self->ms_c) {
		size_t j;
		for (j = i; j < self->ms_c; ++j) {
			(*freefun)(self->ms_v[j].mc_start,
			           self->ms_v[j].mc_size,
			           flags);
		}
		if (maybe_hinted) {
			krealloc_in_place_nx(self->ms_v,
			                     i * sizeof(struct mchunk),
			                     flags & ~GFP_CALLOC);
		} else {
			struct mchunk *vec;
			vec = (struct mchunk *)krealloc_nx(self->ms_v,
			                                   i *
			                                   sizeof(struct mchunk),
			                                   flags);
			if likely(vec != NULL)
				self->ms_v = vec;
		}
		self->ms_c = i;
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mchunkvec_truncate_leading)(struct mchunkvec *__restrict self,
                                          physpagecnt_t remove_pages,
                                          freefun_t freefun, gfp_t flags) {
	struct mchunk *vec;
	for (;;) {
		physpagecnt_t count;
		assert(self->ms_c != 0);
		count = self->ms_v[0].mc_size;
		if (count > remove_pages)
			break;
		/* Drop the first chunk. */
		(*freefun)(self->ms_v[0].mc_start, count, flags);
		--self->ms_c;
		memmovedown(&self->ms_v[0], &self->ms_v[1],
		            self->ms_c, sizeof(struct mchunk));
		remove_pages -= count;
	}
	if (remove_pages != 0) {
		/* Truncate leading pages from the first chunk. */
		(*freefun)(self->ms_v[0].mc_start, remove_pages, flags);
		self->ms_v[0].mc_start += remove_pages;
		self->ms_v[0].mc_size -= remove_pages;
	}

	/* Try to free unused memory. */
	vec = (struct mchunk *)krealloc_nx(self->ms_v,
	                                   self->ms_c *
	                                   sizeof(struct mchunk),
	                                   flags);
	if likely(vec != NULL)
		self->ms_v = vec;
}

PRIVATE NOBLOCK void
NOTHROW(FCALL unmap_and_unprepare_and_sync_memory)(void *addr, size_t num_bytes) {
	/* Unmap the affected address range & sync in every mman. */
	pagedir_unmap(addr, num_bytes);
	mman_supersync(addr, num_bytes);
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	pagedir_unprepare(addr, num_bytes);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

#if !defined(NDEBUG) && !defined(CONFIG_NO_SMP)
	/* This check right here only  serves to turn fully undefined  behavior
	 * when another CPU is currently  initializing a page which we've  just
	 * unmapped (which would indicate an error elsewhere within the kernel)
	 * into something that's a bit easier to narrow down:
	 * Instead of (possibly) failing anywhere within the hinted-page-mapping
	 * function,  fail  with  a  normal  #PF  upon  access  to  bad  memory. */
	mman_kernel_hintinit_inuse_waitfor();
#endif /* !NDEBUG && !CONFIG_NO_SMP */
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL movedown_bits)(mpart_blkst_word_t *dst_bitset,
                             mpart_blkst_word_t const *src_bitset,
                             size_t dst_index, size_t src_index,
                             size_t num_bits) {
#define BITSET_INDEX(index) ((index) / BITSOF(mpart_blkst_word_t))
#define BITSET_SHIFT(index) ((index) % BITSOF(mpart_blkst_word_t))
#define GETBIT(index)       ((src_bitset[BITSET_INDEX(index)] >> BITSET_SHIFT(index)) & 1)
#define SETBIT_OFF(index)   ((dst_bitset[BITSET_INDEX(index)] &= ~((mpart_blkst_word_t)1 << BITSET_SHIFT(index))))
#define SETBIT_ON(index)    ((dst_bitset[BITSET_INDEX(index)] |= ((mpart_blkst_word_t)1 << BITSET_SHIFT(index))))
	while (num_bits) {
		--num_bits;
		if (GETBIT(src_index)) {
			SETBIT_ON(dst_index);
		} else {
			SETBIT_OFF(dst_index);
		}
		++dst_index;
		++src_index;
	}
#undef SETBIT_ON
#undef SETBIT_OFF
#undef GETBIT
#undef BITSET_SHIFT
#undef BITSET_INDEX
}




/* Trim off the trailing data from the given mem-part to make
 * its   effective   new  size   be  equal   to  `part_size'.
 * The  caller must  ensure all  the proper  locking, and the
 * non-shared-ness of the given mem-part. */
PRIVATE NOBLOCK NONNULL((1, 3)) void
NOTHROW(FCALL mpart_truncate_trailing)(struct mpart *__restrict self,
                                       size_t part_size,
                                       freefun_t freefun, gfp_t flags,
                                       uintptr_t node_flags) {
	physpagecnt_t part_pages;
	TRACE_KRAM(KERN_TRACE "[mm] mpart_truncate_trailing(%p, %" PRIuSIZ ", %p, %#x, %#" PRIuPTR ")\n",
	           self, part_size, freefun, flags, node_flags);
	assert(self->mp_maxaddr > self->mp_minaddr + part_size - 1);
	self->mp_maxaddr = self->mp_minaddr + part_size - 1;
	if (!(self->mp_flags & MPART_F_BLKST_INL) && self->mp_blkst_ptr != NULL) {
		size_t word_count, block_count;
		block_count = part_size >> self->mp_file->mf_blockshift;
		word_count  = CEILDIV(block_count, MPART_BLKST_BLOCKS_PER_WORD);
		if (node_flags & MNODE_F_MHINT) {
			krealloc_in_place_nx(self->mp_blkst_ptr,
			                     word_count * sizeof(mpart_blkst_word_t),
			                     flags & ~GFP_CALLOC);
		} else {
			mpart_blkst_word_t *bitset;
			bitset = (mpart_blkst_word_t *)krealloc_nx(self->mp_blkst_ptr,
			                                           word_count *
			                                           sizeof(mpart_blkst_word_t),
			                                           flags);
			if likely(bitset != NULL)
				self->mp_blkst_ptr = bitset;
		}
	}
	part_pages = (physpagecnt_t)(part_size >> PAGESHIFT);
	/* Free unused memory from the part backing data store. */
	switch (self->mp_state) {

	case MPART_ST_SWP:
	case MPART_ST_MEM:
		assert(self->mp_mem.mc_size > part_pages);
		(*freefun)(self->mp_mem.mc_start + part_pages,
		           self->mp_mem.mc_size - part_pages,
		           flags);
		self->mp_mem.mc_size = part_pages;
		break;

	case MPART_ST_SWP_SC:
	case MPART_ST_MEM_SC:
		mchunkvec_truncate(&self->mp_mem_sc, part_pages, freefun, flags,
		                   (node_flags & MNODE_F_MHINT) != 0);
		break;

	default:
		break;
	}
}

/* Trim off the leading `remove_size' bytes from the given mem-part.
 * The  caller  must  ensure  all   the  proper  locking,  and   the
 * non-shared-ness of the given mem-part. */
PRIVATE NOBLOCK NONNULL((1, 3)) void
NOTHROW(FCALL mpart_truncate_leading)(struct mpart *__restrict self,
                                      size_t remove_size,
                                      freefun_t freefun, gfp_t flags) {
	size_t remove_blocks;
	physpagecnt_t remove_pages;
	TRACE_KRAM(KERN_TRACE "[mm] mpart_truncate_leading(%p, %iu, %p, %#x)\n",
	           self, remove_size, freefun, flags);
	assert(remove_size != 0);
	assert(mpart_getsize(self) > remove_size);
	remove_pages  = remove_size >> PAGESHIFT;
	remove_blocks = remove_size >> self->mp_file->mf_blockshift;
	COMPILER_WRITE_BARRIER();
	self->mp_maxaddr -= remove_size;
	if (self->mp_flags & MPART_F_BLKST_INL) {
		self->mp_blkst_inl >>= remove_blocks * MPART_BLOCK_STBITS;
	} else if (self->mp_blkst_ptr != NULL) {
		mpart_blkst_word_t *bitset;
		size_t word_count, keep_blocks;
		keep_blocks = mpart_getblockcount(self, self->mp_file);
		movedown_bits(self->mp_blkst_ptr, self->mp_blkst_ptr,
		              0, remove_blocks * MPART_BLOCK_STBITS,
		              keep_blocks * MPART_BLOCK_STBITS);
		word_count = CEILDIV(keep_blocks, MPART_BLKST_BLOCKS_PER_WORD);
		assert(word_count >= 0);
		if (word_count == 1) {
			/* Switch over to using an in-line bitset. */
			bitset = self->mp_blkst_ptr;
			self->mp_blkst_inl = bitset[0];
			self->mp_flags |= MPART_F_BLKST_INL;
			kfree(bitset);
		} else {
			/* Try to release unused memory. */
			bitset = (mpart_blkst_word_t *)krealloc_nx(self->mp_blkst_ptr,
			                                           word_count *
			                                           sizeof(mpart_blkst_word_t),
			                                           flags);
			if likely(bitset != NULL)
				self->mp_blkst_ptr = bitset;
		}
	}

	/* Free unused memory from the part backing data store. */
	switch (self->mp_state) {

	case MPART_ST_SWP:
	case MPART_ST_MEM:
		assert(self->mp_mem.mc_size > remove_pages);
		(*freefun)(self->mp_mem.mc_start, remove_pages, flags);
		self->mp_mem.mc_start += remove_pages;
		self->mp_mem.mc_size -= remove_pages;
		break;

	case MPART_ST_SWP_SC:
	case MPART_ST_MEM_SC:
		mchunkvec_truncate_leading(&self->mp_mem_sc, remove_pages,
		                           freefun, flags);
		break;

	default:
		break;
	}
}



/* Free all pages within the given address range [lo,hi)-style */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mchunkvec_free_subrange)(struct mchunk *__restrict vec, freefun_t freefun, gfp_t flags,
                                       size_t lo_split_chunk_index, physpagecnt_t lo_split_chunk_offset,
                                       size_t hi_split_chunk_index, physpagecnt_t hi_split_chunk_offset) {
	size_t i;
	assert(lo_split_chunk_index <= hi_split_chunk_index);
	if (lo_split_chunk_index == hi_split_chunk_index) {
		assert(lo_split_chunk_offset < hi_split_chunk_offset);
		/* Special case: the entire unmap-area is located within the last chunk. */
		(*freefun)(vec[lo_split_chunk_index].mc_start + lo_split_chunk_offset,
		           hi_split_chunk_offset - lo_split_chunk_offset, flags);
	} else {
		/* Free the tail after the last chunk of the first part. */
		(*freefun)(vec[lo_split_chunk_index].mc_start + lo_split_chunk_offset,
		           vec[lo_split_chunk_index].mc_size - lo_split_chunk_offset,
		           flags);

		/* Free all whole chunks being unmapped. */
		for (i = lo_split_chunk_index + 1; i < hi_split_chunk_index; ++i)
			(*freefun)(vec[i].mc_start, vec[i].mc_size, flags);

		/* Free leading data before `hi_split_chunk_offset'. */
		(*freefun)(vec[hi_split_chunk_index].mc_start,
		           hi_split_chunk_offset, flags);
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL try_truncate_mchunk_vector)(struct mchunk **__restrict p_vec,
                                          size_t new_count, gfp_t flags) {
	struct mchunk *newvec;
	newvec = (struct mchunk *)krealloc_nx(*p_vec,
	                                      new_count *
	                                      sizeof(struct mchunk),
	                                      flags);
	if likely(newvec)
		*p_vec = newvec;
}


#ifndef NDEBUG
/* Return the total # of bytes mapped by the given chunk-vec. */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW(FCALL mpart_getramsize)(struct mpart const *__restrict self) {
	size_t result;
	if (self->mp_state == MPART_ST_MEM) {
		result = self->mp_mem.mc_size;
	} else {
		size_t i;
		result = 0;
		for (i = 0; i < self->mp_mem_sc.ms_c; ++i)
			result += self->mp_mem_sc.ms_v[i].mc_size;
	}
	return result * PAGESIZE;
}
#endif /* !NDEBUG */


/* (try to)  unmap the  given  sub-range of  virtual  (kernel)
 * memory that is mapped by `node', which is backed by `part'.
 *
 * This function is called while holding a lock to both `part',
 * as well as the kernel mman.
 *
 * @return: true:  Unmap successful.
 * @return: false: Insufficient memory to do the unmap right now (try again later) */
PRIVATE NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL mman_unmap_mpart_subregion)(struct mnode *__restrict node,
                                          struct mpart *__restrict part,
                                          byte_t *unmap_minaddr,
                                          byte_t *unmap_maxaddr,
                                          gfp_t flags) {
	struct mnode *hinode, *lonode;
	struct mpart *hipart, *lopart;
	size_t losize, hisize, hioffset;
	size_t unmap_size;
	freefun_t freefun;
	TRACE_KRAM(KERN_TRACE "[mm] mman_unmap_mpart_subregion(%p(%p-%p),%p,%p,%p,%#x)\n",
	           node, mnode_getminaddr(node), mnode_getmaxaddr(node), part,
	           unmap_minaddr, unmap_maxaddr, flags);
	assert(mman_lock_acquired(&mman_kernel));
	assert(mpart_lock_acquired(part));
	assert(!(part->mp_flags & MPART_F_NOSPLIT));
	assert(!(node->mn_flags & MNODE_F_NOSPLIT));
	assert(unmap_minaddr >= node->mn_minaddr);
	assert(unmap_maxaddr <= node->mn_maxaddr);
	assertf(unmap_minaddr != node->mn_minaddr || unmap_maxaddr != node->mn_maxaddr,
	        "This case should be handled by the caller");

	/* TODO: None of the following should be a requirement!
	 *       However, right now the below codes assumes all of this stuff.
	 * The  only solution here is having a proper mpart-split function which
	 * we can use to do all of the necessary unsharing, etc... when deleting
	 * a kernel ram sub-region that was backed by a part that's also  mapped
	 * somewhere else... */
	assert(mpart_isanon(part));
	assert(LIST_FIRST(mpart_getnodlst_from_mnodeflags(part, node->mn_flags)) == node);
	assert(LIST_NEXT(node, mn_link) == NULL);

	/* Even though it's not required, mem-nodes within the kernel mman are allowed
	 * to  be linked into the writable list. When they are, we have to remove them
	 * from  said list if we intend to unmap  them. For this purpose we don't have
	 * to  re-add the node when `mman_mappings_insert()' is called, but to prevent
	 * memory corruption, we do have to remove it and prevent bogus pointers  from
	 * appearing  inside the  kernel mman's  writable list  (which could otherwise
	 * result in memory corruption). */
	if unlikely(LIST_ISBOUND(node, mn_writable))
		LIST_UNBIND(node, mn_writable);

	unmap_size = (size_t)(unmap_maxaddr - unmap_minaddr) + 1;
	freefun    = mpart_getfreefun(part);

	/* Set-up malloc-flags for all of the (potential) calls below. */
	flags = GFP_LOCKED | GFP_PREFLT | GFP_ATOMIC | (flags & ~GFP_CALLOC);

	/* Check for simple case: Truncate the node/part at the back. */
	if (unmap_maxaddr == node->mn_maxaddr) {
		size_t part_size;

		/* Truncate at the back. */
		mman_mappings_removenode(&mman_kernel, node);

		/* Unmap the affected address range & sync in every mman. */
		unmap_and_unprepare_and_sync_memory(unmap_minaddr, unmap_size);

		COMPILER_WRITE_BARRIER();
		node->mn_maxaddr = unmap_minaddr - 1;
		part_size        = node->mn_partoff + (size_t)(unmap_minaddr - node->mn_minaddr);
		mpart_truncate_trailing(part, part_size, freefun, flags, node->mn_flags);
		COMPILER_WRITE_BARRIER();

		/* Re-insert the (now truncated) node into the kernel mman. */
		mman_mappings_insert(&mman_kernel, node);
		return true;
	}

	/* Either  truncate a node at the front, or cut out a chunk in the middle.
	 * In  either case, we have to make sure  that (in case of a hinted node),
	 * all  pages above the  to-be unmapped area  have been fully initialized,
	 * thus ensuring that no other CPU (or thread) might possibly try to  load
	 * pages from that upper area when we need to change its backing pointers. */
	if (node->mn_flags & MNODE_F_MHINT) {
		byte_t *tail_minaddr, *tail_endaddr;
		tail_minaddr = unmap_maxaddr + 1;
		tail_endaddr = (byte_t *)mnode_getendaddr(node);

#ifdef CONFIG_DEBUG_HEAP
		if (node->mn_part->mp_file == &mfile_dbgheap) {
			pflag_t was;
			/* Super-ugly, hacky work-around because the heap system can't
			 * be made compatible  with lockops without  a full  re-write.
			 *
			 * s.a.: `heap_unmap_kram()' */
			heap_validate_all();
			was = PREEMPTION_PUSHOFF();
			ATOMIC_OR(THIS_TASK->t_flags, _TASK_FDBGHEAPDMEM);
			do {
				__asm__ __volatile__("" : : "r" (*tail_minaddr));
				tail_minaddr += PAGESIZE;
			} while (tail_minaddr < tail_endaddr);
			PREEMPTION_POP(was);
			ATOMIC_AND(THIS_TASK->t_flags, ~_TASK_FDBGHEAPDMEM);
			heap_validate_all();
		} else
#endif /* CONFIG_DEBUG_HEAP */
		{
			/* We  keep the lazy initialization of hinted nodes simple, and let
			 * the #PF handler to most of the work. As such, all we really have
			 * to  do is  ensure that every  page from the  tail-range has been
			 * accessed at least once. */
			do {
				__asm__ __volatile__("" : : "r" (*tail_minaddr));
				tail_minaddr += PAGESIZE;
			} while (tail_minaddr < tail_endaddr);
		}

		/* Make sure that any other CPU is still initializing hinted pages,
		 * which may  overlap with  the address  range we've  just  loaded. */
		mman_kernel_hintinit_inuse_waitfor();
	}

	if unlikely(node->mn_partoff != 0) {
		/* Truncate the leading address range that was never even mapped...
		 * All of the  below code assumes  that it is  operating on a  zero
		 * offset mnode->mpart mapping. */
		mpart_truncate_leading(part, node->mn_partoff, freefun, flags);
		node->mn_partoff = 0;
	}

	{
		size_t mpart_size;
		mpart_size = mpart_getsize(part);
		assert(mpart_size >= mnode_getsize(node));
		if unlikely(mpart_size > mnode_getsize(node)) {
			/* Truncate the trailing address range  that was never even  mapped.
			 * All of the below code assumes that the original part isn't larger
			 * than the associated node. */
			mpart_truncate_trailing(part, mpart_size, freefun, flags, 0);
		}
	}

	/* Ensure that the node's and part's sizes match up exactly. */
	assert(node->mn_partoff == 0);
	assert(mpart_getsize(part) == mnode_getsize(node));

	/* Check for slightly more complicated case: Truncate a node at the front. */
	if (unmap_minaddr == node->mn_minaddr) {
		size_t remove_size;

		/* We can truncate the node at the front. */
		unmap_and_unprepare_and_sync_memory(unmap_minaddr, unmap_size);
		remove_size = (size_t)(unmap_maxaddr - unmap_minaddr) + 1;
		mman_mappings_removenode(&mman_kernel, node);
		mpart_truncate_leading(part, remove_size, freefun, flags);

		/* Trim the node. */
		node->mn_minaddr += remove_size;
		mman_mappings_insert(&mman_kernel, node);
		return true;
	}

	/* Cut-out a hole in the middle.
	 *
	 * Note that for this purpose, we may even use `mcoreheap_alloc_locked_nx()'
	 * in order to dynamically allocate the required additional data structures! */
	TRACE_KRAM(KERN_TRACE "[mm] mman_unmap_mpart_subregion(): Cut a hole %p-%p into %p-%p\n",
	           unmap_minaddr, unmap_maxaddr, mnode_getminaddr(node), mnode_getmaxaddr(node));

	lonode = node;
	lopart = part;

	/* Allocate new elements for the hi-node and hi-part. */
	hinode = (struct mnode *)kmalloc_nx(sizeof(struct mnode), flags);
	if (hinode) {
		hinode->mn_flags = MNODE_F_NORMAL;
	} else {
		union mcorepart *cp;
		cp = mcoreheap_alloc_locked_nx();
		if unlikely(cp == NULL)
			goto fail;
		hinode           = &cp->mcp_node;
		hinode->mn_flags = MNODE_F_NORMAL | MNODE_F_COREPART;
	}
	hipart = (struct mpart *)kmalloc_nx(sizeof(struct mpart), flags);
	if (hipart) {
		hipart->mp_flags = MPART_F_NORMAL;
	} else {
		union mcorepart *cp;
		cp = mcoreheap_alloc_locked_nx();
		if unlikely(cp == NULL)
			goto fail_hinode;
		hipart           = &cp->mcp_part;
		hipart->mp_flags = MPART_F_NORMAL | MPART_F_COREPART;
	}
	hipart->mp_xflags = MPART_XF_NORMAL;

	/* Figure out the eventual sizes of the lo- and hi-parts */
	losize   = unmap_minaddr - node->mn_minaddr;
	hisize   = node->mn_maxaddr - unmap_maxaddr;
	hioffset = (size_t)((unmap_maxaddr + 1) - node->mn_minaddr);
	assert(losize != 0);
	assert(hisize != 0);
	assert(IS_ALIGNED(losize, PAGESIZE));
	assert(IS_ALIGNED(hisize, PAGESIZE));

#ifndef NDEBUG
	assertf(!MPART_ST_INMEM(part->mp_state) ||
	        mpart_getramsize(part) == mpart_getsize(part),
	        "mpart_getramsize(part) = %#" PRIxSIZ "\n"
	        "mpart_getsize(part)    = %#" PRIxSIZ,
	        mpart_getramsize(part), mpart_getsize(part));
#endif /* !NDEBUG */

	/* Check if we also need to allocate an additional
	 * block-status  bitset  for  use  with   `hipart' */
	hipart->mp_blkst_ptr = NULL;
	if (!(lopart->mp_flags & MPART_F_BLKST_INL) && lopart->mp_blkst_ptr != NULL) {
		size_t bitset_bytes_per_word;
		bitset_bytes_per_word = MPART_BLKST_BLOCKS_PER_WORD << part->mp_file->mf_blockshift;
		if (losize > bitset_bytes_per_word && hisize > bitset_bytes_per_word) {
			mpart_blkst_word_t *bitset;
			size_t new_bitset_bytes, new_bitset_blocks, new_bitset_words;
			new_bitset_bytes  = MIN(losize, hisize);
			new_bitset_blocks = new_bitset_bytes >> part->mp_file->mf_blockshift;
			new_bitset_words  = CEILDIV(new_bitset_blocks, MPART_BLKST_BLOCKS_PER_WORD);
			assert(new_bitset_words >= 2);
			bitset = (mpart_blkst_word_t *)kmalloc_nx(new_bitset_words *
			                                          sizeof(mpart_blkst_word_t),
			                                          flags);
			if unlikely(!bitset)
				goto fail_hinode_hipart;
			hipart->mp_blkst_ptr = bitset;
		} else {
			/* We can just re-use the block-status bitset from `lopart',
			 * and have the smaller part make use of `MPART_F_BLKST_INL' */
		}
	}

	/* Allocate dynamic memory that is necessary for splitting the backing storage. */
	hipart->mp_state = lopart->mp_state;
	switch (lopart->mp_state) {

	case MPART_ST_SWP_SC:
	case MPART_ST_MEM_SC: {
		size_t lo_split_chunk_index, hi_split_chunk_index;
		physpagecnt_t lo_split_chunk_offset, hi_split_chunk_offset;
		size_t lo_chunks, hi_chunks;
		struct mchunkvec vec;

		/* We may have to allocate a new dynamic mem/swap  vector.
		 * First of all: Figure out where exactly the split  needs
		 * to happen, in terms of CHUNK_INDEX and CHUNK_OFFSET for
		 * both where the lo-part will end, and where the  hi-part
		 * will start at. */
		vec = lopart->mp_mem_sc;
		lo_split_chunk_offset = losize >> PAGESHIFT;
		for (lo_split_chunk_index = 0;;) {
			physpagecnt_t count;
			assert(lo_split_chunk_index < vec.ms_c);
			count = vec.ms_v[lo_split_chunk_index].mc_size;
			if (count > lo_split_chunk_offset)
				break;
			lo_split_chunk_offset -= count;
			++lo_split_chunk_index;
		}
		hi_split_chunk_index  = lo_split_chunk_index;
		hi_split_chunk_offset = lo_split_chunk_offset + ((hioffset - losize) >> PAGESHIFT);
		for (;;) {
			physpagecnt_t count;
			assert(hi_split_chunk_index < vec.ms_c);
			count = vec.ms_v[hi_split_chunk_index].mc_size;
			if (count > hi_split_chunk_offset)
				break;
			hi_split_chunk_offset -= count;
			++hi_split_chunk_index;
		}

		/* We now have to adjust the backing storage, such that:
		 * >> lopart->mp_mem_sc = { [0...<lo_split_chunk_index:lo_split_chunk_offset>) }
		 * >> hipart->mp_mem_sc = { [<hi_split_chunk_index:hi_split_chunk_offset>...n) }
		 * For  this, start out by figuring out exactly how many chunks we'll be needing
		 * for the lo- and hi-part's chunk-vectors. */
		lo_chunks = lo_split_chunk_index;
		if (lo_split_chunk_offset != 0)
			++lo_chunks;
		hi_chunks = vec.ms_c - hi_split_chunk_index;
		assert(lo_chunks >= 1);
		assert(hi_chunks >= 1);

		/* Handle the simple cases where one of the 2 parts can
		 * be  implemented without the  need of a chunk-vector. */
		if (lo_chunks == 1 && hi_chunks == 1) {
			size_t lo_size;

			/* Both parts only need a single chunk. */
			assert((lo_split_chunk_index == 0 && lo_split_chunk_offset != 0) ||
			       (lo_split_chunk_index == 1 && lo_split_chunk_offset == 0));
			assert(hi_split_chunk_index == vec.ms_c - 1);
			lo_size = lo_split_chunk_offset;
			if (lo_split_chunk_index != 0)
				lo_size = vec.ms_v[0].mc_size;
			lopart->mp_state = lopart->mp_state == MPART_ST_MEM_SC ? MPART_ST_MEM : MPART_ST_SWP;
			hipart->mp_state = lopart->mp_state;
			lopart->mp_mem.mc_start = vec.ms_v[0].mc_start;
			lopart->mp_mem.mc_size  = lo_size;
			hipart->mp_mem.mc_start = vec.ms_v[hi_split_chunk_index].mc_start + hi_split_chunk_offset;
			hipart->mp_mem.mc_size  = vec.ms_v[hi_split_chunk_index].mc_size - hi_split_chunk_offset;
			/* === Point of no return */

			/* Unmap the requested address range. */
			unmap_and_unprepare_and_sync_memory(unmap_minaddr, unmap_size);

			/* Free physical memory. */
			mchunkvec_free_subrange(vec.ms_v, freefun, flags,
			                        lo_split_chunk_index, lo_split_chunk_offset,
			                        hi_split_chunk_index, hi_split_chunk_offset);
			kfree(vec.ms_v);
		} else if (lo_chunks == 1) {
			size_t lo_size;

			/* `hipart' must use a vector, while `lopart' uses a single chunk. */
			assert(hipart->mp_state == lopart->mp_state);
			assert((lo_split_chunk_index == 0 && lo_split_chunk_offset != 0) ||
			       (lo_split_chunk_index == 1 && lo_split_chunk_offset == 0));
			lo_size = lo_split_chunk_offset;
			if (lo_split_chunk_index != 0)
				lo_size = vec.ms_v[0].mc_size;
			lopart->mp_state = lopart->mp_state == MPART_ST_MEM_SC ? MPART_ST_MEM : MPART_ST_SWP;
			lopart->mp_mem.mc_start = vec.ms_v[0].mc_start;
			lopart->mp_mem.mc_size  = lo_size;
			/* === Point of no return */

			/* Unmap the requested address range. */
			unmap_and_unprepare_and_sync_memory(unmap_minaddr, unmap_size);

			/* Free physical memory. */
			mchunkvec_free_subrange(vec.ms_v, freefun, flags,
			                        lo_split_chunk_index, lo_split_chunk_offset,
			                        hi_split_chunk_index, hi_split_chunk_offset);

			/* Shift down the still-remaining hi-part. */
			vec.ms_c -= hi_split_chunk_index;
			memmovedown(&vec.ms_v[0],
			            &vec.ms_v[hi_split_chunk_index],
			            vec.ms_c, sizeof(struct mchunk));
			vec.ms_v[0].mc_start += hi_split_chunk_offset;
			vec.ms_v[0].mc_size -= hi_split_chunk_offset;

			/* Try to free unused memory. */
			try_truncate_mchunk_vector(&vec.ms_v, vec.ms_c, flags);

			/* Now just set `vec' as the vector used by `hipart' */
			hipart->mp_mem_sc = vec;
		} else if (hi_chunks == 1) {
			/* `lopart' must stay as a vector, and `hipart' becomes a single chunk. */
			assert(lo_chunks > 1);
			assert(hi_split_chunk_index == vec.ms_c - 1);
			hipart->mp_state = lopart->mp_state == MPART_ST_MEM_SC ? MPART_ST_MEM : MPART_ST_SWP;
			hipart->mp_mem = vec.ms_v[hi_split_chunk_index];
			hipart->mp_mem.mc_start += hi_split_chunk_offset;
			hipart->mp_mem.mc_size -= hi_split_chunk_offset;
			/* === Point of no return */

			/* Unmap the requested address range. */
			unmap_and_unprepare_and_sync_memory(unmap_minaddr, unmap_size);

			/* Now to free all of the backing physical memory to-be removed. */
			mchunkvec_free_subrange(vec.ms_v, freefun, flags,
			                        lo_split_chunk_index, lo_split_chunk_offset,
			                        hi_split_chunk_index, hi_split_chunk_offset);

			/* Update the vector information for `lopart' */
			vec.ms_v[lo_split_chunk_index].mc_size = lo_split_chunk_offset;
			vec.ms_c = lo_chunks;

			/* Try to free unused memory. */
			try_truncate_mchunk_vector(&vec.ms_v, vec.ms_c, flags);

			/* Write-back the chunk-vector. */
			lopart->mp_mem_sc = vec;
		} else {
			/* `lopart' must stay as a vector, and an additional
			 * vector needs to be allocated for use by `hipart'. */
			struct mchunk *newvec;
			assert(lo_chunks >= 2);
			assert(hi_chunks >= 2);

			/* Allocate a vector for the smaller of the 2 requirements. */
			newvec = (struct mchunk *)kmalloc_nx(MIN(lo_chunks, hi_chunks) *
			                                     sizeof(struct mchunk),
			                                     flags);
			if unlikely(!newvec)
				goto fail_hinode_hipart_bitset;

			/* === Point of no return */
			unmap_and_unprepare_and_sync_memory(unmap_minaddr, unmap_size);

			/* Free accessed memory. */
			mchunkvec_free_subrange(vec.ms_v, freefun, flags,
			                        lo_split_chunk_index, lo_split_chunk_offset,
			                        hi_split_chunk_index, hi_split_chunk_offset);

			if (hi_chunks <= lo_chunks) {
				/* Use `newvec' for `hipart' */
				memcpy(&newvec[0],
				       &vec.ms_v[hi_split_chunk_index],
				       hi_chunks, sizeof(struct mchunk));
				newvec[0].mc_start += hi_split_chunk_offset;
				newvec[0].mc_size -= hi_split_chunk_offset;
				hipart->mp_mem_sc.ms_c = hi_chunks;
				hipart->mp_mem_sc.ms_v = newvec;

				/* Trim the last chunk still apart of the truncated `lopart' */
				vec.ms_v[lo_split_chunk_index].mc_size = lo_split_chunk_offset;

				/* Write-back the truncated vector into `lopart' */
				try_truncate_mchunk_vector(&lopart->mp_mem_sc.ms_v, lo_chunks, flags);
				lopart->mp_mem_sc.ms_c = lo_chunks;
			} else {
				/* Use `newvec' for `lopart', and re-purpose the
				 * old  vector from `lopart' for use in `hipart' */
				memcpy(&newvec[0], &vec.ms_v[0], lo_chunks, sizeof(struct mchunk));
				if (lo_split_chunk_offset != 0) {
					assert(lo_split_chunk_index == lo_chunks - 1);
					newvec[lo_split_chunk_index].mc_size = lo_split_chunk_offset;
				}
				lopart->mp_mem_sc.ms_c = lo_chunks;
				lopart->mp_mem_sc.ms_v = newvec;

				/* Shift-down the chunks for `hipart' */
				vec.ms_c = hi_chunks;
				memmovedown(&vec.ms_v[0],
				            &vec.ms_v[hi_split_chunk_index],
				            vec.ms_c, sizeof(struct mchunk));
				vec.ms_v[0].mc_start += hi_split_chunk_offset;
				vec.ms_v[0].mc_size -= hi_split_chunk_offset;

				/* Write-back the truncated vector into `hipart' */
				try_truncate_mchunk_vector(&vec.ms_v, vec.ms_c, flags);
				hipart->mp_mem_sc = vec;
			}
		}
	}	break;

	case MPART_ST_SWP:
	case MPART_ST_MEM: {
		physpagecnt_t losize_pages;
		physpagecnt_t hioffset_pages;
		losize_pages   = losize >> PAGESHIFT;
		hioffset_pages = hioffset >> PAGESHIFT;
		hipart->mp_mem = lopart->mp_mem;
		hipart->mp_mem.mc_start += hioffset_pages;
		hipart->mp_mem.mc_size -= hioffset_pages;

		/* === Point of no return */
		unmap_and_unprepare_and_sync_memory(unmap_minaddr, unmap_size);
		(*freefun)(lopart->mp_mem.mc_start + losize_pages,
		           hioffset_pages - losize_pages, flags);
		lopart->mp_mem.mc_size = losize_pages;
	}	break;

	default:
		/* === Point of no return */
		unmap_and_unprepare_and_sync_memory(unmap_minaddr, unmap_size);
		break;
	}

#ifndef NDEBUG
	assertf(!MPART_ST_INMEM(lopart->mp_state) ||
	        mpart_getramsize(lopart) == losize,
	        "mpart_getramsize(lopart) = %#" PRIxSIZ "\n"
	        "losize                   = %#" PRIxSIZ,
	        mpart_getramsize(lopart), losize);
	assertf(!MPART_ST_INMEM(hipart->mp_state) ||
	        mpart_getramsize(hipart) == hisize,
	        "mpart_getramsize(hipart) = %#" PRIxSIZ "\n"
	        "hisize                   = %#" PRIxSIZ,
	        mpart_getramsize(hipart), hisize);
#endif /* !NDEBUG */

	/* Remove the old node from the kernel mman. */
	mman_mappings_removenode(&mman_kernel, node);

	if (lopart->mp_flags & MPART_F_BLKST_INL) {
		size_t hioffset_blocks;
		hioffset_blocks      = hioffset >> part->mp_file->mf_blockshift;
		hipart->mp_blkst_inl = lopart->mp_blkst_inl >> (hioffset_blocks * MPART_BLOCK_STBITS);
		hipart->mp_flags |= MPART_F_BLKST_INL;
	} else if (lopart->mp_blkst_ptr != NULL) {
		size_t bitset_bytes_per_word, hioffset_blocks;
		size_t loblocks, hiblocks;
		shift_t blockshift    = part->mp_file->mf_blockshift;
		hioffset_blocks       = hioffset >> blockshift;
		bitset_bytes_per_word = MPART_BLKST_BLOCKS_PER_WORD << blockshift;
		loblocks              = losize >> blockshift;
		hiblocks              = hisize >> blockshift;
		if (losize > bitset_bytes_per_word && hisize > bitset_bytes_per_word) {
			if (losize >= hisize) {
				movedown_bits(hipart->mp_blkst_ptr,
				              lopart->mp_blkst_ptr,
				              0, hioffset_blocks * MPART_BLOCK_STBITS,
				              hiblocks * MPART_BLOCK_STBITS);
			} else {
				/* Must swap bitsets */
				mpart_blkst_word_t *loset, *hiset, *smaller_bitset;
				loset = hipart->mp_blkst_ptr;
				hiset = lopart->mp_blkst_ptr;
				memcpy(loset, hiset,
				       CEILDIV(loblocks, MPART_BLKST_BLOCKS_PER_WORD),
				       sizeof(mpart_blkst_word_t));
				movedown_bits(hiset, hiset, 0,
				              hioffset_blocks * MPART_BLOCK_STBITS,
				              hiblocks * MPART_BLOCK_STBITS);

				/* Try to release unused memory. */
				smaller_bitset = (mpart_blkst_word_t *)krealloc_nx(hiset,
				                                                   CEILDIV(hiblocks, MPART_BLKST_BLOCKS_PER_WORD) *
				                                                   sizeof(mpart_blkst_word_t),
				                                                   flags);
				if likely(smaller_bitset != NULL)
					hiset = smaller_bitset;

				/* Write-back the updated bitsets. */
				lopart->mp_blkst_ptr = loset;
				hipart->mp_blkst_ptr = hiset;
			}
		} else if (hisize > bitset_bytes_per_word) {
			mpart_blkst_word_t *hiset, *smaller_bitset;

			/* Re-use  the bitset from `lopart' in `hipart', and
			 * change `lopart' to make use of the inline bitset. */
			hiset = lopart->mp_blkst_ptr;
			lopart->mp_blkst_inl = hiset[0];
			lopart->mp_flags |= MPART_F_BLKST_INL;
			movedown_bits(hiset, hiset, 0,
			              hioffset_blocks * MPART_BLOCK_STBITS,
			              hiblocks * MPART_BLOCK_STBITS);

			/* Try to release unused memory. */
			smaller_bitset = (mpart_blkst_word_t *)krealloc_nx(hiset,
			                                                   CEILDIV(hiblocks, MPART_BLKST_BLOCKS_PER_WORD) *
			                                                   sizeof(mpart_blkst_word_t),
			                                                   flags);
			if likely(smaller_bitset != NULL)
				hiset = smaller_bitset;
			hipart->mp_blkst_ptr = hiset;
		} else {
			/* (possibly) keep the bitset in lopart, but use the inline-bitset in hipart. */
			mpart_blkst_word_t *loset = lopart->mp_blkst_ptr;
			movedown_bits(&hipart->mp_blkst_inl, loset, 0,
			              hioffset_blocks * MPART_BLOCK_STBITS,
			              hiblocks * MPART_BLOCK_STBITS);
			hipart->mp_flags |= MPART_F_BLKST_INL;
			if (losize <= bitset_bytes_per_word) {
				/* Free the dynamic bitset in lopart, and replace with the inline bitset. */
				lopart->mp_blkst_inl = loset[0];
				lopart->mp_flags |= MPART_F_BLKST_INL;
				kfree(loset);
			}
		}
	}

	/* With all of the complicated stuff out of the way, move on
	 * to initializing the new hinode/hipart pair, as well as to
	 * truncate the old lonode/lopart pair near the top. */
	hinode->mn_minaddr = unmap_maxaddr + 1;
	hinode->mn_maxaddr = lonode->mn_maxaddr;
	lonode->mn_maxaddr = unmap_minaddr - 1;
	hinode->mn_flags  |= lonode->mn_flags & (MNODE_F_PMASK | MNODE_F_SHARED |
	                                         MNODE_F_MPREPARED | MNODE_F_MLOCK);
	hinode->mn_part    = hipart; /* Inherit reference */
	hinode->mn_fspath  = xincref(lonode->mn_fspath);
	hinode->mn_fsname  = xincref(lonode->mn_fsname);
	hinode->mn_mman    = &mman_kernel;
	hinode->mn_partoff = 0;
	/*hinode->mn_link  = ...;*/ /* Initialized below */
	hinode->mn_module = lonode->mn_module;
	if (hinode->mn_module)
		module_inc_nodecount(hinode->mn_module);

	/* Have the hi-node mirror the is-writable attribute of the lo-node */
	LIST_ENTRY_UNBOUND_INIT(&hinode->mn_writable);
	if (LIST_ISBOUND(lonode, mn_writable)) {
		LIST_INSERT_HEAD(&mman_kernel.mm_writable,
		                 hinode, mn_writable);
	}

	/* Initialize the hi-part. */
	hipart->mp_refcnt = 1;
	hipart->mp_flags |= lopart->mp_flags & (MPART_F_MAYBE_BLK_INIT |
	                                        MPART_F_CHANGED | MPART_F_NOFREE |
	                                        MPART_F_MLOCK | MPART_F_MLOCK_FROZEN);
	/*hipart->mp_state = ...;*/ /* Already initialized above */
	hipart->mp_file = incref(lopart->mp_file);
	LIST_INIT(&hipart->mp_copy);
	LIST_INIT(&hipart->mp_share);
	hinode->mn_link.le_next  = NULL;
	hinode->mn_link.le_prev  = &mpart_getnodlst_from_mnodeflags(hipart, lonode->mn_flags)->lh_first;
	*hinode->mn_link.le_prev = hinode;
	SLIST_INIT(&hipart->mp_lockops);
	/*LIST_ENTRY_UNBOUND_INIT(&hipart->mp_allparts);*/ /* Initialized below */
	DBG_memset(&hipart->mp_changed, 0xcc, sizeof(hipart->mp_changed));
	hipart->mp_maxaddr = lopart->mp_maxaddr;
	lopart->mp_maxaddr = lopart->mp_minaddr + (losize - 1);
	hipart->mp_minaddr = hipart->mp_maxaddr - (hisize - 1);
	_mpart_init_asanon(hipart);
	/*hipart->mp_blkst_ptr = ...;*/ /* Initialized above */
	/*hipart->mp_mem       = ...;*/ /* Initialized above */
	hipart->mp_meta = NULL;

	/* Mirror the part-of-global-list status of `lopart' in `hipart' */
	if (LIST_ISBOUND(lopart, mp_allparts)) {
		if (lopart->mp_flags & MPART_F_GLOBAL_REF)
			hipart->mp_refcnt = 2; /* +1 for the global list. */
		mpart_all_list_insert(hipart);
	} else {
	    LIST_ENTRY_UNBOUND_INIT(&hipart->mp_allparts);
		assertf(!(lopart->mp_flags & MPART_F_GLOBAL_REF),
		        "How can you have a global ref, but not be part of the global list?");
	}

	/* Insert the lo- and hi-nodes now that they've been updated
	 * to include the requested gap in-between. */
	mman_mappings_insert(&mman_kernel, lonode);
	mman_mappings_insert(&mman_kernel, hinode);

	if (hipart->mp_flags & MPART_F_CHANGED) {
		/* Must insert into the list of changed parts. */
		struct mfile *file = hipart->mp_file;
		struct mpart *next;
		hipart->mp_refcnt = 2;
		do {
			next = ATOMIC_READ(file->mf_changed.slh_first);
			if unlikely(next == MFILE_PARTS_ANONYMOUS) {
				hipart->mp_refcnt = 1;
				hipart->mp_flags &= ~MPART_F_CHANGED;
				break;
			}
			assertf(file->mf_ops->mo_saveblocks != NULL,
			        "MPART_F_CHANGED+mf_changed!=ANON imply the presence of this operator");
			hipart->mp_changed.sle_next = next;
			COMPILER_WRITE_BARRIER();
		} while (!ATOMIC_CMPXCH_WEAK(file->mf_changed.slh_first,
		                             next, hipart));
	}

	/* And we're done! */
	return true;
fail_hinode_hipart_bitset:
	kfree(hipart->mp_blkst_ptr);
fail_hinode_hipart:
	mpart_free(hipart);
fail_hinode:
	mnode_free(hinode);
fail:
	return false;
}



PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL lockop_kram_cb_post)(Tobpostlockop(mman) *__restrict self,
                                   struct mman *__restrict UNUSED(mm)) {
	struct mman_unmap_kram_job *job;
	job = container_of(self, struct mman_unmap_kram_job, mukj_post_lop_mm);
	(*job->mukj_done)(job);
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(mman) *
NOTHROW(FCALL lockop_kram_cb)(Toblockop(mman) *__restrict self,
                              struct mman *__restrict UNUSED(mm));

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL lockop_kram_async_cb)(Tobpostlockop(mman) *__restrict self,
                                    struct mman *__restrict UNUSED(mm)) {
	struct mman_unmap_kram_job *job;
	job = container_of(self, struct mman_unmap_kram_job, mukj_post_lop_mm);
	job->mukj_lop_mm.olo_func = &lockop_kram_cb;
	SLIST_ATOMIC_INSERT(&mman_kernel_lockops,
	                    &job->mukj_lop_mm,
	                    olo_link);
	/* DONT reap `mman_kernel' at this point! */
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(mman) *
NOTHROW(FCALL lockop_kram_cb)(Toblockop(mman) *__restrict self,
                              struct mman *__restrict UNUSED(mm)) {
	struct mman_unmap_kram_job *job, *res;
	job = container_of(self, struct mman_unmap_kram_job, mukj_lop_mm);
	res = mman_unmap_kram_locked_ex(job, NULL);
	if (res == MMAN_UNMAP_KRAM_LOCKED_EX_DONE) {
		if likely(job->mukj_done != NULL) {
			/* Set-up a post-lock callback to exec the done-callback.
			 * */
			job->mukj_post_lop_mm.oplo_func = &lockop_kram_cb_post;
			return &job->mukj_post_lop_mm;
		}
	} else if (res != MMAN_UNMAP_KRAM_LOCKED_EX_ASYNC) {
		/* Must re-queue as pending for the kernel mman.
		 * This must happen in a post-op so we don't end up in an infinite loop! */
		res->mukj_post_lop_mm.oplo_func = &lockop_kram_async_cb;
		return &res->mukj_post_lop_mm;
	}
	return NULL;
}


PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mpartlockop_kram_cb_post)(Tobpostlockop(mpart) *__restrict self,
                                        struct mpart *__restrict UNUSED(part)) {
	struct mman_unmap_kram_job *job;
	job = container_of(self, struct mman_unmap_kram_job, mukj_post_lop_mp);
	(*job->mukj_done)(job);
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(mpart) *
NOTHROW(FCALL mpartlockop_kram_cb)(Toblockop(mpart) *__restrict self,
                                   struct mpart *__restrict part) {
	struct mman_unmap_kram_job *job, *res;
	job = container_of(self, struct mman_unmap_kram_job, mukj_lop_mp);
	/* Note that at this point, we're not holding a lock to  the
	 * kernel mman, meaning we have to try and acquire it first! */
	if (mman_lock_tryacquire(&mman_kernel)) {
		res = mman_unmap_kram_locked_ex(job, part);
		mman_lock_release(&mman_kernel);
	} else {
		/* Failed to lock the kernel mman. -> Enqueue  the
		 * rest of the task for when it becomes available. */
		res = job;
	}
	if (res == MMAN_UNMAP_KRAM_LOCKED_EX_DONE) {
		if likely(job->mukj_done != NULL) {
			/* Set-up a post-lock callback to exec the done-callback */
			job->mukj_post_lop_mp.oplo_func = &mpartlockop_kram_cb_post;
			return &job->mukj_post_lop_mp;
		}
	} else if (res != MMAN_UNMAP_KRAM_LOCKED_EX_ASYNC) {
		/* Must re-queue as pending for the kernel mman. */
		res->mukj_lop_mm.olo_func = &lockop_kram_cb;
		SLIST_ATOMIC_INSERT(&mman_kernel_lockops,
		                    &res->mukj_lop_mm,
		                    olo_link);
	}
	return NULL;
}


/* Insert `lop' into the lock-operations list of `self',  and
 * return `true', or don't insert it into the list, acquire a
 * lock to `self', and return `false' */
PRIVATE NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL mpart_lockop_insert_or_lock)(struct mpart *__restrict self,
                                           Toblockop(mpart) *__restrict lop) {
	bool did_remove;
	Toblockop_slist(mpart) locklist;
	SLIST_ATOMIC_INSERT(&self->mp_lockops, lop, olo_link);
	if likely(!mpart_lock_tryacquire(self))
		return true;

	/* Welp... We've got the lock... -> Try to remove `lop' once again. */
	locklist.slh_first = SLIST_ATOMIC_CLEAR(&self->mp_lockops);
	did_remove         = true;
	SLIST_TRYREMOVE(&locklist, lop, olo_link, {
		did_remove = false;
	});
	if (locklist.slh_first != NULL) {
		/* Re-queue all removed elements. */
		Toblockop(mpart) *lastop;
		lastop = SLIST_FIRST(&locklist);
		while (SLIST_NEXT(lastop, olo_link))
			lastop = SLIST_NEXT(lastop, olo_link);
		SLIST_ATOMIC_INSERT_R(&self->mp_lockops,
		                      SLIST_FIRST(&locklist),
		                      lastop, olo_link);
	}
	if (!did_remove) {
		/* Lock acquired, but `lop' was already executed.
		 * Act as though we had never acquired the lock in the first place! */
		mpart_lock_release(self);
		return true;
	}

	/* Lock acquired, and `lop' not added to the lock-op list. */
	return false;
}


/* Try to unmap kernel memory while the caller is holding a lock to the kernel mman.
 * NOTE: This function can be used to delete any kind of kernel-space memory  mapping,
 *       but special care must be taken when it comes to read-only, or shared copy-on-
 *       write memory mappings (see the documentation of `struct mman_unmap_kram_job')
 * @param: locked_part: If non-NULL, a part which may be assumed as locked by the caller.
 * @return: MMAN_UNMAP_KRAM_LOCKED_EX_DONE:  Success (you must invoke the done-callback)
 * @return: MMAN_UNMAP_KRAM_LOCKED_EX_ASYNC: Success (memory will  be free'd  asynchronously)
 *                                           In this case, so-long as the job isn't allocated
 *                                           in-line  with the memory being free'd, the given
 *                                           done-callback is responsible to free `job'
 * @return: * : Insufficient memory (re-queue the returned job for later execution) */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) struct mman_unmap_kram_job *
NOTHROW(FCALL mman_unmap_kram_locked_ex)(struct mman_unmap_kram_job *__restrict job,
                                         struct mpart *locked_part) {
	mman_unmap_kram_job_done_t job_done;
	byte_t *job_orgaddr, *job_minaddr, *job_maxaddr;
	gfp_t job_flags;
	job_done    = job->mukj_done;
	job_minaddr = job->mukj_minaddr;
	job_maxaddr = job->mukj_maxaddr;
	job_flags   = job->mukj_flags;
	job_orgaddr = job_minaddr;
	assert(job_maxaddr >= job_minaddr);
	assert(IS_ALIGNED((uintptr_t)job_minaddr, PAGESIZE));
	assert(IS_ALIGNED((uintptr_t)job_maxaddr + 1, PAGESIZE));
	assert(mman_lock_acquired(&mman_kernel));
	if (job_flags & GFP_CALLOC)
		bzero(job, sizeof(*job));
	for (;;) {
		struct mnode *node;
		struct mpart *part;
		byte_t *unmap_minaddr;
		byte_t *unmap_maxaddr;
		size_t unmap_size;

		node = mnode_tree_locate(mman_kernel.mm_mappings, job_minaddr);
		assertf(node != NULL, "Address %p not mapped", job_minaddr);
		assert(mnode_getminaddr(node) <= job_minaddr);
		assert(mnode_getmaxaddr(node) >= job_minaddr);
		if unlikely(node->mn_flags & MNODE_F_KERNPART) {
			kernel_panic("Attempted to unmap kernel part at %p-%p (via unmap-kram %p-%p)",
			             mnode_getminaddr(node), mnode_getmaxaddr(node),
			             job_minaddr, job_maxaddr);
		}
		assert(node->mn_mman == &mman_kernel);
		assert(mnode_iskern(node));
		part = node->mn_part;
		assert(part);
#ifndef NDEBUG
		if (job_minaddr == (byte_t *)job) {
			assert(node->mn_flags & MNODE_F_PREAD);
			assert(node->mn_flags & MNODE_F_PWRITE);
			if (node->mn_flags & MNODE_F_SHARED) {
				assert(LIST_EMPTY(&part->mp_copy));
				assert(LIST_FIRST(&part->mp_share) == node);
			} else {
				assert(LIST_EMPTY(&part->mp_share));
				assert(LIST_FIRST(&part->mp_copy) == node);
			}
			assert(LIST_NEXT(node, mn_link) == NULL);
			assert(mpart_isanon(part));
#ifdef MPART_ST_VIO
			assert(part->mp_state != MPART_ST_VIO);
#endif /* MPART_ST_VIO */
		}
#endif /* !NDEBUG */

		/* In order to unmap a sub-segment of a hinted mem-node, the following must be done:
		 *  - Because hinted mem-nodes cannot be split (only truncated),
		 *    we must first see how many  pages reside on the upper  end
		 *    of the sub-segment to-be unmapped.
		 *  - We  must always chose  the upper end  because we must eventually
		 *    truncate the associated mem-part's `mp_blkst_ptr' vector, though
		 *    we cannot modify its base-pointer, or move around its  elements.
		 *    NOTE: The   same    goes   for    the   `mp_mem_sc.ms_v'    vector.
		 *    This  restriction must  be in  place, since  the page-fault handler
		 *    doesn't acquire any sort of lock before accessing such a component,
		 *    relying  purely  on the  assumption that  the  kernel won't  try to
		 *    unmap  its  own private  memory,  whilst still  using  said memory.
		 *  - We then ensure that all pages above the unmapped segment have been
		 *    initialized in kernel  memory (this is  guarantied to be  NOEXCEPT
		 *    because  hinted  memory in  kernel-space is  always pre-allocated,
		 *    and always  has  initializers  that don't  throw  any  exceptions)
		 *    A type  of initializer  like this  would usually  only  `memset()'
		 *    or `mempat()' new memory for either debugging or `calloc()'
		 *  - Once that is done, we know that everything above the sub-segment
		 *    to-be unmapped has  been allocated, and  consequently no  longer
		 *    represents hinted memory (the page directory contains the actual
		 *    memory mapping, rather than a hint as to how to initialize  it).
		 *    Because of this, we can proceed to replace the upper sub-segment
		 *    with a new  mman node/part  pair, before moving  on to  truncate
		 *    the  original  (and still  hinted) base  node  to end  where the
		 *    unmapped sub-segment ends.
		 *
		 * Before:
		 * /--mpart at 0xc1234567
		 * [HINTEDHINTEDHINTEDHINTEDHINTEDHINTEDHINTEDHINTEDHINTEDHINTEDHINTED]
		 *              |-- Unmap this part ---|
		 *
		 * NOTE:     There would normally be a race condition right here:
		 *           Before we're allowed to truncate the `Before' node, we must still
		 *           ensure that no other CPU is currently inside of the #PF  handler,
		 *           and in the progress of  mapping the same high-region which  we've
		 *           already faulted at that point.  (though since that other CPU  may
		 *           have started its #PF  before we already did  it's job for it,  it
		 *           may still be trying to access `node')
		 * Solution: We  need a global in-use counter `mman_kernel_hintinit_inuse' that
		 *           tracks how  many CPUs  are  currently initializing  HINTED  nodes.
		 *           The counter is incremented before the first access to the actually
		 *           hinted node, and  decremented once  initialization has  completed.
		 *
		 * After:
		 * /--mpart at 0xc1234567              /--mpart at 0xc7654321
		 * [HINTEDHINTED]                      [USABLEUSABLEUSABLEUSABLEUSABLE]
		 *              |-- Unmap this part ---|
		 *
		 * Note that the upper part is entirely new, and no longer represents
		 * hinted memory, while the lower part  still is the same mpart,  but
		 * has been truncated!
		 *
		 * HINTED: Allocated, but initialized memory (initialize on first access)
		 * USABLE: Fully initialized memory
		 */

		/* Figure out the actual bounds which we wish to unmap. */
		unmap_minaddr = job_minaddr;
		unmap_maxaddr = job_maxaddr;
		if (unmap_maxaddr > (byte_t *)mnode_getmaxaddr(node))
			unmap_maxaddr = (byte_t *)mnode_getmaxaddr(node);
		unmap_size = (size_t)(unmap_maxaddr - unmap_minaddr) + 1;

		/* Check for simple case: unmap a node as a whole. */
		if (unmap_minaddr == mnode_getminaddr(node) &&
		    unmap_maxaddr == mnode_getmaxaddr(node)) {
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			/* Make sure that the (accessed) address range has been prepared. */
			if (!(node->mn_flags & MNODE_F_MPREPARED)) {
				if (!pagedir_prepare(unmap_minaddr, unmap_size))
					goto failed;
			} else {
				node->mn_flags &= ~MNODE_F_MPREPARED; /* Prevent double-unprepare! */
			}
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

			/* Make sure the node isn't apart of the kernel mman's writable list!
			 * Said list doesn't need  to be correct in  that it doesn't have  to
			 * contain  all writable  nodes, however we  must still keep  it as a
			 * valid  list, and if  we were to delete  `node' without removing it
			 * first, it could  result in bogus  pointers and memory  corruption. */
			if unlikely(LIST_ISBOUND(node, mn_writable))
				LIST_UNBIND(node, mn_writable);
			mman_mappings_removenode(&mman_kernel, node);
			ATOMIC_OR(node->mn_flags, MNODE_F_UNMAPPED);

			/* Keep track of how many nodes are mapping a particular module. */
			if (node->mn_module)
				module_dec_nodecount(node->mn_module);
			DBG_memset(&node->mn_module, 0xcc, sizeof(node->mn_module));

			/* Unmap the affected address range & sync in every mman. */
			unmap_and_unprepare_and_sync_memory(unmap_minaddr, unmap_size);

			/* Just delete the node as a whole! */
			mnode_destroy(node);
			goto continue_nextpart;
		}

		/* In order to do this unmap, we'll have to split the node.
		 * Check if we're allowed to do this. */
		if unlikely((node->mn_flags & MNODE_F_NOSPLIT) ||
		            (part->mp_flags & MPART_F_NOSPLIT)) {
			/* Not allowed... (keep on re-attempting the unmap in hopes
			 * that `_mman_lockops_reap()' will  join us together  with
			 * another unmap request, which then  allows the node as  a
			 * whole to be unmapped). */
			goto failed;
		}

		/* We'll need to somehow split the part, meaning that we'll be
		 * needing to acquire a lock to said part! */
		if (part != locked_part) {
			if (!mpart_lock_tryacquire(part)) {
				if (job_orgaddr == (byte_t *)job)
					job = (struct mman_unmap_kram_job *)job_minaddr;
				job->mukj_done             = job_done;
				job->mukj_maxaddr          = job_maxaddr;
				job->mukj_flags            = job_flags;
				job->mukj_minaddr          = unmap_minaddr;
				job->mukj_lop_mp.olo_func = &mpartlockop_kram_cb;
				if (mpart_lockop_insert_or_lock(part, &job->mukj_lop_mp))
					return MMAN_UNMAP_KRAM_LOCKED_EX_ASYNC;
				if (job_flags & GFP_CALLOC)
					bzero(job, sizeof(*job));
			}
		}

#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
		/* Make sure that the (accessed) address range has been prepared. */
		if (!(node->mn_flags & MNODE_F_MPREPARED)) {
			if (!pagedir_prepare(unmap_minaddr, unmap_size))
				goto failed;
		}
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

		/* At this point, we've got a lock to the part, so try to unmap it! */
		{
			bool unmap_ok;
			incref(part);
			unmap_ok = mman_unmap_mpart_subregion(node, part,
			                                      unmap_minaddr,
			                                      unmap_maxaddr,
			                                      job_flags | GFP_ATOMIC);
			if (part != locked_part)
				mpart_lock_release(part);
			decref_unlikely(part);
			if (!unmap_ok) {
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
				/* If we've manually prepared the affected address range  above,
				 * then we must still undo this upon failure, so-as not to leave
				 * memory prepared when it shouldn't be. */
				if (!(node->mn_flags & MNODE_F_MPREPARED))
					pagedir_unprepare(unmap_minaddr, unmap_size);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
				goto failed;
			}
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			/* Upon success, `mman_unmap_mpart_subregion()'  will have  already
			 * unmapped+unprepared the affected address range, meaning we don't
			 * have to unprepare it anymore. */
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
		}

		/* Continue after the successfully unmapped address range. */
continue_nextpart:
		job_minaddr = unmap_maxaddr + 1;
		if (job_minaddr > job_maxaddr)
			break;
	}
	if (job_orgaddr == (byte_t *)job)
		return MMAN_UNMAP_KRAM_LOCKED_EX_ASYNC;
	return MMAN_UNMAP_KRAM_LOCKED_EX_DONE;
failed:
	/* Re-construct at a higher address. */
	if (job_orgaddr == (byte_t *)job)
		job = (struct mman_unmap_kram_job *)job_minaddr;
	job->mukj_done    = job_done;
	job->mukj_minaddr = job_minaddr;
	job->mukj_maxaddr = job_maxaddr;
	job->mukj_flags   = job_flags;
	return job;
}





PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL krulist_sorted_insert_byaddr)(struct mman_unmap_kram_job_slist *__restrict self,
                                            struct mman_unmap_kram_job *__restrict op) {
	struct mman_unmap_kram_job **p_next, *next;
	p_next = SLIST_PFIRST(self);
	while ((next = *p_next) != NULL) {
		assert(next != op);
		if (next > op)
			break; /* Insert before this one! */
		p_next = SLIST_PNEXT(next, mukj_link);
	}
	SLIST_P_INSERT_BEFORE(p_next, op, mukj_link);
}



PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL krulist_merge_adjacent)(struct mman_unmap_kram_job_slist *__restrict self) {
	struct mman_unmap_kram_job *iter, *next;
	assert(!SLIST_EMPTY(self));
	iter = SLIST_FIRST(self);
	for (;;) {
		assert(iter->mukj_minaddr == (byte_t *)iter);
		next = SLIST_NEXT(iter, mukj_link);
		if (!next)
			break;
		if (iter->mukj_maxaddr + 1 == (byte_t *)next &&
		    (iter->mukj_done == NULL || next->mukj_done == NULL)) {
			if (next->mukj_done != NULL)
				iter->mukj_done = next->mukj_done;
			/* Merge these together! */
			iter->mukj_link.sle_next = next->mukj_link.sle_next;
			iter->mukj_maxaddr       = next->mukj_maxaddr;
			iter->mukj_flags         = next->mukj_flags;
			if (iter->mukj_flags & GFP_CALLOC)
				bzero(next, sizeof(*next));
			continue;
		}
		/* Continue trying to merge other segments. */
		iter = next;
	}
}


/* Reap lock operations of the given mman. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _mman_lockops_reap)(struct mman *__restrict self) {
	struct mman_unmap_kram_job_slist krlist;
	Toblockop_slist(mman) lops;
	Tobpostlockop_slist(mman) post;
	Toblockop(mman) *iter;
/*again:*/
	if (!mman_lock_tryacquire(self))
		return;
	SLIST_INIT(&post);
again_steal_and_service_lops:
	lops.slh_first = SLIST_ATOMIC_CLEAR(&FORMMAN(self, thismman_lockops));
again_service_lops:
	SLIST_INIT(&krlist);
	iter = SLIST_FIRST(&lops);
	while (iter != NULL) {
		Toblockop(mman) *next;
		Tobpostlockop(mman) *later;
		next = SLIST_NEXT(iter, olo_link);

		/* Special handling for unmap-kram jobs with inline-memory.
		 * For  efficiency,  these  get  merged  with  each  other. */
		if (iter->olo_func == &lockop_kram_cb) {
			struct mman_unmap_kram_job *job;
			job = container_of(iter, struct mman_unmap_kram_job, mukj_lop_mm);
			if (job->mukj_minaddr == (byte_t *)job) {
				/* Insert into the kram-operations list. */
				krulist_sorted_insert_byaddr(&krlist, job);
				goto continue_with_next;
			}
		}

		/* Invoke the lock operation. */
		assert(pagedir_ismapped((void *)iter->olo_func));
		later = (*iter->olo_func)(iter, self);

		/* Enqueue operations for later execution. */
		if (later != NULL) {
			assert(pagedir_ismapped(later));
			SLIST_INSERT(&post, later, oplo_link);
		}
continue_with_next:
		iter = next;
	}

	/* At this point, all remaining elements in `krlist' are requests
	 * for unmapping kernel  RAM, which have  already been sorted  by
	 * their base address. */
	if (!SLIST_EMPTY(&krlist)) {

		/* Merge adjacent krlist operations */
		krulist_merge_adjacent(&krlist);

		/* Invoke unmap-kernel-ram lops */
		do {
			struct mman_unmap_kram_job *job;
			Tobpostlockop(mman) *later;
			job = SLIST_FIRST(&krlist);
			SLIST_REMOVE_HEAD(&krlist, mukj_link);
			later = lockop_kram_cb(&job->mukj_lop_mm, self);
			if (later != NULL) {
				assert(pagedir_ismapped(later));
				SLIST_INSERT(&post, later, oplo_link);
			}
		} while (!SLIST_EMPTY(&krlist));
	}

	_mman_lock_release(self);

	/* Check for more operations. */
	lops.slh_first = SLIST_ATOMIC_CLEAR(&FORMMAN(self, thismman_lockops));
	if unlikely(!SLIST_EMPTY(&lops)) {
		if likely(mman_lock_tryacquire(self))
			goto again_service_lops;
		/* re-queue all stolen lops. */
		iter = SLIST_FIRST(&lops);
		while (SLIST_NEXT(iter, olo_link))
			iter = SLIST_NEXT(iter, olo_link);
		SLIST_ATOMIC_INSERT_R(&FORMMAN(self, thismman_lockops),
		                      SLIST_FIRST(&lops), iter, olo_link);
		if unlikely(mman_lock_tryacquire(self))
			goto again_steal_and_service_lops;
	}

	/* Run all enqueued post-operations. */
	while (!SLIST_EMPTY(&post)) {
		Tobpostlockop(mman) *op;
		op = SLIST_FIRST(&post);
		SLIST_REMOVE_HEAD(&post, oplo_link);
		assert(pagedir_ismapped((void *)op->oplo_func));
		(*op->oplo_func)(op, self);

		/* To ease debugging, keep `op' visible during unwinding,
		 * even  when  `op->oplo_func'   is  a  faulty   pointer. */
#ifndef NDEBUG
		__asm__ __volatile__("" : : "X" (op));
#endif /* !NDEBUG */
	}
}




/* Without blocking, unmap a given region of kernel RAM.
 * NOTE: The  caller must ensure that the given the address range can
 *       be  written to without any chance of that write blocking, or
 *       resulting in an exception. (i.e. don't use this one to unmap
 *       file mappings or the like...)
 *       If your intend is to unmap mappings that don't fulfill this
 *       requirement, the you should read the description of `struct
 *       mman_unmap_kram_job' and use `mman_unmap_kram_locked_ex()'
 * @param: flags:   Set of `0 | GFP_CALLOC'. When `GFP_CALLOC' is given, allows
 *                  the memory  management system  to assume  that the  backing
 *                  physical  memory  is zero-initialized.  If you're  not sure
 *                  if this is  the case,  better pass  `0'. If  you lie  here,
 *                  calloc() might arbitrarily break... */
PUBLIC NOBLOCK void
NOTHROW(FCALL mman_unmap_kram)(PAGEDIR_PAGEALIGNED void *addr,
                               size_t num_bytes, gfp_t flags) {
	struct mman_unmap_kram_job *job;
	if unlikely(!num_bytes)
		return;
	assert(!(flags & ~(GFP_CALLOC)));
	assert(IS_ALIGNED((uintptr_t)addr, PAGESIZE));
	num_bytes = CEIL_ALIGN(num_bytes, PAGESIZE);
	job = (struct mman_unmap_kram_job *)addr;
	job->mukj_done    = NULL;
	job->mukj_minaddr = (byte_t *)addr;
	job->mukj_maxaddr = (byte_t *)addr + num_bytes - 1;
	job->mukj_flags   = flags;
	mman_unmap_kram_ex(job);
}

/* Same as `mman_unmap_kram()', but may be used to improve efficiency
 * when the caller is already holding a lock to `mman_kernel.mm_lock' */
PUBLIC NOBLOCK void
NOTHROW(FCALL mman_unmap_kram_locked)(PAGEDIR_PAGEALIGNED void *addr,
                                      size_t num_bytes, gfp_t flags) {
	struct mman_unmap_kram_job *job;
	if unlikely(!num_bytes)
		return;
	assert(!(flags & ~(GFP_CALLOC)));
	assert(IS_ALIGNED((uintptr_t)addr, PAGESIZE));
	num_bytes = CEIL_ALIGN(num_bytes, PAGESIZE);
	job = (struct mman_unmap_kram_job *)addr;
	job->mukj_done    = NULL;
	job->mukj_minaddr = (byte_t *)addr;
	job->mukj_maxaddr = (byte_t *)addr + num_bytes - 1;
	job->mukj_flags   = flags;

	/* Try to unmap kernel ram directly. */
	job = mman_unmap_kram_locked_ex(job);
	assert(job != MMAN_UNMAP_KRAM_LOCKED_EX_DONE);
	if unlikely(job != MMAN_UNMAP_KRAM_LOCKED_EX_ASYNC) {
		job->mukj_lop_mm.olo_func = &lockop_kram_cb;
		SLIST_ATOMIC_INSERT(&mman_kernel_lockops,
		                    &job->mukj_lop_mm,
		                    olo_link);
	}
}

/* Do all of the necessary locking and queuing to eventually bring `job' to completion. */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) void
NOTHROW(FCALL mman_unmap_kram_ex)(/*inherit(always)*/ struct mman_unmap_kram_job *__restrict job) {
	if (mman_lock_tryacquire(&mman_kernel)) {
		struct mman_unmap_kram_job *st;
		/* Try to unmap kernel ram directly. */
		st = mman_unmap_kram_locked_ex(job);
		mman_lock_release(&mman_kernel);
		if (st == MMAN_UNMAP_KRAM_LOCKED_EX_DONE) {
			if likely(job->mukj_done != NULL)
				(*job->mukj_done)(job);
		} else if unlikely(st != MMAN_UNMAP_KRAM_LOCKED_EX_ASYNC) {
			goto do_schedule_lockop;
		}
	} else {
do_schedule_lockop:
		job->mukj_lop_mm.olo_func = &lockop_kram_cb;
		SLIST_ATOMIC_INSERT(&mman_kernel_lockops,
		                    &job->mukj_lop_mm, olo_link);
		_mman_lockops_reap(&mman_kernel);
	}
}



PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL kfree_for_done)(struct mman_unmap_kram_job *__restrict self) {
	kfree(self);
}


/* Helper  function that can  be used to unmap  anything by re-using  `freeme', which must be
 * a kmalloc-pointer with `kmalloc_usable_size(freeme) >= sizeof(struct mman_unmap_kram_job)'
 * in order to represent intermediate storage for */
PUBLIC NOBLOCK NONNULL((3)) void
NOTHROW(FCALL mman_unmap_kram_and_kfree)(void const *addr, size_t num_bytes,
                                         void *__restrict freeme, gfp_t flags) {
	struct mman_unmap_kram_job *job;
	num_bytes += (uintptr_t)addr & PAGEMASK;
	addr      = (void *)FLOOR_ALIGN((uintptr_t)addr, PAGESIZE);
	num_bytes = CEIL_ALIGN(num_bytes, PAGESIZE);
	assert(kmalloc_usable_size(freeme) >= sizeof(struct mman_unmap_kram_job));
	if unlikely(!num_bytes) {
		/* Special case: nothing to do... */
		kfree(freeme);
		return;
	}
	job = (struct mman_unmap_kram_job *)freeme;
	job->mukj_done    = &kfree_for_done;
	job->mukj_minaddr = (byte_t *)addr;
	job->mukj_maxaddr = (byte_t *)addr + num_bytes - 1;
	job->mukj_flags   = flags;
	mman_unmap_kram_ex(job);
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_KRAM_UNMAP_C */
