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
#ifndef GUARD_KERNEL_CORE_FILESYS_SUPER_C
#define GUARD_KERNEL_CORE_FILESYS_SUPER_C 1
#define __WANT_FSUPER__fs_changedsuper_lop
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/allnodes.h>
#include <kernel/fs/filesys.h>
#include <kernel/fs/super.h>

#include <hybrid/atomic.h>

#include <kos/except.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

DECL_BEGIN

PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(LOCKOP_CC fsuper_add2changed_lop)(struct lockop *__restrict self) {
	/* Insert into the changed list (our caller is holding its lock) */
	REF struct fsuper *me = container_of(self, struct fsuper, _fs_changedsuper_lop);
	LIST_INSERT_HEAD(&fchangedsuper_list, me, fs_changedsuper);
	return NULL;
}



/* Helper function to asynchronously add a given super-block to the list of changed superblocks.
 * @return: true:  Superblock was added to the changed list, or will be added asynchronously.
 * @return: false: Superblock was already added to the changed list, or a async request to
 *                 perform the addition has already been enqueued. */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL fsuper_add2changed)(struct fsuper *__restrict self) {
	bool result = false;
	/* Quick check: was it already marked as changed? */
#ifndef __OPTIMIZE_SIZE__
	if (!fsuper_haschanged(self))
#endif /* !__OPTIMIZE_SIZE__ */
	{
		STATIC_ASSERT_MSG(offsetof(struct fsuper, fs_changedsuper.le_prev) ==
		                  offsetof(struct fsuper, _fs_changedsuper_lop.lo_func),
		                  "This is required for the ATOMIC_CMPXCH below to "
		                  "be thread- and async-safe");

		/* Try to acquire a lock to the list of changed superblocks */
		if (fchangedsuper_tryacquire()) {
			COMPILER_BARRIER();
			if (!LIST_ISBOUND(self, fs_changedsuper)) {
				incref(self);
				LIST_INSERT_HEAD(&fchangedsuper_list, self, fs_changedsuper);
				result = true;
			}
			fchangedsuper_release();
		} else {
			/* Try to do the addition asynchronously. */
			if (ATOMIC_CMPXCH(self->_fs_changedsuper_lop.lo_func,
			                  NULL, &fsuper_add2changed_lop)) {
				incref(self);
				result = true;
				/* Enqueue an async lockop. */
				lockop_enqueue(&fchangedsuper_lockops, &self->_fs_changedsuper_lop);

				/* Reap to prevent race conditions. */
				_fchangedsuper_reap();
			}
		}
	}
	return result;
}


/* #1: Remove `self' from the list of changed superblocks (if not done already)
 * #2: Write modified data and attributes of all changed fnode-s to disk.
 * #3: Invoke the `so_sync' operator (if defined)
 * If an exception is thrown during step #2 or #3, re-add `self' to the list of changed superblocks */
PUBLIC NONNULL((1)) void KCALL
fsuper_sync(struct fsuper *__restrict self)
		THROWS(E_WOULDBLOCK, E_IOERROR, ...) {
	COMPILER_BARRIER();
	if (LIST_ISBOUND(self, fs_changedsuper)) {
		fchangedsuper_acquire();
		COMPILER_BARRIER();
		if (LIST_ISBOUND(self, fs_changedsuper)) {
			LIST_UNBIND(self, fs_changedsuper);
			decref_nokill(self);
		}
		fchangedsuper_release();
	}
	TRY {
		COMPILER_BARRIER();
		while (!LIST_EMPTY(&self->fs_changednodes)) {
			uintptr_t changes;
			REF struct fnode *changed_node;
			fsuper_changednodes_lock_acquire(self);
			COMPILER_BARRIER();
			changed_node = LIST_FIRST(&self->fs_changednodes);
			if (changed_node != NULL)
				LIST_UNBIND(changed_node, fn_changed);
			COMPILER_BARRIER();
			fsuper_changednodes_lock_release(self);
			if (!changed_node)
				break;
			assert(changed_node->fn_super == self);
			/* Sync changed parts of `changed_node' */
			changes = ATOMIC_FETCHAND(changed_node->mf_flags, ~(MFILE_F_CHANGED | MFILE_F_ATTRCHANGED));
			changes &= (MFILE_F_CHANGED | MFILE_F_ATTRCHANGED);
			TRY {
				if (changes & MFILE_F_CHANGED) {
					mfile_sync(changed_node);
					changes &= ~MFILE_F_CHANGED;
				}
				if (changes & MFILE_F_ATTRCHANGED) {
					struct fnode_ops const *ops;
					ops = fnode_getops(changed_node);
					(*ops->no_wrattr)(changed_node);
					changes &= ~MFILE_F_ATTRCHANGED;
				}
			} EXCEPT {
				/* Upon error, re-mark elements we couldn't sync as changed. */
				mfile_changed(changed_node, changes);
				decref_unlikely(changed_node);
				RETHROW();
			}
			decref_unlikely(changed_node);
		}
		COMPILER_BARRIER();


		/* Invoke the `so_sync' operator. */
		{
			struct fsuper_ops const *ops;
			ops = fsuper_getops(self);
			if (ops->so_sync != NULL)
				(*ops->so_sync)(self);
		}
	} EXCEPT {
		/* Upon error, re-add the superblock to the list of changed ones. */
		fsuper_add2changed(self);
		RETHROW();
	}
}


/* Synchronize all superblocks containing changed fnode-s (s.a. `fchangedsuper_list') */
PUBLIC void KCALL fsuper_syncall(void)
		THROWS(E_WOULDBLOCK, E_IOERROR, ...) {
	while (!LIST_EMPTY(&fchangedsuper_list)) {
		REF struct fsuper *changed_superblock;
		COMPILER_BARRIER();
		fchangedsuper_acquire();
		changed_superblock = LIST_FIRST(&fchangedsuper_list);
		if (changed_superblock != NULL)
			LIST_UNBIND(changed_superblock, fs_changedsuper);
		fchangedsuper_release();
		if (!changed_superblock)
			break;
		FINALLY_DECREF_UNLIKELY(changed_superblock);
		fsuper_sync(changed_superblock);
		COMPILER_BARRIER();
	}
}


/* Default operators for `struct fsuper_ops' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fsuper_v_destroy)(struct mfile *__restrict self) {
	struct fsuper *me = mfile_assuper(self);

	/* Validate that the superblock is in a state where it can safely be destroyed. */
	assert(SLIST_EMPTY(&me->fs_mountslockops));
	assert(SLIST_EMPTY(&me->fs_changednodes_lops));
	assert(SLIST_EMPTY(&me->fs_nodeslockops));
	assert(atomic_rwlock_canwrite(&me->fs_nodeslock));
	assert(atomic_rwlock_canwrite(&me->fs_mountslock));
	assert(atomic_lock_available(&me->fs_changednodes_lock));
	assert(me->fs_changednodes.lh_first == NULL ||
	       me->fs_changednodes.lh_first == FSUPER_NODES_DELETED);
	assert(me->fs_nodes == NULL ||
	       me->fs_nodes == FSUPER_NODES_DELETED);
	assert(me->fs_mounts.lh_first == NULL);
	assert(LIST_ISBOUND(me, fs_changedsuper));

	/* Drop references */
	decref(me->fs_sys);
	xdecref(me->fs_dev);

	/* Continue destruction one level deeper */
	fdirnode_v_destroy(&me->fs_root);
}




DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_SUPER_C */
