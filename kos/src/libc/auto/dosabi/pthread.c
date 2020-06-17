/* HASH CRC-32:0xc1aacb64 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_PTHREAD_C
#define GUARD_LIBC_AUTO_DOSABI_PTHREAD_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/pthread.h"

DECL_BEGIN

/* Create a new thread, starting with execution of START-ROUTINE
 * getting passed ARG. Creation attributed come from ATTR. The new
 * handle is stored in *NEWTHREAD */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 3)) int
NOTHROW_NCX(LIBDCALL libd_pthread_create)(pthread_t *__restrict newthread,
                                          pthread_attr_t const *__restrict attr,
                                          __pthread_start_routine_t start_routine,
                                          void *__restrict arg) {
	return libc_pthread_create(newthread, attr, start_routine, arg);
}
/* Terminate calling thread.
 * The registered cleanup handlers are called via exception handling */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") ATTR_NORETURN void
(LIBDCALL libd_pthread_exit)(void *retval) THROWS(...) {
	libc_pthread_exit(retval);
}
/* Make calling thread wait for termination of the thread THREAD. The
 * exit status of the thread is stored in *THREAD_RETURN, if THREAD_RETURN
 * is not NULL */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") int
NOTHROW_RPC(LIBDCALL libd_pthread_join)(pthread_t pthread,
                                        void **thread_return) {
	return libc_pthread_join(pthread, thread_return);
}
/* Check whether thread THREAD has terminated. If yes return the status of
 * the thread in *THREAD_RETURN, if THREAD_RETURN is not NULL */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") int
NOTHROW_NCX(LIBDCALL libd_pthread_tryjoin_np)(pthread_t pthread,
                                              void **thread_return) {
	return libc_pthread_tryjoin_np(pthread, thread_return);
}
/* Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL. */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") int
NOTHROW_RPC(LIBDCALL libd_pthread_timedjoin_np)(pthread_t pthread,
                                                void **thread_return,
                                                struct timespec const *abstime) {
	return libc_pthread_timedjoin_np(pthread, thread_return, abstime);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") int
NOTHROW_RPC(LIBDCALL libd_pthread_timedjoin64_np)(pthread_t pthread,
                                                  void **thread_return,
                                                  struct timespec64 const *abstime) {
	return libc_pthread_timedjoin64_np(pthread, thread_return, abstime);
}
/* Indicate that the thread THREAD is never to be joined with PTHREAD_JOIN.
 * The resources of THREAD will therefore be freed immediately when it
 * terminates, instead of waiting for another thread to perform PTHREAD_JOIN on it */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") int
NOTHROW_NCX(LIBDCALL libd_pthread_detach)(pthread_t pthread) {
	return libc_pthread_detach(pthread);
}
/* Compare two thread identifiers */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") ATTR_CONST int
NOTHROW_NCX(LIBDCALL libd_pthread_equal)(pthread_t thr1,
                                         pthread_t thr2) {
	return libc_pthread_equal(thr1, thr2);
}
/* Initialize thread attribute *ATTR with default attributes
 * (detachstate is PTHREAD_JOINABLE, scheduling policy is SCHED_OTHER, no user-provided stack) */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_attr_init)(pthread_attr_t *attr) {
	return libc_pthread_attr_init(attr);
}
/* Destroy thread attribute *ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_attr_destroy)(pthread_attr_t *attr) {
	return libc_pthread_attr_destroy(attr);
}
/* Get detach state attribute */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_attr_getdetachstate)(pthread_attr_t const *attr,
                                                       int *detachstate) {
	return libc_pthread_attr_getdetachstate(attr, detachstate);
}
/* Set detach state attribute */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_attr_setdetachstate)(pthread_attr_t *attr,
                                                       int detachstate) {
	return libc_pthread_attr_setdetachstate(attr, detachstate);
}
/* Get the size of the guard area created for stack overflow protection */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_attr_getguardsize)(pthread_attr_t const *attr,
                                                     size_t *guardsize) {
	return libc_pthread_attr_getguardsize(attr, guardsize);
}
/* Set the size of the guard area created for stack overflow protection */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_attr_setguardsize)(pthread_attr_t *attr,
                                                     size_t guardsize) {
	return libc_pthread_attr_setguardsize(attr, guardsize);
}
/* Return in *PARAM the scheduling parameters of *ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_attr_getschedparam)(pthread_attr_t const *__restrict attr,
                                                      struct sched_param *__restrict param) {
	return libc_pthread_attr_getschedparam(attr, param);
}
/* Set scheduling parameters (priority, etc) in *ATTR according to PARAM */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_attr_setschedparam)(pthread_attr_t *__restrict attr,
                                                      struct sched_param const *__restrict param) {
	return libc_pthread_attr_setschedparam(attr, param);
}
/* Return in *POLICY the scheduling policy of *ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_attr_getschedpolicy)(pthread_attr_t const *__restrict attr,
                                                       int *__restrict policy) {
	return libc_pthread_attr_getschedpolicy(attr, policy);
}
/* Set scheduling policy in *ATTR according to POLICY */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_attr_setschedpolicy)(pthread_attr_t *attr,
                                                       int policy) {
	return libc_pthread_attr_setschedpolicy(attr, policy);
}
/* Return in *INHERIT the scheduling inheritance mode of *ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_attr_getinheritsched)(pthread_attr_t const *__restrict attr,
                                                        int *__restrict inherit) {
	return libc_pthread_attr_getinheritsched(attr, inherit);
}
/* Set scheduling inheritance mode in *ATTR according to INHERIT */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_attr_setinheritsched)(pthread_attr_t *attr,
                                                        int inherit) {
	return libc_pthread_attr_setinheritsched(attr, inherit);
}
/* Return in *SCOPE the scheduling contention scope of *ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_attr_getscope)(pthread_attr_t const *__restrict attr,
                                                 int *__restrict scope) {
	return libc_pthread_attr_getscope(attr, scope);
}
/* Set scheduling contention scope in *ATTR according to SCOPE */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_attr_setscope)(pthread_attr_t *attr,
                                                 int scope) {
	return libc_pthread_attr_setscope(attr, scope);
}
/* Return the previously set address for the stack */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") ATTR_DEPRECATED("Use pthread_attr_getstack()") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_attr_getstackaddr)(pthread_attr_t const *__restrict attr,
                                                     void **__restrict stackaddr) {
	return libc_pthread_attr_getstackaddr(attr, stackaddr);
}
/* Set the starting address of the stack of the thread to be created.
 * Depending on whether the stack grows up or down the value must either
 * be higher or lower than all the address in the memory block. The
 * minimal size of the block must be PTHREAD_STACK_MIN */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") ATTR_DEPRECATED("Use pthread_attr_setstack()") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_attr_setstackaddr)(pthread_attr_t *attr,
                                                     void *stackaddr) {
	return libc_pthread_attr_setstackaddr(attr, stackaddr);
}
/* Return the currently used minimal stack size */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_attr_getstacksize)(pthread_attr_t const *__restrict attr,
                                                     size_t *__restrict stacksize) {
	return libc_pthread_attr_getstacksize(attr, stacksize);
}
/* Add information about the minimum stack size needed for the thread
 * to be started. This size must never be less than PTHREAD_STACK_MIN
 * and must also not exceed the system limits */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_attr_setstacksize)(pthread_attr_t *attr,
                                                     size_t stacksize) {
	return libc_pthread_attr_setstacksize(attr, stacksize);
}
/* Return the previously set address for the stack */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBDCALL libd_pthread_attr_getstack)(pthread_attr_t const *__restrict attr,
                                                 void **__restrict stackaddr,
                                                 size_t *__restrict stacksize) {
	return libc_pthread_attr_getstack(attr, stackaddr, stacksize);
}
/* The following two interfaces are intended to replace the last two. They
 * require setting the address as well as the size since only setting the
 * address will make the implementation on some architectures impossible */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_attr_setstack)(pthread_attr_t *attr,
                                                 void *stackaddr,
                                                 size_t stacksize) {
	return libc_pthread_attr_setstack(attr, stackaddr, stacksize);
}
/* Thread created with attribute ATTR will be limited to run only on
 * the processors represented in CPUSET */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 3)) int
NOTHROW_NCX(LIBDCALL libd_pthread_attr_setaffinity_np)(pthread_attr_t *attr,
                                                       size_t cpusetsize,
                                                       cpu_set_t const *cpuset) {
	return libc_pthread_attr_setaffinity_np(attr, cpusetsize, cpuset);
}
/* Get bit set in CPUSET representing the processors threads created with ATTR can run on */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 3)) int
NOTHROW_NCX(LIBDCALL libd_pthread_attr_getaffinity_np)(pthread_attr_t const *attr,
                                                       size_t cpusetsize,
                                                       cpu_set_t *cpuset) {
	return libc_pthread_attr_getaffinity_np(attr, cpusetsize, cpuset);
}
/* Get the default attributes used by pthread_create in this process */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_getattr_default_np)(pthread_attr_t *attr) {
	return libc_pthread_getattr_default_np(attr);
}
/* Set the default attributes to be used by pthread_create in this process */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_setattr_default_np)(pthread_attr_t const *attr) {
	return libc_pthread_setattr_default_np(attr);
}
/* Initialize thread attribute *ATTR with attributes corresponding to the
 * already running thread THREAD. It shall be called on uninitialized ATTR
 * and destroyed with pthread_attr_destroy when no longer needed */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_getattr_np)(pthread_t pthread,
                                              pthread_attr_t *attr) {
	return libc_pthread_getattr_np(pthread, attr);
}
/* Set the scheduling parameters for TARGET_THREAD according to POLICY and *PARAM */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((3)) int
NOTHROW_NCX(LIBDCALL libd_pthread_setschedparam)(pthread_t target_thread,
                                                 int policy,
                                                 struct sched_param const *param) {
	return libc_pthread_setschedparam(target_thread, policy, param);
}
/* Return in *POLICY and *PARAM the scheduling parameters for TARGET_THREAD */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((2, 3)) int
NOTHROW_NCX(LIBDCALL libd_pthread_getschedparam)(pthread_t target_thread,
                                                 int *__restrict policy,
                                                 struct sched_param *__restrict param) {
	return libc_pthread_getschedparam(target_thread, policy, param);
}
/* Set the scheduling priority for TARGET_THREAD */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") int
NOTHROW_NCX(LIBDCALL libd_pthread_setschedprio)(pthread_t target_thread,
                                                int prio) {
	return libc_pthread_setschedprio(target_thread, prio);
}
/* Get thread name visible in the kernel and its interfaces */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_getname_np)(pthread_t target_thread,
                                              char *buf,
                                              size_t buflen) {
	return libc_pthread_getname_np(target_thread, buf, buflen);
}
/* Set thread name visible in the kernel and its interfaces */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_setname_np)(pthread_t target_thread,
                                              const char *name) {
	return libc_pthread_setname_np(target_thread, name);
}
/* Return the TID of the given `target_thread'
 * If the given `target_thread' has already terminated, 0 is returned */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") ATTR_CONST WUNUSED pid_t
NOTHROW_NCX(LIBDCALL libd_pthread_gettid_np)(pthread_t target_thread) {
	return libc_pthread_gettid_np(target_thread);
}
/* Set new concurrency level to LEVEL */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") int
NOTHROW_NCX(LIBDCALL libd_pthread_setconcurrency)(int level) {
	return libc_pthread_setconcurrency(level);
}
/* Limit specified thread THREAD to run only on the processors represented in CPUSET */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((3)) int
NOTHROW_NCX(LIBDCALL libd_pthread_setaffinity_np)(pthread_t pthread,
                                                  size_t cpusetsize,
                                                  cpu_set_t const *cpuset) {
	return libc_pthread_setaffinity_np(pthread, cpusetsize, cpuset);
}
/* Get bit set in CPUSET representing the processors THREAD can run on */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((3)) int
NOTHROW_NCX(LIBDCALL libd_pthread_getaffinity_np)(pthread_t pthread,
                                                  size_t cpusetsize,
                                                  cpu_set_t *cpuset) {
	return libc_pthread_getaffinity_np(pthread, cpusetsize, cpuset);
}
/* Guarantee that the initialization function INIT_ROUTINE will be called
 * only once, even if pthread_once is executed several times with the
 * same ONCE_CONTROL argument. ONCE_CONTROL must point to a static or
 * extern variable initialized to PTHREAD_ONCE_INIT. */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
(LIBDCALL libd_pthread_once)(pthread_once_t *once_control,
                             __pthread_once_routine_t init_routine) THROWS(...) {
	return libc_pthread_once(once_control, init_routine);
}
/* Set cancelability state of current thread to STATE,
 * returning old state in *OLDSTATE if OLDSTATE is not NULL */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") int
NOTHROW_NCX(LIBDCALL libd_pthread_setcancelstate)(int state,
                                                  int *oldstate) {
	return libc_pthread_setcancelstate(state, oldstate);
}
/* Set cancellation state of current thread to TYPE, returning the old
 * type in *OLDTYPE if OLDTYPE is not NULL */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") int
NOTHROW_NCX(LIBDCALL libd_pthread_setcanceltype)(int type,
                                                 int *oldtype) {
	return libc_pthread_setcanceltype(type, oldtype);
}
/* Cancel THREAD immediately or at the next possibility */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") int
NOTHROW_NCX(LIBDCALL libd_pthread_cancel)(pthread_t pthread) {
	return libc_pthread_cancel(pthread);
}
/* Function called to call the cleanup handler. As an extern inline
 * function the compiler is free to decide inlining the change when
 * needed or fall back on the copy which must exist somewhere else */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd___pthread_cleanup_routine)(struct __pthread_cleanup_frame *frame) {
	libc___pthread_cleanup_routine(frame);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") __cleanup_fct_attribute void
NOTHROW_NCX(LIBDCALL libd___pthread_register_cancel)(__pthread_unwind_buf_t *buf) {
	libc___pthread_register_cancel(buf);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") __cleanup_fct_attribute NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd___pthread_unregister_cancel)(__pthread_unwind_buf_t *buf) {
	libc___pthread_unregister_cancel(buf);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") __cleanup_fct_attribute NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd___pthread_register_cancel_defer)(__pthread_unwind_buf_t *buf) {
	libc___pthread_register_cancel_defer(buf);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") __cleanup_fct_attribute NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd___pthread_unregister_cancel_restore)(__pthread_unwind_buf_t *buf) {
	libc___pthread_unregister_cancel_restore(buf);
}
/* Internal interface to initiate cleanup */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") ATTR_WEAK __cleanup_fct_attribute NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd___pthread_unwind_next)(__pthread_unwind_buf_t *buf) {
	libc___pthread_unwind_next(buf);
}
/* Initialize a mutex */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutex_init)(pthread_mutex_t *mutex,
                                              pthread_mutexattr_t const *mutexattr) {
	return libc_pthread_mutex_init(mutex, mutexattr);
}
/* Destroy a mutex */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutex_destroy)(pthread_mutex_t *mutex) {
	return libc_pthread_mutex_destroy(mutex);
}
/* Try locking a mutex */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutex_trylock)(pthread_mutex_t *mutex) {
	return libc_pthread_mutex_trylock(mutex);
}
/* Lock a mutex */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutex_lock)(pthread_mutex_t *mutex) {
	return libc_pthread_mutex_lock(mutex);
}
/* Wait until lock becomes available, or specified time passes */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_pthread_mutex_timedlock)(pthread_mutex_t *__restrict mutex,
                                                   struct timespec const *__restrict abstime) {
	return libc_pthread_mutex_timedlock(mutex, abstime);
}
/* Wait until lock becomes available, or specified time passes */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_pthread_mutex_timedlock64)(pthread_mutex_t *__restrict mutex,
                                                     struct timespec64 const *__restrict abstime) {
	return libc_pthread_mutex_timedlock64(mutex, abstime);
}
/* Unlock a mutex */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutex_unlock)(pthread_mutex_t *mutex) {
	return libc_pthread_mutex_unlock(mutex);
}
/* Get the priority ceiling of MUTEX */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutex_getprioceiling)(pthread_mutex_t const *__restrict mutex,
                                                        int *__restrict prioceiling) {
	return libc_pthread_mutex_getprioceiling(mutex, prioceiling);
}
/* Set the priority ceiling of MUTEX to PRIOCEILING, return old
 * priority ceiling value in *OLD_CEILING */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 3)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutex_setprioceiling)(pthread_mutex_t *__restrict mutex,
                                                        int prioceiling,
                                                        int *__restrict old_ceiling) {
	return libc_pthread_mutex_setprioceiling(mutex, prioceiling, old_ceiling);
}
/* Declare the state protected by MUTEX as consistent */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutex_consistent)(pthread_mutex_t *mutex) {
	return libc_pthread_mutex_consistent(mutex);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutex_consistent_np)(pthread_mutex_t *mutex) {
	return libc_pthread_mutex_consistent_np(mutex);
}
/* Initialize mutex attribute object ATTR with default attributes (kind is PTHREAD_MUTEX_TIMED_NP) */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_init)(pthread_mutexattr_t *attr) {
	return libc_pthread_mutexattr_init(attr);
}
/* Destroy mutex attribute object ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_destroy)(pthread_mutexattr_t *attr) {
	return libc_pthread_mutexattr_destroy(attr);
}
/* Get the process-shared flag of the mutex attribute ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_getpshared)(pthread_mutexattr_t const *__restrict attr,
                                                        int *__restrict pshared) {
	return libc_pthread_mutexattr_getpshared(attr, pshared);
}
/* Set the process-shared flag of the mutex attribute ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_setpshared)(pthread_mutexattr_t *attr,
                                                        int pshared) {
	return libc_pthread_mutexattr_setpshared(attr, pshared);
}
/* Return in *KIND the mutex kind attribute in *ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_gettype)(pthread_mutexattr_t const *__restrict attr,
                                                     int *__restrict kind) {
	return libc_pthread_mutexattr_gettype(attr, kind);
}
/* Set the mutex kind attribute in *ATTR to KIND (either PTHREAD_MUTEX_NORMAL,
 * PTHREAD_MUTEX_RECURSIVE, PTHREAD_MUTEX_ERRORCHECK, or PTHREAD_MUTEX_DEFAULT) */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_settype)(pthread_mutexattr_t *attr,
                                                     int kind) {
	return libc_pthread_mutexattr_settype(attr, kind);
}
/* Return in *PROTOCOL the mutex protocol attribute in *ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_getprotocol)(pthread_mutexattr_t const *__restrict attr,
                                                         int *__restrict protocol) {
	return libc_pthread_mutexattr_getprotocol(attr, protocol);
}
/* Set the mutex protocol attribute in *ATTR to PROTOCOL (either
 * PTHREAD_PRIO_NONE, PTHREAD_PRIO_INHERIT, or PTHREAD_PRIO_PROTECT) */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_setprotocol)(pthread_mutexattr_t *attr,
                                                         int protocol) {
	return libc_pthread_mutexattr_setprotocol(attr, protocol);
}
/* Return in *PRIOCEILING the mutex prioceiling attribute in *ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_getprioceiling)(pthread_mutexattr_t const *__restrict attr,
                                                            int *__restrict prioceiling) {
	return libc_pthread_mutexattr_getprioceiling(attr, prioceiling);
}
/* Set the mutex prioceiling attribute in *ATTR to PRIOCEILING */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_setprioceiling)(pthread_mutexattr_t *attr,
                                                            int prioceiling) {
	return libc_pthread_mutexattr_setprioceiling(attr, prioceiling);
}
/* Get the robustness flag of the mutex attribute ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_getrobust)(pthread_mutexattr_t const *attr,
                                                       int *robustness) {
	return libc_pthread_mutexattr_getrobust(attr, robustness);
}
/* Set the robustness flag of the mutex attribute ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_setrobust)(pthread_mutexattr_t *attr,
                                                       int robustness) {
	return libc_pthread_mutexattr_setrobust(attr, robustness);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_getrobust_np)(pthread_mutexattr_t const *attr,
                                                          int *robustness) {
	return libc_pthread_mutexattr_getrobust_np(attr, robustness);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_mutexattr_setrobust_np)(pthread_mutexattr_t *attr,
                                                          int robustness) {
	return libc_pthread_mutexattr_setrobust_np(attr, robustness);
}
/* Initialize read-write lock RWLOCK using attributes ATTR,
 * or use the default values if later is NULL */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_rwlock_init)(pthread_rwlock_t *__restrict rwlock,
                                               pthread_rwlockattr_t const *__restrict attr) {
	return libc_pthread_rwlock_init(rwlock, attr);
}
/* Destroy read-write lock RWLOCK */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_rwlock_destroy)(pthread_rwlock_t *rwlock) {
	return libc_pthread_rwlock_destroy(rwlock);
}
/* Acquire read lock for RWLOCK */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_pthread_rwlock_rdlock)(pthread_rwlock_t *rwlock) {
	return libc_pthread_rwlock_rdlock(rwlock);
}
/* Try to acquire read lock for RWLOCK */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_rwlock_tryrdlock)(pthread_rwlock_t *rwlock) {
	return libc_pthread_rwlock_tryrdlock(rwlock);
}
/* Try to acquire read lock for RWLOCK or return after specfied time */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_pthread_rwlock_timedrdlock)(pthread_rwlock_t *__restrict rwlock,
                                                      struct timespec const *__restrict abstime) {
	return libc_pthread_rwlock_timedrdlock(rwlock, abstime);
}
/* Try to acquire read lock for RWLOCK or return after specfied time */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_pthread_rwlock_timedrdlock64)(pthread_rwlock_t *__restrict rwlock,
                                                        struct timespec64 const *__restrict abstime) {
	return libc_pthread_rwlock_timedrdlock64(rwlock, abstime);
}
/* Acquire write lock for RWLOCK */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_pthread_rwlock_wrlock)(pthread_rwlock_t *rwlock) {
	return libc_pthread_rwlock_wrlock(rwlock);
}
/* Try to acquire write lock for RWLOCK */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_rwlock_trywrlock)(pthread_rwlock_t *rwlock) {
	return libc_pthread_rwlock_trywrlock(rwlock);
}
/* Try to acquire write lock for RWLOCK or return after specfied time */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_pthread_rwlock_timedwrlock)(pthread_rwlock_t *__restrict rwlock,
                                                      struct timespec const *__restrict abstime) {
	return libc_pthread_rwlock_timedwrlock(rwlock, abstime);
}
/* Try to acquire write lock for RWLOCK or return after specfied time */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_pthread_rwlock_timedwrlock64)(pthread_rwlock_t *__restrict rwlock,
                                                        struct timespec64 const *__restrict abstime) {
	return libc_pthread_rwlock_timedwrlock64(rwlock, abstime);
}
/* Unlock RWLOCK */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_rwlock_unlock)(pthread_rwlock_t *rwlock) {
	return libc_pthread_rwlock_unlock(rwlock);
}
/* Initialize attribute object ATTR with default values */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_rwlockattr_init)(pthread_rwlockattr_t *attr) {
	return libc_pthread_rwlockattr_init(attr);
}
/* Destroy attribute object ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_rwlockattr_destroy)(pthread_rwlockattr_t *attr) {
	return libc_pthread_rwlockattr_destroy(attr);
}
/* Return current setting of process-shared attribute of ATTR in PSHARED */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_rwlockattr_getpshared)(pthread_rwlockattr_t const *__restrict attr,
                                                         int *__restrict pshared) {
	return libc_pthread_rwlockattr_getpshared(attr, pshared);
}
/* Set process-shared attribute of ATTR to PSHARED */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_rwlockattr_setpshared)(pthread_rwlockattr_t *attr,
                                                         int pshared) {
	return libc_pthread_rwlockattr_setpshared(attr, pshared);
}
/* Return current setting of reader/writer preference */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_rwlockattr_getkind_np)(pthread_rwlockattr_t const *__restrict attr,
                                                         int *__restrict pref) {
	return libc_pthread_rwlockattr_getkind_np(attr, pref);
}
/* Set reader/write preference */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_rwlockattr_setkind_np)(pthread_rwlockattr_t *attr,
                                                         int pref) {
	return libc_pthread_rwlockattr_setkind_np(attr, pref);
}
/* Initialize condition variable COND using attributes ATTR, or use
 * the default values if later is NULL */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_cond_init)(pthread_cond_t *__restrict cond,
                                             pthread_condattr_t const *__restrict cond_attr) {
	return libc_pthread_cond_init(cond, cond_attr);
}
/* Destroy condition variable COND */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_cond_destroy)(pthread_cond_t *cond) {
	return libc_pthread_cond_destroy(cond);
}
/* Wake up one thread waiting for condition variable COND */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_cond_signal)(pthread_cond_t *cond) {
	return libc_pthread_cond_signal(cond);
}
/* Wake up all threads waiting for condition variables COND */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_cond_broadcast)(pthread_cond_t *cond) {
	return libc_pthread_cond_broadcast(cond);
}
/* Wait for condition variable COND to be signaled or broadcast.
 * MUTEX is assumed to be locked before. */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_pthread_cond_wait)(pthread_cond_t *__restrict cond,
                                             pthread_mutex_t *__restrict mutex) {
	return libc_pthread_cond_wait(cond, mutex);
}
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970). */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBDCALL libd_pthread_cond_timedwait)(pthread_cond_t *__restrict cond,
                                                  pthread_mutex_t *__restrict mutex,
                                                  struct timespec const *__restrict abstime) {
	return libc_pthread_cond_timedwait(cond, mutex, abstime);
}
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970). */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBDCALL libd_pthread_cond_timedwait64)(pthread_cond_t *__restrict cond,
                                                    pthread_mutex_t *__restrict mutex,
                                                    struct timespec64 const *__restrict abstime) {
	return libc_pthread_cond_timedwait64(cond, mutex, abstime);
}
/* Initialize condition variable attribute ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_condattr_init)(pthread_condattr_t *attr) {
	return libc_pthread_condattr_init(attr);
}
/* Destroy condition variable attribute ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_condattr_destroy)(pthread_condattr_t *attr) {
	return libc_pthread_condattr_destroy(attr);
}
/* Get the process-shared flag of the condition variable attribute ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_condattr_getpshared)(pthread_condattr_t const *__restrict attr,
                                                       int *__restrict pshared) {
	return libc_pthread_condattr_getpshared(attr, pshared);
}
/* Set the process-shared flag of the condition variable attribute ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_condattr_setpshared)(pthread_condattr_t *attr,
                                                       int pshared) {
	return libc_pthread_condattr_setpshared(attr, pshared);
}
/* Get the clock selected for the condition variable attribute ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_condattr_getclock)(pthread_condattr_t const *__restrict attr,
                                                     clockid_t *__restrict clock_id) {
	return libc_pthread_condattr_getclock(attr, clock_id);
}
/* Set the clock selected for the condition variable attribute ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_condattr_setclock)(pthread_condattr_t *attr,
                                                     clockid_t clock_id) {
	return libc_pthread_condattr_setclock(attr, clock_id);
}
/* Initialize the spinlock LOCK. If PSHARED is nonzero the
 * spinlock can be shared between different processes */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_spin_init)(pthread_spinlock_t *lock,
                                             int pshared) {
	return libc_pthread_spin_init(lock, pshared);
}
/* Destroy the spinlock LOCK */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_spin_destroy)(pthread_spinlock_t *lock) {
	return libc_pthread_spin_destroy(lock);
}
/* Wait until spinlock LOCK is retrieved */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_spin_lock)(pthread_spinlock_t *lock) {
	return libc_pthread_spin_lock(lock);
}
/* Try to lock spinlock LOCK */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_spin_trylock)(pthread_spinlock_t *lock) {
	return libc_pthread_spin_trylock(lock);
}
/* Release spinlock LOCK */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_spin_unlock)(pthread_spinlock_t *lock) {
	return libc_pthread_spin_unlock(lock);
}
/* Initialize BARRIER with the attributes in ATTR.
 * The barrier is opened when COUNT waiters arrived */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_barrier_init)(pthread_barrier_t *__restrict barrier,
                                                pthread_barrierattr_t const *__restrict attr,
                                                unsigned int count) {
	return libc_pthread_barrier_init(barrier, attr, count);
}
/* Destroy a previously dynamically initialized barrier BARRIER */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_barrier_destroy)(pthread_barrier_t *barrier) {
	return libc_pthread_barrier_destroy(barrier);
}
/* Wait on barrier BARRIER */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_pthread_barrier_wait)(pthread_barrier_t *barrier) {
	return libc_pthread_barrier_wait(barrier);
}
/* Initialize barrier attribute ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_barrierattr_init)(pthread_barrierattr_t *attr) {
	return libc_pthread_barrierattr_init(attr);
}
/* Destroy previously dynamically initialized barrier attribute ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_barrierattr_destroy)(pthread_barrierattr_t *attr) {
	return libc_pthread_barrierattr_destroy(attr);
}
/* Get the process-shared flag of the barrier attribute ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_barrierattr_getpshared)(pthread_barrierattr_t const *__restrict attr,
                                                          int *__restrict pshared) {
	return libc_pthread_barrierattr_getpshared(attr, pshared);
}
/* Set the process-shared flag of the barrier attribute ATTR */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_barrierattr_setpshared)(pthread_barrierattr_t *attr,
                                                          int pshared) {
	return libc_pthread_barrierattr_setpshared(attr, pshared);
}
/* Create a key value identifying a location in the thread-specific
 * data area. Each thread maintains a distinct thread-specific data
 * area. DESTR_FUNCTION, if non-NULL, is called with the value
 * associated to that key when the key is destroyed.
 * DESTR_FUNCTION is not called if the value associated is NULL when
 * the key is destroyed */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pthread_key_create)(pthread_key_t *key,
                                              __pthread_destr_function_t destr_function) {
	return libc_pthread_key_create(key, destr_function);
}
/* Destroy KEY */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") int
NOTHROW_NCX(LIBDCALL libd_pthread_key_delete)(pthread_key_t key) {
	return libc_pthread_key_delete(key);
}
/* Return current value of the thread-specific data slot identified by KEY */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") void *
NOTHROW_NCX(LIBDCALL libd_pthread_getspecific)(pthread_key_t key) {
	return libc_pthread_getspecific(key);
}
/* Store POINTER in the thread-specific data slot identified by KEY */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") int
NOTHROW_NCX(LIBDCALL libd_pthread_setspecific)(pthread_key_t key,
                                               void const *pointer) {
	return libc_pthread_setspecific(key, pointer);
}
/* Get ID of CPU-time clock for thread THREAD_ID */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_pthread_getcpuclockid)(pthread_t pthread_id,
                                                 clockid_t *clock_id) {
	return libc_pthread_getcpuclockid(pthread_id, clock_id);
}
/* Install handlers to be called when a new process is created with FORK.
 * The PREPARE handler is called in the parent process just before performing
 * FORK. The PARENT handler is called in the parent process just after FORK.
 * The CHILD handler is called in the child process. Each of the three
 * handlers can be NULL, meaning that no handler needs to be called at that
 * point.
 * PTHREAD_ATFORK can be called several times, in which case the PREPARE
 * handlers are called in LIFO order (last added with PTHREAD_ATFORK,
 * first called before FORK), and the PARENT and CHILD handlers are called
 * in FIFO (first added, first called) */
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") int
NOTHROW_NCX(LIBDCALL libd_pthread_atfork)(__pthread_atfork_func_t prepare,
                                          __pthread_atfork_func_t parent,
                                          __pthread_atfork_func_t child) {
	return libc_pthread_atfork(prepare, parent, child);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread_ext") int
NOTHROW_NCX(LIBDCALL libd_pthread_set_num_processors_np)(int n) {
	return libc_pthread_set_num_processors_np(n);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$pthread_create, libd_pthread_create);
DEFINE_PUBLIC_ALIAS(DOS$pthread_exit, libd_pthread_exit);
DEFINE_PUBLIC_ALIAS(DOS$pthread_join, libd_pthread_join);
DEFINE_PUBLIC_ALIAS(DOS$pthread_tryjoin_np, libd_pthread_tryjoin_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_timedjoin_np, libd_pthread_timedjoin_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_timedjoin64_np, libd_pthread_timedjoin64_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_detach, libd_pthread_detach);
DEFINE_PUBLIC_ALIAS(DOS$thrd_equal, libd_pthread_equal);
DEFINE_PUBLIC_ALIAS(DOS$pthread_equal, libd_pthread_equal);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_init, libd_pthread_attr_init);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_destroy, libd_pthread_attr_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_getdetachstate, libd_pthread_attr_getdetachstate);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setdetachstate, libd_pthread_attr_setdetachstate);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_getguardsize, libd_pthread_attr_getguardsize);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setguardsize, libd_pthread_attr_setguardsize);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_getschedparam, libd_pthread_attr_getschedparam);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setschedparam, libd_pthread_attr_setschedparam);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_getschedpolicy, libd_pthread_attr_getschedpolicy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setschedpolicy, libd_pthread_attr_setschedpolicy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_getinheritsched, libd_pthread_attr_getinheritsched);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setinheritsched, libd_pthread_attr_setinheritsched);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_getscope, libd_pthread_attr_getscope);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setscope, libd_pthread_attr_setscope);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_getstackaddr, libd_pthread_attr_getstackaddr);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setstackaddr, libd_pthread_attr_setstackaddr);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_getstacksize, libd_pthread_attr_getstacksize);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setstacksize, libd_pthread_attr_setstacksize);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_getstack, libd_pthread_attr_getstack);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setstack, libd_pthread_attr_setstack);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setaffinity_np, libd_pthread_attr_setaffinity_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_getaffinity_np, libd_pthread_attr_getaffinity_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_getattr_default_np, libd_pthread_getattr_default_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_setattr_default_np, libd_pthread_setattr_default_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_getattr_np, libd_pthread_getattr_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_setschedparam, libd_pthread_setschedparam);
DEFINE_PUBLIC_ALIAS(DOS$pthread_getschedparam, libd_pthread_getschedparam);
DEFINE_PUBLIC_ALIAS(DOS$pthread_setschedprio, libd_pthread_setschedprio);
DEFINE_PUBLIC_ALIAS(DOS$pthread_getname_np, libd_pthread_getname_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_setname_np, libd_pthread_setname_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_gettid_np, libd_pthread_gettid_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_setconcurrency, libd_pthread_setconcurrency);
DEFINE_PUBLIC_ALIAS(DOS$pthread_setaffinity_np, libd_pthread_setaffinity_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_getaffinity_np, libd_pthread_getaffinity_np);
DEFINE_PUBLIC_ALIAS(DOS$call_once, libd_pthread_once);
DEFINE_PUBLIC_ALIAS(DOS$pthread_once, libd_pthread_once);
DEFINE_PUBLIC_ALIAS(DOS$pthread_setcancelstate, libd_pthread_setcancelstate);
DEFINE_PUBLIC_ALIAS(DOS$pthread_setcanceltype, libd_pthread_setcanceltype);
DEFINE_PUBLIC_ALIAS(DOS$pthread_cancel, libd_pthread_cancel);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_cleanup_routine, libd___pthread_cleanup_routine);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_register_cancel, libd___pthread_register_cancel);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_unregister_cancel, libd___pthread_unregister_cancel);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_register_cancel_defer, libd___pthread_register_cancel_defer);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_unregister_cancel_restore, libd___pthread_unregister_cancel_restore);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_unwind_next, libd___pthread_unwind_next);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_init, libd_pthread_mutex_init);
DEFINE_PUBLIC_ALIAS(DOS$mtx_destroy, libd_pthread_mutex_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_destroy, libd_pthread_mutex_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_trylock, libd_pthread_mutex_trylock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_lock, libd_pthread_mutex_lock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_timedlock, libd_pthread_mutex_timedlock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_timedlock64, libd_pthread_mutex_timedlock64);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_unlock, libd_pthread_mutex_unlock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_getprioceiling, libd_pthread_mutex_getprioceiling);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_setprioceiling, libd_pthread_mutex_setprioceiling);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_consistent, libd_pthread_mutex_consistent);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_consistent_np, libd_pthread_mutex_consistent_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_init, libd_pthread_mutexattr_init);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_destroy, libd_pthread_mutexattr_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_getpshared, libd_pthread_mutexattr_getpshared);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_setpshared, libd_pthread_mutexattr_setpshared);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_gettype, libd_pthread_mutexattr_gettype);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_settype, libd_pthread_mutexattr_settype);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_getprotocol, libd_pthread_mutexattr_getprotocol);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_setprotocol, libd_pthread_mutexattr_setprotocol);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_getprioceiling, libd_pthread_mutexattr_getprioceiling);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_setprioceiling, libd_pthread_mutexattr_setprioceiling);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_getrobust, libd_pthread_mutexattr_getrobust);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_setrobust, libd_pthread_mutexattr_setrobust);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_getrobust_np, libd_pthread_mutexattr_getrobust_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_setrobust_np, libd_pthread_mutexattr_setrobust_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_init, libd_pthread_rwlock_init);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_destroy, libd_pthread_rwlock_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_rdlock, libd_pthread_rwlock_rdlock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_tryrdlock, libd_pthread_rwlock_tryrdlock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_timedrdlock, libd_pthread_rwlock_timedrdlock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_timedrdlock64, libd_pthread_rwlock_timedrdlock64);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_wrlock, libd_pthread_rwlock_wrlock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_trywrlock, libd_pthread_rwlock_trywrlock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_timedwrlock, libd_pthread_rwlock_timedwrlock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_timedwrlock64, libd_pthread_rwlock_timedwrlock64);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_unlock, libd_pthread_rwlock_unlock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlockattr_init, libd_pthread_rwlockattr_init);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlockattr_destroy, libd_pthread_rwlockattr_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlockattr_getpshared, libd_pthread_rwlockattr_getpshared);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlockattr_setpshared, libd_pthread_rwlockattr_setpshared);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlockattr_getkind_np, libd_pthread_rwlockattr_getkind_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlockattr_setkind_np, libd_pthread_rwlockattr_setkind_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_cond_init, libd_pthread_cond_init);
DEFINE_PUBLIC_ALIAS(DOS$cnd_destroy, libd_pthread_cond_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_cond_destroy, libd_pthread_cond_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_cond_signal, libd_pthread_cond_signal);
DEFINE_PUBLIC_ALIAS(DOS$pthread_cond_broadcast, libd_pthread_cond_broadcast);
DEFINE_PUBLIC_ALIAS(DOS$pthread_cond_wait, libd_pthread_cond_wait);
DEFINE_PUBLIC_ALIAS(DOS$pthread_cond_timedwait, libd_pthread_cond_timedwait);
DEFINE_PUBLIC_ALIAS(DOS$pthread_cond_timedwait64, libd_pthread_cond_timedwait64);
DEFINE_PUBLIC_ALIAS(DOS$pthread_condattr_init, libd_pthread_condattr_init);
DEFINE_PUBLIC_ALIAS(DOS$pthread_condattr_destroy, libd_pthread_condattr_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_condattr_getpshared, libd_pthread_condattr_getpshared);
DEFINE_PUBLIC_ALIAS(DOS$pthread_condattr_setpshared, libd_pthread_condattr_setpshared);
DEFINE_PUBLIC_ALIAS(DOS$pthread_condattr_getclock, libd_pthread_condattr_getclock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_condattr_setclock, libd_pthread_condattr_setclock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_spin_init, libd_pthread_spin_init);
DEFINE_PUBLIC_ALIAS(DOS$pthread_spin_destroy, libd_pthread_spin_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_spin_lock, libd_pthread_spin_lock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_spin_trylock, libd_pthread_spin_trylock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_spin_unlock, libd_pthread_spin_unlock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_barrier_init, libd_pthread_barrier_init);
DEFINE_PUBLIC_ALIAS(DOS$pthread_barrier_destroy, libd_pthread_barrier_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_barrier_wait, libd_pthread_barrier_wait);
DEFINE_PUBLIC_ALIAS(DOS$pthread_barrierattr_init, libd_pthread_barrierattr_init);
DEFINE_PUBLIC_ALIAS(DOS$pthread_barrierattr_destroy, libd_pthread_barrierattr_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_barrierattr_getpshared, libd_pthread_barrierattr_getpshared);
DEFINE_PUBLIC_ALIAS(DOS$pthread_barrierattr_setpshared, libd_pthread_barrierattr_setpshared);
DEFINE_PUBLIC_ALIAS(DOS$pthread_key_create, libd_pthread_key_create);
DEFINE_PUBLIC_ALIAS(DOS$tss_delete, libd_pthread_key_delete);
DEFINE_PUBLIC_ALIAS(DOS$pthread_key_delete, libd_pthread_key_delete);
DEFINE_PUBLIC_ALIAS(DOS$tss_get, libd_pthread_getspecific);
DEFINE_PUBLIC_ALIAS(DOS$pthread_getspecific, libd_pthread_getspecific);
DEFINE_PUBLIC_ALIAS(DOS$pthread_setspecific, libd_pthread_setspecific);
DEFINE_PUBLIC_ALIAS(DOS$pthread_getcpuclockid, libd_pthread_getcpuclockid);
DEFINE_PUBLIC_ALIAS(DOS$pthread_atfork, libd_pthread_atfork);
DEFINE_PUBLIC_ALIAS(DOS$pthread_set_num_processors_np, libd_pthread_set_num_processors_np);

#endif /* !GUARD_LIBC_AUTO_DOSABI_PTHREAD_C */
