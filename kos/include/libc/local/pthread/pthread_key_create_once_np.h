/* HASH CRC-32:0x706601cc */
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
#ifndef __local_pthread_key_create_once_np_defined
#define __local_pthread_key_create_once_np_defined
#include <__crt.h>
#if defined(__CRT_HAVE_pthread_key_create) || defined(__CRT_HAVE_thr_keycreate)
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pthread_key_create_defined
#define __local___localdep_pthread_key_create_defined
#ifdef __CRT_HAVE_pthread_key_create
__CREDIRECT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,__localdep_pthread_key_create,(__pthread_key_t *__key, void (__LIBKCALL *__destr_function)(void *___value)),pthread_key_create,(__key,__destr_function))
#elif defined(__CRT_HAVE_thr_keycreate)
__CREDIRECT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,__localdep_pthread_key_create,(__pthread_key_t *__key, void (__LIBKCALL *__destr_function)(void *___value)),thr_keycreate,(__key,__destr_function))
#else /* ... */
#undef __local___localdep_pthread_key_create_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_key_create_defined */
#ifndef __local___localdep_pthread_key_delete_defined
#define __local___localdep_pthread_key_delete_defined
#ifdef __CRT_HAVE_pthread_key_delete
__CREDIRECT(,__errno_t,__NOTHROW_NCX,__localdep_pthread_key_delete,(__pthread_key_t __key),pthread_key_delete,(__key))
#elif defined(__CRT_HAVE_tss_delete)
__CREDIRECT(,__errno_t,__NOTHROW_NCX,__localdep_pthread_key_delete,(__pthread_key_t __key),tss_delete,(__key))
#else /* ... */
#undef __local___localdep_pthread_key_delete_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_key_delete_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/__atomic.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(pthread_key_create_once_np) __ATTR_NONNULL((1)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pthread_key_create_once_np))(__pthread_key_t *__key, void (__LIBKCALL *__destr_function)(void *)) {
	__pthread_key_t __kv;
	__errno_t __error;
__again:
	__kv = __hybrid_atomic_load(*__key, __ATOMIC_ACQUIRE);
#ifdef __PTHREAD_ONCE_KEY_NP
	if (__kv != __PTHREAD_ONCE_KEY_NP)
#else /* __PTHREAD_ONCE_KEY_NP */
	if (__kv != (__pthread_key_t)-1)
#endif /* !__PTHREAD_ONCE_KEY_NP */
	{
		return 0; /* Already initialized. */
	}

	/* Try to do the init ourselves. */
	__error = (__NAMESPACE_LOCAL_SYM __localdep_pthread_key_create)(__key, __destr_function);
	if __unlikely(__error != 0)
		return __error; /* Error... */

	/* Try to save the results. */
#ifdef __PTHREAD_ONCE_KEY_NP
	if __unlikely(!__hybrid_atomic_cmpxch(*__key, __PTHREAD_ONCE_KEY_NP, __kv,
	                                    __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST))
#else /* __PTHREAD_ONCE_KEY_NP */
	if __unlikely(!__hybrid_atomic_cmpxch(*__key, (__pthread_key_t)-1, __kv,
	                                    __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST))
#endif /* !__PTHREAD_ONCE_KEY_NP */
	{
		/* Someone else was faster. - Destroy our version of the key,  and
		 * try again in order to use the other key that was created in the
		 * mean time. */
#if defined(__CRT_HAVE_pthread_key_delete) || defined(__CRT_HAVE_tss_delete)
		(__NAMESPACE_LOCAL_SYM __localdep_pthread_key_delete)(__kv);
#endif /* __CRT_HAVE_pthread_key_delete || __CRT_HAVE_tss_delete */
		goto __again;
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_key_create_once_np_defined
#define __local___localdep_pthread_key_create_once_np_defined
#define __localdep_pthread_key_create_once_np __LIBC_LOCAL_NAME(pthread_key_create_once_np)
#endif /* !__local___localdep_pthread_key_create_once_np_defined */
#else /* __CRT_HAVE_pthread_key_create || __CRT_HAVE_thr_keycreate */
#undef __local_pthread_key_create_once_np_defined
#endif /* !__CRT_HAVE_pthread_key_create && !__CRT_HAVE_thr_keycreate */
#endif /* !__local_pthread_key_create_once_np_defined */
