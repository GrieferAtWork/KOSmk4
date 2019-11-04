/* HASH CRC-32:0x656ba94a */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_tss_create_defined
#ifdef __CRT_HAVE_pthread_key_create
#define __local_tss_create_defined 1
#ifndef ____pthread_destr_function_t_defined
#define ____pthread_destr_function_t_defined 1
typedef void (__LIBCCALL *__pthread_destr_function_t)(void *);
#endif /* !____pthread_destr_function_t_defined */
#include <bits/threads.h>

#include <bits/pthreadtypes.h>
/* Dependency: "pthread_key_create" */
#ifndef ____localdep_pthread_key_create_defined
#define ____localdep_pthread_key_create_defined 1
#ifdef __CRT_HAVE_pthread_key_create
/* Create a key value identifying a location in the thread-specific
 * data area. Each thread maintains a distinct thread-specific data
 * area. DESTR_FUNCTION, if non-NULL, is called with the value
 * associated to that key when the key is destroyed.
 * DESTR_FUNCTION is not called if the value associated is NULL when
 * the key is destroyed */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_pthread_key_create,(__pthread_key_t *__key, __pthread_destr_function_t __destr_function),pthread_key_create,(__key,__destr_function))
#else /* LIBC: pthread_key_create */
#undef ____localdep_pthread_key_create_defined
#endif /* pthread_key_create... */
#endif /* !____localdep_pthread_key_create_defined */

__NAMESPACE_LOCAL_BEGIN
/* Create new thread-specific storage key and stores it in the object pointed by TSS_ID.
 * If DESTRUCTOR is not NULL, the function will be called when the thread terminates
 * s.a. `pthread_key_create()' */
__LOCAL_LIBC(tss_create) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(tss_create))(__tss_t *__tss_id,
                                                        __tss_dtor_t __destructor) {
#line 480 "kos/src/libc/magic/threads.c"
	int __error;
	__error = __localdep_pthread_key_create((__pthread_key_t *)__tss_id, __destructor);
	if __likely(!__error)
		return 0; /* thrd_success */
	return 2; /* thrd_error */
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_pthread_key_create) */
#endif /* !__local_tss_create_defined */
