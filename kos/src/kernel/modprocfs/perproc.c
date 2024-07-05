/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODPROCFS_PERPROC_C
#define GUARD_MODPROCFS_PERPROC_C 1
#define __WANT_FS_INIT
#define _KOS_SOURCE 1
#define FNODE_FSDATA_T struct taskpid

#include <kernel/compiler.h>

DECL_BEGIN
struct taskpid;
DECL_END

#include <kernel/fs/constdir.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/lnknode.h>
#include <kernel/fs/node.h>
#include <kernel/fs/printnode.h>
#include <kernel/fs/super.h>
#include <kernel/handle.h>
#include <kernel/malloc.h>
#include <kernel/user.h>
#include <sched/group.h>

#include <kos/ioctl/pidfd.h>
#include <kos/kernel/handle.h>

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/**/
#include "procfs.h"

/* Per-process controls types. */

DECL_BEGIN

/* Lookup a file in a generic per-process directory, given the list of files of said directory. */
PRIVATE WUNUSED NONNULL((1, 3)) REF struct fdirent *KCALL
procfs_perproc_lookup_impl(struct fdirent *const *__restrict files, size_t count,
                           struct flookup_info *__restrict info) {
	size_t lo, hi;
	lo = 0;
	hi = count;
	while (lo < hi) {
		struct fdirent *entry;
		size_t i;
		int cmp;
		i     = (lo + hi) / 2;
		entry = files[i];
		cmp   = strcmpz(entry->fd_name, info->flu_name, info->flu_namelen);
		if (cmp > 0) {
			hi = i;
		} else if (cmp < 0) {
			lo = i + 1;
		} else {
			/* Found it! */
			return incref(entry);
		}
	}
	/* If requested, also do another case-insensitive search. */
	if (info->flu_flags & AT_DOSPATH) {
		size_t i;
		for (i = 0; i < count; ++i) {
			struct fdirent *entry;
			entry = files[i];
			if (entry->fd_namelen != info->flu_namelen)
				continue;
			if (memcasecmp(entry->fd_name, info->flu_name,
			               info->flu_namelen * sizeof(char)) != 0)
				continue;
			/* Found it! */
			return incref(entry);
		}
	}
	return NULL;
}

#define procfs_perproc_enumsz_impl sizeof(struct constdirenum)
PRIVATE NONNULL((3)) void KCALL
procfs_perproc_enum_impl(struct fdirent *const *files, size_t count,
                         struct fdirenum *__restrict result) {
	struct constdirenum *ret = (struct constdirenum *)result;
	/* Fill in enumerator info */
	ret->de_ops    = &constdirenum_ops;
	ret->cde_index = 0;
	ret->cde_entc  = count;
	ret->cde_entv  = files;
}




/* Common operators for all per-process files. */
#define procfs_perproc_v_changed fnode_v_changed
#define procfs_perproc_v_wrattr  fnode_v_wrattr_noop
#define procfs_perproc_v_free    (*(typeof_field(struct fnode_ops, no_free))(void *)-1)
#define procfs_perproc_v_ioctl   fnode_v_ioctl
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(KCALL procfs_perproc_v_destroy)(struct mfile *__restrict self) {
	struct fnode *me = mfile_asnode(self);
	assert(!LIST_ISBOUND(me, fn_allnodes));
	assert(me->fn_supent.rb_rhs == FSUPER_NODES_DELETED);
	assert(me->fn_file.mf_parts == MFILE_PARTS_ANONYMOUS);
	decref_unlikely(me->fn_fsdata);
	kfree(me);
}

/* Operators for per-process directories */
INTDEF NONNULL((1)) void KCALL
procfs_perproc_dir_v_stat(struct mfile *__restrict self,
                          NCX struct stat *result)
		THROWS(...);
#define procfs_perproc_dir_v_free     procfs_perproc_v_free
#define procfs_perproc_dir_v_destroy  procfs_perproc_v_destroy
#define procfs_perproc_dir_v_changed  procfs_perproc_v_changed
#define procfs_perproc_dir_v_wrattr   procfs_perproc_v_wrattr
#define procfs_perproc_dir_v_perm_ops procfs_perproc_v_perm_ops
#define procfs_perproc_dir_v_open     fdirnode_v_open
#define procfs_perproc_dir_v_ioctl    fdirnode_v_ioctl
INTDEF struct mfile_stream_ops const procfs_perproc_dir_v_stream_ops;



/************************************************************************/
/* Special file types (with custom implementations)                     */
/************************************************************************/
INTDEF struct flnknode_ops const procfs_pp_exe;
INTDEF struct flnknode_ops const procfs_pp_cwd;
INTDEF struct flnknode_ops const procfs_pp_root;
INTDEF struct fdirnode_ops const procfs_pp_fd;
INTDEF struct fdirnode_ops const procfs_pp_fdinfo;
INTDEF struct fdirnode_ops const procfs_pp_map_files;
INTDEF struct fdirnode_ops const procfs_pp_task;
INTDEF struct fdirnode_ops const procfs_pp_kos_dcwd;
INTDEF struct fdirnode_ops const procfs_pp_kos_drives;



/************************************************************************/
/* Generic / template-based per-process file/dir-tree impl.             */
/************************************************************************/

/* Templates for per-process files. */
PRIVATE struct fnode const procfs_perproc_reg_template = {
	.fn_file = {
		MFILE_INIT_mf_refcnt(1), /* Return value of creator */
		MFILE_INIT_mf_ops(NULL), /* Will be overwritten */
		MFILE_INIT_mf_lock,
		MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
		MFILE_INIT_mf_initdone,
		MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
		MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
		MFILE_INIT_mf_meta,
		MFILE_INIT_mf_flags(MFILE_F_NOATIME | MFILE_F_NOMTIME |
		                    MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE |
		                    MFILE_FN_FLEETING),
		MFILE_INIT_mf_trunclock,
		MFILE_INIT_mf_filesize((uint64_t)-1),
		MFILE_INIT_mf_atime(0, 0),
		MFILE_INIT_mf_mtime(0, 0),
		MFILE_INIT_mf_ctime(0, 0),
		MFILE_INIT_mf_btime(0, 0),
		MFILE_INIT_mf_msalign(NULL),
	},
	FNODE_INIT_fn_nlink(1),
	FNODE_INIT_fn_mode(0), /* Will be overwritten */
	FNODE_INIT_fn_uid(0),  /* Ignored; overwritten by `fnode_perm_ops::npo_getown' */
	FNODE_INIT_fn_gid(0),  /* Ignored; overwritten by `fnode_perm_ops::npo_getown' */
	FNODE_INIT_fn_ino(0),
	FNODE_INIT_fn_super(&procfs_super),
	FNODE_INIT_fn_changed,
	FNODE_INIT_fn_supent,
	FNODE_INIT_fn_allnodes,
};
PRIVATE struct fnode const procfs_perproc_nomap_template = {
	.fn_file = {
		MFILE_INIT_mf_refcnt(1), /* Return value of creator */
		MFILE_INIT_mf_ops(NULL), /* Will be overwritten */
		MFILE_INIT_mf_lock,
		MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
		MFILE_INIT_mf_initdone,
		MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
		MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
		MFILE_INIT_mf_meta,
		MFILE_INIT_mf_flags(MFILE_F_NOATIME | MFILE_F_NOMTIME |
		                    MFILE_FN_NODIRATIME | MFILE_F_NOUSRMMAP |
		                    MFILE_F_NOUSRIO | MFILE_F_READONLY |
		                    MFILE_F_FIXEDFILESIZE | MFILE_FN_FLEETING),
		MFILE_INIT_mf_trunclock,
		MFILE_INIT_mf_filesize((uint64_t)-1),
		MFILE_INIT_mf_atime(0, 0),
		MFILE_INIT_mf_mtime(0, 0),
		MFILE_INIT_mf_ctime(0, 0),
		MFILE_INIT_mf_btime(0, 0),
		MFILE_INIT_mf_msalign(NULL),
	},
	FNODE_INIT_fn_nlink(1),
	FNODE_INIT_fn_mode(S_IFDIR | 0555), /* May be overwritten (but this is the default for the /proc/[pid] root directory) */
	FNODE_INIT_fn_uid(0), /* Ignored; overwritten by `fnode_perm_ops::npo_getown' */
	FNODE_INIT_fn_gid(0), /* Ignored; overwritten by `fnode_perm_ops::npo_getown' */
	FNODE_INIT_fn_ino(0),
	FNODE_INIT_fn_super(&procfs_super),
	FNODE_INIT_fn_changed,
	FNODE_INIT_fn_supent,
	FNODE_INIT_fn_allnodes,
};

/* Template for files from "/proc/[PID]/fd/[NO]" */
INTDEF struct flnknode_ops const procfs_pp_fdlnk_ops;
INTERN_CONST struct flnknode const procfs_pp_fdlnk_template = {
	.ln_node = {
		.fn_file = {
			MFILE_INIT_mf_refcnt(1), /* Return value of creator */
			MFILE_INIT_mf_ops(&procfs_pp_fdlnk_ops.lno_node.no_file),
			MFILE_INIT_mf_lock,
			MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
			MFILE_INIT_mf_initdone,
			MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
			MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
			MFILE_INIT_mf_meta,
			MFILE_INIT_mf_flags(MFILE_F_NOATIME | MFILE_F_NOMTIME |
			                    MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |
			                    MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE |
			                    MFILE_FN_FLEETING),
			MFILE_INIT_mf_trunclock,
			MFILE_INIT_mf_filesize(0),
			MFILE_INIT_mf_atime(0, 0),
			MFILE_INIT_mf_mtime(0, 0),
			MFILE_INIT_mf_ctime(0, 0),
			MFILE_INIT_mf_btime(0, 0),
			MFILE_INIT_mf_msalign(NULL),
		},
		FNODE_INIT_fn_nlink(1),
		FNODE_INIT_fn_mode(S_IFLNK | 0777),
		FNODE_INIT_fn_uid(0), /* Ignored; overwritten by `fnode_perm_ops::npo_getown' */
		FNODE_INIT_fn_gid(0), /* Ignored; overwritten by `fnode_perm_ops::npo_getown' */
		FNODE_INIT_fn_ino(0),
		FNODE_INIT_fn_super(&procfs_super),
		FNODE_INIT_fn_changed,
		FNODE_INIT_fn_supent,
		FNODE_INIT_fn_allnodes,
	},
};

/* Template for files from  "/proc/[PID]/fdinfo/[NO]" */
INTDEF struct printnode_ops const procfs_pp_fdinfo_ops;
INTERN_CONST struct printnode const procfs_pp_fdinfo_template = {
	.pn_node = {{
		.fn_file = {
			MFILE_INIT_mf_refcnt(1), /* Return value of creator */
			MFILE_INIT_mf_ops(&procfs_pp_fdinfo_ops.pno_reg.rno_node.no_file),
			MFILE_INIT_mf_lock,
			MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
			MFILE_INIT_mf_initdone,
			MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
			MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
			MFILE_INIT_mf_meta,
			MFILE_INIT_mf_flags(MFILE_F_NOATIME | MFILE_F_NOMTIME |
			                    MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE |
			                    MFILE_FN_FLEETING),
			MFILE_INIT_mf_trunclock,
			MFILE_INIT_mf_filesize((uint64_t)-1),
			MFILE_INIT_mf_atime(0, 0),
			MFILE_INIT_mf_mtime(0, 0),
			MFILE_INIT_mf_ctime(0, 0),
			MFILE_INIT_mf_btime(0, 0),
			MFILE_INIT_mf_msalign(NULL),
		},
		FNODE_INIT_fn_nlink(1),
		FNODE_INIT_fn_mode(S_IFREG | 0400),
		FNODE_INIT_fn_uid(0),  /* Ignored; overwritten by `fnode_perm_ops::npo_getown' */
		FNODE_INIT_fn_gid(0),  /* Ignored; overwritten by `fnode_perm_ops::npo_getown' */
		FNODE_INIT_fn_ino(0),
		FNODE_INIT_fn_super(&procfs_super),
		FNODE_INIT_fn_changed,
		FNODE_INIT_fn_supent,
		FNODE_INIT_fn_allnodes,
	}},
};

/* Template for files from "/proc/[PID]/kos/dcwd/[id]" */
INTDEF struct flnknode_ops const procfs_perproc_dcwdlink_ops;
INTERN_CONST struct flnknode const procfs_perproc_dcwdlink_template = {
	.ln_node = {
		.fn_file = {
			MFILE_INIT_mf_refcnt(1), /* Return value of creator */
			MFILE_INIT_mf_ops(&procfs_perproc_dcwdlink_ops.lno_node.no_file),
			MFILE_INIT_mf_lock,
			MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
			MFILE_INIT_mf_initdone,
			MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
			MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
			MFILE_INIT_mf_meta,
			MFILE_INIT_mf_flags(MFILE_F_NOATIME | MFILE_F_NOMTIME |
			                    MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |
			                    MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE |
			                    MFILE_FN_FLEETING),
			MFILE_INIT_mf_trunclock,
			MFILE_INIT_mf_filesize(0),
			MFILE_INIT_mf_atime(0, 0),
			MFILE_INIT_mf_mtime(0, 0),
			MFILE_INIT_mf_ctime(0, 0),
			MFILE_INIT_mf_btime(0, 0),
			MFILE_INIT_mf_msalign(NULL),
		},
		FNODE_INIT_fn_nlink(1),
		FNODE_INIT_fn_mode(S_IFLNK | 0777),
		FNODE_INIT_fn_uid(0), /* Ignored; overwritten by `fnode_perm_ops::npo_getown' */
		FNODE_INIT_fn_gid(0), /* Ignored; overwritten by `fnode_perm_ops::npo_getown' */
		FNODE_INIT_fn_ino(0),
		FNODE_INIT_fn_super(&procfs_super),
		FNODE_INIT_fn_changed,
		FNODE_INIT_fn_supent,
		FNODE_INIT_fn_allnodes,
	},
};

/* Template for files from "/proc/[PID]/kos/drives/[id]" */
INTDEF struct flnknode_ops const procfs_perproc_drivelink_ops;
INTERN_CONST struct flnknode const procfs_perproc_drivelink_template = {
	.ln_node = {
		.fn_file = {
			MFILE_INIT_mf_refcnt(1), /* Return value of creator */
			MFILE_INIT_mf_ops(&procfs_perproc_drivelink_ops.lno_node.no_file),
			MFILE_INIT_mf_lock,
			MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
			MFILE_INIT_mf_initdone,
			MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
			MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
			MFILE_INIT_mf_meta,
			MFILE_INIT_mf_flags(MFILE_F_NOATIME | MFILE_F_NOMTIME |
			                    MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |
			                    MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE |
			                    MFILE_FN_FLEETING),
			MFILE_INIT_mf_trunclock,
			MFILE_INIT_mf_filesize(0),
			MFILE_INIT_mf_atime(0, 0),
			MFILE_INIT_mf_mtime(0, 0),
			MFILE_INIT_mf_ctime(0, 0),
			MFILE_INIT_mf_btime(0, 0),
			MFILE_INIT_mf_msalign(NULL),
		},
		FNODE_INIT_fn_nlink(1),
		FNODE_INIT_fn_mode(S_IFLNK | 0777),
		FNODE_INIT_fn_uid(0), /* Ignored; overwritten by `fnode_perm_ops::npo_getown' */
		FNODE_INIT_fn_gid(0), /* Ignored; overwritten by `fnode_perm_ops::npo_getown' */
		FNODE_INIT_fn_ino(0),
		FNODE_INIT_fn_super(&procfs_super),
		FNODE_INIT_fn_changed,
		FNODE_INIT_fn_supent,
		FNODE_INIT_fn_allnodes,
	},
};


/* Template for files from "/proc/[PID]/map_files/[...]" */
INTDEF struct flnknode_ops const perproc_mapfile_lnknode_ops;
INTERN_CONST struct flnknode const perproc_mapfile_lnknode_template = {
	.ln_node = {
		.fn_file = {
			MFILE_INIT_mf_refcnt(1), /* Return value of creator */
			MFILE_INIT_mf_ops(&perproc_mapfile_lnknode_ops.lno_node.no_file),
			MFILE_INIT_mf_lock,
			MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
			MFILE_INIT_mf_initdone,
			MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
			MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
			MFILE_INIT_mf_meta,
			MFILE_INIT_mf_flags(MFILE_F_NOATIME | MFILE_F_NOMTIME |
			                    MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |
			                    MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE |
			                    MFILE_FN_FLEETING),
			MFILE_INIT_mf_trunclock,
			MFILE_INIT_mf_filesize(0),
			MFILE_INIT_mf_atime(0, 0),
			MFILE_INIT_mf_mtime(0, 0),
			MFILE_INIT_mf_ctime(0, 0),
			MFILE_INIT_mf_btime(0, 0),
			MFILE_INIT_mf_msalign(NULL),
		},
		FNODE_INIT_fn_nlink(1),
		FNODE_INIT_fn_mode(S_IFLNK | 0400),
		FNODE_INIT_fn_uid(0), /* Ignored; overwritten by `fnode_perm_ops::npo_getown' */
		FNODE_INIT_fn_gid(0), /* Ignored; overwritten by `fnode_perm_ops::npo_getown' */
		FNODE_INIT_fn_ino(0),
		FNODE_INIT_fn_super(&procfs_super),
		FNODE_INIT_fn_changed,
		FNODE_INIT_fn_supent,
		FNODE_INIT_fn_allnodes,
	},
};


/* Directory entry structure for statically defined /proc/[pid]/... files. */
struct procfs_perproc_dirent {
	struct fnode_ops const   *ppd_fops;    /* [1..1][const] File-node operators. */
	mode_t ppd_mod;                        /* [const] File-mode for the pointed-to file. */
#ifndef __WANT_FS_INLINE_STRUCTURES /* Doesn't work because g++ is lazy */
	struct fdirent            ppd_ent;     /* Underlying directory entry. */
#else /* !__WANT_FS_INLINE_STRUCTURES */
	_FDIRENT_FIELDS
#endif /* __WANT_FS_INLINE_STRUCTURES */
};

/* Assert that fields of `struct procfs_perproc_dirent' are binary compatible with `fdirent' starting at `fd_refcnt' */
static_assert((offsetof(struct procfs_perproc_dirent, fd_refcnt) - offsetof(struct procfs_perproc_dirent, fd_refcnt)) == offsetof(struct fdirent, fd_refcnt));
static_assert((offsetof(struct procfs_perproc_dirent, fd_ops) - offsetof(struct procfs_perproc_dirent, fd_refcnt)) == offsetof(struct fdirent, fd_ops));
static_assert((offsetof(struct procfs_perproc_dirent, fd_ino) - offsetof(struct procfs_perproc_dirent, fd_refcnt)) == offsetof(struct fdirent, fd_ino));
static_assert((offsetof(struct procfs_perproc_dirent, fd_hash) - offsetof(struct procfs_perproc_dirent, fd_refcnt)) == offsetof(struct fdirent, fd_hash));
static_assert((offsetof(struct procfs_perproc_dirent, fd_namelen) - offsetof(struct procfs_perproc_dirent, fd_refcnt)) == offsetof(struct fdirent, fd_namelen));
static_assert((offsetof(struct procfs_perproc_dirent, fd_type) - offsetof(struct procfs_perproc_dirent, fd_refcnt)) == offsetof(struct fdirent, fd_type));
static_assert((offsetof(struct procfs_perproc_dirent, fd_name) - offsetof(struct procfs_perproc_dirent, fd_refcnt)) == offsetof(struct fdirent, fd_name));

#define fdirent_asperproc(self)           container_of(&(self)->fd_refcnt, struct procfs_perproc_dirent, fd_refcnt)
#define procfs_perproc_dirent_asent(self) ((struct fdirent *)&(self)->fd_refcnt)


PRIVATE WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
procfs_perproc_dirent_v_opennode_reg(struct fdirent *__restrict self,
                                     struct fdirnode *__restrict dir) {
	struct procfs_perproc_dirent *me = fdirent_asperproc(self);
	REF struct fnode *result;
	result = (REF struct fnode *)memcpy(kmalloc(sizeof(struct fnode), GFP_NORMAL),
	                                    &procfs_perproc_reg_template, sizeof(struct fnode));

	/* Fill in fields. */
	result->fn_file.mf_ops = &me->ppd_fops->no_file;
	result->fn_fsdata      = incref(dir->dn_node.fn_fsdata);
	result->fn_ino         = procfs_perproc_ino(result->fn_fsdata, result->fn_file.mf_ops);
	result->fn_mode        = me->ppd_mod;
	return result;
}

PRIVATE WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
procfs_perproc_dirent_v_opennode_nomap(struct fdirent *__restrict self,
                                       struct fdirnode *__restrict dir) {
	struct procfs_perproc_dirent *me = fdirent_asperproc(self);
	REF struct fnode *result;
	result = (REF struct fnode *)memcpy(kmalloc(sizeof(struct fnode), GFP_NORMAL),
	                                    &procfs_perproc_nomap_template, sizeof(struct fnode));

	/* Fill in fields. */
	result->fn_file.mf_ops = &me->ppd_fops->no_file;
	result->fn_fsdata      = incref(dir->dn_node.fn_fsdata);
	result->fn_ino         = procfs_perproc_ino(result->fn_fsdata, result->fn_file.mf_ops);
	result->fn_mode        = me->ppd_mod;
	return result;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1, 2)) ino_t FCALL
procfs_perproc_dirent_v_getino(struct fdirent *__restrict self,
                               struct fdirnode *__restrict dir) {
	struct procfs_perproc_dirent *me = fdirent_asperproc(self);
	return procfs_perproc_ino(dir->dn_node.fn_fsdata, &me->ppd_fops->no_file);
}


PRIVATE struct fdirent_ops const procfs_perproc_dirent_ops_reg = {
	/* `struct procfs_perproc_dirent'-objects are only allocated statically, so destroy must never be called. */
	.fdo_destroy  = (typeof_field(struct fdirent_ops, fdo_destroy))(void *)-1,
	.fdo_opennode = &procfs_perproc_dirent_v_opennode_reg,
	.fdo_getino   = &procfs_perproc_dirent_v_getino,
};
PRIVATE struct fdirent_ops const procfs_perproc_dirent_ops_nomap = {
	/* `struct procfs_perproc_dirent'-objects are only allocated statically, so destroy must never be called. */
	.fdo_destroy  = (typeof_field(struct fdirent_ops, fdo_destroy))(void *)-1,
	.fdo_opennode = &procfs_perproc_dirent_v_opennode_nomap,
	.fdo_getino   = &procfs_perproc_dirent_v_getino,
};

/* Return the set of directory entry operators used for per-process files of `dt_type' (one of `DT_*') */
#define procfs_perproc_dirent_ops_for(dt_type)            \
	((dt_type) == DT_REG ? &procfs_perproc_dirent_ops_reg \
	                     : &procfs_perproc_dirent_ops_nomap)



#if __SIZEOF_INO_T__ == 4
#define _INVALID_INO ((ino_t)UINT32_C(0xcccccccc))
#elif __SIZEOF_INO_T__ == 8
#define _INVALID_INO ((ino_t)UINT64_C(0xcccccccccccccccc))
#else /* __SIZEOF_INO_T__ == ... */
#error "Unsupported sizeof(ino_t)"
#endif /* __SIZEOF_INO_T__ != ... */

/* Forward declarations */
#define MKDIR_BEGIN(ops_symbol_name)               INTDEF struct fdirnode_ops const ops_symbol_name;
#define MKREG_RO(ops_symbol_name, printer)         INTDEF struct printnode_ops const ops_symbol_name;
#define MKREG_RW(ops_symbol_name, printer, writer) INTDEF struct printnode_ops const ops_symbol_name;
#define MKLNK(ops_symbol_name, readlink)           INTDEF struct flnknode_ops const ops_symbol_name;
#include "perproc.def"

/* Define directory entries. */
#define _DEFINE_DIRENT(symbol_name, name, type, perm, fnode_ops_ptr, hash) \
	PRIVATE struct procfs_perproc_dirent symbol_name = {                   \
		.ppd_fops    = (struct fnode_ops *)(fnode_ops_ptr),                \
		.ppd_mod     = DTTOIF(type) | (perm),                              \
		.fd_refcnt  = 2, /* +1: symbol_name, +1: DIRECTORY_ENTRY_LIST */   \
		.fd_ops     = procfs_perproc_dirent_ops_for(type),                 \
		.fd_ino     = _INVALID_INO, /* Mustn't be used */                  \
		.fd_hash    = hash,                                                \
		.fd_namelen = COMPILER_STRLEN(name),                               \
		.fd_type    = type,                                                \
		/* .fd_name = */ name                                              \
	};
#define ROOTENT(name, type, perm, fnode_ops_ptr, hash) \
	_DEFINE_DIRENT(PP_CAT2(perproc_root_dirent_, __LINE__), name, type, perm, fnode_ops_ptr, hash)
#define MKDIR_ENT(name, type, perm, fnode_ops_ptr, hash) \
	_DEFINE_DIRENT(PP_CAT2(perproc_dirent_, __LINE__), name, type, perm, fnode_ops_ptr, hash)
#include "perproc.def"
#undef _DEFINE_DIRENT


/* Define sub-directory tables. */
#define MKDIR_BEGIN(ops_symbol_name) \
	PRIVATE REF struct fdirent *const __##ops_symbol_name##_files[] = {
#define MKDIR_ENT(name, type, perm, fnode_ops_ptr, hash) \
		procfs_perproc_dirent_asent(&PP_CAT2(perproc_dirent_, __LINE__)),
#define MKDIR_END \
	};
#include "perproc.def"


/* Define operator tables. */
#define procfs_perproc_lnknode_v_destroy  procfs_perproc_v_destroy
#define procfs_perproc_lnknode_v_changed  procfs_perproc_v_changed
#define procfs_perproc_lnknode_v_ioctl    flnknode_v_ioctl
#define procfs_perproc_lnknode_v_free     procfs_perproc_v_free
#define procfs_perproc_lnknode_v_wrattr   procfs_perproc_v_wrattr
#define procfs_perproc_lnknode_v_perm_ops procfs_perproc_v_perm_ops
INTDEF struct mfile_stream_ops const procfs_perproc_lnknode_v_stream_ops;
#define procfs_perproc_printnode_v_ioctl printnode_v_ioctl
INTDEF struct mfile_stream_ops const procfs_perproc_printnode_v_stream_ops;
INTDEF NONNULL((1)) void KCALL
procfs_perproc_printnode_v_stat(struct mfile *__restrict self,
                                NCX struct stat *result)
		THROWS(...);

#define MKDIR_BEGIN(ops_symbol_name)                                             \
	PRIVATE WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL                    \
	__##ops_symbol_name##_v_lookup(struct fdirnode *__restrict UNUSED(self),     \
	                               struct flookup_info *__restrict info) {       \
		return procfs_perproc_lookup_impl(__##ops_symbol_name##_files,           \
		                                  lengthof(__##ops_symbol_name##_files), \
		                                  info);                                 \
	}                                                                            \
	PRIVATE NONNULL((1)) void KCALL                                              \
	__##ops_symbol_name##_v_enum(struct fdirenum *__restrict result) {           \
		procfs_perproc_enum_impl(__##ops_symbol_name##_files,                    \
		                         lengthof(__##ops_symbol_name##_files),          \
		                         result);                                        \
	}                                                                            \
	INTERN_CONST struct fdirnode_ops const ops_symbol_name = {                   \
		.dno_node = {                                                            \
			.no_file = {                                                         \
				.mo_destroy = &procfs_perproc_dir_v_destroy,                     \
				.mo_changed = &procfs_perproc_dir_v_changed,                     \
				.mo_stream  = &procfs_perproc_dir_v_stream_ops,                  \
			},                                                                   \
			.no_free   = &procfs_perproc_dir_v_free,                             \
			.no_wrattr = &procfs_perproc_dir_v_wrattr,                           \
			.no_perm   = &procfs_perproc_dir_v_perm_ops,                         \
		},                                                                       \
		.dno_lookup = &__##ops_symbol_name##_v_lookup,                           \
		.dno_enumsz = procfs_perproc_enumsz_impl,                                \
		.dno_enum   = &__##ops_symbol_name##_v_enum,                             \
	};
#define MKREG_RO(ops_symbol_name, printer)                               \
	INTDEF NONNULL((1, 2)) void KCALL                                    \
	printer(struct printnode *__restrict self,                           \
	        pformatprinter printer_, void *arg,                          \
	        pos_t offset_hint);                                          \
	INTERN_CONST struct printnode_ops const ops_symbol_name = {          \
		.pno_reg = {{                                                    \
			.no_file = {                                                 \
				.mo_destroy    = &procfs_perproc_v_destroy,              \
				.mo_loadblocks = &printnode_v_loadblocks,                \
				.mo_changed    = &procfs_perproc_v_changed,              \
				.mo_stream     = &procfs_perproc_printnode_v_stream_ops, \
			},                                                           \
			.no_free   = &procfs_perproc_v_free,                         \
			.no_wrattr = &procfs_perproc_v_wrattr,                       \
			.no_perm   = &procfs_perproc_v_perm_ops,                     \
		}},                                                              \
		.pno_print = &printer,                                           \
	};
#define MKREG_RW(ops_symbol_name, printer, writer)                             \
	INTDEF NONNULL((1, 2)) void KCALL                                          \
	printer(struct printnode *__restrict self,                                 \
	        pformatprinter printer_, void *arg,                                \
	        pos_t offset_hint);                                                \
	INTDEF WUNUSED NONNULL((1)) size_t KCALL                                   \
	writer(struct mfile *__restrict self, NCX void const *src,                 \
	       size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);           \
	PRIVATE struct mfile_stream_ops const __##ops_symbol_name##_stream_ops = { \
		.mso_pread  = &printnode_v_pread,                                      \
		.mso_preadv = &printnode_v_preadv,                                     \
		.mso_pwrite = &writer,                                                 \
		.mso_stat   = &procfs_perproc_printnode_v_stat,                        \
		.mso_ioctl  = &procfs_perproc_printnode_v_ioctl,                       \
	};                                                                         \
	INTERN_CONST struct printnode_ops const ops_symbol_name = {                \
		.pno_reg = {{                                                          \
			.no_file = {                                                       \
				.mo_destroy    = &procfs_perproc_v_destroy,                    \
				.mo_loadblocks = &printnode_v_loadblocks,                      \
				.mo_changed    = &procfs_perproc_v_changed,                    \
				.mo_stream     = &__##ops_symbol_name##_stream_ops,            \
			},                                                                 \
			.no_free   = &procfs_perproc_v_free,                               \
			.no_wrattr = &procfs_perproc_v_wrattr,                             \
			.no_perm   = &procfs_perproc_v_perm_ops,                           \
		}},                                                                    \
		.pno_print = &printer,                                                 \
	};
#define MKLNK(ops_symbol_name, readlink)                            \
	INTDEF WUNUSED NONNULL((1)) size_t KCALL                        \
	readlink(struct flnknode *__restrict self,                      \
	         NCX /*utf-8*/ char *buf, size_t bufsize)               \
			THROWS(E_SEGFAULT, E_IOERROR, ...);                     \
	INTERN_CONST struct flnknode_ops const ops_symbol_name = {      \
		.lno_node = {                                               \
			.no_file = {                                            \
				.mo_destroy = &procfs_perproc_lnknode_v_destroy,    \
				.mo_changed = &procfs_perproc_lnknode_v_changed,    \
				.mo_stream  = &procfs_perproc_lnknode_v_stream_ops, \
			},                                                      \
			.no_free   = &procfs_perproc_lnknode_v_free,            \
			.no_wrattr = &procfs_perproc_lnknode_v_wrattr,          \
			.no_perm   = &procfs_perproc_lnknode_v_perm_ops,        \
		},                                                          \
		.lno_readlink = &readlink,                                  \
	};
#include "perproc.def"






/************************************************************************/
/* Per-process root directory                                           */
/************************************************************************/

/* Define the per-process root directory. */
PRIVATE REF struct fdirent *const procfs_perproc_root_files[] = {
#define ROOTENT(name, type, perm, fnode_ops_ptr, hash) \
	procfs_perproc_dirent_asent(&PP_CAT2(perproc_root_dirent_, __LINE__)),
#include "perproc.def"
};

PRIVATE WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
procfs_perproc_root_v_lookup(struct fdirnode *__restrict UNUSED(self),
                             struct flookup_info *__restrict info) {
	return procfs_perproc_lookup_impl(procfs_perproc_root_files,
	                                  lengthof(procfs_perproc_root_files),
	                                  info);
}

#define procfs_perproc_root_v_enumsz procfs_perproc_enumsz_impl
PRIVATE NONNULL((1)) void KCALL
procfs_perproc_root_v_enum(struct fdirenum *__restrict result) {
	procfs_perproc_enum_impl(procfs_perproc_root_files,
	                         lengthof(procfs_perproc_root_files),
	                         result);
}

PRIVATE BLOCKING NONNULL((1)) syscall_slong_t KCALL
procfs_perproc_root_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
                            NCX UNCHECKED void *arg, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, ...) {
	struct fdirnode *me = mfile_asdir(self);

	/* Forward ioctls from <kos/ioctl/pidfd.h> to the bound taskpid object. */
	if (_IOC_ISKOS(cmd) && _IOC_TYPE(cmd) == _IOC_TYPE(PIDFD_IOC_GETTID)) {
		return (*handle_type_db.h_ioctl[HANDLE_TYPE_PIDFD])(me->dn_node.fn_fsdata,
		                                                    cmd, arg, mode);
	}

	/* Fallback: do an ioctl on the directory itself. */
	return fdirnode_v_ioctl(self, cmd, arg, mode);
}

PRIVATE WUNUSED NONNULL((1)) REF void *KCALL
procfs_perproc_root_v_tryas(struct mfile *__restrict self,
                            uintptr_half_t wanted_type)
		THROWS(...) {
	struct fdirnode *me = mfile_asdir(self);

	/* Allow file nodes for `/proc/[PID]' (and only that one)
	 * to be casted into the underlying taskpid object,  thus
	 * mirroring linux's pidfd_open(42) <=>  open("/proc/42")
	 * behavior. */
	if (wanted_type == HANDLE_TYPE_PIDFD)
		return incref(me->dn_node.fn_fsdata);
	return NULL;
}


PRIVATE struct mfile_stream_ops const procfs_perproc_root_v_stream_ops = {
	.mso_open  = &fdirnode_v_open,
	.mso_stat  = &procfs_perproc_dir_v_stat,
	.mso_ioctl = &procfs_perproc_root_v_ioctl,
	.mso_tryas = &procfs_perproc_root_v_tryas,
};

/* Operators for `/proc/[pid]/'
 * NOTE: For this directory, `fn_fsdata' is a `REF struct taskpid *' [1..1] */
INTERN_CONST struct fdirnode_ops const procfs_perproc_root_ops = {
	.dno_node = {
		.no_file = {
			.mo_destroy = &procfs_perproc_dir_v_destroy,
			.mo_changed = &procfs_perproc_dir_v_changed,
			.mo_stream  = &procfs_perproc_root_v_stream_ops,
		},
		.no_free   = &procfs_perproc_dir_v_free,
		.no_wrattr = &procfs_perproc_dir_v_wrattr,
		.no_perm   = &procfs_perproc_dir_v_perm_ops,
	},
	.dno_lookup = &procfs_perproc_root_v_lookup,
	.dno_enumsz = procfs_perproc_root_v_enumsz,
	.dno_enum   = &procfs_perproc_root_v_enum,
};



/* Define the per-task root directory. */
PRIVATE REF struct fdirent *const procfs_pertask_root_files[] = {
#define ROOTENT(name, type, perm, fnode_ops_ptr, hash) \
	procfs_perproc_dirent_asent(&PP_CAT2(perproc_root_dirent_, __LINE__)),
#define DEFINE_PERTASK_ROOT_DIRECTORY
#include "perproc.def"
#undef DEFINE_PERTASK_ROOT_DIRECTORY
};

PRIVATE WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
procfs_pertask_root_v_lookup(struct fdirnode *__restrict UNUSED(self),
                             struct flookup_info *__restrict info) {
	return procfs_perproc_lookup_impl(procfs_pertask_root_files,
	                                  lengthof(procfs_pertask_root_files),
	                                  info);
}

#define procfs_pertask_root_v_enumsz procfs_perproc_root_v_enumsz
PRIVATE NONNULL((1)) void KCALL
procfs_pertask_root_v_enum(struct fdirenum *__restrict result) {
	procfs_perproc_enum_impl(procfs_pertask_root_files,
	                         lengthof(procfs_pertask_root_files),
	                         result);
}



/* Operators for `/proc/[pid]/task/[tid]'
 * NOTE: For this directory, `fn_fsdata' is a `REF struct taskpid *' [1..1] */
INTERN_CONST struct fdirnode_ops const procfs_pertask_root_ops = {
	.dno_node = {
		.no_file = {
			.mo_destroy = &procfs_perproc_dir_v_destroy,
			.mo_changed = &procfs_perproc_dir_v_changed,
			.mo_stream  = &procfs_perproc_root_v_stream_ops,
		},
		.no_free   = &procfs_perproc_dir_v_free,
		.no_wrattr = &procfs_perproc_dir_v_wrattr,
		.no_perm   = &procfs_perproc_dir_v_perm_ops,
	},
	.dno_lookup = &procfs_pertask_root_v_lookup,
	.dno_enumsz = procfs_pertask_root_v_enumsz,
	.dno_enum   = &procfs_pertask_root_v_enum,
};






/************************************************************************/
/* Per-process root directory entry operators (for the /proc/PID dir's dirent) */
/************************************************************************/
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL procfs_perproc_root_dirent_v_destroy)(struct fdirent *__restrict self) {
	struct procfs_perproc_root_dirent *me = fdirent_asperprocroot(self);
	decref_unlikely(me->pprd_pid);
	kfree(me);
}

PRIVATE WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
procfs_perproc_root_dirent_v_opennode(struct fdirent *__restrict self,
                                      struct fdirnode *__restrict UNUSED(dir)) {
	struct procfs_perproc_root_dirent *me = fdirent_asperprocroot(self);
	REF struct fnode *result;
	result = (REF struct fnode *)memcpy(kmalloc(sizeof(struct fnode), GFP_NORMAL),
	                                    &procfs_perproc_nomap_template, sizeof(struct fnode));

	/* Fill in fields. */
	result->fn_file.mf_ops = &procfs_perproc_root_ops.dno_node.no_file;
	result->fn_fsdata = incref(me->pprd_pid);
	result->fn_ino = procfs_perproc_ino(me->pprd_pid, &procfs_perproc_root_ops);
	return result;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1, 2)) ino_t
NOTHROW(FCALL procfs_perproc_root_dirent_v_getino)(struct fdirent *__restrict self,
                                                   struct fdirnode *__restrict UNUSED(dir)) {
	struct procfs_perproc_root_dirent *me = fdirent_asperprocroot(self);
	return procfs_perproc_ino(me->pprd_pid, &procfs_perproc_root_ops);
}

/* Operators for `procfs_perproc_root_dirent' */
INTERN_CONST struct fdirent_ops const procfs_perproc_root_dirent_ops = {
	.fdo_destroy  = &procfs_perproc_root_dirent_v_destroy,
	.fdo_opennode = &procfs_perproc_root_dirent_v_opennode,
	.fdo_getino   = &procfs_perproc_root_dirent_v_getino,
};

PRIVATE WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
procfs_pertask_root_dirent_v_opennode(struct fdirent *__restrict self,
                                      struct fdirnode *__restrict UNUSED(dir)) {
	struct procfs_perproc_root_dirent *me = fdirent_asperprocroot(self);
	REF struct fnode *result;
	result = (REF struct fnode *)memcpy(kmalloc(sizeof(struct fnode), GFP_NORMAL),
	                                    &procfs_perproc_nomap_template, sizeof(struct fnode));

	/* Fill in fields. */
	result->fn_file.mf_ops = &procfs_pertask_root_ops.dno_node.no_file;
	result->fn_fsdata      = incref(me->pprd_pid);
	result->fn_ino         = procfs_perproc_ino(me->pprd_pid, &procfs_pertask_root_ops);
	return result;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1, 2)) ino_t
NOTHROW(FCALL procfs_pertask_root_dirent_v_getino)(struct fdirent *__restrict self,
                                                   struct fdirnode *__restrict UNUSED(dir)) {
	struct procfs_perproc_root_dirent *me = fdirent_asperprocroot(self);
	return procfs_perproc_ino(me->pprd_pid, &procfs_pertask_root_ops);
}

/* Operators for `procfs_pertask_root_dirent' (under /proc/[pid]/task/[tid]) */
INTERN_CONST struct fdirent_ops const procfs_pertask_root_dirent_ops = {
	.fdo_destroy  = &procfs_perproc_root_dirent_v_destroy,
	.fdo_opennode = &procfs_pertask_root_dirent_v_opennode,
	.fdo_getino   = &procfs_pertask_root_dirent_v_getino,
};


DECL_END

#endif /* !GUARD_MODPROCFS_PERPROC_C */
