/* HASH CRC-32:0xf19517a6 */
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
#ifndef GUARD_LIBC_AUTO_STDLIB_H
#define GUARD_LIBC_AUTO_STDLIB_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <stdlib.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 4)) void (LIBDCALL libd_qsort_r)(void *pbase, size_t item_count, size_t item_size, __compar_d_fn_t cmp, void *arg) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF NONNULL((1, 4)) void (LIBCCALL libc_qsort_r)(void *pbase, size_t item_count, size_t item_size, __compar_d_fn_t cmp, void *arg) THROWS(...);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((1, 2, 5)) void *(LIBDCALL libd_bsearch_r)(void const *pkey, void const *pbase, size_t item_count, size_t item_size, __compar_d_fn_t cmp, void *arg) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((1, 2, 5)) void *(LIBCCALL libc_bsearch_r)(void const *pkey, void const *pbase, size_t item_count, size_t item_size, __compar_d_fn_t cmp, void *arg) THROWS(...);
#endif /* !__KERNEL__ */
INTDEF NONNULL((1, 4)) void (LIBCCALL libc_qsort)(void *pbase, size_t item_count, size_t item_size, __compar_fn_t cmp) THROWS(...);
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((1, 2, 5)) void *(LIBCCALL libc_bsearch)(void const *pkey, void const *pbase, size_t item_count, size_t item_size, __compar_fn_t cmp) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED long NOTHROW(LIBDCALL libd_labs)(long x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED long NOTHROW(LIBCCALL libc_labs)(long x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED __LONGLONG NOTHROW(LIBDCALL libd_llabs)(__LONGLONG x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED __LONGLONG NOTHROW(LIBCCALL libc_llabs)(__LONGLONG x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED ldiv_t NOTHROW_NCX(LIBDCALL libd_ldiv)(long numer, long denom);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED ldiv_t NOTHROW_NCX(LIBCCALL libc_ldiv)(long numer, long denom);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED lldiv_t NOTHROW_NCX(LIBDCALL libd_lldiv)(__LONGLONG numer, __LONGLONG denom);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED lldiv_t NOTHROW_NCX(LIBCCALL libc_lldiv)(__LONGLONG numer, __LONGLONG denom);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_abs)(int x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_abs)(int x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED struct __div_struct NOTHROW_NCX(LIBDCALL libd_div)(int numer, int denom);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED struct __div_struct NOTHROW_NCX(LIBCCALL libc_div)(int numer, int denom);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_getenv)(char const *varname);
INTDEF int NOTHROW_NCX(LIBDCALL libd_mblen)(char const *str, size_t maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF int NOTHROW_NCX(LIBCCALL libc_mblen)(char const *str, size_t maxlen);
INTDEF int NOTHROW_NCX(LIBDCALL libd_mbtowc)(char16_t *__restrict pwc, char const *__restrict str, size_t maxlen);
INTDEF int NOTHROW_NCX(LIBKCALL libc_mbtowc)(char32_t *__restrict pwc, char const *__restrict str, size_t maxlen);
INTDEF int NOTHROW_NCX(LIBDCALL libd_wctomb)(char *str, char16_t wc);
INTDEF int NOTHROW_NCX(LIBKCALL libc_wctomb)(char *str, char32_t wc);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_mbstowcs)(char16_t *__restrict dst, char const *__restrict src, size_t dstlen);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBKCALL libc_mbstowcs)(char32_t *__restrict dst, char const *__restrict src, size_t dstlen);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBDCALL libd_wcstombs)(char *__restrict dst, char16_t const *__restrict src, size_t dstlen);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBKCALL libc_wcstombs)(char *__restrict dst, char32_t const *__restrict src, size_t dstlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> system(3)
 * Execute a given `command' on the system interpreter (as in `sh -c $command')
 * The return value is the exit status after running `command'
 * When `command' is `NULL' only check if a system interpreter is available.
 * When no system interpreter is available, `127' is returned. */
INTDEF int NOTHROW_RPC(LIBDCALL libd_system)(char const *command);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> system(3)
 * Execute a given `command' on the system interpreter (as in `sh -c $command')
 * The return value is the exit status after running `command'
 * When `command' is `NULL' only check if a system interpreter is available.
 * When no system interpreter is available, `127' is returned. */
INTDEF int NOTHROW_RPC(LIBCCALL libc_system)(char const *command);
INTDEF ATTR_NORETURN void (LIBCCALL libc_abort)(void) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_NORETURN void (LIBDCALL libd_exit)(int status) THROWS(...);
INTDEF ATTR_NORETURN void (LIBDCALL libd_quick_exit)(int status) THROWS(...);
INTDEF ATTR_NORETURN void (LIBDCALL libd__Exit)(int status) THROWS(...);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBDCALL libd_malloc)(size_t num_bytes);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((1, 2)) void *NOTHROW_NCX(LIBDCALL libd_calloc)(size_t count, size_t num_bytes);
INTDEF ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBDCALL libd_realloc)(void *mallptr, size_t num_bytes);
INTDEF void NOTHROW_NCX(LIBDCALL libd_free)(void *mallptr);
INTDEF void NOTHROW(LIBDCALL libd_srand)(long seed);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_atoi)(char const *__restrict nptr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_atoi)(char const *__restrict nptr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED NONNULL((1)) long NOTHROW_NCX(LIBDCALL libd_atol)(char const *__restrict nptr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) long NOTHROW_NCX(LIBCCALL libc_atol)(char const *__restrict nptr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBDCALL libd_atoll)(char const *__restrict nptr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBCCALL libc_atoll)(char const *__restrict nptr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF NONNULL((1)) unsigned long NOTHROW_NCX(LIBDCALL libd_strtoul)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF NONNULL((1)) unsigned long NOTHROW_NCX(LIBCCALL libc_strtoul)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF NONNULL((1)) long NOTHROW_NCX(LIBDCALL libd_strtol)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF NONNULL((1)) long NOTHROW_NCX(LIBCCALL libc_strtol)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBDCALL libd_strtoull)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBCCALL libc_strtoull)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBDCALL libd_strtoll)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBCCALL libc_strtoll)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF WUNUSED NONNULL((1)) double NOTHROW_NCX(LIBDCALL libd_atof)(char const *__restrict nptr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF WUNUSED NONNULL((1)) double NOTHROW_NCX(LIBCCALL libc_atof)(char const *__restrict nptr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF NONNULL((1)) double NOTHROW_NCX(LIBDCALL libd_strtod)(char const *__restrict nptr, char **endptr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF NONNULL((1)) double NOTHROW_NCX(LIBCCALL libc_strtod)(char const *__restrict nptr, char **endptr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF NONNULL((1)) float NOTHROW_NCX(LIBDCALL libd_strtof)(char const *__restrict nptr, char **endptr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF NONNULL((1)) float NOTHROW_NCX(LIBCCALL libc_strtof)(char const *__restrict nptr, char **endptr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF NONNULL((1)) __LONGDOUBLE NOTHROW_NCX(LIBDCALL libd_strtold)(char const *__restrict nptr, char **endptr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF NONNULL((1)) __LONGDOUBLE NOTHROW_NCX(LIBCCALL libc_strtold)(char const *__restrict nptr, char **endptr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBDCALL libd_strtou32)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBCCALL libc_strtou32)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBDCALL libd_strto32)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBCCALL libc_strto32)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBDCALL libd_strtou64)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBCCALL libc_strtou64)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF NONNULL((1)) int64_t NOTHROW_NCX(LIBDCALL libd_strto64)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_LEAF NONNULL((1)) int64_t NOTHROW_NCX(LIBCCALL libc_strto64)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBDCALL libd_strtou32_l)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBCCALL libc_strtou32_l)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBDCALL libd_strto32_l)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBCCALL libc_strto32_l)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBDCALL libd_strtou64_l)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBCCALL libc_strtou64_l)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF NONNULL((1)) int64_t NOTHROW_NCX(LIBDCALL libd_strto64_l)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF NONNULL((1)) int64_t NOTHROW_NCX(LIBCCALL libc_strto64_l)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((3)) char *NOTHROW_NCX(LIBDCALL libd_gcvt)(double val, int ndigit, char *buf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((3)) char *NOTHROW_NCX(LIBCCALL libc_gcvt)(double val, int ndigit, char *buf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((3, 4, 5)) int NOTHROW_NCX(LIBDCALL libd_ecvt_r)(double val, int ndigit, int *__restrict decptr, int *__restrict sign, char *__restrict buf, size_t len);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((3, 4, 5)) int NOTHROW_NCX(LIBCCALL libc_ecvt_r)(double val, int ndigit, int *__restrict decptr, int *__restrict sign, char *__restrict buf, size_t len);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((3, 4, 5)) int NOTHROW_NCX(LIBDCALL libd_fcvt_r)(double val, int ndigit, int *__restrict decptr, int *__restrict sign, char *__restrict buf, size_t len);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((3, 4, 5)) int NOTHROW_NCX(LIBCCALL libc_fcvt_r)(double val, int ndigit, int *__restrict decptr, int *__restrict sign, char *__restrict buf, size_t len);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((3)) char *NOTHROW_NCX(LIBDCALL libd_qgcvt)(__LONGDOUBLE val, int ndigit, char *buf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((3)) char *NOTHROW_NCX(LIBCCALL libc_qgcvt)(__LONGDOUBLE val, int ndigit, char *buf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((3, 4, 5)) int NOTHROW_NCX(LIBDCALL libd_qecvt_r)(__LONGDOUBLE val, int ndigit, int *__restrict decptr, int *__restrict sign, char *__restrict buf, size_t len);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((3, 4, 5)) int NOTHROW_NCX(LIBCCALL libc_qecvt_r)(__LONGDOUBLE val, int ndigit, int *__restrict decptr, int *__restrict sign, char *__restrict buf, size_t len);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((3, 4, 5)) int NOTHROW_NCX(LIBDCALL libd_qfcvt_r)(__LONGDOUBLE val, int ndigit, int *__restrict decptr, int *__restrict sign, char *__restrict buf, size_t len);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((3, 4, 5)) int NOTHROW_NCX(LIBCCALL libc_qfcvt_r)(__LONGDOUBLE val, int ndigit, int *__restrict decptr, int *__restrict sign, char *__restrict buf, size_t len);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((3, 4)) char *NOTHROW_NCX(LIBDCALL libd_qecvt)(__LONGDOUBLE val, int ndigit, int *__restrict decptr, int *__restrict sign);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((3, 4)) char *NOTHROW_NCX(LIBCCALL libc_qecvt)(__LONGDOUBLE val, int ndigit, int *__restrict decptr, int *__restrict sign);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((3, 4)) char *NOTHROW_NCX(LIBDCALL libd_qfcvt)(__LONGDOUBLE val, int ndigit, int *__restrict decptr, int *__restrict sign);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((3, 4)) char *NOTHROW_NCX(LIBCCALL libc_qfcvt)(__LONGDOUBLE val, int ndigit, int *__restrict decptr, int *__restrict sign);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_drand48_r)(struct drand48_data *__restrict buffer, double *__restrict result);
INTDEF NONNULL((1, 2, 3)) int NOTHROW_NCX(LIBDCALL libd_erand48_r)(unsigned short xsubi[3], struct drand48_data *__restrict buffer, double *__restrict result);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_lrand48_r)(struct drand48_data *__restrict buffer, long *__restrict result);
INTDEF NONNULL((1, 2, 3)) int NOTHROW_NCX(LIBDCALL libd_nrand48_r)(unsigned short xsubi[3], struct drand48_data *__restrict buffer, long *__restrict result);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_mrand48_r)(struct drand48_data *__restrict buffer, long *__restrict result);
INTDEF NONNULL((1, 2, 3)) int NOTHROW_NCX(LIBDCALL libd_jrand48_r)(unsigned short xsubi[3], struct drand48_data *__restrict buffer, long *__restrict result);
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBDCALL libd_srand48_r)(long seedval, struct drand48_data *buffer);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_seed48_r)(unsigned short seed16v[3], struct drand48_data *buffer);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_lcong48_r)(unsigned short param[7], struct drand48_data *buffer);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_random_r)(struct random_data *__restrict buf, int32_t *__restrict result);
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBDCALL libd_srandom_r)(unsigned int seed, struct random_data *buf);
INTDEF NONNULL((2, 4)) int NOTHROW_NCX(LIBDCALL libd_initstate_r)(unsigned int seed, char *__restrict statebuf, size_t statelen, struct random_data *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_setstate_r)(char *__restrict statebuf, struct random_data *__restrict buf);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_on_exit)(__on_exit_func_t func, void *arg);
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `template_' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all 'X'-characters before the call (else errno=EINVAL + return -1), with
 * random characters such that the filename described by `template_' will not
 * already exists. Then, create a new file with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The # of trailing characters to-be ignored
 *                    after the required 6 trailing 'X'-characters. */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_NCX(LIBDCALL libd_mkstemps)(char *template_, __STDC_INT_AS_SIZE_T suffixlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `template_' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all 'X'-characters before the call (else errno=EINVAL + return -1), with
 * random characters such that the filename described by `template_' will not
 * already exists. Then, create a new file with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The # of trailing characters to-be ignored
 *                    after the required 6 trailing 'X'-characters. */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_NCX(LIBCCALL libc_mkstemps)(char *template_, __STDC_INT_AS_SIZE_T suffixlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_rpmatch)(char const *response);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_rpmatch)(char const *response);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_rand_r)(unsigned int *__restrict pseed);
INTDEF int NOTHROW_RPC(LIBDCALL libd_getloadavg)(double loadavg[], __STDC_INT_AS_SIZE_T nelem);
INTDEF NONNULL((1)) double NOTHROW_NCX(LIBDCALL libd_erand48)(unsigned short xsubi[3]);
INTDEF NONNULL((1)) long NOTHROW_NCX(LIBDCALL libd_nrand48)(unsigned short xsubi[3]);
INTDEF NONNULL((1)) long NOTHROW_NCX(LIBDCALL libd_jrand48)(unsigned short xsubi[3]);
INTDEF void NOTHROW_NCX(LIBDCALL libd_srand48)(long seedval);
INTDEF NONNULL((1)) unsigned short *NOTHROW_NCX(LIBDCALL libd_seed48)(unsigned short seed16v[3]);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd_lcong48)(unsigned short param[7]);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_putenv)(char *string);
INTDEF void NOTHROW_NCX(LIBDCALL libd_srandom)(unsigned int seed);
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBDCALL libd_initstate)(unsigned int seed, char *statebuf, size_t statelen);
INTDEF NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_setstate)(char *statebuf);
INTDEF WUNUSED char *NOTHROW_NCX(LIBDCALL libd_l64a)(long n);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) long NOTHROW_NCX(LIBDCALL libd_a64l)(char const *s);
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink()', but will also function for
 * non-symlink paths, as well as always return an absolute (unambiguous) path
 * @param: resolved: A buffer of `PATH_MAX' bytes to-be filled with the resulting
 *                   path, or NULL to automatically `malloc()'ate and return a
 *                   buffer of sufficient size. */
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_RPC(LIBDCALL libd_realpath)(char const *filename, char *resolved);
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * NOTE: You may also pass `NULL' for `resolved' to have a buffer of `buflen'
 *       bytes automatically allocated in the heap, ontop of which you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
INTDEF WUNUSED char *NOTHROW_RPC(LIBDCALL libd_frealpath)(fd_t fd, char *resolved, size_t buflen);
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * @param flags: Set of `0 | AT_ALTPATH | AT_DOSPATH'
 * NOTE: You may use `AT_ALTPATH' to cause the path to be printed in alternate
 *       representation mode. This means that if the path would have normally
 *       been printed as a unix path, it would instead be printed as a DOS path.
 *       Similarly, the reverse also applies.
 * NOTE: You may also pass `NULL' for `resolved' to have a buffer of `buflen'
 *       bytes automatically allocated in the heap, ontop of which you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
INTDEF WUNUSED char *NOTHROW_RPC(LIBDCALL libd_frealpath4)(fd_t fd, char *resolved, size_t buflen, atflag_t flags);
/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is not dereferenced,
 * causing the path to the symlink itself to be printed. - Otherwise, the
 * filed pointed to by the symblic link is printed.
 * NOTE: You may use `AT_ALTPATH' to cause the path to be printed in alternate
 *       representation mode. This means that if the path would have normally
 *       been printed as a unix path, it would instead be printed as a DOS path.
 *       Similarly, the reverse also applies.
 * NOTE: You may also pass `NULL' for `resolved' to have a buffer of `buflen'
 *       bytes automatically allocated in the heap, ontop of which you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size.
 * @param flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH'
 * @return: NULL: [errno=ERANGE]: `buflen' is too small to fit the entire path */
INTDEF WUNUSED NONNULL((2)) char *NOTHROW_RPC(LIBDCALL libd_frealpathat)(fd_t dirfd, char const *filename, char *resolved, size_t buflen, atflag_t flags);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_setenv)(char const *varname, char const *val, int replace);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_unsetenv)(char const *varname);
/* >> mktemp(3)
 * Badly designed version of `mkstemp' that won't actually create
 * the temporary file, meaning that by the time the caller tries to
 * create the file themselves, another process may have already
 * created it.
 * Also: when no temporary filename can be created, rather than
 *       returning something sensible like `NULL', this function
 *       will instead set `template_' to an empty string, and still
 *       re-return it like it would if everything had worked! */
INTDEF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_mktemp)(char *template_);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mktemp(3)
 * Badly designed version of `mkstemp' that won't actually create
 * the temporary file, meaning that by the time the caller tries to
 * create the file themselves, another process may have already
 * created it.
 * Also: when no temporary filename can be created, rather than
 *       returning something sensible like `NULL', this function
 *       will instead set `template_' to an empty string, and still
 *       re-return it like it would if everything had worked! */
INTDEF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_mktemp)(char *template_);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((3, 4)) char *NOTHROW_NCX(LIBDCALL libd_ecvt)(double val, int ndigit, int *__restrict decptr, int *__restrict sign);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((3, 4)) char *NOTHROW_NCX(LIBCCALL libc_ecvt)(double val, int ndigit, int *__restrict decptr, int *__restrict sign);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((3, 4)) char *NOTHROW_NCX(LIBDCALL libd_fcvt)(double val, int ndigit, int *__restrict decptr, int *__restrict sign);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((3, 4)) char *NOTHROW_NCX(LIBCCALL libc_fcvt)(double val, int ndigit, int *__restrict decptr, int *__restrict sign);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((1, 2, 3)) int NOTHROW_NCX(LIBDCALL libd_getsubopt)(char **__restrict optionp, char *const *__restrict tokens, char **__restrict valuep);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((1, 2, 3)) int NOTHROW_NCX(LIBCCALL libc_getsubopt)(char **__restrict optionp, char *const *__restrict tokens, char **__restrict valuep);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mkstemp(3), mkstemp64(3)
 * Replace the last 6 characters of `template_', which must be filled with
 * all 'X'-characters before the call (else errno=EINVAL + return -1),
 * with random characters such that the filename described by `template_'
 * will not already exists. Then, create a new file with `O_RDWR' and return
 * the file descriptor of that file. */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_RPC(LIBDCALL libd_mkstemp)(char *template_);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mkstemp(3), mkstemp64(3)
 * Replace the last 6 characters of `template_', which must be filled with
 * all 'X'-characters before the call (else errno=EINVAL + return -1),
 * with random characters such that the filename described by `template_'
 * will not already exists. Then, create a new file with `O_RDWR' and return
 * the file descriptor of that file. */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_RPC(LIBCCALL libc_mkstemp)(char *template_);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mkdtemp(3)
 * Replace the last 6 characters of `template_', which must be filled with
 * all 'X'-characters before the call (else errno=EINVAL + return -1),
 * with random characters such that the pathname described by `template_'
 * will not already exists. Then, create a new directory with `mode=0700',
 * and re-return `template_' to indicate success.
 * On error, `NULL' will be returned, and the contents of `template_' are undefined. */
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_RPC(LIBDCALL libd_mkdtemp)(char *template_);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mkdtemp(3)
 * Replace the last 6 characters of `template_', which must be filled with
 * all 'X'-characters before the call (else errno=EINVAL + return -1),
 * with random characters such that the pathname described by `template_'
 * will not already exists. Then, create a new directory with `mode=0700',
 * and re-return `template_' to indicate success.
 * On error, `NULL' will be returned, and the contents of `template_' are undefined. */
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_RPC(LIBCCALL libc_mkdtemp)(char *template_);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF int NOTHROW_NCX(LIBDCALL libd_grantpt)(fd_t fd);
INTDEF int NOTHROW_NCX(LIBDCALL libd_unlockpt)(fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF int NOTHROW_NCX(LIBCCALL libc_unlockpt)(fd_t fd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Returns the name of the PTY slave (Pseudo TTY slave)
 * associated with the master descriptor `fd' */
INTDEF WUNUSED char *NOTHROW_NCX(LIBDCALL libd_ptsname)(fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Returns the name of the PTY slave (Pseudo TTY slave)
 * associated with the master descriptor `fd' */
INTDEF WUNUSED char *NOTHROW_NCX(LIBCCALL libc_ptsname)(fd_t fd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED fd_t NOTHROW_RPC(LIBDCALL libd_posix_openpt)(oflag_t oflags);
/* Returns the name of the PTY slave (Pseudo TTY slave)
 * associated with the master descriptor `fd' */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBDCALL libd_ptsname_r)(fd_t fd, char *buf, size_t buflen);
INTDEF NONNULL((1)) long NOTHROW_NCX(LIBDCALL libd_strtol_l)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) long NOTHROW_NCX(LIBCCALL libc_strtol_l)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) unsigned long NOTHROW_NCX(LIBDCALL libd_strtoul_l)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) unsigned long NOTHROW_NCX(LIBCCALL libc_strtoul_l)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBDCALL libd_strtoll_l)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBCCALL libc_strtoll_l)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBDCALL libd_strtoull_l)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) __ULONGLONG NOTHROW_NCX(LIBCCALL libc_strtoull_l)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) double NOTHROW_NCX(LIBDCALL libd_strtod_l)(char const *__restrict nptr, char **endptr, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) double NOTHROW_NCX(LIBCCALL libc_strtod_l)(char const *__restrict nptr, char **endptr, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) float NOTHROW_NCX(LIBDCALL libd_strtof_l)(char const *__restrict nptr, char **endptr, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) float NOTHROW_NCX(LIBCCALL libc_strtof_l)(char const *__restrict nptr, char **endptr, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) __LONGDOUBLE NOTHROW_NCX(LIBDCALL libd_strtold_l)(char const *__restrict nptr, char **endptr, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) __LONGDOUBLE NOTHROW_NCX(LIBCCALL libc_strtold_l)(char const *__restrict nptr, char **endptr, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_secure_getenv)(char const *varname);
/* Return the result of `realpath(filename)' as a `malloc()'-allocated buffer
 * Upon error, `NULL' is returned instead */
INTDEF ATTR_MALLOC WUNUSED NONNULL((1)) char *NOTHROW_RPC(LIBDCALL libd_canonicalize_file_name)(char const *filename);
/* >> mkostemp(3), mkostemp64(3)
 * Replace the last 6 characters of `template_' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all 'X'-characters before the call (else errno=EINVAL + return -1), with
 * random characters such that the filename described by `template_' will not
 * already exists. Then, create a new file with `O_RDWR | flags' and return the file
 * descriptor of that file.
 * @param: flags: Additional flags to pass to `open(2)',
 *                but `O_ACCMODE' is always set to `O_RDWR' */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_NCX(LIBDCALL libd_mkostemp)(char *template_, oflag_t flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mkostemp(3), mkostemp64(3)
 * Replace the last 6 characters of `template_' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all 'X'-characters before the call (else errno=EINVAL + return -1), with
 * random characters such that the filename described by `template_' will not
 * already exists. Then, create a new file with `O_RDWR | flags' and return the file
 * descriptor of that file.
 * @param: flags: Additional flags to pass to `open(2)',
 *                but `O_ACCMODE' is always set to `O_RDWR' */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_NCX(LIBCCALL libc_mkostemp)(char *template_, oflag_t flags);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_NCX(LIBDCALL libd_mkostemps)(char *template_, __STDC_INT_AS_SIZE_T suffixlen, oflag_t flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_NCX(LIBCCALL libc_mkostemps)(char *template_, __STDC_INT_AS_SIZE_T suffixlen, oflag_t flags);
/* Internal implementation for creating temporary files.
 * @param: what: Select what kind of temporary object to create.
 *                  `0': Create a temporary file. (The handle of that file will be returned)
 *                       Creating mode used is 0600
 *                       This mode is only recognized when `$has_function(open)'
 *                  `1': Create a temporary directory. (0 is returned on success)
 *                       Creating mode used is 0700
 *                       This mode is only recognized when `$has_function(mkdir)'
 *                       NOTE: `flags' is ignored in this mode
 *                  `2': Braindead `mktemp(3)'-mode: Like `0', but don't actually create the
 *                       file. Instead, return `0' on success
 *                       This mode is only recognized when `$has_function(open) || $has_function(stat)'
 *                       NOTE: `flags' is ignored in this mode */
INTDEF WUNUSED NONNULL((2)) fd_t NOTHROW_RPC(LIBCCALL libc_system_mktemp)(unsigned int what, char *template_, __STDC_INT_AS_SIZE_T suffixlen, oflag_t flags);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> shexec(3)
 * Execute command with the system interpreter (such as: `/bin/sh -c $command')
 * This function is used to implement `system(3)' and `popen(3)', and may be
 * used to invoke the system interpreter.
 * This function only returns on failure (similar to exec(2)), and will never
 * return on success (since in that case, the calling program will have been
 * replaced by the system shell) */
INTDEF int NOTHROW_RPC(LIBDCALL libd_shexec)(char const *command);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> shexec(3)
 * Execute command with the system interpreter (such as: `/bin/sh -c $command')
 * This function is used to implement `system(3)' and `popen(3)', and may be
 * used to invoke the system interpreter.
 * This function only returns on failure (similar to exec(2)), and will never
 * return on success (since in that case, the calling program will have been
 * replaced by the system shell) */
INTDEF int NOTHROW_RPC(LIBCCALL libc_shexec)(char const *command);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBDCALL libd_reallocf)(void *mallptr, size_t num_bytes);
/* Same as `recallocv(mallptr, new_elem_count, elem_size)', but also ensure that
 * when `mallptr != NULL', memory pointed to by the old `mallptr...+=old_elem_count*elem_size'
 * is explicitly freed to zero (s.a. `freezero()') when reallocation must move the memory block */
INTDEF ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((3, 4)) void *NOTHROW_NCX(LIBDCALL libd_recallocarray)(void *mallptr, size_t old_elem_count, size_t new_elem_count, size_t elem_size);
/* Same as `free(mallptr)', but also ensure that the memory region
 * described by `mallptr...+=num_bytes' is explicitly freed to zero, or
 * immediately returned to the OS, rather than being left in cache
 * while still containing its previous contents. */
INTDEF void NOTHROW_NCX(LIBDCALL libd_freezero)(void *mallptr, size_t num_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Returns the absolute filename of the main executable (s.a. `program_invocation_name') */
INTDEF ATTR_CONST WUNUSED char const *NOTHROW_NCX(LIBCCALL libc_getexecname)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Enumerate all open file descriptors by invoking `(*func)(cookie, <fd>)' for each of them
 * If during any of these invocations, `(*func)(...)' returns non-zero, enumeration stops,
 * and `fdwalk()' returns with that same value. If `(*func)(...)' is never called, or all
 * invocations return 0, `fdwalk()' will also return 0. */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_fdwalk)(__fdwalk_func_t func, void *cookie);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Enumerate all open file descriptors by invoking `(*func)(cookie, <fd>)' for each of them
 * If during any of these invocations, `(*func)(...)' returns non-zero, enumeration stops,
 * and `fdwalk()' returns with that same value. If `(*func)(...)' is never called, or all
 * invocations return 0, `fdwalk()' will also return 0. */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_fdwalk)(__fdwalk_func_t func, void *cookie);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strtonum(3)
 * Similar to `strtoi()' with `base=10', but return human-
 * readable error messages in `*p_errstr' on error (alongside
 * `return==0') (or `NULL' on success).
 * The following messages are defined:
 *   - "too large": Numeric value is too great (`ERANGE' && greater than `hi')
 *   - "too small": Numeric value is too small (`ERANGE' && less than `lo')
 *   - "invalid":   Any other error (`ENOTSUP' or `ECANCELED')
 * @return: 0 : [*p_errstr != NULL] Error
 * @return: 0 : [*p_errstr == NULL] Success
 * @return: * : [*p_errstr == NULL] Success */
INTDEF WUNUSED NONNULL((1, 4)) __LONGLONG NOTHROW_NCX(LIBDCALL libd_strtonum)(char const *nptr, __LONGLONG lo, __LONGLONG hi, char const **p_errstr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strtonum(3)
 * Similar to `strtoi()' with `base=10', but return human-
 * readable error messages in `*p_errstr' on error (alongside
 * `return==0') (or `NULL' on success).
 * The following messages are defined:
 *   - "too large": Numeric value is too great (`ERANGE' && greater than `hi')
 *   - "too small": Numeric value is too small (`ERANGE' && less than `lo')
 *   - "invalid":   Any other error (`ENOTSUP' or `ECANCELED')
 * @return: 0 : [*p_errstr != NULL] Error
 * @return: 0 : [*p_errstr == NULL] Success
 * @return: * : [*p_errstr == NULL] Success */
INTDEF WUNUSED NONNULL((1, 4)) __LONGLONG NOTHROW_NCX(LIBCCALL libc_strtonum)(char const *nptr, __LONGLONG lo, __LONGLONG hi, char const **p_errstr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 4)) int (LIBDCALL libd_heapsort)(void *pbase, size_t item_count, size_t item_size, __compar_fn_t cmp) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 4)) int (LIBCCALL libc_heapsort)(void *pbase, size_t item_count, size_t item_size, __compar_fn_t cmp) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 4)) int (LIBDCALL libd_mergesort)(void *pbase, size_t item_count, size_t item_size, __compar_fn_t cmp) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 4)) int (LIBCCALL libc_mergesort)(void *pbase, size_t item_count, size_t item_size, __compar_fn_t cmp) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_radixsort)(unsigned char const **base, int item_count, unsigned char const *table, unsigned endbyte);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_sradixsort)(unsigned char const **base, int item_count, unsigned char const *table, unsigned endbyte);
INTDEF WUNUSED NONNULL((1, 2)) char *NOTHROW_NCX(LIBDCALL libd_getbsize)(int *headerlenp, __LONGPTR_TYPE__ *blocksizep);
/* >> devname(3), devname_r(3) */
INTDEF ATTR_CONST char *NOTHROW_NCX(LIBDCALL libd_devname)(dev_t dev, mode_t type);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> devname(3), devname_r(3) */
INTDEF ATTR_CONST char *NOTHROW_NCX(LIBCCALL libc_devname)(dev_t dev, mode_t type);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> devname(3), devname_r(3) */
INTDEF NONNULL((3)) int NOTHROW_NCX(LIBDCALL libd_devname_r)(dev_t dev, mode_t type, char *buf, size_t len);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getprogname(3), setprogname(3) */
INTDEF ATTR_CONST WUNUSED char const *NOTHROW_NCX(LIBCCALL libc_getprogname)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> getprogname(3), setprogname(3) */
INTDEF void NOTHROW_NCX(LIBDCALL libd_setprogname)(char const *name);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getprogname(3), setprogname(3) */
INTDEF void NOTHROW_NCX(LIBCCALL libc_setprogname)(char const *name);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__set_doserrno)(u32 err);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Alias for argv[0], as passed to main() */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char **NOTHROW_NCX(LIBCCALL libc___p__pgmptr)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF _purecall_handler NOTHROW_NCX(LIBDCALL libd__set_purecall_handler)(_purecall_handler __handler);
INTDEF _invalid_parameter_handler NOTHROW_NCX(LIBDCALL libd__set_invalid_parameter_handler)(_invalid_parameter_handler __handler);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__get_pgmptr)(char **pvalue);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__get_pgmptr)(char **pvalue);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__get_wpgmptr)(char16_t **pvalue);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc__get_wpgmptr)(char32_t **pvalue);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__set_fmode)(int mode);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__get_fmode)(int *pmode);
INTDEF unsigned int NOTHROW_NCX(LIBDCALL libd__set_abort_behavior)(unsigned int flags, unsigned int mask);
INTDEF ATTR_CONST WUNUSED __INT64_TYPE__ NOTHROW(LIBDCALL libd__abs64)(__INT64_TYPE__ x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED __INT64_TYPE__ NOTHROW(LIBCCALL libc__abs64)(__INT64_TYPE__ x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED NONNULL((1)) double NOTHROW_NCX(LIBDCALL libd__atof_l)(char const *__restrict nptr, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) double NOTHROW_NCX(LIBCCALL libc__atof_l)(char const *__restrict nptr, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd__atoi_l)(char const *__restrict nptr, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc__atoi_l)(char const *__restrict nptr, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED NONNULL((1)) long int NOTHROW_NCX(LIBDCALL libd__atol_l)(char const *__restrict nptr, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) long int NOTHROW_NCX(LIBCCALL libc__atol_l)(char const *__restrict nptr, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBDCALL libd__atoll_l)(char const *__restrict nptr, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBCCALL libc__atoll_l)(char const *__restrict nptr, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED u16 NOTHROW_NCX(LIBDCALL libd__byteswap_ushort)(u16 val);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED u16 NOTHROW_NCX(LIBCCALL libc__byteswap_ushort)(u16 val);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED u32 NOTHROW_NCX(LIBDCALL libd__byteswap_ulong)(u32 val);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED u32 NOTHROW_NCX(LIBCCALL libc__byteswap_ulong)(u32 val);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED u64 NOTHROW_NCX(LIBDCALL libd__byteswap_uint64)(u64 val);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED u64 NOTHROW_NCX(LIBCCALL libc__byteswap_uint64)(u64 val);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((1, 2, 5)) void *(LIBDCALL libd_bsearch_s)(void const *key, void const *base, size_t elem_count, size_t elem_size, __dos_compar_d_fn_t compar, void *arg) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((1, 2, 5)) void *(LIBCCALL libc_bsearch_s)(void const *key, void const *base, size_t elem_count, size_t elem_size, __dos_compar_d_fn_t compar, void *arg) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 4)) void (LIBDCALL libd_qsort_s)(void *base, size_t elem_count, size_t elem_size, __dos_compar_d_fn_t compar, void *arg) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 4)) void (LIBCCALL libc_qsort_s)(void *base, size_t elem_count, size_t elem_size, __dos_compar_d_fn_t compar, void *arg) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 2, 4)) errno_t NOTHROW_NCX(LIBDCALL libd_getenv_s)(size_t *psize, char *buf, rsize_t buflen, char const *varname);
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_NCX(LIBDCALL libd__dupenv_s)(char **__restrict pbuf, size_t *pbuflen, char const *varname);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd__itoa_s)(int val, char *buf, size_t buflen, int radix);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc__itoa_s)(int val, char *buf, size_t buflen, int radix);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd__ltoa_s)(long val, char *buf, size_t buflen, int radix);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc__ltoa_s)(long val, char *buf, size_t buflen, int radix);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd__ultoa_s)(unsigned long val, char *buf, size_t buflen, int radix);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc__ultoa_s)(unsigned long val, char *buf, size_t buflen, int radix);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBDCALL libd__i64toa)(s64 val, char *buf, int radix);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc__i64toa)(s64 val, char *buf, int radix);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBDCALL libd__ui64toa)(u64 val, char *buf, int radix);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc__ui64toa)(u64 val, char *buf, int radix);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd__i64toa_s)(s64 val, char *buf, size_t buflen, int radix);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc__i64toa_s)(s64 val, char *buf, size_t buflen, int radix);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd__ui64toa_s)(u64 val, char *buf, size_t buflen, int radix);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc__ui64toa_s)(u64 val, char *buf, size_t buflen, int radix);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED NONNULL((1)) s64 NOTHROW_NCX(LIBDCALL libd__atoi64)(char const *__restrict nptr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) s64 NOTHROW_NCX(LIBCCALL libc__atoi64)(char const *__restrict nptr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED NONNULL((1)) s64 NOTHROW_NCX(LIBDCALL libd__atoi64_l)(char const *__restrict nptr, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) s64 NOTHROW_NCX(LIBCCALL libc__atoi64_l)(char const *__restrict nptr, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd__mbstrlen)(char const *str);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc__mbstrlen)(char const *str);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd__mbstrnlen)(char const *str, size_t maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc__mbstrnlen)(char const *str, size_t maxlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd__mbstrlen_l)(char const *str, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc__mbstrlen_l)(char const *str, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd__mbstrnlen_l)(char const *str, size_t maxlen, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc__mbstrnlen_l)(char const *str, size_t maxlen, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd__mblen_l)(char const *str, size_t maxlen, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc__mblen_l)(char const *str, size_t maxlen, locale_t locale);
INTDEF int NOTHROW_NCX(LIBDCALL libd__mbtowc_l)(char16_t *dst, char const *src, size_t srclen, locale_t locale);
INTDEF int NOTHROW_NCX(LIBKCALL libc__mbtowc_l)(char32_t *dst, char const *src, size_t srclen, locale_t locale);
INTDEF size_t NOTHROW_NCX(LIBDCALL libd__mbstowcs_l)(char16_t *dst, char const *src, size_t dstlen, locale_t locale);
INTDEF size_t NOTHROW_NCX(LIBKCALL libc__mbstowcs_l)(char32_t *dst, char const *src, size_t dstlen, locale_t locale);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__mbstowcs_s)(size_t *presult, char16_t *dst, size_t dstsize, char const *src, size_t dstlen);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc__mbstowcs_s)(size_t *presult, char32_t *dst, size_t dstsize, char const *src, size_t dstlen);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_mbstowcs_s)(size_t *presult, char16_t *dst, size_t dstsize, char const *src, size_t dstlen);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc_mbstowcs_s)(size_t *presult, char32_t *dst, size_t dstsize, char const *src, size_t dstlen);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__mbstowcs_s_l)(size_t *presult, char16_t *dst, size_t dstsize, char const *src, size_t dstlen, locale_t locale);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc__mbstowcs_s_l)(size_t *presult, char32_t *dst, size_t dstsize, char const *src, size_t dstlen, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_rand_s)(unsigned int *__restrict randval);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
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
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_ALIGN(2) ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBDCALL libd__aligned_malloc)(size_t num_bytes, size_t min_alignment);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_ALIGN(2) ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBCCALL libc__aligned_malloc)(size_t num_bytes, size_t min_alignment);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBDCALL libd__aligned_offset_malloc)(size_t num_bytes, size_t min_alignment, size_t offset);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBCCALL libc__aligned_offset_malloc)(size_t num_bytes, size_t min_alignment, size_t offset);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_ALLOC_ALIGN(3) ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBDCALL libd__aligned_realloc)(void *aligned_mallptr, size_t newsize, size_t min_alignment);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_ALLOC_ALIGN(3) ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBCCALL libc__aligned_realloc)(void *aligned_mallptr, size_t newsize, size_t min_alignment);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_ALLOC_ALIGN(4) ATTR_ALLOC_SIZE((2, 3)) void *NOTHROW_NCX(LIBDCALL libd__aligned_recalloc)(void *aligned_mallptr, size_t count, size_t num_bytes, size_t min_alignment);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_ALLOC_ALIGN(4) ATTR_ALLOC_SIZE((2, 3)) void *NOTHROW_NCX(LIBCCALL libc__aligned_recalloc)(void *aligned_mallptr, size_t count, size_t num_bytes, size_t min_alignment);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBDCALL libd__aligned_offset_realloc)(void *aligned_mallptr, size_t newsize, size_t min_alignment, size_t offset);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBCCALL libc__aligned_offset_realloc)(void *aligned_mallptr, size_t newsize, size_t min_alignment, size_t offset);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *NOTHROW_NCX(LIBDCALL libd__aligned_offset_recalloc)(void *aligned_mallptr, size_t count, size_t num_bytes, size_t min_alignment, size_t offset);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *NOTHROW_NCX(LIBCCALL libc__aligned_offset_recalloc)(void *aligned_mallptr, size_t count, size_t num_bytes, size_t min_alignment, size_t offset);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED size_t NOTHROW_NCX(LIBDCALL libd__aligned_msize)(void *aligned_mallptr, size_t min_alignment, size_t offset);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED size_t NOTHROW_NCX(LIBCCALL libc__aligned_msize)(void *aligned_mallptr, size_t min_alignment, size_t offset);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF void NOTHROW_NCX(LIBDCALL libd__aligned_free)(void *aligned_mallptr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF void NOTHROW_NCX(LIBCCALL libc__aligned_free)(void *aligned_mallptr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF char *NOTHROW_RPC(LIBDCALL libd__fullpath)(char *buf, char const *path, size_t buflen);
INTDEF NONNULL((1, 5, 6)) errno_t NOTHROW_NCX(LIBDCALL libd__ecvt_s)(char *buf, size_t buflen, double val, int ndigit, int *__restrict decptr, int *__restrict sign);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 5, 6)) errno_t NOTHROW_NCX(LIBCCALL libc__ecvt_s)(char *buf, size_t buflen, double val, int ndigit, int *__restrict decptr, int *__restrict sign);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 5, 6)) errno_t NOTHROW_NCX(LIBDCALL libd__fcvt_s)(char *buf, size_t buflen, double val, int ndigit, int *__restrict decptr, int *__restrict sign);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 5, 6)) errno_t NOTHROW_NCX(LIBCCALL libc__fcvt_s)(char *buf, size_t buflen, double val, int ndigit, int *__restrict decptr, int *__restrict sign);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd__gcvt_s)(char *buf, size_t buflen, double val, int ndigit);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc__gcvt_s)(char *buf, size_t buflen, double val, int ndigit);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__atoflt)(float *__restrict result, char const *__restrict nptr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__atoflt)(float *__restrict result, char const *__restrict nptr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__atoflt_l)(float *__restrict result, char const *__restrict nptr, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__atoflt_l)(float *__restrict result, char const *__restrict nptr, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__atodbl)(double *__restrict result, char __KOS_FIXED_CONST *__restrict nptr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__atodbl)(double *__restrict result, char __KOS_FIXED_CONST *__restrict nptr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__atodbl_l)(double *__restrict result, char __KOS_FIXED_CONST *__restrict nptr, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__atodbl_l)(double *__restrict result, char __KOS_FIXED_CONST *__restrict nptr, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__atoldbl)(__LONGDOUBLE *__restrict result, char __KOS_FIXED_CONST *__restrict nptr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__atoldbl)(__LONGDOUBLE *__restrict result, char __KOS_FIXED_CONST *__restrict nptr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__atoldbl_l)(__LONGDOUBLE *__restrict result, char __KOS_FIXED_CONST *__restrict nptr, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__atoldbl_l)(__LONGDOUBLE *__restrict result, char __KOS_FIXED_CONST *__restrict nptr, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST unsigned int NOTHROW(LIBDCALL libd__rotl)(unsigned int val, int shift);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST unsigned int NOTHROW(LIBCCALL libc__rotl)(unsigned int val, int shift);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST unsigned int NOTHROW(LIBDCALL libd__rotr)(unsigned int val, int shift);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST unsigned int NOTHROW(LIBCCALL libc__rotr)(unsigned int val, int shift);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST u64 NOTHROW(LIBDCALL libd__rotl64)(u64 val, int shift);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST u64 NOTHROW(LIBCCALL libc__rotl64)(u64 val, int shift);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST u64 NOTHROW(LIBDCALL libd__rotr64)(u64 val, int shift);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST u64 NOTHROW(LIBCCALL libc__rotr64)(u64 val, int shift);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST unsigned long NOTHROW(LIBDCALL libd__lrotl)(unsigned long val, int shift);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST unsigned long NOTHROW(LIBCCALL libc__lrotl)(unsigned long val, int shift);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST unsigned long NOTHROW(LIBDCALL libd__lrotr)(unsigned long val, int shift);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST unsigned long NOTHROW(LIBCCALL libc__lrotr)(unsigned long val, int shift);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__putenv_s)(char const *varname, char const *val);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__putenv_s)(char const *varname, char const *val);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 2, 3)) void NOTHROW_RPC(LIBDCALL libd__searchenv)(char const *file, char const *envvar, char *__restrict resultpath);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 2, 3)) void NOTHROW_RPC(LIBCCALL libc__searchenv)(char const *file, char const *envvar, char *__restrict resultpath);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_RPC(LIBDCALL libd__searchenv_s)(char const *file, char const *envvar, char *__restrict resultpath, size_t buflen);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd__makepath)(char *__restrict buf, char const *drive, char const *dir, char const *file, char const *ext);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc__makepath)(char *__restrict buf, char const *drive, char const *dir, char const *file, char const *ext);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd__splitpath)(char const *__restrict abspath, char *drive, char *dir, char *file, char *ext);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc__splitpath)(char const *__restrict abspath, char *drive, char *dir, char *file, char *ext);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd__makepath_s)(char *buf, size_t buflen, char const *drive, char const *dir, char const *file, char const *ext);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc__makepath_s)(char *buf, size_t buflen, char const *drive, char const *dir, char const *file, char const *ext);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd__splitpath_s)(char const *__restrict abspath, char *drive, size_t drivelen, char *dir, size_t dirlen, char *file, size_t filelen, char *ext, size_t extlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc__splitpath_s)(char const *__restrict abspath, char *drive, size_t drivelen, char *dir, size_t dirlen, char *file, size_t filelen, char *ext, size_t extlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF void NOTHROW_NCX(LIBDCALL libd__seterrormode)(int mode);
INTDEF int NOTHROW_NCX(LIBDCALL libd__set_error_mode)(int mode);
INTDEF void NOTHROW_NCX(LIBDCALL libd__beep)(unsigned int freq, unsigned int duration);
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBDCALL libd_itoa)(int val, char *buf, int radix);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc_itoa)(int val, char *buf, int radix);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBDCALL libd_ltoa)(long val, char *buf, int radix);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc_ltoa)(long val, char *buf, int radix);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBDCALL libd_ultoa)(unsigned long val, char *buf, int radix);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc_ultoa)(unsigned long val, char *buf, int radix);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF onexit_t NOTHROW_NCX(LIBDCALL libd_onexit)(onexit_t func);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
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
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd__wmakepath_s)(char16_t *buf, size_t buflen, char16_t const *drive, char16_t const *dir, char16_t const *file, char16_t const *ext);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBKCALL libc__wmakepath_s)(char32_t *buf, size_t buflen, char32_t const *drive, char32_t const *dir, char32_t const *file, char32_t const *ext);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd__wmakepath)(char16_t *__restrict buf, char16_t const *drive, char16_t const *dir, char16_t const *file, char16_t const *ext);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBKCALL libc__wmakepath)(char32_t *__restrict buf, char32_t const *drive, char32_t const *dir, char32_t const *file, char32_t const *ext);
INTDEF NONNULL((1, 2, 3)) void NOTHROW_RPC(LIBDCALL libd__wsearchenv)(char16_t const *file, char16_t const *envvar, char16_t *__restrict resultpath);
INTDEF NONNULL((1, 2, 3)) void NOTHROW_RPC(LIBKCALL libc__wsearchenv)(char32_t const *file, char32_t const *envvar, char32_t *__restrict resultpath);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd__wsplitpath)(char16_t const *__restrict abspath, char16_t *drive, char16_t *dir, char16_t *file, char16_t *ext);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBKCALL libc__wsplitpath)(char32_t const *__restrict abspath, char32_t *drive, char32_t *dir, char32_t *file, char32_t *ext);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd__wsplitpath_s)(char16_t const *__restrict abspath, char16_t *drive, size_t drivelen, char16_t *dir, size_t dirlen, char16_t *file, size_t filelen, char16_t *ext, size_t extlen);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBKCALL libc__wsplitpath_s)(char32_t const *__restrict abspath, char32_t *drive, size_t drivelen, char32_t *dir, size_t dirlen, char32_t *file, size_t filelen, char32_t *ext, size_t extlen);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_STDLIB_H */
