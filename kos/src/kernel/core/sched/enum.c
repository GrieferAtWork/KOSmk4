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
#ifndef GUARD_KERNEL_SRC_SCHED_ENUM_C
#define GUARD_KERNEL_SRC_SCHED_ENUM_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/rt.h> /* dbg_active */
#include <kernel/panic.h>
#include <sched/cpu.h>
#include <sched/enum.h>
#include <sched/pertask.h>
#include <sched/scheduler.h>
#include <sched/task.h>

#include <kos/kernel/cpu-state.h>
#include <kos/types.h>

#include <assert.h>
#include <atomic.h>
#include <stdbool.h>

DECL_BEGIN



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
#ifdef CONFIG_NO_SMP
PUBLIC NOBLOCK NONNULL((1)) ssize_t
NOTHROW(FCALL system_enum_threads_nb)(system_enum_threads_cb_t cb, void *arg)
#define LOCAL_cpu (&bootcpu)
#else /* CONFIG_NO_SMP */
PUBLIC NOBLOCK NONNULL((1, 3)) ssize_t
NOTHROW(FCALL system_enum_threads_cpu_noipi_nb)(system_enum_threads_cb_t cb, void *arg,
                                                struct cpu *__restrict me)
#define LOCAL_cpu me
#endif /* !CONFIG_NO_SMP */
{
	ssize_t temp, result;
	struct task *thread, *idle;
	/* Start out by enumerating our IDLE thread. */
	idle   = &FORCPU(LOCAL_cpu, thiscpu_idle);
	result = (*cb)(arg, idle);
	if unlikely(result < 0)
		goto done;

	/* Now walk the running-thread-loop */
	FOREACH_thiscpu_threads (thread, LOCAL_cpu) {
		if (thread != idle) {
			temp = (*cb)(arg, thread);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
	}

#ifndef CONFIG_NO_SMP
	/* Now go through all of the pending threads. */
	FOREACH_thiscpu_sched_pending (thread, LOCAL_cpu) {
		assert(thread != idle || kernel_poisoned());
		temp = (*cb)(arg, thread);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
#endif /* !CONFIG_NO_SMP */

done:
	return result;
err:
	return temp;
}
#undef LOCAL_cpu

#ifndef CONFIG_NO_SMP
#if CPU_IPI_ARGCOUNT < 4
#error "Need at least 4 IPI pointers!"
#endif /* CPU_IPI_ARGCOUNT < 4 */
PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) /*ATTR_NOTHROW*/ struct icpustate *
NOTHROW(FCALL system_enum_threads_ipi)(struct icpustate *__restrict state,
                                       void *args[CPU_IPI_ARGCOUNT]) {
	system_enum_threads_cb_t cb;
	void *cb_arg;
	ssize_t *presult;
	cb       = (system_enum_threads_cb_t)args[0];
	cb_arg   = args[1];
	presult  = (ssize_t *)args[2];
	*presult = system_enum_threads_cpu_noipi_nb(cb, cb_arg, THIS_CPU);
	COMPILER_BARRIER();
	*(bool *)args[3] = true; /* Indicate callback completion. */
	COMPILER_BARRIER();
	return state;
}

/* Enumerate threads hosted by `me' */
PRIVATE NOBLOCK NONNULL((1, 3, 4)) ssize_t
NOTHROW(FCALL system_enum_cputhreads_nb)(system_enum_threads_cb_t cb, void *arg,
                                         struct cpu *__restrict me,
                                         struct cpu *__restrict mycpu) {
	ssize_t result;
	void *args[CPU_IPI_ARGCOUNT];
	bool completed;
	if (me == mycpu || dbg_active)
		return system_enum_threads_cpu_noipi_nb(cb, arg, me);
	completed = false;
	args[0] = (void *)cb;
	args[1] = arg;
	args[2] = (void *)&result;
	args[3] = &completed;

	/* Wait until we can send an IPI */
	while (!cpu_sendipi(me, &system_enum_threads_ipi, args,
	                    CPU_IPI_FWAITFOR | CPU_IPI_FWAKEUP))
		task_pause();

	/* Wait for IPI to complete. */
	while (!atomic_load(&completed))
		task_pause();

	/* Done! */
	return result;
}

/* Same as `system_enum_threads_nb()', but don't use IPIs.
 * This requires `dbg_active' or the caller to be a  super
 * override. */
PUBLIC NOBLOCK NONNULL((1)) ssize_t
NOTHROW(FCALL system_enum_threads_noipi_nb)(system_enum_threads_cb_t cb, void *arg) {
	unsigned int i = 0;
	ssize_t temp, result = 0;
	do {
		temp = system_enum_threads_cpu_noipi_nb(cb, arg, cpu_vector[i]);
		if unlikely(temp < 0) {
			result = temp;
			goto done;
		}
		result += temp;
	} while (++i < cpu_count);
done:
	return result;
}


PUBLIC NOBLOCK NONNULL((1)) ssize_t
NOTHROW(FCALL system_enum_threads_nb)(system_enum_threads_cb_t cb, void *arg) {
	unsigned int i = 0;
	ssize_t temp, result = 0;
	struct task *caller = THIS_TASK;
	uintptr_t old_flags = atomic_fetchor(&caller->t_flags, TASK_FKEEPCORE);
	struct cpu *mycpu   = atomic_read(&caller->t_cpu);
	do {
		temp = system_enum_cputhreads_nb(cb, arg, cpu_vector[i], mycpu);
		if unlikely(temp < 0) {
			result = temp;
			goto done;
		}
		result += temp;
	} while (++i < cpu_count);
done:
	if (!(old_flags & TASK_FKEEPCORE))
		atomic_and(&caller->t_flags, ~TASK_FKEEPCORE);
	return result;
}

/* Enumerate threads hosted by `me' */
PUBLIC NOBLOCK NONNULL((1, 3)) ssize_t
NOTHROW(FCALL system_enum_threads_cpu_nb)(system_enum_threads_cb_t cb, void *arg,
                                          struct cpu *__restrict me) {
	ssize_t result;
	struct task *caller = THIS_TASK;
	uintptr_t old_flags = atomic_fetchor(&caller->t_flags, TASK_FKEEPCORE);
	struct cpu *mycpu   = atomic_read(&caller->t_cpu);
	/* Enumerate the given CPU */
	result = system_enum_cputhreads_nb(cb, arg, me, mycpu);
	if (!(old_flags & TASK_FKEEPCORE))
		atomic_and(&caller->t_flags, ~TASK_FKEEPCORE);
	return result;
}
#endif /* !CONFIG_NO_SMP */

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_ENUM_C */
