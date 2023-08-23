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
#ifndef GUARD_LIBC_USER_STDIO_API_H
#define GUARD_LIBC_USER_STDIO_API_H 1

#include "../api.h"
/**/

#include <hybrid/sequence/list.h>

#include <asm/crt/stdio.h>
#include <asm/os/stdio.h>
#include <bits/crt/io-file.h>
#include <bits/crt/mbstate.h>
#include <kos/refcnt.h>
#include <kos/sched/shared-recursive-rwlock.h>
#include <kos/types.h>

#include <assert.h>
#include <stdint.h>

#include <libio.h>

#include "../libc/globals.h"

DECL_BEGIN

#ifndef EOF
#define EOF __EOF
#endif /* !EOF */

#ifndef WEOF16
#define WEOF16 __WEOF16
#define WEOF32 __WEOF32
#endif /* !WEOF16 */

#ifndef __mbstate_t_defined
#define __mbstate_t_defined
typedef struct __mbstate mbstate_t;
#endif /* !__mbstate_t_defined */


#define IO_RW           __IO_FILE_IORW      /* The file was opened for read+write permissions ('+' flag) */
#define IO_MALLBUF      __IO_FILE_IOMALLBUF /* The buffer was allocated internally. */
#define IO_READING      __IO_FILE_IOREADING /* The buffer can be used for reading and writing. */
#define IO_FSYNC        __IO_FILE_IOCOMMIT  /* Also synchronize the underlying file after flushing the buffer. */
#define IO_NODYNSCALE   __IO_FILE_IOUSERBUF /* The buffer is not allowed to dynamically change its buffer size. */
#define IO_LNBUF        __IO_FILE_IOLNBUF   /* The buffer is line-buffered, meaning that it will
                                             * flush  its data whenever  a line-feed is printed.
                                             * Additionally if the `IO_ISATTY' flag is set,
                                             * attempting to read from  a line-buffered file will  cause
                                             * all other existing line-buffered files to be synchronized
                                             * first. This is done to ensure that interactive files  are
                                             * always up-to-date before data is read from one of them. */
#define IO_LNIFTYY      __IO_FILE_IOLNIFTYY /* Automatically  set/delete  the  `IO_LNBUF'  and
                                             * `IO_ISATTY' flags, and add/remove the file from
                                             * `fb_ttys' the next time this comes into question. To determine
                                             * this, the pointed-to  file is  tested for being  a TTY  device
                                             * using `DeeFile_IsAtty(fb_file)'.
                                             * HINT: This flag is set for all newly created buffers by default. */
#define IO_ISATTY       __IO_FILE_IOISATTY  /* This buffer refers to a TTY device. */
#define IO_NOTATTY      __IO_FILE_IONOTATTY /* This buffer does not refer to a TTY device. */
#define IO_HASVTAB      __IO_FILE_IONOFD    /* The file uses a V-table, rather than a file descriptor. */
#ifdef __IO_FILE_IONOLOCK
#define IO_NOLOCK       __IO_FILE_IONOLOCK  /* The buffer does not perform any locking (s.a. `__fsetlocking()') */
#define _IO_NOLOCK_OPT  __IO_FILE_IONOLOCK  /* The buffer does not perform any locking (s.a. `__fsetlocking()') */
#else /* __IO_FILE_IONOLOCK */
#define _IO_NOLOCK_OPT  0
#endif /* !__IO_FILE_IONOLOCK */

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
 *          fb_lock        <---> if_exdata->io_lock
 *          fb_file        <---> IO_HASVTAB:  iofile_data::io_*fn + iofile_data::io_cookie
 *                               !IO_HASVTAB: if_fd
 *          fb_ptr         <---> if_ptr
 *          fb_cnt         <---> if_cnt
 *          fb_chng        <---> if_exdata->io_chng
 *          fb_chsz        <---> if_exdata->io_chsz
 *          fb_base        <---> if_base
 *          fb_size        <---> if_bufsiz
 *          fb_ttych       <---> if_exdata->io_lnch
 *          fb_fblk        <---> if_exdata->io_fblk
 *          fb_fpos        <---> if_exdata->io_fpos
 *          fb_flag        <---> if_flag
 */

struct iofile_data_novtab {
	/* TODO: Add support for using mmap(2) to map files and thereby implement read/write */
	uintptr_t                      io_zero;   /* Always ZERO(0). - Required for binary compatibility with DOS. */
	__WEAK refcnt_t                io_refcnt; /* Reference counter. */
	char                          *io_getln;  /* [0..1] malloc'd buffer for `fgetln(3)' (no lock, because
	                                           * only used by `fgetln()', which is already thread-unsafe) */
	struct shared_recursive_rwlock io_lock;   /* Lock for the file. */
	byte_t                        *io_chng;   /* [>= :if_base][+io_chsz <= :if_base + :if_bufsiz]
	                                           * [valid_if(io_chsz != 0)][lock(io_lock)]
	                                           * Pointer to the  first character that  was
	                                           * changed since the buffer had been loaded. */
	size_t                         io_chsz;   /* [lock(io_lock)] Amount of bytes that were changed. */
	LIST_ENTRY(FILE)               io_lnch;   /* [lock(changed_linebuffered_files_lock)][0..1] Chain of line-buffered file that
	                                           * have  changed and must  be flushed before another  line-buffered file is read. */
	LIST_ENTRY(FILE)               io_link;   /* [lock(all_files_lock)][0..1] Entry  in  the  global chain  of  open  files.
	                                           * (Used by `fcloseall()', as well as flushing all open files during `exit()') */
	uintptr_t                      io_fver;   /* [lock(flushall_lock)] Last time that this file was flushed because of a global flush. */
	pos64_t                        io_fblk;   /* [lock(io_lock)] The starting address of the data block currently stored in `if_base'. */
	pos64_t                        io_fpos;   /* [lock(io_lock)] The current (assumed) position within the underlying file stream. */
	mbstate_t                      io_mbs;    /* [lock(io_lock)] MB State used for translating unicode data. */
};
#define IOFILE_DATA_NOVTAB_INIT()                    \
	{                                                \
		.io_zero   = 0,                              \
		.io_refcnt = 2,                              \
		.io_lock   = SHARED_RECURSIVE_RWLOCK_INIT,   \
		.io_chng   = NULL,                           \
		.io_chsz   = 0,                              \
		.io_lnch   = LIST_ENTRY_UNBOUND_INITIALIZER, \
		.io_link   = LIST_ENTRY_UNBOUND_INITIALIZER, \
		.io_fblk   = 0,                              \
		.io_fpos   = 0,                              \
		.io_mbs    = MBSTATE_INIT                    \
	}

/* Prototypes for the *actual* low-level callbacks that can be hooked for FILE I/O */
typedef ssize_t (LIBKCALL *__funopen2_readfn_t)(void *cookie, void *buf, size_t num_bytes);
typedef ssize_t (LIBKCALL *__funopen2_writefn_t)(void *cookie, void const *buf, size_t num_bytes);
typedef off_t (LIBKCALL *__funopen2_seekfn_t)(void *cookie, off_t off, int whence);
typedef off64_t (LIBKCALL *__funopen2_64_seekfn_t)(void *cookie, off64_t off, int whence);
typedef int (LIBKCALL *__funopen2_flushfn_t)(void *cookie);
typedef int (LIBKCALL *__funopen2_closefn_t)(void *cookie);

struct iofile_data: iofile_data_novtab {
	/* All of the following fields only exist when `IO_HASVTAB' is set. */
	__funopen2_readfn_t    io_readfn;  /* [0..1][const] Read function */
	__funopen2_writefn_t   io_writefn; /* [0..1][const] Write function */
	__funopen2_64_seekfn_t io_seekfn;  /* [0..1][const] Seek function */
	__funopen2_flushfn_t   io_flushfn; /* [0..1][const] Flush function */
	__funopen2_closefn_t   io_closefn; /* [0..1][const] Close function */
	void                  *io_cookie;  /* [?..?][const] Magic cookie */
};


#define FEOF(self)      ((self)->if_flag & IO_EOF)
#define FERROR(self)    ((self)->if_flag & IO_ERR)
#define FSETERROR(self) ((self)->if_flag |= IO_ERR)
#define FCLEARERR(self) ((self)->if_flag &= ~(IO_ERR | IO_EOF))
#ifdef IO_NOLOCK
/* likely since it's the default, and few programs bother to change it */
#define FMUSTLOCK(self) likely(!((self)->if_flag & IO_NOLOCK))
#else /* IO_NOLOCK */
#define FMUSTLOCK(self) 1
#endif /* !IO_NOLOCK */

#define IOBUF_FACTOR             4    /* Try to scale up the I/O buffer, such that bufsize ~= FPOS / IOBUF_FACTOR */
#define IOBUF_MAX                8192
#define IOBUF_MIN                512
#define IOBUF_RELOCATE_THRESHOLD 2048 /* When >= this amount of bytes are unused in the buffer, free them. */

/* File locking helpers. */
#define file_lock_reading(x)     shared_recursive_rwlock_reading(&(x)->if_exdata->io_lock)
#define file_lock_writing(x)     shared_recursive_rwlock_writing(&(x)->if_exdata->io_lock)
#define file_lock_tryread(x)     shared_recursive_rwlock_tryread(&(x)->if_exdata->io_lock)
#define file_lock_trywrite(x)    shared_recursive_rwlock_trywrite(&(x)->if_exdata->io_lock)
#define file_lock_tryupgrade(x)  shared_recursive_rwlock_tryupgrade(&(x)->if_exdata->io_lock)
#define file_lock_read(x)        shared_recursive_rwlock_read(&(x)->if_exdata->io_lock)
#define file_lock_write(x)       shared_recursive_rwlock_write(&(x)->if_exdata->io_lock)
#define file_lock_upgrade(x)     shared_recursive_rwlock_upgrade(&(x)->if_exdata->io_lock)
#define file_lock_downgrade(x)   shared_recursive_rwlock_downgrade(&(x)->if_exdata->io_lock)
#define file_lock_endread(x)     shared_recursive_rwlock_endread(&(x)->if_exdata->io_lock)
#define file_lock_endwrite(x)    shared_recursive_rwlock_endwrite(&(x)->if_exdata->io_lock)

/* Destroy the given file */
INTDEF NONNULL((1)) void LIBCCALL file_destroy(FILE *__restrict self);
__DEFINE_REFCNT_FUNCTIONS(FILE, if_exdata->io_refcnt, file_destroy);


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
INTERN WUNUSED NONNULL((1)) int LIBCCALL file_sungetc(FILE *__restrict self);
INTDEF WUNUSED NONNULL((1)) int LIBCCALL file_truncate(FILE *__restrict self, pos64_t new_size);

/* @param: poflags: When non-NULL, filled with `O_*'
 * @return: * :     Set of `IO_*' */
INTDEF WUNUSED uint32_t LIBCCALL file_evalmodes(char const *modes, oflag_t *poflags);
/* @param: flags: Set of `IO_*' */
INTDEF WUNUSED FILE *LIBCCALL file_openfd(/*inherit(on_success)*/ fd_t fd, uint32_t flags);
INTDEF WUNUSED NONNULL((1)) FILE *LIBCCALL file_reopenfd(FILE *__restrict self, fd_t fd, uint32_t flags);


#undef FILE_HAVE_UOFFSET
#if __SIZEOF_POINTER__ < 8
#define FILE_HAVE_UOFFSET 1
#endif /* __SIZEOF_POINTER__ < 8 */


/* Offset from the base of a user-FILE object to the start of the
 * internal FILE. Usually `0', but may be larger in compatibility
 * mode. */
#ifdef FILE_HAVE_UOFFSET
INTDEF ptrdiff_t file_uoffset;
#endif /* FILE_HAVE_UOFFSET */

/* Pack/unpack a user-given FILE object. */
#ifdef FILE_HAVE_UOFFSET
#define file_fromuser(ptr)     ((FILE *)((byte_t *)(ptr) + file_uoffset))
#define file_fromuser_opt(ptr) ((FILE *)((ptr) ? (byte_t *)(ptr) + file_uoffset : (byte_t *)(ptr)))
#define file_touser(ptr)       ((FILE *)((byte_t *)(ptr) - file_uoffset))
#define file_touser_opt(ptr)   ((FILE *)((ptr) ? (byte_t *)(ptr) - file_uoffset : (byte_t *)(ptr)))
#define file_free(self)        free((byte_t *)(self) - file_uoffset)
INTDEF WUNUSED FILE *__FCALL file_calloc(size_t extsize); /* Defined in "../libc/compat.c" */
#else /* FILE_HAVE_UOFFSET */
#define file_fromuser(ptr)     (ptr)
#define file_fromuser_opt(ptr) (ptr)
#define file_touser(ptr)       (ptr)
#define file_touser_opt(ptr)   (ptr)
#define file_free(self)        free(self)
#define file_calloc(extsize)   ((FILE *)calloc(sizeof(FILE) + (extsize)))
#endif /* !FILE_HAVE_UOFFSET */

#undef __CCAST
#define __CCAST(T) /* Nothing */
#if EOF == -1
#define libc_seterrno_and_return_EOF(eno) libc_seterrno(eno)
#else /* EOF == -1 */
#define libc_seterrno_and_return_EOF(eno) (libc_seterrno(eno), EOF)
#endif /* EOF != -1 */
#if (WEOF16 & 0xffff) == (-1 & 0xffff)
#define libc_seterrno_and_return_WEOF16(eno) ((wint16_t)libc_seterrno(eno))
#else /* (WEOF16 & 0xffff) == (-1 & 0xffff) */
#define libc_seterrno_and_return_WEOF16(eno) (libc_seterrno(eno), WEOF16)
#endif /* (WEOF16 & 0xffff) != (-1 & 0xffff) */
#if (WEOF32 & 0xffffffff) == (-1 & 0xffffffff)
#define libc_seterrno_and_return_WEOF32(eno) ((wint32_t)libc_seterrno(eno))
#else /* (WEOF32 & 0xffffffff) == (-1 & 0xffffffff) */
#define libc_seterrno_and_return_WEOF32(eno) (libc_seterrno(eno), WEOF32)
#endif /* (WEOF32 & 0xffffffff) != (-1 & 0xffffffff) */
#undef __CCAST
#define __CCAST /* Nothing */

DECL_END

#endif /* !GUARD_LIBC_USER_STDIO_API_H */
