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
#include <kernel/mman/fault.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
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


struct mpart_load_private_node_or_unlock_unlockinfo {
	struct unlockinfo mplpnouu_info; /* Underlying unlockinfo */
	struct mpart     *mplpnouu_part; /* [1..1] The part in question (caller manages lock for this one) */
	struct mfile     *mplpnouu_file; /* [1..1] The file in question. */
};

PRIVATE NONNULL((1)) void
NOTHROW(FCALL mpart_load_private_node_or_unlock_unlockcb)(struct unlockinfo *__restrict self) {
	struct mpart_load_private_node_or_unlock_unlockinfo *info;
	info = container_of(self, struct mpart_load_private_node_or_unlock_unlockinfo, mplpnouu_info);
	/* Unlock+decref all parts except for the one whose lock our caller is managing. */
	mfile_unlock_and_decref_parts_except(info->mplpnouu_file, info->mplpnouu_part);
	mfile_lock_endwrite(info->mplpnouu_file);
	/* Original part reference (caller is still holding another, so *_nokill) */
	decref_nokill(info->mplpnouu_part);
}

PRIVATE BLOCKING NONNULL((1, 4)) bool FCALL
mpart_load_private_node_setcore_or_unlock(struct mpart *__restrict self,
                                          mpart_reladdr_t minaddr, size_t num_bytes,
                                          struct unlockinfo *unlock) {
	bool ok;
	struct mpart_setcore_data sc_data;

	/* If the part hasn't been loaded into the core, and the area  we're
	 * going to access isn't very large, then try to split the part into
	 * a couple of  smaller parts, so  that the range  that needs to  be
	 * loaded into the core (read: allocated) becomes smaller. */
	if (!mpart_maybesplit_or_unlock(self, unlock, minaddr, num_bytes))
		return false;

	/* Force-allocate this mem-part. */
	mpart_setcore_data_init(&sc_data);
	incref(self);
	FINALLY_DECREF_UNLIKELY(self);
	TRY {
		ok = mpart_setcore_or_unlock(self, unlock, &sc_data);
		if (!ok) {
			do {
				mpart_lock_acquire(self);
			} while (!mpart_setcore_or_unlock(self, NULL, &sc_data));
			mpart_lock_release(self);
		}
	} EXCEPT {
		mpart_setcore_data_fini(&sc_data);
		RETHROW();
	}
	return ok;
}

PRIVATE BLOCKING NONNULL((1)) bool FCALL
mpart_load_private_node_or_unlock(struct mpart *__restrict self,
                                  mpart_reladdr_t minaddr, size_t num_bytes) {
	struct mpart_load_private_node_or_unlock_unlockinfo unlock;
	unlock.mplpnouu_info.ui_unlock = &mpart_load_private_node_or_unlock_unlockcb;
	unlock.mplpnouu_file           = self->mp_file;
	unlock.mplpnouu_part           = self;

	/* Must also assert that the part is allocated. */
	if (!MPART_ST_INCORE(self->mp_state)) {
		bool ok;
		ok = mpart_load_private_node_setcore_or_unlock(self, minaddr, num_bytes,
		                                               &unlock.mplpnouu_info);
		if (!ok)
			return false;
	}

	return mpart_load_or_unlock(self, &unlock.mplpnouu_info, minaddr, num_bytes);
}


INTDEF NOBLOCK NONNULL((1)) void /* From "./mpart-trim.c" */
NOTHROW(FCALL mnode_list_sort_by_partoff)(struct mnode_list *__restrict self);

/* Ensure that all blocks mapped by MAP_PRIVATE nodes of `self'
 * that map at least 1 byte above `minaddr' have a block-status
 * of MPART_BLOCK_ST_LOAD or MPART_BLOCK_ST_CHNG. */
PRIVATE BLOCKING NONNULL((1)) bool FCALL
mpart_load_private_nodes_or_unlock(struct mpart *__restrict self,
                                   mpart_reladdr_t minaddr) {
	struct mnode *node;

	/* Enumerate copy-on-write (iow: MAP_PRIVATE) nodes of `self' */
	mnode_list_sort_by_partoff(&self->mp_copy);
	node = LIST_FIRST(&self->mp_copy);
	while (node) {
		bool ok;
		mpart_reladdr_t node_minaddr, node_endaddr;
		assert(node->mn_part == self);
		node_minaddr = mnode_getpartminaddr(node);
		node_endaddr = mnode_getpartendaddr(node);
		if (node_minaddr < minaddr) {
			node_minaddr = minaddr;
			if (node_minaddr >= node_endaddr) {
				node = LIST_NEXT(node, mn_link);
				continue;
			}
		}
		assert(node_minaddr < node_endaddr);

		/* Check for adjacent nodes. */
		while ((node = LIST_NEXT(node, mn_link)) != NULL) {
			PAGEDIR_PAGEALIGNED mpart_reladdr_t nextnode_minaddr;
			PAGEDIR_PAGEALIGNED mpart_reladdr_t nextnode_endaddr;
			assert(node->mn_part == self);
			nextnode_minaddr = mnode_getpartminaddr(node);
			nextnode_endaddr = mnode_getpartendaddr(node);
			if (nextnode_minaddr > node_endaddr)
				break; /* There's a gap after the end of the relevant range. */
			if (node_endaddr < nextnode_endaddr) {
				/* Extend  load-range  to  include  this  node,
				 * since it overlaps/extends our current range. */
				node_endaddr = nextnode_endaddr;
			}
		}

		/* Ensure that this sub-range is loaded. */
		ok = mpart_load_private_node_or_unlock(self, node_minaddr,
		                                       node_endaddr - node_minaddr);
		if (!ok)
			return false;
	}

	return true;
}

/* Ensure that blocks of all sub-ranges of MAP_PRIVATE-nodes of parts above
 * `new_size' have status  `MPART_BLOCK_ST_LOAD' or  `MPART_BLOCK_ST_CHNG'. */
PRIVATE BLOCKING NONNULL((1)) bool FCALL
mfile_do_load_private_nodes_above_or_unlock(struct mfile *__restrict self,
                                            pos_t new_size) {
	struct mpart *iter;
	struct mpart_tree_minmax mima;
	assert(mfile_lock_writing(self));
	assert(self->mf_parts != NULL);
	assert(self->mf_parts != MFILE_PARTS_ANONYMOUS);
	mpart_tree_minmaxlocate(self->mf_parts, new_size, (pos_t)-1, &mima);
	assert((mima.mm_min != NULL) == (mima.mm_max != NULL));
	if (mima.mm_min == NULL)
		return true;
	for (iter = mima.mm_min;;) {
		bool ok;
		mpart_reladdr_t minaddr = 0;
		if (mpart_getminaddr(iter) < new_size) {
			assert(mpart_getmaxaddr(iter) >= new_size);
			minaddr = (mpart_reladdr_t)(new_size - mpart_getminaddr(iter));
		}
		assertf(mpart_lock_acquired(iter), "Caller should be holding locks to all parts");
		assert(iter->mp_file == self);
		ok = mpart_load_private_nodes_or_unlock(iter, minaddr);
		if (!ok)
			return false;
		if (iter == mima.mm_max)
			break;
		iter = mpart_tree_nextnode(iter);
		assert(iter);
	}
	return true;
}

PRIVATE BLOCKING NONNULL((1)) bool FCALL
mfile_load_private_nodes_above_or_unlock(struct mfile *__restrict self,
                                         pos_t new_size) {
	bool result;
	result = mfile_do_load_private_nodes_above_or_unlock(self, new_size);
	if (unlikely(atomic_read(&self->mf_msalign.lh_first) != NULL) && result) {
		/* Must also load uninitialized nodes from all sub-files of `self'
		 * that were  created  using  `mfile_create_misaligned_wrapper()'! */
		/* TODO */
	}
	return result;
}




/* Callback that may ONLY be invoked from `mso_freeblocks_or_unlock', where it MUST
 * be called if the function  wants to do something that  might block, prior to  it
 * returning `false' or by throwing an exception. */
PUBLIC NONNULL((1)) void
NOTHROW(FCALL mfile_freeblocks_unlock)(struct mfile *__restrict self,
                                       pos_t aligned_new_size) {
	REF struct mpart *overlapping_part;
	overlapping_part = mpart_tree_locate(self->mf_parts, aligned_new_size);
	if (overlapping_part) {
		if (mpart_getminaddr(overlapping_part) == aligned_new_size) {
			incref(overlapping_part);
		} else {
			overlapping_part = NULL;
		}
	}
	mfile_unlock_and_decref_parts(self);
	mfile_lock_endwrite(self);
	if (overlapping_part != NULL)
		decref_unlikely(mpart_merge(overlapping_part));
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
	REF struct mpart *overlapping_part;
	struct mfile_freeblocks_token token;
#define LOCAL_fini_token() (token.mfbt_fini ? (*token.mfbt_fini)(&token) : (void)0)
	pos_t old_size;
	pos_t aligned_old_size;
	pos_t aligned_new_size;
	bzero(&token, sizeof(token));
again:
	TRY {
		old_size = mfile_getsize(self);
		if (new_size >= old_size) {
handle_newsize_ge_oldsize:
			if (new_size == old_size) {
				LOCAL_fini_token();
				return; /* Nothing changed... */
			}

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
			LOCAL_fini_token();
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
			if (new_size == 0 && mfile_isanon(self)) {
				LOCAL_fini_token();
				return;
			}
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
			LOCAL_fini_token();
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

		/* Step #5.1: Make sure that all sub-ranges of parts mapped above `new_size' and
		 *            using MAP_PRIVATE-semantics are loaded into memory. This is needed
		 *            to ensure that MAP_PRIVATE captures a snap-shot at the point where
		 *            the mapping was  created, and  won't be affected  by a  subsequent
		 *            ftruncate.
		 * This is required to ensure that MAP_PRIVATE mappings retain their original
		 * content even after the  part of the  file that they  are mapping has  been
		 * truncated. */
		if (!mfile_load_private_nodes_above_or_unlock(self, new_size))
			goto again;

		/* Step #6: Check if a mem-part exists  that overlaps with `aligned_new_size',  but
		 *          doesn't border against it. If so, release part-locks & references, then
		 *          split  said part by use of `mpart_split()'. After the split, re-acquire
		 *          locks  and references and  check if something changed.  If it turns out
		 *          that the newly  split part  didn't have to  be split,  release locks  &
		 *          references once again, `mpart_merge()' the newly split part, and  start
		 *          over from scratch. */
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

			/* Re-check for an overlapping part. */
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
			if (atomic64_read(&self->mf_filesize) != (uint64_t)old_size) {
				mfile_unlock_and_decref_parts(self);
				mfile_lock_endwrite(self);
				decref_unlikely(mpart_merge(overlapping_part));
				goto again_reacquire_after_split;
			}

			decref_unlikely(overlapping_part);
			goto everything_confirmed;
		} /* if (HAVE_OVERLAPPING_PART) */

		/* Step #7: Update `mf_filesize' from `old_size' to  `new_size'. If it turns out  that
		 *          the file's size changed since it was read above, re-merge a possibly split
		 *          part from #6 and start over from scratch. */
		if (atomic64_read(&self->mf_filesize) != (uint64_t)old_size) {
			mfile_unlock_and_decref_parts(self);
			mfile_lock_endwrite(self);
			goto again;
		}

everything_confirmed:
		/* Invoke the free-blocks operator (if defined) */
		if (self->mf_ops->mo_stream &&
		    self->mf_ops->mo_stream->mso_freeblocks_or_unlock) {
			bool ok;
			ok = (*self->mf_ops->mo_stream->mso_freeblocks_or_unlock)(self, &token, aligned_new_size);
			if (!ok)
				goto again;
			DBG_memset(&token, 0xcc, sizeof(token));
		}

	} EXCEPT {
		LOCAL_fini_token();
		RETHROW();
	}


	/************************************************************************/
	/* POINT OF NO RETURN                                                   */
	/************************************************************************/

	/* Store the file's new size. */
	atomic64_write(&self->mf_filesize, (uint64_t)new_size);

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

		/* TODO: Posix wants access to SHARED nodes of `part' after this point to raise SIGBUS */

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

		/* A blocks of `part' with status LOAD must be set to CHNG.
		 *
		 * Since  we changed the  part to be  anonymous, any block that
		 * is loaded into memory (and isn't all 0-es) no longer matches
		 * the default initializer  of `mfile_anon', which  initializes
		 * to all 0-es. As such, we have to mark such blocks as changed */
		if (MPART_ST_INCORE(part->mp_state) &&
		    ((part->mp_flags & MPART_F_BLKST_INL) || part->mp_blkst_ptr)) {
			size_t i, count = mpart_getblockcount(part, self);
			for (i = 0; i < count; ++i) {
				unsigned int st = mpart_getblockstate(part, i);
				if (st == MPART_BLOCK_ST_LOAD) {
					/* NOTE: Technically only required if the block's
					 *       backing physical memory  isn't all  0-es */
					mpart_setblockstate(part, i, MPART_BLOCK_ST_CHNG);
				}
			}
		}

		/* And with that, this part's been marked made anonymous! */
		mpart_lock_release(part);

		/* Release our reference by also trimming the part,  thus
		 * trying to remove any sub-range that's no longer mapped
		 * into memory. */
		mpart_trim(part);
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
