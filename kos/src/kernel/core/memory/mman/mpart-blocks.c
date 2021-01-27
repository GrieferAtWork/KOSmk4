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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_BLOCKS_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_BLOCKS_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/mman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>

#include <kos/except.h>

#include <assert.h>
#include <inttypes.h>
#include <string.h>

DECL_BEGIN

/* Load the bounds of the longest consecutive physical memory address range
 * that starts at `partrel_offset', has been populated with meaningful data
 * and contains at least 1 byte (and at most `num_bytes' bytes).
 * Note that `result->mppl_size < num_bytes' for multiple reasons:
 *   - The end of the given mem-part `self' is reached
 *   - Backing physical memory of `self' is scattered, and the next
 *     byte is apart of the next (discontinuous) chunk of memory.
 *   - The next block located at the end of the returned range isn't
 *     already loaded in-core. (that is: doesn't have a state that
 *     was set to `MPART_BLOCK_ST_LOAD' or `MPART_BLOCK_ST_CHNG')
 *
 * NOTE: The caller must be holding a lock to `self'
 * NOTE: The caller is responsible to ensure that `MPART_ST_INMEM(self->mp_state)'
 *       before calling this function. 
 * NOTE: If necessary, the length of the returned range may be truncated in
 *       order to accommodate the requirements on the state of contained blocks.
 *
 * @return: MPART_MEMADDR_SUCCESS:    Success
 * @return: MPART_MEMADDR_NOT_LOADED: Error: At least one accessed block has a state that
 *                                           is `MPART_BLOCK_ST_NDEF' or `MPART_BLOCK_ST_INIT'
 * @return: MPART_MEMADDR_BAD_BOUNDS: Error: `partrel_offset >= mpart_getsize(self)' */
PUBLIC NOBLOCK NONNULL((1)) unsigned int
NOTHROW(FCALL mpart_memaddr_for_read)(struct mpart *__restrict self,
                                      mpart_reladdr_t partrel_offset, size_t num_bytes,
                                      struct mpart_physloc *__restrict result) {
	/* Check for special case: Our part doesn't contain `partrel_offset' */
	if unlikely(partrel_offset >= mpart_getsize(self))
		goto err_bad_bounds;

	/* Calculate the largest, continuous physical
	 * address range starting at `partrel_offset' */
	mpart_memaddr_direct(self, partrel_offset, result);

	/* Limit the to-be returned range by `num_bytes' */
	if (result->mppl_size > num_bytes)
		result->mppl_size = num_bytes;

	/* Check the state of blocks that overlap with the result range. */
	if unlikely(!mpart_hasblockstate(self)) {
		/* Simple (but rather unlikely) case: All blocks are known to be CHNG */
	} else {
		struct mfile *file = self->mp_file;
		size_t i, min, max;
		min = (partrel_offset) >> file->mf_blockshift;
		max = (partrel_offset + result->mppl_size - 1) >> file->mf_blockshift;
		/* Iterate over blocks within the result range,
		 * and ensure that they've all been initialized. */
		for (i = min; i <= max; ++i) {
			unsigned int st;
			st = mpart_getblockstate(self, i);
			if (st == MPART_BLOCK_ST_NDEF || st == MPART_BLOCK_ST_INIT)
				goto err_not_loaded;
		}
	}
	return MPART_MEMADDR_SUCCESS;
err_not_loaded:
	return MPART_MEMADDR_NOT_LOADED;
err_bad_bounds:
	return MPART_MEMADDR_BAD_BOUNDS;
}



/* Same as `mpart_memaddr()', but have a looser requirement in regards to
 * the current state of blocks that are entirely contained within the to-
 * be returned address range.
 *
 * While `mpart_memaddr_for_read()' requires that all blocks that overlap
 * with the returned range have a state of are either `MPART_BLOCK_ST_LOAD'
 * or `MPART_BLOCK_ST_CHNG', this function only requires this for the 0-2
 * blocks that only partially overlap with the returned range.
 *
 * All of the blocks that fully overlap with the returned range are only
 * required to not have a state set to `MPART_BLOCK_ST_INIT'.
 *
 * @return: MPART_MEMADDR_SUCCESS:    Success
 * @return: MPART_MEMADDR_NOT_LOADED: Error: At least one fully accessed block has a state
 *                                           that is `MPART_BLOCK_ST_INIT', or at least one
 *                                           of the 0-2 border blocks has a state that is one
 *                                           of `MPART_BLOCK_ST_INIT', or `MPART_BLOCK_ST_NDEF'
 * @return: MPART_MEMADDR_BAD_BOUNDS: Error: `partrel_offset >= mpart_getsize(self)' */
PUBLIC NOBLOCK NONNULL((1)) unsigned int
NOTHROW(FCALL mpart_memaddr_for_write)(struct mpart *__restrict self,
                                       mpart_reladdr_t partrel_offset, size_t num_bytes,
                                       struct mpart_physloc *__restrict result) {
	/* Check for special case: Our part doesn't contain `partrel_offset' */
	if unlikely(partrel_offset >= mpart_getsize(self))
		goto err_bad_bounds;

	/* Calculate the largest, continuous physical
	 * address range starting at `partrel_offset' */
	mpart_memaddr_direct(self, partrel_offset, result);

	/* Limit the to-be returned range by `num_bytes' */
	if (result->mppl_size > num_bytes)
		result->mppl_size = num_bytes;

	/* Check the state of blocks that overlap with the result range. */
	if unlikely(!mpart_hasblockstate(self)) {
		/* Simple (but rather unlikely) case: All blocks are known to be CHNG */
	} else {
		struct mfile *file = self->mp_file;
		size_t i, min, max, block_mask;
		unsigned int st;
		block_mask = (1 << file->mf_blockshift) - 1;
		min        = (partrel_offset) >> file->mf_blockshift;
		max        = (partrel_offset + result->mppl_size - 1) >> file->mf_blockshift;
		if ((partrel_offset & block_mask) != 0) {
			/* Starting address isn't block-aligned.
			 * -> This means that the first (leading) block must be fully initialized. */
			st = mpart_getblockstate(self, min);
			if (st == MPART_BLOCK_ST_NDEF || st == MPART_BLOCK_ST_INIT)
				goto err_not_loaded;
			++min;
		}
		if (((partrel_offset + result->mppl_size) & block_mask) != 0) {
			/* Ending address isn't block-aligned.
			 * -> This means that the last (trailing) block must be fully initialized. */
			st = mpart_getblockstate(self, max);
			if (st == MPART_BLOCK_ST_NDEF || st == MPART_BLOCK_ST_INIT)
				goto err_not_loaded;
			--max;
		}
		/* Iterate over whole blocks within the result range,
		 * and ensure that they don't use INIT states.
		 *
		 * Note though that we _do_ allow them to still be
		 * undefined, since they'll just get be overwritten. */
		for (i = min; i <= max; ++i) {
			st = mpart_getblockstate(self, max);
			if (st == MPART_BLOCK_ST_INIT)
				goto err_not_loaded;
		}
	}
	return MPART_MEMADDR_SUCCESS;
err_not_loaded:
	return MPART_MEMADDR_NOT_LOADED;
err_bad_bounds:
	return MPART_MEMADDR_BAD_BOUNDS;
}



/* Commit modifications made to the given backing address range.
 * For this purpose, this function:
 *   - Set the state of all blocks that fully overlap with the given
 *     address range to `MPART_BLOCK_ST_CHNG', (after internally
 *     asserting that their old state wasn't `MPART_BLOCK_ST_INIT')
 *   - Of the 0-2 blocks that only overlap partially with the given
 *     address range, make the following state transitions:
 *      - MPART_BLOCK_ST_LOAD -> MPART_BLOCK_ST_CHNG
 *      - MPART_BLOCK_ST_CHNG -> MPART_BLOCK_ST_CHNG  (i.e. no-op)
 *      - MPART_BLOCK_ST_INIT: Internal assertion failure
 *      - MPART_BLOCK_ST_NDEF:
 *        - If the partially overlapped block isn't the last (iow: right-most)
 *          block (meaning that the given address range partially overlaps
 *          with its beginning), then an internal assertion fails.
 *        - If the partially overlapped block _is_ the last block, then
 *          it's state also remains unaltered, and this function returns
 *          the offset from `partrel_offset' to that block's start.
 *
 * If this function manages change any at least 1 block to `MPART_BLOCK_ST_CHNG'
 * when that block wasn't already marked as such, and if the associated file
 * implements the `mo_saveblocks' operator, then set the MPART_F_CHANGED flag.
 * If that flag wasn't set before, then add a new reference to `self' to the
 * list of changed parts of the associated file.
 *
 * @return: * : The # of successfully committed bytes.
 *              Usually the same as `num_bytes', but see above */
PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL mpart_memaddr_for_write_commit)(struct mpart *__restrict self,
                                              mpart_reladdr_t partrel_offset,
                                              size_t num_bytes) {
	/* Check for special case: Our part doesn't contain `partrel_offset' */
	assert((partrel_offset + num_bytes) <= mpart_getsize(self));

	/* Check the state of blocks that overlap with the result range. */
	if unlikely(!mpart_hasblockstate(self)) {
		/* Simple (but rather unlikely) case: All blocks are already known to be CHNG */
	} else {
		struct mfile *file = self->mp_file;
		size_t i, min, max, block_mask;
		unsigned int st;
		bool did_change;
		block_mask = (1 << file->mf_blockshift) - 1;
		min        = (partrel_offset) >> file->mf_blockshift;
		max        = (partrel_offset + num_bytes - 1) >> file->mf_blockshift;
		did_change = false;
		if ((partrel_offset & block_mask) != 0) {
			/* Starting address isn't block-aligned.
			 * -> This means that the first (leading) block must be fully initialized. */
			st = mpart_getblockstate(self, min);
			assert(st == MPART_BLOCK_ST_LOAD || st == MPART_BLOCK_ST_CHNG);
			if (st == MPART_BLOCK_ST_LOAD) {
				mpart_setblockstate(self, min, MPART_BLOCK_ST_CHNG);
				did_change = true;
			}
			++min;
		}
		if (((partrel_offset + num_bytes) & block_mask) != 0) {
			/* Ending address isn't block-aligned.
			 * -> This means that the last (trailing) block must be fully initialized. */
			st = mpart_getblockstate(self, max);
			assert(st == MPART_BLOCK_ST_NDEF ||
			       st == MPART_BLOCK_ST_LOAD ||
			       st == MPART_BLOCK_ST_CHNG);
			if (st == MPART_BLOCK_ST_NDEF) {
				size_t new_size;
				/* This can happen if there was a partial write error.
				 * In this case, we must return the # of bytes leading
				 * up to the final block that couldn't be fully written, but
				 * continue to leave that last (now partially initialized)
				 * trailing block as undefined within the bitset. */
				new_size = (max << file->mf_blockshift) - partrel_offset;
				assertf(new_size < num_bytes,
				        "new_size:  %" PRIuSIZ "\n"
				        "num_bytes: %" PRIuSIZ,
				        new_size, num_bytes);
				num_bytes = new_size;
			} else if (st == MPART_BLOCK_ST_LOAD) {
				/* Mark the last (trailing) block as changed. */
				mpart_setblockstate(self, max, MPART_BLOCK_ST_CHNG);
				did_change = true;
			}
			--max;
		}

		/* Iterate over whole blocks within the result range,
		 * and ensure that they don't use INIT states.
		 *
		 * Note though that we _do_ allow them to still be
		 * undefined, since they've been fully written to. */
		for (i = min; i <= max; ++i) {
			st = mpart_getblockstate(self, max);
			assert(st == MPART_BLOCK_ST_NDEF ||
			       st == MPART_BLOCK_ST_LOAD ||
			       st == MPART_BLOCK_ST_CHNG);
			if (st != MPART_BLOCK_ST_CHNG) {
				mpart_setblockstate(self, max, MPART_BLOCK_ST_CHNG);
				did_change = true;
			}
		}

		/* If we did manage to set at least 1 block to changed that
		 * wasn't set as such before, then we must mark this mem-part
		 * as having changed, and possibly add it to the associated
		 * file's list of changed parts. */
		if (did_change && file->mf_ops->mo_saveblocks != NULL &&
		    !mfile_isanon(file) && (self->mp_flags & MPART_F_CHANGED) == 0) {

			/* Mark the part as changed. */
			ATOMIC_OR(self->mp_flags, MPART_F_CHANGED);

			/* Add the part to its file's changed-list. */
			SLIST_ATOMIC_INSERT(&file->mf_changed, self, mp_changed);

			/* If defined, invoke the part-changed callback. */
			if (file->mf_ops->mo_changed != NULL)
				(*file->mf_ops->mo_changed)(file, self);
		}
	}
	return num_bytes;
}



/* Whilst inheriting a lock to `self' from the caller (which is _always_
 * released before this function returns), make sure that the first byte
 * pointed to `partrel_offset' has been loaded for reading (that is: the
 * the containing block has transitioned to one of `MPART_BLOCK_ST_LOAD'
 * or `MPART_BLOCK_ST_CHNG')
 * The given `loc->mppl_size' is a hint as to how many consecutive blocks
 * this function should attempt to load, though it will only ever load a
 * single cluster of consecutive blocks that starts with an uninitialized
 * block containing `partrel_offset' */
PUBLIC NONNULL((1, 3)) void FCALL
mpart_memload_and_unlock(struct mpart *__restrict self,
                         mpart_reladdr_t partrel_offset,
                         struct mpart_physloc const *__restrict loc)
		THROWS(E_WOULDBLOCK, ...) {
	struct mfile *file;
	size_t i, min, max, limit, block_size;
	unsigned int st;
	physaddr_t min_addr;
	assert(partrel_offset < mpart_getsize(self));
	assert(mpart_hasblockstate(self));
	file = self->mp_file;
	min  = partrel_offset >> file->mf_blockshift;

	/* Check the status of the first part (the one pointed-to by `min'). */
	st = mpart_getblockstate(self, min);
	assert(st == MPART_BLOCK_ST_INIT ||
	       st == MPART_BLOCK_ST_NDEF);
	if (st == MPART_BLOCK_ST_INIT) {
		/* Special case: We must wait for someone else to finish initialization! */
		incref(file);
		mpart_lock_release(self);
		{
			FINALLY_DECREF_UNLIKELY(file);
			task_connect(&file->mf_initdone);
		}
		if unlikely(!(ATOMIC_READ(self->mp_flags) & MPART_F_MAYBE_BLK_INIT)) {
			task_disconnectall();
		} else {
			task_waitfor();
		}
		/* Return to the caller, since we've lost the lock to `self' */
		return;
	}
	/* Set the initial part's state to INIT */
	mpart_setblockstate(self, min, MPART_BLOCK_ST_INIT);

	/* Try to load more than a single block at once! */
	limit = (partrel_offset + loc->mppl_size - 1) >> file->mf_blockshift;
	assert(limit >= min);
	max = min;
	while (max < limit) {
		st = mpart_getblockstate(self, max + 1);
		if (st != MPART_BLOCK_ST_NDEF)
			break; /* Can't load this one for whatever reason... */
		mpart_setblockstate(self, max + 1, MPART_BLOCK_ST_INIT);
		++max;
	}

	/* Set the flag to indicate that there may be INIT-blocks. */
	ATOMIC_OR(self->mp_flags, MPART_F_MAYBE_BLK_INIT);

	assert(max >= min);
	assert(max <= limit);

	/* With INIT now set for all of the parts in min...max,
	 * we can proceed to actually do the initialization now! */
	incref(file);
	mpart_lock_release(self);

	/* Calculate the actual physical address of the first byte
	 * of the block referenced by `min' */
	block_size = (size_t)1 << file->mf_blockshift;
	min_addr   = loc->mppl_addr - (partrel_offset & (block_size - 1));
	assert(IS_ALIGNED(min_addr, MIN(block_size, PAGESIZE)));

	/* Actually load blocks. */
	TRY {
		if likely(file->mf_ops->mo_loadblocks != NULL) {
			(*file->mf_ops->mo_loadblocks)(file, (self->mp_minaddr >> file->mf_blockshift) + min,
			                               min_addr, (max - min) + 1);
		}
	} EXCEPT {
		/* Change back all INIT-parts to UNDEF */
		for (i = min; i <= max; ++i)
			mpart_setblockstate(self, i, MPART_BLOCK_ST_NDEF);
		sig_broadcast(&file->mf_initdone);
		decref_unlikely(file);
		RETHROW();
	}
	/* Mark all INIT-pages as loaded. */
	for (i = min; i <= max; ++i)
		mpart_setblockstate(self, i, MPART_BLOCK_ST_LOAD);

	/* Broadcast that init has finished. */
	sig_broadcast(&file->mf_initdone);

	decref_unlikely(file);
}



/* Directly return physical backing memory containing the byte `partrel_offset',
 * without looking at the associated block-state at all. The caller is responsible
 * to ensure that `MPART_ST_INMEM(self->mp_state)' before calling this function.
 * NOTE: The caller must be holding a lock to `self' (which is allowed to be a DMA lock)
 * NOTE: This function may also assume that at least the first byte (that
 *       is: the byte described by `partrel_offset') is in-bounds of the
 *       given mem-part `self' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_memaddr_direct)(struct mpart *__restrict self,
                                    mpart_reladdr_t partrel_offset,
                                    struct mpart_physloc *__restrict result) {
	assert(partrel_offset < mpart_getsize(self));
	if (self->mp_state == MPART_ST_MEM) {
		/* Simple case: Everything is linear physical memory. */
		result->mppl_addr = physpage2addr(self->mp_mem.mc_start) + partrel_offset;
		result->mppl_size = (self->mp_mem.mc_size * PAGESIZE) - partrel_offset;
	} else {
		size_t i, chunk_size;
		assert(self->mp_state == MPART_ST_MEM_SC);
		/* Difficult case: Must find the chunk containing the given offset. */
		for (i = 0;;) {
			assert(i < self->mp_mem_sc.ms_c);
			chunk_size = self->mp_mem_sc.ms_v[i].mc_size * PAGESIZE;
			if (partrel_offset < chunk_size)
				break;
			partrel_offset -= chunk_size;
			++i;
		}
		result->mppl_addr = physpage2addr(self->mp_mem_sc.ms_v[i].mc_start) + partrel_offset;
		result->mppl_size = chunk_size - partrel_offset;
	}
}



/* Mark all blocks that overlap with the given address range as CHNG.
 * For this purpose, the caller must ensure that:
 * >> !OVERFLOW_UADD(partrel_offset, num_bytes, &endaddr) && endaddr <= mpart_getsize(self)
 * If any of the blocks within the given range had yet to be marked as CHNG,
 * and the associated file is not anonymous, and implements the `mo_saveblocks'
 * operator, and the `MPART_F_CHANGED' flag had yet to be set for the given part,
 * then set the `MPART_F_CHANGED' flag and add `self' to the list of changed
 * parts of its associated file.
 * NOTE: The caller must be holding a lock to `self' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_changed)(struct mpart *__restrict self,
                             mpart_reladdr_t partrel_offset,
                             size_t num_bytes) {
	size_t i, blocks_start, blocks_end;
	unsigned int shift;
	struct mfile *file;
	bool did_change;
	assert(mpart_lock_acquired(self));
	assert(partrel_offset + num_bytes >= partrel_offset);
	assert(partrel_offset + num_bytes <= mpart_getsize(self));
	if (!mpart_hasblockstate(self))
		return; /* All parts are already set to CHNG */
	file         = self->mp_file;
	shift        = file->mf_blockshift;
	blocks_start = partrel_offset >> shift;
	blocks_end   = ((partrel_offset + num_bytes - 1) >> shift) + 1;
	did_change   = false;
	for (i = blocks_start; i < blocks_end; ++i) {
		unsigned int st;
		st = mpart_getblockstate(self, i);
		if (st != MPART_BLOCK_ST_CHNG) {
			mpart_setblockstate(self, i, MPART_BLOCK_ST_CHNG);
			did_change = true;
		}
	}

	/* If we did manage to set at least 1 block to changed that
	 * wasn't set as such before, then we must mark this mem-part
	 * as having changed, and possibly add it to the associated
	 * file's list of changed parts. */
	if (did_change && file->mf_ops->mo_saveblocks != NULL &&
	    !mfile_isanon(file) && (self->mp_flags & MPART_F_CHANGED) == 0) {

		/* Mark the part as changed. */
		ATOMIC_OR(self->mp_flags, MPART_F_CHANGED);

		/* Add the part to its file's changed-list. */
		SLIST_ATOMIC_INSERT(&file->mf_changed, self, mp_changed);

		/* If defined, invoke the part-changed callback. */
		if (file->mf_ops->mo_changed != NULL)
			(*file->mf_ops->mo_changed)(file, self);
	}
}


PRIVATE NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL mpart_atomic_cmpxch_blockstate)(struct mpart *__restrict self,
                                              size_t partrel_block_index,
                                              unsigned int old_st,
                                              unsigned int new_st) {
	mpart_blkst_word_t *pword, mask, oldword, newword;
	mpart_blkst_word_t old_val, new_val;
	unsigned int shift;
	assert(old_st < ((unsigned int)1 << MPART_BLOCK_STBITS));
	assert(new_st < ((unsigned int)1 << MPART_BLOCK_STBITS));
	shift   = (unsigned int)((partrel_block_index % MPART_BLKST_BLOCKS_PER_WORD) * MPART_BLOCK_STBITS);
	mask    = (mpart_blkst_word_t)((1 << MPART_BLOCK_STBITS) - 1) << shift;
	old_val = (mpart_blkst_word_t)old_st << shift;
	new_val = (mpart_blkst_word_t)new_st << shift;
	if (self->mp_flags & MPART_F_BLKST_INL) {
		pword = &self->mp_blkst_inl;
	} else {
		size_t index;
		assert(self->mp_blkst_ptr);
		index = partrel_block_index / MPART_BLKST_BLOCKS_PER_WORD;
		pword = &self->mp_blkst_ptr[index];
	}
	do {
		oldword = ATOMIC_READ(*pword);
		if ((oldword & mask) != old_val)
			return false;
		newword = (oldword & ~mask) | new_val;
	} while (!ATOMIC_CMPXCH_WEAK(*pword, oldword, newword));
	return true;
}

/* For use with `MNODE_F_MHINT':
 *  - Ensure that the pages (== block) at the given `offset'
 *    has been marked as `MPART_BLOCK_ST_CHNG', invoking the
 *    block loader from the associated file if necessary.
 *  - Afterwards, map the associated page to `addr' within
 *    the current page directory, using `perm'.
 * This function is used to implement handling of hinted
 * mem-nodes when encountered by the #PF handler. */
PUBLIC NOPREEMPT NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_hinted_mmap)(struct mpart *__restrict self,
                                 PAGEDIR_PAGEALIGNED void *addr,
                                 PAGEDIR_PAGEALIGNED mpart_reladdr_t offset,
                                 u16 perm) {
	unsigned int st;
	struct mpart_physloc pl;
	size_t block_index;

	/* Some hinted-node-related assertions that we can make
	 * without the need of knowing the accessing mem-node. */
	assert(!PREEMPTION_ENABLED());
	assert(self->mp_file != NULL);
	assert(ADDR_ISKERN(self->mp_file));
	assert(self->mp_file->mf_blockshift == PAGESHIFT);
	assert(self->mp_file->mf_parts == MFILE_PARTS_ANONYMOUS);
	assert(MPART_ST_INMEM(self->mp_state));

	/* Index of the block (aka. page) that is being accessed.
	 * Note the `self->mp_file->mf_blockshift == PAGESHIFT'
	 * assert above, so we know that 1 block equals 1 page! */
	block_index = offset >> PAGESHIFT;

	/* Load the physical location of the accessed page. */
	mpart_memaddr_direct(self, offset, &pl);

	/* Ensure that the accessed block is set to `MPART_BLOCK_ST_CHNG' */
#ifndef CONFIG_NO_SMP
again_read_st:
#endif /* !CONFIG_NO_SMP */
	st = mpart_getblockstate(self, block_index);
	if (st != MPART_BLOCK_ST_CHNG) {
#ifdef CONFIG_NO_SMP
		assert(st != MPART_BLOCK_ST_INIT);
#else /* CONFIG_NO_SMP */
		/* When another CPU is currently initializing this same page,
		 * then we must wait for it to finish doing so before we can
		 * proceed. */
		if (st == MPART_BLOCK_ST_INIT) {
			/* Another CPU is currently doing the INIT */
			task_pause();
			goto again_read_st;
		}

		/* Must lazily initialize this block!
		 * For this purpose, we must disable preemption, since being
		 * interrupted during the init, and having another thread then
		 * attempt to access the same page that we're trying to init
		 * would result in a dead-lock, where it will just keep on
		 * seeing `MPART_BLOCK_ST_INIT' for all of eternity... */
		if (!mpart_atomic_cmpxch_blockstate(self, block_index, st,
		                                    MPART_BLOCK_ST_INIT)) {
			/* Someone else was faster... -> Just re-read the status! */
			goto again_read_st;
		}
#endif /* !CONFIG_NO_SMP */

		if (st == MPART_BLOCK_ST_NDEF) {
			auto mo_loadblocks = self->mp_file->mf_ops->mo_loadblocks;
			if likely(mo_loadblocks != NULL) {
				/* NOTE: We're allowed to assume that this call is NOBLOCK+NOTHROW! */
				(*mo_loadblocks)(self->mp_file,
				                 (mfile_block_t)((mpart_getminaddr(self) >>
				                                  PAGESHIFT) +
				                                 block_index),
				                 pl.mppl_addr, 1);
			}
		}

		/* And with that, the init is done. -> Mark the block as CHNG.
		 * Also note that we don't have to deal with `MPART_F_MAYBE_BLK_INIT'
		 * or `self->mp_file->mf_initdone'. - None of those matter for hinted
		 * memory nodes! */
		mpart_setblockstate(self, block_index, MPART_BLOCK_ST_CHNG);
	}

	/* At this point, we know that the accessed page has surely been
	 * initialized, so we are safe to map it into the current page directory.
	 * Also: We don't have to worry about preparing the page directory here.
	 *       Hinted nodes require that the `MNODE_F_MPREPARED' flag be set,
	 *       meaning that we're allowed to assume that the page directory
	 *       is, and always has been, prepared. */
	pagedir_mapone(addr, pl.mppl_addr, perm);

	/* Because we got here as the result of a #PF, we don't even have to
	 * sync anything since all that our mapone() call did, was expand the
	 * set of available permissions, which the MMU will lazily pick up on
	 * all by itself. */
}

/* Convenience wrapper for `mpart_hinted_mmap()' */
PUBLIC NOPREEMPT NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mnode_hinted_mmap)(struct mnode *__restrict self,
                                 PAGEDIR_PAGEALIGNED void *fault_page) {
	struct mpart *part;

	/* Assert all of the invariants associated with hinted nodes. */
	assert(ADDR_ISKERN(self));
	assert(ADDRRANGE_ISKERN(mnode_getaddr(self),
	                        mnode_getendaddr(self)));
	assert(self->mn_flags & MNODE_F_MHINT);
	assert(self->mn_mman == &mman_kernel);
	part = self->mn_part;
	assert(part != NULL);
	assert(ADDR_ISKERN(part));
	assert(self->mn_link.le_prev ==
	       ((self->mn_flags & MNODE_F_SHARED)
	        ? &part->mp_share.lh_first
	        : &part->mp_copy.lh_first));
	assert(*self->mn_link.le_prev == self);
	assert(self->mn_link.le_next == NULL);
	assert((self->mn_flags & MNODE_F_SHARED) ? LIST_EMPTY(&part->mp_copy)
	                                         : LIST_EMPTY(&part->mp_share));

	/* Call forward to the mem-part-level hint handler. */
	mpart_hinted_mmap(part, fault_page,
	                  self->mn_partoff +
	                  (mpart_reladdr_t)((uintptr_t)fault_page -
	                                    (uintptr_t)mnode_getminaddr(self)),
	                  mnode_getperm_kernel(self));
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_BLOCKS_C */
