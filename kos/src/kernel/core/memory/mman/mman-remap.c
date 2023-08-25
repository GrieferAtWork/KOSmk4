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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_REMAP_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_REMAP_C 1
#define __WANT_MPART__mp_nodlsts /* mpart_getnodlst_from_mnodeflags() */
#define __WANT_MNODE__mn_alloc
#define __WANT_MNODE__mn_dead
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/node.h>
#include <kernel/fs/path.h>
#include <kernel/mman.h>
#include <kernel/mman/flags.h>
#include <kernel/mman/mfile-map.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/module.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/remap.h>
#include <kernel/mman/sync.h>
#include <kernel/mman/unmapped.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>

#include <kos/except.h>
#include <kos/except/reason/illop.h>
#include <kos/except/reason/inval.h>

#include <assert.h>
#include <atomic.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */


#define RANGES_OVERLAP(r1_start, r1_end, r2_start, r2_end) \
	((r1_end) > (r2_start) && (r2_end) > (r1_start))
#define RANGES_OVERLAP_OR_TOUCH(r1_start, r1_end, r2_start, r2_end) \
	((r1_end) >= (r2_start) && (r2_end) >= (r1_start))



#ifndef __mnode_slist_defined
#define __mnode_slist_defined
SLIST_HEAD(mnode_slist, mnode);
#endif /* !__mnode_slist_defined */

/* Set of relevant flags kept during mremap operations. */
#define MREMAP_KEPT_MNODE_FLAGS \
	(MNODE_F_PMASK | MNODE_F_SHARED | MNODE_F_MLOCK)


/* Verify that the calling thread has access to `self' as per `prot_flags' */
PRIVATE NONNULL((1)) void KCALL
verify_mfile_access(struct mfile *__restrict self,
                    unsigned int prot_flags) {
	/* Problem:
	 *     Using mremap(2), user-space is able to circumvent hmi_minaddr/hmi_maxaddr
	 *     limits originally imposed during mmap(2):
	 *     >> fd file_with_limits;
	 *     >> void *p = mmap(NULL, PAGESIZE, MAP_SHARED, PROT_READ | PROT_WRITE, file_with_limits, 0);
	 *     >> p = mremap(p, 0, 100 * PAGESIZE, MREMAP_MAYMOVE);
	 *     Even if `file_with_limits' limited the mapable address range, mremap() is
	 *     able  to exceed those limits, since we have no way of checking what those
	 *     limits would have originally been...
	 * Solution:
	 *     Check  if it's an fnode, and if it is, verify that the calling thread has
	 *     access to said node as per the new mapping's protection flags. While this
	 *     doesn't handle special cases where drivers want to hand out extra  access
	 *     rights, it *does* prevent the case where an unprivileged process tries to
	 *     resize a physical memory mapping to get access to arbitrary physical mem.
	 */

	unsigned int access;
	struct fnode *file;
	if (self == &mfile_zero) {
		/* Fast-pass / special case:
		 * /dev/zero can always be re-sized, even if its mode-bits are wonky. */
		return;
	}
	if likely(!mfile_isnode(self))
		return;
	file   = mfile_asnode(self);
	access = R_OK;
#if 0 /* Wrong: this would also only require write-access! */
	if (prot_flags & PROT_EXEC)
		access |= X_OK;
#endif

	/* When the caller wants a write-shared mapping,
	 * assert write-access to  the underlying  file. */
	if ((prot_flags & (PROT_SHARED | PROT_WRITE)) ==
	    /*         */ (PROT_SHARED | PROT_WRITE))
		access |= W_OK;
	fnode_access(file, access);
}

/* Create a duplicate of a PROT_SHARED mapping. */
PRIVATE BLOCKING_IF(flags & MREMAP_POPULATE) NONNULL((1)) PAGEDIR_PAGEALIGNED void *KCALL
duplicate_shared_mapping(struct mman *__restrict self,
                         PAGEDIR_PAGEALIGNED void *old_address,
                         PAGEDIR_PAGEALIGNED size_t new_size,
                         unsigned int flags,
                         PAGEDIR_PAGEALIGNED void *new_address) {
	PAGEDIR_PAGEALIGNED void *result;
	struct mnode *node;
	REF struct mpart *part;
	REF struct path *node_fspath;
	REF struct fdirent *node_fsname;
	struct mfile_map_with_unlockinfo map;
	struct mnode_slist old_mappings;
	uintptr_t mnode_flags;
	size_t old_size;

	/* Set-up the constant, fixed fields of our file-map descriptor. */
	map.mmwu_map.mfm_size = new_size;
	map.ui_unlock         = &mfile_map_with_unlockinfo_unlock;

	/* Start by locking the give mman. */
again:
	mman_lock_acquire(self);

	/* Lookup the node at `old_address' */
	node = mman_mappings_locate(self, old_address);
	if unlikely(!node) {
err_unmapped_old_address:
		mman_lock_release(self);
		THROW(E_SEGFAULT_UNMAPPED, old_address,
		      E_SEGFAULT_CONTEXT_FAULT);
	}

	/* Make sure that `node' is a viable candidate for what we have in mind. */
	if unlikely(node == &FORMMAN(self, thismman_kernel_reservation))
		goto err_unmapped_old_address;
	if unlikely((part = node->mn_part) == NULL)
		goto err_unmapped_old_address;

	/* Load relevant node flags. */
	mnode_flags = node->mn_flags & MREMAP_KEPT_MNODE_FLAGS;
	if unlikely(!(mnode_flags & MNODE_F_SHARED)) {
		mman_lock_release(self);
err_not_shareable:
		THROW(E_INVALID_OPERATION,
		      E_ILLEGAL_OPERATION_CONTEXT_MREMAP_OLDSZ0_NOT_SHAREABLE);
	}

	/* Fill in our mfile mapping descriptor with information from `node' */
	old_size               = (size_t)((byte_t *)mnode_getendaddr(node) - (byte_t *)old_address);
	map.mmwu_map.mfm_addr  = mnode_getfileaddrat(node, old_address);
	map.mmwu_map.mfm_prot  = prot_from_mnodeflags(mnode_flags);
	map.mmwu_map.mfm_flags = mapflags_from_mnodeflags_usronly(mnode_flags) |
	                         mapflags_from_remapflags_poponly(flags);
	node_fspath            = xincref(node->mn_fspath);
	node_fsname            = xincref(node->mn_fsname);
	SLIST_INIT(&map.mmwu_map.mfm_flist);
	mman_lock_release(self);
	FINALLY_XDECREF_UNLIKELY(node_fspath);
	FINALLY_XDECREF_UNLIKELY(node_fsname);

	/* Lookup the file associated with the part we've found! */
	{
		FINALLY_DECREF_UNLIKELY(part);
		mpart_lock_acquire(part);
		/* Make sure that the mem-part isn't anonymous! */
		if unlikely(mpart_isanon(part)) {
			mpart_lock_release(part);
			goto err_not_shareable;
		}
		map.mmwu_map.mfm_file = incref(part->mp_file);
		mpart_lock_release(part);
	}
	FINALLY_DECREF_UNLIKELY(map.mmwu_map.mfm_file);

	/* If the duplicate mapping's size is greater than the original
	 * mapping's (iow: when the calling process wants to gain extra
	 * access to the underlying file), re-check access permissions. */
	if (map.mmwu_map.mfm_size > old_size)
		verify_mfile_access(map.mmwu_map.mfm_file, map.mmwu_map.mfm_prot);

	/* Initialize & lock the requested address range. */
	_mfile_map_init_and_acquire(&map.mmwu_map);

	TRY {
		/* Re-acquire a lock to our mman. */
		while unlikely(!mman_lock_tryacquire(self)) {
			mfile_map_release(&map.mmwu_map);
			mman_lock_waitfor(self);
again_lock_mman_phase2:
			mfile_map_acquire(&map.mmwu_map);
		}

		/* Re-check that the mapping from  `old_address'
		 * still exists as it did when we started above. */
		node = mman_mappings_locate(self, old_address);
		if unlikely(!node) {
something_changed:
			mman_lock_release(self);
			mfile_map_release(&map.mmwu_map);
			mfile_map_fini(&map.mmwu_map);
			goto again;
		}
		if unlikely(node == &FORMMAN(self, thismman_kernel_reservation))
			goto something_changed;
		if unlikely(node->mn_fspath != node_fspath)
			goto something_changed;
		if unlikely(node->mn_fsname != node_fsname)
			goto something_changed;
		if unlikely((part = node->mn_part) == NULL)
			goto something_changed;
		if unlikely(atomic_read(&part->mp_file) != map.mmwu_map.mfm_file)
			goto something_changed;
		if unlikely(map.mmwu_map.mfm_addr != mnode_getfileaddrat(node, old_address))
			goto something_changed;
		if unlikely(mnode_flags != (node->mn_flags & MREMAP_KEPT_MNODE_FLAGS))
			goto something_changed;

		/* Everything's still in order!
		 * In this case, move on ahead to figuring out where
		 * we should place  the to-be  returned mapping  at. */
		result = mman_getunmapped_or_unlock(/* self:                 */ self,
		                                    /* addr:                 */ new_address,
		                                    /* num_bytes:            */ map.mmwu_map.mfm_size,
		                                    /* flags:                */ mapflags_from_remapflags_fndonly(flags),
		                                    /* min_alignment:        */ PAGESIZE,
		                                    /* min_alignment_offset: */ 0,
		                                    /* unlock:               */ &map /* Unlock the file-map on error! */);

		/* Check for special case: lock was lost. */
		if unlikely(result == MAP_FAILED)
			goto again_lock_mman_phase2;

		/* Prepare the page directory of target address range for mapping stuff. */
		if (!pagedir_prepare_p(self->mm_pagedir_p, result, map.mmwu_map.mfm_size)) {
			/* Failed to prepare the backing page directory... :( */
			mfile_map_release(&map.mmwu_map);
			mman_lock_release(self);
			THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
		}

	} EXCEPT {
		mfile_map_fini(&map.mmwu_map);
		RETHROW();
	}
	/* === Point of no return === */

	/* Get rid of existing mappings. */
	SLIST_INIT(&old_mappings);
	for (;;) {
		struct mnode *removeme;
		removeme = mman_mappings_rremove(self,
		                                 (byte_t *)result,
		                                 (byte_t *)result + map.mmwu_map.mfm_size - 1);
		if likely(removeme == NULL)
			break;
		assert(removeme->mn_mman == self);
		if (LIST_ISBOUND(removeme, mn_writable))
			LIST_REMOVE(removeme, mn_writable);
		/* Keep track of how many nodes are mapping some given module. */
		if (removeme->mn_module)
			module_dec_nodecount(removeme->mn_module);
		atomic_or(&removeme->mn_flags, MNODE_F_UNMAPPED);
		DBG_memset(&removeme->mn_writable, 0xcc, sizeof(removeme->mn_writable));
		DBG_memset(&removeme->mn_module, 0xcc, sizeof(removeme->mn_module));
		SLIST_INSERT(&old_mappings, removeme, _mn_dead);
	}

	/* Do the actual work of injecting the new mem-nodes into the mman. */
	while (!SLIST_EMPTY(&map.mmwu_map.mfm_nodes)) {
		struct mnode *node;
		struct mpart *part;
		pagedir_prot_t map_prot;
		node = SLIST_FIRST(&map.mmwu_map.mfm_nodes);
		SLIST_REMOVE_HEAD(&map.mmwu_map.mfm_nodes, _mn_alloc);
		part           = node->mn_part;
		node->mn_flags = mnode_flags;
		node->mn_mman  = self;
		/* Insert the node into the share-list of the associated part. */
		assert(mnode_flags & MNODE_F_SHARED);
		LIST_INSERT_HEAD(&part->mp_share, node, mn_link);

		node->mn_fspath = xincref(node_fspath);
		node->mn_fsname = xincref(node_fsname);
		node->mn_module = NULL;
		node->mn_minaddr += (uintptr_t)result;
		node->mn_maxaddr += (uintptr_t)result;

		/* Set the MLOCK  flag for  the backing  mem-part when  MAP_LOCKED is  given.
		 * Note that in this case, `node->mn_flags' already contains `MNODE_F_MLOCK'! */
		if ((mnode_flags & MAP_LOCKED) && !(part->mp_flags & MPART_F_MLOCK_FROZEN))
			atomic_or(&part->mp_flags, MPART_F_MLOCK);

		/* Map the backing part (as far as that is possible) */
		map_prot = mpart_mmap_node_p(part, self->mm_pagedir_p,
		                             mnode_getaddr(node),
		                             mnode_getsize(node),
		                             node->mn_partoff,
		                             node);

		/* If the node was mapped with write-permissions enabled,
		 * then add it to the  list of writable nodes within  our
		 * memory manager. */
		LIST_ENTRY_UNBOUND_INIT(&node->mn_writable);
		if (map_prot & PAGEDIR_PROT_WRITE)
			LIST_INSERT_HEAD(&self->mm_writable, node, mn_writable);

		mman_mappings_insert_and_verify(self, node);
		node = mnode_merge_with_partlock(node);
		mpart_assert_integrity(node->mn_part);
		mpart_lock_release(node->mn_part);
	}

	/* Now that we're done remapping stuff, we can unprepare the target range. */
	pagedir_unprepare_p(self->mm_pagedir_p, result, map.mmwu_map.mfm_size);

	/* If some other mapping was there before, then we must invalidate
	 * the page directory  cache so-as to  prevent any stale  entries.
	 * This has to happen before we  unlock the mman, and destroy  the
	 * old mappings, though!
	 * NOTE: We don't do  this unconditionally though,  because this  isn't
	 *       one of the fastest operations since this one has to go through
	 *       all of the hoops of broadcasting an IPI to everyone else... */
	if (!SLIST_EMPTY(&old_mappings))
		mman_sync_p(self, result, map.mmwu_map.mfm_size);

	/* Release locks. */
	mman_lock_release(self);
	mfile_map_fini(&map.mmwu_map);

	/* Destroy unmapped, pre-existing nodes. */
	while (!SLIST_EMPTY(&old_mappings)) {
		struct mnode *oldnode;
		oldnode = SLIST_FIRST(&old_mappings);
		SLIST_REMOVE_HEAD(&old_mappings, _mn_dead);
		assert(oldnode->mn_flags & MNODE_F_UNMAPPED);
		mnode_destroy(oldnode);
	}
	return result;
}


struct mappinginfo {
	REF struct mfile         *mi_file;      /* [0..1] The file being mapped (or `NULL' for RESERVED mappings) */
	REF struct path          *mi_fspath;    /* [0..1] Filesystem path for this mapping */
	REF struct fdirent       *mi_fsname;    /* [0..1] Filesystem name for this mapping */
	PAGEDIR_PAGEALIGNED pos_t mi_fpos;      /* Starting offset into `mi_file' of the first mapped byte. */
	uintptr_t                 mi_nodeflags; /* Set of `MNODE_F_* & MREMAP_KEPT_MNODE_FLAGS' for node flags. */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mappinginfo_fini)(struct mappinginfo *__restrict self) {
	xdecref_unlikely(self->mi_fsname);
	xdecref_unlikely(self->mi_fspath);
	xdecref_unlikely(self->mi_file);
	DBG_memset(self, 0xcc, sizeof(*self));
}

/* Lookup information about  memory mappings within  the given address  range,
 * and make sure that exactly 1 mapping  exists in that location. If at  least
 * 1 byte of that range isn't covered by a mnode, throw `E_SEGFAULT_UNMAPPED'.
 * If  not all of the nodes from the given range span a singular type of file,
 * throw `E_SEGFAULT_NONCONTINUOUS' (with a pointer  set to the first byte  of
 * a  node that differs from the file found within the initial node at `addr')
 * @return: true:  Success
 * @return: false: Lock was lost (try again!) */
PRIVATE WUNUSED NONNULL((1, 2)) bool FCALL
get_mappinginfo_or_unlock(struct mman *__restrict self,
                          struct mappinginfo *__restrict result,
                          PAGEDIR_PAGEALIGNED byte_t *minaddr,
                          /*pgalign-minus-1*/ byte_t *maxaddr)
		THROWS(E_SEGFAULT_UNMAPPED,
		       E_SEGFAULT_NONCONTINUOUS) {
	struct mnode *node;
	struct mpart *part;
	node = mman_mappings_locate(self, minaddr);
	if unlikely(!node) {
/*err_unmapped_minaddr:*/
		mman_lock_release(self);
		THROW(E_SEGFAULT_UNMAPPED, minaddr,
		      E_SEGFAULT_CONTEXT_FAULT);
	}

	/* Figure out what kind of mapping we're dealing with! */
	result->mi_nodeflags = node->mn_flags & MREMAP_KEPT_MNODE_FLAGS;
	if ((part = node->mn_part) == NULL) {
		/* Simple case: reserved mapping. */
		result->mi_file   = 0;
		result->mi_fspath = 0;
		result->mi_fsname = 0;
		result->mi_fpos   = 0;
		return true;
	}

	/* Lock the part so we can extract the underlying file. */
	if (!mpart_lock_tryacquire(part)) {
		/* Spin until the lock becomes available and let our caller try again. */
		incref(part);
		mman_lock_release(self);
		FINALLY_DECREF_UNLIKELY(part);
		mpart_lock_waitfor(part);
		return false;
	}
	result->mi_file = incref(part->mp_file);
	mpart_lock_release(part);

	/* Extract remaining mapping information. */
	result->mi_fspath = xincref(node->mn_fspath);
	result->mi_fsname = xincref(node->mn_fsname);
	result->mi_fpos   = mnode_getfileaddrat(node, minaddr);

	/* Check if the entirety of the existing mapping is contained
	 * within the bounds of `node'. If some part of the range  is
	 * located outside of `node', then we must scan ahead to make
	 * sure that the mapping is continuous. */
	if (maxaddr > mnode_getmaxaddr(node)) {
		/* Must scan ahead! */
		do {
			byte_t *expected_minaddr;
			expected_minaddr = (byte_t *)mnode_getmaxaddr(node) + 1;
			/* Load the next node. */
			node = mnode_tree_nextnode(node);
			if unlikely(!node || mnode_getminaddr(node) != expected_minaddr) {
				/* The byte at `expected_minaddr' isn't mapped... */
				mman_lock_release(self);
				mappinginfo_fini(result);
				THROW(E_SEGFAULT_UNMAPPED, expected_minaddr,
				      E_SEGFAULT_CONTEXT_FAULT);
			}
			/* Check if the file mapped by `node' is what we're expecting. */
			if ((part = node->mn_part) == NULL) {
				if unlikely(result->mi_file != NULL) {
err_noncontinuous_mapping:
					mman_lock_release(self);
					mappinginfo_fini(result);
					THROW(E_SEGFAULT_NONCONTINUOUS,
					      expected_minaddr);
				}
			} else {
				if unlikely(atomic_read(&part->mp_file) != result->mi_file)
					goto err_noncontinuous_mapping;
#if 0 /* The following is implicitly check by `part->mp_file != result->mi_file',
       * since `part->mp_file' is a [1..1] field. */
				if unlikely(result->mi_file == NULL)
					goto err_noncontinuous_mapping;
#endif
				if unlikely(result->mi_nodeflags != (node->mn_flags & MREMAP_KEPT_MNODE_FLAGS))
					goto err_noncontinuous_mapping;
				if unlikely(result->mi_fspath != node->mn_fspath)
					goto err_noncontinuous_mapping;
				if unlikely(result->mi_fsname != node->mn_fsname)
					goto err_noncontinuous_mapping;
				if unlikely(result->mi_fpos != mnode_getfileaddrat(node, minaddr))
					goto err_noncontinuous_mapping;
			}
			/* Keep going until we've covered the entire range. */
		} while (maxaddr > mnode_getmaxaddr(node));
	}
	return true;
}




PRIVATE NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(KCALL insert_and_maybe_map_nodes)(struct mman *__restrict self,
                                          struct mfile_map *__restrict map,
                                          struct mappinginfo const *__restrict mapinfo,
                                          uintptr_t loadaddr, bool did_prepare) {
	while (!SLIST_EMPTY(&map->mfm_nodes)) {
		struct mnode *node;
		struct mpart *part;
		node = SLIST_FIRST(&map->mfm_nodes);
		SLIST_REMOVE_HEAD(&map->mfm_nodes, _mn_alloc);
		node->mn_flags  = mapinfo->mi_nodeflags;
		node->mn_mman   = self;
		node->mn_fspath = xincref(mapinfo->mi_fspath);
		node->mn_fsname = xincref(mapinfo->mi_fsname);
		node->mn_module = NULL;
		node->mn_minaddr += loadaddr;
		node->mn_maxaddr += loadaddr;
		LIST_ENTRY_UNBOUND_INIT(&node->mn_writable);
		mman_mappings_insert(self, node);

		/* Insert the node into the copy- or share-list of the associated part. */
		assert((node->mn_part == NULL) == mfile_map_isreserved(map));
		if ((part = node->mn_part) != NULL) {
			struct mnode_list *list;

			/* Add the new node to the part's appropriate node-list. */
			list = mpart_getnodlst_from_mnodeflags(part, mapinfo->mi_nodeflags);
			LIST_INSERT_HEAD(list, node, mn_link);

			/* Set the MLOCK  flag for  the backing  mem-part when  MAP_LOCKED is  given.
			 * Note that in this case, `node->mn_flags' already contains `MNODE_F_MLOCK'! */
			if ((mapinfo->mi_nodeflags & MAP_LOCKED) && !(part->mp_flags & MPART_F_MLOCK_FROZEN))
				atomic_or(&part->mp_flags, MPART_F_MLOCK);
			mnode_assert_integrity(node);

			if (did_prepare) {
				pagedir_prot_t map_prot;
				/* Map the backing part (as far as that is possible) */
				map_prot = mpart_mmap_node_p(part, self->mm_pagedir_p,
				                             mnode_getaddr(node),
				                             mnode_getsize(node),
				                             node->mn_partoff,
				                             node);

				/* If the node was mapped with write-permissions enabled,
				 * then add it to the  list of writable nodes within  our
				 * memory manager. */
				if (map_prot & PAGEDIR_PROT_WRITE)
					LIST_INSERT_HEAD(&self->mm_writable, node, mn_writable);
			}
			node = mnode_merge_with_partlock(node);
			mpart_assert_integrity(node->mn_part);
			mpart_lock_release(node->mn_part);
		} else {
			mnode_assert_integrity(node);
			mnode_merge(node);
		}
	}
}



PRIVATE BLOCKING_IF(flags & MREMAP_POPULATE) NONNULL((1)) PAGEDIR_PAGEALIGNED void *KCALL
resize_existing_mapping(struct mman *__restrict self,
                        PAGEDIR_PAGEALIGNED void *old_address,
                        PAGEDIR_PAGEALIGNED size_t old_size,
                        PAGEDIR_PAGEALIGNED size_t new_size,
                        unsigned int flags,
                        PAGEDIR_PAGEALIGNED void *new_address,
                        size_t orig_old_size,
                        size_t orig_new_size) {
	PAGEDIR_PAGEALIGNED void *result;
	byte_t *old_maxaddr;
	struct mappinginfo mapinfo;
	struct mnode_slist old_mappings;
	if unlikely(OVERFLOW_UADD((uintptr_t)old_address, old_size - 1,
	                          (uintptr_t *)&old_maxaddr)) {
/*err_bad_old_size:*/
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_MREMAP_OLD_SIZE,
		      orig_old_size);
	}
	SLIST_INIT(&old_mappings);
again_lock_mman:
	mman_lock_acquire(self);

	/* Scan nodes from `old_address...old_maxaddr' and check if they're
	 * all representing a continuous  mapping across the entire  range. */
	if (!get_mappinginfo_or_unlock(self, &mapinfo, (byte_t *)old_address, old_maxaddr))
		goto again_lock_mman;

	TRY {
		/* Simple case: Truncate a mapping (and possibly move it when `MREMAP_FIXED' is given) */
		if (old_size >= new_size) {
			byte_t *old_newmax;
			byte_t *result_maxaddr;
			struct mnode *node;
			struct mnode_slist movenodes;
			ptrdiff_t move_disp;
			unsigned int i;
			result = old_address;
			if (flags & MREMAP_FIXED)
				result = new_address;
			if unlikely(OVERFLOW_UADD((uintptr_t)result, new_size - 1,
			                          (uintptr_t *)&result_maxaddr)) {
				mman_lock_release(self);
				mappinginfo_fini(&mapinfo);
/*err_bad_new_size:*/
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_MREMAP_NEW_SIZE,
				      orig_new_size);
			}

			if ((flags & (MREMAP_FIXED | MREMAP_FIXED_NOREPLACE)) ==
			    /*    */ (MREMAP_FIXED | MREMAP_FIXED_NOREPLACE)) {
				/* Check if there's already a mapping here... */
				if unlikely((node = mman_mappings_rlocate(self, result, result_maxaddr)) != NULL) {
					void *node_minaddr, *node_maxaddr;
					node_minaddr = mnode_getminaddr(node);
					node_maxaddr = mnode_getmaxaddr(node);
					mman_lock_release(self);
					/*mappinginfo_fini(&mapinfo);*/ /* s.a. EXCEPT below! */
					THROW(E_BADALLOC_ADDRESS_ALREADY_EXISTS,
					      result, result_maxaddr,
					      node_minaddr, node_maxaddr);
				}
			} else {
				/* Make  sure that (if  they exist), mem-nodes have
				 * bounds at both `result' and `result_maxaddr + 1' */
				node = mman_mappings_locate(self, result);
				if (node && mnode_getminaddr(node) != result &&
				    !mnode_split_or_unlock(self, node, result, NULL)) {
fini_mapinfo_and_again_lock_mman:
					mappinginfo_fini(&mapinfo);
					goto again_lock_mman;
				}
				node = mman_mappings_locate(self, result_maxaddr);
				if (node && mnode_getmaxaddr(node) != result_maxaddr &&
				    !mnode_split_or_unlock(self, node, result_maxaddr + 1, NULL))
					goto fini_mapinfo_and_again_lock_mman;
			}

			/* If necessary, split  mem-nodes from `old_address'  so that  the
			 * mapped address range has proper bounds around its entire range. */
			node = mman_mappings_locate(self, old_address);
			assert(node);
			if (old_address != mnode_getminaddr(node) &&
			    !mnode_split_or_unlock(self, node, old_address, NULL))
				goto fini_mapinfo_and_again_lock_mman;
			node = mman_mappings_locate(self, old_maxaddr);
			assert(node);
			if (old_maxaddr != mnode_getmaxaddr(node) &&
			    !mnode_split_or_unlock(self, node, old_maxaddr + 1, NULL))
				goto fini_mapinfo_and_again_lock_mman;
			/* Also split the node at the end of the range being unmapped. */
			old_newmax = (byte_t *)old_address + new_size - 1;
			node       = mman_mappings_locate(self, old_newmax);
			assert(node);
			if (old_newmax != mnode_getmaxaddr(node) &&
			    !mnode_split_or_unlock(self, node, old_newmax + 1, NULL))
				goto fini_mapinfo_and_again_lock_mman;

			/* Make sure that both the old, as well as the new address
			 * range have been prepared. */
			if unlikely(!pagedir_prepare_p(self->mm_pagedir_p, old_address, old_size)) {
err_cannot_prepare:
				mnode_merge(mman_mappings_locate(self, old_address));
				mnode_merge(mman_mappings_locate(self, old_maxaddr));
				mnode_merge(mman_mappings_locate(self, old_newmax));
				mman_lock_release(self);
				/*mappinginfo_fini(&mapinfo);*/ /* s.a. EXCEPT below! */
				THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
			}
			if unlikely(!pagedir_prepare_p(self->mm_pagedir_p, result, new_size)) {
				pagedir_unprepare_p(self->mm_pagedir_p, old_address, old_size);
				goto err_cannot_prepare;
			}

			/* With all of  the mem-node splits  done, it's time  to
			 * shuffle around nodes the way our caller want's us to. */
			SLIST_INIT(&movenodes);
			move_disp = (byte_t *)result - (byte_t *)old_address;
			if (move_disp != 0) {
				while ((node = mman_mappings_rremove(self, old_address, old_newmax)) != NULL) {
					node->mn_minaddr += move_disp;
					node->mn_maxaddr += move_disp;
					if (LIST_ISBOUND(node, mn_writable))
						LIST_UNBIND(node, mn_writable);
					SLIST_INSERT(&movenodes, node, _mn_dead);
				}
			}

			/* Remove  nodes from the end of the  old mapping, as well as from
			 * the address range where the mapping in its entirety will go to. */
			i = 0;
			if (old_newmax == old_maxaddr)
				i = 1;
			for (; i < 2; ++i) {
				if (i == 0) {
					node = mman_mappings_rremove(self, old_newmax + 1, old_maxaddr);
				} else {
					if (move_disp == 0)
						break; /*  */
					node = mman_mappings_rremove(self, result, result_maxaddr);
				}
				if (!node)
					continue;
				mnode_pagedir_unmap_p(self->mm_pagedir_p, node);
				mnode_pagedir_sync_smp_p(self->mm_pagedir_p, node);
				assert(node->mn_mman == self);
				if (LIST_ISBOUND(node, mn_writable))
					LIST_REMOVE(node, mn_writable);
				/* Keep track of how many nodes are mapping some given module. */
				if (node->mn_module)
					module_dec_nodecount(node->mn_module);
				atomic_or(&node->mn_flags, MNODE_F_UNMAPPED);
				DBG_memset(&node->mn_writable, 0xcc, sizeof(node->mn_writable));
				DBG_memset(&node->mn_module, 0xcc, sizeof(node->mn_module));
				SLIST_INSERT(&old_mappings, node, _mn_dead);
			}

			/* Delete the pagedir mapping of the old mapping location. */
			pagedir_unmap_p(self->mm_pagedir_p, old_address, old_size);
			pagedir_sync_smp_p(self->mm_pagedir_p, old_address, old_size);

			/* Re-insert all of the (now displaced) nodes into the tree. */
			while (!SLIST_EMPTY(&movenodes)) {
				node = SLIST_FIRST(&movenodes);
				SLIST_REMOVE_HEAD(&movenodes, _mn_dead);
				mman_mappings_insert(self, node);
				if (node->mn_part != NULL && mpart_lock_tryacquire(node->mn_part)) {
					pagedir_prot_t map_prot;

					/* Map the backing part (as far as that is possible) */
					map_prot = mpart_mmap_node_p(node->mn_part,
					                             self->mm_pagedir_p,
					                             mnode_getaddr(node),
					                             mnode_getsize(node),
					                             node->mn_partoff,
					                             node);

					/* If the node was mapped with write-permissions enabled,
					 * then add it to the  list of writable nodes within  our
					 * memory manager. */
					if (map_prot & PAGEDIR_PROT_WRITE)
						LIST_INSERT_HEAD(&self->mm_writable, node, mn_writable);
					mnode_assert_integrity(node);
					node = mnode_merge_with_partlock(node);
					mpart_assert_integrity(node->mn_part);
					mpart_lock_release(node->mn_part);
				} else {
					mnode_assert_integrity(node);
					mnode_merge(node);
				}
			}

			/* Unprepare address ranges prepared above.
			 * NOTE: Make sure to deal with overlap between the 2 regions! */
			if (RANGES_OVERLAP_OR_TOUCH((byte_t *)old_address, old_maxaddr + 1,
			                            (byte_t *)result, result_maxaddr + 1)) {
				byte_t *range_minaddr, *range_endaddr;
				range_minaddr = (byte_t *)old_address;
				if (range_minaddr > (byte_t *)result)
					range_minaddr = (byte_t *)result;
				range_endaddr = result_maxaddr + 1;
				if (range_endaddr < old_maxaddr + 1)
					range_endaddr = old_maxaddr + 1;
				pagedir_unprepare_p(self->mm_pagedir_p, range_minaddr,
				                    (size_t)(range_endaddr - range_minaddr));
			} else {
				pagedir_unprepare_p(self->mm_pagedir_p, old_address, old_size);
				pagedir_unprepare_p(self->mm_pagedir_p, result, new_size);
			}
		} else {
			struct mfile_map_with_unlockinfo map;
			/* Complicated case: Extend the existing mapping to become larger.
			 * Start by constructing mnode/mpart pairs for all of the  missing
			 * parts. */
			map.mmwu_map.mfm_file  = mapinfo.mi_file;
			map.mmwu_map.mfm_addr  = mapinfo.mi_fpos + old_size;
			map.mmwu_map.mfm_size  = new_size - old_size;
			map.mmwu_map.mfm_prot  = prot_from_mnodeflags(mapinfo.mi_nodeflags);
			map.mmwu_map.mfm_flags = mapflags_from_mnodeflags_usronly(mapinfo.mi_nodeflags) |
			                         mapflags_from_remapflags_poponly(flags);
			SLIST_INIT(&map.mmwu_map.mfm_flist);
			mman_lock_release(self);

			/* If the duplicate mapping's size is greater than the original
			 * mapping's (iow: when the calling process wants to gain extra
			 * access to the underlying file), re-check access permissions. */
			if (map.mmwu_map.mfm_size > old_size)
				verify_mfile_access(map.mmwu_map.mfm_file, map.mmwu_map.mfm_prot);

			_mfile_map_init_and_acquire_or_reserved(&map.mmwu_map);
			TRY {
				/* Re-acquire a lock to the mman. */
				while (!mman_lock_tryacquire(self)) {
					mfile_map_release_or_reserved(&map.mmwu_map);
					mman_lock_waitfor(self);
again_lock_mman_phase2:
					mfile_map_acquire_or_reserved(&map.mmwu_map);
				}

				/* Re-check that the mapping from `old_address' still exists as it did when we started above. */
				{
					struct mappinginfo new_mapinfo;
					if (!get_mappinginfo_or_unlock(self, &new_mapinfo, (byte_t *)old_address, old_maxaddr))
						goto again_lock_mman_phase2;
					if unlikely(bcmp(&new_mapinfo, &mapinfo, sizeof(mapinfo)) != 0) {
						/* Mapping information changed (start over from scratch) */
						mfile_map_release_or_reserved(&map.mmwu_map);
						mman_lock_release(self);
						mfile_map_fini_or_reserved(&map.mmwu_map);
						mappinginfo_fini(&new_mapinfo);
						mappinginfo_fini(&mapinfo);
						goto again_lock_mman;
					}
					xdecref_nokill(new_mapinfo.mi_file);
					xdecref_nokill(new_mapinfo.mi_fspath);
					xdecref_nokill(new_mapinfo.mi_fsname);
				}

				/* Check if we can just inject the newly created file nodes
				 * at the end  of the  already-existing (partial)  mapping.
				 * iow: at `old_maxaddr+1...+=map.mmwu_map.mfm_size' */
				if (!(flags & MREMAP_FIXED) &&
				    mman_mappings_rlocate(self, old_maxaddr + 1,
				                          old_maxaddr + map.mmwu_map.mfm_size) == NULL) {
					/* Can just expand the existing mapping! */
					bool did_prepare;
					byte_t *addend_startaddr;
					addend_startaddr = old_maxaddr + 1;

					/* Try to prepare the new target address range (so we can map to it directly) */
					did_prepare = pagedir_prepare_p(self->mm_pagedir_p,
					                                addend_startaddr,
					                                map.mmwu_map.mfm_size);

					/* Do the actual work of injecting the new mem-nodes into the mman. */
					insert_and_maybe_map_nodes(self, &map.mmwu_map, &mapinfo,
					                           (uintptr_t)addend_startaddr,
					                           did_prepare);
					if (did_prepare) {
						pagedir_unprepare_p(self->mm_pagedir_p,
						                    addend_startaddr,
						                    map.mmwu_map.mfm_size);
					}

					result = old_address; /* Keep the same address */
				} else {
					struct mnode *node;
					ptrdiff_t move_disp;
					bool did_prepare;

					/* Must create a new mapping somewhere else,
					 * and move  everything  to  that  location. */
					map.ui_unlock = &mfile_map_with_unlockinfo_unlock_or_reserved;

					/* Find a suitable location for the mapping as a whole. */
					result = mman_getunmapped_or_unlock(/* self:                 */ self,
					                                    /* addr:                 */ new_address,
					                                    /* num_bytes:            */ new_size,
					                                    /* flags:                */ mapflags_from_remapflags_fndonly(flags),
					                                    /* min_alignment:        */ PAGESIZE,
					                                    /* min_alignment_offset: */ 0,
					                                    /* unlock:               */ &map /* Unlock the file-map on error! */);

					/* Check for special case: lock was lost. */
					if unlikely(result == MAP_FAILED)
						goto again_lock_mman_phase2;

					/* The address range being moved may not entirely overlap with
					 * proper mnode bounds. We already  know that its entirety  is
					 * mapped by nodes, but the lowest/greatest address may not be
					 * at the start/end of some mnode.
					 *
					 * Because  we need to move the mapping elsewhere, we have to
					 * make sure that mem-nodes are split at those two positions.
					 * Else, we'd be moving more memory than we're supposed to! */
					node = mman_mappings_locate(self, old_address);
					assert(node);
					if ((byte_t *)mnode_getminaddr(node) < (byte_t *)old_address) {
						if (!mnode_split_or_unlock(self, node, old_address, &map))
							goto again_lock_mman_phase2;
					}
					node = mman_mappings_locate(self, old_maxaddr);
					assert(node);
					if ((byte_t *)mnode_getmaxaddr(node) > (byte_t *)old_maxaddr) {
						if (!mnode_split_or_unlock(self, node, (byte_t *)old_maxaddr + 1, &map))
							goto again_lock_mman_phase2;
					}

					/* Prepare the pagedir to remove the old mapping, so we can unmap it. */
					if unlikely(!pagedir_prepare_p(self->mm_pagedir_p, old_address, old_size)) {
						mnode_merge(mman_mappings_locate(self, old_address));
						mnode_merge(mman_mappings_locate(self, old_maxaddr));
						mman_lock_release(self);
						mfile_map_release_or_reserved(&map.mmwu_map);
						/*mappinginfo_fini(&mapinfo);*/ /* s.a. EXCEPT below! */
						THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
					}

					/* Unmap the mapping from its old location. */
					pagedir_unmap_p(self->mm_pagedir_p, old_address, old_size);
					pagedir_sync_smp_p(self->mm_pagedir_p, old_address, old_size);
					pagedir_unprepare_p(self->mm_pagedir_p, old_address, old_size);

					/* Try to prepare the new target address range (so we can map to it directly) */
					did_prepare = pagedir_prepare_p(self->mm_pagedir_p, result, new_size);

					/* Move all of the nodes from `old_address...+=old_size' to `result...+=old_size' */
					assert(result != old_address);
					assert(!RANGES_OVERLAP((byte_t *)result, (byte_t *)result + old_size,
					                       (byte_t *)old_address, (byte_t *)old_address + old_size));
					move_disp = (byte_t *)result - (byte_t *)old_address;
					while ((node = mman_mappings_rremove(self, old_address, old_maxaddr)) != NULL) {
						assertf((byte_t *)mnode_getminaddr(node) >= (byte_t *)old_address &&
						        (byte_t *)mnode_getmaxaddr(node) <= (byte_t *)old_maxaddr,
						        "Node at %p-%p exceeds move bounds %p-%p\n"
						        "This should have been prevented by the `mnode_split_or_unlock()' above!",
						        (byte_t *)mnode_getminaddr(node),
						        (byte_t *)mnode_getmaxaddr(node),
						        (byte_t *)old_address, (byte_t *)old_maxaddr);

						node->mn_minaddr += move_disp;
						node->mn_maxaddr += move_disp;
						if (LIST_ISBOUND(node, mn_writable))
							LIST_UNBIND(node, mn_writable);
						mman_mappings_insert(self, node);
						if (node->mn_part != NULL && did_prepare &&
						    mpart_lock_tryacquire(node->mn_part)) {
							pagedir_prot_t map_prot;

							/* Map the backing part (as far as that is possible) */
							map_prot = mpart_mmap_node_p(node->mn_part,
							                             self->mm_pagedir_p,
							                             mnode_getaddr(node),
							                             mnode_getsize(node),
							                             node->mn_partoff,
							                             node);

							/* If the node was mapped with write-permissions enabled,
							 * then add it to the  list of writable nodes within  our
							 * memory manager. */
							if (map_prot & PAGEDIR_PROT_WRITE)
								LIST_INSERT_HEAD(&self->mm_writable, node, mn_writable);
							mnode_assert_integrity(node);
							node = mnode_merge_with_partlock(node);
							mpart_assert_integrity(node->mn_part);
							mpart_lock_release(node->mn_part);
						} else {
							mnode_assert_integrity(node);
							mnode_merge(node);
						}
					}

					/* Now inject all of the new mem-nodes we've just created. */
					insert_and_maybe_map_nodes(self, &map.mmwu_map, &mapinfo,
					                           (uintptr_t)((byte_t *)result + old_size),
					                           did_prepare);
					if (did_prepare)
						pagedir_unprepare_p(self->mm_pagedir_p, result, new_size);
				}
			} EXCEPT {
				mfile_map_fini_or_reserved(&map.mmwu_map);
				RETHROW();
			}
			mfile_map_fini_or_reserved(&map.mmwu_map);
		}
	} EXCEPT {
		mappinginfo_fini(&mapinfo);
		RETHROW();
	}

	/* Release locks and cleanup `mapinfo' */
	mman_lock_release(self);
	mappinginfo_fini(&mapinfo);

	/* Destroy unmapped, pre-existing nodes. */
	while (!SLIST_EMPTY(&old_mappings)) {
		struct mnode *oldnode;
		oldnode = SLIST_FIRST(&old_mappings);
		SLIST_REMOVE_HEAD(&old_mappings, _mn_dead);
		assert(oldnode->mn_flags & MNODE_F_UNMAPPED);
		mnode_destroy(oldnode);
	}

	/* Return the new mapping-base-address. */
	return result;
}


/* Remap an existing mapping at `old_address'.
 *  - The given `new_address' (if `MREMAP_FIXED' was given)
 *    must  have the same  in-page offset as `old_address'.
 *    s.a.  `E_INVALID_ARGUMENT_CONTEXT_MREMAP_NEW_ADDRESS'
 *  - The  given `old_address' is  floor-aligned to whole pages.
 *    The resulting addend is added to `old_size' (if non-zero),
 *    `new_size', as well as the eventual `return' value.
 *  - the given `old_size' is ceil-aligned to whole pages.
 *  - the given `new_size' is ceil-aligned to whole pages.
 * This function operates in 1 of 2 ways:
 *
 * if (old_size == 0):
 *     requires:
 *       - The `MREMAP_MAYMOVE' flag _must_ be set
 *       - The mnode at `old_address' must point to a non-anonymous mpart,
 *         and have the `MNODE_F_SHARED' flag set.
 *     action:
 *       - Create   another  memory  mapping  with  the  same  protection
 *         and  share  characteristics as  that from  `old_address', such
 *         that `return...+=new_size' is mapped, `return != old_address',
 *         and the  in-file offset  at `old_address'  equals the  in-file
 *         offset at `return'. Use  `MREMAP_FIXED' and other flags  so-as
 *         to choose where to put the new mapping.
 *       - The existing mapping is kept in this case.
 * else:
 *     requires:
 *       - `old_address...+=old_size' must point to some kind of uninterrupted
 *         mapping of a singular file (such that in-file offsets for all bytes
 *         from the given range map linearly to virtual addresses).
 *     action:
 *       - When `new_size <= old_size', unmap trailing pages. For this purpose,
 *         all  pages touched by `old_address...+=new_size' will remain mapped.
 *         When `MREMAP_FIXED'  is given,  all of  the remaining  mappings  are
 *         moved  over  to `new_address...+=new_size',  and  `new_address' will
 *         be returned. Otherwise, `old_address' will be re-returned.
 *       - When `new_size > old_size', allocate more mnode/mpart pairs to fill
 *         in the missing portion of the file mapping.
 *         When `MREMAP_FIXED' is given, move the (now larger) file mapping to
 *         that address, removing the  old mapping from `old_address',  before
 *         returning the mapping at `new_address'
 *         Otherwise,  check if the  missing portion can  simply be mapped above
 *         the existing mapping (`old_address+old_size...+=(new_size-old_size)')
 *         If it can, put it at that position. Otherwise, use `MREMAP_FIXED' and
 *         other flags to choose where to put the new mapping.
 *
 * @param: self:        The relevant memory manager.
 * @param: old_address: Address of the already-existing mapping.
 * @param: old_size:    The size of the already-existing mapping (at `old_address')
 *                      Set  to  zero  for  duplication  of  PROT_SHARED  mappings.
 * @param: new_size:    The size of the to-be returned mapping.
 * @param: flags:       Set of `MREMAP_MAYMOVE | MREMAP_FIXED | MREMAP_32BIT | MREMAP_GROWSDOWN  |
 *                      MREMAP_GROWSUP | MREMAP_STACK | MREMAP_POPULATE | MREMAP_FIXED_NOREPLACE |
 *                      MREMAP_NOASLR'
 * @param: new_address: When `MREMAP_FIXED' is given: the new address of the mapping.
 * @throws: E_SEGFAULT_UNMAPPED: No mapping (or a kernel-mapping) at `old_address'
 * @throws: *:E_INVALID_ARGUMENT_CONTEXT_MREMAP_NEW_SIZE:             `new_size == 0'
 * @throws: *:E_INVALID_ARGUMENT_CONTEXT_MREMAP_FIXED_NO_MAYMOVE:     `MREMAP_FIXED' w/o `MREMAP_MAYMOVE'
 * @throws: *:E_INVALID_ARGUMENT_CONTEXT_MREMAP_NEW_ADDRESS:          `new_address & PAGEMASK != old_address & PAGEMASK'
 * @throws: *:E_INVALID_ARGUMENT_CONTEXT_MREMAP_OLDSZ0_NO_MAYMOVE:    `old_size == 0 && !MREMAP_MAYMOVE'
 * @throws: *:E_INVALID_ARGUMENT_CONTEXT_MREMAP_OLDSZ0_NOT_SHAREABLE: Mapping at `old_address' isn't `PROT_SHARED' */
PUBLIC BLOCKING_IF(flags & MREMAP_POPULATE) NONNULL((1)) void *KCALL
mman_remap(struct mman *__restrict self, UNCHECKED void *old_address,
           size_t old_size, size_t new_size, unsigned int flags,
           UNCHECKED void *new_address)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_INVALID_ARGUMENT, ...) {
	void *result;
	uintptr_t addend;
	size_t used_old_size = old_size;
	size_t used_new_size = new_size;

	/* The `new_size' argument mustn't be `0' */
	if unlikely(used_new_size == 0) {
err_bad_new_size:
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_MREMAP_NEW_SIZE,
		      new_size);
	}

	/* Account for in-page offsets.
	 * Note that such offsets are treated by re-mapping whole containing pages. */
	addend = (uintptr_t)old_address & PAGEMASK;
	if unlikely(addend != 0) {
		if (used_old_size != 0) {
			if unlikely(OVERFLOW_UADD(used_old_size, addend, &used_old_size)) {
err_bad_old_size:
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_MREMAP_OLD_SIZE,
				      old_size);
			}
		}
		if unlikely(OVERFLOW_UADD(used_new_size, addend, &used_new_size))
			goto err_bad_new_size;
		old_address = (byte_t *)old_address - addend;
	}

	/* Ceil-align memory block sizes. */
	if unlikely(OVERFLOW_UADD(used_old_size, PAGEMASK, &used_old_size))
		goto err_bad_old_size;
	used_old_size &= ~PAGEMASK;
	if (OVERFLOW_UADD(used_new_size, PAGEMASK, &used_new_size))
		goto err_bad_new_size;
	used_new_size &= ~PAGEMASK;

	/* When remapping to a fixed address, that address must have
	 * the  same  in-page  alignment  as  the  original address. */
	if (flags & MREMAP_FIXED) {
		if unlikely(!(flags & MREMAP_MAYMOVE)) {
			THROW(E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION,
			      E_INVALID_ARGUMENT_CONTEXT_MREMAP_FIXED_NO_MAYMOVE,
			      flags, MREMAP_FIXED | MREMAP_MAYMOVE, MREMAP_FIXED);
		}
		if unlikely(((uintptr_t)new_address & PAGEMASK) != addend) {
			THROW(E_INVALID_ARGUMENT_BAD_ALIGNMENT,
			      E_INVALID_ARGUMENT_CONTEXT_MREMAP_NEW_ADDRESS,
			      (uintptr_t)new_address, PAGEMASK, addend);
		}
		new_address = (byte_t *)new_address - addend;
	}

	if (used_old_size == 0) {
		/* Special case: Create another mapping of a PROT_SHARED-mapping
		 * that can be found at `old_address', such that `return' points
		 * at another mapping of the same by as `old_address' does right
		 * now! */
		if unlikely(!(flags & MREMAP_MAYMOVE)) {
			/* The `MREMAP_MAYMOVE' flag _must_ be specified for zero-sized remap! */
			THROW(E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION,
			      E_INVALID_ARGUMENT_CONTEXT_MREMAP_OLDSZ0_NO_MAYMOVE,
			      flags, MREMAP_MAYMOVE);
		}
		/* Actually create the duplicate mapping. */
		result = duplicate_shared_mapping(self, old_address,
		                                  used_new_size, flags,
		                                  new_address);
	} else {
		/* Resize an existing mapping. */
		result = resize_existing_mapping(self, old_address, used_old_size,
		                                 used_new_size, flags, new_address,
		                                 old_size, new_size);
	}
	return (byte_t *)result + addend;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_REMAP_C */
