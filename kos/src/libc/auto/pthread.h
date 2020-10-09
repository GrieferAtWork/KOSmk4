/* HASH CRC-32:0x10933222 */
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
#ifndef GUARD_LIBC_AUTO_PTHREAD_H
#define GUARD_LIBC_AUTO_PTHREAD_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <pthread.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Create a new thread, starting with execution of START-ROUTINE
 * getting passed ARG. Creation attributed come from ATTR. The new
 * handle is stored in *NEWTHREAD
 * @return: EOK:    Success
 * @return: EAGAIN: Insufficient resources, or operation-not-permitted */
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_create)(pthread_t *__restrict newthread, pthread_attr_t const *__restrict attr, __pthread_start_routine_t start_routine, void *__restrict arg);
/* Terminate calling thread.
 * The registered cleanup handlers are called via exception handling */
INTDEF ATTR_NORETURN void (LIBDCALL libd_pthread_exit)(void *retval) THROWS(...);
/* Make calling thread wait for termination of the thread THREAD. The
 * exit status of the thread is stored in *THREAD_RETURN, if THREAD_RETURN
 * is not NULL
 * @return: EOK: Success */
INTDEF errno_t NOTHROW_RPC(LIBDCALL libd_pthread_join)(pthread_t pthread, void **thread_return);
/* Check whether thread THREAD has terminated. If yes return the status of
 * the thread in *THREAD_RETURN, if THREAD_RETURN is not NULL
 * @return: EOK:   Success
 * @return: EBUSY: The thread has yet to terminate */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_tryjoin_np)(pthread_t pthread, void **thread_return);
/* Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF errno_t NOTHROW_RPC(LIBDCALL libd_pthread_timedjoin_np)(pthread_t pthread, void **thread_return, struct timespec const *abstime);
/* Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF errno_t NOTHROW_RPC(LIBDCALL libd_pthread_timedjoin64_np)(pthread_t pthread, void **thread_return, struct timespec64 const *abstime);
/* Indicate that the thread THREAD is never to be joined with PTHREAD_JOIN.
 * The resources of THREAD will therefore be freed immediately when it
 * terminates, instead of waiting for another thread to perform PTHREAD_JOIN on it
 * @return: EOK: Success */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_detach)(pthread_t pthread);
/* Compare two thread identifiers
 * @return: 0 : Given threads are non-equal
 * @return: * : Given threads are equal */
INTDEF ATTR_CONST int NOTHROW(LIBDCALL libd_pthread_equal)(pthread_t thr1, pthread_t thr2);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Compare two thread identifiers
 * @return: 0 : Given threads are non-equal
 * @return: * : Given threads are equal */
INTDEF ATTR_CONST int NOTHROW(LIBCCALL libc_pthread_equal)(pthread_t thr1, pthread_t thr2);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Initialize thread attribute *ATTR with default attributes (detachstate is
 * PTHREAD_JOINABLE, scheduling policy is SCHED_OTHER, no user-provided stack)
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_init)(pthread_attr_t *attr);
/* Destroy thread attribute *ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_destroy)(pthread_attr_t *attr);
/* Get detach state attribute
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_getdetachstate)(pthread_attr_t const *attr, int *detachstate);
/* Set detach state attribute
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `detachstate' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setdetachstate)(pthread_attr_t *attr, int detachstate);
/* Get the size of the guard area created for stack overflow protection
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_getguardsize)(pthread_attr_t const *attr, size_t *guardsize);
/* Set the size of the guard area created for stack overflow protection
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setguardsize)(pthread_attr_t *attr, size_t guardsize);
/* Return in *PARAM the scheduling parameters of *ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_getschedparam)(pthread_attr_t const *__restrict attr, struct sched_param *__restrict param);
/* Set scheduling parameters (priority, etc) in *ATTR according to PARAM
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `param' */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setschedparam)(pthread_attr_t *__restrict attr, struct sched_param const *__restrict param);
/* Return in *POLICY the scheduling policy of *ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_getschedpolicy)(pthread_attr_t const *__restrict attr, int *__restrict policy);
/* Set scheduling policy in *ATTR according to POLICY
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `policy' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setschedpolicy)(pthread_attr_t *attr, int policy);
/* Return in *INHERIT the scheduling inheritance mode of *ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_getinheritsched)(pthread_attr_t const *__restrict attr, int *__restrict inherit);
/* Set scheduling inheritance mode in *ATTR according to INHERIT
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `inherit' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setinheritsched)(pthread_attr_t *attr, int inherit);
/* Return in *SCOPE the scheduling contention scope of *ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_getscope)(pthread_attr_t const *__restrict attr, int *__restrict scope);
/* Set scheduling contention scope in *ATTR according to SCOPE
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `scope' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setscope)(pthread_attr_t *attr, int scope);
/* Return the previously set address for the stack
 * @return: EOK: Success */
INTDEF ATTR_DEPRECATED("Use pthread_attr_getstack()") NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_getstackaddr)(pthread_attr_t const *__restrict attr, void **__restrict stackaddr);
/* Set the starting address of the stack of the thread to be created.
 * Depending on whether the stack grows up or down the value must either
 * be higher or lower than all the address in the memory block. The
 * minimal size of the block must be PTHREAD_STACK_MIN
 * @return: EOK:    Success
 * @return: EINVAL: The stack isn't suitably aligned */
INTDEF ATTR_DEPRECATED("Use pthread_attr_setstack()") NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setstackaddr)(pthread_attr_t *attr, void *stackaddr);
/* Return the currently used minimal stack size
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_getstacksize)(pthread_attr_t const *__restrict attr, size_t *__restrict stacksize);
/* Add information about the minimum stack size needed for the thread
 * to be started. This size must never be less than PTHREAD_STACK_MIN
 * and must also not exceed the system limits
 * @return: EOK:    Success
 * @return: EINVAL: `stacksize' is too small */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setstacksize)(pthread_attr_t *attr, size_t stacksize);
/* Return the previously set address for the stack
 * @return: EOK: Success */
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_getstack)(pthread_attr_t const *__restrict attr, void **__restrict stackaddr, size_t *__restrict stacksize);
/* The following two interfaces are intended to replace the last two. They
 * require setting the address as well as the size since only setting the
 * address will make the implementation on some architectures impossible
 * @return: EOK:    Success
 * @return: EINVAL: `stacksize' is too small, or the stack isn't suitably aligned */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setstack)(pthread_attr_t *attr, void *stackaddr, size_t stacksize);
/* Thread created with attribute ATTR will be limited to run only on
 * the processors represented in CPUSET
 * @return: EOK:    Success
 * @return: EINVAL: The given set contains a non-existant CPU
 * @return: ENOMEM: Insufficient memory */
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setaffinity_np)(pthread_attr_t *attr, size_t cpusetsize, cpu_set_t const *cpuset);
/* Get bit set in CPUSET representing the processors threads created with ATTR can run on
 * @return: EOK:    Success
 * @return: EINVAL: `cpusetsize' is too small */
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_getaffinity_np)(pthread_attr_t const *attr, size_t cpusetsize, cpu_set_t *cpuset);
/* Get the default attributes used by pthread_create in this process
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_getattr_default_np)(pthread_attr_t *attr);
/* Set the default attributes to be used by pthread_create in this process
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_setattr_default_np)(pthread_attr_t const *attr);
/* Initialize thread attribute *ATTR with attributes corresponding to the
 * already running thread THREAD. It shall be called on uninitialized ATTR
 * and destroyed with pthread_attr_destroy when no longer needed
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_getattr_np)(pthread_t pthread, pthread_attr_t *attr);
/* Set the scheduling parameters for TARGET_THREAD according to POLICY and *PARAM
 * @return: EOK:    Success
 * @return: EPERM:  The caller isn't allowed to specify `policy' and `param'
 * @return: ESRCH:  `pthread' has already exited
 * @return: EINVAL: Invalid/unsupported `policy', or `param' is malformed for `policy' */
INTDEF NONNULL((3)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_setschedparam)(pthread_t target_thread, int policy, struct sched_param const *param);
/* Return in *POLICY and *PARAM the scheduling parameters for TARGET_THREAD
 * @return: EOK:   Success
 * @return: ESRCH: `pthread' has already exited */
INTDEF NONNULL((2, 3)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_getschedparam)(pthread_t target_thread, int *__restrict policy, struct sched_param *__restrict param);
/* Set the scheduling priority for TARGET_THREAD
 * @return: EOK:    Success
 * @return: EPERM:  The caller isn't allowed to specify `prio'
 * @return: ESRCH:  `pthread' has already exited
 * @return: EINVAL: Invalid/unsupported `prio' */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_setschedprio)(pthread_t target_thread, int prio);
/* Get thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `buflen' is too small */
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_getname_np)(pthread_t target_thread, char *buf, size_t buflen);
/* Set thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `name' is too long */
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_setname_np)(pthread_t target_thread, const char *name);
/* Return the TID of the given `target_thread'.
 * If the given `target_thread' has already terminated, 0 is returned
 * @return: * : The PID OF the given thread
 * @return: 0 : The given `target_thread' has already terminated */
INTDEF ATTR_PURE WUNUSED pid_t NOTHROW_NCX(LIBDCALL libd_pthread_gettid_np)(pthread_t target_thread);
/* Set new concurrency level to LEVEL
 * @return: EOK:    Success
 * @return: EINVAL: The given `level' is negative */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_setconcurrency)(int level);
/* Limit specified thread THREAD to run only on the processors represented in CPUSET
 * @return: EOK:   Success
 * @return: ESRCH: `pthread' has already exited */
INTDEF NONNULL((3)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_setaffinity_np)(pthread_t pthread, size_t cpusetsize, cpu_set_t const *cpuset);
/* Get bit set in CPUSET representing the processors THREAD can run on
 * @return: EOK:   Success
 * @return: ESRCH: `pthread' has already exited */
INTDEF NONNULL((3)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_getaffinity_np)(pthread_t pthread, size_t cpusetsize, cpu_set_t *cpuset);
/* Guarantee that the initialization function INIT_ROUTINE will be called
 * only once, even if pthread_once is executed several times with the
 * same ONCE_CONTROL argument. ONCE_CONTROL must point to a static or
 * extern variable initialized to PTHREAD_ONCE_INIT.
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t (LIBDCALL libd_pthread_once)(pthread_once_t *once_control, __pthread_once_routine_t init_routine) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Guarantee that the initialization function INIT_ROUTINE will be called
 * only once, even if pthread_once is executed several times with the
 * same ONCE_CONTROL argument. ONCE_CONTROL must point to a static or
 * extern variable initialized to PTHREAD_ONCE_INIT.
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t (LIBCCALL libc_pthread_once)(pthread_once_t *once_control, __pthread_once_routine_t init_routine) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Set cancelability state of current thread to STATE,
 * returning old state in *OLDSTATE if OLDSTATE is not NULL
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `state' */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_setcancelstate)(int state, int *oldstate);
/* Set cancellation state of current thread to TYPE,
 * returning the old type in *OLDTYPE if OLDTYPE is not NULL
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `type' */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_setcanceltype)(int type, int *oldtype);
/* Cancel THREAD immediately or at the next possibility
 * @return: EOK:   Success
 * @return: ESRCH: `pthread' has already exited */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_cancel)(pthread_t pthread);
/* Function called to call the cleanup handler. As an extern inline
 * function the compiler is free to decide inlining the change when
 * needed or fall back on the copy which must exist somewhere else */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd___pthread_cleanup_routine)(struct __pthread_cleanup_frame *frame);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Function called to call the cleanup handler. As an extern inline
 * function the compiler is free to decide inlining the change when
 * needed or fall back on the copy which must exist somewhere else */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc___pthread_cleanup_routine)(struct __pthread_cleanup_frame *frame);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF __cleanup_fct_attribute void NOTHROW_NCX(LIBDCALL libd___pthread_register_cancel)(__pthread_unwind_buf_t *buf);
INTDEF __cleanup_fct_attribute NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd___pthread_unregister_cancel)(__pthread_unwind_buf_t *buf);
INTDEF __cleanup_fct_attribute NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd___pthread_register_cancel_defer)(__pthread_unwind_buf_t *buf);
INTDEF __cleanup_fct_attribute NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd___pthread_unregister_cancel_restore)(__pthread_unwind_buf_t *buf);
/* Internal interface to initiate cleanup */
INTDEF ATTR_WEAK __cleanup_fct_attribute NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd___pthread_unwind_next)(__pthread_unwind_buf_t *buf);
/* Initialize a mutex
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutex_init)(pthread_mutex_t *mutex, pthread_mutexattr_t const *mutexattr);
/* Destroy a mutex
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutex_destroy)(pthread_mutex_t *mutex);
/* Try locking a mutex
 * @return: EOK:   Success
 * @return: EBUSY: The mutex has already been locked
 *                 In case of a recursive mutex, another
 *                 thread was the one to acquire the lock. */
INTDEF WUNUSED NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutex_trylock)(pthread_mutex_t *mutex);
/* Lock a mutex
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_mutex_lock)(pthread_mutex_t *mutex);
/* Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF WUNUSED NONNULL((1, 2)) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_mutex_timedlock)(pthread_mutex_t *__restrict mutex, struct timespec const *__restrict abstime);
/* Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF WUNUSED NONNULL((1, 2)) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_mutex_timedlock64)(pthread_mutex_t *__restrict mutex, struct timespec64 const *__restrict abstime);
/* Unlock a mutex
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutex_unlock)(pthread_mutex_t *mutex);
/* Get the priority ceiling of MUTEX
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutex_getprioceiling)(pthread_mutex_t const *__restrict mutex, int *__restrict prioceiling);
/* Set the priority ceiling of MUTEX to PRIOCEILING,
 * return old priority ceiling value in *OLD_CEILING
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `prioceiling' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutex_setprioceiling)(pthread_mutex_t *__restrict mutex, int prioceiling, int *__restrict old_ceiling);
/* Declare the state protected by MUTEX as consistent
 * @return: EOK:    Success
 * @return: EINVAL: Not a robust mutex
 * @return: EINVAL: Mutex was already in a consistent state */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutex_consistent)(pthread_mutex_t *mutex);
/* Initialize mutex attribute object ATTR with default attributes (kind is PTHREAD_MUTEX_TIMED_NP)
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_init)(pthread_mutexattr_t *attr);
/* Destroy mutex attribute object ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_destroy)(pthread_mutexattr_t *attr);
/* Get the process-shared flag of the mutex attribute ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_getpshared)(pthread_mutexattr_t const *__restrict attr, int *__restrict pshared);
/* Set the process-shared flag of the mutex attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_setpshared)(pthread_mutexattr_t *attr, int pshared);
/* Return in *KIND the mutex kind attribute in *ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_gettype)(pthread_mutexattr_t const *__restrict attr, int *__restrict kind);
/* Set the mutex kind attribute in *ATTR to KIND (either PTHREAD_MUTEX_NORMAL,
 * PTHREAD_MUTEX_RECURSIVE, PTHREAD_MUTEX_ERRORCHECK, or PTHREAD_MUTEX_DEFAULT)
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `kind' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_settype)(pthread_mutexattr_t *attr, int kind);
/* Return in *PROTOCOL the mutex protocol attribute in *ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_getprotocol)(pthread_mutexattr_t const *__restrict attr, int *__restrict protocol);
/* Set the mutex protocol attribute in *ATTR to PROTOCOL (either
 * PTHREAD_PRIO_NONE, PTHREAD_PRIO_INHERIT, or PTHREAD_PRIO_PROTECT)
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `protocol' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_setprotocol)(pthread_mutexattr_t *attr, int protocol);
/* Return in *PRIOCEILING the mutex prioceiling attribute in *ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_getprioceiling)(pthread_mutexattr_t const *__restrict attr, int *__restrict prioceiling);
/* Set the mutex prioceiling attribute in *ATTR to PRIOCEILING
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `prioceiling' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_setprioceiling)(pthread_mutexattr_t *attr, int prioceiling);
/* Get the robustness flag of the mutex attribute ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_getrobust)(pthread_mutexattr_t const *attr, int *robustness);
/* Set the robustness flag of the mutex attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `robustness' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_setrobust)(pthread_mutexattr_t *attr, int robustness);
/* Initialize read-write lock RWLOCK using attributes ATTR,
 * or use the default values if later is NULL
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_rwlock_init)(pthread_rwlock_t *__restrict rwlock, pthread_rwlockattr_t const *__restrict attr);
/* Destroy read-write lock RWLOCK
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_rwlock_destroy)(pthread_rwlock_t *rwlock);
/* Acquire read lock for RWLOCK
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_rwlock_rdlock)(pthread_rwlock_t *rwlock);
/* Try to acquire read lock for RWLOCK
 * @return: EOK:   Success
 * @return: EBUSY: A read-lock cannot be acquired at the moment,
 *                 because a write-lock is already being held. */
INTDEF WUNUSED NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_rwlock_tryrdlock)(pthread_rwlock_t *rwlock);
/* Try to acquire read lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF WUNUSED NONNULL((1, 2)) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_rwlock_timedrdlock)(pthread_rwlock_t *__restrict rwlock, struct timespec const *__restrict abstime);
/* Try to acquire read lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF WUNUSED NONNULL((1, 2)) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_rwlock_timedrdlock64)(pthread_rwlock_t *__restrict rwlock, struct timespec64 const *__restrict abstime);
/* Acquire write lock for RWLOCK
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_rwlock_wrlock)(pthread_rwlock_t *rwlock);
/* Try to acquire write lock for RWLOCK
 * @return: EOK:   Success
 * @return: EBUSY: A write-lock cannot be acquired at the moment,
 *                 because read-locks are already being held. */
INTDEF WUNUSED NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_rwlock_trywrlock)(pthread_rwlock_t *rwlock);
/* Try to acquire write lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF WUNUSED NONNULL((1, 2)) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_rwlock_timedwrlock)(pthread_rwlock_t *__restrict rwlock, struct timespec const *__restrict abstime);
/* Try to acquire write lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF WUNUSED NONNULL((1, 2)) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_rwlock_timedwrlock64)(pthread_rwlock_t *__restrict rwlock, struct timespec64 const *__restrict abstime);
/* Unlock RWLOCK
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_rwlock_unlock)(pthread_rwlock_t *rwlock);
/* Initialize attribute object ATTR with default values
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_rwlockattr_init)(pthread_rwlockattr_t *attr);
/* Destroy attribute object ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_rwlockattr_destroy)(pthread_rwlockattr_t *attr);
/* Return current setting of process-shared attribute of ATTR in PSHARED
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_rwlockattr_getpshared)(pthread_rwlockattr_t const *__restrict attr, int *__restrict pshared);
/* Set process-shared attribute of ATTR to PSHARED
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pthread' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_rwlockattr_setpshared)(pthread_rwlockattr_t *attr, int pshared);
/* Return current setting of reader/writer preference
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_rwlockattr_getkind_np)(pthread_rwlockattr_t const *__restrict attr, int *__restrict pref);
/* Set reader/write preference
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pref' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_rwlockattr_setkind_np)(pthread_rwlockattr_t *attr, int pref);
/* Initialize condition variable COND using attributes
 * ATTR, or use the default values if later is NULL
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_cond_init)(pthread_cond_t *__restrict cond, pthread_condattr_t const *__restrict cond_attr);
/* Destroy condition variable COND
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_cond_destroy)(pthread_cond_t *cond);
/* Wake up one thread waiting for condition variable COND
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_cond_signal)(pthread_cond_t *cond);
/* Wake up all threads waiting for condition variables COND
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_cond_broadcast)(pthread_cond_t *cond);
/* Wait for condition variable COND to be signaled or broadcast.
 * MUTEX is assumed to be locked before.
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_cond_wait)(pthread_cond_t *__restrict cond, pthread_mutex_t *__restrict mutex);
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF WUNUSED NONNULL((1, 2, 3)) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_cond_timedwait)(pthread_cond_t *__restrict cond, pthread_mutex_t *__restrict mutex, struct timespec const *__restrict abstime);
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF WUNUSED NONNULL((1, 2, 3)) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_cond_timedwait64)(pthread_cond_t *__restrict cond, pthread_mutex_t *__restrict mutex, struct timespec64 const *__restrict abstime);
/* Initialize condition variable attribute ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_condattr_init)(pthread_condattr_t *attr);
/* Destroy condition variable attribute ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_condattr_destroy)(pthread_condattr_t *attr);
/* Get the process-shared flag of the condition variable attribute ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_condattr_getpshared)(pthread_condattr_t const *__restrict attr, int *__restrict pshared);
/* Set the process-shared flag of the condition variable attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_condattr_setpshared)(pthread_condattr_t *attr, int pshared);
/* Get the clock selected for the condition variable attribute ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_condattr_getclock)(pthread_condattr_t const *__restrict attr, clockid_t *__restrict clock_id);
/* Set the clock selected for the condition variable attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `clock_id' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_condattr_setclock)(pthread_condattr_t *attr, clockid_t clock_id);
/* Initialize the spinlock LOCK. If PSHARED is nonzero the
 * spinlock can be shared between different processes
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_spin_init)(pthread_spinlock_t *lock, int pshared);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Initialize the spinlock LOCK. If PSHARED is nonzero the
 * spinlock can be shared between different processes
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_spin_init)(pthread_spinlock_t *lock, int pshared);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Destroy the spinlock LOCK
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_spin_destroy)(pthread_spinlock_t *lock);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Destroy the spinlock LOCK
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_spin_destroy)(pthread_spinlock_t *lock);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Wait until spinlock LOCK is retrieved
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_spin_lock)(pthread_spinlock_t *lock);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Wait until spinlock LOCK is retrieved
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_spin_lock)(pthread_spinlock_t *lock);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Try to lock spinlock LOCK
 * @return: EOK:   Success
 * @return: EBUSY: Lock has already been acquired */
INTDEF WUNUSED NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_spin_trylock)(pthread_spinlock_t *lock);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Try to lock spinlock LOCK
 * @return: EOK:   Success
 * @return: EBUSY: Lock has already been acquired */
INTDEF WUNUSED NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_spin_trylock)(pthread_spinlock_t *lock);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Release spinlock LOCK
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_spin_unlock)(pthread_spinlock_t *lock);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Release spinlock LOCK
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_spin_unlock)(pthread_spinlock_t *lock);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Initialize BARRIER with the attributes in ATTR.
 * The barrier is opened when COUNT waiters arrived
 * @return: EOK:    Success
 * @return: EINVAL: The given `count' is ZERO(0) */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_barrier_init)(pthread_barrier_t *__restrict barrier, pthread_barrierattr_t const *__restrict attr, unsigned int count);
/* Destroy a previously dynamically initialized barrier BARRIER
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_barrier_destroy)(pthread_barrier_t *barrier);
/* Wait on barrier BARRIER
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_barrier_wait)(pthread_barrier_t *barrier);
/* Initialize barrier attribute ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_barrierattr_init)(pthread_barrierattr_t *attr);
/* Destroy previously dynamically initialized barrier attribute ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_barrierattr_destroy)(pthread_barrierattr_t *attr);
/* Get the process-shared flag of the barrier attribute ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_barrierattr_getpshared)(pthread_barrierattr_t const *__restrict attr, int *__restrict pshared);
/* Set the process-shared flag of the barrier attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_barrierattr_setpshared)(pthread_barrierattr_t *attr, int pshared);
/* Create a key value identifying a location in the thread-specific
 * data area. Each thread maintains a distinct thread-specific data
 * area. DESTR_FUNCTION, if non-NULL, is called with the value
 * associated to that key when the key is destroyed.
 * DESTR_FUNCTION is not called if the value associated is NULL when
 * the key is destroyed
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to create the key */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_key_create)(pthread_key_t *key, __pthread_destr_function_t destr_function);
/* Destroy KEY
 * @return: EOK: Success */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_key_delete)(pthread_key_t key);
/* Return current value of the thread-specific data slot identified by KEY
 * @return: * :   The value currently associated with `key' in the calling thread
 * @return: NULL: The current value is `NULL', or no value has been bound, yet */
INTDEF WUNUSED void *NOTHROW_NCX(LIBDCALL libd_pthread_getspecific)(pthread_key_t key);
/* Store POINTER in the thread-specific data slot identified by KEY
 * @return: EOK:    Success
 * @return: ENOMEM: `pointer' is non-NULL, `key' had yet to be allowed for the
 *                  calling thread, and an attempt to allocate it just now failed */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_setspecific)(pthread_key_t key, void const *pointer);
/* Get ID of CPU-time clock for thread THREAD_ID
 * @return: EOK: Success */
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_getcpuclockid)(pthread_t pthread, clockid_t *clock_id);
/* Install handlers to be called when a new process is created with FORK.
 * The PREPARE handler is called in the parent process just before performing
 * FORK. The PARENT handler is called in the parent process just after FORK.
 * The CHILD handler is called in the child process. Each of the three
 * handlers can be NULL, meaning that no handler needs to be called at that
 * point.
 * PTHREAD_ATFORK can be called several times, in which case the PREPARE
 * handlers are called in LIFO order (last added with PTHREAD_ATFORK,
 * first called before FORK), and the PARENT and CHILD handlers are called
 * in FIFO (first added, first called)
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to register callbacks */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_atfork)(__pthread_atfork_func_t prepare, __pthread_atfork_func_t parent, __pthread_atfork_func_t child);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @return: * : The number of cpus that the calling thread is able to run on */
INTDEF __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_pthread_num_processors_np)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Restrict the calling thread to only run on the first `n' cpus
 * @return: EOK:    Success
 * @return: EINVAL: `n' was specified as less than `1'
 * @return: * :     Same as `errno' after a call to `sched_setaffinity(2)' */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_set_num_processors_np)(int n);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Restrict the calling thread to only run on the first `n' cpus
 * @return: EOK:    Success
 * @return: EINVAL: `n' was specified as less than `1'
 * @return: * :     Same as `errno' after a call to `sched_setaffinity(2)' */
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_pthread_set_num_processors_np)(int n);
/* Returns 1 if the calling thread is the main() thread (i.e. the
 * thread that was started by the kernel in order to execute the
 * calling program), and 0 otherwise. Additionally, -1 is returned
 * if the calling thread "hasn't been initialized", though this
 * isn't a case that can actually happen under KOS's implementation. */
INTDEF ATTR_CONST int NOTHROW(LIBCCALL libc_pthread_main_np)(void);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_PTHREAD_H */
