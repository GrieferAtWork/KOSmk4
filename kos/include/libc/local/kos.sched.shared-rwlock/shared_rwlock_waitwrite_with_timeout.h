/* HASH CRC-32:0x51dfa395 */
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
#ifndef __local_shared_rwlock_waitwrite_with_timeout_defined
#define __local_shared_rwlock_waitwrite_with_timeout_defined
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
#if defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
#include <kos/anno.h>
#include <kos/bits/shared-rwlock.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_LFutexExprI_except_defined
#define __local___localdep_LFutexExprI_except_defined
#if defined(__CRT_HAVE_LFutexExprI) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/timespec.h>
#include <kos/bits/futex-expr.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(3) __ATTR_IN_OPT(4) __ATTR_NONNULL((1)),int,__THROWING(...),__localdep_LFutexExprI_except,(__uintptr_t *__ulockaddr, void *__base, struct lfutexexpr const *__expr, struct timespec const *__timeout, unsigned int __timeout_flags),LFutexExprI,(__ulockaddr,__base,__expr,__timeout,__timeout_flags))
#elif defined(__CRT_HAVE_LFutexExprI64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/timespec.h>
#include <kos/bits/futex-expr.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(3) __ATTR_IN_OPT(4) __ATTR_NONNULL((1)),int,__THROWING(...),__localdep_LFutexExprI_except,(__uintptr_t *__ulockaddr, void *__base, struct lfutexexpr const *__expr, struct timespec const *__timeout, unsigned int __timeout_flags),LFutexExprI64,(__ulockaddr,__base,__expr,__timeout,__timeout_flags))
#elif defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.futexexpr/LFutexExprI_except.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_LFutexExprI_except __LIBC_LOCAL_NAME(LFutexExprI_except)
#else /* ... */
#undef __local___localdep_LFutexExprI_except_defined
#endif /* !... */
#endif /* !__local___localdep_LFutexExprI_except_defined */
__NAMESPACE_LOCAL_END
#ifdef __KERNEL__
#include <hybrid/__assert.h>
#include <sched/sig.h>
#else /* __KERNEL__ */
#include <kos/syscalls.h>
#include <kos/asm/futex.h>
#include <kos/bits/futex-expr.h>
#ifndef __SHARED_RWLOCK_WAITWRITEEXPR_DEFINED
#define __SHARED_RWLOCK_WAITWRITEEXPR_DEFINED
__NAMESPACE_LOCAL_BEGIN
static struct lfutexexpr const __shared_rwlock_waitwriteexpr[] = {
	/* Wait until `sl_lock == 0' */
	LFUTEXEXPR_INIT(__builtin_offsetof(struct shared_rwlock, sl_lock), LFUTEX_WAIT_UNTIL, 0, 0),
	LFUTEXEXPR_INIT(0, LFUTEX_EXPREND, 0, 0)
};
__NAMESPACE_LOCAL_END
#endif /* !__SHARED_RWLOCK_WAITWRITEEXPR_DEFINED */

#endif /* !__KERNEL__ */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(shared_rwlock_waitwrite_with_timeout) __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL
(__FCALL __LIBC_LOCAL_NAME(shared_rwlock_waitwrite_with_timeout))(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(E_WOULDBLOCK, ...) {
#ifdef __KERNEL__
	__hybrid_assert(!task_wasconnected());
	while (__hybrid_atomic_load(&__self->sl_lock, __ATOMIC_ACQUIRE) != 0) {
		TASK_POLL_BEFORE_CONNECT({
			if (__hybrid_atomic_load(&__self->sl_lock, __ATOMIC_ACQUIRE) == 0)
				goto __success;
		});
		task_connect_for_poll(&__self->sl_wrwait);
		if __unlikely(__hybrid_atomic_load(&__self->sl_lock, __ATOMIC_ACQUIRE) == 0) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor(__abs_timeout))
			return 0;
	}
__success:
#else /* __KERNEL__ */
	while (__hybrid_atomic_load(&__self->sl_lock, __ATOMIC_ACQUIRE) != 0) {
		__hybrid_atomic_store(&__self->sl_wrwait, 1, __ATOMIC_SEQ_CST);
		if ((__NAMESPACE_LOCAL_SYM __localdep_LFutexExprI_except)(&__self->sl_wrwait, __self,
		                       __NAMESPACE_LOCAL_SYM __shared_rwlock_waitwriteexpr,
		                       __abs_timeout,
		                       LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE |
		                       LFUTEX_WAIT_FLAG_TIMEOUT_FORPOLL) < 0)
			return 0;
	}
#endif /* !__KERNEL__ */
	__COMPILER_BARRIER();
	return 1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_shared_rwlock_waitwrite_with_timeout_defined
#define __local___localdep_shared_rwlock_waitwrite_with_timeout_defined
#define __localdep_shared_rwlock_waitwrite_with_timeout __LIBC_LOCAL_NAME(shared_rwlock_waitwrite_with_timeout)
#endif /* !__local___localdep_shared_rwlock_waitwrite_with_timeout_defined */
#else /* __KERNEL__ || __CRT_HAVE_LFutexExprI || __CRT_HAVE_LFutexExprI64 || (__cplusplus && __KOS__ && (__CRT_HAVE_LFutexExpr || __CRT_HAVE_LFutexExpr64)) */
#undef __local_shared_rwlock_waitwrite_with_timeout_defined
#endif /* !__KERNEL__ && !__CRT_HAVE_LFutexExprI && !__CRT_HAVE_LFutexExprI64 && (!__cplusplus || !__KOS__ || (!__CRT_HAVE_LFutexExpr && !__CRT_HAVE_LFutexExpr64)) */
#endif /* !__local_shared_rwlock_waitwrite_with_timeout_defined */
