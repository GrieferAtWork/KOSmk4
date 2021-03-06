/* HASH CRC-32:0x69db1a2a */
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
/* >> remove(3)
 * Remove a file or directory `filename' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_remove)(char const *filename);
/* >> rename(3)
 * Rename a given file `oldname' to `newname_or_path', or in the event
 * that `newname_or_path' refers to a directory, place the file within. */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_rename)(char const *oldname, char const *newname_or_path);
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_tmpnam)(char *buf);
/* >> fclose(3)
 * Close and destroy a given file `stream' */
INTDEF NONNULL((1)) int (LIBDCALL libd_fclose)(FILE *__restrict stream) THROWS(...);
/* >> fflush(3)
 * Flush any unwritten data from `stream' to the underlying filesystem/TTY */
INTDEF int (LIBDCALL libd_fflush)(FILE *stream) THROWS(...);
/* >> setbuf(3)
 * Alias for `setvbuf(stream, buf, _IOFBF, BUFSIZ)' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd_setbuf)(FILE *__restrict stream, char *buf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> setbuf(3)
 * Alias for `setvbuf(stream, buf, _IOFBF, BUFSIZ)' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_setbuf)(FILE *__restrict stream, char *buf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> setvbuf(3)
 * Set the buffer and buffer-mode to-be used by the given `stream'
 * @param modes: One of `_IOFBF', `_IOLBF' or `_IONBF' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_setvbuf)(FILE *__restrict stream, char *__restrict buf, __STDC_INT_AS_UINT_T modes, size_t bufsize);
/* >> fgetc(3)
 * Read and return a single character from `stream'
 * If the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
INTDEF NONNULL((1)) int (LIBDCALL libd_fgetc)(FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getchar(3)
 * Alias for `fgetc(stdin)' */
INTDEF int (LIBCCALL libc_getchar)(void) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fputc(3)
 * Write a single character `ch' to `stream' */
INTDEF NONNULL((2)) int (LIBDCALL libd_fputc)(int ch, FILE *__restrict stream) THROWS(...);
/* >> putchar(3)
 * Alias for `fputc(ch, stdout)' */
INTDEF int (LIBDCALL libd_putchar)(int ch) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> putchar(3)
 * Alias for `fputc(ch, stdout)' */
INTDEF int (LIBCCALL libc_putchar)(int ch) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fgets(3)
 * Read up to `bufsize - 1' bytes of data from `stream', storing them into `buf' stopped when
 * the buffer is full or a line-feed was read (in this case, the line-feed is also written to `buf')
 * Afterwards, append a trailing NUL-character and re-return `buf', or return `NULL' if an error occurred. */
INTDEF WUNUSED NONNULL((1, 3)) char *(LIBDCALL libd_fgets)(char *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fgets(3)
 * Read up to `bufsize - 1' bytes of data from `stream', storing them into `buf' stopped when
 * the buffer is full or a line-feed was read (in this case, the line-feed is also written to `buf')
 * Afterwards, append a trailing NUL-character and re-return `buf', or return `NULL' if an error occurred. */
INTDEF WUNUSED NONNULL((1, 3)) char *(LIBCCALL libc_fgets)(char *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fputs(3)
 * Print a given string `str' to `stream'. This is identical to:
 * >> fwrite(str, sizeof(char), strlen(str), stream); */
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd_fputs)(char const *__restrict str, FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fputs(3)
 * Print a given string `str' to `stream'. This is identical to:
 * >> fwrite(str, sizeof(char), strlen(str), stream); */
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_fputs)(char const *__restrict str, FILE *__restrict stream) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> puts(3)
 * Print a given string `str', followed by a line-feed to `stdout' */
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd_puts)(char const *__restrict string) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> puts(3)
 * Print a given string `str', followed by a line-feed to `stdout' */
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_puts)(char const *__restrict string) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ungetc(3)
 * Unget a single character byte of data previously returned by `getc()' */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBDCALL libd_ungetc)(int ch, FILE *__restrict stream);
/* >> fread(3)
 * Read up to `elemsize * elemcount' bytes of data from `stream' into `buf' */
INTDEF WUNUSED NONNULL((1, 4)) size_t (LIBDCALL libd_fread)(void *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
/* >> fwrite(3)
 * Write up to `elemsize * elemcount' bytes of data from `buf' into `stream' */
INTDEF NONNULL((1, 4)) size_t (LIBDCALL libd_fwrite)(void const *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
/* >> fseek(3)
 * Change the current in-file position of `stream' as a byte-offet from the start of the file */
INTDEF NONNULL((1)) int (LIBDCALL libd_fseek)(FILE *__restrict stream, long int off, int whence) THROWS(...);
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offet from the start of the file */
INTDEF WUNUSED NONNULL((1)) long int (LIBDCALL libd_ftell)(FILE *__restrict stream) THROWS(...);
/* >> rewind(3)
 * Rewind the current in-file position of `stream' to its starting position */
INTDEF NONNULL((1)) void (LIBDCALL libd_rewind)(FILE *__restrict stream) THROWS(...);
/* >> clearerr(3)
 * Clear the error state of `stream', returning the stream to normal operations mode */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd_clearerr)(FILE *__restrict stream);
/* >> feof(3)
 * Check if end-of-file has been reached in `stream' */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_feof)(FILE __KOS_FIXED_CONST *__restrict stream);
/* >> ferror(3)
 * Check if an I/O error occurred in `stream' */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_ferror)(FILE __KOS_FIXED_CONST *__restrict stream);
/* >> perror(3)
 * Print a given `message' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
INTDEF void NOTHROW_RPC(LIBDCALL libd_perror)(char const *message);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> perror(3)
 * Print a given `message' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
INTDEF void NOTHROW_RPC(LIBCCALL libc_perror)(char const *message);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fopen(3), fopen64(3)
 * Create and return a new file-stream for accessing `filename' */
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_RPC(LIBDCALL libd_fopen)(char const *__restrict filename, char const *__restrict modes);
/* >> freopen(3), freopen64(3)
 * Re-open the given `stream' as a file-stream for accessing `filename' */
INTDEF NONNULL((1, 2, 3)) FILE *NOTHROW_RPC(LIBDCALL libd_freopen)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* >> fgetpos(3), fgetpos64(3)
 * Initialize an opaque descriptor `pos' for the current in-file position of `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
INTDEF NONNULL((1, 2)) int (LIBDCALL libd_fgetpos)(FILE *__restrict stream, fpos_t *__restrict pos) THROWS(...);
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
INTDEF NONNULL((1, 2)) int (LIBDCALL libd_fsetpos)(FILE *__restrict stream, fpos_t const *__restrict pos) THROWS(...);
/* >> fprintf(3), vfprintf(3)
 * Print data to `stream', following `format'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd_vfprintf)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fprintf(3), vfprintf(3)
 * Print data to `stream', following `format'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_vfprintf)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fprintf(3), vfprintf(3)
 * Print data to `stream', following `format'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (VLIBDCALL libd_fprintf)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fprintf(3), vfprintf(3)
 * Print data to `stream', following `format'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (VLIBCCALL libc_fprintf)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> printf(3), vprintf(3)
 * Print data to `stdout', following `format'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd_vprintf)(char const *__restrict format, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> printf(3), vprintf(3)
 * Print data to `stdout', following `format'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_vprintf)(char const *__restrict format, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> printf(3), vprintf(3)
 * Print data to `stdout', following `format'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T (VLIBDCALL libd_printf)(char const *__restrict format, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> printf(3), vprintf(3)
 * Print data to `stdout', following `format'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T (VLIBCCALL libc_printf)(char const *__restrict format, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fscanf(3), vfscanf(3)
 * Scan data from `stream', following `format'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vfscanf)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fscanf(3), vfscanf(3)
 * Scan data from `stream', following `format'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc_vfscanf)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> scanf(3), vscanf(3)
 * Scan data from `stdin', following `format'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vscanf)(char const *__restrict format, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> scanf(3), vscanf(3)
 * Scan data from `stdin', following `format'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBCCALL libc_vscanf)(char const *__restrict format, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fscanf(3), vfscanf(3)
 * Scan data from `stream', following `format'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_fscanf)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fscanf(3), vfscanf(3)
 * Scan data from `stream', following `format'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc_fscanf)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> scanf(3), vscanf(3)
 * Scan data from `stdin', following `format'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_scanf)(char const *__restrict format, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> scanf(3), vscanf(3)
 * Scan data from `stdin', following `format'
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
/* >> sscanf(3), vsscanf(3)
 * Scan data from a given `input' string, following `format'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd_vsscanf)(char const *__restrict input, char const *__restrict format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> sscanf(3), vsscanf(3)
 * Scan data from a given `input' string, following `format'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_vsscanf)(char const *__restrict input, char const *__restrict format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sscanf(3), vsscanf(3)
 * Scan data from a given `input' string, following `format'
 * Return the number of successfully scanned data items */
INTDEF ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd_sscanf)(char const *__restrict input, char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> sscanf(3), vsscanf(3)
 * Scan data from a given `input' string, following `format'
 * Return the number of successfully scanned data items */
INTDEF ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc_sscanf)(char const *__restrict input, char const *__restrict format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sprintf(3), vsprintf(3)
 * Print a formatted string to a given in-member string buffer `buf'
 * Return the number of written characters, excluding a trailing NUL-character */
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd_vsprintf)(char *__restrict dest, char const *__restrict format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> sprintf(3), vsprintf(3)
 * Print a formatted string to a given in-member string buffer `buf'
 * Return the number of written characters, excluding a trailing NUL-character */
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc_vsprintf)(char *__restrict dest, char const *__restrict format, va_list args);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sprintf(3), vsprintf(3)
 * Print a formatted string to a given in-member string buffer `buf'
 * Return the number of written characters, excluding a trailing NUL-character */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd_sprintf)(char *__restrict buf, char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> sprintf(3), vsprintf(3)
 * Print a formatted string to a given in-member string buffer `buf'
 * Return the number of written characters, excluding a trailing NUL-character */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc_sprintf)(char *__restrict buf, char const *__restrict format, ...);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> snprintf(3), vsnprintf(3)
 * Print a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-
 * character), and never write more than `buflen' characters to `buf' */
INTDEF ATTR_LIBC_PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd_vsnprintf)(char *__restrict buf, size_t buflen, char const *__restrict format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> snprintf(3), vsnprintf(3)
 * Print a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-
 * character), and never write more than `buflen' characters to `buf' */
INTDEF ATTR_LIBC_PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_vsnprintf)(char *__restrict buf, size_t buflen, char const *__restrict format, va_list args);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> snprintf(3), vsnprintf(3)
 * Print a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-
 * character), and never write more than `buflen' characters to `buf' */
INTDEF ATTR_LIBC_PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd_snprintf)(char *__restrict buf, size_t buflen, char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> snprintf(3), vsnprintf(3)
 * Print a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-
 * character), and never write more than `buflen' characters to `buf' */
INTDEF ATTR_LIBC_PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc_snprintf)(char *__restrict buf, size_t buflen, char const *__restrict format, ...);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dprintf(3), vdprintf(3) */
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBDCALL libd_vdprintf)(fd_t fd, char const *__restrict format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> dprintf(3), vdprintf(3) */
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBCCALL libc_vdprintf)(fd_t fd, char const *__restrict format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dprintf(3), vdprintf(3) */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(VLIBDCALL libd_dprintf)(fd_t fd, char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> dprintf(3), vdprintf(3) */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(VLIBCCALL libc_dprintf)(fd_t fd, char const *__restrict format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> renameat(2) */
INTDEF NONNULL((2, 4)) int NOTHROW_RPC(LIBDCALL libd_renameat)(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path);
/* >> removeat(3)
 * Remove a file or directory `filename' relative to a given base directory `dirfd' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBDCALL libd_removeat)(fd_t dirfd, char const *filename);
/* >> frenameat(2)
 * @param flags: Set of `0 | AT_DOSPATH' */
INTDEF NONNULL((2, 4)) int NOTHROW_RPC(LIBDCALL libd_frenameat)(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path, atflag_t flags);
/* >> tmpnam_r(3) */
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_tmpnam_r)(char *buf);
/* >> setbuffer(3)
 * Specify the location and size for the buffer to-be used by `stream' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd_setbuffer)(FILE *__restrict stream, char *buf, size_t bufsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> setbuffer(3)
 * Specify the location and size for the buffer to-be used by `stream' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_setbuffer)(FILE *__restrict stream, char *buf, size_t bufsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> setlinebuf(3)
 * Change the given `stream' to become line-buffered */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd_setlinebuf)(FILE *__restrict stream);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> setlinebuf(3)
 * Change the given `stream' to become line-buffered */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_setlinebuf)(FILE *__restrict stream);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fflush_unlocked(3)
 * Same as `fflush()', but performs I/O without acquiring a lock to `stream' */
INTDEF int (LIBDCALL libd_fflush_unlocked)(FILE *stream) THROWS(...);
/* >> fread_unlocked(3)
 * Same as `fread()', but performs I/O without acquiring a lock to `stream' */
INTDEF WUNUSED NONNULL((1, 4)) size_t (LIBDCALL libd_fread_unlocked)(void *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
/* >> fwrite_unlocked(3)
 * Same as `fwrite()', but performs I/O without acquiring a lock to `stream' */
INTDEF WUNUSED NONNULL((1, 4)) size_t (LIBDCALL libd_fwrite_unlocked)(void const *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
INTDEF NONNULL((1)) int (LIBDCALL libd_fgetc_unlocked)(FILE *__restrict stream) THROWS(...);
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
INTDEF NONNULL((2)) int (LIBDCALL libd_fputc_unlocked)(int ch, FILE *__restrict stream) THROWS(...);
/* >> tempnam(3) */
INTDEF ATTR_MALLOC WUNUSED char *NOTHROW_NCX(LIBDCALL libd_tempnam)(char const *dir, char const *pfx);
/* >> fdopen(3)
 * Open a new file stream by inheriting a given file descriptor `fd'
 * Note that upon success (`return != NULL'), the given `fd'
 * will be `close()'d once `fclose(return)' is called */
INTDEF WUNUSED NONNULL((2)) FILE *NOTHROW_NCX(LIBDCALL libd_fdopen)(fd_t fd, char const *__restrict modes);
/* >> fileno(3)
 * Return the underlying file descriptor number used by `stream' */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_NCX(LIBDCALL libd_fileno)(FILE *__restrict stream);
/* >> fmemopen(3) */
INTDEF WUNUSED NONNULL((1, 3)) FILE *NOTHROW_NCX(LIBDCALL libd_fmemopen)(void *mem, size_t len, char const *modes);
/* >> open_memstream(3) */
INTDEF WUNUSED FILE *NOTHROW_NCX(LIBDCALL libd_open_memstream)(char **bufloc, size_t *sizeloc);
/* >> getdelim(3) */
INTDEF WUNUSED NONNULL((1, 2, 4)) ssize_t (LIBDCALL libd_getdelim)(char **__restrict lineptr, size_t *__restrict pcount, int delimiter, FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getdelim(3) */
INTDEF WUNUSED NONNULL((1, 2, 4)) ssize_t (LIBCCALL libc_getdelim)(char **__restrict lineptr, size_t *__restrict pcount, int delimiter, FILE *__restrict stream) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> getline(3) */
INTDEF WUNUSED NONNULL((1, 2, 3)) ssize_t (LIBDCALL libd_getline)(char **__restrict lineptr, size_t *__restrict pcount, FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getline(3) */
INTDEF WUNUSED NONNULL((1, 2, 3)) ssize_t (LIBCCALL libc_getline)(char **__restrict lineptr, size_t *__restrict pcount, FILE *__restrict stream) THROWS(...);
/* >> getchar_unlocked(3)
 * Same as `getchar()', but performs I/O without acquiring a lock to `stdin' */
INTDEF int (LIBCCALL libc_getchar_unlocked)(void) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> putchar_unlocked(3)
 * Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
INTDEF int (LIBDCALL libd_putchar_unlocked)(int ch) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> putchar_unlocked(3)
 * Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
INTDEF int (LIBCCALL libc_putchar_unlocked)(int ch) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> flockfile(3)
 * Acquire a lock to `stream' and block until doing so succeeds */
INTDEF NONNULL((1)) void NOTHROW_RPC(LIBDCALL libd_flockfile)(FILE *__restrict stream);
/* >> funlockfile(3)
 * Release a previously acquired lock from `stream' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd_funlockfile)(FILE *__restrict stream);
/* >> ftrylockfile(3)
 * Try to acquire a lock to `stream' */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_ftrylockfile)(FILE *__restrict stream);
/* >> popen(3)
 * Open and return a new process I/O stream for executing `COMMAND' */
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_RPC(LIBDCALL libd_popen)(char const *command, char const *modes);
/* >> pclose(3)
 * Close a process I/O file `stream' (s.a. `popen(3)') */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_pclose)(FILE *stream);
/* >> popenve(3)
 * Similar to `popen(3)', but rather than running `execl("/bin/sh", "-c", command)',
 * this function will `execve(path, argv, envp)'. The returned FILE must still be
 * closed using `pclose(3)', rather than `fclose(3)' */
INTDEF WUNUSED NONNULL((1, 2, 3, 4)) FILE *NOTHROW_RPC(LIBDCALL libd_popenve)(char const *path, __TARGV, __TENVP, char const *modes);
/* >> getw(3)
 * Similar to `getc()', but read 2 bytes */
INTDEF NONNULL((1)) int (LIBDCALL libd_getw)(FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getw(3)
 * Similar to `getc()', but read 2 bytes */
INTDEF NONNULL((1)) int (LIBCCALL libc_getw)(FILE *__restrict stream) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> putw(3)
 * Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
INTDEF NONNULL((2)) int (LIBDCALL libd_putw)(int w, FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> putw(3)
 * Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
INTDEF NONNULL((2)) int (LIBCCALL libc_putw)(int w, FILE *__restrict stream) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fopencookie(3) */
INTDEF WUNUSED NONNULL((2)) FILE *NOTHROW_NCX(LIBDCALL libd_fopencookie)(void *__restrict magic_cookie, char const *__restrict modes, cookie_io_functions_t io_funcs);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fopencookie(3) */
INTDEF WUNUSED NONNULL((2)) FILE *NOTHROW_NCX(LIBCCALL libc_fopencookie)(void *__restrict magic_cookie, char const *__restrict modes, cookie_io_functions_t io_funcs);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fgets_unlocked(3)
 * Same as `fgets()', but performs I/O without acquiring a lock to `stream' */
INTDEF WUNUSED NONNULL((1, 3)) char *(LIBDCALL libd_fgets_unlocked)(char *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fgets_unlocked(3)
 * Same as `fgets()', but performs I/O without acquiring a lock to `stream' */
INTDEF WUNUSED NONNULL((1, 3)) char *(LIBCCALL libc_fgets_unlocked)(char *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fputs_unlocked(3)
 * Same as `fputs()', but performs I/O without acquiring a lock to `stream' */
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_fputs_unlocked)(char const *__restrict string, FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fputs_unlocked(3)
 * Same as `fputs()', but performs I/O without acquiring a lock to `stream' */
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
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
INTDEF NONNULL((1)) int (LIBDCALL libd_fseeko)(FILE *__restrict stream, off_t off, int whence) THROWS(...);
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
INTDEF WUNUSED NONNULL((1)) off_t (LIBDCALL libd_ftello)(FILE *__restrict stream) THROWS(...);
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
INTDEF NONNULL((1)) int (LIBDCALL libd_fseeko64)(FILE *__restrict stream, off64_t off, int whence) THROWS(...);
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
INTDEF WUNUSED NONNULL((1)) off64_t (LIBDCALL libd_ftello64)(FILE *__restrict stream) THROWS(...);
/* >> fopen(3), fopen64(3)
 * Create and return a new file-stream for accessing `filename' */
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_RPC(LIBDCALL libd_fopen64)(char const *__restrict filename, char const *__restrict modes);
/* >> freopen(3), freopen64(3)
 * Re-open the given `stream' as a file-stream for accessing `filename' */
INTDEF NONNULL((1, 2, 3)) FILE *NOTHROW_RPC(LIBDCALL libd_freopen64)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* >> fgetpos(3), fgetpos64(3)
 * Initialize an opaque descriptor `pos' for the current in-file position of `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
INTDEF NONNULL((1, 2)) int (LIBDCALL libd_fgetpos64)(FILE *__restrict stream, fpos64_t *__restrict pos) THROWS(...);
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
INTDEF NONNULL((1, 2)) int (LIBDCALL libd_fsetpos64)(FILE *__restrict stream, fpos64_t const *__restrict pos) THROWS(...);
/* >> asprintf(3), vasprintf(3)
 * Print the given `format' into a newly allocated, heap-allocated string which is then stored in `*pstr' */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd_vasprintf)(char **__restrict pstr, char const *__restrict format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> asprintf(3), vasprintf(3)
 * Print the given `format' into a newly allocated, heap-allocated string which is then stored in `*pstr' */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc_vasprintf)(char **__restrict pstr, char const *__restrict format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> asprintf(3), vasprintf(3)
 * Print the given `format' into a newly allocated, heap-allocated string which is then stored in `*pstr' */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd_asprintf)(char **__restrict pstr, char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> asprintf(3), vasprintf(3)
 * Print the given `format' into a newly allocated, heap-allocated string which is then stored in `*pstr' */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc_asprintf)(char **__restrict pstr, char const *__restrict format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fdreopen(3)
 * Re-open the given `stream' as a file-stream for accessing `fd' */
INTDEF NONNULL((2, 3)) FILE *NOTHROW_RPC(LIBDCALL libd_fdreopen)(fd_t fd, char const *__restrict modes, FILE *__restrict stream);
/* >> fdreopen(3)
 * Re-open the given `stream' as a file-stream for accessing `fd' */
INTDEF NONNULL((2, 3)) FILE *NOTHROW_RPC(LIBDCALL libd_fdreopen_unlocked)(fd_t fd, char const *__restrict modes, FILE *__restrict stream);
/* >> freopen(3), freopen64(3)
 * Re-open the given `stream' as a file-stream for accessing `filename' */
INTDEF NONNULL((1, 2, 3)) FILE *NOTHROW_RPC(LIBDCALL libd_freopen_unlocked)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* >> freopen(3), freopen64(3)
 * Re-open the given `stream' as a file-stream for accessing `filename' */
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
/* >> getdelim(3) */
INTDEF WUNUSED NONNULL((1, 2, 4)) ssize_t (LIBDCALL libd_getdelim_unlocked)(char **__restrict lineptr, size_t *__restrict pcount, int delimiter, FILE *__restrict stream) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getdelim(3) */
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
 * Truncate the given file `stream' to a length of `length' */
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
 * Truncate the given file `stream' to a length of `length' */
INTDEF NONNULL((1)) int (LIBDCALL libd_fftruncate64)(FILE *__restrict stream, __PIO_OFFSET64 length) THROWS(...);
/* >> fftruncate64_unlocked(3)
 * Truncate the given file `stream' to a length of `length' */
INTDEF NONNULL((1)) int (LIBDCALL libd_fftruncate64_unlocked)(FILE *__restrict stream, __PIO_OFFSET64 length) THROWS(...);
/* >> fprintf_unlocked(3), vfprintf_unlocked(3) */
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd_vfprintf_unlocked)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fprintf_unlocked(3), vfprintf_unlocked(3) */
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_vfprintf_unlocked)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fprintf_unlocked(3), vfprintf_unlocked(3) */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (VLIBDCALL libd_fprintf_unlocked)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fprintf_unlocked(3), vfprintf_unlocked(3) */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (VLIBCCALL libc_fprintf_unlocked)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> printf_unlocked(3), vprintf_unlocked(3) */
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd_vprintf_unlocked)(char const *__restrict format, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> printf_unlocked(3), vprintf_unlocked(3) */
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_vprintf_unlocked)(char const *__restrict format, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> printf_unlocked(3), vprintf_unlocked(3) */
INTDEF ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T (VLIBDCALL libd_printf_unlocked)(char const *__restrict format, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> printf_unlocked(3), vprintf_unlocked(3) */
INTDEF ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T (VLIBCCALL libc_printf_unlocked)(char const *__restrict format, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fscanf_unlocked(3), vfscanf_unlocked(3) */
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vfscanf_unlocked)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fscanf_unlocked(3), vfscanf_unlocked(3) */
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc_vfscanf_unlocked)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> scanf_unlocked(3), vscanf_unlocked(3) */
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vscanf_unlocked)(char const *__restrict format, va_list args) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> scanf_unlocked(3), vscanf_unlocked(3) */
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBCCALL libc_vscanf_unlocked)(char const *__restrict format, va_list args) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fscanf_unlocked(3), vfscanf_unlocked(3) */
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_fscanf_unlocked)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fscanf_unlocked(3), vfscanf_unlocked(3) */
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc_fscanf_unlocked)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> scanf_unlocked(3), vscanf_unlocked(3) */
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_scanf_unlocked)(char const *__restrict format, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> scanf_unlocked(3), vscanf_unlocked(3) */
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc_scanf_unlocked)(char const *__restrict format, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fgetln(3) */
INTDEF WUNUSED NONNULL((1, 2)) char *NOTHROW_NCX(LIBDCALL libd_fgetln)(FILE *__restrict fp, size_t *__restrict lenp);
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
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) __ATTR_FORMAT_ARG(2) char const *NOTHROW_NCX(LIBDCALL libd_fmtcheck)(char const *user_format, char const *good_format);
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
