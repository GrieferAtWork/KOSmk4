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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_HANDLE_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_HANDLE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_FS
#include <kernel/fs/devfs.h>
#include <kernel/fs/devnode.h>
#include <kernel/fs/filehandle.h>
#include <kernel/fs/node.h>
#include <kernel/fs/path.h>
#include <kernel/fs/ramfs.h>
#include <kernel/fs/super.h>
#include <kernel/fs/vfs.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/iovec.h>
#include <kernel/mman/mfile.h>
#include <kernel/user.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <kos/except.h>
#include <kos/except/reason/fs.h>
#include <kos/except/reason/inval.h>
#include <sys/stat.h>

#include <assert.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/* Constructs a wrapper object that implements seeking, allowing normal reads/writes to
 * be dispatched via `mfile_upread()' and `mfile_upwrite()' (which uses the `mso_pread'
 * and `mso_pwrite' operators, with `mfile_read()' and `mfile_write()' as fallback, so-
 * long as `MFILE_F_NOUSRIO' isn't set)
 *
 * The operators of the following system calls are forwarded 1-on-1 to `mfile_u*':
 *   - pread(2), preadv(2), pwrite(2), pwritev(2)
 *   - ioctl(2), truncate(2), mmap(2), fallocate(2)
 *   - fsync(2), fdatasync(2), stat(2), poll(2), hop(2)
 * As stated, `lseek(2)', `read(2)' and `write(2)' are dispatched via pread/pwrite
 *
 * This function is actually used when trying to open a mem-file with neither
 * `mso_read'/`mso_readv', nor `mso_write'/`mso_writev' pre-defined. As such,
 * open(2)-ing a generic mfile object uses `mfile_open()' (see below). */
PUBLIC NONNULL((1, 2)) void KCALL
mfile_v_open(struct mfile *__restrict self, struct handle *__restrict hand,
             struct path *access_path, struct fdirent *access_dent) {
	REF struct filehandle *fh;
	assert(hand->h_type == HANDLE_TYPE_MFILE);
	assert(hand->h_data == self);

	/* Construct the filehandle wrapper object. */
	fh = filehandle_new(self, access_path, access_dent);

	/* Write-back the file-handle wrapper. */
	hand->h_type = HANDLE_TYPE_FILEHANDLE;
	hand->h_data = fh;   /* Inherit reference */
	decref_nokill(self); /* Old reference from `hand->h_data' */
}


/* Generic open function for mem-file arbitrary mem-file objects. This function
 * is unconditionally invoked during a call to `open(2)' in order to  construct
 * wrapper  objects   and  the   like.  This   function  is   implemented   as:
 * >> struct mfile_stream_ops const *stream = self->mf_ops->mo_stream;
 * >> if (!stream) {
 * >>     mfile_v_open(self, hand, access_path, access_dent);
 * >> } else if (stream->mso_open) {
 * >>     (*stream->mso_open)(self, hand, access_path, access_dent);
 * >> } else if (!stream->mso_read && !stream->mso_readv &&
 * >>            !stream->mso_write && !stream->mso_writev) {
 * >>     mfile_v_open(self, hand, access_path, access_dent);
 * >> } else {
 * >>     // Open mfile itself (iow: `hand->h_data == self')
 * >> } */
PUBLIC NONNULL((1, 2)) void KCALL
mfile_open(struct mfile *__restrict self, struct handle *__restrict hand,
           struct path *access_path, struct fdirent *access_dent) {
	struct mfile_stream_ops const *stream = self->mf_ops->mo_stream;
	if (!stream) {
		mfile_v_open(self, hand, access_path, access_dent);
	} else if (stream->mso_open) {
		(*stream->mso_open)(self, hand, access_path, access_dent);
	} else if (!stream->mso_read && !stream->mso_readv &&
	           !stream->mso_write && !stream->mso_writev) {
		mfile_v_open(self, hand, access_path, access_dent);
	} else {
		/* Open mfile itself (iow: `hand->h_data == self') */
	}
}


/* User-visible mem-file access API. (same as the handle access API) */
DEFINE_PUBLIC_ALIAS(mfile_uread, handle_mfile_read);
DEFINE_PUBLIC_ALIAS(mfile_uwrite, handle_mfile_write);
DEFINE_PUBLIC_ALIAS(mfile_upread, handle_mfile_pread);
DEFINE_PUBLIC_ALIAS(mfile_upwrite, handle_mfile_pwrite);
DEFINE_PUBLIC_ALIAS(mfile_ureadv, handle_mfile_readv);
DEFINE_PUBLIC_ALIAS(mfile_uwritev, handle_mfile_writev);
DEFINE_PUBLIC_ALIAS(mfile_upreadv, handle_mfile_preadv);
DEFINE_PUBLIC_ALIAS(mfile_upwritev, handle_mfile_pwritev);
DEFINE_PUBLIC_ALIAS(mfile_useek, handle_mfile_seek);
DEFINE_PUBLIC_ALIAS(mfile_uioctl, handle_mfile_ioctl);
DEFINE_PUBLIC_ALIAS(mfile_utruncate, handle_mfile_truncate);
DEFINE_PUBLIC_ALIAS(mfile_ummap, handle_mfile_mmap);
DEFINE_PUBLIC_ALIAS(mfile_uallocate, handle_mfile_allocate);
DEFINE_PUBLIC_ALIAS(mfile_usync, handle_mfile_sync);
DEFINE_PUBLIC_ALIAS(mfile_udatasync, handle_mfile_datasync);
DEFINE_PUBLIC_ALIAS(mfile_ustat, handle_mfile_stat);
DEFINE_PUBLIC_ALIAS(mfile_upollconnect, handle_mfile_pollconnect);
DEFINE_PUBLIC_ALIAS(mfile_upolltest, handle_mfile_polltest);
DEFINE_PUBLIC_ALIAS(mfile_uhop, handle_mfile_hop);
DEFINE_PUBLIC_ALIAS(mfile_utryas, handle_mfile_tryas);
DEFINE_PUBLIC_ALIAS(mfile_uprintlink, handle_mfile_printlink);


/* DATABLOCK HANDLE OPERATIONS */
DEFINE_HANDLE_REFCNT_FUNCTIONS(mfile, struct mfile);

/************************************************************************/
/* Handle-specific operator wrappers for `struct mfile'                 */
/************************************************************************/

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_mfile_read(struct mfile *__restrict self,
                  USER CHECKED void *dst,
                  size_t num_bytes, iomode_t mode)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if likely(stream != NULL) {
		if likely(stream->mso_read)
			return (*stream->mso_read)(self, dst, num_bytes, mode);
		if likely(stream->mso_readv) {
			struct iov_buffer iov;
			iov_buffer_initone(&iov, dst, num_bytes);
			return (*stream->mso_readv)(self, &iov, num_bytes, mode);
		}
	}
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_READ);
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_mfile_write(struct mfile *__restrict self,
                   USER CHECKED void const *src,
                   size_t num_bytes, iomode_t mode)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if likely(stream != NULL) {
		if likely(stream->mso_write)
			return (*stream->mso_write)(self, src, num_bytes, mode);
		if likely(stream->mso_writev) {
			struct iov_buffer iov;
			iov_buffer_initone(&iov, src, num_bytes);
			return (*stream->mso_writev)(self, &iov, num_bytes, mode);
		}
	}
	if likely((mode & IO_APPEND) && !(self->mf_flags & MFILE_F_NOUSRIO))
		return mfile_tailwrite(self, src, num_bytes);
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_WRITE);
}

PUBLIC WUNUSED NONNULL((1)) size_t KCALL
mfile_utailwrite(struct mfile *__restrict self,
                 USER CHECKED void const *src,
                 size_t num_bytes, iomode_t mode)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if likely(stream != NULL) {
		if likely(stream->mso_write)
			return (*stream->mso_write)(self, src, num_bytes, mode | IO_APPEND);
		if likely(stream->mso_writev) {
			struct iov_buffer iov;
			iov_buffer_initone(&iov, src, num_bytes);
			return (*stream->mso_writev)(self, &iov, num_bytes, mode | IO_APPEND);
		}
	}
	if likely(!(self->mf_flags & MFILE_F_NOUSRIO))
		return mfile_tailwrite(self, src, num_bytes);
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_WRITE);
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_mfile_pread(struct mfile *__restrict self,
                   USER CHECKED void *dst, size_t num_bytes,
                   pos_t addr, iomode_t mode)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if (stream != NULL) {
		if (stream->mso_pread)
			return (*stream->mso_pread)(self, dst, num_bytes, addr, mode);
		if (stream->mso_preadv) {
			struct iov_buffer iov;
			iov_buffer_initone(&iov, dst, num_bytes);
			return (*stream->mso_preadv)(self, &iov, num_bytes, addr, mode);
		}
	}
	if likely(!(self->mf_flags & MFILE_F_NOUSRIO))
		return mfile_read(self, dst, num_bytes, addr);
	if (stream != NULL && addr == 0) {
		if (stream->mso_read)
			return (*stream->mso_read)(self, dst, num_bytes, mode);
		if (stream->mso_readv) {
			struct iov_buffer iov;
			iov_buffer_initone(&iov, dst, num_bytes);
			return (*stream->mso_readv)(self, &iov, num_bytes, mode);
		}
	}
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_PREAD);
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_mfile_pwrite(struct mfile *__restrict self,
                    USER CHECKED void const *src, size_t num_bytes,
                    pos_t addr, iomode_t mode)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if (stream != NULL) {
		if (stream->mso_pwrite)
			return (*stream->mso_pwrite)(self, src, num_bytes, addr, mode);
		if (stream->mso_pwritev) {
			struct iov_buffer iov;
			iov_buffer_initone(&iov, src, num_bytes);
			return (*stream->mso_pwritev)(self, &iov, num_bytes, addr, mode);
		}
	}
	if likely(!(self->mf_flags & MFILE_F_NOUSRIO))
		return mfile_write(self, src, num_bytes, addr);
	if (stream != NULL && addr == 0) {
		if (stream->mso_write)
			return (*stream->mso_write)(self, src, num_bytes, mode);
		if (stream->mso_writev) {
			struct iov_buffer iov;
			iov_buffer_initone(&iov, src, num_bytes);
			return (*stream->mso_writev)(self, &iov, num_bytes, mode);
		}
	}
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_PWRITE);
}

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_mfile_readv(struct mfile *__restrict self,
                   struct iov_buffer *__restrict dst,
                   size_t num_bytes, iomode_t mode)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if likely(stream != NULL) {
		if (stream->mso_readv)
			return (*stream->mso_readv)(self, dst, num_bytes, mode);
		if (stream->mso_read) {
			size_t result = 0;
			struct iov_entry ent;
			IOV_BUFFER_FOREACH(ent, dst) {
				size_t part;
				if (!ent.ive_size)
					continue;
				TRY {
					part = (*stream->mso_read)(self, ent.ive_base,
					                           ent.ive_size, mode);
				} EXCEPT {
					if ((was_thrown(E_INTERRUPT_USER_RPC) ||
					     was_thrown(E_WOULDBLOCK)) &&
					    result != 0)
						goto done_read;
					RETHROW();
				}
				result += part;
				if (part < ent.ive_size)
					break;
				/* Don't block for the remainder */
				mode |= IO_NONBLOCK | IO_NODATAZERO;
			}
done_read:
			return result;
		}
	}
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_READ);
}

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_mfile_writev(struct mfile *__restrict self,
                    struct iov_buffer *__restrict src,
                    size_t num_bytes, iomode_t mode)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if likely(stream != NULL) {
		if (stream->mso_writev)
			return (*stream->mso_writev)(self, src, num_bytes, mode);
		if (stream->mso_write) {
			size_t result = 0;
			struct iov_entry ent;
			IOV_BUFFER_FOREACH(ent, src) {
				size_t part;
				if (!ent.ive_size)
					continue;
				TRY {
					part = (*stream->mso_write)(self, ent.ive_base,
					                            ent.ive_size, mode);
				} EXCEPT {
					if ((was_thrown(E_INTERRUPT_USER_RPC) ||
					     was_thrown(E_WOULDBLOCK)) &&
					    result != 0)
						goto done_write;
					RETHROW();
				}
				result += part;
				if (part < ent.ive_size)
					break;
				/* Don't block for the remainder */
				mode |= IO_NONBLOCK | IO_NODATAZERO;
			}
done_write:
			return result;
		}
	}
	if likely(!(self->mf_flags & MFILE_F_NOUSRIO) && (mode & IO_APPEND))
		return mfile_tailwritev(self, src, 0, num_bytes);
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_WRITE);
}

PUBLIC WUNUSED NONNULL((1, 2)) size_t KCALL
mfile_utailwritev(struct mfile *__restrict self,
                  struct iov_buffer *__restrict src,
                  size_t num_bytes, iomode_t mode)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if likely(stream != NULL) {
		if (stream->mso_writev)
			return (*stream->mso_writev)(self, src, num_bytes, mode | IO_APPEND);
		if (stream->mso_write) {
			size_t result = 0;
			struct iov_entry ent;
			IOV_BUFFER_FOREACH(ent, src) {
				size_t part;
				if (!ent.ive_size)
					continue;
				TRY {
					part = (*stream->mso_write)(self, ent.ive_base,
					                            ent.ive_size,
					                            mode | IO_APPEND);
				} EXCEPT {
					if ((was_thrown(E_INTERRUPT_USER_RPC) ||
					     was_thrown(E_WOULDBLOCK)) &&
					    result != 0)
						goto done_write;
					RETHROW();
				}
				result += part;
				if (part < ent.ive_size)
					break;
				/* Don't block for the remainder */
				mode |= IO_NONBLOCK | IO_NODATAZERO;
			}
done_write:
			return result;
		}
	}
	if likely(!(self->mf_flags & MFILE_F_NOUSRIO))
		return mfile_tailwritev(self, src, 0, num_bytes);
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_WRITE);
}

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_mfile_preadv(struct mfile *__restrict self,
                    struct iov_buffer *__restrict dst,
                    size_t num_bytes, pos_t addr, iomode_t mode)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if (stream != NULL) {
		if (stream->mso_preadv)
			return (*stream->mso_preadv)(self, dst, num_bytes, addr, mode);
		if (stream->mso_pread) {
			size_t result = 0;
			struct iov_entry ent;
			IOV_BUFFER_FOREACH(ent, dst) {
				size_t part;
				if (!ent.ive_size)
					continue;
				TRY {
					part = (*stream->mso_pread)(self, ent.ive_base,
					                            ent.ive_size, addr,
					                            mode);
				} EXCEPT {
					if ((was_thrown(E_INTERRUPT_USER_RPC) ||
					     was_thrown(E_WOULDBLOCK)) &&
					    result != 0)
						goto done_pread;
					RETHROW();
				}
				result += part;
				if (part < ent.ive_size)
					break;
				addr += part;
				/* Don't block for the remainder */
				mode |= IO_NONBLOCK | IO_NODATAZERO;
			}
done_pread:
			return result;
		}
	}
	if likely(!(self->mf_flags & MFILE_F_NOUSRIO))
		return mfile_readv(self, dst, 0, num_bytes, addr);
	if (stream != NULL && addr == 0) {
		if (stream->mso_readv)
			return (*stream->mso_readv)(self, dst, num_bytes, mode);
		if (stream->mso_read) {
			size_t result = 0;
			struct iov_entry ent;
			IOV_BUFFER_FOREACH(ent, dst) {
				size_t part;
				if (!ent.ive_size)
					continue;
				TRY {
					part = (*stream->mso_read)(self, ent.ive_base,
					                           ent.ive_size, mode);
				} EXCEPT {
					if ((was_thrown(E_INTERRUPT_USER_RPC) ||
					     was_thrown(E_WOULDBLOCK)) &&
					    result != 0)
						goto done_read;
					RETHROW();
				}
				result += part;
				if (part < ent.ive_size)
					break;
				/* Don't block for the remainder */
				mode |= IO_NONBLOCK | IO_NODATAZERO;
			}
done_read:
			return result;
		}
	}
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_PREAD);
}

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_mfile_pwritev(struct mfile *__restrict self,
                     struct iov_buffer *__restrict src,
                     size_t num_bytes, pos_t addr, iomode_t mode)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if (stream != NULL) {
		if (stream->mso_pwritev)
			return (*stream->mso_pwritev)(self, src, num_bytes, addr, mode);
		if (stream->mso_pwrite) {
			size_t result = 0;
			struct iov_entry ent;
			IOV_BUFFER_FOREACH(ent, src) {
				size_t part;
				if (!ent.ive_size)
					continue;
				TRY {
					part = (*stream->mso_pwrite)(self, ent.ive_base,
					                             ent.ive_size, addr,
					                             mode);
				} EXCEPT {
					if ((was_thrown(E_INTERRUPT_USER_RPC) ||
					     was_thrown(E_WOULDBLOCK)) &&
					    result != 0)
						goto done_pwrite;
					RETHROW();
				}
				result += part;
				if (part < ent.ive_size)
					break;
				addr += part;
				/* Don't block for the remainder */
				mode |= IO_NONBLOCK | IO_NODATAZERO;
			}
done_pwrite:
			return result;
		}
	}
	if likely(!(self->mf_flags & MFILE_F_NOUSRIO))
		return mfile_writev(self, src, 0, num_bytes, addr);
	if (stream != NULL && addr == 0) {
		if (stream->mso_writev)
			return (*stream->mso_writev)(self, src, num_bytes, mode);
		if (stream->mso_write) {
			size_t result = 0;
			struct iov_entry ent;
			IOV_BUFFER_FOREACH(ent, src) {
				size_t part;
				if (!ent.ive_size)
					continue;
				TRY {
					part = (*stream->mso_write)(self, ent.ive_base,
					                            ent.ive_size, mode);
				} EXCEPT {
					if ((was_thrown(E_INTERRUPT_USER_RPC) ||
					     was_thrown(E_WOULDBLOCK)) &&
					    result != 0)
						goto done_write;
					RETHROW();
				}
				result += part;
				if (part < ent.ive_size)
					break;
				/* Don't block for the remainder */
				mode |= IO_NONBLOCK | IO_NODATAZERO;
			}
done_write:
			return result;
		}
	}
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_PWRITE);
}

INTERN NONNULL((1)) pos_t KCALL
handle_mfile_seek(struct mfile *__restrict self,
                  off_t offset, unsigned int whence)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if likely(stream != NULL && stream->mso_seek)
		return (*stream->mso_seek)(self, offset, whence);
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_SEEK);
}

INTERN NONNULL((1)) syscall_slong_t KCALL
handle_mfile_ioctl(struct mfile *__restrict self, syscall_ulong_t cmd,
                   USER UNCHECKED void *arg, iomode_t mode)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if likely(stream != NULL && stream->mso_ioctl)
		return (*stream->mso_ioctl)(self, cmd, arg, mode);
	THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
	      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
	      cmd);
}

INTERN NONNULL((1)) void KCALL
handle_mfile_truncate(struct mfile *__restrict self,
                      pos_t new_size)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if (stream != NULL && stream->mso_truncate) {
		(*stream->mso_truncate)(self, new_size);
		return;
	}
	if likely(!(self->mf_flags & MFILE_F_NOUSRIO)) {
		mfile_truncate(self, new_size);
		return;
	}
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_TRUNC);
}

INTERN NONNULL((1, 2)) void KCALL
handle_mfile_mmap(struct mfile *__restrict self,
                  struct handle_mmap_info *__restrict info)
		THROWS(...) {
	struct mfile_stream_ops const *stream;

	/* Special case for device files (which have fixed filesystem names) */
	if (mfile_isdevice(self)) {
		if (!info->hmi_fsname) {
			struct device *dev = mfile_asdevice(self);
			devfs_byname_read();
			if (dev->dv_byname_node.rb_lhs != DEVICE_BYNAME_DELETED)
				info->hmi_fsname = incref(&dev->dv_dirent->dd_dirent);
			devfs_byname_endread();
		}
		if (!info->hmi_fspath)
			info->hmi_fspath = vfs_mount_location(THIS_VFS, &devfs.fs_root);
	}

	/* Invoke the optional streams override operator. */
	stream = self->mf_ops->mo_stream;
	if (stream != NULL && stream->mso_mmap) {
		(*stream->mso_mmap)(self, info);
		return;
	}

	/* Fallback: any mfile can be mmap'd (because that's what they're there for)
	 *           However, the `MFILE_F_NOUSRMMAP' flag can be used to deny user-
	 *           space the right to do that. */
	if likely(!(self->mf_flags & MFILE_F_NOUSRMMAP)) {
		info->hmi_file = incref(self);
		return;
	}
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_MMAP);
}

INTERN NONNULL((1)) pos_t KCALL
handle_mfile_allocate(struct mfile *__restrict self,
                      fallocate_mode_t mode,
                      pos_t start, pos_t length)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if (stream != NULL && stream->mso_allocate) {
		return (*stream->mso_allocate)(self, mode, start, length);
	}
	if likely(!(self->mf_flags & MFILE_F_NOUSRIO)) {
		/* TODO: mfile_allocate()   (pre-load parts of the file into memory) */
		return 0;
	}
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_ALLOCATE);
}

INTERN NONNULL((1)) void KCALL
handle_mfile_sync(struct mfile *__restrict self)
		THROWS(...) {
	if (mfile_isnode(self)) {
		struct fnode *node;
		node = mfile_asnode(self);
		fnode_syncdata(node);
		fnode_syncattr(node);
	} else {
		mfile_sync(self);
	}
}

INTERN NONNULL((1)) void KCALL
handle_mfile_datasync(struct mfile *__restrict self)
		THROWS(...) {
	if (mfile_isnode(self)) {
		struct fnode *node;
		node = mfile_asnode(self);
		fnode_syncdata(node);
	} else {
		mfile_sync(self);
	}
}

INTERN NONNULL((1)) void KCALL
handle_mfile_stat(struct mfile *__restrict self,
                  USER CHECKED struct stat *result)
		THROWS(...) {
	dev_t st_dev;
	ino_t st_ino;
	mode_t st_mode;
	nlink_t st_nlink;
	uid_t st_uid;
	gid_t st_gid;
	dev_t st_rdev;
	pos_t st_size;
	blksize_t st_blksize;
	struct timespec st_atimespec;
	struct timespec st_mtimespec;
	struct timespec st_ctimespec;

	mfile_tslock_acquire(self);
	st_size = (pos_t)atomic64_read(&self->mf_filesize);
	if (mfile_isanon(self))
		st_size = 0;
	st_blksize = (blksize_t)(self->mf_part_amask + 1);

	memcpy(&st_atimespec, &self->mf_atime, sizeof(struct timespec));
	memcpy(&st_mtimespec, &self->mf_mtime, sizeof(struct timespec));
	memcpy(&st_ctimespec, &self->mf_ctime, sizeof(struct timespec));

	st_dev = st_rdev = 0;
	if (mfile_isnode(self)) {
		struct fnode *me;
		struct fdevnode *blk;
		me  = mfile_asnode(self);
		blk = (struct fdevnode *)me->fn_super->fs_dev;
		/* Fill in extended file-node information */
		if (blk)
			st_dev = blk->dn_devno;
		st_ino   = me->fn_ino;
		st_mode  = me->fn_mode;
		st_nlink = me->fn_nlink;
		st_uid   = me->fn_uid;
		st_gid   = me->fn_gid;
		if (fnode_isdevnode(me))
			st_rdev = fnode_asdevnode(me)->dn_devno;
	} else {
		st_ino   = 0;
		st_mode  = 0777 | S_IFBLK;
		st_nlink = 1;
		st_uid   = 0;
		st_gid   = 0;
	}
	mfile_tslock_release(self);

	/* Check if the file has been deleted. If it has, timestamps are invalid. */
	if (ATOMIC_READ(self->mf_flags) & MFILE_F_DELETED) {
		memset(&st_atimespec, 0, sizeof(struct timespec));
		memset(&st_mtimespec, 0, sizeof(struct timespec));
		memset(&st_ctimespec, 0, sizeof(struct timespec));
	}

	/* Fill in generic default information */
	result->st_dev               = (typeof(result->st_dev))st_dev;
	result->st_ino               = (typeof(result->st_ino))st_ino;
	result->st_mode              = (typeof(result->st_mode))st_mode;
	result->st_nlink             = (typeof(result->st_nlink))st_nlink;
	result->st_uid               = (typeof(result->st_uid))st_uid;
	result->st_gid               = (typeof(result->st_gid))st_gid;
	result->st_rdev              = (typeof(result->st_rdev))st_rdev;
	result->st_size              = (typeof(result->st_size))st_size;
	result->st_blksize           = (typeof(result->st_blksize))st_blksize;
	result->st_blocks            = (typeof(result->st_blocks))CEILDIV(st_size, st_blksize);
	result->st_atimespec.tv_sec  = (typeof(result->st_atimespec.tv_sec))st_atimespec.tv_sec;
	result->st_atimespec.tv_nsec = (typeof(result->st_atimespec.tv_nsec))st_atimespec.tv_nsec;
	result->st_mtimespec.tv_sec  = (typeof(result->st_mtimespec.tv_sec))st_mtimespec.tv_sec;
	result->st_mtimespec.tv_nsec = (typeof(result->st_mtimespec.tv_nsec))st_mtimespec.tv_nsec;
	result->st_ctimespec.tv_sec  = (typeof(result->st_ctimespec.tv_sec))st_ctimespec.tv_sec;
	result->st_ctimespec.tv_nsec = (typeof(result->st_ctimespec.tv_nsec))st_ctimespec.tv_nsec;

	/* If defined, invoke a stat information override callback. */
	{
		struct mfile_stream_ops const *stream;
		stream = self->mf_ops->mo_stream;
		if (stream && stream->mso_stat)
			(*stream->mso_stat)(self, result);
	}
}

INTERN NONNULL((1)) void KCALL
handle_mfile_pollconnect(struct mfile *__restrict self,
                         poll_mode_t what)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if (stream && stream->mso_pollconnect)
		(*stream->mso_pollconnect)(self, what);
}

INTERN WUNUSED NONNULL((1)) poll_mode_t KCALL
handle_mfile_polltest(struct mfile *__restrict self,
                      poll_mode_t what)
		THROWS(...) {
	poll_mode_t result;
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if (stream && stream->mso_polltest)
		result = (*stream->mso_polltest)(self, what);
	else {
		result = what & (POLLINMASK | POLLOUTMASK);
		if (self->mf_flags & MFILE_F_NOUSRIO) {
			result = 0;
			if (stream) {
				if (stream->mso_read || stream->mso_readv)
					result |= what & POLLINMASK;
				if (stream->mso_write || stream->mso_writev)
					result |= what & POLLOUTMASK;
			}
		}
	}
	return result;
}

INTERN NONNULL((1)) syscall_slong_t KCALL
handle_mfile_hop(struct mfile *__restrict self,
                 syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	/* TODO: Default HOP operations. */

	/* Check for a custom HOP override. */
	stream = self->mf_ops->mo_stream;
	if (stream && stream->mso_hop)
		return (*stream->mso_hop)(self, cmd, arg, mode);
	THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
	      E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND,
	      cmd);
}

INTERN NONNULL((1)) REF void *KCALL
handle_mfile_tryas(struct mfile *__restrict self,
                   uintptr_half_t wanted_type)
		THROWS(E_WOULDBLOCK) {
	struct mfile_stream_ops const *stream;
	assert(wanted_type != HANDLE_TYPE_MFILE);
	stream = self->mf_ops->mo_stream;
	if (stream && stream->mso_tryas)
		return (*stream->mso_tryas)(self, wanted_type);
	return NULL;
}

INTERN NONNULL((1, 2)) ssize_t KCALL
handle_mfile_printlink(struct mfile *__restrict self,
                       pformatprinter printer, void *arg)
		THROWS(E_WOULDBLOCK) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if (stream && stream->mso_printlink)
		return (*stream->mso_printlink)(self, printer, arg);

	/* Special handling for known special node types. */
	if (mfile_isnode(self)) {
		struct fnode *node = mfile_asnode(self);

		/* Devfs device files. */
		if (fnode_isdevice(node)) {
			REF struct devdirent *devname;
			REF struct path *devpath;
			struct device *dev = fnode_asdevice(node);
			device_getname_lock_acquire(dev);
			devname = incref(dev->dv_dirent);
			device_getname_lock_release(dev);
			FINALLY_DECREF_UNLIKELY(devname);
			devpath = vfs_mount_location(THIS_VFS, &devfs.fs_root);
			if (devpath) {
				REF struct path *root;
				FINALLY_DECREF_UNLIKELY(devpath);
				root = fs_getroot(THIS_FS);
				FINALLY_DECREF_UNLIKELY(root);
				return path_printent(devpath, devname->dd_dirent.fd_name,
				                     devname->dd_dirent.fd_namelen, printer, arg,
				                     AT_PATHPRINT_INCTRAIL, root);
			}
			return format_printf(printer, arg, "devfs:/%$s",
			                     (size_t)devname->dd_dirent.fd_namelen,
			                     devname->dd_dirent.fd_name);
		}
	}
	return format_printf(printer, arg,
	                     "anon_inode:[mfile:%" PRIuPTR "]",
	                     skew_kernel_pointer(self));
}

DECL_END

#else /* CONFIG_USE_NEW_FS */
#include <fs/fifo.h>
#include <fs/node.h>
#include <fs/special-node.h>
#include <fs/vfs.h>
#include <kernel/aio.h>
#include <kernel/except.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/mman/mpartmeta.h>
#include <kernel/user.h>
#include <sched/cred.h>

#include <hybrid/atomic.h>

#include <kos/except/reason/fs.h>
#include <kos/except/reason/inval.h>
#include <kos/hop/mfile.h>
#include <sys/stat.h>

#include <assert.h>
#include <errno.h>
#include <string.h>

DECL_BEGIN

/* DATABLOCK HANDLE OPERATIONS */
DEFINE_HANDLE_REFCNT_FUNCTIONS(mfile, struct mfile);

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_mfile_read(struct mfile *__restrict self,
                  USER CHECKED void *dst,
                  size_t num_bytes, iomode_t mode) THROWS(...) {
	size_t result;
	if unlikely(!self->mf_ops->mo_stream_read) {
		THROW(E_FSERROR_UNSUPPORTED_OPERATION,
		      E_FILESYSTEM_OPERATION_READ);
	}
	result = (*self->mf_ops->mo_stream_read)(self, dst, num_bytes, mode);
	return result;
}

INTERN NONNULL((1)) size_t KCALL
handle_mfile_write(struct mfile *__restrict self,
                   USER CHECKED void const *src,
                   size_t num_bytes, iomode_t mode) THROWS(...) {
	size_t result;
	if unlikely(!self->mf_ops->mo_stream_write) {
		THROW(E_FSERROR_UNSUPPORTED_OPERATION,
		      E_FILESYSTEM_OPERATION_WRITE);
	}
	result = (*self->mf_ops->mo_stream_write)(self, src, num_bytes, mode);
	return result;
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_mfile_pread(struct mfile *__restrict self,
                   USER CHECKED void *dst,
                   size_t num_bytes, pos_t addr, iomode_t mode) {
	if (vm_datablock_isinode(self)) {
		/* TODO: Support for `IO_NONBLOCK' */
		(void)mode;
		return inode_read((struct inode *)self, dst, num_bytes, addr);
	}
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_PREAD);
}

INTERN NONNULL((1)) size_t KCALL
handle_mfile_pwrite(struct mfile *__restrict self,
                        USER CHECKED void const *src,
                        size_t num_bytes, pos_t addr, iomode_t mode) {
	if (vm_datablock_isinode(self)) {
		/* TODO: Support for `IO_NONBLOCK' */
		(void)mode;
		inode_write((struct inode *)self, src, num_bytes, addr);
		return num_bytes;
	}
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_PWRITE);
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_mfile_preadv(struct mfile *__restrict self,
                    struct iov_buffer *__restrict dst, size_t num_bytes,
                    pos_t addr, iomode_t mode) {
	if (vm_datablock_isinode(self)) {
		/* TODO: Support for `IO_NONBLOCK' */
		(void)mode;
		return inode_readv((struct inode *)self, dst, num_bytes, addr);
	}
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_PREAD);
}

INTERN NONNULL((1)) size_t KCALL
handle_mfile_pwritev(struct mfile *__restrict self,
                     struct iov_buffer *__restrict src, size_t num_bytes,
                     pos_t addr, iomode_t mode) {
	if (vm_datablock_isinode(self)) {
		/* TODO: Support for `IO_NONBLOCK' */
		(void)mode;
		inode_writev((struct inode *)self, src, num_bytes, addr);
		return num_bytes;
	}
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_PWRITE);
}



INTERN NONNULL((1)) void KCALL
handle_mfile_truncate(struct mfile *__restrict self,
                      pos_t new_size) {
	if (vm_datablock_isinode(self)) {
		inode_truncate((struct inode *)self, new_size);
	} else {
		/* TODO: Anonymize the parts of this data block. */
	}
}

/* TODO */
INTERN NONNULL((1)) pos_t KCALL
handle_mfile_allocate(struct mfile *__restrict self,
                      fallocate_mode_t mode,
                      pos_t start, pos_t length);

INTERN NONNULL((1)) void KCALL
handle_mfile_sync(struct mfile *__restrict self) {
	if (vm_datablock_isinode(self))
		inode_sync((struct inode *)self);
	else {
		mfile_sync(self);
	}
}

INTERN NONNULL((1)) void KCALL
handle_mfile_datasync(struct mfile *__restrict self) {
	mfile_sync(self);
}

INTERN NONNULL((1)) void KCALL
handle_mfile_pollconnect(struct mfile *__restrict self,
                         poll_mode_t what) {
	assert((self->mf_ops->dt_handle_pollconnect != NULL) ==
	       (self->mf_ops->dt_handle_polltest != NULL));
	if (self->mf_ops->dt_handle_pollconnect) {
		(*self->mf_ops->dt_handle_pollconnect)(self, what);
	} else if (what & (POLLOUTMASK | POLLINMASK)) {
		if (vm_datablock_isinode(self))
			rwlock_pollconnect(__inode_lock((struct inode *)self));
	}
}

INTERN NONNULL((1)) poll_mode_t KCALL
handle_mfile_polltest(struct mfile *__restrict self,
                      poll_mode_t what) {
	assert((self->mf_ops->dt_handle_pollconnect != NULL) ==
	       (self->mf_ops->dt_handle_polltest != NULL));
	if (self->mf_ops->dt_handle_polltest)
		return (*self->mf_ops->dt_handle_polltest)(self, what);
	if (what & POLLOUTMASK) {
		if (vm_datablock_isinode(self)) {
			if (rwlock_canwrite(__inode_lock((struct inode *)self)))
				return POLLOUTMASK | POLLINMASK;
		} else {
			return POLLOUTMASK | POLLINMASK;
		}
	} else if (what & POLLINMASK) {
		if (vm_datablock_isinode(self)) {
			if (rwlock_canread(__inode_lock((struct inode *)self)))
				return POLLINMASK;
		} else {
			return POLLINMASK;
		}
	}
	return 0;
}


INTERN NONNULL((1)) syscall_slong_t KCALL
handle_mfile_ioctl(struct mfile *__restrict self, syscall_ulong_t cmd,
                   USER UNCHECKED void *arg, iomode_t mode) {
	if (vm_datablock_isinode(self))
		return inode_ioctl((struct inode *)self, cmd, arg, mode);
	THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
	      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
	      cmd);
}

INTERN NONNULL((1)) syscall_slong_t KCALL
handle_mfile_hop(struct mfile *__restrict self, syscall_ulong_t cmd,
                 USER UNCHECKED void *arg, iomode_t mode) {
	switch (cmd) {

	case HOP_MFILE_SYNCALL: {
		pos_t count = mfile_sync(self);
		if (arg) {
			validate_writable(arg, sizeof(u64));
			*(u64 *)arg = (u64)count;
		}
	}	break;

	case HOP_DATABLOCK_ANONYMIZE:
		/* Need write permissions. */
		if ((mode & IO_ACCMODE) == IO_RDONLY)
			THROW(E_INVALID_HANDLE_OPERATION, 0, E_INVALID_HANDLE_OPERATION_TRUNC, mode);
		mfile_delete(self);
		break;

	case HOP_DATABLOCK_OPEN_FUTEX:
	case HOP_DATABLOCK_OPEN_FUTEX_EXISTING: {
		size_t struct_size;
		struct hop_datablock_open_futex *data;
		REF struct mfutex *ftx;
		struct handle hnd;
		/* [struct hop_datablock_open_futex *result] Return an existing a futex for the given address. */
		validate_readwrite(arg, sizeof(struct hop_datablock_open_futex));
		data        = (struct hop_datablock_open_futex *)arg;
		struct_size = ATOMIC_READ(data->dof_struct_size);
		if (struct_size != sizeof(struct hop_datablock_open_futex))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_datablock_open_futex), struct_size);
		if (cmd == HOP_DATABLOCK_OPEN_FUTEX_EXISTING) {
			ftx = mfile_lookupfutex(self, (pos_t)data->dof_address);
			if (!ftx)
				return -ENOENT;
		} else {
			ftx = mfile_createfutex(self, (pos_t)data->dof_address);
		}
		FINALLY_DECREF_UNLIKELY(ftx);
		hnd.h_type = HANDLE_TYPE_FUTEX;
		hnd.h_mode = mode;
		hnd.h_data = ftx;
		return handle_installhop(&data->dof_openfd, hnd);
	}	break;

	case HOP_INODE_OPEN_SUPERBLOCK: {
		struct handle result_handle;
		if (!vm_datablock_isinode(self)) {
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_MFILE,
			      0,
			      HANDLE_TYPEKIND_MFILE_INODE,
			      0);
		}
		result_handle.h_mode = mode;
		result_handle.h_type = HANDLE_TYPE_MFILE;
		result_handle.h_data = ((struct inode *)self)->i_super;
		inode_access_accmode((struct inode *)result_handle.h_data, mode);
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, result_handle);
	}	break;

	case HOP_INODE_CHMOD: {
		size_t struct_size;
		mode_t mask, flag;
		struct hop_inode_chmod *data;
		struct inode *me;
		if (!vm_datablock_isinode(self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_MFILE,
			      0,
			      HANDLE_TYPEKIND_MFILE_INODE,
			      0);
		validate_readwrite(arg, sizeof(struct hop_inode_chmod));
		data        = (struct hop_inode_chmod *)arg;
		struct_size = ATOMIC_READ(data->icm_struct_size);
		if (struct_size != sizeof(struct hop_inode_chmod))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_inode_chmod), struct_size);
		me   = (struct inode *)self;
		mask = ATOMIC_READ(data->icm_perm_mask);
		flag = ATOMIC_READ(data->icm_perm_flag);
		data->icm_perm_old = inode_chmod(me, mask, flag);
	}	break;

	case HOP_INODE_CHOWN: {
		size_t struct_size;
		struct hop_inode_chown *data;
		uid_t old_owner;
		gid_t old_group;
		if (!vm_datablock_isinode(self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_MFILE,
			      0,
			      HANDLE_TYPEKIND_MFILE_INODE,
			      0);
		validate_readwrite(arg, sizeof(struct hop_inode_chown));
		data        = (struct hop_inode_chown *)arg;
		struct_size = ATOMIC_READ(data->ico_struct_size);
		if (struct_size != sizeof(struct hop_inode_chown))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_inode_chown), struct_size);
		inode_chown((struct inode *)self,
		            (uid_t)ATOMIC_READ(data->ico_newowner),
		            (gid_t)ATOMIC_READ(data->ico_newgroup),
		            &old_owner,
		            &old_group);
		COMPILER_WRITE_BARRIER();
		data->ico_oldowner = (u32)old_owner;
		data->ico_oldgroup = (u32)old_group;
	}	break;

	case HOP_DIRECTORY_OPENNODE: {
		size_t struct_size;
		struct hop_directory_opennode *data;
		USER UNCHECKED char const *name;
		u16 namelen, openflags;
		uintptr_t hash;
		REF struct inode *child_node;
		REF struct fdirent *child_entry;
		struct handle temp;
		struct directory_node *me;
		if (!vm_datablock_isinode(self) || !INODE_ISDIR((struct inode *)self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_MFILE,
			      0,
			      HANDLE_TYPEKIND_MFILE_DIRECTORY,
			      0);
		me = (struct directory_node *)self;
		validate_readwrite(arg, sizeof(struct hop_directory_opennode));
		data        = (struct hop_directory_opennode *)arg;
		struct_size = ATOMIC_READ(data->don_struct_size);
		if (struct_size != sizeof(struct hop_directory_opennode))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_directory_opennode), struct_size);
		COMPILER_READ_BARRIER();
		name      = data->don_name;
		namelen   = data->don_len;
		openflags = data->don_flags;
		COMPILER_READ_BARRIER();
		validate_readable(name, namelen);
		VALIDATE_FLAGSET(openflags,
		                 HOP_DIRECTORY_OPENNODE_FNOCASE,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_OPENNODE_FLAGS);
		hash = fdirent_hash(name, namelen);
		if (!capable(CAP_DAC_READ_SEARCH)) {
			inode_loadattr(me);
			inode_access(me, R_OK | X_OK);
		}
		child_node = openflags & HOP_DIRECTORY_OPENNODE_FNOCASE
		             ? directory_getcasenode(me, name, namelen, hash, &child_entry)
		             : directory_getnode(me, name, namelen, hash, &child_entry);
		if unlikely(!child_node)
			THROW(E_FSERROR_FILE_NOT_FOUND);
		{
			struct hop_openfd *fd;
			FINALLY_DECREF(child_entry);
			FINALLY_DECREF(child_node);
			/* Install handles for objects that the caller wants to open */
			fd = ATOMIC_READ(data->don_node);
			if (fd) {
				temp.h_type = HANDLE_TYPE_MFILE;
				temp.h_mode = mode;
				temp.h_data = child_node;
				handle_installhop(fd, temp);
			}
			fd = ATOMIC_READ(data->don_dent);
			if (fd) {
				temp.h_type = HANDLE_TYPE_FDIRENT;
				temp.h_mode = mode;
				temp.h_data = child_entry;
				handle_installhop(fd, temp);
			}
		}
	}	break;

	case HOP_DIRECTORY_CREATFILE: {
		size_t struct_size;
		struct hop_directory_creatfile *data;
		USER UNCHECKED char const *name;
		u16 namelen;
		oflag_t oflags;
		REF struct inode *child_node;
		REF struct fdirent *child_entry;
		struct handle temp;
		mode_t newfile_mode;
		uid_t newfile_owner;
		gid_t newfile_group;
		bool was_newly_created;
		if (!vm_datablock_isinode(self) || !INODE_ISDIR((struct inode *)self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_MFILE,
			      0,
			      HANDLE_TYPEKIND_MFILE_DIRECTORY,
			      0);
		validate_readwrite(arg, sizeof(struct hop_directory_creatfile));
		data        = (struct hop_directory_creatfile *)arg;
		struct_size = ATOMIC_READ(data->dcf_struct_size);
		if (struct_size != sizeof(struct hop_directory_creatfile))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_directory_creatfile), struct_size);
		COMPILER_READ_BARRIER();
		name          = data->dcf_name;
		namelen       = data->dcf_len;
		oflags        = (oflag_t)data->dcf_oflags;
		newfile_mode  = (mode_t)data->dcf_mode;
		newfile_owner = (uid_t)data->dcf_owner;
		newfile_group = (gid_t)data->dcf_group;
		COMPILER_READ_BARRIER();
		validate_readable(name, namelen);
		VALIDATE_FLAGSET(oflags,
		                 O_CREAT | O_EXCL | O_DOSPATH,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_CREATFILE_OFLAGS);
		VALIDATE_FLAGSET(newfile_mode, 07777,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_CREATFILE_MODE);
		if (newfile_owner == (uid_t)-1)
			newfile_owner = fs_getuid(THIS_FS);
		if (newfile_group == (gid_t)-1)
			newfile_group = fs_getgid(THIS_FS);
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		child_node = directory_creatfile((struct directory_node *)self,
		                                 name,
		                                 namelen,
		                                 oflags,
		                                 newfile_owner,
		                                 newfile_group,
		                                 newfile_mode & ~ATOMIC_READ(THIS_FS->f_umask),
		                                 &child_entry,
		                                 &was_newly_created);
		{
			struct hop_openfd *fd;
			FINALLY_DECREF(child_entry);
			FINALLY_DECREF(child_node);
			ATOMIC_WRITE(data->dcf_status, was_newly_created
			                               ? HOP_DIRECTORY_CREATFILE_STATUS_CREATED_NEW
			                               : HOP_DIRECTORY_CREATFILE_STATUS_ALREADY_EXISTED);
			/* Install handles for objects that the caller wants to open */
			fd = ATOMIC_READ(data->dcf_node);
			if (fd) {
				temp.h_type = HANDLE_TYPE_MFILE;
				temp.h_mode = mode;
				temp.h_data = child_node;
				handle_installhop(fd, temp);
			}
			fd = ATOMIC_READ(data->dcf_dent);
			if (fd) {
				temp.h_type = HANDLE_TYPE_FDIRENT;
				temp.h_mode = mode;
				temp.h_data = child_entry;
				handle_installhop(fd, temp);
			}
		}
	}	break;

	case HOP_DIRECTORY_REMOVE: {
		STATIC_ASSERT(HOP_DIRECTORY_REMOVE_FLAG_REGULAR == DIRECTORY_REMOVE_FREGULAR);
		STATIC_ASSERT(HOP_DIRECTORY_REMOVE_FLAG_DIRECTORY == DIRECTORY_REMOVE_FDIRECTORY);
		STATIC_ASSERT(HOP_DIRECTORY_REMOVE_FLAG_NOCASE == DIRECTORY_REMOVE_FNOCASE);
		STATIC_ASSERT(HOP_DIRECTORY_REMOVE_STATUS_UNLINK == DIRECTORY_REMOVE_STATUS_UNLINK);
		STATIC_ASSERT(HOP_DIRECTORY_REMOVE_STATUS_RMDIR == DIRECTORY_REMOVE_STATUS_RMDIR);
		STATIC_ASSERT(HOP_DIRECTORY_REMOVE_STATUS_FDELETED == DIRECTORY_REMOVE_STATUS_FDELETED);
		size_t struct_size;
		struct hop_directory_remove *data;
		USER UNCHECKED char const *name;
		u16 namelen;
		uintptr_t hash;
		unsigned int remove_mode;
		unsigned int remove_status;
		REF struct inode *child_node;
		REF struct fdirent *child_entry;
		struct handle temp;
		if (!vm_datablock_isinode(self) || !INODE_ISDIR((struct inode *)self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_MFILE,
			      0,
			      HANDLE_TYPEKIND_MFILE_DIRECTORY,
			      0);
		validate_readwrite(arg, sizeof(struct hop_directory_remove));
		data        = (struct hop_directory_remove *)arg;
		struct_size = ATOMIC_READ(data->drm_struct_size);
		if (struct_size != sizeof(struct hop_directory_remove))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_directory_remove), struct_size);
		COMPILER_READ_BARRIER();
		name        = data->drm_name;
		namelen     = data->drm_len;
		remove_mode = data->drm_flags;
		COMPILER_READ_BARRIER();
		validate_readable(name, namelen);
		VALIDATE_FLAGSET(remove_mode,
		                 HOP_DIRECTORY_REMOVE_FLAG_REGULAR |
		                 HOP_DIRECTORY_REMOVE_FLAG_DIRECTORY |
		                 HOP_DIRECTORY_REMOVE_FLAG_NOCASE,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_REMOVE_FLAGS);
		if (!(remove_mode & (HOP_DIRECTORY_REMOVE_FLAG_REGULAR | HOP_DIRECTORY_REMOVE_FLAG_DIRECTORY))) {
			THROW(E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION,
			      E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_REMOVE_FLAGS,
			      remove_mode,
			      HOP_DIRECTORY_REMOVE_FLAG_REGULAR | HOP_DIRECTORY_REMOVE_FLAG_DIRECTORY,
			      0);
		}
		hash = fdirent_hash(name, namelen);
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		remove_status = directory_remove((struct directory_node *)self,
		                                 name,
		                                 namelen,
		                                 hash,
		                                 remove_mode,
		                                 &child_node,
		                                 &child_entry,
		                                 NULL,
		                                 NULL);
		{
			struct hop_openfd *fd;
			FINALLY_DECREF(child_entry);
			FINALLY_DECREF(child_node);
			/* Install handles for objects that the caller wants to open */
			ATOMIC_WRITE(data->drm_status, (u16)remove_status);
			fd = ATOMIC_READ(data->drm_node);
			if (fd) {
				temp.h_type = HANDLE_TYPE_MFILE;
				temp.h_mode = mode;
				temp.h_data = child_node;
				handle_installhop(fd, temp);
			}
			fd = ATOMIC_READ(data->drm_dent);
			if (fd) {
				temp.h_type = HANDLE_TYPE_FDIRENT;
				temp.h_mode = mode;
				temp.h_data = child_entry;
				handle_installhop(fd, temp);
			}
		}
	}	break;


	case HOP_DIRECTORY_RENAME: {
		STATIC_ASSERT(HOP_DIRECTORY_RENAME_FNORMAL == DIRECTORY_RENAME_FNORMAL);
		STATIC_ASSERT(HOP_DIRECTORY_RENAME_FNOCASE == DIRECTORY_RENAME_FNOCASE);
		size_t struct_size;
		struct hop_directory_rename *data;
		USER UNCHECKED char const *srcname;
		USER UNCHECKED char const *dstname;
		u16 srcnamelen, dstnamelen;
		unsigned int rename_mode, dstdir;
		REF struct inode *srcchild_node;
		REF struct inode *dstchild_node;
		REF struct fdirent *srcchild_entry;
		REF struct fdirent *dstchild_entry;
		REF struct directory_node *target_dir;
		struct handle temp;
		if (!vm_datablock_isinode(self) || !INODE_ISDIR((struct inode *)self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_MFILE,
			      0,
			      HANDLE_TYPEKIND_MFILE_DIRECTORY,
			      0);
		validate_readwrite(arg, sizeof(struct hop_directory_rename));
		data        = (struct hop_directory_rename *)arg;
		struct_size = ATOMIC_READ(data->drn_struct_size);
		if (struct_size != sizeof(struct hop_directory_rename))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_directory_rename), struct_size);
		COMPILER_READ_BARRIER();
		srcname     = data->drn_srcname;
		srcnamelen  = data->drn_srclen;
		dstname     = data->drn_dstname;
		dstnamelen  = data->drn_dstlen;
		rename_mode = data->drn_flags;
		dstdir      = (unsigned int)data->drn_dstdir;
		COMPILER_READ_BARRIER();
		validate_readable(srcname, srcnamelen);
		validate_readable(dstname, dstnamelen);
		VALIDATE_FLAGSET(rename_mode,
		                 HOP_DIRECTORY_RENAME_FNORMAL |
		                 HOP_DIRECTORY_RENAME_FNOCASE,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_RENAME_FLAGS);
		if (dstdir == (unsigned int)-1) {
			target_dir = (REF struct directory_node *)incref(self);
		} else {
			target_dir = handle_get_dirnode(dstdir);
		}
		{
			FINALLY_DECREF(target_dir);
			cred_require_sysadmin(); /* TODO: More finely grained access! */
			directory_rename((struct directory_node *)self,
			                 srcname,
			                 srcnamelen,
			                 fdirent_hash(srcname, srcnamelen),
			                 target_dir,
			                 dstname,
			                 dstnamelen,
			                 rename_mode,
			                 &srcchild_entry,
			                 &dstchild_entry,
			                 &srcchild_node,
			                 &dstchild_node,
			                 NULL,
			                 NULL);
		}
		{
			struct hop_openfd *fd;
			FINALLY_DECREF(srcchild_entry);
			FINALLY_DECREF(dstchild_entry);
			FINALLY_DECREF(srcchild_node);
			FINALLY_DECREF(dstchild_node);
			/* Install handles for objects that the caller wants to open */
			if ((fd = ATOMIC_READ(data->drn_srcnode)) != NULL) {
				temp.h_type = HANDLE_TYPE_MFILE;
				temp.h_mode = mode;
				temp.h_data = srcchild_node;
				handle_installhop(fd, temp);
			}
			if ((fd = ATOMIC_READ(data->drn_srcdent)) != NULL) {
				temp.h_type = HANDLE_TYPE_FDIRENT;
				temp.h_mode = mode;
				temp.h_data = srcchild_entry;
				handle_installhop(fd, temp);
			}
			if ((fd = ATOMIC_READ(data->drn_dstnode)) != NULL) {
				temp.h_type = HANDLE_TYPE_MFILE;
				temp.h_mode = mode;
				temp.h_data = dstchild_node;
				handle_installhop(fd, temp);
			}
			if ((fd = ATOMIC_READ(data->drn_dstdent)) != NULL) {
				temp.h_type = HANDLE_TYPE_FDIRENT;
				temp.h_mode = mode;
				temp.h_data = dstchild_entry;
				handle_installhop(fd, temp);
			}
		}
	}	break;

	case HOP_DIRECTORY_LINK: {
		STATIC_ASSERT(HOP_DIRECTORY_LINK_FNORMAL == DIRECTORY_LINK_FNORMAL);
		STATIC_ASSERT(HOP_DIRECTORY_LINK_FNOCASE == DIRECTORY_LINK_FNOCASE);
		size_t struct_size;
		struct hop_directory_link *data;
		USER UNCHECKED char const *name;
		u16 namelen;
		unsigned int link_mode;
		REF struct inode *link_node;
		REF struct fdirent *child_entry;
		unsigned int link_nodefd;
		struct handle temp;
		if (!vm_datablock_isinode(self) || !INODE_ISDIR((struct inode *)self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_MFILE,
			      0,
			      HANDLE_TYPEKIND_MFILE_DIRECTORY,
			      0);
		validate_readwrite(arg, sizeof(struct hop_directory_link));
		data        = (struct hop_directory_link *)arg;
		struct_size = ATOMIC_READ(data->dli_struct_size);
		if (struct_size != sizeof(struct hop_directory_link))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_directory_link), struct_size);
		COMPILER_READ_BARRIER();
		name        = data->dli_name;
		namelen     = data->dli_len;
		link_mode   = data->dli_flags;
		link_nodefd = data->dli_linknode;
		COMPILER_READ_BARRIER();
		validate_readable(name, namelen);
		VALIDATE_FLAGSET(link_mode,
		                 HOP_DIRECTORY_LINK_FNOCASE,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_LINK_FLAGS);
		link_node = handle_get_fnode(link_nodefd);
		{
			FINALLY_DECREF(link_node);
			cred_require_sysadmin(); /* TODO: More finely grained access! */
			directory_link((struct directory_node *)self,
			               name,
			               namelen,
			               link_node,
			               link_mode,
			               &child_entry);
		}
		{
			struct hop_openfd *fd;
			FINALLY_DECREF(child_entry);
			/* Install handles for objects that the caller wants to open */
			if ((fd = ATOMIC_READ(data->dli_dent)) != NULL) {
				temp.h_type = HANDLE_TYPE_FDIRENT;
				temp.h_mode = mode;
				temp.h_data = child_entry;
				handle_installhop(fd, temp);
			}
		}
	}	break;

	case HOP_DIRECTORY_SYMLINK: {
		STATIC_ASSERT(HOP_DIRECTORY_SYMLINK_FNORMAL == DIRECTORY_SYMLINK_FNORMAL);
		STATIC_ASSERT(HOP_DIRECTORY_SYMLINK_FNOCASE == DIRECTORY_SYMLINK_FNOCASE);
		size_t struct_size;
		struct hop_directory_symlink *data;
		USER UNCHECKED char const *name;
		u16 namelen;
		USER UNCHECKED char const *text;
		size_t textlen;
		unsigned int symlink_createmode;
		REF struct symlink_node *child_node;
		REF struct fdirent *child_entry;
		struct handle temp;
		mode_t symlink_mode;
		uid_t symlink_owner;
		gid_t symlink_group;
		if (!vm_datablock_isinode(self) || !INODE_ISDIR((struct inode *)self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_MFILE,
			      0,
			      HANDLE_TYPEKIND_MFILE_DIRECTORY,
			      0);
		validate_readwrite(arg, sizeof(struct hop_directory_symlink));
		data        = (struct hop_directory_symlink *)arg;
		struct_size = ATOMIC_READ(data->dsl_struct_size);
		if (struct_size != sizeof(struct hop_directory_symlink))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_directory_symlink), struct_size);
		COMPILER_READ_BARRIER();
		name               = data->dsl_name;
		namelen            = data->dsl_len;
		symlink_createmode = data->dsl_flags;
		text               = data->dsl_text;
		textlen            = data->dsl_textlen;
		symlink_mode       = (mode_t)data->dsl_mode;
		symlink_owner      = (uid_t)data->dsl_owner;
		symlink_group      = (gid_t)data->dsl_group;
		COMPILER_READ_BARRIER();
		validate_readable(name, namelen);
		validate_readable(text, textlen);
		VALIDATE_FLAGSET(symlink_createmode,
		                 HOP_DIRECTORY_SYMLINK_FNOCASE,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_SYMLINK_FLAGS);
		VALIDATE_FLAGSET(symlink_mode, 07777,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_SYMLINK_MODE);
		if (symlink_owner == (uid_t)-1)
			symlink_owner = fs_getuid(THIS_FS);
		if (symlink_group == (gid_t)-1)
			symlink_group = fs_getgid(THIS_FS);
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		child_node = directory_symlink((struct directory_node *)self,
		                               name,
		                               namelen,
		                               text,
		                               textlen,
		                               symlink_owner,
		                               symlink_group,
		                               symlink_mode,
		                               symlink_createmode,
		                               &child_entry);
		{
			struct hop_openfd *fd;
			FINALLY_DECREF(child_entry);
			FINALLY_DECREF(child_node);
			/* Install handles for objects that the caller wants to open */
			if ((fd = ATOMIC_READ(data->dsl_node)) != NULL) {
				temp.h_type = HANDLE_TYPE_MFILE;
				temp.h_mode = mode;
				temp.h_data = child_node;
				handle_installhop(fd, temp);
			}
			if ((fd = ATOMIC_READ(data->dsl_dent)) != NULL) {
				temp.h_type = HANDLE_TYPE_FDIRENT;
				temp.h_mode = mode;
				temp.h_data = child_entry;
				handle_installhop(fd, temp);
			}
		}
	}	break;

	case HOP_DIRECTORY_MKNOD: {
		STATIC_ASSERT(HOP_DIRECTORY_MKNOD_FNORMAL == DIRECTORY_MKNOD_FNORMAL);
		STATIC_ASSERT(HOP_DIRECTORY_MKNOD_FNOCASE == DIRECTORY_MKNOD_FNOCASE);
		size_t struct_size;
		struct hop_directory_mknod *data;
		USER UNCHECKED char const *name;
		u16 namelen;
		unsigned int mknod_mode;
		REF struct inode *child_node;
		REF struct fdirent *child_entry;
		struct handle temp;
		mode_t newfile_mode;
		uid_t newfile_owner;
		gid_t newfile_group;
		dev_t mknod_dev;
		if (!vm_datablock_isinode(self) || !INODE_ISDIR((struct inode *)self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_MFILE,
			      0,
			      HANDLE_TYPEKIND_MFILE_DIRECTORY,
			      0);
		validate_readwrite(arg, sizeof(struct hop_directory_mknod));
		data        = (struct hop_directory_mknod *)arg;
		struct_size = ATOMIC_READ(data->dmn_struct_size);
		if (struct_size != sizeof(struct hop_directory_mknod))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_directory_mknod), struct_size);
		COMPILER_READ_BARRIER();
		name          = data->dmn_name;
		namelen       = data->dmn_len;
		mknod_mode    = data->dmn_flags;
		newfile_mode  = (mode_t)data->dmn_mode;
		newfile_owner = (uid_t)data->dmn_owner;
		newfile_group = (gid_t)data->dmn_group;
		mknod_dev     = (dev_t)data->dmn_device;
		COMPILER_READ_BARRIER();
		validate_readable(name, namelen);
		newfile_mode &= ~ATOMIC_READ(THIS_FS->f_umask);
		VALIDATE_FLAGSET(mknod_mode,
		                 HOP_DIRECTORY_MKNOD_FNOCASE,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKNOD_FLAGS);
		VALIDATE_FLAGSET(newfile_mode, 07777 | S_IFMT,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKNOD_MODE);
		if ((newfile_mode & S_IFMT) != S_IFREG &&
		    (newfile_mode & S_IFMT) != S_IFCHR &&
		    (newfile_mode & S_IFMT) != S_IFBLK) {
			THROW(E_INVALID_ARGUMENT_BAD_FLAG_MASK,
			      E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKNOD_MODE,
			      newfile_mode,
			      S_IFMT);
		}
		if (newfile_owner == (uid_t)-1)
			newfile_owner = fs_getuid(THIS_FS);
		if (newfile_group == (gid_t)-1)
			newfile_group = fs_getgid(THIS_FS);
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		child_node = directory_mknod((struct directory_node *)self,
		                             name,
		                             namelen,
		                             newfile_mode,
		                             newfile_owner,
		                             newfile_group,
		                             mknod_dev,
		                             mknod_mode,
		                             &child_entry);
		{
			struct hop_openfd *fd;
			FINALLY_DECREF(child_entry);
			FINALLY_DECREF(child_node);
			/* Install handles for objects that the caller wants to open */
			if ((fd = ATOMIC_READ(data->dmn_node)) != NULL) {
				temp.h_type = HANDLE_TYPE_MFILE;
				temp.h_mode = mode;
				temp.h_data = child_node;
				handle_installhop(fd, temp);
			}
			if ((fd = ATOMIC_READ(data->dmn_dent)) != NULL) {
				temp.h_type = HANDLE_TYPE_FDIRENT;
				temp.h_mode = mode;
				temp.h_data = child_entry;
				handle_installhop(fd, temp);
			}
		}
	}	break;

	case HOP_DIRECTORY_MKDIR: {
		STATIC_ASSERT(HOP_DIRECTORY_MKDIR_FNORMAL == DIRECTORY_MKDIR_FNORMAL);
		STATIC_ASSERT(HOP_DIRECTORY_MKDIR_FNOCASE == DIRECTORY_MKDIR_FNOCASE);
		size_t struct_size;
		struct hop_directory_mkdir *data;
		USER UNCHECKED char const *name;
		u16 namelen;
		unsigned int mkdir_mode;
		REF struct directory_node *child_node;
		REF struct fdirent *child_entry;
		struct handle temp;
		mode_t newfile_mode;
		uid_t newfile_owner;
		gid_t newfile_group;
		if (!vm_datablock_isinode(self) || !INODE_ISDIR((struct inode *)self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_MFILE,
			      0,
			      HANDLE_TYPEKIND_MFILE_DIRECTORY,
			      0);
		validate_readwrite(arg, sizeof(struct hop_directory_mkdir));
		data        = (struct hop_directory_mkdir *)arg;
		struct_size = ATOMIC_READ(data->dmd_struct_size);
		if (struct_size != sizeof(struct hop_directory_mkdir))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_directory_mkdir), struct_size);
		COMPILER_READ_BARRIER();
		name          = data->dmd_name;
		namelen       = data->dmd_len;
		mkdir_mode    = data->dmd_flags;
		newfile_mode  = (mode_t)data->dmd_mode;
		newfile_owner = (uid_t)data->dmd_owner;
		newfile_group = (gid_t)data->dmd_group;
		COMPILER_READ_BARRIER();
		validate_readable(name, namelen);
		VALIDATE_FLAGSET(mkdir_mode,
		                 HOP_DIRECTORY_MKDIR_FNOCASE,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKDIR_FLAGS);
		VALIDATE_FLAGSET(newfile_mode, 07777,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKDIR_MODE);
		if (newfile_owner == (uid_t)-1)
			newfile_owner = fs_getuid(THIS_FS);
		if (newfile_group == (gid_t)-1)
			newfile_group = fs_getgid(THIS_FS);
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		child_node = directory_mkdir((struct directory_node *)self,
		                             name,
		                             namelen,
		                             newfile_mode & ~ATOMIC_READ(THIS_FS->f_umask),
		                             newfile_owner,
		                             newfile_group,
		                             mkdir_mode,
		                             &child_entry);
		{
			struct hop_openfd *fd;
			FINALLY_DECREF(child_entry);
			FINALLY_DECREF(child_node);
			/* Install handles for objects that the caller wants to open */
			if ((fd = ATOMIC_READ(data->dmd_node)) != NULL) {
				temp.h_type = HANDLE_TYPE_MFILE;
				temp.h_mode = mode;
				temp.h_data = child_node;
				handle_installhop(fd, temp);
			}
			if ((fd = ATOMIC_READ(data->dmd_dent)) != NULL) {
				temp.h_type = HANDLE_TYPE_FDIRENT;
				temp.h_mode = mode;
				temp.h_data = child_entry;
				handle_installhop(fd, temp);
			}
		}
	}	break;

	case HOP_SUPERBLOCK_OPEN_BLKDEV: {
		struct handle result_handle;
		if (!vm_datablock_isinode(self) || !INODE_ISSUPER((struct inode *)self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_MFILE,
			      0,
			      HANDLE_TYPEKIND_MFILE_SUPERBLOCK,
			      0);
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		result_handle.h_data = ((struct superblock *)self)->s_device;
		if (!result_handle.h_data)
			THROW(E_NO_DEVICE, E_NO_DEVICE_KIND_BLKDEV);
		result_handle.h_mode = mode;
		result_handle.h_type = HANDLE_TYPE_BLKDEV;
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, result_handle);
	}	break;

	case HOP_SUPERBLOCK_OPEN_DRIVER: {
		struct handle result_handle;
		if (!vm_datablock_isinode(self) || !INODE_ISSUPER((struct inode *)self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_MFILE,
			      0,
			      HANDLE_TYPEKIND_MFILE_SUPERBLOCK,
			      0);
		cred_require_sysadmin();
		result_handle.h_type = HANDLE_TYPE_MODULE;
		result_handle.h_mode = mode;
		result_handle.h_data = ((struct superblock *)self)->s_driver;
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, result_handle);
	}	break;

	case HOP_SUPERBLOCK_SYNC:
		if (!vm_datablock_isinode(self) || !INODE_ISSUPER((struct inode *)self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_MFILE,
			      0,
			      HANDLE_TYPEKIND_MFILE_SUPERBLOCK,
			      0);
		superblock_sync((struct superblock *)self,
		                (unsigned int)(uintptr_t)arg != 0);
		break;

	case HOP_SUPERBLOCK_FEATURES: {
		struct superblock *super;
		struct hop_superblock_features *data;
		size_t struct_size;
		u32 feat_flags;
		if (!vm_datablock_isinode(self)) {
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_MFILE,
			      0,
			      HANDLE_TYPEKIND_MFILE_INODE,
			      0);
		}
		validate_readwrite(arg, sizeof(struct hop_superblock_features));
		data        = (struct hop_superblock_features *)arg;
		struct_size = ATOMIC_READ(data->sbf_struct_size);
		if (struct_size != sizeof(struct hop_superblock_features))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_superblock_features), struct_size);
		super = ((struct inode *)self)->i_super;
		feat_flags = 0;
		if (superblock_features_has_symlink(&super->s_features))
			feat_flags |= HOP_SUPERBLOCK_FEAT_SYMLINKS;
		if (superblock_features_has_hrdlink(&super->s_features))
			feat_flags |= HOP_SUPERBLOCK_FEAT_HRDLINKS;
		COMPILER_READ_BARRIER();
		/* Copy features info to user-space. */
		data->sbf_features           = feat_flags;
		data->sbf_sector_size        = (u64)1 << self->mf_blockshift;
		data->sbf_link_max           = (u64)super->s_features.sf_link_max;
		data->sbf_name_max           = (u64)super->s_features.sf_name_max;
		data->sbf_symlink_max        = (u64)super->s_features.sf_symlink_max;
		data->sbf_rec_incr_xfer_size = (u32)super->s_features.sf_rec_incr_xfer_size;
		data->sbf_rec_max_xfer_size  = (u32)super->s_features.sf_rec_max_xfer_size;
		data->sbf_rec_min_xfer_size  = (u32)super->s_features.sf_rec_min_xfer_size;
		data->sbf_rec_xfer_align     = (u32)super->s_features.sf_rec_xfer_align;
		data->sbf_filesizebits       = super->s_features.sf_filesizebits;
		data->sbf_magic              = super->s_features.sf_magic;
		COMPILER_READ_BARRIER();
	}	break;

		/* TODO: HOP for using `inode_read_blocking()' */
		/* TODO: HOP for using `inode_readv_blocking()' */

	default:
		/* Handle FIFO control operations if we are referring to one. */
		if (vm_datablock_isinode(self) && INODE_ISFIFO((struct inode *)self))
			return fifo_hop((struct fifo_node *)self, cmd, arg, mode);
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND,
		      cmd);
		break;
	}
	return 0;
}

PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW(KCALL mpart_tree_count)(struct mpart const *__restrict self) {
	size_t result = 0;
again:
	++result;
	assert(!mpart_isanon(self));
	if (self->mp_filent.rb_lhs) {
		if (self->mp_filent.rb_rhs)
			result += mpart_tree_count(self->mp_filent.rb_rhs);
		self = self->mp_filent.rb_lhs;
		goto again;
	}
	if (self->mp_filent.rb_rhs) {
		self = self->mp_filent.rb_rhs;
		goto again;
	}
	return result;
}

INTERN NONNULL((1)) void KCALL
handle_mfile_stat(struct mfile *__restrict self,
                  USER CHECKED struct stat *result) {
	if (vm_datablock_isinode(self)) {
		/* INode stat! */
		inode_stat((struct inode *)self, result);
	} else {
		/* Generic data-block stat */
		size_t partcount = 0;
		mfile_lock_read(self);
		if (self->mf_parts && self->mf_parts != MFILE_PARTS_ANONYMOUS)
			partcount = mpart_tree_count(self->mf_parts);
		mfile_lock_endread(self);
		COMPILER_BARRIER();
		memset(result, 0, sizeof(*result));
		result->st_blksize = (size_t)1 << self->mf_blockshift;
		result->st_blocks  = partcount;
	}
}

INTERN NONNULL((1, 2)) void KCALL
handle_mfile_mmap(struct mfile *__restrict self,
                  struct handle_mmap_info *__restrict info)
		THROWS(...) {
	info->hmi_file = incref(self);
}


DECL_END
#endif /* !CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_HANDLE_C */
