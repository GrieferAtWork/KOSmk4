/* HASH CRC-32:0x1211f042 */
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
#ifndef __local_cnd_init_defined
#define __local_cnd_init_defined
#include <__crt.h>
#ifdef __CRT_HAVE_pthread_cond_init
#include <bits/crt/threads.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pthread_cond_init_defined
#define __local___localdep_pthread_cond_init_defined
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT(1),__errno_t,__NOTHROW_NCX,__localdep_pthread_cond_init,(__pthread_cond_t *__restrict __cond, __pthread_condattr_t const *__restrict __cond_attr),pthread_cond_init,(__cond,__cond_attr))
#endif /* !__local___localdep_pthread_cond_init_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(cnd_init) __ATTR_OUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cnd_init))(__cnd_t *__restrict __cond) {
	__errno_t __error;
	__error = (__NAMESPACE_LOCAL_SYM __localdep_pthread_cond_init)((__pthread_cond_t *)__cond, __NULLPTR);
	if __likely(!__error)
		return __thrd_success;
	return __thrd_error;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cnd_init_defined
#define __local___localdep_cnd_init_defined
#define __localdep_cnd_init __LIBC_LOCAL_NAME(cnd_init)
#endif /* !__local___localdep_cnd_init_defined */
#else /* __CRT_HAVE_pthread_cond_init */
#undef __local_cnd_init_defined
#endif /* !__CRT_HAVE_pthread_cond_init */
#endif /* !__local_cnd_init_defined */
