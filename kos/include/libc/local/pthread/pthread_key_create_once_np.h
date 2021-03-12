/* HASH CRC-32:0x804462c7 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_pthread_key_create_once_np_defined
#define __local_pthread_key_create_once_np_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_pthread_key_create
#ifndef ____pthread_destr_function_t_defined
#define ____pthread_destr_function_t_defined 1
typedef void (__LIBKCALL *__pthread_destr_function_t)(void *);
#endif /* !____pthread_destr_function_t_defined */
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: pthread_key_create from pthread */
#ifndef __local___localdep_pthread_key_create_defined
#define __local___localdep_pthread_key_create_defined 1
/* >> pthread_key_create(3)
 * Create a key value identifying a location in the thread-specific
 * data area. Each thread maintains a distinct thread-specific data
 * area. `destr_function', if non-`NULL', is called with the value
 * associated to that key when the key is destroyed.
 * `destr_function' is not called if the value associated is `NULL'
 * when the key is destroyed
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to create the key */
__CREDIRECT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,__localdep_pthread_key_create,(__pthread_key_t *__key, __pthread_destr_function_t __destr_function),pthread_key_create,(__key,__destr_function))
#endif /* !__local___localdep_pthread_key_create_defined */
/* Dependency: pthread_key_delete from pthread */
#ifndef __local___localdep_pthread_key_delete_defined
#define __local___localdep_pthread_key_delete_defined 1
#ifdef __CRT_HAVE_pthread_key_delete
/* >> pthread_key_delete(3)
 * Destroy the given `key'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid `key' */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,__localdep_pthread_key_delete,(__pthread_key_t __key),pthread_key_delete,(__key))
#elif defined(__CRT_HAVE_tss_delete)
/* >> pthread_key_delete(3)
 * Destroy the given `key'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid `key' */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,__localdep_pthread_key_delete,(__pthread_key_t __key),tss_delete,(__key))
#else /* ... */
#undef __local___localdep_pthread_key_delete_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_key_delete_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/__atomic.h>
__NAMESPACE_LOCAL_BEGIN
/* >> pthread_key_create_once_np(3)
 * Same as `pthread_key_create()', but the given `key' must be pre-initialized
 * using the static initializer `PTHREAD_ONCE_KEY_NP', whilst this function will
 * make sure that even in the event of multiple simultaneous threads calling
 * this function, only one will create the key, and all others will wait until
 * the key has been created. Once the key was created, further calls to this
 * function will no longer block, but simply return immediately.
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to create the key */
__LOCAL_LIBC(pthread_key_create_once_np) __ATTR_NONNULL((1)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pthread_key_create_once_np))(__pthread_key_t *__key, __pthread_destr_function_t __destr_function) {
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
	__error = __localdep_pthread_key_create(__key, __destr_function);
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
		__localdep_pthread_key_delete(__kv);
#endif /* __CRT_HAVE_pthread_key_delete || __CRT_HAVE_tss_delete */
		goto __again;
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_key_create_once_np_defined
#define __local___localdep_pthread_key_create_once_np_defined 1
#define __localdep_pthread_key_create_once_np __LIBC_LOCAL_NAME(pthread_key_create_once_np)
#endif /* !__local___localdep_pthread_key_create_once_np_defined */
#else /* __CRT_HAVE_pthread_key_create */
#undef __local_pthread_key_create_once_np_defined
#endif /* !__CRT_HAVE_pthread_key_create */
#endif /* !__local_pthread_key_create_once_np_defined */
