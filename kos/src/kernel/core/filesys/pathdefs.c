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
#ifndef GUARD_KERNEL_CORE_FILESYS_PATHDEFS_C
#define GUARD_KERNEL_CORE_FILESYS_PATHDEFS_C 1
#define __WANT_FS_INIT
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/path.h>
#include <kernel/fs/ramfs.h>
#include <kernel/fs/super.h>

#include <linux/magic.h>

#include <stddef.h>

DECL_BEGIN

/* Special superblock (and directory) set for unmounted filesystem root paths.
 * Iow: this may  be set  in `struct path::p_dir'  for paths  that  are
 *      root dirs, as is the case when `struct path::p_parent == NULL'. */
PUBLIC struct ramfs_super fsuper_unmounted = {
	.rs_sup = {
		.fs_nodes         = FSUPER_NODES_DELETED,
		.fs_nodeslock     = ATOMIC_RWLOCK_INIT,
		.fs_nodeslockops  = SLIST_HEAD_INITIALIZER(fsuper_unmounted.rs_sup.fs_nodeslockops),
		.fs_mounts        = { FSUPER_MOUNTS_DELETED },
		.fs_mountslock    = ATOMIC_RWLOCK_INIT,
		.fs_mountslockops = SLIST_HEAD_INITIALIZER(fsuper_unmounted.rs_sup.fs_mountslockops),
		.fs_sys           = &ramfs_filesys,
		.fs_dev           = NULL,
		.fs_feat = {
			.sf_filesize_max       = (pos_t)-1,
			.sf_uid_max            = (uid_t)-1,
			.sf_gid_max            = (gid_t)-1,
			.sf_symlink_max        = (pos_t)-1,
			.sf_link_max           = (nlink_t)-1,
			.sf_magic              = RAMFS_MAGIC,
			.sf_rec_incr_xfer_size = PAGESIZE,
			.sf_rec_max_xfer_size  = PAGESIZE,
			.sf_rec_min_xfer_size  = PAGESIZE,
			.sf_rec_xfer_align     = PAGESIZE,
			.sf_name_max           = (u16)-1,
			.sf_filesizebits       = BITSOF(pos_t),
		},
		.fs_changednodes      = { FSUPER_NODES_DELETED },
		.fs_changednodes_lock = ATOMIC_LOCK_INIT,
		.fs_changednodes_lops = SLIST_HEAD_INITIALIZER(fsuper_unmounted.rs_sup.fs_changednodes_lops),
		.fs_changedsuper      = LIST_ENTRY_UNBOUND_INITIALIZER,
		.fs_root = {
			.dn_node = {
				.fn_file = {
					MFILE_INIT_mf_refcnt(2), /* +1: fsuper_unmounted, +1: path_unmounted_root.p_dir */
					MFILE_INIT_mf_ops(&ramfs_super_ops.so_fdir.dno_node.no_file),
					MFILE_INIT_mf_lock,
					MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
					MFILE_INIT_mf_initdone,
					MFILE_INIT_mf_lockops,
					MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
					MFILE_INIT_mf_blockshift(PAGESHIFT),
					MFILE_INIT_mf_flags(MFILE_FS_NOSUID | MFILE_FS_NOEXEC | MFILE_F_NOATIME |
					                    MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_NOMTIME |
					                    MFILE_F_FIXEDFILESIZE | MFILE_FM_ATTRREADONLY | MFILE_F_DELETED |
					                    MFILE_F_CHANGED | MFILE_F_ATTRCHANGED | MFILE_F_READONLY),
					MFILE_INIT_mf_trunclock,
					MFILE_INIT_mf_filesize((uint64_t)-1),
					/* TODO: Have an initializer that copies `boottime' into these 3! */
					MFILE_INIT_mf_atime(0, 0),
					MFILE_INIT_mf_mtime(0, 0),
					MFILE_INIT_mf_ctime(0, 0),
				},
				FNODE_INIT_fn_nlink(1),
				FNODE_INIT_fn_mode(S_IFDIR | 0755),
				FNODE_INIT_fn_uid(0), /* root */
				FNODE_INIT_fn_gid(0), /* root */
				FNODE_INIT_fn_ino(0), /* Fixed INO for root directory */
				FNODE_INIT_fn_super(&fsuper_unmounted.rs_sup),
				FNODE_INIT_fn_changed,
				.fn_supent = { FSUPER_NODES_DELETED, NULL },
				FNODE_INIT_fn_allsuper_EX(LIST_ENTRY_UNBOUND_INITIALIZER),
			},
			.dn_parent = NULL,
		},
	},
	.rs_dat = {
		.rdd_treelock = SHARED_RWLOCK_INIT,
		.rdd_tree     = RAMFS_DIRDATA_TREE_DELETED,
	},
};


/* Opening an empty directory just re-opens the
 * directory inside which it supposedly resides. */
PRIVATE WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
fdirent_empty_opennode(struct fdirent *__restrict UNUSED(self),
                       struct fdirnode *__restrict dir) {
	REF struct mfile *result;
	result = incref(_fnode_asfile(_fdirnode_asnode(dir)));
	return mfile_asnode(result);
}


PRIVATE struct fdirent_ops const fdirent_empty_ops = {
	.fdo_destroy  = (void(KCALL *)(struct fdirent *__restrict))(void *)(uintptr_t)-1,
	.fdo_opennode = &fdirent_empty_opennode,
};

PUBLIC struct fdirent fdirent_empty = {
	.fd_refcnt  = 2, /* +1: fdirent_empty, +1: path_unmounted_root.p_name */
	.fd_ops     = &fdirent_empty_ops,
	.fd_ino     = (ino_t)0, /* == fsuper_unmounted.rs_sup.fs_root.dn_node.fn_ino */
	.fd_hash    = FDIRENT_EMPTY_HASH,
	.fd_namelen = 0,
	.fd_type    = DT_DIR, /* == IFTODT(fsuper_unmounted.rs_sup.fs_root.dn_node.fn_mode) */
	.fd_name    = "",
};

/* Special path pointed-to by newly-allocated VFS */
PUBLIC struct path path_unmounted_root = {
	.p_refcnt  = 1, /* +1: path_unmounted_root */
	.p_flags   = PATH_F_NORMAL,
	.p_parent  = NULL,
	.p_name    = &fdirent_empty,
	.p_dir     = &fsuper_unmounted.rs_sup.fs_root,
	.p_recent  = TAILQ_ENTRY_UNBOUND_INITIALIZER,
	.p_cldlock = SHARED_RWLOCK_INIT,
	.p_cldlops = SLIST_HEAD_INITIALIZER(path_unmounted_root.p_cldlops),
	.p_cldused = 0,
	.p_cldsize = 0,
	.p_cldmask = 0,
	.p_cldlist = PATH_CLDLIST_DELETED,
};


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_PATHDEFS_C */
