/* HASH CRC-32:0xa0207487 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_RecvMMsg64_defined
#define __local_RecvMMsg64_defined
#include <__crt.h>
#ifdef __CRT_HAVE_recvmmsg
#include <kos/anno.h>
#include <features.h>
#include <bits/types.h>
#include <bits/os/mmsghdr.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_RecvMMsg32_defined
#define __local___localdep_RecvMMsg32_defined
__CREDIRECT(__ATTR_INOUTS(2, 3) __ATTR_IN_OPT(5),__SIZE_TYPE__,__THROWING,__localdep_RecvMMsg32,(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct __timespec32 *__tmo),recvmmsg,(__sockfd,__vmessages,__vlen,__msg_flags,__tmo))
#endif /* !__local___localdep_RecvMMsg32_defined */
__LOCAL_LIBC(RecvMMsg64) __ATTR_INOUTS(2, 3) __ATTR_IN_OPT(5) __SIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(RecvMMsg64))(__fd_t __sockfd, struct mmsghdr *__vmessages, __STDC_UINT_AS_SIZE_T __vlen, __STDC_INT_AS_UINT_T __msg_flags, struct __timespec64 *__tmo) __THROWS(...) {
	struct __timespec32 __tmo32;
	if (!__tmo)
		return (__NAMESPACE_LOCAL_SYM __localdep_RecvMMsg32)(__sockfd, __vmessages, __vlen, __msg_flags, __NULLPTR);
	__tmo32.tv_sec  = (__time32_t)__tmo->tv_sec,
	__tmo32.tv_nsec = __tmo->tv_nsec;
	return (__NAMESPACE_LOCAL_SYM __localdep_RecvMMsg32)(__sockfd, __vmessages, __vlen, __msg_flags, &__tmo32);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_RecvMMsg64_defined
#define __local___localdep_RecvMMsg64_defined
#define __localdep_RecvMMsg64 __LIBC_LOCAL_NAME(RecvMMsg64)
#endif /* !__local___localdep_RecvMMsg64_defined */
#else /* __CRT_HAVE_recvmmsg */
#undef __local_RecvMMsg64_defined
#endif /* !__CRT_HAVE_recvmmsg */
#endif /* !__local_RecvMMsg64_defined */
