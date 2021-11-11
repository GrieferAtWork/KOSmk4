/* HASH CRC-32:0x593f82b7 */
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
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __NOBLOCK NONNULL((1)) bool
NOTHROW(__FCALL libc_shared_rwlock_tryread)(struct shared_rwlock *__restrict self) {
	uintptr_t temp;
	do {
		temp = __hybrid_atomic_load(self->sl_lock, __ATOMIC_ACQUIRE);
		if (temp == (uintptr_t)-1)
			return false;
		__hybrid_assert(temp != (uintptr_t)-2);
	} while (!__hybrid_atomic_cmpxch_weak(self->sl_lock, temp, temp + 1,
	                                      __ATOMIC_ACQUIRE, __ATOMIC_RELAXED));
	__COMPILER_READ_BARRIER();
	return true;
}
/* >> shared_rwlock_trywrite(3)
 * Try to acquire a write-lock to `self' */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __NOBLOCK NONNULL((1)) bool
NOTHROW(__FCALL libc_shared_rwlock_trywrite)(struct shared_rwlock *__restrict self) {
	if (!__hybrid_atomic_cmpxch(self->sl_lock, 0, (uintptr_t)-1,
	                            __ATOMIC_ACQUIRE, __ATOMIC_RELAXED))
		return false;
	__COMPILER_BARRIER();
	return true;
}
#include <hybrid/__assert.h>
#include <kos/bits/futex.h>
/* >> shared_rwlock_endwrite(3)
 * Release a a write-lock from `self' */
INTERN ATTR_SECTION(".text.crt.sched.futex") __NOBLOCK NONNULL((1)) void
NOTHROW(__FCALL libc_shared_rwlock_endwrite)(struct shared_rwlock *__restrict self) {
	__COMPILER_BARRIER();
	__hybrid_assertf(self->sl_lock == (uintptr_t)-1, "Lock isn't in write-mode (%x)", self->sl_lock);
	__hybrid_atomic_store(self->sl_lock, 0, __ATOMIC_RELEASE);
	if (!__shared_rwlock_wrwait_send(self))
		__shared_rwlock_rdwait_broadcast(self);
}
/* >> shared_rwlock_endread(3)
 * Release a read-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
INTERN ATTR_SECTION(".text.crt.sched.futex") __NOBLOCK NONNULL((1)) bool
NOTHROW(__FCALL libc_shared_rwlock_endread)(struct shared_rwlock *__restrict self) {
	uintptr_t __result;
	__COMPILER_READ_BARRIER();
	__hybrid_assertf(self->sl_lock != (uintptr_t)-1, "Lock is in write-mode (%x)", self->sl_lock);
	__hybrid_assertf(self->sl_lock != 0, "Lock isn't held by anyone");
	__result = __hybrid_atomic_decfetch(self->sl_lock, __ATOMIC_RELEASE);
	if (__result == 0)
		__shared_rwlock_wrwait_send(self);
	return __result == 0;
}
/* >> shared_rwlock_end(3)
 * Release a read- or write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
INTERN ATTR_SECTION(".text.crt.sched.futex") __NOBLOCK NONNULL((1)) bool
NOTHROW(__FCALL libc_shared_rwlock_end)(struct shared_rwlock *__restrict self) {
	__COMPILER_BARRIER();
	if (self->sl_lock != (uintptr_t)-1) {
		/* Read-lock */
		uintptr_t __result;
		__hybrid_assertf(self->sl_lock != 0, "No remaining read-locks");
		__result = __hybrid_atomic_decfetch(self->sl_lock, __ATOMIC_RELEASE);
		if (__result == 0)
			__shared_rwlock_wrwait_send(self);
		return __result == 0;
	}
	/* Write-lock */
	__hybrid_atomic_store(self->sl_lock, 0, __ATOMIC_RELEASE);
	if (!__shared_rwlock_wrwait_send(self))
		__shared_rwlock_rdwait_broadcast(self);
	return true;
}
/* >> shared_rwlock_downgrade(3)
 * Downgrade a write-lock to a read-lock (Always succeeds). */
INTERN ATTR_SECTION(".text.crt.sched.futex") __NOBLOCK NONNULL((1)) void
NOTHROW(__FCALL libc_shared_rwlock_downgrade)(struct shared_rwlock *__restrict self) {
	__COMPILER_WRITE_BARRIER();
	__hybrid_assertf(self->sl_lock == (uintptr_t)-1, "Lock isn't in write-mode (%x)", self->sl_lock);
	__hybrid_atomic_store(self->sl_lock, 1, __ATOMIC_RELEASE);
	__shared_rwlock_rdwait_broadcast(self); /* Allow for more readers. */
}
#ifdef __KERNEL__
#include <hybrid/__assert.h>
#include <sched/signal.h>
#else /* __KERNEL__ */
#include <kos/syscalls.h>
#include <kos/bits/futex.h>
#include <kos/bits/futex-expr.h>
#ifndef __SHARED_RWLOCK_WAITREADEXPR_DEFINED
#define __SHARED_RWLOCK_WAITREADEXPR_DEFINED
__NAMESPACE_LOCAL_BEGIN
static struct lfutexexpr const __shared_rwlock_waitreadexpr[] = {
	/* Wait while `sl_lock == (uintptr_t)-1' */
	LFUTEXEXPR_INIT(offsetof(struct shared_rwlock, sl_lock), LFUTEX_WAIT_WHILE, (uintptr_t)-1, 0)
};
__NAMESPACE_LOCAL_END
#endif /* !__SHARED_RWLOCK_WAITREADEXPR_DEFINED */

#endif /* !__KERNEL__ */
/* >> shared_rwlock_read(3)
 * Acquire a read-lock to the given shared_rwlock. */
INTERN ATTR_SECTION(".text.crt.sched.futex") __BLOCKING NONNULL((1)) void
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
		task_waitfor();
	}
success:
#else /* __KERNEL__ */
	while (!libc_shared_rwlock_tryread(self)) {
		__hybrid_atomic_store(self->sl_rdwait, 1, __ATOMIC_SEQ_CST);
		libc_LFutexExpr64(&self->sl_rdwait, self, 1, __NAMESPACE_LOCAL_SYM __shared_rwlock_waitreadexpr, NULL, 0);
	}
#endif /* !__KERNEL__ */
	COMPILER_READ_BARRIER();
}

DECL_END

DEFINE_PUBLIC_ALIAS(shared_rwlock_tryread, libc_shared_rwlock_tryread);
DEFINE_PUBLIC_ALIAS(shared_rwlock_trywrite, libc_shared_rwlock_trywrite);
DEFINE_PUBLIC_ALIAS(shared_rwlock_endwrite, libc_shared_rwlock_endwrite);
DEFINE_PUBLIC_ALIAS(shared_rwlock_endread, libc_shared_rwlock_endread);
DEFINE_PUBLIC_ALIAS(shared_rwlock_end, libc_shared_rwlock_end);
DEFINE_PUBLIC_ALIAS(shared_rwlock_downgrade, libc_shared_rwlock_downgrade);
DEFINE_PUBLIC_ALIAS(shared_rwlock_read, libc_shared_rwlock_read);

#endif /* !GUARD_LIBC_AUTO_KOS_SCHED_SHARED_RWLOCK_C */
