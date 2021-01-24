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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MPARTMETA_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MPARTMETA_C 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/mpartmeta.h>

#include <hybrid/atomic.h>

#include <kos/except.h>

#include <assert.h>
#include <stddef.h>

DECL_BEGIN


/* Destroy the given mem-futex. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfutex_destroy)(struct mfutex *__restrict self) {
	REF struct mpart *part;
	struct mpartmeta *meta;

	/* Broadcast the mem-futex one last time. */
	sig_broadcast_for_fini(&self->mfu_signal);

	part = self->mfu_part.get();
	if (part) {
		meta = part->mp_meta;
		assert(meta != NULL);
		if (mpartmeta_ftxlock_trywrite(meta)) {
			/* Remove the mem-futex from the tree ourselves. */
			mfutex_tree_removenode(&meta->mpm_ftx, self);
			mpartmeta_ftxlock_endwrite(meta);
		} else {
			/* Enqueue the futex for lazy removal. */
			SLIST_ATOMIC_INSERT(&meta->mpm_ftx_dead, self, _mfu_dead);
	
			/* Reap dead futex objects associated with the meta-controller. */
			mpartmeta_deadftx_reap(meta);
			decref_unlikely(part);
			return;
		}

		/* Cleanup... */
		decref(part);
	}

	/* Free the futex object itself. */
	mfutex_free(self);
}

/* Same as `mfutex_destroy()', but _always_ enqueue the futex to-be reaped
 * lazily once `mpartmeta_deadftx_reap()' is called with the associated controller. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfutex_destroy_later)(struct mfutex *__restrict self) {
	REF struct mpart *part;
	struct mpartmeta *meta;

	/* Broadcast the mem-futex one last time. */
	sig_broadcast_for_fini(&self->mfu_signal);

	part = self->mfu_part.m_pointer; /* Inherit reference */
	meta = part->mp_meta;
	assert(meta != NULL);

	/* Enqueue the futex for lazy removal. */
	SLIST_ATOMIC_INSERT(&meta->mpm_ftx_dead, self, _mfu_dead);

	/* Reap dead futex objects associated with the meta-controller. */
	mpartmeta_deadftx_reap(meta);
	decref_unlikely(part);
}


/* Mem-futex tree API. All of these functions require that the caller
 * be holding a lock to the associated `struct mpartmeta::mpm_ftxlock'. */
DECL_END

#define RBTREE_LEFT_LEANING
#define RBTREE(name)           mfutex_tree_##name
#define RBTREE_T               struct mfutex
#define RBTREE_Tkey            mpart_reladdr_t
#define RBTREE_GETNODE(self)   (self)->mfu_mtaent
#define RBTREE_GETKEY(self)    mfutex_addr(self)
#define RBTREE_ISRED(self)     ((self)->mfu_addr & 1)
#define RBTREE_SETRED(self)    (void)((self)->mfu_addr |= 1)
#define RBTREE_SETBLACK(self)  (void)((self)->mfu_addr &= ~1)
#define RBTREE_CC              FCALL
#define RBTREE_NOTHROW         NOTHROW
#define RBTREE_DECL            FUNDEF
#define RBTREE_IMPL            PUBLIC
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN


PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpartmeta_destroy)(struct mpartmeta *__restrict self) {
	/* Make sure to free all still-pending dead futex objects. */
	while (!SLIST_EMPTY(&self->mpm_ftx_dead)) {
		struct mfutex *dead_futex;
		dead_futex = SLIST_FIRST(&self->mpm_ftx_dead);
		SLIST_REMOVE_HEAD(&self->mpm_ftx_dead, _mfu_dead);
		/* Normally, we'd also have to remove the futex from our `mpm_ftx'
		 * tree, however since that tree will be free'd in a moment, also,
		 * there's really no point is doing so! */
		mfutex_free(dead_futex);
	}

	/* Free the meta-data controller. */
	kfree(self);
}



/* Reap dead futex objects of `self' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _mpartmeta_deadftx_reap)(struct mpartmeta *__restrict self) {
	struct mfutex *ftx, *iter;
again:
	if (!atomic_rwlock_trywrite(&self->mpm_ftxlock))
		return;
	ftx = SLIST_ATOMIC_CLEAR(&self->mpm_ftx_dead);
	for (iter = ftx; iter; iter = SLIST_NEXT(iter, _mfu_dead))
		mfutex_tree_removenode(&self->mpm_ftx, iter);
	atomic_rwlock_endwrite(&self->mpm_ftxlock);
	while (ftx) {
		struct mfutex *next;
		next = SLIST_NEXT(ftx, _mfu_dead);
		mfutex_free(ftx);
		ftx = next;
	}
	if (mpartmeta_deadftx_mustreap(self))
		goto again;
}




/************************************************************************/
/* Futex access/creation API                                            */
/************************************************************************/

/* Return a pointer to the meta-data controller of `self', allocating it
 * if not already allocated in the past. This function should not be called
 * when already holding a lock to `self'. - Use `mpart_hasmeta_or_unlock()'
 * for that purpose instead! */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) struct mpartmeta *FCALL
mpart_getmeta(struct mpart *__restrict self) THROWS(E_BADALLOC) {
	struct mpartmeta *result;
	result = self->mp_meta;
	if unlikely(!result) {
		result = (struct mpartmeta *)kmalloc(sizeof(struct mpartmeta),
		                                     GFP_CALLOC);
		mpartmeta_cinit(result);
		if unlikely(!ATOMIC_CMPXCH(self->mp_meta, NULL, result)) {
			kfree(result);
			result = ATOMIC_READ(self->mp_meta);
		}
	}
	return result;
}

/* Return a reference to the futex associated with `partrel_offset' within the given part.
 * If no such futex already exists, use this chance to allocate it, as well as a potentially
 * missing `mfutex_controller' when `self->mp_meta' was `NULL' when this function was called.
 * @param: partrel_offset:   Part-relative futex address (will be floor-aligned by
 *                           `MFUTEX_ADDR_ALIGNMENT' internally)
 * @return: * :              A reference to the futex associated with `partrel_offset'
 * @return: MPART_FUTEX_OOB: The given `partrel_offset' is greater than `mpart_getsize(self)'. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mfutex *FCALL
mpart_createfutex(struct mpart *__restrict self, mpart_reladdr_t partrel_offset)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	REF struct mfutex *result;
	struct mpartmeta *meta;
	/* Enforce proper alignment. */
	partrel_offset &= ~(MFUTEX_ADDR_ALIGNMENT - 1);

	meta = mpart_getmeta(self);
	mpartmeta_ftxlock_read(meta);
	if unlikely(partrel_offset >= mpart_getsize(self)) {
		result = MPART_FUTEX_OOB;
		mpartmeta_ftxlock_endread(meta);
	} else {
		/* Check for an existing futex. */
		result = mfutex_tree_locate(meta->mpm_ftx, partrel_offset);
		if (result && tryincref(result)) {
			mpartmeta_ftxlock_endread(meta);
		} else {
			/* Must create a new futex object.
			 * But note that we're currently holding a lock to `meta',
			 * so only non-blocking operations before releasing it! */
			result = (REF struct mfutex *)kmalloc_nx(sizeof(struct mfutex),
			                                         GFP_ATOMIC);
			if unlikely(!result) {
				struct mfutex *old_futex;
				mpartmeta_ftxlock_endread(meta);
				result = (REF struct mfutex *)kmalloc(sizeof(struct mfutex),
				                                      GFP_NORMAL);
				TRY {
					mpartmeta_ftxlock_write(meta);
				} EXCEPT {
					kfree(result);
					RETHROW();
				}
check_old_futex:
				old_futex = mfutex_tree_locate(meta->mpm_ftx, partrel_offset);
				if unlikely(old_futex && tryincref(old_futex)) {
					/* Deal with the case of another, existing futex. */
					mpartmeta_ftxlock_endwrite(meta);
					kfree(result);
					return old_futex;
				}
			} else {
				TRY {
					if (!mpartmeta_ftxlock_upgrade(meta))
						goto check_old_futex;
				} EXCEPT {
					kfree(result);
					RETHROW();
				}
			}
			/* Initialize the new futex object. */
			mfutex_init(result, self, partrel_offset);
			/* Insert the new futex into the tree. */
			mfutex_tree_insert(&meta->mpm_ftx, result);
			mpartmeta_ftxlock_endwrite(meta);
		}
	}
	return result;
}

/* Same as `mpart_createfutex()', but don't allocate a new futex object if none already
 * exists for the given `partrel_offset'
 * @param: partrel_offset:   Part-relative futex address (will be floor-aligned by
 *                           `MFUTEX_ADDR_ALIGNMENT' internally)
 * @return: * :              A reference to the futex bound to the given `partrel_offset'
 * @return: NULL:            No futex exists for the given `partrel_offset'.
 * @return: MPART_FUTEX_OOB: The given `partrel_offset' is greater than `mpart_getsize(self)'. */
PUBLIC WUNUSED NONNULL((1)) REF struct mfutex *FCALL
mpart_lookupfutex(struct mpart *__restrict self, mpart_reladdr_t partrel_offset)
		THROWS(E_WOULDBLOCK) {
	REF struct mfutex *result = NULL;
	struct mpartmeta *meta;
	meta = self->mp_meta;
	if (meta) {
		/* Enforce proper alignment. */
		partrel_offset &= ~(MFUTEX_ADDR_ALIGNMENT - 1);
		mpartmeta_ftxlock_read(meta);
		result = mfutex_tree_locate(meta->mpm_ftx, partrel_offset);
		/* If we found anything, try to acquire a reference. */
		if (result && !tryincref(result))
			result = NULL;
		mpartmeta_ftxlock_endread(meta);
	}
	return result;
}


/* Lookup a futex at a given address that is offset from the start of a given
 * mem-file. Note though the possibly unintended behavior which applies when
 * the given `mfile' is anonymous at the time of the call being made.
 * @param: addr: Absolute file-address of the futex (will be floor-aligned by
 *               `MFUTEX_ADDR_ALIGNMENT' internally)
 * WARNING: Using this function when `self' has been, or always was anonymous, will
 *          cause the mem-part associated with the returned futex to also be anonymous,
 *          meaning that the part would get freshly allocated, and repeated calls with
 *          the same arguments would not yield the same futex object!
 *       -> As such, in the most common case of a futex lookup where you wish to find
 *          the futex associated with some given `uintptr_t', the process would be to
 *          to determine the `mnode' of the address, and using that node then determine
 *          the associated mpart, and relative offset into that mem-part. If a lookup
 *          of the futex then returns `MPART_FUTEX_OOB', loop back around
 *          and once again lookup the `mnode'.
 *       -> In the end, there exists no API also found on linux that would make use of this
 *          function, however on KOS it is possible to access this function through use of
 *          the HANDLE_TYPE_DATABLOCK-specific hop() function `HOP_DATABLOCK_OPEN_FUTEX[_EXISTING]'
 * @return: * : The futex associated with the given `addr' */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mfutex *FCALL
mfile_createfutex(struct mfile *__restrict self, pos_t addr)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	REF struct mfutex *result;
	REF struct mpart *part;
again:
	part = mfile_getpart(self, addr, self->mf_part_amask + 1);
	{
		mpart_reladdr_t reladdr;
		FINALLY_DECREF_UNLIKELY(part);
		reladdr = (mpart_reladdr_t)(addr - mpart_getminaddr(part));
		result  = mpart_createfutex(part, reladdr);
	}
	if unlikely(result == MPART_FUTEX_OOB)
		goto again;
	return result;
}


/* Same as `mfile_createfutex()', but don't allocate a new
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
again:
	mfile_lock_read(self);
	if unlikely(!mfile_isanon(self))
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
	reladdr &= ~(MFUTEX_ADDR_ALIGNMENT - 1);
	if (mpartmeta_ftxlock_tryread(meta)) {
		result = mfutex_tree_locate(meta->mpm_ftx, reladdr);
		if (result && !tryincref(result))
			result = NULL;
		mpartmeta_ftxlock_endread(meta);
		mfile_lock_endread(self);
	} else {
		/* Must acquire a temporary reference to the part,
		 * so we can drop our lock to the underlying file. */
		if unlikely(!tryincref(part))
			goto unlock_file_and_done;
		mfile_lock_endread(self);
		FINALLY_DECREF_UNLIKELY(part);
		mpartmeta_ftxlock_read(meta);
		if unlikely(reladdr >= mpart_getsize(part)) {
			mpartmeta_ftxlock_endread(meta);
			goto again;
		}
		result = mfutex_tree_locate(meta->mpm_ftx, reladdr);
		if (result && !tryincref(result))
			result = NULL;
		mpartmeta_ftxlock_endread(meta);
	}
done:
	return result;
}

/* Return the futex object that is associated with the given virtual memory address.
 * In the event that `addr' isn't mapped to anything (or is mapped to a reserved
 * node), then throw an `E_SEGFAULT' exception.
 * @param: addr: Absolute memory-address of the futex (will be floor-aligned by
 *               `MFUTEX_ADDR_ALIGNMENT' internally) */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mfutex *FCALL
mman_createfutex(struct mman *__restrict self, UNCHECKED void *addr)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT) {
	REF struct mfutex *result;
	REF struct mpart *part;
	mpart_reladdr_t reladdr;
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
	reladdr = node->mn_partoff + ((byte_t *)addr - node->mn_minaddr);
	mman_lock_endread(self);
	{
		FINALLY_DECREF_UNLIKELY(part);
		/* Construct the futex at the requested address within the part. */
		result = mpart_createfutex(part, reladdr);
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
		result = mfutex_tree_locate(meta->mpm_ftx, reladdr);
		if (result && !tryincref(result))
			result = NULL;
		mpartmeta_ftxlock_endread(meta);
		mman_lock_endread(self);
	} else {
		/* Must acquire a temporary reference to the part,
		 * so we can drop our lock to the underlying mman. */
		incref(part);
		mman_lock_endread(self);
		FINALLY_DECREF_UNLIKELY(part);
		mpartmeta_ftxlock_read(meta);
		/* We may assume that the backing mem-node didn't get
		 * unmapped in the mean time, since that would indicate
		 * an error within the behavior of the calling program.
		 * With this in mind, we're allowed to invoke weakly
		 * undefined behavior, which essentially means that we
		 * don't have to re-check that `node' is still there!
		 *
		 * However, what we _do_ need to check is `part' having
		 * gotten split in the mean time. */
		if unlikely(reladdr >= mpart_getsize(part)) {
			mpartmeta_ftxlock_endread(meta);
			goto again;
		}

		result = mfutex_tree_locate(meta->mpm_ftx, reladdr);
		if (result && !tryincref(result))
			result = NULL;
		mpartmeta_ftxlock_endread(meta);
	}
	return result;
}

/* Broadcast to all thread waiting for a futex at `addr' within the current mman.
 * If `addr' isn't mapped, or no pre-existing node is bound to that address,
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
