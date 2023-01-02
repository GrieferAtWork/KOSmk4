/* HASH CRC-32:0xcd085bb4 */
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
#ifndef __local_cthread_init_defined
#define __local_cthread_init_defined
#include <__crt.h>
#if defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self) || defined(__CRT_HAVE_cthread_self)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pthread_self_defined
#define __local___localdep_pthread_self_defined
#ifdef __CRT_HAVE_pthread_self
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pthread_t,__NOTHROW,__localdep_pthread_self,(void),pthread_self,())
#elif defined(__CRT_HAVE_thrd_current)
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pthread_t,__NOTHROW,__localdep_pthread_self,(void),thrd_current,())
#elif defined(__CRT_HAVE_thr_self)
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pthread_t,__NOTHROW,__localdep_pthread_self,(void),thr_self,())
#elif defined(__CRT_HAVE_cthread_self)
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pthread_t,__NOTHROW,__localdep_pthread_self,(void),cthread_self,())
#else /* ... */
#undef __local___localdep_pthread_self_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_self_defined */
__LOCAL_LIBC(cthread_init) __ULONGPTR_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cthread_init))(void) {
	__COMPILER_IMPURE();
	return (__ULONGPTR_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_pthread_self)();
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cthread_init_defined
#define __local___localdep_cthread_init_defined
#define __localdep_cthread_init __LIBC_LOCAL_NAME(cthread_init)
#endif /* !__local___localdep_cthread_init_defined */
#else /* __CRT_HAVE_pthread_self || __CRT_HAVE_thrd_current || __CRT_HAVE_thr_self || __CRT_HAVE_cthread_self */
#undef __local_cthread_init_defined
#endif /* !__CRT_HAVE_pthread_self && !__CRT_HAVE_thrd_current && !__CRT_HAVE_thr_self && !__CRT_HAVE_cthread_self */
#endif /* !__local_cthread_init_defined */
