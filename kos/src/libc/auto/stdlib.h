/* HASH 0xf640e51c */
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
#ifndef GUARD_LIBC_AUTO_STDLIB_H
#define GUARD_LIBC_AUTO_STDLIB_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <stdlib.h>
#include <kos/anno.h>

DECL_BEGIN

INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBCCALL libc_strtou32)(char const *__restrict nptr, char **endptr, int base);
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBCCALL libc_strto32)(char const *__restrict nptr, char **endptr, int base);
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBCCALL libc_strtou64)(char const *__restrict nptr, char **endptr, int base);
INTDEF ATTR_LEAF NONNULL((1)) int64_t NOTHROW_NCX(LIBCCALL libc_strto64)(char const *__restrict nptr, char **endptr, int base);
#ifndef __KERNEL__
INTDEF NONNULL((1, 4)) void (LIBCCALL libc_qsort_r)(void *pbase, size_t item_count, size_t item_size, __compar_d_fn_t cmp, void *arg) __THROWS(...);
INTDEF NONNULL((1, 2, 5)) WUNUSED void *NOTHROW_NCX(LIBCCALL libc_bsearch_r)(void const *pkey, void const *pbase, size_t item_count, size_t item_size, __compar_d_fn_t cmp, void *arg);
INTDEF NONNULL((1, 4)) void (LIBCCALL libc_qsort)(void *pbase, size_t item_count, size_t item_size, __compar_fn_t cmp) __THROWS(...);
INTDEF NONNULL((1, 2, 5)) WUNUSED void *NOTHROW_NCX(LIBCCALL libc_bsearch)(void const *pkey, void const *pbase, size_t item_count, size_t item_size, __compar_fn_t cmp);
INTDEF ATTR_CONST WUNUSED long NOTHROW(LIBCCALL libc_labs)(long x);
INTDEF ATTR_CONST WUNUSED __LONGLONG NOTHROW(LIBCCALL libc_llabs)(__LONGLONG x);
INTDEF ATTR_CONST WUNUSED ldiv_t NOTHROW_NCX(LIBCCALL libc_ldiv)(long numer, long denom);
INTDEF ATTR_CONST WUNUSED lldiv_t NOTHROW_NCX(LIBCCALL libc_lldiv)(__LONGLONG numer, __LONGLONG denom);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_abs)(int x);
INTDEF ATTR_CONST WUNUSED div_t NOTHROW_NCX(LIBCCALL libc_div)(int numer, int denom);
INTDEF int NOTHROW_NCX(LIBCCALL libc_mblen)(char const *s, size_t n);
INTDEF int NOTHROW_NCX(LIBCCALL libc_mbtowc)(char32_t *__restrict pwc, char const *__restrict s, size_t n);
INTDEF int NOTHROW_NCX(LIBDCALL libd_mbtowc)(char16_t *__restrict pwc, char const *__restrict s, size_t n);
INTDEF int NOTHROW_NCX(LIBCCALL libc_wctomb)(char *s, char32_t wchar);
INTDEF int NOTHROW_NCX(LIBDCALL libd_wctomb)(char *s, char16_t wchar);
INTDEF size_t NOTHROW_NCX(LIBCCALL libc_mbstowcs)(char32_t *__restrict pwcs, char const *__restrict src, size_t maxlen);
INTDEF size_t NOTHROW_NCX(LIBDCALL libd_mbstowcs)(char16_t *__restrict pwcs, char const *__restrict src, size_t maxlen);
INTDEF size_t NOTHROW_NCX(LIBCCALL libc_wcstombs)(char *__restrict s, char32_t const *__restrict pwcs, size_t n);
INTDEF size_t NOTHROW_NCX(LIBDCALL libd_wcstombs)(char *__restrict s, char16_t const *__restrict pwcs, size_t n);
INTDEF void NOTHROW(LIBCCALL libc_srand)(long seed);
INTDEF int NOTHROW(LIBCCALL libc_rand)(void);
INTDEF ATTR_PURE NONNULL((1)) WUNUSED int NOTHROW_NCX(LIBCCALL libc_atoi)(char const *__restrict nptr);
INTDEF ATTR_PURE NONNULL((1)) WUNUSED long NOTHROW_NCX(LIBCCALL libc_atol)(char const *__restrict nptr);
INTDEF ATTR_PURE NONNULL((1)) WUNUSED __LONGLONG NOTHROW_NCX(LIBCCALL libc_atoll)(char const *__restrict nptr);
INTDEF ATTR_LEAF NONNULL((1)) unsigned long NOTHROW_NCX(LIBCCALL libc_strtoul)(char const *__restrict nptr, char **endptr, int base);
INTDEF ATTR_LEAF NONNULL((1)) long NOTHROW_NCX(LIBCCALL libc_strtol)(char const *__restrict nptr, char **endptr, int base);
INTDEF ATTR_LEAF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBCCALL libc_strtoull)(char const *__restrict nptr, char **endptr, int base);
INTDEF ATTR_LEAF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBCCALL libc_strtoll)(char const *__restrict nptr, char **endptr, int base);
INTDEF ATTR_LEAF WUNUSED NONNULL((1)) double NOTHROW_NCX(LIBCCALL libc_atof)(char const *__restrict nptr);
INTDEF ATTR_LEAF NONNULL((1)) double NOTHROW_NCX(LIBCCALL libc_strtod)(char const *__restrict nptr, char **endptr);
INTDEF ATTR_LEAF NONNULL((1)) float NOTHROW_NCX(LIBCCALL libc_strtof)(char const *__restrict nptr, char **endptr);
INTDEF ATTR_LEAF NONNULL((1)) long double NOTHROW_NCX(LIBCCALL libc_strtold)(char const *__restrict nptr, char **endptr);
#define libc_strtoq libc_strtoll
#define libc_strtouq libc_strtoull
INTDEF WUNUSED NONNULL((3)) char *NOTHROW_NCX(LIBCCALL libc_gcvt)(double val, int ndigit, char *buf);
INTDEF NONNULL((3, 4, 5)) int NOTHROW_NCX(LIBCCALL libc_ecvt_r)(double val, int ndigit, int *__restrict decptr, int *__restrict sign, char *__restrict buf, size_t len);
INTDEF NONNULL((3, 4, 5)) int NOTHROW_NCX(LIBCCALL libc_fcvt_r)(double val, int ndigit, int *__restrict decptr, int *__restrict sign, char *__restrict buf, size_t len);
INTDEF NONNULL((3)) char *NOTHROW_NCX(LIBCCALL libc_qgcvt)(long double val, int ndigit, char *buf);
INTDEF NONNULL((3, 4, 5)) int NOTHROW_NCX(LIBCCALL libc_qecvt_r)(long double val, int ndigit, int *__restrict decptr, int *__restrict sign, char *__restrict buf, size_t len);
INTDEF NONNULL((3, 4, 5)) int NOTHROW_NCX(LIBCCALL libc_qfcvt_r)(long double val, int ndigit, int *__restrict decptr, int *__restrict sign, char *__restrict buf, size_t len);
INTDEF WUNUSED NONNULL((3, 4)) char *NOTHROW_NCX(LIBCCALL libc_qecvt)(long double val, int ndigit, int *__restrict decptr, int *__restrict sign);
INTDEF WUNUSED NONNULL((3, 4)) char *NOTHROW_NCX(LIBCCALL libc_qfcvt)(long double val, int ndigit, int *__restrict decptr, int *__restrict sign);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_rand_r)(unsigned int *__restrict seed);
INTDEF long NOTHROW_NCX(LIBCCALL libc_random)(void);
INTDEF void NOTHROW_NCX(LIBCCALL libc_srandom)(unsigned int seed);
INTDEF WUNUSED NONNULL((3, 4)) char *NOTHROW_NCX(LIBCCALL libc_ecvt)(double val, int ndigit, int *__restrict decptr, int *__restrict sign);
INTDEF WUNUSED NONNULL((3, 4)) char *NOTHROW_NCX(LIBCCALL libc_fcvt)(double val, int ndigit, int *__restrict decptr, int *__restrict sign);
INTDEF WUNUSED NONNULL((1, 2, 3)) int NOTHROW_NCX(LIBCCALL libc_getsubopt)(char **__restrict optionp, char *const *__restrict tokens, char **__restrict valuep);
INTDEF NONNULL((1)) long NOTHROW_NCX(LIBCCALL libc_strtol_l)(char const *__restrict nptr, char **endptr, int base, locale_t locale);
INTDEF NONNULL((1)) unsigned long NOTHROW_NCX(LIBCCALL libc_strtoul_l)(char const *__restrict nptr, char **endptr, int base, locale_t locale);
INTDEF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBCCALL libc_strtoll_l)(char const *__restrict nptr, char **endptr, int base, locale_t locale);
INTDEF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBCCALL libc_strtoull_l)(char const *__restrict nptr, char **endptr, int base, locale_t locale);
INTDEF NONNULL((1)) double NOTHROW_NCX(LIBCCALL libc_strtod_l)(char const *__restrict nptr, char **endptr, locale_t locale);
INTDEF NONNULL((1)) float NOTHROW_NCX(LIBCCALL libc_strtof_l)(char const *__restrict nptr, char **endptr, locale_t locale);
INTDEF NONNULL((1)) long double NOTHROW_NCX(LIBCCALL libc_strtold_l)(char const *__restrict nptr, char **endptr, locale_t locale);
INTDEF ATTR_CONST WUNUSED __INT64_TYPE__ NOTHROW(LIBCCALL libc__abs64)(__INT64_TYPE__ x);
INTDEF WUNUSED ATTR_PURE NONNULL((1)) double NOTHROW_NCX(LIBCCALL libc__atof_l)(char const *__restrict nptr, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc__atoi_l)(char const *__restrict nptr, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1)) long int NOTHROW_NCX(LIBCCALL libc__atol_l)(char const *__restrict nptr, locale_t locale);
INTDEF WUNUSED ATTR_PURE NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBCCALL libc__atoll_l)(char const *__restrict nptr, locale_t locale);
INTDEF ATTR_CONST WUNUSED u16 NOTHROW_NCX(LIBCCALL libc__byteswap_ushort)(u16 val);
INTDEF ATTR_CONST WUNUSED u32 NOTHROW_NCX(LIBCCALL libc__byteswap_ulong)(u32 val);
INTDEF ATTR_CONST WUNUSED u64 NOTHROW_NCX(LIBCCALL libc__byteswap_uint64)(u64 val);
INTDEF NONNULL((1, 2, 5)) WUNUSED void *NOTHROW_NCX(LIBCCALL libc_bsearch_s)(void const *key, void const *base, size_t nmemb, size_t size, __dos_compar_d_fn_t compar, void *arg);
INTDEF NONNULL((1, 4)) void NOTHROW_NCX(LIBCCALL libc_qsort_s)(void *base, size_t nmemb, size_t size, __dos_compar_d_fn_t compar, void *arg);
#define libc__itoa libc_itoa
#define libc__ltoa libc_ltoa
#define libc__ultoa libc_ultoa
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc__itoa_s)(int val, char *buf, size_t bufsize, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc__ltoa_s)(long val, char *buf, size_t bufsize, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc__ultoa_s)(unsigned long val, char *buf, size_t bufsize, int radix);
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc__i64toa)(s64 val, char *buf, int radix);
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc__ui64toa)(u64 val, char *buf, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc__i64toa_s)(s64 val, char *buf, size_t bufsize, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc__ui64toa_s)(u64 val, char *buf, size_t bufsize, int radix);
#define libc__strtoi64 libc_strto64
#define libc__strtoui64 libc_strtou64
#define libc__strtoi64_l libc_strto64_l
#define libc__strtoui64_l libc_strtou64_l
INTDEF ATTR_PURE NONNULL((1)) WUNUSED s64 NOTHROW_NCX(LIBCCALL libc__atoi64)(char const *__restrict nptr);
INTDEF ATTR_PURE NONNULL((1)) WUNUSED s64 NOTHROW_NCX(LIBCCALL libc__atoi64_l)(char const *__restrict nptr, locale_t locale);
INTDEF ATTR_PURE NONNULL((1)) WUNUSED size_t NOTHROW_NCX(LIBCCALL libc__mbstrlen)(char const *str);
INTDEF ATTR_PURE NONNULL((1)) WUNUSED size_t NOTHROW_NCX(LIBCCALL libc__mbstrnlen)(char const *str, size_t maxlen);
INTDEF ATTR_PURE NONNULL((1)) WUNUSED size_t NOTHROW_NCX(LIBCCALL libc__mbstrlen_l)(char const *str, locale_t locale);
INTDEF ATTR_PURE NONNULL((1)) WUNUSED size_t NOTHROW_NCX(LIBCCALL libc__mbstrnlen_l)(char const *str, size_t maxlen, locale_t locale);
INTDEF ATTR_PURE NONNULL((1)) WUNUSED int NOTHROW_NCX(LIBCCALL libc__mblen_l)(char const *str, size_t maxlen, locale_t locale);
INTDEF int NOTHROW_NCX(LIBCCALL libc__mbtowc_l)(char32_t *dst, char const *src, size_t srclen, locale_t locale);
INTDEF int NOTHROW_NCX(LIBDCALL libd__mbtowc_l)(char16_t *dst, char const *src, size_t srclen, locale_t locale);
INTDEF size_t NOTHROW_NCX(LIBCCALL libc__mbstowcs_l)(char32_t *buf, char const *src, size_t maxlen, locale_t locale);
INTDEF size_t NOTHROW_NCX(LIBDCALL libd__mbstowcs_l)(char16_t *buf, char const *src, size_t maxlen, locale_t locale);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__mbstowcs_s)(size_t *presult, char32_t *buf, size_t buflen, char const *src, size_t maxlen);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__mbstowcs_s)(size_t *presult, char16_t *buf, size_t buflen, char const *src, size_t maxlen);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__mbstowcs_s_l)(size_t *presult, char32_t *buf, size_t buflen, char const *src, size_t maxlen, locale_t locale);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__mbstowcs_s_l)(size_t *presult, char16_t *buf, size_t buflen, char const *src, size_t maxlen, locale_t locale);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_rand_s)(unsigned int *__restrict randval);
#define libc__strtol_l libc_strtol_l
#define libc__strtoul_l libc_strtoul_l
#define libc__strtoll_l libc_strtoll_l
#define libc__strtoull_l libc_strtoull_l
#define libc__strtod_l libc_strtod_l
#define libc__strtof_l libc_strtof_l
#define libc__strtold_l libc_strtold_l
INTDEF int NOTHROW_NCX(LIBCCALL libc__wctomb_l)(char *buf, char32_t wc, locale_t locale);
INTDEF int NOTHROW_NCX(LIBDCALL libd__wctomb_l)(char *buf, char16_t wc, locale_t locale);
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc_wctomb_s)(int *presult, char *buf, rsize_t buflen, char32_t wc);
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc__wctomb_s_l)(int *presult, char *buf, size_t buflen, char32_t wc, locale_t locale);
INTDEF NONNULL((1, 2, 4)) errno_t NOTHROW_NCX(LIBCCALL libc__wcstombs_s_l)(size_t *presult, char *buf, size_t buflen, char32_t const *src, size_t maxlen, locale_t locale);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBCCALL libc__wcstombs_l)(char *dst, char32_t const *src, size_t maxlen, locale_t locale);
INTDEF NONNULL((1, 2, 4)) errno_t NOTHROW_NCX(LIBCCALL libc_wcstombs_s)(size_t *presult, char *buf, size_t buflen, char32_t const *src, size_t maxlen);
INTDEF WUNUSED size_t NOTHROW_NCX(LIBCCALL libc__aligned_msize)(void *mptr, size_t min_alignment, size_t offset);
INTDEF NONNULL((1, 5, 6)) errno_t NOTHROW_NCX(LIBCCALL libc__ecvt_s)(char *buf, size_t buflen, double val, int ndigit, int *__restrict decptr, int *__restrict sign);
INTDEF NONNULL((1, 5, 6)) errno_t NOTHROW_NCX(LIBCCALL libc__fcvt_s)(char *buf, size_t buflen, double val, int ndigit, int *__restrict decptr, int *__restrict sign);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc__gcvt_s)(char *buf, size_t buflen, double val, int ndigit);
#define libc__ecvt libc_ecvt
#define libc__fcvt libc_fcvt
#define libc__gcvt libc_gcvt
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__atoflt)(float *__restrict result, char const *__restrict nptr);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__atoflt_l)(float *__restrict result, char const *__restrict nptr, locale_t locale);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__atodbl)(double *__restrict result, char __KOS_FIXED_CONST *__restrict nptr);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__atodbl_l)(double *__restrict result, char __KOS_FIXED_CONST *__restrict nptr, locale_t locale);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__atoldbl)(long double *__restrict result, char __KOS_FIXED_CONST *__restrict nptr);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__atoldbl_l)(long double *__restrict result, char __KOS_FIXED_CONST *__restrict nptr, locale_t locale);
INTDEF ATTR_CONST unsigned int NOTHROW(LIBCCALL libc__rotl)(unsigned int val, int shift);
INTDEF ATTR_CONST unsigned int NOTHROW(LIBCCALL libc__rotr)(unsigned int val, int shift);
INTDEF ATTR_CONST u64 NOTHROW(LIBCCALL libc__rotl64)(u64 val, int shift);
INTDEF ATTR_CONST u64 NOTHROW(LIBCCALL libc__rotr64)(u64 val, int shift);
INTDEF ATTR_CONST unsigned long NOTHROW(LIBCCALL libc__lrotl)(unsigned long val, int shift);
INTDEF ATTR_CONST unsigned long NOTHROW(LIBCCALL libc__lrotr)(unsigned long val, int shift);
/* Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
#define libc__swab libc_swab
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc__makepath)(char *__restrict buf, char const *drive, char const *dir, char const *file, char const *ext);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc__splitpath)(char const *__restrict abspath, char *drive, char *dir, char *file, char *ext);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc__makepath_s)(char *buf, size_t buflen, char const *drive, char const *dir, char const *file, char const *ext);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc__splitpath_s)(char const *__restrict abspath, char *drive, size_t drivelen, char *dir, size_t dirlen, char *file, size_t filelen, char *ext, size_t extlen);
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc_itoa)(int val, char *dst, int radix);
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc_ltoa)(long val, char *dst, int radix);
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc_ultoa)(unsigned long val, char *dst, int radix);
INTDEF NONNULL((1)) s64 NOTHROW_NCX(LIBCCALL libc_strto64_l)(char const *__restrict nptr, char **endptr, int base, locale_t locale);
INTDEF NONNULL((1)) u64 NOTHROW_NCX(LIBCCALL libc_strtou64_l)(char const *__restrict nptr, char **endptr, int base, locale_t locale);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_STDLIB_H */
