/* HASH CRC-32:0xef4bd444 */
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
#ifndef __local_cthread_keycreate_defined
#define __local_cthread_keycreate_defined
#include <__crt.h>
#if defined(__CRT_HAVE_pthread_key_create) || defined(__CRT_HAVE_thr_keycreate) || defined(__CRT_HAVE___pthread_key_create)
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pthread_key_create_defined
#define __local___localdep_pthread_key_create_defined
#ifdef __CRT_HAVE_pthread_key_create
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,__localdep_pthread_key_create,(__pthread_key_t *__key, void (__LIBKCALL *__destr_function)(void *___value)),pthread_key_create,(__key,__destr_function))
#elif defined(__CRT_HAVE_thr_keycreate)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,__localdep_pthread_key_create,(__pthread_key_t *__key, void (__LIBKCALL *__destr_function)(void *___value)),thr_keycreate,(__key,__destr_function))
#elif defined(__CRT_HAVE___pthread_key_create)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,__localdep_pthread_key_create,(__pthread_key_t *__key, void (__LIBKCALL *__destr_function)(void *___value)),__pthread_key_create,(__key,__destr_function))
#else /* ... */
#undef __local___localdep_pthread_key_create_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_key_create_defined */
__LOCAL_LIBC(cthread_keycreate) __ATTR_OUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cthread_keycreate))(__pthread_key_t *__key) {
	return (__NAMESPACE_LOCAL_SYM __localdep_pthread_key_create)((__pthread_key_t *)__key, __NULLPTR) == 0 ? 0 : -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cthread_keycreate_defined
#define __local___localdep_cthread_keycreate_defined
#define __localdep_cthread_keycreate __LIBC_LOCAL_NAME(cthread_keycreate)
#endif /* !__local___localdep_cthread_keycreate_defined */
#else /* __CRT_HAVE_pthread_key_create || __CRT_HAVE_thr_keycreate || __CRT_HAVE___pthread_key_create */
#undef __local_cthread_keycreate_defined
#endif /* !__CRT_HAVE_pthread_key_create && !__CRT_HAVE_thr_keycreate && !__CRT_HAVE___pthread_key_create */
#endif /* !__local_cthread_keycreate_defined */
