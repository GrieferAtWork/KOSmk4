/* HASH CRC-32:0x299d9487 */
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
#ifndef __local_pselect_defined
#if (defined(__CRT_HAVE_pselect) || defined(__CRT_HAVE_pselect64))
#define __local_pselect_defined 1
/* Dependency: "pselect64" from "sys.select" */
#ifndef ____localdep_pselect64_defined
#define ____localdep_pselect64_defined 1
#if defined(__CRT_HAVE_pselect64)
__CREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_pselect64,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct __timespec64 const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask),pselect64,(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask))
#elif defined(__CRT_HAVE_pselect) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_pselect64,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct __timespec64 const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask),pselect,(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask))
#elif defined(__CRT_HAVE_pselect)
#include <local/sys.select/pselect64.h>
#define __localdep_pselect64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pselect64))
#else /* CUSTOM: pselect64 */
#undef ____localdep_pselect64_defined
#endif /* pselect64... */
#endif /* !____localdep_pselect64_defined */

/* Dependency: "pselect32" from "sys.select" */
#ifndef ____localdep_pselect32_defined
#define ____localdep_pselect32_defined 1
#if defined(__CRT_HAVE_pselect)
__CREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_pselect32,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct __timespec32 const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask),pselect,(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask))
#else /* LIBC: pselect */
#undef ____localdep_pselect32_defined
#endif /* pselect32... */
#endif /* !____localdep_pselect32_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(pselect) __STDC_INT_AS_SSIZE_T
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(pselect))(__STDC_INT_AS_SIZE_T __nfds,
                                                     fd_set *__restrict __readfds,
                                                     fd_set *__restrict __writefds,
                                                     fd_set *__restrict __exceptfds,
                                                     struct __TM_TYPE(timespec) const *__restrict __timeout,
                                                     struct __sigset_struct const *__restrict __sigmask) {
#line 152 "kos/src/libc/magic/sys.select.c"
#ifdef __CRT_HAVE_pselect64
	struct __timespec64 __tmv;
	if (!__timeout)
		return __localdep_pselect64(__nfds, __readfds, __writefds, __exceptfds, __NULLPTR, __sigmask);
	__tms.tv_sec  = (__time64_t)__timeout->tv_sec;
	__tms.tv_nsec = __timeout->tv_nsec;
	return __localdep_pselect64(__nfds, __readfds, __writefds, __exceptfds, &__tms, __sigmask);
#else /* __CRT_HAVE_pselect64 */
	struct __timespec32 __tms;
	if (!__timeout)
		return __localdep_pselect32(__nfds, __readfds, __writefds, __exceptfds, __NULLPTR, __sigmask);
	__tms.tv_sec  = (__time32_t)__timeout->tv_sec;
	__tms.tv_nsec = __timeout->tv_nsec;
	return __localdep_pselect32(__nfds, __readfds, __writefds, __exceptfds, &__tms, __sigmask);
#endif /* !__CRT_HAVE_pselect64 */
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_pselect) || defined(__CRT_HAVE_pselect64)) */
#endif /* !__local_pselect_defined */
