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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MPARTMETA_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MPARTMETA_C 1
#define __WANT_MFUTEX__mfu_lop
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/mpartmeta.h>

#include <kos/except.h>

#include <assert.h>
#include <atomic.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Assert consistency of `__WANT_MFUTEX__mfu_lop' */
static_assert(sizeof(struct sig) + sizeof(void *) == sizeof(Toblockop(mpart)));
static_assert(sizeof(struct sig) + sizeof(void *) == sizeof(Tobpostlockop(mpart)));

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mfutex_remove_from_mpart_postlop)(Tobpostlockop(mpart) *__restrict _lop,
                                                REF struct mpart *__restrict UNUSED(part)) {
	WEAK REF struct mfutex *me;
	me = container_of(_lop, struct mfutex, _mfu_plop);
	weakdecref_likely(me);
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(mpart) *
NOTHROW(FCALL mfutex_remove_from_mpart_lop)(Toblockop(mpart) *__restrict _lop,
                                            REF struct mpart *__restrict part);

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mfutex_remove_from_other_mpart_postlop)(Tobpostlockop(mpart) *__restrict _lop,
                                                      struct mpart *__restrict UNUSED(_old_part)) {
	WEAK REF struct mfutex *me;
	REF struct mpart *part;
	struct mpartmeta *meta;
	me = container_of(_lop, struct mfutex, _mfu_plop);

	/* Figure out the *real* part, and remove `self' from _its_ tree! */
again_read_part:
	part = awref_get(&me->mfu_part);
	if (!part)
		goto drop_futex_reference_after;
	meta = part->mp_meta;
	assert(meta != NULL);
	if (mpartmeta_ftxlock_trywrite(meta)) {
		/* Remove the mem-futex from the tree ourselves. */
		if unlikely(part != awref_ptr(&me->mfu_part)) {
			mpartmeta_ftxlock_endwrite(meta, part);
			decref_unlikely(part);
			goto again_read_part;
		}
		mpartmeta_ftx_removenode(meta, me);
		mpartmeta_ftxlock_endwrite(meta, part);
		weakdecref_nokill(me); /* From the futex-tree... */
drop_futex_reference_after:
		weakdecref_unlikely(me); /* From our caller */
	} else {
		/* Enqueue the futex for lazy removal. */
		incref(part); /* Inherited by `mfutex_remove_from_mpart_lop()' */
		me->_mfu_lop.olo_func = &mfutex_remove_from_mpart_lop;
		SLIST_ATOMIC_INSERT(&meta->mpm_ftxlops, &me->_mfu_lop, olo_link);

		/* Reap dead futex objects associated with the meta-controller. */
		_mpartmeta_ftxlock_reap(meta, part);
		decref_unlikely(part);
	}
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(mpart) *
NOTHROW(FCALL mfutex_remove_from_mpart_lop)(Toblockop(mpart) *__restrict _lop,
                                            REF struct mpart *__restrict part) {
	WEAK REF struct mfutex *me;
	me = container_of(_lop, struct mfutex, _mfu_lop);

	/* This reference was only needed to keep `part' alive until we
	 * got to a point where we're able to remove ourselves from its
	 * futex tree (iff we're still part of said tree) */
	decref_nokill(part);

	/* Ensure that `me' is still bound to `part' */
	if unlikely(part != awref_ptr(&me->mfu_part)) {
		me->_mfu_plop.oplo_func = &mfutex_remove_from_other_mpart_postlop;
		return &me->_mfu_plop;
	}

	/* Remove the mem-futex from the tree ourselves. */
	mpartmeta_ftx_removenode(part->mp_meta, me);
	weakdecref_nokill(me); /* From the futex-tree... */

	/* Drop the part reference, and free the futex itself later. */
	me->_mfu_plop.oplo_func = &mfutex_remove_from_mpart_postlop;
	return &me->_mfu_plop;
}

/* Destroy the given mem-futex. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfutex_destroy)(struct mfutex *__restrict self) {
	REF struct mpart *part;
	struct mpartmeta *meta;

	/* Broadcast the mem-futex one last time. */
	sig_broadcast_for_fini(&self->mfu_signal);

again_read_part:
	part = awref_get(&self->mfu_part);
	if (part) {
		meta = part->mp_meta;
		assert(meta != NULL);
		if (mpartmeta_ftxlock_trywrite(meta)) {
			/* Remove the mem-futex from the tree ourselves. */
			if unlikely(part != awref_ptr(&self->mfu_part)) {
				mpartmeta_ftxlock_endwrite(meta, part);
				decref_unlikely(part);
				goto again_read_part;
			}
			mpartmeta_ftx_removenode(meta, self);
			mpartmeta_ftxlock_endwrite(meta, part);
			weakdecref_nokill(self); /* From the futex-tree... */
		} else {
			/* Enqueue the futex for lazy removal. */
			incref(part); /* Inherited by `mfutex_remove_from_mpart_lop()' */
			self->_mfu_lop.olo_func = &mfutex_remove_from_mpart_lop;
			SLIST_ATOMIC_INSERT(&meta->mpm_ftxlops, &self->_mfu_lop, olo_link);

			/* Reap dead futex objects associated with the meta-controller. */
			_mpartmeta_ftxlock_reap(meta, part);
			decref_unlikely(part);
			return;
		}

		/* Cleanup... */
		decref_unlikely(part);
	}

	/* Free the futex object itself. */
	weakdecref_likely(self);
}

/* Mem-futex tree API. All of  these functions require that the  caller
 * be holding a lock to the associated `struct mpartmeta::mpm_ftxlock'. */
DECL_END

#define RBTREE_LEFT_LEANING
#define RBTREE_WANT_TRYINSERT
#define RBTREE_WANT_RLOCATE
#define RBTREE_WANT_RREMOVE
#define RBTREE(name)         mfutex_tree_##name
#define RBTREE_T             struct mfutex
#define RBTREE_Tkey          mpart_reladdr_t
#define RBTREE_GETNODE(self) (self)->mfu_mtaent
#define RBTREE_GETKEY(self)  mfutex_addr(self)
#define RBTREE_REDFIELD      mfu_addr
#define RBTREE_REDBIT        1
#define RBTREE_CC            FCALL
#define RBTREE_NOTHROW       NOTHROW
#define RBTREE_DECL          FUNDEF
#define RBTREE_IMPL          PUBLIC
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN


/* Clear the `mfu_part' field of all futex objects reachable from `root' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfutex_tree_clear_all_parts)(WEAK REF struct mfutex *__restrict root) {
	WEAK REF struct mfutex *lhs, *rhs;
again:
	/* If the futex is still alive, clear its part-pointer */
	if (tryincref(root)) {
		awref_clear(&root->mfu_part);
		decref_unlikely(root);
	}
	lhs = root->mfu_mtaent.rb_lhs;
	rhs = root->mfu_mtaent.rb_rhs;
	DBG_memset(&root->mfu_mtaent, 0xcc, sizeof(root->mfu_mtaent));

	/* Drop the weak reference held by the futex-tree */
	weakdecref_unlikely(root);
	if (lhs) {
		if (rhs)
			mfutex_tree_clear_all_parts(rhs);
		root = lhs;
		goto again;
	}
	if (rhs) {
		root = rhs;
		goto again;
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpartmeta_destroy)(struct mpartmeta *__restrict self) {
	assert(SLIST_EMPTY(&self->mpm_ftxlops));

	/* Deal with the rare situation where someone's still listening to us... */
	sig_broadcast_for_fini(&self->mpm_dma_done);

	/* For every futex apart of `mpm_ftx', clear the `mfu_part' pointer. */
	if (self->mpm_ftx != NULL)
		mfutex_tree_clear_all_parts(self->mpm_ftx);

	/* Free the meta-data controller. */
	kfree(self);
}






/************************************************************************/
/* Helper functions to creating/destroying DMA locks.                   */
/************************************************************************/

/* Must be called when `mpm_dmalocks' drops to `0' */
PUBLIC NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mpart *
NOTHROW(FCALL _mpart_dma_donelock)(REF struct mpart *__restrict self) {
	/* When dma-locks go away,  it may also become  possible
	 * to merge the part with some of its neighboring parts!
	 * For this purpose, check `MPART_XF_MERGE_AFTER_DMA' */
	uintptr_quarter_t xflags;

	/* Do the broadcast first, since `self' might change when `mpart_merge()' is called. */
	sig_broadcast(&self->mp_meta->mpm_dma_done);
	xflags = atomic_read(&self->mp_xflags);
	if unlikely(xflags & (MPART_XF_TRIM_AFTER_DMA | MPART_XF_MERGE_AFTER_DMA)) {
		xflags &= MPART_XF_TRIM_AFTER_DMA | MPART_XF_MERGE_AFTER_DMA;
		atomic_and(&self->mp_xflags, ~xflags);
		if (xflags & MPART_XF_MERGE_AFTER_DMA)
			self = mpart_merge(self);
		if (xflags & MPART_XF_TRIM_AFTER_DMA)
			mpart_trim(incref(self));
	}
	return self;
}






/************************************************************************/
/* Futex access/creation API                                            */
/************************************************************************/

/* Return  a pointer to  the meta-data controller  of `self', allocating it
 * if not already allocated in the past. This function should not be called
 * when already holding a lock to `self'. - Use `mpart_hasmeta_or_unlock()'
 * for that purpose instead! */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) struct mpartmeta *FCALL
mpart_getmeta(struct mpart *__restrict self) THROWS(E_BADALLOC) {
	struct mpartmeta *result;
	result = self->mp_meta;
	if unlikely(!result) {
		result = (struct mpartmeta *)kmalloc(sizeof(struct mpartmeta),
		                                     GFP_CALLOC);
		mpartmeta_cinit(result);

		/* Need to be holding a lock in order to write to `mp_meta'.
		 * s.a.  the  explaination  in   `mpart_hasmeta_or_unlock()' */
		TRY {
			mpart_lock_acquire(self);
		} EXCEPT {
			kfree(result);
			RETHROW();
		}

		/* Remember that meta-data has been allocated. */
		if likely(self->mp_meta == NULL) {
			self->mp_meta = result;
			mpart_lock_release(self);
		} else {
			mpart_lock_release(self);
			kfree(result);
			result = self->mp_meta;
		}
	}
	return result;
}

/* Return a reference  to the futex  associated with `file_position'  within the given  part.
 * If no such futex already exists, use this chance to allocate it, as well as a  potentially
 * missing `mfutex_controller' when `self->mp_meta' was `NULL' when this function was called.
 * @param: file_position:    The absolute in-file address of the futex (will be floor-aligned
 *                           by `MFUTEX_ADDR_ALIGNMENT' internally)
 * @return: * :              A reference to the futex associated with `file_position'
 * @return: MPART_FUTEX_OOB: The given `file_position' isn't mapped by `self'. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mfutex *FCALL
mpart_createfutex(struct mpart *__restrict self, pos_t file_position)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	REF struct mfutex *result;
	struct mpartmeta *meta;
	mpart_reladdr_t partrel_offset;

	/* Enforce proper alignment. */
	file_position &= ~(MFUTEX_ADDR_ALIGNMENT - 1);

	meta = mpart_getmeta(self);
again:
	mpartmeta_ftxlock_read(meta);
	if unlikely(file_position < mpart_getminaddr(self) ||
	            file_position > mpart_getmaxaddr(self)) {
		result = MPART_FUTEX_OOB;
		mpartmeta_ftxlock_endread(meta, self);
		goto done;
	}
	partrel_offset = (mpart_reladdr_t)(file_position - mpart_getminaddr(self));

	/* Check for an existing futex. */
	result = mpartmeta_ftx_locate(meta, partrel_offset);
	if (result && tryincref(result)) {
		mpartmeta_ftxlock_endread(meta, self);
		goto done;
	}

	/* Must create a new futex object.
	 * But note that we're currently holding a lock to `meta',
	 * so only  non-blocking operations  before releasing  it! */
	result = (REF struct mfutex *)kmalloc_nx(sizeof(struct mfutex),
	                                         GFP_ATOMIC);
	if unlikely(!result) {
		struct mfutex *old_futex;
		mpartmeta_ftxlock_endread(meta, self);
		result = (REF struct mfutex *)kmalloc(sizeof(struct mfutex),
		                                      GFP_NORMAL);
		TRY {
			mpartmeta_ftxlock_write(meta);
		} EXCEPT {
			kfree(result);
			RETHROW();
		}
check_old_futex:
		if unlikely(file_position < mpart_getminaddr(self) ||
		            file_position > mpart_getmaxaddr(self)) {
			kfree(result);
			mpartmeta_ftxlock_endwrite(meta, self);
			result = MPART_FUTEX_OOB;
			goto done;
		}
		partrel_offset = (mpart_reladdr_t)(file_position - mpart_getminaddr(self));

		/* Initialize the new futex object. */
		mfutex_init(result, self, partrel_offset);

		/* Try to insert the new futex into the tree. */
		if (mpartmeta_ftx_tryinsert(meta, result)) {
			++result->mfu_weakrefcnt; /* Tree-reference */
		} else {
			bool refok;
			old_futex = mpartmeta_ftx_locate(meta, partrel_offset);
			assert(old_futex);
			refok = tryincref(old_futex);
			mpartmeta_ftxlock_endwrite(meta, self);
			kfree(result);
			if likely(refok)
				return old_futex;
			/* Try again (the dead futex should have been
			 * reaped by  `mpartmeta_ftxlock_endwrite()') */
			goto again;
		}
	} else {
		TRY {
			if (!mpartmeta_ftxlock_upgrade(meta))
				goto check_old_futex;
		} EXCEPT {
			kfree(result);
			RETHROW();
		}

		/* Initialize the new futex object. */
		mfutex_init(result, self, partrel_offset);

		/* Insert the new futex into the tree. */
		++result->mfu_weakrefcnt; /* Tree-reference */
		mpartmeta_ftx_insert(meta, result);
	}
	mpartmeta_ftxlock_endwrite(meta, self);
done:
	return result;
}



/* Same as `mpart_createfutex()', but don't allocate a new futex object if none already
 * exists for the given `file_position'.
 * @param: file_position:    The absolute in-file address of the futex (will be floor-aligned
 *                           by `MFUTEX_ADDR_ALIGNMENT' internally)
 * @return: * :              A reference to the futex bound to the given `partrel_offset'
 * @return: NULL:            No futex exists for the given `partrel_offset'.
 * @return: MPART_FUTEX_OOB: The given `file_position' isn't mapped by `self'. */
PUBLIC WUNUSED NONNULL((1)) REF struct mfutex *FCALL
mpart_lookupfutex(struct mpart *__restrict self, pos_t file_position)
		THROWS(E_WOULDBLOCK) {
	REF struct mfutex *result = NULL;
	struct mpartmeta *meta;

	/* Enforce proper alignment. */
	file_position &= ~(MFUTEX_ADDR_ALIGNMENT - 1);
	meta = self->mp_meta;
	if (meta) {
		mpartmeta_ftxlock_read(meta);
		if likely(file_position >= mpart_getminaddr(self) &&
		          file_position <= mpart_getmaxaddr(self)) {
			mpart_reladdr_t reladdr;
			reladdr = (mpart_reladdr_t)(file_position - mpart_getminaddr(self));
			result  = mpartmeta_ftx_locate(meta, reladdr);
			/* If we found anything, try to acquire a reference. */
			if (result && !tryincref(result))
				result = NULL;
		} else {
			result = MPART_FUTEX_OOB;
		}
		mpartmeta_ftxlock_endread(meta, self);
	} else {
		/* Must still validate that this part is mapping the given `file_position' */
		mpart_lock_acquire(self);
		if unlikely(file_position < mpart_getminaddr(self) ||
		            file_position > mpart_getmaxaddr(self))
			result = MPART_FUTEX_OOB;
		mpart_lock_release(self);
	}
	return result;
}



/* Lookup a futex at a given address that is offset from the start of a given
 * mem-file. Note though the possibly unintended behavior which applies  when
 * the given `mfile' is anonymous at the time of the call being made.
 * @param: addr: Absolute file-address of the futex (will be floor-aligned by
 *               `MFUTEX_ADDR_ALIGNMENT' internally)
 * WARNING: Using  this function  when `self' has  been, or always  was anonymous, will
 *          cause the mem-part associated with the returned futex to also be anonymous,
 *          meaning that the part would get freshly allocated, and repeated calls  with
 *          the same arguments would not yield the same futex object!
 *       -> As  such, in the most common case of  a futex lookup where you wish to find
 *          the futex associated with some given  `uintptr_t', the process would be  to
 *          to determine the `mnode' of the address, and using that node then determine
 *          the associated mpart, and relative offset  into that mem-part. If a  lookup
 *          of  the   futex   then   returns  `MPART_FUTEX_OOB',   loop   back   around
 *          and once again lookup the `mnode'.
 * @return: * : The futex associated with the given `addr' */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mfutex *FCALL
mfile_createfutex(struct mfile *__restrict self, pos_t addr)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	REF struct mfutex *result;
	REF struct mpart *part;
again:
	part = mfile_getpart(self, addr, self->mf_part_amask + 1);
	{
		FINALLY_DECREF_UNLIKELY(part);
		result  = mpart_createfutex(part, addr);
	}
	if unlikely(result == MPART_FUTEX_OOB)
		goto again;
	return result;
}


/* Same  as `mfile_createfutex()', but don't allocate a new
 * futex object if none already exists for the given `addr'
 * @param: addr:  Absolute file-address of the futex (will be floor-aligned by
 *                `MFUTEX_ADDR_ALIGNMENT' internally)
 * @return: * :   The futex associated with the given `addr'
 * @return: NULL: No futex exists for the given address. */
PUBLIC WUNUSED NONNULL((1)) REF struct mfutex *FCALL
mfile_lookupfutex(struct mfile *__restrict self, pos_t addr)
		THROWS(E_WOULDBLOCK) {
	REF struct mfutex *result = NULL;
	struct mpart *part;
	struct mpartmeta *meta;
	mpart_reladdr_t reladdr;
	if unlikely(mfile_isanon(self))
		goto done;
	addr &= ~(MFUTEX_ADDR_ALIGNMENT - 1);
again:
	mfile_lock_read(self);
	if unlikely(mfile_isanon(self))
		goto unlock_file_and_done;
	part = mpart_tree_locate(self->mf_parts, addr);
	if (part == NULL) {
unlock_file_and_done:
		mfile_lock_endread(self);
		goto done;
	}
	if (wasdestroyed(part))
		goto unlock_file_and_done;
	meta = part->mp_meta;
	if (!meta)
		goto unlock_file_and_done;
	reladdr = (mpart_reladdr_t)(addr - mpart_getminaddr(part));
	if (mpartmeta_ftxlock_tryread(meta)) {
		result = mpartmeta_ftx_locate(meta, reladdr);
		if (result && !tryincref(result))
			result = NULL;
		mpartmeta_ftxlock_endread(meta, part);
		mfile_lock_endread(self);
	} else {
		/* Must acquire a temporary reference to the part,
		 * so we can drop our lock to the underlying file. */
		if unlikely(!tryincref(part))
			goto unlock_file_and_done;
		mfile_lock_endread(self);
		FINALLY_DECREF_UNLIKELY(part);
		mpartmeta_ftxlock_read(meta);
		if unlikely(addr < mpart_getminaddr(part) ||
		            addr > mpart_getmaxaddr(part)) {
			mpartmeta_ftxlock_endread(meta, part);
			goto again;
		}
		reladdr = (mpart_reladdr_t)(addr - mpart_getminaddr(part));
		result  = mpartmeta_ftx_locate(meta, reladdr);
		if (result && !tryincref(result))
			result = NULL;
		mpartmeta_ftxlock_endread(meta, part);
	}
done:
	return result;
}

/* Return the futex object that is associated with the given virtual memory address.
 * In  the event that  `addr' isn't mapped to  anything (or is  mapped to a reserved
 * node), then throw an `E_SEGFAULT' exception.
 * @param: addr: Absolute memory-address of the futex (will be floor-aligned by
 *               `MFUTEX_ADDR_ALIGNMENT' internally) */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mfutex *FCALL
mman_createfutex(struct mman *__restrict self, UNCHECKED void *addr)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT) {
	REF struct mfutex *result;
	REF struct mpart *part;
	pos_t filepos;
	struct mnode *node;
again:
	mman_lock_read(self);

	/* Lookup the accessed node. */
	node = mnode_tree_locate(self->mm_mappings, addr);
	if unlikely(node == NULL || (part = node->mn_part) == NULL) {
		mman_lock_endread(self);
		THROW(E_SEGFAULT_UNMAPPED, addr,
		      E_SEGFAULT_CONTEXT_FAULT |
		      E_SEGFAULT_CONTEXT_FUTEX);
	}
	assert(!wasdestroyed(part));
	incref(part);
	filepos = part->mp_minaddr + node->mn_partoff +
	          ((byte_t *)addr - node->mn_minaddr);
	mman_lock_endread(self);
	{
		FINALLY_DECREF_UNLIKELY(part);
		/* Construct the futex at the requested address within the file. */
		result = mpart_createfutex(part, filepos);
	}
	if unlikely(result == MPART_FUTEX_OOB)
		goto again;
	return result;
}


/* Same as `mman_createfutex()', but don't allocate a new futex object if none already
 * exists for the given `addr'. If the given address isn't mapped, also return `NULL'.
 * @param: addr:  Absolute memory-address of the futex (will be floor-aligned by
 *                `MFUTEX_ADDR_ALIGNMENT' internally)
 * @return: * :   The futex associated with the given `addr'
 * @return: NULL: No futex exists for the given address. */
PUBLIC WUNUSED NONNULL((1)) REF struct mfutex *FCALL
mman_lookupfutex(struct mman *__restrict self, UNCHECKED void *addr)
		THROWS(E_WOULDBLOCK) {
	REF struct mfutex *result;
	mpart_reladdr_t reladdr;
	struct mpart *part;
	struct mpartmeta *meta;
	struct mnode *node;
again:
	mman_lock_read(self);

	/* Lookup the accessed node. */
	node = mnode_tree_locate(self->mm_mappings, addr);
	if (!node) {
unlock_mman_and_return_null:
		mman_lock_endread(self);
		return NULL;
	}
	part = node->mn_part;
	if unlikely(!part)
		goto unlock_mman_and_return_null;
	assert(!wasdestroyed(part));
	meta = part->mp_meta;
	if (!meta)
		goto unlock_mman_and_return_null;
	reladdr = node->mn_partoff + ((byte_t *)addr - node->mn_minaddr);
	reladdr &= ~(MFUTEX_ADDR_ALIGNMENT - 1);
	if (mpartmeta_ftxlock_tryread(meta)) {
		result = mpartmeta_ftx_locate(meta, reladdr);
		if (result && !tryincref(result))
			result = NULL;
		mpartmeta_ftxlock_endread(meta, part);
		mman_lock_endread(self);
	} else {
		/* Must acquire a temporary reference to the part,
		 * so we can drop our lock to the underlying mman. */
		pos_t filepos;
		filepos = part->mp_minaddr + reladdr;
		incref(part);
		mman_lock_endread(self);
		FINALLY_DECREF_UNLIKELY(part);
		mpartmeta_ftxlock_read(meta);

		/* We may assume that  the backing mem-node didn't  get
		 * unmapped in the mean time, since that would indicate
		 * an error within the behavior of the calling program.
		 * With this in  mind, we're allowed  to invoke  weakly
		 * undefined  behavior, which essentially means that we
		 * don't have to re-check  that `node' is still  there!
		 *
		 * However, what we _do_ need to check is `part' having
		 * gotten split in the mean time. */
		if unlikely(filepos < mpart_getminaddr(part) ||
		            filepos > mpart_getmaxaddr(part)) {
			mpartmeta_ftxlock_endread(meta, part);
			goto again;
		}
		reladdr = (mpart_reladdr_t)(filepos - mpart_getminaddr(part));
		result  = mpartmeta_ftx_locate(meta, reladdr);
		if (result && !tryincref(result))
			result = NULL;
		mpartmeta_ftxlock_endread(meta, part);
	}
	return result;
}

/* Broadcast to all thread waiting for a futex at `addr' within the current mman.
 * If `addr' isn't  mapped, or  no pre-existing node  is bound  to that  address,
 * simply do nothing and return immediately.
 * @param: addr: Absolute memory-address of the futex (will be floor-aligned by
 *               `MFUTEX_ADDR_ALIGNMENT' internally) */
PUBLIC void FCALL
mman_broadcastfutex(UNCHECKED void *addr)
		THROWS(E_WOULDBLOCK) {
	REF struct mfutex *ftx;
	ftx = mman_lookupfutex(THIS_MMAN, addr);
	if (ftx) {
		sig_broadcast(&ftx->mfu_signal);
		decref_unlikely(ftx);
	}
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MPARTMETA_C */
