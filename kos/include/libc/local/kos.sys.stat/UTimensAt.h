/* HASH CRC-32:0x6ce75f9e */
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
#ifndef __local_UTimensAt_defined
#define __local_UTimensAt_defined 1
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_UTimensAt64) || defined(__CRT_HAVE_UTimensAt)
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_UTimensAt32_defined) && defined(__CRT_HAVE_UTimensAt)
#define __local___localdep_UTimensAt32_defined 1
__CREDIRECT_VOID(__ATTR_NONNULL((2)),__THROWING,__localdep_UTimensAt32,(__fd_t __dirfd, char const *__filename, struct timespec const __times[2 /*or:3*/], __atflag_t __flags),UTimensAt,(__dirfd,__filename,__times,__flags))
#endif /* !__local___localdep_UTimensAt32_defined && __CRT_HAVE_UTimensAt */
#ifndef __local___localdep_UTimensAt64_defined
#define __local___localdep_UTimensAt64_defined 1
#ifdef __CRT_HAVE_UTimensAt64
__CREDIRECT_VOID(__ATTR_NONNULL((2)),__THROWING,__localdep_UTimensAt64,(__fd_t __dirfd, char const *__filename, struct __timespec64 const __times[2 /*or:3*/], __atflag_t __flags),UTimensAt64,(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE_UTimensAt) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT_VOID(__ATTR_NONNULL((2)),__THROWING,__localdep_UTimensAt64,(__fd_t __dirfd, char const *__filename, struct __timespec64 const __times[2 /*or:3*/], __atflag_t __flags),UTimensAt,(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE_UTimensAt)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sys.stat/UTimensAt64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_UTimensAt64 __LIBC_LOCAL_NAME(UTimensAt64)
#else /* ... */
#undef __local___localdep_UTimensAt64_defined
#endif /* !... */
#endif /* !__local___localdep_UTimensAt64_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/fcntl.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(UTimensAt) __ATTR_NONNULL((2)) void
(__LIBCCALL __LIBC_LOCAL_NAME(UTimensAt))(__fd_t __dirfd, char const *__filename, struct timespec const __times[2 /*or:3*/], __atflag_t __flags) __THROWS(...) {

#ifdef __AT_CHANGE_CTIME
	struct __timespec64 __tms[3];
	if (!__times) {
		(__NAMESPACE_LOCAL_SYM __localdep_UTimensAt64)(__dirfd, __filename, __NULLPTR, __flags);
	} else {
		__tms[0].tv_sec  = (__time64_t)__times[0].tv_sec;
		__tms[0].tv_nsec = __times[0].tv_nsec;
		__tms[1].tv_sec  = (__time64_t)__times[1].tv_sec;
		__tms[1].tv_nsec = __times[1].tv_nsec;
		if (__flags & __AT_CHANGE_CTIME) {
			__tms[2].tv_sec  = (__time64_t)__times[2].tv_sec;
			__tms[2].tv_nsec = __times[2].tv_nsec;
		}
		(__NAMESPACE_LOCAL_SYM __localdep_UTimensAt64)(__dirfd, __filename, __tms, __flags);
	}
#else /* __AT_CHANGE_CTIME */
	struct __timespec64 __tms[2];
	if (!__times) {
		(__NAMESPACE_LOCAL_SYM __localdep_UTimensAt64)(__dirfd, __filename, __NULLPTR, __flags);
	} else {
		__tms[0].tv_sec  = (__time64_t)__times[0].tv_sec;
		__tms[0].tv_nsec = __times[0].tv_nsec;
		__tms[1].tv_sec  = (__time64_t)__times[1].tv_sec;
		__tms[1].tv_nsec = __times[1].tv_nsec;
		(__NAMESPACE_LOCAL_SYM __localdep_UTimensAt64)(__dirfd, __filename, __tms, __flags);
	}
#endif /* !__AT_CHANGE_CTIME */





























}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_UTimensAt_defined
#define __local___localdep_UTimensAt_defined 1
#define __localdep_UTimensAt __LIBC_LOCAL_NAME(UTimensAt)
#endif /* !__local___localdep_UTimensAt_defined */
#else /* __CRT_HAVE_UTimensAt64 || __CRT_HAVE_UTimensAt */
#undef __local_UTimensAt_defined
#endif /* !__CRT_HAVE_UTimensAt64 && !__CRT_HAVE_UTimensAt */
#endif /* !__local_UTimensAt_defined */
