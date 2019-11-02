/* HASH CRC-32:0x60bb8d6c */
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
#ifndef __local_thrd_join_defined
#if defined(__CRT_HAVE_pthread_join)
#define __local_thrd_join_defined 1
#include <bits/pthreadtypes.h>
#include <hybrid/typecore.h>

#include <bits/threads.h>
/* Dependency: "pthread_join" */
#ifndef ____localdep_pthread_join_defined
#define ____localdep_pthread_join_defined 1
#if defined(__CRT_HAVE_pthread_join)
/* Make calling thread wait for termination of the thread THREAD. The
 * exit status of the thread is stored in *THREAD_RETURN, if THREAD_RETURN
 * is not NULL */
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_pthread_join,(__pthread_t __pthread, void **__thread_return),pthread_join,(__pthread,__thread_return))
#else /* LIBC: pthread_join */
#undef ____localdep_pthread_join_defined
#endif /* pthread_join... */
#endif /* !____localdep_pthread_join_defined */

__NAMESPACE_LOCAL_BEGIN
/* Block current thread until execution of THR is complete.
 * In case that RES is not NULL, will store the return value of THR when exiting
 * s.a. `pthread_join()' */
__LOCAL_LIBC(thrd_join) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(thrd_join))(__thrd_t __thr,
                                                       int *__res) {
#line 212 "kos/src/libc/magic/threads.c"
	int __error;
#if __SIZEOF_POINTER__ == __SIZEOF_INT__
	void *__resptr;
	__error = __localdep_pthread_join((__pthread_t)__thr, __res ? &__resptr : __NULLPTR);
	if __likely(!__error) {
		if (__res)
			*__res = (int)(unsigned int)(__UINTPTR_TYPE__)__resptr;
		return 0; /* thrd_success */
	}
#else /* __SIZEOF_POINTER__ == __SIZEOF_INT__ */
	__error = __localdep_pthread_join((__pthread_t)__thr, (void **)__res);
	if __likely(!__error)
		return 0; /* thrd_success */
#endif /* __SIZEOF_POINTER__ != __SIZEOF_INT__ */
	return 2; /* thrd_error */
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_pthread_join) */
#endif /* !__local_thrd_join_defined */
