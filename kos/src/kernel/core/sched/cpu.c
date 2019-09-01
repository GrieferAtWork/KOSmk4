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
#ifndef GUARD_KERNEL_SRC_SCHED_CPU_C
#define GUARD_KERNEL_SRC_SCHED_CPU_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/printk.h>
#include <kernel/types.h>
#include <sched/cpu.h>
#include <sched/pid.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <kos/jiffies.h>
#include <sys/wait.h>

#include <bits/timespec.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>


#include <sys/io.h>

DECL_BEGIN


#ifdef __HAVE_CPUSET_FULL_MASK
PUBLIC cpuset_t ___cpuset_full_mask ASMNAME("__cpuset_full_mask") = 1;
#endif


/* [!0][<= CONFIG_MAX_CPU_COUNT][const] The total number of known CPUs. */
PUBLIC cpuid_t _cpu_count ASMNAME("cpu_count") = 1;
#ifndef CONFIG_NO_SMP
PUBLIC cpuid_t cpu_online_count = 1;
#endif /* !CONFIG_NO_SMP */

/* [1..1][cpu_count] Vector of CPU descriptors.
 * NOTE: The index in this vector is the `cpu_id' of the associated CPU.
 * NOTE: `_bootcpu' always has the CPUID ZERO(0) */
PUBLIC struct cpu *_cpu_vector[CONFIG_MAX_CPU_COUNT] ASMNAME("cpu_vector") = { &_bootcpu };


INTDEF byte_t __kernel_percpu_size[];

PRIVATE ATTR_USED ATTR_SECTION(".data.percpu.head")
struct cpu cpu_header = {
	/*.c_id       = */0,
	/*.c_current  = */NULL,
	/*.c_sleeping = */NULL,
#ifndef CONFIG_NO_SMP
	/*.c_pending  = */CPU_PENDING_ENDOFCHAIN,
#endif /* !CONFIG_NO_SMP */
	/*.c_heapsize = */(size_t)__kernel_percpu_size,
	/*.c_state    = */CPU_STATE_RUNNING
};

PUBLIC ATTR_PERCPU jtime_t volatile cpu_jiffies = 0;
PUBLIC ATTR_PERCPU quantum_diff_t volatile cpu_quantum_offset = 0;
PUBLIC ATTR_PERCPU quantum_diff_t volatile cpu_quantum_length = (quantum_diff_t)-1;


/* Weakly implement preemptive interrupt disabling as no-ops. */
PUBLIC ATTR_WEAK NOBLOCK ATTR_SECTION(".text.kernel.cpu_disable_preemptive_interrupts") void
NOTHROW(KCALL cpu_disable_preemptive_interrupts)(void) {
}
DEFINE_PUBLIC_WEAK_ALIAS(cpu_enable_preemptive_interrupts,cpu_disable_preemptive_interrupts);
DEFINE_PUBLIC_WEAK_ALIAS(cpu_quantum_reset,cpu_disable_preemptive_interrupts);

PUBLIC NOBLOCK ATTR_WEAK WUNUSED ATTR_SECTION(".text.kernel.cpu_quantum_elapsed")
quantum_diff_t NOTHROW(KCALL cpu_quantum_elapsed)(void) {
	return 0;
}
PUBLIC NOBLOCK ATTR_WEAK WUNUSED ATTR_SECTION(".text.kernel.cpu_quantum_remaining")
quantum_diff_t NOTHROW(KCALL cpu_quantum_remaining)(void) {
	return (quantum_diff_t)-1;
}
DEFINE_PUBLIC_WEAK_ALIAS(cpu_quantum_elapsed_nopr, cpu_quantum_elapsed);
DEFINE_PUBLIC_WEAK_ALIAS(cpu_quantum_remaining_nopr, cpu_quantum_remaining);


PUBLIC NOBLOCK WUNUSED qtime_t
NOTHROW(KCALL cpu_quantum_time)(void) {
	qtime_t result;
	struct cpu *me;
	pflag_t was;
	quantum_diff_t elapsed;
	was = PREEMPTION_PUSHOFF();
	me             = THIS_CPU;
	result.q_jtime = FORCPU(me, cpu_jiffies);
	result.q_qtime = FORCPU(me, cpu_quantum_offset);
	result.q_qsize = FORCPU(me, cpu_quantum_length);
	elapsed        = cpu_quantum_elapsed_nopr();
	PREEMPTION_POP(was);
	if (OVERFLOW_UADD(result.q_qtime, elapsed, &result.q_qtime)) {
		result.q_jtime += ((quantum_diff_t)-1) / result.q_qsize;
		result.q_qtime += elapsed;
		result.q_qtime -= (quantum_diff_t)-1;
	}
	if (result.q_qtime >= result.q_qsize) {
		result.q_jtime += result.q_qtime / result.q_qsize;
		result.q_qtime = result.q_qtime % result.q_qsize;
	}
	return result;
}

PUBLIC NOBLOCK WUNUSED qtime_t
NOTHROW(KCALL quantum_time)(void) {
	qtime_t result;
	struct cpu *me;
	pflag_t was;
	quantum_diff_t elapsed, my_qoff, my_qlen;
	/* BOOT_JIFFIES + (BOOT_QUANTUM_OFFSET - MY_QUANTUM_OFFSET + cpu_quantum_elapsed()) */
	was = PREEMPTION_PUSHOFF();
	me             = THIS_CPU;
	result.q_jtime = FORCPU(&_bootcpu, cpu_jiffies);
	result.q_qtime = FORCPU(&_bootcpu, cpu_quantum_offset);
	result.q_qsize = FORCPU(&_bootcpu, cpu_quantum_length);
	my_qoff        = FORCPU(me, cpu_quantum_offset);
	my_qlen        = FORCPU(me, cpu_quantum_length);
	elapsed        = cpu_quantum_elapsed_nopr();
	PREEMPTION_POP(was);
	if (my_qlen > result.q_qsize) {
		result.q_qtime = (quantum_diff_t)(((u64)result.q_qtime * result.q_qsize) / my_qlen);
		result.q_qsize = my_qlen;
	} else if (my_qlen < result.q_qsize) {
		my_qoff = (quantum_diff_t)(((u64)my_qoff * my_qlen) / result.q_qsize);
		elapsed = (quantum_diff_t)(((u64)elapsed * my_qlen) / result.q_qsize);
	}

	if (OVERFLOW_UADD(result.q_qtime, elapsed, &result.q_qtime)) {
		result.q_jtime += ((quantum_diff_t)-1) / result.q_qsize;
		result.q_qtime += elapsed;
		result.q_qtime -= (quantum_diff_t)-1;
	}
	if (OVERFLOW_USUB(result.q_qtime, my_qoff, &result.q_qtime)) {
		result.q_jtime -= ((quantum_diff_t)-1) / result.q_qsize;
		result.q_qtime -= my_qoff;
		result.q_qtime += (quantum_diff_t)-1;
	}
	if (result.q_qtime >= result.q_qsize) {
		result.q_jtime += result.q_qtime / result.q_qsize;
		result.q_qtime = result.q_qtime % result.q_qsize;
	}
	return result;
}

PUBLIC NOBLOCK NONNULL((1)) qtime_t
NOTHROW(FCALL quantum_local_to_global)(qtime_t *__restrict tmp) {
	qtime_t boot_time, locl_time;
	struct cpu *me = THIS_CPU;
	quantum_diff_t elapsed;
	locl_time.q_jtime = FORCPU(me, cpu_jiffies);
	locl_time.q_qtime = FORCPU(me, cpu_quantum_offset);
	locl_time.q_qsize = FORCPU(me, cpu_quantum_length);
	elapsed           = cpu_quantum_elapsed_nopr();
	if (OVERFLOW_UADD(locl_time.q_qtime, elapsed, &locl_time.q_qtime)) {
		locl_time.q_jtime += ((quantum_diff_t)-1) / locl_time.q_qsize;
		locl_time.q_qtime += elapsed;
		locl_time.q_qtime -= (quantum_diff_t)-1;
	}
	if (me == &_bootcpu)
		return locl_time;
	boot_time.q_jtime = FORCPU(&_bootcpu, cpu_jiffies);
	boot_time.q_qtime = FORCPU(&_bootcpu, cpu_quantum_offset);
	boot_time.q_qsize = FORCPU(&_bootcpu, cpu_quantum_length);
	if (locl_time.q_qtime >= locl_time.q_qsize) {
		locl_time.q_jtime += locl_time.q_qtime / locl_time.q_qsize;
		locl_time.q_qtime = locl_time.q_qtime % locl_time.q_qsize;
	}
	if (locl_time.q_qsize < boot_time.q_qsize) {
		locl_time.q_qtime = (locl_time.q_qtime * boot_time.q_qsize) / locl_time.q_qsize;
		locl_time.q_qsize = boot_time.q_qsize;
	} else if (locl_time.q_qsize > boot_time.q_qsize) {
		boot_time.q_qtime = (boot_time.q_qtime * locl_time.q_qsize) / boot_time.q_qsize;
		boot_time.q_qsize = locl_time.q_qsize;
	}
	if (tmp->q_qsize < boot_time.q_qsize) {
		tmp->q_qtime = (tmp->q_qtime * boot_time.q_qsize) / tmp->q_qsize;
		tmp->q_qsize = boot_time.q_qsize;
	} else if (tmp->q_qsize > boot_time.q_qsize) {
		boot_time.q_qtime = (boot_time.q_qtime * tmp->q_qsize) / boot_time.q_qsize;
		boot_time.q_qsize = tmp->q_qsize;
		locl_time.q_qtime = (locl_time.q_qtime * tmp->q_qsize) / locl_time.q_qsize;
		locl_time.q_qsize = tmp->q_qsize;
	}
	/* TMP = (TMP - LOCAL) + BOOT */
	tmp->q_jtime -= locl_time.q_jtime;
	tmp->q_jtime += boot_time.q_jtime;
	if (OVERFLOW_USUB(tmp->q_qtime, locl_time.q_qtime, &tmp->q_qtime)) {
		tmp->q_jtime -= ((quantum_diff_t)-1 / tmp->q_qsize);
		tmp->q_qtime += (quantum_diff_t)-1;
		tmp->q_qtime -= locl_time.q_qtime;
	}
	if (OVERFLOW_UADD(tmp->q_qtime, boot_time.q_qtime, &tmp->q_qtime)) {
		tmp->q_jtime += ((quantum_diff_t)-1 / tmp->q_qsize);
		tmp->q_qtime -= (quantum_diff_t)-1;
		tmp->q_qtime += boot_time.q_qtime;
	}
	if (tmp->q_qtime >= tmp->q_qsize) {
		tmp->q_jtime += tmp->q_qtime / tmp->q_qsize;
		tmp->q_qtime = tmp->q_qtime % tmp->q_qsize;
	}
	return boot_time;
}

PUBLIC NOBLOCK NONNULL((1)) qtime_t
NOTHROW(FCALL quantum_global_to_local)(qtime_t *__restrict tmp) {
	qtime_t boot_time, locl_time;
	struct cpu *me = THIS_CPU;
	quantum_diff_t elapsed;
	locl_time.q_jtime = FORCPU(me, cpu_jiffies);
	locl_time.q_qtime = FORCPU(me, cpu_quantum_offset);
	locl_time.q_qsize = FORCPU(me, cpu_quantum_length);
	elapsed = cpu_quantum_elapsed_nopr();
	if (OVERFLOW_UADD(locl_time.q_qtime, elapsed, &locl_time.q_qtime)) {
		locl_time.q_jtime += ((quantum_diff_t)-1) / locl_time.q_qsize;
		locl_time.q_qtime += elapsed;
		locl_time.q_qtime -= (quantum_diff_t)-1;
	}
	if (me == &_bootcpu)
		return locl_time;
	boot_time.q_jtime = FORCPU(&_bootcpu, cpu_jiffies);
	boot_time.q_qtime = FORCPU(&_bootcpu, cpu_quantum_offset);
	boot_time.q_qsize = FORCPU(&_bootcpu, cpu_quantum_length);
	if (locl_time.q_qtime >= locl_time.q_qsize) {
		locl_time.q_jtime += locl_time.q_qtime / locl_time.q_qsize;
		locl_time.q_qtime = locl_time.q_qtime % locl_time.q_qsize;
	}
	if (locl_time.q_qsize < boot_time.q_qsize) {
		locl_time.q_qtime = (locl_time.q_qtime * boot_time.q_qsize) / locl_time.q_qsize;
		locl_time.q_qsize = boot_time.q_qsize;
	} else if (locl_time.q_qsize > boot_time.q_qsize) {
		boot_time.q_qtime = (boot_time.q_qtime * locl_time.q_qsize) / boot_time.q_qsize;
		boot_time.q_qsize = locl_time.q_qsize;
	}
	if (tmp->q_qsize < boot_time.q_qsize) {
		tmp->q_qtime = (tmp->q_qtime * boot_time.q_qsize) / tmp->q_qsize;
		tmp->q_qsize = boot_time.q_qsize;
	} else if (tmp->q_qsize > boot_time.q_qsize) {
		boot_time.q_qtime = (boot_time.q_qtime * tmp->q_qsize) / boot_time.q_qsize;
		boot_time.q_qsize = tmp->q_qsize;
		locl_time.q_qtime = (locl_time.q_qtime * tmp->q_qsize) / locl_time.q_qsize;
		locl_time.q_qsize = tmp->q_qsize;
	}
	/* TMP = (TMP - BOOT) + LOCAL */
	tmp->q_jtime -= boot_time.q_jtime;
	tmp->q_jtime += locl_time.q_jtime;
	if (OVERFLOW_USUB(tmp->q_qtime, boot_time.q_qtime, &tmp->q_qtime)) {
		tmp->q_jtime -= ((quantum_diff_t)-1 / tmp->q_qsize);
		tmp->q_qtime += (quantum_diff_t)-1;
		tmp->q_qtime -= boot_time.q_qtime;
	}
	if (OVERFLOW_UADD(tmp->q_qtime, locl_time.q_qtime, &tmp->q_qtime)) {
		tmp->q_jtime += ((quantum_diff_t)-1 / tmp->q_qsize);
		tmp->q_qtime -= (quantum_diff_t)-1;
		tmp->q_qtime += locl_time.q_qtime;
	}
	if (tmp->q_qtime >= tmp->q_qsize) {
		tmp->q_jtime += tmp->q_qtime / tmp->q_qsize;
		tmp->q_qtime = tmp->q_qtime % tmp->q_qsize;
	}
	return locl_time;
}




/* Increment `cpu_quantum_offset' by `diff' incrementing the `cpu_jiffies' counter
 * when the resulting value turns out to be greater than `cpu_quantum_length',
 * in which case the value will also be truncated.
 * When `cpu_jiffies' is incremented, also check if this causes additional
 * tasks to time out, and if so, re-schedule them for execution. */
PUBLIC NOBLOCK quantum_diff_t
NOTHROW(FCALL cpu_add_quantum_offset)(quantum_diff_t diff) {
	struct cpu *me = THIS_CPU;
	quantum_diff_t new_diff, more_jiffies = 0;
	quantum_diff_t length = FORCPU(me, cpu_quantum_length);
	assert(!PREEMPTION_ENABLED());
	if (OVERFLOW_UADD(FORCPU(me, cpu_quantum_offset), diff, &new_diff)) {
		more_jiffies = ((quantum_diff_t)-1 / length);
		new_diff     = (FORCPU(me, cpu_quantum_offset) + diff) - ((quantum_diff_t)-1);
	}
	if (new_diff >= length) {
		more_jiffies += new_diff / length;
		new_diff = new_diff % length;
	}
	FORCPU(me, cpu_quantum_offset) = new_diff;
	if (more_jiffies) {
		struct task *sleeper, *last_sleeper, *next;
		jtime_t new_jiffies;
		new_jiffies             = FORCPU(me, cpu_jiffies) + more_jiffies;
		FORCPU(me, cpu_jiffies) = new_jiffies;
		if ((sleeper = me->c_sleeping) != NULL) {
			if (sleeper->t_sched.s_asleep.ss_timeout.q_jtime > new_jiffies)
				goto done_wakeup;
			if (((u64)sleeper->t_sched.s_asleep.ss_timeout.q_qtime *
			     sleeper->t_sched.s_asleep.ss_timeout.q_qsize) >
			    ((u64)new_diff * length))
				goto done_wakeup;
			last_sleeper = sleeper;
			ATOMIC_FETCHOR(sleeper->t_flags, TASK_FTIMEOUT | TASK_FRUNNING);
			while ((next = last_sleeper->t_sched.s_asleep.ss_tmonxt) != NULL) {
				STATIC_ASSERT(offsetof(struct task, t_sched.s_running.sr_runprv) !=
				              offsetof(struct task, t_sched.s_asleep.ss_tmonxt));
				if (next->t_sched.s_asleep.ss_timeout.q_jtime > new_jiffies)
					break;
				if (((u64)next->t_sched.s_asleep.ss_timeout.q_qtime *
				     next->t_sched.s_asleep.ss_timeout.q_qsize) >
				    ((u64)new_diff * length))
					break;
				ATOMIC_FETCHOR(next->t_flags, TASK_FTIMEOUT | TASK_FRUNNING);
				last_sleeper->t_sched.s_running.sr_runnxt = next;
				next->t_sched.s_running.sr_runprv         = last_sleeper;
				last_sleeper                              = next;
			}
			me->c_sleeping = next;
			if (next)
				next->t_sched.s_asleep.ss_pself = &me->c_sleeping;
			/* Re-schedule all of the sleepers. */
			next                                       = me->c_current->t_sched.s_running.sr_runnxt;
			sleeper->t_sched.s_running.sr_runprv       = me->c_current;
			last_sleeper->t_sched.s_running.sr_runnxt  = next;
			next->t_sched.s_running.sr_runprv          = last_sleeper;
			me->c_current->t_sched.s_running.sr_runnxt = sleeper;
		}
	}
done_wakeup:
	return length;
}


PUBLIC NOBLOCK void
NOTHROW(KCALL cpu_quantum_end)(void) {
	quantum_diff_t elapsed, length;
	assert(!PREEMPTION_ENABLED());
	elapsed = cpu_quantum_elapsed_nopr();
	cpu_quantum_reset_nopr();
	length = cpu_add_quantum_offset(elapsed);
	THIS_TASK->t_atime.add_quantum(elapsed, length);
}




/* Enter a sleeping state and return once being woken (true),
 * or once the given `abs_timeout' (which must be global) expires (false)
 * WARNING: Even if the caller has disabled preemption prior to the call,
 *          it will be re-enabled once this function returns.
 * NOTE: This function is the bottom-most (and still task-level) API
 *       for conserving CPU cycles using preemption, in that this
 *       function is even used to implement `task_wait()'.
 *       The functions used to implement this one no longer work on tasks, but on CPUs!
 * NOTE: If the thread is transferred to a different CPU while sleeping, a
 *       sporadic wakeup will be triggered, causing `task_sleep()' to return
 *      `true'.
 * The proper way of using this function is as follows:
 * >> while (SHOULD_WAIT()) { // Test some condition for which to wait
 * >>     PREEMPTION_DISABLE();
 * >>     // Test again now that interrupts are disabled
 * >>     // This test is required to prevent a race condition
 * >>     // where the condition is signaled between it being
 * >>     // changed and interrupts being disabled.
 * >>     COMPILER_READ_BARRIER();
 * >>     if (!SHOULD_WAIT()) {
 * >>         PREEMPTION_ENABLE();
 * >>         break;
 * >>     }
 * >>     // Serve RPC functions (when TRUE is returned, preemption was re-enabled)
 * >>     if (task_serve()) continue;
 * >>     // Do the actual sleep.
 * >>     if (!task_sleep(TIMEOUT))
 * >>         return DID_TIME_OUT;
 * >> }
 * >> return WAS_SIGNALED;
 * The sleeping thread should then be woken as follows:
 * >> SET_SHOULD_WAIT(false);
 * >> task_wake(waiting_thread); */
PUBLIC bool NOTHROW(FCALL task_sleep)(qtime_t const *abs_timeout) {
	struct task *me = THIS_TASK;
	struct cpu *mycpu;
	if (abs_timeout) {
		qtime_t now;
		/* Immediately time out. */
		if (!abs_timeout->q_jtime && !abs_timeout->q_qtime)
			return false;
		/* Copy the given timeout with preemption still enabled.
		 * That way, a faulty input pointer can be handled more easily. */
		memcpy(&me->t_sched.s_asleep.ss_timeout,
		       abs_timeout, sizeof(qtime_t));
		COMPILER_READ_BARRIER();
		PREEMPTION_DISABLE();
		/* Adjust the timeout for the local CPU */
		now = quantum_global_to_local(&me->t_sched.s_asleep.ss_timeout);
		/* Check if the given timeout has already expired. */
		if (now >= me->t_sched.s_asleep.ss_timeout) {
			PREEMPTION_ENABLE();
			return false;
		}
	} else {
		me->t_sched.s_asleep.ss_timeout.q_jtime = (jtime_t)-1;
		me->t_sched.s_asleep.ss_timeout.q_qtime = 0;
		me->t_sched.s_asleep.ss_timeout.q_qsize = 1;
		PREEMPTION_DISABLE();
	}
	/* End the current quantum prematurely. */
	cpu_quantum_end();

	mycpu = me->t_cpu;
	/* The caller is the only thread hosted by this cpu. */
	if likely(me->t_sched.s_running.sr_runnxt == me) {
		/* Special case: blocking call made by the IDLE thread. */
		if unlikely(me == &FORCPU(mycpu, _this_idle)) {
			/* Wait for the next interrupt. */
			PREEMPTION_ENABLE_WAIT();
			/* Indicate a sporadic wake-up. */
			return false;
		}
		/* Unschedule the caller, and instead schedule the IDLE thread. */
		FORCPU(mycpu, _this_idle).t_sched.s_running.sr_runprv = &FORCPU(mycpu, _this_idle);
		FORCPU(mycpu, _this_idle).t_sched.s_running.sr_runnxt = &FORCPU(mycpu, _this_idle);
		ATOMIC_FETCHOR(FORCPU(mycpu, _this_idle).t_flags, TASK_FRUNNING);
		mycpu->c_current = &FORCPU(mycpu, _this_idle);
	} else {
		/* Schedule the next task. */
		struct task *prev = me->t_sched.s_running.sr_runprv;
		struct task *next = me->t_sched.s_running.sr_runnxt;
		assert(prev->t_sched.s_running.sr_runnxt == me);
		assert(next->t_sched.s_running.sr_runprv == me);
		assert(prev != me);
		assert(next != me);
		mycpu->c_current = next;
		next->t_sched.s_running.sr_runprv = prev;
		prev->t_sched.s_running.sr_runnxt = next;
	}
	assert(mycpu->c_current->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv == mycpu->c_current);
	assert(mycpu->c_current->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt == mycpu->c_current);
	me->t_sched.s_running.sr_runprv = NULL;
	me->t_sched.s_running.sr_runnxt = NULL;
	assert(me->t_flags & TASK_FRUNNING);
	ATOMIC_FETCHAND(me->t_flags, ~TASK_FRUNNING);

	/* Register the calling task as a sleeper within the CPU. */
	cpu_addsleepingtask(me);

	/* Continue execution in the next thread. */
	cpu_run_current_and_remember(me);

#ifndef NDEBUG
	PREEMPTION_DISABLE();
	assert(THIS_TASK->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv == THIS_TASK);
	assert(THIS_TASK->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt == THIS_TASK);
	PREEMPTION_ENABLE();
#endif /* !NDEBUG */

	/* This is where we get _after_ we've been scheduled again.
	 * for this purpose, check if we timed out. */
	if (ATOMIC_FETCHAND(me->t_flags, ~TASK_FTIMEOUT) & TASK_FTIMEOUT)
		return false; /* Timeout... */
	return true;
}


/* The C-level implementation of the scheduling interrupt
 * that is fired periodically for the purposes of preemption. */
INTERN NOBLOCK NONNULL((1, 2)) struct task *
NOTHROW(FCALL cpu_scheduler_interrupt)(struct cpu *__restrict caller,
                                       struct task *__restrict thread) {
	/* NOTE: Preemption is disabled while we're in here! */
	struct task *sleeper, *last_sleeper, *next;
	assert(thread == caller->c_current);
	/* Keep track of the cpu-local time, as well
	 * as the previous thread's active-time. */
	++FORCPU(caller, cpu_jiffies);
	++thread->t_atime.q_jtime;

	if ((sleeper = caller->c_sleeping) != NULL) {
		jtime_t now = FORCPU(caller, cpu_jiffies);
		quantum_diff_t diff, length;
		if (sleeper->t_sched.s_asleep.ss_timeout.q_jtime > now)
			goto done_wakeup;
		if (sleeper->t_sched.s_asleep.ss_timeout.q_jtime == now) {
			diff   = FORCPU(caller, cpu_quantum_offset);
			length = FORCPU(caller, cpu_quantum_length);
			if (((u64)sleeper->t_sched.s_asleep.ss_timeout.q_qtime *
			     sleeper->t_sched.s_asleep.ss_timeout.q_qsize) >
			    ((u64)diff * length))
				goto done_wakeup;
		}
		last_sleeper = sleeper;
		ATOMIC_FETCHOR(sleeper->t_flags, TASK_FTIMEOUT | TASK_FRUNNING);
		while ((next = last_sleeper->t_sched.s_asleep.ss_tmonxt) != NULL) {
			STATIC_ASSERT(offsetof(struct task, t_sched.s_running.sr_runprv) !=
			              offsetof(struct task, t_sched.s_asleep.ss_tmonxt));
			if (next->t_sched.s_asleep.ss_timeout.q_jtime > now)
				break;
			if (next->t_sched.s_asleep.ss_timeout.q_jtime == now) {
				diff   = FORCPU(caller, cpu_quantum_offset);
				length = FORCPU(caller, cpu_quantum_length);
				if (((u64)next->t_sched.s_asleep.ss_timeout.q_qtime *
				     next->t_sched.s_asleep.ss_timeout.q_qsize) >
				    ((u64)diff * length))
					break;
			}
			ATOMIC_FETCHOR(next->t_flags, TASK_FTIMEOUT | TASK_FRUNNING);
			last_sleeper->t_sched.s_running.sr_runnxt = next;
			next->t_sched.s_running.sr_runprv         = last_sleeper;
			last_sleeper                              = next;
		}
		caller->c_sleeping = next;
		if (next)
			next->t_sched.s_asleep.ss_pself = &caller->c_sleeping;
		/* Re-schedule all of the sleepers. */
		next                                           = caller->c_current->t_sched.s_running.sr_runnxt;
		sleeper->t_sched.s_running.sr_runprv           = caller->c_current;
		last_sleeper->t_sched.s_running.sr_runnxt      = next;
		next->t_sched.s_running.sr_runprv              = last_sleeper;
		caller->c_current->t_sched.s_running.sr_runnxt = sleeper;
	}
done_wakeup:
	return thread->t_sched.s_running.sr_runnxt;
}



typedef void /*NOTHROW*/((KCALL *pertask_onexit_t)(void));
INTDEF pertask_onexit_t __kernel_pertask_onexit_start[];
INTDEF pertask_onexit_t __kernel_pertask_onexit_end[];


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_decref_for_exit)(struct task *__restrict self) {
	decref(self);
}


/* Terminate the calling thread immediately.
 * WARNING: Do not call this function to terminate a thread.
 *          It would work, but exception handlers would not
 *          get unwound and resources would be leaked.
 *          If you wish to exit your current thread, just
 *          throw an `E_EXIT_THREAD' error.
 * This function is called by the unhandled exception handler
 * when it encounters an `E_EXIT_THREAD' error, or when exception
 * data cannot be propagated to userspace in the event of an
 * interrupt throwing some error, whilst originating from user-space.
 * NOTE: The caller should fill in `error_info()->e_error.e_exit.e_reason'
 *       to pass information on why the exit is happening. */
PUBLIC ATTR_NORETURN void
NOTHROW(FCALL task_exit)(int w_status) {
	struct task *caller, *next;
	struct cpu *mycpu;
	caller = THIS_TASK;
	assert(caller->t_flags & TASK_FRUNNING);

	/* Set the bit to indicate that we've started termination. */
	if (!(ATOMIC_FETCHOR(caller->t_flags, TASK_FTERMINATING) & TASK_FTERMINATING)) {
		/* Invoke cleanup callbacks. */
		pertask_onexit_t *iter = __kernel_pertask_onexit_start;
		printk(KERN_TRACE "[sched] Exiting thread %p[pid=%u]\n",
		       caller, task_getroottid_of_s(caller));
		for (; iter < __kernel_pertask_onexit_end; ++iter)
			(**iter)();
	}

	{
		struct taskpid *pid = THIS_TASKPID;
		if (pid) {
			assert(!WIFSTOPPED(w_status));
			assert(!WIFCONTINUED(w_status));
			/* Remember the task's exit status. */
			ATOMIC_WRITE(pid->tp_status.w_status, w_status);
			sig_broadcast(&pid->tp_changed);
		}
	}

	PREEMPTION_DISABLE();
	mycpu = caller->t_cpu;
	assertf(mycpu->c_current == caller, "Inconsistent scheduler state");
	assertf(caller != &FORCPU(mycpu, _this_idle), "The IDLE task cannot be terminated");
	assertf(caller->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv == caller &&
	        caller->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt == caller &&
	        (caller->t_sched.s_running.sr_runnxt == caller) ==
	        (caller->t_sched.s_running.sr_runprv == caller),
	        "caller             = %p\n"
	        "caller->PREV       = %p\n"
	        "caller->PREV->NEXT = %p\n"
	        "caller->NEXT       = %p\n"
	        "caller->NEXT->PREV = %p\n",
	        caller,
	        caller->t_sched.s_running.sr_runprv,
	        caller->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt,
	        caller->t_sched.s_running.sr_runnxt,
	        caller->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv);

	/* Indicate the end of the current quantum. */
	cpu_quantum_end();

	if (caller->t_sched.s_running.sr_runnxt == caller) {
		/* Last caller (load the IDLE caller now). */
		FORCPU(mycpu, _this_idle).t_sched.s_running.sr_runprv = &FORCPU(mycpu, _this_idle);
		FORCPU(mycpu, _this_idle).t_sched.s_running.sr_runnxt = &FORCPU(mycpu, _this_idle);
		ATOMIC_FETCHOR(FORCPU(mycpu, _this_idle).t_flags, TASK_FRUNNING);
		mycpu->c_current = next = &FORCPU(mycpu, _this_idle);
	} else {
		/* Unlink and load the next task. */
		mycpu->c_current = next                                          = caller->t_sched.s_running.sr_runnxt;
		caller->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = next;
		next->t_sched.s_running.sr_runprv                                = caller->t_sched.s_running.sr_runprv;
	}
	caller->t_sched.s_running.sr_runprv = NULL;
	caller->t_sched.s_running.sr_runnxt = NULL;
	assert(mycpu->c_current != caller);
	assert(next->t_sched.s_state);

	/* Hi-jack the execution stack of the next thread to have it do the decref()
	 * of our own thread, thus preventing the undefined behavior that would be
	 * caused if we tried to decref (and possibly destroy) ourself. */
	next->t_sched.s_state = task_push_asynchronous_srpc(next->t_sched.s_state,
	                                                    (task_srpc_t)&task_decref_for_exit,
	                                                    caller,
	                                                    NULL);
	/* Good bye... */
	cpu_run_current();
}



/* Convert to/from quantime time and regular timespecs */
PUBLIC NOBLOCK WUNUSED struct timespec
NOTHROW(FCALL qtime_to_timespec)(qtime_t const *__restrict qtime) {
	struct timespec result;
	result.tv_sec = qtime->q_jtime / HZ;
	result.tv_nsec = ((qtime->q_jtime % HZ) * (__NSECS_PER_SEC / HZ)) +
	                 ((qtime->q_qtime * (__NSECS_PER_SEC / HZ)) / qtime->q_qsize);
	return result;
}

PUBLIC NOBLOCK WUNUSED qtime_t
NOTHROW(FCALL timespec_to_qtime)(struct timespec const *__restrict tms) {
	qtime_t result;
	result.q_jtime = tms->tv_sec * HZ;
	result.q_qtime = tms->tv_nsec;
	result.q_qsize = __NSECS_PER_SEC;
	return result;
}



#undef CONFIG_AUTOADJUST_QUANTUM_DRIFT
//#define CONFIG_AUTOADJUST_QUANTUM_DRIFT 1


#ifdef CONFIG_AUTOADJUST_QUANTUM_DRIFT
LOCAL u8 cmos_read(u8 regno) {
	outb((port_t)0x70, regno);
	return inb((port_t)0x71);
}

INTERN struct timespec rtc_getnow(void) {
	struct timespec result;
	result.tv_nsec = 0;
	result.tv_sec  = cmos_read(0x00);
	result.tv_sec += cmos_read(0x02) * 60;
	result.tv_sec += cmos_read(0x04) * 60 * 60;
	/* TODO: day, month, year */
	return result;
}

INTERN struct timespec rtc_getres(void) {
	struct timespec result;
	result.tv_sec = 1;
	result.tv_nsec = 0;
	return result;
}


PRIVATE ATTR_PERCPU struct timespec resync_prev_rtc; /* RTC time at the previous resync */
PRIVATE ATTR_PERCPU struct timespec resync_prev_cpu; /* CPU time at the previous resync */

/* Timestamp (in per-cpu jiffies) of when the next re-sync should take place the soonest. */
PRIVATE ATTR_PERCPU jtime_t rtc_resync_next_jiffies;

/* Min interval between jiffi resync timings. */
PRIVATE jtime_t rtc_resync_interval = 2;
#endif /* CONFIG_AUTOADJUST_QUANTUM_DRIFT */


PUBLIC ATTR_NORETURN void
NOTHROW(FCALL cpu_idlemain)(void) {
#ifdef CONFIG_AUTOADJUST_QUANTUM_DRIFT
	struct cpu *me = THIS_CPU;
#endif /* CONFIG_AUTOADJUST_QUANTUM_DRIFT */
	for (;;) {
#ifdef CONFIG_AUTOADJUST_QUANTUM_DRIFT
		if (FORCPU(me, cpu_jiffies) >= FORCPU(me, rtc_resync_next_jiffies)) {
			qtime_t cpqtime;
			struct timespec cputime, rtctime;
			struct timespec cpudiff, rtcdiff;
			struct timespec drift; /* About by which the CPU has drifted away from the RTC */
again_resync:
			COMPILER_BARRIER();
			cpqtime = cpu_quantum_time();
			rtctime = rtc_getnow();
			COMPILER_BARRIER();
			if unlikely(!rtctime.tv_sec && !rtctime.tv_nsec)
				goto done_rtc; /* No RTC available... */
			cputime = qtime_to_timespec(&cpqtime);
			cputime -= cputime % rtc_getres();
			cpudiff = cputime - FORCPU(me, resync_prev_cpu);
			/* Truncate the CPU time diff to the RTC resolution. */
			rtcdiff = rtctime - FORCPU(me, resync_prev_rtc);
			drift   = cpudiff - rtcdiff;
			if (drift.get_nanoseconds() >= (__NSECS_PER_SEC / 8)) {
				/* Must fix the drift by adjusting `cpu_quantum_length'. */
				typedef __CRT_PRIVATE_SINT(__SIZEOF_JTIME_T__) sjtime_t;
				typedef __CRT_PRIVATE_UINT(__SIZEOF_QUANTUM_DIFF_T__) squantum_diff_t;
				qtime_t qdrift  = timespec_to_qtime(&drift); /* Total drift in quantum time. */
				qtime_t qpassd = timespec_to_qtime(&cpudiff);
				quantum_diff_t old_qlen;
				s64 total_quantum_drift;
				u64 total_quantum_passd;
				squantum_diff_t total_quantum_adjust;
				assert(qdrift.q_qsize == qpassd.q_qsize);
				assert(qdrift.q_qsize == __NSECS_PER_SEC);
				old_qlen = FORCPU(me, cpu_quantum_length);
				qdrift.q_qtime = (qdrift.q_qtime * old_qlen) / __NSECS_PER_SEC;
				qpassd.q_qtime = (qpassd.q_qtime * old_qlen) / __NSECS_PER_SEC;
				total_quantum_drift = ((s64)(sjtime_t)qdrift.q_jtime * (u64)old_qlen) + (squantum_diff_t)qdrift.q_qtime;
				total_quantum_passd = ((u64)qpassd.q_jtime * (u64)old_qlen) + (u64)qpassd.q_qtime;
				if unlikely(!total_quantum_passd)
					goto done_rtc;
				/* Must adjust `cpu_quantum_length' by subtracting `total_quantum_drift / total_quantum_passd' */
				total_quantum_adjust = (squantum_diff_t)(total_quantum_drift / total_quantum_passd);
				if (total_quantum_adjust != 0) {
					if (!ATOMIC_CMPXCH(*(quantum_diff_t *)&FORCPU(me, cpu_quantum_length), old_qlen, total_quantum_adjust))
						goto again_resync;
					COMPILER_BARRIER();
					FORCPU(me, resync_prev_rtc) = rtctime;
					FORCPU(me, resync_prev_cpu) = cputime;
					FORCPU(me, rtc_resync_next_jiffies) = FORCPU(me, cpu_jiffies) + rtc_resync_interval;
					COMPILER_BARRIER();
					printk(KERN_INFO "Adjust cpu#%u quantum length by %I32d (%I32u -> %I32u) to account for drift\n",
					       (unsigned int)me->c_id,
					       (s32)total_quantum_adjust,
					       (u32)old_qlen,
					       (u32)(old_qlen + total_quantum_adjust));
				}
			}
		}
done_rtc:
#endif /* CONFIG_AUTOADJUST_QUANTUM_DRIFT */

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
	return false;
}

PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL cpu_schedule_idle_job_and_incref)(idle_job_t job, void *arg,
                                                ptrdiff_t refcnt_offset) {
	(void)job;
	(void)arg;
	(void)refcnt_offset;
	/* TODO */
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
