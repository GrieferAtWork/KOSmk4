/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_STDIO_C
#define GUARD_LIBC_USER_STDIO_C 1

#include "../api.h"
/**/

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sync/atomic-owner-rwlock.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <bits/io-file.h>
#include <kos/syscalls.h>
#include <parts/errno.h>

#include <assert.h>
#include <fcntl.h>
#include <format-printer.h>
#include <limits.h>
#include <malloc.h>
#include <pwd.h>
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
#include "string.h"

DECL_BEGIN

#define libc__vscanf_s_l     libc__vscanf_l
#define libc__vprintf_s_l    libc__vprintf_l
#define libc__vfprintf_s_l   libc__vfprintf_l
#define libc_format_printf   format_printf
#define libc_format_vprintf  format_vprintf
#define libc_ferror_unlocked libc_ferror
#define libc_feof_unlocked   libc_feof

PRIVATE ATTR_SECTION(".data.crt.FILE.locked.utility.std_files_io") 
struct iofile_data_novtab std_files_io[3] = {
	/* [0] = */ IOFILE_DATA_NOVTAB_INIT(),
	/* [1] = */ IOFILE_DATA_NOVTAB_INIT(),
	/* [2] = */ IOFILE_DATA_NOVTAB_INIT()
};

INTERN ATTR_SECTION(".data.crt.FILE.locked.utility.std_files") FILE std_files[3] = {
	/* [0] = */ __IO_FILE_INIT(NULL, 0, NULL, IO_LNBUF, STDIN_FILENO, { 0 }, 0, (struct iofile_data *)&std_files_io[0]),
	/* [1] = */ __IO_FILE_INIT(NULL, 0, NULL, IO_RW | IO_LNIFTYY, STDOUT_FILENO, { 0 }, 0, (struct iofile_data *)&std_files_io[1]),
	/* [2] = */ __IO_FILE_INIT(NULL, 0, NULL, IO_RW | IO_LNIFTYY, STDERR_FILENO, { 0 }, 0, (struct iofile_data *)&std_files_io[2]),
};

#undef stdin
#undef stdout
#undef stderr
PUBLIC ATTR_SECTION(".data.crt.FILE.locked.read.read.stdin")    FILE *stdin  = &std_files[0];
PUBLIC ATTR_SECTION(".data.crt.FILE.locked.write.write.stdout") FILE *stdout = &std_files[1];
PUBLIC ATTR_SECTION(".data.crt.FILE.locked.write.write.stderr") FILE *stderr = &std_files[2];

DEFINE_NOREL_GLOBAL_META(FILE *, stdin, ".crt.FILE.locked.read.read.stdin");
DEFINE_NOREL_GLOBAL_META(FILE *, stdout, ".crt.FILE.locked.write.write.stdout");
DEFINE_NOREL_GLOBAL_META(FILE *, stderr, ".crt.FILE.locked.write.write.stderr");
#define stdin  GET_NOREL_GLOBAL(stdin)
#define stdout GET_NOREL_GLOBAL(stdout)
#define stderr GET_NOREL_GLOBAL(stderr)


/* [0..1][lock(all_files_lock)] Chain of all files.
 * NOTE: This chain excludes the initial stdin, stdout and stderr streams! */
PRIVATE ATTR_SECTION(".bss.crt.application.exit.all_files")
FILE *all_files = NULL;
PRIVATE ATTR_SECTION(".bss.crt.application.exit.all_files_lock")
struct atomic_rwlock all_files_lock = ATOMIC_RWLOCK_INIT;

/* Add the given file to the set of all files */
PRIVATE ATTR_SECTION(".text.crt.FILE.core.utility.allfiles_insert")
NONNULL((1)) void LIBCCALL allfiles_insert(FILE *__restrict self) {
	atomic_rwlock_write(&all_files_lock);
	LLIST_INSERT(all_files, self, if_exdata->io_link);
	assert(LLIST_ISBOUND(self, if_exdata->io_link));
	atomic_rwlock_endwrite(&all_files_lock);
}

/* Remove the given file from the set of all files */
PRIVATE ATTR_SECTION(".text.crt.FILE.core.utility.allfiles_remove")
NONNULL((1)) void LIBCCALL allfiles_remove(FILE *__restrict self) {
	atomic_rwlock_write(&all_files_lock);
	assert(LLIST_ISBOUND(self, if_exdata->io_link));
	LLIST_REMOVE(self, if_exdata->io_link);
	atomic_rwlock_endwrite(&all_files_lock);
}


/* [0..1][lock(changed_linebuffered_files_lock)] Chain of tty-buffers. */
PRIVATE ATTR_SECTION(".bss.crt.FILE.core.write.changed_linebuffered_files")
FILE *changed_linebuffered_files = NULL;
PRIVATE ATTR_SECTION(".bss.crt.FILE.core.write.changed_linebuffered_files_lock")
struct atomic_rwlock changed_linebuffered_files_lock = ATOMIC_RWLOCK_INIT;

/* Add the given file to the set of changed line-buffered files */
PRIVATE ATTR_SECTION(".text.crt.FILE.core.write.changed_linebuffered_insert")
NONNULL((1)) void LIBCCALL changed_linebuffered_insert(FILE *__restrict self) {
	atomic_rwlock_write(&changed_linebuffered_files_lock);
	if (!LLIST_ISBOUND(self, if_exdata->io_lnch))
		LLIST_INSERT(changed_linebuffered_files, self, if_exdata->io_lnch);
	assert(LLIST_ISBOUND(self, if_exdata->io_lnch));
	atomic_rwlock_endwrite(&changed_linebuffered_files_lock);
}

/* Remove the given file from the set of changed line-buffered files */
PRIVATE ATTR_SECTION(".text.crt.FILE.core.write.changed_linebuffered_remove")
NONNULL((1)) void LIBCCALL changed_linebuffered_remove(FILE *__restrict self) {
	atomic_rwlock_write(&changed_linebuffered_files_lock);
	if (LLIST_ISBOUND(self, if_exdata->io_lnch)) {
		LLIST_REMOVE(self, if_exdata->io_lnch);
		LLIST_UNBIND(self, if_exdata->io_lnch);
	}
	atomic_rwlock_endwrite(&changed_linebuffered_files_lock);
}

/* Low-level file read operation. */
PRIVATE ATTR_SECTION(".text.crt.FILE.core.read.file_system_read")
NONNULL((1)) ssize_t LIBCCALL file_system_read(FILE *__restrict self,
                                               void *buf, size_t num_bytes) {
	ssize_t result;
	if (self->if_flag & IO_HASVTAB) {
		struct iofile_data *ex;
		ex = self->if_exdata;
		result = (*ex->io_vtab.read)(ex->io_magi, (char *)buf, num_bytes);
	} else {
		result = read(self->if_fd, buf, num_bytes);
	}
	return result;
}

/* Low-level file write operation. */
PRIVATE ATTR_SECTION(".text.crt.FILE.core.write.file_system_write")
NONNULL((1)) ssize_t LIBCCALL file_system_write(FILE *__restrict self,
                                                void const *buf, size_t num_bytes) {
	ssize_t result;
	if (self->if_flag & IO_HASVTAB) {
		struct iofile_data *ex;
		ex = self->if_exdata;
		result = (*ex->io_vtab.write)(ex->io_magi, (char const *)buf, num_bytes);
	} else {
		result = write(self->if_fd, buf, num_bytes);
	}
	return result;
}

LOCAL ATTR_SECTION(".text.crt.FILE.core.write.file_system_writeall_vt")
NONNULL((1)) ssize_t LIBCCALL file_system_writeall_vt(FILE *__restrict self,
                                                      void const *buf, size_t num_bytes) {
	ssize_t result;
	struct iofile_data *ex;
	ex = self->if_exdata;
	result = (*ex->io_vtab.write)(ex->io_magi, (char const *)buf, num_bytes);
	if (result > 0 && (size_t)result < num_bytes) {
		/* Keep on writing */
		for (;;) {
			ssize_t temp;
			temp = (*ex->io_vtab.write)(ex->io_magi,
			                            (char const *)((byte_t *)buf + (size_t)result),
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
	return result;
}

PRIVATE ATTR_SECTION(".text.crt.FILE.core.write.file_system_writeall")
NONNULL((1)) ssize_t LIBCCALL file_system_writeall(FILE *__restrict self,
                                                   void const *buf, size_t num_bytes) {
	ssize_t result;
	if (self->if_flag & IO_HASVTAB) {
		result = file_system_writeall_vt(self, buf, num_bytes);
	} else {
		result = writeall(self->if_fd, buf, num_bytes);
	}
	return result;
}

/* Low-level file seek operation. */
PRIVATE ATTR_SECTION(".text.crt.FILE.core.seek.file_system_seek")
NONNULL((1)) off64_t LIBCCALL file_system_seek(FILE *__restrict self,
                                               off64_t offset, int whence) {
	off64_t result;
	if (self->if_flag & IO_HASVTAB) {
		struct iofile_data *ex;
		ex     = self->if_exdata;
		result = offset;
		if ((*ex->io_vtab.seek)(ex->io_magi, &result, whence))
			result = -1;
	} else {
		result = lseek64(self->if_fd, offset, whence);
	}
	return result;
}

/* Low-level file close operation. */
PRIVATE ATTR_SECTION(".text.crt.FILE.core.utility.file_system_close")
NONNULL((1)) int LIBCCALL file_system_close(FILE *__restrict self) {
	int result;
	if (self->if_flag & IO_HASVTAB) {
		struct iofile_data *ex;
		ex     = self->if_exdata;
		result = (*ex->io_vtab.close)(ex->io_magi);
	} else {
		result = close(self->if_fd);
	}
	return result;
}

/* Low-level file sync operation. */
PRIVATE ATTR_SECTION(".text.crt.FILE.core.write.file_system_sync")
NONNULL((1)) int LIBCCALL file_system_sync(FILE *__restrict self) {
	int result;
	if (self->if_flag & IO_HASVTAB) {
		result = 0; /* No-op */
	} else {
		result = fsync(self->if_fd);
	}
	return result;
}

/* Low-level file truncate operation. */
PRIVATE ATTR_SECTION(".text.crt.FILE.core.write.file_system_sync")
NONNULL((1)) int LIBCCALL file_system_trunc(FILE *__restrict self, pos64_t new_size) {
	int result;
	if (self->if_flag & IO_HASVTAB) {
		/* Not allowed for VTABLE files. */
		libc_seterrno(EPERM);
		result = -1;
	} else {
		result = ftruncate64(self->if_fd, new_size);
	}
	return result;
}

/* Determine if `self' is a TTY */
INTERN ATTR_SECTION(".text.crt.FILE.core.utility.file_determine_isatty")
NONNULL((1)) void LIBCCALL file_determine_isatty(FILE *__restrict self) {
	uint32_t flags = self->if_flag;
	if (!(flags & (IO_NOTATTY | IO_ISATTY))) {
		if (flags & IO_HASVTAB) {
			flags |= IO_NOTATTY;
		} else {
			int is_a_tty;
			is_a_tty = isatty(self->if_fd);
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


PRIVATE ATTR_SECTION(".text.crt.FILE.core.utility.file_buffer_realloc") byte_t *LIBCCALL
file_buffer_realloc(FILE *__restrict self, size_t new_size) {
	if (!(self->if_flag & IO_MALLBUF))
		return (byte_t *)malloc(new_size);
	assert(!(self->if_flag & IO_READING));
	return (byte_t *)realloc(self->if_base, new_size);
}


/* Change the operations mode of a given buffer. */
PRIVATE ATTR_SECTION(".text.crt.FILE.core.utility.file_setmode")
WUNUSED NONNULL((1)) int LIBCCALL file_setmode(FILE *__restrict self,
                                               void *buf, int mode, size_t size) {
	/* Convert DOS names. */
	if unlikely(mode == 0x0040)
		mode = _IOLBF;
	if unlikely(mode == 0x0004)
		mode = _IONBF;
	/* Translate buffer mode into file flags. */
	if (mode == _IONBF)
		mode = IO_NODYNSCALE;
	else if (mode == _IOFBF)
		mode = 0;
	else {
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
			 * it has been truncated to ZERO(0). */
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
			 * it has been truncated to ZERO(0). */
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
	libc_seterrno(EWOULDBLOCK);
err:
	return -1;
}

INTERN NONNULL((1)) ATTR_SECTION(".text.crt.FILE.core.write.file_sync")
int LIBCCALL file_sync(FILE *__restrict self) {
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

PRIVATE ATTR_SECTION(".text.crt.application.exit.file_sync_locked")
int LIBCCALL file_sync_locked(FILE *__restrict self) {
	int result;
	if (FMUSTLOCK(self)) {
		file_write(self);
		result = file_sync(self);
		file_endwrite(self);
	} else {
		result = file_sync(self);
	}
	return result;
}

INTERN NONNULL((1)) ATTR_SECTION(".text.crt.FILE.core.utility.file_decref")
void LIBCCALL file_decref(FILE *__restrict self) {
	refcnt_t refcnt;
	struct iofile_data *ex;
	assert(self);
	ex = self->if_exdata;
	assert(ex);
	refcnt = ATOMIC_FETCHDEC(ex->io_refcnt);
	assert(refcnt != 0);
	if (refcnt == 1) {
		/* Last reference -> This file has to go away! */
		assert(!(self >= std_files &&
		         self < COMPILER_ENDOF(std_files)));
		assert(!(ex >= std_files_io &&
		         ex < COMPILER_ENDOF(std_files_io)));
		assert(!atomic_owner_rwlock_reading(&ex->io_lock));
		assert(!(self->if_flag & IO_READING));
		if (ex->io_chsz != 0) {
			/* The file still contains some changed data.
			 * -> Try to flush data data. */
			atomic_owner_rwlock_init_read(&ex->io_lock);
			ATOMIC_WRITE(ex->io_refcnt, 1);
			/* NOTE: Errors during this sync are ignored! */
			file_sync(self);
			atomic_owner_rwlock_endread(&ex->io_lock);
			refcnt = ATOMIC_FETCHDEC(ex->io_refcnt);
			assert(refcnt != 0);
			if (refcnt != 1)
				return; /* The file was revived. */
		}
		assert(!atomic_owner_rwlock_reading(&ex->io_lock));
		assert(!(self->if_flag & IO_READING));
		/* Close the underlying file. */
		if (self->if_flag & IO_HASVTAB) {
			errno_t saved_errno;
			/* In this case, we have to be careful in case the file gets revived. */
			atomic_owner_rwlock_init_read(&ex->io_lock);
			ATOMIC_WRITE(ex->io_refcnt, 1);
			saved_errno = libc_geterrno_safe();
			/* NOTE: Errors during this close are ignored! */
			(*ex->io_vtab.close)(ex->io_magi);
			libc_seterrno(saved_errno);
			atomic_owner_rwlock_endread(&ex->io_lock);
			refcnt = ATOMIC_FETCHDEC(ex->io_refcnt);
			assert(refcnt != 0);
			if (refcnt != 1)
				return; /* The file was revived. */
		} else {
			sys_close(self->if_fd);
		}
		assert(!atomic_owner_rwlock_reading(&ex->io_lock));
		assert(!(self->if_flag & IO_READING));
		/* Make sure that the file is no longer accessible through the global file lists. */
		if (LLIST_ISBOUND(self, if_exdata->io_lnch))
			changed_linebuffered_remove(self);
		allfiles_remove(self);
		/* Free a heap-allocated buffer. */
		if (self->if_flag & IO_MALLBUF)
			free(self->if_base);
#if 1 /* This is always the case... */
		assert(ex == (struct iofile_data *)(self + 1));
#else
		if (ex != (struct iofile_data *)(self + 1))
			free(ex);
#endif
		free(self);
	}
}


/* Synchronize unwritten data of all line-buffered files. */
INTERN ATTR_SECTION(".text.crt.FILE.core.write.file_sync_lnfiles")
void LIBCCALL file_sync_lnfiles(void) {
	while (ATOMIC_READ(changed_linebuffered_files) != NULL) {
		FILE *fp;
		atomic_rwlock_write(&changed_linebuffered_files_lock);
		fp = changed_linebuffered_files;
		for (;;) {
			if unlikely(!fp) {
				atomic_rwlock_endwrite(&changed_linebuffered_files_lock);
				goto done;
			}
			assert(LLIST_ISBOUND(fp, if_exdata->io_lnch));
			if (file_tryincref(fp))
				break;
			fp = LLIST_NEXT(fp, if_exdata->io_lnch);
		}
		/* Remove the file from the chain of changed line-buffered files. */
		assert(LLIST_ISBOUND(fp, if_exdata->io_lnch));
		LLIST_REMOVE(fp, if_exdata->io_lnch);
		LLIST_UNBIND(fp, if_exdata->io_lnch);
		atomic_rwlock_endwrite(&changed_linebuffered_files_lock);
		/* Synchronize this buffer. */
		if (FMUSTLOCK(fp)) {
			file_write(fp);
			file_sync(fp);
			file_endwrite(fp);
		} else {
			file_sync(fp);
		}
		file_decref(fp);
	}
done:
	;
}

PRIVATE ATTR_SECTION(".text.crt.application.exit.file_do_syncall_locked")
void LIBCCALL file_do_syncall_locked(uintptr_t version) {
	for (;;) {
		FILE *fp, *next_fp;
		atomic_rwlock_read(&all_files_lock);
		fp = all_files;
		while (fp &&
		       fp->if_exdata->io_fver == version &&
		       !file_tryincref(fp))
			fp = LLIST_NEXT(fp, if_exdata->io_link);
		atomic_rwlock_endread(&all_files_lock);
		if (!fp)
			break;
do_flush_fp:
		if (FMUSTLOCK(fp)) {
			file_write(fp);
			fp->if_exdata->io_fver = version;
			file_sync(fp);
			file_endwrite(fp);
		} else {
			fp->if_exdata->io_fver = version;
			file_sync(fp);
		}
		atomic_rwlock_read(&all_files_lock);
		next_fp = LLIST_NEXT(fp, if_exdata->io_link);
		while (next_fp &&
		       next_fp->if_exdata->io_fver == version &&
		       !file_tryincref(next_fp))
			next_fp = LLIST_NEXT(next_fp, if_exdata->io_link);
		atomic_rwlock_endread(&all_files_lock);
		file_decref(fp);
		if (!next_fp)
			continue; /* Do another full scan for changed files. */
		fp = next_fp;
		goto do_flush_fp;
	}
}

PRIVATE ATTR_SECTION(".text.crt.FILE.unlocked.write.utility.file_do_syncall_unlocked")
void LIBCCALL file_do_syncall_unlocked(uintptr_t version) {
	for (;;) {
		FILE *fp, *next_fp;
		atomic_rwlock_read(&all_files_lock);
		fp = all_files;
		while (fp &&
		       fp->if_exdata->io_fver == version &&
		       !file_tryincref(fp))
			fp = LLIST_NEXT(fp, if_exdata->io_link);
		atomic_rwlock_endread(&all_files_lock);
		if (!fp)
			break;
do_flush_fp:
		fp->if_exdata->io_fver = version;
		file_sync(fp);
		atomic_rwlock_read(&all_files_lock);
		next_fp = LLIST_NEXT(fp, if_exdata->io_link);
		while (next_fp &&
		       next_fp->if_exdata->io_fver == version &&
		       !file_tryincref(next_fp))
			next_fp = LLIST_NEXT(next_fp, if_exdata->io_link);
		atomic_rwlock_endread(&all_files_lock);
		file_decref(fp);
		if (!next_fp)
			continue; /* Do another full scan for changed files. */
		fp = next_fp;
		goto do_flush_fp;
	}
}


PRIVATE ATTR_SECTION(".bss.crt.application.exit.flushall_lock")
struct atomic_owner_rwlock flushall_lock = ATOMIC_OWNER_RWLOCK_INIT;
PRIVATE ATTR_SECTION(".bss.crt.application.exit.flushall_version")
uintptr_t flushall_version = 0;
PRIVATE ATTR_SECTION(".bss.crt.application.exit.flushall_must_restart")
bool flushall_must_restart = false;

PRIVATE ATTR_SECTION(".text.crt.application.exit.file_syncall_locked")
void LIBCCALL file_syncall_locked(void) {
	/* Check for recursion (as is possible due to file cookies) */
	if (atomic_owner_rwlock_writing(&flushall_lock)) {
		/* Don't allow recursion, but solve the problem by re-starting the flush operation. */
		flushall_must_restart = true;
		return;
	}
	atomic_owner_rwlock_write(&flushall_lock);
	do {
		flushall_must_restart = false;
		file_do_syncall_locked(flushall_version++);
	} while (flushall_must_restart);
	atomic_owner_rwlock_endwrite(&flushall_lock);
}

PRIVATE ATTR_SECTION(".text.crt.FILE.unlocked.write.utility.file_syncall_unlocked")
void LIBCCALL file_syncall_unlocked(void) {
	/* Check for recursion (as is possible due to file cookies) */
	if (atomic_owner_rwlock_writing(&flushall_lock)) {
		/* Don't allow recursion, but solve the problem by re-starting the flush operation. */
		flushall_must_restart = true;
		return;
	}
	atomic_owner_rwlock_write(&flushall_lock);
	do {
		flushall_must_restart = false;
		file_do_syncall_unlocked(flushall_version++);
	} while (flushall_must_restart);
	atomic_owner_rwlock_endwrite(&flushall_lock);
}


/* High-level, common read-from-file function. */
INTERN ATTR_SECTION(".text.crt.FILE.core.read.file_readdata")
NONNULL((1)) size_t LIBCCALL file_readdata(FILE *__restrict self,
                                           void *buf, size_t num_bytes) {
	ssize_t read_size;
	size_t result = 0;
	size_t bufavail;
	uint32_t old_flags;
	pos64_t next_data;
	uint8_t *new_buffer;
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
		/* Make sure that we only invoke read() on the underlying
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
		size_t initial_bufsize;
		if unlikely(self->if_flag & IO_NODYNSCALE) {
			/* Dynamic scaling is disabled. Must forward the read() to the underlying file. */
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
			read_size = file_system_read(self, buf, num_bytes);
			COMPILER_BARRIER();
			if unlikely(read_size < 0)
				goto err;
			ex->io_fpos = next_data + num_bytes;
			result += (size_t)read_size;
			num_bytes -= (size_t)read_size;
			goto done;
		}
		if (num_bytes >= IOBUF_MAX)
			goto read_through;
		initial_bufsize = num_bytes;
		if (initial_bufsize < IOBUF_MIN)
			initial_bufsize = IOBUF_MIN;
		new_buffer = file_buffer_realloc(self, initial_bufsize);
		if unlikely(!new_buffer)
			goto read_through;
		self->if_base   = new_buffer;
		self->if_bufsiz = initial_bufsize;
		self->if_flag  |= IO_MALLBUF;
	} else if (num_bytes >= self->if_bufsiz) {
		/* The caller wants at least as much as this buf could even handle.
		 * Upscale the buf, or use load data using read-through mode. */
		if (self->if_flag & (IO_NODYNSCALE | IO_READING))
			goto read_through;
		if (num_bytes > IOBUF_MAX)
			goto read_through;
		/* Upscale the buf. */
		new_buffer = file_buffer_realloc(self, num_bytes);
		/* If the allocation failed, also use read-through mode. */
		if unlikely(!new_buffer)
			goto read_through;
		self->if_base   = new_buffer;
		self->if_bufsiz = num_bytes;
		self->if_flag  |= IO_MALLBUF;
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
INTERN ATTR_SECTION(".text.crt.FILE.core.write.file_writedata")
NONNULL((1)) size_t LIBCCALL file_writedata(FILE *__restrict self,
                                            void const *buf, size_t num_bytes) {
	size_t result = 0;
	size_t new_bufsize;
	size_t bufavail;
	uint8_t *new_buffer;
	struct iofile_data *ex;
	assert(self);
	ex = self->if_exdata;
	assert(ex);
	/* Check to make sure that this file is writable. */
	if (!(self->if_flag & IO_RW)) {
		libc_seterrno(EPERM);
		goto err;
	}
	if (self->if_flag & IO_LNIFTYY)
		file_determine_isatty(self);
again:
	/* Fill available buf. */
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
		if (self->if_cnt >= bufavail)
			self->if_cnt -= bufavail;
		else {
			self->if_cnt = 0;
		}
		/* When operating in line-buffered mode, check
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
		/* Buffer is too large or cannot be relocated.
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
		/* If there is no more available buf to-be read,
		 * reset the file pointer and change to the next chunk. */
		if (!self->if_cnt) {
			ex->io_fblk += (size_t)(self->if_ptr - self->if_base);
			self->if_ptr = self->if_base;
		}
		goto again;
	}

	/* Extend the buf */
	new_bufsize = self->if_bufsiz * 2;
	if (new_bufsize < IOBUF_MIN)
		new_bufsize = IOBUF_MIN;
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

INTERN ATTR_SECTION(".text.crt.FILE.core.write.file_writedata")
NONNULL((1)) pos64_t LIBCCALL file_seek(FILE *__restrict self,
                                        off64_t off, int whence) {
	pos64_t result;
	struct iofile_data *ex;
	assert(self);
	ex = self->if_exdata;
	assert(ex);
	self->if_flag &= ~IO_EOF;
	if (whence == SEEK_SET || whence == SEEK_CUR) {
		pos64_t old_abspos;
		pos64_t new_abspos;
		uint8_t *new_pos;
		/* For these modes, we can calculate the new position,
		 * allowing for in-buffer seek, as well as delayed seek. */
		old_abspos = ex->io_fblk;
		old_abspos += (self->if_ptr - self->if_base);
		if (whence == SEEK_SET)
			new_abspos = (pos64_t)off;
		else {
			/* Special case: position-query */
			if (off == 0)
				return old_abspos;
			new_abspos = old_abspos + off;
		}
		if unlikely(new_abspos >= INT64_MAX) {
			libc_seterrno(EOVERFLOW);
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
			/* Seek below the current pointer (but we don't
			 * remember how much was actually read there, so
			 * we simply truncate the buffer fully) */
			self->if_cnt = 0;
		} else {
			size_t skipsz = (size_t)(new_pos - self->if_ptr);
			if (self->if_cnt >= skipsz)
				self->if_cnt -= skipsz;
			else {
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


INTERN ATTR_SECTION(".text.crt.FILE.core.read.file_getc")
WUNUSED NONNULL((1)) int LIBCCALL file_getc(FILE *__restrict self) {
	uint8_t *new_buffer;
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
	if (file_sync(self))
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
		new_buffer = file_buffer_realloc(self, IOBUF_MIN);
		if unlikely(!new_buffer)
			goto read_through;
		self->if_base   = new_buffer;
		self->if_bufsiz = IOBUF_MIN;
	} else {
		if (self->if_bufsiz < IOBUF_MIN &&
		    !(self->if_flag & (IO_NODYNSCALE | IO_READING))) {
			/* Upscale the buffer. */
			new_buffer = file_buffer_realloc(self, IOBUF_MIN);
			if unlikely(!new_buffer)
				goto read_through;
			self->if_base   = new_buffer;
			self->if_bufsiz = IOBUF_MIN;
			self->if_flag  |= IO_MALLBUF;
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

INTERN ATTR_SECTION(".text.crt.FILE.core.read.file_ungetc")
WUNUSED NONNULL((1)) int LIBCCALL file_ungetc(FILE *__restrict self, unsigned char ch) {
	uint8_t *new_buffer;
	size_t new_bufsize, inc_size;
	struct iofile_data *ex;
	assert(self);
	/* Simple case: unget() the character. */
	if (self->if_ptr != self->if_base)
		goto unget_in_buffer;
	/* The buffer is already full. - Try to resize it, then insert at the front. */
	if (self->if_flag & IO_READING)
		goto eof;
	if (self->if_flag & IO_NODYNSCALE) {
		/* Check for special case: Even when dynscale is disabled,
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
		new_bufsize = self->if_bufsiz + 1;
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
	assert(self->if_ptr != self->if_base);
	/* Finally, insert the character into the buffer. */
unget_in_buffer:
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

INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.core.read.file_getc16")
WUNUSED NONNULL((1)) char16_t LIBCCALL file_getc16(FILE *__restrict self) {
	char16_t result;
	struct iofile_data *ex;
	assert(self);
	ex = self->if_exdata;
	assert(ex);
	/* Check for a pending surrogate */
	if ((ex->io_mbs.__word & __MBSTATE_TYPE_MASK) == __MBSTATE_TYPE_WR_UTF16_LO) {
		result = (char16_t)(0xdc00 + (ex->io_mbs.__word & 0x000003ff));
		ex->io_mbs.__word = 0;
		goto done;
	}
	/* Try to complete an in-progress utf-8 sequence. */
	for (;;) {
		size_t error;
		char buf[1];
		int ch;
		ch = file_getc(self);
		if (ch == EOF) {
			result = EOF16;
			goto done;
		}
		buf[0] = (char)(unsigned char)(unsigned int)ch;
		error  = unicode_c8toc16(&result, buf, 1, &ex->io_mbs);
		if likely(error > 0) /* Completed sequence. */
			goto done;
		if unlikely(error == 0) {
			/* Shouldn't happen (a surrogate was written) */
			if (file_ungetc(self, (unsigned char)buf[0]) == EOF)
				result = EOF16;
			goto done;
		}
		if unlikely(error == (size_t)-1) {
			/* Unicode error. */
			libc_seterrno(EILSEQ);
			self->if_flag |= IO_ERR;
			result = EOF16;
			goto done;
		}
		/* Incomplete sequence (continue reading...) */
	}
done:
	return result;
}

INTERN ATTR_SECTION(".text.crt.wchar.FILE.core.read.file_getc32")
WUNUSED NONNULL((1)) char32_t LIBCCALL file_getc32(FILE *__restrict self) {
	char32_t result;
	struct iofile_data *ex;
	assert(self);
	ex = self->if_exdata;
	assert(ex);
	/* Try to complete an in-progress utf-8 sequence. */
	for (;;) {
		size_t error;
		char buf[1];
		int ch;
		ch = file_getc(self);
		if (ch == EOF) {
			result = EOF32;
			goto done;
		}
		buf[0] = (char)(unsigned char)(unsigned int)ch;
		error  = unicode_c8toc32(&result, buf, 1, &ex->io_mbs);
		if likely(error > 0) /* Completed sequence. */
			goto done;
		if unlikely(error == (size_t)-1) {
			/* Unicode error. */
			libc_seterrno(EILSEQ);
			self->if_flag |= IO_ERR;
			result = EOF32;
			goto done;
		}
		/* Incomplete sequence (continue reading...) */
	}
done:
	return result;
}


INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.core.read.file_ungetc16")
WUNUSED NONNULL((1)) char16_t LIBCCALL file_ungetc16(FILE *__restrict self, char16_t ch) {
	char32_t unget_char;
	char16_t result = ch;
	struct iofile_data *ex;
	assert(self);
	ex = self->if_exdata;
	assert(ex);
	/* Check for a pending surrogate */
	if ((ex->io_mbs.__word & __MBSTATE_TYPE_MASK) == __MBSTATE_TYPE_WR_UTF16_LO) {
		char16_t lo_surrogate;
		if unlikely(ch < UTF16_HIGH_SURROGATE_MIN || ch > UTF16_HIGH_SURROGATE_MAX) {
set_ilseq:
			libc_seterrno(EILSEQ);
			self->if_flag |= IO_ERR;
			result = EOF16;
			goto done;
		}
		lo_surrogate = (char16_t)(0xdc00 + (ex->io_mbs.__word & 0x000003ff));
		ex->io_mbs.__word = 0;
		unget_char = ch;
		unget_char -= 0xd800;
		unget_char <<= 10;
		unget_char += 0x10000 - 0xdc00;
		unget_char += lo_surrogate;
	} else {
		if unlikely(ch >= UTF16_HIGH_SURROGATE_MIN &&
		            ch <= UTF16_HIGH_SURROGATE_MAX)
			goto set_ilseq;
		unget_char = ch;
	}
	if (file_ungetc32(self, unget_char) == EOF32)
		result = EOF16;
done:
	return result;
}

INTERN ATTR_SECTION(".text.crt.wchar.FILE.core.read.file_ungetc32")
WUNUSED NONNULL((1)) char32_t LIBCCALL file_ungetc32(FILE *__restrict self, char32_t ch) {
	char32_t result = ch;
	char buf[UNICODE_UTF8_MAXLEN], *end;
	end = unicode_writeutf8(buf, ch);
	assert(end > buf);
	do {
		--end;
		if (file_ungetc(self, (unsigned char)*end) == EOF) {
			result = EOF32;
			break;
		}
	} while (end > buf);
	return result;
}

INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.core.write.file_print16")
WUNUSED NONNULL((1)) ssize_t LIBCCALL
file_print16(void *self, char16_t const *__restrict data, size_t datalen) {
	ssize_t result;
	struct format_16to8_data arg;
	struct iofile_data *ex;
	FILE *me = (FILE *)self;
	assert(me);
	ex = me->if_exdata;
	assert(ex);
	arg.fd_arg       = self;
	arg.fd_printer   = &libc_file_printer_unlocked;
	arg.fd_surrogate = 0;
	/* Check for a the pending surrogate pair */
	if ((ex->io_mbs.__word & __MBSTATE_TYPE_MASK) == __MBSTATE_TYPE_UTF16_LO) {
		arg.fd_surrogate = 0xdc00 + (ex->io_mbs.__word & 0x000003ff);
		ex->io_mbs.__word = 0;
	}
	result = format_16to8(&arg, data, datalen);
	/* Update the pending surrogate pair */
	if (arg.fd_surrogate)
		ex->io_mbs.__word = __MBSTATE_TYPE_UTF16_LO | (arg.fd_surrogate - 0xdc00);
	return result;
}

INTERN ATTR_SECTION(".text.crt.wchar.FILE.core.write.file_print32")
WUNUSED NONNULL((1)) ssize_t LIBCCALL
file_print32(void *self, char32_t const *__restrict data, size_t datalen) {
	ssize_t result;
	struct format_32to8_data arg;
	arg.fd_printer = &libc_file_printer_unlocked;
	arg.fd_arg     = self;
	result = format_32to8(&arg, data, datalen);
	return result;
}



INTERN ATTR_SECTION(".text.crt.FILE.core.write.file_truncate")
WUNUSED NONNULL((1)) int LIBCCALL file_truncate(FILE *__restrict self,
                                                pos64_t new_size) {
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
	/* With data flushed and the loaded buffer
	 * truncated, truncate the underlying file. */
	COMPILER_BARRIER();
	if (file_system_trunc(self, new_size))
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
 * string passed as second argument to file.open:
 * >> file.open("foo.txt","w+");                    // STD-C mode name.
 * >> file.open("foo.txt","text,RW,T,C");           // Extended form.
 * >> file.open("foo.txt","text,rdwr,trunc,creat"); // Long form.
 */
#define BASEMODE_MASK (O_ACCMODE | O_CREAT | O_EXCL | O_TRUNC | O_APPEND)
PRIVATE ATTR_SECTION(".rodata.crt.FILE.core.utility.open_options")
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
	{ "xread", OPEN_EXFLAG_FNORMAL, O_XREAD, O_XREAD },
	{ "xwrite", OPEN_EXFLAG_FNORMAL, O_XWRITE, O_XWRITE },
	{ "hidden", OPEN_EXFLAG_FNORMAL, O_HIDDEN, O_HIDDEN },
	/* Extended flag names. */
	{ "binary", OPEN_EXFLAG_FNORMAL, 0, 0 },
	{ "text", OPEN_EXFLAG_FTEXT, 0, 0 },
	{ "nobuf", OPEN_EXFLAG_FNOBUF, 0, 0 },
};


/* @param: poflags: When non-NULL, filled with `O_*'
 * @return: * :     Set of `IO_*' */
INTERN ATTR_SECTION(".text.crt.FILE.core.utility.file_evalmodes")
WUNUSED uint32_t LIBCCALL file_evalmodes(char const *modes,
                                         oflag_t *poflags) {
	/* IO_LNIFTYY: Check if the stream handle is a tty
	 *             the first time it is read from. */
	uint32_t result = IO_LNIFTYY;
	oflag_t oflags = O_RDONLY;
	if (modes) {
		unsigned int flags = 0;
		for (;;) {
			bool open_binary;
			unsigned int i;
			size_t optlen;
			char const *next = strchr(modes, ',');
			if (!next)
				next = modes + strlen(modes);
			optlen = (size_t)(next - modes);
			if (optlen < COMPILER_LENOF(open_options[0].name)) {
				for (i = 0; i < COMPILER_LENOF(open_options); ++i) {
					if (open_options[i].name[optlen])
						continue;
					if (memcmp(open_options[i].name, modes, optlen * sizeof(char)) != 0)
						continue;
					if (oflags & open_options[i].mask)
						goto err_invalid_oflags; /* Check illegal old flags. */
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
			open_binary = false;
			if (*modes == 'r') {
				oflags |= O_RDONLY;
			} else if (*modes == 'w') {
				oflags |= O_WRONLY | O_TRUNC | O_CREAT;
			} else if (*modes == 'a') {
				oflags |= O_WRONLY | O_APPEND | O_CREAT;
			} else {
				goto err_invalid_oflags;
			}
			if (*++modes == 'b') {
				++modes;
				open_binary = true;
			}
			if (*modes == '+') {
				++modes;
				oflags &= ~O_ACCMODE;
				oflags |= O_RDWR;
			}
			if (*modes == 'b' && !open_binary) {
				++modes;
				open_binary = true;
			}
			if (*modes == 'x' &&
			    (oflags & (O_TRUNC | O_CREAT)) == (O_TRUNC | O_CREAT)) {
				++modes;
				oflags |= O_EXCL;
			}
			if (*modes == 't' && !open_binary)
				++modes; /* Accept a trailing `t', as suggested by STD-C */
			if (modes != next)
				goto err_invalid_oflags;
			if (!open_binary)
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
INTERN ATTR_SECTION(".text.crt.FILE.core.utility.file_openfd")
WUNUSED FILE *LIBCCALL file_openfd(/*inherit(on_success)*/ fd_t fd, uint32_t flags) {
	FILE *result;
	struct iofile_data *ex;
	result = (FILE *)calloc(1,
	                        sizeof(FILE) +
	                        sizeof(struct iofile_data_novtab));
	if unlikely(!result)
		goto done;
	ex = (struct iofile_data *)(result + 1);
	result->if_exdata = ex;
	result->if_fd     = fd; /* Inherit reference */
	atomic_owner_rwlock_cinit(&ex->io_lock);
	assert(ex->io_zero == 0);
	ex->io_refcnt   = 1;
	result->if_flag = flags;
	/* Insert the new file stream into the global list of them. */
	allfiles_insert(result);
done:
	return result;
}


INTERN NONNULL((1)) ATTR_SECTION(".text.crt.FILE.core.utility.file_openfd")
WUNUSED FILE *LIBCCALL file_reopenfd(FILE *__restrict self,
                                     fd_t fd, uint32_t flags) {
	struct iofile_data *ex;
	if unlikely(self->if_flag & IO_READING) {
		/* reopen() isn't allowed from within a cookie function. */
		libc_seterrno(EPERM);
		return NULL;
	}
	if (file_sync(self))
		return NULL;
	if (LLIST_ISBOUND(self, if_exdata->io_lnch))
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
	ex->io_mbs.__word = 0;
	return self;
}


INTERN NONNULL((1)) ATTR_SECTION(".text.crt.FILE.core.utility.file_openfd")
WUNUSED FILE *LIBCCALL file_opencookie(cookie_io_functions_t const *__restrict io,
                                       void *magic, uint32_t flags) {
	FILE *result;
	struct iofile_data *ex;
	result = (FILE *)calloc(1,
	                        sizeof(FILE) +
	                        sizeof(struct iofile_data));
	if unlikely(!result)
		goto done;
	ex = (struct iofile_data *)(result + 1);
	result->if_exdata = ex;
	atomic_owner_rwlock_cinit(&ex->io_lock);
	assert(ex->io_zero == 0);
	ex->io_refcnt = 1;
	/* Check if the stream handle is a tty the first time it is read from. */
	result->if_flag = IO_HASVTAB | IO_NOTATTY | (flags & ~IO_LNIFTYY);
	ex->io_magi = magic;
	memcpy(&ex->io_vtab, io, sizeof(cookie_io_functions_t));
	/* Insert the new file stream into the global list of them. */
	allfiles_insert(result);
done:
	return result;
}









/*[[[start:implementation]]]*/

/*[[[head:_flushall,hash:CRC-32=0xc6dc9668]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.application.exit._flushall") int
(LIBCCALL libc__flushall)(void)
		__THROWS(...)
/*[[[body:_flushall]]]*/
{
	/* All all streams opened by the user. */
	file_syncall_locked();
	/* Flush the active STD streams. */
	file_sync_locked(stdin);
	file_sync_locked(stdout);
	file_sync_locked(stderr);
	return 0;
}
/*[[[end:_flushall]]]*/

/*[[[head:flushall_unlocked,hash:CRC-32=0x80bd200a]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.write.utility.flushall_unlocked") int
(LIBCCALL libc_flushall_unlocked)(void)
		__THROWS(...)
/*[[[body:flushall_unlocked]]]*/
{
	/* All all streams opened by the user. */
	file_syncall_unlocked();
	/* Flush the active STD streams. */
	file_sync(stdin);
	file_sync(stdout);
	file_sync(stderr);
	return 0;
}
/*[[[end:flushall_unlocked]]]*/


/*[[[head:removeat,hash:CRC-32=0xe49fdb2f]]]*/
/* Remove a file or directory `FILENAME' relative to a given base directory `DIRFD' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify.removeat") int
NOTHROW_RPC(LIBCCALL libc_removeat)(fd_t dirfd,
                                    char const *filename)
/*[[[body:removeat]]]*/
{
	errno_t result;
	result = sys_unlinkat(dirfd, filename,
	                      AT_REMOVEDIR | AT_REMOVEREG);
	return libc_seterrno_syserr(result);
}
/*[[[end:removeat]]]*/

/*[[[head:remove,hash:CRC-32=0x64fa6603]]]*/
/* Remove a file or directory `FILENAME' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify.remove") int
NOTHROW_RPC(LIBCCALL libc_remove)(char const *filename)
/*[[[body:remove]]]*/
{
	return removeat(AT_FDCWD, filename);
}
/*[[[end:remove]]]*/



/*[[[head:ftrylockfile,hash:CRC-32=0xd722c23a]]]*/
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

/*[[[head:funlockfile,hash:CRC-32=0x8bcf6d79]]]*/
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

/*[[[head:flockfile,hash:CRC-32=0xfd67d4fb]]]*/
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


/*[[[head:fflush,hash:CRC-32=0xde4ea3b3]]]*/
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.write.utility.fflush") int
(LIBCCALL libc_fflush)(FILE *stream)
		__THROWS(...)
/*[[[body:fflush]]]*/
{
	int result;
	if (!stream)
		return flushall();
	if (FMUSTLOCK(stream)) {
		file_write(stream);
		result = file_sync(stream);
		file_endwrite(stream);
	} else {
		result = file_sync(stream);
	}
	return result;
}
/*[[[end:fflush]]]*/

/*[[[head:fflush_unlocked,hash:CRC-32=0xd1e8ad1a]]]*/
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.write.utility.fflush_unlocked") int
(LIBCCALL libc_fflush_unlocked)(FILE *stream)
		__THROWS(...)
/*[[[body:fflush_unlocked]]]*/
{
	int result;
	if (!stream)
		return flushall_unlocked();
	result = file_sync(stream);
	return result;
}
/*[[[end:fflush_unlocked]]]*/



/*[[[head:fread,hash:CRC-32=0xbcbea33b]]]*/
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
	if (FMUSTLOCK(stream)) {
		file_write(stream);
		result = file_readdata(stream, buf, total);
		/* Unread the last partially read element. */
		if unlikely(result != total)
			file_seek(stream, -(result % elemsize), SEEK_CUR);
		file_endwrite(stream);
	} else {
		result = file_readdata(stream, buf, total);
		/* Unread the last partially read element. */
		if unlikely(result != total)
			file_seek(stream, -(result % elemsize), SEEK_CUR);
	}
	return result / elemsize;
}
/*[[[end:fread]]]*/

/*[[[head:fread_unlocked,hash:CRC-32=0xa5a4c13a]]]*/
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
	result = file_readdata(stream, buf, total);
	/* Unread the last partially read element. */
	if unlikely(result != total)
		file_seek(stream, -(result % elemsize), SEEK_CUR);
	return result / elemsize;
}
/*[[[end:fread_unlocked]]]*/

/*[[[head:fwrite,hash:CRC-32=0x3ad9c250]]]*/
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
	if (FMUSTLOCK(stream)) {
		file_write(stream);
		result = file_writedata(stream, buf, total);
		file_endwrite(stream);
	} else {
		result = file_writedata(stream, buf, total);
	}
	return result / elemsize;
}
/*[[[end:fwrite]]]*/

/*[[[head:fwrite_unlocked,hash:CRC-32=0xbecd53d0]]]*/
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
	result = file_writedata(stream, buf, total);
	return result / elemsize;
}
/*[[[end:fwrite_unlocked]]]*/

/*[[[head:file_printer,hash:CRC-32=0x9195b450]]]*/
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.write.write.file_printer") ssize_t
(LIBCCALL libc_file_printer)(void *arg,
                             char const *__restrict data,
                             size_t datalen)
		__THROWS(...)
/*[[[body:file_printer]]]*/
{
	FILE *me = (FILE *)arg;
	ssize_t result;
	if (FMUSTLOCK(me)) {
		file_write(me);
		result = (ssize_t)file_writedata(me, data, datalen * sizeof(char));
		if unlikely(!result && FERROR(me))
			result = -1;
		file_endwrite(me);
	} else {
		result = (ssize_t)file_writedata(me, data, datalen * sizeof(char));
		if unlikely(!result && FERROR(me))
			result = -1;
	}
	return result;
}
/*[[[end:file_printer]]]*/

/*[[[head:file_printer_unlocked,hash:CRC-32=0xafb946a0]]]*/
/* Same as `file_printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.write.write.file_printer_unlocked") ssize_t
(LIBCCALL libc_file_printer_unlocked)(void *arg,
                                      char const *__restrict data,
                                      size_t datalen)
		__THROWS(...)
/*[[[body:file_printer_unlocked]]]*/
{
	FILE *me = (FILE *)arg;
	ssize_t result;
	result = (ssize_t)file_writedata(me, data, datalen * sizeof(char));
	if unlikely(!result && FERROR(me))
		result = -1;
	return result;
}
/*[[[end:file_printer_unlocked]]]*/


/*[[[head:ftell,hash:CRC-32=0x9ade4155]]]*/
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
	result = file_seek(stream, 0, SEEK_CUR);
	file_endread(stream);
	if unlikely(result > LONG_MAX)
		return (long int)libc_seterrno(EOVERFLOW);
	return (long int)(off64_t)result;
}
/*[[[end:ftell]]]*/

/*[[[head:fseek,hash:CRC-32=0x36926aed]]]*/
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
	if (FMUSTLOCK(stream)) {
		file_write(stream);
		file_seek(stream, (off64_t)off, whence);
		result = unlikely(FERROR(stream)) ? -1 : 0;
		file_endwrite(stream);
	} else {
		file_seek(stream, (off64_t)off, whence);
		result = unlikely(FERROR(stream)) ? -1 : 0;
	}
	return result;
}
/*[[[end:fseek]]]*/

/*[[[head:ftello,hash:CRC-32=0xa30621b]]]*/
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
	result = file_seek(stream, 0, SEEK_CUR);
	file_endread(stream);
	if unlikely(result > INT32_MAX)
		return (off_t)libc_seterrno(EOVERFLOW);
	return (off_t)(pos_t)result;
}
/*[[[end:ftello]]]*/

/*[[[head:ftello64,hash:CRC-32=0xa063d212]]]*/
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
	result = file_seek(stream, 0, SEEK_CUR);
	file_endread(stream);
	if unlikely(result > INT64_MAX)
		return (off64_t)libc_seterrno(EOVERFLOW);
	return (off64_t)result;
}
#endif /* MAGIC:alias */
/*[[[end:ftello64]]]*/


/*[[[head:fseeko,hash:CRC-32=0xa8e9784a]]]*/
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
	if (FMUSTLOCK(stream)) {
		file_write(stream);
		file_seek(stream, (off64_t)off, whence);
		result = unlikely(FERROR(stream)) ? -1 : 0;
		file_endwrite(stream);
	} else {
		file_seek(stream, (off64_t)off, whence);
		result = unlikely(FERROR(stream)) ? -1 : 0;
	}
	return result;
}
/*[[[end:fseeko]]]*/

/*[[[head:fseeko64,hash:CRC-32=0x3b17d39a]]]*/
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
	if (FMUSTLOCK(stream)) {
		file_write(stream);
		file_seek(stream, (off64_t)off, whence);
		result = unlikely(FERROR(stream)) ? -1 : 0;
		file_endwrite(stream);
	} else {
		file_seek(stream, (off64_t)off, whence);
		result = unlikely(FERROR(stream)) ? -1 : 0;
	}
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:fseeko64]]]*/


/*[[[head:fgetpos,hash:CRC-32=0xf66d6385]]]*/
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

/*[[[head:fsetpos,hash:CRC-32=0xbabf8781]]]*/
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

/*[[[head:fgetpos64,hash:CRC-32=0x1d4fc892]]]*/
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

/*[[[head:fsetpos64,hash:CRC-32=0xd9692c8d]]]*/
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




/*[[[head:ftell_unlocked,hash:CRC-32=0xdc7f2980]]]*/
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
	result = file_seek(stream, 0, SEEK_CUR);
	if unlikely(result > LONG_MAX)
		return (long int)libc_seterrno(EOVERFLOW);
	return (long int)(off64_t)result;
}
/*[[[end:ftell_unlocked]]]*/

/*[[[head:ftello_unlocked,hash:CRC-32=0x8791586]]]*/
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
	result = file_seek(stream, 0, SEEK_CUR);
	if unlikely(result > INT32_MAX)
		return (off_t)libc_seterrno(EOVERFLOW);
	return (off_t)(pos_t)result;
}
/*[[[end:ftello_unlocked]]]*/

/*[[[head:ftello64_unlocked,hash:CRC-32=0x2b17cd17]]]*/
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
	result = file_seek(stream, 0, SEEK_CUR);
	if unlikely(result > INT64_MAX)
		return (off64_t)libc_seterrno(EOVERFLOW);
	return (off64_t)result;
}
#endif /* MAGIC:alias */
/*[[[end:ftello64_unlocked]]]*/

/*[[[head:fseek_unlocked,hash:CRC-32=0xe09291a2]]]*/
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
	file_seek(stream, (off64_t)off, whence);
	result = unlikely(FERROR(stream)) ? -1 : 0;
	return result;
}
/*[[[end:fseek_unlocked]]]*/

/*[[[head:fseeko_unlocked,hash:CRC-32=0xf1f15cff]]]*/
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
	file_seek(stream, (off64_t)off, whence);
	result = unlikely(FERROR(stream)) ? -1 : 0;
	return result;
}
/*[[[end:fseeko_unlocked]]]*/

/*[[[head:fseeko64_unlocked,hash:CRC-32=0x74065e39]]]*/
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
	file_seek(stream, (off64_t)off, whence);
	result = unlikely(FERROR(stream)) ? -1 : 0;
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:fseeko64_unlocked]]]*/

/*[[[head:fgetpos_unlocked,hash:CRC-32=0xbdf65bef]]]*/
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

/*[[[head:fsetpos_unlocked,hash:CRC-32=0x98021ac4]]]*/
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

/*[[[head:fgetpos64_unlocked,hash:CRC-32=0x6d9d3796]]]*/
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

/*[[[head:fsetpos64_unlocked,hash:CRC-32=0x491c4359]]]*/
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

/*[[[head:ungetc,hash:CRC-32=0xd879073d]]]*/
/* Unget a single character byte of data previously returned by `getc()' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.read.getc.ungetc") int
NOTHROW_NCX(LIBCCALL libc_ungetc)(int ch,
                                  FILE *__restrict stream)
/*[[[body:ungetc]]]*/
{
	int result;
	if unlikely(!stream) {
		libc_seterrno(EINVAL);
		return EOF;
	}
	if (FMUSTLOCK(stream)) {
		file_write(stream);
		result = file_ungetc(stream, (unsigned char)(unsigned int)ch);
		file_endwrite(stream);
	} else {
		result = file_ungetc(stream, (unsigned char)(unsigned int)ch);
	}
	return result;
}
/*[[[end:ungetc]]]*/

/*[[[head:ungetc_unlocked,hash:CRC-32=0xcb4cd356]]]*/
/* Unget a single character byte of data previously returned by `getc()' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.read.getc.ungetc_unlocked") int
NOTHROW_NCX(LIBCCALL libc_ungetc_unlocked)(int ch,
                                           FILE *__restrict stream)
/*[[[body:ungetc_unlocked]]]*/
{
	int result;
	if unlikely(!stream) {
		libc_seterrno(EINVAL);
		return EOF;
	}
	result = file_ungetc(stream, (unsigned char)(unsigned int)ch);
	return result;
}
/*[[[end:ungetc_unlocked]]]*/

/*[[[head:rewind,hash:CRC-32=0xb5df8874]]]*/
/* Rewind the current in-file position of `STREAM' to its starting position */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.seek.utility.rewind") void
(LIBCCALL libc_rewind)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:rewind]]]*/
{
	if likely(stream) {
		if (FMUSTLOCK(stream)) {
			file_write(stream);
			file_seek(stream, 0, SEEK_SET);
			stream->if_flag &= ~(IO_EOF | IO_ERR);
			file_endwrite(stream);
		} else {
			file_seek(stream, 0, SEEK_SET);
			stream->if_flag &= ~(IO_EOF | IO_ERR);
		}
	}
}
/*[[[end:rewind]]]*/

/*[[[head:rewind_unlocked,hash:CRC-32=0x45e63258]]]*/
/* Rewind the current in-file position of `STREAM' to its starting position */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.seek.utility.rewind_unlocked") void
(LIBCCALL libc_rewind_unlocked)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:rewind_unlocked]]]*/
{
	if likely(stream) {
		file_seek(stream, 0, SEEK_SET);
		stream->if_flag &= ~(IO_EOF | IO_ERR);
	}
}
/*[[[end:rewind_unlocked]]]*/

/*[[[head:fisatty,hash:CRC-32=0x14a18309]]]*/
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.io.tty.fisatty") int
NOTHROW_NCX(LIBCCALL libc_fisatty)(FILE *__restrict stream)
/*[[[body:fisatty]]]*/
{
	if unlikely(!stream) {
		libc_seterrno(EINVAL);
		return -1;
	}
	file_determine_isatty(stream);
	return (stream->if_flag & IO_ISATTY) != 0;
}
/*[[[end:fisatty]]]*/

/*[[[head:fftruncate,hash:CRC-32=0xe4d5e5ca]]]*/
/* >> fftruncate(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.utility.fftruncate") int
(LIBCCALL libc_fftruncate)(FILE *__restrict stream,
                           __PIO_OFFSET length)
		__THROWS(...)
/*[[[body:fftruncate]]]*/
{
	int result;
	if unlikely(!stream) {
		libc_seterrno(EINVAL);
		return -1;
	}
	if (FMUSTLOCK(stream)) {
		file_write(stream);
		result = file_truncate(stream, (pos64_t)length);
		file_endwrite(stream);
	} else {
		result = file_truncate(stream, (pos64_t)length);
	}
	return result;
}
/*[[[end:fftruncate]]]*/

/*[[[head:fftruncate_unlocked,hash:CRC-32=0x3e7de05c]]]*/
/* >> fftruncate_unlocked(3)
 * Same as `fftruncate()', but don't acquire a lock to the file */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.utility.fftruncate_unlocked") int
(LIBCCALL libc_fftruncate_unlocked)(FILE *__restrict stream,
                                    __PIO_OFFSET length)
		__THROWS(...)
/*[[[body:fftruncate_unlocked]]]*/
{
	int result;
	if unlikely(!stream) {
		libc_seterrno(EINVAL);
		return -1;
	}
	result = file_truncate(stream, (pos64_t)length);
	return result;
}
/*[[[end:fftruncate_unlocked]]]*/

/*[[[head:fftruncate64,hash:CRC-32=0x2823a266]]]*/
/* >> fftruncate64(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_fftruncate64, libc_fftruncate);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.utility.fftruncate64") int
(LIBCCALL libc_fftruncate64)(FILE *__restrict stream,
                             __PIO_OFFSET64 length)
		__THROWS(...)
/*[[[body:fftruncate64]]]*/
{
	int result;
	if unlikely(!stream) {
		libc_seterrno(EINVAL);
		return -1;
	}
	if (FMUSTLOCK(stream)) {
		file_write(stream);
		result = file_truncate(stream, (pos64_t)length);
		file_endwrite(stream);
	} else {
		result = file_truncate(stream, (pos64_t)length);
	}
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:fftruncate64]]]*/

/*[[[head:fftruncate64_unlocked,hash:CRC-32=0x3e678d0b]]]*/
/* >> fftruncate64_unlocked(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_fftruncate64_unlocked, libc_fftruncate_unlocked);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.utility.fftruncate64_unlocked") int
(LIBCCALL libc_fftruncate64_unlocked)(FILE *__restrict stream,
                                      __PIO_OFFSET64 length)
		__THROWS(...)
/*[[[body:fftruncate64_unlocked]]]*/
{
	int result;
	if unlikely(!stream) {
		libc_seterrno(EINVAL);
		return -1;
	}
	result = file_truncate(stream, (pos64_t)length);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:fftruncate64_unlocked]]]*/

/*[[[head:setvbuf,hash:CRC-32=0x821d8c5b]]]*/
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
	if (FMUSTLOCK(stream)) {
		file_write(stream);
		result = file_sync(stream);
		if likely(result == 0) {
			result = file_setmode(stream,
			                      buf,
			                      modes,
			                      bufsize);
		}
		file_endwrite(stream);
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
/*[[[end:setvbuf]]]*/

/*[[[head:setvbuf_unlocked,hash:CRC-32=0x5b37c233]]]*/
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
	result = file_sync(stream);
	if likely(result == 0) {
		result = file_setmode(stream,
		                      buf,
		                      modes,
		                      bufsize);
	}
	return result;
}
/*[[[end:setvbuf_unlocked]]]*/

/*[[[head:feof,hash:CRC-32=0x242fca39]]]*/
/* Check if end-of-file has been reached in `STREAM' */
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.read.utility.feof") int
NOTHROW_NCX(LIBCCALL libc_feof)(FILE __KOS_FIXED_CONST *__restrict stream)
/*[[[body:feof]]]*/
{
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	return FEOF(stream);
}
/*[[[end:feof]]]*/

/*[[[head:ferror,hash:CRC-32=0x12a3cbe2]]]*/
/* Check if an I/O error occurred in `STREAM' */
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.utility.ferror") int
NOTHROW_NCX(LIBCCALL libc_ferror)(FILE __KOS_FIXED_CONST *__restrict stream)
/*[[[body:ferror]]]*/
{
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	return FERROR(stream);
}
/*[[[end:ferror]]]*/

/*[[[head:clearerr,hash:CRC-32=0x5a580e13]]]*/
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

/*[[[head:tmpfile,hash:CRC-32=0x64fe2124]]]*/
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


/*[[[head:fopen,hash:CRC-32=0xae7d11d6]]]*/
/* Create and return a new file-stream for accessing `FILENAME' */
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.access.fopen") FILE *
NOTHROW_RPC(LIBCCALL libc_fopen)(char const *__restrict filename,
                                 char const *__restrict modes)
/*[[[body:fopen]]]*/
{
	/* TODO: (re-)add extension functions `fopenat()' and `fopenat64()'
	 *       that allow for the specification of `dfd' and `atflags' */
	fd_t fd;
	FILE *result;
	uint32_t flags;
	oflag_t oflags;
	flags = file_evalmodes(modes, &oflags);
	fd    = open(filename, oflags, 0644);
	if unlikely(fd < 0)
		return NULL;
	result = file_openfd(fd, flags);
	if unlikely(!result)
		sys_close(fd);
	return result;
}
/*[[[end:fopen]]]*/

/*[[[head:fdopen,hash:CRC-32=0x1f8a4143]]]*/
/* Open a new file stream by inheriting a given file descriptor `FD'
 * Note that upon success (`return != NULL'), the given `FD' will be `close()'d once `fclose(return)' is called */
INTERN WUNUSED NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.utility.fdopen") FILE *
NOTHROW_NCX(LIBCCALL libc_fdopen)(fd_t fd,
                                  char const *__restrict modes)
/*[[[body:fdopen]]]*/
{
	FILE *result;
	uint32_t flags;
	flags  = file_evalmodes(modes, NULL);
	result = file_openfd(fd, flags);
	return result;
}
/*[[[end:fdopen]]]*/

/*[[[head:fclose,hash:CRC-32=0x39fb2d00]]]*/
/* Close and destroy a given file `STREAM' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.access.fclose") int
(LIBCCALL libc_fclose)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fclose]]]*/
{
	if unlikely(!stream)
		return (int)libc_seterrno(EINVAL);
	file_decref(stream);
	return 0;
}
/*[[[end:fclose]]]*/

/*[[[head:fputc,hash:CRC-32=0x290bbe6]]]*/
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

/*[[[head:fputc_unlocked,hash:CRC-32=0x3241f95c]]]*/
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

/*[[[head:fileno,hash:CRC-32=0x3e5d2e52]]]*/
/* Return the underlying file descriptor number used by `STREAM' */
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.utility.fileno") fd_t
NOTHROW_NCX(LIBCCALL libc_fileno)(FILE *__restrict stream)
/*[[[body:fileno]]]*/
{
	if unlikely(!stream || (stream->if_flag & IO_HASVTAB))
		return (fd_t)libc_seterrno(EINVAL);
	return ATOMIC_READ(stream->if_fd);
}
/*[[[end:fileno]]]*/







/*[[[head:fgetc,hash:CRC-32=0x6878a3ba]]]*/
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.read.getc.fgetc") int
(LIBCCALL libc_fgetc)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fgetc]]]*/
{
	int result;
	if unlikely(!stream) {
		libc_seterrno(EINVAL);
		return EOF;
	}
	if (FMUSTLOCK(stream)) {
		file_write(stream);
		result = file_getc(stream);
		file_endwrite(stream);
	} else {
		result = file_getc(stream);
	}
	return result;
}
/*[[[end:fgetc]]]*/

/*[[[head:fgetc_unlocked,hash:CRC-32=0x35abb527]]]*/
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.unlocked.read.getc.fgetc_unlocked") int
(LIBCCALL libc_fgetc_unlocked)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fgetc_unlocked]]]*/
{
	int result;
	if unlikely(!stream) {
		libc_seterrno(EINVAL);
		return EOF;
	}
	result = file_getc(stream);
	return result;
}
/*[[[end:fgetc_unlocked]]]*/



/*[[[head:popen,hash:CRC-32=0xf06d3859]]]*/
/* Open and return a new process I/O stream for executing `COMMAND' */
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.access.popen") FILE *
NOTHROW_RPC(LIBCCALL libc_popen)(char const *command,
                                 char const *modes)
/*[[[body:popen]]]*/
{
	(void)command;
	(void)modes;
	CRT_UNIMPLEMENTED("popen"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:popen]]]*/

/*[[[impl:pclose]]]*/
DEFINE_INTERN_ALIAS(libc_pclose, libc_fclose);

/*[[[head:fopencookie,hash:CRC-32=0x3296b325]]]*/
INTERN WUNUSED NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.access.fopencookie") FILE *
NOTHROW_NCX(LIBCCALL libc_fopencookie)(void *__restrict magic_cookie,
                                       char const *__restrict modes,
                                       cookie_io_functions_t io_funcs)
/*[[[body:fopencookie]]]*/
{
	FILE *result;
	uint32_t flags;
	flags  = file_evalmodes(modes, NULL);
	result = file_opencookie(&io_funcs, magic_cookie, flags);
	return result;
}
/*[[[end:fopencookie]]]*/

/*[[[head:tmpnam_r,hash:CRC-32=0x6af8b66c]]]*/
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.utility.tmpnam_r") char *
NOTHROW_NCX(LIBCCALL libc_tmpnam_r)(char *buf)
/*[[[body:tmpnam_r]]]*/
{
	(void)buf;
	CRT_UNIMPLEMENTED("tmpnam_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:tmpnam_r]]]*/

/*[[[head:_fsopen,hash:CRC-32=0xba60465e]]]*/
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

/*[[[head:fcloseall,hash:CRC-32=0x3e1e7a50]]]*/
/* Alias for `_fcloseall()' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.utility.fcloseall") int
(LIBCCALL libc_fcloseall)(void)
		__THROWS(...)
/*[[[body:fcloseall]]]*/
{
	int result = 0;
	FILE *fp;
again:
	atomic_rwlock_write(&all_files_lock);
	fp = all_files;
	while (fp) {
		if (!file_tryincref(fp)) {
			fp = LLIST_NEXT(fp, if_exdata->io_link);
			continue;
		}
		LLIST_UNLINK(fp, if_exdata->io_link);
		LLIST_UNBIND(fp, if_exdata->io_link);
		atomic_rwlock_endwrite(&all_files_lock);
		/* !!!WARNING!!!
		 * This is entirely unsafe, but if you think about it:
		 * This function could only ever be entirely unsafe! */
		ATOMIC_WRITE(fp->if_exdata->io_refcnt, 1);
		file_decref(fp);
		++result;
		goto again;
	}
	atomic_rwlock_endwrite(&all_files_lock);
	return result;
}
/*[[[end:fcloseall]]]*/


struct memopen_cookie {
	byte_t *moc_base; /* [1..1] Base-pointer */
	byte_t *moc_cur;  /* [1..1] Current position */
	byte_t *moc_end;  /* [1..1] End-pointer */
};

PRIVATE ATTR_SECTION(".text.crt.FILE.utility.memopen.read")
ssize_t LIBCCALL memopen_read(void *cookie, char *buf, size_t num_bytes) {
	size_t maxlen;
	struct memopen_cookie *me;
	me = (struct memopen_cookie *)cookie;
	maxlen = (size_t)(me->moc_end - me->moc_cur);
	if (maxlen > num_bytes)
		maxlen = num_bytes;
	memcpy(buf, me->moc_cur, maxlen);
	me->moc_cur += maxlen;
	return (size_t)maxlen;
}

PRIVATE ATTR_SECTION(".text.crt.FILE.utility.memopen.write")
ssize_t LIBCCALL memopen_write(void *cookie, char const *buf, size_t num_bytes) {
	size_t maxlen;
	struct memopen_cookie *me;
	me = (struct memopen_cookie *)cookie;
	maxlen = (size_t)(me->moc_end - me->moc_cur);
	if (maxlen > num_bytes)
		maxlen = num_bytes;
	memcpy(me->moc_cur, buf, maxlen);
	me->moc_cur += maxlen;
	return (size_t)maxlen;
}

PRIVATE ATTR_SECTION(".text.crt.FILE.utility.memopen.seek")
int LIBCCALL memopen_seek(void *cookie, off64_t *pos, int whence) {
	pos64_t newpos;
	struct memopen_cookie *me;
	size_t maxlen;
	me = (struct memopen_cookie *)cookie;
	newpos = (pos64_t)*pos;
	maxlen = (size_t)(me->moc_end - me->moc_cur);
	switch (whence) {

	case SEEK_SET:
		break;

	case SEEK_CUR:
		newpos += (size_t)(me->moc_cur - me->moc_base);
		if ((off64_t)newpos < 0)
			goto err_EOVERFLOW;
		break;

	case SEEK_END:
		newpos += maxlen;
		if ((off64_t)newpos < 0)
			goto err_EOVERFLOW;
		break;

	default:
		libc_seterrno(EINVAL);
		return -1;
	}
	if (newpos > maxlen)
		newpos = maxlen;
	me->moc_cur = me->moc_base + (size_t)newpos;
	*pos = (off64_t)newpos;
	return 0;
err_EOVERFLOW:
	libc_seterrno(EOVERFLOW);
	return -1;
}

PRIVATE ATTR_SECTION(".text.crt.FILE.utility.memopen.close")
int LIBCCALL memopen_close(void *cookie) {
	free(cookie);
	return 0;
}



/*[[[head:fmemopen,hash:CRC-32=0xe54d8f29]]]*/
INTERN WUNUSED NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.access.fmemopen") FILE *
NOTHROW_NCX(LIBCCALL libc_fmemopen)(void *mem,
                                    size_t len,
                                    char const *modes)
/*[[[body:fmemopen]]]*/
{
	FILE *result;
	uint32_t flags;
	cookie_io_functions_t cookies;
	struct memopen_cookie *magic;
	magic = (struct memopen_cookie *)malloc(sizeof(struct memopen_cookie));
	if unlikely(!magic)
		return NULL;
	magic->moc_base = (byte_t *)mem;
	magic->moc_cur  = (byte_t *)mem;
	magic->moc_end  = (byte_t *)mem + len;
	cookies.read  = &memopen_read;
	cookies.write = &memopen_write;
	cookies.seek  = &memopen_seek;
	cookies.close = &memopen_close;
	flags  = file_evalmodes(modes, NULL);
	result = file_opencookie(&cookies, magic, flags);
	if unlikely(!result)
		free(magic);
	return result;
}
/*[[[end:fmemopen]]]*/



struct memstream_file {
	byte_t **mf_pbase; /* Pointer to the user-defined base field. */
	size_t  *mf_psize; /* Pointer to the user-defined size field. */
	byte_t  *mf_base;  /* [0..1][owned] Allocated base pointer. */
	byte_t  *mf_ptr;   /* [0..1] Current read/write pointer (May be located beyond `mf_end'; allocated lazily during writes). */
	byte_t  *mf_end;   /* [0..1] Allocated buffer end pointer. */
};

PRIVATE ATTR_SECTION(".text.crt.FILE.utility.memstream.read")
ssize_t LIBCCALL memstream_read(void *cookie, char *buf, size_t num_bytes) {
	struct memstream_file *me;
	me = (struct memstream_file *)cookie;
	size_t maxread = me->mf_end - me->mf_ptr;
	if (maxread > num_bytes)
		maxread = num_bytes;
	memcpy(buf, me->mf_ptr, maxread);
	me->mf_ptr += maxread;
	return (ssize_t)maxread;
}

PRIVATE ATTR_SECTION(".text.crt.FILE.utility.memstream.write")
ssize_t LIBCCALL memstream_write(void *cookie, char const *buf, size_t num_bytes) {
	struct memstream_file *me;
	size_t new_alloc, result = 0;
	byte_t *new_buffer;
	me = (struct memstream_file *)cookie;
	if likely(me->mf_ptr < me->mf_end) {
		result = me->mf_end - me->mf_ptr;
		if (result > num_bytes)
			result = num_bytes;
		memcpy(me->mf_ptr, buf, num_bytes);
		me->mf_ptr += result;
		buf += result;
		num_bytes -= result;
	}
	if (!num_bytes)
		goto done;
	/* Allocate more memory. */
	new_alloc = (size_t)(me->mf_ptr - me->mf_base);
	if unlikely(OVERFLOW_UADD(new_alloc, num_bytes, &new_alloc))
		goto err_EOVERFLOW;
	new_buffer = (byte_t *)realloc(me->mf_base,
	                               (new_alloc + 1) * sizeof(char));
	if unlikely(!new_buffer)
		goto err;
	me->mf_ptr  = new_buffer + (me->mf_ptr - me->mf_base);
	me->mf_base = new_buffer;
	me->mf_end  = new_buffer + new_alloc;
	/* Copy data into the new portion of the buf. */
	memcpy(me->mf_ptr, buf, num_bytes);
	*me->mf_end = 0; /* NUL-termination. */
	result += num_bytes;
	/* Update the user-given pointer locations with buf parameters. */
	*me->mf_pbase = me->mf_base;
	*me->mf_psize = (size_t)(me->mf_end - me->mf_base);
done:
	return (ssize_t)result;
err_EOVERFLOW:
	libc_seterrno(EOVERFLOW);
err:
	return -1;
}

PRIVATE ATTR_SECTION(".text.crt.FILE.utility.memstream.seek")
int LIBCCALL memstream_seek(void *cookie, off64_t *offset, int whence) {
	struct memstream_file *me;
	off64_t new_pos;
	me = (struct memstream_file *)cookie;
	new_pos = (size_t)(me->mf_ptr - me->mf_base);
	switch (whence) {

	case SEEK_SET:
		new_pos = *offset;
		break;

	case SEEK_CUR:
		new_pos += *offset;
		break;

	case SEEK_END:
		new_pos = (size_t)(me->mf_end - me->mf_base) - *offset;
		break;

	default:
		libc_seterrno(EINVAL);
		return -1;
	}
	if unlikely(new_pos < 0)
		goto err_EOVERFLOW;
	me->mf_ptr = me->mf_base + (size_t)new_pos;
	*offset      = (off64_t)new_pos;
	return 0;
err_EOVERFLOW:
	libc_seterrno(EOVERFLOW);
	return -1;
}

PRIVATE ATTR_SECTION(".text.crt.FILE.utility.memstream.close")
int LIBCCALL memstream_close(void *cookie) {
	free(cookie);
	return 0;
}

/*[[[head:open_memstream,hash:CRC-32=0x88256706]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.locked.access.open_memstream") FILE *
NOTHROW_NCX(LIBCCALL libc_open_memstream)(char **bufloc,
                                          size_t *sizeloc)
/*[[[body:open_memstream]]]*/
{
	FILE *result;
	cookie_io_functions_t cookies;
	struct memstream_file *magic;
	magic = (struct memstream_file *)malloc(sizeof(struct memstream_file));
	if unlikely(!magic)
		return NULL;
	magic->mf_pbase = (byte_t **)bufloc;
	magic->mf_psize = sizeloc;
	magic->mf_base  = NULL;
	magic->mf_ptr   = NULL;
	magic->mf_end   = NULL;
	cookies.read    = &memstream_read;
	cookies.write   = &memstream_write;
	cookies.seek    = &memstream_seek;
	cookies.close   = &memstream_close;
	result = file_opencookie(&cookies, magic, IO_RW);
	if unlikely(!result)
		free(magic);
	return result;
}
/*[[[end:open_memstream]]]*/


/*[[[impl:_filbuf]]]*/
/*[[[impl:_flsbuf]]]*/
DEFINE_INTERN_ALIAS(libc__filbuf, libc_fgetc_unlocked);
DEFINE_INTERN_ALIAS(libc__flsbuf, libc_fputc_unlocked);


/*[[[head:tmpnam,hash:CRC-32=0xbf2cf1b4]]]*/
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.utility.tmpnam") char *
NOTHROW_NCX(LIBCCALL libc_tmpnam)(char *buf)
/*[[[body:tmpnam]]]*/
{
	(void)buf;
	CRT_UNIMPLEMENTED("tmpnam"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:tmpnam]]]*/

/*[[[head:tempnam,hash:CRC-32=0xb00b230a]]]*/
INTERN ATTR_MALLOC WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.fs.utility.tempnam") char *
NOTHROW_NCX(LIBCCALL libc_tempnam)(char const *dir,
                                   char const *pfx)
/*[[[body:tempnam]]]*/
{
	(void)dir;
	(void)pfx;
	CRT_UNIMPLEMENTED("tempnam"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:tempnam]]]*/










/*[[[head:rename,hash:CRC-32=0xa02b3cdc]]]*/
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

/*[[[head:renameat,hash:CRC-32=0xbd605ee5]]]*/
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

/*[[[head:frenameat,hash:CRC-32=0x9c3ba45f]]]*/
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



/*[[[head:_rmtmp,hash:CRC-32=0x945037e3]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.utility._rmtmp") int
NOTHROW_RPC(LIBCCALL libc__rmtmp)(void)
/*[[[body:_rmtmp]]]*/
{
	CRT_UNIMPLEMENTED("_rmtmp"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_rmtmp]]]*/



/*[[[head:obstack_vprintf,hash:CRC-32=0x4e0b1367]]]*/
INTERN ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.obstack.obstack_vprintf") int
NOTHROW_NCX(LIBCCALL libc_obstack_vprintf)(struct obstack *__restrict obstack_,
                                           char const *__restrict format,
                                           va_list args)
/*[[[body:obstack_vprintf]]]*/
{
	(void)obstack_;
	(void)format;
	(void)args;
	CRT_UNIMPLEMENTED("obstack_vprintf"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:obstack_vprintf]]]*/


/*[[[head:_get_output_format,hash:CRC-32=0xfcb3e874]]]*/
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

/*[[[head:_set_output_format,hash:CRC-32=0x3be8f0f4]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.utility._set_output_format") uint32_t
NOTHROW_NCX(LIBCCALL libc__set_output_format)(uint32_t format)
/*[[[body:_set_output_format]]]*/
{
	(void)format;
	CRT_UNIMPLEMENTED("_set_output_format"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_set_output_format]]]*/

/*[[[head:_getmaxstdio,hash:CRC-32=0xcec925e8]]]*/
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

/*[[[head:_setmaxstdio,hash:CRC-32=0x88505f51]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.utility._setmaxstdio") int
NOTHROW_NCX(LIBCCALL libc__setmaxstdio)(int val)
/*[[[body:_setmaxstdio]]]*/
{
	(void)val;
	CRT_UNIMPLEMENTED("_setmaxstdio"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_setmaxstdio]]]*/

/*[[[head:_get_printf_count_output,hash:CRC-32=0xf6cff066]]]*/
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

/*[[[head:_set_printf_count_output,hash:CRC-32=0x2bf0d499]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.FILE.utility._set_printf_count_output") int
NOTHROW_NCX(LIBCCALL libc__set_printf_count_output)(int val)
/*[[[body:_set_printf_count_output]]]*/
{
	(void)val;
	CRT_UNIMPLEMENTED("_set_printf_count_output"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_set_printf_count_output]]]*/

PRIVATE ATTR_SECTION(".bss.crt.io.tty.cuserid_buffer") char cuserid_buffer[L_cuserid];

/*[[[head:cuserid,hash:CRC-32=0xf4e34131]]]*/
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

/*[[[head:fdreopen,hash:CRC-32=0xe6d00371]]]*/
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
	if (FMUSTLOCK(stream))
		file_write(stream);
	oldfd = stream->if_fd;
	if unlikely(fd == oldfd) {
		file_endwrite(stream);
		libc_seterrno(EBADF);
		stream = NULL;
		goto done;
	}
	stream->if_fd   = fd;
	stream->if_flag = IO_LNIFTYY | (stream->if_flag & IO_NOLOCK);
	if (FMUSTLOCK(stream))
		file_endwrite(stream);
	sys_close(oldfd);
done:
	return stream;
}
/*[[[end:fdreopen]]]*/

/*[[[head:fdreopen_unlocked,hash:CRC-32=0x3f798273]]]*/
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

/*[[[head:freopen,hash:CRC-32=0xac8268a7]]]*/
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
	uint32_t flags;
	oflag_t oflags;
	flags = file_evalmodes(modes, &oflags);
	fd    = open(filename, oflags, 0644);
	if unlikely(fd < 0)
		return NULL;
	if (FMUSTLOCK(stream)) {
		file_write(stream);
		result = file_reopenfd(stream, fd, flags);
		file_endwrite(stream);
	} else {
		result = file_reopenfd(stream, fd, flags);
	}
	if unlikely(!result)
		sys_close(fd);
	return result;
}
/*[[[end:freopen]]]*/

/*[[[head:freopen_unlocked,hash:CRC-32=0x5bc9ea07]]]*/
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
	uint32_t flags;
	oflag_t oflags;
	flags = file_evalmodes(modes, &oflags);
	fd    = open(filename, oflags, 0644);
	if unlikely(fd < 0)
		return NULL;
	result = file_reopenfd(stream, fd, flags);
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


#undef libc_feof_unlocked
#undef libc_ferror_unlocked
DEFINE_INTERN_ALIAS(libc_feof_unlocked, libc_feof);
DEFINE_INTERN_ALIAS(libc_ferror_unlocked, libc_ferror);

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x6295edbf]]]*/
#undef fprintf
#undef _IO_fprintf
#undef fprintf_unlocked
#undef fprintf_s
#undef printf
#undef _IO_printf
#undef printf_unlocked
#undef printf_s
#undef fscanf
#undef fscanf_unlocked
#undef fscanf_s
#undef scanf
#undef scanf_unlocked
#undef scanf_s
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
DEFINE_PUBLIC_WEAK_ALIAS(remove, libc_remove);
DEFINE_PUBLIC_WEAK_ALIAS(rename, libc_rename);
DEFINE_PUBLIC_WEAK_ALIAS(tmpnam, libc_tmpnam);
DEFINE_PUBLIC_WEAK_ALIAS(fclose, libc_fclose);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_fclose, libc_fclose);
DEFINE_PUBLIC_WEAK_ALIAS(_fclose_nolock, libc_fclose);
DEFINE_PUBLIC_WEAK_ALIAS(fflush, libc_fflush);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_fflush, libc_fflush);
DEFINE_PUBLIC_WEAK_ALIAS(setbuf, libc_setbuf);
DEFINE_PUBLIC_WEAK_ALIAS(setvbuf, libc_setvbuf);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_setvbuf, libc_setvbuf);
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
DEFINE_PUBLIC_WEAK_ALIAS(_IO_fputs, libc_fputs);
DEFINE_PUBLIC_WEAK_ALIAS(puts, libc_puts);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_puts, libc_puts);
DEFINE_PUBLIC_WEAK_ALIAS(ungetc, libc_ungetc);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_ungetc, libc_ungetc);
DEFINE_PUBLIC_WEAK_ALIAS(ungetc_unlocked, libc_ungetc);
DEFINE_PUBLIC_WEAK_ALIAS(fread, libc_fread);
DEFINE_PUBLIC_WEAK_ALIAS(fwrite, libc_fwrite);
DEFINE_PUBLIC_WEAK_ALIAS(fseek, libc_fseek);
DEFINE_PUBLIC_WEAK_ALIAS(fseek_unlocked, libc_fseek);
DEFINE_PUBLIC_WEAK_ALIAS(ftell, libc_ftell);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_ftell, libc_ftell);
DEFINE_PUBLIC_WEAK_ALIAS(ftell_unlocked, libc_ftell);
DEFINE_PUBLIC_WEAK_ALIAS(rewind, libc_rewind);
DEFINE_PUBLIC_WEAK_ALIAS(rewind_unlocked, libc_rewind);
DEFINE_PUBLIC_WEAK_ALIAS(clearerr, libc_clearerr);
DEFINE_PUBLIC_WEAK_ALIAS(clearerr_unlocked, libc_clearerr);
DEFINE_PUBLIC_WEAK_ALIAS(feof, libc_feof);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_feof, libc_feof);
DEFINE_PUBLIC_WEAK_ALIAS(feof_unlocked, libc_feof);
DEFINE_PUBLIC_WEAK_ALIAS(ferror, libc_ferror);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_ferror, libc_ferror);
DEFINE_PUBLIC_WEAK_ALIAS(ferror_unlocked, libc_ferror);
DEFINE_PUBLIC_WEAK_ALIAS(perror, libc_perror);
DEFINE_PUBLIC_WEAK_ALIAS(tmpfile, libc_tmpfile);
DEFINE_PUBLIC_WEAK_ALIAS(fopen, libc_fopen);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_fopen, libc_fopen);
DEFINE_PUBLIC_WEAK_ALIAS(fopen64, libc_fopen);
DEFINE_PUBLIC_WEAK_ALIAS(freopen, libc_freopen);
DEFINE_PUBLIC_WEAK_ALIAS(freopen64, libc_freopen);
DEFINE_PUBLIC_WEAK_ALIAS(freopen_unlocked, libc_freopen);
DEFINE_PUBLIC_WEAK_ALIAS(fgetpos, libc_fgetpos);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_fgetpos, libc_fgetpos);
DEFINE_PUBLIC_WEAK_ALIAS(fgetpos_unlocked, libc_fgetpos);
DEFINE_PUBLIC_WEAK_ALIAS(fsetpos, libc_fsetpos);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_fsetpos, libc_fsetpos);
DEFINE_PUBLIC_WEAK_ALIAS(fsetpos_unlocked, libc_fsetpos);
DEFINE_PUBLIC_WEAK_ALIAS(vfprintf, libc_vfprintf);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_vfprintf, libc_vfprintf);
DEFINE_PUBLIC_WEAK_ALIAS(vfprintf_s, libc_vfprintf);
DEFINE_PUBLIC_WEAK_ALIAS(fprintf, libc_fprintf);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_fprintf, libc_fprintf);
DEFINE_PUBLIC_WEAK_ALIAS(fprintf_unlocked, libc_fprintf);
DEFINE_PUBLIC_WEAK_ALIAS(fprintf_s, libc_fprintf);
DEFINE_PUBLIC_WEAK_ALIAS(vprintf, libc_vprintf);
DEFINE_PUBLIC_WEAK_ALIAS(vprintf_unlocked, libc_vprintf);
DEFINE_PUBLIC_WEAK_ALIAS(vprintf_s, libc_vprintf);
DEFINE_PUBLIC_WEAK_ALIAS(printf, libc_printf);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_printf, libc_printf);
DEFINE_PUBLIC_WEAK_ALIAS(printf_unlocked, libc_printf);
DEFINE_PUBLIC_WEAK_ALIAS(printf_s, libc_printf);
DEFINE_PUBLIC_WEAK_ALIAS(vfscanf, libc_vfscanf);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_vfscanf, libc_vfscanf);
DEFINE_PUBLIC_WEAK_ALIAS(__vfscanf, libc_vfscanf);
DEFINE_PUBLIC_WEAK_ALIAS(vfscanf_unlocked, libc_vfscanf);
DEFINE_PUBLIC_WEAK_ALIAS(_vfscanf, libc_vfscanf);
DEFINE_PUBLIC_WEAK_ALIAS(_vfscanf_s, libc_vfscanf);
DEFINE_PUBLIC_WEAK_ALIAS(vfscanf_s, libc_vfscanf);
DEFINE_PUBLIC_WEAK_ALIAS(vscanf, libc_vscanf);
DEFINE_PUBLIC_WEAK_ALIAS(vscanf_unlocked, libc_vscanf);
DEFINE_PUBLIC_WEAK_ALIAS(_vscanf, libc_vscanf);
DEFINE_PUBLIC_WEAK_ALIAS(_vscanf_s, libc_vscanf);
DEFINE_PUBLIC_WEAK_ALIAS(vscanf_s, libc_vscanf);
DEFINE_PUBLIC_WEAK_ALIAS(fscanf, libc_fscanf);
DEFINE_PUBLIC_WEAK_ALIAS(fscanf_unlocked, libc_fscanf);
DEFINE_PUBLIC_WEAK_ALIAS(fscanf_s, libc_fscanf);
DEFINE_PUBLIC_WEAK_ALIAS(scanf, libc_scanf);
DEFINE_PUBLIC_WEAK_ALIAS(scanf_unlocked, libc_scanf);
DEFINE_PUBLIC_WEAK_ALIAS(scanf_s, libc_scanf);
DEFINE_PUBLIC_WEAK_ALIAS(gets, libc_gets);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_gets, libc_gets);
DEFINE_PUBLIC_WEAK_ALIAS(vdprintf, libc_vdprintf);
DEFINE_PUBLIC_WEAK_ALIAS(dprintf, libc_dprintf);
DEFINE_PUBLIC_WEAK_ALIAS(renameat, libc_renameat);
DEFINE_PUBLIC_WEAK_ALIAS(removeat, libc_removeat);
DEFINE_PUBLIC_WEAK_ALIAS(frenameat, libc_frenameat);
DEFINE_PUBLIC_WEAK_ALIAS(tmpnam_r, libc_tmpnam_r);
DEFINE_PUBLIC_WEAK_ALIAS(setbuffer, libc_setbuffer);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_setbuffer, libc_setbuffer);
DEFINE_PUBLIC_WEAK_ALIAS(setlinebuf, libc_setlinebuf);
DEFINE_PUBLIC_WEAK_ALIAS(fflush_unlocked, libc_fflush_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(_fflush_nolock, libc_fflush_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fread_unlocked, libc_fread_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_fread, libc_fread_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(_fread_nolock, libc_fread_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fwrite_unlocked, libc_fwrite_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_fwrite, libc_fwrite_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(_fwrite_nolock, libc_fwrite_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fgetc_unlocked, libc_fgetc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(getc_unlocked, libc_fgetc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fputc_unlocked, libc_fputc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(putc_unlocked, libc_fputc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(tempnam, libc_tempnam);
DEFINE_PUBLIC_WEAK_ALIAS(_tempnam, libc_tempnam);
DEFINE_PUBLIC_WEAK_ALIAS(fdopen, libc_fdopen);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_fdopen, libc_fdopen);
DEFINE_PUBLIC_WEAK_ALIAS(_fdopen, libc_fdopen);
DEFINE_PUBLIC_WEAK_ALIAS(fileno, libc_fileno);
DEFINE_PUBLIC_WEAK_ALIAS(fileno_unlocked, libc_fileno);
DEFINE_PUBLIC_WEAK_ALIAS(_fileno, libc_fileno);
DEFINE_PUBLIC_WEAK_ALIAS(fmemopen, libc_fmemopen);
DEFINE_PUBLIC_WEAK_ALIAS(open_memstream, libc_open_memstream);
DEFINE_PUBLIC_WEAK_ALIAS(getdelim, libc_getdelim);
DEFINE_PUBLIC_WEAK_ALIAS(getline, libc_getline);
DEFINE_PUBLIC_WEAK_ALIAS(getchar_unlocked, libc_getchar_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(putchar_unlocked, libc_putchar_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(flockfile, libc_flockfile);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_flockfile, libc_flockfile);
DEFINE_PUBLIC_WEAK_ALIAS(_lock_file, libc_flockfile);
DEFINE_PUBLIC_WEAK_ALIAS(funlockfile, libc_funlockfile);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_funlockfile, libc_funlockfile);
DEFINE_PUBLIC_WEAK_ALIAS(_unlock_file, libc_funlockfile);
DEFINE_PUBLIC_WEAK_ALIAS(ftrylockfile, libc_ftrylockfile);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_ftrylockfile, libc_ftrylockfile);
DEFINE_PUBLIC_WEAK_ALIAS(cuserid, libc_cuserid);
DEFINE_PUBLIC_WEAK_ALIAS(popen, libc_popen);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_popen, libc_popen);
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
DEFINE_PUBLIC_WEAK_ALIAS(ftello64, libc_ftello64);
DEFINE_PUBLIC_WEAK_ALIAS(ftello64_unlocked, libc_ftello64);
DEFINE_PUBLIC_WEAK_ALIAS(_ftelli64, libc_ftello64);
DEFINE_PUBLIC_WEAK_ALIAS(fopen64, libc_fopen64);
DEFINE_PUBLIC_WEAK_ALIAS(freopen64, libc_freopen64);
DEFINE_PUBLIC_WEAK_ALIAS(freopen64_unlocked, libc_freopen64);
DEFINE_PUBLIC_WEAK_ALIAS(fgetpos64, libc_fgetpos64);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_fgetpos64, libc_fgetpos64);
DEFINE_PUBLIC_WEAK_ALIAS(fgetpos64_unlocked, libc_fgetpos64);
DEFINE_PUBLIC_WEAK_ALIAS(fsetpos64, libc_fsetpos64);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_fsetpos64, libc_fsetpos64);
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
DEFINE_PUBLIC_WEAK_ALIAS(_fseek_nolock, libc_fseek_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(ftell_unlocked, libc_ftell_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(_ftell_nolock, libc_ftell_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fseeko_unlocked, libc_fseeko_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(ftello_unlocked, libc_ftello_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(flushall_unlocked, libc_flushall_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fgetpos_unlocked, libc_fgetpos_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fsetpos_unlocked, libc_fsetpos_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(getw_unlocked, libc_getw_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(putw_unlocked, libc_putw_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(setvbuf_unlocked, libc_setvbuf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(ungetc_unlocked, libc_ungetc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(_ungetc_nolock, libc_ungetc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(getdelim_unlocked, libc_getdelim_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(getline_unlocked, libc_getline_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(rewind_unlocked, libc_rewind_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fisatty, libc_fisatty);
DEFINE_PUBLIC_WEAK_ALIAS(fftruncate, libc_fftruncate);
DEFINE_PUBLIC_WEAK_ALIAS(fftruncate_unlocked, libc_fftruncate_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(puts_unlocked, libc_puts_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fseeko64_unlocked, libc_fseeko64_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(_fseeki64_nolock, libc_fseeko64_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(ftello64_unlocked, libc_ftello64_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(_ftelli64_nolock, libc_ftello64_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fgetpos64_unlocked, libc_fgetpos64_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fsetpos64_unlocked, libc_fsetpos64_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fftruncate64, libc_fftruncate64);
DEFINE_PUBLIC_WEAK_ALIAS(fftruncate64_unlocked, libc_fftruncate64_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(vfprintf_unlocked, libc_vfprintf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fprintf_unlocked, libc_fprintf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(vprintf_unlocked, libc_vprintf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(printf_unlocked, libc_printf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(vfscanf_unlocked, libc_vfscanf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(vscanf_unlocked, libc_vscanf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fscanf_unlocked, libc_fscanf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(scanf_unlocked, libc_scanf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(_fsopen, libc__fsopen);
DEFINE_PUBLIC_WEAK_ALIAS(_flushall, libc__flushall);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_flush_all, libc__flushall);
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
DEFINE_PUBLIC_WEAK_ALIAS(_wperror, libc__wperror);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wperror, libd__wperror);
DEFINE_PUBLIC_WEAK_ALIAS(_fread_nolock_s, libc__fread_nolock_s);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_STDIO_C */
