/* HASH CRC-32:0xc542162c */
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
#ifndef GUARD_LIBC_AUTO_WCHAR_H
#define GUARD_LIBC_AUTO_WCHAR_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <wchar.h>

DECL_BEGIN

#ifndef __errno_t_defined
#define __errno_t_defined
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */
#ifndef __rsize_t_defined
#define __rsize_t_defined
typedef size_t rsize_t;
#endif /* !__rsize_t_defined */

#ifndef __KERNEL__
/* >> btowc(3)
 * Convert a single-byte into a wide character. If the given
 * character `ch' isn't valid, or  is `EOF', then `WEOF'  is
 * returned instead. */
INTDEF ATTR_CONST WUNUSED wint16_t NOTHROW_NCX(LIBDCALL libd_btowc)(int ch);
/* >> btowc(3)
 * Convert a single-byte into a wide character. If the given
 * character `ch' isn't valid, or  is `EOF', then `WEOF'  is
 * returned instead. */
INTDEF ATTR_CONST WUNUSED wint32_t NOTHROW_NCX(LIBKCALL libc_btowc)(int ch);
/* >> wctob(3)
 * Convert a wide-character into a single-byte character. If
 * doing so isn't possible, then `EOF' is returned  instead. */
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBDCALL libd_wctob)(wint16_t ch);
/* >> wctob(3)
 * Convert a wide-character into a single-byte character. If
 * doing so isn't possible, then `EOF' is returned  instead. */
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBKCALL libc_wctob)(wint32_t ch);
/* >> mbrtowc(3) */
INTDEF size_t NOTHROW_NCX(LIBDCALL libd_mbrtowc)(char16_t *pwc, char const *__restrict str, size_t maxlen, mbstate_t *mbs);
/* >> mbrtowc(3) */
INTDEF size_t NOTHROW_NCX(LIBKCALL libc_mbrtowc)(char32_t *pwc, char const *__restrict str, size_t maxlen, mbstate_t *mbs);
/* >> wcrtomb(3) */
INTDEF size_t NOTHROW_NCX(LIBDCALL libd_wcrtomb)(char *__restrict str, char16_t wc, mbstate_t *mbs);
/* >> wcrtomb(3) */
INTDEF size_t NOTHROW_NCX(LIBKCALL libc_wcrtomb)(char *__restrict str, char32_t wc, mbstate_t *mbs);
/* >> mbrlen(3) */
INTDEF WUNUSED size_t NOTHROW_NCX(LIBDCALL libd_mbrlen)(char const *__restrict str, size_t maxlen, mbstate_t *mbs);
/* >> mbrlen(3) */
INTDEF WUNUSED size_t NOTHROW_NCX(LIBKCALL libc_mbrlen)(char const *__restrict str, size_t maxlen, mbstate_t *mbs);
/* >> mbsrtowcs(3) */
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_mbsrtowcs)(char16_t *__restrict dst, char const **__restrict psrc, size_t dstlen, mbstate_t *mbs);
/* >> mbsrtowcs(3) */
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBKCALL libc_mbsrtowcs)(char32_t *__restrict dst, char const **__restrict psrc, size_t dstlen, mbstate_t *mbs);
/* >> wcsrtombs(3) */
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_wcsrtombs)(char *dst, char16_t const **__restrict psrc, size_t dstlen, mbstate_t *mbs);
/* >> wcsrtombs(3) */
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBKCALL libc_wcsrtombs)(char *dst, char32_t const **__restrict psrc, size_t dstlen, mbstate_t *mbs);
/* >> wcstol(3) */
INTDEF ATTR_LEAF NONNULL((1)) long NOTHROW_NCX(LIBDCALL libd_wcstol)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base);
/* >> wcstol(3) */
INTDEF ATTR_LEAF NONNULL((1)) long NOTHROW_NCX(LIBKCALL libc_wcstol)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base);
/* >> wcstoul(3) */
INTDEF ATTR_LEAF NONNULL((1)) unsigned long NOTHROW_NCX(LIBDCALL libd_wcstoul)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base);
/* >> wcstoul(3) */
INTDEF ATTR_LEAF NONNULL((1)) unsigned long NOTHROW_NCX(LIBKCALL libc_wcstoul)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mbsinit(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_mbsinit)(mbstate_t const *mbs);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mbsinit(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_mbsinit)(mbstate_t const *mbs);
/* >> wmemcmp(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wmemcmp)(char16_t const *s1, char16_t const *s2, size_t num_chars);
/* >> wmemcmp(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wmemcmp)(char32_t const *s1, char32_t const *s2, size_t num_chars);
/* >> wcscpy(3) */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcscpy)(char16_t *__restrict buf, char16_t const *__restrict src);
/* >> wcscpy(3) */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcscpy)(char32_t *__restrict buf, char32_t const *__restrict src);
/* >> wcscat(3) */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcscat)(char16_t *__restrict buf, char16_t const *__restrict src);
/* >> wcscat(3) */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcscat)(char32_t *__restrict buf, char32_t const *__restrict src);
/* >> wcsncat(3) */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsncat)(char16_t *__restrict buf, char16_t const *__restrict src, size_t buflen);
/* >> wcsncat(3) */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsncat)(char32_t *__restrict buf, char32_t const *__restrict src, size_t buflen);
/* >> wcsncpy(3) */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsncpy)(char16_t *__restrict buf, char16_t const *__restrict src, size_t buflen);
/* >> wcsncpy(3) */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsncpy)(char32_t *__restrict buf, char32_t const *__restrict src, size_t buflen);
/* >> wcscmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBDCALL libd_wcscmp)(char16_t const *s1, char16_t const *s2);
/* >> wcscmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBKCALL libc_wcscmp)(char32_t const *s1, char32_t const *s2);
/* >> wcsncmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_ROS(1, 3) ATTR_ACCESS_ROS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsncmp)(char16_t const *s1, char16_t const *s2, size_t maxlen);
/* >> wcsncmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_ROS(1, 3) ATTR_ACCESS_ROS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcsncmp)(char32_t const *s1, char32_t const *s2, size_t maxlen);
/* >> wcscoll(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBDCALL libd_wcscoll)(char16_t const *s1, char16_t const *s2);
/* >> wcscoll(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBKCALL libc_wcscoll)(char32_t const *s1, char32_t const *s2);
/* >> wcsxfrm(3) */
INTDEF ATTR_ACCESS_ROS(2, 3) ATTR_ACCESS_WRS(1, 3) size_t NOTHROW_NCX(LIBDCALL libd_wcsxfrm)(char16_t *dst, char16_t const *__restrict src, size_t buflen);
/* >> wcsxfrm(3) */
INTDEF ATTR_ACCESS_ROS(2, 3) ATTR_ACCESS_WRS(1, 3) size_t NOTHROW_NCX(LIBKCALL libc_wcsxfrm)(char32_t *dst, char32_t const *__restrict src, size_t buflen);
/* >> getwchar(3), getwchar_unlocked(3) */
INTDEF wint16_t (LIBDCALL libd_getwchar)(void) THROWS(...);
/* >> getwchar(3), getwchar_unlocked(3) */
INTDEF wint32_t (LIBKCALL libc_getwchar)(void) THROWS(...);
/* >> putwchar(3), putwchar_unlocked(3) */
INTDEF wint16_t (LIBDCALL libd_putwchar)(char16_t wc) THROWS(...);
/* >> putwchar(3), putwchar_unlocked(3) */
INTDEF wint32_t (LIBKCALL libc_putwchar)(char32_t wc) THROWS(...);
/* >> fgetws(3), fgetws_unlocked(3) */
INTDEF WUNUSED ATTR_ACCESS_RW(3) NONNULL((1)) char16_t *(LIBDCALL libd_fgetws)(char16_t *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) THROWS(...);
/* >> fgetws(3), fgetws_unlocked(3) */
INTDEF WUNUSED ATTR_ACCESS_RW(3) NONNULL((1)) char32_t *(LIBKCALL libc_fgetws)(char32_t *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) THROWS(...);
/* >> fputws(3), fputws_unlocked(3) */
INTDEF ATTR_ACCESS_RW(2) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_fputws)(char16_t const *__restrict str, FILE *__restrict stream) THROWS(...);
/* >> fputws(3), fputws_unlocked(3) */
INTDEF ATTR_ACCESS_RW(2) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_fputws)(char32_t const *__restrict str, FILE *__restrict stream) THROWS(...);
/* >> wcsftime(3) */
INTDEF ATTR_LIBC_C16FTIME(3, 0) NONNULL((1, 3, 4)) size_t NOTHROW_NCX(LIBDCALL libd_wcsftime)(char16_t *__restrict buf, size_t buflen, char16_t const *__restrict format, struct tm const *__restrict tp);
/* >> wcsftime(3) */
INTDEF ATTR_LIBC_C32FTIME(3, 0) NONNULL((1, 3, 4)) size_t NOTHROW_NCX(LIBKCALL libc_wcsftime)(char32_t *__restrict buf, size_t buflen, char32_t const *__restrict format, struct tm const *__restrict tp);
/* >> wcstok(3) */
INTDEF NONNULL((2, 3)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcstok)(char16_t *str, char16_t const *__restrict delim, char16_t **__restrict save_ptr);
/* >> wcstok(3) */
INTDEF NONNULL((2, 3)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcstok)(char32_t *str, char32_t const *__restrict delim, char32_t **__restrict save_ptr);
/* >> wcslen(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) size_t NOTHROW_NCX(LIBDCALL libd_wcslen)(char16_t const *__restrict str);
/* >> wcslen(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) size_t NOTHROW_NCX(LIBKCALL libc_wcslen)(char32_t const *__restrict str);
/* >> wcsspn(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) size_t NOTHROW_NCX(LIBDCALL libd_wcsspn)(char16_t const *haystack, char16_t const *accept);
/* >> wcsspn(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) size_t NOTHROW_NCX(LIBKCALL libc_wcsspn)(char32_t const *haystack, char32_t const *accept);
/* >> wcscspn(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) size_t NOTHROW_NCX(LIBDCALL libd_wcscspn)(char16_t const *haystack, char16_t const *reject);
/* >> wcscspn(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) size_t NOTHROW_NCX(LIBKCALL libc_wcscspn)(char32_t const *haystack, char32_t const *reject);
/* >> wcschr(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcschr)(char16_t const *__restrict haystack, char16_t needle);
/* >> wcschr(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcschr)(char32_t const *__restrict haystack, char32_t needle);
/* >> wcsrchr(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsrchr)(char16_t const *__restrict haystack, char16_t needle);
/* >> wcsrchr(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsrchr)(char32_t const *__restrict haystack, char32_t needle);
/* >> wcspbrk(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcspbrk)(char16_t const *haystack, char16_t const *accept);
/* >> wcspbrk(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcspbrk)(char32_t const *haystack, char32_t const *accept);
/* >> wcsstr(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsstr)(char16_t const *haystack, char16_t const *needle);
/* >> wcsstr(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsstr)(char32_t const *haystack, char32_t const *needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fwide(3) */
INTDEF ATTR_ACCESS_RW(1) int NOTHROW_NCX(LIBDCALL libd_fwide)(FILE *fp, int mode);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fwide(3) */
INTDEF ATTR_ACCESS_RW(1) int NOTHROW_NCX(LIBCCALL libc_fwide)(FILE *fp, int mode);
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
INTDEF ATTR_ACCESS_RW(1) ATTR_LIBC_C16PRINTF(2, 3) NONNULL((2)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_fwprintf)(FILE *__restrict stream, char16_t const *__restrict format, ...) THROWS(...);
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
INTDEF ATTR_ACCESS_RW(1) ATTR_LIBC_C32PRINTF(2, 3) NONNULL((2)) __STDC_INT_AS_SIZE_T (VLIBKCALL libc_fwprintf)(FILE *__restrict stream, char32_t const *__restrict format, ...) THROWS(...);
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
INTDEF ATTR_ACCESS_RW(1) ATTR_LIBC_C16PRINTF(2, 0) NONNULL((2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vfwprintf)(FILE *__restrict stream, char16_t const *__restrict format, va_list args) THROWS(...);
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
INTDEF ATTR_ACCESS_RW(1) ATTR_LIBC_C32PRINTF(2, 0) NONNULL((2)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_vfwprintf)(FILE *__restrict stream, char32_t const *__restrict format, va_list args) THROWS(...);
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
INTDEF ATTR_LIBC_C16PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_wprintf)(char16_t const *__restrict format, ...) THROWS(...);
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
INTDEF ATTR_LIBC_C32PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBKCALL libc_wprintf)(char32_t const *__restrict format, ...) THROWS(...);
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
INTDEF ATTR_LIBC_C16PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vwprintf)(char16_t const *__restrict format, va_list args) THROWS(...);
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
INTDEF ATTR_LIBC_C32PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_vwprintf)(char32_t const *__restrict format, va_list args) THROWS(...);
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
INTDEF ATTR_ACCESS_RW(1) ATTR_LIBC_C16SCANF(2, 3) NONNULL((2)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_fwscanf)(FILE *__restrict stream, char16_t const *__restrict format, ...) THROWS(...);
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
INTDEF ATTR_ACCESS_RW(1) ATTR_LIBC_C32SCANF(2, 3) NONNULL((2)) __STDC_INT_AS_SIZE_T (VLIBKCALL libc_fwscanf)(FILE *__restrict stream, char32_t const *__restrict format, ...) THROWS(...);
/* >> wscanf(3), vwscanf(3), wscanf_unlocked(3), vwscanf_unlocked(3) */
INTDEF ATTR_LIBC_C16SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_wscanf)(char16_t const *__restrict format, ...) THROWS(...);
/* >> wscanf(3), vwscanf(3), wscanf_unlocked(3), vwscanf_unlocked(3) */
INTDEF ATTR_LIBC_C32SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBKCALL libc_wscanf)(char32_t const *__restrict format, ...) THROWS(...);
/* >> swscanf(3), vswscanf(3) */
INTDEF ATTR_LIBC_C16SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd_swscanf)(char16_t const *__restrict src, char16_t const *__restrict format, ...);
/* >> swscanf(3), vswscanf(3) */
INTDEF ATTR_LIBC_C32SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBKCALL libc_swscanf)(char32_t const *__restrict src, char32_t const *__restrict format, ...);
/* >> vswprintf(3) */
INTDEF ATTR_LIBC_C16PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd_vswprintf)(char16_t *__restrict buf, size_t buflen, char16_t const *__restrict format, va_list args);
/* >> vswprintf(3) */
INTDEF ATTR_LIBC_C32PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBKCALL libc_vswprintf)(char32_t *__restrict buf, size_t buflen, char32_t const *__restrict format, va_list args);
/* >> swprintf(3) */
INTDEF ATTR_LIBC_C16PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd_swprintf)(char16_t *__restrict buf, size_t buflen, char16_t const *__restrict format, ...);
/* >> swprintf(3) */
INTDEF ATTR_LIBC_C32PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBKCALL libc_swprintf)(char32_t *__restrict buf, size_t buflen, char32_t const *__restrict format, ...);
/* >> wcstod(3) */
INTDEF ATTR_LEAF NONNULL((1)) double NOTHROW_NCX(LIBDCALL libd_wcstod)(char16_t const *__restrict nptr, char16_t **endptr);
/* >> wcstod(3) */
INTDEF ATTR_LEAF NONNULL((1)) double NOTHROW_NCX(LIBKCALL libc_wcstod)(char32_t const *__restrict nptr, char32_t **endptr);
/* >> wcstof(3) */
INTDEF ATTR_LEAF NONNULL((1)) float NOTHROW_NCX(LIBDCALL libd_wcstof)(char16_t const *__restrict nptr, char16_t **endptr);
/* >> wcstof(3) */
INTDEF ATTR_LEAF NONNULL((1)) float NOTHROW_NCX(LIBKCALL libc_wcstof)(char32_t const *__restrict nptr, char32_t **endptr);
/* >> wcstold(3) */
INTDEF ATTR_LEAF NONNULL((1)) __LONGDOUBLE NOTHROW_NCX(LIBDCALL libd_wcstold)(char16_t const *__restrict nptr, char16_t **endptr);
/* >> wcstold(3) */
INTDEF ATTR_LEAF NONNULL((1)) __LONGDOUBLE NOTHROW_NCX(LIBKCALL libc_wcstold)(char32_t const *__restrict nptr, char32_t **endptr);
/* >> wcstoll(3) */
INTDEF ATTR_LEAF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBDCALL libd_wcstoll)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base);
/* >> wcstoll(3) */
INTDEF ATTR_LEAF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBKCALL libc_wcstoll)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base);
/* >> wcstoull(3) */
INTDEF ATTR_LEAF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBDCALL libd_wcstoull)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base);
/* >> wcstoull(3) */
INTDEF ATTR_LEAF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBKCALL libc_wcstoull)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base);
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
INTDEF WUNUSED ATTR_ACCESS_RW(1) ATTR_LIBC_C16SCANF(2, 0) NONNULL((2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vfwscanf)(FILE *__restrict stream, char16_t const *__restrict format, va_list args) THROWS(...);
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
INTDEF WUNUSED ATTR_ACCESS_RW(1) ATTR_LIBC_C32SCANF(2, 0) NONNULL((2)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_vfwscanf)(FILE *__restrict stream, char32_t const *__restrict format, va_list args) THROWS(...);
/* >> vwscanf(3) */
INTDEF WUNUSED ATTR_LIBC_C16SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vwscanf)(char16_t const *__restrict format, va_list args) THROWS(...);
/* >> vwscanf(3) */
INTDEF WUNUSED ATTR_LIBC_C32SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_vwscanf)(char32_t const *__restrict format, va_list args) THROWS(...);
/* >> swscanf(3), vswscanf(3) */
INTDEF WUNUSED ATTR_LIBC_C16SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd_vswscanf)(char16_t const *__restrict input, char16_t const *__restrict format, va_list args);
/* >> swscanf(3), vswscanf(3) */
INTDEF WUNUSED ATTR_LIBC_C32SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBKCALL libc_vswscanf)(char32_t const *__restrict input, char32_t const *__restrict format, va_list args);
/* >> wcscasecmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBDCALL libd_wcscasecmp)(char16_t const *s1, char16_t const *s2);
/* >> wcscasecmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBKCALL libc_wcscasecmp)(char32_t const *s1, char32_t const *s2);
/* >> wcsncasecmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_ROS(1, 3) ATTR_ACCESS_ROS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsncasecmp)(char16_t const *s1, char16_t const *s2, size_t maxlen);
/* >> wcsncasecmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_ROS(1, 3) ATTR_ACCESS_ROS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcsncasecmp)(char32_t const *s1, char32_t const *s2, size_t maxlen);
/* >> wcscasecmp_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBDCALL libd_wcscasecmp_l)(char16_t const *s1, char16_t const *s2, locale_t locale);
/* >> wcscasecmp_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBKCALL libc_wcscasecmp_l)(char32_t const *s1, char32_t const *s2, locale_t locale);
/* >> wcsncasecmp_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBDCALL libd_wcsncasecmp_l)(char16_t const *s1, char16_t const *s2, size_t maxlen, locale_t locale);
/* >> wcsncasecmp_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBKCALL libc_wcsncasecmp_l)(char32_t const *s1, char32_t const *s2, size_t maxlen, locale_t locale);
/* >> wcscoll_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBDCALL libd_wcscoll_l)(char16_t const *s1, char16_t const *s2, locale_t locale);
/* >> wcscoll_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBKCALL libc_wcscoll_l)(char32_t const *s1, char32_t const *s2, locale_t locale);
/* >> wcsxfrm_l(3) */
INTDEF ATTR_ACCESS_ROS(2, 3) ATTR_ACCESS_WRS(1, 3) size_t NOTHROW_NCX(LIBDCALL libd_wcsxfrm_l)(char16_t *dst, char16_t const *__restrict src, size_t buflen, locale_t locale);
/* >> wcsxfrm_l(3) */
INTDEF ATTR_ACCESS_ROS(2, 3) ATTR_ACCESS_WRS(1, 3) size_t NOTHROW_NCX(LIBKCALL libc_wcsxfrm_l)(char32_t *dst, char32_t const *__restrict src, size_t buflen, locale_t locale);
/* >> wcpcpy(3) */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcpcpy)(char16_t *__restrict dst, char16_t const *__restrict src);
/* >> wcpcpy(3) */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcpcpy)(char32_t *__restrict dst, char32_t const *__restrict src);
/* >> wcpncpy(3) */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcpncpy)(char16_t *__restrict buf, char16_t const *__restrict src, size_t buflen);
/* >> wcpncpy(3) */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcpncpy)(char32_t *__restrict buf, char32_t const *__restrict src, size_t buflen);
/* >> mbsnrtowcs(3) */
INTDEF NONNULL((2)) size_t NOTHROW_NCX(LIBDCALL libd_mbsnrtowcs)(char16_t *__restrict dst, char const **__restrict psrc, size_t nmc, size_t dstlen, mbstate_t *mbs);
/* >> mbsnrtowcs(3) */
INTDEF NONNULL((2)) size_t NOTHROW_NCX(LIBKCALL libc_mbsnrtowcs)(char32_t *__restrict dst, char const **__restrict psrc, size_t nmc, size_t dstlen, mbstate_t *mbs);
/* >> wcsnrtombs(3) */
INTDEF NONNULL((2)) size_t NOTHROW_NCX(LIBDCALL libd_wcsnrtombs)(char *dst, char16_t const **__restrict psrc, size_t nwc, size_t dstlen, mbstate_t *mbs);
/* >> wcsnrtombs(3) */
INTDEF NONNULL((2)) size_t NOTHROW_NCX(LIBKCALL libc_wcsnrtombs)(char *dst, char32_t const **__restrict psrc, size_t nwc, size_t dstlen, mbstate_t *mbs);
/* >> wcsnlen(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_ROS(1, 2) NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcsnlen)(char16_t const *__restrict str, size_t maxlen);
/* >> wcsnlen(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_ROS(1, 2) NONNULL((1)) size_t NOTHROW_NCX(LIBKCALL libc_wcsnlen)(char32_t const *__restrict str, size_t maxlen);
/* >> wcsdup(3) */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ACCESS_RO(1) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsdup)(char16_t const *__restrict string);
/* >> wcsdup(3) */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ACCESS_RO(1) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsdup)(char32_t const *__restrict string);
/* >> wcwidth(3)
 * Returns the number of columns needed to display `ch' in a system terminal
 * When `ch' cannot be  displayed at all, `-1'  is returned (but `errno'  is
 * never modified by this function). Zero-width characters return `0'. */
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBDCALL libd_wcwidth)(char16_t ch);
/* >> wcwidth(3)
 * Returns the number of columns needed to display `ch' in a system terminal
 * When `ch' cannot be  displayed at all, `-1'  is returned (but `errno'  is
 * never modified by this function). Zero-width characters return `0'. */
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBKCALL libc_wcwidth)(char32_t ch);
/* >> wcswidth(3)
 * Returns the number of columns needed to display `str...+=wcslen(str, num_chars)'
 * in a system terminal. If any of the contained characters cannot be printed, then
 * `-1' is returned. (s.a. `wcwidth(3)') */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) __STDC_INT32_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd_wcswidth)(char16_t const *__restrict str, size_t num_chars);
/* >> wcswidth(3)
 * Returns the number of columns needed to display `str...+=wcslen(str, num_chars)'
 * in a system terminal. If any of the contained characters cannot be printed, then
 * `-1' is returned. (s.a. `wcwidth(3)') */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) __STDC_INT32_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc_wcswidth)(char32_t const *__restrict str, size_t num_chars);
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcschrnul)(char16_t const *haystack, char16_t needle);
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcschrnul)(char32_t const *haystack, char32_t needle);
/* >> wcstol_l(3) */
INTDEF NONNULL((1)) long NOTHROW_NCX(LIBDCALL libd_wcstol_l)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
/* >> wcstol_l(3) */
INTDEF NONNULL((1)) long NOTHROW_NCX(LIBKCALL libc_wcstol_l)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
/* >> wcstoul_l(3) */
INTDEF NONNULL((1)) unsigned long NOTHROW_NCX(LIBDCALL libd_wcstoul_l)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
/* >> wcstoul_l(3) */
INTDEF NONNULL((1)) unsigned long NOTHROW_NCX(LIBKCALL libc_wcstoul_l)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
/* >> wcstoll_l(3) */
INTDEF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBDCALL libd_wcstoll_l)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
/* >> wcstoll_l(3) */
INTDEF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBKCALL libc_wcstoll_l)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
/* >> wcstoull_l(3) */
INTDEF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBDCALL libd_wcstoull_l)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
/* >> wcstoull_l(3) */
INTDEF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBKCALL libc_wcstoull_l)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
/* >> wcstof_l(3) */
INTDEF NONNULL((1)) float NOTHROW_NCX(LIBDCALL libd_wcstof_l)(char16_t const *__restrict nptr, char16_t **endptr, locale_t locale);
/* >> wcstof_l(3) */
INTDEF NONNULL((1)) float NOTHROW_NCX(LIBKCALL libc_wcstof_l)(char32_t const *__restrict nptr, char32_t **endptr, locale_t locale);
/* >> wcstod_l(3) */
INTDEF NONNULL((1)) double NOTHROW_NCX(LIBDCALL libd_wcstod_l)(char16_t const *__restrict nptr, char16_t **endptr, locale_t locale);
/* >> wcstod_l(3) */
INTDEF NONNULL((1)) double NOTHROW_NCX(LIBKCALL libc_wcstod_l)(char32_t const *__restrict nptr, char32_t **endptr, locale_t locale);
/* >> wcstold_l(3) */
INTDEF NONNULL((1)) __LONGDOUBLE NOTHROW_NCX(LIBDCALL libd_wcstold_l)(char16_t const *__restrict nptr, char16_t **endptr, locale_t locale);
/* >> wcstold_l(3) */
INTDEF NONNULL((1)) __LONGDOUBLE NOTHROW_NCX(LIBKCALL libc_wcstold_l)(char32_t const *__restrict nptr, char32_t **endptr, locale_t locale);
/* >> getwchar(3), getwchar_unlocked(3) */
INTDEF wint16_t (LIBDCALL libd_getwchar_unlocked)(void) THROWS(...);
/* >> getwchar(3), getwchar_unlocked(3) */
INTDEF wint32_t (LIBKCALL libc_getwchar_unlocked)(void) THROWS(...);
/* >> putwchar(3), putwchar_unlocked(3) */
INTDEF wint16_t (LIBDCALL libd_putwchar_unlocked)(char16_t wc) THROWS(...);
/* >> putwchar(3), putwchar_unlocked(3) */
INTDEF wint32_t (LIBKCALL libc_putwchar_unlocked)(char32_t wc) THROWS(...);
/* >> fgetws(3), fgetws_unlocked(3) */
INTDEF ATTR_ACCESS_RW(3) NONNULL((1)) char16_t *(LIBDCALL libd_fgetws_unlocked)(char16_t *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) THROWS(...);
/* >> fgetws(3), fgetws_unlocked(3) */
INTDEF ATTR_ACCESS_RW(3) NONNULL((1)) char32_t *(LIBKCALL libc_fgetws_unlocked)(char32_t *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) THROWS(...);
/* >> fputws(3), fputws_unlocked(3) */
INTDEF ATTR_ACCESS_RW(2) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_fputws_unlocked)(char16_t const *__restrict str, FILE *__restrict stream) THROWS(...);
/* >> fputws(3), fputws_unlocked(3) */
INTDEF ATTR_ACCESS_RW(2) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_fputws_unlocked)(char32_t const *__restrict str, FILE *__restrict stream) THROWS(...);
/* >> wcsftime_l(3) */
INTDEF ATTR_LIBC_C16FTIME(3, 0) NONNULL((1, 3, 4)) size_t NOTHROW_NCX(LIBDCALL libd_wcsftime_l)(char16_t *__restrict buf, size_t maxsize, char16_t const *__restrict format, struct tm const *__restrict tp, locale_t locale);
/* >> wcsftime_l(3) */
INTDEF ATTR_LIBC_C32FTIME(3, 0) NONNULL((1, 3, 4)) size_t NOTHROW_NCX(LIBKCALL libc_wcsftime_l)(char32_t *__restrict buf, size_t maxsize, char32_t const *__restrict format, struct tm const *__restrict tp, locale_t locale);
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
INTDEF ATTR_ACCESS_RW(1) ATTR_LIBC_C16PRINTF(2, 0) NONNULL((2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vfwprintf_unlocked)(FILE *__restrict stream, char16_t const *__restrict format, va_list args) THROWS(...);
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
INTDEF ATTR_ACCESS_RW(1) ATTR_LIBC_C32PRINTF(2, 0) NONNULL((2)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_vfwprintf_unlocked)(FILE *__restrict stream, char32_t const *__restrict format, va_list args) THROWS(...);
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
INTDEF ATTR_ACCESS_RW(1) ATTR_LIBC_C16PRINTF(2, 3) NONNULL((2)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_fwprintf_unlocked)(FILE *__restrict stream, char16_t const *__restrict format, ...) THROWS(...);
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
INTDEF ATTR_ACCESS_RW(1) ATTR_LIBC_C32PRINTF(2, 3) NONNULL((2)) __STDC_INT_AS_SIZE_T (VLIBKCALL libc_fwprintf_unlocked)(FILE *__restrict stream, char32_t const *__restrict format, ...) THROWS(...);
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
INTDEF ATTR_LIBC_C16PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_wprintf_unlocked)(char16_t const *__restrict format, ...) THROWS(...);
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
INTDEF ATTR_LIBC_C32PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBKCALL libc_wprintf_unlocked)(char32_t const *__restrict format, ...) THROWS(...);
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
INTDEF ATTR_LIBC_C16PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vwprintf_unlocked)(char16_t const *__restrict format, va_list args) THROWS(...);
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
INTDEF ATTR_LIBC_C32PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_vwprintf_unlocked)(char32_t const *__restrict format, va_list args) THROWS(...);
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
INTDEF WUNUSED ATTR_ACCESS_RW(1) ATTR_LIBC_C16SCANF(2, 0) NONNULL((2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vfwscanf_unlocked)(FILE *__restrict stream, char16_t const *__restrict format, va_list args) THROWS(...);
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
INTDEF WUNUSED ATTR_ACCESS_RW(1) ATTR_LIBC_C32SCANF(2, 0) NONNULL((2)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_vfwscanf_unlocked)(FILE *__restrict stream, char32_t const *__restrict format, va_list args) THROWS(...);
/* >> vwscanf(3) */
INTDEF WUNUSED ATTR_LIBC_C16SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vwscanf_unlocked)(char16_t const *__restrict format, va_list args) THROWS(...);
/* >> vwscanf(3) */
INTDEF WUNUSED ATTR_LIBC_C32SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_vwscanf_unlocked)(char32_t const *__restrict format, va_list args) THROWS(...);
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
INTDEF WUNUSED ATTR_ACCESS_RW(1) ATTR_LIBC_C16SCANF(2, 3) NONNULL((2)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_fwscanf_unlocked)(FILE *__restrict stream, char16_t const *__restrict format, ...) THROWS(...);
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
INTDEF WUNUSED ATTR_ACCESS_RW(1) ATTR_LIBC_C32SCANF(2, 3) NONNULL((2)) __STDC_INT_AS_SIZE_T (VLIBKCALL libc_fwscanf_unlocked)(FILE *__restrict stream, char32_t const *__restrict format, ...) THROWS(...);
/* >> wscanf(3), vwscanf(3), wscanf_unlocked(3), vwscanf_unlocked(3) */
INTDEF WUNUSED ATTR_LIBC_C16SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_wscanf_unlocked)(char16_t const *__restrict format, ...) THROWS(...);
/* >> wscanf(3), vwscanf(3), wscanf_unlocked(3), vwscanf_unlocked(3) */
INTDEF WUNUSED ATTR_LIBC_C32SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBKCALL libc_wscanf_unlocked)(char32_t const *__restrict format, ...) THROWS(...);
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsend)(char16_t const *__restrict str);
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsend)(char32_t const *__restrict str);
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnend)(char16_t const *__restrict str, size_t maxlen);
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnend)(char32_t const *__restrict str, size_t maxlen);
/* >> wcsto32_r(3) */
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBDCALL libd_wcsto32_r)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
/* >> wcsto32_r(3) */
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBKCALL libc_wcsto32_r)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
/* >> wcstou32_r(3) */
INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBDCALL libd_wcstou32_r)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
/* >> wcstou32_r(3) */
INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBKCALL libc_wcstou32_r)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
/* >> wcsto32(3) */
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBDCALL libd_wcsto32)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base);
/* >> wcsto32(3) */
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBKCALL libc_wcsto32)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base);
/* >> wcstou32(3) */
INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBDCALL libd_wcstou32)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base);
/* >> wcstou32(3) */
INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBKCALL libc_wcstou32)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base);
/* >> wcsto64_r(3) */
INTDEF ATTR_LEAF NONNULL((1)) int64_t NOTHROW_NCX(LIBDCALL libd_wcsto64_r)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
/* >> wcsto64_r(3) */
INTDEF ATTR_LEAF NONNULL((1)) int64_t NOTHROW_NCX(LIBKCALL libc_wcsto64_r)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
/* >> wcstou64_r(3) */
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBDCALL libd_wcstou64_r)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
/* >> wcstou64_r(3) */
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBKCALL libc_wcstou64_r)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
/* >> wcstou64(3) */
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBDCALL libd_wcstou64)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base);
/* >> wcstou64(3) */
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBKCALL libc_wcstou64)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base);
/* >> wcsto64(3) */
INTDEF ATTR_LEAF NONNULL((1)) int64_t NOTHROW_NCX(LIBDCALL libd_wcsto64)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base);
/* >> wcsto64(3) */
INTDEF ATTR_LEAF NONNULL((1)) int64_t NOTHROW_NCX(LIBKCALL libc_wcsto64)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base);
/* >> wcsto32_l(3) */
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBDCALL libd_wcsto32_l)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
/* >> wcsto32_l(3) */
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBKCALL libc_wcsto32_l)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
/* >> wcstou32_l(3) */
INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBDCALL libd_wcstou32_l)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
/* >> wcstou32_l(3) */
INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBKCALL libc_wcstou32_l)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
/* >> wcsto64_l(3) */
INTDEF ATTR_LEAF NONNULL((1)) int64_t NOTHROW_NCX(LIBDCALL libd_wcsto64_l)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
/* >> wcsto64_l(3) */
INTDEF ATTR_LEAF NONNULL((1)) int64_t NOTHROW_NCX(LIBKCALL libc_wcsto64_l)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
/* >> wcstou64_l(3) */
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBDCALL libd_wcstou64_l)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
/* >> wcstou64_l(3) */
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBKCALL libc_wcstou64_l)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
/* >> wcsncoll(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_ROS(1, 3) ATTR_ACCESS_ROS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsncoll)(char16_t const *s1, char16_t const *s2, size_t maxlen);
/* >> wcsncoll(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_ROS(1, 3) ATTR_ACCESS_ROS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcsncoll)(char32_t const *s1, char32_t const *s2, size_t maxlen);
/* >> wcscasecoll(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBDCALL libd_wcscasecoll)(char16_t const *s1, char16_t const *s2);
/* >> wcscasecoll(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBKCALL libc_wcscasecoll)(char32_t const *s1, char32_t const *s2);
/* >> wcsncasecoll(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_ROS(1, 3) ATTR_ACCESS_ROS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsncasecoll)(char16_t const *s1, char16_t const *s2, size_t maxlen);
/* >> wcsncasecoll(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_ROS(1, 3) ATTR_ACCESS_ROS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcsncasecoll)(char32_t const *s1, char32_t const *s2, size_t maxlen);
/* >> wcsnrev(3) */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnrev)(char16_t *__restrict str, size_t maxlen);
/* >> wcsnrev(3) */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnrev)(char32_t *__restrict str, size_t maxlen);
/* >> wcsnlwr(3) */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_ACCESS_RWS(1, 2) NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnlwr)(char16_t *__restrict str, size_t maxlen);
/* >> wcsnlwr(3) */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_ACCESS_RWS(1, 2) NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnlwr)(char32_t *__restrict str, size_t maxlen);
/* >> wcsnupr(3) */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_ACCESS_RWS(1, 2) NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnupr)(char16_t *__restrict str, size_t maxlen);
/* >> wcsnupr(3) */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_ACCESS_RWS(1, 2) NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnupr)(char32_t *__restrict str, size_t maxlen);
/* >> wcscasestr(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcscasestr)(char16_t const *haystack, char16_t const *needle);
/* >> wcscasestr(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcscasestr)(char32_t const *haystack, char32_t const *needle);
/* >> wcspcpy(3)
 * Same as wcscpy, but return a pointer after the last written character */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcspcpy)(char16_t *__restrict buf, char16_t const *__restrict src);
/* >> wcspcpy(3)
 * Same as wcscpy, but return a pointer after the last written character */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcspcpy)(char32_t *__restrict buf, char32_t const *__restrict src);
/* >> wcspncpy(3)
 * Same as wcsncpy, but return a pointer after the last written character */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcspncpy)(char16_t *__restrict buf, char16_t const *__restrict src, size_t buflen);
/* >> wcspncpy(3)
 * Same as wcsncpy, but return a pointer after the last written character */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcspncpy)(char32_t *__restrict buf, char32_t const *__restrict src, size_t buflen);
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnchr)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnchr)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnrchr)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnrchr)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
/* >> wcssep(3) */
INTDEF ATTR_LEAF ATTR_ACCESS_RO(2) ATTR_ACCESS_RW(1) char16_t *NOTHROW_NCX(LIBDCALL libd_wcssep)(char16_t **__restrict stringp, char16_t const *__restrict delim);
/* >> wcssep(3) */
INTDEF ATTR_LEAF ATTR_ACCESS_RO(2) ATTR_ACCESS_RW(1) char32_t *NOTHROW_NCX(LIBKCALL libc_wcssep)(char32_t **__restrict stringp, char32_t const *__restrict delim);
/* >> wcsfry(3) */
INTDEF ATTR_LEAF ATTR_ACCESS_RW(1) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsfry)(char16_t *__restrict str);
/* >> wcsfry(3) */
INTDEF ATTR_LEAF ATTR_ACCESS_RW(1) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsfry)(char32_t *__restrict str);
/* >> wcsndup(3) */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ACCESS_ROS(1, 2) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsndup)(char16_t const *__restrict str, size_t max_chars);
/* >> wcsndup(3) */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ACCESS_ROS(1, 2) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsndup)(char32_t const *__restrict str, size_t max_chars);
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsrchrnul)(char16_t const *__restrict haystack, char16_t needle);
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsrchrnul)(char32_t const *__restrict haystack, char32_t needle);
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnchrnul)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnchrnul)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnrchrnul)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnrchrnul)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
/* >> wcsoff(3)
 * Same as `wcschrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcsoff)(char16_t const *__restrict haystack, char16_t needle);
/* >> wcsoff(3)
 * Same as `wcschrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBKCALL libc_wcsoff)(char32_t const *__restrict haystack, char32_t needle);
/* >> wcsroff(3)
 * Same as `wcsrchrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcsroff)(char16_t const *__restrict haystack, char16_t needle);
/* >> wcsroff(3)
 * Same as `wcsrchrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBKCALL libc_wcsroff)(char32_t const *__restrict haystack, char32_t needle);
/* >> wcsnoff(3)
 * Same as `wcsnchrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcsnoff)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
/* >> wcsnoff(3)
 * Same as `wcsnchrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBKCALL libc_wcsnoff)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
/* >> wcsnroff(3)
 * Same as `wcsnrchrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcsnroff)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
/* >> wcsnroff(3)
 * Same as `wcsnrchrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBKCALL libc_wcsnroff)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
/* >> fuzzy_wcscmp(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wcscmp)(char16_t const *s1, char16_t const *s2);
/* >> fuzzy_wcscmp(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBKCALL libc_fuzzy_wcscmp)(char32_t const *s1, char32_t const *s2);
/* >> fuzzy_wcsncmp(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wcsncmp)(char16_t const *s1, size_t s1_maxlen, char16_t const *s2, size_t s2_maxlen);
/* >> fuzzy_wcsncmp(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBKCALL libc_fuzzy_wcsncmp)(char32_t const *s1, size_t s1_maxlen, char32_t const *s2, size_t s2_maxlen);
/* >> fuzzy_wmemcasecmp(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wmemcasecmp)(char16_t const *s1, size_t s1_bytes, char16_t const *s2, size_t s2_bytes);
/* >> fuzzy_wmemcasecmp(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBKCALL libc_fuzzy_wmemcasecmp)(char32_t const *s1, size_t s1_bytes, char32_t const *s2, size_t s2_bytes);
/* >> fuzzy_wcscasecmp(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wcscasecmp)(char16_t const *s1, char16_t const *s2);
/* >> fuzzy_wcscasecmp(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBKCALL libc_fuzzy_wcscasecmp)(char32_t const *s1, char32_t const *s2);
/* >> fuzzy_wcsncasecmp(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wcsncasecmp)(char16_t const *s1, size_t s1_maxlen, char16_t const *s2, size_t s2_maxlen);
/* >> fuzzy_wcsncasecmp(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBKCALL libc_fuzzy_wcsncasecmp)(char32_t const *s1, size_t s1_maxlen, char32_t const *s2, size_t s2_maxlen);
/* >> wildwcscmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBDCALL libd_wildwcscmp)(char16_t const *pattern, char16_t const *string);
/* >> wildwcscmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBKCALL libc_wildwcscmp)(char32_t const *pattern, char32_t const *string);
/* >> wildwcscasecmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBDCALL libd_wildwcscasecmp)(char16_t const *pattern, char16_t const *string);
/* >> wildwcscasecmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBKCALL libc_wildwcscasecmp)(char32_t const *pattern, char32_t const *string);
/* >> wcsverscmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBDCALL libd_wcsverscmp)(char16_t const *s1, char16_t const *s2);
/* >> wcsverscmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBKCALL libc_wcsverscmp)(char32_t const *s1, char32_t const *s2);
/* >> wcsncoll_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_ROS(1, 3) ATTR_ACCESS_ROS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsncoll_l)(char16_t const *s1, char16_t const *s2, size_t maxlen, locale_t locale);
/* >> wcsncoll_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_ROS(1, 3) ATTR_ACCESS_ROS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcsncoll_l)(char32_t const *s1, char32_t const *s2, size_t maxlen, locale_t locale);
/* >> wcscasecoll_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBDCALL libd_wcscasecoll_l)(char16_t const *s1, char16_t const *s2, locale_t locale);
/* >> wcscasecoll_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBKCALL libc_wcscasecoll_l)(char32_t const *s1, char32_t const *s2, locale_t locale);
/* >> wcsncasecoll_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_ROS(1, 3) ATTR_ACCESS_ROS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsncasecoll_l)(char16_t const *s1, char16_t const *s2, size_t maxlen, locale_t locale);
/* >> wcsncasecoll_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_ROS(1, 3) ATTR_ACCESS_ROS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcsncasecoll_l)(char32_t const *s1, char32_t const *s2, size_t maxlen, locale_t locale);
/* >> wcslwr_l(3) */
INTDEF ATTR_LEAF ATTR_ACCESS_RW(1) char16_t *NOTHROW_NCX(LIBDCALL libd_wcslwr_l)(char16_t *__restrict str, locale_t locale);
/* >> wcslwr_l(3) */
INTDEF ATTR_LEAF ATTR_ACCESS_RW(1) char32_t *NOTHROW_NCX(LIBKCALL libc_wcslwr_l)(char32_t *__restrict str, locale_t locale);
/* >> wcsupr_l(3) */
INTDEF ATTR_LEAF ATTR_ACCESS_RW(1) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsupr_l)(char16_t *__restrict str, locale_t locale);
/* >> wcsupr_l(3) */
INTDEF ATTR_LEAF ATTR_ACCESS_RW(1) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsupr_l)(char32_t *__restrict str, locale_t locale);
/* >> wcsnlwr_l(3) */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_ACCESS_RWS(1, 2) NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnlwr_l)(char16_t *__restrict str, size_t maxlen, locale_t locale);
/* >> wcsnlwr_l(3) */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_ACCESS_RWS(1, 2) NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnlwr_l)(char32_t *__restrict str, size_t maxlen, locale_t locale);
/* >> wcsnupr_l(3) */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_ACCESS_RWS(1, 2) NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnupr_l)(char16_t *__restrict str, size_t maxlen, locale_t locale);
/* >> wcsnupr_l(3) */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_ACCESS_RWS(1, 2) NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnupr_l)(char32_t *__restrict str, size_t maxlen, locale_t locale);
/* >> wcscasestr_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) char16_t *NOTHROW_NCX(LIBDCALL libd_wcscasestr_l)(char16_t const *haystack, char16_t const *needle, locale_t locale);
/* >> wcscasestr_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) char32_t *NOTHROW_NCX(LIBKCALL libc_wcscasestr_l)(char32_t const *haystack, char32_t const *needle, locale_t locale);
/* >> fuzzy_wmemcasecmp_l(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wmemcasecmp_l)(char16_t const *s1, size_t s1_bytes, char16_t const *s2, size_t s2_bytes, locale_t locale);
/* >> fuzzy_wmemcasecmp_l(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBKCALL libc_fuzzy_wmemcasecmp_l)(char32_t const *s1, size_t s1_bytes, char32_t const *s2, size_t s2_bytes, locale_t locale);
/* >> fuzzy_wcscasecmp_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wcscasecmp_l)(char16_t const *s1, char16_t const *s2, locale_t locale);
/* >> fuzzy_wcscasecmp_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) size_t NOTHROW_NCX(LIBKCALL libc_fuzzy_wcscasecmp_l)(char32_t const *s1, char32_t const *s2, locale_t locale);
/* >> fuzzy_wcsncasecmp_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_ROS(1, 2) ATTR_ACCESS_ROS(3, 4) NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wcsncasecmp_l)(char16_t const *s1, size_t s1_maxlen, char16_t const *s2, size_t s2_maxlen, locale_t locale);
/* >> fuzzy_wcsncasecmp_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_ROS(1, 2) ATTR_ACCESS_ROS(3, 4) NONNULL((1, 3)) size_t NOTHROW_NCX(LIBKCALL libc_fuzzy_wcsncasecmp_l)(char32_t const *s1, size_t s1_maxlen, char32_t const *s2, size_t s2_maxlen, locale_t locale);
/* >> wildwcscasecmp_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBDCALL libd_wildwcscasecmp_l)(char16_t const *pattern, char16_t const *string, locale_t locale);
/* >> wildwcscasecmp_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBKCALL libc_wildwcscasecmp_l)(char32_t const *pattern, char32_t const *string, locale_t locale);
/* >> wcslcat(3) */
INTDEF ATTR_LEAF ATTR_ACCESS_RO(2) ATTR_ACCESS_RWS(1, 3) NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcslcat)(char16_t *__restrict dst, char16_t const *__restrict src, size_t bufsize);
/* >> wcslcat(3) */
INTDEF ATTR_LEAF ATTR_ACCESS_RO(2) ATTR_ACCESS_RWS(1, 3) NONNULL((1)) size_t NOTHROW_NCX(LIBKCALL libc_wcslcat)(char32_t *__restrict dst, char32_t const *__restrict src, size_t bufsize);
/* >> wcslcpy(3) */
INTDEF ATTR_LEAF ATTR_ACCESS_RO(2) ATTR_ACCESS_WRS(1, 3) NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcslcpy)(char16_t *__restrict dst, char16_t const *__restrict src, size_t bufsize);
/* >> wcslcpy(3) */
INTDEF ATTR_LEAF ATTR_ACCESS_RO(2) ATTR_ACCESS_WRS(1, 3) NONNULL((1)) size_t NOTHROW_NCX(LIBKCALL libc_wcslcpy)(char32_t *__restrict dst, char32_t const *__restrict src, size_t bufsize);
/* >> wcsnset(3) */
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnset)(char16_t *__restrict str, char16_t ch, size_t maxlen);
/* >> wcsnset(3) */
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnset)(char32_t *__restrict str, char32_t ch, size_t maxlen);
/* >> wcsrev(3) */
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsrev)(char16_t *__restrict str);
/* >> wcsrev(3) */
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsrev)(char32_t *__restrict str);
/* >> wcsset(3) */
INTDEF ATTR_LEAF ATTR_ACCESS_RW(1) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsset)(char16_t *__restrict str, int ch);
/* >> wcsset(3) */
INTDEF ATTR_LEAF ATTR_ACCESS_RW(1) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsset)(char32_t *__restrict str, int ch);
/* >> wcslwr(3) */
INTDEF ATTR_ACCESS_RW(1) char16_t *NOTHROW_NCX(LIBDCALL libd_wcslwr)(char16_t *__restrict str);
/* >> wcslwr(3) */
INTDEF ATTR_ACCESS_RW(1) char32_t *NOTHROW_NCX(LIBKCALL libc_wcslwr)(char32_t *__restrict str);
/* >> wcsupr(3) */
INTDEF ATTR_ACCESS_RW(1) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsupr)(char16_t *__restrict str);
/* >> wcsupr(3) */
INTDEF ATTR_ACCESS_RW(1) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsupr)(char32_t *__restrict str);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_WCHAR_H */
