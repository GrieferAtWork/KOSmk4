/* HASH CRC-32:0x76955030 */
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
#ifndef GUARD_LIBC_AUTO_KOS_SCHED_SHARED_RECURSIVE_RWLOCK_C
#define GUARD_LIBC_AUTO_KOS_SCHED_SHARED_RECURSIVE_RWLOCK_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "kos.sched.shared-recursive-rwlock.h"
#include "kos.sched.shared-rwlock.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <hybrid/__atomic.h>
/* >> shared_recursive_rwlock_tryread(3)
 * Try  to acquire a read-lock to `self' */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __NOBLOCK ATTR_INOUT(1) bool
NOTHROW(__FCALL libc_shared_recursive_rwlock_tryread)(struct shared_recursive_rwlock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (libc_shared_rwlock_tryread(&self->srr_lock))
		return true;
	if (__shared_recursive_rwlock_isown(self)) {
		++self->srr_wrcnt;
		return true;
	}
	return false;
}
#include <hybrid/__atomic.h>
/* >> shared_recursive_rwlock_trywrite(3)
 * Try to acquire a recursive write-lock to `self' */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __NOBLOCK ATTR_INOUT(1) bool
NOTHROW(__FCALL libc_shared_recursive_rwlock_trywrite)(struct shared_recursive_rwlock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (libc_shared_rwlock_trywrite(&self->srr_lock)) {
		__shared_recursive_rwlock_setown(self);
		return true;
	}
	if (__shared_recursive_rwlock_isown(self)) {
		++self->srr_wrcnt;
		return true;
	}
	return false;
}
#include <hybrid/__atomic.h>
#include <hybrid/__assert.h>
#include <kos/asm/futex.h>
/* >> shared_recursive_rwlock_endwrite(3)
 * Release a recursive write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
INTERN ATTR_SECTION(".text.crt.sched.futex") __NOBLOCK ATTR_INOUT(1) bool
NOTHROW(__FCALL libc_shared_recursive_rwlock_endwrite)(struct shared_recursive_rwlock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	__COMPILER_BARRIER();
	__hybrid_assertf(self->srr_lock.sl_lock == (uintptr_t)-1,
	                 "Lock isn't in write-mode (%x)",
	                 self->srr_lock.sl_lock);
	__hybrid_assertf(__shared_recursive_rwlock_isown(self),
	                 "You're not the owner of this lock");
	if (self->srr_wrcnt == 0) {
		self->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(&self->srr_lock.sl_lock, 0, __ATOMIC_RELEASE);
		if (!__shared_rwlock_wrwait_send(&self->srr_lock))
			__shared_rwlock_rdwait_broadcast(&self->srr_lock);
		return true;
	}
	--self->srr_wrcnt;
	return false;
}
#include <hybrid/__atomic.h>
#include <hybrid/__assert.h>
#include <kos/asm/futex.h>
/* >> shared_recursive_rwlock_endread(3)
 * Release  a   read-lock  from   `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
INTERN ATTR_SECTION(".text.crt.sched.futex") __NOBLOCK ATTR_INOUT(1) bool
NOTHROW(__FCALL libc_shared_recursive_rwlock_endread)(struct shared_recursive_rwlock *__restrict self) {
	uintptr_t result;
	__COMPILER_WORKAROUND_GCC_105689(self);
	COMPILER_READ_BARRIER();
	if (self->srr_lock.sl_lock == (uintptr_t)-1)
		return libc_shared_recursive_rwlock_endwrite(self);
	__hybrid_assertf(self->srr_lock.sl_lock != 0, "Lock isn't held by anyone");
	result = __hybrid_atomic_decfetch(&self->srr_lock.sl_lock, __ATOMIC_RELEASE);
	if (result == 0)
		__shared_rwlock_wrwait_send(&self->srr_lock);
	return result == 0;
}
#include <kos/bits/shared-recursive-rwlock.h>
#include <hybrid/__assert.h>
/* >> shared_recursive_rwlock_downgrade(3)
 * Downgrade a recursive write-lock to a read-lock (Always succeeds, but you have
 * to ensure  that  you're only  holding  a  single write-lock  at  the  moment). */
INTERN ATTR_SECTION(".text.crt.sched.futex") __NOBLOCK ATTR_INOUT(1) void
NOTHROW(__FCALL libc_shared_recursive_rwlock_downgrade)(struct shared_recursive_rwlock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	__hybrid_assertf(__shared_recursive_rwlock_isown(self), "You're not holding this lock");
	__hybrid_assertf(self->srr_wrcnt > 0, "You're holding more than 1 write-lock");
	self->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID;
	COMPILER_WRITE_BARRIER();
	libc_shared_rwlock_downgrade(&self->srr_lock);
}
#include <hybrid/__atomic.h>
/* >> shared_recursive_rwlock_upgrade(3)
 * Blocking-upgrade a read-lock into a recursive write-lock
 * NOTE: The lock is always upgraded, but when `false' is returned, no lock
 *       may  have been  held temporarily,  meaning that  the caller should
 *       re-load local copies of affected resources.
 * @return: true:  Upgrade was performed without the read-lock being lost
 * @return: false: The read-lock had to be released before a recursive write-lock was acquired */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_recursive_rwlock_upgrade)(struct shared_recursive_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__hybrid_atomic_cmpxch(&self->srr_lock.sl_lock, 1, (uintptr_t)-1, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED)) {
		__shared_recursive_rwlock_setown(self);
		return true; /* Lock wasn't lost */
	}
	libc_shared_recursive_rwlock_endread(self);
	libc_shared_recursive_rwlock_write(self);
	return false; /* Lock was (temporarily) lost */
}
/* >> shared_recursive_rwlock_read(3)
 * Acquire a read-lock to the given shared_recursive_rwlock. */
INTERN ATTR_SECTION(".text.crt.sched.futex") __BLOCKING ATTR_INOUT(1) void
(__FCALL libc_shared_recursive_rwlock_read)(struct shared_recursive_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self)) {
		++self->srr_wrcnt;
		return;
	}
	libc_shared_rwlock_read(&self->srr_lock);
}
/* >> shared_recursive_rwlock_write(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock. */
INTERN ATTR_SECTION(".text.crt.sched.futex") __BLOCKING ATTR_INOUT(1) void
(__FCALL libc_shared_recursive_rwlock_write)(struct shared_recursive_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self)) {
		++self->srr_wrcnt;
		return;
	}
	libc_shared_rwlock_write(&self->srr_lock);
	__shared_recursive_rwlock_setown(self);
}
/* >> shared_recursive_rwlock_read_with_timeout(3), shared_recursive_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_recursive_rwlock_read_with_timeout)(struct shared_recursive_rwlock *__restrict self,
                                                         __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self)) {
		++self->srr_wrcnt;
		return true;
	}
	return libc_shared_rwlock_read_with_timeout(&self->srr_lock, abs_timeout);
}
/* >> shared_recursive_rwlock_write_with_timeout(3), shared_recursive_rwlock_write_with_timeout64(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a recursive write-lock.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_recursive_rwlock_write_with_timeout)(struct shared_recursive_rwlock *__restrict self,
                                                          __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	bool result;
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self)) {
		++self->srr_wrcnt;
		return true;
	}
	result = libc_shared_rwlock_write_with_timeout(&self->srr_lock, abs_timeout);
	if (result)
		__shared_recursive_rwlock_setown(self);
	return result;
}
/* >> shared_recursive_rwlock_waitread(3)
 * Wait until acquiring a read-lock to `self' no longer blocks */
INTERN ATTR_SECTION(".text.crt.sched.futex") __BLOCKING ATTR_INOUT(1) void
(__FCALL libc_shared_recursive_rwlock_waitread)(struct shared_recursive_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self))
		return;
	libc_shared_rwlock_waitread(&self->srr_lock);
}
/* >> shared_recursive_rwlock_waitwrite(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks */
INTERN ATTR_SECTION(".text.crt.sched.futex") __BLOCKING ATTR_INOUT(1) void
(__FCALL libc_shared_recursive_rwlock_waitwrite)(struct shared_recursive_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self))
		return;
	libc_shared_rwlock_waitwrite(&self->srr_lock);
}
/* >> shared_recursive_rwlock_waitread_with_timeout(3), shared_recursive_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_recursive_rwlock_waitread_with_timeout)(struct shared_recursive_rwlock *__restrict self,
                                                             __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self))
		return true;
	return libc_shared_rwlock_waitread_with_timeout(&self->srr_lock, abs_timeout);
}
/* >> shared_recursive_rwlock_waitwrite_with_timeout(3), shared_recursive_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_recursive_rwlock_waitwrite_with_timeout)(struct shared_recursive_rwlock *__restrict self,
                                                              __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self))
		return true;
	return libc_shared_rwlock_waitwrite_with_timeout(&self->srr_lock, abs_timeout);
}
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_shared_recursive_rwlock_read_with_timeout64, libc_shared_recursive_rwlock_read_with_timeout);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* >> shared_recursive_rwlock_read_with_timeout(3), shared_recursive_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2) bool
(__FCALL libc_shared_recursive_rwlock_read_with_timeout64)(struct shared_recursive_rwlock *__restrict self,
                                                           struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self)) {
		++self->srr_wrcnt;
		return true;
	}
	return libc_shared_rwlock_read_with_timeout64(&self->srr_lock, abs_timeout);
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_shared_recursive_rwlock_write_with_timeout64, libc_shared_recursive_rwlock_write_with_timeout);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* >> shared_recursive_rwlock_write_with_timeout(3), shared_recursive_rwlock_write_with_timeout64(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a recursive write-lock.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2) bool
(__FCALL libc_shared_recursive_rwlock_write_with_timeout64)(struct shared_recursive_rwlock *__restrict self,
                                                            struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	bool result;
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self)) {
		++self->srr_wrcnt;
		return true;
	}
	result = libc_shared_rwlock_write_with_timeout64(&self->srr_lock, abs_timeout);
	if (result)
		__shared_recursive_rwlock_setown(self);
	return result;
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_shared_recursive_rwlock_waitread_with_timeout64, libc_shared_recursive_rwlock_waitread_with_timeout);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* >> shared_recursive_rwlock_waitread_with_timeout(3), shared_recursive_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2) bool
(__FCALL libc_shared_recursive_rwlock_waitread_with_timeout64)(struct shared_recursive_rwlock *__restrict self,
                                                               struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self))
		return true;
	return libc_shared_rwlock_waitread_with_timeout64(&self->srr_lock, abs_timeout);
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_shared_recursive_rwlock_waitwrite_with_timeout64, libc_shared_recursive_rwlock_waitwrite_with_timeout);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* >> shared_recursive_rwlock_waitwrite_with_timeout(3), shared_recursive_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2) bool
(__FCALL libc_shared_recursive_rwlock_waitwrite_with_timeout64)(struct shared_recursive_rwlock *__restrict self,
                                                                struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self))
		return true;
	return libc_shared_rwlock_waitwrite_with_timeout64(&self->srr_lock, abs_timeout);
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(shared_recursive_rwlock_tryread, libc_shared_recursive_rwlock_tryread);
DEFINE_PUBLIC_ALIAS(shared_recursive_rwlock_trywrite, libc_shared_recursive_rwlock_trywrite);
DEFINE_PUBLIC_ALIAS(shared_recursive_rwlock_endwrite, libc_shared_recursive_rwlock_endwrite);
DEFINE_PUBLIC_ALIAS(shared_recursive_rwlock_endread, libc_shared_recursive_rwlock_endread);
DEFINE_PUBLIC_ALIAS(shared_recursive_rwlock_downgrade, libc_shared_recursive_rwlock_downgrade);
DEFINE_PUBLIC_ALIAS(shared_recursive_rwlock_upgrade, libc_shared_recursive_rwlock_upgrade);
DEFINE_PUBLIC_ALIAS(shared_recursive_rwlock_read, libc_shared_recursive_rwlock_read);
DEFINE_PUBLIC_ALIAS(shared_recursive_rwlock_write, libc_shared_recursive_rwlock_write);
DEFINE_PUBLIC_ALIAS(shared_recursive_rwlock_read_with_timeout, libc_shared_recursive_rwlock_read_with_timeout);
DEFINE_PUBLIC_ALIAS(shared_recursive_rwlock_write_with_timeout, libc_shared_recursive_rwlock_write_with_timeout);
DEFINE_PUBLIC_ALIAS(shared_recursive_rwlock_waitread, libc_shared_recursive_rwlock_waitread);
DEFINE_PUBLIC_ALIAS(shared_recursive_rwlock_waitwrite, libc_shared_recursive_rwlock_waitwrite);
DEFINE_PUBLIC_ALIAS(shared_recursive_rwlock_waitread_with_timeout, libc_shared_recursive_rwlock_waitread_with_timeout);
DEFINE_PUBLIC_ALIAS(shared_recursive_rwlock_waitwrite_with_timeout, libc_shared_recursive_rwlock_waitwrite_with_timeout);
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(shared_recursive_rwlock_read_with_timeout64, libc_shared_recursive_rwlock_read_with_timeout64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(shared_recursive_rwlock_write_with_timeout64, libc_shared_recursive_rwlock_write_with_timeout64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(shared_recursive_rwlock_waitread_with_timeout64, libc_shared_recursive_rwlock_waitread_with_timeout64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(shared_recursive_rwlock_waitwrite_with_timeout64, libc_shared_recursive_rwlock_waitwrite_with_timeout64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_KOS_SCHED_SHARED_RECURSIVE_RWLOCK_C */
