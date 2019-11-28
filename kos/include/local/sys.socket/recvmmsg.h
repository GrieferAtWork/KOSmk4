/* HASH CRC-32:0xf8eba67e */
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
#ifndef __local_recvmmsg_defined
#if defined(__CRT_HAVE_recvmmsg) || defined(__CRT_HAVE_recvmmsg64)
#define __local_recvmmsg_defined 1
/* Dependency: "recvmmsg64" from "sys.socket" */
#ifndef ____localdep_recvmmsg64_defined
#define ____localdep_recvmmsg64_defined 1
#ifdef __CRT_HAVE_recvmmsg64
/* Receive up to VLEN messages as described by VMESSAGES from socket FD.
 * Returns the number of messages received or -1 for errors. */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_recvmmsg64,(__fd_t __sockfd, struct mmsghdr *__vmessages, unsigned int __vlen, int __flags, struct __timespec64 *__tmo),recvmmsg64,(__sockfd,__vmessages,__vlen,__flags,__tmo))
#elif defined(__CRT_HAVE_recvmmsg) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Receive up to VLEN messages as described by VMESSAGES from socket FD.
 * Returns the number of messages received or -1 for errors. */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_recvmmsg64,(__fd_t __sockfd, struct mmsghdr *__vmessages, unsigned int __vlen, int __flags, struct __timespec64 *__tmo),recvmmsg,(__sockfd,__vmessages,__vlen,__flags,__tmo))
#elif defined(__CRT_HAVE_recvmmsg)
#include <local/sys.socket/recvmmsg64.h>
/* Receive up to VLEN messages as described by VMESSAGES from socket FD.
 * Returns the number of messages received or -1 for errors. */
#define __localdep_recvmmsg64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(recvmmsg64))
#else /* CUSTOM: recvmmsg64 */
#undef ____localdep_recvmmsg64_defined
#endif /* recvmmsg64... */
#endif /* !____localdep_recvmmsg64_defined */

/* Dependency: "recvmmsg32" from "sys.socket" */
#ifndef ____localdep_recvmmsg32_defined
#define ____localdep_recvmmsg32_defined 1
#ifdef __CRT_HAVE_recvmmsg
/* Receive up to VLEN messages as described by VMESSAGES from socket FD.
 * Returns the number of messages received or -1 for errors. */
__CREDIRECT_VOID(__ATTR_NONNULL((2)),__NOTHROW_RPC,__localdep_recvmmsg32,(__fd_t __sockfd, struct mmsghdr *__vmessages, unsigned int __vlen, int __flags, struct __timespec32 *__tmo),recvmmsg,(__sockfd,__vmessages,__vlen,__flags,__tmo))
#else /* LIBC: recvmmsg */
#undef ____localdep_recvmmsg32_defined
#endif /* recvmmsg32... */
#endif /* !____localdep_recvmmsg32_defined */

__NAMESPACE_LOCAL_BEGIN
/* Receive up to VLEN messages as described by VMESSAGES from socket FD.
 * Returns the number of messages received or -1 for errors. */
__LOCAL_LIBC(recvmmsg) __ATTR_NONNULL((2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(recvmmsg))(__fd_t __sockfd,
                                                      struct mmsghdr *__vmessages,
                                                      unsigned int __vlen,
                                                      int __flags,
                                                      struct __TM_TYPE(timespec) *__tmo) {
#line 246 "kos/src/libc/magic/sys.socket.c"
#ifdef __CRT_HAVE_recvmmsg64
	struct __timespec64 __tmo64;
	if (!__tmo)
		return __localdep_recvmmsg64(__sockfd,__vmessages,__vlen,__flags,__NULLPTR);
	__tmo32.tv_sec  = (__time64_t)__tmo->tv_sec,
	__tmo32.tv_nsec = __tmo->tv_nsec;
	return __localdep_recvmmsg64(__sockfd,__vmessages,__vlen,__flags,&__tmo64);
#else
	struct __timespec32 __tmo32;
	if (!__tmo)
		return __localdep_recvmmsg32(__sockfd,__vmessages,__vlen,__flags,__NULLPTR);
	__tmo32.tv_sec  = (__time32_t)__tmo->tv_sec,
	__tmo32.tv_nsec = __tmo->tv_nsec;
	return __localdep_recvmmsg32(__sockfd,__vmessages,__vlen,__flags,&__tmo32);
#endif
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_recvmmsg || __CRT_HAVE_recvmmsg64 */
#endif /* !__local_recvmmsg_defined */
