/* HASH CRC-32:0x243be93a */
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
#ifndef __local_cnd_signal_defined
#define __local_cnd_signal_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_pthread_cond_signal
#include <bits/crt/threads.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: pthread_cond_signal from pthread */
#ifndef __local___localdep_pthread_cond_signal_defined
#define __local___localdep_pthread_cond_signal_defined 1
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
/* >> pthread_cond_signal(3)
 * Wake up one thread waiting for condition variable `cond'
 * @return: EOK: Success */
__CREDIRECT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,__localdep_pthread_cond_signal,(__pthread_cond_t *__cond),pthread_cond_signal,(__cond))
#endif /* !__local___localdep_pthread_cond_signal_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
/* >> cnd_signal(3)
 * Wakeup one thread currently waiting on the given
 * condition variable (s.a. `pthread_cond_signal(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__LOCAL_LIBC(cnd_signal) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cnd_signal))(__cnd_t *__restrict __cond) {
	__errno_t __error;
	__error = __localdep_pthread_cond_signal((__pthread_cond_t *)__cond);
	if __likely(!__error)
		return __thrd_success;
	return __thrd_error;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cnd_signal_defined
#define __local___localdep_cnd_signal_defined 1
#define __localdep_cnd_signal __LIBC_LOCAL_NAME(cnd_signal)
#endif /* !__local___localdep_cnd_signal_defined */
#else /* __CRT_HAVE_pthread_cond_signal */
#undef __local_cnd_signal_defined
#endif /* !__CRT_HAVE_pthread_cond_signal */
#endif /* !__local_cnd_signal_defined */
