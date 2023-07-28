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
#ifndef GUARD_KERNEL_CORE_FILESYS_PATHDEFS_C
#define GUARD_KERNEL_CORE_FILESYS_PATHDEFS_C 1
#define __WANT_FS_INIT
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/notify-config.h> /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
#include <kernel/fs/path.h>
#include <kernel/fs/ramfs.h>
#include <kernel/fs/super.h>

#include <linux/magic.h>

#include <stddef.h>

DECL_BEGIN

INTDEF NONNULL((1)) void KCALL /* From "./null.c" */
nullfile_v_stat(struct mfile *__restrict UNUSED(self),
                NCX struct stat *result);

PRIVATE struct mfile_stream_ops const fsuper_unmounted_v_stream_ops = {
	.mso_open  = &ramfs_super_v_open,
	.mso_stat  = &nullfile_v_stat, /* stat() on unmounted root paths returns `boottime' timestamps! */
	.mso_ioctl = &fsuper_v_ioctl,
};


PRIVATE struct fsuper_ops const fsuper_unmounted_ops = {
	.so_fdir = {
		.dno_node = {
			.no_file = {
				.mo_destroy = &ramfs_super_v_destroy,
				.mo_changed = &ramfs_super_v_changed,
				.mo_stream  = &fsuper_unmounted_v_stream_ops,
			},
			.no_free   = &ramfs_super_v_free,
			.no_wrattr = &ramfs_super_v_wrattr,
		},
		.dno_lookup = &ramfs_super_v_lookup,
		.dno_enumsz = ramfs_super_v_enumsz,
		.dno_enum   = &ramfs_super_v_enum,
		.dno_mkfile = &ramfs_super_v_mkfile,
		.dno_unlink = &ramfs_super_v_unlink,
		.dno_rename = &ramfs_super_v_rename,
#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
		.dno_attach_notify = &ramfs_super_v_attach_notify,
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
	},
};


/* Special superblock (and directory) set for unmounted filesystem root paths.
 * Iow: this may  be set  in `struct path::p_dir'  for paths  that  are
 *      root dirs, as is the case when `struct path::p_parent == NULL'. */
PUBLIC struct ramfs_super fsuper_unmounted = {
	.rs_sup = {
		.fs_nodes         = FSUPER_NODES_DELETED,
		.fs_nodeslock     = ATOMIC_RWLOCK_INIT,
		.fs_nodeslockops  = SLIST_HEAD_INITIALIZER(fsuper_unmounted.rs_sup.fs_nodeslockops),
		.fs_mounts        = LIST_HEAD_INITIALIZER(fsuper_unmounted.rs_sup.fs_mounts), /* !!! DON'T MARK AS FSUPER_MOUNTS_DELETED !!! (needed for `umount("/")') */
		.fs_mountslock    = ATOMIC_RWLOCK_INIT,
		.fs_mountslockops = SLIST_HEAD_INITIALIZER(fsuper_unmounted.rs_sup.fs_mountslockops),
		.fs_sys           = &ramfs_filesys,
		.fs_dev           = NULL,
		.fs_loadblocks    = (typeoffield(struct fsuper, fs_loadblocks))(void *)-1,
		.fs_saveblocks    = (typeoffield(struct fsuper, fs_saveblocks))(void *)-1,
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
					MFILE_INIT_mf_ops(&fsuper_unmounted_ops.so_fdir.dno_node.no_file),
					MFILE_INIT_mf_lock,
					MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
					MFILE_INIT_mf_initdone,
					MFILE_INIT_mf_lockops,
					MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
					MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
					MFILE_INIT_mf_notify,
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
					MFILE_INIT_mf_flags(MFILE_FS_NOSUID | MFILE_FS_NOEXEC |
					                    MFILE_F_NOATIME | MFILE_FN_NODIRATIME |
					                    MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |
					                    MFILE_F_NOMTIME | MFILE_F_FIXEDFILESIZE |
					                    MFILE_FN_ATTRREADONLY | MFILE_F_DELETED |
					                    MFILE_F_CHANGED | MFILE_F_ATTRCHANGED |
					                    MFILE_F_READONLY | MFILE_F_ROFLAGS),
					MFILE_INIT_mf_trunclock,
					MFILE_INIT_mf_filesize((uint64_t)-1),
					/* TODO: Have an initializer that copies `boottime' into these 4! */
					MFILE_INIT_mf_atime(0, 0),
					MFILE_INIT_mf_mtime(0, 0),
					MFILE_INIT_mf_ctime(0, 0),
					MFILE_INIT_mf_btime(0, 0),
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
		},
	},
	.rs_dat = {
		.rdd_lock = SHARED_RWLOCK_INIT,
		.rdd_tree     = NULL,
	},
};


/* Opening  an empty directory just re-opens the
 * directory inside which it supposedly resides. */
PRIVATE WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
fdirent_empty_opennode(struct fdirent *__restrict UNUSED(self),
                       struct fdirnode *__restrict dir) {
	REF struct mfile *result;
	result = incref(_fnode_asfile(_fdirnode_asnode(dir)));
	return mfile_asnode(result);
}


PUBLIC_CONST struct fdirent_ops const fdirent_empty_ops = {
	.fdo_destroy  = (typeoffield(struct fdirent_ops, fdo_destroy))(void *)-1,
	.fdo_opennode = &fdirent_empty_opennode,
};

PUBLIC struct fdirent fdirent_empty = {
	.fd_refcnt  = 2, /* +1: fdirent_empty, +1: path_unmounted_root.p_name */
	.fd_ops     = &fdirent_empty_ops,
	.fd_ino     = (ino_t)0, /* == fsuper_unmounted.rs_sup.fs_root.dn_node.fn_ino */
	.fd_hash    = FDIRENT_EMPTY_HASH,
	.fd_namelen = 0,
	.fd_type    = DT_DIR, /* == IFTODT(fsuper_unmounted.rs_sup.fs_root.dn_node.fn_mode) */
	/* .fd_name = */ "",
};


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_PATHDEFS_C */
