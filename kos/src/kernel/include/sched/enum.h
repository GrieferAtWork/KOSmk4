/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_SCHED_ENUM_H
#define GUARD_KERNEL_INCLUDE_SCHED_ENUM_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

/* Helper functions for enumerating KOS system threads. */
#define TASK_ENUM_CC FCALL

DECL_BEGIN

#ifdef __CC__
struct taskpid;
struct task;
struct cpu;

typedef NONNULL((2)) ssize_t
(TASK_ENUM_CC *system_enum_threads_cb_t)(void *arg, struct task *__restrict thread);


/* Enumerate all threads on the entire system without blocking.
 * WARNING: On SMP, this function makes use of IPIs, which it will
 *          also wait for to complete, meaning that if another CPU
 *          waits for this  function to  complete with  preemption
 *          disabled, the system will dead-lock
 * WARNING: This function can  only give  a "best-effort"  guaranty
 *          when it comes  to not missing  any threads. --  Threads
 *          that move between CPUs during the call to this function
 *          may not  be listed,  and threads  that have  yet to  be
 *          started  aren't  listed, either.  Consequently,  it can
 *          also happen that a thread is enumerated more than once.
 * NOTE: Only use this function if it's OK to miss some thread, and
 *       for some threads to be listed  more than once. If it's  at
 *       all possible for  you to acquire  a lock to  `pidns_root',
 *       you should do that instead, as  that's the only way to  do
 *       a consistent enumeration of threads. */
FUNDEF NOBLOCK NONNULL((1)) ssize_t
NOTHROW(FCALL system_enum_threads_nb)(system_enum_threads_cb_t cb, void *arg);

#ifdef CONFIG_NO_SMP
#define system_enum_threads_noipi_nb(cb, arg)         system_enum_threads_nb(cb, arg)
#define system_enum_threads_cpu_nb(cb, arg, me)       system_enum_threads_nb(cb, arg)
#define system_enum_threads_cpu_noipi_nb(cb, arg, me) system_enum_threads_nb(cb, arg)
#else /* CONFIG_NO_SMP */
/* Same as `system_enum_threads_nb()', but don't use IPIs.
 * This requires `dbg_active' or the caller to be a  super
 * override. */
FUNDEF NOBLOCK NONNULL((1)) ssize_t
NOTHROW(FCALL system_enum_threads_noipi_nb)(system_enum_threads_cb_t cb, void *arg);

/* Enumerate threads hosted by `me' */
FUNDEF NOBLOCK NONNULL((1, 3)) ssize_t
NOTHROW(FCALL system_enum_threads_cpu_nb)(system_enum_threads_cb_t cb, void *arg,
                                          struct cpu *__restrict me);

/* Same as `system_enum_threads_cpu_nb()', but assume that `me == THIS_CPU',
 * or that the caller is somehow  preventing changes to the scheduler  state
 * of `me' (e.g. via `sched_super_override_start()' or `dbg_active') */
FUNDEF NOBLOCK NONNULL((1, 3)) ssize_t
NOTHROW(FCALL system_enum_threads_cpu_noipi_nb)(system_enum_threads_cb_t cb, void *arg,
                                                struct cpu *__restrict me);
#endif /* !CONFIG_NO_SMP */

#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_ENUM_H */
