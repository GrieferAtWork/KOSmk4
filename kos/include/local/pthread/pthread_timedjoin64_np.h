/* HASH CRC-32:0x8b646bbf */
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
#ifndef __local_pthread_timedjoin64_np_defined
#ifdef __CRT_HAVE_pthread_timedjoin_np
#define __local_pthread_timedjoin64_np_defined 1
#include <bits/pthreadtypes.h>
#include <bits/timespec.h>
#include <bits/pthreadtypes.h>

#include <bits/timespec.h>
/* Dependency: "pthread_timedjoin32_np" from "pthread" */
#ifndef ____localdep_pthread_timedjoin32_np_defined
#define ____localdep_pthread_timedjoin32_np_defined 1
#ifdef __CRT_HAVE_pthread_timedjoin_np
/* Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL. */
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_pthread_timedjoin32_np,(__pthread_t __pthread, void **__thread_return, struct __timespec32 const *__abstime),pthread_timedjoin_np,(__pthread,__thread_return,__abstime))
#else /* LIBC: pthread_timedjoin_np */
#undef ____localdep_pthread_timedjoin32_np_defined
#endif /* pthread_timedjoin32_np... */
#endif /* !____localdep_pthread_timedjoin32_np_defined */

__NAMESPACE_LOCAL_BEGIN
/* Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL. */
__LOCAL_LIBC(pthread_timedjoin64_np) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(pthread_timedjoin64_np))(__pthread_t __pthread,
                                                                    void **__thread_return,
                                                                    struct __timespec64 const *__abstime) {
#line 294 "kos/src/libc/magic/pthread.c"
	int __result;
	struct __timespec32 __abstime32;
	__abstime32.tv_sec  = (__time32_t)__abstime->tv_sec;
	__abstime32.tv_nsec = __abstime->tv_nsec;
	__result = __localdep_pthread_timedjoin32_np(__pthread, __thread_return, &__abstime32);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_pthread_timedjoin_np */
#endif /* !__local_pthread_timedjoin64_np_defined */
