/* HASH CRC-32:0x99a4fcea */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_opensock_defined
#define __local_opensock_defined
#include <__crt.h>
#include <asm/os/socket.h>
#if (defined(__CRT_HAVE_socket) || defined(__CRT_HAVE___socket)) && defined(__SOCK_DGRAM) && (defined(__AF_LOCAL) || defined(__AF_INET) || defined(__AF_INET6))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_socket_defined
#define __local___localdep_socket_defined
#ifdef __CRT_HAVE_socket
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,__localdep_socket,(__STDC_INT_AS_UINT_T __domain, __STDC_INT_AS_UINT_T __type, __STDC_INT_AS_UINT_T __protocol),socket,(__domain,__type,__protocol))
#elif defined(__CRT_HAVE___socket)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,__localdep_socket,(__STDC_INT_AS_UINT_T __domain, __STDC_INT_AS_UINT_T __type, __STDC_INT_AS_UINT_T __protocol),__socket,(__domain,__type,__protocol))
#else /* ... */
#undef __local___localdep_socket_defined
#endif /* !... */
#endif /* !__local___localdep_socket_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(opensock) __ATTR_WUNUSED __fd_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(opensock))(void) {
	__SIZE_TYPE__ __i;
	static unsigned int const __domains[] = {
#ifdef __AF_LOCAL
		__AF_LOCAL,
#endif /* __AF_LOCAL */
#ifdef __AF_INET
		__AF_INET,
#endif /* __AF_INET */
#ifdef __AF_INET6
		__AF_INET6,
#endif /* __AF_INET6 */
	};
	for (__i = 0; __i < __COMPILER_LENOF(__domains); ++__i) {
		__fd_t __result;
#ifdef __SOCK_CLOEXEC
		__result = (__NAMESPACE_LOCAL_SYM __localdep_socket)(__domains[__i], __SOCK_DGRAM | __SOCK_CLOEXEC, 0);
#else /* __SOCK_CLOEXEC */
		__result = (__NAMESPACE_LOCAL_SYM __localdep_socket)(__domains[__i], __SOCK_DGRAM, 0);
#endif /* !__SOCK_CLOEXEC */
		if __likely(__result >= 0)
			return __result;
	}
#ifdef __ENOENT
	return __libc_seterrno(__ENOENT);
#else /* __ENOENT */
	return __libc_seterrno(1);
#endif /* !__ENOENT */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_opensock_defined
#define __local___localdep_opensock_defined
#define __localdep_opensock __LIBC_LOCAL_NAME(opensock)
#endif /* !__local___localdep_opensock_defined */
#else /* (__CRT_HAVE_socket || __CRT_HAVE___socket) && __SOCK_DGRAM && (__AF_LOCAL || __AF_INET || __AF_INET6) */
#undef __local_opensock_defined
#endif /* (!__CRT_HAVE_socket && !__CRT_HAVE___socket) || !__SOCK_DGRAM || (!__AF_LOCAL && !__AF_INET && !__AF_INET6) */
#endif /* !__local_opensock_defined */
