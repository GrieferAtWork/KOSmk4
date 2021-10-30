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
#define __WANT_MFILE__mf_lop
#define __WANT_MFILE__mf_plop
#define __WANT_MFILE__mf_fsuperlop
#define __WANT_MFILE__mf_fsuperplop
#define __WANT_MFILE__mf_delfnodes
#define __WANT_FNODE__fn_alllop
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/allnodes.h>
#include <kernel/fs/blkdev.h>
#include <kernel/fs/filesys.h>
#include <kernel/fs/super.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <kos/except.h>
#include <sys/statfs.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

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
		while (self->fs_changednodes.lh_first != FSUPER_NODES_DELETED &&
		       !LIST_EMPTY(&self->fs_changednodes)) {
			uintptr_t changes;
			REF struct fnode *changed_node;
			fsuper_changednodes_acquire(self);
			COMPILER_BARRIER();
			changed_node = LIST_FIRST(&self->fs_changednodes);
			if (changed_node != NULL)
				LIST_UNBIND(changed_node, fn_changed);
			COMPILER_BARRIER();
			fsuper_changednodes_release(self);
			if (!changed_node)
				break;
			assert(changed_node->fn_super == self);

			/* Sync changed parts of `changed_node' */
			for (;;) {
				changes = ATOMIC_READ(changed_node->mf_flags);
				if (changes & MFILE_F_DELETED) {
					/* Don't handle changes for deleted files. */
					changes = 0;
					break;
				}
				if (ATOMIC_CMPXCH_WEAK(changed_node->mf_flags, changes,
				                       changes & ~(MFILE_F_CHANGED | MFILE_F_ATTRCHANGED)))
					break;
			}
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

		/* Sync the associated device file. */
		{
			struct blkdev *dev;
			dev = self->fs_dev;
			if (dev != NULL) {
				struct blkdev_ops const *ops;
				/* fnode_syncdata() would also work here, but that function
				 * only conditionally invokes  `bdo_sync', whereas we  have
				 * to  invoke that operator (if it exists) unconditionally!
				 *
				 * As such, just do a normal file sync, followed by always
				 * invoking the `bdo_sync' operator. */
				mfile_sync(dev);
				ops = blkdev_getops(dev);
				if (ops->bdo_sync != NULL)
					(*ops->bdo_sync)(dev);
			}
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
		/* TODO: `fchangedsuper_list' must be a TAILQ, and we must always take
		 *       the _LAST_ element  here. That way,  we can sync  filesystems
		 *       from least-recently-modified to  most-..., thus resulting  in
		 *       one filesystem's sync causing modifications to another.
		 *
		 * Yes: that makes sense; if a superblock is synced such that disk
		 * writes are made, then devfs is  marked as changed and would  be
		 * also be synced at a later point. */
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
PUBLIC NOBLOCK NONNULL((1)) void /* `kfree(fnode_assuper(self));' */
NOTHROW(KCALL fsuper_v_free)(struct fnode *__restrict self) {
	kfree(fnode_assuper(self));
}

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
	assertf(me->fs_changednodes.lh_first == NULL ||
	        me->fs_changednodes.lh_first == FSUPER_NODES_DELETED,
	        "Nodes would have references");
	assertf(me->fs_nodes == NULL ||
	        me->fs_nodes == FSUPER_NODES_DELETED,
	        "Nodes would have references");
	assertf(me->fs_mounts.lh_first == NULL ||
	        me->fs_mounts.lh_first == FSUPER_MOUNTS_DELETED,
	        "Mounting points would have references");
	assertf(!LIST_ISBOUND(me, fs_changedsuper),
	        "The changed-list would have a reference");

	/* Drop references */
	decref(me->fs_sys);
	xdecref(me->fs_dev);

	/* Continue destruction one level deeper */
	fdirnode_v_destroy(&me->fs_root);
}




/************************************************************************/
/* Async helpers for `fsuper_delete()'                                  */
/************************************************************************/

/* Begin deletion of `self' */
PRIVATE WUNUSED NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL mfile_begin_delete)(struct mfile *__restrict self) {
	uintptr_t old_flags;

	/* Delete global reference to the superblock. */
	if (ATOMIC_FETCHAND(self->mf_flags, ~(MFILE_FN_GLOBAL_REF |
	                                      MFILE_F_PERSISTENT)) &
	    MFILE_FN_GLOBAL_REF) {
		decref_nokill(self);
	}

	/* Mark the device as deleted (and make available use of the file fields) */
	mfile_tslock_acquire(self);
	old_flags = ATOMIC_FETCHOR(self->mf_flags,
	                           MFILE_F_DELETED | MFILE_F_NOATIME |
	                           MFILE_F_NOMTIME | MFILE_FN_NODIRATIME |
	                           MFILE_F_CHANGED | MFILE_F_ATTRCHANGED |
	                           MFILE_F_FIXEDFILESIZE | MFILE_FN_ATTRREADONLY |
	                           MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |
	                           MFILE_FS_NOSUID | MFILE_FS_NOEXEC |
	                           MFILE_F_READONLY);
	if (old_flags & MFILE_F_PERSISTENT)
		ATOMIC_AND(self->mf_flags, ~MFILE_F_PERSISTENT); /* Also clear the PERSISTENT flag */
	mfile_tslock_release(self);

	/* Already deleted, or deletion already in progress. */
	return (old_flags & MFILE_F_DELETED) == 0;
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LOCKOP_CC fnode_remove_from_allnodes_postlop)(struct postlockop *__restrict self) {
	REF struct fnode *me;
	me = container_of(self, struct fnode, _mf_plop);
	mfile_delete_impl(me);
}

PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(LOCKOP_CC fnode_remove_from_allnodes_lop)(struct lockop *__restrict self) {
	REF struct fnode *me;
	me = container_of(self, struct fnode, _mf_lop);
	COMPILER_READ_BARRIER();
	if unlikely(me->_fn_alllop.lo_func == &fnode_addtoall_lop) {
		/* Must let `fnode_addtoall_lop()' finish first! */
		me->_mf_lop.lo_func = &fnode_remove_from_allnodes_lop;
		lockop_enqueue(&fallnodes_lockops, &me->_mf_lop);
		return NULL;
	}
	if (LIST_ISBOUND(me, fn_allnodes))
		LIST_UNBIND(me, fn_allnodes);
	me->_mf_plop.plo_func = &fnode_remove_from_allnodes_postlop;
	return &me->_mf_plop;
}


/* Deletion implementation for file-nodes. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LOCKOP_CC fnode_delete_from_all_impl)(REF struct fnode *__restrict self) {
	/* Try to remove the node from the global list of all nodes. */
again_unbind_allnodes:
	COMPILER_READ_BARRIER();
	if (LIST_ISBOUND(self, fn_allnodes)) {
		if (fallnodes_tryacquire()) {
			COMPILER_READ_BARRIER();
			if unlikely(self->_fn_alllop.lo_func == &fnode_addtoall_lop) {
				fallnodes_release(); /* This should reap & invoke fnode_addtoall_lop() */
				goto again_unbind_allnodes;
			}
			if (LIST_ISBOUND(self, fn_allnodes))
				LIST_UNBIND(self, fn_allnodes);
			fallnodes_release();
		} else {
			self->_mf_lop.lo_func = &fnode_remove_from_allnodes_lop;
			lockop_enqueue(&fallnodes_lockops, &self->_mf_lop);
			_fallnodes_reap();
			return;
		}
	}

	/* Delete the mfile-portion. */
	mfile_delete_impl(self);
}



PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC fsuper_clearnodes_postlop)(Tobpostlockop(fsuper) *__restrict self,
                                             REF struct fsuper *__restrict me) {
	assert(self == &me->fs_root._mf_fsuperplop);
	(void)self;

	/* Finalize deletion of all nodes which were still alive within the node-tree. */
	while (me->fs_root._mf_delfnodes) {
		REF struct fnode *node    = me->fs_root._mf_delfnodes;
		me->fs_root._mf_delfnodes = node->_mf_delfnodes;
		fnode_delete_from_all_impl(node); /* This inherits the reference for us! */
	}

	/* Finalize deletion of the superblock by deleting the mfile backing its root directory. */
	mfile_delete_impl(&me->fs_root);
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC fsuper_clearnodes_tree)(struct fnode *__restrict tree,
                                          struct fsuper *__restrict self) {
	struct fnode *lhs, *rhs;
again:
	lhs = tree->fn_supent.rb_lhs;
	rhs = tree->fn_supent.rb_rhs;

	/* Mark this node as deleted */
	DBG_memset(&tree->fn_supent, 0xcc, sizeof(tree->fn_supent));
	ATOMIC_WRITE(tree->fn_supent.rb_rhs, FSUPER_NODES_DELETED);

	/* Try to get a reference to this tree-node. */
	if (tryincref(tree)) {
		/* Try to begin deletion of this file (unless it's already marked as deleted) */
		if (mfile_begin_delete(tree)) {
			/* Do the rest of the deletion later. */
			tree->_mf_delfnodes = self->fs_root._mf_delfnodes; /* Inherit referenece */
			self->fs_root._mf_delfnodes = tree;                /* Inherit referenece */
		} else {
			decref_unlikely(tree);
		}
	}

	/* Recursively scan the rest of the tree. */
	if (lhs) {
		if (rhs)
			fsuper_clearnodes_tree(rhs, self);
		tree = lhs;
		goto again;
	}
	if (rhs) {
		tree = rhs;
		goto again;
	}
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(fsuper) *
NOTHROW(LOCKOP_CC fsuper_clearnodes_lop)(Toblockop(fsuper) *__restrict self,
                                         REF struct fsuper *__restrict me) {
	assert(self == &me->fs_root._mf_fsuperlop);
	(void)self;
	COMPILER_READ_BARRIER();
	if (me->fs_nodes != FSUPER_NODES_DELETED) {
		if (me->fs_nodes != NULL)
			fsuper_clearnodes_tree(me->fs_nodes, me);
		ATOMIC_WRITE(me->fs_nodes, FSUPER_NODES_DELETED);
	}
	me->fs_root._mf_fsuperplop.oplo_func = &fsuper_clearnodes_postlop;
	return &me->fs_root._mf_fsuperplop;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LOCKOP_CC fsuper_clear_changed_postlop)(Tobpostlockop(fsuper) *__restrict self,
                                                REF struct fsuper *__restrict me) {
	assert(self == &me->fs_root._mf_fsuperplop);
	(void)self;

	/* Finalize deletion of all nodes which we stole from the changed-list. */
	while (me->fs_root._mf_delfnodes) {
		REF struct fnode *node    = me->fs_root._mf_delfnodes;
		me->fs_root._mf_delfnodes = node->_mf_delfnodes;
		fnode_delete_from_all_impl(node); /* This inherits the reference for us! */
	}

	/* Set `me->fs_nodes = FSUPER_NODES_DELETED' */
	COMPILER_READ_BARRIER();
	if (me->fs_nodes != FSUPER_NODES_DELETED) {
		if (fsuper_nodes_trywrite(me)) {
			fsuper_clearnodes_lop(&me->fs_root._mf_fsuperlop, me);
			fsuper_nodes_endwrite(me);
		} else {
			me->fs_root._mf_fsuperlop.olo_func = &fsuper_clearnodes_lop;
			oblockop_enqueue(&me->fs_changednodes_lops, &me->fs_root._mf_fsuperlop);
			_fsuper_nodes_reap(me);
			return;
		}
	}

	fsuper_clearnodes_postlop(&me->fs_root._mf_fsuperplop, me);
}


PRIVATE NOBLOCK NONNULL((1)) Tobpostlockop(fsuper) *
NOTHROW(LOCKOP_CC fsuper_clear_changed_lop)(Toblockop(fsuper) *__restrict self,
                                            REF struct fsuper *__restrict me) {
	assert(self == &me->fs_root._mf_fsuperlop);
	(void)self;
	if likely(me->fs_changednodes.lh_first != FSUPER_NODES_DELETED) {
		/* Clear all changed nodes (and move reference to `me->fs_root._mf_delfnodes'). */
		while (!LIST_EMPTY(&me->fs_changednodes)) {
			REF struct fnode *node;
			node = LIST_FIRST(&me->fs_changednodes);
			LIST_UNBIND(node, fn_changed); /* With this, we inherit the reference from `fs_changednodes' */
			assert(!wasdestroyed(node));
			if (!mfile_begin_delete(node)) {
				/* Special case: the node is already being deleted for some other reason,
				 *               meaning  that we are unable to gain ownership of its LOP
				 *               fields (which we'd need for doing the decref later)
				 * It's still thread-safe to do the decref here, but it may not be very
				 * efficient since  our caller  is already  holding an  atomic  lock... */
				decref(node);
				continue;
			}

			/* Do the decref() (and deletion) in the post-lockop phase. */
			node->_mf_delfnodes       = me->fs_root._mf_delfnodes;
			me->fs_root._mf_delfnodes = node;
		}
		ATOMIC_WRITE(me->fs_changednodes.lh_first, FSUPER_NODES_DELETED);
	}

	/* Decref() (and delete) all of the other objects in the post-phase */
	me->fs_root._mf_fsuperplop.oplo_func = &fsuper_clear_changed_postlop;
	return &me->fs_root._mf_fsuperplop;
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LOCKOP_CC fsuper_delete_remove_from_all_postlop)(struct postlockop *__restrict self) {
	REF struct fsuper *me;
	me = container_of(self, struct fsuper, fs_root._mf_plop);
	me->fs_root._mf_delfnodes = NULL;

	/* Clear the superblock's list of changed nodes (and mark it as DELETED) */
	if (fsuper_changednodes_tryacquire(me)) {
		fsuper_clear_changed_lop(&me->fs_root._mf_fsuperlop, me);
		fsuper_changednodes_release(me);
	} else {
		me->fs_root._mf_fsuperlop.olo_func = &fsuper_clear_changed_lop; /* Inherit reference */
		oblockop_enqueue(&me->fs_changednodes_lops, &me->fs_root._mf_fsuperlop);
		_fsuper_changednodes_reap(me);
		return;
	}
	fsuper_clear_changed_postlop(&me->fs_root._mf_fsuperplop, me);
}


PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(LOCKOP_CC fsuper_delete_remove_from_all_lop)(struct lockop *__restrict self) {
	REF struct fsuper *me;
	me = container_of(self, struct fsuper, fs_root._mf_lop);
	COMPILER_READ_BARRIER();
	if (LIST_ISBOUND(me, fs_root.fn_allsuper))
		LIST_UNBIND(me, fs_root.fn_allsuper);
	me->fs_root._mf_plop.plo_func = &fsuper_delete_remove_from_all_postlop;
	return &me->fs_root._mf_plop;
}


/* Mark `self' as deleted (should be called when all
 * mounting  points  using `self'  have  gone away):
 *  - For all nodes in `self->fs_nodes':
 *    - Call `mfile_delete()'
 *    - Remove the fnode from the global list of file-nodes
 *  - Mark the `fs_nodes' and `fs_changednodes' as `FSUPER_NODES_DELETED',
 *    and  drop  references from  all  changed files  that  were captured.
 * Note that the caller should first invoke `fsuper_sync()' to ensure
 * that any unwritten changes are written to disk.
 *
 * Anything  from the  above that  couldn't be  done synchronously via
 * non-blocking operations will  instead be completed  asynchronously,
 * meaning that the caller should let the superblock cleanup itself as
 * required locks become available... */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fsuper_delete)(struct fsuper *__restrict self) {
	/* Check for special case: singleton filesystems mustn't be marked as DELETED */
	if (self->fs_sys->ffs_flags & FFILESYS_F_SINGLE)
		return;

	if (!mfile_begin_delete(&self->fs_root))
		return; /* Already deleted, or deletion already in progress. */

	incref(self);

	/* Remove from the list of all superblocks */
	COMPILER_READ_BARRIER();
	if (LIST_ISBOUND(self, fs_root.fn_allsuper)) {
		if (fallsuper_tryacquire()) {
			COMPILER_READ_BARRIER();
			if (LIST_ISBOUND(self, fs_root.fn_allsuper))
				LIST_UNBIND(self, fs_root.fn_allsuper);
			fallsuper_release();
		} else {
			self->fs_root._mf_lop.lo_func = &fsuper_delete_remove_from_all_lop; /* Inherit reference */
			lockop_enqueue(&fallsuper_lockops, &self->fs_root._mf_lop);
			_fallsuper_reap();
			return;
		}
	}
	fsuper_delete_remove_from_all_postlop(&self->fs_root._mf_plop); /* Inherit reference */
}



/* Gather information about the filesystem and store that information in `*result' */
PUBLIC NONNULL((1, 2)) void FCALL
fsuper_statfs(struct fsuper *__restrict self,
              USER CHECKED struct statfs *result)
		THROWS(E_IOERROR, E_SEGFAULT, ...) {
	struct fsuper_ops const *ops = fsuper_getops(self);

	/* Fill in default fields. */
	result->f_type    = (typeof(result->f_type))self->fs_feat.sf_magic;
	result->f_bsize   = (typeof(result->f_bsize))1 << self->fs_root.mf_blockshift;
	result->f_blocks  = self->fs_dev ? (typeof(result->f_blocks))(blkdev_getsize(self->fs_dev) >> self->fs_root.mf_blockshift) : 0;
	result->f_namelen = (typeof(result->f_namelen))self->fs_feat.sf_name_max;
	result->f_frsize  = (typeof(result->f_frsize))1 << self->fs_root.mf_blockshift;
	result->f_flags   = (typeof(result->f_flags))statvfs_flags_from_mfile_flags(self->fs_root.mf_flags);

	/* If defined, invoke the statfs operator for remaining fields. */
	if (ops->so_statfs) {
		(*ops->so_statfs)(self, result);
	} else {
		/* Fill remaining fields with all zeroes. */
		result->f_bfree         = (typeof(result->f_bfree))0;
		result->f_bavail        = (typeof(result->f_bavail))0;
		result->f_files         = (typeof(result->f_files))0;
		result->f_ffree         = (typeof(result->f_ffree))0;
		result->f_fsid.__val[0] = (typeof(result->f_fsid.__val[0]))0;
		result->f_fsid.__val[1] = (typeof(result->f_fsid.__val[1]))0;
	}
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_SUPER_C */
