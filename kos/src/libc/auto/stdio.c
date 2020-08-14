/* HASH CRC-32:0xdeaeb4f1 */
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
#ifndef GUARD_LIBC_AUTO_STDIO_C
#define GUARD_LIBC_AUTO_STDIO_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/stdio.h"
#include "format-printer.h"
#include "../user/stdlib.h"
#include "../user/string.h"
#include "unicode.h"
#include "../user/unistd.h"

DECL_BEGIN

#include "../libc/globals.h"
#ifndef __KERNEL__
#include <asm/crt/stdio.h>
/* Alias for `setvbuf(STREAM, buf, _IOFBF, BUFSIZ)' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.utility") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc_setbuf)(FILE *__restrict stream,
                                  char *buf) {
	libc_setvbuf(stream, buf,
	        buf ? ___IOFBF : ___IONBF,
	        buf ? __BUFSIZ : 0);
}
#include <local/stdstreams.h>
/* Alias for `fgetc(stdin)' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.getc") int
(LIBCCALL libc_getchar)(void) THROWS(...) {
	return libc_fgetc(stdin);
}
#include <local/stdstreams.h>
/* Alias for `fputc(CH, stdout)' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.putc") int
(LIBCCALL libc_putchar)(int ch) THROWS(...) {
	return libc_fputc(ch, stdout);
}
#include <hybrid/typecore.h>
#include <parts/errno.h>
/* Read up to `BUFSIZE - 1' bytes of data from `STREAM', storing them into `BUF' stopped when
 * the buffer is full or a line-feed was read (in this case, the line-feed is also written to `BUF')
 * Afterwards, append a trailing NUL-character and re-return `BUF', or return `NULL' if an error occurred. */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.read") WUNUSED NONNULL((1, 3)) char *
(LIBCCALL libc_fgets)(char *__restrict buf,
                      __STDC_INT_AS_SIZE_T bufsize,
                      FILE *__restrict stream) THROWS(...) {
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
#ifdef ERANGE
		__libc_seterrno(ERANGE);
#endif /* ERANGE */
		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		int ch = libc_fgetc(stream);
		if (ch == EOF) {
			if (n == 0 || libc_ferror(stream))
				return NULL;
			break;
		}
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = '\n';
			ch = libc_fgetc(stream);
			if (ch == EOF) {
				if (n == 0 || libc_ferror(stream))
					return NULL;
				break;
			}
			if (ch == '\r')
				continue;
			libc_ungetc(ch, stream);
			break;
		}
		buf[n] = (char)ch;
		if (ch == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}
/* Print a given string `STR' to `STREAM'. This is identical to:
 * >> fwrite(str, sizeof(char), strlen(str), stream); */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.write") NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(LIBCCALL libc_fputs)(char const *__restrict str,
                      FILE *__restrict stream) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	result = libc_fwrite(str,
	                sizeof(char),
	                libc_strlen(str),
	                stream);
	return result;
}
#include <local/stdstreams.h>
/* Print a given string `STR', followed by a line-feed to `STDOUT' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.write") NONNULL((1)) __STDC_INT_AS_SSIZE_T
(LIBCCALL libc_puts)(char const *__restrict string) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result, temp;
	result = libc_fputs(string, stdout);
	if (result >= 0) {
		temp = libc_fputc('\n', stdout);
		if (temp <= 0)
			result = temp;
		else
			result += temp;
	}
	return result;
}
#include <local/stdstreams.h>
#include <parts/errno.h>
/* Print a given `MESSAGE' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
INTERN ATTR_SECTION(".text.crt.errno.utility") void
NOTHROW_RPC(LIBCCALL libc_perror)(char const *message) {
	char const *enodesc;
	enodesc = libc_strerror(__libc_geterrno());
	if (message) {
		libc_fprintf(stderr, "%s: %s\n",
		        message, enodesc);
	} else {
		libc_fprintf(stderr, "%s\n",
		        enodesc);
	}
}
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.printf") ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(LIBCCALL libc_vfprintf)(FILE *__restrict stream,
                         char const *__restrict format,
                         va_list args) THROWS(...) {
	return (__STDC_INT_AS_SSIZE_T)libc_format_vprintf(&libc_file_printer, stream, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.write.printf") ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(VLIBDCALL libd_fprintf)(FILE *__restrict stream,
                         char const *__restrict format,
                         ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfprintf(stream, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.printf") ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(VLIBCCALL libc_fprintf)(FILE *__restrict stream,
                         char const *__restrict format,
                         ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfprintf(stream, format, args);
	va_end(args);
	return result;
}
#include <local/stdstreams.h>
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.printf") ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
(LIBCCALL libc_vprintf)(char const *__restrict format,
                        va_list args) THROWS(...) {
	return libc_vfprintf(stdout, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.write.printf") ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T
(VLIBDCALL libd_printf)(char const *__restrict format,
                        ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vprintf(format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.printf") ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T
(VLIBCCALL libc_printf)(char const *__restrict format,
                        ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vprintf(format, args);
	va_end(args);
	return result;
}
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_SIZE_T__ != __SIZEOF_INT__
__LOCAL_LIBC(vfscanf_getc) ssize_t
(__FORMATPRINTER_CC vfscanf_getc)(void *arg) {
	return (ssize_t)libc_fgetc((FILE *)arg);
}
#endif /* !__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_SIZE_T__ != __SIZEOF_INT__ */
__LOCAL_LIBC(vfscanf_ungetc) ssize_t
(__FORMATPRINTER_CC vfscanf_ungetc)(void *arg, char32_t ch) {
	return ungetc((int)(unsigned int)ch, (FILE *)arg);
}
__NAMESPACE_LOCAL_END
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBCCALL libc_vfscanf)(FILE *__restrict stream,
                        char const *__restrict format,
                        va_list args) THROWS(...) {
#if defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_SIZE_T__ == __SIZEOF_INT__
	return libc_format_vscanf((pformatgetc)(void *)&libc_fgetc,
	                     &__NAMESPACE_LOCAL_SYM vfscanf_ungetc,
	                     (void *)stream,
	                     format, args);
#else /* __LIBCCALL_IS_FORMATPRINTER_CC && __SIZEOF_SIZE_T__ == __SIZEOF_INT__ */
	return libc_format_vscanf(&__NAMESPACE_LOCAL_SYM vfscanf_getc,
	                     &__NAMESPACE_LOCAL_SYM vfscanf_ungetc,
	                     (void *)stream,
	                     format, args);
#endif /* !__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_SIZE_T__ != __SIZEOF_INT__ */
}
#include <local/stdstreams.h>
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBCCALL libc_vscanf)(char const *__restrict format,
                       va_list args) THROWS(...) {
	return libc_vfscanf(stdin, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_fscanf)(FILE *__restrict stream,
                        char const *__restrict format,
                        ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfscanf(stream, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBCCALL libc_fscanf)(FILE *__restrict stream,
                        char const *__restrict format,
                        ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfscanf(stream, format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_scanf)(char const *__restrict format,
                       ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vscanf(format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBCCALL libc_scanf)(char const *__restrict format,
                       ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vscanf(format, args);
	va_end(args);
	return result;
}
#include <local/stdstreams.h>
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.read") WUNUSED ATTR_DEPRECATED("No buffer size checks (use `fgets\' instead)") NONNULL((1)) char *
(LIBCCALL libc_gets)(char *__restrict buf) THROWS(...) {
	return libc_fgets(buf, INT_MAX, stdin);
}
#include <asm/crt/stdio.h>
#include <hybrid/typecore.h>
#include <bits/format-printer.h>
#if __SIZEOF_CHAR__ == 1
#ifndef ____vsscanf_getc_defined
#define ____vsscanf_getc_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsscanf_getc) ssize_t
(FORMATPRINTER_CC vsscanf_getc)(void *arg) {
	char32_t result = libc_unicode_readutf8((char const **)arg);
	return result ? result : __EOF;
}
__LOCAL_LIBC(vsscanf_ungetc) ssize_t
(FORMATPRINTER_CC vsscanf_ungetc)(void *arg, char32_t UNUSED(ch)) {
	libc_unicode_readutf8_rev((char const **)arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsscanf_getc_defined */

#elif __SIZEOF_CHAR__ == 2
#ifndef ____vsc16scanf_getc_defined
#define ____vsc16scanf_getc_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsc16scanf_getc) ssize_t
(FORMATPRINTER_CC vsc16scanf_getc)(void *arg) {
	char32_t result = unicode_readutf16((char16_t const **)arg);
	return result ? result : __EOF;
}
__LOCAL_LIBC(vsc16scanf_ungetc) ssize_t
(FORMATPRINTER_CC vsc16scanf_ungetc)(void *arg, char32_t UNUSED(ch)) {
	unicode_readutf16_rev((char16_t const **)arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsc16scanf_getc_defined */

#else /* ... */
#ifndef ____vsc32scanf_getc_defined
#define ____vsc32scanf_getc_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsc32scanf_getc) ssize_t
(FORMATPRINTER_CC vsc32scanf_getc)(void *arg) {
	char32_t result = **(char32_t const **)arg;
	if (!result)
		return __EOF;
	++*(char32_t const **)arg;
	return result;
}
__LOCAL_LIBC(vsc32scanf_ungetc) ssize_t
(FORMATPRINTER_CC vsc32scanf_ungetc)(void *arg, char32_t UNUSED(ch)) {
	--*(char32_t const **)arg;
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsc32scanf_getc_defined */

#endif /* !... */
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_SECTION(".text.crt.unicode.static.format.scanf") WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc_vsscanf)(char const *__restrict input,
                                   char const *__restrict format,
                                   va_list args) {
	char const *input_pointer = input;

	return libc_format_vscanf(&__NAMESPACE_LOCAL_SYM vsscanf_getc,
	                     &__NAMESPACE_LOCAL_SYM vsscanf_ungetc,
	                     (void *)&input_pointer, format, args);









}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.scanf") ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd_sscanf)(char const *__restrict input,
                                   char const *__restrict format,
                                   ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vsscanf(input, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_SECTION(".text.crt.unicode.static.format.scanf") ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc_sscanf)(char const *__restrict input,
                                   char const *__restrict format,
                                   ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vsscanf(input, format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
INTERN ATTR_SECTION(".text.crt.unicode.static.format.printf") ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc_vsprintf)(char *__restrict dest,
                                    char const *__restrict format,
                                    va_list args) {
	__STDC_INT_AS_SSIZE_T result;
	char *dest_pointer = dest;
	result = (__STDC_INT_AS_SSIZE_T)libc_format_vprintf(&libc_format_sprintf_printer,
	                                               (void *)&dest_pointer,
	                                               format, args);
	if (result >= 0)
		*dest_pointer = '\0';
	return result;
}
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd_sprintf)(char *__restrict buf,
                                    char const *__restrict format,
                                    ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vsprintf(buf, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
INTERN ATTR_SECTION(".text.crt.unicode.static.format.printf") ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc_sprintf)(char *__restrict buf,
                                    char const *__restrict format,
                                    ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vsprintf(buf, format, args);
	va_end(args);
	return result;
}
#ifndef ____format_snprintf_data_defined
#define ____format_snprintf_data_defined 1
struct __format_snprintf_data {
	char         *__sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
	__SIZE_TYPE__ __sd_bufsiz; /* Remaining buffer size. */
};
#endif /* !____format_snprintf_data_defined */
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
INTERN ATTR_SECTION(".text.crt.unicode.static.format.printf") ATTR_LIBC_PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc_vsnprintf)(char *__restrict buf,
                                     size_t buflen,
                                     char const *__restrict format,
                                     va_list args) {
	struct __format_snprintf_data data;
	__STDC_INT_AS_SSIZE_T result;
	data.__sd_buffer = buf;
	data.__sd_bufsiz = buflen;
	result = (__STDC_INT_AS_SSIZE_T)libc_format_vprintf(&libc_format_snprintf_printer,
	                                               (void *)&data, format, args);
	if (result >= 0 && data.__sd_bufsiz != 0)
		*data.__sd_buffer = '\0';
	return result;
}
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd_snprintf)(char *__restrict buf,
                                     size_t buflen,
                                     char const *__restrict format,
                                     ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vsnprintf(buf, buflen, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
INTERN ATTR_SECTION(".text.crt.unicode.static.format.printf") ATTR_LIBC_PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc_snprintf)(char *__restrict buf,
                                     size_t buflen,
                                     char const *__restrict format,
                                     ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vsnprintf(buf, buflen, format, args);
	va_end(args);
	return result;
}
#ifndef __KERNEL__
#include <hybrid/typecore.h>
#include <hybrid/host.h>
#include <bits/format-printer.h>
#if !defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_INT__ != __SIZEOF_POINTER__
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vdprintf_printer) __ssize_t
(__FORMATPRINTER_CC __vdprintf_printer)(void *__arg, char const *__restrict __data, __size_t __datalen) {
	return (__ssize_t)libc_write((int)(unsigned int)(__UINTPTR_TYPE__)__arg, __data, __datalen);
}
__NAMESPACE_LOCAL_END
#endif /* !__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_INT__ != __SIZEOF_POINTER__ */
INTERN ATTR_SECTION(".text.crt.io.write") ATTR_LIBC_PRINTF(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(LIBCCALL libc_vdprintf)(fd_t fd,
                                    char const *__restrict format,
                                    va_list args) {
#if !defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_INT__ != __SIZEOF_POINTER__
	return libc_format_vprintf(&__NAMESPACE_LOCAL_SYM __vdprintf_printer,
	                      (void *)(__UINTPTR_TYPE__)(unsigned int)fd,
	                      format, args);
#else /* !__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_INT__ != __SIZEOF_POINTER__ */
	return libc_format_vprintf((pformatprinter)(void *)&libc_write,
	                      (void *)(__UINTPTR_TYPE__)(unsigned int)fd,
	                      format, args);
#endif /* __LIBCCALL_IS_FORMATPRINTER_CC && __SIZEOF_INT__ == __SIZEOF_POINTER__ */
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.io.write") ATTR_LIBC_PRINTF(2, 3) NONNULL((2)) __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(VLIBDCALL libd_dprintf)(fd_t fd,
                                    char const *__restrict format,
                                    ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vdprintf(fd, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.io.write") ATTR_LIBC_PRINTF(2, 3) NONNULL((2)) __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(VLIBCCALL libc_dprintf)(fd_t fd,
                                    char const *__restrict format,
                                    ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vdprintf(fd, format, args);
	va_end(args);
	return result;
}
#include <asm/crt/stdio.h>
/* Specify the location and size for the buffer to-be used by `STREAM' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.utility") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc_setbuffer)(FILE *__restrict stream,
                                     char *buf,
                                     size_t bufsize) {
	libc_setvbuf(stream,
	        buf,
	        buf ? ___IOFBF : ___IONBF,
	        buf ? bufsize : (size_t)0);
}
/* Change the given `STREAM' to become line-buffered */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.utility") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc_setlinebuf)(FILE *__restrict stream) {
	libc_setvbuf(stream, NULL, _IOLBF, 0);
}
#include <asm/crt/stdio.h>
#include <hybrid/__assert.h>
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.read") WUNUSED NONNULL((1, 2, 4)) ssize_t
(LIBCCALL libc_getdelim)(char **__restrict lineptr,
                         size_t *__restrict pcount,
                         int delimiter,
                         FILE *__restrict stream) THROWS(...) {
	int ch;
	char *buffer;
	size_t bufsize, result = 0;
	buffer  = *lineptr;
	bufsize = buffer ? *pcount : 0;
	for (;;) {
		if (result + 1 >= bufsize) {
			/* Allocate more memory. */
			size_t new_bufsize = bufsize * 2;
			if (new_bufsize <= result + 1)
				new_bufsize = 16;
			__hybrid_assert(new_bufsize > result + 1);
			buffer = (char *)libc_realloc(buffer,
			                         new_bufsize *
			                         sizeof(char));
			if unlikely(!buffer)
				return -1;
			bufsize  = new_bufsize;
			*lineptr = buffer;
			*pcount  = bufsize;
		}
		ch = libc_fgetc(stream);
		if (ch == EOF)
			break; /* EOF */
		buffer[result++] = (char)ch;
		if (ch == delimiter)
			break; /* Delimiter reached */
		/* Special case for line-delimiter. */
		if (delimiter == '\n' && ch == '\r') {
			/* Deal with '\r\n', as well as '\r' */
			ch = libc_fgetc(stream);
			if (ch != EOF && ch != '\n')
				libc_ungetc(ch, stream);
			/* Unify linefeeds (to use POSIX notation) */
			buffer[result - 1] = '\n';
			break;
		}
	}
	/* NUL-Terminate the buffer. */
	buffer[result] = '\0';
	return result;
}
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.read") WUNUSED NONNULL((1, 2, 3)) ssize_t
(LIBCCALL libc_getline)(char **__restrict lineptr,
                        size_t *__restrict pcount,
                        FILE *__restrict stream) THROWS(...) {
	return libc_getdelim(lineptr, pcount, '\n', stream);
}
#include <local/stdstreams.h>
/* Same as `getchar()', but performs I/O without acquiring a lock to `stdin' */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.getc") int
(LIBCCALL libc_getchar_unlocked)(void) THROWS(...) {
	return libc_fgetc_unlocked(stdin);
}
#include <local/stdstreams.h>
/* Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.putc") int
(LIBCCALL libc_putchar_unlocked)(int ch) THROWS(...) {
	return libc_fputc_unlocked(ch, stdout);
}
#include <asm/crt/stdio.h>
/* Similar to `getc()', but read 2 bytes */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.getc") NONNULL((1)) int
(LIBCCALL libc_getw)(FILE *__restrict stream) THROWS(...) {
	u16 result;
	return libc_fread(&result, sizeof(result), 1, stream)
	       ? (int)result
	       : (int)EOF;
}
#include <asm/crt/stdio.h>
/* Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.putc") NONNULL((2)) int
(LIBCCALL libc_putw)(int w,
                     FILE *__restrict stream) THROWS(...) {
	u16 c = (u16)w;
	return libc_fwrite(&c, sizeof(c), 1, stream)
	       ? w
	       : EOF;
}
#include <hybrid/typecore.h>
#include <asm/crt/stdio.h>
#include <parts/errno.h>
/* Same as `fgets()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.read") WUNUSED NONNULL((1, 3)) char *
(LIBCCALL libc_fgets_unlocked)(char *__restrict buf,
                               __STDC_INT_AS_SIZE_T bufsize,
                               FILE *__restrict stream) THROWS(...) {
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
#ifdef ERANGE
		__libc_seterrno(ERANGE);
#endif /* ERANGE */
		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		int ch = libc_fgetc_unlocked(stream);
		if (ch == EOF) {
			if (n == 0 || libc_ferror(stream))
				return NULL;
			break;
		}
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = '\n';
			ch = libc_fgetc_unlocked(stream);
			if (ch == EOF) {
				if (n == 0 || libc_ferror(stream))
					return NULL;
				break;
			}
			if (ch == '\r')
				continue;
			libc_ungetc_unlocked(ch, stream);
			break;
		}
		buf[n] = (char)ch;
		if (ch == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}
/* Same as `fputs()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.write") NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBCCALL libc_fputs_unlocked)(char const *__restrict string,
                               FILE *__restrict stream) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	result = libc_fwrite_unlocked(string,
	                         sizeof(char),
	                         libc_strlen(string),
	                         stream);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.obstack") ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(VLIBDCALL libd_obstack_printf)(struct obstack *__restrict obstack_,
                                           char const *__restrict format,
                                           ...) {
	int result;
	va_list args;
	va_start(args, format);
	result = libc_obstack_vprintf(obstack_, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.obstack") ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(VLIBCCALL libc_obstack_printf)(struct obstack *__restrict obstack_,
                                           char const *__restrict format,
                                           ...) {
	int result;
	va_list args;
	va_start(args, format);
	result = libc_obstack_vprintf(obstack_, format, args);
	va_end(args);
	return result;
}
#include <hybrid/typecore.h>
#include <hybrid/__assert.h>
#ifndef __format_aprintf_data_defined
#define __format_aprintf_data_defined 1
struct format_aprintf_data {
	char         *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owend] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};
#endif /* !__format_aprintf_data_defined */
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
INTERN ATTR_SECTION(".text.crt.heap.strdup") WUNUSED ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc_vasprintf)(char **__restrict pstr,
                                     char const *__restrict format,
                                     va_list args) {
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
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
INTERN ATTR_SECTION(".text.crt.dos.heap.strdup") WUNUSED ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd_asprintf)(char **__restrict pstr,
                                     char const *__restrict format,
                                     ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vasprintf(pstr, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
INTERN ATTR_SECTION(".text.crt.heap.strdup") WUNUSED ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc_asprintf)(char **__restrict pstr,
                                     char const *__restrict format,
                                     ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vasprintf(pstr, format, args);
	va_end(args);
	return result;
}
#include <asm/crt/stdio.h>
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.getc") NONNULL((1)) int
(LIBCCALL libc_getw_unlocked)(FILE *__restrict stream) THROWS(...) {
	u16 result;
	return libc_fread_unlocked(&result, sizeof(result), 1, stream)
	       ? (int)result
	       : (int)EOF;
}
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.putc") NONNULL((2)) int
(LIBCCALL libc_putw_unlocked)(int w,
                              FILE *__restrict stream) THROWS(...) {
	u16 c = (u16)w;
	return libc_fwrite_unlocked(&c, sizeof(c), 1, stream)
	       ? w
	       : EOF;
}
#include <asm/crt/stdio.h>
#include <hybrid/__assert.h>
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.read") WUNUSED NONNULL((1, 2, 4)) ssize_t
(LIBCCALL libc_getdelim_unlocked)(char **__restrict lineptr,
                                  size_t *__restrict pcount,
                                  int delimiter,
                                  FILE *__restrict stream) THROWS(...) {
	int ch;
	char *buffer;
	size_t bufsize, result = 0;
	buffer  = *lineptr;
	bufsize = buffer ? *pcount : 0;
	for (;;) {
		if (result + 1 >= bufsize) {
			/* Allocate more memory. */
			size_t new_bufsize = bufsize * 2;
			if (new_bufsize <= result + 1)
				new_bufsize = 16;
			__hybrid_assert(new_bufsize > result + 1);
			buffer = (char *)libc_realloc(buffer,
			                         new_bufsize *
			                         sizeof(char));
			if unlikely(!buffer)
				goto err;
			bufsize  = new_bufsize;
			*lineptr = buffer;
			*pcount  = bufsize;
		}
		ch = libc_fgetc_unlocked(stream);
		if (ch == EOF)
			break; /* EOF */
		buffer[result++] = (char)ch;
		if (ch == delimiter)
			break; /* Delimiter reached */
		/* Special case for line-delimiter. */
		if (delimiter == '\n' && ch == '\r') {
			/* Deal with '\r\n', as well as '\r' */
			ch = libc_fgetc_unlocked(stream);
			if (ch != EOF && ch != '\n')
				libc_ungetc_unlocked(ch, stream);
			/* Unify linefeeds (to use POSIX notation) */
			buffer[result - 1] = '\n';
			break;
		}
	}
	/* NUL-Terminate the buffer. */
	buffer[result] = '\0';
	return result;
err:
	return -1;
}
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.read") WUNUSED NONNULL((1, 2, 3)) ssize_t
(LIBCCALL libc_getline_unlocked)(char **__restrict lineptr,
                                 size_t *__restrict pcount,
                                 FILE *__restrict stream) THROWS(...) {
	return libc_getdelim_unlocked(lineptr, pcount, '\n', stream);
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.write") NONNULL((1)) __STDC_INT_AS_SSIZE_T
(LIBCCALL libc_puts_unlocked)(char const *__restrict string) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result, temp;
	result = libc_fputs_unlocked(string, stdout);
	if (result >= 0) {
		temp = libc_fputc_unlocked('\n', stdout);
		if (temp <= 0)
			result = temp;
		else
			result += temp;
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.printf") ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(LIBCCALL libc_vfprintf_unlocked)(FILE *__restrict stream,
                                  char const *__restrict format,
                                  va_list args) THROWS(...) {
	return (__STDC_INT_AS_SSIZE_T)libc_format_vprintf(&libc_file_printer_unlocked, stream, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.write.printf") ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(VLIBDCALL libd_fprintf_unlocked)(FILE *__restrict stream,
                                  char const *__restrict format,
                                  ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfprintf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.printf") ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(VLIBCCALL libc_fprintf_unlocked)(FILE *__restrict stream,
                                  char const *__restrict format,
                                  ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfprintf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.printf") ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
(LIBCCALL libc_vprintf_unlocked)(char const *__restrict format,
                                 va_list args) THROWS(...) {
	return libc_vfprintf_unlocked(stdout, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.write.printf") ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T
(VLIBDCALL libd_printf_unlocked)(char const *__restrict format,
                                 ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vprintf_unlocked(format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.printf") ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T
(VLIBCCALL libc_printf_unlocked)(char const *__restrict format,
                                 ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vprintf_unlocked(format, args);
	va_end(args);
	return result;
}
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_SIZE_T__ != __SIZEOF_INT__
__LOCAL_LIBC(vfscanf_getc_unlocked) ssize_t
(__FORMATPRINTER_CC vfscanf_getc_unlocked)(void *arg) {
	return (ssize_t)libc_fgetc_unlocked((FILE *)arg);
}
#endif /* !__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_SIZE_T__ != __SIZEOF_INT__ */
__LOCAL_LIBC(vfscanf_ungetc_unlocked) ssize_t
(__FORMATPRINTER_CC vfscanf_ungetc_unlocked)(void *arg, char32_t ch) {
	return ungetc_unlocked((int)(unsigned int)ch, (FILE *)arg);
}
__NAMESPACE_LOCAL_END
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBCCALL libc_vfscanf_unlocked)(FILE *__restrict stream,
                                 char const *__restrict format,
                                 va_list args) THROWS(...) {
#if defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_SIZE_T__ == __SIZEOF_INT__
	return libc_format_vscanf((pformatgetc)(void *)&libc_fgetc_unlocked,
	                     &__NAMESPACE_LOCAL_SYM vfscanf_ungetc_unlocked,
	                     (void *)stream,
	                     format, args);
#else /* __LIBCCALL_IS_FORMATPRINTER_CC && __SIZEOF_SIZE_T__ == __SIZEOF_INT__ */
	return libc_format_vscanf(&__NAMESPACE_LOCAL_SYM vfscanf_getc_unlocked,
	                     &__NAMESPACE_LOCAL_SYM vfscanf_ungetc_unlocked,
	                     (void *)stream,
	                     format, args);
#endif /* !__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_SIZE_T__ != __SIZEOF_INT__ */
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBCCALL libc_vscanf_unlocked)(char const *__restrict format,
                                va_list args) THROWS(...) {
	return libc_vfscanf_unlocked(stdin, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_fscanf_unlocked)(FILE *__restrict stream,
                                 char const *__restrict format,
                                 ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfscanf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBCCALL libc_fscanf_unlocked)(FILE *__restrict stream,
                                 char const *__restrict format,
                                 ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfscanf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_scanf_unlocked)(char const *__restrict format,
                                ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vscanf_unlocked(format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBCCALL libc_scanf_unlocked)(char const *__restrict format,
                                ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vscanf_unlocked(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") WUNUSED NONNULL((1, 2)) FILE *
NOTHROW_RPC(LIBCCALL libc__fsopen)(char const *filename,
                                   char const *modes,
                                   int sflag) {
	(void)sflag;
	return libc_fopen(filename, modes);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBCCALL libc__vscanf_l)(char const *__restrict format,
                          locale_t locale,
                          va_list args) THROWS(...) {
	(void)locale;
	return libc_vscanf(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBCCALL libc__vfscanf_l)(FILE *__restrict stream,
                           char const *__restrict format,
                           locale_t locale,
                           va_list args) THROWS(...) {
	(void)locale;
	return libc_vfscanf(stream, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.scanf") WUNUSED ATTR_LIBC_SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc__vsscanf_l)(char const *__restrict input,
                                      char const *__restrict format,
                                      locale_t locale,
                                      va_list args) {
	(void)locale;
	return libc_vsscanf(input, format, args);
}
#include <asm/crt/stdio.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
struct __vsnscanf_data {
	char const *__ptr;
	char const *__end;
};
__LOCAL_LIBC(vsnscanf_getc) __SSIZE_TYPE__
(__FORMATPRINTER_CC __vsnscanf_getc)(void *__arg) {
	__CHAR32_TYPE__ __result;
	__result = libc_unicode_readutf8_n(&((struct __vsnscanf_data *)__arg)->__ptr,
	                              ((struct __vsnscanf_data *)__arg)->__end);
	return __result ? __result : __EOF;
}
__LOCAL_LIBC(vsnscanf_ungetc) __SSIZE_TYPE__
(__FORMATPRINTER_CC __vsnscanf_ungetc)(void *__arg, __CHAR32_TYPE__ __UNUSED(__ch)) {
	libc_unicode_readutf8_rev(&((struct __vsnscanf_data *)__arg)->__ptr);
	return 0;
}
__NAMESPACE_LOCAL_END
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.scanf") WUNUSED ATTR_LIBC_SCANF(3, 4) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc__vsnscanf)(char const *__restrict input,
                                     size_t inputlen,
                                     char const *__restrict format,
                                     va_list args) {
	struct __NAMESPACE_LOCAL_SYM __vsnscanf_data data;
	data.__ptr = input;
	data.__end = input + inputlen;
	return libc_format_vscanf(&__NAMESPACE_LOCAL_SYM __vsnscanf_getc,
	                     &__NAMESPACE_LOCAL_SYM __vsnscanf_ungetc,
	                     (void *)&data, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.scanf") ATTR_LIBC_SCANF(3, 5) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc__vsnscanf_l)(char const *__restrict input,
                                       size_t inputlen,
                                       char const *__restrict format,
                                       locale_t locale,
                                       va_list args) {
	(void)locale;
	return libc__vsnscanf(input, inputlen, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") ATTR_LIBC_SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd__scanf_l)(char const *__restrict format,
                          locale_t locale,
                          ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vscanf_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") ATTR_LIBC_SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBCCALL libc__scanf_l)(char const *__restrict format,
                          locale_t locale,
                          ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vscanf_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") ATTR_LIBC_SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd__fscanf_l)(FILE *__restrict stream,
                           char const *__restrict format,
                           locale_t locale,
                           ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfscanf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") ATTR_LIBC_SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBCCALL libc__fscanf_l)(FILE *__restrict stream,
                           char const *__restrict format,
                           locale_t locale,
                           ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfscanf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.scanf") ATTR_LIBC_SCANF(3, 4) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__snscanf)(char const *__restrict input,
                                     size_t inputlen,
                                     char const *__restrict format,
                                     ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnscanf(input, inputlen, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.scanf") ATTR_LIBC_SCANF(3, 4) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc__snscanf)(char const *__restrict input,
                                     size_t inputlen,
                                     char const *__restrict format,
                                     ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnscanf(input, inputlen, format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.scanf") ATTR_LIBC_SCANF(3, 5) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__snscanf_l)(char const *__restrict input,
                                       size_t inputlen,
                                       char const *__restrict format,
                                       locale_t locale,
                                       ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnscanf_l(input, inputlen, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.scanf") ATTR_LIBC_SCANF(3, 5) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc__snscanf_l)(char const *__restrict input,
                                       size_t inputlen,
                                       char const *__restrict format,
                                       locale_t locale,
                                       ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnscanf_l(input, inputlen, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc__vsprintf_l)(char *__restrict buf,
                                       char const *__restrict format,
                                       locale_t locale,
                                       va_list args) {
	(void)locale;
	return libc_vsprintf(buf, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF_P(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc__vsprintf_p)(char *__restrict buf,
                                       size_t bufsize,
                                       char const *__restrict format,
                                       va_list args) {
	(void)buf;
	(void)bufsize;
	(void)format;
	(void)args;
	/* TODO */
	__COMPILER_IMPURE();
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF_P(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc__vsprintf_p_l)(char *__restrict buf,
                                         size_t bufsize,
                                         char const *__restrict format,
                                         locale_t locale,
                                         va_list args) {
	(void)locale;
	return libc__vsprintf_p(buf, bufsize, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__sprintf_l)(char *__restrict buf,
                                       char const *__restrict format,
                                       locale_t locale,
                                       ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsprintf_l(buf, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc__sprintf_l)(char *__restrict buf,
                                       char const *__restrict format,
                                       locale_t locale,
                                       ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsprintf_l(buf, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__sprintf_s_l)(char *__restrict buf,
                                         size_t bufsize,
                                         char const *__restrict format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnprintf_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc__sprintf_s_l)(char *__restrict buf,
                                         size_t bufsize,
                                         char const *__restrict format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnprintf_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF_P(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__sprintf_p)(char *__restrict buf,
                                       size_t bufsize,
                                       char const *__restrict format,
                                       ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsprintf_p(buf, bufsize, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF_P(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc__sprintf_p)(char *__restrict buf,
                                       size_t bufsize,
                                       char const *__restrict format,
                                       ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsprintf_p(buf, bufsize, format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF_P(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__sprintf_p_l)(char *__restrict buf,
                                         size_t bufsize,
                                         char const *__restrict format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsprintf_p_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF_P(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc__sprintf_p_l)(char *__restrict buf,
                                         size_t bufsize,
                                         char const *__restrict format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsprintf_p_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") WUNUSED ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc__vscprintf)(char const *__restrict format,
                                      va_list args) {
	return libc_vsnprintf(NULL, 0, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") WUNUSED ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__scprintf)(char const *__restrict format,
                                      ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vscprintf(format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") WUNUSED ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc__scprintf)(char const *__restrict format,
                                      ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vscprintf(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") WUNUSED ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc__vscprintf_l)(char const *__restrict format,
                                        locale_t locale,
                                        va_list args) {
	(void)locale;
	return libc__vscprintf(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") WUNUSED ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc__vscprintf_p)(char const *__restrict format,
                                        va_list args) {
	(void)format;
	(void)args;
	/* TODO */
	__COMPILER_IMPURE();
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") WUNUSED ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc__vscprintf_p_l)(char const *__restrict format,
                                          locale_t locale,
                                          va_list args) {
	(void)locale;
	return libc__vscprintf_p(format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") WUNUSED ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__scprintf_l)(char const *__restrict format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vscprintf_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") WUNUSED ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc__scprintf_l)(char const *__restrict format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vscprintf_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") WUNUSED ATTR_LIBC_PRINTF_P(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__scprintf_p)(char const *__restrict format,
                                        ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vscprintf_p(format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") WUNUSED ATTR_LIBC_PRINTF_P(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc__scprintf_p)(char const *__restrict format,
                                        ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vscprintf_p(format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") WUNUSED ATTR_LIBC_PRINTF_P(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__scprintf_p_l)(char const *__restrict format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vscprintf_p_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") WUNUSED ATTR_LIBC_PRINTF_P(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc__scprintf_p_l)(char const *__restrict format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vscprintf_p_l(format, locale, args);
	va_end(args);
	return result;
}
/* WARNING: This function returns the number of written character. - Not the required buffer size! */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc__vsnprintf)(char *__restrict buf,
                                      size_t bufsize,
                                      char const *__restrict format,
                                      va_list args) {
	__STDC_INT_AS_SIZE_T result;
	result = libc_vsnprintf(buf, bufsize, format, args);
	if (result > bufsize)
		result = bufsize;
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc__vsnprintf_l)(char *__restrict buf,
                                        size_t bufsize,
                                        char const *__restrict format,
                                        locale_t locale,
                                        va_list args) {
	(void)locale;
	return libc__vsnprintf(buf, bufsize, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF(4, 0) NONNULL((4)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc__vsnprintf_s)(char *__restrict buf,
                                        size_t bufsize,
                                        size_t buflen,
                                        char const *__restrict format,
                                        va_list args) {
	(void)buflen;
	return libc__vsnprintf(buf, bufsize, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(4, 0) NONNULL((4)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc__vsnprintf_s_l)(char *__restrict buf,
                                          size_t bufsize,
                                          size_t buflen,
                                          char const *__restrict format,
                                          locale_t locale,
                                          va_list args) {
	(void)buflen;
	(void)locale;
	return libc__vsnprintf(buf, bufsize, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__snprintf)(char *__restrict buf,
                                      size_t bufsize,
                                      char const *__restrict format,
                                      ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnprintf(buf, bufsize, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc__snprintf)(char *__restrict buf,
                                      size_t bufsize,
                                      char const *__restrict format,
                                      ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnprintf(buf, bufsize, format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__snprintf_l)(char *__restrict buf,
                                        size_t bufsize,
                                        char const *__restrict format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnprintf_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc__snprintf_l)(char *__restrict buf,
                                        size_t bufsize,
                                        char const *__restrict format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnprintf_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__snprintf_c)(char *__restrict buf,
                                        size_t bufsize,
                                        char const *__restrict format,
                                        ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnprintf(buf, bufsize, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc__snprintf_c)(char *__restrict buf,
                                        size_t bufsize,
                                        char const *__restrict format,
                                        ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnprintf(buf, bufsize, format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__snprintf_c_l)(char *__restrict buf,
                                          size_t bufsize,
                                          char const *__restrict format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnprintf_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc__snprintf_c_l)(char *__restrict buf,
                                          size_t bufsize,
                                          char const *__restrict format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnprintf_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF(4, 5) NONNULL((4)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__snprintf_s)(char *__restrict buf,
                                        size_t bufsize,
                                        size_t buflen,
                                        char const *__restrict format,
                                        ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnprintf_s(buf, bufsize, buflen, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF(4, 5) NONNULL((4)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc__snprintf_s)(char *__restrict buf,
                                        size_t bufsize,
                                        size_t buflen,
                                        char const *__restrict format,
                                        ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnprintf_s(buf, bufsize, buflen, format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(4, 6) NONNULL((4)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__snprintf_s_l)(char *__restrict buf,
                                          size_t bufsize,
                                          size_t buflen,
                                          char const *__restrict format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnprintf_s_l(buf, bufsize, buflen, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(4, 6) NONNULL((4)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc__snprintf_s_l)(char *__restrict buf,
                                          size_t bufsize,
                                          size_t buflen,
                                          char const *__restrict format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnprintf_s_l(buf, bufsize, buflen, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBCCALL libc__vprintf_l)(char const *__restrict format,
                           locale_t locale,
                           va_list args) THROWS(...) {
	(void)locale;
	return libc_vprintf(format, args);
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBCCALL libc__vprintf_p)(char const *__restrict format,
                           va_list args) THROWS(...) {
	return libc__vfprintf_p(stdout, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBCCALL libc__vprintf_p_l)(char const *__restrict format,
                             locale_t locale,
                             va_list args) THROWS(...) {
	(void)locale;
	return libc__vprintf_p(format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd__printf_l)(char const *__restrict format,
                           locale_t locale,
                           ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vprintf_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBCCALL libc__printf_l)(char const *__restrict format,
                           locale_t locale,
                           ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vprintf_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd__printf_s_l)(char const *__restrict format,
                             locale_t locale,
                             ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vprintf_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBCCALL libc__printf_s_l)(char const *__restrict format,
                             locale_t locale,
                             ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vprintf_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF_P(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd__printf_p)(char const *__restrict format,
                           ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vprintf_p(format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF_P(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBCCALL libc__printf_p)(char const *__restrict format,
                           ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vprintf_p(format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF_P(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd__printf_p_l)(char const *__restrict format,
                             locale_t locale,
                             ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vprintf_p_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF_P(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBCCALL libc__printf_p_l)(char const *__restrict format,
                             locale_t locale,
                             ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vprintf_p_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBCCALL libc__vfprintf_l)(FILE *__restrict stream,
                            char const *__restrict format,
                            locale_t locale,
                            va_list args) THROWS(...) {
	(void)locale;
	return libc_vfprintf(stream, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF_P(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBCCALL libc__vfprintf_p)(FILE *__restrict stream,
                            char const *__restrict format,
                            va_list args) THROWS(...) {
	(void)stream;
	(void)format;
	(void)args;
	/* TODO */
	__COMPILER_IMPURE();
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF_P(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBCCALL libc__vfprintf_p_l)(FILE *__restrict stream,
                              char const *__restrict format,
                              locale_t locale,
                              va_list args) THROWS(...) {
	(void)locale;
	return libc__vfprintf_p(stream, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd__fprintf_l)(FILE *__restrict stream,
                            char const *__restrict format,
                            locale_t locale,
                            ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfprintf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBCCALL libc__fprintf_l)(FILE *__restrict stream,
                            char const *__restrict format,
                            locale_t locale,
                            ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfprintf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd__fprintf_s_l)(FILE *__restrict stream,
                              char const *__restrict format,
                              locale_t locale,
                              ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfprintf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBCCALL libc__fprintf_s_l)(FILE *__restrict stream,
                              char const *__restrict format,
                              locale_t locale,
                              ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfprintf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF_P(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd__fprintf_p)(FILE *__restrict stream,
                            char const *__restrict format,
                            ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vfprintf_p(stream, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF_P(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBCCALL libc__fprintf_p)(FILE *__restrict stream,
                            char const *__restrict format,
                            ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vfprintf_p(stream, format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF_P(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd__fprintf_p_l)(FILE *__restrict stream,
                              char const *__restrict format,
                              locale_t locale,
                              ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfprintf_p_l(stream, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF_P(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBCCALL libc__fprintf_p_l)(FILE *__restrict stream,
                              char const *__restrict format,
                              locale_t locale,
                              ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfprintf_p_l(stream, format, locale, args);
	va_end(args);
	return result;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") NONNULL((1, 2, 3)) errno_t
NOTHROW_RPC(LIBCCALL libc_fopen_s)(FILE **pstream,
                                   char const *filename,
                                   char const *modes) {
	FILE *result;
	if unlikely(!pstream || !filename || !modes) {
#ifdef EINVAL
		return EINVAL;
#else /* EINVAL */
		return 1;
#endif /* !EINVAL */
	}
	result = libc_fopen64(filename, modes);
	if unlikely(!result) {
#ifdef ENOMEM
		return __libc_geterrno_or(ENOMEM);
#else /* ENOMEM */
		return 1;
#endif /* !ENOMEM */
	}
	*pstream = result;
	return EOK;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") NONNULL((1, 2, 3, 4)) errno_t
NOTHROW_RPC(LIBCCALL libc_freopen_s)(FILE **pstream,
                                     char const *filename,
                                     char const *modes,
                                     FILE *oldstream) {
	if unlikely(!pstream || !filename || !modes || !oldstream) {
#ifdef EINVAL
		return EINVAL;
#else /* EINVAL */
		return 1;
#endif /* !EINVAL */
	}
	oldstream = libc_freopen(filename, modes, oldstream);
	if unlikely(!oldstream) {
#ifdef __libc_geterrno
		return __libc_geterrno();
#else /* __libc_geterrno */
		return 1;
#endif /* !__libc_geterrno */
	}
	*pstream = oldstream;
	return EOK;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_tmpnam_s)(char *__restrict buf,
                                    rsize_t bufsize) {
	if unlikely(!buf) {
#ifdef EINVAL
		return EINVAL;
#else /* EINVAL */
		return 1;
#endif /* !EINVAL */
	}
	if unlikely(bufsize < L_tmpnam) {
#ifdef ERANGE
		return ERANGE; /* XXX: Is this what dos does? */
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	if unlikely(!libc_tmpnam(buf)) {
#ifdef __libc_geterrno
		return __libc_geterrno();
#else /* __libc_geterrno */
		return 1;
#endif /* !__libc_geterrno */
	}
	return EOK;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.utility") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_clearerr_s)(FILE *__restrict stream) {
	if (!stream) {
#ifdef EINVAL
		return EINVAL;
#else /* EINVAL */
		return 1;
#endif /* !EINVAL */
	}
	libc_clearerr(stream);
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") NONNULL((1)) errno_t
NOTHROW_RPC(LIBCCALL libc_tmpfile_s)(FILE **pstream) {
	if (!pstream) {
#ifdef EINVAL
		return EINVAL;
#else /* EINVAL */
		return 1;
#endif /* !EINVAL */
	}
	*pstream = libc_tmpfile64();
	if (!*pstream) {
#ifdef ENOMEM
		return __libc_geterrno_or(ENOMEM);
#else /* ENOMEM */
		return __libc_geterrno_or(1);
#endif /* !ENOMEM */
	}
	return 0;
}
#include <parts/errno.h>
#include <hybrid/__overflow.h>
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.read") WUNUSED NONNULL((1, 5)) size_t
NOTHROW_RPC(LIBCCALL libc_fread_s)(void *__restrict buf,
                                   size_t bufsize,
                                   size_t elemsize,
                                   size_t elemcount,
                                   FILE *__restrict stream) {
	size_t reqbuf;
	if (__hybrid_overflow_umul(elemsize, elemcount, &reqbuf) ||
	    reqbuf > bufsize) {
#ifdef ERANGE
		__libc_seterrno(ERANGE);
#endif /* ERANGE */
		return 0;
	}
	if unlikely(!stream || !buf) {
#ifdef EINVAL
		__libc_seterrno(EINVAL);
#endif /* EINVAL */
		return 0;
	}
	return libc_fread(buf, elemsize, elemcount, stream);
}
#include <local/stdstreams.h>
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.read") WUNUSED NONNULL((1)) char *
NOTHROW_RPC(LIBCCALL libc_gets_s)(char *__restrict buf,
                                  rsize_t bufsize) {
	if unlikely(!buf) {
#ifdef EINVAL
		__libc_seterrno(EINVAL);
#endif /* EINVAL */
		return NULL;
	}
	return libc_fgets(buf, (__STDC_INT_AS_SIZE_T)(unsigned int)bufsize, stdin);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.read") ATTR_LIBC_PRINTF(4, 0) NONNULL((4)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc_vsnprintf_s)(char *__restrict buf,
                                       size_t bufsize,
                                       size_t buflen,
                                       char const *__restrict format,
                                       va_list args) {
	return libc_vsnprintf(buf, buflen < bufsize ? buflen : bufsize, format, args);
}
#include <local/stdstreams.h>
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.errno.utility") ATTR_COLD void
(LIBDCALL libd__wperror)(char16_t const *__restrict message) THROWS(...) {
	char const *enodesc;
	enodesc = libc_strerror(__libc_geterrno());
	if (message) {

		libc_fprintf(stderr, "%I16s: %s\n", message, enodesc);



	} else {
		libc_fprintf(stderr, "%s\n",
		        enodesc);
	}
}
#include <local/stdstreams.h>
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.errno.utility") ATTR_COLD void
(LIBKCALL libc__wperror)(char32_t const *__restrict message) THROWS(...) {
	char const *enodesc;
	enodesc = libc_strerror(__libc_geterrno());
	if (message) {



		libc_fprintf(stderr, "%I32s: %s\n", message, enodesc);

	} else {
		libc_fprintf(stderr, "%s\n",
		        enodesc);
	}
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.read.read") WUNUSED NONNULL((1, 5)) size_t
(LIBCCALL libc__fread_nolock_s)(void *__restrict buf,
                                size_t bufsize,
                                size_t elemsize,
                                size_t elemcount,
                                FILE *__restrict stream) THROWS(...) {
	bufsize = elemsize ? bufsize / elemsize : 0;
	return libc_fread_unlocked(buf, elemsize,
	                      bufsize < elemcount
	                      ? bufsize
	                      : elemcount,
	                      stream);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(setbuf, libc_setbuf);
DEFINE_PUBLIC_ALIAS(getchar, libc_getchar);
DEFINE_PUBLIC_ALIAS(putchar, libc_putchar);
DEFINE_PUBLIC_ALIAS(fgets, libc_fgets);
DEFINE_PUBLIC_ALIAS(_IO_fputs, libc_fputs);
DEFINE_PUBLIC_ALIAS(fputs, libc_fputs);
DEFINE_PUBLIC_ALIAS(_IO_puts, libc_puts);
DEFINE_PUBLIC_ALIAS(puts, libc_puts);
DEFINE_PUBLIC_ALIAS(perror, libc_perror);
DEFINE_PUBLIC_ALIAS(_IO_vfprintf, libc_vfprintf);
DEFINE_PUBLIC_ALIAS(vfprintf, libc_vfprintf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_IO_fprintf, libd_fprintf);
DEFINE_PUBLIC_ALIAS(DOS$fprintf, libd_fprintf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_IO_fprintf, libc_fprintf);
DEFINE_PUBLIC_ALIAS(fprintf, libc_fprintf);
DEFINE_PUBLIC_ALIAS(vprintf, libc_vprintf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_IO_printf, libd_printf);
DEFINE_PUBLIC_ALIAS(DOS$printf_s, libd_printf);
DEFINE_PUBLIC_ALIAS(DOS$printf, libd_printf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_IO_printf, libc_printf);
DEFINE_PUBLIC_ALIAS(printf_s, libc_printf);
DEFINE_PUBLIC_ALIAS(printf, libc_printf);
DEFINE_PUBLIC_ALIAS(_IO_vfscanf, libc_vfscanf);
DEFINE_PUBLIC_ALIAS(__vfscanf, libc_vfscanf);
DEFINE_PUBLIC_ALIAS(vfscanf, libc_vfscanf);
DEFINE_PUBLIC_ALIAS(vscanf, libc_vscanf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$fscanf, libd_fscanf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(fscanf, libc_fscanf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$scanf, libd_scanf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(scanf, libc_scanf);
DEFINE_PUBLIC_ALIAS(_IO_gets, libc_gets);
DEFINE_PUBLIC_ALIAS(gets, libc_gets);
DEFINE_PUBLIC_ALIAS(__vsscanf, libc_vsscanf);
DEFINE_PUBLIC_ALIAS(vsscanf, libc_vsscanf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_IO_sscanf, libd_sscanf);
DEFINE_PUBLIC_ALIAS(DOS$sscanf, libd_sscanf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_IO_sscanf, libc_sscanf);
DEFINE_PUBLIC_ALIAS(sscanf, libc_sscanf);
DEFINE_PUBLIC_ALIAS(_IO_vsprintf, libc_vsprintf);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(vsprintf, libc_vsprintf);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_IO_sprintf, libd_sprintf);
DEFINE_PUBLIC_ALIAS(DOS$sprintf, libd_sprintf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_IO_sprintf, libc_sprintf);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(sprintf, libc_sprintf);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__vsnprintf, libc_vsnprintf);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(vsnprintf, libc_vsnprintf);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$snprintf, libd_snprintf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(snprintf, libc_snprintf);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(vdprintf, libc_vdprintf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$dprintf, libd_dprintf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(dprintf, libc_dprintf);
DEFINE_PUBLIC_ALIAS(_IO_setbuffer, libc_setbuffer);
DEFINE_PUBLIC_ALIAS(setbuffer, libc_setbuffer);
DEFINE_PUBLIC_ALIAS(setlinebuf, libc_setlinebuf);
DEFINE_PUBLIC_ALIAS(__getdelim, libc_getdelim);
DEFINE_PUBLIC_ALIAS(getdelim, libc_getdelim);
DEFINE_PUBLIC_ALIAS(getline, libc_getline);
DEFINE_PUBLIC_ALIAS(getchar_unlocked, libc_getchar_unlocked);
DEFINE_PUBLIC_ALIAS(putchar_unlocked, libc_putchar_unlocked);
DEFINE_PUBLIC_ALIAS(getw, libc_getw);
DEFINE_PUBLIC_ALIAS(putw, libc_putw);
DEFINE_PUBLIC_ALIAS(fgets_unlocked, libc_fgets_unlocked);
DEFINE_PUBLIC_ALIAS(fputs_unlocked, libc_fputs_unlocked);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$obstack_printf, libd_obstack_printf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(obstack_printf, libc_obstack_printf);
DEFINE_PUBLIC_ALIAS(vasprintf, libc_vasprintf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$__asprintf, libd_asprintf);
DEFINE_PUBLIC_ALIAS(DOS$asprintf, libd_asprintf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__asprintf, libc_asprintf);
DEFINE_PUBLIC_ALIAS(asprintf, libc_asprintf);
DEFINE_PUBLIC_ALIAS(getw_unlocked, libc_getw_unlocked);
DEFINE_PUBLIC_ALIAS(putw_unlocked, libc_putw_unlocked);
DEFINE_PUBLIC_ALIAS(getdelim_unlocked, libc_getdelim_unlocked);
DEFINE_PUBLIC_ALIAS(getline_unlocked, libc_getline_unlocked);
DEFINE_PUBLIC_ALIAS(puts_unlocked, libc_puts_unlocked);
DEFINE_PUBLIC_ALIAS(vfprintf_unlocked, libc_vfprintf_unlocked);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$fprintf_s, libd_fprintf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fprintf_unlocked, libd_fprintf_unlocked);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(fprintf_unlocked, libc_fprintf_unlocked);
DEFINE_PUBLIC_ALIAS(vprintf_unlocked, libc_vprintf_unlocked);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$printf_s, libd_printf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$printf_unlocked, libd_printf_unlocked);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(printf_unlocked, libc_printf_unlocked);
DEFINE_PUBLIC_ALIAS(vfscanf_unlocked, libc_vfscanf_unlocked);
DEFINE_PUBLIC_ALIAS(vscanf_unlocked, libc_vscanf_unlocked);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$fscanf_unlocked, libd_fscanf_unlocked);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(fscanf_unlocked, libc_fscanf_unlocked);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$scanf_unlocked, libd_scanf_unlocked);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(scanf_unlocked, libc_scanf_unlocked);
DEFINE_PUBLIC_ALIAS(_fsopen, libc__fsopen);
DEFINE_PUBLIC_ALIAS(_vscanf_s_l, libc__vscanf_l);
DEFINE_PUBLIC_ALIAS(_vscanf_l, libc__vscanf_l);
DEFINE_PUBLIC_ALIAS(_vfscanf_s_l, libc__vfscanf_l);
DEFINE_PUBLIC_ALIAS(_vfscanf_l, libc__vfscanf_l);
DEFINE_PUBLIC_ALIAS(_vsscanf_s_l, libc__vsscanf_l);
DEFINE_PUBLIC_ALIAS(_vsscanf_l, libc__vsscanf_l);
DEFINE_PUBLIC_ALIAS(_vsnscanf_s, libc__vsnscanf);
DEFINE_PUBLIC_ALIAS(_vsnscanf, libc__vsnscanf);
DEFINE_PUBLIC_ALIAS(_vsnscanf_s_l, libc__vsnscanf_l);
DEFINE_PUBLIC_ALIAS(_vsnscanf_l, libc__vsnscanf_l);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_scanf_s_l, libd__scanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_scanf_l, libd__scanf_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_scanf_s_l, libc__scanf_l);
DEFINE_PUBLIC_ALIAS(_scanf_l, libc__scanf_l);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_fscanf_s_l, libd__fscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_fscanf_l, libd__fscanf_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_fscanf_s_l, libc__fscanf_l);
DEFINE_PUBLIC_ALIAS(_fscanf_l, libc__fscanf_l);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_snscanf_s, libd__snscanf);
DEFINE_PUBLIC_ALIAS(DOS$_snscanf, libd__snscanf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_snscanf_s, libc__snscanf);
DEFINE_PUBLIC_ALIAS(_snscanf, libc__snscanf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_snscanf_s_l, libd__snscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_snscanf_l, libd__snscanf_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_snscanf_s_l, libc__snscanf_l);
DEFINE_PUBLIC_ALIAS(_snscanf_l, libc__snscanf_l);
DEFINE_PUBLIC_ALIAS(_vsprintf_l, libc__vsprintf_l);
DEFINE_PUBLIC_ALIAS(_vsprintf_p, libc__vsprintf_p);
DEFINE_PUBLIC_ALIAS(_vsprintf_p_l, libc__vsprintf_p_l);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_sprintf_l, libd__sprintf_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_sprintf_l, libc__sprintf_l);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_sprintf_s_l, libd__sprintf_s_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_sprintf_s_l, libc__sprintf_s_l);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_sprintf_p, libd__sprintf_p);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_sprintf_p, libc__sprintf_p);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_sprintf_p_l, libd__sprintf_p_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_sprintf_p_l, libc__sprintf_p_l);
DEFINE_PUBLIC_ALIAS(_vscprintf, libc__vscprintf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_scprintf, libd__scprintf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_scprintf, libc__scprintf);
DEFINE_PUBLIC_ALIAS(_vscprintf_l, libc__vscprintf_l);
DEFINE_PUBLIC_ALIAS(_vscprintf_p, libc__vscprintf_p);
DEFINE_PUBLIC_ALIAS(_vscprintf_p_l, libc__vscprintf_p_l);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_scprintf_l, libd__scprintf_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_scprintf_l, libc__scprintf_l);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_scprintf_p, libd__scprintf_p);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_scprintf_p, libc__scprintf_p);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_scprintf_p_l, libd__scprintf_p_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_scprintf_p_l, libc__scprintf_p_l);
DEFINE_PUBLIC_ALIAS(_vsnprintf, libc__vsnprintf);
DEFINE_PUBLIC_ALIAS(_vsprintf_s_l, libc__vsnprintf_l);
DEFINE_PUBLIC_ALIAS(_vsnprintf_l, libc__vsnprintf_l);
DEFINE_PUBLIC_ALIAS(_vsnprintf_s, libc__vsnprintf_s);
DEFINE_PUBLIC_ALIAS(_vsnprintf_s_l, libc__vsnprintf_s_l);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_snprintf, libd__snprintf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_snprintf, libc__snprintf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_snprintf_l, libd__snprintf_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_snprintf_l, libc__snprintf_l);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_snprintf_c, libd__snprintf_c);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_snprintf_c, libc__snprintf_c);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_snprintf_c_l, libd__snprintf_c_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_snprintf_c_l, libc__snprintf_c_l);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_snprintf_s, libd__snprintf_s);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_snprintf_s, libc__snprintf_s);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_snprintf_s_l, libd__snprintf_s_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_snprintf_s_l, libc__snprintf_s_l);
DEFINE_PUBLIC_ALIAS(_vprintf_s_l, libc__vprintf_l);
DEFINE_PUBLIC_ALIAS(_vprintf_l, libc__vprintf_l);
DEFINE_PUBLIC_ALIAS(_vprintf_p, libc__vprintf_p);
DEFINE_PUBLIC_ALIAS(_vprintf_p_l, libc__vprintf_p_l);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_printf_l, libd__printf_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_printf_l, libc__printf_l);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_printf_s_l, libd__printf_s_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_printf_s_l, libc__printf_s_l);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_printf_p, libd__printf_p);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_printf_p, libc__printf_p);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_printf_p_l, libd__printf_p_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_printf_p_l, libc__printf_p_l);
DEFINE_PUBLIC_ALIAS(_vfprintf_s_l, libc__vfprintf_l);
DEFINE_PUBLIC_ALIAS(_vfprintf_l, libc__vfprintf_l);
DEFINE_PUBLIC_ALIAS(_vfprintf_p, libc__vfprintf_p);
DEFINE_PUBLIC_ALIAS(_vfprintf_p_l, libc__vfprintf_p_l);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_fprintf_l, libd__fprintf_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_fprintf_l, libc__fprintf_l);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_fprintf_s_l, libd__fprintf_s_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_fprintf_s_l, libc__fprintf_s_l);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_fprintf_p, libd__fprintf_p);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_fprintf_p, libc__fprintf_p);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_fprintf_p_l, libd__fprintf_p_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_fprintf_p_l, libc__fprintf_p_l);
DEFINE_PUBLIC_ALIAS(fopen_s, libc_fopen_s);
DEFINE_PUBLIC_ALIAS(freopen_s, libc_freopen_s);
DEFINE_PUBLIC_ALIAS(tmpnam_s, libc_tmpnam_s);
DEFINE_PUBLIC_ALIAS(clearerr_s, libc_clearerr_s);
DEFINE_PUBLIC_ALIAS(tmpfile_s, libc_tmpfile_s);
DEFINE_PUBLIC_ALIAS(fread_s, libc_fread_s);
DEFINE_PUBLIC_ALIAS(gets_s, libc_gets_s);
DEFINE_PUBLIC_ALIAS(vsnprintf_s, libc_vsnprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$_wperror, libd__wperror);
DEFINE_PUBLIC_ALIAS(_wperror, libc__wperror);
DEFINE_PUBLIC_ALIAS(_fread_nolock_s, libc__fread_nolock_s);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_STDIO_C */
