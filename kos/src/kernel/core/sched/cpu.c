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
#ifndef GUARD_KERNEL_SRC_SCHED_CPU_C
#define GUARD_KERNEL_SRC_SCHED_CPU_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/debugtrap.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <sched/cpu.h>
#include <sched/pid.h>
#include <sched/rpc.h>
#include <sched/task.h>
#include <sched/time.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <bits/timespec.h>
#include <kos/jiffies.h>
#include <sys/wait.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN


#ifdef CONFIG_NO_SMP
#define DO_FLAGS_INDICATE_RUNNING(f)  (((f) & (TASK_FSTARTED|TASK_FRUNNING|TASK_FTERMINATED)) == (TASK_FSTARTED|TASK_FRUNNING))
#define DO_FLAGS_INDICATE_SLEEPING(f) (((f) & (TASK_FSTARTED|TASK_FRUNNING|TASK_FTERMINATED)) == (TASK_FSTARTED))
#else /* CONFIG_NO_SMP */
#define DO_FLAGS_INDICATE_RUNNING(f)  (((f) & (TASK_FSTARTED|TASK_FRUNNING|TASK_FTERMINATED|TASK_FPENDING)) == (TASK_FSTARTED|TASK_FRUNNING))
#define DO_FLAGS_INDICATE_SLEEPING(f) (((f) & (TASK_FSTARTED|TASK_FRUNNING|TASK_FTERMINATED|TASK_FPENDING)) == (TASK_FSTARTED))
#endif /* !CONFIG_NO_SMP */


#ifndef NDEBUG
PRIVATE NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(KCALL cpu_validate_pointer)(struct cpu *__restrict self) {
	cpuid_t i;
	for (i = 0; i < cpu_count; ++i) {
		if (cpu_vector[i] == self)
			return true;
	}
	return false;
}

PRIVATE NOBLOCK bool
NOTHROW(FCALL cpu_do_assert_running)(struct task *__restrict thread,
                                     struct cpu *__restrict me) {
	struct task *iter;
	assertf(DO_FLAGS_INDICATE_RUNNING(thread->t_flags),
	        "Flags do not indicate that the thread is running\n"
	        "thread          = %p\n"
	        "thread->t_flags = %#Ix\n",
	        thread, thread->t_flags);
	me = THIS_CPU;
	iter = me->c_current;
	do {
		if (iter == thread)
			return true;
	} while ((iter = iter->t_sched.s_running.sr_runnxt) != me->c_current);
	assertf(cpu_validate_pointer(thread->t_cpu),
	        "CPU Pointer %p of thread %p [tid=%u] is invalid",
	        thread->t_cpu, thread, task_getroottid_of_s(thread));
	assertf(thread->t_cpu == me,
	        "Thread is loaded onto a different CPU\n"
	        "me            = %p [cid=%u]\n"
	        "thread->t_cpu = %p [cid=%u]\n"
	        "thread        = %p [cid=%u]\n",
	        me, (unsigned int)me->c_id,
	        thread->t_cpu, (unsigned int)thread->t_cpu->c_id,
	        thread, task_getroottid_of_s(thread));
	/* Special case: The IDLE thread doesn't need to be part of the active chain! */
	if (thread == &FORCPU(me, thiscpu_idle))
		return true;
	if (__assertion_checkf("thread in THIS_CPU->c_current",
	                       "Thread %p [tid=%u] is not running on cpu %p [cid=%u]\n",
	                       thread, task_getroottid_of_s(thread),
	                       me, (unsigned int)me->c_id))
		return false;
	return true;
}

PRIVATE NOBLOCK bool
NOTHROW(FCALL cpu_do_assert_sleeping)(struct task *__restrict thread,
                                      struct cpu *__restrict me) {
	struct task *iter;
	assertf(DO_FLAGS_INDICATE_SLEEPING(thread->t_flags),
	        "Flags do not indicate that the thread is sleeping\n"
	        "thread          = %p [tid=%u]\n"
	        "thread->t_flags = %#Ix\n",
	        thread, task_getroottid_of_s(thread), thread->t_flags);
	me = THIS_CPU;
	for (iter = me->c_sleeping; iter != NULL;
	     iter = iter->t_sched.s_asleep.ss_tmonxt) {
		if (iter == thread)
			return true;
	}
	assertf(cpu_validate_pointer(thread->t_cpu),
	        "CPU Pointer %p of thread %p [tid=%u] is invalid",
	        thread->t_cpu, thread, task_getroottid_of_s(thread));
	assertf(thread->t_cpu == me,
	        "Thread is loaded onto a different CPU\n"
	        "me            = %p [cid=%u]\n"
	        "thread->t_cpu = %p [cid=%u]\n"
	        "thread        = %p [cid=%u]\n",
	        me, (unsigned int)me->c_id,
	        thread->t_cpu, (unsigned int)thread->t_cpu->c_id,
	        thread, task_getroottid_of_s(thread));
	/* Special case: The IDLE thread doesn't need to be part of the active chain! */
	if (thread == &FORCPU(me, thiscpu_idle))
		return true;
	if (__assertion_checkf("thread in THIS_CPU->c_sleeping",
	                       "Thread %p [tid=%u] is not running on cpu %p [cid=%u]\n",
	                       thread, task_getroottid_of_s(thread),
	                       me, (unsigned int)me->c_id))
		return false;
	return true;
}

PRIVATE NOBLOCK bool
NOTHROW(FCALL cpu_assert_rootpidns_integrity)(struct task *ignored_thread) {
	size_t i;
	struct cpu *me;
	if (!sync_tryread(&pidns_root))
		return true;
	me = THIS_CPU;
	for (i = 0; i <= pidns_root.pn_mask; ++i) {
		REF struct task *thread;
		struct taskpid *pid = pidns_root.pn_list[i].pe_pid;
		if (pid == NULL || pid == PIDNS_ENTRY_DELETED)
			continue;
		thread = taskpid_gettask(pid);
		if (!thread)
			continue;
		if (thread->t_cpu == me && thread != ignored_thread) {
			bool was_ok;
			uintptr_t flags = thread->t_flags;
			if (flags & TASK_FRUNNING) {
				was_ok = cpu_do_assert_running(thread, me);
			} else if (!(flags & TASK_FSTARTED)) {
				was_ok = true;
			} else if (flags & TASK_FTERMINATED) {
				was_ok = true;
			} else
#ifndef CONFIG_NO_SMP
			if (flags & TASK_FPENDING) {
				was_ok = true;
			} else
#endif /* !CONFIG_NO_SMP */
			{
				was_ok = cpu_do_assert_sleeping(thread, me);
			}
			if unlikely(!was_ok) {
				sync_endread(&pidns_root);
				decref_unlikely(thread);
				return false;
			}
		}
		decref_unlikely(thread);
	}
	sync_endread(&pidns_root);
	return true;
}

PUBLIC NOBLOCK void
NOTHROW(FCALL cpu_do_assert_integrity)(bool need_caller) {
	struct task *iter;
	struct task *caller;
	struct cpu *me;
	bool found_caller = false;
	caller = THIS_TASK;
	me     = caller->t_cpu;
	assertf(cpu_validate_pointer(me),
	        "Invalid cpu pointer: %p", me);
	iter = me->c_current;
	do {
		struct task **pother, *other;
		if (iter == caller)
			found_caller = true;
		/* Verify that no running thread appears as part of the sleepers chain. */
		for (pother = &me->c_sleeping; (other = *pother) != NULL;
		     pother = &other->t_sched.s_asleep.ss_tmonxt) {
			assertf(other->t_sched.s_asleep.ss_pself == pother,
			        "Broken list of sleeping thread\n"
			        "me                               = %p [cid=%u]\n"
			        "caller                           = %p [tid=%u]\n"
			        "other                            = %p [tid=%u]\n"
			        "other->t_sched.s_asleep.ss_pself = %p\n"
			        "pother                           = %p\n"
			        "PREV_SLEEPER(other)              = %p [tid=%u]\n"
			        "NEXT_SLEEPER(other)              = %p [tid=%u]\n",
			        me, (unsigned int)me->c_id,
			        caller, task_getroottid_of_s(caller),
			        other, task_getroottid_of_s(other),
			        other->t_sched.s_asleep.ss_pself,
			        pother,
			        pother == &me->c_sleeping ? NULL : container_of(pother, struct task, t_sched.s_asleep.ss_tmonxt),
			        pother == &me->c_sleeping ? 0 : task_getroottid_of_s(container_of(pother, struct task, t_sched.s_asleep.ss_tmonxt)),
			        other->t_sched.s_asleep.ss_tmonxt,
			        other->t_sched.s_asleep.ss_tmonxt ? task_getroottid_of_s(other->t_sched.s_asleep.ss_tmonxt) : 0);
			assertf(other != iter,
			        "Running thread also appears as sleeper\n"
			        "me                  = %p [cid=%u]\n"
			        "caller              = %p [tid=%u]\n"
			        "iter                = %p [tid=%u]\n"
			        "other               = %p [tid=%u]\n"
			        "PREV_SLEEPER(other) = %p [tid=%u]\n"
			        "NEXT_SLEEPER(other) = %p [tid=%u]\n",
			        me, (unsigned int)me->c_id,
			        caller, task_getroottid_of_s(caller),
			        iter, task_getroottid_of_s(iter),
			        other, task_getroottid_of_s(other),
			        pother == &me->c_sleeping ? NULL : container_of(pother, struct task, t_sched.s_asleep.ss_tmonxt),
			        pother == &me->c_sleeping ? 0 : task_getroottid_of_s(container_of(pother, struct task, t_sched.s_asleep.ss_tmonxt)),
			        other->t_sched.s_asleep.ss_tmonxt,
			        other->t_sched.s_asleep.ss_tmonxt ? task_getroottid_of_s(other->t_sched.s_asleep.ss_tmonxt) : 0);
			assertf(DO_FLAGS_INDICATE_SLEEPING(other->t_flags),
			        "Sleeping thread has incorrect flags\n"
			        "me                  = %p [cid=%u]\n"
			        "caller              = %p [tid=%u]\n"
			        "other               = %p [tid=%u]\n"
			        "other->t_flags      = %#Ix\n"
			        "PREV_PENDING(other) = %p [tid=%u]\n"
			        "NEXT_PENDING(other) = %p [tid=%u]\n",
			        me, (unsigned int)me->c_id,
			        caller, task_getroottid_of_s(caller),
			        other, task_getroottid_of_s(other),
			        other->t_flags,
			        pother == &me->c_pending ? NULL : container_of(pother, struct task, t_sched.s_pending.ss_pennxt),
			        pother == &me->c_pending ? 0 : task_getroottid_of_s(container_of(pother, struct task, t_sched.s_pending.ss_pennxt)),
			        other->t_sched.s_pending.ss_pennxt,
			        other->t_sched.s_pending.ss_pennxt ? task_getroottid_of_s(other->t_sched.s_pending.ss_pennxt) : 0);
			if (other == caller)
				found_caller = true;
		}
#ifndef CONFIG_NO_SMP
		/* Verify that no running thread appears as part of the pending chain. */
		for (pother = &me->c_pending; (other = *pother) != CPU_PENDING_ENDOFCHAIN;
		     pother = &other->t_sched.s_pending.ss_pennxt) {
			assert(other);
			assertf(other != iter,
			        "Running thread also appears as pending\n"
			        "me                  = %p [cid=%u]\n"
			        "caller              = %p [tid=%u]\n"
			        "iter                = %p [tid=%u]\n"
			        "other               = %p [tid=%u]\n"
			        "PREV_PENDING(other) = %p [tid=%u]\n"
			        "NEXT_PENDING(other) = %p [tid=%u]\n",
			        me, (unsigned int)me->c_id,
			        caller, task_getroottid_of_s(caller),
			        iter, task_getroottid_of_s(iter),
			        other, task_getroottid_of_s(other),
			        pother == &me->c_pending ? NULL : container_of(pother, struct task, t_sched.s_pending.ss_pennxt),
			        pother == &me->c_pending ? 0 : task_getroottid_of_s(container_of(pother, struct task, t_sched.s_pending.ss_pennxt)),
			        other->t_sched.s_pending.ss_pennxt,
			        other->t_sched.s_pending.ss_pennxt ? task_getroottid_of_s(other->t_sched.s_pending.ss_pennxt) : 0);
			assertf((other->t_flags & (TASK_FPENDING | TASK_FRUNNING)) == TASK_FPENDING,
			        "Pending thread has incorrect flags\n"
			        "me                  = %p [cid=%u]\n"
			        "caller              = %p [tid=%u]\n"
			        "other               = %p [tid=%u]\n"
			        "other->t_flags      = %#Ix\n"
			        "PREV_PENDING(other) = %p [tid=%u]\n"
			        "NEXT_PENDING(other) = %p [tid=%u]\n",
			        me, (unsigned int)me->c_id,
			        caller, task_getroottid_of_s(caller),
			        other, task_getroottid_of_s(other),
			        other->t_flags,
			        pother == &me->c_pending ? NULL : container_of(pother, struct task, t_sched.s_pending.ss_pennxt),
			        pother == &me->c_pending ? 0 : task_getroottid_of_s(container_of(pother, struct task, t_sched.s_pending.ss_pennxt)),
			        other->t_sched.s_pending.ss_pennxt,
			        other->t_sched.s_pending.ss_pennxt ? task_getroottid_of_s(other->t_sched.s_pending.ss_pennxt) : 0);
			if (other == caller)
				found_caller = true;
		}
#endif /* !CONFIG_NO_SMP */
		assertf(iter->t_sched.s_running.sr_runnxt &&
		        iter->t_sched.s_running.sr_runprv &&
		        /* Ensure that the prev/next ring is complete */
		        iter->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv == iter &&
		        iter->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt == iter &&
		        /* Ensure that in the case of a single-element ring, its pointers are consistent. */
		        (iter->t_sched.s_running.sr_runnxt == iter)
		        ? (iter->t_sched.s_running.sr_runprv == iter) && (me->c_current == iter)
		        : 1,
		        "me               = %p [cid=%u]\n"
		        "caller           = %p [tid=%u]\n"
		        "me->c_current    = %p [tid=%u]\n"
		        "iter             = %p [tid=%u]\n"
		        "iter->PREV       = %p [tid=%u]\n"
		        "iter->PREV->NEXT = %p [tid=%u]\n"
		        "iter->NEXT       = %p [tid=%u]\n"
		        "iter->NEXT->PREV = %p [tid=%u]\n",
		        me, (unsigned int)me->c_id,
		        caller, task_getroottid_of_s(caller),
		        me->c_current, task_getroottid_of_s(me->c_current),
		        iter, task_getroottid_of_s(iter),
		        iter->t_sched.s_running.sr_runprv,
		        task_getroottid_of_s(iter->t_sched.s_running.sr_runprv),
		        iter->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt,
		        task_getroottid_of_s(iter->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt),
		        iter->t_sched.s_running.sr_runnxt,
		        task_getroottid_of_s(iter->t_sched.s_running.sr_runnxt),
		        iter->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv,
		        task_getroottid_of_s(iter->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv));
		assertf(DO_FLAGS_INDICATE_RUNNING(iter->t_flags),
		        "Task apart of the ring of running threads is lacking the TASK_FRUNNING flag\n"
		        "me            = %p [cid=%u]\n"
		        "caller        = %p [tid=%u]\n"
		        "iter          = %p [tid=%u]\n"
		        "iter->PREV    = %p [tid=%u]\n"
		        "iter->NEXT    = %p [tid=%u]\n"
		        "iter->t_flags = %#Ix\n",
		        me, (unsigned int)me->c_id,
		        caller, task_getroottid_of_s(caller),
		        iter, task_getroottid_of_s(iter),
		        iter->t_sched.s_running.sr_runprv,
		        task_getroottid_of_s(iter->t_sched.s_running.sr_runprv),
		        iter->t_sched.s_running.sr_runnxt,
		        task_getroottid_of_s(iter->t_sched.s_running.sr_runnxt),
		        iter->t_flags);
	} while ((iter = iter->t_sched.s_running.sr_runnxt) != me->c_current);
	assertf(found_caller || !need_caller,
	        "failed to find calling thread\n"
	        "me            = %p [cid=%u]\n"
	        "caller        = %p [tid=%u]\n"
	        "me->c_current = %p [tid=%u]\n",
	        me, (unsigned int)me->c_id,
	        caller, task_getroottid_of_s(caller),
	        me->c_current, task_getroottid_of_s(me->c_current));
}


PUBLIC NOBLOCK void
NOTHROW(FCALL cpu_assert_running)(struct task *__restrict thread) {
	pflag_t was;
again:
	was = PREEMPTION_PUSHOFF();
	cpu_do_assert_integrity(true);
	if (!cpu_do_assert_running(thread, THIS_CPU)) {
failed:
		PREEMPTION_POP(was);
		goto again;
	}
	if (!cpu_assert_rootpidns_integrity(thread))
		goto failed;
	PREEMPTION_POP(was);
}

PUBLIC NOBLOCK void
NOTHROW(FCALL cpu_assert_sleeping)(struct task *__restrict thread) {
	pflag_t was;
again:
	was = PREEMPTION_PUSHOFF();
	cpu_do_assert_integrity(true);
	if (!cpu_do_assert_sleeping(thread, THIS_CPU)) {
failed:
		PREEMPTION_POP(was);
		goto again;
	}
	if (!cpu_assert_rootpidns_integrity(thread))
		goto failed;
	PREEMPTION_POP(was);
}

PUBLIC NOBLOCK void
NOTHROW(FCALL cpu_assert_integrity)(struct task *ignored_thread) {
	pflag_t was;
again:
	was = PREEMPTION_PUSHOFF();
	cpu_do_assert_integrity(!ignored_thread || ignored_thread != THIS_TASK);
	if (!cpu_assert_rootpidns_integrity(ignored_thread)) {
		PREEMPTION_POP(was);
		goto again;
	}
	PREEMPTION_POP(was);
}
#else /* !NDEBUG */
PUBLIC NOBLOCK void
NOTHROW(FCALL cpu_assert_integrity)(struct task *UNUSED(ignored_thread)) {
	/* no-op */
}
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL cpu_assert_running)(struct task *__restrict UNUSED(thread)) {
	/* no-op */
}
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL cpu_assert_sleeping)(struct task *__restrict UNUSED(thread)) {
	/* no-op */
}
#endif /* NDEBUG */



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


PRIVATE ATTR_USED ATTR_SECTION(".data.percpu.head")
struct cpu cpu_header = {
	/*.c_id       = */ 0,
	/*.c_current  = */ NULL,
	/*.c_sleeping = */ NULL,
#ifndef CONFIG_NO_SMP
	/*.c_pending  = */ CPU_PENDING_ENDOFCHAIN,
#endif /* !CONFIG_NO_SMP */
	/*.c_override = */ NULL,
	/*.c_state    = */ CPU_STATE_RUNNING
};

/* Weakly implement preemptive interrupt disabling as no-ops. */
PUBLIC ATTR_WEAK NOBLOCK ATTR_SECTION(".text.kernel.arch_cpu_disable_preemptive_interrupts_nopr") void
NOTHROW(KCALL arch_cpu_disable_preemptive_interrupts_nopr)(void) {
}
DEFINE_PUBLIC_WEAK_ALIAS(arch_cpu_enable_preemptive_interrupts_nopr, arch_cpu_disable_preemptive_interrupts_nopr);
DEFINE_PUBLIC_WEAK_ALIAS(arch_cpu_quantum_reset_nopr, arch_cpu_disable_preemptive_interrupts_nopr);

PUBLIC NOBLOCK ATTR_WEAK WUNUSED ATTR_SECTION(".text.kernel.arch_cpu_quantum_elapsed_nopr")
ATTR_CONST quantum_diff_t NOTHROW(KCALL arch_cpu_quantum_elapsed_nopr)(void) {
	return 0;
}


PUBLIC ATTR_PERCPU jtime_t volatile thiscpu_jiffies = 0;
PUBLIC ATTR_PERCPU quantum_diff_t volatile thiscpu_quantum_offset = 0;
PUBLIC ATTR_PERCPU quantum_diff_t volatile thiscpu_quantum_length = (quantum_diff_t)-1;

PUBLIC NOBLOCK WUNUSED qtime_t
NOTHROW(KCALL cpu_quantum_time)(void) {
	qtime_t result;
	struct cpu *me;
	pflag_t was;
	quantum_diff_t elapsed;
	was = PREEMPTION_PUSHOFF();
	me             = THIS_CPU;
	result.q_qtime = FORCPU(me, thiscpu_quantum_offset);
	result.q_qsize = FORCPU(me, thiscpu_quantum_length);
	elapsed        = cpu_quantum_elapsed_nopr(me, &result.q_jtime);
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




/* Increment `thiscpu_quantum_offset' by `diff' incrementing the `thiscpu_jiffies' counter
 * when the resulting value turns out to be greater than `thiscpu_quantum_length',
 * in which case the value will also be truncated.
 * When `thiscpu_jiffies' is incremented, also check if this causes additional
 * tasks to time out, and if so, re-schedule them for execution. */
PUBLIC NOBLOCK NOPREEMPT quantum_diff_t
NOTHROW(FCALL cpu_add_quantum_offset_nopr)(quantum_diff_t diff) {
	struct cpu *me = THIS_CPU;
	quantum_diff_t new_diff, more_jiffies = 0;
	quantum_diff_t length = FORCPU(me, thiscpu_quantum_length);
	assert(!PREEMPTION_ENABLED());
	if (OVERFLOW_UADD(FORCPU(me, thiscpu_quantum_offset), diff, &new_diff)) {
		more_jiffies = ((quantum_diff_t)-1 / length);
		new_diff     = (FORCPU(me, thiscpu_quantum_offset) + diff) - ((quantum_diff_t)-1);
	}
	if (new_diff >= length) {
		more_jiffies += new_diff / length;
		new_diff = new_diff % length;
	}
	FORCPU(me, thiscpu_quantum_offset) = new_diff;
	if (more_jiffies) {
		struct task *sleeper, *last_sleeper, *next;
		jtime_t new_jiffies;
		new_jiffies = FORCPU(me, thiscpu_jiffies) + more_jiffies;
		FORCPU(me, thiscpu_jiffies) = new_jiffies;
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
			next = me->c_current->t_sched.s_running.sr_runnxt;
			sleeper->t_sched.s_running.sr_runprv       = me->c_current;
			last_sleeper->t_sched.s_running.sr_runnxt  = next;
			next->t_sched.s_running.sr_runprv          = last_sleeper;
			me->c_current->t_sched.s_running.sr_runnxt = sleeper;
		}
	}
done_wakeup:
	return length;
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
PUBLIC bool NOTHROW(FCALL task_sleep)(struct timespec const *abs_timeout) {
	struct task *me = THIS_TASK;
	struct cpu *mycpu;
	cpu_assert_integrity();
	if (abs_timeout) {
		qtime_t now;
		/* Check if we should immediately time out. */
		if (!abs_timeout->tv_sec && !abs_timeout->tv_nsec)
			goto do_return_false;
		PREEMPTION_DISABLE();
		me->t_sched.s_asleep.ss_timeout = realtime_to_cpu_quantum_time_nopr(abs_timeout);
		now = cpu_quantum_time();
		/* Check if the given timeout has already expired. */
		if (now >= me->t_sched.s_asleep.ss_timeout) {
do_return_false:
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
	cpu_quantum_end_nopr();

	mycpu = me->t_cpu;
	cpu_assert_running(me);
	if (me == mycpu->c_override)
		goto wait_a_bit;

	/* The caller is the only thread hosted by this cpu. */
	if likely(me->t_sched.s_running.sr_runnxt == me) {
		struct task *idle;
		/* Special case: blocking call made by the IDLE thread. */
		if unlikely(me == &FORCPU(mycpu, thiscpu_idle)) {
wait_a_bit:
			/* Wait for the next interrupt. */
			PREEMPTION_ENABLE_WAIT();
			/* Indicate a sporadic wake-up. */
			return false;
		}
		/* Check if the IDLE thread had been sleeping. */
		idle = &FORCPU(mycpu, thiscpu_idle);
		if (idle->t_sched.s_asleep.ss_pself) {
			/* The IDLE thread had been sleeping (time it out) */
			ATOMIC_FETCHOR(idle->t_flags, TASK_FTIMEOUT);
			if ((*idle->t_sched.s_asleep.ss_pself = idle->t_sched.s_asleep.ss_tmonxt) != NULL)
				idle->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = idle->t_sched.s_asleep.ss_pself;
		}
		/* Unschedule the caller, and instead schedule the IDLE thread. */
		idle->t_sched.s_running.sr_runprv = idle;
		idle->t_sched.s_running.sr_runnxt = idle;
		ATOMIC_FETCHOR(idle->t_flags, TASK_FRUNNING);
		mycpu->c_current = idle;
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
	cpu_addsleepingtask_nopr(me);

	/* Continue execution in the next thread. */
	cpu_run_current_and_remember_nopr(me);

	/* HINT: If your debugger break here, it means that your
	 *       thread is probably waiting on some kind of signal. */
	cpu_assert_running(me);

	/* Check if we got timed out. */
	if (ATOMIC_FETCHAND(me->t_flags, ~TASK_FTIMEOUT) & TASK_FTIMEOUT)
		return false; /* Timeout... */

	return true;
}



INTDEF NOBLOCK void
NOTHROW(FCALL cpu_inc_jiffies)(struct cpu *__restrict self);

/* The C-level implementation of the scheduling interrupt
 * that is fired periodically for the purposes of preemption. */
INTERN NOBLOCK NONNULL((1, 2)) struct task *
NOTHROW(FCALL cpu_scheduler_interrupt)(struct cpu *__restrict caller,
                                       struct task *__restrict thread) {
	/* NOTE: Preemption is disabled while we're in here! */
	struct task *sleeper, *last_sleeper, *next;
	assertf(thread == caller->c_current,
	        "thread            = %p\n"
	        "caller            = %p\n"
	        "caller->c_id      = %u\n"
	        "caller->c_current = %p\n",
	        thread, caller,
	        (unsigned int)caller->c_id,
	        caller->c_current);
	cpu_assert_running(thread);
	/* Keep track of the cpu-local time, as well
	 * as the previous thread's active-time. */
	cpu_inc_jiffies(caller);
	++thread->t_atime.q_jtime;
	/* Check for a scheduling override */
	next = caller->c_override;
	/* Unlikely, since a sched override usually
	 * also disables preemptive interrupts. */
	if unlikely(next) {
		assert(thread == next);
		return next;
	}
	if ((sleeper = caller->c_sleeping) != NULL) {
		jtime_t now = FORCPU(caller, thiscpu_jiffies);
		quantum_diff_t diff, length;
		if (sleeper->t_sched.s_asleep.ss_timeout.q_jtime > now)
			goto done_wakeup;
		if (sleeper->t_sched.s_asleep.ss_timeout.q_jtime == now) {
			diff   = FORCPU(caller, thiscpu_quantum_offset);
			length = FORCPU(caller, thiscpu_quantum_length);
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
				diff   = FORCPU(caller, thiscpu_quantum_offset);
				length = FORCPU(caller, thiscpu_quantum_length);
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
		next = caller->c_current->t_sched.s_running.sr_runnxt;
		sleeper->t_sched.s_running.sr_runprv           = caller->c_current;
		last_sleeper->t_sched.s_running.sr_runnxt      = next;
		next->t_sched.s_running.sr_runprv              = last_sleeper;
		caller->c_current->t_sched.s_running.sr_runnxt = sleeper;
		cpu_assert_integrity();
	}
done_wakeup:
	return thread->t_sched.s_running.sr_runnxt;
}



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
	struct taskpid *pid = THIS_TASKPID;
	assert(!WIFSTOPPED(w_status));
	assert(!WIFCONTINUED(w_status));
	caller = THIS_TASK;
	assert(caller->t_flags & TASK_FRUNNING);
	if unlikely(caller->t_flags & TASK_FCRITICAL) {
		kernel_panic("Critical thread %p [tid=%u] has exited",
		             caller, task_getroottid_of_s(caller));
	}
	/* Fill in the exit status */
	if (pid)
		ATOMIC_WRITE(pid->tp_status.w_status, w_status);

	/* Set the bit to indicate that we've started termination. */
	if (!(ATOMIC_FETCHOR(caller->t_flags, TASK_FTERMINATING) & TASK_FTERMINATING)) {
		pertask_onexit_t *iter;
		printk(KERN_TRACE "[sched] Exiting thread %p [tid=%u]\n",
		       caller, task_getroottid_of_s(caller));

		/* Trigger the appropriate debug trap associated with thread/process exits.
		 * This is required because otherwise GDB will sooner or later hang itself
		 * when waiting for the exited-notification of a terminated thread once it's
		 * no longer able to find the thread apart of thread listings.
		 * s.a. /kos/misc/gdbridge/gdbride.dee
		 */
		if (kernel_debugtrap_enabled() && pid) {
			struct debugtrap_reason reason;
			reason.dtr_reason = task_isprocessleader_p(caller) ? DEBUGTRAP_REASON_PEXITED
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
	mycpu = caller->t_cpu;
	assertf(mycpu->c_current == caller, "Inconsistent scheduler state");
	assertf(mycpu->c_override != caller, "Cannot exit while being the scheduling override");
	assertf(caller != &FORCPU(mycpu, thiscpu_idle), "The IDLE task cannot be terminated");
	cpu_assert_integrity();

	/* Indicate the end of the current quantum. */
	cpu_quantum_end_nopr();

	if (caller->t_sched.s_running.sr_runnxt == caller) {
		/* Last caller (load the IDLE caller now). */
		FORCPU(mycpu, thiscpu_idle).t_sched.s_running.sr_runprv = &FORCPU(mycpu, thiscpu_idle);
		FORCPU(mycpu, thiscpu_idle).t_sched.s_running.sr_runnxt = &FORCPU(mycpu, thiscpu_idle);
		ATOMIC_FETCHOR(FORCPU(mycpu, thiscpu_idle).t_flags, TASK_FRUNNING);
		mycpu->c_current = next = &FORCPU(mycpu, thiscpu_idle);
	} else {
		/* Unlink and load the next task. */
		mycpu->c_current = next = caller->t_sched.s_running.sr_runnxt;
		caller->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = next;
		next->t_sched.s_running.sr_runprv = caller->t_sched.s_running.sr_runprv;
	}
	caller->t_sched.s_running.sr_runprv = NULL;
	caller->t_sched.s_running.sr_runnxt = NULL;
	assert(mycpu->c_current != caller);
	assert(next->t_sched.s_state);
	cpu_assert_integrity(/*ignored_thread:*/ caller);

	/* Hi-jack the execution stack of the next thread to have it do the decref()
	 * of our own thread, thus preventing the undefined behavior that would be
	 * caused if we tried to decref (and possibly destroy) ourself. */
	next->t_sched.s_state = task_push_asynchronous_rpc(next->t_sched.s_state,
	                                                   &task_decref_for_exit,
	                                                   caller);

	/* Set the flag to indicate that we've been fully terminated.
	 * NOTE: Also ensure that a couple of other flags are set/cleared correctly. */
	ATOMIC_FETCHOR(caller->t_flags, TASK_FTERMINATING | TASK_FTERMINATED | TASK_FSTARTED);
#ifndef CONFIG_NO_SMP
	ATOMIC_FETCHAND(caller->t_flags, ~(TASK_FRUNNING | TASK_FWAKING | TASK_FTIMEOUT | TASK_FSUSPENDED | TASK_FPENDING));
#else /* !CONFIG_NO_SMP */
	ATOMIC_FETCHAND(caller->t_flags, ~(TASK_FRUNNING | TASK_FWAKING | TASK_FTIMEOUT | TASK_FSUSPENDED));
#endif /* CONFIG_NO_SMP */

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
	if (pid)
		sig_broadcast(&pid->tp_changed);

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
