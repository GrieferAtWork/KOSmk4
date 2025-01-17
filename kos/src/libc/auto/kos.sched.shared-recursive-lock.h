/* HASH CRC-32:0x9cb2a229 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_KOS_SCHED_SHARED_RECURSIVE_LOCK_H
#define GUARD_LIBC_AUTO_KOS_SCHED_SHARED_RECURSIVE_LOCK_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/sched/shared-recursive-lock.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> shared_recursive_lock_tryacquire(3)
 * Try to acquire a recursive lock to `self' */
INTDEF WUNUSED __NOBLOCK ATTR_INOUT(1) bool NOTHROW(__FCALL libc_shared_recursive_lock_tryacquire)(struct shared_recursive_lock *__restrict self);
/* >> shared_recursive_lock_release_ex(3)
 * Release a recursive  lock from  `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
INTDEF __NOBLOCK ATTR_INOUT(1) bool NOTHROW(__FCALL libc_shared_recursive_lock_release_ex)(struct shared_recursive_lock *__restrict self);
/* >> shared_recursive_lock_acquire(3)
 * Acquire a recursive lock to the given shared_recursive_lock. */
INTDEF __BLOCKING ATTR_INOUT(1) void (__FCALL libc_shared_recursive_lock_acquire)(struct shared_recursive_lock *__restrict self) THROWS(E_WOULDBLOCK, E_INTERRUPT);
/* >> shared_recursive_lock_acquire_with_timeout(3), shared_recursive_lock_acquire_with_timeout64(3)
 * Acquire a recursive lock to the given shared_recursive_lock.
 * @return: true:  Successfully acquired a recursive lock.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING ATTR_INOUT(1) bool (__FCALL libc_shared_recursive_lock_acquire_with_timeout)(struct shared_recursive_lock *__restrict self, __shared_lock_timespec abs_timeout) THROWS(E_WOULDBLOCK, E_INTERRUPT);
/* >> shared_recursive_lock_waitfor(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks */
INTDEF __BLOCKING ATTR_INOUT(1) void (__FCALL libc_shared_recursive_lock_waitfor)(struct shared_recursive_lock *__restrict self) THROWS(E_WOULDBLOCK, E_INTERRUPT);
/* >> shared_recursive_lock_waitfor_with_timeout(3), shared_recursive_lock_waitfor_with_timeout64(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks
 * @return: true:  A lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING ATTR_INOUT(1) bool (__FCALL libc_shared_recursive_lock_waitfor_with_timeout)(struct shared_recursive_lock *__restrict self, __shared_lock_timespec abs_timeout) THROWS(E_WOULDBLOCK, E_INTERRUPT);
/* >> shared_recursive_lock_acquire_with_timeout(3), shared_recursive_lock_acquire_with_timeout64(3)
 * Acquire a recursive lock to the given shared_recursive_lock.
 * @return: true:  Successfully acquired a recursive lock.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2) bool (__FCALL libc_shared_recursive_lock_acquire_with_timeout64)(struct shared_recursive_lock *__restrict self, struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, E_INTERRUPT);
/* >> shared_recursive_lock_waitfor_with_timeout(3), shared_recursive_lock_waitfor_with_timeout64(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks
 * @return: true:  A lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2) bool (__FCALL libc_shared_recursive_lock_waitfor_with_timeout64)(struct shared_recursive_lock *__restrict self, struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, E_INTERRUPT);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_KOS_SCHED_SHARED_RECURSIVE_LOCK_H */
