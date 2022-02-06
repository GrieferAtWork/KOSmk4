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
#ifndef GUARD_KERNEL_SRC_SCHED_ENUM_C
#define GUARD_KERNEL_SRC_SCHED_ENUM_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/rt.h> /* dbg_active */
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/panic.h>
#include <kernel/types.h>
#include <sched/cpu.h>
#include <sched/enum.h>
#include <sched/group.h>
#include <sched/scheduler.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <alloca.h>
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>


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
	FOREACH_thiscpu_threads(thread, LOCAL_cpu) {
		if (thread != idle) {
			temp = (*cb)(arg, thread);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
	}

#ifndef CONFIG_NO_SMP
	/* Now go through all of the pending threads. */
	FOREACH_thiscpu_sched_pending(thread, LOCAL_cpu) {
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
	while (!cpu_sendipi(me, &system_enum_threads_ipi, args,
	                    CPU_IPI_FWAITFOR | CPU_IPI_FWAKEUP)) {
		/* Wait until we can send an IPI */
		task_pause();
	}
	/* Wait for IPI to complete. */
	while (!ATOMIC_LOAD(completed))
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
	uintptr_t old_flags = ATOMIC_FETCHOR(caller->t_flags, TASK_FKEEPCORE);
	struct cpu *mycpu   = ATOMIC_READ(caller->t_cpu);
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
		ATOMIC_AND(caller->t_flags, ~TASK_FKEEPCORE);
	return result;
}

/* Enumerate threads hosted by `me' */
PUBLIC NOBLOCK NONNULL((1, 3)) ssize_t
NOTHROW(FCALL system_enum_threads_cpu_nb)(system_enum_threads_cb_t cb, void *arg,
                                          struct cpu *__restrict me) {
	ssize_t result;
	struct task *caller = THIS_TASK;
	uintptr_t old_flags = ATOMIC_FETCHOR(caller->t_flags, TASK_FKEEPCORE);
	struct cpu *mycpu   = ATOMIC_READ(caller->t_cpu);
	/* Enumerate the given CPU */
	result = system_enum_cputhreads_nb(cb, arg, me, mycpu);
	if (!(old_flags & TASK_FKEEPCORE))
		ATOMIC_AND(caller->t_flags, ~TASK_FKEEPCORE);
	return result;
}
#endif /* !CONFIG_NO_SMP */



#ifndef CONFIG_USE_NEW_GROUP
#define ASSERT_POISON(expr) assert((expr) || kernel_poisoned())

#define DO(expr)            do { if ((temp = (expr)) < 0) goto err; result += temp; } __WHILE0
#define CB(task_, taskpid_) DO((*cb)(arg, task_, taskpid_))
#define CB_THREAD(task_)    CB(task_, FORTASK(task_, this_taskpid))


PRIVATE NOBLOCK NONNULL((1, 3)) ssize_t
NOTHROW(FCALL task_enum_mycpu_nb)(task_enum_cb_t cb, void *arg,
                                  struct cpu *__restrict c) {
	ssize_t temp, result;
	struct task *thread, *idle;
	/* Start out by enumerating our IDLE thread. */
	idle   = &FORCPU(c, thiscpu_idle);
	result = (*cb)(arg, idle, FORTASK(idle, this_taskpid));
	if unlikely(result < 0)
		goto done;

	/* Now walk the running-thread-loop */
	FOREACH_thiscpu_threads(thread, c) {
		if (thread != idle)
			CB_THREAD(thread);
	}

#ifndef CONFIG_NO_SMP
	/* Now go through all of the pending threads. */
	FOREACH_thiscpu_sched_pending(thread, c) {
		ASSERT_POISON(thread != idle);
		CB_THREAD(thread);
	}
#endif /* !CONFIG_NO_SMP */
done:
	return result;
err:
	return temp;
}

#ifndef CONFIG_NO_SMP
#if CPU_IPI_ARGCOUNT < 4
#error "Need at least 4 IPI pointers!"
#endif /* CPU_IPI_ARGCOUNT < 4 */
PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) /*ATTR_NOTHROW*/ struct icpustate *
NOTHROW(FCALL task_enum_cpu_ipi)(struct icpustate *__restrict state, void *args[CPU_IPI_ARGCOUNT]) {
	task_enum_cb_t cb;
	void *cb_arg;
	ssize_t *presult;
	cb       = (task_enum_cb_t)args[0];
	cb_arg   = args[1];
	presult  = (ssize_t *)args[2];
	*presult = task_enum_mycpu_nb(cb, cb_arg, THIS_CPU);
	COMPILER_BARRIER();
	*(bool *)args[3] = true; /* Indicate callback completion. */
	COMPILER_BARRIER();
	return state;
}
#endif /* !CONFIG_NO_SMP */


/* Enumerate all threads  running, sleeping, or  pending on  `c'
 * Threads that have terminated, or haven't been started are not
 * enumerated by this function. */
PUBLIC NOBLOCK NONNULL((1, 3)) ssize_t
NOTHROW(FCALL task_enum_cpu_nb)(task_enum_cb_t cb, void *arg,
                                struct cpu *__restrict c) {
	ssize_t result;
#ifdef CONFIG_NO_SMP
	result = task_enum_mycpu_nb(cb, arg, c);
#else /* CONFIG_NO_SMP */
	uintptr_t old_flags;
#ifdef CONFIG_HAVE_DEBUGGER
	/* Don't need any of this IPI stuff when already in debugger-mode! */
	if (dbg_active)
		return task_enum_mycpu_nb(cb, arg, c);
#endif /* CONFIG_HAVE_DEBUGGER */
	old_flags = ATOMIC_FETCHOR(THIS_TASK->t_flags, TASK_FKEEPCORE);
	if (c == THIS_CPU) {
		result = task_enum_mycpu_nb(cb, arg, c);
		if (!(old_flags & TASK_FKEEPCORE))
			ATOMIC_AND(THIS_TASK->t_flags, ~TASK_FKEEPCORE);
	} else {
		if (!(old_flags & TASK_FKEEPCORE))
			ATOMIC_AND(THIS_TASK->t_flags, ~TASK_FKEEPCORE);
		if (!cpu_isrunning(c)) {
cpu_not_running:
			/* The CPU only contains a single thread: it's IDLE thread. */
			result = (*cb)(arg, &FORCPU(c, thiscpu_idle), FORTASK(&FORCPU(c, thiscpu_idle), this_taskpid));
		} else {
			void *args[CPU_IPI_ARGCOUNT];
			bool completed = false;
			args[0] = (void *)cb;
			args[1] = arg;
			args[2] = (void *)&result;
			args[3] = &completed;
			while (!cpu_sendipi(c, &task_enum_cpu_ipi, args, CPU_IPI_FWAITFOR)) {
				if (!cpu_isrunning(c))
					goto cpu_not_running;
				/* Wait until we can send the IPI */
				task_pause();
			}
			/* Wait for the IPI to complete. */
			while (!ATOMIC_LOAD(completed))
				task_pause();
			/* Done! */
		}
	}
#endif /* !CONFIG_NO_SMP */
	return result;
}



/* Enumerate  all  threads  found  anywhere  on  the  system.
 * This is the same as calling `task_enum_cpu()' for all CPUs */
PUBLIC NOBLOCK NONNULL((1)) ssize_t
NOTHROW(FCALL task_enum_all_nb)(task_enum_cb_t cb, void *arg) {
	ssize_t result;
#ifdef CONFIG_NO_SMP
	result = task_enum_cpu_nb(cb, arg, &bootcpu);
#else /* CONFIG_NO_SMP */
	ssize_t temp;
	unsigned int i;
	result = 0;
	/* TODO: This is flawed -- We might miss threads if they get moved between CPUs! */
	for (i = 0; i < cpu_count; ++i) {
		temp = task_enum_cpu_nb(cb, arg, cpu_vector[i]);
		if unlikely(temp < 0)
			return temp;
		result += temp;
	}
#endif /* !CONFIG_NO_SMP */
	return result;
}



struct task_enum_filter_data {
	task_enum_cb_t ef_cb;  /* [1..1] The underlying callback */
	void          *ef_arg; /* Argument for `ef_cb' */
};

PRIVATE NOBLOCK NONNULL((1, 3)) ssize_t
NOTHROW(TASK_ENUM_CC task_enum_filter_kernel_cb_nb)(void *arg, struct task *thread,
                                                    struct taskpid *__restrict pid) {
	struct task_enum_filter_data *data;
	data = (struct task_enum_filter_data *)arg;
	/* Filter non-kernel threads. */
	if (!thread || (thread->t_flags & TASK_FKERNTHREAD) == 0)
		return 0;
	return (*data->ef_cb)(data->ef_arg, thread, pid);
}

PUBLIC NOBLOCK NONNULL((1)) ssize_t
NOTHROW(FCALL task_enum_kernel_nb)(task_enum_cb_t cb, void *arg) {
	ssize_t result;
	struct task_enum_filter_data data;
	data.ef_cb  = cb;
	data.ef_arg = arg;
	/* Enumerate all threads, but filter anything that isn't a kernel thread. */
	result = task_enum_all_nb(&task_enum_filter_kernel_cb_nb, &data);
	return result;
}


struct task_enum_filter_proc_data {
	task_enum_cb_t  efp_cb;   /* [1..1] The underlying callback. */
	void           *efp_arg;  /* Argument for `ef_cb'. */
	struct task    *efp_proc; /* [1..1] The process, who's thread shall be filtered. */
};

PRIVATE NOBLOCK NONNULL((1, 3)) ssize_t
NOTHROW(TASK_ENUM_CC task_enum_filter_proc_cb_nb)(void *arg, struct task *thread,
                                                  struct taskpid *__restrict pid) {
	struct task_enum_filter_proc_data *data;
	data = (struct task_enum_filter_proc_data *)arg;
	if (!thread ||
	    task_getprocess_of(thread) != data->efp_proc ||
	    thread == data->efp_proc)
		return 0;
	return (*data->efp_cb)(data->efp_arg, thread, pid);
}


/* Enumerate all  threads  apart  of the  same  process  as  `proc'
 * If `proc' is a kernel-space thread, same as `task_enum_kernel()' */
PUBLIC NOBLOCK NONNULL((1, 3)) ssize_t
NOTHROW(FCALL task_enum_proc_thrds_nb)(task_enum_cb_t cb, void *arg,
                                       struct task *__restrict proc) {
	ssize_t temp, result;
	struct taskgroup *group;
	struct taskpid *tpid;
	/* Retrieve the process leader of `proc' */
	proc = task_getprocess_of(proc);

	/* Check for special case: this is a kernel thread.
	 * In this case, we must enumerate all system-wide kernel threads. */
	if unlikely(proc->t_flags & TASK_FKERNTHREAD)
		return task_enum_kernel_nb(cb, arg);

	/* Enumerate the process leader. */
	result = (*cb)(arg, proc, FORTASK(proc, this_taskpid));
	if unlikely(result < 0)
		goto done;

	/* Lock the process's thread list. */
	group = &FORTASK(proc, this_taskgroup);
	if (sync_tryread(&group->tg_proc_threads_lock)) {
		/* Enumerate threads. */
		FOREACH_taskgroup__proc_threads(tpid, group) {
			REF struct task *thread;
			thread = taskpid_gettask(tpid);
			if (!thread)
				continue;
			/* Only enumerate threads. - Don't enumerate child processes. */
			temp = task_getprocess_of(thread) == proc
			       ? (*cb)(arg, thread, tpid)
			       : 0;
			decref_unlikely(thread);
			if unlikely(temp < 0) {
				sync_endread(&group->tg_proc_threads_lock);
				goto err;
			}
			result += temp;
		}
		sync_endread(&group->tg_proc_threads_lock);
	} else {
		/* Enumerate all threads, and filter by
		 * `thread != proc && task_getprocess_of(thread) == proc' */
		struct task_enum_filter_proc_data data;
		data.efp_cb   = cb;
		data.efp_arg  = arg;
		data.efp_proc = proc;
		temp = task_enum_all_nb(&task_enum_filter_proc_cb_nb, &data);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
done:
	return result;
err:
	return temp;
}
#endif /* !CONFIG_USE_NEW_GROUP */

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_ENUM_C */
