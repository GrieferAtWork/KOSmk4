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
#ifndef GUARD_KERNEL_SRC_SCHED_RPC_ASYNC_C
#define GUARD_KERNEL_SRC_SCHED_RPC_ASYNC_C 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/types.h>
#include <kernel/vm.h>
#include <sched/cpu.h>
#include <sched/rpc.h>
#include <assert.h>
#include <sched/signal.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <alloca.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#ifdef __x86_64__
#define ICPUSTATE_ISANYUSER ICPUSTATE_ISUSER
#else /* __x86_64__ */
#define ICPUSTATE_ISANYUSER ICPUSTATE_ISUSER_OR_VM86
#endif /* !__x86_64__ */

#ifndef CONFIG_NO_SMP
PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL ipi_schedule_asynchronous_rpc_dw)(struct icpustate *__restrict state,
                                                void *args[CPU_IPI_ARGCOUNT]) {
	struct task *target    = (struct task *)args[0];
	task_rpc_t func        = (task_rpc_t)args[1];
	void *arg              = args[2];
	struct sig *completed  = (struct sig *)args[3];
	struct cpu *mycpu      = THIS_CPU;
	struct cpu *target_cpu = ATOMIC_READ(target->t_cpu);
	uintptr_t target_flags;
	if unlikely(target_cpu != mycpu) {
		/* Re-deliver the IPI to yet another CPU (letting it bounce until we get it right) */
		while (!cpu_sendipi(target_cpu,
		                    &ipi_schedule_asynchronous_rpc_dw,
		                    args,
		                    CPU_IPI_FWAKEUP))
			task_pause();
		return state;
	}
	if (target == THIS_TASK) {
		struct icpustate *result;
		result = (*func)(arg, state,
		                 ICPUSTATE_ISANYUSER(*state)
		                 ? TASK_RPC_REASON_ASYNCUSER
		                 : TASK_RPC_REASON_ASYNC,
		                 NULL);
		if (completed)
			sig_broadcast(completed);
		return result;
	}
	target_flags = ATOMIC_READ(target->t_flags);
	if unlikely(target_flags & TASK_FTERMINATED) {
		if (completed)
			sig_altbroadcast(completed, TASK_ASYNC_RPC_SIGALT_TERMINATED);
		return state;
	}
	target->t_sched.s_state = task_push_asynchronous_rpc(target->t_sched.s_state,
	                                                     func, arg, completed);
	return state;
}

PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL ipi_schedule_asynchronous_rpc_lp)(struct icpustate *__restrict state,
                                                void *args[CPU_IPI_ARGCOUNT]) {
	struct task *target    = (struct task *)args[0];
	task_rpc_t func        = (task_rpc_t)args[1];
	void *arg              = args[2];
	struct sig *completed  = (struct sig *)args[3];
	struct cpu *mycpu      = THIS_CPU;
	struct cpu *target_cpu = ATOMIC_READ(target->t_cpu);
	uintptr_t target_flags;
	if unlikely(target_cpu != mycpu) {
		/* Re-deliver the IPI to yet another CPU (letting it bounce until we get it right) */
		while (!cpu_sendipi(target_cpu,
		                    &ipi_schedule_asynchronous_rpc_lp,
		                    args,
		                    CPU_IPI_FWAKEUP))
			task_pause();
		return state;
	}
	if (target == THIS_TASK) {
		struct icpustate *result;
		result = (*func)(arg, state,
		                 ICPUSTATE_ISANYUSER(*state)
		                 ? TASK_RPC_REASON_ASYNCUSER
		                 : TASK_RPC_REASON_ASYNC,
		                 NULL);
		if (completed)
			sig_broadcast(completed);
		return result;
	}
	target_flags = ATOMIC_READ(target->t_flags);
	if unlikely(target_flags & TASK_FTERMINATED) {
		if (completed)
			sig_altbroadcast(completed, TASK_ASYNC_RPC_SIGALT_TERMINATED);
		return state;
	}
	target->t_sched.s_state = task_push_asynchronous_rpc(target->t_sched.s_state,
	                                                     func, arg, completed);
	if (!(target_flags & (TASK_FRUNNING | TASK_FPENDING))) {
		struct task *caller, *next;
		/* Wake up a sleeping thread by using a sporadic wake-up. */
		cpu_assert_sleeping(target);
		ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
		if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
			target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
		caller = THIS_TASK;
		next = caller->t_sched.s_running.sr_runnxt;
		target->t_sched.s_running.sr_runprv = caller;
		target->t_sched.s_running.sr_runnxt = next;
		caller->t_sched.s_running.sr_runnxt = target;
		next->t_sched.s_running.sr_runprv   = target;
		ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
		cpu_assert_running(target);
	}
	return state;
}

PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL ipi_schedule_asynchronous_rpc)(struct icpustate *__restrict state,
                                             void *args[CPU_IPI_ARGCOUNT]) {
	struct task *target    = (struct task *)args[0];
	task_rpc_t func        = (task_rpc_t)args[1];
	void *arg              = args[2];
	struct sig *completed  = (struct sig *)args[3];
	struct cpu *mycpu      = THIS_CPU;
	struct cpu *target_cpu = ATOMIC_READ(target->t_cpu);
	uintptr_t target_flags;
	if unlikely(target_cpu != mycpu) {
		/* Re-deliver the IPI to yet another CPU (letting it bounce until we get it right) */
		while (!cpu_sendipi(target_cpu, &ipi_schedule_asynchronous_rpc, args, CPU_IPI_FWAKEUP))
			task_pause();
		return state;
	}
	if (target == THIS_TASK) {
		struct icpustate *result;
		result = (*func)(arg, state,
		                 ICPUSTATE_ISANYUSER(*state)
		                 ? TASK_RPC_REASON_ASYNCUSER
		                 : TASK_RPC_REASON_ASYNC,
		                 NULL);
		if (completed)
			sig_broadcast(completed);
		return result;
	}
	target_flags = ATOMIC_READ(target->t_flags);
	if unlikely(target_flags & TASK_FTERMINATED) {
		if (completed)
			sig_altbroadcast(completed, TASK_ASYNC_RPC_SIGALT_TERMINATED);
		return state;
	}
	target->t_sched.s_state = task_push_asynchronous_rpc(target->t_sched.s_state,
	                                                     func, arg, completed);
	if (target_flags & TASK_FRUNNING) {
		/* Running thread */
		cpu_assert_running(target);
		if (target != THIS_TASK) {
			struct task *caller, *next;
			/* Re-schedule the thread to execute as soon as possible. */
			target->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = target->t_sched.s_running.sr_runnxt;
			target->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = target->t_sched.s_running.sr_runprv;
insert_target_after_caller:
			caller                              = THIS_TASK;
			next                                = caller->t_sched.s_running.sr_runnxt;
			target->t_sched.s_running.sr_runprv = caller;
			target->t_sched.s_running.sr_runnxt = next;
			caller->t_sched.s_running.sr_runnxt = target;
			next->t_sched.s_running.sr_runprv   = target;
			ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
			cpu_assert_running(target);
		}
	} else if (!(target_flags & TASK_FPENDING)) {
		/* Wake up a sleeping thread by using a sporadic wake-up. */
		cpu_assert_sleeping(target);
		ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
		if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
			target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
		goto insert_target_after_caller;
	}
	return state;
}

PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL ipi_schedule_asynchronous_rpc_hp)(struct icpustate *__restrict state,
                                                void *args[CPU_IPI_ARGCOUNT]) {
	struct task *target    = (struct task *)args[0];
	task_rpc_t func        = (task_rpc_t)args[1];
	void *arg              = args[2];
	struct sig *completed  = (struct sig *)args[3];
	struct cpu *mycpu      = THIS_CPU;
	struct cpu *target_cpu = ATOMIC_READ(target->t_cpu);
	uintptr_t target_flags;
	if unlikely(target_cpu != mycpu) {
		/* Re-deliver the IPI to yet another CPU (letting it bounce until we get it right) */
		while (!cpu_sendipi(target_cpu, &ipi_schedule_asynchronous_rpc_hp, args, CPU_IPI_FWAKEUP))
			task_pause();
		return state;
	}
	if (target == THIS_TASK) {
		struct icpustate *result;
		result = (*func)(arg, state,
		                 ICPUSTATE_ISANYUSER(*state)
		                 ? TASK_RPC_REASON_ASYNCUSER
		                 : TASK_RPC_REASON_ASYNC,
		                 NULL);
		if (completed)
			sig_broadcast(completed);
		return result;
	}
	target_flags = ATOMIC_READ(target->t_flags);
	if unlikely(target_flags & TASK_FTERMINATED) {
		if (completed)
			sig_altbroadcast(completed, TASK_ASYNC_RPC_SIGALT_TERMINATED);
		return state;
	}
	target->t_sched.s_state = task_push_asynchronous_rpc(target->t_sched.s_state,
	                                                     func, arg, completed);
	if (target_flags & TASK_FRUNNING) {
		/* Running thread */
		cpu_assert_running(target);
		if (target != THIS_TASK) {
			struct task *caller, *next;
			/* Re-schedule the thread to execute as soon as possible. */
			target->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = target->t_sched.s_running.sr_runnxt;
			target->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = target->t_sched.s_running.sr_runprv;
insert_target_after_caller:
			caller                              = THIS_TASK;
			next                                = caller->t_sched.s_running.sr_runnxt;
			target->t_sched.s_running.sr_runprv = caller;
			target->t_sched.s_running.sr_runnxt = next;
			caller->t_sched.s_running.sr_runnxt = target;
			next->t_sched.s_running.sr_runprv   = target;
			ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
			cpu_assert_running(target);
			return CPU_IPI_MODE_SWITCH_TASKS;
		}
	} else if (!(target_flags & TASK_FPENDING)) {
		/* Wake up a sleeping thread by using a sporadic wake-up. */
		cpu_assert_sleeping(target);
		ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
		if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
			target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
		goto insert_target_after_caller;
	}
	return state;
}






PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL ipi_redirect_usercode_rpc_dw)(struct icpustate *__restrict state,
                                            void *args[CPU_IPI_ARGCOUNT]) {
	struct task *target    = (struct task *)args[0];
	struct cpu *mycpu      = THIS_CPU;
	struct cpu *target_cpu = ATOMIC_READ(target->t_cpu);
	uintptr_t target_flags;
	if unlikely(target_cpu != mycpu) {
		/* Re-deliver the IPI to yet another CPU (letting it bounce until we get it right) */
		while (!cpu_sendipi(target_cpu, &ipi_redirect_usercode_rpc_dw, args, CPU_IPI_FWAKEUP))
			task_pause();
		return state;
	}
	target_flags = ATOMIC_READ(target->t_flags);
	if unlikely(target_flags & TASK_FTERMINATED)
		return state;
	task_enable_redirect_usercode_rpc(target);
	return state;
}

PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL ipi_redirect_usercode_rpc_lp)(struct icpustate *__restrict state,
                                            void *args[CPU_IPI_ARGCOUNT]) {
	struct task *target    = (struct task *)args[0];
	struct cpu *mycpu      = THIS_CPU;
	struct cpu *target_cpu = ATOMIC_READ(target->t_cpu);
	uintptr_t target_flags;
	if unlikely(target_cpu != mycpu) {
		/* Re-deliver the IPI to yet another CPU (letting it bounce until we get it right) */
		while (!cpu_sendipi(target_cpu, &ipi_redirect_usercode_rpc_lp, args, CPU_IPI_FWAKEUP))
			task_pause();
		return state;
	}
	target_flags = ATOMIC_READ(target->t_flags);
	if unlikely(target_flags & TASK_FTERMINATED)
		return state;
	task_enable_redirect_usercode_rpc(target);
	if (!(target_flags & (TASK_FRUNNING | TASK_FPENDING))) {
		struct task *caller, *next;
		/* Wake up a sleeping thread by using a sporadic wake-up. */
		cpu_assert_sleeping(target);
		ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
		if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
			target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
		caller                              = THIS_TASK;
		next                                = caller->t_sched.s_running.sr_runnxt;
		target->t_sched.s_running.sr_runprv = caller;
		target->t_sched.s_running.sr_runnxt = next;
		caller->t_sched.s_running.sr_runnxt = target;
		next->t_sched.s_running.sr_runprv   = target;
		ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
		cpu_assert_running(target);
	}
	return state;
}

PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL ipi_redirect_usercode_rpc_hp)(struct icpustate *__restrict state,
                                            void *args[CPU_IPI_ARGCOUNT]) {
	struct task *target    = (struct task *)args[0];
	struct cpu *mycpu      = THIS_CPU;
	struct cpu *target_cpu = ATOMIC_READ(target->t_cpu);
	uintptr_t target_flags;
	if unlikely(target_cpu != mycpu) {
		/* Re-deliver the IPI to yet another CPU (letting it bounce until we get it right) */
		while (!cpu_sendipi(target_cpu, &ipi_redirect_usercode_rpc_hp, args, CPU_IPI_FWAKEUP))
			task_pause();
		return state;
	}
	target_flags = ATOMIC_READ(target->t_flags);
	if unlikely(target_flags & TASK_FTERMINATED)
		return state;
	task_enable_redirect_usercode_rpc(target);
	if (target_flags & TASK_FRUNNING) {
		/* Running thread */
		cpu_assert_running(target);
		if (target != THIS_TASK) {
			struct task *caller, *next;
			/* Re-schedule the thread to execute as soon as possible. */
			target->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = target->t_sched.s_running.sr_runnxt;
			target->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = target->t_sched.s_running.sr_runprv;
insert_target_after_caller:
			caller                              = THIS_TASK;
			next                                = caller->t_sched.s_running.sr_runnxt;
			target->t_sched.s_running.sr_runprv = caller;
			target->t_sched.s_running.sr_runnxt = next;
			caller->t_sched.s_running.sr_runnxt = target;
			next->t_sched.s_running.sr_runprv   = target;
			ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
			cpu_assert_running(target);
			return CPU_IPI_MODE_SWITCH_TASKS;
		}
	} else if (!(target_flags & TASK_FPENDING)) {
		/* Wake up a sleeping thread by using a sporadic wake-up. */
		cpu_assert_sleeping(target);
		ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
		if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
			target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
		goto insert_target_after_caller;
	}
	return state;
}

PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL ipi_redirect_usercode_rpc)(struct icpustate *__restrict state,
                                         void *args[CPU_IPI_ARGCOUNT]) {
	uintptr_t target_flags;
	struct task *target    = (struct task *)args[0];
	struct cpu *mycpu      = THIS_CPU;
	struct cpu *target_cpu = ATOMIC_READ(target->t_cpu);
	if unlikely(target_cpu != mycpu) {
		/* Re-deliver the IPI to yet another CPU (letting it bounce until we get it right) */
		while (!cpu_sendipi(target_cpu, &ipi_redirect_usercode_rpc, args, CPU_IPI_FWAKEUP))
			task_pause();
		return state;
	}
	target_flags = ATOMIC_READ(target->t_flags);
	if unlikely(target_flags & TASK_FTERMINATED)
		return state;
	task_enable_redirect_usercode_rpc(target);
	/* Wake the task, so-as to allow an interrupting user-code RPC to  */
	if (target_flags & TASK_FRUNNING) {
		/* Running thread */
		cpu_assert_running(target);
		if (target != THIS_TASK) {
			struct task *caller, *next;
			/* Re-schedule the thread to execute as soon as possible. */
			target->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = target->t_sched.s_running.sr_runnxt;
			target->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = target->t_sched.s_running.sr_runprv;
insert_target_after_caller:
			caller                              = THIS_TASK;
			next                                = caller->t_sched.s_running.sr_runnxt;
			target->t_sched.s_running.sr_runprv = caller;
			target->t_sched.s_running.sr_runnxt = next;
			caller->t_sched.s_running.sr_runnxt = target;
			next->t_sched.s_running.sr_runprv   = target;
			ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
			cpu_assert_running(target);
			return CPU_IPI_MODE_SWITCH_TASKS;
		}
	} else if (!(target_flags & TASK_FPENDING)) {
		/* Wake up a sleeping thread by using a sporadic wake-up. */
		cpu_assert_sleeping(target);
		ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
		if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
			target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
		goto insert_target_after_caller;
	}
	return state;
}
#endif



PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL task_redirect_usercode_rpc)(struct task *__restrict target, uintptr_t mode) {
	pflag_t was;
#ifndef CONFIG_NO_SMP
	struct cpu *mycpu;
	struct cpu *target_cpu;
	was        = PREEMPTION_PUSHOFF();
	mycpu      = THIS_CPU;
	target_cpu = ATOMIC_READ(target->t_cpu);
	if (mycpu != target_cpu) {
		void *args[CPU_IPI_ARGCOUNT];
		args[0] = (void *)target;
		args[1] = (void *)mode;
		while (!cpu_sendipi(target_cpu,
		                    ((mode & TASK_RPC_FDONTWAKE)
		                     ? &ipi_redirect_usercode_rpc_dw
		                     : (mode & TASK_RPC_FLOWPRIO)
		                       ? &ipi_redirect_usercode_rpc_lp
		                       : (mode & TASK_RPC_FHIGHPRIO)
		                         ? &ipi_redirect_usercode_rpc_hp
		                         : &ipi_redirect_usercode_rpc),
		                    args,
		                    CPU_IPI_FWAKEUP))
			task_pause();
		PREEMPTION_POP(was);
	} else
#endif /* !CONFIG_NO_SMP */
	{
		uintptr_t target_flags;
#ifdef CONFIG_NO_SMP
		was = PREEMPTION_PUSHOFF();
#endif /* CONFIG_NO_SMP */
		target_flags = target->t_flags;
		/* Deliver the RPC to another thread on our own CPU. */
		if (target_flags & TASK_FTERMINATED) {
			PREEMPTION_POP(was);
			return false;
		}
		task_enable_redirect_usercode_rpc(target);
		if (mode & TASK_RPC_FDONTWAKE)
			goto done_success;
		if (target_flags & TASK_FRUNNING) {
			/* Running thread */
			cpu_assert_running(target);
			if (!(mode & TASK_RPC_FLOWPRIO) && target != THIS_TASK) {
				struct task *caller, *next;
				/* Re-schedule the thread to execute as soon as possible. */
				target->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = target->t_sched.s_running.sr_runnxt;
				target->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = target->t_sched.s_running.sr_runprv;
insert_target_after_caller:
				caller = THIS_TASK;
				next   = caller->t_sched.s_running.sr_runnxt;
				target->t_sched.s_running.sr_runprv = caller;
				target->t_sched.s_running.sr_runnxt = next;
				caller->t_sched.s_running.sr_runnxt = target;
				next->t_sched.s_running.sr_runprv   = target;
				ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
				cpu_assert_running(target);
				if (PREEMPTION_WASENABLED(was)) {
					if (mode & TASK_RPC_FHIGHPRIO) {
						/* End the current quantum prematurely. */
						cpu_quantum_end();
						/* Immediately switch to the next target thread. */
#ifndef CONFIG_NO_SMP
						mycpu->c_current = target;
#else
						_bootcpu.c_current = target;
#endif
						cpu_run_current_and_remember(caller);
					}
					PREEMPTION_ENABLE();
				}
				return true;
			}
		}
#ifndef CONFIG_NO_SMP
		else if (!(target_flags & TASK_FPENDING))
#else /* !CONFIG_NO_SMP */
		else
#endif /* CONFIG_NO_SMP */
		{
			/* Wake up a sleeping thread by using a sporadic wake-up. */
			assert(target != THIS_TASK);
			cpu_assert_sleeping(target);
			ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
			if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
				target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
			goto insert_target_after_caller;
		}
done_success:
		PREEMPTION_POP(was);
	}
	return true;
}

#ifndef CONFIG_NO_SMP
STATIC_ASSERT(CPU_IPI_FWAITFOR == TASK_RPC_FWAITFOR);
#endif /* !CONFIG_NO_SMP */

PUBLIC NOBLOCK NONNULL((1, 2)) bool
NOTHROW(KCALL task_schedule_asynchronous_rpc)(struct task *__restrict target, task_rpc_t func,
                                              void *arg, uintptr_t mode, struct sig *completed) {
	pflag_t was;
#ifndef CONFIG_NO_SMP
	struct cpu *mycpu;
	struct cpu *target_cpu;
	was        = PREEMPTION_PUSHOFF();
	mycpu      = THIS_CPU;
	target_cpu = ATOMIC_READ(target->t_cpu);
	if (mycpu != target_cpu) {
		void *args[CPU_IPI_ARGCOUNT];
		args[0] = target;
		args[1] = (void *)func;
		args[2] = arg;
		args[3] = completed;
		while (!cpu_sendipi(target_cpu,
		                    ((mode & TASK_RPC_FDONTWAKE)
		                     ? &ipi_schedule_asynchronous_rpc_dw
		                     : (mode & TASK_RPC_FLOWPRIO)
		                       ? &ipi_schedule_asynchronous_rpc_lp
		                       : (mode & TASK_RPC_FHIGHPRIO)
		                         ? &ipi_schedule_asynchronous_rpc_hp
		                         : &ipi_schedule_asynchronous_rpc),
		                    args,
		                    CPU_IPI_FWAKEUP | (mode & TASK_RPC_FWAITFOR)))
			task_pause();
		PREEMPTION_POP(was);
	} else
#endif /* !CONFIG_NO_SMP */
	{
		uintptr_t target_flags;
#ifdef CONFIG_NO_SMP
		was = PREEMPTION_PUSHOFF();
#endif /* CONFIG_NO_SMP */
		/* ASYNC RPC to-be delivered to our own CPU */
		if unlikely(target == THIS_TASK) {
			PREEMPTION_POP(was);
			/* Execute the RPC immediately. */
			task_rpc_exec_here(func, arg, completed);
			return true;
		}
		/* Deliver the RPC to another thread on our own CPU. */
		target_flags = target->t_flags;
		if (target_flags & TASK_FTERMINATED) {
			PREEMPTION_POP(was);
			return false;
		}
		target->t_sched.s_state = task_push_asynchronous_rpc(target->t_sched.s_state,
		                                                     func, arg, completed);
		if (mode & TASK_RPC_FDONTWAKE)
			goto done_success;
		if (target_flags & TASK_FRUNNING) {
			/* Running thread */
			cpu_assert_running(target);
			if (!(mode & TASK_RPC_FLOWPRIO) && target != THIS_TASK) {
				struct task *caller, *next;
				/* Re-schedule the thread to execute as soon as possible. */
				target->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = target->t_sched.s_running.sr_runnxt;
				target->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = target->t_sched.s_running.sr_runprv;
insert_target_after_caller:
				caller                              = THIS_TASK;
				next                                = caller->t_sched.s_running.sr_runnxt;
				target->t_sched.s_running.sr_runprv = caller;
				target->t_sched.s_running.sr_runnxt = next;
				caller->t_sched.s_running.sr_runnxt = target;
				next->t_sched.s_running.sr_runprv   = target;
				ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
				cpu_assert_running(target);
				if (PREEMPTION_WASENABLED(was)) {
					if (mode & TASK_RPC_FHIGHPRIO) {
						/* End the current quantum prematurely. */
						cpu_quantum_end();
						/* Immediately switch to the next target thread. */
#ifndef CONFIG_NO_SMP
						mycpu->c_current = target;
#else
						_bootcpu.c_current = target;
#endif
						cpu_run_current_and_remember(caller);
					}
					PREEMPTION_ENABLE();
				}
				return true;
			}
		}
#ifndef CONFIG_NO_SMP
		else if (!(target_flags & TASK_FPENDING))
#else /* !CONFIG_NO_SMP */
		else
#endif /* CONFIG_NO_SMP */
		{
			/* Wake up a sleeping thread by using a sporadic wake-up. */
			assert(target != THIS_TASK);
			cpu_assert_sleeping(target);
			ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
			if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
				target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
			goto insert_target_after_caller;
		}
done_success:
		PREEMPTION_POP(was);
	}
	return true;
}




#ifndef CONFIG_NO_SMP
PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL ipi_schedule_asynchronous_srpc_dw)(struct icpustate *__restrict state,
                                                 void *args[CPU_IPI_ARGCOUNT]) {
	struct task *target    = (struct task *)args[0];
	task_srpc_t func       = (task_srpc_t)args[1];
	void *arg              = args[2];
	struct sig *completed  = (struct sig *)args[3];
	struct cpu *mycpu      = THIS_CPU;
	struct cpu *target_cpu = ATOMIC_READ(target->t_cpu);
	uintptr_t target_flags;
	if unlikely(target_cpu != mycpu) {
		/* Re-deliver the IPI to yet another CPU (letting it bounce until we get it right) */
		while (!cpu_sendipi(target_cpu, &ipi_schedule_asynchronous_srpc_dw, args, CPU_IPI_FWAKEUP))
			task_pause();
		return state;
	}
	if (target == THIS_TASK) {
		(*func)(arg);
		if (completed)
			sig_broadcast(completed);
		return state;
	}
	target_flags = ATOMIC_READ(target->t_flags);
	if unlikely(target_flags & TASK_FTERMINATED) {
		if (completed)
			sig_altbroadcast(completed, TASK_ASYNC_RPC_SIGALT_TERMINATED);
		return state;
	}
	target->t_sched.s_state = task_push_asynchronous_srpc(target->t_sched.s_state,
	                                                      func, arg, completed);
	return state;
}

PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL ipi_schedule_asynchronous_srpc_lp)(struct icpustate *__restrict state,
                                                 void *args[CPU_IPI_ARGCOUNT]) {
	struct task *target    = (struct task *)args[0];
	task_srpc_t func       = (task_srpc_t)args[1];
	void *arg              = args[2];
	struct sig *completed  = (struct sig *)args[3];
	struct cpu *mycpu      = THIS_CPU;
	struct cpu *target_cpu = ATOMIC_READ(target->t_cpu);
	uintptr_t target_flags;
	if unlikely(target_cpu != mycpu) {
		/* Re-deliver the IPI to yet another CPU (letting it bounce until we get it right) */
		while (!cpu_sendipi(target_cpu, &ipi_schedule_asynchronous_srpc_lp, args, CPU_IPI_FWAKEUP))
			task_pause();
		return state;
	}
	if (target == THIS_TASK) {
		(*func)(arg);
		if (completed)
			sig_broadcast(completed);
		return state;
	}
	target_flags = ATOMIC_READ(target->t_flags);
	if unlikely(target_flags & TASK_FTERMINATED) {
		if (completed)
			sig_altbroadcast(completed, TASK_ASYNC_RPC_SIGALT_TERMINATED);
		return state;
	}
	target->t_sched.s_state = task_push_asynchronous_srpc(target->t_sched.s_state,
	                                                      func, arg, completed);
	if (!(target_flags & (TASK_FRUNNING | TASK_FPENDING))) {
		struct task *caller, *next;
		/* Wake up a sleeping thread by using a sporadic wake-up. */
		cpu_assert_sleeping(target);
		ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
		if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
			target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
		caller                              = THIS_TASK;
		next                                = caller->t_sched.s_running.sr_runnxt;
		target->t_sched.s_running.sr_runprv = caller;
		target->t_sched.s_running.sr_runnxt = next;
		caller->t_sched.s_running.sr_runnxt = target;
		next->t_sched.s_running.sr_runprv   = target;
		ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
		cpu_assert_running(target);
	}
	return state;
}

PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL ipi_schedule_asynchronous_srpc)(struct icpustate *__restrict state,
                                              void *args[CPU_IPI_ARGCOUNT]) {
	struct task *target    = (struct task *)args[0];
	task_srpc_t func       = (task_srpc_t)args[1];
	void *arg              = args[2];
	struct sig *completed  = (struct sig *)args[3];
	struct cpu *mycpu      = THIS_CPU;
	struct cpu *target_cpu = ATOMIC_READ(target->t_cpu);
	uintptr_t target_flags;
	if unlikely(target_cpu != mycpu) {
		/* Re-deliver the IPI to yet another CPU (letting it bounce until we get it right) */
		while (!cpu_sendipi(target_cpu, &ipi_schedule_asynchronous_srpc, args, CPU_IPI_FWAKEUP))
			task_pause();
		return state;
	}
	if (target == THIS_TASK) {
		(*func)(arg);
		if (completed)
			sig_broadcast(completed);
		return state;
	}
	target_flags = ATOMIC_READ(target->t_flags);
	if unlikely(target_flags & TASK_FTERMINATED) {
		if (completed)
			sig_altbroadcast(completed, TASK_ASYNC_RPC_SIGALT_TERMINATED);
		return state;
	}
	target->t_sched.s_state = task_push_asynchronous_srpc(target->t_sched.s_state,
	                                                      func, arg, completed);
	if (target_flags & TASK_FRUNNING) {
		/* Running thread */
		cpu_assert_running(target);
		if (target != THIS_TASK) {
			struct task *caller, *next;
			/* Re-schedule the thread to execute as soon as possible. */
			target->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = target->t_sched.s_running.sr_runnxt;
			target->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = target->t_sched.s_running.sr_runprv;
insert_target_after_caller:
			caller                              = THIS_TASK;
			next                                = caller->t_sched.s_running.sr_runnxt;
			target->t_sched.s_running.sr_runprv = caller;
			target->t_sched.s_running.sr_runnxt = next;
			caller->t_sched.s_running.sr_runnxt = target;
			next->t_sched.s_running.sr_runprv   = target;
			ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
			cpu_assert_running(target);
		}
	} else if (!(target_flags & TASK_FPENDING)) {
		/* Wake up a sleeping thread by using a sporadic wake-up. */
		cpu_assert_sleeping(target);
		ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
		if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
			target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
		goto insert_target_after_caller;
	}
	return state;
}

PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL ipi_schedule_asynchronous_srpc_hp)(struct icpustate *__restrict state,
                                                 void *args[CPU_IPI_ARGCOUNT]) {
	struct task *target    = (struct task *)args[0];
	task_srpc_t func       = (task_srpc_t)args[1];
	void *arg              = args[2];
	struct sig *completed  = (struct sig *)args[3];
	struct cpu *mycpu      = THIS_CPU;
	struct cpu *target_cpu = ATOMIC_READ(target->t_cpu);
	uintptr_t target_flags;
	if unlikely(target_cpu != mycpu) {
		/* Re-deliver the IPI to yet another CPU (letting it bounce until we get it right) */
		while (!cpu_sendipi(target_cpu,
		                    &ipi_schedule_asynchronous_srpc,
		                    args,
		                    CPU_IPI_FWAKEUP))
			task_pause();
		return state;
	}
	if (target == THIS_TASK) {
		(*func)(arg);
		if (completed)
			sig_broadcast(completed);
		return state;
	}
	target_flags = ATOMIC_READ(target->t_flags);
	if unlikely(target_flags & TASK_FTERMINATED) {
		if (completed)
			sig_altbroadcast(completed, TASK_ASYNC_RPC_SIGALT_TERMINATED);
		return state;
	}
	target->t_sched.s_state = task_push_asynchronous_srpc(target->t_sched.s_state,
	                                                      func, arg, completed);
	if (target_flags & TASK_FRUNNING) {
		/* Running thread */
		cpu_assert_running(target);
		if (target != THIS_TASK) {
			struct task *caller, *next;
			/* Re-schedule the thread to execute as soon as possible. */
			target->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = target->t_sched.s_running.sr_runnxt;
			target->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = target->t_sched.s_running.sr_runprv;
insert_target_after_caller:
			caller                              = THIS_TASK;
			next                                = caller->t_sched.s_running.sr_runnxt;
			target->t_sched.s_running.sr_runprv = caller;
			target->t_sched.s_running.sr_runnxt = next;
			caller->t_sched.s_running.sr_runnxt = target;
			next->t_sched.s_running.sr_runprv   = target;
			ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
			cpu_assert_running(target);
			return CPU_IPI_MODE_SWITCH_TASKS;
		}
	} else if (!(target_flags & TASK_FPENDING)) {
		/* Wake up a sleeping thread by using a sporadic wake-up. */
		cpu_assert_sleeping(target);
		ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
		if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
			target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
		goto insert_target_after_caller;
	}
	return state;
}
#endif

PUBLIC NOBLOCK NONNULL((1, 2)) bool
NOTHROW(KCALL task_schedule_asynchronous_srpc)(struct task *__restrict target, task_srpc_t func,
                                               void *arg, uintptr_t mode, struct sig *completed) {
	pflag_t was;
#ifndef CONFIG_NO_SMP
	struct cpu *mycpu;
	struct cpu *target_cpu;
	was        = PREEMPTION_PUSHOFF();
	mycpu      = THIS_CPU;
	target_cpu = ATOMIC_READ(target->t_cpu);
	if (mycpu != target_cpu) {
		void *args[CPU_IPI_ARGCOUNT];
		args[0] = target;
		args[1] = (void *)func;
		args[2] = arg;
		args[3] = completed;
		while (!cpu_sendipi(target_cpu,
		                    ((mode & TASK_RPC_FDONTWAKE)
		                     ? &ipi_schedule_asynchronous_srpc_dw
		                     : (mode & TASK_RPC_FLOWPRIO)
		                       ? &ipi_schedule_asynchronous_srpc_lp
		                       : (mode & TASK_RPC_FHIGHPRIO)
		                         ? &ipi_schedule_asynchronous_srpc_hp
		                         : &ipi_schedule_asynchronous_srpc),
		                    args,
		                    CPU_IPI_FWAKEUP | (mode & TASK_RPC_FWAITFOR)))
			task_pause();
		PREEMPTION_POP(was);
	} else
#endif /* !CONFIG_NO_SMP */
	{
		uintptr_t target_flags;
#ifdef CONFIG_NO_SMP
		was = PREEMPTION_PUSHOFF();
#endif /* CONFIG_NO_SMP */
		/* ASYNC RPC to-be delivered to our own CPU */
		if unlikely(target == THIS_TASK) {
			PREEMPTION_POP(was);
			/* Execute the RPC immediately. */
			(*func)(arg);
			if (completed)
				sig_broadcast(completed);
			return true;
		}
		/* Deliver the RPC to another thread on our own CPU. */
		target_flags = target->t_flags;
		if (target_flags & TASK_FTERMINATED) {
			PREEMPTION_POP(was);
			return false;
		}
		target->t_sched.s_state = task_push_asynchronous_srpc(target->t_sched.s_state,
		                                                      func, arg, completed);
		if (mode & TASK_RPC_FDONTWAKE)
			goto done_success;
		if (target_flags & TASK_FRUNNING) {
			/* Running thread */
			cpu_assert_running(target);
			if (!(mode & TASK_RPC_FLOWPRIO) && target != THIS_TASK) {
				struct task *caller, *next;
				/* Re-schedule the thread to execute as soon as possible. */
				target->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = target->t_sched.s_running.sr_runnxt;
				target->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = target->t_sched.s_running.sr_runprv;
insert_target_after_caller:
				caller                              = THIS_TASK;
				next                                = caller->t_sched.s_running.sr_runnxt;
				target->t_sched.s_running.sr_runprv = caller;
				target->t_sched.s_running.sr_runnxt = next;
				caller->t_sched.s_running.sr_runnxt = target;
				next->t_sched.s_running.sr_runprv   = target;
				ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
				cpu_assert_running(target);
				if (PREEMPTION_WASENABLED(was)) {
					if (mode & TASK_RPC_FHIGHPRIO) {
						/* End the current quantum prematurely. */
						cpu_quantum_end();
						/* Immediately switch to the next target thread. */
#ifndef CONFIG_NO_SMP
						mycpu->c_current = target;
#else
						_bootcpu.c_current = target;
#endif
						cpu_run_current_and_remember(caller);
					}
					PREEMPTION_ENABLE();
				}
				return true;
			}
		}
#ifndef CONFIG_NO_SMP
		else if (!(target_flags & TASK_FPENDING))
#else /* !CONFIG_NO_SMP */
		else
#endif /* CONFIG_NO_SMP */
		{
			/* Wake up a sleeping thread by using a sporadic wake-up. */
			assert(target != THIS_TASK);
			cpu_assert_sleeping(target);
			ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
			if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
				target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
			goto insert_target_after_caller;
		}
done_success:
		PREEMPTION_POP(was);
	}
	return true;
}





#ifndef CONFIG_NO_SMP
struct dat_exec_asynchronous_rpc {
	task_rpc_t   ar_func;
	void        *ar_arg;
	uintptr_t    ar_mode;
	struct sig  *ar_completed;
	volatile int ar_status;
#define EXEC_ASYNC_STATUS_PENDING    0x0000 /* The RPC is still pending scheduling. */
#define EXEC_ASYNC_STATUS_CONFIRMED  0x0001 /* The RPC has been confirmed. */
#define EXEC_ASYNC_STATUS_TERMINATED 0x0002 /* The RPC has failed because the target has terminated. */
#define EXEC_ASYNC_STATUS_CORECHANGE 0x0003 /* The target thread has moved to a different core (retry). */
};

PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL ipi_exec_asynchronous_rpc)(struct icpustate *__restrict state,
                                         void *args[CPU_IPI_ARGCOUNT]) {
	struct task *target;
	uintptr_t target_flags;
	struct dat_exec_asynchronous_rpc *data;
	struct cpu *target_cpu, *mycpu = THIS_CPU;
	target     = (struct task *)args[0];
	data       = (struct dat_exec_asynchronous_rpc *)args[1];
	target_cpu = ATOMIC_READ(target->t_cpu);
	if unlikely(mycpu != target_cpu) {
		COMPILER_BARRIER();
		ATOMIC_WRITE(data->ar_status, EXEC_ASYNC_STATUS_CORECHANGE);
		COMPILER_BARRIER();
		return state;
	}
	if (target == THIS_TASK) {
		task_rpc_t func = data->ar_func;
		void *arg       = data->ar_arg;
		COMPILER_BARRIER();
		ATOMIC_WRITE(data->ar_status, EXEC_ASYNC_STATUS_CORECHANGE);
		COMPILER_BARRIER();
		return (*func)(arg, state,
		               ICPUSTATE_ISANYUSER(*state)
		               ? TASK_RPC_REASON_ASYNCUSER
		               : TASK_RPC_REASON_ASYNC,
		               NULL);
	}
	target_flags = ATOMIC_READ(target->t_flags);
	if unlikely(target_flags & TASK_FTERMINATED) {
		COMPILER_BARRIER();
		ATOMIC_WRITE(data->ar_status, EXEC_ASYNC_STATUS_TERMINATED);
		COMPILER_BARRIER();
		return state;
	}
	target->t_sched.s_state = task_push_asynchronous_rpc(target->t_sched.s_state,
	                                                     data->ar_func,
	                                                     data->ar_arg,
	                                                     data->ar_completed);
	if (data->ar_mode & TASK_RPC_FDONTWAKE)
		goto done_success;
	if (target_flags & TASK_FRUNNING) {
		/* Running thread */
		cpu_assert_running(target);
		if (!(data->ar_mode & TASK_RPC_FLOWPRIO) && target != THIS_TASK) {
			struct task *caller, *next;
			/* Re-schedule the thread to execute as soon as possible. */
			target->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = target->t_sched.s_running.sr_runnxt;
			target->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = target->t_sched.s_running.sr_runprv;
insert_target_after_caller:
			caller                              = THIS_TASK;
			next                                = caller->t_sched.s_running.sr_runnxt;
			target->t_sched.s_running.sr_runprv = caller;
			target->t_sched.s_running.sr_runnxt = next;
			caller->t_sched.s_running.sr_runnxt = target;
			next->t_sched.s_running.sr_runprv   = target;
			ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
			cpu_assert_running(target);
			if (data->ar_mode & TASK_RPC_FHIGHPRIO) {
				COMPILER_BARRIER();
				ATOMIC_WRITE(data->ar_status, EXEC_ASYNC_STATUS_CONFIRMED);
				COMPILER_BARRIER();
				return CPU_IPI_MODE_SWITCH_TASKS;
			}
		}
	} else if (!(target_flags & TASK_FPENDING)) {
		/* Wake up a sleeping thread by using a sporadic wake-up. */
		cpu_assert_sleeping(target);
		ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
		if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
			target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
		goto insert_target_after_caller;
	}
done_success:
	COMPILER_BARRIER();
	ATOMIC_WRITE(data->ar_status, EXEC_ASYNC_STATUS_CONFIRMED);
	COMPILER_BARRIER();
	return state;
}

PUBLIC NOBLOCK_IF(!PREEMPTION_ENABLED()) NONNULL((1, 2)) bool
NOTHROW(KCALL task_exec_asynchronous_rpc)(struct task *__restrict target, task_rpc_t func,
                                          void *arg, uintptr_t mode, struct sig *completed) {
	pflag_t was;
	struct cpu *mycpu;
	struct cpu *target_cpu;
	was   = PREEMPTION_PUSHOFF();
	mycpu = THIS_CPU;
again:
	target_cpu = ATOMIC_READ(target->t_cpu);
	if (mycpu != target_cpu) {
		void *args[CPU_IPI_ARGCOUNT];
		struct dat_exec_asynchronous_rpc data;
		int final_state;
		data.ar_func      = func;
		data.ar_arg       = arg;
		data.ar_mode      = mode;
		data.ar_completed = completed;
		data.ar_status    = EXEC_ASYNC_STATUS_PENDING;
		args[0]           = target;
		args[1]           = &data;
		while (!cpu_sendipi(target_cpu,
		                    &ipi_exec_asynchronous_rpc,
		                    args,
		                    CPU_IPI_FWAKEUP | (mode & TASK_RPC_FWAITFOR)))
			task_pause();
		if (PREEMPTION_WASENABLED(was)) {
			PREEMPTION_ENABLE();
			while ((final_state = ATOMIC_READ(data.ar_status)) == EXEC_ASYNC_STATUS_PENDING)
				task_yield();
		} else {
			while ((final_state = ATOMIC_READ(data.ar_status)) == EXEC_ASYNC_STATUS_PENDING)
				task_pause();
		}
		/* Check if the IPI failed because the target thread changed cores */
		if unlikely(final_state == EXEC_ASYNC_STATUS_CORECHANGE)
			goto again;
		return final_state == EXEC_ASYNC_STATUS_CONFIRMED;
	} else {
		uintptr_t target_flags;
		/* ASYNC RPC to-be delivered to our own CPU */
		if unlikely(target == THIS_TASK) {
			PREEMPTION_POP(was);
			/* Execute the RPC immediately. */
			task_rpc_exec_here(func, arg, completed);
			return true;
		}
		/* Deliver the RPC to another thread on our own CPU. */
		target_flags = target->t_flags;
		if (target_flags & TASK_FTERMINATED) {
			PREEMPTION_POP(was);
			return false;
		}
		target->t_sched.s_state = task_push_asynchronous_rpc(target->t_sched.s_state,
		                                                     func, arg, completed);
		if (mode & TASK_RPC_FDONTWAKE)
			goto done_success;
		if (target_flags & TASK_FRUNNING) {
			/* Running thread */
			cpu_assert_running(target);
			if (!(mode & TASK_RPC_FLOWPRIO) && target != THIS_TASK) {
				struct task *caller, *next;
				/* Re-schedule the thread to execute as soon as possible. */
				target->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = target->t_sched.s_running.sr_runnxt;
				target->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = target->t_sched.s_running.sr_runprv;
insert_target_after_caller:
				caller                              = THIS_TASK;
				next                                = caller->t_sched.s_running.sr_runnxt;
				target->t_sched.s_running.sr_runprv = caller;
				target->t_sched.s_running.sr_runnxt = next;
				caller->t_sched.s_running.sr_runnxt = target;
				next->t_sched.s_running.sr_runprv   = target;
				ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
				cpu_assert_running(target);
				if (PREEMPTION_WASENABLED(was)) {
					if (mode & TASK_RPC_FHIGHPRIO) {
						/* End the current quantum prematurely. */
						cpu_quantum_end();
						/* Immediately switch to the next target thread. */
						mycpu->c_current = target;
						cpu_run_current_and_remember(caller);
					}
					PREEMPTION_ENABLE();
				}
				return true;
			}
		} else if (!(target_flags & TASK_FPENDING)) {
			/* Wake up a sleeping thread by using a sporadic wake-up. */
			assert(target != THIS_TASK);
			cpu_assert_sleeping(target);
			ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
			assert(target->t_sched.s_asleep.ss_pself);
			if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
				target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
			goto insert_target_after_caller;
		}
done_success:
		PREEMPTION_POP(was);
	}
	return true;
}


struct dat_exec_asynchronous_srpc {
	task_srpc_t  ar_func;
	void        *ar_arg;
	uintptr_t    ar_mode;
	struct sig  *ar_completed;
	volatile int ar_status;
};

PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL ipi_exec_asynchronous_srpc)(struct icpustate *__restrict state,
                                          void *args[CPU_IPI_ARGCOUNT]) {
	struct task *target;
	uintptr_t target_flags;
	struct dat_exec_asynchronous_srpc *data;
	struct cpu *target_cpu, *mycpu = THIS_CPU;
	target     = (struct task *)args[0];
	data       = (struct dat_exec_asynchronous_srpc *)args[1];
	target_cpu = ATOMIC_READ(target->t_cpu);
	if unlikely(mycpu != target_cpu) {
		COMPILER_BARRIER();
		ATOMIC_WRITE(data->ar_status, EXEC_ASYNC_STATUS_CORECHANGE);
		COMPILER_BARRIER();
		return state;
	}
	if (target == THIS_TASK) {
		task_srpc_t func = data->ar_func;
		void *arg        = data->ar_arg;
		COMPILER_BARRIER();
		ATOMIC_WRITE(data->ar_status, EXEC_ASYNC_STATUS_CORECHANGE);
		COMPILER_BARRIER();
		(*func)(arg);
		return state;
	}
	target_flags = ATOMIC_READ(target->t_flags);
	if unlikely(target_flags & TASK_FTERMINATED) {
		COMPILER_BARRIER();
		ATOMIC_WRITE(data->ar_status, EXEC_ASYNC_STATUS_TERMINATED);
		COMPILER_BARRIER();
		return state;
	}
	target->t_sched.s_state = task_push_asynchronous_srpc(target->t_sched.s_state,
	                                                      data->ar_func,
	                                                      data->ar_arg,
	                                                      data->ar_completed);
	if (data->ar_mode & TASK_RPC_FDONTWAKE)
		goto done_success;
	if (target_flags & TASK_FRUNNING) {
		/* Running thread */
		cpu_assert_running(target);
		if (!(data->ar_mode & TASK_RPC_FLOWPRIO) && target != THIS_TASK) {
			struct task *caller, *next;
			/* Re-schedule the thread to execute as soon as possible. */
			target->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = target->t_sched.s_running.sr_runnxt;
			target->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = target->t_sched.s_running.sr_runprv;
insert_target_after_caller:
			caller                              = THIS_TASK;
			next                                = caller->t_sched.s_running.sr_runnxt;
			target->t_sched.s_running.sr_runprv = caller;
			target->t_sched.s_running.sr_runnxt = next;
			caller->t_sched.s_running.sr_runnxt = target;
			next->t_sched.s_running.sr_runprv   = target;
			ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
			cpu_assert_running(target);
			if (data->ar_mode & TASK_RPC_FHIGHPRIO) {
				COMPILER_BARRIER();
				ATOMIC_WRITE(data->ar_status, EXEC_ASYNC_STATUS_CONFIRMED);
				COMPILER_BARRIER();
				return CPU_IPI_MODE_SWITCH_TASKS;
			}
		}
	} else if (!(target_flags & TASK_FPENDING)) {
		/* Wake up a sleeping thread by using a sporadic wake-up. */
		cpu_assert_sleeping(target);
		ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
		if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
			target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
		goto insert_target_after_caller;
	}
done_success:
	COMPILER_BARRIER();
	ATOMIC_WRITE(data->ar_status, EXEC_ASYNC_STATUS_CONFIRMED);
	COMPILER_BARRIER();
	return state;
}

PUBLIC NOBLOCK_IF(!PREEMPTION_ENABLED()) NONNULL((1, 2)) bool
NOTHROW(KCALL task_exec_asynchronous_srpc)(struct task *__restrict target, task_srpc_t func,
                                           void *arg, uintptr_t mode, struct sig *completed) {
	pflag_t was;
	struct cpu *mycpu;
	struct cpu *target_cpu;
	was   = PREEMPTION_PUSHOFF();
	mycpu = THIS_CPU;
again:
	target_cpu = ATOMIC_READ(target->t_cpu);
	if (mycpu != target_cpu) {
		void *args[CPU_IPI_ARGCOUNT];
		struct dat_exec_asynchronous_srpc data;
		int final_state;
		data.ar_func      = func;
		data.ar_arg       = arg;
		data.ar_mode      = mode;
		data.ar_completed = completed;
		data.ar_status    = EXEC_ASYNC_STATUS_PENDING;
		args[0]           = target;
		args[1]           = &data;
		while (!cpu_sendipi(target_cpu,
		                    &ipi_exec_asynchronous_srpc,
		                    args,
		                    CPU_IPI_FWAKEUP | (mode & TASK_RPC_FWAITFOR)))
			task_pause();
		if (PREEMPTION_WASENABLED(was)) {
			PREEMPTION_ENABLE();
			while ((final_state = ATOMIC_READ(data.ar_status)) == EXEC_ASYNC_STATUS_PENDING)
				task_yield();
		} else {
			while ((final_state = ATOMIC_READ(data.ar_status)) == EXEC_ASYNC_STATUS_PENDING)
				task_pause();
		}
		/* Check if the IPI failed because the target thread changed cores */
		if unlikely(final_state == EXEC_ASYNC_STATUS_CORECHANGE)
			goto again;
		return final_state == EXEC_ASYNC_STATUS_CONFIRMED;
	} else {
		uintptr_t target_flags;
		/* ASYNC SRPC to-be delivered to our own CPU */
		if unlikely(target == THIS_TASK) {
			PREEMPTION_POP(was);
			/* Execute the SRPC immediately. */
			(*func)(arg);
			if (completed)
				sig_broadcast(completed);
			return true;
		}
		/* Deliver the SRPC to another thread on our own CPU. */
		target_flags = target->t_flags;
		if (target_flags & TASK_FTERMINATED) {
			PREEMPTION_POP(was);
			return false;
		}
		target->t_sched.s_state = task_push_asynchronous_srpc(target->t_sched.s_state,
		                                                      func, arg, completed);
		if (mode & TASK_RPC_FDONTWAKE)
			goto done_success;
		if (target_flags & TASK_FRUNNING) {
			/* Running thread */
			cpu_assert_running(target);
			if (!(mode & TASK_RPC_FLOWPRIO) && target != THIS_TASK) {
				struct task *caller, *next;
				/* Re-schedule the thread to execute as soon as possible. */
				target->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = target->t_sched.s_running.sr_runnxt;
				target->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = target->t_sched.s_running.sr_runprv;
insert_target_after_caller:
				caller                              = THIS_TASK;
				next                                = caller->t_sched.s_running.sr_runnxt;
				target->t_sched.s_running.sr_runprv = caller;
				target->t_sched.s_running.sr_runnxt = next;
				caller->t_sched.s_running.sr_runnxt = target;
				next->t_sched.s_running.sr_runprv   = target;
				ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
				cpu_assert_running(target);
				if (PREEMPTION_WASENABLED(was)) {
					if (mode & TASK_RPC_FHIGHPRIO) {
						/* End the current quantum prematurely. */
						cpu_quantum_end();
						/* Immediately switch to the next target thread. */
						mycpu->c_current = target;
						cpu_run_current_and_remember(caller);
					}
					PREEMPTION_ENABLE();
				}
				return true;
			}
		} else if (!(target_flags & TASK_FPENDING)) {
			/* Wake up a sleeping thread by using a sporadic wake-up. */
			assert(target != THIS_TASK);
			cpu_assert_sleeping(target);
			ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
			if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
				target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
			goto insert_target_after_caller;
		}
done_success:
		PREEMPTION_POP(was);
	}
	return true;
}
#else /* !CONFIG_NO_SMP */
DEFINE_PUBLIC_ALIAS(task_exec_asynchronous_rpc, task_schedule_asynchronous_rpc);
DEFINE_PUBLIC_ALIAS(task_exec_asynchronous_srpc, task_schedule_asynchronous_srpc);
#endif /* CONFIG_NO_SMP */





#ifndef CONFIG_NO_SMP
struct dat_exec_asynchronous_rpc_v {
	task_rpc_t   ar_func;
	void const  *ar_buf;
	size_t       ar_bufsize;
	uintptr_t    ar_mode;
	struct sig  *ar_completed;
	volatile int ar_status;
};

PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL ipi_exec_asynchronous_rpc_v)(struct icpustate *__restrict state,
                                           void *args[CPU_IPI_ARGCOUNT]) {
	struct task *target;
	uintptr_t target_flags;
	struct dat_exec_asynchronous_rpc_v *data;
	struct cpu *target_cpu, *mycpu = THIS_CPU;
	target     = (struct task *)args[0];
	data       = (struct dat_exec_asynchronous_rpc_v *)args[1];
	target_cpu = ATOMIC_READ(target->t_cpu);
	if unlikely(mycpu != target_cpu) {
		COMPILER_BARRIER();
		ATOMIC_WRITE(data->ar_status, EXEC_ASYNC_STATUS_CORECHANGE);
		COMPILER_BARRIER();
		return state;
	}
	if (target == THIS_TASK) {
		/* execute the RPC function right now (after copying the argument buffer). */
		task_rpc_t func = data->ar_func;
		void *buf       = alloca(data->ar_bufsize);
		memcpy(buf, data->ar_buf, data->ar_bufsize);
		COMPILER_BARRIER();
		ATOMIC_WRITE(data->ar_status, EXEC_ASYNC_STATUS_CORECHANGE);
		COMPILER_BARRIER();
		return (*func)(buf, state, ICPUSTATE_ISANYUSER(*state) ? TASK_RPC_REASON_ASYNCUSER : TASK_RPC_REASON_ASYNC,
		               NULL);
	}
	target_flags = ATOMIC_READ(target->t_flags);
	if unlikely(target_flags & TASK_FTERMINATED) {
		COMPILER_BARRIER();
		ATOMIC_WRITE(data->ar_status, EXEC_ASYNC_STATUS_TERMINATED);
		COMPILER_BARRIER();
		return state;
	}
	target->t_sched.s_state = task_push_asynchronous_rpc_v(target->t_sched.s_state,
	                                                       data->ar_func,
	                                                       data->ar_buf,
	                                                       data->ar_bufsize,
	                                                       data->ar_completed);
	if (data->ar_mode & TASK_RPC_FDONTWAKE)
		goto done_success;
	if (target_flags & TASK_FRUNNING) {
		/* Running thread */
		cpu_assert_running(target);
		if (!(data->ar_mode & TASK_RPC_FLOWPRIO) && target != THIS_TASK) {
			struct task *caller, *next;
			/* Re-schedule the thread to execute as soon as possible. */
			target->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = target->t_sched.s_running.sr_runnxt;
			target->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = target->t_sched.s_running.sr_runprv;
insert_target_after_caller:
			caller                              = THIS_TASK;
			next                                = caller->t_sched.s_running.sr_runnxt;
			target->t_sched.s_running.sr_runprv = caller;
			target->t_sched.s_running.sr_runnxt = next;
			caller->t_sched.s_running.sr_runnxt = target;
			next->t_sched.s_running.sr_runprv   = target;
			ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
			cpu_assert_running(target);
			if (data->ar_mode & TASK_RPC_FHIGHPRIO) {
				COMPILER_BARRIER();
				ATOMIC_WRITE(data->ar_status, EXEC_ASYNC_STATUS_CONFIRMED);
				COMPILER_BARRIER();
				return CPU_IPI_MODE_SWITCH_TASKS;
			}
		}
	} else if (!(target_flags & TASK_FPENDING)) {
		/* Wake up a sleeping thread by using a sporadic wake-up. */
		cpu_assert_sleeping(target);
		ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
		if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
			target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
		goto insert_target_after_caller;
	}
done_success:
	COMPILER_BARRIER();
	ATOMIC_WRITE(data->ar_status, EXEC_ASYNC_STATUS_CONFIRMED);
	COMPILER_BARRIER();
	return state;
}
#endif /* !CONFIG_NO_SMP */

PUBLIC NOBLOCK_IF(!PREEMPTION_ENABLED()) NONNULL((1, 2)) bool
NOTHROW(KCALL task_exec_asynchronous_rpc_v)(struct task *__restrict target, task_rpc_t func,
                                            void const *buf, size_t bufsize, uintptr_t mode,
                                            struct sig *completed) {
	pflag_t was;
#ifndef CONFIG_NO_SMP
	struct cpu *mycpu;
	struct cpu *target_cpu;
	was   = PREEMPTION_PUSHOFF();
	mycpu = THIS_CPU;
again:
	target_cpu = ATOMIC_READ(target->t_cpu);
	if (mycpu != target_cpu) {
		void *args[CPU_IPI_ARGCOUNT];
		struct dat_exec_asynchronous_rpc_v data;
		int final_state;
		data.ar_func      = func;
		data.ar_buf       = buf;
		data.ar_bufsize   = bufsize;
		data.ar_mode      = mode;
		data.ar_completed = completed;
		data.ar_status    = EXEC_ASYNC_STATUS_PENDING;
		args[0]           = target;
		args[1]           = &data;
		while (!cpu_sendipi(target_cpu,
		                    &ipi_exec_asynchronous_rpc_v,
		                    args,
		                    CPU_IPI_FWAKEUP | (mode & TASK_RPC_FWAITFOR)))
			task_pause();
		if (PREEMPTION_WASENABLED(was)) {
			PREEMPTION_ENABLE();
			while ((final_state = ATOMIC_READ(data.ar_status)) == EXEC_ASYNC_STATUS_PENDING)
				task_yield();
		} else {
			while ((final_state = ATOMIC_READ(data.ar_status)) == EXEC_ASYNC_STATUS_PENDING)
				task_pause();
		}
		/* Check if the IPI failed because the target thread changed cores */
		if unlikely(final_state == EXEC_ASYNC_STATUS_CORECHANGE)
			goto again;
		return final_state == EXEC_ASYNC_STATUS_CONFIRMED;
	} else
#endif /* !CONFIG_NO_SMP */
	{
		uintptr_t target_flags;
#ifdef CONFIG_NO_SMP
		was = PREEMPTION_PUSHOFF();
#endif /* CONFIG_NO_SMP */
		/* ASYNC RPC to-be delivered to our own CPU */
		if unlikely(target == THIS_TASK) {
			PREEMPTION_POP(was);
			/* Execute the RPC immediately. */
			task_rpc_exec_here(func, (void *)buf, completed);
			return true;
		}
		/* Deliver the RPC to another thread on our own CPU. */
		target_flags = target->t_flags;
		if (target_flags & TASK_FTERMINATED) {
			PREEMPTION_POP(was);
			return false;
		}
		if (mode & TASK_RPC_FDONTWAKE)
			goto done_success;
		target->t_sched.s_state = task_push_asynchronous_rpc_v(target->t_sched.s_state,
		                                                       func, buf, bufsize, completed);
		if (target_flags & TASK_FRUNNING) {
			/* Running thread */
			cpu_assert_running(target);
			if (!(mode & TASK_RPC_FLOWPRIO) && target != THIS_TASK) {
				struct task *caller, *next;
				/* Re-schedule the thread to execute as soon as possible. */
				target->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = target->t_sched.s_running.sr_runnxt;
				target->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = target->t_sched.s_running.sr_runprv;
insert_target_after_caller:
				caller                              = THIS_TASK;
				next                                = caller->t_sched.s_running.sr_runnxt;
				target->t_sched.s_running.sr_runprv = caller;
				target->t_sched.s_running.sr_runnxt = next;
				caller->t_sched.s_running.sr_runnxt = target;
				next->t_sched.s_running.sr_runprv   = target;
				ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
				cpu_assert_running(target);
				if (PREEMPTION_WASENABLED(was)) {
					if (mode & TASK_RPC_FHIGHPRIO) {
						/* End the current quantum prematurely. */
						cpu_quantum_end();
						/* Immediately switch to the next target thread. */
#ifndef CONFIG_NO_SMP
						mycpu->c_current = target;
#else
						_bootcpu.c_current = target;
#endif
						cpu_run_current_and_remember(caller);
					}
					PREEMPTION_ENABLE();
				}
				return true;
			}
		}
#ifndef CONFIG_NO_SMP
		else if (!(target_flags & TASK_FPENDING))
#else /* !CONFIG_NO_SMP */
		else
#endif /* CONFIG_NO_SMP */
		{
			/* Wake up a sleeping thread by using a sporadic wake-up. */
			assert(target != THIS_TASK);
			cpu_assert_sleeping(target);
			ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
			if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
				target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
			goto insert_target_after_caller;
		}
done_success:
		PREEMPTION_POP(was);
	}
	return true;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_RPC_ASYNC_C */
