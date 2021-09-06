/* HASH CRC-32:0x4a09d6ed */
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
#ifndef __local_sigtimedwait64_defined
#define __local_sigtimedwait64_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_sigtimedwait
#include <bits/os/siginfo.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_sigtimedwait32_defined
#define __local___localdep_sigtimedwait32_defined 1
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_sigtimedwait32,(struct __sigset_struct const *__restrict __set, struct __siginfo_struct *__restrict __info, struct __timespec32 const *__rel_timeout),sigtimedwait,(__set,__info,__rel_timeout))
#endif /* !__local___localdep_sigtimedwait32_defined */
__LOCAL_LIBC(sigtimedwait64) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(sigtimedwait64))(struct __sigset_struct const *__restrict __set, struct __siginfo_struct *__restrict __info, struct __timespec64 const *__rel_timeout) {
	struct __timespec32 __tmv;
	if (!__rel_timeout)
		return __localdep_sigtimedwait32(__set, __info, __NULLPTR);
	__tmv.tv_sec  = (__time32_t)__rel_timeout->tv_sec;
	__tmv.tv_nsec = __rel_timeout->tv_nsec;
	return __localdep_sigtimedwait32(__set, __info, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sigtimedwait64_defined
#define __local___localdep_sigtimedwait64_defined 1
#define __localdep_sigtimedwait64 __LIBC_LOCAL_NAME(sigtimedwait64)
#endif /* !__local___localdep_sigtimedwait64_defined */
#else /* __CRT_HAVE_sigtimedwait */
#undef __local_sigtimedwait64_defined
#endif /* !__CRT_HAVE_sigtimedwait */
#endif /* !__local_sigtimedwait64_defined */
