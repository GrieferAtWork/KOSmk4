/* HASH CRC-32:0x6b3c17c6 */
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
#ifndef GUARD_LIBC_AUTO_KOS_SCHED_SHARED_RWLOCK_H
#define GUARD_LIBC_AUTO_KOS_SCHED_SHARED_RWLOCK_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/sched/shared-rwlock.h>

DECL_BEGIN

/* >> shared_rwlock_tryread(3)
 * Try to acquire a read-lock to `self' */
INTDEF WUNUSED __NOBLOCK NONNULL((1)) bool NOTHROW(__FCALL libc_shared_rwlock_tryread)(struct shared_rwlock *__restrict self);
/* >> shared_rwlock_trywrite(3)
 * Try to acquire a write-lock to `self' */
INTDEF WUNUSED __NOBLOCK NONNULL((1)) bool NOTHROW(__FCALL libc_shared_rwlock_trywrite)(struct shared_rwlock *__restrict self);
/* >> shared_rwlock_endwrite(3)
 * Release a a write-lock from `self' */
INTDEF __NOBLOCK NONNULL((1)) void NOTHROW(__FCALL libc_shared_rwlock_endwrite)(struct shared_rwlock *__restrict self);
/* >> shared_rwlock_endread(3)
 * Release a read-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
INTDEF __NOBLOCK NONNULL((1)) bool NOTHROW(__FCALL libc_shared_rwlock_endread)(struct shared_rwlock *__restrict self);
/* >> shared_rwlock_end(3)
 * Release a read- or write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
INTDEF __NOBLOCK NONNULL((1)) bool NOTHROW(__FCALL libc_shared_rwlock_end)(struct shared_rwlock *__restrict self);
/* >> shared_rwlock_downgrade(3)
 * Downgrade a write-lock to a read-lock (Always succeeds). */
INTDEF __NOBLOCK NONNULL((1)) void NOTHROW(__FCALL libc_shared_rwlock_downgrade)(struct shared_rwlock *__restrict self);
/* >> shared_rwlock_read(3)
 * Acquire a read-lock to the given shared_rwlock. */
INTDEF __BLOCKING NONNULL((1)) void (__FCALL libc_shared_rwlock_read)(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK, ...);

DECL_END

#endif /* !GUARD_LIBC_AUTO_KOS_SCHED_SHARED_RWLOCK_H */
