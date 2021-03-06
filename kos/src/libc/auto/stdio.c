/* HASH CRC-32:0xa07d05a8 */
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
/* >> setbuf(3)
 * Alias for `setvbuf(stream, buf, _IOFBF, BUFSIZ)' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.utility") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc_setbuf)(FILE *__restrict stream,
                                  char *buf) {
	libc_setvbuf(stream, buf,
	        buf ? ___IOFBF : ___IONBF,
	        buf ? __BUFSIZ : 0);
}
#include <libc/local/stdstreams.h>
/* >> getchar(3)
 * Alias for `fgetc(stdin)' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.getc") int
(LIBCCALL libc_getchar)(void) THROWS(...) {
	return libc_fgetc(stdin);
}
#include <libc/local/stdstreams.h>
/* >> putchar(3)
 * Alias for `fputc(ch, stdout)' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.putc") int
(LIBCCALL libc_putchar)(int ch) THROWS(...) {
	return libc_fputc(ch, stdout);
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
/* >> fgets(3)
 * Read up to `bufsize - 1' bytes of data from `stream', storing them into `buf' stopped when
 * the buffer is full or a line-feed was read (in this case, the line-feed is also written to `buf')
 * Afterwards, append a trailing NUL-character and re-return `buf', or return `NULL' if an error occurred. */
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
/* >> fputs(3)
 * Print a given string `str' to `stream'. This is identical to:
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
#include <libc/local/stdstreams.h>
/* >> puts(3)
 * Print a given string `str', followed by a line-feed to `stdout' */
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
#include <libc/local/stdstreams.h>
#include <libc/errno.h>
/* >> perror(3)
 * Print a given `message' alongside `strerror(errno)' to stderr:
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
/* >> fprintf(3), vfprintf(3)
 * Print data to `stream', following `format'
 * Return the number of successfully printed bytes */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.printf") ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(LIBCCALL libc_vfprintf)(FILE *__restrict stream,
                         char const *__restrict format,
                         va_list args) THROWS(...) {
	return (__STDC_INT_AS_SSIZE_T)libc_format_vprintf(&libc_file_printer, stream, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fprintf(3), vfprintf(3)
 * Print data to `stream', following `format'
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
/* >> fprintf(3), vfprintf(3)
 * Print data to `stream', following `format'
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
#include <libc/local/stdstreams.h>
/* >> printf(3), vprintf(3)
 * Print data to `stdout', following `format'
 * Return the number of successfully printed bytes */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.printf") ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
(LIBCCALL libc_vprintf)(char const *__restrict format,
                        va_list args) THROWS(...) {
	return libc_vfprintf(stdout, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> printf(3), vprintf(3)
 * Print data to `stdout', following `format'
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
/* >> printf(3), vprintf(3)
 * Print data to `stdout', following `format'
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
/* >> fscanf(3), vfscanf(3)
 * Scan data from `stream', following `format'
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
#include <libc/local/stdstreams.h>
/* >> scanf(3), vscanf(3)
 * Scan data from `stdin', following `format'
 * Return the number of successfully scanned data items */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBCCALL libc_vscanf)(char const *__restrict format,
                       va_list args) THROWS(...) {
	return libc_vfscanf(stdin, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fscanf(3), vfscanf(3)
 * Scan data from `stream', following `format'
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
/* >> fscanf(3), vfscanf(3)
 * Scan data from `stream', following `format'
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
/* >> scanf(3), vscanf(3)
 * Scan data from `stdin', following `format'
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
/* >> scanf(3), vscanf(3)
 * Scan data from `stdin', following `format'
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
#include <libc/local/stdstreams.h>
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.read") WUNUSED ATTR_DEPRECATED("No buffer size checks (use `fgets\' instead)") NONNULL((1)) char *
(LIBCCALL libc_gets)(char *__restrict buf) THROWS(...) {
	return libc_fgets(buf, INT_MAX, stdin);
}
#include <asm/crt/stdio.h>
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
#ifndef ____vsscanf_getc_defined
#define ____vsscanf_getc_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsscanf_getc) ssize_t
(FORMATPRINTER_CC vsscanf_getc)(void *arg) {
	char const *reader = *(char const **)arg;
	char32_t result = libc_unicode_readutf8(&reader);
	if (!result)
		return __EOF;
	*(char const **)arg = reader;
	return result;
}
__LOCAL_LIBC(vsscanf_ungetc) ssize_t
(FORMATPRINTER_CC vsscanf_ungetc)(void *arg, char32_t UNUSED(ch)) {
	libc_unicode_readutf8_rev((char const **)arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsscanf_getc_defined */
/* >> sscanf(3), vsscanf(3)
 * Scan data from a given `input' string, following `format'
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
/* >> sscanf(3), vsscanf(3)
 * Scan data from a given `input' string, following `format'
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
/* >> sscanf(3), vsscanf(3)
 * Scan data from a given `input' string, following `format'
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
/* >> sprintf(3), vsprintf(3)
 * Print a formatted string to a given in-member string buffer `buf'
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
/* >> sprintf(3), vsprintf(3)
 * Print a formatted string to a given in-member string buffer `buf'
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
/* >> sprintf(3), vsprintf(3)
 * Print a formatted string to a given in-member string buffer `buf'
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
/* >> snprintf(3), vsnprintf(3)
 * Print a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-
 * character), and never write more than `buflen' characters to `buf' */
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
/* >> snprintf(3), vsnprintf(3)
 * Print a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-
 * character), and never write more than `buflen' characters to `buf' */
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
/* >> snprintf(3), vsnprintf(3)
 * Print a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-
 * character), and never write more than `buflen' characters to `buf' */
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
#include <bits/crt/format-printer.h>
#if !defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_INT__ != __SIZEOF_POINTER__
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vdprintf_printer) __ssize_t
(__FORMATPRINTER_CC __vdprintf_printer)(void *__arg, char const *__restrict __data, __size_t __datalen) {
	return (__ssize_t)libc_write((int)(unsigned int)(__UINTPTR_TYPE__)__arg, __data, __datalen);
}
__NAMESPACE_LOCAL_END
#endif /* !__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_INT__ != __SIZEOF_POINTER__ */
/* >> dprintf(3), vdprintf(3) */
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
/* >> dprintf(3), vdprintf(3) */
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
/* >> dprintf(3), vdprintf(3) */
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
/* >> setbuffer(3)
 * Specify the location and size for the buffer to-be used by `stream' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.utility") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc_setbuffer)(FILE *__restrict stream,
                                     char *buf,
                                     size_t bufsize) {
	libc_setvbuf(stream,
	        buf,
	        buf ? ___IOFBF : ___IONBF,
	        buf ? bufsize : (size_t)0);
}
/* >> setlinebuf(3)
 * Change the given `stream' to become line-buffered */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.utility") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc_setlinebuf)(FILE *__restrict stream) {
	libc_setvbuf(stream, NULL, _IOLBF, 0);
}
#include <asm/crt/stdio.h>
#include <hybrid/__assert.h>
/* >> getdelim(3) */
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
/* >> getline(3) */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.read") WUNUSED NONNULL((1, 2, 3)) ssize_t
(LIBCCALL libc_getline)(char **__restrict lineptr,
                        size_t *__restrict pcount,
                        FILE *__restrict stream) THROWS(...) {
	return libc_getdelim(lineptr, pcount, '\n', stream);
}
#include <libc/local/stdstreams.h>
/* >> getchar_unlocked(3)
 * Same as `getchar()', but performs I/O without acquiring a lock to `stdin' */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.getc") int
(LIBCCALL libc_getchar_unlocked)(void) THROWS(...) {
	return libc_fgetc_unlocked(stdin);
}
#include <libc/local/stdstreams.h>
/* >> putchar_unlocked(3)
 * Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.putc") int
(LIBCCALL libc_putchar_unlocked)(int ch) THROWS(...) {
	return libc_fputc_unlocked(ch, stdout);
}
#include <asm/crt/stdio.h>
/* >> getw(3)
 * Similar to `getc()', but read 2 bytes */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.getc") NONNULL((1)) int
(LIBCCALL libc_getw)(FILE *__restrict stream) THROWS(...) {
	u16 result;
	return libc_fread(&result, sizeof(result), 1, stream)
	       ? (int)result
	       : (int)EOF;
}
#include <asm/crt/stdio.h>
/* >> putw(3)
 * Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.putc") NONNULL((2)) int
(LIBCCALL libc_putw)(int w,
                     FILE *__restrict stream) THROWS(...) {
	u16 c = (u16)w;
	return libc_fwrite(&c, sizeof(c), 1, stream)
	       ? w
	       : EOF;
}
#include <libio.h>
#include <features.h>
#include <bits/types.h>
#ifndef ____fopencookie_holder_defined
__NAMESPACE_LOCAL_BEGIN
#define ____fopencookie_holder_defined 1
struct __fopencookie_holder {
	void                     *foch_cookie; /* User-defined `magic_cookie' */
	_IO_cookie_io_functions_t foch_funcs;  /* Cookie functions */
};
__NAMESPACE_LOCAL_END
#endif /* !____fopencookie_holder_defined */
#ifndef __fopencookie_to_funopen_closefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_closefn_defined 1
__LOCAL_LIBC(fopencookie_to_funopen_closefn) int
(__LIBKCALL fopencookie_to_funopen_closefn)(void *cookie) {
	int result = 0;
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	if (holder->foch_funcs.close != NULL)
		result = (*holder->foch_funcs.close)(holder->foch_cookie);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
	libc_free(holder);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
	return result;
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_closefn_defined */

#if !defined(__BUILDING_LIBC) && defined(__CRT_HAVE_funopen64) && __SIZEOF_INT__ == __SIZEOF_SIZE_T__
#ifndef __fopencookie_to_funopen_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_readfn_defined 1
__LOCAL_LIBC(fopencookie_to_funopen_readfn) int
(__LIBKCALL fopencookie_to_funopen_readfn)(void *cookie, char *buf, int num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (int)(*holder->foch_funcs.read)(holder->foch_cookie, buf, (size_t)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_readfn_defined */

#ifndef __fopencookie_to_funopen_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_writefn_defined 1
__LOCAL_LIBC(fopencookie_to_funopen_writefn) int
(__LIBKCALL fopencookie_to_funopen_writefn)(void *cookie, char const *buf, int num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (int)(*holder->foch_funcs.write)(holder->foch_cookie, buf, (size_t)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_writefn_defined */

#ifndef __fopencookie_to_funopen64_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen64_seekfn_defined 1
__LOCAL_LIBC(fopencookie_to_funopen64_seekfn) off64_t
(__LIBKCALL fopencookie_to_funopen64_seekfn)(void *cookie, off64_t off, int whence) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
#ifdef __USE_KOS_ALTERATIONS
	if ((*holder->foch_funcs.seek)(holder->foch_cookie, (pos64_t *)&off, whence) != 0)
		return -1;
#else /* __USE_KOS_ALTERATIONS */
	if ((*holder->foch_funcs.seek)(holder->foch_cookie, &off, whence) != 0)
		return -1;
#endif /* !__USE_KOS_ALTERATIONS */
	return off;
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen64_seekfn_defined */

#elif !defined(__BUILDING_LIBC) && defined(__CRT_HAVE_funopen) && !defined(__CRT_HAVE_funopen2_64) && __SIZEOF_INT__ == __SIZEOF_SIZE_T__
#ifndef __fopencookie_to_funopen_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_readfn_defined 1
__LOCAL_LIBC(fopencookie_to_funopen_readfn) int
(__LIBKCALL fopencookie_to_funopen_readfn)(void *cookie, char *buf, int num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (int)(*holder->foch_funcs.read)(holder->foch_cookie, buf, (size_t)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_readfn_defined */

#ifndef __fopencookie_to_funopen_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_writefn_defined 1
__LOCAL_LIBC(fopencookie_to_funopen_writefn) int
(__LIBKCALL fopencookie_to_funopen_writefn)(void *cookie, char const *buf, int num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (int)(*holder->foch_funcs.write)(holder->foch_cookie, buf, (size_t)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_writefn_defined */

#ifndef __fopencookie_to_funopen_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_seekfn_defined 1
__LOCAL_LIBC(fopencookie_to_funopen_seekfn) __FS_TYPE(off)
(__LIBKCALL fopencookie_to_funopen_seekfn)(void *cookie, __FS_TYPE(off) off, int whence) {
#if __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
#ifdef __USE_KOS_ALTERATIONS
	if ((*holder->foch_funcs.seek)(holder->foch_cookie, (pos64_t *)&off, whence) != 0)
		return -1;
#else /* __USE_KOS_ALTERATIONS */
	if ((*holder->foch_funcs.seek)(holder->foch_cookie, (off64_t *)&off, whence) != 0)
		return -1;
#endif /* !__USE_KOS_ALTERATIONS */
	return off;
#else /* __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__ */
#ifdef __USE_KOS_ALTERATIONS
	pos64_t newpos = (pos64_t)off;
#else /* __USE_KOS_ALTERATIONS */
	off64_t newpos = off;
#endif /* !__USE_KOS_ALTERATIONS */
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	if ((*holder->foch_funcs.seek)(holder->foch_cookie, &newpos, whence) != 0)
		return -1;
	return (__FS_TYPE(off))newpos;
#endif /* __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__ */
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_seekfn_defined */

#elif (defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2))
#ifndef __fopencookie_to_funopen2_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen2_readfn_defined 1
__LOCAL_LIBC(fopencookie_to_funopen2_readfn) ssize_t
(__LIBKCALL fopencookie_to_funopen2_readfn)(void *cookie, void *buf, size_t num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (*holder->foch_funcs.read)(holder->foch_cookie, (char *)buf, num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen2_readfn_defined */

#ifndef __fopencookie_to_funopen2_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen2_writefn_defined 1
__LOCAL_LIBC(fopencookie_to_funopen2_writefn) ssize_t
(__LIBKCALL fopencookie_to_funopen2_writefn)(void *cookie, void const *buf, size_t num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (*holder->foch_funcs.write)(holder->foch_cookie, (char const *)buf, num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen2_writefn_defined */

#ifndef __fopencookie_to_funopen64_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen64_seekfn_defined 1
__LOCAL_LIBC(fopencookie_to_funopen64_seekfn) off64_t
(__LIBKCALL fopencookie_to_funopen64_seekfn)(void *cookie, off64_t off, int whence) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
#ifdef __USE_KOS_ALTERATIONS
	if ((*holder->foch_funcs.seek)(holder->foch_cookie, (pos64_t *)&off, whence) != 0)
		return -1;
#else /* __USE_KOS_ALTERATIONS */
	if ((*holder->foch_funcs.seek)(holder->foch_cookie, &off, whence) != 0)
		return -1;
#endif /* !__USE_KOS_ALTERATIONS */
	return off;
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen64_seekfn_defined */

#elif defined(__CRT_HAVE_funopen2) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
#ifndef __fopencookie_to_funopen2_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen2_readfn_defined 1
__LOCAL_LIBC(fopencookie_to_funopen2_readfn) ssize_t
(__LIBKCALL fopencookie_to_funopen2_readfn)(void *cookie, void *buf, size_t num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (*holder->foch_funcs.read)(holder->foch_cookie, (char *)buf, num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen2_readfn_defined */

#ifndef __fopencookie_to_funopen2_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen2_writefn_defined 1
__LOCAL_LIBC(fopencookie_to_funopen2_writefn) ssize_t
(__LIBKCALL fopencookie_to_funopen2_writefn)(void *cookie, void const *buf, size_t num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (*holder->foch_funcs.write)(holder->foch_cookie, (char const *)buf, num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen2_writefn_defined */

#ifndef __fopencookie_to_funopen_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_seekfn_defined 1
__LOCAL_LIBC(fopencookie_to_funopen_seekfn) __FS_TYPE(off)
(__LIBKCALL fopencookie_to_funopen_seekfn)(void *cookie, __FS_TYPE(off) off, int whence) {
#if __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
#ifdef __USE_KOS_ALTERATIONS
	if ((*holder->foch_funcs.seek)(holder->foch_cookie, (pos64_t *)&off, whence) != 0)
		return -1;
#else /* __USE_KOS_ALTERATIONS */
	if ((*holder->foch_funcs.seek)(holder->foch_cookie, (off64_t *)&off, whence) != 0)
		return -1;
#endif /* !__USE_KOS_ALTERATIONS */
	return off;
#else /* __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__ */
#ifdef __USE_KOS_ALTERATIONS
	pos64_t newpos = (pos64_t)off;
#else /* __USE_KOS_ALTERATIONS */
	off64_t newpos = off;
#endif /* !__USE_KOS_ALTERATIONS */
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	if ((*holder->foch_funcs.seek)(holder->foch_cookie, &newpos, whence) != 0)
		return -1;
	return (__FS_TYPE(off))newpos;
#endif /* __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__ */
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_seekfn_defined */

#elif (defined(__CRT_HAVE_funopen) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_funopen2) || defined(__CRT_HAVE_fopencookie) || defined(__CRT_HAVE_funopen)))
#ifndef __fopencookie_to_funopen_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_readfn_defined 1
__LOCAL_LIBC(fopencookie_to_funopen_readfn) int
(__LIBKCALL fopencookie_to_funopen_readfn)(void *cookie, char *buf, int num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (int)(*holder->foch_funcs.read)(holder->foch_cookie, buf, (size_t)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_readfn_defined */

#ifndef __fopencookie_to_funopen_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_writefn_defined 1
__LOCAL_LIBC(fopencookie_to_funopen_writefn) int
(__LIBKCALL fopencookie_to_funopen_writefn)(void *cookie, char const *buf, int num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (int)(*holder->foch_funcs.write)(holder->foch_cookie, buf, (size_t)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_writefn_defined */

#ifndef __fopencookie_to_funopen64_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen64_seekfn_defined 1
__LOCAL_LIBC(fopencookie_to_funopen64_seekfn) off64_t
(__LIBKCALL fopencookie_to_funopen64_seekfn)(void *cookie, off64_t off, int whence) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
#ifdef __USE_KOS_ALTERATIONS
	if ((*holder->foch_funcs.seek)(holder->foch_cookie, (pos64_t *)&off, whence) != 0)
		return -1;
#else /* __USE_KOS_ALTERATIONS */
	if ((*holder->foch_funcs.seek)(holder->foch_cookie, &off, whence) != 0)
		return -1;
#endif /* !__USE_KOS_ALTERATIONS */
	return off;
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen64_seekfn_defined */

#else /* ... */
#ifndef __fopencookie_to_funopen_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_readfn_defined 1
__LOCAL_LIBC(fopencookie_to_funopen_readfn) int
(__LIBKCALL fopencookie_to_funopen_readfn)(void *cookie, char *buf, int num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (int)(*holder->foch_funcs.read)(holder->foch_cookie, buf, (size_t)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_readfn_defined */

#ifndef __fopencookie_to_funopen_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_writefn_defined 1
__LOCAL_LIBC(fopencookie_to_funopen_writefn) int
(__LIBKCALL fopencookie_to_funopen_writefn)(void *cookie, char const *buf, int num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (int)(*holder->foch_funcs.write)(holder->foch_cookie, buf, (size_t)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_writefn_defined */

#ifndef __fopencookie_to_funopen_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_seekfn_defined 1
__LOCAL_LIBC(fopencookie_to_funopen_seekfn) __FS_TYPE(off)
(__LIBKCALL fopencookie_to_funopen_seekfn)(void *cookie, __FS_TYPE(off) off, int whence) {
#if __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
#ifdef __USE_KOS_ALTERATIONS
	if ((*holder->foch_funcs.seek)(holder->foch_cookie, (pos64_t *)&off, whence) != 0)
		return -1;
#else /* __USE_KOS_ALTERATIONS */
	if ((*holder->foch_funcs.seek)(holder->foch_cookie, (off64_t *)&off, whence) != 0)
		return -1;
#endif /* !__USE_KOS_ALTERATIONS */
	return off;
#else /* __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__ */
#ifdef __USE_KOS_ALTERATIONS
	pos64_t newpos = (pos64_t)off;
#else /* __USE_KOS_ALTERATIONS */
	off64_t newpos = off;
#endif /* !__USE_KOS_ALTERATIONS */
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	if ((*holder->foch_funcs.seek)(holder->foch_cookie, &newpos, whence) != 0)
		return -1;
	return (__FS_TYPE(off))newpos;
#endif /* __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__ */
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_seekfn_defined */

#endif /* !... */
/* >> fopencookie(3) */
INTERN ATTR_SECTION(".text.crt.FILE.locked.access") WUNUSED NONNULL((2)) FILE *
NOTHROW_NCX(LIBCCALL libc_fopencookie)(void *__restrict magic_cookie,
                                       char const *__restrict modes,
                                       cookie_io_functions_t io_funcs) {
	FILE *result;
	struct __NAMESPACE_LOCAL_SYM __fopencookie_holder *holder;
	(void)modes; /* unused... */
	holder = (struct __NAMESPACE_LOCAL_SYM __fopencookie_holder *)libc_malloc(sizeof(struct __NAMESPACE_LOCAL_SYM __fopencookie_holder));
	if unlikely(!holder)
		return NULL;
	holder->foch_cookie        = magic_cookie;
	holder->foch_funcs.read  = io_funcs.read;
	holder->foch_funcs.write = io_funcs.write;
	holder->foch_funcs.seek  = io_funcs.seek;
	holder->foch_funcs.close = io_funcs.close;












#if (defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2))
	result = libc_funopen2_64(/* cookie:  */ holder,
	                     /* readfn:  */ io_funcs.read ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen2_readfn : NULL,
	                     /* writefn: */ io_funcs.write ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen2_writefn : NULL,
	                     /* seekfn:  */ io_funcs.seek ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen64_seekfn : NULL,
	                     /* flushfn: */ NULL,
	                     /* closefn: */ &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_closefn);
#elif defined(__CRT_HAVE_funopen2) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
	result = libc_funopen2(/* cookie:  */ holder,
	                  /* readfn:  */ io_funcs.read ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen2_readfn : NULL,
	                  /* writefn: */ io_funcs.write ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen2_writefn : NULL,
	                  /* seekfn:  */ io_funcs.seek ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_seekfn : NULL,
	                  /* flushfn: */ NULL,
	                  /* closefn: */ &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_closefn);
#elif (defined(__CRT_HAVE_funopen) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_funopen2) || defined(__CRT_HAVE_fopencookie) || defined(__CRT_HAVE_funopen)))
	result = libc_funopen64(/* cookie:  */ holder,
	                   /* readfn:  */ io_funcs.read ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_readfn : NULL,
	                   /* writefn: */ io_funcs.write ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_writefn : NULL,
	                   /* seekfn:  */ io_funcs.seek ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen64_seekfn : NULL,
	                   /* closefn: */ &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_closefn);
#else /* ... */
	result = libc_funopen(/* cookie:  */ holder,
	                 /* readfn:  */ io_funcs.read ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_readfn : NULL,
	                 /* writefn: */ io_funcs.write ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_writefn : NULL,
	                 /* seekfn:  */ io_funcs.seek ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_seekfn : NULL,
	                 /* closefn: */ &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_closefn);
#endif /* !... */
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
	if unlikely(!result)
		libc_free(holder);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
	return result;
}
#include <hybrid/typecore.h>
#include <asm/crt/stdio.h>
#include <libc/errno.h>
/* >> fgets_unlocked(3)
 * Same as `fgets()', but performs I/O without acquiring a lock to `stream' */
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
/* >> fputs_unlocked(3)
 * Same as `fputs()', but performs I/O without acquiring a lock to `stream' */
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
/* >> asprintf(3), vasprintf(3)
 * Print the given `format' into a newly allocated, heap-allocated string which is then stored in `*pstr' */
INTERN ATTR_SECTION(".text.crt.heap.strdup") ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
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
		*pstr = NULL;
		return -1;
	}
	result = libc_format_aprintf_pack(&data, NULL);
	*pstr  = result;
	if unlikely(!result)
		return -1;
	return (__STDC_INT_AS_SSIZE_T)error;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> asprintf(3), vasprintf(3)
 * Print the given `format' into a newly allocated, heap-allocated string which is then stored in `*pstr' */
INTERN ATTR_SECTION(".text.crt.dos.heap.strdup") ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
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
/* >> asprintf(3), vasprintf(3)
 * Print the given `format' into a newly allocated, heap-allocated string which is then stored in `*pstr' */
INTERN ATTR_SECTION(".text.crt.heap.strdup") ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
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
	       ? (int)(unsigned int)result
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
/* >> getdelim(3) */
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
#include <libc/local/stdstreams.h>
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
/* >> fprintf_unlocked(3), vfprintf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.printf") ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(LIBCCALL libc_vfprintf_unlocked)(FILE *__restrict stream,
                                  char const *__restrict format,
                                  va_list args) THROWS(...) {
	return (__STDC_INT_AS_SSIZE_T)libc_format_vprintf(&libc_file_printer_unlocked, stream, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fprintf_unlocked(3), vfprintf_unlocked(3) */
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
/* >> fprintf_unlocked(3), vfprintf_unlocked(3) */
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
#include <libc/local/stdstreams.h>
/* >> printf_unlocked(3), vprintf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.printf") ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
(LIBCCALL libc_vprintf_unlocked)(char const *__restrict format,
                                 va_list args) THROWS(...) {
	return libc_vfprintf_unlocked(stdout, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> printf_unlocked(3), vprintf_unlocked(3) */
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
/* >> printf_unlocked(3), vprintf_unlocked(3) */
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
/* >> fscanf_unlocked(3), vfscanf_unlocked(3) */
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
#include <libc/local/stdstreams.h>
/* >> scanf_unlocked(3), vscanf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBCCALL libc_vscanf_unlocked)(char const *__restrict format,
                                va_list args) THROWS(...) {
	return libc_vfscanf_unlocked(stdin, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fscanf_unlocked(3), vfscanf_unlocked(3) */
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
/* >> fscanf_unlocked(3), vfscanf_unlocked(3) */
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
/* >> scanf_unlocked(3), vscanf_unlocked(3) */
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
/* >> scanf_unlocked(3), vscanf_unlocked(3) */
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
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__ && ((defined(__CRT_HAVE_funopen2) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__) || (defined(__CRT_HAVE_funopen2_64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2))))
#ifndef ____funopen2_types_defined
#define ____funopen2_types_defined 1
typedef __ssize_t (__LIBKCALL *__funopen2_readfn_t)(void *__cookie, void *__buf, __size_t __num_bytes);
typedef __ssize_t (__LIBKCALL *__funopen2_writefn_t)(void *__cookie, void const *__buf, __size_t __num_bytes);
typedef __FS_TYPE(off) (__LIBKCALL *__funopen2_seekfn_t)(void *__cookie, __FS_TYPE(off) __off, int __whence);
typedef int (__LIBKCALL *__funopen2_flushfn_t)(void *__cookie);
typedef int (__LIBKCALL *__funopen2_closefn_t)(void *__cookie);
#endif /* !____funopen2_types_defined */

#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ && ((__CRT_HAVE_funopen2 && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__) || (__CRT_HAVE_funopen2_64 && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__) || ((__CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign) && ((__CRT_HAVE_funopen2 && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || __CRT_HAVE_funopen2_64 || __CRT_HAVE_funopen2))) */
#ifndef ____funopen_types_defined
#define ____funopen_types_defined 1
typedef int (__LIBKCALL *__funopen_readfn_t)(void *__cookie, char *__buf, int __num_bytes);
typedef int (__LIBKCALL *__funopen_writefn_t)(void *__cookie, char const *__buf, int __num_bytes);
typedef __FS_TYPE(off) (__LIBKCALL *__funopen_seekfn_t)(void *__cookie, __FS_TYPE(off) __off, int __whence);
typedef int (__LIBKCALL *__funopen_closefn_t)(void *__cookie);
#endif /* !____funopen_types_defined */

#ifndef ____funopen_holder_defined
__NAMESPACE_LOCAL_BEGIN
#define ____funopen_holder_defined 1
struct __funopen_holder {
	void               *fh_cookie;  /* [0..1] funopen readfn */
	__funopen_readfn_t  fh_readfn;  /* [0..1] funopen readfn */
	__funopen_writefn_t fh_writefn; /* [0..1] funopen writefn */
	__funopen_seekfn_t  fh_seekfn;  /* [0..1] funopen seekfn */
	__funopen_closefn_t fh_closefn; /* [0..1] funopen closefn */
};
__NAMESPACE_LOCAL_END
#endif /* !____funopen_holder_defined */

#ifndef __funopen_to_funopen2_closefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_closefn_defined 1
__LOCAL_LIBC(funopen_to_funopen2_closefn) int
(__LIBKCALL funopen_to_funopen2_closefn)(void *cookie) {
	int result = 0;
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	if (holder->fh_closefn != NULL)
		result = (*holder->fh_closefn)(holder->fh_cookie);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
	libc_free(holder);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
	return result;
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_closefn_defined */

#if (defined(__CRT_HAVE_funopen2) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__) || (defined(__CRT_HAVE_funopen2_64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2)))
#ifndef __funopen_to_funopen2_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_readfn_defined 1
__LOCAL_LIBC(funopen_to_funopen2_readfn) ssize_t
(__LIBKCALL funopen_to_funopen2_readfn)(void *cookie, void *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_readfn)(holder->fh_cookie, (char *)buf,
	                                     (int)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_readfn_defined */

#ifndef __funopen_to_funopen2_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_writefn_defined 1
__LOCAL_LIBC(funopen_to_funopen2_writefn) ssize_t
(__LIBKCALL funopen_to_funopen2_writefn)(void *cookie, void const *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_writefn)(holder->fh_cookie, (char const *)buf,
	                                      (int)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_writefn_defined */

#ifndef ____funopen2_types_defined
#define ____funopen2_types_defined 1
typedef __ssize_t (__LIBKCALL *__funopen2_readfn_t)(void *__cookie, void *__buf, __size_t __num_bytes);
typedef __ssize_t (__LIBKCALL *__funopen2_writefn_t)(void *__cookie, void const *__buf, __size_t __num_bytes);
typedef __FS_TYPE(off) (__LIBKCALL *__funopen2_seekfn_t)(void *__cookie, __FS_TYPE(off) __off, int __whence);
typedef int (__LIBKCALL *__funopen2_flushfn_t)(void *__cookie);
typedef int (__LIBKCALL *__funopen2_closefn_t)(void *__cookie);
#endif /* !____funopen2_types_defined */

#ifndef __funopen_to_funopen2_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_seekfn_defined 1
__LOCAL_LIBC(funopen_to_funopen2_seekfn) __FS_TYPE(off)
(__LIBKCALL funopen_to_funopen2_seekfn)(void *cookie, __FS_TYPE(off) off, int whence) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_seekfn)(holder->fh_cookie, off, whence);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_seekfn_defined */

#elif defined(__CRT_HAVE_fopencookie)
#ifndef __funopen_to_funopen2_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_readfn_defined 1
__LOCAL_LIBC(funopen_to_funopen2_readfn) ssize_t
(__LIBKCALL funopen_to_funopen2_readfn)(void *cookie, void *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_readfn)(holder->fh_cookie, (char *)buf,
	                                     (int)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_readfn_defined */

#ifndef __funopen_to_funopen2_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_writefn_defined 1
__LOCAL_LIBC(funopen_to_funopen2_writefn) ssize_t
(__LIBKCALL funopen_to_funopen2_writefn)(void *cookie, void const *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_writefn)(holder->fh_cookie, (char const *)buf,
	                                      (int)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_writefn_defined */

#ifndef __funopen_to_fopencookie_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_fopencookie_seekfn_defined 1
#ifdef __USE_KOS_ALTERATIONS
__LOCAL_LIBC(funopen_to_fopencookie_seekfn) int
(__LIBKCALL funopen_to_fopencookie_seekfn)(void *cookie, pos64_t *pos, int whence)
#else /* __USE_KOS_ALTERATIONS */
__LOCAL_LIBC(funopen_to_fopencookie_seekfn) int
(__LIBKCALL funopen_to_fopencookie_seekfn)(void *cookie, off64_t *pos, int whence)
#endif /* !__USE_KOS_ALTERATIONS */
{
	__FS_TYPE(off) newpos;
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	newpos = (*holder->fh_seekfn)(holder->fh_cookie, (__FS_TYPE(off))*pos, whence);
	if unlikely(newpos == -1)
		return -1;
#ifdef __USE_KOS_ALTERATIONS
	*pos = (pos64_t)(off64_t)newpos;
#else /* __USE_KOS_ALTERATIONS */
	*pos = (off64_t)newpos;
#endif /* !__USE_KOS_ALTERATIONS */
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_fopencookie_seekfn_defined */

#include <libio.h>
#else /* ... */
#ifndef ____funopen64_types_defined
#define ____funopen64_types_defined 1
typedef __off64_t (__LIBKCALL *__funopen64_seekfn_t)(void *__cookie, __off64_t __off, int __whence);
#endif /* !____funopen64_types_defined */

#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__
#ifndef __funopen_to_funopen2_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_readfn_defined 1
__LOCAL_LIBC(funopen_to_funopen2_readfn) ssize_t
(__LIBKCALL funopen_to_funopen2_readfn)(void *cookie, void *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_readfn)(holder->fh_cookie, (char *)buf,
	                                     (int)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_readfn_defined */

#ifndef __funopen_to_funopen2_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_writefn_defined 1
__LOCAL_LIBC(funopen_to_funopen2_writefn) ssize_t
(__LIBKCALL funopen_to_funopen2_writefn)(void *cookie, void const *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_writefn)(holder->fh_cookie, (char const *)buf,
	                                      (int)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_writefn_defined */

#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ */
#ifndef __funopen_to_funopen64_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen64_readfn_defined 1
__LOCAL_LIBC(funopen_to_funopen64_readfn) int
(__LIBKCALL funopen_to_funopen64_readfn)(void *cookie, char *buf, int num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_readfn)(holder->fh_cookie, buf, num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen64_readfn_defined */

#ifndef __funopen_to_funopen64_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen64_writefn_defined 1
__LOCAL_LIBC(funopen_to_funopen64_writefn) int
(__LIBKCALL funopen_to_funopen64_writefn)(void *cookie, char const *buf, int num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_writefn)(holder->fh_cookie, buf, num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen64_writefn_defined */

#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
#ifndef __funopen_to_funopen64_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen64_seekfn_defined 1
__LOCAL_LIBC(funopen_to_funopen64_seekfn) off64_t
(__LIBKCALL funopen_to_funopen64_seekfn)(void *cookie, off64_t off, int whence) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_seekfn)(holder->fh_cookie, (__FS_TYPE(off))off, whence);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen64_seekfn_defined */

#endif /* !... */
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ || ((!__CRT_HAVE_funopen2 || __FS_SIZEOF(OFF) != __SIZEOF_OFF32_T__) && (!__CRT_HAVE_funopen2_64 || __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__) && ((!__CRT_HAVE_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE_funopen2_64 && !__CRT_HAVE_funopen2))) */
/* >> funopen(3), funopen64(3) */
INTERN ATTR_SECTION(".text.crt.FILE.locked.access") WUNUSED FILE *
NOTHROW_NCX(LIBCCALL libc_funopen)(void const *cookie,
                                   __funopen_readfn_t readfn,
                                   __funopen_writefn_t writefn,
                                   __funopen_seekfn_t seekfn,
                                   __funopen_closefn_t closefn) {
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__ && ((defined(__CRT_HAVE_funopen2) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__) || (defined(__CRT_HAVE_funopen2_64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2))))
	return libc_funopen2(cookie,
	                (__funopen2_readfn_t)readfn,
	                (__funopen2_writefn_t)writefn,
	                seekfn, NULL, closefn);
#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ && ((__CRT_HAVE_funopen2 && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__) || (__CRT_HAVE_funopen2_64 && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__) || ((__CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign) && ((__CRT_HAVE_funopen2 && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || __CRT_HAVE_funopen2_64 || __CRT_HAVE_funopen2))) */
	FILE *result;
	struct __NAMESPACE_LOCAL_SYM __funopen_holder *holder;
#if (defined(__CRT_HAVE_funopen) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen64) || (__SIZEOF_INT__ == __SIZEOF_SIZE_T__ && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2)))) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2) || defined(__CRT_HAVE_fopencookie) || defined(__CRT_HAVE_funopen)))
	if (!seekfn)
		return libc_funopen64(cookie, readfn, writefn, NULL, closefn);
#endif /* (__CRT_HAVE_funopen && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || __CRT_HAVE_funopen64 || (__SIZEOF_INT__ == __SIZEOF_SIZE_T__ && ((__CRT_HAVE_funopen2 && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || __CRT_HAVE_funopen2_64 || ((__CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign) && __CRT_HAVE_funopen2))) || ((__CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_funopen2_64 || __CRT_HAVE_funopen2 || __CRT_HAVE_fopencookie || __CRT_HAVE_funopen)) */
	holder = (struct __NAMESPACE_LOCAL_SYM __funopen_holder *)libc_malloc(sizeof(struct __NAMESPACE_LOCAL_SYM __funopen_holder));
	if unlikely(!holder)
		return NULL;
	holder->fh_cookie  = (void *)cookie;
	holder->fh_readfn  = readfn;
	holder->fh_writefn = writefn;
	holder->fh_seekfn  = seekfn;
	holder->fh_closefn = closefn;
#if (defined(__CRT_HAVE_funopen2) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__) || (defined(__CRT_HAVE_funopen2_64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2)))
	result = libc_funopen2(/* cookie:  */ holder,
	                  /* readfn:  */ readfn  ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_readfn  : NULL,
	                  /* writefn: */ writefn ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_writefn : NULL,
	                  /* seekfn:  */ seekfn  ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_seekfn  : NULL,
	                  /* flushfn: */ NULL,
	                  /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
#elif defined(__CRT_HAVE_fopencookie)
	{
		_IO_cookie_io_functions_t ioc_functions;
		ioc_functions.read  = readfn ? (__io_read_fn *)&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_readfn : NULL;
		ioc_functions.write = writefn ? (__io_write_fn *)&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_writefn : NULL;
		ioc_functions.seek  = seekfn ? &__NAMESPACE_LOCAL_SYM funopen_to_fopencookie_seekfn  : NULL;
		ioc_functions.close = &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn;
		result = crt_fopencookie(holder, readfn && writefn ? "r+" : readfn ? "r" : "w", ioc_functions);
	}
#else /* ... */
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__
	result = libc_funopen64(/* cookie:  */ holder,
	                   /* readfn:  */ readfn  ? (__funopen_readfn_t)&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_readfn  : NULL,
	                   /* writefn: */ writefn ? (__funopen_writefn_t)&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_writefn : NULL,
	                   /* seekfn:  */ seekfn  ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen64_seekfn  : NULL,
	                   /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ */
	result = libc_funopen64(/* cookie:  */ holder,
	                   /* readfn:  */ readfn  ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen64_readfn  : NULL,
	                   /* writefn: */ writefn ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen64_writefn : NULL,
	                   /* seekfn:  */ seekfn  ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen64_seekfn  : NULL,
	                   /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
#endif /* !... */
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
	if unlikely(!result)
		libc_free(holder);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
	return result;
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ || ((!__CRT_HAVE_funopen2 || __FS_SIZEOF(OFF) != __SIZEOF_OFF32_T__) && (!__CRT_HAVE_funopen2_64 || __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__) && ((!__CRT_HAVE_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE_funopen2_64 && !__CRT_HAVE_funopen2))) */
}
#include <bits/types.h>
#if __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
DEFINE_INTERN_ALIAS(libc_funopen64, libc_funopen);
#else /* __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__ */
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__ && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2)))
#ifndef ____funopen2_types_defined
#define ____funopen2_types_defined 1
typedef __ssize_t (__LIBKCALL *__funopen2_readfn_t)(void *__cookie, void *__buf, __size_t __num_bytes);
typedef __ssize_t (__LIBKCALL *__funopen2_writefn_t)(void *__cookie, void const *__buf, __size_t __num_bytes);
typedef __FS_TYPE(off) (__LIBKCALL *__funopen2_seekfn_t)(void *__cookie, __FS_TYPE(off) __off, int __whence);
typedef int (__LIBKCALL *__funopen2_flushfn_t)(void *__cookie);
typedef int (__LIBKCALL *__funopen2_closefn_t)(void *__cookie);
#endif /* !____funopen2_types_defined */

#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ && ((__CRT_HAVE_funopen2 && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || __CRT_HAVE_funopen2_64 || ((__CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign) && __CRT_HAVE_funopen2)) */
#ifndef ____funopen_types_defined
#define ____funopen_types_defined 1
typedef int (__LIBKCALL *__funopen_readfn_t)(void *__cookie, char *__buf, int __num_bytes);
typedef int (__LIBKCALL *__funopen_writefn_t)(void *__cookie, char const *__buf, int __num_bytes);
typedef __FS_TYPE(off) (__LIBKCALL *__funopen_seekfn_t)(void *__cookie, __FS_TYPE(off) __off, int __whence);
typedef int (__LIBKCALL *__funopen_closefn_t)(void *__cookie);
#endif /* !____funopen_types_defined */

#ifndef ____funopen64_types_defined
#define ____funopen64_types_defined 1
typedef __off64_t (__LIBKCALL *__funopen64_seekfn_t)(void *__cookie, __off64_t __off, int __whence);
#endif /* !____funopen64_types_defined */

#ifndef ____funopen_holder_defined
__NAMESPACE_LOCAL_BEGIN
#define ____funopen_holder_defined 1
struct __funopen_holder {
	void               *fh_cookie;  /* [0..1] funopen readfn */
	__funopen_readfn_t  fh_readfn;  /* [0..1] funopen readfn */
	__funopen_writefn_t fh_writefn; /* [0..1] funopen writefn */
	__funopen_seekfn_t  fh_seekfn;  /* [0..1] funopen seekfn */
	__funopen_closefn_t fh_closefn; /* [0..1] funopen closefn */
};
__NAMESPACE_LOCAL_END
#endif /* !____funopen_holder_defined */

#ifndef ____funopen64_holder_defined
__NAMESPACE_LOCAL_BEGIN
#define ____funopen64_holder_defined 1
struct __funopen64_holder {
	void                *fh64_cookie;  /* [0..1] funopen readfn */
	__funopen_readfn_t   fh64_readfn;  /* [0..1] funopen readfn */
	__funopen_writefn_t  fh64_writefn; /* [0..1] funopen writefn */
	__funopen64_seekfn_t fh64_seekfn;  /* [0..1] funopen seekfn */
	__funopen_closefn_t  fh64_closefn; /* [0..1] funopen closefn */
};
__NAMESPACE_LOCAL_END
#endif /* !____funopen64_holder_defined */

#ifndef __funopen_to_funopen2_closefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_closefn_defined 1
__LOCAL_LIBC(funopen_to_funopen2_closefn) int
(__LIBKCALL funopen_to_funopen2_closefn)(void *cookie) {
	int result = 0;
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	if (holder->fh_closefn != NULL)
		result = (*holder->fh_closefn)(holder->fh_cookie);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
	libc_free(holder);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
	return result;
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_closefn_defined */

#if (defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2))
#ifndef __funopen_to_funopen2_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_readfn_defined 1
__LOCAL_LIBC(funopen_to_funopen2_readfn) ssize_t
(__LIBKCALL funopen_to_funopen2_readfn)(void *cookie, void *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_readfn)(holder->fh_cookie, (char *)buf,
	                                     (int)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_readfn_defined */

#ifndef __funopen_to_funopen2_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_writefn_defined 1
__LOCAL_LIBC(funopen_to_funopen2_writefn) ssize_t
(__LIBKCALL funopen_to_funopen2_writefn)(void *cookie, void const *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_writefn)(holder->fh_cookie, (char const *)buf,
	                                      (int)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_writefn_defined */

#ifndef ____funopen2_types_defined
#define ____funopen2_types_defined 1
typedef __ssize_t (__LIBKCALL *__funopen2_readfn_t)(void *__cookie, void *__buf, __size_t __num_bytes);
typedef __ssize_t (__LIBKCALL *__funopen2_writefn_t)(void *__cookie, void const *__buf, __size_t __num_bytes);
typedef __FS_TYPE(off) (__LIBKCALL *__funopen2_seekfn_t)(void *__cookie, __FS_TYPE(off) __off, int __whence);
typedef int (__LIBKCALL *__funopen2_flushfn_t)(void *__cookie);
typedef int (__LIBKCALL *__funopen2_closefn_t)(void *__cookie);
#endif /* !____funopen2_types_defined */

#if __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
#ifndef __funopen_to_funopen2_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_seekfn_defined 1
__LOCAL_LIBC(funopen_to_funopen2_seekfn) __FS_TYPE(off)
(__LIBKCALL funopen_to_funopen2_seekfn)(void *cookie, __FS_TYPE(off) off, int whence) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_seekfn)(holder->fh_cookie, off, whence);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_seekfn_defined */

#else /* __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__ */
#ifndef __funopen64_to_funopen2_64_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen64_to_funopen2_64_seekfn_defined 1
__LOCAL_LIBC(funopen64_to_funopen2_64_seekfn) __off64_t
(__LIBKCALL funopen64_to_funopen2_64_seekfn)(void *cookie, __off64_t off, int whence) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_seekfn)(holder->fh_cookie, off, whence);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen64_to_funopen2_64_seekfn_defined */

#endif /* __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__ */
#elif defined(__CRT_HAVE_fopencookie)
#ifndef __funopen_to_funopen2_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_readfn_defined 1
__LOCAL_LIBC(funopen_to_funopen2_readfn) ssize_t
(__LIBKCALL funopen_to_funopen2_readfn)(void *cookie, void *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_readfn)(holder->fh_cookie, (char *)buf,
	                                     (int)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_readfn_defined */

#ifndef __funopen_to_funopen2_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_writefn_defined 1
__LOCAL_LIBC(funopen_to_funopen2_writefn) ssize_t
(__LIBKCALL funopen_to_funopen2_writefn)(void *cookie, void const *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_writefn)(holder->fh_cookie, (char const *)buf,
	                                      (int)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_writefn_defined */

#if __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
#ifndef __funopen_to_fopencookie_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_fopencookie_seekfn_defined 1
#ifdef __USE_KOS_ALTERATIONS
__LOCAL_LIBC(funopen_to_fopencookie_seekfn) int
(__LIBKCALL funopen_to_fopencookie_seekfn)(void *cookie, pos64_t *pos, int whence)
#else /* __USE_KOS_ALTERATIONS */
__LOCAL_LIBC(funopen_to_fopencookie_seekfn) int
(__LIBKCALL funopen_to_fopencookie_seekfn)(void *cookie, off64_t *pos, int whence)
#endif /* !__USE_KOS_ALTERATIONS */
{
	__FS_TYPE(off) newpos;
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	newpos = (*holder->fh_seekfn)(holder->fh_cookie, (__FS_TYPE(off))*pos, whence);
	if unlikely(newpos == -1)
		return -1;
#ifdef __USE_KOS_ALTERATIONS
	*pos = (pos64_t)(off64_t)newpos;
#else /* __USE_KOS_ALTERATIONS */
	*pos = (off64_t)newpos;
#endif /* !__USE_KOS_ALTERATIONS */
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_fopencookie_seekfn_defined */

#else /* __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__ */
#ifndef __funopen64_to_fopencookie_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen64_to_fopencookie_seekfn_defined 1
#ifdef __USE_KOS_ALTERATIONS
__LOCAL_LIBC(funopen64_to_fopencookie_seekfn) int
(__LIBKCALL funopen64_to_fopencookie_seekfn)(void *cookie, pos64_t *pos, int whence)
#else /* __USE_KOS_ALTERATIONS */
__LOCAL_LIBC(funopen64_to_fopencookie_seekfn) int
(__LIBKCALL funopen64_to_fopencookie_seekfn)(void *cookie, off64_t *pos, int whence)
#endif /* !__USE_KOS_ALTERATIONS */
{
	off64_t newpos;
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	newpos = (*holder->fh_seekfn)(holder->fh_cookie, (off64_t)*pos, whence);
	if unlikely(newpos == -1)
		return -1;
#ifdef __USE_KOS_ALTERATIONS
	*pos = (pos64_t)newpos;
#else /* __USE_KOS_ALTERATIONS */
	*pos = newpos;
#endif /* !__USE_KOS_ALTERATIONS */
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen64_to_fopencookie_seekfn_defined */

#endif /* __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__ */
#include <libio.h>
#else /* ... */
#ifndef ____funopen64_types_defined
#define ____funopen64_types_defined 1
typedef __off64_t (__LIBKCALL *__funopen64_seekfn_t)(void *__cookie, __off64_t __off, int __whence);
#endif /* !____funopen64_types_defined */

#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__
#ifndef __funopen_to_funopen2_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_readfn_defined 1
__LOCAL_LIBC(funopen_to_funopen2_readfn) ssize_t
(__LIBKCALL funopen_to_funopen2_readfn)(void *cookie, void *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_readfn)(holder->fh_cookie, (char *)buf,
	                                     (int)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_readfn_defined */

#ifndef __funopen_to_funopen2_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_writefn_defined 1
__LOCAL_LIBC(funopen_to_funopen2_writefn) ssize_t
(__LIBKCALL funopen_to_funopen2_writefn)(void *cookie, void const *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_writefn)(holder->fh_cookie, (char const *)buf,
	                                      (int)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_writefn_defined */

#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ */
#ifndef __funopen_to_funopen64_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen64_readfn_defined 1
__LOCAL_LIBC(funopen_to_funopen64_readfn) int
(__LIBKCALL funopen_to_funopen64_readfn)(void *cookie, char *buf, int num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_readfn)(holder->fh_cookie, buf, num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen64_readfn_defined */

#ifndef __funopen_to_funopen64_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen64_writefn_defined 1
__LOCAL_LIBC(funopen_to_funopen64_writefn) int
(__LIBKCALL funopen_to_funopen64_writefn)(void *cookie, char const *buf, int num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_writefn)(holder->fh_cookie, buf, num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen64_writefn_defined */

#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
#if __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
#ifndef __funopen_to_funopen64_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen64_seekfn_defined 1
__LOCAL_LIBC(funopen_to_funopen64_seekfn) off64_t
(__LIBKCALL funopen_to_funopen64_seekfn)(void *cookie, off64_t off, int whence) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_seekfn)(holder->fh_cookie, (__FS_TYPE(off))off, whence);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen64_seekfn_defined */

#else /* __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__ */
#ifndef __funopen64_to_funopen_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen64_to_funopen_seekfn_defined 1
__LOCAL_LIBC(funopen64_to_funopen_seekfn) __FS_TYPE(off)
(__LIBKCALL funopen64_to_funopen_seekfn)(void *cookie, __FS_TYPE(off) off, int whence) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (__FS_TYPE(off))(*holder->fh_seekfn)(holder->fh_cookie, (off64_t)off, whence);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen64_to_funopen_seekfn_defined */

#endif /* __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__ */
#endif /* !... */
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ || ((!__CRT_HAVE_funopen2 || __SIZEOF_OFF64_T__ != __SIZEOF_OFF32_T__) && !__CRT_HAVE_funopen2_64 && ((!__CRT_HAVE_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE_posix_memalign) || !__CRT_HAVE_funopen2)) */
/* >> funopen(3), funopen64(3) */
INTERN ATTR_SECTION(".text.crt.FILE.locked.utility") WUNUSED FILE *
NOTHROW_NCX(LIBCCALL libc_funopen64)(void const *cookie,
                                     __funopen_readfn_t readfn,
                                     __funopen_writefn_t writefn,
                                     __funopen64_seekfn_t seekfn,
                                     __funopen_closefn_t closefn) {
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__ && (defined(__CRT_HAVE_funopen2_64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2)))
	return libc_funopen2_64(cookie,
	                   (__funopen2_readfn_t)readfn,
	                   (__funopen2_writefn_t)writefn,
	                   seekfn, NULL, closefn);
#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ && (__CRT_HAVE_funopen2_64 || ((__CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign) && __CRT_HAVE_funopen2)) */
	FILE *result;
	struct __NAMESPACE_LOCAL_SYM __funopen64_holder *holder;






	holder = (struct __NAMESPACE_LOCAL_SYM __funopen64_holder *)libc_malloc(sizeof(struct __NAMESPACE_LOCAL_SYM __funopen64_holder));
	if unlikely(!holder)
		return NULL;
	holder->fh64_cookie  = (void *)cookie;
	holder->fh64_readfn  = readfn;
	holder->fh64_writefn = writefn;
	holder->fh64_seekfn  = seekfn;
	holder->fh64_closefn = closefn;
#if defined(__CRT_HAVE_funopen2_64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2))
#if __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
	result = libc_funopen2_64(/* cookie:  */ holder,
	                     /* readfn:  */ readfn  ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_readfn  : NULL,
	                     /* writefn: */ writefn ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_writefn : NULL,
	                     /* seekfn:  */ seekfn  ? (__funopen2_64_seekfn_t)&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_seekfn  : NULL,
	                     /* flushfn: */ NULL,
	                     /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
#else /* __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__ */
	result = libc_funopen2_64(/* cookie:  */ holder,
	                     /* readfn:  */ readfn  ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_readfn  : NULL,
	                     /* writefn: */ writefn ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_writefn : NULL,
	                     /* seekfn:  */ seekfn  ? &__NAMESPACE_LOCAL_SYM funopen64_to_funopen2_64_seekfn  : NULL,
	                     /* flushfn: */ NULL,
	                     /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
#endif /* __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__ */
#elif defined(__CRT_HAVE_fopencookie)
	{
		_IO_cookie_io_functions_t ioc_functions;
		ioc_functions.read  = readfn ? (__io_read_fn *)&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_readfn : NULL;
		ioc_functions.write = writefn ? (__io_write_fn *)&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_writefn : NULL;
#if __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
		ioc_functions.seek  = seekfn ? &__NAMESPACE_LOCAL_SYM funopen_to_fopencookie_seekfn : NULL;
#else /* __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__ */
		ioc_functions.seek  = seekfn ? &__NAMESPACE_LOCAL_SYM funopen64_to_fopencookie_seekfn : NULL;
#endif /* __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__ */
		ioc_functions.close = &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn;
		result = crt_fopencookie(holder, readfn && writefn ? "r+" : readfn ? "r" : "w", ioc_functions);
	}
#else /* ... */
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__
#if __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
	result = funopen32(/* cookie:  */ holder,
	                   /* readfn:  */ readfn  ? (__funopen_readfn_t)&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_readfn  : NULL,
	                   /* writefn: */ writefn ? (__funopen_writefn_t)&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_writefn : NULL,
	                   /* seekfn:  */ seekfn  ? (__funopen_seekfn_t)&__NAMESPACE_LOCAL_SYM funopen_to_funopen64_seekfn  : NULL,
	                   /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
#else /* __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__ */
	result = funopen32(/* cookie:  */ holder,
	                   /* readfn:  */ readfn  ? (__funopen_readfn_t)&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_readfn  : NULL,
	                   /* writefn: */ writefn ? (__funopen_writefn_t)&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_writefn : NULL,
	                   /* seekfn:  */ seekfn  ? &__NAMESPACE_LOCAL_SYM funopen64_to_funopen_seekfn  : NULL,
	                   /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
#endif /* __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__ */
#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ */
#if __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
	result = funopen32(/* cookie:  */ holder,
	                   /* readfn:  */ readfn  ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen64_readfn  : NULL,
	                   /* writefn: */ writefn ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen64_writefn : NULL,
	                   /* seekfn:  */ seekfn  ? (__funopen_seekfn_t)&__NAMESPACE_LOCAL_SYM funopen_to_funopen64_seekfn  : NULL,
	                   /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
#else /* __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__ */
	result = funopen32(/* cookie:  */ holder,
	                   /* readfn:  */ readfn  ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen64_readfn  : NULL,
	                   /* writefn: */ writefn ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen64_writefn : NULL,
	                   /* seekfn:  */ seekfn  ? &__NAMESPACE_LOCAL_SYM funopen64_to_funopen_seekfn  : NULL,
	                   /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
#endif /* __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__ */
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
#endif /* !... */
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
	if unlikely(!result)
		libc_free(holder);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
	return result;
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ || (!__CRT_HAVE_funopen2_64 && ((!__CRT_HAVE_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE_posix_memalign) || !__CRT_HAVE_funopen2)) */
}
#endif /* __SIZEOF_OFF64_T__ != __SIZEOF_OFF32_T__ */
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
#include <libc/local/stdstreams.h>
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
#include <libc/errno.h>
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
#include <libc/errno.h>
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
#include <libc/errno.h>
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
#include <libc/errno.h>
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
#include <libc/errno.h>
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
#include <libc/errno.h>
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
#include <libc/local/stdstreams.h>
#include <libc/errno.h>
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
#include <libc/local/stdstreams.h>
#include <libc/errno.h>
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
#include <libc/local/stdstreams.h>
#include <libc/errno.h>
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
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_fgetchar, libc_getchar);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(getchar, libc_getchar);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_fputchar, libc_putchar);
#endif /* __LIBCCALL_IS_LIBDCALL */
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
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_getw, libc_getw);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(getw, libc_getw);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_putw, libc_putw);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(putw, libc_putw);
DEFINE_PUBLIC_ALIAS(fopencookie, libc_fopencookie);
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
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(fprintf_s, libc_fprintf_unlocked);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(fprintf_unlocked, libc_fprintf_unlocked);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(vprintf_s, libc_vprintf_unlocked);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(vprintf_unlocked, libc_vprintf_unlocked);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$printf_s, libd_printf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$printf_unlocked, libd_printf_unlocked);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(printf_s, libc_printf_unlocked);
#endif /* __LIBCCALL_IS_LIBDCALL */
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
DEFINE_PUBLIC_ALIAS(funopen, libc_funopen);
DEFINE_PUBLIC_ALIAS(funopen64, libc_funopen64);
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
