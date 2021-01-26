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
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>
#include <kernel/vm/phys.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <kos/except.h>
#include <sys/param.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

#include <libc/string.h>

DECL_BEGIN

#ifndef NDEBUG
#define DBG_memset(dst, byte, num_bytes) memset(dst, byte, num_bytes)
#else /* !NDEBUG */
#define DBG_memset(dst, byte, num_bytes) (void)0
#endif /* NDEBUG */

#ifndef NDEBUG
#define DBG_memset(dst, byte, num_bytes) memset(dst, byte, num_bytes)
#else /* !NDEBUG */
#define DBG_memset(dst, byte, num_bytes) (void)0
#endif /* NDEBUG */

/* Allocate physical memory for use with mem-parts created for `self'
 * This function is a more restrictive version of `page_malloc_part(1, max_pages, res_pages)',
 * in that it will also ensure that returned pages are properly aligned, as well
 * as that the given `max_pages' is also properly aligned. Note however that so-long
 * as the size of a single file-block is <= PAGESIZE, this function behaves 100%
 * identical to the above call to `page_malloc_part()' */
PUBLIC NOBLOCK WUNUSED NONNULL((1, 3)) physpage_t
NOTHROW(FCALL mfile_alloc_physmem)(struct mfile *__restrict self,
                                   physpagecnt_t max_pages,
                                   physpagecnt_t *__restrict res_pages) {
	physpage_t result, real_result;
	size_t page_alignment;
	/* Check for the simple case where natural page alignment
	 * is enough to satisfy file-block alignment. */
	if likely(self->mf_blockshift <= PAGESHIFT)
		return page_malloc_part(1, max_pages, res_pages);
	page_alignment = (size_t)1 << (self->mf_blockshift - PAGESHIFT);
	assert(max_pages != 0);
	assertf(IS_ALIGNED(max_pages, page_alignment),
	        "Badly aligned max_pages %#" PRIxSIZ " for use with "
	        "file %p that requires %#" PRIxSIZ "-alignment",
	        max_pages, self, page_alignment);
	result = page_malloc_part(page_alignment + page_alignment - 1,
	                          max_pages + page_alignment - 1,
	                          res_pages);
	if unlikely(result == PHYSPAGE_INVALID) {
		result = page_malloc(page_alignment);
		if (result != PHYSPAGE_INVALID) {
			if (!IS_ALIGNED(result, page_alignment)) {
				page_ccfree(result, max_pages);
				result = PHYSPAGE_INVALID;
			}
		}
		return result;
	}

	/* Trim leading/trailing pages to satisfy the required alignment. */
	real_result = CEIL_ALIGN(result, page_alignment);
	if (real_result > result) {
		/* Trim leading */
		physpagecnt_t count;
		count = (physpagecnt_t)(real_result - result);
		page_ccfree(result, count);
		*res_pages -= count;
	}
	if (!IS_ALIGNED(*res_pages, page_alignment)) {
		/* Trim trailing */
		physpagecnt_t count;
		count = *res_pages & (page_alignment - 1);
		page_ccfree(result + *res_pages - count, count);
		*res_pages -= count;
	}

	assert(*res_pages >= page_alignment);
	assert(*res_pages <= max_pages);
	return real_result;
}


/* Destroy a given mem-file */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_destroy)(struct mfile *__restrict self) {
	assertf(self->mf_parts == NULL ||
	        self->mf_parts == MFILE_PARTS_ANONYMOUS,
	        "Any remaining part should have kept us alive!\n"
	        "Also: You mustn't decref() an mfile before dropping all "
	        /* */ "local references to contained mparts!\n"
	        "self->db_parts = %p\n",
	        self->mf_parts);
	sig_broadcast_for_fini(&self->mf_initdone);
	if (self->mf_ops) {
		(*self->mf_ops->mo_destroy)(self);
	} else {
		kfree(self);
	}
}



PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL destroy_mpart_after_removed_from_file)(struct mpart *__restrict self) {
	assert(wasdestroyed(self));
	assert(!(self->mp_flags & MPART_F_NO_GLOBAL_REF));
	if (LIST_ISBOUND(self, mp_allparts)) {
		/* Must remove from the global list of all known parts. */
		if (mpart_all_lock_tryacquire()) {
			LIST_REMOVE(self, mp_allparts);
			mpart_all_lock_release();
		} else {
			SLIST_ATOMIC_INSERT(&mpart_all_dead, self, _mp_dead);
			_mpart_all_reap();
			return;
		}
	}
	mpart_free(self);
}



/* Reap dead parts of `self' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _mfile_deadparts_reap)(struct mfile *__restrict self) {
	REF struct mpart *parts;
again:
	if (!atomic_rwlock_trywrite(&self->mf_lock))
		return;
	parts = SLIST_ATOMIC_CLEAR(&self->mf_deadparts);
	if (self->mf_parts != MFILE_PARTS_ANONYMOUS) {
		struct mpart *iter;
		for (iter = parts; iter; iter = SLIST_NEXT(iter, _mp_dead))
			mpart_tree_removenode(&self->mf_parts, iter);
	}
	atomic_rwlock_endwrite(&self->mf_lock);
	while (parts) {
		REF struct mpart *next;
		next = SLIST_NEXT(parts, _mp_dead);
		destroy_mpart_after_removed_from_file(parts);
		parts = next;
	}
	if (mfile_deadparts_mustreap(self))
		goto again;
}



PRIVATE NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(KCALL mpart_anon)(struct mpart *__restrict self,
                          struct mfile *__restrict file,
                          struct REF mpart_slist *__restrict decref_later) {
	assert(self->mp_file == file);
	DBG_memset(&self->mp_filent, 0xcc, sizeof(self->mp_filent));
	decref_nokill(file);
	assert(file->mf_blockshift < COMPILER_LENOF(mfile_anon));
	self->mp_file = incref(&mfile_anon[file->mf_blockshift]);
	if (!(ATOMIC_FETCHOR(self->mp_flags, MPART_F_NO_GLOBAL_REF) & MPART_F_NO_GLOBAL_REF)) {
		/* Must drop a reference to this part at a later point in time! */
		SLIST_INSERT(decref_later, self, _mp_oob);
	}
}



PRIVATE NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(KCALL mpart_anon_tree)(struct mpart *__restrict self,
                               struct mfile *__restrict file,
                               struct REF mpart_slist *__restrict decref_later) {
	struct mpart *lhs, *rhs;
again:
	lhs = self->mp_filent.rb_lhs;
	rhs = self->mp_filent.rb_rhs;
	mpart_anon(self, file, decref_later);
	if (lhs) {
		if (rhs)
			mpart_anon_tree(rhs, file, decref_later);
		self = lhs;
		goto again;
	}
	if (rhs) {
		self = rhs;
		goto again;
	}
}



/* Extended mem-part tree functions */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL mpart_tree_foreach_release_and_decref_impl)(struct mpart *__restrict root) {
again:
	mpart_lock_release(root);
	if unlikely(ATOMIC_DECFETCH(root->mp_refcnt) == 0)
		mpart_destroy_later(root);
	if (root->mp_filent.rb_lhs) {
		if (root->mp_filent.rb_rhs)
			mpart_tree_foreach_release_and_decref_impl(root->mp_filent.rb_rhs);
		root = root->mp_filent.rb_lhs;
		goto again;
	}
	if (root->mp_filent.rb_rhs) {
		root = root->mp_filent.rb_rhs;
		goto again;
	}
}

PRIVATE WUNUSED NONNULL((1)) REF struct mpart *
NOTHROW(FCALL mpart_tree_foreach_incref_and_tryacquire_impl)(struct mpart *__restrict root) {
	REF struct mpart *result;
	/* Acquire a lock to the root-node. */
	if (tryincref(root) && !mpart_lock_tryacquire(root))
		return root;
	/* Recursively lock everything. */
	if (root->mp_filent.rb_lhs) {
		result = mpart_tree_foreach_incref_and_tryacquire_impl(root->mp_filent.rb_lhs);
		if unlikely(result != NULL) {
got_result:
			mpart_lock_release(root);
			decref_nokill(root);
			return result;
		}
	}
	if (root->mp_filent.rb_rhs) {
		result = mpart_tree_foreach_incref_and_tryacquire_impl(root->mp_filent.rb_rhs);
		if unlikely(result != NULL) {
			if (root->mp_filent.rb_lhs != NULL)
				mpart_tree_foreach_release_and_decref_impl(root->mp_filent.rb_lhs);
			goto got_result;
		}
	}
	return NULL;
}

/* Try to acquire a lock to all parts within the given tree.
 * If this is impossible, then release all locks already acquired,
 * and return a reference to the part to which no reference could
 * be acquired. (otherwise (on success), NULL is returned) */
PRIVATE WUNUSED REF struct mpart *
NOTHROW(FCALL mpart_tree_foreach_incref_and_tryacquire)(struct mpart *root) {
	REF struct mpart *result = NULL;
	if likely(root != NULL)
		result = mpart_tree_foreach_incref_and_tryacquire_impl(root);
	return result;
}

PRIVATE NONNULL((1)) void
NOTHROW(FCALL mpart_tree_foreach_release_and_decref_teardown_impl)(struct mpart *__restrict root) {
	struct mpart *lhs, *rhs;
again:
	lhs = root->mp_filent.rb_lhs;
	rhs = root->mp_filent.rb_rhs;
	DBG_memset(&root->mp_filent, 0xcc, sizeof(root->mp_filent));
	mpart_lock_release(root);
	if unlikely(ATOMIC_DECFETCH(root->mp_refcnt) == 0)
		mpart_destroy_later(root);
	if (lhs) {
		if (rhs)
			mpart_tree_foreach_release_and_decref_teardown_impl(rhs);
		root = lhs;
		goto again;
	}
	if (rhs) {
		root = rhs;
		goto again;
	}
}

/* Unlock all parts of the given tree. */
PRIVATE void
NOTHROW(FCALL mpart_tree_foreach_release_and_decref_teardown)(struct mpart *root) {
	if (root != NULL)
		mpart_tree_foreach_release_and_decref_teardown_impl(root);
}


/* Make the given file anonymous. What this means is that:
 *  - Existing mappings of all mem-parts are altered to point
 *    at anonymous memory files. For this purpose, the nodes of
 *    all existing mappings are altered.
 *  - The `MPART_F_NO_GLOBAL_REF' flag is set for all parts
 *  - The `mf_parts' and `mf_changed' are set to `MFILE_PARTS_ANONYMOUS'
 *  - The `mf_deadparts' chain is cleared (one last time)
 * The result of all of this is that it is no longer possible to
 * trace back mappings of parts of `self' to that file.
 *
 * This function is called when the given file `self' should be deleted,
 * or has become unavailable for some other reason (e.g. the backing
 * filesystem has been unmounted) */
PUBLIC NONNULL((1)) void FCALL
mfile_makeanon(struct mfile *__restrict self)
		THROWS(E_WOULDBLOCK) {
	REF struct mpart *part;
	struct REF mpart_slist decref_later;
	if (self->mf_parts == MFILE_PARTS_ANONYMOUS)
		return;
	SLIST_INIT(&decref_later);
again:
	mfile_lock_write(self);
	if (self->mf_parts == MFILE_PARTS_ANONYMOUS)
		goto done_parts;
	if (self->mf_parts == NULL) {
		self->mf_parts = MFILE_PARTS_ANONYMOUS;
		goto done_parts;
	}
	/* Acquire locks to all parts, and change them to be anonymous. */
	part = mpart_tree_foreach_incref_and_tryacquire(self->mf_parts);
	if unlikely(part) {
		mfile_lock_endwrite(self);
		FINALLY_DECREF_UNLIKELY(part);
		while (!mpart_lock_available(part))
			task_yield();
		goto again;
	}
	/* Anonymize all parts of the tree. */
	mpart_anon_tree(self->mf_parts, self, &decref_later);
	mpart_tree_foreach_release_and_decref_teardown(self->mf_parts);
done_parts:
	/* Clear the changed-parts list one last time, and set it to ANON */
	part = ATOMIC_XCH(self->mf_changed.slh_first, MFILE_PARTS_ANONYMOUS);
	if (part != MFILE_PARTS_ANONYMOUS) {
		while (part) {
			REF struct mpart *next;
			next = SLIST_NEXT(part, mp_changed);
			DBG_memset(&part->mp_changed, 0xcc, sizeof(part->mp_changed));
			ATOMIC_AND(part->mp_flags, ~(MPART_F_CHANGED));
			SLIST_INSERT(&decref_later, part, _mp_oob);
			part = next;
		}
	}

	mfile_lock_endwrite(self);
	while (!SLIST_EMPTY(&decref_later)) {
		part = SLIST_FIRST(&decref_later);
		SLIST_REMOVE_HEAD(&decref_later, _mp_oob);
		DBG_memset(&part->_mp_oob, 0xcc, sizeof(part->_mp_oob));
		decref(part);
	}

	/* (try to) reap dead parts one last time again. */
	mfile_deadparts_reap(self);

	/* Wake-up possibly waiting threads. */
	sig_broadcast(&self->mf_initdone);
}



PRIVATE NONNULL((1)) void FCALL
restore_changed_parts(struct mfile *__restrict self,
                      REF struct mpart *chain)
		THROWS(E_WOULDBLOCK, ...) {
	struct mpart *other_changes, **p_last, *more_changes;
	other_changes = ATOMIC_CMPXCH_VAL(self->mf_changed.slh_first, NULL, chain);
	if (other_changes == NULL)
		return; /* Success */
	if (chain == NULL)
		return; /* No remaining changes. */
	if (other_changes == MFILE_PARTS_ANONYMOUS) {
		/* Changes may no longer be traced! */
clear_chain:
		while (chain) {
			struct mpart *next;
			next = SLIST_NEXT(chain, mp_changed);
			DBG_memset(&chain->mp_changed, 0xcc, sizeof(chain->mp_changed));
			decref(chain);
			chain = next;
		}
		return;
	}
	/* Find the last of the new changes. */
	p_last = SLIST_P_NEXT(chain, mp_changed);
	while (*p_last)
		p_last = SLIST_P_NEXT(*p_last, mp_changed);
	for (;;) {
		*p_last = other_changes;
		COMPILER_WRITE_BARRIER();
		more_changes = ATOMIC_CMPXCH_VAL(self->mf_changed.slh_first,
		                                 other_changes,
		                                 chain);
		if (more_changes == other_changes)
			break;
		if unlikely(other_changes == MFILE_PARTS_ANONYMOUS)
			goto clear_chain;
		other_changes = more_changes;
	}
}


SIMPLEQ_HEAD(mpart_simpleq, mpart);

PRIVATE NOBLOCK WUNUSED NONNULL((1, 2)) bool
NOTHROW(FCALL mpart_simpleq_contains)(struct mpart_simpleq const *__restrict self,
                                      struct mpart const *__restrict elem) {
	bool result = false;
	SIMPLEQ_CONTAINS(self, elem, _mp_oob2, { result = true; });
	return result;
}



/* Split a potential part at `minaddr' and `maxaddr', and make
 * it so that all parts between that range are removed from the
 * part-tree of `self', by essentially anonymizing them.
 * This function can be used to implement `ftruncate(2)' */
PUBLIC NONNULL((1)) void FCALL
mfile_makeanon_subrange(struct mfile *__restrict self,
                        PAGEDIR_PAGEALIGNED pos_t minaddr,
                        pos_t maxaddr)
		THROWS(E_WOULDBLOCK) {
	struct mpart_tree_minmax mima;
	struct mpart *part;
	struct REF mpart_simpleq anon_parts;
	assert(mfile_addr_aligned(self, minaddr));
	assert(mfile_addr_aligned(self, maxaddr + 1));
again:
	mfile_lock_write(self);
	if (self->mf_parts == MFILE_PARTS_ANONYMOUS)
		goto done;
	mpart_tree_minmaxlocate(self->mf_parts, minaddr, maxaddr, &mima);
	assert((mima.mm_min != NULL) == (mima.mm_max != NULL));
	if (!mima.mm_min)
		goto done;
	/* Check if we may need to split the lower/upper node. */
	if (minaddr > mima.mm_min->mp_minaddr) {
		mpart_reladdr_t offset;
		if unlikely(!tryincref(mima.mm_min))
			mima.mm_min = NULL;
		mfile_lock_endwrite(self);
		if likely(mima.mm_min) {
			FINALLY_DECREF_UNLIKELY(mima.mm_min);
			offset = (mpart_reladdr_t)(minaddr - mima.mm_min->mp_minaddr);
			xdecref(mpart_split(mima.mm_min, offset));
		}
		goto again;
	}
	if (maxaddr < mima.mm_max->mp_maxaddr) {
		mpart_reladdr_t offset;
		if unlikely(!tryincref(mima.mm_max))
			mima.mm_max = NULL;
		mfile_lock_endwrite(self);
		if likely(mima.mm_max) {
			FINALLY_DECREF_UNLIKELY(mima.mm_max);
			offset = (mpart_reladdr_t)((maxaddr + 1) - mima.mm_max->mp_minaddr);
			xdecref(mpart_split(mima.mm_max, offset));
		}
		goto again;
	}
	/* Acquire references and locks to all parts within the discovered range.
	 * Also: Insert all of the affected parts into a secondary list `anon_parts' */
	SIMPLEQ_INIT(&anon_parts);
	part = mima.mm_min;
	for (;;) {
		if (tryincref(part)) {
			assert(part->mp_file == self);
			if (!mpart_lock_tryacquire(part)) {
				REF struct mpart *elem;
				/* Restore all of the affected parts. */
				SIMPLEQ_FOREACH (elem, &anon_parts, _mp_oob2) {
					mpart_lock_release(elem);
					elem->mp_file = incref(self);
					if unlikely(ATOMIC_DECFETCH(elem->mp_refcnt) == 0)
						mpart_destroy_later(elem);
				}
				/* Wait for the problematic part to become available. */
				mfile_lock_endwrite(self);
				FINALLY_DECREF_UNLIKELY(part); /* The `if (tryincref(part)) {' above... */
				while (!mpart_lock_available(part))
					task_yield();
				goto again;
			}
			/* Remember that this is one of the parts. */
			decref_nokill(self); /* Because we're overwriting `mp_file' */
			SIMPLEQ_INSERT_TAIL(&anon_parts, part, _mp_oob2);
		}
		if (part == mima.mm_max)
			break;
		part = mpart_tree_nextnode(part);
	}

	/* With all of the parts that are supposed to become anonymous gathered,
	 * start by removing all of them from our mem-file's part-tree. */
	SIMPLEQ_FOREACH (part, &anon_parts, _mp_oob2) {
		mpart_tree_removenode(&self->mf_parts, part);
		DBG_memset(&part->mp_filent, 0xcc, sizeof(part->mp_filent));
	}

	/* Check if any of the parts that we're supposed to anonymize got marked
	 * as having changed. If so, then we must also fix-up the list of changed
	 * parts in order to get rid of the parts to-be removed. */
	SIMPLEQ_FOREACH (part, &anon_parts, _mp_oob2) {
		if (part->mp_flags & MPART_F_CHANGED) {
			struct REF mpart_slist changed;
			changed.slh_first = SLIST_ATOMIC_CLEAR(&self->mf_changed);
			assert(changed.slh_first);
			SLIST_REMOVEALL(&changed, &part, mp_changed,
			                mpart_simpleq_contains(&anon_parts, part), {
				/* When a match is found, decref the part so-as to inherit
				 * the reference that had been stored within `mf_changed' */
				decref_nokill(part);
			});
			/* Restore all of the changed parts files that should be kept. */
			restore_changed_parts(self, SLIST_FIRST(&changed));
			break;
		}
	}

	/* With that, none of the affected parts can be accessed via the mem-file
	 * anymore. With that in mind, alter all of the parts to delete back-links
	 * to the mem-file, thus making them anonymous. */
	while (!SIMPLEQ_EMPTY(&anon_parts)) {
		/* Release locks and references to all of the parts, and fix-up the
		 * `mp_file' field of all of them to describe anonymous memory instead. */
		part = SIMPLEQ_FIRST(&anon_parts);
		SIMPLEQ_REMOVE_HEAD(&anon_parts, _mp_oob2);

		/* Set-up the part to reference the appropriate anonymous memory file. */
		assert(self->mf_blockshift < COMPILER_LENOF(mfile_anon));
		part->mp_file = incref(&mfile_anon[self->mf_blockshift]);

		/* Unset the changed-bit. */
		ATOMIC_AND(part->mp_flags, ~(MPART_F_CHANGED));

		/* Don't keep a global reference for this part. */
		if (!(ATOMIC_FETCHOR(part->mp_flags, MPART_F_NO_GLOBAL_REF) & MPART_F_NO_GLOBAL_REF))
			decref_nokill(part);

		/* Drop the part-reference that we've generated above when
		 * the part was originally added to the anon_parts-queue. */
		decref(part);
	}
done:
	mfile_lock_endwrite(self);

	/* Wake-up possibly waiting threads. */
	sig_broadcast(&self->mf_initdone);
}



/* Sync unwritten changes made to parts within the given address range.
 * @return: * : The total # of bytes that have been synced. */
PUBLIC NONNULL((1)) pos_t FCALL
mfile_sync(struct mfile *__restrict self)
		THROWS(E_WOULDBLOCK, ...) {
	pos_t result = 0;
	REF struct mpart *changes;
	do {
		changes = ATOMIC_READ(self->mf_changed.slh_first);
		if (!changes || changes == MFILE_PARTS_ANONYMOUS)
			return 0;
	} while (!ATOMIC_CMPXCH_WEAK(self->mf_changed.slh_first,
	                             changes, NULL));
	TRY {
		/* Sync all parts. */
		while (changes) {
			REF struct mpart *next;
			next = SLIST_NEXT(changes, mp_changed);
			result += mpart_sync(changes);
			decref(changes);
			changes = next;
		}
	} EXCEPT {
		restore_changed_parts(self, changes);
		RETHROW();
	}
	return result;
}



/* Create a new part, but don't add it to the global chain of parts, yet.
 * NOTE: The returned part will have the `MPART_F_NO_GLOBAL_REF' flag set! */
PRIVATE ATTR_RETNONNULL NONNULL((1)) REF struct mpart *KCALL
mfile_private_makepart(struct mfile *__restrict self,
                       PAGEDIR_PAGEALIGNED pos_t addr,
                       PAGEDIR_PAGEALIGNED size_t num_bytes)
		THROWS(E_WOULDBLOCK, ...) {
	REF struct mpart *result;
	assert(mfile_addr_aligned(self, addr));
	result = (REF struct mpart *)kmalloc(sizeof(struct mpart),
	                                     GFP_LOCKED);
	result->mp_refcnt = 1;
	result->mp_flags  = MPART_F_NORMAL | MPART_F_NO_GLOBAL_REF;
	result->mp_state  = MPART_ST_VOID;
	result->mp_file   = incref(self);
	LIST_INIT(&result->mp_copy);
	LIST_INIT(&result->mp_share);
	SLIST_INIT(&result->mp_lockops);
	DBG_memset(&result->mp_changed, 0xcc, sizeof(result->mp_changed));
	result->mp_minaddr = addr;
	result->mp_maxaddr = addr + num_bytes - 1;
	result->mp_meta    = NULL;
	if (mfile_getvio(self) != NULL) {
		result->mp_state = MPART_ST_VIO;
		LIST_ENTRY_UNBOUND_INIT(&result->mp_allparts);
		result->mp_blkst_ptr = NULL;
	} else {
		size_t num_blocks;
		num_blocks = num_bytes >> self->mf_blockshift;
		/* Allocate the block-status bitset. */
		if (num_blocks <= MPART_BLKST_BLOCKS_PER_WORD) {
			result->mp_flags |= MPART_F_BLKST_INL;
			result->mp_blkst_inl = MPART_BLOCK_REPEAT(MPART_BLOCK_ST_NDEF);
		} else {
			mpart_blkst_word_t *bitset;
			size_t num_words;
			num_words = CEILDIV(num_blocks, MPART_BLKST_BLOCKS_PER_WORD);
			TRY {
				bitset = (mpart_blkst_word_t *)kmalloc(num_words * sizeof(mpart_blkst_word_t),
#if MPART_BLOCK_ST_NDEF == 0
				                                       GFP_CALLOC |
#endif /* MPART_BLOCK_ST_NDEF == 0 */
				                                       GFP_LOCKED | GFP_PREFLT);
			} EXCEPT {
				kfree(result);
				RETHROW();
			}
#if MPART_BLOCK_ST_NDEF != 0
			memset(bitset, MPART_BLOCK_REPEAT(MPART_BLOCK_ST_NDEF),
			       num_words, sizeof(mpart_blkst_word_t));
#endif /* MPART_BLOCK_ST_NDEF != 0 */
			result->mp_blkst_ptr = bitset;
		}
	}
	if (self->mf_ops->mo_initpart) {
		/* Service custom part initializer. */
		TRY {
			(*self->mf_ops->mo_initpart)(self, result);
		} EXCEPT {
			decref_nokill(self);
			if (!(result->mp_flags & MPART_F_BLKST_INL))
				kfree(result->mp_blkst_ptr);
			kfree(result);
			RETHROW();
		}
	}
	return result;
}



/* Same as `mfile_getpart()', but may _only_ be used when `self' is an
 * anonymous file! As such, this function is mainly used to allocate
 * parts for `mfile_ndef' and `mfile_zero' */
PUBLIC ATTR_RETNONNULL NONNULL((1)) REF struct mpart *FCALL
mfile_makepart(struct mfile *__restrict self,
               PAGEDIR_PAGEALIGNED pos_t addr,
               PAGEDIR_PAGEALIGNED size_t num_bytes)
		THROWS(E_WOULDBLOCK, ...) {
	REF struct mpart *result;
	result = mfile_private_makepart(self, addr, num_bytes);

	/* Add the new part to the global list. */
	if (result->mp_state != MPART_ST_VIO)
		mpart_all_list_insert(result);

	return result;
}



/* Check `self' for a known mem-part that contains `addr', and (if found),
 * return that part. Otherwise, construct a new part start starts at `addr'
 * and spans at most `max_num_bytes' bytes (less may be returned if another part
 * already exists that describes the mapping above the requested location)
 * NOTE: The caller must ensure that:
 * >> mfile_addr_aligned(addr) && mfile_addr_aligned(max_num_bytes)
 * @return: * : A reference to a part that (at some point in the past) contained
 *              the given `addr'. It may no longer contain that address now as
 *              the result of being truncated since. */
PUBLIC ATTR_RETNONNULL NONNULL((1)) REF struct mpart *FCALL
mfile_getpart(struct mfile *__restrict self,
              PAGEDIR_PAGEALIGNED pos_t addr,
              PAGEDIR_PAGEALIGNED size_t max_num_bytes)
		THROWS(E_WOULDBLOCK, ...) {
	REF struct mpart *result;
	struct mpart_tree_minmax mima;
	size_t limit;
	assert(mfile_addr_aligned(self, addr));
	assert(mfile_addr_aligned(self, max_num_bytes));
	assert(max_num_bytes != 0);
	if (self->mf_parts == MFILE_PARTS_ANONYMOUS) {
create_anon_part:
		return mfile_makepart(self, addr, max_num_bytes);
	}
again_lock:
	mfile_lock_read(self);
	result = self->mf_parts;
	if (result == MFILE_PARTS_ANONYMOUS) {
		mfile_lock_endread(self);
		goto create_anon_part;
	}
again_locate:
	result = mpart_tree_locate(result, addr);
	if (result) {
		if unlikely(!tryincref(result)) {
			/* This can happen if `result' is currently pending for destruction... */
			mfile_lock_endread_f(self);
			while (mfile_deadparts_mustreap(self))
				_mfile_deadparts_reap(self);
			goto again_lock;
		}
		mfile_lock_endread(self);
		return result;
	}
	/* No node exists for `addr'. - Figure out what the next-larger node is. */
	mpart_tree_minmaxlocate(result, addr, addr + max_num_bytes - 1, &mima);
	limit = max_num_bytes;
	if (mima.mm_min) {
		limit = (size_t)(mpart_getminaddr(mima.mm_min) - addr);
		if (limit > max_num_bytes)
			limit = max_num_bytes;
	}
	mfile_lock_endread(self);
	/* Construct the new part. */
	result = mfile_private_makepart(self, addr, max_num_bytes);
	TRY {
/*again_lock_after_result_created:*/
		mfile_lock_write(self);
		/* Make sure that nothing else appeared in the mean time. */
		if unlikely(self->mf_parts == MFILE_PARTS_ANONYMOUS) {
			mfile_lock_endwrite(self);
			assert(result->mp_file == self);
			decref_nokill(self);
			assert(self->mf_blockshift < COMPILER_LENOF(mfile_anon));
			result->mp_file = incref(&mfile_anon[self->mf_blockshift]);
			COMPILER_WRITE_BARRIER();

			/* Add the new part to the global list. */
			if (result->mp_state != MPART_ST_VIO)
				mpart_all_list_insert(result);

			return result;
		}

		/* Try to insert the new node. */
		if (mpart_tree_tryinsert(&self->mf_parts, result)) {
			/* Success!
			 * Now also try to add the new part to the list of global parts. */
			if (result->mp_state != MPART_ST_VIO) {
				result->mp_flags &= ~MPART_F_NO_GLOBAL_REF;
				++result->mp_refcnt; /* The reference owned by `mpart_all_list' */
				COMPILER_WRITE_BARRIER();

				/* Add the new part to the global list. */
				mpart_all_list_insert(result);
			}
			mfile_lock_endwrite(self);
			return result;
		}
	} EXCEPT {
		if (!(ATOMIC_FETCHOR(result->mp_flags, MPART_F_NO_GLOBAL_REF) & MPART_F_NO_GLOBAL_REF))
			decref_nokill(result);
		decref(result);
		RETHROW();
	}
	/* The insert failed because of an overlap. */
	mfile_lock_endwrite(self);
	LIST_ENTRY_UNBOUND_INIT(&result->mp_allparts);
	destroy(result);
	goto again_locate;
}


#ifndef __INTELLISENSE__
DECL_END

#define DEFINE_mfile_read
#include "mfile-rw.c.inl"
#define DEFINE_mfile_write
#include "mfile-rw.c.inl"
#define DEFINE_mfile_read_p
#include "mfile-rw.c.inl"
#define DEFINE_mfile_write_p
#include "mfile-rw.c.inl"
#define DEFINE_mfile_readv
#include "mfile-rw.c.inl"
#define DEFINE_mfile_writev
#include "mfile-rw.c.inl"
#define DEFINE_mfile_readv_p
#include "mfile-rw.c.inl"
#define DEFINE_mfile_writev_p
#include "mfile-rw.c.inl"

DECL_BEGIN
#endif /* !__INTELLISENSE__ */


/* Builtin mem files */
PUBLIC struct mfile mfile_phys = MFILE_INIT_ANON(&mfile_phys_ops, PAGESHIFT);
PUBLIC struct mfile mfile_ndef = MFILE_INIT_ANON(&mfile_ndef_ops, PAGESHIFT);

PRIVATE NOBLOCK NONNULL((1, 2)) void FCALL
memfile_phys_initpart(struct mfile *__restrict UNUSED(self),
                      struct mpart *__restrict part) {
	if (!(part->mp_flags & MPART_F_BLKST_INL))
		kfree(part->mp_blkst_ptr);
	/* (re-)configure the part to point to static, physical memory. */
	part->mp_flags = MPART_F_MLOCK | MPART_F_MLOCK_FROZEN |
	                 MPART_F_NO_GLOBAL_REF | MPART_F_NOFREE;
	part->mp_state        = MPART_ST_MEM;
	part->mp_blkst_ptr    = NULL; /* Disable block status (thus having the system act like all
	                               * blocks were using `MPART_BLOCK_ST_CHNG' as their status) */
	part->mp_mem.mc_start = (physpage_t)part->mp_minaddr >> PAGESHIFT;
	part->mp_mem.mc_size  = mpart_getsize(part) >> PAGESHIFT;

	/* Define the alias symbols for the builtin zero-memory file. */
	DEFINE_PUBLIC_SYMBOL(mfile_zero, &mfile_anon[PAGESHIFT], sizeof(struct mfile));
	DEFINE_PUBLIC_SYMBOL(mfile_zero_ops, &mfile_anon_ops[PAGESHIFT], sizeof(struct mfile_ops));
}

PUBLIC_CONST struct mfile_ops const mfile_phys_ops = {
	/* .mo_destroy    = */ NULL,
	/* .mo_initpart   = */ &memfile_phys_initpart,
	/* .mo_loadblocks = */ NULL,
	/* .mo_saveblocks = */ NULL,
};

PUBLIC_CONST struct mfile_ops const mfile_ndef_ops = {
	/* .mo_destroy    = */ NULL,
	/* .mo_initpart   = */ NULL,
	/* .mo_loadblocks = */ NULL,
	/* .mo_saveblocks = */ NULL,
};



/* Fallback files for anonymous memory. These behave the same as `mfile_zero',
 * but one exists for every possible `mf_blockshift' (where the index into this
 * array is equal to that file's `mf_blockshift' value)
 * As such, these files are used by `mfile_makeanon()' as replacement mappings
 * of the original file. */
PUBLIC struct mfile mfile_anon[BITSOF(void *)] = {
#define INIT_ANON_FILE(i) MFILE_INIT_ANON(&mfile_anon_ops[i], i)
	INIT_ANON_FILE(0),
	INIT_ANON_FILE(1),
	INIT_ANON_FILE(2),
	INIT_ANON_FILE(3),
	INIT_ANON_FILE(4),
	INIT_ANON_FILE(5),
	INIT_ANON_FILE(6),
#if (__SIZEOF_POINTER__ * NBBY) > 8
	INIT_ANON_FILE(7),
	INIT_ANON_FILE(8),
	INIT_ANON_FILE(9),
	INIT_ANON_FILE(10),
	INIT_ANON_FILE(11),
	INIT_ANON_FILE(12),
	INIT_ANON_FILE(13),
	INIT_ANON_FILE(14),
	INIT_ANON_FILE(15),
#if (__SIZEOF_POINTER__ * NBBY) > 16
	INIT_ANON_FILE(16),
	INIT_ANON_FILE(17),
	INIT_ANON_FILE(18),
	INIT_ANON_FILE(19),
	INIT_ANON_FILE(20),
	INIT_ANON_FILE(21),
	INIT_ANON_FILE(22),
	INIT_ANON_FILE(23),
	INIT_ANON_FILE(24),
	INIT_ANON_FILE(25),
	INIT_ANON_FILE(26),
	INIT_ANON_FILE(27),
	INIT_ANON_FILE(28),
	INIT_ANON_FILE(29),
	INIT_ANON_FILE(30),
	INIT_ANON_FILE(31),
#if (__SIZEOF_POINTER__ * NBBY) > 32
	INIT_ANON_FILE(32),
	INIT_ANON_FILE(33),
	INIT_ANON_FILE(34),
	INIT_ANON_FILE(35),
	INIT_ANON_FILE(36),
	INIT_ANON_FILE(37),
	INIT_ANON_FILE(38),
	INIT_ANON_FILE(39),
	INIT_ANON_FILE(40),
	INIT_ANON_FILE(41),
	INIT_ANON_FILE(42),
	INIT_ANON_FILE(43),
	INIT_ANON_FILE(44),
	INIT_ANON_FILE(45),
	INIT_ANON_FILE(46),
	INIT_ANON_FILE(47),
	INIT_ANON_FILE(48),
	INIT_ANON_FILE(49),
	INIT_ANON_FILE(50),
	INIT_ANON_FILE(51),
	INIT_ANON_FILE(52),
	INIT_ANON_FILE(53),
	INIT_ANON_FILE(54),
	INIT_ANON_FILE(55),
	INIT_ANON_FILE(56),
	INIT_ANON_FILE(57),
	INIT_ANON_FILE(58),
	INIT_ANON_FILE(59),
	INIT_ANON_FILE(60),
	INIT_ANON_FILE(61),
	INIT_ANON_FILE(62),
	INIT_ANON_FILE(63),
#if (__SIZEOF_POINTER__ * NBBY) > 64
#error Unsupported sizeof(void *)
#endif /* (__SIZEOF_POINTER__ * NBBY) > 64 */
#endif /* (__SIZEOF_POINTER__ * NBBY) > 32 */
#endif /* (__SIZEOF_POINTER__ * NBBY) > 16 */
#endif /* (__SIZEOF_POINTER__ * NBBY) > 8 */
#undef INIT_ANON_FILE
};


#define ANON_LOADBLOCKS_CALLBACK(i)           \
	((i) == PAGESHIFT ? &mfile_zero_loadpages \
	                  : &mfile_zero_loadblocks)

PRIVATE NONNULL((1)) void KCALL
mfile_zero_loadpages(struct mfile *__restrict UNUSED(self),
                     mfile_block_t UNUSED(first_block),
                     physaddr_t buffer, size_t num_blocks) {
	/* Skip pages that were already zero-initialized before-hand! */
	if likely(IS_ALIGNED(buffer, PAGESIZE)) {
		size_t start, end;
		physpage_t page;
		page = physaddr2page(buffer);
		for (start = 0; start < num_blocks;) {
			if (page_iszero(page + start)) {
				++start;
				continue;
			}
			end = start + 1;
			while (end < num_blocks && !page_iszero(page + end))
				++end;
			/* Manually zero-init all pages from start...end */
			vm_memsetphyspages(physpage2addr(page + start),
			                   0, end - start);
			start = end + 1;
		}
	} else {
		/* Fallback for unaligned buffers (should actually happen, though...) */
		vm_memsetphys(buffer, 0, num_blocks * PAGESIZE);
	}
}

PRIVATE NONNULL((1)) void KCALL
mfile_zero_loadblocks(struct mfile *__restrict self,
                      mfile_block_t UNUSED(first_block),
                      physaddr_t buffer, size_t num_blocks) {
	size_t num_bytes;
	/* Generic physical memory zero-function */
	num_bytes = num_blocks << self->mf_blockshift;
	vm_memsetphys(buffer, 0, num_bytes);
}



PUBLIC_CONST struct mfile_ops const mfile_anon_ops[BITSOF(void *)] = {
#define INIT_ANON_OPS(i)                                    \
	{                                                       \
		/* .mo_destroy    = */ NULL,                        \
		/* .mo_initpart   = */ NULL,                        \
		/* .mo_loadblocks = */ ANON_LOADBLOCKS_CALLBACK(i), \
		/* .mo_saveblocks = */ NULL,                        \
	}
	INIT_ANON_OPS(0),
	INIT_ANON_OPS(1),
	INIT_ANON_OPS(2),
	INIT_ANON_OPS(3),
	INIT_ANON_OPS(4),
	INIT_ANON_OPS(5),
	INIT_ANON_OPS(6),
#if (__SIZEOF_POINTER__ * NBBY) > 8
	INIT_ANON_OPS(7),
	INIT_ANON_OPS(8),
	INIT_ANON_OPS(9),
	INIT_ANON_OPS(10),
	INIT_ANON_OPS(11),
	INIT_ANON_OPS(12),
	INIT_ANON_OPS(13),
	INIT_ANON_OPS(14),
	INIT_ANON_OPS(15),
#if (__SIZEOF_POINTER__ * NBBY) > 16
	INIT_ANON_OPS(16),
	INIT_ANON_OPS(17),
	INIT_ANON_OPS(18),
	INIT_ANON_OPS(19),
	INIT_ANON_OPS(20),
	INIT_ANON_OPS(21),
	INIT_ANON_OPS(22),
	INIT_ANON_OPS(23),
	INIT_ANON_OPS(24),
	INIT_ANON_OPS(25),
	INIT_ANON_OPS(26),
	INIT_ANON_OPS(27),
	INIT_ANON_OPS(28),
	INIT_ANON_OPS(29),
	INIT_ANON_OPS(30),
	INIT_ANON_OPS(31),
#if (__SIZEOF_POINTER__ * NBBY) > 32
	INIT_ANON_OPS(32),
	INIT_ANON_OPS(33),
	INIT_ANON_OPS(34),
	INIT_ANON_OPS(35),
	INIT_ANON_OPS(36),
	INIT_ANON_OPS(37),
	INIT_ANON_OPS(38),
	INIT_ANON_OPS(39),
	INIT_ANON_OPS(40),
	INIT_ANON_OPS(41),
	INIT_ANON_OPS(42),
	INIT_ANON_OPS(43),
	INIT_ANON_OPS(44),
	INIT_ANON_OPS(45),
	INIT_ANON_OPS(46),
	INIT_ANON_OPS(47),
	INIT_ANON_OPS(48),
	INIT_ANON_OPS(49),
	INIT_ANON_OPS(50),
	INIT_ANON_OPS(51),
	INIT_ANON_OPS(52),
	INIT_ANON_OPS(53),
	INIT_ANON_OPS(54),
	INIT_ANON_OPS(55),
	INIT_ANON_OPS(56),
	INIT_ANON_OPS(57),
	INIT_ANON_OPS(58),
	INIT_ANON_OPS(59),
	INIT_ANON_OPS(60),
	INIT_ANON_OPS(61),
	INIT_ANON_OPS(62),
	INIT_ANON_OPS(63),
#if (__SIZEOF_POINTER__ * NBBY) > 64
#error Unsupported sizeof(void *)
#endif /* (__SIZEOF_POINTER__ * NBBY) > 64 */
#endif /* (__SIZEOF_POINTER__ * NBBY) > 32 */
#endif /* (__SIZEOF_POINTER__ * NBBY) > 16 */
#endif /* (__SIZEOF_POINTER__ * NBBY) > 8 */
#undef INIT_ANON_OPS
#undef ANON_LOADBLOCKS_CALLBACK
};

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_C */
