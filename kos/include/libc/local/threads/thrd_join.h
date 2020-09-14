/* HASH CRC-32:0xb327fcfa */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_thrd_join_defined
#define __local_thrd_join_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_pthread_join
#include <bits/crt/threads.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: pthread_join from pthread */
#ifndef __local___localdep_pthread_join_defined
#define __local___localdep_pthread_join_defined 1
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
/* Make calling thread wait for termination of the thread THREAD. The
 * exit status of the thread is stored in *THREAD_RETURN, if THREAD_RETURN
 * is not NULL
 * @return: EOK: Success */
__CREDIRECT(,__errno_t,__NOTHROW_RPC,__localdep_pthread_join,(__pthread_t __pthread, void **__thread_return),pthread_join,(__pthread,__thread_return))
#endif /* !__local___localdep_pthread_join_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/threads.h>
__NAMESPACE_LOCAL_BEGIN
/* Block current thread until execution of THR is complete.
 * In case that RES is not NULL, will store the return value of THR when exiting
 * s.a. `pthread_join()' */
__LOCAL_LIBC(thrd_join) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(thrd_join))(__thrd_t __thr, int *__res) {
	__errno_t __error;
#if __SIZEOF_POINTER__ != __SIZEOF_INT__
	void *__resptr;
	__error = __localdep_pthread_join((__pthread_t)__thr, __res ? &__resptr : __NULLPTR);
	if __likely(!__error) {
		if (__res)
			*__res = (int)(unsigned int)(__UINTPTR_TYPE__)__resptr;
		return __thrd_success;
	}
#else /* __SIZEOF_POINTER__ != __SIZEOF_INT__ */
	__error = __localdep_pthread_join((__pthread_t)__thr, (void **)__res);
	if __likely(!__error)
		return __thrd_success;
#endif /* __SIZEOF_POINTER__ == __SIZEOF_INT__ */
	return __thrd_error;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_thrd_join_defined
#define __local___localdep_thrd_join_defined 1
#define __localdep_thrd_join __LIBC_LOCAL_NAME(thrd_join)
#endif /* !__local___localdep_thrd_join_defined */
#else /* __CRT_HAVE_pthread_join */
#undef __local_thrd_join_defined
#endif /* !__CRT_HAVE_pthread_join */
#endif /* !__local_thrd_join_defined */
