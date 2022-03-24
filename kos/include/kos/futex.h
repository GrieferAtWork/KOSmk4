/* HASH CRC-32:0xe25dc7a9 */
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
#ifndef _KOS_FUTEX_H
#define _KOS_FUTEX_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <kos/asm/futex.h>
#include <bits/types.h>
#include <bits/os/timespec.h>
#include <hybrid/__atomic.h>
#ifndef __cplusplus
#include <hybrid/pp/__va_nargs.h>
#endif /* !__cplusplus */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __lfutex_t_defined
#define __lfutex_t_defined
typedef __uintptr_t lfutex_t;
#endif /* !__lfutex_t_defined */

/*
 * `lfutex() and select()' (or `poll()')
 *
 * On  KOS,  it  is  fairly  simple  to  use  any  of  the  available
 * `LFUTEX_WAIT_*' operations in conjunction with a call to `poll()'.
 *
 * Other than this, there exists 2  ways of polling for futex  objects
 * in parallel to polling any other  type of file descriptor, as  well
 * polling  for sleeping child processes (either through use of a file
 * descriptor created using `pidfd_open(pid) (similar to `signalfd()',
 * but  may be used to wait for processes  in a way that is similar to
 * the waitpid() function)', or through use of `kpoll()').
 *
 * - Using the `kpoll()' system call, which  allows for the use of  poll
 *   descriptors that describe any kind of user-space-visible handle  on
 *   which  a given process  can wait (a  regular `fd_t' (using `POLLIN|
 *   POLLOUT|...'),  a  `pid_t'  (using `waitpid()'),  or  an `lfutex_t'
 *   (using any of  the `LFUTEX_WAIT_*' operators  that are  available))
 *   When targeting KOS specifically, this is the preferred way of going
 *   about passively  waiting for  a futex,  as it  doesn't require  the
 *   creation of any additional kernel-space object.
 *   TODO: Implement the `kpoll()' system call
 *
 * - Using the regular `poll()' / `select()' family of system calls, after
 *   having created a futexfd handle.
 *
 */


#if defined(__CRT_HAVE_lfutex) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKEMASK, size_t val = count, lfutex_t mask_and, lfutex_t mask_or)
 *    - LFUTEX_WAIT_LOCK:          (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `futex_op' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__LIBC __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_RPC(__VLIBCCALL lfutex)(lfutex_t *__uaddr, __syscall_ulong_t __futex_op, lfutex_t __val, ...) __CASMNAME_SAME("lfutex");
#elif defined(__CRT_HAVE_lfutex64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKEMASK, size_t val = count, lfutex_t mask_and, lfutex_t mask_or)
 *    - LFUTEX_WAIT_LOCK:          (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `futex_op' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__CVREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_RPC,lfutex,(lfutex_t *__uaddr, __syscall_ulong_t __futex_op, lfutex_t __val),lfutex64,(__uaddr,__futex_op,__val),__val,2,(void *,__UINTPTR_TYPE__))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/lfutex.h>
/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKEMASK, size_t val = count, lfutex_t mask_and, lfutex_t mask_or)
 *    - LFUTEX_WAIT_LOCK:          (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `futex_op' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(lfutex, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_RPC(__VLIBCCALL lfutex)(lfutex_t *__uaddr, __syscall_ulong_t __futex_op, lfutex_t __val, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lfutex))(__uaddr, __futex_op, __val, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define lfutex(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lfutex))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */

#ifdef __USE_TIME64
#if defined(__CRT_HAVE_lfutex) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKEMASK, size_t val = count, lfutex_t mask_and, lfutex_t mask_or)
 *    - LFUTEX_WAIT_LOCK:          (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `futex_op' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__CVREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_RPC,lfutex64,(lfutex_t *__uaddr, __syscall_ulong_t __futex_op, lfutex_t __val),lfutex,(__uaddr,__futex_op,__val),__val,2,(void *,__UINTPTR_TYPE__))
#elif defined(__CRT_HAVE_lfutex64)
/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKEMASK, size_t val = count, lfutex_t mask_and, lfutex_t mask_or)
 *    - LFUTEX_WAIT_LOCK:          (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `futex_op' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__LIBC __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_RPC(__VLIBCCALL lfutex64)(lfutex_t *__uaddr, __syscall_ulong_t __futex_op, lfutex_t __val, ...) __CASMNAME_SAME("lfutex64");
#elif defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/lfutex64.h>
/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKEMASK, size_t val = count, lfutex_t mask_and, lfutex_t mask_or)
 *    - LFUTEX_WAIT_LOCK:          (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `futex_op' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(lfutex64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_RPC(__VLIBCCALL lfutex64)(lfutex_t *__uaddr, __syscall_ulong_t __futex_op, lfutex_t __val, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lfutex64))(__uaddr, __futex_op, __val, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define lfutex64(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lfutex64))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#endif /* __USE_TIME64 */
#ifdef __CRT_HAVE_futex_wake
/* Wake up to `MAX_WAKE' threads waiting for `*UADDR'
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
__CDECLARE(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,futex_wake,(lfutex_t *__uaddr, __SIZE_TYPE__ __max_wake),(__uaddr,__max_wake))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_wake.h>
/* Wake up to `MAX_WAKE' threads waiting for `*UADDR'
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_wake, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL futex_wake)(lfutex_t *__uaddr, __SIZE_TYPE__ __max_wake) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_wake))(__uaddr, __max_wake); })
#endif /* ... */
#ifdef __CRT_HAVE_futex_wakeall
/* Wake all threads waiting for `*UADDR' (same as `futex_wake(uaddr, (size_t)-1)')
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
__CDECLARE(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,futex_wakeall,(lfutex_t *__uaddr),(__uaddr))
#elif defined(__CRT_HAVE_futex_wake) || defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_wakeall.h>
/* Wake all threads waiting for `*UADDR' (same as `futex_wake(uaddr, (size_t)-1)')
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_wakeall, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL futex_wakeall)(lfutex_t *__uaddr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_wakeall))(__uaddr); })
#endif /* ... */
#ifdef __CRT_HAVE_futex_wakemask
/* Similar to `futex_wake()', however once there are no more threads that
 * can be awoken, perform the following operation: `*uaddr = (*uaddr & mask_and) | mask_or'
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
__CDECLARE(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,futex_wakemask,(lfutex_t *__uaddr, __SIZE_TYPE__ __max_wake, lfutex_t __mask_and, lfutex_t __mask_or),(__uaddr,__max_wake,__mask_and,__mask_or))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_wakemask.h>
/* Similar to `futex_wake()', however once there are no more threads that
 * can be awoken, perform the following operation: `*uaddr = (*uaddr & mask_and) | mask_or'
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_wakemask, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL futex_wakemask)(lfutex_t *__uaddr, __SIZE_TYPE__ __max_wake, lfutex_t __mask_and, lfutex_t __mask_or) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_wakemask))(__uaddr, __max_wake, __mask_and, __mask_or); })
#endif /* ... */
#ifdef __CRT_HAVE_futexlock_wake
/* >> futexlock_wake(3), futexlock_wakeall(3)
 * A more efficient variant of `futex_wake()' that does  nothing
 * if `!(*ulockaddr & LFUTEX_WAIT_LOCK_WAITERS)', and will clear
 * the `LFUTEX_WAIT_LOCK_WAITERS' flag  (in a race-safe  manner)
 * when there are no more waiting threads. */
__CDECLARE(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,futexlock_wake,(lfutex_t *__ulockaddr, __SIZE_TYPE__ __max_wake),(__ulockaddr,__max_wake))
#elif defined(__CRT_HAVE_futex_wakemask) || defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futexlock_wake.h>
/* >> futexlock_wake(3), futexlock_wakeall(3)
 * A more efficient variant of `futex_wake()' that does  nothing
 * if `!(*ulockaddr & LFUTEX_WAIT_LOCK_WAITERS)', and will clear
 * the `LFUTEX_WAIT_LOCK_WAITERS' flag  (in a race-safe  manner)
 * when there are no more waiting threads. */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_wake, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL futexlock_wake)(lfutex_t *__ulockaddr, __SIZE_TYPE__ __max_wake) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_wake))(__ulockaddr, __max_wake); })
#endif /* ... */
#ifdef __CRT_HAVE_futexlock_wakeall
/* >> futexlock_wake(3), futexlock_wakeall(3)
 * A more efficient variant of `futex_wake()' that does  nothing
 * if `!(*ulockaddr & LFUTEX_WAIT_LOCK_WAITERS)', and will clear
 * the `LFUTEX_WAIT_LOCK_WAITERS' flag  (in a race-safe  manner)
 * when there are no more waiting threads. */
__CDECLARE(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,futexlock_wakeall,(lfutex_t *__ulockaddr),(__ulockaddr))
#elif defined(__CRT_HAVE_futex_wakeall) || defined(__CRT_HAVE_futex_wake) || defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futexlock_wakeall.h>
/* >> futexlock_wake(3), futexlock_wakeall(3)
 * A more efficient variant of `futex_wake()' that does  nothing
 * if `!(*ulockaddr & LFUTEX_WAIT_LOCK_WAITERS)', and will clear
 * the `LFUTEX_WAIT_LOCK_WAITERS' flag  (in a race-safe  manner)
 * when there are no more waiting threads. */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_wakeall, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL futexlock_wakeall)(lfutex_t *__ulockaddr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_wakeall))(__ulockaddr); })
#endif /* ... */
#ifdef __CRT_HAVE_futex_waitwhile
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile,(lfutex_t *__uaddr, lfutex_t __equal_to_value),(__uaddr,__equal_to_value))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_waitwhile.h>
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_waitwhile, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile)(lfutex_t *__uaddr, lfutex_t __equal_to_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_waitwhile))(__uaddr, __equal_to_value); })
#endif /* ... */
#ifdef __CRT_HAVE_futex_waituntil
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waituntil,(lfutex_t *__uaddr, lfutex_t __not_equal_to_value),(__uaddr,__not_equal_to_value))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_waituntil.h>
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_waituntil, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waituntil)(lfutex_t *__uaddr, lfutex_t __not_equal_to_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_waituntil))(__uaddr, __not_equal_to_value); })
#endif /* ... */
#ifdef __CRT_HAVE_futex_waitwhile
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_equal,(lfutex_t *__uaddr, lfutex_t __equal_to_value),futex_waitwhile,(__uaddr,__equal_to_value))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_waitwhile.h>
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_equal)(lfutex_t *__uaddr, lfutex_t __equal_to_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_waitwhile))(__uaddr, __equal_to_value); }
#endif /* ... */
#ifdef __CRT_HAVE_futex_waituntil
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_notequal,(lfutex_t *__uaddr, lfutex_t __not_equal_to_value),futex_waituntil,(__uaddr,__not_equal_to_value))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_waituntil.h>
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_notequal)(lfutex_t *__uaddr, lfutex_t __not_equal_to_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_waituntil))(__uaddr, __not_equal_to_value); }
#endif /* ... */
#ifdef __CRT_HAVE_futex_waitwhile_above
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_above,(lfutex_t *__uaddr, lfutex_t __above_value),(__uaddr,__above_value))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_waitwhile_above.h>
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_waitwhile_above, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_above)(lfutex_t *__uaddr, lfutex_t __above_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_waitwhile_above))(__uaddr, __above_value); })
#endif /* ... */
#ifdef __CRT_HAVE_futex_waitwhile_below
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_below,(lfutex_t *__uaddr, lfutex_t __below_value),(__uaddr,__below_value))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_waitwhile_below.h>
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_waitwhile_below, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_below)(lfutex_t *__uaddr, lfutex_t __below_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_waitwhile_below))(__uaddr, __below_value); })
#endif /* ... */
#ifdef __CRT_HAVE_futex_waitwhile_aboveequal
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_aboveequal,(lfutex_t *__uaddr, lfutex_t __above_equal_value),(__uaddr,__above_equal_value))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_waitwhile_aboveequal.h>
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_waitwhile_aboveequal, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_aboveequal)(lfutex_t *__uaddr, lfutex_t __above_equal_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_waitwhile_aboveequal))(__uaddr, __above_equal_value); })
#endif /* ... */
#ifdef __CRT_HAVE_futex_waitwhile_belowequal
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_belowequal,(lfutex_t *__uaddr, lfutex_t __below_equal_value),(__uaddr,__below_equal_value))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_waitwhile_belowequal.h>
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_waitwhile_belowequal, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_belowequal)(lfutex_t *__uaddr, lfutex_t __below_equal_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_waitwhile_belowequal))(__uaddr, __below_equal_value); })
#endif /* ... */
#ifdef __CRT_HAVE_futex_waitlock
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted (*uaddr was still set to new_value) */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitlock,(lfutex_t *__uaddr),(__uaddr))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_waitlock.h>
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted (*uaddr was still set to new_value) */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_waitlock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitlock)(lfutex_t *__uaddr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_waitlock))(__uaddr); })
#endif /* ... */
#ifdef __CRT_HAVE_futex_waitwhile_exactbits
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_exactbits,(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask),(__uaddr,__bitmask,__setmask))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_waitwhile_exactbits.h>
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_waitwhile_exactbits, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_exactbits)(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_waitwhile_exactbits))(__uaddr, __bitmask, __setmask); })
#endif /* ... */
#ifdef __CRT_HAVE_futex_waituntil_exactbits
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waituntil_exactbits,(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask),(__uaddr,__bitmask,__setmask))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_waituntil_exactbits.h>
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_waituntil_exactbits, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waituntil_exactbits)(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_waituntil_exactbits))(__uaddr, __bitmask, __setmask); })
#endif /* ... */
#ifdef __CRT_HAVE_futex_waitwhile_anybit
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_anybit,(lfutex_t *__uaddr, lfutex_t __bitmask),(__uaddr,__bitmask))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_waitwhile_anybit.h>
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_waitwhile_anybit, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_anybit)(lfutex_t *__uaddr, lfutex_t __bitmask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_waitwhile_anybit))(__uaddr, __bitmask); })
#endif /* ... */
#ifdef __CRT_HAVE_futex_waitwhile_allbits
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_allbits,(lfutex_t *__uaddr, lfutex_t __bitmask),(__uaddr,__bitmask))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_waitwhile_allbits.h>
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_waitwhile_allbits, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_allbits)(lfutex_t *__uaddr, lfutex_t __bitmask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_waitwhile_allbits))(__uaddr, __bitmask); })
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile,(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec const *__rel_timeout),(__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile,(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec const *__rel_timeout),futex_timedwaitwhile64,(__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaitwhile.h>
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_timedwaitwhile, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaitwhile)(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile))(__uaddr, __equal_to_value, __rel_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaituntil) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaituntil,(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec const *__rel_timeout),(__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaituntil64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaituntil,(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec const *__rel_timeout),futex_timedwaituntil64,(__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaituntil.h>
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_timedwaituntil, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaituntil)(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaituntil))(__uaddr, __not_equal_to_value, __rel_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_equal,(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec const *__rel_timeout),futex_timedwaitwhile,(__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_equal,(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec const *__rel_timeout),futex_timedwaitwhile64,(__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaitwhile.h>
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaitwhile_equal)(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile))(__uaddr, __equal_to_value, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaituntil) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_notequal,(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec const *__rel_timeout),futex_timedwaituntil,(__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaituntil64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_notequal,(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec const *__rel_timeout),futex_timedwaituntil64,(__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaituntil.h>
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaitwhile_notequal)(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaituntil))(__uaddr, __not_equal_to_value, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_above) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_above,(lfutex_t *__uaddr, lfutex_t __above_value, struct timespec const *__rel_timeout),(__uaddr,__above_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_above64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_above,(lfutex_t *__uaddr, lfutex_t __above_value, struct timespec const *__rel_timeout),futex_timedwaitwhile_above64,(__uaddr,__above_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaitwhile_above.h>
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_timedwaitwhile_above, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaitwhile_above)(lfutex_t *__uaddr, lfutex_t __above_value, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_above))(__uaddr, __above_value, __rel_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_below) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_below,(lfutex_t *__uaddr, lfutex_t __below_value, struct timespec const *__rel_timeout),(__uaddr,__below_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_below64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_below,(lfutex_t *__uaddr, lfutex_t __below_value, struct timespec const *__rel_timeout),futex_timedwaitwhile_below64,(__uaddr,__below_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaitwhile_below.h>
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_timedwaitwhile_below, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaitwhile_below)(lfutex_t *__uaddr, lfutex_t __below_value, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_below))(__uaddr, __below_value, __rel_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_aboveequal64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_aboveequal,(lfutex_t *__uaddr, lfutex_t __above_equal_value, struct timespec const *__rel_timeout),futex_timedwaitwhile_aboveequal64,(__uaddr,__above_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_aboveequal) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_aboveequal,(lfutex_t *__uaddr, lfutex_t __above_equal_value, struct timespec const *__rel_timeout),(__uaddr,__above_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaitwhile_aboveequal.h>
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_timedwaitwhile_aboveequal, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaitwhile_aboveequal)(lfutex_t *__uaddr, lfutex_t __above_equal_value, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_aboveequal))(__uaddr, __above_equal_value, __rel_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_belowequal) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_belowequal,(lfutex_t *__uaddr, lfutex_t __below_equal_value, struct timespec const *__rel_timeout),(__uaddr,__below_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_belowequal64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_belowequal,(lfutex_t *__uaddr, lfutex_t __below_equal_value, struct timespec const *__rel_timeout),futex_timedwaitwhile_belowequal64,(__uaddr,__below_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaitwhile_belowequal.h>
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_timedwaitwhile_belowequal, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaitwhile_belowequal)(lfutex_t *__uaddr, lfutex_t __below_equal_value, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_belowequal))(__uaddr, __below_equal_value, __rel_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitlock) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitlock,(lfutex_t *__uaddr, struct timespec const *__rel_timeout),(__uaddr,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitlock64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitlock,(lfutex_t *__uaddr, struct timespec const *__rel_timeout),futex_timedwaitlock64,(__uaddr,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaitlock.h>
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_timedwaitlock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaitlock)(lfutex_t *__uaddr, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitlock))(__uaddr, __rel_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_exactbits) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_exactbits,(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec const *__rel_timeout),(__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_exactbits64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_exactbits,(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec const *__rel_timeout),futex_timedwaitwhile_exactbits64,(__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaitwhile_exactbits.h>
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_timedwaitwhile_exactbits, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaitwhile_exactbits)(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_exactbits))(__uaddr, __bitmask, __setmask, __rel_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaituntil_exactbits) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaituntil_exactbits,(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec const *__rel_timeout),(__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaituntil_exactbits64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaituntil_exactbits,(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec const *__rel_timeout),futex_timedwaituntil_exactbits64,(__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaituntil_exactbits.h>
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_timedwaituntil_exactbits, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaituntil_exactbits)(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaituntil_exactbits))(__uaddr, __bitmask, __setmask, __rel_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_anybit) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_anybit,(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec const *__rel_timeout),(__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_anybit64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_anybit,(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec const *__rel_timeout),futex_timedwaitwhile_anybit64,(__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaitwhile_anybit.h>
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_timedwaitwhile_anybit, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaitwhile_anybit)(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_anybit))(__uaddr, __bitmask, __rel_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_allbits) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_allbits,(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec const *__rel_timeout),(__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_allbits64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_allbits,(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec const *__rel_timeout),futex_timedwaitwhile_allbits64,(__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaitwhile_allbits.h>
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_timedwaitwhile_allbits, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaitwhile_allbits)(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_allbits))(__uaddr, __bitmask, __rel_timeout); })
#endif /* ... */

#ifdef __USE_TIME64
#if defined(__CRT_HAVE_futex_timedwaitwhile) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile64,(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec64 const *__rel_timeout),futex_timedwaitwhile,(__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile64)
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile64,(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec64 const *__rel_timeout),(__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaitwhile64.h>
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_timedwaitwhile64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaitwhile64)(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile64))(__uaddr, __equal_to_value, __rel_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaituntil) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaituntil64,(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec64 const *__rel_timeout),futex_timedwaituntil,(__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaituntil64)
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaituntil64,(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec64 const *__rel_timeout),(__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaituntil64.h>
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_timedwaituntil64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaituntil64)(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaituntil64))(__uaddr, __not_equal_to_value, __rel_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_equal64,(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec64 const *__rel_timeout),futex_timedwaitwhile,(__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile64)
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_equal64,(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec64 const *__rel_timeout),futex_timedwaitwhile64,(__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaitwhile64.h>
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaitwhile_equal64)(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile64))(__uaddr, __equal_to_value, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaituntil) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_notequal64,(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec64 const *__rel_timeout),futex_timedwaituntil,(__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaituntil64)
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_notequal64,(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec64 const *__rel_timeout),futex_timedwaituntil64,(__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaituntil64.h>
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaitwhile_notequal64)(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaituntil64))(__uaddr, __not_equal_to_value, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_above) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_above64,(lfutex_t *__uaddr, lfutex_t __above_value, struct timespec64 const *__rel_timeout),futex_timedwaitwhile_above,(__uaddr,__above_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_above64)
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_above64,(lfutex_t *__uaddr, lfutex_t __above_value, struct timespec64 const *__rel_timeout),(__uaddr,__above_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaitwhile_above64.h>
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_timedwaitwhile_above64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaitwhile_above64)(lfutex_t *__uaddr, lfutex_t __above_value, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_above64))(__uaddr, __above_value, __rel_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_below) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_below64,(lfutex_t *__uaddr, lfutex_t __below_value, struct timespec64 const *__rel_timeout),futex_timedwaitwhile_below,(__uaddr,__below_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_below64)
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_below64,(lfutex_t *__uaddr, lfutex_t __below_value, struct timespec64 const *__rel_timeout),(__uaddr,__below_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaitwhile_below64.h>
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_timedwaitwhile_below64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaitwhile_below64)(lfutex_t *__uaddr, lfutex_t __below_value, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_below64))(__uaddr, __below_value, __rel_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_aboveequal) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_aboveequal64,(lfutex_t *__uaddr, lfutex_t __above_equal_value, struct timespec64 const *__rel_timeout),futex_timedwaitwhile_aboveequal,(__uaddr,__above_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_aboveequal64)
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_aboveequal64,(lfutex_t *__uaddr, lfutex_t __above_equal_value, struct timespec64 const *__rel_timeout),(__uaddr,__above_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaitwhile_aboveequal64.h>
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_timedwaitwhile_aboveequal64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaitwhile_aboveequal64)(lfutex_t *__uaddr, lfutex_t __above_equal_value, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_aboveequal64))(__uaddr, __above_equal_value, __rel_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_belowequal) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_belowequal64,(lfutex_t *__uaddr, lfutex_t __below_equal_value, struct timespec64 const *__rel_timeout),futex_timedwaitwhile_belowequal,(__uaddr,__below_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_belowequal64)
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_belowequal64,(lfutex_t *__uaddr, lfutex_t __below_equal_value, struct timespec64 const *__rel_timeout),(__uaddr,__below_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaitwhile_belowequal64.h>
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_timedwaitwhile_belowequal64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaitwhile_belowequal64)(lfutex_t *__uaddr, lfutex_t __below_equal_value, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_belowequal64))(__uaddr, __below_equal_value, __rel_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitlock) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitlock64,(lfutex_t *__uaddr, struct timespec64 const *__rel_timeout),futex_timedwaitlock,(__uaddr,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitlock64)
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitlock64,(lfutex_t *__uaddr, struct timespec64 const *__rel_timeout),(__uaddr,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaitlock64.h>
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_timedwaitlock64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaitlock64)(lfutex_t *__uaddr, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitlock64))(__uaddr, __rel_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_exactbits) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_exactbits64,(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec64 const *__rel_timeout),futex_timedwaitwhile_exactbits,(__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_exactbits64)
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_exactbits64,(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec64 const *__rel_timeout),(__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaitwhile_exactbits64.h>
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_timedwaitwhile_exactbits64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaitwhile_exactbits64)(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_exactbits64))(__uaddr, __bitmask, __setmask, __rel_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaituntil_exactbits) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaituntil_exactbits64,(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec64 const *__rel_timeout),futex_timedwaituntil_exactbits,(__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaituntil_exactbits64)
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaituntil_exactbits64,(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec64 const *__rel_timeout),(__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaituntil_exactbits64.h>
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_timedwaituntil_exactbits64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaituntil_exactbits64)(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaituntil_exactbits64))(__uaddr, __bitmask, __setmask, __rel_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_anybit) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_anybit64,(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec64 const *__rel_timeout),futex_timedwaitwhile_anybit,(__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_anybit64)
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_anybit64,(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec64 const *__rel_timeout),(__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaitwhile_anybit64.h>
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_timedwaitwhile_anybit64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaitwhile_anybit64)(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_anybit64))(__uaddr, __bitmask, __rel_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_allbits) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_allbits64,(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec64 const *__rel_timeout),futex_timedwaitwhile_allbits,(__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_allbits64)
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_timedwaitwhile_allbits64,(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec64 const *__rel_timeout),(__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <libc/local/kos.futex/futex_timedwaitwhile_allbits64.h>
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futex_timedwaitwhile_allbits64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_timedwaitwhile_allbits64)(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_allbits64))(__uaddr, __bitmask, __rel_timeout); })
#endif /* ... */
#endif /* __USE_TIME64 */
#ifndef ____os_gettid_defined
#define ____os_gettid_defined
#ifdef __CRT_HAVE_gettid
/* >> gettid(2)
 * Return the TID of the calling thread
 * THIS_THREAD->PID */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__os_gettid,(void),gettid,())
#elif defined(__CRT_HAVE___threadid)
/* >> gettid(2)
 * Return the TID of the calling thread
 * THIS_THREAD->PID */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__os_gettid,(void),__threadid,())
#elif defined(__CRT_HAVE_$QGetCurrentThreadId$Aplatform$Adetails$AConcurrency$A$AYAJXZ)
/* >> gettid(2)
 * Return the TID of the calling thread
 * THIS_THREAD->PID */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__os_gettid,(void),?GetCurrentThreadId@platform@details@Concurrency@@YAJXZ,())
#else /* ... */
#undef ____os_gettid_defined
#endif /* !... */
#endif /* !____os_gettid_defined */



/* Check if `futex_waitwhile()' would block
 * @return: 0: `futex_waitwhile()' would block
 * @return: 1: `futex_waitwhile()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitwhile)(lfutex_t *__uaddr, lfutex_t __equal_to_value) {
	return __hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) == __equal_to_value ? 0 : 1;
}

/* Check if `futex_waituntil()' would block
 * @return: 0: `futex_waituntil()' would block
 * @return: 1: `futex_waituntil()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaituntil)(lfutex_t *__uaddr, lfutex_t __not_equal_to_value) {
	return __hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) != __not_equal_to_value ? 0 : 1;
}

/* Check if `futex_waitwhile_equal()' would block
 * @return: 0: `futex_waitwhile_equal()' would block
 * @return: 1: `futex_waitwhile_equal()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitwhile_equal)(lfutex_t *__uaddr, lfutex_t __equal_to_value) {
	return __hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) == __equal_to_value ? 0 : 1;
}

/* Check if `futex_waitwhile_notequal()' would block
 * @return: 0: `futex_waitwhile_notequal()' would block
 * @return: 1: `futex_waitwhile_notequal()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitwhile_notequal)(lfutex_t *__uaddr, lfutex_t __not_equal_to_value) {
	return __hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) != __not_equal_to_value ? 0 : 1;
}

/* Check if `futex_waitwhile_above()' would block
 * @return: 0: `futex_waitwhile_above()' would block
 * @return: 1: `futex_waitwhile_above()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitwhile_above)(lfutex_t *__uaddr, lfutex_t __above_value) {
	return __hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) > __above_value ? 0 : 1;
}

/* Check if `futex_waitwhile_below()' would block
 * @return: 0: `futex_waitwhile_below()' would block
 * @return: 1: `futex_waitwhile_below()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitwhile_below)(lfutex_t *__uaddr, lfutex_t __below_value) {
	return __hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) < __below_value ? 0 : 1;
}

/* Check if `futex_waitwhile_aboveequal()' would block
 * @return: 0: `futex_waitwhile_aboveequal()' would block
 * @return: 1: `futex_waitwhile_aboveequal()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitwhile_aboveequal)(lfutex_t *__uaddr, lfutex_t __above_equal_value) {
	return __hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) >= __above_equal_value ? 0 : 1;
}

/* Check if `futex_waitwhile_belowequal()' would block
 * @return: 0: `futex_waitwhile_belowequal()' would block
 * @return: 1: `futex_waitwhile_belowequal()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitwhile_belowequal)(lfutex_t *__uaddr, lfutex_t __below_equal_value) {
	return __hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) <= __below_equal_value ? 0 : 1;
}

#ifdef ____os_gettid_defined
/* Same as `futex_waitlock()' with a 0-length timeout
 * @return: 0: Successfully acquired the lock
 * @return: 1: Failed to acquire acquired the lock without blocking */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitlock)(lfutex_t *__uaddr) {
	for (;;) {
		lfutex_t __oldval;
		__oldval = __hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE);
		if ((__oldval & LFUTEX_WAIT_LOCK_TIDMASK) != 0)
			break;
		if (__hybrid_atomic_cmpxch_weak(*__uaddr, __oldval, (__oldval & ~LFUTEX_WAIT_LOCK_TIDMASK) | __os_gettid(),
		                                __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST))
			return 0;
	}
	return 1;
}
#endif /* ____os_gettid_defined */

/* Check if `futex_waitwhile_exactbits()' would block
 * @return: 0: `futex_waitwhile_exactbits()' would block
 * @return: 1: `futex_waitwhile_exactbits()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitwhile_exactbits)(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask) {
	return (__hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) & __bitmask) == __setmask ? 0 : 1;
}

/* Check if `futex_waituntil_exactbits()' would block
 * @return: 0: `futex_waituntil_exactbits()' would block
 * @return: 1: `futex_waituntil_exactbits()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaituntil_exactbits)(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask) {
	return (__hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) & __bitmask) != __setmask ? 0 : 1;
}

/* Check if `futex_waitwhile_anybit()' would block
 * @return: 0: `futex_waitwhile_anybit()' would block
 * @return: 1: `futex_waitwhile_anybit()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitwhile_anybit)(lfutex_t *__uaddr, lfutex_t __bitmask) {
	return (__hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) & __bitmask) != 0 ? 0 : 1;
}

/* Check if `futex_waitwhile_allbits()' would block
 * @return: 0: `futex_waitwhile_allbits()' would block
 * @return: 1: `futex_waitwhile_allbits()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitwhile_allbits)(lfutex_t *__uaddr, lfutex_t __bitmask) {
	return (__hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) & __bitmask) == __bitmask ? 0 : 1;
}




/* Get/Set the number of times to spin the following futex operations without
 * entering  kernel-space,  setting  waiter-bits,  and  entering  sleep mode:
 *   - LFUTEX_WAIT_WHILE: SPIN({ if (*uaddr != val) DONE(); });
 *   - LFUTEX_WAIT_UNTIL: SPIN({ if (*uaddr == val) DONE(); });
 *   - ...
 * Futex  spinning  improves  performance  by  bypassing  expensive  blocking   operations
 * when  associated  locks  are  often only  held  for  a  couple of  moments  at  a time.
 * Take for example `lfutex(LFUTEX_WAIT_WHILE)' (or preferably `futex_waitwhile()'), which
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
__CDECLARE_OPT(__ATTR_WUNUSED,unsigned int,__NOTHROW,futex_getspin,(void),())
/* Get/Set the number of times to spin the following futex operations without
 * entering  kernel-space,  setting  waiter-bits,  and  entering  sleep mode:
 *   - LFUTEX_WAIT_WHILE: SPIN({ if (*uaddr != val) DONE(); });
 *   - LFUTEX_WAIT_UNTIL: SPIN({ if (*uaddr == val) DONE(); });
 *   - ...
 * Futex  spinning  improves  performance  by  bypassing  expensive  blocking   operations
 * when  associated  locks  are  often only  held  for  a  couple of  moments  at  a time.
 * Take for example `lfutex(LFUTEX_WAIT_WHILE)' (or preferably `futex_waitwhile()'), which
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
__CDECLARE_OPT(,unsigned int,__NOTHROW,futex_setspin,(unsigned int __new_spin),(__new_spin))



/* Provide overloads for the non-timed functions add an optional `rel_timeout'
 * argument   that   re-directly    to   the    function's   timed    variant.
 * Because  this overload  is purely based  on argument count,  we can emulate
 * this  portably  both  in   C++  and  C  (using   `__HYBRID_PP_VA_OVERLOAD') */
#ifdef __cplusplus
extern "C++" {
#ifdef __CRT_HAVE_futex_wakeall
/* Wake all threads waiting for `*UADDR' (same as `futex_wake(uaddr, (size_t)-1)')
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,futex_wake,(lfutex_t *__uaddr),futex_wakeall,(__uaddr))
#elif defined(__CRT_HAVE_futex_wake) || defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_wakeall.h>
extern "C++" {
/* Wake all threads waiting for `*UADDR' (same as `futex_wake(uaddr, (size_t)-1)')
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL futex_wake)(lfutex_t *__uaddr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_wakeall))(__uaddr); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile,(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec const *__rel_timeout),futex_timedwaitwhile,(__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile,(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec const *__rel_timeout),futex_timedwaitwhile64,(__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaitwhile.h>
extern "C++" {
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile)(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile))(__uaddr, __equal_to_value, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaituntil) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waituntil,(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec const *__rel_timeout),futex_timedwaituntil,(__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaituntil64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waituntil,(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec const *__rel_timeout),futex_timedwaituntil64,(__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaituntil.h>
extern "C++" {
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waituntil)(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaituntil))(__uaddr, __not_equal_to_value, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_equal,(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec const *__rel_timeout),futex_timedwaitwhile,(__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_equal,(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec const *__rel_timeout),futex_timedwaitwhile64,(__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaitwhile.h>
extern "C++" {
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_equal)(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile))(__uaddr, __equal_to_value, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaituntil) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_notequal,(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec const *__rel_timeout),futex_timedwaituntil,(__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaituntil64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_notequal,(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec const *__rel_timeout),futex_timedwaituntil64,(__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaituntil.h>
extern "C++" {
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_notequal)(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaituntil))(__uaddr, __not_equal_to_value, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_above) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_above,(lfutex_t *__uaddr, lfutex_t __above_value, struct timespec const *__rel_timeout),futex_timedwaitwhile_above,(__uaddr,__above_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_above64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_above,(lfutex_t *__uaddr, lfutex_t __above_value, struct timespec const *__rel_timeout),futex_timedwaitwhile_above64,(__uaddr,__above_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaitwhile_above.h>
extern "C++" {
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_above)(lfutex_t *__uaddr, lfutex_t __above_value, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_above))(__uaddr, __above_value, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_below) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_below,(lfutex_t *__uaddr, lfutex_t __below_value, struct timespec const *__rel_timeout),futex_timedwaitwhile_below,(__uaddr,__below_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_below64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_below,(lfutex_t *__uaddr, lfutex_t __below_value, struct timespec const *__rel_timeout),futex_timedwaitwhile_below64,(__uaddr,__below_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaitwhile_below.h>
extern "C++" {
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_below)(lfutex_t *__uaddr, lfutex_t __below_value, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_below))(__uaddr, __below_value, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_aboveequal64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_aboveequal,(lfutex_t *__uaddr, lfutex_t __above_equal_value, struct timespec const *__rel_timeout),futex_timedwaitwhile_aboveequal64,(__uaddr,__above_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_aboveequal) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_aboveequal,(lfutex_t *__uaddr, lfutex_t __above_equal_value, struct timespec const *__rel_timeout),futex_timedwaitwhile_aboveequal,(__uaddr,__above_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaitwhile_aboveequal.h>
extern "C++" {
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_aboveequal)(lfutex_t *__uaddr, lfutex_t __above_equal_value, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_aboveequal))(__uaddr, __above_equal_value, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_belowequal) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_belowequal,(lfutex_t *__uaddr, lfutex_t __below_equal_value, struct timespec const *__rel_timeout),futex_timedwaitwhile_belowequal,(__uaddr,__below_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_belowequal64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_belowequal,(lfutex_t *__uaddr, lfutex_t __below_equal_value, struct timespec const *__rel_timeout),futex_timedwaitwhile_belowequal64,(__uaddr,__below_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaitwhile_belowequal.h>
extern "C++" {
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_belowequal)(lfutex_t *__uaddr, lfutex_t __below_equal_value, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_belowequal))(__uaddr, __below_equal_value, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitlock) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitlock,(lfutex_t *__uaddr, struct timespec const *__rel_timeout),futex_timedwaitlock,(__uaddr,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitlock64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitlock,(lfutex_t *__uaddr, struct timespec const *__rel_timeout),futex_timedwaitlock64,(__uaddr,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaitlock.h>
extern "C++" {
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitlock)(lfutex_t *__uaddr, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitlock))(__uaddr, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_exactbits) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_exactbits,(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec const *__rel_timeout),futex_timedwaitwhile_exactbits,(__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_exactbits64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_exactbits,(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec const *__rel_timeout),futex_timedwaitwhile_exactbits64,(__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaitwhile_exactbits.h>
extern "C++" {
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_exactbits)(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_exactbits))(__uaddr, __bitmask, __setmask, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaituntil_exactbits) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waituntil_exactbits,(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec const *__rel_timeout),futex_timedwaituntil_exactbits,(__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaituntil_exactbits64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waituntil_exactbits,(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec const *__rel_timeout),futex_timedwaituntil_exactbits64,(__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaituntil_exactbits.h>
extern "C++" {
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waituntil_exactbits)(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaituntil_exactbits))(__uaddr, __bitmask, __setmask, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_anybit) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_anybit,(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec const *__rel_timeout),futex_timedwaitwhile_anybit,(__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_anybit64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_anybit,(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec const *__rel_timeout),futex_timedwaitwhile_anybit64,(__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaitwhile_anybit.h>
extern "C++" {
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_anybit)(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_anybit))(__uaddr, __bitmask, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_allbits) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_allbits,(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec const *__rel_timeout),futex_timedwaitwhile_allbits,(__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_allbits64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_allbits,(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec const *__rel_timeout),futex_timedwaitwhile_allbits64,(__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaitwhile_allbits.h>
extern "C++" {
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_allbits)(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_allbits))(__uaddr, __bitmask, __rel_timeout); }
#endif /* ... */
} /* extern "C++" */
#if defined(__USE_TIME64) && !((defined(__USE_TIME_BITS64) || defined(_TIMESPEC_MATCHES_TIMESPEC64)) && defined(__USE_STRUCT64_MACRO))
extern "C++" {
#if defined(__CRT_HAVE_futex_timedwaitwhile) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile,(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec64 const *__rel_timeout),futex_timedwaitwhile,(__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile64)
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile,(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec64 const *__rel_timeout),futex_timedwaitwhile64,(__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaitwhile64.h>
extern "C++" {
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile)(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile64))(__uaddr, __equal_to_value, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaituntil) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waituntil,(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec64 const *__rel_timeout),futex_timedwaituntil,(__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaituntil64)
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waituntil,(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec64 const *__rel_timeout),futex_timedwaituntil64,(__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaituntil64.h>
extern "C++" {
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waituntil)(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaituntil64))(__uaddr, __not_equal_to_value, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_equal,(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec64 const *__rel_timeout),futex_timedwaitwhile,(__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile64)
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_equal,(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec64 const *__rel_timeout),futex_timedwaitwhile64,(__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaitwhile64.h>
extern "C++" {
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_equal)(lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile64))(__uaddr, __equal_to_value, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaituntil) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_notequal,(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec64 const *__rel_timeout),futex_timedwaituntil,(__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaituntil64)
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_notequal,(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec64 const *__rel_timeout),futex_timedwaituntil64,(__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaituntil64.h>
extern "C++" {
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_notequal)(lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaituntil64))(__uaddr, __not_equal_to_value, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_above) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_above,(lfutex_t *__uaddr, lfutex_t __above_value, struct timespec64 const *__rel_timeout),futex_timedwaitwhile_above,(__uaddr,__above_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_above64)
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_above,(lfutex_t *__uaddr, lfutex_t __above_value, struct timespec64 const *__rel_timeout),futex_timedwaitwhile_above64,(__uaddr,__above_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaitwhile_above64.h>
extern "C++" {
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_above)(lfutex_t *__uaddr, lfutex_t __above_value, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_above64))(__uaddr, __above_value, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_below) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_below,(lfutex_t *__uaddr, lfutex_t __below_value, struct timespec64 const *__rel_timeout),futex_timedwaitwhile_below,(__uaddr,__below_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_below64)
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_below,(lfutex_t *__uaddr, lfutex_t __below_value, struct timespec64 const *__rel_timeout),futex_timedwaitwhile_below64,(__uaddr,__below_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaitwhile_below64.h>
extern "C++" {
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_below)(lfutex_t *__uaddr, lfutex_t __below_value, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_below64))(__uaddr, __below_value, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_aboveequal) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_aboveequal,(lfutex_t *__uaddr, lfutex_t __above_equal_value, struct timespec64 const *__rel_timeout),futex_timedwaitwhile_aboveequal,(__uaddr,__above_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_aboveequal64)
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_aboveequal,(lfutex_t *__uaddr, lfutex_t __above_equal_value, struct timespec64 const *__rel_timeout),futex_timedwaitwhile_aboveequal64,(__uaddr,__above_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaitwhile_aboveequal64.h>
extern "C++" {
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_aboveequal)(lfutex_t *__uaddr, lfutex_t __above_equal_value, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_aboveequal64))(__uaddr, __above_equal_value, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_belowequal) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_belowequal,(lfutex_t *__uaddr, lfutex_t __below_equal_value, struct timespec64 const *__rel_timeout),futex_timedwaitwhile_belowequal,(__uaddr,__below_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_belowequal64)
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_belowequal,(lfutex_t *__uaddr, lfutex_t __below_equal_value, struct timespec64 const *__rel_timeout),futex_timedwaitwhile_belowequal64,(__uaddr,__below_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaitwhile_belowequal64.h>
extern "C++" {
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_belowequal)(lfutex_t *__uaddr, lfutex_t __below_equal_value, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_belowequal64))(__uaddr, __below_equal_value, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitlock) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitlock,(lfutex_t *__uaddr, struct timespec64 const *__rel_timeout),futex_timedwaitlock,(__uaddr,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitlock64)
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitlock,(lfutex_t *__uaddr, struct timespec64 const *__rel_timeout),futex_timedwaitlock64,(__uaddr,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaitlock64.h>
extern "C++" {
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitlock)(lfutex_t *__uaddr, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitlock64))(__uaddr, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_exactbits) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_exactbits,(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec64 const *__rel_timeout),futex_timedwaitwhile_exactbits,(__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_exactbits64)
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_exactbits,(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec64 const *__rel_timeout),futex_timedwaitwhile_exactbits64,(__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaitwhile_exactbits64.h>
extern "C++" {
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_exactbits)(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_exactbits64))(__uaddr, __bitmask, __setmask, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaituntil_exactbits) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waituntil_exactbits,(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec64 const *__rel_timeout),futex_timedwaituntil_exactbits,(__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaituntil_exactbits64)
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waituntil_exactbits,(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec64 const *__rel_timeout),futex_timedwaituntil_exactbits64,(__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaituntil_exactbits64.h>
extern "C++" {
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waituntil_exactbits)(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaituntil_exactbits64))(__uaddr, __bitmask, __setmask, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_anybit) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_anybit,(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec64 const *__rel_timeout),futex_timedwaitwhile_anybit,(__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_anybit64)
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_anybit,(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec64 const *__rel_timeout),futex_timedwaitwhile_anybit64,(__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaitwhile_anybit64.h>
extern "C++" {
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_anybit)(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_anybit64))(__uaddr, __bitmask, __rel_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_futex_timedwaitwhile_allbits) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_allbits,(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec64 const *__rel_timeout),futex_timedwaitwhile_allbits,(__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_futex_timedwaitwhile_allbits64)
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,futex_waitwhile_allbits,(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec64 const *__rel_timeout),futex_timedwaitwhile_allbits64,(__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
} /* extern "C++" */
#include <libc/local/kos.futex/futex_timedwaitwhile_allbits64.h>
extern "C++" {
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL futex_waitwhile_allbits)(lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_timedwaitwhile_allbits64))(__uaddr, __bitmask, __rel_timeout); }
#endif /* ... */
} /* extern "C++" */
#endif /* __USE_TIME64 && !((__USE_TIME_BITS64 || _TIMESPEC_MATCHES_TIMESPEC64) && __USE_STRUCT64_MACRO) */
#else /* __cplusplus */
#define __PRIVATE_futex_wake_1(uaddr)                                                 futex_wakeall(uaddr)
#define __PRIVATE_futex_wake_2(uaddr, max_wake)                                       futex_wake(uaddr, max_wake)
#define __PRIVATE_futex_waitwhile_2(uaddr, equal_to_value)                            futex_waitwhile(uaddr, equal_to_value)
#define __PRIVATE_futex_waitwhile_3(uaddr, equal_to_value, rel_timeout)               futex_timedwaitwhile(uaddr, equal_to_value, rel_timeout)
#define __PRIVATE_futex_waituntil_2(uaddr, not_equal_to_value)                        futex_waituntil(uaddr, not_equal_to_value)
#define __PRIVATE_futex_waituntil_3(uaddr, not_equal_to_value, rel_timeout)           futex_timedwaituntil(uaddr, not_equal_to_value, rel_timeout)
#define __PRIVATE_futex_waitwhile_equal_2(uaddr, equal_to_value)                      futex_waitwhile_equal(uaddr, equal_to_value)
#define __PRIVATE_futex_waitwhile_equal_3(uaddr, equal_to_value, rel_timeout)         futex_timedwaitwhile_equal(uaddr, equal_to_value, rel_timeout)
#define __PRIVATE_futex_waitwhile_notequal_2(uaddr, not_equal_to_value)               futex_waitwhile_notequal(uaddr, not_equal_to_value)
#define __PRIVATE_futex_waitwhile_notequal_3(uaddr, not_equal_to_value, rel_timeout)  futex_timedwaitwhile_notequal(uaddr, not_equal_to_value, rel_timeout)
#define __PRIVATE_futex_waitwhile_above_2(uaddr, above_value)                         futex_waitwhile_above(uaddr, above_value)
#define __PRIVATE_futex_waitwhile_above_3(uaddr, above_value, rel_timeout)            futex_timedwaitwhile_above(uaddr, above_value, rel_timeout)
#define __PRIVATE_futex_waitwhile_below_2(uaddr, below_value)                         futex_waitwhile_below(uaddr, below_value)
#define __PRIVATE_futex_waitwhile_below_3(uaddr, below_value, rel_timeout)            futex_timedwaitwhile_below(uaddr, below_value, rel_timeout)
#define __PRIVATE_futex_waitwhile_aboveequal_2(uaddr, above_equal_value)              futex_waitwhile_aboveequal(uaddr, above_equal_value)
#define __PRIVATE_futex_waitwhile_aboveequal_3(uaddr, above_equal_value, rel_timeout) futex_timedwaitwhile_aboveequal(uaddr, above_equal_value, rel_timeout)
#define __PRIVATE_futex_waitwhile_belowequal_2(uaddr, below_equal_value)              futex_waitwhile_belowequal(uaddr, below_equal_value)
#define __PRIVATE_futex_waitwhile_belowequal_3(uaddr, below_equal_value, rel_timeout) futex_timedwaitwhile_belowequal(uaddr, below_equal_value, rel_timeout)
#define __PRIVATE_futex_waitlock_1(uaddr)                                             futex_waitlock(uaddr)
#define __PRIVATE_futex_waitlock_2(uaddr, rel_timeout)                                futex_timedwaitlock(uaddr, rel_timeout)
#define __PRIVATE_futex_waitwhile_exactbits_3(uaddr, bitmask, setmask)                futex_waitwhile_exactbits(uaddr, bitmask, setmask)
#define __PRIVATE_futex_waitwhile_exactbits_4(uaddr, bitmask, setmask, rel_timeout)   futex_timedwaitwhile_exactbits(uaddr, bitmask, setmask, rel_timeout)
#define __PRIVATE_futex_waituntil_exactbits_3(uaddr, bitmask, setmask)                futex_waituntil_exactbits(uaddr, bitmask, setmask)
#define __PRIVATE_futex_waituntil_exactbits_4(uaddr, bitmask, setmask, rel_timeout)   futex_timedwaituntil_exactbits(uaddr, bitmask, setmask, rel_timeout)
#define __PRIVATE_futex_waitwhile_anybit_2(uaddr, bitmask)                            futex_waitwhile_anybit(uaddr, bitmask)
#define __PRIVATE_futex_waitwhile_anybit_3(uaddr, bitmask, rel_timeout)               futex_timedwaitwhile_anybit(uaddr, bitmask, rel_timeout)
#define __PRIVATE_futex_waitwhile_allbits_2(uaddr, bitmask)                           futex_waitwhile_allbits(uaddr, bitmask)
#define __PRIVATE_futex_waitwhile_allbits_3(uaddr, bitmask, rel_timeout)              futex_timedwaitwhile_allbits(uaddr, bitmask, rel_timeout)
#define futex_wake(...)                           __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_wake_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile(...)                      __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waituntil(...)                      __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waituntil_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile_equal(...)                __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_equal_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile_notequal(...)             __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_notequal_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile_above(...)                __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_above_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile_below(...)                __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_below_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile_aboveequal(...)           __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_aboveequal_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile_belowequal(...)           __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_belowequal_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitlock(...)                       __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitlock_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile_exactbits(...)            __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_exactbits_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waituntil_exactbits(...)            __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waituntil_exactbits_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile_anybit(...)               __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_anybit_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile_allbits(...)              __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_allbits_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* !__cplusplus */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_FUTEX_H */
