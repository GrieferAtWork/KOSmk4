/* HASH CRC-32:0xb6855b5b */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_CORECRT_WSTDIO_C
#define GUARD_LIBC_AUTO_CORECRT_WSTDIO_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/corecrt_wstdio.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "../user/string.h"
#include "uchar.h"
#include "../user/wchar.h"

DECL_BEGIN

#include "../libc/globals.h"
#ifndef __KERNEL__
#include <libc/template/stdstreams.h>
#include <libc/errno.h>
#include <parts/printf-config.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.errno.utility") ATTR_COLD void
(LIBDCALL libd__wperror)(char16_t const *__restrict message) THROWS(...) {













	if (message) {

		libc_fprintf(stderr, "%I16s: %m\n", message);



	} else {
		libc_fprintf(stderr, "%m\n");
	}

}
#include <libc/template/stdstreams.h>
#include <libc/errno.h>
#include <parts/printf-config.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.errno.utility") ATTR_COLD void
(LIBKCALL libc__wperror)(char32_t const *__restrict message) THROWS(...) {













	if (message) {



		libc_fprintf(stderr, "%I32s: %m\n", message);

	} else {
		libc_fprintf(stderr, "%m\n");
	}

}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") WUNUSED NONNULL((1, 2)) FILE *
NOTHROW_NCX(LIBDCALL libd__wfsopen)(char16_t const *filename,
                                    char16_t const *mode,
                                    __STDC_INT_AS_UINT_T sh_flag) {
	FILE *result = NULL;
	char *utf8_filename;
	char *utf8_mode;
	utf8_filename = libd_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		goto done;
	utf8_mode = libd_convert_wcstombs(mode);
	if unlikely(!utf8_mode)
		goto done_filename;
	result = libd__fsopen(utf8_filename, utf8_mode, sh_flag);

	libc_free(utf8_mode);

done_filename:

	libc_free(utf8_filename);

done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") WUNUSED NONNULL((1, 2)) FILE *
NOTHROW_NCX(LIBKCALL libc__wfsopen)(char32_t const *filename,
                                    char32_t const *mode,
                                    __STDC_INT_AS_UINT_T sh_flag) {
	FILE *result = NULL;
	char *utf8_filename;
	char *utf8_mode;
	utf8_filename = libc_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		goto done;
	utf8_mode = libc_convert_wcstombs(mode);
	if unlikely(!utf8_mode)
		goto done_filename;
	result = libc__fsopen(utf8_filename, utf8_mode, sh_flag);

	libc_free(utf8_mode);

done_filename:

	libc_free(utf8_filename);

done:
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") WUNUSED NONNULL((2)) FILE *
NOTHROW_NCX(LIBDCALL libd__wfdopen)(fd_t fd,
                                    char16_t const *mode) {
	FILE *result = NULL;
	char *utf8_mode;
	utf8_mode = libd_convert_wcstombs(mode);
	if unlikely(!utf8_mode)
		goto done;
	result = libc_fdopen(fd, utf8_mode);

	libc_free(utf8_mode);

done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") WUNUSED NONNULL((2)) FILE *
NOTHROW_NCX(LIBKCALL libc__wfdopen)(fd_t fd,
                                    char32_t const *mode) {
	FILE *result = NULL;
	char *utf8_mode;
	utf8_mode = libc_convert_wcstombs(mode);
	if unlikely(!utf8_mode)
		goto done;
	result = libc_fdopen(fd, utf8_mode);

	libc_free(utf8_mode);

done:
	return result;
}
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") NONNULL((1, 2, 3)) errno_t
NOTHROW_NCX(LIBDCALL libd__wfopen_s)(FILE **pstream,
                                     char16_t const *filename,
                                     char16_t const *mode) {
	errno_t result;
	char *utf8_filename;
	char *utf8_mode;
	utf8_filename = libd_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		goto err_badalloc;
	utf8_mode = libd_convert_wcstombs(mode);
	if unlikely(!utf8_mode)
		goto err_badalloc_filename;
	result = libd_fopen_s(pstream, utf8_filename, utf8_mode);

	libc_free(utf8_mode);
	libc_free(utf8_filename);

	return result;
err_badalloc_filename:

	libc_free(utf8_filename);

err_badalloc:

	return __libc_geterrno_or(ENOMEM);



}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") NONNULL((1, 2, 3)) errno_t
NOTHROW_NCX(LIBKCALL libc__wfopen_s)(FILE **pstream,
                                     char32_t const *filename,
                                     char32_t const *mode) {
	errno_t result;
	char *utf8_filename;
	char *utf8_mode;
	utf8_filename = libc_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		goto err_badalloc;
	utf8_mode = libc_convert_wcstombs(mode);
	if unlikely(!utf8_mode)
		goto err_badalloc_filename;
	result = libc_fopen_s(pstream, utf8_filename, utf8_mode);

	libc_free(utf8_mode);
	libc_free(utf8_filename);

	return result;
err_badalloc_filename:

	libc_free(utf8_filename);

err_badalloc:

	return __libc_geterrno_or(ENOMEM);



}
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") NONNULL((1, 2, 3)) errno_t
NOTHROW_NCX(LIBDCALL libd__wfreopen_s)(FILE **pstream,
                                       char16_t const *filename,
                                       char16_t const *mode,
                                       FILE *stream) {
	errno_t result;
	char *utf8_filename;
	char *utf8_mode;
	utf8_filename = libd_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		goto err_badalloc;
	utf8_mode = libd_convert_wcstombs(mode);
	if unlikely(!utf8_mode)
		goto err_badalloc_filename;
	result = libd_freopen_s(pstream, utf8_filename, utf8_mode, stream);

	libc_free(utf8_mode);
	libc_free(utf8_filename);

	return result;
err_badalloc_filename:

	libc_free(utf8_filename);

err_badalloc:

	return __libc_geterrno_or(ENOMEM);



}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") NONNULL((1, 2, 3)) errno_t
NOTHROW_NCX(LIBKCALL libc__wfreopen_s)(FILE **pstream,
                                       char32_t const *filename,
                                       char32_t const *mode,
                                       FILE *stream) {
	errno_t result;
	char *utf8_filename;
	char *utf8_mode;
	utf8_filename = libc_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		goto err_badalloc;
	utf8_mode = libc_convert_wcstombs(mode);
	if unlikely(!utf8_mode)
		goto err_badalloc_filename;
	result = libc_freopen_s(pstream, utf8_filename, utf8_mode, stream);

	libc_free(utf8_mode);
	libc_free(utf8_filename);

	return result;
err_badalloc_filename:

	libc_free(utf8_filename);

err_badalloc:

	return __libc_geterrno_or(ENOMEM);



}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.read") char16_t *
NOTHROW_NCX(LIBDCALL libd__getws)(char16_t *buf) {
	return libd__getws_s(buf, (size_t)-1);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.read") char32_t *
NOTHROW_NCX(LIBKCALL libc__getws)(char32_t *buf) {
	return libc__getws_s(buf, (size_t)-1);
}
#include <libc/template/stdstreams.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.read") char16_t *
NOTHROW_NCX(LIBDCALL libd__getws_s)(char16_t *buf,
                                    size_t buflen) {
	return libd_fgetws(buf, buflen, stdin);
}
#include <libc/template/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.read") char32_t *
NOTHROW_NCX(LIBKCALL libc__getws_s)(char32_t *buf,
                                    size_t buflen) {
	return libc_fgetws(buf, buflen, stdin);
}
#include <libc/template/stdstreams.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.write") NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd__putws)(char16_t const *str) {
	return libd_fputws(str, stdout);
}
#include <libc/template/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.write") NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBKCALL libc__putws)(char32_t const *str) {
	return libc_fputws(str, stdout);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(3, 0) NONNULL((2, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd___stdio_common_vfwprintf)(uint64_t options,
                                                    FILE *stream,
                                                    char16_t const *format,
                                                    locale_t locale,
                                                    va_list args) {
	(void)locale;
	(void)options;
	return libd_vfwprintf(stream, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(3, 0) NONNULL((2, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc___stdio_common_vfwprintf)(uint64_t options,
                                                    FILE *stream,
                                                    char32_t const *format,
                                                    locale_t locale,
                                                    va_list args) {
	(void)locale;
	(void)options;
	return libc_vfwprintf(stream, format, args);
}
DEFINE_INTERN_ALIAS(libd___stdio_common_vfwprintf_s, libd___stdio_common_vfwprintf);
DEFINE_INTERN_ALIAS(libc___stdio_common_vfwprintf_s, libc___stdio_common_vfwprintf);
DEFINE_INTERN_ALIAS(libd___stdio_common_vfwprintf_p, libd___stdio_common_vfwprintf);
DEFINE_INTERN_ALIAS(libc___stdio_common_vfwprintf_p, libc___stdio_common_vfwprintf);
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(4, 0) NONNULL((4)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd___stdio_common_vswprintf)(uint64_t options,
                                                    char16_t *buf,
                                                    size_t bufsize,
                                                    char16_t const *format,
                                                    locale_t locale,
                                                    va_list args) {
	__STDC_INT_AS_SSIZE_T result;
	(void)locale;
	result = libd_vswprintf(buf, bufsize, format, args);
	if (!(options & 2) && (size_t)result > bufsize)
		result = bufsize;
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(4, 0) NONNULL((4)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc___stdio_common_vswprintf)(uint64_t options,
                                                    char32_t *buf,
                                                    size_t bufsize,
                                                    char32_t const *format,
                                                    locale_t locale,
                                                    va_list args) {
	__STDC_INT_AS_SSIZE_T result;
	(void)locale;
	result = libc_vswprintf(buf, bufsize, format, args);
	if (!(options & 2) && (size_t)result > bufsize)
		result = bufsize;
	return result;
}
DEFINE_INTERN_ALIAS(libd___stdio_common_vswprintf_s, libd___stdio_common_vswprintf);
DEFINE_INTERN_ALIAS(libc___stdio_common_vswprintf_s, libc___stdio_common_vswprintf);
#include <hybrid/__assert.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(5, 0) NONNULL((5)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd___stdio_common_vsnwprintf_s)(uint64_t options,
                                                       char16_t *buf,
                                                       size_t bufsize,
                                                       size_t maxsize,
                                                       char16_t const *format,
                                                       locale_t locale,
                                                       va_list args) {
	__hybrid_assert(bufsize <= maxsize);
	return libd___stdio_common_vswprintf(options, buf, bufsize, format, locale, args);
}
#include <hybrid/__assert.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(5, 0) NONNULL((5)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc___stdio_common_vsnwprintf_s)(uint64_t options,
                                                       char32_t *buf,
                                                       size_t bufsize,
                                                       size_t maxsize,
                                                       char32_t const *format,
                                                       locale_t locale,
                                                       va_list args) {
	__hybrid_assert(bufsize <= maxsize);
	return libc___stdio_common_vswprintf(options, buf, bufsize, format, locale, args);
}
DEFINE_INTERN_ALIAS(libd___stdio_common_vswprintf_p, libd___stdio_common_vswprintf);
DEFINE_INTERN_ALIAS(libc___stdio_common_vswprintf_p, libc___stdio_common_vswprintf);
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") ATTR_LIBC_C16SCANF(3, 0) NONNULL((2, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd___stdio_common_vfwscanf)(uint64_t options,
                                                   FILE *stream,
                                                   char16_t const *format,
                                                   locale_t locale,
                                                   va_list args) {
	(void)options;
	(void)locale;
	return libd_vfwscanf(stream, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") ATTR_LIBC_C32SCANF(3, 0) NONNULL((2, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc___stdio_common_vfwscanf)(uint64_t options,
                                                   FILE *stream,
                                                   char32_t const *format,
                                                   locale_t locale,
                                                   va_list args) {
	(void)options;
	(void)locale;
	return libc_vfwscanf(stream, format, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") ATTR_LIBC_C16SCANF(4, 0) NONNULL((4)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd___stdio_common_vswscanf)(uint64_t options,
                                                   char16_t const *buf,
                                                   size_t bufsize,
                                                   char16_t const *format,
                                                   locale_t locale,
                                                   va_list args) {
	/* TODO: format_wscanf() */
	(void)options;
	(void)buf;
	(void)bufsize;
	(void)format;
	(void)locale;
	(void)args;
	COMPILER_IMPURE();
	return -1;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") ATTR_LIBC_C32SCANF(4, 0) NONNULL((4)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc___stdio_common_vswscanf)(uint64_t options,
                                                   char32_t const *buf,
                                                   size_t bufsize,
                                                   char32_t const *format,
                                                   locale_t locale,
                                                   va_list args) {
	/* TODO: format_wscanf() */
	(void)options;
	(void)buf;
	(void)bufsize;
	(void)format;
	(void)locale;
	(void)args;
	COMPILER_IMPURE();
	return -1;
}
#include <corecrt_stdio_config.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vsnwprintf_l)(char16_t *buf,
                                         size_t bufsize,
                                         char16_t const *format,
                                         locale_t locale,
                                         va_list args) {
	int result = libd___stdio_common_vswprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS | 1, buf, bufsize, format, locale, args);
	return result < 0 ? -1 : result;
}
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vsnwprintf_l)(char32_t *buf,
                                         size_t bufsize,
                                         char32_t const *format,
                                         locale_t locale,
                                         va_list args) {
	int result = libc___stdio_common_vswprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS | 1, buf, bufsize, format, locale, args);
	return result < 0 ? -1 : result;
}
#include <corecrt_stdio_config.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vswprintf_s_l)(char16_t *buf,
                                          size_t bufsize,
                                          char16_t const *format,
                                          locale_t locale,
                                          va_list args) {
	int result = libd___stdio_common_vswprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, buf, bufsize, format, locale, args);
	return result < 0 ? -1 : result;
}
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vswprintf_s_l)(char32_t *buf,
                                          size_t bufsize,
                                          char32_t const *format,
                                          locale_t locale,
                                          va_list args) {
	int result = libc___stdio_common_vswprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, buf, bufsize, format, locale, args);
	return result < 0 ? -1 : result;
}
DEFINE_INTERN_ALIAS(libd__vswprintf_p_l, libd__vswprintf_c_l);
DEFINE_INTERN_ALIAS(libc__vswprintf_p_l, libc__vswprintf_c_l);
#include <corecrt_stdio_config.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vscwprintf_l)(char16_t const *format,
                                         locale_t locale,
                                         va_list args) {
	int result = libd___stdio_common_vswprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS | 2, NULL, 0, format, locale, args);
	return result < 0 ? -1 : result;
}
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vscwprintf_l)(char32_t const *format,
                                         locale_t locale,
                                         va_list args) {
	int result = libc___stdio_common_vswprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS | 2, NULL, 0, format, locale, args);
	return result < 0 ? -1 : result;
}
DEFINE_INTERN_ALIAS(libd__vscwprintf_p_l, libd__vscwprintf_l);
DEFINE_INTERN_ALIAS(libc__vscwprintf_p_l, libc__vscwprintf_l);
#include <corecrt_stdio_config.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vswprintf_c_l)(char16_t *buf,
                                          size_t bufsize,
                                          char16_t const *format,
                                          locale_t locale,
                                          va_list args) {
	int result = libd___stdio_common_vswprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, buf, bufsize, format, locale, args);
	return result < 0 ? -1 : result;
}
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vswprintf_c_l)(char32_t *buf,
                                          size_t bufsize,
                                          char32_t const *format,
                                          locale_t locale,
                                          va_list args) {
	int result = libc___stdio_common_vswprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, buf, bufsize, format, locale, args);
	return result < 0 ? -1 : result;
}
#include <corecrt_stdio_config.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(4, 0) NONNULL((4)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vsnwprintf_s_l)(char16_t *buf,
                                           size_t bufsize,
                                           size_t maxsize,
                                           char16_t const *format,
                                           locale_t locale,
                                           va_list args) {
	int result = libd___stdio_common_vsnwprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, buf, bufsize, maxsize, format, locale, args);
	return result < 0 ? -1 : result;
}
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(4, 0) NONNULL((4)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vsnwprintf_s_l)(char32_t *buf,
                                           size_t bufsize,
                                           size_t maxsize,
                                           char32_t const *format,
                                           locale_t locale,
                                           va_list args) {
	int result = libc___stdio_common_vsnwprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, buf, bufsize, maxsize, format, locale, args);
	return result < 0 ? -1 : result;
}
#include <corecrt_stdio_config.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vfwprintf_s_l)(FILE *stream,
                                          char16_t const *format,
                                          locale_t locale,
                                          va_list args) {
	return libd___stdio_common_vfwprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, stream, format, locale, args);
}
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vfwprintf_s_l)(FILE *stream,
                                          char32_t const *format,
                                          locale_t locale,
                                          va_list args) {
	return libc___stdio_common_vfwprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, stream, format, locale, args);
}
DEFINE_INTERN_ALIAS(libd__vfwprintf_p_l, libd__vfwprintf_l);
DEFINE_INTERN_ALIAS(libc__vfwprintf_p_l, libc__vfwprintf_l);
#include <corecrt_stdio_config.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vfwscanf_l)(FILE *stream,
                                       char16_t const *format,
                                       locale_t locale,
                                       va_list args) {
	return libd___stdio_common_vfwscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS, stream, format, locale, args);
}
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vfwscanf_l)(FILE *stream,
                                       char32_t const *format,
                                       locale_t locale,
                                       va_list args) {
	return libc___stdio_common_vfwscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS, stream, format, locale, args);
}
#include <corecrt_stdio_config.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vfwscanf_s_l)(FILE *stream,
                                         char16_t const *format,
                                         locale_t locale,
                                         va_list args) {
	return libd___stdio_common_vfwscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS | 1, stream, format, locale, args);
}
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vfwscanf_s_l)(FILE *stream,
                                         char32_t const *format,
                                         locale_t locale,
                                         va_list args) {
	return libc___stdio_common_vfwscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS | 1, stream, format, locale, args);
}
#include <corecrt_stdio_config.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(3, 0) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vsnwscanf_l)(char16_t const *buf,
                                        size_t bufsize,
                                        char16_t const *format,
                                        locale_t locale,
                                        va_list args) {
	return libd___stdio_common_vswscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS, buf, bufsize, format, locale, args);
}
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(3, 0) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vsnwscanf_l)(char32_t const *buf,
                                        size_t bufsize,
                                        char32_t const *format,
                                        locale_t locale,
                                        va_list args) {
	return libc___stdio_common_vswscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS, buf, bufsize, format, locale, args);
}
#include <corecrt_stdio_config.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(3, 0) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vsnwscanf_s_l)(char16_t const *buf,
                                          size_t bufsize,
                                          char16_t const *format,
                                          locale_t locale,
                                          va_list args) {
	return libd___stdio_common_vswscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS | 1, buf, bufsize, format, locale, args);
}
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(3, 0) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vsnwscanf_s_l)(char32_t const *buf,
                                          size_t bufsize,
                                          char32_t const *format,
                                          locale_t locale,
                                          va_list args) {
	return libc___stdio_common_vswscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS | 1, buf, bufsize, format, locale, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vwprintf_l)(char16_t const *format,
                                       locale_t locale,
                                       va_list args) {
	(void)locale;
	return libd_vwprintf(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vwprintf_l)(char32_t const *format,
                                       locale_t locale,
                                       va_list args) {
	(void)locale;
	return libc_vwprintf(format, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vfwprintf_l)(FILE *stream,
                                        char16_t const *format,
                                        locale_t locale,
                                        va_list args) {
	(void)locale;
	return libd_vfwprintf(stream, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vfwprintf_l)(FILE *stream,
                                        char32_t const *format,
                                        locale_t locale,
                                        va_list args) {
	(void)locale;
	return libc_vfwprintf(stream, format, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd___vswprintf_l)(char16_t *buf,
                                         char16_t const *format,
                                         locale_t locale,
                                         va_list args) {
	(void)locale;
	return libd_vswprintf(buf, (size_t)-1, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc___vswprintf_l)(char32_t *buf,
                                         char32_t const *format,
                                         locale_t locale,
                                         va_list args) {
	(void)locale;
	return libc_vswprintf(buf, (size_t)-1, format, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vwscanf_l)(char16_t const *format,
                                      locale_t locale,
                                      va_list args) {
	(void)locale;
	return libd_vwscanf(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vwscanf_l)(char32_t const *format,
                                      locale_t locale,
                                      va_list args) {
	(void)locale;
	return libc_vwscanf(format, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C16PRINTF(4, 0) NONNULL((4)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vsnwprintf_s)(char16_t *buf,
                                         size_t bufsize,
                                         size_t maxsize,
                                         char16_t const *format,
                                         va_list args) {
	return libd__vsnwprintf_s_l(buf, bufsize, maxsize, format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C32PRINTF(4, 0) NONNULL((4)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vsnwprintf_s)(char32_t *buf,
                                         size_t bufsize,
                                         size_t maxsize,
                                         char32_t const *format,
                                         va_list args) {
	return libc__vsnwprintf_s_l(buf, bufsize, maxsize, format, NULL, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C16PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vsnwprintf)(char16_t *buf,
                                       size_t bufsize,
                                       char16_t const *format,
                                       va_list args) {
	return libd__vsnwprintf_l(buf, bufsize, format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C32PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vsnwprintf)(char32_t *buf,
                                       size_t bufsize,
                                       char32_t const *format,
                                       va_list args) {
	return libc__vsnwprintf_l(buf, bufsize, format, NULL, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C16PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vswprintf_c)(char16_t *buf,
                                        size_t bufsize,
                                        char16_t const *format,
                                        va_list args) {
	return libd__vswprintf_c_l(buf, bufsize, format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C32PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vswprintf_c)(char32_t *buf,
                                        size_t bufsize,
                                        char32_t const *format,
                                        va_list args) {
	return libc__vswprintf_c_l(buf, bufsize, format, NULL, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C16PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vswprintf)(char16_t *buf,
                                      char16_t const *format,
                                      va_list args) {
	return libd__vswprintf_c_l(buf, (size_t)-1, format, NULL, args); /* _vswprintf_l */
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C32PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vswprintf)(char32_t *buf,
                                      char32_t const *format,
                                      va_list args) {
	return libc__vswprintf_c_l(buf, (size_t)-1, format, NULL, args); /* _vswprintf_l */
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C16PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vscwprintf)(char16_t const *format,
                                       va_list args) {
	return libd__vscwprintf_l(format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C32PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vscwprintf)(char32_t const *format,
                                       va_list args) {
	return libc__vscwprintf_l(format, NULL, args);
}
DEFINE_INTERN_ALIAS(libd__vscwprintf_p, libd__vscwprintf);
DEFINE_INTERN_ALIAS(libc__vscwprintf_p, libc__vscwprintf);
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") ATTR_LIBC_C16SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vswscanf_l)(char16_t const *buf,
                                       char16_t const *format,
                                       locale_t locale,
                                       va_list args) {
	return libd__vsnwscanf_l(buf, (size_t)-1, format, locale, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") ATTR_LIBC_C32SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vswscanf_l)(char32_t const *buf,
                                       char32_t const *format,
                                       locale_t locale,
                                       va_list args) {
	return libc__vsnwscanf_l(buf, (size_t)-1, format, locale, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") ATTR_LIBC_C16SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vswscanf_s_l)(char16_t const *buf,
                                         char16_t const *format,
                                         locale_t locale,
                                         va_list args) {
	return libd__vsnwscanf_s_l(buf, (size_t)-1, format, locale, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") ATTR_LIBC_C32SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vswscanf_s_l)(char32_t const *buf,
                                         char32_t const *format,
                                         locale_t locale,
                                         va_list args) {
	return libc__vsnwscanf_s_l(buf, (size_t)-1, format, locale, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") ATTR_LIBC_C16SCANF(3, 0) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vsnwscanf)(char16_t const *buf,
                                      size_t bufsize,
                                      char16_t const *format,
                                      va_list args) {
	return libd__vsnwscanf_l(buf, bufsize, format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") ATTR_LIBC_C32SCANF(3, 0) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vsnwscanf)(char32_t const *buf,
                                      size_t bufsize,
                                      char32_t const *format,
                                      va_list args) {
	return libc__vsnwscanf_l(buf, bufsize, format, NULL, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") ATTR_LIBC_C16SCANF(3, 0) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vsnwscanf_s)(char16_t const *buf,
                                        size_t bufsize,
                                        char16_t const *format,
                                        va_list args) {
	return libd__vsnwscanf_s_l(buf, bufsize, format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") ATTR_LIBC_C32SCANF(3, 0) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vsnwscanf_s)(char32_t const *buf,
                                        size_t bufsize,
                                        char32_t const *format,
                                        va_list args) {
	return libc__vsnwscanf_s_l(buf, bufsize, format, NULL, args);
}
#include <libc/template/stdstreams.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vwprintf_s_l)(char16_t const *format,
                                         locale_t locale,
                                         va_list args) {
	return libd__vfwprintf_s_l(stdout, format, locale, args);
}
#include <libc/template/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vwprintf_s_l)(char32_t const *format,
                                         locale_t locale,
                                         va_list args) {
	return libc__vfwprintf_s_l(stdout, format, locale, args);
}
DEFINE_INTERN_ALIAS(libd__vwprintf_p_l, libd__vwprintf_l);
DEFINE_INTERN_ALIAS(libc__vwprintf_p_l, libc__vwprintf_l);
#include <libc/template/stdstreams.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") ATTR_LIBC_C16SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vwscanf_s_l)(char16_t const *format,
                                        locale_t locale,
                                        va_list args) {
	return libd__vfwscanf_s_l(stdin, format, locale, args);
}
#include <libc/template/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") ATTR_LIBC_C32SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vwscanf_s_l)(char32_t const *format,
                                        locale_t locale,
                                        va_list args) {
	return libc__vfwscanf_s_l(stdin, format, locale, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__fwprintf_l)(FILE *stream,
                                        char16_t const *format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vfwprintf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__fwprintf_l)(FILE *stream,
                                        char32_t const *format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfwprintf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__fwprintf_s_l)(FILE *stream,
                                          char16_t const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vfwprintf_s_l(stream, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__fwprintf_s_l)(FILE *stream,
                                          char32_t const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfwprintf_s_l(stream, format, locale, args);
	va_end(args);
	return result;
}
DEFINE_INTERN_ALIAS(libd__fwprintf_p_l, libd__fwprintf_l);
DEFINE_INTERN_ALIAS(libc__fwprintf_p_l, libc__fwprintf_l);
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__wprintf_l)(char16_t const *format,
                                       locale_t locale,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vwprintf_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__wprintf_l)(char32_t const *format,
                                       locale_t locale,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vwprintf_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__wprintf_s_l)(char16_t const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vwprintf_s_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__wprintf_s_l)(char32_t const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vwprintf_s_l(format, locale, args);
	va_end(args);
	return result;
}
DEFINE_INTERN_ALIAS(libd__wprintf_p_l, libd__wprintf_l);
DEFINE_INTERN_ALIAS(libc__wprintf_p_l, libc__wprintf_l);
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd___swprintf_l)(char16_t *buf,
                                         char16_t const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd___vswprintf_l(buf, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc___swprintf_l)(char32_t *buf,
                                         char32_t const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc___vswprintf_l(buf, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C16PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__swprintf)(char16_t *buf,
                                      char16_t const *format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd__vswprintf(buf, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C32PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__swprintf)(char32_t *buf,
                                      char32_t const *format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vswprintf(buf, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__swprintf_s_l)(char16_t *buf,
                                          size_t bufsize,
                                          char16_t const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vswprintf_s_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__swprintf_s_l)(char32_t *buf,
                                          size_t bufsize,
                                          char32_t const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vswprintf_s_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
DEFINE_INTERN_ALIAS(libd__swprintf_p_l, libd__swprintf_c_l);
DEFINE_INTERN_ALIAS(libc__swprintf_p_l, libc__swprintf_c_l);
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__swprintf_c_l)(char16_t *buf,
                                          size_t bufsize,
                                          char16_t const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vswprintf_c_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__swprintf_c_l)(char32_t *buf,
                                          size_t bufsize,
                                          char32_t const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vswprintf_c_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snwprintf_l)(char16_t *buf,
                                         size_t bufsize,
                                         char16_t const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vsnwprintf_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__snwprintf_l)(char32_t *buf,
                                         size_t bufsize,
                                         char32_t const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnwprintf_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(4, 6) NONNULL((4)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snwprintf_s_l)(char16_t *buf,
                                           size_t bufsize,
                                           size_t maxsize,
                                           char16_t const *format,
                                           locale_t locale,
                                           ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vsnwprintf_s_l(buf, bufsize, maxsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(4, 6) NONNULL((4)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__snwprintf_s_l)(char32_t *buf,
                                           size_t bufsize,
                                           size_t maxsize,
                                           char32_t const *format,
                                           locale_t locale,
                                           ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnwprintf_s_l(buf, bufsize, maxsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C16PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__swprintf_c)(char16_t *buf,
                                        size_t bufsize,
                                        char16_t const *format,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd__vswprintf_c(buf, bufsize, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C32PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__swprintf_c)(char32_t *buf,
                                        size_t bufsize,
                                        char32_t const *format,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vswprintf_c(buf, bufsize, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C16PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snwprintf)(char16_t *buf,
                                       size_t bufsize,
                                       char16_t const *format,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd__vsnwprintf(buf, bufsize, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C32PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__snwprintf)(char32_t *buf,
                                       size_t bufsize,
                                       char32_t const *format,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnwprintf(buf, bufsize, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C16PRINTF(4, 5) NONNULL((4)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snwprintf_s)(char16_t *buf,
                                         size_t bufsize,
                                         size_t maxsize,
                                         char16_t const *format,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd__vsnwprintf_s(buf, bufsize, maxsize, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C32PRINTF(4, 5) NONNULL((4)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__snwprintf_s)(char32_t *buf,
                                         size_t bufsize,
                                         size_t maxsize,
                                         char32_t const *format,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnwprintf_s(buf, bufsize, maxsize, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C16PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__scwprintf_l)(char16_t const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vscwprintf_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.printf") ATTR_LIBC_C32PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__scwprintf_l)(char32_t const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vscwprintf_l(format, locale, args);
	va_end(args);
	return result;
}
DEFINE_INTERN_ALIAS(libd__scwprintf_p_l, libd__scwprintf_l);
DEFINE_INTERN_ALIAS(libc__scwprintf_p_l, libc__scwprintf_l);
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C16PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__scwprintf)(char16_t const *format,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd__vscwprintf(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C32PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__scwprintf)(char32_t const *format,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vscwprintf(format, args);
	va_end(args);
	return result;
}
DEFINE_INTERN_ALIAS(libd__scwprintf_p, libd__scwprintf);
DEFINE_INTERN_ALIAS(libc__scwprintf_p, libc__scwprintf);
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__fwscanf_l)(FILE *stream,
                                       char16_t const *format,
                                       locale_t locale,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vfwscanf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__fwscanf_l)(FILE *stream,
                                       char32_t const *format,
                                       locale_t locale,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfwscanf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__fwscanf_s_l)(FILE *stream,
                                         char16_t const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vfwscanf_s_l(stream, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__fwscanf_s_l)(FILE *stream,
                                         char32_t const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfwscanf_s_l(stream, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__wscanf_l)(char16_t const *format,
                                      locale_t locale,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vwscanf_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__wscanf_l)(char32_t const *format,
                                      locale_t locale,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vwscanf_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__wscanf_s_l)(char16_t const *format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vwscanf_s_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__wscanf_s_l)(char32_t const *format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vwscanf_s_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__swscanf_l)(char16_t const *buf,
                                       char16_t const *format,
                                       locale_t locale,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vswscanf_l(buf, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__swscanf_l)(char32_t const *buf,
                                       char32_t const *format,
                                       locale_t locale,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vswscanf_l(buf, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__swscanf_s_l)(char16_t const *buf,
                                         char16_t const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vswscanf_s_l(buf, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__swscanf_s_l)(char32_t const *buf,
                                         char32_t const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vswscanf_s_l(buf, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(3, 5) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snwscanf_l)(char16_t const *buf,
                                        size_t bufsize,
                                        char16_t const *format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vsnwscanf_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(3, 5) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__snwscanf_l)(char32_t const *buf,
                                        size_t bufsize,
                                        char32_t const *format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnwscanf_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(3, 4) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snwscanf)(char16_t const *buf,
                                      size_t bufsize,
                                      char16_t const *format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd__vsnwscanf(buf, bufsize, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(3, 4) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__snwscanf)(char32_t const *buf,
                                      size_t bufsize,
                                      char32_t const *format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnwscanf(buf, bufsize, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(3, 5) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snwscanf_s_l)(char16_t const *buf,
                                          size_t bufsize,
                                          char16_t const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vsnwscanf_s_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(3, 5) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__snwscanf_s_l)(char32_t const *buf,
                                          size_t bufsize,
                                          char32_t const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnwscanf_s_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(3, 4) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snwscanf_s)(char16_t const *buf,
                                        size_t bufsize,
                                        char16_t const *format,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd__vsnwscanf_s(buf, bufsize, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(3, 4) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__snwscanf_s)(char32_t const *buf,
                                        size_t bufsize,
                                        char32_t const *format,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnwscanf_s(buf, bufsize, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C16PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd_vfwprintf_s)(FILE *stream,
                                       char16_t const *format,
                                       va_list args) {
	return libd__vfwprintf_s_l(stream, format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C32PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc_vfwprintf_s)(FILE *stream,
                                       char32_t const *format,
                                       va_list args) {
	return libc__vfwprintf_s_l(stream, format, NULL, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C16PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd_vwprintf_s)(char16_t const *format,
                                      va_list args) {
	return libd__vfwprintf_s_l(stdout, format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C32PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc_vwprintf_s)(char32_t const *format,
                                      va_list args) {
	return libc__vfwprintf_s_l(stdout, format, NULL, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C16PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd_vswprintf_s)(char16_t *buf,
                                       size_t bufsize,
                                       char16_t const *format,
                                       va_list args) {
	return libd__vswprintf_s_l(buf, bufsize, format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C32PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc_vswprintf_s)(char32_t *buf,
                                       size_t bufsize,
                                       char32_t const *format,
                                       va_list args) {
	return libc__vswprintf_s_l(buf, bufsize, format, NULL, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd_vfwscanf_s)(FILE *stream,
                                      char16_t const *format,
                                      va_list args) {
	return libd__vfwscanf_s_l(stream, format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc_vfwscanf_s)(FILE *stream,
                                      char32_t const *format,
                                      va_list args) {
	return libc__vfwscanf_s_l(stream, format, NULL, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd_vwscanf_s)(char16_t const *format,
                                     va_list args) {
	return libd__vfwscanf_s_l(stdin, format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc_vwscanf_s)(char32_t const *format,
                                     va_list args) {
	return libc__vfwscanf_s_l(stdin, format, NULL, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd_vswscanf_s)(char16_t const *buf,
                                      char16_t const *format,
                                      va_list args) {
	return libd__vswscanf_s_l(buf, format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc_vswscanf_s)(char32_t const *buf,
                                      char32_t const *format,
                                      va_list args) {
	return libc__vswscanf_s_l(buf, format, NULL, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C16PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd_fwprintf_s)(FILE *stream,
                                       char16_t const *format,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vfwprintf_s(stream, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C32PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc_fwprintf_s)(FILE *stream,
                                       char32_t const *format,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfwprintf_s(stream, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C16PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd_wprintf_s)(char16_t const *format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vwprintf_s(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C32PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc_wprintf_s)(char32_t const *format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vwprintf_s(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C16PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd_swprintf_s)(char16_t *buf,
                                       size_t bufsize,
                                       char16_t const *format,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vswprintf_s(buf, bufsize, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C32PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc_swprintf_s)(char32_t *buf,
                                       size_t bufsize,
                                       char32_t const *format,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vswprintf_s(buf, bufsize, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd_fwscanf_s)(FILE *stream,
                                      char16_t const *format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vfwscanf_s(stream, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc_fwscanf_s)(FILE *stream,
                                      char32_t const *format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfwscanf_s(stream, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd_wscanf_s)(char16_t const *format,
                                     ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vwscanf_s(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc_wscanf_s)(char32_t const *format,
                                     ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vwscanf_s(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd_swscanf_s)(char16_t const *buf,
                                      char16_t const *format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vswscanf_s(buf, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc_swscanf_s)(char32_t const *buf,
                                      char32_t const *format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vswscanf_s(buf, format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$_wperror, libd__wperror);
DEFINE_PUBLIC_ALIAS(_wperror, libc__wperror);
DEFINE_PUBLIC_ALIAS(DOS$_wfsopen, libd__wfsopen);
DEFINE_PUBLIC_ALIAS(_wfsopen, libc__wfsopen);
DEFINE_PUBLIC_ALIAS(DOS$_wfdopen, libd__wfdopen);
DEFINE_PUBLIC_ALIAS(_wfdopen, libc__wfdopen);
DEFINE_PUBLIC_ALIAS(DOS$_wfopen_s, libd__wfopen_s);
DEFINE_PUBLIC_ALIAS(_wfopen_s, libc__wfopen_s);
DEFINE_PUBLIC_ALIAS(DOS$_wfreopen_s, libd__wfreopen_s);
DEFINE_PUBLIC_ALIAS(_wfreopen_s, libc__wfreopen_s);
DEFINE_PUBLIC_ALIAS(DOS$_getws, libd__getws);
DEFINE_PUBLIC_ALIAS(_getws, libc__getws);
DEFINE_PUBLIC_ALIAS(DOS$_getws_s, libd__getws_s);
DEFINE_PUBLIC_ALIAS(_getws_s, libc__getws_s);
DEFINE_PUBLIC_ALIAS(DOS$_putws, libd__putws);
DEFINE_PUBLIC_ALIAS(_putws, libc__putws);
DEFINE_PUBLIC_ALIAS(DOS$__stdio_common_vfwprintf, libd___stdio_common_vfwprintf);
DEFINE_PUBLIC_ALIAS(__stdio_common_vfwprintf, libc___stdio_common_vfwprintf);
DEFINE_PUBLIC_ALIAS(DOS$__stdio_common_vfwprintf_s, libd___stdio_common_vfwprintf_s);
DEFINE_PUBLIC_ALIAS(__stdio_common_vfwprintf_s, libc___stdio_common_vfwprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$__stdio_common_vfwprintf_p, libd___stdio_common_vfwprintf_p);
DEFINE_PUBLIC_ALIAS(__stdio_common_vfwprintf_p, libc___stdio_common_vfwprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$__stdio_common_vswprintf, libd___stdio_common_vswprintf);
DEFINE_PUBLIC_ALIAS(__stdio_common_vswprintf, libc___stdio_common_vswprintf);
DEFINE_PUBLIC_ALIAS(DOS$__stdio_common_vswprintf_s, libd___stdio_common_vswprintf_s);
DEFINE_PUBLIC_ALIAS(__stdio_common_vswprintf_s, libc___stdio_common_vswprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$__stdio_common_vsnwprintf_s, libd___stdio_common_vsnwprintf_s);
DEFINE_PUBLIC_ALIAS(__stdio_common_vsnwprintf_s, libc___stdio_common_vsnwprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$__stdio_common_vswprintf_p, libd___stdio_common_vswprintf_p);
DEFINE_PUBLIC_ALIAS(__stdio_common_vswprintf_p, libc___stdio_common_vswprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$__stdio_common_vfwscanf, libd___stdio_common_vfwscanf);
DEFINE_PUBLIC_ALIAS(__stdio_common_vfwscanf, libc___stdio_common_vfwscanf);
DEFINE_PUBLIC_ALIAS(DOS$__stdio_common_vswscanf, libd___stdio_common_vswscanf);
DEFINE_PUBLIC_ALIAS(__stdio_common_vswscanf, libc___stdio_common_vswscanf);
DEFINE_PUBLIC_ALIAS(DOS$_vsnwprintf_l, libd__vsnwprintf_l);
DEFINE_PUBLIC_ALIAS(_vsnwprintf_l, libc__vsnwprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vswprintf_s_l, libd__vswprintf_s_l);
DEFINE_PUBLIC_ALIAS(_vswprintf_s_l, libc__vswprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vswprintf_p_l, libd__vswprintf_p_l);
DEFINE_PUBLIC_ALIAS(_vswprintf_p_l, libc__vswprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_vscwprintf_l, libd__vscwprintf_l);
DEFINE_PUBLIC_ALIAS(_vscwprintf_l, libc__vscwprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vscwprintf_p_l, libd__vscwprintf_p_l);
DEFINE_PUBLIC_ALIAS(_vscwprintf_p_l, libc__vscwprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_vswprintf_l, libd__vswprintf_c_l);
DEFINE_PUBLIC_ALIAS(DOS$_vswprintf_c_l, libd__vswprintf_c_l);
DEFINE_PUBLIC_ALIAS(_vswprintf_l, libc__vswprintf_c_l);
DEFINE_PUBLIC_ALIAS(_vswprintf_c_l, libc__vswprintf_c_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsnwprintf_s_l, libd__vsnwprintf_s_l);
DEFINE_PUBLIC_ALIAS(_vsnwprintf_s_l, libc__vsnwprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vfwprintf_s_l, libd__vfwprintf_s_l);
DEFINE_PUBLIC_ALIAS(_vfwprintf_s_l, libc__vfwprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vfwprintf_p_l, libd__vfwprintf_p_l);
DEFINE_PUBLIC_ALIAS(_vfwprintf_p_l, libc__vfwprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_vfwscanf_l, libd__vfwscanf_l);
DEFINE_PUBLIC_ALIAS(_vfwscanf_l, libc__vfwscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vfwscanf_s_l, libd__vfwscanf_s_l);
DEFINE_PUBLIC_ALIAS(_vfwscanf_s_l, libc__vfwscanf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsnwscanf_l, libd__vsnwscanf_l);
DEFINE_PUBLIC_ALIAS(_vsnwscanf_l, libc__vsnwscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsnwscanf_s_l, libd__vsnwscanf_s_l);
DEFINE_PUBLIC_ALIAS(_vsnwscanf_s_l, libc__vsnwscanf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vwprintf_l, libd__vwprintf_l);
DEFINE_PUBLIC_ALIAS(_vwprintf_l, libc__vwprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vfwprintf_l, libd__vfwprintf_l);
DEFINE_PUBLIC_ALIAS(_vfwprintf_l, libc__vfwprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$__vswprintf_l, libd___vswprintf_l);
DEFINE_PUBLIC_ALIAS(__vswprintf_l, libc___vswprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vwscanf_l, libd__vwscanf_l);
DEFINE_PUBLIC_ALIAS(_vwscanf_l, libc__vwscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsnwprintf_s, libd__vsnwprintf_s);
DEFINE_PUBLIC_ALIAS(_vsnwprintf_s, libc__vsnwprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$_vsnwprintf, libd__vsnwprintf);
DEFINE_PUBLIC_ALIAS(_vsnwprintf, libc__vsnwprintf);
DEFINE_PUBLIC_ALIAS(DOS$_vswprintf_c, libd__vswprintf_c);
DEFINE_PUBLIC_ALIAS(_vswprintf_c, libc__vswprintf_c);
DEFINE_PUBLIC_ALIAS(DOS$_vswprintf, libd__vswprintf);
DEFINE_PUBLIC_ALIAS(_vswprintf, libc__vswprintf);
DEFINE_PUBLIC_ALIAS(DOS$_vscwprintf, libd__vscwprintf);
DEFINE_PUBLIC_ALIAS(_vscwprintf, libc__vscwprintf);
DEFINE_PUBLIC_ALIAS(DOS$_vscwprintf_p, libd__vscwprintf_p);
DEFINE_PUBLIC_ALIAS(_vscwprintf_p, libc__vscwprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_vswscanf_l, libd__vswscanf_l);
DEFINE_PUBLIC_ALIAS(_vswscanf_l, libc__vswscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vswscanf_s_l, libd__vswscanf_s_l);
DEFINE_PUBLIC_ALIAS(_vswscanf_s_l, libc__vswscanf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsnwscanf, libd__vsnwscanf);
DEFINE_PUBLIC_ALIAS(_vsnwscanf, libc__vsnwscanf);
DEFINE_PUBLIC_ALIAS(DOS$_vsnwscanf_s, libd__vsnwscanf_s);
DEFINE_PUBLIC_ALIAS(_vsnwscanf_s, libc__vsnwscanf_s);
DEFINE_PUBLIC_ALIAS(DOS$_vwprintf_s_l, libd__vwprintf_s_l);
DEFINE_PUBLIC_ALIAS(_vwprintf_s_l, libc__vwprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vwprintf_p_l, libd__vwprintf_p_l);
DEFINE_PUBLIC_ALIAS(_vwprintf_p_l, libc__vwprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_vwscanf_s_l, libd__vwscanf_s_l);
DEFINE_PUBLIC_ALIAS(_vwscanf_s_l, libc__vwscanf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_fwprintf_l, libd__fwprintf_l);
DEFINE_PUBLIC_ALIAS(_fwprintf_l, libc__fwprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_fwprintf_s_l, libd__fwprintf_s_l);
DEFINE_PUBLIC_ALIAS(_fwprintf_s_l, libc__fwprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_fwprintf_p_l, libd__fwprintf_p_l);
DEFINE_PUBLIC_ALIAS(_fwprintf_p_l, libc__fwprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_wprintf_l, libd__wprintf_l);
DEFINE_PUBLIC_ALIAS(_wprintf_l, libc__wprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_wprintf_s_l, libd__wprintf_s_l);
DEFINE_PUBLIC_ALIAS(_wprintf_s_l, libc__wprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_wprintf_p_l, libd__wprintf_p_l);
DEFINE_PUBLIC_ALIAS(_wprintf_p_l, libc__wprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$__swprintf_l, libd___swprintf_l);
DEFINE_PUBLIC_ALIAS(__swprintf_l, libc___swprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_swprintf, libd__swprintf);
DEFINE_PUBLIC_ALIAS(_swprintf, libc__swprintf);
DEFINE_PUBLIC_ALIAS(DOS$_swprintf_s_l, libd__swprintf_s_l);
DEFINE_PUBLIC_ALIAS(_swprintf_s_l, libc__swprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_swprintf_p_l, libd__swprintf_p_l);
DEFINE_PUBLIC_ALIAS(_swprintf_p_l, libc__swprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_swprintf_l, libd__swprintf_c_l);
DEFINE_PUBLIC_ALIAS(DOS$_swprintf_c_l, libd__swprintf_c_l);
DEFINE_PUBLIC_ALIAS(_swprintf_l, libc__swprintf_c_l);
DEFINE_PUBLIC_ALIAS(_swprintf_c_l, libc__swprintf_c_l);
DEFINE_PUBLIC_ALIAS(DOS$_snwprintf_l, libd__snwprintf_l);
DEFINE_PUBLIC_ALIAS(_snwprintf_l, libc__snwprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_snwprintf_s_l, libd__snwprintf_s_l);
DEFINE_PUBLIC_ALIAS(_snwprintf_s_l, libc__snwprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_swprintf_c, libd__swprintf_c);
DEFINE_PUBLIC_ALIAS(_swprintf_c, libc__swprintf_c);
DEFINE_PUBLIC_ALIAS(DOS$_snwprintf, libd__snwprintf);
DEFINE_PUBLIC_ALIAS(_snwprintf, libc__snwprintf);
DEFINE_PUBLIC_ALIAS(DOS$_snwprintf_s, libd__snwprintf_s);
DEFINE_PUBLIC_ALIAS(_snwprintf_s, libc__snwprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$_scwprintf_l, libd__scwprintf_l);
DEFINE_PUBLIC_ALIAS(_scwprintf_l, libc__scwprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_scwprintf_p_l, libd__scwprintf_p_l);
DEFINE_PUBLIC_ALIAS(_scwprintf_p_l, libc__scwprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_scwprintf, libd__scwprintf);
DEFINE_PUBLIC_ALIAS(_scwprintf, libc__scwprintf);
DEFINE_PUBLIC_ALIAS(DOS$_scwprintf_p, libd__scwprintf_p);
DEFINE_PUBLIC_ALIAS(_scwprintf_p, libc__scwprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_fwscanf_l, libd__fwscanf_l);
DEFINE_PUBLIC_ALIAS(_fwscanf_l, libc__fwscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_fwscanf_s_l, libd__fwscanf_s_l);
DEFINE_PUBLIC_ALIAS(_fwscanf_s_l, libc__fwscanf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_wscanf_l, libd__wscanf_l);
DEFINE_PUBLIC_ALIAS(_wscanf_l, libc__wscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_wscanf_s_l, libd__wscanf_s_l);
DEFINE_PUBLIC_ALIAS(_wscanf_s_l, libc__wscanf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_swscanf_l, libd__swscanf_l);
DEFINE_PUBLIC_ALIAS(_swscanf_l, libc__swscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_swscanf_s_l, libd__swscanf_s_l);
DEFINE_PUBLIC_ALIAS(_swscanf_s_l, libc__swscanf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_snwscanf_l, libd__snwscanf_l);
DEFINE_PUBLIC_ALIAS(_snwscanf_l, libc__snwscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_snwscanf, libd__snwscanf);
DEFINE_PUBLIC_ALIAS(_snwscanf, libc__snwscanf);
DEFINE_PUBLIC_ALIAS(DOS$_snwscanf_s_l, libd__snwscanf_s_l);
DEFINE_PUBLIC_ALIAS(_snwscanf_s_l, libc__snwscanf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_snwscanf_s, libd__snwscanf_s);
DEFINE_PUBLIC_ALIAS(_snwscanf_s, libc__snwscanf_s);
DEFINE_PUBLIC_ALIAS(DOS$vfwprintf_s, libd_vfwprintf_s);
DEFINE_PUBLIC_ALIAS(vfwprintf_s, libc_vfwprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$vwprintf_s, libd_vwprintf_s);
DEFINE_PUBLIC_ALIAS(vwprintf_s, libc_vwprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$vswprintf_s, libd_vswprintf_s);
DEFINE_PUBLIC_ALIAS(vswprintf_s, libc_vswprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$vfwscanf_s, libd_vfwscanf_s);
DEFINE_PUBLIC_ALIAS(vfwscanf_s, libc_vfwscanf_s);
DEFINE_PUBLIC_ALIAS(DOS$vwscanf_s, libd_vwscanf_s);
DEFINE_PUBLIC_ALIAS(vwscanf_s, libc_vwscanf_s);
DEFINE_PUBLIC_ALIAS(DOS$vswscanf_s, libd_vswscanf_s);
DEFINE_PUBLIC_ALIAS(vswscanf_s, libc_vswscanf_s);
DEFINE_PUBLIC_ALIAS(DOS$fwprintf_s, libd_fwprintf_s);
DEFINE_PUBLIC_ALIAS(fwprintf_s, libc_fwprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$wprintf_s, libd_wprintf_s);
DEFINE_PUBLIC_ALIAS(wprintf_s, libc_wprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$swprintf_s, libd_swprintf_s);
DEFINE_PUBLIC_ALIAS(swprintf_s, libc_swprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$fwscanf_s, libd_fwscanf_s);
DEFINE_PUBLIC_ALIAS(fwscanf_s, libc_fwscanf_s);
DEFINE_PUBLIC_ALIAS(DOS$wscanf_s, libd_wscanf_s);
DEFINE_PUBLIC_ALIAS(wscanf_s, libc_wscanf_s);
DEFINE_PUBLIC_ALIAS(DOS$swscanf_s, libd_swscanf_s);
DEFINE_PUBLIC_ALIAS(swscanf_s, libc_swscanf_s);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_CORECRT_WSTDIO_C */
