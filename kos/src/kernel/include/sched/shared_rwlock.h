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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SHARED_RWLOCK_H
#define GUARD_KERNEL_INCLUDE_SCHED_SHARED_RWLOCK_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/signal.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#include <hybrid/byteorder.h>

#include <kos/sched/shared-rwlock.h>

#ifdef __CC__
DECL_BEGIN

FUNDEF BLOCKING NOCONNECT NONNULL((1)) void FCALL shared_rwlock_write(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_read_nx)(struct shared_rwlock *__restrict self);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_write_nx)(struct shared_rwlock *__restrict self);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL FCALL shared_rwlock_read_with_timeout(struct shared_rwlock *__restrict self, ktime_t abs_timeout) THROWS(E_WOULDBLOCK);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL FCALL shared_rwlock_write_with_timeout(struct shared_rwlock *__restrict self, ktime_t abs_timeout) THROWS(E_WOULDBLOCK);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_read_with_timeout_nx)(struct shared_rwlock *__restrict self, ktime_t abs_timeout);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_write_with_timeout_nx)(struct shared_rwlock *__restrict self, ktime_t abs_timeout);
FUNDEF BLOCKING NOCONNECT NONNULL((1)) void FCALL shared_rwlock_waitread(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF BLOCKING NOCONNECT NONNULL((1)) void FCALL shared_rwlock_waitwrite(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_waitread_nx)(struct shared_rwlock *__restrict self);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_waitwrite_nx)(struct shared_rwlock *__restrict self);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL FCALL shared_rwlock_waitread_with_timeout(struct shared_rwlock *__restrict self, ktime_t abs_timeout) THROWS(E_WOULDBLOCK);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL FCALL shared_rwlock_waitwrite_with_timeout(struct shared_rwlock *__restrict self, ktime_t abs_timeout) THROWS(E_WOULDBLOCK);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_waitread_with_timeout_nx)(struct shared_rwlock *__restrict self, ktime_t abs_timeout);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_waitwrite_with_timeout_nx)(struct shared_rwlock *__restrict self, ktime_t abs_timeout);
#ifdef __cplusplus
extern "C++" {
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL FCALL shared_rwlock_read(struct shared_rwlock *__restrict self, ktime_t abs_timeout) THROWS(E_WOULDBLOCK) ASMNAME("shared_rwlock_read_with_timeout");
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL FCALL shared_rwlock_write(struct shared_rwlock *__restrict self, ktime_t abs_timeout) THROWS(E_WOULDBLOCK) ASMNAME("shared_rwlock_write_with_timeout");
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_read_nx)(struct shared_rwlock *__restrict self, ktime_t abs_timeout) ASMNAME("shared_rwlock_read_with_timeout_nx");
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_write_nx)(struct shared_rwlock *__restrict self, ktime_t abs_timeout) ASMNAME("shared_rwlock_write_with_timeout_nx");
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL FCALL shared_rwlock_waitread(struct shared_rwlock *__restrict self, ktime_t abs_timeout) THROWS(E_WOULDBLOCK) ASMNAME("shared_rwlock_waitread_with_timeout");
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL FCALL shared_rwlock_waitwrite(struct shared_rwlock *__restrict self, ktime_t abs_timeout) THROWS(E_WOULDBLOCK) ASMNAME("shared_rwlock_waitwrite_with_timeout");
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_waitread_nx)(struct shared_rwlock *__restrict self, ktime_t abs_timeout) ASMNAME("shared_rwlock_waitread_with_timeout_nx");
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_waitwrite_nx)(struct shared_rwlock *__restrict self, ktime_t abs_timeout) ASMNAME("shared_rwlock_waitwrite_with_timeout_nx");
} /* extern "C++" */
#endif /* __cplusplus */

/* NOTE: The lock is always upgraded, but when `FALSE' is returned, no lock
 *       may  have been  held temporarily,  meaning that  the caller should
 *       re-load local copies of affected resources. */
LOCAL BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL
(FCALL shared_rwlock_upgrade)(struct shared_rwlock *__restrict self)
		THROWS(E_WOULDBLOCK);

/* NOTE: The lock is always upgraded for `return != 0', but when `2' is returned,
 *       no lock may have been held  temporarily, meaning that the caller  should
 *       re-load local copies of affected resources.
 * NOTE: When `0' is returned, the original read-lock created by the caller has
 *       already been released. */
LOCAL NOCONNECT NONNULL((1)) unsigned int
NOTHROW(FCALL shared_rwlock_upgrade_nx)(struct shared_rwlock *__restrict self);

#if !defined(__INTELLISENSE__)
/* NOTE: The lock is always upgraded, but when `FALSE' is returned, no lock
 *       may  have been  held temporarily,  meaning that  the caller should
 *       re-load local copies of affected resources. */
LOCAL BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL
(FCALL shared_rwlock_upgrade)(struct shared_rwlock *__restrict self)
		THROWS(E_WOULDBLOCK) {
	if (shared_rwlock_tryupgrade(self))
		return 1;
	shared_rwlock_endread(self);
	shared_rwlock_write(self);
	return 0;
}

/* NOTE: The lock is always upgraded for `return != 0', but when `2' is returned,
 *       no lock may have been held  temporarily, meaning that the caller  should
 *       re-load local copies of affected resources.
 * NOTE: When `0' is returned, the original read-lock created by the caller has
 *       already been released. */
LOCAL NOCONNECT NONNULL((1)) unsigned int
NOTHROW(FCALL shared_rwlock_upgrade_nx)(struct shared_rwlock *__restrict self) {
	if (shared_rwlock_tryupgrade(self))
		return 1;
	shared_rwlock_endread(self);
	if (!shared_rwlock_write_nx(self))
		return 0;
	return 2;
}
#endif /* !__INTELLISENSE__ */

__DEFINE_SYNC_RWLOCK(struct shared_rwlock,
                     shared_rwlock_tryread,
                     shared_rwlock_read,
                     shared_rwlock_read_nx,
                     shared_rwlock_endread,
                     shared_rwlock_reading,
                     shared_rwlock_canread,
                     shared_rwlock_trywrite,
                     shared_rwlock_write,
                     shared_rwlock_write_nx,
                     shared_rwlock_endwrite,
                     shared_rwlock_writing,
                     shared_rwlock_canwrite,
                     shared_rwlock_end,
                     shared_rwlock_tryupgrade,
                     shared_rwlock_upgrade,
                     shared_rwlock_upgrade_nx,
                     shared_rwlock_downgrade)

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SHARED_RWLOCK_H */
