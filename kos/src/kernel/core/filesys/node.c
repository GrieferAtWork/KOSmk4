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
#ifndef GUARD_KERNEL_CORE_FILESYS_NODE_C
#define GUARD_KERNEL_CORE_FILESYS_NODE_C 1
#define __WANT_MFILE__mf_lop
#define __WANT_MFILE__mf_plop
#define __WANT_MFILE__mf_fsuperlop
#define __WANT_MFILE__mf_fsuperplop
#define __WANT_MFILE__mf_lopX
#define __WANT_FNODE__fn_chnglop
#define __WANT_FNODE__fn_alllop
#define __WANT_FNODE__fn_suplop
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/allnodes.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/node.h>
#include <kernel/fs/notify.h>
#include <kernel/fs/ramfs.h>
#include <kernel/fs/super.h>
#include <kernel/malloc.h>
#include <sched/cred.h>
#include <sched/task.h>

#include <kos/except.h>
#include <kos/except/reason/fs.h>
#include <kos/except/reason/inval.h>
#include <kos/nopf.h>

#include <assert.h>
#include <atomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>


/* Filenode tree operations. (for `struct fsuper::fs_nodes') */
#define RBTREE_LEFT_LEANING
#define RBTREE_WANT_TRYINSERT
#define RBTREE_WANT_MINMAXLOCATE
#define RBTREE_MINMAX_T_DEFINED
#define fnode_tree_minmax_t  struct fnode_tree_minmax
#define RBTREE(name)         fnode_tree_##name
#define RBTREE_T             struct fnode
#define RBTREE_Tkey          ino_t
#define RBTREE_GETNODE(self) (self)->fn_supent
#define RBTREE_GETKEY(self)  (self)->fn_ino
#define RBTREE_REDFIELD      mf_flags
#define RBTREE_REDBIT        _MFILE_FN__RBRED
#define RBTREE_CC            FCALL
#define RBTREE_NOTHROW       NOTHROW
#define RBTREE_DECL          FUNDEF
#define RBTREE_IMPL          PUBLIC
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */


/* No-op callback for `no_wrattr' (for RAM filesystems) */
PUBLIC NONNULL((1)) void
NOTHROW(KCALL fnode_v_wrattr_noop)(struct fnode *__restrict UNUSED(self)) {
	/* Do nothing */
}


PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(fsuper) *
NOTHROW(LOCKOP_CC fnode_add2changed_lop)(Toblockop(fsuper) *__restrict self,
                                         struct fsuper *__restrict obj) {
	/* Insert into the changed list (our caller is holding its lock) */
	REF struct fnode *me = container_of(self, struct fnode, _fn_chnglop);
	if (obj->fs_changednodes.lh_first != FSUPER_NODES_DELETED) {
		bool is_first = LIST_EMPTY(&obj->fs_changednodes);
		LIST_INSERT_HEAD(&obj->fs_changednodes, me, fn_changed);
		/* First changed node was added to the superblock.
		 * -> Mark the superblock as changed (for `sync(2)') */
		if (is_first)
			fsuper_add2changed(obj);
	}
	return NULL;
}


/* Add the given node to the list of changed nodes. If already done,
 * (or  already  asynchronously  in-progress),  return  immediately. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fnode_add2changed)(struct fnode *__restrict self) {
	struct fsuper *super = self->fn_super;
	static_assert(offsetof(struct fnode, fn_changed.le_prev) ==
	              offsetof(struct fnode, _fn_chnglop.olo_func),
	              "This is required for the atomic_cmpxch "
	              "below to be thread- and async-safe");

	/* Try to acquire a lock to the list of changed superblocks */
	if (fsuper_changednodes_tryacquire(super)) {
		bool is_first = false;
		if (!LIST_ISBOUND(self, fn_changed) &&
		    super->fs_changednodes.lh_first != FSUPER_NODES_DELETED) {
			incref(self);
			is_first = LIST_EMPTY(&super->fs_changednodes);
			LIST_INSERT_HEAD(&super->fs_changednodes, self, fn_changed);
		}
		fsuper_changednodes_release(super);
		if (is_first) {
			/* First changed node was added to the superblock.
			 * -> Mark the superblock as changed (for `sync(2)') */
			fsuper_add2changed(super);
		}
	} else {
		/* Try to do the addition asynchronously. */
		if (atomic_cmpxch(&self->_fn_chnglop.olo_func,
		                  NULL, &fnode_add2changed_lop)) {
			incref(self);
			oblockop_enqueue(&super->fs_changednodes_lops, &self->_fn_chnglop);
			_fsuper_changednodes_reap(super);
		}
	}
}



/* Mandatory callback for all types derived from `struct fnode',
 * for  use with `mf_ops->mo_changed'.  MUST NOT BE OVERWRITTEN! */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fnode_v_changed)(struct mfile *__restrict self,
                               uintptr_t old_flags,
                               uintptr_t UNUSED(new_flags)) {
	struct fnode *me = mfile_asnode(self);
	if (!(old_flags & (MFILE_F_CHANGED | MFILE_F_ATTRCHANGED))) {
		/* Add to the list of changed file-nodes the first time around. */
		fnode_add2changed(me);
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fnode_free)(struct fnode *__restrict self) {
	struct fnode_ops const *ops = fnode_getops(self);
	if (ops->no_free) {
		(*ops->no_free)(self);
	} else {
		kfree(self);
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LOCKOP_CC fnode_v_destroy_rmall_postlop)(struct postlockop *__restrict self) {
	/* Free the file-node */
	fnode_free(container_of(self, struct fnode, _mf_plop));
}

PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(LOCKOP_CC fnode_v_destroy_rmallsuper_lop)(struct lockop *__restrict self) {
	struct fsuper *me = container_of(self, struct fsuper, fs_root._mf_lop);
	assert(me->fs_root._fn_alllop.lo_func != &fnode_addtoall_lop);
	if (LIST_ISBOUND(me, fs_root.fn_allsuper))
		fallsuper_remove(me);
	me->fs_root._mf_plop.plo_func = &fnode_v_destroy_rmall_postlop;
	return &me->fs_root._mf_plop;
}

PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(LOCKOP_CC fnode_v_destroy_rmallnodes_lop)(struct lockop *__restrict self) {
	struct fnode *me = container_of(self, struct fnode, _mf_lop);
	if unlikely(me->_fn_alllop.lo_func == &fnode_addtoall_lop) {
		/* Must let `fnode_addtoall_lop()' finish first! */
		me->_mf_lop.lo_func = &fnode_v_destroy_rmallnodes_lop;
		lockop_enqueue(&fallnodes_lockops, &me->_mf_lop);
		return NULL;
	}
	if (LIST_ISBOUND(me, fn_allnodes))
		fallnodes_remove(me);
	me->_mf_plop.plo_func = &fnode_v_destroy_rmall_postlop;
	return &me->_mf_plop;
}


PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC fnode_v_destroy_rmsuper_postlop)(Tobpostlockop(fsuper) *__restrict self,
                                                   struct fsuper *__restrict UNUSED(obj)) {
	struct fnode *me = container_of(self, struct fnode, _mf_fsuperplop);

	/* Remove the node from the list of all nodes. */
again_unbind_allnodes:
	COMPILER_READ_BARRIER();
	if (LIST_ISBOUND(me, fn_allnodes)) {
		if (fallnodes_tryacquire()) {
			COMPILER_READ_BARRIER();
			if unlikely(me->_fn_alllop.lo_func == &fnode_addtoall_lop) {
				fallnodes_release(); /* This should reap & invoke fnode_addtoall_lop() */
				goto again_unbind_allnodes;
			}
			if (LIST_ISBOUND(me, fn_allnodes))
				fallnodes_remove(me);
			fallnodes_release();
		} else {
			DBG_memset(me->_mf_lopX, 0xcc, sizeof(me->_mf_lopX));
			me->_mf_lop.lo_func = &fnode_v_destroy_rmallnodes_lop;
			lockop_enqueue(&fallnodes_lockops, &me->_mf_lop);
			_fallnodes_reap();
			return;
		}
	}

	/* Free the file-node */
	fnode_free(me);
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(fsuper) *
NOTHROW(LOCKOP_CC fnode_v_destroy_rmsuper_lop)(Toblockop(fsuper) *__restrict self,
                                               struct fsuper *__restrict obj) {
	struct fnode *me = container_of(self, struct fnode, _mf_fsuperlop);
	COMPILER_READ_BARRIER();
	assertf(me->_fn_suplop.olo_func != &fnode_add2sup_lop,
	        "The `fnode_add2sup_lop' function owns a reference to the node, "
	        "and we only get here then the reference counter reaches 0, so "
	        "there should be no way the object is still trying to async-add "
	        "itself to the nodes list!");
	if (me->fn_supent.rb_rhs != FSUPER_NODES_DELETED) {
		assert(obj->fs_nodes != FSUPER_NODES_DELETED);
		fsuper_nodes_removenode(obj, me);
	}
	me->_mf_fsuperplop.oplo_func = &fnode_v_destroy_rmsuper_postlop;
	return &me->_mf_fsuperplop;
}


/* File-node  destroy callback. Must be set in `mo_destroy',
 * but may be overwritten by sub-classes, in which case this
 * function must be called as the last thing done within the
 * sub-class destroy-operator. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fnode_v_destroy)(struct mfile *__restrict self) {
	struct fnode *me = mfile_asnode(self);
	assertf(!(me->mf_flags & MFILE_FN_GLOBAL_REF),
	        "Then why are we being destroyed?");

	/* Remove the node from its superblock's node-tree, as well
	 * as  from the  global list  of all  nodes or superblocks. */
	if (fnode_issuper(me)) {
		struct fsuper *super = fnode_assuper(me);
		if (LIST_ISBOUND(super, fs_root.fn_allsuper)) {
			/* Remove from `fallsuper_list' */
			if (fallsuper_tryacquire()) {
				assert(super->fs_root._fn_alllop.lo_func != &fnode_addtoall_lop);
				if (LIST_ISBOUND(super, fs_root.fn_allsuper))
					fallsuper_remove(super);
				fallsuper_release();
			} else {
				DBG_memset(super->fs_root._mf_lopX, 0xcc, sizeof(super->fs_root._mf_lopX));
				super->fs_root._mf_lop.lo_func = &fnode_v_destroy_rmallsuper_lop;
				lockop_enqueue(&fallsuper_lockops, &super->fs_root._mf_lop);
				_fallsuper_reap();
				return;
			}
		}
	} else {
		REF struct fsuper *super = me->fn_super;
		/* Remove from the associated superblock's list of nodes. */
		if (atomic_read(&me->fn_supent.rb_rhs) != FSUPER_NODES_DELETED) {
			if (fsuper_nodes_trywrite(super)) {
				COMPILER_READ_BARRIER();
				if (me->fn_supent.rb_rhs != FSUPER_NODES_DELETED) {
					assertf(me->_fn_suplop.olo_func != &fnode_add2sup_lop,
					        "The `fnode_add2sup_lop' function owns a reference to the node, "
					        "and we only get here then the reference counter reaches 0, so "
					        "there should be no way the object is still trying to async-add "
					        "itself to the nodes list!");
					assert(super->fs_nodes != FSUPER_NODES_DELETED);
					fsuper_nodes_removenode(super, me);
				}
				fsuper_nodes_endwrite(super);
			} else {
				me->_mf_fsuperlop.olo_func = &fnode_v_destroy_rmsuper_lop;
				oblockop_enqueue(&super->fs_nodeslockops, &me->_mf_fsuperlop);
				_fsuper_nodes_reap(super);
				decref_unlikely(super);
				return;
			}
		}
		decref_unlikely(super);

		/* Remove the node from the list of all nodes. */
again_unbind_allnodes:
		COMPILER_READ_BARRIER();
		if (LIST_ISBOUND(me, fn_allnodes)) {
			if (fallnodes_tryacquire()) {
				COMPILER_READ_BARRIER();
				if unlikely(me->_fn_alllop.lo_func == &fnode_addtoall_lop) {
					fallnodes_release(); /* This should reap & invoke fnode_addtoall_lop() */
					goto again_unbind_allnodes;
				}
				if (LIST_ISBOUND(me, fn_allnodes))
					fallnodes_remove(me);
				fallnodes_release();
			} else {
				DBG_memset(me->_mf_lopX, 0xcc, sizeof(me->_mf_lopX));
				me->_mf_lop.lo_func = &fnode_v_destroy_rmallnodes_lop;
				lockop_enqueue(&fallnodes_lockops, &me->_mf_lop);
				_fallnodes_reap();
				return;
			}
		}
	}

	/* Free the file-node */
	fnode_free(me);
}



/* Get the uid/gid of a given file-node. These functions respect `npo_getown' */
PUBLIC BLOCKING NONNULL((1)) uid_t KCALL
fnode_getuid(struct fnode *__restrict self) {
	uid_t result;
	struct fnode_perm_ops const *perm_ops;
	perm_ops = fnode_getops(self)->no_perm;
	if (perm_ops && perm_ops->npo_getown) {
		gid_t _ignored;
		(*perm_ops->npo_getown)(self, &result, &_ignored);
	} else {
#if 1
		result = atomic_read(&self->fn_uid);
#else
		mfile_tslock_acquire(self);
		result = self->fn_uid;
		mfile_tslock_release(self);
#endif
	}
	return result;
}

PUBLIC BLOCKING NONNULL((1)) gid_t KCALL
fnode_getgid(struct fnode *__restrict self) {
	gid_t result;
	struct fnode_perm_ops const *perm_ops;
	perm_ops = fnode_getops(self)->no_perm;
	if (perm_ops && perm_ops->npo_getown) {
		uid_t _ignored;
		(*perm_ops->npo_getown)(self, &_ignored, &result);
	} else {
#if 1
		result = atomic_read(&self->fn_gid);
#else
		mfile_tslock_acquire(self);
		result = self->fn_gid;
		mfile_tslock_release(self);
#endif
	}
	return result;
}

PUBLIC BLOCKING NONNULL((1, 2, 3)) void KCALL
fnode_getugid(struct fnode *__restrict self,
              uid_t *__restrict puid,
              gid_t *__restrict pgid) {
	struct fnode_perm_ops const *perm_ops;
	perm_ops = fnode_getops(self)->no_perm;
	if (perm_ops && perm_ops->npo_getown) {
		(*perm_ops->npo_getown)(self, puid, pgid);
	} else {
		mfile_tslock_acquire(self);
		*puid = self->fn_uid;
		*pgid = self->fn_gid;
		mfile_tslock_release(self);
	}
}




/* For use with `_fn_alllop': asynchronously add the node to the list of all nodes.
 * This function needs to be exposed publicly because it being set requires special
 * care if set during custom fnode destructors.
 * Note that the default `fnode_v_destroy()' includes correct handling for this. */
PUBLIC NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(LOCKOP_CC fnode_addtoall_lop)(struct lockop *__restrict self) {
	static_assert(offsetof(struct fnode, fn_allnodes.le_prev) == offsetof(struct fnode, _fn_alllop.lo_func));
	struct fnode *me = container_of(self, struct fnode, _fn_alllop);
	assert(me->_fn_alllop.lo_func == &fnode_addtoall_lop);
	atomic_write(&me->fn_allnodes.le_prev, &fallnodes_list.lh_first); /* This write needs to be atomic */
	if ((me->fn_allnodes.le_next = fallnodes_list.lh_first) != NULL)
		me->fn_allnodes.le_next->fn_allnodes.le_prev = &me->fn_allnodes.le_next;
	__fallnodes_size_inc();
	return NULL;
}



/* Add the given node `self'  to the list of all  nodes. The caller must  ensure
 * that this function is _NOT_ called such that it would violate the REMOVE_ONCE
 * constraint  of `fn_allnodes'. Iow:  don't call this  function when `self' has
 * already become globally visible by some other means.
 *
 * This function can be used to initialize:
 *  - self->fn_allnodes
 * ... but  may only be called once _all_ other fields of `self' have already been
 *     initialized, and only if `self' isn't globally visible by some other means. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fnode_init_addtoall)(struct fnode *__restrict self) {
	/* Yes: we do a raw init! */
	DBG_memset(&self->fn_allnodes, 0xcc, sizeof(self->fn_allnodes));
	if (fallnodes_tryacquire()) {
		fallnodes_insert(self);
		fallnodes_release();
	} else {
		/* Use a lock operator. */
		self->_fn_alllop.lo_func = &fnode_addtoall_lop;
		COMPILER_WRITE_BARRIER();
		lockop_enqueue(&fallnodes_lockops, &self->_fn_alllop);
		_fallnodes_reap();
	}
}


PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC destroy_node_from_super_postlop)(Tobpostlockop(fsuper) *__restrict self,
                                                   struct fsuper *__restrict UNUSED(obj)) {
	struct fnode *me;
	me = container_of(self, struct fnode, _mf_fsuperplop);
	mfile_destroy(me);
}

/* For use with `_fn_suplop': The node is currently adding itself to the superblock
 * by  means of an asynchronous operation. NOTE: This lock operator unconditionally
 * inherits a reference  to `container_of(self, struct fnode, _fn_suplop)', and  as
 * such  you may assume that a fnode which  has been destroyed would no longer make
 * use of this.
 *
 * However, in situations where `fsuper_nodes_removenode(node)' is called, you  must
 * first check  if  `node->_fn_suplop.olo_func == &fnode_add2sup_lop',  and  if  so,
 * must  release your lock to the superblock before reacquiring it in order to allow
 * the node to fully add itself to the superblock's node tree so that you may safely
 * remove it later.
 *
 * Similarly, `fsuper_nodes_locate()' or `fsuper_nodes_remove()' returning NULL when
 * `fsuper_nodes_mustreap()' does not necessarily mean  that the node you're  trying
 * to lookup/remove doesn't exist; it may just be trying to add itself right now. */
PUBLIC NOBLOCK NONNULL((1, 2)) Tobpostlockop(fsuper) *
NOTHROW(LOCKOP_CC fnode_add2sup_lop)(Toblockop(fsuper) *__restrict self,
                                     struct fsuper *__restrict obj) {
	REF struct fnode *me;
	me = container_of(self, struct fnode, _fn_suplop);
	assert(obj == me->fn_super);

	/* Check for special  case: if  the node has  been marked  as
	 * deleted, then we mustn't add it to the super's Inode tree. */
	if unlikely(me->mf_flags & MFILE_F_DELETED) {
		atomic_write(&me->fn_supent.rb_rhs, FSUPER_NODES_DELETED);
		return NULL;
	}
	if unlikely(!fsuper_nodes_tryinsert(obj, me)) {
		struct fnode *existing;
		existing = fsuper_nodes_remove(obj, me->fn_ino);
		assert(existing);
		existing->fn_supent.rb_rhs = FSUPER_NODES_DELETED;
		fsuper_nodes_insert(obj, me);
	}

	/* Inherit one reference from `me' */
	if unlikely(atomic_decfetch(&me->mf_refcnt) == 0) {
		/* Don't do the destroy here; use a post-operator for that! */
		me->_mf_fsuperplop.oplo_func = &destroy_node_from_super_postlop;
		return &me->_mf_fsuperplop;
	}
	return NULL;
}

/* The async combination of adding `self' to its superblock's node tree, as  well
 * as to the global list of all nodes. The caller must ensure that `self->fn_ino'
 * isn't already in use any  other file-node. If another  node with the same  INO
 * number  already exists, said other node is  first removed from the INode tree.
 *
 * This function can be used to initialize:
 *  - self->fn_supent
 *  - self->fn_allnodes
 * ... but  may only be called once _all_ other fields of `self' have already been
 *     initialized, and only if `self' isn't globally visible by some other means,
 *     though the fields initialized  by this are pretty  much the only fields  by
 *     which nodes *normally* become globally visible. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fnode_init_addtosuper_and_all)(struct fnode *__restrict self) {
	struct fsuper *super = self->fn_super;
	assert(!(self->mf_flags & MFILE_F_DELETED));
	if (fsuper_nodes_trywrite(super)) {
		if unlikely(!fsuper_nodes_tryinsert(super, self)) {
			struct fnode *existing;
			existing = fsuper_nodes_remove(super, self->fn_ino);
			assert(existing);
			existing->fn_supent.rb_rhs = FSUPER_NODES_DELETED;
			fsuper_nodes_insert(super, self);
		}

		/* Also add to the list of all nodes.
		 * NOTE: Like required by `fnode_init_addtoall()', this function must be
		 *       called _BEFORE_ `self' becomes globally visible, which is still
		 *       the case so-long as we've not `fsuper_nodes_endwrite(super)'. */
		fnode_init_addtoall(self);

		/* Release the super-nodes lock. */
		fsuper_nodes_endwrite(super);
	} else {
		static_assert(offsetof(struct fnode, _fn_suplop.olo_func) ==
		              offsetof(struct fnode, fn_supent.rb_rhs),
		              "This is a requirement to ensure that the node can't "
		              "accidentally appear as `rb_rhs == FSUPER_NODES_DELETED', "
		              "which would indicate that it had been removed from the "
		              "super's node tree, when in fact it's still in limbo as "
		              "to whether or not it's part of said tree.");

		/* Use lock operations to have the INode add itself to the  */
		++self->mf_refcnt; /* +1: inherited by `fnode_add2sup_lop()' */
		self->_fn_suplop.olo_func = &fnode_add2sup_lop;
		COMPILER_WRITE_BARRIER();

		/* Also add to the all-nodes list. */
		fnode_init_addtoall(self);
		COMPILER_BARRIER();

		/* At this point we would normally have a race condition since `node'
		 * has yet to be added to its superblock's node-tree, but (may)  have
		 * already become globally visible (via the all-nodes list).
		 *
		 * But this is resolved by  `node->_fn_suplop.olo_func = &fnode_add2sup_lop',
		 * which for one makes it so that `fn_supent.rb_rhs != FSUPER_NODES_DELETED',
		 * marking  the file as _NOT_ removed from its super's Inode tree, as well as
		 * by this special scenario being publicly documented by requiring other code
		 * to reap a superblock's node-lops before trying to remove an INode that  is
		 * marked  as  `node->_fn_suplop.olo_func == &fnode_add2sup_lop', as  well as
		 * also reaping if trying (and failing) to remove from a super that's got any
		 * pending lops. */
		oblockop_enqueue(&super->fs_nodeslockops, &self->_fn_suplop);
		_fsuper_nodes_reap(super);
	}
}






/* High-level file-node functions */

/* Change permissions, SUID/SGID and the sticky bit of the given INode (flagsmask: 07777)
 * The new file mode is calculated as `(old_mode & perm_mask) | perm_flag', before  being
 * masked by what the underlying filesystem is capable of representing.
 * @return: * : The old file mode
 * @throw: E_FSERROR_READONLY:    The `MFILE_FN_ATTRREADONLY' flag is (or was) set.
 * @throw: E_INSUFFICIENT_RIGHTS: `check_permissions' is true and you're not allowed to do this. */
PUBLIC BLOCKING NONNULL((1)) mode_t KCALL
fnode_chmod(struct fnode *__restrict self, mode_t perm_mask,
            mode_t perm_flag, bool check_permissions)
		THROWS(E_FSERROR_READONLY, E_INSUFFICIENT_RIGHTS) {
	mode_t old_mode, new_mode;
	struct timespec now = realtime();

	/* Check if file attributes may be modified. */
	if unlikely(self->mf_flags & MFILE_FN_ATTRREADONLY)
		THROW(E_FSERROR_READONLY);

	/* Only these bits can be modified at all! */
	perm_mask &= 07777;
	perm_flag &= 07777;

	/* These bits must be preserved at all cost (they contain file type information) */
	perm_mask |= ~07777;

#ifndef CONFIG_KERNEL_EVERYONE_IS_ROOT
	if (check_permissions) {
		struct fnode_perm_ops const *perm_ops;
		perm_ops = fnode_getops(self)->no_perm;
		if (perm_ops && perm_ops->npo_getown) {
			uid_t uid;
			gid_t gid;
			(*perm_ops->npo_getown)(self, &uid, &gid);
			if (uid != cred_getfsuid() && !capable(CAP_FOWNER))
				THROW(E_INSUFFICIENT_RIGHTS, CAP_FOWNER);
			if ((perm_flag & S_ISGID) || (perm_mask & S_ISGID)) {
				/* The Set-gid bit can must  be turned off (i.e.  cannot be turned on/or  left
				 * on) when the caller isn't apart of the group associated with `self->fn_gid' */
				if (!capable(CAP_FSETID) && !cred_isfsgroupmember(gid)) {
					perm_mask &= ~S_ISGID;
					perm_flag &= ~S_ISGID;
				}
			}
			check_permissions = false;
		}
	}
again:
#endif /* !CONFIG_KERNEL_EVERYONE_IS_ROOT */
	mfile_tslock_acquire(self);
#ifndef CONFIG_KERNEL_EVERYONE_IS_ROOT
	if (check_permissions) {
		/* Permission restrictions:
		 *   - `fn_uid' must match the caller's fsuid, or the caller must have `CAP_FOWNER'
		 *   - If `fn_gid' doesn't relate to the caller, and the caller doesn't
		 *     have `CAP_FSETID', then the `S_ISGID' bit is always turned  off.
		 * That is all. - Every user's allowed to set the SETUID bit, since they can only do this
		 * for  files they own, and in doing this,  only allow programs to impersonate that user!
		 */
		uid_t uid;
again_check_permissions:
		uid = self->fn_uid;
		if (uid != cred_getfsuid() && !capable(CAP_FOWNER)) {
			mfile_tslock_release_br(self);
			THROW(E_INSUFFICIENT_RIGHTS, CAP_FOWNER);
		}
		if ((perm_flag & S_ISGID) || (perm_mask & S_ISGID)) {
			/* The Set-gid bit can must  be turned off (i.e.  cannot be turned on/or  left
			 * on) when the caller isn't apart of the group associated with `self->fn_gid' */
			if (!capable(CAP_FSETID)) {
				gid_t gid = self->fn_gid;
				COMPILER_BARRIER();
				mfile_tslock_release_br(self);
				if (!cred_isfsgroupmember(gid)) {
					perm_mask &= ~S_ISGID;
					perm_flag &= ~S_ISGID;
					goto again;
				}
				mfile_tslock_acquire_br(self);
				if (gid != self->fn_gid || uid != self->fn_uid)
					goto again_check_permissions;
			}
		}
	}
#else /* !CONFIG_KERNEL_EVERYONE_IS_ROOT */
	(void)check_permissions;
#endif /* CONFIG_KERNEL_EVERYONE_IS_ROOT */

	old_mode = self->fn_mode;
	new_mode = (old_mode & perm_mask) | perm_flag;
	/* Set the new file mode. */
	atomic_write(&self->fn_mode, new_mode);
	if (old_mode != new_mode)
		self->mf_ctime = now; /* Attributes-changed */
	mfile_tslock_release(self);

	/* Broadcast that mode bits have changed. */
	if (old_mode != new_mode) {
		mfile_changed(self, MFILE_F_ATTRCHANGED);
		mfile_inotify_attrib(self); /* Post `IN_ATTRIB' */
	}
	return old_mode;
}



/* Change the owner and group of the given file. NOTE: either attribute is only
 * altered when  `owner != (uid_t)-1'  and  `group != (gid_t)-1'  respectively.
 * @throw: E_FSERROR_READONLY:    The `MFILE_FN_ATTRREADONLY' flag is (or was) set.
 * @throw: E_INSUFFICIENT_RIGHTS: `check_permissions' is true and you're not allowed to do this.
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_CHOWN_UNSUPP_UID:uid: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_CHOWN_UNSUPP_GID:gid: [...] */
PUBLIC NONNULL((1)) void KCALL
fnode_chown(struct fnode *__restrict self, uid_t owner, gid_t group,
            NCX uid_t *pold_owner, NCX gid_t *pold_group,
            bool check_permissions)
		THROWS(E_SEGFAULT, E_FSERROR_READONLY,
		       E_INSUFFICIENT_RIGHTS, E_INVALID_ARGUMENT_BAD_VALUE) {
	struct timespec now = realtime();
	bool changed = false;
	uid_t old_owner, new_owner;
	gid_t old_group, new_group;

	/* Verify that the filesystem allows the given owner/group */
	if (owner != (uid_t)-1 && !fsuper_validuid(self->fn_super, owner))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE, E_INVALID_ARGUMENT_CONTEXT_CHOWN_UNSUPP_UID, owner);
	if (group != (gid_t)-1 && !fsuper_validgid(self->fn_super, group))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE, E_INVALID_ARGUMENT_CONTEXT_CHOWN_UNSUPP_GID, group);

	{
		struct fnode_perm_ops const *perm_ops;
		perm_ops = fnode_getops(self)->no_perm;
		if (perm_ops && perm_ops->npo_getown) {
			/* Owner/group are fixed and cannot be changed. */
			(*perm_ops->npo_getown)(self, &old_owner, &old_group);
			if ((owner != (uid_t)-1 && owner != old_owner) ||
			    (group != (gid_t)-1 && group != old_group))
				THROW(E_FSERROR_READONLY);
			if (pold_owner)
				*pold_owner = old_owner;
			if (pold_group)
				*pold_group = old_group;
			return;
		}
	}

	mfile_tslock_acquire(self);
again_read_old_values:
	COMPILER_READ_BARRIER();
	old_owner = self->fn_uid;
	old_group = self->fn_gid;
	COMPILER_READ_BARRIER();
	new_owner = owner;
	new_group = group;
	if (new_owner == (uid_t)-1)
		new_owner = old_owner;
	if (new_group == (gid_t)-1)
		new_group = old_group;

	/* Write-back old owner/group values to user-space. */
	if (pold_owner || pold_group) {
		if ((pold_owner && memcpy_nopf(pold_owner, &old_owner, sizeof(uid_t)) != 0) ||
		    (pold_group && memcpy_nopf(pold_group, &old_group, sizeof(gid_t)) != 0)) {
			mfile_tslock_release_br(self);
			COMPILER_WRITE_BARRIER();
			*pold_owner = old_owner;
			*pold_group = old_group;
			COMPILER_WRITE_BARRIER();
			mfile_tslock_acquire_br(self);
			if (old_owner != self->fn_uid ||
			    old_group != self->fn_gid)
				goto again_read_old_values;
		}
	}

	/* Only do permission checks if stuff actually changed! */
	if (old_owner != new_owner || old_group != new_group) {
		mode_t mode;

		/* Check if file attributes may be modified. */
		if unlikely(self->mf_flags & MFILE_FN_ATTRREADONLY) {
			mfile_tslock_release_br(self);
			THROW(E_FSERROR_READONLY);
		}

#ifndef CONFIG_KERNEL_EVERYONE_IS_ROOT
		if (check_permissions) {
			/* Permission restrictions:
			 *   - `new_owner' must match `old_owner', or the caller needs `CAP_CHOWN'
			 *   - `new_group' must be apart of the caller's groups, or the caller needs `CAP_CHOWN'
			 */
			if (!capable(CAP_CHOWN)) {
				if (new_owner != old_owner) {
					mfile_tslock_release_br(self);
					THROW(E_INSUFFICIENT_RIGHTS, CAP_CHOWN);
				}
				if (new_group != old_group) {
					mfile_tslock_release_br(self);
					if (!cred_isfsgroupmember(group))
						THROW(E_INSUFFICIENT_RIGHTS, CAP_CHOWN);
					mfile_tslock_acquire_br(self);
					if (old_owner != self->fn_uid ||
					    old_group != self->fn_gid)
						goto again_read_old_values;
				}
			}
		}
#else /* !CONFIG_KERNEL_EVERYONE_IS_ROOT */
		(void)check_permissions;
#endif /* CONFIG_KERNEL_EVERYONE_IS_ROOT */

		mode = self->fn_mode;
		if (mode & 0111) {
			/* When  changing the  owner or  group of  an executable file,
			 * then the  S_ISUID  and  S_ISGID  bits  should  be  cleared.
			 * However, `S_ISGID' is not cleared when `S_IXGRP' isn't set. */
			mode_t mask;
			if (mode & S_IXGRP) {
				mask = ~(S_ISUID | S_ISGID);
			} else {
				mask = ~(S_ISUID);
			}
			mode &= mask;
			atomic_write(&self->fn_mode, mode);
		}

		/* Actually write the new owner/group */
		self->fn_uid   = new_owner;
		self->fn_gid   = new_group;
		self->mf_ctime = now; /* Attributes-changed */
		changed        = true;
	}
	mfile_tslock_release(self);

	/* Broadcast that owner values have changed. */
	if (changed) {
		mfile_changed(self, MFILE_F_ATTRCHANGED);
		mfile_inotify_attrib(self); /* Post `IN_ATTRIB' */
	}
}



PRIVATE NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL maybe_set_timestamp)(struct timespec *__restrict dst,
                                   struct timespec const *src) {
	if (src != NULL && (dst->tv_sec != src->tv_sec ||
	                    dst->tv_nsec != src->tv_nsec)) {
		dst->tv_sec  = src->tv_sec;
		dst->tv_nsec = src->tv_nsec;
		return true;
	}
	return false;
}


/* Change all non-NULL the timestamp that are given.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: The `MFILE_F_DELETED' is set.
 * @throw: E_FSERROR_READONLY: The `MFILE_FN_ATTRREADONLY' flag is (or was) set.
 * @return: true:  File attributes were changed.
 * @return: false: File attributes remain unchanged (ctime wasn't updated). */
PUBLIC NONNULL((1)) bool KCALL
mfile_chtime(struct mfile *__restrict self,
             struct timespec const *new_atime,
             struct timespec const *new_mtime,
             struct timespec const *new_btime)
		THROWS(E_FSERROR_READONLY) {
	struct timespec now = realtime();
	bool changed;
	if unlikely(self->mf_flags & MFILE_FN_ATTRREADONLY)
		THROW(E_FSERROR_READONLY);
	mfile_tslock_acquire(self);
	/* Check if the file was deleted. (If it was,
	 * then timestamps must no longer be modified
	 * sine they're re-used for lops & the like) */
	COMPILER_READ_BARRIER();
	if (self->mf_flags & MFILE_F_DELETED) {
		mfile_tslock_release_br(self);
		THROW(E_FSERROR_DELETED, E_FILESYSTEM_DELETED_FILE);
	}
	/* Fill in new timestamps. */
	changed = maybe_set_timestamp(&self->mf_atime, new_atime);
	changed |= maybe_set_timestamp(&self->mf_mtime, new_mtime);
	changed |= maybe_set_timestamp(&self->mf_btime, new_btime);
	if (changed)
		self->mf_ctime = now; /* Attributes-changed */
	mfile_tslock_release(self);

	/* Mark attributes of this file as having changed. */
	if (changed) {
		mfile_changed(self, MFILE_F_ATTRCHANGED);
		mfile_inotify_attrib(self); /* Post `IN_ATTRIB' */
	}
	return changed;
}



/* Clear the `MFILE_F_ATTRCHANGED' flag and  remove `self' from the  associated
 * superblock's list of changed nodes. If this succeeds, invoke the `no_wrattr'
 * operator. If said operator returns  with an exception, set the  attr-changed
 * flag once again by means of `mfile_changed(self, MFILE_F_ATTRCHANGED)' */
PUBLIC BLOCKING NONNULL((1)) void KCALL
fnode_syncattr(struct fnode *__restrict self)
		THROWS(E_WOULDBLOCK, E_IOERROR, ...) {
	struct fsuper *super;
	uintptr_t old_flags;

	/* Clear the `MFILE_F_ATTRCHANGED' flag. */
	do {
		old_flags = atomic_read(&self->mf_flags);
		if (!(old_flags & MFILE_F_ATTRCHANGED) || (old_flags & MFILE_F_DELETED))
			return;
	} while (!atomic_cmpxch_weak(&self->mf_flags, old_flags,
	                             old_flags & ~MFILE_F_ATTRCHANGED));

	if (!(old_flags & MFILE_F_CHANGED)) {
		super = self->fn_super;
again_acquire_super_changed:
		TRY {
			fsuper_changednodes_acquire(super);
		} EXCEPT {
			mfile_changed(self, MFILE_F_ATTRCHANGED);
			RETHROW();
		}
		if likely(LIST_ISBOUND(self, fn_changed)) {
			/* Check for special case: the node hasn't been fully added to the
			 * superblock's changed list. In this case we have to let the  LOP
			 * do its thing before we can safely remove the node. */
			if unlikely(self->_fn_chnglop.olo_func == &fnode_add2changed_lop) {
				fsuper_changednodes_release(super);
				goto again_acquire_super_changed;
			}
			LIST_UNBIND(self, fn_changed);
			decref_nokill(self); /* Inherited from the changed list */
		}
		fsuper_changednodes_release(super);

		/* To prevent race conditions, re-check if the node
		 * should  actually appear within the changed list. */
		if (atomic_read(&self->mf_flags) & MFILE_F_CHANGED)
			fnode_add2changed(self);
	}

	/* Write modified attributes to disk. */
	TRY {
		struct fnode_ops const *ops;
		ops = fnode_getops(self);
		(*ops->no_wrattr)(self);
	} EXCEPT {
		/* Add back to changed list on error. */
		mfile_changed(self, MFILE_F_ATTRCHANGED);
		RETHROW();
	}
}


/* Clear the `MFILE_F_ATTRCHANGED' flag and remove `self' from the associated
 * superblock's list of changed nodes. If this succeeds, invoke `mfile_sync'.
 * If said function returns with an exception, set the attr-changed flag once
 * again by means of `mfile_changed(self, MFILE_F_CHANGED)' */
PUBLIC BLOCKING NONNULL((1)) void KCALL
fnode_syncdata(struct fnode *__restrict self)
		THROWS(E_WOULDBLOCK, E_IOERROR, ...) {
	struct fsuper *super;
	uintptr_t old_flags;

	/* Clear the `MFILE_F_CHANGED' flag. */
	do {
		old_flags = atomic_read(&self->mf_flags);
		if (!(old_flags & MFILE_F_CHANGED) || (old_flags & MFILE_F_DELETED))
			return;
	} while (!atomic_cmpxch_weak(&self->mf_flags, old_flags,
	                             old_flags & ~MFILE_F_CHANGED));

	if (!(old_flags & MFILE_F_ATTRCHANGED)) {
		super = self->fn_super;
again_acquire_super_changed:
		TRY {
			fsuper_changednodes_acquire(super);
		} EXCEPT {
			mfile_changed(self, MFILE_F_CHANGED);
			RETHROW();
		}
		if likely(LIST_ISBOUND(self, fn_changed)) {
			/* Check for special case: the node hasn't been fully added to the
			 * superblock's changed list. In this case we have to let the  LOP
			 * do its thing before we can safely remove the node. */
			if unlikely(self->_fn_chnglop.olo_func == &fnode_add2changed_lop) {
				fsuper_changednodes_release(super);
				goto again_acquire_super_changed;
			}
			LIST_UNBIND(self, fn_changed);
			decref_nokill(self); /* Inherited from the changed list */
		}
		fsuper_changednodes_release(super);

		/* To prevent race conditions, re-check if the node
		 * should  actually appear within the changed list. */
		if (atomic_read(&self->mf_flags) & MFILE_F_ATTRCHANGED)
			fnode_add2changed(self);
	}

	/* Write modified attributes to disk. */
	TRY {
		struct mfile_stream_ops const *stream_ops;
		mfile_sync(self);

		/* If defined, invoke the streams-sync operator */
		stream_ops = self->mf_ops->mo_stream;
		if (stream_ops != NULL && stream_ops->mso_sync != NULL)
			(*stream_ops->mso_sync)(self);
	} EXCEPT {
		/* Add back to changed list on error. */
		mfile_changed(self, MFILE_F_CHANGED);
		RETHROW();
	}
}




/* Check if the calling thread is allowed to access `self' as described by `type'
 * @param: type:   Set of `R_OK | W_OK | X_OK' (all specified types must be allowed)
 * @return: true:  Access granted
 * @return: false: Access denied. */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL fnode_mayaccess)(struct fnode *__restrict self,
                               unsigned int type) {
	unsigned int how;
	mode_t mode = atomic_read(&self->fn_mode);
	struct fnode_perm_ops const *perm_ops;
	perm_ops = fnode_getops(self)->no_perm;
	if (perm_ops && perm_ops->npo_getown) {
		uid_t uid;
		gid_t gid;
		(*perm_ops->npo_getown)(self, &uid, &gid);
		for (how = 1; how <= 4; how <<= 1) {
			if (!(type & how))
				continue; /* Access not checked. */
			if likely(mode & how)
				continue; /* Access is allowed for everyone. */
			if (mode & (how << 3)) {
				if likely(cred_isfsgroupmember(gid))
					continue; /* The calling thread's user is part of the file owner's group */
			}
			if (mode & (how << 6)) {
				if likely(uid == cred_getfsuid())
					continue; /* The calling thread's user is the file's owner */
				/* CAP_FOWNER: ... Ignore filesystem-uid checks ... */
				if likely(capable(CAP_FOWNER))
					continue;
			}
			return false;
		}
		return true;
	}
	for (how = 1; how <= 4; how <<= 1) {
		if (!(type & how))
			continue; /* Access not checked. */
		if likely(mode & how)
			continue; /* Access is allowed for everyone. */
		if (mode & (how << 3)) {
			gid_t gid = atomic_read(&self->fn_gid);
			if likely(cred_isfsgroupmember(gid))
				continue; /* The calling thread's user is part of the file owner's group */
		}
		if (mode & (how << 6)) {
			uid_t uid = atomic_read(&self->fn_uid);
			if likely(uid == cred_getfsuid())
				continue; /* The calling thread's user is the file's owner */
			/* CAP_FOWNER: ... Ignore filesystem-uid checks ... */
			if likely(capable(CAP_FOWNER))
				continue;
		}
		return false;
	}
	return true;
}

/* Helper wrapper for `fnode_mayaccess()' that asserts access
 * and throws `E_FSERROR_ACCESS_DENIED' is access was denied.
 * @param: type: Set of `R_OK | W_OK | X_OK' (all specified types must be allowed)
 * @return:                         Access granted
 * @throw: E_FSERROR_ACCESS_DENIED: Access denied. */
PUBLIC NOBLOCK NONNULL((1)) void FCALL
fnode_access(struct fnode *__restrict self, unsigned int type)
		THROWS(E_FSERROR_ACCESS_DENIED) {
	if unlikely(!fnode_mayaccess(self, type))
		THROW(E_FSERROR_ACCESS_DENIED);
}






/************************************************************************/
/* Implementation of `fnode_delete()'                                   */
/************************************************************************/

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LOCKOP_CC fnode_delete_remove_from_allnodes_postlop)(struct postlockop *__restrict self) {
	REF struct fnode *me;
	me = container_of(self, struct fnode, _mf_plop);

	/* At this point, all of the global hooks of `me' have been  removed.
	 * The rest of the deletion work relates only to the underlying mfile
	 * and includes stuff like anonymizing any bound mem-parts. */
	mfile_delete_impl(me); /* Inherit reference */
}

PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(LOCKOP_CC fnode_delete_remove_from_allnodes_lop)(struct lockop *__restrict self) {
	REF struct fnode *me;
	me = container_of(self, struct fnode, _mf_lop);
	COMPILER_READ_BARRIER();
	if (LIST_ISBOUND(me, fn_allnodes)) {
		fallnodes_remove(me);
		LIST_ENTRY_UNBOUND_INIT(&me->fn_allnodes);
	}
	me->_mf_plop.plo_func = &fnode_delete_remove_from_allnodes_postlop; /* Inherit reference */
	return &me->_mf_plop;
}


PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC fnode_delete_remove_from_changed_postlop)(Tobpostlockop(fsuper) *__restrict self,
                                                            struct fsuper *__restrict UNUSED(obj)) {
	REF struct fnode *me;
	me = container_of(self, struct fnode, _mf_fsuperplop);

	/* Remove from `fallnodes_list'. */
	COMPILER_READ_BARRIER();
	if (LIST_ISBOUND(me, fn_allnodes)) {
		COMPILER_READ_BARRIER();
		if (fallnodes_tryacquire()) {
			COMPILER_READ_BARRIER();
			if (LIST_ISBOUND(me, fn_allnodes)) {
				fallnodes_remove(me);
				LIST_ENTRY_UNBOUND_INIT(&me->fn_allnodes);
			}
			COMPILER_READ_BARRIER();
			fallnodes_release();
		} else {
			me->_mf_lop.lo_func = &fnode_delete_remove_from_allnodes_lop; /* Inherit reference */
			lockop_enqueue(&fallnodes_lockops, &me->_mf_lop);
			_fallnodes_reap();
			return;
		}
	}
	fnode_delete_remove_from_allnodes_postlop(&me->_mf_plop); /* Inherit reference */
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(fsuper) *
NOTHROW(LOCKOP_CC fnode_delete_remove_from_changed_lop)(Toblockop(fsuper) *__restrict self,
                                                        struct fsuper *__restrict UNUSED(obj)) {
	REF struct fnode *me;
	me = container_of(self, struct fnode, _mf_fsuperlop);
	if (LIST_ISBOUND(me, fn_changed)) {
		LIST_UNBIND(me, fn_changed);
		decref_nokill(me); /* Reference from the `fn_changed' list. */
	}

	me->_mf_fsuperplop.oplo_func = &fnode_delete_remove_from_changed_postlop; /* Inherit reference */
	return &me->_mf_fsuperplop;
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC fnode_delete_remove_from_byino_postlop)(Tobpostlockop(fsuper) *__restrict self,
                                                          struct fsuper *__restrict obj) {
	REF struct fnode *me;
	me = container_of(self, struct fnode, _mf_fsuperplop);

	/* Remove from `obj->fs_changednodes'. */
	COMPILER_READ_BARRIER();
	if (LIST_ISBOUND(me, fn_changed)) {
		COMPILER_READ_BARRIER();
		if (fsuper_changednodes_tryacquire(obj)) {
			COMPILER_READ_BARRIER();
			if (LIST_ISBOUND(me, fn_changed)) {
				LIST_UNBIND(me, fn_changed);
				decref_nokill(me); /* Reference from the `fn_changed' list. */
			}
			COMPILER_READ_BARRIER();
			fsuper_changednodes_release(obj);
		} else {
			me->_mf_fsuperlop.olo_func = &fnode_delete_remove_from_changed_lop; /* Inherit reference */
			oblockop_enqueue(&obj->fs_changednodes_lops, &me->_mf_fsuperlop);
			_fsuper_changednodes_reap(obj);
			return;
		}
	}

	fnode_delete_remove_from_changed_postlop(&me->_mf_fsuperplop, obj); /* Inherit reference */
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(fsuper) *
NOTHROW(LOCKOP_CC fnode_delete_remove_from_byino_lop)(Toblockop(fsuper) *__restrict self,
                                                      struct fsuper *__restrict obj) {
	REF struct fnode *me;
	me = container_of(self, struct fnode, _mf_fsuperlop);
	COMPILER_READ_BARRIER();
	if (me->fn_supent.rb_rhs != FSUPER_NODES_DELETED) {
		if unlikely(me->_fn_suplop.olo_func == &fnode_add2sup_lop) {
			/* Device is still being async-added to the nodes tree.
			 * In this case, we must wait for it to finish doing so
			 * before trying to repeat the remove-from-tree lop. */
			me->_mf_fsuperlop.olo_func = &fnode_delete_remove_from_byino_lop;
			oblockop_enqueue(&obj->fs_nodeslockops, &me->_mf_fsuperlop); /* Retry later... */
			return NULL;
		}
		fsuper_nodes_removenode(obj, me);
		atomic_write(&me->fn_supent.rb_rhs, FSUPER_NODES_DELETED);
	}
	me->_mf_fsuperplop.oplo_func = &fnode_delete_remove_from_byino_postlop; /* Inherit reference */
	return &me->_mf_fsuperplop;
}



/* Internal implementation of `fnode_delete()' (don't call this one
 * unless you know that you're doing; otherwise, you may cause race
 * conditions that can result in data corruption) */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fnode_delete_impl)(/*inherit(always)*/ REF struct fnode *__restrict self) {
	struct fsuper *super = self->fn_super;

	/* Remove from the superblock's INode tree. */
	if (atomic_read(&self->fn_supent.rb_rhs) != FSUPER_NODES_DELETED) {
again_lock_super:
		if (fsuper_nodes_trywrite(super)) {
			COMPILER_READ_BARRIER();
			if (self->fn_supent.rb_rhs != FSUPER_NODES_DELETED) {
				if unlikely(self->_fn_suplop.olo_func == &fnode_add2sup_lop) {
					/* Reap+retry */
					_fsuper_nodes_endwrite(super);
					_fsuper_nodes_reap(super);
					goto again_lock_super;
				}
				fsuper_nodes_removenode(super, self);
				atomic_write(&self->fn_supent.rb_rhs, FSUPER_NODES_DELETED);
			}
			fsuper_nodes_endwrite(super);
		} else {
			self->_mf_fsuperlop.olo_func = &fnode_delete_remove_from_byino_lop; /* Inherit reference */
			oblockop_enqueue(&super->fs_nodeslockops, &self->_mf_fsuperlop);
			_fsuper_nodes_reap(super);
			return;
		}
	}
	fnode_delete_remove_from_byino_postlop(&self->_mf_fsuperplop, super); /* Inherit reference */
}

PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL fnode_delete_strt)(struct fnode *__restrict self) {
	uintptr_t old_flags;

	/* Mark the file as deleted (and make available use of the timestamp fields) */
	mfile_tslock_acquire(self);
	old_flags = atomic_fetchor(&self->mf_flags,
	                           MFILE_F_DELETED | MFILE_F_NOATIME | MFILE_FN_NODIRATIME |
	                           MFILE_F_NOMTIME | MFILE_F_CHANGED | MFILE_F_ATTRCHANGED |
	                           MFILE_F_FIXEDFILESIZE | MFILE_FN_ATTRREADONLY |
	                           MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_READONLY);
	mfile_tslock_release(self);

	/* Delete global reference to the file-node. */
	if ((old_flags & MFILE_FN_GLOBAL_REF) &&
	    (atomic_fetchand(&self->mf_flags, ~(MFILE_FN_GLOBAL_REF)) & MFILE_FN_GLOBAL_REF))
		decref_nokill(self);

	/* Also clear the PERSISTENT flag */
	if (old_flags & MFILE_F_PERSISTENT)
		atomic_and(&self->mf_flags, ~MFILE_F_PERSISTENT);

	return !(old_flags & MFILE_F_DELETED);
}

PUBLIC NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL fnode_delete_strt_with_tslock)(struct fnode *__restrict self) {
	uintptr_t old_flags;

	/* Mark the file as deleted (and make available use of the timestamp fields) */
	old_flags = atomic_fetchor(&self->mf_flags,
	                           MFILE_F_DELETED | MFILE_F_NOATIME | MFILE_FN_NODIRATIME |
	                           MFILE_F_NOMTIME | MFILE_F_CHANGED | MFILE_F_ATTRCHANGED |
	                           MFILE_F_FIXEDFILESIZE | MFILE_FN_ATTRREADONLY |
	                           MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_READONLY);

	/* Delete global reference to the file-node. */
	if ((old_flags & MFILE_FN_GLOBAL_REF) &&
	    (atomic_fetchand(&self->mf_flags, ~(MFILE_FN_GLOBAL_REF)) & MFILE_FN_GLOBAL_REF))
		decref_nokill(self);

	/* Also clear the PERSISTENT flag */
	if (old_flags & MFILE_F_PERSISTENT)
		atomic_and(&self->mf_flags, ~MFILE_F_PERSISTENT);

	return !(old_flags & MFILE_F_DELETED);
}




/* Perform all of the async work needed for deleting `self' as the result of `fn_nlink == 0'
 * This function will do the following (asynchronously if necessary)
 *  - Set flags: MFILE_F_DELETED | MFILE_F_NOATIME | MFILE_FN_NODIRATIME |
 *               MFILE_F_NOMTIME | MFILE_F_CHANGED | MFILE_F_ATTRCHANGED |
 *               MFILE_F_FIXEDFILESIZE    |    MFILE_FN_ATTRREADONLY     |
 *               MFILE_F_NOUSRMMAP |  MFILE_F_NOUSRIO  |  MFILE_F_READONLY
 *    If `MFILE_F_DELETED' was already set, none of the below are done!
 *  - Unlink `self->fn_supent' (if bound)
 *  - Unlink `self->fn_changed' (if bound)
 *  - Unlink `self->fn_allnodes' (if bound)
 *  - Call `mfile_delete()' (technically `mfile_delete_impl()') */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fnode_delete)(struct fnode *__restrict self) {
	assertf(!fnode_isdevice(self), "You need to use `device_delete()' in this case!");
	assertf(!fnode_issuper(self), "You need to use `super_delete()' in this case!");

	if (!fnode_delete_strt(self))
		return; /* Already deleted, or deletion already in progress. */
	incref(self);
	fnode_delete_impl(self);
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_NODE_C */
