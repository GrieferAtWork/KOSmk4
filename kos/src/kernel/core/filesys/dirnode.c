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
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/dirhandle.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/node.h>
#include <kernel/handle.h>

#include <kos/except.h>
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
PUBLIC WUNUSED NONNULL((4, 5)) ssize_t FCALL
fdirenum_feedent(USER CHECKED struct dirent *buf,
                 size_t bufsize, readdir_mode_t readdir_mode,
                 struct fdirent *__restrict ent,
                 struct fdirnode *__restrict dir)
		THROWS(E_SEGFAULT) {
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
                struct path *access_path, struct fdirent *access_dent) {
	REF struct dirhandle *dh;
	/* Construct the directory handle. */
	dh = dirhandle_new(mfile_asdir(self), access_path, access_dent);
	assert(hand->h_type == HANDLE_TYPE_MFILE);
	assert(hand->h_data == self);
	hand->h_type = HANDLE_TYPE_DIRHANDLE;
	hand->h_data = dh;
	decref_nokill(self);
}

PUBLIC NONNULL((1)) void KCALL
fdirnode_v_stat(struct mfile *__restrict self,
                USER CHECKED struct stat *result)
		THROWS(...) {
	result->st_blocks = (typeof(result->st_blocks))1;
	result->st_size   = (typeof(result->st_size))1 << self->mf_blockshift;
}

/* Default stream operators for directories (using `fdirnode_v_open') */
PUBLIC_CONST struct mfile_stream_ops const fdirnode_v_stream_ops = {
	.mso_open = &fdirnode_v_open,
	.mso_stat = &fdirnode_v_stat,
};



/* Construct a directory  enumerator object in  `*result'.
 * This function must initialize _all_ fields of `*result'
 * It  is undefined if files created or  deleted after the creation of an
 * enumerator, will still be enumerated by said enumerator. It is however
 * guarantied that all files created  before, and not deleted after  will
 * always be enumerated */
PUBLIC NONNULL((1, 2)) void FCALL
fdirnode_enum(struct fdirnode *__restrict self,
              struct fdirenum *__restrict result) {
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
PUBLIC WUNUSED NONNULL((1, 2)) unsigned int FCALL
fdirnode_mkfile(struct fdirnode *__restrict self,
                struct fmkfile_info *__restrict info)
		THROWS(E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL,
		       E_FSERROR_READONLY, E_FSERROR_TOO_MANY_HARD_LINKS,
		       E_FSERROR_UNSUPPORTED_OPERATION) {
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
PUBLIC WUNUSED NONNULL((1, 2)) unsigned int FCALL
fdirnode_unlink(struct fdirnode *__restrict self,
                struct fdirent *__restrict entry,
                struct fnode *__restrict file)
		THROWS(E_FSERROR_FILE_NOT_FOUND, E_FSERROR_DIRECTORY_NOT_EMPTY, E_FSERROR_READONLY) {
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
PUBLIC WUNUSED NONNULL((1, 2)) unsigned int FCALL
fdirnode_rename(struct fdirnode *__restrict self,
                struct frename_info *__restrict info)
		THROWS(E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL, E_FSERROR_READONLY) {
	struct fdirnode_ops const *ops;

	/* Do the low-level rename operation */
	ops = fdirnode_getops(self);
	if unlikely(!ops->dno_rename)
		THROW(E_FSERROR_READONLY);
	return (*ops->dno_rename)(self, info);
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_DIRNODE_C */
