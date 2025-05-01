/* HASH CRC-32:0xa7d08585 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
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

#include <pthread_np.h>
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> pthread_exit(3)
 * Terminate calling thread.
 * The registered cleanup handlers are called via exception handling */
INTDEF ATTR_NORETURN ATTR_ACCESS_NONE(1) void (LIBDCALL libd_pthread_exit)(void *retval);
/* >> pthread_join(3)
 * Make calling thread wait for termination of the thread  `self'.
 * The exit status of the thread is stored in `*thread_return', if
 * `thread_return' is not `NULL'.
 * @return: EOK: Success */
INTDEF ATTR_OUT_OPT(2) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_join)(pthread_t self, void **thread_return);
/* >> pthread_getresult_np(3)
 * Same as `pthread_join(3)', but don't destroy `self' at the end.
 * Instead, the caller must destroy `self' themselves via  another
 * call to `pthread_detach(3)'.
 * @return: EOK: Success */
INTDEF ATTR_OUT_OPT(2) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_getresult_np)(pthread_t self, void **thread_return);
/* >> pthread_tryjoin_np(3)
 * Check whether thread  `self' has terminated.  If so return  the
 * status of the thread in `*thread_return', if `thread_return' is
 * not `NULL'.
 * @return: EOK:   Success
 * @return: EBUSY: The thread has yet to terminate */
INTDEF ATTR_OUT_OPT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_tryjoin_np)(pthread_t self, void **thread_return);
/* >> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
 * Make calling thread  wait for termination  of the thread  `self',
 * but only until `timeout'. The exit status of the thread is stored
 * in  `*thread_return',   if   `thread_return'   is   not   `NULL'.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF ATTR_IN_OPT(3) ATTR_OUT_OPT(2) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_timedjoin_np)(pthread_t self, void **thread_return, struct timespec const *abstime);
/* >> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
 * Make calling thread  wait for termination  of the thread  `self',
 * but only until `timeout'. The exit status of the thread is stored
 * in  `*thread_return',   if   `thread_return'   is   not   `NULL'.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF ATTR_IN_OPT(3) ATTR_OUT_OPT(2) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_timedjoin64_np)(pthread_t self, void **thread_return, struct timespec64 const *abstime);
/* >> pthread_detach(3)
 * Indicate that the thread `self' is  never to be joined with  `pthread_join(3)'.
 * The resources of `self' will therefore be freed immediately when it terminates,
 * instead of waiting for another thread to perform `pthread_join(3)' on it
 * @return: EOK: Success */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_detach)(pthread_t self);
/* >> pthread_equal(3)
 * Compare two thread identifiers
 * @return: 0 : Given threads are non-equal
 * @return: * : Given threads are equal */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_pthread_equal)(pthread_t thr1, pthread_t thr2);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> pthread_equal(3)
 * Compare two thread identifiers
 * @return: 0 : Given threads are non-equal
 * @return: * : Given threads are equal */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_pthread_equal)(pthread_t thr1, pthread_t thr2);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> pthread_attr_init(3)
 * Initialize thread  attribute `*self'  with default  attributes (detachstate  is
 * `PTHREAD_JOINABLE', scheduling policy is `SCHED_OTHER', no user-provided stack)
 * @return: EOK: Success */
INTDEF ATTR_OUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_init)(pthread_attr_t *self);
/* >> pthread_attr_destroy(3)
 * Destroy thread attribute `*self'
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_destroy)(pthread_attr_t *self);
/* >> pthread_attr_getdetachstate(3)
 * Get   detach   state    attribute
 * @param: *detachstate: One of `PTHREAD_CREATE_JOINABLE', `PTHREAD_CREATE_DETACHED'
 * @return: EOK: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_getdetachstate)(pthread_attr_t const *__restrict self, int *__restrict detachstate);
/* >> pthread_attr_setdetachstate(3)
 * Set   detach   state    attribute
 * @param: detachstate: One of `PTHREAD_CREATE_JOINABLE', `PTHREAD_CREATE_DETACHED'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `detachstate' */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setdetachstate)(pthread_attr_t *self, int detachstate);
/* >> pthread_attr_getguardsize(3)
 * Get the size of the guard area created for stack overflow protection
 * @return: EOK: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_getguardsize)(pthread_attr_t const *__restrict self, size_t *__restrict guardsize);
/* >> pthread_attr_setguardsize(3)
 * Set the size of the guard area created for stack overflow protection
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setguardsize)(pthread_attr_t *self, size_t guardsize);
/* >> pthread_attr_getschedparam(3)
 * Return in `*param' the scheduling parameters of `*self'
 * @return: EOK: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_getschedparam)(pthread_attr_t const *__restrict self, struct sched_param *__restrict param);
/* >> pthread_attr_setschedparam(3)
 * Set scheduling parameters (priority, etc) in `*self' according to `param'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `param' */
INTDEF ATTR_IN(2) ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setschedparam)(pthread_attr_t *__restrict self, struct sched_param const *__restrict param);
/* >> pthread_attr_getschedpolicy(3)
 * Return in `*policy' the scheduling policy of `*self'
 * @return: EOK: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_getschedpolicy)(pthread_attr_t const *__restrict self, int *__restrict policy);
/* >> pthread_attr_setschedpolicy(3)
 * Set scheduling policy in `*self' according to `policy'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `policy' */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setschedpolicy)(pthread_attr_t *self, int policy);
/* >> pthread_attr_getinheritsched(3)
 * Return in `*inherit' the scheduling inheritance mode of `*self'
 * @return: EOK: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_getinheritsched)(pthread_attr_t const *__restrict self, int *__restrict inherit);
/* >> pthread_attr_setinheritsched(3)
 * Set scheduling inheritance mode in `*self' according to `inherit'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `inherit' */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setinheritsched)(pthread_attr_t *self, int inherit);
/* >> pthread_attr_getscope(3)
 * Return in `*scope' the scheduling contention scope of `*self'
 * @param:  scope: Filled with one of `PTHREAD_SCOPE_*'
 * @return: EOK: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_getscope)(pthread_attr_t const *__restrict self, int *__restrict scope);
/* >> pthread_attr_setscope(3)
 * Set scheduling contention scope in `*self' according to `scope'
 * @param:  scope:  One of `PTHREAD_SCOPE_*'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `scope' */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setscope)(pthread_attr_t *self, int scope);
/* >> pthread_attr_getstackaddr(3)
 * Return the previously set address for the stack
 * @return: EOK: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_getstackaddr)(pthread_attr_t const *__restrict self, void **__restrict stackaddr);
/* >> pthread_attr_setstackaddr(3)
 * Set the starting address  of the stack of  the thread to be  created.
 * Depending on whether the stack grows up or down the value must either
 * be higher or  lower than  all the address  in the  memory block.  The
 * minimal size of the block must be `PTHREAD_STACK_MIN'
 * @return: EOK:    Success
 * @return: EINVAL: The stack isn't suitably aligned */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setstackaddr)(pthread_attr_t *self, void *stackaddr);
/* >> pthread_attr_getstacksize(3)
 * Return the currently used minimal stack size
 * @return: EOK: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_getstacksize)(pthread_attr_t const *__restrict self, size_t *__restrict stacksize);
/* >> pthread_attr_setstacksize(3)
 * Add information about the minimum  stack size needed for the  thread
 * to be started. This size must never be less than `PTHREAD_STACK_MIN'
 * and must also not exceed the system limits
 * @return: EOK:    Success
 * @return: EINVAL: `stacksize' is too small */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setstacksize)(pthread_attr_t *self, size_t stacksize);
/* >> pthread_attr_getstack(3)
 * Return the previously set address for the stack
 * @return: EOK: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(3) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_getstack)(pthread_attr_t const *__restrict self, void **__restrict stackaddr, size_t *__restrict stacksize);
/* >> pthread_attr_setstack(3)
 * The following two interfaces are intended to replace the last two. They
 * require setting the address as well as the size since only setting  the
 * address will make the implementation on some architectures impossible
 * @return: EOK:    Success
 * @return: EINVAL: `stacksize' is too small, or the stack isn't suitably aligned */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setstack)(pthread_attr_t *self, void *stackaddr, size_t stacksize);
/* >> pthread_attr_setaffinity_np(3)
 * Set cpuset on which the thread will be allowed to run
 * @return: EOK:    Success
 * @return: EINVAL: The given set contains a non-existant CPU
 * @return: ENOMEM: Insufficient memory */
INTDEF ATTR_INOUT(1) ATTR_IN_OPT(3) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setaffinity_np)(pthread_attr_t *self, size_t cpusetsize, cpu_set_t const *cpuset);
/* >> pthread_attr_getaffinity_np(3)
 * Get cpuset on which the thread will be allowed to run
 * @return: EOK:    Success
 * @return: EINVAL: `cpusetsize' is too small */
INTDEF ATTR_IN(1) ATTR_OUT_OPT(3) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_getaffinity_np)(pthread_attr_t const *self, size_t cpusetsize, cpu_set_t *cpuset);
/* >> pthread_getattr_default_np(3)
 * Get the default attributes used by `pthread_create(3)' when given `NULL' for its `attr' argument.
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
INTDEF ATTR_OUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_getattr_default_np)(pthread_attr_t *attr);
/* >> pthread_setattr_default_np(3)
 * Set the default attributes to be used by `pthread_create(3)' when given `NULL' for its `attr' argument.
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
INTDEF ATTR_IN(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_setattr_default_np)(pthread_attr_t const *attr);
/* >> pthread_getattr_np(3)
 * Initialize thread attribute `*attr' with attributes corresponding to  the
 * already running thread `self'. It shall be called on uninitialized `attr'
 * and destroyed with `pthread_attr_destroy(3)' when no longer needed
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
INTDEF ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_getattr_np)(pthread_t self, pthread_attr_t *attr);
/* >> pthread_setschedparam(3)
 * Set the scheduling parameters for `self' according to `policy' and `*param'
 * @return: EOK:    Success
 * @return: EPERM:  The caller isn't allowed to specify `policy' and `param'
 * @return: ESRCH:  `self' has already exited
 * @return: EINVAL: Invalid/unsupported `policy', or `param' is malformed for `policy' */
INTDEF ATTR_IN(3) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_setschedparam)(pthread_t self, int policy, struct sched_param const *param);
/* >> pthread_getschedparam(3)
 * Return in `*policy' and `*param' the scheduling parameters for `self'
 * @return: EOK:   Success
 * @return: ESRCH: `self' has already exited */
INTDEF ATTR_OUT(2) ATTR_OUT(3) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_getschedparam)(pthread_t self, int *__restrict policy, struct sched_param *__restrict param);
/* >> pthread_setschedprio(3)
 * Set the scheduling priority for `self'
 * @return: EOK:    Success
 * @return: EPERM:  The caller isn't allowed to specify `prio'
 * @return: ESRCH:  `self' has already exited
 * @return: EINVAL: Invalid/unsupported `prio' */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_setschedprio)(pthread_t self, int prio);
/* >> pthread_getname_np(3)
 * Get thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `buflen' is too small */
INTDEF ATTR_OUTS(2, 3) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_getname_np)(pthread_t self, char *buf, size_t buflen);
/* >> pthread_setname_np(3)
 * Set thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `name' is too long */
INTDEF ATTR_IN(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_setname_np)(pthread_t self, const char *name);
/* >> pthread_gettid_np(3)
 * Return the TID of the given `self'.
 * If `self' has already terminated, 0 is returned
 * @return: * : The TID of the given thread
 * @return: 0 : The given `self' has already terminated */
INTDEF ATTR_PURE WUNUSED pid_t NOTHROW_NCX(LIBDCALL libd_pthread_gettid_np)(pthread_t self);
/* >> pthread_getpidfd_np(3)
 * Return a PIDfd for `self'. If not already allocated, allocate a PIDfd  lazily.
 * To  guaranty that a PIDfd is available for a given thread, you can make use of
 * `pthread_attr_setpidfdallocated_np()' to have `pthread_create(3)' allocate the
 * PIDfd for you.
 * @return: EOK:    Success: the PIDfd of the given thread was stored in `*p_pidfd'
 * @return: ESRCH:  The given `self' has already terminated (only when not already allocated)
 * @return: EMFILE: Too many open files (process) (only when not already allocated)
 * @return: ENFILE: Too many open files (system) (only when not already allocated)
 * @return: ENOMEM: Insufficient memory (only when not already allocated) */
INTDEF ATTR_PURE WUNUSED ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_getpidfd_np)(pthread_t self, fd_t *__restrict p_pidfd);
/* >> pthread_attr_setpidfdallocated_np(3)
 * Specify if `pthread_create(3)' should allocate a PIDfd for new  threads.
 * Said PIDfd can be retrieved (or lazily allocated when not pre-allocated)
 * via `pthread_getpidfd_np(3)'
 * @param: allocated: 0=no (default) or 1=yes
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `allocated' */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setpidfdallocated_np)(pthread_attr_t *self, int allocated);
/* >> pthread_attr_getpidfdallocated_np(3)
 * Write 0=no or  1=yes to `*allocated',  indicative of  `pthread_create(3)'
 * automatically allocating a PIDfd descriptor for the newly spawned thread.
 * @return: EOK: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_getpidfdallocated_np)(pthread_attr_t const *__restrict self, int *__restrict allocated);
/* >> pthread_setconcurrency(3)
 * Set new concurrency level to `level'
 * @return: EOK:    Success
 * @return: EINVAL: The given `level' is negative */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_setconcurrency)(int level);
/* >> pthread_setaffinity_np(3)
 * Limit specified thread `self' to run only on the processors represented in `cpuset'
 * @return: EOK:   Success
 * @return: ESRCH: `self' has already exited */
INTDEF ATTR_IN_OPT(3) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_setaffinity_np)(pthread_t self, size_t cpusetsize, cpu_set_t const *cpuset);
/* >> pthread_getaffinity_np(3)
 * Get bit set in `cpuset' representing the processors `self' can run on
 * @return: EOK:   Success
 * @return: ESRCH: `self' has already exited */
INTDEF ATTR_OUT_OPT(3) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_getaffinity_np)(pthread_t self, size_t cpusetsize, cpu_set_t *cpuset);
/* >> pthread_once(3)
 * Guarantee that the initialization function `init_routine' will be called
 * only  once,  even if  pthread_once is  executed  several times  with the
 * same `once_control' argument. `once_control' must  point to a static  or
 * extern variable initialized to `PTHREAD_ONCE_INIT'.
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) NONNULL((2)) errno_t NOTHROW_CB(LIBDCALL libd_pthread_once)(pthread_once_t *once_control, void (LIBDCALL *init_routine)(void));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> pthread_once(3)
 * Guarantee that the initialization function `init_routine' will be called
 * only  once,  even if  pthread_once is  executed  several times  with the
 * same `once_control' argument. `once_control' must  point to a static  or
 * extern variable initialized to `PTHREAD_ONCE_INIT'.
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) NONNULL((2)) errno_t NOTHROW_CB(LIBCCALL libc_pthread_once)(pthread_once_t *once_control, void (LIBCCALL *init_routine)(void));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> pthread_setcancelstate(3)
 * Set  cancelability  state   of  current   thread  to   `state',
 * returning old state in `*oldstate' if `oldstate' is not `NULL'.
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `state' */
INTDEF ATTR_OUT_OPT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_setcancelstate)(int state, int *oldstate);
/* >> pthread_setcanceltype(3)
 * Set cancellation state of current thread to `type',
 * returning the old type in `*oldtype' if `oldtype' is not `NULL'.
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `type' */
INTDEF ATTR_OUT_OPT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_setcanceltype)(int type, int *oldtype);
/* >> pthread_cancel(3)
 * Cancel `self' immediately or at the next possibility
 * @return: EOK:   Success
 * @return: ESRCH: `self' has already exited */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_cancel)(pthread_t self);
/* Function called to call the cleanup handler. As an extern inline
 * function the compiler is free to decide inlining the change when
 * needed or fall back on the copy which must exist somewhere else */
INTDEF ATTR_INOUT(1) void NOTHROW_NCX(LIBDCALL libd___pthread_cleanup_routine)(struct __pthread_cleanup_frame *frame);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Function called to call the cleanup handler. As an extern inline
 * function the compiler is free to decide inlining the change when
 * needed or fall back on the copy which must exist somewhere else */
INTDEF ATTR_INOUT(1) void NOTHROW_NCX(LIBCCALL libc___pthread_cleanup_routine)(struct __pthread_cleanup_frame *frame);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF __cleanup_fct_attribute void NOTHROW_NCX(LIBDCALL libd___pthread_register_cancel)(__pthread_unwind_buf_t *buf);
INTDEF __cleanup_fct_attribute ATTR_INOUT(1) void NOTHROW_NCX(LIBDCALL libd___pthread_unregister_cancel)(__pthread_unwind_buf_t *buf);
INTDEF __cleanup_fct_attribute ATTR_INOUT(1) void NOTHROW_NCX(LIBDCALL libd___pthread_register_cancel_defer)(__pthread_unwind_buf_t *buf);
INTDEF __cleanup_fct_attribute ATTR_INOUT(1) void NOTHROW_NCX(LIBDCALL libd___pthread_unregister_cancel_restore)(__pthread_unwind_buf_t *buf);
/* Internal interface to initiate cleanup */
INTDEF ATTR_WEAK __cleanup_fct_attribute ATTR_INOUT(1) void NOTHROW_NCX(LIBDCALL libd___pthread_unwind_next)(__pthread_unwind_buf_t *buf);
/* >> pthread_mutex_init(3)
 * Initialize the given mutex `self'
 * @return: EOK: Success */
INTDEF ATTR_OUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutex_init)(pthread_mutex_t *self, pthread_mutexattr_t const *mutexattr);
/* >> pthread_mutex_destroy(3)
 * Destroy the given mutex `self'
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutex_destroy)(pthread_mutex_t *self);
/* >> pthread_mutex_trylock(3)
 * Try locking the given mutex `self'
 * @return: EOK:   Success
 * @return: EBUSY: The  mutex  has  already  been   locked
 *                 In case of  a recursive mutex,  another
 *                 thread was the one to acquire the lock. */
INTDEF WUNUSED ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutex_trylock)(pthread_mutex_t *self);
/* >> pthread_mutex_lock(3)
 * Lock the given mutex `self'
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_mutex_lock)(pthread_mutex_t *self);
/* >> pthread_mutex_timedlock(3), pthread_mutex_timedlock64(3)
 * Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_mutex_timedlock)(pthread_mutex_t *__restrict self, struct timespec const *__restrict abstime);
/* >> pthread_mutex_timedlock(3), pthread_mutex_timedlock64(3)
 * Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_mutex_timedlock64)(pthread_mutex_t *__restrict self, struct timespec64 const *__restrict abstime);
/* >> pthread_mutex_reltimedlock_np(3), pthread_mutex_reltimedlock64_np(3)
 * Wait until lock becomes available, or specified amount of time has passed
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired */
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_mutex_reltimedlock_np)(pthread_mutex_t *__restrict self, struct timespec const *__restrict reltime);
/* >> pthread_mutex_reltimedlock_np(3), pthread_mutex_reltimedlock64_np(3)
 * Wait until lock becomes available, or specified amount of time has passed
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired */
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_mutex_reltimedlock64_np)(pthread_mutex_t *__restrict self, struct timespec64 const *__restrict reltime);
/* >> pthread_mutex_unlock(3)
 * Unlock the given mutex `self'
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutex_unlock)(pthread_mutex_t *self);
/* >> pthread_mutex_getprioceiling(3)
 * Get the priority ceiling of `self'
 * @return: EOK: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutex_getprioceiling)(pthread_mutex_t const *__restrict self, int *__restrict prioceiling);
/* >> pthread_mutex_setprioceiling(3)
 * Set the priority ceiling of `self' to `prioceiling',
 * return  old priority ceiling value in `*old_ceiling'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `prioceiling' */
INTDEF ATTR_INOUT(1) ATTR_OUT_OPT(3) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutex_setprioceiling)(pthread_mutex_t *__restrict self, int prioceiling, int *__restrict old_ceiling);
/* >> pthread_mutex_consistent(3)
 * Declare the state protected by `self' as consistent
 * @return: EOK:    Success
 * @return: EINVAL: Not a robust mutex
 * @return: EINVAL: Mutex was already in a consistent state */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutex_consistent)(pthread_mutex_t *self);
/* >> pthread_mutexattr_init(3)
 * Initialize mutex attribute object `self' with default
 * attributes    (kind    is   `PTHREAD_MUTEX_TIMED_NP')
 * @return: EOK: Success */
INTDEF ATTR_OUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_init)(pthread_mutexattr_t *self);
/* >> pthread_mutexattr_destroy(3)
 * Destroy mutex attribute object `self'
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_destroy)(pthread_mutexattr_t *self);
/* >> pthread_mutexattr_getpshared(3)
 * Get the process-shared flag of the mutex attribute `self'
 * @return: EOK: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_getpshared)(pthread_mutexattr_t const *__restrict self, int *__restrict pshared);
/* >> pthread_mutexattr_setpshared(3)
 * Set the process-shared flag of the mutex attribute `self'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_setpshared)(pthread_mutexattr_t *self, int pshared);
/* >> pthread_mutexattr_gettype(3)
 * Return in `*kind' the mutex kind attribute in `*self'
 * @return: EOK: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_gettype)(pthread_mutexattr_t const *__restrict self, int *__restrict kind);
/* >> pthread_mutexattr_settype(3)
 * Set  the mutex kind attribute in `*self' to `kind' (either `PTHREAD_MUTEX_NORMAL',
 * `PTHREAD_MUTEX_RECURSIVE', `PTHREAD_MUTEX_ERRORCHECK', or `PTHREAD_MUTEX_DEFAULT')
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `kind' */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_settype)(pthread_mutexattr_t *self, int kind);
/* >> pthread_mutexattr_getprotocol(3)
 * Return in `*protocol' the mutex protocol attribute in `*self'
 * @return: EOK: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_getprotocol)(pthread_mutexattr_t const *__restrict self, int *__restrict protocol);
/* >> pthread_mutexattr_setprotocol(3)
 * Set  the  mutex protocol  attribute  in `*self'  to  `protocol' (either
 * `PTHREAD_PRIO_NONE', `PTHREAD_PRIO_INHERIT', or `PTHREAD_PRIO_PROTECT')
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `protocol' */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_setprotocol)(pthread_mutexattr_t *self, int protocol);
/* >> pthread_mutexattr_getprioceiling(3)
 * Return in `*prioceiling' the mutex prioceiling attribute in `*self'
 * @return: EOK: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_getprioceiling)(pthread_mutexattr_t const *__restrict self, int *__restrict prioceiling);
/* >> pthread_mutexattr_setprioceiling(3)
 * Set the mutex prioceiling attribute in `*self' to `prioceiling'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `prioceiling' */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_setprioceiling)(pthread_mutexattr_t *self, int prioceiling);
/* >> pthread_mutexattr_getrobust(3)
 * Get the robustness flag of the mutex attribute `self'
 * @return: EOK: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_getrobust)(pthread_mutexattr_t const *__restrict self, int *__restrict robustness);
/* >> pthread_mutexattr_setrobust(3)
 * Set the robustness flag of the mutex attribute `self'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `robustness' */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_setrobust)(pthread_mutexattr_t *self, int robustness);
/* >> pthread_rwlock_init(3)
 * Initialize read-write lock `self' using attributes `attr',
 * or  use   the  default   values   if  later   is   `NULL'.
 * @return: EOK: Success */
INTDEF ATTR_IN_OPT(2) ATTR_OUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_rwlock_init)(pthread_rwlock_t *__restrict self, pthread_rwlockattr_t const *__restrict attr);
/* >> pthread_rwlock_destroy(3)
 * Destroy read-write lock `self'
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_rwlock_destroy)(pthread_rwlock_t *self);
/* >> pthread_rwlock_rdlock(3)
 * Acquire read lock for `self'
 * @return: EOK:     Success
 * @return: EAGAIN:  The maximum # of read-locks has been acquired
 * @return: EDEADLK: You're already holding a write-lock
 * @return: EDEADLK: [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                   You're already holding a read-lock */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_rwlock_rdlock)(pthread_rwlock_t *self);
/* >> pthread_rwlock_tryrdlock(3)
 * Try to acquire read lock for `self'
 * @return: EOK:    Success
 * @return: EBUSY:  A read-lock cannot be acquired at the moment,
 *                  because a write-lock  is already being  held.
 * @return: EAGAIN: The maximum # of read-locks has been acquired */
INTDEF WUNUSED ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_rwlock_tryrdlock)(pthread_rwlock_t *self);
/* >> pthread_rwlock_wrlock(3)
 * Acquire write lock for `self'
 * @return: EOK:     Success
 * @return: EDEADLK: You're already holding a read-lock
 * @return: EDEADLK: [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                   You're already holding a write-lock */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_rwlock_wrlock)(pthread_rwlock_t *self);
/* >> pthread_rwlock_trywrlock(3)
 * Try to acquire write lock for `self'
 * @return: EOK:   Success
 * @return: EBUSY: A write-lock cannot be acquired at the moment,
 *                 because read-locks  are  already  being  held. */
INTDEF WUNUSED ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_rwlock_trywrlock)(pthread_rwlock_t *self);
/* >> pthread_rwlock_timedrdlock(3), pthread_rwlock_timedrdlock64(3)
 * Try to acquire read lock for `self' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EAGAIN:    The maximum # of read-locks has been acquired
 * @return: EDEADLK:   You're already holding a write-lock
 * @return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a read-lock */
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_rwlock_timedrdlock)(pthread_rwlock_t *__restrict self, struct timespec const *__restrict abstime);
/* >> pthread_rwlock_timedwrlock(3), pthread_rwlock_timedwrlock64(3)
 * Try to acquire write lock for `self' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EDEADLK:   You're already holding a read-lock
 * @return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a write-lock */
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_rwlock_timedwrlock)(pthread_rwlock_t *__restrict self, struct timespec const *__restrict abstime);
/* >> pthread_rwlock_timedrdlock(3), pthread_rwlock_timedrdlock64(3)
 * Try to acquire read lock for `self' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EAGAIN:    The maximum # of read-locks has been acquired
 * @return: EDEADLK:   You're already holding a write-lock
 * @return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a read-lock */
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_rwlock_timedrdlock64)(pthread_rwlock_t *__restrict self, struct timespec64 const *__restrict abstime);
/* >> pthread_rwlock_timedwrlock(3), pthread_rwlock_timedwrlock64(3)
 * Try to acquire write lock for `self' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EDEADLK:   You're already holding a read-lock
 * @return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a write-lock */
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_rwlock_timedwrlock64)(pthread_rwlock_t *__restrict self, struct timespec64 const *__restrict abstime);
/* >> pthread_rwlock_reltimedrdlock_np(3), pthread_rwlock_reltimedrdlock64_np(3)
 * Try to  acquire read  lock for  `self'  or return  after the  specified  time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired
 * @return: EAGAIN:    The maximum # of read-locks has been acquired
 * @return: EDEADLK:   You're already holding a write-lock
 * @return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a read-lock */
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_rwlock_reltimedrdlock_np)(pthread_rwlock_t *__restrict self, struct timespec const *__restrict reltime);
/* >> pthread_rwlock_reltimedwrlock_np(3), pthread_rwlock_reltimedwrlock64_np(3)
 * Try to  acquire write  lock for  `self' or  return after  the specified  time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired
 * @return: EDEADLK:   You're already holding a read-lock
 * @return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a write-lock */
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_rwlock_reltimedwrlock_np)(pthread_rwlock_t *__restrict self, struct timespec const *__restrict reltime);
/* >> pthread_rwlock_reltimedrdlock_np(3), pthread_rwlock_reltimedrdlock64_np(3)
 * Try to  acquire read  lock for  `self'  or return  after the  specified  time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired
 * @return: EAGAIN:    The maximum # of read-locks has been acquired
 * @return: EDEADLK:   You're already holding a write-lock
 * @return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a read-lock */
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_rwlock_reltimedrdlock64_np)(pthread_rwlock_t *__restrict self, struct timespec64 const *__restrict reltime);
/* >> pthread_rwlock_reltimedwrlock_np(3), pthread_rwlock_reltimedwrlock64_np(3)
 * Try to  acquire write  lock for  `self' or  return after  the specified  time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired
 * @return: EDEADLK:   You're already holding a read-lock
 * @return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a write-lock */
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_rwlock_reltimedwrlock64_np)(pthread_rwlock_t *__restrict self, struct timespec64 const *__restrict reltime);
/* >> pthread_rwlock_unlock(3)
 * Unlock `self'
 * @return: EOK:   Success
 * @return: EPERM: You're not holding a read- or write-lock */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_rwlock_unlock)(pthread_rwlock_t *self);
/* >> pthread_rwlockattr_init(3)
 * Initialize attribute object `self' with default values
 * @return: EOK: Success */
INTDEF ATTR_OUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_rwlockattr_init)(pthread_rwlockattr_t *self);
/* >> pthread_rwlockattr_destroy(3)
 * Destroy attribute object  `self'
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_rwlockattr_destroy)(pthread_rwlockattr_t *self);
/* >> pthread_rwlockattr_getpshared(3)
 * Return current setting of process-shared attribute of `self' in `*pshared'
 * @return: EOK: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_rwlockattr_getpshared)(pthread_rwlockattr_t const *__restrict self, int *__restrict pshared);
/* >> pthread_rwlockattr_setpshared(3)
 * Set process-shared attribute of `self' to `pshared'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_rwlockattr_setpshared)(pthread_rwlockattr_t *self, int pshared);
/* >> pthread_rwlockattr_getkind_np(3)
 * Return current setting of reader/writer preference
 * @return: EOK: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_rwlockattr_getkind_np)(pthread_rwlockattr_t const *__restrict self, int *__restrict pref);
/* >> pthread_rwlockattr_setkind_np(3)
 * Set     reader/write     preference
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pref' */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_rwlockattr_setkind_np)(pthread_rwlockattr_t *self, int pref);
/* >> pthread_cond_init(3)
 * Initialize condition variable `self' using attributes
 * `attr', or use the default values if later is `NULL'.
 * @return: EOK: Success */
INTDEF ATTR_IN_OPT(2) ATTR_OUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_cond_init)(pthread_cond_t *__restrict self, pthread_condattr_t const *__restrict cond_attr);
/* >> pthread_cond_destroy(3)
 * Destroy condition variable `self'
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_cond_destroy)(pthread_cond_t *self);
/* >> pthread_cond_signal(3)
 * Wake up one thread waiting for condition variable `self'
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_cond_signal)(pthread_cond_t *self);
/* >> pthread_cond_broadcast(3)
 * Wake up all threads waiting for condition variables `self'
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_cond_broadcast)(pthread_cond_t *self);
/* >> pthread_cond_wait(3)
 * Wait for condition variable `self' to be signaled or broadcast.
 * `mutex' is assumed to be locked before.
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) ATTR_INOUT(2) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_cond_wait)(pthread_cond_t *__restrict self, pthread_mutex_t *__restrict mutex);
/* >> pthread_cond_timedwait(3), pthread_cond_timedwait64(3)
 * Wait for condition variable `self' to be signaled or broadcast
 * until `abstime'.  `mutex'  is  assumed to  be  locked  before.
 * `abstime' is  an  absolute  time specification;  zero  is  the
 * beginning of the epoch (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF WUNUSED ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_cond_timedwait)(pthread_cond_t *__restrict self, pthread_mutex_t *__restrict mutex, struct timespec const *__restrict abstime);
/* >> pthread_cond_timedwait(3), pthread_cond_timedwait64(3)
 * Wait for condition variable `self' to be signaled or broadcast
 * until `abstime'.  `mutex'  is  assumed to  be  locked  before.
 * `abstime' is  an  absolute  time specification;  zero  is  the
 * beginning of the epoch (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTDEF WUNUSED ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_cond_timedwait64)(pthread_cond_t *__restrict self, pthread_mutex_t *__restrict mutex, struct timespec64 const *__restrict abstime);
/* >> pthread_cond_reltimedwait_np(3), pthread_cond_reltimedwait64_np(3)
 * Wait for  condition  variable  `self' to  be  signaled  or  broadcast
 * until `reltime'. `mutex' is assumed to be locked before.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired */
INTDEF WUNUSED ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_cond_reltimedwait_np)(pthread_cond_t *__restrict self, pthread_mutex_t *__restrict mutex, struct timespec const *__restrict reltime);
/* >> pthread_cond_reltimedwait_np(3), pthread_cond_reltimedwait64_np(3)
 * Wait for  condition  variable  `self' to  be  signaled  or  broadcast
 * until `reltime'. `mutex' is assumed to be locked before.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired */
INTDEF WUNUSED ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_cond_reltimedwait64_np)(pthread_cond_t *__restrict self, pthread_mutex_t *__restrict mutex, struct timespec64 const *__restrict reltime);
/* >> pthread_condattr_init(3)
 * Initialize condition variable attribute `self'
 * @return: EOK: Success */
INTDEF ATTR_OUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_condattr_init)(pthread_condattr_t *self);
/* >> pthread_condattr_destroy(3)
 * Destroy condition variable attribute `self'
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_condattr_destroy)(pthread_condattr_t *self);
/* >> pthread_condattr_getpshared(3)
 * Get the process-shared flag of the condition variable attribute `self'
 * @return: EOK: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_condattr_getpshared)(pthread_condattr_t const *__restrict self, int *__restrict pshared);
/* >> pthread_condattr_setpshared(3)
 * Set the process-shared flag of the condition variable attribute `self'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_condattr_setpshared)(pthread_condattr_t *self, int pshared);
/* >> pthread_condattr_getclock(3)
 * Get the clock selected for the condition variable attribute `self'
 * @return: EOK: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_condattr_getclock)(pthread_condattr_t const *__restrict self, clockid_t *__restrict clock_id);
/* >> pthread_condattr_setclock(3)
 * Set the clock selected for the condition variable attribute `self'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `clock_id' */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_condattr_setclock)(pthread_condattr_t *self, clockid_t clock_id);
/* >> pthread_spin_init(3)
 * Initialize the spinlock `self'. If `pshared' is nonzero
 * the  spinlock can be shared between different processes
 * @return: EOK: Success */
INTDEF ATTR_OUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_spin_init)(pthread_spinlock_t *self, int pshared);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> pthread_spin_init(3)
 * Initialize the spinlock `self'. If `pshared' is nonzero
 * the  spinlock can be shared between different processes
 * @return: EOK: Success */
INTDEF ATTR_OUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_spin_init)(pthread_spinlock_t *self, int pshared);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> pthread_spin_destroy(3)
 * Destroy the spinlock `self'
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_spin_destroy)(pthread_spinlock_t *self);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> pthread_spin_destroy(3)
 * Destroy the spinlock `self'
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_spin_destroy)(pthread_spinlock_t *self);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> pthread_spin_lock(3)
 * Wait until spinlock `self' is retrieved
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_spin_lock)(pthread_spinlock_t *self);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> pthread_spin_lock(3)
 * Wait until spinlock `self' is retrieved
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_spin_lock)(pthread_spinlock_t *self);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> pthread_spin_trylock(3)
 * Try to lock spinlock `self'
 * @return: EOK:   Success
 * @return: EBUSY: Lock has already been acquired */
INTDEF WUNUSED ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_spin_trylock)(pthread_spinlock_t *self);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> pthread_spin_trylock(3)
 * Try to lock spinlock `self'
 * @return: EOK:   Success
 * @return: EBUSY: Lock has already been acquired */
INTDEF WUNUSED ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_spin_trylock)(pthread_spinlock_t *self);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> pthread_spin_unlock(3)
 * Release  spinlock  `self'
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_spin_unlock)(pthread_spinlock_t *self);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> pthread_spin_unlock(3)
 * Release  spinlock  `self'
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_spin_unlock)(pthread_spinlock_t *self);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> pthread_barrier_init(3)
 * Initialize `self' with  the attributes in  `attr'.
 * The barrier is opened when `count' waiters arrived
 * @return: EOK:    Success
 * @return: EINVAL: The given `count' is ZERO(0) */
INTDEF ATTR_IN_OPT(2) ATTR_OUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_barrier_init)(pthread_barrier_t *__restrict self, pthread_barrierattr_t const *__restrict attr, unsigned int count);
/* >> pthread_barrier_destroy(3)
 * Destroy the given (previously dynamically initialized) `self'
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_barrier_destroy)(pthread_barrier_t *self);
/* >> pthread_barrier_wait(3)
 * Wait on  the given  `self'
 * @return: 0 :                            Success
 * @return: PTHREAD_BARRIER_SERIAL_THREAD: Success, and you were picked to be the "serialization" thread. */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_RPC(LIBDCALL libd_pthread_barrier_wait)(pthread_barrier_t *self);
/* >> pthread_barrierattr_init(3)
 * Initialize barrier attribute `self'
 * @return: EOK: Success */
INTDEF ATTR_OUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_barrierattr_init)(pthread_barrierattr_t *self);
/* >> pthread_barrierattr_destroy(3)
 * Destroy previously dynamically initialized barrier attribute `self'
 * @return: EOK: Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_barrierattr_destroy)(pthread_barrierattr_t *self);
/* >> pthread_barrierattr_getpshared(3)
 * Get the process-shared flag of the barrier attribute `self'
 * @return: EOK: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_barrierattr_getpshared)(pthread_barrierattr_t const *__restrict self, int *__restrict pshared);
/* >> pthread_barrierattr_setpshared(3)
 * Set the process-shared flag of the barrier attribute `self'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_barrierattr_setpshared)(pthread_barrierattr_t *self, int pshared);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> pthread_key_create_once_np(3)
 * Same as `pthread_key_create()', but the  given `key' must be  pre-initialized
 * using the static initializer `PTHREAD_ONCE_KEY_NP', whilst this function will
 * make  sure that  even in the  event of multiple  simultaneous threads calling
 * this function, only one will create the  key, and all others will wait  until
 * the key has been  created. Once the  key was created,  further calls to  this
 * function will no longer block, but simply return immediately.
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to create the key */
INTDEF ATTR_OUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_key_create_once_np)(pthread_key_t *key, void (LIBKCALL *destr_function)(void *));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> pthread_key_delete(3)
 * Destroy the given  `key'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid `key' */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_key_delete)(pthread_key_t key);
/* >> pthread_getspecific(3)
 * Return current value of the thread-specific data slot identified by `key'
 * @return: * :   The value currently associated with `key' in the calling thread
 * @return: NULL: The current value is `NULL'
 * @return: NULL: No value has been bound, yet
 * @return: NULL: Invalid `key' */
INTDEF WUNUSED void *NOTHROW_NCX(LIBDCALL libd_pthread_getspecific)(pthread_key_t key);
/* >> pthread_setspecific(3)
 * Store POINTER in the thread-specific data slot identified by `key'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid `key'
 * @return: ENOMEM: `pointer' is non-`NULL', `key' had yet to be allocated for the
 *                  calling  thread, and an attempt to allocate it just now failed */
INTDEF ATTR_ACCESS_NONE(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_setspecific)(pthread_key_t key, void const *pointer);
/* >> pthread_getspecificptr_np(3)
 * Return a pointer to the per-thread storage location associated with `key'
 * @return: * :   The address read/written by `pthread_getspecific()' / `pthread_setspecific()'
 * @return: NULL: `key' had yet to be allocated for the calling thread,
 *                and an  attempt  to  allocate  it  just  now  failed.
 * @return: NULL: Invalid `key'. */
INTDEF ATTR_PURE WUNUSED void **NOTHROW_NCX(LIBDCALL libd_pthread_getspecificptr_np)(pthread_key_t key);
/* >> pthread_getcpuclockid(3)
 * Get the ID of CPU-time clock for thread `self'
 * @return: EOK: Success */
INTDEF ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_getcpuclockid)(pthread_t self, clockid_t *clock_id);
/* >> pthread_atfork(3)
 * Install handlers to be called when a new process is created with  `fork(2)'.
 * The `prepare' handler is called in the parent process just before performing
 * `fork(2)'. The `parent' handler is called  in the parent process just  after
 * `fork(2)'.  The `child' handler is called in  the child process. Each of the
 * three  handlers can be `NULL', meaning that no handler needs to be called at
 * that point.
 * `pthread_atfork(3)' can be called several times, in which case the `prepare'
 * handlers are  called in  LIFO order  (last added  with  `pthread_atfork(3)',
 * first  called before `fork(2)'),  and the `parent'  and `child' handlers are
 * called in FIFO order (first added -> first called)
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to register callbacks */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_atfork)(void (LIBDCALL *prepare)(void), void (LIBDCALL *parent)(void), void (LIBDCALL *child)(void));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> pthread_num_processors_np(3)
 * @return: * : The number of cpus that the calling thread is able to run on */
INTDEF WUNUSED __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_pthread_num_processors_np)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> pthread_set_num_processors_np(3)
 * Restrict the calling thread to only run on the first `n' cpus
 * @return: EOK:    Success
 * @return: EINVAL: `n' was specified as less than `1'
 * @return: * :     Same as `errno' after a call to `sched_setaffinity(2)' */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_set_num_processors_np)(int n);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> pthread_set_num_processors_np(3)
 * Restrict the calling thread to only run on the first `n' cpus
 * @return: EOK:    Success
 * @return: EINVAL: `n' was specified as less than `1'
 * @return: * :     Same as `errno' after a call to `sched_setaffinity(2)' */
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_pthread_set_num_processors_np)(int n);
/* >> pthread_main_np(3)
 * Returns  1 if the  calling thread is the  main() thread (i.e. the
 * thread  that was  started by the  kernel in order  to execute the
 * calling program), and 0  otherwise. Additionally, -1 is  returned
 * if the  calling  thread  "hasn't been initialized",  though  this
 * isn't a case that can actually happen under KOS's implementation. */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_pthread_main_np)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> pthread_attr_setstartsuspended_np(3)
 * Specify if `pthread_create(3)' should start the thread in a suspended state.
 * @param: start_suspended: 0=no (default) or 1=yes
 * @see pthread_resume_np, pthread_continue_np
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `start_suspended' */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setstartsuspended_np)(pthread_attr_t *__restrict self, int start_suspended);
/* >> pthread_attr_getpidfdallocated_np(3)
 * Write 0=no or 1=yes to `*start_suspended', indicative of `pthread_create(3)'
 * starting  newly spawned thread  in a suspended  state (requiring the creator
 * to resume the thread at least once before execution actually starts)
 * @return: EOK: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_getstartsuspended_np)(pthread_attr_t const *__restrict self, int *start_suspended);
/* >> pthread_suspend2_np(3)
 * Increment the given thread's suspend-counter. If the counter was `0' before,
 * then the thread is suspended and this function only returns once the  thread
 * has stopped executing code. The counter's old value is optionally stored  in
 * `p_old_suspend_counter' (when non-NULL)
 *
 * Signals directed at suspended thread will not be handled until that thread has
 * been resumed (s.a. `pthread_resume2_np(3)')
 *
 * @see pthread_suspend_np, pthread_resume2_np, pthread_resume_np, pthread_continue_np
 * @return: EOK:       Success
 * @return: ESRCH:     The thread has already been terminated
 * @return: ENOMEM:    Insufficient memory
 * @return: EOVERFLOW: The suspension counter can't go any higher */
INTDEF ATTR_OUT_OPT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_suspend2_np)(pthread_t self, uint32_t *p_old_suspend_counter);
/* >> pthread_resume2_np(3)
 * Decrement the given thread's suspend-counter. If the counter was already `0',
 * then  the calls is a no-op (and `EOK').  If the counter was `1', execution of
 * the thread is allowed to  continue (or start for the  first time in case  the
 * thread was created with `pthread_attr_setstartsuspended_np(3)' set to 1). The
 * counter's old  value is  optionally stored  in `p_old_suspend_counter'  (when
 * non-NULL).
 *
 * @see pthread_suspend_np, pthread_suspend2_np, pthread_resume_np, pthread_continue_np
 * @return: EOK:   Success
 * @return: ESRCH: The thread has already been terminated */
INTDEF ATTR_OUT_OPT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_resume2_np)(pthread_t self, uint32_t *p_old_suspend_counter);
/* >> pthread_attach_np(3)
 * Attach  to `self' for a second time. After a call to this function, `pthread_detach(3)'
 * must be called one extra time before the thread descriptor `self' is actually destroyed */
INTDEF void NOTHROW_NCX(LIBDCALL libd_pthread_attach_np)(pthread_t self);
/* >> pthread_enumthreads_np(3)
 * Enumerate all threads created by `pthread_create(3)' by invoking `cb' once for each of them.
 * Only threads whose descriptors have yet to be destroyed are enumerated, and care is taken to
 * ensure that the `thrd' passed  to `cb' cannot be destroyed  while inside of `cb'. Also  note
 * that `cb' is allowed to call `pthread_attach_np(3)' to re-attach previously detached  thread
 * descriptors (assuming that those descriptors haven't been destroyed, yet)
 * @return: * :     A call to `cb' returned a value other than `EOK', and enumeration was halted
 * @return: EOK:    All threads were enumerated by being passed to `cb'
 * @return: ENOMEM: Insufficient memory to allocate a required, internal buffer */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_enumthreads_np)(errno_t (__LIBKCALL *cb)(void *cookie, pthread_t thrd), void *cookie);
/* >> pthread_attachtid_np(3)
 * Return a descriptor for a (potentially, previously detached) thread `tid'.
 * This function cannot be used to attach threads created by means other than
 * via `pthread_create(3)', and also won't work  for threads not part of  the
 * calling process.
 * Semantically, this function is equivalent to calling `pthread_enumthreads_np(3)'
 * in  other  to  find the  correct  thread, then  using  `pthread_attach_np(3)' to
 * (re-)attach a reference to its descriptor.
 *
 * @return: EOK:    Success. In this case, the caller must use `pthread_detach(3)'
 *                  in  order  to   release  the  new   reference  to   `*result'.
 * @return: EINVAL: Invalid `tid' (is `0' or negative)
 * @return: ESRCH:  Descriptor for thread with `tid' has already been destroyed,
 *                  or didn't exist  (within the calling  process) in the  first
 *                  place. */
INTDEF ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attachtid_np)(pid_t tid, pthread_t *__restrict result);
/* >> pthread_attachpidfd_np(3)
 * Similar to `pthread_attachtid_np(3)', but search for a thread that has an
 * allocated PIDfd descriptor (as returned by `pthread_getpidfd_np(3)'), and
 * (re-)attach that thread's descriptor.  Only the original file  descriptor
 * returned by `pthread_getpidfd_np(3)' is  understood by this function.  If
 * you `dup(2)' that descriptor and try to pass the duplicate, this function
 * will be unable to locate your descriptor.
 *
 * @return: EOK:    Success. In this case, the caller must use `pthread_detach(3)'
 *                  in  order  to   release  the  new   reference  to   `*result'.
 * @return: EINVAL: Invalid `pidfd' (is negative)
 * @return: ESRCH:  Descriptor for thread with `pidfd' has already been  destroyed,
 *                  or  didn't  exist (within  the  calling process)  in  the first
 *                  place, or the given `pidfd' is not what was originally returned
 *                  by  `pthread_getpidfd_np(3)'  (but is  the result  of `dup(2)') */
INTDEF ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attachpidfd_np)(fd_t pidfd, pthread_t *__restrict result);
/* >> pthread_continue_np(3), pthread_unsuspend_np(3)
 * Set the given thread's suspend-counter to `0'. If the counter was already `0',
 * then the calls is a no-op (and  `EOK'). Otherwise, execution of the thread  is
 * allowed  to  continue (or  start for  the first  time in  case the  thread was
 * created with `pthread_attr_setstartsuspended_np(3)' set to 1).
 *
 * @see pthread_suspend_np, pthread_suspend2_np, pthread_resume2_np, pthread_resume_np
 * @return: EOK:   Success
 * @return: ESRCH: The thread has already been terminated */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_continue_np)(pthread_t self);
/* >> pthread_attr_setcreatesuspend_np(3)
 * Setup `self' such that created threads start in a "suspended" state,
 * requiring a call to one of the following function to actually start:
 *  - `pthread_continue_np(3)' (or `pthread_unsuspend_np(3)')
 *  - `pthread_resume_np(3)'
 *  - `pthread_resume_all_np(3)'
 * Alias for `pthread_attr_setstartsuspended_np(self, 1)'
 * @return: EOK: Always returned */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_attr_setcreatesuspend_np)(pthread_attr_t *__restrict self);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> pthread_attr_setcreatesuspend_np(3)
 * Setup `self' such that created threads start in a "suspended" state,
 * requiring a call to one of the following function to actually start:
 *  - `pthread_continue_np(3)' (or `pthread_unsuspend_np(3)')
 *  - `pthread_resume_np(3)'
 *  - `pthread_resume_all_np(3)'
 * Alias for `pthread_attr_setstartsuspended_np(self, 1)'
 * @return: EOK: Always returned */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_attr_setcreatesuspend_np)(pthread_attr_t *__restrict self);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> pthread_suspend_np(3)
 * Increment the given thread's suspend-counter. If the counter was `0' before,
 * then the thread is suspended and this function only returns once the  thread
 * has stopped executing code.
 *
 * Signals directed at suspended thread will not be handled until that thread has
 * been  resumed  (s.a.  `pthread_resume_np(3)'  and   `pthread_unsuspend_np(3)')
 *
 * @see pthread_suspend2_np
 * @return: EOK:       Success
 * @return: ESRCH:     The thread has already been terminated
 * @return: ENOMEM:    Insufficient memory
 * @return: EOVERFLOW: The suspension counter can't go any higher */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_suspend_np)(pthread_t self);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> pthread_suspend_np(3)
 * Increment the given thread's suspend-counter. If the counter was `0' before,
 * then the thread is suspended and this function only returns once the  thread
 * has stopped executing code.
 *
 * Signals directed at suspended thread will not be handled until that thread has
 * been  resumed  (s.a.  `pthread_resume_np(3)'  and   `pthread_unsuspend_np(3)')
 *
 * @see pthread_suspend2_np
 * @return: EOK:       Success
 * @return: ESRCH:     The thread has already been terminated
 * @return: ENOMEM:    Insufficient memory
 * @return: EOVERFLOW: The suspension counter can't go any higher */
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_pthread_suspend_np)(pthread_t self);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> pthread_suspend_np(3)
 * Decrement the given thread's suspend-counter. If the counter was already `0',
 * then  the calls is a no-op (and `EOK').  If the counter was `1', execution of
 * the thread is allowed to  continue (or start for the  first time in case  the
 * thread was created with `pthread_attr_setstartsuspended_np(3)' set to 1).
 *
 * @see pthread_suspend_np, pthread_suspend2_np, pthread_resume2_np, pthread_continue_np
 * @return: EOK:   Success
 * @return: ESRCH: The thread has already been terminated */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_resume_np)(pthread_t self);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> pthread_suspend_np(3)
 * Decrement the given thread's suspend-counter. If the counter was already `0',
 * then  the calls is a no-op (and `EOK').  If the counter was `1', execution of
 * the thread is allowed to  continue (or start for the  first time in case  the
 * thread was created with `pthread_attr_setstartsuspended_np(3)' set to 1).
 *
 * @see pthread_suspend_np, pthread_suspend2_np, pthread_resume2_np, pthread_continue_np
 * @return: EOK:   Success
 * @return: ESRCH: The thread has already been terminated */
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_pthread_resume_np)(pthread_t self);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> pthread_getunique_np(3)
 * Wrapper around `pthread_gettid_np(3)' that is also available on some other platforms. */
INTDEF ATTR_PURE WUNUSED errno_t NOTHROW_NCX(LIBDCALL libd_pthread_getunique_np)(pthread_t self, pthread_id_np_t *ptid);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> pthread_getunique_np(3)
 * Wrapper around `pthread_gettid_np(3)' that is also available on some other platforms. */
INTDEF ATTR_PURE WUNUSED errno_t NOTHROW_NCX(LIBCCALL libc_pthread_getunique_np)(pthread_t self, pthread_id_np_t *ptid);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> pthread_mutex_isowned_np(3)
 * Check if the calling thread is holding a lock to `mutex' (for use by assertions)
 * @return: 1 : Yes, you are holding a lock to `mutex'
 * @return: 0 : Either `mutex' isn't locked, or it isn't you that's holding the lock */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd_pthread_mutex_isowned_np)(pthread_mutex_t __KOS_FIXED_CONST *mutex);
INTDEF WUNUSED NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_switch_add_np)(pthread_switch_routine_t routine);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_switch_add_np)(pthread_switch_routine_t routine);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_pthread_switch_delete_np)(pthread_switch_routine_t routine);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_pthread_switch_delete_np)(pthread_switch_routine_t routine);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_PTHREAD_H */
