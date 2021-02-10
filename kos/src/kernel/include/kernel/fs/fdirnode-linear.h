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

#if 0
#ifndef CONFIG_USE_NEW_FS
#include <fs/node.h>
#else /* !CONFIG_USE_NEW_FS */
#include <kernel/fs/fdirent.h>
#include <kernel/fs/fdirnode.h>
#include <kernel/types.h>
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
 *     positions of any unrelated directory entry is not altered.
 * Using this, a filesystem may provide a low-level readdir() function
 * that simply reads a directory entry from a given address within the
 * directory stream.
 *
 * NOTE: Filesystem-level operator tables _must_ use the provided
 *       operators    for    `ldno_lookup'    and     `ldno_enum'
 *
 * As far as  implementation goes, `ldno_readdir'  is lazily called  when
 * trying to load more directory entries. For this purpose, that function
 * will  be called  iteratively by `ldno_lookup'  to find the  file it is
 * looking for, whilst  caching all  entires that it  wasn't looking  for
 * within a hash-map  stored within  the directory object.  When the  end
 * of  the directory file  is reached, then the  last-read file offset is
 * set to  `(pos_t)-1',  and  `ldno_readdir' will  not  be  called  again
 * (tough  it  may still  be  getting called  by  another thread  in case
 * multiple accesses were being made at the same time)
 *
 * Enumeration works the same, except that it will only stop once all
 * directory entries have been loaded.
 *
 */

struct flindirnode;
struct flindirent;

struct flindirnode_ops {
#define _flindirnode_ops_firstfield(prefix)  _fdirnode_ops_firstfield(prefix)
#define flindirnode_ops_as_fdirnode_ops(ops) ((struct fdirnode_ops const *)&(ops)->_fdirnode_ops_firstfield(ldno_))
#define flindirnode_ops_as_fnode_ops(ops)    ((struct fnode_ops const *)&(ops)->_fnode_ops_firstfield(ldno_))
#define flindirnode_ops_as_mfile_ops(ops)    ((struct mfile_ops const *)&(ops)->_mfile_ops_firstfield(ldno_))
#define FLINDIRNODE_OPS_FIELDS(prefix, T)                                             \
	FDIRNODE_OPS_FIELDS(prefix, T);                                                   \
//	                                                                                  \
	/* [1..1] Read a directory entry from a given position within the directory file. \
	 * Note that this function should _NOT_ initialize `return->fld_link'             \
	 * @param: pentry_pos: [in]  Pointer to the position of the entry to read.        \
	 *                     [out] Pointer to the next entry followed the one returned. \
	 *                           When `NULL' is returned, what's written back is      \
	 *                           undefined.                                           \
	 * @return: * :   The file entry that was read.                                   \
	 * @return: NULL: The end of the directory file has been reached. */              \
	WUNUSED NONNULL((1, 2)) REF struct flindirent *                                   \
	(KCALL *prefix##readdir)(T *__restrict self, pos_t *__restrict pentry_pos)

	/* TODO: Integration with `ldno_mkfile', `ldno_unlink' and `ldno_rename'
	 *       All of these operators must somehow interact with the directory
	 *       cache, and there are 2 ways to go about this:
	 *  - Add lower-level operators that replace those mentioned, and have
	 *    all flindirnode objects use the same callbacks for the  original
	 *    operators, which in turn call the more-lower-level ones
	 *  - Provide a set of functions that must be called by fs-specific
	 *    implementations of the original operators. In this case, also
	 *    provide examples of how to wrap functions properly.
	 * I feel like the later is the only ~true~ way we can go, since a filesystem
	 * should  still be able to construct custom sub-classes of `flindirent', and
	 * such a system would simply be more flexible in general...
	 *
	 * NOPE! Dumb it down to where the filesystem must specify: */

	/* [0..1][lock(READ(self->ldn_dat.ldd_flock))]
	 * Skip unused portions of the directory file. Unused here means
	 * that  such  portions may  be  used when  creating  new files. */
	WUNUSED NONNULL((1)) pos_t
	(KCALL *ldno_skipfree)(struct flindirnode *__restrict self, pos_t start);

	/* [1..1][lock(READ(self->ldn_dat.ldd_flock))]
	 * Read a directory entry from `*pentry_pos'. The caller will  have
	 * ensured that `*pentry_pos' doesn't point  at free space. If  the
	 * end of the directory has been reached, return `NULL'. Otherwise,
	 * return a new entry and update `*pentry_pos' to point to its end. */
	WUNUSED NONNULL((1, 2)) REF struct flindirent *
	(KCALL *ldno_readdir)(struct flindirnode *__restrict self,
	                      pos_t *__restrict pentry_pos);


	/* Operators... */
	FLINDIRNODE_OPS_FIELDS(ldno_, struct flindirnode);
};

struct flindirenum {
	struct fdirenum_ops const *lde_ops; /* [1..1][const] Operators. */
	REF struct flindirnode    *lde_dir; /* [1..1][const] Source directory.
	                                     * Note that  this field  also holds  a reference  to
	                                     * the `ldn_dat.ldd_norehash' counter, such that said
	                                     * counter  is  decremented when  this  enumerator is
	                                     * destroyed. */
	size_t                     lde_;
	/* TODO: position index data */
};



struct flindirent {
	SLIST_ENTRY(flindirent) fld_link; /* [0..1][lock(:ldn_dat.ldd_lock)] Next dirent with a similar hash. */
	pos_t                   fld_pos;  /* [const] Absolute in-directory position of this entry. */
	uintptr_t               fld_hash; /* [const] Hash of this directory entry. (s.a. `fdirent_hash()') */
	struct fdirent          fld_ent;  /* The underlying directory entry. */
};

#ifndef __flindirent_slist_defined
#define __flindirent_slist_defined
SLIST_HEAD(flindirent_slist, flindirent);
#endif /* !__flindirent_slist_defined */

struct flindirbucket {
	struct REF flindirent_slist ldb_entires; /* [0..n] List of directory entries with a similar hash. */
};

struct flindirdat {
	struct shared_rwlock  ldd_flock;    /* Lock for synchronizing changes to the backing directory file. */
};

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


/* Return a pointer to linear-directory-node operators of `self' */
#define flindirnode_getops(self) \
	((struct flindirnode_ops const *)__COMPILER_REQTYPE(struct flindirnode const *, self)->mf_ops)


/* Default callback for `flindirnode_ops::ldno_destory'
 * If  overwritten, sub-classes _must_ invoke this one! */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL flindirnode_destroy)(struct flindirnode *__restrict self);

/* Default callback for `flindirnode_ops::ldno_lookup' */
FUNDEF WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
flindirnode_lookup(struct flindirnode *__restrict self,
                   struct flookup_info *__restrict info);

/* Default callback for `flindirnode_ops::ldno_enum' */
FUNDEF NONNULL((1, 2)) void KCALL
flindirnode_enum(struct flindirnode *__restrict self,
                 struct fdirenum *__restrict result);



DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */
#endif

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FDIRNODE_LINEAR_H */
