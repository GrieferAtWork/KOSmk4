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
#ifndef GUARD_KERNEL_SRC_SCHED_CPU_C
#define GUARD_KERNEL_SRC_SCHED_CPU_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h> /* CONFIG_HAVE_DEBUGGER */
#include <kernel/debugtrap.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/vm.h>
#include <sched/cpu.h>
#include <sched/pid.h>
#include <sched/rpc.h>
#include <sched/scheduler.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <bits/os/timespec.h>
#include <sys/wait.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

#ifdef CONFIG_HAVE_DEBUGGER
#include <debugger/rt.h> /* dbg_active */
#endif /* CONFIG_HAVE_DEBUGGER */

DECL_BEGIN

#ifdef __HAVE_CPUSET_FULL_MASK
PUBLIC cpuset_t ___cpuset_full_mask ASMNAME("__cpuset_full_mask") = 1;
#endif /* __HAVE_CPUSET_FULL_MASK */


/* [!0][<= CONFIG_MAX_CPU_COUNT][const] The total number of known CPUs. */
PUBLIC unsigned int cpu_count_ ASMNAME("cpu_count") = 1;
#ifndef CONFIG_NO_SMP
PUBLIC unsigned int cpu_online_count = 1;
#endif /* !CONFIG_NO_SMP */

/* [1..1][cpu_count] Vector of CPU descriptors.
 * NOTE: The index in this vector is the `cpu_id' of the associated CPU.
 * NOTE: `_bootcpu' always has the CPUID ZERO(0) */
PUBLIC struct cpu *_cpu_vector[CONFIG_MAX_CPU_COUNT] ASMNAME("cpu_vector") = { &_bootcpu };


PRIVATE ATTR_USED ATTR_SECTION(".data.percpu.head")
struct cpu cpu_header = {
	/* .c_id       = */ 0,
	/* .c_state    = */ CPU_STATE_RUNNING,
#if ((__SIZEOF_INT__ + 2) % __SIZEOF_POINTER__) != 0
	/* ._c_pad     = */ { 0, },
#endif /* ((__SIZEOF_INT__ + 2) % __SIZEOF_POINTER__) != 0 */
#ifndef CONFIG_NO_SMP
	/* .c_pdir     = */ pagedir_kernel_phys
#endif /* !CONFIG_NO_SMP */
};



typedef void /*NOTHROW*/ (KCALL *pertask_onexit_t)(void);
INTDEF pertask_onexit_t __kernel_pertask_onexit_start[];
INTDEF pertask_onexit_t __kernel_pertask_onexit_end[];


PRIVATE NOBLOCK WUNUSED NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL task_decref_for_exit)(void *arg,
                                    struct icpustate *__restrict state,
                                    unsigned int UNUSED(reason),
                                    struct rpc_syscall_info const *UNUSED(sc_info)) {
	decref((struct task *)arg);
	return state;
}

PRIVATE ATTR_KERNEL_PANIC_NORETURN ATTR_COLD ATTR_NOINLINE void
NOTHROW(FCALL panic_critical_thread_exited)(void) {
	struct task *me = THIS_TASK;
	kernel_panic("Critical thread at %p has exited", me);
}

/* Terminate the calling thread immediately.
 * WARNING: Do not call this function to terminate a thread.
 *          It would work, but exception handlers would not
 *          get unwound and resources would be leaked.
 *          If you wish to exit your current thread, just
 *          throw an `E_EXIT_THREAD' error instead.
 * This function is called by the unhandled exception handler
 * when it encounters an `E_EXIT_THREAD' error, or when exception
 * data cannot be propagated to userspace in the event of an
 * interrupt throwing some error, whilst originating from user-space.
 * @param: w_status: The task's exit status (mustn't be `WIFSTOPPED()' or `WIFCONTINUED()').
 *                   This argument is ignored for kernel-threads.
 * WARNING: Calling this function from an IDLE task, or any other
 *          task that is critical will cause the kernel to PANIC! */
PUBLIC ATTR_NORETURN void
NOTHROW(FCALL task_exit)(int w_status) {
	struct task *caller = THIS_TASK, *next;
	struct cpu *me;
	struct taskpid *pid = THIS_TASKPID;
	assert(!WIFSTOPPED(w_status));
	assert(!WIFCONTINUED(w_status));
	assertf(PREEMPTION_ENABLED(),
	        "Without preemption, how do you want to switch tasks?");
	assert(caller->t_flags & TASK_FRUNNING);
	if unlikely(caller->t_flags & TASK_FCRITICAL) {
		panic_critical_thread_exited();
		ATOMIC_AND(caller->t_flags, ~TASK_FCRITICAL);
	}
	/* Fill in the exit status */
	if (pid)
		ATOMIC_WRITE(pid->tp_status.w_status, w_status);

	/* Set the bit to indicate that we've started termination. */
	if (!(ATOMIC_FETCHOR(caller->t_flags, TASK_FTERMINATING) & TASK_FTERMINATING)) {
		pertask_onexit_t *iter;
		printk(KERN_TRACE "[sched] Exiting thread %p\n", caller);

		/* Trigger the appropriate debug trap associated with thread/process exits.
		 * This is required because otherwise GDB will sooner or later hang itself
		 * when waiting for the exited-notification of a terminated thread once it's
		 * no longer able to find the thread apart of thread listings.
		 * s.a. /kos/misc/gdbridge/gdbride.dee
		 */
		if (kernel_debugtrap_enabled() && pid) {
			struct debugtrap_reason reason;
			reason.dtr_reason = task_isprocessleader_p(caller)
			                    ? DEBUGTRAP_REASON_PEXITED
			                    : DEBUGTRAP_REASON_TEXITED;
			reason.dtr_signo  = w_status;
			reason.dtr_ptrarg = caller;
			kernel_debugtrap(&reason);
		}

		/* Invoke cleanup callbacks. */
		iter = __kernel_pertask_onexit_start;
		for (; iter < __kernel_pertask_onexit_end; ++iter)
			(**iter)();
	}

	PREEMPTION_DISABLE();
	me = caller->t_cpu;
	assertf(FORCPU(me, thiscpu_sched_current) == caller, "Inconsistent scheduler state");
	assertf(FORCPU(me, thiscpu_sched_override) != caller, "Cannot exit while being the scheduling override");
	assertf(caller != &FORCPU(me, thiscpu_idle), "The IDLE task cannot be terminated");

	/* Account for timings and scheduler internals, as well as figure out a successor thread. */
	next = sched_intern_yield_onexit(me, caller); /* NOTE: This causes us to inherit a reference to `caller' */
	FORCPU(me, thiscpu_sched_current) = next;

	/* Hi-jack the execution stack of the next thread to have it do the decref()
	 * of our own thread, thus preventing the undefined behavior that would be
	 * caused if we tried to decref (and possibly destroy) ourself.
	 *
	 * NOTE: The reference destroyed here was gifted to us by `sched_intern_yield_onexit()' */
	{
		struct scpustate *state;
		state = FORTASK(next, this_sstate);
		state = task_push_asynchronous_rpc(state,
		                                   &task_decref_for_exit,
		                                   caller);
		FORTASK(next, this_sstate) = state;
	}

	/* Update our thread's status flags. */
	{
		uintptr_t old_flags;
		uintptr_t new_flags;
		do {
			/* Set the flag to indicate that we've been fully terminated.
			 * NOTE: Also ensure that a couple of other flags are set/cleared correctly,
			 *       though most of these flags should already have the proper status */
			enum {
				set = (/* Set the terminated flags */
				       TASK_FTERMINATING | TASK_FTERMINATED |
				       /* Ensure that the thread's status indicates that it was (once) started */
				       TASK_FSTARTED | TASK_FSTARTING |
				       /* Once dead, there'd be no point in being moved to a different core */
				       TASK_FKEEPCORE |
				       0),
				del = (/* We're no longer running */
				       TASK_FRUNNING |
				       /* If we were running in vfork()-mode, clear the
				        * VFORK flag to wake up our waiting parent thread. */
				       TASK_FVFORK |
				       /* This flag really shouldn't be set, so clearing simply ensures
				        * some consistency */
				       TASK_FTIMEOUT |
				       /* Once dead, we can no longer be resumed (so we're also no longer suspended) */
				       TASK_FSUSPENDED | TASK_FGDB_STOPPED |
				       0)
			};
			old_flags = ATOMIC_READ(caller->t_flags);
			new_flags = old_flags;
			/* While this was already checked for above, some other thread may have set this
			 * flag in the mean time (though doing something like that would be really bad
			 * practice). In any case: properly handle the CRITICAL-flag until the very end,
			 * so that other code can guaranty that setting the flag at any point when the
			 * TERMINATED flag hasn't also been set will cause an intentional kernel panic. */
			if unlikely(new_flags & TASK_FCRITICAL)
				panic_critical_thread_exited();
			new_flags |= set;
			new_flags &= ~del;
		} while (!ATOMIC_CMPXCH_WEAK(caller->t_flags,
		                             old_flags,
		                             new_flags));
	}

	/* Broadcast the status-changed signal _after_ setting `TASK_FTERMINATED'
	 * That way, other thread can use `tp_changed' alongside `TASK_FTERMINATED'
	 * in order to wait for the thread to fully terminate. If we were to broadcast
	 * `tp_changed' before setting the flag, then even though we've got interrupts
	 * disabled, another CPU may receive the `tp_changed' signal and read the flags
	 * field not containing `TASK_FTERMINATED' yet before we've set the flag, causing
	 * it to end up soft-locked (as in: CTRL+C would still work), waiting for the
	 * thread to terminate when in fact it already has terminated.
	 * However, we must fill in the exit status _before_ setting `TASK_FTERMINATED',
	 * such that another thread waiting for us to terminate knows that once `TASK_FTERMINATED'
	 * has been set, the thread's pid's `tp_status' field contains its final exit status.
	 * Thus, the terminate-flag acts as an interlocked check for the exit status and
	 * waiting for the status to change during thread exit. */
	if (pid) {
		/* Important! Must broadcast the change while impersonating `next'!
		 *
		 * Our current thread context is already too broken to allow us to
		 * re-schedule others threads that may be waiting for us to exit. */
		sig_broadcast_as_nopr(&pid->tp_changed, next);
	}

	/* Good bye... */
	cpu_run_current_nopr();
}




PUBLIC ATTR_NORETURN void
NOTHROW(FCALL cpu_idlemain)(void) {
	for (;;) {
		/* TODO: sync() (`superblock_syncall()') superblocks.
		 * NOTE: Should only happen after some delay (e.g. 2 seconds)
		 *       since the last write operation, or since IDLE began. */

		/* TODO: Do IDLE jobs, such as cleaning up memory. */
		/* TODO: Based on the current power profile, wait for different length's
		 *       of periods before entering deep sleep mode (in high performance
		 *       mode, never enter deep sleep mode. - Only `hlt' normally). */

		cpu_deepsleep();
	}
}



/* Optional functions to schedule / delete jobs that should be executed
 * by the current CPU's IDLE thread the next time there is nothing to do.
 * NOTE: These functions should be used for the purposes of _HINTS_ _ONLY_!
 *       The kernel is not actually required to implement them, and when
 *       defined as no-ops that simply return `false', kernel operations
 *       must be the same as otherwise!
 * `cpu_schedule_idle_job_and_incref' is the same as `cpu_schedule_idle_job()',
 * but if the request succeeds (return == true), atomically increment a `refcnt_t'
 * field found at `arg + refcnt_offset', thus allowing the job-function to take
 * a reference to some object with which to work.
 * @param: job:    The job to perform.
 * @param: arg:    The argument to pass to `job' when it should be executed.
 * @return: true:  Successfully scheduled the job for execution.
 *                 In this case, it is guarantied that the job will either be executed, or canceled.
 * @return: false: Failed to allocate memory for the job, or there are already too many jobs.
 * @return: false: Another IDLE job with the same `job' and `arg' had already been scheduled.
 * @return: false: The kernel has been configured to disable IDLE jobs. */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL cpu_schedule_idle_job)(idle_job_t job, void *arg) {
	(void)job;
	(void)arg;
	/* TODO */
	COMPILER_IMPURE();
	return false;
}

PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL cpu_schedule_idle_job_and_incref)(idle_job_t job, void *arg,
                                                ptrdiff_t refcnt_offset) {
	(void)job;
	(void)arg;
	(void)refcnt_offset;
	/* TODO */
	COMPILER_IMPURE();
	return false;
}

/* Delete a previously schedule IDLE job before it can be serviced.
 * @return: true:  The job was unscheduled, and invoked with `IDLE_JOB_MODE_CANCEL'
 * @return: false: Either the job was never scheduled, or has already been serviced
 *                 when the CPU had some down-time between now and a prior call to
 *                `cpu_schedule_idle_job*()' */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL cpu_delete_idle_job)(idle_job_t job, void *arg) {
	(void)job;
	(void)arg;
	/* TODO */
	COMPILER_IMPURE();
	return false;
}



PRIVATE NOBLOCK void
NOTHROW(FCALL invoke_simple_idle_job)(void *arg, unsigned int mode) {
	if (mode == IDLE_JOB_MODE_SERVICE)
		(*(NOBLOCK void /*NOTHROW*/ (KCALL *)(void))arg)();
}

PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL cpu_schedule_idle_job_simple)(NOBLOCK void /*NOTHROW*/ (KCALL *func)(void)) {
	return cpu_schedule_idle_job(&invoke_simple_idle_job, (void *)func);
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_CPU_C */
