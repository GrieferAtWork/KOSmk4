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
#include <kernel/mman/mpart.h>
#include <kernel/mman/mpartmeta.h>

#include <assert.h>
#include <stddef.h>

DECL_BEGIN


/* Destroy the given mem-futex. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL mfutex_destroy)(struct mfutex *__restrict self) {
	REF struct mpart *part;
	struct mpartmeta *meta;

	/* Broadcast the mem-futex one last time. */
	sig_broadcast_for_fini(&self->mfu_signal);

	part = self->mfu_part.m_pointer; /* Inherit reference */
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
	mfutex_free(self);
}

/* Same as `mfutex_destroy()', but _always_ enqueue the futex to-be reaped
 * lazily once `mpartmeta_deadftx_reap()' is called with the associated controller. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL mfutex_destroy_later)(struct mfutex *__restrict self) {
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


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MPARTMETA_C */
