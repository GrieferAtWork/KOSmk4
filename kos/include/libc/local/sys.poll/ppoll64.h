/* HASH CRC-32:0x8d0c15f9 */
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
#ifndef __local_ppoll64_defined
#define __local_ppoll64_defined
#include <__crt.h>
#ifdef __CRT_HAVE_ppoll
#include <bits/os/pollfd.h>
#include <bits/os/timespec.h>
#include <bits/os/sigset.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ppoll32_defined
#define __local___localdep_ppoll32_defined
__CREDIRECT(__ATTR_INOUTS(1, 2) __ATTR_IN_OPT(3) __ATTR_IN_OPT(4),int,__NOTHROW_RPC,__localdep_ppoll32,(struct pollfd *__fds, __UINTPTR_TYPE__ __nfds, struct __timespec32 const *__timeout, struct __sigset_struct const *__ss),ppoll,(__fds,__nfds,__timeout,__ss))
#endif /* !__local___localdep_ppoll32_defined */
__LOCAL_LIBC(ppoll64) __ATTR_INOUTS(1, 2) __ATTR_IN_OPT(3) __ATTR_IN_OPT(4) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(ppoll64))(struct pollfd *__fds, __UINTPTR_TYPE__ __nfds, struct __timespec64 const *__timeout, struct __sigset_struct const *__ss) {
	struct __timespec32 __tmo32;
	if (!__timeout)
		return (__NAMESPACE_LOCAL_SYM __localdep_ppoll32)(__fds, __nfds, __NULLPTR, __ss);
	__tmo32.tv_sec  = (__time32_t)__timeout->tv_sec;
	__tmo32.tv_nsec = __timeout->tv_nsec;
	return (__NAMESPACE_LOCAL_SYM __localdep_ppoll32)(__fds, __nfds, &__tmo32, __ss);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ppoll64_defined
#define __local___localdep_ppoll64_defined
#define __localdep_ppoll64 __LIBC_LOCAL_NAME(ppoll64)
#endif /* !__local___localdep_ppoll64_defined */
#else /* __CRT_HAVE_ppoll */
#undef __local_ppoll64_defined
#endif /* !__CRT_HAVE_ppoll */
#endif /* !__local_ppoll64_defined */
