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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_PARTS_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_PARTS_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <kos/except.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#ifndef NDEBUG
#define DBG_memset(dst, byte, num_bytes) memset(dst, byte, num_bytes)
#else /* !NDEBUG */
#define DBG_memset(dst, byte, num_bytes) (void)0
#endif /* NDEBUG */


/* Create a new part, but don't add it to the global chain of parts, yet.
 * NOTE: The returned part will have the `MPART_F_NO_GLOBAL_REF' flag set! */
PRIVATE ATTR_RETNONNULL NONNULL((1)) REF struct mpart *KCALL
mfile_private_makepart(struct mfile *__restrict self,
                       PAGEDIR_PAGEALIGNED pos_t addr,
                       PAGEDIR_PAGEALIGNED size_t num_bytes)
		THROWS(E_WOULDBLOCK, ...) {
	REF struct mpart *result;
	assert(mfile_addr_aligned(self, addr));
	result = (REF struct mpart *)kmalloc(sizeof(struct mpart),
	                                     GFP_LOCKED);
	result->mp_refcnt = 1;
	result->mp_flags  = MPART_F_NORMAL | MPART_F_NO_GLOBAL_REF;
	result->mp_state  = MPART_ST_VOID;
	result->mp_file   = incref(self);
	LIST_INIT(&result->mp_copy);
	LIST_INIT(&result->mp_share);
	SLIST_INIT(&result->mp_lockops);
	DBG_memset(&result->mp_changed, 0xcc, sizeof(result->mp_changed));
	result->mp_minaddr = addr;
	result->mp_maxaddr = addr + num_bytes - 1;
	result->mp_meta    = NULL;
#ifdef LIBVIO_CONFIG_ENABLED
	if (mfile_getvio(self) != NULL) {
		result->mp_state = MPART_ST_VIO;
		LIST_ENTRY_UNBOUND_INIT(&result->mp_allparts);
		result->mp_blkst_ptr = NULL;
	} else
#endif /* LIBVIO_CONFIG_ENABLED */
	{
		size_t num_blocks;
		num_blocks = num_bytes >> self->mf_blockshift;
		/* Allocate the block-status bitset. */
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
			memset(bitset, MPART_BLOCK_REPEAT(MPART_BLOCK_ST_NDEF),
			       num_words, sizeof(mpart_blkst_word_t));
#endif /* MPART_BLOCK_ST_NDEF != 0 */
			result->mp_blkst_ptr = bitset;
		}
	}
	if (self->mf_ops->mo_initpart) {
		/* Service custom part initializer. */
		TRY {
			(*self->mf_ops->mo_initpart)(self, result);
		} EXCEPT {
			decref_nokill(self);
			if (!(result->mp_flags & MPART_F_BLKST_INL))
				kfree(result->mp_blkst_ptr);
			kfree(result);
			RETHROW();
		}
	}
	return result;
}



/* Same as `mfile_getpart()', but may _only_ be used when `self' is an
 * anonymous file! As such, this function is mainly used to allocate
 * parts for `mfile_ndef' and `mfile_zero' */
PUBLIC ATTR_RETNONNULL NONNULL((1)) REF struct mpart *FCALL
mfile_makepart(struct mfile *__restrict self,
               PAGEDIR_PAGEALIGNED pos_t addr,
               PAGEDIR_PAGEALIGNED size_t num_bytes)
		THROWS(E_WOULDBLOCK, ...) {
	REF struct mpart *result;
	result = mfile_private_makepart(self, addr, num_bytes);
	_mpart_init_asanon(result);

	/* Add the new part to the global list. */
#ifdef LIBVIO_CONFIG_ENABLED
	if (result->mp_state != MPART_ST_VIO)
#endif /* LIBVIO_CONFIG_ENABLED */
	{
		mpart_all_list_insert(result);
	}

	return result;
}



/* Check `self' for a known mem-part that contains `addr', and (if found),
 * return that part. Otherwise, construct a new part start starts at `addr'
 * and spans at most `max_num_bytes' bytes (less may be returned if another part
 * already exists that describes the mapping above the requested location)
 * NOTE: The caller must ensure that:
 * >> mfile_addr_aligned(addr) && mfile_addr_aligned(max_num_bytes)
 * @return: * : A reference to a part that (at some point in the past) contained
 *              the given `addr'. It may no longer contain that address now as
 *              the result of being truncated since. */
PUBLIC ATTR_RETNONNULL NONNULL((1)) REF struct mpart *FCALL
mfile_getpart(struct mfile *__restrict self,
              PAGEDIR_PAGEALIGNED pos_t addr,
              PAGEDIR_PAGEALIGNED size_t max_num_bytes)
		THROWS(E_WOULDBLOCK, ...) {
	REF struct mpart *result;
	struct mpart_tree_minmax mima;
	size_t limit;
	assert(mfile_addr_aligned(self, addr));
	assert(mfile_addr_aligned(self, max_num_bytes));
	assert(max_num_bytes != 0);
	if (self->mf_parts == MFILE_PARTS_ANONYMOUS) {
create_anon_part:
		return mfile_makepart(self, addr, max_num_bytes);
	}
again_lock:
	mfile_lock_read(self);
	result = self->mf_parts;
	if (result == MFILE_PARTS_ANONYMOUS) {
		mfile_lock_endread(self);
		goto create_anon_part;
	}
	result = mpart_tree_locate(result, addr);
	if (result) {
		if unlikely(!tryincref(result)) {
			/* This can happen if `result' is currently pending for destruction... */
			mfile_lock_endread_f(self);
			while (mfile_lockops_mustreap(self))
				_mfile_lockops_reap(self);
			goto again_lock;
		}
		mfile_lock_endread(self);
		return result;
	}
	/* TODO: Try to extend a preceding mem-part! */

	/* No node exists for `addr'. - Figure out what the next-larger node is. */
	mpart_tree_minmaxlocate(self->mf_parts, addr, addr + max_num_bytes - 1, &mima);
	limit = max_num_bytes;
	if (mima.mm_min) {
		limit = (size_t)(mpart_getminaddr(mima.mm_min) - addr);
		if (limit > max_num_bytes)
			limit = max_num_bytes;
	}
	mfile_lock_endread(self);
	/* Construct the new part. */
	result = mfile_private_makepart(self, addr, limit);
	TRY {
/*again_lock_after_result_created:*/
		mfile_lock_write(self);
		/* Make sure that nothing else appeared in the mean time. */
		if unlikely(self->mf_parts == MFILE_PARTS_ANONYMOUS) {
			mfile_lock_endwrite(self);
			assert(result->mp_file == self);
			decref_nokill(self);
			assert(self->mf_blockshift < COMPILER_LENOF(mfile_anon));
			result->mp_file = incref(&mfile_anon[self->mf_blockshift]);
			COMPILER_WRITE_BARRIER();

			/* Add the new part to the global list. */
#ifdef LIBVIO_CONFIG_ENABLED
			if (result->mp_state != MPART_ST_VIO)
#endif /* LIBVIO_CONFIG_ENABLED */
			{
				mpart_all_list_insert(result);
			}

			return result;
		}

		/* Try to insert the new node. */
		if (mpart_tree_tryinsert(&self->mf_parts, result)) {
			/* Success!
			 * Now also try to add the new part to the list of global parts. */
#ifdef LIBVIO_CONFIG_ENABLED
			if (result->mp_state != MPART_ST_VIO)
#endif /* LIBVIO_CONFIG_ENABLED */
			{
				result->mp_flags &= ~MPART_F_NO_GLOBAL_REF;
				++result->mp_refcnt; /* The reference owned by `mpart_all_list' */
				COMPILER_WRITE_BARRIER();

				/* Add the new part to the global list. */
				mpart_all_list_insert(result);
			}
			mfile_lock_endwrite(self);
			return result;
		}
	} EXCEPT {
		if (!(ATOMIC_FETCHOR(result->mp_flags, MPART_F_NO_GLOBAL_REF) & MPART_F_NO_GLOBAL_REF))
			decref_nokill(result);
		decref(result);
		RETHROW();
	}
	/* The insert failed because of an overlap. */
	mfile_lock_endwrite(self);
	LIST_ENTRY_UNBOUND_INIT(&result->mp_allparts);
	_mpart_init_asanon(result);
	mpart_destroy(result);
	goto again_lock;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_PARTS_C */
