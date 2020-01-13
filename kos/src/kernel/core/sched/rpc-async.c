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
#include <sched/signal.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <alloca.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#ifndef CONFIG_NO_SMP
#define WAS_START_AND_IS_NOT_PENDING(f) (((f) & (TASK_FPENDING | TASK_FSTARTED)) == TASK_FSTARTED)
#define WAS_START_AND_IS_SLEEPING(f)    (((f) & (TASK_FRUNNING | TASK_FPENDING | TASK_FSTARTED)) == TASK_FSTARTED)
#else /* !CONFIG_NO_SMP */
#define WAS_START_AND_IS_NOT_PENDING(f) (((f) & TASK_FSTARTED) != 0)
#define WAS_START_AND_IS_SLEEPING(f)    (((f) & (TASK_FRUNNING | TASK_FSTARTED)) == TASK_FSTARTED)
#endif /* CONFIG_NO_SMP */


#ifdef CONFIG_NO_SMP
#define IFELSE_SMP(if_smp, if_no_smp) if_no_smp
#else /* CONFIG_NO_SMP */
#define IFELSE_SMP(if_smp, if_no_smp) if_smp
#endif /* !CONFIG_NO_SMP */


#ifndef CONFIG_NO_SMP
#ifndef __INTELLISENSE__
DECL_END

#define DEFINE_SCHEDIPI_RPC_DW 1
#include "rpc-async-schedipi.c.inl"
#define DEFINE_SCHEDIPI_RPC_LP 1
#include "rpc-async-schedipi.c.inl"
#define DEFINE_SCHEDIPI_RPC_HP 1
#include "rpc-async-schedipi.c.inl"
#define DEFINE_SCHEDIPI_RPC    1
#include "rpc-async-schedipi.c.inl"

DECL_BEGIN
#else /* !__INTELLISENSE__ */

PRIVATE NOBLOCK struct icpustate *NOTHROW(FCALL ipi_schedule_asynchronous_rpc_dw)(struct icpustate *__restrict state, void *args[CPU_IPI_ARGCOUNT]);
PRIVATE NOBLOCK struct icpustate *NOTHROW(FCALL ipi_schedule_asynchronous_rpc_lp)(struct icpustate *__restrict state, void *args[CPU_IPI_ARGCOUNT]);
PRIVATE NOBLOCK struct icpustate *NOTHROW(FCALL ipi_schedule_asynchronous_rpc_hp)(struct icpustate *__restrict state, void *args[CPU_IPI_ARGCOUNT]);
PRIVATE NOBLOCK struct icpustate *NOTHROW(FCALL ipi_schedule_asynchronous_rpc)(struct icpustate *__restrict state, void *args[CPU_IPI_ARGCOUNT]);

PRIVATE NOBLOCK struct icpustate *NOTHROW(FCALL ipi_redirect_usercode_rpc_dw)(struct icpustate *__restrict state, void *args[CPU_IPI_ARGCOUNT]);
PRIVATE NOBLOCK struct icpustate *NOTHROW(FCALL ipi_redirect_usercode_rpc_lp)(struct icpustate *__restrict state, void *args[CPU_IPI_ARGCOUNT]);
PRIVATE NOBLOCK struct icpustate *NOTHROW(FCALL ipi_redirect_usercode_rpc_hp)(struct icpustate *__restrict state, void *args[CPU_IPI_ARGCOUNT]);
PRIVATE NOBLOCK struct icpustate *NOTHROW(FCALL ipi_redirect_usercode_rpc)(struct icpustate *__restrict state, void *args[CPU_IPI_ARGCOUNT]);

#endif /* __INTELLISENSE__ */

#define IPI_FUNCTION_OF_MODE(mode, name) \
	(((mode)&TASK_RPC_FDONTWAKE)         \
	 ? &name##_dw                        \
	 : ((mode)&TASK_RPC_FLOWPRIO)        \
	   ? &name##_lp                      \
	   : ((mode)&TASK_RPC_FHIGHPRIO)     \
	     ? &name##_hp                    \
	     : &name)
#endif /* !CONFIG_NO_SMP */





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
		cpu_ipi_t ipifunc;
		args[0] = (void *)target;
		args[1] = (void *)mode;
		ipifunc = IPI_FUNCTION_OF_MODE(mode, ipi_redirect_usercode_rpc);
		while (!cpu_sendipi(target_cpu,
		                    ipifunc,
		                    args,
		                    CPU_IPI_FWAKEUP))
			task_pause();
		PREEMPTION_POP(was);
	} else
#endif /* !CONFIG_NO_SMP */
	{
		uintptr_t target_flags;
		struct task *caller = THIS_TASK;
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
			if (!(mode & TASK_RPC_FLOWPRIO) && target != caller) {
				struct task *next;
				/* Re-schedule the thread to execute as soon as possible. */
				target->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = target->t_sched.s_running.sr_runnxt;
				target->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = target->t_sched.s_running.sr_runprv;
insert_target_after_caller:
				next   = caller->t_sched.s_running.sr_runnxt;
				target->t_sched.s_running.sr_runprv = caller;
				target->t_sched.s_running.sr_runnxt = next;
				caller->t_sched.s_running.sr_runnxt = target;
				next->t_sched.s_running.sr_runprv   = target;
				ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
				cpu_assert_running(target);
				if (PREEMPTION_WASENABLED(was)) {
					if ((mode & TASK_RPC_FHIGHPRIO) &&
					    IFELSE_SMP((*mycpu), _bootcpu).c_override != caller) {
						/* End the current quantum prematurely. */
						cpu_quantum_end_nopr();
						/* Immediately switch to the next target thread. */
						IFELSE_SMP((*mycpu), _bootcpu).c_current = target;
						cpu_run_current_and_remember_nopr(caller);
					}
					PREEMPTION_ENABLE();
				}
				return true;
			}
		} else if (WAS_START_AND_IS_NOT_PENDING(target_flags)) {
			/* Wake up a sleeping thread by using a sporadic wake-up. */
			assert(target != caller);
			cpu_assert_sleeping(target);
			ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
			if unlikely(!target->t_sched.s_asleep.ss_pself) {
				/* Special case: The IDLE thread can sleep outside of the sleepers chain */
#ifndef CONFIG_NO_SMP
				assert(target == &FORCPU(mycpu, thiscpu_idle));
#else /* !CONFIG_NO_SMP */
				assert(target == &PERCPU(thiscpu_idle));
#endif /* CONFIG_NO_SMP */
			} else {
				if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
					target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
			}
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
NOTHROW(KCALL task_schedule_asynchronous_rpc)(struct task *__restrict target,
                                              task_rpc_t func,
                                              void *arg,
                                              uintptr_t mode) {
	pflag_t was;
#ifndef CONFIG_NO_SMP
	struct cpu *mycpu;
	struct cpu *target_cpu;
	was        = PREEMPTION_PUSHOFF();
	mycpu      = THIS_CPU;
	target_cpu = ATOMIC_READ(target->t_cpu);
	if (mycpu != target_cpu) {
		void *args[CPU_IPI_ARGCOUNT];
		cpu_ipi_t ipifunc;
		args[0] = target;
		args[1] = (void *)func;
		args[2] = arg;
		ipifunc = IPI_FUNCTION_OF_MODE(mode, ipi_schedule_asynchronous_rpc);
		while (!cpu_sendipi(target_cpu,
		                    ipifunc,
		                    args,
		                    CPU_IPI_FWAKEUP |
		                    (mode & TASK_RPC_FWAITFOR)))
			task_pause();
		PREEMPTION_POP(was);
	} else
#endif /* !CONFIG_NO_SMP */
	{
		uintptr_t target_flags;
		struct task *caller = THIS_TASK;
#ifdef CONFIG_NO_SMP
		was = PREEMPTION_PUSHOFF();
#endif /* CONFIG_NO_SMP */
		/* ASYNC RPC to-be delivered to our own CPU */
		if unlikely(target == caller) {
			PREEMPTION_POP(was);
			/* Execute the RPC immediately. */
			task_rpc_exec_here(func, arg);
			return true;
		}
		/* Deliver the RPC to another thread on our own CPU. */
		target_flags = target->t_flags;
		if (target_flags & TASK_FTERMINATED) {
			PREEMPTION_POP(was);
			return false;
		}
		target->t_sched.s_state = task_push_asynchronous_rpc(target->t_sched.s_state,
		                                                     func, arg);
		if (mode & TASK_RPC_FDONTWAKE)
			goto done_success;
		if (target_flags & TASK_FRUNNING) {
			/* Running thread */
			cpu_assert_running(target);
			if (!(mode & TASK_RPC_FLOWPRIO)) {
				struct task *next;
				/* Re-schedule the thread to execute as soon as possible. */
				target->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = target->t_sched.s_running.sr_runnxt;
				target->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = target->t_sched.s_running.sr_runprv;
insert_target_after_caller:
				next = caller->t_sched.s_running.sr_runnxt;
				target->t_sched.s_running.sr_runprv = caller;
				target->t_sched.s_running.sr_runnxt = next;
				caller->t_sched.s_running.sr_runnxt = target;
				next->t_sched.s_running.sr_runprv   = target;
				ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
				cpu_assert_running(target);
				if (PREEMPTION_WASENABLED(was)) {
					if ((mode & TASK_RPC_FHIGHPRIO) &&
					    IFELSE_SMP((*mycpu), _bootcpu).c_override != caller) {
						/* End the current quantum prematurely. */
						cpu_quantum_end_nopr();
						/* Immediately switch to the next target thread. */
						IFELSE_SMP((*mycpu), _bootcpu).c_current = target;
						cpu_run_current_and_remember_nopr(caller);
					}
					PREEMPTION_ENABLE();
				}
				return true;
			}
		} else if (WAS_START_AND_IS_NOT_PENDING(target_flags)) {
			/* Wake up a sleeping thread by using a sporadic wake-up. */
			cpu_assert_sleeping(target);
			ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
			if unlikely(!target->t_sched.s_asleep.ss_pself) {
				/* Special case: The IDLE thread can sleep outside of the sleepers chain */
#ifndef CONFIG_NO_SMP
				assert(target == &FORCPU(mycpu, thiscpu_idle));
#else /* !CONFIG_NO_SMP */
				assert(target == &PERCPU(thiscpu_idle));
#endif /* CONFIG_NO_SMP */
			} else {
				if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
					target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
			}
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
	struct cpu *target_cpu;
	struct task *caller = THIS_TASK;
	struct cpu *mycpu   = caller->t_cpu;
	target     = (struct task *)args[0];
	data       = (struct dat_exec_asynchronous_rpc *)args[1];
	target_cpu = ATOMIC_READ(target->t_cpu);
	if unlikely(mycpu != target_cpu) {
		COMPILER_BARRIER();
		ATOMIC_WRITE(data->ar_status, EXEC_ASYNC_STATUS_CORECHANGE);
		COMPILER_BARRIER();
		return state;
	}
	if (target == caller) {
		task_rpc_t func = data->ar_func;
		void *arg       = data->ar_arg;
		COMPILER_BARRIER();
		ATOMIC_WRITE(data->ar_status, EXEC_ASYNC_STATUS_CORECHANGE);
		COMPILER_BARRIER();
		state = (*func)(arg, state,
		                icpustate_isuser(state)
		                ? TASK_RPC_REASON_ASYNCUSER
		                : TASK_RPC_REASON_ASYNC,
		                NULL);
		return state;
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
	                                                     data->ar_arg);
	if (data->ar_mode & TASK_RPC_FDONTWAKE)
		goto done_success;
	if (target_flags & TASK_FRUNNING) {
		/* Running thread */
		cpu_assert_running(target);
		if (!(data->ar_mode & TASK_RPC_FLOWPRIO)) {
			struct task *next;
			/* Re-schedule the thread to execute as soon as possible. */
			target->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = target->t_sched.s_running.sr_runnxt;
			target->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = target->t_sched.s_running.sr_runprv;
insert_target_after_caller:
			next = caller->t_sched.s_running.sr_runnxt;
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
				mycpu->c_current = target;
				return CPU_IPI_MODE_SWITCH_TASKS;
			}
		}
	} else if (WAS_START_AND_IS_NOT_PENDING(target_flags)) {
		/* Wake up a sleeping thread by using a sporadic wake-up. */
		cpu_assert_sleeping(target);
		ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
		if unlikely(!target->t_sched.s_asleep.ss_pself) {
			/* Special case: The IDLE thread can sleep outside of the sleepers chain */
			assert(target == &FORCPU(mycpu, thiscpu_idle));
		} else {
			if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
				target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
		}
		goto insert_target_after_caller;
	}
done_success:
	COMPILER_BARRIER();
	ATOMIC_WRITE(data->ar_status, EXEC_ASYNC_STATUS_CONFIRMED);
	COMPILER_BARRIER();
	return state;
}

PUBLIC NOBLOCK_IF(!PREEMPTION_ENABLED()) NONNULL((1, 2)) bool
NOTHROW(KCALL task_exec_asynchronous_rpc)(struct task *__restrict target,
                                          task_rpc_t func,
                                          void *arg,
                                          uintptr_t mode) {
	pflag_t was;
	struct task *caller = THIS_TASK;
	struct cpu *mycpu, *target_cpu;
	was   = PREEMPTION_PUSHOFF();
	mycpu = caller->t_cpu;
again:
	target_cpu = ATOMIC_READ(target->t_cpu);
	if (mycpu != target_cpu) {
		void *args[CPU_IPI_ARGCOUNT];
		struct dat_exec_asynchronous_rpc data;
		int final_state;
		data.ar_func   = func;
		data.ar_arg    = arg;
		data.ar_mode   = mode;
		data.ar_status = EXEC_ASYNC_STATUS_PENDING;
		args[0]        = target;
		args[1]        = &data;
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
		if unlikely(target == caller) {
			PREEMPTION_POP(was);
			/* Execute the RPC immediately. */
			task_rpc_exec_here(func, arg);
			return true;
		}
		/* Deliver the RPC to another thread on our own CPU. */
		target_flags = target->t_flags;
		if (target_flags & TASK_FTERMINATED) {
			PREEMPTION_POP(was);
			return false;
		}
		target->t_sched.s_state = task_push_asynchronous_rpc(target->t_sched.s_state,
		                                                     func, arg);
		if (mode & TASK_RPC_FDONTWAKE)
			goto done_success;
		if (target_flags & TASK_FRUNNING) {
			/* Running thread */
			cpu_assert_running(target);
			if (!(mode & TASK_RPC_FLOWPRIO)) {
				struct task *next;
				/* Re-schedule the thread to execute as soon as possible. */
				target->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = target->t_sched.s_running.sr_runnxt;
				target->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = target->t_sched.s_running.sr_runprv;
insert_target_after_caller:
				next = caller->t_sched.s_running.sr_runnxt;
				target->t_sched.s_running.sr_runprv = caller;
				target->t_sched.s_running.sr_runnxt = next;
				caller->t_sched.s_running.sr_runnxt = target;
				next->t_sched.s_running.sr_runprv   = target;
				ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
				cpu_assert_running(target);
				if (PREEMPTION_WASENABLED(was)) {
					if ((mode & TASK_RPC_FHIGHPRIO) &&
					    mycpu->c_override != caller) {
						/* End the current quantum prematurely. */
						cpu_quantum_end_nopr();
						/* Immediately switch to the next target thread. */
						mycpu->c_current = target;
						cpu_run_current_and_remember_nopr(caller);
					}
					PREEMPTION_ENABLE();
				}
				return true;
			}
		} else if (WAS_START_AND_IS_NOT_PENDING(target_flags)) {
			/* Wake up a sleeping thread by using a sporadic wake-up. */
			cpu_assert_sleeping(target);
			ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
			assert(target->t_sched.s_asleep.ss_pself);
			if unlikely(!target->t_sched.s_asleep.ss_pself) {
				/* Special case: The IDLE thread can sleep outside of the sleepers chain */
				assert(target == &FORCPU(mycpu, thiscpu_idle));
			} else {
				if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
					target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
			}
			goto insert_target_after_caller;
		}
done_success:
		PREEMPTION_POP(was);
	}
	return true;
}
#else /* !CONFIG_NO_SMP */
DEFINE_PUBLIC_ALIAS(task_exec_asynchronous_rpc, task_schedule_asynchronous_rpc);
#endif /* CONFIG_NO_SMP */





#ifndef CONFIG_NO_SMP
struct dat_exec_asynchronous_rpc_v {
	task_rpc_t   ar_func;
	void const  *ar_buf;
	size_t       ar_bufsize;
	uintptr_t    ar_mode;
	volatile int ar_status;
};

PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL ipi_exec_asynchronous_rpc_v)(struct icpustate *__restrict state,
                                           void *args[CPU_IPI_ARGCOUNT]) {
	struct task *target;
	uintptr_t target_flags;
	struct dat_exec_asynchronous_rpc_v *data;
	struct cpu *target_cpu;
	struct task *caller = THIS_TASK;
	struct cpu *mycpu   = caller->t_cpu;
	target     = (struct task *)args[0];
	data       = (struct dat_exec_asynchronous_rpc_v *)args[1];
	target_cpu = ATOMIC_READ(target->t_cpu);
	if unlikely(mycpu != target_cpu) {
		COMPILER_BARRIER();
		ATOMIC_WRITE(data->ar_status, EXEC_ASYNC_STATUS_CORECHANGE);
		COMPILER_BARRIER();
		return state;
	}
	if (target == caller) {
		/* execute the RPC function right now (after copying the argument buffer). */
		task_rpc_t func = data->ar_func;
		void *buf       = alloca(data->ar_bufsize);
		memcpy(buf, data->ar_buf, data->ar_bufsize);
		COMPILER_BARRIER();
		ATOMIC_WRITE(data->ar_status, EXEC_ASYNC_STATUS_CORECHANGE);
		COMPILER_BARRIER();
		state = (*func)(buf,
		                state,
		                icpustate_isuser(state) ? TASK_RPC_REASON_ASYNCUSER
		                                        : TASK_RPC_REASON_ASYNC,
		                NULL);
		return state;
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
	                                                       data->ar_bufsize);
	if (data->ar_mode & TASK_RPC_FDONTWAKE)
		goto done_success;
	if (target_flags & TASK_FRUNNING) {
		/* Running thread */
		cpu_assert_running(target);
		if (!(data->ar_mode & TASK_RPC_FLOWPRIO)) {
			struct task *next;
			/* Re-schedule the thread to execute as soon as possible. */
			target->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = target->t_sched.s_running.sr_runnxt;
			target->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = target->t_sched.s_running.sr_runprv;
insert_target_after_caller:
			next = caller->t_sched.s_running.sr_runnxt;
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
				mycpu->c_current = target;
				return CPU_IPI_MODE_SWITCH_TASKS;
			}
		}
	} else if (WAS_START_AND_IS_NOT_PENDING(target_flags)) {
		/* Wake up a sleeping thread by using a sporadic wake-up. */
		cpu_assert_sleeping(target);
		ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
		if unlikely(!target->t_sched.s_asleep.ss_pself) {
			/* Special case: The IDLE thread can sleep outside of the sleepers chain */
			assert(target == &FORCPU(mycpu, thiscpu_idle));
		} else {
			if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
				target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
		}
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
NOTHROW(KCALL task_exec_asynchronous_rpc_v)(struct task *__restrict target,
                                            task_rpc_t func,
                                            void const *buf,
                                            size_t bufsize,
                                            uintptr_t mode) {
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
		data.ar_func    = func;
		data.ar_buf     = buf;
		data.ar_bufsize = bufsize;
		data.ar_mode    = mode;
		data.ar_status  = EXEC_ASYNC_STATUS_PENDING;
		args[0]         = target;
		args[1]         = &data;
		while (!cpu_sendipi(target_cpu,
		                    &ipi_exec_asynchronous_rpc_v,
		                    args,
		                    CPU_IPI_FWAKEUP |
		                    (mode & TASK_RPC_FWAITFOR)))
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
		struct task *caller = THIS_TASK;
#ifdef CONFIG_NO_SMP
		was = PREEMPTION_PUSHOFF();
#endif /* CONFIG_NO_SMP */
		/* ASYNC RPC to-be delivered to our own CPU */
		if unlikely(target == caller) {
			PREEMPTION_POP(was);
			/* Execute the RPC immediately. */
			task_rpc_exec_here(func, (void *)buf);
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
		                                                       func, buf, bufsize);
		if (target_flags & TASK_FRUNNING) {
			/* Running thread */
			cpu_assert_running(target);
			if (!(mode & TASK_RPC_FLOWPRIO)) {
				struct task *next;
				/* Re-schedule the thread to execute as soon as possible. */
				target->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = target->t_sched.s_running.sr_runnxt;
				target->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = target->t_sched.s_running.sr_runprv;
insert_target_after_caller:
				next = caller->t_sched.s_running.sr_runnxt;
				target->t_sched.s_running.sr_runprv = caller;
				target->t_sched.s_running.sr_runnxt = next;
				caller->t_sched.s_running.sr_runnxt = target;
				next->t_sched.s_running.sr_runprv   = target;
				ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
				cpu_assert_running(target);
				if (PREEMPTION_WASENABLED(was)) {
					if ((mode & TASK_RPC_FHIGHPRIO) &&
					    IFELSE_SMP((*mycpu), _bootcpu).c_override != caller) {
						/* End the current quantum prematurely. */
						cpu_quantum_end_nopr();
						/* Immediately switch to the next target thread. */
						IFELSE_SMP((*mycpu), _bootcpu).c_current = target;
						cpu_run_current_and_remember_nopr(caller);
					}
					PREEMPTION_ENABLE();
				}
				return true;
			}
		} else if (WAS_START_AND_IS_NOT_PENDING(target_flags)) {
			/* Wake up a sleeping thread by using a sporadic wake-up. */
			cpu_assert_sleeping(target);
			ATOMIC_FETCHOR(target->t_flags, TASK_FRUNNING);
			if unlikely(!target->t_sched.s_asleep.ss_pself) {
				/* Special case: The IDLE thread can sleep outside of the sleepers chain */
#ifndef CONFIG_NO_SMP
				assert(target == &FORCPU(mycpu, thiscpu_idle));
#else /* !CONFIG_NO_SMP */
				assert(target == &PERCPU(thiscpu_idle));
#endif /* CONFIG_NO_SMP */
			} else {
				if ((*target->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_tmonxt) != NULL)
					target->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = target->t_sched.s_asleep.ss_pself;
			}
			goto insert_target_after_caller;
		}
done_success:
		PREEMPTION_POP(was);
	}
	return true;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_RPC_ASYNC_C */
