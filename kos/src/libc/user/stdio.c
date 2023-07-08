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
#ifndef GUARD_LIBC_USER_STDIO_C
#define GUARD_LIBC_USER_STDIO_C 1
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/align.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>
#include <hybrid/sched/atomic-lock.h>
#include <hybrid/sched/atomic-rwlock.h>
#include <hybrid/sequence/list.h>

#include <bits/crt/io-file.h>
#include <kos/syscalls.h>
#include <sys/wait.h>

#include <assert.h>
#include <atomic.h>
#include <fcntl.h>
#include <format-printer.h>
#include <limits.h>
#include <malloc.h>
#include <pwd.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unicode.h>
#include <unistd.h>

#include "format-printer.h"
#include "malloc.h"
#include "stdio-api.h"
#include "stdio.h"
#include "stdlib.h"

#ifndef OFF_MAX
#define OFF_MAX __PRIVATE_MAX_S(__SIZEOF_OFF_T__)
#endif /* !OFF_MAX */
#ifndef OFF64_MAX
#define OFF64_MAX __PRIVATE_MAX_S(__SIZEOF_OFF64_T__)
#endif /* !OFF64_MAX */


DECL_BEGIN

#undef libc_ferror_unlocked
#undef libc_feof_unlocked
#define libc_ferror_unlocked libc_ferror
#define libc_feof_unlocked   libc_feof

static_assert(offsetof(FILE, if_ptr) == __OFFSET_IO_FILE_PTR);
static_assert(offsetof(FILE, if_cnt) == __OFFSET_IO_FILE_CNT);
static_assert(offsetof(FILE, if_base) == __OFFSET_IO_FILE_BASE);
static_assert(offsetof(FILE, if_flag) == __OFFSET_IO_FILE_FLAG);
static_assert(offsetof(FILE, if_fd) == __OFFSET_IO_FILE_FD);
static_assert(offsetof(FILE, if_charbuf) == __OFFSET_IO_FILE_CHARBUF);
static_assert(offsetof(FILE, if_bufsiz) == __OFFSET_IO_FILE_BUFSIZ);
static_assert(offsetof(FILE, if_exdata) == __OFFSET_IO_FILE_EXDATA);
static_assert(sizeof(FILE) == __SIZEOF_IO_FILE);

typedef LIST_HEAD_P(FILE) FileList;

/* [0..1][lock(all_files_lock)] Chain of all files.
 * NOTE: This chain excludes the initial stdin, stdout and stderr streams! */
PRIVATE ATTR_SECTION(".bss.crt.application.exit")
FileList all_files = LIST_HEAD_INITIALIZER(all_files);
PRIVATE ATTR_SECTION(".bss.crt.application.exit")
struct atomic_rwlock all_files_lock = ATOMIC_RWLOCK_INIT;

/* Helper macros for `all_files_lock' */
#define all_files_mustreap()   0
#define all_files_reap()       (void)0
#define _all_files_reap()      (void)0
#define all_files_write()      atomic_rwlock_write(&all_files_lock)
#define all_files_trywrite()   atomic_rwlock_trywrite(&all_files_lock)
#define all_files_endwrite()   (atomic_rwlock_endwrite(&all_files_lock), all_files_reap())
#define _all_files_endwrite()  atomic_rwlock_endwrite(&all_files_lock)
#define all_files_read()       atomic_rwlock_read(&all_files_lock)
#define all_files_tryread()    atomic_rwlock_tryread(&all_files_lock)
#define _all_files_endread()   atomic_rwlock_endread(&all_files_lock)
#define all_files_endread()    (void)(atomic_rwlock_endread_ex(&all_files_lock) && (all_files_reap(), 0))
#define _all_files_end()       atomic_rwlock_end(&all_files_lock)
#define all_files_end()        (void)(atomic_rwlock_end_ex(&all_files_lock) && (all_files_reap(), 0))
#define all_files_upgrade()    atomic_rwlock_upgrade(&all_files_lock)
#define all_files_tryupgrade() atomic_rwlock_tryupgrade(&all_files_lock)
#define all_files_downgrade()  atomic_rwlock_downgrade(&all_files_lock)
#define all_files_reading()    atomic_rwlock_reading(&all_files_lock)
#define all_files_writing()    atomic_rwlock_writing(&all_files_lock)
#define all_files_canread()    atomic_rwlock_canread(&all_files_lock)
#define all_files_canwrite()   atomic_rwlock_canwrite(&all_files_lock)
#define all_files_waitread()   atomic_rwlock_waitread(&all_files_lock)
#define all_files_waitwrite()  atomic_rwlock_waitwrite(&all_files_lock)


/* Add the given file to the set of all files */
PRIVATE ATTR_SECTION(".text.crt.FILE.core.utility") NONNULL((1)) void LIBCCALL
allfiles_insert(FILE *__restrict self) {
	all_files_write();
	assert(!LIST_ISBOUND(self, if_exdata->io_link));
	LIST_INSERT_HEAD(&all_files, self, if_exdata->io_link);
	assert(LIST_ISBOUND(self, if_exdata->io_link));
	all_files_endwrite();
}

/* Remove the given file from the set of all files */
PRIVATE ATTR_SECTION(".text.crt.FILE.core.utility") NONNULL((1)) void LIBCCALL
allfiles_remove(FILE *__restrict self) {
	all_files_write();
	assert(LIST_ISBOUND(self, if_exdata->io_link));
	LIST_REMOVE(self, if_exdata->io_link);
	all_files_endwrite();
}


/* [0..1][lock(changed_linebuffered_files_lock)] Chain of tty-buffers. */
PRIVATE ATTR_SECTION(".bss.crt.FILE.core.write")
FileList changed_linebuffered_files = LIST_HEAD_INITIALIZER(changed_linebuffered_files);
PRIVATE ATTR_SECTION(".bss.crt.FILE.core.write")
struct atomic_lock changed_linebuffered_files_lock = ATOMIC_LOCK_INIT;

/* Add the given file to the set of changed line-buffered files */
PRIVATE ATTR_SECTION(".text.crt.FILE.core.write") NONNULL((1)) void LIBCCALL
changed_linebuffered_insert(FILE *__restrict self) {
	atomic_lock_acquire(&changed_linebuffered_files_lock);
	if (!LIST_ISBOUND(self, if_exdata->io_lnch))
		LIST_INSERT_HEAD(&changed_linebuffered_files, self, if_exdata->io_lnch);
	assert(LIST_ISBOUND(self, if_exdata->io_lnch));
	atomic_lock_release(&changed_linebuffered_files_lock);
}

/* Remove the given file from the set of changed line-buffered files */
PRIVATE ATTR_SECTION(".text.crt.FILE.core.write") NONNULL((1)) void LIBCCALL
changed_linebuffered_remove(FILE *__restrict self) {
	atomic_lock_acquire(&changed_linebuffered_files_lock);
	if (LIST_ISBOUND(self, if_exdata->io_lnch))
		LIST_UNBIND(self, if_exdata->io_lnch);
	atomic_lock_release(&changed_linebuffered_files_lock);
}

/* Low-level file read operation. */
PRIVATE ATTR_SECTION(".text.crt.FILE.core.read") NONNULL((1)) ssize_t LIBCCALL
file_system_read(FILE *__restrict self, void *buf, size_t num_bytes) {
	ssize_t result;
	if (self->if_flag & IO_HASVTAB) {
		struct iofile_data *ex;
		ex = self->if_exdata;
		if unlikely(!ex->io_readfn)
			return libc_seterrno(EPERM);
		result = (*ex->io_readfn)(ex->io_cookie, buf, num_bytes);
	} else {
		result = read(self->if_fd, buf, num_bytes);
	}
	return result;
}

/* Low-level file write operation. */
PRIVATE ATTR_SECTION(".text.crt.FILE.core.write") NONNULL((1)) ssize_t LIBCCALL
file_system_write(FILE *__restrict self, void const *buf, size_t num_bytes) {
	ssize_t result;
	if (self->if_flag & IO_HASVTAB) {
		struct iofile_data *ex;
		ex = self->if_exdata;
		if unlikely(!ex->io_writefn)
			return libc_seterrno(EPERM);
		result = (*ex->io_writefn)(ex->io_cookie, buf, num_bytes);
	} else {
		result = write(self->if_fd, buf, num_bytes);
	}
	return result;
}

PRIVATE ATTR_SECTION(".text.crt.FILE.core.write") NONNULL((1)) ssize_t LIBCCALL
file_system_writeall(FILE *__restrict self, void const *buf, size_t num_bytes) {
	ssize_t result;
	if (self->if_flag & IO_HASVTAB) {
		struct iofile_data *ex;
		ex = self->if_exdata;
		if unlikely(!ex->io_writefn)
			return libc_seterrno(EPERM);
		result = (*ex->io_writefn)(ex->io_cookie, buf, num_bytes);
		if (result > 0 && (size_t)result < num_bytes) {
			/* Keep on writing */
			for (;;) {
				ssize_t temp;
				temp = (*ex->io_writefn)(ex->io_cookie,
				                         (byte_t const *)buf + (size_t)result,
				                         num_bytes - (size_t)result);
				if (temp <= 0) {
					result = temp;
					break;
				}
				result += temp;
				if ((size_t)result >= num_bytes)
					break;
			}
		}
	} else {
		result = writeall(self->if_fd, buf, num_bytes);
	}
	return result;
}

/* Low-level file seek operation. */
PRIVATE ATTR_SECTION(".text.crt.FILE.core.seek") NONNULL((1)) off64_t LIBCCALL
file_system_seek(FILE *__restrict self, off64_t offset, int whence) {
	off64_t result;
	if (self->if_flag & IO_HASVTAB) {
		struct iofile_data *ex;
		ex = self->if_exdata;
		if unlikely(!ex->io_seekfn)
			return libc_seterrno(EPERM);
		result = (*ex->io_seekfn)(ex->io_cookie, offset, whence);
	} else {
		result = lseek64(self->if_fd, offset, whence);
	}
	return result;
}

/* Low-level file close operation. */
PRIVATE ATTR_SECTION(".text.crt.FILE.core.utility") NONNULL((1)) int LIBCCALL
file_system_close(FILE *__restrict self) {
	int result;
	if (self->if_flag & IO_HASVTAB) {
		struct iofile_data *ex;
		ex     = self->if_exdata;
		result = 0;
		if (ex->io_closefn != NULL)
			result = (*ex->io_closefn)(ex->io_cookie);
	} else {
		result = close(self->if_fd);
	}
	return result;
}

/* Low-level file sync operation. */
PRIVATE ATTR_SECTION(".text.crt.FILE.core.write") NONNULL((1)) int LIBCCALL
file_system_sync(FILE *__restrict self) {
	int result;
	if (self->if_flag & IO_HASVTAB) {
		struct iofile_data *ex;
		ex     = self->if_exdata;
		result = 0;
		if (ex->io_flushfn != NULL)
			result = (*ex->io_flushfn)(ex->io_cookie);
	} else {
		result = fsync(self->if_fd);
	}
	return result;
}

/* Low-level file truncate operation. */
PRIVATE ATTR_SECTION(".text.crt.FILE.core.write") NONNULL((1)) int LIBCCALL
file_system_trunc(FILE *__restrict self, pos64_t new_size) {
	int result;
	if (self->if_flag & IO_HASVTAB) {
		/* Not allowed for VTABLE files. */
		result = (int)libc_seterrno(EPERM);
	} else {
		result = ftruncate64(self->if_fd, new_size);
	}
	return result;
}

/* Determine if `self' is a TTY */
INTERN ATTR_SECTION(".text.crt.FILE.core.utility") NONNULL((1)) void LIBCCALL
file_determine_isatty(FILE *__restrict self) {
	uint32_t flags = self->if_flag;
	if (!(flags & (IO_NOTATTY | IO_ISATTY))) {
		if (flags & IO_HASVTAB) {
			flags |= IO_NOTATTY;
		} else {
			int is_a_tty;
			errno_t saved_errno;
			/* Preserve errno */
			saved_errno = libc_geterrno();
			is_a_tty    = isatty(self->if_fd);
			(void)libc_seterrno(saved_errno);
			flags |= is_a_tty ? IO_ISATTY : IO_NOTATTY;
		}
		self->if_flag = flags;
	}
	if (flags & IO_LNIFTYY) {
		self->if_flag &= ~IO_LNIFTYY;
		/* Set the line-buffered flag if it is a TTY. */
		if (flags & IO_ISATTY)
			self->if_flag |= IO_LNBUF;
	}
}


PRIVATE ATTR_SECTION(".text.crt.FILE.core.utility") byte_t *LIBCCALL
file_buffer_realloc(FILE *__restrict self, size_t new_size) {
	if (!(self->if_flag & IO_MALLBUF))
		return (byte_t *)malloc(new_size);
	assert(!(self->if_flag & IO_READING));
	return (byte_t *)realloc(self->if_base, new_size);
}

PRIVATE ATTR_SECTION(".text.crt.FILE.core.utility") byte_t *LIBCCALL
file_buffer_realloc_dynscale(FILE *__restrict self,
                             size_t *__restrict pnew_size,
                             pos64_t fpos) {
	size_t lower_limit;
	if (fpos >= (pos64_t)IOBUF_MAX * IOBUF_FACTOR) {
		lower_limit = IOBUF_MAX;
	} else {
		lower_limit = (size_t)(fpos / IOBUF_FACTOR);
	}
	if (*pnew_size < lower_limit)
		*pnew_size = lower_limit;
	return file_buffer_realloc(self, *pnew_size);

}


/* Change the operations mode of a given buffer. */
PRIVATE WUNUSED ATTR_SECTION(".text.crt.FILE.core.utility") NONNULL((1)) int LIBCCALL
file_setmode(FILE *__restrict self, void *buf, unsigned int mode, size_t size) {
	/* Convert DOS names. */
	if unlikely(mode == 0x0040)
		mode = _IOLBF;
	if unlikely(mode == 0x0004)
		mode = _IONBF;
	/* Translate buffer mode into file flags. */
	if (mode == _IONBF) {
		mode = IO_NODYNSCALE;
	} else if (mode == _IOFBF) {
		mode = 0;
	} else {
		mode = IO_LNBUF;
	}
	/* Set new file flags. */
	self->if_flag &= ~(IO_NODYNSCALE | IO_LNBUF | IO_LNIFTYY);
	self->if_flag |= mode;
	self->if_exdata->io_chsz = 0;
	if (!size) {
		if (!(self->if_flag & IO_NODYNSCALE)) {
			if (self->if_flag & IO_READING)
				goto err_cannot_resize;
			/* Resize-to-zero. */
			if (self->if_flag & IO_MALLBUF)
				free(self->if_base);
			self->if_ptr    = (uint8_t *)(uintptr_t)(self->if_ptr - self->if_base);
			self->if_cnt    = 0;
			self->if_bufsiz = 0;
			self->if_base   = NULL;
		} else {
			/* Dynamically scaled buffer. */
		}
	} else if (buf != NULL) {
		size_t bufoff;
		if (buf == self->if_base &&
		    size == self->if_bufsiz)
			goto done; /* Unchanged. */
		/* User-defined buffer. */
		if (self->if_flag & IO_READING)
			goto err_cannot_resize;
		/* Check how we should update the base-pointer. */
		bufoff = (size_t)(self->if_ptr - self->if_base);
		if (bufoff >= size) {
			/* Clear the available-buffer now that
			 * it has been  truncated to  ZERO(0). */
			self->if_cnt = 0;
		} else {
			size_t minsiz = (size_t)((self->if_base + size) - self->if_ptr);
			/* Truncate the available-buffer. */
			if (self->if_cnt > minsiz)
				self->if_cnt = minsiz;
			/* Copy data into the new buffer. */
			memcpy(buf, self->if_base, self->if_cnt);
		}
		if (self->if_flag & IO_MALLBUF)
			free(self->if_base);
		/* Relocate pointers. */
		self->if_ptr    = (byte_t *)buf + (self->if_ptr - self->if_base);
		self->if_base   = (byte_t *)buf;
		self->if_bufsiz = size;
	} else if (size != self->if_bufsiz) {
		size_t bufoff;
		byte_t *new_buffer;
		if (self->if_flag & IO_READING)
			goto err_cannot_resize;
		new_buffer = file_buffer_realloc(self, size);
		if unlikely(!new_buffer)
			goto err;
		/* Figure out where pointers are located at and update them. */
		bufoff = (size_t)(self->if_ptr - self->if_base);
		if (bufoff >= size) {
			/* Clear the available-buffer now that
			 * it has been  truncated to  ZERO(0). */
			self->if_cnt = 0;
		} else {
			size_t minsiz = (size_t)((self->if_base + size) - self->if_ptr);
			/* Truncate the available-buffer. */
			if (self->if_cnt > minsiz)
				self->if_cnt = minsiz;
		}
		/* Relocate pointers. */
		self->if_ptr    = new_buffer + (self->if_ptr - self->if_base);
		self->if_base   = new_buffer;
		self->if_bufsiz = size;
		self->if_flag  |= IO_MALLBUF;
	}
	self->if_exdata->io_chng = self->if_base;
done:
	return 0;
err_cannot_resize:
	/* This can happen if the function is called from a FILE cookie. */
	(void)libc_seterrno(EWOULDBLOCK);
err:
	return -1;
}

INTERN ATTR_SECTION(".text.crt.FILE.core.write") NONNULL((1)) int LIBCCALL
file_sync(FILE *__restrict self) {
	pos64_t abs_chngpos;
	size_t changed_size;
	ssize_t temp;
	uint32_t old_flags;
	struct iofile_data *ex;
	assert(self);
	ex = self->if_exdata;
	assert(ex);
again:
	changed_size = ex->io_chsz;
	if (!changed_size)
		goto done;
	abs_chngpos = ex->io_fblk;
	abs_chngpos += (ex->io_chng - self->if_base);
	if (abs_chngpos != ex->io_fpos) {
		off64_t new_pos;
		/* Seek to the position where we need to change stuff. */
		new_pos = file_system_seek(self, (off64_t)abs_chngpos, SEEK_SET);
		if unlikely(new_pos == (off64_t)-1)
			goto err;
		ex->io_fpos = (pos64_t)new_pos;
		/* Since the buffer may have changed, we need to start over. */
		goto again;
	}
	/* Write all changed data. */
	old_flags = self->if_flag;
	self->if_flag |= IO_READING;
	COMPILER_BARRIER();
	temp = file_system_writeall(self,
	                            ex->io_chng,
	                            changed_size);
	COMPILER_BARRIER();
	self->if_flag &= ~IO_READING;
	self->if_flag |= old_flags & IO_READING;
	if unlikely(temp < 0)
		goto err;
	if (changed_size == ex->io_chsz &&
	    abs_chngpos == ex->io_fblk + (ex->io_chng - self->if_base)) {
		/* Data was synchronized. */
		ex->io_chsz = 0;
		ex->io_fpos += changed_size;
		self->if_ptr = ex->io_chng + changed_size;

		/* Remove the file from the chain of changed, line-buffered files. */
		changed_linebuffered_remove(self);

		/* Also synchronize the underlying file. */
		if (self->if_flag & IO_FSYNC) {
			int error;
			error = file_system_sync(self);
			if (error != 0)
				return error;
		}
	}
done:
	return 0;
err:
	self->if_flag |= IO_ERR;
	return -1;
}

INTERN NONNULL((1)) ATTR_SECTION(".text.crt.FILE.core.utility") void LIBCCALL
file_destroy(FILE *__restrict self) {
	refcnt_t refcnt;
	struct iofile_data *ex;
	ex = self->if_exdata;

	/* Last reference -> This file has to go away! */
	assert(!shared_recursive_rwlock_reading(&ex->io_lock));
	assert(!(self->if_flag & IO_READING));
	if (ex->io_chsz != 0) {
		/* The file still contains some changed data.
		 * -> Try to flush data data. */
		shared_recursive_rwlock_init_read(&ex->io_lock);
		atomic_write(&ex->io_refcnt, 1);

		/* NOTE: Errors during this sync are ignored! */
		file_sync(self);
		shared_recursive_rwlock_endread(&ex->io_lock);
		refcnt = atomic_fetchdec(&ex->io_refcnt);
		assert(refcnt != 0);
		if (refcnt != 1)
			return; /* The file was revived. */
	}
	assert(!shared_recursive_rwlock_reading(&ex->io_lock));
	assert(!(self->if_flag & IO_READING));

	/* Close the underlying file. */
	if (self->if_flag & IO_HASVTAB) {
		/* In this case, we have to be careful in case the file gets revived. */
		shared_recursive_rwlock_init_read(&ex->io_lock);
		atomic_write(&ex->io_refcnt, 1);
		/* NOTE: Errors during this close are ignored! */
		if (ex->io_closefn != NULL) {
			errno_t saved_errno;
			saved_errno = libc_geterrno_safe();
			(*ex->io_closefn)(ex->io_cookie);
			(void)libc_seterrno(saved_errno);
		}
		shared_recursive_rwlock_endread(&ex->io_lock);
		refcnt = atomic_fetchdec(&ex->io_refcnt);
		assert(refcnt != 0);
		if (refcnt != 1)
			return; /* The file was revived. */
	} else {
		if likely(self->if_fd >= 0)
			sys_close(self->if_fd);
	}
	assert(!shared_recursive_rwlock_reading(&ex->io_lock));
	assert(!(self->if_flag & IO_READING));

	/* Make sure that the file is no longer accessible through the global file lists. */
	if (LIST_ISBOUND(self, if_exdata->io_lnch))
		changed_linebuffered_remove(self);
	allfiles_remove(self);

	/* Free a heap-allocated buffer. */
	if (self->if_flag & IO_MALLBUF)
		free(self->if_base);

	/* Free the dynamically allocated fgetln(3) buffer. */
	free(ex->io_getln);

#if 1 /* This is always the case... */
	assert(ex == (struct iofile_data *)(self + 1));
#else
	if (ex != (struct iofile_data *)(self + 1))
		free(ex);
#endif
	file_free(self);
}



/* Synchronize unwritten data of all line-buffered files. */
INTERN ATTR_SECTION(".text.crt.FILE.core.write") void LIBCCALL
file_sync_lnfiles(void) {
	FILE *fp;
again:
	if (LIST_EMPTY(&changed_linebuffered_files))
		return;
	atomic_lock_acquire(&changed_linebuffered_files_lock);
	LIST_FOREACH (fp, &changed_linebuffered_files, if_exdata->io_lnch) {
		/* Skip files which we can't incref. */
		if (!tryincref(fp))
			continue;
		/* Unbind the file from the chain of changed line-buffered files. */
		LIST_UNBIND(fp, if_exdata->io_lnch);
		atomic_lock_release(&changed_linebuffered_files_lock);
		/* Synchronize this buffer. */
		if (FMUSTLOCK(fp)) {
			file_lock_write(fp);
			file_sync(fp);
			file_lock_endwrite(fp);
		} else {
			file_sync(fp);
		}
		decref(fp);
		goto again;
	}
	atomic_lock_release(&changed_linebuffered_files_lock);
}

PRIVATE ATTR_SECTION(".text.crt.application.exit") void LIBCCALL
file_do_syncall_locked(uintptr_t version) {
	for (;;) {
		FILE *fp, *next_fp;
		all_files_read();
		LIST_FOREACH (fp, &all_files, if_exdata->io_link) {
			if (fp->if_exdata->io_fver != version) {
				if (tryincref(fp))
					break;
			}
		}
		all_files_endread();
		if (!fp)
			break;
do_flush_fp:
		if (FMUSTLOCK(fp)) {
			file_lock_write(fp);
			fp->if_exdata->io_fver = version;
			file_sync(fp);
			file_lock_endwrite(fp);
		} else {
			fp->if_exdata->io_fver = version;
			file_sync(fp);
		}
		all_files_read();
		next_fp = LIST_NEXT(fp, if_exdata->io_link);
		while (next_fp &&
		       (next_fp->if_exdata->io_fver == version ||
		        !tryincref(next_fp)))
			next_fp = LIST_NEXT(next_fp, if_exdata->io_link);
		all_files_endread();
		decref(fp);
		if (!next_fp)
			continue; /* Do another full scan for changed files. */
		fp = next_fp;
		goto do_flush_fp;
	}
}

PRIVATE ATTR_SECTION(".text.crt.FILE.unlocked.write.utility") void LIBCCALL
file_do_syncall_unlocked(uintptr_t version) {
	for (;;) {
		FILE *fp, *next_fp;
		all_files_read();
		LIST_FOREACH (fp, &all_files, if_exdata->io_link) {
			if (fp->if_exdata->io_fver != version) {
				if (tryincref(fp))
					break;
			}
		}
		all_files_endread();
		if (!fp)
			break;
do_flush_fp:
		fp->if_exdata->io_fver = version;
		file_sync(fp);
		all_files_read();
		next_fp = LIST_NEXT(fp, if_exdata->io_link);
		while (next_fp &&
		       (next_fp->if_exdata->io_fver == version ||
		        !tryincref(next_fp)))
			next_fp = LIST_NEXT(next_fp, if_exdata->io_link);
		all_files_endread();
		decref(fp);
		if (!next_fp)
			continue; /* Do another full scan for changed files. */
		fp = next_fp;
		goto do_flush_fp;
	}
}


PRIVATE ATTR_SECTION(".bss.crt.application.exit")
struct shared_recursive_rwlock flushall_lock = SHARED_RECURSIVE_RWLOCK_INIT;
PRIVATE ATTR_SECTION(".bss.crt.application.exit") uintptr_t flushall_version = 0;
PRIVATE ATTR_SECTION(".bss.crt.application.exit") bool flushall_must_restart = false;

PRIVATE ATTR_SECTION(".text.crt.application.exit") void LIBCCALL
file_syncall_locked(void) {
	/* Check for recursion (as is possible due to file cookies) */
	if (shared_recursive_rwlock_writing(&flushall_lock)) {
		/* Don't allow recursion, but solve the problem by re-starting the flush operation. */
		flushall_must_restart = true;
		return;
	}
	shared_recursive_rwlock_write(&flushall_lock);
	do {
		flushall_must_restart = false;
		file_do_syncall_locked(flushall_version++);
	} while (flushall_must_restart);
	shared_recursive_rwlock_endwrite(&flushall_lock);
}

PRIVATE ATTR_SECTION(".text.crt.FILE.unlocked.write.utility") void LIBCCALL
file_syncall_unlocked(void) {
	/* Check for recursion (as is possible due to file cookies) */
	if (shared_recursive_rwlock_writing(&flushall_lock)) {
		/* Don't allow recursion, but solve the problem by re-starting the flush operation. */
		flushall_must_restart = true;
		return;
	}
	shared_recursive_rwlock_write(&flushall_lock);
	do {
		flushall_must_restart = false;
		file_do_syncall_unlocked(flushall_version++);
	} while (flushall_must_restart);
	shared_recursive_rwlock_endwrite(&flushall_lock);
}


/* High-level, common read-from-file function. */
INTERN ATTR_SECTION(".text.crt.FILE.core.read") NONNULL((1)) size_t LIBCCALL
file_readdata(FILE *__restrict self, void *buf, size_t num_bytes) {
	ssize_t read_size;
	size_t result = 0;
	size_t bufavail;
	uint32_t old_flags;
	pos64_t next_data;
	bool did_read_data = false;
	struct iofile_data *ex;
	assert(self);
	ex = self->if_exdata;
	assert(ex);
again:
	bufavail = self->if_cnt;
	if likely(bufavail) {
read_from_buffer:
		if (bufavail > num_bytes)
			bufavail = num_bytes;
		memcpy(buf, self->if_ptr, bufavail);

		/* Update buf pointers. */
		self->if_cnt -= bufavail;
		self->if_ptr += bufavail;
		result += bufavail;
		num_bytes -= bufavail;
		if (!num_bytes)
			goto done_noeof;

		/* Make sure that we only invoke read() on the  underlying
		 * file once, so-as to ensure that we don't start blocking
		 * because the underlying file is pipe-like and now empty,
		 * before the caller got a chance to process the data that
		 * we _did_ manage to extract! */
		if (did_read_data)
			goto done;
		buf = (byte_t *)buf + bufavail;
	}

	/* The buf is empty and must be re-filled. */
	/* First off: Flush any changes that had been made. */
	COMPILER_BARRIER();
	if (file_sync(self))
		goto err;
	if (self->if_flag & IO_LNIFTYY)
		file_determine_isatty(self);
	COMPILER_BARRIER();
	ex->io_chng = self->if_base;
	ex->io_chsz = 0;

	/* Unlikely: But can happen due to recursive callbacks. */
	if unlikely(self->if_cnt)
		goto read_from_buffer;

	/* If we're a TTY buf, flush all other TTY buffers before reading. */
	if (self->if_flag & IO_LNBUF) {
		COMPILER_BARRIER();
		file_sync_lnfiles();
		COMPILER_BARRIER();
		if unlikely(self->if_cnt)
			goto read_from_buffer;
		ex->io_chng = self->if_base;
		ex->io_chsz = 0;
	}

	/* Determine where the next block of data is. */
	next_data = ex->io_fblk + (self->if_ptr - self->if_base);

	/* If no buf had been allocated, allocate one now. */
	if unlikely(!self->if_bufsiz) {
		/* Start out with the smallest size. */
		uint8_t *new_buffer;
		size_t new_bufsize;
		assert(self->if_ptr == self->if_base);
		next_data = ex->io_fpos;
		if unlikely(self->if_flag & IO_NODYNSCALE) {
			/* Dynamic scaling is disabled. Must forward the read() to the underlying file. */
read_through:
			self->if_ptr = self->if_base;
			if (next_data != ex->io_fpos) {
				/* Seek in the underlying file to get where we need to go. */
				off64_t new_pos;
				COMPILER_BARRIER();
				new_pos = file_system_seek(self, (off64_t)next_data, SEEK_SET);
				COMPILER_BARRIER();
				if unlikely(new_pos < 0)
					goto err;
				ex->io_fpos = next_data;
				goto again; /* Must start over because of recursive callbacks. */
			}
			COMPILER_BARRIER();
			read_size = file_system_read(self, buf, num_bytes);
			COMPILER_BARRIER();
			if unlikely(read_size < 0)
				goto err;
			ex->io_fpos = next_data + (size_t)read_size;
			result += (size_t)read_size;
			num_bytes -= (size_t)read_size;
			goto done;
		}
		if (num_bytes >= IOBUF_MAX)
			goto read_through;
		new_bufsize = num_bytes * 2;
		if (new_bufsize > IOBUF_MAX)
			new_bufsize = IOBUF_MAX;
		if (new_bufsize < IOBUF_MIN)
			new_bufsize = IOBUF_MIN;
		new_buffer = file_buffer_realloc_dynscale(self, &new_bufsize, next_data);
		if unlikely(!new_buffer) {
			new_bufsize = IOBUF_MIN;
			new_buffer  = file_buffer_realloc(self, new_bufsize);
			if unlikely(!new_buffer)
				goto read_through;
		}
		self->if_base   = new_buffer;
		self->if_bufsiz = new_bufsize;
		self->if_flag  |= IO_MALLBUF;
	} else if (num_bytes >= self->if_bufsiz) {
		size_t new_bufsize;
		uint8_t *new_buffer;

		/* The caller wants at least as much as this buf could even handle.
		 * Upscale  the  buf, or  use  load data  using  read-through mode. */
		if (self->if_flag & (IO_NODYNSCALE | IO_READING))
			goto read_through;
		if (num_bytes > IOBUF_MAX)
			goto read_through;

		/* Upscale the buf. */
		new_bufsize = num_bytes * 2;
		if (new_bufsize > IOBUF_MAX)
			new_bufsize = IOBUF_MAX;
		new_buffer = file_buffer_realloc_dynscale(self, &new_bufsize, next_data);

		/* If the allocation failed, also use read-through mode. */
		if unlikely(!new_buffer) {
			new_bufsize = num_bytes;
			new_buffer  = file_buffer_realloc(self, new_bufsize);
			if unlikely(!new_buffer)
				goto read_through;
		}
		self->if_base   = new_buffer;
		self->if_bufsiz = new_bufsize;
		self->if_flag  |= IO_MALLBUF;
	} else {
		size_t new_bufsize;

		/* Make  use  of   the  current  file-offset   to  dynamically  increase   the
		 * max  buffer  size,  such  that  we  try  to  keep  said  max  buffer   size
		 * capped around `ftell() / IOBUF_FACTOR' (though still cap it with its limit) */
		if (next_data >= (pos64_t)IOBUF_MAX * IOBUF_FACTOR) {
			new_bufsize = IOBUF_MAX;
		} else {
			new_bufsize = (size_t)(next_data / IOBUF_FACTOR);
		}
		if (new_bufsize > self->if_bufsiz) {
			/* Try to increase the buffer size. */
			uint8_t *new_buffer;
			new_buffer = file_buffer_realloc(self, new_bufsize);
			if likely(new_buffer) {
				self->if_base   = new_buffer;
				self->if_bufsiz = new_bufsize;
				self->if_flag  |= IO_MALLBUF;
			}
		}
	}

	self->if_ptr = self->if_base;
	ex->io_chng  = self->if_base;
	ex->io_fblk  = next_data;
	assert(self->if_cnt == 0);
	assert(ex->io_chsz == 0);
	assert(self->if_bufsiz != 0);
	if (next_data != ex->io_fpos) {
		/* Seek in the underlying file to get where we need to go. */
		off64_t new_pos;
		COMPILER_BARRIER();
		new_pos = file_system_seek(self, (off64_t)next_data, SEEK_SET);
		COMPILER_BARRIER();
		if unlikely(new_pos < 0)
			goto err;
		ex->io_fpos = next_data;
		goto again; /* Must start over because of recursive callbacks. */
	}

	/* Actually read the data. */
	old_flags = self->if_flag;
	self->if_flag |= IO_READING;
	COMPILER_BARRIER();
	read_size = file_system_read(self,
	                             self->if_base,
	                             self->if_bufsiz);
	COMPILER_BARRIER();
	self->if_flag &= ~IO_READING;
	self->if_flag |= old_flags & IO_READING;
	if unlikely(read_size < 0)
		goto err;
	if unlikely(read_size == 0)
		goto done;
	ex->io_fpos   = next_data + (size_t)read_size;
	self->if_ptr  = self->if_base;
	self->if_cnt  = (size_t)read_size;
	did_read_data = true;
	goto again;
done:
	if (num_bytes != 0)
		self->if_flag |= IO_EOF;
done_noeof:
	return result;
err:
	self->if_flag |= IO_ERR;
	return 0;
}



/* High-level, common write-to-file function. */
INTERN ATTR_SECTION(".text.crt.FILE.core.write") NONNULL((1)) size_t LIBCCALL
file_writedata(FILE *__restrict self, void const *buf, size_t num_bytes) {
	size_t result = 0;
	size_t new_bufsize;
	size_t bufavail;
	uint8_t *new_buffer;
	struct iofile_data *ex;
	assert(self);
	ex = self->if_exdata;
	assert(ex);

	/* Check to make sure that this file is writable. */
	if unlikely(!(self->if_flag & IO_RW)) {
		/* """
		 * EBADF  The file descriptor underlying stream is not a valid file
		 *        descriptor open for writing.
		 * """
		 *
		 * ... Technically, using EBADF here is kind-of debatable, since  the
		 * specs  seem to be  talking about the  underlying system FD, rather
		 * than permissions associated with the actual STDIO stream, but this
		 * still appears to be the error that's closest to this case. */
		(void)libc_seterrno(EBADF);
		goto err;
	}
	if (self->if_flag & IO_LNIFTYY)
		file_determine_isatty(self);

	/* Fill available buf. */
again:
	bufavail = (self->if_base + self->if_bufsiz) - self->if_ptr;
	if likely(bufavail) {
		if (bufavail > num_bytes)
			bufavail = num_bytes;
		if unlikely(!bufavail)
			goto done_noeof;
		memcpy(self->if_ptr, buf, bufavail);
		result += bufavail;

		/* Update the changed file-area. */
		if (!ex->io_chsz) {
			ex->io_chng = self->if_ptr;
			ex->io_chsz = bufavail;
		} else {
			if (ex->io_chng > self->if_ptr) {
				ex->io_chsz += (size_t)(ex->io_chng - self->if_ptr);
				ex->io_chng = self->if_ptr;
			}
			if (ex->io_chng + ex->io_chsz < self->if_ptr + bufavail)
				ex->io_chsz = (size_t)((self->if_ptr + bufavail) - ex->io_chng);
		}

		/* If this is a line-buffered file, add it to the chain of changed ones. */
		if (self->if_flag & IO_LNBUF)
			changed_linebuffered_insert(self);

		/* Update the file pointer. */
		self->if_ptr += bufavail;
		if (self->if_cnt >= bufavail) {
			self->if_cnt -= bufavail;
		} else {
			self->if_cnt = 0;
		}

		/* When  operating  in line-buffered  mode, check
		 * if there was a linefeed in what we just wrote. */
		if ((self->if_flag & IO_LNBUF) &&
		    (memchr(buf, '\n', num_bytes) ||
		     memchr(buf, '\r', num_bytes))) {
			/* Flush all line-buffered files. */
			file_sync_lnfiles();

			/* Flush this file. */
			COMPILER_BARRIER();
			if ((self->if_flag & IO_ERR) || file_sync(self))
				goto err0;
			COMPILER_BARRIER();
			num_bytes -= bufavail;
			if (!num_bytes)
				goto done;
			buf = (byte_t *)buf + bufavail;
			goto again;
		}

		num_bytes -= bufavail;
		if (!num_bytes)
			goto done;
		buf = (byte_t *)buf + bufavail;
	}

	/* No more buf available.
	 * Either we must flush the buf, or we must extend it. */
	if (self->if_bufsiz >= IOBUF_MAX ||
	    (self->if_flag & (IO_NODYNSCALE | IO_READING))) {
		/* Buffer is too  large or  cannot be  relocated.
		 * >> Therefor, we must flush it, then try again. */
		if (self->if_flag & IO_LNBUF)
			file_sync_lnfiles();
		COMPILER_BARRIER();
		if ((self->if_flag & IO_ERR) || file_sync(self))
			goto err0;
		COMPILER_BARRIER();
		ex->io_chng = self->if_base;
		ex->io_chsz = 0;

		/* Check for special case: If the buf is fixed to zero-length,
		 *                         we must act as a write-through buf. */
		if (!self->if_bufsiz) {
			ssize_t temp;
do_writethrough:
			COMPILER_BARRIER();
			temp = file_system_write(self, buf, num_bytes);
			COMPILER_BARRIER();
			if unlikely(temp < 0)
				goto err;
			result += (size_t)temp;
			num_bytes -= (size_t)temp;
			goto done;
		}

		/* If there  is  no  more  available  buf  to-be  read,
		 * reset the file pointer and change to the next chunk. */
		if (!self->if_cnt) {
			ex->io_fblk += (size_t)(self->if_ptr - self->if_base);
			self->if_ptr = self->if_base;
		}
		goto again;
	}

	/* Extend the buf */
	new_bufsize = (size_t)self->if_bufsiz * 2;
	if (new_bufsize < IOBUF_MIN)
		new_bufsize = IOBUF_MIN;
	if (new_bufsize > IOBUF_MAX)
		new_bufsize = IOBUF_MAX;
	new_buffer = file_buffer_realloc(self, new_bufsize);
	if unlikely(!new_buffer) {
		/* Buffer relocation failed. - sync() + operate in write-through mode as fallback. */
		if (self->if_flag & IO_LNBUF)
			file_sync_lnfiles();
		COMPILER_BARRIER();
		if ((self->if_flag & IO_ERR) || file_sync(self))
			goto err0;
		COMPILER_BARRIER();
		ex->io_chng = self->if_base;
		ex->io_chsz = 0;
		goto do_writethrough;
	}

	/* Install the new buf. */
	self->if_ptr    = new_buffer + (self->if_ptr - self->if_base);
	ex->io_chng     = new_buffer + (ex->io_chng - self->if_base);
	self->if_bufsiz = new_bufsize;
	self->if_base   = new_buffer;
	self->if_flag  |= IO_MALLBUF;

	/* Go back and use the new buf. */
	goto again;
done:
	if (num_bytes != 0)
		self->if_flag |= IO_EOF;
done_noeof:
	return result;
err:
	self->if_flag |= IO_ERR;
err0:
	return 0;
}

INTERN ATTR_SECTION(".text.crt.FILE.core.seek") NONNULL((1)) pos64_t LIBCCALL
file_seek(FILE *__restrict self, off64_t off, int whence) {
	pos64_t result;
	struct iofile_data *ex;
	assert(self);
	ex = self->if_exdata;
	assert(ex);
	if (whence == SEEK_SET || whence == SEEK_CUR) {
		pos64_t old_abspos;
		pos64_t new_abspos;
		uint8_t *new_pos;
		/* For these modes, we  can calculate the new  position,
		 * allowing for in-buffer seek, as well as delayed seek. */
		old_abspos = ex->io_fblk;
		old_abspos += (self->if_ptr - self->if_base);
		if (whence == SEEK_SET) {
			new_abspos = (pos64_t)off;
		} else {
			/* Special case: position-query */
			if (off == 0)
				return old_abspos;
			new_abspos = old_abspos + off;
		}
		self->if_flag &= ~IO_EOF;
		if unlikely(new_abspos >= INT64_MAX) {
			(void)libc_seterrno(EOVERFLOW);
			goto err;
		}
		if (new_abspos < old_abspos)
			goto full_seek;
#if __SIZEOF_POINTER__ < 8
		if ((new_abspos - old_abspos) >= SIZE_MAX)
			goto full_seek;
#endif /* __SIZEOF_POINTER__ < 8 */

		/* Seek-ahead-in-buffer. */
		new_pos = self->if_base + (size_t)(new_abspos - ex->io_fblk);
#if __SIZEOF_POINTER__ < 8
		if (new_pos < self->if_base)
			goto full_seek;
#endif /* __SIZEOF_POINTER__ < 8 */

		/* Truncate the read buffer */
		if (new_pos < self->if_ptr) {
			/* Seek  below the current pointer (but we don't
			 * remember how much was actually read there, so
			 * we simply truncate the buffer fully) */
			self->if_cnt = 0;
		} else {
			size_t skipsz = (size_t)(new_pos - self->if_ptr);
			if (self->if_cnt >= skipsz) {
				self->if_cnt -= skipsz;
			} else {
				self->if_cnt = 0;
			}
		}
		self->if_ptr = new_pos;
		return new_abspos;
	}
full_seek:
	if (self->if_flag & IO_LNIFTYY)
		file_determine_isatty(self);
	if (self->if_flag & IO_LNBUF)
		file_sync_lnfiles();

	/* Synchronize the buffer. */
	COMPILER_BARRIER();
	if ((self->if_flag & IO_ERR) || file_sync(self))
		goto err0;
	COMPILER_BARRIER();
	ex->io_chng = self->if_base;
	ex->io_chsz = 0;
	COMPILER_BARRIER();
	self->if_flag &= ~IO_EOF;

	/* Do a full seek using the underlying file. */
	result = (pos64_t)file_system_seek(self, off, whence);
	if unlikely((off64_t)result < 0)
		goto err;
	COMPILER_BARRIER();

	/* Clear the buffer and set the new file pointer. */
	ex->io_fblk  = result;
	ex->io_fpos  = result;
	self->if_cnt = 0;
	self->if_ptr = self->if_base;
	ex->io_chng  = self->if_base;
	ex->io_chsz  = 0;
	return result;
err:
	self->if_flag |= IO_ERR;
err0:
	return (pos64_t)-1;
}


INTERN WUNUSED ATTR_SECTION(".text.crt.FILE.core.read") NONNULL((1)) int LIBCCALL
file_getc(FILE *__restrict self) {
	uint8_t *new_buffer;
	size_t new_bufsize;
	ssize_t read_size;
	uint32_t old_flags;
	int result;
	pos64_t next_data;
	struct iofile_data *ex;
	assert(self);
again:
	if (self->if_cnt) {
read_from_buffer:
		/* Simple case: we can read from the active buffer. */
		result = (int)(unsigned int)(unsigned char)*self->if_ptr++;
		--self->if_cnt;
		goto done;
	}
	ex = self->if_exdata;
	assert(ex);

	/* The buffer is empty and must be re-filled. */
	/* First off: Flush any changes that had been made. */
	COMPILER_BARRIER();
	if unlikely(file_sync(self) != 0)
		goto err0;
	COMPILER_BARRIER();
	ex->io_chng = self->if_base;
	ex->io_chsz = 0;

	/* Unlikely: But can happen due to recursive callbacks. */
	if unlikely(self->if_cnt)
		goto read_from_buffer;

	/* If we're a TTY buffer, flush all other TTY buffers before reading. */
	if (self->if_flag & IO_LNIFTYY)
		file_determine_isatty(self);
	if (self->if_flag & IO_LNBUF) {
		COMPILER_BARRIER();
		file_sync_lnfiles();
		COMPILER_BARRIER();
		if unlikely(self->if_cnt)
			goto read_from_buffer;
		ex->io_chng = self->if_base;
		ex->io_chsz = 0;
	}

	/* Determine where the next block of data is. */
	next_data = ex->io_fblk + (self->if_ptr - self->if_base);

	/* If no buffer had been allocated, allocate one now. */
	if unlikely(!self->if_bufsiz) {
		if unlikely(self->if_flag & IO_NODYNSCALE) {
			byte_t buf[1];
			/* Dynamic scaling is disabled. Must forward the getc() to the underlying file. */
read_through:
			if (next_data != ex->io_fpos) {
				/* Seek in the underlying file to get where we need to go. */
				off64_t new_pos;
				COMPILER_BARRIER();
				new_pos = file_system_seek(self, (off64_t)next_data, SEEK_SET);
				COMPILER_BARRIER();
				if unlikely(new_pos < 0)
					goto err;
				ex->io_fpos = next_data;
				goto again; /* Must start over because of recursive callbacks. */
			}
			COMPILER_BARRIER();
			read_size = file_system_read(self, buf, 1);
			COMPILER_BARRIER();
			if unlikely(read_size < 0)
				goto err;
			if (!read_size) {
				self->if_flag |= IO_EOF;
				result = EOF;
			} else {
				result = (int)(unsigned int)(unsigned char)buf[0];
				/* Set the file and block address. */
				ex->io_fpos = next_data + 1;
				ex->io_fblk = next_data + 1;
			}
			goto done;
		}

		/* Start out with the smallest size. */
		new_bufsize = IOBUF_MIN;
		new_buffer  = file_buffer_realloc_dynscale(self, &new_bufsize, next_data);
		if unlikely(!new_buffer) {
			new_bufsize = IOBUF_MIN;
			new_buffer  = file_buffer_realloc(self, new_bufsize);
			if unlikely(!new_buffer)
				goto read_through;
		}
		self->if_base   = new_buffer;
		self->if_bufsiz = new_bufsize;
	} else {
		if (!(self->if_flag & (IO_NODYNSCALE | IO_READING))) {
			/* Upscale the buffer. */
			if (next_data >= (pos64_t)IOBUF_MAX * IOBUF_FACTOR) {
				new_bufsize = IOBUF_MAX;
			} else {
				new_bufsize = (size_t)(next_data / IOBUF_FACTOR);
				if (new_bufsize < IOBUF_MIN)
					new_bufsize = IOBUF_MIN;
			}
			if (new_bufsize > self->if_bufsiz) {
				new_buffer = file_buffer_realloc(self, new_bufsize);
				if likely(new_buffer) {
					self->if_base   = new_buffer;
					self->if_bufsiz = new_bufsize;
					self->if_flag  |= IO_MALLBUF;
				}
			}
		}
	}

	self->if_ptr = self->if_base;
	ex->io_chng  = self->if_base;
	ex->io_fblk  = next_data;
	assert(self->if_cnt == 0);
	assert(ex->io_chsz == 0);
	assert(self->if_bufsiz != 0);
	if (next_data != ex->io_fpos) {
		/* Seek in the underlying file to get where we need to go. */
		off64_t new_pos;
		COMPILER_BARRIER();
		new_pos = file_system_seek(self, (off64_t)next_data, SEEK_SET);
		COMPILER_BARRIER();
		if unlikely(new_pos < 0)
			goto err;
		ex->io_fpos = next_data;
		goto again; /* Must start over because of recursive callbacks. */
	}

	/* Actually read the data. */
	new_buffer = self->if_base;
	old_flags  = self->if_flag;
	self->if_flag |= IO_READING;
	COMPILER_BARRIER();
	read_size = file_system_read(self,
	                             self->if_base,
	                             self->if_bufsiz);
	COMPILER_BARRIER();
	self->if_flag &= ~IO_READING;
	self->if_flag |= old_flags & IO_READING;
	if unlikely(read_size < 0)
		goto err;
	if unlikely(self->if_cnt)
		goto read_from_buffer;
	if unlikely(ex->io_chsz)
		goto again;
	ex->io_fpos = next_data + (size_t)read_size;

	/* Check for special case: EOF reached. */
	if (!read_size) {
		result = EOF;
		self->if_flag |= IO_EOF;
	} else {
		self->if_cnt = read_size - 1;
		self->if_ptr = self->if_base + 1;
		result = (int)(unsigned int)(unsigned char)*self->if_base;
	}
done:
	return result;
err:
	self->if_flag |= IO_ERR;
err0:
	result = EOF;
	goto done;
}

INTERN WUNUSED ATTR_SECTION(".text.crt.FILE.core.read") NONNULL((1)) int LIBCCALL
file_ungetc(FILE *__restrict self, unsigned char ch) {
	uint8_t *new_buffer;
	size_t new_bufsize, inc_size;
	struct iofile_data *ex;
	assert(self);

	/* Simple case: unget() the character. */
	if (self->if_ptr > self->if_base)
		goto unget_in_buffer;

	/* The buffer is already full. - Try to resize it, then insert at the front. */
	if (self->if_flag & IO_READING)
		goto eof;
	if (self->if_flag & IO_NODYNSCALE) {
		/* Check for special  case: Even when  dynscale is  disabled,
		 * still allow for an unget buffer of at least a single byte. */
		if (self->if_bufsiz != 0)
			goto eof;
	}
	ex = self->if_exdata;
	assert(ex);

	/* If the current block cannot be further extended, that's an EOF. */
	if (!ex->io_fblk)
		goto eof;
	inc_size = self->if_bufsiz;

	/* Determine the minimum buffer size. */
	if unlikely(!inc_size)
		inc_size = (self->if_flag & IO_NODYNSCALE) ? 1 : IOBUF_MIN;
	if ((pos64_t)inc_size > ex->io_fblk)
		inc_size = (size_t)ex->io_fblk;
	new_bufsize = self->if_bufsiz + inc_size;
	new_buffer  = file_buffer_realloc(self, new_bufsize);
	if unlikely(!new_buffer) {
		inc_size    = 1;
		new_bufsize = (size_t)self->if_bufsiz + 1;
		new_buffer  = file_buffer_realloc(self, new_bufsize);
		if unlikely(!new_buffer)
			goto err;
	}
	assert(new_bufsize > self->if_bufsiz);

	/* Install the new buffer. */
	self->if_ptr = new_buffer + (self->if_ptr - self->if_base) + inc_size;
	if (ex->io_chsz)
		ex->io_chng = new_buffer + (ex->io_chng - self->if_base) + inc_size;
	ex->io_fblk -= inc_size;
	self->if_base   = new_buffer;
	self->if_bufsiz = new_bufsize;
	self->if_flag  |= IO_MALLBUF;
	assert(self->if_ptr > self->if_base);

	/* Finally, insert the character into the buffer. */
unget_in_buffer:
	self->if_flag &= ~IO_EOF;
	*--self->if_ptr = (uint8_t)(unsigned char)(unsigned int)ch;
	++self->if_cnt;
	return (int)(unsigned int)ch;
eof:
	self->if_flag |= IO_EOF;
	return EOF;
err:
	self->if_flag |= IO_ERR;
	return EOF;
}

INTERN WUNUSED ATTR_SECTION(".text.crt.FILE.core.read") NONNULL((1)) int LIBCCALL
file_sungetc(FILE *__restrict self) {
	int result;
	if (self->if_ptr > self->if_base) {
		self->if_flag &= ~IO_EOF;
		result = *--self->if_ptr;
		++self->if_cnt;
	} else {
		result = EOF;
	}
	return result;
}

INTERN WUNUSED ATTR_SECTION(".text.crt.FILE.core.write") NONNULL((1)) int LIBCCALL
file_truncate(FILE *__restrict self, pos64_t new_size) {
	pos64_t abs_pos, abs_end;
	struct iofile_data *ex;
	assert(self);

	/* Synchronize the buffer. */
	if unlikely(file_sync(self))
		goto err0;
	ex = self->if_exdata;
	assert(ex);
	ex->io_chng = self->if_base;
	ex->io_chsz = 0;
	abs_pos     = ex->io_fblk + (self->if_ptr - self->if_base);
	abs_end     = abs_pos + self->if_cnt;
	if (new_size < abs_pos) {
		/* Truncate to get rid of the current buffer. */
		self->if_cnt = 0;
	} else if (new_size < abs_end) {
		/* Truncate the current buffer. */
		self->if_cnt = (size_t)(new_size - abs_pos);
	}

	/* With  data flushed and the loaded buffer
	 * truncated, truncate the underlying file. */
	COMPILER_BARRIER();
	if unlikely(file_system_trunc(self, new_size))
		goto err;
	COMPILER_BARRIER();
	return 0;
err:
	self->if_flag |= IO_ERR;
err0:
	return -1;
}


struct open_option {
	char     name[11]; /* Name. */
#define OPEN_EXFLAG_FNORMAL 0x00
#define OPEN_EXFLAG_FTEXT   0x01 /* Wrap the file in a text-file wrapper that
	                              * automatically converts its encoding to UTF-8. */
#define OPEN_EXFLAG_FNOBUF  0x02 /* Open the file without wrapping it inside a buffer. */
	uint8_t  exflg;   /* Extended flags (Set of `OPEN_EXFLAG_F*'). */
	oflag_t  mask;    /* Mask of flags which, when already set, causes the format to become invalid. */
	oflag_t  flag;    /* Flags. (or-ed with the flags after `mask' is checked) */
};

#ifndef O_XREAD
#define O_XREAD 0
#endif /* !O_XREAD */

#ifndef O_XWRITE
#define O_XWRITE 0
#endif /* !O_XWRITE */

#ifndef O_HIDDEN
#define O_HIDDEN 0
#endif /* !O_HIDDEN */

/* Open options are parsed from a comma-separated
 * string passed as second argument to fopen:
 * >> fopen("foo.txt", "w+");                    // STD-C mode name.
 * >> fopen("foo.txt", "text,RW,T,C");           // Extended form.
 * >> fopen("foo.txt", "text,rdwr,trunc,creat"); // Long form. */
#define BASEMODE_MASK (O_ACCMODE | O_CREAT | O_EXCL | O_TRUNC | O_APPEND)
PRIVATE ATTR_SECTION(".rodata.crt.FILE.core.utility")
struct open_option const open_options[] = {
	/* Short flag names. */
	{ "R", OPEN_EXFLAG_FNORMAL, O_ACCMODE, O_RDONLY },
	{ "W", OPEN_EXFLAG_FNORMAL, O_ACCMODE, O_WRONLY },
	{ "RW", OPEN_EXFLAG_FNORMAL, O_ACCMODE, O_RDWR },
	{ "C", OPEN_EXFLAG_FNORMAL, O_CREAT, O_CREAT },
	{ "X", OPEN_EXFLAG_FNORMAL, O_EXCL, O_EXCL },
	{ "T", OPEN_EXFLAG_FNORMAL, O_TRUNC, O_TRUNC },
	{ "A", OPEN_EXFLAG_FNORMAL, O_APPEND, O_APPEND },
	{ "NB", OPEN_EXFLAG_FNORMAL, O_NONBLOCK, O_NONBLOCK },
	{ "S", OPEN_EXFLAG_FNORMAL, O_SYNC, O_SYNC },
	{ "D", OPEN_EXFLAG_FNOBUF, O_DIRECT, O_DIRECT },
	{ "NF", OPEN_EXFLAG_FNORMAL, O_NOFOLLOW, O_NOFOLLOW },
	{ "NA", OPEN_EXFLAG_FNORMAL, O_NOATIME, O_NOATIME },
	{ "CE", OPEN_EXFLAG_FNORMAL, O_CLOEXEC, O_CLOEXEC },
	{ "XR", OPEN_EXFLAG_FNORMAL, O_XREAD, O_XREAD },
	{ "XW", OPEN_EXFLAG_FNORMAL, O_XWRITE, O_XWRITE },
	{ "H", OPEN_EXFLAG_FNORMAL, O_HIDDEN, O_HIDDEN },
	/* Flags by name. */
	{ "rdonly", OPEN_EXFLAG_FNORMAL, O_ACCMODE, O_RDONLY },
	{ "wronly", OPEN_EXFLAG_FNORMAL, O_ACCMODE, O_WRONLY },
	{ "rdwr", OPEN_EXFLAG_FNORMAL, O_ACCMODE, O_RDWR },
	{ "creat", OPEN_EXFLAG_FNORMAL, O_CREAT, O_CREAT },
	{ "excl", OPEN_EXFLAG_FNORMAL, O_EXCL, O_EXCL },
	{ "trunc", OPEN_EXFLAG_FNORMAL, O_TRUNC, O_TRUNC },
	{ "append", OPEN_EXFLAG_FNORMAL, O_APPEND, O_APPEND },
	{ "nonblock", OPEN_EXFLAG_FNORMAL, O_NONBLOCK, O_NONBLOCK },
	{ "sync", OPEN_EXFLAG_FNORMAL, O_SYNC, O_SYNC },
	{ "direct", OPEN_EXFLAG_FNOBUF, O_DIRECT, O_DIRECT },
	{ "nofollow", OPEN_EXFLAG_FNORMAL, O_NOFOLLOW, O_NOFOLLOW },
	{ "noatime", OPEN_EXFLAG_FNORMAL, O_NOATIME, O_NOATIME },
	{ "cloexec", OPEN_EXFLAG_FNORMAL, O_CLOEXEC, O_CLOEXEC },
	{ "clofork", OPEN_EXFLAG_FNORMAL, O_CLOFORK, O_CLOFORK },
	{ "dospath", OPEN_EXFLAG_FNORMAL, O_DOSPATH, O_DOSPATH },
	{ "tmpfile", OPEN_EXFLAG_FNORMAL, O_TMPFILE, O_TMPFILE },
	{ "xread", OPEN_EXFLAG_FNORMAL, O_XREAD, O_XREAD },
	{ "xwrite", OPEN_EXFLAG_FNORMAL, O_XWRITE, O_XWRITE },
	{ "hidden", OPEN_EXFLAG_FNORMAL, O_HIDDEN, O_HIDDEN },
	{ "dsync", OPEN_EXFLAG_FNORMAL, O_DSYNC, O_DSYNC },
	{ "async", OPEN_EXFLAG_FNORMAL, O_ASYNC, O_ASYNC },
	{ "rsync", OPEN_EXFLAG_FNORMAL, O_RSYNC, O_RSYNC },
	{ "noctty", OPEN_EXFLAG_FNORMAL, O_NOCTTY, O_NOCTTY },
	{ "largefile", OPEN_EXFLAG_FNORMAL, O_LARGEFILE, O_LARGEFILE },
	{ "directory", OPEN_EXFLAG_FNORMAL, O_DIRECTORY, O_DIRECTORY },
	{ "path", OPEN_EXFLAG_FNORMAL, O_PATH, O_PATH },
	/* Extended flag names. */
	{ "binary", OPEN_EXFLAG_FNORMAL, 0, 0 },
	{ "text", OPEN_EXFLAG_FTEXT, 0, 0 },
	{ "nobuf", OPEN_EXFLAG_FNOBUF, 0, 0 },
};


/* @param: poflags: When non-NULL, filled with `O_*'
 * @return: * :     Set of `IO_LNIFTYY | IO_RW | IO_NODYNSCALE' */
INTERN WUNUSED ATTR_SECTION(".text.crt.FILE.core.utility") uint32_t LIBCCALL
file_evalmodes(char const *modes, oflag_t *poflags) {
	/* IO_LNIFTYY: Check if the stream handle is a tty
	 *             the  first  time it  is  read from. */
	uint32_t result = IO_LNIFTYY;
	oflag_t oflags = O_RDONLY;
	if (modes) {
		unsigned int flags = 0;
		for (;;) {
			int open_binary_mode;
			unsigned int i;
			size_t optlen;
			char const *next;
			next   = strchrnul(modes, ',');
			optlen = (size_t)(next - modes);
			if (optlen < lengthof(open_options[0].name)) {
				for (i = 0; i < lengthof(open_options); ++i) {
					if (open_options[i].name[optlen])
						continue;
					if (bcmp(open_options[i].name, modes, optlen, sizeof(char)) != 0)
						continue;
					if ((oflags & open_options[i].mask) != 0)
						goto err_invalid_oflags; /* XXX: Illegal file option */
					/* Apply new flags. */
					flags |= open_options[i].exflg;
					oflags |= open_options[i].flag;
					goto found_option;
				}
			}

			/* Check for an STD-C conforming open mode. */
			if (!optlen)
				goto err_invalid_oflags;
			if (oflags & BASEMODE_MASK)
				goto err_invalid_oflags;
			/* -1: Binary file
			 *  0: Indeterminate
			 * +1: Text file */
			open_binary_mode = 0;
			if (*modes == 'r') {
				oflags |= O_RDONLY;
			} else if (*modes == 'w') {
				oflags |= O_WRONLY | O_TRUNC | O_CREAT;
			} else if (*modes == 'a') {
				oflags |= O_WRONLY | O_APPEND | O_CREAT;
			} else {
				goto err_invalid_oflags;
			}
			++modes;
			while (modes < next) {
				char ch = *modes;
				if (ch == '+' && (oflags & O_ACCMODE) != O_RDWR) {
					/* Open with read+write access */
					oflags &= ~O_ACCMODE;
					oflags |= O_RDWR;
				} else if (ch == 'b' && open_binary_mode == 0) {
					/* Open as a binary file */
					open_binary_mode = -1;
				} else if (*modes == 't' && open_binary_mode == 0) {
					/* Open as a text file */
					open_binary_mode = 1;
				} else if (*modes == 'x' && (oflags & (O_TRUNC | O_CREAT)) == (O_TRUNC | O_CREAT)) {
					/* Don't open an existing file */
					oflags |= O_EXCL;
				} else if (*modes == 'e' && !(oflags & O_CLOEXEC)) {
					/* Set the close-on-exec flag */
					oflags |= O_CLOEXEC;
				} else {
					/* XXX: Unrecognized mode character? */
				}
				++modes;
			}
			if (open_binary_mode > 0)
				flags |= OPEN_EXFLAG_FTEXT;
err_invalid_oflags:
found_option:
			if (!*next)
				break;
			modes = next + 1;
		}
		if ((oflags & O_ACCMODE) != O_RDONLY)
			result |= IO_RW; /* Writable! */
		if (flags & OPEN_EXFLAG_FTEXT) {
			/* Open a text-file? */
		}
		if (flags & OPEN_EXFLAG_FNOBUF) {
			/* Disable buffering. */
			result |= IO_NODYNSCALE;
			result &= ~IO_LNIFTYY;
		}
	}
	if (poflags)
		*poflags = oflags;
	return result;
}


/* @param: flags: Set of `IO_*' */
INTERN WUNUSED ATTR_SECTION(".text.crt.FILE.core.utility") FILE *LIBCCALL
file_openfd(/*inherit(on_success)*/ fd_t fd, uint32_t flags) {
	FILE *result;
	struct iofile_data *ex;
	result = file_calloc(sizeof(struct iofile_data_novtab));
	if unlikely(!result)
		goto done;
	ex = (struct iofile_data *)(result + 1);
	result->if_exdata = ex;
	result->if_fd     = fd; /* Inherit reference */
	assert(ex->io_getln == NULL);
	shared_recursive_rwlock_cinit(&ex->io_lock);
	assert(ex->io_zero == 0);
	ex->io_refcnt   = 1;
	result->if_flag = flags;

	/* Insert the new file stream into the global list of them. */
	allfiles_insert(result);
done:
	return result;
}


INTERN WUNUSED NONNULL((1)) ATTR_SECTION(".text.crt.FILE.core.utility") FILE *LIBCCALL
file_reopenfd(FILE *__restrict self, fd_t fd, uint32_t flags) {
	struct iofile_data *ex;
	if unlikely(self->if_flag & IO_READING) {
		/* reopen() isn't allowed from within a cookie function. */
		(void)libc_seterrno(EPERM);
		return NULL;
	}
	if (file_sync(self))
		return NULL;
	if (LIST_ISBOUND(self, if_exdata->io_lnch))
		changed_linebuffered_remove(self);
	file_system_close(self);
	self->if_flag = flags;
	self->if_fd   = fd;
	self->if_ptr  = self->if_base;
	self->if_cnt  = 0;
	ex = self->if_exdata;
	assert(ex);
	ex->io_chng = self->if_base;
	ex->io_chsz = 0;
	ex->io_fblk = 0;
	ex->io_fpos = 0;
	mbstate_init(&ex->io_mbs);
	return self;
}










PRIVATE NONNULL((1)) ATTR_SECTION(".text.crt.application.exit") void LIBCCALL
file_sync_std_stream(FILE *__restrict stream) {
	if unlikely(!stream)
		return;
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		file_sync(stream);
		file_lock_endwrite(stream);
	} else {
		file_sync(stream);
	}
}


/*[[[head:libc__flushall,hash:CRC-32=0x6230416a]]]*/
INTERN ATTR_SECTION(".text.crt.application.exit") int
(LIBCCALL libc__flushall)(void) THROWS(...)
/*[[[body:libc__flushall]]]*/
{
	/* All all streams opened by the user. */
	file_syncall_locked();

	/* Flush active std-streams. */
	file_sync_std_stream(stdin);
	file_sync_std_stream(stdout);
	file_sync_std_stream(stderr);
	return 0;
}
/*[[[end:libc__flushall]]]*/

/*[[[head:libc_flushall_unlocked,hash:CRC-32=0x775d1c6e]]]*/
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.utility") int
(LIBCCALL libc_flushall_unlocked)(void) THROWS(...)
/*[[[body:libc_flushall_unlocked]]]*/
{
	/* All all streams opened by the user. */
	file_syncall_unlocked();

	/* Flush the active STD streams. */
	file_sync(file_fromuser(stdin));
	file_sync(file_fromuser(stdout));
	file_sync(file_fromuser(stderr));
	return 0;
}
/*[[[end:libc_flushall_unlocked]]]*/

/*[[[head:libd_rename,hash:CRC-32=0x39cda09f]]]*/
/* >> rename(2)
 * Rename  a given file `oldname' to `newname_or_path', or in the event
 * that `newname_or_path' refers to a directory, place the file within. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(1) ATTR_IN(2) int
NOTHROW_RPC(LIBDCALL libd_rename)(char const *oldname,
                                  char const *newname_or_path)
/*[[[body:libd_rename]]]*/
{
	return libd_renameat(AT_FDCWD, oldname, AT_FDCWD, newname_or_path);
}
/*[[[end:libd_rename]]]*/

/*[[[head:libc_rename,hash:CRC-32=0xd2ab8df7]]]*/
/* >> rename(2)
 * Rename  a given file `oldname' to `newname_or_path', or in the event
 * that `newname_or_path' refers to a directory, place the file within. */
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(1) ATTR_IN(2) int
NOTHROW_RPC(LIBCCALL libc_rename)(char const *oldname,
                                  char const *newname_or_path)
/*[[[body:libc_rename]]]*/
{
	errno_t result;
	result = sys_rename(oldname, newname_or_path);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_rename]]]*/

/*[[[head:libd_renameat,hash:CRC-32=0x6dd4a4d5]]]*/
/* >> renameat(2) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(2) ATTR_IN(4) int
NOTHROW_RPC(LIBDCALL libd_renameat)(fd_t oldfd,
                                    char const *oldname,
                                    fd_t newfd,
                                    char const *newname_or_path)
/*[[[body:libd_renameat]]]*/
{
	return libd_renameat2(oldfd, oldname, newfd, newname_or_path, 0);
}
/*[[[end:libd_renameat]]]*/

/*[[[head:libc_renameat,hash:CRC-32=0xcc508bbe]]]*/
/* >> renameat(2) */
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(2) ATTR_IN(4) int
NOTHROW_RPC(LIBCCALL libc_renameat)(fd_t oldfd,
                                    char const *oldname,
                                    fd_t newfd,
                                    char const *newname_or_path)
/*[[[body:libc_renameat]]]*/
{
	errno_t result;
	result = sys_renameat(oldfd, oldname, newfd, newname_or_path);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_renameat]]]*/

/*[[[head:libd_renameat2,hash:CRC-32=0xa7977515]]]*/
/* >> renameat2(2)
 * @param flags: Set of `0 | AT_RENAME_NOREPLACE | AT_RENAME_EXCHANGE |
 *                       AT_RENAME_WHITEOUT | AT_RENAME_MOVETODIR | AT_DOSPATH'
 * NOTE: For portability, use the following names:
 *   - `AT_RENAME_NOREPLACE' --> `RENAME_NOREPLACE'
 *   - `AT_RENAME_EXCHANGE'  --> `RENAME_EXCHANGE'
 *   - `AT_RENAME_WHITEOUT'  --> `RENAME_WHITEOUT' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(2) ATTR_IN(4) int
NOTHROW_RPC(LIBDCALL libd_renameat2)(fd_t oldfd,
                                     char const *oldname,
                                     fd_t newfd,
                                     char const *newname_or_path,
                                     atflag_t flags)
/*[[[body:libd_renameat2]]]*/
{
	return libc_renameat2(oldfd, oldname, newfd, newname_or_path, flags | libd_AT_DOSPATH);
}
/*[[[end:libd_renameat2]]]*/

/*[[[head:libc_renameat2,hash:CRC-32=0x8a43fd18]]]*/
/* >> renameat2(2)
 * @param flags: Set of `0 | AT_RENAME_NOREPLACE | AT_RENAME_EXCHANGE |
 *                       AT_RENAME_WHITEOUT | AT_RENAME_MOVETODIR | AT_DOSPATH'
 * NOTE: For portability, use the following names:
 *   - `AT_RENAME_NOREPLACE' --> `RENAME_NOREPLACE'
 *   - `AT_RENAME_EXCHANGE'  --> `RENAME_EXCHANGE'
 *   - `AT_RENAME_WHITEOUT'  --> `RENAME_WHITEOUT' */
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(2) ATTR_IN(4) int
NOTHROW_RPC(LIBCCALL libc_renameat2)(fd_t oldfd,
                                     char const *oldname,
                                     fd_t newfd,
                                     char const *newname_or_path,
                                     atflag_t flags)
/*[[[body:libc_renameat2]]]*/
{
	errno_t result;
	result = sys_renameat2(oldfd, oldname, newfd, newname_or_path, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_renameat2]]]*/

/*[[[head:libc_ftrylockfile,hash:CRC-32=0xb1aa19d]]]*/
/* >> ftrylockfile(3)
 * Try to acquire a lock to `stream'
 * @return: == 0 : Lock successfully acquired
 * @return: != 0 : Failed to acquire lock */
INTERN ATTR_SECTION(".text.crt.FILE.locked.utility") WUNUSED ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_ftrylockfile)(FILE *__restrict stream)
/*[[[body:libc_ftrylockfile]]]*/
{
	if unlikely(!stream)
		return -1;
	stream = file_fromuser(stream);
	return file_lock_trywrite(stream) ? 0 : 1;
}
/*[[[end:libc_ftrylockfile]]]*/

/*[[[head:libc_flockfile,hash:CRC-32=0xe01fa69b]]]*/
/* >> flockfile(3)
 * Acquire a lock to `stream' and block until doing so succeeds */
INTERN ATTR_SECTION(".text.crt.FILE.locked.utility") ATTR_INOUT(1) void
NOTHROW_RPC(LIBCCALL libc_flockfile)(FILE *__restrict stream)
/*[[[body:libc_flockfile]]]*/
{
	if likely(stream) {
		stream = file_fromuser(stream);
		/* Must always lock the file here, irregardless of `FMUSTLOCK()'.
		 * This behavior is implemented by the documentation (and naming)
		 * of `__fsetlocking(3)' and `FSETLOCKING_BYCALLER'. */
		file_lock_write(stream);
	}
}
/*[[[end:libc_flockfile]]]*/

/*[[[head:libc_funlockfile,hash:CRC-32=0xb5574c14]]]*/
/* >> funlockfile(3)
 * Release a previously acquired lock from `stream' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.utility") void
NOTHROW_NCX(LIBCCALL libc_funlockfile)(FILE *__restrict stream)
/*[[[body:libc_funlockfile]]]*/
{
	if likely(stream) {
		stream = file_fromuser(stream);
		/* Must always unlock the file here, irregardless of `FMUSTLOCK()'.
		 * This behavior is implemented  by the documentation (and  naming)
		 * of `__fsetlocking(3)' and `FSETLOCKING_BYCALLER'. */
		file_lock_endwrite(stream);
	}
}
/*[[[end:libc_funlockfile]]]*/

/*[[[head:libc_fflush,hash:CRC-32=0x5aeba993]]]*/
/* >> fflush(3)
 * Flush any unwritten data from `stream' to the underlying filesystem/TTY */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.utility") int
(LIBCCALL libc_fflush)(FILE *stream) THROWS(...)
/*[[[body:libc_fflush]]]*/
{
	int result;
	if (!stream)
		return flushall();
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		result = file_sync(stream);
		file_lock_endwrite(stream);
	} else {
		result = file_sync(stream);
	}
	return result;
}
/*[[[end:libc_fflush]]]*/

/*[[[head:libc_fflush_unlocked,hash:CRC-32=0xdc145d17]]]*/
/* >> fflush_unlocked(3)
 * Same as `fflush()', but performs I/O without acquiring a lock to `stream' */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.utility") int
(LIBCCALL libc_fflush_unlocked)(FILE *stream) THROWS(...)
/*[[[body:libc_fflush_unlocked]]]*/
{
	int result;
	if (!stream)
		return flushall_unlocked();
	stream = file_fromuser(stream);
	result = file_sync(stream);
	return result;
}
/*[[[end:libc_fflush_unlocked]]]*/



/*[[[head:libc_fread,hash:CRC-32=0x7cbaba70]]]*/
/* >> fread(3)
 * Read up to `elemsize * elemcount' bytes of data from `stream' into `buf' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.read") WUNUSED ATTR_INOUT(4) ATTR_OUT_OPT(1) size_t
(LIBCCALL libc_fread)(void *__restrict buf,
                      size_t elemsize,
                      size_t elemcount,
                      FILE *__restrict stream) THROWS(...)
/*[[[body:libc_fread]]]*/
{
	size_t result, total;
	if unlikely(!stream) {
		(void)libc_seterrno(EINVAL);
		return 0;
	}
	if unlikely(!elemsize)
		return 0;
	stream = file_fromuser(stream);
	if unlikely(OVERFLOW_UMUL(elemcount, elemsize, &total)) {
		(void)libc_seterrno(EOVERFLOW);
		FSETERROR(stream);
		return 0;
	}
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		result = file_readdata(stream, buf, total);
		/* Unread the last partially read element. */
		if unlikely(result != total)
			file_seek(stream, -(result % elemsize), SEEK_CUR);
		file_lock_endwrite(stream);
	} else {
		result = file_readdata(stream, buf, total);
		/* Unread the last partially read element. */
		if unlikely(result != total)
			file_seek(stream, -(result % elemsize), SEEK_CUR);
	}
	return result / elemsize;
}
/*[[[end:libc_fread]]]*/

/*[[[head:libc_fread_unlocked,hash:CRC-32=0x21301529]]]*/
/* >> fread_unlocked(3)
 * Same as `fread()', but performs I/O without acquiring a lock to `stream' */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.read") WUNUSED ATTR_INOUT(4) ATTR_OUT_OPT(1) size_t
(LIBCCALL libc_fread_unlocked)(void *__restrict buf,
                               size_t elemsize,
                               size_t elemcount,
                               FILE *__restrict stream) THROWS(...)
/*[[[body:libc_fread_unlocked]]]*/
{
	size_t result, total;
	if unlikely(!stream) {
		(void)libc_seterrno(EINVAL);
		return 0;
	}
	if unlikely(!elemsize)
		return 0;
	stream = file_fromuser(stream);
	if unlikely(OVERFLOW_UMUL(elemcount, elemsize, &total)) {
		(void)libc_seterrno(EOVERFLOW);
		FSETERROR(stream);
		return 0;
	}
	result = file_readdata(stream, buf, total);
	/* Unread the last partially read element. */
	if unlikely(result != total)
		file_seek(stream, -(result % elemsize), SEEK_CUR);
	return result / elemsize;
}
/*[[[end:libc_fread_unlocked]]]*/

/*[[[head:libc_fwrite,hash:CRC-32=0xaadcf331]]]*/
/* >> fwrite(3)
 * Write up to `elemsize * elemcount' bytes of data from `buf' into `stream' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.write") ATTR_INOUT(4) ATTR_IN_OPT(1) size_t
(LIBCCALL libc_fwrite)(void const *__restrict buf,
                       size_t elemsize,
                       size_t elemcount,
                       FILE *__restrict stream) THROWS(...)
/*[[[body:libc_fwrite]]]*/
{
	size_t result, total;
	if unlikely(!stream) {
		(void)libc_seterrno(EINVAL);
		return 0;
	}
	if unlikely(!elemsize)
		return 0;
	stream = file_fromuser(stream);
	if unlikely(OVERFLOW_UMUL(elemcount, elemsize, &total)) {
		(void)libc_seterrno(EOVERFLOW);
		FSETERROR(stream);
		return 0;
	}
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		result = file_writedata(stream, buf, total);
		file_lock_endwrite(stream);
	} else {
		result = file_writedata(stream, buf, total);
	}
	return result / elemsize;
}
/*[[[end:libc_fwrite]]]*/

/*[[[head:libc_fwrite_unlocked,hash:CRC-32=0x6dc3ca4c]]]*/
/* >> fwrite_unlocked(3)
 * Same as `fwrite()', but performs I/O without acquiring a lock to `stream' */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.write") ATTR_INOUT(4) ATTR_IN_OPT(1) size_t
(LIBCCALL libc_fwrite_unlocked)(void const *__restrict buf,
                                size_t elemsize,
                                size_t elemcount,
                                FILE *__restrict stream) THROWS(...)
/*[[[body:libc_fwrite_unlocked]]]*/
{
	size_t result, total;
	if unlikely(!stream) {
		(void)libc_seterrno(EINVAL);
		return 0;
	}
	if unlikely(!elemsize)
		return 0;
	stream = file_fromuser(stream);
	if unlikely(OVERFLOW_UMUL(elemcount, elemsize, &total)) {
		(void)libc_seterrno(EOVERFLOW);
		FSETERROR(stream);
		return 0;
	}
	result = file_writedata(stream, buf, total);
	return result / elemsize;
}
/*[[[end:libc_fwrite_unlocked]]]*/

/*[[[head:libc_file_printer,hash:CRC-32=0xe9f604b]]]*/
/* >> file_printer(3)
 * For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.write") ATTR_INS(2, 3) NONNULL((1)) ssize_t
(__FORMATPRINTER_CC libc_file_printer)(void *arg,
                                       char const *__restrict data,
                                       size_t datalen) THROWS(...)
/*[[[body:libc_file_printer]]]*/
{
	FILE *me = file_fromuser((FILE *)arg);
	ssize_t result;
	if (FMUSTLOCK(me)) {
		file_lock_write(me);
		result = (ssize_t)file_writedata(me, data, datalen * sizeof(char));
		if unlikely(!result && FERROR(me))
			result = -1;
		file_lock_endwrite(me);
	} else {
		result = (ssize_t)file_writedata(me, data, datalen * sizeof(char));
		if unlikely(!result && FERROR(me))
			result = -1;
	}
	return result;
}
/*[[[end:libc_file_printer]]]*/

/*[[[head:libc_file_printer_unlocked,hash:CRC-32=0x9b1abb91]]]*/
/* >> file_printer_unlocked(3)
 * Same as `file_printer()', but performs I/O without acquiring a lock to `(FILE *)arg' */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.write") ATTR_INS(2, 3) NONNULL((1)) ssize_t
(__FORMATPRINTER_CC libc_file_printer_unlocked)(void *arg,
                                                char const *__restrict data,
                                                size_t datalen) THROWS(...)
/*[[[body:libc_file_printer_unlocked]]]*/
{
	FILE *me = file_fromuser((FILE *)arg);
	ssize_t result;
	result = (ssize_t)file_writedata(me, data, datalen * sizeof(char));
	if unlikely(!result && FERROR(me))
		result = -1;
	return result;
}
/*[[[end:libc_file_printer_unlocked]]]*/








/************************************************************************/
/* ftell[_unlocked](3), ftello[_unlocked](3), ftello64[_unlocked](3)    */
/************************************************************************/

/*[[[head:libc_ftell,hash:CRC-32=0xd8ffd5ee]]]*/
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offset from the start of the file */
INTERN ATTR_SECTION(".text.crt.FILE.locked.seek.seek") WUNUSED ATTR_INOUT(1) long int
(LIBCCALL libc_ftell)(FILE *__restrict stream) THROWS(...)
/*[[[body:libc_ftell]]]*/
{
	pos64_t result;
	if unlikely(!stream)
		return (long int)libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream)) {
		file_lock_read(stream);
		result = file_seek(stream, 0, SEEK_CUR);
		file_lock_endread(stream);
	} else {
		result = file_seek(stream, 0, SEEK_CUR);
	}
	if unlikely(result > LONG_MAX)
		return (long int)libc_seterrno(EOVERFLOW);
	return (long int)(off64_t)result;
}
/*[[[end:libc_ftell]]]*/

/*[[[head:libc_ftell_unlocked,hash:CRC-32=0x5a61185e]]]*/
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.seek.seek") WUNUSED ATTR_INOUT(1) long int
(LIBCCALL libc_ftell_unlocked)(FILE *__restrict stream) THROWS(...)
/*[[[body:libc_ftell_unlocked]]]*/
{
	pos64_t result;
	if unlikely(!stream)
		return (long int)libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	result = file_seek(stream, 0, SEEK_CUR);
	if unlikely(result > LONG_MAX)
		return (long int)libc_seterrno(EOVERFLOW);
	return (long int)(off64_t)result;
}
/*[[[end:libc_ftell_unlocked]]]*/

/*[[[head:libc_ftello,hash:CRC-32=0xbdd7dcbd]]]*/
#if __SIZEOF_OFF_T__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_ftello, libc_ftell);
#else /* MAGIC:alias */
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.seek.seek") WUNUSED ATTR_INOUT(1) off_t
(LIBCCALL libc_ftello)(FILE *__restrict stream) THROWS(...)
/*[[[body:libc_ftello]]]*/
{
	pos64_t result;
	if unlikely(!stream)
		return (off_t)libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream)) {
		file_lock_read(stream);
		result = file_seek(stream, 0, SEEK_CUR);
		file_lock_endread(stream);
	} else {
		result = file_seek(stream, 0, SEEK_CUR);
	}
	if unlikely(result > OFF_MAX)
		return (off_t)libc_seterrno(EOVERFLOW);
	return (off_t)(pos_t)result;
}
#endif /* MAGIC:alias */
/*[[[end:libc_ftello]]]*/

/*[[[head:libc_ftello_unlocked,hash:CRC-32=0x3a02df12]]]*/
#if __SIZEOF_OFF_T__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_ftello_unlocked, libc_ftell_unlocked);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.seek.seek") WUNUSED ATTR_INOUT(1) off_t
(LIBCCALL libc_ftello_unlocked)(FILE *__restrict stream) THROWS(...)
/*[[[body:libc_ftello_unlocked]]]*/
{
	pos64_t result;
	if unlikely(!stream)
		return (off_t)libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	result = file_seek(stream, 0, SEEK_CUR);
	if unlikely(result > OFF_MAX)
		return (off_t)libc_seterrno(EOVERFLOW);
	return (off_t)(pos_t)result;
}
#endif /* MAGIC:alias */
/*[[[end:libc_ftello_unlocked]]]*/

/*[[[head:libc_ftello64,hash:CRC-32=0xd42097c1]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_ftello64, libc_ftello);
#else /* MAGIC:alias */
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.seek.seek") WUNUSED ATTR_INOUT(1) off64_t
(LIBCCALL libc_ftello64)(FILE *__restrict stream) THROWS(...)
/*[[[body:libc_ftello64]]]*/
{
	pos64_t result;
	if unlikely(!stream)
		return (off64_t)libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	file_lock_read(stream);
	result = file_seek(stream, 0, SEEK_CUR);
	file_lock_endread(stream);
	if unlikely(result > OFF64_MAX)
		return (off64_t)libc_seterrno(EOVERFLOW);
	return (off64_t)result;
}
#endif /* MAGIC:alias */
/*[[[end:libc_ftello64]]]*/

/*[[[head:libc_ftello64_unlocked,hash:CRC-32=0xa8b5c04f]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_ftello64_unlocked, libc_ftello_unlocked);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.seek.seek") WUNUSED ATTR_INOUT(1) off64_t
(LIBCCALL libc_ftello64_unlocked)(FILE *__restrict stream) THROWS(...)
/*[[[body:libc_ftello64_unlocked]]]*/
{
	pos64_t result;
	if unlikely(!stream)
		return (off64_t)libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	result = file_seek(stream, 0, SEEK_CUR);
	if unlikely(result > OFF64_MAX)
		return (off64_t)libc_seterrno(EOVERFLOW);
	return (off64_t)result;
}
#endif /* MAGIC:alias */
/*[[[end:libc_ftello64_unlocked]]]*/








/************************************************************************/
/* fseek[_unlocked](3), fseeko[_unlocked](3), fseeko64[_unlocked](3)    */
/************************************************************************/

/*[[[head:libc_fseek,hash:CRC-32=0xd6971d21]]]*/
/* >> fseek(3)
 * Change the current in-file position of `stream' as a byte-offset from the start of the file */
INTERN ATTR_SECTION(".text.crt.FILE.locked.seek.seek") ATTR_INOUT(1) int
(LIBCCALL libc_fseek)(FILE *__restrict stream,
                      long int off,
                      int whence) THROWS(...)
/*[[[body:libc_fseek]]]*/
{
	int result;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		file_seek(stream, (off64_t)off, whence);
		result = unlikely(FERROR(stream)) ? -1 : 0;
		file_lock_endwrite(stream);
	} else {
		file_seek(stream, (off64_t)off, whence);
		result = unlikely(FERROR(stream)) ? -1 : 0;
	}
	return result;
}
/*[[[end:libc_fseek]]]*/

/*[[[head:libc_fseek_unlocked,hash:CRC-32=0xb313b947]]]*/
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.seek.seek") ATTR_INOUT(1) int
(LIBCCALL libc_fseek_unlocked)(FILE *__restrict stream,
                               long int off,
                               int whence) THROWS(...)
/*[[[body:libc_fseek_unlocked]]]*/
{
	int result;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	file_seek(stream, (off64_t)off, whence);
	result = unlikely(FERROR(stream)) ? -1 : 0;
	return result;
}
/*[[[end:libc_fseek_unlocked]]]*/

/*[[[head:libc_fseeko,hash:CRC-32=0x885a541e]]]*/
#if __SIZEOF_OFF_T__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_fseeko, libc_fseek);
#else /* MAGIC:alias */
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.seek.seek") ATTR_INOUT(1) int
(LIBCCALL libc_fseeko)(FILE *__restrict stream,
                       off_t off,
                       int whence) THROWS(...)
/*[[[body:libc_fseeko]]]*/
{
	int result;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		file_seek(stream, (off64_t)off, whence);
		result = unlikely(FERROR(stream)) ? -1 : 0;
		file_lock_endwrite(stream);
	} else {
		file_seek(stream, (off64_t)off, whence);
		result = unlikely(FERROR(stream)) ? -1 : 0;
	}
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:libc_fseeko]]]*/

/*[[[head:libc_fseeko_unlocked,hash:CRC-32=0x87e7e130]]]*/
#if __SIZEOF_OFF_T__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_fseeko_unlocked, libc_fseek_unlocked);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.seek.seek") ATTR_INOUT(1) int
(LIBCCALL libc_fseeko_unlocked)(FILE *__restrict stream,
                                off_t off,
                                int whence) THROWS(...)
/*[[[body:libc_fseeko_unlocked]]]*/
{
	int result;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	file_seek(stream, (off64_t)off, whence);
	result = unlikely(FERROR(stream)) ? -1 : 0;
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:libc_fseeko_unlocked]]]*/

/*[[[head:libc_fseeko64,hash:CRC-32=0x3cbf51ad]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_fseeko64, libc_fseeko);
#else /* MAGIC:alias */
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.seek.seek") ATTR_INOUT(1) int
(LIBCCALL libc_fseeko64)(FILE *__restrict stream,
                         off64_t off,
                         int whence) THROWS(...)
/*[[[body:libc_fseeko64]]]*/
{
	int result;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		file_seek(stream, (off64_t)off, whence);
		result = unlikely(FERROR(stream)) ? -1 : 0;
		file_lock_endwrite(stream);
	} else {
		file_seek(stream, (off64_t)off, whence);
		result = unlikely(FERROR(stream)) ? -1 : 0;
	}
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:libc_fseeko64]]]*/

/*[[[head:libc_fseeko64_unlocked,hash:CRC-32=0x80a03001]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_fseeko64_unlocked, libc_fseeko_unlocked);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.seek.seek") ATTR_INOUT(1) int
(LIBCCALL libc_fseeko64_unlocked)(FILE *__restrict stream,
                                  off64_t off,
                                  int whence) THROWS(...)
/*[[[body:libc_fseeko64_unlocked]]]*/
{
	int result;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	file_seek(stream, (off64_t)off, whence);
	result = unlikely(FERROR(stream)) ? -1 : 0;
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:libc_fseeko64_unlocked]]]*/








/************************************************************************/
/* fgetpos[_unlocked](3), fsetpos[_unlocked](3)                         */
/* fgetpos64[_unlocked](3), fsetpos64[_unlocked](3)                     */
/************************************************************************/

/*[[[head:libc_fgetpos,hash:CRC-32=0xa30357e9]]]*/
/* >> fgetpos(3), fgetpos64(3)
 * Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.seek.pos") ATTR_INOUT(1) ATTR_OUT(2) int
(LIBCCALL libc_fgetpos)(FILE *__restrict stream,
                        fpos_t *__restrict pos) THROWS(...)
/*[[[body:libc_fgetpos]]]*/
{
	off_t result = ftello(stream);
	if unlikely(result == -1 && libc_geterrno() != EOK)
		return -1;
	*pos = (fpos_t)result;
	return 0;
}
/*[[[end:libc_fgetpos]]]*/

/*[[[head:libc_fgetpos_unlocked,hash:CRC-32=0x87fc3d54]]]*/
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.seek.pos") ATTR_INOUT(1) ATTR_OUT(2) int
(LIBCCALL libc_fgetpos_unlocked)(FILE *__restrict stream,
                                 fpos_t *__restrict pos) THROWS(...)
/*[[[body:libc_fgetpos_unlocked]]]*/
{
	off_t result = ftello_unlocked(stream);
	if unlikely(result == -1 && libc_geterrno() != EOK)
		return -1;
	*pos = (fpos_t)result;
	return 0;
}
/*[[[end:libc_fgetpos_unlocked]]]*/

/*[[[head:libc_fsetpos,hash:CRC-32=0xb3757bfa]]]*/
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.seek.pos") ATTR_IN(2) ATTR_INOUT(1) int
(LIBCCALL libc_fsetpos)(FILE *__restrict stream,
                        fpos_t const *__restrict pos) THROWS(...)
/*[[[body:libc_fsetpos]]]*/
{
	return fseeko(stream, (off_t)(pos_t)*pos, SEEK_SET);
}
/*[[[end:libc_fsetpos]]]*/

/*[[[head:libc_fsetpos_unlocked,hash:CRC-32=0x8fdd8faa]]]*/
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.seek.pos") ATTR_IN(2) ATTR_INOUT(1) int
(LIBCCALL libc_fsetpos_unlocked)(FILE *__restrict stream,
                                 fpos_t const *__restrict pos) THROWS(...)
/*[[[body:libc_fsetpos_unlocked]]]*/
{
	return fseeko_unlocked(stream, (off_t)(pos_t)*pos, SEEK_SET);
}
/*[[[end:libc_fsetpos_unlocked]]]*/

/*[[[head:libc_fgetpos64,hash:CRC-32=0xb3cdfb42]]]*/
#if __SIZEOF_FPOS32_T__ == __SIZEOF_FPOS64_T__
DEFINE_INTERN_ALIAS(libc_fgetpos64, libc_fgetpos);
#else /* MAGIC:alias */
/* >> fgetpos(3), fgetpos64(3)
 * Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.seek.pos") ATTR_INOUT(1) ATTR_OUT(2) int
(LIBCCALL libc_fgetpos64)(FILE *__restrict stream,
                          fpos64_t *__restrict pos) THROWS(...)
/*[[[body:libc_fgetpos64]]]*/
{
	off64_t result = ftello64(stream);
	if unlikely(result == -1 && libc_geterrno() != EOK)
		return -1;
	*pos = (fpos64_t)result;
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_fgetpos64]]]*/

/*[[[head:libc_fgetpos64_unlocked,hash:CRC-32=0x1dbbea6f]]]*/
#if __SIZEOF_FPOS32_T__ == __SIZEOF_FPOS64_T__
DEFINE_INTERN_ALIAS(libc_fgetpos64_unlocked, libc_fgetpos_unlocked);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.seek.pos") ATTR_INOUT(1) ATTR_OUT(2) int
(LIBCCALL libc_fgetpos64_unlocked)(FILE *__restrict stream,
                                   fpos64_t *__restrict pos) THROWS(...)
/*[[[body:libc_fgetpos64_unlocked]]]*/
{
	off64_t result = ftello64_unlocked(stream);
	if unlikely(result == -1 && libc_geterrno() != EOK)
		return -1;
	*pos = (fpos64_t)result;
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_fgetpos64_unlocked]]]*/

/*[[[head:libc_fsetpos64,hash:CRC-32=0x6093e7e5]]]*/
#if __SIZEOF_FPOS32_T__ == __SIZEOF_FPOS64_T__
DEFINE_INTERN_ALIAS(libc_fsetpos64, libc_fsetpos);
#else /* MAGIC:alias */
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.seek.pos") ATTR_IN(2) ATTR_INOUT(1) int
(LIBCCALL libc_fsetpos64)(FILE *__restrict stream,
                          fpos64_t const *__restrict pos) THROWS(...)
/*[[[body:libc_fsetpos64]]]*/
{
	return fseeko64(stream, (off64_t)(pos64_t)*pos, SEEK_SET);
}
#endif /* MAGIC:alias */
/*[[[end:libc_fsetpos64]]]*/

/*[[[head:libc_fsetpos64_unlocked,hash:CRC-32=0xf3b90dc5]]]*/
#if __SIZEOF_FPOS32_T__ == __SIZEOF_FPOS64_T__
DEFINE_INTERN_ALIAS(libc_fsetpos64_unlocked, libc_fsetpos_unlocked);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.seek.pos") ATTR_IN(2) ATTR_INOUT(1) int
(LIBCCALL libc_fsetpos64_unlocked)(FILE *__restrict stream,
                                   fpos64_t const *__restrict pos) THROWS(...)
/*[[[body:libc_fsetpos64_unlocked]]]*/
{
	return fseeko64_unlocked(stream, (off64_t)(pos64_t)*pos, SEEK_SET);
}
#endif /* MAGIC:alias */
/*[[[end:libc_fsetpos64_unlocked]]]*/








/************************************************************************/
/* ungetc[_unlocked](3)                                                 */
/************************************************************************/

/*[[[head:libc_ungetc,hash:CRC-32=0xe8eebbd0]]]*/
/* >> ungetc(3)
 * Unget a single character byte of data previously returned by `getc()' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.getc") ATTR_INOUT(2) int
NOTHROW_NCX(LIBCCALL libc_ungetc)(int ch,
                                  FILE *__restrict stream)
/*[[[body:libc_ungetc]]]*/
{
	int result;
	if unlikely(!stream)
		return libc_seterrno_and_return_EOF(EINVAL);
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		result = file_ungetc(stream, (unsigned char)(unsigned int)ch);
		file_lock_endwrite(stream);
	} else {
		result = file_ungetc(stream, (unsigned char)(unsigned int)ch);
	}
	return result;
}
/*[[[end:libc_ungetc]]]*/

/* From: libc4/5 */
DEFINE_PUBLIC_ALIAS(_IO_sputbackc, libc__IO_sputbackc);
DEFINE_PUBLIC_ALIAS(_IO_default_pbackfail, libc__IO_sputbackc);
INTERN ATTR_SECTION(".text.crt.compat.linux") int
NOTHROW_NCX(LIBCCALL libc__IO_sputbackc)(FILE *__restrict stream, int ch) {
	return libc_ungetc(ch, stream);
}

DEFINE_PUBLIC_ALIAS(_IO_sungetc, libc__IO_sungetc);
INTERN ATTR_SECTION(".text.crt.compat.linux") int
NOTHROW_NCX(LIBCCALL libc__IO_sungetc)(FILE *__restrict stream) {
	int result;
	if unlikely(!stream)
		return libc_seterrno_and_return_EOF(EINVAL);
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		result = file_sungetc(stream);
		file_lock_endwrite(stream);
	} else {
		result = file_sungetc(stream);
	}
	return result;
}

DEFINE_PUBLIC_ALIAS(_IO_un_link, libc__IO_nop);        /* Supposed to call `allfiles_remove(stream)' here that would break `fclose(3)' */
DEFINE_PUBLIC_ALIAS(_IO_link_in, libc__IO_nop);        /* Supposed to call `allfiles_insert(stream)' here that would break `fclose(3)' */
DEFINE_PUBLIC_ALIAS(_IO_default_finish, libc__IO_nop); /* Supposed to do cleanup, but we only do that in `fclose(3)' */
DEFINE_PUBLIC_ALIAS(_IO_unsave_markers, libc__IO_nop); /* Supposed to clean up markers (which we don't implement) */
DEFINE_PUBLIC_ALIAS(_IO_remove_marker, libc__IO_nop);  /* Supposed to clean up markers (which we don't implement) */
INTERN ATTR_SECTION(".text.crt.compat.linux") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc__IO_nop)(FILE *__restrict stream) {
	(void)stream;
	COMPILER_IMPURE();
}

DEFINE_PUBLIC_ALIAS(_IO_unbuffer_all, libc__IO_unbuffer_all);
INTERN ATTR_SECTION(".text.crt.compat.linux") void
NOTHROW_NCX(LIBCCALL libc__IO_unbuffer_all)(void) {
	FILE *fp;
	all_files_read();
	LIST_FOREACH (fp, &all_files, if_exdata->io_link) {
		setvbuf(file_touser(fp), NULL, _IONBF, 0);
	}
	all_files_endread();
}

DEFINE_PUBLIC_ALIAS(_IO_ignore, libc__IO_ignore);
INTERN ATTR_SECTION(".text.crt.compat.linux") NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__IO_ignore)(FILE *__restrict stream, size_t n) {
	size_t result = 0;
	/* Super inefficient, but we're only here for compat, so that's OK. */
	while (result < n) {
		if (fgetc(stream) == EOF)
			break;
		++result;
	}
	return result;
}

DEFINE_PUBLIC_ALIAS(_IO_padn, libc__IO_padn);
INTERN ATTR_SECTION(".text.crt.compat.linux") NONNULL((1)) ssize_t
NOTHROW_NCX(LIBCCALL libc__IO_padn)(FILE *__restrict stream, int padch, size_t n) {
	size_t result = 0;
	/* Super inefficient, but we're only here for compat, so that's OK. */
	while (result < n) {
		if (fputc(padch, stream) == EOF)
			break;
		++result;
	}
	return result;
}

DEFINE_PUBLIC_ALIAS(_IO_do_write, libc__IO_do_write);
INTERN ATTR_SECTION(".text.crt.compat.linux") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc__IO_do_write)(FILE *__restrict stream,
                                        void const *buf, size_t buflen) {
	size_t result;
	result = fwrite(buf, 1, buflen, stream);
	return result == buflen ? 0 : EOF;
}

DEFINE_PUBLIC_ALIAS(_IO_default_xsputn, libc__IO_default_xsputn);
INTERN ATTR_SECTION(".text.crt.compat.linux") NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__IO_default_xsputn)(FILE *__restrict stream,
                                              void const *buf, size_t buflen) {
	return fwrite(buf, 1, buflen, stream);
}

DEFINE_PUBLIC_ALIAS(_IO_sgetn, libc__IO_sgetn);
DEFINE_PUBLIC_ALIAS(_IO_default_xsgetn, libc__IO_sgetn);
INTERN ATTR_SECTION(".text.crt.compat.linux") NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__IO_sgetn)(FILE *__restrict stream,
                                     void *buf, size_t buflen) {
	return fread(buf, 1, buflen, stream);
}

DEFINE_PUBLIC_ALIAS(_IO_nobackup_pbackfail, libc__IO_nobackup_pbackfail);
INTERN ATTR_SECTION(".text.crt.compat.linux") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc__IO_nobackup_pbackfail)(FILE *__restrict stream, int ch) {
	stream = file_fromuser(stream);
	if (stream->if_ptr > stream->if_base) {
		--stream->if_ptr;
		++stream->if_cnt;
	}
	if (stream->if_cnt && ch != EOF)
		*stream->if_ptr = (unsigned char)(unsigned int)ch;
	return (int)(unsigned int)(unsigned char)(unsigned int)ch;
}

DEFINE_PUBLIC_ALIAS(_IO_setb, libc__IO_setb);
INTERN ATTR_SECTION(".text.crt.compat.linux") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc__IO_setb)(FILE *__restrict stream,
                                    void *bufbase,
                                    void *bufend,
                                    int set_IO_MALLBUF) {
	stream = file_fromuser(stream);
	if (stream->if_flag & IO_MALLBUF)
		free(stream->if_base);
	stream->if_flag &= ~(IO_MALLBUF | IO_NODYNSCALE | IO_LNBUF | IO_LNIFTYY);
	stream->if_ptr  = (unsigned char *)bufbase;
	stream->if_base = (unsigned char *)bufbase;
	stream->if_cnt  = (uint32_t)(size_t)((byte_t *)bufend - (byte_t *)bufbase);
	stream->if_exdata->io_chng = stream->if_base;
	if (set_IO_MALLBUF)
		stream->if_flag |= IO_MALLBUF;
}

DEFINE_PUBLIC_ALIAS(_IO_doallocbuf, libc__IO_doallocbuf);
DEFINE_PUBLIC_ALIAS(_IO_default_doallocate, libc__IO_doallocbuf);
INTERN ATTR_SECTION(".text.crt.compat.linux") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc__IO_doallocbuf)(FILE *__restrict stream) {
	stream = file_fromuser(stream);
	if (stream->if_cnt != 0 || stream->if_ptr > stream->if_base)
		goto done; /* Already has a buffer. */
	if (file_setmode(stream, NULL, _IOFBF, IOBUF_MIN) == 0)
		goto done; /* Was able to assign a dynamically allocated buffer. */
	/* Fun fact: KOS's stdio also has an inline buffer. And even though
	 * it's  normally only there for DOS-compat, we can actually use it
	 * for its intended purpose here! */
	libc__IO_setb(file_touser(stream),
	              stream->if_charbuf,
	              stream->if_charbuf + lengthof(stream->if_charbuf),
	              0);
done:
	return 1; /* NOTE: Only `_IO_default_doallocate()' has return value (`_IO_doallocbuf()' returns void) */
}

INTERN ATTR_SECTION(".text.crt.compat.linux") NONNULL((1)) int64_t
NOTHROW_NCX(LIBCCALL libc__IO_return_M1_R1)(FILE *__restrict stream) {
	(void)stream;
	COMPILER_IMPURE();
	return -1;
}
INTERN ATTR_SECTION(".text.crt.compat.linux") NONNULL((1)) int64_t
NOTHROW_NCX(LIBCCALL libc__IO_return_0_R1)(FILE *__restrict stream) {
	(void)stream;
	COMPILER_IMPURE();
	return 0;
}
#ifdef __LIBCCALL_CALLER_CLEANUP
#define libc__IO_return_M1_R2 libc__IO_return_M1_R1
#define libc__IO_return_M1_R3 libc__IO_return_M1_R1
#define libc__IO_return_0_R2  libc__IO_return_0_R1
#define libc__IO_return_0_R3  libc__IO_return_0_R1
#else /* __LIBCCALL_CALLER_CLEANUP */
INTERN ATTR_SECTION(".text.crt.compat.linux") NONNULL((1)) int64_t
NOTHROW_NCX(LIBCCALL libc__IO_return_M1_R2)(FILE *__restrict stream, void *a) {
	(void)stream;
	(void)a;
	COMPILER_IMPURE();
	return -1;
}
INTERN ATTR_SECTION(".text.crt.compat.linux") NONNULL((1)) int64_t
NOTHROW_NCX(LIBCCALL libc__IO_return_M1_R3)(FILE *__restrict stream, void *a, void *b) {
	(void)stream;
	(void)a;
	(void)b;
	COMPILER_IMPURE();
	return -1;
}
INTERN ATTR_SECTION(".text.crt.compat.linux") NONNULL((1)) int64_t
NOTHROW_NCX(LIBCCALL libc__IO_return_0_R2)(FILE *__restrict stream, void *a) {
	(void)stream;
	(void)a;
	COMPILER_IMPURE();
	return 0;
}
INTERN ATTR_SECTION(".text.crt.compat.linux") NONNULL((1)) int64_t
NOTHROW_NCX(LIBCCALL libc__IO_return_0_R3)(FILE *__restrict stream, void *a, void *b) {
	(void)stream;
	(void)a;
	(void)b;
	COMPILER_IMPURE();
	return 0;
}
#endif /* !__LIBCCALL_CALLER_CLEANUP */
DEFINE_PUBLIC_ALIAS(_IO_default_underflow, libc__IO_return_M1_R1);
DEFINE_PUBLIC_ALIAS(_IO_default_seek, libc__IO_return_M1_R3);
DEFINE_PUBLIC_ALIAS(_IO_default_stat, libc__IO_return_M1_R2);
DEFINE_PUBLIC_ALIAS(_IO_default_read, libc__IO_return_M1_R3);
DEFINE_PUBLIC_ALIAS(_IO_default_sync, libc__IO_return_0_R1);
DEFINE_PUBLIC_ALIAS(_IO_default_write, libc__IO_return_0_R3);
DEFINE_PUBLIC_ALIAS(_IO_marker_delta, libc__IO_return_0_R1);
DEFINE_PUBLIC_ALIAS(_IO_marker_difference, libc__IO_return_0_R2);
DEFINE_PUBLIC_ALIAS(_IO_init_marker, libc__IO_return_0_R2); /* Actually returns void */
DEFINE_PUBLIC_ALIAS(_IO_least_marker, libc__IO_return_0_R1);

/* We don't keep track of any column values... (so don't implement these) */
DEFINE_PUBLIC_ALIAS(_IO_get_column, libc__IO_return_M1_R1);
DEFINE_PUBLIC_ALIAS(_IO_set_column, libc__IO_return_0_R2);
DEFINE_PUBLIC_ALIAS(_IO_adjust_column, libc__IO_adjust_column);
INTERN ATTR_SECTION(".text.crt.compat.linux") unsigned int
NOTHROW_NCX(LIBCCALL libc__IO_adjust_column)(unsigned int start,
                                             char const *line,
                                             unsigned int count) {
	COMPILER_IMPURE();
	(void)line;
	(void)count;
	return start;
}


/*[[[head:libc_ungetc_unlocked,hash:CRC-32=0x96fcb2cb]]]*/
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.getc") ATTR_INOUT(2) int
NOTHROW_NCX(LIBCCALL libc_ungetc_unlocked)(int ch,
                                           FILE *__restrict stream)
/*[[[body:libc_ungetc_unlocked]]]*/
{
	int result;
	if unlikely(!stream)
		return libc_seterrno_and_return_EOF(EINVAL);
	stream = file_fromuser(stream);
	result = file_ungetc(stream, (unsigned char)(unsigned int)ch);
	return result;
}
/*[[[end:libc_ungetc_unlocked]]]*/








/************************************************************************/
/* rewind[_unlocked](3)                                                 */
/************************************************************************/

/*[[[head:libc_rewind,hash:CRC-32=0x66e9917a]]]*/
/* >> rewind(3)
 * Rewind the current in-file position of `stream' to its starting position */
INTERN ATTR_SECTION(".text.crt.FILE.locked.seek.utility") ATTR_INOUT(1) void
(LIBCCALL libc_rewind)(FILE *__restrict stream) THROWS(...)
/*[[[body:libc_rewind]]]*/
{
	if likely(stream) {
		stream = file_fromuser(stream);
		if (FMUSTLOCK(stream)) {
			file_lock_write(stream);
			file_seek(stream, 0, SEEK_SET);
			stream->if_flag &= ~(IO_EOF | IO_ERR);
			file_lock_endwrite(stream);
		} else {
			file_seek(stream, 0, SEEK_SET);
			stream->if_flag &= ~(IO_EOF | IO_ERR);
		}
	}
}
/*[[[end:libc_rewind]]]*/

/*[[[head:libc_rewind_unlocked,hash:CRC-32=0xccdbf6a8]]]*/
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.seek.utility") ATTR_INOUT(1) void
(LIBCCALL libc_rewind_unlocked)(FILE *__restrict stream) THROWS(...)
/*[[[body:libc_rewind_unlocked]]]*/
{
	if likely(stream) {
		stream = file_fromuser(stream);
		file_seek(stream, 0, SEEK_SET);
		stream->if_flag &= ~(IO_EOF | IO_ERR);
	}
}
/*[[[end:libc_rewind_unlocked]]]*/








/************************************************************************/
/* fisatty(3)                                                           */
/************************************************************************/

/*[[[head:libc_fisatty,hash:CRC-32=0xedbae8bc]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") WUNUSED ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_fisatty)(FILE *__restrict stream)
/*[[[body:libc_fisatty]]]*/
{
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	file_determine_isatty(stream);
	return (stream->if_flag & IO_ISATTY) != 0;
}
/*[[[end:libc_fisatty]]]*/








/************************************************************************/
/* fftruncate[_unlocked](3), fftruncate64[_unlocked](3)                 */
/************************************************************************/

/*[[[head:libc_fftruncate,hash:CRC-32=0x4ae02efe]]]*/
/* >> fftruncate(3)
 * Truncate the given file `stream' to a length of `length' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.utility") ATTR_INOUT(1) int
(LIBCCALL libc_fftruncate)(FILE *__restrict stream,
                           __PIO_OFFSET length) THROWS(...)
/*[[[body:libc_fftruncate]]]*/
{
	int result;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		result = file_truncate(stream, (pos64_t)length);
		file_lock_endwrite(stream);
	} else {
		result = file_truncate(stream, (pos64_t)length);
	}
	return result;
}
/*[[[end:libc_fftruncate]]]*/

/*[[[head:libc_fftruncate_unlocked,hash:CRC-32=0xfcf0c177]]]*/
/* >> fftruncate_unlocked(3)
 * Same as `fftruncate()', but don't acquire a lock to the file */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.utility") ATTR_INOUT(1) int
(LIBCCALL libc_fftruncate_unlocked)(FILE *__restrict stream,
                                    __PIO_OFFSET length) THROWS(...)
/*[[[body:libc_fftruncate_unlocked]]]*/
{
	int result;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	result = file_truncate(stream, (pos64_t)length);
	return result;
}
/*[[[end:libc_fftruncate_unlocked]]]*/

/*[[[head:libc_fftruncate64,hash:CRC-32=0x7e3673c7]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_fftruncate64, libc_fftruncate);
#else /* MAGIC:alias */
/* >> fftruncate64(3)
 * Truncate the given file `stream' to a length of `length' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.utility") ATTR_INOUT(1) int
(LIBCCALL libc_fftruncate64)(FILE *__restrict stream,
                             __PIO_OFFSET64 length) THROWS(...)
/*[[[body:libc_fftruncate64]]]*/
{
	int result;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		result = file_truncate(stream, (pos64_t)length);
		file_lock_endwrite(stream);
	} else {
		result = file_truncate(stream, (pos64_t)length);
	}
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:libc_fftruncate64]]]*/

/*[[[head:libc_fftruncate64_unlocked,hash:CRC-32=0xbf00a71f]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_fftruncate64_unlocked, libc_fftruncate_unlocked);
#else /* MAGIC:alias */
/* >> fftruncate64_unlocked(3)
 * Truncate the given file `stream' to a length of `length' */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.utility") ATTR_INOUT(1) int
(LIBCCALL libc_fftruncate64_unlocked)(FILE *__restrict stream,
                                      __PIO_OFFSET64 length) THROWS(...)
/*[[[body:libc_fftruncate64_unlocked]]]*/
{
	int result;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	result = file_truncate(stream, (pos64_t)length);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:libc_fftruncate64_unlocked]]]*/








/************************************************************************/
/* setvbuf[_unlocked](3)                                                */
/************************************************************************/

/*[[[head:libc_setvbuf,hash:CRC-32=0x6f7babf4]]]*/
/* >> setvbuf(3)
 * Set the buffer and buffer-mode to-be used by the given `stream'
 * @param modes: One of `_IOFBF', `_IOLBF' or `_IONBF' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.utility") ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_setvbuf)(FILE *__restrict stream,
                                   char *__restrict buf,
                                   __STDC_INT_AS_UINT_T modes,
                                   size_t bufsize)
/*[[[body:libc_setvbuf]]]*/
{
	int result;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		result = file_sync(stream);
		if likely(result == 0) {
			result = file_setmode(stream,
			                      buf,
			                      modes,
			                      bufsize);
		}
		file_lock_endwrite(stream);
	} else {
		result = file_sync(stream);
		if likely(result == 0) {
			result = file_setmode(stream,
			                      buf,
			                      modes,
			                      bufsize);
		}
	}
	return result;
}
/*[[[end:libc_setvbuf]]]*/

/*[[[head:libc_setvbuf_unlocked,hash:CRC-32=0xb426e2f4]]]*/
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.utility") ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_setvbuf_unlocked)(FILE *__restrict stream,
                                            char *__restrict buf,
                                            __STDC_INT_AS_UINT_T modes,
                                            size_t bufsize)
/*[[[body:libc_setvbuf_unlocked]]]*/
{
	int result;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	result = file_sync(stream);
	if likely(result == 0) {
		result = file_setmode(stream,
		                      buf,
		                      modes,
		                      bufsize);
	}
	return result;
}
/*[[[end:libc_setvbuf_unlocked]]]*/








/************************************************************************/
/* feof(3), ferror(3), clearerr(3)                                      */
/************************************************************************/

/*[[[head:libc_feof,hash:CRC-32=0x78012c42]]]*/
/* >> feof(3)
 * Check if end-of-file has been reached in `stream' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.utility") ATTR_PURE WUNUSED ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_feof)(FILE __KOS_FIXED_CONST *__restrict stream)
/*[[[body:libc_feof]]]*/
{
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	return FEOF(stream);
}
/*[[[end:libc_feof]]]*/

/*[[[head:libc_ferror,hash:CRC-32=0x3c0f94b1]]]*/
/* >> ferror(3)
 * Check if an I/O error occurred in `stream' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.utility") ATTR_PURE WUNUSED ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_ferror)(FILE __KOS_FIXED_CONST *__restrict stream)
/*[[[body:libc_ferror]]]*/
{
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	return FERROR(stream);
}
/*[[[end:libc_ferror]]]*/

/*[[[head:libc_clearerr,hash:CRC-32=0x2a495ee6]]]*/
/* >> clearerr(3)
 * Clear the error state of `stream', returning the stream to normal operations mode */
INTERN ATTR_SECTION(".text.crt.FILE.locked.access") ATTR_INOUT(1) void
NOTHROW_NCX(LIBCCALL libc_clearerr)(FILE *__restrict stream)
/*[[[body:libc_clearerr]]]*/
{
	if likely(stream) {
		stream = file_fromuser(stream);
		FCLEARERR(stream);
	}
}
/*[[[end:libc_clearerr]]]*/








/************************************************************************/
/* fileno(3)                                                            */
/************************************************************************/

/*[[[head:libc_fileno,hash:CRC-32=0x192582a0]]]*/
/* >> fileno(3)
 * Return the underlying file descriptor number used by `stream' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.utility") WUNUSED ATTR_INOUT(1) fd_t
NOTHROW_NCX(LIBCCALL libc_fileno)(FILE *__restrict stream)
/*[[[body:libc_fileno]]]*/
{
	if unlikely(!stream)
		goto err_inval;
	stream = file_fromuser(stream);
	if unlikely(stream->if_flag & IO_HASVTAB)
		goto err_nostream;
	return atomic_read(&stream->if_fd);
err_nostream:
	/* """
	 * EBADF The stream is not associated with a file.
	 * """ */
	return (fd_t)libc_seterrno(EBADF);
err_inval:
	return (fd_t)libc_seterrno(EINVAL);
}
/*[[[end:libc_fileno]]]*/








/************************************************************************/
/* fopen(3), fopen64(3)                                                 */
/************************************************************************/

/*[[[head:libd_fopen,hash:CRC-32=0x4d179ebb]]]*/
/* >> fopen(3), fopen64(3)
 * Create and return a new file-stream for accessing `filename' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.access") WUNUSED ATTR_IN(1) ATTR_IN(2) FILE *
NOTHROW_RPC(LIBDCALL libd_fopen)(char const *__restrict filename,
                                 char const *__restrict modes)
/*[[[body:libd_fopen]]]*/
{
	fd_t fd;
	FILE *result;
	uint32_t flags;
	oflag_t oflags;
	flags = file_evalmodes(modes, &oflags);
	fd    = open(filename, oflags | libd_O_DOSPATH, 0644);
	if unlikely(fd < 0)
		return NULL;
	result = file_openfd(fd, flags);
	if likely(result) {
		result = file_touser(result);
	} else {
		sys_close(fd);
	}
	return result;
}
/*[[[end:libd_fopen]]]*/

/*[[[head:libc_fopen,hash:CRC-32=0x591a0264]]]*/
/* >> fopen(3), fopen64(3)
 * Create and return a new file-stream for accessing `filename' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.access") WUNUSED ATTR_IN(1) ATTR_IN(2) FILE *
NOTHROW_RPC(LIBCCALL libc_fopen)(char const *__restrict filename,
                                 char const *__restrict modes)
/*[[[body:libc_fopen]]]*/
{
	/* TODO: (re-)add extension functions `fopenat()' and `fopenat64()'
	 *       that allow for  the specification of  `dfd' and  `atflags' */
	fd_t fd;
	FILE *result;
	uint32_t flags;
	oflag_t oflags;
	flags = file_evalmodes(modes, &oflags);
	fd    = open(filename, oflags, 0644);
	if unlikely(fd < 0)
		return NULL;
	result = file_openfd(fd, flags);
	if likely(result) {
		result = file_touser(result);
	} else {
		sys_close(fd);
	}
	return result;
}
/*[[[end:libc_fopen]]]*/








/************************************************************************/
/* fdopen(3)                                                            */
/************************************************************************/

/*[[[head:libc_fdopen,hash:CRC-32=0xb20003ef]]]*/
/* >> fdopen(3)
 * Open a new file stream by inheriting a given file descriptor `fd'
 * Note that upon success (`return != NULL'), the given `fd' will be
 * `close(2)'d once `fclose(return)' is called. */
INTERN ATTR_SECTION(".text.crt.FILE.locked.utility") WUNUSED ATTR_IN(2) FILE *
NOTHROW_NCX(LIBCCALL libc_fdopen)(fd_t fd,
                                  char const *__restrict modes)
/*[[[body:libc_fdopen]]]*/
{
	FILE *result;
	uint32_t flags;
	flags  = file_evalmodes(modes, NULL);
	result = file_openfd(fd, flags);
	result = file_touser_opt(result);
	return result;
}
/*[[[end:libc_fdopen]]]*/








/************************************************************************/
/* fclose(3)                                                            */
/************************************************************************/

/*[[[head:libc_fclose,hash:CRC-32=0xeebfb94b]]]*/
/* >> fclose(3)
 * Close and destroy a given file `stream' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.access") ATTR_INOUT(1) int
(LIBCCALL libc_fclose)(FILE *__restrict stream) THROWS(...)
/*[[[body:libc_fclose]]]*/
{
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	decref(stream);
	return 0;
}
/*[[[end:libc_fclose]]]*/








/************************************************************************/
/* fgetln(3)                                                            */
/************************************************************************/

/*[[[head:libc_fgetln,hash:CRC-32=0x9f2272a2]]]*/
/* >> fgetln(3)
 * A slightly more convenient (but way less portable) alternative to `fgets(3)'
 * This function automatically malloc's a  buffer of sufficient length for  the
 * next line in the given `stream', and stores its length in `*lenp'
 * NOTE: KOS adds the following extensions to this function:
 *  - We guaranty that "return[*lenp] == '\0'" upon a non-NULL return
 *  - You may pass `lenp == NULL', which simply ignores that argument
 * @return: NULL: The EOF flag of `stream' is set (fix this with `clearerr(3)'),
 *                or the underlying file has been fully read.
 * @return: * :   Pointer to an  automatically malloc'd  buffer (to-be  freed
 *                by  fclose(3)  once you  call  that function  on  the given
 *                `stream'). The buffer is re-used in subsequence invocations
 *                of this function, and documentation states that it may also
 *                be invalidated during any  other I/O operation relating  to
 *                `stream', though this isn't the case under KOS. */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.scanf") WUNUSED ATTR_INOUT(1) ATTR_OUT_OPT(2) char *
NOTHROW_NCX(LIBCCALL libc_fgetln)(FILE *__restrict stream,
                                  size_t *__restrict lenp)
/*[[[body:libc_fgetln]]]*/
{
	size_t i, bufsiz;
	char *result;
	if unlikely(!stream) {
		(void)libc_seterrno(EINVAL);
		return NULL;
	}
	stream = file_fromuser(stream);
	if (FEOF(stream)) /* XXX: Also do this on FERROR()? */
		return NULL;  /* Must return `NULL' after EOF */
	result = stream->if_exdata->io_getln;
	if (!result) {
		result = (char *)malloc(IOBUF_MIN, sizeof(char));
		if unlikely(!result)
			return NULL;
		stream->if_exdata->io_getln = result;
	}
	bufsiz = malloc_usable_size(result) / sizeof(char);
	assert(bufsiz != 0);
	for (i = 0;; ++i) {
		int ch;
		if (i >= bufsiz - 1) {
			/* Allocate larger buffer. */
			size_t new_bufsiz = bufsiz * 2;
			char *new_result;
			new_result = (char *)realloc(result, new_bufsiz, sizeof(char));
			if unlikely(!new_result) {
				new_bufsiz = i + 2;
				new_result = (char *)realloc(result, new_bufsiz, sizeof(char));
				if unlikely(!new_result)
					return NULL;
			}
			result = new_result;
			bufsiz = malloc_usable_size(result) / sizeof(char);
			assert(bufsiz >= new_bufsiz);
			stream->if_exdata->io_getln = result;
		}
		ch = libc_fgetc(stream);
		if (ch == EOF)
			break; /* End-of-file */
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			result[i++] = '\n';
			ch = libc_fgetc(stream);
			if (ch == EOF)
				break;
			if (ch == '\r')
				continue;
			libc_ungetc(ch, stream);
			break;
		}
		result[i] = (char)ch;
		if (ch == '\n') {
			++i; /* Must keep the trailing '\n' at the end of lines! */
			break;
		}
	}

	/* Special case: absolutely _must_ return `NULL' on EOF */
	if (i == 0)
		return NULL;

	/* NUL-terminate line.
	 * NOTE: This is actually a KOS extension, as BSD's fgetln()
	 *       documents that it  doesn't NUL-terminate the  line! */
	result[i] = '\0';

	/* KOS extension: we make the `lenp' argument optional. */
	if (lenp != NULL)
		*lenp = i;
	return result;



}
/*[[[end:libc_fgetln]]]*/




PRIVATE WUNUSED ATTR_SECTION(".text.crt.FILE.core.utility") NONNULL((1)) FILE *LIBCCALL
fp_funopen(void const *cookie,
           __funopen2_readfn_t readfn, __funopen2_writefn_t writefn,
           __funopen2_64_seekfn_t seekfn, __funopen2_flushfn_t flushfn,
           __funopen2_closefn_t closefn) {
	FILE *result;
	struct iofile_data *ex;
	result = file_calloc(sizeof(struct iofile_data));
	if unlikely(!result)
		goto done;
	ex = (struct iofile_data *)(result + 1);
	result->if_exdata = ex;
	assert(ex->io_getln == NULL);
	shared_recursive_rwlock_cinit(&ex->io_lock);
	assert(ex->io_zero == 0);
	ex->io_refcnt = 1;

	/* Initialize flags:
	 *  - IO_HASVTAB: The most important flag: this is a V-table FILE.
	 *  - IO_NOTATTY: Well... It's not a tty, isn't it?
	 *  - IO_FSYNC:   Required so that `io_flushfn()' gets called during fflush(3)
	 *  - IO_RW:      Indicative of `io_writefn()' being available. */
	result->if_flag = IO_HASVTAB | IO_NOTATTY | IO_FSYNC;
	if (writefn != NULL)
		result->if_flag |= IO_RW;
	ex->io_readfn  = readfn;
	ex->io_writefn = writefn;
	ex->io_seekfn  = seekfn;
	ex->io_flushfn = flushfn;
	ex->io_closefn = closefn;
	ex->io_cookie  = (void *)cookie;

	/* Insert the new file stream into the global list of them. */
	allfiles_insert(result);
	result = file_touser(result);
done:
	return result;
}


#if __SIZEOF_OFF64_T__ != __SIZEOF_OFF32_T__
struct funopen2_32_holder {
	void                *fh_cookie;  /* [?..?] funopen2 cookie */
	__funopen2_readfn_t  fh_readfn;  /* [0..1] funopen2 readfn */
	__funopen2_writefn_t fh_writefn; /* [0..1] funopen2 writefn */
	__funopen2_seekfn_t  fh_seekfn;  /* [0..1] funopen2 seekfn */
	__funopen2_flushfn_t fh_flushfn; /* [0..1] funopen2 flushfn */
	__funopen2_closefn_t fh_closefn; /* [0..1] funopen2 closefn */
};

PRIVATE ATTR_SECTION(".text.crt.FILE.locked.utility") ssize_t LIBKCALL
funopen2_32_readfn(void *cookie, void *buf, size_t num_bytes) {
	struct funopen2_32_holder *holder;
	holder = (struct funopen2_32_holder *)cookie;
	return (*holder->fh_readfn)(holder->fh_cookie, buf, num_bytes);
}

PRIVATE ATTR_SECTION(".text.crt.FILE.locked.utility") ssize_t LIBKCALL
funopen2_32_writefn(void *cookie, void const *buf, size_t num_bytes) {
	struct funopen2_32_holder *holder;
	holder = (struct funopen2_32_holder *)cookie;
	return (*holder->fh_writefn)(holder->fh_cookie, buf, num_bytes);
}

PRIVATE ATTR_SECTION(".text.crt.FILE.locked.utility") off64_t LIBKCALL
funopen2_32_seekfn(void *cookie, off64_t off, int whence) {
	struct funopen2_32_holder *holder;
	holder = (struct funopen2_32_holder *)cookie;
	return (off64_t)(*holder->fh_seekfn)(holder->fh_cookie, (off32_t)off, whence);
}

PRIVATE ATTR_SECTION(".text.crt.FILE.locked.utility") int LIBKCALL
funopen2_32_flushfn(void *cookie) {
	struct funopen2_32_holder *holder;
	holder = (struct funopen2_32_holder *)cookie;
	return (*holder->fh_flushfn)(holder->fh_cookie);
}

PRIVATE ATTR_SECTION(".text.crt.FILE.locked.utility") int LIBKCALL
funopen2_32_closefn(void *cookie) {
	int result = 0;
	struct funopen2_32_holder *holder;
	holder = (struct funopen2_32_holder *)cookie;
	if (holder->fh_closefn)
		result = (*holder->fh_closefn)(holder->fh_cookie);
	free(holder);
	return result;
}
#endif /* __SIZEOF_OFF64_T__ != __SIZEOF_OFF32_T__ */

/*[[[head:libc_funopen2,hash:CRC-32=0x556facc1]]]*/
/* >> funopen2(3), funopen2_64(3) */
INTERN ATTR_SECTION(".text.crt.FILE.locked.utility") WUNUSED FILE *
NOTHROW_NCX(LIBCCALL libc_funopen2)(void const *cookie,
                                    ssize_t (LIBKCALL *readfn)(void *cookie, void *buf, size_t num_bytes),
                                    ssize_t (LIBKCALL *writefn)(void *cookie, void const *buf, size_t num_bytes),
                                    off_t (LIBKCALL *seekfn)(void *cookie, off_t off, int whence),
                                    int (LIBKCALL *flushfn)(void *cookie),
                                    int (LIBKCALL *closefn)(void *cookie))
/*[[[body:libc_funopen2]]]*/
{
#if __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
	return fp_funopen(cookie, readfn, writefn, seekfn, flushfn, closefn);
#else /* __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__ */
	FILE *result;
	struct funopen2_32_holder *holder;
	if (!seekfn) {
		result = fp_funopen(cookie, readfn, writefn, NULL, flushfn, closefn);
	} else {
		/* Need a custom wrapper for `seekfn'! */
		holder = (struct funopen2_32_holder *)malloc(sizeof(struct funopen2_32_holder));
		if unlikely(!holder)
			return NULL;
		holder->fh_cookie  = (void *)cookie;
		holder->fh_readfn  = readfn;
		holder->fh_writefn = writefn;
		holder->fh_seekfn  = seekfn;
		holder->fh_flushfn = flushfn;

		/* Open the actual file. */
		result = fp_funopen(/* cookie:  */ holder,
		                    /* readfn:  */ readfn ? &funopen2_32_readfn : NULL,
		                    /* writefn: */ writefn ? &funopen2_32_writefn : NULL,
		                    /* seekfn:  */ seekfn ? &funopen2_32_seekfn : NULL,
		                    /* flushfn: */ flushfn ? &funopen2_32_flushfn : NULL,
		                    /* closefn: */ closefn ? &funopen2_32_closefn : NULL);
		if unlikely(!result)
			free(holder);
	}
	return result;
#endif /* __SIZEOF_OFF64_T__ != __SIZEOF_OFF32_T__ */
}
/*[[[end:libc_funopen2]]]*/

/*[[[head:libc_funopen2_64,hash:CRC-32=0xfcfc6428]]]*/
#if __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
DEFINE_INTERN_ALIAS(libc_funopen2_64, libc_funopen2);
#else /* MAGIC:alias */
/* >> funopen2(3), funopen2_64(3) */
INTERN ATTR_SECTION(".text.crt.FILE.locked.utility") WUNUSED FILE *
NOTHROW_NCX(LIBCCALL libc_funopen2_64)(void const *cookie,
                                       ssize_t (LIBKCALL *readfn)(void *cookie, void *buf, size_t num_bytes),
                                       ssize_t (LIBKCALL *writefn)(void *cookie, void const *buf, size_t num_bytes),
                                       off64_t (LIBKCALL *seekfn)(void *cookie, off64_t off, int whence),
                                       int (LIBKCALL *flushfn)(void *cookie),
                                       int (LIBKCALL *closefn)(void *cookie))
/*[[[body:libc_funopen2_64]]]*/
{
	FILE *result;
	result = fp_funopen(cookie, readfn, writefn, seekfn, flushfn, closefn);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:libc_funopen2_64]]]*/





/* Structure pointed-to by `if_exdata' of files opened with `popen(3)' */
struct iofile_data_popen: iofile_data_novtab {
	pid_t iop_pid; /* [const] PID of the child process. */
};

struct popen_execve_args {
	char const  *pxa_path; /* [1..1] Path of program to exec */
	char *const *pxa_argv; /* [1..1][0..n] Arguments to pass to program */
	char *const *pxa_envp; /* [1..1][0..n] Environ to pass to program */
};


/* GCC doesn't like the way we use vfork(), when in fact it's perfectly valid
 * GCC simply doesn't understand that vfork() returns `0' the first time, and
 * only returns non-0 the second time around.
 * >>> warning : variable 'child_override_fdvl' might be clobbered by 'longjmp' or 'vfork' [-Wclobbered]
 */
__pragma_GCC_diagnostic_push_ignored(Wclobbered)

#define LIBC_POPEN_COMMAND 0 /* arg: `[0..1] char const *command;' */
#define LIBC_POPEN_EXECVE  1 /* arg: `[1..1] struct popen_execve_args *args;' */
PRIVATE ATTR_SECTION(".text.crt.FILE.utility.popen") WUNUSED NONNULL((1)) FILE *
NOTHROW_RPC(LIBCCALL libc_popen_impl)(char const *modes, unsigned int how, void *arg) {
	FILE *result;
	struct iofile_data_popen *ex;
	uint32_t flags;
	oflag_t oflags;
	fd_t pipefds[2];
	fd_t child_override_fdno; /* One of `STD*_FILENO' to override in the child process */
	fd_t child_override_fdvl; /* The FD with which to override `child_override_fdno' */
	pid_t cpid;

	/* Parse open flags. */
	flags = file_evalmodes(modes, &oflags);
	if unlikely((oflags & O_ACCMODE) == O_RDWR) {
		/* Even though it could be done (by use of 4 pipe files), the
		 * standard  doesn't  allow for  bi-directional communication
		 * with processes opened via popen(3)...
		 *
		 * Maybe one day this will be implemented as a KOS extension... */
		(void)libc_seterrno(EINVAL);
		return NULL;
	}

	/* Allocate the FILE object. */
	result = file_calloc(sizeof(struct iofile_data_popen));
	if unlikely(!result)
		goto done;

	/* Initialize generate FILE fields. */
	ex = (struct iofile_data_popen *)(result + 1);
	result->if_exdata = (struct iofile_data *)ex;
	assert(ex->io_getln == NULL);
	shared_recursive_rwlock_cinit(&ex->io_lock);
	assert(ex->io_zero == 0);
	ex->io_refcnt   = 1;
	result->if_flag = flags;

	/* Allocate the pipe pair that's going to be used. */
	if unlikely(pipe2(pipefds, oflags & (O_CLOEXEC | O_CLOFORK | O_NONBLOCK | O_DIRECT)))
		goto err_r;

	/* Select pipe fds that shall be used for overwrite operations. */
	if ((oflags & O_ACCMODE) != O_RDONLY) {
		/* Write to child process */
		child_override_fdno = STDIN_FILENO;
		child_override_fdvl = pipefds[0];
		result->if_fd       = pipefds[1];
	} else {
		/* Read from child process */
		child_override_fdno = STDOUT_FILENO;
		child_override_fdvl = pipefds[1];
		result->if_fd       = pipefds[0];
	}

	/* Spawn child process */
	COMPILER_BARRIER();
	cpid = vfork();
	COMPILER_BARRIER();
	if (cpid == 0) {
		/* In child process! */

		/* Override file descriptors. */
		if (child_override_fdvl != child_override_fdno)
			sys_dup2(child_override_fdvl, child_override_fdno);

		/* Don't keep the parent-process pipe end open.
		 * Note that when `O_CLOEXEC' was set, the exec
		 * below will automatically close the file! */
		if (!(oflags & O_CLOEXEC)) {
			sys_close(result->if_fd);
			if (child_override_fdvl != child_override_fdno)
				sys_close(child_override_fdvl);
		}

		/* Run another program. */
		switch (how) {

		case LIBC_POPEN_COMMAND:
			shexec((char const *)arg);
			break;

		case LIBC_POPEN_EXECVE: {
			struct popen_execve_args *args;
			args = (struct popen_execve_args *)arg;
			execve(args->pxa_path, args->pxa_argv, args->pxa_envp);
		}	break;

		default: __builtin_unreachable();
		}
		_exit(127);
	}
	COMPILER_BARRIER();

	/* Check if vfork() may have failed. */
	if unlikely(cpid == -1) {
		sys_close(pipefds[0]);
		sys_close(pipefds[1]);
		goto err_r;
	}

	/* Remember the PID of the child process */
	ex->iop_pid = cpid;

	/* Insert the new file stream into the global list of them. */
	allfiles_insert(result);
done:
	result = file_touser_opt(result);
	return result;
err_r:
	file_free(result);
	return NULL;
}

__pragma_GCC_diagnostic_pop_ignored(Wclobbered)




/*[[[head:libc_popen,hash:CRC-32=0x6b9b5f4f]]]*/
/* >> popen(3)
 * Open and return a new process I/O stream for executing `command'
 * @param: command: The command to execute (s.a. `shexec(3)')
 * @param: modes:   One of "r", "w", "re" or "we" ('e' sets  O_CLOEXEC
 *                  for the internal file descriptor within the parent
 *                  process) */
INTERN ATTR_SECTION(".text.crt.FILE.utility.popen") WUNUSED ATTR_IN(2) ATTR_IN_OPT(1) FILE *
NOTHROW_RPC(LIBCCALL libc_popen)(char const *command,
                                 char const *modes)
/*[[[body:libc_popen]]]*/
{
	return libc_popen_impl(modes, LIBC_POPEN_COMMAND, (void *)command);
}
/*[[[end:libc_popen]]]*/

/*[[[head:libc_popenve,hash:CRC-32=0xe2946668]]]*/
/* >> popenve(3)
 * Similar to `popen(3)', but rather than running `shexec(command)', this
 * function will `execve(path, argv, envp)'. The returned FILE must still
 * be closed using `pclose(3)', rather than `fclose(3)' */
INTERN ATTR_SECTION(".text.crt.FILE.utility.popen") WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) ATTR_IN(4) FILE *
NOTHROW_RPC(LIBCCALL libc_popenve)(char const *path,
                                   __TARGV,
                                   __TENVP,
                                   char const *modes)
/*[[[body:libc_popenve]]]*/
{
	struct popen_execve_args args;
	args.pxa_path = path;
	args.pxa_argv = ___argv;
	args.pxa_envp = ___envp;
	return libc_popen_impl(modes, LIBC_POPEN_EXECVE, &args);
}
/*[[[end:libc_popenve]]]*/

/*[[[head:libc_pclose,hash:CRC-32=0x2319830f]]]*/
/* >> pclose(3)
 * Close a process I/O file `stream' (s.a. `popen(3)') */
INTERN ATTR_SECTION(".text.crt.FILE.utility.popen") int
NOTHROW_NCX(LIBCCALL libc_pclose)(FILE *stream)
/*[[[body:libc_pclose]]]*/
{
	int result;
	struct iofile_data_popen *ex;
	if unlikely(!stream)
		return libc_seterrno(EINVAL);
	stream = file_fromuser(stream);
	ex     = (struct iofile_data_popen *)stream->if_exdata;

	/* Flush any unwritten data (in case `popen(..., "w")' was used) */
	result = file_sync(stream);
	if (result != 0)
		return result;

	/* Close  our end of the pipe. --  If the other process is currently
	 * doing a blocking read/write with their end of the pipe, then this
	 * will  cause that operation to be interrupted and indicate EOF (by
	 * read(2) or write(2) returning `0'). */
	if (stream->if_fd >= 0) {
		sys_close(stream->if_fd);
		stream->if_fd = -1; /* Don't try to close again in `file_destroy()' */
	}

	/* Wait for the child process to exit. */
	result = 0;
	for (;;) {
		pid_t error;
		error = waitpid(ex->iop_pid, &result, 0);
		if (error == ex->iop_pid)
			break;
		if (error >= 0)
			continue; /* Some other process??? */
		if unlikely(libc_geterrno() != EINTR) {
			/* This right here is a real problem with how this API is  designed:
			 * If another thread is using `wait(2)' and reaped our child process
			 * before  we were able to join it  (and read its exit status), then
			 * us trying to waitpid() for it will fail with `ECHILD', and  we'll
			 * never be able to ever retrieve the exit status again.
			 *
			 * The solution to  this problem is  for multi-threaded programs  to
			 * never make use  of `wait(2)'  (for the obvious  reason that  they
			 * might accidentally reap child processes spawned by other threads) */
			return -1;
		}
	}

	/* Destroy the file stream object. */
	decref(stream);

	/* Return the wait status (yes: status; not exit-code). */
	return result;
}
/*[[[end:libc_pclose]]]*/





/*[[[head:libc_fputc,hash:CRC-32=0xbc375bfe]]]*/
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.putc") ATTR_INOUT(2) int
(LIBCCALL libc_fputc)(int ch,
                      FILE *__restrict stream) THROWS(...)
/*[[[body:libc_fputc]]]*/
{
	unsigned char chr = (unsigned char)ch;
	return fwrite(&chr, sizeof(chr), 1, stream) ? ch : EOF;
}
/*[[[end:libc_fputc]]]*/

/*[[[head:libc_fputc_unlocked,hash:CRC-32=0x68194c72]]]*/
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.putc") ATTR_INOUT(2) int
(LIBCCALL libc_fputc_unlocked)(int ch,
                               FILE *__restrict stream) THROWS(...)
/*[[[body:libc_fputc_unlocked]]]*/
{
	unsigned char chr = (unsigned char)ch;
	return fwrite_unlocked(&chr, sizeof(chr), 1, stream) ? ch : EOF;
}
/*[[[end:libc_fputc_unlocked]]]*/







/*[[[head:libc_fgetc,hash:CRC-32=0xa8c345cf]]]*/
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.getc") ATTR_INOUT(1) int
(LIBCCALL libc_fgetc)(FILE *__restrict stream) THROWS(...)
/*[[[body:libc_fgetc]]]*/
{
	int result;
	if unlikely(!stream)
		return libc_seterrno_and_return_EOF(EINVAL);
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		result = file_getc(stream);
		file_lock_endwrite(stream);
	} else {
		result = file_getc(stream);
	}
	return result;
}
/*[[[end:libc_fgetc]]]*/

/*[[[head:libc_fgetc_unlocked,hash:CRC-32=0xda610c90]]]*/
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.getc") ATTR_INOUT(1) int
(LIBCCALL libc_fgetc_unlocked)(FILE *__restrict stream) THROWS(...)
/*[[[body:libc_fgetc_unlocked]]]*/
{
	int result;
	if unlikely(!stream)
		return libc_seterrno_and_return_EOF(EINVAL);
	stream = file_fromuser(stream);
	result = file_getc(stream);
	return result;
}
/*[[[end:libc_fgetc_unlocked]]]*/


/*[[[head:libc_fcloseall,hash:CRC-32=0x35bbcabc]]]*/
/* >> fcloseall(3)
 * Close all opened files */
INTERN ATTR_SECTION(".text.crt.dos.FILE.utility") int
(LIBCCALL libc_fcloseall)(void) THROWS(...)
/*[[[body:libc_fcloseall]]]*/
{
	int result = 0;
	FILE *fp;
again:
	all_files_write();
	LIST_FOREACH (fp, &all_files, if_exdata->io_link) {
		if (!tryincref(fp))
			continue;
		LIST_UNBIND(fp, if_exdata->io_link);
		all_files_endwrite();
		/* !!!WARNING!!!
		 * This is entirely unsafe, but if you think about it:
		 * This  function could only  ever be entirely unsafe! */
		atomic_write(&fp->if_exdata->io_refcnt, 1);
		decref(fp);
		++result;
		goto again;
	}
	all_files_endwrite();
	return result;
}
/*[[[end:libc_fcloseall]]]*/


/*[[[impl:libc__filbuf]]]*/
/*[[[impl:libc__flsbuf]]]*/
DEFINE_INTERN_ALIAS(libc__filbuf, libc_fgetc_unlocked);
DEFINE_INTERN_ALIAS(libc__flsbuf, libc_fputc_unlocked);


/*[[[head:libc_tmpnam,hash:CRC-32=0xbb61fce5]]]*/
/* >> tmpnam(3), tmpnam_r(3) */
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED ATTR_OUT(1) char *
NOTHROW_NCX(LIBCCALL libc_tmpnam)(char *buf)
/*[[[body:libc_tmpnam]]]*/
/*AUTO*/{
	(void)buf;
	CRT_UNIMPLEMENTEDF("tmpnam(buf: %q)", buf); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_tmpnam]]]*/

/*[[[head:libd_tmpnam,hash:CRC-32=0x24757967]]]*/
/* >> tmpnam(3), tmpnam_r(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED ATTR_OUT(1) char *
NOTHROW_NCX(LIBDCALL libd_tmpnam)(char *buf)
/*[[[body:libd_tmpnam]]]*/
/*AUTO*/{
	(void)buf;
	CRT_UNIMPLEMENTEDF("tmpnam(buf: %q)", buf); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd_tmpnam]]]*/

/*[[[head:libc_tempnam,hash:CRC-32=0x898712d2]]]*/
/* >> tempnam(3) */
INTERN ATTR_SECTION(".text.crt.fs.utility") ATTR_MALLOC WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_tempnam)(char const *dir,
                                   char const *pfx)
/*[[[body:libc_tempnam]]]*/
/*AUTO*/{
	(void)dir;
	(void)pfx;
	CRT_UNIMPLEMENTEDF("tempnam(dir: %q, pfx: %q)", dir, pfx); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_tempnam]]]*/

/*[[[head:libc_tmpfile,hash:CRC-32=0xe9ec4ee6]]]*/
/* >> tmpfile(3), tmpfile64(3)
 * Create and return a new file-stream for accessing a temporary file for reading/writing */
INTERN ATTR_SECTION(".text.crt.FILE.locked.access") WUNUSED FILE *
NOTHROW_RPC(LIBCCALL libc_tmpfile)(void)
/*[[[body:libc_tmpfile]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("tmpfile"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_tmpfile]]]*/

/*[[[impl:libc_tmpfile64]]]*/
DEFINE_INTERN_ALIAS(libc_tmpfile64, libc_tmpfile);

/*[[[head:libc__rmtmp,hash:CRC-32=0xbda88955]]]*/
INTERN ATTR_SECTION(".text.crt.dos.FILE.utility") int
NOTHROW_RPC(LIBCCALL libc__rmtmp)(void)
/*[[[body:libc__rmtmp]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_rmtmp"); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc__rmtmp]]]*/

/*[[[head:libc__get_output_format,hash:CRC-32=0x399b2fa1]]]*/
INTERN ATTR_SECTION(".text.crt.dos.FILE.utility") WUNUSED uint32_t
NOTHROW_NCX(LIBCCALL libc__get_output_format)(void)
/*[[[body:libc__get_output_format]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_get_output_format"); /* TODO */
	return (uint32_t)libc_seterrno(ENOSYS);
}
/*[[[end:libc__get_output_format]]]*/

/*[[[head:libc__set_output_format,hash:CRC-32=0x79b641ad]]]*/
INTERN ATTR_SECTION(".text.crt.dos.FILE.utility") uint32_t
NOTHROW_NCX(LIBCCALL libc__set_output_format)(uint32_t format)
/*[[[body:libc__set_output_format]]]*/
/*AUTO*/{
	(void)format;
	CRT_UNIMPLEMENTEDF("_set_output_format(format: %" PRIx32 ")", format); /* TODO */
	return (uint32_t)libc_seterrno(ENOSYS);
}
/*[[[end:libc__set_output_format]]]*/





/* When set to `true', '%n' cannot be used in format strings.
 *
 * NOTE: DOS specs state  that '%n' be  disabled by  default.
 *       However, since KOS is primarily a unix OS, we enable
 *       is  by default. But note that the PE loader will set
 *       it to disabled for the sake of compatibility! */
INTERN ATTR_SECTION(".bss.crt.dos.FILE.utility")
bool libc_printf_percent_n_disabled = false;

/*[[[head:libc__get_printf_count_output,hash:CRC-32=0x4adc1a8]]]*/
/* >> _get_printf_count_output(3), _set_printf_count_output(3)
 * Enable or disable use of '%n' in printf-style format strings. */
INTERN ATTR_SECTION(".text.crt.dos.FILE.utility") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__get_printf_count_output)(void)
/*[[[body:libc__get_printf_count_output]]]*/
{
	return atomic_read(&libc_printf_percent_n_disabled) ? 0 : 1;
}
/*[[[end:libc__get_printf_count_output]]]*/

/*[[[head:libc__set_printf_count_output,hash:CRC-32=0x35aa644e]]]*/
/* >> _get_printf_count_output(3), _set_printf_count_output(3)
 * Enable or disable use of '%n' in printf-style format strings. */
INTERN ATTR_SECTION(".text.crt.dos.FILE.utility") int
NOTHROW_NCX(LIBCCALL libc__set_printf_count_output)(int val)
/*[[[body:libc__set_printf_count_output]]]*/
{
	bool old_enabled;
	old_enabled = atomic_xch(&libc_printf_percent_n_disabled, val == 0);
	return old_enabled;
}
/*[[[end:libc__set_printf_count_output]]]*/

/*[[[head:libc_fdreopen,hash:CRC-32=0xbf34162d]]]*/
/* >> fdreopen(3), fdreopen_unlocked(3)
 * Re-open the given `stream' as a file-stream for accessing `fd' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.access") ATTR_IN(2) ATTR_INOUT(3) FILE *
NOTHROW_RPC(LIBCCALL libc_fdreopen)(fd_t fd,
                                    char const *__restrict modes,
                                    FILE *__restrict stream)
/*[[[body:libc_fdreopen]]]*/
{
	fd_t oldfd;
	(void)modes;
	if unlikely(!stream) {
		libc_seterrno(EINVAL);
		goto done;
	}
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream))
		file_lock_write(stream);
	oldfd = stream->if_fd;
	if unlikely(fd == oldfd) {
		if (FMUSTLOCK(stream))
			file_lock_endwrite(stream);
		libc_seterrno(EBADF);
		stream = NULL;
		goto done;
	}
	stream->if_fd   = fd;
	stream->if_flag = IO_LNIFTYY | IO_RW | (stream->if_flag & IO_NOLOCK);
	if (FMUSTLOCK(stream))
		file_lock_endwrite(stream);
	sys_close(oldfd);
	stream = file_touser(stream);
done:
	return stream;
}
/*[[[end:libc_fdreopen]]]*/

/*[[[head:libc_fdreopen_unlocked,hash:CRC-32=0xcfcc2964]]]*/
/* >> fdreopen(3), fdreopen_unlocked(3)
 * Re-open the given `stream' as a file-stream for accessing `fd' */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.access") ATTR_IN(2) ATTR_INOUT(3) FILE *
NOTHROW_RPC(LIBCCALL libc_fdreopen_unlocked)(fd_t fd,
                                             char const *__restrict modes,
                                             FILE *__restrict stream)
/*[[[body:libc_fdreopen_unlocked]]]*/
{
	fd_t oldfd;
	(void)modes;
	if unlikely(!stream) {
		libc_seterrno(EINVAL);
		goto done;
	}
	stream = file_fromuser(stream);
	oldfd  = stream->if_fd;
	if unlikely(fd == oldfd) {
		libc_seterrno(EBADF);
		stream = NULL;
		goto done;
	}
	stream->if_fd   = fd;
	stream->if_flag = IO_LNIFTYY | IO_RW;
	sys_close(oldfd);
	stream = file_touser(stream);
done:
	return stream;
}
/*[[[end:libc_fdreopen_unlocked]]]*/

/*[[[head:libd_freopen,hash:CRC-32=0x3737f42]]]*/
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.access") ATTR_IN(1) ATTR_IN(2) ATTR_INOUT(3) FILE *
NOTHROW_RPC(LIBDCALL libd_freopen)(char const *__restrict filename,
                                   char const *__restrict modes,
                                   FILE *__restrict stream)
/*[[[body:libd_freopen]]]*/
{
	fd_t fd;
	FILE *result;
	uint32_t flags;
	oflag_t oflags;
	flags = file_evalmodes(modes, &oflags);
	fd    = open(filename, oflags | libd_O_DOSPATH, 0644);
	if unlikely(fd < 0)
		return NULL;
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		result = file_reopenfd(stream, fd, flags);
		file_lock_endwrite(stream);
	} else {
		result = file_reopenfd(stream, fd, flags);
	}
	if likely(result) {
		result = file_touser(result);
	} else {
		sys_close(fd);
	}
	return result;
}
/*[[[end:libd_freopen]]]*/

/*[[[head:libc_freopen,hash:CRC-32=0xec0e8cdd]]]*/
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.access") ATTR_IN(1) ATTR_IN(2) ATTR_INOUT(3) FILE *
NOTHROW_RPC(LIBCCALL libc_freopen)(char const *__restrict filename,
                                   char const *__restrict modes,
                                   FILE *__restrict stream)
/*[[[body:libc_freopen]]]*/
{
	fd_t fd;
	FILE *result;
	uint32_t flags;
	oflag_t oflags;
	flags = file_evalmodes(modes, &oflags);
	fd    = open(filename, oflags, 0644);
	if unlikely(fd < 0)
		return NULL;
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		result = file_reopenfd(stream, fd, flags);
		file_lock_endwrite(stream);
	} else {
		result = file_reopenfd(stream, fd, flags);
	}
	if likely(result) {
		result = file_touser(result);
	} else {
		sys_close(fd);
	}
	return result;
}
/*[[[end:libc_freopen]]]*/

/*[[[head:libd_freopen_unlocked,hash:CRC-32=0xffae1309]]]*/
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.unlocked.access") ATTR_IN(1) ATTR_IN(2) ATTR_INOUT(3) FILE *
NOTHROW_RPC(LIBDCALL libd_freopen_unlocked)(char const *__restrict filename,
                                            char const *__restrict modes,
                                            FILE *__restrict stream)
/*[[[body:libd_freopen_unlocked]]]*/
{
	fd_t fd;
	FILE *result;
	uint32_t flags;
	oflag_t oflags;
	flags = file_evalmodes(modes, &oflags);
	fd    = open(filename, oflags | libd_O_DOSPATH, 0644);
	if unlikely(fd < 0)
		return NULL;
	stream = file_fromuser(stream);
	result = file_reopenfd(stream, fd, flags);
	if likely(result) {
		result = file_touser(result);
	} else {
		sys_close(fd);
	}
	return result;
}
/*[[[end:libd_freopen_unlocked]]]*/

/*[[[head:libc_freopen_unlocked,hash:CRC-32=0x74ebe71e]]]*/
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.access") ATTR_IN(1) ATTR_IN(2) ATTR_INOUT(3) FILE *
NOTHROW_RPC(LIBCCALL libc_freopen_unlocked)(char const *__restrict filename,
                                            char const *__restrict modes,
                                            FILE *__restrict stream)
/*[[[body:libc_freopen_unlocked]]]*/
{
	fd_t fd;
	FILE *result;
	uint32_t flags;
	oflag_t oflags;
	flags = file_evalmodes(modes, &oflags);
	fd    = open(filename, oflags, 0644);
	if unlikely(fd < 0)
		return NULL;
	stream = file_fromuser(stream);
	result = file_reopenfd(stream, fd, flags);
	if likely(result) {
		result = file_touser(result);
	} else {
		sys_close(fd);
	}
	return result;
}
/*[[[end:libc_freopen_unlocked]]]*/



/*[[[impl:libc_fopen64]]]*/
/*[[[impl:libc_freopen64]]]*/
/*[[[impl:libc_freopen64_unlocked]]]*/
DEFINE_INTERN_ALIAS(libc_freopen64, libc_freopen);
DEFINE_INTERN_ALIAS(libc_freopen64_unlocked, libc_freopen_unlocked);
DEFINE_INTERN_ALIAS(libc_fopen64, libc_fopen);

/*[[[impl:libd_fopen64]]]*/
/*[[[impl:libd_freopen64]]]*/
/*[[[impl:libd_freopen64_unlocked]]]*/
DEFINE_INTERN_ALIAS(libd_freopen64, libd_freopen);
DEFINE_INTERN_ALIAS(libd_freopen64_unlocked, libd_freopen_unlocked);
DEFINE_INTERN_ALIAS(libd_fopen64, libd_fopen);


#undef libc_feof_unlocked
#undef libc_ferror_unlocked
DEFINE_INTERN_ALIAS(libc_feof_unlocked, libc_feof);
DEFINE_INTERN_ALIAS(libc_ferror_unlocked, libc_ferror);





/*[[[start:exports,hash:CRC-32=0x1d8f4611]]]*/
DEFINE_PUBLIC_ALIAS(DOS$__rename, libd_rename);
DEFINE_PUBLIC_ALIAS(DOS$__libc_rename, libd_rename);
DEFINE_PUBLIC_ALIAS(DOS$rename, libd_rename);
DEFINE_PUBLIC_ALIAS(__rename, libc_rename);
DEFINE_PUBLIC_ALIAS(__libc_rename, libc_rename);
DEFINE_PUBLIC_ALIAS(rename, libc_rename);
DEFINE_PUBLIC_ALIAS(DOS$tmpnam, libd_tmpnam);
DEFINE_PUBLIC_ALIAS(tmpnam, libc_tmpnam);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_fclose_nolock, libc_fclose);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(_IO_fclose, libc_fclose);
DEFINE_PUBLIC_ALIAS(fclose, libc_fclose);
DEFINE_PUBLIC_ALIAS(fflush, libc_fflush);
DEFINE_PUBLIC_ALIAS(_IO_fflush, libc_fflush);
DEFINE_PUBLIC_ALIAS(_IO_sync, libc_fflush);
DEFINE_PUBLIC_ALIAS(setvbuf, libc_setvbuf);
DEFINE_PUBLIC_ALIAS(_IO_setvbuf, libc_setvbuf);
DEFINE_PUBLIC_ALIAS(getc, libc_fgetc);
DEFINE_PUBLIC_ALIAS(fgetc, libc_fgetc);
DEFINE_PUBLIC_ALIAS(_IO_getc, libc_fgetc);
DEFINE_PUBLIC_ALIAS(_IO_default_uflow, libc_fgetc);
DEFINE_PUBLIC_ALIAS(putc, libc_fputc);
DEFINE_PUBLIC_ALIAS(fputc, libc_fputc);
DEFINE_PUBLIC_ALIAS(_IO_putc, libc_fputc);
DEFINE_PUBLIC_ALIAS(ungetc, libc_ungetc);
DEFINE_PUBLIC_ALIAS(_IO_ungetc, libc_ungetc);
DEFINE_PUBLIC_ALIAS(fread, libc_fread);
DEFINE_PUBLIC_ALIAS(_IO_fread, libc_fread);
DEFINE_PUBLIC_ALIAS(fwrite, libc_fwrite);
DEFINE_PUBLIC_ALIAS(_IO_fwrite, libc_fwrite);
DEFINE_PUBLIC_ALIAS(fwrite_s, libc_fwrite);
DEFINE_PUBLIC_ALIAS(fseek, libc_fseek);
DEFINE_PUBLIC_ALIAS(ftell, libc_ftell);
DEFINE_PUBLIC_ALIAS(_IO_ftell, libc_ftell);
DEFINE_PUBLIC_ALIAS(rewind_unlocked, libc_rewind);
DEFINE_PUBLIC_ALIAS(rewind, libc_rewind);
DEFINE_PUBLIC_ALIAS(clearerr_unlocked, libc_clearerr);
DEFINE_PUBLIC_ALIAS(clearerr, libc_clearerr);
DEFINE_PUBLIC_ALIAS(_IO_feof, libc_feof);
DEFINE_PUBLIC_ALIAS(feof_unlocked, libc_feof);
DEFINE_PUBLIC_ALIAS(feof, libc_feof);
DEFINE_PUBLIC_ALIAS(_IO_ferror, libc_ferror);
DEFINE_PUBLIC_ALIAS(ferror_unlocked, libc_ferror);
DEFINE_PUBLIC_ALIAS(ferror, libc_ferror);
DEFINE_PUBLIC_ALIAS(tmpfile, libc_tmpfile);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fopen, libd_fopen);
DEFINE_PUBLIC_ALIAS(DOS$setmntent, libd_fopen);
DEFINE_PUBLIC_ALIAS(DOS$__setmntent, libd_fopen);
DEFINE_PUBLIC_ALIAS(DOS$fopen, libd_fopen);
DEFINE_PUBLIC_ALIAS(_IO_fopen, libc_fopen);
DEFINE_PUBLIC_ALIAS(setmntent, libc_fopen);
DEFINE_PUBLIC_ALIAS(__setmntent, libc_fopen);
DEFINE_PUBLIC_ALIAS(fopen, libc_fopen);
DEFINE_PUBLIC_ALIAS(DOS$freopen, libd_freopen);
DEFINE_PUBLIC_ALIAS(freopen, libc_freopen);
DEFINE_PUBLIC_ALIAS(fgetpos, libc_fgetpos);
DEFINE_PUBLIC_ALIAS(_IO_fgetpos, libc_fgetpos);
DEFINE_PUBLIC_ALIAS(fsetpos, libc_fsetpos);
DEFINE_PUBLIC_ALIAS(_IO_fsetpos, libc_fsetpos);
DEFINE_PUBLIC_ALIAS(DOS$renameat, libd_renameat);
DEFINE_PUBLIC_ALIAS(renameat, libc_renameat);
DEFINE_PUBLIC_ALIAS(DOS$renameat2, libd_renameat2);
DEFINE_PUBLIC_ALIAS(renameat2, libc_renameat2);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_fflush_nolock, libc_fflush_unlocked);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(fflush_unlocked, libc_fflush_unlocked);
DEFINE_PUBLIC_ALIAS(fread_unlocked, libc_fread_unlocked);
DEFINE_PUBLIC_ALIAS(_fread_nolock, libc_fread_unlocked);
DEFINE_PUBLIC_ALIAS(fwrite_unlocked, libc_fwrite_unlocked);
DEFINE_PUBLIC_ALIAS(_fwrite_nolock, libc_fwrite_unlocked);
DEFINE_PUBLIC_ALIAS(fgetc_unlocked, libc_fgetc_unlocked);
DEFINE_PUBLIC_ALIAS(getc_unlocked, libc_fgetc_unlocked);
DEFINE_PUBLIC_ALIAS(_getc_nolock, libc_fgetc_unlocked);
DEFINE_PUBLIC_ALIAS(_fgetc_nolock, libc_fgetc_unlocked);
DEFINE_PUBLIC_ALIAS(putc_unlocked, libc_fputc_unlocked);
DEFINE_PUBLIC_ALIAS(fputc_unlocked, libc_fputc_unlocked);
DEFINE_PUBLIC_ALIAS(_putc_nolock, libc_fputc_unlocked);
DEFINE_PUBLIC_ALIAS(_fputc_nolock, libc_fputc_unlocked);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_tempnam, libc_tempnam);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(tempnam, libc_tempnam);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_fdopen, libc_fdopen);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(_IO_fdopen, libc_fdopen);
DEFINE_PUBLIC_ALIAS(fdopen, libc_fdopen);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_fileno, libc_fileno);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(fileno_unlocked, libc_fileno);
DEFINE_PUBLIC_ALIAS(fileno, libc_fileno);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_lock_file, libc_flockfile);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(_IO_flockfile, libc_flockfile);
DEFINE_PUBLIC_ALIAS(flockfile, libc_flockfile);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_unlock_file, libc_funlockfile);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(_IO_funlockfile, libc_funlockfile);
DEFINE_PUBLIC_ALIAS(funlockfile, libc_funlockfile);
DEFINE_PUBLIC_ALIAS(_IO_ftrylockfile, libc_ftrylockfile);
DEFINE_PUBLIC_ALIAS(ftrylockfile, libc_ftrylockfile);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_popen, libc_popen);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(_IO_popen, libc_popen);
DEFINE_PUBLIC_ALIAS(popen, libc_popen);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_pclose, libc_pclose);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(pclose, libc_pclose);
DEFINE_PUBLIC_ALIAS(popenve, libc_popenve);
DEFINE_PUBLIC_ALIAS(_fcloseall, libc_fcloseall);
DEFINE_PUBLIC_ALIAS(fcloseall, libc_fcloseall);
DEFINE_PUBLIC_ALIAS(fseeko, libc_fseeko);
DEFINE_PUBLIC_ALIAS(ftello, libc_ftello);
DEFINE_PUBLIC_ALIAS(tmpfile64, libc_tmpfile64);
DEFINE_PUBLIC_ALIAS(fseeko64, libc_fseeko64);
DEFINE_PUBLIC_ALIAS(__fseeko64, libc_fseeko64);
DEFINE_PUBLIC_ALIAS(fseek64, libc_fseeko64);
DEFINE_PUBLIC_ALIAS(_fseeki64, libc_fseeko64);
DEFINE_PUBLIC_ALIAS(ftello64, libc_ftello64);
DEFINE_PUBLIC_ALIAS(__ftello64, libc_ftello64);
DEFINE_PUBLIC_ALIAS(ftell64, libc_ftello64);
DEFINE_PUBLIC_ALIAS(_ftelli64, libc_ftello64);
DEFINE_PUBLIC_ALIAS(DOS$fopen64, libd_fopen64);
DEFINE_PUBLIC_ALIAS(fopen64, libc_fopen64);
DEFINE_PUBLIC_ALIAS(DOS$freopen64, libd_freopen64);
DEFINE_PUBLIC_ALIAS(freopen64, libc_freopen64);
DEFINE_PUBLIC_ALIAS(fgetpos64, libc_fgetpos64);
DEFINE_PUBLIC_ALIAS(_IO_fgetpos64, libc_fgetpos64);
DEFINE_PUBLIC_ALIAS(fsetpos64, libc_fsetpos64);
DEFINE_PUBLIC_ALIAS(_IO_fsetpos64, libc_fsetpos64);
DEFINE_PUBLIC_ALIAS(file_printer, libc_file_printer);
DEFINE_PUBLIC_ALIAS(file_printer_unlocked, libc_file_printer_unlocked);
DEFINE_PUBLIC_ALIAS(fdreopen, libc_fdreopen);
DEFINE_PUBLIC_ALIAS(fdreopen_unlocked, libc_fdreopen_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$freopen_unlocked, libd_freopen_unlocked);
DEFINE_PUBLIC_ALIAS(freopen_unlocked, libc_freopen_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$freopen64_unlocked, libd_freopen64_unlocked);
DEFINE_PUBLIC_ALIAS(freopen64_unlocked, libc_freopen64_unlocked);
DEFINE_PUBLIC_ALIAS(fseek_unlocked, libc_fseek_unlocked);
DEFINE_PUBLIC_ALIAS(_fseek_nolock, libc_fseek_unlocked);
DEFINE_PUBLIC_ALIAS(ftell_unlocked, libc_ftell_unlocked);
DEFINE_PUBLIC_ALIAS(_ftell_nolock, libc_ftell_unlocked);
DEFINE_PUBLIC_ALIAS(fseeko_unlocked, libc_fseeko_unlocked);
DEFINE_PUBLIC_ALIAS(ftello_unlocked, libc_ftello_unlocked);
DEFINE_PUBLIC_ALIAS(flushall_unlocked, libc_flushall_unlocked);
DEFINE_PUBLIC_ALIAS(fgetpos_unlocked, libc_fgetpos_unlocked);
DEFINE_PUBLIC_ALIAS(fsetpos_unlocked, libc_fsetpos_unlocked);
DEFINE_PUBLIC_ALIAS(setvbuf_unlocked, libc_setvbuf_unlocked);
DEFINE_PUBLIC_ALIAS(ungetc_unlocked, libc_ungetc_unlocked);
DEFINE_PUBLIC_ALIAS(_ungetc_nolock, libc_ungetc_unlocked);
DEFINE_PUBLIC_ALIAS(rewind_unlocked, libc_rewind_unlocked);
DEFINE_PUBLIC_ALIAS(fisatty, libc_fisatty);
DEFINE_PUBLIC_ALIAS(fftruncate, libc_fftruncate);
DEFINE_PUBLIC_ALIAS(fftruncate_unlocked, libc_fftruncate_unlocked);
DEFINE_PUBLIC_ALIAS(fseeko64_unlocked, libc_fseeko64_unlocked);
DEFINE_PUBLIC_ALIAS(fseek64_unlocked, libc_fseeko64_unlocked);
DEFINE_PUBLIC_ALIAS(_fseeki64_nolock, libc_fseeko64_unlocked);
DEFINE_PUBLIC_ALIAS(ftello64_unlocked, libc_ftello64_unlocked);
DEFINE_PUBLIC_ALIAS(ftell64_unlocked, libc_ftello64_unlocked);
DEFINE_PUBLIC_ALIAS(_ftelli64_nolock, libc_ftello64_unlocked);
DEFINE_PUBLIC_ALIAS(fgetpos64_unlocked, libc_fgetpos64_unlocked);
DEFINE_PUBLIC_ALIAS(fsetpos64_unlocked, libc_fsetpos64_unlocked);
DEFINE_PUBLIC_ALIAS(fftruncate64, libc_fftruncate64);
DEFINE_PUBLIC_ALIAS(fftruncate64_unlocked, libc_fftruncate64_unlocked);
DEFINE_PUBLIC_ALIAS(fgetln, libc_fgetln);
DEFINE_PUBLIC_ALIAS(funopen2, libc_funopen2);
DEFINE_PUBLIC_ALIAS(funopen2_64, libc_funopen2_64);
DEFINE_PUBLIC_ALIAS(_flushall, libc__flushall);
DEFINE_PUBLIC_ALIAS(_IO_flush_all, libc__flushall);
DEFINE_PUBLIC_ALIAS(_IO_cleanup, libc__flushall);
DEFINE_PUBLIC_ALIAS(_rmtmp, libc__rmtmp);
DEFINE_PUBLIC_ALIAS(__uflow, libc__filbuf);
DEFINE_PUBLIC_ALIAS(__underflow, libc__filbuf);
DEFINE_PUBLIC_ALIAS(__srget, libc__filbuf);
DEFINE_PUBLIC_ALIAS(_filbuf, libc__filbuf);
DEFINE_PUBLIC_ALIAS(__swbuf, libc__flsbuf);
DEFINE_PUBLIC_ALIAS(_flsbuf, libc__flsbuf);
DEFINE_PUBLIC_ALIAS(_get_printf_count_output, libc__get_printf_count_output);
DEFINE_PUBLIC_ALIAS(_set_printf_count_output, libc__set_printf_count_output);
DEFINE_PUBLIC_ALIAS(_get_output_format, libc__get_output_format);
DEFINE_PUBLIC_ALIAS(_set_output_format, libc__set_output_format);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_STDIO_C */
