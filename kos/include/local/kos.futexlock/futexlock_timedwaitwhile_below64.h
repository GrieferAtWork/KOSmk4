/* HASH CRC-32:0xc8de2cb8 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef __local_futexlock_timedwaitwhile_below64_defined
#if (defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock))
#define __local_futexlock_timedwaitwhile_below64_defined 1
#include <kos/bits/futex.h>
/* Dependency: "lfutexlock64" from "kos.futexlock" */
#ifndef ____localdep_lfutexlock64_defined
#define ____localdep_lfutexlock64_defined 1
#if defined(__CRT_HAVE_lfutexlock64)
/* >> lfutexlock(2)
 * High-level wrapper around the lfutexlockat system call
 * This function behaves identical to the lfutex() system call, except that it takes
 * two futex addresses, where `ulockaddr' is used as a flag specifying that threads may
 * be waiting to be awoken once `LFUTEX_WAKE' is invoked on that memory location, whilst
 * the other futex address is used for the wait-while-condition checking, the same way
 * those checks would also be performed by the `lfutex() system call'
 * @param: command: One of:
 *    - LFUTEX_WAKE:              (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t count)
 *    - LFUTEX_NOP:               (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t ignored)
 *    - LFUTEX_WAIT:              (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutexlock ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:         (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:        (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:        (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_CMPXCH: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `command'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `command' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_lfutexlock64,(__uintptr_t *__ulockaddr, __uintptr_t *__uaddr, __syscall_ulong_t __command, __uintptr_t __val, /*struct timespec64 const *timeout, lfutex_t val2*/...),lfutexlock64,(__ulockaddr,__uaddr,__command,__val,))
#elif defined(__CRT_HAVE_lfutexlock) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> lfutexlock(2)
 * High-level wrapper around the lfutexlockat system call
 * This function behaves identical to the lfutex() system call, except that it takes
 * two futex addresses, where `ulockaddr' is used as a flag specifying that threads may
 * be waiting to be awoken once `LFUTEX_WAKE' is invoked on that memory location, whilst
 * the other futex address is used for the wait-while-condition checking, the same way
 * those checks would also be performed by the `lfutex() system call'
 * @param: command: One of:
 *    - LFUTEX_WAKE:              (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t count)
 *    - LFUTEX_NOP:               (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t ignored)
 *    - LFUTEX_WAIT:              (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutexlock ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:         (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:        (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:        (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_CMPXCH: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `command'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `command' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_lfutexlock64,(__uintptr_t *__ulockaddr, __uintptr_t *__uaddr, __syscall_ulong_t __command, __uintptr_t __val, /*struct timespec64 const *timeout, lfutex_t val2*/...),lfutexlock,(__ulockaddr,__uaddr,__command,__val,))
#elif defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/lfutexlock64.h>
/* >> lfutexlock(2)
 * High-level wrapper around the lfutexlockat system call
 * This function behaves identical to the lfutex() system call, except that it takes
 * two futex addresses, where `ulockaddr' is used as a flag specifying that threads may
 * be waiting to be awoken once `LFUTEX_WAKE' is invoked on that memory location, whilst
 * the other futex address is used for the wait-while-condition checking, the same way
 * those checks would also be performed by the `lfutex() system call'
 * @param: command: One of:
 *    - LFUTEX_WAKE:              (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t count)
 *    - LFUTEX_NOP:               (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t ignored)
 *    - LFUTEX_WAIT:              (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutexlock ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:         (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:        (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:        (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_CMPXCH: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `command'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `command' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
#define __localdep_lfutexlock64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lfutexlock64))
#else /* CUSTOM: lfutexlock64 */
#undef ____localdep_lfutexlock64_defined
#endif /* lfutexlock64... */
#endif /* !____localdep_lfutexlock64_defined */

__NAMESPACE_LOCAL_BEGIN
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__LOCAL_LIBC(futexlock_timedwaitwhile_below64) __ATTR_NONNULL((1, 2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_below64))(__uintptr_t *__ulockaddr,
                                                                              __uintptr_t *__uaddr,
                                                                              __uintptr_t __below_value,
                                                                              struct __timespec64 *__rel_timeout) {
#line 403 "kos/src/libc/magic/kos.futexlock.c"
	return __localdep_lfutexlock64(__ulockaddr, __uaddr, LFUTEX_WAIT_WHILE_BELOW, __below_value, __rel_timeout);
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)) */
#endif /* !__local_futexlock_timedwaitwhile_below64_defined */
