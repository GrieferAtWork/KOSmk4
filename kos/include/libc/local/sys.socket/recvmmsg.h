/* HASH CRC-32:0x5b59335c */
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_recvmmsg_defined
#define __local_recvmmsg_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_recvmmsg64) || defined(__CRT_HAVE_recvmmsg)
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: recvmmsg32 from sys.socket */
#if !defined(__local___localdep_recvmmsg32_defined) && defined(__CRT_HAVE_recvmmsg)
#define __local___localdep_recvmmsg32_defined 1
/* Same as `recvmsg(2)', but may be used to receive many
 * messages (datagrams) with a single system call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_recvmmsg32,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct __timespec32 *__tmo),recvmmsg,(__sockfd,__vmessages,__vlen,__msg_flags,__tmo))
#endif /* !__local___localdep_recvmmsg32_defined && __CRT_HAVE_recvmmsg */
/* Dependency: recvmmsg64 from sys.socket */
#ifndef __local___localdep_recvmmsg64_defined
#define __local___localdep_recvmmsg64_defined 1
#ifdef __CRT_HAVE_recvmmsg64
/* Same as `recvmsg(2)', but may be used to receive many
 * messages (datagrams) with a single system call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_recvmmsg64,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct __timespec64 *__tmo),recvmmsg64,(__sockfd,__vmessages,__vlen,__msg_flags,__tmo))
#elif defined(__CRT_HAVE_recvmmsg) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Same as `recvmsg(2)', but may be used to receive many
 * messages (datagrams) with a single system call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_recvmmsg64,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct __timespec64 *__tmo),recvmmsg,(__sockfd,__vmessages,__vlen,__msg_flags,__tmo))
#elif defined(__CRT_HAVE_recvmmsg)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.socket/recvmmsg64.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `recvmsg(2)', but may be used to receive many
 * messages (datagrams) with a single system call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
#define __localdep_recvmmsg64 __LIBC_LOCAL_NAME(recvmmsg64)
#else /* ... */
#undef __local___localdep_recvmmsg64_defined
#endif /* !... */
#endif /* !__local___localdep_recvmmsg64_defined */
/* Same as `recvmsg(2)', but may be used to receive many
 * messages (datagrams) with a single system call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @return: * : The # of datagrams successfully received.
 * @return: -1: Error (s.a. `recvmsg(2)') */
__LOCAL_LIBC(recvmmsg) __ATTR_NONNULL((2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(recvmmsg))(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct timespec *__tmo) {

	struct __timespec64 __tmo64;
	if (!__tmo)
		return __localdep_recvmmsg64(__sockfd, __vmessages, __vlen, __msg_flags, __NULLPTR);
	__tmo32.tv_sec  = (__time64_t)__tmo->tv_sec,
	__tmo32.tv_nsec = __tmo->tv_nsec;
	return __localdep_recvmmsg64(__sockfd, __vmessages, __vlen, __msg_flags, &__tmo64);








}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_recvmmsg_defined
#define __local___localdep_recvmmsg_defined 1
#define __localdep_recvmmsg __LIBC_LOCAL_NAME(recvmmsg)
#endif /* !__local___localdep_recvmmsg_defined */
#else /* __CRT_HAVE_recvmmsg64 || __CRT_HAVE_recvmmsg */
#undef __local_recvmmsg_defined
#endif /* !__CRT_HAVE_recvmmsg64 && !__CRT_HAVE_recvmmsg */
#endif /* !__local_recvmmsg_defined */
