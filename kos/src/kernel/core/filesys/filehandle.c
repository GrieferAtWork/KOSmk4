/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_FILESYS_FILEHANDLE_C
#define GUARD_KERNEL_CORE_FILESYS_FILEHANDLE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/devfs.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/dirhandle.h>
#include <kernel/fs/fifohandle.h>
#include <kernel/fs/filehandle.h>
#include <kernel/fs/fs.h>
#include <kernel/fs/notify.h>
#include <kernel/fs/path.h>
#include <kernel/fs/ramfs.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/malloc.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mfilemeta.h>

#include <hybrid/overflow.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/kernel/handle.h>

#include <assert.h>
#include <atomic.h>
#include <format-printer.h>
#include <stddef.h>

DECL_BEGIN

/* Destroy the given filehandle object. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL filehandle_destroy)(struct filehandle *__restrict self) {
	REF struct mfile *file = self->fh_file;

	/* Release a possible flock-based file lock. */
	mfile_flock_release_expecting_nolock(file, filehandle_get_flock_key(self));

	/* TODO: If the file was opened as writable, must post `IN_CLOSE_WRITE'! */
	mfile_inotify_closero(file); /* Post `IN_CLOSE_NOWRITE' */
	decref_unlikely(file);
	xdecref_unlikely(self->fh_path);
	xdecref_unlikely(self->fh_dirent);
	kfree(self);
}

/* Allocate and return a new file handle wrapper for the given  file.
 * This function is used to implement `mfile_v_open()', which is  the
 * fallback open operator for mfile-s to implement seek capabilities.
 *
 * Handle operates invoked on the returned object are forwarded to the
 * relevant `mfile_u*' functions, lseek(2) is implemented locally, and
 * `read(2)' and `write(2)' are implemented via `pread(2)'+`pwrite(2)' */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct filehandle *KCALL
filehandle_new(struct mfile *__restrict self,
               struct path *access_path,
               struct fdirent *access_dent)
		THROWS(E_BADALLOC) {
	REF struct filehandle *result;
	result = (REF struct filehandle *)kmalloc(sizeof(struct filehandle), GFP_NORMAL);
	result->fh_refcnt = 1;
	result->fh_file   = incref(self);
	result->fh_path   = xincref(access_path);
	result->fh_dirent = xincref(access_dent);
	atomic64_init(&result->fh_offset, 0);
	mfile_inotify_opened(self); /* Post `IN_OPEN' */
	return result;
}


/************************************************************************/
/* Handle operators for `HANDLE_TYPE_FILEHANDLE'                        */
/************************************************************************/
DEFINE_HANDLE_REFCNT_FUNCTIONS(filehandle, struct filehandle);

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_filehandle_read(struct filehandle *__restrict self, NCX void *dst,
                       size_t num_bytes, iomode_t mode) THROWS(...) {
	size_t result;
	uint64_t oldpos, newpos;
again:
	oldpos = atomic64_read(&self->fh_offset);
	result = mfile_upread(self->fh_file, dst, num_bytes, (pos_t)oldpos, mode);
	newpos = oldpos + result;
	if (!atomic64_cmpxch(&self->fh_offset, oldpos, newpos))
		goto again;
	return result;
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_filehandle_write(struct filehandle *__restrict self,
                        NCX void const *src,
                        size_t num_bytes, iomode_t mode) THROWS(...) {
	size_t result;
	/* Deal with O_APPEND */
	if (mode & IO_APPEND) {
		result = mfile_utailwrite(self->fh_file, src, num_bytes, mode);
	} else {
#if 1 /* This is still better than potentially overwriting unrelated data... */
		uint64_t oldpos, newpos;
		oldpos = atomic64_read(&self->fh_offset);
		result = mfile_upwrite(self->fh_file, src, num_bytes, (pos_t)oldpos, mode);
		newpos = oldpos + result;
		atomic64_write(&self->fh_offset, newpos);
#else
		uint64_t oldpos, newpos;
again:
		oldpos = atomic64_read(&self->fh_offset);
		result = mfile_upwrite(self->fh_file, src, num_bytes, (pos_t)oldpos, mode);
		newpos = oldpos + result;
		if (!atomic64_cmpxch(&self->fh_offset, oldpos, newpos))
			goto again;
#endif
	}
	return result;
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_filehandle_pread(struct filehandle *__restrict self, NCX void *dst,
                        size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	return mfile_upread(self->fh_file, dst, num_bytes, addr, mode);
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_filehandle_pwrite(struct filehandle *__restrict self, NCX void const *src,
                         size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	return mfile_upwrite(self->fh_file, src, num_bytes, addr, mode);
}

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_filehandle_readv(struct filehandle *__restrict self,
                        struct iov_buffer *__restrict dst,
                        size_t num_bytes, iomode_t mode) THROWS(...) {
	size_t result;
	uint64_t oldpos, newpos;
again:
	oldpos = atomic64_read(&self->fh_offset);
	result = mfile_upreadv(self->fh_file, dst, num_bytes, (pos_t)oldpos, mode);
	newpos = oldpos + result;
	if (!atomic64_cmpxch(&self->fh_offset, oldpos, newpos))
		goto again;
	return result;
}

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_filehandle_writev(struct filehandle *__restrict self,
                         struct iov_buffer *__restrict src,
                         size_t num_bytes, iomode_t mode) THROWS(...) {
	size_t result;
	/* Deal with O_APPEND */
	if (mode & IO_APPEND) {
		result = mfile_utailwritev(self->fh_file, src, num_bytes, mode);
	} else {
#if 1 /* This is still better than potentially overwriting unrelated data... */
		uint64_t oldpos, newpos;
		oldpos = atomic64_read(&self->fh_offset);
		result = mfile_upwritev(self->fh_file, src, num_bytes, (pos_t)oldpos, mode);
		newpos = oldpos + result;
		atomic64_write(&self->fh_offset, newpos);
#else
		uint64_t oldpos, newpos;
again:
		oldpos = atomic64_read(&self->fh_offset);
		result = mfile_upwritev(self->fh_file, src, num_bytes, (pos_t)oldpos, mode);
		newpos = oldpos + result;
		if (!atomic64_cmpxch(&self->fh_offset, oldpos, newpos))
			goto again;
#endif
	}
	return result;
}

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_filehandle_preadv(struct filehandle *__restrict self,
                         struct iov_buffer *__restrict dst,
                         size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	return mfile_upreadv(self->fh_file, dst, num_bytes, addr, mode);
}

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_filehandle_pwritev(struct filehandle *__restrict self,
                          struct iov_buffer *__restrict src,
                          size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	return mfile_upwritev(self->fh_file, src, num_bytes, addr, mode);
}
INTERN NONNULL((1)) pos_t KCALL
handle_filehandle_seek(struct filehandle *__restrict self,
                       off_t offset, unsigned int whence) THROWS(...) {
	uint64_t newpos;
	switch (whence) {

	case SEEK_SET:
		newpos = (uint64_t)(pos_t)offset;
		break;

	case SEEK_CUR: {
		/* This is the only case where the new file position depends on the
		 * old, also making it the only  case where we need CAS  semantics. */
		uint64_t oldpos;
		do {
			oldpos = atomic64_read(&self->fh_offset);
			newpos = oldpos + (int64_t)offset;
			if unlikely(offset < 0 ? newpos > oldpos
			                       : newpos < oldpos)
				THROW(E_OVERFLOW);
		} while (!atomic64_cmpxch(&self->fh_offset, oldpos, newpos));
		goto done;
	}	break;

	case SEEK_END: {
		uint64_t filesize;
		filesize = atomic64_read(&self->fh_file->mf_filesize);
		newpos   = filesize + (int64_t)offset;
		if unlikely(offset < 0 ? newpos > filesize
		                       : newpos < filesize)
			THROW(E_OVERFLOW);
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE,
		      whence);
		break;
	}

	/* Write-back the new file position. */
	atomic64_write(&self->fh_offset, newpos);
done:
	return (pos_t)newpos;
}

INTERN NONNULL((1)) syscall_slong_t KCALL
handle_filehandle_ioctl(struct filehandle *__restrict self, ioctl_t cmd,
                        NCX UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	return mfile_uioctl(self->fh_file, cmd, arg, mode);
}

INTERN NONNULL((1)) void KCALL
handle_filehandle_truncate(struct filehandle *__restrict self, pos_t new_size) THROWS(...) {
	mfile_utruncate(self->fh_file, new_size);
}

INTERN NONNULL((1, 2)) void KCALL
handle_filehandle_mmap(struct filehandle *__restrict self,
                       struct handle_mmap_info *__restrict info) THROWS(...) {
	mfile_ummap(self->fh_file, info);
	/* Supplement `info' with filesystem names from `self' */
	if (info->hmi_fsname == NULL)
		info->hmi_fsname = xincref(self->fh_dirent);
	if (info->hmi_fspath == NULL)
		info->hmi_fspath = xincref(self->fh_path);
}

INTERN NONNULL((1)) pos_t KCALL
handle_filehandle_allocate(struct filehandle *__restrict self,
                           fallocate_mode_t mode, pos_t start,
                           pos_t length) THROWS(...) {
	return mfile_uallocate(self->fh_file, mode, start, length);
}

INTERN NONNULL((1)) void KCALL
handle_filehandle_flock(struct filehandle *__restrict self,
                        syscall_ulong_t operation) THROWS(...) {
	mfile_flock_key_t key = filehandle_get_flock_key(self);
	mfile_flock(self->fh_file, operation, key);
}

INTERN NONNULL((1)) void KCALL
handle_filehandle_sync(struct filehandle *__restrict self) THROWS(...) {
	mfile_usync(self->fh_file);
}

INTERN NONNULL((1)) void KCALL
handle_filehandle_datasync(struct filehandle *__restrict self) THROWS(...) {
	mfile_udatasync(self->fh_file);
}

INTERN NONNULL((1)) void KCALL
handle_filehandle_stat(struct filehandle *__restrict self,
                       NCX struct stat *result) THROWS(...) {
	mfile_ustat(self->fh_file, result);
}

INTERN NONNULL((1)) void KCALL
handle_filehandle_pollconnect(struct filehandle *__restrict self,
                              poll_mode_t what) THROWS(...) {
	mfile_upollconnect(self->fh_file, what);
}

INTERN WUNUSED NONNULL((1)) poll_mode_t KCALL
handle_filehandle_polltest(struct filehandle *__restrict self,
                           poll_mode_t what) THROWS(...) {
	return mfile_upolltest(self->fh_file, what);
}

INTERN NONNULL((1)) REF void *KCALL
handle_filehandle_tryas(struct filehandle *__restrict self,
                        uintptr_half_t wanted_type)
		THROWS(E_WOULDBLOCK) {
	switch (wanted_type) {
	case HANDLE_TYPE_MFILE: return incref(self->fh_file);
	case HANDLE_TYPE_DIRENT: return xincref(self->fh_dirent);
	case HANDLE_TYPE_PATH: return xincref(self->fh_path);
	default: break;
	}
	return mfile_utryas(self->fh_file, wanted_type);
}



static_assert(offsetof(struct filehandle, fh_path) == offsetof(struct fifohandle, fu_path));
static_assert(offsetof(struct filehandle, fh_dirent) == offsetof(struct fifohandle, fu_dirent));
DEFINE_INTERN_ALIAS(handle_fifohandle_printlink, handle_filehandle_printlink);
INTERN NONNULL((1, 2)) ssize_t KCALL
handle_filehandle_printlink(struct filehandle *__restrict self,
                            pformatprinter printer, void *arg)
		THROWS(E_WOULDBLOCK, ...) {
	if (self->fh_dirent) {
		if (self->fh_path) {
			REF struct path *root = fs_getroot(THIS_FS);
			FINALLY_DECREF_UNLIKELY(root);
			return path_printent(self->fh_path, self->fh_dirent->fd_name,
			                     self->fh_dirent->fd_namelen, printer, arg,
			                     AT_PATHPRINT_INCTRAIL, root);
		}
		if (self->fh_dirent->fd_name[0] == '/')
			return (*printer)(arg, self->fh_dirent->fd_name, self->fh_dirent->fd_namelen);
		return format_printf(printer, arg, "?/%$s",
		                     (size_t)self->fh_dirent->fd_namelen,
		                     self->fh_dirent->fd_name);
	}
	return mfile_uprintlink(self->fh_file, printer, arg);
}


/************************************************************************/
/* Handle operators for `HANDLE_TYPE_TEMPHANDLE'                        */
/************************************************************************/
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL handle_temphandle_decref)(REF struct filehandle *__restrict self) {
	struct mfile *file;

	/* Decrement reference counter. */
	if (atomic_decfetch(&self->fh_refcnt) != 0)
		return;

	/* Delete the pointed-to file, using the most appropriate delete function. */
	file = self->fh_file;
	if (mfile_isnode(file)) {
		struct fnode *node = mfile_asnode(file);
		if (fnode_isdevice(node)) {
			device_delete(fnode_asdevice(node));
		} else if (fnode_issuper(node)) {
			fsuper_delete(fnode_assuper(node));
		} else {
			fnode_delete(node);
		}
	} else {
		/* Default: just delete a regular, old file. */
		mfile_delete(file);
	}

	/* Invoke the normal destroy function for filehandle objects. */
	filehandle_destroy(self);
}

DEFINE_INTERN_ALIAS(handle_temphandle_refcnt, handle_filehandle_refcnt);
DEFINE_INTERN_ALIAS(handle_temphandle_incref, handle_filehandle_incref);
/*DEFINE_INTERN_ALIAS(handle_temphandle_decref, handle_filehandle_decref);*/ /* Special handling! */
DEFINE_INTERN_ALIAS(handle_temphandle_tryincref, handle_filehandle_tryincref);
DEFINE_INTERN_ALIAS(handle_temphandle_weakgetref, handle_filehandle_weakgetref);
DEFINE_INTERN_ALIAS(handle_temphandle_weaklckref, handle_filehandle_weaklckref);
DEFINE_INTERN_ALIAS(handle_temphandle_weakdecref, handle_filehandle_weakdecref);
DEFINE_INTERN_ALIAS(handle_temphandle_read, handle_filehandle_read);
DEFINE_INTERN_ALIAS(handle_temphandle_write, handle_filehandle_write);
DEFINE_INTERN_ALIAS(handle_temphandle_pread, handle_filehandle_pread);
DEFINE_INTERN_ALIAS(handle_temphandle_pwrite, handle_filehandle_pwrite);
DEFINE_INTERN_ALIAS(handle_temphandle_readv, handle_filehandle_readv);
DEFINE_INTERN_ALIAS(handle_temphandle_writev, handle_filehandle_writev);
DEFINE_INTERN_ALIAS(handle_temphandle_preadv, handle_filehandle_preadv);
DEFINE_INTERN_ALIAS(handle_temphandle_pwritev, handle_filehandle_pwritev);
/*DEFINE_INTERN_ALIAS(handle_temphandle_readdir, handle_filehandle_readdir);*/
DEFINE_INTERN_ALIAS(handle_temphandle_seek, handle_filehandle_seek);
DEFINE_INTERN_ALIAS(handle_temphandle_ioctl, handle_filehandle_ioctl);
DEFINE_INTERN_ALIAS(handle_temphandle_truncate, handle_filehandle_truncate);
DEFINE_INTERN_ALIAS(handle_temphandle_mmap, handle_filehandle_mmap);
DEFINE_INTERN_ALIAS(handle_temphandle_allocate, handle_filehandle_allocate);
DEFINE_INTERN_ALIAS(handle_temphandle_flock, handle_filehandle_flock);
DEFINE_INTERN_ALIAS(handle_temphandle_sync, handle_filehandle_sync);
DEFINE_INTERN_ALIAS(handle_temphandle_datasync, handle_filehandle_datasync);
DEFINE_INTERN_ALIAS(handle_temphandle_stat, handle_filehandle_stat);
DEFINE_INTERN_ALIAS(handle_temphandle_pollconnect, handle_filehandle_pollconnect);
DEFINE_INTERN_ALIAS(handle_temphandle_polltest, handle_filehandle_polltest);
DEFINE_INTERN_ALIAS(handle_temphandle_tryas, handle_filehandle_tryas);
DEFINE_INTERN_ALIAS(handle_temphandle_printlink, handle_filehandle_printlink);

DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_FILEHANDLE_C */
