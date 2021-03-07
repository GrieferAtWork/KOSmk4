/* HASH CRC-32:0xc6334279 */
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
#ifndef GUARD_LIBC_AUTO_STDIO_H
#define GUARD_LIBC_AUTO_STDIO_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <stdio.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Remove a file or directory `FILENAME' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_remove)(char const *filename);
/* Rename a given file `OLDNAME' to `NEWNAME_OR_PATH', or in the event
 * that `NEWNAME_OR_PATH' refers to a directory, place the file within. */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_rename)(char const *oldname, char const *newname_or_path);
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_tmpnam)(char *buf);
/* Close and destroy a given file `STREAM' */
INTDEF NONNULL((1)) int (LIBDCALL libd_fclose)(FILE *__restrict stream) THROWS(...);
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
INTDEF int (LIBDCALL libd_fflush)(FILE *stream) THROWS(...);
/* Alias for `setvbuf(STREAM, buf, _IOFBF, BUFSIZ)' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd_setbuf)(FILE *__restrict stream, char *buf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Alias for `setvbuf(STREAM, buf, _IOFBF, BUFSIZ)' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_setbuf)(FILE *__restrict stream, char *buf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Set the buffer and buffer-mode to-be used by the given `STREAM'
 * @param modes: One of `_IOFBF', `_IOLBF' or `_IONBF' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_setvbuf)(FILE *__restrict stream, char *__restrict buf, __STDC_INT_AS_UINT_T modes, size_t bufsize);
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
INTDEF NONNULL((1)) int (LIBDCALL libd_fgetc)(FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Alias for `fgetc(stdin)' */
INTDEF int (LIBCCALL libc_getchar)(void) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Write a single character `CH' to `STREAM' */
INTDEF NONNULL((2)) int (LIBDCALL libd_fputc)(int ch, FILE *__restrict stream) THROWS(...);
/* Alias for `fputc(CH, stdout)' */
INTDEF int (LIBDCALL libd_putchar)(int ch) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Alias for `fputc(CH, stdout)' */
INTDEF int (LIBCCALL libc_putchar)(int ch) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Read up to `BUFSIZE - 1' bytes of data from `STREAM', storing them into `BUF' stopped when
 * the buffer is full or a line-feed was read (in this case, the line-feed is also written to `BUF')
 * Afterwards, append a trailing NUL-character and re-return `BUF', or return `NULL' if an error occurred. */
INTDEF WUNUSED NONNULL((1, 3)) char *(LIBDCALL libd_fgets)(char *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Read up to `BUFSIZE - 1' bytes of data from `STREAM', storing them into `BUF' stopped when
 * the buffer is full or a line-feed was read (in this case, the line-feed is also written to `BUF')
 * Afterwards, append a trailing NUL-character and re-return `BUF', or return `NULL' if an error occurred. */
INTDEF WUNUSED NONNULL((1, 3)) char *(LIBCCALL libc_fgets)(char *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Print a given string `STR' to `STREAM'. This is identical to:
 * >> fwrite(str, sizeof(char), strlen(str), stream); */
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd_fputs)(char const *__restrict str, FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Print a given string `STR' to `STREAM'. This is identical to:
 * >> fwrite(str, sizeof(char), strlen(str), stream); */
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_fputs)(char const *__restrict str, FILE *__restrict stream) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Print a given string `STR', followed by a line-feed to `STDOUT' */
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd_puts)(char const *__restrict string) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Print a given string `STR', followed by a line-feed to `STDOUT' */
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_puts)(char const *__restrict string) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Unget a single character byte of data previously returned by `getc()' */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBDCALL libd_ungetc)(int ch, FILE *__restrict stream);
/* Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF' */
INTDEF WUNUSED NONNULL((1, 4)) size_t (LIBDCALL libd_fread)(void *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
/* Write up to `ELEMSIZE * ELEMCOUNT' bytes of data from `BUF' into `STREAM' */
INTDEF NONNULL((1, 4)) size_t (LIBDCALL libd_fwrite)(void const *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
/* Change the current in-file position of `STREAM' as a byte-offet from the start of the file */
INTDEF NONNULL((1)) int (LIBDCALL libd_fseek)(FILE *__restrict stream, long int off, int whence) THROWS(...);
/* Return the current in-file position of `STREAM' as a byte-offet from the start of the file */
INTDEF WUNUSED NONNULL((1)) long int (LIBDCALL libd_ftell)(FILE *__restrict stream) THROWS(...);
/* Rewind the current in-file position of `STREAM' to its starting position */
INTDEF NONNULL((1)) void (LIBDCALL libd_rewind)(FILE *__restrict stream) THROWS(...);
/* Clear the error state of `STREAM', returning the stream to normal operations mode */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd_clearerr)(FILE *__restrict stream);
/* Check if end-of-file has been reached in `STREAM' */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_feof)(FILE __KOS_FIXED_CONST *__restrict stream);
/* Check if an I/O error occurred in `STREAM' */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_ferror)(FILE __KOS_FIXED_CONST *__restrict stream);
/* Print a given `MESSAGE' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
INTDEF void NOTHROW_RPC(LIBDCALL libd_perror)(char const *message);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Print a given `MESSAGE' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
INTDEF void NOTHROW_RPC(LIBCCALL libc_perror)(char const *message);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Create and return a new file-stream for accessing `FILENAME' */
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_RPC(LIBDCALL libd_fopen)(char const *__restrict filename, char const *__restrict modes);
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
INTDEF NONNULL((1, 2, 3)) FILE *NOTHROW_RPC(LIBDCALL libd_freopen)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
INTDEF NONNULL((1, 2)) int (LIBDCALL libd_fgetpos)(FILE *__restrict stream, fpos_t *__restrict pos) THROWS(...);
/* Set the file position of `STREAM' to `POS', as previously initialized with a call to `fgetpos()' */
INTDEF NONNULL((1, 2)) int (LIBDCALL libd_fsetpos)(FILE *__restrict stream, fpos_t const *__restrict pos) THROWS(...);
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd_vfprintf)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_vfprintf)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (VLIBDCALL libd_fprintf)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (VLIBCCALL libc_fprintf)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd_vprintf)(char const *__restrict format, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_vprintf)(char const *__restrict format, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T (VLIBDCALL libd_printf)(char const *__restrict format, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T (VLIBCCALL libc_printf)(char const *__restrict format, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vfscanf)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc_vfscanf)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vscanf)(char const *__restrict format, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBCCALL libc_vscanf)(char const *__restrict format, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_fscanf)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc_fscanf)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_scanf)(char const *__restrict format, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc_scanf)(char const *__restrict format, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_DEPRECATED("No buffer size checks (use `fgets\' instead)") NONNULL((1)) char *(LIBDCALL libd_gets)(char *__restrict buf) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_DEPRECATED("No buffer size checks (use `fgets\' instead)") NONNULL((1)) char *(LIBCCALL libc_gets)(char *__restrict buf) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd_vsscanf)(char const *__restrict input, char const *__restrict format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_vsscanf)(char const *__restrict input, char const *__restrict format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd_sscanf)(char const *__restrict input, char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc_sscanf)(char const *__restrict input, char const *__restrict format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd_vsprintf)(char *__restrict dest, char const *__restrict format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc_vsprintf)(char *__restrict dest, char const *__restrict format, va_list args);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd_sprintf)(char *__restrict buf, char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc_sprintf)(char *__restrict buf, char const *__restrict format, ...);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
INTDEF ATTR_LIBC_PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd_vsnprintf)(char *__restrict buf, size_t buflen, char const *__restrict format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
INTDEF ATTR_LIBC_PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_vsnprintf)(char *__restrict buf, size_t buflen, char const *__restrict format, va_list args);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character),
 * and never write more than `BUFLEN' characters to `BUF' */
INTDEF ATTR_LIBC_PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd_snprintf)(char *__restrict buf, size_t buflen, char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character),
 * and never write more than `BUFLEN' characters to `BUF' */
INTDEF ATTR_LIBC_PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc_snprintf)(char *__restrict buf, size_t buflen, char const *__restrict format, ...);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBDCALL libd_vdprintf)(fd_t fd, char const *__restrict format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBCCALL libc_vdprintf)(fd_t fd, char const *__restrict format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(VLIBDCALL libd_dprintf)(fd_t fd, char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(VLIBCCALL libc_dprintf)(fd_t fd, char const *__restrict format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((2, 4)) int NOTHROW_RPC(LIBDCALL libd_renameat)(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path);
/* Remove a file or directory `FILENAME' relative to a given base directory `DIRFD' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBDCALL libd_removeat)(fd_t dirfd, char const *filename);
/* @param flags: Set of `0 | AT_DOSPATH' */
INTDEF NONNULL((2, 4)) int NOTHROW_RPC(LIBDCALL libd_frenameat)(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path, atflag_t flags);
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_tmpnam_r)(char *buf);
/* Specify the location and size for the buffer to-be used by `STREAM' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd_setbuffer)(FILE *__restrict stream, char *buf, size_t bufsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Specify the location and size for the buffer to-be used by `STREAM' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_setbuffer)(FILE *__restrict stream, char *buf, size_t bufsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Change the given `STREAM' to become line-buffered */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd_setlinebuf)(FILE *__restrict stream);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Change the given `STREAM' to become line-buffered */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_setlinebuf)(FILE *__restrict stream);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
INTDEF int (LIBDCALL libd_fflush_unlocked)(FILE *stream) THROWS(...);
/* Same as `fread()', but performs I/O without acquiring a lock to `STREAM' */
INTDEF WUNUSED NONNULL((1, 4)) size_t (LIBDCALL libd_fread_unlocked)(void *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
/* Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM' */
INTDEF WUNUSED NONNULL((1, 4)) size_t (LIBDCALL libd_fwrite_unlocked)(void const *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
INTDEF NONNULL((1)) int (LIBDCALL libd_fgetc_unlocked)(FILE *__restrict stream) THROWS(...);
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
INTDEF NONNULL((2)) int (LIBDCALL libd_fputc_unlocked)(int ch, FILE *__restrict stream) THROWS(...);
INTDEF ATTR_MALLOC WUNUSED char *NOTHROW_NCX(LIBDCALL libd_tempnam)(char const *dir, char const *pfx);
/* Open a new file stream by inheriting a given file descriptor `FD'
 * Note that upon success (`return != NULL'), the given `FD'
 * will be `close()'d once `fclose(return)' is called */
INTDEF WUNUSED NONNULL((2)) FILE *NOTHROW_NCX(LIBDCALL libd_fdopen)(fd_t fd, char const *__restrict modes);
/* Return the underlying file descriptor number used by `STREAM' */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_NCX(LIBDCALL libd_fileno)(FILE *__restrict stream);
INTDEF WUNUSED NONNULL((1, 3)) FILE *NOTHROW_NCX(LIBDCALL libd_fmemopen)(void *mem, size_t len, char const *modes);
INTDEF WUNUSED FILE *NOTHROW_NCX(LIBDCALL libd_open_memstream)(char **bufloc, size_t *sizeloc);
INTDEF WUNUSED NONNULL((1, 2, 4)) ssize_t (LIBDCALL libd_getdelim)(char **__restrict lineptr, size_t *__restrict pcount, int delimiter, FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((1, 2, 4)) ssize_t (LIBCCALL libc_getdelim)(char **__restrict lineptr, size_t *__restrict pcount, int delimiter, FILE *__restrict stream) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((1, 2, 3)) ssize_t (LIBDCALL libd_getline)(char **__restrict lineptr, size_t *__restrict pcount, FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((1, 2, 3)) ssize_t (LIBCCALL libc_getline)(char **__restrict lineptr, size_t *__restrict pcount, FILE *__restrict stream) THROWS(...);
/* Same as `getchar()', but performs I/O without acquiring a lock to `stdin' */
INTDEF int (LIBCCALL libc_getchar_unlocked)(void) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
INTDEF int (LIBDCALL libd_putchar_unlocked)(int ch) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
INTDEF int (LIBCCALL libc_putchar_unlocked)(int ch) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Acquire a lock to `STREAM' and block until doing so succeeds */
INTDEF NONNULL((1)) void NOTHROW_RPC(LIBDCALL libd_flockfile)(FILE *__restrict stream);
/* Release a previously acquired lock from `STREAM' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd_funlockfile)(FILE *__restrict stream);
/* Try to acquire a lock to `STREAM' */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_ftrylockfile)(FILE *__restrict stream);
/* Open and return a new process I/O stream for executing `COMMAND' */
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_RPC(LIBDCALL libd_popen)(char const *command, char const *modes);
/* Close a process I/O file `STREAM' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_pclose)(FILE *stream);
/* Similar to `getc()', but read 2 bytes */
INTDEF NONNULL((1)) int (LIBDCALL libd_getw)(FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Similar to `getc()', but read 2 bytes */
INTDEF NONNULL((1)) int (LIBCCALL libc_getw)(FILE *__restrict stream) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
INTDEF NONNULL((2)) int (LIBDCALL libd_putw)(int w, FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
INTDEF NONNULL((2)) int (LIBCCALL libc_putw)(int w, FILE *__restrict stream) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((2)) FILE *NOTHROW_NCX(LIBDCALL libd_fopencookie)(void *__restrict magic_cookie, char const *__restrict modes, cookie_io_functions_t io_funcs);
/* Same as `fgets()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTDEF WUNUSED NONNULL((1, 3)) char *(LIBDCALL libd_fgets_unlocked)(char *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `fgets()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTDEF WUNUSED NONNULL((1, 3)) char *(LIBCCALL libc_fgets_unlocked)(char *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `fputs()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_fputs_unlocked)(char const *__restrict string, FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `fputs()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc_fputs_unlocked)(char const *__restrict string, FILE *__restrict stream) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_obstack_vprintf)(struct obstack *__restrict obstack_, char const *__restrict format, va_list args);
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(VLIBDCALL libd_obstack_printf)(struct obstack *__restrict obstack_, char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(VLIBCCALL libc_obstack_printf)(struct obstack *__restrict obstack_, char const *__restrict format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Change the current in-file position of `STREAM' */
INTDEF NONNULL((1)) int (LIBDCALL libd_fseeko)(FILE *__restrict stream, off_t off, int whence) THROWS(...);
/* Return the current in-file position of `STREAM' */
INTDEF WUNUSED NONNULL((1)) off_t (LIBDCALL libd_ftello)(FILE *__restrict stream) THROWS(...);
/* 64-bit variant of `fseeko' */
INTDEF NONNULL((1)) int (LIBDCALL libd_fseeko64)(FILE *__restrict stream, off64_t off, int whence) THROWS(...);
/* 64-bit variant of `ftello' */
INTDEF WUNUSED NONNULL((1)) off64_t (LIBDCALL libd_ftello64)(FILE *__restrict stream) THROWS(...);
/* 64-bit variant of `fopen' */
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_RPC(LIBDCALL libd_fopen64)(char const *__restrict filename, char const *__restrict modes);
/* 64-bit variant of `freopen' */
INTDEF NONNULL((1, 2, 3)) FILE *NOTHROW_RPC(LIBDCALL libd_freopen64)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* 64-bit variant of `fgetpos' */
INTDEF NONNULL((1, 2)) int (LIBDCALL libd_fgetpos64)(FILE *__restrict stream, fpos64_t *__restrict pos) THROWS(...);
/* 64-bit variant of `fsetpos' */
INTDEF NONNULL((1, 2)) int (LIBDCALL libd_fsetpos64)(FILE *__restrict stream, fpos64_t const *__restrict pos) THROWS(...);
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd_vasprintf)(char **__restrict pstr, char const *__restrict format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc_vasprintf)(char **__restrict pstr, char const *__restrict format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd_asprintf)(char **__restrict pstr, char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc_asprintf)(char **__restrict pstr, char const *__restrict format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Re-open the given `STREAM' as a file-stream for accessing `FD' */
INTDEF NONNULL((2, 3)) FILE *NOTHROW_RPC(LIBDCALL libd_fdreopen)(fd_t fd, char const *__restrict modes, FILE *__restrict stream);
/* Re-open the given `STREAM' as a file-stream for accessing `FD' */
INTDEF NONNULL((2, 3)) FILE *NOTHROW_RPC(LIBDCALL libd_fdreopen_unlocked)(fd_t fd, char const *__restrict modes, FILE *__restrict stream);
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
INTDEF NONNULL((1, 2, 3)) FILE *NOTHROW_RPC(LIBDCALL libd_freopen_unlocked)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
INTDEF NONNULL((1, 2, 3)) FILE *NOTHROW_RPC(LIBDCALL libd_freopen64_unlocked)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
INTDEF NONNULL((1)) int (LIBDCALL libd_fseek_unlocked)(FILE *__restrict stream, long int off, int whence) THROWS(...);
INTDEF WUNUSED NONNULL((1)) long int (LIBDCALL libd_ftell_unlocked)(FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1)) int (LIBDCALL libd_fseeko_unlocked)(FILE *__restrict stream, off_t off, int whence) THROWS(...);
INTDEF WUNUSED NONNULL((1)) off_t (LIBDCALL libd_ftello_unlocked)(FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1, 2)) int (LIBDCALL libd_fgetpos_unlocked)(FILE *__restrict stream, fpos_t *__restrict pos) THROWS(...);
INTDEF NONNULL((1, 2)) int (LIBDCALL libd_fsetpos_unlocked)(FILE *__restrict stream, fpos_t const *__restrict pos) THROWS(...);
INTDEF NONNULL((1)) int (LIBDCALL libd_getw_unlocked)(FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) int (LIBCCALL libc_getw_unlocked)(FILE *__restrict stream) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((2)) int (LIBDCALL libd_putw_unlocked)(int w, FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((2)) int (LIBCCALL libc_putw_unlocked)(int w, FILE *__restrict stream) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_setvbuf_unlocked)(FILE *__restrict stream, char *__restrict buf, __STDC_INT_AS_UINT_T modes, size_t bufsize);
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBDCALL libd_ungetc_unlocked)(int ch, FILE *__restrict stream);
INTDEF WUNUSED NONNULL((1, 2, 4)) ssize_t (LIBDCALL libd_getdelim_unlocked)(char **__restrict lineptr, size_t *__restrict pcount, int delimiter, FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((1, 2, 4)) ssize_t (LIBCCALL libc_getdelim_unlocked)(char **__restrict lineptr, size_t *__restrict pcount, int delimiter, FILE *__restrict stream) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((1, 2, 3)) ssize_t (LIBDCALL libd_getline_unlocked)(char **__restrict lineptr, size_t *__restrict pcount, FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((1, 2, 3)) ssize_t (LIBCCALL libc_getline_unlocked)(char **__restrict lineptr, size_t *__restrict pcount, FILE *__restrict stream) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) void (LIBDCALL libd_rewind_unlocked)(FILE *__restrict stream) THROWS(...);
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_fisatty)(FILE *__restrict stream);
/* >> fftruncate(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
INTDEF NONNULL((1)) int (LIBDCALL libd_fftruncate)(FILE *__restrict stream, __PIO_OFFSET length) THROWS(...);
/* >> fftruncate_unlocked(3)
 * Same as `fftruncate()', but don't acquire a lock to the file */
INTDEF NONNULL((1)) int (LIBDCALL libd_fftruncate_unlocked)(FILE *__restrict stream, __PIO_OFFSET length) THROWS(...);
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd_puts_unlocked)(char const *__restrict string) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_puts_unlocked)(char const *__restrict string) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) int (LIBDCALL libd_fseeko64_unlocked)(FILE *__restrict stream, off64_t off, int whence) THROWS(...);
INTDEF WUNUSED NONNULL((1)) off64_t (LIBDCALL libd_ftello64_unlocked)(FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1, 2)) int (LIBDCALL libd_fgetpos64_unlocked)(FILE *__restrict stream, fpos64_t *__restrict pos) THROWS(...);
INTDEF NONNULL((1, 2)) int (LIBDCALL libd_fsetpos64_unlocked)(FILE *__restrict stream, fpos64_t const *__restrict pos) THROWS(...);
/* >> fftruncate64(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
INTDEF NONNULL((1)) int (LIBDCALL libd_fftruncate64)(FILE *__restrict stream, __PIO_OFFSET64 length) THROWS(...);
/* >> fftruncate64_unlocked(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
INTDEF NONNULL((1)) int (LIBDCALL libd_fftruncate64_unlocked)(FILE *__restrict stream, __PIO_OFFSET64 length) THROWS(...);
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd_vfprintf_unlocked)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_vfprintf_unlocked)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (VLIBDCALL libd_fprintf_unlocked)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (VLIBCCALL libc_fprintf_unlocked)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd_vprintf_unlocked)(char const *__restrict format, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_vprintf_unlocked)(char const *__restrict format, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T (VLIBDCALL libd_printf_unlocked)(char const *__restrict format, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T (VLIBCCALL libc_printf_unlocked)(char const *__restrict format, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vfscanf_unlocked)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc_vfscanf_unlocked)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vscanf_unlocked)(char const *__restrict format, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBCCALL libc_vscanf_unlocked)(char const *__restrict format, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_fscanf_unlocked)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc_fscanf_unlocked)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_scanf_unlocked)(char const *__restrict format, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc_scanf_unlocked)(char const *__restrict format, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> funopen(3), funopen64(3) */
INTDEF WUNUSED FILE *NOTHROW_NCX(LIBDCALL libd_funopen)(void const *cookie, __funopen_readfn_t readfn, __funopen_writefn_t writefn, __funopen_seekfn_t seekfn, __funopen_closefn_t closefn);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> funopen(3), funopen64(3) */
INTDEF WUNUSED FILE *NOTHROW_NCX(LIBCCALL libc_funopen)(void const *cookie, __funopen_readfn_t readfn, __funopen_writefn_t writefn, __funopen_seekfn_t seekfn, __funopen_closefn_t closefn);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> funopen2(3), funopen2_64(3) */
INTDEF WUNUSED FILE *NOTHROW_NCX(LIBDCALL libd_funopen2)(void const *cookie, __funopen2_readfn_t readfn, __funopen2_writefn_t writefn, __funopen2_seekfn_t seekfn, __funopen2_flushfn_t flushfn, __funopen2_closefn_t closefn);
/* >> funopen(3), funopen64(3) */
INTDEF WUNUSED FILE *NOTHROW_NCX(LIBDCALL libd_funopen64)(void const *cookie, __funopen_readfn_t readfn, __funopen_writefn_t writefn, __funopen64_seekfn_t seekfn, __funopen_closefn_t closefn);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> funopen(3), funopen64(3) */
INTDEF WUNUSED FILE *NOTHROW_NCX(LIBCCALL libc_funopen64)(void const *cookie, __funopen_readfn_t readfn, __funopen_writefn_t writefn, __funopen64_seekfn_t seekfn, __funopen_closefn_t closefn);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> funopen2(3), funopen2_64(3) */
INTDEF WUNUSED FILE *NOTHROW_NCX(LIBDCALL libd_funopen2_64)(void const *cookie, __funopen2_readfn_t readfn, __funopen2_writefn_t writefn, __funopen2_64_seekfn_t seekfn, __funopen2_flushfn_t flushfn, __funopen2_closefn_t closefn);
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_RPC(LIBDCALL libd__fsopen)(char const *filename, char const *modes, int sflag);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_RPC(LIBCCALL libc__fsopen)(char const *filename, char const *modes, int sflag);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) int (LIBDCALL libd__filbuf)(FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((2)) int (LIBDCALL libd__flsbuf)(int ch, FILE *__restrict stream) THROWS(...);
INTDEF int NOTHROW_NCX(LIBDCALL libd__setmaxstdio)(int val);
INTDEF int NOTHROW_NCX(LIBDCALL libd__set_printf_count_output)(int val);
INTDEF uint32_t NOTHROW_NCX(LIBDCALL libd__set_output_format)(uint32_t format);
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBDCALL libd__vscanf_l)(char const *__restrict format, locale_t locale, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vscanf_l)(char const *__restrict format, locale_t locale, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd__vfscanf_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vfscanf_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd__vsscanf_l)(char const *__restrict input, char const *__restrict format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsscanf_l)(char const *__restrict input, char const *__restrict format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_SCANF(3, 4) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd__vsnscanf)(char const *__restrict input, size_t inputlen, char const *__restrict format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_SCANF(3, 4) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsnscanf)(char const *__restrict input, size_t inputlen, char const *__restrict format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_SCANF(3, 5) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd__vsnscanf_l)(char const *__restrict input, size_t inputlen, char const *__restrict format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_SCANF(3, 5) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsnscanf_l)(char const *__restrict input, size_t inputlen, char const *__restrict format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd__scanf_l)(char const *__restrict format, locale_t locale, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__scanf_l)(char const *__restrict format, locale_t locale, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd__fscanf_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__fscanf_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_SCANF(3, 4) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd__snscanf)(char const *__restrict input, size_t inputlen, char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_SCANF(3, 4) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snscanf)(char const *__restrict input, size_t inputlen, char const *__restrict format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_SCANF(3, 5) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd__snscanf_l)(char const *__restrict input, size_t inputlen, char const *__restrict format, locale_t locale, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_SCANF(3, 5) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snscanf_l)(char const *__restrict input, size_t inputlen, char const *__restrict format, locale_t locale, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd__vsprintf_l)(char *__restrict buf, char const *__restrict format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsprintf_l)(char *__restrict buf, char const *__restrict format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF_P(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd__vsprintf_p)(char *__restrict buf, size_t bufsize, char const *__restrict format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF_P(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsprintf_p)(char *__restrict buf, size_t bufsize, char const *__restrict format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF_P(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd__vsprintf_p_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF_P(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsprintf_p_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd__sprintf_l)(char *__restrict buf, char const *__restrict format, locale_t locale, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__sprintf_l)(char *__restrict buf, char const *__restrict format, locale_t locale, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd__sprintf_s_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__sprintf_s_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF_P(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd__sprintf_p)(char *__restrict buf, size_t bufsize, char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF_P(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__sprintf_p)(char *__restrict buf, size_t bufsize, char const *__restrict format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF_P(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd__sprintf_p_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF_P(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__sprintf_p_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd__vscprintf)(char const *__restrict format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vscprintf)(char const *__restrict format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd__scprintf)(char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__scprintf)(char const *__restrict format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd__vscprintf_l)(char const *__restrict format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vscprintf_l)(char const *__restrict format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd__vscprintf_p)(char const *__restrict format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vscprintf_p)(char const *__restrict format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd__vscprintf_p_l)(char const *__restrict format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vscprintf_p_l)(char const *__restrict format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd__scprintf_l)(char const *__restrict format, locale_t locale, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__scprintf_l)(char const *__restrict format, locale_t locale, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_PRINTF_P(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd__scprintf_p)(char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_PRINTF_P(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__scprintf_p)(char const *__restrict format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_PRINTF_P(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd__scprintf_p_l)(char const *__restrict format, locale_t locale, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_PRINTF_P(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__scprintf_p_l)(char const *__restrict format, locale_t locale, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* WARNING: This function returns the number of written character. - Not the required buffer size! */
INTDEF ATTR_LIBC_PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd__vsnprintf)(char *__restrict buf, size_t bufsize, char const *__restrict format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* WARNING: This function returns the number of written character. - Not the required buffer size! */
INTDEF ATTR_LIBC_PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsnprintf)(char *__restrict buf, size_t bufsize, char const *__restrict format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd__vsnprintf_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsnprintf_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(4, 0) NONNULL((4)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd__vsnprintf_s)(char *__restrict buf, size_t bufsize, size_t buflen, char const *__restrict format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(4, 0) NONNULL((4)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsnprintf_s)(char *__restrict buf, size_t bufsize, size_t buflen, char const *__restrict format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(4, 0) NONNULL((4)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd__vsnprintf_s_l)(char *__restrict buf, size_t bufsize, size_t buflen, char const *__restrict format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(4, 0) NONNULL((4)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsnprintf_s_l)(char *__restrict buf, size_t bufsize, size_t buflen, char const *__restrict format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd__snprintf)(char *__restrict buf, size_t bufsize, char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snprintf)(char *__restrict buf, size_t bufsize, char const *__restrict format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd__snprintf_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snprintf_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd__snprintf_c)(char *__restrict buf, size_t bufsize, char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snprintf_c)(char *__restrict buf, size_t bufsize, char const *__restrict format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd__snprintf_c_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snprintf_c_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(4, 5) NONNULL((4)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd__snprintf_s)(char *__restrict buf, size_t bufsize, size_t buflen, char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(4, 5) NONNULL((4)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snprintf_s)(char *__restrict buf, size_t bufsize, size_t buflen, char const *__restrict format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(4, 6) NONNULL((4)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd__snprintf_s_l)(char *__restrict buf, size_t bufsize, size_t buflen, char const *__restrict format, locale_t locale, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(4, 6) NONNULL((4)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snprintf_s_l)(char *__restrict buf, size_t bufsize, size_t buflen, char const *__restrict format, locale_t locale, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBDCALL libd__vprintf_l)(char const *__restrict format, locale_t locale, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vprintf_l)(char const *__restrict format, locale_t locale, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBDCALL libd__vprintf_p)(char const *__restrict format, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vprintf_p)(char const *__restrict format, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBDCALL libd__vprintf_p_l)(char const *__restrict format, locale_t locale, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vprintf_p_l)(char const *__restrict format, locale_t locale, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd__printf_l)(char const *__restrict format, locale_t locale, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__printf_l)(char const *__restrict format, locale_t locale, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd__printf_s_l)(char const *__restrict format, locale_t locale, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__printf_s_l)(char const *__restrict format, locale_t locale, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF_P(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd__printf_p)(char const *__restrict format, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF_P(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__printf_p)(char const *__restrict format, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF_P(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd__printf_p_l)(char const *__restrict format, locale_t locale, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF_P(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__printf_p_l)(char const *__restrict format, locale_t locale, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd__vfprintf_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vfprintf_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF_P(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd__vfprintf_p)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF_P(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vfprintf_p)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF_P(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd__vfprintf_p_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF_P(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vfprintf_p_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd__fprintf_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__fprintf_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd__fprintf_s_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__fprintf_s_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF_P(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd__fprintf_p)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF_P(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__fprintf_p)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF_P(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd__fprintf_p_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF_P(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__fprintf_p_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_RPC(LIBDCALL libd_fopen_s)(FILE **pstream, char const *filename, char const *modes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_RPC(LIBCCALL libc_fopen_s)(FILE **pstream, char const *filename, char const *modes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 2, 3, 4)) errno_t NOTHROW_RPC(LIBDCALL libd_freopen_s)(FILE **pstream, char const *filename, char const *modes, FILE *oldstream);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 2, 3, 4)) errno_t NOTHROW_RPC(LIBCCALL libc_freopen_s)(FILE **pstream, char const *filename, char const *modes, FILE *oldstream);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_tmpnam_s)(char *__restrict buf, rsize_t bufsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_tmpnam_s)(char *__restrict buf, rsize_t bufsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_clearerr_s)(FILE *__restrict stream);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_clearerr_s)(FILE *__restrict stream);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) errno_t NOTHROW_RPC(LIBDCALL libd_tmpfile_s)(FILE **pstream);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) errno_t NOTHROW_RPC(LIBCCALL libc_tmpfile_s)(FILE **pstream);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((1, 5)) size_t NOTHROW_RPC(LIBDCALL libd_fread_s)(void *__restrict buf, size_t bufsize, size_t elemsize, size_t elemcount, FILE *__restrict stream);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((1, 5)) size_t NOTHROW_RPC(LIBCCALL libc_fread_s)(void *__restrict buf, size_t bufsize, size_t elemsize, size_t elemcount, FILE *__restrict stream);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_RPC(LIBDCALL libd_gets_s)(char *__restrict buf, rsize_t bufsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_RPC(LIBCCALL libc_gets_s)(char *__restrict buf, rsize_t bufsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(4, 0) NONNULL((4)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd_vsnprintf_s)(char *__restrict buf, size_t bufsize, size_t buflen, char const *__restrict format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(4, 0) NONNULL((4)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_vsnprintf_s)(char *__restrict buf, size_t bufsize, size_t buflen, char const *__restrict format, va_list args);
INTDEF ATTR_COLD void (LIBDCALL libd__wperror)(char16_t const *__restrict message) THROWS(...);
INTDEF ATTR_COLD void (LIBKCALL libc__wperror)(char32_t const *__restrict message) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((1, 5)) size_t (LIBDCALL libd__fread_nolock_s)(void *__restrict buf, size_t bufsize, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((1, 5)) size_t (LIBCCALL libc__fread_nolock_s)(void *__restrict buf, size_t bufsize, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_STDIO_H */
