/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_SPLIT_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_SPLIT_C 1
#define __WANT_MPART__mp_nodlsts
#define __WANT_MNODE__mn_alloc
#define __WANT_MFUTEX__mfu_dead
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
#include <kernel/panic.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/minmax.h>

#include <kos/except.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#define KMALLOC_TRY_TRUNCATE_LOCKED_ATOMIC_NX(ptr, num_bytes, gfp)         \
	do {                                                                   \
		typeof(*(ptr)) *_new_ptr;                                          \
		_new_ptr = (typeof(*(ptr)) *)krealloc_nx(ptr, num_bytes,           \
		                                         GFP_ATOMIC | GFP_LOCKED | \
		                                         GFP_PREFLT | (gfp));      \
		if likely(_new_ptr != NULL)                                        \
			(ptr) = _new_ptr;                                              \
	}	__WHILE0

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

#define vector_getblockstatus(vector, i)                            \
	(((vector)[(i) / MPART_BLKST_BLOCKS_PER_WORD] >>                \
	  (((i) % MPART_BLKST_BLOCKS_PER_WORD) * MPART_BLOCK_STBITS)) & \
	 (((unsigned int)1 << MPART_BLOCK_STBITS) - 1))
#define zvector_setblockstatus(vector, i, val)      \
	((vector)[(i) / MPART_BLKST_BLOCKS_PER_WORD] |= \
	 ((mpart_blkst_word_t)(val) << (((i) % MPART_BLKST_BLOCKS_PER_WORD) * MPART_BLOCK_STBITS)))




/* (manually) check if one the blocks of the given
 * mem-part  was marked as having changed, without
 * looking at the part's CHANGED flag. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL mpart_really_changed)(struct mpart const *__restrict self) {
	size_t i, count;
	if unlikely(!mpart_hasblockstate(self)) {
		/* Special case: Without a block-status bitset, all
		 *               blocks  are  implicitly   changed. */
		return true;
	}
	count = mpart_getblockcount(self, self->mp_file);
	for (i = 0; i < count; ++i) {
		unsigned int st;
		st = mpart_getblockstate(self, i);
		if (st == MPART_BLOCK_ST_CHNG)
			return true;
	}
	return false;
}





/* Try to incref the mman of `self' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL tryincref_mman_of_mnode)(struct mnode *__restrict self) {
	struct mman *mm = self->mn_mman;
	COMPILER_UNUSED(tryincref(mm));
}



/* Try to decref the mman of `self' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL trydecref_mman_of_mnode)(struct mnode *__restrict self) {
	struct mman *mm = self->mn_mman;
	if (!wasdestroyed(mm))
		decref_unlikely(mm);
}



/* Increment the reference counter of every (not already-destroyed)
 * mman that can be reached via the `mp_copy' and `mp_share' chains
 * of `self'. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_foreach_mmans_incref)(struct mpart *__restrict self) {
	unsigned int i;
	for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
		struct mnode *node;
		LIST_FOREACH (node, &self->_mp_nodlsts[i], mn_link)
			tryincref_mman_of_mnode(node);
	}
}



/* Do the reverse of `mpart_foreach_mmans_incref()' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_foreach_mmans_decref)(struct mpart *__restrict self) {
	unsigned int i;
	for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
		struct mnode *node;
		LIST_FOREACH (node, &self->_mp_nodlsts[i], mn_link)
			trydecref_mman_of_mnode(node);
	}
}



/* Check if the given mnode_list contains nodes that have the MLOCK flag set. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL mnode_list_contains_mlocked_nodes)(struct mnode_list const *__restrict self) {
	struct mnode const *node;
	LIST_FOREACH (node, self, mn_link) {
		if (node->mn_flags & MNODE_F_MLOCK)
			return true;
	}
	return false;
}



/* Check if `start_node...| stop_node' contains `mm' */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1, 2)) bool
NOTHROW(FCALL mnode_list_contains_mman)(struct mnode const *__restrict start_node,
                                        struct mman const *__restrict mm,
                                        struct mnode const *stop_node DFL(NULL)) {
	while (start_node != stop_node) {
		if (start_node->mn_mman == mm)
			return true;
		start_node = LIST_NEXT(start_node, mn_link);
	}
	return false;
}



/* Try to acquire a lock to every (unique and not destroyed)
 * mman that can be found apart of the copy- and share-lists
 * of `self'.
 *
 * The caller  must ensure  that they  are holding  references
 * to all of those mmans (s.a. `mpart_foreach_mmans_incref()')
 *
 * @return: * : When non-NULL, a pointer to an mman who's lock
 *              could  not be acquired immediately (the caller
 *              should unlock everything  else and wait  until
 *              the lock of that mman becomes available) */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) struct mman *
NOTHROW(FCALL mpart_lock_all_mmans)(struct mpart *__restrict self) {
	struct mnode *node;
	struct mman *mm;
	LIST_FOREACH (node, &self->mp_copy, mn_link) {
		mm = node->mn_mman;
		if unlikely(wasdestroyed(mm))
			continue;
		if (mnode_list_contains_mman(LIST_FIRST(&self->mp_copy), mm, node))
			continue; /* Already enumerated. */
		if (!mman_lock_tryacquire(mm)) {
			struct mman *blocking_mm = mm;
			/* Cannot be locked immediately. */
			while (node != LIST_FIRST(&self->mp_copy)) {
				node = LIST_PREV_UNSAFE(node, mn_link);
				mm   = node->mn_mman;
				if unlikely(wasdestroyed(mm))
					continue;
				if (mnode_list_contains_mman(LIST_FIRST(&self->mp_copy), mm, node))
					continue; /* Will be enumerated later. */
				mman_lock_release(mm);
			}
			return blocking_mm;
		}
	}
	LIST_FOREACH (node, &self->mp_share, mn_link) {
		mm = node->mn_mman;
		if unlikely(wasdestroyed(mm))
			continue;
		if (mnode_list_contains_mman(LIST_FIRST(&self->mp_copy), mm))
			continue; /* Already enumerated. */
		if (mnode_list_contains_mman(LIST_FIRST(&self->mp_share), mm, node))
			continue; /* Already enumerated. */
		if (!mman_lock_tryacquire(mm)) {
			/* Cannot be locked immediately. */
			struct mman *blocking_mm = mm;
			/* Unlock all share-nodes (that have already been locked). */
			while (node != LIST_FIRST(&self->mp_share)) {
				node = LIST_PREV_UNSAFE(node, mn_link);
				mm   = node->mn_mman;
				if unlikely(wasdestroyed(mm))
					continue;
				if (mnode_list_contains_mman(LIST_FIRST(&self->mp_copy), mm))
					continue; /* Will be enumerated later. */
				if (mnode_list_contains_mman(LIST_FIRST(&self->mp_share), mm, node))
					continue; /* Will be enumerated later. */
				mman_lock_release(mm);
			}
			/* Unlock all copy-on-write nodes. */
			LIST_FOREACH (node, &self->mp_copy, mn_link) {
				mm = node->mn_mman;
				if unlikely(wasdestroyed(mm))
					continue;
				if (mnode_list_contains_mman(LIST_FIRST(&self->mp_copy), mm, node))
					continue; /* Already enumerated. */
				mman_lock_release(mm);
			}
			return blocking_mm;
		}
	}
	return NULL;
}


#ifndef NDEBUG
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_assert_all_mmans_locked)(struct mpart *__restrict self) {
	unsigned int i;
	for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
		struct mnode *node;
		LIST_FOREACH (node, &self->_mp_nodlsts[i], mn_link) {
			struct mman *mm;
			mm = node->mn_mman;
			if unlikely(wasdestroyed(mm))
				continue;
			assertf(mman_lock_acquired(mm),
			        "No lock held for mman %p",
			        mm);
		}
	}
}
#else /* !NDEBUG */
#define mpart_assert_all_mmans_locked(self) (void)0
#endif /* NDEBUG */



/* Do the reverse of `mpart_lock_all_mmans()' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_unlock_all_mmans)(struct mpart *__restrict self) {
	struct mnode *node;
	struct mman *mm;
	mpart_assert_all_mmans_locked(self);
	LIST_FOREACH (node, &self->mp_share, mn_link) {
		mm = node->mn_mman;
		if unlikely(wasdestroyed(mm))
			continue;
		if (mnode_list_contains_mman(LIST_FIRST(&self->mp_copy), mm))
			continue; /* Will be enumerated later. */
		if (mnode_list_contains_mman(LIST_FIRST(&self->mp_share), mm, node))
			continue; /* Already enumerated. */
		mman_lock_release(mm);
	}
	LIST_FOREACH (node, &self->mp_copy, mn_link) {
		mm = node->mn_mman;
		if unlikely(wasdestroyed(mm))
			continue;
		if (mnode_list_contains_mman(LIST_FIRST(&self->mp_copy), mm, node))
			continue; /* Already enumerated. */
		mman_lock_release(mm);
	}
}

/* Unlock all the mmans of a given pair of mparts. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_unlock_all_mmans2)(struct mpart *__restrict lopart,
                                       struct mpart *__restrict hipart) {
	struct mnode *node;
	struct mman *mm;
	mpart_assert_all_mmans_locked(lopart);
	mpart_assert_all_mmans_locked(hipart);
	LIST_FOREACH (node, &lopart->mp_share, mn_link) {
		mm = node->mn_mman;
		if unlikely(wasdestroyed(mm))
			continue;
		if (mnode_list_contains_mman(LIST_FIRST(&hipart->mp_share), mm))
			continue; /* Will be enumerated later. */
		if (mnode_list_contains_mman(LIST_FIRST(&hipart->mp_copy), mm))
			continue; /* Will be enumerated later. */
		if (mnode_list_contains_mman(LIST_FIRST(&lopart->mp_copy), mm))
			continue; /* Will be enumerated later. */
		if (mnode_list_contains_mman(LIST_FIRST(&lopart->mp_share), mm, node))
			continue; /* Already enumerated. */
		mman_lock_release(mm);
	}
	LIST_FOREACH (node, &lopart->mp_copy, mn_link) {
		mm = node->mn_mman;
		if unlikely(wasdestroyed(mm))
			continue;
		if (mnode_list_contains_mman(LIST_FIRST(&hipart->mp_share), mm))
			continue; /* Will be enumerated later. */
		if (mnode_list_contains_mman(LIST_FIRST(&hipart->mp_copy), mm))
			continue; /* Will be enumerated later. */
		if (mnode_list_contains_mman(LIST_FIRST(&lopart->mp_copy), mm, node))
			continue; /* Already enumerated. */
		mman_lock_release(mm);
	}
	LIST_FOREACH (node, &hipart->mp_share, mn_link) {
		mm = node->mn_mman;
		if unlikely(wasdestroyed(mm))
			continue;
		if (mnode_list_contains_mman(LIST_FIRST(&hipart->mp_copy), mm))
			continue; /* Will be enumerated later. */
		if (mnode_list_contains_mman(LIST_FIRST(&hipart->mp_share), mm, node))
			continue; /* Already enumerated. */
		mman_lock_release(mm);
	}
	LIST_FOREACH (node, &hipart->mp_copy, mn_link) {
		mm = node->mn_mman;
		if unlikely(wasdestroyed(mm))
			continue;
		if (mnode_list_contains_mman(LIST_FIRST(&hipart->mp_copy), mm, node))
			continue; /* Already enumerated. */
		mman_lock_release(mm);
	}
}

/* Call  `mpart_lock_all_mmans()',  and upon  release  the following
 * locks before waiting on the blocking mman, and returning `false':
 *    - mpart_foreach_mmans_decref(self);
 *    - mpart_lock_release(self);
 * Otherwise, return `true' and don't release any locks. */
PRIVATE NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL mpart_lock_all_mmans_or_unlock_and_decref)(struct mpart *__restrict self) {
	struct mman *error;
	error = mpart_lock_all_mmans(self);
	if (error != NULL) {
		/* Blocking wait for `error' to become available. */
		incref(error);
		mpart_foreach_mmans_decref(self);
		mpart_lock_release(self);
		FINALLY_DECREF_UNLIKELY(error);
		mman_lock_waitfor(error);
		return false;
	}
	return true;
}

/* If present, acquire a lock  to `&self->mp_meta->mpm_ftxlock', and upon  release
 * the following locks before waiting on the blocking mman, and returning `false':
 *    - mpart_unlock_all_mmans(self);
 *    - mpart_foreach_mmans_decref(self);
 *    - mpart_lock_release(self);
 * Otherwise, return `true' and don't release any locks. */
PRIVATE NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL mpart_lock_meta_futex_or_unlock_and_decref)(struct mpart *__restrict self) {
	struct mpartmeta *meta = self->mp_meta;
	if (meta != NULL) {
		if (!mpartmeta_ftxlock_trywrite(meta)) {
			mpart_unlock_all_mmans(self);
			mpart_foreach_mmans_decref(self);
			mpart_lock_release(self);
			mpartmeta_ftxlock_waitwrite(meta);
			return false;
		}
	}
	return true;
}




/************************************************************************/
/* Helper structures/functions for splitting mem-parts                  */
/************************************************************************/
struct mpart_split_data {
	PAGEDIR_PAGEALIGNED mpart_reladdr_t msd_offset;   /* [const] The split-offset. */
	struct mpart                       *msd_lopart;   /* [1..1][const] The pre-existing lo-part. */
	struct mpart                       *msd_hipart;   /* [1..1][const][owned] The new mem-part to-be used for the copy. */
	struct mpartmeta                   *msd_himeta;   /* [0..1][owned] Meta-data controller for `msd_hipart'. */
	struct mnode_slist                  msd_hinodes;  /* [0..n][owned] Linked list (via `_mn_alloc') of mem-nodes for the hi-part. */
	size_t                              msd_hinodec;  /* # of nodes within the `msd_hinodes' list. */
	mpart_blkst_word_t                 *msd_hibitset; /* [0..1][owned] block-state bitset for the hi-part. */
	struct mchunk                      *msd_himvec;   /* [0..1][owned] Dynamically allocated vector of mem-chunks. */
};

PRIVATE NONNULL((1, 2)) void FCALL
mpart_split_data_init(struct mpart_split_data *__restrict self,
                      struct mpart *__restrict lopart) {
	self->msd_lopart = lopart;
	self->msd_hipart = (REF struct mpart *)kmalloc(sizeof(struct mpart),
	                                               GFP_LOCKED | GFP_PREFLT);
	self->msd_himeta = NULL;
	SLIST_INIT(&self->msd_hinodes);
	self->msd_hinodec  = 0;
	self->msd_hibitset = NULL;
	self->msd_himvec   = NULL;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_split_data_fini)(struct mpart_split_data *__restrict self) {
	kfree(self->msd_himvec);
	kfree(self->msd_hibitset);
	while (!SLIST_EMPTY(&self->msd_hinodes)) {
		struct mnode *node;
		node = SLIST_FIRST(&self->msd_hinodes);
		SLIST_REMOVE_HEAD(&self->msd_hinodes, _mn_alloc);
		kfree(node);
	}
	kfree(self->msd_himeta);
	kfree(self->msd_hipart);
}

/* Release all locks associated with `self' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL unlockall)(struct mpart *__restrict self) {
	if (self->mp_meta != NULL)
		mpartmeta_ftxlock_endwrite(self->mp_meta, self);
	mpart_unlock_all_mmans(self);
	mpart_foreach_mmans_decref(self);
	mpart_lock_release(self);
}



/* Count the # of mem-nodes needed to map the hi-part that is being created. */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) size_t
NOTHROW(FCALL mpart_count_needed_nodes_in_list)(struct mpart_split_data const *__restrict self,
                                                struct mnode_list const *__restrict list) {
	size_t result = 0;
	struct mnode *node;
	LIST_FOREACH (node, list, mn_link) {
		mpart_reladdr_t min, max;
		if unlikely(wasdestroyed(node->mn_mman))
			continue; /* Skip nodes that were destroyed. */
		if unlikely(node->mn_flags & MNODE_F_UNMAPPED)
			continue; /* Skip nodes that were unmapped. (NOTE: We're holding a lock to `node->mn_mman') */
		min = mnode_getpartminaddr(node);
		max = mnode_getpartmaxaddr(node);
		assert(min <= max);
		assert(max < mpart_getsize(self->msd_lopart));
		/* NOTE: We _only_ have to create new nodes for those cases where
		 *       the split position  lies _inside_ of  the range that  is
		 *       actually being mapped by some node!
		 * s.a. `mnode_getpartminaddr() ... mnode_getpartmaxaddr()' */
		if (min < self->msd_offset && self->msd_offset <= max)
			++result; /* This node has to be split in 2 */
	}
	return result;
}

PRIVATE NOBLOCK WUNUSED NONNULL((1)) size_t
NOTHROW(FCALL mpart_count_needed_nodes_for_hipart)(struct mpart_split_data const *__restrict self) {
	size_t result;
	result = mpart_count_needed_nodes_in_list(self, &self->msd_lopart->mp_copy);
	result += mpart_count_needed_nodes_in_list(self, &self->msd_lopart->mp_share);
	return result;
}


/* Count the # of blocks marked as `MPART_BLOCK_ST_CHNG' within the first `num_blocks' blocks. */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) size_t
NOTHROW(FCALL mpart_count_changed_blocks_before)(struct mpart const *__restrict self,
                                                 size_t num_blocks) {
	size_t i, result = 0;
	assert(num_blocks <= mpart_getblockcount(self, self->mp_file));
	for (i = 0; i < num_blocks; ++i) {
		unsigned int st;
		st = mpart_getblockstate(self, i);
		if (st == MPART_BLOCK_ST_CHNG)
			++result;
	}
	return result;
}

/* Return the (byte-)offset into swap memory where chunks should be split. */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) size_t
NOTHROW(FCALL mpart_get_swp_offset_after_split)(struct mpart const *__restrict self,
                                                PAGEDIR_PAGEALIGNED size_t partrel_offset) {
	size_t lo_blocks, changed_blocks, byte_offset;
	lo_blocks      = partrel_offset >> self->mp_file->mf_blockshift;
	changed_blocks = mpart_count_changed_blocks_before(self, lo_blocks);
	byte_offset    = changed_blocks << self->mp_file->mf_blockshift;
	return byte_offset;
}



/* Allocate  copies of nodes needed to describe
 * all of the new mappings following the split.
 *
 * If this cannot  be done without  blocking, release all  locks
 * (using `unlockall(self->msd_lopart)'), perform the allocation
 * while blocking, and return `false'.
 *
 * Otherwise (if no locks were released), return `true' */
PRIVATE NOBLOCK NONNULL((1)) bool FCALL
mpart_split_data_alloc_mnodes_or_unlock(struct mpart_split_data *__restrict self) {
	size_t needed;
	needed = mpart_count_needed_nodes_for_hipart(self);

	/* Hint that we usually only get here once, with everything set to NULL/0 */
	(void)__builtin_expect(self->msd_hinodec, 0);
	(void)__builtin_expect(SLIST_EMPTY(&self->msd_hinodes), 1);

	/* Keep on allocating nodes until we've got enough! */
	while (needed > self->msd_hinodec) {
		struct mnode *new_node;
		new_node = (struct mnode *)kmalloc_nx(sizeof(struct mnode),
		                                      GFP_ATOMIC | GFP_CALLOC |
		                                      GFP_LOCKED | GFP_PREFLT);
		if unlikely(!new_node) {
			/* Allocate the remainder without holding any
			 * locks,  and  while  blocking  is  allowed. */
			unlockall(self->msd_lopart);
			do {
				new_node = (struct mnode *)kmalloc(sizeof(struct mnode),
				                                   GFP_CALLOC | GFP_LOCKED |
				                                   GFP_PREFLT);
				SLIST_INSERT(&self->msd_hinodes, new_node, _mn_alloc);
				++self->msd_hinodec;
			} while (needed > self->msd_hinodec);
			return false;
		}
		SLIST_INSERT(&self->msd_hinodes, new_node, _mn_alloc);
		++self->msd_hinodec;
	}
	return true;
}



/* Allocate `self->msd_himeta' if necessary. */
PRIVATE NOBLOCK NONNULL((1)) bool FCALL
mpart_split_data_alloc_himeta_or_unlock(struct mpart_split_data *__restrict self) {
	struct mpartmeta *lometa;
	lometa = self->msd_lopart->mp_meta;
	if (lometa == NULL)
		goto done;

	/* Check if there are any allocated mfutex objects above the split-mark. */
	if (mpartmeta_ftx_rlocate(lometa,
	                          self->msd_offset,
	                          (mpart_reladdr_t)-1) == NULL)
		goto done;

	/* There are futex objects that (may) have to be redistributed.
	 * -> As such, we must allocate a secondary meta-data controller
	 *    for the high-part. */
	if likely(self->msd_himeta == NULL) {
		struct mpartmeta *himeta;
		himeta = (struct mpartmeta *)kmalloc_nx(sizeof(struct mpartmeta),
		                                        GFP_ATOMIC | GFP_CALLOC);
		if unlikely(!himeta) {
			/* Must allocate while blocking. */
			unlockall(self->msd_lopart);
			himeta = (struct mpartmeta *)kmalloc(sizeof(struct mpartmeta),
			                                     GFP_CALLOC);
			mpartmeta_cinit(himeta);
			self->msd_himeta = himeta;
			return false;
		}
		mpartmeta_cinit(himeta);
		self->msd_himeta = himeta;
	}
done:
	return true;
}



/* Allocate `self->msd_hibitset' if necessary. */
PRIVATE NOBLOCK NONNULL((1)) bool FCALL
mpart_split_data_alloc_hibitset_or_unlock(struct mpart_split_data *__restrict self) {
	size_t hi_num_bytes, hi_block_count;
	struct mpart *lopart = self->msd_lopart;

	/* Dynamically allocate block-status bitset in hipart */
	if (lopart->mp_flags & MPART_F_BLKST_INL)
		goto done;
	if (lopart->mp_blkst_ptr == NULL)
		goto done;
	hi_num_bytes   = mpart_getsize(lopart) - self->msd_offset;
	hi_block_count = hi_num_bytes >> lopart->mp_file->mf_blockshift;
	assert(hi_block_count != 0);
	if (hi_block_count > MPART_BLKST_BLOCKS_PER_WORD) {
		size_t reqsize;
		mpart_blkst_word_t *hi_bitset;
		reqsize = CEILDIV(hi_block_count, MPART_BLKST_BLOCKS_PER_WORD) * sizeof(mpart_blkst_word_t);

		/* Allocate a total of `reqsize' bytes. */
		hi_bitset = (mpart_blkst_word_t *)krealloc_nx(self->msd_hibitset, reqsize,
		                                              GFP_ATOMIC | GFP_CALLOC |
		                                              GFP_LOCKED | GFP_PREFLT);
		if unlikely(!hi_bitset) {
			unlockall(lopart);
			/* Must allocate while blocking */
			hi_bitset = self->msd_hibitset;
			hi_bitset = (mpart_blkst_word_t *)krealloc(self->msd_hibitset, reqsize,
			                                           GFP_CALLOC | GFP_LOCKED | GFP_PREFLT);
			self->msd_hibitset = hi_bitset;
			return false;
		}
		self->msd_hibitset = hi_bitset;
	}
done:
	return true;
}



/* Calculate the index of the chunk, and the offset into that
 * chunk  after  skipping  the  first  `lo_pages'  of `self'. */
PRIVATE NOBLOCK NONNULL((1, 3, 4)) void
NOTHROW(FCALL mchunkvec_split_after)(struct mchunkvec const *__restrict self,
                                     physpagecnt_t lo_pages,
                                     size_t *__restrict psplit_index,
                                     physpagecnt_t *__restrict psplit_offset) {
	size_t i = 0;
	for (;;) {
		physpagecnt_t chunk_size;
		assert(i < self->ms_c);
		chunk_size = self->ms_v[i].mc_size;
		if (chunk_size > lo_pages)
			break;
		lo_pages -= chunk_size;
		++i;
	}
	*psplit_index  = i;
	*psplit_offset = lo_pages;
}



/* Allocate `self->msd_himvec' if necessary. */
PRIVATE NOBLOCK NONNULL((1)) bool FCALL
mpart_split_data_alloc_himvec_or_unlock(struct mpart_split_data *__restrict self) {
	/* Dynamically allocate the vector needed for scattered mem/swp in hipart */
	struct mpart *lopart = self->msd_lopart;
	switch (lopart->mp_state) {
		physpagecnt_t lo_pages;

	case MPART_ST_MEM_SC: {
		size_t split_index;
		physpagecnt_t split_offset;
		lo_pages = self->msd_offset / PAGESIZE;
do_split_many_chunks_after_lo_pages:
		/* Figure out where we need to put the split. */
		mchunkvec_split_after(&lopart->mp_mem_sc, lo_pages,
		                      &split_index, &split_offset);

		/* Deal with special cases where splitting is easy. */
		if (split_index == 0) {
			/* Simple case */
		} else if (split_index == 1 && split_offset == 0) {
			/* Simple case */
		} else if (split_index == lopart->mp_mem_sc.ms_c - 1) {
			/* Simple case */
		} else {
			/* The (second) generic case: We need to split somewhere in the middle. */
			struct mchunk *vec;
			size_t lo_vec_length, hi_vec_length, newvec_length;
			lo_vec_length = split_index;
			hi_vec_length = lopart->mp_mem_sc.ms_c - lo_vec_length;
			if (split_offset == 0)
				++lo_vec_length;
			newvec_length = MIN(lo_vec_length, hi_vec_length);
			assert(newvec_length != 0);

			/* Ensure that sufficient memory is available. */
			vec = (struct mchunk *)krealloc_nx(self->msd_himvec,
			                                   newvec_length * sizeof(struct mchunk),
			                                   GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
			if unlikely(!vec) {
				/* Must allocate while blocking... */
				unlockall(lopart);
				vec = (struct mchunk *)krealloc(self->msd_himvec,
				                                newvec_length * sizeof(struct mchunk),
				                                GFP_LOCKED | GFP_PREFLT);
				self->msd_himvec = vec;
				return false;
			}
			self->msd_himvec = vec;
		}
	}	break;

	case MPART_ST_SWP: {
		size_t swp_split_offset;
		swp_split_offset = mpart_get_swp_offset_after_split(lopart, self->msd_offset);
		if likely(IS_ALIGNED(swp_split_offset, PAGESIZE)) {
			break;
		} else {
			/* FIXME: This is where it gets _insanly_ complicated.
			 *
			 * - Imagine a part for a file with 1-byte block-size.
			 * - Our part now contains 8192 bytes in total, with
			 *   the bytes at 0 and  4096 being marked as  CHNG,
			 *   and were thus  written to swap  (into a  single
			 *   page, of which only for  the first 2 bytes  are
			 *   actually in-use)
			 *
			 * - We now want to split this part at offset 4096
			 *
			 * In this scenario, we'd have to:
			 *  #1:  Change the 2nd changed block to INIT
			 *  #2:  Allocate a new swap-page
			 *  #3:  Allocate a temporary physical memory page
			 *  #4:  Read the single, modified byte from offset=1
			 *       in the swap-page of lo-part (we can do  this
			 *       because  we've marked the associated page as
			 *       INIT)
			 *  #5:  Change the 2nd changed block back to CHNG,
			 *       and   broadcast   the   INIT-done   signal
			 *  #6:  Write the data read into the temporary physical
			 *       memory page to the new swap-page
			 *  #7:  Free the temporary physical memory page
			 *  #8:  Acquire a new lock to lo-part
			 *  #9:  Check that nothing's changed in the mean time
			 *  #10: Use the now-initialized swap-page for the hi-part
			 *
			 * ooof...
			 *
			 * NOTE: The above isn't safe: We can't re-verify that the
			 *       swap-contents of the  lo-part haven't changed  in
			 *       step #9, then compared to what we've read  during
			 *       step #4!
			 *       So there's even an unfixable design flaw in the above...
			 */
			kernel_panic("Not implemented");
		}
	}	break;

	case MPART_ST_SWP_SC: {
		size_t swp_split_offset;
		swp_split_offset = mpart_get_swp_offset_after_split(lopart, self->msd_offset);
		if likely(IS_ALIGNED(swp_split_offset, PAGESIZE)) {
			lo_pages = swp_split_offset / PAGESIZE;
			goto do_split_many_chunks_after_lo_pages;
		} else {
			/* FIXME: See above */
			kernel_panic("Not implemented");
		}
	}	break;

	default:
		break;
	}
	return true;
}



/* Drop 1 reference to every futex from the given tree.
 * NOTE: The caller must be holding a lock to the associated
 *       mem-part-meta controller. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfutex_tree_foreach_decref_or_destroy_later)(struct mfutex *__restrict self) {
	struct mfutex *lhs, *rhs;
again:
	lhs = self->mfu_mtaent.rb_lhs;
	rhs = self->mfu_mtaent.rb_rhs;
	decref_unlikely(self);
	if (lhs != NULL) {
		if (rhs != NULL)
			mfutex_tree_foreach_decref_or_destroy_later(rhs);
		self = lhs;
		goto again;
	}
	if (rhs != NULL) {
		self = rhs;
		goto again;
	}
}







/* Split the given mem-part `self' (which  should be a member of  `file')
 * after `offset' bytes from the start of backing file. For this purpose,
 * the given `offset' should  be `> mpart_getminaddr(self)', and must  be
 * both page- and block-aligned.
 * @return: NULL: The given `offset' is outside  the bounds of file  memory
 *                represented by `part'. The caller should handle this case
 *                by re-checking for a missing part, and creating that part
 *                if it cannot be found.
 * @return: * :   A reference to a part that (at one point) began at `offset' */
PUBLIC BLOCKING NONNULL((1)) REF struct mpart *FCALL
mpart_split(struct mpart *__restrict self,
            PAGEDIR_PAGEALIGNED pos_t offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	struct mpart_split_data data;
	struct mfile *file;
#ifdef __INTELLISENSE__
	struct mpart *&lopart = data.msd_lopart;
	struct mpart *&hipart = data.msd_hipart;
#else /* __INTELLISENSE__ */
#define lopart data.msd_lopart
#define hipart data.msd_hipart
#endif /* !__INTELLISENSE__ */
	assert(mfile_partaddr_aligned(self->mp_file, offset));
	mpart_split_data_init(&data, self);
	TRY {
again:
		/* Acquire a lock. */
		mpart_lock_acquire(self);

		/* Quick check: If the given `offset' is out-of-bounds,
		 *              then we actually have to return `NULL'! */
		if unlikely(offset <= mpart_getminaddr(self) ||
		            offset >= mpart_getendaddr(self)) {
release_and_return_null:
			mpart_split_data_fini(&data);
			mpart_lock_release(self);
			return NULL;
		}

		/* Ensure that there aren't any INIT-blocks. */
		if (!mpart_initdone_or_unlock(self, NULL))
			goto again;

		/* Ensure that no-one is holding any DMA-locks onto `self',
		 * which may be  used to  prevent a part  from being  split */
		if (!mpart_nodma_or_unlock(self, NULL))
			goto again;

		/* Calculate the part-relative offset where the split should be made. */
		data.msd_offset = (mpart_reladdr_t)(offset - mpart_getminaddr(self));

		file = self->mp_file;
		assertf(data.msd_offset != 0, "Invalid split-offset: 0");
		assertf(mfile_partaddr_aligned(file, data.msd_offset),
		        "Badly aligned offset %#" PRIxSIZ, data.msd_offset);
		assertf(!(self->mp_flags & MPART_F_NOSPLIT),
		        "You're not allowed to split this part!");

		/* Step #1: Acquire  references to all  affected mmans. This way,
		 *          we can prevent any of them from dying under our noses
		 *          while we're still trying  to fiddle with them,  which
		 *          also gives us  a consistent base-line  when it  comes
		 *          to  which nodes  are still  alive (those  with a non-
		 *          destroyed memory manager). */
		mpart_foreach_mmans_incref(self);

		/* Step #2: Acquire locks to all of the mmans of mapping nodes. */
		if (!mpart_lock_all_mmans_or_unlock_and_decref(self))
			goto again;

		/* Step #3: If present, acquire a lock to the lo-part's meta-data futex tree. */
		if (!mpart_lock_meta_futex_or_unlock_and_decref(self))
			goto again;

		/* Step #4: Make all of the necessary allocations. */
		if (!mpart_split_data_alloc_mnodes_or_unlock(&data)) {
relock_with_data:
			mpart_lock_acquire_and_initdone_nodma(self);
			if unlikely(data.msd_offset >= mpart_getsize(self))
				goto release_and_return_null;
			file = self->mp_file;
			assertf(mfile_partaddr_aligned(file, data.msd_offset),
			        "Internal error: file alignment changed");
			assertf(!(self->mp_flags & MPART_F_NOSPLIT),
			        "Internal error: MPART_F_NOSPLIT flag was modified");
			mpart_foreach_mmans_incref(self);
			if (!mpart_lock_all_mmans_or_unlock_and_decref(self))
				goto relock_with_data;
			if (!mpart_lock_meta_futex_or_unlock_and_decref(self))
				goto relock_with_data;
		}
		if (!mpart_split_data_alloc_himeta_or_unlock(&data))
			goto again;
		if (!mpart_split_data_alloc_hibitset_or_unlock(&data))
			goto again;
		if (!mpart_split_data_alloc_himvec_or_unlock(&data))
			goto again;

		/* Step #5: If the associated file isn't anonymous, then we must
		 *          also acquire a lock to it, so that we can insert the
		 *          new part we'll be creating into it. */
		if (!mpart_isanon(self)) {
			if (!mfile_lock_trywrite(file)) {
				incref(file);
				unlockall(self);
				FINALLY_DECREF_UNLIKELY(file);
				mfile_lock_waitwrite(file);
				goto again;
			}
			assert(!mfile_isanon(file));
		}
	} EXCEPT {
		mpart_split_data_fini(&data);
		RETHROW();
	}

	/* At this point, we've made all of the necessary allocations, and acquired
	 * all  of the mandatory locks. With this in  mind: This is the point of no
	 * return, after which all we really have to do is put everything together. */

	/* The initial reference that we'll end up returning */
	hipart->mp_refcnt = 1;

	/* Fill in flags for the new pat. */
	hipart->mp_xflags = MPART_XF_NORMAL;
	hipart->mp_flags = (lopart->mp_flags & (MPART_F_GLOBAL_REF |
	                                        MPART_F_CHANGED |
	                                        MPART_F_NOFREE |
	                                        MPART_F_BLKST_INL)) |
	                   (MPART_F_LOCKBIT);

	if (hipart->mp_flags & MPART_F_GLOBAL_REF)
		++hipart->mp_refcnt; /* The reference that'll be stored in global data! */
	hipart->mp_state = lopart->mp_state;
	hipart->mp_file  = incref(file);
	LIST_INIT(&hipart->mp_copy);
	LIST_INIT(&hipart->mp_share);
	SLIST_INIT(&hipart->mp_lockops);
	/*hipart->mp_allparts;*/ /* Initialized below */
	/*hipart->mp_changed;*/  /* Initialized below */
	hipart->mp_minaddr = lopart->mp_minaddr + data.msd_offset;
	hipart->mp_maxaddr = lopart->mp_maxaddr;
	assert(hipart->mp_minaddr < hipart->mp_maxaddr);

	/* Re-distribute mem-nodes from `lopart' to refer to `hipart' when necessary
	 * NOTE: There's no need to re-map anything, because the backing physical memory
	 *       doesn't actually change at any point! */
	{
		unsigned int i;
		for (i = 0; i < lengthof(lopart->_mp_nodlsts); ++i) {
			struct mnode *lonode;
			LIST_FOREACH_SAFE (lonode, &lopart->_mp_nodlsts[i], mn_link) {
				mpart_reladdr_t min, max;
				if unlikely(wasdestroyed(lonode->mn_mman))
					continue; /* Skip nodes that were destroyed. */
				if unlikely(lonode->mn_flags & MNODE_F_UNMAPPED)
					continue; /* Skip nodes that were unmapped. (NOTE: We're holding a lock to `lonode->mn_mman') */
				assert(lonode->mn_part == lopart);
				min = mnode_getpartminaddr(lonode);
				max = mnode_getpartmaxaddr(lonode);
				assert(min <= max);
				assert(max < mpart_getsize(lopart));
				assertf(mpart_getnodlst_from_mnodeflags(hipart, lonode->mn_flags) == &hipart->_mp_nodlsts[i],
				        "Node indicates list:           %s\n"
				        "but we found the node in list: %s\n",
				        (lonode->mn_flags & MNODE_F_SHARED) ? "shared" : "copy",
				        (&lopart->_mp_nodlsts[i] == &lopart->mp_share) ? "shared" : "copy");
				if (min >= data.msd_offset) {
					/* Our `lonode' is entirely located within `hipart' -> move it in there
					 *
					 * NOTE: This also moves the reference we (might be) holding to `lonode->mn_mman',
					 *       by  having it be  inherited by `hipart' (which  will eventually drop said
					 *       reference in `mpart_foreach_mmans_decref(hipart)') */
					LIST_REMOVE(lonode, mn_link);
					LIST_INSERT_HEAD(&hipart->_mp_nodlsts[i], lonode, mn_link);
					decref_nokill(lopart);
					lonode->mn_part = hipart;
					++hipart->mp_refcnt;
					lonode->mn_partoff -= data.msd_offset;
				} else if (/*min < data.msd_offset && */ data.msd_offset <= max) {
					/* NOTE: We _only_ have to create new nodes for those cases where
					 *       the split position  lies _inside_ of  the range that  is
					 *       actually being mapped by some node!
					 * s.a. `mnode_getpartminaddr() ... mnode_getpartmaxaddr()' */
					struct mnode *hinode;
					size_t noderel_offset;
					/* This one must be split! */
					assertf(!(lonode->mn_flags & MNODE_F_NOSPLIT),
					        "Not allowed to split this node (at %p...%p)",
					        mnode_getminaddr(lonode),
					        mnode_getmaxaddr(lonode));
					assert(!SLIST_EMPTY(&data.msd_hinodes));
					hinode = SLIST_FIRST(&data.msd_hinodes);
					SLIST_REMOVE_HEAD(&data.msd_hinodes, _mn_alloc);
					noderel_offset     = data.msd_offset - min;
					hinode->mn_flags   = lonode->mn_flags;
					hinode->mn_minaddr = lonode->mn_minaddr + noderel_offset;
					hinode->mn_maxaddr = lonode->mn_maxaddr;
					assert(!wasdestroyed(lonode->mn_mman)); /* We don't weakincref because the mman wasn't destroyed, yet! */
					hinode->mn_mman    = lonode->mn_mman;
					hinode->mn_part    = hipart;
					incref(lonode->mn_mman); /* This incref will later be dropped by `mpart_foreach_mmans_decref(hipart)' */
					++hipart->mp_refcnt;
					hinode->mn_partoff = 0;
					LIST_INSERT_HEAD(&hipart->_mp_nodlsts[i], hinode, mn_link);
					LIST_ENTRY_UNBOUND_INIT(&hinode->mn_writable);
					if (LIST_ISBOUND(lonode, mn_writable))
						LIST_INSERT_HEAD(&hinode->mn_mman->mm_writable, hinode, mn_writable);
					hinode->mn_fspath = xincref(lonode->mn_fspath);
					hinode->mn_fsname = xincref(lonode->mn_fsname);
					hinode->mn_module = lonode->mn_module;
					if (hinode->mn_module)
						module_inc_nodecount(hinode->mn_module);

					/* Update/re-insert both nodes. */
					mman_mappings_removenode(lonode->mn_mman, lonode);
					lonode->mn_maxaddr = hinode->mn_minaddr - 1;
					assert(IS_ALIGNED((uintptr_t)lonode->mn_minaddr, PAGESIZE));
					assert(IS_ALIGNED((uintptr_t)lonode->mn_maxaddr + 1, PAGESIZE));
					mman_mappings_insert(lonode->mn_mman, lonode);
					mman_mappings_insert(hinode->mn_mman, hinode);
				}
			}
		}
	} /* Scope */

	/* Fill in the backing memory for `hipart' */
	switch (hipart->mp_state) {
		physpagecnt_t lo_pages;

	case MPART_ST_MEM: {
		/* (aside from VOID), this one's probably the simplest case! */
		lo_pages = data.msd_offset / PAGESIZE;
do_split_single_chunk_after_lo_pages:
		hipart->mp_mem.mc_start = lopart->mp_mem.mc_start + lo_pages;
		hipart->mp_mem.mc_size  = lopart->mp_mem.mc_size - lo_pages;
		lopart->mp_mem.mc_size  = lo_pages;
		goto maybe_free_unused_mvec;
	}	break;

	case MPART_ST_MEM_SC: {
		size_t split_index;
		physpagecnt_t split_offset;
		lo_pages = data.msd_offset / PAGESIZE;
do_split_many_chunks_after_lo_pages:
		/* Figure out where we need to put the split. */
		mchunkvec_split_after(&lopart->mp_mem_sc, lo_pages,
		                      &split_index, &split_offset);

		/* Deal with special cases where splitting is easy. */
		assert(hipart->mp_state == lopart->mp_state);
		if (split_index == 0) {
			/* Split within the first chunk. */
			memcpy(&hipart->mp_mem_sc,
			       &lopart->mp_mem_sc,
			       sizeof(struct mchunkvec));
			lopart->mp_mem.mc_start = hipart->mp_mem_sc.ms_v[0].mc_start;
			lopart->mp_mem.mc_size  = split_offset;
			hipart->mp_mem_sc.ms_v[0].mc_start += split_offset;
			hipart->mp_mem_sc.ms_v[0].mc_size -= split_offset;
fix_lo_part_state_affinity:
			lopart->mp_state = hipart->mp_state == MPART_ST_MEM_SC ? MPART_ST_MEM : MPART_ST_SWP;
			goto maybe_free_unused_mvec;
		} else if (split_index == 1 && split_offset == 0) {
			/* Split at the end of the first chunk. */
			struct mchunk *vec, *newvec;
			size_t cnt = lopart->mp_mem_sc.ms_c - 1;
			vec = lopart->mp_mem_sc.ms_v;
			memcpy(&lopart->mp_mem, &vec[0], sizeof(struct mchunk));
			memmovedown(&vec[0], &vec[1], cnt, sizeof(struct mchunk));
			newvec = (struct mchunk *)krealloc_nx(vec, cnt * sizeof(struct mchunk),
			                                      GFP_ATOMIC | GFP_CALLOC |
			                                      GFP_LOCKED | GFP_PREFLT);
			if likely(newvec)
				vec = newvec;
			hipart->mp_mem_sc.ms_v = vec;
			hipart->mp_mem_sc.ms_c = cnt;
			goto fix_lo_part_state_affinity;
		} else if (split_index == lopart->mp_mem_sc.ms_c - 1) {
			struct mchunk *last_chunk;
			last_chunk = &lopart->mp_mem_sc.ms_v[lopart->mp_mem_sc.ms_c - 1];
			if (split_offset == 0) {
				struct mchunk *newvec;
				/* Split at the start of the last chunk. */
				hipart->mp_mem.mc_start = last_chunk->mc_start;
				hipart->mp_mem.mc_size  = last_chunk->mc_size;
				--lopart->mp_mem_sc.ms_c;
				newvec = (struct mchunk *)krealloc_nx(lopart->mp_mem_sc.ms_v,
				                                      lopart->mp_mem_sc.ms_c *
				                                      sizeof(struct mchunk),
				                                      GFP_ATOMIC | GFP_CALLOC |
				                                      GFP_LOCKED | GFP_PREFLT);
				if likely(newvec != NULL)
					lopart->mp_mem_sc.ms_v = newvec;
			} else {
				/* Split within the last chunk. */
				hipart->mp_mem.mc_start = last_chunk->mc_start + split_offset;
				hipart->mp_mem.mc_size  = last_chunk->mc_size - split_offset;
				last_chunk->mc_size     = split_offset;
			}
			hipart->mp_state = lopart->mp_state == MPART_ST_MEM_SC ? MPART_ST_MEM : MPART_ST_SWP;
			goto maybe_free_unused_mvec;
		} else {
			/* The generic case: We need to split somewhere in the middle. */
			struct mchunk *newvec, *oldvec;
			size_t lo_vec_length, hi_vec_length, newvec_length;
			lo_vec_length = split_index;
			hi_vec_length = lopart->mp_mem_sc.ms_c - lo_vec_length;
			if (split_offset == 0)
				++lo_vec_length;
			newvec_length = MIN(lo_vec_length, hi_vec_length);
			assert(newvec_length != 0);
			assert(kmalloc_usable_size(data.msd_himvec) >= newvec_length * sizeof(struct mchunk));
			newvec = data.msd_himvec;
			KMALLOC_TRY_TRUNCATE_LOCKED_ATOMIC_NX(newvec, newvec_length * sizeof(struct mchunk), 0);
			DBG_memset(&data.msd_himvec, 0xcc, sizeof(data.msd_himvec));
			oldvec = lopart->mp_mem_sc.ms_v;
			if (lo_vec_length < hi_vec_length) {
				/* Use `newvec' for `lopart' */
				memcpy(newvec, oldvec, lo_vec_length, sizeof(struct mchunk));
				memmovedown(oldvec, oldvec + lo_vec_length, hi_vec_length, sizeof(struct mchunk));
				KMALLOC_TRY_TRUNCATE_LOCKED_ATOMIC_NX(oldvec, hi_vec_length * sizeof(struct mchunk), 0);
				lopart->mp_mem_sc.ms_v = newvec;
				lopart->mp_mem_sc.ms_c = lo_vec_length;
				hipart->mp_mem_sc.ms_v = oldvec;
				hipart->mp_mem_sc.ms_c = hi_vec_length;
			} else {
				/* Use `newvec' for `hipart' */
				memcpy(newvec, oldvec + lo_vec_length, hi_vec_length, sizeof(struct mchunk));
				KMALLOC_TRY_TRUNCATE_LOCKED_ATOMIC_NX(oldvec, lo_vec_length * sizeof(struct mchunk), 0);
				lopart->mp_mem_sc.ms_v = oldvec;
				lopart->mp_mem_sc.ms_c = lo_vec_length;
				hipart->mp_mem_sc.ms_v = newvec;
				hipart->mp_mem_sc.ms_c = hi_vec_length;
			}
			if (split_offset == 0) {
				/* Must adjust the last chunk of lopart, and the first chunk of hipart */
				struct mchunk *lomax, *himin;
				lomax = &lopart->mp_mem_sc.ms_v[lopart->mp_mem_sc.ms_c - 1];
				himin = &hipart->mp_mem_sc.ms_v[0];
				assert(bcmp(lomax, himin, sizeof(struct mchunk)) == 0);
				lomax->mc_size = split_offset;
				himin->mc_start += split_offset;
				himin->mc_size -= split_offset;
			}
		}
	}	break;

	case MPART_ST_SWP: {
		size_t swp_split_offset;
		swp_split_offset = mpart_get_swp_offset_after_split(self, data.msd_offset);
		if likely(IS_ALIGNED(swp_split_offset, PAGESIZE)) {
			lo_pages = swp_split_offset / PAGESIZE;
			goto do_split_single_chunk_after_lo_pages;
		} else {
			/* FIXME: See above */
			kernel_panic("Not implemented");
		}
		goto maybe_free_unused_mvec;
	}	break;

	case MPART_ST_SWP_SC: {
		size_t swp_split_offset;
		swp_split_offset = mpart_get_swp_offset_after_split(self, data.msd_offset);
		if likely(IS_ALIGNED(swp_split_offset, PAGESIZE)) {
			lo_pages = swp_split_offset / PAGESIZE;
			goto do_split_many_chunks_after_lo_pages;
		} else {
			/* FIXME: See above */
			kernel_panic("Not implemented");
		}
		goto maybe_free_unused_mvec;
	}	break;

	default:
maybe_free_unused_mvec:
		if unlikely(data.msd_himvec != NULL) {
			kfree(data.msd_himvec);
			DBG_memset(&data.msd_himvec, 0xcc, sizeof(data.msd_himvec));
		}
		break;
	}

	/* Fill in the block-status bitset for `hipart' */
	if (lopart->mp_flags & MPART_F_BLKST_INL) {
		/* If everything already managed to fit into a single word in the lo-part,
		 * then  we can just re-use the old  status-word, but simply shift it over
		 * some. */
		size_t lo_block_count;
		lo_block_count = data.msd_offset >> file->mf_blockshift;
		assert(lo_block_count != 0);
		assert(lo_block_count <= MPART_BLKST_BLOCKS_PER_WORD);
		hipart->mp_blkst_inl = lopart->mp_blkst_inl >> (lo_block_count * MPART_BLOCK_STBITS);
maybe_free_unused_hibitset:
		if unlikely(data.msd_hibitset != NULL) {
			kfree(data.msd_hibitset);
			DBG_memset(&data.msd_hibitset, 0xcc, sizeof(data.msd_hibitset));
		}
	} else if (lopart->mp_blkst_ptr == NULL) {
		hipart->mp_blkst_ptr = NULL;
		goto maybe_free_unused_hibitset;
	} else {
		size_t i, hi_num_bytes, lo_block_count, hi_block_count;
		mpart_blkst_word_t *lo_bitset;
		hi_num_bytes   = mpart_getsize(lopart) - data.msd_offset;
		lo_block_count = data.msd_offset >> file->mf_blockshift;
		hi_block_count = hi_num_bytes >> file->mf_blockshift;
		lo_bitset      = lopart->mp_blkst_ptr;
		assert(hi_block_count != 0);
		if (hi_block_count <= MPART_BLKST_BLOCKS_PER_WORD) {
			/* Can use the inline bitset. */
			mpart_blkst_word_t word = 0;
			for (i = 0; i < hi_block_count; ++i) {
				unsigned int st;
				st = vector_getblockstatus(lo_bitset, lo_block_count + i);
				word |= st << (i * MPART_BLOCK_STBITS);
			}
			hipart->mp_blkst_inl = word;
			hipart->mp_flags |= MPART_F_BLKST_INL;
			goto maybe_free_unused_hibitset;
		} else {
			size_t reqsize;
			mpart_blkst_word_t *hi_bitset = data.msd_hibitset;
			assert(hi_bitset);
			reqsize = CEILDIV(hi_block_count, MPART_BLKST_BLOCKS_PER_WORD) *
			          sizeof(mpart_blkst_word_t);
			assert(kmalloc_usable_size(hi_bitset) >= reqsize);
			assert(memxchr(hi_bitset, 0, reqsize) == NULL); /* We're assuming that `hi_bitset' is zero-initialized! */

			/* Try to truncate the actual vector length to what we need. */
			KMALLOC_TRY_TRUNCATE_LOCKED_ATOMIC_NX(hi_bitset, reqsize, GFP_CALLOC);

			/* Now to actually copy the bits! */
			for (i = 0; i < hi_block_count; ++i) {
				unsigned int st;
				st = vector_getblockstatus(lo_bitset, lo_block_count + i);
				zvector_setblockstatus(hi_bitset, i, st);
			}
			hipart->mp_blkst_ptr = hi_bitset;
		}
	}

	/* If  the new (hi-part) has the CHANGED flag set (as inherited from the original part),
	 * then check if  (some of) the  actually changed blocks  can be found  in the  hi-part.
	 * If so, then we must immediately add the hi-part to the changed list of the associated
	 * mem-file. */
	DBG_memset(&hipart->mp_changed, 0xcc, sizeof(hipart->mp_changed));
	if ((hipart->mp_flags & MPART_F_CHANGED) &&
	    file->mf_ops->mo_saveblocks != NULL && !mpart_isanon(self)) {
		assert(!mfile_isanon(file));
		if (mpart_really_changed(hipart)) {
			struct mpart *next;

			/* Must add the new `hipart' to the file's list of changed parts.
			 *
			 * NOTE: Special case must be taken to deal with the case where
			 *       backing  the file's changed-part  list has been marked
			 *       as anonymous, or simply doesn't wish to keep track  of
			 *       changed parts. */
			incref(hipart);
			do {
				next = ATOMIC_READ(file->mf_changed.slh_first);
				if unlikely(next == MFILE_PARTS_ANONYMOUS) {
					decref_nokill(hipart);
					goto clear_hipart_changed_bit;
				}
				hipart->mp_changed.sle_next = next;
				COMPILER_WRITE_BARRIER();
			} while (!ATOMIC_CMPXCH_WEAK(file->mf_changed.slh_first,
			                             next, hipart));
		} else {
			/* The hi-part hasn't ~actually~ changed (so just clear the flag, and don't
			 * add it to the list of changed parts) */
clear_hipart_changed_bit:
			hipart->mp_flags &= ~MPART_F_CHANGED;
		}
	}

	/* Fill in the MLOCK flags for the new part. */
	if (lopart->mp_flags & MPART_F_MLOCK_FROZEN) {
		/* If the original part's mlock-status is frozen, then just
		 * inherit  the  status and  that  fact for  the  new part. */
		hipart->mp_flags |= lopart->mp_flags & (MPART_F_MLOCK | MPART_F_MLOCK_FROZEN);
	} else if (lopart->mp_flags & MPART_F_MLOCK) {
		/* Must update the MLOCK status of both the lo- and hi-parts */
		if (!mnode_list_contains_mlocked_nodes(&lopart->mp_copy) &&
		    !mnode_list_contains_mlocked_nodes(&lopart->mp_share))
			ATOMIC_AND(lopart->mp_flags, ~MPART_F_MLOCK);

		if (mnode_list_contains_mlocked_nodes(&hipart->mp_copy) ||
		    mnode_list_contains_mlocked_nodes(&hipart->mp_share))
			hipart->mp_flags |= MPART_F_MLOCK;
	}

	/* Initialize the meta-data controller for the hi-part by stealing
	 * all futex  objects  above  the  split-mark  from  the  lo-part. */
	if (lopart->mp_meta != NULL) {
		struct mfutex *ftx;
		struct mpartmeta *lometa = lopart->mp_meta;
		struct mpartmeta *himeta = data.msd_himeta;
		struct mfutex_slist dead_mfutex;
		assert(himeta != NULL);
		atomic_rwlock_cinit_write(&himeta->mpm_ftxlock);
		assert(SLIST_EMPTY(&himeta->mpm_ftxlops));
		assert(himeta->mpm_ftx == NULL);
		hipart->mp_meta = himeta; /* Fill in the meta-data field of the hi-part. */
		COMPILER_WRITE_BARRIER();
		SLIST_INIT(&dead_mfutex);
		while ((ftx = mpartmeta_ftx_rremove(lometa, data.msd_offset,
		                                    (mpart_reladdr_t)-1)) != NULL) {
			/* Take a reference to prevent futex objects from being destroyed
			 * before we've finished transferring them to their new mem-part! */
			if likely(tryincref(ftx)) {
				/* Futex is still alive. */
				ftx->mfu_addr -= data.msd_offset;
				COMPILER_WRITE_BARRIER();
				awref_set(&ftx->mfu_part, hipart);
				mpartmeta_ftx_insert(himeta, ftx);
			} else {
				/* Futex is already dead... */
				SLIST_INSERT(&dead_mfutex, ftx, _mfu_dead);
			}
		}

		/* Must re-insert dead futex objects into the old tree, such that
		 * they  can be reap the normal way  once we unlock the old tree. */
		if unlikely(!SLIST_EMPTY(&dead_mfutex)) {
			do {
				ftx = SLIST_FIRST(&dead_mfutex);
				SLIST_REMOVE_HEAD(&dead_mfutex, _mfu_dead);
				mpartmeta_ftx_insert(lometa, ftx);
			} while (!SLIST_EMPTY(&dead_mfutex));
		}

		_mpartmeta_ftxlock_endwrite(lometa); /* Acquired above (in `Step #3') */

		/* We're still holding references to  _all_ of the futex objects  that
		 * we managed to transfer over into the himeta-tree. As such, we still
		 * have to drop all of those references */
		if (himeta->mpm_ftx != NULL)
			mfutex_tree_foreach_decref_or_destroy_later(himeta->mpm_ftx);
		_mpartmeta_ftxlock_endwrite(himeta);

		/* Must reap dead futex objects once again, but this time only have to
		 * do so because we've just released our locks to the meta-data  futex
		 * trees! */
		mpartmeta_ftxlock_reap(himeta, hipart);
		mpartmeta_ftxlock_reap(lometa, lopart);
	} else {
		if unlikely(data.msd_himeta != NULL) {
			kfree(data.msd_himeta);
			DBG_memset(&data.msd_himeta, 0xcc, sizeof(data.msd_himeta));
		}
		hipart->mp_meta = NULL;
	}

	/* Insert the new `hipart' into the global list of know parts.
	 * NOTE: On this has been done, `hipart' may be considered finalized,
	 *       meaning that we can no  longer go around normal  limitations
	 *       when it comes to writing to its fields. */
#ifdef LIBVIO_CONFIG_ENABLED
	if (hipart->mp_state == MPART_ST_VIO) {
		LIST_ENTRY_UNBOUND_INIT(&hipart->mp_allparts);
	} else
#endif /* LIBVIO_CONFIG_ENABLED */
	{
		COMPILER_WRITE_BARRIER();
		mpart_all_list_insert(hipart);
	}

	/* Update the part-tree of the associated file. */
	if (!mpart_isanon(self)) {
		mpart_tree_removenode(&file->mf_parts, self);
		lopart->mp_maxaddr = hipart->mp_minaddr - 1;
		mpart_tree_insert(&file->mf_parts, lopart);
		mpart_tree_insert(&file->mf_parts, hipart);
		mfile_lock_endwrite(file);
	} else {
		lopart->mp_maxaddr = hipart->mp_minaddr - 1;
		_mpart_init_asanon(hipart);
	}


	/* Release locks. */
	mpart_unlock_all_mmans2(lopart, hipart);
	mpart_foreach_mmans_decref(hipart);
	mpart_foreach_mmans_decref(lopart);

	/* Also release the lock to the (new) `hipart'
	 * This lock was originally acquired (so-to-say) by initializing the new
	 * part's `mp_flags' field with the `MPART_F_LOCKBIT' flag already  set. */
	mpart_assert_integrity(hipart);
	mpart_lock_release(hipart);

	/* Truncate dynamically allocated parts of `self'
	 * NOTE: We're  allowed  to   realloc/free  a   dynamically  allocated   block-status
	 *       bitset,  even  though there  are  cases where  a  thread can  write  to that
	 *       vector  without  first  acquiring a  lock  to the  associated  part, because
	 *       the only  case where  this can  happen is  when one  had previously  written
	 *       INIT  values  to  its  elements,  which  is  something  that  we've  already
	 *       asserted to not be the case (s.a. `mpart_lock_acquire_and_initdone_nodma()') */
	if (!(self->mp_flags & MPART_F_BLKST_INL)) {
		size_t block_count;
		mpart_blkst_word_t *bitset;
		bitset      = self->mp_blkst_ptr;
		block_count = mpart_getblockcount(self, file);
		if (block_count <= MPART_BLKST_BLOCKS_PER_WORD) {
			/* Switch over to the inline bitset. */
			self->mp_blkst_inl = bitset[0];
			ATOMIC_OR(self->mp_flags, MPART_F_BLKST_INL);
			kfree(bitset);
		} else {
			/* Truncate the bitset. */
			size_t reqsize;
			reqsize = CEILDIV(block_count, MPART_BLKST_BLOCKS_PER_WORD) *
			          sizeof(mpart_blkst_word_t);
			assert(kmalloc_usable_size(bitset) >= reqsize);
			bitset = (mpart_blkst_word_t *)krealloc_nx(bitset, reqsize,
			                                           GFP_ATOMIC | GFP_LOCKED |
			                                           GFP_PREFLT);
			if likely(bitset != NULL)
				self->mp_blkst_ptr = bitset;
		}
	}

	/* Truncate a dynamically allocated chunk-vector. */
#if 0 /* Already (implicitly) done above */
	if (self->mp_state == MPART_ST_SWP_SC || self->mp_state == MPART_ST_MEM_SC) {
		static_assert(offsetof(struct mpart, mp_mem_sc.ms_c) == offsetof(struct mpart, mp_swp_sc.ms_c));
		static_assert(offsetof(struct mpart, mp_mem_sc.ms_v) == offsetof(struct mpart, mp_swp_sc.ms_v));
		struct mchunk *vec;
		vec = self->mp_mem_sc.ms_v;
		vec = (struct mchunk *)krealloc_nx(vec,
		                                   self->mp_mem_sc.ms_c * sizeof(struct mchunk),
		                                   GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
		if likely(vec != NULL)
			self->mp_mem_sc.ms_v = vec;
	}
#endif

	mpart_assert_integrity(self);
	mpart_lock_release(self);

	/* Free nodes for the hi-part that we didn't end up using. */
	if unlikely(!SLIST_EMPTY(&data.msd_hinodes)) {
		do {
			struct mnode *node;
			node = SLIST_FIRST(&data.msd_hinodes);
			SLIST_REMOVE_HEAD(&data.msd_hinodes, _mn_alloc);
			kfree(node);
		} while (!SLIST_EMPTY(&data.msd_hinodes));
	}

	return hipart;
#undef lopart
#undef hipart
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_SPLIT_C */
