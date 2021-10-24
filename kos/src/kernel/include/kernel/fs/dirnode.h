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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_DIRNODE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_DIRNODE_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_FS
#include <fs/node.h>
#else /* !CONFIG_USE_NEW_FS */
#include <kernel/fs/node.h>
#include <kernel/types.h>

#include <asm/os/fcntl.h> /* __AT_DOSPATH */
#include <asm/os/stdio.h> /* __RENAME_NOREPLACE, __RENAME_EXCHANGE */
#include <bits/os/timespec.h>
#include <kos/io.h> /* readdir_mode_t */

#if !defined(AT_DOSPATH) && defined(__AT_DOSPATH)
#define AT_DOSPATH __AT_DOSPATH
#endif /* !AT_DOSPATH && __AT_DOSPATH */
#if !defined(AT_RENAME_NOREPLACE) && defined(__RENAME_NOREPLACE)
#define AT_RENAME_NOREPLACE __RENAME_NOREPLACE
#endif /* !AT_RENAME_NOREPLACE && __RENAME_NOREPLACE */
#if !defined(AT_RENAME_EXCHANGE) && defined(__RENAME_EXCHANGE)
#define AT_RENAME_EXCHANGE __RENAME_EXCHANGE
#endif /* !AT_RENAME_EXCHANGE && __RENAME_EXCHANGE */
#if !defined(AT_RENAME_MOVETODIR) && defined(__RENAME_MOVETODIR)
#define AT_RENAME_MOVETODIR __RENAME_MOVETODIR
#endif /* !AT_RENAME_MOVETODIR && __RENAME_MOVETODIR */

#ifdef __CC__
DECL_BEGIN

struct fdirent;
struct fdirnode;

struct fdirenum;
struct fdirenum_ops {
	/* [1..1] Finalization callback. */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (KCALL *deo_fini)(struct fdirenum *__restrict self);

	/* [1..1] Directory reader callback.
	 * When end-of-file has been reached, `0' is returned.
	 * NOTE: This function mustn't enumerate the `.' and `..' entires! */
	NONNULL((1)) size_t
	(KCALL *deo_readdir)(struct fdirenum *__restrict self, USER CHECKED struct dirent *buf,
	                     size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode)
			THROWS(...);

	/* [1..1] Directory stream seeking.
	 * This callback must at least be capable of  `offset=0,whence=SEEK_SET',
	 * which may be used to rewind the directory and re-read all entries that
	 * had already been read before. (s.a. `rewinddir(3)')
	 * Other  than this, it is undefined what an absolute `offset' actually
	 * represents.  - It may be an index (seeking to the n'th entry), or an
	 * absolute position within the containing directory file, or something
	 * entirety different. (multiple directory entires are even allowed  to
	 * share the same  ~position~, meaning that  reading the position,  and
	 * later restoring it is _not_ a  usage-case that has to be  supported)
	 * NOTE: This function mustn't enumerate the `.' and `..' entires!
	 * @return: * : The new position (however that may be defined) within
	 *              the directory stream.
	 * @throw: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE:whence: [...] */
	NONNULL((1)) pos_t
	(KCALL *deo_seekdir)(struct fdirenum *__restrict self,
	                     off_t offset, unsigned int whence)
			THROWS(...);
};

#define FDIRENUM_HEADER                                               \
	struct fdirenum_ops const *de_ops; /* [1..1][const] Operators. */ \
	REF struct fdirnode       *de_dir; /* [1..1][const] Directory being enumerated. */


struct fdirenum {
	FDIRENUM_HEADER
	void *de_data[14]; /* Filesystem-specific data. */
};

/* Helper macros for operating with `struct fdirenum' */
#define fdirenum_init(self, ops, dir) \
	((self)->de_ops = (ops),          \
	 (self)->de_dir = mfile_asdir(incref(dir)))
#define fdirenum_fini(self)             \
	((*(self)->de_ops->deo_fini)(self), \
	 decref_unlikely((self)->de_dir))
#define fdirenum_readdir(self, buf, bufsize, readdir_mode, mode) \
	(*(self)->de_ops->deo_readdir)(self, buf, bufsize, readdir_mode, mode)
#define fdirenum_seekdir(self, offset, whence) \
	(*(self)->de_ops->deo_seekdir)(self, offset, whence)

/* Feed   directory  entry  information  (the  `feed_d_*'  arguments)
 * into `buf' as requested by  `readdir_mode' ('.' and '..'  handling
 * is  _NOT_ done by  this function), and  return the expected return
 * value, or its bitwise-inverse. When a positive number is returned,
 * the fed directory  entry should be  consumed (read: yielded).  But
 * when a negative number is returned, the directory entry should not
 * be  consumed, and the caller should forward the bitwise inverse to
 * their caller.
 * @return: >= 0: Advance directory position to next entry and re-return this value.
 * @return: <  0: Keep current directory position and re-return bitwise inverse ('~') of this value. */
FUNDEF WUNUSED ssize_t FCALL
fdirenum_feedent(USER CHECKED struct dirent *buf,
                 size_t bufsize, readdir_mode_t readdir_mode,
                 ino_t feed_d_ino, unsigned char feed_d_type,
                 u16 feed_d_namlen, USER CHECKED char const *feed_d_name)
		THROWS(E_SEGFAULT);





/* Special value for uncalculated hash */
#define FLOOKUP_INFO_HASH_UNSET 0

/* Info descriptor for looking up directory entries by-name. */
struct flookup_info {
	CHECKED USER /*utf-8*/ char const *flu_name;    /* [?..flu_namelen] Name for the new file. */
	uintptr_t                          flu_hash;    /* Hash for `mkf_name' (s.a. `fdirent_hash()') or
	                                                 * `FLOOKUP_INFO_HASH_UNSET'  if  not calculated. */
	u16                                flu_namelen; /* Length of `mkf_name' */
	u16                               _flu_pad;     /* ... */
	atflag_t                           flu_flags;   /* Set of `0 | AT_DOSPATH' (other flags are silently ignored) */
};

struct fcreatfile_info {
	uid_t                      c_owner;     /* [in] File owner */
	gid_t                      c_group;     /* [in] File group */
	struct timespec            c_atime;     /* [in] File access timestamp */
	struct timespec            c_mtime;     /* [in] File modified timestamp */
	struct timespec            c_ctime;     /* [in] File created timestamp */
	union {
		dev_t                  c_rdev;      /* [valid_if(S_ISDEV(mkf_fmode))][in] Referenced device. */
		struct {
			CHECKED USER /*utf-8*/ char const *s_text; /* [?..s_size][in] Symlink text. */
			size_t                             s_size; /* [in] Symlink text length (in characters; excluding trailing \0). */
		}                      c_symlink;   /* [valid_if(S_ISLNK(mkf_fmode))] Symlink text. */
	};
};

/* Info descriptor for: creat(2), mkdir(2), mknod(2), symlink(2) and link(2) */
struct fmkfile_info {
	union {
		struct {
			CHECKED USER /*utf-8*/ char const *mkf_name;    /* [?..mkf_namelen][in] Name for the new file. */
			uintptr_t                          mkf_hash;    /* [in] Hash for `mkf_name' (s.a. `fdirent_hash()') (or `FLOOKUP_INFO_HASH_UNSET') */
			u16                                mkf_namelen; /* [in] Length of `mkf_name' */
			u16                               _mkf_pad;     /* ... */
			atflag_t                           mkf_flags;   /* [in] Set of `0 | AT_DOSPATH' */
		};
		struct flookup_info            mkf_lookup_info;     /* [in] Lookup info for the new file being created. */
	};
	REF struct fdirent                *mkf_dent;    /* [1..1][out] Directory entry for the new file (s.a. `dno_lookup') */
	mode_t                             mkf_fmode;   /* [in] File  type & access  permissions for the new  file-node. If a hard-
	                                                 * link  should be created, this is field is set to ZERO. For this purpose,
	                                                 * node that all S_IF*-file-type-flags are non-zero, meaning you can simply
	                                                 * switch on this field and use `0' for hard-link. */
	union {
		REF struct fnode              *mkf_rnode;   /* [1..1][out] The newly constructed file-node. */
		REF struct fregnode           *mkf_rreg;    /* [1..1][out][valid_if(S_ISREG(mkf_fmode) || (mkf_fmode == 0 && fnode_isreg(mkf_hrdlnk.hl_node)))] */
		REF struct fdirnode           *mkf_rdir;    /* [1..1][out][valid_if(S_ISDIR(mkf_fmode) || (mkf_fmode == 0 && fnode_isdir(mkf_hrdlnk.hl_node)))] */
		REF struct flnknode           *mkf_rlnk;    /* [1..1][out][valid_if(S_ISLNK(mkf_fmode) || (mkf_fmode == 0 && fnode_islnk(mkf_hrdlnk.hl_node)))] */
		REF struct ffifonode          *mkf_rfifo;   /* [1..1][out][valid_if(S_ISFIFO(mkf_fmode) || (mkf_fmode == 0 && fnode_isfifo(mkf_hrdlnk.hl_node)))] */
		REF struct fsocknode          *mkf_rsock;   /* [1..1][out][valid_if(S_ISSOCK(mkf_fmode) || (mkf_fmode == 0 && fnode_issock(mkf_hrdlnk.hl_node)))] */
		REF struct fdevnode           *mkf_rdev;    /* [1..1][out][valid_if(S_ISDEV(mkf_fmode) || (mkf_fmode == 0 && fnode_isdevnode(mkf_hrdlnk.hl_node)))] */
	};
	union {
		struct {
			struct fnode              *hl_node;     /* [1..1][in] The file to which to create a hard-link. */
		}                      mkf_hrdlnk; /* [valid_if((mkf_fmode & S_IFMT) == 0)] Hardlink creation info. */
		struct fcreatfile_info mkf_creat;  /* [valid_if((mkf_fmode & S_IFMT) != 0)] File creation info. */
	};
};

/* Info descriptor for: rename(2) */
struct frename_info {
	union {
		struct {
			CHECKED USER /*utf-8*/ char const *frn_name;    /* [?..frn_namelen][in] Name for the new file. */
			uintptr_t                          frn_hash;    /* [in] Hash for `frn_name' (s.a. `fdirent_hash()') (or `FLOOKUP_INFO_HASH_UNSET') */
			u16                                frn_namelen; /* [in] Length of `frn_name' */
			u16                               _frn_pad;     /* ... */
			atflag_t                           frn_flags;   /* [in] Set of `0 | AT_DOSPATH | AT_RENAME_EXCHANGE' */
		};
		struct flookup_info             frn_lookup_info;    /* [in] Lookup info for the new file being created. */
	};
	/*OUT_REF*/ struct fnode           *frn_repfile; /* [0..1][in] The existing file that should be replaced with `frn_file',
	                                                  *            or `NULL' if no pre-existing file should be replaced,  and
	                                                  *            only new files should be created (mandatory field when the
	                                                  *            `AT_RENAME_EXCHANGE' flag was given).
	                                                  * [0..1][out_if(FDIRNODE_RENAME_EXISTS)]. */
	/*OUT_REF*/ struct fdirent         *frn_dent;    /* [0..1][out] New directory entry for the file (or `frn_repfile' for `FDIRNODE_RENAME_EXISTS') */
	struct fnode                       *frn_file;    /* [1..1][in] The file that should be renamed. */
	struct fdirent                     *frn_oldent;  /* [1..1][in] Directory of `frn_file' in `frn_olddir'
	                                                  * Under `AT_RENAME_EXCHANGE', this is [in|out]  REF. */
	struct fdirnode                    *frn_olddir;  /* [1..1][in] Old containing directory. (Part of the same superblock!)
	                                                  * NOTE: The new  directory  is  guarantied  not to  be  a  child  of  this
	                                                  *       directory! (this must be asserted by the caller of `dno_rename()') */
};




/* Return values for `dno_mkfile' */
#define FDIRNODE_MKFILE_SUCCESS 0 /* Success.  `info'  is  modified   like:
                                   * >> info->mkf_rnode = incref(NEW_FILE);
                                   * >> info->mkf_dent  = incref(DIRENT_OF(NEW_FILE)); */
#define FDIRNODE_MKFILE_EXISTS  1 /* Special case: the file `info->mkf_name' already exists. `info' is modified like:
                                   * >> info->mkf_rnode = incref(EXISTING_FILE);
                                   * >> info->mkf_dent  = incref(DIRENT_OF(EXISTING_FILE)); */


/* Return values for `dno_unlink' */
#define FDIRNODE_UNLINK_SUCCESS 0 /* Success */
#define FDIRNODE_UNLINK_DELETED 2 /* Error: The given `entry' was already deleted. (reload arguments & try again) */


/* Return values for `dno_rename' */
#define FDIRNODE_RENAME_SUCCESS 0 /* Success. `info' is modified like:
                                   * >> info->frn_dent = incref(NEW_DIRENT_OF(info->frn_file));
                                   * >> MARKED_AS_DELETED(info->frn_oldent);
                                   * >> if (info->frn_repfile) MARKED_AS_DELETED(DIRENT_OF(info->frn_repfile)); */
#define FDIRNODE_RENAME_EXISTS  1 /* Special case: the file `info->frn_name' already exists. `info' is modified like:
                                   * >> info->frn_repfile = incref(EXISTING_FILE);
                                   * >> info->frn_dent    = incref(NEW_DIRENT_OF(EXISTING_FILE)); */
#define FDIRNODE_RENAME_DELETED 2 /* Error: The given `info->frn_oldent' was deleted. (reload arguments & try again) */




struct fdirnode_ops {
	struct fnode_ops dno_node; /* FNode operators */

	/* [1..1] Lookup a directory entry within `self', given its name.
	 * @return: NULL: No entry exists that is matching the given name. */
	WUNUSED NONNULL((1, 2)) REF struct fdirent *
	(KCALL *dno_lookup)(struct fdirnode *__restrict self,
	                    struct flookup_info *__restrict info);

	/* [1..1] Construct a directory enumerator object in `*result'.
	 * This  function  must  initialize _all_  fields  of `*result'
	 * It  is undefined if files created or  deleted after the creation of an
	 * enumerator, will still be enumerated by said enumerator. It is however
	 * guarantied that all files created  before, and not deleted after  will
	 * always be enumerated.
	 * The caller of this function has already initialized:
	 *  - result->de_dir = incref(DIR);
	 * This function must initialize:
	 *  - result->de_ops = ...;          # FS-specific
	 *  - result->*      = ...;          # Additional fs-specific fields
	 * If this operator returns with an exception, the caller will decref()
	 * whatever directory  is stored  in  `result->de_dir' at  that  point. */
	NONNULL((1)) void
	(KCALL *dno_enum)(struct fdirenum *__restrict result);

	/* [0..1] Create  new files within a given directory.
	 * @throw: E_FSERROR_ILLEGAL_PATH:          `info->mkf_name' contains bad characters
	 * @throw: E_FSERROR_DISK_FULL:             Disk full
	 * @throw: E_FSERROR_READONLY:              Read-only filesystem
	 * @throw: E_FSERROR_TOO_MANY_HARD_LINKS:   ...
	 * @throw: E_FSERROR_UNSUPPORTED_OPERATION: The requested S_IFMT isn't supported.
	 * @return: * : One of `FDIRNODE_MKFILE_*'
	 *
	 * Implementation:
	 * >> REF struct fnode *newfil;
	 * >> REF struct fdirent *newent;
	 * >> REF struct fdirent *existing_ent;
	 * >> newfil = info->mkf_fmode ? ALLOCATE_FILE(info->mkf_fmode, &info->mkf_creat) : incref(info->mkf_hrdlnk.hl_node);
	 * >> // `newent' holds a reference to `newfil->fn_nlink'
	 * >> newent = ALLOCATE_NEW_DIRECTORY_ENTRY(newfil, info->mkf_name, info->mkf_namelen);
	 * >> existing_ent = LOOKUP_EXISTING_FILE(self, newent->fd_name);
	 * >> if (existing_ent) {
	 * >>     // WAS_DELETED() check is only needed if DELETED entries can still
	 * >>     // be looked up (as the result of them async-removoing themselves)
	 * >>     if (WAS_DELETED(existing_ent)) {
	 * >>         REMOVE_DIRECTORY_ENTRY(self, existing_ent);
	 * >>     } else {
	 * >>         info->mkf_dent  = incref(existing_ent);
	 * >>         info->mkf_rnode = incref(existing_ent->FILE);
	 * >>         return FDIRNODE_MKFILE_EXISTS;
	 * >>     }
	 * >> }
	 * >> INSERT_DIRECTORY_ENTRY(self, newent);
	 * >> info->mkf_dent  = incref(newent);
	 * >> info->mkf_rnode = incref(newfil);
	 * >> return FDIRNODE_MKFILE_SUCCESS; */
	WUNUSED NONNULL((1, 2)) unsigned int
	(KCALL *dno_mkfile)(struct fdirnode *__restrict self,
	                    struct fmkfile_info *__restrict info)
			THROWS(E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL,
			       E_FSERROR_READONLY, E_FSERROR_TOO_MANY_HARD_LINKS,
			       E_FSERROR_UNSUPPORTED_OPERATION);

	/* [0..1] Delete   the  specified  file  from  this  directory.
	 * This function is also responsible to update `file->fn_nlink'
	 * @throw: E_FSERROR_DIRECTORY_NOT_EMPTY: `file' is a non-empty directory.
	 * @throw: E_FSERROR_READONLY:            Read-only filesystem
	 * @return: * : One of `FDIRNODE_UNLINK_*'
	 *
	 * Implementation:
	 * >> if (WAS_DELETED(entry))
	 * >>     return FDIRNODE_UNLINK_DELETED;
	 * >> assert(entry->FILE == file);
	 * >> REMOVE_DIRECTORY_ENTRY(self, entry);
	 * >> MARK_DELETED(entry); */
	WUNUSED NONNULL((1, 2, 3)) unsigned int
	(KCALL *dno_unlink)(struct fdirnode *__restrict self,
	                    struct fdirent *__restrict entry,
	                    struct fnode *__restrict file)
			THROWS(E_FSERROR_DIRECTORY_NOT_EMPTY,
			       E_FSERROR_READONLY);

	/* [0..1] Rename/move the specified file from one location to  another.
	 * The caller must ensure that  `self' and `info->frn_olddir' are  part
	 * of the same filesystem, and (if `fnode_isdir(info->frn_file)'), that
	 * `self' isn't its child.
	 * @throw: E_FSERROR_ILLEGAL_PATH: `info->frn_name' contains bad characters
	 * @throw: E_FSERROR_DISK_FULL:    Disk full
	 * @throw: E_FSERROR_READONLY:     Read-only filesystem
	 * @return: * : One of `FDIRNODE_RENAME_*'
	 *
	 * Implementation:
	 * >> REF struct fdirent *newent;
	 * >> REF struct fdirent *existing_ent;
	 * >> REF struct fnode   *existing_fil;
	 * >> REF struct fdirent *repent = NULL;
	 * >> if (WAS_DELETED(info->frn_oldent))
	 * >>     return FDIRNODE_RENAME_DELETED;
	 * >> assert(info->frn_oldent->FILE == info->frn_file);
	 * >> newent       = ALLOCATE_NEW_DIRECTORY_ENTRY(info->frn_file, info->frn_name, info->frn_namelen);
	 * >> existing_ent = LOOKUP_EXISTING_FILE(self, newent->fd_name);
	 * >> existing_fil = NULL;
	 * >> if (existing_ent) {
	 * >>     // WAS_DELETED() check is only needed if DELETED entries can still
	 * >>     // be looked up (as the result of them async-removoing themselves)
	 * >>     if (WAS_DELETED(existing_ent)) {
	 * >>         REMOVE_DIRECTORY_ENTRY(self, existing_ent);
	 * >>         DBG_memset(&existing_ent, 0xcc, sizeof(existing_ent));
	 * >>     } else {
	 * >>         existing_fil = existing_ent->FILE;
	 * >>     }
	 * >> }
	 * >> if (info->frn_repfile != existing_fil) {
	 * >>     info->frn_dent    = xincref(existing_ent);
	 * >>     info->frn_repfile = xincref(existing_fil);
	 * >>     return FDIRNODE_RENAME_EXISTS;
	 * >> }
	 * >> if (info->frn_repfile != NULL) {
	 * >>     if (info->frn_flags & AT_RENAME_EXCHANGE) {
	 * >>         repent = ALLOCATE_NEW_DIRECTORY_ENTRY(info->frn_repfile,
	 * >>                                               info->frn_oldent->fd_name,
	 * >>                                               info->frn_oldent->fd_namelen);
	 * >>     }
	 * >>     REMOVE_DIRECTORY_ENTRY(self, existing_ent);
	 * >>     MARK_DELETED(existing_ent);
	 * >> }
	 * >> REMOVE_DIRECTORY_ENTRY(info->frn_olddir, info->frn_oldent);
	 * >> MARK_DELETED(info->frn_oldent);
	 * >> INSERT_DIRECTORY_ENTRY(self, newent);
	 * >> if (repent) {
	 * >>     INSERT_DIRECTORY_ENTRY(info->frn_olddir, repent);
	 * >>     decref_unlikely(info->frn_oldent);
	 * >>     info->frn_oldent = incref(repent);
	 * >> }
	 * >> info->frn_dent = incref(newent);
	 * >> return FDIRNODE_RENAME_SUCCESS; */
	WUNUSED NONNULL((1, 2)) unsigned int
	(KCALL *dno_rename)(struct fdirnode *__restrict self,
	                    struct frename_info *__restrict info)
			THROWS(E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL, E_FSERROR_READONLY);
};

struct fdirnode
#ifndef __WANT_FS_INLINE_STRUCTURES
    : fnode                         /* Underlying file-node */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct fnode         dn_node;   /* Underlying file-node */
#define _fdirnode_node_     dn_node.
#define _fdirnode_asnode(x) &(x)->dn_node
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _fdirnode_node_     /* nothing */
#define _fdirnode_asnode(x) x
#endif /* !__WANT_FS_INLINE_STRUCTURES */
};


/* Return a pointer to directory-node operators of `self' */
#define fdirnode_getops(self)                                                                                       \
	__COMPILER_CONTAINER_OF(__COMPILER_REQTYPE(struct fdirnode const *, self)->_fdirnode_node_ _fnode_file_ mf_ops, \
	                        struct fdirnode_ops, dno_node.no_file)
#define _fdirnode_assert_ops_(ops) \
	_fnode_assert_ops_(&(ops)->dno_node)

/* Check if a given `struct fdirnode *self' is a fsuper. */
#define fdirnode_issuper(self)  (&(self)->_fdirnode_node_ fn_super->fs_root == (self))
#define fdirnode_assuper(self)  __COMPILER_CONTAINER_OF(self, struct fsuper, fs_root)



/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_fdirnode_node_ _fnode_file_ mf_atime
 *  - self->_fdirnode_node_ _fnode_file_ mf_mtime
 *  - self->_fdirnode_node_ _fnode_file_ mf_ctime
 *  - self->_fdirnode_node_ fn_uid
 *  - self->_fdirnode_node_ fn_gid
 *  - self->_fdirnode_node_ fn_allnodes
 *  - self->_fdirnode_node_ fn_supent
 *  - self->_fdirnode_node_ fn_nlink  (to `1')
 *  - self->_fdirnode_node_ fn_ino
 *  - self->_fdirnode_node_ fn_mode (with something or'd with S_IFDIR)
 * @param: struct fdirnode     *self:  Directory node to initialize.
 * @param: struct fdirnode_ops *ops:   Directory operators.
 * @param: struct fsuper       *super: Associated superblock. */
#define _fdirnode_init(self, ops, super)                                                                               \
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
	 (self)->_fdirnode_node_ _fnode_file_ mf_blockshift = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_blockshift, \
	 (self)->_fdirnode_node_ _fnode_file_ mf_part_amask = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_part_amask, \
	 atomic64_init(&(self)->_fdirnode_node_ _fnode_file_ mf_filesize, (uint64_t)-1),                                   \
	 (self)->_fdirnode_node_ fn_super = incref(super))
#define _fdirnode_cinit(self, ops, super)                                                                              \
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
	 (self)->_fdirnode_node_ _fnode_file_ mf_blockshift = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_blockshift, \
	 (self)->_fdirnode_node_ _fnode_file_ mf_part_amask = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_part_amask, \
	 atomic64_init(&(self)->_fdirnode_node_ _fnode_file_ mf_filesize, (uint64_t)-1),                                   \
	 (self)->_fdirnode_node_ fn_super = incref(super))
/* Finalize a partially initialized `struct fdirnode' (as initialized by `_fdirnode_init()') */
#define _fdirnode_fini(self) \
	(decref_nokill((self)->_fdirnode_node_ fn_super))

/* Default operators for `struct fdirnode_ops' */
#define fdirnode_v_destroy fnode_v_destroy
/* Constructs a wrapper object that implements readdir() (s.a. `dirhandle_new()') */
struct handle;
FUNDEF NONNULL((1, 2)) void KCALL
fdirnode_v_open(struct mfile *__restrict self, struct handle *__restrict hand,
                struct path *access_path, struct fdirent *access_dent);

/* Default stream operators for directories (using `fdirnode_v_open') */
DATDEF struct mfile_stream_ops const fdirnode_v_stream_ops;



/* Public API (high-level wrappers around low-level operators) */

/* Lookup a directory entry within `self', given its name.
 * @return: NULL: No entry exists that is matching the given name. */
#define fdirnode_lookup(self, info) \
	(*fdirnode_getops(self)->dno_lookup)(self, info)

/* Construct a directory  enumerator object in  `*result'.
 * This function must initialize _all_ fields of `*result'
 * It  is undefined if files created or  deleted after the creation of an
 * enumerator, will still be enumerated by said enumerator. It is however
 * guarantied that all files created  before, and not deleted after  will
 * always be enumerated */
FUNDEF NONNULL((1, 2)) void FCALL
fdirnode_enum(struct fdirnode *__restrict self,
              struct fdirenum *__restrict result);


/* Create new files within a given directory.
 * @throw: E_FSERROR_ILLEGAL_PATH:          `info->mkf_name' contains bad characters
 * @throw: E_FSERROR_DISK_FULL:             Disk full
 * @throw: E_FSERROR_READONLY:              Read-only filesystem (or unsupported operation)
 * @throw: E_FSERROR_TOO_MANY_HARD_LINKS:   ...
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION: The requested S_IFMT isn't supported.
 * @return: * : One of `FDIRNODE_MKFILE_*' */
FUNDEF WUNUSED NONNULL((1, 2)) unsigned int KCALL
fdirnode_mkfile(struct fdirnode *__restrict self,
                struct fmkfile_info *__restrict info)
		THROWS(E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL,
		       E_FSERROR_READONLY, E_FSERROR_TOO_MANY_HARD_LINKS,
		       E_FSERROR_UNSUPPORTED_OPERATION);

/* Delete the specified file from this directory
 * @throw: E_FSERROR_FILE_NOT_FOUND:      The file had  already been deleted,  or
 *                                        renamed (it no longer exists as `entry'
 *                                        within `self').
 * @throw: E_FSERROR_DIRECTORY_NOT_EMPTY: `file' is a non-empty directory.
 * @throw: E_FSERROR_READONLY:            Read-only filesystem (or unsupported operation)
 * @return: * : One of `FDIRNODE_UNLINK_*' */
FUNDEF WUNUSED NONNULL((1, 2)) unsigned int KCALL
fdirnode_unlink(struct fdirnode *__restrict self,
                struct fdirent *__restrict entry,
                struct fnode *__restrict file)
		THROWS(E_FSERROR_FILE_NOT_FOUND, E_FSERROR_DIRECTORY_NOT_EMPTY, E_FSERROR_READONLY);

/* Rename/move the specified file from one location to another
 * @throw: E_FSERROR_ILLEGAL_PATH: `info->frn_name' contains bad characters
 * @throw: E_FSERROR_DISK_FULL:    Disk full
 * @throw: E_FSERROR_READONLY:     Read-only filesystem
 * @return: * : One of `FDIRNODE_RENAME_*' */
FUNDEF WUNUSED NONNULL((1, 2)) unsigned int KCALL
fdirnode_rename(struct fdirnode *__restrict self,
                struct frename_info *__restrict info)
		THROWS(E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL, E_FSERROR_READONLY);


DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_DIRNODE_H */