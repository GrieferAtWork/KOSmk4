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
#ifndef GUARD_KERNEL_SRC_MEMORY_MBUILDER_LOCK_C
#define GUARD_KERNEL_SRC_MEMORY_MBUILDER_LOCK_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/path.h>
#include <kernel/malloc.h>
#include <kernel/mman/flags.h>
#include <kernel/mman/mbuilder.h>
#include <kernel/mman/mfile-map.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <misc/unlockinfo.h>
#include <sched/task.h>

#include <kos/except.h>

#include <assert.h>
#include <stdbool.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
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




/* Check if `part' is already referenced by `self' */
#define mbuilder_uparts_contains(self, part) \
	(mbuilder_find_node_for_mpart(self, part) != NULL)

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mbuilder_uparts_insert)(struct mbuilder_norpc *__restrict self,
                                      struct mbnode *__restrict node) {
	struct mbnode_list *list;
	list = mbnode_partset_listof(&self->mb_uparts, node->mbn_part);
	LIST_INSERT_HEAD(list, node, mbn_nxtuprt);
}

/* Find the mb-node currently registered as part of the `mb_uparts'
 * set, as  the owner  of the  lock that  is being  held on  `part' */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1, 2)) struct mbnode *
NOTHROW(FCALL mbuilder_find_node_for_mpart)(struct mbuilder_norpc const *__restrict self,
                                            struct mpart const *__restrict part) {
	struct mbnode *iter;
	LIST_FOREACH (iter, mbnode_partset_listof(&self->mb_uparts, part), mbn_nxtuprt) {
		if (iter->mbn_part == part)
			break; /* Found it! */
	}
	return iter;
}



struct mfile_map_for_reflow: mfile_map {
	/* @override(.mfm_file, [REF]) */
	uintptr_t           mfmfr_nodeflags; /* Finalized values for `mnode::mn_flags'. */
	uintptr_t           mfmfr_mapaddr;   /* Finalized mapping base-address. (to-be re-added to all nodes) */
	REF struct path    *mfmfr_fspath;    /* [0..1] Optional mapping path */
	REF struct fdirent *mfmfr_fsname;    /* [0..1] Optional mapping name */
};



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

		/* Not needed! Nothing in `mfile_map_reflow_or_unlock()' every read this! */
		/*iter->_mbn_partoff = ...;*/

		/* Remove whatever node is mapping this one's part from list of
		 * node that map unqiue parts, since  we have to gift `fm'  our
		 * lock to that part. */
		if likely(LIST_ISBOUND(iter, mbn_nxtuprt)) {
			/* Simple case: Our node is the only (or currently registered)
			 *              mapping of the associated part. */
			LIST_REMOVE(iter, mbn_nxtuprt);
		} else {
			struct mbnode *owner_node;
			/* Slightly difficult case: Must find+remove the actual node
			 * that is registered as owner  of the lock associated  with
			 * the relevant mem-part. */
			owner_node = mbuilder_find_node_for_mpart(self, iter->mbn_part);
			assertf(owner_node != NULL,
			        "Internal error: No-one is holding known unique part %p",
			        iter->mbn_part);
			/* NOTE: Mark as unbound, since `owner_node' isn't part of our
			 *       current file mapping! */
			LIST_UNBIND(owner_node, mbn_nxtuprt);
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
                                       /*in*/ struct mfile_map_for_reflow *__restrict fm,
                                       bool success) {
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

		/* Insert  the node as the holder of the associated unique part.
		 * Note that upon  success (i.e.  `mfile_map_reflow_or_unlock()'
		 * didn't  return `false'),  we may  assume that  the reflow was
		 * successful, which also  means that we've  inherited locks  to
		 * to all of the parts, which also means that all of those locks
		 * are  unique,  since `mfile_map_reflow_or_unlock()'  will have
		 * ensured that all locks are exclusive.
		 *
		 * Upon  failure, it is  possible that one of  the parts we've been
		 * given by `mfile_map_reflow_or_unlock()' already exists somewhere
		 * else within our  node-tree, meaning if  that has happened,  then
		 * we must manually check if the part is actually unique! */
#ifdef NDEBUG
		if likely(success || !mbuilder_uparts_contains(self, iter->mbn_part))
#else /* NDEBUG */
		if (success) {
			assert(!mbuilder_uparts_contains(self, iter->mbn_part));
			mbuilder_uparts_insert(self, iter);
		} else if (!mbuilder_uparts_contains(self, iter->mbn_part))
#endif /* !NDEBUG */
		{
			mbuilder_uparts_insert(self, iter);
		}
		iter->mbn_flags = fm->mfmfr_nodeflags;
		iter->mbn_minaddr += (uintptr_t)fm->mfmfr_mapaddr;
		iter->mbn_maxaddr += (uintptr_t)fm->mfmfr_mapaddr;
		iter->mbn_fspath = xincref(fm->mfmfr_fspath);
		iter->mbn_fsname = xincref(fm->mfmfr_fsname);

		/* Insert the node into our builder's mapping-tree */
		mbnode_tree_insert(&self->mb_mappings, iter);

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
		mbuilder_insert_filemap(self, p_fmnode, &fm, false);
		RETHROW();
	}
	mbuilder_insert_filemap(self, p_fmnode, &fm, ok);
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
