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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_CONSTDIR_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_CONSTDIR_H 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/dirnode.h>
#include <kernel/types.h>

/*
 * Constant directories  are  special  read-only  folders  that
 * contain a fixed set of statically defined directory entries.
 *
 * These types of folders are mainly used for singleton
 * config  paths  in procfs,  like `/proc/sys/kernel/'.
 *
 */

#ifdef __CC__
DECL_BEGIN

struct fdirent_ops;
struct constdirent {
	REF struct fnode                       *cd_node;     /* [1..1][const] File pointed-to by this directory entry. */
#if __ALIGNOF_POS_T__ > __ALIGNOF_POINTER__
	byte_t __cd_pad[__ALIGNOF_POS_T__ - __ALIGNOF_POINTER__];
#define CONSTDIRENT_PRIVATE_INIT_PAD_ {},
#else /* __ALIGNOF_POS_T__ > __ALIGNOF_POINTER__ */
#define CONSTDIRENT_PRIVATE_INIT_PAD_ /* nothing */
#endif /* __ALIGNOF_POS_T__ <= __ALIGNOF_POINTER__ */
	/* Below fields are  binary-compatible with  `struct fdirent'
	 * I wish I could simply put a field `struct fdirent cd_ent',
	 * but g++ programmers got lazy and decided to disallow brace
	 * init in such a situation:
	 * "initialization of flexible array member in a nested context" */
	WEAK refcnt_t                           cd_refcnt;   /* Reference counter. */
	struct fdirent_ops const               *cd_ops;      /* [1..1][const] Operators. */
	ino_t                                   cd_ino;      /* [const][== cd_node->fn_ino] INode number of this directory entry. */
	uintptr_t                               cd_hash;     /* [const][== fdirent_hash(fd_name, fd_namelen)] Hash of this directory entry. */
	u16                                     cd_namelen;  /* [const][!0] Length of the directory entry name (in characters). */
	unsigned char                           cd_type;     /* [const] Directory entry type (one of `DT_*') */
	COMPILER_FLEXIBLE_ARRAY(/*utf-8*/ char, cd_name);    /* [const][fd_namelen] Directory entry name. (NUL-terminated) */
};

/* Default alloc/free functions for `struct constdirent' */
#define _constdirent_alloc(namelen)                                                  \
	((struct constdirent *)kmalloc(__builtin_offsetof(struct constdirent, cd_name) + \
	                               ((namelen) + 1) * sizeof(char),                   \
	                               GFP_NORMAL))
#define _constdirent_free(self) kfree(self)


/* Static initializer for `struct constdirent'
 * NOTE: `fd_hash' can be auto-generated via `libgen.fdirent_hash' */
#define CONSTDIRENT_INIT(node, fd_ino, fd_type, fd_name, fd_hash) \
	{ node, CONSTDIRENT_PRIVATE_INIT_PAD_ 1, &constdirent_ops,    \
	  fd_ino, fd_hash, (sizeof(fd_name) / sizeof(char)) - 1,      \
	  fd_type, fd_name }

/* Operators used to facilitate `struct constdirent' */
DATDEF struct fdirent_ops const constdirent_ops;
FUNDEF NOBLOCK NONNULL((1)) void /* decref(me->cd_node) + _constdirent_free(me) */
NOTHROW(KCALL constdirent_v_destroy)(struct fdirent *__restrict self);
FUNDEF WUNUSED NONNULL((1, 2)) REF struct fnode *
NOTHROW(KCALL constdirent_v_opennode)(struct fdirent *__restrict self, /* return incref(me->cd_node); */
                                      struct fdirnode *__restrict dir);


/* Convert between `struct fdirent' and `struct constdirent' */
#define fdirent_asconst(self)   COMPILER_CONTAINER_OF(&(self)->fd_refcnt, struct constdirent, cd_refcnt)
#define constdirent_asent(self) ((struct fdirent *)&(self)->cd_refcnt)


/* Enumeration of `struct constdir' */
struct constdirenum
#ifdef __cplusplus
    : fdirenum                        /* Underlying enumerator */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct fdirenum        cde_enum;  /* Underlying enumerator */
#endif /* !__cplusplus */
	size_t                 cde_index; /* [lock(ATOMIC)] Index into `cde_entv'; `>= cde_entc' is used to indicate EOF. */
	size_t                 cde_entc;  /* [const] # of directory entries to enumerate */
	struct fdirent *const *cde_entv;  /* [1..1][const][0..cde_entc][const] Directory entries. */
};

/* Operators for `struct constdirenum' */
DATDEF struct fdirenum_ops const constdirenum_ops;
FUNDEF NOBLOCK NONNULL((1)) void /* no-op */
NOTHROW(KCALL constdirenum_v_fini)(struct fdirenum *__restrict self);
FUNDEF NONNULL((1)) size_t KCALL
constdirenum_v_readdir(struct fdirenum *__restrict self, NCX struct dirent *buf,
                       size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode)
		THROWS(E_SEGFAULT, ...);
FUNDEF NONNULL((1)) pos_t KCALL
constdirenum_v_seekdir(struct fdirenum *__restrict self,
                       off_t offset, unsigned int whence)
		THROWS(E_OVERFLOW, E_INVALID_ARGUMENT_UNKNOWN_COMMAND);



struct constdir
#ifndef __WANT_FS_INLINE_STRUCTURES
    : fdirnode                        /* Underlying directory */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct fdirnode        cd_dir;   /* Underlying file-node */
#define _constdir_asdir(x) &(x)->cd_dir
#define _constdir_dir_     cd_dir.
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _constdir_asdir(x) x
#define _constdir_dir_     /* nothing */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
	size_t                                        cd_entc;  /* [const] # of files in this directory */
	COMPILER_FLEXIBLE_ARRAY(REF struct fdirent *, cd_entv); /* [1..1][const][0..cd_entc] Files in this directory.
	                                                         * Sorted  by-name,  lexicographically   ascendingly. */
};

/* Helper macros */
#define fdirnode_asconst(self)  ((struct constdir *)(self))
#define fnode_asconstdir(self)  fdirnode_asconst(fnode_asdir(self))
#define mfile_asconstdir(self)  fdirnode_asconst(mfile_asdir(self))
#define fsuper_asconstdir(self) fdirnode_asconst(&(self)->fs_root)


/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_constdir_dir_ _fdirnode_node_ _fnode_file_ mf_atime
 *  - self->_constdir_dir_ _fdirnode_node_ _fnode_file_ mf_mtime
 *  - self->_constdir_dir_ _fdirnode_node_ _fnode_file_ mf_ctime
 *  - self->_constdir_dir_ _fdirnode_node_ _fnode_file_ mf_btime
 *  - self->_constdir_dir_ _fdirnode_node_ fn_uid
 *  - self->_constdir_dir_ _fdirnode_node_ fn_gid
 *  - self->_constdir_dir_ _fdirnode_node_ fn_allnodes
 *  - self->_constdir_dir_ _fdirnode_node_ fn_supent
 *  - self->_constdir_dir_ _fdirnode_node_ fn_nlink
 *  - self->_constdir_dir_ _fdirnode_node_ fn_ino
 *  - self->_constdir_dir_ _fdirnode_node_ fn_mode (with something or'd with S_IFDIR)
 *  - self->cd_entc
 *  - self->cd_entv[*]
 * @param: struct fdirnode     *self:  Const directory node to initialize.
 * @param: struct fdirnode_ops *ops:   Const directory operators. (usually `constdir_ops')
 * @param: struct fsuper       *super: Associated superblock. */
#define _constdir_init(self, ops, super)                                                                               \
	(_fdirnode_assert_ops_(ops) _fnode_init_common(_fdirnode_asnode(self)),                                            \
	 (self)->_fdirnode_node_ _fnode_file_ mf_parts             = MFILE_PARTS_ANONYMOUS,                                \
	 (self)->_fdirnode_node_ _fnode_file_ mf_changed.slh_first = MFILE_PARTS_ANONYMOUS,                                \
	 (self)->_fdirnode_node_ _fnode_file_ mf_flags = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_flags &          \
	                                                 (MFILE_F_DELETED | MFILE_F_PERSISTENT |                           \
	                                                  MFILE_F_READONLY | MFILE_F_NOATIME |                             \
	                                                  MFILE_F_NOMTIME | MFILE_F_NOUSRMMAP |                            \
	                                                  MFILE_F_NOUSRIO | MFILE_F_FIXEDFILESIZE),                        \
	 __hybrid_assert(((self)->_fdirnode_node_ _fnode_file_ mf_flags &                                                  \
	                  (MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_FIXEDFILESIZE)) ==                                \
	                 (MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_FIXEDFILESIZE)),                                   \
	 (self)->_fdirnode_node_ _fnode_file_ mf_ops        = &(ops)->dno_node.no_file,                                    \
	 (self)->_fdirnode_node_ _fnode_file_ mf_part_amask = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_part_amask, \
	 (self)->_fdirnode_node_ _fnode_file_ mf_blockshift = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_blockshift, \
	 (self)->_fdirnode_node_ _fnode_file_ mf_iobashift  = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_iobashift,  \
	 atomic64_init(&(self)->_fdirnode_node_ _fnode_file_ mf_filesize, (uint64_t)-1),                                   \
	 (self)->_fdirnode_node_ fn_super = incref(super))
#define _constdir_cinit(self, ops, super)                                                                              \
	(_fdirnode_assert_ops_(ops) _fnode_cinit_common(_fdirnode_asnode(self)),                                           \
	 (self)->_fdirnode_node_ _fnode_file_ mf_parts             = MFILE_PARTS_ANONYMOUS,                                \
	 (self)->_fdirnode_node_ _fnode_file_ mf_changed.slh_first = MFILE_PARTS_ANONYMOUS,                                \
	 (self)->_fdirnode_node_ _fnode_file_ mf_flags = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_flags &          \
	                                                 (MFILE_F_DELETED | MFILE_F_PERSISTENT |                           \
	                                                  MFILE_F_READONLY | MFILE_F_NOATIME |                             \
	                                                  MFILE_F_NOMTIME | MFILE_F_NOUSRMMAP |                            \
	                                                  MFILE_F_NOUSRIO | MFILE_F_FIXEDFILESIZE),                        \
	 __hybrid_assert(((self)->_fdirnode_node_ _fnode_file_ mf_flags &                                                  \
	                  (MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_FIXEDFILESIZE)) ==                                \
	                 (MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_FIXEDFILESIZE)),                                   \
	 (self)->_fdirnode_node_ _fnode_file_ mf_ops        = &(ops)->dno_node.no_file,                                    \
	 (self)->_fdirnode_node_ _fnode_file_ mf_part_amask = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_part_amask, \
	 (self)->_fdirnode_node_ _fnode_file_ mf_blockshift = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_blockshift, \
	 (self)->_fdirnode_node_ _fnode_file_ mf_iobashift  = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_iobashift,  \
	 atomic64_cinit(&(self)->_fdirnode_node_ _fnode_file_ mf_filesize, (uint64_t)-1),                                  \
	 (self)->_fdirnode_node_ fn_super = incref(super))
/* Finalize a partially initialized `struct fdirnode' (as initialized by `_fdirnode_init()') */
#define _fdirnode_fini(self) \
	(decref_nokill((self)->_fdirnode_node_ fn_super))



/* Default operators for `struct constdir' */
FUNDEF WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
constdir_v_lookup(struct fdirnode *__restrict self,
                  struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT);
FUNDEF NONNULL((1)) void
NOTHROW(KCALL constdir_v_enum)(struct fdirenum *__restrict result);
#define constdir_v_enumsz     sizeof(struct constdirenum)
#define constdir_v_destroy    fdirnode_v_destroy
#define constdir_v_changed    fdirnode_v_changed
#define constdir_v_open       fdirnode_v_open
#define constdir_v_stat       fdirnode_v_stat
#define constdir_v_stream_ops fdirnode_v_stream_ops
#define constdir_v_wrattr     fnode_v_wrattr_noop
/* Default operators for `struct constdir' (using the functions above) */
DATDEF struct fdirnode_ops const constdir_ops;


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_CONSTDIR_H */
