/* HASH CRC-32:0xea734de6 */
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
#ifndef GUARD_LIBC_AUTO_CORECRT_WCONIO_H
#define GUARD_LIBC_AUTO_CORECRT_WCONIO_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <corecrt_wconio.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF WUNUSED wint16_t NOTHROW_NCX(LIBDCALL libd__getwch)(void);
INTDEF WUNUSED wint32_t NOTHROW_NCX(LIBKCALL libc__getwch)(void);
INTDEF WUNUSED wint16_t NOTHROW_NCX(LIBDCALL libd__getwch_nolock)(void);
INTDEF WUNUSED wint32_t NOTHROW_NCX(LIBKCALL libc__getwch_nolock)(void);
INTDEF WUNUSED wint16_t NOTHROW_NCX(LIBDCALL libd__getwche)(void);
INTDEF WUNUSED wint32_t NOTHROW_NCX(LIBKCALL libc__getwche)(void);
INTDEF WUNUSED wint16_t NOTHROW_NCX(LIBDCALL libd__getwche_nolock)(void);
INTDEF WUNUSED wint32_t NOTHROW_NCX(LIBKCALL libc__getwche_nolock)(void);
INTDEF wint16_t NOTHROW_NCX(LIBDCALL libd__putwch)(char16_t ch);
INTDEF wint32_t NOTHROW_NCX(LIBKCALL libc__putwch)(char32_t ch);
INTDEF wint16_t NOTHROW_NCX(LIBDCALL libd__putwch_nolock)(char16_t ch);
INTDEF wint32_t NOTHROW_NCX(LIBKCALL libc__putwch_nolock)(char32_t ch);
INTDEF wint16_t NOTHROW_NCX(LIBDCALL libd__ungetwch)(wint16_t ch);
INTDEF wint32_t NOTHROW_NCX(LIBKCALL libc__ungetwch)(wint32_t ch);
INTDEF wint16_t NOTHROW_NCX(LIBDCALL libd__ungetwch_nolock)(wint16_t ch);
INTDEF wint32_t NOTHROW_NCX(LIBKCALL libc__ungetwch_nolock)(wint32_t ch);
INTDEF ATTR_INOUT(1) char16_t *NOTHROW_NCX(LIBDCALL libd__cgetws)(char16_t *__restrict buf);
INTDEF ATTR_INOUT(1) char32_t *NOTHROW_NCX(LIBKCALL libc__cgetws)(char32_t *__restrict buf);
INTDEF ATTR_OUT(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__cgetws_s)(char16_t *buf, size_t bufsize, size_t *__restrict p_readsize);
INTDEF ATTR_OUT(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBKCALL libc__cgetws_s)(char32_t *buf, size_t bufsize, size_t *__restrict p_readsize);
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd__cputws)(char16_t const *__restrict str);
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBKCALL libc__cputws)(char32_t const *__restrict str);
INTDEF ATTR_IN(2) ATTR_LIBC_C16PRINTF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___conio_common_vcwprintf)(uint64_t options, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(2) ATTR_LIBC_C32PRINTF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc___conio_common_vcwprintf)(uint64_t options, char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(2) ATTR_LIBC_C16PRINTF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___conio_common_vcwprintf_s)(uint64_t options, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(2) ATTR_LIBC_C32PRINTF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc___conio_common_vcwprintf_s)(uint64_t options, char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(2) ATTR_LIBC_C16PRINTF_P(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___conio_common_vcwprintf_p)(uint64_t options, char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(2) ATTR_LIBC_C32PRINTF_P(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc___conio_common_vcwprintf_p)(uint64_t options, char32_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED ATTR_IN(2) ATTR_LIBC_C16SCANF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___conio_common_vcwscanf)(uint64_t options, char16_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED ATTR_IN(2) ATTR_LIBC_C32SCANF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc___conio_common_vcwscanf)(uint64_t options, char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcwprintf_l)(char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vcwprintf_l)(char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcwprintf_s_l)(char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vcwprintf_s_l)(char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF_P(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcwprintf_p_l)(char16_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF_P(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vcwprintf_p_l)(char32_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C16SCANF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcwscanf_l)(char16_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C32SCANF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vcwscanf_l)(char32_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C16SCANF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcwscanf_s_l)(char16_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C32SCANF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vcwscanf_s_l)(char32_t const *format, locale_t locale, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcwprintf)(char16_t const *format, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vcwprintf)(char32_t const *format, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcwprintf_s)(char16_t const *format, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vcwprintf_s)(char32_t const *format, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF_P(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcwprintf_p)(const char16_t *format, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF_P(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vcwprintf_p)(const char32_t *format, va_list args);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C16SCANF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcwscanf)(char16_t const *format, va_list args);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C32SCANF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vcwscanf)(char32_t const *format, va_list args);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C16SCANF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcwscanf_s)(char16_t const *format, va_list args);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C32SCANF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vcwscanf_s)(char32_t const *format, va_list args);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cwprintf)(char16_t const *format, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__cwprintf)(char32_t const *format, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cwprintf_l)(char16_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__cwprintf_l)(char32_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cwprintf_s)(char16_t const *format, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__cwprintf_s)(char32_t const *format, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cwprintf_s_l)(char16_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__cwprintf_s_l)(char32_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF_P(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cwprintf_p)(char16_t const *format, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF_P(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__cwprintf_p)(char32_t const *format, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C16PRINTF_P(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cwprintf_p_l)(char16_t const *format, locale_t locale, ...);
INTDEF ATTR_IN(1) ATTR_LIBC_C32PRINTF_P(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__cwprintf_p_l)(char32_t const *format, locale_t locale, ...);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C16SCANF(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cwscanf)(char16_t const *format, ...);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C32SCANF(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__cwscanf)(char32_t const *format, ...);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C16SCANF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cwscanf_l)(char16_t const *format, locale_t locale, ...);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C32SCANF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__cwscanf_l)(char32_t const *format, locale_t locale, ...);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C16SCANF(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cwscanf_s)(char16_t const *format, ...);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C32SCANF(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__cwscanf_s)(char32_t const *format, ...);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C16SCANF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cwscanf_s_l)(char16_t const *format, locale_t locale, ...);
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_C32SCANF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__cwscanf_s_l)(char32_t const *format, locale_t locale, ...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_CORECRT_WCONIO_H */
