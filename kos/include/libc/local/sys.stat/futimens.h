/* HASH CRC-32:0x753b7fb0 */
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
#ifndef __local_futimens_defined
#define __local_futimens_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_futimens64) || defined(__CRT_HAVE_futimens)
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_futimens32_defined) && defined(__CRT_HAVE_futimens)
#define __local___localdep_futimens32_defined
__CREDIRECT(__ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_RPC,__localdep_futimens32,(__fd_t __fd, struct timespec const __times[2 /*or:3*/]),futimens,(__fd,__times))
#endif /* !__local___localdep_futimens32_defined && __CRT_HAVE_futimens */
#ifndef __local___localdep_futimens64_defined
#define __local___localdep_futimens64_defined
#if defined(__CRT_HAVE_futimens) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_RPC,__localdep_futimens64,(__fd_t __fd, struct __timespec64 const __times[2 /*or:3*/]),futimens,(__fd,__times))
#elif defined(__CRT_HAVE_futimens64)
__CREDIRECT(__ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_RPC,__localdep_futimens64,(__fd_t __fd, struct __timespec64 const __times[2 /*or:3*/]),futimens64,(__fd,__times))
#elif defined(__CRT_HAVE_futimens)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.stat/futimens64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_futimens64 __LIBC_LOCAL_NAME(futimens64)
#else /* ... */
#undef __local___localdep_futimens64_defined
#endif /* !... */
#endif /* !__local___localdep_futimens64_defined */
__LOCAL_LIBC(futimens) __ATTR_ACCESS_RO_OPT(2) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(futimens))(__fd_t __fd, struct timespec const __times[2 /*or:3*/]) {

	struct __timespec64 __tms[2];
	if (!__times)
		return (__NAMESPACE_LOCAL_SYM __localdep_futimens64)(__fd, __NULLPTR);
	__tms[0].tv_sec  = (__time64_t)__times[0].tv_sec;
	__tms[0].tv_nsec = __times[0].tv_nsec;
	__tms[1].tv_sec  = (__time64_t)__times[1].tv_sec;
	__tms[1].tv_nsec = __times[1].tv_nsec;
	return (__NAMESPACE_LOCAL_SYM __localdep_futimens64)(__fd, __tms);










}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_futimens_defined
#define __local___localdep_futimens_defined
#define __localdep_futimens __LIBC_LOCAL_NAME(futimens)
#endif /* !__local___localdep_futimens_defined */
#else /* __CRT_HAVE_futimens64 || __CRT_HAVE_futimens */
#undef __local_futimens_defined
#endif /* !__CRT_HAVE_futimens64 && !__CRT_HAVE_futimens */
#endif /* !__local_futimens_defined */
