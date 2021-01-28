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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_FORK_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_FORK_C 1
#define _KOS_SOURCE 1
#define __WANT_MNODE__mn_alloc

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/printk.h> /* TODO: REMOVE_ME */
#include <kernel/paging.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <kos/except.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

/* Mask of mnode flags copied during fork() */
#define MNODE_FLAGS_FORKMASK (~(MNODE_F_COREPART))

/* Because you're not allowed to fork the kernel mman, we never have to
 * check for pending lock-operations, since those are only supposed for
 * the kernel mman. As such, we should never have to reap anything! */
#undef mman_lock_release
#define mman_lock_release mman_lock_release_f

DECL_BEGIN

#ifndef NDEBUG
#define DBG_memset(dst, byte, num_bytes) memset(dst, byte, num_bytes)
#else /* !NDEBUG */
#define DBG_memset(dst, byte, num_bytes) (void)0
#endif /* NDEBUG */



/*
 * === Bad ideas (and why they're bad) ===
 *
 * pagedir_fork:
 *    Use the `v_unused*_ign' bits of the entries of all of the
 *    dynamically allocated vectors within the page directory
 *    as a data-stream to encode a reference counter for the
 *    surrounding page-vector. (s.a. `p32_pagedir_refe2_incref')
 *
 * >> // Initialize `self' as a fork-copy of the current page directory:
 * >> //   - Initialize kernel-space of `self' completely normal.
 * >> //   - Clear the WRITABLE bit for all user-space pages
 * >> //   - (try to) increment the reference counter for all currently
 * >> //     allocated vectors in `P32_PDIR_E2_IDENTITY'. Where this is
 * >> //     impossible (due to a refcnt overflow), a hard copy of the
 * >> //     associated vector is made.
 * >> INTDEF NOBLOCK NONNULL((1)) void
 * >> NOTHROW(FCALL p32_pagedir_fork)(VIRT struct p32_pdir *__restrict self,
 * >>                                 PHYS struct p32_pdir *phys_self);
 * >> 
 * >> // Reference counter control for `P32_PDIR_E2_IDENTITY[vec2]'
 * >> // NOTE: Reference counting is implemented by combining the `d_unused1_ign'
 * >> //       fields of all of the E1-entires pointed to by the indexed E2-vector.
 * >> INTDEF NOBLOCK __BOOL NOTHROW(FCALL p32_pagedir_refe2_incref)(unsigned int vec2); // true: OK; false: Failed to incref
 * >> INTDEF NOBLOCK __BOOL NOTHROW(FCALL p32_pagedir_refe2_decref)(unsigned int vec2); // true: OK; false: Last ref has gone away (you must free the vector now)
 * >> INTDEF NOBLOCK __BOOL NOTHROW(FCALL p32_pagedir_refe2_isshrd)(unsigned int vec2); // true: At least 2 references; false: 1 reference
 *
 * BAD: Is this really something that would make sense? After all:
 *      all of the page directory initialization on `newmm' will
 *      already happen completely lazily, and the intended use of
 *      fork() is to-be followed by an exec(), meaning that it
 *      doesn't actually make that much sense to not just do what
 *      the old VM system did; even in regards to how to implement
 *      exec... (i.e. don't create a new mman on exec, but use the
 *      `struct mbuilder' system and `mbuilder_apply()')
 *
 */




struct forktree_data {
	struct mnode      *ftd_newtree;  /* [0..n] New tree of nodes (not a valid R/B-tree until everything has been forked) */
	struct mman       *ftd_oldmm;    /* [1..1] The old (to-be fork(2)'d) mman. */
	struct mman       *ftd_newmm;    /* [1..1] The new (target) mman */
	struct mnode_slist ftd_freelist; /* [0..n] List of free mem-nodes */
	bool               ftd_didulock; /* Set to true if `ftd_newmm' was ever unlocked. */
};


INTDEF NOBLOCK NONNULL((1, 2)) struct mpart_postlockop * /* from "mnode.c" */
NOTHROW(FCALL mnode_unlink_from_part_lockop)(struct mpart_lockop *__restrict self,
                                             struct mpart *__restrict part);
INTDEF NOBLOCK NONNULL((1)) void /* from "mnode.c" */
NOTHROW(FCALL mpart_maybe_clear_mlock)(struct mpart *__restrict self);

/* Destroy the given `node', but (try to) re-use it by adding it to `ftd_freelist' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL forktree_mnode_destroy)(struct forktree_data *__restrict self,
                                      struct mnode *__restrict node) {
	REF struct mpart *part;
	assert(!(node->mn_flags & MNODE_F_COREPART));
	xdecref_unlikely(node->mn_fspath);
	xdecref_unlikely(node->mn_fsname);
	if ((part = node->mn_part) != NULL) {
		/* Try to unlink the node from the copy- or share-chain of the associated part. */
		if (mpart_lock_tryacquire(part)) {
			LIST_REMOVE(node, mn_link);
			if ((node->mn_flags & (MNODE_F_MLOCK)) &&
			    (part->mp_flags & (MPART_F_MLOCK | MPART_F_MLOCK_FROZEN)) == MPART_F_MLOCK)
				mpart_maybe_clear_mlock(part);
			mpart_lock_release(part);
			decref_unlikely(part);
		} else {
			struct mpart_lockop *lop;

			/* Let the mem-part know that this node has been unmapped. */
			ATOMIC_OR(node->mn_flags, MNODE_F_UNMAPPED);

			/* Must insert the node into the part's list of deleted nodes. */
			weakincref(node->mn_mman); /* A weak reference here is required by the ABI */
			DBG_memset(&node->mn_part, 0xcc, sizeof(node->mn_part));

			/* Insert into the lock-operations list of `part'
			 * The act of doing this is what essentially causes
			 * ownership of our node to be transfered to `part' */
			lop = (struct mpart_lockop *)node;
			lop->mplo_func = &mnode_unlink_from_part_lockop;
			SLIST_ATOMIC_INSERT(&part->mp_lockops, lop, mplo_link);

			/* Try to reap dead nodes. */
			_mpart_deadnodes_reap(part);

			/* Drop our old reference to the associated part. */
			decref(part);
			return;
		}
	}

	/* Insert into the free-list to allow for fast object-reuse. */
	SLIST_INSERT(&self->ftd_freelist, node, _mn_alloc);
}


PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL forktree_insert_into_newmm)(struct forktree_data *__restrict self,
                                          struct mnode *__restrict root) {
	struct mnode *lhs, *rhs;
	struct mman *newmm;
again:
	lhs   = root->mn_mement.rb_lhs;
	rhs   = root->mn_mement.rb_rhs;
	newmm = self->ftd_newmm;
	for (;;) {
		struct mnode *oldnode;
		oldnode = mnode_tree_rremove(&newmm->mm_mappings,
		                             root->mn_minaddr,
		                             root->mn_maxaddr);
		if likely(!oldnode)
			break;
		if (oldnode != &FORMMAN(newmm, thismman_kernel_reservation))
			forktree_mnode_destroy(self, oldnode);
	}

	/* Insert `root' into the tree. */
	mnode_tree_insert(&newmm->mm_mappings, root);

	/* Recursively traverse the entire tree. */
	if (lhs) {
		if (rhs)
			forktree_insert_into_newmm(self, rhs);
		root = lhs;
		goto again;
	}
	if (rhs) {
		root = rhs;
		goto again;
	}
}

/* Ensure that `self->ftd_newmm->mm_mappings' is a valid tree of mem-nodes
 * by inserting all nodes from the incomplete tree `ftd_newtree' into the
 * actual mappings tree of that mman. Where an overlap is found, the existing
 * node is removed from `self->ftd_newmm' will be destroyed. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL forktree_unlock_newmm)(struct forktree_data *__restrict self) {
	struct mman *newmm;
	newmm = self->ftd_newmm;

	/* Like the description says. But make sure not to free the kernel-reserve node! */
	if (self->ftd_newtree != NULL)
		forktree_insert_into_newmm(self, self->ftd_newtree);
	DBG_memset(&self->ftd_newtree, 0xcc, sizeof(self->ftd_newtree));

	/* Make sure that `thismman_kernel_reservation' is apart of the tree. */
	{
		struct mnode *node;
		node = mnode_tree_rlocate(newmm->mm_mappings,
		                          FORMMAN(newmm, thismman_kernel_reservation).mn_minaddr,
		                          FORMMAN(newmm, thismman_kernel_reservation).mn_maxaddr);
		assert(!node || node == &FORMMAN(newmm, thismman_kernel_reservation));
		if (!node)
			mnode_tree_insert(&newmm->mm_mappings, &FORMMAN(newmm, thismman_kernel_reservation));
	}

	/* Release our lock to the new mman. */
	mman_lock_release(newmm);
}



/* Helper functions to replicate a tree of memory mappings for the purpose
 * of forking a memory manager:
 *  - While holding a lock to both `ftd_newmm', as well as `ftd_oldmm',
 *    try to fork the given `oldtree' of mem-nodes into a copy that will be
 *    stored in `*p_newtree'.
 *  - When `oldtree' is `NULL', simply set `*p_newtree' to `NULL'.
 *  - Otherwise, use `mnode_tree_rremove()' on `ftd_newmm->mm_mappings'
 *    to try to remove a mem-node already duplicated during a prior call, in
 *    which case check that attributes (flags, min/max-addr, part, partoff,
 *    fsname, fspath) are still up to date. If so, then simply set `*p_newtree'
 *    to that previously duplicated node, and continue replicating the child-
 *    nodes of `oldtree'
 *  - Otherwise, a new mem-node will be allocated (preferrably via `ftd_freelist')
 *    and initialized to replicate `oldtree' (for this purpose, a lock to the
 *    backing part of `oldtree' will also be acquired, so that the new mem-node
 *    can be added to the part's list of copy- or share-nodes).
 *    Afterwards, all sub-trees of `oldtree' will be forked recursively:
 *    >> forktree_or_unlock(self, &(*p_newtree)->mn_mement.rb_lhs, oldtree->mn_mement.rb_lhs);
 *    >> forktree_or_unlock(self, &(*p_newtree)->mn_mement.rb_rhs, oldtree->mn_mement.rb_rhs);
 * @return: true:  Success
 * @return: false: Failure: A mem-node could not be allocated atomically, or a lock
 *                 to a mem-part could not be acquired immediately), a lock to `ftd_oldmm'
 *                 and `ftd_newmm' is released (the later by using `forktree_unlock_newmm',
 *                 which will merge all nodes from `self->ftd_newtree' into `ftd_newmm's
 *                 tree of mappings), and:
 *                   - A new mem-node is allocated w/ blocking, and added to `freelist'
 *                   - Keep on yielding until the locked part becomes available
 *                 -> The caller must then re-acquire locks and try again */
PRIVATE NONNULL((1, 2)) bool FCALL
forktree_or_unlock(struct forktree_data *__restrict self,
                   struct mnode **__restrict p_newtree,
                   struct mnode *newtree_parent,
                   struct mnode *oldtree) {
	struct mnode *newtree;
	struct mpart *part;
	if (!oldtree) {
		/* Super simple case... */
		*p_newtree = NULL;
		return true;
	}

again:
	/* Check if there is a pre-existing node at this address. */
	newtree = mnode_tree_rremove(&self->ftd_newmm->mm_mappings,
	                             oldtree->mn_minaddr,
	                             oldtree->mn_maxaddr);
	if (newtree) {
		/* Check if same features. */
		if (newtree->mn_minaddr == oldtree->mn_minaddr &&
		    newtree->mn_maxaddr == oldtree->mn_maxaddr &&
		    newtree->mn_part == oldtree->mn_part &&
		    newtree->mn_fsname == oldtree->mn_fsname &&
		    newtree->mn_fspath == oldtree->mn_fspath &&
		    (newtree->mn_flags & ~(~MNODE_FLAGS_FORKMASK | MNODE_F__RBRED)) ==
		    (oldtree->mn_flags & ~(~MNODE_FLAGS_FORKMASK | MNODE_F__RBRED))) {
			/* Always inherit the _RBRED flag (since we're trying to re-
			 * construct the old mman's R/B-tree of memory mappings). */
			newtree->mn_flags &= ~MNODE_F__RBRED;
			newtree->mn_flags |= oldtree->mn_flags & MNODE_F__RBRED;
			goto continue_after_fork_newtree; /* Can re-use this node! */
		}
		assert(newtree != &FORMMAN(self->ftd_newmm, thismman_kernel_reservation));
		/* Different nodes -> Delete the pre-existing, overlapping node. */
		forktree_mnode_destroy(self, newtree);
		goto again;
	}
	assertf(oldtree != &FORMMAN(self->ftd_oldmm, thismman_kernel_reservation),
	        "This should have been handled by the `mnode_tree_rremove()' above!");

	/* Must actually create a new copy of `oldtree'. For this purpose,
	 * start by trying to allocate a new node from the free-list. */
	newtree = SLIST_FIRST(&self->ftd_freelist);
	if (newtree) {
		SLIST_REMOVE_HEAD(&self->ftd_freelist, _mn_alloc);
	} else {
		/* Must use kmalloc_nx+GFP_LOCKED */
		newtree = (struct mnode *)kmalloc_nx(sizeof(struct mnode),
		                                     GFP_ATOMIC | GFP_LOCKED |
		                                     GFP_PREFLT);
		if (!newtree) {
			/* Must blocking-allocate a new mem-part. */
			mman_lock_release(self->ftd_oldmm);
			forktree_unlock_newmm(self);
			newtree = (struct mnode *)kmalloc(sizeof(struct mnode),
			                                  GFP_LOCKED | GFP_PREFLT);
			/* Add to the free list so we've got the node
			 * pre-allocated the next time around! */
			SLIST_INSERT(&self->ftd_freelist, newtree, _mn_alloc);
			return false;
		}
	}
	
	/* Initialize fields of `newtree' as a copy of `oldtree'. */
	part                 = oldtree->mn_part;
	newtree->mn_minaddr  = oldtree->mn_minaddr;
	newtree->mn_maxaddr  = oldtree->mn_maxaddr;
	newtree->mn_flags    = oldtree->mn_flags & MNODE_FLAGS_FORKMASK;
	newtree->mn_part     = part;               /* incref'd below... */
	newtree->mn_fspath   = oldtree->mn_fspath; /* incref'd below... */
	newtree->mn_fsname   = oldtree->mn_fsname; /* incref'd below... */
	newtree->mn_mman     = self->ftd_newmm;
	newtree->mn_partoff  = oldtree->mn_partoff;
	LIST_ENTRY_UNBOUND_INIT(&newtree->mn_writable);
	newtree->_mn_module = NULL;

	if (part) {
		struct mnode_list *list;
		incref(part); /* The reference stored in `newtree->mn_part' */

		/* Acquire a lock to `part' */
		if (!mpart_lock_tryacquire(part)) {
			mman_lock_release(self->ftd_oldmm);
			forktree_unlock_newmm(self);
			FINALLY_DECREF_UNLIKELY(part); /* The reference from `newtree->mn_part' */
			/* Must blocking-wait for the part to become available. */
			do {
				task_serve();
				task_yield();
			} while (!mpart_lock_available(part));
			return false;
		}

		/* Add `newtree' to the relevant node-list. */
		list = (newtree->mn_flags & MNODE_F_SHARED) ? &part->mp_share : &part->mp_copy;
		LIST_INSERT_HEAD(list, newtree, mn_link);

		/* Release the lock to `part'. */
		mpart_lock_release(part);
	} else {
		/* Simple case: just clone a memory reservation node. */
		DBG_memset(&newtree->mn_link, 0xcc, sizeof(newtree->mn_link));
	}

	/* Create references for filesystem name objects. */
	xincref(newtree->mn_fspath);
	xincref(newtree->mn_fsname);
continue_after_fork_newtree:
	/* Insert the `newtree' node into the tree we're currently building. */
	*p_newtree                = newtree;
	newtree->mn_mement.rb_par = newtree_parent;
	newtree->mn_mement.rb_lhs = NULL;
	newtree->mn_mement.rb_rhs = NULL;
	/* Recursion... */
	if (oldtree->mn_mement.rb_lhs) {
		if (!forktree_or_unlock(self,
		                        &newtree->mn_mement.rb_rhs,
		                        newtree, oldtree->mn_mement.rb_rhs))
			return false;
		newtree_parent = newtree;
		oldtree        = oldtree->mn_mement.rb_lhs;
		p_newtree      = &newtree->mn_mement.rb_lhs;
		goto again;
	}
	if (oldtree->mn_mement.rb_rhs) {
		newtree_parent = newtree;
		oldtree        = oldtree->mn_mement.rb_rhs;
		p_newtree      = &newtree->mn_mement.rb_rhs;
		goto again;
	}
	return true;
}


/* Destroy all nodes from a given R/B-tree of mem-nodes. */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL forktree_freeall)(struct forktree_data *__restrict self,
                                struct mnode *__restrict root) {
	struct mnode *lhs, *rhs;
again:
	lhs = root->mn_mement.rb_lhs;
	rhs = root->mn_mement.rb_rhs;
	forktree_mnode_destroy(self, root);
	if (lhs) {
		if (rhs)
			forktree_freeall(self, rhs);
		root = lhs;
		goto again;
	}
	if (rhs) {
		root = rhs;
		goto again;
	}
}



/* Free all mem-nodes from the given free-list. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mnode_slist_freeall)(struct mnode_slist *__restrict self) {
	struct mnode *node;
	for (node = SLIST_FIRST(self); unlikely(node);) {
		struct mnode *next;
		next = SLIST_NEXT(node, _mn_alloc);
		kfree(node);
		node = next;
	}
}



/* Delete write-attempt from all writable user-space mem-nodes. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL forktree_clearwrite)(struct mman *__restrict mm) {
	struct mnode *iter;
	if (LIST_EMPTY(&mm->mm_writable))
		return;
	iter = LIST_FIRST(&mm->mm_writable);
	LIST_INIT(&mm->mm_writable);
	for (;;) {
		struct mnode *next;
		void *addr;
		size_t size;
		printk(KERN_TRACE "[mm] fork: delete write-access to %p-%p\n",
		       mnode_getminaddr(iter), mnode_getmaxaddr(iter));
		next = LIST_NEXT(iter, mn_writable);
		LIST_ENTRY_UNBOUND_INIT(&iter->mn_writable);
		addr = mnode_getaddr(iter);
		size = mnode_getsize(iter);
		/* Need to prepare the pagedir for the unwrite first. If this call fails,
		 * then simply throw an exception, which our caller will then handle for us.
		 * But also note that we must first unlock the old and new mman */
		if (!pagedir_prepare_map(addr, size)) {
			/* Kill the ant with a shotgun, and just unmap everything. */
			pagedir_unmap_userspace();
			iter = next;
			while (iter) {
				next = LIST_NEXT(iter, mn_writable);
				LIST_ENTRY_UNBOUND_INIT(&iter->mn_writable);
				iter = next;
			}
			goto done;
		}
		pagedir_unwrite(addr, size);
		pagedir_unprepare_map(addr, size);
		if (!next)
			break;
		iter = next;
	}
	/* After clearing all of those write-permissions, we must sync the
	 * current (i.e. copied) mman to ensure that no-one is writing to
	 * any of the (now shared) pages.
	 * Following this call, any further modifications made to the memory
	 * of the old mman will be unshared from the new mman (i.e. will no
	 * longer appear in both page directories) */
done:
#if 1 /* !!!FIXME!!! (high priority): It seems as though `pagedir_unwrite()' doesn't work? */
	pagedir_unmap_userspace();
#endif
	mman_syncall();
}


/* Memory manager construction functions.
 * NOTE: mman_fork() will fork the current mman. */
PUBLIC ATTR_RETNONNULL WUNUSED REF struct mman *FCALL
mman_fork(void) THROWS(E_BADALLOC, ...) {
	struct forktree_data ft;
	ft.ftd_oldmm = THIS_MMAN;
	assertf(ft.ftd_oldmm != &mman_kernel, "You can't fork the kernel...");
	ft.ftd_newmm = mman_new();

	/* REMINDER: When not able to acquire a lock, we must call `task_serve()' after
	 *           releasing all other already-acquired locks. This is necessary to
	 *           deal with another thread within our current mman calling exec().
	 * Otherwise, we might get a situation with a process w/ 2 threads, where one
	 * thread calls exec() while another calls fork(), which could then result in
	 * both to exec(), as well as the fork() succeeding, but the fork() succeeding
	 * in the context of the program being exec'd by the first thread (which would
	 * be no good), rather than the program that contained the fork() call. */

	SLIST_INIT(&ft.ftd_freelist);
	ft.ftd_didulock = false;
	TRY {
		/* Because everything relating to low-level page directories can be made
		 * to happen lazily, forking a memory manager is as simply as replicating
		 * its tree of memory nodes.
		 *
		 * For this purpose, try to keep the total # of simultaneous locks low, so
		 * that the overall impact (in regards to lock contention) is kept minimal. */

again:
		/* Try to acquire locks to both the old (to-be copied) and new mman. */
		mman_lock_acquire(ft.ftd_oldmm);

#ifndef __OPTIMIZE_SIZE__
		/* TODO: The first time we get here, try to count exactly how many mem-nodes
		 *       we'll be needing to do the fork, and pre-allocate exactly that many
		 *       to begin with (that way, we won't need to allocate so much while
		 *       holding all too many locks) */
#endif /* !__OPTIMIZE_SIZE__ */

		if unlikely(!mman_lock_tryacquire(ft.ftd_newmm)) {
			/* Super unlikely, but can happen because `ft.ftd_newmm' becomes globally
			 * visible even before we're done here, starting with the first
			 * replicated mem-part via `SOME_GLOBAL_PART->[mp_copy|mp_share]->[...]->mn_mman'
			 *
			 * As such, it is possible that someone else (e.g. someone calling
			 * mpart_split()) has acquired a lock to the mman. - So just wait
			 * for them to release said lock! */
			mman_lock_release(ft.ftd_oldmm);
			do {
				task_serve();
				task_yield();
			} while (!mman_lock_available(ft.ftd_newmm));
			goto again;
		}

		/* We're now holding a lock to both the old, as well as the new mman.
		 * That's everything we need to start forking the tree of mappings. */
		ft.ftd_newtree = NULL;
		if (!forktree_or_unlock(&ft, &ft.ftd_newtree, NULL,
		                        ft.ftd_oldmm->mm_mappings)) {
			/* Try again... */
			task_serve();
			goto again;
		}

		/* Successfully forked the entire tree of memory nodes, but must still
		 * delete write permissions for all writable nodes of the old mman, so
		 * that we can ensure that anything written to by either the old, or the
		 * new mman will be handled via copy-on-write going forward. */
		forktree_clearwrite(ft.ftd_oldmm);

		/* Release our lock to the old mman. */
		mman_lock_release(ft.ftd_oldmm);

		if (ft.ftd_didulock) {
			/* Write-back the tree of mappings into `ft.ftd_newmm'.
			 * For this purpose, make sure that there aren't any left-over
			 * nodes from any previous fork-attempts... */
			if unlikely(ft.ftd_newmm->mm_mappings != NULL)
				forktree_freeall(&ft, ft.ftd_newmm->mm_mappings);

			/* Because we had to release our lock from the new mman at
			 * one point, there is a chance that someone else added a
			 * mapping to our page directory.
			 * To make sure that this didn't happen, clear the page
			 * directory once again at this point. */
			pagedir_unmap_userspace_p(ft.ftd_newmm->mm_pagedir_p);
#ifndef CONFIG_NO_SMP
			pagedir_syncall_smp_p(ft.ftd_newmm->mm_pagedir_p);
#endif /* !CONFIG_NO_SMP */
		} else {
			assert(ft.ftd_newmm->mm_mappings == NULL);
		}

		/* Because `ft.ftd_newtree' is a mirror copy of the tree of mappings
		 * from the old mman, we can simply assign it as-is as a valid R/B-tree
		 * of mem-nodes to-be used by the new mman. */
		ft.ftd_newmm->mm_mappings = ft.ftd_newtree;

		/* Release our lock to the new mman. */
		mman_lock_release(ft.ftd_newmm);

		/* NOTE: No further initialization of the underlying page directory of `ft.ftd_newmm'
		 *       is needed, since everything will happen lazily on first access. This
		 *       way, we don't even have to create a single mapping with the new mman's
		 *       page directory! */
	} EXCEPT {
		mnode_slist_freeall(&ft.ftd_freelist);
		decref_likely(ft.ftd_newmm);
		RETHROW();
	}
	mnode_slist_freeall(&ft.ftd_freelist);
	return ft.ftd_newmm;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_FORK_C */
