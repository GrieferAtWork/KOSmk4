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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_PARTS_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_PARTS_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>
#include <kernel/rand.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>

#include <kos/except.h>
#include <kos/except/reason/illop.h>

#include <assert.h>
#include <atomic.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
#endif /* NDEBUG || NDEBUG_FINI */


/* While holding a read- or write-lock to `self', try to extend an
 * existing mem-part that borders against the given address  range
 * in order to fill the specified gap.
 * This function assumes that:
 *  - @assume(mfile_lock_reading(self) || mfile_lock_writing(self));
 *  - @assume(data->mep_minaddr <= data->mep_maxaddr);
 *  - @assume(mfile_partaddr_aligned(self, data->mep_minaddr));
 *  - @assume(mfile_partaddr_aligned(self, data->mep_maxaddr + 1));
 *  - @assume(WAS_CALLED(mfile_extendpart_data_init(data)));
 *  - @assume(self->mf_parts != MFILE_PARTS_ANONYMOUS);
 *  - @assume(!mpart_tree_rlocate(self->mf_parts, data->mep_minaddr, data->mep_maxaddr));
 * Locking logic:
 *   in:                                         mfile_lock_reading(self) || mfile_lock_writing(self)
 *   return == *:                                mfile_lock_writing(self) && undefined(out(data)) &&
 *                                               mpart_lock_acquired(return)
 *   return == MFILE_EXTENDPART_OR_UNLOCK_NOSIB: (mfile_lock_reading(self) || mfile_lock_writing(self)) &&
 *                                               undefined(out(data))
 *   return == MFILE_EXTENDPART_OR_UNLOCK_AGAIN: mfile_lock_end(self) && unlock()
 *   EXCEPT:                                     mfile_lock_end(self) && unlock()
 * @return: * : Success: A pointer to an extended mem-part that contains the entirety
 *                       of the address  range originally specified  in `data'.  Note
 *                       that in this case, you're inheriting a lock to that part.
 *                       Note: In this case, this function also guaranties that the
 *                       returned part doesn't exist in  SWAP, though it may  still
 *                       not be allowed (i.e. it's state may be MPART_ST_VOID)
 * @return: MFILE_EXTENDPART_OR_UNLOCK_NOSIB: (kind-of) success; the function was unable
 *                       to extend a pre-existing mem-part, but this is because there was
 *                       no such part to begin with: No existing part was neighboring, or
 *                       was even remotely close to the given address range, meaning that
 *                       extending such a part (if one even exists at all) would be  less
 *                       efficient than just creating a new, separate part.
 * @return: MFILE_EXTENDPART_OR_UNLOCK_AGAIN: The lock to `self' (and `unlock') was lost.
 *                       Simply re-acquire those locks and try again. Note that in this
 *                       case, the caller should always acquire a write-lock to `self'! */
PUBLIC WUNUSED NONNULL((1, 2)) struct mpart *FCALL
mfile_extendpart_or_unlock(struct mfile *__restrict self,
                           struct mfile_extendpart_data *__restrict data,
                           struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	assert(mfile_lock_reading(self) || mfile_lock_writing(self));
	assert(data->mep_minaddr <= data->mep_maxaddr);
	assert(mfile_partaddr_aligned(self, data->mep_minaddr));
	assert(mfile_partaddr_aligned(self, data->mep_maxaddr + 1));
	assert(self->mf_parts != MFILE_PARTS_ANONYMOUS);
	assert(!mpart_tree_rlocate(self->mf_parts, data->mep_minaddr, data->mep_maxaddr));

	/* TODO */

	(void)self;
	(void)unlock;
	mfile_extendpart_data_fini(data);

	return MFILE_EXTENDPART_OR_UNLOCK_NOSIB;
}

/* Look  at the neighbors of `part' and try to merge them with `part'. If
 * no neighbors exist, or if those neighbors are so far away that merging
 * with  them wouldn't be efficient, then simply insert `part' as-is into
 * the given mem-file `self', before adding `part' to the global list  of
 * parts, and finally releasing a lock to `self', as well as re-returning
 * a pointer to the given part.
 *  - For this purpose,  the caller must  initialize:
 *    >> part->mp_refcnt = MPART_F_GLOBAL_REF ? 2 : 1
 *  - If the `MPART_F_CHANGED' flag is  set, the given part, or  the
 *    combination of it and the to-be returned part will be added to
 *    the changed-part list.
 *  - However, if this is done, the caller is responsible for updating
 *    the file such that `MFILE_F_CHANGED' is set, and  `mo_changed()'
 *    is invoked.
 *  - If merging was done, return a reference to the new part against
 *    within the given `part' was merged (i.e. the one that was  left
 *    apart of the mem-part tree of `self')
 * This function assumes that:
 *  - @assume(mfile_lock_writing(self));
 *  - @assume(mfile_partaddr_aligned(self, part->mp_minaddr));
 *  - @assume(mfile_partaddr_aligned(self, part->mp_maxaddr + 1));
 *  - @assume(self->mf_parts != MFILE_PARTS_ANONYMOUS);
 *  - @assume(LIST_EMPTY(&part->mp_copy));
 *  - @assume(LIST_EMPTY(&part->mp_share));
 *  - @assume(UNINITIALIZED(&part->mp_allparts));
 *  - @assume(part->mp_refcnt == 1 + ((part->mp_flags & MPART_F_GLOBAL_REF) != 0) + ((part->mp_flags & MPART_F_CHANGED) != 0));
 *  - @assume(part->mp_file == self);
 *  - @assume(INITIALIZED(part->mp_*)); // All other fields...
 * @return: NULL: A pre-existing part overlaps with the address range of `part':
 *                mpart_tree_rlocate(self->mf_parts, part->mp_minaddr, part->mp_maxaddr) != NULL
 * @return: * :   A reference to a part that (at one point) contained a super-set
 *                of  the   address  range   described  by   the  given   `part'. */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) REF struct mpart *
NOTHROW(FCALL mfile_insert_and_merge_part_and_unlock)(struct mfile *__restrict self,
                                                      /*inherit(on_success)*/ struct mpart *__restrict part) {
	assert(mfile_lock_writing(self));
	assert(mfile_partaddr_aligned(self, part->mp_minaddr));
	assert(mfile_partaddr_aligned(self, part->mp_maxaddr + 1));
	assert(self->mf_parts != MFILE_PARTS_ANONYMOUS);
	assert(LIST_EMPTY(&part->mp_copy));
	assert(LIST_EMPTY(&part->mp_share));
	assert(part->mp_refcnt == ((part->mp_flags & MPART_F_GLOBAL_REF)
	                           ? (part->mp_flags & MPART_F_CHANGED) ? 3 : 2
	                           : (part->mp_flags & MPART_F_CHANGED) ? 2 : 1));
	assert(part->mp_file == self);

	/* Try to insert the new part into the tree. */
	if unlikely(!mpart_tree_tryinsert(&self->mf_parts, part))
		return NULL;
	if (part->mp_flags & MPART_F_CHANGED) {
		/* Add the new part to the list of changed parts. */
		struct mpart *next_changed;
		do {
			next_changed = atomic_read(&self->mf_changed.slh_first);
			if unlikely(next_changed == MFILE_PARTS_ANONYMOUS ||
			            self->mf_ops->mo_saveblocks == NULL) {
				assertf(self->mf_ops->mo_saveblocks == NULL ? (next_changed == MFILE_PARTS_ANONYMOUS ||
				                                               next_changed == NULL)
				                                            : 1,
				        "This is an invariant that must never be broken");

				/* Can't add the part to the list of changed parts for one of 2 reasons:
				 * - `next_changed == MFILE_PARTS_ANONYMOUS': Changed parts are not being tracked
				 * - `self->mf_ops->mo_saveblocks == NULL':   The file is unable to save changes
				 *
				 * NOTE: As far as semantics go, we're  allowed to leave the MPART_F_CHANGED  flag
				 *       in-tact when `next_changed == MFILE_PARTS_ANONYMOUS', since the flag must
				 *       be ignored in that  case. To harden code  against the eventuality of  the
				 *       flag being set in cases  where its meaning is  invalid, we only clear  it
				 *       when we have to, or randomly. */
				--part->mp_refcnt;
#ifndef NDEBUG
				if (next_changed != MFILE_PARTS_ANONYMOUS || (krand() & 1))
#endif /* !NDEBUG */
				{
					part->mp_flags &= ~MPART_F_CHANGED;
				}
				break;
			}
			part->mp_changed.sle_next = next_changed;
			COMPILER_WRITE_BARRIER();
		} while (!atomic_cmpxch_weak(&self->mf_changed.slh_first,
		                             next_changed, part));
	}

	/* This is when  the part will  actually become  visible!
	 * With that in mind, we have to be certain that the part
	 * is  fully initialized and  ready for every sub-system. */
	COMPILER_BARRIER();

	mpart_all_list_insert(part);
	mfile_lock_endwrite(self);

	/* Try to merge the part. */
	return mpart_merge(part);
}



/* High-level wrapper for `mf_ops->mo_newpart' that automatically does
 * the  right  things when  `mf_ops->mo_newpart' hasn't  been defined.
 * This function doesn't  do any further  initialization than what  is
 * already described by `mf_ops->mo_newpart' */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mpart *FCALL
_mfile_newpart(struct mfile *__restrict self,
               PAGEDIR_PAGEALIGNED pos_t addr,
               PAGEDIR_PAGEALIGNED size_t num_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	REF struct mpart *result;
	if (self->mf_ops->mo_newpart) {
		result = (*self->mf_ops->mo_newpart)(self, addr, num_bytes);
		assert(!(result->mp_flags & (MPART_F_GLOBAL_REF | MPART_F_LOCKBIT |
		                             MPART_F_CHANGED | MPART_F__RBRED)));
	} else {
		size_t num_blocks;
		result = (REF struct mpart *)kmalloc(sizeof(struct mpart),
		                                     GFP_LOCKED | GFP_PREFLT);
		result->mp_flags = MPART_F_NORMAL;
		num_blocks = (num_bytes + mfile_getblockmask(self)) >> self->mf_blockshift;
		if (num_blocks <= MPART_BLKST_BLOCKS_PER_WORD) {
			result->mp_flags |= MPART_F_BLKST_INL;
			result->mp_blkst_inl = MPART_BLOCK_REPEAT(MPART_BLOCK_ST_NDEF);
		} else {
			mpart_blkst_word_t *bitset;
			size_t num_words;
			num_words = CEILDIV(num_blocks, MPART_BLKST_BLOCKS_PER_WORD);
			TRY {
				bitset = (mpart_blkst_word_t *)kmalloc(num_words * sizeof(mpart_blkst_word_t),
#if MPART_BLOCK_ST_NDEF == 0
				                                       GFP_CALLOC |
#endif /* MPART_BLOCK_ST_NDEF == 0 */
				                                       GFP_LOCKED | GFP_PREFLT);
			} EXCEPT {
				kfree(result);
				RETHROW();
			}
#if MPART_BLOCK_ST_NDEF != 0
			memsetc(bitset, MPART_BLOCK_REPEAT(MPART_BLOCK_ST_NDEF),
			        num_words, sizeof(mpart_blkst_word_t));
#endif /* MPART_BLOCK_ST_NDEF != 0 */
			result->mp_blkst_ptr = bitset;
		}
		result->mp_state = MPART_ST_VOID;
		result->mp_meta  = NULL;
#ifdef LIBVIO_CONFIG_ENABLED
		if unlikely(self->mf_ops->mo_vio != NULL)
			result->mp_state = MPART_ST_VIO;
#endif /* LIBVIO_CONFIG_ENABLED */
	}
	return result;
}

/* Same as `mfile_getpart()', but may _only_ be used when `self' is an
 * anonymous file! As such, this  function is mainly used to  allocate
 * parts for `mfile_ndef' and `mfile_zero' */
PUBLIC ATTR_RETNONNULL NONNULL((1)) REF struct mpart *FCALL
mfile_makepart(struct mfile *__restrict self,
               PAGEDIR_PAGEALIGNED pos_t addr,
               PAGEDIR_PAGEALIGNED size_t num_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	REF struct mpart *result;
	assert(mfile_isanon(self));
	assert(mfile_partaddr_aligned(self, addr));
	assert(mfile_partaddr_aligned(self, num_bytes));
	assert(num_bytes != 0);
	result = _mfile_newpart(self, addr, num_bytes);

	/* Initialize remaining fields. */
	result->mp_refcnt = 1;
	result->mp_xflags = MPART_XF_NORMAL;
	result->mp_file   = self;
	if unlikely(self->mf_flags & MFILE_F_DELETED)
		result->mp_file = &mfile_anon[self->mf_blockshift];
	incref(result->mp_file);
	LIST_INIT(&result->mp_copy);
	LIST_INIT(&result->mp_share);
	SLIST_INIT(&result->mp_lockops);
	result->mp_minaddr = addr;
	result->mp_maxaddr = addr + num_bytes - 1;
	DBG_memset(&result->mp_changed, 0xcc, sizeof(result->mp_changed));
	_mpart_init_asanon(result);

	/* Even if it's an anon part, still add it to the global list, so `system_cc()' sees it. */
	mpart_all_list_insert(result);
	return result;
}



/* Check `self' for a known mem-part that contains `addr', and (if
 * found), return that part. Otherwise, construct a new part start
 * starts at `addr' and spans around `hint_bytes' bytes (less  may
 * be returned if another part  already exists that describes  the
 * mapping above the requested location, and more may be  returned
 * if  a pre-existing part was spans beyond `addr +hint_bytes -1')
 *
 * Note that the caller must ensure that:
 * >> mfile_partaddr_aligned(addr) && mfile_partaddr_aligned(hint_bytes)
 * @return: * : A reference to a part that (at some point in the past) contained
 *              the given `addr'. It may no  longer contain that address now  as
 *              the result of being truncated since.
 * @throw: E_INVALID_OPERATION:E_ILLEGAL_OPERATION_CONTEXT_MMAP_BEYOND_END_OF_FILE: ... */
PUBLIC ATTR_RETNONNULL NONNULL((1)) REF struct mpart *FCALL
mfile_getpart(struct mfile *__restrict self,
              PAGEDIR_PAGEALIGNED pos_t addr,
              PAGEDIR_PAGEALIGNED size_t hint_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_INVALID_OPERATION) {
	REF struct mpart *result;
	size_t num_bytes;
	pos_t loadmax;
again:
	if (mfile_isanon(self)) {
makeanon:
		return mfile_makepart(self, addr, hint_bytes);
	}

	assert(mfile_partaddr_aligned(self, addr));
	assert(mfile_partaddr_aligned(self, hint_bytes));
	assert(hint_bytes != 0);

	/* Check for a pre-existing part at the given location,
	 * as well as making sure that `addr' lies in-bounds of
	 * our file. */
	mfile_lock_read(self);
	if unlikely(self->mf_parts == MFILE_PARTS_ANONYMOUS) {
		mfile_lock_endread(self);
		goto makeanon;
	}
	result = mpart_tree_locate(self->mf_parts, addr);
	if (result != NULL && tryincref(result)) {
		/* Found a pre-existing part. */
		mfile_lock_endread(self);
		return result;
	}

	/* Figure out the max address range which we're
	 * allowed to assign to the to-be created part. */
	num_bytes = hint_bytes;
	if (OVERFLOW_UADD(addr, num_bytes - 1, &loadmax)) {
		num_bytes = (size_t)((pos_t)0 - addr);
		loadmax   = (pos_t)-1;
	}

	/* Check if `addr'  lies in-bounds of  the file, and  limit the max  #
	 * of bytes for the new mem-part to always stop just shy of the block-
	 * aligned ceil-size of the underlying mem-part. */
	{
		pos_t filsiz = mfile_getsize(self);
		if (!OVERFLOW_UADD(filsiz, self->mf_part_amask, &filsiz)) {
			filsiz &= ~(pos_t)self->mf_part_amask;
			if likely(filsiz >= self->mf_part_amask) {
				if unlikely(addr >= filsiz) {
					mfile_lock_endread(self);
					THROW(E_INVALID_OPERATION,
					      E_ILLEGAL_OPERATION_CONTEXT_MMAP_BEYOND_END_OF_FILE,
					      (uintptr_t)addr);
				}
				if (loadmax >= (filsiz - 1)) {
					size_t diff;
					diff    = (size_t)(loadmax - (filsiz - 1));
					loadmax = (filsiz - 1);
					num_bytes -= diff;
				}
			}
		}
	}

	/* Limit the given `num_bytes' by the distance
	 * until the  next  already-present  mem-part. */
	{
		struct mpart_tree_minmax mima;
		struct mfile_extendpart_data extdat;
		mpart_tree_minmaxlocate(self->mf_parts, addr, loadmax, &mima);
		if (mima.mm_min != NULL) {
			assert(addr < mpart_getminaddr(mima.mm_min));
			assert(loadmax >= mpart_getminaddr(mima.mm_min));
			loadmax   = mpart_getminaddr(mima.mm_min) - 1;
			num_bytes = (size_t)(loadmax - addr) + 1;
		}

		/* Try to extend a successor/predecessor mem-part to include
		 * the address range which we're  supposed to return to  our
		 * caller! */
		mfile_extendpart_data_init(&extdat);
		extdat.mep_minaddr = addr;
		extdat.mep_maxaddr = loadmax;
again_extend_part:
		TRY {
			result = mfile_extendpart_or_unlock(self, &extdat, NULL);
		} EXCEPT {
			mfile_extendpart_data_fini(&extdat);
			RETHROW();
		}
		if (result == MFILE_EXTENDPART_OR_UNLOCK_AGAIN) {
			TRY {
				mfile_lock_write(self);
			} EXCEPT {
				mfile_extendpart_data_fini(&extdat);
				RETHROW();
			}
			if unlikely(mfile_isanon(self)) {
				mfile_lock_endwrite(self);
				mfile_extendpart_data_fini(&extdat);
				goto again;
			}
			result = mpart_tree_locate(self->mf_parts, addr);
			if unlikely(result != NULL && tryincref(result)) {
				/* Found a pre-existing part. */
				mfile_lock_endwrite(self);
				mfile_extendpart_data_fini(&extdat);
				return result;
			}
			/* Figure out the max address range which we're
			 * allowed to assign to the to-be created part. */
			num_bytes = hint_bytes;
			if (OVERFLOW_UADD(addr, num_bytes - 1, &loadmax)) {
				num_bytes = (size_t)((pos_t)0 - addr);
				loadmax   = (pos_t)-1;
			}

			/* Check if `addr'  lies in-bounds of  the file, and  limit the max  #
			 * of bytes for the new mem-part to always stop just shy of the block-
			 * aligned ceil-size of the underlying mem-part. */
			{
				pos_t filsiz = mfile_getsize(self);
				if (!OVERFLOW_UADD(filsiz, self->mf_part_amask, &filsiz)) {
					filsiz &= ~(pos_t)self->mf_part_amask;
					if likely(filsiz >= self->mf_part_amask) {
						if unlikely(addr >= filsiz) {
							mfile_lock_endwrite(self);
							mfile_extendpart_data_fini(&extdat);
							THROW(E_INVALID_OPERATION,
							      E_ILLEGAL_OPERATION_CONTEXT_MMAP_BEYOND_END_OF_FILE,
							      (uintptr_t)addr);
						}
						if (loadmax >= (filsiz - 1)) {
							size_t diff;
							diff    = (size_t)(loadmax - (filsiz - 1));
							loadmax = (filsiz - 1);
							num_bytes -= diff;
						}
					}
				}
			}
			mpart_tree_minmaxlocate(self->mf_parts, addr, loadmax, &mima);
			if (mima.mm_min != NULL) {
				assert(addr < mpart_getminaddr(mima.mm_min));
				assert(loadmax >= mpart_getminaddr(mima.mm_min));
				loadmax   = mpart_getminaddr(mima.mm_min) - 1;
				num_bytes = (size_t)(loadmax - addr) + 1;
			}
			goto again_extend_part;
		}
		if (result != MFILE_EXTENDPART_OR_UNLOCK_NOSIB) {
			incref(result);
			mpart_assert_integrity(result);
			mpart_lock_release(result);
			mfile_lock_endwrite(self);
			return result;
		}
	}
	mfile_lock_end(self);

	/* Must construct a new mem-part. */
	result = _mfile_newpart(self, addr, num_bytes);

	/* Initialize remaining fields. */
	result->mp_refcnt = 2; /* +1: return, +1: MPART_F_GLOBAL_REF */
	result->mp_xflags = MPART_XF_NORMAL;
	result->mp_file   = incref(self);
	LIST_INIT(&result->mp_copy);
	LIST_INIT(&result->mp_share);
	SLIST_INIT(&result->mp_lockops);
	/*TAILQ_ENTRY_UNBOUND_INIT(&result->mp_allparts);*/ /* Initialized later... */
	result->mp_minaddr = addr;
	result->mp_maxaddr = loadmax;
	DBG_memset(&result->mp_changed, 0xcc, sizeof(result->mp_changed));
	_mpart_init_asanon(result);
	result->mp_flags |= MPART_F_GLOBAL_REF;
	TRY {
		mfile_lock_write(self);
	} EXCEPT {
		TAILQ_ENTRY_UNBOUND_INIT(&result->mp_allparts);
		result->mp_refcnt = 0;
		mpart_destroy(result);
		RETHROW();
	}

	/* Verify that nothing's changed in the mean time. */
	if unlikely(self->mf_parts == MFILE_PARTS_ANONYMOUS)
		goto startover;
	{
		pos_t filsiz = mfile_getsize(self);
		if (filsiz < (loadmax + 1) || loadmax == (pos_t)-1) {
			if (!OVERFLOW_UADD(filsiz, self->mf_part_amask, &filsiz)) {
				filsiz &= ~(pos_t)self->mf_part_amask;
				--filsiz;
				if unlikely(filsiz < loadmax)
					goto startover;
			}
		}
	}

	/* Add the new part to the list of all parts. (but only if it's not a VIO part) */
#ifdef LIBVIO_CONFIG_ENABLED
	if unlikely(result->mp_state == MPART_ST_VIO) {
		/* Don't insert VIO-parts into the global list. Note that getting here
		 * is  highly unlikely, since VIO files are usually also anonymous, or
		 * have their backing mem-parts be pre-allocated... */
		result->mp_flags &= ~MPART_F_GLOBAL_REF;
		result->mp_refcnt = 1;
	}
#endif /* LIBVIO_CONFIG_ENABLED */

	/* Try to insert the new part into the tree. */
	result = mfile_insert_and_merge_part_and_unlock(self, result);
	if unlikely(!result)
		goto startover;
	return result;
startover:
	mfile_lock_endwrite(self);
	TAILQ_ENTRY_UNBOUND_INIT(&result->mp_allparts);
	result->mp_refcnt = 0;
	mpart_destroy(result);
	goto again;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_PARTS_C */
