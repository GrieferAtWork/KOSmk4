/* HASH CRC-32:0x3cd11fe1 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_KOS_SCHED_SHARED_RWLOCK_C
#define GUARD_LIBC_AUTO_KOS_SCHED_SHARED_RWLOCK_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "kos.sched.shared-rwlock.h"
#include "../user/kos.futexexpr.h"

DECL_BEGIN

#include <hybrid/__atomic.h>
/* >> shared_rwlock_tryread(3)
 * Try to acquire a read-lock to `self' */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __NOBLOCK ATTR_INOUT(1) bool
NOTHROW(__FCALL libc_shared_rwlock_tryread)(struct shared_rwlock *__restrict self) {
	uintptr_t temp;
	__COMPILER_WORKAROUND_GCC_105689(self);
	do {
		temp = __hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE);
		if (temp == (uintptr_t)-1)
			return false;
		__hybrid_assert(temp != (uintptr_t)-2);
	} while (!__hybrid_atomic_cmpxch_weak(&self->sl_lock, temp, temp + 1,
	                                      __ATOMIC_ACQUIRE, __ATOMIC_RELAXED));
	__COMPILER_READ_BARRIER();
	return true;
}
/* >> shared_rwlock_trywrite(3)
 * Try to acquire a write-lock to `self' */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __NOBLOCK ATTR_INOUT(1) bool
NOTHROW(__FCALL libc_shared_rwlock_trywrite)(struct shared_rwlock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (!__hybrid_atomic_cmpxch(&self->sl_lock, 0, (uintptr_t)-1,
	                            __ATOMIC_ACQUIRE, __ATOMIC_RELAXED))
		return false;
	__COMPILER_BARRIER();
	return true;
}
#include <hybrid/__assert.h>
#include <kos/asm/futex.h>
/* >> shared_rwlock_endwrite(3)
 * Release a write-lock from `self' */
INTERN ATTR_SECTION(".text.crt.sched.futex") __NOBLOCK ATTR_INOUT(1) void
NOTHROW(__FCALL libc_shared_rwlock_endwrite)(struct shared_rwlock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	__COMPILER_BARRIER();
	__hybrid_assertf(self->sl_lock == (uintptr_t)-1, "Lock isn't in write-mode (%x)", self->sl_lock);
	__hybrid_atomic_store(&self->sl_lock, 0, __ATOMIC_RELEASE);
	if (!__shared_rwlock_wrwait_send(self))
		__shared_rwlock_rdwait_broadcast(self);
}
/* >> shared_rwlock_endread(3)
 * Release a read-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
INTERN ATTR_SECTION(".text.crt.sched.futex") __NOBLOCK ATTR_INOUT(1) bool
NOTHROW(__FCALL libc_shared_rwlock_endread)(struct shared_rwlock *__restrict self) {
	uintptr_t __result;
	__COMPILER_WORKAROUND_GCC_105689(self);
	__COMPILER_READ_BARRIER();
	__hybrid_assertf(self->sl_lock != (uintptr_t)-1, "Lock is in write-mode (%x)", self->sl_lock);
	__hybrid_assertf(self->sl_lock != 0, "Lock isn't held by anyone");
	__result = __hybrid_atomic_decfetch(&self->sl_lock, __ATOMIC_RELEASE);
	if (__result == 0)
		__shared_rwlock_wrwait_send(self);
	return __result == 0;
}
/* >> shared_rwlock_end(3)
 * Release a read- or write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
INTERN ATTR_SECTION(".text.crt.sched.futex") __NOBLOCK ATTR_INOUT(1) bool
NOTHROW(__FCALL libc_shared_rwlock_end)(struct shared_rwlock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	__COMPILER_BARRIER();
	if (self->sl_lock != (uintptr_t)-1) {
		/* Read-lock */
		uintptr_t __result;
		__hybrid_assertf(self->sl_lock != 0, "No remaining read-locks");
		__result = __hybrid_atomic_decfetch(&self->sl_lock, __ATOMIC_RELEASE);
		if (__result == 0)
			__shared_rwlock_wrwait_send(self);
		return __result == 0;
	}
	/* Write-lock */
	__hybrid_atomic_store(&self->sl_lock, 0, __ATOMIC_RELEASE);
	if (!__shared_rwlock_wrwait_send(self))
		__shared_rwlock_rdwait_broadcast(self);
	return true;
}
/* >> shared_rwlock_downgrade(3)
 * Downgrade a write-lock to a read-lock (Always succeeds). */
INTERN ATTR_SECTION(".text.crt.sched.futex") __NOBLOCK ATTR_INOUT(1) void
NOTHROW(__FCALL libc_shared_rwlock_downgrade)(struct shared_rwlock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	__COMPILER_WRITE_BARRIER();
	__hybrid_assertf(self->sl_lock == (uintptr_t)-1, "Lock isn't in write-mode (%x)", self->sl_lock);
	__hybrid_atomic_store(&self->sl_lock, 1, __ATOMIC_RELEASE);
	__shared_rwlock_rdwait_broadcast(self); /* Allow for more readers. */
}
/* >> shared_rwlock_upgrade(3)
 * Blocking-upgrade a read-lock into a write-lock
 * NOTE: The lock is always upgraded, but when `false' is returned, no lock
 *       may  have been  held temporarily,  meaning that  the caller should
 *       re-load local copies of affected resources.
 * @return: true:  Upgrade was performed without the read-lock being lost
 * @return: false: The read-lock had to be released before a write-lock was acquired */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_rwlock_upgrade)(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__hybrid_atomic_cmpxch(&self->sl_lock, 1, (uintptr_t)-1, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED))
		return true; /* Lock wasn't lost */
	libc_shared_rwlock_endread(self);
	libc_shared_rwlock_write(self);
	return false; /* Lock was (temporarily) lost */
}
#ifdef __KERNEL__
#include <hybrid/__assert.h>
#include <sched/sig.h>
#else /* __KERNEL__ */
#include <kos/syscalls.h>
#include <kos/asm/futex.h>
#include <kos/bits/futex-expr.h>
#ifndef __SHARED_RWLOCK_WAITREADEXPR_DEFINED
#define __SHARED_RWLOCK_WAITREADEXPR_DEFINED
__NAMESPACE_LOCAL_BEGIN
static struct lfutexexpr const __shared_rwlock_waitreadexpr[] = {
	/* Wait while `sl_lock == (uintptr_t)-1' */
	LFUTEXEXPR_INIT(offsetof(struct shared_rwlock, sl_lock), LFUTEX_WAIT_WHILE, (uintptr_t)-1, 0),
	LFUTEXEXPR_INIT(0, LFUTEX_EXPREND, 0, 0)
};
__NAMESPACE_LOCAL_END
#endif /* !__SHARED_RWLOCK_WAITREADEXPR_DEFINED */

#endif /* !__KERNEL__ */
/* >> shared_rwlock_read(3)
 * Acquire a read-lock to the given shared_rwlock. */
INTERN ATTR_SECTION(".text.crt.sched.futex") __BLOCKING ATTR_INOUT(1) void
(__FCALL libc_shared_rwlock_read)(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...) {
#ifdef __KERNEL__
	__hybrid_assert(!task_wasconnected());
	while (!libc_shared_rwlock_tryread(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (libc_shared_rwlock_tryread(self))
				goto success;
		});
		task_connect(&self->sl_rdwait);
		if unlikely(libc_shared_rwlock_tryread(self)) {
			task_disconnectall();
			break;
		}
		task_waitfor(KTIME_INFINITE);
	}
success:
#else /* __KERNEL__ */
	while (!libc_shared_rwlock_tryread(self)) {
		__hybrid_atomic_store(&self->sl_rdwait, 1, __ATOMIC_SEQ_CST);
		libc_LFutexExprI64(&self->sl_rdwait, self,
		                     __NAMESPACE_LOCAL_SYM __shared_rwlock_waitreadexpr,
		                     NULL, 0);
	}
#endif /* !__KERNEL__ */
	COMPILER_READ_BARRIER();
}
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
	LFUTEXEXPR_INIT(offsetof(struct shared_rwlock, sl_lock), LFUTEX_WAIT_UNTIL, 0, 0),
	LFUTEXEXPR_INIT(0, LFUTEX_EXPREND, 0, 0)
};
__NAMESPACE_LOCAL_END
#endif /* !__SHARED_RWLOCK_WAITWRITEEXPR_DEFINED */

#endif /* !__KERNEL__ */
/* >> shared_rwlock_write(3)
 * Acquire a write-lock to the given shared_rwlock. */
INTERN ATTR_SECTION(".text.crt.sched.futex") __BLOCKING ATTR_INOUT(1) void
(__FCALL libc_shared_rwlock_write)(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...) {
#ifdef __KERNEL__
	__hybrid_assert(!task_wasconnected());
	while (!libc_shared_rwlock_trywrite(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (libc_shared_rwlock_trywrite(self))
				goto success;
		});
		task_connect(&self->sl_wrwait);
		if unlikely(libc_shared_rwlock_trywrite(self)) {
			task_disconnectall();
			break;
		}
		task_waitfor(KTIME_INFINITE);
	}
success:
#else /* __KERNEL__ */
	while (!libc_shared_rwlock_trywrite(self)) {
		__hybrid_atomic_store(&self->sl_wrwait, 1, __ATOMIC_SEQ_CST);
		libc_LFutexExprI64(&self->sl_wrwait, self,
		                     __NAMESPACE_LOCAL_SYM __shared_rwlock_waitwriteexpr,
		                     NULL, 0);
	}
#endif /* !__KERNEL__ */
	COMPILER_BARRIER();
}
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_rwlock_read_with_timeout)(struct shared_rwlock *__restrict self,
                                               __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...) {
#ifdef __KERNEL__
	__hybrid_assert(!task_wasconnected());
	while (!libc_shared_rwlock_tryread(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (libc_shared_rwlock_tryread(self))
				goto success;
		});
		task_connect(&self->sl_rdwait);
		if unlikely(libc_shared_rwlock_tryread(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor(abs_timeout))
			return false;
	}
success:
#else /* __KERNEL__ */
	while (!libc_shared_rwlock_tryread(self)) {
		__hybrid_atomic_store(&self->sl_rdwait, 1, __ATOMIC_SEQ_CST);
		if (libc_LFutexExprI(&self->sl_rdwait, self,
		                       __NAMESPACE_LOCAL_SYM __shared_rwlock_waitreadexpr,
		                       abs_timeout, 0) < 0)
			return false;
	}
#endif /* !__KERNEL__ */
	COMPILER_READ_BARRIER();
	return true;
}
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_rwlock_write_with_timeout)(struct shared_rwlock *__restrict self,
                                                __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...) {
#ifdef __KERNEL__
	__hybrid_assert(!task_wasconnected());
	while (!libc_shared_rwlock_trywrite(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (libc_shared_rwlock_trywrite(self))
				goto success;
		});
		task_connect(&self->sl_wrwait);
		if unlikely(libc_shared_rwlock_trywrite(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor(abs_timeout))
			return false;
	}
success:
#else /* __KERNEL__ */
	while (!libc_shared_rwlock_trywrite(self)) {
		__hybrid_atomic_store(&self->sl_wrwait, 1, __ATOMIC_SEQ_CST);
		if (libc_LFutexExprI(&self->sl_wrwait, self,
		                       __NAMESPACE_LOCAL_SYM __shared_rwlock_waitwriteexpr,
		                       abs_timeout, LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE) < 0)
			return false;
	}
#endif /* !__KERNEL__ */
	COMPILER_BARRIER();
	return true;
}
/* >> shared_rwlock_waitread(3)
 * Wait until acquiring a read-lock to `self' no longer blocks */
INTERN ATTR_SECTION(".text.crt.sched.futex") __BLOCKING ATTR_INOUT(1) void
(__FCALL libc_shared_rwlock_waitread)(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...) {
#ifdef __KERNEL__
	__hybrid_assert(!task_wasconnected());
	while (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == (uintptr_t)-1) {
		TASK_POLL_BEFORE_CONNECT({
			if (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) != (uintptr_t)-1)
				goto success;
		});
		task_connect_for_poll(&self->sl_rdwait);
		if unlikely(__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) != (uintptr_t)-1) {
			task_disconnectall();
			break;
		}
		task_waitfor(KTIME_INFINITE);
	}
success:
#else /* __KERNEL__ */
	while (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == (uintptr_t)-1) {
		__hybrid_atomic_store(&self->sl_rdwait, 1, __ATOMIC_SEQ_CST);
		libc_LFutexExprI64(&self->sl_rdwait, self, __NAMESPACE_LOCAL_SYM __shared_rwlock_waitreadexpr,
		                     NULL, LFUTEX_WAIT_FLAG_TIMEOUT_FORPOLL);
	}
#endif /* !__KERNEL__ */
	COMPILER_READ_BARRIER();
}
/* >> shared_rwlock_waitwrite(3)
 * Wait until acquiring a write-lock to `self' no longer blocks */
INTERN ATTR_SECTION(".text.crt.sched.futex") __BLOCKING ATTR_INOUT(1) void
(__FCALL libc_shared_rwlock_waitwrite)(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...) {
#ifdef __KERNEL__
	__hybrid_assert(!task_wasconnected());
	while (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) != 0) {
		TASK_POLL_BEFORE_CONNECT({
			if (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == 0)
				goto success;
		});
		task_connect_for_poll(&self->sl_wrwait);
		if unlikely(__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == 0) {
			task_disconnectall();
			break;
		}
		task_waitfor(KTIME_INFINITE);
	}
success:
#else /* __KERNEL__ */
	while (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) != 0) {
		__hybrid_atomic_store(&self->sl_wrwait, 1, __ATOMIC_SEQ_CST);
		libc_LFutexExprI64(&self->sl_wrwait, self, __NAMESPACE_LOCAL_SYM __shared_rwlock_waitwriteexpr,
		                     NULL, LFUTEX_WAIT_FLAG_TIMEOUT_FORPOLL);
	}
#endif /* !__KERNEL__ */
	COMPILER_BARRIER();
}
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_rwlock_waitread_with_timeout)(struct shared_rwlock *__restrict self,
                                                   __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...) {
#ifdef __KERNEL__
	__hybrid_assert(!task_wasconnected());
	while (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == (uintptr_t)-1) {
		TASK_POLL_BEFORE_CONNECT({
			if (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) != (uintptr_t)-1)
				goto success;
		});
		task_connect_for_poll(&self->sl_rdwait);
		if unlikely(__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) != (uintptr_t)-1) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor(abs_timeout))
			return false;
	}
success:
#else /* __KERNEL__ */
	while (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == (uintptr_t)-1) {
		__hybrid_atomic_store(&self->sl_rdwait, 1, __ATOMIC_SEQ_CST);
		if (libc_LFutexExprI(&self->sl_rdwait, self,
		                       __NAMESPACE_LOCAL_SYM __shared_rwlock_waitreadexpr,
		                       abs_timeout,
		                       LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE |
		                       LFUTEX_WAIT_FLAG_TIMEOUT_FORPOLL) < 0)
			return false;
	}
#endif /* !__KERNEL__ */
	COMPILER_READ_BARRIER();
	return true;
}
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_rwlock_waitwrite_with_timeout)(struct shared_rwlock *__restrict self,
                                                    __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...) {
#ifdef __KERNEL__
	__hybrid_assert(!task_wasconnected());
	while (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) != 0) {
		TASK_POLL_BEFORE_CONNECT({
			if (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == 0)
				goto success;
		});
		task_connect_for_poll(&self->sl_wrwait);
		if unlikely(__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == 0) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor(abs_timeout))
			return false;
	}
success:
#else /* __KERNEL__ */
	while (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) != 0) {
		__hybrid_atomic_store(&self->sl_wrwait, 1, __ATOMIC_SEQ_CST);
		if (libc_LFutexExprI(&self->sl_wrwait, self,
		                       __NAMESPACE_LOCAL_SYM __shared_rwlock_waitwriteexpr,
		                       abs_timeout,
		                       LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE |
		                       LFUTEX_WAIT_FLAG_TIMEOUT_FORPOLL) < 0)
			return false;
	}
#endif /* !__KERNEL__ */
	COMPILER_BARRIER();
	return true;
}
#ifndef __KERNEL__
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS_P(libc_shared_rwlock_read_with_timeout64,libc_shared_rwlock_read_with_timeout,WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2),bool,THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self, struct timespec64 const *abs_timeout),(self,abs_timeout));
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#include <kos/syscalls.h>
#include <kos/asm/futex.h>
#include <kos/bits/futex-expr.h>
#ifndef __SHARED_RWLOCK_WAITREADEXPR_DEFINED
#define __SHARED_RWLOCK_WAITREADEXPR_DEFINED
__NAMESPACE_LOCAL_BEGIN
static struct lfutexexpr const __shared_rwlock_waitreadexpr[] = {
	/* Wait while `sl_lock == (uintptr_t)-1' */
	LFUTEXEXPR_INIT(offsetof(struct shared_rwlock, sl_lock), LFUTEX_WAIT_WHILE, (uintptr_t)-1, 0),
	LFUTEXEXPR_INIT(0, LFUTEX_EXPREND, 0, 0)
};
__NAMESPACE_LOCAL_END
#endif /* !__SHARED_RWLOCK_WAITREADEXPR_DEFINED */
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2) bool
(__FCALL libc_shared_rwlock_read_with_timeout64)(struct shared_rwlock *__restrict self,
                                                 struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	while (!libc_shared_rwlock_tryread(self)) {
		__hybrid_atomic_store(&self->sl_rdwait, 1, __ATOMIC_SEQ_CST);
		if (libc_LFutexExprI64(&self->sl_rdwait, self,
		                         __NAMESPACE_LOCAL_SYM __shared_rwlock_waitreadexpr,
		                         abs_timeout, LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE) < 0)
			return false;
	}
	COMPILER_READ_BARRIER();
	return true;
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS_P(libc_shared_rwlock_write_with_timeout64,libc_shared_rwlock_write_with_timeout,WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2),bool,THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self, struct timespec64 const *abs_timeout),(self,abs_timeout));
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#include <kos/syscalls.h>
#include <kos/asm/futex.h>
#include <kos/bits/futex-expr.h>
#ifndef __SHARED_RWLOCK_WAITWRITEEXPR_DEFINED
#define __SHARED_RWLOCK_WAITWRITEEXPR_DEFINED
__NAMESPACE_LOCAL_BEGIN
static struct lfutexexpr const __shared_rwlock_waitwriteexpr[] = {
	/* Wait until `sl_lock == 0' */
	LFUTEXEXPR_INIT(offsetof(struct shared_rwlock, sl_lock), LFUTEX_WAIT_UNTIL, 0, 0),
	LFUTEXEXPR_INIT(0, LFUTEX_EXPREND, 0, 0)
};
__NAMESPACE_LOCAL_END
#endif /* !__SHARED_RWLOCK_WAITWRITEEXPR_DEFINED */
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2) bool
(__FCALL libc_shared_rwlock_write_with_timeout64)(struct shared_rwlock *__restrict self,
                                                  struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	while (!libc_shared_rwlock_trywrite(self)) {
		__hybrid_atomic_store(&self->sl_wrwait, 1, __ATOMIC_SEQ_CST);
		if (libc_LFutexExprI64(&self->sl_wrwait, self,
		                         __NAMESPACE_LOCAL_SYM __shared_rwlock_waitwriteexpr,
		                         abs_timeout, LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE) < 0)
			return false;
	}
	COMPILER_BARRIER();
	return true;
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS_P(libc_shared_rwlock_waitread_with_timeout64,libc_shared_rwlock_waitread_with_timeout,WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2),bool,THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self, struct timespec64 const *abs_timeout),(self,abs_timeout));
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#include <kos/syscalls.h>
#include <kos/asm/futex.h>
#include <kos/bits/futex-expr.h>
#ifndef __SHARED_RWLOCK_WAITREADEXPR_DEFINED
#define __SHARED_RWLOCK_WAITREADEXPR_DEFINED
__NAMESPACE_LOCAL_BEGIN
static struct lfutexexpr const __shared_rwlock_waitreadexpr[] = {
	/* Wait while `sl_lock == (uintptr_t)-1' */
	LFUTEXEXPR_INIT(offsetof(struct shared_rwlock, sl_lock), LFUTEX_WAIT_WHILE, (uintptr_t)-1, 0),
	LFUTEXEXPR_INIT(0, LFUTEX_EXPREND, 0, 0)
};
__NAMESPACE_LOCAL_END
#endif /* !__SHARED_RWLOCK_WAITREADEXPR_DEFINED */
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2) bool
(__FCALL libc_shared_rwlock_waitread_with_timeout64)(struct shared_rwlock *__restrict self,
                                                     struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	while (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == (uintptr_t)-1) {
		__hybrid_atomic_store(&self->sl_rdwait, 1, __ATOMIC_SEQ_CST);
		if (libc_LFutexExprI64(&self->sl_rdwait, self,
		                         __NAMESPACE_LOCAL_SYM __shared_rwlock_waitreadexpr,
		                         abs_timeout,
		                         LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE |
		                         LFUTEX_WAIT_FLAG_TIMEOUT_FORPOLL) < 0)
			return false;
	}
	COMPILER_READ_BARRIER();
	return true;
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS_P(libc_shared_rwlock_waitwrite_with_timeout64,libc_shared_rwlock_waitwrite_with_timeout,WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2),bool,THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self, struct timespec64 const *abs_timeout),(self,abs_timeout));
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#include <kos/syscalls.h>
#include <kos/asm/futex.h>
#include <kos/bits/futex-expr.h>
#ifndef __SHARED_RWLOCK_WAITWRITEEXPR_DEFINED
#define __SHARED_RWLOCK_WAITWRITEEXPR_DEFINED
__NAMESPACE_LOCAL_BEGIN
static struct lfutexexpr const __shared_rwlock_waitwriteexpr[] = {
	/* Wait until `sl_lock == 0' */
	LFUTEXEXPR_INIT(offsetof(struct shared_rwlock, sl_lock), LFUTEX_WAIT_UNTIL, 0, 0),
	LFUTEXEXPR_INIT(0, LFUTEX_EXPREND, 0, 0)
};
__NAMESPACE_LOCAL_END
#endif /* !__SHARED_RWLOCK_WAITWRITEEXPR_DEFINED */
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2) bool
(__FCALL libc_shared_rwlock_waitwrite_with_timeout64)(struct shared_rwlock *__restrict self,
                                                      struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	while (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) != 0) {
		__hybrid_atomic_store(&self->sl_wrwait, 1, __ATOMIC_SEQ_CST);
		if (libc_LFutexExprI64(&self->sl_wrwait, self,
		                         __NAMESPACE_LOCAL_SYM __shared_rwlock_waitwriteexpr,
		                         abs_timeout,
		                         LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE |
		                         LFUTEX_WAIT_FLAG_TIMEOUT_FORPOLL) < 0)
			return false;
	}
	COMPILER_BARRIER();
	return true;
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* !__KERNEL__ */
#ifdef __KERNEL__
#include <sched/sig.h>
/* >> shared_rwlock_read_nx(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_rwlock_read_nx)(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...) {
	__hybrid_assert(!task_wasconnected());
	while (!libc_shared_rwlock_tryread(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (libc_shared_rwlock_tryread(self))
				goto success;
		});
		task_connect(&self->sl_rdwait);
		if unlikely(libc_shared_rwlock_tryread(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx(KTIME_INFINITE))
			return false;
	}
success:
	COMPILER_READ_BARRIER();
	return true;
}
#include <sched/sig.h>
/* >> shared_rwlock_write_nx(3)
 * Acquire a write-lock to the given shared_rwlock.
 * Acquire  a  lock   to  the  given   shared_lock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_rwlock_write_nx)(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...) {
	__hybrid_assert(!task_wasconnected());
	while (!libc_shared_rwlock_trywrite(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (libc_shared_rwlock_trywrite(self))
				goto success;
		});
		task_connect(&self->sl_wrwait);
		if unlikely(libc_shared_rwlock_trywrite(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx(KTIME_INFINITE))
			return false;
	}
success:
	COMPILER_BARRIER();
	return true;
}
#include <sched/sig.h>
/* >> shared_rwlock_read_with_timeout_nx(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_rwlock_read_with_timeout_nx)(struct shared_rwlock *__restrict self,
                                                  __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	__hybrid_assert(!task_wasconnected());
	while (!libc_shared_rwlock_tryread(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (libc_shared_rwlock_tryread(self))
				goto success;
		});
		task_connect(&self->sl_rdwait);
		if unlikely(libc_shared_rwlock_tryread(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx(abs_timeout))
			return false;
	}
success:
	COMPILER_READ_BARRIER();
	return true;
}
#include <sched/sig.h>
/* >> shared_rwlock_write_with_timeout_nx(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_rwlock_write_with_timeout_nx)(struct shared_rwlock *__restrict self,
                                                   __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	__hybrid_assert(!task_wasconnected());
	while (!libc_shared_rwlock_trywrite(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (libc_shared_rwlock_trywrite(self))
				goto success;
		});
		task_connect(&self->sl_wrwait);
		if unlikely(libc_shared_rwlock_trywrite(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx(abs_timeout))
			return false;
	}
success:
	COMPILER_BARRIER();
	return true;
}
#include <sched/sig.h>
/* >> shared_rwlock_waitread_nx(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_rwlock_waitread_nx)(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...) {
	__hybrid_assert(!task_wasconnected());
	while (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == (uintptr_t)-1) {
		TASK_POLL_BEFORE_CONNECT({
			if (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) != (uintptr_t)-1)
				goto success;
		});
		task_connect_for_poll(&self->sl_rdwait);
		if unlikely(__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) != (uintptr_t)-1) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx(KTIME_INFINITE))
			return false;
	}
success:
	COMPILER_READ_BARRIER();
	return true;
}
#include <sched/sig.h>
/* >> shared_rwlock_waitwrite_nx(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * Acquire a lock to the given shared_lock.
 * @return: true:  A write-lock became available.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_rwlock_waitwrite_nx)(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...) {
	__hybrid_assert(!task_wasconnected());
	while (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) != 0) {
		TASK_POLL_BEFORE_CONNECT({
			if (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == 0)
				goto success;
		});
		task_connect_for_poll(&self->sl_wrwait);
		if unlikely(__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == 0) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx(KTIME_INFINITE))
			return false;
	}
success:
	COMPILER_BARRIER();
	return true;
}
#include <sched/sig.h>
/* >> shared_rwlock_waitread_with_timeout_nx(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_rwlock_waitread_with_timeout_nx)(struct shared_rwlock *__restrict self,
                                                      __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	__hybrid_assert(!task_wasconnected());
	while (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == (uintptr_t)-1) {
		TASK_POLL_BEFORE_CONNECT({
			if (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) != (uintptr_t)-1)
				goto success;
		});
		task_connect_for_poll(&self->sl_rdwait);
		if unlikely(__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) != (uintptr_t)-1) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx(abs_timeout))
			return false;
	}
success:
	COMPILER_READ_BARRIER();
	return true;
}
#include <sched/sig.h>
/* >> shared_rwlock_waitwrite_with_timeout_nx(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_rwlock_waitwrite_with_timeout_nx)(struct shared_rwlock *__restrict self,
                                                       __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	__hybrid_assert(!task_wasconnected());
	while (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) != 0) {
		TASK_POLL_BEFORE_CONNECT({
			if (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == 0)
				goto success;
		});
		task_connect_for_poll(&self->sl_wrwait);
		if unlikely(__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == 0) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx(abs_timeout))
			return false;
	}
success:
	COMPILER_BARRIER();
	return true;
}
#endif /* __KERNEL__ */

DECL_END

DEFINE_PUBLIC_ALIAS_P(shared_rwlock_tryread,libc_shared_rwlock_tryread,WUNUSED __NOBLOCK ATTR_INOUT(1),bool,NOTHROW,__FCALL,(struct shared_rwlock *__restrict self),(self));
DEFINE_PUBLIC_ALIAS_P(shared_rwlock_trywrite,libc_shared_rwlock_trywrite,WUNUSED __NOBLOCK ATTR_INOUT(1),bool,NOTHROW,__FCALL,(struct shared_rwlock *__restrict self),(self));
DEFINE_PUBLIC_ALIAS_P_VOID(shared_rwlock_endwrite,libc_shared_rwlock_endwrite,__NOBLOCK ATTR_INOUT(1),NOTHROW,__FCALL,(struct shared_rwlock *__restrict self),(self));
DEFINE_PUBLIC_ALIAS_P(shared_rwlock_endread,libc_shared_rwlock_endread,__NOBLOCK ATTR_INOUT(1),bool,NOTHROW,__FCALL,(struct shared_rwlock *__restrict self),(self));
DEFINE_PUBLIC_ALIAS_P(shared_rwlock_end,libc_shared_rwlock_end,__NOBLOCK ATTR_INOUT(1),bool,NOTHROW,__FCALL,(struct shared_rwlock *__restrict self),(self));
DEFINE_PUBLIC_ALIAS_P_VOID(shared_rwlock_downgrade,libc_shared_rwlock_downgrade,__NOBLOCK ATTR_INOUT(1),NOTHROW,__FCALL,(struct shared_rwlock *__restrict self),(self));
DEFINE_PUBLIC_ALIAS_P(shared_rwlock_upgrade,libc_shared_rwlock_upgrade,WUNUSED __BLOCKING ATTR_INOUT(1),bool,THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self),(self));
DEFINE_PUBLIC_ALIAS_P_VOID(shared_rwlock_read,libc_shared_rwlock_read,__BLOCKING ATTR_INOUT(1),THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self),(self));
DEFINE_PUBLIC_ALIAS_P_VOID(shared_rwlock_write,libc_shared_rwlock_write,__BLOCKING ATTR_INOUT(1),THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self),(self));
DEFINE_PUBLIC_ALIAS_P(shared_rwlock_read_with_timeout,libc_shared_rwlock_read_with_timeout,WUNUSED __BLOCKING ATTR_INOUT(1),bool,THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self, __shared_rwlock_timespec abs_timeout),(self,abs_timeout));
DEFINE_PUBLIC_ALIAS_P(shared_rwlock_write_with_timeout,libc_shared_rwlock_write_with_timeout,WUNUSED __BLOCKING ATTR_INOUT(1),bool,THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self, __shared_rwlock_timespec abs_timeout),(self,abs_timeout));
DEFINE_PUBLIC_ALIAS_P_VOID(shared_rwlock_waitread,libc_shared_rwlock_waitread,__BLOCKING ATTR_INOUT(1),THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self),(self));
DEFINE_PUBLIC_ALIAS_P_VOID(shared_rwlock_waitwrite,libc_shared_rwlock_waitwrite,__BLOCKING ATTR_INOUT(1),THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self),(self));
DEFINE_PUBLIC_ALIAS_P(shared_rwlock_waitread_with_timeout,libc_shared_rwlock_waitread_with_timeout,WUNUSED __BLOCKING ATTR_INOUT(1),bool,THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self, __shared_rwlock_timespec abs_timeout),(self,abs_timeout));
DEFINE_PUBLIC_ALIAS_P(shared_rwlock_waitwrite_with_timeout,libc_shared_rwlock_waitwrite_with_timeout,WUNUSED __BLOCKING ATTR_INOUT(1),bool,THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self, __shared_rwlock_timespec abs_timeout),(self,abs_timeout));
#ifndef __KERNEL__
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(shared_rwlock_read_with_timeout64,libc_shared_rwlock_read_with_timeout64,WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2),bool,THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self, struct timespec64 const *abs_timeout),(self,abs_timeout));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(shared_rwlock_write_with_timeout64,libc_shared_rwlock_write_with_timeout64,WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2),bool,THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self, struct timespec64 const *abs_timeout),(self,abs_timeout));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(shared_rwlock_waitread_with_timeout64,libc_shared_rwlock_waitread_with_timeout64,WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2),bool,THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self, struct timespec64 const *abs_timeout),(self,abs_timeout));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(shared_rwlock_waitwrite_with_timeout64,libc_shared_rwlock_waitwrite_with_timeout64,WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2),bool,THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self, struct timespec64 const *abs_timeout),(self,abs_timeout));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* !__KERNEL__ */
#ifdef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(shared_rwlock_read_nx,libc_shared_rwlock_read_nx,WUNUSED __BLOCKING ATTR_INOUT(1),bool,THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self),(self));
DEFINE_PUBLIC_ALIAS_P(shared_rwlock_write_nx,libc_shared_rwlock_write_nx,WUNUSED __BLOCKING ATTR_INOUT(1),bool,THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self),(self));
DEFINE_PUBLIC_ALIAS_P(shared_rwlock_read_with_timeout_nx,libc_shared_rwlock_read_with_timeout_nx,WUNUSED __BLOCKING ATTR_INOUT(1),bool,THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self, __shared_rwlock_timespec abs_timeout),(self,abs_timeout));
DEFINE_PUBLIC_ALIAS_P(shared_rwlock_write_with_timeout_nx,libc_shared_rwlock_write_with_timeout_nx,WUNUSED __BLOCKING ATTR_INOUT(1),bool,THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self, __shared_rwlock_timespec abs_timeout),(self,abs_timeout));
DEFINE_PUBLIC_ALIAS_P(shared_rwlock_waitread_nx,libc_shared_rwlock_waitread_nx,WUNUSED __BLOCKING ATTR_INOUT(1),bool,THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self),(self));
DEFINE_PUBLIC_ALIAS_P(shared_rwlock_waitwrite_nx,libc_shared_rwlock_waitwrite_nx,WUNUSED __BLOCKING ATTR_INOUT(1),bool,THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self),(self));
DEFINE_PUBLIC_ALIAS_P(shared_rwlock_waitread_with_timeout_nx,libc_shared_rwlock_waitread_with_timeout_nx,WUNUSED __BLOCKING ATTR_INOUT(1),bool,THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self, __shared_rwlock_timespec abs_timeout),(self,abs_timeout));
DEFINE_PUBLIC_ALIAS_P(shared_rwlock_waitwrite_with_timeout_nx,libc_shared_rwlock_waitwrite_with_timeout_nx,WUNUSED __BLOCKING ATTR_INOUT(1),bool,THROWING(E_WOULDBLOCK, ...),__FCALL,(struct shared_rwlock *__restrict self, __shared_rwlock_timespec abs_timeout),(self,abs_timeout));
#endif /* __KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_KOS_SCHED_SHARED_RWLOCK_C */
