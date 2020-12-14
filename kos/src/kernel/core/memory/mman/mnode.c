/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MNODE_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MNODE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/paging.h>

#include <hybrid/atomic.h>

#include <kos/except.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/* Free/destroy a given mem-node */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mnode_free)(struct mnode *__restrict self) {
	if (self->mn_flags & MNODE_F_COREPART) {
		/* TODO: Must use the corebase free() function! */
	}
	kfree(self);
}



PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_maybe_clear_mlock)(struct mpart *__restrict self) {
	/* Check if there are any nodes mapping our part that use LOCK flags.
	 * For this purpose, both copy-on-write and shared nodes can lock the part. */
	struct mnode *node;
	LIST_FOREACH(node, &self->mp_copy, mn_link) {
		if (node->mn_flags & MNODE_F_MLOCK)
			return;
	}
	LIST_FOREACH(node, &self->mp_share, mn_link) {
		if (node->mn_flags & MNODE_F_MLOCK)
			return;
	}
	/* Clear the lock-flag for our part, since there are no
	 * more nodes that could keep our part locked in-core! */
	ATOMIC_AND(self->mp_flags, ~MPART_F_MLOCK);
}



PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mnode_destroy)(struct mnode *__restrict self) {
	REF struct mpart *part;
	xdecref(self->mn_fspath);
	xdecref(self->mn_fsname);
	if ((part = self->mn_part) != NULL) {
		/* Try to unlink the node from the copy- or share-chain of the associated part. */
		if (mpart_lock_tryacquire(part)) {
			LIST_REMOVE(self, mn_link);
			if ((self->mn_flags & (MNODE_F_MLOCK)) &&
			    (part->mp_flags & (MPART_F_MLOCK | MPART_F_MLOCK_FROZEN)) == MPART_F_MLOCK)
				mpart_maybe_clear_mlock(part);
			mpart_lock_release(part);
			decref_unlikely(part);
		} else {
			/* Must insert the node into the part's list of deleted nodes. */
			weakincref(self->mn_mman); /* A weak reference here is required by the ABI */

			/* Mark our part as being destroyed in the eyes of others. */
			ATOMIC_WRITE(self->mn_part, NULL);

			/* Insert into the dead-nodes list of `part'
			 * The act of doing this is what essentially causes
			 * ownership of our node to be transfered to `part' */
			SLIST_ATOMIC_INSERT(&part->mp_deadnodes, self, _mn_dead);

			/* Try to reap dead nodes. */
			mpart_deadnodes_reap(part);

			/* Drop our old reference to the associated part. */
			decref_unlikely(part);
			return;
		}
	}
	mnode_free(self);
}



/* Clear page-directory-level write-access to `self'. This function must be
 * called for all writable memory mappings of a MMAN when the MMAN is cloned or
 * a copy-on-write mapping is created for an already-shared `mn_part':
 * >> mmap() {
 * >>     ...
 * >>     if (flags & MNODE_F_SHARED) {
 * >>         ...
 * >>     } else {
 * >>         if (part->mp_copy == NULL) {
 * >>             LIST_FOREACH(node, &part->mp_share, mn_link) {
 * >>                 mnode_clear_write(node);
 * >>             }
 * >>         } else if (LIST_NEXT(part->mp_copy, mn_link) != NULL &&
 * >>                    mfile_isanon(file)) {
 * >>             // This is what would happen during a fork()
 * >>             mnode_clear_write(part->mp_copy);
 * >>         }
 * >>     }
 * >> }
 * NOTE: This function is designed to be called while the caller is already
 *       holding a lock to the node's associated mem-part.
 * @return: * : One of `MNODE_CLEAR_WRITE_*' */
PUBLIC NOBLOCK NONNULL((1)) unsigned int
NOTHROW(FCALL mnode_clear_write)(struct mnode *__restrict self) {
	unsigned int result;
	struct mman *mm = self->mn_mman;
	if (!LIST_ISBOUND(self, mn_writable)) {
		/* Simple case: this node isn't writable.
		 * This is thread-safe, since our caller is currently holding a
		 * lock to the associated mem-part, and for this node to (re-)gain
		 * write access, it would first have to acquire that same lock.
		 *
		 * As such, if it's not writable now, then it can't become so
		 * before our caller releases their lock to the associated part. */
		return MNODE_CLEAR_WRITE_SUCCESS;
	}

	if (!tryincref(mm))
		return MNODE_CLEAR_WRITE_SUCCESS; /* Special case: deleted node. */

	/* Try to acquire a lock to the associated mman */
	if (!mman_lock_tryacquire(mm)) {
		result = MNODE_CLEAR_WRITE_WOULDBLOCK;
	} else {
		if unlikely(self->mn_part == NULL) {
			/* Special case: deleted node.
			 * This must be checked _after_ we've acquired the lock. */
			result = MNODE_CLEAR_WRITE_SUCCESS;
		} else {
			/* Do the thing! */
			result = mnode_clear_write_locked(self, mm);
			if likely(result == MNODE_CLEAR_WRITE_SUCCESS) {
				/* Sync the memory mamanger. */
				mman_sync_p(mm,
				            mnode_getaddr(self),
				            mnode_getsize(self));
			}
		}
		mman_lock_release(mm);
	}
	decref_unlikely(mm);
	return result;
}



/* Same as `mnode_clear_write', but the caller is already holding a lock to `mm',
 * and this function will never return with `MNODE_CLEAR_WRITE_WOULDBLOCK'.
 * NOTE: Unlike with `mnode_clear_write', when calling this function,
 *       the caller must ensure that:
 *        - !wasdestroyed(mm)
 *        - !mman_lock_acquired(mm)
 *        - self->mn_part != NULL
 *        - LIST_ISBOUND(self, mn_writable)
 * Also note that the caller is responsible to sync `mm' before unlocking it! */
PUBLIC NOBLOCK NONNULL((1, 2)) unsigned int
NOTHROW(FCALL mnode_clear_write_locked)(struct mnode *__restrict self,
                                        struct mman *__restrict mm) {
	pagedir_phys_t pdir;
	void *addr;
	size_t size;
	assert(!wasdestroyed(mm));
	assert(!mman_lock_acquired(mm));
	assert(self->mn_part != NULL);
	assert(LIST_ISBOUND(self, mn_writable));
	assertf(self->mn_flags & MNODE_F_PWRITE,
	        "How could we have been added to the list of writable nodes "
	        "when we're not actually supposed to be writable at all?");

	pdir = mm->mm_pdir_phys;
	addr = mnode_getaddr(self);
	size = mnode_getsize(self);

	/* Prepare the page directory */
	if unlikely(!pagedir_prepare_map_p(pdir, addr, size))
		return MNODE_CLEAR_WRITE_BADALLOC;

	/* Delete write permissions. */
	pagedir_unwrite_p(pdir, addr, size);

	/* Unprepare the page directory. */
	pagedir_unprepare_map_p(pdir, addr, size);

	/* Unlink from the list of writable nodes. */
	LIST_UNBIND(self, mn_writable);
	return MNODE_CLEAR_WRITE_SUCCESS;
}



/* Same as `mnode_clear_write_locked()', but directory operate on
 * the current page directory. */
PUBLIC NOBLOCK NONNULL((1)) unsigned int
NOTHROW(FCALL mnode_clear_write_locked_local)(struct mnode *__restrict self) {
	void *addr;
	size_t size;
	assert(self->mn_part != NULL);
	assert(LIST_ISBOUND(self, mn_writable));
	assertf(self->mn_flags & MNODE_F_PWRITE,
	        "How could we have been added to the list of writable nodes "
	        "when we're not actually supposed to be writable at all?");

	addr = mnode_getaddr(self);
	size = mnode_getsize(self);

	/* Prepare the page directory */
	if unlikely(!pagedir_prepare_map(addr, size))
		return MNODE_CLEAR_WRITE_BADALLOC;

	/* Delete write permissions. */
	pagedir_unwrite(addr, size);

	/* Unprepare the page directory. */
	pagedir_unprepare_map(addr, size);

	/* Unlink from the list of writable nodes. */
	LIST_UNBIND(self, mn_writable);
	return MNODE_CLEAR_WRITE_SUCCESS;
}



/* Mem-node tree API. All of these functions require that the caller
 * be holding a lock to the associated mman. */
DECL_END

#undef RBTREE_LEFT_LEANING
#define RBTREE_WANT_PREV_NEXT_NODE
#define RBTREE(name)           mnode_tree_##name
#define RBTREE_T               struct mnode
#define RBTREE_Tkey            pos_t
#define RBTREE_GETNODE(self)   (self)->mn_mement
#define RBTREE_GETMINKEY(self) mnode_getminaddr(self)
#define RBTREE_GETMAXKEY(self) mnode_getmaxaddr(self)
#define RBTREE_ISRED(self)     ((self)->mp_flags & MNODE_F__RBRED)
#define RBTREE_SETRED(self)    (void)((self)->mp_flags |= MNODE_F__RBRED)
#define RBTREE_SETBLACK(self)  (void)((self)->mp_flags &= ~MNODE_F__RBRED)
#define RBTREE_CC              FCALL
#define RBTREE_NOTHROW         NOTHROW
#define RBTREE_DECL            FUNDEF
#define RBTREE_IMPL            PUBLIC
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN



DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MNODE_C */
