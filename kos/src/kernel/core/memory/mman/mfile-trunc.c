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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_TRUNC_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_TRUNC_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/node.h>
#include <kernel/fs/super.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/mpartmeta.h>
#include <misc/unlockinfo.h>
#include <sched/atomic64.h>
#include <sched/sig.h>
#include <sched/task.h>

#include <hybrid/overflow.h>

#include <kos/except.h>

#include <assert.h>
#include <atomic.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */


/* Ensure that no mem-parts with `mpart_getminaddr() >= minaddr' exists within `self'
 * for  which `mpart_hasblocksstate_init()' is  the case. If any  such part is found,
 * then   `mfile_unlock_and_decref_parts(self), mfile_lock_endwrite(self);'    before
 * waiting for the found  part to no longer  feature INIT-blocks and return  `false'.
 *
 * When no parts with init-blocks above `minaddr' are found, don't release any locks
 * and return `true'. */
PRIVATE BLOCKING WUNUSED NONNULL((1)) bool FCALL
mfile_ensure_no_ST_INIT_for_parts_above_or_unlock_and_decref(struct mfile *__restrict self,
                                                             pos_t minaddr)
		THROWS(...) {
	struct mpart *iter;
	struct mpart_tree_minmax mima;
	mpart_tree_minmaxlocate(self->mf_parts, minaddr, (pos_t)-1, &mima);
	if (mima.mm_min != NULL) {
		for (iter = mima.mm_min;;) {
			if unlikely(mpart_hasblocksstate_init(iter)) {
				/* Damn it! - have to wait for this one... */
				incref(iter);
				mfile_unlock_and_decref_parts(self);
				mfile_lock_endwrite(self);
				FINALLY_DECREF_UNLIKELY(iter);
				task_connect(&self->mf_initdone);
				for (;;) {
					bool hasinit;
					TRY {
						mpart_lock_acquire(iter);
					} EXCEPT {
						task_disconnectall();
						RETHROW();
					}
					hasinit = mpart_hasblocksstate_init(iter);
					mpart_lock_release(iter);
					if (!hasinit)
						break;
					task_waitfor();
				}
				task_disconnectall();
				return false;
			}

			/* Another addendum: in order to fully anonymize a mem-part,
			 * we also have to remove  it from the changed-part list  of
			 * the associated file when `MPART_F_CHANGED' was set.
			 *
			 * However, we can only  clear `MPART_F_CHANGED' if the  part
			 * doesn't have any DMA locks (we know that `MPART_F_CHANGED'
			 * won't get set because it only  can when holding a lock  to
			 * the mem-part, which  we're already the  only ones who  can
			 * do so). */
			if (iter->mp_flags & MPART_F_CHANGED) {
				if unlikely(self->mf_changed.slh_first == MFILE_PARTS_ANONYMOUS) {
					atomic_and(&iter->mp_flags, ~MPART_F_CHANGED);
					DBG_memset(&iter->mp_changed, 0xcc, sizeof(iter->mp_changed));
				} else {
					struct mpartmeta *meta = iter->mp_meta;
					assert(self->mf_changed.slh_first != NULL);
					if (meta != NULL && atomic_read(&meta->mpm_dmalocks) != 0) {
						/* Have to wait for this one... */
						incref(iter);
						mfile_unlock_and_decref_parts(self);
						mfile_lock_endwrite(self);
						FINALLY_DECREF_UNLIKELY(iter);
						task_connect(&meta->mpm_dma_done);
						if unlikely(atomic_read(&meta->mpm_dmalocks) == 0) {
							task_disconnectall();
							return false;
						}
						task_waitfor();
						return false;
					}
				}
			}

			if (iter == mima.mm_max)
				break;
			iter = mpart_tree_nextnode(iter);
			assert(iter);
		}
	}
	return true;
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
	pos_t old_size;
	pos_t aligned_old_size;
	pos_t aligned_new_size;
again:
	old_size = mfile_getsize(self);
	if (new_size >= old_size) {
handle_newsize_ge_oldsize:
		if (new_size == old_size)
			return; /* Nothing changed... */

		/* Check that the new file size is allowed by the filesystem. */
		if (mfile_isnode(self)) {
			struct fnode *node = mfile_asnode(self);
			/* Just like `mfile_write()', we throw a file-too-big error
			 * when trying to increase a file beyond the logical limits
			 * of the underlying physical medium. */
			if unlikely(new_size > node->fn_super->fs_feat.sf_filesize_max)
				THROW(E_FSERROR_FILE_TOO_BIG);
		}

		/* Simple  case: increasing a file's size is as simple as getting
		 * a write-lock to `self->mf_lock', then using that lock to  also
		 * get a trunc-lock, before finally doing a cmpxch to set the new
		 * file size (before notifying the system about attributes having
		 * changed) */
		mfile_lock_write(self); /* Normal lock */

		/* Check if we're allowed to modify the file's size. */
		if unlikely(self->mf_flags & MFILE_F_FIXEDFILESIZE) {
			mfile_lock_endwrite(self);
			THROW(E_FSERROR_READONLY);
		}

		mfile_trunclock_inc(self); /* Trunc-lock (needed for specs and tracing of file-size changes) */
		mfile_lock_endwrite(self); /* Don't need the normal lock anymore (trunc is enough to prevent file size reductions) */

		/* Try to set the new file size. */
		if (!atomic64_cmpxch(&self->mf_filesize,
		                     (uint64_t)old_size,
		                     (uint64_t)new_size)) {
			mfile_trunclock_dec(self);
			goto again;
		}

		/* *_nosignal because we unconditionally broadcast because of the file size changed. */
		mfile_trunclock_dec_nosignal(self);

		/* Always broadcast because we've just increased the file's size! */
		sig_broadcast(&self->mf_initdone);

		/* Notify about file attributes having changed. */
		mfile_changed(self, MFILE_F_ATTRCHANGED);
		return;
	}

	/* Check if we're allowed to modify the file's size. */
	if unlikely(self->mf_flags & MFILE_F_FIXEDFILESIZE) {
		/* Special case: you are allowed to truncate(2) a file to a size of `0'
		 *               when that file is also  anonymous, even if the  file's
		 *               size doesn't match  `0', and the  file itself has  the
		 *               FIXEDFILESIZE flag set.
		 * This is needed to get something like `echo 32 > /proc/kos/futexfd-maxexpr'
		 * working properly, as the ">"  operator includes O_TRUNC, which causes  the
		 * open to do `mfile_utruncate(node, 0)' during the open operation. */
		if (new_size == 0 && mfile_isanon(self))
			return;
		THROW(E_FSERROR_READONLY);
	}

	/* The complicated case: need to _reduce_ the file size:
	 *  #1:  Acquire a write-lock `mfile_lock_write(self);'
	 *  #2:  Check if `mf_trunclock == 0'. If not, wait for it to become so
	 *  #3:  If `mf_parts == MFILE_PARTS_ANONYMOUS', directly modify the file size.
	 *  #4:  Calculated `aligned_old_size' and `aligned_new_size'. If
	 *       these don't differ, then directly modify the file  size.
	 *  #5:  Acquire references+locks to _all_ mem-parts (from `mf_parts') (yes: all; there is no way around this)
	 *       Parts for which no reference could be acquired are silently removed from
	 *       the part-tree (we can do this because we're holding a write-lock),  thus
	 *       guarantying that _all_ mem-parts from the part-tree are `!wasdestroyed'.
	 *       Also make sure that `!mpart_hasblocksstate_init' for any mem-part  which
	 *       may need to be anonymized in step #8.
	 *  #6:  Check if a mem-part exists  that overlaps with `aligned_new_size',  but
	 *       doesn't border against it. If so, release part-locks & references, then
	 *       split  said part by use of `mpart_split()'. After the split, re-acquire
	 *       locks  and references and  check if something changed.  If it turns out
	 *       that the newly  split part  didn't have to  be split,  release locks  &
	 *       references once again, `mpart_merge()' the newly split part, and  start
	 *       over from scratch.
	 *  #7:  Update `mf_filesize' from `old_size' to  `new_size'. If it turns out  that
	 *       the file's size changed since it was read above, re-merge a possibly split
	 *       part from #6 and start over from scratch.
	 *  #8:  Remove all mem-parts from the part-tree which have a min-address that
	 *       is `>= aligned_new_size'. Because of the split, it is guaranted  that
	 *       there isn't any part that overlaps with `aligned_new_size'.
	 *  #9:  Make all of the removed mem-parts anonymous and release the
	 *       lock still held on each  of them before decref()-ing  each.
	 *  #10: Release locks + references from all of the remaining mem-
	 *       parts which still remain  apart of the file's  part-tree.
	 *  #11: Release the write-lock `mfile_lock_endwrite(self);'
	 *  #12: Broadcast `&self->mf_initdone'
	 *  #13: Notify `mfile_changed(self, MFILE_F_ATTRCHANGED);'
	 */

	/* Step #1: Acquire a write-lock `mfile_lock_write(self);' */
	mfile_lock_write(self);

	/* Step #2: Check if `mf_trunclock == 0'. If not, wait for it to become so
	 * NOTE: Because we're holding a lock `mfile_lock_write(self)',
	 *       the trunc lock can't be incremented by other  threads! */
	if (self->mf_trunclock != 0) {
		mfile_lock_endwrite(self);
		assert(!task_wasconnected());

		/* `mf_initdone' is broadcast when `mf_trunclock' hits `0' */
		task_connect(&self->mf_initdone);

		/* Verify that  the foreign  trunc-lock still  exists.
		 * Also check that the file-size hasn't changed again. */
		if unlikely(atomic_read(&self->mf_trunclock) != 0 ||
		            old_size != mfile_getsize(self)) {
			task_disconnectall();
			goto again;
		}

		/* Do the wait... */
		task_waitfor();
		goto again;
	}

	/* Step #3: If `mf_parts == MFILE_PARTS_ANONYMOUS', directly modify the file size. */
	if unlikely(self->mf_parts == MFILE_PARTS_ANONYMOUS) {
		bool ok;
directly_modify_file_size:
		ok = atomic64_cmpxch(&self->mf_filesize,
		                     (uint64_t)old_size,
		                     (uint64_t)new_size);
		mfile_lock_endwrite(self);
		if (!ok)
			goto again;
		sig_broadcast(&self->mf_initdone);        /* Because the file size changed. */
		mfile_changed(self, MFILE_F_ATTRCHANGED); /* *ditto* */
		return;
	}

	/* Step #4: Calculated `aligned_old_size' and `aligned_new_size'. If
	 *          these don't differ, then directly modify the file  size.
	 * Note that we have to be careful because both the old and new file
	 * size can overflow once ceil-aligned. */
	if (OVERFLOW_UADD(new_size, self->mf_part_amask, &aligned_new_size)) {
		/* The aligned value of the new size overflows. When this happens,
		 * then we know that (since `new_size < old_size'), the file's old
		 * size  must point somewhere into the range of what is physically
		 * possible to represent by `pos_t'
		 *
		 * As such, we also know that the "aligned" file sizes won't  differ,
		 * since both the new and old size would overflow in the same manner. */
		assertf((old_size >> self->mf_blockshift) ==
		        (new_size >> self->mf_blockshift),
		        "Something's wrong with the logic: new_size < old_size, "
		        "and new_size overflows, meaning that old_size should "
		        "have overflowed in the same manner...");
		goto directly_modify_file_size;
	}
	aligned_new_size = mfile_partaddr_flooralign(self, aligned_new_size);

	if (OVERFLOW_UADD(old_size, self->mf_part_amask, &aligned_old_size)) {
		/* In this case, we're guarantied that `aligned_old_size' would differ  from
		 * `aligned_new_size', such that `aligned_old_size > aligned_new_size', even
		 * if we're unable to properly calculate `aligned_old_size' (since it  can't
		 * be represented) */
	} else {
		aligned_old_size = mfile_partaddr_flooralign(self, aligned_old_size);
		assertf(aligned_old_size >= aligned_new_size,
		        "But we already know that `old_size >= new_size', so how can this be?");

		/* Check for simple case: the aligned file size didn't change. */
		if (aligned_old_size == aligned_new_size)
			goto directly_modify_file_size;
	}
	/* Aligned file-size changed! */

	/* Step #5: Acquire references+locks  to _all_ mem-parts (from  `mf_parts')
	 * Parts for which no reference could be acquired are silently removed from
	 * the part-tree (we can do this because we're holding a write-lock),  thus
	 * guarantying that _all_ mem-parts from the part-tree are `!wasdestroyed'. */
	{
		REF struct mpart *blocking_part;
		blocking_part = mfile_tryincref_and_lock_parts(self);
		if unlikely(blocking_part) {
			mfile_lock_endwrite(self);
			FINALLY_DECREF_UNLIKELY(blocking_part);
			mpart_lock_waitfor(blocking_part);
			goto again;
		}
		if (!mfile_ensure_no_ST_INIT_for_parts_above_or_unlock_and_decref(self, aligned_new_size))
			goto again;
	}

	/* Step #6: Check if a mem-part exists  that overlaps with `aligned_new_size',  but
	 *          doesn't border against it. If so, release part-locks & references, then
	 *          split  said part by use of `mpart_split()'. After the split, re-acquire
	 *          locks  and references and  check if something changed.  If it turns out
	 *          that the newly  split part  didn't have to  be split,  release locks  &
	 *          references once again, `mpart_merge()' the newly split part, and  start
	 *          over from scratch. */
	{
		struct mpart *overlapping_part;
		overlapping_part = mpart_tree_locate(self->mf_parts, aligned_new_size);
		if (overlapping_part &&
		    mpart_getminaddr(overlapping_part) != aligned_new_size) {
			REF struct mpart *blocking_part;

again_handle_overlapping_part:
			/* Must split this part... */
			incref(overlapping_part);
			mfile_unlock_and_decref_parts(self);
			mfile_lock_endwrite(self);
			{
				FINALLY_DECREF_UNLIKELY(overlapping_part);
				overlapping_part = mpart_split(overlapping_part, aligned_new_size);
			}
			if unlikely(!overlapping_part)
				goto again; /* Race condition: someone else also split this part before us! */

			/* Re-acquire locks. */
again_reacquire_after_split:
			TRY {
				/* Check-check if stuff changed. */
				old_size = mfile_getsize(self);
				if unlikely(new_size >= old_size) {
					decref_unlikely(mpart_merge(overlapping_part));
					goto handle_newsize_ge_oldsize;
				}
				mfile_lock_write(self);
				if unlikely(self->mf_flags & MFILE_F_FIXEDFILESIZE) {
					mfile_lock_endwrite(self);
					THROW(E_FSERROR_READONLY);
				}
				if (!OVERFLOW_UADD(old_size, self->mf_part_amask, &aligned_old_size)) {
					aligned_old_size = mfile_partaddr_flooralign(self, aligned_old_size);
					assert(aligned_old_size >= aligned_new_size);
					if (aligned_old_size == aligned_new_size) {
						decref_unlikely(mpart_merge(overlapping_part));
						goto directly_modify_file_size;
					}
				}
				if (self->mf_trunclock != 0) {
					mfile_lock_endwrite(self);
					assert(!task_wasconnected());
					task_connect(&self->mf_initdone);
					if unlikely(atomic_read(&self->mf_trunclock) != 0) {
						task_disconnectall();
						goto again_reacquire_after_split;
					}
					task_waitfor();
					goto again_reacquire_after_split;
				}
				blocking_part = mfile_tryincref_and_lock_parts(self);
				if unlikely(blocking_part) {
					mfile_lock_endwrite(self);
					FINALLY_DECREF_UNLIKELY(blocking_part);
					mpart_lock_waitfor(blocking_part);
					goto again_reacquire_after_split;
				}
				if (!mfile_ensure_no_ST_INIT_for_parts_above_or_unlock_and_decref(self, aligned_new_size))
					goto again_reacquire_after_split;
			} EXCEPT {
				decref_unlikely(mpart_merge(overlapping_part));
				RETHROW();
			}
			{
				struct mpart *new_overlapping_part;
				new_overlapping_part = mpart_tree_locate(self->mf_parts, aligned_new_size);
				if (new_overlapping_part &&
				    mpart_getminaddr(new_overlapping_part) != aligned_new_size) {
					decref_unlikely(mpart_merge(overlapping_part));
					overlapping_part = new_overlapping_part;
					goto again_handle_overlapping_part;
				}
			}

			/* Do step #7 while we still know about `overlapping_part' */
			if (!atomic64_cmpxch(&self->mf_filesize, (uint64_t)old_size, (uint64_t)new_size)) {
				mfile_unlock_and_decref_parts(self);
				mfile_lock_endwrite(self);
				decref_unlikely(mpart_merge(overlapping_part));
				goto again_reacquire_after_split;
			}

			decref_unlikely(overlapping_part);
			goto after_file_size_changed;
		} /* if (HAVE_OVERLAPPING_PART) */
	}     /* Scope... */

	/* Step #7: Update `mf_filesize' from `old_size' to  `new_size'. If it turns out  that
	 *          the file's size changed since it was read above, re-merge a possibly split
	 *          part from #6 and start over from scratch. */
	if (atomic64_read(&self->mf_filesize) != (uint64_t)old_size) {
		mfile_unlock_and_decref_parts(self);
		mfile_lock_endwrite(self);
		goto again;
	}

	atomic64_write(&self->mf_filesize, (uint64_t)new_size);

after_file_size_changed:
	/* Step #8: Remove all mem-parts from the part-tree which have a min-address that
	 *          is `>= aligned_new_size'. Because of the split, it is guaranted  that
	 *          there isn't any part that overlaps with `aligned_new_size'. */
	for (;;) {
		REF struct mpart *part;
		/* NOTE: Normally, the mem-part tree doesn't contain references, but right
		 *       now it  does, as  `mfile_tryincref_and_lock_parts' created  some. */
		part = mpart_tree_rremove(&self->mf_parts, aligned_new_size, (pos_t)-1);
		if (!part)
			break;

		/* Step #9: Make all of the removed mem-parts anonymous and release the
		 *          lock still held on each  of them before decref()-ing  each. */

		/* Mark this mem-part as anonymous.
		 * This is why we had to ensure that none of the parts above the truncation
		 * boundary had init-blocks (`!mpart_hasblocksstate_init'). Because so-long
		 * as a mem-part got init-blocks, we're not allowed to make it anon. */
		assert(!mpart_isanon(part));
		DBG_memset(&part->mp_filent.rb_lhs, 0xcc, sizeof(part->mp_filent.rb_lhs));
		part->mp_filent.rb_rhs = NULL; /* Indicator for `mpart_trim()' */

		/* Mark the part as anonymous */
		atomic_write(&part->mp_filent.rb_par, (struct mpart *)-1);

		/* Assign the relevant anonymous-memory file for use during any future access. */
		assert(part->mp_file == self);
		part->mp_file = incref(&mfile_anon[self->mf_blockshift]);
		decref_nokill(self); /* Old reference from `part->mp_file' */

		if (part->mp_flags & MPART_F_CHANGED) {
			assertf(!part->mp_meta ||
			        !part->mp_meta->mpm_dmalocks,
			        "Ensured by `mfile_ensure_no_ST_INIT_for_parts_above_or_unlock_and_decref()'");
			if likely(self->mf_changed.slh_first != MFILE_PARTS_ANONYMOUS) {
				assertf(self->mf_ops->mo_saveblocks != NULL,
				        "MPART_F_CHANGED+mf_changed!=ANON imply the presence of this operator");
				/* Remove from the list of changed mem-parts. */
				SLIST_REMOVE(&self->mf_changed, part, mp_changed);
				decref_nokill(part); /* From `self->mf_changed' */
			}
			atomic_and(&part->mp_flags, ~MPART_F_CHANGED);
		}
		DBG_memset(&part->mp_changed, 0xcc, sizeof(part->mp_changed));

		/* Anonymous parts mustn't be holding global references! */
		if ((part->mp_flags & MPART_F_GLOBAL_REF) &&
		    (atomic_fetchand(&part->mp_flags, ~MPART_F_GLOBAL_REF) & MPART_F_GLOBAL_REF))
			decref_nokill(part);

		/* And with that, this part's been marked made anonymous! */
		mpart_lock_release(part);
		decref_unlikely(part);
	}

	/* Step #10: Release locks + references from all of the remaining mem-
	 *           parts which still remain  apart of the file's  part-tree. */
	mfile_unlock_and_decref_parts(self);

	/* Step #11: Release the write-lock `mfile_lock_endwrite(self);' */
	mfile_lock_endwrite(self);

	/* Step #12: Broadcast `&self->mf_initdone' */
	sig_broadcast(&self->mf_initdone);

	/* Step #13: Notify `mfile_changed(self, MFILE_F_ATTRCHANGED);' */
	mfile_changed(self, MFILE_F_ATTRCHANGED);
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_TRUNC_C */
