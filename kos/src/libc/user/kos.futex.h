/* HASH CRC-32:0x20c01fbb */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_KOS_FUTEX_H
#define GUARD_LIBC_USER_KOS_FUTEX_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/futex.h>

DECL_BEGIN

/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKEMASK, size_t val = count, lfutex_t mask_and, lfutex_t mask_or)
 *    - LFUTEX_NOP:                (lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t val = ignored)
 *    - LFUTEX_WAIT:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutex_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `futex_op' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
INTDEF NONNULL((1)) ssize_t NOTHROW_RPC(LIBCCALL libc_lfutex)(lfutex_t *uaddr, syscall_ulong_t futex_op, lfutex_t val, /*struct timespec const *timeout, lfutex_t val2*/...);
/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKEMASK, size_t val = count, lfutex_t mask_and, lfutex_t mask_or)
 *    - LFUTEX_NOP:                (lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t val = ignored)
 *    - LFUTEX_WAIT:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutex_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `futex_op' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
INTDEF NONNULL((1)) ssize_t NOTHROW_RPC(LIBCCALL libc_lfutex64)(lfutex_t *uaddr, syscall_ulong_t futex_op, lfutex_t val, /*struct timespec64 const *timeout, lfutex_t val2*/...);
/* Wake up to `MAX_WAKE' threads waiting for `*UADDR'
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
INTDEF NONNULL((1)) ssize_t NOTHROW_NCX(LIBCCALL libc_futex_wake)(lfutex_t *uaddr, size_t max_wake);
/* Wake all threads waiting for `*UADDR' (same as `futex_wake(uaddr, (size_t)-1)')
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
INTDEF NONNULL((1)) ssize_t NOTHROW_NCX(LIBCCALL libc_futex_wakeall)(lfutex_t *uaddr);
/* Similar to `futex_wake()', however once there are no more threads that
 * can be awoken, perform the following operation: `*uaddr = (*uaddr & mask_and) | mask_or'
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
INTDEF NONNULL((1)) ssize_t NOTHROW_NCX(LIBCCALL libc_futex_wakemask)(lfutex_t *uaddr, size_t max_wake, lfutex_t mask_and, lfutex_t mask_or);
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_waitwhile)(lfutex_t *uaddr, lfutex_t equal_to_value);
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_waituntil)(lfutex_t *uaddr, lfutex_t not_equal_to_value);
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_above)(lfutex_t *uaddr, lfutex_t above_value);
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_below)(lfutex_t *uaddr, lfutex_t below_value);
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_aboveequal)(lfutex_t *uaddr, lfutex_t above_equal_value);
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_belowequal)(lfutex_t *uaddr, lfutex_t below_equal_value);
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted (*uaddr was still set to new_value) */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_cmpxch)(lfutex_t *uaddr, lfutex_t old_value, lfutex_t new_value);
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted (*uaddr was still set to new_value) */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_waituntil_cmpxch)(lfutex_t *uaddr, lfutex_t old_value, lfutex_t new_value);
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted (*uaddr was still set to new_value) */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_waitlock)(lfutex_t *uaddr);
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_exactbits)(lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask);
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_waituntil_exactbits)(lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask);
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_anybit)(lfutex_t *uaddr, lfutex_t bitmask);
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_allbits)(lfutex_t *uaddr, lfutex_t bitmask);
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile)(lfutex_t *uaddr, lfutex_t equal_to_value, struct timespec const *rel_timeout);
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaituntil)(lfutex_t *uaddr, lfutex_t not_equal_to_value, struct timespec const *rel_timeout);
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_above)(lfutex_t *uaddr, lfutex_t above_value, struct timespec const *rel_timeout);
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_below)(lfutex_t *uaddr, lfutex_t below_value, struct timespec const *rel_timeout);
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_aboveequal)(lfutex_t *uaddr, lfutex_t above_equal_value, struct timespec const *rel_timeout);
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_belowequal)(lfutex_t *uaddr, lfutex_t below_equal_value, struct timespec const *rel_timeout);
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_cmpxch)(lfutex_t *uaddr, lfutex_t old_value, lfutex_t new_value, struct timespec const *rel_timeout);
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaituntil_cmpxch)(lfutex_t *uaddr, lfutex_t old_value, lfutex_t new_value, struct timespec const *rel_timeout);
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaitlock)(lfutex_t *uaddr, struct timespec const *rel_timeout);
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_exactbits)(lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask, struct timespec const *rel_timeout);
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaituntil_exactbits)(lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask, struct timespec const *rel_timeout);
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_anybit)(lfutex_t *uaddr, lfutex_t bitmask, struct timespec const *rel_timeout);
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_allbits)(lfutex_t *uaddr, lfutex_t bitmask, struct timespec const *rel_timeout);
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile64)(lfutex_t *uaddr, lfutex_t equal_to_value, struct timespec64 const *rel_timeout);
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaituntil64)(lfutex_t *uaddr, lfutex_t not_equal_to_value, struct timespec64 const *rel_timeout);
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_above64)(lfutex_t *uaddr, lfutex_t above_value, struct timespec64 const *rel_timeout);
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_below64)(lfutex_t *uaddr, lfutex_t below_value, struct timespec64 const *rel_timeout);
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_aboveequal64)(lfutex_t *uaddr, lfutex_t above_equal_value, struct timespec64 const *rel_timeout);
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_belowequal64)(lfutex_t *uaddr, lfutex_t below_equal_value, struct timespec64 const *rel_timeout);
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_cmpxch64)(lfutex_t *uaddr, lfutex_t old_value, lfutex_t new_value, struct timespec64 const *rel_timeout);
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaituntil_cmpxch64)(lfutex_t *uaddr, lfutex_t old_value, lfutex_t new_value, struct timespec64 const *rel_timeout);
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaitlock64)(lfutex_t *uaddr, struct timespec64 const *rel_timeout);
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_exactbits64)(lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask, struct timespec64 const *rel_timeout);
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaituntil_exactbits64)(lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask, struct timespec64 const *rel_timeout);
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_anybit64)(lfutex_t *uaddr, lfutex_t bitmask, struct timespec64 const *rel_timeout);
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_allbits64)(lfutex_t *uaddr, lfutex_t bitmask, struct timespec64 const *rel_timeout);
/* Get/Set the number of times to spin the following futex operations without
 * entering kernel-space, setting waiter-bits, and entering sleep mode:
 *   - LFUTEX_WAIT_WHILE: SPIN({ if (*uaddr != val) DONE(); });
 *   - LFUTEX_WAIT_UNTIL: SPIN({ if (*uaddr == val) DONE(); });
 *   - ...
 * Futex spinning improves performance by bypassing expensive blocking operations
 * when associated locks are often only held for a couple of moments at a time.
 * Take for example `lfutex(LFUTEX_WAIT_WHILE)' (or preferrably `futex_waitwhile()'), which
 * is wrapped like this:
 * >> unsigned int spins;
 * >> spins = futex_getspin();
 * >> while (spins--) {
 * >> 	if (*uaddr != val)
 * >> 		return 0;
 * >> 	if (sched_yield())
 * >> 		break; // If there was nothing to switch to, sched_yield() returns non-zero
 * >> }
 * >> return lfutex(uaddr, LFUTEX_WAIT_WHILE, val, (struct timespec const *)NULL);
 * Upon startup, `futex_getspin()' is pre-initialized to `4'.
 * @return: * : The current (get) / old (set) spin value */
INTDEF WUNUSED unsigned int NOTHROW(LIBCCALL libc_futex_getspin)(void);
/* Get/Set the number of times to spin the following futex operations without
 * entering kernel-space, setting waiter-bits, and entering sleep mode:
 *   - LFUTEX_WAIT_WHILE: SPIN({ if (*uaddr != val) DONE(); });
 *   - LFUTEX_WAIT_UNTIL: SPIN({ if (*uaddr == val) DONE(); });
 *   - ...
 * Futex spinning improves performance by bypassing expensive blocking operations
 * when associated locks are often only held for a couple of moments at a time.
 * Take for example `lfutex(LFUTEX_WAIT_WHILE)' (or preferrably `futex_waitwhile()'), which
 * is wrapped like this:
 * >> unsigned int spins;
 * >> spins = futex_getspin();
 * >> while (spins--) {
 * >> 	if (*uaddr != val)
 * >> 		return 0;
 * >> 	if (sched_yield())
 * >> 		break; // If there was nothing to switch to, sched_yield() returns non-zero
 * >> }
 * >> return lfutex(uaddr, LFUTEX_WAIT_WHILE, val, (struct timespec const *)NULL);
 * Upon startup, `futex_getspin()' is pre-initialized to `4'.
 * @return: * : The current (get) / old (set) spin value */
INTDEF unsigned int NOTHROW(LIBCCALL libc_futex_setspin)(unsigned int new_spin);

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_FUTEX_H */
