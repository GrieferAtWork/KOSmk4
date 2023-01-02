/* HASH CRC-32:0xd0a9b968 */
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
#ifndef GUARD_LIBC_AUTO_KOS_SCHED_SHARED_RECURSIVE_RWLOCK_H
#define GUARD_LIBC_AUTO_KOS_SCHED_SHARED_RECURSIVE_RWLOCK_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/sched/shared-recursive-rwlock.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> shared_recursive_rwlock_tryread(3)
 * Try  to acquire a read-lock to `self' */
INTDEF WUNUSED __NOBLOCK ATTR_INOUT(1) bool NOTHROW(__FCALL libc_shared_recursive_rwlock_tryread)(struct shared_recursive_rwlock *__restrict self);
/* >> shared_recursive_rwlock_trywrite(3)
 * Try to acquire a recursive write-lock to `self' */
INTDEF WUNUSED __NOBLOCK ATTR_INOUT(1) bool NOTHROW(__FCALL libc_shared_recursive_rwlock_trywrite)(struct shared_recursive_rwlock *__restrict self);
/* >> shared_recursive_rwlock_endwrite(3)
 * Release a recursive write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
INTDEF __NOBLOCK ATTR_INOUT(1) bool NOTHROW(__FCALL libc_shared_recursive_rwlock_endwrite)(struct shared_recursive_rwlock *__restrict self);
/* >> shared_recursive_rwlock_endread(3)
 * Release  a   read-lock  from   `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
INTDEF __NOBLOCK ATTR_INOUT(1) bool NOTHROW(__FCALL libc_shared_recursive_rwlock_endread)(struct shared_recursive_rwlock *__restrict self);
/* >> shared_recursive_rwlock_downgrade(3)
 * Downgrade a recursive write-lock to a read-lock (Always succeeds, but you have
 * to ensure  that  you're only  holding  a  single write-lock  at  the  moment). */
INTDEF __NOBLOCK ATTR_INOUT(1) void NOTHROW(__FCALL libc_shared_recursive_rwlock_downgrade)(struct shared_recursive_rwlock *__restrict self);
/* >> shared_recursive_rwlock_upgrade(3)
 * Blocking-upgrade a read-lock into a recursive write-lock
 * NOTE: The lock is always upgraded, but when `false' is returned, no lock
 *       may  have been  held temporarily,  meaning that  the caller should
 *       re-load local copies of affected resources.
 * @return: true:  Upgrade was performed without the read-lock being lost
 * @return: false: The read-lock had to be released before a recursive write-lock was acquired */
INTDEF WUNUSED __BLOCKING ATTR_INOUT(1) bool (__FCALL libc_shared_recursive_rwlock_upgrade)(struct shared_recursive_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...);
/* >> shared_recursive_rwlock_read(3)
 * Acquire a read-lock to the given shared_recursive_rwlock. */
INTDEF __BLOCKING ATTR_INOUT(1) void (__FCALL libc_shared_recursive_rwlock_read)(struct shared_recursive_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...);
/* >> shared_recursive_rwlock_write(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock. */
INTDEF __BLOCKING ATTR_INOUT(1) void (__FCALL libc_shared_recursive_rwlock_write)(struct shared_recursive_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...);
/* >> shared_recursive_rwlock_read_with_timeout(3), shared_recursive_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING ATTR_INOUT(1) bool (__FCALL libc_shared_recursive_rwlock_read_with_timeout)(struct shared_recursive_rwlock *__restrict self, __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...);
/* >> shared_recursive_rwlock_write_with_timeout(3), shared_recursive_rwlock_write_with_timeout64(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a recursive write-lock.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING ATTR_INOUT(1) bool (__FCALL libc_shared_recursive_rwlock_write_with_timeout)(struct shared_recursive_rwlock *__restrict self, __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...);
/* >> shared_recursive_rwlock_waitread(3)
 * Wait until acquiring a read-lock to `self' no longer blocks */
INTDEF __BLOCKING ATTR_INOUT(1) void (__FCALL libc_shared_recursive_rwlock_waitread)(struct shared_recursive_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...);
/* >> shared_recursive_rwlock_waitwrite(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks */
INTDEF __BLOCKING ATTR_INOUT(1) void (__FCALL libc_shared_recursive_rwlock_waitwrite)(struct shared_recursive_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...);
/* >> shared_recursive_rwlock_waitread_with_timeout(3), shared_recursive_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING ATTR_INOUT(1) bool (__FCALL libc_shared_recursive_rwlock_waitread_with_timeout)(struct shared_recursive_rwlock *__restrict self, __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...);
/* >> shared_recursive_rwlock_waitwrite_with_timeout(3), shared_recursive_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING ATTR_INOUT(1) bool (__FCALL libc_shared_recursive_rwlock_waitwrite_with_timeout)(struct shared_recursive_rwlock *__restrict self, __shared_rwlock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...);
/* >> shared_recursive_rwlock_read_with_timeout(3), shared_recursive_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2) bool (__FCALL libc_shared_recursive_rwlock_read_with_timeout64)(struct shared_recursive_rwlock *__restrict self, struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, ...);
/* >> shared_recursive_rwlock_write_with_timeout(3), shared_recursive_rwlock_write_with_timeout64(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a recursive write-lock.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2) bool (__FCALL libc_shared_recursive_rwlock_write_with_timeout64)(struct shared_recursive_rwlock *__restrict self, struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, ...);
/* >> shared_recursive_rwlock_waitread_with_timeout(3), shared_recursive_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2) bool (__FCALL libc_shared_recursive_rwlock_waitread_with_timeout64)(struct shared_recursive_rwlock *__restrict self, struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, ...);
/* >> shared_recursive_rwlock_waitwrite_with_timeout(3), shared_recursive_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2) bool (__FCALL libc_shared_recursive_rwlock_waitwrite_with_timeout64)(struct shared_recursive_rwlock *__restrict self, struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, ...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_KOS_SCHED_SHARED_RECURSIVE_RWLOCK_H */
