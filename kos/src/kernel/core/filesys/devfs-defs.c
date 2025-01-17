/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_FILESYS_DEVFS_DEFS_C
#define GUARD_KERNEL_CORE_FILESYS_DEVFS_DEFS_C 1
#define __WANT_FS_INIT
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <kernel/driver.h>
#include <kernel/fs/allnodes.h>
#include <kernel/fs/devfs-disk.h>
#include <kernel/fs/devfs-spec.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/notify-config.h> /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
#include <kernel/fs/ramfs.h>

#include <linux/magic.h>

#include <stddef.h>

DECL_BEGIN

/* Operator tables for special /dev directories. */
INTDEF struct fdirnode_ops const devfs_block_ops;
INTDEF struct fdirnode_ops const devfs_char_ops;
INTDEF struct fdirnode_ops const devfs_cpu_ops;
INTDEF struct fdirnode_ops const devfs_disk_ops;

#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
#define MFILE_INIT_mf_notify_ MFILE_INIT_mf_meta,
#else /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
#define MFILE_INIT_mf_notify_ /* nothing */
#endif /* !CONFIG_HAVE_KERNEL_FS_NOTIFY */

#define INIT_SPECIAL_DEVFS_SUBDIR(ops, ino)                                         \
	{                                                                               \
		.dn_node = {                                                                \
			.fn_file = {                                                            \
				MFILE_INIT_mf_refcnt(2), /* +1: devfs_*, +1: MFILE_FN_GLOBAL_REF */ \
				MFILE_INIT_mf_ops(&ops.dno_node.no_file),                           \
				MFILE_INIT_mf_lock,                                                 \
				MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),                         \
				MFILE_INIT_mf_initdone,                                             \
				MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),                       \
				MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),                     \
				MFILE_INIT_mf_notify_                                               \
				MFILE_INIT_mf_flags(MFILE_FN_GLOBAL_REF | MFILE_F_NOUSRMMAP |       \
				                    MFILE_F_NOUSRIO | MFILE_F_PERSISTENT |          \
				                    MFILE_F_FIXEDFILESIZE | MFILE_FN_ATTRREADONLY), \
				MFILE_INIT_mf_trunclock,                                            \
				MFILE_INIT_mf_filesize((uint64_t)-1),                               \
				MFILE_INIT_mf_atime(0, 0),                                          \
				MFILE_INIT_mf_mtime(0, 0),                                          \
				MFILE_INIT_mf_ctime(0, 0),                                          \
				MFILE_INIT_mf_btime(0, 0),                                          \
				MFILE_INIT_mf_msalign(NULL),                                        \
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


/* Default rules for /dev/disk */
INTDEF struct fdirnode_ops const _devdiskruledir_default_ops;
#define DEFINE_DISKRULE(devdiskrule_name, name, ino, symbol_byname, symbol_toname, hash) \
	INTDEF WUNUSED NONNULL((1, 2)) REF struct blkdev *KCALL                              \
	symbol_byname(struct devdiskruledir *__restrict self,                                \
	              struct flookup_info *__restrict info);                                 \
	INTDEF WUNUSED NONNULL((1, 2, 4)) ssize_t KCALL                                      \
	symbol_toname(struct devdiskruledir *__restrict self,                                \
	              __pformatprinter printer, void *arg,                                   \
	              struct blkdev *__restrict dev,                                         \
	              uintptr_t variant);                                                    \
	PRIVATE struct devdiskruledir _dir_##devdiskrule_name = {                            \
		.ddrd_dir = {                                                                    \
			.dn_node = {                                                                 \
				.fn_file = {                                                             \
					MFILE_INIT_mf_refcnt(1),                                             \
					MFILE_INIT_mf_ops(&_devdiskruledir_default_ops.dno_node.no_file),    \
					MFILE_INIT_mf_lock,                                                  \
					MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),                          \
					MFILE_INIT_mf_initdone,                                              \
					MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),                        \
					MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),                      \
					MFILE_INIT_mf_notify_                                                \
					MFILE_INIT_mf_flags(MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |            \
					                    MFILE_F_NOATIME | MFILE_F_NOMTIME |              \
					                    MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE),       \
					MFILE_INIT_mf_trunclock,                                             \
					MFILE_INIT_mf_filesize((uint64_t)-1),                                \
					MFILE_INIT_mf_atime(0, 0),                                           \
					MFILE_INIT_mf_mtime(0, 0),                                           \
					MFILE_INIT_mf_ctime(0, 0),                                           \
					MFILE_INIT_mf_btime(0, 0),                                           \
					MFILE_INIT_mf_msalign(NULL),                                         \
				},                                                                       \
				FNODE_INIT_fn_nlink(1),                                                  \
				FNODE_INIT_fn_mode(S_IFDIR | 0555),                                      \
				FNODE_INIT_fn_uid(0), /* root */                                         \
				FNODE_INIT_fn_gid(0), /* root */                                         \
				FNODE_INIT_fn_ino(ino),                                                  \
				FNODE_INIT_fn_super(&devfs.rs_sup),                                      \
				FNODE_INIT_fn_changed,                                                   \
				FNODE_INIT_fn_supent,                                                    \
				FNODE_INIT_fn_allnodes,                                                  \
			},                                                                           \
		},                                                                               \
		._ddrd_prefix = "../../\0",                                                      \
		.ddrd_byname  = &symbol_byname,                                                  \
		.ddrd_toname  = &symbol_toname,                                                  \
		.ddrd_drv     = &drv_self,                                                       \
	};                                                                                   \
	INTERN struct devdiskrule devdiskrule_name = {                                       \
		.ddre_rule  = &_dir_##devdiskrule_name,                                          \
		{ ._ddre_lop = { NULL, NULL } },                                                 \
		.fd_refcnt  = 2,                                                                 \
		.fd_ops     = &devdiskrule_ops,                                                  \
		.fd_ino     = ino,                                                               \
		.fd_hash    = hash,                                                              \
		.fd_namelen = COMPILER_STRLEN(name),                                             \
		.fd_type    = DT_DIR,                                                            \
		/* .fd_name = */ name                                                            \
	}

/* clang-format off */
DEFINE_DISKRULE(_devdisk_defrule_byid,        "by-id",        DEVFS_INO_MISC(0), devdisk_id_byname,        devdisk_id_toname,        /*[[[fdirent_hash]]]*/FDIRENT_HASH_INIT(0xb29944d6, 0x64692d7962, 0x76429915, 0x64692d7962)/*[[[end]]]*/);
DEFINE_DISKRULE(_devdisk_defrule_bylabel,     "by-label",     DEVFS_INO_MISC(1), devdisk_label_byname,     devdisk_label_toname,     /*[[[fdirent_hash]]]*/FDIRENT_HASH_INIT(0x9f3dd6b, 0xcf90756ccd994472, 0x94cceff8, 0x764298cf6c7590cc)/*[[[end]]]*/);
DEFINE_DISKRULE(_devdisk_defrule_bypartlabel, "by-partlabel", DEVFS_INO_MISC(2), devdisk_partlabel_byname, devdisk_partlabel_toname, /*[[[fdirent_hash]]]*/FDIRENT_HASH_INIT(0x91e74e2c, 0xd018056d5dfea6d3, 0xacbecae8, 0x764298f3d96b7a2d)/*[[[end]]]*/);
DEFINE_DISKRULE(_devdisk_defrule_bypartuuid,  "by-partuuid",  DEVFS_INO_MISC(3), devdisk_partuuid_byname,  devdisk_partuuid_toname,  /*[[[fdirent_hash]]]*/FDIRENT_HASH_INIT(0x9fdfd6e0, 0x2118056cf1fdade7, 0x95c1e202, 0x764298f36d6a8192)/*[[[end]]]*/);
DEFINE_DISKRULE(_devdisk_defrule_bypath,      "by-path",      DEVFS_INO_MISC(4), devdisk_path_byname,      devdisk_path_toname,      /*[[[fdirent_hash]]]*/FDIRENT_HASH_INIT(0xf201b8d3, 0x687461702d7962, 0x76ab0d51, 0x687461702d7962)/*[[[end]]]*/);
DEFINE_DISKRULE(_devdisk_defrule_byuuid,      "by-uuid",      DEVFS_INO_MISC(5), devdisk_uuid_byname,      devdisk_uuid_toname,      /*[[[fdirent_hash]]]*/FDIRENT_HASH_INIT(0x1efdade7, 0x646975752d7962, 0x76a70292, 0x646975752d7962)/*[[[end]]]*/);
/* clang-format on */

#undef DEFINE_DISKRULE





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
			MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
			MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
			MFILE_INIT_mf_notify_
			MFILE_INIT_mf_flags(MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |
			                    MFILE_F_FIXEDFILESIZE | MFILE_FN_ATTRREADONLY),
			MFILE_INIT_mf_trunclock,
			MFILE_INIT_mf_filesize((uint64_t)-1),
			MFILE_INIT_mf_atime(0, 0),
			MFILE_INIT_mf_mtime(0, 0),
			MFILE_INIT_mf_ctime(0, 0),
			MFILE_INIT_mf_btime(0, 0),
			MFILE_INIT_mf_msalign(NULL),
		},
		FNODE_INIT_fn_nlink(1),
		FNODE_INIT_fn_mode(S_IFLNK | 0444),
		FNODE_INIT_fn_uid(0), /* root */
		FNODE_INIT_fn_gid(0), /* root */
		FNODE_INIT_fn_ino(0),
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
		.fs_loadblocks    = (typeof_field(struct fsuper, fs_loadblocks))(void *)-1,
		.fs_saveblocks    = (typeof_field(struct fsuper, fs_saveblocks))(void *)-1,
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
					MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
					MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
					MFILE_INIT_mf_notify_
					MFILE_INIT_mf_flags(MFILE_FS_NOSUID | MFILE_FS_NOEXEC |
					                    MFILE_FN_GLOBAL_REF | MFILE_F_NOUSRMMAP |
					                    MFILE_F_NOUSRIO | MFILE_F_PERSISTENT |
					                    MFILE_F_FIXEDFILESIZE | MFILE_FN_ATTRREADONLY),
					MFILE_INIT_mf_trunclock,
					MFILE_INIT_mf_filesize((uint64_t)-1),
					MFILE_INIT_mf_atime(0, 0),
					MFILE_INIT_mf_mtime(0, 0),
					MFILE_INIT_mf_ctime(0, 0),
					MFILE_INIT_mf_btime(0, 0),
					MFILE_INIT_mf_msalign(NULL),
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
		.rdd_lock = SHARED_RWLOCK_INIT,
		.rdd_lops = SLIST_HEAD_INITIALIZER(devfs.rs_dat.rdd_lops),
		.rdd_tree = NULL,
	},
};


/* Lock accessor helpers for `devfs_byname_lock' and `devfs_byname_tree' */
PUBLIC NOBLOCK void NOTHROW(KCALL _devfs_byname_reap)(void) {
#ifndef __INTELLISENSE__
#define __LOCAL_self      (&devfs_byname_lops)
#define __LOCAL_trylock() devfs_byname_trywrite()
#define __LOCAL_unlock()  _devfs_byname_endwrite()
#include <libc/template/lockop.h>
#endif /* !__INTELLISENSE__ */
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_DEVFS_DEFS_C */
