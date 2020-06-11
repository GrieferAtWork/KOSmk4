/* HASH CRC-32:0xcde12514 */
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
#ifndef GUARD_LIBC_USER_STDIO_H
#define GUARD_LIBC_USER_STDIO_H 1

#include "../api.h"
#include "../auto/stdio.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <stdio.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Remove a file or directory `FILENAME' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_remove)(char const *filename);
/* Rename a given file `OLDNAME' to `NEWNAME_OR_PATH', or in the event
 * that `NEWNAME_OR_PATH' refers to a directory, place the file within. */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_rename)(char const *oldname, char const *newname_or_path);
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_tmpnam)(char *buf);
/* Close and destroy a given file `STREAM' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fclose)(FILE *__restrict stream) THROWS(...);
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
INTDEF int (LIBCCALL libc_fflush)(FILE *stream) THROWS(...);
/* Set the buffer and buffer-mode to-be used by the given `STREAM'
 * @param modes: One of `_IOFBF', `_IOLBF' or `_IONBF' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_setvbuf)(FILE *__restrict stream, char *__restrict buf, int modes, size_t bufsize);
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fgetc)(FILE *__restrict stream) THROWS(...);
/* Write a single character `CH' to `STREAM' */
INTDEF NONNULL((2)) int (LIBCCALL libc_fputc)(int ch, FILE *__restrict stream) THROWS(...);
/* Unget a single character byte of data previously returned by `getc()' */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_ungetc)(int ch, FILE *__restrict stream);
/* Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF' */
INTDEF WUNUSED NONNULL((1, 4)) size_t (LIBCCALL libc_fread)(void *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
/* Write up to `ELEMSIZE * ELEMCOUNT' bytes of data from `BUF' into `STREAM' */
INTDEF NONNULL((1, 4)) size_t (LIBCCALL libc_fwrite)(void const *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
/* Change the current in-file position of `STREAM' as a byte-offet from the start of the file */
INTDEF NONNULL((1)) int (LIBCCALL libc_fseek)(FILE *__restrict stream, long int off, int whence) THROWS(...);
/* Return the current in-file position of `STREAM' as a byte-offet from the start of the file */
INTDEF WUNUSED NONNULL((1)) long int (LIBCCALL libc_ftell)(FILE *__restrict stream) THROWS(...);
/* Rewind the current in-file position of `STREAM' to its starting position */
INTDEF NONNULL((1)) void (LIBCCALL libc_rewind)(FILE *__restrict stream) THROWS(...);
/* Clear the error state of `STREAM', returning the stream to normal operations mode */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_clearerr)(FILE *__restrict stream);
/* Check if end-of-file has been reached in `STREAM' */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_feof)(FILE __KOS_FIXED_CONST *__restrict stream);
/* Check if an I/O error occurred in `STREAM' */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_ferror)(FILE __KOS_FIXED_CONST *__restrict stream);
/* Create and return a new file-stream for accessing a temporary file for reading/writing */
INTDEF WUNUSED FILE *NOTHROW_RPC(LIBCCALL libc_tmpfile)(void);
/* Create and return a new file-stream for accessing `FILENAME' */
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_RPC(LIBCCALL libc_fopen)(char const *__restrict filename, char const *__restrict modes);
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
INTDEF NONNULL((1, 2, 3)) FILE *NOTHROW_RPC(LIBCCALL libc_freopen)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fgetpos)(FILE *__restrict stream, fpos_t *__restrict pos) THROWS(...);
/* Set the file position of `STREAM' to `POS', as previously initialized with a call to `fgetpos()' */
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fsetpos)(FILE *__restrict stream, fpos_t const *__restrict pos) THROWS(...);
INTDEF NONNULL((2, 4)) int NOTHROW_RPC(LIBCCALL libc_renameat)(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path);
/* Remove a file or directory `FILENAME' relative to a given base directory `DIRFD' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_removeat)(fd_t dirfd, char const *filename);
/* @param flags: Set of `0 | AT_DOSPATH' */
INTDEF NONNULL((2, 4)) int NOTHROW_RPC(LIBCCALL libc_frenameat)(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path, atflag_t flags);
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_tmpnam_r)(char *buf);
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
INTDEF int (LIBCCALL libc_fflush_unlocked)(FILE *stream) THROWS(...);
/* Same as `fread()', but performs I/O without acquiring a lock to `STREAM' */
INTDEF WUNUSED NONNULL((1, 4)) size_t (LIBCCALL libc_fread_unlocked)(void *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
/* Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM' */
INTDEF WUNUSED NONNULL((1, 4)) size_t (LIBCCALL libc_fwrite_unlocked)(void const *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fgetc_unlocked)(FILE *__restrict stream) THROWS(...);
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
INTDEF NONNULL((2)) int (LIBCCALL libc_fputc_unlocked)(int ch, FILE *__restrict stream) THROWS(...);
INTDEF ATTR_MALLOC WUNUSED char *NOTHROW_NCX(LIBCCALL libc_tempnam)(char const *dir, char const *pfx);
/* Open a new file stream by inheriting a given file descriptor `FD'
 * Note that upon success (`return != NULL'), the given `FD'
 * will be `close()'d once `fclose(return)' is called */
INTDEF WUNUSED NONNULL((2)) FILE *NOTHROW_NCX(LIBCCALL libc_fdopen)(fd_t fd, char const *__restrict modes);
/* Return the underlying file descriptor number used by `STREAM' */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_NCX(LIBCCALL libc_fileno)(FILE *__restrict stream);
INTDEF WUNUSED NONNULL((1, 3)) FILE *NOTHROW_NCX(LIBCCALL libc_fmemopen)(void *mem, size_t len, char const *modes);
INTDEF WUNUSED FILE *NOTHROW_NCX(LIBCCALL libc_open_memstream)(char **bufloc, size_t *sizeloc);
/* Acquire a lock to `STREAM' and block until doing so succeeds */
INTDEF NONNULL((1)) void NOTHROW_RPC(LIBCCALL libc_flockfile)(FILE *__restrict stream);
/* Release a previously acquired lock from `STREAM' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_funlockfile)(FILE *__restrict stream);
/* Try to acquire a lock to `STREAM' */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_ftrylockfile)(FILE *__restrict stream);
/* Return the name of the current user (`getpwuid(geteuid())'), storing
 * that name in `S'. When `S' is NULL, a static buffer is used instead */
INTDEF char *NOTHROW_NCX(LIBCCALL libc_cuserid)(char *s);
/* Open and return a new process I/O stream for executing `COMMAND' */
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_RPC(LIBCCALL libc_popen)(char const *command, char const *modes);
/* Close a process I/O file `STREAM' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_pclose)(FILE *stream);
/* Alias for `_fcloseall()' */
INTDEF int (LIBCCALL libc_fcloseall)(void) THROWS(...);
INTDEF WUNUSED NONNULL((2)) FILE *NOTHROW_NCX(LIBCCALL libc_fopencookie)(void *__restrict magic_cookie, char const *__restrict modes, cookie_io_functions_t io_funcs);
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_obstack_vprintf)(struct obstack *__restrict obstack_, char const *__restrict format, va_list args);
/* Change the current in-file position of `STREAM' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fseeko)(FILE *__restrict stream, off_t off, int whence) THROWS(...);
/* Return the current in-file position of `STREAM' */
INTDEF WUNUSED NONNULL((1)) off_t (LIBCCALL libc_ftello)(FILE *__restrict stream) THROWS(...);
/* 64-bit variant of `tmpfile' */
INTDEF WUNUSED FILE *NOTHROW_RPC(LIBCCALL libc_tmpfile64)(void);
/* 64-bit variant of `fseeko' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fseeko64)(FILE *__restrict stream, off64_t off, int whence) THROWS(...);
/* 64-bit variant of `ftello' */
INTDEF WUNUSED NONNULL((1)) off64_t (LIBCCALL libc_ftello64)(FILE *__restrict stream) THROWS(...);
/* 64-bit variant of `fopen' */
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_RPC(LIBCCALL libc_fopen64)(char const *__restrict filename, char const *__restrict modes);
/* 64-bit variant of `freopen' */
INTDEF NONNULL((1, 2, 3)) FILE *NOTHROW_RPC(LIBCCALL libc_freopen64)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* 64-bit variant of `fgetpos' */
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fgetpos64)(FILE *__restrict stream, fpos64_t *__restrict pos) THROWS(...);
/* 64-bit variant of `fsetpos' */
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fsetpos64)(FILE *__restrict stream, fpos64_t const *__restrict pos) THROWS(...);
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
INTDEF NONNULL((1, 2)) ssize_t (LIBCCALL libc_file_printer)(void *arg, char const *__restrict data, size_t datalen) THROWS(...);
/* Same as `file_printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTDEF NONNULL((1, 2)) ssize_t (LIBCCALL libc_file_printer_unlocked)(void *arg, char const *__restrict data, size_t datalen) THROWS(...);
/* Re-open the given `STREAM' as a file-stream for accessing `FD' */
INTDEF NONNULL((2, 3)) FILE *NOTHROW_RPC(LIBCCALL libc_fdreopen)(fd_t fd, char const *__restrict modes, FILE *__restrict stream);
/* Re-open the given `STREAM' as a file-stream for accessing `FD' */
INTDEF NONNULL((2, 3)) FILE *NOTHROW_RPC(LIBCCALL libc_fdreopen_unlocked)(fd_t fd, char const *__restrict modes, FILE *__restrict stream);
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
INTDEF NONNULL((1, 2, 3)) FILE *NOTHROW_RPC(LIBCCALL libc_freopen_unlocked)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
INTDEF NONNULL((1, 2, 3)) FILE *NOTHROW_RPC(LIBCCALL libc_freopen64_unlocked)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
INTDEF NONNULL((1)) int (LIBCCALL libc_fseek_unlocked)(FILE *__restrict stream, long int off, int whence) THROWS(...);
INTDEF NONNULL((1)) long int (LIBCCALL libc_ftell_unlocked)(FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1)) int (LIBCCALL libc_fseeko_unlocked)(FILE *__restrict stream, off_t off, int whence) THROWS(...);
INTDEF NONNULL((1)) off_t (LIBCCALL libc_ftello_unlocked)(FILE *__restrict stream) THROWS(...);
INTDEF int (LIBCCALL libc_flushall_unlocked)(void) THROWS(...);
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fgetpos_unlocked)(FILE *__restrict stream, fpos_t *__restrict pos) THROWS(...);
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fsetpos_unlocked)(FILE *__restrict stream, fpos_t const *__restrict pos) THROWS(...);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_setvbuf_unlocked)(FILE *__restrict stream, char *__restrict buf, int modes, size_t bufsize);
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_ungetc_unlocked)(int ch, FILE *__restrict stream);
INTDEF NONNULL((1)) void (LIBCCALL libc_rewind_unlocked)(FILE *__restrict stream) THROWS(...);
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_fisatty)(FILE *__restrict stream);
/* >> fftruncate(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fftruncate)(FILE *__restrict stream, __PIO_OFFSET length) THROWS(...);
/* >> fftruncate_unlocked(3)
 * Same as `fftruncate()', but don't acquire a lock to the file */
INTDEF NONNULL((1)) int (LIBCCALL libc_fftruncate_unlocked)(FILE *__restrict stream, __PIO_OFFSET length) THROWS(...);
INTDEF NONNULL((1)) int (LIBCCALL libc_fseeko64_unlocked)(FILE *__restrict stream, off64_t off, int whence) THROWS(...);
INTDEF WUNUSED NONNULL((1)) off64_t (LIBCCALL libc_ftello64_unlocked)(FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fgetpos64_unlocked)(FILE *__restrict stream, fpos64_t *__restrict pos) THROWS(...);
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fsetpos64_unlocked)(FILE *__restrict stream, fpos64_t const *__restrict pos) THROWS(...);
/* >> fftruncate64(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fftruncate64)(FILE *__restrict stream, __PIO_OFFSET64 length) THROWS(...);
/* >> fftruncate64_unlocked(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fftruncate64_unlocked)(FILE *__restrict stream, __PIO_OFFSET64 length) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_RPC(LIBCCALL libc__fsopen)(char const *filename, char const *modes, int sflag);
INTDEF int (LIBCCALL libc__flushall)(void) THROWS(...);
INTDEF int NOTHROW_RPC(LIBCCALL libc__rmtmp)(void);
INTDEF NONNULL((1)) int (LIBCCALL libc__filbuf)(FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((2)) int (LIBCCALL libc__flsbuf)(int ch, FILE *__restrict stream) THROWS(...);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__getmaxstdio)(void);
INTDEF int NOTHROW_NCX(LIBCCALL libc__setmaxstdio)(int val);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__get_printf_count_output)(void);
INTDEF int NOTHROW_NCX(LIBCCALL libc__set_printf_count_output)(int val);
INTDEF WUNUSED uint32_t NOTHROW_NCX(LIBCCALL libc__get_output_format)(void);
INTDEF uint32_t NOTHROW_NCX(LIBCCALL libc__set_output_format)(uint32_t format);
INTDEF ATTR_LIBC_SCANF(3, 5) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsnscanf_l)(char const *__restrict input, size_t inputlen, char const *__restrict format, locale_t locale, va_list args);
INTDEF ATTR_LIBC_SCANF(3, 5) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snscanf_l)(char const *__restrict input, size_t inputlen, char const *__restrict format, locale_t locale, ...);
INTDEF ATTR_LIBC_PRINTF_P(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__fprintf_p_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, ...) THROWS(...);
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_RPC(LIBCCALL libc_gets_s)(char *__restrict buf, rsize_t bufsize);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_STDIO_H */
