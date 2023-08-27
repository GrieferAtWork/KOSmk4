/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MNODE_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MNODE_C 1
#define __WANT_MPART__mp_nodlsts
#define __WANT_MNODE__mn_dead  /* Only to assert offsets */
#define __WANT_MNODE__mn_alloc /* Only to assert offsets */
#define __WANT_MNODE__mn_ilink /* Only to assert offsets */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/entry.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/path.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/mcoreheap.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/module.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/sync.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <sched/task.h>

#include <hybrid/align.h>

#include <kos/except.h>
#include <kos/lockop.h>

#include <assert.h>
#include <atomic.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Check if 2 given ranges overlap (that is: share at least 1 common address) */
#define RANGE_OVERLAPS(a_min, a_max, b_min, b_max) \
	((a_max) >= (b_min) && (a_min) <= (b_max))


/* `struct mnode' offsets */
static_assert(offsetof(struct mnode, mn_mement) == OFFSET_MNODE_MEMENT);
static_assert(offsetof(struct mnode, mn_mement.rb_par) == OFFSET_MNODE_MEMENT_PAR);
static_assert(offsetof(struct mnode, mn_mement.rb_lhs) == OFFSET_MNODE_MEMENT_LHS);
static_assert(offsetof(struct mnode, mn_mement.rb_rhs) == OFFSET_MNODE_MEMENT_RHS);
static_assert(offsetof(struct mnode, _mn_dead) == OFFSET_MNODE__DEAD);
static_assert(offsetof(struct mnode, mn_minaddr) == OFFSET_MNODE_MINADDR);
static_assert(offsetof(struct mnode, mn_maxaddr) == OFFSET_MNODE_MAXADDR);
static_assert(offsetof(struct mnode, mn_flags) == OFFSET_MNODE_FLAGS);
static_assert(offsetof(struct mnode, mn_part) == OFFSET_MNODE_PART);
static_assert(offsetof(struct mnode, mn_fspath) == OFFSET_MNODE_FSPATH);
static_assert(offsetof(struct mnode, mn_fsname) == OFFSET_MNODE_FSNAME);
static_assert(offsetof(struct mnode, mn_mman) == OFFSET_MNODE_MMAN);
static_assert(offsetof(struct mnode, _mn_alloc) == OFFSET_MNODE__ALLOC);
static_assert(offsetof(struct mnode, mn_partoff) == OFFSET_MNODE_PARTOFF);
static_assert(offsetof(struct mnode, mn_link) == OFFSET_MNODE_LINK);
static_assert(offsetof(struct mnode, mn_link.le_next) == OFFSET_MNODE_LINK_NEXT);
static_assert(offsetof(struct mnode, mn_link.le_prev) == OFFSET_MNODE_LINK_PREV);
static_assert(offsetof(struct mnode, mn_writable) == OFFSET_MNODE_WRITABLE);
static_assert(offsetof(struct mnode, mn_writable.le_next) == OFFSET_MNODE_WRITABLE_NEXT);
static_assert(offsetof(struct mnode, mn_writable.le_prev) == OFFSET_MNODE_WRITABLE_PREV);
static_assert(offsetof(struct mnode, _mn_iswritable) == OFFSET_MNODE__ISWRITABLE);
static_assert(offsetof(struct mnode, _mn_iswritable) == OFFSET_MNODE__ISWRITABLE);
static_assert(offsetof(struct mnode, _mn_ilink) == OFFSET_MNODE__ILINK);
static_assert(offsetof(struct mnode, mn_module) == OFFSET_MNODE_MODULE);
static_assert(sizeof(struct mnode) == SIZEOF_MNODE);
static_assert(alignof(struct mnode) == ALIGNOF_MNODE);


/* Free/destroy a given mem-node */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mnode_free)(struct mnode *__restrict self) {
	if (self->mn_flags & MNODE_F_COREPART) {
		mcoreheap_free(container_of(self, union mcorepart, mcp_node));
	} else {
		kfree(self);
	}
}



INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_maybe_clear_mlock)(struct mpart *__restrict self) {
	/* Check if  there are  any nodes  mapping our  part that  use LOCK  flags.
	 * For this purpose, both copy-on-write and shared nodes can lock the part. */
	unsigned int i;
	for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
		struct mnode *node;
		LIST_FOREACH (node, &self->_mp_nodlsts[i], mn_link) {
			if (node->mn_flags & MNODE_F_MLOCK)
				return;
		}
	}

	/* Clear the lock-flag for our part, since there are no
	 * more nodes that could keep our part locked  in-core! */
	atomic_and_release(&self->mp_flags, ~MPART_F_MLOCK);
}



PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mnode_unlink_from_part_lockop_post)(Tobpostlockop(mpart) *__restrict self,
                                                  REF struct mpart *__restrict part) {
	struct mnode *me;
	me = (struct mnode *)self;
	weakdecref(me->mn_mman);
	mpart_trim(part); /* This also inherits our reference to `part' */
	mnode_free(me);
}

INTERN NOBLOCK NONNULL((1, 2)) Tobpostlockop(mpart) *
NOTHROW(FCALL mnode_unlink_from_part_lockop)(Toblockop(mpart) *__restrict self,
                                             REF struct mpart *__restrict part) {
	Tobpostlockop(mpart) *post;
	struct mnode *me;
	me = (struct mnode *)self;
	LIST_REMOVE(me, mn_link);
	if ((me->mn_flags & (MNODE_F_MLOCK)) &&
	    (part->mp_flags & (MPART_F_MLOCK | MPART_F_MLOCK_FROZEN)) == MPART_F_MLOCK)
		mpart_maybe_clear_mlock(part);

	/* Do the rest in post so we won't be holding a lock to the mem-part anymore:
	 * >> weakdecref(me->mn_mman);
	 * >> mnode_free(me); */
	post            = (Tobpostlockop(mpart) *)self;
	post->oplo_func = &mnode_unlink_from_part_lockop_post;
	return post;
}



PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mnode_destroy)(struct mnode *__restrict self) {
	REF struct mpart *part;
	assertf((self->mn_flags & MNODE_F_UNMAPPED) || wasdestroyed(self->mn_mman),
	        "A mem-node may only be destroyed if it's marked as UNMAPPED, "
	        "or belongs to a dead memory manager");

	xdecref(self->mn_fspath);
	xdecref(self->mn_fsname);
	part = self->mn_part;
	DBG_memset(&self->mn_part, 0xcc, sizeof(self->mn_part));
	if (part != NULL) {
		/* Try to unlink the node from the copy- or share-chain of the associated part. */
		if (mpart_lock_tryacquire(part)) {
			LIST_REMOVE(self, mn_link);
			if ((self->mn_flags & (MNODE_F_MLOCK)) &&
			    (part->mp_flags & (MPART_F_MLOCK | MPART_F_MLOCK_FROZEN)) == MPART_F_MLOCK)
				mpart_maybe_clear_mlock(part);
			mpart_lock_release(part);
			mpart_trim(part); /* This also inherits our reference to `part' */
		} else {
			Toblockop(mpart) *lop;

			/* Must insert the node into the part's list of deleted nodes. */
			weakincref(self->mn_mman); /* A weak reference here is required by the ABI */

			/* Insert into  the lock-operations  list of  `part'
			 * The act of doing this is what essentially  causes
			 * ownership of our node to be transferred to `part'
			 * Additionally,   `mnode_unlink_from_part_lockop()'
			 * inherits our reference to `part'! */
			lop = (Toblockop(mpart) *)self;
			lop->olo_func = &mnode_unlink_from_part_lockop;
			SLIST_ATOMIC_INSERT(&part->mp_lockops, lop, olo_link);

			/* Try to reap dead nodes. */
			_mpart_lockops_reap(part);
			return;
		}
	}
	mnode_free(self);
}


#ifndef NDEBUG
/* Assert the integrity of the given mem-node.
 * The caller must be holding a lock to `self->mn_mman' (or the mman must be destroyed). */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mnode_assert_integrity)(struct mnode *__restrict self) {
#if 0
	(void)self;
	COMPILER_IMPURE();
#else
	assert(mman_lock_acquired(self->mn_mman) || wasdestroyed(self->mn_mman) || dbg_active);
	assertf((self->mn_flags & MNODE_F_COREPART) || kmalloc_islocked(self),
	        "Descriptor of mem-node at %p is not locked into memory", self);
	assertf(self->mn_maxaddr > self->mn_minaddr,
	        "Invalid min/max addr range:\n"
	        "self->mn_minaddr = %#" PRIxPTR "\n"
	        "self->mn_maxaddr = %#" PRIxPTR "",
	        self->mn_minaddr, self->mn_maxaddr);
	assertf(IS_ALIGNED((uintptr_t)self->mn_minaddr, PAGESIZE),
	        "Node %p-%p min address it not page-aligned",
	        mnode_getminaddr(self),
	        mnode_getmaxaddr(self));
	assertf(IS_ALIGNED((uintptr_t)self->mn_maxaddr + 1, PAGESIZE),
	        "Node %p-%p max address it not page-aligned",
	        mnode_getminaddr(self),
	        mnode_getmaxaddr(self));

	/* If there is a part, ensure that the mapped range fits inside. */
	if (self->mn_part) {
		mpart_reladdr_t part_size;
		mpart_reladdr_t node_partend;
		assertf(IS_ALIGNED(self->mn_partoff, PAGESIZE),
		        "Node %p-%p part offset %#" PRIxSIZ " is not page-aligned",
		        mnode_getminaddr(self),
		        mnode_getmaxaddr(self),
		        self->mn_partoff);

		node_partend = mnode_getpartendaddr(self);
		part_size    = mpart_getsize(self->mn_part);
		assertf(node_partend <= part_size,
		        "Address range mapped by node %p-%p goes beyond end of part:\n"
		        "node: %#" PRIxSIZ "-%#" PRIxSIZ "\n"
		        "part: 0x0-%#" PRIxSIZ "",
		        mnode_getminaddr(self),
		        mnode_getmaxaddr(self),
		        mnode_getpartminaddr(self),
		        mnode_getpartmaxaddr(self),
		        part_size - 1);

		/* Kernel parts don't necessarily have to appear in their part's node lists. */
		if (!(self->mn_flags & MNODE_F_KERNPART)) {
			do {
				struct mnode_list *mylist;
				struct mnode *iter;
				mylist = mpart_getnodlst_from_mnodeflags(self->mn_part, self->mn_flags);
				iter   = LIST_FIRST(mylist);
				while (iter && iter != self)
					iter = LIST_NEXT(iter, mn_link);
				if (iter == self)
					break;
			} while (__assertion_checkf(NULL, "Node %p-%p does not appear in %s-list of part %p\n",
			                            mnode_getminaddr(self),
			                            mnode_getmaxaddr(self),
			                            self->mn_flags & MNODE_F_SHARED ? "shared" : "copy",
			                            self->mn_part));
		}

		/* When the node is mlock'd, then the part has to be, too (unless the part is frozen as munlock'd) */
		if (self->mn_flags & MNODE_F_MLOCK) {
			assertf((self->mn_part->mp_flags & MPART_F_MLOCK) ||
			        (self->mn_part->mp_flags & MPART_F_MLOCK_FROZEN),
			        "Node %p-%p is mlock'd, but assigned part %p isn't",
			        mnode_getminaddr(self),
			        mnode_getmaxaddr(self),
			        self->mn_part);
		}
	}

	if (self->mn_flags & MNODE_F_MHINT) {
		/* Assert all of the invariants required from hinted nodes. */
		struct mnode_list *mylist;
		assert(self->mn_mman == &mman_kernel);
		assert(self->mn_part != NULL);
		mylist = mpart_getnodlst_from_mnodeflags(self->mn_part, self->mn_flags);
		assert(!LIST_EMPTY(mylist));
		assert(LIST_FIRST(mylist) == self);
		assert(self->mn_link.le_prev == LIST_PFIRST(mylist));
		assert(self->mn_link.le_next == NULL);
		assert(mpart_isanon(self->mn_part));
		assert(self->mn_part->mp_file->mf_ops->mo_loadblocks != NULL);
		assert(self->mn_part->mp_file->mf_blockshift == PAGESHIFT);
		assert(mfile_isanon(self->mn_part->mp_file));
		assert(MPART_ST_INMEM(self->mn_part->mp_state));
	}

	if (self->mn_module) {
		assertf(self->mn_module->md_mman == self->mn_mman,
		        "Module %p[mman:%p] pointed-to be node %p[mman:%p] "
		        "at %p-%p belongs to different mman",
		        self->mn_module, self->mn_module->md_mman, self, self->mn_mman,
		        mnode_getminaddr(self), mnode_getmaxaddr(self));
		assertf(self->mn_module->md_nodecount != 0,
		        "Node-counter of module %p pointed-to be node %p at %p-%p is zero",
		        self->mn_module, self,
		        mnode_getminaddr(self), mnode_getmaxaddr(self));
	}
#endif
}
#endif /* !NDEBUG */



/* Clear page-directory-level write-access to `self'. This function must  be
 * called for all writable memory mappings of a MMAN when the MMAN is cloned
 * or a copy-on-write  mapping is created  for an already-shared  `mn_part':
 * >> mmap() {
 * >>     ...
 * >>     if (flags & MNODE_F_SHARED) {
 * >>         ...
 * >>     } else {
 * >>         if (part->mp_copy == NULL) {
 * >>             LIST_FOREACH (node, &part->mp_share, mn_link) {
 * >>                 mnode_clear_write(node);
 * >>             }
 * >>         } else if (LIST_NEXT(part->mp_copy, mn_link) != NULL &&
 * >>                    mpart_isanon(part)) {
 * >>             // This is what would happen during a fork()
 * >>             mnode_clear_write(part->mp_copy);
 * >>         }
 * >>     }
 * >> }
 * NOTE: This function is designed to be called while the caller is
 *       already holding a lock to the node's associated  mem-part.
 * @return: * : One of `MNODE_CLEAR_WRITE_*' */
PUBLIC NOBLOCK NONNULL((1)) unsigned int
NOTHROW(FCALL mnode_clear_write)(struct mnode *__restrict self) {
	unsigned int result;
	struct mman *mm = self->mn_mman;
	if (!LIST_ISBOUND(self, mn_writable)) {
		/* Simple case: this node isn't writable.
		 * This is thread-safe,  since our caller  is currently holding  a
		 * lock to the associated mem-part, and for this node to (re-)gain
		 * write access, it would first have to acquire that same lock.
		 *
		 * As  such, if it's  not writable now, then  it can't become so
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
		result = mnode_clear_write_locked_p(self, mm);
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

PUBLIC NOBLOCK NONNULL((1)) unsigned int
NOTHROW(FCALL mnode_clear_write_r)(struct mnode *__restrict self,
                                   size_t noderel_offset,
                                   size_t num_bytes) {
	unsigned int result;
	struct mman *mm = self->mn_mman;
	if (!LIST_ISBOUND(self, mn_writable)) {
		/* Simple case: this node isn't writable.
		 * This is thread-safe,  since our caller  is currently holding  a
		 * lock to the associated mem-part, and for this node to (re-)gain
		 * write access, it would first have to acquire that same lock.
		 *
		 * As  such, if it's  not writable now, then  it can't become so
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
		result = mnode_clear_write_locked_p_r(self, mm, noderel_offset, num_bytes);
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
 * and  this  function  will  never  return  with `MNODE_CLEAR_WRITE_WOULDBLOCK'.
 * NOTE: Unlike with `mnode_clear_write', when calling this function,
 *       the caller must ensure that:
 *        - !wasdestroyed(mm)
 *        - mman_lock_acquired(mm)
 *        - self->mn_part != NULL
 *        - LIST_ISBOUND(self, mn_writable)
 * Also note that the caller is responsible to sync `mm' before unlocking it! */
PUBLIC NOBLOCK NONNULL((1, 2)) unsigned int
NOTHROW(FCALL mnode_clear_write_locked_p)(struct mnode *__restrict self,
                                          struct mman *__restrict mm) {
	pagedir_phys_t pdir;
	void *addr;
	size_t size;
	assert(!wasdestroyed(mm));
	assert(mman_lock_acquired(mm));
	assert(self->mn_part != NULL);
	assert(LIST_ISBOUND(self, mn_writable));
	assertf(self->mn_flags & MNODE_F_PWRITE,
	        "How could we have been added to the list of writable nodes "
	        "when we're not actually supposed to be writable at all?");
	assertf(!(self->mn_flags & MNODE_F_MPREPARED),
	        "This function should only be called for user-space nodes, "
	        "and user-space nodes should never have the MPREPARED bit set");

	pdir = mm->mm_pagedir_p;
	addr = mnode_getaddr(self);
	size = mnode_getsize(self);

	/* Prepare the page directory */
	if unlikely(!pagedir_prepare_p(pdir, addr, size))
		return MNODE_CLEAR_WRITE_BADALLOC;

	/* Delete write permissions. */
#ifdef ARCH_PAGEDIR_HAVE_DENYWRITE
	pagedir_denywrite_p(pdir, addr, size);
#else /* ARCH_PAGEDIR_HAVE_DENYWRITE */
	pagedir_unmap_p(pdir, addr, size); /* Mapping will be re-created lazily! */
#endif /* !ARCH_PAGEDIR_HAVE_DENYWRITE */

	/* Unprepare the page directory. */
	pagedir_unprepare_p(pdir, addr, size);

	/* Unlink from the list of writable nodes. */
	LIST_UNBIND(self, mn_writable);
	return MNODE_CLEAR_WRITE_SUCCESS;
}

PUBLIC NOBLOCK NONNULL((1, 2)) unsigned int
NOTHROW(FCALL mnode_clear_write_locked_p_r)(struct mnode *__restrict self,
                                            struct mman *__restrict mm,
                                            size_t noderel_offset,
                                            size_t num_bytes) {
	pagedir_phys_t pdir;
	void *addr;
	assert(!wasdestroyed(mm));
	assert(mman_lock_acquired(mm));
	assert(self->mn_part != NULL);
	assert(LIST_ISBOUND(self, mn_writable));
	assertf(self->mn_flags & MNODE_F_PWRITE,
	        "How could we have been added to the list of writable nodes "
	        "when we're not actually supposed to be writable at all?");
	assertf(!(self->mn_flags & MNODE_F_MPREPARED),
	        "This function should only be called for user-space nodes, "
	        "and user-space nodes should never have the MPREPARED bit set");
	assert((noderel_offset + num_bytes) >= noderel_offset);
	assert((noderel_offset + num_bytes) <= mnode_getsize(self));

	pdir = mm->mm_pagedir_p;
	addr = (byte_t *)mnode_getaddr(self) + noderel_offset;

	/* Force page-alignment. */
	if unlikely((uintptr_t)addr & PAGEMASK) {
		num_bytes += (uintptr_t)addr & PAGEMASK;
		addr = (void *)((uintptr_t)addr & ~PAGEMASK);
	}
	if unlikely(num_bytes & PAGEMASK) {
		num_bytes += PAGEMASK;
		num_bytes &= ~PAGEMASK;
	}

	/* Check for special case: it's the entire node. */
	if (addr == mnode_getaddr(self) && num_bytes == mnode_getsize(self))
		return mnode_clear_write_locked_p(self, mm);

	/* Prepare the page directory */
	if unlikely(!pagedir_prepare_p(pdir, addr, num_bytes))
		return MNODE_CLEAR_WRITE_BADALLOC;

	/* Delete write permissions. */
#ifdef ARCH_PAGEDIR_HAVE_DENYWRITE
	pagedir_denywrite_p(pdir, addr, num_bytes);
#else /* ARCH_PAGEDIR_HAVE_DENYWRITE */
	pagedir_unmap_p(pdir, addr, num_bytes); /* Mapping will be re-created lazily! */
#endif /* !ARCH_PAGEDIR_HAVE_DENYWRITE */

	/* Unprepare the page directory. */
	pagedir_unprepare_p(pdir, addr, num_bytes);

	/* Don't unlink from the list of writable nodes (since part of the node is still writable). */
	/*LIST_UNBIND(self, mn_writable);*/
	return MNODE_CLEAR_WRITE_SUCCESS;
}



/* Same as  `mnode_clear_write_locked_p()', but  directory
 * operate on the current page directory / memory manager. */
PUBLIC NOBLOCK NONNULL((1)) unsigned int
NOTHROW(FCALL mnode_clear_write_locked)(struct mnode *__restrict self) {
	void *addr;
	size_t size;
	assert(self->mn_part != NULL);
	assert(LIST_ISBOUND(self, mn_writable));
	assertf(self->mn_flags & MNODE_F_PWRITE,
	        "How could we have been added to the list of writable nodes "
	        "when we're not actually supposed to be writable at all?");
	assertf(!(self->mn_flags & MNODE_F_MPREPARED),
	        "This function should only be called for user-space nodes, "
	        "and user-space nodes should never have the MPREPARED bit set");

	addr = mnode_getaddr(self);
	size = mnode_getsize(self);

	/* Prepare the page directory */
	if unlikely(!pagedir_prepare(addr, size))
		return MNODE_CLEAR_WRITE_BADALLOC;

	/* Delete write permissions. */
#ifdef ARCH_PAGEDIR_HAVE_DENYWRITE
	pagedir_denywrite(addr, size);
#else /* ARCH_PAGEDIR_HAVE_DENYWRITE */
	pagedir_unmap(addr, size); /* Mapping will be re-created lazily! */
#endif /* !ARCH_PAGEDIR_HAVE_DENYWRITE */

	/* Unprepare the page directory. */
	pagedir_unprepare(addr, size);

	/* Unlink from the list of writable nodes. */
	LIST_UNBIND(self, mn_writable);
	return MNODE_CLEAR_WRITE_SUCCESS;
}


/* Split `lonode' (which contains `addr_where_to_split') at that address.  If
 * this cannot be done without blocking, unlock and eventually return `false' */
PUBLIC WUNUSED NONNULL((1, 2)) bool FCALL
mnode_split_or_unlock(struct mman *__restrict self,
                      struct mnode *__restrict lonode,
                      PAGEDIR_PAGEALIGNED void const *addr_where_to_split,
                      struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	bool result = true;
	struct mnode *hinode;
	struct mpart *part;
	byte_t const *lonode_minaddr, *lonode_maxaddr;
	assert((byte_t const *)addr_where_to_split >= (byte_t const *)mnode_getaddr(lonode));
	assert((byte_t const *)addr_where_to_split < (byte_t const *)mnode_getendaddr(lonode));

	/* Safety check: panic if the specified node isn't allowed to be split. */
	if unlikely(lonode->mn_flags & MNODE_F_NOSPLIT) {
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
		lonode_minaddr = lonode->mn_minaddr;
		lonode_maxaddr = lonode->mn_maxaddr;
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
		lonode = mnode_tree_locate(self->mm_mappings, lonode_minaddr);
		if ((lonode == NULL) ||
		    (lonode->mn_minaddr != lonode_minaddr) ||
		    (lonode->mn_maxaddr != lonode_maxaddr) ||
		    (lonode->mn_flags & MNODE_F_NOSPLIT))
			goto err_changed_free_hinode;
	}

	/* Fill in fields of `hinode' from `lonode' */
	assert(lonode->mn_mman == self);
	part               = lonode->mn_part;
	hinode->mn_flags   = lonode->mn_flags & ~MNODE_F_COREPART;
	hinode->mn_minaddr = (byte_t *)addr_where_to_split;
	hinode->mn_maxaddr = lonode->mn_maxaddr;
	hinode->mn_part    = part; /* incref'd later! */
	hinode->mn_fspath  = xincref(lonode->mn_fspath);
	hinode->mn_fsname  = xincref(lonode->mn_fsname);
	hinode->mn_mman    = self;
	hinode->mn_partoff = lonode->mn_partoff + (size_t)((byte_t *)addr_where_to_split - lonode->mn_minaddr);
	hinode->mn_module  = lonode->mn_module;
	if (hinode->mn_module)
		module_inc_nodecount(hinode->mn_module);

	/* At this point, we've managed to allocate the missing  hi-node.
	 * Deal with the simple case where the original node doesn't have
	 * a backing mem-part (since in that case, we don't even need  to
	 * acquire any additional locks) */
	if (part == NULL)
		goto done_nopart; /* Simple case */

	/* Must acquire a lock to the part so we can insert  */
	if (!mpart_lock_tryacquire(part)) {
		/* Must blocking-wait for the part to become available. */
		incref(part);
		lonode_minaddr = lonode->mn_minaddr;
		lonode_maxaddr = lonode->mn_maxaddr;
		if (hinode->mn_module) {
			assert(hinode->mn_module->md_nodecount >= 2);
			--hinode->mn_module->md_nodecount;
		}
		DBG_memset(&hinode->mn_module, 0xcc, sizeof(hinode->mn_module));
		mman_lock_release(self);
		if (result) {
			unlockinfo_xunlock(unlock);
			result = false;
		}
		xdecref(hinode->mn_fspath);
		xdecref(hinode->mn_fsname);
		{
			FINALLY_DECREF_UNLIKELY(part);
			mpart_lock_waitfor(part);
		}
		mman_lock_acquire(self);
		goto reload_lonode_after_mman_lock;
	}

	/* Insert  the new mem-node  into the backing part's
	 * list of either copy-on-write, or shared mappings. */
	{
		struct mnode_list *list;
		list = mpart_getnodlst_from_mnodeflags(part, hinode->mn_flags);
		LIST_INSERT_HEAD(list, hinode, mn_link);
	}
	mpart_lock_release(part);
	incref(part); /* The reference stored in `hinode->mn_part' */
done_nopart:

	/* Copy the is-writable attribute form `lonode' into `hinode' */
	LIST_ENTRY_UNBOUND_INIT(&hinode->mn_writable);
	if (LIST_ISBOUND(lonode, mn_writable))
		LIST_INSERT_HEAD(&self->mm_writable, hinode, mn_writable);

	/* Update the existing node, and re-insert both nodes into the mman. */
	mman_mappings_removenode(self, lonode);
	lonode->mn_maxaddr = (byte_t *)addr_where_to_split - 1;
	mman_mappings_insert_and_verify(self, lonode);
	mman_mappings_insert_and_verify(self, hinode);

	/* If we had  to unlock  stuff above,  release our  lock to  the mman  to
	 * keep things consistent with the false-result-means-no-locks invariant. */
	if (!result)
		mman_lock_release(self);
	return result;
err_changed_free_hinode:
	mman_lock_release(self);
	kfree(hinode);
	return false;
}



/* Mem-node tree API. All of these functions require that the caller
 * be holding a lock to the associated mman. */
DECL_END

#undef RBTREE_LEFT_LEANING
#define RBTREE_WANT_MINMAXLOCATE
#define RBTREE_WANT_PREV_NEXT_NODE
#define RBTREE_WANT_RREMOVE
#define RBTREE_WANT_RLOCATE
#define RBTREE_WANT_TRYINSERT
#define RBTREE_MINMAX_T_DEFINED
#define mnode_tree_minmax_t    struct mnode_tree_minmax
#define RBTREE(name)           mnode_tree_##name
#define RBTREE_T               struct mnode
#define RBTREE_Tkey            VIRT void const *
#define RBTREE_GETNODE(self)   (self)->mn_mement
#define RBTREE_GETMINKEY(self) mnode_getminaddr(self)
#define RBTREE_GETMAXKEY(self) mnode_getmaxaddr(self)
#define RBTREE_REDFIELD        mn_flags
#define RBTREE_REDBIT          MNODE_F__RBRED
#define RBTREE_CC              FCALL
#define RBTREE_NOTHROW         NOTHROW
#define RBTREE_DECL            FUNDEF
#define RBTREE_IMPL            PUBLIC
#include <hybrid/sequence/rbtree-abi.h>

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MNODE_C */
