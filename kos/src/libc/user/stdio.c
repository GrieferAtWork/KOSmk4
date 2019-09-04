/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_STDIO_C
#define GUARD_LIBC_USER_STDIO_C 1

#include "../api.h"
#include "stdio.h"
#include "malloc.h"
#include "format-printer.h"

#include <bits/io-file.h>
#include <fcntl.h>
#include <format-printer.h>
#include <kos/syscalls.h>
#include <limits.h>
#include <malloc.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <assert.h>
#include <unistd.h>
#include <pwd.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sync/atomic-owner-rwlock.h>
#include <hybrid/sync/atomic-rwlock.h>

DECL_BEGIN

#define libc__vscanf_s_l    libc__vscanf_l
#define libc__vprintf_s_l   libc__vprintf_l
#define libc__vfprintf_s_l  libc__vfprintf_l
#define libc_format_printf  format_printf
#define libc_format_vprintf format_vprintf

#define IO_R       __IO_FILE_IOR       /* The current buffer was read from disk (Undefined when 'if_cnt == 0'). */
#define IO_W       __IO_FILE_IOW       /* The current buffer has changed since being read. */
#define IO_NBF     __IO_FILE_IONBF     /* ??? */
#define IO_MALLBUF __IO_FILE_IOMALLBUF /* The buffer was allocated internally. */
#define IO_EOF     __IO_FILE_IOEOF     /* Set when the file pointed to by 'if_fd' has been exhausted. */
#define IO_ERR     __IO_FILE_IOERR     /* Set when an I/O error occurred. */
#define IO_NOFD    __IO_FILE_IONOFD    /* The file acts as output to buffer only. - 'if_fd' is not valid. (Currently ignored when loading/flushing data) */
#define IO_RW      __IO_FILE_IORW      /* The file was opened for read+write permissions ('+' flag) */
#define IO_USERBUF __IO_FILE_IOUSERBUF /* The buffer was given by the user. */
#define IO_LNBUF   __IO_FILE_IOLNBUF   /* NOT ORIGINALLY DEFINED IN DOS: Use line-buffering. */
#define IO_SETVBUF __IO_FILE_IOSETVBUF /* ??? */
#define IO_FEOF    __IO_FILE_IOFEOF    /* Never used */
#define IO_FLRTN   __IO_FILE_IOFLRTN   /* ??? */
#define IO_CTRLZ   __IO_FILE_IOCTRLZ   /* ??? */
#define IO_COMMIT  __IO_FILE_IOCOMMIT  /* ??? */
#define IO_LOCKED  __IO_FILE_IOLOCKED  /* ??? */
#define IO_LNIFTYY __IO_FILE_IOLNIFTYY /* NOT ORIGINALLY DEFINED IN DOS: Determine 'isatty()' on first access and set `__IO_FILE_IOLNBUF' accordingly. */

struct iofile_data {
	uintptr_t                  io_zero; /* Always ZERO(0). - Required for binary compatibility with DOS. */
	struct atomic_owner_rwlock io_lock; /* Lock for the file. */
	pos64_t                    io_pos;  /* The current in-file position of 'if_fd' */
	size_t                     io_read; /* The amount of bytes within the currently loaded buffer that were read from disk.
	                                     * When `IO_R' is set, `io_pos' is located within the buffer at 'if_base+io_read' */
	LLIST_NODE(FILE)           io_link; /* [lock(libc_ffiles_lock)][0..1] Entry in the global chain of open files. (Used by `fcloseall()', as well as flushing all open files during `exit()') */
	LLIST_NODE(FILE)           io_lnch; /* [lock(libc_flnchg_lock)][0..1] Chain of line-buffered file that have changed and must be flushed before another line-buffered file is read.
	                                     * NOTE: The standard streams stdin, stdout and stderr are not apart of this list! */
	//mbstate_t                io_mbs;  /* MB State used for translating unicode data. */
};


PRIVATE ATTR_SECTION(".data.crt.FILE.locked.read.read.io_stdin") struct iofile_data io_stdin = {
	/* .io_zero = */0,
	/* .io_lock = */ATOMIC_OWNER_RWLOCK_INIT,
	/* .io_pos  = */0,
	/* .io_read = */0,
	/* .io_link = */LLIST_INITNODE,
	/* .io_lnch = */LLIST_INITNODE,
};
PRIVATE ATTR_SECTION(".data.crt.FILE.locked.write.write.io_stdout") struct iofile_data io_stdout = {
	/* .io_zero = */0,
	/* .io_lock = */ATOMIC_OWNER_RWLOCK_INIT,
	/* .io_pos  = */0,
	/* .io_read = */0,
	/* .io_link = */LLIST_INITNODE,
	/* .io_lnch = */LLIST_INITNODE,
};
PRIVATE ATTR_SECTION(".data.crt.FILE.locked.write.write.io_stderr") struct iofile_data io_stderr = {
	/* .io_zero = */0,
	/* .io_lock = */ATOMIC_OWNER_RWLOCK_INIT,
	/* .io_pos  = */0,
	/* .io_read = */0,
	/* .io_link = */LLIST_INITNODE,
	/* .io_lnch = */LLIST_INITNODE,
};

INTERN ATTR_SECTION(".data.crt.FILE.locked.utility.std_files") FILE libc_std_files[3] = {
	/* [0] = */__IO_FILE_INIT(NULL,0,NULL,IO_LNBUF,STDIN_FILENO,{0},0,&io_stdin),
#if 0
	/* [1] = */__IO_FILE_INIT(NULL,0,NULL,IO_USERBUF,STDIN_FILENO,{0},0,&io_stdout),
	/* [2] = */__IO_FILE_INIT(NULL,0,NULL,IO_USERBUF,STDIN_FILENO,{0},0,&io_stderr),
#else
	/* [1] = */__IO_FILE_INIT(NULL,0,NULL,IO_LNIFTYY,STDIN_FILENO,{0},0,&io_stdout),
	/* [2] = */__IO_FILE_INIT(NULL,0,NULL,IO_LNIFTYY,STDIN_FILENO,{0},0,&io_stderr),
#endif
};

#undef stdin
#undef stdout
#undef stderr
PUBLIC ATTR_SECTION(".data.crt.FILE.locked.read.read.stdin") FILE *stdin  = &libc_std_files[0];
PUBLIC ATTR_SECTION(".data.crt.FILE.locked.write.write.stdout") FILE *stdout = &libc_std_files[1];
PUBLIC ATTR_SECTION(".data.crt.FILE.locked.write.write.stderr") FILE *stderr = &libc_std_files[2];

DEFINE_NOREL_GLOBAL_META(FILE *, stdin, ".crt.FILE.locked.read.read.stdin");
DEFINE_NOREL_GLOBAL_META(FILE *, stdout, ".crt.FILE.locked.write.write.stdout");
DEFINE_NOREL_GLOBAL_META(FILE *, stderr, ".crt.FILE.locked.write.write.stderr");
#define stdin  GET_NOREL_GLOBAL(stdin)
#define stdout GET_NOREL_GLOBAL(stdout)
#define stderr GET_NOREL_GLOBAL(stderr)


INTERN DEFINE_ATOMIC_RWLOCK(libc_ffiles_lock);
INTERN DEFINE_ATOMIC_RWLOCK(libc_flnchg_lock);
INTERN LLIST(FILE) libc_ffiles = LLIST_INIT;
INTERN LLIST(FILE) libc_flnchg = LLIST_INIT;

#define FEOF(self)      ((self)->if_flag&IO_EOF)
#define FERROR(self)    ((self)->if_flag&IO_ERR)
#define FSETERROR(self) ((self)->if_flag|=IO_ERR)
#define FCLEARERR(self) ((self)->if_flag&=~IO_ERR)

#define IOBUF_MAX                8192
#define IOBUF_MIN                512
#define IOBUF_RELOCATE_THRESHOLD 2048 /* When >= this amount of bytes are unused in the buffer, free them. */


#define file_reading(x)     atomic_owner_rwlock_reading(&(x)->if_exdata->io_lock)
#define file_writing(x)     atomic_owner_rwlock_writing(&(x)->if_exdata->io_lock)
#define file_tryread(x)     atomic_owner_rwlock_tryread(&(x)->if_exdata->io_lock)
#define file_trywrite(x)    atomic_owner_rwlock_trywrite(&(x)->if_exdata->io_lock)
#define file_tryupgrade(x)  atomic_owner_rwlock_tryupgrade(&(x)->if_exdata->io_lock)
#define file_read(x)        atomic_owner_rwlock_read(&(x)->if_exdata->io_lock)
#define file_write(x)       atomic_owner_rwlock_write(&(x)->if_exdata->io_lock)
#define file_upgrade(x)     atomic_owner_rwlock_upgrade(&(x)->if_exdata->io_lock)
#define file_downgrade(x)   atomic_owner_rwlock_downgrade(&(x)->if_exdata->io_lock)
#define file_endread(x)     atomic_owner_rwlock_endread(&(x)->if_exdata->io_lock)
#define file_endwrite(x)    atomic_owner_rwlock_endwrite(&(x)->if_exdata->io_lock)

#if 0
/* Lockless */
#undef file_reading
#undef file_writing
#undef file_tryread
#undef file_trywrite
#undef file_tryupgrade
#undef file_read
#undef file_write
#undef file_upgrade
#undef file_downgrade
#undef file_endread
#undef file_endwrite
#define file_reading(x)           1
#define file_writing(x)           1
#define file_tryread(x)           1
#define file_trywrite(x)          1
#define file_tryupgrade(x)        1
#define file_read(x)        (void)0
#define file_write(x)       (void)0
#define file_upgrade(x)     (void)0
#define file_downgrade(x)   (void)0
#define file_endread(x)     (void)0
#define file_endwrite(x)    (void)0
#endif


/* Low-level read/write/seek/tell implementation. */
INTDEF size_t NOTHROW_NCX(LIBCCALL libc_fdoread)(void *__restrict buf, size_t size, FILE *__restrict self);
INTDEF size_t NOTHROW_NCX(LIBCCALL libc_fdowrite)(void const *__restrict buf, size_t size, FILE *__restrict self);
INTDEF int NOTHROW_NCX(LIBCCALL libc_fdoflush)(FILE *__restrict self);
INTDEF pos64_t NOTHROW_NCX(LIBCCALL libc_fdotell)(FILE *__restrict self);
INTDEF int NOTHROW_NCX(LIBCCALL libc_fdoseek)(FILE *__restrict self, off64_t off, int whence);
INTDEF int NOTHROW_NCX(LIBCCALL libc_dosetvbuf)(FILE *__restrict self, char *__restrict buf, int modes, size_t n);
INTDEF int NOTHROW_NCX(LIBCCALL libc_doungetc)(int c, FILE *__restrict self);
/* Try to fill unused buffer memory with new data, allocating a new buffer if none was available before. */
INTDEF int NOTHROW_NCX(LIBCCALL libc_doffill)(FILE *__restrict self);

/* Flush all line-buffered file streams that have changed.
 * This function is called before data is read from a
 * line-buffered source 'sender' that is already write-locked. */
INTDEF void NOTHROW_NCX(LIBCCALL libc_flush_changed_lnbuf_files)(FILE *__restrict sender);

/* All all user-defined input streams, not including stdin, stdout or stderr.
 * NOTE: Errors that may occur during this act are ignored, so-as to
 *       ensure that attempts at flushing later files are always made. */
INTDEF void NOTHROW_NCX(LIBCCALL libc_flushall_nostd)(void);
/* Same as `libc_flushall_nostd', but also flush standard streams. */
//INTDEF void LIBCCALL libc_flushall(void);







/*  */



INTERN void LIBCCALL
libc_flush_changed_lnbuf_files(FILE *__restrict sender) {
	while (ATOMIC_READ(libc_flnchg)) {
		FILE *flush_file;
		atomic_rwlock_read(&libc_flnchg_lock);
		COMPILER_READ_BARRIER();
		if (!libc_flnchg) {
			atomic_rwlock_endread(&libc_flnchg_lock);
			break;
		}
		if (!atomic_rwlock_upgrade(&libc_flnchg_lock) &&
		    !ATOMIC_READ(libc_flnchg)) {
			atomic_rwlock_endwrite(&libc_flnchg_lock);
			break;
		}
		flush_file = libc_flnchg;
		if (flush_file != sender && !file_trywrite(flush_file)) {
			atomic_rwlock_endwrite(&libc_flnchg_lock);
			continue;
		}
		/* Unlink the file from the list of changed streams. */
		LLIST_UNLINK(flush_file, if_exdata->io_lnch);
		atomic_rwlock_endwrite(&libc_flnchg_lock);
		/* Flush the file. */
		libc_fdoflush(flush_file);
		if (flush_file != sender)
			file_endwrite(flush_file);
	}
}

LOCAL void LIBCCALL
libc_fchecktty(FILE *__restrict self) {
	if (self->if_flag & IO_LNIFTYY) {
		self->if_flag &= ~IO_LNIFTYY;
		if (isatty(self->if_fd)) {
			syslog(LOG_DEBUG, "[LIBC] Stream handle %d is a tty\n", self->if_fd);
			self->if_flag |= IO_LNBUF;
		}
	}
}


INTERN size_t LIBCCALL
libc_fdoread(void *__restrict buf, size_t size, FILE *__restrict self) {
	size_t result, part, minsize;
	unsigned char *buffer;
	ssize_t temp;

	/* Read data from the loaded buffer. */
	result = MIN(self->if_cnt, size);
	memcpy(buf, self->if_ptr, result);
	self->if_ptr += result;
	self->if_cnt -= result;
	size -= result;
	if (!size)
		goto end;
	*(uintptr_t *)&buf += result;
	libc_fchecktty(self);

	/* Read everything that is too large directly. */
#if !(IOBUF_MAX & (IOBUF_MAX - 1))
	part = size & ~(IOBUF_MAX - 1);
#else
	part = (size / IOBUF_MAX) * IOBUF_MAX;
#endif
	if (part) {
		if (self->if_flag & IO_LNBUF)
			libc_flush_changed_lnbuf_files(self);
		temp = read(self->if_fd, buf, part);
		if (temp <= 0)
			goto err;
		self->if_exdata->io_pos += temp;
		result += temp;
		size -= temp;
		if (!size)
			goto end;
		*(uintptr_t *)&buf += temp;
	}
	assert(size);
	assert(!self->if_cnt);
	if (self->if_flag & IO_USERBUF) {
		/* Read all data that doesn't fit into the buffer directly. */
part_again:
		if (!self->if_bufsiz)
			part = size;
		else {
			part = (size / self->if_bufsiz) * self->if_bufsiz;
		}
		if (part) {
			if (self->if_flag & IO_LNBUF)
				libc_flush_changed_lnbuf_files(self);
			temp = read(self->if_fd,
			            buf,
			            part);
			if (temp <= 0)
				goto err;
			*(uintptr_t *)&buf += temp;
			size -= temp;
			if ((size_t)temp != part)
				goto part_again;
		}
		if (!size)
			goto end;

		/* Fill the buffer. */
		assert(self->if_bufsiz);
		if (self->if_flag & IO_LNBUF)
			libc_flush_changed_lnbuf_files(self);
		temp = read(self->if_fd,
		            self->if_base,
		            self->if_bufsiz);
		if (temp <= 0)
			goto err;
		self->if_ptr             = self->if_base;
		self->if_cnt             = (size_t)temp;
		self->if_exdata->io_read = (size_t)temp;
		self->if_flag |= IO_R;
		self->if_flag &= ~IO_W;
		goto load_buffer;
	}

	/* Allocate/Re-allocate a buffer of sufficient size. */
	minsize = CEIL_ALIGN(size, IOBUF_MIN);
	buffer  = self->if_base;
	if (minsize > self->if_bufsiz) {
		/* Must allocate more memory. */
		buffer = (unsigned char *)realloc(buffer, minsize);
		if unlikely(!buffer)
			goto direct_io;
		self->if_base   = buffer;
		self->if_bufsiz = minsize;
		self->if_flag |= IO_MALLBUF;
	} else if ((self->if_bufsiz - minsize) >=
	           IOBUF_RELOCATE_THRESHOLD) {
		/* Try to free unused data. */
		assert(self->if_flag & IO_MALLBUF);
		buffer = (unsigned char *)realloc(buffer, minsize);
		if unlikely(!buffer) {
			buffer = self->if_base;
			goto fill_buffer;
		}
		self->if_base   = buffer;
		self->if_bufsiz = minsize;
	}
fill_buffer:
	/* Read data into the buffer. */
	assert(minsize);
	if (self->if_flag & IO_LNBUF)
		libc_flush_changed_lnbuf_files(self);
	temp = read(self->if_fd, buffer, minsize);
	if (temp <= 0)
		goto err;
	self->if_exdata->io_read = (size_t)temp;
	self->if_exdata->io_pos += temp;
	self->if_cnt = (size_t)temp;
	self->if_ptr = buffer;
	self->if_flag |= IO_R;
	self->if_flag &= ~IO_W;
load_buffer:
	part = MIN((size_t)temp, size);
	/* Copy data out of the buffer. */
	memcpy(buf, self->if_ptr, part);
	self->if_ptr += part;
	self->if_cnt -= part;
	result += part;
end:
	/* Update the EOF flag according to the result. */
	return result;
direct_io:
	/* Read the remainder using direct I/O. */
	if (self->if_flag & IO_LNBUF)
		libc_flush_changed_lnbuf_files(self);
	temp = read(self->if_fd, buf, size);
	if (temp <= 0)
		goto err;
	result += temp;
	self->if_exdata->io_pos += temp;
	goto end;
err:
	if (temp == 0) {
		self->if_flag |= IO_EOF;
		return result;
	}
	self->if_flag |= IO_ERR;
	return 0;
}

INTERN int LIBCCALL
libc_fdoflush(FILE *__restrict self) {
	size_t flushsize;
	ssize_t temp;
	unsigned char *write_pointer;
	size_t write_size;
	/* Don't do anything if the buffer hasn't changed, or doesn't have a handle. */
	if (!(self->if_flag & IO_W) || (self->if_flag & IO_NOFD))
		return 0;
	flushsize = (size_t)(self->if_ptr - self->if_base);
	assertf(flushsize <= self->if_bufsiz, "Invalid file layout (ptr: %p; buf: %p...%p)",
	        self->if_ptr, self->if_base, self->if_base + self->if_bufsiz - 1);
	/* If the input buffer was read before, we must seek
	 * backwards to get back to where it was read from. */
	if (self->if_flag & IO_R && self->if_exdata->io_read) {
		off64_t pos = lseek64(self->if_fd,
		                      -(ssize_t)self->if_exdata->io_read,
		                      SEEK_CUR);
		if (pos < 0)
			goto err;
		self->if_exdata->io_pos = (pos64_t)pos;
	}
	/* Write the entirety of the current buffer up until the current R/W position. */
	write_pointer = self->if_base;
	write_size = (size_t)((uintptr_t)self->if_ptr -
	                      (uintptr_t)write_pointer);
	while (write_size) {
		temp = write(self->if_fd, write_pointer, write_size);
		if (temp < 0)
			goto err;
		if (!temp) {
			self->if_flag |= IO_EOF;
#ifdef CONFIG_FILE_DATASYNC_DURING_FLUSH
			if (libc_fdatasync(self->if_fd))
				goto err;
#endif
			return 0; /* XXX: Is this correct? */
		}
		self->if_exdata->io_pos += temp;
		write_pointer += temp;
		write_size -= temp;
	}
	if (self->if_flag & IO_LNBUF) {
		atomic_rwlock_write(&libc_flnchg_lock);
		if (LLIST_ISBOUND(self, if_exdata->io_lnch))
			LLIST_UNLINK(self, if_exdata->io_lnch);
		atomic_rwlock_endwrite(&libc_flnchg_lock);
	}

	/* Delete the changed and EOF flags. */
	self->if_flag &= ~(IO_EOF | IO_W | IO_R);
	/* Mark the buffer as empty. */
	self->if_exdata->io_read = 0;
	self->if_ptr             = self->if_base;
	self->if_cnt             = 0;
#ifdef CONFIG_FILE_DATASYNC_DURING_FLUSH
	/* Do a disk sync. */
	if (libc_fdatasync(self->if_fd))
		goto err;
#endif
	return 0;
err:
	self->if_flag |= IO_ERR;
	return -1;
}

INTERN int LIBCCALL
libc_doffill(FILE *__restrict self) {
	size_t avail;
	ssize_t temp;
	avail = (self->if_base + self->if_bufsiz) -
	        (self->if_ptr + self->if_cnt);
	if (!avail) {
		if (!self->if_bufsiz &&
		    !(self->if_flag & IO_USERBUF)) {
			avail = IOBUF_MIN;
			/* Allocate an initial buffer. */
			do {
				self->if_base = (unsigned char *)malloc(avail);
			} while (unlikely(!self->if_base) && (avail /= 2) != 0);
			if unlikely(!self->if_base)
				goto err;
			self->if_ptr    = self->if_base;
			self->if_bufsiz = avail;
		} else {
			/* Don't do anything if no data needs to be read. */
			return 0;
		}
	}
	assert(avail);
	libc_fchecktty(self);
	if (self->if_flag & IO_LNBUF)
		libc_flush_changed_lnbuf_files(self);
	/* Read more data. */
	temp = read(self->if_fd,
	            self->if_ptr + self->if_cnt,
	            avail);
	if (temp <= 0) {
		if (temp)
			goto err;
		/* Handle EOF. (We don't signal it unless no more data can be read) */
		if (!self->if_cnt) {
			self->if_flag |= IO_EOF;
			return -1;
		}
	} else {
		/* Update the file to mirror newly available data. */
		self->if_flag &= ~(IO_EOF);
		self->if_cnt += temp;
		self->if_exdata->io_read += temp;
		self->if_exdata->io_pos += temp;
	}
	return 0;
err:
	self->if_flag |= IO_ERR;
	return -1;
}

LOCAL void LIBCCALL
libc_fmarkchanged(FILE *__restrict self) {
	if (self->if_flag & IO_W)
		return;
	self->if_flag |= IO_W;
	if (self->if_flag & IO_LNBUF) {
		atomic_rwlock_write(&libc_flnchg_lock);
		if (!LLIST_ISBOUND(self, if_exdata->io_lnch))
			LLIST_INSERT(libc_flnchg, self, if_exdata->io_lnch);
		atomic_rwlock_endwrite(&libc_flnchg_lock);
	}
}

INTERN size_t LIBCCALL
libc_fdowrite(void const *__restrict buf, size_t size, FILE *__restrict self) {
	size_t result, part, minsize;
	unsigned char *buffer;
	ssize_t temp;
buffer_write_more:
	/* Write data to buffer (including to the overflow area). */
	result = MIN((size_t)((self->if_base + self->if_bufsiz) - self->if_ptr), size);
	libc_fchecktty(self);
	if (result) {
		memcpy(self->if_ptr, buf, result);
		libc_fmarkchanged(self);
		self->if_ptr += result;
		if (result >= self->if_cnt)
			self->if_cnt = 0;
		else {
			self->if_cnt -= result;
		}
		size -= result;
		/* Flush the buffer if it is line-buffered. */
		if (self->if_flag & IO_LNBUF &&
		    memchr(buf, '\n', result)) {
			if (libc_fdoflush(self))
				return 0;
			/* With the buffer now empty, we must write more data to it. */
			goto buffer_write_more;
		}
		if (!size)
			goto end;
		*(uintptr_t *)&buf += result;
	}
	if (!size)
		goto end;
	assert(!self->if_cnt);
	assert(self->if_ptr == self->if_base + self->if_bufsiz);

	/* Use direct I/O for anything that doesn't fit into the buffer. */
part_again:
	if (self->if_flag & IO_USERBUF) {
		if (!self->if_bufsiz)
			part = size;
		else {
			part = (size / self->if_bufsiz) * self->if_bufsiz;
		}
	} else {
		part = (size / IOBUF_MAX) * IOBUF_MAX;
	}
	/* Special case: if the last part contains line-feeds in a
	 *               line-buffered file, use direct I/O for that part as well. */
	if (self->if_flag & IO_LNBUF &&
	    memchr((byte_t *)buf + part, '\n', size - part))
		part = size;
	if (part) {
		/* Flush the buffer before performing direct I/O to preserve write order. */
		if (libc_fdoflush(self))
			return 0;
		temp = write(self->if_fd, buf, part);
		if (temp < 0)
			goto err;
		self->if_exdata->io_pos += temp;
		result += temp;
		size -= temp;
		if (!size)
			goto end;
		*(uintptr_t *)&buf += part;
		if ((size_t)temp != part)
			goto part_again;
	}
	/* Write the remainder to the buffer.
	 * NOTE: we've already confirmed that it doesn't contain a line-feed. */
	assert(!(self->if_flag & IO_R));
	assert(!(self->if_flag & IO_LNBUF) || !memchr(buf, '\n', size));
	buffer = self->if_base;
	if (!(self->if_flag & IO_USERBUF)) {
		/* Make sure the buffer is of sufficient size. */
		minsize = CEIL_ALIGN(size, IOBUF_MIN);
		if (minsize > self->if_bufsiz) {
			buffer = (unsigned char *)realloc(buffer, minsize);
			if unlikely(!buffer)
				goto direct_io;
			self->if_base   = buffer;
			self->if_bufsiz = minsize;
			self->if_flag |= IO_MALLBUF;
		} else if ((self->if_bufsiz - minsize) >=
		           IOBUF_RELOCATE_THRESHOLD) {
			/* Try to free unused data. */
			assert(self->if_flag & IO_MALLBUF);
			buffer = (unsigned char *)realloc(buffer, minsize);
			if unlikely(!buffer) {
				buffer = self->if_base;
				goto fill_buffer;
			}
			self->if_base   = buffer;
			self->if_bufsiz = minsize;
		}
	}
fill_buffer:
	assert(size);
	assert(size <= self->if_bufsiz);
	memcpy(buffer, buf, size);
	self->if_ptr = buffer + size;
	assert(!self->if_cnt);
	result += size;
	libc_fmarkchanged(self);
end:
	return result;
direct_io:
	/* Read the remainder using direct I/O. */
	temp = write(self->if_fd, buf, size);
	if (temp <= 0)
		goto err;
	result += temp;
	self->if_exdata->io_pos += temp;
	goto end;
err:
	self->if_flag |= IO_ERR;
	return 0;
}

INTERN pos64_t LIBCCALL
libc_fdotell(FILE *__restrict self) {
	pos64_t result = self->if_exdata->io_pos;
	if (self->if_flag & IO_R)
		result -= self->if_exdata->io_read;
	result += (size_t)(self->if_ptr - self->if_base);
	return result;
}

INTERN int LIBCCALL
libc_fdoseek(FILE *__restrict self, off64_t off, int whence) {
	off64_t new_pos;
	if ((whence == SEEK_SET || whence == SEEK_CUR) &&
	    off <= (ssize_t)(((size_t)-1) / 2)) {
		uintptr_t new_ptr;
		off64_t seek_offset = off;
		/* Special optimizations for seeking in-buffer. */
		if (whence == SEEK_SET)
			seek_offset = (off64_t)((pos64_t)off - libc_fdotell(self));
		if (!__builtin_add_overflow((uintptr_t)self->if_ptr,
		                            (uintptr_t)seek_offset,
		                            &new_ptr) &&
#if __SIZEOF_KERNEL_OFF_T__ > __SIZEOF_POINTER__
		    seek_offset < (off64_t)(uintptr_t)-1 &&
#endif
		    (uintptr_t)new_ptr >= (uintptr_t)self->if_base &&
		    (uintptr_t)new_ptr < (uintptr_t)self->if_ptr + self->if_cnt) {
			/* All right! - Successful seek within the currently loaded buffer. */
			self->if_ptr = (unsigned char *)new_ptr;
			self->if_cnt += ((uintptr_t)self->if_ptr -
			                 (uintptr_t)new_ptr);
			return 0;
		}
	}
	/* Flush the currently active buffer. */
	if (libc_fdoflush(self))
		goto err;

	if (whence == SEEK_CUR) {
		/* Must adjust for the underlying descriptor position. */
		if (self->if_flag & IO_R)
			off -= self->if_exdata->io_read;
		off += (size_t)(self->if_ptr - self->if_base);
	}

	/* Mark the file buffer as empty. */
	self->if_exdata->io_read = 0;
	self->if_ptr             = self->if_base;
	self->if_cnt             = 0;
	self->if_flag &= ~(IO_R | IO_W);

	/* Invoke the underlying stream descriptor. */
	new_pos = lseek64(self->if_fd, off, whence);

	/* Update the stored stream pointer. */
	if (new_pos < 0)
		self->if_flag |= IO_ERR;
	else {
		self->if_exdata->io_pos = (pos64_t)new_pos;
	}
	return 0;
err:
	return -1;
}


#define DOS_IOFBF 0x0000 /* Fully buffered. */
#define DOS_IOLBF 0x0040 /* Line buffered. */
#define DOS_IONBF 0x0004 /* No buffering. */


INTERN int LIBCCALL
libc_dosetvbuf(FILE *__restrict self, char *__restrict buf, int modes, size_t n) {
	/* Start out by flushing everything. */
	if (libc_fdoflush(self))
		return -1;

	/* Mark the file buffer as empty and delete special flags. */
	self->if_exdata->io_read = 0;
	self->if_ptr             = self->if_base;
	self->if_cnt             = 0;
	self->if_flag &= ~(IO_R | IO_W | IO_LNBUF | IO_LNIFTYY);

	if (modes == _IONBF || modes == DOS_IONBF) {
		/* Don't use any buffer. */
		if (self->if_flag & IO_MALLBUF)
			free(self->if_base);
		self->if_bufsiz = 0;
		self->if_ptr    = NULL;
		self->if_base   = NULL;
		return 0;
	}

	if (modes == _IOLBF || modes == DOS_IOLBF) {
		self->if_flag |= IO_LNBUF;
		/* Passing ZERO(0) for 'n' here causes the previous buffer to be kept. */
		if (!n)
			return 0;
	} else if (modes != _IOFBF
#if DOS_IOFBF != _IOFBF
	           && modes != DOS_IOFBF
#endif
	           ) {
inval:
		return (int)libc_seterrno(EINVAL);
	}

	/* Allocate/use the given buffer. */
	if (n < 2)
		goto inval;
#if __SIZEOF_SIZE_T__ > 4
	if (n > (u32)-1 && n != (size_t)-1)
		goto inval;
#endif
	if (!buf) {
		/* Dynamically allocate a buffer. */
		if (self->if_flag & IO_MALLBUF) {
			/* (re-)allocate an existing buffer. */
			buf = (char *)self->if_base;
			/* Make sure the buffer's size has actually changed.
			 * NOTE: As an extension, we accept `(size_t)-1' to keep the old buffer size. */
			if (n == (size_t)-1)
				n = (size_t)self->if_bufsiz;
			else if ((size_t)self->if_bufsiz != n) {
				buf = (char *)realloc(buf, n);
				if unlikely(!buf)
					return -1;
			}
		} else {
			/* To go with the special behavior for (size_t)-1 above,
			 * here that value indicates a max-length buffer as would be allocated regularly. */
			if (n == (size_t)-1)
				n = IOBUF_MAX;
			buf = (char *)malloc(n);
			if unlikely(!buf)
				return -1;
			self->if_flag |= IO_MALLBUF;
		}
	} else {
		/* Mark the buffer as being fixed-length, thus preventing it from being re-allocated. */
		self->if_flag |= IO_USERBUF;
	}

	/* Install the given buffer. */
	self->if_ptr    = (unsigned char *)buf;
	self->if_base   = (unsigned char *)buf;
	self->if_bufsiz = (u32)n;

	return 0;
}

INTERN int LIBCCALL libc_doungetc(int c, FILE *__restrict self) {
	pos_t buffer_start;
	if (self->if_ptr != self->if_base) {
		/* Simple case: we're not at the start of the buffer. */
		if (self->if_flag & IO_R &&
		    self->if_ptr[-1] != (char)c)
			libc_fmarkchanged(self);
		*--self->if_ptr = (char)c;
		return c;
	}
	/* Make sure we're not going too far back. */
	buffer_start = self->if_exdata->io_pos;
	if (self->if_flag & IO_R)
		buffer_start -= self->if_exdata->io_read;
	if (!buffer_start)
		return EOF;

	/* This is where it gets complicated... */
	assert(self->if_ptr == self->if_base);
	assert(self->if_cnt <= self->if_bufsiz);
	if (self->if_cnt != self->if_bufsiz) {
insert_front:
		/* We can shift the entire buffer. */
		assert(self->if_exdata->io_read <= self->if_bufsiz);
		memmove(self->if_base + 1, self->if_base,
		        self->if_exdata->io_read);
		/* Update the file to make it look like it was read
		 * one byte before where it was really read at. */
		--self->if_exdata->io_pos;
		++self->if_exdata->io_read;
		++self->if_cnt;
	} else {
		unsigned char *new_buffer;
		size_t new_size;
		if (self->if_flag & IO_USERBUF)
			return -1;
		/* If the current buffer isn't user-given, we can simply allocate more. */
		new_size = CEIL_ALIGN(self->if_bufsiz + 1, IOBUF_MIN);
#if __SIZEOF_SIZE_T__ > 4
		if
			unlikely(new_size > (size_t)(u32)-1)
		return -1;
#endif
realloc_again:
		new_buffer = (unsigned char *)realloc(self->if_base, new_size);
		if (!new_buffer) {
			if (new_size != self->if_bufsiz + 1) {
				new_size = self->if_bufsiz + 1;
				goto realloc_again;
			}
			return -1;
		}
		/* Update buffer points. */
		self->if_ptr    = new_buffer;
		self->if_base   = new_buffer;
		self->if_bufsiz = new_size;
		assert(self->if_cnt < self->if_bufsiz);
		goto insert_front;
	}

	*self->if_base = (char)c;
	if (self->if_flag & IO_R)
		self->if_flag |= IO_R;
	return c;
}

INTERN void LIBCCALL libc_flushall_nostd(void) {
	FILE *iter;
	atomic_rwlock_read(&libc_ffiles_lock);
	LLIST_FOREACH(iter, libc_ffiles, if_exdata->io_link) {
		file_write(iter);
		libc_fdoflush(iter);
		file_endwrite(iter);
	}
	atomic_rwlock_endread(&libc_ffiles_lock);
}

INTERN void LIBCCALL libc_flushall_nostd_unlocked(void) {
	FILE *iter;
	LLIST_FOREACH(iter, libc_ffiles, if_exdata->io_link) {
		libc_fdoflush(iter);
	}
}

PRIVATE void LIBCCALL
libc_flushstdstream(FILE *self) {
	if (!self)
		return;
	file_write(self);
	libc_fdoflush(self);
	file_endwrite(self);
}

PRIVATE void LIBCCALL
libc_flushstdstream_unlocked(FILE *self) {
	if (!self)
		return;
	libc_fdoflush(self);
}


#undef flushall
#undef _flushall
#undef libc__flushall

DEFINE_PUBLIC_ALIAS(_flushall, libc_doflushall);
DEFINE_PUBLIC_ALIAS(flushall, libc_doflushall);
DEFINE_INTERN_ALIAS(libc__flushall, libc_doflushall);
INTERN int LIBCCALL libc_doflushall(void) {
	libc_flushstdstream(stdin);
	libc_flushstdstream(stdout);
	libc_flushstdstream(stderr);
	/* Finally, flush all non-standard streams. */
	libc_flushall_nostd();
	return 0;
}










/*[[[start:implementation]]]*/


/*[[[impl:flushall_unlocked]]]*/
#undef libc_flushall_unlocked
DEFINE_INTERN_ALIAS(libc_flushall_unlocked, libc_doflushall_unlocked);
INTERN int LIBCCALL libc_doflushall_unlocked(void) {
	libc_flushstdstream_unlocked(stdin);
	libc_flushstdstream_unlocked(stdout);
	libc_flushstdstream_unlocked(stderr);
	/* Finally, flush all non-standard streams. */
	libc_flushall_nostd_unlocked();
	return 0;
}


/*[[[head:removeat,hash:0x656f9e94]]]*/
/* Remove a file or directory `FILENAME' relative to a given base directory `DIRFD' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify.removeat") int
NOTHROW_RPC(LIBCCALL libc_removeat)(fd_t dirfd,
                                    char const *filename)
/*[[[body:removeat]]]*/
{
	errno_t result;
	result = sys_unlinkat(dirfd, filename, AT_REMOVEDIR | AT_REMOVEREG);
	return libc_seterrno_syserr(result);
}
/*[[[end:removeat]]]*/

/*[[[head:remove,hash:0xdd986498]]]*/
/* Remove a file or directory `FILENAME' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify.remove") int
NOTHROW_RPC(LIBCCALL libc_remove)(char const *filename)
/*[[[body:remove]]]*/
{
	return removeat(AT_FDCWD, filename);
}
/*[[[end:remove]]]*/



/*[[[head:ftrylockfile,hash:0x76aac2c7]]]*/
/* Try to acquire a lock to `STREAM' */
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.utility.ftrylockfile") int
NOTHROW_NCX(LIBCCALL libc_ftrylockfile)(FILE *__restrict stream)
/*[[[body:ftrylockfile]]]*/
{
	if unlikely(!stream)
		return -1;
	return file_trywrite(stream) ? 0 : 1;
}
/*[[[end:ftrylockfile]]]*/

/*[[[head:funlockfile,hash:0xd79cb5e5]]]*/
/* Release a previously acquired lock from `STREAM' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.utility.funlockfile") void
NOTHROW_NCX(LIBCCALL libc_funlockfile)(FILE *__restrict stream)
/*[[[body:funlockfile]]]*/
{
	if likely(stream)
		file_endwrite(stream);
}
/*[[[end:funlockfile]]]*/

/*[[[head:flockfile,hash:0x8d52965]]]*/
/* Acquire a lock to `STREAM' and block until doing so succeeds */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.utility.flockfile") void
NOTHROW_RPC(LIBCCALL libc_flockfile)(FILE *__restrict stream)
/*[[[body:flockfile]]]*/
{
	if likely(stream)
		file_write(stream);
}
/*[[[end:flockfile]]]*/


/*[[[head:fflush,hash:0xc7a1e57e]]]*/
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.write.utility.fflush") int
(LIBCCALL libc_fflush)(FILE *stream)
		__THROWS(...)
/*[[[body:fflush]]]*/
{
	int result;
	if (!stream)
		return flushall();
	file_write(stream);
	result = libc_fdoflush(stream);
	file_endwrite(stream);
	return result;
}
/*[[[end:fflush]]]*/

/*[[[head:fflush_unlocked,hash:0x230bce90]]]*/
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.write.utility.fflush_unlocked") int
(LIBCCALL libc_fflush_unlocked)(FILE *stream)
		__THROWS(...)
/*[[[body:fflush_unlocked]]]*/
{
	int result;
	if (!stream)
		return flushall_unlocked();
	result = libc_fdoflush(stream);
	return result;
}
/*[[[end:fflush_unlocked]]]*/



/*[[[head:fread,hash:0x3390b1f4]]]*/
/* Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF' */
INTERN WUNUSED NONNULL((1, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.read.read.fread") size_t
(LIBCCALL libc_fread)(void *__restrict buf,
                      size_t elemsize,
                      size_t elemcount,
                      FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fread]]]*/
{
	size_t result, total;
	if unlikely(!stream) {
		libc_seterrno(EINVAL);
		return 0;
	}
	if unlikely(!elemsize)
		return 0;
	if unlikely(OVERFLOW_UMUL(elemcount, elemsize, &total)) {
		libc_seterrno(EOVERFLOW);
		FSETERROR(stream);
		return 0;
	}
	file_write(stream);
	result = libc_fdoread(buf, total, stream);
	file_endwrite(stream);
	return result / elemsize;
}
/*[[[end:fread]]]*/

/*[[[head:fread_unlocked,hash:0xcc0dba63]]]*/
/* Same as `fread()', but performs I/O without acquiring a lock to `STREAM' */
INTERN WUNUSED NONNULL((1, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.read.read.fread_unlocked") size_t
(LIBCCALL libc_fread_unlocked)(void *__restrict buf,
                               size_t elemsize,
                               size_t elemcount,
                               FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fread_unlocked]]]*/
{
	size_t result, total;
	if unlikely(!stream) {
		libc_seterrno(EINVAL);
		return 0;
	}
	if unlikely(!elemsize)
		return 0;
	if unlikely(OVERFLOW_UMUL(elemcount, elemsize, &total)) {
		libc_seterrno(EOVERFLOW);
		FSETERROR(stream);
		return 0;
	}
	result = libc_fdoread(buf, total, stream);
	return result / elemsize;
}
/*[[[end:fread_unlocked]]]*/

/*[[[head:fwrite,hash:0x7fd36acf]]]*/
/* Write up to `ELEMSIZE * ELEMCOUNT' bytes of data from `BUF' into `STREAM' */
INTERN NONNULL((1, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.write.write.fwrite") size_t
(LIBCCALL libc_fwrite)(void const *__restrict buf,
                       size_t elemsize,
                       size_t elemcount,
                       FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fwrite]]]*/
{
	size_t result, total;
	if unlikely(!stream) {
		libc_seterrno(EINVAL);
		return 0;
	}
	if unlikely(!elemsize)
		return 0;
	if unlikely(OVERFLOW_UMUL(elemcount, elemsize, &total)) {
		libc_seterrno(EOVERFLOW);
		FSETERROR(stream);
		return 0;
	}
	file_write(stream);
	result = libc_fdowrite(buf, total, stream);
	file_endwrite(stream);
	return result / elemsize;
}
/*[[[end:fwrite]]]*/

/*[[[head:fwrite_unlocked,hash:0xb022199e]]]*/
/* Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM' */
INTERN NONNULL((1, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.write.printf.fwrite_unlocked") size_t
(LIBCCALL libc_fwrite_unlocked)(void const *__restrict buf,
                                size_t elemsize,
                                size_t elemcount,
                                FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fwrite_unlocked]]]*/
{
	size_t result, total;
	if unlikely(!stream) {
		libc_seterrno(EINVAL);
		return 0;
	}
	if unlikely(!elemsize)
		return 0;
	if unlikely(OVERFLOW_UMUL(elemcount, elemsize, &total)) {
		libc_seterrno(EOVERFLOW);
		FSETERROR(stream);
		return 0;
	}
	result = libc_fdowrite(buf, total, stream);
	return result / elemsize;
}
/*[[[end:fwrite_unlocked]]]*/

/*[[[head:file_printer,hash:0x7aae8944]]]*/
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.write.write.file_printer") ssize_t
(LIBCCALL libc_file_printer)(void *arg,
                             char const *__restrict data,
                             size_t datalen)
		__THROWS(...)
/*[[[body:file_printer]]]*/
{
	ssize_t result;
	if unlikely(!arg)
		return 0;
	file_write((FILE *)arg);
	result = (ssize_t)libc_fdowrite(data, datalen * sizeof(char), (FILE *)arg);
	if unlikely(!result && FERROR((FILE *)arg))
		result = -1;
	file_endwrite((FILE *)arg);
	return result;
}
/*[[[end:file_printer]]]*/

/*[[[head:file_printer_unlocked,hash:0xaa267ca7]]]*/
/* Same as `file_printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.write.write.file_printer_unlocked") ssize_t
(LIBCCALL libc_file_printer_unlocked)(void *arg,
                                      char const *__restrict data,
                                      size_t datalen)
		__THROWS(...)
/*[[[body:file_printer_unlocked]]]*/
{
	ssize_t result;
	if unlikely(!arg)
		return 0;
	result = (ssize_t)libc_fdowrite(data, datalen * sizeof(char), (FILE *)arg);
	if unlikely(!result && FERROR((FILE *)arg))
		result = -1;
	return result;
}
/*[[[end:file_printer_unlocked]]]*/


/*[[[head:ftell,hash:0xcf16a527]]]*/
/* Return the current in-file position of `STREAM' as a byte-offet from the start of the file */
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.seek.seek.ftell") long int
(LIBCCALL libc_ftell)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:ftell]]]*/
{
	pos64_t result;
	if unlikely(!stream)
		return (long int)libc_seterrno(EINVAL);
	file_read(stream);
	result = (pos64_t)libc_fdotell(stream);
	file_endread(stream);
	if unlikely(result > LONG_MAX)
		return (long int)libc_seterrno(EOVERFLOW);
	return (long int)(off64_t)result;
}
/*[[[end:ftell]]]*/

/*[[[head:fseek,hash:0x89b0d9d3]]]*/
/* Change the current in-file position of `STREAM' as a byte-offet from the start of the file */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.seek.seek.fseek") int
(LIBCCALL libc_fseek)(FILE *__restrict stream,
                      long int off,
                      int whence)
		__THROWS(...)
/*[[[body:fseek]]]*/
{
	int result;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	file_write(stream);
	result = libc_fdoseek(stream,
	                      (off64_t)off,
	                      whence);
	file_endwrite(stream);
	return result;
}
/*[[[end:fseek]]]*/

/*[[[head:ftello,hash:0x7304cdc2]]]*/
/* Return the current in-file position of `STREAM' */
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.seek.seek.ftello") off_t
(LIBCCALL libc_ftello)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:ftello]]]*/
{
	pos64_t result;
	if unlikely(!stream)
		return (off_t)libc_seterrno(EINVAL);
	file_read(stream);
	result = (pos64_t)libc_fdotell(stream);
	file_endread(stream);
	if unlikely(result > INT32_MAX)
		return (off_t)libc_seterrno(EOVERFLOW);
	return (off_t)(pos_t)result;
}
/*[[[end:ftello]]]*/

/*[[[head:ftello64,hash:0x1d8e96fb]]]*/
/* 64-bit variant of `ftello' */
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_ftello64, libc_ftello);
#else
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.seek.seek.ftello64") off64_t
(LIBCCALL libc_ftello64)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:ftello64]]]*/
{
	pos64_t result;
	if unlikely(!stream)
		return (off64_t)libc_seterrno(EINVAL);
	file_read(stream);
	result = (pos64_t)libc_fdotell(stream);
	file_endread(stream);
	if unlikely(result > INT64_MAX)
		return (off64_t)libc_seterrno(EOVERFLOW);
	return (off64_t)result;
}
#endif /* MAGIC:alias */
/*[[[end:ftello64]]]*/


/*[[[head:fseeko,hash:0x999a6f2f]]]*/
/* Change the current in-file position of `STREAM' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.seek.seek.fseeko") int
(LIBCCALL libc_fseeko)(FILE *__restrict stream,
                       off_t off,
                       int whence)
		__THROWS(...)
/*[[[body:fseeko]]]*/
{
	int result;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	file_write(stream);
	result = libc_fdoseek(stream,
	                      (off64_t)off,
	                      whence);
	file_endwrite(stream);
	return result;
}
/*[[[end:fseeko]]]*/

/*[[[head:fseeko64,hash:0xa138ca44]]]*/
/* 64-bit variant of `fseeko' */
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_fseeko64, libc_fseeko);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.seek.seek.fseeko64") int
(LIBCCALL libc_fseeko64)(FILE *__restrict stream,
                         off64_t off,
                         int whence)
		__THROWS(...)
/*[[[body:fseeko64]]]*/
{
	int result;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	file_write(stream);
	result = libc_fdoseek(stream,
	                      off,
	                      whence);
	file_endwrite(stream);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:fseeko64]]]*/


/*[[[head:fgetpos,hash:0xcf13b2d6]]]*/
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.seek.pos.fgetpos") int
(LIBCCALL libc_fgetpos)(FILE *__restrict stream,
                        fpos_t *__restrict pos)
		__THROWS(...)
/*[[[body:fgetpos]]]*/
{
	off_t result;
	result = ftello(stream);
	if unlikely(result == -1 && libc_geterrno() != EOK)
		return -1;
	*pos = (fpos_t)result;
	return 0;
}
/*[[[end:fgetpos]]]*/

/*[[[head:fsetpos,hash:0xf6d5eef6]]]*/
/* Set the file position of `STREAM' to `POS', as previously initialized with a call to `fgetpos()' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.seek.pos.fsetpos") int
(LIBCCALL libc_fsetpos)(FILE *__restrict stream,
                        fpos_t const *__restrict pos)
		__THROWS(...)
/*[[[body:fsetpos]]]*/
{
	return fseeko(stream, (off_t)(pos_t)*pos, SEEK_SET);
}
/*[[[end:fsetpos]]]*/

/*[[[head:fgetpos64,hash:0xf16041df]]]*/
/* 64-bit variant of `fgetpos' */
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_fgetpos64, libc_fgetpos);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.seek.pos.fgetpos64") int
(LIBCCALL libc_fgetpos64)(FILE *__restrict stream,
                          fpos64_t *__restrict pos)
		__THROWS(...)
/*[[[body:fgetpos64]]]*/
{
	off64_t result;
	result = ftello64(stream);
	if unlikely(result == -1 && libc_geterrno() != EOK)
		return -1;
	*pos = (fpos64_t)result;
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:fgetpos64]]]*/

/*[[[head:fsetpos64,hash:0xa500bbcf]]]*/
/* 64-bit variant of `fsetpos' */
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_fsetpos64, libc_fsetpos);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.seek.pos.fsetpos64") int
(LIBCCALL libc_fsetpos64)(FILE *__restrict stream,
                          fpos64_t const *__restrict pos)
		__THROWS(...)
/*[[[body:fsetpos64]]]*/
{
	return fseeko64(stream, (off64_t)(pos64_t)*pos, SEEK_SET);
}
#endif /* MAGIC:alias */
/*[[[end:fsetpos64]]]*/




/*[[[head:ftell_unlocked,hash:0xc6094e0b]]]*/
/* Return the current in-file position of `STREAM' as a byte-offet from the start of the file */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.seek.seek.ftell_unlocked") long int
(LIBCCALL libc_ftell_unlocked)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:ftell_unlocked]]]*/
{
	pos64_t result;
	if unlikely(!stream)
		return (long int)libc_seterrno(EINVAL);
	result = (pos64_t)libc_fdotell(stream);
	if unlikely(result > LONG_MAX)
		return (long int)libc_seterrno(EOVERFLOW);
	return (long int)(off64_t)result;
}
/*[[[end:ftell_unlocked]]]*/

/*[[[head:ftello_unlocked,hash:0x28e6d615]]]*/
/* Return the current in-file position of `STREAM' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.seek.seek.ftello_unlocked") off_t
(LIBCCALL libc_ftello_unlocked)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:ftello_unlocked]]]*/
{
	pos64_t result;
	if unlikely(!stream)
		return (off_t)libc_seterrno(EINVAL);
	result = (pos64_t)libc_fdotell(stream);
	if unlikely(result > INT32_MAX)
		return (off_t)libc_seterrno(EOVERFLOW);
	return (off_t)(pos_t)result;
}
/*[[[end:ftello_unlocked]]]*/

/*[[[head:ftello64_unlocked,hash:0x401f5ef2]]]*/
/* 64-bit variant of `ftello' */
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_ftello64_unlocked, libc_ftello_unlocked);
#else
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.seek.seek.ftello64_unlocked") off64_t
(LIBCCALL libc_ftello64_unlocked)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:ftello64_unlocked]]]*/
{
	pos64_t result;
	if unlikely(!stream)
		return (off64_t)libc_seterrno(EINVAL);
	result = (pos64_t)libc_fdotell(stream);
	if unlikely(result > INT64_MAX)
		return (off64_t)libc_seterrno(EOVERFLOW);
	return (off64_t)result;
}
#endif /* MAGIC:alias */
/*[[[end:ftello64_unlocked]]]*/

/*[[[head:fseek_unlocked,hash:0xc0171a3c]]]*/
/* Change the current in-file position of `STREAM' as a byte-offet from the start of the file */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.seek.seek.fseek_unlocked") int
(LIBCCALL libc_fseek_unlocked)(FILE *__restrict stream,
                               long int off,
                               int whence)
		__THROWS(...)
/*[[[body:fseek_unlocked]]]*/
{
	int result;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	result = libc_fdoseek(stream,
	                      (off64_t)off,
	                      whence);
	return result;
}
/*[[[end:fseek_unlocked]]]*/

/*[[[head:fseeko_unlocked,hash:0xeb64d1ab]]]*/
/* Change the current in-file position of `STREAM' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.seek.seek.fseeko_unlocked") int
(LIBCCALL libc_fseeko_unlocked)(FILE *__restrict stream,
                                off_t off,
                                int whence)
		__THROWS(...)
/*[[[body:fseeko_unlocked]]]*/
{
	int result;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	result = libc_fdoseek(stream,
	                      (off64_t)off,
	                      whence);
	return result;
}
/*[[[end:fseeko_unlocked]]]*/

/*[[[head:fseeko64_unlocked,hash:0xecbf6807]]]*/
/* 64-bit variant of `fseeko' */
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_fseeko64_unlocked, libc_fseeko_unlocked);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.seek.seek.fseeko64_unlocked") int
(LIBCCALL libc_fseeko64_unlocked)(FILE *__restrict stream,
                                  off64_t off,
                                  int whence)
		__THROWS(...)
/*[[[body:fseeko64_unlocked]]]*/
{
	int result;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	result = libc_fdoseek(stream,
	                      (off64_t)off,
	                      whence);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:fseeko64_unlocked]]]*/

/*[[[head:fgetpos_unlocked,hash:0xa0f513af]]]*/
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.seek.pos.fgetpos_unlocked") int
(LIBCCALL libc_fgetpos_unlocked)(FILE *__restrict stream,
                                 fpos_t *__restrict pos)
		__THROWS(...)
/*[[[body:fgetpos_unlocked]]]*/
{
	off_t result;
	result = ftello(stream);
	if unlikely(result == -1 && libc_geterrno() != EOK)
		return -1;
	*pos = (fpos_t)result;
	return 0;
}
/*[[[end:fgetpos_unlocked]]]*/

/*[[[head:fsetpos_unlocked,hash:0x9ed1ca29]]]*/
/* Set the file position of `STREAM' to `POS', as previously initialized with a call to `fgetpos()' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.seek.pos.fsetpos_unlocked") int
(LIBCCALL libc_fsetpos_unlocked)(FILE *__restrict stream,
                                 fpos_t const *__restrict pos)
		__THROWS(...)
/*[[[body:fsetpos_unlocked]]]*/
{
	return fseeko(stream, (off_t)(pos_t)*pos, SEEK_SET);
}
/*[[[end:fsetpos_unlocked]]]*/

/*[[[head:fgetpos64_unlocked,hash:0x3bf2a92e]]]*/
/* 64-bit variant of `fgetpos' */
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_fgetpos64_unlocked, libc_fgetpos_unlocked);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.seek.pos.fgetpos64_unlocked") int
(LIBCCALL libc_fgetpos64_unlocked)(FILE *__restrict stream,
                                   fpos64_t *__restrict pos)
		__THROWS(...)
/*[[[body:fgetpos64_unlocked]]]*/
{
	off64_t result;
	result = ftello64(stream);
	if unlikely(result == -1 && libc_geterrno() != EOK)
		return -1;
	*pos = (fpos64_t)result;
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:fgetpos64_unlocked]]]*/

/*[[[head:fsetpos64_unlocked,hash:0x291d06d3]]]*/
/* 64-bit variant of `fsetpos' */
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_fsetpos64_unlocked, libc_fsetpos_unlocked);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.seek.pos.fsetpos64_unlocked") int
(LIBCCALL libc_fsetpos64_unlocked)(FILE *__restrict stream,
                                   fpos64_t const *__restrict pos)
		__THROWS(...)
/*[[[body:fsetpos64_unlocked]]]*/
{
	return fseeko64(stream, (off64_t)(pos64_t)*pos, SEEK_SET);
}
#endif /* MAGIC:alias */
/*[[[end:fsetpos64_unlocked]]]*/

/*[[[head:getw,hash:0x16174e7d]]]*/
/* Similar to `getc()', but read 2 bytes */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.read.getc.getw") int
(LIBCCALL libc_getw)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:getw]]]*/
{
	u16 result;
	return fread(&result,
	             sizeof(result),
	             1,
	             stream)
	       ? (int)result
	       : (int)EOF;
}
/*[[[end:getw]]]*/

/*[[[head:getw_unlocked,hash:0xb671e142]]]*/
/* Similar to `getc()', but read 2 bytes */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.read.getc.getw_unlocked") int
(LIBCCALL libc_getw_unlocked)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:getw_unlocked]]]*/
{
	u16 result;
	return fread_unlocked(&result,
	                      sizeof(result),
	                      1,
	                      stream)
	       ? (int)result
	       : (int)EOF;
}
/*[[[end:getw_unlocked]]]*/

/*[[[head:putw,hash:0x581c0e0e]]]*/
/* Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.write.putc.putw") int
(LIBCCALL libc_putw)(int w,
                     FILE *__restrict stream)
		__THROWS(...)
/*[[[body:putw]]]*/
{
	u16 c = (u16)w;
	return fwrite(&c,
	              sizeof(c),
	              1,
	              stream)
	       ? w
	       : EOF;
}
/*[[[end:putw]]]*/

/*[[[head:putw_unlocked,hash:0xe98a61e]]]*/
/* Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.write.putc.putw_unlocked") int
(LIBCCALL libc_putw_unlocked)(int w,
                              FILE *__restrict stream)
		__THROWS(...)
/*[[[body:putw_unlocked]]]*/
{
	u16 c = (u16)w;
	return fwrite_unlocked(&c,
	                       sizeof(c),
	                       1,
	                       stream)
	       ? w
	       : EOF;
}
/*[[[end:putw_unlocked]]]*/

/*[[[head:ungetc,hash:0x7691376c]]]*/
/* Unget a single character byte of data previously returned by `getc()' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.read.getc.ungetc") int
NOTHROW_NCX(LIBCCALL libc_ungetc)(int ch,
                                  FILE *__restrict stream)
/*[[[body:ungetc]]]*/
{
	int result;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	file_write(stream);
	result = libc_doungetc(ch, stream);
	file_endwrite(stream);
	return result;
}
/*[[[end:ungetc]]]*/

/*[[[head:ungetc_unlocked,hash:0x9a203c0f]]]*/
/* Unget a single character byte of data previously returned by `getc()' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.read.getc.ungetc_unlocked") int
NOTHROW_NCX(LIBCCALL libc_ungetc_unlocked)(int ch,
                                           FILE *__restrict stream)
/*[[[body:ungetc_unlocked]]]*/
{
	int result;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	result = libc_doungetc(ch, stream);
	return result;
}
/*[[[end:ungetc_unlocked]]]*/

/*[[[head:rewind,hash:0x7cef3aad]]]*/
/* Rewind the current in-file position of `STREAM' to its starting position */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.seek.utility.rewind") void
(LIBCCALL libc_rewind)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:rewind]]]*/
{
	if likely(stream) {
		file_write(stream);
		libc_fdoseek(stream, 0, SEEK_SET);
		file_endwrite(stream);
	}
}
/*[[[end:rewind]]]*/

/*[[[head:rewind_unlocked,hash:0x78e274f0]]]*/
/* Rewind the current in-file position of `STREAM' to its starting position */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.seek.utility.rewind_unlocked") void
(LIBCCALL libc_rewind_unlocked)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:rewind_unlocked]]]*/
{
	if likely(stream)
		libc_fdoseek(stream, 0, SEEK_SET);
}
/*[[[end:rewind_unlocked]]]*/

/*[[[head:fisatty,hash:0x3c409b31]]]*/
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.io.tty.fisatty") int
NOTHROW_NCX(LIBCCALL libc_fisatty)(FILE *__restrict stream)
/*[[[body:fisatty]]]*/
{
	fd_t fd = fileno(stream);
	if unlikely(fd < 0)
		return -1;
	return isatty(fd);
}
/*[[[end:fisatty]]]*/

/*[[[head:setvbuf,hash:0x68fe473a]]]*/
/* Set the buffer and buffer-mode to-be used by the given `STREAM'
 * @param modes: One of `_IOFBF', `_IOLBF' or `_IONBF' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.read.utility.setvbuf") int
NOTHROW_NCX(LIBCCALL libc_setvbuf)(FILE *__restrict stream,
                                   char *__restrict buf,
                                   int modes,
                                   size_t bufsize)
/*[[[body:setvbuf]]]*/
{
	int result;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	file_write(stream);
	result = libc_dosetvbuf(stream,
	                        buf,
	                        modes,
	                        bufsize);
	file_endwrite(stream);
	return result;
}
/*[[[end:setvbuf]]]*/

/*[[[head:setvbuf_unlocked,hash:0xac7cd712]]]*/
/* Set the buffer and buffer-mode to-be used by the given `STREAM'
 * @param modes: One of `_IOFBF', `_IOLBF' or `_IONBF' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.read.utility.setvbuf_unlocked") int
NOTHROW_NCX(LIBCCALL libc_setvbuf_unlocked)(FILE *__restrict stream,
                                            char *__restrict buf,
                                            int modes,
                                            size_t bufsize)
/*[[[body:setvbuf_unlocked]]]*/
{
	int result;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	result = libc_dosetvbuf(stream,
	                        buf,
	                        modes,
	                        bufsize);
	return result;
}
/*[[[end:setvbuf_unlocked]]]*/

/*[[[head:setbuf,hash:0x7a79b157]]]*/
/* Alias for `setvbuf(STREAM, buf, _IOFBF, BUFSIZ)' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.read.utility.setbuf") void
NOTHROW_NCX(LIBCCALL libc_setbuf)(FILE *__restrict stream,
                                  char *__restrict buf)
/*[[[body:setbuf]]]*/
{
	setvbuf(stream,
	        buf,
	        _IOFBF,
	        BUFSIZ);
}
/*[[[end:setbuf]]]*/

/*[[[head:setbuffer,hash:0x44b5aae9]]]*/
/* Specify the location and size for the buffer to-be used by `STREAM' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.read.utility.setbuffer") void
NOTHROW_NCX(LIBCCALL libc_setbuffer)(FILE *__restrict stream,
                                     char *buf,
                                     size_t bufsize)
/*[[[body:setbuffer]]]*/
{
	setvbuf(stream,
	        buf,
	        buf ? _IOFBF : _IONBF,
	        buf ? bufsize : (size_t)0);
}
/*[[[end:setbuffer]]]*/

/*[[[head:setlinebuf,hash:0xdc6dde24]]]*/
/* Change the given `STREAM' to become line-buffered */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.read.utility.setlinebuf") void
NOTHROW_NCX(LIBCCALL libc_setlinebuf)(FILE *__restrict stream)
/*[[[body:setlinebuf]]]*/
{
	setvbuf(stream,
	        NULL,
	        _IOLBF,
	        0);
}
/*[[[end:setlinebuf]]]*/

/*[[[head:puts,hash:0x286bbae]]]*/
/* Print a given string `STR', followed by a line-feed to `STDOUT' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.write.write.puts") __STDC_INT_AS_SSIZE_T
(LIBCCALL libc_puts)(char const *__restrict str)
		__THROWS(...)
/*[[[body:puts]]]*/
{
	ssize_t result;
	FILE *stream = stdout;
	file_write(stream);
	result = fputs_unlocked(str, stream);
	if (result >= 0)
		result += fwrite_unlocked("\n", sizeof(char), 1, stream);
	file_endwrite(stream);
	return result;
}
/*[[[end:puts]]]*/

/*[[[head:puts_unlocked,hash:0x7705ed9b]]]*/
/* Print a given string `STR', followed by a line-feed to `STDOUT' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.write.write.puts_unlocked") __STDC_INT_AS_SSIZE_T
(LIBCCALL libc_puts_unlocked)(char const *__restrict str)
		__THROWS(...)
/*[[[body:puts_unlocked]]]*/
{
	ssize_t result;
	FILE *stream = stdout;
	result       = fputs_unlocked(str, stream);
	if (result >= 0)
		result += fwrite_unlocked("\n", sizeof(char), 1, stream);
	return result;
}
/*[[[end:puts_unlocked]]]*/



/*[[[head:feof,hash:0x1ced5676]]]*/
/* Check if end-of-file has been reached in `STREAM' */
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.read.utility.feof") int
NOTHROW_NCX(LIBCCALL libc_feof)(FILE *__restrict stream)
/*[[[body:feof]]]*/
{
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	return FEOF(stream);
}
/*[[[end:feof]]]*/

/*[[[head:ferror,hash:0x9b4b88e9]]]*/
/* Check if an I/O error occurred in `STREAM' */
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.utility.ferror") int
NOTHROW_NCX(LIBCCALL libc_ferror)(FILE *__restrict stream)
/*[[[body:ferror]]]*/
{
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	return FERROR(stream);
}
/*[[[end:ferror]]]*/

/*[[[head:clearerr,hash:0xd5ba0061]]]*/
/* Clear the error state of `STREAM', returning the stream to normal operations mode */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.access.clearerr") void
NOTHROW_NCX(LIBCCALL libc_clearerr)(FILE *__restrict stream)
/*[[[body:clearerr]]]*/
{
	if likely(stream)
		FCLEARERR(stream);
}
/*[[[end:clearerr]]]*/

/*[[[head:clearerr_s,hash:0xab68c670]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.locked.utility.clearerr_s") errno_t
NOTHROW_NCX(LIBCCALL libc_clearerr_s)(FILE *__restrict stream)
/*[[[body:clearerr_s]]]*/
{
	if unlikely(!stream)
		return EINVAL;
	clearerr(stream);
	return EOK;
}
/*[[[end:clearerr_s]]]*/


PRIVATE int LIBCCALL
parse_open_modes(char const *__restrict modes) {
	int mode = O_RDONLY;
	if (modes) {
		for (; *modes; ++modes) {
			if (*modes == 'r')
				mode = O_RDONLY;
			if (*modes == 'w')
				mode = O_WRONLY | O_CREAT | O_TRUNC;
			if (*modes == '+')
				mode &= ~(O_TRUNC | O_ACCMODE), mode |= O_RDWR;
		}
	}
	return mode;
}


/*[[[head:tmpfile,hash:0xc57c6fc2]]]*/
/* Create and return a new file-stream for accessing a temporary file for reading/writing */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.access.tmpfile") FILE *
NOTHROW_RPC(LIBCCALL libc_tmpfile)(void)
/*[[[body:tmpfile]]]*/
{
	CRT_UNIMPLEMENTED("tmpfile"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:tmpfile]]]*/

/*[[[impl:tmpfile64]]]*/
DEFINE_INTERN_ALIAS(libc_tmpfile64,libc_tmpfile);


/*[[[head:fopen,hash:0x5ffa1610]]]*/
/* Create and return a new file-stream for accessing `FILENAME' */
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.access.fopen") FILE *
NOTHROW_RPC(LIBCCALL libc_fopen)(char const *__restrict filename,
                                 char const *__restrict modes)
/*[[[body:fopen]]]*/
{
	fd_t fd;
	FILE *result;
	fd = open(filename, parse_open_modes(modes), 0644);
	if unlikely(fd < 0)
		return NULL;
	result = fdopen(fd, modes);
	if unlikely(!result)
		sys_close(fd);
	return result;
}
/*[[[end:fopen]]]*/

/*[[[head:fdopen,hash:0x566167d6]]]*/
/* Open a new file stream by inheriting a given file descriptor `FD'
 * Note that upon success (`return != NULL'), the given `FD' will be `close()'d once `fclose(return)' is called */
INTERN WUNUSED NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.utility.fdopen") FILE *
NOTHROW_NCX(LIBCCALL libc_fdopen)(fd_t fd,
                                  char const *__restrict modes)
/*[[[body:fdopen]]]*/
{
	FILE *result = (FILE *)calloc(1, sizeof(FILE));
	(void)modes;
	if unlikely(!result)
		goto done;
	result->if_exdata = (struct iofile_data *)calloc(1, sizeof(struct iofile_data));
	if unlikely(!result->if_exdata)
		goto err_r;
	result->if_fd = fd;
	/* Check if the stream handle is a tty the first time it is read from. */
	result->if_flag = IO_LNIFTYY;
	/* Insert the new file stream into the global list of them. */
	atomic_rwlock_write(&libc_ffiles_lock);
	LLIST_INSERT(libc_ffiles, result, if_exdata->io_link);
	atomic_rwlock_endwrite(&libc_ffiles_lock);
done:
	return result;
err_r:
	free(result);
	return NULL;
}
/*[[[end:fdopen]]]*/

/*[[[head:fclose,hash:0x842943de]]]*/
/* Close and destroy a given file `STREAM' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.access.fclose") int
(LIBCCALL libc_fclose)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fclose]]]*/
{
	int result = 0;
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	libc_fdoflush(stream);

	/* Remove the stream from the global list of known files. */
	atomic_rwlock_write(&libc_ffiles_lock);
	if (LLIST_ISBOUND(stream, if_exdata->io_link))
		LLIST_UNLINK(stream, if_exdata->io_link);
	atomic_rwlock_endwrite(&libc_ffiles_lock);

	if (!(stream->if_flag & IO_NOFD))
		sys_close(stream->if_fd);

	/* Free a dynamically allocated buffer. */
	if (stream->if_flag & IO_MALLBUF)
		free(stream->if_base);

	/* Make sure not to free one of the STD streams. */
	if (!(stream >= libc_std_files &&
	      stream < COMPILER_ENDOF(libc_std_files))) {
		/* Free extended file data. */
		free(stream->if_exdata);
		/* Free the file buffer itself. */
		free(stream);
	} else {
		/* Mark STD streams as not having a handle. */
		stream->if_flag |= IO_NOFD;
	}
	return result;
}
/*[[[end:fclose]]]*/

/*[[[head:getchar,hash:0xf34ab87a]]]*/
/* Alias for `fgetc(stdin)' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.read.getc.getchar") int
(LIBCCALL libc_getchar)(void)
		__THROWS(...)
/*[[[body:getchar]]]*/
{
	return fgetc(stdin);
}
/*[[[end:getchar]]]*/

/*[[[head:getchar_unlocked,hash:0xcb95ac1b]]]*/
/* Same as `getchar()', but performs I/O without acquiring a lock to `stdin' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.read.getc.getchar_unlocked") int
(LIBCCALL libc_getchar_unlocked)(void)
		__THROWS(...)
/*[[[body:getchar_unlocked]]]*/
{
	return fgetc_unlocked(stdin);
}
/*[[[end:getchar_unlocked]]]*/

/*[[[head:putchar,hash:0xc03330a3]]]*/
/* Alias for `fputc(CH, stdout)' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.write.putc.putchar") int
(LIBCCALL libc_putchar)(int ch)
		__THROWS(...)
/*[[[body:putchar]]]*/
{
	return fputc(ch, stdout);
}
/*[[[end:putchar]]]*/

/*[[[head:putchar_unlocked,hash:0x256f07ae]]]*/
/* Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.write.putc.putchar_unlocked") int
(LIBCCALL libc_putchar_unlocked)(int ch)
		__THROWS(...)
/*[[[body:putchar_unlocked]]]*/
{
	return fputc_unlocked(ch, stdout);
}
/*[[[end:putchar_unlocked]]]*/


/*[[[head:fputc,hash:0x7622b101]]]*/
/* Write a single character `CH' to `STREAM' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.write.putc.fputc") int
(LIBCCALL libc_fputc)(int ch,
                      FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fputc]]]*/
{
	unsigned char chr = (unsigned char)ch;
	return fwrite(&chr, sizeof(chr), 1, stream) ? ch : EOF;
}
/*[[[end:fputc]]]*/

/*[[[head:fputc_unlocked,hash:0xdfd0a286]]]*/
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.write.putc.fputc_unlocked") int
(LIBCCALL libc_fputc_unlocked)(int ch,
                               FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fputc_unlocked]]]*/
{
	unsigned char chr = (unsigned char)ch;
	return fwrite_unlocked(&chr, sizeof(chr), 1, stream) ? ch : EOF;
}
/*[[[end:fputc_unlocked]]]*/

/*[[[head:fileno,hash:0xf14110c1]]]*/
/* Return the underlying file descriptor number used by `STREAM' */
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.utility.fileno") fd_t
NOTHROW_NCX(LIBCCALL libc_fileno)(FILE *__restrict stream)
/*[[[body:fileno]]]*/
{
	if unlikely(!stream || (stream->if_flag & IO_NOFD))
		return (fd_t)libc_seterrno(EINVAL);
	return ATOMIC_READ(stream->if_fd);
}
/*[[[end:fileno]]]*/




/*[[[head:fputs,hash:0xa50d59de]]]*/
/* Print a given string `STR' to `STREAM'. This is identical to:
 * >> fwrite(str, sizeof(char), strlen(str), stream); */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.write.write.fputs") __STDC_INT_AS_SSIZE_T
(LIBCCALL libc_fputs)(char const *__restrict str,
                      FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fputs]]]*/
{
	__STDC_INT_AS_SIZE_T result;
	result = fwrite(str,
	                sizeof(char),
	                strlen(str),
	                stream);
	return result;
}
/*[[[end:fputs]]]*/

/*[[[head:fputs_unlocked,hash:0x4e1ca02f]]]*/
/* Same as `fputs()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.write.write.fputs_unlocked") __STDC_INT_AS_SIZE_T
(LIBCCALL libc_fputs_unlocked)(char const *__restrict str,
                               FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fputs_unlocked]]]*/
{
	__STDC_INT_AS_SIZE_T result;
	result = fwrite_unlocked(str,
	                         sizeof(char),
	                         strlen(str),
	                         stream);
	return result;
}
/*[[[end:fputs_unlocked]]]*/

/*[[[head:vfprintf,hash:0x559e1675]]]*/
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
INTERN ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.write.printf.vfprintf") __STDC_INT_AS_SSIZE_T
(LIBCCALL libc_vfprintf)(FILE *__restrict stream,
                         char const *__restrict format,
                         va_list args)
		__THROWS(...)
/*[[[body:vfprintf]]]*/
{
	return format_vprintf(&file_printer,
	                      stream,
	                      format,
	                      args);
}
/*[[[end:vfprintf]]]*/

/*[[[head:vfprintf_unlocked,hash:0x41cecdc2]]]*/
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
INTERN ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.write.printf.vfprintf_unlocked") __STDC_INT_AS_SSIZE_T
(LIBCCALL libc_vfprintf_unlocked)(FILE *__restrict stream,
                                  char const *__restrict format,
                                  va_list args)
		__THROWS(...)
/*[[[body:vfprintf_unlocked]]]*/
{
	return format_vprintf(&file_printer_unlocked,
	                      stream,
	                      format,
	                      args);
}
/*[[[end:vfprintf_unlocked]]]*/

PRIVATE ssize_t LIBCCALL vfscanf_ungetc(void *arg, char32_t ch) {
	return ungetc((int)(unsigned int)ch, (FILE *)arg);
}
PRIVATE ssize_t LIBCCALL vfscanf_ungetc_unlocked(void *arg, char32_t ch) {
	return ungetc_unlocked((int)(unsigned int)ch, (FILE *)arg);
}


#if __SIZEOF_SIZE_T__ == __SIZEOF_INT__
#define vfscanf_getc          (*(pformatgetc)&fgetc)
#define vfscanf_getc_unlocked (*(pformatgetc)&fgetc_unlocked)
#else /* __SIZEOF_SIZE_T__ == __SIZEOF_INT__ */
PRIVATE ssize_t LIBCCALL vfscanf_getc(void *arg) {
	return (ssize_t)fgetc((FILE *)arg);
}
PRIVATE ssize_t LIBCCALL vfscanf_getc_unlocked(void *arg) {
	return (ssize_t)fgetc_unlocked((FILE *)arg);
}

#endif /* __SIZEOF_SIZE_T__ != __SIZEOF_INT__ */

/*[[[head:vfscanf,hash:0x623e4278]]]*/
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_LIBC_SCANF(2, 0) WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.read.scanf.vfscanf") __STDC_INT_AS_SIZE_T
(LIBCCALL libc_vfscanf)(FILE *__restrict stream,
                        char const *__restrict format,
                        va_list args)
		__THROWS(...)
/*[[[body:vfscanf]]]*/
{
	return format_vscanf(&vfscanf_getc,
	                     &vfscanf_ungetc,
	                     stream,
	                     format,
	                     args);
}
/*[[[end:vfscanf]]]*/

/*[[[head:vfscanf_unlocked,hash:0xb49fdfb4]]]*/
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_LIBC_SCANF(2, 0) WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.read.scanf.vfscanf_unlocked") __STDC_INT_AS_SIZE_T
(LIBCCALL libc_vfscanf_unlocked)(FILE *__restrict stream,
                                 char const *__restrict format,
                                 va_list args)
		__THROWS(...)
/*[[[body:vfscanf_unlocked]]]*/
{
	return format_vscanf(&vfscanf_getc_unlocked,
	                     &vfscanf_ungetc_unlocked,
	                     stream,
	                     format,
	                     args);
}
/*[[[end:vfscanf_unlocked]]]*/






/*[[[head:fgetc,hash:0xd09c5a4a]]]*/
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.read.getc.fgetc") int
(LIBCCALL libc_fgetc)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fgetc]]]*/
{
	unsigned char result;
	return libc_fread(&result,
	                  sizeof(result),
	                  1,
	                  stream) == 1
	       ? (int)(unsigned int)result
	       : (int)EOF;
}
/*[[[end:fgetc]]]*/

/*[[[head:fgetc_unlocked,hash:0x7583484b]]]*/
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.read.getc.fgetc_unlocked") int
(LIBCCALL libc_fgetc_unlocked)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fgetc_unlocked]]]*/
{
	unsigned char result;
	return libc_fread_unlocked(&result,
	                           sizeof(result),
	                           1,
	                           stream) == 1
	       ? (int)(unsigned int)result
	       : (int)EOF;
}
/*[[[end:fgetc_unlocked]]]*/

/*[[[head:fgets,hash:0xf387cf90]]]*/
/* Read up to `BUFSIZE - 1' bytes of data from `STREAM', storing them into `BUF'
 * stopped when the buffer is full or a line-feed was read (in this case, the
 * line-feed is also written to `BUF')
 * Afterwards, append a trailing NUL-character and re-return `BUF', or return
 * `NULL' if an error occurred. */
INTERN WUNUSED NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.read.read.fgets") char *
(LIBCCALL libc_fgets)(char *__restrict buf,
                      __STDC_INT_AS_SIZE_T bufsize,
                      FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fgets]]]*/
{
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
		libc_seterrno(ERANGE);
		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		int ch = fgetc(stream);
		if (ch == EOF) {
			if (ferror(stream))
				return NULL;
			break;
		}
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = '\n';
			ch = fgetc(stream);
			if (ch == EOF) {
				if (ferror(stream))
					return NULL;
				break;
			}
			if (ch == '\r')
				continue;
		}
		buf[n] = (char)ch;
		if (ch == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}
/*[[[end:fgets]]]*/

/*[[[head:fgets_unlocked,hash:0xbf58dbc4]]]*/
/* Same as `fgets()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTERN WUNUSED NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.read.read.fgets_unlocked") char *
(LIBCCALL libc_fgets_unlocked)(char *__restrict buf,
                               __STDC_INT_AS_SIZE_T bufsize,
                               FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fgets_unlocked]]]*/
{
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
		libc_seterrno(ERANGE);
		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		int ch = fgetc_unlocked(stream);
		if (ch == EOF) {
			if (ferror_unlocked(stream))
				return NULL;
			break;
		}
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = '\n';
			ch = fgetc_unlocked(stream);
			if (ch == EOF) {
				if (ferror_unlocked(stream))
					return NULL;
				break;
			}
			if (ch == '\r')
				continue;
		}
		buf[n] = (char)ch;
		if (ch == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}
/*[[[end:fgets_unlocked]]]*/










/*[[[head:getline,hash:0x89a5b657]]]*/
INTERN WUNUSED NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.read.read.getline") ssize_t
(LIBCCALL libc_getline)(char **__restrict lineptr,
                        size_t *__restrict pcount,
                        FILE *__restrict stream)
		__THROWS(...)
/*[[[body:getline]]]*/
{
	CRT_UNIMPLEMENTED("getline"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getline]]]*/

/*[[[head:getline_unlocked,hash:0x827e7883]]]*/
INTERN WUNUSED NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.read.read.getline_unlocked") ssize_t
(LIBCCALL libc_getline_unlocked)(char **__restrict lineptr,
                                 size_t *__restrict pcount,
                                 FILE *__restrict stream)
		__THROWS(...)
/*[[[body:getline_unlocked]]]*/
{
	CRT_UNIMPLEMENTED("getline_unlocked"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getline_unlocked]]]*/


/*[[[head:getdelim,hash:0x4fd6e8e6]]]*/
INTERN WUNUSED NONNULL((1, 2, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.read.read.getdelim") ssize_t
(LIBCCALL libc_getdelim)(char **__restrict lineptr,
                         size_t *__restrict pcount,
                         int delimiter,
                         FILE *__restrict stream)
		__THROWS(...)
/*[[[body:getdelim]]]*/
{
	CRT_UNIMPLEMENTED("getdelim"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getdelim]]]*/

/*[[[head:getdelim_unlocked,hash:0x1d4c5f5b]]]*/
INTERN WUNUSED NONNULL((1, 2, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.read.read.getdelim_unlocked") ssize_t
(LIBCCALL libc_getdelim_unlocked)(char **__restrict lineptr,
                                  size_t *__restrict pcount,
                                  int delimiter,
                                  FILE *__restrict stream)
		__THROWS(...)
/*[[[body:getdelim_unlocked]]]*/
{
	CRT_UNIMPLEMENTED("getdelim_unlocked"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getdelim_unlocked]]]*/

/*[[[head:popen,hash:0xaad8bdf8]]]*/
/* Open and return a new process I/O stream for executing `COMMAND' */
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.access.popen") FILE *
NOTHROW_RPC(LIBCCALL libc_popen)(char const *command,
                                 char const *modes)
/*[[[body:popen]]]*/
{
	CRT_UNIMPLEMENTED("popen"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:popen]]]*/

/*[[[head:pclose,hash:0xef98a1c2]]]*/
/* Close a process I/O file `STREAM' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.access.pclose") int
NOTHROW_NCX(LIBCCALL libc_pclose)(FILE *stream)
/*[[[body:pclose]]]*/
{
	CRT_UNIMPLEMENTED("pclose"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pclose]]]*/

/*[[[head:fopencookie,hash:0x78415e2c]]]*/
INTERN WUNUSED NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.access.fopencookie") FILE *
NOTHROW_NCX(LIBCCALL libc_fopencookie)(void *__restrict magic_cookie,
                                       char const *__restrict modes,
                                       cookie_io_functions_t io_funcs)
/*[[[body:fopencookie]]]*/
{
	CRT_UNIMPLEMENTED("fopencookie"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:fopencookie]]]*/

/*[[[head:tmpnam_r,hash:0xd1ce7b33]]]*/
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.utility.tmpnam_r") char *
NOTHROW_NCX(LIBCCALL libc_tmpnam_r)(char *buf)
/*[[[body:tmpnam_r]]]*/
{
	CRT_UNIMPLEMENTED("tmpnam_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:tmpnam_r]]]*/

/*[[[head:vasprintf,hash:0x577b8d86]]]*/
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
INTERN ATTR_LIBC_PRINTF(2, 3) WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.heap.strdup.vasprintf") __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc_vasprintf)(char **__restrict pstr,
                                     char const *__restrict format,
                                     va_list args)
/*[[[body:vasprintf]]]*/
/*AUTO*/{
	char *result;
	ssize_t error;
	struct format_aprintf_data data;
	__hybrid_assert(pstr != NULL);
	data.ap_avail = 0;
	data.ap_used  = 0;
	data.ap_base  = NULL;
	error = libc_format_vprintf(&libc_format_aprintf_printer, &data, format, args);
	if unlikely(error < 0) {
		libc_free(data.ap_base);
		return -1;
	}
	result = libc_format_aprintf_pack(&data, NULL);
	if unlikely(!result)
		return -1;
	*pstr = result;
	return (__STDC_INT_AS_SSIZE_T)error;
}
/*[[[end:vasprintf]]]*/

/*[[[head:_wperror,hash:0x1cb1c359]]]*/
INTERN ATTR_COLD
ATTR_WEAK ATTR_SECTION(".text.crt.dos.errno._wperror") void
(LIBCCALL libc__wperror)(char32_t const *__restrict errmsg)
		__THROWS(...)
/*[[[body:_wperror]]]*/
{
	CRT_UNIMPLEMENTED("_wperror"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:_wperror]]]*/

/*[[[head:_fsopen,hash:0x1781bc86]]]*/
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.locked.access._fsopen") FILE *
NOTHROW_RPC(LIBCCALL libc__fsopen)(char const *filename,
                                   char const *modes,
                                   int sflag)
/*[[[body:_fsopen]]]*/
{
	(void)sflag;
	return fopen(filename, modes);
}
/*[[[end:_fsopen]]]*/

/*[[[head:perror,hash:0xc876411c]]]*/
/* Print a given `MESSAGE' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.errno.utility.perror") void
NOTHROW_RPC(LIBCCALL libc_perror)(char const *message)
/*[[[body:perror]]]*/
{
	if (message) {
		fprintf(stderr, "%s: %s\n", message, strerror(errno));
	} else {
		fprintf(stderr, "%s\n", strerror(errno));
	}
}
/*[[[end:perror]]]*/

/*[[[head:fcloseall,hash:0x4e3df054]]]*/
/* Alias for `_fcloseall()' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.utility.fcloseall") int
(LIBCCALL libc_fcloseall)(void)
		__THROWS(...)
/*[[[body:fcloseall]]]*/
{
	CRT_UNIMPLEMENTED("fcloseall"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:fcloseall]]]*/

/*[[[head:fmemopen,hash:0x89257606]]]*/
INTERN WUNUSED NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.access.fmemopen") FILE *
NOTHROW_NCX(LIBCCALL libc_fmemopen)(void *mem,
                                    size_t len,
                                    char const *modes)
/*[[[body:fmemopen]]]*/
{
	CRT_UNIMPLEMENTED("fmemopen"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:fmemopen]]]*/

#if (__SIZEOF_INT__ == __SIZEOF_POINTER__) || \
     defined(__i386__) || defined(__x86_64__)
#define __vdprintf_printer  (*(pformatprinter)(void *)&write)
#else
PRIVATE ATTR_SECTION(".text.crt.io.write.vdprintf")
ssize_t LIBCCALL __vdprintf_printer(void *arg, char const *__restrict data, size_t datalen) {
	return (__ssize_t)write((fd_t)(unsigned int)(uintptr_t)arg,
	                        data,
	                        datalen);
}
#endif

/*[[[head:vdprintf,hash:0x49540983]]]*/
INTERN ATTR_LIBC_PRINTF(2, 0) NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.io.write.vdprintf") __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(LIBCCALL libc_vdprintf)(fd_t fd,
                                    char const *__restrict format,
                                    va_list args)
/*[[[body:vdprintf]]]*/
/*AUTO*/{
	return libc_format_vprintf(&__vdprintf_printer,
	                     (void *)(__UINTPTR_TYPE__)(unsigned int)fd,
	                      format,
	                      args);
}
/*[[[end:vdprintf]]]*/

/*[[[head:obstack_printf,hash:0xd4bbe8a]]]*/
INTERN ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.obstack.obstack_printf") int
NOTHROW_NCX(VLIBCCALL libc_obstack_printf)(struct obstack *__restrict obstack_,
                                           char const *__restrict format,
                                           ...)
/*[[[body:obstack_printf]]]*/
/*AUTO*/{
	int result;
	va_list args;
	va_start(args, format);
	result = libc_obstack_vprintf(obstack_, format, args);
	va_end(args);
	return result;
}
/*[[[end:obstack_printf]]]*/

/*[[[head:_flsbuf,hash:0xb1a46b64]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.locked.write.write._flsbuf") int
(LIBCCALL libc__flsbuf)(int ch,
                        FILE *__restrict stream)
		__THROWS(...)
/*[[[body:_flsbuf]]]*/
{
	CRT_UNIMPLEMENTED("_flsbuf"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_flsbuf]]]*/

/*[[[head:open_memstream,hash:0xcbee42d7]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.access.open_memstream") FILE *
NOTHROW_NCX(LIBCCALL libc_open_memstream)(char **bufloc,
                                          size_t *sizeloc)
/*[[[body:open_memstream]]]*/
{
	CRT_UNIMPLEMENTED("open_memstream"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:open_memstream]]]*/

/*[[[head:_filbuf,hash:0x8ffca692]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.locked.read.read._filbuf") int
(LIBCCALL libc__filbuf)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:_filbuf]]]*/
{
	CRT_UNIMPLEMENTED("_filbuf"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_filbuf]]]*/

/*[[[head:tempnam,hash:0xe5f584b8]]]*/
INTERN ATTR_MALLOC WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.fs.utility.tempnam") char *
NOTHROW_NCX(LIBCCALL libc_tempnam)(char const *dir,
                                   char const *pfx)
/*[[[body:tempnam]]]*/
{
	CRT_UNIMPLEMENTED("tempnam"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:tempnam]]]*/










/*[[[head:rename,hash:0x6e25d971]]]*/
/* Rename a given file `OLDNAME' to `NEWNAME_OR_PATH', or in the event
 * that `NEWNAME_OR_PATH' refers to a directory, place the file within. */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify.rename") int
NOTHROW_RPC(LIBCCALL libc_rename)(char const *oldname,
                                  char const *newname_or_path)
/*[[[body:rename]]]*/
{
	errno_t result;
	result = sys_rename(oldname, newname_or_path);
	return libc_seterrno_syserr(result);
}
/*[[[end:rename]]]*/

/*[[[head:renameat,hash:0xf070a1ec]]]*/
INTERN NONNULL((2, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify.renameat") int
NOTHROW_RPC(LIBCCALL libc_renameat)(fd_t oldfd,
                                    char const *oldname,
                                    fd_t newfd,
                                    char const *newname_or_path)
/*[[[body:renameat]]]*/
{
	errno_t result;
	result = sys_renameat(oldfd,
	                      oldname,
	                      newfd,
	                      newname_or_path);
	return libc_seterrno_syserr(result);
}
/*[[[end:renameat]]]*/

/*[[[head:frenameat,hash:0x4738d690]]]*/
/* @param flags: Set of `0|AT_DOSPATH' */
INTERN NONNULL((2, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify.frenameat") int
NOTHROW_RPC(LIBCCALL libc_frenameat)(fd_t oldfd,
                                     char const *oldname,
                                     fd_t newfd,
                                     char const *newname_or_path,
                                     atflag_t flags)
/*[[[body:frenameat]]]*/
{
	errno_t result;
	result = sys_frenameat(oldfd,
	                       oldname,
	                       newfd,
	                       newname_or_path,
	                       flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:frenameat]]]*/



/*[[[head:tmpnam,hash:0x2976b636]]]*/
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.utility.tmpnam") char *
NOTHROW_NCX(LIBCCALL libc_tmpnam)(char *buf)
/*[[[body:tmpnam]]]*/
{
	CRT_UNIMPLEMENTED("tmpnam"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:tmpnam]]]*/

/*[[[head:_rmtmp,hash:0x5381d93f]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.utility._rmtmp") int
NOTHROW_RPC(LIBCCALL libc__rmtmp)(void)
/*[[[body:_rmtmp]]]*/
{
	CRT_UNIMPLEMENTED("_rmtmp"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_rmtmp]]]*/



/*[[[head:fprintf,hash:0x2bdd0ae6]]]*/
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
INTERN ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.write.printf.fprintf") __STDC_INT_AS_SSIZE_T
(VLIBCCALL libc_fprintf)(FILE *__restrict stream,
                         char const *__restrict format,
                         ...)
		__THROWS(...)
/*[[[body:fprintf]]]*/
/*AUTO*/{
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfprintf(stream, format, args);
	va_end(args);
	return result;
}
/*[[[end:fprintf]]]*/




/*[[[head:obstack_vprintf,hash:0x62da4b93]]]*/
INTERN ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.obstack.obstack_vprintf") int
NOTHROW_NCX(LIBCCALL libc_obstack_vprintf)(struct obstack *__restrict obstack_,
                                           char const *__restrict format,
                                           va_list args)
/*[[[body:obstack_vprintf]]]*/
{
	CRT_UNIMPLEMENTED("obstack_vprintf"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:obstack_vprintf]]]*/

/*[[[head:gets,hash:0x6f2cc4db]]]*/
INTERN WUNUSED ATTR_DEPRECATED("No buffer size checks (use `fgets' instead)") NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.read.read.gets") char *
(LIBCCALL libc_gets)(char *__restrict buf)
		__THROWS(...)
/*[[[body:gets]]]*/
{
	return fgets(buf, (__STDC_INT_AS_SIZE_T)-1, stdin);
}
/*[[[end:gets]]]*/

/*[[[head:asprintf,hash:0x66a39337]]]*/
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
INTERN ATTR_LIBC_PRINTF(2, 3) WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.heap.strdup.asprintf") __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc_asprintf)(char **__restrict pstr,
                                     char const *__restrict format,
                                     ...)
/*[[[body:asprintf]]]*/
/*AUTO*/{
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vasprintf(pstr, format, args);
	va_end(args);
	return result;
}
/*[[[end:asprintf]]]*/

/*[[[head:scanf,hash:0x4154e937]]]*/
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_LIBC_SCANF(1, 2) WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.read.scanf.scanf") __STDC_INT_AS_SIZE_T
(VLIBCCALL libc_scanf)(char const *__restrict format,
                       ...)
		__THROWS(...)
/*[[[body:scanf]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vscanf(format, args);
	va_end(args);
	return result;
}
/*[[[end:scanf]]]*/
















/*[[[head:tmpfile_s,hash:0x51d2fbfb]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.locked.access.tmpfile_s") errno_t
NOTHROW_RPC(LIBCCALL libc_tmpfile_s)(FILE **pstream)
/*[[[body:tmpfile_s]]]*/
{
	FILE *result;
	if unlikely(!pstream)
		return EINVAL;
	result = tmpfile64();
	if unlikely(!result)
		return libc_geterrno();
	*pstream = result;
	return EOK;
}
/*[[[end:tmpfile_s]]]*/

/*[[[head:fopen_s,hash:0x77c84fb2]]]*/
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.locked.access.fopen_s") errno_t
NOTHROW_RPC(LIBCCALL libc_fopen_s)(FILE **pstream,
                                   char const *filename,
                                   char const *modes)
/*[[[body:fopen_s]]]*/
{
	FILE *result;
	if unlikely(!pstream || !filename || !modes)
		return EINVAL;
	result = fopen64(filename, modes);
	if unlikely(!result)
		return libc_geterrno();
	*pstream = result;
	return EOK;
}
/*[[[end:fopen_s]]]*/

/*[[[head:tmpnam_s,hash:0xe4afdc1e]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.utility.tmpnam_s") errno_t
NOTHROW_NCX(LIBCCALL libc_tmpnam_s)(char *__restrict buf,
                                    rsize_t bufsize)
/*[[[body:tmpnam_s]]]*/
{
	if unlikely(!buf)
		return EINVAL;
	if unlikely(bufsize < L_tmpnam)
		return ERANGE; /* XXX: Is this what dos does? */
	if unlikely(!tmpnam(buf))
		return libc_geterrno();
	return EOK;
}
/*[[[end:tmpnam_s]]]*/

/*[[[head:sscanf_s,hash:0xfb81997]]]*/
INTERN ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.static.format.scanf.sscanf_s") __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc_sscanf_s)(char const *__restrict input,
                                     char const *__restrict format,
                                     ...)
/*[[[body:sscanf_s]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vsscanf_s(input, format, args);
	va_end(args);
	return result;
}
/*[[[end:sscanf_s]]]*/

/*[[[impl:vscanf_s]]]*/
/*[[[impl:fscanf_s]]]*/
DEFINE_INTERN_ALIAS(libc_vscanf_s, libc_vscanf);
DEFINE_INTERN_ALIAS(libc_fscanf_s, libc_fscanf);



/*[[[head:printf,hash:0xbce0793a]]]*/
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
INTERN ATTR_LIBC_PRINTF(1, 2) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.write.printf.printf") __STDC_INT_AS_SSIZE_T
(VLIBCCALL libc_printf)(char const *__restrict format,
                        ...)
		__THROWS(...)
/*[[[body:printf]]]*/
/*AUTO*/{
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vprintf(format, args);
	va_end(args);
	return result;
}
/*[[[end:printf]]]*/

/*[[[head:dprintf,hash:0x4c8cc0d1]]]*/
INTERN ATTR_LIBC_PRINTF(2, 3) NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.io.write.dprintf") __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(VLIBCCALL libc_dprintf)(fd_t fd,
                                    char const *__restrict format,
                                    ...)
/*[[[body:dprintf]]]*/
/*AUTO*/{
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vdprintf(fd, format, args);
	va_end(args);
	return result;
}
/*[[[end:dprintf]]]*/



/*[[[head:vsnprintf_s,hash:0xab7ef9cf]]]*/
INTERN ATTR_LIBC_PRINTF(4, 0) NONNULL((4))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.static.format.printf.vsnprintf_s") __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc_vsnprintf_s)(char *__restrict buf,
                                       size_t bufsize,
                                       size_t buflen,
                                       char const *__restrict format,
                                       va_list args)
/*[[[body:vsnprintf_s]]]*/
{
	return vsnprintf(buf, buflen < bufsize ? buflen : bufsize, format, args);
}
/*[[[end:vsnprintf_s]]]*/

/*[[[head:_fread_nolock_s,hash:0x1cb2185d]]]*/
INTERN WUNUSED NONNULL((1, 5))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.unlocked.read.read._fread_nolock_s") size_t
(LIBCCALL libc__fread_nolock_s)(void *__restrict buf,
                                size_t bufsize,
                                size_t elemsize,
                                size_t elemcount,
                                FILE *__restrict stream)
		__THROWS(...)
/*[[[body:_fread_nolock_s]]]*/
{
	size_t reqbuf;
	if (OVERFLOW_UMUL(elemsize, elemcount, &reqbuf) ||
	    reqbuf > bufsize) {
		libc_seterrno(ERANGE);
		return 0;
	}
	if unlikely(!stream || !buf) {
		libc_seterrno(EINVAL);
		return 0;
	}
	return fread_unlocked(buf, elemsize, elemcount, stream);
}
/*[[[end:_fread_nolock_s]]]*/

/*[[[impl:vsscanf_s]]]*/
DEFINE_INTERN_ALIAS(libc_vsscanf_s,libc_vsscanf);

/*[[[head:fread_s,hash:0x3787766b]]]*/
INTERN WUNUSED NONNULL((1, 5))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.locked.read.read.fread_s") size_t
NOTHROW_RPC(LIBCCALL libc_fread_s)(void *__restrict buf,
                                   size_t bufsize,
                                   size_t elemsize,
                                   size_t elemcount,
                                   FILE *__restrict stream)
/*[[[body:fread_s]]]*/
{
	size_t reqbuf;
	if (OVERFLOW_UMUL(elemsize, elemcount, &reqbuf) ||
	    reqbuf > bufsize) {
		libc_seterrno(ERANGE);
		return 0;
	}
	if unlikely(!stream || !buf) {
		libc_seterrno(EINVAL);
		return 0;
	}
	return fread(buf, elemsize, elemcount, stream);
}
/*[[[end:fread_s]]]*/

/*[[[head:gets_s,hash:0x51e82e80]]]*/
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.locked.read.read.gets_s") char *
NOTHROW_RPC(LIBCCALL libc_gets_s)(char *__restrict buf,
                                  rsize_t bufsize)
/*[[[body:gets_s]]]*/
{
	if unlikely(!buf) {
		libc_seterrno(EINVAL);
		return NULL;
	}
	return fgets(buf, bufsize, stdin);
}
/*[[[end:gets_s]]]*/

/*[[[head:freopen_s,hash:0x7eeee08e]]]*/
INTERN NONNULL((1, 2, 3, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.locked.access.freopen_s") errno_t
NOTHROW_RPC(LIBCCALL libc_freopen_s)(FILE **pstream,
                                     char const *filename,
                                     char const *modes,
                                     FILE *oldstream)
/*[[[body:freopen_s]]]*/
{
	if unlikely(!pstream || !filename || !modes || !oldstream)
		return EINVAL;
	oldstream = freopen(filename, modes, oldstream);
	if unlikely(!oldstream)
		return libc_geterrno();
	*pstream = oldstream;
	return EOK;
}
/*[[[end:freopen_s]]]*/

/*[[[impl:vfscanf_s]]]*/
/*[[[impl:scanf_s]]]*/
DEFINE_INTERN_ALIAS(libc_vfscanf_s, libc_vfscanf);
DEFINE_INTERN_ALIAS(libc_scanf_s, libc_scanf);


/*[[[head:_vfprintf_p,hash:0x730e7579]]]*/
INTERN ATTR_LIBC_PRINTF_P(2, 0) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.static.format.printf._vfprintf_p") __STDC_INT_AS_SIZE_T
(LIBCCALL libc__vfprintf_p)(FILE *__restrict stream,
                            char const *__restrict format,
                            va_list args)
		__THROWS(...)
/*[[[body:_vfprintf_p]]]*/
/*AUTO*/{
	/* TODO */
	(void)stream;
	(void)format;
	(void)args;
	return 0;
}
/*[[[end:_vfprintf_p]]]*/

/*[[[head:_vprintf_p,hash:0x92ebfa56]]]*/
INTERN ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.static.format.printf._vprintf_p") __STDC_INT_AS_SIZE_T
(LIBCCALL libc__vprintf_p)(char const *__restrict format,
                           va_list args)
		__THROWS(...)
/*[[[body:_vprintf_p]]]*/
{
	return _vfprintf_p(stdout, format, args);
}
/*[[[end:_vprintf_p]]]*/

/*[[[head:_fprintf_p,hash:0x5a80e98f]]]*/
INTERN ATTR_LIBC_PRINTF_P(2, 3) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.static.format.printf._fprintf_p") __STDC_INT_AS_SIZE_T
(VLIBCCALL libc__fprintf_p)(FILE *__restrict stream,
                            char const *__restrict format,
                            ...)
		__THROWS(...)
/*[[[body:_fprintf_p]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vfprintf_p(stream, format, args);
	va_end(args);
	return result;
}
/*[[[end:_fprintf_p]]]*/

/*[[[head:fscanf,hash:0x54064e98]]]*/
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_LIBC_SCANF(2, 3) WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.read.scanf.fscanf") __STDC_INT_AS_SIZE_T
(VLIBCCALL libc_fscanf)(FILE *__restrict stream,
                        char const *__restrict format,
                        ...)
		__THROWS(...)
/*[[[body:fscanf]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfscanf(stream, format, args);
	va_end(args);
	return result;
}
/*[[[end:fscanf]]]*/

/*[[[head:_printf_p,hash:0x40f43533]]]*/
INTERN ATTR_LIBC_PRINTF_P(1, 2) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.static.format.printf._printf_p") __STDC_INT_AS_SIZE_T
(VLIBCCALL libc__printf_p)(char const *__restrict format,
                           ...)
		__THROWS(...)
/*[[[body:_printf_p]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vprintf_p(format, args);
	va_end(args);
	return result;
}
/*[[[end:_printf_p]]]*/





/*[[[head:_vprintf_l,hash:0x2b8e84ac]]]*/
INTERN ATTR_LIBC_PRINTF(1, 0) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf._vprintf_l") __STDC_INT_AS_SIZE_T
(LIBCCALL libc__vprintf_l)(char const *__restrict format,
                           locale_t locale,
                           va_list args)
		__THROWS(...)
/*[[[body:_vprintf_l]]]*/
{
	(void)locale;
	return vprintf(format, args);
}
/*[[[end:_vprintf_l]]]*/

/*[[[head:_fprintf_s_l,hash:0x83a38f55]]]*/
INTERN ATTR_LIBC_PRINTF(2, 4) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf._fprintf_s_l") __STDC_INT_AS_SIZE_T
(VLIBCCALL libc__fprintf_s_l)(FILE *__restrict stream,
                              char const *__restrict format,
                              locale_t locale,
                              ...)
		__THROWS(...)
/*[[[body:_fprintf_s_l]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfprintf_s_l(stream, format, locale, args);
	va_end(args);
	return result;
}
/*[[[end:_fprintf_s_l]]]*/

/*[[[head:_vscanf_l,hash:0x3a1383d]]]*/
INTERN ATTR_LIBC_SCANF(1, 3) WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf._vscanf_l") __STDC_INT_AS_SIZE_T
(LIBCCALL libc__vscanf_l)(char const *__restrict format,
                          locale_t locale,
                          va_list args)
		__THROWS(...)
/*[[[body:_vscanf_l]]]*/
{
	(void)locale;
	return vscanf(format, args);
}
/*[[[end:_vscanf_l]]]*/

/*[[[head:_vfscanf_l,hash:0x2fafcafc]]]*/
INTERN ATTR_LIBC_SCANF(2, 4) WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf._vfscanf_l") __STDC_INT_AS_SIZE_T
(LIBCCALL libc__vfscanf_l)(FILE *__restrict stream,
                           char const *__restrict format,
                           locale_t locale,
                           va_list args)
		__THROWS(...)
/*[[[body:_vfscanf_l]]]*/
{
	(void)locale;
	return vfscanf(stream, format, args);
}
/*[[[end:_vfscanf_l]]]*/

/*[[[head:_fscanf_l,hash:0x3eccb4a3]]]*/
INTERN ATTR_LIBC_SCANF(2, 4) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf._fscanf_l") __STDC_INT_AS_SIZE_T
(VLIBCCALL libc__fscanf_l)(FILE *__restrict stream,
                           char const *__restrict format,
                           locale_t locale,
                           ...)
		__THROWS(...)
/*[[[body:_fscanf_l]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfscanf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
/*[[[end:_fscanf_l]]]*/

/*[[[head:_scanf_l,hash:0xd849aefa]]]*/
INTERN ATTR_LIBC_SCANF(1, 3) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf._scanf_l") __STDC_INT_AS_SIZE_T
(VLIBCCALL libc__scanf_l)(char const *__restrict format,
                          locale_t locale,
                          ...)
		__THROWS(...)
/*[[[body:_scanf_l]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vscanf_l(format, locale, args);
	va_end(args);
	return result;
}
/*[[[end:_scanf_l]]]*/

/*[[[head:_vprintf_p_l,hash:0x5484e890]]]*/
INTERN ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf._vprintf_p_l") __STDC_INT_AS_SIZE_T
(LIBCCALL libc__vprintf_p_l)(char const *__restrict format,
                             locale_t locale,
                             va_list args)
		__THROWS(...)
/*[[[body:_vprintf_p_l]]]*/
{
	(void)locale;
	return _vprintf_p(format, args);
}
/*[[[end:_vprintf_p_l]]]*/

/*[[[head:_printf_p_l,hash:0x46ec5b76]]]*/
INTERN ATTR_LIBC_PRINTF_P(1, 3) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf._printf_p_l") __STDC_INT_AS_SIZE_T
(VLIBCCALL libc__printf_p_l)(char const *__restrict format,
                             locale_t locale,
                             ...)
		__THROWS(...)
/*[[[body:_printf_p_l]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vprintf_p_l(format, locale, args);
	va_end(args);
	return result;
}
/*[[[end:_printf_p_l]]]*/

/*[[[head:_printf_s_l,hash:0x28b9cdff]]]*/
INTERN ATTR_LIBC_PRINTF(1, 3) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf._printf_s_l") __STDC_INT_AS_SIZE_T
(VLIBCCALL libc__printf_s_l)(char const *__restrict format,
                             locale_t locale,
                             ...)
		__THROWS(...)
/*[[[body:_printf_s_l]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vprintf_s_l(format, locale, args);
	va_end(args);
	return result;
}
/*[[[end:_printf_s_l]]]*/

/*[[[head:_printf_l,hash:0x8e3f89d4]]]*/
INTERN ATTR_LIBC_PRINTF(1, 3) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf._printf_l") __STDC_INT_AS_SIZE_T
(VLIBCCALL libc__printf_l)(char const *__restrict format,
                           locale_t locale,
                           ...)
		__THROWS(...)
/*[[[body:_printf_l]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vprintf_l(format, locale, args);
	va_end(args);
	return result;
}
/*[[[end:_printf_l]]]*/

/*[[[head:_vfprintf_l,hash:0x240ba835]]]*/
INTERN ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf._vfprintf_l") __STDC_INT_AS_SIZE_T
(LIBCCALL libc__vfprintf_l)(FILE *__restrict stream,
                            char const *__restrict format,
                            locale_t locale,
                            va_list args)
		__THROWS(...)
/*[[[body:_vfprintf_l]]]*/
{
	(void)locale;
	return vfprintf(stream, format, args);
}
/*[[[end:_vfprintf_l]]]*/

/*[[[head:_fprintf_p_l,hash:0x627e934b]]]*/
INTERN ATTR_LIBC_PRINTF_P(2, 4) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf._fprintf_p_l") __STDC_INT_AS_SIZE_T
(VLIBCCALL libc__fprintf_p_l)(FILE *__restrict stream,
                              char const *__restrict format,
                              locale_t locale,
                              ...)
		__THROWS(...)
/*[[[body:_fprintf_p_l]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfprintf_p_l(stream, format, locale, args);
	va_end(args);
	return result;
}
/*[[[end:_fprintf_p_l]]]*/

/*[[[head:_vfprintf_p_l,hash:0xeb18d9f2]]]*/
INTERN ATTR_LIBC_PRINTF_P(2, 0) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf._vfprintf_p_l") __STDC_INT_AS_SIZE_T
(LIBCCALL libc__vfprintf_p_l)(FILE *__restrict stream,
                              char const *__restrict format,
                              locale_t locale,
                              va_list args)
		__THROWS(...)
/*[[[body:_vfprintf_p_l]]]*/
{
	(void)locale;
	return _vfprintf_p(stream, format, args);
}
/*[[[end:_vfprintf_p_l]]]*/

/*[[[head:_fprintf_l,hash:0xd39659d8]]]*/
INTERN ATTR_LIBC_PRINTF(2, 4) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf._fprintf_l") __STDC_INT_AS_SIZE_T
(VLIBCCALL libc__fprintf_l)(FILE *__restrict stream,
                            char const *__restrict format,
                            locale_t locale,
                            ...)
		__THROWS(...)
/*[[[body:_fprintf_l]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfprintf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
/*[[[end:_fprintf_l]]]*/

/*[[[head:vscanf,hash:0xde6255c2]]]*/
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_LIBC_SCANF(1, 0) WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.read.scanf.vscanf") __STDC_INT_AS_SIZE_T
(LIBCCALL libc_vscanf)(char const *__restrict format,
                       va_list args)
		__THROWS(...)
/*[[[body:vscanf]]]*/
{
	return vfscanf(stdin, format, args);
}
/*[[[end:vscanf]]]*/

/*[[[head:vscanf_unlocked,hash:0x12216dc3]]]*/
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_LIBC_SCANF(1, 0) WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.read.scanf.vscanf_unlocked") __STDC_INT_AS_SIZE_T
(LIBCCALL libc_vscanf_unlocked)(char const *__restrict format,
                                va_list args)
		__THROWS(...)
/*[[[body:vscanf_unlocked]]]*/
{
	return vfscanf_unlocked(stdin, format, args);
}
/*[[[end:vscanf_unlocked]]]*/

/*[[[head:vprintf,hash:0xeadc14c3]]]*/
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
INTERN ATTR_LIBC_PRINTF(1, 0) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.write.printf.vprintf") __STDC_INT_AS_SSIZE_T
(LIBCCALL libc_vprintf)(char const *__restrict format,
                        va_list args)
		__THROWS(...)
/*[[[body:vprintf]]]*/
{
	return vfprintf(stdout, format, args);
}
/*[[[end:vprintf]]]*/


/*[[[head:vprintf_unlocked,hash:0x86105d48]]]*/
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
INTERN ATTR_LIBC_PRINTF(1, 0) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.write.printf.vprintf_unlocked") __STDC_INT_AS_SSIZE_T
(LIBCCALL libc_vprintf_unlocked)(char const *__restrict format,
                                 va_list args)
		__THROWS(...)
/*[[[body:vprintf_unlocked]]]*/
{
	return vfprintf_unlocked(stdout, format, args);
}
/*[[[end:vprintf_unlocked]]]*/

/*[[[head:printf_unlocked,hash:0x2f89fbf1]]]*/
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
INTERN ATTR_LIBC_PRINTF(1, 2) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.write.printf.printf_unlocked") __STDC_INT_AS_SSIZE_T
(VLIBCCALL libc_printf_unlocked)(char const *__restrict format,
                                 ...)
		__THROWS(...)
/*[[[body:printf_unlocked]]]*/
{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = vfprintf_unlocked(stdout, format, args);
	va_end(args);
	return result;
}
/*[[[end:printf_unlocked]]]*/

/*[[[head:fprintf_unlocked,hash:0x5b34db69]]]*/
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
INTERN ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.write.printf.fprintf_unlocked") __STDC_INT_AS_SSIZE_T
(VLIBCCALL libc_fprintf_unlocked)(FILE *__restrict stream,
                                  char const *__restrict format,
                                  ...)
		__THROWS(...)
/*[[[body:fprintf_unlocked]]]*/
{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = vfprintf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
/*[[[end:fprintf_unlocked]]]*/

/*[[[head:fscanf_unlocked,hash:0x34676b76]]]*/
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_LIBC_SCANF(2, 3) WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.read.scanf.fscanf_unlocked") __STDC_INT_AS_SIZE_T
(VLIBCCALL libc_fscanf_unlocked)(FILE *__restrict stream,
                                 char const *__restrict format,
                                 ...)
		__THROWS(...)
/*[[[body:fscanf_unlocked]]]*/
{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = vfscanf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
/*[[[end:fscanf_unlocked]]]*/

/*[[[head:scanf_unlocked,hash:0xce425ccd]]]*/
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_LIBC_SCANF(1, 2) WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.read.scanf.scanf_unlocked") __STDC_INT_AS_SIZE_T
(VLIBCCALL libc_scanf_unlocked)(char const *__restrict format,
                                ...)
		__THROWS(...)
/*[[[body:scanf_unlocked]]]*/
{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = vfscanf_unlocked(stdin, format, args);
	va_end(args);
	return result;
}
/*[[[end:scanf_unlocked]]]*/

/*[[[head:_get_output_format,hash:0x7d4633da]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.utility._get_output_format") uint32_t
NOTHROW_NCX(LIBCCALL libc__get_output_format)(void)
/*[[[body:_get_output_format]]]*/
{
	CRT_UNIMPLEMENTED("_get_output_format"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_get_output_format]]]*/

/*[[[head:_set_output_format,hash:0x6d1b018b]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.utility._set_output_format") uint32_t
NOTHROW_NCX(LIBCCALL libc__set_output_format)(uint32_t format)
/*[[[body:_set_output_format]]]*/
{
	CRT_UNIMPLEMENTED("_set_output_format"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_set_output_format]]]*/

/*[[[head:_getmaxstdio,hash:0x9e22521a]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.utility._getmaxstdio") int
NOTHROW_NCX(LIBCCALL libc__getmaxstdio)(void)
/*[[[body:_getmaxstdio]]]*/
{
	CRT_UNIMPLEMENTED("_getmaxstdio"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_getmaxstdio]]]*/

/*[[[head:_setmaxstdio,hash:0x28b688d9]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.utility._setmaxstdio") int
NOTHROW_NCX(LIBCCALL libc__setmaxstdio)(int val)
/*[[[body:_setmaxstdio]]]*/
{
	CRT_UNIMPLEMENTED("_setmaxstdio"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_setmaxstdio]]]*/

/*[[[head:_get_printf_count_output,hash:0x5127be1c]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.utility._get_printf_count_output") int
NOTHROW_NCX(LIBCCALL libc__get_printf_count_output)(void)
/*[[[body:_get_printf_count_output]]]*/
{
	CRT_UNIMPLEMENTED("_get_printf_count_output"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_get_printf_count_output]]]*/

/*[[[head:_set_printf_count_output,hash:0x7a39813c]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.utility._set_printf_count_output") int
NOTHROW_NCX(LIBCCALL libc__set_printf_count_output)(int val)
/*[[[body:_set_printf_count_output]]]*/
{
	CRT_UNIMPLEMENTED("_set_printf_count_output"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_set_printf_count_output]]]*/

/*[[[head:DOS$_wperror,hash:0x786dcf26]]]*/
INTERN ATTR_COLD
ATTR_WEAK ATTR_SECTION(".text.crt.dos.errno._wperror") void
(LIBDCALL libd__wperror)(char16_t const *__restrict errmsg)
		__THROWS(...)
/*[[[body:DOS$_wperror]]]*/
{
	CRT_UNIMPLEMENTED("_wperror"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:DOS$_wperror]]]*/

PRIVATE ATTR_SECTION(".bss.crt.io.tty.cuserid_buffer") char cuserid_buffer[L_cuserid];

/*[[[head:cuserid,hash:0x47205402]]]*/
/* Return the name of the current user (`getpwuid(geteuid())'), storing
 * that name in `S'. When `S' is NULL, a static buffer is used instead */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.io.tty.cuserid") char *
NOTHROW_NCX(LIBCCALL libc_cuserid)(char *s)
/*[[[body:cuserid]]]*/
{
	char buf[NSS_BUFLEN_PASSWD];
	struct passwd pwent, *pwptr;
	if (getpwuid_r(geteuid(),
	               &pwent,
	               buf,
	               sizeof(buf),
	               &pwptr) ||
	    pwptr == NULL) {
		if (s != NULL)
			s[0] = '\0';
		return s;
	}
	if (s == NULL)
		s = cuserid_buffer;
	s[L_cuserid - 1] = '\0';
	return strncpy(s, pwptr->pw_name, L_cuserid - 1);
}
/*[[[end:cuserid]]]*/

/*[[[head:fdreopen,hash:0xd2bb34b]]]*/
/* Re-open the given `STREAM' as a file-stream for accessing `FD' */
INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.access.fdreopen") FILE *
NOTHROW_RPC(LIBCCALL libc_fdreopen)(fd_t fd,
                                    char const *__restrict modes,
                                    FILE *__restrict stream)
/*[[[body:fdreopen]]]*/
{
	fd_t oldfd;
	(void)modes;
	if unlikely(!stream) {
		libc_seterrno(EINVAL);
		goto done;
	}
	file_write(stream);
	oldfd = stream->if_fd;
	if unlikely(fd == oldfd) {
		file_endwrite(stream);
		libc_seterrno(EBADF);
		stream = NULL;
		goto done;
	}
	stream->if_fd   = fd;
	stream->if_flag = IO_LNIFTYY;
	file_endwrite(stream);
	sys_close(oldfd);
done:
	return stream;
}
/*[[[end:fdreopen]]]*/

/*[[[head:fdreopen_unlocked,hash:0x1b12f468]]]*/
/* Re-open the given `STREAM' as a file-stream for accessing `FD' */
INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.access.fdreopen_unlocked") FILE *
NOTHROW_RPC(LIBCCALL libc_fdreopen_unlocked)(fd_t fd,
                                             char const *__restrict modes,
                                             FILE *__restrict stream)
/*[[[body:fdreopen_unlocked]]]*/
{
	fd_t oldfd;
	(void)modes;
	if unlikely(!stream) {
		libc_seterrno(EINVAL);
		goto done;
	}
	oldfd = stream->if_fd;
	if unlikely(fd == oldfd) {
		libc_seterrno(EBADF);
		stream = NULL;
		goto done;
	}
	stream->if_fd   = fd;
	stream->if_flag = IO_LNIFTYY;
	sys_close(oldfd);
done:
	return stream;
}
/*[[[end:fdreopen_unlocked]]]*/

/*[[[head:freopen,hash:0x1af30efd]]]*/
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.access.freopen") FILE *
NOTHROW_RPC(LIBCCALL libc_freopen)(char const *__restrict filename,
                                   char const *__restrict modes,
                                   FILE *__restrict stream)
/*[[[body:freopen]]]*/
{
	fd_t fd;
	FILE *result;
	fd = open(filename, parse_open_modes(modes), 0644);
	if unlikely(fd < 0)
		return NULL;
	result = fdreopen(fd, modes, stream);
	if unlikely(!result)
		sys_close(fd);
	return result;
}
/*[[[end:freopen]]]*/

/*[[[head:freopen_unlocked,hash:0x1e12fcfe]]]*/
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.access.freopen_unlocked") FILE *
NOTHROW_RPC(LIBCCALL libc_freopen_unlocked)(char const *__restrict filename,
                                            char const *__restrict modes,
                                            FILE *__restrict stream)
/*[[[body:freopen_unlocked]]]*/
{
	fd_t fd;
	FILE *result;
	fd = open(filename, parse_open_modes(modes), 0644);
	if unlikely(fd < 0)
		return NULL;
	result = fdreopen_unlocked(fd, modes, stream);
	if unlikely(!result)
		sys_close(fd);
	return result;
}
/*[[[end:freopen_unlocked]]]*/

/*[[[impl:fopen64]]]*/
/*[[[impl:freopen64]]]*/
/*[[[impl:freopen64_unlocked]]]*/
DEFINE_INTERN_ALIAS(libc_freopen64, libc_freopen);
DEFINE_INTERN_ALIAS(libc_freopen64_unlocked, libc_freopen_unlocked);
DEFINE_INTERN_ALIAS(libc_fopen64, libc_fopen);

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0xc341667d]]]*/
#undef fprintf
#undef fprintf_unlocked
#undef fprintf_s
#undef printf
#undef printf_unlocked
#undef printf_s
#undef fscanf
#undef fscanf_unlocked
#undef scanf
#undef scanf_unlocked
#undef dprintf
#undef obstack_printf
#undef asprintf
#undef __asprintf
#undef fprintf_unlocked
#undef printf_unlocked
#undef fscanf_unlocked
#undef scanf_unlocked
#undef _scanf_l
#undef _scanf_s_l
#undef _fscanf_l
#undef _fscanf_s_l
#undef _printf_l
#undef _printf_s_l
#undef _printf_p
#undef _printf_p_l
#undef _fprintf_l
#undef _fprintf_s_l
#undef _fprintf_p
#undef _fprintf_p_l
#undef fscanf_s
#undef scanf_s
#undef sscanf_s
DEFINE_PUBLIC_WEAK_ALIAS(remove, libc_remove);
DEFINE_PUBLIC_WEAK_ALIAS(rename, libc_rename);
DEFINE_PUBLIC_WEAK_ALIAS(tmpnam, libc_tmpnam);
DEFINE_PUBLIC_WEAK_ALIAS(fclose, libc_fclose);
DEFINE_PUBLIC_WEAK_ALIAS(_fclose_nolock, libc_fclose);
DEFINE_PUBLIC_WEAK_ALIAS(fflush, libc_fflush);
DEFINE_PUBLIC_WEAK_ALIAS(fflush_unlocked, libc_fflush);
DEFINE_PUBLIC_WEAK_ALIAS(_fflush_nolock, libc_fflush);
DEFINE_PUBLIC_WEAK_ALIAS(setbuf, libc_setbuf);
DEFINE_PUBLIC_WEAK_ALIAS(setvbuf, libc_setvbuf);
DEFINE_PUBLIC_WEAK_ALIAS(setvbuf_unlocked, libc_setvbuf);
DEFINE_PUBLIC_WEAK_ALIAS(fgetc, libc_fgetc);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_getc, libc_fgetc);
DEFINE_PUBLIC_WEAK_ALIAS(getc, libc_fgetc);
DEFINE_PUBLIC_WEAK_ALIAS(getchar, libc_getchar);
DEFINE_PUBLIC_WEAK_ALIAS(_fgetchar, libc_getchar);
DEFINE_PUBLIC_WEAK_ALIAS(fputc, libc_fputc);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_putc, libc_fputc);
DEFINE_PUBLIC_WEAK_ALIAS(putc, libc_fputc);
DEFINE_PUBLIC_WEAK_ALIAS(putchar, libc_putchar);
DEFINE_PUBLIC_WEAK_ALIAS(_fputchar, libc_putchar);
DEFINE_PUBLIC_WEAK_ALIAS(fgets, libc_fgets);
DEFINE_PUBLIC_WEAK_ALIAS(fputs, libc_fputs);
DEFINE_PUBLIC_WEAK_ALIAS(puts, libc_puts);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_puts, libc_puts);
DEFINE_PUBLIC_WEAK_ALIAS(puts_unlocked, libc_puts);
DEFINE_PUBLIC_WEAK_ALIAS(ungetc, libc_ungetc);
DEFINE_PUBLIC_WEAK_ALIAS(ungetc_unlocked, libc_ungetc);
DEFINE_PUBLIC_WEAK_ALIAS(_ungetc_nolock, libc_ungetc);
DEFINE_PUBLIC_WEAK_ALIAS(fread, libc_fread);
DEFINE_PUBLIC_WEAK_ALIAS(fwrite, libc_fwrite);
DEFINE_PUBLIC_WEAK_ALIAS(fseek, libc_fseek);
DEFINE_PUBLIC_WEAK_ALIAS(fseek_unlocked, libc_fseek);
DEFINE_PUBLIC_WEAK_ALIAS(_fseek_nolock, libc_fseek);
DEFINE_PUBLIC_WEAK_ALIAS(ftell, libc_ftell);
DEFINE_PUBLIC_WEAK_ALIAS(ftell_unlocked, libc_ftell);
DEFINE_PUBLIC_WEAK_ALIAS(_ftell_nolock, libc_ftell);
DEFINE_PUBLIC_WEAK_ALIAS(rewind, libc_rewind);
DEFINE_PUBLIC_WEAK_ALIAS(rewind_unlocked, libc_rewind);
DEFINE_PUBLIC_WEAK_ALIAS(clearerr, libc_clearerr);
DEFINE_PUBLIC_WEAK_ALIAS(clearerr_unlocked, libc_clearerr);
DEFINE_PUBLIC_WEAK_ALIAS(feof, libc_feof);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_feof, libc_feof);
DEFINE_PUBLIC_WEAK_ALIAS(feof_unlocked, libc_feof);
DEFINE_PUBLIC_WEAK_ALIAS(ferror, libc_ferror);
DEFINE_PUBLIC_WEAK_ALIAS(ferror_unlocked, libc_ferror);
DEFINE_PUBLIC_WEAK_ALIAS(perror, libc_perror);
DEFINE_PUBLIC_WEAK_ALIAS(tmpfile, libc_tmpfile);
DEFINE_PUBLIC_WEAK_ALIAS(fopen, libc_fopen);
DEFINE_PUBLIC_WEAK_ALIAS(fopen64, libc_fopen);
DEFINE_PUBLIC_WEAK_ALIAS(freopen, libc_freopen);
DEFINE_PUBLIC_WEAK_ALIAS(freopen64, libc_freopen);
DEFINE_PUBLIC_WEAK_ALIAS(freopen_unlocked, libc_freopen);
DEFINE_PUBLIC_WEAK_ALIAS(fgetpos, libc_fgetpos);
DEFINE_PUBLIC_WEAK_ALIAS(fgetpos_unlocked, libc_fgetpos);
DEFINE_PUBLIC_WEAK_ALIAS(fsetpos, libc_fsetpos);
DEFINE_PUBLIC_WEAK_ALIAS(fsetpos_unlocked, libc_fsetpos);
DEFINE_PUBLIC_WEAK_ALIAS(vfprintf, libc_vfprintf);
DEFINE_PUBLIC_WEAK_ALIAS(vfprintf_unlocked, libc_vfprintf);
DEFINE_PUBLIC_WEAK_ALIAS(vfprintf_s, libc_vfprintf);
DEFINE_PUBLIC_WEAK_ALIAS(fprintf, libc_fprintf);
DEFINE_PUBLIC_WEAK_ALIAS(fprintf_unlocked, libc_fprintf);
DEFINE_PUBLIC_WEAK_ALIAS(fprintf_s, libc_fprintf);
DEFINE_PUBLIC_WEAK_ALIAS(vprintf, libc_vprintf);
DEFINE_PUBLIC_WEAK_ALIAS(vprintf_unlocked, libc_vprintf);
DEFINE_PUBLIC_WEAK_ALIAS(vprintf_s, libc_vprintf);
DEFINE_PUBLIC_WEAK_ALIAS(printf, libc_printf);
DEFINE_PUBLIC_WEAK_ALIAS(printf_unlocked, libc_printf);
DEFINE_PUBLIC_WEAK_ALIAS(printf_s, libc_printf);
DEFINE_PUBLIC_WEAK_ALIAS(vfscanf, libc_vfscanf);
DEFINE_PUBLIC_WEAK_ALIAS(vfscanf_unlocked, libc_vfscanf);
DEFINE_PUBLIC_WEAK_ALIAS(_vfscanf, libc_vfscanf);
DEFINE_PUBLIC_WEAK_ALIAS(_vfscanf_s, libc_vfscanf);
DEFINE_PUBLIC_WEAK_ALIAS(vscanf, libc_vscanf);
DEFINE_PUBLIC_WEAK_ALIAS(vscanf_unlocked, libc_vscanf);
DEFINE_PUBLIC_WEAK_ALIAS(_vscanf, libc_vscanf);
DEFINE_PUBLIC_WEAK_ALIAS(_vscanf_s, libc_vscanf);
DEFINE_PUBLIC_WEAK_ALIAS(fscanf, libc_fscanf);
DEFINE_PUBLIC_WEAK_ALIAS(fscanf_unlocked, libc_fscanf);
DEFINE_PUBLIC_WEAK_ALIAS(scanf, libc_scanf);
DEFINE_PUBLIC_WEAK_ALIAS(scanf_unlocked, libc_scanf);
DEFINE_PUBLIC_WEAK_ALIAS(gets, libc_gets);
DEFINE_PUBLIC_WEAK_ALIAS(vdprintf, libc_vdprintf);
DEFINE_PUBLIC_WEAK_ALIAS(dprintf, libc_dprintf);
DEFINE_PUBLIC_WEAK_ALIAS(renameat, libc_renameat);
DEFINE_PUBLIC_WEAK_ALIAS(removeat, libc_removeat);
DEFINE_PUBLIC_WEAK_ALIAS(frenameat, libc_frenameat);
DEFINE_PUBLIC_WEAK_ALIAS(tmpnam_r, libc_tmpnam_r);
DEFINE_PUBLIC_WEAK_ALIAS(setbuffer, libc_setbuffer);
DEFINE_PUBLIC_WEAK_ALIAS(setlinebuf, libc_setlinebuf);
DEFINE_PUBLIC_WEAK_ALIAS(fflush_unlocked, libc_fflush_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fread_unlocked, libc_fread_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fwrite_unlocked, libc_fwrite_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fgetc_unlocked, libc_fgetc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fputc_unlocked, libc_fputc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(tempnam, libc_tempnam);
DEFINE_PUBLIC_WEAK_ALIAS(_tempnam, libc_tempnam);
DEFINE_PUBLIC_WEAK_ALIAS(fdopen, libc_fdopen);
DEFINE_PUBLIC_WEAK_ALIAS(_fdopen, libc_fdopen);
DEFINE_PUBLIC_WEAK_ALIAS(fileno, libc_fileno);
DEFINE_PUBLIC_WEAK_ALIAS(fileno_unlocked, libc_fileno);
DEFINE_PUBLIC_WEAK_ALIAS(_fileno, libc_fileno);
DEFINE_PUBLIC_WEAK_ALIAS(fmemopen, libc_fmemopen);
DEFINE_PUBLIC_WEAK_ALIAS(open_memstream, libc_open_memstream);
DEFINE_PUBLIC_WEAK_ALIAS(getdelim, libc_getdelim);
DEFINE_PUBLIC_WEAK_ALIAS(getdelim_unlocked, libc_getdelim);
DEFINE_PUBLIC_WEAK_ALIAS(getline, libc_getline);
DEFINE_PUBLIC_WEAK_ALIAS(getline_unlocked, libc_getline);
DEFINE_PUBLIC_WEAK_ALIAS(getchar_unlocked, libc_getchar_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(putchar_unlocked, libc_putchar_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(flockfile, libc_flockfile);
DEFINE_PUBLIC_WEAK_ALIAS(_lock_file, libc_flockfile);
DEFINE_PUBLIC_WEAK_ALIAS(funlockfile, libc_funlockfile);
DEFINE_PUBLIC_WEAK_ALIAS(_unlock_file, libc_funlockfile);
DEFINE_PUBLIC_WEAK_ALIAS(ftrylockfile, libc_ftrylockfile);
DEFINE_PUBLIC_WEAK_ALIAS(cuserid, libc_cuserid);
DEFINE_PUBLIC_WEAK_ALIAS(popen, libc_popen);
DEFINE_PUBLIC_WEAK_ALIAS(_popen, libc_popen);
DEFINE_PUBLIC_WEAK_ALIAS(pclose, libc_pclose);
DEFINE_PUBLIC_WEAK_ALIAS(_pclose, libc_pclose);
DEFINE_PUBLIC_WEAK_ALIAS(getw, libc_getw);
DEFINE_PUBLIC_WEAK_ALIAS(getw_unlocked, libc_getw);
DEFINE_PUBLIC_WEAK_ALIAS(_getw, libc_getw);
DEFINE_PUBLIC_WEAK_ALIAS(putw, libc_putw);
DEFINE_PUBLIC_WEAK_ALIAS(putw_unlocked, libc_putw);
DEFINE_PUBLIC_WEAK_ALIAS(_putw, libc_putw);
DEFINE_PUBLIC_WEAK_ALIAS(fcloseall, libc_fcloseall);
DEFINE_PUBLIC_WEAK_ALIAS(_fcloseall, libc_fcloseall);
DEFINE_PUBLIC_WEAK_ALIAS(fopencookie, libc_fopencookie);
DEFINE_PUBLIC_WEAK_ALIAS(fgets_unlocked, libc_fgets_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fputs_unlocked, libc_fputs_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(obstack_vprintf, libc_obstack_vprintf);
DEFINE_PUBLIC_WEAK_ALIAS(obstack_printf, libc_obstack_printf);
DEFINE_PUBLIC_WEAK_ALIAS(fseeko, libc_fseeko);
DEFINE_PUBLIC_WEAK_ALIAS(fseeko_unlocked, libc_fseeko);
DEFINE_PUBLIC_WEAK_ALIAS(ftello, libc_ftello);
DEFINE_PUBLIC_WEAK_ALIAS(ftello_unlocked, libc_ftello);
DEFINE_PUBLIC_WEAK_ALIAS(tmpfile64, libc_tmpfile64);
DEFINE_PUBLIC_WEAK_ALIAS(fseeko64, libc_fseeko64);
DEFINE_PUBLIC_WEAK_ALIAS(fseeko64_unlocked, libc_fseeko64);
DEFINE_PUBLIC_WEAK_ALIAS(_fseeki64, libc_fseeko64);
DEFINE_PUBLIC_WEAK_ALIAS(_fseeki64_nolock, libc_fseeko64);
DEFINE_PUBLIC_WEAK_ALIAS(ftello64, libc_ftello64);
DEFINE_PUBLIC_WEAK_ALIAS(ftello64_unlocked, libc_ftello64);
DEFINE_PUBLIC_WEAK_ALIAS(_ftelli64, libc_ftello64);
DEFINE_PUBLIC_WEAK_ALIAS(_ftelli64_nolock, libc_ftello64);
DEFINE_PUBLIC_WEAK_ALIAS(fopen64, libc_fopen64);
DEFINE_PUBLIC_WEAK_ALIAS(freopen64, libc_freopen64);
DEFINE_PUBLIC_WEAK_ALIAS(freopen64_unlocked, libc_freopen64);
DEFINE_PUBLIC_WEAK_ALIAS(fgetpos64, libc_fgetpos64);
DEFINE_PUBLIC_WEAK_ALIAS(fgetpos64_unlocked, libc_fgetpos64);
DEFINE_PUBLIC_WEAK_ALIAS(fsetpos64, libc_fsetpos64);
DEFINE_PUBLIC_WEAK_ALIAS(fsetpos64_unlocked, libc_fsetpos64);
DEFINE_PUBLIC_WEAK_ALIAS(file_printer, libc_file_printer);
DEFINE_PUBLIC_WEAK_ALIAS(file_printer_unlocked, libc_file_printer_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(vasprintf, libc_vasprintf);
DEFINE_PUBLIC_WEAK_ALIAS(asprintf, libc_asprintf);
DEFINE_PUBLIC_WEAK_ALIAS(__asprintf, libc_asprintf);
DEFINE_PUBLIC_WEAK_ALIAS(fdreopen, libc_fdreopen);
DEFINE_PUBLIC_WEAK_ALIAS(fdreopen_unlocked, libc_fdreopen);
DEFINE_PUBLIC_WEAK_ALIAS(fdreopen_unlocked, libc_fdreopen_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(freopen_unlocked, libc_freopen_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(freopen64_unlocked, libc_freopen64_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fseek_unlocked, libc_fseek_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fseeko_unlocked, libc_fseeko_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(ftell_unlocked, libc_ftell_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(ftello_unlocked, libc_ftello_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(flushall_unlocked, libc_flushall_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fgetpos_unlocked, libc_fgetpos_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fsetpos_unlocked, libc_fsetpos_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(getw_unlocked, libc_getw_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(putw_unlocked, libc_putw_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(setvbuf_unlocked, libc_setvbuf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(ungetc_unlocked, libc_ungetc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(getdelim_unlocked, libc_getdelim_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(getline_unlocked, libc_getline_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(rewind_unlocked, libc_rewind_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fisatty, libc_fisatty);
DEFINE_PUBLIC_WEAK_ALIAS(puts_unlocked, libc_puts_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fseeko64_unlocked, libc_fseeko64_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(ftello64_unlocked, libc_ftello64_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fgetpos64_unlocked, libc_fgetpos64_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fsetpos64_unlocked, libc_fsetpos64_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(vfprintf_unlocked, libc_vfprintf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fprintf_unlocked, libc_fprintf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(vprintf_unlocked, libc_vprintf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(printf_unlocked, libc_printf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(vfscanf_unlocked, libc_vfscanf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(vscanf_unlocked, libc_vscanf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fscanf_unlocked, libc_fscanf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(scanf_unlocked, libc_scanf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(_fsopen, libc__fsopen);
DEFINE_PUBLIC_WEAK_ALIAS(_rmtmp, libc__rmtmp);
DEFINE_PUBLIC_WEAK_ALIAS(_filbuf, libc__filbuf);
DEFINE_PUBLIC_WEAK_ALIAS(_flsbuf, libc__flsbuf);
DEFINE_PUBLIC_WEAK_ALIAS(_getmaxstdio, libc__getmaxstdio);
DEFINE_PUBLIC_WEAK_ALIAS(_setmaxstdio, libc__setmaxstdio);
DEFINE_PUBLIC_WEAK_ALIAS(_get_printf_count_output, libc__get_printf_count_output);
DEFINE_PUBLIC_WEAK_ALIAS(_set_printf_count_output, libc__set_printf_count_output);
DEFINE_PUBLIC_WEAK_ALIAS(_get_output_format, libc__get_output_format);
DEFINE_PUBLIC_WEAK_ALIAS(_set_output_format, libc__set_output_format);
DEFINE_PUBLIC_WEAK_ALIAS(_scanf_l, libc__scanf_l);
DEFINE_PUBLIC_WEAK_ALIAS(_scanf_s_l, libc__scanf_l);
DEFINE_PUBLIC_WEAK_ALIAS(_fscanf_l, libc__fscanf_l);
DEFINE_PUBLIC_WEAK_ALIAS(_fscanf_s_l, libc__fscanf_l);
DEFINE_PUBLIC_WEAK_ALIAS(_vprintf_l, libc__vprintf_l);
DEFINE_PUBLIC_WEAK_ALIAS(_vprintf_s_l, libc__vprintf_l);
DEFINE_PUBLIC_WEAK_ALIAS(_vprintf_p, libc__vprintf_p);
DEFINE_PUBLIC_WEAK_ALIAS(_vprintf_p_l, libc__vprintf_p_l);
DEFINE_PUBLIC_WEAK_ALIAS(_printf_l, libc__printf_l);
DEFINE_PUBLIC_WEAK_ALIAS(_printf_s_l, libc__printf_s_l);
DEFINE_PUBLIC_WEAK_ALIAS(_printf_p, libc__printf_p);
DEFINE_PUBLIC_WEAK_ALIAS(_printf_p_l, libc__printf_p_l);
DEFINE_PUBLIC_WEAK_ALIAS(_vfprintf_l, libc__vfprintf_l);
DEFINE_PUBLIC_WEAK_ALIAS(_vfprintf_s_l, libc__vfprintf_l);
DEFINE_PUBLIC_WEAK_ALIAS(_vfprintf_p, libc__vfprintf_p);
DEFINE_PUBLIC_WEAK_ALIAS(_vfprintf_p_l, libc__vfprintf_p_l);
DEFINE_PUBLIC_WEAK_ALIAS(_fprintf_l, libc__fprintf_l);
DEFINE_PUBLIC_WEAK_ALIAS(_fprintf_s_l, libc__fprintf_s_l);
DEFINE_PUBLIC_WEAK_ALIAS(_fprintf_p, libc__fprintf_p);
DEFINE_PUBLIC_WEAK_ALIAS(_fprintf_p_l, libc__fprintf_p_l);
DEFINE_PUBLIC_WEAK_ALIAS(fopen_s, libc_fopen_s);
DEFINE_PUBLIC_WEAK_ALIAS(freopen_s, libc_freopen_s);
DEFINE_PUBLIC_WEAK_ALIAS(tmpnam_s, libc_tmpnam_s);
DEFINE_PUBLIC_WEAK_ALIAS(clearerr_s, libc_clearerr_s);
DEFINE_PUBLIC_WEAK_ALIAS(tmpfile_s, libc_tmpfile_s);
DEFINE_PUBLIC_WEAK_ALIAS(fread_s, libc_fread_s);
DEFINE_PUBLIC_WEAK_ALIAS(gets_s, libc_gets_s);
DEFINE_PUBLIC_WEAK_ALIAS(fscanf_s, libc_fscanf_s);
DEFINE_PUBLIC_WEAK_ALIAS(vfscanf_s, libc_vfscanf_s);
DEFINE_PUBLIC_WEAK_ALIAS(scanf_s, libc_scanf_s);
DEFINE_PUBLIC_WEAK_ALIAS(vscanf_s, libc_vscanf_s);
DEFINE_PUBLIC_WEAK_ALIAS(sscanf_s, libc_sscanf_s);
DEFINE_PUBLIC_WEAK_ALIAS(vsscanf_s, libc_vsscanf_s);
DEFINE_PUBLIC_WEAK_ALIAS(vsnprintf_s, libc_vsnprintf_s);
DEFINE_PUBLIC_WEAK_ALIAS(_wperror, libc__wperror);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wperror, libd__wperror);
DEFINE_PUBLIC_WEAK_ALIAS(_fread_nolock_s, libc__fread_nolock_s);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_STDIO_C */
