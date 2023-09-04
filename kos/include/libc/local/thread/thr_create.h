/* HASH CRC-32:0xd4bb1c8d */
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
#ifndef __local_thr_create_defined
#define __local_thr_create_defined
#include <__crt.h>
#ifdef __CRT_HAVE_pthread_create
#include <bits/crt/pthreadtypes.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pthread_attr_destroy_defined
#define __local___localdep_pthread_attr_destroy_defined
#ifdef __CRT_HAVE_pthread_attr_destroy
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,__localdep_pthread_attr_destroy,(__pthread_attr_t *__self),pthread_attr_destroy,(__self))
#elif defined(__CRT_HAVE___pthread_attr_destroy)
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,__localdep_pthread_attr_destroy,(__pthread_attr_t *__self),__pthread_attr_destroy,(__self))
#else /* ... */
#undef __local___localdep_pthread_attr_destroy_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_attr_destroy_defined */
#ifndef __local___localdep_pthread_attr_init_defined
#define __local___localdep_pthread_attr_init_defined
#ifdef __CRT_HAVE_pthread_attr_init
__CREDIRECT(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,__localdep_pthread_attr_init,(__pthread_attr_t *__self),pthread_attr_init,(__self))
#elif defined(__CRT_HAVE___pthread_attr_init)
__CREDIRECT(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,__localdep_pthread_attr_init,(__pthread_attr_t *__self),__pthread_attr_init,(__self))
#else /* ... */
#undef __local___localdep_pthread_attr_init_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_attr_init_defined */
#if !defined(__local___localdep_pthread_attr_setdetachstate_defined) && defined(__CRT_HAVE_pthread_attr_setdetachstate)
#define __local___localdep_pthread_attr_setdetachstate_defined
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,__localdep_pthread_attr_setdetachstate,(__pthread_attr_t *__self, int __detachstate),pthread_attr_setdetachstate,(__self,__detachstate))
#endif /* !__local___localdep_pthread_attr_setdetachstate_defined && __CRT_HAVE_pthread_attr_setdetachstate */
#if !defined(__local___localdep_pthread_attr_setscope_defined) && defined(__CRT_HAVE_pthread_attr_setscope)
#define __local___localdep_pthread_attr_setscope_defined
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,__localdep_pthread_attr_setscope,(__pthread_attr_t *__self, int __scope),pthread_attr_setscope,(__self,__scope))
#endif /* !__local___localdep_pthread_attr_setscope_defined && __CRT_HAVE_pthread_attr_setscope */
#ifndef __local___localdep_pthread_attr_setstack_defined
#define __local___localdep_pthread_attr_setstack_defined
#ifdef __CRT_HAVE_pthread_attr_setstack
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,__localdep_pthread_attr_setstack,(__pthread_attr_t *__self, void *__stackaddr, __SIZE_TYPE__ __stacksize),pthread_attr_setstack,(__self,__stackaddr,__stacksize))
#elif defined(__CRT_HAVE_pthread_attr_setstackaddr) && defined(__CRT_HAVE_pthread_attr_setstacksize)
__NAMESPACE_LOCAL_END
#include <libc/local/pthread/pthread_attr_setstack.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_pthread_attr_setstack __LIBC_LOCAL_NAME(pthread_attr_setstack)
#else /* ... */
#undef __local___localdep_pthread_attr_setstack_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_attr_setstack_defined */
#ifndef __local___localdep_pthread_attr_setstacksize_defined
#define __local___localdep_pthread_attr_setstacksize_defined
#ifdef __CRT_HAVE_pthread_attr_setstacksize
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,__localdep_pthread_attr_setstacksize,(__pthread_attr_t *__self, __SIZE_TYPE__ __stacksize),pthread_attr_setstacksize,(__self,__stacksize))
#elif (defined(__CRT_HAVE_pthread_attr_getstack) || (defined(__CRT_HAVE_pthread_attr_getstackaddr) && defined(__CRT_HAVE_pthread_attr_getstacksize))) && defined(__CRT_HAVE_pthread_attr_setstack)
__NAMESPACE_LOCAL_END
#include <libc/local/pthread/pthread_attr_setstacksize.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_pthread_attr_setstacksize __LIBC_LOCAL_NAME(pthread_attr_setstacksize)
#else /* ... */
#undef __local___localdep_pthread_attr_setstacksize_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_attr_setstacksize_defined */
#ifndef __local___localdep_pthread_create_defined
#define __local___localdep_pthread_create_defined
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT(1) __ATTR_NONNULL((3)),__errno_t,__NOTHROW_NCX,__localdep_pthread_create,(__pthread_t *__restrict __p_newthread, __pthread_attr_t const *__restrict __attr, void *(__LIBCCALL *__start_routine)(void *__arg), void *__arg),pthread_create,(__p_newthread,__attr,__start_routine,__arg))
#endif /* !__local___localdep_pthread_create_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/pthreadvalues.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(thr_create) __ATTR_OUT(6) __ATTR_NONNULL((3)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(thr_create))(void *__stack_base, __SIZE_TYPE__ __stack_size, void *(__LIBCCALL *__start_routine)(void *__arg), void *__arg, long __flags, __pthread_t *__newthread) {
	__errno_t __result;
	if (__flags || __stack_base || __stack_size) {
#if !defined(__CRT_HAVE_pthread_attr_init) && !defined(__CRT_HAVE___pthread_attr_init)
#ifdef __ENOSYS
		return __ENOSYS;
#else /* __ENOSYS */
		return 1;
#endif /* !__ENOSYS */
#else /* !__CRT_HAVE_pthread_attr_init && !__CRT_HAVE___pthread_attr_init */
		__pthread_attr_t __attr;
		if (__flags & ~(0 |
#if defined(__CRT_HAVE_pthread_attr_setscope) && defined(__PTHREAD_SCOPE_SYSTEM)
		              0x00000001 |
#endif /* __CRT_HAVE_pthread_attr_setscope && __PTHREAD_SCOPE_SYSTEM */
#if defined(__CRT_HAVE_pthread_attr_setdetachstate) && defined(__PTHREAD_CREATE_DETACHED)
		              0x00000040 |
#endif /* __CRT_HAVE_pthread_attr_setdetachstate && __PTHREAD_CREATE_DETACHED */
		              0)
#if !defined(__CRT_HAVE_pthread_attr_setstack) && !defined(__CRT_HAVE_pthread_attr_setstacksize)
		    || __stack_base || __stack_size
#elif !defined(__CRT_HAVE_pthread_attr_setstack) && (!defined(__CRT_HAVE_pthread_attr_setstackaddr) || !defined(__CRT_HAVE_pthread_attr_setstacksize))
		    || __stack_base
#elif !defined(__CRT_HAVE_pthread_attr_setstacksize) && ((!defined(__CRT_HAVE_pthread_attr_getstack) && (!defined(__CRT_HAVE_pthread_attr_getstackaddr) || !defined(__CRT_HAVE_pthread_attr_getstacksize))) || !defined(__CRT_HAVE_pthread_attr_setstack))
		    || (!__stack_base && __stack_size)
#endif /* ... */
		    )
		{
#ifdef __ENOSYS
			return __ENOSYS;
#else /* __ENOSYS */
			return 1;
#endif /* !__ENOSYS */
		}
		__result = (__NAMESPACE_LOCAL_SYM __localdep_pthread_attr_init)(&__attr);
		if __unlikely(__result != 0)
			return __result;
#if defined(__CRT_HAVE_pthread_attr_setscope) && defined(__PTHREAD_SCOPE_SYSTEM)
		if (__flags & 0x00000001) {
			__result = (__NAMESPACE_LOCAL_SYM __localdep_pthread_attr_setscope)(&__attr, __PTHREAD_SCOPE_SYSTEM);
			if __unlikely(__result != 0)
				goto __done_attr;
		}
#endif /* __CRT_HAVE_pthread_attr_setscope && __PTHREAD_SCOPE_SYSTEM */
#if defined(__CRT_HAVE_pthread_attr_setdetachstate) && defined(__PTHREAD_CREATE_DETACHED)
		if (__flags & 0x00000040) {
			__result = (__NAMESPACE_LOCAL_SYM __localdep_pthread_attr_setdetachstate)(&__attr, __PTHREAD_CREATE_DETACHED);
			if __unlikely(__result != 0)
				goto __done_attr;
		}
#endif /* __CRT_HAVE_pthread_attr_setdetachstate && __PTHREAD_CREATE_DETACHED */
#if defined(__CRT_HAVE_pthread_attr_setstack) || (defined(__CRT_HAVE_pthread_attr_setstackaddr) && defined(__CRT_HAVE_pthread_attr_setstacksize))
		if (__stack_base) {
			__result = (__NAMESPACE_LOCAL_SYM __localdep_pthread_attr_setstack)(&__attr, __stack_base, __stack_size);
			if __unlikely(__result != 0)
				goto __done_attr;
		} else
#endif /* __CRT_HAVE_pthread_attr_setstack || (__CRT_HAVE_pthread_attr_setstackaddr && __CRT_HAVE_pthread_attr_setstacksize) */
#if defined(__CRT_HAVE_pthread_attr_setstacksize) || ((defined(__CRT_HAVE_pthread_attr_getstack) || (defined(__CRT_HAVE_pthread_attr_getstackaddr) && defined(__CRT_HAVE_pthread_attr_getstacksize))) && defined(__CRT_HAVE_pthread_attr_setstack))
		if (__stack_size) {
			__result = (__NAMESPACE_LOCAL_SYM __localdep_pthread_attr_setstacksize)(&__attr, __stack_size);
			if __unlikely(__result != 0)
				goto __done_attr;
		} else
#endif /* __CRT_HAVE_pthread_attr_setstacksize || ((__CRT_HAVE_pthread_attr_getstack || (__CRT_HAVE_pthread_attr_getstackaddr && __CRT_HAVE_pthread_attr_getstacksize)) && __CRT_HAVE_pthread_attr_setstack) */
		{
		}

		/* Actually create the new thread. */
		__result = (__NAMESPACE_LOCAL_SYM __localdep_pthread_create)(__newthread, &__attr, __start_routine, __arg);
		goto __done_attr; /* Suppress warnings if not otherwise used. */
__done_attr:;
#if defined(__CRT_HAVE_pthread_attr_destroy) || defined(__CRT_HAVE___pthread_attr_destroy)
		(__NAMESPACE_LOCAL_SYM __localdep_pthread_attr_destroy)(&__attr);
#endif /* __CRT_HAVE_pthread_attr_destroy || __CRT_HAVE___pthread_attr_destroy */
#endif /* __CRT_HAVE_pthread_attr_init || __CRT_HAVE___pthread_attr_init */
	} else {
		/* Create new thread with default attributes. */
		__result = (__NAMESPACE_LOCAL_SYM __localdep_pthread_create)(__newthread, __NULLPTR, __start_routine, __arg);
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_thr_create_defined
#define __local___localdep_thr_create_defined
#define __localdep_thr_create __LIBC_LOCAL_NAME(thr_create)
#endif /* !__local___localdep_thr_create_defined */
#else /* __CRT_HAVE_pthread_create */
#undef __local_thr_create_defined
#endif /* !__CRT_HAVE_pthread_create */
#endif /* !__local_thr_create_defined */
