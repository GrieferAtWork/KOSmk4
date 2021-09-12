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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_FDIRNODE_LINEAR_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_FDIRNODE_LINEAR_H 1

#include <kernel/compiler.h>

#if 1
#ifndef CONFIG_USE_NEW_FS
#include <fs/node.h>
#else /* !CONFIG_USE_NEW_FS */
#include <kernel/fs/fdirent.h>
#include <kernel/fs/fdirnode.h>
#include <kernel/types.h>
#include <sched/atomic64.h>
#include <sched/shared_rwlock.h>

#include <hybrid/sync/atomic-rwlock.h>

#ifdef __CC__
DECL_BEGIN

/* Pre-defined directory access helper node for linear directories.
 * A linear directory is one that simply divides the directory data
 * into chunks of either fixed- or variable-length segments,  where
 * one  (or  multiple)  such  segments   make  up  a  file   entry.
 * As  such, linear directories have the following characteristics:
 *   - Linear time search
 *   - Linearly ordered directory entry enumeration
 *   - In-stream  positions of files do not change, unless a file is
 *     deleted, or a new file is created. In both cases, the in-file
 *     positions of any unrelated directory entry is not altered. */

struct flindirnode;
struct flindirent;


struct flindirent {
	SLIST_ENTRY(flindirent) fld_byname; /* [0..1][lock(:ldd_flock)] Next dirent with a similar hash. */
	TAILQ_ENTRY(flindirent) fld_bypos;  /* [0..1][lock(:ldd_flock)] List of entries by position. */
	pos_t                   fld_minpos; /* [lock(:ldd_flock)] Absolute in-directory position of this entry. */
	pos_t                   fld_maxpos; /* [lock(:ldd_flock)] Absolute end position of this entry. */
	uintptr_t               fld_hash;   /* [const] Hash of this directory entry. (s.a. `fdirent_hash()') */
	struct fdirent          fld_ent;    /* The underlying directory entry. */
};

#define flindirent_from_fdirent(self) COMPILER_CONTAINER_OF(self, struct flindirent, fld_ent)
#define flindirent_destroy(self)      fdirent_destroy(&(self)->fld_ent)
DEFINE_REFCOUNT_FUNCTIONS(struct flindirent, fld_ent.fd_refcnt, flindirent_destroy)


#ifndef __flindirent_slist_defined
#define __flindirent_slist_defined
SLIST_HEAD(flindirent_slist, flindirent);
#endif /* !__flindirent_slist_defined */

#ifndef __flindirent_tailq_defined
#define __flindirent_tailq_defined
TAILQ_HEAD(flindirent_tailq, flindirent);
#endif /* !__flindirent_tailq_defined */



struct flinmkent_info {
	union {
		struct {
			CHECKED USER /*utf-8*/ char const *lmk_name;    /* [?..lmk_namelen][in] Name for the new file. */
			uintptr_t                          lmk_hash;    /* [in] Hash for `lmk_name' (s.a. `fdirent_hash()') */
			u16                                lmk_namelen; /* [in] Length of `lmk_name' */
			u16                               _lmk_pad;     /* ... */
			u16                               _lmk_pad2;    /* ... */
		};
		struct flookup_info            lmk_lookup_info;     /* [in] Lookup info for the new file being created. */
	};
	REF struct flindirent             *lmk_dent; /* [1..1][out] Directory entry for the new file (s.a. `dno_lookup') */
	struct fnode                      *lmk_node; /* [1..1][in] The file-node for which the entry should be created. */
};

struct flindirnode_ops {
#define _flindirnode_ops_firstfield(prefix)  _fdirnode_ops_firstfield(prefix)
#define flindirnode_ops_as_fdirnode_ops(ops) ((struct fdirnode_ops const *)&(ops)->_fdirnode_ops_firstfield(ldno_))
#define flindirnode_ops_as_fnode_ops(ops)    ((struct fnode_ops const *)&(ops)->_fnode_ops_firstfield(ldno_))
#define flindirnode_ops_as_mfile_ops(ops)    ((struct mfile_ops const *)&(ops)->_mfile_ops_firstfield(ldno_))
#define FLINDIRNODE_OPS_FIELDS(prefix, T)                                             \
	FDIRNODE_OPS_FIELDS(prefix, T);                                                   \
	                                                                                  \
	/* [1..1][lock(READ(ldd_flock))]                                                  \
	 * Read a directory entry from a given position within the directory file.        \
	 * When   returning   non-NULL,    this   function   should    initialize:        \
	 *   - return->fld_byname         = UNDEF;                                        \
	 *   - return->fld_bypos          = UNDEF;                                        \
	 *   - return->fld_minpos         = ... >= pos;                                   \
	 *   - return->fld_maxpos         = ... >= fld_minpos;                            \
	 *   - return->fld_hash           = fdirent_hashof(&return->fld_ent);             \
	 *   - return->fld_ent.fd_refcnt  = UNDEF;                                        \
	 *   - return->fld_ent.fd_ops     = ...;                                          \
	 *   - return->fld_ent.fd_ino     = ...;                                          \
	 *   - return->fld_ent.fd_namelen = ...;                                          \
	 *   - return->fld_ent.fd_type    = ...;                                          \
	 *   - return->fld_ent.fd_name    = ...;                                          \
	 * @param: pos:   The starting position from which to search for the next entry.  \
	 * @return: * :   The file entry that was read.                                   \
	 * @return: NULL: The end of the directory file has been reached. */              \
	WUNUSED NONNULL((1)) REF struct flindirent *                                      \
	(KCALL *prefix##linreaddir)(T *__restrict self, pos_t pos);                       \
	                                                                                  \
	/* [0..1][lock(WRITE(ldd_flock))]                                                 \
	 * Write to the directory file that a given `entry' has been deleted.             \
	 *   - entry->fld_byname         = UNDEF;                                         \
	 *   - entry->fld_bypos          = UNDEF;                                         \
	 *   - entry->fld_minpos         = ...;                                           \
	 *   - entry->fld_maxpos         = ...;                                           \
	 *   - entry->fld_hash           = fdirent_hashof(&entry->fld_ent);               \
	 *   - entry->fld_ent.fd_refcnt  = UNDEF;                                         \
	 *   - entry->fld_ent.fd_ops     = ...;                                           \
	 *   - entry->fld_ent.fd_ino     = ...;                                           \
	 *   - entry->fld_ent.fd_namelen = ...;                                           \
	 *   - entry->fld_ent.fd_type    = ...;                                           \
	 *   - entry->fld_ent.fd_name    = ...; */                                        \
	NONNULL((1, 2)) void                                                              \
	(KCALL *prefix##linrment)(T *__restrict self,                                     \
	                          struct flindirent const *__restrict entry);             \
	                                                                                  \
	/* [0..1][lock(WRITE(ldd_flock))]                                                 \
	 * Create a new on-disk directory entry for some given file-node.                 \
	 *   - info->lmk_name     = [in:const];                                           \
	 *   - info->lmk_hash     = [in:const];                                           \
	 *   - info->lmk_namelen  = [in:const];                                           \
	 *   - info->lmk_dent     = [out];            // Set to NULL to indicate reserved \
	 *                                            // directory space.  In this  case, \
	 *                                            // `return' if # of reserved  bytes \
	 *                                            // starting at `pos'                \
	 * @param: pos:      The position where the new entry should go.                  \
	 * @param: size:     The max # of bytes which may be                              \
	 * @return: > size:  The  required  amount of  free  directory-file space.        \
	 *                   In this case, all out-fields of `info' are undefined.        \
	 * @return: <= size: The total amount of required file space.                     \
	 *                   When `info->lmk_dent == NULL',  */                           \
	WUNUSED NONNULL((1, 2)) size_t                                                    \
	(KCALL *prefix##linmkent)(T *__restrict self,                                     \
	                          struct flinmkent_info *__restrict info,                 \
	                          pos_t pos, size_t size);                                \
	                                                                                  \
	/* [0..1][lock(WRITE(ldd_flock))]                                                 \
	 * Same as `ldno_linmkent', but create a new file rather than link an existing.   \
	 * This function will not be called for for the purpose of hard-linking,  which   \
	 * is handled via  `ldno_linmkent' (with  respect to  `f_super->fs_nlink_max'),   \
	 * meaning that this is the function used  to create new files in a  directory,   \
	 * as well as allocating their fnode objects.                                     \
	 *   - info->mkf_name     = [in:const];                                           \
	 *   - info->mkf_hash     = [in:const];                                           \
	 *   - info->mkf_namelen  = [in:const];                                           \
	 *   - info->mkf_flags    = [in:const,undef]; // NOCASE and EXISTS are handled    \
	 *                                            // by the caller!                   \
	 *   - info->mkf_dent     = [out];            // Set to NULL to indicate reserved \
	 *                                            // directory space.  In this  case, \
	 *                                            // `return' if # of reserved  bytes \
	 *                                            // starting at `pos'                \
	 *   - info->mkf_fmode    = [in:const];                                           \
	 *   - info->mkf_rnode    = [out];            // Already added to tree of nodes   \
	 *   - info->mkf_creat.*  = [in:const];                                           \
	 * @param: pos:      The position where the new entry should go.                  \
	 * @param: size:     The max # of bytes which may be                              \
	 * @return: 0:       Unsupported file type/operation (`info->mkf_fmode')          \
	 *                   Same   as   not    implementing   this    operator.          \
	 *                   Caller will throw `E_FSERROR_UNSUPPORTED_OPERATION'          \
	 * @return: > size:  The  required  amount of  free  directory-file space.        \
	 *                   In this case, all out-fields of `info' are undefined.        \
	 * @return: <= size: The total amount of required file space.                     \
	 *                   When `info->mkf_dent == NULL',  */                           \
	WUNUSED NONNULL((1, 3)) size_t                                                    \
	(KCALL *prefix##linmkfil)(T *__restrict self, mode_t mode,                        \
	                          struct fcreatfile_info const *__restrict info);


	/* Operators... */
	FLINDIRNODE_OPS_FIELDS(ldno_, struct flindirnode);
};

struct flindirenum;
struct flindirenum {
	struct fdirenum_ops const *lde_ops; /* [1..1][const] Operators. */
	REF struct flindirnode    *lde_dir; /* [1..1][const] Source directory.
	                                     * Note that this  field also  holds a  reference
	                                     * to  the `ldd_norehash' counter, such that said
	                                     * counter is decremented when this enumerator is
	                                     * destroyed. */
	atomic64_t                 lde_pos; /* Lower bound for the next-to-be-read entry's `fld_minpos' */
	WEAK struct flindirent    *lde_ent; /* [0..1][lock(lde_dir->ldd_flock)]
	                                     * [lock(WRITE_NULL(ATOMIC))] // To write NULL, you don't need a the lock!
	                                     * Cache for the next entry to-be read. NULL if
	                                     * the next entry  was deleted  before it was  read, or  if
	                                     * the  next  entry  has   yet  to  be  loaded   from-disk.
	                                     * In either case, `lde_pos' must be used to in conjunction
	                                     * with `ldno_linreaddir', unless `ldd_loaded' */
	LIST_ENTRY(flindirenum)    lde_all; /* [0..1][lock(lde_dir->_MFILE_F_SMP_TSLOCK)]
	                                     * List of all open directory enumerators for `lde_dir' */
};

#ifndef __flindirenum_list_defined
#define __flindirenum_list_defined
LIST_HEAD(flindirenum_list, flindirenum);
#endif /* !__flindirenum_list_defined */


struct flindirbucket {
	struct flindirent_slist ldb_entires; /* [0..n] List of directory entries with a similar hash. */
};

struct flindirdat {
	struct flindirenum_list     ldd_enum;       /* [lock(_MFILE_F_SMP_TSLOCK)] List of all open directory enumerators */
	struct shared_rwlock        ldd_flock;      /* Lock for synchronizing changes to the backing directory file. */
	struct REF flindirent_tailq ldd_bypos;      /* [lock(ldd_flock)] List of entries (sorted by position). */
	size_t                      ldd_byname_siz; /* [lock(ldd_flock)] # of entries within `ldd_byname_tab' */
	size_t                      ldd_byname_msk; /* [lock(ldd_flock)] Hash-mask of `ldd_byname_tab' */
	struct flindirbucket       *ldd_byname_tab; /* [0..ldd_byname_msk][owned][lock(ldd_flock)] By-name hash-table. */
	bool                        ldd_loaded;     /* [lock(WRITE_ONCE(WRITE(ldd_flock)))] Set to `true' once `ldno_linreaddir' returns EOF. */
};

/* Initialize the given linear directory controller. */
#define flindirdat_init(self)                \
	(SLIST_INIT(&(self)->ldd_enum),          \
	 shared_rwlock_init(&(self)->ldd_flock), \
	 TAILQ_INIT(&(self)->ldd_bypos),         \
	 (self)->ldd_byname_siz = 0,             \
	 (self)->ldd_byname_msk = 0,             \
	 (self)->ldd_byname_tab = __NULLPTR,     \
	 (self)->ldd_loaded     = 0)
#define flindirdat_cinit(self)                             \
	(__hybrid_assert(SLIST_EMPTY(&(self)->ldd_enum)),      \
	 shared_rwlock_cinit(&(self)->ldd_flock),              \
	 TAILQ_INIT(&(self)->ldd_bypos),                       \
	 __hybrid_assert((self)->ldd_byname_siz == 0),         \
	 __hybrid_assert((self)->ldd_byname_msk == 0),         \
	 __hybrid_assert((self)->ldd_byname_tab == __NULLPTR), \
	 __hybrid_assert((self)->ldd_loaded == 0))

/* Finalize the given linear directory controller. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL flindirdat_fini)(struct flindirdat *__restrict self);



struct flindirnode
#ifdef __cplusplus
    : fdirnode                       /* Underlying directory-node */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct fdirnode      ldn_dir;    /* Underlying directory-node */
#endif /* !__cplusplus */
	struct flindirdat    ldn_dat;    /* Linear directory data. */
};

/* Initialize common+basic fields. The caller must still initialize:
 *  - mf_atime, mf_mtime, mf_ctime
 *  - fn_allnodes, fn_supent, fn_ino, fn_mode (with something or'd with S_IFDIR)
 * @param: struct flindirnode     *self:   Directory node to initialize.
 * @param: struct flindirnode_ops *ops:    Directory operators.
 * @param: struct fdirnode        *parent: Parent directory. */
#define _flindirnode_init(self, ops, parent) \
	(_fdirnode_init(self, flindirnode_ops_as_fdirnode_ops(ops), parent), flindirdat_init(&(self)->ldn_dat))
#define _flindirnode_cinit(self, ops, parent) \
	(_fdirnode_cinit(self, flindirnode_ops_as_fdirnode_ops(ops), parent), flindirdat_cinit(&(self)->ldn_dat))
/* Finalize a partially initialized `struct flindirnode' (as initialized by `_flindirnode_init()') */
#define _flindirnode_fini(self) _fdirnode_fini(self)

/* Return a pointer to linear-directory-node operators of `self' */
#define flindirnode_getops(self) \
	((struct flindirnode_ops const *)__COMPILER_REQTYPE(struct flindirnode const *, self)->mf_ops)


/* Default operators for `flindirnode_ops::ldno_*' */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL flindirnode_v_destroy)(struct flindirnode *__restrict self);
FUNDEF WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL flindirnode_v_lookup(struct flindirnode *__restrict self, struct flookup_info *__restrict info);
FUNDEF NONNULL((1, 2)) void KCALL flindirnode_v_enum(struct flindirnode *__restrict self, struct fdirenum *__restrict result);
FUNDEF NONNULL((1, 2)) void KCALL flindirnode_v_mkfile(struct flindirnode *__restrict self, struct fmkfile_info *__restrict info);
FUNDEF NONNULL((1, 2, 3)) void KCALL flindirnode_v_unlink(struct flindirnode *__restrict self, struct fdirent *__restrict entry, struct fnode *__restrict file);
FUNDEF NONNULL((1, 2)) void KCALL flindirnode_v_rename(struct flindirnode *__restrict self, struct frename_info *__restrict info);



DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */
#endif

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FDIRNODE_LINEAR_H */
