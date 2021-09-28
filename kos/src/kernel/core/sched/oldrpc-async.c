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
#ifndef GUARD_KERNEL_SRC_SCHED_OLDRPC_ASYNC_C
#define GUARD_KERNEL_SRC_SCHED_OLDRPC_ASYNC_C 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_RPC
#include <kernel/except.h>
#include <kernel/types.h>
#include <sched/cpu.h>
#include <sched/rpc.h>
#include <sched/scheduler.h>
#include <sched/signal.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>

#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <alloca.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#define WAS_START_AND_IS_NOT_PENDING(f) (((f) & TASK_FSTARTED) != 0)
#define WAS_START_AND_IS_SLEEPING(f)    (((f) & (TASK_FRUNNING | TASK_FSTARTED)) == TASK_FSTARTED)

#ifdef CONFIG_NO_SMP
#define IFELSE_SMP(if_smp, if_no_smp) if_no_smp
#else /* CONFIG_NO_SMP */
#define IFELSE_SMP(if_smp, if_no_smp) if_smp
#endif /* !CONFIG_NO_SMP */


#ifndef CONFIG_NO_SMP
PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL ipi_schedule_asynchronous_rpc)(struct icpustate *__restrict state,
                                             void *args[CPU_IPI_ARGCOUNT]) {
	REF struct task *target;
	struct cpu *me, *target_cpu;
	struct task *caller;
	task_rpc_t func;
	void *arg;
	uintptr_t mode;
	uintptr_t target_flags;
	func   = (task_rpc_t)args[1];
	arg    = args[2];
	caller = THIS_TASK;
	target = (REF struct task *)args[0];
	mode   = (uintptr_t)args[3];
	if (target == caller) {
		struct icpustate *result;
		result = (*func)(arg, state,
		                 icpustate_isuser(state)
		                 ? TASK_RPC_REASON_ASYNCUSER
		                 : TASK_RPC_REASON_ASYNC,
		                 NULL);
		decref_nokill(target);
		return result;
	}
	target_flags = ATOMIC_READ(target->t_flags);
	if unlikely(target_flags & TASK_FTERMINATED) {
		state = (*func)(arg, state, TASK_RPC_REASON_SHUTDOWN, NULL);
		decref(target);
		return state;
	}
	target_cpu = ATOMIC_READ(target->t_cpu);
	me         = caller->t_cpu;
	if unlikely(target_cpu != me) {
		/* Re-deliver the IPI to yet another CPU (letting it bounce until we get it right) */
		while (!cpu_sendipi(target_cpu,
		                    &ipi_schedule_asynchronous_rpc, args,
		                    CPU_IPI_FWAKEUP))
			task_pause();
		return state;
	}
	{
		struct scpustate *target_state;
		target_state = FORTASK(target, this_sstate);
		target_state = task_push_asynchronous_rpc(target_state, func, arg);
		FORTASK(target, this_sstate) = target_state;
	}
	if (!(mode & TASK_RPC_FDONTWAKE) && caller != target) {
		struct task *next_thread;
		next_thread = sched_intern_localwake(IFELSE_SMP(me, &bootcpu),
		                                     caller, target,
		                                     (mode & TASK_RPC_FHIGHPRIO) != 0);
		if (next_thread != caller) {
			FORCPU(me, thiscpu_sched_current) = next_thread;
			decref_unlikely(target);
			return CPU_IPI_MODE_SWITCH_TASKS;
		}
	}
	decref_unlikely(target);
	return state;
}



PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL ipi_redirect_usercode_rpc)(struct icpustate *__restrict state,
                                         void *args[CPU_IPI_ARGCOUNT]) {
	REF struct task *target;
	struct cpu *me, *target_cpu;
	struct task *caller;
	uintptr_t target_flags;
	uintptr_t mode;
	target       = (REF struct task *)args[0];
	mode         = (uintptr_t)args[1];
	target_flags = ATOMIC_READ(target->t_flags);
	if unlikely(target_flags & TASK_FTERMINATED) {
		/* TODO: What now?
		 *       Our  caller is `task_redirect_usercode_rpc()',  which may return `false'
		 *       to indicate this  error condition.  However since this  IPI is  serviced
		 *       asynchronously, we only get here when that function has already returned
		 *       to its caller, indicating success... */
		decref(target);
		return state;
	}
	caller     = THIS_TASK;
	me         = caller->t_cpu;
	target_cpu = ATOMIC_READ(target->t_cpu);
	if unlikely(target_cpu != me) {
		/* Re-deliver the IPI to yet another CPU (letting it bounce until we get it right) */
		while (!cpu_sendipi(target_cpu,
		                    &ipi_redirect_usercode_rpc,
		                    args, /* inherit:reference:target */
		                    CPU_IPI_FWAKEUP))
			task_pause();
		return state;
	}
	task_enable_redirect_usercode_rpc(target);
	if (!(mode & TASK_RPC_FDONTWAKE) && caller != target) {
		struct task *next_thread;
		next_thread = sched_intern_localwake(IFELSE_SMP(me, &bootcpu),
		                                     caller, target,
		                                     (mode & TASK_RPC_FHIGHPRIO) != 0);
		if (next_thread != caller) {
			FORCPU(me, thiscpu_sched_current) = next_thread;
			decref_unlikely(target);
			return CPU_IPI_MODE_SWITCH_TASKS;
		}
	}
	decref_unlikely(target);
	return state;
}
#endif /* !CONFIG_NO_SMP */





/* High-level variant of `task_enable_redirect_usercode_rpc':
 * This function automatically performs all of the necessary locking, checks and IPIs
 * in order to execute `task_enable_redirect_usercode_rpc()' for `target' within  the
 * proper context.
 * NOTE: This function also causes a sporadic wakeup for `target', irregardless of
 *       usercode already having been redirected, having the same effect as a call
 *       to `task_wake()'.
 * @return: true:  Successfully redirected the given thread (though it may have
 *                 already been redirected before).
 * @return: false: The RPC could not be scheduled because `target' has terminated.
 *        WARNING: The target may still terminate before the RPC can be serviced,
 *                 though  this  has to  be  detected in  some  different manner. */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL task_redirect_usercode_rpc)(struct task *__restrict target, uintptr_t mode) {
	pflag_t was;
#ifndef CONFIG_NO_SMP
	struct cpu *me;
	struct cpu *target_cpu;
	was        = PREEMPTION_PUSHOFF();
	me         = THIS_CPU;
	target_cpu = ATOMIC_READ(target->t_cpu);
	if (me != target_cpu) {
		void *args[CPU_IPI_ARGCOUNT];
		args[0] = (void *)incref(target);
		args[1] = (void *)mode;
		while (!cpu_sendipi(target_cpu,
		                    &ipi_redirect_usercode_rpc, args,
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
		if (!(mode & TASK_RPC_FDONTWAKE) && caller != target) {
			target = sched_intern_localwake(IFELSE_SMP(me, &bootcpu),
			                                caller, target,
			                                (mode & TASK_RPC_FHIGHPRIO) != 0 &&
			                                PREEMPTION_WASENABLED(was));
			if (target != caller) {
				/* Immediately switch to the next target thread. */
				FORCPU(IFELSE_SMP(me, &bootcpu), thiscpu_sched_current) = target;
				cpu_run_current_and_remember_nopr(caller);
			}
		}
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
	struct cpu *me;
	struct cpu *target_cpu;
	was        = PREEMPTION_PUSHOFF();
	me         = THIS_CPU;
	target_cpu = ATOMIC_READ(target->t_cpu);
	if (me != target_cpu) {
		void *args[CPU_IPI_ARGCOUNT];
		args[0] = incref(target);
		args[1] = (void *)func;
		args[2] = arg;
		args[3] = (void *)(uintptr_t)mode;
		while (!cpu_sendipi(target_cpu,
		                    &ipi_schedule_asynchronous_rpc, args,
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
		{
			struct scpustate *target_state;
			target_state = FORTASK(target, this_sstate);
			target_state = task_push_asynchronous_rpc(target_state, func, arg);
			FORTASK(target, this_sstate) = target_state;
		}
		if (!(mode & TASK_RPC_FDONTWAKE) && caller != target) {
			target = sched_intern_localwake(IFELSE_SMP(me, &bootcpu),
			                                caller, target,
			                                (mode & TASK_RPC_FHIGHPRIO) != 0 &&
			                                PREEMPTION_WASENABLED(was));
			if (target != caller) {
				/* Immediately switch to the next target thread. */
				FORCPU(IFELSE_SMP(me, &bootcpu), thiscpu_sched_current) = target;
				cpu_run_current_and_remember_nopr(caller);
			}
		}
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
	struct task *caller;
	struct cpu *me;
	caller     = THIS_TASK;
	me         = caller->t_cpu;
	target     = (struct task *)args[0];
	data       = (struct dat_exec_asynchronous_rpc *)args[1];
	target_cpu = ATOMIC_READ(target->t_cpu);
	if unlikely(me != target_cpu) {
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
	{
		struct scpustate *target_state;
		target_state = FORTASK(target, this_sstate);
		target_state = task_push_asynchronous_rpc(target_state,
		                                          data->ar_func,
		                                          data->ar_arg);
		FORTASK(target, this_sstate) = target_state;
	}
	if (!(data->ar_mode & TASK_RPC_FDONTWAKE) && caller != target) {
		target = sched_intern_localwake(IFELSE_SMP(me, &bootcpu),
		                                caller, target,
		                                data->ar_mode & TASK_RPC_FHIGHPRIO);
		if (target != caller) {
			COMPILER_BARRIER();
			ATOMIC_WRITE(data->ar_status, EXEC_ASYNC_STATUS_CONFIRMED);
			COMPILER_BARRIER();
			FORCPU(me, thiscpu_sched_current) = target;
			return CPU_IPI_MODE_SWITCH_TASKS;
		}
	}
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
	struct cpu *me, *target_cpu;
	was = PREEMPTION_PUSHOFF();
	me  = caller->t_cpu;
again:
	target_cpu = ATOMIC_READ(target->t_cpu);
	if (me != target_cpu) {
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
				task_tryyield();
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
		{
			struct scpustate *target_state;
			target_state = FORTASK(target, this_sstate);
			target_state = task_push_asynchronous_rpc(target_state, func, arg);
			FORTASK(target, this_sstate) = target_state;
		}
		if (!(mode & TASK_RPC_FDONTWAKE) && caller != target) {
			target = sched_intern_localwake(IFELSE_SMP(me, &bootcpu),
			                                caller, target,
			                                (mode & TASK_RPC_FHIGHPRIO) != 0 &&
			                                PREEMPTION_WASENABLED(was));
			if (target != caller) {
				/* Immediately switch to the next target thread. */
				FORCPU(IFELSE_SMP(me, &bootcpu), thiscpu_sched_current) = target;
				cpu_run_current_and_remember_nopr(caller);
			}
		}
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
	struct task *caller;
	struct cpu *me;
	caller     = THIS_TASK;
	me         = caller->t_cpu;
	target     = (struct task *)args[0];
	data       = (struct dat_exec_asynchronous_rpc_v *)args[1];
	target_cpu = ATOMIC_READ(target->t_cpu);
	if unlikely(me != target_cpu) {
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
	{
		struct scpustate *target_state;
		target_state = FORTASK(target, this_sstate);
		target_state = task_push_asynchronous_rpc_v(target_state,
		                                            data->ar_func,
		                                            data->ar_buf,
		                                            data->ar_bufsize);
		FORTASK(target, this_sstate) = target_state;
	}
	if (!(data->ar_mode & TASK_RPC_FDONTWAKE) && caller != target) {
		target = sched_intern_localwake(IFELSE_SMP(me, &bootcpu),
		                                caller, target,
		                                data->ar_mode & TASK_RPC_FHIGHPRIO);
		if (target != caller) {
			COMPILER_BARRIER();
			ATOMIC_WRITE(data->ar_status, EXEC_ASYNC_STATUS_CONFIRMED);
			COMPILER_BARRIER();
			FORCPU(me, thiscpu_sched_current) = target;
			return CPU_IPI_MODE_SWITCH_TASKS;
		}
	}
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
	struct cpu *me, *target_cpu;
	was = PREEMPTION_PUSHOFF();
	me  = THIS_CPU;
again:
	target_cpu = ATOMIC_READ(target->t_cpu);
	if (me != target_cpu) {
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
				task_tryyield();
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
		{
			struct scpustate *target_state;
			target_state = FORTASK(target, this_sstate);
			target_state = task_push_asynchronous_rpc_v(target_state,
			                                            func, buf, bufsize);
			FORTASK(target, this_sstate) = target_state;
		}
		if (!(mode & TASK_RPC_FDONTWAKE) && caller != target) {
			target = sched_intern_localwake(IFELSE_SMP(me, &bootcpu),
			                                caller, target,
			                                (mode & TASK_RPC_FHIGHPRIO) != 0 &&
			                                PREEMPTION_WASENABLED(was));
			if (target != caller) {
				/* Immediately switch to the next target thread. */
				FORCPU(IFELSE_SMP(me, &bootcpu), thiscpu_sched_current) = target;
				cpu_run_current_and_remember_nopr(caller);
			}
		}
		PREEMPTION_POP(was);
	}
	return true;
}

DECL_END
#endif /* !CONFIG_USE_NEW_RPC */

#endif /* !GUARD_KERNEL_SRC_SCHED_OLDRPC_ASYNC_C */
