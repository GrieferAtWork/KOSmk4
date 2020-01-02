/* HASH CRC-32:0x5d983981 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_sigtimedwait_defined
#if defined(__CRT_HAVE_sigtimedwait) || defined(__CRT_HAVE_sigtimedwait64)
#define __local_sigtimedwait_defined 1
/* Dependency: "sigtimedwait64" from "signal" */
#ifndef ____localdep_sigtimedwait64_defined
#define ____localdep_sigtimedwait64_defined 1
#ifdef __CRT_HAVE_sigtimedwait64
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_sigtimedwait64,(struct __sigset_struct const *__restrict __set, siginfo_t *__restrict __info, struct __timespec64 const *__timeout),sigtimedwait64,(__set,__info,__timeout))
#elif defined(__CRT_HAVE_sigtimedwait) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_sigtimedwait64,(struct __sigset_struct const *__restrict __set, siginfo_t *__restrict __info, struct __timespec64 const *__timeout),sigtimedwait,(__set,__info,__timeout))
#elif defined(__CRT_HAVE_sigtimedwait)
#include <local/signal/sigtimedwait64.h>
#define __localdep_sigtimedwait64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigtimedwait64))
#else /* CUSTOM: sigtimedwait64 */
#undef ____localdep_sigtimedwait64_defined
#endif /* sigtimedwait64... */
#endif /* !____localdep_sigtimedwait64_defined */

/* Dependency: "sigtimedwait32" from "signal" */
#ifndef ____localdep_sigtimedwait32_defined
#define ____localdep_sigtimedwait32_defined 1
#ifdef __CRT_HAVE_sigtimedwait
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_sigtimedwait32,(struct __sigset_struct const *__restrict __set, siginfo_t *__restrict __info, struct __timespec32 const *__timeout),sigtimedwait,(__set,__info,__timeout))
#else /* LIBC: sigtimedwait */
#undef ____localdep_sigtimedwait32_defined
#endif /* sigtimedwait32... */
#endif /* !____localdep_sigtimedwait32_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sigtimedwait) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(sigtimedwait))(struct __sigset_struct const *__restrict __set,
                                                          siginfo_t *__restrict __info,
                                                          struct timespec const *__timeout) {
#line 344 "kos/src/libc/magic/signal.c"
#ifdef __CRT_HAVE_sigtimedwait64
	struct __timespec64 __tmv;
	if (!__timeout)
		return __localdep_sigtimedwait64(__set, __info, __NULLPTR);
	__tmv.tv_sec  = (__time64_t)__timeout->tv_sec;
	__tmv.tv_nsec = __timeout->tv_nsec;
	return __localdep_sigtimedwait64(__set, __info, __NULLPTR);
#else /* __CRT_HAVE_sigtimedwait64 */
	struct __timespec32 __tmv;
	if (!__timeout)
		return __localdep_sigtimedwait32(__set, __info, __NULLPTR);
	__tmv.tv_sec  = (__time32_t)__timeout->tv_sec;
	__tmv.tv_nsec = __timeout->tv_nsec;
	return __localdep_sigtimedwait32(__set, __info, __NULLPTR);
#endif /* !__CRT_HAVE_sigtimedwait64 */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_sigtimedwait || __CRT_HAVE_sigtimedwait64 */
#endif /* !__local_sigtimedwait_defined */
