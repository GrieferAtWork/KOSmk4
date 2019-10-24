/* HASH CRC-32:0xd4958f90 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
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
INTDEF WUNUSED wint_t NOTHROW_NCX(LIBCCALL libc_btowc)(int ch);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc_wctob)(wint_t ch);
INTDEF NONNULL((2)) size_t NOTHROW_NCX(LIBCCALL libc_mbrtowc)(char32_t *pwc, char const *__restrict str, size_t maxlen, mbstate_t *ps);
INTDEF NONNULL((2)) size_t NOTHROW_NCX(LIBDCALL libd_mbrtowc)(char16_t *pwc, char const *__restrict str, size_t maxlen, mbstate_t *ps);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_wcrtomb)(char *__restrict str, char32_t wc, mbstate_t *ps);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcrtomb)(char *__restrict str, char16_t wc, mbstate_t *ps);
INTDEF WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_mbrlen)(char const *__restrict str, size_t maxlen, mbstate_t *ps);
INTDEF WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_mbrlen)(char const *__restrict str, size_t maxlen, mbstate_t *ps);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBCCALL libc_mbsrtowcs)(char32_t *dst, char const **__restrict psrc, size_t len, mbstate_t *ps);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_mbsrtowcs)(char16_t *dst, char const **__restrict psrc, size_t len, mbstate_t *ps);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBCCALL libc_wcsrtombs)(char *dst, char32_t const **__restrict psrc, size_t len, mbstate_t *ps);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_wcsrtombs)(char *dst, char16_t const **__restrict psrc, size_t len, mbstate_t *ps);
INTDEF NONNULL((1)) double NOTHROW_NCX(LIBCCALL libc_wcstod)(char32_t const *__restrict nptr, char32_t **endptr);
INTDEF NONNULL((1)) double NOTHROW_NCX(LIBDCALL libd_wcstod)(char16_t const *__restrict nptr, char16_t **endptr);
INTDEF NONNULL((1)) long NOTHROW_NCX(LIBCCALL libc_wcstol)(char32_t const *__restrict nptr, char32_t **endptr, int base);
INTDEF NONNULL((1)) long NOTHROW_NCX(LIBDCALL libd_wcstol)(char16_t const *__restrict nptr, char16_t **endptr, int base);
INTDEF NONNULL((1)) unsigned long NOTHROW_NCX(LIBCCALL libc_wcstoul)(char32_t const *__restrict nptr, char32_t **endptr, int base);
INTDEF NONNULL((1)) unsigned long NOTHROW_NCX(LIBDCALL libd_wcstoul)(char16_t const *__restrict nptr, char16_t **endptr, int base);
INTDEF WUNUSED ATTR_PURE int NOTHROW_NCX(LIBCCALL libc_mbsinit)(mbstate_t const *ps);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_wmemcmp)(char32_t const *s1, char32_t const *s2, size_t num_chars);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wmemcmp)(char16_t const *s1, char16_t const *s2, size_t num_chars);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBCCALL libc_wmemcpy)(char32_t *__restrict dst, char32_t const *__restrict src, size_t num_chars);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wmemcpy)(char16_t *__restrict dst, char16_t const *__restrict src, size_t num_chars);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBCCALL libc_wmemmove)(char32_t *dst, char32_t const *src, size_t num_chars);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wmemmove)(char16_t *dst, char16_t const *src, size_t num_chars);
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wmemset)(char32_t *dst, char32_t filler, size_t num_chars);
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wmemset)(char16_t *dst, char16_t filler, size_t num_chars);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcscpy)(char32_t *__restrict buf, char32_t const *__restrict src);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcscpy)(char16_t *__restrict buf, char16_t const *__restrict src);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcscat)(char32_t *__restrict buf, char32_t const *__restrict src);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcscat)(char16_t *__restrict buf, char16_t const *__restrict src);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcsncat)(char32_t *__restrict buf, char32_t const *__restrict src, size_t buflen);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsncat)(char16_t *__restrict buf, char16_t const *__restrict src, size_t buflen);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcsncpy)(char32_t *__restrict buf, char32_t const *__restrict src, size_t buflen);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsncpy)(char16_t *__restrict buf, char16_t const *__restrict src, size_t buflen);
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_wcscmp)(char32_t const *s1, char32_t const *s2);
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcscmp)(char16_t const *s1, char16_t const *s2);
/* Same as `wcscmp', but compare at most `MAXLEN' characters from either string */
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_wcsncmp)(char32_t const *s1, char32_t const *s2, size_t maxlen);
/* Same as `wcscmp', but compare at most `MAXLEN' characters from either string */
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsncmp)(char16_t const *s1, char16_t const *s2, size_t maxlen);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_wcscoll)(char32_t const *s1, char32_t const *s2);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcscoll)(char16_t const *s1, char16_t const *s2);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBCCALL libc_wcsxfrm)(char32_t *dst, char32_t const *__restrict src, size_t maxlen);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_wcsxfrm)(char16_t *dst, char16_t const *__restrict src, size_t maxlen);
INTDEF NONNULL((1, 3, 4)) size_t NOTHROW_NCX(LIBCCALL libc_wcsftime)(char32_t *__restrict buf, size_t buflen, char32_t const *__restrict format, struct tm const *__restrict tp);
INTDEF NONNULL((1, 3, 4)) size_t NOTHROW_NCX(LIBDCALL libd_wcsftime)(char16_t *__restrict buf, size_t buflen, char16_t const *__restrict format, struct tm const *__restrict tp);
INTDEF NONNULL((2, 3)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcstok)(char32_t *string, char32_t const *__restrict delim, char32_t **__restrict save_ptr);
INTDEF NONNULL((2, 3)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcstok)(char16_t *string, char16_t const *__restrict delim, char16_t **__restrict save_ptr);
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_wcslen)(char32_t const *__restrict string);
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcslen)(char16_t const *__restrict string);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) size_t NOTHROW_NCX(LIBCCALL libc_wcsspn)(char32_t const *haystack, char32_t const *accept);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_wcsspn)(char16_t const *haystack, char16_t const *accept);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) size_t NOTHROW_NCX(LIBCCALL libc_wcscspn)(char32_t const *haystack, char32_t const *reject);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_wcscspn)(char16_t const *haystack, char16_t const *reject);
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcschr)(char32_t const *__restrict haystack, char32_t needle);
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcschr)(char16_t const *__restrict haystack, char16_t needle);
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcsrchr)(char32_t const *__restrict haystack, char32_t needle);
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsrchr)(char16_t const *__restrict haystack, char16_t needle);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcspbrk)(char32_t const *haystack, char32_t const *accept);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcspbrk)(char16_t const *haystack, char16_t const *accept);
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcsstr)(char32_t const *haystack, char32_t const *needle);
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsstr)(char16_t const *haystack, char16_t const *needle);
INTDEF WUNUSED ATTR_PURE NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wmemchr)(char32_t const *__restrict haystack, char32_t needle, size_t num_chars);
INTDEF WUNUSED ATTR_PURE NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wmemchr)(char16_t const *__restrict haystack, char16_t needle, size_t num_chars);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_fwide)(FILE *fp, int mode);
INTDEF ATTR_LIBC_WSCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc_swscanf)(char32_t const *__restrict src, char32_t const *__restrict format, ...);
INTDEF ATTR_LIBC_WSCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd_swscanf)(char16_t const *__restrict src, char16_t const *__restrict format, ...);
INTDEF ATTR_LIBC_WPRINTF(3, 0) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_vswprintf)(char32_t *__restrict buf, size_t buflen, char32_t const *__restrict format, va_list args);
INTDEF ATTR_LIBC_WPRINTF(3, 0) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd_vswprintf)(char16_t *__restrict buf, size_t buflen, char16_t const *__restrict format, va_list args);
INTDEF ATTR_LIBC_WPRINTF(3, 4) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc_swprintf)(char32_t *__restrict buf, size_t buflen, char32_t const *__restrict format, ...);
INTDEF ATTR_LIBC_WPRINTF(3, 4) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBDCALL libd_swprintf)(char16_t *__restrict buf, size_t buflen, char16_t const *__restrict format, ...);
INTDEF ATTR_PURE NONNULL((1)) float NOTHROW_NCX(LIBCCALL libc_wcstof)(char32_t const *__restrict nptr, char32_t **endptr);
INTDEF ATTR_PURE NONNULL((1)) float NOTHROW_NCX(LIBDCALL libd_wcstof)(char16_t const *__restrict nptr, char16_t **endptr);
INTDEF ATTR_PURE NONNULL((1)) long double NOTHROW_NCX(LIBCCALL libc_wcstold)(char32_t const *__restrict nptr, char32_t **endptr);
INTDEF ATTR_PURE NONNULL((1)) long double NOTHROW_NCX(LIBDCALL libd_wcstold)(char16_t const *__restrict nptr, char16_t **endptr);
INTDEF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBCCALL libc_wcstoll)(char32_t const *__restrict nptr, char32_t **endptr, int base);
INTDEF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBDCALL libd_wcstoll)(char16_t const *__restrict nptr, char16_t **endptr, int base);
INTDEF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBCCALL libc_wcstoull)(char32_t const *__restrict nptr, char32_t **endptr, int base);
INTDEF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBDCALL libd_wcstoull)(char16_t const *__restrict nptr, char16_t **endptr, int base);
INTDEF WUNUSED ATTR_LIBC_WSCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_vswscanf)(char32_t const *__restrict src, char32_t const *__restrict format, va_list args);
INTDEF WUNUSED ATTR_LIBC_WSCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd_vswscanf)(char16_t const *__restrict src, char16_t const *__restrict format, va_list args);
#define libc___mbrlen libc_mbrlen
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_wcscasecmp)(char32_t const *s1, char32_t const *s2);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcscasecmp)(char16_t const *s1, char16_t const *s2);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_wcsncasecmp)(char32_t const *s1, char32_t const *s2, size_t maxlen);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsncasecmp)(char16_t const *s1, char16_t const *s2, size_t maxlen);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_wcscasecmp_l)(char32_t const *s1, char32_t const *s2, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcscasecmp_l)(char16_t const *s1, char16_t const *s2, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_wcsncasecmp_l)(char32_t const *s1, char32_t const *s2, size_t maxlen, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsncasecmp_l)(char16_t const *s1, char16_t const *s2, size_t maxlen, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_wcscoll_l)(char32_t const *s1, char32_t const *s2, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcscoll_l)(char16_t const *s1, char16_t const *s2, locale_t locale);
INTDEF NONNULL((2)) size_t NOTHROW_NCX(LIBCCALL libc_wcsxfrm_l)(char32_t *dst, char32_t const *__restrict src, size_t maxlen, locale_t locale);
INTDEF NONNULL((2)) size_t NOTHROW_NCX(LIBDCALL libd_wcsxfrm_l)(char16_t *dst, char16_t const *__restrict src, size_t maxlen, locale_t locale);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcpcpy)(char32_t *__restrict dst, char32_t const *__restrict src);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcpcpy)(char16_t *__restrict dst, char16_t const *__restrict src);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcpncpy)(char32_t *__restrict buf, char32_t const *__restrict src, size_t buflen);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcpncpy)(char16_t *__restrict buf, char16_t const *__restrict src, size_t buflen);
/* Same as `wcslen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_wcsnlen)(char32_t const *__restrict string, size_t maxlen);
/* Same as `wcslen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcsnlen)(char16_t const *__restrict string, size_t maxlen);
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
#define libc_wcswcs libc_wcsstr
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
#define libd_wcswcs libd_wcsstr
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcschrnul)(char32_t const *haystack, char32_t needle);
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcschrnul)(char16_t const *haystack, char16_t needle);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBCCALL libc_wmempcpy)(char32_t *__restrict dst, char32_t const *__restrict src, size_t num_chars);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wmempcpy)(char16_t *__restrict dst, char16_t const *__restrict src, size_t num_chars);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBCCALL libc_wmempmove)(char32_t *dst, char32_t const *src, size_t num_chars);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wmempmove)(char16_t *dst, char16_t const *src, size_t num_chars);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) long NOTHROW_NCX(LIBCCALL libc_wcstol_l)(char32_t const *__restrict nptr, char32_t **__restrict endptr, int base, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) long NOTHROW_NCX(LIBDCALL libd_wcstol_l)(char16_t const *__restrict nptr, char16_t **__restrict endptr, int base, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) unsigned long NOTHROW_NCX(LIBCCALL libc_wcstoul_l)(char32_t const *__restrict nptr, char32_t **__restrict endptr, int base, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) unsigned long NOTHROW_NCX(LIBDCALL libd_wcstoul_l)(char16_t const *__restrict nptr, char16_t **__restrict endptr, int base, locale_t locale);
#define libc_wcstoq libc_wcstoll
#define libd_wcstoq libd_wcstoll
#define libc_wcstouq libc_wcstoull
#define libd_wcstouq libd_wcstoull
INTDEF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBCCALL libc_wcstoll_l)(char32_t const *__restrict nptr, char32_t **endptr, int base, locale_t locale);
INTDEF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBDCALL libd_wcstoll_l)(char16_t const *__restrict nptr, char16_t **endptr, int base, locale_t locale);
INTDEF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBCCALL libc_wcstoull_l)(char32_t const *__restrict nptr, char32_t **endptr, int base, locale_t locale);
INTDEF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBDCALL libd_wcstoull_l)(char16_t const *__restrict nptr, char16_t **endptr, int base, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) float NOTHROW_NCX(LIBCCALL libc_wcstof_l)(char32_t const *__restrict nptr, char32_t **endptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) float NOTHROW_NCX(LIBDCALL libd_wcstof_l)(char16_t const *__restrict nptr, char16_t **endptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) double NOTHROW_NCX(LIBCCALL libc_wcstod_l)(char32_t const *__restrict nptr, char32_t **endptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) double NOTHROW_NCX(LIBDCALL libd_wcstod_l)(char16_t const *__restrict nptr, char16_t **endptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) long double NOTHROW_NCX(LIBCCALL libc_wcstold_l)(char32_t const *__restrict nptr, char32_t **endptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) long double NOTHROW_NCX(LIBDCALL libd_wcstold_l)(char16_t const *__restrict nptr, char16_t **endptr, locale_t locale);
INTDEF NONNULL((1, 3, 4)) size_t NOTHROW_NCX(LIBCCALL libc_wcsftime_l)(char32_t *__restrict buf, size_t maxsize, char32_t const *__restrict format, __STRUCT_TM const *__restrict tp, locale_t locale);
INTDEF NONNULL((1, 3, 4)) size_t NOTHROW_NCX(LIBDCALL libd_wcsftime_l)(char16_t *__restrict buf, size_t maxsize, char16_t const *__restrict format, __STRUCT_TM const *__restrict tp, locale_t locale);
/* Same as `STR+wcslen(STR)' */
INTDEF WUNUSED ATTR_PURE ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcsend)(char32_t const *__restrict string);
/* Same as `STR+wcslen(STR)' */
INTDEF WUNUSED ATTR_PURE ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsend)(char16_t const *__restrict string);
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcsnend)(char32_t const *__restrict string, size_t maxlen);
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnend)(char16_t const *__restrict string, size_t maxlen);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint32_t NOTHROW_NCX(LIBCCALL libc_wcstou32)(char32_t const *__restrict nptr, char32_t **endptr, int base);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint32_t NOTHROW_NCX(LIBDCALL libd_wcstou32)(char16_t const *__restrict nptr, char16_t **endptr, int base);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int32_t NOTHROW_NCX(LIBCCALL libc_wcsto32)(char32_t const *__restrict nptr, char32_t **endptr, int base);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int32_t NOTHROW_NCX(LIBDCALL libd_wcsto32)(char16_t const *__restrict nptr, char16_t **endptr, int base);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint64_t NOTHROW_NCX(LIBCCALL libc_wcstou64)(char32_t const *__restrict nptr, char32_t **endptr, int base);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint64_t NOTHROW_NCX(LIBDCALL libd_wcstou64)(char16_t const *__restrict nptr, char16_t **endptr, int base);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int64_t NOTHROW_NCX(LIBCCALL libc_wcsto64)(char32_t const *__restrict nptr, char32_t **endptr, int base);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int64_t NOTHROW_NCX(LIBDCALL libd_wcsto64)(char16_t const *__restrict nptr, char16_t **endptr, int base);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_wcsncoll)(char32_t const *s1, char32_t const *s2, size_t maxlen);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsncoll)(char16_t const *s1, char16_t const *s2, size_t maxlen);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_wcscasecoll)(char32_t const *s1, char32_t const *s2);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcscasecoll)(char16_t const *s1, char16_t const *s2);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_wcsncasecoll)(char32_t const *s1, char32_t const *s2, size_t maxlen);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsncasecoll)(char16_t const *s1, char16_t const *s2, size_t maxlen);
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcsnrev)(char32_t *__restrict str, size_t maxlen);
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnrev)(char16_t *__restrict str, size_t maxlen);
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcsnlwr)(char32_t *__restrict str, size_t maxlen);
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcsnupr)(char32_t *__restrict str, size_t maxlen);
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnupr)(char16_t *__restrict str, size_t maxlen);
/* Same as `wcsstr', but ignore casing */
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcscasestr)(char32_t const *haystack, char32_t const *needle);
/* Same as `wcsstr', but ignore casing */
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcscasestr)(char16_t const *haystack, char16_t const *needle);
/* Same as wcscpy, but return a pointer after the last written character */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcspcpy)(char32_t *__restrict buf, char32_t const *__restrict src);
/* Same as wcscpy, but return a pointer after the last written character */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcspcpy)(char16_t *__restrict buf, char16_t const *__restrict src);
/* Same as wcsncpy, but return a pointer after the last written character */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcspncpy)(char32_t *__restrict buf, char32_t const *__restrict src, size_t buflen);
/* Same as wcsncpy, but return a pointer after the last written character */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcspncpy)(char16_t *__restrict buf, char16_t const *__restrict src, size_t buflen);
/* Same as wmemset, but return a pointer after the last written character */
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wmempset)(char32_t *dst, char32_t filler, size_t num_chars);
/* Same as wmemset, but return a pointer after the last written character */
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wmempset)(char16_t *dst, char16_t filler, size_t num_chars);
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcsnchr)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnchr)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcsnrchr)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnrchr)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
INTDEF NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcssep)(char32_t **__restrict stringp, char32_t const *__restrict delim);
INTDEF NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcssep)(char16_t **__restrict stringp, char16_t const *__restrict delim);
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcsfry)(char32_t *__restrict string);
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsfry)(char16_t *__restrict string);
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF WUNUSED ATTR_PURE ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcsrchrnul)(char32_t const *__restrict haystack, char32_t needle);
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF WUNUSED ATTR_PURE ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsrchrnul)(char16_t const *__restrict haystack, char16_t needle);
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF WUNUSED ATTR_PURE ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcsnchrnul)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF WUNUSED ATTR_PURE ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnchrnul)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF WUNUSED ATTR_PURE ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcsnrchrnul)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF WUNUSED ATTR_PURE ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnrchrnul)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_wcsoff)(char32_t const *__restrict haystack, char32_t needle);
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcsoff)(char16_t const *__restrict haystack, char16_t needle);
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_wcsroff)(char32_t const *__restrict haystack, char32_t needle);
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcsroff)(char16_t const *__restrict haystack, char16_t needle);
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_wcsnoff)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcsnoff)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_wcsnroff)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcsnroff)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 3)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_wmemcmp)(char32_t const *s1, size_t s1_chars, char32_t const *s2, size_t s2_chars);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wmemcmp)(char16_t const *s1, size_t s1_chars, char16_t const *s2, size_t s2_chars);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_wcscmp)(char32_t const *s1, char32_t const *s2);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wcscmp)(char16_t const *s1, char16_t const *s2);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 3)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_wcsncmp)(char32_t const *s1, size_t s1_maxlen, char32_t const *s2, size_t s2_maxlen);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wcsncmp)(char16_t const *s1, size_t s1_maxlen, char16_t const *s2, size_t s2_maxlen);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 3)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_wmemcasecmp)(char32_t const *s1, size_t s1_bytes, char32_t const *s2, size_t s2_bytes);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wmemcasecmp)(char16_t const *s1, size_t s1_bytes, char16_t const *s2, size_t s2_bytes);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_wcscasecmp)(char32_t const *s1, char32_t const *s2);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wcscasecmp)(char16_t const *s1, char16_t const *s2);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 3)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_wcsncasecmp)(char32_t const *s1, size_t s1_maxlen, char32_t const *s2, size_t s2_maxlen);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wcsncasecmp)(char16_t const *s1, size_t s1_maxlen, char16_t const *s2, size_t s2_maxlen);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_wildwcscmp)(char32_t const *pattern, char32_t const *string);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wildwcscmp)(char16_t const *pattern, char16_t const *string);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_wildwcscasecmp)(char32_t const *pattern, char32_t const *string);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wildwcscasecmp)(char16_t const *pattern, char16_t const *string);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_wcsverscmp)(char32_t const *s1, char32_t const *s2);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsverscmp)(char16_t const *s1, char16_t const *s2);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_wcsncoll_l)(char32_t const *s1, char32_t const *s2, size_t maxlen, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsncoll_l)(char16_t const *s1, char16_t const *s2, size_t maxlen, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_wcscasecoll_l)(char32_t const *s1, char32_t const *s2, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcscasecoll_l)(char16_t const *s1, char16_t const *s2, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_wcsncasecoll_l)(char32_t const *s1, char32_t const *s2, size_t maxlen, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsncasecoll_l)(char16_t const *s1, char16_t const *s2, size_t maxlen, locale_t locale);
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcslwr_l)(char32_t *__restrict str, locale_t locale);
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcslwr_l)(char16_t *__restrict str, locale_t locale);
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcsupr_l)(char32_t *__restrict str, locale_t locale);
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsupr_l)(char16_t *__restrict str, locale_t locale);
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcsnlwr_l)(char32_t *__restrict str, size_t maxlen, locale_t locale);
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnlwr_l)(char16_t *__restrict str, size_t maxlen, locale_t locale);
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcsnupr_l)(char32_t *__restrict str, size_t maxlen, locale_t locale);
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnupr_l)(char16_t *__restrict str, size_t maxlen, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcscasestr_l)(char32_t const *haystack, char32_t const *needle, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcscasestr_l)(char16_t const *haystack, char16_t const *needle, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 3)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_wmemcasecmp_l)(char32_t const *s1, size_t s1_bytes, char32_t const *s2, size_t s2_bytes, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wmemcasecmp_l)(char16_t const *s1, size_t s1_bytes, char16_t const *s2, size_t s2_bytes, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_wcscasecmp_l)(char32_t const *s1, char32_t const *s2, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wcscasecmp_l)(char16_t const *s1, char16_t const *s2, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 3)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_wcsncasecmp_l)(char32_t const *s1, size_t s1_maxlen, char32_t const *s2, size_t s2_maxlen, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wcsncasecmp_l)(char16_t const *s1, size_t s1_maxlen, char16_t const *s2, size_t s2_maxlen, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_wildwcscasecmp_l)(char32_t const *pattern, char32_t const *string, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wildwcscasecmp_l)(char16_t const *pattern, char16_t const *string, locale_t locale);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBCCALL libc_wcscat_s)(char32_t *dst, size_t dstsize, char32_t const *src);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBDCALL libd_wcscat_s)(char16_t *dst, size_t dstsize, char16_t const *src);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_wcscpy_s)(char32_t *dst, rsize_t dstsize, char32_t const *src);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_wcscpy_s)(char16_t *dst, rsize_t dstsize, char16_t const *src);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_wcsncat_s)(char32_t *dst, rsize_t dstsize, char32_t const *src, rsize_t maxlen);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_wcsncat_s)(char16_t *dst, rsize_t dstsize, char16_t const *src, rsize_t maxlen);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_wcsncpy_s)(char32_t *dst, rsize_t dstsize, char32_t const *src, rsize_t maxlen);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_wcsncpy_s)(char16_t *dst, rsize_t dstsize, char16_t const *src, rsize_t maxlen);
#define libc__wcsicmp libc_wcscasecmp
#define libd__wcsicmp libd_wcscasecmp
#define libc__wcsnicmp libc_wcsncasecmp
#define libd__wcsnicmp libd_wcsncasecmp
#define libc__wcsicmp_l libc_wcscasecmp_l
#define libd__wcsicmp_l libd_wcscasecmp_l
#define libc__wcsnicmp_l libc_wcsncasecmp_l
#define libd__wcsnicmp_l libd_wcsncasecmp_l
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__wcsnset_s)(char32_t *buf, size_t buflen, char32_t ch, size_t maxlen);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__wcsnset_s)(char16_t *buf, size_t buflen, char16_t ch, size_t maxlen);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc__wcsset_s)(char32_t *dst, size_t dstsize, char32_t ch);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd__wcsset_s)(char16_t *dst, size_t dstsize, char16_t ch);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__wcslwr_s)(char32_t *buf, size_t buflen);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__wcslwr_s)(char16_t *buf, size_t buflen);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__wcsupr_s)(char32_t *buf, size_t buflen);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__wcsupr_s)(char16_t *buf, size_t buflen);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__wcslwr_s_l)(char32_t *buf, size_t buflen, locale_t locale);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__wcslwr_s_l)(char16_t *buf, size_t buflen, locale_t locale);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__wcsupr_s_l)(char32_t *buf, size_t buflen, locale_t locale);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__wcsupr_s_l)(char16_t *buf, size_t buflen, locale_t locale);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBCCALL libc_wmemcpy_s)(char32_t *dst, rsize_t dstlength, char32_t const *src, rsize_t srclength);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBDCALL libd_wmemcpy_s)(char16_t *dst, rsize_t dstlength, char16_t const *src, rsize_t srclength);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBCCALL libc_wmemmove_s)(char32_t *dst, rsize_t dstlength, char32_t const *src, rsize_t srclength);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBDCALL libd_wmemmove_s)(char16_t *dst, rsize_t dstlength, char16_t const *src, rsize_t srclength);
#define libc__wcsnset libc_wcsnset
#define libd__wcsnset libd_wcsnset
#define libc__wcsrev libc_wcsrev
#define libd__wcsrev libd_wcsrev
#define libc__wcsset libc_wcsset
#define libd__wcsset libd_wcsset
#define libc__wcslwr libc_wcslwr
#define libd__wcslwr libd_wcslwr
#define libc__wcsupr libc_wcsupr
#define libd__wcsupr libd_wcsupr
#define libc__wcslwr_l libc_wcslwr_l
#define libd__wcslwr_l libd_wcslwr_l
#define libc__wcsupr_l libc_wcsupr_l
#define libd__wcsupr_l libd_wcsupr_l
#define libc__wcscoll_l libc_wcscoll_l
#define libd__wcscoll_l libd_wcscoll_l
#define libc__wcsicoll libc_wcscasecoll
#define libd__wcsicoll libd_wcscasecoll
#define libc__wcsicoll_l libc_wcscasecoll_l
#define libd__wcsicoll_l libd_wcscasecoll_l
#define libc__wcsncoll libc_wcsncasecoll
#define libd__wcsncoll libd_wcsncasecoll
#define libc__wcsncoll_l libc_wcsncoll_l
#define libd__wcsncoll_l libd_wcsncoll_l
#define libc__wcsnicoll libc_wcsncasecoll
#define libd__wcsnicoll libd_wcsncasecoll
#define libc__wcsnicoll_l libc_wcsncasecoll_l
#define libd__wcsnicoll_l libd_wcsncasecoll_l
#define libc_wcsicmp libc_wcscasecmp
#define libd_wcsicmp libd_wcscasecmp
#define libc_wcsnicmp libc_wcsncasecmp
#define libd_wcsnicmp libd_wcsncasecmp
#define libc_wcsicoll libc_wcscasecoll
#define libd_wcsicoll libd_wcscasecoll
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcsnset)(char32_t *__restrict str, char32_t ch, size_t maxlen);
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnset)(char16_t *__restrict str, char16_t ch, size_t maxlen);
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcsrev)(char32_t *__restrict str);
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsrev)(char16_t *__restrict str);
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcsset)(char32_t *__restrict str, char32_t ch);
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsset)(char16_t *__restrict str, char16_t ch);
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcslwr)(char32_t *__restrict str);
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcslwr)(char16_t *__restrict str);
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_wcsupr)(char32_t *__restrict str);
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsupr)(char16_t *__restrict str);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_WCHAR_H */
