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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_C 1
#define __WANT_MPART__mp_dead
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

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

/* Try to incref all parts of the given tree.
 * Parts that have already been destroyed are simply ignored. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_tree_tryincref)(struct mpart *__restrict root) {
again:
	COMPILER_UNUSED(tryincref(root));
	/* Recursive over the entire tree. */
	if (root->mp_filent.rb_lhs) {
		if (root->mp_filent.rb_rhs)
			mpart_tree_tryincref(root->mp_filent.rb_rhs);
		root = root->mp_filent.rb_lhs;
		goto again;
	}
	if (root->mp_filent.rb_rhs) {
		root = root->mp_filent.rb_rhs;
		goto again;
	}
}

/* Drop references from all parts (that haven't already
 * been destroyed) that are reachable from `root'. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_tree_decref)(struct mpart *__restrict root) {
	struct mpart *lhs, *rhs;
again:
	lhs = root->mp_filent.rb_lhs;
	rhs = root->mp_filent.rb_rhs;
	if likely(!wasdestroyed(root))
		decref(root);
	/* Recursive over the entire tree. */
	if (lhs) {
		if (rhs)
			mpart_tree_decref(rhs);
		root = lhs;
		goto again;
	}
	if (rhs) {
		root = rhs;
		goto again;
	}
}

/* Release locks to all parts reachable from `root'. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_tree_unlock)(struct mpart *__restrict root) {
again:
	if likely(!wasdestroyed(root))
		mpart_lock_release(root);
	/* Recursive over the entire tree. */
	if (root->mp_filent.rb_lhs) {
		if (root->mp_filent.rb_rhs)
			mpart_tree_tryincref(root->mp_filent.rb_rhs);
		root = root->mp_filent.rb_lhs;
		goto again;
	}
	if (root->mp_filent.rb_rhs) {
		root = root->mp_filent.rb_rhs;
		goto again;
	}
}

/* Try to acquire a lock to all parts reachable from `root'.
 * If one of these locks cannot be acquired without blocking,
 * release all locks already acquired and return that part. */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) struct mpart *
NOTHROW(FCALL mpart_tree_trylock)(struct mpart *__restrict root) {
	struct mpart *result;
	/* Try to lock the root-part. (but skip destroyed parts) */
	if likely(!wasdestroyed(root)) {
		if (!mpart_lock_tryacquire(root))
			return root;
	}
	/* Recursively lock the entire tree (but keep track of our
	 * current path so we're always able to release exaclty those
	 * locks which we've already acquired previously). */
	if (root->mp_filent.rb_lhs) {
		result = mpart_tree_trylock(root->mp_filent.rb_lhs);
		if (result != NULL)
			goto err_lock_root;
	}
	if (root->mp_filent.rb_rhs) {
		result = mpart_tree_trylock(root->mp_filent.rb_rhs);
		if (result != NULL)
			goto err_lock_lhs;
	}
	return NULL;
err_lock_lhs:
	if (root->mp_filent.rb_lhs)
		mpart_tree_unlock(root->mp_filent.rb_lhs);
err_lock_root:
	if likely(!wasdestroyed(root))
		mpart_lock_release(root);
	return result;
}

/* Acquire a lock to all parts within the parts-tree of
 * `self', or decref all parts and release a lock to `self'
 * before waiting for the blocking part to become available
 * and returning `false' */
PRIVATE WUNUSED NONNULL((1)) bool FCALL
mfile_lockparts_or_decref_and_unlock(struct mfile *__restrict self)
		THROWS(E_WOULDBLOCK) {
	struct mpart *blocking;
	/* Try to lock all parts. */
	blocking = mpart_tree_trylock(self->mf_parts);
	if (blocking) {
		/* Found a blocking part :( */
		incref(blocking); /* Keep around a reference to this part. */
		mpart_tree_decref(self->mf_parts);
		mfile_lock_endwrite(self);
		FINALLY_DECREF_UNLIKELY(blocking);
		/* Wait for the lock to become available. */
		while (!mpart_lock_available(blocking))
			task_yield();
		return false;
	}
	return true;
}


/* Make all parts reachable from `root' anonymous, as well as override
 * their `mp_file' field with `mfile_anon[...]', before releasing the
 * lock held to said part and dropping a reference. If this results in
 * the part being destroyed, don't destroy it immediately, but add it to
 * the given `dead' list instead (linked via `_mp_dead')
 *
 * This is done for all parts reachable from `root'. */
PRIVATE NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL mpart_tree_makeanon_and_unlock_and_decref)(struct mpart *__restrict root,
                                                         struct mfile *__restrict file,
                                                         struct mpart_slist *__restrict dead) {
	struct mpart *lhs, *rhs;
again:
	lhs = root->mp_filent.rb_lhs;
	rhs = root->mp_filent.rb_rhs;
	if (!wasdestroyed(root)) {
		/* Set the NO_GLOBAL_REF bit, thus essentially unloading the part from the
		 * global part cache (should this mem-part still be apart of said cache) */
		if (ATOMIC_FETCHAND(root->mp_flags, ~MPART_F_GLOBAL_REF) & MPART_F_GLOBAL_REF)
			decref_nokill(root); /* The global reference... */
		_mpart_init_asanon(root);
		assert(root->mp_file == file);
		root->mp_file = incref(&mfile_anon[file->mf_blockshift]);
		mpart_lock_release(root);
		decref_nokill(file); /* The reference previously stored  in `root->mp_file' */
		if (ATOMIC_DECFETCH(root->mp_refcnt) == 0)
			SLIST_INSERT(dead, root, _mp_dead); /* Destroy this one later... */
	} else {
		DBG_memset(&root->mp_filent, 0xcc, sizeof(root->mp_filent));
	}
	/* Recursive over the entire tree. */
	if (lhs) {
		if (rhs)
			mpart_tree_makeanon_and_unlock_and_decref(rhs, file, dead);
		root = lhs;
		goto again;
	}
	if (rhs) {
		root = rhs;
		goto again;
	}
}



/* Make the given file anonymous. What this means is that:
 *  - Existing mappings of all mem-parts are altered to point
 *    at anonymous memory files. For this purpose, the nodes of
 *    all existing mappings are altered.
 *  - The `MPART_F_GLOBAL_REF' flag is cleared for all parts
 *  - The `mf_parts' and `mf_changed' are set to `MFILE_PARTS_ANONYMOUS'
 * The result of all of this is that it is no longer possible to
 * trace back mappings of parts of `self' to that file.
 *
 * This function is called when the given file `self' should be deleted,
 * or has become unavailable for some other reason (e.g. the backing
 * filesystem has been unmounted) */
PUBLIC NONNULL((1)) void FCALL
mfile_delete(struct mfile *__restrict self)
		THROWS(E_WOULDBLOCK) {
	struct mpart_slist dead;

	/* Quick check: is the file already anonymous? */
#ifdef CONFIG_USE_NEW_FS
	if (self->mf_flags & MFILE_F_DELETED)
		return; /* Nothing to do here! */
#else /* CONFIG_USE_NEW_FS */
	if (ATOMIC_READ(self->mf_parts) == MFILE_PARTS_ANONYMOUS)
		return; /* Nothing to do here! */
#endif /* !CONFIG_USE_NEW_FS */
	SLIST_INIT(&dead);
again_lock:
	mfile_lock_write(self);
	COMPILER_READ_BARRIER();
	if (self->mf_parts == MFILE_PARTS_ANONYMOUS)
		goto done; /* Nothing to do here! */
	if (self->mf_parts == NULL) {
		self->mf_parts = MFILE_PARTS_ANONYMOUS;
		goto do_clear_changed_parts;
	}
	/* Try to incref all of the parts from `self' */
	mpart_tree_tryincref(self->mf_parts);

	/* Acquire locks to all parts. */
	if (!mfile_lockparts_or_decref_and_unlock(self))
		goto again_lock;

	/* TODO: Set some kind of FILE_WAS_DELETED flag in `self'
	 *       that will cause all future file-parts created by
	 *       `mfile_getpart()' to point to `mfile_anon' instead
	 *       of our file! */

	/* For every node within the tree, do the following:
	 * >> if (!wasdestroyed(part)) {
	 * >>     if (ATOMIC_FETCHAND(part->mp_flags, ~MPART_F_GLOBAL_REF) & MPART_F_GLOBAL_REF)
	 * >>         decref_nokill(part);
	 * >>     _mpart_init_asanon(part);
	 * >>     assert(part->mp_file == self);
	 * >>     part->mp_file = incref(&mfile_anon[...]);
	 * >>     decref_nokill(self);
	 * >>     if (ATOMIC_DECFETCH(part->mp_refcnt) == 0)
	 * >>         SLIST_INSERT(&dead, part, _mp_dead);
	 * >> } */
	mpart_tree_makeanon_and_unlock_and_decref(self->mf_parts, self, &dead);
	self->mf_parts = MFILE_PARTS_ANONYMOUS;
do_clear_changed_parts:

	/* Clear the list of changed mem-parts. Anything non-synced changes that
	 * still exist at this point will be lost, but we must still drop all of
	 * the references stored in the changed-part list! */
	{
		struct mpart_slist changed;
		changed.slh_first = ATOMIC_XCH(self->mf_changed.slh_first, MFILE_PARTS_ANONYMOUS);
		assert(changed.slh_first != MFILE_PARTS_ANONYMOUS);
		while (!SLIST_EMPTY(&changed)) {
			struct mpart *part;
			part = SLIST_FIRST(&changed);
			SLIST_REMOVE_HEAD(&changed, mp_changed);
			assert(part->mp_file == &mfile_anon[self->mf_blockshift]);
			DBG_memset(&part->mp_changed, 0xcc, sizeof(part->mp_changed));

			/* Also clear the CHANGED bit for all of the parts.
			 * We're allowed to do this because we've set the changed list of ANON,
			 * giving us special permissions to clear this bit (s.a. the documentation
			 * of the `MPART_F_CHANGED' flag) */
			ATOMIC_AND(part->mp_flags, ~MPART_F_CHANGED);

			/* Drop a reference from the changed mem-part. This is the reference
			 * that was originally created when the part was added to the changed
			 * list. */
			if (ATOMIC_DECFETCH(part->mp_refcnt) == 0)
				SLIST_INSERT(&dead, part, _mp_dead);
		}
	} /* Scope... */

done:

#ifdef CONFIG_USE_NEW_FS
	/* Mark the file as having been deleted. */
	ATOMIC_OR(self->mf_flags, MFILE_F_DELETED);
#endif /* CONFIG_USE_NEW_FS */

	mfile_lock_endwrite_f(self);

	/* Destroy all mem-parts apart of the dead-list. */
	while (!SLIST_EMPTY(&dead)) {
		struct mpart *part;
		part = SLIST_FIRST(&dead);
		SLIST_REMOVE_HEAD(&dead, _mp_dead);
		mpart_destroy(part);
	}

	/* Reap lockops _after_ having destroyed all of the old parts
	 * have been destroyed, thus raising the interlocked-ness between
	 * those 2 operations, which may potentially increase efficiency. */
	mfile_lockops_reap(self);

	/* Wake-up possibly waiting threads.
	 * Since we've altered the backing files of a lot of parts, we
	 * have to ensure that threads waiting for init to be done are
	 * connected to the relevant signal. */
	sig_broadcast(&self->mf_initdone);
}





/* Try to incref all parts within the given range.
 * Parts that have already been destroyed are simply ignored. */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mpart_tree_tryincref_inrange)(struct mpart *lo,
                                            struct mpart *hi) {
	for (;;) {
		COMPILER_UNUSED(tryincref(lo));
		if (lo == hi)
			break;
		lo = mpart_tree_nextnode(lo);
		assert(lo);
	}
}

/* Drop references from all parts (that haven't already
 * been destroyed) within the given range. */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mpart_tree_decref_inrange)(struct mpart *lo,
                                         struct mpart *hi) {
	for (;;) {
		if likely(!wasdestroyed(hi))
			decref(hi);
		if (hi == lo)
			break;
		hi = mpart_tree_prevnode(hi);
		assert(hi);
	}
}

/* Release locks to all parts within the given range. */
/*
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mpart_tree_unlock_inrange)(struct mpart *lo,
                                         struct mpart *hi) {
	for (;;) {
		if likely(!wasdestroyed(hi))
			mpart_lock_release(hi);
		if (hi == lo)
			break;
		hi = mpart_tree_prevnode(hi);
		assert(hi);
	}
}*/

/* Try to acquire a lock to all parts within the given range.
 * If one of these locks cannot be acquired without blocking,
 * release all locks already acquired and return that part. */
PRIVATE NOBLOCK NONNULL((1, 2)) struct mpart *
NOTHROW(FCALL mpart_tree_trylock_inrange)(struct mpart *lo,
                                          struct mpart *hi) {
	struct mpart *iter = lo;
	for (;;) {
		if likely(!wasdestroyed(iter)) {
			if (!mpart_lock_tryacquire(iter))
				goto fail;
		}
		if (iter == hi)
			break;
		iter = mpart_tree_nextnode(iter);
		assert(iter);
	}
	return NULL;
fail:
	/* Release all locks already acquired. */
	while (lo != iter) {
		if likely(!wasdestroyed(lo))
			mpart_lock_release(lo);
		lo = mpart_tree_nextnode(lo);
		assert(lo);
	}
	return iter;
}

/* Acquire a lock to all parts within the given range, or
 * decref all parts within said range and release a lock to
 * `self' before waiting for the blocking part to become
 * available and returning `false' */
PRIVATE WUNUSED NONNULL((1, 2, 3)) bool FCALL
mfile_lockparts_or_decref_and_unlock_inrange(struct mfile *__restrict self,
                                             struct mpart *lo,
                                             struct mpart *hi)
		THROWS(E_WOULDBLOCK) {
	struct mpart *blocking;
	/* Try to lock all parts. */
	blocking = mpart_tree_trylock_inrange(lo, hi);
	if (blocking) {
		/* Found a blocking part :( */
		incref(blocking); /* Keep around a reference to this part. */
		mpart_tree_decref_inrange(lo, hi);
		mfile_lock_endwrite(self);
		FINALLY_DECREF_UNLIKELY(blocking);
		/* Wait for the lock to become available. */
		while (!mpart_lock_available(blocking))
			task_yield();
		return false;
	}
	return true;
}



/* Split a potential part at `minaddr' and `maxaddr', and make
 * it so that all parts between that range are removed from the
 * part-tree of `self', by essentially anonymizing them.
 * This function can be used to implement `ftruncate(2)'
 *
 * NOTE: Unlike `mfile_delete()', this function doesn't mark
 *       the file itself as deleted, meaning that more parts
 *       can still be created at a later point in time! */
PUBLIC NONNULL((1)) void FCALL
mfile_makeanon_subrange(struct mfile *__restrict self,
                        PAGEDIR_PAGEALIGNED pos_t minaddr,
                        pos_t maxaddr)
		THROWS(E_WOULDBLOCK) {
	struct mpart_slist dead;
	struct mpart_tree_minmax mima;
	assert(mfile_addr_aligned(self, minaddr));
	assert(mfile_addr_aligned(self, maxaddr + 1));
	SLIST_INIT(&dead);
again_lock:
	mfile_lock_write(self);
	if (self->mf_parts == MFILE_PARTS_ANONYMOUS)
		goto done; /* Simple case: the entire file was made anonymous */
	mpart_tree_minmaxlocate(self->mf_parts, minaddr, maxaddr, &mima);
	assert((mima.mm_min != NULL) == (mima.mm_max != NULL));
	if (!mima.mm_min)
		goto done; /* Simple case: Nothing to make anonymous! */
	/* Check if we may need to split the lower/upper node. */
	if (minaddr > mima.mm_min->mp_minaddr) {
		if unlikely(!tryincref(mima.mm_min))
			mima.mm_min = NULL;
		mfile_lock_endwrite(self);
		if likely(mima.mm_min) {
			FINALLY_DECREF_UNLIKELY(mima.mm_min);
			xdecref(mpart_split(mima.mm_min, minaddr));
		}
		goto again_lock;
	}
	if (maxaddr < mima.mm_max->mp_maxaddr) {
		if unlikely(!tryincref(mima.mm_max))
			mima.mm_max = NULL;
		mfile_lock_endwrite(self);
		if likely(mima.mm_max) {
			FINALLY_DECREF_UNLIKELY(mima.mm_max);
			xdecref(mpart_split(mima.mm_max, maxaddr + 1));
		}
		goto again_lock;
	}

	/* Try to incref all of the parts within the given range. */
	mpart_tree_tryincref_inrange(mima.mm_min, mima.mm_max);

	/* (try to) acquire references and locks to all parts within the discovered range. */
	if (!mfile_lockparts_or_decref_and_unlock_inrange(self,
	                                                  mima.mm_min,
	                                                  mima.mm_max))
		goto again_lock;

	/* For all non-destroyed parts: do what `mpart_tree_makeanon_and_unlock_and_decref'
	 * does, whilst removing all of the affected parts from the part-tree of `self'. */
	{
		struct mpart *part = mima.mm_min;
		mpart_tree_removenode(&self->mf_parts, part);
		do {
			if (!wasdestroyed(part)) {
				/* Set the NO_GLOBAL_REF bit, thus essentially unloading the part from the
				 * global part cache (should this mem-part still be apart of said cache) */
				if (ATOMIC_FETCHAND(part->mp_flags, ~MPART_F_GLOBAL_REF) & MPART_F_GLOBAL_REF)
					decref_nokill(part); /* The global reference... */
				_mpart_init_asanon(part);
				assert(part->mp_file == self);
				part->mp_file = incref(&mfile_anon[self->mf_blockshift]);
				COMPILER_WRITE_BARRIER();
				/* Clear the CHANGED-bit now, since we can only do so while also holding
				 * a lock to the mem-part, given that we're not actually setting the
				 * changed-part list of `self' to anonymous! */
				ATOMIC_AND(part->mp_flags, ~(MPART_F_CHANGED | MPART_F_LOCKBIT));
				mpart_lockops_reap(part);
				decref_nokill(self);                       /* The reference previously stored  in `part->mp_file' */
				if (ATOMIC_DECFETCH(part->mp_refcnt) == 0) /* Reference created by `mpart_tree_tryincref_inrange()' */
					SLIST_INSERT(&dead, part, _mp_dead);   /* Destroy this one later... */
			} else {
				DBG_memset(&part->mp_filent, 0xcc, sizeof(part->mp_filent));
			}
			part = mpart_tree_rremove(&self->mf_parts, minaddr, maxaddr);
		} while (part != NULL);
	} /* Scope... */

	{
		struct mpart_slist changed;
		struct mpart **p_chng, *chng;
		/* Capture all elements from the list of changed parts. */
		do {
			changed.slh_first = ATOMIC_READ(self->mf_changed.slh_first);
			if (changed.slh_first == MFILE_PARTS_ANONYMOUS)
				goto done;
		} while (!ATOMIC_CMPXCH_WEAK(self->mf_changed.slh_first,
		                             changed.slh_first, NULL));

		/* Remove all changed parts from within the caller-given file-range. */
		p_chng = SLIST_P_FIRST(&changed);
		while ((chng = *p_chng) != NULL) {
			if (minaddr <= chng->mp_maxaddr &&
			    maxaddr >= chng->mp_minaddr) {
				/* Apart of the anonymized address range! */
				assert(chng->mp_file == &mfile_anon[self->mf_blockshift]);
				SLIST_P_REMOVE(p_chng, mp_changed);
				DBG_memset(&chng->mp_changed, 0xcc, sizeof(chng->mp_changed));
				assert(!(chng->mp_flags & MPART_F_CHANGED));

				/* Drop a reference from the changed mem-part. This is the reference
				 * that was originally created when the part was added to the changed
				 * list. */
				if (ATOMIC_DECFETCH(chng->mp_refcnt) == 0)
					SLIST_INSERT(&dead, chng, _mp_dead);
			} else {
				/* Keep this part! */
				p_chng = SLIST_P_NEXT(chng, mp_changed);
			}
		}
		if (!SLIST_EMPTY(&changed)) {
			/* Re-insert all remaining changed parts into the changed-part list. */
			struct mpart_slist more_changed;
again_restore_changed:
			more_changed.slh_first = ATOMIC_CMPXCH_VAL(self->mf_changed.slh_first,
			                                           NULL, changed.slh_first);
			if (more_changed.slh_first == NULL)
				goto done;
			/* : If the changed-part list was set to ANON in the mean time, then discard all changed parts. */
			if (more_changed.slh_first == MFILE_PARTS_ANONYMOUS) {
				/* Discard all changed parts */
				do {
					chng = SLIST_FIRST(&changed);
					SLIST_REMOVE_HEAD(&changed, mp_changed);
					DBG_memset(&chng->mp_changed, 0xcc, sizeof(chng->mp_changed));
					if (ATOMIC_DECFETCH(chng->mp_refcnt) == 0)
						SLIST_INSERT(&dead, chng, _mp_dead);
				} while (!SLIST_EMPTY(&changed));
				goto done;
			}
			/* Combine the 2 lists of changed parts and try to restore everything at once. */
			if (!ATOMIC_CMPXCH(self->mf_changed.slh_first,
			                   more_changed.slh_first, NULL))
				goto again_restore_changed;
			chng = SLIST_FIRST(&more_changed);
			while (SLIST_NEXT(chng, mp_changed))
				chng = SLIST_NEXT(chng, mp_changed);
			chng->mp_changed.sle_next = changed.slh_first;
			changed                   = more_changed;
			goto again_restore_changed;
		}
	} /* Scope... */

done:
	mfile_lock_endwrite_f(self);

	/* Destroy all mem-parts apart of the dead-list. */
	while (!SLIST_EMPTY(&dead)) {
		struct mpart *part;
		part = SLIST_FIRST(&dead);
		SLIST_REMOVE_HEAD(&dead, _mp_dead);
		mpart_destroy(part);
	}

	/* Reap lockops _after_ having destroyed all of the old parts
	 * have been destroyed, thus raising the interlocked-ness between
	 * those 2 operations, which may potentially increase efficiency. */
	mfile_lockops_reap(self);

	/* Wake-up possibly waiting threads.
	 * Since we've altered the backing files of a lot of parts, we
	 * have to ensure that threads waiting for init to be done are
	 * connected to the relevant signal. */
	sig_broadcast(&self->mf_initdone);
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_C */
