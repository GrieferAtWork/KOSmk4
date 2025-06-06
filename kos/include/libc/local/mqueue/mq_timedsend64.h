/* HASH CRC-32:0xa617997c */
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
#ifndef __local_mq_timedsend64_defined
#define __local_mq_timedsend64_defined
#include <__crt.h>
#ifdef __CRT_HAVE_mq_timedsend
#include <bits/os/timespec.h>
#include <bits/os/mqueue.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mq_timedsend32_defined
#define __local___localdep_mq_timedsend32_defined
__CREDIRECT(__ATTR_IN(5) __ATTR_OUTS(2, 3),int,__NOTHROW_RPC,__localdep_mq_timedsend32,(__mqd_t __mqdes, char const *__msg_ptr, __SIZE_TYPE__ __msg_len, unsigned int __msg_prio, struct __timespec32 const *__abs_timeout),mq_timedsend,(__mqdes,__msg_ptr,__msg_len,__msg_prio,__abs_timeout))
#endif /* !__local___localdep_mq_timedsend32_defined */
__LOCAL_LIBC(mq_timedsend64) __ATTR_IN(5) __ATTR_INS(2, 3) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(mq_timedsend64))(__mqd_t __mqdes, char const *__msg_ptr, __SIZE_TYPE__ __msg_len, unsigned int __msg_prio, struct __timespec64 const *__abs_timeout) {
	struct __timespec32 __abs_timeout32;
	__abs_timeout32.tv_sec  = (__time32_t)__abs_timeout->tv_sec;
	__abs_timeout32.tv_nsec = __abs_timeout->tv_nsec;
	return (__NAMESPACE_LOCAL_SYM __localdep_mq_timedsend32)(__mqdes, __msg_ptr, __msg_len, __msg_prio, &__abs_timeout32);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mq_timedsend64_defined
#define __local___localdep_mq_timedsend64_defined
#define __localdep_mq_timedsend64 __LIBC_LOCAL_NAME(mq_timedsend64)
#endif /* !__local___localdep_mq_timedsend64_defined */
#else /* __CRT_HAVE_mq_timedsend */
#undef __local_mq_timedsend64_defined
#endif /* !__CRT_HAVE_mq_timedsend */
#endif /* !__local_mq_timedsend64_defined */
