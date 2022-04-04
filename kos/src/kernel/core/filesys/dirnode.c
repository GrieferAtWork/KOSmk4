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
#ifndef GUARD_KERNEL_CORE_FILESYS_DIRNODE_C
#define GUARD_KERNEL_CORE_FILESYS_DIRNODE_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/dirhandle.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/node.h>
#include <kernel/handle.h>
#include <sched/task.h>

#include <kos/except.h>
#include <kos/except/reason/fs.h>
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
		if (bufsize >= (size_t)(feed_d_namlen + 1)) {
			bufsize = (size_t)feed_d_namlen;
			buf->d_name[feed_d_namlen] = '\0'; /* NUL termination */
		} else if ((readdir_mode & READDIR_MODEMASK) == READDIR_DEFAULT) {
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
fdirnode_v_open(struct mfile *__restrict self,
                /*in|out*/ REF struct handle *__restrict hand,
                struct path *access_path, struct fdirent *access_dent,
                oflag_t UNUSED(oflags))
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


/* Allocate  (on the stack)  and return a new  directory enumerator for `self'
 * The returned object must be finalized as `fdirenum_fini(return)' once done. */
PUBLIC BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct fdirenum *
_fdirnode_initenum(struct fdirenum *__restrict self, struct fdirnode *__restrict dir)
		THROWS(E_IOERROR, ...) {
	DBG_memset(self, 0xcc, sizeof(*self));
	self->de_dir = mfile_asdir(incref(dir));
	TRY {
		struct fdirnode_ops const *ops;
		ops = fdirnode_getops(dir);
		/* Construct a directory enumerator. */
		(*ops->dno_enum)(self);
	} EXCEPT {
		decref_unlikely(self->de_dir);
		RETHROW();
	}
	return self;
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
#ifdef CONFIG_HAVE_FS_NOTIFY
	struct inotify_controller *newfile_notcon;
	struct dnotify_link *newfile_link;
#endif /* CONFIG_HAVE_FS_NOTIFY */
	unsigned int result;
	struct fdirnode_ops const *ops;
	ops = fdirnode_getops(self);
#ifndef CONFIG_HAVE_FS_NOTIFY
	if unlikely(!ops->dno_mkfile)
#endif /* !CONFIG_HAVE_FS_NOTIFY */
	{
		/* Check for an already-existing file. */
		REF struct fdirent *ent;
again_lookup:
		ent = fdirnode_lookup(self, &info->mkf_lookup_info);
		if (ent) {
			REF struct fnode *node;
			TRY {
				node = fdirent_opennode(ent, self);
			} EXCEPT {
				decref_unlikely(ent);
				RETHROW();
			}
			if unlikely(!node) {
				/* Race condition: file was deleted after we did the lookup above. */
				decref_unlikely(ent);
				goto again_lookup;
			}
			info->mkf_dent  = ent;  /* Inherit reference */
			info->mkf_rnode = node; /* Inherit reference */
			return FDIRNODE_MKFILE_EXISTS;
		}

#ifdef CONFIG_HAVE_FS_NOTIFY
		if unlikely(!ops->dno_mkfile)
#endif /* CONFIG_HAVE_FS_NOTIFY */
		{
			/* If we don't have permissions to change files,
			 * then don't throw READONLY, but ACCESS_DENIED. */
			fnode_access(self, W_OK);

			/* If we have permissions, then throw READONLY. */
			THROW(E_FSERROR_READONLY);
		}
	}

#ifdef CONFIG_HAVE_FS_NOTIFY
	/* Because we have no way of knowing if the containing directory will  be
	 * traced by the time the new file  has been created, we have to  prepare
	 * for the case where it is, in which case we have to ensure that the new
	 * file will be traced, too.
	 *
	 * Because of this, we have to allocate memory that will be needed to
	 * link the newly  created file to  it's parent's notify  controller. */
	if (S_ISDIR(info->mkf_fmode) ||
	    (info->mkf_fmode == 0 && fnode_isdir(info->mkf_hrdlnk.hl_node))) {
		newfile_notcon = dnotify_controller_alloc();
		inotify_controller_asdnotify(newfile_notcon)->dnc_files = NULL;
	} else {
		newfile_notcon = inotify_controller_alloc();
	}
	newfile_notcon->inc_file = NULL;
	TRY {
		newfile_link = dnotify_link_alloc();
	} EXCEPT {
		inotify_controller_free(newfile_notcon);
		RETHROW();
	}
#endif /* CONFIG_HAVE_FS_NOTIFY */

	TRY {
		result = (*ops->dno_mkfile)(self, info);
	} EXCEPT {
#ifdef CONFIG_HAVE_FS_NOTIFY
		dnotify_link_free(newfile_link);
		inotify_controller_free(newfile_notcon);
#endif /* CONFIG_HAVE_FS_NOTIFY */

		/* If `dno_mkfile' throws `E_FSERROR_UNSUPPORTED_OPERATION', try to
		 * fill  in the correct `E_FILESYSTEM_OPERATION_*' context based on
		 * `info->mkf_fmode'. */
		if (was_thrown(E_FSERROR_UNSUPPORTED_OPERATION) &&
		    PERTASK_GET(this_exception_args.e_fserror.f_unsupported_operation.uo_operation_id) == 0) {
			uintptr_t context = 0;
			switch (info->mkf_fmode & S_IFMT) {
			case 0:
				/* IFMT=0 is used to have fs drivers create hard links! */
				context = E_FILESYSTEM_OPERATION_LINK;
				break;
			case S_IFREG:
			case S_IFSOCK: /* XXX: Custom code for sockets? */
				context = E_FILESYSTEM_OPERATION_CREAT;
				break;
			case S_IFDIR:
				context = E_FILESYSTEM_OPERATION_MKDIR;
				break;
			case S_IFLNK:
				context = E_FILESYSTEM_OPERATION_SYMLINK;
				break;
			case S_IFBLK:
			case S_IFCHR:
			case S_IFIFO:
				context = E_FILESYSTEM_OPERATION_MKNOD;
				break;
			default:
				break;
			}
			PERTASK_SET(this_exception_args.e_fserror.f_unsupported_operation.uo_operation_id, context);
		}
		RETHROW();
	}

#ifdef CONFIG_HAVE_FS_NOTIFY
	/* Must lazily bind directory notifications to child
	 * files,  like  also done  by `fdirent_opennode()':
	 *  - info->mkf_rnode
	 *  - info->mkf_dent
	 *
	 * IMPORTANT: The bind here  must be done  such that  it
	 * is NOTHROW, since (in case  a new file was  created),
	 * we have no way of dealing with an allocation failure. */
	if (self->mf_notify != NULL) {
again_acquire_notify_lock:
		notify_lock_acquire();
		COMPILER_READ_BARRIER();
		if (self->mf_notify != NULL) {
			struct dnotify_link *olnk;
			struct dnotify_controller *dnot;
			dnot = inotify_controller_asdnotify(self->mf_notify);
			olnk = dnotify_link_tree_locate(dnot->dnc_files, info->mkf_dent);
			if (olnk) {
				assert(olnk->dnl_dir == dnot);
				assert(olnk->dnl_fil == info->mkf_rnode->mf_notify);
			} else {
				/* Link is missing -> create it */
				struct mfile *rfile = info->mkf_rnode;
				assert(newfile_notcon->inc_file == NULL ||
				       newfile_notcon->inc_file == rfile);
				if (rfile->mf_notify == NULL) {
					if (newfile_notcon->inc_file == NULL) {
						struct mfile_stream_ops const *stream;
						newfile_notcon->inc_file = rfile;
						newfile_notcon->inc_fhnd = NULL;
						/* Allocate a notify file handle. */
						stream = rfile->mf_ops->mo_stream;
						if (stream && stream->mso_notify_attach) {
							notify_lock_release_br();
							/* If this throws in this context, there is literally nothing we can do. */
							TRY {
								newfile_notcon->inc_fhnd = (*stream->mso_notify_attach)(info->mkf_rnode);
							} EXCEPT {
								inotify_controller_free(newfile_notcon);
								dnotify_link_free(newfile_link);
								RETHROW();
							}
							goto again_acquire_notify_lock;
						}
					}
					/* Assign a notify controller. */
					LIST_INIT(&newfile_notcon->inc_listeners);
					LIST_INIT(&newfile_notcon->inc_dirs);
					rfile->mf_notify = newfile_notcon;
					newfile_notcon   = NULL; /* Steal */
				}
				/* Create the link */
				newfile_link->dnl_dir = dnot;
				newfile_link->dnl_fil = rfile->mf_notify;
				newfile_link->dnl_ent = incref(info->mkf_dent);
				LIST_INSERT_HEAD(&newfile_link->dnl_fil->inc_dirs, newfile_link, dnl_fillink);
				dnotify_link_tree_insert(&dnot->dnc_files, newfile_link);
				newfile_link = NULL; /* Steal */
			}
		}
		notify_lock_release();
	}
	dnotify_link_xfree(newfile_link);
	if (newfile_notcon) {
		if (newfile_notcon->inc_file) {
			struct mfile_stream_ops const *stream;
			assert(newfile_notcon->inc_file == info->mkf_rnode);
			/* Detach notify handle. */
			stream = info->mkf_rnode->mf_ops->mo_stream;
			if (stream && stream->mso_notify_detach)
				(*stream->mso_notify_detach)(info->mkf_rnode, newfile_notcon->inc_fhnd);
		}
		inotify_controller_free(newfile_notcon);
	}

	/* If a new file was created, post the relevant fs event. */
	if (result == FDIRNODE_MKFILE_SUCCESS)
		mfile_inotify_created(info->mkf_rnode); /* Post `IN_CREATE' */
#endif /* CONFIG_HAVE_FS_NOTIFY */

	return result;
}

/* Delete the specified file from this directory
 * @throw: E_FSERROR_DIRECTORY_NOT_EMPTY: `file' is a non-empty directory.
 * @throw: E_FSERROR_READONLY:            Read-only filesystem (or unsupported operation)
 * @return: * : One of `FDIRNODE_UNLINK_*' */
PUBLIC BLOCKING WUNUSED NONNULL((1, 2)) unsigned int KCALL
fdirnode_unlink(struct fdirnode *__restrict self,
                struct fdirent *__restrict entry,
                struct fnode *__restrict file)
		THROWS(E_FSERROR_DIRECTORY_NOT_EMPTY,
		       E_FSERROR_READONLY, E_IOERROR, ...) {
	unsigned int result;
	struct fdirnode_ops const *ops;
	ops = fdirnode_getops(self);
	if unlikely(!ops->dno_unlink)
		THROW(E_FSERROR_READONLY);
	result = (*ops->dno_unlink)(self, entry, file);
	if (result == FDIRNODE_UNLINK_SUCCESS)
		mfile_inotify_deleted(file); /* Post `IN_DELETE' and `IN_DELETE_SELF' */
	return result;
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
