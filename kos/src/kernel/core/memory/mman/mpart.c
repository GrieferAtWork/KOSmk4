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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_C 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/memory.h>
#include <kernel/mman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/mpartmeta.h>
#include <kernel/swap.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <kos/except.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if __SIZEOF_POINTER__ == 4 && MPART_BLOCK_STBITS == 2
#define MPART_BLOCK_REPEAT(st) (__UINT32_C(0x55555555) * (st))
#elif __SIZEOF_POINTER__ == 8 && MPART_BLOCK_STBITS == 2
#define MPART_BLOCK_REPEAT(st) (__UINT64_C(0x5555555555555555) * (st))
#elif __SIZEOF_POINTER__ == 2 && MPART_BLOCK_STBITS == 2
#define MPART_BLOCK_REPEAT(st) (__UINT16_C(0x5555) * (st))
#elif __SIZEOF_POINTER__ == 1 && MPART_BLOCK_STBITS == 2
#define MPART_BLOCK_REPEAT(st) (__UINT8_C(0x55) * (st))
#elif __SIZEOF_POINTER__ == 4 && MPART_BLOCK_STBITS == 1
#define MPART_BLOCK_REPEAT(st) (__UINT32_C(0xffffffff) * (st))
#elif __SIZEOF_POINTER__ == 8 && MPART_BLOCK_STBITS == 1
#define MPART_BLOCK_REPEAT(st) (__UINT64_C(0xffffffffffffffff) * (st))
#elif __SIZEOF_POINTER__ == 2 && MPART_BLOCK_STBITS == 1
#define MPART_BLOCK_REPEAT(st) (__UINT16_C(0xffff) * (st))
#elif __SIZEOF_POINTER__ == 1 && MPART_BLOCK_STBITS == 1
#define MPART_BLOCK_REPEAT(st) (__UINT8_C(0xff) * (st))
#else
#error "Unsupported __SIZEOF_POINTER__ and/or MPART_BLOCK_STBITS"
#endif


#ifndef NDEBUG
#define DBG_memset(dst, byte, num_bytes) memset(dst, byte, num_bytes)
#else /* !NDEBUG */
#define DBG_memset(dst, byte, num_bytes) (void)0
#endif /* NDEBUG */

#ifdef __INTELLISENSE__
typedef typeof(((struct mpart *)0)->mp_blkst_inl) bitset_word_t;
#else /* __INTELLISENSE__ */
#define bitset_word_t typeof(((struct mpart *)0)->mp_blkst_inl)
#endif /* !__INTELLISENSE__ */
#define BITSET_ITEMS_PER_WORD (BITSOF(bitset_word_t) / MPART_BLOCK_STBITS)


/* Reference counting control for `struct mpart' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_free)(struct mpart *__restrict self) {
	if (self->mp_flags & MPART_F_COREPART) {
		/* TODO: Must use the corebase free() function! */
	}
	kfree(self);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mchunk_freemem)(struct mchunk *__restrict self) {
	page_free(self->mc_start, self->mc_size);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mchunk_freeswp)(struct mchunk *__restrict self) {
	swap_free(self->mc_start, self->mc_size);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mchunkvec_freemem)(struct mchunk *__restrict vec, size_t count) {
	size_t i;
	for (i = 0; i < count; ++i)
		mchunk_freemem(&vec[i]);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mchunkvec_freeswp)(struct mchunk *__restrict vec, size_t count) {
	size_t i;
	for (i = 0; i < count; ++i)
		mchunk_freeswp(&vec[i]);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_fini)(struct mpart *__restrict self) {
	assert(!LIST_EMPTY(&self->mp_copy));
	assert(!LIST_EMPTY(&self->mp_share));
	assert(!(self->mp_flags & MPART_F_NO_GLOBAL_REF));
	/* Make sure that we've served _all_ dead nodes that may have still been there. */
	while (!SLIST_EMPTY(&self->mp_deadnodes)) {
		struct mnode *node;
		node = SLIST_FIRST(&self->mp_deadnodes);
		SLIST_REMOVE_HEAD(&self->mp_deadnodes, _mn_dead);
		/* Deleted nodes will still be holding references to their mman!
		 * However, that's the only thing they'll still be holding. */
		weakdecref(node->mn_mman);
		/* Free the node. */
		mnode_free(node);
	}
	/* If valid, free the block-status extension vector. */
	if (MPART_ST_HASST(self->mp_state) && !(self->mp_flags & MPART_F_BLKST_INL))
		kfree(self->mp_blkst_ptr);

	/* Free state-specific data. */
	switch (self->mp_state) {

	case MPART_ST_SWP:
		if (!(self->mp_flags & MPART_F_DONT_FREE))
			mchunk_freeswp(&self->mp_swp);
		break;

	case MPART_ST_MEM:
		if (!(self->mp_flags & MPART_F_DONT_FREE))
			mchunk_freemem(&self->mp_mem);
		break;

	case MPART_ST_SWP_SC:
		if (!(self->mp_flags & MPART_F_DONT_FREE))
			mchunkvec_freeswp(self->mp_swp_sc.ms_v, self->mp_swp_sc.ms_c);
		kfree(self->mp_swp_sc.ms_v);
		break;

	case MPART_ST_MEM_SC:
		if (!(self->mp_flags & MPART_F_DONT_FREE))
			mchunkvec_freemem(self->mp_mem_sc.ms_v, self->mp_mem_sc.ms_c);
		kfree(self->mp_mem_sc.ms_v);
		break;

	default:
		break;
	}
	if (self->mp_meta) {
		/* Free mem-part meta-data. */
		mpartmeta_destroy(self->mp_meta);
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_destroy)(struct mpart *__restrict self) {
	REF struct mfile *file;
	mpart_fini(self);
	file = self->mp_file;
	assert(file);
	if (file->mf_parts == MFILE_PARTS_ANONYMOUS) {
		/* No need to unlink from the file. - The file's tree was deleted! */
remove_node_from_globals:
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
	} else if (mfile_lock_trywrite(file)) {
		/* Immediately remove the part from the associated file's tree. */
		if (file->mf_parts != MFILE_PARTS_ANONYMOUS)
			mpart_tree_removenode(&file->mf_parts, self);
		mfile_lock_endwrite(file);
		DBG_memset(&self->mp_filent, 0xcc, sizeof(self->mp_filent));
		goto remove_node_from_globals;
	} else {
		/* Enqueue the file for later deletion. */
		SLIST_ATOMIC_INSERT(&file->mf_deadparts, self, _mp_dead);
		_mfile_deadparts_reap(file);
	}
	decref(file);
}

/* Same as `mpart_destroy()', but always enqueue the part via `_mp_dead'
 * NOTE: For this, the caller must ensure that `self->mp_file->mf_parts != MFILE_PARTS_ANONYMOUS' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_destroy_later)(struct mpart *__restrict self) {
	REF struct mfile *file;
	mpart_fini(self);
	file = self->mp_file;
	assert(file);
	assert(file->mf_parts != MFILE_PARTS_ANONYMOUS);
	SLIST_ATOMIC_INSERT(&file->mf_deadparts, self, _mp_dead);
	decref(file);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_maybe_clear_mlock)(struct mpart *__restrict self) {
	/* Check if there are any nodes mapping our part that use LOCK flags.
	 * For this purpose, both copy-on-write and shared nodes can lock the part. */
	struct mnode *node;
	LIST_FOREACH (node, &self->mp_copy, mn_link) {
		if (node->mn_flags & MNODE_F_MLOCK)
			return;
	}
	LIST_FOREACH (node, &self->mp_share, mn_link) {
		if (node->mn_flags & MNODE_F_MLOCK)
			return;
	}
	/* Clear the lock-flag for our part, since there are no
	 * more nodes that could keep our part locked in-core! */
	ATOMIC_AND(self->mp_flags, ~MPART_F_MLOCK);
}



/* Reap dead nodes of `self' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _mpart_deadnodes_reap)(struct mpart *__restrict self) {
	struct mnode *node;
	struct mnode_slist deadnodes;
	bool must_recheck_mlock;
again:
	if (!mpart_lock_tryacquire(self))
		return;
	deadnodes.slh_first = SLIST_ATOMIC_CLEAR(&self->mp_deadnodes);

	/* Unlink all of the deleted nodes. */
	must_recheck_mlock = false;
	SLIST_FOREACH (node, &deadnodes, _mn_dead) {
		assert(wasdestroyed(node->mn_mman) || (node->mn_flags & MNODE_F_UNMAPPED));
		LIST_REMOVE(node, mn_link);
		if (node->mn_flags & MNODE_F_MLOCK)
			must_recheck_mlock = true;
	}

	/* If we have to, then clear the MLOCK flag. */
	if (must_recheck_mlock &&
	    (self->mp_flags & (MPART_F_MLOCK |
	                       MPART_F_MLOCK_FROZEN)) == MPART_F_MLOCK)
		mpart_maybe_clear_mlock(self);

	mpart_lock_release(self);

	/* Free all of the unlinked nodes, and drop the weak references
	 * they were still holding to their respective (now-destroyed) mmans. */
	while (!SLIST_EMPTY(&deadnodes)) {
		node = SLIST_FIRST(&deadnodes);
		SLIST_REMOVE_HEAD(&deadnodes, _mn_dead);
		weakdecref(node->mn_mman);
		mnode_free(node);
	}
	if (mpart_deadnodes_mustreap(self))
		goto again;
}



/* Mem-part tree API. All of these functions require that the caller
 * be holding a lock to the associated file. */
DECL_END

#undef RBTREE_LEFT_LEANING
#define RBTREE_WANT_PREV_NEXT_NODE
#define RBTREE(name)           mpart_tree_##name
#define RBTREE_T               struct mpart
#define RBTREE_Tkey            pos_t
#define RBTREE_GETNODE(self)   (self)->mp_filent
#define RBTREE_GETMINKEY(self) mpart_getminaddr(self)
#define RBTREE_GETMAXKEY(self) mpart_getmaxaddr(self)
#define RBTREE_ISRED(self)     ((self)->mp_flags & MPART_F__RBRED)
#define RBTREE_SETRED(self)    ATOMIC_OR((self)->mp_flags, MPART_F__RBRED)
#define RBTREE_SETBLACK(self)  ATOMIC_AND((self)->mp_flags, ~MPART_F__RBRED)
#define RBTREE_CC              FCALL
#define RBTREE_NOTHROW         NOTHROW
#define RBTREE_DECL            FUNDEF
#define RBTREE_IMPL            PUBLIC
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN

/* Get/Set the state of the index'd block `partrel_block_index' from the part's block-state bitset.
 * NOTE: The caller is responsible to ensure that mem-part is in a state
 *       where the bitset is valid (iow: `MPART_ST_HASST(self->mp_state)'),
 *       and that `partrel_block_index' is located in-bounds.
 * NOTE: The caller must be holding a lock to `self', unless the intend is to
 *       change the state of a block that used to be `MPART_BLOCK_ST_INIT',
 *       in which case `mpart_setblockstate()' may be called without holding
 *       a lock to `self'
 *       But also note that after transitioning away from `MPART_BLOCK_ST_INIT',
 *       the caller must broadcast the `mf_initdone' signal of the file that
 *       was used to initialize the part.
 * NOTE: When calling `mpart_setblockstate()' to set `MPART_BLOCK_ST_INIT',
 *       then the caller is also responsible to set the `MPART_F_MAYBE_BLK_INIT'
 *       flag! But note that that flag should _NOT_ be cleared by the one
 *       who originally set it, since other (unrelated) blocks may exist
 *       that still make use of the `MPART_BLOCK_ST_CHNG' state!
 * @param: at:  One of `MPART_BLOCK_ST_*'
 * @return: * : *ditto* */
PUBLIC NOBLOCK NONNULL((1)) unsigned int
NOTHROW(FCALL mpart_getblockstate)(struct mpart const *__restrict self,
                                   size_t partrel_block_index) {
	bitset_word_t word;
	unsigned int shift;
	assert(mpart_lock_acquired(self));
	assert(partrel_block_index < mpart_getblockcount(self, self->mp_file));
	if (self->mp_flags & MPART_F_BLKST_INL) {
		word = self->mp_blkst_inl;
	} else {
		size_t index;
		assert(self->mp_blkst_ptr);
		index = partrel_block_index / BITSET_ITEMS_PER_WORD;
		word  = self->mp_blkst_ptr[index];
	}
	shift = (unsigned int)((partrel_block_index % BITSET_ITEMS_PER_WORD) * MPART_BLOCK_STBITS);
	return (unsigned int)(word >> shift) & (((unsigned int)1 << MPART_BLOCK_STBITS) - 1);
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_setblockstate)(struct mpart *__restrict self,
                                   size_t partrel_block_index,
                                   unsigned int st) {
	bitset_word_t *pword, mask, val, oldval, newval;
	unsigned int shift;
	assert(st < ((unsigned int)1 << MPART_BLOCK_STBITS));
	shift = (unsigned int)((partrel_block_index % BITSET_ITEMS_PER_WORD) * MPART_BLOCK_STBITS);
	mask  = (bitset_word_t)((1 << MPART_BLOCK_STBITS) - 1) << shift;
	val   = (bitset_word_t)st << shift;
	if (self->mp_flags & MPART_F_BLKST_INL) {
		pword = &self->mp_blkst_inl;
	} else {
		size_t index;
		assert(self->mp_blkst_ptr);
		index = partrel_block_index / BITSET_ITEMS_PER_WORD;
		pword = &self->mp_blkst_ptr[index];
	}
	do {
		oldval = ATOMIC_READ(*pword);
		newval = (oldval & ~mask) | val;
	} while (!ATOMIC_CMPXCH_WEAK(*pword, oldval, newval));
}


/* Check if the given mem-part contains blocks with `MPART_BLOCK_ST_INIT'.
 * For this purpose, if the `MPART_F_MAYBE_BLK_INIT' flag isn't set, then
 * this function immediately returns `false'.
 * Otherwise, all blocks of the part are searched, and if one is found that
 * uses the `MPART_BLOCK_ST_INIT' state, return `true'. Otherwise, clear
 * the `MPART_F_MAYBE_BLK_INIT' flag and return `false'.
 * NOTE: The caller must be holding a lock to `self' */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL mpart_hasblocksstate_init)(struct mpart *__restrict self) {
	size_t i, count;
	assert(mpart_lock_acquired(self));
	if (!(self->mp_flags & MPART_F_MAYBE_BLK_INIT))
		return false;

	/* Manually check all of the blocks. */
	count = mpart_getblockcount(self, self->mp_file);
	for (i = 0; i < count; ++i) {
		unsigned int st;
		st = mpart_getblockstate(self, i);
		if (st == MPART_BLOCK_ST_INIT)
			return true; /* Yup! There are INIT-parts... */
	}
	/* No INIT-part found (just clear the MAYBE_BLK_INIT flag) */
	ATOMIC_AND(self->mp_flags, ~MPART_F_MAYBE_BLK_INIT);
	return false;
}


/* Sync changes made to the given mem-part.
 * @return: * : The total # of bytes that were synced.
 * NOTE: The caller is responsible for adding/removing the part to/from
 *       the associated file's list of changed parts! */
PRIVATE NOBLOCK NONNULL((1)) size_t FCALL
mpart_sync_impl(struct mpart *__restrict self, bool keep_lock) {
	size_t result = 0;
	struct mfile *file;
	size_t start, block_count;
	unsigned int status;
	bool has_initializing_parts;
	assert(!task_wasconnected());

	/* Deal with the special case where our part is a VIO-part. */
	if unlikely(self->mp_state == MPART_ST_VIO)
		goto done_noop_nolock;

again:
	if (!(self->mp_flags & MPART_F_CHANGED) && !keep_lock)
		goto done_noop_nolock;
	/* Lock the part, load it into the core, make sure that anyone
	 * that might have write-access right now has this permission
	 * revoked, and that there aren't any DMA operation in-process. */
	/* TODO: It would be nice if we could differentiate between read-
	 *       and write- DMA operations, and only wait for write DMA
	 *       operations here. - In practice, we don't have to worry
	 *       about anyone reading memory in the mean time... */
	mpart_lock_acquire_and_setcore_unwrite_nodma(self);

	if (!(self->mp_flags & MPART_F_CHANGED))
		goto done_noop;

	/* Note: For our purposes, we can assume that no-one else will
	 *       be able to make modifications to our mem-part, or set
	 *       the CHANGED flag once again until we release our lock!
	 * The case of the 1 remaining copy-on-write mapping with write
	 * access may be ignored for our purpose! */
	file = self->mp_file;

	/* Make sure that the underlying file actually provides us with
	 * the means of writing back changes */
	if unlikely(file->mf_ops->mo_saveblocks == NULL)
		goto done_noop;

	/* Figure out how many individual blocks are contained by this part. */
	block_count = mpart_getblockcount(self, file);

	/* Make sure that the block-state-bitset is writable. */
	if unlikely(!mpart_hasblockstate(self)) {
		/* Not writable means that the mem-part uses HEAP-based+NULL-alloc, which
		 * means that currently all blocks are considered `MPART_BLOCK_ST_CHNG'
		 *
		 * This is unlikely to happen, but is a well-defined scenario. */
		if (block_count <= BITSET_ITEMS_PER_WORD) {
			/* Just use the in-line bitset. */
			self->mp_blkst_inl = MPART_BLOCK_REPEAT(MPART_BLOCK_ST_CHNG);
			ATOMIC_OR(self->mp_flags, MPART_F_BLKST_INL);
		} else {
			size_t bitset_size;
			bitset_word_t *bitset;
			/* Must allocate the bitset on the heap! */
			bitset_size = CEILDIV(block_count,
			                      BITSOF(bitset_word_t) /
			                      MPART_BLOCK_STBITS) *
			              sizeof(bitset_word_t);
			bitset = (bitset_word_t *)kmalloc_nx(bitset_size,
			                                     GFP_ATOMIC | GFP_LOCKED |
			                                     GFP_PREFLT);
			if unlikely(!bitset) {
				/* Must allocate the new bitset while blocking! */
				mpart_lock_release_f(self);
				bitset = (bitset_word_t *)kmalloc(bitset_size, GFP_LOCKED | GFP_PREFLT);
				TRY {
					mpart_lock_acquire_and_setcore_unwrite_nodma(self);
				} EXCEPT {
					kfree(bitset);
					mpart_deadnodes_reap(self);
					RETHROW();
				}
				/* Check if anything's changed. */
				if unlikely(!(self->mp_flags & MPART_F_CHANGED) ||
				            file != self->mp_file ||
				            block_count != mpart_getblockcount(self, file) ||
				            mpart_hasblockstate(self)) {
					mpart_lock_release_f(self);
					kfree(bitset);
					goto again;
				}
				/* Nothing's changed, so we can just write-back the new bitset. */
			}
			/* Initialize the bitset. */
#if MPART_BLOCK_ST_CHNG == ((1 << MPART_BLOCK_STBITS) - 1)
			memset(bitset, 0xff, bitset_size);
#else /* ... */
#error "Unimplemeneted case"
#endif /* !... */
			/* Write-back the bitset. */
			self->mp_blkst_ptr = bitset;
		}
	}

	/* At this point, we know that there are changes, and we've made sure that
	 * the block-state bitset is writable (in case it wasn't writable before) */
	assert(self->mp_state == MPART_ST_MEM ||
	       self->mp_state == MPART_ST_MEM_SC);

	/* Scan for continuous segments of changed blocks. */
	has_initializing_parts = false;
	for (start = 0; start < block_count; ++start) {
		unsigned int st;
		size_t i, end;
		struct mpart_physloc loc;
		st = mpart_getblockstate(self, start);
		if (st != MPART_BLOCK_ST_CHNG) {
			/* Part hasn't been changed. */
			if (st == MPART_BLOCK_ST_INIT)
				has_initializing_parts = true;
			continue;
		}

		/* Figure out the max continuous physical memory range that
		 * can be used to describe memory starting at the lo'th block. */
		mpart_memaddr_direct(self, start << file->mf_blockshift, &loc);
		assert(loc.mppl_size >= (size_t)1 << file->mf_blockshift);

		/* Figure out the max hi-block that is still contained with
		 * the physical memory range described by `loc' */
		block_count = start + (loc.mppl_size >> file->mf_blockshift);
		assert(block_count >= start);
		assert(block_count <= mpart_getblockcount(self, file));

		/* Alter the state of changed parts to INIT, thus essentially
		 * locking them in-memory until we're down writing them back
		 * to disk, or wherever else they should go. */
		for (end = start + 1;;) {
			mpart_setblockstate(self, end - 1, MPART_BLOCK_ST_INIT);
			if (end >= block_count)
				break; /* The next block would no longer be apart of the containing chunk. */
			st = mpart_getblockstate(self, end);
			if (st != MPART_BLOCK_ST_CHNG)
				break; /* The next block is no longer marked as changed. */
			++end;
		}

		/* Now to do the actual work: */
		incref(file);
		ATOMIC_OR(self->mp_flags, MPART_F_MAYBE_BLK_INIT);
		mpart_lock_release_f(self);
		TRY {
			/* Account for synced pages. */
			result += (end - start) << file->mf_blockshift;
			/* Actually do the save. */
			(*file->mf_ops->mo_saveblocks)(file,
			                               (self->mp_minaddr >> file->mf_blockshift) + start,
			                               loc.mppl_addr, end - start);
		} EXCEPT {
			/* The write-back failed. - As such we must re-store the ST_CHNG status
			 * of all of the pages we've altered to INIT, as well as broadcast the
			 * init-done signal of the associated file. */
			for (i = start; i < end; ++i)
				mpart_setblockstate(self, i, MPART_BLOCK_ST_CHNG);
			sig_broadcast(&file->mf_initdone);
			decref_unlikely(file);
			mpart_deadnodes_reap(self);
			RETHROW();
		}
		/* Change the states of all saved pages back to ST_LOAD */
		for (i = start; i < end; ++i)
			mpart_setblockstate(self, i, MPART_BLOCK_ST_LOAD);
		sig_broadcast(&file->mf_initdone);
		decref_unlikely(file);
		/* Scan for more changes. */
		goto again;
	}
	if unlikely(has_initializing_parts) {
		incref(file);
		mpart_lock_release_f(self);
		/* Wait until parts that are being initialized finish doing that. */
		TRY {
			{
				FINALLY_DECREF_UNLIKELY(file);
				task_connect(&file->mf_initdone);
				TRY {
					mpart_lock_acquire(self);
				} EXCEPT {
					task_disconnectall();
					RETHROW();
				}
				/* Check for init-parts once again. */
				if unlikely(!mpart_hasblocksstate_init(self)) {
					mpart_lock_release_f(self);
					task_disconnectall();
					goto again;
				}
				mpart_lock_release_f(self);
			}
			/* Wait for initialization to complete. */
			task_waitfor();
		} EXCEPT {
			mpart_deadnodes_reap(self);
			RETHROW();
		}
		/* Try again. (hopefully now, all INIT-blocks are gone) */
		goto again;
	}

	/* Clear the LOCK-bit and CHANGED-flag at the same time! :)
	 * Also clear the the `MPART_F_MAYBE_BLK_INIT' flag, since
	 * we're handling that case as well (see above) */
	if (keep_lock) {
		ATOMIC_AND(self->mp_flags, ~(MPART_F_CHANGED | MPART_F_MAYBE_BLK_INIT));
		return result;
	}
	ATOMIC_AND(self->mp_flags, ~(MPART_F_LOCKBIT | MPART_F_CHANGED |
	                             MPART_F_MAYBE_BLK_INIT));
	mpart_deadnodes_reap(self);
	return result;
done_noop:
	if (keep_lock)
		return result;
	mpart_lock_release(self);
	return result;
done_noop_nolock:
	if (keep_lock)
		mpart_lock_acquire_and_setcore_unwrite_nodma(self);
	return result;
}

/* Sync changes made to the given mem-part.
 * @return: * : The total # of bytes that were synced.
 * NOTE: The caller is responsible for adding/removing the part to/from
 *       the associated file's list of changed parts! */
PUBLIC NOBLOCK NONNULL((1)) size_t FCALL
mpart_sync(struct mpart *__restrict self) {
	return mpart_sync_impl(self, false);
}

/* Same as `mpart_sync()', but keep on holding onto the lock to `self' */
PUBLIC NOBLOCK NONNULL((1)) size_t FCALL
mpart_lock_acquire_and_setcore_unwrite_sync(struct mpart *__restrict self) {
	return mpart_sync_impl(self, true);
}





#ifndef __INTELLISENSE__
DECL_END

#define DEFINE_mpart_read
#include "mpart-rw.c.inl"
#define DEFINE_mpart_write
#include "mpart-rw.c.inl"
#define DEFINE_mpart_read_p
#include "mpart-rw.c.inl"
#define DEFINE_mpart_write_p
#include "mpart-rw.c.inl"
#define DEFINE_mpart_readv
#include "mpart-rw.c.inl"
#define DEFINE_mpart_writev
#include "mpart-rw.c.inl"
#define DEFINE_mpart_readv_p
#include "mpart-rw.c.inl"
#define DEFINE_mpart_writev_p
#include "mpart-rw.c.inl"

DECL_BEGIN
#endif /* !__INTELLISENSE__ */




/* Lock for `mpart_all_list' */
PUBLIC struct atomic_lock mpart_all_lock = ATOMIC_LOCK_INIT;

/* [0..n][CHAIN(mp_allparts)][lock(mpart_all_lock)]
 * List of all memory parts currently in use. List head indices are `MPART_ALL_LIST_*'
 * NOTE: This list holds a reference to every contain part that wasn't already
 *       destroyed, and doesn't have the `MPART_F_NO_GLOBAL_REF' flag set. */
PUBLIC struct mpart_list mpart_all_list = LIST_HEAD_INITIALIZER(mpart_all_list);

/* [0..n][CHAIN(_mp_dead)][lock(ATOMIC)]
 * List of dead parts that have yet to be removed from lists in `mpart_all_list'.
 * This list must be cleared whenever the caller has released a lock to `mpart_all_lock'.
 * For this purpose, you may simply use `mpart_all_reap()' */
PUBLIC struct mpart_slist mpart_all_dead = SLIST_HEAD_INITIALIZER(mpart_all_dead);

/* [0..n][CHAIN(_mp_newglobl)][lock(ATOMIC)]
 * Similar to `mpart_all_dead', but this is a list of references to parts
 * that should be added to `mpart_all_list' once the lock becomes available.
 *
 * Because these are references, mpart_destroy() remains NOBLOCK, because
 * by the time a mem-part is destroyed, it is know that it can't be pending
 * to-be added to the global list of parts anymore. (because it being pending
 * would have otherwise prevented it from being destroyed) */
PUBLIC struct REF mpart_slist mpart_all_pending = SLIST_HEAD_INITIALIZER(mpart_all_pending);

/* Try to reap all dead memory-parts from `mpart_all_dead'.
 * This function must be called after releasing a lock from `mpart_all_lock' */
PUBLIC NOBLOCK void NOTHROW(FCALL _mpart_all_reap)(void) {
	struct mpart *parts, *iter;
	REF struct mpart *pending_parts;
again:
	if (!atomic_lock_tryacquire(&mpart_all_lock))
		return;
	parts = SLIST_ATOMIC_CLEAR(&mpart_all_dead);
	for (iter = parts; iter; iter = SLIST_NEXT(iter, _mp_dead)) {
		assert(LIST_ISBOUND(iter, mp_allparts));
		LIST_REMOVE(iter, mp_allparts);
	}
	pending_parts = SLIST_ATOMIC_CLEAR(&mpart_all_pending);
	while (pending_parts) {
		struct mpart *next;
		next = SLIST_NEXT(pending_parts, _mp_dead);
		LIST_INSERT_HEAD(&mpart_all_list, pending_parts, mp_allparts);
		decref_unlikely(pending_parts); /* The reference inherited from `mpart_all_pending' */
		pending_parts = next;
	}
	atomic_lock_release(&mpart_all_lock);
	while (parts) {
		struct mpart *next;
		next = SLIST_NEXT(parts, _mp_dead);
		mpart_free(parts);
		parts = next;
	}
	if (mpart_all_mustreap())
		goto again;
}


/* Add the given mpart `self' to the global list of parts. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_all_list_insert)(struct mpart *__restrict self) {
	if (mpart_all_lock_tryacquire()) {
		/* Directly insert into the global part list. */
		LIST_INSERT_HEAD(&mpart_all_list, self, mp_allparts);
		mpart_all_lock_release();
	} else {
		/* Enqueue `self' as a pending globally visible part. */
		incref(self); /* This reference is inherited by `mpart_all_pending' */
		SLIST_ATOMIC_INSERT(&mpart_all_pending, self, _mp_newglobl);
		/* Make sure `self' gets added if the lock became
		 * available in the mean time. */
		_mpart_all_reap();
	}
}




DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_C */
