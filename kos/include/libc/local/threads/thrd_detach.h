/* HASH CRC-32:0xae1278f4 */
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
#ifndef __local_thrd_detach_defined
#define __local_thrd_detach_defined
#include <__crt.h>
#if defined(__CRT_HAVE_pthread_detach) || defined(__CRT_HAVE_cthread_detach)
#include <bits/crt/threads.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pthread_detach_defined
#define __local___localdep_pthread_detach_defined
#ifdef __CRT_HAVE_pthread_detach
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__errno_t,__NOTHROW_NCX,__localdep_pthread_detach,(__pthread_t __self),pthread_detach,(__self))
#elif defined(__CRT_HAVE_cthread_detach)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__errno_t,__NOTHROW_NCX,__localdep_pthread_detach,(__pthread_t __self),cthread_detach,(__self))
#else /* ... */
#undef __local___localdep_pthread_detach_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_detach_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/threads.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(thrd_detach) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(thrd_detach))(__thrd_t __thr) {
	__errno_t __error;
	__error = (__NAMESPACE_LOCAL_SYM __localdep_pthread_detach)((__pthread_t)__thr);
	if __likely(!__error)
		return __thrd_success;
	return __thrd_error;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_thrd_detach_defined
#define __local___localdep_thrd_detach_defined
#define __localdep_thrd_detach __LIBC_LOCAL_NAME(thrd_detach)
#endif /* !__local___localdep_thrd_detach_defined */
#else /* __CRT_HAVE_pthread_detach || __CRT_HAVE_cthread_detach */
#undef __local_thrd_detach_defined
#endif /* !__CRT_HAVE_pthread_detach && !__CRT_HAVE_cthread_detach */
#endif /* !__local_thrd_detach_defined */
