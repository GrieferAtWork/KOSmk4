/* HASH CRC-32:0x8d17d748 */
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
#ifndef __local_pthread_once_defined
#define __local_pthread_once_defined
#include <__crt.h>
#include <kos/anno.h>
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_except_rethrow_defined) && defined(__CRT_HAVE_except_rethrow)
#define __local___localdep_except_rethrow_defined
__COMPILER_CREDIRECT_VOID(__LIBC,__ATTR_COLD __ATTR_NORETURN,__THROWING,__LIBKCALL,__localdep_except_rethrow,(void),except_rethrow,())
#endif /* !__local___localdep_except_rethrow_defined && __CRT_HAVE_except_rethrow */
__NAMESPACE_LOCAL_END
#include <asm/crt/pthreadvalues.h>
#include <hybrid/__atomic.h>
#include <hybrid/sched/__yield.h>
#include <asm/os/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(pthread_once) __ATTR_NONNULL((1, 2)) __errno_t
(__LIBCCALL __LIBC_LOCAL_NAME(pthread_once))(__pthread_once_t *__once_control, void (__LIBCCALL *__init_routine)(void)) __THROWS(...) {
	__pthread_once_t __status;
__again:
	__status = __hybrid_atomic_cmpxch_val(*__once_control,
	                                    __PTHREAD_ONCE_INIT,
	                                    __PTHREAD_ONCE_INIT + 1,
	                                    __ATOMIC_SEQ_CST,
	                                    __ATOMIC_SEQ_CST);
	if (__status == __PTHREAD_ONCE_INIT) {
		/* To  comply with POSIX, we must be able to roll-back once
		 * initialization when `init_routine' "cancels" our thread. */
#ifdef __cplusplus
		try {
			(*__init_routine)();
		} catch (...) {
			/* roll-back... */
			__hybrid_atomic_store(*__once_control,
			                      __PTHREAD_ONCE_INIT,
			                      __ATOMIC_RELEASE);
#ifdef __CRT_HAVE_except_rethrow
			(__NAMESPACE_LOCAL_SYM __localdep_except_rethrow)();
#else /* __CRT_HAVE_except_rethrow */
			throw;
#endif /* !__CRT_HAVE_except_rethrow */
		}
#else /* __cplusplus */
		(*__init_routine)();
#endif /* !__cplusplus */
		__hybrid_atomic_store(*__once_control,
		                      __PTHREAD_ONCE_INIT + 2,
		                      __ATOMIC_RELEASE);
	} else if (__status != __PTHREAD_ONCE_INIT + 2) {
		if __unlikely(__status != __PTHREAD_ONCE_INIT + 1) {
			/* Quote(https://man7.org/linux/man-pages/man3/pthread_once.3p.html):
			 * """
			 * If  an implementation  detects that  the value  specified by the
			 * once_control argument  to pthread_once()  does  not refer  to  a
			 * pthread_once_t object  initialized by  PTHREAD_ONCE_INIT, it  is
			 * recommended that the function should fail and report an [EINVAL]
			 * error.
			 * """
			 */
#ifdef __EINVAL
			return __EINVAL;
#else /* __EINVAL */
			return 1;
#endif /* !__EINVAL */
		}

		/* Wait for some other thread to finish init_routine() */
		do {
			__hybrid_yield();
		} while (__hybrid_atomic_load(*__once_control, __ATOMIC_ACQUIRE) ==
		         __PTHREAD_ONCE_INIT + 1);
		/* Must re-check the once-status, since another thread may have
		 * rolled back completion  in case its  call to  `init_routine'
		 * resulted in an exception being called. (or to speak in terms
		 * of POSIX, caused its thread to be "canceled") */
		goto __again;
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_once_defined
#define __local___localdep_pthread_once_defined
#define __localdep_pthread_once __LIBC_LOCAL_NAME(pthread_once)
#endif /* !__local___localdep_pthread_once_defined */
#endif /* !__local_pthread_once_defined */
