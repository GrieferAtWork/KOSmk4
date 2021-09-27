/* HASH CRC-32:0xf6e25b1d */
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
#ifndef __local_localtime64_defined
#define __local_localtime64_defined
#include <__crt.h>
#include <bits/types.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_localtime32_defined
#define __local___localdep_localtime32_defined
#ifdef __CRT_HAVE_localtime
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime32,(__time64_t const *__timer),localtime,(__timer))
#elif defined(__CRT_HAVE__localtime32)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime32,(__time64_t const *__timer),_localtime32,(__timer))
#else /* ... */
#undef __local___localdep_localtime32_defined
#endif /* !... */
#endif /* !__local___localdep_localtime32_defined */
#ifndef __local___localdep_localtime64_r_defined
#define __local___localdep_localtime64_r_defined
#if defined(__CRT_HAVE_localtime_r) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),localtime_r,(__timer,__tp))
#elif defined(__CRT_HAVE_localtime64_r)
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),localtime64_r,(__timer,__tp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/localtime64_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_localtime64_r __LIBC_LOCAL_NAME(localtime64_r)
#endif /* !... */
#endif /* !__local___localdep_localtime64_r_defined */
__NAMESPACE_LOCAL_END
#if defined(__BUILDING_LIBC) || (!defined(__CRT_HAVE_localtime) && !defined(__CRT_HAVE__localtime32))
#ifndef __LIBC_GMTIME_BUFFER_DEFINED
#define __LIBC_GMTIME_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__gmtime_buf) struct __NAMESPACE_STD_SYM tm __gmtime_buf = { 0 };
__NAMESPACE_LOCAL_END
#endif /* !__LIBC_GMTIME_BUFFER_DEFINED */
#endif /* __BUILDING_LIBC || (!__CRT_HAVE_localtime && !__CRT_HAVE__localtime32) */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(localtime64) __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct __NAMESPACE_STD_SYM tm *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(localtime64))(__time64_t const *__timer) {
#if defined(__CRT_HAVE_localtime) || defined(__CRT_HAVE__localtime32)
	__time32_t __tm32 = (__time32_t)*__timer;
	return (__NAMESPACE_LOCAL_SYM __localdep_localtime32)(&__tm32);
#else /* __CRT_HAVE_localtime || __CRT_HAVE__localtime32 */
	return (__NAMESPACE_LOCAL_SYM __localdep_localtime64_r)(__timer, &__NAMESPACE_LOCAL_SYM __gmtime_buf);
#endif /* !__CRT_HAVE_localtime && !__CRT_HAVE__localtime32 */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_localtime64_defined
#define __local___localdep_localtime64_defined
#define __localdep_localtime64 __LIBC_LOCAL_NAME(localtime64)
#endif /* !__local___localdep_localtime64_defined */
#endif /* !__local_localtime64_defined */
