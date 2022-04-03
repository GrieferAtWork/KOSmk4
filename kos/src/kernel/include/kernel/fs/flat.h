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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_FLAT_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_FLAT_H 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/super.h>
#include <kernel/types.h>

#include <kos/sched/shared-rwlock.h>

/*
 * Helpers for "flat" filesystems:
 *  - Directory data is read/written like regular files
 *  - Directory entries are flexible-length chunks within the directory files
 *  - fdirent_open() only uses fd_type and fd_ino (alongside the superblock's
 *    fnode tree and an fs-specific create-new-fnode function for new nodes).
 *
 * Pretty much all on-disk filesystem drivers are derived from this model.
 */

#ifdef __CC__
DECL_BEGIN

struct flatdirnode;
struct flatdirent;

TAILQ_HEAD(flatdirent_tailq, flatdirent);
struct flatdirent {
	pos_t                       fde_pos;   /* [const] Starting position in directory file-stream. */
	size_t                      fde_size;  /* [const] Total size (in bytes) of entry in directory file-stream. */
	TAILQ_ENTRY(REF flatdirent) fde_bypos; /* [0..1][lock(:fdn_data.fdd_lock)] By-`fde_pos'-sorted list of dir entries.
	                                        * This  field becomes [const] once it is  marked as UNBOUND, at which point
	                                        * this directory entry may be considered as having been deleted. */
	struct fdirent              fde_ent;   /* Underlying directory entry. */
};

/* Default allocator/free functions for `flatdirent'.
 *
 * - Note that  `flatdirent_ops'  (and  `flatdirent_v_destroy')
 *   make use of these to free the entry, but custom sub-clases
 *   are free to define their  own alloc/free functions by  use
 *   of a custom destroy and `fdnx_mkent'.
 * - `_flatdirent_alloc()' is used when `fdnx_mkent' isn't defined. */
#define _flatdirent_alloc(namelen)                                                         \
	((struct flatdirent *)kmalloc(__builtin_offsetof(struct flatdirent, fde_ent.fd_name) + \
	                              ((namelen) + 1) * sizeof(char),                          \
	                              GFP_NORMAL))
#define _flatdirent_free(self) kfree(__COMPILER_REQTYPE(struct flatdirent *, self))


#define flatdirent_destroy(self) fdirent_destroy(&(self)->fde_ent)
DEFINE_REFCOUNT_FUNCTIONS(struct flatdirent, fde_ent.fd_refcnt, flatdirent_destroy)

#define fdirent_asflat(self)      COMPILER_CONTAINER_OF(self, struct flatdirent, fde_ent)
#define flatdirent_basaddr(self) ((self)->fde_pos)
#define flatdirent_endaddr(self) ((self)->fde_pos + (self)->fde_size)

/* Check if `self' was deleted. */
#define flatdirent_wasdeleted(self)        (!TAILQ_ISBOUND(self, fde_bypos))
#define flatdirent_wasdeleted_atomic(self) (__hybrid_atomic_load((self)->fde_bypos.tqe_prev, __ATOMIC_ACQUIRE) == NULL)


/* Operators for `struct flatdirent'. These are implemented
 * such that `fdo_opennode' invokes  `flatsuper_opennode()' */
DATDEF struct fdirent_ops const flatdirent_ops;
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL flatdirent_v_destroy)(struct fdirent *__restrict self);
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
flatdirent_v_opennode(struct fdirent *__restrict self,
                      struct fdirnode *__restrict dir)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_IOERROR, ...);



struct flatdirnode_xops {
	/* [1..1][lock(READ(self->fdn_data.fdd_lock))]
	 * - Read & return an entry from the directory stream of `self', with
	 *   backing  stream  data loaded  from-disk  via `mfile_read(self)'.
	 * - The caller is responsible to guaranty that `pos' either equals `0',
	 *   or the `fde_pos+fde_size' of some other directory entry  previously
	 *   returned by this function.
	 * - This operator will not be called if `MFILE_F_DELETED' was found to be  set
	 *   at some point after the read-lock to self->fdn_data.fdd_lock was acquired.
	 * This function must initialize:
	 *  - return->fde_ent.fd_ops     = ...;     # likely set to `flatdirent_ops'
	 *  - return->fde_ent.fd_ino     = ...;     # FS-specific (important for `flatsuper_ops::ffso_makenode')
	 *  - return->fde_ent.fd_type    = ...;     # File type   (important for `flatsuper_ops::ffso_makenode')
	 *  - return->fde_ent.fd_name    = ...;     # `fd_namelen'-character long filename (NUL terminator done by caller)
	 *  - return->fde_ent.fd_namelen = ...;     # Length of filename
	 *  - return->fde_pos            = ...;     # Some value >= pos
	 *  - return->fde_size           = ...;     # Some value > 0
	 * The caller of this function will initialize:
	 *  - return->fde_bypos         = ...;      # Caller will insert into by-position list
	 *  - return->fde_ent.fd_refcnt = 1;
	 *  - return->fde_ent.fd_name[return->fde_ent.fd_namelen] = '\0';
	 *  - return->fde_ent.fd_hash   = fdirent_hash(return->fde_ent.fd_name, return->fde_ent.fd_namelen);
	 *  - ...;                                  # Caller will insert into hash-vector (case-sensitive; duplicate
	 *                                          # names are automatically corrected by deleting duplicate files)
	 * @return: * :   Newly allocated, partially initialized dirent. (see above)
	 * @return: NULL: No more entries exist past `pos'; end-of-directory */
	BLOCKING WUNUSED struct flatdirent *
	(KCALL *fdnx_readdir)(struct flatdirnode *__restrict self, pos_t pos)
			THROWS(E_BADALLOC, E_IOERROR, ...);

	/* [0..1][lock(WRITE(self->fdn_data.fdd_lock))]
	 * - Write a directory entry `ent' pointing to `file' into the stream of  `self'.
	 * - The caller of this function must check for `MFILE_F_READONLY' and not invoke
	 *   it if that flag was set at the time of the check.
	 * - This  operator will not be called if  `MFILE_F_DELETED' was found to be set
	 *   at some point after the write-lock to self->fdn_data.fdd_lock was acquired.
	 * - When `FFLATSUPER_FEAT_WRITEDIR_CHANGES_INO' is set, this operator may alter:
	 *   - file->fn_ino          (in this case though, only while holding `mfile_tslock_acquire()')
	 *   - ent->fde_ent.fd_ino   (must remain in-sync with `file->fn_ino'; no
	 *                           lock  is needed when  writing to this field)
	 *
	 * Implementation:
	 * >> pos_t entpos;
	 * >> if (IS_PART_OF_RESERVED_RANGE(ent->fde_pos, ent->fde_size)) {
	 * >>     // Some directories have reserved address range (usually at the start)
	 * >>     // which cannot be used for "normal" entries (e.g. "fat"). To handle
	 * >>     // this case, `fdnx_writedir' may modify `fde_pos' such that it points
	 * >>     // at the end of a reserved area.
	 * >>     pos_t end = END_OF_RESREVED_RANGE(ent->fde_pos);
	 * >>     size_t delta = end - ent->fde_pos;
	 * >>     if (OVERFLOW_USUB(ent->fde_size, delta, &ent->fde_size))
	 * >>         ent->fde_size = 0;
	 * >>     ent->fde_pos = end;
	 * >> }
	 * >> entpos = ent->fde_pos;
	 * >> if (!IS_PROPERLY_ALIGNED(entpos)) { // Only needed if different entries have different alignments,
	 * >>                                     // or rather: the end of an entry isn't a properly aligned start
	 * >>                                     // of another.
	 * >>     pos_t newpos = CEIL_ALIGN(entpos);
	 * >>     size_t delta = end - entpos;
	 * >>     if (OVERFLOW_USUB(ent->fde_size, delta, &ent->fde_size))
	 * >>         ent->fde_size = 0;
	 * >>     entpos = end;
	 * >> }
	 * >> size_t reqsize = REQUIRED_STREAM_SIZE_FOR(ent, file);
	 * >> if (ent->fde_size < reqsize) {
	 * >>     ent->fde_size = reqsize;
	 * >>     return false;
	 * >> }
	 * >>
	 * >> WRITE_ENTRY_TO_DIRSTREAM(self, ent, file, entpos, reqsiz);
	 * >> ent->fde_pos  = entpos;
	 * >> ent->fde_size = reqsiz;
	 * >> return true;
	 * @param: at_end_of_dir: Entry is being created at the end of the directory.
	 * @return: true:  New entry was written to disk
	 * @return: false: Insufficient space at `ent->fde_pos'  (which may have been  moved
	 *                 to a higher location in case it overlapped with a reserved area).
	 *                 The requires space was saved in `ent->fde_size'.
	 * @throw: E_FSERROR_ILLEGAL_PATH: `ent->fde_ent.fd_name' contains illegal characters.
	 * @throw: E_FSERROR_DISK_FULL:    Unable to write many more data: disk is full. */
	BLOCKING WUNUSED NONNULL((1, 2, 3)) __BOOL
	(KCALL *fdnx_writedir)(struct flatdirnode *__restrict self,
	                       struct flatdirent *__restrict ent,
	                       struct fnode *__restrict file,
	                       __BOOL at_end_of_dir)
			THROWS(E_IOERROR, E_FSERROR_DISK_FULL, E_FSERROR_ILLEGAL_PATH, ...);

	/* [0..1][lock(WRITE(self->fdn_data.fdd_lock))]
	 * [if(fdnx_writedir != NULL, [1..1])]
	 * - Modify the on-disk data for `ent' to mark it as having been deleted.
	 * - This function is invoked during error-cleanup paths, and even though
	 *   it is allowed to throw exceptions,  it should refrain from doing  so
	 *   since the act might lead to filesystem errors.
	 * - If  appropriate,  the  _CALLER_ will  decrement  `[file]->fn_nlink'! If
	 *   in this case `fn_nlink' drops to `0', `fdnx_deletefile' will be called.
	 * - The caller of this function must check for `MFILE_F_READONLY' and
	 *   not invoke it  if that flag  was set  at the time  of the  check.
	 * - This operator will not be called if `MFILE_F_DELETED' was found to be set at
	 *   some point after the  write-lock to `self->fdn_data.fdd_lock' was  acquired.
	 * @param: at_end_of_dir: When `true', the delete is happening such that `ent'
	 *                        scrapes against the far end of the directory stream. */
	BLOCKING NONNULL((1, 2, 3)) void
	(KCALL *fdnx_deleteent)(struct flatdirnode *__restrict self,
	                        struct flatdirent *__restrict ent,
	                        struct fnode *__restrict file,
	                        __BOOL at_end_of_dir)
			THROWS(E_IOERROR, ...);

	/* [0..1][if(fdnx_writedir != NULL, [1..1])]
	 * - Create  a new file & directory entry (but _DONT_ try to add the entry to `self')
	 * - This function is only supposed to allocate a new file-node as will be needed for
	 *   representing the file specified by `info'  in memory. NOTE: This function  isn't
	 *   called when `info->mkf_fmode == 0' (iow: for the hardlink case)
	 * - This  operator will not be called if  `MFILE_F_DELETED' was found to be set
	 *   at some point after the write-lock to self->fdn_data.fdd_lock was acquired.
	 *
	 * This function must allocate+initialize the returned file:
	 *  - return->_fnode_file_ mf_ops        = ...;                # As appropriate
	 *  - return->_fnode_file_ mf_parts      = NULL;               # Or `MFILE_PARTS_ANONYMOUS' if that fits better. (Note that for `flatdirnode's, this _MUST_ be `NULL')
	 *  - return->_fnode_file_ mf_changed    = SLIST_INIT;         # Or `MFILE_PARTS_ANONYMOUS' if that fits better. (Note that for `flatdirnode's, this _MUST_ be `NULL')
	 *  - return->_fnode_file_ mf_flags      = ... & (MFILE_F_READONLY | MFILE_F_NOUSRMMAP |    # directories require `MFILE_F_FIXEDFILESIZE', and should
	 *                                                MFILE_F_NOUSRIO | MFILE_F_FIXEDFILESIZE | # probably also have `MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO'
	 *                                                MFILE_FN_ATTRREADONLY | MFILE_F_ROFLAGS);
	 *  - return->_fnode_file_ mf_filesize   = S_ISDIR(info->mkf_fmode) ? (pos_t)-1 : (pos_t)...;
	 *  - return->fn_ino                     = <unallocated>;      # FS-specific, inode number for non-allocated files (later allocated in `fdnx_allocfile' or `fdnx_writedir')
	 *  - return->fn_fsdata                  = ...;                # Optional...
	 *  - return->*                          = ...;                # Any fields from sub-classes of `fnode'
	 * The caller of this function will do the following additional init:
	 *  - return->_fnode_file_ mf_refcnt     = 1 + ...;   # +1: MFILE_FN_GLOBAL_REF
	 *  - return->_fnode_file_ mf_notify     = NULL;
	 *  - return->_fnode_file_ mf_flags     |= MFILE_FN_GLOBAL_REF;
	 *  - return->_fnode_file_ mf_flags     |= self->_fdirnode_node_ _fnode_file_ mf_flags & (MFILE_F_READONLY | MFILE_F_NOATIME | MFILE_F_NOMTIME);
	 *  - return->_fnode_file_ mf_lock       = ATOMIC_RWLOCK_INIT;
	 *  - return->_fnode_file_ mf_initdone   = SIG_INIT;
	 *  - return->_fnode_file_ mf_lockops    = SLIST_HEAD_INITIALIZER(~);
	 *  - return->_fnode_file_ mf_changed    = SLIST_HEAD_INITIALIZER(~);
	 *  - return->_fnode_file_ mf_part_amask = self->_fdirnode_node_ _fnode_file_ mf_part_amask;
	 *  - return->_fnode_file_ mf_blockshift = self->_fdirnode_node_ _fnode_file_ mf_blockshift;
	 *  - return->_fnode_file_ mf_iobashift  = self->_fdirnode_node_ _fnode_file_ mf_iobashift;
	 *  - return->_fnode_file_ mf_trunclock  = 0;
	 *  - return->_fnode_file_ mf_atime      = info->mkf_creat.c_atime;
	 *  - return->_fnode_file_ mf_mtime      = info->mkf_creat.c_mtime;
	 *  - return->_fnode_file_ mf_ctime      = info->mkf_creat.c_ctime;
	 *  - return->_fnode_file_ mf_btime      = info->mkf_creat.c_btime;
	 *  - return->fn_nlink                   = 1;
	 *  - return->fn_mode                    = info->mkf_fmode;
	 *  - return->fn_uid                     = info->mkf_creat.c_owner;
	 *  - return->fn_gid                     = info->mkf_creat.c_group;
	 *  - return->fn_super                   = incref(self->_fdirnode_node_ fn_super);
	 *  - return->fn_changed                 = LIST_ENTRY_UNBOUND_INITIALIZER;
	 *  - return->fn_supent                  = ...;    # By adding to the superblock's node-tree (or marking as unbound)
	 *  - return->fn_allnodes                = ...;    # via `fnode_init_addtoall()'
	 * @return: * : The newly allocated (and partially initialized) file.
	 * @throw: E_FSERROR_UNSUPPORTED_OPERATION: Filesystem doesn't support `info->mkf_fmode & S_IFMT' */
	BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct fnode *
	(KCALL *fdnx_mkfile)(struct flatdirnode *__restrict self,
	                     struct fmkfile_info const *__restrict info)
			THROWS(E_BADALLOC, E_IOERROR, E_FSERROR_UNSUPPORTED_OPERATION, ...);

	/* [0..1]
	 * - Allocate a new flat-directory-entry for a given `file' returned by `fdnx_mkfile()'
	 *   This  operator is optional, and if not implemented will be substituted by a direct
	 *   allocation of a `struct flatdirent' object (using `flatdirent_ops' for operators)
	 * - This operator is also used in the implementation of rename() operations.
	 * - If appropriate, the _CALLER_ will increment `file->fn_nlink'!
	 *
	 * This operator must allocate+initialize the returned entry:
	 *  - return->fde_ent.fd_ops = ...;  # As appropriate for sub-classes (usually `flatdirent_ops')
	 *  - return->*              = ...;  # Any fields from sub-classes of `flatdirent'
	 * The caller of this operator will do the following additional init:
	 *  - return->fde_pos            = ...;  # Initialized by/with help of `fdnx_writedir()'
	 *  - return->fde_size           = ...;  # Initialized by/with help of `fdnx_writedir()'
	 *  - return->fde_bypos          = ...;  # Initialized after successful `fdnx_writedir()'
	 *  - return->fde_ent.fd_refcnt  = 1;
	 *  - return->fde_ent.fd_ino     = file->fn_ino;
	 *  - return->fde_ent.fd_namelen = info->mkf_namelen;
	 *  - return->fde_ent.fd_type    = IFTODT(file->fn_mode);
	 *  - *(char *)mempcpy(return->fde_ent.fd_name, info->mkf_name, info->mkf_namelen, sizeof(char)) = '\0';
	 *  - return->fde_ent.fd_hash    = info->mkf_hash;     # or `fdirent_hash(return->fde_ent.fd_name, return->fde_ent.fd_namelen)'
	 *  - ...;                               # Caller will insert into hash-vector after successful `fdnx_writedir()'
	 * @return: * : The newly allocated (and partially initialized) directory entry. */
	BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) struct flatdirent *
	(KCALL *fdnx_mkent)(struct flatdirnode *__restrict self,
	                    struct fmkfile_info const *__restrict info,
	                    struct fnode *__restrict file)
			THROWS(E_SEGFAULT, E_BADALLOC, E_IOERROR, ...);

	/* [0..1][lock(WRITE(self->fdn_data.fdd_lock))]
	 * Optional  callback that is invoked as a phase-2 addendum to `fdnx_mkfile'.
	 * This  callback is invoked after the flat-dir implementation has created an
	 * appropriate directory entry for `file' (that is: `ent'), and written it to
	 * the underlying directory stream (via `fdnx_writedir()'). This function can
	 * then be used to allocate on-disk template data for `file'.
	 *
	 * Used for:
	 *   - FAT:  Allocate and write out the initial content template for directories
	 *   - EXT2: Allocate a new Inode for `file', and update  `ent->fde_ent.fd_ino',
	 *           `file->fn_ino', and the on-disk entry for `ent' (Ext2DiskDirent) to
	 *           all reference the proper Inode number.
	 *   - ...
	 *
	 * If this operator returns with an exception, the directory entry previously
	 * written by `fdnx_writedir()' will be marked as deleted (`fdnx_deleteent'). */
	BLOCKING NONNULL((1, 2, 3, 4)) void
	(KCALL *fdnx_allocfile)(struct flatdirnode *__restrict self,
	                        struct flatdirent *__restrict ent,
	                        struct fnode *__restrict file,
	                        struct fmkfile_info const *__restrict info)
			THROWS(E_BADALLOC, E_IOERROR, ...);

	/* [0..1]
	 * Following deletion of `last_deleted_ent', the nlink counter of `file' reached `0'.
	 * As  the result of  this, this operator is  invoked for the  purpose of freeing any
	 * remaining on-disk data of `file'.
	 *
	 * At the point at which this operator is invoked, `self' will have already been
	 * marked as deleted
	 *
	 * Used for:
	 *   - FAT:  Free the cluster chain used for backing data of `file'
	 *   - EXT2: Free file data, followed by deallocating the on-disk INode object
	 *   - ...
	 *
	 * Even  if this operator returns with an exception, `last_deleted_ent' will not
	 * be re-established, and `file->fn_nlink' will remain at `0'. Exactly what this
	 * means for on-disk  data is  filesystem-specific, but it  probably means  that
	 * there's now a minor filesystem inconsistency.
	 *
	 * Note that unlike `fdnx_allocfile()', this operator is _NOT_ invoked  while
	 * holding any sort of lock to `self'! Instead, it can be invoked as a stand-
	 * alone function. */
	BLOCKING NONNULL((1, 2, 3)) void
	(KCALL *fdnx_deletefile)(struct flatdirnode *__restrict self,
	                         struct flatdirent *__restrict last_deleted_ent,
	                         struct fnode *__restrict file)
			THROWS(E_IOERROR, ...);

	/* [0..1][lock(WRITE(oldparent->fdn_data.fdd_lock) &&
	 *             WRITE(newparent->fdn_data.fdd_lock))]
	 * Optional callback invoked when the directory entry of a file changes,
	 * alongside which a change in  directory may also occur. This  operator
	 * is invoked from `oldparent' and may  be used to update on-disk  meta-
	 * data for special directory entries present on some filesystems.
	 *
	 * Even if this operator returns with an exception, a rename is not aborted. */
	BLOCKING NONNULL((1, 2, 3, 4, 5)) void
	(KCALL *fdnx_direntchanged)(struct fnode *__restrict self,
	                            struct flatdirnode *oldparent,
	                            struct flatdirnode *newparent,
	                            struct flatdirent *__restrict old_ent,
	                            struct flatdirent *__restrict new_ent)
			THROWS(E_IOERROR, ...);

	/* More operators go here. */
};


/* Flat directory enumeration */
struct flatdirenum
#ifdef __cplusplus
    : fdirenum                        /* Underlying enumerator */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct fdirenum        ffde_enum; /* Underlying enumerator */
#endif /* !__cplusplus */
	REF struct flatdirent *ffde_next; /* [0..1][lock(SMP(ffde_lock))] Next entry to read.
	                                   * When NULL, load the next entry with a position `>= ffde_pos' */
	pos_t                  ffde_pos;  /* [valid_if(!ffde_next)][lock(SMP(ffde_lock))] Next position. */
#ifndef CONFIG_NO_SMP
	struct atomic_lock     ffde_lock; /* Lock for the above. */
#endif /* !CONFIG_NO_SMP */
};
#define fdirenum_asflat(self) ((struct flatdirenum *)(self))

#ifdef CONFIG_NO_SMP
#define flatdirenum_lock_acquire_nopr(self) (void)0
#define flatdirenum_lock_release_nopr(self) (void)0
#else /* CONFIG_NO_SMP */
#define flatdirenum_lock_acquire_nopr(self) atomic_lock_acquire_nopr(&(self)->ffde_lock)
#define flatdirenum_lock_release_nopr(self) atomic_lock_release(&(self)->ffde_lock)
#endif /* !CONFIG_NO_SMP */
#define flatdirenum_lock_acquire(self)      \
	do {                                     \
		pflag_t _was = PREEMPTION_PUSHOFF(); \
		flatdirenum_lock_acquire_nopr(self)
#define flatdirenum_lock_release_br(self)     \
		(flatdirenum_lock_release_nopr(self), \
		 PREEMPTION_POP(_was))
#define flatdirenum_lock_release(self)     \
		flatdirenum_lock_release_br(self); \
	}	__WHILE0

/* Directory enumeration operators for `struct flatdirenum' */
DATDEF struct fdirenum_ops const flatdirenum_ops;
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL flatdirenum_v_fini)(struct fdirenum *__restrict self);
FUNDEF BLOCKING NONNULL((1)) size_t KCALL
flatdirenum_v_readdir(struct fdirenum *__restrict self, USER CHECKED struct dirent *buf,
                      size_t bufsize, readdir_mode_t readdir_mode, iomode_t UNUSED(mode))
		THROWS(E_SEGFAULT, E_BADALLOC, E_WOULDBLOCK, E_IOERROR, ...);
FUNDEF BLOCKING NONNULL((1)) pos_t KCALL
flatdirenum_v_seekdir(struct fdirenum *__restrict self,
                      off_t offset, unsigned int whence)
		THROWS(E_BADALLOC, E_IOERROR, ...);

/* Return a reference to the first directory entry at a position `>= pos'
 * If no such entry exists, return `NULL' instead. */
FUNDEF BLOCKING WUNUSED NONNULL((1)) REF struct flatdirent *KCALL
flatdirnode_entafter(struct flatdirnode *__restrict self, pos_t pos)
		THROWS(E_IOERROR, ...);





struct flatdirnode_ops {
	struct fdirnode_ops     fdno_dir;  /* Directory operators */
	struct flatdirnode_xops fdno_flat; /* Flat directory operators */
};

/* Default operators for `struct flatdirnode'-derived directories. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL flatdirnode_v_destroy)(struct mfile *__restrict self);
#define flatdirnode_v_open       fdirnode_v_open
#define flatdirnode_v_stat       fdirnode_v_stat
#define flatdirnode_v_changed    fdirnode_v_changed
#define flatdirnode_v_ioctl      fdirnode_v_ioctl
#define flatdirnode_v_stream_ops fdirnode_v_stream_ops
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
flatdirnode_v_lookup(struct fdirnode *__restrict self,
                     struct flookup_info *__restrict info)
		THROWS(E_BADALLOC, E_IOERROR, ...);
/* NOTE: `flatdirnode_v_enum()' solves the  deleted-file problem by  searching
 *       though the directory for the next dirent with a position >= any entry
 *       that got deleted.
 *       Other than that, seekdir() addressing uses `fde_pos', with readdir()
 *       rounding up to the nearest  existing entry with a starting  position
 *       that is >= the seek'd address. (SEEK_END is relative to the fde_pos+
 *       fde_size of the last directory entry) */
FUNDEF NONNULL((1)) void KCALL
flatdirnode_v_enum(struct fdirenum *__restrict result)
		THROWS(E_WOULDBLOCK);
#define flatdirnode_v_enumsz sizeof(struct flatdirenum)
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) unsigned int KCALL
flatdirnode_v_mkfile(struct fdirnode *__restrict self,
                     struct fmkfile_info *__restrict info)
		THROWS(E_BADALLOC, E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL,
		       E_FSERROR_READONLY, E_FSERROR_TOO_MANY_HARD_LINKS,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...);
FUNDEF BLOCKING WUNUSED NONNULL((1, 2, 3)) unsigned int KCALL
flatdirnode_v_unlink(struct fdirnode *__restrict self,
                     struct fdirent *__restrict entry,
                     struct fnode *__restrict file)
		THROWS(E_BADALLOC, E_FSERROR_DIRECTORY_NOT_EMPTY,
		       E_FSERROR_READONLY, E_IOERROR, ...);
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) unsigned int KCALL
flatdirnode_v_rename(struct fdirnode *__restrict self,
                     struct frename_info *__restrict info)
		THROWS(E_BADALLOC, E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL,
		       E_FSERROR_READONLY, E_IOERROR, ...);


struct flatdir_bucket {
	struct flatdirent *ffdb_ent; /* [0..1] Directory entry, `flatdirnode_deleted_dirent' for deleted, or NULL for sentinel */
};


/* Flags for `struct flatdirdata::fdd_flags' */
#define FFLATDIR_F_NORMAL         0x0000 /* Normal flags */
#define FFLATDIR_F_EOF            0x0001 /* EOF was reached (`fdnx_readdir(this, flatdirent_endaddr(TAILQ_LAST(&fdd_bypos))) == NULL') */
#define FFLATDIR_F_GAP_NOTLARGEST 0x0002 /* `fdd_biggest_gap' may not necessarily be the largest gap. */

struct flatdirdata {
	/* TODO: Slightly alter the design so it becomes possible to reap cached directory  entries
	 *       during system_cc(). Currently, that is only possible for `TAILQ_LAST(&fdd_bypos)',
	 *       as  the assumption is made that `fdd_bypos' contains all entries leading up to the
	 *       last one already loaded.
	 * Solution: There has to be a way to indicate that `fdd_bypos' may be incomplete as the
	 *           result of unused directory entries having been unloaded. */
	struct shared_rwlock        fdd_lock;        /* Lock for directory data. */
	struct REF flatdirent_tailq fdd_bypos;       /* [0..n][lock(fdd_lock)] List of files sorted by position in directory  stream.
	                                              * The files in this list are _IDENTICAL_ to those in `fdd_fileslist'. This list
	                                              * is simply an alternative way of looking at the contents of the directory. */
	pos_t                       fdd_biggest_gap; /* [lock(fdd_lock)] Size of the biggest gap between directory entries in `fdd_bypos'
	                                              * Used during file creation to pick between searching for a suitable gap to put new
	                                              * files, or appending them at the end of the directory. */
	struct flatdirent          *fdd_biggest_suc; /* [lock(fdd_lock)][1..1][valid_if(fdd_biggest_gap != 0)] Successor after `fdd_biggest_gap' */
	uintptr_t                   fdd_flags;       /* [lock(fdd_lock)] Set of `FFLATDIR_F_*' */
	size_t                      fdd_filessize;   /* [lock(fdd_lock)] Amount of used (non-NULL and non-deleted) directory entries */
	size_t                      fdd_filesused;   /* [lock(fdd_lock)] Amount of (non-NULL) directory entries */
	size_t                      fdd_filesmask;   /* [lock(fdd_lock)] Hash-mask for `p_cldlist' */
	struct flatdir_bucket      *fdd_fileslist;   /* [1..fdd_filesmask+1][owned_if(!= flatdir_empty_buckets)]
	                                              * [lock(fdd_lock)] Hash-vector  of  files in  this directory.
	                                              * Elements may no longer be added if `MFILE_F_DELETED' is set */
};

/* Hash-vector iteration helper macros */
#define flatdirent_hashof(self)       ((self)->fde_ent.fd_hash)
#define flatdirent_hashnx(i, perturb) ((i) = (((i) << 2) + (i) + (perturb) + 1), (perturb) >>= 5)

/* Empty hash-vector */
DATDEF struct flatdir_bucket const _flatdir_empty_buckets[1] ASMNAME("flatdir_empty_buckets");
#define flatdir_empty_buckets ((struct flatdir_bucket *)_flatdir_empty_buckets)

/* Deleted directory entry marker for `struct flatdir_bucket::ffdb_ent' */
DATDEF struct flatdirent flatdirnode_deleted_dirent;

#define flatdirdata_init(self)                    \
	(shared_rwlock_init(&(self)->fdd_lock),       \
	 TAILQ_INIT(&(self)->fdd_bypos),              \
	 (self)->fdd_biggest_gap = 0,                 \
	 (self)->fdd_flags       = FFLATDIR_F_NORMAL, \
	 (self)->fdd_filessize   = 0,                 \
	 (self)->fdd_filesused   = 0,                 \
	 (self)->fdd_filesmask   = 0,                 \
	 (self)->fdd_fileslist   = flatdir_empty_buckets)
#define flatdirdata_cinit(self)                               \
	(shared_rwlock_cinit(&(self)->fdd_lock),                  \
	 __hybrid_assert(TAILQ_EMPTY(&(self)->fdd_bypos)),        \
	 __hybrid_assert((self)->fdd_biggest_gap == 0),           \
	 __hybrid_assert((self)->fdd_flags == FFLATDIR_F_NORMAL), \
	 __hybrid_assert((self)->fdd_filessize == 0),             \
	 __hybrid_assert((self)->fdd_filesused == 0),             \
	 __hybrid_assert((self)->fdd_filesmask == 0),             \
	 (self)->fdd_fileslist = flatdir_empty_buckets)

/* Finalize the given flat directory data container. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL flatdirdata_fini)(struct flatdirdata *__restrict self);

/* Helper functions for adding/removing directory entries  to the files list of  `self'
 * These functions _ONLY_ modify `fdd_fileslist' and friends; the caller is responsible
 * for `fdd_bypos', as well as to be holding a lock to `self->fdn_data.fdd_lock'. */
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL flatdirnode_fileslist_removeent)(struct flatdirnode *__restrict self, struct flatdirent *__restrict ent);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL flatdirnode_fileslist_insertent)(struct flatdirnode *__restrict self, struct flatdirent *__restrict ent);
FUNDEF NOBLOCK WUNUSED NONNULL((1, 2)) __BOOL NOTHROW(FCALL flatdirnode_fileslist_tryinsertent)(struct flatdirnode *__restrict self, struct flatdirent *__restrict ent);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL flatdirnode_fileslist_rehash_after_remove)(struct flatdirnode *__restrict self);
FUNDEF NONNULL((1)) void FCALL flatdirnode_fileslist_rehash_before_insert(struct flatdirnode *__restrict self) THROWS(E_BADALLOC);

/* Lookup the named entry, returning `NULL' if not found. */
FUNDEF NOBLOCK NONNULL((1, 2)) struct flatdirent *FCALL
flatdirnode_fileslist_lookup(struct flatdirnode *__restrict self,
                             struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT);
/* Remove the named entry, returning `NULL' if not found.
 * Same as `flatdirnode_fileslist_lookup' + `flatdirnode_fileslist_removeent' */
FUNDEF NOBLOCK NONNULL((1, 2)) struct flatdirent *FCALL
flatdirnode_fileslist_remove(struct flatdirnode *__restrict self,
                             struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT);





/* Helpers for accessing `struct flatdirdata::fdd_lock' */
#define /*        */ _flatdirdata_reap(self)        (void)0
#define /*        */ flatdirdata_reap(self)         (void)0
#define /*        */ flatdirdata_mustreap(self)     0
#define /*BLOCKING*/ flatdirdata_write(self)        shared_rwlock_write(&(self)->fdd_lock)
#define /*BLOCKING*/ flatdirdata_write_nx(self)     shared_rwlock_write_nx(&(self)->fdd_lock)
#define /*        */ flatdirdata_trywrite(self)     shared_rwlock_trywrite(&(self)->fdd_lock)
#define /*        */ flatdirdata_endwrite(self)     (shared_rwlock_endwrite(&(self)->fdd_lock), flatdirdata_reap(self))
#define /*        */ _flatdirdata_endwrite(self)    shared_rwlock_endwrite(&(self)->fdd_lock)
#define /*BLOCKING*/ flatdirdata_read(self)         shared_rwlock_read(&(self)->fdd_lock)
#define /*BLOCKING*/ flatdirdata_read_nx(self)      shared_rwlock_read_nx(&(self)->fdd_lock)
#define /*        */ flatdirdata_tryread(self)      shared_rwlock_tryread(&(self)->fdd_lock)
#define /*        */ _flatdirdata_endread(self)     shared_rwlock_endread(&(self)->fdd_lock)
#define /*        */ flatdirdata_endread(self)      (void)(shared_rwlock_endread(&(self)->fdd_lock) && (flatdirdata_reap(self), 0))
#define /*        */ _flatdirdata_end(self)         shared_rwlock_end(&(self)->fdd_lock)
#define /*        */ flatdirdata_end(self)          (void)(shared_rwlock_end(&(self)->fdd_lock) && (flatdirdata_reap(self), 0))
#define /*BLOCKING*/ flatdirdata_upgrade(self)      shared_rwlock_upgrade(&(self)->fdd_lock)
#define /*        */ flatdirdata_tryupgrade(self)   shared_rwlock_tryupgrade(&(self)->fdd_lock)
#define /*        */ flatdirdata_downgrade(self)    shared_rwlock_downgrade(&(self)->fdd_lock)
#define /*        */ flatdirdata_reading(self)      shared_rwlock_reading(&(self)->fdd_lock)
#define /*        */ flatdirdata_writing(self)      shared_rwlock_writing(&(self)->fdd_lock)
#define /*        */ flatdirdata_canread(self)      shared_rwlock_canread(&(self)->fdd_lock)
#define /*        */ flatdirdata_canwrite(self)     shared_rwlock_canwrite(&(self)->fdd_lock)
#define /*BLOCKING*/ flatdirdata_waitread(self)     shared_rwlock_waitread(&(self)->fdd_lock)
#define /*BLOCKING*/ flatdirdata_waitwrite(self)    shared_rwlock_waitwrite(&(self)->fdd_lock)
#define /*BLOCKING*/ flatdirdata_waitread_nx(self)  shared_rwlock_waitread_nx(&(self)->fdd_lock)
#define /*BLOCKING*/ flatdirdata_waitwrite_nx(self) shared_rwlock_waitwrite_nx(&(self)->fdd_lock)


struct flatdirnode
#ifndef __WANT_FS_INLINE_STRUCTURES
    : fdirnode                   /* Underlying directory-node */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct fdirnode    fdn_dir;  /* Underlying directory-node */
#define _flatdirnode_dir_     fdn_dir.
#define _flatdirnode_asdir(x) &(x)->fdn_dir
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _flatdirnode_dir_     /* nothing */
#define _flatdirnode_asdir(x) x
#endif /* !__WANT_FS_INLINE_STRUCTURES */
	struct flatdirdata fdn_data; /* Flat directory node data. */
};


/* Helper conversion functions */
#define fdirnode_asflat(self) ((struct flatdirnode *)(self))
#define fnode_asflatdir(self) fdirnode_asflat(fnode_asdir(self))
#define mfile_asflatdir(self) fdirnode_asflat(mfile_asdir(self))


/* Return a pointer to directory-node operators of `self' */
#define flatdirnode_getops(self)                                                                                                         \
	__COMPILER_CONTAINER_OF(__COMPILER_REQTYPE(struct flatdirnode const *, self)->_flatdirnode_dir_ _fdirnode_node_ _fnode_file_ mf_ops, \
	                        struct flatdirnode_ops, fdno_dir.dno_node.no_file)
#define _flatdirnode_assert_ops_(ops) \
	_fdirnode_assert_ops_(&(ops)->fdno_dir)

/* Check if a given `struct flatdirnode *self' is a fsuper. */
#define flatdirnode_issuper(self) (&(self)->_flatdirnode_dir_ _fdirnode_node_ fn_super->fs_root == _flatdirnode_asdir(self))
#define flatdirnode_assuper(self) __COMPILER_CONTAINER_OF((struct fdirnode *)(self), struct flatsuper, ffs_super.fs_root)


/* Helpers for accessing `struct flatdirnode::fdn_data.fdd_lock' */
#define /*        */ _flatdirnode_reap(self)        _flatdirdata_reap(&(self)->fdn_data)
#define /*        */ flatdirnode_reap(self)         flatdirdata_reap(&(self)->fdn_data)
#define /*        */ flatdirnode_mustreap(self)     flatdirdata_mustreap(&(self)->fdn_data)
#define /*BLOCKING*/ flatdirnode_write(self)        flatdirdata_write(&(self)->fdn_data)
#define /*BLOCKING*/ flatdirnode_write_nx(self)     flatdirdata_write_nx(&(self)->fdn_data)
#define /*        */ flatdirnode_trywrite(self)     flatdirdata_trywrite(&(self)->fdn_data)
#define /*        */ flatdirnode_endwrite(self)     flatdirdata_endwrite(&(self)->fdn_data)
#define /*        */ _flatdirnode_endwrite(self)    _flatdirdata_endwrite(&(self)->fdn_data)
#define /*BLOCKING*/ flatdirnode_read(self)         flatdirdata_read(&(self)->fdn_data)
#define /*BLOCKING*/ flatdirnode_read_nx(self)      flatdirdata_read_nx(&(self)->fdn_data)
#define /*        */ flatdirnode_tryread(self)      flatdirdata_tryread(&(self)->fdn_data)
#define /*        */ _flatdirnode_endread(self)     _flatdirdata_endread(&(self)->fdn_data)
#define /*        */ flatdirnode_endread(self)      flatdirdata_endread(&(self)->fdn_data)
#define /*        */ _flatdirnode_end(self)         _flatdirdata_end(&(self)->fdn_data)
#define /*        */ flatdirnode_end(self)          flatdirdata_end(&(self)->fdn_data)
#define /*BLOCKING*/ flatdirnode_upgrade(self)      flatdirdata_upgrade(&(self)->fdn_data)
#define /*BLOCKING*/ flatdirnode_upgrade_nx(self)   flatdirdata_upgrade_nx(&(self)->fdn_data)
#define /*        */ flatdirnode_tryupgrade(self)   flatdirdata_tryupgrade(&(self)->fdn_data)
#define /*        */ flatdirnode_downgrade(self)    flatdirdata_downgrade(&(self)->fdn_data)
#define /*        */ flatdirnode_reading(self)      flatdirdata_reading(&(self)->fdn_data)
#define /*        */ flatdirnode_writing(self)      flatdirdata_writing(&(self)->fdn_data)
#define /*        */ flatdirnode_canread(self)      flatdirdata_canread(&(self)->fdn_data)
#define /*        */ flatdirnode_canwrite(self)     flatdirdata_canwrite(&(self)->fdn_data)
#define /*BLOCKING*/ flatdirnode_waitread(self)     flatdirdata_waitread(&(self)->fdn_data)
#define /*BLOCKING*/ flatdirnode_waitwrite(self)    flatdirdata_waitwrite(&(self)->fdn_data)
#define /*BLOCKING*/ flatdirnode_waitread_nx(self)  flatdirdata_waitread_nx(&(self)->fdn_data)
#define /*BLOCKING*/ flatdirnode_waitwrite_nx(self) flatdirdata_waitwrite_nx(&(self)->fdn_data)


/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_flatdirnode_dir_ _fdirnode_node_ _fnode_file_ mf_atime
 *  - self->_flatdirnode_dir_ _fdirnode_node_ _fnode_file_ mf_mtime
 *  - self->_flatdirnode_dir_ _fdirnode_node_ _fnode_file_ mf_ctime
 *  - self->_flatdirnode_dir_ _fdirnode_node_ _fnode_file_ mf_btime
 *  - self->_flatdirnode_dir_ _fdirnode_node_ fn_uid
 *  - self->_flatdirnode_dir_ _fdirnode_node_ fn_gid
 *  - self->_flatdirnode_dir_ _fdirnode_node_ fn_allnodes
 *  - self->_flatdirnode_dir_ _fdirnode_node_ fn_supent
 *  - self->_flatdirnode_dir_ _fdirnode_node_ fn_nlink  (to `1')
 *  - self->_flatdirnode_dir_ _fdirnode_node_ fn_ino
 *  - self->_flatdirnode_dir_ _fdirnode_node_ fn_mode (with something or'd with S_IFDIR)
 * @param: struct flatdirnode     *self:   Directory node to initialize.
 * @param: struct flatdirnode_ops *ops:    Directory operators.
 * @param: struct flatdirnode     *parent: Parent directory. */
#define _flatdirnode_init(self, ops, parent)                                                 \
	(_fdirnode_init(_flatdirnode_asdir(self), &(ops)->fdno_dir, _flatdirnode_asdir(parent)), \
	 (self)->_flatdirnode_dir_ _fdirnode_node_ _fnode_file_ mf_parts = __NULLPTR,            \
	 SLIST_INIT(&(self)->_flatdirnode_dir_ _fdirnode_node_ _fnode_file_ mf_changed),         \
	 flatdirdata_init(&(self)->fdn_data))
#define _flatdirnode_cinit(self, ops, super)                                                           \
	(_fdirnode_cinit(_flatdirnode_asdir(self), &(ops)->fdno_dir, _flatdirnode_asdir(parent)),          \
	 __hybrid_assert((self)->_flatdirnode_dir_ _fdirnode_node_ _fnode_file_ mf_parts == __NULLPTR),    \
	 __hybrid_assert(SLIST_EMPTY(&(self)->_flatdirnode_dir_ _fdirnode_node_ _fnode_file_ mf_changed)), \
	 flatdirdata_cinit(&(self)->fdn_data))
/* Finalize a partially initialized `struct flatdirnode' (as initialized by `_flatdirnode_init()') */
#define _flatdirnode_fini(self) \
	_fdirnode_fini(_flatdirnode_asdir(self))




/************************************************************************/
/* Flat superblock                                                      */
/************************************************************************/
struct flatsuper_ops {
	/* More operators go here. */

	/* [1..1][lock(READ(dir->fdn_data.fdd_lock))]
	 * Allocate a new file-node object for `ent' in `dir'
	 * This function may assume:
	 *  - !flatdirent_wasdeleted(ent);
	 * This function must allocate+initialize the returned node:
	 *  - return->_fnode_file_ mf_ops        = ...;                # As appropriate
	 *  - return->_fnode_file_ mf_parts      = NULL;               # Or `MFILE_PARTS_ANONYMOUS' if that fits better. (Note that for `flatdirnode's, this _MUST_ be `NULL')
	 *  - return->_fnode_file_ mf_changed    = SLIST_INIT;         # Or `MFILE_PARTS_ANONYMOUS' if that fits better. (Note that for `flatdirnode's, this _MUST_ be `SLIST_INIT')
	 *  - return->_fnode_file_ mf_flags      = ... & (MFILE_F_READONLY | MFILE_F_NOUSRMMAP |    # directories require `MFILE_F_FIXEDFILESIZE', and should
	 *                                                MFILE_F_NOUSRIO | MFILE_F_FIXEDFILESIZE | # probably also have `MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO'
	 *                                                MFILE_FN_ATTRREADONLY | MFILE_F_ROFLAGS);
	 *  - return->_fnode_file_ mf_filesize   = ...;                # As read from disk
	 *  - return->_fnode_file_ mf_atime      = ...;                # As read from disk
	 *  - return->_fnode_file_ mf_mtime      = ...;                # As read from disk
	 *  - return->_fnode_file_ mf_ctime      = ...;                # As read from disk
	 *  - return->_fnode_file_ mf_btime      = ...;                # As read from disk
	 *  - return->fn_nlink                   = ...;                # As read from disk
	 *  - return->fn_mode                    = ...;                # As read from disk  (S_IFMT must match `DTTOIF(ent->fde_ent.fd_type)')
	 *  - return->fn_uid                     = ...;                # As read from disk
	 *  - return->fn_gid                     = ...;                # As read from disk
	 *  - return->fn_fsdata                  = ...;                # Optional...
	 *  - return->*                          = ...;                # Any fields from sub-classes of `fnode'
	 * The caller of this function will do the following additional init:
	 *  - return->_fnode_file_ mf_refcnt     = 2;      # +1: MFILE_FN_GLOBAL_REF, +1: return of `flatsuper_opennode'
	 *  - return->_fnode_file_ mf_notify     = NULL;
	 *  - return->_fnode_file_ mf_flags     |= MFILE_FN_GLOBAL_REF;
	 *  - return->_fnode_file_ mf_flags     |= dir->mf_flags & (MFILE_F_READONLY | MFILE_F_NOATIME | MFILE_F_NOMTIME);
	 *  - return->_fnode_file_ mf_lock       = ATOMIC_RWLOCK_INIT;
	 *  - return->_fnode_file_ mf_initdone   = SIG_INIT;
	 *  - return->_fnode_file_ mf_lockops    = SLIST_HEAD_INITIALIZER(~);
	 *  - return->_fnode_file_ mf_changed    = SLIST_HEAD_INITIALIZER(~);
	 *  - return->_fnode_file_ mf_part_amask = self->ffs_super.fs_root._fdirnode_node_ _fnode_file_ mf_part_amask;
	 *  - return->_fnode_file_ mf_blockshift = self->ffs_super.fs_root._fdirnode_node_ _fnode_file_ mf_blockshift;
	 *  - return->_fnode_file_ mf_iobashift  = self->ffs_super.fs_root._fdirnode_node_ _fnode_file_ mf_iobashift;
	 *  - return->_fnode_file_ mf_trunclock  = 0;
	 *  - return->fn_ino                     = ent->fde_ent.fd_ino;
	 *  - return->fn_super                   = incref(dir->_fdirnode_node_ fn_super);
	 *  - return->fn_changed                 = LIST_ENTRY_UNBOUND_INITIALIZER;
	 *  - return->fn_supent                  = ...;    # By adding to the superblock's node-tree (or marking as unbound)
	 *  - return->fn_allnodes                = ...;    # via `fnode_init_addtoall()'
	 * @return: * : The newly allocated (and partially initialized) node. */
	ATTR_RETNONNULL WUNUSED NONNULL((1)) struct fnode *
	(KCALL *ffso_makenode)(struct flatsuper *__restrict self,
	                       struct flatdirent *__restrict ent,
	                       struct flatdirnode *__restrict dir)
			THROWS(E_BADALLOC, E_IOERROR);

	struct fsuper_ops       ffso_super; /* Super operators */
	struct flatdirnode_xops ffso_flat;  /* Flat root directory operators */
};


/* Flags for `struct flatsuper::ffs_features' */
#define FFLATSUPER_FEAT_NORMAL               0x0000 /* No special features. */
#define FFLATSUPER_FEAT_WRITEDIR_CHANGES_INO 0x0001 /* The `fdnx_writedir' operator of directories may alter the INode number of a file. */

struct flatsuper {
	/* flat-superblock-specific data goes here. */
	uintptr_t          ffs_features; /* Set of `FFLATSUPER_FEAT_*' */
	struct fsuper      ffs_super;    /* Underlying superblock. */
	struct flatdirdata ffs_rootdata; /* Directory data for the filesystem root. */
};


/* Helper conversion functions */
#define fsuper_asflat(self)        COMPILER_CONTAINER_OF(self, struct flatsuper, ffs_super)
#define fdirnode_asflatsuper(self) COMPILER_CONTAINER_OF(self, struct flatsuper, ffs_super.fs_root)
#define fnode_asflatsuper(self)    fdirnode_asflatsuper(fnode_asdir(self))
#define mfile_asflatsuper(self)    fdirnode_asflatsuper(mfile_asdir(self))

/* Return the root directory of a given `struct flatsuper' */
#define flatsuper_getroot(self)   fdirnode_asflat(&(self)->ffs_super.fs_root)

/* Return a pointer to flat-super operators of `self' */
#define flatsuper_getops(self)                                                                                                         \
	__COMPILER_CONTAINER_OF(__COMPILER_REQTYPE(struct flatsuper const *, self)->ffs_super.fs_root._fdirnode_node_ _fnode_file_ mf_ops, \
	                        struct flatsuper_ops, ffso_super.so_fdir.dno_node.no_file)

/* Default operators for `struct flatsuper'-derived superblocks. */
FUNDEF NOBLOCK NONNULL((1)) void /* `kfree(fnode_asflatsuper(self));' */
NOTHROW(KCALL flatsuper_v_free)(struct fnode *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL flatsuper_v_destroy)(struct mfile *__restrict self);
#define flatsuper_v_ioctl      fsuper_v_ioctl
#define flatsuper_v_open       flatdirnode_v_open
#define flatsuper_v_stat       flatdirnode_v_stat
#define flatsuper_v_changed    fsuper_v_changed
#define flatsuper_v_stream_ops fsuper_v_stream_ops



/* Open the  file-node associated  with  a given  directory  entry.
 * When the directory entry has already been deleted, return `NULL'
 *
 * This function will use the  INO number referenced by the  dirent
 * to look through the fnode tree of the superblock associated with
 * `dir'. If something was found, assert the correct node type with
 * `self->fde_ent.fd_type'  and return it.  Otherwise, create a new
 * file-node  object via the superblock's `ffso_makenode' operator,
 * register that node  within the  superblock's node-tree  (double-
 * checking that no node with identical INO number already exists),
 * before returning said newly created node.
 *
 * @return: * :   The file-node referenced by `self'.
 * @return: NULL: The given `self' was marked as deleted. */
#ifdef __INTELLISENSE__
BLOCKING WUNUSED REF struct fnode *
flatsuper_opennode(struct flatdirnode *__restrict dir,
                   struct flatdirent *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_IOERROR, ...);
#else /* __INTELLISENSE__ */
#define flatsuper_opennode(dir, self) \
	flatdirent_v_opennode(&(self)->fde_ent, _flatdirnode_asdir(dir))
#endif /* !__INTELLISENSE__ */



DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FLAT_H */
