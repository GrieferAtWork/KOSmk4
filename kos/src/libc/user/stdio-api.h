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
#ifndef GUARD_LIBC_USER_STDIO_API_H
#define GUARD_LIBC_USER_STDIO_API_H 1

#include "../api.h"
/**/

#include <hybrid/atomic.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sync/atomic-owner-rwlock.h>

#include <asm/crt/stdio.h>
#include <asm/os/stdio.h>
#include <bits/crt/io-file.h>
#include <bits/crt/mbstate.h>
#include <kos/types.h>

#include <assert.h>
#include <stdint.h>

#include <libio.h>

#include "../libc/globals.h"

DECL_BEGIN

#undef EOF
#undef WEOF
#define EOF   __EOF
#define EOF16 ((char16_t)__WEOF16)
#define EOF32 ((char32_t)__WEOF32)

#ifndef __mbstate_t_defined
#define __mbstate_t_defined 1
typedef struct __mbstate mbstate_t;
#endif /* !__mbstate_t_defined */


#define IO_RW           __IO_FILE_IORW      /* The file was opened for read+write permissions ('+' flag) */
#define IO_MALLBUF      __IO_FILE_IOMALLBUF /* The buffer was allocated internally. */
#define IO_READING      __IO_FILE_IOREADING /* The buffer can be used for reading and writing. */
#define IO_FSYNC        __IO_FILE_IOCOMMIT  /* Also synchronize the underlying file after flushing the buffer. */
#define IO_NODYNSCALE   __IO_FILE_IOUSERBUF /* The buffer is not allowed to dynamically change its buffer size. */
#define IO_LNBUF        __IO_FILE_IOLNBUF   /* The buffer is line-buffered, meaning that it will
                                             * flush its data whenever a line-feed is printed.
                                             * Additionally if the `IO_ISATTY' flag is set,
                                             * attempting to read from a line-buffered file will cause
                                             * all other existing line-buffered files to be synchronized
                                             * first. This is done to ensure that interactive files are
                                             * always up-to-date before data is read from one of them. */
#define IO_LNIFTYY      __IO_FILE_IOLNIFTYY /* Automatically set/delete the `IO_LNBUF' and
                                             * `IO_ISATTY' flags, and add/remove the file from
                                             * `fb_ttys' the next time this comes into question. To determine
                                             * this, the pointed-to file is tested for being a TTY device
                                             * using `DeeFile_IsAtty(fb_file)'.
                                             * HINT: This flag is set for all newly created buffers by default. */
#define IO_ISATTY       __IO_FILE_IOISATTY  /* This buffer refers to a TTY device. */
#define IO_NOTATTY      __IO_FILE_IONOTATTY /* This buffer does not refer to a TTY device. */
#define IO_HASVTAB      __IO_FILE_IONOFD    /* The file uses a V-table, rather than a file descriptor. */
#ifdef __IO_FILE_IONOLOCK
#define IO_NOLOCK       __IO_FILE_IONOLOCK  /* The buffer does not perform any locking (s.a. `__fsetlocking()') */
#endif /* __IO_FILE_IONOLOCK */

/* Flags not defined by deemon, but required by the C standard. */
#define IO_EOF          __IO_FILE_IOEOF /* Set when the file pointed to by 'if_fd' has been exhausted. */
#define IO_ERR          __IO_FILE_IOERR /* Set when an I/O error occurred. */



/* NOTE: The KOS FILE type is derived from deemon's FileBuffer type.
 *       Flags re-appear using the following map:
 *          ~FILE_BUFFER_FSTATICBUF     <---> IO_MALLBUF
 *          ~FILE_BUFFER_FREADONLY      <---> IO_RW
 *          FILE_BUFFER_FSYNC           <---> IO_FSYNC
 *          FILE_BUFFER_FREADING        <---> IO_READING
 *          FILE_BUFFER_FNODYNSCALE     <---> IO_NODYNSCALE
 *          FILE_BUFFER_FLNBUF          <---> IO_LNBUF
 *          FILE_BUFFER_FLNIFTTY        <---> IO_LNIFTYY
 *          FILE_BUFFER_FISATTY         <---> IO_ISATTY
 *          FILE_BUFFER_FNOTATTY        <---> IO_NOTATTY
 *       Members re-appear using the following map:
 *          fb_lock  <---> if_exdata->io_lock
 *          fb_file  <---> IO_HASVTAB: if_exdata->io_vtab + if_exdata->io_magi
 *                        !IO_HASVTAB: if_fd
 *          fb_ptr   <---> if_ptr
 *          fb_cnt   <---> if_cnt
 *          fb_chng  <---> if_exdata->io_chng
 *          fb_chsz  <---> if_exdata->io_chsz
 *          fb_base  <---> if_base
 *          fb_size  <---> if_bufsiz
 *          fb_ttych <---> if_exdata->io_lnch
 *          fb_fblk  <---> if_exdata->io_fblk
 *          fb_fpos  <---> if_exdata->io_fpos
 *          fb_flag  <---> if_flag
 */

struct iofile_data_novtab {
	uintptr_t                  io_zero;   /* Always ZERO(0). - Required for binary compatibility with DOS. */
	__WEAK refcnt_t            io_refcnt; /* Reference counter. */
	struct atomic_owner_rwlock io_lock;   /* Lock for the file. */
	byte_t                    *io_chng;   /* [>= :if_base][+io_chsz <= :if_base + :if_bufsiz]
	                                       * [valid_if(io_chsz != 0)][lock(fb_lock)]
	                                       * Pointer to the first character that was
	                                       * changed since the buffer had been loaded. */
	size_t                     io_chsz;   /* [lock(fb_lock)] Amount of bytes that were changed. */
	LIST_ENTRY(FILE)           io_lnch;   /* [lock(changed_linebuffered_files_lock)][0..1] Chain of line-buffered file that
	                                       * have changed and must be flushed before another line-buffered file is read. */
	LIST_ENTRY(FILE)           io_link;   /* [lock(all_files_lock)][0..1] Entry in the global chain of open files. (Used
	                                       * by `fcloseall()', as well as flushing all open files during `exit()') */
	uintptr_t                  io_fver;   /* [lock(flushall_lock)] Last time that this file was flushed because of a
	                                       * global flush. */
	pos64_t                    io_fblk;   /* The starting address of the data block currently stored in `if_base'. */
	pos64_t                    io_fpos;   /* The current (assumed) position within the underlying file stream. */
	mbstate_t                  io_mbs;    /* MB State used for translating unicode data. */
};
#define IOFILE_DATA_NOVTAB_INIT()                          \
	{                                                      \
		/* .io_zero   = */ 0,                              \
		/* .io_refcnt = */ 2,                              \
		/* .io_lock   = */ ATOMIC_OWNER_RWLOCK_INIT,       \
		/* .io_chng   = */ NULL,                           \
		/* .io_chsz   = */ 0,                              \
		/* .io_lnch   = */ LIST_ENTRY_UNBOUND_INITIALIZER, \
		/* .io_link   = */ LIST_ENTRY_UNBOUND_INITIALIZER, \
		/* .io_fblk   = */ 0,                              \
		/* .io_fpos   = */ 0,                              \
		/* .io_mbs    = */ MBSTATE_INIT                    \
	}

struct iofile_data: iofile_data_novtab {
	/* All of the following fields only exist when `IO_HASVTAB' is set. */
	cookie_io_functions_t io_vtab; /* [const] File buffer */
	void                 *io_magi; /* [const] Magic cook */
};


#define FEOF(self)      ((self)->if_flag & IO_EOF)
#define FERROR(self)    ((self)->if_flag & IO_ERR)
#define FSETERROR(self) ((self)->if_flag |= IO_ERR)
#define FCLEARERR(self) ((self)->if_flag &= ~(IO_ERR | IO_EOF))
#ifdef IO_NOLOCK
#define FMUSTLOCK(self) (!((self)->if_flag & IO_NOLOCK))
#else /* IO_NOLOCK */
#define FMUSTLOCK(self) 1
#endif /* !IO_NOLOCK */

#define IOBUF_FACTOR             4    /* Try to scale up the I/O buffer, such that bufsize ~= FPOS / IOBUF_FACTOR */
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

/* TODO: Use <kos/refcnt.h> for reference counting, rather than these inline functions here! */

LOCAL NONNULL((1)) ATTR_SECTION(".text.crt.FILE.core.utility.file_tryincref")
WUNUSED bool LIBCCALL file_tryincref(FILE *__restrict self) {
	refcnt_t refcnt;
	struct iofile_data *ex;
	assert(self);
	ex = self->if_exdata;
	assert(ex);
	do {
		refcnt = ATOMIC_READ(ex->io_refcnt);
		if unlikely(refcnt == 0)
			return false;
	} while (!ATOMIC_CMPXCH_WEAK(ex->io_refcnt, refcnt, refcnt + 1));
	return true;
}

LOCAL NONNULL((1)) ATTR_SECTION(".text.crt.FILE.core.utility.file_incref")
void LIBCCALL file_incref(FILE *__restrict self) {
#ifdef NDEBUG
	struct iofile_data *ex;
	assert(self);
	ex = self->if_exdata;
	assert(ex);
	ATOMIC_INC(ex->io_refcnt);
#else /* NDEBUG */
	bool ok;
	ok = file_tryincref(self);
	assert(ok);
#endif /* !NDEBUG */
}

INTDEF NONNULL((1)) void LIBCCALL file_decref(FILE *__restrict self);

/* Synchronize unwritten data of all line-buffered files. */
INTDEF void LIBCCALL file_sync_lnfiles(void);

/* Determine if `self' is a TTY */
INTDEF NONNULL((1)) void LIBCCALL file_determine_isatty(FILE *__restrict self);
INTDEF NONNULL((1)) int LIBCCALL file_sync(FILE *__restrict self);

/* High-level, common read-from-file function. */
INTDEF NONNULL((1)) size_t LIBCCALL file_readdata(FILE *__restrict self, void *buf, size_t num_bytes);

/* High-level, common write-to-file function. */
INTDEF NONNULL((1)) size_t LIBCCALL file_writedata(FILE *__restrict self, void const *buf, size_t num_bytes);
INTDEF NONNULL((1)) pos64_t LIBCCALL file_seek(FILE *__restrict self, off64_t off, int whence);
INTDEF WUNUSED NONNULL((1)) int LIBCCALL file_getc(FILE *__restrict self);
INTDEF WUNUSED NONNULL((1)) int LIBCCALL file_ungetc(FILE *__restrict self, unsigned char ch);
INTDEF WUNUSED NONNULL((1)) int LIBCCALL file_truncate(FILE *__restrict self, pos64_t new_size);

/* Unicode integration */
INTDEF WUNUSED NONNULL((1)) char16_t LIBCCALL file_getc16(FILE *__restrict self);
INTDEF WUNUSED NONNULL((1)) char16_t LIBCCALL file_ungetc16(FILE *__restrict self, char16_t ch);
INTDEF WUNUSED NONNULL((1)) char32_t LIBCCALL file_getc32(FILE *__restrict self);
INTDEF WUNUSED NONNULL((1)) char32_t LIBCCALL file_ungetc32(FILE *__restrict self, char32_t ch);

/* 8/16/32-bit format-printers for FILE objects. */
INTDEF WUNUSED NONNULL((1)) ssize_t LIBCCALL file_print16(void *self, char16_t const *__restrict data, size_t datalen);
INTDEF WUNUSED NONNULL((1)) ssize_t LIBCCALL file_print32(void *self, char32_t const *__restrict data, size_t datalen);


/* @param: poflags: When non-NULL, filled with `O_*'
 * @return: * :     Set of `IO_*' */
INTDEF WUNUSED uint32_t LIBCCALL file_evalmodes(char const *modes, oflag_t *poflags);
/* @param: flags: Set of `IO_*' */
INTDEF WUNUSED FILE *LIBCCALL file_openfd(/*inherit(on_success)*/ fd_t fd, uint32_t flags);
INTDEF WUNUSED NONNULL((1)) FILE *LIBCCALL file_reopenfd(FILE *__restrict self, fd_t fd, uint32_t flags);
INTDEF WUNUSED NONNULL((1)) FILE *LIBCCALL file_opencookie(cookie_io_functions_t const *__restrict io, void *magic, uint32_t flags);


DECL_END

#endif /* !GUARD_LIBC_USER_STDIO_API_H */
