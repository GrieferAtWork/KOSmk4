/* HASH CRC-32:0x19745140 */
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
#ifndef __local_usleep_defined
#define __local_usleep_defined
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_nanosleep64) || defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE___nanosleep) || defined(__CRT_HAVE___libc_nanosleep) || defined(__CRT_HAVE___crtSleep) || defined(__CRT_HAVE_delay)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___crtSleep_defined
#define __local___localdep___crtSleep_defined
#ifdef __CRT_HAVE___crtSleep
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(,__NOTHROW_RPC,__localdep___crtSleep,(__UINT32_TYPE__ __msecs),__crtSleep,(__msecs))
#elif defined(__CRT_HAVE_delay)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(,__NOTHROW_RPC,__localdep___crtSleep,(__UINT32_TYPE__ __msecs),delay,(__msecs))
#else /* ... */
#undef __local___localdep___crtSleep_defined
#endif /* !... */
#endif /* !__local___localdep___crtSleep_defined */
#ifndef __local___localdep_nanosleep_defined
#define __local___localdep_nanosleep_defined
#if defined(__CRT_HAVE_nanosleep) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),int,__NOTHROW_RPC,__localdep_nanosleep,(struct timespec const *__requested_time, struct timespec *__remaining),nanosleep,(__requested_time,__remaining))
#elif defined(__CRT_HAVE___nanosleep) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),int,__NOTHROW_RPC,__localdep_nanosleep,(struct timespec const *__requested_time, struct timespec *__remaining),__nanosleep,(__requested_time,__remaining))
#elif defined(__CRT_HAVE___libc_nanosleep) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),int,__NOTHROW_RPC,__localdep_nanosleep,(struct timespec const *__requested_time, struct timespec *__remaining),__libc_nanosleep,(__requested_time,__remaining))
#elif defined(__CRT_HAVE_nanosleep64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),int,__NOTHROW_RPC,__localdep_nanosleep,(struct timespec const *__requested_time, struct timespec *__remaining),nanosleep64,(__requested_time,__remaining))
#elif defined(__CRT_HAVE_nanosleep64) || defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE___nanosleep) || defined(__CRT_HAVE___libc_nanosleep)
__NAMESPACE_LOCAL_END
#include <libc/local/time/nanosleep.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_nanosleep __LIBC_LOCAL_NAME(nanosleep)
#else /* ... */
#undef __local___localdep_nanosleep_defined
#endif /* !... */
#endif /* !__local___localdep_nanosleep_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(usleep) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(usleep))(__useconds_t __useconds) {
#if defined(__CRT_HAVE_nanosleep64) || defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE___nanosleep) || defined(__CRT_HAVE___libc_nanosleep)
	struct timespec __ts;
	__ts.tv_sec  = (__TM_TYPE(time))(__useconds / __UINT32_C(1000000));
	__ts.tv_nsec = (__syscall_ulong_t)(__useconds % __UINT32_C(1000000)) * __UINT16_C(1000);
	return (__NAMESPACE_LOCAL_SYM __localdep_nanosleep)(&__ts, __NULLPTR);
#else /* __CRT_HAVE_nanosleep64 || __CRT_HAVE_nanosleep || __CRT_HAVE___nanosleep || __CRT_HAVE___libc_nanosleep */
	(__NAMESPACE_LOCAL_SYM __localdep___crtSleep)(__useconds / 1000l); /*USEC_PER_MSEC*/
	return 0;
#endif /* !__CRT_HAVE_nanosleep64 && !__CRT_HAVE_nanosleep && !__CRT_HAVE___nanosleep && !__CRT_HAVE___libc_nanosleep */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_usleep_defined
#define __local___localdep_usleep_defined
#define __localdep_usleep __LIBC_LOCAL_NAME(usleep)
#endif /* !__local___localdep_usleep_defined */
#else /* __CRT_HAVE_nanosleep64 || __CRT_HAVE_nanosleep || __CRT_HAVE___nanosleep || __CRT_HAVE___libc_nanosleep || __CRT_HAVE___crtSleep || __CRT_HAVE_delay */
#undef __local_usleep_defined
#endif /* !__CRT_HAVE_nanosleep64 && !__CRT_HAVE_nanosleep && !__CRT_HAVE___nanosleep && !__CRT_HAVE___libc_nanosleep && !__CRT_HAVE___crtSleep && !__CRT_HAVE_delay */
#endif /* !__local_usleep_defined */
