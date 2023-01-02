/* HASH CRC-32:0xe016d04c */
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
#ifndef __local__sleep_defined
#define __local__sleep_defined
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_nanosleep64) || defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE___nanosleep) || defined(__CRT_HAVE___libc_nanosleep)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
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
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/nanosleep.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_nanosleep __LIBC_LOCAL_NAME(nanosleep)
#endif /* !... */
#endif /* !__local___localdep_nanosleep_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/timespec.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_sleep) void
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_sleep))(__UINT32_TYPE__ __milli) {
	struct timespec __ts;
	__ts.tv_sec  = __milli / 1000;
	__ts.tv_nsec = (__milli % 1000) * 1000;
#if defined(__libc_geterrno) && defined(__EINTR)
	{
		struct timespec __rem;
		for (;;) {
			__rem.tv_sec  = 0;
			__rem.tv_nsec = 0;
			if ((__NAMESPACE_LOCAL_SYM __localdep_nanosleep)(&__ts, &__rem) == 0)
				break;
			if (__libc_geterrno() == __EINTR)
				break;
			__ts.tv_sec  = __rem.tv_sec;
			__ts.tv_nsec = __rem.tv_nsec;
		}
	}
#else /* __libc_geterrno && __EINTR */
	(__NAMESPACE_LOCAL_SYM __localdep_nanosleep)(&__ts, __NULLPTR);
#endif /* !__libc_geterrno || !__EINTR */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__sleep_defined
#define __local___localdep__sleep_defined
#define __localdep__sleep __LIBC_LOCAL_NAME(_sleep)
#endif /* !__local___localdep__sleep_defined */
#else /* __CRT_HAVE_nanosleep64 || __CRT_HAVE_nanosleep || __CRT_HAVE___nanosleep || __CRT_HAVE___libc_nanosleep */
#undef __local__sleep_defined
#endif /* !__CRT_HAVE_nanosleep64 && !__CRT_HAVE_nanosleep && !__CRT_HAVE___nanosleep && !__CRT_HAVE___libc_nanosleep */
#endif /* !__local__sleep_defined */
