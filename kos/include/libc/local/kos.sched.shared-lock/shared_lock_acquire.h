/* HASH CRC-32:0x7c5bf1b6 */
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
#ifndef __local_shared_lock_acquire_defined
#define __local_shared_lock_acquire_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)
#include <kos/anno.h>
#include <kos/bits/shared-lock.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_LFutexExpr64_except_defined
#define __local___localdep_LFutexExpr64_except_defined
#if defined(__CRT_HAVE_LFutexExpr) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <bits/os/timespec.h>
#include <kos/bits/futex-expr.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 3)),int,__THROWING,__localdep_LFutexExpr64_except,(__uintptr_t *__ulockaddr, void *__base, struct lfutexexpr const *__expr, struct __timespec64 const *__timeout, unsigned int __timeout_flags),LFutexExpr,(__ulockaddr,__base,__expr,__timeout,__timeout_flags))
#elif defined(__CRT_HAVE_LFutexExpr64)
__NAMESPACE_LOCAL_END
#include <bits/os/timespec.h>
#include <kos/bits/futex-expr.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 3)),int,__THROWING,__localdep_LFutexExpr64_except,(__uintptr_t *__ulockaddr, void *__base, struct lfutexexpr const *__expr, struct __timespec64 const *__timeout, unsigned int __timeout_flags),LFutexExpr64,(__ulockaddr,__base,__expr,__timeout,__timeout_flags))
#elif defined(__CRT_HAVE_LFutexExpr)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.futexexpr/LFutexExpr64_except.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_LFutexExpr64_except __LIBC_LOCAL_NAME(LFutexExpr64_except)
#else /* ... */
#undef __local___localdep_LFutexExpr64_except_defined
#endif /* !... */
#endif /* !__local___localdep_LFutexExpr64_except_defined */
__NAMESPACE_LOCAL_END
#ifdef __KERNEL__
#include <hybrid/__assert.h>
#include <sched/signal.h>
#else /* __KERNEL__ */
#include <kos/syscalls.h>
#include <kos/asm/futex.h>
#include <kos/bits/futex-expr.h>
#ifndef __SHARED_LOCK_WAITEXPR_DEFINED
#define __SHARED_LOCK_WAITEXPR_DEFINED
__NAMESPACE_LOCAL_BEGIN
static struct lfutexexpr const __shared_lock_waitexpr[] = {
	/* Wait until `sl_lock == 0' */
	LFUTEXEXPR_INIT(__builtin_offsetof(struct shared_lock, sl_lock), LFUTEX_WAIT_UNTIL, 0, 0),
	LFUTEXEXPR_INIT(0, LFUTEX_EXPREND, 0, 0)
};
__NAMESPACE_LOCAL_END
#endif /* !__SHARED_LOCK_WAITEXPR_DEFINED */

#endif /* !__KERNEL__ */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(shared_lock_acquire) __BLOCKING __NOCONNECT __ATTR_NONNULL((1)) void
(__FCALL __LIBC_LOCAL_NAME(shared_lock_acquire))(struct shared_lock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) {
#ifdef __KERNEL__
	__hybrid_assert(!task_wasconnected());
	while (__hybrid_atomic_xch(__self->sl_lock, 1, __ATOMIC_ACQUIRE) != 0) {
		TASK_POLL_BEFORE_CONNECT({
			if (__hybrid_atomic_xch(__self->sl_lock, 1, __ATOMIC_ACQUIRE) == 0)
				goto __success;
		});
		task_connect(&__self->sl_sig);
		if __unlikely(__hybrid_atomic_xch(__self->sl_lock, 1, __ATOMIC_ACQUIRE) == 0) {
			task_disconnectall();
			break;
		}
		task_waitfor(KTIME_INFINITE);
	}
__success:
#else /* __KERNEL__ */
	while (__hybrid_atomic_xch(__self->sl_lock, 1, __ATOMIC_ACQUIRE) != 0) {
		__hybrid_atomic_store(__self->sl_sig, 1, __ATOMIC_SEQ_CST);
		(__NAMESPACE_LOCAL_SYM __localdep_LFutexExpr64_except)(&__self->sl_sig, __self, __NAMESPACE_LOCAL_SYM __shared_lock_waitexpr, __NULLPTR, 0);
	}
#endif /* !__KERNEL__ */
	__COMPILER_BARRIER();
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_shared_lock_acquire_defined
#define __local___localdep_shared_lock_acquire_defined
#define __localdep_shared_lock_acquire __LIBC_LOCAL_NAME(shared_lock_acquire)
#endif /* !__local___localdep_shared_lock_acquire_defined */
#else /* __KERNEL__ || __CRT_HAVE_LFutexExpr64 || __CRT_HAVE_LFutexExpr */
#undef __local_shared_lock_acquire_defined
#endif /* !__KERNEL__ && !__CRT_HAVE_LFutexExpr64 && !__CRT_HAVE_LFutexExpr */
#endif /* !__local_shared_lock_acquire_defined */
