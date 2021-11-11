/* HASH CRC-32:0x9f9c0e56 */
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
#ifndef __local_shared_lock_waitfor_with_timeout_defined
#define __local_shared_lock_waitfor_with_timeout_defined
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
#if defined(__KERNEL__) || (defined(__CRT_HAVE_LFutexExpr) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE_LFutexExpr64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__CRT_HAVE_lfutexexpr64) || defined(__CRT_HAVE_lfutexexpr)
#include <kos/anno.h>
#include <kos/bits/shared-lock.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_LFutexExpr_except_defined
#define __local___localdep_LFutexExpr_except_defined
#if defined(__CRT_HAVE_LFutexExpr) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <kos/bits/futex-expr.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 4)),int,__THROWING,__localdep_LFutexExpr_except,(__uintptr_t *__ulockaddr, void *__base, __SIZE_TYPE__ __exprc, struct lfutexexpr const *__exprv, struct timespec const *__timeout, unsigned int __timeout_flags),LFutexExpr,(__ulockaddr,__base,__exprc,__exprv,__timeout,__timeout_flags))
#elif defined(__CRT_HAVE_LFutexExpr64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <kos/bits/futex-expr.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 4)),int,__THROWING,__localdep_LFutexExpr_except,(__uintptr_t *__ulockaddr, void *__base, __SIZE_TYPE__ __exprc, struct lfutexexpr const *__exprv, struct timespec const *__timeout, unsigned int __timeout_flags),LFutexExpr64,(__ulockaddr,__base,__exprc,__exprv,__timeout,__timeout_flags))
#elif defined(__CRT_HAVE_lfutexexpr64) || defined(__CRT_HAVE_lfutexexpr)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.futexexpr/LFutexExpr_except.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_LFutexExpr_except __LIBC_LOCAL_NAME(LFutexExpr_except)
#else /* ... */
#undef __local___localdep_LFutexExpr_except_defined
#endif /* !... */
#endif /* !__local___localdep_LFutexExpr_except_defined */
__NAMESPACE_LOCAL_END
#ifdef __KERNEL__
#include <hybrid/__assert.h>
#include <sched/signal.h>
#else /* __KERNEL__ */
#include <kos/syscalls.h>
#include <kos/bits/futex.h>
#include <kos/bits/futex-expr.h>
#ifndef __SHARED_LOCK_WAITEXPR_DEFINED
#define __SHARED_LOCK_WAITEXPR_DEFINED
__NAMESPACE_LOCAL_BEGIN
static struct lfutexexpr const __shared_lock_waitexpr[] = {
	/* Wait until `sl_lock == 0' */
	LFUTEXEXPR_INIT(__builtin_offsetof(struct shared_lock, sl_lock), LFUTEX_WAIT_UNTIL, 0, 0)
};
__NAMESPACE_LOCAL_END
#endif /* !__SHARED_LOCK_WAITEXPR_DEFINED */

#endif /* !__KERNEL__ */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(shared_lock_waitfor_with_timeout) __ATTR_WUNUSED __BLOCKING __NOCONNECT __ATTR_NONNULL((1)) __BOOL
(__FCALL __LIBC_LOCAL_NAME(shared_lock_waitfor_with_timeout))(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
#ifdef __KERNEL__
	__hybrid_assert(!task_wasconnected());
	while (__hybrid_atomic_load(__self->sl_lock, __ATOMIC_ACQUIRE) != 0) {
		TASK_POLL_BEFORE_CONNECT({
			if (__hybrid_atomic_load(__self->sl_lock, __ATOMIC_ACQUIRE) == 0)
				goto __success;
		});
		task_connect(&__self->sl_sig);
		if __unlikely(__hybrid_atomic_load(__self->sl_lock, __ATOMIC_ACQUIRE) == 0) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor(__abs_timeout))
			return 0;
	}
__success:
#else /* __KERNEL__ */
	while (__hybrid_atomic_load(__self->sl_lock, __ATOMIC_ACQUIRE) != 0) {
		__hybrid_atomic_store(__self->sl_sig, 1, __ATOMIC_SEQ_CST);
		if ((__NAMESPACE_LOCAL_SYM __localdep_LFutexExpr_except)(&__self->sl_sig, __self, 1,
		                      __NAMESPACE_LOCAL_SYM __shared_lock_waitexpr,
		                      __abs_timeout, LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE) < 0)
			return 0;
	}
#endif /* !__KERNEL__ */
	return 1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_shared_lock_waitfor_with_timeout_defined
#define __local___localdep_shared_lock_waitfor_with_timeout_defined
#define __localdep_shared_lock_waitfor_with_timeout __LIBC_LOCAL_NAME(shared_lock_waitfor_with_timeout)
#endif /* !__local___localdep_shared_lock_waitfor_with_timeout_defined */
#else /* __KERNEL__ || (__CRT_HAVE_LFutexExpr && (!__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CRT_HAVE_LFutexExpr64 && (__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || __CRT_HAVE_lfutexexpr64 || __CRT_HAVE_lfutexexpr */
#undef __local_shared_lock_waitfor_with_timeout_defined
#endif /* !__KERNEL__ && (!__CRT_HAVE_LFutexExpr || (__USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__)) && (!__CRT_HAVE_LFutexExpr64 || (!__USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__)) && !__CRT_HAVE_lfutexexpr64 && !__CRT_HAVE_lfutexexpr */
#endif /* !__local_shared_lock_waitfor_with_timeout_defined */
