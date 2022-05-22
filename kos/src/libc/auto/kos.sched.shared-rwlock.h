/* HASH CRC-32:0xdc6f9251 */
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
#ifndef GUARD_LIBC_AUTO_KOS_SCHED_SHARED_RWLOCK_H
#define GUARD_LIBC_AUTO_KOS_SCHED_SHARED_RWLOCK_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/sched/shared-rwlock.h>

DECL_BEGIN

/* >> shared_rwlock_tryread(3)
 * Try to acquire a read-lock to `self' */
INTDEF WUNUSED __NOBLOCK ATTR_ACCESS_RW(1) bool NOTHROW(__FCALL libc_shared_rwlock_tryread)(struct shared_rwlock *__restrict self);
/* >> shared_rwlock_trywrite(3)
 * Try to acquire a write-lock to `self' */
INTDEF WUNUSED __NOBLOCK ATTR_ACCESS_RW(1) bool NOTHROW(__FCALL libc_shared_rwlock_trywrite)(struct shared_rwlock *__restrict self);
/* >> shared_rwlock_endwrite(3)
 * Release a write-lock from `self' */
INTDEF __NOBLOCK ATTR_ACCESS_RW(1) void NOTHROW(__FCALL libc_shared_rwlock_endwrite)(struct shared_rwlock *__restrict self);
/* >> shared_rwlock_endread(3)
 * Release a read-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
INTDEF __NOBLOCK ATTR_ACCESS_RW(1) bool NOTHROW(__FCALL libc_shared_rwlock_endread)(struct shared_rwlock *__restrict self);
/* >> shared_rwlock_end(3)
 * Release a read- or write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
INTDEF __NOBLOCK ATTR_ACCESS_RW(1) bool NOTHROW(__FCALL libc_shared_rwlock_end)(struct shared_rwlock *__restrict self);
/* >> shared_rwlock_downgrade(3)
 * Downgrade a write-lock to a read-lock (Always succeeds). */
INTDEF __NOBLOCK ATTR_ACCESS_RW(1) void NOTHROW(__FCALL libc_shared_rwlock_downgrade)(struct shared_rwlock *__restrict self);
/* >> shared_rwlock_upgrade(3)
 * Blocking-upgrade a read-lock into a write-lock
 * NOTE: The lock is always upgraded, but when `false' is returned, no lock
 *       may  have been  held temporarily,  meaning that  the caller should
 *       re-load local copies of affected resources.
 * @return: true:  Upgrade was performed without the read-lock being lost
 * @return: false: The read-lock had to be released before a write-lock was acquired */
INTDEF WUNUSED __BLOCKING ATTR_ACCESS_RW(1) bool (__FCALL libc_shared_rwlock_upgrade)(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...);
/* >> shared_rwlock_read(3)
 * Acquire a read-lock to the given shared_rwlock. */
INTDEF __BLOCKING ATTR_ACCESS_RW(1) void (__FCALL libc_shared_rwlock_read)(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...);
/* >> shared_rwlock_write(3)
 * Acquire a write-lock to the given shared_rwlock. */
INTDEF __BLOCKING ATTR_ACCESS_RW(1) void (__FCALL libc_shared_rwlock_write)(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...);
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING ATTR_ACCESS_RW(1) bool (__FCALL libc_shared_rwlock_read_with_timeout)(struct shared_rwlock *__restrict self, __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...);
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING ATTR_ACCESS_RW(1) bool (__FCALL libc_shared_rwlock_write_with_timeout)(struct shared_rwlock *__restrict self, __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...);
/* >> shared_rwlock_waitread(3)
 * Wait until acquiring a read-lock to `self' no longer blocks */
INTDEF __BLOCKING ATTR_ACCESS_RW(1) void (__FCALL libc_shared_rwlock_waitread)(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...);
/* >> shared_rwlock_waitwrite(3)
 * Wait until acquiring a write-lock to `self' no longer blocks */
INTDEF __BLOCKING ATTR_ACCESS_RW(1) void (__FCALL libc_shared_rwlock_waitwrite)(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...);
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING ATTR_ACCESS_RW(1) bool (__FCALL libc_shared_rwlock_waitread_with_timeout)(struct shared_rwlock *__restrict self, __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...);
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING ATTR_ACCESS_RW(1) bool (__FCALL libc_shared_rwlock_waitwrite_with_timeout)(struct shared_rwlock *__restrict self, __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...);
#ifndef __KERNEL__
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING ATTR_ACCESS_RO_OPT(2) ATTR_ACCESS_RW(1) bool (__FCALL libc_shared_rwlock_read_with_timeout64)(struct shared_rwlock *__restrict self, struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, ...);
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING ATTR_ACCESS_RO_OPT(2) ATTR_ACCESS_RW(1) bool (__FCALL libc_shared_rwlock_write_with_timeout64)(struct shared_rwlock *__restrict self, struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, ...);
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING ATTR_ACCESS_RO_OPT(2) ATTR_ACCESS_RW(1) bool (__FCALL libc_shared_rwlock_waitread_with_timeout64)(struct shared_rwlock *__restrict self, struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, ...);
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING ATTR_ACCESS_RO_OPT(2) ATTR_ACCESS_RW(1) bool (__FCALL libc_shared_rwlock_waitwrite_with_timeout64)(struct shared_rwlock *__restrict self, struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, ...);
#endif /* !__KERNEL__ */
#ifdef __KERNEL__
/* >> shared_rwlock_read_nx(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTDEF WUNUSED __BLOCKING ATTR_ACCESS_RW(1) bool (__FCALL libc_shared_rwlock_read_nx)(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...);
/* >> shared_rwlock_write_nx(3)
 * Acquire a write-lock to the given shared_rwlock.
 * Acquire  a  lock   to  the  given   shared_lock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTDEF WUNUSED __BLOCKING ATTR_ACCESS_RW(1) bool (__FCALL libc_shared_rwlock_write_nx)(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...);
/* >> shared_rwlock_read_with_timeout_nx(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTDEF WUNUSED __BLOCKING ATTR_ACCESS_RW(1) bool (__FCALL libc_shared_rwlock_read_with_timeout_nx)(struct shared_rwlock *__restrict self, __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...);
/* >> shared_rwlock_write_with_timeout_nx(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTDEF WUNUSED __BLOCKING ATTR_ACCESS_RW(1) bool (__FCALL libc_shared_rwlock_write_with_timeout_nx)(struct shared_rwlock *__restrict self, __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...);
/* >> shared_rwlock_waitread_nx(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTDEF WUNUSED __BLOCKING ATTR_ACCESS_RW(1) bool (__FCALL libc_shared_rwlock_waitread_nx)(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...);
/* >> shared_rwlock_waitwrite_nx(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * Acquire a lock to the given shared_lock.
 * @return: true:  A write-lock became available.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTDEF WUNUSED __BLOCKING ATTR_ACCESS_RW(1) bool (__FCALL libc_shared_rwlock_waitwrite_nx)(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...);
/* >> shared_rwlock_waitread_with_timeout_nx(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTDEF WUNUSED __BLOCKING ATTR_ACCESS_RW(1) bool (__FCALL libc_shared_rwlock_waitread_with_timeout_nx)(struct shared_rwlock *__restrict self, __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...);
/* >> shared_rwlock_waitwrite_with_timeout_nx(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTDEF WUNUSED __BLOCKING ATTR_ACCESS_RW(1) bool (__FCALL libc_shared_rwlock_waitwrite_with_timeout_nx)(struct shared_rwlock *__restrict self, __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...);
#endif /* __KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_KOS_SCHED_SHARED_RWLOCK_H */
