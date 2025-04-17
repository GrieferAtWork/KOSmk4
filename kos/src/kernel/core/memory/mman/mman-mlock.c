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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_MLOCK_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_MLOCK_C 1

#include <kernel/compiler.h>

#include <kernel/mman.h>
#include <kernel/mman/fault.h>
#include <kernel/mman/mlock.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/rangelock.h>
#include <kernel/paging.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>
#include <hybrid/sequence/list.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/types.h>

#include <assert.h>
#include <atomic.h>
#include <stddef.h>

DECL_BEGIN


/* Helpers for blocking range-lock acquisition, as well as a number
 * of extended operations to-be performed prior to actually locking
 * backing mem-parts:
 * >>    struct mrangelock rl;
 * >>again:
 * >>    mman_lock_acquire(self);
 * >>    mrangelock_aq_init(&rl, self, minaddr, maxaddr);
 * >>    if (!mrangelock_aq_continuous_or_unlock(&rl, self, minaddr, maxaddr))
 * >>        goto again;
 * >>    if (!mrangelock_aq_splitnodes_or_unlock(&rl, minaddr, maxaddr))
 * >>        goto again;
 * >>    if (!mrangelock_aq_lockparts_or_unlock(&rl))
 * >>        goto again;
 * >>    ...
 * >>    mrangelock_release(&rl);
 * >>    mman_lock_release(self);
 */

/* Initialize `self' for the given address range. */
#define mrangelock_aq_init(self, mm, minaddr, maxaddr) \
	mman_mappings_minmaxlocate(mm, minaddr, maxaddr, &(self)->mrl_nodes)

/* Ensure that the given address  range is a continuous mapping.  If
 * this isn't the case, release locks and throw E_SEGFAULT_UNMAPPED. */
#define mrangelock_aq_continuous_or_unlock(...) (mrangelock_aq_continuous_or_unlock(__VA_ARGS__), 1)
PRIVATE NONNULL((1)) void
(FCALL mrangelock_aq_continuous_or_unlock)(struct mrangelock *__restrict self,
                                           struct mman *__restrict mm,
                                           void const *minaddr, void const *maxaddr)
		THROWS(E_SEGFAULT) {
	struct mnode *node;
	if unlikely(!self->mrl_nodes.mm_min)
		goto err_minaddr_is_unmapped;

	/* Check the leading node. */
	if unlikely((byte_t const *)minaddr <
	            (byte_t const *)mnode_getminaddr(self->mrl_nodes.mm_min)) {
		assert(self->mrl_nodes.mm_min->mn_mman == mm);
err_minaddr_is_unmapped:
		mman_lock_release(mm);
		THROW(E_SEGFAULT_UNMAPPED, minaddr, E_SEGFAULT_CONTEXT_FAULT);
	}

	/* Check intermediate nodes for linear consistency. */
	for (node = self->mrl_nodes.mm_min;;) {
		void const *expected_addr;
		assert(node->mn_mman == mm);
		if (node == self->mrl_nodes.mm_max)
			break;
		expected_addr = mnode_getendaddr(node);
		node          = mnode_tree_nextnode(node);
		assert(node);
		if unlikely(expected_addr != mnode_getaddr(node)) {
			mman_lock_release(mm);
			THROW(E_SEGFAULT_UNMAPPED, expected_addr, E_SEGFAULT_CONTEXT_FAULT);
		}
	}

	/* Check the trailing node. */
	if unlikely((byte_t const *)maxaddr >
	            (byte_t const *)mnode_getmaxaddr(self->mrl_nodes.mm_max)) {
		void const *endaddr;
		endaddr = mnode_getendaddr(self->mrl_nodes.mm_max);
		mman_lock_release(mm);
		THROW(E_SEGFAULT_UNMAPPED, endaddr, E_SEGFAULT_CONTEXT_FAULT);
	}
}



/* Split border mem-nodes to match the given range more closely. */
PRIVATE WUNUSED NONNULL((1)) bool FCALL
mrangelock_aq_splitnodes_or_unlock(struct mrangelock *__restrict self,
                                   struct mman *__restrict mm,
                                   void const *minaddr, void const *maxaddr,
                                   mrangelock_filter_cb_t filter)
		THROWS(E_BADALLOC) {
	if likely(self->mrl_nodes.mm_min) {
		if ((byte_t const *)minaddr > (byte_t const *)mnode_getminaddr(self->mrl_nodes.mm_min) &&
		    (*filter)(NULL, self->mrl_nodes.mm_min)) {
			if unlikely(!mnode_split_or_unlock(mm, self->mrl_nodes.mm_min, minaddr))
				goto fail;
			mman_mappings_minmaxlocate(mm, minaddr, maxaddr, &self->mrl_nodes);
		}
		if ((byte_t const *)maxaddr < (byte_t const *)mnode_getmaxaddr(self->mrl_nodes.mm_max) &&
		    (*filter)(NULL, self->mrl_nodes.mm_max)) {
			if unlikely(!mnode_split_or_unlock(mm, self->mrl_nodes.mm_max, (byte_t const *)maxaddr + 1))
				goto fail;
			mman_mappings_minmaxlocate(mm, minaddr, maxaddr, &self->mrl_nodes);
		}
	}
	return true;
fail:
	return false;
}


/* Acquire locks to every unique mem-part within the given mem-range.
 * If this can't be done, unlock everything and wait for the blocking
 * mem-part to become available. */
PRIVATE WUNUSED NONNULL((1, 2)) bool FCALL
mrangelock_aq_lockparts_or_unlock(struct mrangelock *__restrict self,
                                  struct mman *__restrict mm,
                                  mrangelock_filter_cb_t filter)
		THROWS(E_WOULDBLOCK) {
	struct mpart *blocking_part;
	if unlikely(!self->mrl_nodes.mm_min)
		return true;

	/* Actually lock all of the unique mem-parts. */
	blocking_part = _mrangelock_tryacquire(self, filter);
	if unlikely(blocking_part) {
		/* Block until this part becomes available. */
		incref(blocking_part);
		mman_lock_release(mm);
		FINALLY_DECREF_UNLIKELY(blocking_part);
		mpart_lock_waitfor(blocking_part);
		goto fail;
	}

	/* Success! */
	return true;
fail:
	return false;
}




PRIVATE NOBLOCK ATTR_PURE NONNULL((2)) bool
NOTHROW(FCALL mlock_rangelock_filter)(void *UNUSED(arg),
                                      struct mnode *__restrict node) {
	/* We only care for nodes that aren't already MLOCK'd */
	return (node->mn_flags & MNODE_F_MLOCK) == 0;
}

PRIVATE NOBLOCK ATTR_PURE NONNULL((2)) bool
NOTHROW(FCALL munlock_rangelock_filter)(void *UNUSED(arg),
                                        struct mnode *__restrict node) {
	/* We  only care for  nodes that actually have  the MLOCK flag set.
	 * Nodes that don't have this flag set we don't care about, meaning
	 * that the caller doesn't need to bother locking their parts! */
	return (node->mn_flags & MNODE_F_MLOCK) != 0;
}





/* Set the `MNODE_F_MLOCK' flag for  all mem-nodes within the  given
 * address range, and potentially pre-populate all nodes within said
 * range for immediate use.
 * @param: flags: Set of `MLOCK_NOW | MLOCK_ONFAULT | MLOCK_IFMAPPED'
 * @throws: *:E_INVALID_ARGUMENT_CONTEXT_MLOCK_SIZE: [...]
 * @throws: E_SEGFAULT_UNMAPPED: When `MLOCK_IFMAPPED' isn't given, this exception is
 *                               thrown for the first address of the given range that
 *                               isn't  mapped. When this  happens, no mem-nodes will
 *                               have had their MLOCK-state altered. */
PUBLIC BLOCKING_IF(!(flags & MLOCK_ONFAULT)) NONNULL((1)) void FCALL
mman_mlock(struct mman *__restrict self, void const *addr,
           size_t num_bytes, unsigned int flags)
		THROWS(E_INVALID_ARGUMENT_BAD_VALUE, E_SEGFAULT_UNMAPPED, E_BADALLOC, ...) {
	struct mrangelock rl;
	byte_t const *minaddr, *maxaddr;
	minaddr = (byte_t const *)addr;
	if unlikely(OVERFLOW_UADD((uintptr_t)minaddr, num_bytes - 1,
	                          (uintptr_t *)&maxaddr)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_MLOCK_SIZE,
		      num_bytes);
	}
	/* Align address bounds to whole pages. */
	minaddr = (byte_t const *)FLOOR_ALIGN((uintptr_t)minaddr, PAGESIZE);
	maxaddr = (byte_t const *)(CEIL_ALIGN((uintptr_t)maxaddr + 1, PAGESIZE) - 1);
again:
	/* Acquire locks... */
	if (flags & MLOCK_ONFAULT) {
again_no_prefault:
		mman_lock_acquire(self);
		mrangelock_aq_init(&rl, self, minaddr, maxaddr);

		/* If need be, ensure that the range is complete. */
		if (!(flags & MLOCK_IFMAPPED) &&
		    !mrangelock_aq_continuous_or_unlock(&rl, self, minaddr, maxaddr))
			goto again_no_prefault;
	} else {
		struct mfault mf;
		__mfault_init(&mf);
		RAII_FINALLY { mfault_fini(&mf); };
again_prefault:
		/* Go over all nodes within the given address range, and
		 * trigger a read-fault for  all read-only nodes, and  a
		 * write-fault for all read/write ones.
		 * This  way, and because we're currently holding locks
		 * to everything that can somehow affect how/when stuff
		 * gets to be MLOCK'd /  MUNLOCK'd, all of these  nodes
		 * will still be locked into memory once we get  around
		 * to actually setting the MLOCK flags below! */
		mman_lock_acquire(self);

		/* Load the requested address range. */
		mrangelock_aq_init(&rl, self, minaddr, maxaddr);

		/* If need be, ensure that the range is complete. */
		if (!(flags & MLOCK_IFMAPPED) &&
		    !mrangelock_aq_continuous_or_unlock(&rl, self, minaddr, maxaddr))
			goto again_prefault;

		if likely(rl.mrl_nodes.mm_min) {
			do {
				pagedir_prot_t prot;
				byte_t const *fault_minaddr, *fault_maxaddr;
				fault_minaddr = (byte_t const *)mnode_getminaddr(rl.mrl_nodes.mm_min);
				fault_maxaddr = (byte_t const *)mnode_getmaxaddr(rl.mrl_nodes.mm_min);
				if (fault_minaddr < minaddr)
					fault_minaddr = minaddr;
				if (fault_maxaddr > maxaddr)
					fault_maxaddr = maxaddr;

				/* If there is a backing part to this node, then fault it! */
				if ((mf.mfl_part = rl.mrl_nodes.mm_min->mn_part) != NULL) {
					mf.mfl_mman  = self;
					mf.mfl_addr  = (void *)fault_minaddr;
					mf.mfl_size  = (size_t)(fault_maxaddr - fault_minaddr) + 1;
					mf.mfl_flags = MMAN_FAULT_F_NORMAL;
					mf.mfl_node  = rl.mrl_nodes.mm_min;
					if (rl.mrl_nodes.mm_min->mn_flags & MNODE_F_PWRITE)
						mf.mfl_flags = MMAN_FAULT_F_NORMAL | MMAN_FAULT_F_WRITE;

					/* Fault this node. */
					if (!mfault_lockpart_or_unlock(&mf))
						goto again_prefault;

					/* NOTE: Because  we only ever  fault for reading (`mf.mfl_flags = MMAN_FAULT_F_NORMAL'),
					 *       we don't have to worry about `mfault_or_unlock()' throwing `E_FSERROR_READONLY'! */
					if (!mfault_or_unlock(&mf))
						goto again_prefault;

					/* Re-initialize internal fields  of the memfault  controller.
					 * A successful call  to `mfault_or_unlock()' normally  leaves
					 * these fields in an undefined state, such that `mfault_fini'
					 * doesn't normally have to be called in this case.
					 *
					 * However, because we may need to use the  fault-controller
					 * once again, and because we're still inside a RAII_FINALLY
					 * block that will call  `mfault_fini()' if an exception  is
					 * thrown, we have to re-initialize to ensure consistency! */
					__mfault_init(&mf);

					/* Re-map the freshly faulted memory. */
					if unlikely(mf.mfl_node->mn_flags & MNODE_F_MPREPARED) {
						prot = mpart_mmap_node_p(mf.mfl_part, self->mm_pagedir_p,
						                         mf.mfl_addr, mf.mfl_size,
						                         mf.mfl_offs, mf.mfl_node);
					} else {
						if unlikely(!pagedir_prepare_p(self->mm_pagedir_p, mf.mfl_addr, mf.mfl_size)) {
							mpart_lock_release(mf.mfl_part);
							mman_lock_release(self);
							THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
						}
						prot = mpart_mmap_node_p(mf.mfl_part, self->mm_pagedir_p,
						                         mf.mfl_addr, mf.mfl_size,
						                         mf.mfl_offs, mf.mfl_node);
						pagedir_unprepare_p(self->mm_pagedir_p, mf.mfl_addr, mf.mfl_size);
					}

					/* Upon success, `mfault_lockpart_or_unlock()' will have  acquired
					 * a lock to the associated part. We will actually be needing this
					 * lock later, and we will re-acquire it at that point.
					 *
					 * But  until then, our lock to `self' will prevent the now-faulted
					 * backing data of `mf.mfl_part'  from being unloaded again,  since
					 * anyone trying to do so would have to acquire our mman-lock first
					 * (which we won't release until after we've re-acquired the  part-
					 * lock if everything goes to plan) */
					mpart_lock_release(mf.mfl_part);

					/* If write-access was granted, add the node to the list of writable nodes. */
					if ((prot & PAGEDIR_PROT_WRITE) && !LIST_ISBOUND(mf.mfl_node, mn_writable))
					    LIST_INSERT_HEAD(&self->mm_writable, mf.mfl_node, mn_writable);
				}

				/* If we've gone through  all nodes within the  requested
				 * address range (and all of them have now been faulted),
				 * then we can stop trying to search for more nodes. */
				if (fault_maxaddr >= maxaddr)
					break;

				/* Find the next-greater node above `fault_maxaddr' */
				mman_mappings_minmaxlocate(self, fault_maxaddr + 1,
				                           maxaddr, &rl.mrl_nodes);
			} while (rl.mrl_nodes.mm_min);

			/* Because the actual node distribution may have changed
			 * while we were faulting memory above, we must  re-load
			 * the range of nodes with which we wish to work! */
			mman_mappings_minmaxlocate(self, minaddr, maxaddr, &rl.mrl_nodes);
		}
	}

	/* Split mem-nodes if necessary. */
	if (!mrangelock_aq_splitnodes_or_unlock(&rl, self, minaddr, maxaddr, &mlock_rangelock_filter))
		goto again;

	/* Actually acquire part locks. */
	if (!mrangelock_aq_lockparts_or_unlock(&rl, self, &mlock_rangelock_filter))
		goto again;

	/* Go over all nodes within the given range. */
	if likely(rl.mrl_nodes.mm_min) {
		struct mnode *node;
		for (node = rl.mrl_nodes.mm_min;;) {
			if (!(node->mn_flags & MNODE_F_MLOCK)) {
				struct mpart *part;
				/* Set the MLOCK flag. */
				atomic_or(&node->mn_flags, MNODE_F_MLOCK);
				if ((part = node->mn_part) != NULL) {
					assert(mpart_lock_acquired(part));
					/* If the mem-part isn't marked as MLOCK'd, and the MLOCK
					 * flag isn't frozen, then set it now, since the part now
					 * has at least 1 mapping that's supposed to be locked. */
					if ((part->mp_flags & (MPART_F_MLOCK | MPART_F_MLOCK_FROZEN)) == 0)
						atomic_or(&part->mp_flags, MPART_F_MLOCK);
				}
			}
			if (node == rl.mrl_nodes.mm_max)
				break;
			node = mnode_tree_nextnode(node);
			assert(node);
		}
	}

	/* Release part locks. */
	mrangelock_release(&rl);

	/* Try to merge nodes. */
	mman_mergenodes_inrange(self, minaddr, maxaddr);

	/* Release the mman-lock. */
	mman_lock_release(self);
}


INTDEF NOBLOCK NONNULL((1)) void /* from "mnode.c" */
NOTHROW(FCALL mpart_maybe_clear_mlock)(struct mpart *__restrict self);

/* Clear the `MNODE_F_MLOCK' flag for all mem-nodes within the given address range.
 * @param: flags: Set of `0 | MLOCK_IFMAPPED'
 * @throws: *:E_INVALID_ARGUMENT_CONTEXT_MUNLOCK_SIZE: [...]
 * @throws: E_SEGFAULT_UNMAPPED: When `MLOCK_IFMAPPED' isn't given, this exception is
 *                               thrown for the first address of the given range that
 *                               isn't  mapped. When this  happens, no mem-nodes will
 *                               have had their MLOCK-state altered. */
PUBLIC NONNULL((1)) void FCALL
mman_munlock(struct mman *__restrict self, void const *addr,
             size_t num_bytes, unsigned int flags)
		THROWS(E_INVALID_ARGUMENT_BAD_VALUE, E_SEGFAULT_UNMAPPED, E_BADALLOC) {
	struct mrangelock rl;
	byte_t const *minaddr, *maxaddr;
	minaddr = (byte_t const *)addr;
	if unlikely(OVERFLOW_UADD((uintptr_t)minaddr, num_bytes - 1,
	                          (uintptr_t *)&maxaddr)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_MUNLOCK_SIZE,
		      num_bytes);
	}

	/* Align address bounds to whole pages. */
	minaddr = (byte_t const *)FLOOR_ALIGN((uintptr_t)minaddr, PAGESIZE);
	maxaddr = (byte_t const *)(CEIL_ALIGN((uintptr_t)maxaddr + 1, PAGESIZE) - 1);

	/* Acquire locks... */
again:
	mman_lock_acquire(self);
	mrangelock_aq_init(&rl, self, minaddr, maxaddr);
	if (!(flags & MLOCK_IFMAPPED) &&
	    !mrangelock_aq_continuous_or_unlock(&rl, self, minaddr, maxaddr))
		goto again;

	/* Split mem-nodes if necessary. */
	if (!mrangelock_aq_splitnodes_or_unlock(&rl, self, minaddr, maxaddr, &munlock_rangelock_filter))
		goto again;

	/* Actually acquire part locks. */
	if (!mrangelock_aq_lockparts_or_unlock(&rl, self, &munlock_rangelock_filter))
		goto again;

	/* Go over all nodes within the given range. */
	if likely(rl.mrl_nodes.mm_min) {
		struct mnode *node;
		for (node = rl.mrl_nodes.mm_min;;) {
			if (node->mn_flags & MNODE_F_MLOCK) {
				struct mpart *part;
				atomic_and(&node->mn_flags, ~MNODE_F_MLOCK);
				if ((part = node->mn_part) != NULL) {
					assert(mpart_lock_acquired(part));
					/* If  the mem-part is marked as MLOCK'd, and that flag isn't
					 * frozen, then try to unset it if none of its mem-nodes have
					 * their MLOCK flags set anymore. */
					if ((part->mp_flags & (MPART_F_MLOCK | MPART_F_MLOCK_FROZEN)) == MPART_F_MLOCK)
						mpart_maybe_clear_mlock(part);
				}
			}
			if (node == rl.mrl_nodes.mm_max)
				break;
			node = mnode_tree_nextnode(node);
			assert(node);
		}
	}

	/* Release part locks. */
	mrangelock_release(&rl);

	/* Try to merge nodes. */
	mman_mergenodes_inrange(self, minaddr, maxaddr);

	/* Release the mman-lock. */
	mman_lock_release(self);
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_MLOCK_C */
