/* HASH CRC-32:0xd8109abd */
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
#ifndef __local_FUtimens_defined
#define __local_FUtimens_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_FUtimens64) || defined(__CRT_HAVE_FUtimens)
#include <kos/anno.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_FUtimens32_defined) && defined(__CRT_HAVE_FUtimens)
#define __local___localdep_FUtimens32_defined
__CREDIRECT_VOID(,__THROWING,__localdep_FUtimens32,(__fd_t __fd, struct timespec const __times[2 /*or:3*/]),FUtimens,(__fd,__times))
#endif /* !__local___localdep_FUtimens32_defined && __CRT_HAVE_FUtimens */
#ifndef __local___localdep_FUtimens64_defined
#define __local___localdep_FUtimens64_defined
#if defined(__CRT_HAVE_FUtimens) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT_VOID(__ATTR_IN_OPT(2),__THROWING,__localdep_FUtimens64,(__fd_t __fd, struct __timespec64 const __times[2 /*or:3*/]),FUtimens,(__fd,__times))
#elif defined(__CRT_HAVE_FUtimens64)
__CREDIRECT_VOID(__ATTR_IN_OPT(2),__THROWING,__localdep_FUtimens64,(__fd_t __fd, struct __timespec64 const __times[2 /*or:3*/]),FUtimens64,(__fd,__times))
#elif defined(__CRT_HAVE_FUtimens)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sys.stat/FUtimens64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_FUtimens64 __LIBC_LOCAL_NAME(FUtimens64)
#else /* ... */
#undef __local___localdep_FUtimens64_defined
#endif /* !... */
#endif /* !__local___localdep_FUtimens64_defined */
__LOCAL_LIBC(FUtimens) __ATTR_IN_OPT(2) void
(__LIBCCALL __LIBC_LOCAL_NAME(FUtimens))(__fd_t __fd, struct timespec const __times[2 /*or:3*/]) __THROWS(...) {
#if defined(__CRT_HAVE_UTimensAt64) || defined(__CRT_HAVE_UTimensAt)
	struct __timespec64 __tms[2];
	if (!__times) {
		(__NAMESPACE_LOCAL_SYM __localdep_FUtimens64)(__fd, __NULLPTR);
	} else {
		__tms[0].tv_sec  = (__time64_t)__times[0].tv_sec;
		__tms[0].tv_nsec = __times[0].tv_nsec;
		__tms[1].tv_sec  = (__time64_t)__times[1].tv_sec;
		__tms[1].tv_nsec = __times[1].tv_nsec;
		(__NAMESPACE_LOCAL_SYM __localdep_FUtimens64)(__fd, __tms);
	}
#else /* __CRT_HAVE_UTimensAt64 || __CRT_HAVE_UTimensAt */
	struct __timespec32 __tms[2];
	if (!__times) {
		(__NAMESPACE_LOCAL_SYM __localdep_FUtimens32)(__fd, __NULLPTR);
	} else {
		__tms[0].tv_sec  = (__time32_t)__times[0].tv_sec;
		__tms[0].tv_nsec = __times[0].tv_nsec;
		__tms[1].tv_sec  = (__time32_t)__times[1].tv_sec;
		__tms[1].tv_nsec = __times[1].tv_nsec;
		(__NAMESPACE_LOCAL_SYM __localdep_FUtimens32)(__fd, __tms);
	}
#endif /* !__CRT_HAVE_UTimensAt64 && !__CRT_HAVE_UTimensAt */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_FUtimens_defined
#define __local___localdep_FUtimens_defined
#define __localdep_FUtimens __LIBC_LOCAL_NAME(FUtimens)
#endif /* !__local___localdep_FUtimens_defined */
#else /* __CRT_HAVE_FUtimens64 || __CRT_HAVE_FUtimens */
#undef __local_FUtimens_defined
#endif /* !__CRT_HAVE_FUtimens64 && !__CRT_HAVE_FUtimens */
#endif /* !__local_FUtimens_defined */
