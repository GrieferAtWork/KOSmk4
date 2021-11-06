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
#ifndef GUARD_KERNEL_CORE_FILESYS_DIRNODE_C
#define GUARD_KERNEL_CORE_FILESYS_DIRNODE_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/dirhandle.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/node.h>
#include <kernel/handle.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <sys/stat.h>

#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fdirenum_empty_v_fini)(struct fdirenum *__restrict UNUSED(self)) {
	COMPILER_IMPURE(); /* No-op */
}

PRIVATE BLOCKING NONNULL((1)) size_t KCALL
fdirenum_empty_v_readdir(struct fdirenum *__restrict UNUSED(self), USER CHECKED struct dirent *UNUSED(buf),
                         size_t UNUSED(bufsize), readdir_mode_t UNUSED(readdir_mode), iomode_t UNUSED(mode))
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	COMPILER_IMPURE();
	return 0; /* Always indicate EOF */
}

PRIVATE BLOCKING NONNULL((1)) pos_t KCALL
fdirenum_empty_v_seekdir(struct fdirenum *__restrict UNUSED(self),
                         off_t offset, unsigned int whence)
		THROWS(E_OVERFLOW, E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_IOERROR, ...) {
	switch (whence) {
	case SEEK_SET:
		break;

	case SEEK_CUR:
	case SEEK_END:
		/* CUR/END is always `0', or negative offsets would underflow */
		if unlikely(offset < 0)
			THROW(E_OVERFLOW);
		break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE,
		      whence);
	}
	return (pos_t)0;
}

/* Simple  catch-all fallback to enumerate an empty directory.
 * A minimal implementation of `struct fdirnode_ops::dno_enum'
 * may simply  do `result->de_ops = &fdirenum_empty_ops'  when
 * wanting enumeration to yield an empty directory. */
PUBLIC_CONST struct fdirenum_ops const fdirenum_empty_ops = {
	.deo_fini    = &fdirenum_empty_v_fini,
	.deo_readdir = &fdirenum_empty_v_readdir,
	.deo_seekdir = &fdirenum_empty_v_seekdir,
};


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
PUBLIC WUNUSED ssize_t FCALL
fdirenum_feedent_ex(USER CHECKED struct dirent *buf,
                    size_t bufsize, readdir_mode_t readdir_mode,
                    ino_t feed_d_ino, unsigned char feed_d_type,
                    u16 feed_d_namlen, USER CHECKED char const *feed_d_name)
		THROWS(E_SEGFAULT) {
	size_t result;
	result = ((offsetof(struct dirent, d_name)) +
	          (feed_d_namlen + 1) * sizeof(char));
	if (bufsize >= offsetof(struct dirent, d_name)) {
		/* Fill in basic members of the user-buffer (CAUTION: E_SEGFAULT) */
		buf->d_ino    = (typeof(buf->d_ino))feed_d_ino;
		buf->d_type   = (typeof(buf->d_type))feed_d_type;
		buf->d_namlen = (typeof(buf->d_namlen))feed_d_namlen;
		bufsize -= offsetof(struct dirent, d_name);
		if (bufsize >= (size_t)(feed_d_namlen + 1))
			bufsize = (size_t)(feed_d_namlen + 1);
		else if ((readdir_mode & READDIR_MODEMASK) == READDIR_DEFAULT) {
			result ^= (size_t)-1; /* Don't yield */
		}

		/* Copy the entry name to user-space (CAUTION: E_SEGFAULT) */
		memcpy(buf->d_name, feed_d_name, bufsize, sizeof(char));
		COMPILER_WRITE_BARRIER();
		if ((readdir_mode & READDIR_MODEMASK) == READDIR_PEEK)
			result ^= (size_t)-1; /* Don't yield */
	} else {
		if ((readdir_mode & READDIR_MODEMASK) != READDIR_CONTINUE)
			result ^= (size_t)-1; /* Don't yield */
	}
	return result;
}

/* Same as `fdirenum_feedent_ex()', but feed values from `ent' */
PUBLIC BLOCKING WUNUSED NONNULL((4, 5)) ssize_t FCALL
fdirenum_feedent(USER CHECKED struct dirent *buf,
                 size_t bufsize, readdir_mode_t readdir_mode,
                 struct fdirent *__restrict ent,
                 struct fdirnode *__restrict dir)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	size_t result;
	result = ((offsetof(struct dirent, d_name)) +
	          (ent->fd_namelen + 1) * sizeof(char));
	if (bufsize >= offsetof(struct dirent, d_name)) {
		/* Fill in basic members of the user-buffer (CAUTION: E_SEGFAULT) */
		buf->d_ino    = (typeof(buf->d_ino))fdirent_getino(ent, dir);
		buf->d_type   = (typeof(buf->d_type))ent->fd_type;
		buf->d_namlen = (typeof(buf->d_namlen))ent->fd_namelen;
		bufsize -= offsetof(struct dirent, d_name);
		if (bufsize >= (size_t)(ent->fd_namelen + 1))
			bufsize = (size_t)(ent->fd_namelen + 1);
		else if ((readdir_mode & READDIR_MODEMASK) == READDIR_DEFAULT) {
			result ^= (size_t)-1; /* Don't yield */
		}

		/* Copy the entry name to user-space (CAUTION: E_SEGFAULT) */
		memcpy(buf->d_name, ent->fd_name, bufsize, sizeof(char));
		COMPILER_WRITE_BARRIER();
		if ((readdir_mode & READDIR_MODEMASK) == READDIR_PEEK)
			result ^= (size_t)-1; /* Don't yield */
	} else {
		if ((readdir_mode & READDIR_MODEMASK) != READDIR_CONTINUE)
			result ^= (size_t)-1; /* Don't yield */
	}
	return result;
}

/* Same as `fdirenum_feedent()', but may only be used when `ent' doesn't implement `fdo_getino' */
PUBLIC WUNUSED NONNULL((4)) ssize_t FCALL
fdirenum_feedent_fast(USER CHECKED struct dirent *buf,
                      size_t bufsize, readdir_mode_t readdir_mode,
                      struct fdirent *__restrict ent)
		THROWS(E_SEGFAULT) {
	size_t result;
	result = ((offsetof(struct dirent, d_name)) +
	          (ent->fd_namelen + 1) * sizeof(char));
	assertf(!ent->fd_ops->fdo_getino, "Must use `fdirenum_feedent()'");
	if (bufsize >= offsetof(struct dirent, d_name)) {
		/* Fill in basic members of the user-buffer (CAUTION: E_SEGFAULT) */
		buf->d_ino    = (typeof(buf->d_ino))ent->fd_ino;
		buf->d_type   = (typeof(buf->d_type))ent->fd_type;
		buf->d_namlen = (typeof(buf->d_namlen))ent->fd_namelen;
		bufsize -= offsetof(struct dirent, d_name);
		if (bufsize >= (size_t)(ent->fd_namelen + 1))
			bufsize = (size_t)(ent->fd_namelen + 1);
		else if ((readdir_mode & READDIR_MODEMASK) == READDIR_DEFAULT) {
			result ^= (size_t)-1; /* Don't yield */
		}

		/* Copy the entry name to user-space (CAUTION: E_SEGFAULT) */
		memcpy(buf->d_name, ent->fd_name, bufsize, sizeof(char));
		COMPILER_WRITE_BARRIER();
		if ((readdir_mode & READDIR_MODEMASK) == READDIR_PEEK)
			result ^= (size_t)-1; /* Don't yield */
	} else {
		if ((readdir_mode & READDIR_MODEMASK) != READDIR_CONTINUE)
			result ^= (size_t)-1; /* Don't yield */
	}
	return result;
}




/* Default operators for `struct fdirnode_ops' */

/* Constructs a wrapper object that implements readdir() (s.a. `dirhandle_new()') */
PUBLIC NONNULL((1, 2)) void KCALL
fdirnode_v_open(struct mfile *__restrict self, struct handle *__restrict hand,
                struct path *access_path, struct fdirent *access_dent)
		THROWS(E_BADALLOC) {
	REF struct dirhandle *dh;
	/* Construct the directory handle. */
	dh = dirhandle_new(mfile_asdir(self), access_path, access_dent);
	assert(hand->h_type == HANDLE_TYPE_MFILE);
	assert(hand->h_data == self);
	hand->h_type = HANDLE_TYPE_DIRHANDLE;
	hand->h_data = dh;
	decref_nokill(self);
}

/* Writes `st_blocks = 1;', `st_size = mfile_getblocksize(self);' */
PUBLIC NONNULL((1)) void KCALL
fdirnode_v_stat(struct mfile *__restrict self,
                USER CHECKED struct stat *result)
		THROWS(E_SEGFAULT) {
	result->st_blocks = (typeof(result->st_blocks))1;
	result->st_size   = (typeof(result->st_size))mfile_getblocksize(self);
}

/* Default stream operators for directories (using `fdirnode_v_open') */
PUBLIC_CONST struct mfile_stream_ops const fdirnode_v_stream_ops = {
	.mso_open  = &fdirnode_v_open,
	.mso_stat  = &fdirnode_v_stat,
	.mso_ioctl = &fdirnode_v_ioctl,
	.mso_hop   = &fdirnode_v_hop,
};




/* Helper-wrapper for `fdirent_opennode(fdirnode_lookup(self, info))'
 * @return: NULL: No entry exists  that is matching  the given  name.
 *                The  case  where `fdirent_opennode()'  returns NULL
 *                is implicitly handled by repeating the lookup until
 *                a non-deleted entry (or no entry at all) is  found. */
PUBLIC BLOCKING WUNUSED NONNULL((1, 2)) REF struct fnode *FCALL
fdirnode_lookup_node(struct fdirnode *__restrict self,
                     struct flookup_info *__restrict info,
                     /*out[1..1]_opt*/ REF struct fdirent **p_dirent)
		THROWS(E_SEGFAULT, E_BADALLOC, E_IOERROR, ...) {
	REF struct fnode *result;
	REF struct fdirent *ent;
again:
	ent = fdirnode_lookup(self, info);
	if (!ent)
		return NULL; /* Non-existent file */
	TRY {
		result = fdirent_opennode(ent, self);
	} EXCEPT {
		decref_unlikely(ent);
		RETHROW();
	}
	if unlikely(!result) {
		/* Race condition: directory entry was deleted after the lookup above! */
		decref_likely(ent);
		goto again;
	}
	/* Write-back results */
	if (p_dirent) {
		*p_dirent = ent; /* Inherit reference */
	} else {
		decref_unlikely(ent);
	}
	return result;
}



/* !!! DON'T USE THIS FUNCTION IF YOU COULD ALSO USE `path_traverse()' !!!
 *
 * Low-level implementation of a directory path walking function. Mainly
 * intended to traverse filesystem paths without mounting a directory on
 * some `struct path'. This function simply  scans `path' for '/'  chars
 * and does a really dumb path traversal.
 *  - _NO_ support for symbolic links.
 *  - _NO_ support for "." and ".." references
 *  - _NO_ support for permission checks
 *  - _NO_ support for dos paths
 *  - _NO_ support not-a-directory exceptions (if a path isn't a directory, return `NULL')
 *  - Empty paths segments are silently ignored (including leading/trailing '/')
 *
 * @return: NULL: File not found (path or file doesn't exist,
 *                or a segment of the path isn't a directory) */
PUBLIC BLOCKING WUNUSED NONNULL((1)) REF struct fnode *FCALL
fdirnode_lookup_path(struct fdirnode *__restrict self,
                     USER CHECKED char const *path)
		THROWS(E_SEGFAULT, E_BADALLOC, E_IOERROR, ...) {
	REF struct fnode *result = mfile_asnode(incref(self));
	for (;;) {
		USER CHECKED char const *sep;
		size_t partlen;
		TRY {
			sep = strchrnul(path, '/');
		} EXCEPT {
			decref_unlikely(result);
			RETHROW();
		}
		partlen = (size_t)(sep - path);
		if (partlen != 0) {
			struct flookup_info info;
			FINALLY_DECREF_UNLIKELY(result);
			if unlikely(!fnode_isdir(result))
				return NULL; /* Not a directory */
			if unlikely(partlen > 0xffff)
				return NULL; /* Name too long */
			info.flu_name    = path;
			info.flu_namelen = (u16)partlen;
			info.flu_flags   = 0;
			info.flu_hash    = FLOOKUP_INFO_HASH_UNSET;
			result = fdirnode_lookup_node(fnode_asdir(result), &info);
			if unlikely(!result)
				return NULL; /* File not found */
		}
		TRY {
			if (!*sep)
				break;
		} EXCEPT {
			decref_unlikely(result);
			RETHROW();
		}
		path = sep + 1;
	}
	return result;
}



/* Construct a directory  enumerator object in  `*result'.
 * This function must initialize _all_ fields of `*result'
 * It  is undefined if files created or  deleted after the creation of an
 * enumerator, will still be enumerated by said enumerator. It is however
 * guarantied that all files created  before, and not deleted after  will
 * always be enumerated */
PUBLIC BLOCKING NONNULL((1, 2)) void FCALL
fdirnode_enum(struct fdirnode *__restrict self,
              struct fdirenum *__restrict result)
		THROWS(E_IOERROR, ...) {
	DBG_memset(result, 0xcc, sizeof(*result));
	result->de_dir = mfile_asdir(incref(self));
	TRY {
		struct fdirnode_ops const *ops;
		ops = fdirnode_getops(self);
		(*ops->dno_enum)(result);
	} EXCEPT {
		decref_unlikely(result->de_dir);
		RETHROW();
	}
}


/* Create new files within a given directory.
 * @throw: E_FSERROR_ILLEGAL_PATH:          `info->mkf_name' contains bad characters
 * @throw: E_FSERROR_DISK_FULL:             Disk full
 * @throw: E_FSERROR_READONLY:              Read-only filesystem (or unsupported operation)
 * @throw: E_FSERROR_TOO_MANY_HARD_LINKS:   ...
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION: The requested S_IFMT isn't supported.
 * @throw: E_FSERROR_ACCESS_DENIED:         The file didn't already exist, and caller doesn't have write-access to `self'
 * @return: * : One of `FDIRNODE_MKFILE_*' * */
PUBLIC BLOCKING WUNUSED NONNULL((1, 2)) unsigned int KCALL
fdirnode_mkfile(struct fdirnode *__restrict self,
                struct fmkfile_info *__restrict info)
		THROWS(E_SEGFAULT, E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL,
		       E_FSERROR_READONLY, E_FSERROR_TOO_MANY_HARD_LINKS,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	struct fdirnode_ops const *ops;
	ops = fdirnode_getops(self);
	if unlikely(!ops->dno_mkfile) {
		/* Check for an already-existing file. */
		REF struct fdirent *ent;
		REF struct fnode *node;
again_lookup:
		ent = fdirnode_lookup(self, &info->mkf_lookup_info);
		if (!ent) {
			/* If we don't have permissions to change files,
			 * then don't throw READONLY, but ACCESS_DENIED. */
			fnode_access(self, W_OK);

			/* If we have permissions, then throw READONLY. */
			THROW(E_FSERROR_READONLY);
		}
		TRY {
			node = fdirent_opennode(ent, self);
		} EXCEPT {
			decref_unlikely(ent);
			RETHROW();
		}
		if unlikely(!node) {
			decref_unlikely(ent);
			goto again_lookup;
		}
		info->mkf_dent  = ent;  /* Inherit reference */
		info->mkf_rnode = node; /* Inherit reference */
		return FDIRNODE_MKFILE_EXISTS;
	}
	/* TODO: If this throws `E_FSERROR_UNSUPPORTED_OPERATION' with context == 0,
	 *       try to fill in the correct `E_FILESYSTEM_OPERATION_*' context based
	 *       on `info->mkf_fmode'. */
	return (*ops->dno_mkfile)(self, info);
}

/* Delete the specified file from this directory
 * @throw: E_FSERROR_FILE_NOT_FOUND:      The file had  already been deleted,  or
 *                                        renamed (it no longer exists as `entry'
 *                                        within `self').
 * @throw: E_FSERROR_DIRECTORY_NOT_EMPTY: `file' is a non-empty directory.
 * @throw: E_FSERROR_READONLY:            Read-only filesystem (or unsupported operation)
 * @return: * : One of `FDIRNODE_UNLINK_*' */
PUBLIC BLOCKING WUNUSED NONNULL((1, 2)) unsigned int KCALL
fdirnode_unlink(struct fdirnode *__restrict self,
                struct fdirent *__restrict entry,
                struct fnode *__restrict file)
		THROWS(E_FSERROR_FILE_NOT_FOUND, E_FSERROR_DIRECTORY_NOT_EMPTY,
		       E_FSERROR_READONLY, E_IOERROR, ...) {
	struct fdirnode_ops const *ops;
	ops = fdirnode_getops(self);
	if unlikely(!ops->dno_unlink)
		THROW(E_FSERROR_READONLY);
	return (*ops->dno_unlink)(self, entry, file);
}

/* Rename/move the specified file from one location to another
 * @throw: E_FSERROR_ILLEGAL_PATH: `info->frn_name' contains bad characters
 * @throw: E_FSERROR_DISK_FULL:    Disk full
 * @throw: E_FSERROR_READONLY:     Read-only filesystem
 * @return: * : One of `FDIRNODE_RENAME_*' */
PUBLIC BLOCKING WUNUSED NONNULL((1, 2)) unsigned int KCALL
fdirnode_rename(struct fdirnode *__restrict self,
                struct frename_info *__restrict info)
		THROWS(E_SEGFAULT, E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL,
		       E_FSERROR_READONLY, E_IOERROR, ...) {
	struct fdirnode_ops const *ops;

	/* Do the low-level rename operation */
	ops = fdirnode_getops(self);
	if unlikely(!ops->dno_rename)
		THROW(E_FSERROR_READONLY);
	return (*ops->dno_rename)(self, info);
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_DIRNODE_C */
