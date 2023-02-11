/* HASH CRC-32:0xd34116e5 */
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
#ifndef __local___localdep_futex_waitwhile_defined
#define __local___localdep_futex_waitwhile_defined
#ifdef __CRT_HAVE_futex_waitwhile
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_futex_waitwhile,(__uintptr_t *__uaddr, __uintptr_t __equal_to_value),futex_waitwhile,(__uaddr,__equal_to_value))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.futex/futex_waitwhile.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_futex_waitwhile __LIBC_LOCAL_NAME(futex_waitwhile)
#else /* ... */
#undef __local___localdep_futex_waitwhile_defined
#endif /* !... */
#endif /* !__local___localdep_futex_waitwhile_defined */
#ifndef __local___localdep_futex_wakeall_defined
#define __local___localdep_futex_wakeall_defined
#ifdef __CRT_HAVE_futex_wakeall
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_futex_wakeall,(__uintptr_t *__uaddr),futex_wakeall,(__uaddr))
#elif defined(__CRT_HAVE_futex_wake) || defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.futex/futex_wakeall.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_futex_wakeall __LIBC_LOCAL_NAME(futex_wakeall)
#else /* ... */
#undef __local___localdep_futex_wakeall_defined
#endif /* !... */
#endif /* !__local___localdep_futex_wakeall_defined */
#ifndef __local___localdep_lfutex64_defined
#define __local___localdep_lfutex64_defined
#if defined(__CRT_HAVE_lfutex) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CVREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_lfutex64,(__uintptr_t *__uaddr, __syscall_ulong_t __futex_op, __uintptr_t __val),lfutex,(__uaddr,__futex_op,__val),__val,2,(void *,__UINTPTR_TYPE__))
#elif defined(__CRT_HAVE_lfutex64)
__CVREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_lfutex64,(__uintptr_t *__uaddr, __syscall_ulong_t __futex_op, __uintptr_t __val),lfutex64,(__uaddr,__futex_op,__val),__val,2,(void *,__UINTPTR_TYPE__))
#elif defined(__CRT_HAVE_lfutex)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.futex/lfutex64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_lfutex64 __LIBC_LOCAL_NAME(lfutex64)
#else /* ... */
#undef __local___localdep_lfutex64_defined
#endif /* !... */
#endif /* !__local___localdep_lfutex64_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/pthreadvalues.h>
#include <hybrid/__atomic.h>
#include <hybrid/sched/__yield.h>
#include <asm/os/errno.h>
#include <kos/asm/futex.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(pthread_once) __ATTR_INOUT(1) __ATTR_NONNULL((2)) __errno_t
(__LIBCCALL __LIBC_LOCAL_NAME(pthread_once))(__pthread_once_t *__once_control, void (__LIBCCALL *__init_routine)(void)) __THROWS(...) {
#undef __PRIVATE_PTHREAD_ONCE_USES_FUTEX
#if defined(__CRT_HAVE_futex_wakeall) || defined(__CRT_HAVE_futex_wake) || defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#if __SIZEOF_PTHREAD_ONCE_T == __SIZEOF_POINTER__ && (defined(__CRT_HAVE_futex_waitwhile) || defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex))
#define __PRIVATE_PTHREAD_ONCE_USES_FUTEX
#elif (defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)) && defined(LFUTEX_WAIT_WHILE_EX)
#define __PRIVATE_PTHREAD_ONCE_USES_FUTEX
#endif /* ... */
#endif /* __CRT_HAVE_futex_wakeall || __CRT_HAVE_futex_wake || __CRT_HAVE_lfutex64 || __CRT_HAVE_lfutex */

	/*
	 * Internal state values for pthread_once():
	 *  - __PTHREAD_ONCE_INIT + 0: Not yet called
	 *  - __PTHREAD_ONCE_INIT + 1: Currently being called
	 *  - __PTHREAD_ONCE_INIT + 2: Was called
	 * #ifdef __PRIVATE_PTHREAD_ONCE_USES_FUTEX
	 *  - __PTHREAD_ONCE_INIT + 3: Currently being called, and other threads are waiting
	 * #endif
	 *
	 */
	__pthread_once_t __status;
__again:
	__status = __hybrid_atomic_cmpxch_val(__once_control,
	                                    __PTHREAD_ONCE_INIT,
	                                    __PTHREAD_ONCE_INIT + 1,
	                                    __ATOMIC_SEQ_CST,
	                                    __ATOMIC_SEQ_CST);
	if (__status == __PTHREAD_ONCE_INIT) {
		/* To comply with POSIX, we  must be able to roll-back  our
		 * initialization when `init_routine' "cancels" our thread. */
#ifdef __cplusplus
		try {
			(*__init_routine)();
		} catch (...) {
			/* roll-back... */
#ifdef __PRIVATE_PTHREAD_ONCE_USES_FUTEX
			if (__hybrid_atomic_xch(__once_control, __PTHREAD_ONCE_INIT,
			                        __ATOMIC_RELEASE) == __PTHREAD_ONCE_INIT + 3)
				(__NAMESPACE_LOCAL_SYM __localdep_futex_wakeall)((__uintptr_t *)__once_control);
#else /* __PRIVATE_PTHREAD_ONCE_USES_FUTEX */
			__hybrid_atomic_store(__once_control,
			                      __PTHREAD_ONCE_INIT,
			                      __ATOMIC_RELEASE);
#endif /* !__PRIVATE_PTHREAD_ONCE_USES_FUTEX */
#ifdef __CRT_HAVE_except_rethrow
			(__NAMESPACE_LOCAL_SYM __localdep_except_rethrow)();
#else /* __CRT_HAVE_except_rethrow */
			throw;
#endif /* !__CRT_HAVE_except_rethrow */
		}
#else /* __cplusplus */
		(*__init_routine)();
#endif /* !__cplusplus */

		/* Remember that the function was called. */
#if defined(__PRIVATE_PTHREAD_ONCE_USES_FUTEX) && (defined(__CRT_HAVE_futex_wakeall) || defined(__CRT_HAVE_futex_wake) || defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex))
		if (__hybrid_atomic_xch(__once_control, __PTHREAD_ONCE_INIT + 2,
		                        __ATOMIC_RELEASE) == __PTHREAD_ONCE_INIT + 3)
			(__NAMESPACE_LOCAL_SYM __localdep_futex_wakeall)((__uintptr_t *)__once_control);
#else /* __PRIVATE_PTHREAD_ONCE_USES_FUTEX && (__CRT_HAVE_futex_wakeall || __CRT_HAVE_futex_wake || __CRT_HAVE_lfutex64 || __CRT_HAVE_lfutex) */
		__hybrid_atomic_store(__once_control,
		                      __PTHREAD_ONCE_INIT + 2,
		                      __ATOMIC_RELEASE);
#endif /* !__PRIVATE_PTHREAD_ONCE_USES_FUTEX || (!__CRT_HAVE_futex_wakeall && !__CRT_HAVE_futex_wake && !__CRT_HAVE_lfutex64 && !__CRT_HAVE_lfutex) */
	} else if (__status != __PTHREAD_ONCE_INIT + 2) {
#ifdef __PRIVATE_PTHREAD_ONCE_USES_FUTEX
		if __unlikely(__status != __PTHREAD_ONCE_INIT + 1 &&
		            __status != __PTHREAD_ONCE_INIT + 3)
#else /* __PRIVATE_PTHREAD_ONCE_USES_FUTEX */
		if __unlikely(__status != __PTHREAD_ONCE_INIT + 1)
#endif /* !__PRIVATE_PTHREAD_ONCE_USES_FUTEX */
		{
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
#ifdef __PRIVATE_PTHREAD_ONCE_USES_FUTEX
		if (__status == __PTHREAD_ONCE_INIT + 1) {
			/* Request a futex-wake call once initialization
			 * completes  in  whatever thread  is  doing it. */
			if (!__hybrid_atomic_cmpxch(__once_control,
			                            __PTHREAD_ONCE_INIT + 1,
			                            __PTHREAD_ONCE_INIT + 3,
			                            __ATOMIC_SEQ_CST,
			                            __ATOMIC_SEQ_CST))
				goto __again;
		}
#if __SIZEOF_PTHREAD_ONCE_T == __SIZEOF_POINTER__ && (defined(__CRT_HAVE_futex_waitwhile) || defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex))
		(__NAMESPACE_LOCAL_SYM __localdep_futex_waitwhile)((__uintptr_t *)__once_control, __PTHREAD_ONCE_INIT + 3);
#else /* __SIZEOF_PTHREAD_ONCE_T == __SIZEOF_POINTER__ && (__CRT_HAVE_futex_waitwhile || __CRT_HAVE_lfutex64 || __CRT_HAVE_lfutex) */
		{
			static __pthread_once_t const ___init_marker = __PTHREAD_ONCE_INIT + 3;
			(__NAMESPACE_LOCAL_SYM __localdep_lfutex64)((__uintptr_t *)__once_control, LFUTEX_WAIT_WHILE_EX,
			         (__uintptr_t)&___init_marker, (struct __timespec64 const *)__NULLPTR,
			         sizeof(__pthread_once_t));
		}
#endif /* __SIZEOF_PTHREAD_ONCE_T != __SIZEOF_POINTER__ || (!__CRT_HAVE_futex_waitwhile && !__CRT_HAVE_lfutex64 && !__CRT_HAVE_lfutex) */
#else /* __PRIVATE_PTHREAD_ONCE_USES_FUTEX */
		do {
			__hybrid_yield();
		} while (__hybrid_atomic_load(__once_control, __ATOMIC_ACQUIRE) ==
		         __PTHREAD_ONCE_INIT + 1);
#endif /* !__PRIVATE_PTHREAD_ONCE_USES_FUTEX */

		/* Must re-check the once-status, since another thread may have
		 * rolled back completion  in case its  call to  `init_routine'
		 * resulted in an exception being called. (or to speak in terms
		 * of POSIX, caused its thread to be "canceled") */
		goto __again;
	}
	return 0;
#undef __PRIVATE_PTHREAD_ONCE_USES_FUTEX
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_once_defined
#define __local___localdep_pthread_once_defined
#define __localdep_pthread_once __LIBC_LOCAL_NAME(pthread_once)
#endif /* !__local___localdep_pthread_once_defined */
#endif /* !__local_pthread_once_defined */
