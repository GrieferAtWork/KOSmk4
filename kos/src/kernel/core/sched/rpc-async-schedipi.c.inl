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
#ifdef __INTELLISENSE__
#include "rpc-async.c"
//#define DEFINE_SCHEDIPI_RPC_DW 1 /* TASK_RPC_FDONTWAKE */
//#define DEFINE_SCHEDIPI_RPC_LP 1 /* TASK_RPC_FLOWPRIO */
#define DEFINE_SCHEDIPI_RPC_HP 1 /* TASK_RPC_FHIGHPRIO */
//#define DEFINE_SCHEDIPI_RPC    1 /* TASK_RPC_FNORMAL */
#endif /* __INTELLISENSE__ */


DECL_BEGIN

#ifdef DEFINE_SCHEDIPI_RPC_DW
#define FUNC(x) x##_dw
#elif defined(DEFINE_SCHEDIPI_RPC_LP)
#define FUNC(x) x##_lp
#elif defined(DEFINE_SCHEDIPI_RPC_HP)
#define FUNC(x) x##_hp
#elif defined(DEFINE_SCHEDIPI_RPC)
#define FUNC(x) x
#endif


#ifndef CONFIG_NO_SMP
PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL FUNC(ipi_schedule_asynchronous_rpc))(struct icpustate *__restrict state,
                                                   void *args[CPU_IPI_ARGCOUNT]) {
	struct task *target    = (struct task *)args[0];
	task_rpc_t func        = (task_rpc_t)args[1];
	void *arg              = args[2];
	struct task *caller    = THIS_TASK;
	struct cpu *mycpu      = caller->t_cpu;
	struct cpu *target_cpu = ATOMIC_READ(target->t_cpu);
	uintptr_t target_flags;
	if unlikely(target_cpu != mycpu) {
		/* Re-deliver the IPI to yet another CPU (letting it bounce until we get it right) */
		while (!cpu_sendipi(target_cpu,
		                    &FUNC(ipi_schedule_asynchronous_rpc),
		                    args,
		                    CPU_IPI_FWAKEUP))
			task_pause();
		return state;
	}
	if (target == caller) {
		struct icpustate *result;
		result = (*func)(arg, state,
		                 icpustate_isuser(state)
		                 ? TASK_RPC_REASON_ASYNCUSER
		                 : TASK_RPC_REASON_ASYNC,
		                 NULL);
		return result;
	}
	target_flags = ATOMIC_READ(target->t_flags);
	if unlikely(target_flags & TASK_FTERMINATED) {
		state = (*func)(arg, state, TASK_RPC_REASON_SHUTDOWN, NULL);
		return state;
	}
	target->t_sched.s_state = task_push_asynchronous_rpc(target->t_sched.s_state,
	                                                     func, arg);
#ifdef DEFINE_SCHEDIPI_RPC_LP
	if (WAS_START_AND_IS_SLEEPING(target_flags)) {
		struct task *next;
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
		next = caller->t_sched.s_running.sr_runnxt;
		target->t_sched.s_running.sr_runprv = caller;
		target->t_sched.s_running.sr_runnxt = next;
		caller->t_sched.s_running.sr_runnxt = target;
		next->t_sched.s_running.sr_runprv   = target;
		ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
		cpu_assert_running(target);
	}
#elif defined(DEFINE_SCHEDIPI_RPC_HP) || defined(DEFINE_SCHEDIPI_RPC)
	if (target_flags & TASK_FRUNNING) {
		struct task *next;
		/* Running thread */
		cpu_assert_running(target);
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
#ifdef DEFINE_SCHEDIPI_RPC_HP
		mycpu->c_current = target;
		return CPU_IPI_MODE_SWITCH_TASKS;
#endif /* DEFINE_SCHEDIPI_RPC_HP */
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
#endif
	return state;
}



PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL FUNC(ipi_redirect_usercode_rpc))(struct icpustate *__restrict state,
                                               void *args[CPU_IPI_ARGCOUNT]) {
	struct task *target    = (struct task *)args[0];
	struct task *caller    = THIS_TASK;
	struct cpu *mycpu      = caller->t_cpu;
	struct cpu *target_cpu = ATOMIC_READ(target->t_cpu);
	uintptr_t target_flags;
	if unlikely(target_cpu != mycpu) {
		/* Re-deliver the IPI to yet another CPU (letting it bounce until we get it right) */
		while (!cpu_sendipi(target_cpu,
		                    &FUNC(ipi_redirect_usercode_rpc),
		                    args,
		                    CPU_IPI_FWAKEUP))
			task_pause();
		return state;
	}
	target_flags = ATOMIC_READ(target->t_flags);
	if unlikely(target_flags & TASK_FTERMINATED) {
		/* TODO: What now?
		 *       Our caller is `task_redirect_usercode_rpc()', which may return `false'
		 *       to indicate this error condition. However since this IPI is serviced
		 *       asynchronously, we only get here when that function has already returned
		 *       to its caller, indicating success... */
		return state;
	}
	task_enable_redirect_usercode_rpc(target);
#ifdef DEFINE_SCHEDIPI_RPC_LP
	if (WAS_START_AND_IS_SLEEPING(target_flags)) {
		struct task *next;
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
		next = caller->t_sched.s_running.sr_runnxt;
		target->t_sched.s_running.sr_runprv = caller;
		target->t_sched.s_running.sr_runnxt = next;
		caller->t_sched.s_running.sr_runnxt = target;
		next->t_sched.s_running.sr_runprv   = target;
		ATOMIC_FETCHAND(target->t_flags, ~TASK_FWAKING);
		cpu_assert_running(target);
	}
#elif defined(DEFINE_SCHEDIPI_RPC_HP) || defined(DEFINE_SCHEDIPI_RPC)
	if (target_flags & TASK_FRUNNING) {
		/* Running thread */
		cpu_assert_running(target);
		if (target != caller) {
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
#ifdef DEFINE_SCHEDIPI_RPC_HP
			mycpu->c_current = target;
			return CPU_IPI_MODE_SWITCH_TASKS;
#endif /* DEFINE_SCHEDIPI_RPC_HP */
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
#endif
	return state;
}
#endif /* !CONFIG_NO_SMP */


DECL_END

#undef FUNC
#undef DEFINE_SCHEDIPI_RPC_DW
#undef DEFINE_SCHEDIPI_RPC_LP
#undef DEFINE_SCHEDIPI_RPC_HP
#undef DEFINE_SCHEDIPI_RPC

