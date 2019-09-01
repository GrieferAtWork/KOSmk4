/* HASH 0x2b7d299e */
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
#ifndef __local_futimens64_defined
#if defined(__CRT_HAVE_futimens)
#define __local_futimens64_defined 1
/* Dependency: "futimens32" from "sys.stat" */
#ifndef ____localdep_futimens32_defined
#define ____localdep_futimens32_defined 1
#if defined(__CRT_HAVE_futimens)
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_futimens32,(__fd_t __fd, struct __TM_TYPE(timespec) const __times[2/*or:3*/]),futimens,(__fd,__times))
#else /* LIBC: futimens */
#undef ____localdep_futimens32_defined
#endif /* futimens32... */
#endif /* !____localdep_futimens32_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(futimens64) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(futimens64))(__fd_t __fd,
                                                        struct __timespec64 const __times[2/*or:3*/]) {
#line 668 "kos/src/libc/magic/sys.stat.c"
	struct __timespec32 __tms[2];
	if (!__times)
		return __localdep_futimens32(__fd, __NULLPTR);
	__tms[0].tv_sec  = (__time32_t)__times[0].tv_sec;
	__tms[0].tv_nsec = __times[0].tv_nsec;
	__tms[1].tv_sec  = (__time32_t)__times[1].tv_sec;
	__tms[1].tv_nsec = __times[1].tv_nsec;
	return __localdep_futimens32(__fd, __tms);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_futimens) */
#endif /* !__local_futimens64_defined */
