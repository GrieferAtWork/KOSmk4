/* HASH CRC-32:0x395fa8eb */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_RecvMMsg_defined
#define __local_RecvMMsg_defined
#include <__crt.h>
#include <bits/types.h>
#if (defined(__CRT_HAVE_RecvMMsg) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || defined(__CRT_HAVE_RecvMMsg64) || defined(__CRT_HAVE_recvmmsg)
#include <kos/anno.h>
#include <features.h>
#include <bits/os/mmsghdr.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_RecvMMsg32_defined) && defined(__CRT_HAVE_recvmmsg)
#define __local___localdep_RecvMMsg32_defined
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_INOUTS(2, 3) __ATTR_IN_OPT(5),__SIZE_TYPE__,__THROWING(...),__localdep_RecvMMsg32,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct __timespec32 *__tmo),recvmmsg,(__sockfd,__vmessages,__vlen,__msg_flags,__tmo))
#endif /* !__local___localdep_RecvMMsg32_defined && __CRT_HAVE_recvmmsg */
#ifndef __local___localdep_RecvMMsg64_defined
#define __local___localdep_RecvMMsg64_defined
#if defined(__CRT_HAVE_RecvMMsg) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_INOUTS(2, 3) __ATTR_IN_OPT(5),__SIZE_TYPE__,__THROWING(...),__localdep_RecvMMsg64,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct __timespec64 *__tmo),RecvMMsg,(__sockfd,__vmessages,__vlen,__msg_flags,__tmo))
#elif defined(__CRT_HAVE_RecvMMsg64)
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_INOUTS(2, 3) __ATTR_IN_OPT(5),__SIZE_TYPE__,__THROWING(...),__localdep_RecvMMsg64,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct __timespec64 *__tmo),RecvMMsg64,(__sockfd,__vmessages,__vlen,__msg_flags,__tmo))
#elif defined(__CRT_HAVE_recvmmsg)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sys.socket/RecvMMsg64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_RecvMMsg64 __LIBC_LOCAL_NAME(RecvMMsg64)
#else /* ... */
#undef __local___localdep_RecvMMsg64_defined
#endif /* !... */
#endif /* !__local___localdep_RecvMMsg64_defined */
__LOCAL_LIBC(RecvMMsg) __ATTR_FDREAD(1) __ATTR_INOUTS(2, 3) __ATTR_IN_OPT(5) __SIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(RecvMMsg))(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct timespec *__tmo) __THROWS(...) {

	struct __timespec64 __tmo64;
	if (!__tmo)
		return (__NAMESPACE_LOCAL_SYM __localdep_RecvMMsg64)(__sockfd, __vmessages, __vlen, __msg_flags, __NULLPTR);
	__tmo64.tv_sec  = (__time64_t)__tmo->tv_sec,
	__tmo64.tv_nsec = __tmo->tv_nsec;
	return (__NAMESPACE_LOCAL_SYM __localdep_RecvMMsg64)(__sockfd, __vmessages, __vlen, __msg_flags, &__tmo64);








}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_RecvMMsg_defined
#define __local___localdep_RecvMMsg_defined
#define __localdep_RecvMMsg __LIBC_LOCAL_NAME(RecvMMsg)
#endif /* !__local___localdep_RecvMMsg_defined */
#else /* (__CRT_HAVE_RecvMMsg && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || __CRT_HAVE_RecvMMsg64 || __CRT_HAVE_recvmmsg */
#undef __local_RecvMMsg_defined
#endif /* (!__CRT_HAVE_RecvMMsg || __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__) && !__CRT_HAVE_RecvMMsg64 && !__CRT_HAVE_recvmmsg */
#endif /* !__local_RecvMMsg_defined */
