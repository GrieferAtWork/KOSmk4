/*[[[magic
options["COMPILE.language"] = "c";
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.remove("-g"); // Disable debug informations for this file!
gcc_opt.remove("-fno-rtti");
]]]*/
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODPROCFS_PROCFSDEFS_C
#define GUARD_MODPROCFS_PROCFSDEFS_C 1
#define __WANT_FS_INIT
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver-callbacks.h>
#include <kernel/fs/constdir.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/filesys.h>
#include <kernel/fs/lnknode.h>
#include <kernel/fs/node.h>
#include <kernel/fs/printnode.h>
#include <kernel/fs/super.h>
#include <kernel/malloc.h>
#include <kernel/mman/driver.h>
#include <kernel/uname.h>

#include <linux/magic.h>

#include <stddef.h>

/**/
#include "procfs.h"

#ifdef CONFIG_HAVE_FS_NOTIFY
#define MFILE_INIT_mf_notify_ MFILE_INIT_mf_notify,
#else /* CONFIG_HAVE_FS_NOTIFY */
#define MFILE_INIT_mf_notify_ /* nothing */
#endif /* !CONFIG_HAVE_FS_NOTIFY */


/************************************************************************/
/* Statically initialized data structures                               */
/************************************************************************/

DECL_BEGIN

#ifdef CONFIG_TRACE_MALLOC
INTDEF struct fregnode_ops const procfs_r_kos_leaks_ops;
INTERN struct fregnode procfs_r_kos_leaks = {{
	.fn_file = {
		MFILE_INIT_mf_refcnt(2), /* +1: symbol_name, +1: <my dirent> */
		MFILE_INIT_mf_ops(&procfs_r_kos_leaks_ops.rno_node.no_file),
		MFILE_INIT_mf_lock,
		MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
		MFILE_INIT_mf_initdone,
		MFILE_INIT_mf_lockops,
		MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
		MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
#ifdef CONFIG_HAVE_FS_NOTIFY
		MFILE_INIT_mf_notify,
#endif /* CONFIG_HAVE_FS_NOTIFY */
		MFILE_INIT_mf_flags(MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE |
		                    MFILE_F_ATTRCHANGED | MFILE_F_CHANGED |
		                    MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO),
		MFILE_INIT_mf_trunclock,
		MFILE_INIT_mf_filesize(0),
		MFILE_INIT_mf_atime(0, 0),
		MFILE_INIT_mf_mtime(0, 0),
		MFILE_INIT_mf_ctime(0, 0),
		MFILE_INIT_mf_btime(0, 0),
	},
	FNODE_INIT_fn_nlink(1),
	FNODE_INIT_fn_mode(S_IFREG | 0400),
	FNODE_INIT_fn_uid(0), /* root */
	FNODE_INIT_fn_gid(0), /* root */
	FNODE_INIT_fn_ino(0),
	FNODE_INIT_fn_super(&procfs_super),
	FNODE_INIT_fn_changed,
	.fn_supent = { NULL, FSUPER_NODES_DELETED },
	FNODE_INIT_fn_allnodes,
}};
#endif /* CONFIG_TRACE_MALLOC */

/* Create forward declarations. */
#define ROOTENT(name, type, nodeptr, hash) \
	INTDEF struct constdirent PP_CAT2(procfs_root_dirent_, __LINE__);
#define MKDIR_BEGIN(symbol_name, perm) \
	INTDEF struct constdir symbol_name;
#define MKREG_RO(symbol_name, perm, printer)                                         \
	INTDEF void KCALL printer(pformatprinter printer, void *arg, pos_t offset_hint); \
	INTDEF struct procfs_regfile symbol_name;
#define MKREG_RW(symbol_name, perm, printer, writer)                                 \
	INTDEF void KCALL printer(pformatprinter printer, void *arg, pos_t offset_hint); \
	INTDEF void KCALL writer(USER CHECKED void const *buf, size_t bufsize);          \
	INTDEF struct procfs_regfile symbol_name;
#define MKREG_CONSTSTR(symbol_name, perm, string_ptr) \
	INTDEF struct procfs_txtfile symbol_name;
#define MKLNK(symbol_name, perm, readlink)            \
	INTDEF WUNUSED NONNULL((1)) size_t KCALL          \
	readlink(struct flnknode *__restrict self,        \
	         USER CHECKED /*utf-8*/ char *buf,        \
	         size_t bufsize) THROWS(E_SEGFAULT, ...); \
	INTDEF struct flnknode symbol_name;
#include "procfs.def"

/* Construct directory entries and files. */
#define ROOTENT(name, type, nodeptr, hash)                             \
	INTERN struct constdirent PP_CAT2(procfs_root_dirent_, __LINE__) = \
	CONSTDIRENT_INIT((struct fnode *)(nodeptr), 0, type, name, hash);
#define MKDIR_ENT(name, type, nodeptr, hash)                       \
	PRIVATE struct constdirent PP_CAT2(procfs_dirent_, __LINE__) = \
	CONSTDIRENT_INIT((struct fnode *)(nodeptr), 0, type, name, hash);
#define __MKREG_IMPL(symbol_name, perm, printer, writer)                         \
	INTERN struct procfs_regfile symbol_name = {                                 \
		.prf_node = {{{                                                          \
			.fn_file = {                                                         \
				MFILE_INIT_mf_refcnt(2), /* +1: symbol_name, +1: <my dirent> */  \
				MFILE_INIT_mf_ops(&procfs_regfile_ops.pno_reg.rno_node.no_file), \
				MFILE_INIT_mf_lock,                                              \
				MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),                      \
				MFILE_INIT_mf_initdone,                                          \
				MFILE_INIT_mf_lockops,                                           \
				MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),                    \
				MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),                  \
				MFILE_INIT_mf_notify_                                            \
				MFILE_INIT_mf_flags(MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE),   \
				MFILE_INIT_mf_trunclock,                                         \
				MFILE_INIT_mf_filesize((uint64_t)-1),                            \
				MFILE_INIT_mf_atime(0, 0),                                       \
				MFILE_INIT_mf_mtime(0, 0),                                       \
				MFILE_INIT_mf_ctime(0, 0),                                       \
				MFILE_INIT_mf_btime(0, 0),                                       \
			},                                                                   \
			FNODE_INIT_fn_nlink(1),                                              \
			FNODE_INIT_fn_mode(S_IFREG | (perm)),                                \
			FNODE_INIT_fn_uid(0), /* root */                                     \
			FNODE_INIT_fn_gid(0), /* root */                                     \
			FNODE_INIT_fn_ino(0),                                                \
			FNODE_INIT_fn_super(&procfs_super),                                  \
			FNODE_INIT_fn_changed,                                               \
			.fn_supent = { NULL, FSUPER_NODES_DELETED },                         \
			FNODE_INIT_fn_allnodes,                                              \
		}}},                                                                     \
		.prf_print = printer,                                                    \
		.prf_write = writer,                                                     \
	};
#define MKREG_RW(symbol_name, perm, printer, writer) __MKREG_IMPL(symbol_name, perm, &printer, &writer)
#define MKREG_RO(symbol_name, perm, printer)         __MKREG_IMPL(symbol_name, perm, &printer, NULL)
#define MKREG_CONSTSTR(symbol_name, perm, string_ptr)                            \
	INTERN struct procfs_txtfile symbol_name = {                                 \
		.ptf_node  = {{{                                                         \
			.fn_file = {                                                         \
				MFILE_INIT_mf_refcnt(2), /* +1: symbol_name, +1: <my dirent> */  \
				MFILE_INIT_mf_ops(&procfs_txtfile_ops.pno_reg.rno_node.no_file), \
				MFILE_INIT_mf_lock,                                              \
				MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),                      \
				MFILE_INIT_mf_initdone,                                          \
				MFILE_INIT_mf_lockops,                                           \
				MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),                    \
				MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),                  \
				MFILE_INIT_mf_notify_                                            \
				MFILE_INIT_mf_flags(MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE),   \
				MFILE_INIT_mf_trunclock,                                         \
				MFILE_INIT_mf_filesize((uint64_t)-1),                            \
				MFILE_INIT_mf_atime(0, 0),                                       \
				MFILE_INIT_mf_mtime(0, 0),                                       \
				MFILE_INIT_mf_ctime(0, 0),                                       \
				MFILE_INIT_mf_btime(0, 0),                                       \
			},                                                                   \
			FNODE_INIT_fn_nlink(1),                                              \
			FNODE_INIT_fn_mode(S_IFREG | (perm)),                                \
			FNODE_INIT_fn_uid(0), /* root */                                     \
			FNODE_INIT_fn_gid(0), /* root */                                     \
			FNODE_INIT_fn_ino(0),                                                \
			FNODE_INIT_fn_super(&procfs_super),                                  \
			FNODE_INIT_fn_changed,                                               \
			.fn_supent = { NULL, FSUPER_NODES_DELETED },                         \
			FNODE_INIT_fn_allnodes,                                              \
		}}},                                                                     \
		.ptf_string = string_ptr,                                                \
	};
#define MKLNK(symbol_name, perm, readlink)                                           \
	PRIVATE struct flnknode_ops const __##symbol_name##_ops = {                      \
		.lno_node = {                                                                \
			.no_file = {                                                             \
				.mo_destroy = (typeoffield(struct mfile_ops, mo_destroy))(void *)-1, \
				.mo_changed = &fnode_v_changed,                                      \
			},                                                                       \
			.no_free   = (typeoffield(struct fnode_ops, no_free))(void *)-1,         \
			.no_wrattr = &fnode_v_wrattr_noop,                                       \
		},                                                                           \
		.lno_readlink = &readlink,                                                   \
	};                                                                               \
	INTERN struct flnknode symbol_name = {{                                          \
		.fn_file = {                                                                 \
			MFILE_INIT_mf_refcnt(2), /* +1: symbol_name, +1: <my dirent> */          \
			MFILE_INIT_mf_ops(&__##symbol_name##_ops.lno_node.no_file),              \
			MFILE_INIT_mf_lock,                                                      \
			MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),                              \
			MFILE_INIT_mf_initdone,                                                  \
			MFILE_INIT_mf_lockops,                                                   \
			MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),                            \
			MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),                          \
			MFILE_INIT_mf_notify_                                                    \
			MFILE_INIT_mf_flags(MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |                \
			                    MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE),           \
			MFILE_INIT_mf_trunclock,                                                 \
			MFILE_INIT_mf_filesize(0),                                               \
			MFILE_INIT_mf_atime(0, 0),                                               \
			MFILE_INIT_mf_mtime(0, 0),                                               \
			MFILE_INIT_mf_ctime(0, 0),                                               \
			MFILE_INIT_mf_btime(0, 0),                                               \
		},                                                                           \
		FNODE_INIT_fn_nlink(1),                                                      \
		FNODE_INIT_fn_mode(S_IFLNK | (perm)),                                        \
		FNODE_INIT_fn_uid(0), /* root */                                             \
		FNODE_INIT_fn_gid(0), /* root */                                             \
		FNODE_INIT_fn_ino(0),                                                        \
		FNODE_INIT_fn_super(&procfs_super),                                          \
		FNODE_INIT_fn_changed,                                                       \
		.fn_supent = { NULL, FSUPER_NODES_DELETED },                                 \
		FNODE_INIT_fn_allnodes,                                                      \
	}};
#include "procfs.def"


/* Calculate directory sizes (in # of entries). */
#define MKDIR_BEGIN(symbol_name, perm) \
	enum { __##symbol_name##_lenof_dir = 0
#define MKDIR_ENT(name, type, nodeptr, hash) + 1
#define MKDIR_END };
#include "procfs.def"

/* Construct directories. */
#define MKDIR_BEGIN(symbol_name, perm)                                          \
	INTERN struct constdir symbol_name = {                                      \
		.cd_dir  = {{                                                           \
			.fn_file = {                                                        \
				MFILE_INIT_mf_refcnt(2), /* +1: symbol_name, +1: <my dirent> */ \
				MFILE_INIT_mf_ops(&constdir_ops.dno_node.no_file),              \
				MFILE_INIT_mf_lock,                                             \
				MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),                     \
				MFILE_INIT_mf_initdone,                                         \
				MFILE_INIT_mf_lockops,                                          \
				MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),                   \
				MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),                 \
				MFILE_INIT_mf_notify_                                           \
				MFILE_INIT_mf_flags(MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |       \
				                    MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE),  \
				MFILE_INIT_mf_trunclock,                                        \
				MFILE_INIT_mf_filesize((uint64_t)-1),                           \
				MFILE_INIT_mf_atime(0, 0),                                      \
				MFILE_INIT_mf_mtime(0, 0),                                      \
				MFILE_INIT_mf_ctime(0, 0),                                      \
				MFILE_INIT_mf_btime(0, 0),                                      \
			},                                                                  \
			FNODE_INIT_fn_nlink(1),                                             \
			FNODE_INIT_fn_mode(S_IFDIR | (perm)),                               \
			FNODE_INIT_fn_uid(0), /* root */                                    \
			FNODE_INIT_fn_gid(0), /* root */                                    \
			FNODE_INIT_fn_ino(0),                                               \
			FNODE_INIT_fn_super(&procfs_super),                                 \
			FNODE_INIT_fn_changed,                                              \
			.fn_supent = { NULL, FSUPER_NODES_DELETED },                        \
			FNODE_INIT_fn_allnodes,                                             \
		}},                                                                     \
		.cd_entc = __##symbol_name##_lenof_dir,                                 \
		{
#define MKDIR_ENT(name, type, nodeptr, hash) \
			constdirent_asent(&PP_CAT2(procfs_dirent_, __LINE__)),
#define MKDIR_END \
		}         \
	};
#include "procfs.def"






INTDEF struct fsuper_ops const procfs_super_ops;
INTERN struct fsuper procfs_super = {
	.fs_nodes         = FSUPER_NODES_DELETED, /* Don't add nodes here! */
	.fs_nodeslock     = ATOMIC_RWLOCK_INIT,
	.fs_nodeslockops  = SLIST_HEAD_INITIALIZER(procfs_super.fs_nodeslockops),
	.fs_mounts        = LIST_HEAD_INITIALIZER(procfs_super.fs_mounts),
	.fs_mountslock    = ATOMIC_RWLOCK_INIT,
	.fs_mountslockops = SLIST_HEAD_INITIALIZER(procfs_super.fs_mountslockops),
	.fs_sys           = &procfs_filesys,
	.fs_dev           = NULL,
	.fs_loadblocks    = (typeoffield(struct fsuper, fs_loadblocks))(void *)-1,
	.fs_saveblocks    = (typeoffield(struct fsuper, fs_saveblocks))(void *)-1,
	.fs_feat = {
		.sf_filesize_max       = (pos_t)-1,
		.sf_uid_max            = (uid_t)-1,
		.sf_gid_max            = (gid_t)-1,
		.sf_symlink_max        = (pos_t)-1,
		.sf_link_max           = (nlink_t)-1,
		.sf_magic              = PROC_SUPER_MAGIC,
		.sf_rec_incr_xfer_size = PAGESIZE,
		.sf_rec_max_xfer_size  = PAGESIZE,
		.sf_rec_min_xfer_size  = PAGESIZE,
		.sf_rec_xfer_align     = PAGESIZE,
		.sf_name_max           = (u16)-1,
		.sf_filesizebits       = BITSOF(pos_t),
	},
	.fs_changednodes      = LIST_HEAD_INITIALIZER(procfs_super.fs_changednodes),
	.fs_changednodes_lock = ATOMIC_LOCK_INIT,
	.fs_changednodes_lops = SLIST_HEAD_INITIALIZER(procfs_super.fs_changednodes_lops),
	.fs_changedsuper      = LIST_ENTRY_UNBOUND_INITIALIZER,
	.fs_root = {
		.dn_node = {
			.fn_file = {
				MFILE_INIT_mf_refcnt(2), /* +1: devfs, +1: procfs_filesys.ffs_single */
				MFILE_INIT_mf_ops(&procfs_super_ops.so_fdir.dno_node.no_file),
				MFILE_INIT_mf_lock,
				MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
				MFILE_INIT_mf_initdone,
				MFILE_INIT_mf_lockops,
				MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
				MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
#ifdef CONFIG_HAVE_FS_NOTIFY
				MFILE_INIT_mf_notify,
#endif /* CONFIG_HAVE_FS_NOTIFY */
				MFILE_INIT_mf_flags(MFILE_FS_NOSUID | MFILE_FS_NOEXEC |
				                    MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |
				                    MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE),
				MFILE_INIT_mf_trunclock,
				MFILE_INIT_mf_filesize((uint64_t)-1),
				MFILE_INIT_mf_atime(0, 0),
				MFILE_INIT_mf_mtime(0, 0),
				MFILE_INIT_mf_ctime(0, 0),
				MFILE_INIT_mf_btime(0, 0),
			},
			FNODE_INIT_fn_nlink(1),
			FNODE_INIT_fn_mode(S_IFDIR | 0555),
			FNODE_INIT_fn_uid(0), /* root */
			FNODE_INIT_fn_gid(0), /* root */
			FNODE_INIT_fn_ino(0),
			FNODE_INIT_fn_super(&procfs_super),
			FNODE_INIT_fn_changed,
			FNODE_INIT_fn_supent,
			FNODE_INIT_fn_allnodes,
		},
	},
};

INTERN struct ffilesys procfs_filesys = {
	.ffs_drv      = &drv_self,
	{ .ffs_single = &procfs_super },
	.ffs_flags    = FFILESYS_F_NODEV | FFILESYS_F_SINGLE,
	/* .ffs_name  = */ "procfs",
};

DECL_END

#endif /* !GUARD_MODPROCFS_PROCFSDEFS_C */
