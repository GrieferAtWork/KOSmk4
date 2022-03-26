/* HASH CRC-32:0x9c06336 */
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
#ifndef GUARD_LIBC_AUTO_KOS_SCHED_SHARED_LOCK_H
#define GUARD_LIBC_AUTO_KOS_SCHED_SHARED_LOCK_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/sched/shared-lock.h>

DECL_BEGIN

/* >> shared_lock_acquire(3)
 * Acquire a lock to the given shared_lock. */
INTDEF __BLOCKING NONNULL((1)) void (__FCALL libc_shared_lock_acquire)(struct shared_lock *__restrict self) THROWS(E_WOULDBLOCK, ...);
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING NONNULL((1)) bool (__FCALL libc_shared_lock_acquire_with_timeout)(struct shared_lock *__restrict self, __shared_lock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...);
/* >> shared_lock_waitfor(3)
 * Wait for `self' to become available. */
INTDEF __BLOCKING NONNULL((1)) void (__FCALL libc_shared_lock_waitfor)(struct shared_lock *__restrict self) THROWS(E_WOULDBLOCK, ...);
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING NONNULL((1)) bool (__FCALL libc_shared_lock_waitfor_with_timeout)(struct shared_lock *__restrict self, __shared_lock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...);
#ifndef __KERNEL__
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING NONNULL((1)) bool (__FCALL libc_shared_lock_acquire_with_timeout64)(struct shared_lock *__restrict self, struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, ...);
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTDEF WUNUSED __BLOCKING NONNULL((1)) bool (__FCALL libc_shared_lock_waitfor_with_timeout64)(struct shared_lock *__restrict self, struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, ...);
#endif /* !__KERNEL__ */
#ifdef __KERNEL__
/* >> shared_lock_acquire_nx(3)
 * Acquire a lock to the given shared_lock.
 * @return: true:  Successfully acquired a lock.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTDEF WUNUSED __BLOCKING NONNULL((1)) bool (__FCALL libc_shared_lock_acquire_nx)(struct shared_lock *__restrict self) THROWS(E_WOULDBLOCK, ...);
/* >> shared_lock_acquire_with_timeout_nx(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTDEF WUNUSED __BLOCKING NONNULL((1)) bool (__FCALL libc_shared_lock_acquire_with_timeout_nx)(struct shared_lock *__restrict self, __shared_lock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...);
/* >> shared_lock_waitfor_nx(3)
 * Wait that `self' becomes available.
 * @return: true:  The lock became available.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTDEF WUNUSED __BLOCKING NONNULL((1)) bool (__FCALL libc_shared_lock_waitfor_nx)(struct shared_lock *__restrict self) THROWS(E_WOULDBLOCK, ...);
/* >> shared_lock_waitfor_with_timeout_nx(3)
 * Wait that `self' becomes available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTDEF WUNUSED __BLOCKING NONNULL((1)) bool (__FCALL libc_shared_lock_waitfor_with_timeout_nx)(struct shared_lock *__restrict self, __shared_lock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...);
#endif /* __KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_KOS_SCHED_SHARED_LOCK_H */
