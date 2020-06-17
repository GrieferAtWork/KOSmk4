/* HASH CRC-32:0x270f6224 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_KOS_FUTEXLOCK_C
#define GUARD_LIBC_AUTO_DOSABI_KOS_FUTEXLOCK_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/kos.futexlock.h"

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
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) ssize_t
NOTHROW_RPC(VLIBDCALL libd_lfutexlock)(lfutex_t *ulockaddr,
                                       lfutex_t *uaddr,
                                       syscall_ulong_t futex_op,
                                       lfutex_t val,
                                       ...) {
	va_list args;
	void *v0;
	uintptr_t v1_uintptr_t;
	va_start(args, val);
	v0           = va_arg(args, void *);
	v1_uintptr_t = va_arg(args, uintptr_t);
	va_end(args);
	return libc_lfutexlock(ulockaddr, uaddr, futex_op, val, v0, v1_uintptr_t);
}
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
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) ssize_t
NOTHROW_RPC(VLIBDCALL libd_lfutexlock64)(lfutex_t *ulockaddr,
                                         lfutex_t *uaddr,
                                         syscall_ulong_t futex_op,
                                         lfutex_t val,
                                         ...) {
	va_list args;
	void *v0;
	uintptr_t v1_uintptr_t;
	va_start(args, val);
	v0           = va_arg(args, void *);
	v1_uintptr_t = va_arg(args, uintptr_t);
	va_end(args);
	return libc_lfutexlock64(ulockaddr, uaddr, futex_op, val, v0, v1_uintptr_t);
}
/* A more efficient variant of `futex_wake()' that can be used to wake up threads waiting
 * on some given futex-lock. - This method of waking is faster, since it doesn't invoke a
 * system call when no thread is waiting on the given lock */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1)) ssize_t
NOTHROW_NCX(LIBDCALL libd_futexlock_wake)(lfutex_t *ulockaddr,
                                          size_t max_wake) {
	return libc_futexlock_wake(ulockaddr, max_wake);
}
/* A more efficient variant of `futex_wake()' that can be used to wake up threads waiting
 * on some given futex-lock. - This method of waking is faster, since it doesn't invoke a
 * system call when no thread is waiting on the given lock */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1)) ssize_t
NOTHROW_NCX(LIBDCALL libd_futexlock_wakeall)(lfutex_t *ulockaddr) {
	return libc_futexlock_wakeall(ulockaddr);
}
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_waitwhile)(lfutex_t *ulockaddr,
                                               lfutex_t *uaddr,
                                               lfutex_t equal_to_value) {
	return libc_futexlock_waitwhile(ulockaddr, uaddr, equal_to_value);
}
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_waituntil)(lfutex_t *ulockaddr,
                                               lfutex_t *uaddr,
                                               lfutex_t not_equal_to_value) {
	return libc_futexlock_waituntil(ulockaddr, uaddr, not_equal_to_value);
}
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_waitwhile_above)(lfutex_t *ulockaddr,
                                                     lfutex_t *uaddr,
                                                     lfutex_t above_value) {
	return libc_futexlock_waitwhile_above(ulockaddr, uaddr, above_value);
}
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_waitwhile_below)(lfutex_t *ulockaddr,
                                                     lfutex_t *uaddr,
                                                     lfutex_t below_value) {
	return libc_futexlock_waitwhile_below(ulockaddr, uaddr, below_value);
}
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_waitwhile_aboveequal)(lfutex_t *ulockaddr,
                                                          lfutex_t *uaddr,
                                                          lfutex_t above_equal_value) {
	return libc_futexlock_waitwhile_aboveequal(ulockaddr, uaddr, above_equal_value);
}
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_waitwhile_belowequal)(lfutex_t *ulockaddr,
                                                          lfutex_t *uaddr,
                                                          lfutex_t below_equal_value) {
	return libc_futexlock_waitwhile_belowequal(ulockaddr, uaddr, below_equal_value);
}
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted (*uaddr was still set to new_value) */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_waitwhile_cmpxch)(lfutex_t *ulockaddr,
                                                      lfutex_t *uaddr,
                                                      lfutex_t old_value,
                                                      lfutex_t new_value) {
	return libc_futexlock_waitwhile_cmpxch(ulockaddr, uaddr, old_value, new_value);
}
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted (*uaddr was still set to new_value) */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_waituntil_cmpxch)(lfutex_t *ulockaddr,
                                                      lfutex_t *uaddr,
                                                      lfutex_t old_value,
                                                      lfutex_t new_value) {
	return libc_futexlock_waituntil_cmpxch(ulockaddr, uaddr, old_value, new_value);
}
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted (*uaddr was still set to new_value) */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_waitlock)(lfutex_t *ulockaddr,
                                              lfutex_t *uaddr) {
	return libc_futexlock_waitlock(ulockaddr, uaddr);
}
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_waitwhile_exactbits)(lfutex_t *ulockaddr,
                                                         lfutex_t *uaddr,
                                                         lfutex_t bitmask,
                                                         lfutex_t setmask) {
	return libc_futexlock_waitwhile_exactbits(ulockaddr, uaddr, bitmask, setmask);
}
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_waituntil_exactbits)(lfutex_t *ulockaddr,
                                                         lfutex_t *uaddr,
                                                         lfutex_t bitmask,
                                                         lfutex_t setmask) {
	return libc_futexlock_waituntil_exactbits(ulockaddr, uaddr, bitmask, setmask);
}
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_waitwhile_anybit)(lfutex_t *ulockaddr,
                                                      lfutex_t *uaddr,
                                                      lfutex_t bitmask) {
	return libc_futexlock_waitwhile_anybit(ulockaddr, uaddr, bitmask);
}
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_waitwhile_allbits)(lfutex_t *ulockaddr,
                                                       lfutex_t *uaddr,
                                                       lfutex_t bitmask) {
	return libc_futexlock_waitwhile_allbits(ulockaddr, uaddr, bitmask);
}
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaitwhile)(lfutex_t *ulockaddr,
                                                    lfutex_t *uaddr,
                                                    lfutex_t equal_to_value,
                                                    struct timespec const *rel_timeout) {
	return libc_futexlock_timedwaitwhile(ulockaddr, uaddr, equal_to_value, rel_timeout);
}
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaituntil)(lfutex_t *ulockaddr,
                                                    lfutex_t *uaddr,
                                                    lfutex_t not_equal_to_value,
                                                    struct timespec const *rel_timeout) {
	return libc_futexlock_timedwaituntil(ulockaddr, uaddr, not_equal_to_value, rel_timeout);
}
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaitwhile_above)(lfutex_t *ulockaddr,
                                                          lfutex_t *uaddr,
                                                          lfutex_t above_value,
                                                          struct timespec const *rel_timeout) {
	return libc_futexlock_timedwaitwhile_above(ulockaddr, uaddr, above_value, rel_timeout);
}
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaitwhile_below)(lfutex_t *ulockaddr,
                                                          lfutex_t *uaddr,
                                                          lfutex_t below_value,
                                                          struct timespec const *rel_timeout) {
	return libc_futexlock_timedwaitwhile_below(ulockaddr, uaddr, below_value, rel_timeout);
}
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaitwhile_aboveequal)(lfutex_t *ulockaddr,
                                                               lfutex_t *uaddr,
                                                               lfutex_t above_equal_value,
                                                               struct timespec const *rel_timeout) {
	return libc_futexlock_timedwaitwhile_aboveequal(ulockaddr, uaddr, above_equal_value, rel_timeout);
}
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaitwhile_belowequal)(lfutex_t *ulockaddr,
                                                               lfutex_t *uaddr,
                                                               lfutex_t below_equal_value,
                                                               struct timespec const *rel_timeout) {
	return libc_futexlock_timedwaitwhile_belowequal(ulockaddr, uaddr, below_equal_value, rel_timeout);
}
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaitwhile_cmpxch)(lfutex_t *ulockaddr,
                                                           lfutex_t *uaddr,
                                                           lfutex_t old_value,
                                                           lfutex_t new_value,
                                                           struct timespec const *rel_timeout) {
	return libc_futexlock_timedwaitwhile_cmpxch(ulockaddr, uaddr, old_value, new_value, rel_timeout);
}
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaituntil_cmpxch)(lfutex_t *ulockaddr,
                                                           lfutex_t *uaddr,
                                                           lfutex_t old_value,
                                                           lfutex_t new_value,
                                                           struct timespec const *rel_timeout) {
	return libc_futexlock_timedwaituntil_cmpxch(ulockaddr, uaddr, old_value, new_value, rel_timeout);
}
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaitlock)(lfutex_t *ulockaddr,
                                                   lfutex_t *uaddr,
                                                   struct timespec const *rel_timeout) {
	return libc_futexlock_timedwaitlock(ulockaddr, uaddr, rel_timeout);
}
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaitwhile_exactbits)(lfutex_t *ulockaddr,
                                                              lfutex_t *uaddr,
                                                              lfutex_t bitmask,
                                                              lfutex_t setmask,
                                                              struct timespec const *rel_timeout) {
	return libc_futexlock_timedwaitwhile_exactbits(ulockaddr, uaddr, bitmask, setmask, rel_timeout);
}
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaituntil_exactbits)(lfutex_t *ulockaddr,
                                                              lfutex_t *uaddr,
                                                              lfutex_t bitmask,
                                                              lfutex_t setmask,
                                                              struct timespec const *rel_timeout) {
	return libc_futexlock_timedwaituntil_exactbits(ulockaddr, uaddr, bitmask, setmask, rel_timeout);
}
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaitwhile_anybit)(lfutex_t *ulockaddr,
                                                           lfutex_t *uaddr,
                                                           lfutex_t bitmask,
                                                           struct timespec const *rel_timeout) {
	return libc_futexlock_timedwaitwhile_anybit(ulockaddr, uaddr, bitmask, rel_timeout);
}
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaitwhile_allbits)(lfutex_t *ulockaddr,
                                                            lfutex_t *uaddr,
                                                            lfutex_t bitmask,
                                                            struct timespec const *rel_timeout) {
	return libc_futexlock_timedwaitwhile_allbits(ulockaddr, uaddr, bitmask, rel_timeout);
}
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaitwhile64)(lfutex_t *ulockaddr,
                                                      lfutex_t *uaddr,
                                                      lfutex_t equal_to_value,
                                                      struct timespec64 const *rel_timeout) {
	return libc_futexlock_timedwaitwhile64(ulockaddr, uaddr, equal_to_value, rel_timeout);
}
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaituntil64)(lfutex_t *ulockaddr,
                                                      lfutex_t *uaddr,
                                                      lfutex_t not_equal_to_value,
                                                      struct timespec64 const *rel_timeout) {
	return libc_futexlock_timedwaituntil64(ulockaddr, uaddr, not_equal_to_value, rel_timeout);
}
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaitwhile_above64)(lfutex_t *ulockaddr,
                                                            lfutex_t *uaddr,
                                                            lfutex_t above_value,
                                                            struct timespec64 const *rel_timeout) {
	return libc_futexlock_timedwaitwhile_above64(ulockaddr, uaddr, above_value, rel_timeout);
}
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaitwhile_below64)(lfutex_t *ulockaddr,
                                                            lfutex_t *uaddr,
                                                            lfutex_t below_value,
                                                            struct timespec64 const *rel_timeout) {
	return libc_futexlock_timedwaitwhile_below64(ulockaddr, uaddr, below_value, rel_timeout);
}
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaitwhile_aboveequal64)(lfutex_t *ulockaddr,
                                                                 lfutex_t *uaddr,
                                                                 lfutex_t above_equal_value,
                                                                 struct timespec64 const *rel_timeout) {
	return libc_futexlock_timedwaitwhile_aboveequal64(ulockaddr, uaddr, above_equal_value, rel_timeout);
}
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaitwhile_belowequal64)(lfutex_t *ulockaddr,
                                                                 lfutex_t *uaddr,
                                                                 lfutex_t below_equal_value,
                                                                 struct timespec64 const *rel_timeout) {
	return libc_futexlock_timedwaitwhile_belowequal64(ulockaddr, uaddr, below_equal_value, rel_timeout);
}
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaitwhile_cmpxch64)(lfutex_t *ulockaddr,
                                                             lfutex_t *uaddr,
                                                             lfutex_t old_value,
                                                             lfutex_t new_value,
                                                             struct timespec64 const *rel_timeout) {
	return libc_futexlock_timedwaitwhile_cmpxch64(ulockaddr, uaddr, old_value, new_value, rel_timeout);
}
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaituntil_cmpxch64)(lfutex_t *ulockaddr,
                                                             lfutex_t *uaddr,
                                                             lfutex_t old_value,
                                                             lfutex_t new_value,
                                                             struct timespec64 const *rel_timeout) {
	return libc_futexlock_timedwaituntil_cmpxch64(ulockaddr, uaddr, old_value, new_value, rel_timeout);
}
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaitlock64)(lfutex_t *ulockaddr,
                                                     lfutex_t *uaddr,
                                                     struct timespec64 const *rel_timeout) {
	return libc_futexlock_timedwaitlock64(ulockaddr, uaddr, rel_timeout);
}
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaitwhile_exactbits64)(lfutex_t *ulockaddr,
                                                                lfutex_t *uaddr,
                                                                lfutex_t bitmask,
                                                                lfutex_t setmask,
                                                                struct timespec64 const *rel_timeout) {
	return libc_futexlock_timedwaitwhile_exactbits64(ulockaddr, uaddr, bitmask, setmask, rel_timeout);
}
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaituntil_exactbits64)(lfutex_t *ulockaddr,
                                                                lfutex_t *uaddr,
                                                                lfutex_t bitmask,
                                                                lfutex_t setmask,
                                                                struct timespec64 const *rel_timeout) {
	return libc_futexlock_timedwaituntil_exactbits64(ulockaddr, uaddr, bitmask, setmask, rel_timeout);
}
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaitwhile_anybit64)(lfutex_t *ulockaddr,
                                                             lfutex_t *uaddr,
                                                             lfutex_t bitmask,
                                                             struct timespec64 const *rel_timeout) {
	return libc_futexlock_timedwaitwhile_anybit64(ulockaddr, uaddr, bitmask, rel_timeout);
}
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.dos.sched.futexlock") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_futexlock_timedwaitwhile_allbits64)(lfutex_t *ulockaddr,
                                                              lfutex_t *uaddr,
                                                              lfutex_t bitmask,
                                                              struct timespec64 const *rel_timeout) {
	return libc_futexlock_timedwaitwhile_allbits64(ulockaddr, uaddr, bitmask, rel_timeout);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$lfutexlock, libd_lfutexlock);
DEFINE_PUBLIC_ALIAS(DOS$lfutexlock64, libd_lfutexlock64);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_wake, libd_futexlock_wake);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_wakeall, libd_futexlock_wakeall);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_waitwhile, libd_futexlock_waitwhile);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_waituntil, libd_futexlock_waituntil);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_waitwhile_above, libd_futexlock_waitwhile_above);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_waitwhile_below, libd_futexlock_waitwhile_below);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_waitwhile_aboveequal, libd_futexlock_waitwhile_aboveequal);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_waitwhile_belowequal, libd_futexlock_waitwhile_belowequal);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_waitwhile_cmpxch, libd_futexlock_waitwhile_cmpxch);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_waituntil_cmpxch, libd_futexlock_waituntil_cmpxch);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_waitlock, libd_futexlock_waitlock);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_waitwhile_exactbits, libd_futexlock_waitwhile_exactbits);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_waituntil_exactbits, libd_futexlock_waituntil_exactbits);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_waitwhile_anybit, libd_futexlock_waitwhile_anybit);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_waitwhile_allbits, libd_futexlock_waitwhile_allbits);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaitwhile, libd_futexlock_timedwaitwhile);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaituntil, libd_futexlock_timedwaituntil);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaitwhile_above, libd_futexlock_timedwaitwhile_above);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaitwhile_below, libd_futexlock_timedwaitwhile_below);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaitwhile_aboveequal, libd_futexlock_timedwaitwhile_aboveequal);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaitwhile_belowequal, libd_futexlock_timedwaitwhile_belowequal);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaitwhile_cmpxch, libd_futexlock_timedwaitwhile_cmpxch);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaituntil_cmpxch, libd_futexlock_timedwaituntil_cmpxch);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaitlock, libd_futexlock_timedwaitlock);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaitwhile_exactbits, libd_futexlock_timedwaitwhile_exactbits);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaituntil_exactbits, libd_futexlock_timedwaituntil_exactbits);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaitwhile_anybit, libd_futexlock_timedwaitwhile_anybit);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaitwhile_allbits, libd_futexlock_timedwaitwhile_allbits);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaitwhile64, libd_futexlock_timedwaitwhile64);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaituntil64, libd_futexlock_timedwaituntil64);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaitwhile_above64, libd_futexlock_timedwaitwhile_above64);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaitwhile_below64, libd_futexlock_timedwaitwhile_below64);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaitwhile_aboveequal64, libd_futexlock_timedwaitwhile_aboveequal64);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaitwhile_belowequal64, libd_futexlock_timedwaitwhile_belowequal64);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaitwhile_cmpxch64, libd_futexlock_timedwaitwhile_cmpxch64);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaituntil_cmpxch64, libd_futexlock_timedwaituntil_cmpxch64);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaitlock64, libd_futexlock_timedwaitlock64);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaitwhile_exactbits64, libd_futexlock_timedwaitwhile_exactbits64);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaituntil_exactbits64, libd_futexlock_timedwaituntil_exactbits64);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaitwhile_anybit64, libd_futexlock_timedwaitwhile_anybit64);
DEFINE_PUBLIC_ALIAS(DOS$futexlock_timedwaitwhile_allbits64, libd_futexlock_timedwaitwhile_allbits64);

#endif /* !GUARD_LIBC_AUTO_DOSABI_KOS_FUTEXLOCK_C */
