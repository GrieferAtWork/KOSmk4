/* HASH CRC-32:0xd9497949 */
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
/* (#) Portability: libiberty (/include/timeval-utils.h) */
#ifndef _TIMEVAL_UTILS_H
#define _TIMEVAL_UTILS_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/os/timeval.h>

#ifdef __CC__
__SYSDECL_BEGIN

#include <bits/types.h>
#if defined(__CRT_HAVE_timeval_add) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CDECLARE_VOID(__ATTR_NONNULL((1, 2, 3)),__NOTHROW_NCX,timeval_add,(struct timeval *__result, struct timeval const *__lhs, struct timeval const *__rhs),(__result,__lhs,__rhs))
#elif defined(__CRT_HAVE_timeval_add64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT_VOID(__ATTR_NONNULL((1, 2, 3)),__NOTHROW_NCX,timeval_add,(struct timeval *__result, struct timeval const *__lhs, struct timeval const *__rhs),timeval_add64,(__result,__lhs,__rhs))
#else /* ... */
#include <libc/local/timeval-utils/timeval_add.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(timeval_add, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) void __NOTHROW_NCX(__LIBCCALL timeval_add)(struct timeval *__result, struct timeval const *__lhs, struct timeval const *__rhs) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timeval_add))(__result, __lhs, __rhs); })
#endif /* !... */
#if defined(__CRT_HAVE_timeval_sub) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CDECLARE_VOID(__ATTR_NONNULL((1, 2, 3)),__NOTHROW_NCX,timeval_sub,(struct timeval *__result, struct timeval const *__lhs, struct timeval const *__rhs),(__result,__lhs,__rhs))
#elif defined(__CRT_HAVE_timeval_sub64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT_VOID(__ATTR_NONNULL((1, 2, 3)),__NOTHROW_NCX,timeval_sub,(struct timeval *__result, struct timeval const *__lhs, struct timeval const *__rhs),timeval_sub64,(__result,__lhs,__rhs))
#else /* ... */
#include <libc/local/timeval-utils/timeval_sub.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(timeval_sub, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) void __NOTHROW_NCX(__LIBCCALL timeval_sub)(struct timeval *__result, struct timeval const *__lhs, struct timeval const *__rhs) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timeval_sub))(__result, __lhs, __rhs); })
#endif /* !... */

#ifdef __USE_TIME64
#if defined(__CRT_HAVE_timeval_add) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT_VOID(__ATTR_NONNULL((1, 2, 3)),__NOTHROW_NCX,timeval_add64,(struct timeval64 *__result, struct timeval64 const *__lhs, struct timeval64 const *__rhs),timeval_add,(__result,__lhs,__rhs))
#elif defined(__CRT_HAVE_timeval_add64)
__CDECLARE_VOID(__ATTR_NONNULL((1, 2, 3)),__NOTHROW_NCX,timeval_add64,(struct timeval64 *__result, struct timeval64 const *__lhs, struct timeval64 const *__rhs),(__result,__lhs,__rhs))
#else /* ... */
#include <libc/local/timeval-utils/timeval_add64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(timeval_add64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) void __NOTHROW_NCX(__LIBCCALL timeval_add64)(struct timeval64 *__result, struct timeval64 const *__lhs, struct timeval64 const *__rhs) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timeval_add64))(__result, __lhs, __rhs); })
#endif /* !... */
#if defined(__CRT_HAVE_timeval_sub) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT_VOID(__ATTR_NONNULL((1, 2, 3)),__NOTHROW_NCX,timeval_sub64,(struct timeval64 *__result, struct timeval64 const *__lhs, struct timeval64 const *__rhs),timeval_sub,(__result,__lhs,__rhs))
#elif defined(__CRT_HAVE_timeval_sub64)
__CDECLARE_VOID(__ATTR_NONNULL((1, 2, 3)),__NOTHROW_NCX,timeval_sub64,(struct timeval64 *__result, struct timeval64 const *__lhs, struct timeval64 const *__rhs),(__result,__lhs,__rhs))
#else /* ... */
#include <libc/local/timeval-utils/timeval_sub64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(timeval_sub64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) void __NOTHROW_NCX(__LIBCCALL timeval_sub64)(struct timeval64 *__result, struct timeval64 const *__lhs, struct timeval64 const *__rhs) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timeval_sub64))(__result, __lhs, __rhs); })
#endif /* !... */
#endif /* __USE_TIME64 */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_TIMEVAL_UTILS_H */
