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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MM_KRAM_UNMAP_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MM_KRAM_UNMAP_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/mman.h>
#include <kernel/mman/mcoreheap.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mm-kram.h>
#include <kernel/mman/mm-lockop.h>
#include <kernel/mman/mm-sync.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/swap.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/minmax.h>

#include <kos/except.h>
#include <sys/mmio.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#ifndef NDEBUG
#define DBG_memset(dst, byte, num_bytes) memset(dst, byte, num_bytes)
#else /* !NDEBUG */
#define DBG_memset(dst, byte, num_bytes) (void)0
#endif /* NDEBUG */

STATIC_ASSERT_MSG(GFP_ATOMIC == 0x0400,
                  "This is currently hard-coded in "
                  "<kernel/mman/mm-map.h> and "
                  "<kernel/mman/mm-lockop.h>");

#ifndef CONFIG_NO_SMP
/* Atomic counter for how many CPUs are currently initializing hinted pages (s.a. `MNODE_F_MHINT').
 * This counter behaves similar to the in-use counter found in ATOMIC_REF, and is needed in order
 * to allow for syncing of internal re-trace operations in `mman_unmap_kram_locked()' with
 * other CPUs having previously started initializing hinted pages.
 *
 * For more information on the data race solved by this counter, see the detailed explanation
 * of `mman_kernel_hintinit_inuse' within `mman_unmap_kram_locked()' */
INTERN WEAK unsigned int mman_kernel_hintinit_inuse = 0;
#endif /* !CONFIG_NO_SMP */


struct mlockop_kram;
SLIST_HEAD(mlockop_kram_slist, mlockop_kram);

struct mlockop_kram: mlockop {
	PAGEDIR_PAGEALIGNED size_t lkr_size;  /* Total size (in bytes of the region)  */
	gfp_t                      lkr_flags; /* Set of `0 | GFP_CALLOC' */
};



PRIVATE NOBLOCK struct mlockop *
NOTHROW(FCALL mlockop_kram_cb)(struct mlockop *__restrict self, gfp_t flags) {
	struct mlockop_kram *me;
	size_t size;
	me   = (struct mlockop_kram *)self;
	size = me->lkr_size;
	assert(!(flags & GFP_CALLOC));
	assert(me->lkr_flags == 0 || me->lkr_flags == GFP_CALLOC);
	flags |= me->lkr_flags;
	if (flags & GFP_CALLOC)
		memset(me, 0, sizeof(*me)); /* Ensure consistent zero-initialized-ness */
	/* (try to) do the actual unmapping. */
	return mman_unmap_kram_locked_ex(self, size, flags);
}



PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mlockop_slist_sorted_insert_byaddr)(struct mlockop_kram_slist *__restrict self,
                                                  struct mlockop *__restrict op) {
	struct mlockop **p_next, *next;
	p_next = (struct mlockop **)SLIST_P_FIRST(self);
	while ((next = *p_next) != NULL) {
		assert(next != op);
		if (next > op)
			break; /* Insert before this one! */
		p_next = SLIST_P_NEXT(next, mlo_link);
	}
	SLIST_P_INSERT_BEFORE(p_next, op, mlo_link);
}



PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mlockop_kram_slist_merge_adjacent)(struct mlockop_kram_slist *__restrict self) {
	struct mlockop_kram *iter, *next;
	assert(!SLIST_EMPTY(self));
	iter = SLIST_FIRST(self);
	for (;;) {
		next = (struct mlockop_kram *)SLIST_NEXT(iter, mlo_link);
		if (!next)
			break;
		if ((byte_t *)iter + iter->lkr_size == (byte_t *)next) {
			/* Merge these together! */
			iter->mlo_link.sle_next = next->mlo_link.sle_next;
			iter->lkr_size += next->lkr_size;
			iter->lkr_flags &= next->lkr_flags;
			if (iter->lkr_flags & GFP_CALLOC)
				memset(next, 0, sizeof(*next));
			continue;
		}
		/* Continue trying to merge other segments. */
		iter = next;
	}
}



/* Reap lock operations of `self' */
PUBLIC NOBLOCK void
NOTHROW(FCALL _mman_lockops_reap)(gfp_t flags) {
	struct mlockop_slist more;
	struct mlockop_slist lops;
	struct mlockop_kram_slist kram;
	struct mlockop *iter;
	assert(flags & GFP_ATOMIC);
	assert(!(flags & GFP_CALLOC));
again:
	if (!mman_lock_tryacquire(&mman_kernel))
		return;
	lops.slh_first = SLIST_ATOMIC_CLEAR(&mman_kernel_lockops);
again_service_lops:
	SLIST_INIT(&kram);
	SLIST_INIT(&more);
	iter = SLIST_FIRST(&lops);
	while (iter != NULL) {
		struct mlockop *lop_more, *next;
		next = SLIST_NEXT(iter, mlo_link);
		/* Execute these later... */
		if (iter->mlo_func == &mlockop_kram_cb) {
			/* Insert into the kram-list of operations. */
			mlockop_slist_sorted_insert_byaddr(&kram, iter);
		} else {
			/* Invoke the lock operation. */
			iter->mlo_link.sle_next = NULL;
			lop_more = (*iter->mlo_func)(iter, flags);
			if unlikely(lop_more != NULL) {
				struct mlockop *last;
				last = lop_more;
				while (SLIST_NEXT(last, mlo_link) != NULL)
					last = SLIST_NEXT(last, mlo_link);
				/* Re-queue future operations. */
				SLIST_INSERT_R(&more, lop_more, last, mlo_link);
			}
		}
		iter = next;
	}
	/* At this point, all remaining elements in `kram' are requests
	 * for unmapping kernel RAM, which have already been sorted by
	 * their base address. */
	if likely(!SLIST_EMPTY(&kram)) {
		/* Merge adjacent kram operations */
		mlockop_kram_slist_merge_adjacent(&kram);
		/* Invoke unmap-kernel-ram lops */
		do {
			struct mlockop *lop, *lop_more;
			lop            = (struct mlockop *)SLIST_FIRST(&kram);
			kram.slh_first = (struct mlockop_kram *)SLIST_NEXT(lop, mlo_link);
			/*lop->mlo_link.sle_next = NULL;*/ /* `mlockop_kram_cb()' doesn't care about this... */
			lop_more = mlockop_kram_cb(lop, flags);
			if unlikely(lop_more != NULL) {
				struct mlockop *last;
				last = lop_more;
				while (SLIST_NEXT(last, mlo_link) != NULL)
					last = SLIST_NEXT(last, mlo_link);
				/* Re-queue future operations. */
				SLIST_INSERT_R(&more, lop_more, last, mlo_link);
			}
		} while (!SLIST_EMPTY(&kram));
	}

	mman_lock_release_f(&mman_kernel);
	/* If other lops (aside from `more') were addend, then consume
	 * them an merge them with `more' before trying to service all
	 * of them together as one large package!
	 * Doing this can improve efficiency of unmap-kernel-ram requests! */
enqueue_more:
	if (!ATOMIC_CMPXCH(mman_kernel_lockops.slh_first, NULL, more.slh_first)) {
		lops.slh_first = ATOMIC_XCH(mman_kernel_lockops.slh_first, NULL);
		if (!SLIST_EMPTY(&more)) {
			struct mlockop *last;
			last = SLIST_FIRST(&lops);
			while (SLIST_NEXT(last, mlo_link) != NULL)
				last = SLIST_NEXT(last, mlo_link);
			last->mlo_link.sle_next = more.slh_first;
		}
		if (mman_lock_tryacquire(&mman_kernel))
			goto again_service_lops;
		/* Enqueue everything together. */
		more = lops;
		goto enqueue_more;
	}
}



/* Run `op->mlo_func' in the context of holding a lock to the kernel VM at some
 * point in the future. The given `op->mlo_func' is responsible for freeing the
 * backing memory of `op' during its invocation. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mman_kernel_lockop)(struct mlockop *__restrict op, gfp_t flags) {
	/* Atomically insert the new lock operation. */
	SLIST_ATOMIC_INSERT(&mman_kernel_lockops, op, mlo_link);
	_mman_lockops_reap(flags);
}



/* Same as `mman_kernel_lockop()', but `op->mlo_link' may point to another lock
 * op that should also be enqueued, which may point to another, and so on...
 * Additionally, `op' may be `NULL', in which case the call is a no-op */
PUBLIC NOBLOCK void
NOTHROW(FCALL mman_kernel_lockop_many)(struct mlockop *op, gfp_t flags) {
	struct mlockop *lastop;
	if unlikely(!op)
		return;
	lastop = op;
	while (SLIST_NEXT(lastop, mlo_link) != NULL)
		lastop = SLIST_NEXT(lastop, mlo_link);
	/* Atomically insert all of the new elements. */
	SLIST_ATOMIC_INSERT_R(&mman_kernel_lockops, op, lastop, mlo_link);
	_mman_lockops_reap(flags);
}



/* Without blocking, unmap a given region of kernel RAM.
 * These functions will attempt to acquire a lock to the kernel mman, and
 * if that fails, will instead inject a pending lock operation into the
 * kernel mman's `mman_kernel_lockops', which will then perform the actual
 * job of unmapping the associated address range as soon as doing so becomes
 * possible.
 * These functions may only be used to unmap nodes mapped with the `MNODE_F_NO_MERGE'
 * flag, as well as read+write permissions. Additionally, if preparing the backing
 * page directory fails, as might happen if the associated node didn't have the
 * `MNODE_F_MPREPARED' flag set, then a warning is written to the system (unless
 * an internal rate-limit check fails), and the unmap operation is re-inserted as
 * a pending lock operation into `mman_kernel_lockops' (meaning that the unmap will
 * be re-attempted repeatedly until it (hopefully) succeeds at some point)
 * @param: flags:   Set of `GFP_*'. When `GFP_CALLOC' is given, allows the memory
 *                  management system to assume that the backing physical memory
 *                  is zero-initialized. If you're not sure if this is the case,
 *                  better pass `false'. If you lie here, calloc() might arbitrarily
 *                  break... */
PUBLIC NOBLOCK_IF(flags & GFP_ATOMIC) void
NOTHROW(FCALL mman_unmap_kram)(PAGEDIR_PAGEALIGNED void *addr,
                               PAGEDIR_PAGEALIGNED size_t num_bytes,
                               gfp_t flags) {
	struct mlockop_kram *lockop;
	assert(num_bytes != 0);
	assert(IS_ALIGNED((uintptr_t)addr, PAGESIZE));
	assert(IS_ALIGNED(num_bytes, PAGESIZE));
	assert(flags & GFP_ATOMIC);
	if (mman_lock_tryacquire(&mman_kernel)) {
		/* Directly try to unmap kernel ram. */
		lockop = (struct mlockop_kram *)mman_unmap_kram_locked_ex(addr, num_bytes, flags);
		mman_lock_release(&mman_kernel);
		if unlikely(lockop != NULL)
			goto do_schedule_lockop;
	} else {
		lockop = (struct mlockop_kram *)addr;
		lockop->mlo_func  = &mlockop_kram_cb;
		lockop->lkr_size  = num_bytes;
		lockop->lkr_flags = flags & GFP_CALLOC;
do_schedule_lockop:
		mman_kernel_lockop(lockop);
	}
}


INTDEF NOBLOCK NONNULL((1, 2)) void /* From "mpart.c" */
NOTHROW(FCALL mnode_unlink_from_part_lockop)(struct mpart_lockop *__restrict self,
                                             struct mpart *__restrict part);


PRIVATE NOBLOCK void
NOTHROW(FCALL mnode_destroy_kram)(struct mnode *__restrict self) {
	REF struct mpart *part;
	part = self->mn_part;
	if unlikely(self->mn_fspath != NULL)
		decref(self->mn_fspath);
	if unlikely(self->mn_fsname != NULL)
		decref(self->mn_fsname);

	/* Try to unlink the node from the copy- or share-chain of the associated part. */
	if (mpart_lock_tryacquire(part)) {
		LIST_REMOVE(self, mn_link);
		if ((self->mn_flags & (MNODE_F_MLOCK)) &&
		    (part->mp_flags & (MPART_F_MLOCK | MPART_F_MLOCK_FROZEN)) == MPART_F_MLOCK)
			ATOMIC_AND(part->mp_flags, ~MPART_F_MLOCK);
		mpart_lock_release(part);
		decref_unlikely(part);
	} else {
		struct mpart_lockop *lop;
		/* Must insert the node into the part's list of deleted nodes. */
		weakincref(&mman_kernel); /* A weak reference here is required by the ABI */
		DBG_memset(&self->mn_part, 0xcc, sizeof(self->mn_part));

		/* Insert into the lock-operations list of `part'
		 * The act of doing this is what essentially causes
		 * ownership of our node to be transfered to `part' */
		lop = (struct mpart_lockop *)self;
		lop->mplo_func = &mnode_unlink_from_part_lockop;
		SLIST_ATOMIC_INSERT(&part->mp_lockops, lop, mplo_link);

		/* Try to reap dead nodes. */
		_mpart_deadnodes_reap(part);

		/* Drop our old reference to the associated part. */
		decref_likely(part);
		return;
	}
	mnode_free(self);
}

typedef NOBLOCK void
/*NOTHROW*/(FCALL *freefun_t)(physpage_t base, physpagecnt_t num_pages, gfp_t flags);
PRIVATE NOBLOCK void
NOTHROW(FCALL freefun_phys)(physpage_t base,
                            physpagecnt_t num_pages,
                            gfp_t flags) {
	page_ffree(base, num_pages, (flags & GFP_CALLOC) != 0);
}
PRIVATE NOBLOCK void
NOTHROW(FCALL freefun_swap)(physpage_t base,
                            physpagecnt_t num_pages,
                            gfp_t UNUSED(flags)) {
	swap_free(base, num_pages);
}
PRIVATE NOBLOCK void
NOTHROW(FCALL freefun_noop)(physpage_t UNUSED(base),
                            physpagecnt_t UNUSED(num_pages),
                            gfp_t UNUSED(flags)) {
}

PRIVATE ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) freefun_t
NOTHROW(FCALL freefun_for_mpart)(struct mpart const *__restrict self) {
	freefun_t result;
	switch (self->mp_state) {

	case MPART_ST_SWP:
	case MPART_ST_SWP_SC:
		result = &freefun_swap;
		break;

	case MPART_ST_MEM:
	case MPART_ST_MEM_SC:
		result = &freefun_phys;
		if (self->mp_flags & MPART_F_DONT_FREE)
			result = &freefun_noop;
		break;

	default:
		result = &freefun_noop;
		break;
	}
	return result;
}



PRIVATE NOBLOCK NONNULL((1, 3)) void
NOTHROW(FCALL mchunkvec_truncate)(struct mchunkvec *__restrict self,
                                  physpagecnt_t total_pages,
                                  freefun_t freefun, gfp_t flags,
                                  bool maybe_hinted) {
	size_t i;
	physpagecnt_t total = 0;
	assert(total_pages != 0);
	for (i = 0;; ++i) {
		assert(i < self->ms_c);
		total += self->ms_v[i].mc_size;
		if (total > total_pages) {
			size_t keep;
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
			if (i < (self->ms_c - 1)) {
				size_t new_count = i;
				for (++i; i < self->ms_c; ++i) {
					(*freefun)(self->ms_v[i].mc_start,
					           self->ms_v[i].mc_size,
					           flags);
				}
				if (maybe_hinted) {
					krealloc_in_place_nx(self->ms_v,
					                     new_count * sizeof(struct mchunk),
					                     flags & ~GFP_CALLOC);
				} else {
					struct mchunk *vec;
					vec = (struct mchunk *)krealloc_nx(self->ms_v,
					                                   new_count * sizeof(struct mchunk),
					                                   GFP_LOCKED | GFP_PREFLT |
					                                   (flags & ~GFP_CALLOC));
					if likely(vec != NULL)
						self->ms_v = vec;
				}
				self->ms_c = new_count;
			}
		}
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
	                                   self->ms_c * sizeof(struct mchunk),
	                                   GFP_LOCKED | GFP_PREFLT |
	                                   (flags & ~GFP_CALLOC));
	if likely(vec != NULL)
		self->ms_v = vec;
}

PRIVATE NOBLOCK void
NOTHROW(FCALL unmap_and_unprepare_and_sync_memory)(void *addr, size_t num_bytes) {
	/* Unmap the affected address range & sync in every mman. */
	pagedir_unmap(addr, num_bytes);
	mman_supersync(addr, num_bytes);
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	pagedir_unprepare_map(addr, num_bytes);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

#if !defined(NDEBUG) && !defined(CONFIG_NO_SMP)
	/* This check right here only serves to turn fully undefined behavior
	 * when another CPU is currently initializing a page which we've just
	 * unmapped (which would indicate an error elsewhere within the kernel)
	 * into something that's a bit easier to narrow down:
	 * Instead of (possibly) failing anywhere within the hinted-page-mapping
	 * function, fail with a normal #PF upon access to bad memory. */
	while (ATOMIC_READ(mman_kernel_hintinit_inuse) != 0)
		task_pause();
#endif /* !NDEBUG && !CONFIG_NO_SMP */
}

PRIVATE NOBLOCK void
NOTHROW(FCALL movedown_bits)(mpart_blkst_word_t *__restrict dst_bitset,
                             mpart_blkst_word_t const *__restrict src_bitset,
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



/* (try to) unmap the given sub-range of virtual (kernel)
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
	size_t unmap_size;
	freefun_t freefun;
	assert(flags & GFP_ATOMIC);
	assert(mman_lock_acquired(&mman_kernel));
	assert(mpart_lock_acquired(part));
	assert(!(part->mp_flags & MPART_F_NO_SPLIT));
	assert(!(node->mn_flags & MNODE_F_NO_SPLIT));
	assert(unmap_minaddr >= node->mn_minaddr);
	assert(unmap_maxaddr <= node->mn_maxaddr);
	assertf(unmap_minaddr != node->mn_minaddr || unmap_maxaddr != node->mn_maxaddr,
	        "This case should be handled by the caller");
	unmap_size = (size_t)(unmap_maxaddr - unmap_minaddr) + 1;
	freefun    = freefun_for_mpart(part);

	/* Check for simple case: Truncate the node/part at the back. */
	if (unmap_minaddr == node->mn_minaddr) {
		size_t part_size;
		physpagecnt_t part_pages;

		/* Truncate at the back. */
		mnode_tree_removenode(&mman_kernel.mm_mappings, node);

		/* Unmap the affected address range & sync in every mman. */
		unmap_and_unprepare_and_sync_memory(unmap_minaddr, unmap_size);

		COMPILER_WRITE_BARRIER();
		node->mn_maxaddr = unmap_minaddr - 1;
		part_size        = node->mn_partoff + (size_t)(unmap_minaddr - node->mn_minaddr);
		assert(part->mp_maxaddr > part->mp_minaddr + part_size - 1);
		part->mp_maxaddr = part->mp_minaddr + part_size - 1;
		if (!(part->mp_flags & MPART_F_BLKST_INL) && part->mp_blkst_ptr != NULL) {
			size_t word_count, block_count;
			block_count = part_size >> part->mp_file->mf_blockshift;
			word_count  = CEILDIV(block_count, MPART_BLKST_BLOCKS_PER_WORD);
			if (node->mn_flags & MNODE_F_MHINT) {
				krealloc_in_place_nx(part->mp_blkst_ptr,
				                     word_count * sizeof(mpart_blkst_word_t),
				                     flags & ~GFP_CALLOC);
			} else {
				mpart_blkst_word_t *bitset;
				bitset = (mpart_blkst_word_t *)krealloc_nx(part->mp_blkst_ptr,
				                                      word_count * sizeof(mpart_blkst_word_t),
				                                      GFP_LOCKED | GFP_PREFLT |
				                                      (flags & ~GFP_CALLOC));
				if likely(bitset != NULL)
					part->mp_blkst_ptr = bitset;
			}
		}
		part_pages = (physpagecnt_t)(part_size >> PAGESHIFT);
		/* Free unused memory from the part backing data store. */
		switch (part->mp_state) {

		case MPART_ST_SWP:
		case MPART_ST_MEM:
			assert(part->mp_mem.mc_size > part_pages);
			(*freefun)(part->mp_mem.mc_start + part_pages,
			           part->mp_mem.mc_size - part_pages,
			           flags);
			part->mp_mem.mc_size = part_pages;
			break;

		case MPART_ST_SWP_SC:
		case MPART_ST_MEM_SC:
			mchunkvec_truncate(&part->mp_mem_sc, part_pages, freefun, flags,
			                   (node->mn_flags & MNODE_F_MHINT) != 0);
			break;

		default:
			break;
		}

		/* Re-insert the (now truncated) node into the kernel mman. */
		COMPILER_WRITE_BARRIER();
		mnode_tree_insert(&mman_kernel.mm_mappings, node);
		return true;
	}

	/* Either truncate a node at the front, or cut out a chunk in the middle.
	 * In either case, we have to make sure that (in case of a hinted node),
	 * all pages above the to-be unmapped area have been fully initialized,
	 * thus ensuring that no other CPU (or thread) might possibly try to load
	 * pages from that upper area when we need to change its backing pointers. */
	if (node->mn_flags & MNODE_F_MHINT) {
		byte_t *tail_minaddr, *tail_endaddr;
		tail_minaddr = unmap_maxaddr + 1;
		tail_endaddr = (byte_t *)mnode_getendaddr(node);
		/* We keep the lazy initialization of hinted nodes simple, and let
		 * the #PF handler to most of the work. As such, all we really have
		 * to do is ensure that every page from the tail-range has been
		 * accessed at least once. */
		do {
			peekb(tail_minaddr);
			tail_minaddr += PAGESIZE;
		} while (tail_minaddr < tail_endaddr);

#ifndef CONFIG_NO_SMP
		/* Make sure that any other CPU is still initializing hinted pages,
		 * which may overlap with the address range we've just loaded. */
		while (ATOMIC_READ(mman_kernel_hintinit_inuse) != 0)
			task_pause();
#endif /* !CONFIG_NO_SMP */
	}

	if unlikely(node->mn_partoff != 0) {
		/* TODO: Truncate the leading address range that was never even mapped...
		 *       All of the below code assumes that it is operating on a zero
		 *       offset mnode->mpart mapping. */
	}
	{
		size_t mpart_size;
		mpart_size = mpart_getsize(part);
		assert(mpart_size >= mnode_getsize(node));
		if unlikely(mpart_size > mnode_getsize(node)) {
			/* TODO: Truncate the trailing address range that was never even mapped.
			 *       All of the below code assumes that the original part isn't larger
			 *       than the associated node. */
		}
	}

	/* Check for slightly more complicated case: Truncate a node at the front. */
	if (unmap_minaddr == node->mn_minaddr) {
		size_t remove_size, remove_blocks;
		physpagecnt_t remove_pages;
		/* We can truncate the node at the front. */
		unmap_and_unprepare_and_sync_memory(unmap_minaddr, unmap_size);
		remove_size   = (size_t)((unmap_maxaddr + 1) - node->mn_minaddr);
		remove_pages  = remove_size >> PAGESHIFT;
		remove_blocks = remove_size >> part->mp_file->mf_blockshift;
		mnode_tree_removenode(&mman_kernel.mm_mappings, node);
		COMPILER_WRITE_BARRIER();
		node->mn_minaddr += remove_size;
		part->mp_maxaddr -= remove_size;
		if (part->mp_flags & MPART_F_BLKST_INL) {
			part->mp_blkst_inl >>= remove_blocks * MPART_BLOCK_STBITS;
		} else if (part->mp_blkst_ptr != NULL) {
			mpart_blkst_word_t *bitset;
			size_t word_count, keep_blocks;
			keep_blocks = mpart_getblockcount(part, part->mp_file);
			movedown_bits(part->mp_blkst_ptr, part->mp_blkst_ptr,
			              0, remove_blocks * MPART_BLOCK_STBITS,
			              keep_blocks * MPART_BLOCK_STBITS);
			word_count = CEILDIV(keep_blocks, MPART_BLKST_BLOCKS_PER_WORD);
			assert(word_count >= 0);
			if (word_count == 1) {
				/* Switch over to using an in-line bitset. */
				bitset = part->mp_blkst_ptr;
				part->mp_blkst_inl = bitset[0];
				part->mp_flags |= MPART_F_BLKST_INL;
				kfree(bitset);
			} else {
				/* Try to release unused memory. */
				bitset = (mpart_blkst_word_t *)krealloc_nx(part->mp_blkst_ptr,
				                                      word_count * sizeof(mpart_blkst_word_t),
				                                      GFP_LOCKED | GFP_PREFLT |
				                                      (flags & ~GFP_CALLOC));
				if likely(bitset != NULL)
					part->mp_blkst_ptr = bitset;
			}
		}

		/* Free unused memory from the part backing data store. */
		switch (part->mp_state) {

		case MPART_ST_SWP:
		case MPART_ST_MEM:
			assert(part->mp_mem.mc_size > remove_pages);
			(*freefun)(part->mp_mem.mc_start, remove_pages, flags);
			part->mp_mem.mc_start += remove_pages;
			part->mp_mem.mc_size -= remove_pages;
			break;

		case MPART_ST_SWP_SC:
		case MPART_ST_MEM_SC:
			mchunkvec_truncate_leading(&part->mp_mem_sc, remove_pages,
			                           freefun, flags);
			break;

		default:
			break;
		}

		/* Re-insert the (now truncated) node into the kernel mman. */
		COMPILER_WRITE_BARRIER();
		mnode_tree_insert(&mman_kernel.mm_mappings, node);
		return true;
	}

	/* Cut-out a hole in the middle.
	 *
	 * Note that for this purpose, we may even use `mcoreheap_alloc_locked_nx()'
	 * in order to dynamically allocate the required additional data structures! */
	{
		struct mnode *hinode, *lonode = node;
		struct mpart *hipart, *lopart = part;
		size_t losize, hisize, hioffset;

		/* Allocate new elements for the hi-node and hi-part. */
		hinode = (struct mnode *)kmalloc_nx(sizeof(struct mnode),
		                                    GFP_LOCKED | GFP_PREFLT |
		                                    (flags & ~GFP_CALLOC));
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
		hipart = (struct mpart *)kmalloc_nx(sizeof(struct mpart),
		                                    GFP_LOCKED | GFP_PREFLT |
		                                    (flags & ~GFP_CALLOC));
		if (hipart) {
			hipart->mp_flags = MPART_F_NORMAL;
		} else {
			union mcorepart *cp;
			cp = mcoreheap_alloc_locked_nx();
			if unlikely(cp == NULL) {
				mnode_free(hinode);
				goto fail;
			}
			hipart           = &cp->mcp_part;
			hipart->mp_flags = MPART_F_NORMAL | MPART_F_COREPART;
		}

		/* Figure out the eventual sizes of the lo- and hi-parts */
		losize   = unmap_minaddr - node->mn_minaddr;
		hisize   = node->mn_maxaddr - unmap_maxaddr;
		hioffset = (size_t)((unmap_maxaddr + 1) - node->mn_minaddr);
		assert(losize != 0);
		assert(hisize != 0);
		assert(IS_ALIGNED(losize, PAGESIZE));
		assert(IS_ALIGNED(hisize, PAGESIZE));

		/* Check if we also need to allocate an additional
		 * block-status bitset for use with `hipart' */
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
				bitset = (mpart_blkst_word_t *)kmalloc_nx(new_bitset_words * sizeof(mpart_blkst_word_t),
				                                     GFP_LOCKED | GFP_PREFLT | (flags & ~GFP_CALLOC));
				if unlikely(!bitset) {
					mpart_free(hipart);
					mnode_free(hinode);
					goto fail;
				}
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
			size_t lo_chunks, hi_chunks, i;
			struct mchunkvec vec;

			/* We may have to allocate a new dynamic mem/swap vector.
			 * First of all: Figure out where exactly the split needs
			 * to happen, in terms of CHUNK_INDEX and CHUNK_OFFSET for
			 * both where the lo-part will end, and where the hi-part
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
			hi_split_chunk_offset = lo_split_chunk_offset + (hioffset - losize) >> PAGESHIFT;
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
			 * For this, start out by figuring out exactly how many chunks we'll be needing
			 * for the lo- and hi-part's chunk-vectors. */
			lo_chunks = lo_split_chunk_index;
			if (lo_split_chunk_offset != 0) {
				assert(lo_split_chunk_index != 0);
				++lo_chunks;
			}
			hi_chunks = vec.ms_c - hi_split_chunk_index;
			assert(lo_chunks >= 1);
			assert(hi_chunks >= 1);
			/* Handle the simple cases where one of the 2 parts can
			 * be implemented without the need of a chunk-vector. */
			if (lo_chunks == 1 && hi_chunks == 1) {
				/* Both parts only need a single chunk. */
				assert(lo_split_chunk_index == 0);
				assert(hi_split_chunk_index == vec.ms_c - 1);
				lopart->mp_state = lopart->mp_state == MPART_ST_MEM_SC ? MPART_ST_MEM : MPART_ST_SWP;
				hipart->mp_state = lopart->mp_state;
				lopart->mp_mem.mc_start = vec.ms_v[0].mc_start;
				lopart->mp_mem.mc_size  = lo_split_chunk_offset;
				hipart->mp_mem.mc_start = vec.ms_v[hi_split_chunk_index].mc_start + hi_split_chunk_offset;
				hipart->mp_mem.mc_size  = vec.ms_v[hi_split_chunk_index].mc_size - hi_split_chunk_offset;
				/* === Point of no return */

				/* Unmap the requested address range. */
				unmap_and_unprepare_and_sync_memory(unmap_minaddr, unmap_size);

				/* Free physical memory. */
				if (lo_split_chunk_offset != 0) {
					/* Free apart of the first chunk. */
					(*freefun)(vec.ms_v[0].mc_start + lo_split_chunk_offset,
					           vec.ms_v[0].mc_size - lo_split_chunk_offset,
					           flags);
				}
				/* Free all intermediate chunks. */
				for (i = 1; i < hi_split_chunk_index; ++i) {
					(*freefun)(vec.ms_v[i].mc_start,
					           vec.ms_v[i].mc_size,
					           flags);
				}
				/* Free the lead-up to `hipart's chunk */
				if (hi_split_chunk_offset != 0) {
					(*freefun)(vec.ms_v[hi_split_chunk_index].mc_start,
					           hi_split_chunk_offset,
					           flags);
				}
				kfree(vec.ms_v);
			} else if (lo_chunks == 1) {
				/* TODO: `hipart' must use a vector, while `lopart' uses a single chunk. */
				/* === Point of no return */
				unmap_and_unprepare_and_sync_memory(unmap_minaddr, unmap_size);
			} else if (hi_chunks == 1) {
				/* TODO: `lopart' must stay as a vector, and `hipart' becomes a single chunk. */
				/* === Point of no return */
				unmap_and_unprepare_and_sync_memory(unmap_minaddr, unmap_size);
			} else {
				/* TODO: `lopart' must stay as a vector, and an additional vector needs to
				 *       be allocated for use by `hipart'. */
				/* === Point of no return */
				unmap_and_unprepare_and_sync_memory(unmap_minaddr, unmap_size);
			}
			/* TODO */
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
			           lopart->mp_mem.mc_size - losize_pages,
			           flags);
			lopart->mp_mem.mc_size = losize_pages;
		}	break;

		default:
			/* === Point of no return */
			unmap_and_unprepare_and_sync_memory(unmap_minaddr, unmap_size);
			break;
		}

		/* Remove the old node from the kernel mman. */
		mnode_tree_removenode(&mman_kernel.mm_mappings, node);

		if (lopart->mp_flags & MPART_F_BLKST_INL) {
			size_t hioffset_blocks;
			hioffset_blocks      = hioffset >> part->mp_file->mf_blockshift;
			hipart->mp_blkst_inl = lopart->mp_blkst_inl >> (hioffset_blocks * MPART_BLOCK_STBITS);
			hipart->mp_flags |= MPART_F_BLKST_INL;
		} else if (lopart->mp_blkst_ptr != NULL) {
			size_t bitset_bytes_per_word, hioffset_blocks;
			size_t loblocks, hiblocks;
			unsigned int blockshift;
			blockshift            = part->mp_file->mf_blockshift;
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
					                                              GFP_LOCKED | GFP_PREFLT | (flags & ~GFP_CALLOC));
					if likely(smaller_bitset != NULL)
						hiset = smaller_bitset;
					/* Write-back the updated bitsets. */
					lopart->mp_blkst_ptr = loset;
					hipart->mp_blkst_ptr = hiset;
				}
			} else if (hisize > bitset_bytes_per_word) {
				mpart_blkst_word_t *hiset, *smaller_bitset;
				/* Re-use the bitset from `lopart' in `hipart', and
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
				                                              GFP_LOCKED | GFP_PREFLT | (flags & ~GFP_CALLOC));
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
		lopart->mp_maxaddr = lopart->mp_minaddr;
		hinode->mn_flags  |= lonode->mn_flags & (MNODE_F_PEXEC | MNODE_F_PWRITE |
		                                         MNODE_F_PREAD | MNODE_F_SHARED |
		                                         MNODE_F_MPREPARED | MNODE_F_MLOCK);
		hinode->mn_part    = hipart; /* Inherit reference */
		hinode->mn_fspath  = xincref(lonode->mn_fspath);
		hinode->mn_fsname  = xincref(lonode->mn_fsname);
		hinode->mn_mman    = &mman_kernel;
		hinode->mn_partoff = 0;
		/*hinode->mn_link  = ...;*/ /* Initialized below */

		/* Have the hi-node mirror the is-writable attribute of the lo-node */
		LIST_ENTRY_UNBOUND_INIT(hinode, mn_writable);
		if (LIST_ISBOUND(lonode, mn_writable)) {
			LIST_INSERT_HEAD(&mman_kernel.mm_writable,
			                 hinode, mn_writable);
		}

		/* Initialize the hi-part. */
		hipart->mp_refcnt = 1;
		hipart->mp_flags |= lopart->mp_flags & (MPART_F_MAYBE_BLK_INIT | MPART_F_NO_GLOBAL_REF |
		                                        MPART_F_CHANGED | MPART_F_DONT_FREE |
		                                        MPART_F_MLOCK | MPART_F_MLOCK_FROZEN);
		/*hipart->mp_state = ...;*/ /* Alraedy initialized above */
		hipart->mp_file = incref(lopart->mp_file);
		LIST_INIT(&hipart->mp_copy);
		LIST_INIT(&hipart->mp_share);
		hinode->mn_link.le_next = NULL;
		if (lonode->mn_flags & MNODE_F_SHARED) {
			hinode->mn_link.le_prev = &hipart->mp_share.lh_first;
		} else {
			hinode->mn_link.le_prev = &hipart->mp_copy.lh_first;
		}
		*hinode->mn_link.le_prev = hinode;
		SLIST_INIT(&hipart->mp_lockops);
		/*LIST_ENTRY_UNBOUND_INIT(hipart, mp_allparts);*/ /* Initialized below */
		DBG_memset(&hipart->mp_changed, 0xcc, sizeof(hipart->mp_changed));
		hipart->mp_minaddr = 0;
		hipart->mp_maxaddr = (pos_t)(hisize - 1);
		DBG_memset(&hipart->mp_filent, 0xcc, sizeof(hipart->mp_filent));
		/*hipart->mp_blkst_ptr = ...;*/ /* Initialized above */
		/*hipart->mp_mem       = ...;*/ /* Initialized above */
		hipart->mp_meta = NULL;

		/* Mirror the part-of-global-list status of `lopart' in `hipart' */
		if (LIST_ISBOUND(hipart, mp_allparts)) {
			if (!(lopart->mp_flags & MPART_F_NO_GLOBAL_REF))
				hipart->mp_refcnt = 2; /* +1 for the global list. */
			mpart_all_list_insert(hipart);
		} else {
		    LIST_ENTRY_UNBOUND_INIT(hipart, mp_allparts);
			assertf(lopart->mp_flags & MPART_F_NO_GLOBAL_REF,
			        "How can you have a global ref, but not be part of the global list?");
		}

		/* Insert the lo- and hi-nodes now that they've been updated
		 * to include the requested gap in-between. */
		mnode_tree_insert(&mman_kernel.mm_mappings, lonode);
		mnode_tree_insert(&mman_kernel.mm_mappings, hinode);

		/* And we're done! */
		return true;
	}
fail:
	return false;
}


/* Insert `lop' into the lock-operations list of `mman_kernel',
 * and return `true', or don't insert it into the list, acquire
 * a lock to `mman_kernel', and return `false' */
PRIVATE NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL mman_lockop_insert_or_lock)(struct mlockop *__restrict lop) {
	bool did_remove;
	struct mlockop_slist locklist;
	SLIST_ATOMIC_INSERT(&mman_kernel_lockops, lop, mlo_link);
	if likely(!mman_lock_tryacquire(&mman_kernel))
		return true;
	/* Welp... We've got the lock... -> Try to remove `lop' once again. */
	locklist.slh_first = SLIST_ATOMIC_CLEAR(&mman_kernel_lockops);
	did_remove         = true;
	SLIST_TRYREMOVE(&locklist, lop, mlo_link, {
		did_remove = false;
	});
	if (locklist.slh_first != NULL) {
		/* Re-queue all removed elements. */
		struct mlockop *lastop;
		lastop = SLIST_FIRST(&locklist);
		while (SLIST_NEXT(lastop, mlo_link))
			lastop = SLIST_NEXT(lastop, mlo_link);
		SLIST_ATOMIC_INSERT_R(&mman_kernel_lockops,
		                      SLIST_FIRST(&locklist),
		                      lastop, mlo_link);
	}
	if (!did_remove) {
		/* Lock acquired, but `lop' was already executed.
		 * Act as though we had never acquired the lock in the first place! */
		mman_lock_release(&mman_kernel);
		return true;
	}
	/* Lock acquired, and `lop' not added to the lock-op list. */
	return false;
}


struct mpart_lockop_truncate: mpart_lockop {
	PAGEDIR_PAGEALIGNED size_t mplot_size;  /* Total size (in bytes of the region)  */
	gfp_t                      mplot_flags; /* Set of `0 | GFP_CALLOC' */
};

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mpart_lockop_truncate_cb)(struct mpart_lockop *__restrict self,
                                        struct mpart *__restrict part) {
	struct mpart_lockop_truncate *me;
	struct mnode *node;
	byte_t *unmap_minaddr, *unmap_maxaddr;
	gfp_t flags;
	me            = (struct mpart_lockop_truncate *)self;
	unmap_minaddr = (byte_t *)me;
	unmap_maxaddr = (byte_t *)me + me->mplot_size - 1;
	flags         = me->mplot_flags | GFP_ATOMIC;
	if (flags & GFP_CALLOC)
		memset(me, 0, sizeof(*me));
	if (!mman_lock_tryacquire(&mman_kernel)) {
		struct mlockop_kram *lop;
		lop = (struct mlockop_kram *)me;
		lop->mlo_func  = &mlockop_kram_cb;
		lop->lkr_size  = (size_t)(unmap_maxaddr - (byte_t *)me) + 1;
		lop->lkr_flags = flags;
		if (mman_lockop_insert_or_lock(lop))
			return;
		if (flags & GFP_CALLOC)
			memset(lop, 0, sizeof(*lop));
	}

	/* At this point, we're holding a lock to both the mman, as
	 * well as (what is supposed to be) the backing mem-part.
	 *
	 * As such, start out by validating that this is actually the case. */
	node = mnode_tree_locate(mman_kernel.mm_mappings, unmap_minaddr);
	assertf(node != NULL, "Address %p not mapped", unmap_minaddr);
	assert(mnode_getminaddr(node) >= unmap_minaddr);
	assert(mnode_getmaxaddr(node) <= unmap_maxaddr);
	if unlikely(node->mn_flags & MNODE_F_KERNPART) {
		kernel_panic("Attempted to unmap kernel part at %p-%p (via unmap-kram %p-%p)",
		             mnode_getminaddr(node), mnode_getmaxaddr(node),
		             unmap_minaddr, unmap_maxaddr);
	}
	assert(node->mn_mman == &mman_kernel);
	assert(node->mn_flags & MNODE_F_PREAD);
	assert(node->mn_flags & MNODE_F_PWRITE);
	assert(mnode_iskern(node));
	assert(node->mn_part);
	assert(node->mn_part->mp_flags & MPART_F_NO_GLOBAL_REF);
	if (node->mn_flags & MNODE_F_SHARED) {
		assert(LIST_EMPTY(&node->mn_part->mp_copy));
		assert(LIST_FIRST(&node->mn_part->mp_share) == node);
	} else {
		assert(LIST_EMPTY(&node->mn_part->mp_share));
		assert(LIST_FIRST(&node->mn_part->mp_copy) == node);
	}
	assert(LIST_NEXT(node, mn_link) == NULL);
	assert(mfile_isanon(node->mn_part->mp_file));
#ifdef MPART_ST_VIO
	assert(node->mn_part->mp_state != MPART_ST_VIO);
#endif /* MPART_ST_VIO */

	if unlikely(node->mn_part != part)
		goto changed;
	if unlikely(unmap_minaddr < mnode_getminaddr(node))
		goto changed;
	if unlikely(unmap_maxaddr > mnode_getmaxaddr(node))
		goto changed;
	if unlikely(unmap_minaddr == mnode_getminaddr(node) &&
	            unmap_maxaddr == mnode_getmaxaddr(node))
		goto changed;
	if unlikely(node->mn_flags & MNODE_F_NO_SPLIT)
		goto changed;
	if unlikely(part->mp_flags & MPART_F_NO_SPLIT)
		goto changed;
	/* Everything looks in order.
	 * -> Try to do the actual sub-range unmapping! */
	if (!mman_unmap_mpart_subregion(node, part,
	                                unmap_minaddr,
	                                unmap_maxaddr,
	                                flags))
		goto changed; /* Handle allocation errors by re-attempting later. */
	mman_lock_release(&mman_kernel);
	return;
changed:
	/* Failed to unmap the sub-region.
	 * Resolve this issue by re-queue a pending lock operation for
	 * execution within the context of holding a lock to the kernel
	 * memory manager. */
	{
		struct mlockop_kram *lop;
		lop = (struct mlockop_kram *)me;
		lop->mlo_func  = &mlockop_kram_cb;
		lop->lkr_size  = (size_t)(unmap_maxaddr - (byte_t *)me) + 1;
		lop->lkr_flags = flags;
		SLIST_ATOMIC_INSERT(&mman_kernel_lockops, lop, mlo_link);
	}
	mman_lock_release_f(&mman_kernel);
	_mman_lockops_reap();
}


/* Insert `lop' into the lock-operations list of `self', and
 * return `true', or don't insert it into the list, acquire a
 * lock to `self', and return `false' */
PRIVATE NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL mpart_lockop_insert_or_lock)(struct mpart *__restrict self,
                                           struct mpart_lockop *__restrict lop) {
	bool did_remove;
	struct mpart_lockop_slist locklist;
	SLIST_ATOMIC_INSERT(&self->mp_lockops, lop, mplo_link);
	if likely(!mpart_lock_tryacquire(self))
		return true;
	/* Welp... We've got the lock... -> Try to remove `lop' once again. */
	locklist.slh_first = SLIST_ATOMIC_CLEAR(&self->mp_lockops);
	did_remove         = true;
	SLIST_TRYREMOVE(&locklist, lop, mplo_link, {
		did_remove = false;
	});
	if (locklist.slh_first != NULL) {
		/* Re-queue all removed elements. */
		struct mpart_lockop *lastop;
		lastop = SLIST_FIRST(&locklist);
		while (SLIST_NEXT(lastop, mplo_link))
			lastop = SLIST_NEXT(lastop, mplo_link);
		SLIST_ATOMIC_INSERT_R(&self->mp_lockops,
		                      SLIST_FIRST(&locklist),
		                      lastop, mplo_link);
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


/* Try to unmap kernel raw while the caller is holding a lock to the kernel mman.
 * @param: flags: Set of `GFP_*'
 * @return: NULL: Successfully unmapped kernel ram.
 * @return: * :   Failed to allocate needed memory.
 *                The returned value is a freshly initialized pending mman-
 *                lock-operation which the caller must enqueue for execution.
 *                (s.a. `mman_kernel_lockop()' and `mlockop_callback_t') */
PUBLIC WUNUSED NOBLOCK_IF(flags & GFP_ATOMIC) struct mlockop *
NOTHROW(FCALL mman_unmap_kram_locked_ex)(PAGEDIR_PAGEALIGNED void *addr,
                                         PAGEDIR_PAGEALIGNED size_t num_bytes,
                                         gfp_t flags) {
	byte_t *maxaddr;
	assert(mman_lock_acquired(&mman_kernel));
	assert(num_bytes != 0);
	assert(IS_ALIGNED((uintptr_t)addr, PAGESIZE));
	assert(IS_ALIGNED(num_bytes, PAGESIZE));
	assert(flags & GFP_ATOMIC);
	maxaddr = (byte_t *)addr + num_bytes - 1;
	for (;;) {
		struct mnode *node;
		struct mpart *part;
		byte_t *unmap_minaddr;
		byte_t *unmap_maxaddr;
		size_t unmap_size;

		node = mnode_tree_locate(mman_kernel.mm_mappings, addr);
		assertf(node != NULL, "Address %p not mapped", addr);
		assert(mnode_getminaddr(node) >= addr);
		assert(mnode_getmaxaddr(node) <= addr);
		if unlikely(node->mn_flags & MNODE_F_KERNPART) {
			kernel_panic("Attempted to unmap kernel part at %p-%p (via unmap-kram %p-%p)",
			             mnode_getminaddr(node), mnode_getmaxaddr(node), addr, maxaddr);
		}
		assert(node->mn_mman == &mman_kernel);
		assert(node->mn_flags & MNODE_F_PREAD);
		assert(node->mn_flags & MNODE_F_PWRITE);
		assert(mnode_iskern(node));
		part = node->mn_part;
		assert(part);
		assert(part->mp_flags & MPART_F_NO_GLOBAL_REF);
		if (node->mn_flags & MNODE_F_SHARED) {
			assert(LIST_EMPTY(&part->mp_share));
			assert(LIST_FIRST(&part->mp_copy) == node);
		} else {
			assert(LIST_EMPTY(&part->mp_copy));
			assert(LIST_FIRST(&part->mp_share) == node);
		}
		assert(LIST_NEXT(node, mn_link) == NULL);
		assert(mfile_isanon(part->mp_file));
#ifdef MPART_ST_VIO
		assert(part->mp_state != MPART_ST_VIO);
#endif /* MPART_ST_VIO */

		/* In order to unmap a sub-segment of a hinted mem-node, the following must be done:
		 *  - Because hinted mem-nodes cannot be split (only truncated),
		 *    we must first see how many pages reside on the upper end
		 *    of the sub-segment to-be unmapped.
		 *  - We must always chose the upper end because we must eventually
		 *    truncate the associated mem-part's `mp_blkst_ptr' vector, though
		 *    we cannot modify its base-pointer, or move around its elements.
		 *    NOTE: The same goes for the `mp_mem_sc.ms_v' vector.
		 *    This restriction must be in place, since the page-fault handler
		 *    doesn't acquire any sort of lock before accessing such a component,
		 *    relying purely on the assumption that the kernel won't try to
		 *    unmap its own private memory, whilst still using said memory.
		 *  - We then ensure that all pages above the unmapped segment have been
		 *    initialized in kernel memory (this is guarantied to be NOEXCEPT
		 *    because hinted memory in kernel-space is always pre-allocated,
		 *    and always has initializers that don't throw any exceptions)
		 *    A type of initializer like this would usually only `memset()'
		 *    or `mempat()' new memory for either debugging or `calloc()'
		 *  - Once that is done, we know that everything above the sub-segment
		 *    to-be unmapped has been allocated, and consequently no longer
		 *    represents hinted memory (the page directory contains the actual
		 *    memory mapping, rather than a hint as to how to initialize it).
		 *    Because of this, we can proceed to replace the upper sub-segment
		 *    with a new mman node/part pair, before moving on to truncate
		 *    the original (and still hinted) base node to end where the
		 *    unmapped sub-segment ends.
		 *
		 * Before:
		 * /--mpart at 0xc1234567
		 * [HINTEDHINTEDHINTEDHINTEDHINTEDHINTEDHINTEDHINTEDHINTEDHINTEDHINTED]
		 *              |-- Unmap this part ---|
		 *
		 * NOTE:     There would normally be a race condition right here:
		 *           Before we're allowed to truncate the `Before' node, we must still
		 *           ensure that no other CPU is currently inside of the #PF handler,
		 *           an in the progress of mapping the same high-region which we've
		 *           already faulted at that point. (though since that other CPU may
		 *           have started its #PF before we already did it's job for it, it
		 *           may still be trying to access `node')
		 * Solution: We need a global in-use counter `mman_kernel_hintinit_inuse' that
		 *           tracks how many CPUs are currently initializing HINTED nodes.
		 *           The counter is incremented before the first access to the actually
		 *           hinted node, and decremented once initialization has completed.
		 *
		 * After:
		 * /--mpart at 0xc1234567              /--mpart at 0xc7654321
		 * [HINTEDHINTED]                      [USABLEUSABLEUSABLEUSABLEUSABLE]
		 *              |-- Unmap this part ---|
		 *
		 * Note that the upper part is entirely new, and no longer represents
		 * hinted memory, while the lower part still is the same mpart, but
		 * has been truncated!
		 *
		 * HINTED: Allocated, but initialized memory (initialize on first access)
		 * USABLE: Fully initialized memory
		 */

		/* Figure out the actual bounds which we wish to unmap. */
		unmap_minaddr = (byte_t *)addr;
		unmap_maxaddr = maxaddr;
		if (unmap_minaddr > (byte_t *)mnode_getminaddr(node))
			unmap_minaddr = (byte_t *)mnode_getminaddr(node);
		if (unmap_maxaddr < (byte_t *)mnode_getmaxaddr(node))
			unmap_maxaddr = (byte_t *)mnode_getmaxaddr(node);
		unmap_size = (size_t)(unmap_maxaddr - unmap_minaddr) + 1;

#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
		/* Make sure that the (accessed) address range has been prepared. */
		if (!(node->mn_flags & MNODE_F_MPREPARED)) {
			if (!pagedir_prepare_map(unmap_minaddr, unmap_size))
				goto failed;
			ATOMIC_OR(node->mn_flags, MNODE_F_MPREPARED);
		}
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

		/* Check for simple case: unmap a node as a whole. */
		if (unmap_minaddr == mnode_getminaddr(node) &&
		    unmap_maxaddr == mnode_getmaxaddr(node)) {
			mnode_tree_removenode(&mman_kernel.mm_mappings, node);
			ATOMIC_OR(node->mn_flags, MNODE_F_UNMAPPED);

			/* Unmap the affected address range & sync in every mman. */
			unmap_and_unprepare_and_sync_memory(unmap_minaddr, unmap_size);

			/* Just delete the node as a whole! */
			mnode_destroy_kram(node);
			goto continue_nextpart;
		}

		/* In order to do this unmap, we'll have to split the node.
		 * Check if we're allowed to do this. */
		if unlikely((node->mn_flags & MNODE_F_NO_SPLIT) ||
		            (part->mp_flags & MPART_F_NO_SPLIT)) {
			/* Not allowed... (keep on re-attempting the unmap in hopes
			 * that `_mman_lockops_reap()' will join us together with
			 * another unmap request, which then allows the node as a
			 * whole to be unmapped). */
			if (maxaddr > unmap_maxaddr) {
				/* XXX: We could still try to unmap memory further above */
			}
			goto failed;
		}

		/* We'll need to somehow split the part, meaning that we'll be
		 * needing to acquire a lock to said part! */
		if (!mpart_lock_tryacquire(part)) {
			struct mpart_lockop_truncate *lop;
			/* Try to do the truncate later... */
			lop = (struct mpart_lockop_truncate *)unmap_minaddr;
			lop->mplo_func   = &mpart_lockop_truncate_cb;
			lop->mplot_size  = unmap_size;
			lop->mplot_flags = flags & GFP_CALLOC;
			if (mpart_lockop_insert_or_lock(part, lop))
				goto continue_nextpart;
			if (flags & GFP_CALLOC)
				memset(lop, 0, sizeof(*lop));
		}

		/* At this point, we've got a lock to the part, so try to unmap it! */
		{
			bool unmap_ok;
			incref(part);
			unmap_ok = mman_unmap_mpart_subregion(node, part,
			                                      unmap_minaddr,
			                                      unmap_maxaddr,
			                                      flags);
			mpart_lock_release(part);
			decref_unlikely(part);
			if (!unmap_ok)
				goto failed;
		}

		/* Continue after the successfully unmapped address range. */
continue_nextpart:
		addr = unmap_maxaddr + 1;
		if (addr > maxaddr)
			break;
	}
	return NULL;
	{
		struct mlockop_kram *mlo;
failed:
		mlo = (struct mlockop_kram *)addr;
		mlo->mlo_func          = &mlockop_kram_cb;
		mlo->mlo_link.sle_next = NULL; /* Only a single element. */
		mlo->lkr_size          = (size_t)(maxaddr - (byte_t *)addr) + 1;
		mlo->lkr_flags         = flags & GFP_CALLOC;
		return mlo;
	}

}

/* Same as `mman_unmap_kram_locked_ex()', but automatically enqueue a
 * possibly returned mlockop object into the kernel mman. */
PUBLIC NOBLOCK void
NOTHROW(FCALL mman_unmap_kram_locked)(PAGEDIR_PAGEALIGNED void *addr,
                                      PAGEDIR_PAGEALIGNED size_t num_bytes,
                                      gfp_t flags) {
	struct mlockop *lop;
	lop = mman_unmap_kram_locked_ex(addr, num_bytes, flags);
	if (lop != NULL)
		mman_kernel_lockop(lop);
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MM_KRAM_UNMAP_C */
