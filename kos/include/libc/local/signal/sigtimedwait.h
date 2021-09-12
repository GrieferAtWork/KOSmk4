/* HASH CRC-32:0xffe1fab7 */
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
#ifndef __local_sigtimedwait_defined
#define __local_sigtimedwait_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_sigtimedwait64) || defined(__CRT_HAVE_sigtimedwait)
#include <bits/os/siginfo.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_sigtimedwait32_defined) && defined(__CRT_HAVE_sigtimedwait)
#define __local___localdep_sigtimedwait32_defined 1
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_sigtimedwait32,(struct __sigset_struct const *__restrict __set, struct __siginfo_struct *__restrict __info, struct __timespec32 const *__rel_timeout),sigtimedwait,(__set,__info,__rel_timeout))
#endif /* !__local___localdep_sigtimedwait32_defined && __CRT_HAVE_sigtimedwait */
#ifndef __local___localdep_sigtimedwait64_defined
#define __local___localdep_sigtimedwait64_defined 1
#ifdef __CRT_HAVE_sigtimedwait64
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_sigtimedwait64,(struct __sigset_struct const *__restrict __set, struct __siginfo_struct *__restrict __info, struct __timespec64 const *__rel_timeout),sigtimedwait64,(__set,__info,__rel_timeout))
#elif defined(__CRT_HAVE_sigtimedwait) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_sigtimedwait64,(struct __sigset_struct const *__restrict __set, struct __siginfo_struct *__restrict __info, struct __timespec64 const *__rel_timeout),sigtimedwait,(__set,__info,__rel_timeout))
#elif defined(__CRT_HAVE_sigtimedwait)
__NAMESPACE_LOCAL_END
#include <libc/local/signal/sigtimedwait64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sigtimedwait64 __LIBC_LOCAL_NAME(sigtimedwait64)
#else /* ... */
#undef __local___localdep_sigtimedwait64_defined
#endif /* !... */
#endif /* !__local___localdep_sigtimedwait64_defined */
__LOCAL_LIBC(sigtimedwait) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(sigtimedwait))(struct __sigset_struct const *__restrict __set, struct __siginfo_struct *__restrict __info, struct timespec const *__rel_timeout) {

	struct __timespec64 __tmv;
	if (!__rel_timeout)
		return __NAMESPACE_LOCAL_SYM __localdep_sigtimedwait64(__set, __info, __NULLPTR);
	__tmv.tv_sec  = (__time64_t)__rel_timeout->tv_sec;
	__tmv.tv_nsec = __rel_timeout->tv_nsec;
	return __NAMESPACE_LOCAL_SYM __localdep_sigtimedwait64(__set, __info, __NULLPTR);








}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sigtimedwait_defined
#define __local___localdep_sigtimedwait_defined 1
#define __localdep_sigtimedwait __LIBC_LOCAL_NAME(sigtimedwait)
#endif /* !__local___localdep_sigtimedwait_defined */
#else /* __CRT_HAVE_sigtimedwait64 || __CRT_HAVE_sigtimedwait */
#undef __local_sigtimedwait_defined
#endif /* !__CRT_HAVE_sigtimedwait64 && !__CRT_HAVE_sigtimedwait */
#endif /* !__local_sigtimedwait_defined */
