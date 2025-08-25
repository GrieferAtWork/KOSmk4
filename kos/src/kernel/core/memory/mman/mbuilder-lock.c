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
#ifndef GUARD_KERNEL_SRC_MEMORY_MBUILDER_LOCK_C
#define GUARD_KERNEL_SRC_MEMORY_MBUILDER_LOCK_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/path.h>
#include <kernel/mman/flags.h>
#include <kernel/mman/mbuilder.h>
#include <kernel/mman/mfile-map.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <misc/unlockinfo.h>

#include <hybrid/sequence/list.h>

#include <kos/except.h>
#include <kos/types.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Check if the [inner_min,inner_max] range is entirely contained in [outer_min,outer_max] */
#define RANGE_CONTAINS(outer_min, outer_max, inner_min, inner_max) \
	((inner_min) >= (outer_min) && (inner_max) <= (outer_max))

/* Acquire a lock to every unique mem-part mapped by `self'.
 * If this fails for at least  one of the parts, unlock  all
 * parts already locked  at that point,  invoke `unlock'  if
 * given, wait until  the blocking  part becomes  available,
 * and return `false'
 * Otherwise, return `true' */
PRIVATE NONNULL((1)) bool FCALL
mbuilder_lockparts_or_unlock(struct mbuilder_norpc *__restrict self,
                             struct unlockinfo *unlock) {
	size_t bucket;
	for (bucket = 0; bucket < MBNODE_PARTSET_NUMBUCKETS; ++bucket) {
		struct mbnode *iter;
		LIST_FOREACH (iter, &self->mb_uparts.mbps_set[bucket], mbn_nxtuprt) {
			struct mbnode *iter2;
			struct mpart *part = iter->mbn_part;
			if (mpart_lock_tryacquire(part))
				continue;

			/* We've got a blocking part... */
			for (bucket = 0;; ++bucket) {
				assert(bucket < MBNODE_PARTSET_NUMBUCKETS);
				for (iter2 = LIST_FIRST(&self->mb_uparts.mbps_set[bucket]);
				     iter2; iter2 = LIST_NEXT(iter2, mbn_nxtuprt)) {
					if (iter2 == iter)
						goto done_unlock_all;
					mpart_lock_release(iter2->mbn_part);
				}
			}
done_unlock_all:
			unlockinfo_xunlock(unlock);
			mpart_lock_waitfor(part);
			return false;
		}
	}
	return true;
}

/* Release locks to all of the mapped mem-parts, as should have previously
 * been   acquired   during  a   call   to  `mbuilder_partlocks_acquire()' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mbuilder_partlocks_release)(struct mbuilder_norpc *__restrict self) {
	size_t bucket;
	struct mbnode *node;
	for (bucket = 0; bucket < MBNODE_PARTSET_NUMBUCKETS; ++bucket) {
		LIST_FOREACH (node, &self->mb_uparts.mbps_set[bucket], mbn_nxtuprt) {
			mpart_lock_release(node->mbn_part);
		}
	}
}


/* Helper wrapper for `mbuilder_partlocks_acquire_or_unlock()' that
 * will  keep  on  attempting  the  operation  until  it  succeeds. */
PUBLIC BLOCKING NONNULL((1)) void FCALL
mbuilder_partlocks_acquire(struct mbuilder_norpc *__restrict self)
		THROWS(E_BADALLOC, E_WOULDBLOCK, ...) {
	while (!mbuilder_partlocks_acquire_or_unlock(self, NULL))
		;
}




struct mfile_map_for_reflow: mfile_map {
	/* @override(.mfm_file, [REF]) */
	uintptr_t           mfmfr_nodeflags; /* Finalized values for `mnode::mn_flags'. */
	uintptr_t           mfmfr_mapaddr;   /* Finalized mapping base-address. (to-be re-added to all nodes) */
	REF struct path    *mfmfr_fspath;    /* [0..1] Optional mapping path */
	REF struct fdirent *mfmfr_fsname;    /* [0..1] Optional mapping name */
};


PRIVATE NOBLOCK WUNUSED NONNULL((1, 2, 3)) struct mbnode *
NOTHROW(FCALL mbuilder_find_other_mbnode_mapping_mpart)(struct mbnode *__restrict root,
                                                        struct mbnode const *__restrict not_this,
                                                        struct mpart const *__restrict part) {
again:
	if (root != not_this && root->mbn_part == part)
		return root;
	if (root->mbn_mement.rb_lhs) {
		if (root->mbn_mement.rb_rhs) {
			struct mbnode *result;
			result = mbuilder_find_other_mbnode_mapping_mpart(root->mbn_mement.rb_rhs,
			                                                  not_this, part);
			if (result)
				return result;
		}
		root = root->mbn_mement.rb_lhs;
		goto again;
	}
	if (root->mbn_mement.rb_rhs) {
		root = root->mbn_mement.rb_rhs;
		goto again;
	}
	return NULL;
}

/* Convert a file-map-base node `*p_fmnode' into the associated `mfile_map',
 * as well as remove all nodes associated with the mapping from `self',  and
 * the file-map base-node from `*p_fmnode' */
PRIVATE NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL mbuilder_extract_filemap)(/*in|out*/ struct mbuilder_norpc *__restrict self,
                                        /*in|out:remove*/ struct mbnode **__restrict p_fmnode,
                                        /*out*/ struct mfile_map_for_reflow *__restrict fm) {
	struct mbnode *fmnode, *iter;
	fmnode = *p_fmnode;

	/* Remove from the file-mappings list. */
	SLIST_P_REMOVE(p_fmnode, mbn_nxtfile);

	/* Fill in fields of the file-map. */
	fm->mfm_file            = fmnode->mbn_file; /* Inherit reference. */
	fm->mfm_addr            = mnode_mbn_filpos_get(fmnode);
	/*->mfm_size            = ...;*/ /* Set below */
	fm->mfm_prot            = prot_from_mnodeflags(fmnode->mbn_flags);
	fm->mfm_flags           = mapflags_from_mbnodeflags(fmnode->mbn_flags);
	fm->mfm_nodes.slh_first = (struct mnode *)fmnode;
	fm->mfm_flist           = self->_mb_fnodes; /* Steal the free-list */
	fm->mfmfr_nodeflags     = fmnode->mbn_flags;
	fm->mfmfr_mapaddr       = (uintptr_t)fmnode->mbn_minaddr;
	fm->mfmfr_fspath        = fmnode->mbn_fspath;
	fm->mfmfr_fsname        = fmnode->mbn_fsname;
	DBG_memset(&self->_mb_fnodes, 0xcc, sizeof(self->_mb_fnodes));
	mpart_setcore_data_init(&fm->mfm_scdat);
	mpart_unsharecow_data_init(&fm->mfm_ucdat);

	for (iter = fmnode;;) {
		struct mbnode *next;
		mbnode_tree_removenode(&self->mb_mappings, iter);
		DBG_memset(&iter->mbn_mement, 0xcc, sizeof(iter->mbn_mement));
		iter->mbn_minaddr -= fm->mfmfr_mapaddr;
		iter->mbn_maxaddr -= fm->mfmfr_mapaddr;
		assert(iter->mbn_part);
		assert(mpart_lock_acquired(iter->mbn_part));

		/* NOTE: the logic here needs to handle a rather complicated case:
		 *
		 * Given a program with these PHDRs (is: /bin/busybox on x86_64)
		 *   LOAD           0x000000 0000000000400000 0000000000400000 0x0b03a0 0x0b03a0 R E 0x1000  (.text)
		 *   LOAD           0x0b03a0 00000000004b13a0 00000000004b13a0 0x000e6c 0x0027b8 RW  0x1000  (.data + .bss)
		 *
		 * Since the .data isn't page-aligned, but does have synced file/vaddr offsets,
		 * the  ELF  loader   will  extend   its  mapping  by   0x3a0  leading   bytes:
		 *   LOAD           0x0b0000 00000000004b1000 00000000004b1000 0x00120c 0x0027b8 RW  0x1000  (.data + .bss)
		 *
		 * This gets mapped as:
		 * - 0000000000400000-00000000004B0FFF r-xp: /bin/busybox+0000000000000000
		 * - 00000000004B1000-00000000004B1FFF rw-p: /bin/busybox+00000000000B0000 [leading "3A0" are redundant; maps 0x1000 of 0x120c .data from /bin/busybox+0xb0000]
		 * - 00000000004B2000-00000000004B2FFF rw-p: /bin/busybox+00000000000B1000 [Mapped using "mbnode_create_partialbss"; leading 0x20c are read /bin/busybox+0xb1000]
		 *
		 * In this configuration, "/bin/busybox+0xb0000-0xb0fff" is mapped twice:
		 * - 00000000004B0000-00000000004B0FFF r-xp
		 * - 00000000004B1000-00000000004B1FFF rw-p
		 *
		 * That is actually OK however, both mappings are "p" (PRIVATE)
		 *
		 * Now,  when  the 3rd  mapping  (00000000004B2000-00000000004B2FFF) is
		 * initialized,  this is done  by "mbnode_create_partialbss" which does
		 * a partial read from the actual file (iow: doesn't use lazy mapping),
		 * though  the same effect  could also be  achieved when another thread
		 * calls "cc(1)" or similar.
		 *
		 * The end result is that there is  a chance that the kernel will  try
		 * to merge the node for "/bin/busybox+00000000000B0000" with the node
		 * for its successor "/bin/busybox+00000000000B1000".
		 *
		 * That is also OK, but when it happens, then the kernel may also choose
		 * to anonymize the mpart (that will later become our  `iter->mbn_part')
		 * because it doesn't appear to be in-use.
		 *
		 * This, too, is OK, since that is where we come in: when the file
		 * mapping is re-locked, the non-continuous mnode that was deleted
		 * during the merge is detected by "mbnode_is_continuous", and  we
		 * get here, with it being our job to re-construct an (incomplete)
		 * "struct mfile_map_for_reflow" that can then be completed by our
		 * caller  by replacing the deleted (from the merge) part with its
		 * proper equivalent.
		 *
		 * However, recall what happened earlier: the mbuilder still contains
		 * 2 different mnodes referencing  the same (now-deleted) mpart  (the
		 * one that is currently in `iter->mbn_part'), but only one of them
		 * (specifically: "00000000004B0000-00000000004B0FFF") is considered
		 * to be the lock-owner.
		 *
		 * Yet, this representing a problem how:
		 * - mbuilder_reflow_filemap_or_unlock
		 * - mfile_map_reflow_or_unlock
		 * - mfile_map_unlock_and_remove_non_overlapping_parts
		 *
		 * This call chain will unlock the twice-mapped part both during the first pass,
		 * and  then try to do so again during  the second pass, leading to an assertion
		 * fault in "mfile_map_unlock_and_remove_non_overlapping_parts" when it tries to
		 * release a lock that was already released during the second pass.
		 *
		 * The  solution  here is  "mbuilder_find_other_mbnode_mapping_mpart", which
		 * checks  if the associated mpart might have another mapping, and transfers
		 * the responsibility of (re-)acquiring a lock to some other mbnode, in case
		 * mfile_map reflowing caused locks to be reloaded.
		 */

		/* Not needed! Nothing in `mfile_map_reflow_or_unlock()' every read this! */
		/*iter->_mbn_partoff = ...;*/

		/* Remove whatever node is mapping this one's part from list of
		 * nodes that map unique parts, since we have to gift `fm'  our
		 * lock to that part. */
		if likely(LIST_ISBOUND(iter, mbn_nxtuprt)) {
			/* If the builder contains another mbnode that references "iter->mbn_part",
			 * then that mbnode must be inserted into  the set at this point, so-as  to
			 * ensure that a lock to that part will be re-acquired in later passes! */
			struct mbnode *other_mapping_for_part;

			/* NOTE: This is an O(n) operation in a hot branch. Instead of always doing this,
			 *       have some sort of flag to indicate  that the linked mpart of the  mbnode
			 *       *may* be referenced by another mbnode within the mbuilder.
			 *
			 * Since  that flag wouldn't be hot, it could be used to speed up calls to
			 * mbuilder_find_other_mbnode_mapping_mpart by mirroring the behavior when
			 * said function returns NULL. */
			if (iter->mbn_flags & MBNODE_F_DUPLICATE) {
				other_mapping_for_part = mbuilder_find_other_mbnode_mapping_mpart(self->mb_mappings,
				                                                                  iter, iter->mbn_part);
				if (other_mapping_for_part)
					LIST_INSERT_BEFORE(iter, other_mapping_for_part, mbn_nxtuprt);
			} else {
				assertf((other_mapping_for_part = mbuilder_find_other_mbnode_mapping_mpart(self->mb_mappings,
				                                                                           iter, iter->mbn_part)) == NULL,
				        "There shouldn't be another mapping for this "
				        "part because `MBNODE_F_DUPLICATE' isn't set!");
			}
			LIST_REMOVE(iter, mbn_nxtuprt);
		}
		DBG_memset(&iter->mbn_nxtuprt, 0xcc, sizeof(iter->mbn_nxtuprt));

		if ((next = iter->mbn_filnxt) == NULL) {
			/* Remember the total size of the mapping. */
			fm->mfm_size = (size_t)(iter->mbn_maxaddr + 1);
			break;
		}

		/* NOTE: Skip decref on the initial part, because those
		 *       2  references  have  been  inherited  by  `fm' */
		xdecref_nokill(next->mbn_fspath);
		xdecref_nokill(next->mbn_fsname);
		iter = next;
	}
}

/* Undo everything done by `mbuilder_extract_filemap()' by re-inserting the
 * given `fm' into the mem-builder. */
PRIVATE NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL mbuilder_insert_filemap)(/*in|out*/ struct mbuilder_norpc *__restrict self,
                                       /*in|out:insert*/ struct mbnode **__restrict p_fmnode,
                                       /*in*/ struct mfile_map_for_reflow *__restrict fm) {
	struct mbnode *fmnode, *iter;
	fmnode = (struct mbnode *)SLIST_FIRST(&fm->mfm_nodes);

	/* Re-add `fmnode' into the `*p_fmnode' list. */
	SLIST_P_INSERT_BEFORE(p_fmnode, fmnode, mbn_nxtfile);

	/* Fill in fields shared by all nodes. */
	iter = fmnode;

	/* Fill in basic mapping information. */
	fmnode->mbn_file = fm->mfm_file; /* Inherit reference. */
	mnode_mbn_filpos_set(fmnode, fm->mfm_addr);

	self->_mb_fnodes = fm->mfm_flist; /* Steal the free-list */
	DBG_memset(&fm->mfm_flist, 0xcc, sizeof(fm->mfm_flist));
	mpart_setcore_data_fini(&fm->mfm_scdat);
	mpart_unsharecow_data_fini(&fm->mfm_ucdat);

	for (;;) {
		struct mbnode *next;

		/* If this part isn't already being used, insert it into
		 * the list of unique mem-parts used by our mem-builder. */
		LIST_ENTRY_UNBOUND_INIT(&iter->mbn_nxtuprt);

		/* Insert the node as the holder of the associated unique part.
		 *
		 * Because some singular mpart may be mapped multiple times, it
		 * is  always possible that the part is always contained in the
		 * set of parts referenced by the mbuilder. */
		iter->mbn_flags = fm->mfmfr_nodeflags;
		iter->mbn_minaddr += (uintptr_t)fm->mfmfr_mapaddr;
		iter->mbn_maxaddr += (uintptr_t)fm->mfmfr_mapaddr;
		iter->mbn_fspath = xincref(fm->mfmfr_fspath);
		iter->mbn_fsname = xincref(fm->mfmfr_fsname);

		/* Insert the node into our builder's mapping-tree */
		mbnode_tree_insert(&self->mb_mappings, iter);
		mbuilder_uparts_insert(self, iter);

		next = iter->mbn_filnxt;
		if (!next)
			break;
		DBG_memset(&next->mbn_nxtfile, 0xcc, sizeof(iter->mbn_nxtfile));
		DBG_memset(&next->mbn_file, 0xcc, sizeof(iter->mbn_file));
		DBG_memset(&next->mbn_filpos, 0xcc, sizeof(iter->mbn_filpos));
		iter = next;
	}
}


struct mb_unlock_all_parts_info: unlockinfo {
	struct mbuilder_norpc *mualpi_builder; /* [1..1] The builder on which we must invoke
	                                        *        `mbuilder_partlocks_release()' */
	struct unlockinfo     *mualpi_uunlock; /* [0..1] User-defined unlock-info callback.
	                                        *        Will also be invoked, if given. */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mb_unlock_all_parts_info_unlock)(struct unlockinfo *__restrict self) {
	struct mb_unlock_all_parts_info *me;
	me = (struct mb_unlock_all_parts_info *)self;
	mbuilder_partlocks_release(me->mualpi_builder);
	unlockinfo_xunlock(me->mualpi_uunlock);
}


/* Check if the mapping of parts bound to individual nodes apart of
 * the given `fmnode' mapping is  continuous (that is: the  address
 * ranges described by mapped  nodes are entirely contained  within
 * those ranges for which an attempt at mapping is made) */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL mbnode_is_continuous)(struct mbnode const *__restrict fmnode) {
	pos_t fm_base;   /* File-map-base */
	byte_t *mm_base; /* Memory-map-base */
	struct mbnode const *iter;
	mm_base = fmnode->mbn_minaddr;
	fm_base = mnode_mbn_filpos_get(fmnode);
	iter    = fmnode;
	do {
		pos_t iter_fm_minaddr, iter_fm_maxaddr;
		struct mpart *part;

		/* Calculate the effective file-map address range
		 * that's  supposed  to be  mapped by  this node. */
		iter_fm_minaddr = fm_base + (size_t)(iter->mbn_minaddr - mm_base);
		iter_fm_maxaddr = fm_base + (size_t)(iter->mbn_maxaddr - mm_base);

		/* Check if the requested address range is entirely contained
		 * by what  is being  provided  by the  associated  mem-part. */
		part = iter->mbn_part;
		if unlikely(!RANGE_CONTAINS(part->mp_minaddr, part->mp_maxaddr,
		                            iter_fm_minaddr, iter_fm_maxaddr)) {
			/* Found a hole in the mapping...
			 * That can happen when `part' was recently split, and
			 * must  be resolved by  re-flowing this file mapping. */
			return false;
		}
	} while ((iter = iter->mbn_filnxt) != NULL);
	return true;
}


/* Reflow a file mapping that starts with `*p_fmnode'  (i.e.
 * the given  `fmnode IN self->mb_files'),  such  that  file
 * parts are added/removed as necessary to form a  coherent,
 * and continuous mapping  of the  requested address  range.
 * If nothing needed to be done, or the reflow could be done
 * without needing to release any locks, return `true'.
 *
 * Otherwise, release all locks and return `false' */
PRIVATE BLOCKING NONNULL((1, 2)) bool FCALL
mbuilder_reflow_filemap_or_unlock(struct mbuilder_norpc *__restrict self,
                                  struct mbnode **__restrict p_fmnode,
                                  struct unlockinfo *unlock)
		THROWS(...) {
	bool ok;
	struct mfile_map_for_reflow fm;
	struct mbnode *fmnode = *p_fmnode;
	if (mbnode_is_continuous(fmnode)) {
		/* TODO: Must check whatever'll eventually end up being done by
		 *       `mfile_map_reflow_or_unlock()' when the `MAP_POPULATE'
		 *       (here: `fmnode->mbn_flags & MBNODE_F_POPULATE') flag
		 *       was set. */
		return true;
	}

	/* Incomplete mapping. - Make use of `mfile_map_reflow_or_unlock()'
	 * to (try to) re-flow the  mapping. For this purpose, convert  the
	 * mapping within the builder into a conventional `mfile_map' */
	mbuilder_extract_filemap(self, p_fmnode, &fm);
	TRY {
		struct mb_unlock_all_parts_info inner_unlock;
		/* the  unlock-callback of this  must invoke the `unlock'
		 * that we've  been given,  in addition  to also  calling
		 * `mbuilder_partlocks_release()'. Note  that the  couple
		 * of parts that we've let `fm' inherit will have already
		 * been unlocked by `mfile_map_reflow_or_unlock()' */
		inner_unlock.ui_unlock      = &mb_unlock_all_parts_info_unlock;
		inner_unlock.mualpi_builder = self;
		inner_unlock.mualpi_uunlock = unlock;
		/* Do the actual re-flow. */
		ok = mfile_map_reflow_or_unlock(&fm, &inner_unlock);
	} EXCEPT {
		mbuilder_insert_filemap(self, p_fmnode, &fm);
		RETHROW();
	}
	mbuilder_insert_filemap(self, p_fmnode, &fm);
	return ok;
}



/* Acquire  locks to all  of the parts being  mapped by `self', and
 * ensure that  all mappings  within `self'  are fully  continuous.
 * If  this cannot  be done  without blocking,  invoke `unlock' (if
 * given), try to make it so that a repeated call will (eventually)
 * succeed, and return `false'.
 * Otherwise (if all locks have been acquired, and all mappings are
 * continuous), return `true'.
 * NOTE: If this function returns with an exception, `unlock' will
 *       also be invoked. */
PUBLIC BLOCKING NONNULL((1)) bool FCALL
mbuilder_partlocks_acquire_or_unlock(struct mbuilder_norpc *__restrict self,
                                     struct unlockinfo *unlock)
		THROWS(E_BADALLOC, E_WOULDBLOCK, ...) {
	struct mbnode **p_fmnode;
	/* Step #1: Acquire locks to all mapped parts. */
	if (!mbuilder_lockparts_or_unlock(self, unlock))
		goto fail;

	/* Go over all file mappings and re-flow them if necessary. */
	p_fmnode = SLIST_PFIRST(&self->mb_files);
	while (*p_fmnode != NULL) {
		if (!mbuilder_reflow_filemap_or_unlock(self, p_fmnode, unlock))
			goto fail;
		p_fmnode = SLIST_PNEXT(*p_fmnode, mbn_nxtfile);
	}

	/* At this point, we know that all mappings are continuous,
	 * and  will stay that way (for the time being) since we're
	 * still  holding a lock to every unique part that is being
	 * mapped! */
	return true;
fail:
	return false;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MBUILDER_LOCK_C */
