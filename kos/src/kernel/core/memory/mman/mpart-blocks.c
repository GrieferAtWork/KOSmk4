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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_BLOCKS_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_BLOCKS_C 1
#define __WANT_MPART__mp_nodlsts /* mpart_getnodlst_from_mnodeflags() */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/aio.h>
#include <kernel/fs/notify.h>
#include <kernel/mman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/phys.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>

#include <kos/except.h>

#include <assert.h>
#include <inttypes.h>
#include <string.h>

DECL_BEGIN

/* Mask of block status bitset bits. */
#define MPART_BLOCK_ST_MASK (((mpart_blkst_word_t)1 << MPART_BLOCK_STBITS) - 1)
STATIC_ASSERT((MPART_BLOCK_ST_NDEF & MPART_BLOCK_ST_MASK) == MPART_BLOCK_ST_NDEF);
STATIC_ASSERT((MPART_BLOCK_ST_INIT & MPART_BLOCK_ST_MASK) == MPART_BLOCK_ST_INIT);
STATIC_ASSERT((MPART_BLOCK_ST_LOAD & MPART_BLOCK_ST_MASK) == MPART_BLOCK_ST_LOAD);
STATIC_ASSERT((MPART_BLOCK_ST_CHNG & MPART_BLOCK_ST_MASK) == MPART_BLOCK_ST_CHNG);


/* Helper wrapper for invocation of `mfile_ops::mo_loadblocks' and `mfile_ops::mo_saveblocks'
 * within  a synchronous context. This function will invoke `io' with a locally allocated AIO
 * handle before proceeding to wait for I/O to complete.
 *
 * If the calling thread is interrupted during  waiting, I/O is canceled and the  function
 * returned with an exception. Otherwise, the function returns normally once I/O completed
 * successfully. In the event of an I/O error, this function will re-throw said error. */
PUBLIC BLOCKING NONNULL((1, 2)) void KCALL
mfile_dosyncio(struct mfile *__restrict self,
               NONNULL((1, 5)) void (KCALL *io)(struct mfile *__restrict self, pos_t addr,
                                                physaddr_t buf, size_t num_bytes,
                                                struct aio_multihandle *__restrict aio),
               pos_t addr, physaddr_t buf, size_t num_bytes) {
	struct aio_multihandle_generic hand;
	aio_multihandle_generic_init(&hand);
	TRY {
		(*io)(self, addr, buf, num_bytes, &hand);
		aio_multihandle_done(&hand);
	} EXCEPT {
		aio_multihandle_fail(&hand);
	}
	RAII_FINALLY { aio_multihandle_generic_fini(&hand); };
	aio_multihandle_generic_waitfor(&hand);
	aio_multihandle_generic_checkerror(&hand);
}




/* Return  the # of pages containing MPART_BLOCK_ST_CHNG-
 * blocks that can be found within `[0,partrel_pageaddr)'
 *
 * This function should be used to convert from part-rel
 * offsets  into in-swap-data offsets when `self's state
 * indicates that the part is currently located in swap. */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) physpagecnt_t
NOTHROW(FCALL mpart_page2swap)(struct mpart const *__restrict self,
                               physpagecnt_t partrel_pageaddr) {
	physpagecnt_t result;
	mpart_blkst_word_t word, *bitset;
	shift_t shift;
	assert(((size_t)partrel_pageaddr << PAGESHIFT) <= mpart_getsize(self));
	shift = self->mp_file->mf_blockshift;
	if (self->mp_flags & MPART_F_BLKST_INL) {
		/* Special case: inline bitset. */
		word   = self->mp_blkst_inl;
		result = 0;
account_trailing_word:
#ifndef __OPTIMIZE_SIZE__
		if likely(shift == PAGESHIFT) {
			/* Simple case: 1 block === 1 page
			 * iow: count the # of ST_CHNG pages. */
			while (partrel_pageaddr) {
				if ((word & MPART_BLOCK_ST_MASK) == MPART_BLOCK_ST_CHNG)
					++result;
				--partrel_pageaddr;
				word >>= MPART_BLOCK_STBITS;
			}
		} else if (shift > PAGESHIFT)
#else /* !__OPTIMIZE_SIZE__ */
		if (shift >= PAGESHIFT)
#endif /* __OPTIMIZE_SIZE__ */
		{
			/* Blocks are larger than pages (must # multiple pages per block) */
			physpagecnt_t pages_per_block;
			pages_per_block = (physpagecnt_t)1 << (shift - PAGESHIFT);
			while (partrel_pageaddr) {
				physpagecnt_t part;
				part = pages_per_block;
				if (part > partrel_pageaddr)
					part = partrel_pageaddr;
				if ((word & MPART_BLOCK_ST_MASK) == MPART_BLOCK_ST_CHNG)
					result += part;
				partrel_pageaddr -= part;
				word >>= MPART_BLOCK_STBITS;
			}
		} else {
			/* Blocks are smaller than pages (must check multiple blocks for changes) */
			physpagecnt_t blocks_per_page;
			blocks_per_page = (physpagecnt_t)1 << (PAGESHIFT - shift);
			while (partrel_pageaddr) {
				physpagecnt_t i;
				bool found = false;
				for (i = 0; i < blocks_per_page; ++i) {
					if ((word & MPART_BLOCK_ST_MASK) == MPART_BLOCK_ST_CHNG)
						found = true;
					word >>= MPART_BLOCK_STBITS;
				}
				if (found)
					++result;
				--partrel_pageaddr;
			}
		}
	} else if ((bitset = self->mp_blkst_ptr) == NULL) {
		/* Simple case: When the blkst-bitset is NULL, then all blocks
		 *              should  be considered to  be CHANGED, so there
		 *              is no conversion required. */
		result = partrel_pageaddr;
	} else {
		/* Difficult case: Must possibly account for multiple words. */
		size_t num_blocks, num_words;
		result     = 0;
		num_blocks = ((size_t)partrel_pageaddr << PAGESHIFT) >> shift;
		num_words  = num_blocks / MPART_BLKST_BLOCKS_PER_WORD;
		if (num_words != 0) {
			if (shift >= PAGESHIFT) {
				size_t i;
				/* Large blocks. -> Every changed block describes at least
				 * 1 change page. - As such,  first count the # of  change
				 * blocks,  which we can then simply convert into the # of
				 * changed pages. */
				for (i = 0; i < num_words; ++i) {
					word = bitset[i];
					while (word) {
						if ((word & MPART_BLOCK_ST_MASK) == MPART_BLOCK_ST_CHNG)
							++result;
						word >>= MPART_BLOCK_STBITS;
					}
				}
				/* Convert the # of changed blocks into the # of changed pages */
				result <<= (shift - PAGESHIFT);
			} else {
				/* Small blocks. -> For every page, there are multiple blocks
				 * that may be marked as changed, and if at least one of them
				 * is  actually marked as such, then the whole page should be
				 * considered as changed, too.
				 * This gets more complicated  when you consider that  blocks
				 * belonging to a single page don't necessarily have to align
				 * by whole bitset words, either.
				 * As such, we handle this case separately. */
				physpagecnt_t i, blocks_per_page;
				shift_t page2block_shift;
				page2block_shift = PAGESHIFT - shift;
				blocks_per_page  = (physpagecnt_t)1 << page2block_shift;
				for (i = 0; i < partrel_pageaddr; ++i) {
					size_t j, count;
					/* Check if any block at one of these indices is CHNG:
					 *    [i << page2block_shift, (i+1) << page2block_shift) */
					j     = i << page2block_shift;
					count = blocks_per_page;
					do {
						word = bitset[j / MPART_BLKST_BLOCKS_PER_WORD];
						word >>= (j % MPART_BLKST_BLOCKS_PER_WORD) * MPART_BLOCK_STBITS;
						if ((word & MPART_BLOCK_ST_MASK) == MPART_BLOCK_ST_CHNG) {
							/* Found a CHNG block within the range bound to this page! */
							++result;
							break;
						}
						++j;
					} while (--count);
				}
				return result;
			}
			/* Figure out how many pages are still described by the trailing word. */
			{
				size_t checked_blocks, checked_bytes, checked_pages;
				checked_blocks = num_words * MPART_BLKST_BLOCKS_PER_WORD;
				checked_bytes  = checked_blocks << shift;
				checked_pages  = checked_bytes >> PAGESHIFT;
				assertf(partrel_pageaddr >= checked_pages,
				        "partrel_pageaddr = %" PRIuSIZ "\n"
				        "checked_pages    = %" PRIuSIZ,
				        partrel_pageaddr, checked_pages);
				partrel_pageaddr -= checked_pages;
			}
		}
		if (partrel_pageaddr) {
			word = bitset[num_words];
			goto account_trailing_word;
		}
	}
	return result;
}



/* Load  the bounds of the longest consecutive physical memory address range
 * that starts at `partrel_offset', has been populated with meaningful data,
 * and contains at least 1 byte (and at most `num_bytes' bytes).
 *
 * Note that `result->mppl_size < num_bytes' for multiple reasons:
 *  - The end of the given mem-part `self' is reached
 *  - Backing physical memory of `self' is scattered, and the next
 *    byte is apart of the  next (discontinuous) chunk of  memory.
 *  - The next block located at the end of the returned range isn't
 *    already loaded in-core. (that is:  doesn't have a state  that
 *    was set to `MPART_BLOCK_ST_LOAD' or `MPART_BLOCK_ST_CHNG')
 *
 * NOTE: The caller must be holding a lock to `self'
 * NOTE: The caller is responsible to ensure that `MPART_ST_INMEM(self->mp_state)'
 *       before calling this function.
 * NOTE: If necessary, the  length of  the returned  range may  be truncated  in
 *       order to accommodate the requirements on the state of contained blocks.
 *
 * @return: true:  Success
 * @return: false: Error: At least  one accessed  block  has a  state  that
 *                        is `MPART_BLOCK_ST_NDEF' or `MPART_BLOCK_ST_INIT' */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL mpart_memaddr_for_read)(struct mpart *__restrict self,
                                      mpart_reladdr_t partrel_offset, size_t num_bytes,
                                      struct mpart_physloc *__restrict result) {
	assert(partrel_offset < mpart_getsize(self));

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
		/* Iterate  over blocks within the result range,
		 * and ensure that they've all been initialized. */
		for (i = min; i <= max; ++i) {
			unsigned int st;
			st = mpart_getblockstate(self, i);
			if (st == MPART_BLOCK_ST_NDEF || st == MPART_BLOCK_ST_INIT) {
				size_t loadend, loadsiz;
				if (i == min)
					goto err_not_loaded;
				loadend = i << file->mf_blockshift;
				assert(loadend > partrel_offset);
				loadsiz = loadend - partrel_offset;
				assert(loadsiz < result->mppl_size);
				result->mppl_size = loadsiz;
				break;
			}
		}
	}
	return true;
err_not_loaded:
	return false;
}



/* Same as `mpart_memaddr()', but have a looser requirement in regards to
 * the current state of blocks that are entirely contained within the to-
 * be returned address range.
 *
 * While `mpart_memaddr_for_read()' requires that all blocks that overlap
 * with the returned range have  a state of either  `MPART_BLOCK_ST_LOAD'
 * or `MPART_BLOCK_ST_CHNG', this function only requires this for the 0-2
 * blocks that only partially overlap with the returned range.
 *
 * All of the blocks that fully overlap with the returned range are
 * only required to not have a state set to  `MPART_BLOCK_ST_INIT'.
 *
 * @return: true:  Success
 * @return: false: Error: At least  one fully  accessed  block has  a  state
 *                        that  is  `MPART_BLOCK_ST_INIT', or  at  least one
 *                        of the 0-2 border blocks  has a state that is  one
 *                        of `MPART_BLOCK_ST_INIT', or `MPART_BLOCK_ST_NDEF' */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL mpart_memaddr_for_write)(struct mpart *__restrict self,
                                       mpart_reladdr_t partrel_offset, size_t num_bytes,
                                       struct mpart_physloc *__restrict result) {
	assert(partrel_offset < mpart_getsize(self));

	/* Calculate the largest, continuous physical
	 * address range starting at `partrel_offset' */
	mpart_memaddr_direct(self, partrel_offset, result);

	/* Limit the to-be returned range by `num_bytes' */
	if (result->mppl_size > num_bytes)
		result->mppl_size = num_bytes;

	/* Check the state of blocks that overlap with the result range. */
	if unlikely(!mpart_hasblockstate(self)) {
		/* Simple (but rather unlikely) case: All blocks are known to be CHNG */
	} else if likely(result->mppl_size != 0) {
		struct mfile *file = self->mp_file;
		size_t i, min, max, block_mask;
		unsigned int st;
		block_mask = mfile_getblockmask(file);
		min        = (partrel_offset) >> file->mf_blockshift;
		max        = (partrel_offset + result->mppl_size - 1) >> file->mf_blockshift;
		if ((partrel_offset & block_mask) != 0) {
			/* Starting address isn't block-aligned.
			 * -> This means that the first (leading) block must be fully initialized. */
			st = mpart_getblockstate(self, min);
			if (st == MPART_BLOCK_ST_NDEF || st == MPART_BLOCK_ST_INIT)
				goto err_not_loaded;
			++min;
			if (((partrel_offset + result->mppl_size) & block_mask) != 0) {
				/* Ending address isn't block-aligned.
				 * -> This means that the last (trailing) block must be fully initialized. */
				st = mpart_getblockstate(self, max);
				if (st == MPART_BLOCK_ST_NDEF || st == MPART_BLOCK_ST_INIT) {
					/* For now, stop writing at the start of the last (NDEF/INIT) block. */
					result->mppl_size = (max << file->mf_blockshift) - partrel_offset;
					assertf(result->mppl_size != 0,
					        "Must be non-empty, because the first couple of bytes "
					        "should be able to access the unaligned tail of `min'");
				}
				if (min >= max)
					goto done; /* Prevent underflow when `max == 0' */
				--max;
			}
		} else if (((partrel_offset + result->mppl_size) & block_mask) != 0) {
			/* Ending address isn't block-aligned.
			 * -> This means that the last (trailing) block must be fully initialized. */
			st = mpart_getblockstate(self, max);
			if (st == MPART_BLOCK_ST_NDEF || st == MPART_BLOCK_ST_INIT) {
				if (min == max) {
					/* Start address may be aligned, but end address
					 * is  apart  of  the  same,  not-loaded  block! */
					goto err_not_loaded;
				}
				/* For now, stop writing at the start of the last (NDEF/INIT) block. */
				result->mppl_size = (max << file->mf_blockshift) - partrel_offset;
				assertf(result->mppl_size != 0,
				        "Must be non-empty, because we've handle `min == max'");
			}
			if (min >= max)
				goto done; /* Prevent underflow when `max == 0' */
			--max;
		}
		/* Iterate over whole blocks within the result range,
		 * and  ensure  that  they  don't  use  INIT  states.
		 *
		 * Note though that we _do_  allow them to still  be
		 * undefined, since they'll just get be overwritten. */
		for (i = min; i <= max; ++i) {
			st = mpart_getblockstate(self, i);
			if (st == MPART_BLOCK_ST_INIT) {
				size_t loadend, loadsiz;
				if (i == min)
					goto err_not_loaded;
				loadend = i << file->mf_blockshift;
				assert(loadend > partrel_offset);
				loadsiz = loadend - partrel_offset;
				assert(loadsiz < result->mppl_size);
				result->mppl_size = loadsiz;
				goto done;
			}
		}
	}
done:
	return true;
err_not_loaded:
	return false;
}



/* Try  to add the given `part' to the list of changed parts of `self'
 * Does nothing when `part' was already marked as changed, or the list
 * of changed parts of `self' has previously been set to ANON. */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mfile_add_changed_part)(struct mfile *__restrict self,
                                      struct mpart *__restrict part) {
	if (self->mf_ops->mo_saveblocks != NULL && !mpart_isanon(part) &&
	    (part->mp_flags & MPART_F_CHANGED) == 0) {
		struct mpart *next;

		/* Mark the part as changed. */
		ATOMIC_OR(part->mp_flags, MPART_F_CHANGED);
		incref(part); /* For the list of changed parts. */

		/* Add the part to its file's changed-list. */
		do {
			next = ATOMIC_READ(self->mf_changed.slh_first);

			/* Deal with special case: The file is currently being made
			 * anonymous. This is  quite unlikely, since  a fully  anon
			 * file will sooner or later also mark all of its parts  as
			 * anonymous,  meaning  that  `mpart_isanon()'  would  have
			 * already failed  had `self'  been anonymous  for a  while
			 * longer. */
			if unlikely(next == MFILE_PARTS_ANONYMOUS) {
				ATOMIC_AND(part->mp_flags, ~MPART_F_CHANGED);
				decref_nokill(part);
				return;
			}
			part->mp_changed.sle_next = next;
			COMPILER_WRITE_BARRIER();
		} while (!ATOMIC_CMPXCH_WEAK(self->mf_changed.slh_first,
		                             next, part));

		/* Mark the file as changed (and update the last-modified timestamp). */
		{
			uintptr_t changes = MFILE_F_CHANGED;
			if (!(self->mf_flags & MFILE_F_NOMTIME)) {
				struct timespec now = realtime();
				mfile_tslock_acquire(self);
				COMPILER_READ_BARRIER();
				if (!(self->mf_flags & (MFILE_F_NOMTIME | MFILE_F_DELETED))) {
					self->mf_mtime = now;
					self->mf_ctime = now;
					changes |= MFILE_F_ATTRCHANGED;
				}
				mfile_tslock_release(self);
			}
			mfile_changed(self, changes);
			mfile_inotify_modified(self); /* Post `IN_MODIFY' */
		}
	}
}



/* Commit modifications made to the given backing address range.
 * For this purpose, this function will:
 *  - Set the state of all blocks that fully overlap with the given
 *    address range  to  `MPART_BLOCK_ST_CHNG',  (after  internally
 *    asserting  that their old state wasn't `MPART_BLOCK_ST_INIT')
 *  - Of the 0-2 blocks that only overlap partially with the given
 *    address  range,  make   the  following  state   transitions:
 *     - MPART_BLOCK_ST_LOAD -> MPART_BLOCK_ST_CHNG
 *     - MPART_BLOCK_ST_CHNG -> MPART_BLOCK_ST_CHNG  (i.e. no-op)
 *     - MPART_BLOCK_ST_INIT: Internal assertion failure
 *     - MPART_BLOCK_ST_NDEF:
 *       - If the partially overlapped block isn't the last (iow: right-most)
 *         block (meaning  that the  given address  range partially  overlaps
 *         with its beginning), then an internal assertion fails.
 *       - If the partially overlapped block _is_ the last block,  then
 *         it's state also remains unaltered, and this function returns
 *         the offset from `partrel_offset' to that block's start.
 *
 * If this function manages change any at least 1 block to `MPART_BLOCK_ST_CHNG'
 * when that block  wasn't already marked  as such, and  if the associated  file
 * implements the `mo_saveblocks' operator,  then set the MPART_F_CHANGED  flag.
 * If  that flag wasn't  set before, then add  a new reference  to `self' to the
 * list of changed parts of the associated file (unless the file's list of parts
 * marked as changed was set to `mf_changed = MFILE_PARTS_ANONYMOUS').
 *
 * @return: * : The   #   of  successfully   committed  bytes.
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
	} else if likely(num_bytes != 0) {
		struct mfile *file = self->mp_file;
		size_t i, min, max, block_mask;
		unsigned int st;
		bool did_change;
		block_mask = mfile_getblockmask(file);
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
				/* This  can  happen if  there  was a  partial  write error.
				 * In  this  case, we  must return  the  # of  bytes leading
				 * up to the final block that couldn't be fully written, but
				 * continue  to leave that  last (now partially initialized)
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
			if (min >= max)
				goto after_intermediate_blocks; /* Prevent underflow when `max == 0' */
			--max;
		}

		/* Iterate over whole blocks within the result range,
		 * and  ensure  that  they  don't  use  INIT  states.
		 *
		 * Note though that we _do_ allow them to still be
		 * undefined, since they've been fully written to. */
		for (i = min; i <= max; ++i) {
			st = mpart_getblockstate(self, i);
			assert(st == MPART_BLOCK_ST_NDEF ||
			       st == MPART_BLOCK_ST_LOAD ||
			       st == MPART_BLOCK_ST_CHNG);
			if (st != MPART_BLOCK_ST_CHNG) {
				mpart_setblockstate(self, i, MPART_BLOCK_ST_CHNG);
				did_change = true;
			}
		}
after_intermediate_blocks:

		/* If  we did manage to set at  least 1 block to changed that
		 * wasn't set as such before, then we must mark this mem-part
		 * as having changed, and possibly  add it to the  associated
		 * file's list of changed parts. */
		if (did_change)
			mfile_add_changed_part(file, self);
	}
	return num_bytes;
}



/* Whilst inheriting a lock to `self' from the caller (which is _always_
 * released before this function returns), make sure that the first byte
 * pointed to `partrel_offset' has been loaded for reading (that is: the
 * containing block has transitioned to one of `MPART_BLOCK_ST_LOAD'  or
 * `MPART_BLOCK_ST_CHNG')
 * The given `loc->mppl_size' is a hint as to how many consecutive blocks
 * this function should attempt to load, though it will only ever load  a
 * single cluster of consecutive blocks that starts with an uninitialized
 * block containing `partrel_offset' */
PUBLIC BLOCKING NONNULL((1, 3)) void FCALL
mpart_memload_and_unlock(struct mpart *__restrict self,
                         mpart_reladdr_t partrel_offset,
                         struct mpart_physloc const *__restrict loc,
                         struct unlockinfo *unlock)
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
	if unlikely(st != MPART_BLOCK_ST_INIT && st != MPART_BLOCK_ST_NDEF) {
		/* Data _is_ available! (this can happen if the caller read
		 * INIT  before, but the block was loaded in the mean time) */
		return;
	}
	if (st == MPART_BLOCK_ST_INIT) {
		bool hasinit;
		/* Special case: We must wait for someone else to finish initialization! */
		incref(file);
		_mpart_lock_release(self);
		unlockinfo_xunlock(unlock);
		mpart_lockops_reap(self);
		{
			FINALLY_DECREF_UNLIKELY(file);
			task_connect(&file->mf_initdone);
		}
		TRY {
			mpart_lock_acquire(self);
		} EXCEPT {
			task_disconnectall();
			RETHROW();
		}
		hasinit = mpart_hasblocksstate_init(self);
		mpart_lock_release(self);
		if unlikely(!hasinit) {
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

	/* With  INIT now set for all of the parts in min...max,
	 * we can proceed to actually do the initialization now! */
	incref(file);

	/* Prevent the file's size from being lowered. */
	mfile_trunclock_inc(file);

	/* Release locks. */
	_mpart_lock_release(self);
	unlockinfo_xunlock(unlock);
	mpart_lockops_reap(self);

	/* Calculate the actual physical address of the first byte
	 * of the block referenced by `min' */
	block_size = mfile_getblocksize(file);
	min_addr   = loc->mppl_addr - (partrel_offset & (block_size - 1));
	assert(IS_ALIGNED(min_addr, MIN(block_size, PAGESIZE)));

	/* Actually load blocks. */
	TRY {
		pos_t addr;
		size_t num_bytes;
		auto mo_loadblocks = file->mf_ops->mo_loadblocks;

		addr      = self->mp_minaddr + (min << file->mf_blockshift);
		num_bytes = ((max - min) + 1) << file->mf_blockshift;

		if (!mfile_isanon(file)) {
			pos_t filesize = mfile_getsize(file);
			if (!OVERFLOW_UADD(filesize, file->mf_part_amask, &filesize)) {
				filesize = mfile_partaddr_flooralign(file, filesize);

				/* NOTE: The file size may increase in the mean time, but that's actually
				 *       ok: We're currently holding exclusive locks to all of the blocks
				 *       that  we're going to initialize next (s.a. MPART_BLOCK_ST_INIT).
				 *       As  such, if  the file's size  increases, _has_ to  include to a
				 *       point above the  region which we're  trying to initialize  here.
				 * e.g.: Someone else is allowed to  write data, say, +0x12000 bytes  further
				 *       into the file, and that would never affect us here. If this happens,
				 *       there are 2 race conditions that can happen:
				 *   - We've read the file's old size, and it has since increased.
				 *     -> In  this case, we'll be zero-initializing some data that has already
				 *        come to be considered as part of the live file, but that's OK, since
				 *        that data has never been accessed before, and would have been  zero-
				 *        filled in either case.
				 *     -> Even if the  `mo_loadblocks' calls  fails, we'll just  set those  blocks
				 *        back to ST_NDEF, which will effectively look like we didn't do anything.
				 *   - We've read  the file's  new size.  - that's  even simpler,  since then  we
				 *     won't do any  that `bzerophyscc' call  at all.  - In this  case, the  call
				 *     to `mo_loadblocks' will load in data from disk that (may have been) loaded
				 *     when the write  that increased the  file's size was  done. And since  this
				 *     writing  somewhere  further into  a  file automatically  implies  that all
				 *     uninitialized  data  up until  that point  should  be considered  as ZERO,
				 *     we'll  end  with the  same  result, where  the  fs-driver will  just write
				 *     zeroes to the buffer, the same way we would have! */
				if unlikely(addr + num_bytes > filesize) {
					/* Limit the load-range by the size of the file, and zero-initialize
					 * any memory that is being mapped beyond the end natural end of the
					 * file. */
					if unlikely(addr >= filesize) {
						bzerophyscc(min_addr, num_bytes);
					} else {
						size_t load_bytes;
						load_bytes = (size_t)(filesize - addr);
						assert(load_bytes < num_bytes);
						if likely(mo_loadblocks != NULL)
							mfile_dosyncio(file, mo_loadblocks, addr, min_addr, load_bytes);
						bzerophyscc(min_addr + load_bytes,
						            num_bytes - load_bytes);
					}
					goto initdone;
				}
			}
		}

		if likely(mo_loadblocks != NULL)
			mfile_dosyncio(file, mo_loadblocks, addr, min_addr, num_bytes);
	} EXCEPT {
		/* Change back all INIT-parts to UNDEF */
		for (i = min; i <= max; ++i)
			mpart_setblockstate(self, i, MPART_BLOCK_ST_NDEF);
		mfile_trunclock_dec_nosignal(file);
		sig_broadcast(&file->mf_initdone);
		decref_unlikely(file);
		RETHROW();
	}
initdone:

	/* Mark all INIT-pages as loaded. */
	for (i = min; i <= max; ++i)
		mpart_setblockstate(self, i, MPART_BLOCK_ST_LOAD);

	/* Broadcast that init has finished. */
	mfile_trunclock_dec_nosignal(file);
	sig_broadcast(&file->mf_initdone);

	decref_unlikely(file);
}



/* Directly return physical backing  memory containing the byte  `partrel_offset',
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

/* Return a direct pointer to the physical address at `partrel_offset'.
 * The  # of bytes which can be  read from this address directly depend
 * on  the alignment of `partrel_offset'. (s.a. `mpart_memaddr_direct') */
PUBLIC NOBLOCK NONNULL((1)) physaddr_t
NOTHROW(FCALL mpart_getphysaddr)(struct mpart *__restrict self,
                                 mpart_reladdr_t partrel_offset) {
	physaddr_t result;
	assert(partrel_offset < mpart_getsize(self));
	if (self->mp_state == MPART_ST_MEM) {
		/* Simple case: Everything is linear physical memory. */
		result = physpage2addr(self->mp_mem.mc_start) + partrel_offset;
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
		result = physpage2addr(self->mp_mem_sc.ms_v[i].mc_start) + partrel_offset;
	}
	return result;
}



/* Mark all blocks that overlap with the given address range as CHNG.
 * For this purpose, the caller must ensure that:
 * >> !OVERFLOW_UADD(partrel_offset, num_bytes, &endaddr) && endaddr <= mpart_getsize(self)
 *
 * If any of the blocks  within the given range had  yet to be marked as  CHNG,
 * and the associated file is not anonymous, and implements the `mo_saveblocks'
 * operator, and the  `MPART_F_CHANGED' flag had  yet to be  set for the  given
 * part, then set  the `MPART_F_CHANGED'  flag and add  `self' to  the list  of
 * changed parts of its associated file (unless the file's list of parts marked
 * as changed was set to `mf_changed = MFILE_PARTS_ANONYMOUS').
 * NOTE: The caller must be holding a lock to `self' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_changed)(struct mpart *__restrict self,
                             mpart_reladdr_t partrel_offset,
                             size_t num_bytes) {
	size_t i, blocks_start, blocks_end;
	shift_t shift;
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

	/* If  we did manage to set at  least 1 block to changed that
	 * wasn't set as such before, then we must mark this mem-part
	 * as having changed, and possibly  add it to the  associated
	 * file's list of changed parts. */
	if (did_change)
		mfile_add_changed_part(file, self);
}


PRIVATE NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL mpart_atomic_cmpxch_blockstate)(struct mpart *__restrict self,
                                              size_t partrel_block_index,
                                              unsigned int old_st,
                                              unsigned int new_st) {
	mpart_blkst_word_t *pword, mask, oldword, newword;
	mpart_blkst_word_t old_val, new_val;
	shift_t shift;
	assert(old_st < ((unsigned int)1 << MPART_BLOCK_STBITS));
	assert(new_st < ((unsigned int)1 << MPART_BLOCK_STBITS));
	shift   = (shift_t)((partrel_block_index % MPART_BLKST_BLOCKS_PER_WORD) * MPART_BLOCK_STBITS);
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
 *    the   current   page   directory,   using    `prot'.
 * This function is used to implement handling of hinted
 * mem-nodes   when  encountered  by  the  #PF  handler. */
PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL mpart_hinted_mmap)(struct mpart *__restrict self,
                                 PAGEDIR_PAGEALIGNED void *addr,
                                 PAGEDIR_PAGEALIGNED mpart_reladdr_t offset,
                                 pagedir_prot_t prot) {
	unsigned int st;
	struct mpart_physloc pl;
	size_t block_index;

	/* Some hinted-node-related assertions that we can make
	 * without  the need of knowing the accessing mem-node. */
	assert(!PREEMPTION_ENABLED());
	assert(self->mp_file != NULL);
	assert(ADDR_ISKERN(self->mp_file));
	assert(self->mp_file->mf_blockshift == PAGESHIFT);
	assert(self->mp_file->mf_parts == MFILE_PARTS_ANONYMOUS);
	assert(MPART_ST_INMEM(self->mp_state));

	/* Index of the block (aka. page) that is being accessed.
	 * Note  the  `self->mp_file->mf_blockshift == PAGESHIFT'
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
		 * then we must wait for it to finish doing so before we  can
		 * proceed. */
		if (st == MPART_BLOCK_ST_INIT) {
			/* Another CPU is currently doing the INIT */
			task_pause();
			goto again_read_st;
		}

		/* Must lazily initialize this block!
		 * For  this  purpose, preemption  must be  disabled (which
		 * is already done by the caller), since being  interrupted
		 * during the init, and having another thread then  attempt
		 * to  access the same page that we're trying to init would
		 * result in a dead-lock, where it will just keep on seeing
		 * `MPART_BLOCK_ST_INIT' for all of eternity... */
		if (!mpart_atomic_cmpxch_blockstate(self, block_index, st,
		                                    MPART_BLOCK_ST_INIT)) {
			/* Someone else was faster... -> Just re-read the status! */
			goto again_read_st;
		}
#endif /* !CONFIG_NO_SMP */

		if (st == MPART_BLOCK_ST_NDEF) {
			auto mo_loadblocks = self->mp_file->mf_ops->mo_loadblocks;
			if likely(mo_loadblocks != NULL) {
				/* NOTE: We're allowed to assume that this call is NOBLOCK+NOTHROW!
				 *       We  also don't have to call `mfile_trunclock_inc()', since
				 *       doing so wouldn't make any sense for any of the valid use-
				 *       cases of hinted memory mappings. */
				(*mo_loadblocks)(self->mp_file,
				                 mpart_getminaddr(self) + (block_index << PAGESHIFT),
				                 pl.mppl_addr, PAGESIZE,
				                 /* Because of requirements  for hinted mappings  (which
				                  * include  them  needing to  be non-blocking  and non-
				                  * throwing), we can infer that the initializer of such
				                  * a mapping couldn't possibly make use of AIO.
				                  *
				                  * To force a  kernel crash  if it still  tries to,  we
				                  * pass a guarantied faulty pointer for the AIO handle. */
				                 (struct aio_multihandle *)-1);
			}
		}

		/* And with  that, the  init is  done.  -> Mark  the block  as  CHNG.
		 * Also note that we don't have to deal with `MPART_F_MAYBE_BLK_INIT'
		 * or `self->mp_file->mf_initdone'. - None of those matter for hinted
		 * memory nodes! */
		mpart_setblockstate(self, block_index, MPART_BLOCK_ST_CHNG);
	}

	/* At this  point,  we  know  that the  accessed  page  has  surely  been
	 * initialized, so we are safe to map it into the current page directory.
	 * Also: We don't have to worry about preparing the page directory here.
	 *       Hinted nodes require that the `MNODE_F_MPREPARED' flag be  set,
	 *       meaning that we're  allowed to assume  that the page  directory
	 *       is, and always has been, prepared. */
	pagedir_mapone(addr, pl.mppl_addr, prot);

	/* Because  we got here as the result of a #PF, we don't even have to
	 * sync anything since all that our mapone() call did, was expand the
	 * set of available permissions, which the MMU will lazily pick up on
	 * all by itself. */
}

/* Convenience wrapper for `mpart_hinted_mmap()' */
PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) void
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
	assert(self->mn_link.le_prev == &mpart_getnodlst_from_mnodeflags(part, self->mn_flags)->lh_first);
	assert(*self->mn_link.le_prev == self);
	assert(LIST_NEXT(self, mn_link) == NULL);
	assert(LIST_EMPTY(mpart_getnodlst_from_mnodeflags(part, ~self->mn_flags)));

	/* Call forward to the mem-part-level hint handler. */
	mpart_hinted_mmap(part, fault_page,
	                  self->mn_partoff +
	                  (mpart_reladdr_t)((uintptr_t)fault_page -
	                                    (uintptr_t)mnode_getminaddr(self)),
	                  mnode_getperm_force(self));
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_BLOCKS_C */
