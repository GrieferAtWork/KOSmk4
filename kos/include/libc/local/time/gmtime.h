/* HASH CRC-32:0xa838a6d3 */
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
#ifndef __local_gmtime_defined
#define __local_gmtime_defined 1
#include <__crt.h>
#include <bits/types.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: gmtime32 from time */
#ifndef __local___localdep_gmtime32_defined
#define __local___localdep_gmtime32_defined 1
#ifdef __CRT_HAVE_gmtime
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_gmtime32,(__time32_t const *__timer),gmtime,(__timer))
#elif defined(__CRT_HAVE__gmtime32)
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_gmtime32,(__time32_t const *__timer),_gmtime32,(__timer))
#else /* ... */
#undef __local___localdep_gmtime32_defined
#endif /* !... */
#endif /* !__local___localdep_gmtime32_defined */
/* Dependency: gmtime64 from time */
#ifndef __local___localdep_gmtime64_defined
#define __local___localdep_gmtime64_defined 1
#ifdef __CRT_HAVE_gmtime64
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_gmtime64,(__time64_t const *__timer),gmtime64,(__timer))
#elif defined(__CRT_HAVE_gmtime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_gmtime64,(__time64_t const *__timer),gmtime,(__timer))
#elif defined(__CRT_HAVE__gmtime64)
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_gmtime64,(__time64_t const *__timer),_gmtime64,(__timer))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/gmtime64.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
#define __localdep_gmtime64 __LIBC_LOCAL_NAME(gmtime64)
#endif /* !... */
#endif /* !__local___localdep_gmtime64_defined */
/* Dependency: gmtime_r from time */
#ifndef __local___localdep_gmtime_r_defined
#define __local___localdep_gmtime_r_defined 1
#ifdef __CRT_HAVE_gmtime_r
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_gmtime_r,(__TM_TYPE(time) const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),gmtime_r,(__timer,__tp))
#elif defined(__CRT_HAVE___gmtime_r)
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_gmtime_r,(__TM_TYPE(time) const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),__gmtime_r,(__timer,__tp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/gmtime_r.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
#define __localdep_gmtime_r __LIBC_LOCAL_NAME(gmtime_r)
#endif /* !... */
#endif /* !__local___localdep_gmtime_r_defined */
__NAMESPACE_LOCAL_END
#ifdef __BUILDING_LIBC
#ifndef __LIBC_GMTIME_BUFFER_DEFINED
#define __LIBC_GMTIME_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__gmtime_buf) struct __NAMESPACE_STD_SYM tm __gmtime_buf = { 0 };
__NAMESPACE_LOCAL_END
#endif /* !__LIBC_GMTIME_BUFFER_DEFINED */
#endif /* __BUILDING_LIBC */
__NAMESPACE_LOCAL_BEGIN
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__LOCAL_LIBC(gmtime) __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct __NAMESPACE_STD_SYM tm *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(gmtime))(__TM_TYPE(time) const *__timer) {



	__time64_t __tm64 = (__time64_t)*__timer;
	return __localdep_gmtime64(&__tm64);






}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_gmtime_defined
#define __local___localdep_gmtime_defined 1
#define __localdep_gmtime __LIBC_LOCAL_NAME(gmtime)
#endif /* !__local___localdep_gmtime_defined */
#endif /* !__local_gmtime_defined */
