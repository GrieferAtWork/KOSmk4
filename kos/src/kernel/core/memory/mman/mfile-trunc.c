/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_TRUNC_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_TRUNC_C 1
#define __WANT_MPART__mp_nodlsts
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/node.h>
#include <kernel/fs/super.h>
#include <kernel/mman/fault.h>
#include <kernel/mman/mfile-misaligned.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/mpartmeta.h>
#include <misc/unlockinfo.h>
#include <sched/atomic64.h>
#include <sched/sig.h>
#include <sched/task.h>

#include <hybrid/overflow.h>
#include <hybrid/sched/preemption.h>

#include <kos/except.h>

#include <assert.h>
#include <atomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

struct mpart_split_for_truncate {
	REF struct mpart *mpsft_part;            /* [0..1] The part that was split. */
	bool              mpsft_did_set_nomerge; /* True if we *did* set the NOMERGE flag for `mpsft_part' */
};

#define mpart_split_for_truncate_init(self) \
	(void)((self)->mpsft_part = NULL, (self)->mpsft_did_set_nomerge = false)

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_split_for_truncate_fini)(struct mpart_split_for_truncate *__restrict self) {
	if (self->mpsft_part) {
		if (self->mpsft_did_set_nomerge) {
			atomic_and(&self->mpsft_part->mp_flags, ~MPART_F_NOMERGE);
			decref_unlikely(mpart_merge(self->mpsft_part));
		} else {
			decref_unlikely(self->mpsft_part);
		}
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_split_for_truncate_setpart)(struct mpart_split_for_truncate *__restrict self,
                                                /*inherit(always)*/ REF struct mpart *__restrict part) {
	uintptr_half_t old_flags;
	/* Clear out any pre-existing part. */
	mpart_split_for_truncate_fini(self);

	/* Set-up the new part. */
	old_flags = atomic_fetchor(&part->mp_flags, MPART_F_NOMERGE);
	self->mpsft_part            = part; /* Inherit reference */
	self->mpsft_did_set_nomerge = (old_flags & MPART_F_NOMERGE) != 0;
}


/* Change  the size of the given file. If the new size is smaller than
 * the old size, mem-parts outside the new file's size-bounds are made
 * anonymous. When the size is increased, the behavior is the same  as
 * though  a  call `mfile_write(self, "", 1, new_size - 1)'  was made,
 * only that no actual write to the file is performed.
 *
 * @throw: E_FSERROR_READONLY:     The `MFILE_F_FIXEDFILESIZE' flag was set.
 * @throw: E_FSERROR_FILE_TOO_BIG: `new_size' is greater than the fs-specific limit. */
PUBLIC BLOCKING NONNULL((1)) void FCALL
mfile_truncate(struct mfile *__restrict self, pos_t new_size)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_READONLY,
		       E_FSERROR_FILE_TOO_BIG, ...) {
	struct mpart_split_for_truncate split_part;
	pos_t old_size;
	pos_t old_block_aligned_size;
	pos_t new_block_aligned_size;
	pos_t old_part_aligned_size;
	pos_t new_part_aligned_size;
	uintptr_t file_flags;

	/* Initialize our container to represent the special split-part. */
	mpart_split_for_truncate_init(&split_part);
	RAII_FINALLY { mpart_split_for_truncate_fini(&split_part); };

	/* Lock the file */
again:
	mfile_lock_write(self);
again_locked:

	/* Lookup the file's old size. */
	old_size = mfile_getsize(self);

	/* Check if the file has-been/is-being deleted.
	 * -> Also handle the case where the file's size may not be altered. */
	file_flags = atomic_read(&self->mf_flags);
	if (file_flags & (MFILE_F_DELETED | MFILE_F_DELETING | MFILE_F_FIXEDFILESIZE)) {
		mfile_lock_endwrite(self);
		if (new_size == old_size)
			return; /* Size didn't change! */
		if (file_flags & MFILE_F_DELETING) {
			/* Wait for the DELETING-flag to go away. */
			mfile_lock_endwrite(self);
			if (mfile_deleting_waitfor(self))
				goto again;
			file_flags |= MFILE_F_DELETED; /* File was deleted in the mean-time. */
		}
		if (new_size == 0) {
			/* Special case: you are allowed to truncate(2) a file to a size of `0'
			 *               when that file is also  anonymous, even if the  file's
			 *               size doesn't match  `0', and the  file itself has  the
			 *               FIXEDFILESIZE flag set.
			 * This is needed to get something like `echo 32 > /proc/kos/futexfd-maxexpr'
			 * working properly, as the ">"  operator includes O_TRUNC, which causes  the
			 * open to do `mfile_utruncate(node, 0)' during the open operation. */
			if (mfile_isanon(self) && (file_flags & MFILE_F_FIXEDFILESIZE))
				return;
			if (file_flags & MFILE_F_DELETED)
				return; /* Deleted files are effectively empty. */
		}
		THROW(E_FSERROR_READONLY);
	}

	/* Figure out how the new size stands in relation to the old size. */
	if (new_size > old_size) {
		/* Simple case: increase file size (only need a trunc-lock to do this). */
		bool ok;
		mfile_trunclock_inc_locked(self);
		ok = atomic64_cmpxch(&self->mf_filesize, (uint64_t)old_size, (uint64_t)new_size);
		mfile_lock_endwrite(self);
		if unlikely(!ok) {
			mfile_trunclock_dec(self);
			goto again;
		}
		mfile_trunclock_dec_nosignal(self);
		goto done_notify;
	}

	/* Make sure that there aren't any trunc-locks. */
	if (atomic_read(&self->mf_trunclock) != 0) {
		mfile_lock_endwrite(self);
		mfile_trunclock_waitfor(self);
		goto again;
	}

	/* Anonymize misaligned file parts that map to file parts that will go away. */
	if (!mfile_msalign_makeanon_locked_or_unlock(self, new_size, (pos_t)-1))
		goto again;

	/* Check if the effective number of blocks changed. */
	old_block_aligned_size = mfile_blockaddr_ceilalign(self, old_size);
	new_block_aligned_size = mfile_blockaddr_ceilalign(self, new_size);
#define LOCAL_old_block_aligned_size_overflows (old_block_aligned_size < old_size)
#define LOCAL_new_block_aligned_size_overflows (new_block_aligned_size < new_size)
	if ((old_block_aligned_size == new_block_aligned_size) &&
	    (LOCAL_old_block_aligned_size_overflows == LOCAL_new_block_aligned_size_overflows)) {
		/* Special case: file size is being lowered, but # of blocks doesn't change.
		 *
		 * In this case, we only  need to ensure that  no trunc-locks are held,  as
		 * well as that we've anonymized any overlapping misaligned file-parts, and
		 * then we can directly manipulate the file's size! */
		if (!atomic64_cmpxch(&self->mf_filesize, (uint64_t)old_size, (uint64_t)new_size))
			goto again_locked;
		mfile_lock_endwrite(self);
		goto done_notify;
	}

	/* Figure out the new part-aligned file sizes. */
	old_part_aligned_size = mfile_partaddr_ceilalign(self, old_size);
	new_part_aligned_size = mfile_partaddr_ceilalign(self, new_size);
#define LOCAL_old_part_aligned_size_overflows (old_part_aligned_size < old_size)
#define LOCAL_new_part_aligned_size_overflows (new_part_aligned_size < new_size)
	(void)old_part_aligned_size;


	/* The complicated case: we possibly need to get rid of mem-parts.
	 *
	 * This case needs to:
	 * - Ensure that preemption is enabled (since we need to acquire some
	 *   atomic locks further down below, and we can't have that fail due
	 *   to preemption being off)
	 * - Split a mem-part that may be overlapping with `new_part_aligned_size'
	 *   - Only do this if the part-tree of `self' isn't anonymous.
	 *   - The high-part of the split is special here in that we also set
	 *     the `MPART_F_NOMERGE' flag  for it (if  not set already),  and
	 *     remember if we *did* set it (because we want to clear it  once
	 *     again later)
	 *   - If something goes wrong form this point forth, clear the NOMERGE
	 *     flag from the high-part and then  try to re-merge it with  other
	 *     parts of the file.
	 * - Release the lock to `self'
	 *
	 * - Invoke `mo_freeblocks' (if defined) to free blocks that went away
	 *   - If errors happen here, call `mfile_deleting_rollback()'
	 *
	 * - Acquire a new lock to `self' (NOTHROW because preemption is on)
	 * - Acquire locks to all parts of `self' that will need to go away (locking here is NOTHROW because preemption is on)
	 * - Anonymize all parts that need to go away (at the same time, also drop locks from these parts)
	 * - Set the file's new size (unless the current size is `0')
	 *   - A 0-size might  get set if  the file is  being deleted at  the
	 *     same time, which is something we don't want to interfere with.
	 * - Release the lock to `self'
	 * - Clear the `MFILE_F_DELETING' flag of `self'.
	 * - Clear the `MPART_F_NOMERGE' flag from the part split above (if any).
	 * - Try to merge the part split above (if any).
	 * - Do the usual notification of the file-size-changed event.
	 */
	if unlikely(!preemption_ison()) {
		mfile_lock_endwrite(self);
		THROW(E_WOULDBLOCK_PREEMPTED);
	}

	/* Split a mem-part (if necessary) */
	if likely(self->mf_parts != MFILE_PARTS_ANONYMOUS) {
		REF struct mpart *splitme;
		splitme = mpart_tree_locate(self->mf_parts, new_part_aligned_size);
		if (splitme != NULL && mpart_getminaddr(splitme) != new_part_aligned_size) {
			REF struct mpart *hipart;
			if unlikely(!tryincref(splitme)) {
				mfile_lock_endwrite(self);
				goto again;
			}
			mfile_lock_endwrite(self);

			/* Split the part */
			FINALLY_DECREF_UNLIKELY(splitme);
			hipart = mpart_split(splitme, new_part_aligned_size);
			if likely(hipart)
				mpart_split_for_truncate_setpart(&split_part, hipart);
			goto again;
		}
	}

	/* Do everything needed to set the `MFILE_F_DELETING' flag. */
	if likely(!LOCAL_new_part_aligned_size_overflows) {
		if (!mfile_deleting_begin_locked_or_unlock(self, new_part_aligned_size, (pos_t)-1))
			goto again;
	} else {
		atomic_or(&self->mf_flags, MFILE_F_DELETING);
	}
	mfile_lock_endwrite(self);

	/* Invoke the free-blocks operator (if defined) */
	if (self->mf_ops->mo_freeblocks) {
		TRY {
			(*self->mf_ops->mo_freeblocks)(self,
			                               new_block_aligned_size,
			                               old_block_aligned_size - 1);
		} EXCEPT {
			mfile_deleting_rollback(self);
			RETHROW();
		}
	}

	/* ====== Point of no return ====== */

	/* Re-acquire a lock to `self' (NOTHROW because preemption is on) */
	assert(preemption_ison());
	NOEXCEPT_START {
		do {
			mfile_lock_write(self);
			if unlikely(self->mf_parts == MFILE_PARTS_ANONYMOUS)
				break;
			if unlikely(LOCAL_new_part_aligned_size_overflows)
				break;
		} while (!mfile_incref_and_lock_parts_r_or_unlock(self, new_part_aligned_size, (pos_t)-1));
	}
	NOEXCEPT_END;

	if likely(self->mf_parts != MFILE_PARTS_ANONYMOUS && !LOCAL_new_part_aligned_size_overflows) {
		REF struct mpart *dropped_part;
		while ((dropped_part = mpart_tree_rremove(&self->mf_parts, new_part_aligned_size, (pos_t)-1)) != NULL) {
			assert(!mpart_isanon(dropped_part));
			assert(mpart_lock_acquired(dropped_part));

			/* Mark this mem-part as anonymous. */
			DBG_memset(&dropped_part->mp_filent.rb_lhs, 0xcc, sizeof(dropped_part->mp_filent.rb_lhs));
			dropped_part->mp_filent.rb_rhs = NULL; /* Indicator for `mpart_trim()' */
			atomic_write(&dropped_part->mp_filent.rb_par, (struct mpart *)-1);

			/* TODO: Posix wants access to SHARED nodes of `part' after this point to raise SIGBUS */

			/* Assign the relevant anonymous-memory file for use during any future access. */
			assert(dropped_part->mp_file == self);
			dropped_part->mp_file = incref(&mfile_anon[self->mf_blockshift]);
			decref_nokill(self); /* Old reference from `dropped_part->mp_file' */
			if (dropped_part->mp_flags & MPART_F_CHANGED) {
				if likely(self->mf_changed.slh_first != MFILE_PARTS_ANONYMOUS) {
					/* Remove from the list of changed mem-parts. */
					SLIST_REMOVE(&self->mf_changed, dropped_part, mp_changed);
					decref_nokill(dropped_part); /* From `self->mf_changed' */
				}
				atomic_and(&dropped_part->mp_flags, ~MPART_F_CHANGED);
			}
			DBG_memset(&dropped_part->mp_changed, 0xcc, sizeof(dropped_part->mp_changed));

			/* Anonymous parts mustn't be holding global references! */
			if ((dropped_part->mp_flags & MPART_F_GLOBAL_REF) &&
			    (atomic_fetchand(&dropped_part->mp_flags, ~MPART_F_GLOBAL_REF) & MPART_F_GLOBAL_REF))
				decref_nokill(dropped_part);

			/* All blocks of `dropped_part' with status LOAD must be set to CHNG.
			 *
			 * Since  we changed the  part to be  anonymous, any block that
			 * is loaded into memory (and isn't all 0-es) no longer matches
			 * the default initializer  of `mfile_anon', which  initializes
			 * to all 0-es. As such, we have to mark such blocks as changed */
			if (MPART_ST_INCORE(dropped_part->mp_state) &&
				((dropped_part->mp_flags & MPART_F_BLKST_INL) || dropped_part->mp_blkst_ptr)) {
				size_t i, count = mpart_getblockcount(dropped_part, self);
				for (i = 0; i < count; ++i) {
					unsigned int st = mpart_getblockstate(dropped_part, i);
					if (st == MPART_BLOCK_ST_LOAD) {
						/* NOTE: Technically only required if the block's
						 *       backing physical memory  isn't all  0-es */
						mpart_setblockstate(dropped_part, i, MPART_BLOCK_ST_CHNG);
					}
				}
			}

			/* And with that, this part's been marked made anonymous! */
			mpart_lock_release(dropped_part);

			/* Try to merge+trim the dropped part. */
			dropped_part = mpart_merge(dropped_part);
			mpart_trim(dropped_part); /* This inherits our final reference to the part! */
		}
	}

	/* Set the new file size (but be careful not to do so if the current size is `0') */
	while (!atomic64_cmpxch(&self->mf_filesize, (uint64_t)old_size, (uint64_t)new_size)) {
		old_size = (pos_t)atomic64_read(&self->mf_filesize);
		if (old_size == 0)
			break;
	}

	/* Release the lock to `self' */
	mfile_lock_endwrite(self);

	/* Clear the `MFILE_F_DELETING' flag of `self'. */
	atomic_and(&self->mf_flags, ~MFILE_F_DELETING);

	/* And we're done! */
done_notify:
	sig_broadcast(&self->mf_initdone);        /* Because the file size changed. */
	mfile_changed(self, MFILE_F_ATTRCHANGED); /* *ditto* */
#undef LOCAL_new_part_aligned_size_overflows
#undef LOCAL_old_part_aligned_size_overflows
#undef LOCAL_new_block_aligned_size_overflows
#undef LOCAL_old_block_aligned_size_overflows
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_TRUNC_C */
