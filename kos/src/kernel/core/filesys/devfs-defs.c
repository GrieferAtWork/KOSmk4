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
#ifndef GUARD_KERNEL_CORE_FILESYS_DEVFS_DEFS_C
#define GUARD_KERNEL_CORE_FILESYS_DEVFS_DEFS_C 1
#define __WANT_FS_INIT

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <kernel/fs/allnodes.h>
#include <kernel/fs/devfs-spec.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/ramfs.h>

#include <linux/magic.h>

#include <stddef.h>

DECL_BEGIN

/* Operator tables for special /dev directories. */
INTDEF struct fdirnode_ops const devfs_block_ops;
INTDEF struct fdirnode_ops const devfs_char_ops;
INTDEF struct fdirnode_ops const devfs_cpu_ops;
INTDEF struct fdirnode_ops const devfs_disk_ops;

#define INIT_SPECIAL_DEVFS_SUBDIR(ops, ino)                                         \
	{                                                                               \
		.dn_node = {                                                                \
			.fn_file = {                                                            \
				MFILE_INIT_mf_refcnt(2), /* +1: devfs_*, +1: MFILE_FN_GLOBAL_REF */ \
				MFILE_INIT_mf_ops(&ops.dno_node.no_file),                           \
				MFILE_INIT_mf_lock,                                                 \
				MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),                         \
				MFILE_INIT_mf_initdone,                                             \
				MFILE_INIT_mf_lockops,                                              \
				MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),                       \
				MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),                     \
				MFILE_INIT_mf_flags(MFILE_FN_GLOBAL_REF | MFILE_F_NOUSRMMAP |       \
				                    MFILE_F_NOUSRIO | MFILE_F_PERSISTENT |          \
				                    MFILE_F_FIXEDFILESIZE | MFILE_FN_ATTRREADONLY), \
				MFILE_INIT_mf_trunclock,                                            \
				MFILE_INIT_mf_filesize((uint64_t)-1),                               \
				MFILE_INIT_mf_atime(0, 0),                                          \
				MFILE_INIT_mf_mtime(0, 0),                                          \
				MFILE_INIT_mf_ctime(0, 0),                                          \
			},                                                                      \
			FNODE_INIT_fn_nlink(1),                                                 \
			FNODE_INIT_fn_mode(S_IFDIR | 0555),                                     \
			FNODE_INIT_fn_uid(0), /* root */                                        \
			FNODE_INIT_fn_gid(0), /* root */                                        \
			FNODE_INIT_fn_ino(ino),                                                 \
			FNODE_INIT_fn_super(&devfs.rs_sup),                                     \
			FNODE_INIT_fn_changed,                                                  \
			FNODE_INIT_fn_supent,                                                   \
			FNODE_INIT_fn_allnodes,                                                 \
		},                                                                          \
	}

/* Special sub-directories of /dev/ */
INTERN struct fdirnode devfs_block = INIT_SPECIAL_DEVFS_SUBDIR(devfs_block_ops, DEVFS_INO_BLOCK);
INTERN struct fdirnode devfs_char  = INIT_SPECIAL_DEVFS_SUBDIR(devfs_char_ops, DEVFS_INO_CHAR);
INTERN struct fdirnode devfs_cpu   = INIT_SPECIAL_DEVFS_SUBDIR(devfs_cpu_ops, DEVFS_INO_CPU);
INTERN struct fdirnode devfs_disk  = INIT_SPECIAL_DEVFS_SUBDIR(devfs_disk_ops, DEVFS_INO_DISK);
#undef INIT_SPECIAL_DEVFS_SUBDIR

/* Template for symbolic device links, as found in /dev/block/, /dev/char/ and /dev/disk/by-xxx/ */
INTDEF struct flnknode_ops const devicelink_ops;
INTERN_CONST struct flnknode const devicelink_template = {
	.ln_node = {
		.fn_file = {
			MFILE_INIT_mf_refcnt(1),
			MFILE_INIT_mf_ops(&devicelink_ops.lno_node.no_file),
			MFILE_INIT_mf_lock,
			MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
			MFILE_INIT_mf_initdone,
			MFILE_INIT_mf_lockops,
			MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
			MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
			MFILE_INIT_mf_flags(MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |
			                    MFILE_F_FIXEDFILESIZE | MFILE_FN_ATTRREADONLY),
			MFILE_INIT_mf_trunclock,
			MFILE_INIT_mf_filesize((uint64_t)-1),
			MFILE_INIT_mf_atime(0, 0),
			MFILE_INIT_mf_mtime(0, 0),
			MFILE_INIT_mf_ctime(0, 0),
		},
		FNODE_INIT_fn_nlink(1),
		FNODE_INIT_fn_mode(S_IFLNK | 0444),
		FNODE_INIT_fn_uid(0), /* root */
		FNODE_INIT_fn_gid(0), /* root */
		FNODE_INIT_fn_ino(DEVFS_INO_ROOT),
		FNODE_INIT_fn_super(&devfs.rs_sup),
		FNODE_INIT_fn_changed,
		FNODE_INIT_fn_supent,
		FNODE_INIT_fn_allnodes,
	},
};




/* Operators for the /dev root directory and superblock. */
INTDEF struct fsuper_ops const devfs_super_ops;

/* The /dev/ filesystem superblock */
extern struct fnode _devfs__fs_nodes__INIT[];
PUBLIC struct ramfs_super devfs = {
	.rs_sup = {
		.fs_nodes         = _devfs__fs_nodes__INIT,
		.fs_nodeslock     = ATOMIC_RWLOCK_INIT,
		.fs_nodeslockops  = SLIST_HEAD_INITIALIZER(devfs.rs_sup.fs_nodeslockops),
		.fs_mounts        = LIST_HEAD_INITIALIZER(devfs.rs_sup.fs_mounts),
		.fs_mountslock    = ATOMIC_RWLOCK_INIT,
		.fs_mountslockops = SLIST_HEAD_INITIALIZER(devfs.rs_sup.fs_mountslockops),
		.fs_sys           = &devfs_filesys,
		.fs_dev           = NULL,
		.fs_loadblocks    = (void (KCALL *)(struct mfile *__restrict, pos_t, physaddr_t, size_t, struct aio_multihandle *__restrict))(void *)(uintptr_t)-1,
		.fs_saveblocks    = (void (KCALL *)(struct mfile *__restrict, pos_t, physaddr_t, size_t, struct aio_multihandle *__restrict))(void *)(uintptr_t)-1,
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
		.fs_changednodes      = LIST_HEAD_INITIALIZER(devfs.rs_sup.fs_changednodes),
		.fs_changednodes_lock = ATOMIC_LOCK_INIT,
		.fs_changednodes_lops = SLIST_HEAD_INITIALIZER(devfs.rs_sup.fs_changednodes_lops),
		.fs_changedsuper      = LIST_ENTRY_UNBOUND_INITIALIZER,
		.fs_root = {
			.dn_node = {
				.fn_file = {
					MFILE_INIT_mf_refcnt(2), /* +1: devfs, +1: MFILE_FN_GLOBAL_REF */
					MFILE_INIT_mf_ops(&devfs_super_ops.so_fdir.dno_node.no_file),
					MFILE_INIT_mf_lock,
					MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
					MFILE_INIT_mf_initdone,
					MFILE_INIT_mf_lockops,
					MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
					MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
					MFILE_INIT_mf_flags(MFILE_FS_NOSUID | MFILE_FS_NOEXEC |
					                    MFILE_FN_GLOBAL_REF | MFILE_F_NOUSRMMAP |
					                    MFILE_F_NOUSRIO | MFILE_F_PERSISTENT |
					                    MFILE_F_FIXEDFILESIZE | MFILE_FN_ATTRREADONLY),
					MFILE_INIT_mf_trunclock,
					MFILE_INIT_mf_filesize((uint64_t)-1),
					MFILE_INIT_mf_atime(0, 0),
					MFILE_INIT_mf_mtime(0, 0),
					MFILE_INIT_mf_ctime(0, 0),
				},
				FNODE_INIT_fn_nlink(1),
				FNODE_INIT_fn_mode(S_IFDIR | 0755),
				FNODE_INIT_fn_uid(0), /* root */
				FNODE_INIT_fn_gid(0), /* root */
				FNODE_INIT_fn_ino(DEVFS_INO_ROOT),
				FNODE_INIT_fn_super(&devfs.rs_sup),
				FNODE_INIT_fn_changed,
				FNODE_INIT_fn_supent,
				FNODE_INIT_fn_allsuper_EX({ NULL, &fallsuper_list.lh_first }),
			},
		},
	},
	.rs_dat = {
		.rdd_treelock = SHARED_RWLOCK_INIT,
		.rdd_tree     = NULL,
	},
};


/* Lock accessor helpers for `devfs_byname_lock' and `devfs_byname_tree' */
PUBLIC NOBLOCK void NOTHROW(KCALL _devfs_byname_reap)(void) {
	DEFINE_PUBLIC_SYMBOL(devfs_rootdir, &devfs.rs_sup.fs_root, sizeof(struct ramfs_dirnode));
#ifndef __INTELLISENSE__
#define __LOCAL_self      (&devfs_byname_lops)
#define __LOCAL_trylock() devfs_byname_trywrite()
#define __LOCAL_unlock()  _devfs_byname_endwrite()
#include <libc/template/lockop.h>
#endif /* !__INTELLISENSE__ */
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_DEVFS_DEFS_C */