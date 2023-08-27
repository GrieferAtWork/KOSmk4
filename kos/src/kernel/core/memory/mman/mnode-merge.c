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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MNODE_MERGE_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MNODE_MERGE_C 1
#define __WANT_MPART__mp_nodlsts
#define __WANT_MPART__mp_dtplop
#define __WANT_MPART__mp_dead
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/path.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/module.h>
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/mpartmeta.h>
#include <kernel/printk.h>

#include <kos/lockop.h>

#include <assert.h>
#include <atomic.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/*[[[config CONFIG_HAVE_KERNEL_MNODE_MERGE = true]]]*/
#ifdef CONFIG_NO_KERNEL_MNODE_MERGE
#undef CONFIG_HAVE_KERNEL_MNODE_MERGE
#elif !defined(CONFIG_HAVE_KERNEL_MNODE_MERGE)
#define CONFIG_HAVE_KERNEL_MNODE_MERGE
#elif (-CONFIG_HAVE_KERNEL_MNODE_MERGE - 1) == -1
#undef CONFIG_HAVE_KERNEL_MNODE_MERGE
#define CONFIG_NO_KERNEL_MNODE_MERGE
#endif /* ... */
/*[[[end]]]*/

DECL_BEGIN

#ifdef CONFIG_HAVE_KERNEL_MNODE_MERGE

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Check if 2 range overlap. */
#define RANGES_OVERLAP(r1_min, r1_max, r2_min, r2_max) \
	((r1_max) >= (r2_min) && (r2_max) >= (r1_min))


/* Mask  of flags that must be shared  between 2 nodes for them to
 * be mergeable. Note  that the MNODE_F_NOMERGE  flag is apart  of
 * this mask, since neither node should have it set, and by making
 * sure that this flag has the same state for both nodes, it  will
 * be sufficient to  only ensure  that 1  of the  2 nodes  doesn't
 * have said flag set! (!a && (a == b) --> !b) */
#define MNODE_F_MERGEMASK                                \
	(MNODE_F_PMASK | MNODE_F_SHARED | MNODE_F_UNMAPPED | \
	 MNODE_F_KERNPART | MNODE_F_MHINT | MNODE_F_MLOCK |  \
	 MNODE_F_NOSPLIT | MNODE_F_NOMERGE | MNODE_F_NOCORE)

/* Like `MNODE_F_MERGEMASK', but for `struct mpart::mp_flags' */
#define MPART_F_MERGEMASK \
	(MPART_F_NOFREE | MPART_F_NOSPLIT | MPART_F_NOMERGE | MPART_F_MLOCK_FROZEN)


/* Returns `true' if `self' doesn't have any active DMA  locks.
 * Otherwise, return `false' and set `MPART_XF_MERGE_AFTER_DMA'
 *
 * The same also goes for `MPART_BLOCK_ST_INIT'. */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL mpart_canmerge_chkdma)(struct mpart *__restrict self,
                                     bool locks_held) {
	struct mpartmeta *meta;
	if ((meta = self->mp_meta) != NULL && atomic_read(&meta->mpm_dmalocks) != 0) {
		atomic_or(&self->mp_xflags, MPART_XF_MERGE_AFTER_DMA);
		if (atomic_read(&meta->mpm_dmalocks) != 0)
			return false;
		atomic_and(&self->mp_xflags, ~MPART_XF_MERGE_AFTER_DMA);
	}
	if (atomic_read(&self->mp_flags) & MPART_F_MAYBE_BLK_INIT) {
		bool hasinit;
		if (!locks_held) {
			if (!mpart_lock_tryacquire(self))
				goto done_maybe_blk_init;
		}
		hasinit = mpart_hasblocksstate_init(self);
		if (hasinit) {
			/* Set the merge-after-init flag, then check again. */
			atomic_or(&self->mp_xflags, MPART_XF_MERGE_AFTER_INIT);
			hasinit = mpart_hasblocksstate_init(self);
			if (!hasinit)
				atomic_and(&self->mp_xflags, ~MPART_XF_MERGE_AFTER_INIT);
		}
		if (!locks_held)
			mpart_lock_release(self);
		if (hasinit)
			return false;
	}
done_maybe_blk_init:

	return true;
}


/* Check if 2 given (adjacent) nodes might potentially be mergeable.
 * The caller  must  be  holding  a lock  to  the  associated  mman! */
PRIVATE NOBLOCK WUNUSED NONNULL((1, 2)) bool
NOTHROW(FCALL mnode_canmerge)(struct mnode *lonode,
                              struct mnode *hinode) {
	struct mpart *lopart, *hipart;

	/* Check if the 2 nodes are continuous. */
	if (lonode->mn_maxaddr + 1 != hinode->mn_minaddr)
		goto nope;

	/* Check if node flags are compatible. */
	if ((lonode->mn_flags & MNODE_F_MERGEMASK) !=
	    (hinode->mn_flags & MNODE_F_MERGEMASK))
		goto nope;

	/* Check if either of the 2 nodes requires NOMERGE behavior. */
	if (lonode->mn_flags & (MNODE_F_NOMERGE | MNODE_F_MHINT))
		goto nope;

	/* Check if both nodes reference the same backing module. */
	if (lonode->mn_module != hinode->mn_module)
		goto nope;

	/* Make sure that both nodes have the same filesystem name. */
	if (lonode->mn_fspath != hinode->mn_fspath)
		goto nope;
	if (lonode->mn_fsname != hinode->mn_fsname)
		goto nope;

	/* Check if both nodes have a mem-part, or neither do. */
	if ((lopart = lonode->mn_part) == NULL) {
		if (hinode->mn_part != NULL)
			goto nope;
	} else {
		if ((hipart = hinode->mn_part) == NULL)
			goto nope;

		/* Check if the 2 parts are sequentially consistent. */
		if (atomic_read(&lopart->mp_file) != atomic_read(&hipart->mp_file))
			goto nope;
		if (mpart_isanon_atomic(lopart)) {
			if unlikely(!mpart_isanon_atomic(hipart))
				goto nope;
			if (lopart == hipart) {
				/* If it's the same part, then file-offsets mustn't
				 * overlap. - If they do,  then this mean that  the
				 * same memory is mapped  more than once, and  that
				 * we can't actually merge the 2 parts. */
				if (RANGES_OVERLAP(mnode_getpartminaddr(lonode),
				                   mnode_getpartmaxaddr(lonode),
				                   mnode_getpartminaddr(hinode),
				                   mnode_getpartmaxaddr(hinode)))
					goto nope;
			} else {
				/* For differing anonymous parts, we can simply merge  the
				 * 2 parts in whatever shape is necessary for the merge to
				 * succeed. */
			}
		} else {
			if unlikely(mpart_isanon_atomic(hipart))
				goto nope;
			if (mnode_getfileendaddr(lonode) !=
			    mnode_getfileaddr(hinode))
				goto nope;
		}
		if (lopart != hipart) {
			/* Check if part flags are compatible. */
			if ((lopart->mp_flags & MPART_F_MERGEMASK) !=
			    (hipart->mp_flags & MPART_F_MERGEMASK))
				goto nope;

			/* Check for flags that require special handling. */
			if (lopart->mp_flags & (MPART_F_NOMERGE | MPART_F_MLOCK_FROZEN)) {
				if (lopart->mp_flags & MPART_F_NOMERGE)
					goto nope; /* Not allowed to merge. */
				/* When the MLOCK_FROZEN  flag is set,  then the 2  mem-
				 * parts must also share the same `MPART_F_MLOCK' value! */
				if ((lopart->mp_flags & MPART_F_MLOCK) !=
				    (hipart->mp_flags & MPART_F_MLOCK))
					goto nope;
			}

			/* Merging isn't possible  if either of  the 2 parts  currently
			 * has DMA-locks allocated. If this  is the case, then we  must
			 * set  the MERGE_AFTER_DMA flag  in order to  get the owner of
			 * the DMA-locks to re-attempt the merge once they're all gone. */
			if (!mpart_canmerge_chkdma(lopart, false))
				goto nope;
			if (!mpart_canmerge_chkdma(hipart, false))
				goto nope;
		}
	}
	return true;
nope:
	return false;
}


/* Check if 2 given (adjacent) parts might potentially be mergeable.
 * @param: locks_held: True if locks to `lopart' and `hipart' are held.
 *                     Note  that unless this  argument is `true', this
 *                     function may give false positives! */
PRIVATE NOBLOCK WUNUSED NONNULL((1, 2)) bool
NOTHROW(FCALL mpart_canmerge)(struct mpart *lopart,
                              struct mpart *hipart,
                              bool locks_held) {
	/* Check if the 2 parts reference the same file. */
	if (atomic_read(&lopart->mp_file) != atomic_read(&hipart->mp_file))
		goto nope;

	/* Check if the 2 parts are continuous. */
	if (mpart_isanon_atomic(lopart)) {
		if (!mpart_isanon_atomic(hipart))
			goto nope;
	} else {
		if (mpart_isanon_atomic(hipart))
			goto nope;
		/* In-file positions only matter for non-anonymous parts. */
		if (lopart->mp_maxaddr + 1 != hipart->mp_minaddr)
			goto nope;
	}

	/* Check if part flags are compatible. */
	if ((lopart->mp_flags & MPART_F_MERGEMASK) !=
	    (hipart->mp_flags & MPART_F_MERGEMASK))
		goto nope;

	/* Check for flags that require special handling. */
	if (lopart->mp_flags & (MPART_F_NOMERGE | MPART_F_MLOCK_FROZEN)) {
		if (lopart->mp_flags & MPART_F_NOMERGE)
			goto nope; /* Not allowed to merge. */

		/* When the MLOCK_FROZEN  flag is set,  then the 2  mem-
		 * parts must also share the same `MPART_F_MLOCK' value! */
		if ((lopart->mp_flags & MPART_F_MLOCK) !=
		    (hipart->mp_flags & MPART_F_MLOCK))
			goto nope;
	}

	/* Merging isn't possible  if either of  the 2 parts  currently
	 * has DMA-locks allocated. If this  is the case, then we  must
	 * set  the MERGE_AFTER_DMA flag  in order to  get the owner of
	 * the DMA-locks to re-attempt the merge once they're all gone. */
	if (!mpart_canmerge_chkdma(lopart, locks_held))
		goto nope;
	if (!mpart_canmerge_chkdma(hipart, locks_held))
		goto nope;

	/* The combined size of the 2 parts (as would be the result if
	 * we _did_ end up merging them) mustn't exceed what fits into
	 * a `size_t'! */
#if __SIZEOF_POS_T__ > __SIZEOF_SIZE_T__
	{
		pos_t losize, hisize;
		losize = (lopart->mp_maxaddr - lopart->mp_minaddr) + 1;
		hisize = (hipart->mp_maxaddr - hipart->mp_minaddr) + 1;
		if unlikely((losize + hisize) > (pos_t)SIZE_MAX)
			goto nope;
	}
#endif /* __SIZEOF_POS_T__ > __SIZEOF_SIZE_T__ */

	return true;
nope:
	return false;
}



/* Check if `self' has a neighbor with which it should be merged.
 * The caller  must be  holding a  lock to  the associated  mman! */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL mnode_shouldmerge)(struct mnode *__restrict self) {
	struct mnode *neighbor;
	if ((neighbor = mnode_tree_prevnode(self)) != NULL && mnode_canmerge(neighbor, self))
		return true;
	if ((neighbor = mnode_tree_nextnode(self)) != NULL && mnode_canmerge(self, neighbor))
		return true;
	return false;

}




/* Allowed values/states for `thismman_mergenodes_lop.mml_mm_lop.olo_func':
 *   INITIAL  --> MERGENODES_LOP_FUNC_INACTIVE
 */
#define MERGENODES_LOP_FUNC_INACTIVE       ((Toblockop_callback_t(mman))0) /* No request is pending, or running */
#define MERGENODES_LOP_FUNC_PENDING        (&mergenodes_lop_cb)                   /* Request is pending. */
#define MERGENODES_LOP_FUNC_RUNNING        ((Toblockop_callback_t(mman))1) /* Nodes are being merged right now. */
#define MERGENODES_LOP_FUNC_WAITFOR_MPART  ((Toblockop_callback_t(mman))&mergenode_waitfor_mpart_lop)     /* Waiting for a mem-part */
#define MERGENODES_LOP_FUNC_WAITFOR_MPART2 ((Toblockop_callback_t(mman))&mergenode_waitfor_mpart_postlop) /* *ditto* */

union mman_mergenodes_lop {
	Toblockop(mman)      mml_mm_lop;     /* Lop */
	Tobpostlockop(mman)  mml_mm_postlop; /* Post-Lop */
	Toblockop(mpart)     mml_mp_lop;     /* Lop */
	Tobpostlockop(mpart) mml_mp_postlop; /* Post-Lop */
};

/* A special per-mman lockop may be used to enqueue an async call to `mman_mergenodes()'
 * NOTE: The `olo_func' field of this lockop  carries a special role with  its
 *       meaning, in that it may only be set to one of `MERGENODES_LOP_FUNC_*' */
PRIVATE ATTR_PERMMAN ATTR_ALIGN(union mman_mergenodes_lop)
thismman_mergenodes_lop = { { {}, MERGENODES_LOP_FUNC_INACTIVE } };


PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(mman) *
NOTHROW(FCALL mergenodes_lop_cb)(Toblockop(mman) *__restrict lop,
                                 struct mman *__restrict self) {
	assert(lop == &FORMMAN(self, thismman_mergenodes_lop.mml_mm_lop));

	/* Drop  the reference that `async_mergenodes()' created for
	 * us. Note that we can  use *nokill, because the caller  of
	 * `mman_lockops_reap()' must necessarily be holding another
	 * reference to this same mman! */
	decref_nokill(self);

	/* Indicate that we're now running the async-mergenodes function. */
	atomic_write(&lop->olo_func, MERGENODES_LOP_FUNC_RUNNING);

	/* Merge nodes by use of `mman_mergenodes_locked()', however
	 * if we get into a situation where we need to wait for  the
	 * lock of some mem-part to become available, then halt  the
	 * process of merging mem-nodes and enqueue a lockop on  the
	 * blocking mem-part. Then, from within that lock-op, switch
	 * over  to a post-lockop, from inside of which we must then
	 * call  `mman_mergenodes()' in order  to restart the entire
	 * process of merging nodes. */
	mman_mergenodes_locked(self);

	/* If the mergenodes lop still indicates a normal RUNNING
	 * state, then all nodes that may have been mergeable  at
	 * one point have  now been merged,  meaning that we  can
	 * safely switch back to the initial INACTIVE state. */
	if (lop->olo_func == MERGENODES_LOP_FUNC_RUNNING)
		atomic_write(&lop->olo_func, MERGENODES_LOP_FUNC_INACTIVE);
	return NULL;
}



PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mergenode_waitfor_mpart_postlop)(Tobpostlockop(mpart) *__restrict _lop,
                                               REF struct mpart *__restrict self) {
	REF struct mman *mm;
	union mman_mergenodes_lop *lop;
	mm  = (struct mman *)((byte_t *)_lop - (uintptr_t)&thismman_mergenodes_lop.mml_mp_postlop);
	lop = &FORMMAN(mm, thismman_mergenodes_lop);

	/* Drop the reference that `async_waitfor_part_and_mergenodes()'
	 * created for us.  Note that  we can use  *nokill, because  the
	 * caller  of `mpart_lockops_reap()' must necessarily be holding
	 * another reference to this same part! */
	decref_nokill(self);

	/* Reset the LOP-state to indicate that we're inactive.
	 * We won't be inactive for  long, but for the sake  of
	 * consistency, race  conditions,  and  simplicity,  we
	 * temporarily  switch to INACTIVE, only to immediately
	 * re-start. */
	atomic_write(&lop->mml_mm_lop.olo_func, MERGENODES_LOP_FUNC_INACTIVE);

	/* Merge nodes of the mman. */
	mman_mergenodes(mm);

	/* Drop the reference given to us by the caller. */
	decref_unlikely(mm);
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(mpart) *
NOTHROW(FCALL mergenode_waitfor_mpart_lop)(Toblockop(mpart) *__restrict lop,
                                           REF struct mpart *__restrict UNUSED(self)) {
	Tobpostlockop(mpart) *post;
	post = (Tobpostlockop(mpart) *)lop;

	/* Do the rest of the work from a post-lockop.
	 * NOTE: This also inherit the reference to `self' */
	atomic_write(&post->oplo_func, &mergenode_waitfor_mpart_postlop);
	return post;
}

/* Wait for the lock of `blocking_part' to become available,
 * after which point  in time, call  `mman_mergenodes(self)' */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL async_waitfor_part_and_mergenodes)(struct mman *__restrict self,
                                                 struct mpart *__restrict blocking_part) {
	union mman_mergenodes_lop *lop;
	Toblockop_callback_t(mman) func;

	/* These references are inherited by `mergenode_waitfor_mpart_lop'
	 * (aka. `MERGENODES_LOP_FUNC_WAITFOR_MPART') */
	incref(self);
	incref(blocking_part);

	/* (try to) switch over into WAITFOR_MPART-mode. */
	lop = &FORMMAN(self, thismman_mergenodes_lop);
	do {
		func = atomic_read(&lop->mml_mm_lop.olo_func);
		if (func != MERGENODES_LOP_FUNC_INACTIVE &&
		    func != MERGENODES_LOP_FUNC_RUNNING) {
			/* Something that will eventually call mergenodes is already set-up!
			 * -> So just don't interfere... */
			decref_nokill(self);
			decref_nokill(blocking_part);
			return;
		}
	} while (!atomic_cmpxch(&lop->mml_mm_lop.olo_func, func,
	                        MERGENODES_LOP_FUNC_WAITFOR_MPART));

	/* Enqueue the lockop into `blocking_part' */
	SLIST_ATOMIC_INSERT(&blocking_part->mp_lockops,
	                    &lop->mml_mp_lop, olo_link);

	/* Kick-start async lockop handling in case `blocking_part'
	 * became unlocked in the mean time. */
	_mpart_lockops_reap(blocking_part);
}


/* Asynchronously re-attempt trying to merge  mem-parts.
 * May be called if merging isn't possible at the moment
 * due to lack of memory, or-the-like... */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_mergenodes)(struct mman *__restrict self) {
	union mman_mergenodes_lop *lop;
	lop = &FORMMAN(self, thismman_mergenodes_lop);
	if (atomic_cmpxch(&lop->mml_mm_lop.olo_func,
	                  MERGENODES_LOP_FUNC_INACTIVE,
	                  MERGENODES_LOP_FUNC_PENDING)) {
		incref(self); /* Inherited by `mergenodes_lop_cb()' */
		SLIST_ATOMIC_INSERT(&FORMMAN(self, thismman_lockops),
		                    &lop->mml_mm_lop, olo_link);
	}
}


/* Special return value for (some of) the `mnode_domerge*'
 * functions. When returned, this  means that the given  2
 * mem-nodes cannot actually be merged at all! */
#define MNODE_MERGE_CANNOT_MERGE ((struct mnode *)0)

/* Special return value for (some of) the `mnode_domerge*'
 * functions. When returned, stop attempting to merge more
 * nodes and simply return/release all locks.
 * This return value indicates that `thismman_mergenodes_lop'
 * has been re-purposed for async waiting on the lock of some
 * mem-part that is needed for merging nodes. Once that  lock
 * becomes available, `mman_mergenodes()' will  automatically
 * be called in order to re-start the act of merging nodes. */
#define MNODE_MERGE_ASYNC_WAITFOR ((struct mnode *)-1)





/* Merge the 2 given nodes.
 *    @assume(WAS_TRUE_AFTER_MMAN_LOCK(mnode_canmerge(lonode, hinode)));
 *    @assume(lonode->mn_part == NULL);
 *    @assume(hinode->mn_part == NULL);
 * Return a pointer to the newly merged node. */
PRIVATE NOBLOCK ATTR_RETNONNULL NONNULL((1, 2)) struct mnode *
NOTHROW(FCALL mnode_domerge_without_part)(struct mnode *__restrict lonode,
                                          struct mnode *__restrict hinode) {
	assert(lonode->mn_part == NULL);
	assert(hinode->mn_part == NULL);

	printk(KERN_DEBUG "[mm] Merge reserved nodes at %p-%p and %p-%p\n",
	       mnode_getminaddr(lonode), mnode_getmaxaddr(lonode),
	       mnode_getminaddr(hinode), mnode_getmaxaddr(hinode));

	/* Merge the 2 nodes */
	mman_mappings_removenode(lonode->mn_mman, lonode);
	mman_mappings_removenode(lonode->mn_mman, hinode);
	if (hinode->mn_module) {
		assert(hinode->mn_module->md_nodecount >= 2);
		--hinode->mn_module->md_nodecount;
	}

	/* Make the lonode cover the entirety of the hinode. */
	lonode->mn_maxaddr = hinode->mn_maxaddr;
	xdecref_nokill(hinode->mn_fspath);
	xdecref_nokill(hinode->mn_fsname);

	/* If the hinode was in the writable-list, then remove it.
	 * Furthermore, if the lonode wasn't  in its, add it  now! */
	if (LIST_ISBOUND(hinode, mn_writable)) {
		LIST_REMOVE(hinode, mn_writable);
		if (!LIST_ISBOUND(lonode, mn_writable))
			LIST_INSERT_HEAD(&lonode->mn_mman->mm_writable, lonode, mn_writable);
	}

	/* Re-insert the now enlarged lonode. */
	mman_mappings_insert_and_verify(lonode->mn_mman, lonode);

	/* Destroy the no-longer-used hinode. */
	mnode_free(hinode);
	return lonode;
}

/* Merge the 2 given nodes.
 *    @assume(WAS_TRUE_AFTER_MMAN_LOCK(mnode_canmerge(lonode, hinode)));
 *    @assume(lonode->mn_part != NULL);
 *    @assume(lonode->mn_part == hinode->mn_part);
 *    @assume(mpart_lock_acquired(lonode->mn_part));
 * Return a pointer to the newly merged node.
 * @return: * : The merged node.
 * @return: MNODE_MERGE_CANNOT_MERGE: ... */
PRIVATE NOBLOCK NONNULL((1, 2)) struct mnode *
NOTHROW(FCALL mnode_domerge_samepart_locked)(struct mnode *__restrict lonode,
                                             struct mnode *__restrict hinode) {
	assert(lonode->mn_part != NULL);
	assert(lonode->mn_part == hinode->mn_part);
	assert(mpart_lock_acquired(lonode->mn_part));

	/* Figure out the relative mapping addresses of the 2 parts. */
	if (mnode_getpartendaddr(lonode) == mnode_getpartaddr(hinode)) {
		/* Simple case: the in-part offsets mapped by the 2 nodes are
		 * already set-up such that  the memory they're mapping  uses
		 * adjacent in-part offsets. */
	} else {
		/* If  the 2 ranges  overlap with each other  in any way, then
		 * at least some part of the physical backing memory is mapped
		 * more than once, in which case merging isn't possible, since
		 * we must maintain the expected invariant of some part of the
		 * mapping shadowing another part. */
		if (RANGES_OVERLAP(mnode_getpartminaddr(lonode),
		                   mnode_getpartmaxaddr(lonode),
		                   mnode_getpartminaddr(hinode),
		                   mnode_getpartmaxaddr(hinode)))
			return MNODE_MERGE_CANNOT_MERGE;

		/* It ~is~ possible that we might be able to plug the  2
		 * portions of the mem-part that are being mapped out of
		 * the  part, and use  them to re-form  a new which then
		 * contains  only those portions that are actually used.
		 *
		 * However, for this we must also take a look at all other
		 * nodes  which may be  mapping the part  aside from the 2
		 * given nodes which our caller wants us to merge. */
		/* TODO */
		return MNODE_MERGE_CANNOT_MERGE;
	}

	printk(KERN_DEBUG "[mm] Merge nodes at %p-%p and %p-%p\n",
	       mnode_getminaddr(lonode), mnode_getmaxaddr(lonode),
	       mnode_getminaddr(hinode), mnode_getmaxaddr(hinode));

	/* Merge the 2 nodes */
	mman_mappings_removenode(lonode->mn_mman, lonode);
	mman_mappings_removenode(lonode->mn_mman, hinode);

	if (hinode->mn_module) {
		assert(hinode->mn_module->md_nodecount >= 2);
		--hinode->mn_module->md_nodecount;
	}

	/* Make the lonode cover the entirety of the hinode. */
	lonode->mn_maxaddr = hinode->mn_maxaddr;
	xdecref_nokill(hinode->mn_fspath);
	xdecref_nokill(hinode->mn_fsname);

	/* Remove the old hi-node */
	LIST_REMOVE(hinode, mn_link);

	/* If the hinode was in the writable-list, then remove it.
	 * Furthermore, if the  lonode wasn't in  it, add it  now! */
	if (LIST_ISBOUND(hinode, mn_writable)) {
		LIST_REMOVE(hinode, mn_writable);
		if (!LIST_ISBOUND(lonode, mn_writable))
			LIST_INSERT_HEAD(&lonode->mn_mman->mm_writable, lonode, mn_writable);
	}

	/* Re-insert the now enlarged lonode. */
	mman_mappings_insert_and_verify(lonode->mn_mman, lonode);

	/* Destroy the no-longer-used hinode. */
	decref_nokill(hinode->mn_part);
	mnode_free(hinode);
	return lonode;
}



/* Special return values for (some of) the `mpart_domerge*' functions */
#define MPART_MERGE_CANNOT_MERGE  ((struct mpart *)0)  /* s.a. `MNODE_MERGE_CANNOT_MERGE' */
#define MPART_MERGE_ASYNC_WAITFOR ((struct mpart *)-1) /* s.a. `MNODE_MERGE_ASYNC_WAITFOR' */

/* See description below... */
PRIVATE NOBLOCK NONNULL((1, 2, 3, 4)) REF struct mpart *
NOTHROW(FCALL mpart_domerge_with_mm_lock)(/*inherit(on_success)*/ REF struct mpart *lopart,
                                          /*inherit(on_success)*/ REF struct mpart *hipart,
                                          struct mman *__restrict locked_mman,
                                          struct mpart *orig_part);


#ifndef NDEBUG
/* Return the total # of bytes mapped by the given chunk-vec. */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW(FCALL mchunkvec_getsize)(struct mchunk const *__restrict vec, size_t cnt) {
	size_t i, result = 0;
	for (i = 0; i < cnt; ++i)
		result += vec[i].mc_size;
	return result * PAGESIZE;
}
#endif /* !NDEBUG */


/* Merge the 2 given nodes.
 *    @assume(WAS_TRUE_AFTER_MMAN_LOCK(mnode_canmerge(lonode, hinode)));
 *    @assume(lonode->mn_part != NULL);
 *    @assume(hinode->mn_part != NULL);
 *    @assume((lonode->mn_part == part) || (hinode->mn_part == part));
 *    @assume(mpart_lock_acquired(part));
 * Return a pointer to the newly merged node.
 * @return: * : The merged node. In this case, the lock to `part' will
 *              have been released, and the caller must inherit a lock
 *              to `return->mn_part' instead.
 * @return: MNODE_MERGE_CANNOT_MERGE:  ...
 * @return: MNODE_MERGE_ASYNC_WAITFOR: ... */
PRIVATE NOBLOCK NONNULL((1, 2, 3)) struct mnode *
NOTHROW(FCALL mnode_domerge_with_part_lock)(struct mnode *__restrict lonode,
                                            struct mnode *__restrict hinode,
                                            struct mpart *__restrict part) {
	struct mpart *other_part;
	assert(lonode->mn_part != NULL);
	assert(hinode->mn_part != NULL);
	assert((lonode->mn_part == part) || (hinode->mn_part == part));
	assert(mpart_lock_acquired(part));

	/* Check for simple case of both nodes using the same part. */
	if (lonode->mn_part == hinode->mn_part) {
merge_identical_parts:
		return mnode_domerge_samepart_locked(lonode, hinode);
	}
	other_part = lonode->mn_part;
	if (other_part == part)
		other_part = hinode->mn_part;
	assert(other_part != part);
	if (!mpart_lock_tryacquire(other_part)) {
		async_waitfor_part_and_mergenodes(lonode->mn_mman,
		                                  other_part);
		return MNODE_MERGE_ASYNC_WAITFOR;
	}

	/* Re-check if it's possible to merge the 2 parts in question. */
	if (!mpart_canmerge(lonode->mn_part, hinode->mn_part, true)) {
		mpart_lock_release(other_part);
		return MNODE_MERGE_CANNOT_MERGE;
	}

	/* Try to merge `part' with `other_part' */
	{
		REF struct mpart *lopart, *hipart;
		REF struct mpart *merged;
		lopart = incref(lonode->mn_part);
		hipart = incref(hinode->mn_part);
		merged = mpart_domerge_with_mm_lock(lopart, hipart, lonode->mn_mman, part);
		if (merged == MPART_MERGE_CANNOT_MERGE ||
		    merged == MPART_MERGE_ASYNC_WAITFOR) {
			/* Merging will be performed asynchronously, or merging isn't possible. */
			assert(lopart == lonode->mn_part);
			assert(hipart == hinode->mn_part);
			decref_nokill(lopart);
			decref_nokill(hipart);
			mpart_lock_release(other_part);
			if (merged == MPART_MERGE_CANNOT_MERGE)
				return MNODE_MERGE_CANNOT_MERGE;
			return MNODE_MERGE_ASYNC_WAITFOR;
		}

		/* Successfully merged the 2 parts.
		 * As the result of this, we've lost the following locks:
		 *    - mpart_lock_acquired(part)
		 *    - mpart_lock_acquired(other_part)
		 * Whilst simultaneously gaining the following lock:
		 *    - merged_part
		 * Additionally, we're still holding a lock to `locked_mm',
		 * and both of the parts should now be referencing the same
		 * `merged_part' (meaning that we can loop back to the case
		 * of merging 2 nodes mapping the same mem-part) */
		assert(lonode->mn_part == merged);
		assert(hinode->mn_part == merged);
#ifndef NDEBUG
		assertf(merged->mp_state != MPART_ST_MEM_SC ||
		        mchunkvec_getsize(merged->mp_mem_sc.ms_v,
		                          merged->mp_mem_sc.ms_c) ==
		        mpart_getsize(merged),
		        "mchunkvec_getsize(): %#" PRIxSIZ "\n"
		        "mpart_getsize():     %#" PRIxSIZ,
		        mchunkvec_getsize(merged->mp_mem_sc.ms_v,
		                          merged->mp_mem_sc.ms_c),
		        mpart_getsize(merged));
#endif /* !NDEBUG */
		decref_nokill(merged); /* The reference returned by `mpart_domerge_with_mm_lock()' */
		goto merge_identical_parts;
	}
}

/* Merge the 2 given nodes.
 *    @assume(WAS_TRUE_AFTER_MMAN_LOCK(mnode_canmerge(lonode, hinode)));
 * Return a pointer to the newly merged node.
 * @return: * : The merged node.
 * @return: MNODE_MERGE_CANNOT_MERGE:  ...
 * @return: MNODE_MERGE_ASYNC_WAITFOR: ... */
PRIVATE NOBLOCK NONNULL((1, 2)) struct mnode *
NOTHROW(FCALL mnode_domerge)(struct mnode *__restrict lonode,
                             struct mnode *__restrict hinode) {
	struct mpart *lopart;
	assert((lonode->mn_part != NULL) == (hinode->mn_part != NULL));
	if ((lopart = lonode->mn_part) == NULL)
		return mnode_domerge_without_part(lonode, hinode);

	/* Try to acquire a lock to  the first part, so we  can
	 * use `mnode_domerge_with_part_lock()' to do the rest.
	 * If the lock  can't be acquired,  then we can  simply
	 * make use of `async_waitfor_part_and_mergenodes()' in
	 * order to wait for it to become available. */
	if (mpart_lock_tryacquire(lopart)) {
		struct mnode *result;
		result = mnode_domerge_with_part_lock(lonode, hinode, lopart);
		if (result != MNODE_MERGE_CANNOT_MERGE &&
		    result != MNODE_MERGE_ASYNC_WAITFOR)
			lopart = result->mn_part;
		mpart_assert_integrity(lopart);
		mpart_lock_release(lopart);
		return result;
	}

	/* Must asynchronously wait for the part to become available. */
	async_waitfor_part_and_mergenodes(lonode->mn_mman, lopart);
	return MNODE_MERGE_ASYNC_WAITFOR;
}


/* Merge a mem-node without a backing part (i.e. a RESERVED node) */
PRIVATE NOBLOCK ATTR_RETNONNULL NONNULL((1)) struct mnode *
NOTHROW(FCALL mnode_merge_without_part)(struct mnode *__restrict self) {
	struct mnode *neighbor;
	assert(self->mn_part == NULL);
	if ((neighbor = mnode_tree_prevnode(self)) != NULL && mnode_canmerge(neighbor, self))
		self = mnode_domerge_without_part(neighbor, self);
	if ((neighbor = mnode_tree_nextnode(self)) != NULL && mnode_canmerge(self, neighbor))
		self = mnode_domerge_without_part(self, neighbor);
	return self;
}


/* Same as `mnode_merge()', but the  caller must also be holding  a
 * lock to `self->mn_part' (which may  be assumed to be  non-NULL).
 * Upon return, the lock to `self->mn_part' may have been released,
 * because of which case the caller  must alway inherits a lock  to
 * `return->mn_part'. */
PUBLIC NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) struct mnode *
NOTHROW(FCALL mnode_merge_with_partlock)(struct mnode *__restrict self) {
	struct mnode *merged, *neighbor;
	assert(self->mn_part);
	assert(mpart_lock_acquired(self->mn_part));
	if ((neighbor = mnode_tree_prevnode(self)) != NULL && mnode_canmerge(neighbor, self)) {
		merged = mnode_domerge_with_part_lock(neighbor, self, self->mn_part);
		if unlikely(merged == MNODE_MERGE_ASYNC_WAITFOR)
			return self; /* Merging will be completed asynchronously. */
		if (merged != MNODE_MERGE_CANNOT_MERGE)
			self = merged; /* Successfully merged! */
	}
	if ((neighbor = mnode_tree_nextnode(self)) != NULL && mnode_canmerge(self, neighbor)) {
		merged = mnode_domerge_with_part_lock(self, neighbor, self->mn_part);
		if unlikely(merged == MNODE_MERGE_ASYNC_WAITFOR)
			return self; /* Merging will be completed asynchronously. */
		if (merged != MNODE_MERGE_CANNOT_MERGE)
			self = merged; /* Successfully merged! */
	}
	return self;
}


/* While  holding a lock  to `self->mn_mman', try to  merge the given node
 * with its successor/predecessor node, without releasing the lock to  the
 * associated mman. If it is found that `self' is mergeable, but that this
 * cannot be done  without blocking, `self->mn_mman'  is set-up such  that
 * the merge operation will be performed asynchronously.
 * @return: * : The new, merged node (which may have a different min-addr
 *              that the original node `self'). Also note that this  node
 *              may or may not be equal to `self', and that it's min- and
 *              max-addr fields may be  different from those that  `self'
 *              had upon entry, irregardless of `self' being re-returned.
 *              As  a matter of fact `*self' becomes invalid after a call
 *              to this function! */
PUBLIC NOBLOCK ATTR_RETNONNULL NONNULL((1)) struct mnode *
NOTHROW(FCALL mnode_merge)(struct mnode *__restrict self) {
	struct mnode *result;
	struct mpart *part;
	assert(!(self->mn_flags & MNODE_F_UNMAPPED));

	/* Deal with special case: no backing part (RESERVED node) */
	if unlikely((part = self->mn_part) == NULL)
		return mnode_merge_without_part(self);

	/* Try to acquire a lock to the associated part. */
	if (mpart_lock_tryacquire(part)) {
		result = mnode_merge_with_partlock(self);
		mpart_assert_integrity(result->mn_part);
		mpart_lock_release(result->mn_part);
	} else {
		/* If  we couldn't get a lock to the part, but the
		 * node _does_ have  some neighboring nodes  which
		 * may be suitable  for merging,  then enqueue  an
		 * async operation to merge nodes of the mman once
		 * the caller has released their lock to the mman. */
		if (mnode_shouldmerge(self))
			async_waitfor_part_and_mergenodes(self->mn_mman, part);
		result = self;
	}
	return result;
}


/* Mark the given mman as potentially containing mergeable  mem-nodes.
 * These nodes will (eventually) be merged asynchronously, but may not
 * be merged immediately (though they might be merged immediately).
 * NOTE: The caller isn't required to be holding a lock to `self', but
 *       if they are, this function is still going to be non-blocking,
 *       and the node-merging process  will simply happen _after_  the
 *       caller releases their lock. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mman_mergenodes)(struct mman *__restrict self) {
	if (mman_lock_tryacquire(self)) {
		mman_mergenodes_locked(self);
		mman_lock_release(self);
	} else {
		/* Try to enqueue (and possibly start) an async  merge-nodes
		 * operation. If such an operation had already been started,
		 * or is currently still in progress, then do nothing, since
		 * in  that case someone else already acquired a lock to the
		 * mman, and started  an async  merge-nodes operation  after
		 * whatever previously happened  that caused  our caller  to
		 * end up wishing to merge all mem-nodes of `self'! */
		async_mergenodes(self);
		_mman_lockops_reap(self);
	}
}

/* Same as `mman_mergenodes()', but the caller _must_ be holding a lock
 * to the given mman `self'! */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mman_mergenodes_locked)(struct mman *__restrict self) {
	struct mnode *node, *next;
	if unlikely((node = self->mm_mappings) == NULL)
		return;
	while (node->mn_mement.rb_lhs)
		node = node->mn_mement.rb_lhs;
	for (;;) {
		next = mnode_tree_nextnode(node);
		if (!next)
			break;
		if (!mnode_canmerge(node, next)) {
			node = next;
			continue;
		}

		/* Try to merge `node' with `next' */
		node = mnode_domerge(node, next);
		if unlikely(node == MNODE_MERGE_ASYNC_WAITFOR)
			return;
		if (node == MNODE_MERGE_CANNOT_MERGE)
			node = next; /* Nodes couldn't be merged (try next the pair) */
	}
}

/* Helper wrapper to try to merge all nodes within the given range. The
 * caller must be holding a lock to `self' when calling this  function. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mman_mergenodes_inrange)(struct mman *__restrict self,
                                       void const *minaddr,
                                       void const *maxaddr) {
	struct mnode *node, *next;
	struct mnode_tree_minmax mima;
	mman_mappings_minmaxlocate(self, minaddr, maxaddr, &mima);
	if (!mima.mm_min)
		return;

	/* Try to merge the first node of the address range with its
	 * predecessor (which may lie outside of the address  range) */
	next = mnode_tree_prevnode(mima.mm_min);
	if (next && mnode_canmerge(next, mima.mm_min)) {
		next = mnode_domerge(next, mima.mm_min);
		if unlikely(next == MNODE_MERGE_ASYNC_WAITFOR)
			return;
		if (next != MNODE_MERGE_CANNOT_MERGE)
			mima.mm_min = next;
	}

	/* Go over all nodes within the address range, and  try
	 * to merge them with whatever is the next node (resp.) */
	for (node = mima.mm_min;;) {
		next = mnode_tree_nextnode(node);
		if (!next)
			break; /* Nothing here but us chickens... */
		if (!mnode_canmerge(next, mima.mm_min)) {
			if (node == mima.mm_max)
				break;
			node = next;
			continue;
		}

		/* Try to merge `node' with `next' */
		node = mnode_domerge(node, next);
		if unlikely(node == MNODE_MERGE_ASYNC_WAITFOR)
			return;
		if (node == mima.mm_max) {
			/* What we've just tried to merge was the last node from the given
			 * address range, with  whatever comes after  said address  range.
			 * iow: no matter if the merge was successful or not, we're done! */
			break;
		}
		if (node == MNODE_MERGE_CANNOT_MERGE)
			node = next; /* Nodes couldn't be merged (try next the pair) */
	}
}





/************************************************************************/
/* Mem-part merging                                                     */
/************************************************************************/

PRIVATE NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL mnode_trymerge_with_partlock)(struct mnode *__restrict self,
                                            REF struct mpart **__restrict p_part) {
	struct mnode *merged, *neighbor;
	bool result = false;
	REF struct mman *mm;
	mm = self->mn_mman;

	/* Try to get a reference to the mman. Note that we must use `tryincref()',
	 * since the mman may have already been destroyed, since we're accessing it
	 * from the view-point  of one of  its potentially-once-upon-a-time  mapped
	 * mem-parts. */
	if unlikely(!tryincref(mm))
		goto done;

	/* Try to acquire a lock to the mman. */
	if (!mman_lock_tryacquire(mm)) {
		if unlikely(atomic_read(&self->mn_flags) & MNODE_F_UNMAPPED)
			goto done_decref;

		/* Must attempt an async merge of all nodes! */
		async_mergenodes(mm);
		_mman_lockops_reap(mm);
		goto done_decref;
	}

	/* Check if the node has been unmapped, in which case
	 * we can no longer merge it with neighboring  nodes,
	 * since no such nodes exist anymore... */
	if unlikely(self->mn_flags & MNODE_F_UNMAPPED)
		goto done_decref_unlock;

	/* Only assert this when the part's not marked as unmapped! */
	assert(self->mn_part == *p_part);

	if ((neighbor = mnode_tree_prevnode(self)) != NULL && mnode_canmerge(neighbor, self)) {
		merged = mnode_domerge_with_part_lock(neighbor, self, *p_part);
		if unlikely(merged == MNODE_MERGE_ASYNC_WAITFOR)
			goto done_decref_unlock;
		if (merged != MNODE_MERGE_CANNOT_MERGE) {
			result = true; /* Successfully merged! */
			self   = merged;
update_p_part_after_prev:
			decref_unlikely(*p_part);
			*p_part = incref(self->mn_part);
		} else if (self->mn_part != *p_part) {
			/* Even if nodes couldn't be merged, the backing parts may still have been... */
			goto update_p_part_after_prev;
		}
	}
	if ((neighbor = mnode_tree_nextnode(self)) != NULL && mnode_canmerge(self, neighbor)) {
		assert(self->mn_part == *p_part);
		merged = mnode_domerge_with_part_lock(self, neighbor, *p_part);
		if unlikely(merged == MNODE_MERGE_ASYNC_WAITFOR)
			goto done_decref_unlock;
		if (merged != MNODE_MERGE_CANNOT_MERGE) {
			result = true; /* Successfully merged! */
			self   = merged;
update_p_part_after_next:
			decref_unlikely(*p_part);
			*p_part = incref(self->mn_part);
		} else if (self->mn_part != *p_part) {
			/* Even if nodes couldn't be merged, the backing parts may still have been... */
			goto update_p_part_after_next;
		}
	}

done_decref_unlock:
	mman_lock_release(mm);
done_decref:
	decref_unlikely(mm);
done:
	return result;
}


/* Try to merge all of the nodes that are mapping the given part. */
PRIVATE NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mpart *
NOTHROW(FCALL mpart_trymerge_nodes)(REF struct mpart *__restrict self) {
	unsigned int i;
again:
	for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
		struct mnode *node;
		LIST_FOREACH (node, &self->_mp_nodlsts[i], mn_link) {
			if (mnode_trymerge_with_partlock(node, (REF struct mpart **)&self))
				goto again;
		}
	}
	return self;
}



/* Wait for `part_to_wait' to become available, after which point
 * in time, try to merge `part_to_merge' with its neighbors. This
 * will  be done as  per `mpart_merge(part_to_merge)'. The caller
 * must try to reap lockops of `part_to_wait' after calling  this
 * function! */
PRIVATE NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL async_waitfor_part_and_mergepart)(struct mpart *part_to_wait,
                                                struct mpart *part_to_merge);

/* Same as `async_waitfor_part_and_mergepart()', but wait for a given futex-lock. */
PRIVATE NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL async_waitfor_ftxlck_and_mergepart)(struct mpart *part_to_wait,
                                                  struct mpart *part_to_merge);

/* Same as `async_waitfor_part_and_mergepart()', but wait for a given file. */
PRIVATE NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL async_waitfor_file_and_mergepart)(struct mfile *file_to_wait,
                                                struct mpart *part_to_merge);

/* Same as `async_waitfor_part_and_mergepart()', but wait for a given mman. */
PRIVATE NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL async_waitfor_mman_and_mergepart)(struct mman *mman_to_wait,
                                                struct mpart *part_to_merge);


/* Check if `self' has a mem-node that belongs to `mm' */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1, 2)) bool
NOTHROW(FCALL mpart_mappedby_mman)(struct mpart const *__restrict self,
                                   struct mman const *__restrict mm) {
	unsigned int i;
	for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
		struct mnode *node;
		LIST_FOREACH (node, &self->_mp_nodlsts[i], mn_link) {
			if (node->mn_mman == mm)
				return true;
		}
	}
	return false;
}

/* Like `mpart_mappedby_mman()', but stop checking nodes when `stop'
 * is reached. Additionally, `stop' isn't considered to be apart  of
 * the list of nodes to test for mapping `mm' */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1, 3)) bool
NOTHROW(FCALL mpart_mappedby_mman_before)(struct mpart const *__restrict self,
                                          struct mnode const *stop,
                                          struct mman const *__restrict mm) {
	unsigned int i;
	for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
		struct mnode *node;
		LIST_FOREACH (node, &self->_mp_nodlsts[i], mn_link) {
			if (node == stop)
				return false;
			if (node->mn_mman == mm)
				return true;
		}
	}
	return false;
}

/* Incref all mmans of `self' (skipping those that were already destroyed) */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) void
NOTHROW(FCALL mpart_incref_all_mmans)(struct mpart const *__restrict self) {
	unsigned int i;
	for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
		struct mnode *node;
		LIST_FOREACH (node, &self->_mp_nodlsts[i], mn_link)
			COMPILER_UNUSED(tryincref(node->mn_mman));
	}
}

/* Decref all mmans of `self' (skipping those that were already destroyed) */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) void
NOTHROW(FCALL mpart_decref_all_mmans)(struct mpart const *__restrict self) {
	unsigned int i;
	for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
		struct mnode *node;
		LIST_FOREACH (node, &self->_mp_nodlsts[i], mn_link) {
			if likely(!wasdestroyed(node->mn_mman))
				decref_unlikely(node->mn_mman);
		}
	}
}


/* Release locks to every unique mman with nodes that map `self'.
 * For every mman, only a single lock is released, and only locks
 * to mmans to nodes before `stop' are released (unless `stop' is
 * given as `NULL', in which case _all_ locks are released) */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) void
NOTHROW(FCALL mpart_unlock_all_mmans)(struct mpart const *__restrict self,
                                      struct mnode const *stop DFL(NULL),
                                      struct mman *locked_mman DFL(NULL)) {
	struct mnode *node;
	unsigned int i;
	for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
		LIST_FOREACH (node, &self->_mp_nodlsts[i], mn_link) {
			if (node == stop)
				return; /* Stop on this node! */
			if (node->mn_mman == locked_mman)
				continue; /* Must remain locked by the caller */
			if unlikely(wasdestroyed(node->mn_mman))
				continue; /* Skip destroyed mmans */
			if (mpart_mappedby_mman_before(self, node, node->mn_mman))
				continue; /* Already unlocked before... */
			mman_lock_release(node->mn_mman);
		}
	}
}

/* Like `mpart_unlock_all_mmans()', but don't release locks
 * to  mmans  that  are  also  mapped  by  `already_locked' */
PRIVATE NOBLOCK WUNUSED NONNULL((1, 2)) void
NOTHROW(FCALL mpart_unlock_all_mmans_after)(struct mpart const *__restrict self,
                                            struct mpart const *__restrict already_locked,
                                            struct mnode const *stop DFL(NULL),
                                            struct mman *locked_mman DFL(NULL)) {
	struct mnode *node;
	unsigned int i;
	for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
		LIST_FOREACH (node, &self->_mp_nodlsts[i], mn_link) {
			if (node == stop)
				return; /* Stop on this node! */
			if (node->mn_mman == locked_mman)
				continue; /* Must remain locked by the caller */
			if unlikely(wasdestroyed(node->mn_mman))
				continue; /* Skip destroyed mmans */
			if (mpart_mappedby_mman_before(self, node, node->mn_mman))
				continue; /* Already unlocked before... */
			if (mpart_mappedby_mman(already_locked, node->mn_mman))
				continue; /* Lock is held by the caller... */
			mman_lock_release(node->mn_mman);
		}
	}
}

/* Try to acquire locks to all of the mmans of `self'. (skipping dead mmans)
 * If doing so would block for one  of the mmans, release all locks  already
 * acquired, and return a pointer to the blocking mman. */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) struct mman *
NOTHROW(FCALL mpart_lock_all_mmans)(struct mpart const *__restrict self,
                                    struct mman *locked_mman DFL(NULL)) {
	struct mnode *node;
	unsigned int i;
	for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
		LIST_FOREACH (node, &self->_mp_nodlsts[i], mn_link) {
			if (node->mn_mman == locked_mman)
				continue; /* Already locked by the caller... */
			if unlikely(wasdestroyed(node->mn_mman))
				continue; /* Skip destroyed mmans */
			if (mman_lock_tryacquire(node->mn_mman))
				continue; /* Successfully locked the mman */
			if (mpart_mappedby_mman_before(self, node, node->mn_mman))
				continue; /* We've already acquired a lock to this mman in the part. */

			/* Oops... We've got a blocking one here! */
			mpart_unlock_all_mmans(self, node, locked_mman);
			return node->mn_mman;
		}
	}
	return NULL;
}

/* Same as `mpart_lock_all_mmans()', but assume that mmans
 * from   `already_locked'   have  already   been  locked. */
PRIVATE NOBLOCK WUNUSED NONNULL((1, 2)) struct mman *
NOTHROW(FCALL mpart_lock_all_mmans_after)(struct mpart const *__restrict self,
                                          struct mpart const *__restrict already_locked,
                                          struct mman *locked_mman DFL(NULL)) {
	struct mnode *node;
	unsigned int i;
	for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
		LIST_FOREACH (node, &self->_mp_nodlsts[i], mn_link) {
			if (node->mn_mman == locked_mman)
				continue; /* Already locked by the caller... */
			if unlikely(wasdestroyed(node->mn_mman))
				continue; /* Skip destroyed mmans */
			if (mman_lock_tryacquire(node->mn_mman))
				continue; /* Successfully locked the mman */
			if (mpart_mappedby_mman_before(self, node, node->mn_mman))
				continue; /* We've already acquired a lock to this mman in the part. */
			if (mpart_mappedby_mman(already_locked, node->mn_mman))
				continue; /* Assumed to already be locked... */

			/* Oops... We've got a blocking one here! */
			mpart_unlock_all_mmans_after(self, already_locked, node, locked_mman);
			return node->mn_mman;
		}
	}
	return NULL;
}


#define mpart_destroy_lockop_encode(prt) ((struct lockop *)&(prt)->mp_blkst_ptr)
#define mpart_destroy_lockop_decode(lop) container_of((uintptr_t **)(lop), struct mpart, mp_blkst_ptr)
INTDEF NOBLOCK NONNULL((1)) struct postlockop * /* From "mpart.c" */
NOTHROW(FCALL mpart_destroy_lop_rmall_async)(struct lockop *__restrict self);

/* Use an async job to merge `self' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL asyncjob_merge_part)(struct mpart *__restrict self) {
	mpart_start_asyncjob(incref(self), MPART_XF_WILLMERGE);
}


/* Allocate kmalloc()-memory (GFP_LOCKED), but if this allocation fails,
 * make  it so that `orig_part' will be  merged once again the next time
 * lockops of the kernel mman are reaped, before re-attempting the alloc
 * a second time.
 * Only if both attempts fail, `NULL' is returned. */
PRIVATE NOBLOCK ATTR_MALLOC NONNULL((2)) void *
NOTHROW(FCALL merge_malloc)(size_t num_bytes, struct mpart *__restrict orig_part) {
	void *result;
	result = kmalloc_nx(num_bytes, GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
	if (!result) {
		asyncjob_merge_part(orig_part);
		result = kmalloc_nx(num_bytes, GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
	}
	return result;
}

PRIVATE NOBLOCK ATTR_MALLOC NONNULL((3)) void *
NOTHROW(FCALL merge_realloc)(void *ptr, size_t num_bytes,
                             struct mpart *__restrict orig_part) {
	void *result;
	result = krealloc_nx(ptr, num_bytes, GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
	if (!result) {
		asyncjob_merge_part(orig_part);
		result = krealloc_nx(ptr, num_bytes, GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
	}
	return result;
}


/* Transfer the given `tree' into `dst', updating futex
 * objects  to by incrementing `mfu_addr' by `addroff',
 * and setting `newpart' as `mfu_part' */
PRIVATE NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL mpartmeta_transfer_futex_tree)(struct mpartmeta *__restrict dst,
                                             struct mfutex *__restrict tree,
                                             struct mpart *__restrict newpart,
                                             size_t addroff) {
	struct mfutex *lo, *hi;
again:
	lo = tree->mfu_mtaent.rb_lhs;
	hi = tree->mfu_mtaent.rb_rhs;

	if (tryincref(tree)) {
		/* Update this futex object. */
		tree->mfu_addr += addroff;
		awref_set(&tree->mfu_part, newpart);

		/* Insert into the new part's futex-tree. */
		mpartmeta_ftx_insert(dst, tree);

		/* Drop the reference from above. */
		decref_unlikely(tree);
	} else {
		DBG_memset(&tree->mfu_mtaent, 0xcc, sizeof(tree->mfu_mtaent));
		awref_clear(&tree->mfu_part);
		weakdecref_nokill(tree);
	}

	/* Recursively iterate the entire tree. */
	if (lo) {
		if (hi)
			mpartmeta_transfer_futex_tree(dst, hi, newpart, addroff);
		tree = lo;
		goto again;
	}
	if (hi) {
		tree = hi;
		goto again;
	}
}






/* Merge the 2 given parts.
 *    @assume(mpart_canmerge(lopart, hipart));
 *    @assume(mpart_lock_acquired(lopart));
 *    @assume(mpart_lock_acquired(hipart));
 *    @assume(!lopart->mp_meta || mpartmeta_ftxlock_writing(lopart->mp_meta));
 *    @assume(!hipart->mp_meta || mpartmeta_ftxlock_writing(hipart->mp_meta));
 *    @assume(lopart->mp_file == hipart->mp_file));
 *    @assume(mpart_isanon(lopart) || mfile_lock_writing(lopart->mp_file));
 *    @assume(mpart_isanon(lopart) == mpart_isanon(hipart));
 *    @assume(mman_lock_acquired(lopart->mp_copy.each->mn_mman));
 *    @assume(mman_lock_acquired(lopart->mp_share.each->mn_mman));
 *    @assume(mman_lock_acquired(hipart->mp_copy.each->mn_mman));
 *    @assume(mman_lock_acquired(hipart->mp_share.each->mn_mman));
 * Return a pointer to the newly merged node.
 * @return: * : The merged part. (in  this case, the returned  part
 *              is still locked, but locks to `lopart' and `hipart'
 *              have  been lost; Additionally, references to lopart
 *              and hipart will  have also been  dropped, whilst  a
 *              new reference for a new part is returned)
 * @return: MPART_MERGE_CANNOT_MERGE:  ...
 * @return: MPART_MERGE_ASYNC_WAITFOR: ... */
PRIVATE NOBLOCK NONNULL((1, 2, 3)) REF struct mpart *
NOTHROW(FCALL mpart_domerge_with_all_locks)(/*inherit(on_success)*/ REF struct mpart *lopart,
                                            /*inherit(on_success)*/ REF struct mpart *hipart,
                                            struct mpart *orig_part,
                                            struct mman *locked_mman) {
	bool hasmeta;
	size_t losize = mpart_getsize(lopart);
	size_t hisize = mpart_getsize(hipart);
	assert_assume(lopart->mp_file == hipart->mp_file);

	/* Remove with parts from the associated file. (if not anon) */
	if (!mpart_isanon(lopart)) {
		mpart_tree_removenode(&lopart->mp_file->mf_parts, lopart);
		mpart_tree_removenode(&lopart->mp_file->mf_parts, hipart);
	}

	/* Check if we must allocate a meta-controller for `lopart'. */
	hasmeta = hipart->mp_meta &&
	          (hipart->mp_meta->mpm_ftx != NULL ||
#ifdef ARCH_HAVE_RTM
	           hipart->mp_meta->mpm_rtm_vers != 0 ||
#endif /* ARCH_HAVE_RTM */
	           0);
	if (hasmeta && !lopart->mp_meta) {
		/* Must allocate the meta-controller for `lopart' */
		struct mpartmeta *meta;
		meta = (struct mpartmeta *)merge_malloc(sizeof(struct mpartmeta), orig_part);
		if unlikely(!meta)
			goto err_async_waitfor;
		/* Must initialize  the meta-control  lock as  being held  for  writing.
		 * This is necessary since our caller will eventually inherit this lock! */
		_mpartmeta_init_noftxlock(meta);
		atomic_rwlock_init_write(&meta->mpm_ftxlock);
		lopart->mp_meta = meta;
	}

	/* Check how much memory will be required to represent the
	 * new  (merged)  block status  bitset, and  if necessary,
	 * (re-)allocate more memory for `lopart' to hold it! */
	if (lopart->mp_blkst_ptr != NULL || hipart->mp_blkst_ptr != NULL ||
	    (lopart->mp_flags & MPART_F_BLKST_INL) ||
	    (hipart->mp_flags & MPART_F_BLKST_INL)) {
		size_t total_bytes, total_blocks, lo_blocks;
		total_bytes  = losize + hisize;
		total_blocks = total_bytes >> lopart->mp_file->mf_blockshift;
		lo_blocks    = losize >> lopart->mp_file->mf_blockshift;
		if (total_blocks <= MPART_BLKST_BLOCKS_PER_WORD) {
			/* The combination of the 2 parts still fits into the inline bitset. */
			mpart_blkst_word_t loword, hiword;
			shift_t loshift;
			loword = lopart->mp_blkst_inl;
			if unlikely(!(lopart->mp_flags & MPART_F_BLKST_INL)) {
				loword = MPART_BLOCK_REPEAT(MPART_BLOCK_ST_CHNG);
				if (lopart->mp_blkst_ptr != NULL) {
					loword = lopart->mp_blkst_ptr[0];
					kfree(lopart->mp_blkst_ptr);
				}
				atomic_or(&lopart->mp_flags, MPART_F_BLKST_INL);
			}
			hiword = hipart->mp_blkst_inl;
			if unlikely(!(hipart->mp_flags & MPART_F_BLKST_INL)) {
				hiword = MPART_BLOCK_REPEAT(MPART_BLOCK_ST_CHNG);
				if (hipart->mp_blkst_ptr != NULL)
					hiword = hipart->mp_blkst_ptr[0];
			}
			loshift = (shift_t)(lo_blocks * MPART_BLOCK_STBITS);
			loword &= ((mpart_blkst_word_t)1 << loshift) - 1;
			loword |= hiword << loshift;
			lopart->mp_blkst_inl = loword;
		} else {
			/* TODO: Merge dynamically allocated (multi-word) bitsets. */
			goto err_cannot_merge;
		}
	}

	/* Merge mem-part backing data. */
	if likely(MPART_ST_INMEM(lopart->mp_state) &&
	          MPART_ST_INMEM(hipart->mp_state)) {
		/* Merge physical memory
		 * Also: If  memory between the end of `lopart' and the start of
		 *       `hipart' isn't continuous, try to allocate physical ram
		 *       the size of the smaller of the 2 parts such that it  is
		 *       continuous  with the other (larger) part, prepare() all
		 *       of the page directory locations that map the smaller of
		 *       the 2 parts.
		 *       ...
		 *       Continue on  to replace  the  backing storage  of  the
		 *       smaller of the 2 parts with the new physical location,
		 *       thus eventually allowing the larger part to be  linear
		 *       with the smaller part's physical backing memory. */
		struct mchunk *lovec, *hivec;
		size_t locnt, hicnt;
		locnt = 1;
		lovec = &lopart->mp_mem;
		if (MPART_ST_SCATTER(lopart->mp_state)) {
			locnt = lopart->mp_mem_sc.ms_c;
			lovec = lopart->mp_mem_sc.ms_v;
			assert(locnt >= 1);
			if unlikely(locnt == 1) {
				/* Simplify... */
				lopart->mp_mem   = lovec[0];
				lopart->mp_state = MPART_ST_MEM;
				kfree(lovec);
				lovec = &lopart->mp_mem;
			}
		}
		hicnt = 1;
		hivec = &hipart->mp_mem;
		if (MPART_ST_SCATTER(hipart->mp_state)) {
			hicnt = hipart->mp_mem_sc.ms_c;
			hivec = hipart->mp_mem_sc.ms_v;
			if unlikely(hicnt == 1) {
				/* Simplify... */
				hipart->mp_mem   = hivec[0];
				hipart->mp_state = MPART_ST_MEM;
				kfree(hivec);
				hivec = &hipart->mp_mem;
			}
		}
#ifndef NDEBUG
		assertf(mchunkvec_getsize(lovec, locnt) == losize,
		        "mchunkvec_getsize(lovec, locnt) = %#" PRIxSIZ "\n"
		        "losize                          = %#" PRIxSIZ,
		        mchunkvec_getsize(lovec, locnt), losize);
		assertf(mchunkvec_getsize(hivec, hicnt) == hisize,
		        "mchunkvec_getsize(hivec, hicnt) = %#" PRIxSIZ "\n"
		        "hisize                          = %#" PRIxSIZ,
		        mchunkvec_getsize(hivec, hicnt), hisize);
#endif /* !NDEBUG */
		if ((lovec[locnt - 1].mc_start + lovec[locnt - 1].mc_size) != hivec[0].mc_start) {
			/* TODO: Try to re-map the chunks of the 2 parts so they become continuous */
		}

		/* Deal with the simple case: merge 2 in-line vectors. */
		if (locnt == 1 && hicnt == 1) {
			assert(lopart->mp_state == MPART_ST_MEM);
			assert(hipart->mp_state == MPART_ST_MEM);
			if ((lovec->mc_start + lovec->mc_size) == hivec->mc_start) {
				lovec->mc_size += hivec->mc_size;
			} else {
				struct mchunk *newvec;
				newvec = (struct mchunk *)merge_malloc(sizeof(struct mchunk) * 2, orig_part);
				if unlikely(!newvec)
					goto err_async_waitfor;
				newvec[0]              = *lovec;
				newvec[1]              = *hivec;
				lopart->mp_mem_sc.ms_c = 2;
				lopart->mp_mem_sc.ms_v = newvec; /* Inherit */
				lopart->mp_state       = MPART_ST_MEM_SC;
			}
		} else if (hicnt == 1) {
			/* Extend `lovec' with a single entry. */
			assert(lopart->mp_state == MPART_ST_MEM_SC);
			if ((lovec[locnt - 1].mc_start + lovec[locnt - 1].mc_size) == hivec->mc_start) {
				lovec[locnt - 1].mc_size += hivec->mc_size;
			} else {
				struct mchunk *newvec;
				newvec = (struct mchunk *)merge_realloc(lovec,
				                                        (locnt + 1) *
				                                        sizeof(struct mchunk),
				                                        orig_part);
				if unlikely(!newvec)
					goto err_async_waitfor;
				newvec[locnt]          = *hivec;
				lopart->mp_mem_sc.ms_c = locnt + 1;
				lopart->mp_mem_sc.ms_v = newvec; /* Inherit */
			}
		} else if (locnt == 1) {
			assert(lopart->mp_state == MPART_ST_MEM);
			/* Extend `hivec' downwards, and steal it into `lopart' */
			if ((lovec->mc_start + lovec->mc_size) == hivec[0].mc_start) {
				hivec[0].mc_start = lovec->mc_start;
				hivec[0].mc_size += lovec->mc_size;
			} else {
				struct mchunk *newvec;
				newvec = (struct mchunk *)merge_realloc(hivec,
				                                        (hicnt + 1) *
				                                        sizeof(struct mchunk),
				                                        orig_part);
				if unlikely(!newvec)
					goto err_async_waitfor;

				/* Make space at the base of the combined vector. */
				memmoveup(&newvec[1], &newvec[0],
				          hicnt, sizeof(struct mchunk));

				/* Insert the original chunk from `lopart' at the front. */
				newvec[0] = *lovec;
				++hicnt;
				hivec = newvec;
			}
			lopart->mp_mem_sc.ms_c = hicnt;
			lopart->mp_mem_sc.ms_v = hivec;
			lopart->mp_state       = MPART_ST_MEM_SC;
		} else {
			/* Both parts already use dynamically allocated merge-vectors. */
			size_t reqcount, loavail, hiavail;
			bool is_adjacent;
			assert(lopart->mp_state == MPART_ST_MEM_SC);
			assert(hipart->mp_state == MPART_ST_MEM_SC);
			is_adjacent = (lovec[locnt - 1].mc_start +
			               lovec[locnt - 1].mc_size) == hivec[0].mc_start;
			reqcount    = locnt + hicnt;
			if (is_adjacent)
				--reqcount;
			loavail = kmalloc_usable_size(lovec) / sizeof(struct mchunk);
			hiavail = kmalloc_usable_size(hivec) / sizeof(struct mchunk);
			if (loavail >= reqcount) {
				/* Just re-use `lovec' */
				if (is_adjacent) {
					--locnt;
					hivec[0].mc_start = lovec[locnt].mc_start;
					hivec[0].mc_size += lovec[locnt].mc_size;
				}

				/* Merge the 2 vectors. */
				memcpy(&lovec[locnt], &hivec[0], hicnt, sizeof(struct mchunk));
				assert(lopart->mp_mem_sc.ms_v == lovec);
				lovec = (struct mchunk *)krealloc_nx(lovec,
				                                     reqcount * sizeof(struct mchunk),
				                                     GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);

				/* Update accounting. */
				if (lovec)
					lopart->mp_mem_sc.ms_v = lovec;
				lopart->mp_mem_sc.ms_c = reqcount;
				kfree(hivec); /* No longer needed */
			} else if (hiavail >= reqcount) {
				/* Insert `lovec' at the front of `hivec' */
				if (is_adjacent) {
					--locnt;
					hivec[0].mc_start = lovec[locnt].mc_start;
					hivec[0].mc_size += lovec[locnt].mc_size;
				}
				memmoveup(&hivec[locnt], &hivec[0], hicnt, sizeof(struct mchunk));
				memcpy(&hivec[0], &lovec[0], locnt, sizeof(struct mchunk));

				/* Update accounting. */
				lopart->mp_mem_sc.ms_c = reqcount;
				lopart->mp_mem_sc.ms_v = hivec;

				/* Try to release unused memory. */
				hivec = (struct mchunk *)krealloc_nx(hivec,
				                                     reqcount * sizeof(struct mchunk),
				                                     GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
				if (hivec)
					lopart->mp_mem_sc.ms_v = hivec;
				kfree(lovec); /* No longer needed */
			} else {
				/* Neither vector is large enough. -> Must realloc one of them! */
				struct mchunk *newvec;
				newvec = (struct mchunk *)krealloc_nx(lovec,
				                                      reqcount * sizeof(struct mchunk),
				                                      GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
				if (newvec) {
					if (is_adjacent) {
						--locnt;
						hivec[0].mc_start = newvec[locnt].mc_start;
						hivec[0].mc_size += newvec[locnt].mc_size;
					}
					memcpy(&newvec[locnt], &hivec[0], hicnt, sizeof(struct mchunk));

					/* Update accounting. */
					lopart->mp_mem_sc.ms_c = reqcount;
					lopart->mp_mem_sc.ms_v = newvec;
					kfree(hivec);
				} else {
					/* Try to realloc `hivec' (may we'll have better luck with it?) */
					newvec = (struct mchunk *)krealloc_nx(hivec,
					                                      reqcount * sizeof(struct mchunk),
					                                      GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
					if unlikely(!newvec) {
						asyncjob_merge_part(orig_part);
						newvec = (struct mchunk *)krealloc_nx(hivec,
						                                      reqcount * sizeof(struct mchunk),
						                                      GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
						if unlikely(!newvec)
							goto err_async_waitfor;
					}
					if (is_adjacent) {
						--locnt;
						newvec[0].mc_start = lovec[locnt].mc_start;
						newvec[0].mc_size += lovec[locnt].mc_size;
					}
					memmoveup(&newvec[locnt], &newvec[0], hicnt, sizeof(struct mchunk));
					memcpy(&newvec[0], &lovec[0], locnt, sizeof(struct mchunk));

					/* Update accounting. */
					lopart->mp_mem_sc.ms_c = reqcount;
					lopart->mp_mem_sc.ms_v = newvec;
					kfree(lovec); /* No longer needed */
				}
			}
		}
#ifndef NDEBUG
		assert(losize == mpart_getsize(lopart));
		assert(hisize == mpart_getsize(hipart));
		assert((lopart->mp_state == MPART_ST_MEM
		        ? (lopart->mp_mem.mc_size * PAGESIZE)
		        : mchunkvec_getsize(lopart->mp_mem_sc.ms_v,
		                            lopart->mp_mem_sc.ms_c)) ==
		       (losize + hisize));
#endif /* !NDEBUG */
	} else if ((lopart->mp_state == MPART_ST_VOID && hipart->mp_state == MPART_ST_VOID) ||
#ifdef LIBVIO_CONFIG_ENABLED
	           (lopart->mp_state == MPART_ST_VIO && hipart->mp_state == MPART_ST_VIO) ||
#endif /* LIBVIO_CONFIG_ENABLED */
	           0) {
		/* Nothing to do here.... */
	} else {
		/* We could still do the following (but choose not to since that would waste memory):
		 *  - If exactly one of the 2 parts is `MPART_ST_VOID', try to allocate its backing data.
		 *  - If either of the 2  parts is MPART_ST_SWP[_SC], bring  the part into the  core,
		 *    using an async read-from-swap operation. Though this operation would  introduce
		 *    the acquisition of non-atomic locks, which in turn would make us a cancellation
		 *    point, which we're not allowed to become. */

		/* Unsupported mem-part-state combination (don't merge) */
		goto err_cannot_merge;
	}

	/* === Point of no return */

	/* Update the maxaddr field of `lopart'. */
	lopart->mp_maxaddr += hisize;

	/* Merge metadata (and transfer futex objects) */
	if (hasmeta) {
		struct mpartmeta *lometa, *himeta;
		lometa = lopart->mp_meta;
		himeta = hipart->mp_meta;
		assert(lometa); /* Was allocated above, if missing. */
#ifdef ARCH_HAVE_RTM
		if (lometa->mpm_rtm_vers < himeta->mpm_rtm_vers)
			lometa->mpm_rtm_vers = himeta->mpm_rtm_vers;
#endif /* ARCH_HAVE_RTM */

		/* Transfer futex objects (if any). */
		if (himeta->mpm_ftx != NULL) {
			struct mfutex *tree;
			tree            = himeta->mpm_ftx;
			himeta->mpm_ftx = NULL;
			mpartmeta_transfer_futex_tree(lometa, tree, lopart, losize);
		}
	}

	/* Update mem-nodes from `hipart' to reference `lopart' at the proper offsets. */
	{
		unsigned int i;
		for (i = 0; i < lengthof(hipart->_mp_nodlsts); ++i) {
			struct mnode *node, *next;
			struct mnode_list *list;
			list = &hipart->_mp_nodlsts[i];
			node = LIST_FIRST(list);
			LIST_INIT(list);
			for (; node; node = next) {
				next = LIST_NEXT(node, mn_link);

				/* Don't fiddle around with nodes that have been unmapped. */
				if likely(!(node->mn_flags & MNODE_F_UNMAPPED) &&
				          !wasdestroyed(node->mn_mman)) {
					/* Update the part/partoff fields of this node. */
					assert(node->mn_part == hipart);
					decref_nokill(hipart);
					node->mn_part = incref(lopart);
					node->mn_partoff += losize;

					/* Re-insert the node into the proper node-list of `lopart' */
					LIST_INSERT_HEAD(&lopart->_mp_nodlsts[i], node, mn_link);
				} else {
					/* Keep this node. */
					LIST_INSERT_HEAD(list, node, mn_link);
				}
			}
		}
	}

	/* Deal with `hipart' having the GLOBAL_REF bit set. */
	if (atomic_fetchand(&hipart->mp_flags, ~MPART_F_GLOBAL_REF) & MPART_F_GLOBAL_REF) {
		if (TAILQ_ISBOUND(lopart, mp_allparts) && !(lopart->mp_flags & MPART_F_GLOBAL_REF)) {
			incref(lopart);
			if unlikely(atomic_fetchor(&lopart->mp_flags, MPART_F_GLOBAL_REF) & MPART_F_GLOBAL_REF)
				decref_nokill(lopart);
		}
		decref_nokill(hipart);
	}

	/* Destroy `hipart' */
	decref_nokill(hipart->mp_file); /* Nokill, because `lopart' still has a REF! */
	DBG_memset(&hipart->mp_mem_sc, 0xcc, sizeof(hipart->mp_mem_sc));
	if (atomic_cmpxch(&hipart->mp_refcnt, 1, 0)) {
		assertf(LIST_EMPTY(&hipart->mp_copy) &&
		        LIST_EMPTY(&hipart->mp_share),
		        "Mem-nodes with the `MNODE_F_UNMAPPED' should use a lock-op "
		        "which in turn should have been holding a reference to this "
		        "part, meaning we would have been unable to decref-to-0!");
		if (hipart->mp_meta)
			mpartmeta_destroy(hipart->mp_meta);
		if (hipart->mp_blkst_ptr != NULL &&
		    !(hipart->mp_flags & MPART_F_BLKST_INL))
			kfree(hipart->mp_blkst_ptr);
		if (TAILQ_ISBOUND(hipart, mp_allparts)) {
			/* Must remove from the global list of all known parts. */
			if (mpart_all_tryacquire()) {
				_mpart_all_list_remove(hipart);
				mpart_all_release();
			} else {
				struct lockop *lop;
				lop          = mpart_destroy_lockop_encode(hipart);
				lop->lo_func = &mpart_destroy_lop_rmall_async;
				lockop_enqueue(&mpart_all_lops, lop);
				_mpart_all_reap();
				goto done_destroy_hipart;
			}
		}
		mpart_free(hipart);
	} else {
		/* Update to reflect all of the data that's been stolen by `lopart' */
		hipart->mp_state   = MPART_ST_VOID;
		hipart->mp_maxaddr = (pos_t)lopart->mp_file->mf_part_amask;
		hipart->mp_minaddr = hipart->mp_maxaddr + 1;
		if (hipart->mp_flags & MPART_F_BLKST_INL) {
			hipart->mp_blkst_ptr = NULL;
			atomic_and(&hipart->mp_flags, ~MPART_F_BLKST_INL);
		} else if (hipart->mp_blkst_ptr != NULL) {
			kfree(hipart->mp_blkst_ptr);
			hipart->mp_blkst_ptr = NULL;
		}
		hipart->mp_file = incref(&mfile_anon[lopart->mp_file->mf_blockshift]);

		/* Important: _ONLY_ re-initialize as anon when the part wasn't anon before!
		 * - This might seen pointless, but `_mpart_init_asanon()' does a little  more
		 *   than ~just~ setting the anon indicator. - It also marks the part as being
		 *   ready to be trimmed.
		 * - In the situation where  the part is currently  being trimmed (such that  it
		 *   is  waiting for  a lock-op,  as set-up  in `mpart_trim_locked_ftx()'), then
		 *   us doing an unconditional init-as-anon would result in the trim-in-progress
		 *   indicator (`hipart->_mp_trmlop_mm.olo_func') being set to `NULL'.
		 * - When `hipart' is also part of a  lock-op pending list (such as the  pending
		 *   list  of an mman), then it won't actually be removed from the pending list,
		 *   but the lockop entry that would (attempted to) be executed would look like:
		 *   >> { olo_link: 0xcccccccc, olo_func: NULL }
		 *   Which obviously causes the kernel to panic.
		 * - By only initializing as anon conditionally if the part wasn't anon  already,
		 *   while also holding a  lock to `hipart', we  prevent all possible data  races
		 *   relating to `mpart_trim()' having been called recently, or even being called
		 *   right now! */
		if (!mpart_isanon(hipart))
			_mpart_init_asanon(hipart);

		/* Don't re-initialize node lists here. These lists may still contain UNMAPPED nodes
		 * which are using lock-ops in order to remove themselves from these lists. As such,
		 * let them do their thing. */
		/*LIST_INIT(&hipart->mp_copy);*/
		/*LIST_INIT(&hipart->mp_share);*/
		if (hipart->mp_meta) {
			/* Increment the RTM version field. This way, anyone that may be
			 * monitoring `hipart' for RTM changes will know that  something
			 * has changed. In this case  that ~something~ isn't the  actual
			 * data, but the  fact that  `hipart' is no  longer the  correct
			 * place to look at when it  comes to RTM version values,  since
			 * `lopart' now serves as the  combined back-bone of itself  and
			 * what used to be `hipart'.
			 * By incrementing the version field, we essentially force any
			 * in-progress RTM operation to be re-started, at which  point
			 * it should then re-run in the context of `lopart'! */
#ifdef ARCH_HAVE_RTM
			++hipart->mp_meta->mpm_rtm_vers;
#endif /* ARCH_HAVE_RTM */
			mpartmeta_ftxlock_endwrite(hipart->mp_meta, hipart);
		}

		/* Release locks from mmans with UNMAPPED mappings to `hipart' */
		mpart_unlock_all_mmans_after(hipart, lopart, NULL, locked_mman);
		mpart_decref_all_mmans(hipart);

		/* Release our lock to the mem-part itself. */
		mpart_assert_integrity(hipart);
		mpart_lock_release(hipart);

		/* Drop the reference that was originally given to us by the caller. */
		decref_unlikely(hipart);
	}
done_destroy_hipart:
	if (!mpart_isanon(lopart))
		mpart_tree_insert(&lopart->mp_file->mf_parts, lopart);
	mpart_assert_integrity(lopart);
	return lopart;

err_async_waitfor:
	/* Restore parts. */
	if (!mpart_isanon(lopart)) {
		mpart_tree_insert(&lopart->mp_file->mf_parts, lopart);
		mpart_tree_insert(&lopart->mp_file->mf_parts, hipart);
		mpart_assert_integrity(lopart);
		mpart_assert_integrity(hipart);
	}
	return MPART_MERGE_ASYNC_WAITFOR;

err_cannot_merge:
	/* Restore parts. */
	if (!mpart_isanon(lopart)) {
		mpart_tree_insert(&lopart->mp_file->mf_parts, lopart);
		mpart_tree_insert(&lopart->mp_file->mf_parts, hipart);
		mpart_assert_integrity(lopart);
		mpart_assert_integrity(hipart);
	}
	return MPART_MERGE_CANNOT_MERGE;
}


/* Same as `mpart_domerge_with_all_locks()', but futex-locks
 * aren't being held, yet, and will not be held upon return. */
PRIVATE NOBLOCK NONNULL((1, 2, 3)) REF struct mpart *
NOTHROW(FCALL mpart_domerge_with_all_locks_noftx)(/*inherit(on_success)*/ REF struct mpart *lopart,
                                                  /*inherit(on_success)*/ REF struct mpart *hipart,
                                                  struct mpart *orig_part,
                                                  struct mman *locked_mman) {
	REF struct mpart *result;
	struct mpartmeta *meta;
	if ((meta = lopart->mp_meta) != NULL) {
		if (!mpartmeta_ftxlock_trywrite(meta)) {
			if (async_waitfor_ftxlck_and_mergepart(lopart, orig_part))
				_mpartmeta_ftxlock_reap(meta, lopart);
			return MPART_MERGE_ASYNC_WAITFOR;
		}
	}
	if ((meta = hipart->mp_meta) != NULL) {
		if (!mpartmeta_ftxlock_trywrite(meta)) {
			if (lopart->mp_meta)
				mpartmeta_ftxlock_endwrite(lopart->mp_meta, lopart);
			if (async_waitfor_ftxlck_and_mergepart(hipart, orig_part))
				_mpartmeta_ftxlock_reap(meta, hipart);
			return MPART_MERGE_ASYNC_WAITFOR;
		}
	}

	/* With all of the locks now held, check one more time if merging is possible. */
	if unlikely(!mpart_canmerge(lopart, hipart, true)) {
		result = MPART_MERGE_CANNOT_MERGE;
	} else {
		/* Do the actual work of merging the 2 parts. */
		result = mpart_domerge_with_all_locks(lopart, hipart,
		                                      orig_part,
		                                      locked_mman);
	}

	/* Release locks... */
	if (result == MPART_MERGE_CANNOT_MERGE ||
	    result == MPART_MERGE_ASYNC_WAITFOR) {
		if ((meta = lopart->mp_meta) != NULL)
			mpartmeta_ftxlock_endwrite(meta, lopart);
		if ((meta = hipart->mp_meta) != NULL)
			mpartmeta_ftxlock_endwrite(meta, hipart);
	} else {
		if ((meta = result->mp_meta) != NULL)
			mpartmeta_ftxlock_endwrite(meta, result);
	}
	return result;
}


/* Merge the 2 given parts.
 *    @assume(WAS_TRUE_AFTER_MMAN_LOCK(mpart_canmerge(lopart, hipart)));
 *    @assume(mpart_lock_acquired(lopart));
 *    @assume(mpart_lock_acquired(hipart));
 *    @assume(mpart_isanon(lopart) == mpart_isanon(hipart));
 *    @assume(mman_lock_acquired(locked_mman));
 * Return a pointer to the newly merged node.
 * @return: * : The merged part. (in  this case, the returned  part
 *              is still locked, but locks to `lopart' and `hipart'
 *              have  been lost; Additionally, references to lopart
 *              and hipart will  have also been  dropped, whilst  a
 *              new reference for a new part is returned)
 * @return: MPART_MERGE_CANNOT_MERGE:  ...
 * @return: MPART_MERGE_ASYNC_WAITFOR: ... */
PRIVATE NOBLOCK NONNULL((1, 2, 3, 4)) REF struct mpart *
NOTHROW(FCALL mpart_domerge_with_mm_lock)(/*inherit(on_success)*/ REF struct mpart *lopart,
                                          /*inherit(on_success)*/ REF struct mpart *hipart,
                                          struct mman *__restrict locked_mman,
                                          struct mpart *orig_part) {
	struct mman *blocking_mman;
	struct mfile *file = NULL;
	REF struct mpart *result;
	assert(lopart->mp_file == hipart->mp_file);
	assert(mpart_isanon(lopart) == mpart_isanon(hipart));

	/* If the parts  are non-anonymous,  then we also  need a  lock
	 * to the associated file, since `mpart_domerge_with_all_locks'
	 * may need to remove/re-insert mem-parts into the file's  tree
	 * of parts when doing the actual job of merging parts. */
	if (!mpart_isanon(lopart)) {
		file = lopart->mp_file;
		if (!mfile_lock_trywrite(file)) {
			/* Must async-merge the 2 parts sometime in the future... */
			if (!async_waitfor_file_and_mergepart(file, orig_part) ||
			    !mfile_lock_trywrite(file))
				return MPART_MERGE_ASYNC_WAITFOR;
		}
	}

	/* Get references to all non-destroyed mmans of the 2 parts. */
	mpart_incref_all_mmans(lopart);
	mpart_incref_all_mmans(hipart);

	/* Try to acquire locks to the set of all of the mmans that are
	 * mapping the copy/share nodes of the 2 mem-parts we intend to
	 * merge.
	 * Note however that we must do some special handling, since we
	 * have to assume that the caller is locking `locked_mman', and
	 * we mustn't try to acquire or release that lock! */
	blocking_mman = mpart_lock_all_mmans(lopart, locked_mman);
	if unlikely(blocking_mman != NULL) {
waitfor_blocking_mman:
		assert(blocking_mman != locked_mman);
		incref(blocking_mman);
		mpart_decref_all_mmans(hipart);
		mpart_decref_all_mmans(lopart);

		/* Release the file-lock from above, if it was acquired. */
		if (file != NULL)
			mfile_lock_endwrite(file);
		if (async_waitfor_mman_and_mergepart(blocking_mman, orig_part))
			_mman_lockops_reap(blocking_mman);
		decref_unlikely(blocking_mman);
		return MPART_MERGE_ASYNC_WAITFOR;
	}
	blocking_mman = mpart_lock_all_mmans_after(hipart, lopart, locked_mman);
	if unlikely(blocking_mman != NULL) {
		mpart_unlock_all_mmans(lopart, NULL, locked_mman);
		goto waitfor_blocking_mman;
	}

	/* Do the actual work of merging the 2 parts. */
	result = mpart_domerge_with_all_locks_noftx(lopart, hipart,
	                                            orig_part,
	                                            locked_mman);

	/* Release the file-lock from above, if it was acquired. */
	if (file != NULL)
		mfile_lock_endwrite(file);

	/* Release locks and drop references... */
	if (result == MPART_MERGE_CANNOT_MERGE ||
	    result == MPART_MERGE_ASYNC_WAITFOR) {
		mpart_unlock_all_mmans_after(hipart, lopart, NULL, locked_mman);
		mpart_unlock_all_mmans(lopart, NULL, locked_mman);
		mpart_decref_all_mmans(hipart);
		mpart_decref_all_mmans(lopart);
	} else {
		/* The newly created mman will have been constructed from
		 * the super-set of nodes from `lopart' and `hipart',  so
		 * we can unlock+decref it instead of the former.
		 * Also: At this point, `lopart' and `hipart' may already
		 *       point  into the void  (iow: have been destroyed) */
		mpart_unlock_all_mmans(result, NULL, locked_mman);
		mpart_decref_all_mmans(result);
	}
	return result;
}


/* Merge the 2 given parts.
 *    @assume(WAS_TRUE_AFTER_FILE_LOCK(mpart_canmerge(lopart, hipart)));
 *    @assume(mpart_lock_acquired(lopart));
 *    @assume(mpart_lock_acquired(hipart));
 *    @assume(mfile_lock_writing(lopart->mp_file));
 *    @assume(lopart->mp_file == hipart->mp_file);
 * Return a pointer to the newly merged node.
 * @return: * : The merged part. (in  this case, the returned  part
 *              is still locked, but locks to `lopart' and `hipart'
 *              have  been lost; Additionally, references to lopart
 *              and hipart will  have also been  dropped, whilst  a
 *              new reference for a new part is returned)
 * @return: MPART_MERGE_CANNOT_MERGE:  ...
 * @return: MPART_MERGE_ASYNC_WAITFOR: ... */
PRIVATE NOBLOCK NONNULL((1, 2, 3)) REF struct mpart *
NOTHROW(FCALL mpart_domerge_with_file_lock)(/*inherit(on_success)*/ REF struct mpart *lopart,
                                            /*inherit(on_success)*/ REF struct mpart *hipart,
                                            struct mpart *orig_part) {
	REF struct mpart *result;
	struct mman *blocking_mman;
	mpart_incref_all_mmans(lopart);
	mpart_incref_all_mmans(hipart);

	/* Try to acquire locks to the set of all of the mmans that are
	 * mapping the copy/share nodes of the 2 mem-parts we intend to
	 * merge. */
	blocking_mman = mpart_lock_all_mmans(lopart);
	if unlikely(blocking_mman != NULL) {
waitfor_blocking_mman:
		incref(blocking_mman);
		mpart_decref_all_mmans(hipart);
		mpart_decref_all_mmans(lopart);
		if (async_waitfor_mman_and_mergepart(blocking_mman, orig_part))
			_mman_lockops_reap(blocking_mman);
		decref_unlikely(blocking_mman);
		return MPART_MERGE_ASYNC_WAITFOR;
	}
	blocking_mman = mpart_lock_all_mmans_after(hipart, lopart);
	if unlikely(blocking_mman != NULL) {
		mpart_unlock_all_mmans(lopart);
		goto waitfor_blocking_mman;
	}

	/* At this point, we're holding a whole bunch of locks:
	 *   - mpart_lock_acquired(lopart);
	 *   - mpart_lock_acquired(hipart);
	 *   - mfile_lock_writing(lopart->mp_file);
	 *   - mfile_lock_writing(hipart->mp_file); // Because `hipart->mp_file == lopart->mp_file'
	 *   - mman_lock_acquired(lopart->mp_copy.each->mn_mman);
	 *   - mman_lock_acquired(lopart->mp_share.each->mn_mman);
	 *   - mman_lock_acquired(hipart->mp_copy.each->mn_mman);
	 *   - mman_lock_acquired(hipart->mp_share.each->mn_mman); */

	/* Do the actual work of merging the 2 parts. */
	result = mpart_domerge_with_all_locks_noftx(lopart, hipart, orig_part, NULL);

	/* Release locks and drop references... */
	if (result == MPART_MERGE_CANNOT_MERGE ||
	    result == MPART_MERGE_ASYNC_WAITFOR) {
		mpart_unlock_all_mmans_after(hipart, lopart);
		mpart_unlock_all_mmans(lopart);
		mpart_decref_all_mmans(hipart);
		mpart_decref_all_mmans(lopart);
	} else {
		/* The newly created mman will have been constructed from
		 * the super-set of nodes from `lopart' and `hipart',  so
		 * we can unlock+decref it instead of the former.
		 * Also: At this point, `lopart' and `hipart' may already
		 *       point  into the void  (iow: have been destroyed) */
		mpart_unlock_all_mmans(result);
		mpart_decref_all_mmans(result);
	}
	return result;
}


struct async_merge_part {
	union {
		Toblockop(mpart)     amp_part_lop;
		Tobpostlockop(mpart) amp_part_post_lop;
		Toblockop(mfile)     amp_file_lop;
		Tobpostlockop(mfile) amp_file_post_lop;
		Toblockop(mman)      amp_mman_lop;
		Tobpostlockop(mman)  amp_mman_post_lop;
	};
	REF struct mpart *amp_mergeme; /* [1..1][const] The part to merge. */
};

/* Called after a lock to `part' becomes available. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_merge_part_post_cb)(Tobpostlockop(mpart) *__restrict self,
                                        struct mpart *__restrict UNUSED(part)) {
	REF struct mpart *merged;
	struct async_merge_part *me;
	me     = container_of(self, struct async_merge_part, amp_part_post_lop);
	merged = me->amp_mergeme; /* Inherit reference */
	kfree(me);
	atomic_and(&merged->mp_xflags, ~MPART_XF_WILLMERGE);
	merged = mpart_merge(merged);
	decref_unlikely(merged);
}

PRIVATE NOBLOCK NONNULL((1)) Tobpostlockop(mpart) *
NOTHROW(FCALL async_merge_part_cb)(Toblockop(mpart) *__restrict self,
                                   struct mpart *__restrict UNUSED(part)) {
	struct async_merge_part *me;
	me = container_of(self, struct async_merge_part, amp_part_lop);
	me->amp_part_post_lop.oplo_func = &async_merge_part_post_cb;
	return &me->amp_part_post_lop;
}

/* Wait for `part_to_wait' to become available, after which point
 * in time, try to merge `part_to_merge' with its neighbors. This
 * will  be done as  per `mpart_merge(part_to_merge)'. The caller
 * must try to reap lockops of `part_to_wait' after calling  this
 * function! */
PRIVATE NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL async_waitfor_part_and_mergepart)(struct mpart *part_to_wait,
                                                struct mpart *part_to_merge) {
	struct async_merge_part *lop;
	if (atomic_fetchor(&part_to_merge->mp_xflags, MPART_XF_WILLMERGE) & MPART_XF_WILLMERGE)
		return false;
	lop = (struct async_merge_part *)merge_malloc(sizeof(struct async_merge_part), part_to_merge);
	if (!lop)
		return false; /* Merging will be done asynchronously. */

	/* Insert the newly created lock-op. */
	lop->amp_mergeme           = incref(part_to_merge);
	lop->amp_part_lop.olo_func = &async_merge_part_cb;
	oblockop_enqueue(&part_to_wait->mp_lockops,
	                 &lop->amp_part_lop);
	return true;
}

/* Called after a lock to `part->mp_meta->mpm_ftxlock' becomes available. */
#if 1
#define async_merge_ftxlck_post_cb async_merge_part_post_cb
#define async_merge_ftxlck_cb      async_merge_part_cb
#else
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_merge_ftxlck_post_cb)(Tobpostlockop(mpart) *__restrict self,
                                          struct mpart *__restrict UNUSED(part)) {
	REF struct mpart *merged;
	struct async_merge_part *me;
	me     = container_of(self, struct async_merge_part, amp_file_post_lop);
	merged = me->amp_mergeme; /* Inherit reference */
	kfree(me);
	atomic_and(&merged->mp_xflags, ~MPART_XF_WILLMERGE);
	merged = mpart_merge(merged);
	decref_unlikely(merged);
}

PRIVATE NOBLOCK NONNULL((1)) Tobpostlockop(mpart) *
NOTHROW(FCALL async_merge_ftxlck_cb)(Toblockop(mpart) *__restrict self,
                                     struct mpart *__restrict UNUSED(part)) {
	struct async_merge_part *me;
	me = container_of(self, struct async_merge_part, amp_part_lop);
	me->amp_part_post_lop.oplo_func = &async_merge_ftxlck_post_cb;
	return &me->amp_part_post_lop;
}
#endif

/* Same as `async_waitfor_part_and_mergepart()', but wait for a given futex-lock. */
PRIVATE NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL async_waitfor_ftxlck_and_mergepart)(struct mpart *part_to_wait,
                                                  struct mpart *part_to_merge) {
	struct async_merge_part *lop;
	if (atomic_fetchor(&part_to_merge->mp_xflags, MPART_XF_WILLMERGE) & MPART_XF_WILLMERGE)
		return false;
	lop = (struct async_merge_part *)merge_malloc(sizeof(struct async_merge_part), part_to_merge);
	if (!lop)
		return false; /* Merging will be done asynchronously. */

	/* Insert the newly created lock-op. */
	lop->amp_mergeme           = incref(part_to_merge);
	lop->amp_part_lop.olo_func = &async_merge_ftxlck_cb;
	oblockop_enqueue(&part_to_wait->mp_meta->mpm_ftxlops,
	                 &lop->amp_part_lop);
	return true;
}


/* Called after a lock to `file' becomes available. */
#if 1
static_assert(offsetof(struct async_merge_part, amp_file_post_lop) ==
              offsetof(struct async_merge_part, amp_part_post_lop));
#define async_merge_file_post_cb \
	(*(Tobpostlockop_callback_t(mfile))&async_merge_part_post_cb)
#define async_merge_file_cb \
	(*(Toblockop_callback_t(mfile))&async_merge_part_cb)
#else
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_merge_file_post_cb)(Tobpostlockop(mfile) *__restrict self,
                                        struct mfile *__restrict UNUSED(file)) {
	REF struct mpart *merged;
	struct async_merge_part *me;
	me     = container_of(self, struct async_merge_part, amp_file_post_lop);
	merged = me->amp_mergeme; /* Inherit reference */
	kfree(me);
	atomic_and(&merged->mp_xflags, ~MPART_XF_WILLMERGE);
	merged = mpart_merge(merged);
	decref_unlikely(merged);
}

PRIVATE NOBLOCK NONNULL((1)) Tobpostlockop(mfile) *
NOTHROW(FCALL async_merge_file_cb)(Toblockop(mfile) *__restrict self,
                                   struct mfile *__restrict UNUSED(file)) {
	struct async_merge_part *me;
	me = container_of(self, struct async_merge_part, amp_file_lop);
	me->amp_file_post_lop.oplo_func = &async_merge_file_post_cb;
	return &me->amp_file_post_lop;
}
#endif

/* Same as `async_waitfor_part_and_mergepart()', but wait for a given file. */
PRIVATE NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL async_waitfor_file_and_mergepart)(struct mfile *file_to_wait,
                                                struct mpart *part_to_merge) {
	struct async_merge_part *lop;
	if (atomic_fetchor(&part_to_merge->mp_xflags, MPART_XF_WILLMERGE) & MPART_XF_WILLMERGE)
		return false;
	lop = (struct async_merge_part *)merge_malloc(sizeof(struct async_merge_part), part_to_merge);
	if (!lop)
		return false; /* Merging will be done asynchronously. */

	/* Insert the newly created lock-op. */
	lop->amp_mergeme           = incref(part_to_merge);
	lop->amp_file_lop.olo_func = &async_merge_file_cb;
	oblockop_enqueue(&file_to_wait->mf_lockops,
	                 &lop->amp_file_lop);
	return true;
}


/* Called after a lock to `mm' becomes available. */
#if 1
static_assert(offsetof(struct async_merge_part, amp_mman_post_lop) ==
              offsetof(struct async_merge_part, amp_part_post_lop));
#define async_merge_mman_post_cb \
	(*(Tobpostlockop_callback_t(mman))&async_merge_part_post_cb)
#define async_merge_mman_cb \
	(*(Toblockop_callback_t(mman))&async_merge_part_cb)
#else
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_merge_mman_post_cb)(Tobpostlockop(mman) *__restrict self,
                                        struct mman *__restrict UNUSED(mm)) {
	REF struct mpart *merged;
	struct async_merge_part *me;
	me     = container_of(self, struct async_merge_part, amp_mman_post_lop);
	merged = me->amp_mergeme; /* Inherit reference */
	kfree(me);
	atomic_and(&merged->mp_xflags, ~MPART_XF_WILLMERGE);
	merged = mpart_merge(merged);
	decref_unlikely(merged);
}

PRIVATE NOBLOCK NONNULL((1)) Tobpostlockop(mman) *
NOTHROW(FCALL async_merge_mman_cb)(Toblockop(mman) *__restrict self,
                                   struct mman *__restrict UNUSED(mm)) {
	struct async_merge_part *me;
	me = container_of(self, struct async_merge_part, amp_mman_lop);
	me->amp_mman_post_lop.oplo_func = &async_merge_mman_post_cb;
	return &me->amp_mman_post_lop;
}
#endif

/* Same as `async_waitfor_part_and_mergepart()', but wait for a given mman. */
PRIVATE NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL async_waitfor_mman_and_mergepart)(struct mman *mman_to_wait,
                                                struct mpart *part_to_merge) {
	struct async_merge_part *lop;
	if (atomic_fetchor(&part_to_merge->mp_xflags, MPART_XF_WILLMERGE) & MPART_XF_WILLMERGE)
		return false;
	lop = (struct async_merge_part *)merge_malloc(sizeof(struct async_merge_part), part_to_merge);
	if (!lop)
		return false; /* Merging will be done asynchronously. */

	/* Insert the newly created lock-op. */
	lop->amp_mergeme           = incref(part_to_merge);
	lop->amp_mman_lop.olo_func = &async_merge_mman_cb;
	oblockop_enqueue(&FORMMAN(mman_to_wait, thismman_lockops),
	                 &lop->amp_mman_lop);
	return true;
}



/* Same as `mpart_merge()',  but the caller  is holding a  lock
 * to `self' upon entry, and will be holding a lock to `return'
 * upon exit. */
PUBLIC NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mpart *
NOTHROW(FCALL mpart_merge_locked)(REF struct mpart *__restrict self) {
	assert(mpart_lock_acquired(self));
	if (!mpart_isanon(self)) {
		struct mpart *merged, *neighbor;
		struct mfile *file = self->mp_file;
		if (!mfile_lock_trywrite(file)) {
			/* Enqueue a lockop for `file' that will cause
			 * that file to  service _all_  of the  file's
			 * mem-parts when executed. */
			if (async_waitfor_file_and_mergepart(file, self))
				_mfile_lockops_reap(file);
			return self;
		}

		/* Search for adjacent mem-parts. */
		if ((neighbor = mpart_tree_prevnode(self)) != NULL && tryincref(neighbor)) {
			if (!mpart_canmerge(neighbor, self, false)) {
				/* Cannot merge... */
				decref_unlikely(neighbor);
			} else if (!mpart_lock_tryacquire(neighbor)) {
				bool mustreap;
				mustreap = async_waitfor_part_and_mergepart(neighbor, self);
				mfile_lock_endwrite_f(file);
				if (mustreap)
					_mpart_lockops_reap(neighbor);
				decref_unlikely(neighbor);
				mfile_lockops_reap(file);
				return self;
			} else {
				/* Try to merge the 2 parts. */
				merged = mpart_domerge_with_file_lock(neighbor, self, self);
				if (merged == MPART_MERGE_CANNOT_MERGE ||
				    merged == MPART_MERGE_ASYNC_WAITFOR) {
					mpart_lock_release(neighbor);
					if (merged == MPART_MERGE_ASYNC_WAITFOR) {
						/* The  rest of the merge operation will
						 * happen asynchronously. - So return to
						 * the  caller now, and deal with all of
						 * that async stuff later. */
						mfile_lock_endwrite_f(file);
						decref_unlikely(neighbor);
						mfile_lockops_reap(file);
						return self;
					}
					decref_unlikely(neighbor);
				} else {
					/* Success: references & locks to `neighbor' & `self' were inherited. */
					self = merged;
				}
			}
		}

		if ((neighbor = mpart_tree_nextnode(self)) != NULL && tryincref(neighbor)) {
			if (!mpart_canmerge(self, neighbor, false)) {
				/* Cannot merge... */
				decref_unlikely(neighbor);
			} else if (!mpart_lock_tryacquire(neighbor)) {
				bool mustreap;
				mustreap = async_waitfor_part_and_mergepart(neighbor, self);
				mfile_lock_endwrite_f(file);
				if (mustreap)
					_mpart_lockops_reap(neighbor);
				decref_unlikely(neighbor);
				mfile_lockops_reap(file);
				return self;
			} else {
				/* Try to merge the 2 parts. */
				merged = mpart_domerge_with_file_lock(self, neighbor, self);
				if (merged == MPART_MERGE_CANNOT_MERGE ||
				    merged == MPART_MERGE_ASYNC_WAITFOR) {
					mpart_lock_release(neighbor);
					if (merged == MPART_MERGE_ASYNC_WAITFOR) {
						/* The  rest of the merge operation will
						 * happen asynchronously. - So return to
						 * the  caller now, and deal with all of
						 * that async stuff later. */
						mfile_lock_endwrite_f(file);
						decref_unlikely(neighbor);
						mfile_lockops_reap(file);
						return self;
					}
					decref_unlikely(neighbor);
				} else {
					/* Success: references & locks to `neighbor' & `self' were inherited. */
					self = merged;
				}
			}
		}
		mfile_lock_endwrite(file);
	}

	/* If `self' could be merged successfully, then we must also try
	 * to merge all of the mem-nodes that map the (now-merged) part. */
	self = mpart_trymerge_nodes(self);
	return self;
}


/* Try to merge `self' with neighboring parts from the associated file.
 * @return: * : A pointer to the (possibly merged) mem-part. */
PUBLIC NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mpart *
NOTHROW(FCALL mpart_merge)(REF struct mpart *__restrict self) {
	if (mpart_lock_tryacquire(self)) {
domerge_locked:
		self = mpart_merge_locked(self);
		mpart_assert_integrity(self);
		mpart_lock_release(self);
	} else {
		/* Enqueue a lockop to eventually merge `self'
		 * once  the lock to `self' becomes available. */
		if (async_waitfor_part_and_mergepart(self, self)) {
			/* Must try to reap lockops (though we may just
			 * as well also try to acquire the lock  again) */
			if (mpart_lock_tryacquire(self))
				goto domerge_locked;
		}
	}
	return self;
}

#else /* CONFIG_HAVE_KERNEL_MNODE_MERGE */

/* Same as `mnode_merge()', but the  caller must also be holding  a
 * lock to `self->mn_part' (which may  be assumed to be  non-NULL).
 * Upon return, the lock to `self->mn_part' may have been released,
 * because of which case the caller  must alway inherits a lock  to
 * `return->mn_part'. */
PUBLIC NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) struct mnode *
NOTHROW(FCALL mnode_merge_with_partlock)(struct mnode *__restrict self) {
	/* No-op */
	COMPILER_IMPURE();
	return self;
}


/* While  holding a lock  to `self->mn_mman', try to  merge the given node
 * with its successor/predecessor node, without releasing the lock to  the
 * associated mman. If it is found that `self' is mergeable, but that this
 * cannot be done  without blocking, `self->mn_mman'  is set-up such  that
 * the merge operation will be performed asynchronously.
 * @return: * : The new, merged node (which may have a different min-addr
 *              that the original node `self'). Also note that this  node
 *              may or may not be equal to `self', and that it's min- and
 *              max-addr fields may be  different from those that  `self'
 *              had upon entry, irregardless of `self' being re-returned.
 *              As  a matter of fact `*self' becomes invalid after a call
 *              to this function! */
DEFINE_PUBLIC_ALIAS(mnode_merge, mnode_merge_with_partlock);


/* Mark the given mman as potentially containing mergeable  mem-nodes.
 * These nodes will (eventually) be merged asynchronously, but may not
 * be merged immediately (though they might be merged immediately).
 * NOTE: The caller isn't required to be holding a lock to `self', but
 *       if they are, this function is still going to be non-blocking,
 *       and the node-merging process  will simply happen _after_  the
 *       caller releases their lock. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mman_mergenodes)(struct mman *__restrict self) {
	/* No-op */
	COMPILER_IMPURE();
	(void)self;
}


/* Same as `mman_mergenodes()', but the caller _must_ be holding a lock
 * to the given mman `self'! */
DEFINE_PUBLIC_ALIAS(mman_mergenodes_locked, mman_mergenodes);


/* Helper wrapper to try to merge all nodes within the given range. The
 * caller must be holding a lock to `self' when calling this  function. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mman_mergenodes_inrange)(struct mman *__restrict self,
                                       void const *minaddr,
                                       void const *maxaddr) {
	/* No-op */
	COMPILER_IMPURE();
	(void)self;
	(void)minaddr;
	(void)maxaddr;
}


/* Same as `mpart_merge()',  but the caller  is holding a  lock
 * to `self' upon entry, and will be holding a lock to `return'
 * upon exit. */
DEFINE_PUBLIC_ALIAS(mpart_merge_locked, mnode_merge_with_partlock);


/* Try to merge `self' with neighboring parts from the associated file.
 * @return: * : A pointer to the (possibly merged) mem-part. */
DEFINE_PUBLIC_ALIAS(mpart_merge, mnode_merge_with_partlock);

#endif /* !CONFIG_HAVE_KERNEL_MNODE_MERGE */

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MNODE_MERGE_C */
