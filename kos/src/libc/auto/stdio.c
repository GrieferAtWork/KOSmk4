/* HASH CRC-32:0x364b068f */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
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
#include "../user/malloc.h"
#include "obstack.h"
#include "../user/signal.h"
#include "../user/stdlib.h"
#include "string.h"
#include "../user/sys.mman.h"
#include "../user/sys.resource.h"
#include "../user/unicode.h"
#include "../user/unistd.h"

DECL_BEGIN

#include "../libc/globals.h"
#ifndef __KERNEL__
#include <asm/os/fcntl.h>
#include <libc/errno.h>
/* >> remove(3)
 * Remove a file or directory `filename' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_remove)(char const *filename) {

	return libd_removeat(__AT_FDCWD, filename);












}
#include <asm/os/fcntl.h>
#include <libc/errno.h>
/* >> remove(3)
 * Remove a file or directory `filename' */
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_remove)(char const *filename) {

	return libc_removeat(__AT_FDCWD, filename);












}
#include <asm/crt/stdio.h>
/* >> setbuf(3)
 * Alias for `setvbuf(stream, buf, _IOFBF, BUFSIZ)' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.utility") ATTR_INOUT(1) void
NOTHROW_NCX(LIBCCALL libc_setbuf)(FILE *__restrict stream,
                                  char *buf) {
	libc_setvbuf(stream, buf,
	        buf ? ___IOFBF : ___IONBF,
	        buf ? __BUFSIZ : 0);
}
#include <libc/template/stdstreams.h>
/* >> getchar(3)
 * Alias for `fgetc(stdin)' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.getc") int
NOTHROW_CB_NCX(LIBCCALL libc_getchar)(void) {
	return libc_fgetc(stdin);
}
#include <libc/template/stdstreams.h>
/* >> putchar(3)
 * Alias for `fputc(ch, stdout)' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.putc") int
NOTHROW_CB_NCX(LIBCCALL libc_putchar)(int ch) {
	return libc_fputc(ch, stdout);
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <asm/crt/stdio.h>
/* >> fgets(3)
 * Read up to `bufsize - 1' bytes of data from `stream', storing them into `buf' stopped when the
 * buffer is full or a line-feed was read (in this case, the line-feed is also written to `buf').
 * Afterwards, append a trailing NUL-character and re-return `buf', or return `NULL' on error. */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.read") WUNUSED ATTR_INOUT(3) ATTR_OUTS(1, 2) char *
NOTHROW_CB_NCX(LIBCCALL libc_fgets)(char *__restrict buf,
                                    __STDC_INT_AS_SIZE_T bufsize,
                                    FILE *__restrict stream) {
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */

		(void)libc_seterrno(ERANGE);

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
		if (ch == '\n') {
			++n; /* Must keep the trailing '\n' at the end of lines! */
			break;
		}
	}
	buf[n] = '\0'; /* NUL-terminate line */
	return buf;
}
/* >> fputs(3)
 * Print a given string `string' to `stream'. This is identical to:
 * >> fwrite(string, sizeof(char), strlen(string), stream); */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.write") ATTR_IN(1) ATTR_INOUT(2) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(LIBCCALL libc_fputs)(char const *__restrict string,
                                    FILE *__restrict stream) {
	__STDC_INT_AS_SIZE_T result;
	result = libc_fwrite(string,
	                sizeof(char),
	                libc_strlen(string),
	                stream);
	return result;
}
#include <libc/template/stdstreams.h>
/* >> puts(3)
 * Print a given string `string', followed by a line-feed to `stdout'. This is identical to:
 * >> fputs(string, stdout);
 * >> putchar('\n');
 * Return the number of written characters, or `EOF' on error */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.write") ATTR_IN(1) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(LIBCCALL libc_puts)(char const *__restrict string) {
	__STDC_INT_AS_SSIZE_T result, temp;
	result = libc_fputs(string, stdout);
	if (result >= 0) {
		temp = libc_fputc('\n', stdout);
		if (temp <= 0) {
			result = temp;
		} else {
			result += temp;
		}
	}
	return result;
}
#include <parts/printf-config.h>
#include <libc/template/stdstreams.h>
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









	if (message) {
		(void)libc_fprintf(stderr, "%s: %m\n", message);
	} else {
		(void)libc_fprintf(stderr, "%m\n");
	}

}
#include <paths.h>
/* >> tmpfile(3), tmpfile64(3)
 * Create and return a new file-stream for accessing a temporary file for reading/writing
 * The file uses an  operating-system provided file descriptor,  however does not have  a
 * proper name anywhere  on the filesystem  (meaning the file's  contents are deleted  as
 * soon as the returned file stream is closed) */
INTERN ATTR_SECTION(".text.crt.FILE.locked.access") WUNUSED FILE *
NOTHROW_RPC(LIBCCALL libc_tmpfile)(void) {
	FILE *result;
	fd_t tmpfd;

	tmpfd = libc_memfd_create(NULL, __MFD_CLOEXEC);


























	if unlikely(tmpfd < 0)
		return NULL;
	result = libc_fdopen(tmpfd, "w+");

	if unlikely(!result)
		(void)libc_close(tmpfd);

	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fprintf(3), vfprintf(3)
 * Print  data  to  `stream',  following  `format'
 * Return the number of successfully printed bytes */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.write.printf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd_fprintf)(FILE *__restrict stream,
                                       char const *__restrict format,
                                       ...) {
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
 * Print  data  to  `stream',  following  `format'
 * Return the number of successfully printed bytes */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.printf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBCCALL libc_fprintf)(FILE *__restrict stream,
                                       char const *__restrict format,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfprintf(stream, format, args);
	va_end(args);
	return result;
}
#include <libc/template/stdstreams.h>
/* >> printf(3), vprintf(3)
 * Print  data  to  `stdout',  following  `format'
 * Return the number of successfully printed bytes */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.printf") ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(LIBCCALL libc_vprintf)(char const *__restrict format,
                                      va_list args) {
	return libc_vfprintf(stdout, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> printf(3), vprintf(3)
 * Print  data  to  `stdout',  following  `format'
 * Return the number of successfully printed bytes */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.write.printf") ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd_printf)(char const *__restrict format,
                                      ...) {
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
 * Print  data  to  `stdout',  following  `format'
 * Return the number of successfully printed bytes */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.printf") ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBCCALL libc_printf)(char const *__restrict format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vprintf(format, args);
	va_end(args);
	return result;
}
#include <hybrid/typecore.h>
#ifndef ____vfscanf_getc_defined
#define ____vfscanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
#if !defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_FORMAT_WORD_T__ != __SIZEOF_INT__
__LOCAL_LIBC(vfscanf_getc) __format_word_t
NOTHROW_CB_NCX(__FORMATPRINTER_CC vfscanf_getc)(void *arg) {
	return (__format_word_t)libc_fgetc((FILE *)arg);
}
#endif /* !__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_FORMAT_WORD_T__ != __SIZEOF_INT__ */
__LOCAL_LIBC(vfscanf_ungetc) ssize_t
NOTHROW_CB_NCX(__FORMATPRINTER_CC vfscanf_ungetc)(void *arg, __format_word_t word) {
	return libc_ungetc((int)(unsigned char)(unsigned int)word, (FILE *)arg);
}
__NAMESPACE_LOCAL_END
#endif /* !____vfscanf_getc_defined */
/* >> fscanf(3), vfscanf(3)
 * Scan  data   from   `stream',   following   `format'
 * Return the number of successfully scanned data items */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.scanf") WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 0) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBCCALL libc_vfscanf)(FILE *__restrict stream,
                                      char const *__restrict format,
                                      va_list args) {
#if defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_FORMAT_WORD_T__ == __SIZEOF_INT__
	return libc_format_vscanf((pformatgetc)(void *)&libc_fgetc,
	                     &__NAMESPACE_LOCAL_SYM vfscanf_ungetc,
	                     (void *)stream,
	                     format, args);
#else /* __LIBCCALL_IS_FORMATPRINTER_CC && __SIZEOF_FORMAT_WORD_T__ == __SIZEOF_INT__ */
	return libc_format_vscanf(&__NAMESPACE_LOCAL_SYM vfscanf_getc,
	                     &__NAMESPACE_LOCAL_SYM vfscanf_ungetc,
	                     (void *)stream,
	                     format, args);
#endif /* !__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_FORMAT_WORD_T__ != __SIZEOF_INT__ */
}
#include <libc/template/stdstreams.h>
/* >> scanf(3), vscanf(3)
 * Scan data from `stdin', following `format'
 * Return the number of successfully scanned data items */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.scanf") WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 0) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBCCALL libc_vscanf)(char const *__restrict format,
                                     va_list args) {
	return libc_vfscanf(stdin, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fscanf(3), vfscanf(3)
 * Scan  data   from   `stream',   following   `format'
 * Return the number of successfully scanned data items */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 3) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd_fscanf)(FILE *__restrict stream,
                                      char const *__restrict format,
                                      ...) {
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
 * Scan  data   from   `stream',   following   `format'
 * Return the number of successfully scanned data items */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.scanf") WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 3) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBCCALL libc_fscanf)(FILE *__restrict stream,
                                      char const *__restrict format,
                                      ...) {
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 2) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd_scanf)(char const *__restrict format,
                                     ...) {
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
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.scanf") WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 2) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBCCALL libc_scanf)(char const *__restrict format,
                                     ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vscanf(format, args);
	va_end(args);
	return result;
}
#include <libc/template/stdstreams.h>
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.read") WUNUSED ATTR_OUT(1) char *
NOTHROW_CB_NCX(LIBCCALL libc_gets)(char *__restrict buf) {
	return libc_fgets(buf, INT_MAX, stdin);
}
#endif /* !__KERNEL__ */
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
#include <asm/crt/stdio.h>
#ifndef ____vsscanf_getc_defined
#define ____vsscanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsscanf_getc) __format_word_t
NOTHROW_NCX(FORMATPRINTER_CC vsscanf_getc)(void *arg) {
	unsigned char const *reader = *(unsigned char const **)arg;
	unsigned char result        = *reader++;
	if (!result)
		return __EOF;
	*(unsigned char const **)arg = reader;
	return (__format_word_t)result;
}
__LOCAL_LIBC(vsscanf_ungetc) ssize_t
NOTHROW(FORMATPRINTER_CC vsscanf_ungetc)(void *arg, __format_word_t UNUSED(word)) {
	--(*(unsigned char const **)arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsscanf_getc_defined */
/* >> sscanf(3), vsscanf(3)
 * Scan data from a given `input' string, following `format'
 * Return  the  number  of successfully  scanned  data items */
INTERN ATTR_SECTION(".text.crt.unicode.static.format.scanf") WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 0) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc_vsscanf)(char const *__restrict input,
                                   char const *__restrict format,
                                   va_list args) {
	return libc_format_vscanf(&__NAMESPACE_LOCAL_SYM vsscanf_getc,
	                     &__NAMESPACE_LOCAL_SYM vsscanf_ungetc,
	                     (void *)&input, format, args);
}
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sscanf(3), vsscanf(3)
 * Scan data from a given `input' string, following `format'
 * Return  the  number  of successfully  scanned  data items */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.static.format.scanf") ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 3) __STDC_INT_AS_SIZE_T
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
/* >> sscanf(3), vsscanf(3)
 * Scan data from a given `input' string, following `format'
 * Return  the  number  of successfully  scanned  data items */
INTERN ATTR_SECTION(".text.crt.unicode.static.format.scanf") ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 3) __STDC_INT_AS_SIZE_T
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
/* >> sprintf(3), vsprintf(3)
 * Print  a  formatted  string  to  a  given  in-member  string  buffer  `buf'
 * Return the number of written characters, excluding a trailing NUL-character */
INTERN ATTR_SECTION(".text.crt.unicode.static.format.printf") ATTR_IN(2) ATTR_LIBC_PRINTF(2, 0) ATTR_OUT(1) __STDC_INT_AS_SSIZE_T
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
 * Print  a  formatted  string  to  a  given  in-member  string  buffer  `buf'
 * Return the number of written characters, excluding a trailing NUL-character */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_IN(2) ATTR_LIBC_PRINTF(2, 3) ATTR_OUT(1) __STDC_INT_AS_SIZE_T
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
 * Print  a  formatted  string  to  a  given  in-member  string  buffer  `buf'
 * Return the number of written characters, excluding a trailing NUL-character */
INTERN ATTR_SECTION(".text.crt.unicode.static.format.printf") ATTR_IN(2) ATTR_LIBC_PRINTF(2, 3) ATTR_OUT(1) __STDC_INT_AS_SIZE_T
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
#define ____format_snprintf_data_defined
struct __format_snprintf_data {
	char         *__sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
	__SIZE_TYPE__ __sd_bufsiz; /* Remaining buffer size. */
};
#endif /* !____format_snprintf_data_defined */
/* >> snprintf(3), vsnprintf(3)
 * Print  a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing  NUL-
 * character), and never write more than `buflen' characters to `buf' */
INTERN ATTR_SECTION(".text.crt.unicode.static.format.printf") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SIZE_T
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
	if (result >= 0) {
		if (data.__sd_bufsiz != 0) {
			*data.__sd_buffer = '\0';
		} else {
			/* Special handling for when the buffer was truncated.
			 *
			 * This part right here isn't mandated by any of the specs and wasn't
			 * implemented in the original version of this function which  simply
			 * left the string without any NUL terminator.
			 *
			 * However, as it turns out `nano(1)' around `/src/help.c:55` has line:
			 * >> int length = help_line_len(ptr);
			 * >> char *oneline = nmalloc(length + 1);
			 * >>
			 * >> snprintf(oneline, length + 1, "%s", ptr);  // <<---- This line
			 * >> free(openfile->current->data);
			 * >> openfile->current->data = oneline;
			 *
			 * Here, it uses a `length' (which is smaller than `strlen(ptr)') as
			 * the limit in a call to snprintf(), using it to essentially copy a
			 * small part of the larger help string into a line-buffer.
			 *
			 * However,  it also expects  and assumes that  this buffer gets NUL
			 * terminated  even when truncated (which isn't explicitly specified
			 * by the specs; i.e. `man 3 snprintf'), and any program that relies
			 * on this relies on system-specific behavior.
			 *
			 * Amazingly enough,  even without  explicitly NUL  terminating it  at
			 * the correct location, nano didn't crash but occasionally  displayed
			 * some garbled lines, as well as the line-feed that always got copied
			 * at the end of a paragraph in its escaped form '^@'.
			 *
			 * But then again, NUL-termination on  truncation seems to be  something
			 * that happens on linux, and after all: KOS tries to be as much API/ABI
			 * compatible with linux as possible, so: in this goes! */
			if (buflen != 0)
				buf[buflen - 1] = '\0';
		}
	}
	return result;
}
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> snprintf(3), vsnprintf(3)
 * Print  a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing  NUL-
 * character), and never write more than `buflen' characters to `buf' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) ATTR_OUTS(1, 2) __STDC_INT_AS_SIZE_T
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
 * Print  a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing  NUL-
 * character), and never write more than `buflen' characters to `buf' */
INTERN ATTR_SECTION(".text.crt.unicode.static.format.printf") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) ATTR_OUTS(1, 2) __STDC_INT_AS_SIZE_T
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
#include <hybrid/host.h>
/* >> dprintf(3), vdprintf(3) */
INTERN ATTR_SECTION(".text.crt.io.write") ATTR_FDWRITE(1) ATTR_IN(2) ATTR_LIBC_PRINTF(2, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(LIBCCALL libc_vdprintf)(fd_t fd,
                                    char const *__restrict format,
                                    va_list args) {
	return libc_format_vprintf(&libc_write_printer,
	                      (void *)(__UINTPTR_TYPE__)(__CRT_PRIVATE_UINT(__SIZEOF_FD_T__))fd,
	                      format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dprintf(3), vdprintf(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.io.write") ATTR_FDWRITE(1) ATTR_IN(2) ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T
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
INTERN ATTR_SECTION(".text.crt.io.write") ATTR_FDWRITE(1) ATTR_IN(2) ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T
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
#include <asm/os/fcntl.h>
#include <libc/errno.h>
/* >> removeat(3)
 * Remove a file or directory `filename' relative to a given base directory `dirfd' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(2) int
NOTHROW_RPC(LIBDCALL libd_removeat)(fd_t dirfd,
                                    char const *filename) {

	return libd_unlinkat(dirfd, filename, __AT_REMOVEREG | __AT_REMOVEDIR);












}
#include <asm/os/fcntl.h>
#include <libc/errno.h>
/* >> removeat(3)
 * Remove a file or directory `filename' relative to a given base directory `dirfd' */
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(2) int
NOTHROW_RPC(LIBCCALL libc_removeat)(fd_t dirfd,
                                    char const *filename) {

	return libc_unlinkat(dirfd, filename, __AT_REMOVEREG | __AT_REMOVEDIR);












}
/* >> tmpnam(3), tmpnam_r(3) */
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED ATTR_OUT_OPT(1) char *
NOTHROW_NCX(LIBCCALL libc_tmpnam_r)(char *buf) {
	return buf ? libc_tmpnam(buf) : NULL;
}
/* >> setbuffer(3)
 * Specify the location and size for the buffer to-be used by `stream' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.utility") ATTR_INOUT(1) void
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
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.utility") ATTR_INOUT(1) void
NOTHROW_NCX(LIBCCALL libc_setlinebuf)(FILE *__restrict stream) {
	libc_setvbuf(stream, NULL, ___IOLBF, 0);
}
__NAMESPACE_LOCAL_BEGIN
struct __vasnprintf_data {
	char  *vapd_obf; /* [0..1][MAYBE(owned)] Original output buffer. */
	char  *vapd_buf; /* [0..1][MAYBE(owned)] Output buffer base pointer. */
	char  *vapd_ptr; /* [0..vapd_cnt] Pointer into `vapd_buf' for where to continue writing */
	size_t vapd_cnt; /* # of remaining, available bytes in `vapd_ptr' (excluding space for trailing NUL) */
};
__LOCAL_LIBC(vasnprintf_printer) ssize_t
NOTHROW_NCX(FORMATPRINTER_CC vasnprintf_printer)(void *arg, char const *__restrict data, size_t datalen) {
	struct __vasnprintf_data *cookie;
	cookie = (struct __vasnprintf_data *)arg;

	/* Check for sufficient space. */
	if (datalen > cookie->vapd_cnt) {
		char *newbuf;
		size_t reqlen;
		reqlen = (cookie->vapd_ptr - cookie->vapd_buf) * sizeof(char);
		reqlen += datalen * sizeof(char);
		reqlen += sizeof(char); /* For trailing NUL */
		if (cookie->vapd_buf == cookie->vapd_obf) {
			size_t offset;
#if defined(__CRT_HAVE_realloc_in_place) || defined(__CRT_HAVE__expand)
			newbuf = (char *)libc_realloc_in_place(cookie->vapd_obf, reqlen);
			if (newbuf) {
				cookie->vapd_cnt = datalen;
				goto dowrite;
			}
#endif /* __CRT_HAVE_realloc_in_place || __CRT_HAVE__expand */

			/* Allocate the initial version of our own heap-buffer */
			reqlen += 512 * sizeof(char);
			newbuf = (char *)libc_malloc(reqlen);
			if unlikely(!newbuf) {
				reqlen -= 512 * sizeof(char);
				newbuf = (char *)libc_malloc(reqlen);
				if unlikely(!newbuf)
					goto err;
			}
#if defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize)
			reqlen = libc_malloc_usable_size(newbuf) - sizeof(char);
#endif /* __CRT_HAVE_malloc_usable_size || __CRT_HAVE__msize */
			offset = (size_t)(cookie->vapd_ptr - cookie->vapd_buf);
			/* Copy already-printed data off of the initial buffer */
			newbuf = (char *)libc_memcpy(newbuf, cookie->vapd_buf,
			                        offset * sizeof(char));
			cookie->vapd_buf = newbuf;
			cookie->vapd_ptr = newbuf + offset;
			cookie->vapd_cnt = (reqlen / sizeof(char)) - offset;
		} else {
			size_t offset;

#if defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
			/* Already on secondary buffer -> try to realloc to a larger size */
			reqlen += 512 * sizeof(char);
			newbuf = (char *)libc_realloc(cookie->vapd_buf, reqlen);
			if unlikely(!newbuf) {
				reqlen -= 512 * sizeof(char);
				newbuf = (char *)libc_realloc(cookie->vapd_buf, reqlen);
				if unlikely(!newbuf)
					goto err;
			}
#if defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize)
			reqlen = libc_malloc_usable_size(newbuf) - sizeof(char);
#endif /* __CRT_HAVE_malloc_usable_size || __CRT_HAVE__msize */
			offset = (size_t)(cookie->vapd_ptr - cookie->vapd_buf);
			cookie->vapd_buf = newbuf;
			cookie->vapd_ptr = newbuf + offset;
			cookie->vapd_cnt = (reqlen / sizeof(char)) - offset;
#else /* __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc */
			/* No realloc(3) function -> can only use malloc */
			reqlen += 512 * sizeof(char);
			newbuf = (char *)libc_malloc(reqlen);
			if unlikely(!newbuf) {
				reqlen -= 512 * sizeof(char);
				newbuf = (char *)libc_malloc(reqlen);
				if unlikely(!newbuf)
					goto err;
			}
#if defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize)
			reqlen = libc_malloc_usable_size(newbuf) - sizeof(char);
#endif /* __CRT_HAVE_malloc_usable_size || __CRT_HAVE__msize */
			offset = (size_t)(cookie->vapd_ptr - cookie->vapd_buf);
			newbuf = (char *)libc_memcpy(newbuf, cookie->vapd_buf, offset * sizeof(char));
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
			libc_free(cookie->vapd_buf);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
			cookie->vapd_buf = newbuf;
			cookie->vapd_ptr = newbuf + offset;
			cookie->vapd_cnt = (reqlen / sizeof(char)) - offset;
#endif /* !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc */
		}
	}

	/* Do the write! */
dowrite:
	cookie->vapd_ptr = (char *)libc_mempcpy(cookie->vapd_ptr, data, datalen * sizeof(char));
	cookie->vapd_cnt -= datalen;
	return (ssize_t)datalen;
err:
	return -1; /* Stop printing! */
}
__NAMESPACE_LOCAL_END
/* >> asnprintf(3), vasnprintf(3)
 * Given a malloc'd `heapbuf...+=*p_buflen' (where `*p_buflen' is the number of BYTES), write
 * a  given `format'-string to said buffer. If the  buffer is too small, it will be realloc'd
 * (or a new buffer  is alloc'd, and the  given `heapbuf' is free'd  upon success, so- as  to
 * prevent any problem relating to printing failing after a preceding, moving realloc)
 *
 * @param: p_buflen: [in]  The total allocated size (in bytes) of buffer
 *                   [out] The number of bytes written to `*heapbuf' (EXCLUDING the trailing NUL char)
 *                   [out] Unchanged when `NULL' is returned
 * @return: * :   A malloc'd buffer derived from `heapbuf' and populated as specified by `format'->
 * @return: NULL: Failed  to allocated sufficient  heap memory. In  this case, the caller-given
 *                `heapbuf' will still be allocated (iow: must be free'd by the caller), though
 *                its contents are left undefined. */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.putc") WUNUSED ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) ATTR_LIBC_PRINTF(3, 0) char *
NOTHROW_NCX(LIBCCALL libc_vasnprintf)(char *heapbuf,
                                      size_t *p_buflen,
                                      char const *format,
                                      va_list args) {
	size_t result_buflen;
	struct __NAMESPACE_LOCAL_SYM __vasnprintf_data cookie;
	cookie.vapd_obf = heapbuf;
	cookie.vapd_buf = heapbuf;
	cookie.vapd_ptr = heapbuf;
	cookie.vapd_cnt = *p_buflen;

	/* Allocate an initial buffer if none was provided by the caller. */
	if (!cookie.vapd_buf || !cookie.vapd_cnt) {
		cookie.vapd_obf = NULL;
		cookie.vapd_cnt = 512;
		cookie.vapd_buf = (char *)libc_malloc(512 * sizeof(char));
		if unlikely(!cookie.vapd_buf) {
			cookie.vapd_cnt = 1;
			cookie.vapd_buf = (char *)libc_malloc(sizeof(char));
			if unlikely(!cookie.vapd_buf)
				return NULL;
		}
		cookie.vapd_ptr = cookie.vapd_buf;
	}

	/* Do the print. */
	if unlikely(libc_format_vprintf(&__NAMESPACE_LOCAL_SYM vasnprintf_printer,
	                           &cookie, format, args) < 0)
		goto err;

	/* Realloc to shrink result buffer to its minimal size. */
	result_buflen = (size_t)(cookie.vapd_ptr - cookie.vapd_buf);
	if (cookie.vapd_buf == cookie.vapd_obf) {

		/* Still using caller-given buffer -> must use realloc_in_place! */
		libc_realloc_in_place(cookie.vapd_obf, (result_buflen + 1) * sizeof(char));

	} else {

		char *result;
		result = (char *)libc_realloc(cookie.vapd_buf, (result_buflen + 1) * sizeof(char));
		if likely(result != NULL)
			cookie.vapd_buf = result;

	}

	/* Ensure NUL-termination */
	cookie.vapd_buf[result_buflen] = '\0';
	*p_buflen = result_buflen;
	return cookie.vapd_buf;
err:

	if (cookie.vapd_buf != cookie.vapd_obf)
		libc_free(cookie.vapd_buf);

	return NULL;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> asnprintf(3), vasnprintf(3)
 * Given a malloc'd `heapbuf...+=*p_buflen' (where `*p_buflen' is the number of BYTES), write
 * a  given `format'-string to said buffer. If the  buffer is too small, it will be realloc'd
 * (or a new buffer  is alloc'd, and the  given `heapbuf' is free'd  upon success, so- as  to
 * prevent any problem relating to printing failing after a preceding, moving realloc)
 *
 * @param: p_buflen: [in]  The total allocated size (in bytes) of buffer
 *                   [out] The number of bytes written to `*heapbuf' (EXCLUDING the trailing NUL char)
 *                   [out] Unchanged when `NULL' is returned
 * @return: * :   A malloc'd buffer derived from `heapbuf' and populated as specified by `format'->
 * @return: NULL: Failed  to allocated sufficient  heap memory. In  this case, the caller-given
 *                `heapbuf' will still be allocated (iow: must be free'd by the caller), though
 *                its contents are left undefined. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.unlocked.write.putc") WUNUSED ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) ATTR_LIBC_PRINTF(3, 4) char *
NOTHROW_NCX(VLIBDCALL libd_asnprintf)(char *__restrict heapbuf,
                                      size_t *__restrict p_buflen,
                                      char const *__restrict format,
                                      ...) {
	char *result;
	va_list args;
	va_start(args, format);
	result = libc_vasnprintf(heapbuf, p_buflen, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> asnprintf(3), vasnprintf(3)
 * Given a malloc'd `heapbuf...+=*p_buflen' (where `*p_buflen' is the number of BYTES), write
 * a  given `format'-string to said buffer. If the  buffer is too small, it will be realloc'd
 * (or a new buffer  is alloc'd, and the  given `heapbuf' is free'd  upon success, so- as  to
 * prevent any problem relating to printing failing after a preceding, moving realloc)
 *
 * @param: p_buflen: [in]  The total allocated size (in bytes) of buffer
 *                   [out] The number of bytes written to `*heapbuf' (EXCLUDING the trailing NUL char)
 *                   [out] Unchanged when `NULL' is returned
 * @return: * :   A malloc'd buffer derived from `heapbuf' and populated as specified by `format'->
 * @return: NULL: Failed  to allocated sufficient  heap memory. In  this case, the caller-given
 *                `heapbuf' will still be allocated (iow: must be free'd by the caller), though
 *                its contents are left undefined. */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.putc") WUNUSED ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) ATTR_LIBC_PRINTF(3, 4) char *
NOTHROW_NCX(VLIBCCALL libc_asnprintf)(char *__restrict heapbuf,
                                      size_t *__restrict p_buflen,
                                      char const *__restrict format,
                                      ...) {
	char *result;
	va_list args;
	va_start(args, format);
	result = libc_vasnprintf(heapbuf, p_buflen, format, args);
	va_end(args);
	return result;
}
#include <libc/errno.h>
#include <asm/os/stdio.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
struct __memopen_cookie {
	byte_t *moc_base; /* [1..1] Base-pointer */
	byte_t *moc_cur;  /* [1..1] Current position */
	byte_t *moc_end;  /* [1..1] End-pointer */
};

__LOCAL_LIBC(memopen_read) ssize_t
NOTHROW_NCX(LIBCCALL memopen_read)(void *cookie, void *buf, size_t num_bytes) {
	size_t maxlen;
	struct __memopen_cookie *me;
	me = (struct __memopen_cookie *)cookie;
	maxlen = (size_t)(me->moc_end - me->moc_cur);
	if (maxlen > num_bytes)
		maxlen = num_bytes;
	libc_memcpy(buf, me->moc_cur, maxlen);
	me->moc_cur += maxlen;
	return (size_t)maxlen;
}

__LOCAL_LIBC(memopen_write) ssize_t
NOTHROW_NCX(LIBCCALL memopen_write)(void *cookie, void const *buf, size_t num_bytes) {
	size_t maxlen;
	struct __memopen_cookie *me;
	me = (struct __memopen_cookie *)cookie;
	maxlen = (size_t)(me->moc_end - me->moc_cur);
	if (maxlen > num_bytes)
		maxlen = num_bytes;
	libc_memcpy(me->moc_cur, buf, maxlen);
	me->moc_cur += maxlen;
	return (size_t)maxlen;
}

__LOCAL_LIBC(memopen_seek) off64_t
NOTHROW(LIBCCALL memopen_seek)(void *cookie, off64_t off, int whence) {
	pos64_t newpos;
	struct __memopen_cookie *me;
	size_t maxlen;
	me = (struct __memopen_cookie *)cookie;
	newpos = (pos64_t)off;
	maxlen = (size_t)(me->moc_end - me->moc_cur);
	switch (whence) {

	case SEEK_SET:
		break;

	case SEEK_CUR:
		newpos += (size_t)(me->moc_cur - me->moc_base);
		if unlikely((off64_t)newpos < 0)
			goto err_EOVERFLOW;
		break;

	case SEEK_END:
		newpos += maxlen;
		if unlikely((off64_t)newpos < 0)
			goto err_EOVERFLOW;
		break;

	default:
#ifdef EINVAL
		return (off64_t)libc_seterrno(EINVAL);
#else /* EINVAL */
		return (off64_t)libc_seterrno(1);
#endif /* !EINVAL */
	}
	if (newpos > maxlen)
		newpos = maxlen;
	me->moc_cur = me->moc_base + (size_t)newpos;
	return (off64_t)newpos;
err_EOVERFLOW:
#ifdef EOVERFLOW
	return (off64_t)libc_seterrno(EOVERFLOW);
#else /* EOVERFLOW */
	return (off64_t)libc_seterrno(1);
#endif /* !EOVERFLOW */
}

__LOCAL_LIBC(memopen_close) int
NOTHROW(LIBCCALL memopen_close)(void *cookie) {
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(cookie);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return 0;
}
__NAMESPACE_LOCAL_END
/* >> fmemopen(3) */
INTERN ATTR_SECTION(".text.crt.FILE.locked.access") WUNUSED ATTR_IN(3) ATTR_INOUTS(1, 2) FILE *
NOTHROW_NCX(LIBCCALL libc_fmemopen)(void *mem,
                                    size_t len,
                                    char const *modes) {
	FILE *result;
	struct __NAMESPACE_LOCAL_SYM __memopen_cookie *magic;
	magic = (struct __NAMESPACE_LOCAL_SYM __memopen_cookie *)libc_malloc(sizeof(struct __NAMESPACE_LOCAL_SYM __memopen_cookie));
	if unlikely(!magic)
		return NULL;
	magic->moc_base = (byte_t *)mem;
	magic->moc_cur  = (byte_t *)mem;
	magic->moc_end  = (byte_t *)mem + len;
	/* Open a custom file-stream. */
	result = libc_funopen2_64(magic,
	                     &__NAMESPACE_LOCAL_SYM memopen_read,
	                     (libc_strchr(modes, 'w') || libc_strchr(modes, '+'))
	                     ? &__NAMESPACE_LOCAL_SYM memopen_write
	                     : NULL,
	                     &__NAMESPACE_LOCAL_SYM memopen_seek,
	                     NULL,
	                     &__NAMESPACE_LOCAL_SYM memopen_close);

	if unlikely(!result)
		libc_free(magic);

	return result;
}
#include <libc/errno.h>
#include <bits/types.h>
#include <asm/os/stdio.h>
#include <hybrid/__overflow.h>
__NAMESPACE_LOCAL_BEGIN
struct __memstream_file {
	byte_t **mf_pbase; /* [1..1] Pointer to the user-defined base field. */
	size_t  *mf_psize; /* [1..1] Pointer to the user-defined size field. */
	byte_t  *mf_base;  /* [0..1][owned] Allocated base pointer. */
	byte_t  *mf_ptr;   /* [0..1] Current read/write pointer (May be located beyond `mf_end'; allocated lazily during writes). */
	byte_t  *mf_end;   /* [0..1] Allocated buffer end pointer. */
};

__LOCAL_LIBC(memstream_read) ATTR_OUTS(2, 3) ssize_t
NOTHROW_NCX(LIBCCALL memstream_read)(void *cookie, void *buf, size_t num_bytes) {
	struct __memstream_file *me;
	size_t maxread;
	me = (struct __memstream_file *)cookie;
	maxread = me->mf_end - me->mf_ptr;
	if (maxread > num_bytes)
		maxread = num_bytes;
	libc_memcpy(buf, me->mf_ptr, maxread);
	me->mf_ptr += maxread;
	return (ssize_t)maxread;
}

__LOCAL_LIBC(memstream_write) ATTR_INS(2, 3) ssize_t
NOTHROW_NCX(LIBCCALL memstream_write)(void *cookie, void const *buf, size_t num_bytes) {
	struct __memstream_file *me;
	size_t new_alloc, result = 0;
	byte_t *new_buffer;
	me = (struct __memstream_file *)cookie;
	if likely(me->mf_ptr < me->mf_end) {
		result = me->mf_end - me->mf_ptr;
		if (result > num_bytes)
			result = num_bytes;
		libc_memcpy(me->mf_ptr, buf, num_bytes);
		me->mf_ptr += result;
		buf = (byte_t const *)buf + result;
		num_bytes -= result;
	}
	if (!num_bytes)
		goto done;
	/* Allocate more memory. */
	new_alloc = (size_t)(me->mf_ptr - me->mf_base);
	if unlikely(__hybrid_overflow_uadd(new_alloc, num_bytes, &new_alloc))
		goto err_EOVERFLOW;
#if defined(__CRT_HAVE_recalloc) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize)))
	/* Try  to use  recalloc() to  do the  zero-initialization for us.
	 * Since this is the only place where a buffer is ever  allocated,
	 * this also means that any newly allocated buffer space is always
	 * zero-initialized, and we  don't have to  worry about any  delta
	 * between `end - base' and `malloc_usable_size()'. */
	new_buffer = (byte_t *)libc_recalloc(me->mf_base,
	                                (new_alloc + 1) *
	                                sizeof(char));
	if unlikely(!new_buffer)
		goto err;
#else /* __CRT_HAVE_recalloc || ((__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_malloc_usable_size || __CRT_HAVE__msize)) */
	new_buffer = (byte_t *)libc_realloc(me->mf_base,
	                               (new_alloc + 1) *
	                               sizeof(char));
	if unlikely(!new_buffer)
		goto err;
	{
		/* Zero-initialize newly allocated memory (that won't be overwritten in a moment) */
		size_t oldsiz, baspos;
		oldsiz = (size_t)(me->mf_end - me->mf_base);
		baspos = (size_t)(me->mf_ptr - me->mf_base);
		if (baspos > oldsiz)
			libc_bzero(new_buffer + oldsiz, (baspos - oldsiz) * sizeof(char));
	}
#endif /* !__CRT_HAVE_recalloc && ((!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_malloc_usable_size && !__CRT_HAVE__msize)) */
	me->mf_ptr  = new_buffer + (me->mf_ptr - me->mf_base);
	me->mf_base = new_buffer;
	me->mf_end  = new_buffer + new_alloc;
	/* Copy data into the new portion of the buf. */
	libc_memcpy(me->mf_ptr, buf, num_bytes);
	*me->mf_end = 0; /* NUL-termination. */
	result += num_bytes;
	/* Update the user-given pointer locations with buf parameters. */
	*me->mf_pbase = me->mf_base;
	*me->mf_psize = (size_t)(me->mf_end - me->mf_base);
done:
	return (ssize_t)result;
err_EOVERFLOW:
#ifdef EOVERFLOW
	libc_seterrno(EOVERFLOW);
#else /* EOVERFLOW */
	libc_seterrno(1);
#endif /* !EOVERFLOW */
err:
	return -1;
}

__LOCAL_LIBC(memstream_seek) off64_t
NOTHROW(LIBCCALL memstream_seek)(void *cookie, off64_t off, int whence) {
	struct __memstream_file *me;
	off64_t new_pos;
	me = (struct __memstream_file *)cookie;
	new_pos = (off64_t)(pos64_t)(size_t)(me->mf_ptr - me->mf_base);
	switch (whence) {

	case __SEEK_SET:
		new_pos = off;
		break;

	case __SEEK_CUR:
		new_pos += off;
		break;

	case __SEEK_END:
		new_pos = (size_t)(me->mf_end - me->mf_base) + off;
		break;

	default:
#ifdef EINVAL
		return (off64_t)libc_seterrno(EINVAL);
#else /* EINVAL */
		return (off64_t)libc_seterrno(1);
#endif /* !EINVAL */
	}
	if unlikely(new_pos < 0)
		goto err_EOVERFLOW;
	/* Update the actual buffer read/write pointer. */
	if unlikely(__hybrid_overflow_uadd((uintptr_t)me->mf_base,
	                                   (pos64_t)new_pos,
	                                   (uintptr_t *)&me->mf_ptr))
		goto err_EOVERFLOW;
	return (off64_t)new_pos;
err_EOVERFLOW:
#ifdef EOVERFLOW
	return (off64_t)libc_seterrno(EOVERFLOW);
#else /* EOVERFLOW */
	return (off64_t)libc_seterrno(1);
#endif /* !EOVERFLOW */
}

__LOCAL_LIBC(memstream_close) int
NOTHROW(LIBCCALL memstream_close)(void *cookie) {
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(cookie);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return 0;
}

__NAMESPACE_LOCAL_END
/* >> open_memstream(3) */
INTERN ATTR_SECTION(".text.crt.FILE.locked.access") WUNUSED NONNULL((1, 2)) FILE *
NOTHROW_NCX(LIBCCALL libc_open_memstream)(char **bufloc,
                                          size_t *sizeloc) {
	FILE *result;
	struct __NAMESPACE_LOCAL_SYM __memstream_file *magic;
	magic = (struct __NAMESPACE_LOCAL_SYM __memstream_file *)libc_malloc(sizeof(struct __NAMESPACE_LOCAL_SYM __memstream_file));
	if unlikely(!magic)
		return NULL;
	magic->mf_pbase = (byte_t **)bufloc;
	magic->mf_psize = sizeloc;
	magic->mf_base  = NULL;
	magic->mf_ptr   = NULL;
	magic->mf_end   = NULL;
	/* Open a custom file-stream. */
	result = libc_funopen2_64(magic,
	                     &__NAMESPACE_LOCAL_SYM memstream_read,
	                     &__NAMESPACE_LOCAL_SYM memstream_write,
	                     &__NAMESPACE_LOCAL_SYM memstream_seek,
	                     NULL,
	                     &__NAMESPACE_LOCAL_SYM memstream_close);

	if unlikely(!result)
		libc_free(magic);

	return result;
}
#include <hybrid/__assert.h>
/* >> getdelim(3) */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.read") WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) ATTR_INOUT(4) ssize_t
NOTHROW_CB_NCX(LIBCCALL libc_getdelim)(char **__restrict lineptr,
                                       size_t *__restrict pcount,
                                       int delimiter,
                                       FILE *__restrict stream) {
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
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.read") WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) ATTR_INOUT(3) ssize_t
NOTHROW_CB_NCX(LIBCCALL libc_getline)(char **__restrict lineptr,
                                      size_t *__restrict pcount,
                                      FILE *__restrict stream) {
	return libc_getdelim(lineptr, pcount, '\n', stream);
}
#include <libc/template/stdstreams.h>
/* >> getchar_unlocked(3)
 * Same as `getchar()', but performs I/O without acquiring a lock to `stdin' */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.getc") int
NOTHROW_CB_NCX(LIBCCALL libc_getchar_unlocked)(void) {
	return libc_fgetc_unlocked(stdin);
}
#include <libc/template/stdstreams.h>
/* >> putchar_unlocked(3)
 * Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.putc") int
NOTHROW_CB_NCX(LIBCCALL libc_putchar_unlocked)(int ch) {
	return libc_fputc_unlocked(ch, stdout);
}
/* >> __overflow(3)
 * This is essentially Glibc's version of `_flsbuf(3)' (but sadly not binary compatible) */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.write") ATTR_INOUT(1) int
NOTHROW_CB_NCX(LIBCCALL libc___overflow)(FILE *stream,
                                         int ch) {
	return libc__flsbuf(ch, stream);
}
/* >> getw(3)
 * Similar to `getc()', but read 2 bytes */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.getc") ATTR_INOUT(1) int
NOTHROW_CB_NCX(LIBCCALL libc_getw)(FILE *__restrict stream) {
	u16 result;
	return libc_fread(&result, sizeof(result), 1, stream)
	       ? (int)result
	       : (int)EOF;
}
/* >> putw(3)
 * Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
INTERN ATTR_SECTION(".text.crt.FILE.locked.write.putc") ATTR_INOUT(2) int
NOTHROW_CB_NCX(LIBCCALL libc_putw)(int w,
                                   FILE *__restrict stream) {
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
#define ____fopencookie_holder_defined
struct __fopencookie_holder {
	void                     *foch_cookie; /* User-defined `magic_cookie' */
	_IO_cookie_io_functions_t foch_funcs;  /* Cookie functions */
};
__NAMESPACE_LOCAL_END
#endif /* !____fopencookie_holder_defined */
#ifndef __fopencookie_to_funopen_closefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_closefn_defined
__LOCAL_LIBC(fopencookie_to_funopen_closefn) int
NOTHROW_CB(__LIBKCALL fopencookie_to_funopen_closefn)(void *cookie) {
	int result = 0;
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	if (holder->foch_funcs.close != NULL)
		result = (*holder->foch_funcs.close)(holder->foch_cookie);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(holder);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return result;
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_closefn_defined */

#if !defined(__BUILDING_LIBC) && defined(__CRT_HAVE_funopen64) && __SIZEOF_INT__ == __SIZEOF_SIZE_T__
#ifndef __fopencookie_to_funopen_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_readfn_defined
__LOCAL_LIBC(fopencookie_to_funopen_readfn) ATTR_OUTS(2, 3) int
NOTHROW_CB_NCX(__LIBKCALL fopencookie_to_funopen_readfn)(void *cookie, char *buf, int num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (int)(*holder->foch_funcs.read)(holder->foch_cookie, buf, (size_t)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_readfn_defined */

#ifndef __fopencookie_to_funopen_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_writefn_defined
__LOCAL_LIBC(fopencookie_to_funopen_writefn) ATTR_INS(2, 3) int
NOTHROW_CB_NCX(__LIBKCALL fopencookie_to_funopen_writefn)(void *cookie, char const *buf, int num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (int)(*holder->foch_funcs.write)(holder->foch_cookie, buf, (size_t)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_writefn_defined */

#ifndef __fopencookie_to_funopen64_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen64_seekfn_defined
__LOCAL_LIBC(fopencookie_to_funopen64_seekfn) off64_t
NOTHROW_CB(__LIBKCALL fopencookie_to_funopen64_seekfn)(void *cookie, off64_t off, int whence) {
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
#define __fopencookie_to_funopen_readfn_defined
__LOCAL_LIBC(fopencookie_to_funopen_readfn) ATTR_OUTS(2, 3) int
NOTHROW_CB_NCX(__LIBKCALL fopencookie_to_funopen_readfn)(void *cookie, char *buf, int num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (int)(*holder->foch_funcs.read)(holder->foch_cookie, buf, (size_t)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_readfn_defined */

#ifndef __fopencookie_to_funopen_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_writefn_defined
__LOCAL_LIBC(fopencookie_to_funopen_writefn) ATTR_INS(2, 3) int
NOTHROW_CB_NCX(__LIBKCALL fopencookie_to_funopen_writefn)(void *cookie, char const *buf, int num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (int)(*holder->foch_funcs.write)(holder->foch_cookie, buf, (size_t)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_writefn_defined */

#ifndef __fopencookie_to_funopen_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_seekfn_defined
__LOCAL_LIBC(fopencookie_to_funopen_seekfn) __off_t
NOTHROW_CB(__LIBKCALL fopencookie_to_funopen_seekfn)(void *cookie, __off_t off, int whence) {
#if __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__
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
#else /* __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__ */
#ifdef __USE_KOS_ALTERATIONS
	pos64_t newpos = (pos64_t)off;
#else /* __USE_KOS_ALTERATIONS */
	off64_t newpos = off;
#endif /* !__USE_KOS_ALTERATIONS */
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	if ((*holder->foch_funcs.seek)(holder->foch_cookie, &newpos, whence) != 0)
		return -1;
	return (__off_t)newpos;
#endif /* __SIZEOF_OFF_T__ != __SIZEOF_OFF64_T__ */
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_seekfn_defined */

#elif (defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2))
#ifndef __fopencookie_to_funopen2_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen2_readfn_defined
__LOCAL_LIBC(fopencookie_to_funopen2_readfn) ATTR_OUTS(2, 3) ssize_t
NOTHROW_CB_NCX(__LIBKCALL fopencookie_to_funopen2_readfn)(void *cookie, void *buf, size_t num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (*holder->foch_funcs.read)(holder->foch_cookie, (char *)buf, num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen2_readfn_defined */

#ifndef __fopencookie_to_funopen2_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen2_writefn_defined
__LOCAL_LIBC(fopencookie_to_funopen2_writefn) ATTR_INS(2, 3) ssize_t
NOTHROW_CB_NCX(__LIBKCALL fopencookie_to_funopen2_writefn)(void *cookie, void const *buf, size_t num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (*holder->foch_funcs.write)(holder->foch_cookie, (char const *)buf, num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen2_writefn_defined */

#ifndef __fopencookie_to_funopen64_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen64_seekfn_defined
__LOCAL_LIBC(fopencookie_to_funopen64_seekfn) off64_t
NOTHROW_CB(__LIBKCALL fopencookie_to_funopen64_seekfn)(void *cookie, off64_t off, int whence) {
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

#elif defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF_T__ == __SIZEOF_OFF32_T__
#ifndef __fopencookie_to_funopen2_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen2_readfn_defined
__LOCAL_LIBC(fopencookie_to_funopen2_readfn) ATTR_OUTS(2, 3) ssize_t
NOTHROW_CB_NCX(__LIBKCALL fopencookie_to_funopen2_readfn)(void *cookie, void *buf, size_t num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (*holder->foch_funcs.read)(holder->foch_cookie, (char *)buf, num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen2_readfn_defined */

#ifndef __fopencookie_to_funopen2_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen2_writefn_defined
__LOCAL_LIBC(fopencookie_to_funopen2_writefn) ATTR_INS(2, 3) ssize_t
NOTHROW_CB_NCX(__LIBKCALL fopencookie_to_funopen2_writefn)(void *cookie, void const *buf, size_t num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (*holder->foch_funcs.write)(holder->foch_cookie, (char const *)buf, num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen2_writefn_defined */

#ifndef __fopencookie_to_funopen_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_seekfn_defined
__LOCAL_LIBC(fopencookie_to_funopen_seekfn) __off_t
NOTHROW_CB(__LIBKCALL fopencookie_to_funopen_seekfn)(void *cookie, __off_t off, int whence) {
#if __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__
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
#else /* __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__ */
#ifdef __USE_KOS_ALTERATIONS
	pos64_t newpos = (pos64_t)off;
#else /* __USE_KOS_ALTERATIONS */
	off64_t newpos = off;
#endif /* !__USE_KOS_ALTERATIONS */
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	if ((*holder->foch_funcs.seek)(holder->foch_cookie, &newpos, whence) != 0)
		return -1;
	return (__off_t)newpos;
#endif /* __SIZEOF_OFF_T__ != __SIZEOF_OFF64_T__ */
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_seekfn_defined */

#elif (defined(__CRT_HAVE_funopen) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_funopen2) || defined(__CRT_HAVE_fopencookie) || defined(__CRT_HAVE_funopen)))
#ifndef __fopencookie_to_funopen_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_readfn_defined
__LOCAL_LIBC(fopencookie_to_funopen_readfn) ATTR_OUTS(2, 3) int
NOTHROW_CB_NCX(__LIBKCALL fopencookie_to_funopen_readfn)(void *cookie, char *buf, int num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (int)(*holder->foch_funcs.read)(holder->foch_cookie, buf, (size_t)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_readfn_defined */

#ifndef __fopencookie_to_funopen_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_writefn_defined
__LOCAL_LIBC(fopencookie_to_funopen_writefn) ATTR_INS(2, 3) int
NOTHROW_CB_NCX(__LIBKCALL fopencookie_to_funopen_writefn)(void *cookie, char const *buf, int num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (int)(*holder->foch_funcs.write)(holder->foch_cookie, buf, (size_t)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_writefn_defined */

#ifndef __fopencookie_to_funopen64_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen64_seekfn_defined
__LOCAL_LIBC(fopencookie_to_funopen64_seekfn) off64_t
NOTHROW_CB(__LIBKCALL fopencookie_to_funopen64_seekfn)(void *cookie, off64_t off, int whence) {
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
#define __fopencookie_to_funopen_readfn_defined
__LOCAL_LIBC(fopencookie_to_funopen_readfn) ATTR_OUTS(2, 3) int
NOTHROW_CB_NCX(__LIBKCALL fopencookie_to_funopen_readfn)(void *cookie, char *buf, int num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (int)(*holder->foch_funcs.read)(holder->foch_cookie, buf, (size_t)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_readfn_defined */

#ifndef __fopencookie_to_funopen_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_writefn_defined
__LOCAL_LIBC(fopencookie_to_funopen_writefn) ATTR_INS(2, 3) int
NOTHROW_CB_NCX(__LIBKCALL fopencookie_to_funopen_writefn)(void *cookie, char const *buf, int num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (int)(*holder->foch_funcs.write)(holder->foch_cookie, buf, (size_t)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_writefn_defined */

#ifndef __fopencookie_to_funopen_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_seekfn_defined
__LOCAL_LIBC(fopencookie_to_funopen_seekfn) __off_t
NOTHROW_CB(__LIBKCALL fopencookie_to_funopen_seekfn)(void *cookie, __off_t off, int whence) {
#if __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__
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
#else /* __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__ */
#ifdef __USE_KOS_ALTERATIONS
	pos64_t newpos = (pos64_t)off;
#else /* __USE_KOS_ALTERATIONS */
	off64_t newpos = off;
#endif /* !__USE_KOS_ALTERATIONS */
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	if ((*holder->foch_funcs.seek)(holder->foch_cookie, &newpos, whence) != 0)
		return -1;
	return (__off_t)newpos;
#endif /* __SIZEOF_OFF_T__ != __SIZEOF_OFF64_T__ */
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_seekfn_defined */

#endif /* !... */
/* >> fopencookie(3) */
INTERN ATTR_SECTION(".text.crt.FILE.locked.access") WUNUSED ATTR_IN(2) FILE *
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













	result = libc_funopen2_64(/* cookie:  */ holder,
	                     /* readfn:  */ io_funcs.read ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen2_readfn : NULL,
	                     /* writefn: */ io_funcs.write ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen2_writefn : NULL,
	                     /* seekfn:  */ io_funcs.seek ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen64_seekfn : NULL,
	                     /* flushfn: */ NULL,
	                     /* closefn: */ &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_closefn);





















	if unlikely(!result)
		libc_free(holder);

	return result;
}
#include <libc/errno.h>
/* >> fgets_unlocked(3)
 * Same as `fgets()', but performs I/O without acquiring a lock to `stream' */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.read") WUNUSED ATTR_INOUT(3) ATTR_OUTS(1, 2) char *
NOTHROW_CB_NCX(LIBCCALL libc_fgets_unlocked)(char *__restrict buf,
                                             __STDC_INT_AS_SIZE_T bufsize,
                                             FILE *__restrict stream) {
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */

		(void)libc_seterrno(ERANGE);

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
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.write") ATTR_IN(1) ATTR_INOUT(2) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBCCALL libc_fputs_unlocked)(char const *__restrict string,
                                             FILE *__restrict stream) {
	__STDC_INT_AS_SIZE_T result;
	result = libc_fwrite_unlocked(string,
	                         sizeof(char),
	                         libc_strlen(string),
	                         stream);
	return result;
}
/* >> obstack_printf(3), obstack_vprintf(3)
 * Append formated strings to a given obstack. s.a. `obstack_printer(3)' */
INTERN ATTR_SECTION(".text.crt.heap.obstack") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 0) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc_obstack_vprintf)(struct obstack *__restrict self,
                                           char const *__restrict format,
                                           va_list args) {
	return (__STDC_INT_AS_SIZE_T)libc_format_vprintf(&libc_obstack_printer, self, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> obstack_printf(3), obstack_vprintf(3)
 * Append formated strings to a given obstack. s.a. `obstack_printer(3)' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.obstack") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd_obstack_printf)(struct obstack *__restrict self,
                                           char const *__restrict format,
                                           ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_obstack_vprintf(self, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> obstack_printf(3), obstack_vprintf(3)
 * Append formated strings to a given obstack. s.a. `obstack_printer(3)' */
INTERN ATTR_SECTION(".text.crt.heap.obstack") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc_obstack_printf)(struct obstack *__restrict self,
                                           char const *__restrict format,
                                           ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_obstack_vprintf(self, format, args);
	va_end(args);
	return result;
}
#include <asm/os/oflags.h>
#if !__O_LARGEFILE
DEFINE_INTERN_ALIAS_P(libc_tmpfile64,libc_tmpfile,WUNUSED,FILE *,NOTHROW_RPC,LIBCCALL,(void),());
#else /* !__O_LARGEFILE */
#include <paths.h>
/* >> tmpfile(3), tmpfile64(3)
 * Create and return a new file-stream for accessing a temporary file for reading/writing
 * The file uses an  operating-system provided file descriptor,  however does not have  a
 * proper name anywhere  on the filesystem  (meaning the file's  contents are deleted  as
 * soon as the returned file stream is closed) */
INTERN ATTR_SECTION(".text.crt.FILE.locked.access") WUNUSED FILE *
NOTHROW_RPC(LIBCCALL libc_tmpfile64)(void) {
	FILE *result;
	fd_t tmpfd;
#ifndef _PATH_TMP
#define _PATH_TMP "/tmp/"
#endif /* !_PATH_TMP */
	char tmpfd_name_buf[COMPILER_STRLEN(_PATH_TMP "tmp.XXXXXX") + 1];
	(void)libc_memcpy(tmpfd_name_buf, _PATH_TMP "tmp.XXXXXX", sizeof(tmpfd_name_buf));
	{

		sigset_t *oset;
		oset  = libc_setsigmaskfullptr();
		tmpfd = libc_mkstemp64(tmpfd_name_buf);
		if likely(tmpfd >= 0)
			(void)libc_unlink(tmpfd_name_buf);
		(void)libc_setsigmaskptr(oset);









	}
	if unlikely(tmpfd < 0)
		return NULL;
	result = libc_fdopen(tmpfd, "w+");

	if unlikely(!result)
		(void)libc_close(tmpfd);

	return result;
}
#endif /* __O_LARGEFILE */
/* >> fopen_printer(3)
 * Create and return a new write-only file-stream that will write to the given printer.
 * Note  that by default, the buffering is enabled for the file-stream, meaning you may
 * have to call `fflush(return)' before printed data is committed to the given printer.
 * - Buffering can be disabled with `setvbuf(return, NULL, _IONBF, 0)'
 * - When `printer' returns a negative value, `ferror(return)' becomes set
 * @return: * :   A file-stream that emits its data to `printer'
 * @return: NULL: Insufficient memory. */
INTERN ATTR_SECTION(".text.crt.FILE.locked.access") WUNUSED NONNULL((1)) FILE *
NOTHROW_NCX(LIBCCALL libc_fopen_printer)(__pformatprinter printer,
                                         void *arg) {
	/* KOS's pformatprinter is ABI-compatible with the `writefn' of `funopen2(3)' / `funopen2_64(3)'
	 * -> As such, this function can super-easily be implemented with the help of that one! */

	return libc_funopen2_64(arg, NULL, (ssize_t (LIBKCALL *)(void *, void const *, size_t))printer, NULL, NULL, NULL);



}
#include <hybrid/__assert.h>
#ifndef __format_aprintf_data_defined
#define __format_aprintf_data_defined
struct format_aprintf_data {
	char         *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owend] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};
#endif /* !__format_aprintf_data_defined */
/* >> asprintf(3), vasprintf(3)
 * Print the given `format' into a newly allocated, heap-allocated string which is then stored in `*pstr' */
INTERN ATTR_SECTION(".text.crt.heap.strdup") ATTR_IN(2) ATTR_LIBC_PRINTF(2, 0) ATTR_OUT(1) __STDC_INT_AS_SSIZE_T
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.strdup") ATTR_IN(2) ATTR_LIBC_PRINTF(2, 3) ATTR_OUT(1) __STDC_INT_AS_SSIZE_T
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
INTERN ATTR_SECTION(".text.crt.heap.strdup") ATTR_IN(2) ATTR_LIBC_PRINTF(2, 3) ATTR_OUT(1) __STDC_INT_AS_SSIZE_T
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
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.getc") ATTR_INOUT(1) int
NOTHROW_CB_NCX(LIBCCALL libc_getw_unlocked)(FILE *__restrict stream) {
	u16 result;
	return libc_fread_unlocked(&result, sizeof(result), 1, stream)
	       ? (int)(unsigned int)result
	       : (int)EOF;
}
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.putc") ATTR_INOUT(2) int
NOTHROW_CB_NCX(LIBCCALL libc_putw_unlocked)(int w,
                                            FILE *__restrict stream) {
	u16 c = (u16)w;
	return libc_fwrite_unlocked(&c, sizeof(c), 1, stream)
	       ? w
	       : EOF;
}
#include <hybrid/__assert.h>
/* >> getdelim(3) */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.read") WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) ATTR_INOUT(4) ssize_t
NOTHROW_CB_NCX(LIBCCALL libc_getdelim_unlocked)(char **__restrict lineptr,
                                                size_t *__restrict pcount,
                                                int delimiter,
                                                FILE *__restrict stream) {
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
				(void)libc_ungetc_unlocked(ch, stream);

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
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.read") WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) ATTR_INOUT(3) ssize_t
NOTHROW_CB_NCX(LIBCCALL libc_getline_unlocked)(char **__restrict lineptr,
                                               size_t *__restrict pcount,
                                               FILE *__restrict stream) {
	return libc_getdelim_unlocked(lineptr, pcount, '\n', stream);
}
#include <libc/template/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.write") ATTR_IN(1) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(LIBCCALL libc_puts_unlocked)(char const *__restrict string) {
	__STDC_INT_AS_SSIZE_T result, temp;
	result = libc_fputs_unlocked(string, stdout);
	if (result >= 0) {
		temp = libc_fputc_unlocked('\n', stdout);
		if (temp <= 0) {
			result = temp;
		} else {
			++result;
		}
	}
	return result;
}
/* >> fprintf_unlocked(3), vfprintf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.printf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(LIBCCALL libc_vfprintf_unlocked)(FILE *__restrict stream,
                                                char const *__restrict format,
                                                va_list args) {
	return (__STDC_INT_AS_SSIZE_T)libc_format_vprintf(&libc_file_printer_unlocked, stream, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fprintf_unlocked(3), vfprintf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.unlocked.write.printf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd_fprintf_unlocked)(FILE *__restrict stream,
                                                char const *__restrict format,
                                                ...) {
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
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.printf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBCCALL libc_fprintf_unlocked)(FILE *__restrict stream,
                                                char const *__restrict format,
                                                ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfprintf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
#include <libc/template/stdstreams.h>
/* >> printf_unlocked(3), vprintf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.printf") ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(LIBCCALL libc_vprintf_unlocked)(char const *__restrict format,
                                               va_list args) {
	return libc_vfprintf_unlocked(stdout, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> printf_unlocked(3), vprintf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.unlocked.write.printf") ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd_printf_unlocked)(char const *__restrict format,
                                               ...) {
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
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.write.printf") ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBCCALL libc_printf_unlocked)(char const *__restrict format,
                                               ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vprintf_unlocked(format, args);
	va_end(args);
	return result;
}
__NAMESPACE_LOCAL_BEGIN
#if !defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_SIZE_T__ != __SIZEOF_INT__
__LOCAL_LIBC(vfscanf_getc_unlocked) __format_word_t
NOTHROW_CB_NCX(__FORMATPRINTER_CC vfscanf_getc_unlocked)(void *arg) {
	return (__format_word_t)libc_fgetc_unlocked((FILE *)arg);
}
#endif /* !__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_SIZE_T__ != __SIZEOF_INT__ */
__LOCAL_LIBC(vfscanf_ungetc_unlocked) ssize_t
NOTHROW_CB_NCX(__FORMATPRINTER_CC vfscanf_ungetc_unlocked)(void *arg, __format_word_t word) {
	return libc_ungetc_unlocked((int)(unsigned char)(unsigned int)word, (FILE *)arg);
}
__NAMESPACE_LOCAL_END
/* >> fscanf_unlocked(3), vfscanf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.scanf") WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 0) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBCCALL libc_vfscanf_unlocked)(FILE *__restrict stream,
                                               char const *__restrict format,
                                               va_list args) {
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
#include <libc/template/stdstreams.h>
/* >> scanf_unlocked(3), vscanf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.scanf") WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 0) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBCCALL libc_vscanf_unlocked)(char const *__restrict format,
                                              va_list args) {
	return libc_vfscanf_unlocked(stdin, format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fscanf_unlocked(3), vfscanf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.unlocked.read.scanf") WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 3) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd_fscanf_unlocked)(FILE *__restrict stream,
                                               char const *__restrict format,
                                               ...) {
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
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.scanf") WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 3) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBCCALL libc_fscanf_unlocked)(FILE *__restrict stream,
                                               char const *__restrict format,
                                               ...) {
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.unlocked.read.scanf") WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 2) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd_scanf_unlocked)(char const *__restrict format,
                                              ...) {
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
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.scanf") WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 2) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBCCALL libc_scanf_unlocked)(char const *__restrict format,
                                              ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vscanf_unlocked(format, args);
	va_end(args);
	return result;
}
/* >> fmtcheck(3)
 * Check if `user_format' may be used as a drop-in replacement for `good_format'
 * in the context of a call to `printf(3)' (or `format_printf()'), such that all
 * contained format qualifiers reference the  same (or compatible) underlying  C
 * types, and in the same order.
 * If all of this is the  case, simply re-return `user_format'. Otherwise  (i.e.
 * when `user_format' isn't compatible with `good_format'), return `good_format'
 * instead. This function is meant to  be used to validate user-provided  printf
 * format strings before actually using them, after they've been read from  lang
 * config files: `printf(fmtcheck(get_user_fmt(), "%s %s"), "Foo", "Bar");' */
INTERN ATTR_SECTION(".text.crt.FILE.unlocked.read.scanf") ATTR_RETNONNULL WUNUSED ATTR_IN(2) ATTR_IN_OPT(1) __ATTR_FORMAT_ARG(2) char const *
NOTHROW_NCX(LIBCCALL libc_fmtcheck)(char const *user_format,
                                    char const *good_format) {
	/* TODO: Implement properly */
	COMPILER_IMPURE();
	(void)good_format;
	return user_format;
}
#if __SIZEOF_INT__ != __SIZEOF_SIZE_T__ || ((!defined(__CRT_HAVE_funopen2) || __SIZEOF_OFF_T__ != __SIZEOF_OFF32_T__) && (!defined(__CRT_HAVE_funopen2_64) || __SIZEOF_OFF_T__ != __SIZEOF_OFF64_T__) && ((!defined(__CRT_HAVE_malloc) && !defined(__CRT_HAVE___libc_malloc) && !defined(__CRT_HAVE_calloc) && !defined(__CRT_HAVE___libc_calloc) && !defined(__CRT_HAVE_realloc) && !defined(__CRT_HAVE___libc_realloc) && !defined(__CRT_HAVE_memalign) && !defined(__CRT_HAVE_aligned_alloc) && !defined(__CRT_HAVE___libc_memalign) && !defined(__CRT_HAVE_posix_memalign)) || (!defined(__CRT_HAVE_funopen2_64) && !defined(__CRT_HAVE_funopen2))))
#ifndef ____funopen_holder_defined
__NAMESPACE_LOCAL_BEGIN
#define ____funopen_holder_defined
struct __funopen_holder {
	void            *fh_cookie;                                                 /* [?..?] funopen cookie */
	int   (LIBKCALL *fh_readfn)(void *cookie, char *buf, int num_bytes);        /* [0..1] funopen readfn */
	int   (LIBKCALL *fh_writefn)(void *cookie, char const *buf, int num_bytes); /* [0..1] funopen writefn */
	off_t (LIBKCALL *fh_seekfn)(void *cookie, off_t off, int whence);           /* [0..1] funopen seekfn */
	int   (LIBKCALL *fh_closefn)(void *cookie);                                 /* [0..1] funopen closefn */
};
__NAMESPACE_LOCAL_END
#endif /* !____funopen_holder_defined */

#ifndef __funopen_to_funopen2_closefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_closefn_defined
__LOCAL_LIBC(funopen_to_funopen2_closefn) int
NOTHROW_CB(__LIBKCALL funopen_to_funopen2_closefn)(void *cookie) {
	int result = 0;
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	if (holder->fh_closefn != NULL)
		result = (*holder->fh_closefn)(holder->fh_cookie);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(holder);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return result;
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_closefn_defined */

#if (defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF_T__ == __SIZEOF_OFF32_T__) || (defined(__CRT_HAVE_funopen2_64) && __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2)))
#ifndef __funopen_to_funopen2_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_readfn_defined
__LOCAL_LIBC(funopen_to_funopen2_readfn) ATTR_OUTS(2, 3) ssize_t
NOTHROW_CB_NCX(__LIBKCALL funopen_to_funopen2_readfn)(void *cookie, void *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_readfn)(holder->fh_cookie, (char *)buf,
	                                     (int)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_readfn_defined */

#ifndef __funopen_to_funopen2_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_writefn_defined
__LOCAL_LIBC(funopen_to_funopen2_writefn) ATTR_INS(2, 3) ssize_t
NOTHROW_CB_NCX(__LIBKCALL funopen_to_funopen2_writefn)(void *cookie, void const *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_writefn)(holder->fh_cookie, (char const *)buf,
	                                      (int)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_writefn_defined */

#ifndef __funopen_to_funopen2_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_seekfn_defined
__LOCAL_LIBC(funopen_to_funopen2_seekfn) __off_t
NOTHROW_CB(__LIBKCALL funopen_to_funopen2_seekfn)(void *cookie, __off_t off, int whence) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_seekfn)(holder->fh_cookie, off, whence);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_seekfn_defined */

#elif defined(__CRT_HAVE_fopencookie)
#ifndef __funopen_to_funopen2_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_readfn_defined
__LOCAL_LIBC(funopen_to_funopen2_readfn) ATTR_OUTS(2, 3) ssize_t
NOTHROW_CB_NCX(__LIBKCALL funopen_to_funopen2_readfn)(void *cookie, void *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_readfn)(holder->fh_cookie, (char *)buf,
	                                     (int)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_readfn_defined */

#ifndef __funopen_to_funopen2_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_writefn_defined
__LOCAL_LIBC(funopen_to_funopen2_writefn) ATTR_INS(2, 3) ssize_t
NOTHROW_CB_NCX(__LIBKCALL funopen_to_funopen2_writefn)(void *cookie, void const *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_writefn)(holder->fh_cookie, (char const *)buf,
	                                      (int)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_writefn_defined */

#ifndef __funopen_to_fopencookie_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_fopencookie_seekfn_defined
#ifdef __USE_KOS_ALTERATIONS
__LOCAL_LIBC(funopen_to_fopencookie_seekfn) NONNULL((2)) int
NOTHROW_CB(__LIBKCALL funopen_to_fopencookie_seekfn)(void *cookie, pos64_t *pos, int whence)
#else /* __USE_KOS_ALTERATIONS */
__LOCAL_LIBC(funopen_to_fopencookie_seekfn) NONNULL((2)) int
NOTHROW_CB(__LIBKCALL funopen_to_fopencookie_seekfn)(void *cookie, off64_t *pos, int whence)
#endif /* !__USE_KOS_ALTERATIONS */
{
	__off_t newpos;
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	newpos = (*holder->fh_seekfn)(holder->fh_cookie, (__off_t)*pos, whence);
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
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__
#ifndef __funopen_to_funopen2_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_readfn_defined
__LOCAL_LIBC(funopen_to_funopen2_readfn) ATTR_OUTS(2, 3) ssize_t
NOTHROW_CB_NCX(__LIBKCALL funopen_to_funopen2_readfn)(void *cookie, void *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_readfn)(holder->fh_cookie, (char *)buf,
	                                     (int)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_readfn_defined */

#ifndef __funopen_to_funopen2_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_writefn_defined
__LOCAL_LIBC(funopen_to_funopen2_writefn) ATTR_INS(2, 3) ssize_t
NOTHROW_CB_NCX(__LIBKCALL funopen_to_funopen2_writefn)(void *cookie, void const *buf, size_t num_bytes) {
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
#define __funopen_to_funopen64_readfn_defined
__LOCAL_LIBC(funopen_to_funopen64_readfn) ATTR_OUTS(2, 3) int
NOTHROW_CB_NCX(__LIBKCALL funopen_to_funopen64_readfn)(void *cookie, char *buf, int num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_readfn)(holder->fh_cookie, buf, num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen64_readfn_defined */

#ifndef __funopen_to_funopen64_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen64_writefn_defined
__LOCAL_LIBC(funopen_to_funopen64_writefn) ATTR_INS(2, 3) int
NOTHROW_CB_NCX(__LIBKCALL funopen_to_funopen64_writefn)(void *cookie, char const *buf, int num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_writefn)(holder->fh_cookie, buf, num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen64_writefn_defined */

#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
#ifndef __funopen_to_funopen64_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen64_seekfn_defined
__LOCAL_LIBC(funopen_to_funopen64_seekfn) off64_t
NOTHROW_CB(__LIBKCALL funopen_to_funopen64_seekfn)(void *cookie, off64_t off, int whence) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_seekfn)(holder->fh_cookie, (__off_t)off, whence);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen64_seekfn_defined */

#endif /* !... */
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ || ((!__CRT_HAVE_funopen2 || __SIZEOF_OFF_T__ != __SIZEOF_OFF32_T__) && (!__CRT_HAVE_funopen2_64 || __SIZEOF_OFF_T__ != __SIZEOF_OFF64_T__) && ((!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE_funopen2_64 && !__CRT_HAVE_funopen2))) */
/* >> funopen(3), funopen64(3) */
INTERN ATTR_SECTION(".text.crt.FILE.locked.utility") WUNUSED FILE *
NOTHROW_NCX(LIBCCALL libc_funopen)(void const *cookie,
                                   int (LIBKCALL *readfn)(void *cookie, char *buf, int num_bytes),
                                   int (LIBKCALL *writefn)(void *cookie, char const *buf, int num_bytes),
                                   off_t (LIBKCALL *seekfn)(void *cookie, off_t off, int whence),
                                   int (LIBKCALL *closefn)(void *cookie)) {
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__
	return libc_funopen2(cookie,
	                (ssize_t (LIBKCALL *)(void *, void *, size_t))readfn,
	                (ssize_t (LIBKCALL *)(void *, void const *, size_t))writefn,
	                seekfn, NULL, closefn);
#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ */
	FILE *result;
	struct __NAMESPACE_LOCAL_SYM __funopen_holder *holder;

	if (!seekfn)
		return libc_funopen64(cookie, readfn, writefn, NULL, closefn);

	holder = (struct __NAMESPACE_LOCAL_SYM __funopen_holder *)libc_malloc(sizeof(struct __NAMESPACE_LOCAL_SYM __funopen_holder));
	if unlikely(!holder)
		return NULL;
	holder->fh_cookie  = (void *)cookie;
	holder->fh_readfn  = readfn;
	holder->fh_writefn = writefn;
	holder->fh_seekfn  = seekfn;
	holder->fh_closefn = closefn;

	result = libc_funopen2(/* cookie:  */ holder,
	                  /* readfn:  */ readfn  ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_readfn  : NULL,
	                  /* writefn: */ writefn ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_writefn : NULL,
	                  /* seekfn:  */ seekfn  ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_seekfn  : NULL,
	                  /* flushfn: */ NULL,
	                  /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);

























	if unlikely(!result)
		libc_free(holder);

	return result;
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
}
#include <bits/types.h>
#if __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
DEFINE_INTERN_ALIAS_P(libc_funopen64,libc_funopen,WUNUSED,FILE *,NOTHROW_NCX,LIBCCALL,(void const *cookie, int (LIBKCALL *readfn)(void *cookie, char *buf, int num_bytes), int (LIBKCALL *writefn)(void *cookie, char const *buf, int num_bytes), off64_t (LIBKCALL *seekfn)(void *cookie, off64_t off, int whence), int (LIBKCALL *closefn)(void *cookie)),(cookie,readfn,writefn,seekfn,closefn));
#else /* __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__ */
#if __SIZEOF_INT__ != __SIZEOF_SIZE_T__ || ((!defined(__CRT_HAVE_funopen2) || __SIZEOF_OFF64_T__ != __SIZEOF_OFF32_T__) && !defined(__CRT_HAVE_funopen2_64) && ((!defined(__CRT_HAVE_malloc) && !defined(__CRT_HAVE___libc_malloc) && !defined(__CRT_HAVE_calloc) && !defined(__CRT_HAVE___libc_calloc) && !defined(__CRT_HAVE_realloc) && !defined(__CRT_HAVE___libc_realloc) && !defined(__CRT_HAVE_memalign) && !defined(__CRT_HAVE_aligned_alloc) && !defined(__CRT_HAVE___libc_memalign) && !defined(__CRT_HAVE_posix_memalign)) || !defined(__CRT_HAVE_funopen2)))
#ifndef ____funopen_holder_defined
__NAMESPACE_LOCAL_BEGIN
#define ____funopen_holder_defined
struct __funopen_holder {
	void            *fh_cookie;                                                 /* [?..?] funopen cookie */
	int   (LIBKCALL *fh_readfn)(void *cookie, char *buf, int num_bytes);        /* [0..1] funopen readfn */
	int   (LIBKCALL *fh_writefn)(void *cookie, char const *buf, int num_bytes); /* [0..1] funopen writefn */
	off_t (LIBKCALL *fh_seekfn)(void *cookie, off_t off, int whence);           /* [0..1] funopen seekfn */
	int   (LIBKCALL *fh_closefn)(void *cookie);                                 /* [0..1] funopen closefn */
};
__NAMESPACE_LOCAL_END
#endif /* !____funopen_holder_defined */

#ifndef ____funopen64_holder_defined
__NAMESPACE_LOCAL_BEGIN
#define ____funopen64_holder_defined
struct __funopen64_holder {
	void              *fh64_cookie;                                                 /* [0..1] funopen cookie */
	int     (LIBKCALL *fh64_readfn)(void *cookie, char *buf, int num_bytes);        /* [0..1] funopen readfn */
	int     (LIBKCALL *fh64_writefn)(void *cookie, char const *buf, int num_bytes); /* [0..1] funopen writefn */
	off64_t (LIBKCALL *fh64_seekfn)(void *cookie, off64_t off, int whence);         /* [0..1] funopen seekfn */
	int     (LIBKCALL *fh64_closefn)(void *cookie);                                 /* [0..1] funopen closefn */
};
__NAMESPACE_LOCAL_END
#endif /* !____funopen64_holder_defined */

#ifndef __funopen_to_funopen2_closefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_closefn_defined
__LOCAL_LIBC(funopen_to_funopen2_closefn) int
NOTHROW_CB(__LIBKCALL funopen_to_funopen2_closefn)(void *cookie) {
	int result = 0;
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	if (holder->fh_closefn != NULL)
		result = (*holder->fh_closefn)(holder->fh_cookie);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(holder);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return result;
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_closefn_defined */

#if (defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2))
#ifndef __funopen_to_funopen2_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_readfn_defined
__LOCAL_LIBC(funopen_to_funopen2_readfn) ATTR_OUTS(2, 3) ssize_t
NOTHROW_CB_NCX(__LIBKCALL funopen_to_funopen2_readfn)(void *cookie, void *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_readfn)(holder->fh_cookie, (char *)buf,
	                                     (int)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_readfn_defined */

#ifndef __funopen_to_funopen2_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_writefn_defined
__LOCAL_LIBC(funopen_to_funopen2_writefn) ATTR_INS(2, 3) ssize_t
NOTHROW_CB_NCX(__LIBKCALL funopen_to_funopen2_writefn)(void *cookie, void const *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_writefn)(holder->fh_cookie, (char const *)buf,
	                                      (int)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_writefn_defined */

#if __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__
#ifndef __funopen_to_funopen2_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_seekfn_defined
__LOCAL_LIBC(funopen_to_funopen2_seekfn) __off_t
NOTHROW_CB(__LIBKCALL funopen_to_funopen2_seekfn)(void *cookie, __off_t off, int whence) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_seekfn)(holder->fh_cookie, off, whence);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_seekfn_defined */

#else /* __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__ */
#ifndef __funopen64_to_funopen2_64_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen64_to_funopen2_64_seekfn_defined
__LOCAL_LIBC(funopen64_to_funopen2_64_seekfn) off64_t
NOTHROW_CB(__LIBKCALL funopen64_to_funopen2_64_seekfn)(void *cookie, off64_t off, int whence) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_seekfn)(holder->fh_cookie, off, whence);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen64_to_funopen2_64_seekfn_defined */

#endif /* __SIZEOF_OFF_T__ != __SIZEOF_OFF64_T__ */
#elif defined(__CRT_HAVE_fopencookie)
#ifndef __funopen_to_funopen2_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_readfn_defined
__LOCAL_LIBC(funopen_to_funopen2_readfn) ATTR_OUTS(2, 3) ssize_t
NOTHROW_CB_NCX(__LIBKCALL funopen_to_funopen2_readfn)(void *cookie, void *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_readfn)(holder->fh_cookie, (char *)buf,
	                                     (int)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_readfn_defined */

#ifndef __funopen_to_funopen2_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_writefn_defined
__LOCAL_LIBC(funopen_to_funopen2_writefn) ATTR_INS(2, 3) ssize_t
NOTHROW_CB_NCX(__LIBKCALL funopen_to_funopen2_writefn)(void *cookie, void const *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_writefn)(holder->fh_cookie, (char const *)buf,
	                                      (int)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_writefn_defined */

#if __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__
#ifndef __funopen_to_fopencookie_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_fopencookie_seekfn_defined
#ifdef __USE_KOS_ALTERATIONS
__LOCAL_LIBC(funopen_to_fopencookie_seekfn) NONNULL((2)) int
NOTHROW_CB(__LIBKCALL funopen_to_fopencookie_seekfn)(void *cookie, pos64_t *pos, int whence)
#else /* __USE_KOS_ALTERATIONS */
__LOCAL_LIBC(funopen_to_fopencookie_seekfn) NONNULL((2)) int
NOTHROW_CB(__LIBKCALL funopen_to_fopencookie_seekfn)(void *cookie, off64_t *pos, int whence)
#endif /* !__USE_KOS_ALTERATIONS */
{
	__off_t newpos;
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	newpos = (*holder->fh_seekfn)(holder->fh_cookie, (__off_t)*pos, whence);
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

#else /* __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__ */
#ifndef __funopen64_to_fopencookie_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen64_to_fopencookie_seekfn_defined
#ifdef __USE_KOS_ALTERATIONS
__LOCAL_LIBC(funopen64_to_fopencookie_seekfn) int
NOTHROW_CB(__LIBKCALL funopen64_to_fopencookie_seekfn)(void *cookie, pos64_t *pos, int whence)
#else /* __USE_KOS_ALTERATIONS */
__LOCAL_LIBC(funopen64_to_fopencookie_seekfn) int
NOTHROW_CB(__LIBKCALL funopen64_to_fopencookie_seekfn)(void *cookie, off64_t *pos, int whence)
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

#endif /* __SIZEOF_OFF_T__ != __SIZEOF_OFF64_T__ */
#include <libio.h>
#else /* ... */
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__
#ifndef __funopen_to_funopen2_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_readfn_defined
__LOCAL_LIBC(funopen_to_funopen2_readfn) ATTR_OUTS(2, 3) ssize_t
NOTHROW_CB_NCX(__LIBKCALL funopen_to_funopen2_readfn)(void *cookie, void *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_readfn)(holder->fh_cookie, (char *)buf,
	                                     (int)(unsigned int)num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_readfn_defined */

#ifndef __funopen_to_funopen2_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_writefn_defined
__LOCAL_LIBC(funopen_to_funopen2_writefn) ATTR_INS(2, 3) ssize_t
NOTHROW_CB_NCX(__LIBKCALL funopen_to_funopen2_writefn)(void *cookie, void const *buf, size_t num_bytes) {
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
#define __funopen_to_funopen64_readfn_defined
__LOCAL_LIBC(funopen_to_funopen64_readfn) ATTR_OUTS(2, 3) int
NOTHROW_CB_NCX(__LIBKCALL funopen_to_funopen64_readfn)(void *cookie, char *buf, int num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_readfn)(holder->fh_cookie, buf, num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen64_readfn_defined */

#ifndef __funopen_to_funopen64_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen64_writefn_defined
__LOCAL_LIBC(funopen_to_funopen64_writefn) ATTR_INS(2, 3) int
NOTHROW_CB_NCX(__LIBKCALL funopen_to_funopen64_writefn)(void *cookie, char const *buf, int num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_writefn)(holder->fh_cookie, buf, num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen64_writefn_defined */

#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
#if __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__
#ifndef __funopen_to_funopen64_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen64_seekfn_defined
__LOCAL_LIBC(funopen_to_funopen64_seekfn) off64_t
NOTHROW_CB(__LIBKCALL funopen_to_funopen64_seekfn)(void *cookie, off64_t off, int whence) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_seekfn)(holder->fh_cookie, (__off_t)off, whence);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen64_seekfn_defined */

#else /* __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__ */
#ifndef __funopen64_to_funopen_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen64_to_funopen_seekfn_defined
__LOCAL_LIBC(funopen64_to_funopen_seekfn) off_t
NOTHROW_CB(__LIBKCALL funopen64_to_funopen_seekfn)(void *cookie, off_t off, int whence) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (off_t)(*holder->fh_seekfn)(holder->fh_cookie, (off64_t)off, whence);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen64_to_funopen_seekfn_defined */

#endif /* __SIZEOF_OFF_T__ != __SIZEOF_OFF64_T__ */
#endif /* !... */
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ || ((!__CRT_HAVE_funopen2 || __SIZEOF_OFF64_T__ != __SIZEOF_OFF32_T__) && !__CRT_HAVE_funopen2_64 && ((!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || !__CRT_HAVE_funopen2)) */
/* >> funopen(3), funopen64(3) */
INTERN ATTR_SECTION(".text.crt.FILE.locked.utility") WUNUSED FILE *
NOTHROW_NCX(LIBCCALL libc_funopen64)(void const *cookie,
                                     int (LIBKCALL *readfn)(void *cookie, char *buf, int num_bytes),
                                     int (LIBKCALL *writefn)(void *cookie, char const *buf, int num_bytes),
                                     off64_t (LIBKCALL *seekfn)(void *cookie, off64_t off, int whence),
                                     int (LIBKCALL *closefn)(void *cookie)) {
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__
	return libc_funopen2_64(cookie,
	                   (ssize_t (LIBKCALL *)(void *, void *, size_t))readfn,
	                   (ssize_t (LIBKCALL *)(void *, void const *, size_t))writefn,
	                   seekfn, NULL, closefn);
#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ */
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

#if __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__
	result = libc_funopen2_64(/* cookie:  */ holder,
	                     /* readfn:  */ readfn  ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_readfn  : NULL,
	                     /* writefn: */ writefn ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_writefn : NULL,
	                     /* seekfn:  */ seekfn  ? (off64_t (LIBKCALL *)(void *, off64_t, int))&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_seekfn  : NULL,
	                     /* flushfn: */ NULL,
	                     /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
#else /* __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__ */
	result = libc_funopen2_64(/* cookie:  */ holder,
	                     /* readfn:  */ readfn  ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_readfn  : NULL,
	                     /* writefn: */ writefn ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_writefn : NULL,
	                     /* seekfn:  */ seekfn  ? &__NAMESPACE_LOCAL_SYM funopen64_to_funopen2_64_seekfn  : NULL,
	                     /* flushfn: */ NULL,
	                     /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
#endif /* __SIZEOF_OFF_T__ != __SIZEOF_OFF64_T__ */













































	if unlikely(!result)
		libc_free(holder);

	return result;
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
}
#endif /* __SIZEOF_OFF64_T__ != __SIZEOF_OFF32_T__ */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.access") WUNUSED ATTR_IN(1) ATTR_IN(2) FILE *
NOTHROW_RPC(LIBDCALL libd__fsopen)(char const *filename,
                                   char const *modes,
                                   __STDC_INT_AS_UINT_T sflag) {
	(void)sflag;
	return libd_fopen(filename, modes);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") WUNUSED ATTR_IN(1) ATTR_IN(2) FILE *
NOTHROW_RPC(LIBCCALL libc__fsopen)(char const *filename,
                                   char const *modes,
                                   __STDC_INT_AS_UINT_T sflag) {
	(void)sflag;
	return libc_fopen(filename, modes);
}
#include <asm/os/resource.h>
#include <bits/os/rlimit.h>
INTERN ATTR_SECTION(".text.crt.dos.FILE.utility") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__getmaxstdio)(void) {
	struct rlimit rlim;
	if unlikely(libc_getrlimit((__rlimit_resource_t)__RLIMIT_NOFILE, &rlim) != 0)
		rlim.rlim_cur = (__rlim_t)-1;
	return (int)rlim.rlim_cur;
}
#include <asm/os/resource.h>
#include <bits/os/rlimit.h>
INTERN ATTR_SECTION(".text.crt.dos.FILE.utility") int
NOTHROW_NCX(LIBCCALL libc__setmaxstdio)(int newmaxval) {
	struct rlimit rlim;
	if unlikely(libc_getrlimit((__rlimit_resource_t)__RLIMIT_NOFILE, &rlim) != 0)
		goto err;
	rlim.rlim_cur = (__rlim_t)newmaxval;
	if unlikely(libc_setrlimit((__rlimit_resource_t)__RLIMIT_NOFILE, &rlim) != 0) {
err:
		rlim.rlim_cur = (__rlim_t)-1;
	}
	return (int)rlim.rlim_cur;
}
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.access") ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1) errno_t
NOTHROW_RPC(LIBDCALL libd_fopen_s)(FILE **pstream,
                                   char const *filename,
                                   char const *modes) {
	FILE *result;
	if unlikely(!pstream || !filename || !modes) {

		return EINVAL;



	}
	result = libd_fopen64(filename, modes);
	if unlikely(!result) {

		return __libc_geterrno_or(ENOMEM);



	}
	*pstream = result;
	return EOK;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_fopen_s)(FILE **pstream,
                                   char const *filename,
                                   char const *modes) {
	FILE *result;
	if unlikely(!pstream || !filename || !modes) {

		return EINVAL;



	}
	result = libc_fopen64(filename, modes);
	if unlikely(!result) {

		return __libc_geterrno_or(ENOMEM);



	}
	*pstream = result;
	return EOK;
}
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.access") ATTR_IN(2) ATTR_IN(3) ATTR_INOUT(4) ATTR_OUT(1) errno_t
NOTHROW_RPC(LIBDCALL libd_freopen_s)(FILE **pstream,
                                     char const *filename,
                                     char const *modes,
                                     FILE *oldstream) {
	if unlikely(!pstream || !filename || !modes || !oldstream) {

		return EINVAL;



	}
	oldstream = libd_freopen(filename, modes, oldstream);
	if unlikely(!oldstream) {

		return __libc_geterrno();



	}
	*pstream = oldstream;
	return EOK;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") ATTR_IN(2) ATTR_IN(3) ATTR_INOUT(4) ATTR_OUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_freopen_s)(FILE **pstream,
                                     char const *filename,
                                     char const *modes,
                                     FILE *oldstream) {
	if unlikely(!pstream || !filename || !modes || !oldstream) {

		return EINVAL;



	}
	oldstream = libc_freopen(filename, modes, oldstream);
	if unlikely(!oldstream) {

		return __libc_geterrno();



	}
	*pstream = oldstream;
	return EOK;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc_tmpnam_s)(char *__restrict buf,
                                    rsize_t bufsize) {
	if unlikely(!buf) {

		return EINVAL;



	}
	if unlikely(bufsize < L_tmpnam) {

		return ERANGE; /* XXX: Is this what dos does? */



	}
	if unlikely(!libc_tmpnam(buf))
		return __libc_geterrno_or(1);
	return EOK;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.utility") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_clearerr_s)(FILE *__restrict stream) {
	if (!stream) {

		return EINVAL;



	}
	libc_clearerr(stream);
	return 0;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") ATTR_OUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_tmpfile_s)(FILE **pstream) {
	if (!pstream) {

		return EINVAL;



	}
	*pstream = libc_tmpfile64();
	if (!*pstream) {

		return __libc_geterrno_or(ENOMEM);



	}
	return 0;
}
#include <libc/errno.h>
#include <hybrid/__overflow.h>
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.read") WUNUSED ATTR_INOUT(5) ATTR_OUT_OPT(1) size_t
NOTHROW_CB_NCX(LIBCCALL libc_fread_s)(void *__restrict buf,
                                      size_t bufsize,
                                      size_t elemsize,
                                      size_t elemcount,
                                      FILE *__restrict stream) {
	size_t reqbuf;
	if (__hybrid_overflow_umul(elemsize, elemcount, &reqbuf) ||
	    reqbuf > bufsize) {

		(void)libc_seterrno(ERANGE);

		return 0;
	}
	if unlikely(!stream || !buf) {

		(void)libc_seterrno(EINVAL);

		return 0;
	}
	return libc_fread(buf, elemsize, elemcount, stream);
}
#include <libc/template/stdstreams.h>
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.read") WUNUSED ATTR_OUTS(1, 2) char *
NOTHROW_CB_NCX(LIBCCALL libc_gets_s)(char *__restrict buf,
                                     rsize_t bufsize) {
	if unlikely(!buf) {

		(void)libc_seterrno(EINVAL);

		return NULL;
	}
	return libc_fgets(buf, (__STDC_INT_AS_SIZE_T)(unsigned int)bufsize, stdin);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.read.read") WUNUSED ATTR_INOUT(5) ATTR_IN_OPT(1) size_t
NOTHROW_CB_NCX(LIBCCALL libc__fread_nolock_s)(void *__restrict buf,
                                              size_t bufsize,
                                              size_t elemsize,
                                              size_t elemcount,
                                              FILE *__restrict stream) {
	bufsize = elemsize ? bufsize / elemsize : 0;
	return libc_fread_unlocked(buf, elemsize,
	                      bufsize < elemcount
	                      ? bufsize
	                      : elemcount,
	                      stream);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(3) ATTR_INOUT(2) ATTR_LIBC_PRINTF(3, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(LIBCCALL libc___stdio_common_vfprintf)(uint64_t options,
                                                      FILE *stream,
                                                      char const *format,
                                                      locale_t locale,
                                                      va_list args) {
	(void)locale;
	(void)options;
	return libc_vfprintf(stream, format, args);
}
DEFINE_INTERN_ALIAS_P(libc___stdio_common_vfprintf_s,libc___stdio_common_vfprintf,ATTR_IN(3) ATTR_INOUT(2) ATTR_LIBC_PRINTF(3, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(uint64_t options, FILE *stream, char const *format, locale_t locale, va_list args),(options,stream,format,locale,args));
DEFINE_INTERN_ALIAS_P(libc___stdio_common_vfprintf_p,libc___stdio_common_vfprintf,ATTR_IN(3) ATTR_INOUT(2) ATTR_LIBC_PRINTF_P(3, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(uint64_t options, FILE *stream, char const *format, locale_t locale, va_list args),(options,stream,format,locale,args));
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(4) ATTR_LIBC_PRINTF(4, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc___stdio_common_vsprintf)(uint64_t options,
                                                   char *buf,
                                                   size_t bufsize,
                                                   char const *format,
                                                   locale_t locale,
                                                   va_list args) {
	__STDC_INT_AS_SSIZE_T result;
	(void)locale;
	result = libc_vsnprintf(buf, bufsize, format, args);
	if (!(options & 2) && (size_t)result > bufsize)
		result = bufsize;
	return result;
}
#include <hybrid/__assert.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(4) ATTR_LIBC_PRINTF(4, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc___stdio_common_vsprintf_s)(uint64_t options,
                                                     char *buf,
                                                     size_t bufsize,
                                                     char const *format,
                                                     locale_t locale,
                                                     va_list args) {
	__STDC_INT_AS_SSIZE_T result;
	(void)options;
	(void)locale;
	result = libc_vsnprintf(buf, bufsize, format, args);
	__hybrid_assert(((size_t)result + 1) <= bufsize);
	return result;
}
#include <hybrid/__assert.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(5) ATTR_LIBC_PRINTF(5, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc___stdio_common_vsnprintf_s)(uint64_t options,
                                                      char *buf,
                                                      size_t bufsize,
                                                      size_t maxsize,
                                                      char const *format,
                                                      locale_t locale,
                                                      va_list args) {
	__hybrid_assert(bufsize <= maxsize);
	return libc___stdio_common_vsprintf(options, buf, bufsize, format, locale, args);
}
DEFINE_INTERN_ALIAS_P(libc___stdio_common_vsprintf_p,libc___stdio_common_vsprintf,ATTR_IN(4) ATTR_LIBC_PRINTF_P(4, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(uint64_t options, char *buf, size_t bufsize, char const *format, locale_t locale, va_list args),(options,buf,bufsize,format,locale,args));
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(3) ATTR_INOUT(2) ATTR_LIBC_SCANF(3, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(LIBCCALL libc___stdio_common_vfscanf)(uint64_t options,
                                                     FILE *stream,
                                                     char const *format,
                                                     locale_t locale,
                                                     va_list args) {
	(void)options;
	(void)locale;
	return libc_vfscanf(stream, format, args);
}
__NAMESPACE_LOCAL_BEGIN
struct __vsnscanf_data {
	unsigned char const *__ptr;
	unsigned char const *__end;
};
__LOCAL_LIBC(vsnscanf_getc) __format_word_t
NOTHROW_NCX(__FORMATPRINTER_CC vsnscanf_getc)(void *arg) {
	struct __vsnscanf_data *cookie;
	cookie = (struct __vsnscanf_data *)arg;
	if (cookie->__ptr >= cookie->__end)
		return __EOF;
	return (__format_word_t)*cookie->__ptr++;
}
__LOCAL_LIBC(vsnscanf_ungetc) __SSIZE_TYPE__
NOTHROW_NCX(__FORMATPRINTER_CC vsnscanf_ungetc)(void *arg, __format_word_t __UNUSED(word)) {
	struct __vsnscanf_data *cookie;
	cookie = (struct __vsnscanf_data *)arg;
	--cookie->__ptr;
	return 0;
}
__NAMESPACE_LOCAL_END
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(4) ATTR_INS(2, 3) ATTR_LIBC_SCANF(4, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc___stdio_common_vsscanf)(uint64_t options,
                                                  char const *input,
                                                  size_t inputsize,
                                                  char const *format,
                                                  locale_t locale,
                                                  va_list args) {
	struct __NAMESPACE_LOCAL_SYM __vsnscanf_data data;
	(void)options;
	(void)locale;
	if (inputsize == (size_t)-1)
		return libc_vsscanf(input, format, args);
	data.__ptr = (unsigned char const *)input;
	data.__end = (unsigned char const *)input + inputsize;
	return libc_format_vscanf(&__NAMESPACE_LOCAL_SYM vsnscanf_getc,
	                     &__NAMESPACE_LOCAL_SYM vsnscanf_ungetc,
	                     (void *)&data, format, args);
}
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc__vsnprintf_l)(char *buf,
                                        size_t bufsize,
                                        char const *format,
                                        locale_t locale,
                                        va_list args) {
	__STDC_INT_AS_SSIZE_T result = libc___stdio_common_vsprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS | 1, buf, bufsize, format, locale, args);
	return result < 0 ? -1 : result;
}
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc__vsprintf_s_l)(char *buf,
                                         size_t bufsize,
                                         char const *format,
                                         locale_t locale,
                                         va_list args) {
	__STDC_INT_AS_SSIZE_T result = libc___stdio_common_vsprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, buf, bufsize, format, locale, args);
	return result < 0 ? -1 : result;
}
DEFINE_INTERN_ALIAS_P(libc__vsprintf_p_l,libc__vsnprintf_l,ATTR_IN(3) ATTR_LIBC_PRINTF_P(3, 0) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char *buf, size_t bufsize, char const *format, locale_t locale, va_list args),(buf,bufsize,format,locale,args));
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc__vscprintf_l)(char const *format,
                                        locale_t locale,
                                        va_list args) {
	__STDC_INT_AS_SSIZE_T result = libc___stdio_common_vsprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS | 2, NULL, 0, format, locale, args);
	return result < 0 ? -1 : result;
}
DEFINE_INTERN_ALIAS_P(libc__vscprintf_p_l,libc__vscprintf_l,ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char const *format, locale_t locale, va_list args),(format,locale,args));
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc__vsnprintf_c_l)(char *buf,
                                          size_t bufsize,
                                          char const *format,
                                          locale_t locale,
                                          va_list args) {
	__STDC_INT_AS_SSIZE_T result = libc___stdio_common_vsprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, buf, bufsize, format, locale, args);
	return result < 0 ? -1 : result;
}
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(4) ATTR_LIBC_PRINTF(4, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc__vsnprintf_s_l)(char *buf,
                                          size_t bufsize,
                                          size_t maxsize,
                                          char const *format,
                                          locale_t locale,
                                          va_list args) {
	__STDC_INT_AS_SSIZE_T result = libc___stdio_common_vsnprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, buf, bufsize, maxsize, format, locale, args);
	return result < 0 ? -1 : result;
}
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(LIBCCALL libc__vfprintf_s_l)(FILE *stream,
                                            char const *format,
                                            locale_t locale,
                                            va_list args) {
	return libc___stdio_common_vfprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, stream, format, locale, args);
}
DEFINE_INTERN_ALIAS_P(libc__vfprintf_p_l,libc__vfprintf_l,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF_P(2, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(FILE *stream, char const *format, locale_t locale, va_list args),(stream,format,locale,args));
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(LIBCCALL libc__vfscanf_l)(FILE *stream,
                                         char const *format,
                                         locale_t locale,
                                         va_list args) {
	return libc___stdio_common_vfscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS, stream, format, locale, args);
}
DEFINE_INTERN_ALIAS_P(libc__vfscanf_s_l,libc__vfscanf_l,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(FILE *stream, char const *format, locale_t locale, va_list args),(stream,format,locale,args));
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc__vsnscanf_l)(char const *buf,
                                       size_t bufsize,
                                       char const *format,
                                       locale_t locale,
                                       va_list args) {
	return libc___stdio_common_vsscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS, buf, bufsize, format, locale, args);
}
DEFINE_INTERN_ALIAS_P(libc__vsnscanf_s_l,libc__vsnscanf_l,WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char const *buf, size_t bufsize, char const *format, locale_t locale, va_list args),(buf,bufsize,format,locale,args));
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(LIBCCALL libc__vprintf_l)(char const *format,
                                         locale_t locale,
                                         va_list args) {
	(void)locale;
	return libc_vprintf(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(LIBCCALL libc__vfprintf_l)(FILE *stream,
                                          char const *format,
                                          locale_t locale,
                                          va_list args) {
	(void)locale;
	return libc_vfprintf(stream, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(LIBCCALL libc__vscanf_l)(char const *format,
                                        locale_t locale,
                                        va_list args) {
	(void)locale;
	return libc_vscanf(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(2) ATTR_LIBC_PRINTF(2, 0) ATTR_OUT(1) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc__vsprintf_l)(char *buf,
                                       char const *format,
                                       locale_t locale,
                                       va_list args) {
	(void)locale;
	return libc_vsprintf(buf, format, args);
}
DEFINE_INTERN_ALIAS_P(libc__vprintf_p,libc_vprintf,ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *format, va_list args),(format,args));
/* WARNING: This function returns the number of written character. - Not the required buffer size! */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc__vsnprintf)(char *buf,
                                      size_t bufsize,
                                      char const *format,
                                      va_list args) {
	return libc__vsnprintf_l(buf, bufsize, format, NULL, args);
}
DEFINE_INTERN_ALIAS_P(libc__vsprintf_p,libc_vsnprintf,ATTR_IN(3) ATTR_LIBC_PRINTF_P(3, 0) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char *buf, size_t bufsize, char const *format, va_list args),(buf,bufsize,format,args));
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_IN(4) ATTR_LIBC_PRINTF(4, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc__vsnprintf_s)(char *buf,
                                        size_t bufsize,
                                        size_t maxsize,
                                        char const *format,
                                        va_list args) {
	return libc__vsnprintf_s_l(buf, bufsize, maxsize, format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc__vscprintf)(char const *format,
                                      va_list args) {
	return libc__vscprintf_l(format, NULL, args);
}
DEFINE_INTERN_ALIAS_P(libc__vscprintf_p,libc__vscprintf,WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char const *format, va_list args),(format,args));
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc__vsnprintf_c)(char *buf,
                                        size_t bufsize,
                                        char const *format,
                                        va_list args) {
	return libc__vsnprintf_c_l(buf, bufsize, format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc__vsscanf_l)(char const *buf,
                                      char const *format,
                                      locale_t locale,
                                      va_list args) {
	return libc__vsnscanf_l(buf, (size_t)-1, format, locale, args);
}
DEFINE_INTERN_ALIAS_P(libc__vsscanf_s_l,libc__vsscanf_l,WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char const *buf, char const *format, locale_t locale, va_list args),(buf,format,locale,args));
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc__vsnscanf)(char const *buf,
                                     size_t bufsize,
                                     char const *format,
                                     va_list args) {
	return libc__vsnscanf_l(buf, bufsize, format, NULL, args);
}
DEFINE_INTERN_ALIAS_P(libc__vsnscanf_s,libc__vsnscanf,WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char const *buf, size_t bufsize, char const *format, va_list args),(buf,bufsize,format,args));
#include <libc/template/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(LIBCCALL libc__vprintf_s_l)(char const *format,
                                           locale_t locale,
                                           va_list args) {
	return libc__vfprintf_s_l(stdout, format, locale, args);
}
DEFINE_INTERN_ALIAS_P(libc__vprintf_p_l,libc__vprintf_l,ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *format, locale_t locale, va_list args),(format,locale,args));
#include <libc/template/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(LIBCCALL libc__vscanf_s_l)(char const *format,
                                          locale_t locale,
                                          va_list args) {
	return libc__vfscanf_s_l(stdin, format, locale, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 4) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd__fprintf_l)(FILE *stream,
                                          char const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfprintf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 4) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBCCALL libc__fprintf_l)(FILE *stream,
                                          char const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfprintf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 4) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd__fprintf_s_l)(FILE *stream,
                                            char const *format,
                                            locale_t locale,
                                            ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfprintf_s_l(stream, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 4) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBCCALL libc__fprintf_s_l)(FILE *stream,
                                            char const *format,
                                            locale_t locale,
                                            ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfprintf_s_l(stream, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_INTERN_ALIAS_P(libd__fprintf_p,libd_fprintf,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF_P(2, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(FILE *stream, char const *format, ...),(stream,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_INTERN_ALIAS_P(libc__fprintf_p,libc_fprintf,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF_P(2, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(FILE *stream, char const *format, ...),(stream,format,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_INTERN_ALIAS_P(libd__fprintf_p_l,libd__fprintf_l,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF_P(2, 4),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(FILE *stream, char const *format, locale_t locale, ...),(stream,format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_INTERN_ALIAS_P(libc__fprintf_p_l,libc__fprintf_l,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF_P(2, 4),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(FILE *stream, char const *format, locale_t locale, ...),(stream,format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(1) ATTR_LIBC_PRINTF(1, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd__printf_l)(char const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vprintf_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(1) ATTR_LIBC_PRINTF(1, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBCCALL libc__printf_l)(char const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vprintf_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(1) ATTR_LIBC_PRINTF(1, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd__printf_s_l)(char const *format,
                                           locale_t locale,
                                           ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vprintf_s_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(1) ATTR_LIBC_PRINTF(1, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBCCALL libc__printf_s_l)(char const *format,
                                           locale_t locale,
                                           ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vprintf_s_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_INTERN_ALIAS_P(libd__printf_p,libd_printf,ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char const *format, ...),(format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_INTERN_ALIAS_P(libc__printf_p,libc_printf,ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(char const *format, ...),(format,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_INTERN_ALIAS_P(libd__printf_p_l,libd__printf_l,ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char const *format, locale_t locale, ...),(format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_INTERN_ALIAS_P(libc__printf_p_l,libc__printf_l,ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(char const *format, locale_t locale, ...),(format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(2) ATTR_LIBC_PRINTF(2, 4) ATTR_OUT(1) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__sprintf_l)(char *buf,
                                       char const *format,
                                       locale_t locale,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsprintf_l(buf, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(2) ATTR_LIBC_PRINTF(2, 4) ATTR_OUT(1) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__sprintf_l)(char *buf,
                                       char const *format,
                                       locale_t locale,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsprintf_l(buf, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 5) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__sprintf_s_l)(char *buf,
                                         size_t bufsize,
                                         char const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsprintf_s_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 5) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__sprintf_s_l)(char *buf,
                                         size_t bufsize,
                                         char const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsprintf_s_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_INTERN_ALIAS_P(libd__sprintf_p_l,libd__sprintf_l,ATTR_IN(3) ATTR_LIBC_PRINTF_P(3, 5) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char *buf, size_t bufsize, char const *format, locale_t locale, ...),(buf,bufsize,format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_INTERN_ALIAS_P(libc__sprintf_p_l,libc__sprintf_l,ATTR_IN(3) ATTR_LIBC_PRINTF_P(3, 5) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char *buf, size_t bufsize, char const *format, locale_t locale, ...),(buf,bufsize,format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_INTERN_ALIAS_P(libd__sprintf_p,libd_snprintf,ATTR_IN(3) ATTR_LIBC_PRINTF_P(3, 4) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char *buf, size_t bufsize, char const *format, ...),(buf,bufsize,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_INTERN_ALIAS_P(libc__sprintf_p,libc_snprintf,ATTR_IN(3) ATTR_LIBC_PRINTF_P(3, 4) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char *buf, size_t bufsize, char const *format, ...),(buf,bufsize,format,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 5) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snprintf_l)(char *buf,
                                        size_t bufsize,
                                        char const *format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnprintf_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 5) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__snprintf_l)(char *buf,
                                        size_t bufsize,
                                        char const *format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnprintf_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snprintf)(char *buf,
                                      size_t bufsize,
                                      char const *format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnprintf(buf, bufsize, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__snprintf)(char *buf,
                                      size_t bufsize,
                                      char const *format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnprintf(buf, bufsize, format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 5) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snprintf_c_l)(char *buf,
                                          size_t bufsize,
                                          char const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnprintf_c_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 5) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__snprintf_c_l)(char *buf,
                                          size_t bufsize,
                                          char const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnprintf_c_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snprintf_c)(char *buf,
                                        size_t bufsize,
                                        char const *format,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnprintf_c(buf, bufsize, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__snprintf_c)(char *buf,
                                        size_t bufsize,
                                        char const *format,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnprintf_c(buf, bufsize, format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(4) ATTR_LIBC_PRINTF(4, 6) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snprintf_s_l)(char *buf,
                                          size_t bufsize,
                                          size_t maxsize,
                                          char const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnprintf_s_l(buf, bufsize, maxsize, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(4) ATTR_LIBC_PRINTF(4, 6) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__snprintf_s_l)(char *buf,
                                          size_t bufsize,
                                          size_t maxsize,
                                          char const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnprintf_s_l(buf, bufsize, maxsize, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_IN(4) ATTR_LIBC_PRINTF(4, 5) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snprintf_s)(char *buf,
                                        size_t bufsize,
                                        size_t maxsize,
                                        char const *format,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnprintf_s(buf, bufsize, maxsize, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_IN(4) ATTR_LIBC_PRINTF(4, 5) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__snprintf_s)(char *buf,
                                        size_t bufsize,
                                        size_t maxsize,
                                        char const *format,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnprintf_s(buf, bufsize, maxsize, format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(1) ATTR_LIBC_PRINTF(1, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__scprintf_l)(char const *format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vscprintf_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_IN(1) ATTR_LIBC_PRINTF(1, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__scprintf_l)(char const *format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vscprintf_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__scprintf)(char const *format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vscprintf(format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__scprintf)(char const *format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vscprintf(format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_INTERN_ALIAS_P(libd__scprintf_p_l,libd__scprintf_l,ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char const *format, locale_t locale, ...),(format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_INTERN_ALIAS_P(libc__scprintf_p_l,libc__scprintf_l,ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char const *format, locale_t locale, ...),(format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_INTERN_ALIAS_P(libd__scprintf_p,libd__scprintf,WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char const *format, ...),(format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_INTERN_ALIAS_P(libc__scprintf_p,libc__scprintf,WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char const *format, ...),(format,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 4) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd__fscanf_l)(FILE *stream,
                                         char const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfscanf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 4) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBCCALL libc__fscanf_l)(FILE *stream,
                                         char const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfscanf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 4) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd__fscanf_s_l)(FILE *stream,
                                           char const *format,
                                           locale_t locale,
                                           ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfscanf_s_l(stream, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 4) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBCCALL libc__fscanf_s_l)(FILE *stream,
                                           char const *format,
                                           locale_t locale,
                                           ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfscanf_s_l(stream, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd__scanf_l)(char const *format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vscanf_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBCCALL libc__scanf_l)(char const *format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vscanf_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd__scanf_s_l)(char const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vscanf_s_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBCCALL libc__scanf_s_l)(char const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vscanf_s_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 4) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__sscanf_l)(char const *buf,
                                      char const *format,
                                      locale_t locale,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsscanf_l(buf, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 4) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__sscanf_l)(char const *buf,
                                      char const *format,
                                      locale_t locale,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsscanf_l(buf, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 4) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__sscanf_s_l)(char const *buf,
                                        char const *format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsscanf_s_l(buf, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 4) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__sscanf_s_l)(char const *buf,
                                        char const *format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsscanf_s_l(buf, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 5) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snscanf_l)(char const *buf,
                                       size_t bufsize,
                                       char const *format,
                                       locale_t locale,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnscanf_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 5) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__snscanf_l)(char const *buf,
                                       size_t bufsize,
                                       char const *format,
                                       locale_t locale,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnscanf_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 4) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snscanf)(char const *buf,
                                     size_t bufsize,
                                     char const *format,
                                     ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnscanf(buf, bufsize, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 4) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__snscanf)(char const *buf,
                                     size_t bufsize,
                                     char const *format,
                                     ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnscanf(buf, bufsize, format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 5) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snscanf_s_l)(char const *buf,
                                         size_t bufsize,
                                         char const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnscanf_s_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 5) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__snscanf_s_l)(char const *buf,
                                         size_t bufsize,
                                         char const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnscanf_s_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 4) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snscanf_s)(char const *buf,
                                       size_t bufsize,
                                       char const *format,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnscanf_s(buf, bufsize, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 4) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__snscanf_s)(char const *buf,
                                       size_t bufsize,
                                       char const *format,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnscanf_s(buf, bufsize, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(LIBCCALL libc_vfprintf_s)(FILE *stream,
                                         char const *format,
                                         va_list args) {
	return libc__vfprintf_s_l(stream, format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(LIBCCALL libc_vprintf_s)(char const *format,
                                        va_list args) {
	return libc__vprintf_s_l(format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc_vsprintf_s)(char *buf,
                                      size_t bufsize,
                                      char const *format,
                                      va_list args) {
	return libc__vsprintf_s_l(buf, bufsize, format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_IN(4) ATTR_LIBC_PRINTF(4, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc_vsnprintf_s)(char *buf,
                                       size_t bufsize,
                                       size_t maxsize,
                                       char const *format,
                                       va_list args) {
	return libc__vsnprintf_s_l(buf, bufsize, maxsize, format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(LIBCCALL libc_vfscanf_s)(FILE *stream,
                                        char const *format,
                                        va_list args) {
	return libc__vfscanf_s_l(stream, format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(LIBCCALL libc_vscanf_s)(char const *format,
                                       va_list args) {
	return libc__vscanf_s_l(format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc_vsscanf_s)(char const *buf,
                                     char const *format,
                                     va_list args) {
	return libc__vsscanf_s_l(buf, format, NULL, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd_fprintf_s)(FILE *stream,
                                         char const *format,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfprintf_s(stream, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBCCALL libc_fprintf_s)(FILE *stream,
                                         char const *format,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfprintf_s(stream, format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd_printf_s)(char const *format,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vprintf_s(format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBCCALL libc_printf_s)(char const *format,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vprintf_s(format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd_sprintf_s)(char *buf,
                                      size_t bufsize,
                                      char const *format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vsprintf_s(buf, bufsize, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc_sprintf_s)(char *buf,
                                      size_t bufsize,
                                      char const *format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vsprintf_s(buf, bufsize, format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd_fscanf_s)(FILE *stream,
                                        char const *format,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfscanf_s(stream, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBCCALL libc_fscanf_s)(FILE *stream,
                                        char const *format,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfscanf_s(stream, format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd_scanf_s)(char const *format,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vscanf_s(format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(VLIBCCALL libc_scanf_s)(char const *format,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vscanf_s(format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd_sscanf_s)(char const *buf,
                                     char const *format,
                                     ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vsscanf_s(buf, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc_sscanf_s)(char const *buf,
                                     char const *format,
                                     ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vsscanf_s(buf, format, args);
	va_end(args);
	return result;
}
/* >> fprintf(3), vfprintf(3)
 * Print  data  to  `stream',  following  `format'
 * Return the number of successfully printed bytes */
INTERN ATTR_SECTION(".text.crt.compat.linux") ATTR_IN(1) ATTR_INOUT(3) ATTR_LIBC_PRINTF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_CB_NCX(LIBCCALL libc__doprnt)(char const *__restrict format,
                                      va_list args,
                                      FILE *__restrict stream) {
	return libc_vfprintf(stream, format, args);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(DOS$remove,libd_remove,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *filename),(filename));
DEFINE_PUBLIC_ALIAS_P(remove,libc_remove,ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *filename),(filename));
DEFINE_PUBLIC_ALIAS_P_VOID(setbuf,libc_setbuf,ATTR_INOUT(1),NOTHROW_NCX,LIBCCALL,(FILE *__restrict stream, char *buf),(stream,buf));
DEFINE_PUBLIC_ALIAS_P(_fgetchar,libc_getchar,,int,NOTHROW_CB_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(getchar_locked,libc_getchar,,int,NOTHROW_CB_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(getchar,libc_getchar,,int,NOTHROW_CB_NCX,LIBCCALL,(void),());
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_fputchar,libc_putchar,,int,NOTHROW_CB_NCX,LIBCCALL,(int ch),(ch));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(putchar_locked,libc_putchar,,int,NOTHROW_CB_NCX,LIBCCALL,(int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(putchar,libc_putchar,,int,NOTHROW_CB_NCX,LIBCCALL,(int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_IO_fgets,libc_fgets,WUNUSED ATTR_INOUT(3) ATTR_OUTS(1, 2),char *,NOTHROW_CB_NCX,LIBCCALL,(char *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream),(buf,bufsize,stream));
DEFINE_PUBLIC_ALIAS_P(fgets,libc_fgets,WUNUSED ATTR_INOUT(3) ATTR_OUTS(1, 2),char *,NOTHROW_CB_NCX,LIBCCALL,(char *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream),(buf,bufsize,stream));
DEFINE_PUBLIC_ALIAS_P(_IO_fputs,libc_fputs,ATTR_IN(1) ATTR_INOUT(2),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *__restrict string, FILE *__restrict stream),(string,stream));
DEFINE_PUBLIC_ALIAS_P(fputs,libc_fputs,ATTR_IN(1) ATTR_INOUT(2),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *__restrict string, FILE *__restrict stream),(string,stream));
DEFINE_PUBLIC_ALIAS_P(_IO_puts,libc_puts,ATTR_IN(1),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *__restrict string),(string));
DEFINE_PUBLIC_ALIAS_P(puts,libc_puts,ATTR_IN(1),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *__restrict string),(string));
DEFINE_PUBLIC_ALIAS_P_VOID(_IO_perror,libc_perror,,NOTHROW_RPC,LIBCCALL,(char const *message),(message));
DEFINE_PUBLIC_ALIAS_P_VOID(perror,libc_perror,,NOTHROW_RPC,LIBCCALL,(char const *message),(message));
DEFINE_PUBLIC_ALIAS_P(tmpfile,libc_tmpfile,WUNUSED,FILE *,NOTHROW_RPC,LIBCCALL,(void),());
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_IO_fprintf,libd_fprintf,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(FILE *__restrict stream, char const *__restrict format, ...),(stream,format,));
DEFINE_PUBLIC_ALIAS_P(DOS$fprintf,libd_fprintf,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(FILE *__restrict stream, char const *__restrict format, ...),(stream,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_IO_fprintf,libc_fprintf,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(FILE *__restrict stream, char const *__restrict format, ...),(stream,format,));
DEFINE_PUBLIC_ALIAS_P(fprintf,libc_fprintf,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(FILE *__restrict stream, char const *__restrict format, ...),(stream,format,));
DEFINE_PUBLIC_ALIAS_P(vprintf,libc_vprintf,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *__restrict format, va_list args),(format,args));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_IO_printf,libd_printf,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char const *__restrict format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P(DOS$printf_s,libd_printf,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char const *__restrict format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P(DOS$printf,libd_printf,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char const *__restrict format, ...),(format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_IO_printf,libc_printf,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(char const *__restrict format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P(printf_s,libc_printf,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(char const *__restrict format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P(printf,libc_printf,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(char const *__restrict format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P(_IO_vfscanf,libc_vfscanf,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBCCALL,(FILE *__restrict stream, char const *__restrict format, va_list args),(stream,format,args));
DEFINE_PUBLIC_ALIAS_P(__vfscanf,libc_vfscanf,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBCCALL,(FILE *__restrict stream, char const *__restrict format, va_list args),(stream,format,args));
DEFINE_PUBLIC_ALIAS_P(_doscan,libc_vfscanf,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBCCALL,(FILE *__restrict stream, char const *__restrict format, va_list args),(stream,format,args));
DEFINE_PUBLIC_ALIAS_P(vfscanf,libc_vfscanf,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBCCALL,(FILE *__restrict stream, char const *__restrict format, va_list args),(stream,format,args));
DEFINE_PUBLIC_ALIAS_P(_IO_vscanf,libc_vscanf,WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *__restrict format, va_list args),(format,args));
DEFINE_PUBLIC_ALIAS_P(vscanf,libc_vscanf,WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *__restrict format, va_list args),(format,args));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_IO_fscanf,libd_fscanf,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(FILE *__restrict stream, char const *__restrict format, ...),(stream,format,));
DEFINE_PUBLIC_ALIAS_P(DOS$fscanf,libd_fscanf,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(FILE *__restrict stream, char const *__restrict format, ...),(stream,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_IO_fscanf,libc_fscanf,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(FILE *__restrict stream, char const *__restrict format, ...),(stream,format,));
DEFINE_PUBLIC_ALIAS_P(fscanf,libc_fscanf,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(FILE *__restrict stream, char const *__restrict format, ...),(stream,format,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_IO_scanf,libd_scanf,WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char const *__restrict format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P(DOS$scanf,libd_scanf,WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char const *__restrict format, ...),(format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_IO_scanf,libc_scanf,WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(char const *__restrict format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P(scanf,libc_scanf,WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(char const *__restrict format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P(_IO_gets,libc_gets,WUNUSED ATTR_OUT(1),char *,NOTHROW_CB_NCX,LIBCCALL,(char *__restrict buf),(buf));
DEFINE_PUBLIC_ALIAS_P(gets,libc_gets,WUNUSED ATTR_OUT(1),char *,NOTHROW_CB_NCX,LIBCCALL,(char *__restrict buf),(buf));
DEFINE_PUBLIC_ALIAS_P(__vsscanf,libc_vsscanf,WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 0),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,LIBCCALL,(char const *__restrict input, char const *__restrict format, va_list args),(input,format,args));
DEFINE_PUBLIC_ALIAS_P(_IO_vsscanf,libc_vsscanf,WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 0),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,LIBCCALL,(char const *__restrict input, char const *__restrict format, va_list args),(input,format,args));
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS_P(vsscanf,libc_vsscanf,WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 0),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,LIBCCALL,(char const *__restrict input, char const *__restrict format, va_list args),(input,format,args));
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_IO_sscanf,libd_sscanf,ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,VLIBDCALL,(char const *__restrict input, char const *__restrict format, ...),(input,format,));
DEFINE_PUBLIC_ALIAS_P(DOS$sscanf,libd_sscanf,ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,VLIBDCALL,(char const *__restrict input, char const *__restrict format, ...),(input,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_IO_sscanf,libc_sscanf,ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,VLIBCCALL,(char const *__restrict input, char const *__restrict format, ...),(input,format,));
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS_P(sscanf,libc_sscanf,ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,VLIBCCALL,(char const *__restrict input, char const *__restrict format, ...),(input,format,));
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_IO_vsprintf,libc_vsprintf,ATTR_IN(2) ATTR_LIBC_PRINTF(2, 0) ATTR_OUT(1),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char *__restrict dest, char const *__restrict format, va_list args),(dest,format,args));
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS_P(vsprintf,libc_vsprintf,ATTR_IN(2) ATTR_LIBC_PRINTF(2, 0) ATTR_OUT(1),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char *__restrict dest, char const *__restrict format, va_list args),(dest,format,args));
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_IO_sprintf,libd_sprintf,ATTR_IN(2) ATTR_LIBC_PRINTF(2, 3) ATTR_OUT(1),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,VLIBDCALL,(char *__restrict buf, char const *__restrict format, ...),(buf,format,));
DEFINE_PUBLIC_ALIAS_P(DOS$sprintf,libd_sprintf,ATTR_IN(2) ATTR_LIBC_PRINTF(2, 3) ATTR_OUT(1),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,VLIBDCALL,(char *__restrict buf, char const *__restrict format, ...),(buf,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_IO_sprintf,libc_sprintf,ATTR_IN(2) ATTR_LIBC_PRINTF(2, 3) ATTR_OUT(1),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,VLIBCCALL,(char *__restrict buf, char const *__restrict format, ...),(buf,format,));
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS_P(sprintf,libc_sprintf,ATTR_IN(2) ATTR_LIBC_PRINTF(2, 3) ATTR_OUT(1),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,VLIBCCALL,(char *__restrict buf, char const *__restrict format, ...),(buf,format,));
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(__vsnprintf,libc_vsnprintf,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 0) ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,LIBCCALL,(char *__restrict buf, size_t buflen, char const *__restrict format, va_list args),(buf,buflen,format,args));
DEFINE_PUBLIC_ALIAS_P(_IO_vsnprintf,libc_vsnprintf,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 0) ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,LIBCCALL,(char *__restrict buf, size_t buflen, char const *__restrict format, va_list args),(buf,buflen,format,args));
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS_P(vsnprintf,libc_vsnprintf,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 0) ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,LIBCCALL,(char *__restrict buf, size_t buflen, char const *__restrict format, va_list args),(buf,buflen,format,args));
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$__snprintf,libd_snprintf,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,VLIBDCALL,(char *__restrict buf, size_t buflen, char const *__restrict format, ...),(buf,buflen,format,));
DEFINE_PUBLIC_ALIAS_P(DOS$snprintf,libd_snprintf,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,VLIBDCALL,(char *__restrict buf, size_t buflen, char const *__restrict format, ...),(buf,buflen,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(__snprintf,libc_snprintf,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,VLIBCCALL,(char *__restrict buf, size_t buflen, char const *__restrict format, ...),(buf,buflen,format,));
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS_P(snprintf,libc_snprintf,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,VLIBCCALL,(char *__restrict buf, size_t buflen, char const *__restrict format, ...),(buf,buflen,format,));
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_IO_vdprintf,libc_vdprintf,ATTR_FDWRITE(1) ATTR_IN(2) ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_RPC,LIBCCALL,(fd_t fd, char const *__restrict format, va_list args),(fd,format,args));
DEFINE_PUBLIC_ALIAS_P(vdprintf,libc_vdprintf,ATTR_FDWRITE(1) ATTR_IN(2) ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_RPC,LIBCCALL,(fd_t fd, char const *__restrict format, va_list args),(fd,format,args));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$dprintf,libd_dprintf,ATTR_FDWRITE(1) ATTR_IN(2) ATTR_LIBC_PRINTF(2, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_RPC,VLIBDCALL,(fd_t fd, char const *__restrict format, ...),(fd,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(dprintf,libc_dprintf,ATTR_FDWRITE(1) ATTR_IN(2) ATTR_LIBC_PRINTF(2, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_RPC,VLIBCCALL,(fd_t fd, char const *__restrict format, ...),(fd,format,));
DEFINE_PUBLIC_ALIAS_P(DOS$removeat,libd_removeat,ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(fd_t dirfd, char const *filename),(dirfd,filename));
DEFINE_PUBLIC_ALIAS_P(removeat,libc_removeat,ATTR_IN(2),int,NOTHROW_RPC,LIBCCALL,(fd_t dirfd, char const *filename),(dirfd,filename));
DEFINE_PUBLIC_ALIAS_P(tmpnam_r,libc_tmpnam_r,WUNUSED ATTR_OUT_OPT(1),char *,NOTHROW_NCX,LIBCCALL,(char *buf),(buf));
DEFINE_PUBLIC_ALIAS_P_VOID(_IO_setbuffer,libc_setbuffer,ATTR_INOUT(1),NOTHROW_NCX,LIBCCALL,(FILE *__restrict stream, char *buf, size_t bufsize),(stream,buf,bufsize));
DEFINE_PUBLIC_ALIAS_P_VOID(_IO_default_setbuf,libc_setbuffer,ATTR_INOUT(1),NOTHROW_NCX,LIBCCALL,(FILE *__restrict stream, char *buf, size_t bufsize),(stream,buf,bufsize));
DEFINE_PUBLIC_ALIAS_P_VOID(setbuffer,libc_setbuffer,ATTR_INOUT(1),NOTHROW_NCX,LIBCCALL,(FILE *__restrict stream, char *buf, size_t bufsize),(stream,buf,bufsize));
DEFINE_PUBLIC_ALIAS_P_VOID(setlinebuf,libc_setlinebuf,ATTR_INOUT(1),NOTHROW_NCX,LIBCCALL,(FILE *__restrict stream),(stream));
DEFINE_PUBLIC_ALIAS_P(vasnprintf,libc_vasnprintf,WUNUSED ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) ATTR_LIBC_PRINTF(3, 0),char *,NOTHROW_NCX,LIBCCALL,(char *heapbuf, size_t *p_buflen, char const *format, va_list args),(heapbuf,p_buflen,format,args));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$asnprintf,libd_asnprintf,WUNUSED ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) ATTR_LIBC_PRINTF(3, 4),char *,NOTHROW_NCX,VLIBDCALL,(char *__restrict heapbuf, size_t *__restrict p_buflen, char const *__restrict format, ...),(heapbuf,p_buflen,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(asnprintf,libc_asnprintf,WUNUSED ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) ATTR_LIBC_PRINTF(3, 4),char *,NOTHROW_NCX,VLIBCCALL,(char *__restrict heapbuf, size_t *__restrict p_buflen, char const *__restrict format, ...),(heapbuf,p_buflen,format,));
DEFINE_PUBLIC_ALIAS_P(fmemopen,libc_fmemopen,WUNUSED ATTR_IN(3) ATTR_INOUTS(1, 2),FILE *,NOTHROW_NCX,LIBCCALL,(void *mem, size_t len, char const *modes),(mem,len,modes));
DEFINE_PUBLIC_ALIAS_P(open_memstream,libc_open_memstream,WUNUSED NONNULL((1, 2)),FILE *,NOTHROW_NCX,LIBCCALL,(char **bufloc, size_t *sizeloc),(bufloc,sizeloc));
DEFINE_PUBLIC_ALIAS_P(__getdelim,libc_getdelim,WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) ATTR_INOUT(4),ssize_t,NOTHROW_CB_NCX,LIBCCALL,(char **__restrict lineptr, size_t *__restrict pcount, int delimiter, FILE *__restrict stream),(lineptr,pcount,delimiter,stream));
DEFINE_PUBLIC_ALIAS_P(_IO_getdelim,libc_getdelim,WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) ATTR_INOUT(4),ssize_t,NOTHROW_CB_NCX,LIBCCALL,(char **__restrict lineptr, size_t *__restrict pcount, int delimiter, FILE *__restrict stream),(lineptr,pcount,delimiter,stream));
DEFINE_PUBLIC_ALIAS_P(getdelim,libc_getdelim,WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) ATTR_INOUT(4),ssize_t,NOTHROW_CB_NCX,LIBCCALL,(char **__restrict lineptr, size_t *__restrict pcount, int delimiter, FILE *__restrict stream),(lineptr,pcount,delimiter,stream));
DEFINE_PUBLIC_ALIAS_P(__getline,libc_getline,WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) ATTR_INOUT(3),ssize_t,NOTHROW_CB_NCX,LIBCCALL,(char **__restrict lineptr, size_t *__restrict pcount, FILE *__restrict stream),(lineptr,pcount,stream));
DEFINE_PUBLIC_ALIAS_P(_IO_getline,libc_getline,WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) ATTR_INOUT(3),ssize_t,NOTHROW_CB_NCX,LIBCCALL,(char **__restrict lineptr, size_t *__restrict pcount, FILE *__restrict stream),(lineptr,pcount,stream));
DEFINE_PUBLIC_ALIAS_P(getline,libc_getline,WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) ATTR_INOUT(3),ssize_t,NOTHROW_CB_NCX,LIBCCALL,(char **__restrict lineptr, size_t *__restrict pcount, FILE *__restrict stream),(lineptr,pcount,stream));
DEFINE_PUBLIC_ALIAS_P(getchar_unlocked,libc_getchar_unlocked,,int,NOTHROW_CB_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(putchar_unlocked,libc_putchar_unlocked,,int,NOTHROW_CB_NCX,LIBCCALL,(int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(__overflow,libc___overflow,ATTR_INOUT(1),int,NOTHROW_CB_NCX,LIBCCALL,(FILE *stream, int ch),(stream,ch));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_getw,libc_getw,ATTR_INOUT(1),int,NOTHROW_CB_NCX,LIBCCALL,(FILE *__restrict stream),(stream));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(getw,libc_getw,ATTR_INOUT(1),int,NOTHROW_CB_NCX,LIBCCALL,(FILE *__restrict stream),(stream));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_putw,libc_putw,ATTR_INOUT(2),int,NOTHROW_CB_NCX,LIBCCALL,(int w, FILE *__restrict stream),(w,stream));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(putw,libc_putw,ATTR_INOUT(2),int,NOTHROW_CB_NCX,LIBCCALL,(int w, FILE *__restrict stream),(w,stream));
DEFINE_PUBLIC_ALIAS_P(fopencookie,libc_fopencookie,WUNUSED ATTR_IN(2),FILE *,NOTHROW_NCX,LIBCCALL,(void *__restrict magic_cookie, char const *__restrict modes, cookie_io_functions_t io_funcs),(magic_cookie,modes,io_funcs));
DEFINE_PUBLIC_ALIAS_P(fgets_unlocked,libc_fgets_unlocked,WUNUSED ATTR_INOUT(3) ATTR_OUTS(1, 2),char *,NOTHROW_CB_NCX,LIBCCALL,(char *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream),(buf,bufsize,stream));
DEFINE_PUBLIC_ALIAS_P(fputs_unlocked,libc_fputs_unlocked,ATTR_IN(1) ATTR_INOUT(2),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *__restrict string, FILE *__restrict stream),(string,stream));
DEFINE_PUBLIC_ALIAS_P(obstack_vprintf,libc_obstack_vprintf,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,LIBCCALL,(struct obstack *__restrict self, char const *__restrict format, va_list args),(self,format,args));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$obstack_printf,libd_obstack_printf,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,VLIBDCALL,(struct obstack *__restrict self, char const *__restrict format, ...),(self,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(obstack_printf,libc_obstack_printf,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,VLIBCCALL,(struct obstack *__restrict self, char const *__restrict format, ...),(self,format,));
DEFINE_PUBLIC_ALIAS_P(tmpfile64,libc_tmpfile64,WUNUSED,FILE *,NOTHROW_RPC,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(fopen_printer,libc_fopen_printer,WUNUSED NONNULL((1)),FILE *,NOTHROW_NCX,LIBCCALL,(__pformatprinter printer, void *arg),(printer,arg));
DEFINE_PUBLIC_ALIAS_P(_IO_vasprintf,libc_vasprintf,ATTR_IN(2) ATTR_LIBC_PRINTF(2, 0) ATTR_OUT(1),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char **__restrict pstr, char const *__restrict format, va_list args),(pstr,format,args));
DEFINE_PUBLIC_ALIAS_P(vasprintf,libc_vasprintf,ATTR_IN(2) ATTR_LIBC_PRINTF(2, 0) ATTR_OUT(1),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char **__restrict pstr, char const *__restrict format, va_list args),(pstr,format,args));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$__asprintf,libd_asprintf,ATTR_IN(2) ATTR_LIBC_PRINTF(2, 3) ATTR_OUT(1),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char **__restrict pstr, char const *__restrict format, ...),(pstr,format,));
DEFINE_PUBLIC_ALIAS_P(DOS$asprintf,libd_asprintf,ATTR_IN(2) ATTR_LIBC_PRINTF(2, 3) ATTR_OUT(1),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char **__restrict pstr, char const *__restrict format, ...),(pstr,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(__asprintf,libc_asprintf,ATTR_IN(2) ATTR_LIBC_PRINTF(2, 3) ATTR_OUT(1),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char **__restrict pstr, char const *__restrict format, ...),(pstr,format,));
DEFINE_PUBLIC_ALIAS_P(asprintf,libc_asprintf,ATTR_IN(2) ATTR_LIBC_PRINTF(2, 3) ATTR_OUT(1),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char **__restrict pstr, char const *__restrict format, ...),(pstr,format,));
DEFINE_PUBLIC_ALIAS_P(getw_unlocked,libc_getw_unlocked,ATTR_INOUT(1),int,NOTHROW_CB_NCX,LIBCCALL,(FILE *__restrict stream),(stream));
DEFINE_PUBLIC_ALIAS_P(putw_unlocked,libc_putw_unlocked,ATTR_INOUT(2),int,NOTHROW_CB_NCX,LIBCCALL,(int w, FILE *__restrict stream),(w,stream));
DEFINE_PUBLIC_ALIAS_P(getdelim_unlocked,libc_getdelim_unlocked,WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) ATTR_INOUT(4),ssize_t,NOTHROW_CB_NCX,LIBCCALL,(char **__restrict lineptr, size_t *__restrict pcount, int delimiter, FILE *__restrict stream),(lineptr,pcount,delimiter,stream));
DEFINE_PUBLIC_ALIAS_P(getline_unlocked,libc_getline_unlocked,WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) ATTR_INOUT(3),ssize_t,NOTHROW_CB_NCX,LIBCCALL,(char **__restrict lineptr, size_t *__restrict pcount, FILE *__restrict stream),(lineptr,pcount,stream));
DEFINE_PUBLIC_ALIAS_P(puts_unlocked,libc_puts_unlocked,ATTR_IN(1),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *__restrict string),(string));
DEFINE_PUBLIC_ALIAS_P(vfprintf_unlocked,libc_vfprintf_unlocked,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(FILE *__restrict stream, char const *__restrict format, va_list args),(stream,format,args));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$fprintf_s,libd_fprintf_unlocked,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(FILE *__restrict stream, char const *__restrict format, ...),(stream,format,));
DEFINE_PUBLIC_ALIAS_P(DOS$fprintf_unlocked,libd_fprintf_unlocked,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(FILE *__restrict stream, char const *__restrict format, ...),(stream,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(fprintf_s,libc_fprintf_unlocked,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(FILE *__restrict stream, char const *__restrict format, ...),(stream,format,));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(fprintf_unlocked,libc_fprintf_unlocked,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(FILE *__restrict stream, char const *__restrict format, ...),(stream,format,));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(vprintf_s,libc_vprintf_unlocked,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *__restrict format, va_list args),(format,args));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(vprintf_unlocked,libc_vprintf_unlocked,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *__restrict format, va_list args),(format,args));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$printf_s,libd_printf_unlocked,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char const *__restrict format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P(DOS$printf_unlocked,libd_printf_unlocked,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char const *__restrict format, ...),(format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(printf_s,libc_printf_unlocked,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(char const *__restrict format, ...),(format,));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(printf_unlocked,libc_printf_unlocked,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(char const *__restrict format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P(vfscanf_unlocked,libc_vfscanf_unlocked,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBCCALL,(FILE *__restrict stream, char const *__restrict format, va_list args),(stream,format,args));
DEFINE_PUBLIC_ALIAS_P(vscanf_unlocked,libc_vscanf_unlocked,WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *__restrict format, va_list args),(format,args));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$fscanf_unlocked,libd_fscanf_unlocked,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(FILE *__restrict stream, char const *__restrict format, ...),(stream,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(fscanf_unlocked,libc_fscanf_unlocked,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(FILE *__restrict stream, char const *__restrict format, ...),(stream,format,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$scanf_unlocked,libd_scanf_unlocked,WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char const *__restrict format, ...),(format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(scanf_unlocked,libc_scanf_unlocked,WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(char const *__restrict format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P(fmtcheck,libc_fmtcheck,ATTR_RETNONNULL WUNUSED ATTR_IN(2) ATTR_IN_OPT(1) __ATTR_FORMAT_ARG(2),char const *,NOTHROW_NCX,LIBCCALL,(char const *user_format, char const *good_format),(user_format,good_format));
DEFINE_PUBLIC_ALIAS_P(funopen,libc_funopen,WUNUSED,FILE *,NOTHROW_NCX,LIBCCALL,(void const *cookie, int (LIBKCALL *readfn)(void *cookie, char *buf, int num_bytes), int (LIBKCALL *writefn)(void *cookie, char const *buf, int num_bytes), off_t (LIBKCALL *seekfn)(void *cookie, off_t off, int whence), int (LIBKCALL *closefn)(void *cookie)),(cookie,readfn,writefn,seekfn,closefn));
DEFINE_PUBLIC_ALIAS_P(funopen64,libc_funopen64,WUNUSED,FILE *,NOTHROW_NCX,LIBCCALL,(void const *cookie, int (LIBKCALL *readfn)(void *cookie, char *buf, int num_bytes), int (LIBKCALL *writefn)(void *cookie, char const *buf, int num_bytes), off64_t (LIBKCALL *seekfn)(void *cookie, off64_t off, int whence), int (LIBKCALL *closefn)(void *cookie)),(cookie,readfn,writefn,seekfn,closefn));
DEFINE_PUBLIC_ALIAS_P(DOS$_fsopen,libd__fsopen,WUNUSED ATTR_IN(1) ATTR_IN(2),FILE *,NOTHROW_RPC,LIBDCALL,(char const *filename, char const *modes, __STDC_INT_AS_UINT_T sflag),(filename,modes,sflag));
DEFINE_PUBLIC_ALIAS_P(_fsopen,libc__fsopen,WUNUSED ATTR_IN(1) ATTR_IN(2),FILE *,NOTHROW_RPC,LIBCCALL,(char const *filename, char const *modes, __STDC_INT_AS_UINT_T sflag),(filename,modes,sflag));
DEFINE_PUBLIC_ALIAS_P(_getmaxstdio,libc__getmaxstdio,WUNUSED,int,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(_setmaxstdio,libc__setmaxstdio,,int,NOTHROW_NCX,LIBCCALL,(int newmaxval),(newmaxval));
DEFINE_PUBLIC_ALIAS_P(DOS$fopen_s,libd_fopen_s,ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1),errno_t,NOTHROW_RPC,LIBDCALL,(FILE **pstream, char const *filename, char const *modes),(pstream,filename,modes));
DEFINE_PUBLIC_ALIAS_P(fopen_s,libc_fopen_s,ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1),errno_t,NOTHROW_RPC,LIBCCALL,(FILE **pstream, char const *filename, char const *modes),(pstream,filename,modes));
DEFINE_PUBLIC_ALIAS_P(DOS$freopen_s,libd_freopen_s,ATTR_IN(2) ATTR_IN(3) ATTR_INOUT(4) ATTR_OUT(1),errno_t,NOTHROW_RPC,LIBDCALL,(FILE **pstream, char const *filename, char const *modes, FILE *oldstream),(pstream,filename,modes,oldstream));
DEFINE_PUBLIC_ALIAS_P(freopen_s,libc_freopen_s,ATTR_IN(2) ATTR_IN(3) ATTR_INOUT(4) ATTR_OUT(1),errno_t,NOTHROW_RPC,LIBCCALL,(FILE **pstream, char const *filename, char const *modes, FILE *oldstream),(pstream,filename,modes,oldstream));
DEFINE_PUBLIC_ALIAS_P(tmpnam_s,libc_tmpnam_s,ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(char *__restrict buf, rsize_t bufsize),(buf,bufsize));
DEFINE_PUBLIC_ALIAS_P(clearerr_s,libc_clearerr_s,ATTR_INOUT(1),errno_t,NOTHROW_NCX,LIBCCALL,(FILE *__restrict stream),(stream));
DEFINE_PUBLIC_ALIAS_P(tmpfile_s,libc_tmpfile_s,ATTR_OUT(1),errno_t,NOTHROW_RPC,LIBCCALL,(FILE **pstream),(pstream));
DEFINE_PUBLIC_ALIAS_P(fread_s,libc_fread_s,WUNUSED ATTR_INOUT(5) ATTR_OUT_OPT(1),size_t,NOTHROW_CB_NCX,LIBCCALL,(void *__restrict buf, size_t bufsize, size_t elemsize, size_t elemcount, FILE *__restrict stream),(buf,bufsize,elemsize,elemcount,stream));
DEFINE_PUBLIC_ALIAS_P(gets_s,libc_gets_s,WUNUSED ATTR_OUTS(1, 2),char *,NOTHROW_CB_NCX,LIBCCALL,(char *__restrict buf, rsize_t bufsize),(buf,bufsize));
DEFINE_PUBLIC_ALIAS_P(_fread_nolock_s,libc__fread_nolock_s,WUNUSED ATTR_INOUT(5) ATTR_IN_OPT(1),size_t,NOTHROW_CB_NCX,LIBCCALL,(void *__restrict buf, size_t bufsize, size_t elemsize, size_t elemcount, FILE *__restrict stream),(buf,bufsize,elemsize,elemcount,stream));
DEFINE_PUBLIC_ALIAS_P(__stdio_common_vfprintf,libc___stdio_common_vfprintf,ATTR_IN(3) ATTR_INOUT(2) ATTR_LIBC_PRINTF(3, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(uint64_t options, FILE *stream, char const *format, locale_t locale, va_list args),(options,stream,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(__stdio_common_vfprintf_s,libc___stdio_common_vfprintf_s,ATTR_IN(3) ATTR_INOUT(2) ATTR_LIBC_PRINTF(3, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(uint64_t options, FILE *stream, char const *format, locale_t locale, va_list args),(options,stream,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(__stdio_common_vfprintf_p,libc___stdio_common_vfprintf_p,ATTR_IN(3) ATTR_INOUT(2) ATTR_LIBC_PRINTF_P(3, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(uint64_t options, FILE *stream, char const *format, locale_t locale, va_list args),(options,stream,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(__stdio_common_vsprintf,libc___stdio_common_vsprintf,ATTR_IN(4) ATTR_LIBC_PRINTF(4, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(uint64_t options, char *buf, size_t bufsize, char const *format, locale_t locale, va_list args),(options,buf,bufsize,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(__stdio_common_vsprintf_s,libc___stdio_common_vsprintf_s,ATTR_IN(4) ATTR_LIBC_PRINTF(4, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(uint64_t options, char *buf, size_t bufsize, char const *format, locale_t locale, va_list args),(options,buf,bufsize,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(__stdio_common_vsnprintf_s,libc___stdio_common_vsnprintf_s,ATTR_IN(5) ATTR_LIBC_PRINTF(5, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(uint64_t options, char *buf, size_t bufsize, size_t maxsize, char const *format, locale_t locale, va_list args),(options,buf,bufsize,maxsize,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(__stdio_common_vsprintf_p,libc___stdio_common_vsprintf_p,ATTR_IN(4) ATTR_LIBC_PRINTF_P(4, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(uint64_t options, char *buf, size_t bufsize, char const *format, locale_t locale, va_list args),(options,buf,bufsize,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(__stdio_common_vfscanf,libc___stdio_common_vfscanf,WUNUSED ATTR_IN(3) ATTR_INOUT(2) ATTR_LIBC_SCANF(3, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(uint64_t options, FILE *stream, char const *format, locale_t locale, va_list args),(options,stream,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(__stdio_common_vsscanf,libc___stdio_common_vsscanf,WUNUSED ATTR_IN(4) ATTR_INS(2, 3) ATTR_LIBC_SCANF(4, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(uint64_t options, char const *input, size_t inputsize, char const *format, locale_t locale, va_list args),(options,input,inputsize,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(_vsnprintf_l,libc__vsnprintf_l,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 0) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char *buf, size_t bufsize, char const *format, locale_t locale, va_list args),(buf,bufsize,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(_vsprintf_s_l,libc__vsprintf_s_l,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 0) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char *buf, size_t bufsize, char const *format, locale_t locale, va_list args),(buf,bufsize,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(_vsprintf_p_l,libc__vsprintf_p_l,ATTR_IN(3) ATTR_LIBC_PRINTF_P(3, 0) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char *buf, size_t bufsize, char const *format, locale_t locale, va_list args),(buf,bufsize,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(_vscprintf_l,libc__vscprintf_l,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char const *format, locale_t locale, va_list args),(format,locale,args));
DEFINE_PUBLIC_ALIAS_P(_vscprintf_p_l,libc__vscprintf_p_l,ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char const *format, locale_t locale, va_list args),(format,locale,args));
DEFINE_PUBLIC_ALIAS_P(_vsnprintf_c_l,libc__vsnprintf_c_l,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 0) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char *buf, size_t bufsize, char const *format, locale_t locale, va_list args),(buf,bufsize,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(_vsnprintf_s_l,libc__vsnprintf_s_l,ATTR_IN(4) ATTR_LIBC_PRINTF(4, 0) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char *buf, size_t bufsize, size_t maxsize, char const *format, locale_t locale, va_list args),(buf,bufsize,maxsize,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(_vfprintf_s_l,libc__vfprintf_s_l,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(FILE *stream, char const *format, locale_t locale, va_list args),(stream,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(_vfprintf_p_l,libc__vfprintf_p_l,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF_P(2, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(FILE *stream, char const *format, locale_t locale, va_list args),(stream,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(_vfscanf_l,libc__vfscanf_l,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(FILE *stream, char const *format, locale_t locale, va_list args),(stream,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(_vfscanf_s_l,libc__vfscanf_s_l,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(FILE *stream, char const *format, locale_t locale, va_list args),(stream,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(_vsnscanf_l,libc__vsnscanf_l,WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char const *buf, size_t bufsize, char const *format, locale_t locale, va_list args),(buf,bufsize,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(_vsnscanf_s_l,libc__vsnscanf_s_l,WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char const *buf, size_t bufsize, char const *format, locale_t locale, va_list args),(buf,bufsize,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(_vprintf_l,libc__vprintf_l,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *format, locale_t locale, va_list args),(format,locale,args));
DEFINE_PUBLIC_ALIAS_P(_vfprintf_l,libc__vfprintf_l,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(FILE *stream, char const *format, locale_t locale, va_list args),(stream,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(_vscanf_l,libc__vscanf_l,WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *format, locale_t locale, va_list args),(format,locale,args));
DEFINE_PUBLIC_ALIAS_P(_vsprintf_l,libc__vsprintf_l,ATTR_IN(2) ATTR_LIBC_PRINTF(2, 0) ATTR_OUT(1),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char *buf, char const *format, locale_t locale, va_list args),(buf,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(_vprintf_p,libc__vprintf_p,ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *format, va_list args),(format,args));
DEFINE_PUBLIC_ALIAS_P(_vsnprintf,libc__vsnprintf,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 0) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char *buf, size_t bufsize, char const *format, va_list args),(buf,bufsize,format,args));
DEFINE_PUBLIC_ALIAS_P(_vsprintf_p,libc__vsprintf_p,ATTR_IN(3) ATTR_LIBC_PRINTF_P(3, 0) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char *buf, size_t bufsize, char const *format, va_list args),(buf,bufsize,format,args));
DEFINE_PUBLIC_ALIAS_P(_vsnprintf_s,libc__vsnprintf_s,ATTR_IN(4) ATTR_LIBC_PRINTF(4, 0) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char *buf, size_t bufsize, size_t maxsize, char const *format, va_list args),(buf,bufsize,maxsize,format,args));
DEFINE_PUBLIC_ALIAS_P(_vscprintf,libc__vscprintf,WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char const *format, va_list args),(format,args));
DEFINE_PUBLIC_ALIAS_P(_vscprintf_p,libc__vscprintf_p,WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char const *format, va_list args),(format,args));
DEFINE_PUBLIC_ALIAS_P(_vsnprintf_c,libc__vsnprintf_c,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 0) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char *buf, size_t bufsize, char const *format, va_list args),(buf,bufsize,format,args));
DEFINE_PUBLIC_ALIAS_P(_vsscanf_l,libc__vsscanf_l,WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char const *buf, char const *format, locale_t locale, va_list args),(buf,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(_vsscanf_s_l,libc__vsscanf_s_l,WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char const *buf, char const *format, locale_t locale, va_list args),(buf,format,locale,args));
DEFINE_PUBLIC_ALIAS_P(_vsnscanf,libc__vsnscanf,WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char const *buf, size_t bufsize, char const *format, va_list args),(buf,bufsize,format,args));
DEFINE_PUBLIC_ALIAS_P(_vsnscanf_s,libc__vsnscanf_s,WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char const *buf, size_t bufsize, char const *format, va_list args),(buf,bufsize,format,args));
DEFINE_PUBLIC_ALIAS_P(_vprintf_s_l,libc__vprintf_s_l,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *format, locale_t locale, va_list args),(format,locale,args));
DEFINE_PUBLIC_ALIAS_P(_vprintf_p_l,libc__vprintf_p_l,ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *format, locale_t locale, va_list args),(format,locale,args));
DEFINE_PUBLIC_ALIAS_P(_vscanf_s_l,libc__vscanf_s_l,WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *format, locale_t locale, va_list args),(format,locale,args));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_fprintf_l,libd__fprintf_l,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 4),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(FILE *stream, char const *format, locale_t locale, ...),(stream,format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_fprintf_l,libc__fprintf_l,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 4),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(FILE *stream, char const *format, locale_t locale, ...),(stream,format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_fprintf_s_l,libd__fprintf_s_l,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 4),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(FILE *stream, char const *format, locale_t locale, ...),(stream,format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_fprintf_s_l,libc__fprintf_s_l,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 4),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(FILE *stream, char const *format, locale_t locale, ...),(stream,format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_fprintf_p,libd__fprintf_p,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF_P(2, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(FILE *stream, char const *format, ...),(stream,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_fprintf_p,libc__fprintf_p,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF_P(2, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(FILE *stream, char const *format, ...),(stream,format,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_fprintf_p_l,libd__fprintf_p_l,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF_P(2, 4),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(FILE *stream, char const *format, locale_t locale, ...),(stream,format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_fprintf_p_l,libc__fprintf_p_l,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF_P(2, 4),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(FILE *stream, char const *format, locale_t locale, ...),(stream,format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_printf_l,libd__printf_l,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char const *format, locale_t locale, ...),(format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_printf_l,libc__printf_l,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(char const *format, locale_t locale, ...),(format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_printf_s_l,libd__printf_s_l,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char const *format, locale_t locale, ...),(format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_printf_s_l,libc__printf_s_l,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(char const *format, locale_t locale, ...),(format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_printf_p,libd__printf_p,ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char const *format, ...),(format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_printf_p,libc__printf_p,ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(char const *format, ...),(format,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_printf_p_l,libd__printf_p_l,ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char const *format, locale_t locale, ...),(format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_printf_p_l,libc__printf_p_l,ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(char const *format, locale_t locale, ...),(format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_sprintf_l,libd__sprintf_l,ATTR_IN(2) ATTR_LIBC_PRINTF(2, 4) ATTR_OUT(1),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char *buf, char const *format, locale_t locale, ...),(buf,format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_sprintf_l,libc__sprintf_l,ATTR_IN(2) ATTR_LIBC_PRINTF(2, 4) ATTR_OUT(1),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char *buf, char const *format, locale_t locale, ...),(buf,format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_sprintf_s_l,libd__sprintf_s_l,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 5) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char *buf, size_t bufsize, char const *format, locale_t locale, ...),(buf,bufsize,format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_sprintf_s_l,libc__sprintf_s_l,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 5) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char *buf, size_t bufsize, char const *format, locale_t locale, ...),(buf,bufsize,format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_sprintf_p_l,libd__sprintf_p_l,ATTR_IN(3) ATTR_LIBC_PRINTF_P(3, 5) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char *buf, size_t bufsize, char const *format, locale_t locale, ...),(buf,bufsize,format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_sprintf_p_l,libc__sprintf_p_l,ATTR_IN(3) ATTR_LIBC_PRINTF_P(3, 5) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char *buf, size_t bufsize, char const *format, locale_t locale, ...),(buf,bufsize,format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_sprintf_p,libd__sprintf_p,ATTR_IN(3) ATTR_LIBC_PRINTF_P(3, 4) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char *buf, size_t bufsize, char const *format, ...),(buf,bufsize,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_sprintf_p,libc__sprintf_p,ATTR_IN(3) ATTR_LIBC_PRINTF_P(3, 4) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char *buf, size_t bufsize, char const *format, ...),(buf,bufsize,format,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_snprintf_l,libd__snprintf_l,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 5) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char *buf, size_t bufsize, char const *format, locale_t locale, ...),(buf,bufsize,format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_snprintf_l,libc__snprintf_l,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 5) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char *buf, size_t bufsize, char const *format, locale_t locale, ...),(buf,bufsize,format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_snprintf,libd__snprintf,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char *buf, size_t bufsize, char const *format, ...),(buf,bufsize,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_snprintf,libc__snprintf,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char *buf, size_t bufsize, char const *format, ...),(buf,bufsize,format,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_snprintf_c_l,libd__snprintf_c_l,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 5) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char *buf, size_t bufsize, char const *format, locale_t locale, ...),(buf,bufsize,format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_snprintf_c_l,libc__snprintf_c_l,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 5) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char *buf, size_t bufsize, char const *format, locale_t locale, ...),(buf,bufsize,format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_snprintf_c,libd__snprintf_c,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char *buf, size_t bufsize, char const *format, ...),(buf,bufsize,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_snprintf_c,libc__snprintf_c,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char *buf, size_t bufsize, char const *format, ...),(buf,bufsize,format,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_snprintf_s_l,libd__snprintf_s_l,ATTR_IN(4) ATTR_LIBC_PRINTF(4, 6) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char *buf, size_t bufsize, size_t maxsize, char const *format, locale_t locale, ...),(buf,bufsize,maxsize,format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_snprintf_s_l,libc__snprintf_s_l,ATTR_IN(4) ATTR_LIBC_PRINTF(4, 6) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char *buf, size_t bufsize, size_t maxsize, char const *format, locale_t locale, ...),(buf,bufsize,maxsize,format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_snprintf_s,libd__snprintf_s,ATTR_IN(4) ATTR_LIBC_PRINTF(4, 5) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char *buf, size_t bufsize, size_t maxsize, char const *format, ...),(buf,bufsize,maxsize,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_snprintf_s,libc__snprintf_s,ATTR_IN(4) ATTR_LIBC_PRINTF(4, 5) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char *buf, size_t bufsize, size_t maxsize, char const *format, ...),(buf,bufsize,maxsize,format,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_scprintf_l,libd__scprintf_l,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char const *format, locale_t locale, ...),(format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_scprintf_l,libc__scprintf_l,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char const *format, locale_t locale, ...),(format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_scprintf,libd__scprintf,WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char const *format, ...),(format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_scprintf,libc__scprintf,WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char const *format, ...),(format,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_scprintf_p_l,libd__scprintf_p_l,ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char const *format, locale_t locale, ...),(format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_scprintf_p_l,libc__scprintf_p_l,ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char const *format, locale_t locale, ...),(format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_scprintf_p,libd__scprintf_p,WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char const *format, ...),(format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_scprintf_p,libc__scprintf_p,WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char const *format, ...),(format,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_fscanf_l,libd__fscanf_l,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 4),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(FILE *stream, char const *format, locale_t locale, ...),(stream,format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_fscanf_l,libc__fscanf_l,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 4),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(FILE *stream, char const *format, locale_t locale, ...),(stream,format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_fscanf_s_l,libd__fscanf_s_l,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 4),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(FILE *stream, char const *format, locale_t locale, ...),(stream,format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_fscanf_s_l,libc__fscanf_s_l,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 4),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(FILE *stream, char const *format, locale_t locale, ...),(stream,format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_scanf_l,libd__scanf_l,WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char const *format, locale_t locale, ...),(format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_scanf_l,libc__scanf_l,WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(char const *format, locale_t locale, ...),(format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_scanf_s_l,libd__scanf_s_l,WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char const *format, locale_t locale, ...),(format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_scanf_s_l,libc__scanf_s_l,WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(char const *format, locale_t locale, ...),(format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_sscanf_l,libd__sscanf_l,WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 4),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char const *buf, char const *format, locale_t locale, ...),(buf,format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_sscanf_l,libc__sscanf_l,WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 4),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char const *buf, char const *format, locale_t locale, ...),(buf,format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_sscanf_s_l,libd__sscanf_s_l,WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 4),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char const *buf, char const *format, locale_t locale, ...),(buf,format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_sscanf_s_l,libc__sscanf_s_l,WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 4),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char const *buf, char const *format, locale_t locale, ...),(buf,format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_snscanf_l,libd__snscanf_l,WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 5),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char const *buf, size_t bufsize, char const *format, locale_t locale, ...),(buf,bufsize,format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_snscanf_l,libc__snscanf_l,WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 5),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char const *buf, size_t bufsize, char const *format, locale_t locale, ...),(buf,bufsize,format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_snscanf,libd__snscanf,WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 4),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char const *buf, size_t bufsize, char const *format, ...),(buf,bufsize,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_snscanf,libc__snscanf,WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 4),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char const *buf, size_t bufsize, char const *format, ...),(buf,bufsize,format,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_snscanf_s_l,libd__snscanf_s_l,WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 5),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char const *buf, size_t bufsize, char const *format, locale_t locale, ...),(buf,bufsize,format,locale,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_snscanf_s_l,libc__snscanf_s_l,WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 5),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char const *buf, size_t bufsize, char const *format, locale_t locale, ...),(buf,bufsize,format,locale,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$_snscanf_s,libd__snscanf_s,WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 4),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char const *buf, size_t bufsize, char const *format, ...),(buf,bufsize,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_snscanf_s,libc__snscanf_s,WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_SCANF(3, 4),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char const *buf, size_t bufsize, char const *format, ...),(buf,bufsize,format,));
DEFINE_PUBLIC_ALIAS_P(vfprintf_s,libc_vfprintf_s,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(FILE *stream, char const *format, va_list args),(stream,format,args));
DEFINE_PUBLIC_ALIAS_P(vprintf_s,libc_vprintf_s,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *format, va_list args),(format,args));
DEFINE_PUBLIC_ALIAS_P(vsprintf_s,libc_vsprintf_s,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 0) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char *buf, size_t bufsize, char const *format, va_list args),(buf,bufsize,format,args));
DEFINE_PUBLIC_ALIAS_P(vsnprintf_s,libc_vsnprintf_s,ATTR_IN(4) ATTR_LIBC_PRINTF(4, 0) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char *buf, size_t bufsize, size_t maxsize, char const *format, va_list args),(buf,bufsize,maxsize,format,args));
DEFINE_PUBLIC_ALIAS_P(vfscanf_s,libc_vfscanf_s,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(FILE *stream, char const *format, va_list args),(stream,format,args));
DEFINE_PUBLIC_ALIAS_P(vscanf_s,libc_vscanf_s,WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *format, va_list args),(format,args));
DEFINE_PUBLIC_ALIAS_P(vsscanf_s,libc_vsscanf_s,WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,LIBCCALL,(char const *buf, char const *format, va_list args),(buf,format,args));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$fprintf_s,libd_fprintf_s,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(FILE *stream, char const *format, ...),(stream,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(fprintf_s,libc_fprintf_s,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_PRINTF(2, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(FILE *stream, char const *format, ...),(stream,format,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$printf_s,libd_printf_s,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char const *format, ...),(format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(printf_s,libc_printf_s,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(char const *format, ...),(format,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$sprintf_s,libd_sprintf_s,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char *buf, size_t bufsize, char const *format, ...),(buf,bufsize,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(sprintf_s,libc_sprintf_s,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char *buf, size_t bufsize, char const *format, ...),(buf,bufsize,format,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$fscanf_s,libd_fscanf_s,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(FILE *stream, char const *format, ...),(stream,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(fscanf_s,libc_fscanf_s,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_SCANF(2, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(FILE *stream, char const *format, ...),(stream,format,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$scanf_s,libd_scanf_s,WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char const *format, ...),(format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(scanf_s,libc_scanf_s,WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 2),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,VLIBCCALL,(char const *format, ...),(format,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$sscanf_s,libd_sscanf_s,WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBDCALL,(char const *buf, char const *format, ...),(buf,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(sscanf_s,libc_sscanf_s,WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_SCANF(2, 3),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(char const *buf, char const *format, ...),(buf,format,));
DEFINE_PUBLIC_ALIAS_P(_doprnt,libc__doprnt,ATTR_IN(1) ATTR_INOUT(3) ATTR_LIBC_PRINTF(1, 0),__STDC_INT_AS_SSIZE_T,NOTHROW_CB_NCX,LIBCCALL,(char const *__restrict format, va_list args, FILE *__restrict stream),(format,args,stream));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_STDIO_C */
