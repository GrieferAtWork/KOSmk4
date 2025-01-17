/* HASH CRC-32:0x8c3e5791 */
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
#ifndef __local_pthread_timedjoin64_np_defined
#define __local_pthread_timedjoin64_np_defined
#include <__crt.h>
#ifdef __CRT_HAVE_pthread_timedjoin_np
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_crt_pthread_timedjoin32_np_defined
#define __local___localdep_crt_pthread_timedjoin32_np_defined
__CREDIRECT(__ATTR_IN_OPT(3) __ATTR_OUT_OPT(2),__errno_t,__NOTHROW_RPC,__localdep_crt_pthread_timedjoin32_np,(__pthread_t __self, void **__thread_return, struct __timespec32 const *__abstime),pthread_timedjoin_np,(__self,__thread_return,__abstime))
#endif /* !__local___localdep_crt_pthread_timedjoin32_np_defined */
__LOCAL_LIBC(pthread_timedjoin64_np) __ATTR_IN_OPT(3) __ATTR_OUT_OPT(2) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(pthread_timedjoin64_np))(__pthread_t __self, void **__thread_return, struct __timespec64 const *__abstime) {
	struct __timespec32 __abstime32;
	if (!__abstime)
		return (__NAMESPACE_LOCAL_SYM __localdep_crt_pthread_timedjoin32_np)(__self, __thread_return, __NULLPTR);
	__abstime32.tv_sec  = (__time32_t)__abstime->tv_sec;
	__abstime32.tv_nsec = __abstime->tv_nsec;
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_pthread_timedjoin32_np)(__self, __thread_return, &__abstime32);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_timedjoin64_np_defined
#define __local___localdep_pthread_timedjoin64_np_defined
#define __localdep_pthread_timedjoin64_np __LIBC_LOCAL_NAME(pthread_timedjoin64_np)
#endif /* !__local___localdep_pthread_timedjoin64_np_defined */
#else /* __CRT_HAVE_pthread_timedjoin_np */
#undef __local_pthread_timedjoin64_np_defined
#endif /* !__CRT_HAVE_pthread_timedjoin_np */
#endif /* !__local_pthread_timedjoin64_np_defined */
