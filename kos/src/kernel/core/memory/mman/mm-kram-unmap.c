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

#include <kernel/mman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mm-kram.h>
#include <kernel/mman/mm-lockop.h>
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

STATIC_ASSERT_MSG(GFP_ATOMIC == 0x0400,
                  "This is currently hard-coded in "
                  "<kernel/mman/mm-map.h> and "
                  "<kernel/mman/mm-lockop.h>");

#ifndef CONFIG_NO_SMP
/* Atomic counter for how many CPUs are currently initializing hinted pages (s.a. `MNODE_F_MHINT').
 * This counter behaves similar to the in-use counter found in ATOMIC_REF, and is needed in order
 * to allow for syncing of internal re-trace operations in `mman_unmap_kernel_ram_locked()' with
 * other CPUs having previously started initializing hinted pages.
 *
 * For more information on the data race solved by this counter, see the detailed explaination
 * of `mman_kernel_hintinit_inuse' within `mman_unmap_kernel_ram_locked()' */
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
	return mman_unmap_kernel_ram_locked(self, size, flags);
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
NOTHROW(FCALL mman_unmap_kernel_ram)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
                                     PAGEDIR_PAGEALIGNED size_t num_bytes,
                                     gfp_t flags) {
	struct mlockop_kram *lockop;
	assert(num_bytes != 0);
	assert(IS_ALIGNED((uintptr_t)addr, PAGESIZE));
	assert(IS_ALIGNED(num_bytes, PAGESIZE));
	assert(flags & GFP_ATOMIC);
	if (mman_lock_tryacquire(&mman_kernel)) {
		/* Directly try to unmap kernel ram. */
		lockop = (struct mlockop_kram *)mman_unmap_kernel_ram_locked(addr, num_bytes, flags);
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

/* Try to unmap kernel raw while the caller is holding a lock to the kernel mman.
 * @param: flags: Set of `GFP_*'
 * @return: NULL: Successfully unmapped kernel ram.
 * @return: * :   Failed to allocate needed memory.
 *                The returned value is a freshly initialized pending mman-
 *                lock-operation which the caller must enqueue for execution.
 *                (s.a. `mman_kernel_lockop()' and `mlockop_callback_t') */
PUBLIC WUNUSED NOBLOCK_IF(flags & GFP_ATOMIC) struct mlockop *
NOTHROW(FCALL mman_unmap_kernel_ram_locked)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
                                            PAGEDIR_PAGEALIGNED size_t num_bytes,
                                            gfp_t flags) {
	struct mnode *node;
	assert(mman_lock_acquired(&mman_kernel));
	assert(num_bytes != 0);
	assert(IS_ALIGNED((uintptr_t)addr, PAGESIZE));
	assert(IS_ALIGNED(num_bytes, PAGESIZE));
	assert(flags & GFP_ATOMIC);
	for (;;) {
		node = mnode_tree_locate(mman_kernel.mm_mappings, addr);
		assertf(node != NULL, "Address %p not mapped", addr);
		assert(mnode_getminaddr(node) >= addr);
		assert(mnode_getmaxaddr(node) <= addr);
		if unlikely(node->mn_flags & MNODE_F_KERNPART) {
			kernel_panic("Attempted to unmap kernel part at %p-%p (via unmap-kram %p-%p)",
			             mnode_getminaddr(node), mnode_getmaxaddr(node),
			             addr, (byte_t *)addr + num_bytes - 1);
		}
		assert(node->mn_flags & MNODE_F_PREAD);
		assert(node->mn_flags & MNODE_F_PWRITE);
		assert(node->mn_flags & MNODE_F_SHARED);
		assert(mnode_iskern(node));
		assert(node->mn_part);
		assert(node->mn_part->mp_flags & MPART_F_NO_GLOBAL_REF);
		assert(LIST_EMPTY(&node->mn_part->mp_copy));
		assert(LIST_FIRST(&node->mn_part->mp_share) == node);
		assert(LIST_NEXT(node, mn_link) == NULL);
		assert(mfile_isanon(node->mn_part->mp_file));
#ifdef MPART_ST_VIO
		assert(node->mn_part->mp_state != MPART_ST_VIO);
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


		if (mnode_getminaddr(node) != addr) {
			/* TODO */
		}

		/* TODO */
		goto failed;
	}

	return NULL;
	{
		struct mlockop_kram *mlo;
failed:
		mlo = (struct mlockop_kram *)addr;
		mlo->mlo_func          = &mlockop_kram_cb;
		mlo->mlo_link.sle_next = NULL; /* Only a single element. */
		mlo->lkr_size          = num_bytes;
		mlo->lkr_flags         = flags & GFP_CALLOC;
		return mlo;
	}

}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MM_KRAM_UNMAP_C */
