/* HASH CRC-32:0xf58b5f30 */
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
#ifndef __local_tss_create_defined
#define __local_tss_create_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_pthread_key_create
#include <bits/crt/threads.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pthread_key_create_defined
#define __local___localdep_pthread_key_create_defined 1
__NAMESPACE_LOCAL_END
#ifndef ____pthread_destr_function_t_defined
#define ____pthread_destr_function_t_defined 1
typedef void (__LIBKCALL *__pthread_destr_function_t)(void *);
#endif /* !____pthread_destr_function_t_defined */
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,__localdep_pthread_key_create,(__pthread_key_t *__key, __pthread_destr_function_t __destr_function),pthread_key_create,(__key,__destr_function))
#endif /* !__local___localdep_pthread_key_create_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(tss_create) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(tss_create))(__tss_t *__tss_id, __tss_dtor_t __destructor) {
	__errno_t __error;
	__error = (__NAMESPACE_LOCAL_SYM __localdep_pthread_key_create)((__pthread_key_t *)__tss_id, __destructor);
	if __likely(!__error)
		return __thrd_success;
	return __thrd_error;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tss_create_defined
#define __local___localdep_tss_create_defined 1
#define __localdep_tss_create __LIBC_LOCAL_NAME(tss_create)
#endif /* !__local___localdep_tss_create_defined */
#else /* __CRT_HAVE_pthread_key_create */
#undef __local_tss_create_defined
#endif /* !__CRT_HAVE_pthread_key_create */
#endif /* !__local_tss_create_defined */
