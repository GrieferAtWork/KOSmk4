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
PRIVATE NOBLOCK bool
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
	if (thread == &FORCPU(me, _this_idle))
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
	if (thread == &FORCPU(me, _this_idle))
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


INTDEF byte_t __kernel_percpu_size[];

PRIVATE ATTR_USED ATTR_SECTION(".data.percpu.head")
struct cpu cpu_header = {
	/*.c_id       = */ 0,
	/*.c_current  = */ NULL,
	/*.c_sleeping = */ NULL,
#ifndef CONFIG_NO_SMP
	/*.c_pending  = */ CPU_PENDING_ENDOFCHAIN,
#endif /* !CONFIG_NO_SMP */
	/*.c_override = */ NULL,
	/*.c_heapsize = */ (size_t)__kernel_percpu_size,
	/*.c_state    = */ CPU_STATE_RUNNING
};

PUBLIC ATTR_PERCPU jtime_t volatile cpu_jiffies = 0;
PUBLIC ATTR_PERCPU quantum_diff_t volatile cpu_quantum_offset = 0;
PUBLIC ATTR_PERCPU quantum_diff_t volatile cpu_quantum_length = (quantum_diff_t)-1;


/* Weakly implement preemptive interrupt disabling as no-ops. */
PUBLIC ATTR_WEAK NOBLOCK ATTR_SECTION(".text.kernel.cpu_disable_preemptive_interrupts") void
NOTHROW(KCALL cpu_disable_preemptive_interrupts)(void) {
}
DEFINE_PUBLIC_WEAK_ALIAS(cpu_enable_preemptive_interrupts, cpu_disable_preemptive_interrupts);
DEFINE_PUBLIC_WEAK_ALIAS(cpu_quantum_reset, cpu_disable_preemptive_interrupts);

PUBLIC NOBLOCK ATTR_WEAK WUNUSED ATTR_SECTION(".text.kernel.cpu_quantum_elapsed")
ATTR_CONST quantum_diff_t NOTHROW(KCALL cpu_quantum_elapsed)(void) {
	return 0;
}
PUBLIC NOBLOCK ATTR_WEAK WUNUSED ATTR_SECTION(".text.kernel.cpu_quantum_remaining")
ATTR_CONST quantum_diff_t NOTHROW(KCALL cpu_quantum_remaining)(void) {
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


PUBLIC NOBLOCK void
NOTHROW(KCALL cpu_quantum_end)(void) {
	quantum_diff_t elapsed, length;
	assert(!PREEMPTION_ENABLED());
	elapsed = cpu_quantum_elapsed_nopr();
	cpu_quantum_reset_nopr();
	length = cpu_add_quantum_offset(elapsed);
	THIS_TASK->t_atime.add_quantum(elapsed, length);
}

#ifndef __INTELLISENSE__
DECL_END

#define TASK_SLEEP_CPUTIME 1
#include "cpu-task_sleep-impl.c.inl"
#include "cpu-task_sleep-impl.c.inl"

DECL_BEGIN
#endif /* !__INTELLISENSE__ */




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
	++FORCPU(caller, cpu_jiffies);
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



typedef void /*NOTHROW*/ ((KCALL *pertask_onexit_t)(void));
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
		printk(KERN_TRACE "[sched] Exiting thread %p [tid=%u]\n",
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
	assertf(mycpu->c_override != caller, "Cannot exit while being the scheduling override");
	assertf(caller != &FORCPU(mycpu, _this_idle), "The IDLE task cannot be terminated");
	cpu_assert_integrity();

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
		mycpu->c_current = next = caller->t_sched.s_running.sr_runnxt;
		caller->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = next;
		next->t_sched.s_running.sr_runprv = caller->t_sched.s_running.sr_runprv;
	}
	caller->t_sched.s_running.sr_runprv = NULL;
	caller->t_sched.s_running.sr_runnxt = NULL;
	assert(mycpu->c_current != caller);
	assert(next->t_sched.s_state);
	cpu_assert_integrity(/*ignored_thread:*/ THIS_TASK);

	/* Hi-jack the execution stack of the next thread to have it do the decref()
	 * of our own thread, thus preventing the undefined behavior that would be
	 * caused if we tried to decref (and possibly destroy) ourself. */
	next->t_sched.s_state = task_push_asynchronous_srpc(next->t_sched.s_state,
	                                                    (task_srpc_t)&task_decref_for_exit,
	                                                    caller,
	                                                    NULL);

	/* Set the flag to indicate that we've been fully terminated.
	 * NOTE: Also ensure that a couple of other flags are set/cleared correctly. */
	ATOMIC_FETCHOR(caller->t_flags, TASK_FTERMINATING | TASK_FTERMINATED | TASK_FSTARTED);
#ifndef CONFIG_NO_SMP
	ATOMIC_FETCHAND(caller->t_flags, ~(TASK_FRUNNING | TASK_FWAKING | TASK_FTIMEOUT | TASK_FSUSPENDED | TASK_FPENDING));
#else /* !CONFIG_NO_SMP */
	ATOMIC_FETCHAND(caller->t_flags, ~(TASK_FRUNNING | TASK_FWAKING | TASK_FTIMEOUT | TASK_FSUSPENDED));
#endif /* CONFIG_NO_SMP */

	/* Good bye... */
	cpu_run_current();
}



/* Convert to/from quantum time and regular timespecs */
PUBLIC NOBLOCK WUNUSED ATTR_PURE struct timespec
NOTHROW(FCALL qtime_to_timespec)(qtime_t const *__restrict qtime) {
	struct timespec result;
	result.tv_sec = qtime->q_jtime / HZ;
	result.tv_nsec = ((qtime->q_jtime % HZ) * (__NSECS_PER_SEC / HZ)) +
	                 (syscall_ulong_t)((u64)((u64)qtime->q_qtime *
	                                         (__NSECS_PER_SEC / HZ)) /
	                                   qtime->q_qsize);
	return result;
}

PUBLIC NOBLOCK WUNUSED ATTR_PURE qtime_t
NOTHROW(FCALL timespec_to_qtime)(struct timespec const *__restrict tms) {
	qtime_t result;
	result.q_jtime  = tms->tv_sec * HZ;
	result.q_jtime += tms->tv_nsec / (__NSECS_PER_SEC / HZ);
	result.q_qtime  = tms->tv_nsec % (__NSECS_PER_SEC / HZ);
	result.q_qsize  = __NSECS_PER_SEC / HZ;
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
