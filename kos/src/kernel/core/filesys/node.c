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
#ifndef GUARD_KERNEL_CORE_FILESYS_NODE_C
#define GUARD_KERNEL_CORE_FILESYS_NODE_C 1
#define __WANT_MFILE__mf_lop
#define __WANT_MFILE__mf_plop
#define __WANT_MFILE__mf_fsuperlop
#define __WANT_MFILE__mf_fsuperplop
#define __WANT_MFILE__mf_lopX
#define __WANT_FNODE__fn_chnglop
#define __WANT_FNODE__fn_alllop
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/allnodes.h>
#include <kernel/fs/blkdev.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/node.h>
#include <kernel/fs/ramfs.h>
#include <kernel/fs/super.h>
#include <kernel/mman/nopf.h>
#include <sched/cred.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <kos/except.h>
#include <kos/except/reason/fs.h>
#include <kos/except/reason/inval.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>


/* Filenode tree operations. (for `struct fsuper::fs_nodes') */
#define RBTREE_LEFT_LEANING
#define RBTREE(name)               fnode_tree_##name
#define RBTREE_T                   struct fnode
#define RBTREE_Tkey                ino_t
#define RBTREE_GETNODE(self)       (self)->fn_supent
#define RBTREE_GETKEY(self)        (self)->fn_ino
#define RBTREE_ISRED(self)         ((self)->mf_flags & _MFILE_FN__RBRED)
#define RBTREE_SETRED(self)        (void)((self)->mf_flags |= _MFILE_FN__RBRED)
#define RBTREE_SETBLACK(self)      (void)((self)->mf_flags &= ~_MFILE_FN__RBRED)
#define RBTREE_FLIPCOLOR(self)     (void)((self)->mf_flags ^= _MFILE_FN__RBRED)
#define RBTREE_COPYCOLOR(dst, src) (void)((dst)->mf_flags = ((dst)->mf_flags & ~_MFILE_FN__RBRED) | ((src)->mf_flags & _MFILE_FN__RBRED))
#define RBTREE_CC                  FCALL
#define RBTREE_NOTHROW             NOTHROW
#define RBTREE_DECL                FUNDEF
#define RBTREE_IMPL                PUBLIC
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */


/* No-op callback for `no_wrattr' (for RAM filesystems) */
PUBLIC ATTR_CONST NONNULL((1)) void
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
	STATIC_ASSERT_MSG(offsetof(struct fnode, fn_changed.le_prev) ==
	                  offsetof(struct fnode, _fn_chnglop.olo_func),
	                  "This is required for the ATOMIC_CMPXCH "
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
		if (ATOMIC_CMPXCH(self->_fn_chnglop.olo_func,
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
NOTHROW(FCALL fnode_v_changed)(struct mfile *__restrict self,
                               uintptr_t old_flags,
                               uintptr_t UNUSED(new_flags)) {
	struct fnode *me = mfile_asnode(self);
	if (!(old_flags & (MFILE_F_CHANGED | MFILE_F_ATTRCHANGED))) {
		/* Add to the list of changed file-nodes the first time around. */
		fnode_add2changed(me);
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LOCKOP_CC fnode_v_destroy_rmall_postlop)(struct postlockop *__restrict self) {
	struct fnode *me = container_of(self, struct fnode, _mf_plop);
	/* Destroy the underlying mem-file. */
	mfile_destroy(_fnode_asfile(me));
}

PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(LOCKOP_CC fnode_v_destroy_rmallsuper_lop)(struct lockop *__restrict self) {
	struct fsuper *me = container_of(self, struct fsuper, fs_root._mf_lop);
	assert(me->fs_root._fn_alllop.lo_func != &fnode_add2all_lop);
	if (LIST_ISBOUND(me, fs_root.fn_allsuper))
		LIST_REMOVE(me, fs_root.fn_allsuper);
	me->fs_root._mf_plop.plo_func = &fnode_v_destroy_rmall_postlop;
	return &me->fs_root._mf_plop;
}

PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(LOCKOP_CC fnode_v_destroy_rmallnodes_lop)(struct lockop *__restrict self) {
	struct fnode *me = container_of(self, struct fnode, _mf_lop);
	if unlikely(me->_fn_alllop.lo_func == &fnode_add2all_lop) {
		/* Must let `fnode_add2all_lop()' finish first! */
		me->_mf_lop.lo_func = &fnode_v_destroy_rmallnodes_lop;
		lockop_enqueue(&fallnodes_lockops, &me->_mf_lop);
		return NULL;
	}
	if (LIST_ISBOUND(me, fn_allnodes))
		LIST_REMOVE(me, fn_allnodes);
	me->_mf_plop.plo_func = &fnode_v_destroy_rmall_postlop;
	return &me->_mf_plop;
}


PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC fnode_v_destroy_rmsuper_postlop)(Tobpostlockop(fsuper) *__restrict self,
                                                   struct fsuper *__restrict obj) {
	struct fnode *me = container_of(self, struct fnode, _mf_fsuperplop);

	/* Remove the node from the list of all nodes. */
again_unbind_allnodes:
	COMPILER_READ_BARRIER();
	if (LIST_ISBOUND(me, fn_allnodes)) {
		if (fallnodes_tryacquire()) {
			COMPILER_READ_BARRIER();
			if unlikely(me->_fn_alllop.lo_func == &fnode_add2all_lop) {
				fallnodes_release(); /* This should reap & invoke fnode_add2all_lop() */
				goto again_unbind_allnodes;
			}
			if (LIST_ISBOUND(me, fn_allnodes))
				LIST_REMOVE(me, fn_allnodes);
			fallnodes_release();
		} else {
			DBG_memset(me->_mf_lopX, 0xcc, sizeof(me->_mf_lopX));
			me->_mf_lop.lo_func = &fnode_v_destroy_rmallnodes_lop;
			lockop_enqueue(&fallnodes_lockops, &me->_mf_lop);
			_fallnodes_reap();
			return;
		}
	}

	/* Destroy the underlying mem-file. */
	mfile_destroy(_fnode_asfile(me));
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(fsuper) *
NOTHROW(LOCKOP_CC fnode_v_destroy_rmsuper_lop)(Toblockop(fsuper) *__restrict self,
                                               struct fsuper *__restrict obj) {
	struct fnode *me = container_of(self, struct fnode, _mf_fsuperlop);
	COMPILER_READ_BARRIER();
	if (me->fn_supent.rb_lhs != FSUPER_NODES_DELETED) {
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
NOTHROW(FCALL fnode_v_destroy)(struct fnode *__restrict self) {
	assertf(!(self->mf_flags & MFILE_FN_GLOBAL_REF),
	        "Then why are we being destroyed?");

	/* Remove the node from its superblock's node-tree, as well
	 * as  from the  global list  of all  nodes or superblocks. */
	if (fnode_issuper(self)) {
		struct fsuper *me = fnode_assuper(self);
		if (LIST_ISBOUND(me, fs_root.fn_allsuper)) {
			/* Remove from `fallsuper_list' */
			if (fallsuper_tryacquire()) {
				assert(me->fs_root._fn_alllop.lo_func != &fnode_add2all_lop);
				if (LIST_ISBOUND(me, fs_root.fn_allsuper))
					LIST_REMOVE(me, fs_root.fn_allsuper);
				fallsuper_release();
			} else {
				DBG_memset(me->fs_root._mf_lopX, 0xcc, sizeof(me->fs_root._mf_lopX));
				me->fs_root._mf_lop.lo_func = &fnode_v_destroy_rmallsuper_lop;
				lockop_enqueue(&fallsuper_lockops, &me->fs_root._mf_lop);
				_fallsuper_reap();
				return;
			}
		}
	} else {
		REF struct fsuper *super = self->fn_super;
		/* Remove from the associated superblock's list of nodes. */
		if (ATOMIC_READ(self->fn_supent.rb_lhs) != FSUPER_NODES_DELETED) {
			if (fsuper_nodes_trywrite(super)) {
				COMPILER_READ_BARRIER();
				if (self->fn_supent.rb_lhs != FSUPER_NODES_DELETED) {
					assert(super->fs_nodes != FSUPER_NODES_DELETED);
					fsuper_nodes_removenode(super, self);
				}
				fsuper_nodes_endwrite(super);
			} else {
				self->_mf_fsuperlop.olo_func = &fnode_v_destroy_rmsuper_lop;
				oblockop_enqueue(&super->fs_nodeslockops, &self->_mf_fsuperlop);
				_fsuper_nodes_reap(super);
				decref_unlikely(super);
				return;
			}
		}
		decref_unlikely(super);

		/* Remove the node from the list of all nodes. */
again_unbind_allnodes:
		COMPILER_READ_BARRIER();
		if (LIST_ISBOUND(self, fn_allnodes)) {
			if (fallnodes_tryacquire()) {
				COMPILER_READ_BARRIER();
				if unlikely(self->_fn_alllop.lo_func == &fnode_add2all_lop) {
					fallnodes_release(); /* This should reap & invoke fnode_add2all_lop() */
					goto again_unbind_allnodes;
				}
				if (LIST_ISBOUND(self, fn_allnodes))
					LIST_REMOVE(self, fn_allnodes);
				fallnodes_release();
			} else {
				DBG_memset(self->_mf_lopX, 0xcc, sizeof(self->_mf_lopX));
				self->_mf_lop.lo_func = &fnode_v_destroy_rmallnodes_lop;
				lockop_enqueue(&fallnodes_lockops, &self->_mf_lop);
				_fallnodes_reap();
				return;
			}
		}
	}

	/* Destroy the underlying mem-file. */
	mfile_destroy(_fnode_asfile(self));
}



/* For use with `_fn_alllop': asynchronously add the node to the list of all nodes.
 * This function needs to be exposed publicly because it being set requires special
 * care if set during custom fnode destructors.
 * Note that the default `fnode_v_destroy()' includes correct handling for this. */
PUBLIC NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(LOCKOP_CC fnode_add2all_lop)(struct lockop *__restrict self) {
	STATIC_ASSERT(offsetof(struct fnode, fn_allnodes.le_prev) == offsetof(struct fnode, _fn_alllop.lo_func));
	struct fnode *me = container_of(self, struct fnode, _fn_alllop);
	assert(me->_fn_alllop.lo_func == &fnode_add2all_lop);
	ATOMIC_WRITE(me->fn_allnodes.le_prev, &fallnodes_list.lh_first); /* This write needs to be atomic */
	if ((me->fn_allnodes.le_next = fallnodes_list.lh_first) != NULL)
		me->fn_allnodes.le_next->fn_allnodes.le_prev = &me->fn_allnodes.le_next;
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
NOTHROW(FCALL fnode_init_add2all)(struct fnode *__restrict self) {
	/* Yes: we do a raw init! */
	DBG_memset(&self->fn_allnodes, 0xcc, sizeof(self->fn_allnodes));
	if (fallnodes_tryacquire()) {
		LIST_INSERT_HEAD(&fallnodes_list, self, fn_allnodes);
		fallnodes_release();
	} else {
		/* Use a lock operator. */
		self->_fn_alllop.lo_func = &fnode_add2all_lop;
		COMPILER_WRITE_BARRIER();
		lockop_enqueue(&fallnodes_lockops, &self->_fn_alllop);
		_fallnodes_reap();
	}
}






/* High-level file-node functions */

/* Change permissions, SUID/SGID and the sticky bit of the given INode (flagsmask: 07777)
 * The new file mode is calculated as `(old_mode & perm_mask) | perm_flag', before  being
 * masked by what the underlying filesystem is capable of representing.
 * @return: * : The old file mode
 * @throw: E_FSERROR_READONLY:    The `MFILE_FM_ATTRREADONLY' flag is (or was) set.
 * @throw: E_INSUFFICIENT_RIGHTS: `check_permissions' is true and you're not allowed to do this. */
PUBLIC NONNULL((1)) mode_t KCALL
fnode_chmod(struct fnode *__restrict self, mode_t perm_mask,
            mode_t perm_flag, bool check_permissions)
		THROWS(E_FSERROR_READONLY, E_INSUFFICIENT_RIGHTS) {
	mode_t old_mode, new_mode;

	/* Check if file attributes may be modified. */
	if unlikely(self->mf_flags & MFILE_FM_ATTRREADONLY)
		THROW(E_FSERROR_READONLY);

	/* Only these bits can be modified at all! */
	perm_mask &= 07777;
	perm_flag &= 07777;

#ifndef CONFIG_EVERYONE_IS_ROOT
again:
#endif /* !CONFIG_EVERYONE_IS_ROOT */
	mfile_tslock_acquire(self);
#ifndef CONFIG_EVERYONE_IS_ROOT
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
#else /* !CONFIG_EVERYONE_IS_ROOT */
	(void)check_permissions;
#endif /* CONFIG_EVERYONE_IS_ROOT */

	old_mode = self->fn_mode;
	new_mode = (old_mode & perm_mask) | perm_flag;
	/* Set the new file mode. */
	ATOMIC_WRITE(self->fn_mode, new_mode);
	mfile_tslock_release(self);
	/* Broadcast that mode bits have changed. */
	if (old_mode != new_mode)
		mfile_changed(self, MFILE_F_ATTRCHANGED);
	return old_mode;
}



/* Change the owner and group of the given file. NOTE: either attribute is only
 * altered when  `owner != (uid_t)-1'  and  `group != (gid_t)-1'  respectively.
 * @throw: E_FSERROR_READONLY:    The `MFILE_FM_ATTRREADONLY' flag is (or was) set.
 * @throw: E_INSUFFICIENT_RIGHTS: `check_permissions' is true and you're not allowed to do this.
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_CHOWN_UNSUPP_UID:uid: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_CHOWN_UNSUPP_GID:gid: [...] */
PUBLIC NONNULL((1)) void KCALL
fnode_chown(struct fnode *__restrict self, uid_t owner, gid_t group,
            USER CHECKED uid_t *pold_owner, USER CHECKED gid_t *pold_group,
            bool check_permissions)
		THROWS(E_SEGFAULT, E_FSERROR_READONLY,
		       E_INSUFFICIENT_RIGHTS, E_INVALID_ARGUMENT_BAD_VALUE) {
	bool changed = false;
	uid_t old_owner, new_owner;
	gid_t old_group, new_group;

	/* Check if file attributes may be modified. */
	if unlikely(self->mf_flags & MFILE_FM_ATTRREADONLY)
		THROW(E_FSERROR_READONLY);

	/* Verify that the filesystem allows the given owner/group */
	if (owner != (uid_t)-1 && !fsuper_validuid(self->fn_super, owner))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE, E_INVALID_ARGUMENT_CONTEXT_CHOWN_UNSUPP_UID, owner);
	if (group != (gid_t)-1 && !fsuper_validgid(self->fn_super, group))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE, E_INVALID_ARGUMENT_CONTEXT_CHOWN_UNSUPP_GID, group);

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
#ifndef CONFIG_EVERYONE_IS_ROOT
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
#else /* !CONFIG_EVERYONE_IS_ROOT */
		(void)check_permissions;
#endif /* CONFIG_EVERYONE_IS_ROOT */

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
			ATOMIC_WRITE(self->fn_mode, mode);
		}

		/* Actually write the new owner/group */
		self->fn_uid = new_owner;
		self->fn_gid = new_group;
		changed = true;
	}
	mfile_tslock_release(self);

	/* Broadcast that owner values have changed. */
	if (changed)
		mfile_changed(self, MFILE_F_ATTRCHANGED);
}



/* Change all non-NULL the timestamp that are given.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: The `MFILE_F_DELETED' is set.
 * @throw: E_FSERROR_READONLY: The `MFILE_FM_ATTRREADONLY' flag is (or was) set. */
PUBLIC NONNULL((1)) void KCALL
mfile_chtime(struct mfile *__restrict self,
             struct timespec const *new_atime,
             struct timespec const *new_mtime,
             struct timespec const *new_ctime)
		THROWS(E_FSERROR_READONLY) {
	if unlikely(self->mf_flags & MFILE_FM_ATTRREADONLY)
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
	if (new_atime) {
		self->mf_atime.tv_sec  = new_atime->tv_sec;
		self->mf_atime.tv_nsec = new_atime->tv_nsec;
	}
	if (new_mtime) {
		self->mf_mtime.tv_sec  = new_mtime->tv_sec;
		self->mf_mtime.tv_nsec = new_mtime->tv_nsec;
	}
	if (new_ctime) {
		self->mf_ctime.tv_sec  = new_ctime->tv_sec;
		self->mf_ctime.tv_nsec = new_ctime->tv_nsec;
	}
	mfile_tslock_release(self);

	/* Mark attributes of this file as having changed. */
	mfile_changed(self, MFILE_F_ATTRCHANGED);
}



/* Clear the `MFILE_F_ATTRCHANGED' flag and  remove `self' from the  associated
 * superblock's list of changed nodes. If this succeeds, invoke the `no_wrattr'
 * operator. If said operator returns  with an exception, set the  attr-changed
 * flag once again by means of `mfile_changed(self, MFILE_F_ATTRCHANGED)' */
PUBLIC NONNULL((1)) void KCALL
fnode_syncattr(struct fnode *__restrict self)
		THROWS(E_WOULDBLOCK, E_IOERROR, ...) {
	struct fsuper *super;
	uintptr_t old_flags;

	/* Clear the `MFILE_F_ATTRCHANGED' flag. */
	do {
		old_flags = ATOMIC_READ(self->mf_flags);
		if (!(old_flags & MFILE_F_ATTRCHANGED) || (old_flags & MFILE_F_DELETED))
			return;
	} while (!ATOMIC_CMPXCH_WEAK(self->mf_flags, old_flags,
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
		if (ATOMIC_READ(self->mf_flags) & MFILE_F_CHANGED)
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
PUBLIC NONNULL((1)) void KCALL
fnode_syncdata(struct fnode *__restrict self)
		THROWS(E_WOULDBLOCK, E_IOERROR, ...) {
	struct fsuper *super;
	uintptr_t old_flags;

	/* Clear the `MFILE_F_CHANGED' flag. */
	do {
		old_flags = ATOMIC_READ(self->mf_flags);
		if (!(old_flags & MFILE_F_CHANGED) || (old_flags & MFILE_F_DELETED))
			return;
	} while (!ATOMIC_CMPXCH_WEAK(self->mf_flags, old_flags,
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
		if (ATOMIC_READ(self->mf_flags) & MFILE_F_ATTRCHANGED)
			fnode_add2changed(self);
	}

	/* Write modified attributes to disk. */
	TRY {
		mfile_sync(self);

		/* Special case: if we're a block device, also invoke its sync operator. */
		if (fnode_isblkdev(self)) {
			struct blkdev *me;
			struct blkdev_ops const *ops;
			me  = fnode_asblkdev(self);
			ops = blkdev_getops(me);
			if (ops->bdo_sync != NULL)
				(*ops->bdo_sync)(me);
		}

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
PUBLIC ATTR_PURE WUNUSED NONNULL((1)) bool FCALL
fnode_mayaccess(struct fnode *__restrict self,
                unsigned int type)
		THROWS(E_WOULDBLOCK) {
	unsigned int how;
	mode_t mode = ATOMIC_READ(self->fn_mode);
	for (how = 1; how <= 4; how <<= 1) {
		if (!(type & how))
			continue; /* Access not checked. */
		if likely(mode & how)
			continue; /* Access is allowed for everyone. */
		if (mode & (how << 3)) {
			gid_t gid = ATOMIC_READ(self->fn_gid);
			if likely(cred_isfsgroupmember(gid))
				continue; /* The calling thread's user is part of the file owner's group */
		}
		if (mode & (how << 6)) {
			uid_t uid = ATOMIC_READ(self->fn_uid);
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
PUBLIC NONNULL((1)) void FCALL
fnode_access(struct fnode *__restrict self, unsigned int type)
		THROWS(E_FSERROR_ACCESS_DENIED) {
	if unlikely(!fnode_mayaccess(self, type))
		THROW(E_FSERROR_ACCESS_DENIED);
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_NODE_C */
