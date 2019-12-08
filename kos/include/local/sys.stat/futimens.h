/* HASH CRC-32:0xd051af37 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_futimens_defined
#if defined(__CRT_HAVE_futimens) || defined(__CRT_HAVE_futimens64)
#define __local_futimens_defined 1
/* Dependency: "futimens64" from "sys.stat" */
#ifndef ____localdep_futimens64_defined
#define ____localdep_futimens64_defined 1
#ifdef __CRT_HAVE_futimens64
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_futimens64,(__fd_t __fd, struct __timespec64 const __times[2 /*or:3*/]),futimens64,(__fd,__times))
#elif defined(__CRT_HAVE_futimens) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_futimens64,(__fd_t __fd, struct __timespec64 const __times[2 /*or:3*/]),futimens,(__fd,__times))
#elif defined(__CRT_HAVE_futimens)
#include <local/sys.stat/futimens64.h>
#define __localdep_futimens64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futimens64))
#else /* CUSTOM: futimens64 */
#undef ____localdep_futimens64_defined
#endif /* futimens64... */
#endif /* !____localdep_futimens64_defined */

/* Dependency: "futimens32" from "sys.stat" */
#ifndef ____localdep_futimens32_defined
#define ____localdep_futimens32_defined 1
#ifdef __CRT_HAVE_futimens
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_futimens32,(__fd_t __fd, struct timespec const __times[2 /*or:3*/]),futimens,(__fd,__times))
#else /* LIBC: futimens */
#undef ____localdep_futimens32_defined
#endif /* futimens32... */
#endif /* !____localdep_futimens32_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(futimens) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(futimens))(__fd_t __fd,
                                                      struct timespec const __times[2 /*or:3*/]) {
#line 642 "kos/src/libc/magic/sys.stat.c"
#ifdef __CRT_HAVE_utimensat64
	struct __timespec64 __tms[2];
	if (!__times)
		return __localdep_futimens64(__fd, __NULLPTR);
	__tms[0].tv_sec  = (__time64_t)__times[0].tv_sec;
	__tms[0].tv_nsec = __times[0].tv_nsec;
	__tms[1].tv_sec  = (__time64_t)__times[1].tv_sec;
	__tms[1].tv_nsec = __times[1].tv_nsec;
	return __localdep_futimens64(__fd, __tms);
#else /* __CRT_HAVE_utimensat64 */
	struct __timespec32 __tms[2];
	if (!__times)
		return __localdep_futimens32(__fd, __NULLPTR);
	__tms[0].tv_sec  = (__time32_t)__times[0].tv_sec;
	__tms[0].tv_nsec = __times[0].tv_nsec;
	__tms[1].tv_sec  = (__time32_t)__times[1].tv_sec;
	__tms[1].tv_nsec = __times[1].tv_nsec;
	return __localdep_futimens32(__fd, __tms);
#endif /* !__CRT_HAVE_utimensat64 */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_futimens || __CRT_HAVE_futimens64 */
#endif /* !__local_futimens_defined */
