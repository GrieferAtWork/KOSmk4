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
#ifndef GUARD_KERNEL_CORE_FILESYS_DEVFS_C
#define GUARD_KERNEL_CORE_FILESYS_DEVFS_C 1
#define __WANT_MFILE__mf_lop
#define __WANT_MFILE__mf_plop
#define __WANT_FS_INIT
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/fs/allnodes.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/devnode.h>
#include <kernel/fs/filesys.h>
#include <kernel/fs/node.h>
#include <kernel/fs/super.h>
#include <kernel/paging.h>
#include <sched/task.h>

#include <linux/magic.h>

#include <assert.h>
#include <stddef.h>

#undef RBTREE_LEFT_LEANING
#define RBTREE_WANT_PREV_NEXT_NODE
#define RBTREE_OMIT_REMOVE
#define RBTREE(name)           devfs_bynametree_##name
#define RBTREE_T               struct fdevfsnode
#define RBTREE_Tkey            char const *
#define RBTREE_GETNODE(self)   (self)->dfn_byname_node
#define RBTREE_GETKEY(self)    fdevfsnode_getname(self)
#define RBTREE_ISRED(self)     ((self)->_fdevfsnode_devnode_ _fdevnode_node_ _fnode_file_ mf_flags & _MFILE_DEVFS_BYNAME_RED)
#define RBTREE_SETRED(self)    (void)((self)->_fdevfsnode_devnode_ _fdevnode_node_ _fnode_file_ mf_flags |= _MFILE_DEVFS_BYNAME_RED)
#define RBTREE_SETBLACK(self)  (void)((self)->_fdevfsnode_devnode_ _fdevnode_node_ _fnode_file_ mf_flags &= ~_MFILE_DEVFS_BYNAME_RED)
#define RBTREE_CC              FCALL
#define RBTREE_NOTHROW         NOTHROW
#define RBTREE_DECL            FUNDEF
#define RBTREE_IMPL            PUBLIC
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN

PUBLIC struct ffilesys devfs_filesys = {
	.ffs_link = { .le_next = NULL, .le_prev = &ffilesys_formats_list.lh_first },
	.ffs_drv  = &drv_self,
	{ .ffs_single = &devfs.rs_sup },
	.ffs_flags = FFILESYS_F_SINGLE,
	.ffs_name  = "devfs",
};

PRIVATE struct fsuper_ops const devfs_ops = {
	.so_validuid       = NULL,
	.so_validgid       = NULL,
	.so_truncate_atime = NULL,
	.so_truncate_mtime = NULL,
	.so_truncate_ctime = NULL,
	.so_sync           = NULL,
	.so_clearcache     = NULL,
	.so_statfs         = NULL,
	.so_fdir = {
		.dno_node = {
			.no_file = {
				.mo_destroy    = (void (KCALL *)(struct mfile *__restrict))(void *)(uintptr_t)-1, /* Must never be called */
				.mo_newpart    = NULL,
				.mo_loadblocks = NULL,
				.mo_saveblocks = NULL,
				.mo_changed    = &fnode_v_changed,
				.mo_stream     = NULL,
				.mo_vio        = NULL,
			},
			.no_wrattr = &fnode_v_wrattr_noop,
		},
		.dno_lookup       = NULL, /* TODO: devfs_byname_tree + RAMFS_LOOKUP */
		.dno_lookup_fnode = NULL, /* TODO: devfs_byname_tree + RAMFS_LOOKUP */
		.dno_enum         = NULL, /* TODO: devfs_byname_tree + RAMFS_ENUM */
		.dno_mkfile       = NULL, /* TODO: RAMFS_MKFILE */
		.dno_unlink       = NULL, /* TODO: devfs_byname_tree + RAMFS_UNLINK */
		.dno_rename       = NULL, /* TODO: devfs_byname_tree + RAMFS_RENAME */
	},
};

/* The /dev/ filesystem superblock */
PUBLIC struct ramfs_super devfs = {
	.rs_sup = {
		.fs_nodes           = &devfs.rs_sup.fs_root.dn_node,
		.fs_nodeslock       = ATOMIC_RWLOCK_INIT,
		.fs_nodeslockops    = SLIST_HEAD_INITIALIZER(devfs.rs_sup.fs_nodeslockops),
		.fs_mounts          = LIST_HEAD_INITIALIZER(devfs.rs_sup.fs_mounts),
		.fs_mountslock      = ATOMIC_RWLOCK_INIT,
		.fs_mountslockops   = SLIST_HEAD_INITIALIZER(devfs.rs_sup.fs_mountslockops),
		.fs_sys             = &devfs_filesys,
		.fs_dev             = NULL,
		.fs_feat = {
			.sf_filesize_max       = (pos_t)-1,
			.sf_uid_max            = (uid_t)-1,
			.sf_gid_max            = (gid_t)-1,
			.sf_symlink_max        = (pos_t)-1,
			.sf_link_max           = (nlink_t)-1,
			.sf_magic              = DEVFS_SUPER_MAGIC,
			.sf_rec_incr_xfer_size = PAGESIZE,
			.sf_rec_max_xfer_size  = PAGESIZE,
			.sf_rec_min_xfer_size  = PAGESIZE,
			.sf_rec_xfer_align     = PAGESIZE,
			.sf_name_max           = (u16)-1,
			.sf_filesizebits       = BITSOF(pos_t),
		},
		.fs_changednodes_lock = ATOMIC_LOCK_INIT,
		.fs_changednodes_lops = SLIST_HEAD_INITIALIZER(devfs.rs_sup.fs_changednodes_lops),
		.fs_changednodes      = LIST_HEAD_INITIALIZER(devfs.rs_sup.fs_changednodes),
		.fs_changedsuper      = LIST_ENTRY_UNBOUND_INITIALIZER,
		.fs_root = {
			.dn_node = {
				.fn_file = {
					.mf_refcnt     = 3, /* +1: devfs, +1: MFILE_FN_GLOBAL_REF, +1: MFILE_F_PERSISTENT */
					.mf_ops        = &devfs_ops.so_fdir.dno_node.no_file,
					.mf_lock       = ATOMIC_RWLOCK_INIT,
					.mf_parts      = MFILE_PARTS_ANONYMOUS,
					.mf_initdone   = SIG_INIT,
					.mf_lockops    = SLIST_HEAD_INITIALIZER(devfs.rs_sup.fs_root.dn_node.fn_file.mf_lockops),
					.mf_changed    = { MFILE_PARTS_ANONYMOUS },
					.mf_part_amask = PAGEMASK,
					.mf_blockshift = PAGESHIFT,
					.mf_flags      = (MFILE_FS_NOSUID | MFILE_FN_GLOBAL_REF | MFILE_FS_NOEXEC |
					                  MFILE_F_NOATIME | MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |
					                  MFILE_F_NOMTIME | MFILE_F_PERSISTENT | MFILE_F_FIXEDFILESIZE |
					                  MFILE_FM_ATTRREADONLY),
					.mf_trunclock  = 0,
					.mf_filesize   = ATOMIC64_INIT((uint64_t)-1),
					{{
						/* TODO: Have an initializer that copies `boottime' into these 3! */
						.mf_atime = { .tv_sec = 0, .tv_nsec = 0 },
						.mf_mtime = { .tv_sec = 0, .tv_nsec = 0 },
						.mf_ctime = { .tv_sec = 0, .tv_nsec = 0 },
					}},
				},
				.fn_nlink    = 1,
				.fn_mode     = S_IFDIR | 0755,
				.fn_uid      = 0, /* root */
				.fn_gid      = 0, /* root */
				.fn_ino      = 0, /* Fixed INO for root directory */
				.fn_super    = &devfs.rs_sup,
				.fn_changed  = LIST_ENTRY_UNBOUND_INITIALIZER,
				.fn_supent   = { NULL, NULL },
				{.fn_allsuper = { NULL, &fallsuper_list.lh_first }},
			},
			.dn_parent = NULL,
		},
	},
};


/* Default operators for `struct fdevfsnode_ops' */

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LOCKOP_CC fdevfsnode_v_destroy_postlop)(struct postlockop *__restrict self) {
	struct fdevfsnode *me;
	me = container_of(self, struct fdevfsnode, dfn_devnode.dn_node.fn_file._mf_plop);
	decref_likely(me->dfn_dirent);
	fdevnode_v_destroy(&me->dfn_devnode.dn_node.fn_file);
}
PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(LOCKOP_CC fdevfsnode_v_destroy_lop)(struct lockop *__restrict self) {
	struct fdevfsnode *me;
	me = container_of(self, struct fdevfsnode, dfn_devnode.dn_node.fn_file._mf_lop);
	devfs_byname_removenode(me);
	me->dfn_devnode.dn_node.fn_file._mf_plop.plo_func = &fdevfsnode_v_destroy_postlop;
	return &me->dfn_devnode.dn_node.fn_file._mf_plop;
}


/* Destructor  (asynchronously  removes  itself  from
 * `devfs_byname_tree' and does `decref(dfn_dirent)') */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fdevfsnode_v_destroy)(struct mfile *__restrict self) {
	struct fdevfsnode *me;
	me = mfile_asdevfsnode(self);
	assert(me->dfn_devnode.dn_node.fn_super == &devfs.rs_sup);

	/* Must remove `me' from `devfs_byname_tree' */
	if (devfs_byname_trywrite()) {
		devfs_byname_removenode(me);
		devfs_byname_endwrite();
		decref_likely(me->dfn_dirent);
	} else {
		/* Use a lock-op to do the removal */
		me->dfn_devnode.dn_node.fn_file._mf_lop.lo_func = &fdevfsnode_v_destroy_lop;
		lockop_enqueue(&devfs_byname_lops, &me->dfn_devnode.dn_node.fn_file._mf_lop);
		_devfs_byname_reap();
		return;
	}
	fdevnode_v_destroy(&me->dfn_devnode.dn_node.fn_file);
}





/* By-name lookup of devices in /dev/ */
PUBLIC struct atomic_rwlock devfs_byname_lock    = ATOMIC_RWLOCK_INIT;
PUBLIC struct lockop_slist devfs_byname_lops     = SLIST_HEAD_INITIALIZER(devfs_byname_lops);
PUBLIC RBTREE_ROOT(fdevfsnode) devfs_byname_tree = NULL;




/* Register a given device `self' within global control structures:
 *  - devfs_byname_tree
 *  - devfs.fs_nodes
 *  - fallnodes_list
 * This function never creates  additional references for `self',  but
 * leaves the job of setting up  global references (though use of  the
 * flags `MFILE_FN_GLOBAL_REF' and `MFILE_F_PERSISTENT') to the caller */
FUNDEF NONNULL((1)) unsigned int FCALL
devbuilder_register(struct fdevfsnode *__restrict self)
		THROWS(E_WOULDBLOCK) {
	unsigned int result;
	assert(self->dfn_devnode.dn_node.fn_ino ==
	       devfs_devnode_makeino(self->dfn_devnode.dn_node.fn_mode,
	                             self->dfn_devnode.dn_devno));

	/* Acquire all required locks. */
again:
	devfs_byname_write();
	if (!fsuper_nodeslock_trywrite(&devfs.rs_sup)) {
		devfs_byname_endwrite();
		while (!fsuper_nodeslock_canwrite(&devfs.rs_sup))
			task_yield();
		goto again;
	}
	if (!fallnodes_tryacquire()) {
		fsuper_nodeslock_endwrite(&devfs.rs_sup);
		devfs_byname_endwrite();
		while (!fallnodes_available())
			task_yield();
		goto again;
	}

	/* With all required locks held, check if this device already exists. */
	{
		struct fdevfsnode *existing;
		existing = devfs_byname_locate(self->dfn_dirent->fdd_dirent.fd_name);
		if (existing != NULL) {
			if unlikely(wasdestroyed(&existing->dfn_devnode.dn_node.fn_file))
				goto unlock_yield_and_try_again; /* Wait for the destruction to complete. */
			result = DEVBUILDER_REGISTER_EXISTS_NAME;
			goto done;
		}
	}

	/* Also check in devfs's INode tree. */
	{
		struct fnode *existing;
		existing = fsuper_nodes_locate(&devfs.rs_sup, self->dfn_devnode.dn_node.fn_ino);
		if (existing != NULL) {
			if unlikely(wasdestroyed(&existing->fn_file))
				goto unlock_yield_and_try_again; /* Wait for the destruction to complete. */
			result = DEVBUILDER_REGISTER_EXISTS_DEVNO;
			goto done;
		}
	}

	/* Doesn't exist yet -> register our new one! */
	fsuper_nodes_insert(&devfs.rs_sup, &self->dfn_devnode.dn_node);
	devfs_byname_insert(self);
	LIST_INSERT_HEAD(&fallnodes_list, &self->dfn_devnode.dn_node, fn_allnodes);

	/* Indicate success */
	result = DEVBUILDER_REGISTER_SUCCESS;

done:
	/* Release all locks */
	fallnodes_release();
	fsuper_nodeslock_endwrite(&devfs.rs_sup);
	devfs_byname_endwrite();
	return result;

unlock_yield_and_try_again:
	fallnodes_release();
	fsuper_nodeslock_endwrite(&devfs.rs_sup);
	devfs_byname_endwrite();
	task_yield();
	goto again;
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_DEVFS_C */
