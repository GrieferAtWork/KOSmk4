/* HASH CRC-32:0x5affe2f5 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_ctime_defined
#define __local_ctime_defined
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_crt_ctime32_defined
#define __local___localdep_crt_ctime32_defined
#ifdef __CRT_HAVE_ctime
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_crt_ctime32,(__time32_t const *__timer),ctime,(__timer))
#elif defined(__CRT_HAVE__ctime32)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_crt_ctime32,(__time32_t const *__timer),_ctime32,(__timer))
#else /* ... */
#undef __local___localdep_crt_ctime32_defined
#endif /* !... */
#endif /* !__local___localdep_crt_ctime32_defined */
#ifndef __local___localdep_ctime64_defined
#define __local___localdep_ctime64_defined
#if defined(__CRT_HAVE_ctime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_ctime64,(__time64_t const *__timer),ctime,(__timer))
#elif defined(__CRT_HAVE_ctime64)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_ctime64,(__time64_t const *__timer),ctime64,(__timer))
#elif defined(__CRT_HAVE___ctime64)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_ctime64,(__time64_t const *__timer),__ctime64,(__timer))
#elif defined(__CRT_HAVE__ctime64)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_ctime64,(__time64_t const *__timer),_ctime64,(__timer))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/ctime64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_ctime64 __LIBC_LOCAL_NAME(ctime64)
#endif /* !... */
#endif /* !__local___localdep_ctime64_defined */
#ifndef __local___localdep_ctime_r_defined
#define __local___localdep_ctime_r_defined
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_ctime_r) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),char *,__NOTHROW_NCX,__localdep_ctime_r,(__time_t const *__restrict __timer, char __buf[26]),ctime_r,(__timer,__buf))
#elif defined(__CRT_HAVE_ctime64_r) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),char *,__NOTHROW_NCX,__localdep_ctime_r,(__time_t const *__restrict __timer, char __buf[26]),ctime64_r,(__timer,__buf))
#elif defined(__CRT_HAVE___ctime64_r) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),char *,__NOTHROW_NCX,__localdep_ctime_r,(__time_t const *__restrict __timer, char __buf[26]),__ctime64_r,(__timer,__buf))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/ctime_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_ctime_r __LIBC_LOCAL_NAME(ctime_r)
#endif /* !... */
#endif /* !__local___localdep_ctime_r_defined */
__LOCAL_LIBC(ctime) __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ctime))(__time_t const *__timer) {

	__time64_t __tm64 = (__time64_t)*__timer;
	return (__NAMESPACE_LOCAL_SYM __localdep_ctime64)(&__tm64);







}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ctime_defined
#define __local___localdep_ctime_defined
#define __localdep_ctime __LIBC_LOCAL_NAME(ctime)
#endif /* !__local___localdep_ctime_defined */
#endif /* !__local_ctime_defined */
