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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MNODE_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MNODE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/mcoreheap.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mm-sync.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/paging.h>
#include <kernel/panic.h>

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

/* Free/destroy a given mem-node */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mnode_free)(struct mnode *__restrict self) {
	if (self->mn_flags & MNODE_F_COREPART) {
		mcoreheap_free(container_of(self, union mcorepart, mcp_node));
	} else {
		kfree(self);
	}
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



INTDEF NOBLOCK NONNULL((1, 2)) void /* From "mpart.c" */
NOTHROW(FCALL mnode_unlink_from_part_lockop)(struct mpart_lockop *__restrict self,
                                             struct mpart *__restrict part);

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mnode_destroy)(struct mnode *__restrict self) {
	REF struct mpart *part;
	assertf((self->mn_flags & MNODE_F_UNMAPPED) || wasdestroyed(self->mn_mman),
	        "A mem-node may only be destroyed if it's marked as UNMAPPED, "
	        "or belonges to a dead memory manager");
	if (self->mn_flags & MNODE_F_MPREPARED) {
		REF struct mman *mm = self->mn_mman;
		if (tryincref(mm)) {
			pagedir_phys_t pd = self->mn_mman->mm_pagedir_p;
			pagedir_unprepare_map_p(pd, mnode_getaddr(self), mnode_getsize(self));
			decref_unlikely(mm);
		}
	}

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
			struct mpart_lockop *lop;
			/* Must insert the node into the part's list of deleted nodes. */
			weakincref(self->mn_mman); /* A weak reference here is required by the ABI */
			DBG_memset(&self->mn_part, 0xcc, sizeof(self->mn_part));

			/* Insert into the lock-operations list of `part'
			 * The act of doing this is what essentially causes
			 * ownership of our node to be transfered to `part' */
			lop = (struct mpart_lockop *)self;
			lop->mplo_func = &mnode_unlink_from_part_lockop;
			SLIST_ATOMIC_INSERT(&part->mp_lockops, lop, mplo_link);

			/* Try to reap dead nodes. */
			_mpart_deadnodes_reap(part);

			/* Drop our old reference to the associated part. */
			decref(part);
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
		/* Do the thing! */
		result = mnode_clear_write_locked(self, mm);
		if likely(result == MNODE_CLEAR_WRITE_SUCCESS) {
			/* Sync the memory mamanger. */
			mman_sync_p(mm,
			            mnode_getaddr(self),
			            mnode_getsize(self));
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

	pdir = mm->mm_pagedir_p;
	addr = mnode_getaddr(self);
	size = mnode_getsize(self);

	if (self->mn_flags & MNODE_F_MPREPARED) {
		/* Delete write permissions. */
		pagedir_unwrite_p(pdir, addr, size);
	} else {
		/* Prepare the page directory */
		if unlikely(!pagedir_prepare_map_p(pdir, addr, size))
			return MNODE_CLEAR_WRITE_BADALLOC;

		/* Delete write permissions. */
		pagedir_unwrite_p(pdir, addr, size);

		/* Unprepare the page directory. */
		pagedir_unprepare_map_p(pdir, addr, size);
	}

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


/* Split `lonode' (which contains `addr_where_to_split') at that address.
 * If this cannot be done without blocking, unlock and eventually return `false' */
PUBLIC WUNUSED NONNULL((1, 2)) bool FCALL
mnode_split_or_unlock(struct mman *__restrict self,
                      struct mnode *__restrict lonode,
                      PAGEDIR_PAGEALIGNED void *addr_where_to_split,
                      struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	bool result = true;
	struct mnode *hinode;
	struct mpart *part;
	assert((byte_t *)addr_where_to_split >= (byte_t *)mnode_getaddr(lonode));
	assert((byte_t *)addr_where_to_split < (byte_t *)mnode_getendaddr(lonode));

	/* Safety check: panic if the specified node isn't allowed to be split. */
	if unlikely(lonode->mn_flags & MNODE_F_NO_SPLIT) {
		kernel_panic("Not allowed to split node at %p-%p at %p",
		             mnode_getminaddr(lonode),
		             mnode_getmaxaddr(lonode),
		             addr_where_to_split);
	}

	/* Try to allocate the missing high-node. */
	hinode = (struct mnode *)kmalloc_nx(sizeof(struct mnode),
	                                    GFP_LOCKED | GFP_PREFLT | GFP_ATOMIC);
	if (!hinode) {
		/* Must do the thing without blocking. */
		byte_t const *mnode_minaddr, *mnode_maxaddr;
		mnode_minaddr = lonode->mn_minaddr;
		mnode_maxaddr = lonode->mn_maxaddr;
		mman_lock_release(self);
		unlockinfo_xunlock(unlock);
		result = false;
		hinode = (struct mnode *)kmalloc(sizeof(struct mnode), GFP_ATOMIC);
		TRY {
			mman_lock_acquire(self);
		} EXCEPT {
			kfree(hinode);
			RETHROW();
		}
		/* Check if anything changed in the mean time. */
reload_lonode_after_mman_lock:
		lonode = mnode_tree_locate(self->mm_mappings, mnode_minaddr);
		if ((lonode == NULL) ||
		    (lonode->mn_minaddr != mnode_minaddr) ||
		    (lonode->mn_maxaddr != mnode_maxaddr) ||
		    (lonode->mn_flags & MNODE_F_NO_SPLIT))
			goto err_changed_free_hinode;
	}

	/* Fill in fields of `hinode' from `lonode' */
	assert(lonode->mn_mman == self);
	part               = lonode->mn_part;
	hinode->mn_flags   = lonode->mn_flags;
	hinode->mn_minaddr = (byte_t *)addr_where_to_split;
	hinode->mn_maxaddr = lonode->mn_maxaddr;
	hinode->mn_part    = part; /* incref'd later! */
	hinode->mn_fspath  = xincref(lonode->mn_fspath);
	hinode->mn_fsname  = xincref(lonode->mn_fsname);
	hinode->mn_mman    = self;
	hinode->mn_partoff = lonode->mn_partoff + (size_t)((byte_t *)addr_where_to_split - lonode->mn_minaddr);

	/* At this point, we've managed to allocate the missing hi-node.
	 * Deal with the simple case where the original node doesn't have
	 * a backing mem-part (since in that case, we don't even need to
	 * acquire any additional locks) */
	if (part == NULL)
		goto done_nopart; /* Simple case */

	/* Must acquire a lock to the part so we can insert  */
	if (!mpart_lock_tryacquire(part)) {
		/* Must blocking-wait for the part to become available. */
		incref(part);
		mman_lock_release(self);
		if (result) {
			unlockinfo_xunlock(unlock);
			result = false;
		}
		xdecref(hinode->mn_fspath);
		xdecref(hinode->mn_fsname);
		{
			FINALLY_DECREF_UNLIKELY(part);
			while (!mpart_lock_available(part))
				task_yield();
		}
		mman_lock_acquire(self);
		goto reload_lonode_after_mman_lock;
	}

	/* Insert the new mem-node into the backing part's list of either
	 * copy-on-write, or shared mappings. */
	if (hinode->mn_flags & MNODE_F_SHARED) {
		LIST_INSERT_HEAD(&part->mp_share, hinode, mn_link);
	} else {
		LIST_INSERT_HEAD(&part->mp_copy, hinode, mn_link);
	}
	mpart_lock_release(part);
	incref(part); /* The reference stored in `hinode->mn_part' */
done_nopart:
	/* Copy the is-writable attribute form `lonode' into `hinode' */
	LIST_ENTRY_UNBOUND_INIT(hinode, mn_writable);
	if (LIST_ISBOUND(lonode, mn_writable))
		LIST_INSERT_HEAD(&self->mm_writable, hinode, mn_writable);

	/* Update the existing node, and re-insert both nodes into the mman. */
	mnode_tree_removenode(&self->mm_mappings, lonode);
	lonode->mn_maxaddr = (byte_t *)addr_where_to_split - 1;
	mnode_tree_insert(&self->mm_mappings, lonode);
	mnode_tree_insert(&self->mm_mappings, hinode);

	/* If we had to unlock stuff above, release our lock to the mman to
	 * keep things consistent with the false-result-means-no-locks invariant. */
	if (!result)
		mman_lock_release(self);
	return result;
err_changed_free_hinode:
	kfree(hinode);
	return false;
}


/* Mem-node tree API. All of these functions require that the caller
 * be holding a lock to the associated mman. */
DECL_END

#undef RBTREE_LEFT_LEANING
#define RBTREE_WANT_PREV_NEXT_NODE
#define RBTREE(name)           mnode_tree_##name
#define RBTREE_T               struct mnode
#define RBTREE_Tkey            void const *
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

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MNODE_C */
