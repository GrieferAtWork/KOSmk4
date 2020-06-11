/* HASH CRC-32:0xae58b457 */
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
#ifndef GUARD_LIBC_AUTO_STDIO_H
#define GUARD_LIBC_AUTO_STDIO_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <stdio.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Alias for `setvbuf(STREAM, buf, _IOFBF, BUFSIZ)' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_setbuf)(FILE *__restrict stream, char *buf);
/* Alias for `fgetc(stdin)' */
INTDEF int (LIBCCALL libc_getchar)(void) THROWS(...);
/* Alias for `fputc(CH, stdout)' */
INTDEF int (LIBCCALL libc_putchar)(int ch) THROWS(...);
/* Read up to `BUFSIZE - 1' bytes of data from `STREAM', storing them into `BUF' stopped when
 * the buffer is full or a line-feed was read (in this case, the line-feed is also written to `BUF')
 * Afterwards, append a trailing NUL-character and re-return `BUF', or return `NULL' if an error occurred. */
INTDEF WUNUSED NONNULL((1, 3)) char *(LIBCCALL libc_fgets)(char *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) THROWS(...);
/* Print a given string `STR' to `STREAM'. This is identical to:
 * >> fwrite(str, sizeof(char), strlen(str), stream); */
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_fputs)(char const *__restrict str, FILE *__restrict stream) THROWS(...);
/* Print a given string `STR', followed by a line-feed to `STDOUT' */
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_puts)(char const *__restrict string) THROWS(...);
/* Print a given `MESSAGE' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
INTDEF void NOTHROW_RPC(LIBCCALL libc_perror)(char const *message);
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_vfprintf)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (VLIBCCALL libc_fprintf)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_vprintf)(char const *__restrict format, va_list args) THROWS(...);
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
INTDEF ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T (VLIBCCALL libc_printf)(char const *__restrict format, ...) THROWS(...);
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc_vfscanf)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBCCALL libc_vscanf)(char const *__restrict format, va_list args) THROWS(...);
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc_fscanf)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc_scanf)(char const *__restrict format, ...) THROWS(...);
INTDEF WUNUSED ATTR_DEPRECATED("No buffer size checks (use `fgets' instead)") NONNULL((1)) char *(LIBCCALL libc_gets)(char *__restrict buf) THROWS(...);
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_vsscanf)(char const *__restrict input, char const *__restrict format, va_list args);
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc_sscanf)(char const *__restrict input, char const *__restrict format, ...);
#endif /* !__KERNEL__ */
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc_vsprintf)(char *__restrict dest, char const *__restrict format, va_list args);
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc_sprintf)(char *__restrict buf, char const *__restrict format, ...);
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
INTDEF ATTR_LIBC_PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_vsnprintf)(char *__restrict buf, size_t buflen, char const *__restrict format, va_list args);
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
INTDEF ATTR_LIBC_PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc_snprintf)(char *__restrict buf, size_t buflen, char const *__restrict format, ...);
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBCCALL libc_vdprintf)(fd_t fd, char const *__restrict format, va_list args);
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(VLIBCCALL libc_dprintf)(fd_t fd, char const *__restrict format, ...);
/* Specify the location and size for the buffer to-be used by `STREAM' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_setbuffer)(FILE *__restrict stream, char *buf, size_t bufsize);
/* Change the given `STREAM' to become line-buffered */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_setlinebuf)(FILE *__restrict stream);
INTDEF WUNUSED NONNULL((1, 2, 4)) ssize_t (LIBCCALL libc_getdelim)(char **__restrict lineptr, size_t *__restrict pcount, int delimiter, FILE *__restrict stream) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 3)) ssize_t (LIBCCALL libc_getline)(char **__restrict lineptr, size_t *__restrict pcount, FILE *__restrict stream) THROWS(...);
/* Same as `getchar()', but performs I/O without acquiring a lock to `stdin' */
INTDEF int (LIBCCALL libc_getchar_unlocked)(void) THROWS(...);
/* Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
INTDEF int (LIBCCALL libc_putchar_unlocked)(int ch) THROWS(...);
/* Similar to `getc()', but read 2 bytes */
INTDEF NONNULL((1)) int (LIBCCALL libc_getw)(FILE *__restrict stream) THROWS(...);
/* Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
INTDEF NONNULL((2)) int (LIBCCALL libc_putw)(int w, FILE *__restrict stream) THROWS(...);
/* Same as `fgets()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTDEF WUNUSED NONNULL((1, 3)) char *(LIBCCALL libc_fgets_unlocked)(char *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) THROWS(...);
/* Same as `fputs()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc_fputs_unlocked)(char const *__restrict string, FILE *__restrict stream) THROWS(...);
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(VLIBCCALL libc_obstack_printf)(struct obstack *__restrict obstack_, char const *__restrict format, ...);
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
INTDEF WUNUSED ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc_vasprintf)(char **__restrict pstr, char const *__restrict format, va_list args);
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
INTDEF WUNUSED ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc_asprintf)(char **__restrict pstr, char const *__restrict format, ...);
INTDEF NONNULL((1)) int (LIBCCALL libc_getw_unlocked)(FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((2)) int (LIBCCALL libc_putw_unlocked)(int w, FILE *__restrict stream) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 4)) ssize_t (LIBCCALL libc_getdelim_unlocked)(char **__restrict lineptr, size_t *__restrict pcount, int delimiter, FILE *__restrict stream) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 3)) ssize_t (LIBCCALL libc_getline_unlocked)(char **__restrict lineptr, size_t *__restrict pcount, FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_puts_unlocked)(char const *__restrict string) THROWS(...);
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_vfprintf_unlocked)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
INTDEF ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (VLIBCCALL libc_fprintf_unlocked)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBCCALL libc_vprintf_unlocked)(char const *__restrict format, va_list args) THROWS(...);
INTDEF ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T (VLIBCCALL libc_printf_unlocked)(char const *__restrict format, ...) THROWS(...);
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc_vfscanf_unlocked)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBCCALL libc_vscanf_unlocked)(char const *__restrict format, va_list args) THROWS(...);
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc_fscanf_unlocked)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc_scanf_unlocked)(char const *__restrict format, ...) THROWS(...);
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vscanf_l)(char const *__restrict format, locale_t locale, va_list args) THROWS(...);
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vfscanf_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, va_list args) THROWS(...);
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsscanf_l)(char const *__restrict input, char const *__restrict format, locale_t locale, va_list args);
INTDEF WUNUSED ATTR_LIBC_SCANF(3, 4) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsnscanf)(char const *__restrict input, size_t inputlen, char const *__restrict format, va_list args);
INTDEF ATTR_LIBC_SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__scanf_l)(char const *__restrict format, locale_t locale, ...) THROWS(...);
INTDEF ATTR_LIBC_SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__fscanf_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, ...) THROWS(...);
INTDEF ATTR_LIBC_SCANF(3, 4) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snscanf)(char const *__restrict input, size_t inputlen, char const *__restrict format, ...);
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsprintf_l)(char *__restrict buf, char const *__restrict format, locale_t locale, va_list args);
INTDEF ATTR_LIBC_PRINTF_P(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsprintf_p)(char *__restrict buf, size_t bufsize, char const *__restrict format, va_list args);
INTDEF ATTR_LIBC_PRINTF_P(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsprintf_p_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, va_list args);
INTDEF ATTR_LIBC_PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__sprintf_l)(char *__restrict buf, char const *__restrict format, locale_t locale, ...);
INTDEF ATTR_LIBC_PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__sprintf_s_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, ...);
INTDEF ATTR_LIBC_PRINTF_P(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__sprintf_p)(char *__restrict buf, size_t bufsize, char const *__restrict format, ...);
INTDEF ATTR_LIBC_PRINTF_P(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__sprintf_p_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, ...);
INTDEF WUNUSED ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vscprintf)(char const *__restrict format, va_list args);
INTDEF WUNUSED ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__scprintf)(char const *__restrict format, ...);
INTDEF WUNUSED ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vscprintf_l)(char const *__restrict format, locale_t locale, va_list args);
INTDEF WUNUSED ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vscprintf_p)(char const *__restrict format, va_list args);
INTDEF WUNUSED ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vscprintf_p_l)(char const *__restrict format, locale_t locale, va_list args);
INTDEF WUNUSED ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__scprintf_l)(char const *__restrict format, locale_t locale, ...);
INTDEF WUNUSED ATTR_LIBC_PRINTF_P(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__scprintf_p)(char const *__restrict format, ...);
INTDEF WUNUSED ATTR_LIBC_PRINTF_P(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__scprintf_p_l)(char const *__restrict format, locale_t locale, ...);
/* WARNING: This function returns the number of written character. - Not the required buffer size! */
INTDEF ATTR_LIBC_PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsnprintf)(char *__restrict buf, size_t bufsize, char const *__restrict format, va_list args);
INTDEF ATTR_LIBC_PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsnprintf_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, va_list args);
INTDEF ATTR_LIBC_PRINTF(4, 0) NONNULL((4)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsnprintf_s)(char *__restrict buf, size_t bufsize, size_t buflen, char const *__restrict format, va_list args);
INTDEF ATTR_LIBC_PRINTF(4, 0) NONNULL((4)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsnprintf_s_l)(char *__restrict buf, size_t bufsize, size_t buflen, char const *__restrict format, locale_t locale, va_list args);
INTDEF ATTR_LIBC_PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snprintf)(char *__restrict buf, size_t bufsize, char const *__restrict format, ...);
INTDEF ATTR_LIBC_PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snprintf_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, ...);
INTDEF ATTR_LIBC_PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snprintf_c)(char *__restrict buf, size_t bufsize, char const *__restrict format, ...);
INTDEF ATTR_LIBC_PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snprintf_c_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, ...);
INTDEF ATTR_LIBC_PRINTF(4, 5) NONNULL((4)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snprintf_s)(char *__restrict buf, size_t bufsize, size_t buflen, char const *__restrict format, ...);
INTDEF ATTR_LIBC_PRINTF(4, 6) NONNULL((4)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snprintf_s_l)(char *__restrict buf, size_t bufsize, size_t buflen, char const *__restrict format, locale_t locale, ...);
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vprintf_l)(char const *__restrict format, locale_t locale, va_list args) THROWS(...);
INTDEF ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vprintf_p)(char const *__restrict format, va_list args) THROWS(...);
INTDEF ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vprintf_p_l)(char const *__restrict format, locale_t locale, va_list args) THROWS(...);
INTDEF ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__printf_l)(char const *__restrict format, locale_t locale, ...) THROWS(...);
INTDEF ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__printf_s_l)(char const *__restrict format, locale_t locale, ...) THROWS(...);
INTDEF ATTR_LIBC_PRINTF_P(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__printf_p)(char const *__restrict format, ...) THROWS(...);
INTDEF ATTR_LIBC_PRINTF_P(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__printf_p_l)(char const *__restrict format, locale_t locale, ...) THROWS(...);
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vfprintf_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, va_list args) THROWS(...);
INTDEF ATTR_LIBC_PRINTF_P(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vfprintf_p)(FILE *__restrict stream, char const *__restrict format, va_list args) THROWS(...);
INTDEF ATTR_LIBC_PRINTF_P(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBCCALL libc__vfprintf_p_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, va_list args) THROWS(...);
INTDEF ATTR_LIBC_PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__fprintf_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, ...) THROWS(...);
INTDEF ATTR_LIBC_PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__fprintf_s_l)(FILE *__restrict stream, char const *__restrict format, locale_t locale, ...) THROWS(...);
INTDEF ATTR_LIBC_PRINTF_P(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__fprintf_p)(FILE *__restrict stream, char const *__restrict format, ...) THROWS(...);
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_RPC(LIBCCALL libc_fopen_s)(FILE **pstream, char const *filename, char const *modes);
INTDEF NONNULL((1, 2, 3, 4)) errno_t NOTHROW_RPC(LIBCCALL libc_freopen_s)(FILE **pstream, char const *filename, char const *modes, FILE *oldstream);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_tmpnam_s)(char *__restrict buf, rsize_t bufsize);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_clearerr_s)(FILE *__restrict stream);
INTDEF NONNULL((1)) errno_t NOTHROW_RPC(LIBCCALL libc_tmpfile_s)(FILE **pstream);
INTDEF WUNUSED NONNULL((1, 5)) size_t NOTHROW_RPC(LIBCCALL libc_fread_s)(void *__restrict buf, size_t bufsize, size_t elemsize, size_t elemcount, FILE *__restrict stream);
INTDEF ATTR_LIBC_PRINTF(4, 0) NONNULL((4)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_vsnprintf_s)(char *__restrict buf, size_t bufsize, size_t buflen, char const *__restrict format, va_list args);
INTDEF ATTR_COLD void (LIBDCALL libd__wperror)(char16_t const *__restrict message) THROWS(...);
INTDEF ATTR_COLD void (LIBKCALL libc__wperror)(char32_t const *__restrict message) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t (LIBCCALL libc__fread_nolock_s)(void *__restrict buf, size_t bufsize, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_STDIO_H */
