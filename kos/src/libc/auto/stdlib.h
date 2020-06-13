/* HASH CRC-32:0x102a593 */
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
#ifndef GUARD_LIBC_AUTO_STDLIB_H
#define GUARD_LIBC_AUTO_STDLIB_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <stdlib.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF NONNULL((1, 4)) void (LIBCCALL libc_qsort_r)(void *pbase, size_t item_count, size_t item_size, __compar_d_fn_t cmp, void *arg) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) void *(LIBCCALL libc_bsearch_r)(void const *pkey, void const *pbase, size_t item_count, size_t item_size, __compar_d_fn_t cmp, void *arg) THROWS(...);
INTDEF NONNULL((1, 4)) void (LIBCCALL libc_qsort)(void *pbase, size_t item_count, size_t item_size, __compar_fn_t cmp) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) void *(LIBCCALL libc_bsearch)(void const *pkey, void const *pbase, size_t item_count, size_t item_size, __compar_fn_t cmp) THROWS(...);
INTDEF ATTR_CONST WUNUSED long NOTHROW(LIBCCALL libc_labs)(long x);
INTDEF ATTR_CONST WUNUSED __LONGLONG NOTHROW(LIBCCALL libc_llabs)(__LONGLONG x);
INTDEF ATTR_CONST WUNUSED ldiv_t NOTHROW_NCX(LIBCCALL libc_ldiv)(long numer, long denom);
INTDEF ATTR_CONST WUNUSED lldiv_t NOTHROW_NCX(LIBCCALL libc_lldiv)(__LONGLONG numer, __LONGLONG denom);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_abs)(int x);
INTDEF ATTR_CONST WUNUSED struct __div_struct NOTHROW_NCX(LIBCCALL libc_div)(int numer, int denom);
INTDEF int NOTHROW_NCX(LIBCCALL libc_mblen)(char const *str, size_t maxlen);
INTDEF int NOTHROW_NCX(LIBDCALL libd_mbtowc)(char16_t *__restrict pwc, char const *__restrict str, size_t maxlen);
INTDEF int NOTHROW_NCX(LIBKCALL libc_mbtowc)(char32_t *__restrict pwc, char const *__restrict str, size_t maxlen);
INTDEF int NOTHROW_NCX(LIBDCALL libd_wctomb)(char *str, char16_t wc);
INTDEF int NOTHROW_NCX(LIBKCALL libc_wctomb)(char *str, char32_t wc);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_mbstowcs)(char16_t *__restrict dst, char const *__restrict src, size_t dstlen);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBKCALL libc_mbstowcs)(char32_t *__restrict dst, char const *__restrict src, size_t dstlen);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_wcstombs)(char *__restrict dst, char16_t const *__restrict src, size_t dstlen);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBKCALL libc_wcstombs)(char *__restrict dst, char32_t const *__restrict src, size_t dstlen);
INTDEF ATTR_NORETURN void (LIBCCALL libc_abort)(void) THROWS(...);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_atoi)(char const *__restrict nptr);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) long NOTHROW_NCX(LIBCCALL libc_atol)(char const *__restrict nptr);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBCCALL libc_atoll)(char const *__restrict nptr);
INTDEF ATTR_LEAF NONNULL((1)) unsigned long NOTHROW_NCX(LIBCCALL libc_strtoul)(char const *__restrict nptr, char **endptr, int base);
INTDEF ATTR_LEAF NONNULL((1)) long NOTHROW_NCX(LIBCCALL libc_strtol)(char const *__restrict nptr, char **endptr, int base);
INTDEF ATTR_LEAF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBCCALL libc_strtoull)(char const *__restrict nptr, char **endptr, int base);
INTDEF ATTR_LEAF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBCCALL libc_strtoll)(char const *__restrict nptr, char **endptr, int base);
INTDEF ATTR_LEAF WUNUSED NONNULL((1)) double NOTHROW_NCX(LIBCCALL libc_atof)(char const *__restrict nptr);
INTDEF ATTR_LEAF NONNULL((1)) double NOTHROW_NCX(LIBCCALL libc_strtod)(char const *__restrict nptr, char **endptr);
INTDEF ATTR_LEAF NONNULL((1)) float NOTHROW_NCX(LIBCCALL libc_strtof)(char const *__restrict nptr, char **endptr);
INTDEF ATTR_LEAF NONNULL((1)) __LONGDOUBLE NOTHROW_NCX(LIBCCALL libc_strtold)(char const *__restrict nptr, char **endptr);
#endif /* !__KERNEL__ */
INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBCCALL libc_strtou32)(char const *__restrict nptr, char **endptr, int base);
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBCCALL libc_strto32)(char const *__restrict nptr, char **endptr, int base);
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBCCALL libc_strtou64)(char const *__restrict nptr, char **endptr, int base);
INTDEF ATTR_LEAF NONNULL((1)) int64_t NOTHROW_NCX(LIBCCALL libc_strto64)(char const *__restrict nptr, char **endptr, int base);
#ifndef __KERNEL__
INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBCCALL libc_strtou32_l)(char const *__restrict nptr, char **endptr, int base, locale_t locale);
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBCCALL libc_strto32_l)(char const *__restrict nptr, char **endptr, int base, locale_t locale);
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBCCALL libc_strtou64_l)(char const *__restrict nptr, char **endptr, int base, locale_t locale);
INTDEF ATTR_LEAF NONNULL((1)) int64_t NOTHROW_NCX(LIBCCALL libc_strto64_l)(char const *__restrict nptr, char **endptr, int base, locale_t locale);
INTDEF WUNUSED NONNULL((3)) char *NOTHROW_NCX(LIBCCALL libc_gcvt)(double val, int ndigit, char *buf);
INTDEF NONNULL((3, 4, 5)) int NOTHROW_NCX(LIBCCALL libc_ecvt_r)(double val, int ndigit, int *__restrict decptr, int *__restrict sign, char *__restrict buf, size_t len);
INTDEF NONNULL((3, 4, 5)) int NOTHROW_NCX(LIBCCALL libc_fcvt_r)(double val, int ndigit, int *__restrict decptr, int *__restrict sign, char *__restrict buf, size_t len);
INTDEF NONNULL((3)) char *NOTHROW_NCX(LIBCCALL libc_qgcvt)(__LONGDOUBLE val, int ndigit, char *buf);
INTDEF NONNULL((3, 4, 5)) int NOTHROW_NCX(LIBCCALL libc_qecvt_r)(__LONGDOUBLE val, int ndigit, int *__restrict decptr, int *__restrict sign, char *__restrict buf, size_t len);
INTDEF NONNULL((3, 4, 5)) int NOTHROW_NCX(LIBCCALL libc_qfcvt_r)(__LONGDOUBLE val, int ndigit, int *__restrict decptr, int *__restrict sign, char *__restrict buf, size_t len);
INTDEF WUNUSED NONNULL((3, 4)) char *NOTHROW_NCX(LIBCCALL libc_qecvt)(__LONGDOUBLE val, int ndigit, int *__restrict decptr, int *__restrict sign);
INTDEF WUNUSED NONNULL((3, 4)) char *NOTHROW_NCX(LIBCCALL libc_qfcvt)(__LONGDOUBLE val, int ndigit, int *__restrict decptr, int *__restrict sign);
INTDEF WUNUSED NONNULL((3, 4)) char *NOTHROW_NCX(LIBCCALL libc_ecvt)(double val, int ndigit, int *__restrict decptr, int *__restrict sign);
INTDEF WUNUSED NONNULL((3, 4)) char *NOTHROW_NCX(LIBCCALL libc_fcvt)(double val, int ndigit, int *__restrict decptr, int *__restrict sign);
INTDEF WUNUSED NONNULL((1, 2, 3)) int NOTHROW_NCX(LIBCCALL libc_getsubopt)(char **__restrict optionp, char *const *__restrict tokens, char **__restrict valuep);
INTDEF NONNULL((1)) long NOTHROW_NCX(LIBCCALL libc_strtol_l)(char const *__restrict nptr, char **endptr, int base, locale_t locale);
INTDEF NONNULL((1)) unsigned long NOTHROW_NCX(LIBCCALL libc_strtoul_l)(char const *__restrict nptr, char **endptr, int base, locale_t locale);
INTDEF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBCCALL libc_strtoll_l)(char const *__restrict nptr, char **endptr, int base, locale_t locale);
INTDEF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBCCALL libc_strtoull_l)(char const *__restrict nptr, char **endptr, int base, locale_t locale);
INTDEF NONNULL((1)) double NOTHROW_NCX(LIBCCALL libc_strtod_l)(char const *__restrict nptr, char **endptr, locale_t locale);
INTDEF NONNULL((1)) float NOTHROW_NCX(LIBCCALL libc_strtof_l)(char const *__restrict nptr, char **endptr, locale_t locale);
INTDEF NONNULL((1)) __LONGDOUBLE NOTHROW_NCX(LIBCCALL libc_strtold_l)(char const *__restrict nptr, char **endptr, locale_t locale);
/* Alias for argv[0], as passed to main() */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char **NOTHROW_NCX(LIBCCALL libc___p__pgmptr)(void);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__get_pgmptr)(char **pvalue);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__get_wpgmptr)(char16_t **pvalue);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc__get_wpgmptr)(char32_t **pvalue);
INTDEF ATTR_CONST WUNUSED __INT64_TYPE__ NOTHROW(LIBCCALL libc__abs64)(__INT64_TYPE__ x);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) double NOTHROW_NCX(LIBCCALL libc__atof_l)(char const *__restrict nptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc__atoi_l)(char const *__restrict nptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) long int NOTHROW_NCX(LIBCCALL libc__atol_l)(char const *__restrict nptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBCCALL libc__atoll_l)(char const *__restrict nptr, locale_t locale);
INTDEF ATTR_CONST WUNUSED u16 NOTHROW_NCX(LIBCCALL libc__byteswap_ushort)(u16 val);
INTDEF ATTR_CONST WUNUSED u32 NOTHROW_NCX(LIBCCALL libc__byteswap_ulong)(u32 val);
INTDEF ATTR_CONST WUNUSED u64 NOTHROW_NCX(LIBCCALL libc__byteswap_uint64)(u64 val);
INTDEF WUNUSED NONNULL((1, 2, 5)) void *(LIBCCALL libc_bsearch_s)(void const *key, void const *base, size_t nmemb, size_t size, __dos_compar_d_fn_t compar, void *arg) THROWS(...);
INTDEF NONNULL((1, 4)) void (LIBCCALL libc_qsort_s)(void *base, size_t nmemb, size_t size, __dos_compar_d_fn_t compar, void *arg) THROWS(...);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc__itoa_s)(int val, char *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc__ltoa_s)(long val, char *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc__ultoa_s)(unsigned long val, char *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc__i64toa)(s64 val, char *buf, int radix);
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc__ui64toa)(u64 val, char *buf, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc__i64toa_s)(s64 val, char *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc__ui64toa_s)(u64 val, char *buf, size_t buflen, int radix);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) s64 NOTHROW_NCX(LIBCCALL libc__atoi64)(char const *__restrict nptr);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) s64 NOTHROW_NCX(LIBCCALL libc__atoi64_l)(char const *__restrict nptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc__mbstrlen)(char const *str);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc__mbstrnlen)(char const *str, size_t maxlen);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc__mbstrlen_l)(char const *str, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc__mbstrnlen_l)(char const *str, size_t maxlen, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc__mblen_l)(char const *str, size_t maxlen, locale_t locale);
INTDEF int NOTHROW_NCX(LIBDCALL libd__mbtowc_l)(char16_t *dst, char const *src, size_t srclen, locale_t locale);
INTDEF int NOTHROW_NCX(LIBKCALL libc__mbtowc_l)(char32_t *dst, char const *src, size_t srclen, locale_t locale);
INTDEF size_t NOTHROW_NCX(LIBDCALL libd__mbstowcs_l)(char16_t *dst, char const *src, size_t dstlen, locale_t locale);
INTDEF size_t NOTHROW_NCX(LIBKCALL libc__mbstowcs_l)(char32_t *dst, char const *src, size_t dstlen, locale_t locale);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__mbstowcs_s)(size_t *presult, char16_t *dst, size_t dstsize, char const *src, size_t dstlen);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc__mbstowcs_s)(size_t *presult, char32_t *dst, size_t dstsize, char const *src, size_t dstlen);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__mbstowcs_s_l)(size_t *presult, char16_t *dst, size_t dstsize, char const *src, size_t dstlen, locale_t locale);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc__mbstowcs_s_l)(size_t *presult, char32_t *dst, size_t dstsize, char const *src, size_t dstlen, locale_t locale);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_rand_s)(unsigned int *__restrict randval);
INTDEF int NOTHROW_NCX(LIBDCALL libd__wctomb_l)(char *buf, char16_t wc, locale_t locale);
INTDEF int NOTHROW_NCX(LIBKCALL libc__wctomb_l)(char *buf, char32_t wc, locale_t locale);
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd_wctomb_s)(int *presult, char *buf, rsize_t buflen, char16_t wc);
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBKCALL libc_wctomb_s)(int *presult, char *buf, rsize_t buflen, char32_t wc);
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd__wctomb_s_l)(int *presult, char *buf, size_t buflen, char16_t wc, locale_t locale);
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBKCALL libc__wctomb_s_l)(int *presult, char *buf, size_t buflen, char32_t wc, locale_t locale);
INTDEF NONNULL((1, 2, 4)) errno_t NOTHROW_NCX(LIBDCALL libd__wcstombs_s_l)(size_t *presult, char *buf, size_t buflen, char16_t const *src, size_t maxlen, locale_t locale);
INTDEF NONNULL((1, 2, 4)) errno_t NOTHROW_NCX(LIBKCALL libc__wcstombs_s_l)(size_t *presult, char *buf, size_t buflen, char32_t const *src, size_t maxlen, locale_t locale);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd__wcstombs_l)(char *dst, char16_t const *src, size_t maxlen, locale_t locale);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBKCALL libc__wcstombs_l)(char *dst, char32_t const *src, size_t maxlen, locale_t locale);
INTDEF NONNULL((1, 2, 4)) errno_t NOTHROW_NCX(LIBDCALL libd_wcstombs_s)(size_t *presult, char *buf, size_t buflen, char16_t const *src, size_t maxlen);
INTDEF NONNULL((1, 2, 4)) errno_t NOTHROW_NCX(LIBKCALL libc_wcstombs_s)(size_t *presult, char *buf, size_t buflen, char32_t const *src, size_t maxlen);
INTDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_ALIGN(2) ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBCCALL libc__aligned_malloc)(size_t num_bytes, size_t min_alignment);
INTDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBCCALL libc__aligned_offset_malloc)(size_t num_bytes, size_t min_alignment, size_t offset);
INTDEF WUNUSED ATTR_ALLOC_ALIGN(3) ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBCCALL libc__aligned_realloc)(void *aligned_mallptr, size_t newsize, size_t min_alignment);
INTDEF WUNUSED ATTR_ALLOC_ALIGN(4) ATTR_ALLOC_SIZE((2, 3)) void *NOTHROW_NCX(LIBCCALL libc__aligned_recalloc)(void *aligned_mallptr, size_t count, size_t num_bytes, size_t min_alignment);
INTDEF WUNUSED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBCCALL libc__aligned_offset_realloc)(void *aligned_mallptr, size_t newsize, size_t min_alignment, size_t offset);
INTDEF WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *NOTHROW_NCX(LIBCCALL libc__aligned_offset_recalloc)(void *aligned_mallptr, size_t count, size_t num_bytes, size_t min_alignment, size_t offset);
INTDEF ATTR_PURE WUNUSED size_t NOTHROW_NCX(LIBCCALL libc__aligned_msize)(void *aligned_mallptr, size_t min_alignment, size_t offset);
INTDEF void NOTHROW_NCX(LIBCCALL libc__aligned_free)(void *aligned_mallptr);
INTDEF NONNULL((1, 5, 6)) errno_t NOTHROW_NCX(LIBCCALL libc__ecvt_s)(char *buf, size_t buflen, double val, int ndigit, int *__restrict decptr, int *__restrict sign);
INTDEF NONNULL((1, 5, 6)) errno_t NOTHROW_NCX(LIBCCALL libc__fcvt_s)(char *buf, size_t buflen, double val, int ndigit, int *__restrict decptr, int *__restrict sign);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc__gcvt_s)(char *buf, size_t buflen, double val, int ndigit);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__atoflt)(float *__restrict result, char const *__restrict nptr);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__atoflt_l)(float *__restrict result, char const *__restrict nptr, locale_t locale);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__atodbl)(double *__restrict result, char __KOS_FIXED_CONST *__restrict nptr);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__atodbl_l)(double *__restrict result, char __KOS_FIXED_CONST *__restrict nptr, locale_t locale);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__atoldbl)(__LONGDOUBLE *__restrict result, char __KOS_FIXED_CONST *__restrict nptr);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__atoldbl_l)(__LONGDOUBLE *__restrict result, char __KOS_FIXED_CONST *__restrict nptr, locale_t locale);
INTDEF ATTR_CONST unsigned int NOTHROW(LIBCCALL libc__rotl)(unsigned int val, int shift);
INTDEF ATTR_CONST unsigned int NOTHROW(LIBCCALL libc__rotr)(unsigned int val, int shift);
INTDEF ATTR_CONST u64 NOTHROW(LIBCCALL libc__rotl64)(u64 val, int shift);
INTDEF ATTR_CONST u64 NOTHROW(LIBCCALL libc__rotr64)(u64 val, int shift);
INTDEF ATTR_CONST unsigned long NOTHROW(LIBCCALL libc__lrotl)(unsigned long val, int shift);
INTDEF ATTR_CONST unsigned long NOTHROW(LIBCCALL libc__lrotr)(unsigned long val, int shift);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__putenv_s)(char const *varname, char const *val);
INTDEF NONNULL((1, 2, 3)) void NOTHROW_RPC(LIBCCALL libc__searchenv)(char const *file, char const *envvar, char *__restrict resultpath);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc__makepath)(char *__restrict buf, char const *drive, char const *dir, char const *file, char const *ext);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc__splitpath)(char const *__restrict abspath, char *drive, char *dir, char *file, char *ext);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc__makepath_s)(char *buf, size_t buflen, char const *drive, char const *dir, char const *file, char const *ext);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc__splitpath_s)(char const *__restrict abspath, char *drive, size_t drivelen, char *dir, size_t dirlen, char *file, size_t filelen, char *ext, size_t extlen);
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc_itoa)(int val, char *buf, int radix);
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc_ltoa)(long val, char *buf, int radix);
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc_ultoa)(unsigned long val, char *buf, int radix);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) double NOTHROW_NCX(LIBDCALL libd__wtof)(char16_t const *nptr);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) double NOTHROW_NCX(LIBKCALL libc__wtof)(char32_t const *nptr);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) double NOTHROW_NCX(LIBDCALL libd__wtof_l)(char16_t const *nptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) double NOTHROW_NCX(LIBKCALL libc__wtof_l)(char32_t const *nptr, locale_t locale);
INTDEF NONNULL((2)) char16_t *NOTHROW_NCX(LIBDCALL libd__itow)(int val, char16_t *buf, int radix);
INTDEF NONNULL((2)) char32_t *NOTHROW_NCX(LIBKCALL libc__itow)(int val, char32_t *buf, int radix);
INTDEF NONNULL((2)) char16_t *NOTHROW_NCX(LIBDCALL libd__ltow)(long val, char16_t *buf, int radix);
INTDEF NONNULL((2)) char32_t *NOTHROW_NCX(LIBKCALL libc__ltow)(long val, char32_t *buf, int radix);
INTDEF NONNULL((2)) char16_t *NOTHROW_NCX(LIBDCALL libd__ultow)(unsigned long val, char16_t *buf, int radix);
INTDEF NONNULL((2)) char32_t *NOTHROW_NCX(LIBKCALL libc__ultow)(unsigned long val, char32_t *buf, int radix);
INTDEF NONNULL((2)) char16_t *NOTHROW_NCX(LIBDCALL libd__i64tow)(s64 val, char16_t *buf, int radix);
INTDEF NONNULL((2)) char32_t *NOTHROW_NCX(LIBKCALL libc__i64tow)(s64 val, char32_t *buf, int radix);
INTDEF NONNULL((2)) char16_t *NOTHROW_NCX(LIBDCALL libd__ui64tow)(u64 val, char16_t *buf, int radix);
INTDEF NONNULL((2)) char32_t *NOTHROW_NCX(LIBKCALL libc__ui64tow)(u64 val, char32_t *buf, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd__itow_s)(int val, char16_t *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBKCALL libc__itow_s)(int val, char32_t *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd__ltow_s)(long val, char16_t *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBKCALL libc__ltow_s)(long val, char32_t *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd__ultow_s)(unsigned long val, char16_t *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBKCALL libc__ultow_s)(unsigned long val, char32_t *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd__i64tow_s)(s64 val, char16_t *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBKCALL libc__i64tow_s)(s64 val, char32_t *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd__ui64tow_s)(u64 val, char16_t *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBKCALL libc__ui64tow_s)(u64 val, char32_t *buf, size_t buflen, int radix);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) s64 NOTHROW_NCX(LIBDCALL libd__wtoi64)(char16_t const *__restrict nptr);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) s64 NOTHROW_NCX(LIBKCALL libc__wtoi64)(char32_t const *__restrict nptr);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd__wtoi_l)(char16_t const *__restrict nptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBKCALL libc__wtoi_l)(char32_t const *__restrict nptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) long int NOTHROW_NCX(LIBDCALL libd__wtol_l)(char16_t const *__restrict nptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) long int NOTHROW_NCX(LIBKCALL libc__wtol_l)(char32_t const *__restrict nptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) s64 NOTHROW_NCX(LIBDCALL libd__wtoi64_l)(char16_t const *__restrict nptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) s64 NOTHROW_NCX(LIBKCALL libc__wtoi64_l)(char32_t const *__restrict nptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBDCALL libd__wtoll_l)(char16_t const *__restrict nptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBKCALL libc__wtoll_l)(char32_t const *__restrict nptr, locale_t locale);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_STDLIB_H */
