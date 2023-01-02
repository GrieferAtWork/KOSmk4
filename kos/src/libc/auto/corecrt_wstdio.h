/* HASH CRC-32:0xeca7a067 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_CORECRT_WSTDIO_H
#define GUARD_LIBC_AUTO_CORECRT_WSTDIO_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <corecrt_wstdio.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_COLD ATTR_IN_OPT(1) void (LIBDCALL libd__wperror)(char16_t const *__restrict message) THROWS(...);
INTDEF ATTR_COLD ATTR_IN_OPT(1) void (LIBKCALL libc__wperror)(char32_t const *__restrict message) THROWS(...);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) FILE *NOTHROW_NCX(LIBDCALL libd__wfsopen)(char16_t const *filename, char16_t const *mode, __STDC_INT_AS_UINT_T sh_flag);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) FILE *NOTHROW_NCX(LIBKCALL libc__wfsopen)(char32_t const *filename, char32_t const *mode, __STDC_INT_AS_UINT_T sh_flag);
INTDEF WUNUSED ATTR_IN(2) FILE *NOTHROW_NCX(LIBDCALL libd__wfdopen)(fd_t fd, char16_t const *mode);
INTDEF WUNUSED ATTR_IN(2) FILE *NOTHROW_NCX(LIBKCALL libc__wfdopen)(fd_t fd, char32_t const *mode);
INTDEF ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1) errno_t NOTHROW_NCX(LIBDCALL libd__wfopen_s)(FILE **pstream, char16_t const *filename, char16_t const *mode);
INTDEF ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1) errno_t NOTHROW_NCX(LIBKCALL libc__wfopen_s)(FILE **pstream, char32_t const *filename, char32_t const *mode);
INTDEF ATTR_IN(2) ATTR_IN(3) ATTR_INOUT_OPT(4) ATTR_OUT(1) errno_t NOTHROW_NCX(LIBDCALL libd__wfreopen_s)(FILE **pstream, char16_t const *filename, char16_t const *mode, FILE *stream);
INTDEF ATTR_IN(2) ATTR_IN(3) ATTR_INOUT_OPT(4) ATTR_OUT(1) errno_t NOTHROW_NCX(LIBKCALL libc__wfreopen_s)(FILE **pstream, char32_t const *filename, char32_t const *mode, FILE *stream);
INTDEF ATTR_OUT(1) char16_t *NOTHROW_NCX(LIBDCALL libd__getws)(char16_t *buf);
INTDEF ATTR_OUT(1) char32_t *NOTHROW_NCX(LIBKCALL libc__getws)(char32_t *buf);
INTDEF ATTR_OUTS(1, 2) char16_t *NOTHROW_NCX(LIBDCALL libd__getws_s)(char16_t *buf, size_t buflen);
INTDEF ATTR_OUTS(1, 2) char32_t *NOTHROW_NCX(LIBKCALL libc__getws_s)(char32_t *buf, size_t buflen);
INTDEF ATTR_IN(1) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd__putws)(char16_t const *str);
INTDEF ATTR_IN(1) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBKCALL libc__putws)(char32_t const *str);
INTDEF ATTR_IN(3) ATTR_INOUT(2) ATTR_LIBC_C16PRINTF(3, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___stdio_common_vfwprintf)(uint64_t options, FILE *stream, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(3) ATTR_INOUT(2) ATTR_LIBC_C32PRINTF(3, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc___stdio_common_vfwprintf)(uint64_t options, FILE *stream, char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(3) ATTR_INOUT(2) ATTR_LIBC_C16PRINTF(3, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___stdio_common_vfwprintf_s)(uint64_t options, FILE *stream, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(3) ATTR_INOUT(2) ATTR_LIBC_C32PRINTF(3, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc___stdio_common_vfwprintf_s)(uint64_t options, FILE *stream, char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(3) ATTR_INOUT(2) ATTR_LIBC_C16PRINTF_P(3, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___stdio_common_vfwprintf_p)(uint64_t options, FILE *stream, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(3) ATTR_INOUT(2) ATTR_LIBC_C32PRINTF_P(3, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc___stdio_common_vfwprintf_p)(uint64_t options, FILE *stream, char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(4) ATTR_LIBC_C16PRINTF(4, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___stdio_common_vswprintf)(uint64_t options, char16_t *buf, size_t bufsize, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(4) ATTR_LIBC_C32PRINTF(4, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc___stdio_common_vswprintf)(uint64_t options, char32_t *buf, size_t bufsize, char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(4) ATTR_LIBC_C16PRINTF(4, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___stdio_common_vswprintf_s)(uint64_t options, char16_t *buf, size_t bufsize, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(4) ATTR_LIBC_C32PRINTF(4, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc___stdio_common_vswprintf_s)(uint64_t options, char32_t *buf, size_t bufsize, char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(5) ATTR_LIBC_C16PRINTF(5, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___stdio_common_vsnwprintf_s)(uint64_t options, char16_t *buf, size_t bufsize, size_t maxsize, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(5) ATTR_LIBC_C32PRINTF(5, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc___stdio_common_vsnwprintf_s)(uint64_t options, char32_t *buf, size_t bufsize, size_t maxsize, char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(4) ATTR_LIBC_C16PRINTF_P(4, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___stdio_common_vswprintf_p)(uint64_t options, char16_t *buf, size_t bufsize, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(4) ATTR_LIBC_C32PRINTF_P(4, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc___stdio_common_vswprintf_p)(uint64_t options, char32_t *buf, size_t bufsize, char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(3) ATTR_INOUT(2) ATTR_LIBC_C16SCANF(3, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___stdio_common_vfwscanf)(uint64_t options, FILE *stream, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(3) ATTR_INOUT(2) ATTR_LIBC_C32SCANF(3, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc___stdio_common_vfwscanf)(uint64_t options, FILE *stream, char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(4) ATTR_INS(2, 3) ATTR_LIBC_C16SCANF(4, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___stdio_common_vswscanf)(uint64_t options, char16_t const *buf, size_t bufsize, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(4) ATTR_INS(2, 3) ATTR_LIBC_C32SCANF(4, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc___stdio_common_vswscanf)(uint64_t options, char32_t const *buf, size_t bufsize, char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(3) ATTR_LIBC_C16PRINTF(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vsnwprintf_l)(char16_t *buf, size_t bufsize, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(3) ATTR_LIBC_C32PRINTF(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vsnwprintf_l)(char32_t *buf, size_t bufsize, char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(3) ATTR_LIBC_C16PRINTF(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vswprintf_s_l)(char16_t *buf, size_t bufsize, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(3) ATTR_LIBC_C32PRINTF(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vswprintf_s_l)(char32_t *buf, size_t bufsize, char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(3) ATTR_LIBC_C16PRINTF_P(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vswprintf_p_l)(char16_t *buf, size_t bufsize, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(3) ATTR_LIBC_C32PRINTF_P(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vswprintf_p_l)(char32_t *buf, size_t bufsize, char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vscwprintf_l)(char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vscwprintf_l)(char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF_P(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vscwprintf_p_l)(char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF_P(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vscwprintf_p_l)(char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(3) ATTR_LIBC_C16PRINTF(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vswprintf_c_l)(char16_t *buf, size_t bufsize, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(3) ATTR_LIBC_C32PRINTF(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vswprintf_c_l)(char32_t *buf, size_t bufsize, char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(4) ATTR_LIBC_C16PRINTF(4, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vsnwprintf_s_l)(char16_t *buf, size_t bufsize, size_t maxsize, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(4) ATTR_LIBC_C32PRINTF(4, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vsnwprintf_s_l)(char32_t *buf, size_t bufsize, size_t maxsize, char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16PRINTF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vfwprintf_s_l)(FILE *stream, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32PRINTF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vfwprintf_s_l)(FILE *stream, char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16PRINTF_P(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vfwprintf_p_l)(FILE *stream, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32PRINTF_P(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vfwprintf_p_l)(FILE *stream, char32_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16SCANF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vfwscanf_l)(FILE *stream, char16_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32SCANF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vfwscanf_l)(FILE *stream, char32_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16SCANF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vfwscanf_s_l)(FILE *stream, char16_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32SCANF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vfwscanf_s_l)(FILE *stream, char32_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_C16SCANF(3, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vsnwscanf_l)(char16_t const *buf, size_t bufsize, char16_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_C32SCANF(3, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vsnwscanf_l)(char32_t const *buf, size_t bufsize, char32_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_C16SCANF(3, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vsnwscanf_s_l)(char16_t const *buf, size_t bufsize, char16_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_C32SCANF(3, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vsnwscanf_s_l)(char32_t const *buf, size_t bufsize, char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vwprintf_l)(char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vwprintf_l)(char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16PRINTF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vfwprintf_l)(FILE *stream, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32PRINTF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vfwprintf_l)(FILE *stream, char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(2) ATTR_LIBC_C16PRINTF(2, 0) ATTR_OUT(1) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___vswprintf_l)(char16_t *buf, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(2) ATTR_LIBC_C32PRINTF(2, 0) ATTR_OUT(1) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc___vswprintf_l)(char32_t *buf, char32_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C16SCANF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vwscanf_l)(char16_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C32SCANF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vwscanf_l)(char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(4) ATTR_LIBC_C16PRINTF(4, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vsnwprintf_s)(char16_t *buf, size_t bufsize, size_t maxsize, char16_t const *format, va_list args);
INTDEF ATTR_IN(4) ATTR_LIBC_C32PRINTF(4, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vsnwprintf_s)(char32_t *buf, size_t bufsize, size_t maxsize, char32_t const *format, va_list args);
INTDEF ATTR_IN(3) ATTR_LIBC_C16PRINTF(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vsnwprintf)(char16_t *buf, size_t bufsize, char16_t const *format, va_list args);
INTDEF ATTR_IN(3) ATTR_LIBC_C32PRINTF(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vsnwprintf)(char32_t *buf, size_t bufsize, char32_t const *format, va_list args);
INTDEF ATTR_IN(3) ATTR_LIBC_C16PRINTF(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vswprintf_c)(char16_t *buf, size_t bufsize, char16_t const *format, va_list args);
INTDEF ATTR_IN(3) ATTR_LIBC_C32PRINTF(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vswprintf_c)(char32_t *buf, size_t bufsize, char32_t const *format, va_list args);
INTDEF ATTR_IN(2) ATTR_LIBC_C16PRINTF(2, 0) ATTR_OUT(1) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vswprintf)(char16_t *buf, char16_t const *format, va_list args);
INTDEF ATTR_IN(2) ATTR_LIBC_C32PRINTF(2, 0) ATTR_OUT(1) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vswprintf)(char32_t *buf, char32_t const *format, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vscwprintf)(char16_t const *format, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vscwprintf)(char32_t const *format, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF_P(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vscwprintf_p)(char16_t const *format, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF_P(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vscwprintf_p)(char32_t const *format, va_list args);
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_C16SCANF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vswscanf_l)(char16_t const *buf, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_C32SCANF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vswscanf_l)(char32_t const *buf, char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_C16SCANF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vswscanf_s_l)(char16_t const *buf, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_C32SCANF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vswscanf_s_l)(char32_t const *buf, char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_C16SCANF(3, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vsnwscanf)(char16_t const *buf, size_t bufsize, char16_t const *format, va_list args);
INTDEF ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_C32SCANF(3, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vsnwscanf)(char32_t const *buf, size_t bufsize, char32_t const *format, va_list args);
INTDEF ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_C16SCANF(3, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vsnwscanf_s)(char16_t const *buf, size_t bufsize, char16_t const *format, va_list args);
INTDEF ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_C32SCANF(3, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vsnwscanf_s)(char32_t const *buf, size_t bufsize, char32_t const *format, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vwprintf_s_l)(char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vwprintf_s_l)(char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF_P(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vwprintf_p_l)(char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF_P(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vwprintf_p_l)(char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C16SCANF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vwscanf_s_l)(char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C32SCANF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vwscanf_s_l)(char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16PRINTF(2, 4) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__fwprintf_l)(FILE *stream, char16_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32PRINTF(2, 4) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__fwprintf_l)(FILE *stream, char32_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16PRINTF(2, 4) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__fwprintf_s_l)(FILE *stream, char16_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32PRINTF(2, 4) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__fwprintf_s_l)(FILE *stream, char32_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16PRINTF_P(2, 4) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__fwprintf_p_l)(FILE *stream, char16_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32PRINTF_P(2, 4) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__fwprintf_p_l)(FILE *stream, char32_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__wprintf_l)(char16_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__wprintf_l)(char32_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__wprintf_s_l)(char16_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__wprintf_s_l)(char32_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF_P(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__wprintf_p_l)(char16_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF_P(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__wprintf_p_l)(char32_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(2) ATTR_LIBC_C16PRINTF(2, 4) ATTR_OUT(1) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd___swprintf_l)(char16_t *buf, char16_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(2) ATTR_LIBC_C32PRINTF(2, 4) ATTR_OUT(1) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc___swprintf_l)(char32_t *buf, char32_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(2) ATTR_LIBC_C16PRINTF(2, 3) ATTR_OUT(1) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__swprintf)(char16_t *buf, char16_t const *format, ...);
INTDEF ATTR_IN(2) ATTR_LIBC_C32PRINTF(2, 3) ATTR_OUT(1) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__swprintf)(char32_t *buf, char32_t const *format, ...);
INTDEF ATTR_IN(3) ATTR_LIBC_C16PRINTF(3, 5) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__swprintf_s_l)(char16_t *buf, size_t bufsize, char16_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(3) ATTR_LIBC_C32PRINTF(3, 5) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__swprintf_s_l)(char32_t *buf, size_t bufsize, char32_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(3) ATTR_LIBC_C16PRINTF_P(3, 5) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__swprintf_p_l)(char16_t *buf, size_t bufsize, char16_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(3) ATTR_LIBC_C32PRINTF_P(3, 5) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__swprintf_p_l)(char32_t *buf, size_t bufsize, char32_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(3) ATTR_LIBC_C16PRINTF(3, 5) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__swprintf_c_l)(char16_t *buf, size_t bufsize, char16_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(3) ATTR_LIBC_C32PRINTF(3, 5) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__swprintf_c_l)(char32_t *buf, size_t bufsize, char32_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(3) ATTR_LIBC_C16PRINTF(3, 5) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__snwprintf_l)(char16_t *buf, size_t bufsize, char16_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(3) ATTR_LIBC_C32PRINTF(3, 5) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__snwprintf_l)(char32_t *buf, size_t bufsize, char32_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(4) ATTR_LIBC_C16PRINTF(4, 6) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__snwprintf_s_l)(char16_t *buf, size_t bufsize, size_t maxsize, char16_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(4) ATTR_LIBC_C32PRINTF(4, 6) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__snwprintf_s_l)(char32_t *buf, size_t bufsize, size_t maxsize, char32_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(3) ATTR_LIBC_C16PRINTF(3, 4) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__swprintf_c)(char16_t *buf, size_t bufsize, char16_t const *format, ...);
INTDEF ATTR_IN(3) ATTR_LIBC_C32PRINTF(3, 4) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__swprintf_c)(char32_t *buf, size_t bufsize, char32_t const *format, ...);
INTDEF ATTR_IN(3) ATTR_LIBC_C16PRINTF(3, 4) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__snwprintf)(char16_t *buf, size_t bufsize, char16_t const *format, ...);
INTDEF ATTR_IN(3) ATTR_LIBC_C32PRINTF(3, 4) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__snwprintf)(char32_t *buf, size_t bufsize, char32_t const *format, ...);
INTDEF ATTR_IN(4) ATTR_LIBC_C16PRINTF(4, 5) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__snwprintf_s)(char16_t *buf, size_t bufsize, size_t maxsize, char16_t const *format, ...);
INTDEF ATTR_IN(4) ATTR_LIBC_C32PRINTF(4, 5) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__snwprintf_s)(char32_t *buf, size_t bufsize, size_t maxsize, char32_t const *format, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__scwprintf_l)(char16_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__scwprintf_l)(char32_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF_P(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__scwprintf_p_l)(char16_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF_P(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__scwprintf_p_l)(char32_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__scwprintf)(char16_t const *format, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__scwprintf)(char32_t const *format, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF_P(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__scwprintf_p)(char16_t const *format, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF_P(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__scwprintf_p)(char32_t const *format, ...);
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16SCANF(2, 4) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__fwscanf_l)(FILE *stream, char16_t const *format, locale_t locale, ...);
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32SCANF(2, 4) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__fwscanf_l)(FILE *stream, char32_t const *format, locale_t locale, ...);
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16SCANF(2, 4) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__fwscanf_s_l)(FILE *stream, char16_t const *format, locale_t locale, ...);
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32SCANF(2, 4) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__fwscanf_s_l)(FILE *stream, char32_t const *format, locale_t locale, ...);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C16SCANF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__wscanf_l)(char16_t const *format, locale_t locale, ...);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C32SCANF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__wscanf_l)(char32_t const *format, locale_t locale, ...);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C16SCANF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__wscanf_s_l)(char16_t const *format, locale_t locale, ...);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C32SCANF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__wscanf_s_l)(char32_t const *format, locale_t locale, ...);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_C16SCANF(2, 4) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__swscanf_l)(char16_t const *buf, char16_t const *format, locale_t locale, ...);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_C32SCANF(2, 4) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__swscanf_l)(char32_t const *buf, char32_t const *format, locale_t locale, ...);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_C16SCANF(2, 4) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__swscanf_s_l)(char16_t const *buf, char16_t const *format, locale_t locale, ...);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_C32SCANF(2, 4) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__swscanf_s_l)(char32_t const *buf, char32_t const *format, locale_t locale, ...);
INTDEF WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_C16SCANF(3, 5) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__snwscanf_l)(char16_t const *buf, size_t bufsize, char16_t const *format, locale_t locale, ...);
INTDEF WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_C32SCANF(3, 5) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__snwscanf_l)(char32_t const *buf, size_t bufsize, char32_t const *format, locale_t locale, ...);
INTDEF WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_C16SCANF(3, 4) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__snwscanf)(char16_t const *buf, size_t bufsize, char16_t const *format, ...);
INTDEF WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_C32SCANF(3, 4) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__snwscanf)(char32_t const *buf, size_t bufsize, char32_t const *format, ...);
INTDEF WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_C16SCANF(3, 5) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__snwscanf_s_l)(char16_t const *buf, size_t bufsize, char16_t const *format, locale_t locale, ...);
INTDEF WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_C32SCANF(3, 5) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__snwscanf_s_l)(char32_t const *buf, size_t bufsize, char32_t const *format, locale_t locale, ...);
INTDEF WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_C16SCANF(3, 4) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__snwscanf_s)(char16_t const *buf, size_t bufsize, char16_t const *format, ...);
INTDEF WUNUSED ATTR_IN(3) ATTR_INS(1, 2) ATTR_LIBC_C32SCANF(3, 4) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__snwscanf_s)(char32_t const *buf, size_t bufsize, char32_t const *format, ...);
INTDEF ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16PRINTF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd_vfwprintf_s)(FILE *stream, char16_t const *format, va_list args);
INTDEF ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32PRINTF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc_vfwprintf_s)(FILE *stream, char32_t const *format, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd_vwprintf_s)(char16_t const *format, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc_vwprintf_s)(char32_t const *format, va_list args);
INTDEF ATTR_IN(3) ATTR_LIBC_C16PRINTF(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd_vswprintf_s)(char16_t *buf, size_t bufsize, char16_t const *format, va_list args);
INTDEF ATTR_IN(3) ATTR_LIBC_C32PRINTF(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc_vswprintf_s)(char32_t *buf, size_t bufsize, char32_t const *format, va_list args);
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16SCANF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd_vfwscanf_s)(FILE *stream, char16_t const *format, va_list args);
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32SCANF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc_vfwscanf_s)(FILE *stream, char32_t const *format, va_list args);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C16SCANF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd_vwscanf_s)(char16_t const *format, va_list args);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C32SCANF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc_vwscanf_s)(char32_t const *format, va_list args);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_C16SCANF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd_vswscanf_s)(char16_t const *buf, char16_t const *format, va_list args);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_C32SCANF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc_vswscanf_s)(char32_t const *buf, char32_t const *format, va_list args);
INTDEF ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16PRINTF(2, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd_fwprintf_s)(FILE *stream, char16_t const *format, ...);
INTDEF ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32PRINTF(2, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc_fwprintf_s)(FILE *stream, char32_t const *format, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd_wprintf_s)(char16_t const *format, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc_wprintf_s)(char32_t const *format, ...);
INTDEF ATTR_IN(3) ATTR_LIBC_C16PRINTF(3, 4) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd_swprintf_s)(char16_t *buf, size_t bufsize, char16_t const *format, ...);
INTDEF ATTR_IN(3) ATTR_LIBC_C32PRINTF(3, 4) ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc_swprintf_s)(char32_t *buf, size_t bufsize, char32_t const *format, ...);
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16SCANF(2, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd_fwscanf_s)(FILE *stream, char16_t const *format, ...);
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32SCANF(2, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc_fwscanf_s)(FILE *stream, char32_t const *format, ...);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C16SCANF(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd_wscanf_s)(char16_t const *format, ...);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C32SCANF(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc_wscanf_s)(char32_t const *format, ...);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_C16SCANF(2, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd_swscanf_s)(char16_t const *buf, char16_t const *format, ...);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_C32SCANF(2, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc_swscanf_s)(char32_t const *buf, char32_t const *format, ...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_CORECRT_WSTDIO_H */
