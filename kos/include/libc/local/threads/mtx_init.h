/* HASH CRC-32:0xdbf8c5ab */
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
#ifndef __local_mtx_init_defined
#define __local_mtx_init_defined
#include <__crt.h>
#ifdef __CRT_HAVE_pthread_mutex_init
#include <features.h>
#include <bits/crt/threads.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pthread_mutex_init_defined
#define __local___localdep_pthread_mutex_init_defined
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,__localdep_pthread_mutex_init,(__pthread_mutex_t *__self, __pthread_mutexattr_t const *__mutexattr),pthread_mutex_init,(__self,__mutexattr))
#endif /* !__local___localdep_pthread_mutex_init_defined */
#if !defined(__local___localdep_pthread_mutexattr_destroy_defined) && defined(__CRT_HAVE_pthread_mutexattr_destroy)
#define __local___localdep_pthread_mutexattr_destroy_defined
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,__localdep_pthread_mutexattr_destroy,(__pthread_mutexattr_t *__self),pthread_mutexattr_destroy,(__self))
#endif /* !__local___localdep_pthread_mutexattr_destroy_defined && __CRT_HAVE_pthread_mutexattr_destroy */
#if !defined(__local___localdep_pthread_mutexattr_init_defined) && defined(__CRT_HAVE_pthread_mutexattr_init)
#define __local___localdep_pthread_mutexattr_init_defined
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,__localdep_pthread_mutexattr_init,(__pthread_mutexattr_t *__self),pthread_mutexattr_init,(__self))
#endif /* !__local___localdep_pthread_mutexattr_init_defined && __CRT_HAVE_pthread_mutexattr_init */
#ifndef __local___localdep_pthread_mutexattr_settype_defined
#define __local___localdep_pthread_mutexattr_settype_defined
#ifdef __CRT_HAVE_pthread_mutexattr_settype
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,__localdep_pthread_mutexattr_settype,(__pthread_mutexattr_t *__self, int __kind),pthread_mutexattr_settype,(__self,__kind))
#elif defined(__CRT_HAVE_pthread_mutexattr_setkind_np)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,__localdep_pthread_mutexattr_settype,(__pthread_mutexattr_t *__self, int __kind),pthread_mutexattr_setkind_np,(__self,__kind))
#else /* ... */
#undef __local___localdep_pthread_mutexattr_settype_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_mutexattr_settype_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/threads.h>
#include <asm/crt/pthreadvalues.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(mtx_init) __ATTR_OUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mtx_init))(__mtx_t *__restrict __mutex, __STDC_INT_AS_UINT_T __type) {
	__errno_t __error;
	if (__type == __mtx_plain) {
		__error = (__NAMESPACE_LOCAL_SYM __localdep_pthread_mutex_init)((__pthread_mutex_t *)__mutex, __NULLPTR);
	} else {
		__pthread_mutexattr_t __attr;
		__error = (__NAMESPACE_LOCAL_SYM __localdep_pthread_mutexattr_init)(&__attr);
		if (__error == 0) {
			__error = (__NAMESPACE_LOCAL_SYM __localdep_pthread_mutexattr_settype)(&__attr,
			                                  __type == __mtx_recursive
			                                  ? __PTHREAD_MUTEX_RECURSIVE
			                                  : __PTHREAD_MUTEX_TIMED);
			if (__error == 0)
				__error = (__NAMESPACE_LOCAL_SYM __localdep_pthread_mutex_init)((__pthread_mutex_t *)__mutex, &__attr);
			(__NAMESPACE_LOCAL_SYM __localdep_pthread_mutexattr_destroy)(&__attr);
		}
	}
	if __likely(!__error)
		return __thrd_success;
	return __thrd_error;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mtx_init_defined
#define __local___localdep_mtx_init_defined
#define __localdep_mtx_init __LIBC_LOCAL_NAME(mtx_init)
#endif /* !__local___localdep_mtx_init_defined */
#else /* __CRT_HAVE_pthread_mutex_init */
#undef __local_mtx_init_defined
#endif /* !__CRT_HAVE_pthread_mutex_init */
#endif /* !__local_mtx_init_defined */
