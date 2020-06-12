/* HASH CRC-32:0x91fa448b */
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
#ifndef GUARD_LIBC_AUTO_WCHAR_H
#define GUARD_LIBC_AUTO_WCHAR_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <wchar.h>

DECL_BEGIN

#ifndef __errno_t_defined
#define __errno_t_defined 1
typedef int errno_t;
#endif /* !__errno_t_defined */
#ifndef __rsize_t_defined
#define __rsize_t_defined 1
typedef size_t rsize_t;
#endif /* !__rsize_t_defined */

#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED wint_t NOTHROW_NCX(LIBDCALL libd_btowc)(int ch);
INTDEF ATTR_CONST WUNUSED wint_t NOTHROW_NCX(LIBKCALL libc_btowc)(int ch);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc_wctob)(wint_t ch);
INTDEF size_t NOTHROW_NCX(LIBDCALL libd_mbrtowc)(char16_t *pwc, char const *__restrict str, size_t maxlen, mbstate_t *mbs);
INTDEF size_t NOTHROW_NCX(LIBKCALL libc_mbrtowc)(char32_t *pwc, char const *__restrict str, size_t maxlen, mbstate_t *mbs);
INTDEF size_t NOTHROW_NCX(LIBDCALL libd_wcrtomb)(char *__restrict str, char16_t wc, mbstate_t *mbs);
INTDEF size_t NOTHROW_NCX(LIBKCALL libc_wcrtomb)(char *__restrict str, char32_t wc, mbstate_t *mbs);
INTDEF WUNUSED size_t NOTHROW_NCX(LIBDCALL libd_mbrlen)(char const *__restrict str, size_t maxlen, mbstate_t *mbs);
INTDEF WUNUSED size_t NOTHROW_NCX(LIBKCALL libc_mbrlen)(char const *__restrict str, size_t maxlen, mbstate_t *mbs);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_mbsrtowcs)(char16_t *__restrict dst, char const **__restrict psrc, size_t dstlen, mbstate_t *mbs);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBKCALL libc_mbsrtowcs)(char32_t *__restrict dst, char const **__restrict psrc, size_t dstlen, mbstate_t *mbs);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_wcsrtombs)(char *dst, char16_t const **__restrict psrc, size_t dstlen, mbstate_t *mbs);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBKCALL libc_wcsrtombs)(char *dst, char32_t const **__restrict psrc, size_t dstlen, mbstate_t *mbs);
INTDEF NONNULL((1)) long NOTHROW_NCX(LIBDCALL libd_wcstol)(char16_t const *__restrict nptr, char16_t **endptr, int base);
INTDEF NONNULL((1)) long NOTHROW_NCX(LIBKCALL libc_wcstol)(char32_t const *__restrict nptr, char32_t **endptr, int base);
INTDEF NONNULL((1)) unsigned long NOTHROW_NCX(LIBDCALL libd_wcstoul)(char16_t const *__restrict nptr, char16_t **endptr, int base);
INTDEF NONNULL((1)) unsigned long NOTHROW_NCX(LIBKCALL libc_wcstoul)(char32_t const *__restrict nptr, char32_t **endptr, int base);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_mbsinit)(mbstate_t const *mbs);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wmemcmp)(char16_t const *s1, char16_t const *s2, size_t num_chars);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wmemcmp)(char32_t const *s1, char32_t const *s2, size_t num_chars);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wmemcpy)(char16_t *__restrict dst, char16_t const *__restrict src, size_t num_chars);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wmemcpy)(char32_t *__restrict dst, char32_t const *__restrict src, size_t num_chars);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wmemmove)(char16_t *dst, char16_t const *src, size_t num_chars);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wmemmove)(char32_t *dst, char32_t const *src, size_t num_chars);
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wmemset)(char16_t *dst, char16_t filler, size_t num_chars);
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wmemset)(char32_t *dst, char32_t filler, size_t num_chars);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcscpy)(char16_t *__restrict buf, char16_t const *__restrict src);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcscpy)(char32_t *__restrict buf, char32_t const *__restrict src);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcscat)(char16_t *__restrict buf, char16_t const *__restrict src);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcscat)(char32_t *__restrict buf, char32_t const *__restrict src);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsncat)(char16_t *__restrict buf, char16_t const *__restrict src, size_t buflen);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsncat)(char32_t *__restrict buf, char32_t const *__restrict src, size_t buflen);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsncpy)(char16_t *__restrict buf, char16_t const *__restrict src, size_t buflen);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsncpy)(char32_t *__restrict buf, char32_t const *__restrict src, size_t buflen);
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcscmp)(char16_t const *s1, char16_t const *s2);
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcscmp)(char32_t const *s1, char32_t const *s2);
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsncmp)(char16_t const *s1, char16_t const *s2, size_t maxlen);
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcsncmp)(char32_t const *s1, char32_t const *s2, size_t maxlen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcscoll)(char16_t const *s1, char16_t const *s2);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcscoll)(char32_t const *s1, char32_t const *s2);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_wcsxfrm)(char16_t *dst, char16_t const *__restrict src, size_t maxlen);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBKCALL libc_wcsxfrm)(char32_t *dst, char32_t const *__restrict src, size_t maxlen);
INTDEF wint_t (LIBDCALL libd_getwchar)(void) THROWS(...);
INTDEF wint_t (LIBKCALL libc_getwchar)(void) THROWS(...);
INTDEF wint_t (LIBDCALL libd_putwchar)(char16_t wc) THROWS(...);
INTDEF wint_t (LIBKCALL libc_putwchar)(char32_t wc) THROWS(...);
INTDEF WUNUSED NONNULL((1, 3)) char16_t *(LIBDCALL libd_fgetws)(char16_t *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) THROWS(...);
INTDEF WUNUSED NONNULL((1, 3)) char32_t *(LIBKCALL libc_fgetws)(char32_t *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_fputws)(char16_t const *__restrict string, FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_fputws)(char32_t const *__restrict string, FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1, 3, 4)) size_t NOTHROW_NCX(LIBDCALL libd_wcsftime)(char16_t *__restrict buf, size_t buflen, char16_t const *__restrict format, struct tm const *__restrict tp);
INTDEF NONNULL((1, 3, 4)) size_t NOTHROW_NCX(LIBKCALL libc_wcsftime)(char32_t *__restrict buf, size_t buflen, char32_t const *__restrict format, struct tm const *__restrict tp);
INTDEF NONNULL((2, 3)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcstok_s)(char16_t *string, char16_t const *__restrict delim, char16_t **__restrict save_ptr);
INTDEF NONNULL((2, 3)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcstok)(char32_t *string, char32_t const *__restrict delim, char32_t **__restrict save_ptr);
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcslen)(char16_t const *__restrict string);
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBKCALL libc_wcslen)(char32_t const *__restrict string);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_wcsspn)(char16_t const *haystack, char16_t const *accept);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBKCALL libc_wcsspn)(char32_t const *haystack, char32_t const *accept);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_wcscspn)(char16_t const *haystack, char16_t const *reject);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBKCALL libc_wcscspn)(char32_t const *haystack, char32_t const *reject);
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcschr)(char16_t const *__restrict haystack, char16_t needle);
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcschr)(char32_t const *__restrict haystack, char32_t needle);
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsrchr)(char16_t const *__restrict haystack, char16_t needle);
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsrchr)(char32_t const *__restrict haystack, char32_t needle);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcspbrk)(char16_t const *haystack, char16_t const *accept);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcspbrk)(char32_t const *haystack, char32_t const *accept);
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsstr)(char16_t const *haystack, char16_t const *needle);
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsstr)(char32_t const *haystack, char32_t const *needle);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_fwide)(FILE *fp, int mode);
INTDEF ATTR_LIBC_WPRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_fwprintf)(FILE *__restrict stream, char16_t const *__restrict format, ...) THROWS(...);
INTDEF ATTR_LIBC_WPRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBKCALL libc_fwprintf)(FILE *__restrict stream, char32_t const *__restrict format, ...) THROWS(...);
INTDEF ATTR_LIBC_WPRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vfwprintf)(FILE *__restrict stream, char16_t const *__restrict format, va_list args) THROWS(...);
INTDEF ATTR_LIBC_WPRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_vfwprintf)(FILE *__restrict stream, char32_t const *__restrict format, va_list args) THROWS(...);
INTDEF ATTR_LIBC_WPRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_wprintf)(char16_t const *__restrict format, ...) THROWS(...);
INTDEF ATTR_LIBC_WPRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBKCALL libc_wprintf)(char32_t const *__restrict format, ...) THROWS(...);
INTDEF ATTR_LIBC_WPRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vwprintf)(char16_t const *__restrict format, va_list args) THROWS(...);
INTDEF ATTR_LIBC_WPRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_vwprintf)(char32_t const *__restrict format, va_list args) THROWS(...);
INTDEF ATTR_LIBC_WSCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_fwscanf)(FILE *__restrict stream, char16_t const *__restrict format, ...) THROWS(...);
INTDEF ATTR_LIBC_WSCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBKCALL libc_fwscanf)(FILE *__restrict stream, char32_t const *__restrict format, ...) THROWS(...);
INTDEF ATTR_LIBC_WSCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_wscanf)(char16_t const *__restrict format, ...) THROWS(...);
INTDEF ATTR_LIBC_WSCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBKCALL libc_wscanf)(char32_t const *__restrict format, ...) THROWS(...);
INTDEF ATTR_LIBC_WSCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd_swscanf)(char16_t const *__restrict src, char16_t const *__restrict format, ...);
INTDEF ATTR_LIBC_WSCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBKCALL libc_swscanf)(char32_t const *__restrict src, char32_t const *__restrict format, ...);
INTDEF ATTR_LIBC_WPRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd_vswprintf)(char16_t *__restrict buf, size_t buflen, char16_t const *__restrict format, va_list args);
INTDEF ATTR_LIBC_WPRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBKCALL libc_vswprintf)(char32_t *__restrict buf, size_t buflen, char32_t const *__restrict format, va_list args);
INTDEF ATTR_LIBC_WPRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd_swprintf)(char16_t *__restrict buf, size_t buflen, char16_t const *__restrict format, ...);
INTDEF ATTR_LIBC_WPRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBKCALL libc_swprintf)(char32_t *__restrict buf, size_t buflen, char32_t const *__restrict format, ...);
INTDEF NONNULL((1)) double NOTHROW_NCX(LIBDCALL libd_wcstod)(char16_t const *__restrict nptr, char16_t **endptr);
INTDEF NONNULL((1)) double NOTHROW_NCX(LIBKCALL libc_wcstod)(char32_t const *__restrict nptr, char32_t **endptr);
INTDEF ATTR_PURE NONNULL((1)) float NOTHROW_NCX(LIBDCALL libd_wcstof)(char16_t const *__restrict nptr, char16_t **endptr);
INTDEF ATTR_PURE NONNULL((1)) float NOTHROW_NCX(LIBKCALL libc_wcstof)(char32_t const *__restrict nptr, char32_t **endptr);
INTDEF ATTR_PURE NONNULL((1)) __LONGDOUBLE NOTHROW_NCX(LIBDCALL libd_wcstold)(char16_t const *__restrict nptr, char16_t **endptr);
INTDEF ATTR_PURE NONNULL((1)) __LONGDOUBLE NOTHROW_NCX(LIBKCALL libc_wcstold)(char32_t const *__restrict nptr, char32_t **endptr);
INTDEF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBDCALL libd_wcstoll)(char16_t const *__restrict nptr, char16_t **endptr, int base);
INTDEF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBKCALL libc_wcstoll)(char32_t const *__restrict nptr, char32_t **endptr, int base);
INTDEF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBDCALL libd_wcstoull)(char16_t const *__restrict nptr, char16_t **endptr, int base);
INTDEF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBKCALL libc_wcstoull)(char32_t const *__restrict nptr, char32_t **endptr, int base);
INTDEF WUNUSED ATTR_LIBC_WSCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vwscanf)(char16_t const *__restrict format, va_list args) THROWS(...);
INTDEF WUNUSED ATTR_LIBC_WSCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_vwscanf)(char32_t const *__restrict format, va_list args) THROWS(...);
INTDEF WUNUSED ATTR_LIBC_WSCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd_vswscanf)(char16_t const *__restrict src, char16_t const *__restrict format, va_list args);
INTDEF WUNUSED ATTR_LIBC_WSCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBKCALL libc_vswscanf)(char32_t const *__restrict src, char32_t const *__restrict format, va_list args);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcscasecmp)(char16_t const *s1, char16_t const *s2);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcscasecmp)(char32_t const *s1, char32_t const *s2);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsncasecmp)(char16_t const *s1, char16_t const *s2, size_t maxlen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcsncasecmp)(char32_t const *s1, char32_t const *s2, size_t maxlen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcscasecmp_l)(char16_t const *s1, char16_t const *s2, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcscasecmp_l)(char32_t const *s1, char32_t const *s2, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsncasecmp_l)(char16_t const *s1, char16_t const *s2, size_t maxlen, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcsncasecmp_l)(char32_t const *s1, char32_t const *s2, size_t maxlen, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcscoll_l)(char16_t const *s1, char16_t const *s2, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcscoll_l)(char32_t const *s1, char32_t const *s2, locale_t locale);
INTDEF NONNULL((2)) size_t NOTHROW_NCX(LIBDCALL libd_wcsxfrm_l)(char16_t *dst, char16_t const *__restrict src, size_t maxlen, locale_t locale);
INTDEF NONNULL((2)) size_t NOTHROW_NCX(LIBKCALL libc_wcsxfrm_l)(char32_t *dst, char32_t const *__restrict src, size_t maxlen, locale_t locale);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcpcpy)(char16_t *__restrict dst, char16_t const *__restrict src);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcpcpy)(char32_t *__restrict dst, char32_t const *__restrict src);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcpncpy)(char16_t *__restrict buf, char16_t const *__restrict src, size_t buflen);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcpncpy)(char32_t *__restrict buf, char32_t const *__restrict src, size_t buflen);
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcsnlen)(char16_t const *__restrict string, size_t maxlen);
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBKCALL libc_wcsnlen)(char32_t const *__restrict string, size_t maxlen);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd__wcsdup)(char16_t const *__restrict string);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsdup)(char32_t const *__restrict string);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBDCALL libd_wcwidth)(char16_t ch);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBKCALL libc_wcwidth)(char32_t ch);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_wcswidth)(char16_t const *__restrict string, size_t num_chars);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBKCALL libc_wcswidth)(char32_t const *__restrict string, size_t num_chars);
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcschrnul)(char16_t const *haystack, char16_t needle);
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcschrnul)(char32_t const *haystack, char32_t needle);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wmempcpy)(char16_t *__restrict dst, char16_t const *__restrict src, size_t num_chars);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wmempcpy)(char32_t *__restrict dst, char32_t const *__restrict src, size_t num_chars);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wmempmove)(char16_t *dst, char16_t const *src, size_t num_chars);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wmempmove)(char32_t *dst, char32_t const *src, size_t num_chars);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) long NOTHROW_NCX(LIBDCALL libd_wcstol_l)(char16_t const *__restrict nptr, char16_t **endptr, int base, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) long NOTHROW_NCX(LIBKCALL libc_wcstol_l)(char32_t const *__restrict nptr, char32_t **endptr, int base, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) unsigned long NOTHROW_NCX(LIBDCALL libd_wcstoul_l)(char16_t const *__restrict nptr, char16_t **endptr, int base, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) unsigned long NOTHROW_NCX(LIBKCALL libc_wcstoul_l)(char32_t const *__restrict nptr, char32_t **endptr, int base, locale_t locale);
INTDEF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBDCALL libd_wcstoll_l)(char16_t const *__restrict nptr, char16_t **endptr, int base, locale_t locale);
INTDEF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBKCALL libc_wcstoll_l)(char32_t const *__restrict nptr, char32_t **endptr, int base, locale_t locale);
INTDEF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBDCALL libd_wcstoull_l)(char16_t const *__restrict nptr, char16_t **endptr, int base, locale_t locale);
INTDEF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBKCALL libc_wcstoull_l)(char32_t const *__restrict nptr, char32_t **endptr, int base, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) float NOTHROW_NCX(LIBDCALL libd_wcstof_l)(char16_t const *__restrict nptr, char16_t **endptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) float NOTHROW_NCX(LIBKCALL libc_wcstof_l)(char32_t const *__restrict nptr, char32_t **endptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) double NOTHROW_NCX(LIBDCALL libd_wcstod_l)(char16_t const *__restrict nptr, char16_t **endptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) double NOTHROW_NCX(LIBKCALL libc_wcstod_l)(char32_t const *__restrict nptr, char32_t **endptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) __LONGDOUBLE NOTHROW_NCX(LIBDCALL libd_wcstold_l)(char16_t const *__restrict nptr, char16_t **endptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) __LONGDOUBLE NOTHROW_NCX(LIBKCALL libc_wcstold_l)(char32_t const *__restrict nptr, char32_t **endptr, locale_t locale);
INTDEF wint_t (LIBDCALL libd_getwchar_unlocked)(void) THROWS(...);
INTDEF wint_t (LIBKCALL libc_getwchar_unlocked)(void) THROWS(...);
INTDEF wint_t (LIBDCALL libd_putwchar_unlocked)(char16_t wc) THROWS(...);
INTDEF wint_t (LIBKCALL libc_putwchar_unlocked)(char32_t wc) THROWS(...);
INTDEF NONNULL((1, 3)) char16_t *(LIBDCALL libd__fgetws_nolock)(char16_t *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1, 3)) char32_t *(LIBKCALL libc_fgetws_unlocked)(char32_t *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd__fputws_nolock)(char16_t const *__restrict string, FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_fputws_unlocked)(char32_t const *__restrict string, FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1, 3, 4)) size_t NOTHROW_NCX(LIBDCALL libd_wcsftime_l)(char16_t *__restrict buf, size_t maxsize, char16_t const *__restrict format, __STRUCT_TM const *__restrict tp, locale_t locale);
INTDEF NONNULL((1, 3, 4)) size_t NOTHROW_NCX(LIBKCALL libc_wcsftime_l)(char32_t *__restrict buf, size_t maxsize, char32_t const *__restrict format, __STRUCT_TM const *__restrict tp, locale_t locale);
INTDEF ATTR_LIBC_WPRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vfwprintf_unlocked)(FILE *__restrict stream, char16_t const *__restrict format, va_list args) THROWS(...);
INTDEF ATTR_LIBC_WPRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_vfwprintf_unlocked)(FILE *__restrict stream, char32_t const *__restrict format, va_list args) THROWS(...);
INTDEF ATTR_LIBC_WPRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_fwprintf_unlocked)(FILE *__restrict stream, char16_t const *__restrict format, ...) THROWS(...);
INTDEF ATTR_LIBC_WPRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBKCALL libc_fwprintf_unlocked)(FILE *__restrict stream, char32_t const *__restrict format, ...) THROWS(...);
INTDEF ATTR_LIBC_WPRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_wprintf_unlocked)(char16_t const *__restrict format, ...) THROWS(...);
INTDEF ATTR_LIBC_WPRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBKCALL libc_wprintf_unlocked)(char32_t const *__restrict format, ...) THROWS(...);
INTDEF ATTR_LIBC_WPRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vwprintf_unlocked)(char16_t const *__restrict format, va_list args) THROWS(...);
INTDEF ATTR_LIBC_WPRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_vwprintf_unlocked)(char32_t const *__restrict format, va_list args) THROWS(...);
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vwscanf_unlocked)(char16_t const *__restrict format, va_list args) THROWS(...);
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_vwscanf_unlocked)(char32_t const *__restrict format, va_list args) THROWS(...);
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_fwscanf_unlocked)(FILE *__restrict stream, char16_t const *__restrict format, ...) THROWS(...);
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (VLIBKCALL libc_fwscanf_unlocked)(FILE *__restrict stream, char32_t const *__restrict format, ...) THROWS(...);
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBDCALL libd_wscanf_unlocked)(char16_t const *__restrict format, ...) THROWS(...);
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T (VLIBKCALL libc_wscanf_unlocked)(char32_t const *__restrict format, ...) THROWS(...);
/* Same as `STR+wcslen(STR)' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsend)(char16_t const *__restrict string);
/* Same as `STR+wcslen(STR)' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsend)(char32_t const *__restrict string);
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnend)(char16_t const *__restrict string, size_t maxlen);
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnend)(char32_t const *__restrict string, size_t maxlen);
INTDEF ATTR_LEAF WUNUSED NONNULL((1)) int32_t NOTHROW_NCX(LIBDCALL libd_wcsto32)(char16_t const *__restrict nptr, char16_t **endptr, int base);
INTDEF ATTR_LEAF WUNUSED NONNULL((1)) int32_t NOTHROW_NCX(LIBKCALL libc_wcsto32)(char32_t const *__restrict nptr, char32_t **endptr, int base);
INTDEF ATTR_LEAF WUNUSED NONNULL((1)) uint32_t NOTHROW_NCX(LIBDCALL libd_wcstou32)(char16_t const *__restrict nptr, char16_t **endptr, int base);
INTDEF ATTR_LEAF WUNUSED NONNULL((1)) uint32_t NOTHROW_NCX(LIBKCALL libc_wcstou32)(char32_t const *__restrict nptr, char32_t **endptr, int base);
INTDEF ATTR_LEAF WUNUSED NONNULL((1)) uint64_t NOTHROW_NCX(LIBDCALL libd__wcstoui64)(char16_t const *__restrict nptr, char16_t **endptr, int base);
INTDEF ATTR_LEAF WUNUSED NONNULL((1)) uint64_t NOTHROW_NCX(LIBKCALL libc_wcstou64)(char32_t const *__restrict nptr, char32_t **endptr, int base);
INTDEF ATTR_LEAF WUNUSED NONNULL((1)) int64_t NOTHROW_NCX(LIBDCALL libd__wcstoi64)(char16_t const *__restrict nptr, char16_t **endptr, int base);
INTDEF ATTR_LEAF WUNUSED NONNULL((1)) int64_t NOTHROW_NCX(LIBKCALL libc_wcsto64)(char32_t const *__restrict nptr, char32_t **endptr, int base);
INTDEF ATTR_LEAF WUNUSED NONNULL((1)) int32_t NOTHROW_NCX(LIBDCALL libd_wcsto32_l)(char16_t const *__restrict nptr, char16_t **endptr, int base, locale_t locale);
INTDEF ATTR_LEAF WUNUSED NONNULL((1)) int32_t NOTHROW_NCX(LIBKCALL libc_wcsto32_l)(char32_t const *__restrict nptr, char32_t **endptr, int base, locale_t locale);
INTDEF ATTR_LEAF WUNUSED NONNULL((1)) uint32_t NOTHROW_NCX(LIBDCALL libd_wcstou32_l)(char16_t const *__restrict nptr, char16_t **endptr, int base, locale_t locale);
INTDEF ATTR_LEAF WUNUSED NONNULL((1)) uint32_t NOTHROW_NCX(LIBKCALL libc_wcstou32_l)(char32_t const *__restrict nptr, char32_t **endptr, int base, locale_t locale);
INTDEF ATTR_LEAF WUNUSED NONNULL((1)) int64_t NOTHROW_NCX(LIBDCALL libd__wcstoi64_l)(char16_t const *__restrict nptr, char16_t **endptr, int base, locale_t locale);
INTDEF ATTR_LEAF WUNUSED NONNULL((1)) int64_t NOTHROW_NCX(LIBKCALL libc_wcsto64_l)(char32_t const *__restrict nptr, char32_t **endptr, int base, locale_t locale);
INTDEF ATTR_LEAF WUNUSED NONNULL((1)) uint64_t NOTHROW_NCX(LIBDCALL libd__wcstoui64_l)(char16_t const *__restrict nptr, char16_t **endptr, int base, locale_t locale);
INTDEF ATTR_LEAF WUNUSED NONNULL((1)) uint64_t NOTHROW_NCX(LIBKCALL libc_wcstou64_l)(char32_t const *__restrict nptr, char32_t **endptr, int base, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__wcsncoll)(char16_t const *s1, char16_t const *s2, size_t maxlen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcsncoll)(char32_t const *s1, char32_t const *s2, size_t maxlen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__wcsicoll)(char16_t const *s1, char16_t const *s2);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcscasecoll)(char32_t const *s1, char32_t const *s2);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__wcsnicoll)(char16_t const *s1, char16_t const *s2, size_t maxlen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcsncasecoll)(char32_t const *s1, char32_t const *s2, size_t maxlen);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnrev)(char16_t *__restrict str, size_t maxlen);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnrev)(char32_t *__restrict str, size_t maxlen);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) wchar_t *NOTHROW_NCX(LIBCCALL libc_wcsnlwr)(wchar_t *__restrict str, size_t maxlen);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnupr)(char16_t *__restrict str, size_t maxlen);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnupr)(char32_t *__restrict str, size_t maxlen);
/* Same as `strstr', but ignore casing */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcscasestr)(char16_t const *haystack, char16_t const *needle);
/* Same as `strstr', but ignore casing */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcscasestr)(char32_t const *haystack, char32_t const *needle);
/* Same as wcscpy, but return a pointer after the last written character */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcspcpy)(char16_t *__restrict buf, char16_t const *__restrict src);
/* Same as wcscpy, but return a pointer after the last written character */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcspcpy)(char32_t *__restrict buf, char32_t const *__restrict src);
/* Same as wcsncpy, but return a pointer after the last written character */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcspncpy)(char16_t *__restrict buf, char16_t const *__restrict src, size_t buflen);
/* Same as wcsncpy, but return a pointer after the last written character */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcspncpy)(char32_t *__restrict buf, char32_t const *__restrict src, size_t buflen);
/* Same as wmemset, but return a pointer after the last written character */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wmempset)(char16_t *dst, char16_t filler, size_t num_chars);
/* Same as wmemset, but return a pointer after the last written character */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wmempset)(char32_t *dst, char32_t filler, size_t num_chars);
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnchr)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnchr)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnrchr)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnrchr)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
INTDEF ATTR_LEAF NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcssep)(char16_t **__restrict stringp, char16_t const *__restrict delim);
INTDEF ATTR_LEAF NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcssep)(char32_t **__restrict stringp, char32_t const *__restrict delim);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsfry)(char16_t *__restrict string);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsfry)(char32_t *__restrict string);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsndup)(char16_t const *__restrict string, size_t max_chars);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsndup)(char32_t const *__restrict string, size_t max_chars);
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsrchrnul)(char16_t const *__restrict haystack, char16_t needle);
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsrchrnul)(char32_t const *__restrict haystack, char32_t needle);
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnchrnul)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnchrnul)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnrchrnul)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnrchrnul)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcsoff)(char16_t const *__restrict haystack, char16_t needle);
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBKCALL libc_wcsoff)(char32_t const *__restrict haystack, char32_t needle);
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcsroff)(char16_t const *__restrict haystack, char16_t needle);
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBKCALL libc_wcsroff)(char32_t const *__restrict haystack, char32_t needle);
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcsnoff)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBKCALL libc_wcsnoff)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcsnroff)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBKCALL libc_wcsnroff)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wmemcmp)(char16_t const *s1, size_t s1_chars, char16_t const *s2, size_t s2_chars);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBKCALL libc_fuzzy_wmemcmp)(char32_t const *s1, size_t s1_chars, char32_t const *s2, size_t s2_chars);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wcscmp)(char16_t const *s1, char16_t const *s2);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBKCALL libc_fuzzy_wcscmp)(char32_t const *s1, char32_t const *s2);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wcsncmp)(char16_t const *s1, size_t s1_maxlen, char16_t const *s2, size_t s2_maxlen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBKCALL libc_fuzzy_wcsncmp)(char32_t const *s1, size_t s1_maxlen, char32_t const *s2, size_t s2_maxlen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wmemcasecmp)(char16_t const *s1, size_t s1_bytes, char16_t const *s2, size_t s2_bytes);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBKCALL libc_fuzzy_wmemcasecmp)(char32_t const *s1, size_t s1_bytes, char32_t const *s2, size_t s2_bytes);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wcscasecmp)(char16_t const *s1, char16_t const *s2);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBKCALL libc_fuzzy_wcscasecmp)(char32_t const *s1, char32_t const *s2);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wcsncasecmp)(char16_t const *s1, size_t s1_maxlen, char16_t const *s2, size_t s2_maxlen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBKCALL libc_fuzzy_wcsncasecmp)(char32_t const *s1, size_t s1_maxlen, char32_t const *s2, size_t s2_maxlen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wildwcscmp)(char16_t const *pattern, char16_t const *string);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wildwcscmp)(char32_t const *pattern, char32_t const *string);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wildwcscasecmp)(char16_t const *pattern, char16_t const *string);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wildwcscasecmp)(char32_t const *pattern, char32_t const *string);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsverscmp)(char16_t const *s1, char16_t const *s2);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcsverscmp)(char32_t const *s1, char32_t const *s2);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__wcsncoll_l)(char16_t const *s1, char16_t const *s2, size_t maxlen, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcsncoll_l)(char32_t const *s1, char32_t const *s2, size_t maxlen, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__wcsicoll_l)(char16_t const *s1, char16_t const *s2, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcscasecoll_l)(char32_t const *s1, char32_t const *s2, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__wcsnicoll_l)(char16_t const *s1, char16_t const *s2, size_t maxlen, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcsncasecoll_l)(char32_t const *s1, char32_t const *s2, size_t maxlen, locale_t locale);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd__wcslwr_l)(char16_t *__restrict str, locale_t locale);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcslwr_l)(char32_t *__restrict str, locale_t locale);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd__wcsupr_l)(char16_t *__restrict str, locale_t locale);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsupr_l)(char32_t *__restrict str, locale_t locale);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnlwr_l)(char16_t *__restrict str, size_t maxlen, locale_t locale);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnlwr_l)(char32_t *__restrict str, size_t maxlen, locale_t locale);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnupr_l)(char16_t *__restrict str, size_t maxlen, locale_t locale);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnupr_l)(char32_t *__restrict str, size_t maxlen, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcscasestr_l)(char16_t const *haystack, char16_t const *needle, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcscasestr_l)(char32_t const *haystack, char32_t const *needle, locale_t locale);
INTDEF size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wmemcasecmp_l)(char16_t const *s1, size_t s1_bytes, char16_t const *s2, size_t s2_bytes, locale_t locale);
INTDEF size_t NOTHROW_NCX(LIBKCALL libc_fuzzy_wmemcasecmp_l)(char32_t const *s1, size_t s1_bytes, char32_t const *s2, size_t s2_bytes, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wcscasecmp_l)(char16_t const *s1, char16_t const *s2, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBKCALL libc_fuzzy_wcscasecmp_l)(char32_t const *s1, char32_t const *s2, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wcsncasecmp_l)(char16_t const *s1, size_t s1_maxlen, char16_t const *s2, size_t s2_maxlen, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBKCALL libc_fuzzy_wcsncasecmp_l)(char32_t const *s1, size_t s1_maxlen, char32_t const *s2, size_t s2_maxlen, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wildwcscasecmp_l)(char16_t const *pattern, char16_t const *string, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wildwcscasecmp_l)(char32_t const *pattern, char32_t const *string, locale_t locale);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_wcscat_s)(char16_t *dst, size_t dstsize, char16_t const *src);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc_wcscat_s)(char32_t *dst, size_t dstsize, char32_t const *src);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_wcscpy_s)(char16_t *dst, size_t dstsize, char16_t const *src);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc_wcscpy_s)(char32_t *dst, size_t dstsize, char32_t const *src);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_wcsncat_s)(char16_t *dst, rsize_t dstsize, const char16_t *src, rsize_t maxlen);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc_wcsncat_s)(char32_t *dst, rsize_t dstsize, const char32_t *src, rsize_t maxlen);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_wcsncpy_s)(char16_t *dst, size_t dstsize, char16_t const *src, size_t maxlen);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc_wcsncpy_s)(char32_t *dst, size_t dstsize, char32_t const *src, size_t maxlen);
INTDEF ATTR_LEAF errno_t NOTHROW_NCX(LIBDCALL libd__wcsnset_s)(char16_t *__restrict buf, size_t buflen, int ch, size_t maxlen);
INTDEF ATTR_LEAF errno_t NOTHROW_NCX(LIBKCALL libc__wcsnset_s)(char32_t *__restrict buf, size_t buflen, int ch, size_t maxlen);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd__wcsset_s)(char16_t *dst, size_t dstsize, int ch);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBKCALL libc__wcsset_s)(char32_t *dst, size_t dstsize, int ch);
INTDEF ATTR_LEAF errno_t NOTHROW_NCX(LIBDCALL libd__wcslwr_s)(char16_t *buf, size_t buflen);
INTDEF ATTR_LEAF errno_t NOTHROW_NCX(LIBKCALL libc__wcslwr_s)(char32_t *buf, size_t buflen);
INTDEF ATTR_LEAF errno_t NOTHROW_NCX(LIBDCALL libd__wcsupr_s)(char16_t *buf, size_t buflen);
INTDEF ATTR_LEAF errno_t NOTHROW_NCX(LIBKCALL libc__wcsupr_s)(char32_t *buf, size_t buflen);
INTDEF ATTR_LEAF errno_t NOTHROW_NCX(LIBDCALL libd__wcslwr_s_l)(char16_t *buf, size_t buflen, locale_t locale);
INTDEF ATTR_LEAF errno_t NOTHROW_NCX(LIBKCALL libc__wcslwr_s_l)(char32_t *buf, size_t buflen, locale_t locale);
INTDEF ATTR_LEAF errno_t NOTHROW_NCX(LIBDCALL libd__wcsupr_s_l)(char16_t *buf, size_t buflen, locale_t locale);
INTDEF ATTR_LEAF errno_t NOTHROW_NCX(LIBKCALL libc__wcsupr_s_l)(char32_t *buf, size_t buflen, locale_t locale);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBDCALL libd_wmemcpy_s)(void *dst, rsize_t dstlength, void const *src, rsize_t srclength);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBKCALL libc_wmemcpy_s)(void *dst, rsize_t dstlength, void const *src, rsize_t srclength);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBDCALL libd_wmemmove_s)(void *dst, rsize_t dstlength, void const *src, rsize_t srclength);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBKCALL libc_wmemmove_s)(void *dst, rsize_t dstlength, void const *src, rsize_t srclength);
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd__wcsnset)(char16_t *__restrict str, char16_t ch, size_t maxlen);
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnset)(char32_t *__restrict str, char32_t ch, size_t maxlen);
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd__wcsrev)(char16_t *__restrict str);
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsrev)(char32_t *__restrict str);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd__wcsset)(char16_t *__restrict str, int ch);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsset)(char32_t *__restrict str, int ch);
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd__wcslwr)(char16_t *__restrict str);
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcslwr)(char32_t *__restrict str);
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd__wcsupr)(char16_t *__restrict str);
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsupr)(char32_t *__restrict str);
INTDEF WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vscwprintf)(char16_t const *format, va_list args);
INTDEF WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vscwprintf)(char32_t const *format, va_list args);
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(VLIBDCALL libd__scwprintf)(char16_t const *format, ...);
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(VLIBKCALL libc__scwprintf)(char32_t const *format, ...);
INTDEF WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vscwprintf_p)(char16_t const *format, va_list args);
INTDEF WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vscwprintf_p)(char32_t const *format, va_list args);
INTDEF WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__scwprintf_p)(char16_t const *format, ...);
INTDEF WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__scwprintf_p)(char32_t const *format, ...);
INTDEF WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vscwprintf_l)(char16_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vscwprintf_l)(char32_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__scwprintf_l)(char16_t const *format, locale_t locale, ...);
INTDEF WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__scwprintf_l)(char32_t const *format, locale_t locale, ...);
INTDEF WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vscwprintf_p_l)(char16_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vscwprintf_p_l)(char32_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__scwprintf_p_l)(char16_t const *format, locale_t locale, ...);
INTDEF WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__scwprintf_p_l)(char32_t const *format, locale_t locale, ...);
INTDEF NONNULL((4)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vsnwprintf_s)(char16_t *buf, size_t bufsize, size_t buflen, char16_t const *format, va_list args);
INTDEF NONNULL((4)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vsnwprintf_s)(char32_t *buf, size_t bufsize, size_t buflen, char32_t const *format, va_list args);
INTDEF NONNULL((4)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__snwprintf_s)(char16_t *buf, size_t bufsize, size_t buflen, char16_t const *format, ...);
INTDEF NONNULL((4)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__snwprintf_s)(char32_t *buf, size_t bufsize, size_t buflen, char32_t const *format, ...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd__vfwprintf_p)(FILE *stream, char16_t const *format, va_list args) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBKCALL libc__vfwprintf_p)(FILE *stream, char32_t const *format, va_list args) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (VLIBDCALL libd__fwprintf_p)(FILE *stream, char16_t const *format, ...) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (VLIBKCALL libc__fwprintf_p)(FILE *stream, char32_t const *format, ...) THROWS(...);
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd__vwprintf_p)(char16_t const *format, va_list args) THROWS(...);
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBKCALL libc__vwprintf_p)(char32_t const *format, va_list args) THROWS(...);
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (VLIBDCALL libd__wprintf_p)(char16_t const *format, ...) THROWS(...);
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (VLIBKCALL libc__wprintf_p)(char32_t const *format, ...) THROWS(...);
INTDEF NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vswprintf_p)(char16_t *buf, size_t bufsize, char16_t const *format, va_list args);
INTDEF NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vswprintf_p)(char32_t *buf, size_t bufsize, char32_t const *format, va_list args);
INTDEF NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__swprintf_p)(char16_t *dst, size_t bufsize, char16_t const *format, ...);
INTDEF NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__swprintf_p)(char32_t *dst, size_t bufsize, char32_t const *format, ...);
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd__vwprintf_l)(char16_t const *format, locale_t locale, va_list args) THROWS(...);
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBKCALL libc__vwprintf_l)(char32_t const *format, locale_t locale, va_list args) THROWS(...);
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (VLIBDCALL libd__wprintf_l)(char16_t const *format, locale_t locale, ...) THROWS(...);
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (VLIBKCALL libc__wprintf_l)(char32_t const *format, locale_t locale, ...) THROWS(...);
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd__vwprintf_p_l)(char16_t const *format, locale_t locale, va_list args) THROWS(...);
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBKCALL libc__vwprintf_p_l)(char32_t const *format, locale_t locale, va_list args) THROWS(...);
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (VLIBDCALL libd__wprintf_p_l)(char16_t const *format, locale_t locale, ...) THROWS(...);
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (VLIBKCALL libc__wprintf_p_l)(char32_t const *format, locale_t locale, ...) THROWS(...);
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd__vwprintf_s_l)(char16_t const *format, locale_t locale, va_list args) THROWS(...);
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBKCALL libc__vwprintf_s_l)(char32_t const *format, locale_t locale, va_list args) THROWS(...);
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (VLIBDCALL libd__wprintf_s_l)(char16_t const *format, locale_t locale, ...) THROWS(...);
INTDEF NONNULL((1)) __STDC_INT_AS_SSIZE_T (VLIBKCALL libc__wprintf_s_l)(char32_t const *format, locale_t locale, ...) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd__vfwprintf_l)(FILE *stream, char16_t const *format, locale_t locale, va_list args) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBKCALL libc__vfwprintf_l)(FILE *stream, char32_t const *format, locale_t locale, va_list args) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (VLIBDCALL libd__fwprintf_l)(FILE *stream, char16_t const *format, locale_t locale, ...) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (VLIBKCALL libc__fwprintf_l)(FILE *stream, char32_t const *format, locale_t locale, ...) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd__vfwprintf_p_l)(FILE *stream, char16_t const *format, locale_t locale, va_list args) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBKCALL libc__vfwprintf_p_l)(FILE *stream, char32_t const *format, locale_t locale, va_list args) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (VLIBDCALL libd__fwprintf_p_l)(FILE *stream, char16_t const *format, locale_t locale, ...) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (VLIBKCALL libc__fwprintf_p_l)(FILE *stream, char32_t const *format, locale_t locale, ...) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd__vfwprintf_s_l)(FILE *stream, char16_t const *format, locale_t locale, va_list args) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBKCALL libc__vfwprintf_s_l)(FILE *stream, char32_t const *format, locale_t locale, va_list args) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (VLIBDCALL libd__fwprintf_s_l)(FILE *stream, char16_t const *format, locale_t locale, ...) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (VLIBKCALL libc__fwprintf_s_l)(FILE *stream, char32_t const *format, locale_t locale, ...) THROWS(...);
INTDEF NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vswprintf_c_l)(char16_t *dst, size_t bufsize, char16_t const *format, locale_t locale, va_list args);
INTDEF NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vswprintf_c_l)(char32_t *dst, size_t bufsize, char32_t const *format, locale_t locale, va_list args);
INTDEF NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__swprintf_c_l)(char16_t *dst, size_t bufsize, char16_t const *format, locale_t locale, ...);
INTDEF NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__swprintf_c_l)(char32_t *dst, size_t bufsize, char32_t const *format, locale_t locale, ...);
INTDEF NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vswprintf_p_l)(char16_t *dst, size_t bufsize, char16_t const *format, locale_t locale, va_list args);
INTDEF NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vswprintf_p_l)(char32_t *dst, size_t bufsize, char32_t const *format, locale_t locale, va_list args);
INTDEF NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__swprintf_p_l)(char16_t *dst, size_t bufsize, char16_t const *format, locale_t locale, ...);
INTDEF NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__swprintf_p_l)(char32_t *dst, size_t bufsize, char32_t const *format, locale_t locale, ...);
INTDEF NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vswprintf_s_l)(char16_t *dst, size_t wchar_count, char16_t const *format, locale_t locale, va_list args);
INTDEF NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vswprintf_s_l)(char32_t *dst, size_t wchar_count, char32_t const *format, locale_t locale, va_list args);
INTDEF NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__swprintf_s_l)(char16_t *dst, size_t wchar_count, char16_t const *format, locale_t locale, ...);
INTDEF NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__swprintf_s_l)(char32_t *dst, size_t wchar_count, char32_t const *format, locale_t locale, ...);
INTDEF NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vsnwprintf_l)(char16_t *dst, size_t bufsize, char16_t const *format, locale_t locale, va_list args);
INTDEF NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vsnwprintf_l)(char32_t *dst, size_t bufsize, char32_t const *format, locale_t locale, va_list args);
INTDEF NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__snwprintf_l)(char16_t *dst, size_t bufsize, char16_t const *format, locale_t locale, ...);
INTDEF NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__snwprintf_l)(char32_t *dst, size_t bufsize, char32_t const *format, locale_t locale, ...);
INTDEF NONNULL((1, 4)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vsnwprintf_s_l)(char16_t *dst, size_t wchar_count, size_t bufsize, char16_t const *format, locale_t locale, va_list args);
INTDEF NONNULL((1, 4)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vsnwprintf_s_l)(char32_t *dst, size_t wchar_count, size_t bufsize, char32_t const *format, locale_t locale, va_list args);
INTDEF NONNULL((1, 4)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__snwprintf_s_l)(char16_t *dst, size_t wchar_count, size_t bufsize, char16_t const *format, locale_t locale, ...);
INTDEF NONNULL((1, 4)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__snwprintf_s_l)(char32_t *dst, size_t wchar_count, size_t bufsize, char32_t const *format, locale_t locale, ...);
INTDEF WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd__vfwscanf_l)(FILE *stream, char16_t const *format, locale_t locale, va_list args) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (LIBKCALL libc__vfwscanf_l)(FILE *stream, char32_t const *format, locale_t locale, va_list args) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (VLIBDCALL libd__fwscanf_l)(FILE *stream, char16_t const *format, locale_t locale, ...) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (VLIBKCALL libc__fwscanf_l)(FILE *stream, char32_t const *format, locale_t locale, ...) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vswscanf_l)(char16_t const *src, char16_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vswscanf_l)(char32_t const *src, char32_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__swscanf_l)(char16_t const *src, char16_t const *format, locale_t locale, ...);
INTDEF WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__swscanf_l)(char32_t const *src, char32_t const *format, locale_t locale, ...);
INTDEF WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vsnwscanf)(char16_t const *src, size_t bufsize, char16_t const *format, va_list args);
INTDEF WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vsnwscanf)(char32_t const *src, size_t bufsize, char32_t const *format, va_list args);
INTDEF WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__snwscanf)(char16_t const *src, size_t bufsize, char16_t const *format, ...);
INTDEF WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__snwscanf)(char32_t const *src, size_t bufsize, char32_t const *format, ...);
INTDEF WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vsnwscanf_l)(char16_t const *src, size_t bufsize, char16_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vsnwscanf_l)(char32_t const *src, size_t bufsize, char32_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__snwscanf_l)(char16_t const *src, size_t bufsize, char16_t const *format, locale_t locale, ...);
INTDEF WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__snwscanf_l)(char32_t const *src, size_t bufsize, char32_t const *format, locale_t locale, ...);
INTDEF WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vsnwscanf_s_l)(char16_t const *src, size_t bufsize, char16_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vsnwscanf_s_l)(char32_t const *src, size_t bufsize, char32_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__snwscanf_s_l)(char16_t const *src, size_t bufsize, char16_t const *format, locale_t locale, ...);
INTDEF WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__snwscanf_s_l)(char32_t const *src, size_t bufsize, char32_t const *format, locale_t locale, ...);
INTDEF WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBDCALL libd__vwscanf_l)(char16_t const *format, locale_t locale, va_list args) THROWS(...);
INTDEF WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T (LIBKCALL libc__vwscanf_l)(char32_t const *format, locale_t locale, va_list args) THROWS(...);
INTDEF WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T (VLIBDCALL libd__wscanf_l)(char16_t const *format, locale_t locale, ...) THROWS(...);
INTDEF WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T (VLIBKCALL libc__wscanf_l)(char32_t const *format, locale_t locale, ...) THROWS(...);
INTDEF char16_t *NOTHROW_NCX(LIBDCALL libd__getws_s)(char16_t *buf, size_t buflen);
INTDEF char32_t *NOTHROW_NCX(LIBKCALL libc__getws_s)(char32_t *buf, size_t buflen);
INTDEF NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd__putws)(char16_t const *string);
INTDEF NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBKCALL libc__putws)(char32_t const *string);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_WCHAR_H */
