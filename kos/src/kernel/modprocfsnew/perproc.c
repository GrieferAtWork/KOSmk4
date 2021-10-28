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
#ifndef GUARD_MODPROCFS_PERPROC_C
#define GUARD_MODPROCFS_PERPROC_C 1
#define __WANT_FS_INIT
#define _KOS_SOURCE    1
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
#include <kernel/malloc.h>
#include <kernel/user.h>
#include <sched/pid.h>

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
#define procfs_perproc_v_free    (*((void(KCALL *)(struct fnode *__restrict))(void *)(uintptr_t)-1))
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
#define procfs_perproc_dir_v_free    procfs_perproc_v_free
#define procfs_perproc_dir_v_destroy procfs_perproc_v_destroy
#define procfs_perproc_dir_v_changed procfs_perproc_v_changed
#define procfs_perproc_dir_v_wrattr  procfs_perproc_v_wrattr
INTDEF struct mfile_stream_ops const procfs_perproc_dir_v_stream_ops;
#define procfs_perproc_dir_v_open fdirnode_v_open
#define procfs_perproc_dir_v_stat fdirnode_v_stat



/************************************************************************/
/* Special file types (with custom implementations)                     */
/************************************************************************/
INTDEF struct flnknode_ops const procfs_pp_exe;
INTDEF struct flnknode_ops const procfs_pp_cwd;
INTDEF struct flnknode_ops const procfs_pp_root;
INTDEF struct fdirnode_ops const procfs_pp_fd;
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
		MFILE_INIT_mf_lockops,
		MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
		MFILE_INIT_mf_blockshift(PAGESHIFT),
		MFILE_INIT_mf_flags(MFILE_F_NOATIME | MFILE_F_NOMTIME |
		                    MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE |
		                    MFILE_FN_FLEETING),
		MFILE_INIT_mf_trunclock,
		MFILE_INIT_mf_filesize((uint64_t)-1),
		MFILE_INIT_mf_atime(0, 0),
		MFILE_INIT_mf_mtime(0, 0),
		MFILE_INIT_mf_ctime(0, 0),
	},
	FNODE_INIT_fn_nlink(1),
	FNODE_INIT_fn_mode(0), /* Will be overwritten */
	FNODE_INIT_fn_uid(0),
	FNODE_INIT_fn_gid(0),
	FNODE_INIT_fn_ino(0),
	FNODE_INIT_fn_super(&procfs_super),
	FNODE_INIT_fn_changed,
	FNODE_INIT_fn_supent_EX({ NULL, FSUPER_NODES_DELETED }),
	FNODE_INIT_fn_allnodes,
};
PRIVATE struct fnode const procfs_perproc_nomap_template = {
	.fn_file = {
		MFILE_INIT_mf_refcnt(1), /* Return value of creator */
		MFILE_INIT_mf_ops(NULL), /* Will be overwritten */
		MFILE_INIT_mf_lock,
		MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
		MFILE_INIT_mf_initdone,
		MFILE_INIT_mf_lockops,
		MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
		MFILE_INIT_mf_blockshift(PAGESHIFT),
		MFILE_INIT_mf_flags(MFILE_F_NOATIME | MFILE_F_NOMTIME |
		                    MFILE_FN_NODIRATIME | MFILE_F_NOUSRMMAP |
		                    MFILE_F_NOUSRIO | MFILE_F_READONLY |
		                    MFILE_F_FIXEDFILESIZE | MFILE_FN_FLEETING),
		MFILE_INIT_mf_trunclock,
		MFILE_INIT_mf_filesize((uint64_t)-1),
		MFILE_INIT_mf_atime(0, 0),
		MFILE_INIT_mf_mtime(0, 0),
		MFILE_INIT_mf_ctime(0, 0),
	},
	FNODE_INIT_fn_nlink(1),
	FNODE_INIT_fn_mode(S_IFDIR | 0555), /* May be overwritten (but this is the default for the /proc/[pid] root directory) */
	FNODE_INIT_fn_uid(0),
	FNODE_INIT_fn_gid(0),
	FNODE_INIT_fn_ino(0),
	FNODE_INIT_fn_super(&procfs_super),
	FNODE_INIT_fn_changed,
	FNODE_INIT_fn_supent_EX({ NULL, FSUPER_NODES_DELETED }),
	FNODE_INIT_fn_allnodes,
};

/* Template for files from "/proc/[PID]/fd/[NO]" */
INTDEF struct flnknode_ops const procfs_perproc_fdlnk_ops;
INTERN_CONST struct flnknode const procfs_fdlnk_template = {
	.ln_node = {
		.fn_file = {
			MFILE_INIT_mf_refcnt(1), /* Return value of creator */
			MFILE_INIT_mf_ops(&procfs_perproc_fdlnk_ops.lno_node.no_file),
			MFILE_INIT_mf_lock,
			MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
			MFILE_INIT_mf_initdone,
			MFILE_INIT_mf_lockops,
			MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
			MFILE_INIT_mf_blockshift(PAGESHIFT),
			MFILE_INIT_mf_flags(MFILE_F_NOATIME | MFILE_F_NOMTIME |
			                    MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |
			                    MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE |
			                    MFILE_FN_FLEETING),
			MFILE_INIT_mf_trunclock,
			MFILE_INIT_mf_filesize(0),
			MFILE_INIT_mf_atime(0, 0),
			MFILE_INIT_mf_mtime(0, 0),
			MFILE_INIT_mf_ctime(0, 0),
		},
		FNODE_INIT_fn_nlink(1),
		FNODE_INIT_fn_mode(S_IFLNK | 0777),
		FNODE_INIT_fn_uid(0),
		FNODE_INIT_fn_gid(0),
		FNODE_INIT_fn_ino(0),
		FNODE_INIT_fn_super(&procfs_super),
		FNODE_INIT_fn_changed,
		FNODE_INIT_fn_supent_EX({ NULL, FSUPER_NODES_DELETED }),
		FNODE_INIT_fn_allnodes,
	},
};


/* Directory entry structure for statically defined /proc/[pid]/... files. */
struct procfs_perproc_dirent {
	struct fnode_ops const   *ppd_fops;    /* [1..1][const] File-node operators. */
	mode_t ppd_mod;                        /* [const] File-mode for the pointed-to file. */
#if 0                                      /* Doesn't work because g++ is lazy */
	struct fdirent            ppd_ent;     /* Underlying directory entry. */
#else
	WEAK refcnt_t             ppd_refcnt;  /* Reference counter. */
	struct fdirent_ops const *ppd_ops;     /* [1..1][const] Operators. */
	ino_t                     ppd_ino;     /* [valid_if(false)] */
	uintptr_t                 ppd_hash;    /* [const][== fdirent_hash(fd_name, fd_namelen)] Hash of this directory entry. */
	u16                       ppd_namelen; /* [const][!0] Length of the directory entry name (in characters). */
	unsigned char             ppd_type;    /* [const] Directory entry type (one of `DT_*') */
	COMPILER_FLEXIBLE_ARRAY(/*utf-8*/ char, ppd_name); /* [const][ppd_namelen] Directory entry name. (NUL-terminated) */
#endif
};

/* Assert that fields of `struct procfs_perproc_dirent' are binary compatible with `fdirent' starting at `ppd_refcnt' */
static_assert((offsetof(struct procfs_perproc_dirent, ppd_refcnt) - offsetof(struct procfs_perproc_dirent, ppd_refcnt)) == offsetof(struct fdirent, fd_refcnt));
static_assert((offsetof(struct procfs_perproc_dirent, ppd_ops) - offsetof(struct procfs_perproc_dirent, ppd_refcnt)) == offsetof(struct fdirent, fd_ops));
static_assert((offsetof(struct procfs_perproc_dirent, ppd_ino) - offsetof(struct procfs_perproc_dirent, ppd_refcnt)) == offsetof(struct fdirent, fd_ino));
static_assert((offsetof(struct procfs_perproc_dirent, ppd_hash) - offsetof(struct procfs_perproc_dirent, ppd_refcnt)) == offsetof(struct fdirent, fd_hash));
static_assert((offsetof(struct procfs_perproc_dirent, ppd_namelen) - offsetof(struct procfs_perproc_dirent, ppd_refcnt)) == offsetof(struct fdirent, fd_namelen));
static_assert((offsetof(struct procfs_perproc_dirent, ppd_type) - offsetof(struct procfs_perproc_dirent, ppd_refcnt)) == offsetof(struct fdirent, fd_type));
static_assert((offsetof(struct procfs_perproc_dirent, ppd_name) - offsetof(struct procfs_perproc_dirent, ppd_refcnt)) == offsetof(struct fdirent, fd_name));

#define fdirent_asperproc(self)           container_of(&(self)->fd_refcnt, struct procfs_perproc_dirent, ppd_refcnt)
#define procfs_perproc_dirent_asent(self) ((struct fdirent *)&(self)->ppd_refcnt)


PRIVATE WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
procfs_perproc_dirent_v_opennode_reg(struct fdirent *__restrict self,
                                     struct fdirnode *__restrict dir) {
	struct procfs_perproc_dirent *me = fdirent_asperproc(self);
	REF struct fnode *result;
	result = (REF struct fnode *)kmalloc(sizeof(struct fnode), GFP_NORMAL);
	result = (REF struct fnode *)memcpy(result, &procfs_perproc_reg_template, sizeof(struct fnode));

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
	result = (REF struct fnode *)kmalloc(sizeof(struct fnode), GFP_NORMAL);
	result = (REF struct fnode *)memcpy(result, &procfs_perproc_nomap_template, sizeof(struct fnode));

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
	.fdo_destroy  = (void(KCALL *)(struct fdirent *__restrict))(void *)(uintptr_t)-1,
	.fdo_opennode = &procfs_perproc_dirent_v_opennode_reg,
	.fdo_getino   = &procfs_perproc_dirent_v_getino,
};
PRIVATE struct fdirent_ops const procfs_perproc_dirent_ops_nomap = {
	/* `struct procfs_perproc_dirent'-objects are only allocated statically, so destroy must never be called. */
	.fdo_destroy  = (void(KCALL *)(struct fdirent *__restrict))(void *)(uintptr_t)-1,
	.fdo_opennode = &procfs_perproc_dirent_v_opennode_nomap,
	.fdo_getino   = &procfs_perproc_dirent_v_getino,
};

/* Return the set of directory entry operators used for per-process files of `dt_type' (one of `DT_*') */
#define procfs_perproc_dirent_ops_for(dt_type)             \
	((dt_type) == S_IFREG ? &procfs_perproc_dirent_ops_reg \
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
#define __DEFINE_DIRENT(symbol_name, name, type, perm, fnode_ops_ptr, hash) \
	PRIVATE struct procfs_perproc_dirent symbol_name = {                    \
		.ppd_fops    = (struct fnode_ops *)(fnode_ops_ptr),                 \
		.ppd_mod     = DTTOIF(type) | (perm),                               \
		.ppd_refcnt  = 2, /* +1: symbol_name, +1: DIRECTORY_ENTRY_LIST */   \
		.ppd_ops     = procfs_perproc_dirent_ops_for(type),                 \
		.ppd_ino     = _INVALID_INO, /* Mustn't be used */                  \
		.ppd_hash    = hash,                                                \
		.ppd_namelen = COMPILER_STRLEN(name),                               \
		.ppd_type    = type,                                                \
		/* .ppd_name = */ name                                              \
	};
#define ROOTENT(name, type, perm, fnode_ops_ptr, hash) \
	__DEFINE_DIRENT(PP_CAT2(perproc_root_dirent_, __LINE__), name, type, perm, fnode_ops_ptr, hash)
#define MKDIR_ENT(name, type, perm, fnode_ops_ptr, hash) \
	__DEFINE_DIRENT(PP_CAT2(perproc_dirent_, __LINE__), name, type, perm, fnode_ops_ptr, hash)
#include "perproc.def"
#undef __DEFINE_DIRENT


/* Define sub-directory tables. */
#define MKDIR_BEGIN(ops_symbol_name) \
	PRIVATE REF struct fdirent *const __##ops_symbol_name##_files[] = {
#define MKDIR_ENT(name, type, perm, fnode_ops_ptr, hash) \
		procfs_perproc_dirent_asent(&PP_CAT2(perproc_dirent_, __LINE__)),
#define MKDIR_END \
	};
#include "perproc.def"


/* Define operator tables. */
INTDEF struct mfile_stream_ops const procfs_perproc_printnode_v_stream_ops;
INTDEF struct mfile_stream_ops const procfs_perproc_lnknode_v_stream_ops;
INTDEF NONNULL((1)) void KCALL
procfs_perproc_printnode_v_stat(struct mfile *__restrict self,
                                USER CHECKED struct stat *result)
		THROWS(...);

#define MKDIR_BEGIN(ops_symbol_name)                                                   \
	PRIVATE WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL                          \
	__##ops_symbol_name##_v_lookup(struct fdirnode *__restrict UNUSED(self),           \
	                               struct flookup_info *__restrict info) {             \
		return procfs_perproc_lookup_impl(__##ops_symbol_name##_files,                 \
		                                  COMPILER_LENOF(__##ops_symbol_name##_files), \
		                                  info);                                       \
	}                                                                                  \
	PRIVATE NONNULL((1)) void KCALL                                                    \
	__##ops_symbol_name##_v_enum(struct fdirenum *__restrict result) {                 \
		procfs_perproc_enum_impl(__##ops_symbol_name##_files,                          \
		                         COMPILER_LENOF(__##ops_symbol_name##_files),          \
		                         result);                                              \
	}                                                                                  \
	INTERN_CONST struct fdirnode_ops const ops_symbol_name = {                         \
		.dno_node = {                                                                  \
			.no_file = {                                                               \
				.mo_destroy = &procfs_perproc_dir_v_destroy,                           \
				.mo_changed = &procfs_perproc_dir_v_changed,                           \
				.mo_stream  = &procfs_perproc_dir_v_stream_ops,                        \
			},                                                                         \
			.no_free   = &procfs_perproc_dir_v_free,                                   \
			.no_wrattr = &procfs_perproc_dir_v_wrattr,                                 \
		},                                                                             \
		.dno_lookup = &__##ops_symbol_name##_v_lookup,                                 \
		.dno_enum   = &__##ops_symbol_name##_v_enum,                                   \
	};
#define MKREG_RO(ops_symbol_name, printer)                               \
	INTDEF NONNULL((1, 2)) void KCALL                                    \
	printer(struct printnode *__restrict self,                           \
	        pformatprinter printer_, void *arg,                          \
	        size_t offset_hint);                                         \
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
		}},                                                              \
		.pno_print = &printer,                                           \
	};
#define MKREG_RW(ops_symbol_name, printer, writer)                             \
	INTDEF NONNULL((1, 2)) void KCALL                                          \
	printer(struct printnode *__restrict self,                                 \
	        pformatprinter printer_, void *arg,                                \
	        size_t offset_hint);                                               \
	INTDEF WUNUSED NONNULL((1)) size_t KCALL                                   \
	writer(struct mfile *__restrict self, USER CHECKED void const *src,        \
	       size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);           \
	PRIVATE struct mfile_stream_ops const __##ops_symbol_name##_stream_ops = { \
		.mso_pread  = &printnode_v_pread,                                      \
		.mso_preadv = &printnode_v_preadv,                                     \
		.mso_pwrite = &writer,                                                 \
		.mso_stat   = &procfs_perproc_printnode_v_stat,                        \
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
		}},                                                                    \
		.pno_print = &printer,                                                 \
	};
#define MKLNK(ops_symbol_name, readlink)                            \
	INTDEF WUNUSED NONNULL((1)) size_t KCALL                        \
	readlink(struct flnknode *__restrict self,                      \
	         USER CHECKED /*utf-8*/ char *buf,                      \
	         size_t bufsize)                                        \
			THROWS(E_SEGFAULT, E_IOERROR, ...);                     \
	INTERN_CONST struct flnknode_ops const ops_symbol_name = {      \
		.lno_node = {                                               \
			.no_file = {                                            \
				.mo_destroy = &procfs_perproc_v_destroy,            \
				.mo_changed = &procfs_perproc_v_changed,            \
				.mo_stream  = &procfs_perproc_lnknode_v_stream_ops, \
			},                                                      \
			.no_free   = &procfs_perproc_v_free,                    \
			.no_wrattr = &procfs_perproc_v_wrattr,                  \
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
	                                  COMPILER_LENOF(procfs_perproc_root_files),
	                                  info);
}

PRIVATE NONNULL((1)) void KCALL
procfs_perproc_root_v_enum(struct fdirenum *__restrict result) {
	procfs_perproc_enum_impl(procfs_perproc_root_files,
	                         COMPILER_LENOF(procfs_perproc_root_files),
	                         result);
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
	if (wanted_type == HANDLE_TYPE_TASK)
		return incref(me->dn_node.fn_fsdata);
	return NULL;
}

PRIVATE struct mfile_stream_ops const procfs_perproc_root_v_stream_ops = {
	.mso_open  = &fdirnode_v_open,
	.mso_stat  = &procfs_perproc_dir_v_stat,
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
		/* TODO: Operators to override `uid' and `gid', as are used for permission  checks,
		 *       and are exposed to user-space via `stat' (we want to use cred_* values for
		 *       these)
		 * The same also goes for all of the other operator tables above! (grep this file for `no_wrattr') */
	},
	.dno_lookup = &procfs_perproc_root_v_lookup,
	.dno_enum   = &procfs_perproc_root_v_enum,
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
	result = (REF struct fnode *)kmalloc(sizeof(struct fnode), GFP_NORMAL);
	result = (REF struct fnode *)memcpy(result, &procfs_perproc_nomap_template, sizeof(struct fnode));

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

DECL_END

#endif /* !GUARD_MODPROCFS_PERPROC_C */
