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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_FLAT_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_FLAT_H 1

#include <kernel/compiler.h>

/*
 * Helpers for "flat" filesystems:
 *  - Directory data is read/written like regular files
 *  - Directory entries are flexible-length chunks within the directory files
 *  - fdirent_open() only uses fd_type and fd_ino (alongside the superblock's
 *    fnode tree and an fs-specific create-new-fnode function for new nodes).
 *
 * Pretty much all on-disk filesystems are derived from this model.
 */


#ifndef CONFIG_USE_NEW_FS
#include <fs/node.h>
#else /* !CONFIG_USE_NEW_FS */
#include <kernel/fs/dirent.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/super.h>
#include <kernel/types.h>
#include <sched/shared_rwlock.h>

#ifdef __CC__
DECL_BEGIN

/************************************************************************/
/* TODO: REMOVE_ME                                                      */
/* REMINDER: Before using this API for implementing FAT, finish its     */
/*           implementation. Otherwise, you'll likely end up doing      */
/*           everything twice in case some aspects of the API still     */
/*           need to be changed.                                        */
/************************************************************************/


struct fflatdirnode;
struct fflatdirent;

TAILQ_HEAD(fflatdirent_tailq, fflatdirent);
struct fflatdirent {
	pos_t                        fde_pos;   /* [const] Starting position in directory file-stream. */
	size_t                       fde_size;  /* [const] Total size (in bytes) of entry in directory file-stream. */
	TAILQ_ENTRY(REF fflatdirent) fde_bypos; /* [0..1][lock(:fdn_data.fdd_lock)] By-`fde_pos'-sorted list of dir entries.
	                                         * This  field becomes [const] once it is  marked as UNBOUND, at which point
	                                         * this directory entry may be considered as having been deleted. */
	struct fdirent               fde_ent;   /* Underlying directory entry. */
};

/* Default allocator/free functions for `fflatdirent'.
 *
 * - Note that `fflatdirent_ops' (and  `fflatdirent_v_destroy')
 *   make use of these to free the entry, but custom sub-clases
 *   are free to define their  own alloc/free functions by  use
 *   of a custom destroy and `fdnx_mkent'.
 * - `_fflatdirent_alloc()' is used when `fdnx_mkent' isn't defined. */
#define _fflatdirent_alloc(namelen)                                                          \
	((struct fflatdirent *)kmalloc(__builtin_offsetof(struct fflatdirent, fde_ent.fd_name) + \
	                               ((namelen) + 1) * sizeof(char),                           \
	                               GFP_NORMAL))
#define _fflatdirent_free(self) kfree(__COMPILER_REQTYPE(struct fflatdirent *, self))


#define fflatdirent_destroy(self) fdirent_destroy(&(self)->fde_ent)
DEFINE_REFCOUNT_FUNCTIONS(struct fflatdirent, fde_ent.fd_refcnt, fflatdirent_destroy)

#define fdirent_asflat(self)      COMPILER_CONTAINER_OF(self, struct fflatdirent, fde_ent)
#define fflatdirent_basaddr(self) ((self)->fde_pos)
#define fflatdirent_endaddr(self) ((self)->fde_pos + (self)->fde_size)

/* Check if `self' was deleted. */
#define fflatdirent_wasdeleted(self)        (!TAILQ_ISBOUND(self, fde_bypos))
#define fflatdirent_wasdeleted_atomic(self) (__hybrid_atomic_load((self)->fde_bypos.tqe_prev, __ATOMIC_ACQUIRE) == NULL)


/* Operators for `struct fflatdirent'. These are implemented
 * such that `fdo_opennode' invokes  `fflatsuper_opennode()' */
DATDEF struct fdirent_ops const fflatdirent_ops;
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fflatdirent_v_destroy)(struct fdirent *__restrict self);
FUNDEF WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
fflatdirent_v_opennode(struct fdirent *__restrict self,
                       struct fdirnode *__restrict dir)
		THROWS(E_WOULDBLOCK, E_BADALLOC);



struct fflatdirnode_xops {
	/* [1..1][lock(READ(self->fdn_data.fdd_lock))]
	 * - Read & return an entry from the directory stream of `self', with
	 *   backing  stream  data loaded  from-disk  via `mfile_read(self)'.
	 * - The caller is responsible to guaranty that `pos' either equals `0',
	 *   or the `fde_pos+fde_size' of some other directory entry  previously
	 *   returned by this function.
	 * - This operator will not be called if `MFILE_F_DELETED' was found to be  set
	 *   at some point after the read-lock to self->fdn_data.fdd_lock was acquired.
	 * This function must initialize:
	 *  - return->fde_ent.fd_ops     = ...;     # likely set to `fflatdirent_ops'
	 *  - return->fde_ent.fd_ino     = ...;     # FS-specific (important for `fflatsuper_ops::ffso_makenode')
	 *  - return->fde_ent.fd_type    = ...;     # File type   (important for `fflatsuper_ops::ffso_makenode')
	 *  - return->fde_ent.fd_name    = ...;     # NUL-terminated, `fd_namelen'-long filename
	 *  - return->fde_ent.fd_namelen = ...;     # Length of filename
	 *  - return->fde_pos            = ...;     # Some value >= pos
	 *  - return->fde_size           = ...;     # Some value > 0
	 * The caller of this function will initialize:
	 *  - return->fde_bypos         = ...;      # Caller will insert into by-position list
	 *  - return->fde_ent.fd_refcnt = 1;
	 *  - return->fde_ent.fd_hash   = fdirent_hash(return->fde_ent.fd_name, return->fde_ent.fd_namelen);
	 *  - ...;                                  # Caller will insert into hash-vector (case-sensitive; duplicate
	 *                                          # names are automatically corrected by deleting duplicate files)
	 * @return: * :   Newly allocated, partially initialized dirent. (see above)
	 * @return: NULL: No more entries exist past `pos'; end-of-directory */
	WUNUSED struct fflatdirent *
	(KCALL *fdnx_readdir)(struct fflatdirnode *__restrict self, pos_t pos)
			THROWS(E_BADALLOC, E_IOERROR);

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
	 * >>     // this case, `fdnx_writedir' may modify `fde_pos' such that it doesn't
	 * >>     // points at the end of a reserved area.
	 * >>     pos_t end = END_OF_RESREVED_RANGE(ent->fde_pos);
	 * >>     size_t delta = end - ent->fde_pos;
	 * >>     if (OVERFLOW_USUB(ent->fde_size, delta, &ent->fde_size))
	 * >>         ent->fde_size = 0;
	 * >>     ent->fde_pos = end;
	 * >> }
	 * >> entpos = ent->fde_pos;
	 * >> if (!IS_PROPERLY_ALIGNED(entpos)) {
	 * >>     // Directory entries may require special alignment
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
	WUNUSED NONNULL((1, 2, 3)) __BOOL
	(KCALL *fdnx_writedir)(struct fflatdirnode *__restrict self,
	                       struct fflatdirent *__restrict ent,
	                       struct fnode *__restrict file,
	                       __BOOL at_end_of_dir)
			THROWS(E_IOERROR, E_FSERROR_DISK_FULL, E_FSERROR_ILLEGAL_PATH);

	/* [0..1][lock(WRITE(self->fdn_data.fdd_lock))]
	 * [if(fdnx_writedir != NULL, [1..1])]
	 * - Modify the on-disk data for `ent' to mark it as having been deleted.
	 * - This function is invoked during error-cleanup paths, and even though
	 *   it is allowed to throw exceptions,  it should refrain from doing  so
	 *   since the act might lead to filesystem errors.
	 * - If  appropriate,  the _CALLER_  will decrement  `[file]->fn_nlink'! If
	 *   in this case `fn_nlink' drops to `0', `fdnx_deletefil' will be called.
	 * - The caller of this function must check for `MFILE_F_READONLY' and
	 *   not invoke it  if that flag  was set  at the time  of the  check.
	 * - This  operator will not be called if  `MFILE_F_DELETED' was found to be set
	 *   at some point after the write-lock to self->fdn_data.fdd_lock was acquired.
	 * @param: at_end_of_dir: When `true', the delete is happening such that `ent'
	 *                        scrapes against the far end of the directory stream. */
	NONNULL((1, 2)) void
	(KCALL *fdnx_deleteent)(struct fflatdirnode *__restrict self,
	                        struct fflatdirent const *__restrict ent,
	                        __BOOL at_end_of_dir)
			THROWS(E_IOERROR);

	/* [1..1]
	 * - Create  a new file & directory entry (but _DONT_ try to add the entry to `self')
	 * - This function is only supposed to allocate a new file-node as will be needed for
	 *   representing the file specified by `info'  in memory. NOTE: This function  isn't
	 *   called when `info->mkf_fmode == 0' (iow: for the hardlink case)
	 * - This  operator will not be called if  `MFILE_F_DELETED' was found to be set
	 *   at some point after the write-lock to self->fdn_data.fdd_lock was acquired.
	 *
	 * This function must allocate+initialize the returned file:
	 *  - return->_fnode_file_ mf_ops        = ...;                # As appropriate
	 *  - return->_fnode_file_ mf_parts      = NULL;               # Or `MFILE_PARTS_ANONYMOUS' if that fits better. (Note that for `fflatdirnode's, this _MUST_ be `NULL')
	 *  - return->_fnode_file_ mf_blockshift = dir->mf_blockshift; # Probably...
	 *  - return->_fnode_file_ mf_flags      = ... & (MFILE_F_READONLY | MFILE_F_NOUSRMMAP |    # directories require `MFILE_F_FIXEDFILESIZE', and should
	 *                                                MFILE_F_NOUSRIO | MFILE_F_FIXEDFILESIZE | # probably also have `MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO'
	 *                                                MFILE_FM_ATTRREADONLY);
	 *  - return->_fnode_file_ mf_filesize   = S_ISDIR(info->mkf_fmode) ? (pos_t)-1 : (pos_t)...;
	 *  - return->fn_ino                     = <unallocated>;      # FS-specific, inode number for non-allocated files (later allocated in `fdnx_allocfile' or `fdnx_writedir')
	 *  - return->*                          = ...;                # Any fields from sub-classes of `fnode'
	 * The caller of this function will do the following additional init:
	 *  - return->_fnode_file_ mf_refcnt     = 1 + ...;   # +1: MFILE_FN_GLOBAL_REF
	 *  - return->_fnode_file_ mf_flags     |= MFILE_FN_GLOBAL_REF;
	 *  - return->_fnode_file_ mf_flags     |= dir->mf_flags & (MFILE_F_READONLY | MFILE_F_NOATIME | MFILE_F_NOMTIME);
	 *  - return->_fnode_file_ mf_lock       = ATOMIC_RWLOCK_INIT;
	 *  - return->_fnode_file_ mf_initdone   = SIG_INIT;
	 *  - return->_fnode_file_ mf_lockops    = SLIST_HEAD_INITIALIZER(~);
	 *  - return->_fnode_file_ mf_changed    = SLIST_HEAD_INITIALIZER(~);
	 *  - return->_fnode_file_ mf_part_amask = MAX(PAGESIZE, 1 << mf_blockshift) - 1;
	 *  - return->_fnode_file_ mf_trunclock  = 0;
	 *  - return->_fnode_file_ mf_atime      = info->mkf_creat.c_atime;
	 *  - return->_fnode_file_ mf_mtime      = info->mkf_creat.c_mtime;
	 *  - return->_fnode_file_ mf_ctime      = info->mkf_creat.c_ctime;
	 *  - return->fn_nlink                   = 1;
	 *  - return->fn_mode                    = info->mkf_fmode;
	 *  - return->fn_uid                     = info->mkf_creat.c_owner;
	 *  - return->fn_gid                     = info->mkf_creat.c_group;
	 *  - return->fn_super                   = incref(dir->_fdirnode_node_ fn_super);
	 *  - return->fn_changed                 = LIST_ENTRY_UNBOUND_INITIALIZER;
	 *  - return->fn_supent                  = ...;    # By adding to the superblock's node-tree (or marking as unbound)
	 *  - return->fn_allnodes                = ...;    # via `fnode_init_addtoall()'
	 * @return: * : The newly allocated (and partially initialized) file.
	 * @throw: E_FSERROR_UNSUPPORTED_OPERATION: Filesystem doesn't support `info->mkf_fmode & S_IFMT' */
	ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct fnode *
	(KCALL *fdnx_mkfile)(struct fflatdirnode *__restrict self,
	                     struct fmkfile_info const *__restrict info)
			THROWS(E_BADALLOC, E_IOERROR, E_FSERROR_UNSUPPORTED_OPERATION);

	/* [0..1]
	 * - Allocate  a new flat-directory-entry for a given `file' returned by `fdnx_mkfile()'
	 *   This operator is optional, and if not  implemented will be substituted by a  direct
	 *   allocation of a `struct fflatdirent' object (using `fflatdirent_ops' for operators)
	 * - This operator is also used in the implementation of rename() operations.
	 * - If appropriate, the _CALLER_ will increment `file->fn_nlink'!
	 *
	 * This operator must allocate+initialize the returned entry:
	 *  - return->fde_ent.fd_ops = ...;  # As appropriate for sub-classes (usually `fflatdirent_ops')
	 *  - return->*              = ...;  # Any fields from sub-classes of `fflatdirent'
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
	ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) struct fflatdirent *
	(KCALL *fdnx_mkent)(struct fflatdirnode *__restrict self,
	                    struct fmkfile_info const *__restrict info,
	                    struct fnode *__restrict file)
			THROWS(E_BADALLOC, E_IOERROR);

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
	NONNULL((1, 2, 3)) void
	(KCALL *fdnx_allocfile)(struct fflatdirnode *__restrict self,
	                        struct fflatdirent *__restrict ent,
	                        struct fnode *__restrict file)
			THROWS(E_BADALLOC, E_IOERROR);

	/* [0..1]
	 * Following deletion of `deleted_ent', the nlink counter of `file' reached `0'.
	 * As the result of this,  this operator is invoked  for the purpose of  freeing
	 * any remaining on-disk data of `file'.
	 *
	 * At the point at which this operator is invoked, `self' will have already been
	 * marked as deleted
	 *
	 * Used for:
	 *   - FAT:  Free the cluster chain used for backing data of `file'
	 *   - EXT2: Free file data, followed by deallocating the on-disk INode object
	 *   - ...
	 *
	 * Even if this operator returns with an exception, `deleted_ent' will not be
	 * re-established, and `file->fn_nlink' will remain at `0'. Exactly what this
	 * means  for on-disk data is filesystem-specific, but it probably means that
	 * there's now a minor filesystem inconsistency.
	 *
	 * Note that unlike `fdnx_allocfile()', this operator is _NOT_ invoked  while
	 * holding any sort of lock to `self'! Instead, it can be invoked as a stand-
	 * alone function. */
	NONNULL((1, 2, 3)) void
	(KCALL *fdnx_deletefil)(struct fflatdirnode *__restrict self,
	                        struct fflatdirent *__restrict deleted_ent,
	                        struct fnode *__restrict file)
			THROWS(E_IOERROR);

	/* [0..1][lock(WRITE(oldparent->fdn_data.fdd_lock) &&
	 *             WRITE(newparent->fdn_data.fdd_lock))]
	 * Optional callback invoked  when the parent  of this directory  changes.
	 * May be used to update on-disk meta-data as present on some filesystems.
	 *
	 * Even if this operator returns with an exception, a rename is not aborted. */
	NONNULL((1, 2, 3)) void
	(KCALL *fdnx_changeparent)(struct fflatdirnode *__restrict self,
	                           struct fflatdirnode *__restrict oldparent,
	                           struct fflatdirnode *__restrict newparent)
			THROWS(E_IOERROR);

	/* More operators go here. */
};


struct fflatdirnode_ops {
	struct fdirnode_ops      fdno_dir;  /* Directory operators */
	struct fflatdirnode_xops fdno_flat; /* Flat directory operators */
};

/* Default operators for `struct fflatdirnode'-derived directories. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fflatdirnode_v_destroy)(struct mfile *__restrict self);
FUNDEF WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
fflatdirnode_v_lookup(struct fdirnode *__restrict self,
                      struct flookup_info *__restrict info)
		THROWS(E_BADALLOC, E_IOERROR);
/* NOTE: `fflatdirnode_v_enum()' fixes the  deleted-file problem by  searching
 *       though the directory for the next dirent with a position >= any entry
 *       that got deleted.
 *       Other than that, seekdir() addressing uses `fde_pos', with readdir()
 *       rounding up to the nearest  existing entry with a starting  position
 *       that is >= the seek'd address. (SEEK_END is relative to the fde_pos+
 *       fde_size of the last directory entry) */
FUNDEF NONNULL((1)) void KCALL
fflatdirnode_v_enum(struct fdirenum *__restrict result);
FUNDEF WUNUSED NONNULL((1, 2)) unsigned int KCALL
fflatdirnode_v_mkfile(struct fdirnode *__restrict self,
                      struct fmkfile_info *__restrict info)
		THROWS(E_BADALLOC, E_IOERROR, E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL,
		       E_FSERROR_READONLY, E_FSERROR_TOO_MANY_HARD_LINKS,
		       E_FSERROR_UNSUPPORTED_OPERATION);
FUNDEF WUNUSED NONNULL((1, 2, 3)) unsigned int KCALL
fflatdirnode_v_unlink(struct fdirnode *__restrict self,
                      struct fdirent *__restrict entry,
                      struct fnode *__restrict file)
		THROWS(E_BADALLOC, E_IOERROR, E_FSERROR_DIRECTORY_NOT_EMPTY,
		       E_FSERROR_READONLY);
FUNDEF WUNUSED NONNULL((1, 2)) unsigned int KCALL
fflatdirnode_v_rename(struct fdirnode *__restrict self,
                      struct frename_info *__restrict info)
		THROWS(E_BADALLOC, E_IOERROR, E_FSERROR_ILLEGAL_PATH,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY);


struct fflatdir_bucket {
	struct fflatdirent *ffdb_ent; /* [0..1] Directory entry, internal-stub for deleted, or NULL for sentinel */
};


/* Flags for `struct fflatdirdata::fdd_flags' */
#define FFLATDIR_F_NORMAL         0x0000 /* Normal flags */
#define FFLATDIR_F_EOF            0x0001 /* EOF was reached (`fdnx_readdir(this, fflatdirent_endaddr(TAILQ_LAST(&fdd_bypos))) == NULL') */
#define FFLATDIR_F_GAP_NOTLARGEST 0x0002 /* `fdd_biggest_gap' may not necessarily be the largest gap. */

struct fflatdirdata {
	struct shared_rwlock         fdd_lock;        /* Lock for directory data. */
	struct REF fflatdirent_tailq fdd_bypos;       /* [0..n][lock(fdd_lock)] List of files sorted by position in directory  stream.
	                                               * The files in this list are _IDENTICAL_ to those in `fdd_fileslist'. This list
	                                               * is simply an alternative way of looking at the contents of the directory. */
	pos_t                        fdd_biggest_gap; /* [lock(fdd_lock)] Size of the biggest gap between directory entries in `fdd_bypos'
	                                               * Used during file creation to pick between searching for a suitable gap to put new
	                                               * files, or appending them at the end of the directory. */
	struct fflatdirent          *fdd_biggest_suc; /* [lock(fdd_lock)][1..1][valid_if(fdd_biggest_gap != 0)] Successor after `fdd_biggest_gap' */
	uintptr_t                    fdd_flags;       /* [lock(fdd_lock)] */
	size_t                       fdd_filessize;   /* [lock(fdd_lock)] Amount of used (non-NULL and non-deleted) directory entries */
	size_t                       fdd_filesused;   /* [lock(fdd_lock)] Amount of (non-NULL) directory entries */
	size_t                       fdd_filesmask;   /* [lock(fdd_lock)] Hash-mask for `p_cldlist' */
	struct fflatdir_bucket      *fdd_fileslist;   /* [1..fdd_filesmask+1][owned_if(!= fflatdir_empty_buckets)]
	                                               * [lock(fdd_lock)] Hash-vector  of  files in  this directory.
	                                               * Elements may no longer be added if `MFILE_F_DELETED' is set */
};

/* Hash-vector iteration helper macros */
#define fflatdirent_hashof(self)       ((self)->fde_ent.fd_hash)
#define fflatdirent_hashnx(i, perturb) ((i) = (((i) << 2) + (i) + (perturb) + 1), (perturb) >>= 5)

/* Empty hash-vector */
DATDEF struct fflatdir_bucket const _fflatdir_empty_buckets[1] ASMNAME("fflatdir_empty_buckets");
#define fflatdir_empty_buckets ((struct fflatdir_bucket *)_fflatdir_empty_buckets)

#define fflatdirdata_init(self)                   \
	(shared_rwlock_init(&(self)->fdd_lock),       \
	 (self)->fdd_files = __NULLPTR,               \
	 TAILQ_INIT(&(self)->fdd_bypos),              \
	 (self)->fdd_biggest_gap = 0,                 \
	 (self)->fdd_flags       = FFLATDIR_F_NORMAL, \
	 (self)->fdd_filessize   = 0,                 \
	 (self)->fdd_filesused   = 0,                 \
	 (self)->fdd_filesmask   = 0,                 \
	 (self)->fdd_fileslist   = fflatdir_empty_buckets)
#define fflatdirdata_cinit(self)                              \
	(shared_rwlock_cinit(&(self)->fdd_lock),                  \
	 __hybrid_assert((self)->fdd_files == __NULLPTR),         \
	 __hybrid_assert(TAILQ_EMPTY(&(self)->fdd_bypos)),        \
	 __hybrid_assert((self)->fdd_biggest_gap == 0),           \
	 __hybrid_assert((self)->fdd_flags == FFLATDIR_F_NORMAL), \
	 __hybrid_assert((self)->fdd_filessize == 0),             \
	 __hybrid_assert((self)->fdd_filesused == 0),             \
	 __hybrid_assert((self)->fdd_filesmask == 0),             \
	 (self)->fdd_fileslist = fflatdir_empty_buckets)

/* Finalize the given flat directory data container. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fflatdirdata_fini)(struct fflatdirdata *__restrict self);

/* Helper functions for adding/removing directory entries  to the files list of  `self'
 * These functions _ONLY_ modify `fdd_fileslist' and friends; the caller is responsible
 * for `fdd_bypos', as well as to be holding a lock to `self->fdn_data.fdd_lock'. */
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL fflatdirnode_fileslist_removeent)(struct fflatdirnode *__restrict self, struct fflatdirent *__restrict ent);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL fflatdirnode_fileslist_insertent)(struct fflatdirnode *__restrict self, struct fflatdirent *__restrict ent);
FUNDEF NOBLOCK WUNUSED NONNULL((1, 2)) __BOOL NOTHROW(FCALL fflatdirnode_fileslist_tryinsertent)(struct fflatdirnode *__restrict self, struct fflatdirent *__restrict ent);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL fflatdirnode_fileslist_rehash_after_remove)(struct fflatdirnode *__restrict self);
FUNDEF NONNULL((1)) void FCALL fflatdirnode_fileslist_rehash_before_insert(struct fflatdirnode *__restrict self) THROWS(E_BADALLOC);

/* Lookup the named entry, returning `NULL' if not found. */
FUNDEF NOBLOCK NONNULL((1, 2)) struct fflatdirent *FCALL
fflatdirnode_fileslist_lookup(struct fflatdirnode *__restrict self,
                              struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT);
/* Remove the named entry, returning `NULL' if not found.
 * Same as `fflatdirnode_fileslist_lookup' + `fflatdirnode_fileslist_removeent' */
FUNDEF NOBLOCK NONNULL((1, 2)) struct fflatdirent *FCALL
fflatdirnode_fileslist_remove(struct fflatdirnode *__restrict self,
                              struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT);





/* Helpers for accessing `fdd_lock' */
#define _fflatdirdata_reap(self)      (void)0
#define fflatdirdata_reap(self)       (void)0
#define fflatdirdata_write(self)      shared_rwlock_write(&(self)->fdd_lock)
#define fflatdirdata_write_nx(self)   shared_rwlock_write_nx(&(self)->fdd_lock)
#define fflatdirdata_trywrite(self)   shared_rwlock_trywrite(&(self)->fdd_lock)
#define fflatdirdata_endwrite(self)   (shared_rwlock_endwrite(&(self)->fdd_lock), fflatdirdata_reap(self))
#define _fflatdirdata_endwrite(self)  shared_rwlock_endwrite(&(self)->fdd_lock)
#define fflatdirdata_read(self)       shared_rwlock_read(&(self)->fdd_lock)
#define fflatdirdata_read_nx(self)    shared_rwlock_read_nx(&(self)->fdd_lock)
#define fflatdirdata_tryread(self)    shared_rwlock_tryread(&(self)->fdd_lock)
#define _fflatdirdata_endread(self)   shared_rwlock_endread(&(self)->fdd_lock)
#define fflatdirdata_endread(self)    (void)(shared_rwlock_endread(&(self)->fdd_lock) && (fflatdirdata_reap(self), 0))
#define _fflatdirdata_end(self)       shared_rwlock_end(&(self)->fdd_lock)
#define fflatdirdata_end(self)        (void)(shared_rwlock_end(&(self)->fdd_lock) && (fflatdirdata_reap(self), 0))
#define fflatdirdata_upgrade(self)    shared_rwlock_upgrade(&(self)->fdd_lock)
#define fflatdirdata_upgrade_nx(self) shared_rwlock_upgrade_nx(&(self)->fdd_lock)
#define fflatdirdata_tryupgrade(self) shared_rwlock_tryupgrade(&(self)->fdd_lock)
#define fflatdirdata_downgrade(self)  shared_rwlock_downgrade(&(self)->fdd_lock)
#define fflatdirdata_reading(self)    shared_rwlock_reading(&(self)->fdd_lock)
#define fflatdirdata_writing(self)    shared_rwlock_writing(&(self)->fdd_lock)
#define fflatdirdata_canread(self)    shared_rwlock_canread(&(self)->fdd_lock)
#define fflatdirdata_canwrite(self)   shared_rwlock_canwrite(&(self)->fdd_lock)


struct fflatdirnode
#ifndef __WANT_FS_INLINE_STRUCTURES
    : fdirnode                    /* Underlying directory-node */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct fdirnode     fdn_dir;  /* Underlying directory-node */
#define _fflatdirnode_dir_     fdn_dir.
#define _fflatdirnode_asdir(x) &(x)->fdn_dir
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _fflatdirnode_dir_     /* nothing */
#define _fflatdirnode_asdir(x) x
#endif /* !__WANT_FS_INLINE_STRUCTURES */
	struct fflatdirdata fdn_data; /* Flat directory node data. */
};


/* Helper conversion functions */
#define fdirnode_asflat(self) ((struct fflatdirnode *)(self))
#define fnode_asflatdir(self) fdirnode_asflat(fnode_asdir(self))
#define mfile_asflatdir(self) fdirnode_asflat(mfile_asdir(self))


/* Return a pointer to directory-node operators of `self' */
#define fflatdirnode_getops(self)                                                                                                          \
	__COMPILER_CONTAINER_OF(__COMPILER_REQTYPE(struct fflatdirnode const *, self)->_fflatdirnode_dir_ _fdirnode_node_ _fnode_file_ mf_ops, \
	                        struct fflatdirnode_ops, fdno_dir.dno_node.no_file)
#define _fflatdirnode_assert_ops_(ops) \
	_fdirnode_assert_ops_(&(ops)->fdno_dir)

/* Check if a given `struct fflatdirnode *self' is a fsuper. */
#define fflatdirnode_issuper(self) (&(self)->_fflatdirnode_dir_ _fdirnode_node_ fn_super->fs_root == _fflatdirnode_asdir(self))
#define fflatdirnode_assuper(self) __COMPILER_CONTAINER_OF(self, struct fflatsuper, ffs_super.fs_root)


/* Helpers for accessing `fdn_data.fdd_lock' */
#define _fflatdirnode_reap(self)      _fflatdirdata_reap(&(self)->fdn_data)
#define fflatdirnode_reap(self)       fflatdirdata_reap(&(self)->fdn_data)
#define fflatdirnode_write(self)      fflatdirdata_write(&(self)->fdn_data)
#define fflatdirnode_write_nx(self)   fflatdirdata_write_nx(&(self)->fdn_data)
#define fflatdirnode_trywrite(self)   fflatdirdata_trywrite(&(self)->fdn_data)
#define fflatdirnode_endwrite(self)   fflatdirdata_endwrite(&(self)->fdn_data)
#define _fflatdirnode_endwrite(self)  _fflatdirdata_endwrite(&(self)->fdn_data)
#define fflatdirnode_read(self)       fflatdirdata_read(&(self)->fdn_data)
#define fflatdirnode_read_nx(self)    fflatdirdata_read_nx(&(self)->fdn_data)
#define fflatdirnode_tryread(self)    fflatdirdata_tryread(&(self)->fdn_data)
#define _fflatdirnode_endread(self)   _fflatdirdata_endread(&(self)->fdn_data)
#define fflatdirnode_endread(self)    fflatdirdata_endread(&(self)->fdn_data)
#define _fflatdirnode_end(self)       _fflatdirdata_end(&(self)->fdn_data)
#define fflatdirnode_end(self)        fflatdirdata_end(&(self)->fdn_data)
#define fflatdirnode_upgrade(self)    fflatdirdata_upgrade(&(self)->fdn_data)
#define fflatdirnode_upgrade_nx(self) fflatdirdata_upgrade_nx(&(self)->fdn_data)
#define fflatdirnode_tryupgrade(self) fflatdirdata_tryupgrade(&(self)->fdn_data)
#define fflatdirnode_downgrade(self)  fflatdirdata_downgrade(&(self)->fdn_data)
#define fflatdirnode_reading(self)    fflatdirdata_reading(&(self)->fdn_data)
#define fflatdirnode_writing(self)    fflatdirdata_writing(&(self)->fdn_data)
#define fflatdirnode_canread(self)    fflatdirdata_canread(&(self)->fdn_data)
#define fflatdirnode_canwrite(self)   fflatdirdata_canwrite(&(self)->fdn_data)


/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_fflatdirnode_dir_ _fdirnode_node_ _fnode_file_ mf_atime
 *  - self->_fflatdirnode_dir_ _fdirnode_node_ _fnode_file_ mf_mtime
 *  - self->_fflatdirnode_dir_ _fdirnode_node_ _fnode_file_ mf_ctime
 *  - self->_fflatdirnode_dir_ _fdirnode_node_ fn_uid
 *  - self->_fflatdirnode_dir_ _fdirnode_node_ fn_gid
 *  - self->_fflatdirnode_dir_ _fdirnode_node_ fn_allnodes
 *  - self->_fflatdirnode_dir_ _fdirnode_node_ fn_supent
 *  - self->_fflatdirnode_dir_ _fdirnode_node_ fn_nlink  (to `1')
 *  - self->_fflatdirnode_dir_ _fdirnode_node_ fn_ino
 *  - self->_fflatdirnode_dir_ _fdirnode_node_ fn_mode (with something or'd with S_IFDIR)
 * @param: struct fflatdirnode     *self:   Directory node to initialize.
 * @param: struct fflatdirnode_ops *ops:    Directory operators.
 * @param: struct fflatdirnode     *parent: Parent directory. */
#define _fflatdirnode_init(self, ops, parent)                                                  \
	(_fdirnode_init(_fflatdirnode_asdir(self), &(ops)->fdno_dir, _fflatdirnode_asdir(parent)), \
	 fflatdirdata_init(&(self)->fdn_data))
#define _fflatdirnode_cinit(self, ops, super)                                                   \
	(_fdirnode_cinit(_fflatdirnode_asdir(self), &(ops)->fdno_dir, _fflatdirnode_asdir(parent)), \
	 fflatdirdata_cinit(&(self)->fdn_data))
/* Finalize a partially initialized `struct fflatdirnode' (as initialized by `_fflatdirnode_init()') */
#define _fflatdirnode_fini(self) \
	_fdirnode_fini(_fflatdirnode_asdir(self))




/************************************************************************/
/* Flat superblock                                                      */
/************************************************************************/
struct fflatsuper_ops {
	/* More operators go here. */

	/* [1..1][lock(READ(dir->fdn_data.fdd_lock))]
	 * Allocate a new file-node object for `ent' in `dir'
	 * This function may assume:
	 *  - !fflatdirent_wasdeleted(ent);
	 * This function must allocate+initialize the returned node:
	 *  - return->_fnode_file_ mf_ops        = ...;                # As appropriate
	 *  - return->_fnode_file_ mf_parts      = NULL;               # Or `MFILE_PARTS_ANONYMOUS' if that fits better. (Note that for `fflatdirnode's, this _MUST_ be `NULL')
	 *  - return->_fnode_file_ mf_blockshift = dir->mf_blockshift; # Probably...
	 *  - return->_fnode_file_ mf_flags      = ... & (MFILE_F_READONLY | MFILE_F_NOUSRMMAP |    # directories require `MFILE_F_FIXEDFILESIZE', and should
	 *                                                MFILE_F_NOUSRIO | MFILE_F_FIXEDFILESIZE | # probably also have `MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO'
	 *                                                MFILE_FM_ATTRREADONLY);
	 *  - return->_fnode_file_ mf_filesize   = ...;                # As read from disk
	 *  - return->_fnode_file_ mf_atime      = ...;                # As read from disk
	 *  - return->_fnode_file_ mf_mtime      = ...;                # As read from disk
	 *  - return->_fnode_file_ mf_ctime      = ...;                # As read from disk
	 *  - return->fn_nlink                   = ...;                # As read from disk
	 *  - return->fn_mode                    = ...;                # As read from disk  (S_IFMT must match `DTTOIF(ent->fde_ent.fd_type)')
	 *  - return->fn_uid                     = ...;                # As read from disk
	 *  - return->fn_gid                     = ...;                # As read from disk
	 *  - return->*                          = ...;                # Any fields from sub-classes of `fnode'
	 * The caller of this function will do the following additional init:
	 *  - return->_fnode_file_ mf_refcnt     = 2;      # +1: MFILE_FN_GLOBAL_REF, +1: return of `fflatsuper_opennode'
	 *  - return->_fnode_file_ mf_flags     |= MFILE_FN_GLOBAL_REF;
	 *  - return->_fnode_file_ mf_flags     |= dir->mf_flags & (MFILE_F_READONLY | MFILE_F_NOATIME | MFILE_F_NOMTIME);
	 *  - return->_fnode_file_ mf_lock       = ATOMIC_RWLOCK_INIT;
	 *  - return->_fnode_file_ mf_initdone   = SIG_INIT;
	 *  - return->_fnode_file_ mf_lockops    = SLIST_HEAD_INITIALIZER(~);
	 *  - return->_fnode_file_ mf_changed    = SLIST_HEAD_INITIALIZER(~);
	 *  - return->_fnode_file_ mf_part_amask = MAX(PAGESIZE, 1 << mf_blockshift) - 1;
	 *  - return->_fnode_file_ mf_trunclock  = 0;
	 *  - return->fn_ino                     = ent->fde_ent.fd_ino;
	 *  - return->fn_super                   = incref(dir->_fdirnode_node_ fn_super);
	 *  - return->fn_changed                 = LIST_ENTRY_UNBOUND_INITIALIZER;
	 *  - return->fn_supent                  = ...;    # By adding to the superblock's node-tree (or marking as unbound)
	 *  - return->fn_allnodes                = ...;    # via `fnode_init_addtoall()'
	 * @return: * : The newly allocated (and partially initialized) node. */
	ATTR_RETNONNULL WUNUSED NONNULL((1)) struct fnode *
	(KCALL *ffso_makenode)(struct fflatsuper *__restrict self,
	                       struct fflatdirent *__restrict ent,
	                       struct fflatdirnode *__restrict dir)
			THROWS(E_BADALLOC, E_IOERROR);

	struct fsuper_ops        ffso_super; /* Super operators */
	struct fflatdirnode_xops ffso_flat;  /* Flat root directory operators */
};


/* Flags for `struct fflatsuper::ffs_features' */
#define FFLATSUPER_FEAT_NORMAL               0x0000 /* No special features. */
#define FFLATSUPER_FEAT_WRITEDIR_CHANGES_INO 0x0001 /* The `fdnx_writedir' operator of directories may alter the INode number of a file. */

struct fflatsuper {
	/* flat-superblock-specific data goes here. */
	uintptr_t           ffs_features; /* Set of `FFLATSUPER_FEAT_*' */
	struct fsuper       ffs_super;    /* Underlying superblock. */
	struct fflatdirdata ffs_rootdata; /* Directory data for the filesystem root. */
};


/* Helper conversion functions */
#define fsuper_asflat(self)        COMPILER_CONTAINER_OF(self, struct fflatsuper, ffs_super)
#define fdirnode_asflatsuper(self) COMPILER_CONTAINER_OF(self, struct fflatsuper, ffs_super.fs_root)
#define fnode_asflatsuper(self)    fdirnode_asflatsuper(fnode_asdir(self))
#define mfile_asflatsuper(self)    fdirnode_asflatsuper(mfile_asdir(self))

/* Return the root directory of a given `struct fflatsuper' */
#define fflatsuper_getroot(self)   fdirnode_asflat(&(self)->ffs_super.fs_root)

/* Return a pointer to flat-super operators of `self' */
#define fflatsuper_getops(self)                                                                                                         \
	__COMPILER_CONTAINER_OF(__COMPILER_REQTYPE(struct fflatsuper const *, self)->ffs_super.fs_root._fdirnode_node_ _fnode_file_ mf_ops, \
	                        struct fflatsuper_ops, ffso_super.so_fdir.dno_node.no_file)



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
WUNUSED REF struct fnode *
fflatsuper_opennode(struct fflatdirnode *__restrict dir,
                    struct fflatdirent *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC);
#else /* __INTELLISENSE__ */
#define fflatsuper_opennode(dir, self) \
	fflatdirent_v_opennode(&(self)->fde_ent, _fflatdirnode_asdir(dir))
#endif /* !__INTELLISENSE__ */



DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FLAT_H */
