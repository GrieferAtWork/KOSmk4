/* HASH CRC-32:0x2c12874b */
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
#ifndef GUARD_LIBC_AUTO_KOS_FUTEX_C
#define GUARD_LIBC_AUTO_KOS_FUTEX_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/kos.futex.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <hybrid/__atomic.h>
#include <kos/asm/futex.h>
/* >> futexlock_wake(3), futexlock_wakeall(3)
 * A more efficient variant of `futex_wake()' that does  nothing
 * if `!(*ulockaddr & LFUTEX_WAIT_LOCK_WAITERS)', and will clear
 * the `LFUTEX_WAIT_LOCK_WAITERS' flag  (in a race-safe  manner)
 * when there are no more waiting threads. */
INTERN ATTR_SECTION(".text.crt.sched.futex") NONNULL((1)) ssize_t
NOTHROW_NCX(LIBCCALL libc_futexlock_wake)(lfutex_t *ulockaddr,
                                          size_t max_wake) {
	if (!(__hybrid_atomic_load(*ulockaddr, __ATOMIC_ACQUIRE) & LFUTEX_WAIT_LOCK_WAITERS))
		return 0; /* No waiting threads. */
	return libc_futex_wakemask(ulockaddr, max_wake, ~(lfutex_t)LFUTEX_WAIT_LOCK_WAITERS, 0);
}
#include <hybrid/__atomic.h>
#include <kos/asm/futex.h>
/* >> futexlock_wake(3), futexlock_wakeall(3)
 * A more efficient variant of `futex_wake()' that does  nothing
 * if `!(*ulockaddr & LFUTEX_WAIT_LOCK_WAITERS)', and will clear
 * the `LFUTEX_WAIT_LOCK_WAITERS' flag  (in a race-safe  manner)
 * when there are no more waiting threads. */
INTERN ATTR_SECTION(".text.crt.sched.futex") NONNULL((1)) ssize_t
NOTHROW_NCX(LIBCCALL libc_futexlock_wakeall)(lfutex_t *ulockaddr) {
#ifndef __OPTIMIZE_SIZE__
	if (!(__hybrid_atomic_load(*ulockaddr, __ATOMIC_ACQUIRE) & LFUTEX_WAIT_LOCK_WAITERS))
		return 0; /* No waiting threads. */
#endif /* !__OPTIMIZE_SIZE__ */
	if (!(__hybrid_atomic_fetchand(*ulockaddr, ~(lfutex_t)LFUTEX_WAIT_LOCK_WAITERS, __ATOMIC_SEQ_CST) & LFUTEX_WAIT_LOCK_WAITERS))
		return 0; /* No waiting threads. */
	return libc_futex_wakeall(ulockaddr);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(futexlock_wake, libc_futexlock_wake);
DEFINE_PUBLIC_ALIAS(futexlock_wakeall, libc_futexlock_wakeall);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_KOS_FUTEX_C */
