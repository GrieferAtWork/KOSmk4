/* HASH CRC-32:0xd5105c2 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_thr_getspecific_defined
#define __local_thr_getspecific_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_pthread_getspecific) || defined(__CRT_HAVE_tss_get) || defined(__CRT_HAVE_pthread_getspecificptr_np)) && (defined(__CRT_HAVE_pthread_setspecific) || defined(__CRT_HAVE_thr_setspecific))
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pthread_getspecific_defined
#define __local___localdep_pthread_getspecific_defined
#ifdef __CRT_HAVE_pthread_getspecific
__CREDIRECT(__ATTR_WUNUSED,void *,__NOTHROW_NCX,__localdep_pthread_getspecific,(__pthread_key_t __key),pthread_getspecific,(__key))
#elif defined(__CRT_HAVE_tss_get)
__CREDIRECT(__ATTR_WUNUSED,void *,__NOTHROW_NCX,__localdep_pthread_getspecific,(__pthread_key_t __key),tss_get,(__key))
#elif defined(__CRT_HAVE_pthread_getspecificptr_np)
__NAMESPACE_LOCAL_END
#include <libc/local/pthread/pthread_getspecific.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_pthread_getspecific __LIBC_LOCAL_NAME(pthread_getspecific)
#else /* ... */
#undef __local___localdep_pthread_getspecific_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_getspecific_defined */
#ifndef __local___localdep_pthread_setspecific_defined
#define __local___localdep_pthread_setspecific_defined
#ifdef __CRT_HAVE_pthread_setspecific
__CREDIRECT(,__errno_t,__NOTHROW_NCX,__localdep_pthread_setspecific,(__pthread_key_t __key, void const *__pointer),pthread_setspecific,(__key,__pointer))
#elif defined(__CRT_HAVE_thr_setspecific)
__CREDIRECT(,__errno_t,__NOTHROW_NCX,__localdep_pthread_setspecific,(__pthread_key_t __key, void const *__pointer),thr_setspecific,(__key,__pointer))
#else /* ... */
#undef __local___localdep_pthread_setspecific_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_setspecific_defined */
__LOCAL_LIBC(thr_getspecific) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(thr_getspecific))(__pthread_key_t __key, void **__p_val) {
	void *__val;
	*__p_val = __val = (__NAMESPACE_LOCAL_SYM __localdep_pthread_getspecific)(__key);
	if (__val != __NULLPTR)
		return 0;
	return (__NAMESPACE_LOCAL_SYM __localdep_pthread_setspecific)(__key, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_thr_getspecific_defined
#define __local___localdep_thr_getspecific_defined
#define __localdep_thr_getspecific __LIBC_LOCAL_NAME(thr_getspecific)
#endif /* !__local___localdep_thr_getspecific_defined */
#else /* (__CRT_HAVE_pthread_getspecific || __CRT_HAVE_tss_get || __CRT_HAVE_pthread_getspecificptr_np) && (__CRT_HAVE_pthread_setspecific || __CRT_HAVE_thr_setspecific) */
#undef __local_thr_getspecific_defined
#endif /* (!__CRT_HAVE_pthread_getspecific && !__CRT_HAVE_tss_get && !__CRT_HAVE_pthread_getspecificptr_np) || (!__CRT_HAVE_pthread_setspecific && !__CRT_HAVE_thr_setspecific) */
#endif /* !__local_thr_getspecific_defined */
