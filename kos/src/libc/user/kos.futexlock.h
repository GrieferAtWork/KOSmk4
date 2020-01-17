/* HASH CRC-32:0x4c43ebac */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_KOS_FUTEXLOCK_H
#define GUARD_LIBC_USER_KOS_FUTEXLOCK_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/futexlock.h>

DECL_BEGIN

/* >> lfutexlock(3)
 * Helper function to implement the behavior of `lfutexlockexpr()' for only a single futex.
 * This function behaves identical to the lfutex() system call, except that it takes
 * two futex addresses, where `ulockaddr' is used with `LFUTEX_WAIT_LOCK_WAITERS' to cache if
 * there are threads that may be waiting to be awoken once `LFUTEX_WAKE' is invoked on that
 * memory location (aka. `futexlock_wakeall(ulockaddr)'), whilst the other futex address
 * (i.e. `uaddr') is used for the wait-while-condition checking, the same way those checks
 * would also be performed by the `lfutex() system call'
 * @param: futex_op: One of:
 *    - LFUTEX_NOP:                (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t val = ignored)
 *    - LFUTEX_WAIT:               (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutex_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `futex_op' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_RPC(LIBCCALL libc_lfutexlock)(lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t futex_op, lfutex_t val, /*struct timespec const *timeout, lfutex_t val2*/...);
/* >> lfutexlock(3)
 * Helper function to implement the behavior of `lfutexlockexpr()' for only a single futex.
 * This function behaves identical to the lfutex() system call, except that it takes
 * two futex addresses, where `ulockaddr' is used with `LFUTEX_WAIT_LOCK_WAITERS' to cache if
 * there are threads that may be waiting to be awoken once `LFUTEX_WAKE' is invoked on that
 * memory location (aka. `futexlock_wakeall(ulockaddr)'), whilst the other futex address
 * (i.e. `uaddr') is used for the wait-while-condition checking, the same way those checks
 * would also be performed by the `lfutex() system call'
 * @param: futex_op: One of:
 *    - LFUTEX_NOP:                (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t val = ignored)
 *    - LFUTEX_WAIT:               (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutex_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `futex_op' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_RPC(LIBCCALL libc_lfutexlock64)(lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t futex_op, lfutex_t val, /*struct timespec64 const *timeout, lfutex_t val2*/...);
/* A more efficient variant of `futex_wake()' that can be used to wake up threads waiting
 * on some given futex-lock. - This method of waking is faster, since it doesn't invoke a
 * system call when no thread is waiting on the given lock */
INTDEF NONNULL((1)) ssize_t NOTHROW_NCX(LIBCCALL libc_futexlock_wake)(lfutex_t *ulockaddr, size_t max_wake);
/* A more efficient variant of `futex_wake()' that can be used to wake up threads waiting
 * on some given futex-lock. - This method of waking is faster, since it doesn't invoke a
 * system call when no thread is waiting on the given lock */
INTDEF NONNULL((1)) ssize_t NOTHROW_NCX(LIBCCALL libc_futexlock_wakeall)(lfutex_t *ulockaddr);
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t equal_to_value);
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_waituntil)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t not_equal_to_value);
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_above)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t above_value);
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_below)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t below_value);
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_aboveequal)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t above_equal_value);
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_belowequal)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t below_equal_value);
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted (*uaddr was still set to new_value) */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_cmpxch)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t old_value, lfutex_t new_value);
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted (*uaddr was still set to new_value) */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_waituntil_cmpxch)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t old_value, lfutex_t new_value);
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted (*uaddr was still set to new_value) */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_waitlock)(lfutex_t *ulockaddr, lfutex_t *uaddr);
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_exactbits)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask);
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_waituntil_exactbits)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask);
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_anybit)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t bitmask);
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_allbits)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t bitmask);
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t equal_to_value, struct timespec const *rel_timeout);
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaituntil)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t not_equal_to_value, struct timespec const *rel_timeout);
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_above)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t above_value, struct timespec const *rel_timeout);
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_below)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t below_value, struct timespec const *rel_timeout);
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_aboveequal)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t above_equal_value, struct timespec const *rel_timeout);
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_belowequal)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t below_equal_value, struct timespec const *rel_timeout);
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_cmpxch)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t old_value, lfutex_t new_value, struct timespec const *rel_timeout);
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaituntil_cmpxch)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t old_value, lfutex_t new_value, struct timespec const *rel_timeout);
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitlock)(lfutex_t *ulockaddr, lfutex_t *uaddr, struct timespec const *rel_timeout);
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_exactbits)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask, struct timespec const *rel_timeout);
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaituntil_exactbits)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask, struct timespec const *rel_timeout);
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_anybit)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t bitmask, struct timespec const *rel_timeout);
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_allbits)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t bitmask, struct timespec const *rel_timeout);
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile64)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t equal_to_value, struct timespec64 const *rel_timeout);
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaituntil64)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t not_equal_to_value, struct timespec64 const *rel_timeout);
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_above64)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t above_value, struct timespec64 const *rel_timeout);
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_below64)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t below_value, struct timespec64 const *rel_timeout);
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_aboveequal64)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t above_equal_value, struct timespec64 const *rel_timeout);
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_belowequal64)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t below_equal_value, struct timespec64 const *rel_timeout);
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_cmpxch64)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t old_value, lfutex_t new_value, struct timespec64 const *rel_timeout);
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaituntil_cmpxch64)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t old_value, lfutex_t new_value, struct timespec64 const *rel_timeout);
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitlock64)(lfutex_t *ulockaddr, lfutex_t *uaddr, struct timespec64 const *rel_timeout);
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_exactbits64)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask, struct timespec64 const *rel_timeout);
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaituntil_exactbits64)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask, struct timespec64 const *rel_timeout);
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_anybit64)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t bitmask, struct timespec64 const *rel_timeout);
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_allbits64)(lfutex_t *ulockaddr, lfutex_t *uaddr, lfutex_t bitmask, struct timespec64 const *rel_timeout);

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_FUTEXLOCK_H */
