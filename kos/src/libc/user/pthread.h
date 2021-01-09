/* HASH CRC-32:0x60a6a000 */
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
#ifndef GUARD_LIBC_USER_PTHREAD_H
#define GUARD_LIBC_USER_PTHREAD_H 1

#include "../api.h"
#include "../auto/pthread.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <pthread.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> pthread_create(3)
 * Create a new thread, starting with execution of START-ROUTINE
 * getting passed ARG. Creation attributed come from ATTR. The new
 * handle is stored in *NEWTHREAD
 * @return: EOK:    Success
 * @return: EAGAIN: Insufficient resources, or operation-not-permitted */
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_create)(pthread_t *__restrict newthread, pthread_attr_t const *__restrict attr, __pthread_start_routine_t start_routine, void *__restrict arg);
/* >> pthread_exit(3)
 * Terminate calling thread.
 * The registered cleanup handlers are called via exception handling */
INTDEF ATTR_NORETURN void (LIBCCALL libc_pthread_exit)(void *retval) THROWS(...);
/* >> pthread_join(3)
 * Make calling thread wait for termination of the thread THREAD. The
 * exit status of the thread is stored in *THREAD_RETURN, if THREAD_RETURN
 * is not NULL
 * @return: EOK: Success */
INTDEF errno_t NOTHROW_RPC(LIBCCALL libc_pthread_join)(pthread_t pthread, void **thread_return);
/* >> pthread_tryjoin_np(3)
 * Check whether thread THREAD has terminated. If yes return the status of
 * the thread in *THREAD_RETURN, if THREAD_RETURN is not NULL
 * @return: EOK:   Success
 * @return: EBUSY: The thread has yet to terminate */
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_pthread_tryjoin_np)(pthread_t pthread, void **thread_return);
/* >> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
 * Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF errno_t NOTHROW_RPC(LIBCCALL libc_pthread_timedjoin_np)(pthread_t pthread, void **thread_return, struct timespec const *abstime);
/* >> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
 * Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF errno_t NOTHROW_RPC(LIBCCALL libc_pthread_timedjoin64_np)(pthread_t pthread, void **thread_return, struct timespec64 const *abstime);
/* >> pthread_detach(3)
 * Indicate that the thread THREAD is never to be joined with PTHREAD_JOIN.
 * The resources of THREAD will therefore be freed immediately when it
 * terminates, instead of waiting for another thread to perform PTHREAD_JOIN on it
 * @return: EOK: Success */
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_pthread_detach)(pthread_t pthread);
/* >> pthread_self(3)
 * Obtain the identifier of the current thread
 * @return: * : Handle for the calling thread */
INTDEF ATTR_CONST pthread_t NOTHROW(LIBCCALL libc_pthread_self)(void);
/* >> pthread_attr_init(3)
 * Initialize thread attribute *ATTR with default attributes (detachstate is
 * PTHREAD_JOINABLE, scheduling policy is SCHED_OTHER, no user-provided stack)
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_init)(pthread_attr_t *attr);
/* >> pthread_attr_destroy(3)
 * Destroy thread attribute *ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_destroy)(pthread_attr_t *attr);
/* >> pthread_attr_getdetachstate(3)
 * Get detach state attribute
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_getdetachstate)(pthread_attr_t const *attr, int *detachstate);
/* >> pthread_attr_setdetachstate(3)
 * Set detach state attribute
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `detachstate' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_setdetachstate)(pthread_attr_t *attr, int detachstate);
/* >> pthread_attr_getguardsize(3)
 * Get the size of the guard area created for stack overflow protection
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_getguardsize)(pthread_attr_t const *attr, size_t *guardsize);
/* >> pthread_attr_setguardsize(3)
 * Set the size of the guard area created for stack overflow protection
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_setguardsize)(pthread_attr_t *attr, size_t guardsize);
/* >> pthread_attr_getschedparam(3)
 * Return in *PARAM the scheduling parameters of *ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_getschedparam)(pthread_attr_t const *__restrict attr, struct sched_param *__restrict param);
/* >> pthread_attr_setschedparam(3)
 * Set scheduling parameters (priority, etc) in *ATTR according to PARAM
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `param' */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_setschedparam)(pthread_attr_t *__restrict attr, struct sched_param const *__restrict param);
/* >> pthread_attr_getschedpolicy(3)
 * Return in *POLICY the scheduling policy of *ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_getschedpolicy)(pthread_attr_t const *__restrict attr, int *__restrict policy);
/* >> pthread_attr_setschedpolicy(3)
 * Set scheduling policy in *ATTR according to POLICY
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `policy' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_setschedpolicy)(pthread_attr_t *attr, int policy);
/* >> pthread_attr_getinheritsched(3)
 * Return in *INHERIT the scheduling inheritance mode of *ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_getinheritsched)(pthread_attr_t const *__restrict attr, int *__restrict inherit);
/* >> pthread_attr_setinheritsched(3)
 * Set scheduling inheritance mode in *ATTR according to INHERIT
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `inherit' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_setinheritsched)(pthread_attr_t *attr, int inherit);
/* >> pthread_attr_getscope(3)
 * Return in *SCOPE the scheduling contention scope of *ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_getscope)(pthread_attr_t const *__restrict attr, int *__restrict scope);
/* >> pthread_attr_setscope(3)
 * Set scheduling contention scope in *ATTR according to SCOPE
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `scope' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_setscope)(pthread_attr_t *attr, int scope);
/* >> pthread_attr_getstackaddr(3)
 * Return the previously set address for the stack
 * @return: EOK: Success */
INTDEF ATTR_DEPRECATED("Use pthread_attr_getstack()") NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_getstackaddr)(pthread_attr_t const *__restrict attr, void **__restrict stackaddr);
/* >> pthread_attr_setstackaddr(3)
 * Set the starting address of the stack of the thread to be created.
 * Depending on whether the stack grows up or down the value must either
 * be higher or lower than all the address in the memory block. The
 * minimal size of the block must be PTHREAD_STACK_MIN
 * @return: EOK:    Success
 * @return: EINVAL: The stack isn't suitably aligned */
INTDEF ATTR_DEPRECATED("Use pthread_attr_setstack()") NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_setstackaddr)(pthread_attr_t *attr, void *stackaddr);
/* >> pthread_attr_getstacksize(3)
 * Return the currently used minimal stack size
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_getstacksize)(pthread_attr_t const *__restrict attr, size_t *__restrict stacksize);
/* >> pthread_attr_setstacksize(3)
 * Add information about the minimum stack size needed for the thread
 * to be started. This size must never be less than PTHREAD_STACK_MIN
 * and must also not exceed the system limits
 * @return: EOK:    Success
 * @return: EINVAL: `stacksize' is too small */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_setstacksize)(pthread_attr_t *attr, size_t stacksize);
/* >> pthread_attr_getstack(3)
 * Return the previously set address for the stack
 * @return: EOK: Success */
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_getstack)(pthread_attr_t const *__restrict attr, void **__restrict stackaddr, size_t *__restrict stacksize);
/* >> pthread_attr_setstack(3)
 * The following two interfaces are intended to replace the last two. They
 * require setting the address as well as the size since only setting the
 * address will make the implementation on some architectures impossible
 * @return: EOK:    Success
 * @return: EINVAL: `stacksize' is too small, or the stack isn't suitably aligned */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_setstack)(pthread_attr_t *attr, void *stackaddr, size_t stacksize);
/* >> pthread_attr_setaffinity_np(3)
 * Thread created with attribute ATTR will be limited to run only on
 * the processors represented in CPUSET
 * @return: EOK:    Success
 * @return: EINVAL: The given set contains a non-existant CPU
 * @return: ENOMEM: Insufficient memory */
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_setaffinity_np)(pthread_attr_t *attr, size_t cpusetsize, cpu_set_t const *cpuset);
/* >> pthread_attr_getaffinity_np(3)
 * Get bit set in CPUSET representing the processors threads created with ATTR can run on
 * @return: EOK:    Success
 * @return: EINVAL: `cpusetsize' is too small */
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_getaffinity_np)(pthread_attr_t const *attr, size_t cpusetsize, cpu_set_t *cpuset);
/* >> pthread_getattr_default_np(3)
 * Get the default attributes used by pthread_create in this process
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_getattr_default_np)(pthread_attr_t *attr);
/* >> pthread_setattr_default_np(3)
 * Set the default attributes to be used by pthread_create in this process
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_setattr_default_np)(pthread_attr_t const *attr);
/* >> pthread_getattr_np(3)
 * Initialize thread attribute *ATTR with attributes corresponding to the
 * already running thread THREAD. It shall be called on uninitialized ATTR
 * and destroyed with pthread_attr_destroy when no longer needed
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_getattr_np)(pthread_t pthread, pthread_attr_t *attr);
/* >> pthread_gettid_np(3)
 * Set the scheduling parameters for TARGET_THREAD according to POLICY and *PARAM
 * @return: EOK:    Success
 * @return: EPERM:  The caller isn't allowed to specify `policy' and `param'
 * @return: ESRCH:  `pthread' has already exited
 * @return: EINVAL: Invalid/unsupported `policy', or `param' is malformed for `policy' */
INTDEF NONNULL((3)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_setschedparam)(pthread_t target_thread, int policy, struct sched_param const *param);
/* >> pthread_gettid_np(3)
 * Return in *POLICY and *PARAM the scheduling parameters for TARGET_THREAD
 * @return: EOK:   Success
 * @return: ESRCH: `pthread' has already exited */
INTDEF NONNULL((2, 3)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_getschedparam)(pthread_t target_thread, int *__restrict policy, struct sched_param *__restrict param);
/* >> pthread_gettid_np(3)
 * Set the scheduling priority for TARGET_THREAD
 * @return: EOK:    Success
 * @return: EPERM:  The caller isn't allowed to specify `prio'
 * @return: ESRCH:  `pthread' has already exited
 * @return: EINVAL: Invalid/unsupported `prio' */
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_pthread_setschedprio)(pthread_t target_thread, int prio);
/* >> pthread_gettid_np(3)
 * Get thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `buflen' is too small */
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_getname_np)(pthread_t target_thread, char *buf, size_t buflen);
/* >> pthread_gettid_np(3)
 * Set thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `name' is too long */
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_setname_np)(pthread_t target_thread, const char *name);
/* >> pthread_gettid_np(3)
 * Return the TID of the given `target_thread'.
 * If the given `target_thread' has already terminated, 0 is returned
 * @return: * : The PID OF the given thread
 * @return: 0 : The given `target_thread' has already terminated */
INTDEF ATTR_PURE WUNUSED pid_t NOTHROW_NCX(LIBCCALL libc_pthread_gettid_np)(pthread_t target_thread);
/* >> pthread_getconcurrency(3)
 * Determine level of concurrency
 * @return: * : The current concurrency level */
INTDEF ATTR_PURE int NOTHROW_NCX(LIBCCALL libc_pthread_getconcurrency)(void);
/* >> pthread_setconcurrency(3)
 * Set new concurrency level to LEVEL
 * @return: EOK:    Success
 * @return: EINVAL: The given `level' is negative */
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_pthread_setconcurrency)(int level);
/* >> pthread_setaffinity_np(3)
 * Limit specified thread THREAD to run only on the processors represented in CPUSET
 * @return: EOK:   Success
 * @return: ESRCH: `pthread' has already exited */
INTDEF NONNULL((3)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_setaffinity_np)(pthread_t pthread, size_t cpusetsize, cpu_set_t const *cpuset);
/* >> pthread_getaffinity_np(3)
 * Get bit set in CPUSET representing the processors THREAD can run on
 * @return: EOK:   Success
 * @return: ESRCH: `pthread' has already exited */
INTDEF NONNULL((3)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_getaffinity_np)(pthread_t pthread, size_t cpusetsize, cpu_set_t *cpuset);
/* >> pthread_setcancelstate(3)
 * Set cancelability state of current thread to STATE,
 * returning old state in *OLDSTATE if OLDSTATE is not NULL
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `state' */
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_pthread_setcancelstate)(int state, int *oldstate);
/* >> pthread_setcanceltype(3)
 * Set cancellation state of current thread to TYPE,
 * returning the old type in *OLDTYPE if OLDTYPE is not NULL
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `type' */
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_pthread_setcanceltype)(int type, int *oldtype);
/* >> pthread_cancel(3)
 * Cancel THREAD immediately or at the next possibility
 * @return: EOK:   Success
 * @return: ESRCH: `pthread' has already exited */
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_pthread_cancel)(pthread_t pthread);
/* >> pthread_testcancel(3)
 * Test for pending cancellation for the current thread and terminate
 * the thread as per pthread_exit(PTHREAD_CANCELED) if it has been canceled */
INTDEF void NOTHROW_RPC(LIBCCALL libc_pthread_testcancel)(void);
INTDEF __cleanup_fct_attribute void NOTHROW_NCX(LIBCCALL libc___pthread_register_cancel)(__pthread_unwind_buf_t *buf);
INTDEF __cleanup_fct_attribute NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc___pthread_unregister_cancel)(__pthread_unwind_buf_t *buf);
INTDEF __cleanup_fct_attribute NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc___pthread_register_cancel_defer)(__pthread_unwind_buf_t *buf);
INTDEF __cleanup_fct_attribute NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc___pthread_unregister_cancel_restore)(__pthread_unwind_buf_t *buf);
/* Internal interface to initiate cleanup */
INTDEF ATTR_WEAK __cleanup_fct_attribute NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc___pthread_unwind_next)(__pthread_unwind_buf_t *buf);
/* >> pthread_mutex_init(3)
 * Initialize a mutex
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_mutex_init)(pthread_mutex_t *mutex, pthread_mutexattr_t const *mutexattr);
/* >> pthread_mutex_destroy(3)
 * Destroy a mutex
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_mutex_destroy)(pthread_mutex_t *mutex);
/* >> pthread_mutex_trylock(3)
 * Try locking a mutex
 * @return: EOK:   Success
 * @return: EBUSY: The mutex has already been locked
 *                 In case of a recursive mutex, another
 *                 thread was the one to acquire the lock. */
INTDEF WUNUSED NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_mutex_trylock)(pthread_mutex_t *mutex);
/* >> pthread_mutex_lock(3)
 * Lock a mutex
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_RPC(LIBCCALL libc_pthread_mutex_lock)(pthread_mutex_t *mutex);
/* >> pthread_mutex_timedlock(3), pthread_mutex_timedlock64(3)
 * Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF WUNUSED NONNULL((1, 2)) errno_t NOTHROW_RPC(LIBCCALL libc_pthread_mutex_timedlock)(pthread_mutex_t *__restrict mutex, struct timespec const *__restrict abstime);
/* >> pthread_mutex_timedlock(3), pthread_mutex_timedlock64(3)
 * Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF WUNUSED NONNULL((1, 2)) errno_t NOTHROW_RPC(LIBCCALL libc_pthread_mutex_timedlock64)(pthread_mutex_t *__restrict mutex, struct timespec64 const *__restrict abstime);
/* >> pthread_mutex_unlock(3)
 * Unlock a mutex
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_mutex_unlock)(pthread_mutex_t *mutex);
/* >> pthread_mutex_getprioceiling(3)
 * Get the priority ceiling of MUTEX
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_mutex_getprioceiling)(pthread_mutex_t const *__restrict mutex, int *__restrict prioceiling);
/* >> pthread_mutex_setprioceiling(3)
 * Set the priority ceiling of MUTEX to PRIOCEILING,
 * return old priority ceiling value in *OLD_CEILING
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `prioceiling' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_mutex_setprioceiling)(pthread_mutex_t *__restrict mutex, int prioceiling, int *__restrict old_ceiling);
/* >> pthread_mutex_consistent(3)
 * Declare the state protected by MUTEX as consistent
 * @return: EOK:    Success
 * @return: EINVAL: Not a robust mutex
 * @return: EINVAL: Mutex was already in a consistent state */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_mutex_consistent)(pthread_mutex_t *mutex);
/* >> pthread_mutexattr_init(3)
 * Initialize mutex attribute object ATTR with default attributes (kind is PTHREAD_MUTEX_TIMED_NP)
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_init)(pthread_mutexattr_t *attr);
/* >> pthread_mutexattr_destroy(3)
 * Destroy mutex attribute object ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_destroy)(pthread_mutexattr_t *attr);
/* >> pthread_mutexattr_getpshared(3)
 * Get the process-shared flag of the mutex attribute ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_getpshared)(pthread_mutexattr_t const *__restrict attr, int *__restrict pshared);
/* >> pthread_mutexattr_setpshared(3)
 * Set the process-shared flag of the mutex attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_setpshared)(pthread_mutexattr_t *attr, int pshared);
/* >> pthread_mutexattr_gettype(3)
 * Return in *KIND the mutex kind attribute in *ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_gettype)(pthread_mutexattr_t const *__restrict attr, int *__restrict kind);
/* >> pthread_mutexattr_settype(3)
 * Set the mutex kind attribute in *ATTR to KIND (either PTHREAD_MUTEX_NORMAL,
 * PTHREAD_MUTEX_RECURSIVE, PTHREAD_MUTEX_ERRORCHECK, or PTHREAD_MUTEX_DEFAULT)
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `kind' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_settype)(pthread_mutexattr_t *attr, int kind);
/* >> pthread_mutexattr_getprotocol(3)
 * Return in *PROTOCOL the mutex protocol attribute in *ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_getprotocol)(pthread_mutexattr_t const *__restrict attr, int *__restrict protocol);
/* >> pthread_mutexattr_setprotocol(3)
 * Set the mutex protocol attribute in *ATTR to PROTOCOL (either
 * PTHREAD_PRIO_NONE, PTHREAD_PRIO_INHERIT, or PTHREAD_PRIO_PROTECT)
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `protocol' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_setprotocol)(pthread_mutexattr_t *attr, int protocol);
/* >> pthread_mutexattr_getprioceiling(3)
 * Return in *PRIOCEILING the mutex prioceiling attribute in *ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_getprioceiling)(pthread_mutexattr_t const *__restrict attr, int *__restrict prioceiling);
/* >> pthread_mutexattr_setprioceiling(3)
 * Set the mutex prioceiling attribute in *ATTR to PRIOCEILING
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `prioceiling' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_setprioceiling)(pthread_mutexattr_t *attr, int prioceiling);
/* >> pthread_mutexattr_getrobust(3)
 * Get the robustness flag of the mutex attribute ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_getrobust)(pthread_mutexattr_t const *attr, int *robustness);
/* >> pthread_mutexattr_setrobust(3)
 * Set the robustness flag of the mutex attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `robustness' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_setrobust)(pthread_mutexattr_t *attr, int robustness);
/* >> pthread_rwlock_init(3)
 * Initialize read-write lock RWLOCK using attributes ATTR,
 * or use the default values if later is NULL
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_init)(pthread_rwlock_t *__restrict rwlock, pthread_rwlockattr_t const *__restrict attr);
/* >> pthread_rwlock_destroy(3)
 * Destroy read-write lock RWLOCK
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_destroy)(pthread_rwlock_t *rwlock);
/* >> pthread_rwlock_rdlock(3)
 * Acquire read lock for RWLOCK
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_rdlock)(pthread_rwlock_t *rwlock);
/* >> pthread_rwlock_tryrdlock(3)
 * Try to acquire read lock for RWLOCK
 * @return: EOK:   Success
 * @return: EBUSY: A read-lock cannot be acquired at the moment,
 *                 because a write-lock is already being held. */
INTDEF WUNUSED NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_tryrdlock)(pthread_rwlock_t *rwlock);
/* >> pthread_rwlock_timedrdlock(3)
 * Try to acquire read lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF WUNUSED NONNULL((1, 2)) errno_t NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_timedrdlock)(pthread_rwlock_t *__restrict rwlock, struct timespec const *__restrict abstime);
/* >> pthread_rwlock_timedrdlock(3)
 * Try to acquire read lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF WUNUSED NONNULL((1, 2)) errno_t NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_timedrdlock64)(pthread_rwlock_t *__restrict rwlock, struct timespec64 const *__restrict abstime);
/* >> pthread_rwlock_wrlock(3)
 * Acquire write lock for RWLOCK
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_wrlock)(pthread_rwlock_t *rwlock);
/* >> pthread_rwlock_trywrlock(3)
 * Try to acquire write lock for RWLOCK
 * @return: EOK:   Success
 * @return: EBUSY: A write-lock cannot be acquired at the moment,
 *                 because read-locks are already being held. */
INTDEF WUNUSED NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_trywrlock)(pthread_rwlock_t *rwlock);
/* >> pthread_rwlock_timedwrlock(3), pthread_rwlock_timedwrlock64(3)
 * Try to acquire write lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF WUNUSED NONNULL((1, 2)) errno_t NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_timedwrlock)(pthread_rwlock_t *__restrict rwlock, struct timespec const *__restrict abstime);
/* >> pthread_rwlock_timedwrlock(3), pthread_rwlock_timedwrlock64(3)
 * Try to acquire write lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF WUNUSED NONNULL((1, 2)) errno_t NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_timedwrlock64)(pthread_rwlock_t *__restrict rwlock, struct timespec64 const *__restrict abstime);
/* >> pthread_rwlock_unlock(3)
 * Unlock RWLOCK
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_unlock)(pthread_rwlock_t *rwlock);
/* >> pthread_rwlockattr_init(3)
 * Initialize attribute object ATTR with default values
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_init)(pthread_rwlockattr_t *attr);
/* >> pthread_rwlockattr_destroy(3)
 * Destroy attribute object ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_destroy)(pthread_rwlockattr_t *attr);
/* >> pthread_rwlockattr_getpshared(3)
 * Return current setting of process-shared attribute of ATTR in PSHARED
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_getpshared)(pthread_rwlockattr_t const *__restrict attr, int *__restrict pshared);
/* >> pthread_rwlockattr_setpshared(3)
 * Set process-shared attribute of ATTR to PSHARED
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pthread' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_setpshared)(pthread_rwlockattr_t *attr, int pshared);
/* >> pthread_rwlockattr_getkind_np(3)
 * Return current setting of reader/writer preference
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_getkind_np)(pthread_rwlockattr_t const *__restrict attr, int *__restrict pref);
/* >> pthread_rwlockattr_setkind_np(3)
 * Set reader/write preference
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pref' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_setkind_np)(pthread_rwlockattr_t *attr, int pref);
/* >> pthread_cond_init(3)
 * Initialize condition variable COND using attributes
 * ATTR, or use the default values if later is NULL
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_cond_init)(pthread_cond_t *__restrict cond, pthread_condattr_t const *__restrict cond_attr);
/* >> pthread_cond_destroy(3)
 * Destroy condition variable COND
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_cond_destroy)(pthread_cond_t *cond);
/* >> pthread_cond_signal(3)
 * Wake up one thread waiting for condition variable COND
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_cond_signal)(pthread_cond_t *cond);
/* >> pthread_cond_broadcast(3)
 * Wake up all threads waiting for condition variables COND
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_cond_broadcast)(pthread_cond_t *cond);
/* >> pthread_cond_wait(3)
 * Wait for condition variable COND to be signaled or broadcast.
 * MUTEX is assumed to be locked before.
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_RPC(LIBCCALL libc_pthread_cond_wait)(pthread_cond_t *__restrict cond, pthread_mutex_t *__restrict mutex);
/* >> pthread_cond_timedwait(3), pthread_cond_timedwait64(3)
 * Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF WUNUSED NONNULL((1, 2, 3)) errno_t NOTHROW_RPC(LIBCCALL libc_pthread_cond_timedwait)(pthread_cond_t *__restrict cond, pthread_mutex_t *__restrict mutex, struct timespec const *__restrict abstime);
/* >> pthread_cond_timedwait(3), pthread_cond_timedwait64(3)
 * Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF WUNUSED NONNULL((1, 2, 3)) errno_t NOTHROW_RPC(LIBCCALL libc_pthread_cond_timedwait64)(pthread_cond_t *__restrict cond, pthread_mutex_t *__restrict mutex, struct timespec64 const *__restrict abstime);
/* >> pthread_condattr_init(3)
 * Initialize condition variable attribute ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_condattr_init)(pthread_condattr_t *attr);
/* >> pthread_condattr_destroy(3)
 * Destroy condition variable attribute ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_condattr_destroy)(pthread_condattr_t *attr);
/* >> pthread_condattr_getpshared(3)
 * Get the process-shared flag of the condition variable attribute ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_condattr_getpshared)(pthread_condattr_t const *__restrict attr, int *__restrict pshared);
/* >> pthread_condattr_setpshared(3)
 * Set the process-shared flag of the condition variable attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_condattr_setpshared)(pthread_condattr_t *attr, int pshared);
/* >> pthread_condattr_getclock(3)
 * Get the clock selected for the condition variable attribute ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_condattr_getclock)(pthread_condattr_t const *__restrict attr, clockid_t *__restrict clock_id);
/* >> pthread_condattr_setclock(3)
 * Set the clock selected for the condition variable attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `clock_id' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_condattr_setclock)(pthread_condattr_t *attr, clockid_t clock_id);
/* >> pthread_barrier_init(3)
 * Initialize BARRIER with the attributes in ATTR.
 * The barrier is opened when COUNT waiters arrived
 * @return: EOK:    Success
 * @return: EINVAL: The given `count' is ZERO(0) */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_barrier_init)(pthread_barrier_t *__restrict barrier, pthread_barrierattr_t const *__restrict attr, unsigned int count);
/* >> pthread_barrier_destroy(3)
 * Destroy a previously dynamically initialized barrier BARRIER
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_barrier_destroy)(pthread_barrier_t *barrier);
/* >> pthread_barrier_wait(3)
 * Wait on barrier BARRIER
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_RPC(LIBCCALL libc_pthread_barrier_wait)(pthread_barrier_t *barrier);
/* >> pthread_barrierattr_init(3)
 * Initialize barrier attribute ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_barrierattr_init)(pthread_barrierattr_t *attr);
/* >> pthread_barrierattr_destroy(3)
 * Destroy previously dynamically initialized barrier attribute ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_barrierattr_destroy)(pthread_barrierattr_t *attr);
/* >> pthread_barrierattr_getpshared(3)
 * Get the process-shared flag of the barrier attribute ATTR
 * @return: EOK: Success */
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_barrierattr_getpshared)(pthread_barrierattr_t const *__restrict attr, int *__restrict pshared);
/* >> pthread_barrierattr_setpshared(3)
 * Set the process-shared flag of the barrier attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_barrierattr_setpshared)(pthread_barrierattr_t *attr, int pshared);
/* >> pthread_key_create(3)
 * Create a key value identifying a location in the thread-specific
 * data area. Each thread maintains a distinct thread-specific data
 * area. DESTR_FUNCTION, if non-NULL, is called with the value
 * associated to that key when the key is destroyed.
 * DESTR_FUNCTION is not called if the value associated is NULL when
 * the key is destroyed
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to create the key */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_key_create)(pthread_key_t *key, __pthread_destr_function_t destr_function);
/* >> pthread_key_delete(3)
 * Destroy KEY
 * @return: EOK:    Success
 * @return: EINVAL: Invalid `key' */
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_pthread_key_delete)(pthread_key_t key);
/* >> pthread_getspecific(3)
 * Return current value of the thread-specific data slot identified by KEY
 * @return: * :   The value currently associated with `key' in the calling thread
 * @return: NULL: The current value is `NULL'
 * @return: NULL: No value has been bound, yet
 * @return: NULL: Invalid `key' */
INTDEF WUNUSED void *NOTHROW_NCX(LIBCCALL libc_pthread_getspecific)(pthread_key_t key);
/* >> pthread_setspecific(3)
 * Store POINTER in the thread-specific data slot identified by KEY
 * @return: EOK:    Success
 * @return: EINVAL: Invalid `key'
 * @return: ENOMEM: `pointer' is non-NULL, `key' had yet to be allowed for the
 *                  calling thread, and an attempt to allocate it just now failed */
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_pthread_setspecific)(pthread_key_t key, void const *pointer);
/* >> pthread_getcpuclockid(3)
 * Get ID of CPU-time clock for thread THREAD_ID
 * @return: EOK: Success */
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_getcpuclockid)(pthread_t pthread, clockid_t *clock_id);
/* >> pthread_atfork(3)
 * Install handlers to be called when a new process is created with FORK.
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
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_pthread_atfork)(__pthread_atfork_func_t prepare, __pthread_atfork_func_t parent, __pthread_atfork_func_t child);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_PTHREAD_H */
