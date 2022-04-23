/* HASH CRC-32:0xc89cc24 */
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
#ifndef GUARD_LIBC_AUTO_STDLIB_H
#define GUARD_LIBC_AUTO_STDLIB_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <stdlib.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((1, 2, 5)) void *(LIBDCALL libd_bsearch_r)(void const *pkey, void const *pbase, size_t item_count, size_t item_size, int (LIBDCALL *compar)(void const *a, void const *b, void *arg), void *arg) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((1, 2, 5)) void *(LIBCCALL libc_bsearch_r)(void const *pkey, void const *pbase, size_t item_count, size_t item_size, int (LIBCCALL *compar)(void const *a, void const *b, void *arg), void *arg) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 4)) void (LIBDCALL libd_qsort)(void *pbase, size_t item_count, size_t item_size, int (LIBDCALL *compar)(void const *a, void const *b)) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF NONNULL((1, 4)) void (LIBCCALL libc_qsort)(void *pbase, size_t item_count, size_t item_size, int (LIBCCALL *compar)(void const *a, void const *b)) THROWS(...);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((1, 2, 5)) void *(LIBDCALL libd_bsearch)(void const *pkey, void const *pbase, size_t item_count, size_t item_size, int (LIBDCALL *compar)(void const *a, void const *b)) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((1, 2, 5)) void *(LIBCCALL libc_bsearch)(void const *pkey, void const *pbase, size_t item_count, size_t item_size, int (LIBCCALL *compar)(void const *a, void const *b)) THROWS(...);
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
 * The   return   value   is   the   exit   status   after   running  `command'
 * When `command' is `NULL' only check if a system interpreter is available.
 * When  no   system   interpreter   is  available,   `127'   is   returned. */
INTDEF int NOTHROW_RPC(LIBDCALL libd_system)(char const *command);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> system(3)
 * Execute a given `command' on the system interpreter (as in `sh -c $command')
 * The   return   value   is   the   exit   status   after   running  `command'
 * When `command' is `NULL' only check if a system interpreter is available.
 * When  no   system   interpreter   is  available,   `127'   is   returned. */
INTDEF int NOTHROW_RPC(LIBCCALL libc_system)(char const *command);
INTDEF ATTR_NORETURN void (LIBCCALL libc_abort)(void) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_NORETURN void (LIBDCALL libd_exit)(int status) THROWS(...);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_atexit)(void (LIBDCALL *func)(void));
INTDEF ATTR_NORETURN void (LIBDCALL libd_quick_exit)(int status) THROWS(...);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_at_quick_exit)(void (LIBDCALL *func)(void));
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
INTDEF NONNULL((3)) __STDC_INT32_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd_strfromd)(char *__restrict buf, size_t buflen, char const *__restrict format, double fp);
INTDEF NONNULL((3)) __STDC_INT32_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd_strfromf)(char *__restrict buf, size_t buflen, char const *__restrict format, float fp);
INTDEF NONNULL((3)) __STDC_INT32_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd_strfroml)(char *__restrict buf, size_t buflen, char const *__restrict format, __LONGDOUBLE fp);
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
 *               This error supersedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBDCALL libd_strtou32_r)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
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
 *               This error supersedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBCCALL libc_strtou32_r)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
 *               This error supersedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBDCALL libd_strto32_r)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
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
 *               This error supersedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBCCALL libc_strto32_r)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
 *               This error supersedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBDCALL libd_strtou64_r)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
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
 *               This error supersedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBCCALL libc_strtou64_r)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
 *               This error supersedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
INTDEF ATTR_LEAF NONNULL((1)) int64_t NOTHROW_NCX(LIBDCALL libd_strto64_r)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
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
 *               This error supersedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
INTDEF ATTR_LEAF NONNULL((1)) int64_t NOTHROW_NCX(LIBCCALL libc_strto64_r)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, errno_t *error);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBDCALL libd_strtou32)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
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
INTDEF ATTR_LEAF NONNULL((1)) uint32_t NOTHROW_NCX(LIBCCALL libc_strtou32)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBDCALL libd_strto32)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
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
INTDEF ATTR_LEAF NONNULL((1)) int32_t NOTHROW_NCX(LIBCCALL libc_strto32)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBDCALL libd_strtou64)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
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
INTDEF ATTR_LEAF NONNULL((1)) uint64_t NOTHROW_NCX(LIBCCALL libc_strtou64)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_LEAF NONNULL((1)) int64_t NOTHROW_NCX(LIBDCALL libd_strto64)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
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
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_rand_r)(unsigned int *__restrict pseed);
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
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `template_' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all  'X'-characters before the  call (else errno=EINVAL  + return -1), with
 * random  characters such that the filename described by `template_' will not
 * already  exists. Then, create a new file  with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The #  of trailing  characters to-be  ignored
 *                    after the required 6 trailing 'X'-characters. */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_RPC(LIBDCALL libd_mkstemps)(char *template_, __STDC_INT_AS_SIZE_T suffixlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `template_' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all  'X'-characters before the  call (else errno=EINVAL  + return -1), with
 * random  characters such that the filename described by `template_' will not
 * already  exists. Then, create a new file  with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The #  of trailing  characters to-be  ignored
 *                    after the required 6 trailing 'X'-characters. */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_RPC(LIBCCALL libc_mkstemps)(char *template_, __STDC_INT_AS_SIZE_T suffixlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_rpmatch)(char const *response);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_rpmatch)(char const *response);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF int NOTHROW_RPC(LIBDCALL libd_getloadavg)(double loadavg[], __STDC_INT_AS_SIZE_T nelem);
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `template_' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all  'X'-characters before the  call (else errno=EINVAL  + return -1), with
 * random  characters such that the filename described by `template_' will not
 * already  exists. Then, create a new file  with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The #  of trailing  characters to-be  ignored
 *                    after the required 6 trailing 'X'-characters. */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_RPC(LIBDCALL libd_mkstemps64)(char *template_, __STDC_INT_AS_SIZE_T suffixlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `template_' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all  'X'-characters before the  call (else errno=EINVAL  + return -1), with
 * random  characters such that the filename described by `template_' will not
 * already  exists. Then, create a new file  with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The #  of trailing  characters to-be  ignored
 *                    after the required 6 trailing 'X'-characters. */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_RPC(LIBCCALL libc_mkstemps64)(char *template_, __STDC_INT_AS_SIZE_T suffixlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) double NOTHROW_NCX(LIBDCALL libd_erand48)(unsigned short xsubi[3]);
INTDEF NONNULL((1)) long NOTHROW_NCX(LIBDCALL libd_nrand48)(unsigned short xsubi[3]);
INTDEF NONNULL((1)) long NOTHROW_NCX(LIBDCALL libd_jrand48)(unsigned short xsubi[3]);
INTDEF void NOTHROW_NCX(LIBDCALL libd_srand48)(long seedval);
INTDEF NONNULL((1)) unsigned short *NOTHROW_NCX(LIBDCALL libd_seed48)(unsigned short seed16v[3]);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd_lcong48)(unsigned short param[7]);
INTDEF void NOTHROW_NCX(LIBDCALL libd_srandom)(unsigned int seed);
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBDCALL libd_initstate)(unsigned int seed, char *statebuf, size_t statelen);
INTDEF NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_setstate)(char *statebuf);
/* >> l64a(3), a64l(3)
 * Convert between `long' and base-64 encoded integer strings. */
INTDEF ATTR_RETNONNULL WUNUSED char *NOTHROW_NCX(LIBDCALL libd_l64a)(long n);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> l64a(3), a64l(3)
 * Convert between `long' and base-64 encoded integer strings. */
INTDEF ATTR_RETNONNULL WUNUSED char *NOTHROW_NCX(LIBCCALL libc_l64a)(long n);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> l64a(3), a64l(3)
 * Convert between `long' and base-64 encoded integer strings. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) long NOTHROW_NCX(LIBDCALL libd_a64l)(char const *s);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> l64a(3), a64l(3)
 * Convert between `long' and base-64 encoded integer strings. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) long NOTHROW_NCX(LIBCCALL libc_a64l)(char const *s);
/* >> realpath(3)
 * Load the filesystem location of a given file handle.
 * This  function behaves similar to `readlink()', but will also function for
 * non-symlink paths, as well as always return an absolute (unambiguous) path
 * @param: resolved: A buffer of `PATH_MAX' bytes to-be filled with the resulting
 *                   path, or NULL  to automatically `malloc()'ate  and return  a
 *                   buffer of sufficient size. */
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_RPC(LIBDCALL libd_realpath)(char const *filename, char *resolved);
/* >> realpath(3)
 * Load the filesystem location of a given file handle.
 * This  function behaves similar to `readlink()', but will also function for
 * non-symlink paths, as well as always return an absolute (unambiguous) path
 * @param: resolved: A buffer of `PATH_MAX' bytes to-be filled with the resulting
 *                   path, or NULL  to automatically `malloc()'ate  and return  a
 *                   buffer of sufficient size. */
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_RPC(LIBCCALL libc_realpath)(char const *filename, char *resolved);
/* >> frealpath(3)
 * Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
INTDEF WUNUSED char *NOTHROW_RPC(LIBDCALL libd_frealpath)(fd_t fd, char *resolved, size_t buflen);
/* >> frealpath(3)
 * Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
INTDEF WUNUSED char *NOTHROW_RPC(LIBCCALL libc_frealpath)(fd_t fd, char *resolved, size_t buflen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mktemp(3)
 * Badly designed version of  `mkstemp' that won't actually  create
 * the temporary file, meaning that by the time the caller tries to
 * create the  file themselves,  another process  may have  already
 * created it.
 * Also: when no  temporary filename  can be  created, rather  than
 *       returning something  sensible like  `NULL', this  function
 *       will instead set `template_' to an empty string, and still
 *       re-return it like it would if everything had worked! */
INTDEF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_mktemp)(char *template_);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mktemp(3)
 * Badly designed version of  `mkstemp' that won't actually  create
 * the temporary file, meaning that by the time the caller tries to
 * create the  file themselves,  another process  may have  already
 * created it.
 * Also: when no  temporary filename  can be  created, rather  than
 *       returning something  sensible like  `NULL', this  function
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
 * Replace the last 6 characters of  `template_', which must be filled  with
 * all  'X'-characters  before the  call  (else errno=EINVAL  +  return -1),
 * with random characters  such that the  filename described by  `template_'
 * will not already exists. Then, create a new file with `O_RDWR' and return
 * the file descriptor of that file. */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_RPC(LIBDCALL libd_mkstemp)(char *template_);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mkstemp(3), mkstemp64(3)
 * Replace the last 6 characters of  `template_', which must be filled  with
 * all  'X'-characters  before the  call  (else errno=EINVAL  +  return -1),
 * with random characters  such that the  filename described by  `template_'
 * will not already exists. Then, create a new file with `O_RDWR' and return
 * the file descriptor of that file. */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_RPC(LIBCCALL libc_mkstemp)(char *template_);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mkstemp(3), mkstemp64(3)
 * Replace the last 6 characters of  `template_', which must be filled  with
 * all  'X'-characters  before the  call  (else errno=EINVAL  +  return -1),
 * with random characters  such that the  filename described by  `template_'
 * will not already exists. Then, create a new file with `O_RDWR' and return
 * the file descriptor of that file. */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_RPC(LIBDCALL libd_mkstemp64)(char *template_);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mkstemp(3), mkstemp64(3)
 * Replace the last 6 characters of  `template_', which must be filled  with
 * all  'X'-characters  before the  call  (else errno=EINVAL  +  return -1),
 * with random characters  such that the  filename described by  `template_'
 * will not already exists. Then, create a new file with `O_RDWR' and return
 * the file descriptor of that file. */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_RPC(LIBCCALL libc_mkstemp64)(char *template_);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mkdtemp(3)
 * Replace the last 6 characters of `template_', which must be filled with
 * all  'X'-characters before  the call  (else errno=EINVAL  + return -1),
 * with random characters such that the pathname described by  `template_'
 * will not already exists. Then, create a new directory with `mode=0700',
 * and re-return `template_' to indicate success.
 * On error, `NULL' will be returned, and the contents of `template_' are undefined. */
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_RPC(LIBDCALL libd_mkdtemp)(char *template_);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mkdtemp(3)
 * Replace the last 6 characters of `template_', which must be filled with
 * all  'X'-characters before  the call  (else errno=EINVAL  + return -1),
 * with random characters such that the pathname described by  `template_'
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
/* >> ptsname(3)
 * Returns the name of the PTY slave (Pseudo TTY slave)
 * associated   with   the   master   descriptor   `fd' */
INTDEF WUNUSED char *NOTHROW_NCX(LIBDCALL libd_ptsname)(fd_t fd);
/* >> ptsname(3)
 * Returns the name of the PTY slave (Pseudo TTY slave)
 * associated   with   the   master   descriptor   `fd' */
INTDEF WUNUSED char *NOTHROW_NCX(LIBCCALL libc_ptsname)(fd_t fd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED fd_t NOTHROW_RPC(LIBDCALL libd_posix_openpt)(oflag_t oflags);
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
/* >> secure_getenv(3)
 * Same as `getenv(3)', but always  return `NULL' if the  caller
 * is running in set-ugid mode (s.a. `__libc_enable_secure(3)'). */
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_secure_getenv)(char const *varname);
/* >> secure_getenv(3)
 * Same as `getenv(3)', but always  return `NULL' if the  caller
 * is running in set-ugid mode (s.a. `__libc_enable_secure(3)'). */
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_secure_getenv)(char const *varname);
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
 * This  function is used  to implement `system(3)' and  `popen(3)', and may be
 * used to invoke the system interpreter.
 * This function only returns on failure (similar to exec(2)), and will never
 * return on success (since in that case, the calling program will have  been
 * replaced by the system shell)
 * The shell paths attempted by this function are system-dependent, but before any
 * of them are tested, this function will try to use `secure_getenv("SHELL")',  if
 * and only if that variable is defined and starts with a '/'-character. */
INTDEF int NOTHROW_RPC(LIBDCALL libd_shexec)(char const *command);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> shexec(3)
 * Execute command with the system interpreter (such as: `/bin/sh -c $command')
 * This  function is used  to implement `system(3)' and  `popen(3)', and may be
 * used to invoke the system interpreter.
 * This function only returns on failure (similar to exec(2)), and will never
 * return on success (since in that case, the calling program will have  been
 * replaced by the system shell)
 * The shell paths attempted by this function are system-dependent, but before any
 * of them are tested, this function will try to use `secure_getenv("SHELL")',  if
 * and only if that variable is defined and starts with a '/'-character. */
INTDEF int NOTHROW_RPC(LIBCCALL libc_shexec)(char const *command);
/* Returns the absolute filename of the main executable (s.a. `program_invocation_name') */
INTDEF ATTR_CONST WUNUSED char const *NOTHROW_NCX(LIBDCALL libd_getexecname)(void);
/* Returns the absolute filename of the main executable (s.a. `program_invocation_name') */
INTDEF ATTR_CONST WUNUSED char const *NOTHROW_NCX(LIBCCALL libc_getexecname)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Enumerate all open file descriptors by  invoking `(*walk)(arg, <fd>)' for each of  them
 * If during any of these invocations, `(*walk)(...)' returns non-zero, enumeration stops,
 * and  `fdwalk()' returns with that same value. If `(*walk)(...)' is never called, or all
 * invocations return 0, `fdwalk()' will also return 0. */
INTDEF NONNULL((1)) int (LIBDCALL libd_fdwalk)(int (LIBDCALL *walk)(void *arg, fd_t fd), void *arg) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Enumerate all open file descriptors by  invoking `(*walk)(arg, <fd>)' for each of  them
 * If during any of these invocations, `(*walk)(...)' returns non-zero, enumeration stops,
 * and  `fdwalk()' returns with that same value. If `(*walk)(...)' is never called, or all
 * invocations return 0, `fdwalk()' will also return 0. */
INTDEF NONNULL((1)) int (LIBCCALL libc_fdwalk)(int (LIBCCALL *walk)(void *arg, fd_t fd), void *arg) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) char *NOTHROW_NCX(LIBDCALL libd_lltostr)(__LONGLONG value, char *buf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc_lltostr)(__LONGLONG value, char *buf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) char *NOTHROW_NCX(LIBDCALL libd_ulltostr)(__ULONGLONG value, char *buf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc_ulltostr)(__ULONGLONG value, char *buf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBDCALL libd_reallocf)(void *mallptr, size_t num_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBCCALL libc_reallocf)(void *mallptr, size_t num_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> recallocarray(3)
 * Same   as    `recallocv(mallptr, new_elem_count, elem_size)',   but    also   ensure    that
 * when `mallptr != NULL', memory pointed to by the old  `mallptr...+=old_elem_count*elem_size'
 * is explicitly freed to zero (s.a. `freezero()') when reallocation must move the memory block */
INTDEF ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((3, 4)) void *NOTHROW_NCX(LIBDCALL libd_recallocarray)(void *mallptr, size_t old_elem_count, size_t new_elem_count, size_t elem_size);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> recallocarray(3)
 * Same   as    `recallocv(mallptr, new_elem_count, elem_size)',   but    also   ensure    that
 * when `mallptr != NULL', memory pointed to by the old  `mallptr...+=old_elem_count*elem_size'
 * is explicitly freed to zero (s.a. `freezero()') when reallocation must move the memory block */
INTDEF ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((3, 4)) void *NOTHROW_NCX(LIBCCALL libc_recallocarray)(void *mallptr, size_t old_elem_count, size_t new_elem_count, size_t elem_size);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> freezero(3)
 * Same as  `free(mallptr)', but  also ensure  that the  memory  region
 * described by `mallptr...+=num_bytes' is explicitly freed to zero, or
 * immediately returned  to the  OS, rather  than being  left in  cache
 * while still containing its previous contents. */
INTDEF void NOTHROW_NCX(LIBDCALL libd_freezero)(void *mallptr, size_t num_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> freezero(3)
 * Same as  `free(mallptr)', but  also ensure  that the  memory  region
 * described by `mallptr...+=num_bytes' is explicitly freed to zero, or
 * immediately returned  to the  OS, rather  than being  left in  cache
 * while still containing its previous contents. */
INTDEF void NOTHROW_NCX(LIBCCALL libc_freezero)(void *mallptr, size_t num_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((1, 2)) char *NOTHROW_NCX(LIBDCALL libd_getbsize)(int *headerlenp, __LONGPTR_TYPE__ *blocksizep);
/* >> l64a_r(3)
 * Reentrant variant of `l64a(3)'. Note that the max required buffer size
 * @param: buf:     Target buffer (with a size of `bufsize' bytes)
 * @param: bufsize: Buffer size (including a trailing NUL-character)
 * @return: 0 : Success
 * @return: -1: Buffer too small (`errno' was not modified) */
INTDEF int NOTHROW_NCX(LIBDCALL libd_l64a_r)(long n, char *buf, __STDC_INT_AS_SIZE_T bufsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> l64a_r(3)
 * Reentrant variant of `l64a(3)'. Note that the max required buffer size
 * @param: buf:     Target buffer (with a size of `bufsize' bytes)
 * @param: bufsize: Buffer size (including a trailing NUL-character)
 * @return: 0 : Success
 * @return: -1: Buffer too small (`errno' was not modified) */
INTDEF int NOTHROW_NCX(LIBCCALL libc_l64a_r)(long n, char *buf, __STDC_INT_AS_SIZE_T bufsize);
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
INTDEF NONNULL((1, 4)) int (LIBDCALL libd_heapsort)(void *pbase, size_t item_count, size_t item_size, int (LIBDCALL *compar)(void const *a, void const *b)) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 4)) int (LIBCCALL libc_heapsort)(void *pbase, size_t item_count, size_t item_size, int (LIBCCALL *compar)(void const *a, void const *b)) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 4)) int (LIBDCALL libd_mergesort)(void *pbase, size_t item_count, size_t item_size, int (LIBDCALL *compar)(void const *a, void const *b)) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 4)) int (LIBCCALL libc_mergesort)(void *pbase, size_t item_count, size_t item_size, int (LIBCCALL *compar)(void const *a, void const *b)) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_radixsort)(unsigned char const **base, int item_count, unsigned char const *table, unsigned endbyte);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_sradixsort)(unsigned char const **base, int item_count, unsigned char const *table, unsigned endbyte);
/* >> strtonum(3)
 * Similar to `strtoi()'  with `base=10',  but return  human-
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
 * Similar to `strtoi()'  with `base=10',  but return  human-
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
/* >> qsort_r(3) */
INTDEF NONNULL((1, 4)) void (LIBDCALL libd_qsort_r)(void *pbase, size_t item_count, size_t item_size, int (LIBDCALL *compar)(void const *a, void const *b, void *arg), void *arg) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> qsort_r(3) */
INTDEF NONNULL((1, 4)) void (LIBCCALL libc_qsort_r)(void *pbase, size_t item_count, size_t item_size, int (LIBCCALL *compar)(void const *a, void const *b, void *arg), void *arg) THROWS(...);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mkostemp(3), mkostemp64(3)
 * Replace  the  last 6  characters of  `template_' (which  are followed  by exactly
 * `suffixlen'  more  characters that  are left  alone), which  must be  filled with
 * all  'X'-characters  before  the  call  (else  errno=EINVAL  +  return  -1), with
 * random  characters  such  that the  filename  described by  `template_'  will not
 * already exists. Then, create a new file with `O_RDWR | flags' and return the file
 * descriptor of that file.
 * @param: flags: Additional  flags  to pass  to `open(2)',
 *                but `O_ACCMODE' is always set to `O_RDWR' */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_NCX(LIBDCALL libd_mkostemp)(char *template_, oflag_t flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mkostemp(3), mkostemp64(3)
 * Replace  the  last 6  characters of  `template_' (which  are followed  by exactly
 * `suffixlen'  more  characters that  are left  alone), which  must be  filled with
 * all  'X'-characters  before  the  call  (else  errno=EINVAL  +  return  -1), with
 * random  characters  such  that the  filename  described by  `template_'  will not
 * already exists. Then, create a new file with `O_RDWR | flags' and return the file
 * descriptor of that file.
 * @param: flags: Additional  flags  to pass  to `open(2)',
 *                but `O_ACCMODE' is always set to `O_RDWR' */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_NCX(LIBCCALL libc_mkostemp)(char *template_, oflag_t flags);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_NCX(LIBDCALL libd_mkostemps)(char *template_, __STDC_INT_AS_SIZE_T suffixlen, oflag_t flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_NCX(LIBCCALL libc_mkostemps)(char *template_, __STDC_INT_AS_SIZE_T suffixlen, oflag_t flags);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mkostemp(3), mkostemp64(3)
 * Replace  the  last 6  characters of  `template_' (which  are followed  by exactly
 * `suffixlen'  more  characters that  are left  alone), which  must be  filled with
 * all  'X'-characters  before  the  call  (else  errno=EINVAL  +  return  -1), with
 * random  characters  such  that the  filename  described by  `template_'  will not
 * already exists. Then, create a new file with `O_RDWR | flags' and return the file
 * descriptor of that file.
 * @param: flags: Additional  flags  to pass  to `open(2)',
 *                but `O_ACCMODE' is always set to `O_RDWR' */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_NCX(LIBDCALL libd_mkostemp64)(char *template_, oflag_t flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mkostemp(3), mkostemp64(3)
 * Replace  the  last 6  characters of  `template_' (which  are followed  by exactly
 * `suffixlen'  more  characters that  are left  alone), which  must be  filled with
 * all  'X'-characters  before  the  call  (else  errno=EINVAL  +  return  -1), with
 * random  characters  such  that the  filename  described by  `template_'  will not
 * already exists. Then, create a new file with `O_RDWR | flags' and return the file
 * descriptor of that file.
 * @param: flags: Additional  flags  to pass  to `open(2)',
 *                but `O_ACCMODE' is always set to `O_RDWR' */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_NCX(LIBCCALL libc_mkostemp64)(char *template_, oflag_t flags);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_NCX(LIBDCALL libd_mkostemps64)(char *template_, __STDC_INT_AS_SIZE_T suffixlen, oflag_t flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_NCX(LIBCCALL libc_mkostemps64)(char *template_, __STDC_INT_AS_SIZE_T suffixlen, oflag_t flags);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
/* >> humanize_number(3), dehumanize_number(3)
 * @param: scale: Set of `HN_GETSCALE | HN_AUTOSCALE'
 * @param: flags: Set of `HN_DECIMAL | HN_NOSPACE | HN_B | HN_DIVISOR_1000 | HN_IEC_PREFIXES' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_humanize_number)(char *buf, size_t len, int64_t bytes, char const *suffix, int scale, int flags);
/* >> humanize_number(3), dehumanize_number(3)
 * @param: scale: Set of `HN_GETSCALE | HN_AUTOSCALE'
 * @param: flags: Set of `HN_DECIMAL | HN_NOSPACE | HN_B | HN_DIVISOR_1000 | HN_IEC_PREFIXES' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_dehumanize_number)(char const *str, int64_t *size);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_vsetproctitle)(char const *format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> setproctitle(3)
 * Set the program comm name. S.a.:
 *  - pthread_setname_np(3)
 *  - prctl(PR_SET_NAME)
 *  - "/proc/self/comm" */
INTDEF ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) void NOTHROW_NCX(VLIBDCALL libd_setproctitle)(char const *format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> setproctitle(3)
 * Set the program comm name. S.a.:
 *  - pthread_setname_np(3)
 *  - prctl(PR_SET_NAME)
 *  - "/proc/self/comm" */
INTDEF ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) void NOTHROW_NCX(VLIBCCALL libc_setproctitle)(char const *format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strsuftoll(3)
 * Same as `strsuftollx(3)', but if an error happens, make
 * use of `errx(3)' to terminate the program, rather  than
 * return to the caller. */
INTDEF WUNUSED NONNULL((1, 2)) __LONGLONG NOTHROW_NCX(LIBDCALL libd_strsuftoll)(char const *desc, char const *val, __LONGLONG lo, __LONGLONG hi);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strsuftoll(3)
 * Same as `strsuftollx(3)', but if an error happens, make
 * use of `errx(3)' to terminate the program, rather  than
 * return to the caller. */
INTDEF WUNUSED NONNULL((1, 2)) __LONGLONG NOTHROW_NCX(LIBCCALL libc_strsuftoll)(char const *desc, char const *val, __LONGLONG lo, __LONGLONG hi);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strsuftollx(3) */
INTDEF WUNUSED NONNULL((1, 2)) __LONGLONG NOTHROW_NCX(LIBDCALL libd_strsuftollx)(char const *desc, char const *val, __LONGLONG lo, __LONGLONG hi, char *errbuf, size_t errbuflen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strsuftollx(3) */
INTDEF WUNUSED NONNULL((1, 2)) __LONGLONG NOTHROW_NCX(LIBCCALL libc_strsuftollx)(char const *desc, char const *val, __LONGLONG lo, __LONGLONG hi, char *errbuf, size_t errbuflen);
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
INTDEF _invalid_parameter_handler NOTHROW_NCX(LIBDCALL libd__set_invalid_parameter_handler)(_invalid_parameter_handler handler);
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
INTDEF WUNUSED NONNULL((1, 2, 5)) void *(LIBDCALL libd_bsearch_s)(void const *key, void const *base, size_t elem_count, size_t elem_size, int (LIBDCALL *compar)(void *arg, void const *a, void const *b), void *arg) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((1, 2, 5)) void *(LIBCCALL libc_bsearch_s)(void const *key, void const *base, size_t elem_count, size_t elem_size, int (LIBCCALL *compar)(void *arg, void const *a, void const *b), void *arg) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 4)) void (LIBDCALL libd_qsort_s)(void *base, size_t elem_count, size_t elem_size, int (LIBDCALL *compar)(void *arg, void const *a, void const *b), void *arg) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 4)) void (LIBCCALL libc_qsort_s)(void *base, size_t elem_count, size_t elem_size, int (LIBCCALL *compar)(void *arg, void const *a, void const *b), void *arg) THROWS(...);
INTDEF NONNULL((1, 2, 4)) errno_t NOTHROW_NCX(LIBDCALL libd_getenv_s)(size_t *preqsize, char *buf, rsize_t bufsize, char const *varname);
INTDEF NONNULL((1, 2, 4)) errno_t NOTHROW_NCX(LIBCCALL libc_getenv_s)(size_t *preqsize, char *buf, rsize_t bufsize, char const *varname);
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_NCX(LIBDCALL libd__dupenv_s)(char **__restrict pbuf, size_t *pbuflen, char const *varname);
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_NCX(LIBCCALL libc__dupenv_s)(char **__restrict pbuf, size_t *pbuflen, char const *varname);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd__itoa_s)(int val, char *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc__itoa_s)(int val, char *buf, size_t buflen, int radix);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd__ltoa_s)(long val, char *buf, size_t buflen, int radix);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc__ltoa_s)(long val, char *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd__ultoa_s)(unsigned long val, char *buf, size_t buflen, int radix);
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
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd__i64toa_s)(s64 val, char *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc__i64toa_s)(s64 val, char *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd__ui64toa_s)(u64 val, char *buf, size_t buflen, int radix);
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
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_mbstowcs_s)(size_t *presult, char16_t *dst, size_t dstsize, char const *src, size_t dstlen);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc_mbstowcs_s)(size_t *presult, char32_t *dst, size_t dstsize, char const *src, size_t dstlen);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__mbstowcs_s_l)(size_t *presult, char16_t *dst, size_t dstsize, char const *src, size_t dstlen, locale_t locale);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc__mbstowcs_s_l)(size_t *presult, char32_t *dst, size_t dstsize, char const *src, size_t dstlen, locale_t locale);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_rand_s)(unsigned int *__restrict randval);
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
/* >> _fullpath(3)
 * s.a. `realpath(3)', `frealpathat(3)' */
INTDEF WUNUSED NONNULL((2)) char *NOTHROW_RPC(LIBDCALL libd__fullpath)(char *buf, char const *path, size_t buflen);
/* >> _fullpath(3)
 * s.a. `realpath(3)', `frealpathat(3)' */
INTDEF WUNUSED NONNULL((2)) char *NOTHROW_RPC(LIBCCALL libc__fullpath)(char *buf, char const *path, size_t buflen);
INTDEF NONNULL((1, 5, 6)) errno_t NOTHROW_NCX(LIBDCALL libd__ecvt_s)(char *buf, size_t buflen, double val, int ndigit, int *__restrict decptr, int *__restrict sign);
INTDEF NONNULL((1, 5, 6)) errno_t NOTHROW_NCX(LIBCCALL libc__ecvt_s)(char *buf, size_t buflen, double val, int ndigit, int *__restrict decptr, int *__restrict sign);
INTDEF NONNULL((1, 5, 6)) errno_t NOTHROW_NCX(LIBDCALL libd__fcvt_s)(char *buf, size_t buflen, double val, int ndigit, int *__restrict decptr, int *__restrict sign);
INTDEF NONNULL((1, 5, 6)) errno_t NOTHROW_NCX(LIBCCALL libc__fcvt_s)(char *buf, size_t buflen, double val, int ndigit, int *__restrict decptr, int *__restrict sign);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd__gcvt_s)(char *buf, size_t buflen, double val, int ndigit);
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
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__putenv_s)(char const *varname, char const *val);
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
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd__makepath_s)(char *buf, size_t buflen, char const *drive, char const *dir, char const *file, char const *ext);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc__makepath_s)(char *buf, size_t buflen, char const *drive, char const *dir, char const *file, char const *ext);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd__splitpath_s)(char const *__restrict abspath, char *drive, size_t drivelen, char *dir, size_t dirlen, char *file, size_t filelen, char *ext, size_t extlen);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc__splitpath_s)(char const *__restrict abspath, char *drive, size_t drivelen, char *dir, size_t dirlen, char *file, size_t filelen, char *ext, size_t extlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF void NOTHROW_NCX(LIBDCALL libd__seterrormode)(int mode);
INTDEF int NOTHROW_NCX(LIBDCALL libd__set_error_mode)(int mode);
INTDEF void NOTHROW_NCX(LIBDCALL libd__beep)(unsigned int freq, unsigned int duration);
/* >> _sleep(3)
 * Sleep for `milli' milliseconds (1/1.000 seconds) */
INTDEF void NOTHROW_RPC(LIBDCALL libd__sleep)(uint32_t milli);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> _sleep(3)
 * Sleep for `milli' milliseconds (1/1.000 seconds) */
INTDEF void NOTHROW_RPC(LIBCCALL libc__sleep)(uint32_t milli);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF NONNULL((1, 2, 4)) errno_t NOTHROW_NCX(LIBDCALL libd__wgetenv_s)(size_t *preqsize, char16_t *buf, rsize_t bufsize, char16_t const *varname);
INTDEF NONNULL((1, 2, 4)) errno_t NOTHROW_NCX(LIBKCALL libc__wgetenv_s)(size_t *preqsize, char32_t *buf, rsize_t bufsize, char32_t const *varname);
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_NCX(LIBDCALL libd__wdupenv_s)(char16_t **__restrict pbuf, size_t *pbuflen, char16_t const *varname);
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_NCX(LIBKCALL libc__wdupenv_s)(char32_t **__restrict pbuf, size_t *pbuflen, char32_t const *varname);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) errno_t NOTHROW_RPC(LIBDCALL libd__get_environ)(char ***p_environ);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) errno_t NOTHROW_RPC(LIBCCALL libc__get_environ)(char ***p_environ);
INTDEF NONNULL((1)) errno_t NOTHROW_RPC(LIBDCALL libd__get_wenviron)(char16_t ***p_wenviron);
INTDEF NONNULL((1)) errno_t NOTHROW_RPC(LIBKCALL libc__get_wenviron)(char32_t ***p_wenviron);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_STDLIB_H */
