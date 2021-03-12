/* HASH CRC-32:0x54b4f411 */
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
#ifndef GUARD_LIBC_USER_STDIO_H
#define GUARD_LIBC_USER_STDIO_H 1

#include "../api.h"
#include "../auto/stdio.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <stdio.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> remove(3)
 * Remove a file or directory `filename' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_remove)(char const *filename);
/* >> rename(3)
 * Rename a given file `oldname' to `newname_or_path', or in the event
 * that `newname_or_path' refers to a directory, place the file within. */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_rename)(char const *oldname, char const *newname_or_path);
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_tmpnam)(char *buf);
/* >> fclose(3)
 * Close and destroy a given file `stream' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fclose)(FILE *__restrict stream) THROWS(...);
/* >> fflush(3)
 * Flush any unwritten data from `stream' to the underlying filesystem/TTY */
INTDEF int (LIBCCALL libc_fflush)(FILE *stream) THROWS(...);
/* >> setvbuf(3)
 * Set the buffer and buffer-mode to-be used by the given `stream'
 * @param modes: One of `_IOFBF', `_IOLBF' or `_IONBF' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_setvbuf)(FILE *__restrict stream, char *__restrict buf, __STDC_INT_AS_UINT_T modes, size_t bufsize);
/* >> fgetc(3)
 * Read and return a single character from `stream'
 * If the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fgetc)(FILE *__restrict stream) THROWS(...);
/* >> fputc(3)
 * Write a single character `ch' to `stream' */
INTDEF NONNULL((2)) int (LIBCCALL libc_fputc)(int ch, FILE *__restrict stream) THROWS(...);
/* >> ungetc(3)
 * Unget a single character byte of data previously returned by `getc()' */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_ungetc)(int ch, FILE *__restrict stream);
/* >> fread(3)
 * Read up to `elemsize * elemcount' bytes of data from `stream' into `buf' */
INTDEF WUNUSED NONNULL((1, 4)) size_t (LIBCCALL libc_fread)(void *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
/* >> fwrite(3)
 * Write up to `elemsize * elemcount' bytes of data from `buf' into `stream' */
INTDEF NONNULL((1, 4)) size_t (LIBCCALL libc_fwrite)(void const *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
/* >> fseek(3)
 * Change the current in-file position of `stream' as a byte-offet from the start of the file */
INTDEF NONNULL((1)) int (LIBCCALL libc_fseek)(FILE *__restrict stream, long int off, int whence) THROWS(...);
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offet from the start of the file */
INTDEF WUNUSED NONNULL((1)) long int (LIBCCALL libc_ftell)(FILE *__restrict stream) THROWS(...);
/* >> rewind(3)
 * Rewind the current in-file position of `stream' to its starting position */
INTDEF NONNULL((1)) void (LIBCCALL libc_rewind)(FILE *__restrict stream) THROWS(...);
/* >> clearerr(3)
 * Clear the error state of `stream', returning the stream to normal operations mode */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_clearerr)(FILE *__restrict stream);
/* >> feof(3)
 * Check if end-of-file has been reached in `stream' */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_feof)(FILE __KOS_FIXED_CONST *__restrict stream);
/* >> ferror(3)
 * Check if an I/O error occurred in `stream' */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_ferror)(FILE __KOS_FIXED_CONST *__restrict stream);
/* >> tmpfile(3), tmpfile64(3)
 * Create and return a new file-stream for accessing a temporary file for reading/writing */
INTDEF WUNUSED FILE *NOTHROW_RPC(LIBCCALL libc_tmpfile)(void);
/* >> fopen(3), fopen64(3)
 * Create and return a new file-stream for accessing `filename' */
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_RPC(LIBCCALL libc_fopen)(char const *__restrict filename, char const *__restrict modes);
/* >> freopen(3), freopen64(3)
 * Re-open the given `stream' as a file-stream for accessing `filename' */
INTDEF NONNULL((1, 2, 3)) FILE *NOTHROW_RPC(LIBCCALL libc_freopen)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* >> fgetpos(3), fgetpos64(3)
 * Initialize an opaque descriptor `pos' for the current in-file position of `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fgetpos)(FILE *__restrict stream, fpos_t *__restrict pos) THROWS(...);
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fsetpos)(FILE *__restrict stream, fpos_t const *__restrict pos) THROWS(...);
/* >> renameat(2) */
INTDEF NONNULL((2, 4)) int NOTHROW_RPC(LIBCCALL libc_renameat)(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path);
/* >> removeat(3)
 * Remove a file or directory `filename' relative to a given base directory `dirfd' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_removeat)(fd_t dirfd, char const *filename);
/* >> frenameat(2)
 * @param flags: Set of `0 | AT_DOSPATH' */
INTDEF NONNULL((2, 4)) int NOTHROW_RPC(LIBCCALL libc_frenameat)(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path, atflag_t flags);
/* >> tmpnam_r(3) */
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_tmpnam_r)(char *buf);
/* >> fflush_unlocked(3)
 * Same as `fflush()', but performs I/O without acquiring a lock to `stream' */
INTDEF int (LIBCCALL libc_fflush_unlocked)(FILE *stream) THROWS(...);
/* >> fread_unlocked(3)
 * Same as `fread()', but performs I/O without acquiring a lock to `stream' */
INTDEF WUNUSED NONNULL((1, 4)) size_t (LIBCCALL libc_fread_unlocked)(void *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
/* >> fwrite_unlocked(3)
 * Same as `fwrite()', but performs I/O without acquiring a lock to `stream' */
INTDEF WUNUSED NONNULL((1, 4)) size_t (LIBCCALL libc_fwrite_unlocked)(void const *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fgetc_unlocked)(FILE *__restrict stream) THROWS(...);
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
INTDEF NONNULL((2)) int (LIBCCALL libc_fputc_unlocked)(int ch, FILE *__restrict stream) THROWS(...);
/* >> tempnam(3) */
INTDEF ATTR_MALLOC WUNUSED char *NOTHROW_NCX(LIBCCALL libc_tempnam)(char const *dir, char const *pfx);
/* >> fdopen(3)
 * Open a new file stream by inheriting a given file descriptor `fd'
 * Note that upon success (`return != NULL'), the given `fd'
 * will be `close()'d once `fclose(return)' is called */
INTDEF WUNUSED NONNULL((2)) FILE *NOTHROW_NCX(LIBCCALL libc_fdopen)(fd_t fd, char const *__restrict modes);
/* >> fileno(3)
 * Return the underlying file descriptor number used by `stream' */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_NCX(LIBCCALL libc_fileno)(FILE *__restrict stream);
/* >> fmemopen(3) */
INTDEF WUNUSED NONNULL((1, 3)) FILE *NOTHROW_NCX(LIBCCALL libc_fmemopen)(void *mem, size_t len, char const *modes);
/* >> open_memstream(3) */
INTDEF WUNUSED FILE *NOTHROW_NCX(LIBCCALL libc_open_memstream)(char **bufloc, size_t *sizeloc);
/* >> flockfile(3)
 * Acquire a lock to `stream' and block until doing so succeeds */
INTDEF NONNULL((1)) void NOTHROW_RPC(LIBCCALL libc_flockfile)(FILE *__restrict stream);
/* >> funlockfile(3)
 * Release a previously acquired lock from `stream' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_funlockfile)(FILE *__restrict stream);
/* >> ftrylockfile(3)
 * Try to acquire a lock to `stream' */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_ftrylockfile)(FILE *__restrict stream);
/* >> popen(3)
 * Open and return a new process I/O stream for executing `COMMAND' */
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_RPC(LIBCCALL libc_popen)(char const *command, char const *modes);
/* >> pclose(3)
 * Close a process I/O file `stream' (s.a. `popen(3)') */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_pclose)(FILE *stream);
/* >> fcloseall(3)
 * Close all opened files */
INTDEF int (LIBCCALL libc_fcloseall)(void) THROWS(...);
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_obstack_vprintf)(struct obstack *__restrict obstack_, char const *__restrict format, va_list args);
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fseeko)(FILE *__restrict stream, off_t off, int whence) THROWS(...);
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
INTDEF WUNUSED NONNULL((1)) off_t (LIBCCALL libc_ftello)(FILE *__restrict stream) THROWS(...);
/* >> tmpfile(3), tmpfile64(3)
 * Create and return a new file-stream for accessing a temporary file for reading/writing */
INTDEF WUNUSED FILE *NOTHROW_RPC(LIBCCALL libc_tmpfile64)(void);
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fseeko64)(FILE *__restrict stream, off64_t off, int whence) THROWS(...);
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
INTDEF WUNUSED NONNULL((1)) off64_t (LIBCCALL libc_ftello64)(FILE *__restrict stream) THROWS(...);
/* >> fopen(3), fopen64(3)
 * Create and return a new file-stream for accessing `filename' */
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_RPC(LIBCCALL libc_fopen64)(char const *__restrict filename, char const *__restrict modes);
/* >> freopen(3), freopen64(3)
 * Re-open the given `stream' as a file-stream for accessing `filename' */
INTDEF NONNULL((1, 2, 3)) FILE *NOTHROW_RPC(LIBCCALL libc_freopen64)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* >> fgetpos(3), fgetpos64(3)
 * Initialize an opaque descriptor `pos' for the current in-file position of `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fgetpos64)(FILE *__restrict stream, fpos64_t *__restrict pos) THROWS(...);
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fsetpos64)(FILE *__restrict stream, fpos64_t const *__restrict pos) THROWS(...);
/* >> file_printer(3)
 * For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
INTDEF NONNULL((1, 2)) ssize_t (__FORMATPRINTER_CC libc_file_printer)(void *arg, char const *__restrict data, size_t datalen) THROWS(...);
/* >> file_printer_unlocked(3)
 * Same as `file_printer()', but performs I/O without acquiring a lock to `(FILE *)arg' */
INTDEF NONNULL((1, 2)) ssize_t (__FORMATPRINTER_CC libc_file_printer_unlocked)(void *arg, char const *__restrict data, size_t datalen) THROWS(...);
/* >> fdreopen(3)
 * Re-open the given `stream' as a file-stream for accessing `fd' */
INTDEF NONNULL((2, 3)) FILE *NOTHROW_RPC(LIBCCALL libc_fdreopen)(fd_t fd, char const *__restrict modes, FILE *__restrict stream);
/* >> fdreopen(3)
 * Re-open the given `stream' as a file-stream for accessing `fd' */
INTDEF NONNULL((2, 3)) FILE *NOTHROW_RPC(LIBCCALL libc_fdreopen_unlocked)(fd_t fd, char const *__restrict modes, FILE *__restrict stream);
/* >> freopen(3), freopen64(3)
 * Re-open the given `stream' as a file-stream for accessing `filename' */
INTDEF NONNULL((1, 2, 3)) FILE *NOTHROW_RPC(LIBCCALL libc_freopen_unlocked)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* >> freopen(3), freopen64(3)
 * Re-open the given `stream' as a file-stream for accessing `filename' */
INTDEF NONNULL((1, 2, 3)) FILE *NOTHROW_RPC(LIBCCALL libc_freopen64_unlocked)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
INTDEF NONNULL((1)) int (LIBCCALL libc_fseek_unlocked)(FILE *__restrict stream, long int off, int whence) THROWS(...);
INTDEF WUNUSED NONNULL((1)) long int (LIBCCALL libc_ftell_unlocked)(FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1)) int (LIBCCALL libc_fseeko_unlocked)(FILE *__restrict stream, off_t off, int whence) THROWS(...);
INTDEF WUNUSED NONNULL((1)) off_t (LIBCCALL libc_ftello_unlocked)(FILE *__restrict stream) THROWS(...);
INTDEF int (LIBCCALL libc_flushall_unlocked)(void) THROWS(...);
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fgetpos_unlocked)(FILE *__restrict stream, fpos_t *__restrict pos) THROWS(...);
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fsetpos_unlocked)(FILE *__restrict stream, fpos_t const *__restrict pos) THROWS(...);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_setvbuf_unlocked)(FILE *__restrict stream, char *__restrict buf, __STDC_INT_AS_UINT_T modes, size_t bufsize);
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_ungetc_unlocked)(int ch, FILE *__restrict stream);
INTDEF NONNULL((1)) void (LIBCCALL libc_rewind_unlocked)(FILE *__restrict stream) THROWS(...);
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_fisatty)(FILE *__restrict stream);
/* >> fftruncate(3)
 * Truncate the given file `stream' to a length of `length' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fftruncate)(FILE *__restrict stream, __PIO_OFFSET length) THROWS(...);
/* >> fftruncate_unlocked(3)
 * Same as `fftruncate()', but don't acquire a lock to the file */
INTDEF NONNULL((1)) int (LIBCCALL libc_fftruncate_unlocked)(FILE *__restrict stream, __PIO_OFFSET length) THROWS(...);
INTDEF NONNULL((1)) int (LIBCCALL libc_fseeko64_unlocked)(FILE *__restrict stream, off64_t off, int whence) THROWS(...);
INTDEF WUNUSED NONNULL((1)) off64_t (LIBCCALL libc_ftello64_unlocked)(FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fgetpos64_unlocked)(FILE *__restrict stream, fpos64_t *__restrict pos) THROWS(...);
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fsetpos64_unlocked)(FILE *__restrict stream, fpos64_t const *__restrict pos) THROWS(...);
/* >> fftruncate64(3)
 * Truncate the given file `stream' to a length of `length' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fftruncate64)(FILE *__restrict stream, __PIO_OFFSET64 length) THROWS(...);
/* >> fftruncate64_unlocked(3)
 * Truncate the given file `stream' to a length of `length' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fftruncate64_unlocked)(FILE *__restrict stream, __PIO_OFFSET64 length) THROWS(...);
/* >> fgetln(3) */
INTDEF WUNUSED NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_fgetln)(FILE *__restrict fp, size_t *__restrict lenp);
/* >> fmtcheck(3)
 * Check if `user_format' may be used as a drop-in replacement for `good_format'
 * in the context of a call to `printf(3)' (or `format_printf()'), such that all
 * contained format qualifiers reference the same (or compatible) underlying C
 * types, and in the same order.
 * If all of this is the case, simply re-return `user_format'. Otherwise (i.e.
 * when `user_format' isn't compatible with `good_format'), return `good_format'
 * instead. This function is meant to be used to validate user-provided printf
 * format strings before actually using them, after they've been read from lang
 * config files: `printf(fmtcheck(get_user_fmt(), "%s %s"), "Foo", "Bar");' */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) __ATTR_FORMAT_ARG(2) char const *NOTHROW_NCX(LIBCCALL libc_fmtcheck)(char const *user_format, char const *good_format);
/* >> funopen2(3), funopen2_64(3) */
INTDEF WUNUSED FILE *NOTHROW_NCX(LIBCCALL libc_funopen2)(void const *cookie, __funopen2_readfn_t readfn, __funopen2_writefn_t writefn, __funopen2_seekfn_t seekfn, __funopen2_flushfn_t flushfn, __funopen2_closefn_t closefn);
/* >> funopen2(3), funopen2_64(3) */
INTDEF WUNUSED FILE *NOTHROW_NCX(LIBCCALL libc_funopen2_64)(void const *cookie, __funopen2_readfn_t readfn, __funopen2_writefn_t writefn, __funopen2_64_seekfn_t seekfn, __funopen2_flushfn_t flushfn, __funopen2_closefn_t closefn);
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
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_STDIO_H */
