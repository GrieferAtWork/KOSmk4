/* HASH CRC-32:0xd0052de */
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
INTDEF ATTR_CONST WUNUSED wint16_t NOTHROW_NCX(LIBDCALL libd_btowc)(int ch);
INTDEF ATTR_CONST WUNUSED wint32_t NOTHROW_NCX(LIBKCALL libc_btowc)(int ch);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBDCALL libd_wctob)(wint16_t ch);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBKCALL libc_wctob)(wint32_t ch);
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
INTDEF ATTR_LEAF NONNULL((1)) long NOTHROW_NCX(LIBDCALL libd_wcstol)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base);
INTDEF ATTR_LEAF NONNULL((1)) long NOTHROW_NCX(LIBKCALL libc_wcstol)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base);
INTDEF ATTR_LEAF NONNULL((1)) unsigned long NOTHROW_NCX(LIBDCALL libd_wcstoul)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base);
INTDEF ATTR_LEAF NONNULL((1)) unsigned long NOTHROW_NCX(LIBKCALL libc_wcstoul)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_mbsinit)(mbstate_t const *mbs);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_mbsinit)(mbstate_t const *mbs);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcscpy)(char16_t *__restrict buf, char16_t const *__restrict src);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcscpy)(char32_t *__restrict buf, char32_t const *__restrict src);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcscat)(char16_t *__restrict buf, char16_t const *__restrict src);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcscat)(char32_t *__restrict buf, char32_t const *__restrict src);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsncat)(char16_t *__restrict buf, char16_t const *__restrict src, size_t buflen);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsncat)(char32_t *__restrict buf, char32_t const *__restrict src, size_t buflen);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsncpy)(char16_t *__restrict buf, char16_t const *__restrict src, size_t buflen);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsncpy)(char32_t *__restrict buf, char32_t const *__restrict src, size_t buflen);
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcscmp)(char16_t const *s1, char16_t const *s2);
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcscmp)(char32_t const *s1, char32_t const *s2);
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsncmp)(char16_t const *s1, char16_t const *s2, size_t maxlen);
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcsncmp)(char32_t const *s1, char32_t const *s2, size_t maxlen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcscoll)(char16_t const *s1, char16_t const *s2);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcscoll)(char32_t const *s1, char32_t const *s2);
INTDEF NONNULL((2)) size_t NOTHROW_NCX(LIBDCALL libd_wcsxfrm)(char16_t *dst, char16_t const *__restrict src, size_t maxlen);
INTDEF NONNULL((2)) size_t NOTHROW_NCX(LIBKCALL libc_wcsxfrm)(char32_t *dst, char32_t const *__restrict src, size_t maxlen);
INTDEF wint16_t (LIBDCALL libd_getwchar)(void) THROWS(...);
INTDEF wint32_t (LIBKCALL libc_getwchar)(void) THROWS(...);
INTDEF wint16_t (LIBDCALL libd_putwchar)(char16_t wc) THROWS(...);
INTDEF wint32_t (LIBKCALL libc_putwchar)(char32_t wc) THROWS(...);
INTDEF WUNUSED NONNULL((1, 3)) char16_t *(LIBDCALL libd_fgetws)(char16_t *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) THROWS(...);
INTDEF WUNUSED NONNULL((1, 3)) char32_t *(LIBKCALL libc_fgetws)(char32_t *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_fputws)(char16_t const *__restrict str, FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_fputws)(char32_t const *__restrict str, FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1, 3, 4)) size_t NOTHROW_NCX(LIBDCALL libd_wcsftime)(char16_t *__restrict buf, size_t buflen, char16_t const *__restrict format, struct tm const *__restrict tp);
INTDEF NONNULL((1, 3, 4)) size_t NOTHROW_NCX(LIBKCALL libc_wcsftime)(char32_t *__restrict buf, size_t buflen, char32_t const *__restrict format, struct tm const *__restrict tp);
INTDEF NONNULL((2, 3)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcstok)(char16_t *str, char16_t const *__restrict delim, char16_t **__restrict save_ptr);
INTDEF NONNULL((2, 3)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcstok)(char32_t *str, char32_t const *__restrict delim, char32_t **__restrict save_ptr);
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcslen)(char16_t const *__restrict str);
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBKCALL libc_wcslen)(char32_t const *__restrict str);
/* >> strspn(3)
 * Return   the  offset  from  `haystack'  to  the  first
 * character   for   which  `strchr(reject, ch) == NULL'.
 * If no such character exists, return `strlen(haystack)' */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_wcsspn)(char16_t const *haystack, char16_t const *accept);
/* >> strspn(3)
 * Return   the  offset  from  `haystack'  to  the  first
 * character   for   which  `strchr(reject, ch) == NULL'.
 * If no such character exists, return `strlen(haystack)' */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBKCALL libc_wcsspn)(char32_t const *haystack, char32_t const *accept);
/* >> strcspn(3)
 * Return   the  offset  from  `haystack'  to  the  first
 * character   for   which  `strchr(reject, ch) != NULL'.
 * If no such character exists, return `strlen(haystack)' */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_wcscspn)(char16_t const *haystack, char16_t const *reject);
/* >> strcspn(3)
 * Return   the  offset  from  `haystack'  to  the  first
 * character   for   which  `strchr(reject, ch) != NULL'.
 * If no such character exists, return `strlen(haystack)' */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBKCALL libc_wcscspn)(char32_t const *haystack, char32_t const *reject);
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcschr)(char16_t const *__restrict haystack, char16_t needle);
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcschr)(char32_t const *__restrict haystack, char32_t needle);
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsrchr)(char16_t const *__restrict haystack, char16_t needle);
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsrchr)(char32_t const *__restrict haystack, char32_t needle);
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcspbrk)(char16_t const *haystack, char16_t const *accept);
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcspbrk)(char32_t const *haystack, char32_t const *accept);
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsstr)(char16_t const *haystack, char16_t const *needle);
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsstr)(char32_t const *haystack, char32_t const *needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_fwide)(FILE *fp, int mode);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
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
INTDEF ATTR_LEAF NONNULL((1)) double NOTHROW_NCX(LIBDCALL libd_wcstod)(char16_t const *__restrict nptr, char16_t **endptr);
INTDEF ATTR_LEAF NONNULL((1)) double NOTHROW_NCX(LIBKCALL libc_wcstod)(char32_t const *__restrict nptr, char32_t **endptr);
INTDEF ATTR_LEAF NONNULL((1)) float NOTHROW_NCX(LIBDCALL libd_wcstof)(char16_t const *__restrict nptr, char16_t **endptr);
INTDEF ATTR_LEAF NONNULL((1)) float NOTHROW_NCX(LIBKCALL libc_wcstof)(char32_t const *__restrict nptr, char32_t **endptr);
INTDEF ATTR_LEAF NONNULL((1)) __LONGDOUBLE NOTHROW_NCX(LIBDCALL libd_wcstold)(char16_t const *__restrict nptr, char16_t **endptr);
INTDEF ATTR_LEAF NONNULL((1)) __LONGDOUBLE NOTHROW_NCX(LIBKCALL libc_wcstold)(char32_t const *__restrict nptr, char32_t **endptr);
INTDEF ATTR_LEAF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBDCALL libd_wcstoll)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base);
INTDEF ATTR_LEAF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBKCALL libc_wcstoll)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base);
INTDEF ATTR_LEAF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBDCALL libd_wcstoull)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base);
INTDEF ATTR_LEAF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBKCALL libc_wcstoull)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base);
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
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcsnlen)(char16_t const *__restrict str, size_t maxlen);
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBKCALL libc_wcsnlen)(char32_t const *__restrict str, size_t maxlen);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsdup)(char16_t const *__restrict string);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsdup)(char32_t const *__restrict string);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBDCALL libd_wcwidth)(char16_t ch);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBKCALL libc_wcwidth)(char32_t ch);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_wcswidth)(char16_t const *__restrict str, size_t num_chars);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBKCALL libc_wcswidth)(char32_t const *__restrict str, size_t num_chars);
/* Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcschrnul)(char16_t const *haystack, char16_t needle);
/* Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcschrnul)(char32_t const *haystack, char32_t needle);
INTDEF NONNULL((1)) long NOTHROW_NCX(LIBDCALL libd_wcstol_l)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
INTDEF NONNULL((1)) long NOTHROW_NCX(LIBKCALL libc_wcstol_l)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
INTDEF NONNULL((1)) unsigned long NOTHROW_NCX(LIBDCALL libd_wcstoul_l)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
INTDEF NONNULL((1)) unsigned long NOTHROW_NCX(LIBKCALL libc_wcstoul_l)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
INTDEF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBDCALL libd_wcstoll_l)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
INTDEF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBKCALL libc_wcstoll_l)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
INTDEF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBDCALL libd_wcstoull_l)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
INTDEF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBKCALL libc_wcstoull_l)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
INTDEF NONNULL((1)) float NOTHROW_NCX(LIBDCALL libd_wcstof_l)(char16_t const *__restrict nptr, char16_t **endptr, locale_t locale);
INTDEF NONNULL((1)) float NOTHROW_NCX(LIBKCALL libc_wcstof_l)(char32_t const *__restrict nptr, char32_t **endptr, locale_t locale);
INTDEF NONNULL((1)) double NOTHROW_NCX(LIBDCALL libd_wcstod_l)(char16_t const *__restrict nptr, char16_t **endptr, locale_t locale);
INTDEF NONNULL((1)) double NOTHROW_NCX(LIBKCALL libc_wcstod_l)(char32_t const *__restrict nptr, char32_t **endptr, locale_t locale);
INTDEF NONNULL((1)) __LONGDOUBLE NOTHROW_NCX(LIBDCALL libd_wcstold_l)(char16_t const *__restrict nptr, char16_t **endptr, locale_t locale);
INTDEF NONNULL((1)) __LONGDOUBLE NOTHROW_NCX(LIBKCALL libc_wcstold_l)(char32_t const *__restrict nptr, char32_t **endptr, locale_t locale);
INTDEF wint16_t (LIBDCALL libd_getwchar_unlocked)(void) THROWS(...);
INTDEF wint32_t (LIBKCALL libc_getwchar_unlocked)(void) THROWS(...);
INTDEF wint16_t (LIBDCALL libd_putwchar_unlocked)(char16_t wc) THROWS(...);
INTDEF wint32_t (LIBKCALL libc_putwchar_unlocked)(char32_t wc) THROWS(...);
INTDEF NONNULL((1, 3)) char16_t *(LIBDCALL libd_fgetws_unlocked)(char16_t *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1, 3)) char32_t *(LIBKCALL libc_fgetws_unlocked)(char32_t *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_fputws_unlocked)(char16_t const *__restrict str, FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_fputws_unlocked)(char32_t const *__restrict str, FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1, 3, 4)) size_t NOTHROW_NCX(LIBDCALL libd_wcsftime_l)(char16_t *__restrict buf, size_t maxsize, char16_t const *__restrict format, struct tm const *__restrict tp, locale_t locale);
INTDEF NONNULL((1, 3, 4)) size_t NOTHROW_NCX(LIBKCALL libc_wcsftime_l)(char32_t *__restrict buf, size_t maxsize, char32_t const *__restrict format, struct tm const *__restrict tp, locale_t locale);
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
/* Same as `str+wcslen(str)' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsend)(char16_t const *__restrict str);
/* Same as `str+wcslen(str)' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsend)(char32_t const *__restrict str);
/* Same as `str+wcsnlen(str, max_chars)' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnend)(char16_t const *__restrict str, size_t maxlen);
/* Same as `str+wcsnlen(str, max_chars)' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnend)(char32_t const *__restrict str, size_t maxlen);
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL).  The following errors are  defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly,  and
 *               the  returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supercedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBDCALL libd_wcsto32_r)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL).  The following errors are  defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly,  and
 *               the  returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supercedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBKCALL libc_wcsto32_r)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL).  The following errors are  defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly,  and
 *               the  returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supercedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBDCALL libd_wcstou32_r)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL).  The following errors are  defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly,  and
 *               the  returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supercedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBKCALL libc_wcstou32_r)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBDCALL libd_wcsto32)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base);
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBKCALL libc_wcsto32)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base);
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBDCALL libd_wcstou32)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base);
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBKCALL libc_wcstou32)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base);
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL).  The following errors are  defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly,  and
 *               the  returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supercedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
INTDEF ATTR_LEAF NONNULL((1)) int64_t NOTHROW_NCX(LIBDCALL libd_wcsto64_r)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL).  The following errors are  defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly,  and
 *               the  returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supercedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
INTDEF ATTR_LEAF NONNULL((1)) int64_t NOTHROW_NCX(LIBKCALL libc_wcsto64_r)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL).  The following errors are  defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly,  and
 *               the  returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supercedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBDCALL libd_wcstou64_r)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL).  The following errors are  defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly,  and
 *               the  returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supercedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBKCALL libc_wcstou64_r)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBDCALL libd_wcstou64)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base);
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBKCALL libc_wcstou64)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base);
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
INTDEF ATTR_LEAF NONNULL((1)) int64_t NOTHROW_NCX(LIBDCALL libd_wcsto64)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base);
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
INTDEF ATTR_LEAF NONNULL((1)) int64_t NOTHROW_NCX(LIBKCALL libc_wcsto64)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base);
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBDCALL libd_wcsto32_l)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBKCALL libc_wcsto32_l)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBDCALL libd_wcstou32_l)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBKCALL libc_wcstou32_l)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
INTDEF ATTR_LEAF NONNULL((1)) int64_t NOTHROW_NCX(LIBDCALL libd_wcsto64_l)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
INTDEF ATTR_LEAF NONNULL((1)) int64_t NOTHROW_NCX(LIBKCALL libc_wcsto64_l)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBDCALL libd_wcstou64_l)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBKCALL libc_wcstou64_l)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsncoll)(char16_t const *s1, char16_t const *s2, size_t maxlen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcsncoll)(char32_t const *s1, char32_t const *s2, size_t maxlen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcscasecoll)(char16_t const *s1, char16_t const *s2);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcscasecoll)(char32_t const *s1, char32_t const *s2);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsncasecoll)(char16_t const *s1, char16_t const *s2, size_t maxlen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcsncasecoll)(char32_t const *s1, char32_t const *s2, size_t maxlen);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnrev)(char16_t *__restrict str, size_t maxlen);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnrev)(char32_t *__restrict str, size_t maxlen);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnlwr)(char16_t *__restrict str, size_t maxlen);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnlwr)(char32_t *__restrict str, size_t maxlen);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnupr)(char16_t *__restrict str, size_t maxlen);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnupr)(char32_t *__restrict str, size_t maxlen);
/* >> strcasestr(3)
 * Same as `strstr', but ignore casing */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcscasestr)(char16_t const *haystack, char16_t const *needle);
/* >> strcasestr(3)
 * Same as `strstr', but ignore casing */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcscasestr)(char32_t const *haystack, char32_t const *needle);
/* Same as wcscpy, but return a pointer after the last written character */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcspcpy)(char16_t *__restrict buf, char16_t const *__restrict src);
/* Same as wcscpy, but return a pointer after the last written character */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcspcpy)(char32_t *__restrict buf, char32_t const *__restrict src);
/* Same as wcsncpy, but return a pointer after the last written character */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcspncpy)(char16_t *__restrict buf, char16_t const *__restrict src, size_t buflen);
/* Same as wcsncpy, but return a pointer after the last written character */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcspncpy)(char32_t *__restrict buf, char32_t const *__restrict src, size_t buflen);
/* Same as `wcschr', but don't exceed `max_chars' characters. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnchr)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
/* Same as `wcschr', but don't exceed `max_chars' characters. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnchr)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
/* Same as `wcsrchr', but don't exceed `max_chars' characters. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnrchr)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
/* Same as `wcsrchr', but don't exceed `max_chars' characters. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnrchr)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
INTDEF ATTR_LEAF NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcssep)(char16_t **__restrict stringp, char16_t const *__restrict delim);
INTDEF ATTR_LEAF NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcssep)(char32_t **__restrict stringp, char32_t const *__restrict delim);
/* >> strfry(3) */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsfry)(char16_t *__restrict str);
/* >> strfry(3) */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsfry)(char32_t *__restrict str);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsndup)(char16_t const *__restrict str, size_t max_chars);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsndup)(char32_t const *__restrict str, size_t max_chars);
/* Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsrchrnul)(char16_t const *__restrict haystack, char16_t needle);
/* Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsrchrnul)(char32_t const *__restrict haystack, char32_t needle);
/* Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnchrnul)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
/* Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnchrnul)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
/* Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnrchrnul)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
/* Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnrchrnul)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
/* Same as `wcschrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcsoff)(char16_t const *__restrict haystack, char16_t needle);
/* Same as `wcschrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBKCALL libc_wcsoff)(char32_t const *__restrict haystack, char32_t needle);
/* Same as `wcsrchrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcsroff)(char16_t const *__restrict haystack, char16_t needle);
/* Same as `wcsrchrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBKCALL libc_wcsroff)(char32_t const *__restrict haystack, char32_t needle);
/* Same as `wcsnchrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcsnoff)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
/* Same as `wcsnchrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBKCALL libc_wcsnoff)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
/* Same as `wcsnrchrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_wcsnroff)(char16_t const *__restrict haystack, char16_t needle, size_t maxlen);
/* Same as `wcsnrchrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBKCALL libc_wcsnroff)(char32_t const *__restrict haystack, char32_t needle, size_t maxlen);
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
/* >> strverscmp(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsverscmp)(char16_t const *s1, char16_t const *s2);
/* >> strverscmp(3) */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcsverscmp)(char32_t const *s1, char32_t const *s2);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsncoll_l)(char16_t const *s1, char16_t const *s2, size_t maxlen, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcsncoll_l)(char32_t const *s1, char32_t const *s2, size_t maxlen, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcscasecoll_l)(char16_t const *s1, char16_t const *s2, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcscasecoll_l)(char32_t const *s1, char32_t const *s2, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wcsncasecoll_l)(char16_t const *s1, char16_t const *s2, size_t maxlen, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wcsncasecoll_l)(char32_t const *s1, char32_t const *s2, size_t maxlen, locale_t locale);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcslwr_l)(char16_t *__restrict str, locale_t locale);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcslwr_l)(char32_t *__restrict str, locale_t locale);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsupr_l)(char16_t *__restrict str, locale_t locale);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsupr_l)(char32_t *__restrict str, locale_t locale);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnlwr_l)(char16_t *__restrict str, size_t maxlen, locale_t locale);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnlwr_l)(char32_t *__restrict str, size_t maxlen, locale_t locale);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnupr_l)(char16_t *__restrict str, size_t maxlen, locale_t locale);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnupr_l)(char32_t *__restrict str, size_t maxlen, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcscasestr_l)(char16_t const *haystack, char16_t const *needle, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcscasestr_l)(char32_t const *haystack, char32_t const *needle, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wmemcasecmp_l)(char16_t const *s1, size_t s1_bytes, char16_t const *s2, size_t s2_bytes, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBKCALL libc_fuzzy_wmemcasecmp_l)(char32_t const *s1, size_t s1_bytes, char32_t const *s2, size_t s2_bytes, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wcscasecmp_l)(char16_t const *s1, char16_t const *s2, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBKCALL libc_fuzzy_wcscasecmp_l)(char32_t const *s1, char32_t const *s2, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_wcsncasecmp_l)(char16_t const *s1, size_t s1_maxlen, char16_t const *s2, size_t s2_maxlen, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBKCALL libc_fuzzy_wcsncasecmp_l)(char32_t const *s1, size_t s1_maxlen, char32_t const *s2, size_t s2_maxlen, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_wildwcscasecmp_l)(char16_t const *pattern, char16_t const *string, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc_wildwcscasecmp_l)(char32_t const *pattern, char32_t const *string, locale_t locale);
INTDEF ATTR_LEAF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_wcslcat)(char16_t *__restrict dst, char16_t const *__restrict src, size_t bufsize);
INTDEF ATTR_LEAF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBKCALL libc_wcslcat)(char32_t *__restrict dst, char32_t const *__restrict src, size_t bufsize);
INTDEF ATTR_LEAF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_wcslcpy)(char16_t *__restrict dst, char16_t const *__restrict src, size_t bufsize);
INTDEF ATTR_LEAF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBKCALL libc_wcslcpy)(char32_t *__restrict dst, char32_t const *__restrict src, size_t bufsize);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_wcscat_s)(char16_t *dst, size_t dstsize, char16_t const *src);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc_wcscat_s)(char32_t *dst, size_t dstsize, char32_t const *src);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_wcscpy_s)(char16_t *dst, size_t dstsize, char16_t const *src);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc_wcscpy_s)(char32_t *dst, size_t dstsize, char32_t const *src);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_wcsncat_s)(char16_t *dst, rsize_t dstsize, const char16_t *src, rsize_t maxlen);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc_wcsncat_s)(char32_t *dst, rsize_t dstsize, const char32_t *src, rsize_t maxlen);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_wcsncpy_s)(char16_t *dst, size_t dstsize, char16_t const *src, size_t maxlen);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc_wcsncpy_s)(char32_t *dst, size_t dstsize, char32_t const *src, size_t maxlen);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__wcsnset_s)(char16_t *__restrict buf, size_t buflen, char16_t ch, size_t maxlen);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc__wcsnset_s)(char32_t *__restrict buf, size_t buflen, char32_t ch, size_t maxlen);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd__wcsset_s)(char16_t *dst, size_t dstsize, char16_t ch);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBKCALL libc__wcsset_s)(char32_t *dst, size_t dstsize, char32_t ch);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__wcslwr_s)(char16_t *buf, size_t buflen);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc__wcslwr_s)(char32_t *buf, size_t buflen);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__wcsupr_s)(char16_t *buf, size_t buflen);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc__wcsupr_s)(char32_t *buf, size_t buflen);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__wcslwr_s_l)(char16_t *buf, size_t buflen, locale_t locale);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc__wcslwr_s_l)(char32_t *buf, size_t buflen, locale_t locale);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__wcsupr_s_l)(char16_t *buf, size_t buflen, locale_t locale);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc__wcsupr_s_l)(char32_t *buf, size_t buflen, locale_t locale);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBDCALL libd_wmemcpy_s)(char16_t *dst, rsize_t dstlength, char16_t const *src, rsize_t srclength);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBKCALL libc_wmemcpy_s)(char32_t *dst, rsize_t dstlength, char32_t const *src, rsize_t srclength);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBDCALL libd_wmemmove_s)(char16_t *dst, rsize_t dstlength, char16_t const *src, rsize_t srclength);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBKCALL libc_wmemmove_s)(char32_t *dst, rsize_t dstlength, char32_t const *src, rsize_t srclength);
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsnset)(char16_t *__restrict str, char16_t ch, size_t maxlen);
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsnset)(char32_t *__restrict str, char32_t ch, size_t maxlen);
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsrev)(char16_t *__restrict str);
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsrev)(char32_t *__restrict str);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsset)(char16_t *__restrict str, int ch);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsset)(char32_t *__restrict str, int ch);
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcslwr)(char16_t *__restrict str);
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcslwr)(char32_t *__restrict str);
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_wcsupr)(char16_t *__restrict str);
INTDEF ATTR_RETNONNULL NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc_wcsupr)(char32_t *__restrict str);
INTDEF WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vscwprintf)(char16_t const *format, va_list args);
INTDEF WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc__vscwprintf)(char32_t const *format, va_list args);
INTDEF WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__scwprintf)(char16_t const *format, ...);
INTDEF WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBKCALL libc__scwprintf)(char32_t const *format, ...);
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
INTDEF NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd__putws)(char16_t const *str);
INTDEF NONNULL((1)) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBKCALL libc__putws)(char32_t const *str);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_WCHAR_H */
