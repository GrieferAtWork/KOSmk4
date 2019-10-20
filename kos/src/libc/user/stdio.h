/* HASH CRC-32:0x834f3aa8 */
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
#ifndef GUARD_LIBC_USER_STDIO_H
#define GUARD_LIBC_USER_STDIO_H 1

#include "../api.h"
#include "../auto/stdio.h"
#include <kos/anno.h>
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <stdio.h>

DECL_BEGIN

/* Remove a file or directory `FILENAME' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_remove)(char const *filename);
/* Rename a given file `OLDNAME' to `NEWNAME_OR_PATH', or in the event
 * that `NEWNAME_OR_PATH' refers to a directory, place the file within. */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_rename)(char const *oldname, char const *newname_or_path);
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_tmpnam)(char *buf);
/* Close and destroy a given file `STREAM' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fclose)(FILE *__restrict stream) __THROWS(...);
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
INTDEF int (LIBCCALL libc_fflush)(FILE *stream) __THROWS(...);
/* Alias for `setvbuf(STREAM, buf, _IOFBF, BUFSIZ)' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_setbuf)(FILE *__restrict stream, char *__restrict buf);
/* Set the buffer and buffer-mode to-be used by the given `STREAM'
 * @param modes: One of `_IOFBF', `_IOLBF' or `_IONBF' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_setvbuf)(FILE *__restrict stream, char *__restrict buf, int modes, size_t bufsize);
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fgetc)(FILE *__restrict stream) __THROWS(...);
/* Alias for `fgetc(stdin)' */
INTDEF int (LIBCCALL libc_getchar)(void) __THROWS(...);
/* Write a single character `CH' to `STREAM' */
INTDEF NONNULL((2)) int (LIBCCALL libc_fputc)(int ch, FILE *__restrict stream) __THROWS(...);
/* Alias for `fputc(CH, stdout)' */
INTDEF int (LIBCCALL libc_putchar)(int ch) __THROWS(...);
/* Read up to `BUFSIZE - 1' bytes of data from `STREAM', storing them into `BUF' stopped when
 * the buffer is full or a line-feed was read (in this case, the line-feed is also written to `BUF')
 * Afterwards, append a trailing NUL-character and re-return `BUF', or return `NULL' if an error occurred. */
INTDEF WUNUSED NONNULL((1, 3)) char *(LIBCCALL libc_fgets)(char *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) __THROWS(...);
/* Print a given string `STR' to `STREAM'. This is identical to:
 * >> fwrite(str, sizeof(char), strlen(str), stream); */
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_fputs)(char const *__restrict str, FILE *__restrict stream) __THROWS(...);
/* Print a given string `STR', followed by a line-feed to `STDOUT' */
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_puts)(char const *__restrict string) __THROWS(...);
/* Unget a single character byte of data previously returned by `getc()' */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_ungetc)(int ch, FILE *__restrict stream);
/* Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF' */
INTDEF WUNUSED NONNULL((1, 4)) size_t (LIBCCALL libc_fread)(void *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) __THROWS(...);
/* Write up to `ELEMSIZE * ELEMCOUNT' bytes of data from `BUF' into `STREAM' */
INTDEF NONNULL((1, 4)) size_t (LIBCCALL libc_fwrite)(void const *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) __THROWS(...);
/* Change the current in-file position of `STREAM' as a byte-offet from the start of the file */
INTDEF NONNULL((1)) int (LIBCCALL libc_fseek)(FILE *__restrict stream, long int off, int whence) __THROWS(...);
/* Return the current in-file position of `STREAM' as a byte-offet from the start of the file */
INTDEF WUNUSED NONNULL((1)) long int (LIBCCALL libc_ftell)(FILE *__restrict stream) __THROWS(...);
/* Rewind the current in-file position of `STREAM' to its starting position */
INTDEF NONNULL((1)) void (LIBCCALL libc_rewind)(FILE *__restrict stream) __THROWS(...);
/* Clear the error state of `STREAM', returning the stream to normal operations mode */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_clearerr)(FILE *__restrict stream);
/* Check if end-of-file has been reached in `STREAM' */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_feof)(FILE *__restrict stream);
/* Check if an I/O error occurred in `STREAM' */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_ferror)(FILE *__restrict stream);
/* Print a given `MESSAGE' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
INTDEF void NOTHROW_RPC(LIBCCALL libc_perror)(char const *message);
/* Create and return a new file-stream for accessing a temporary file for reading/writing */
INTDEF WUNUSED FILE *NOTHROW_RPC(LIBCCALL libc_tmpfile)(void);
/* Create and return a new file-stream for accessing `FILENAME' */
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_RPC(LIBCCALL libc_fopen)(char const *__restrict filename, char const *__restrict modes);
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
INTDEF NONNULL((1, 2, 3)) FILE *NOTHROW_RPC(LIBCCALL libc_freopen)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fgetpos)(FILE *__restrict stream, fpos_t *__restrict pos) __THROWS(...);
/* Set the file position of `STREAM' to `POS', as previously initialized with a call to `fgetpos()' */
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fsetpos)(FILE *__restrict stream, fpos_t const *__restrict pos) __THROWS(...);
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_vfprintf)(FILE *__restrict stream, char const *__restrict format, va_list args) __THROWS(...);
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (VLIBCCALL libc_fprintf)(FILE *__restrict stream, char const *__restrict format, ...) __THROWS(...);
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_vprintf)(char const *__restrict format, va_list args) __THROWS(...);
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T (VLIBCCALL libc_printf)(char const *__restrict format, ...) __THROWS(...);
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF ATTR_LIBC_SCANF(2, 0) WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc_vfscanf)(FILE *__restrict stream, char const *__restrict format, va_list args) __THROWS(...);
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF ATTR_LIBC_SCANF(1, 0) WUNUSED NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBCCALL libc_vscanf)(char const *__restrict format, va_list args) __THROWS(...);
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF ATTR_LIBC_SCANF(2, 3) WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc_fscanf)(FILE *__restrict stream, char const *__restrict format, ...) __THROWS(...);
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF ATTR_LIBC_SCANF(1, 2) WUNUSED NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc_scanf)(char const *__restrict format, ...) __THROWS(...);
INTDEF WUNUSED ATTR_DEPRECATED("No buffer size checks (use `fgets' instead)") NONNULL((1)) char *(LIBCCALL libc_gets)(char *__restrict buf) __THROWS(...);
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBCCALL libc_vdprintf)(fd_t fd, char const *__restrict format, va_list args);
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(VLIBCCALL libc_dprintf)(fd_t fd, char const *__restrict format, ...);
INTDEF NONNULL((2, 4)) int NOTHROW_RPC(LIBCCALL libc_renameat)(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path);
/* Remove a file or directory `FILENAME' relative to a given base directory `DIRFD' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_removeat)(fd_t dirfd, char const *filename);
/* @param flags: Set of `0|AT_DOSPATH' */
INTDEF NONNULL((2, 4)) int NOTHROW_RPC(LIBCCALL libc_frenameat)(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path, atflag_t flags);
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_tmpnam_r)(char *buf);
/* Specify the location and size for the buffer to-be used by `STREAM' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_setbuffer)(FILE *__restrict stream, char *buf, size_t bufsize);
/* Change the given `STREAM' to become line-buffered */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_setlinebuf)(FILE *__restrict stream);
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
INTDEF int (LIBCCALL libc_fflush_unlocked)(FILE *stream) __THROWS(...);
/* Same as `fread()', but performs I/O without acquiring a lock to `STREAM' */
INTDEF WUNUSED NONNULL((1, 4)) size_t (LIBCCALL libc_fread_unlocked)(void *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) __THROWS(...);
/* Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM' */
INTDEF NONNULL((1, 4)) size_t (LIBCCALL libc_fwrite_unlocked)(void const *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) __THROWS(...);
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fgetc_unlocked)(FILE *__restrict stream) __THROWS(...);
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
INTDEF NONNULL((2)) int (LIBCCALL libc_fputc_unlocked)(int ch, FILE *__restrict stream) __THROWS(...);
INTDEF ATTR_MALLOC WUNUSED char *NOTHROW_NCX(LIBCCALL libc_tempnam)(char const *dir, char const *pfx);
/* Open a new file stream by inheriting a given file descriptor `FD'
 * Note that upon success (`return != NULL'), the given `FD' will be `close()'d once `fclose(return)' is called */
INTDEF WUNUSED NONNULL((2)) FILE *NOTHROW_NCX(LIBCCALL libc_fdopen)(fd_t fd, char const *__restrict modes);
/* Return the underlying file descriptor number used by `STREAM' */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_NCX(LIBCCALL libc_fileno)(FILE *__restrict stream);
INTDEF WUNUSED NONNULL((1, 3)) FILE *NOTHROW_NCX(LIBCCALL libc_fmemopen)(void *mem, size_t len, char const *modes);
INTDEF WUNUSED FILE *NOTHROW_NCX(LIBCCALL libc_open_memstream)(char **bufloc, size_t *sizeloc);
INTDEF WUNUSED NONNULL((1, 2, 4)) ssize_t (LIBCCALL libc_getdelim)(char **__restrict lineptr, size_t *__restrict pcount, int delimiter, FILE *__restrict stream) __THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 3)) ssize_t (LIBCCALL libc_getline)(char **__restrict lineptr, size_t *__restrict pcount, FILE *__restrict stream) __THROWS(...);
/* Same as `getchar()', but performs I/O without acquiring a lock to `stdin' */
INTDEF int (LIBCCALL libc_getchar_unlocked)(void) __THROWS(...);
/* Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
INTDEF int (LIBCCALL libc_putchar_unlocked)(int ch) __THROWS(...);
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
/* Similar to `getc()', but read 2 bytes */
INTDEF NONNULL((1)) int (LIBCCALL libc_getw)(FILE *__restrict stream) __THROWS(...);
/* Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
INTDEF NONNULL((2)) int (LIBCCALL libc_putw)(int w, FILE *__restrict stream) __THROWS(...);
/* Alias for `_fcloseall()' */
INTDEF int (LIBCCALL libc_fcloseall)(void) __THROWS(...);
INTDEF WUNUSED NONNULL((2)) FILE *NOTHROW_NCX(LIBCCALL libc_fopencookie)(void *__restrict magic_cookie, char const *__restrict modes, cookie_io_functions_t io_funcs);
/* Same as `fgets()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTDEF WUNUSED NONNULL((1, 3)) char *(LIBCCALL libc_fgets_unlocked)(char *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) __THROWS(...);
/* Same as `fputs()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc_fputs_unlocked)(char const *__restrict string, FILE *__restrict stream) __THROWS(...);
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_obstack_vprintf)(struct obstack *__restrict obstack_, char const *__restrict format, va_list args);
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(VLIBCCALL libc_obstack_printf)(struct obstack *__restrict obstack_, char const *__restrict format, ...);
/* Change the current in-file position of `STREAM' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fseeko)(FILE *__restrict stream, off_t off, int whence) __THROWS(...);
/* Return the current in-file position of `STREAM' */
INTDEF WUNUSED NONNULL((1)) off_t (LIBCCALL libc_ftello)(FILE *__restrict stream) __THROWS(...);
/* 64-bit variant of `tmpfile' */
INTDEF WUNUSED FILE *NOTHROW_RPC(LIBCCALL libc_tmpfile64)(void);
/* 64-bit variant of `fseeko' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fseeko64)(FILE *__restrict stream, off64_t off, int whence) __THROWS(...);
/* 64-bit variant of `ftello' */
INTDEF WUNUSED NONNULL((1)) off64_t (LIBCCALL libc_ftello64)(FILE *__restrict stream) __THROWS(...);
/* 64-bit variant of `fopen' */
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_RPC(LIBCCALL libc_fopen64)(char const *__restrict filename, char const *__restrict modes);
/* 64-bit variant of `freopen' */
INTDEF NONNULL((1, 2, 3)) FILE *NOTHROW_RPC(LIBCCALL libc_freopen64)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* 64-bit variant of `fgetpos' */
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fgetpos64)(FILE *__restrict stream, fpos64_t *__restrict pos) __THROWS(...);
/* 64-bit variant of `fsetpos' */
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fsetpos64)(FILE *__restrict stream, fpos64_t const *__restrict pos) __THROWS(...);
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
INTDEF NONNULL((1, 2)) ssize_t (LIBCCALL libc_file_printer)(void *arg, char const *__restrict data, size_t datalen) __THROWS(...);
/* Same as `file_printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTDEF NONNULL((1, 2)) ssize_t (LIBCCALL libc_file_printer_unlocked)(void *arg, char const *__restrict data, size_t datalen) __THROWS(...);
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
INTDEF ATTR_LIBC_PRINTF(2, 3) WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc_vasprintf)(char **__restrict pstr, char const *__restrict format, va_list args);
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
INTDEF ATTR_LIBC_PRINTF(2, 3) WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc_asprintf)(char **__restrict pstr, char const *__restrict format, ...);
/* Re-open the given `STREAM' as a file-stream for accessing `FD' */
INTDEF NONNULL((2, 3)) FILE *NOTHROW_RPC(LIBCCALL libc_fdreopen)(fd_t fd, char const *__restrict modes, FILE *__restrict stream);
/* Re-open the given `STREAM' as a file-stream for accessing `FD' */
INTDEF NONNULL((2, 3)) FILE *NOTHROW_RPC(LIBCCALL libc_fdreopen_unlocked)(fd_t fd, char const *__restrict modes, FILE *__restrict stream);
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
INTDEF NONNULL((1, 2, 3)) FILE *NOTHROW_RPC(LIBCCALL libc_freopen_unlocked)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
INTDEF NONNULL((1, 2, 3)) FILE *NOTHROW_RPC(LIBCCALL libc_freopen64_unlocked)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* Change the current in-file position of `STREAM' as a byte-offet from the start of the file */
INTDEF NONNULL((1)) int (LIBCCALL libc_fseek_unlocked)(FILE *__restrict stream, long int off, int whence) __THROWS(...);
/* Change the current in-file position of `STREAM' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fseeko_unlocked)(FILE *__restrict stream, off_t off, int whence) __THROWS(...);
/* Return the current in-file position of `STREAM' as a byte-offet from the start of the file */
INTDEF NONNULL((1)) long int (LIBCCALL libc_ftell_unlocked)(FILE *__restrict stream) __THROWS(...);
/* Return the current in-file position of `STREAM' */
INTDEF NONNULL((1)) off_t (LIBCCALL libc_ftello_unlocked)(FILE *__restrict stream) __THROWS(...);
INTDEF int (LIBCCALL libc_flushall_unlocked)(void) __THROWS(...);
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fgetpos_unlocked)(FILE *__restrict stream, fpos_t *__restrict pos) __THROWS(...);
/* Set the file position of `STREAM' to `POS', as previously initialized with a call to `fgetpos()' */
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fsetpos_unlocked)(FILE *__restrict stream, fpos_t const *__restrict pos) __THROWS(...);
/* Similar to `getc()', but read 2 bytes */
INTDEF NONNULL((1)) int (LIBCCALL libc_getw_unlocked)(FILE *__restrict stream) __THROWS(...);
/* Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
INTDEF NONNULL((2)) int (LIBCCALL libc_putw_unlocked)(int w, FILE *__restrict stream) __THROWS(...);
/* Set the buffer and buffer-mode to-be used by the given `STREAM'
 * @param modes: One of `_IOFBF', `_IOLBF' or `_IONBF' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_setvbuf_unlocked)(FILE *__restrict stream, char *__restrict buf, int modes, size_t bufsize);
/* Unget a single character byte of data previously returned by `getc()' */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_ungetc_unlocked)(int ch, FILE *__restrict stream);
INTDEF WUNUSED NONNULL((1, 2, 4)) ssize_t (LIBCCALL libc_getdelim_unlocked)(char **__restrict lineptr, size_t *__restrict pcount, int delimiter, FILE *__restrict stream) __THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 3)) ssize_t (LIBCCALL libc_getline_unlocked)(char **__restrict lineptr, size_t *__restrict pcount, FILE *__restrict stream) __THROWS(...);
/* Rewind the current in-file position of `STREAM' to its starting position */
INTDEF NONNULL((1)) void (LIBCCALL libc_rewind_unlocked)(FILE *__restrict stream) __THROWS(...);
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_fisatty)(FILE *__restrict stream);
/* >> fftruncate(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fftruncate)(FILE *__restrict stream, __PIO_OFFSET length) __THROWS(...);
/* >> fftruncate_unlocked(3)
 * Same as `fftruncate()', but don't acquire a lock to the file */
INTDEF NONNULL((1)) int (LIBCCALL libc_fftruncate_unlocked)(FILE *__restrict stream, __PIO_OFFSET length) __THROWS(...);
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_puts_unlocked)(char const *__restrict string) __THROWS(...);
/* 64-bit variant of `fseeko' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fseeko64_unlocked)(FILE *__restrict stream, off64_t off, int whence) __THROWS(...);
/* 64-bit variant of `ftello' */
INTDEF WUNUSED NONNULL((1)) off64_t (LIBCCALL libc_ftello64_unlocked)(FILE *__restrict stream) __THROWS(...);
/* 64-bit variant of `fgetpos' */
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fgetpos64_unlocked)(FILE *__restrict stream, fpos64_t *__restrict pos) __THROWS(...);
/* 64-bit variant of `fsetpos' */
INTDEF NONNULL((1, 2)) int (LIBCCALL libc_fsetpos64_unlocked)(FILE *__restrict stream, fpos64_t const *__restrict pos) __THROWS(...);
/* >> fftruncate64(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fftruncate64)(FILE *__restrict stream, __PIO_OFFSET64 length) __THROWS(...);
/* >> fftruncate64_unlocked(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
INTDEF NONNULL((1)) int (LIBCCALL libc_fftruncate64_unlocked)(FILE *__restrict stream, __PIO_OFFSET64 length) __THROWS(...);
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_vfprintf_unlocked)(FILE *__restrict stream, char const *__restrict format, va_list args) __THROWS(...);
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (VLIBCCALL libc_fprintf_unlocked)(FILE *__restrict stream, char const *__restrict format, ...) __THROWS(...);
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_vprintf_unlocked)(char const *__restrict format, va_list args) __THROWS(...);
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T (VLIBCCALL libc_printf_unlocked)(char const *__restrict format, ...) __THROWS(...);
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF ATTR_LIBC_SCANF(2, 0) WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc_vfscanf_unlocked)(FILE *__restrict stream, char const *__restrict format, va_list args) __THROWS(...);
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF ATTR_LIBC_SCANF(1, 0) WUNUSED NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBCCALL libc_vscanf_unlocked)(char const *__restrict format, va_list args) __THROWS(...);
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF ATTR_LIBC_SCANF(2, 3) WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc_fscanf_unlocked)(FILE *__restrict stream, char const *__restrict format, ...) __THROWS(...);
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF ATTR_LIBC_SCANF(1, 2) WUNUSED NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc_scanf_unlocked)(char const *__restrict format, ...) __THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_RPC(LIBCCALL libc__fsopen)(char const *filename, char const *modes, int sflag);
INTDEF int NOTHROW_RPC(LIBCCALL libc__rmtmp)(void);
INTDEF NONNULL((1)) int (LIBCCALL libc__filbuf)(FILE *__restrict stream) __THROWS(...);
INTDEF NONNULL((2)) int (LIBCCALL libc__flsbuf)(int ch, FILE *__restrict stream) __THROWS(...);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__getmaxstdio)(void);
INTDEF int NOTHROW_NCX(LIBCCALL libc__setmaxstdio)(int val);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__get_printf_count_output)(void);
INTDEF int NOTHROW_NCX(LIBCCALL libc__set_printf_count_output)(int val);
INTDEF WUNUSED uint32_t NOTHROW_NCX(LIBCCALL libc__get_output_format)(void);
INTDEF uint32_t NOTHROW_NCX(LIBCCALL libc__set_output_format)(uint32_t format);
INTDEF ATTR_LIBC_SCANF(1, 3) WUNUSED NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vscanf_l)(char const *__restrict format, locale_t locale, va_list args) __THROWS(...);
INTDEF ATTR_LIBC_SCANF(2, 4) WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vfscanf_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, va_list args) __THROWS(...);
INTDEF ATTR_LIBC_SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__scanf_l)(char const *__restrict format, locale_t locale, ...) __THROWS(...);
INTDEF ATTR_LIBC_SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__fscanf_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, ...) __THROWS(...);
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vprintf_l)(char const *__restrict format, locale_t locale, va_list args) __THROWS(...);
INTDEF ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vprintf_p)(char const *__restrict format, va_list args) __THROWS(...);
INTDEF ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vprintf_p_l)(char const *__restrict format, locale_t locale, va_list args) __THROWS(...);
INTDEF ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__printf_l)(char const *__restrict format, locale_t locale, ...) __THROWS(...);
INTDEF ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__printf_s_l)(char const *__restrict format, locale_t locale, ...) __THROWS(...);
INTDEF ATTR_LIBC_PRINTF_P(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__printf_p)(char const *__restrict format, ...) __THROWS(...);
INTDEF ATTR_LIBC_PRINTF_P(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__printf_p_l)(char const *__restrict format, locale_t locale, ...) __THROWS(...);
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vfprintf_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, va_list args) __THROWS(...);
INTDEF ATTR_LIBC_PRINTF_P(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vfprintf_p)(FILE *__restrict stream, char const *__restrict format, va_list args) __THROWS(...);
INTDEF ATTR_LIBC_PRINTF_P(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vfprintf_p_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, va_list args) __THROWS(...);
INTDEF ATTR_LIBC_PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__fprintf_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, ...) __THROWS(...);
INTDEF ATTR_LIBC_PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__fprintf_s_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, ...) __THROWS(...);
INTDEF ATTR_LIBC_PRINTF_P(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__fprintf_p)(FILE *__restrict stream, char const *__restrict format, ...) __THROWS(...);
INTDEF ATTR_LIBC_PRINTF_P(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__fprintf_p_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, ...) __THROWS(...);
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_RPC(LIBCCALL libc_fopen_s)(FILE **pstream, char const *filename, char const *modes);
INTDEF NONNULL((1, 2, 3, 4)) errno_t NOTHROW_RPC(LIBCCALL libc_freopen_s)(FILE **pstream, char const *filename, char const *modes, FILE *oldstream);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_tmpnam_s)(char *__restrict buf, rsize_t bufsize);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_clearerr_s)(FILE *__restrict stream);
INTDEF NONNULL((1)) errno_t NOTHROW_RPC(LIBCCALL libc_tmpfile_s)(FILE **pstream);
INTDEF WUNUSED NONNULL((1, 5)) size_t NOTHROW_RPC(LIBCCALL libc_fread_s)(void *__restrict buf, size_t bufsize, size_t elemsize, size_t elemcount, FILE *__restrict stream);
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_RPC(LIBCCALL libc_gets_s)(char *__restrict buf, rsize_t bufsize);
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc_fscanf_s)(FILE *__restrict stream, char const *__restrict format, ...) __THROWS(...);
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc_vfscanf_s)(FILE *__restrict stream, char const *__restrict format, va_list args) __THROWS(...);
INTDEF ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc_scanf_s)(char const *__restrict format, ...) __THROWS(...);
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBCCALL libc_vscanf_s)(char const *__restrict format, va_list args) __THROWS(...);
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc_sscanf_s)(char const *__restrict input, char const *__restrict format, ...);
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_vsscanf_s)(char const *__restrict input, char const *__restrict format, va_list args);
INTDEF ATTR_LIBC_PRINTF(4, 0) NONNULL((4)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_vsnprintf_s)(char *__restrict buf, size_t bufsize, size_t buflen, char const *__restrict format, va_list args);
INTDEF ATTR_COLD void (LIBCCALL libc__wperror)(char32_t const *__restrict message) __THROWS(...);
INTDEF ATTR_COLD void (LIBDCALL libd__wperror)(char16_t const *__restrict message) __THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t (LIBCCALL libc__fread_nolock_s)(void *__restrict buf, size_t bufsize, size_t elemsize, size_t elemcount, FILE *__restrict stream) __THROWS(...);

DECL_END

#endif /* !GUARD_LIBC_USER_STDIO_H */
