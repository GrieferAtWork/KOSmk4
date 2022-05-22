/* HASH CRC-32:0xe7471405 */
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
#ifndef __local_utimensat64_defined
#define __local_utimensat64_defined
#include <__crt.h>
#ifdef __CRT_HAVE_utimensat
#include <bits/os/timespec.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_utimensat32_defined
#define __local___localdep_utimensat32_defined
__CREDIRECT(__ATTR_IN(2) __ATTR_IN_OPT(3),int,__NOTHROW_RPC,__localdep_utimensat32,(__fd_t __dirfd, char const *__filename, struct timespec const __times[2 /*or:3*/], __atflag_t __flags),utimensat,(__dirfd,__filename,__times,__flags))
#endif /* !__local___localdep_utimensat32_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/fcntl.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(utimensat64) __ATTR_IN(2) __ATTR_IN_OPT(3) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(utimensat64))(__fd_t __dirfd, char const *__filename, struct __timespec64 const __times[2 /*or:3*/], __atflag_t __flags) {
#ifdef __AT_CHANGE_BTIME
	struct __timespec32 __tms[3];
	if (!__times)
		return (__NAMESPACE_LOCAL_SYM __localdep_utimensat32)(__dirfd, __filename, __NULLPTR, __flags);
	__tms[0].tv_sec  = (__time32_t)__times[0].tv_sec;
	__tms[0].tv_nsec = __times[0].tv_nsec;
	__tms[1].tv_sec  = (__time32_t)__times[1].tv_sec;
	__tms[1].tv_nsec = __times[1].tv_nsec;
	if (__flags & __AT_CHANGE_BTIME) {
		__tms[2].tv_sec  = (__time32_t)__times[2].tv_sec;
		__tms[2].tv_nsec = __times[2].tv_nsec;
	}
	return (__NAMESPACE_LOCAL_SYM __localdep_utimensat32)(__dirfd, __filename, __tms, __flags);
#else /* __AT_CHANGE_BTIME */
	struct __timespec32 __tms[2];
	if (!__times)
		return (__NAMESPACE_LOCAL_SYM __localdep_utimensat32)(__dirfd, __filename, __NULLPTR, __flags);
	__tms[0].tv_sec  = (__time32_t)__times[0].tv_sec;
	__tms[0].tv_nsec = __times[0].tv_nsec;
	__tms[1].tv_sec  = (__time32_t)__times[1].tv_sec;
	__tms[1].tv_nsec = __times[1].tv_nsec;
	return (__NAMESPACE_LOCAL_SYM __localdep_utimensat32)(__dirfd, __filename, __tms, __flags);
#endif /* !__AT_CHANGE_BTIME */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_utimensat64_defined
#define __local___localdep_utimensat64_defined
#define __localdep_utimensat64 __LIBC_LOCAL_NAME(utimensat64)
#endif /* !__local___localdep_utimensat64_defined */
#else /* __CRT_HAVE_utimensat */
#undef __local_utimensat64_defined
#endif /* !__CRT_HAVE_utimensat */
#endif /* !__local_utimensat64_defined */
