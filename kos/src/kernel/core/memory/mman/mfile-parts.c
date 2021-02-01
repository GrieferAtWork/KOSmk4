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
#include <hybrid/overflow.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#ifndef NDEBUG
#define DBG_memset(dst, byte, num_bytes) memset(dst, byte, num_bytes)
#else /* !NDEBUG */
#define DBG_memset(dst, byte, num_bytes) (void)0
#endif /* NDEBUG */

LOCAL ATTR_RETNONNULL NONNULL((1)) REF struct mpart *FCALL
_mfile_newpart(struct mfile *__restrict self,
               PAGEDIR_PAGEALIGNED pos_t addr,
               PAGEDIR_PAGEALIGNED size_t num_bytes)
		THROWS(E_WOULDBLOCK, ...) {
	REF struct mpart *result;
	if (self->mf_ops->mo_newpart) {
		result = (*self->mf_ops->mo_newpart)(self, addr, num_bytes);
		assert(!(result->mp_flags & (MPART_F_GLOBAL_REF | MPART_F_LOCKBIT |
		                             MPART_F_CHANGED | MPART_F_PERSISTENT |
		                             MPART_F__RBRED)));
	} else {
		size_t num_blocks;
		result = (REF struct mpart *)kmalloc(sizeof(struct mpart),
		                                     GFP_LOCKED | GFP_PREFLT);
		result->mp_flags = MPART_F_NORMAL;
		num_blocks = (num_bytes + (((size_t)1 << self->mf_blockshift) - 1)) >> self->mf_blockshift;
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
		if unlikely(mfile_getvio(self) != NULL)
			result->mp_state = MPART_ST_VIO;
#endif /* LIBVIO_CONFIG_ENABLED */
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
	assert(mfile_isanon(self));
	assert(mfile_addr_aligned(self, addr));
	assert(mfile_addr_aligned(self, num_bytes));
	assert(num_bytes != 0);
	result = _mfile_newpart(self, addr, num_bytes);

	/* Initialize remaining fields. */
	result->mp_refcnt = 1;
	result->mp_file   = self;
#ifdef CONFIG_USE_NEW_FS
	if (self->mf_flags & MFILE_F_DELETED)
		result->mp_file = &mfile_anon[self->mf_blockshift];
#endif /* CONFIG_USE_NEW_FS */
	incref(result->mp_file);
	LIST_INIT(&result->mp_copy);
	LIST_INIT(&result->mp_share);
	SLIST_INIT(&result->mp_lockops);
	LIST_ENTRY_UNBOUND_INIT(&result->mp_allparts);
	result->mp_minaddr = addr;
	result->mp_maxaddr = addr + num_bytes - 1;
	DBG_memset(&result->mp_changed, 0xcc, sizeof(result->mp_changed));
	_mpart_init_asanon(result);
	return result;
}



/* Check `self' for a known mem-part that contains `addr', and (if
 * found), return that part. Otherwise, construct a new part start
 * starts at `addr' and spans around `hint_bytes' bytes (less may
 * be returned if another part already exists that describes the
 * mapping above the requested location, and more may be returned
 * if a pre-existing part was spans beyond `addr +hint_bytes -1')
 *
 * See also the effect that `mf_size' and `MFILE_F_DELETED' have
 * on the behavior of this function.
 *
 * Note that the caller must ensure that:
 * >> mfile_addr_aligned(addr) && mfile_addr_aligned(hint_bytes)
 * @return: * : A reference to a part that (at some point in the past) contained
 *              the given `addr'. It may no longer contain that address now as
 *              the result of being truncated since.
 * @throw: E_INVALID_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_MMAP_BEYOND_END_OF_FILE: ... */
PUBLIC ATTR_RETNONNULL NONNULL((1)) REF struct mpart *FCALL
mfile_getpart(struct mfile *__restrict self,
              PAGEDIR_PAGEALIGNED pos_t addr,
              PAGEDIR_PAGEALIGNED size_t hint_bytes)
		THROWS(E_WOULDBLOCK, E_INVALID_ARGUMENT, ...) {
	REF struct mpart *result;
	size_t num_bytes;
	pos_t loadmax;
again:
	if (mfile_isanon(self)) {
makeanon:
		return mfile_makepart(self, addr, hint_bytes);
	}

	assert(mfile_addr_aligned(self, addr));
	assert(mfile_addr_aligned(self, hint_bytes));
	assert(hint_bytes != 0);

	/* Check for a pre-existing part at the given location,
	 * as well as making sure that `addr' lies in-bounds of
	 * our file. */
	mfile_lock_read(self);
	if unlikely(self->mf_parts == MFILE_PARTS_ANONYMOUS) {
		mfile_lock_endread(self);
		goto makeanon;
	}
#ifdef CONFIG_USE_NEW_FS
	assert(!(self->mf_flags & MFILE_F_DELETED));
#endif /* CONFIG_USE_NEW_FS */
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

#ifdef CONFIG_USE_NEW_FS
	/* Check if `addr' lies in-bounds of the file, and limit the max #
	 * of bytes for the new mem-part to always stop just shy of the block-
	 * aligned ceil-size of the underlying mem-part. */
	{
		pos_t filsiz;
		filsiz = self->mf_size;
		filsiz += self->mf_part_amask;
		filsiz &= ~self->mf_part_amask;
		if likely(filsiz >= self->mf_part_amask) {
			if unlikely(addr >= filsiz) {
				mfile_lock_endread(self);
				THROW(E_INVALID_ARGUMENT,
				      E_INVALID_ARGUMENT_CONTEXT_MMAP_BEYOND_END_OF_FILE,
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
#endif /* CONFIG_USE_NEW_FS */

	/* Limit the given `num_bytes' by the distance
	 * until the next already-present mem-part. */
	{
		struct mpart_tree_minmax mima;
		mpart_tree_minmaxlocate(self->mf_parts, addr, loadmax, &mima);
		if (mima.mm_min != NULL) {
			assert(addr < mpart_getminaddr(mima.mm_min));
			assert(loadmax >= mpart_getminaddr(mima.mm_min));
			loadmax   = mpart_getminaddr(mima.mm_min) - 1;
			num_bytes = (size_t)(loadmax - addr) + 1;
		}
	}
	mfile_lock_endread(self);

	/* Must construct a new mem-part. */
	result = _mfile_newpart(self, addr, num_bytes);

	/* Initialize remaining fields. */
	result->mp_refcnt = 2; /* +1: return, +1: MPART_F_GLOBAL_REF */
	result->mp_file   = incref(self);
	LIST_INIT(&result->mp_copy);
	LIST_INIT(&result->mp_share);
	SLIST_INIT(&result->mp_lockops);
	/*LIST_ENTRY_UNBOUND_INIT(&result->mp_allparts);*/ /* Initialized later... */
	result->mp_minaddr = addr;
	result->mp_maxaddr = loadmax;
	DBG_memset(&result->mp_changed, 0xcc, sizeof(result->mp_changed));
	_mpart_init_asanon(result);
	result->mp_flags |= MPART_F_GLOBAL_REF;

	/* Mark the part as persistent if our file is, too. */
#ifdef CONFIG_USE_NEW_FS
#if MFILE_F_PERSISTENT == MPART_F_PERSISTENT
	result->mp_flags |= self->mf_flags & MPART_F_PERSISTENT;
#else /* MFILE_F_PERSISTENT == MPART_F_PERSISTENT */
	if (self->mf_flags & MFILE_F_PERSISTENT)
		result->mp_flags |= MPART_F_PERSISTENT;
#endif /* MFILE_F_PERSISTENT != MPART_F_PERSISTENT */
#endif /* CONFIG_USE_NEW_FS */

	TRY {
		mfile_lock_write(self);
	} EXCEPT {
		LIST_ENTRY_UNBOUND_INIT(&result->mp_allparts);
		result->mp_refcnt = 0;
		mpart_destroy(result);
	}

	/* Verify that nothing's changed in the mean time. */
	if unlikely(self->mf_parts == MFILE_PARTS_ANONYMOUS)
		goto startover;
#ifdef CONFIG_USE_NEW_FS
	if (self->mf_size < (loadmax + 1) || loadmax == (pos_t)-1) {
		pos_t filsiz;
		filsiz = self->mf_size;
		filsiz += self->mf_part_amask;
		filsiz &= ~self->mf_part_amask;
		--filsiz;
		if unlikely(filsiz < loadmax)
			goto startover;
	}
#endif /* CONFIG_USE_NEW_FS */

	/* Try to insert the new part into the tree. */
	if unlikely(!mpart_tree_tryinsert(&self->mf_parts, result))
		goto startover;

	/* Add the new part to the list of all parts. (but only if it's not a VIO part) */
#ifdef LIBVIO_CONFIG_ENABLED
	if unlikely(result->mp_state == MPART_ST_VIO) {
		/* Don't insert VIO-parts into the global list. Note that getting here
		 * is highly unlikely, since VIO files are usually also anonymous, or
		 * have their backing mem-parts be pre-allocated... */
		result->mp_flags &= ~MPART_F_GLOBAL_REF;
		result->mp_refcnt = 1;
		LIST_ENTRY_UNBOUND_INIT(&result->mp_allparts);
	} else
#endif /* LIBVIO_CONFIG_ENABLED */
	{
		mpart_all_list_insert(result);
	}

	mfile_lock_endwrite(self);
	return result;
startover:
	mfile_lock_endwrite(self);
	LIST_ENTRY_UNBOUND_INIT(&result->mp_allparts);
	result->mp_refcnt = 0;
	mpart_destroy(result);
	goto again;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_PARTS_C */
