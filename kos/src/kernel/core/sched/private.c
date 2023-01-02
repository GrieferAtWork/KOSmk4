/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_SCHED_PRIVATE_C
#define GUARD_KERNEL_SRC_SCHED_PRIVATE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/panic.h>
#include <kernel/types.h>
#include <sched/cpu.h>
#include <sched/private.h>
#include <sched/sig.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/sched/preemption.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#ifndef CONFIG_NO_SMP
struct cpf_rtdata {
	WEAK uintptr_half_t             cpf_refcnt; /* Reference counter. */
	uintptr_half_t                  cpf_finish; /* Set to non-zero once the CPF is finished. */
	struct sig                      cpf_done;   /* Signal broadcast when `cpf_refcnt' hits `1'. */
	COMPILER_FLEXIBLE_ARRAY(byte_t, cpf_data);  /* User-provided buffer. */
};
DEFINE_REFCNT_FUNCTIONS(struct cpf_rtdata, cpf_refcnt, kfree)


#define CPF_IPI_RTDATA 0
#define CPF_IPI_FUNC   1
#define CPF_IPI_THREAD 2

PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL cpf_ipi)(struct icpustate *__restrict state,
                       void *args[CPU_IPI_ARGCOUNT]) {
	struct cpf_rtdata *rt;
	cpu_private_function_t func;
	struct task *thread;
	struct cpu *target_cpu;
	rt     = (struct cpf_rtdata *)args[CPF_IPI_RTDATA];
	func   = (cpu_private_function_t)args[CPF_IPI_FUNC];
	thread = (struct task *)args[CPF_IPI_THREAD];
	assert(rt->cpf_refcnt == 2);
	/* Read the CPU field _once_ since it might change before the next read. */
	target_cpu = ATOMIC_READ(thread->t_cpu);
	if unlikely(target_cpu != THIS_CPU) {
		while (!cpu_sendipi(target_cpu, &cpf_ipi, args, CPU_IPI_FWAKEUP))
			preemption_tryyield_nopr();
	} else {
		/* Invoke the accessor function */
		(*func)(rt->cpf_data, thread);
		/* Signal service completion. */
		ATOMIC_WRITE(rt->cpf_finish, 1);
		sig_broadcast(&rt->cpf_done);
		decref_unlikely(rt);
	}
	return state;
}
#endif /* !CONFIG_NO_SMP */


/* Call a given `func' in a context such that thread-private variables of `thread'
 * can be read, and following variable-specific restrictions, may potentially also
 * be writable.
 * This is done by ensuring that `func' is run:
 *  - While preemption is disabled
 *  - From some arbitrary  thread hosted by  `thread->t_cpu' at  the
 *    time that `func' is invoked (which is guarantied to not change
 *    because preemption is disabled)
 *    WARNING: When `func' is called, there is a possibility
 *             that `thread == THIS_TASK'
 * If `thread' is hosted by a different CPU, an IPI will be scheduled for execution
 * on said CPU. It is the allocation of a reference-counted control structure  that
 * has  to be shared with the target CPU in this scenario that may potentially fail
 * due to an allocation  failure. Note that this  control structure is required  to
 * safely handle the case of the original thread getting interrupted such that this
 * function will return by throwing an `E_INTERRUPT' exception.
 * This function is most useful for accessing private registers caches of  `thread'
 * from an arbitrary, different thread, such as the x86-specific `x86_get_irregs()'
 * @param: thread:    The thread who's private variables the caller wishes to access.
 * @param: func:      The function used to access `thread's private variables.
 * @param: stack_buf: A buffer of `bufsize'  bytes that is allocated  in the caller's kernel  stack.
 *                    This buffer is passed to `func()' when `thread' is hosted by the caller's CPU.
 *                    When  `thread'  is hosted  by  a different  CPU,  a reference  counted control
 *                    structure containing  sufficient space  for `bufsize'  is allocated  and  pre-
 *                    initialized with the contents of `stack_buf'.  Following this, an IPI is  used
 *                    to invoke `func' in the context  of `thread->t_cpu', whilst passing a  pointer
 *                    to  the memory-copy of this buffer to  `func()', before the return of `func()'
 *                    will cause the  original caller of  `cpu_call_private_function()' to wake  up,
 *                    at  which  the  same  pointer  previously  passed  to  `func()'  is  returned.
 *                    The caller must always clean up this pointer via a call to
 *                    `cpu_private_function_finibuf_ex()', which will free() a dynamically allocated
 *                    buffer, unless the buffer wasn't dynamically allocated.
 * @param: bufsize:   Size of `stack_buf'
 * @param: bufalign:  Alignment requirements of `stack_buf' */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) void *KCALL
cpu_private_function_callbuf_ex(struct task *__restrict thread,
                                cpu_private_function_t func, void *stack_buf,
                                size_t bufsize, size_t bufalign)
		THROWS(E_BADALLOC, E_INTERRUPT) {
	preemption_flag_t was;
#ifndef CONFIG_NO_SMP
	struct cpu *thread_cpu;
#endif /* !CONFIG_NO_SMP */
	(void)bufsize;
	(void)bufalign;
	assert(IS_ALIGNED((uintptr_t)stack_buf, bufalign));
	preemption_pushoff(&was);
#ifndef CONFIG_NO_SMP
	thread_cpu = ATOMIC_READ(thread->t_cpu);
	if (thread_cpu != THIS_CPU) {
		struct cpf_rtdata *rt;
		void *args[CPU_IPI_ARGCOUNT];
		preemption_pop(&was);
		if (bufalign < alignof(struct cpf_rtdata))
			bufalign = alignof(struct cpf_rtdata);
		rt = (struct cpf_rtdata *)kmemalign_offset(bufalign,
		                                           offsetof(struct cpf_rtdata, cpf_data),
		                                           offsetof(struct cpf_rtdata, cpf_data) + bufsize,
		                                           GFP_LOCKED | GFP_PREFLT);
		memcpy(rt->cpf_data, stack_buf, bufsize);
		rt->cpf_refcnt = 2;
		rt->cpf_finish = 0;
		sig_init(&rt->cpf_done);
		args[CPF_IPI_RTDATA] = rt;
		args[CPF_IPI_FUNC]   = (void *)func;
		args[CPF_IPI_THREAD] = thread;
		/* Re-acquire the preemption lock and check that `thread's cpu hasn't changed. */
		preemption_pushoff(&was);
		thread_cpu = ATOMIC_READ(thread->t_cpu);
		if unlikely(thread_cpu == THIS_CPU) {
			kfree(rt);
			goto do_service_directly;
		}
		while (!cpu_sendipi(thread_cpu, &cpf_ipi, args,
		                    CPU_IPI_FWAKEUP | CPU_IPI_FWAITFOR))
			preemption_tryyield_nopr();
		preemption_pop(&was);
		TRY {
			/* Now wait for the function to be serviced. */
			while (!ATOMIC_READ(rt->cpf_finish)) {
				task_connect_for_poll(&rt->cpf_done);
				/* Do the interlocked check */
				if unlikely(ATOMIC_READ(rt->cpf_finish)) {
					task_disconnectall();
					break;
				}
				task_waitfor();
			}
		} EXCEPT {
			/* Drop our reference from the RT controller. */
			decref_unlikely(rt);
			RETHROW();
		}
		return rt->cpf_data;
	}
do_service_directly:
#endif /* !CONFIG_NO_SMP */
	/* Service directly. */
	(*func)(stack_buf, thread);
	preemption_pop(&was);
	return stack_buf;
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL cpu_private_function_do_finibuf_ex)(void *used_buf) {
#ifdef CONFIG_NO_SMP
	(void)used_buf;
	kernel_panic("Should not get here without SMP");
#else /* CONFIG_NO_SMP */
	struct cpf_rtdata *rt;
	rt = container_of((byte_t *)used_buf, struct cpf_rtdata, cpf_data[0]);
	decref_likely(rt);
#endif /* !CONFIG_NO_SMP */
}


/* Simplified variant of `cpu_private_function_callbuf_ex()':
 * >> cpu_private_function_call() {
 * >>     void *ptr;
 * >>     ptr = cpu_private_function_callbuf_ex(thread, func, stack_buf, bufsize, bufalign);
 * >>     if (ptr != stack_buf)
 * >>         memcpy(stack_buf, ptr, bufsize);
 * >>     cpu_private_function_finibuf_ex(ptr, stack_buf);
 * >> }
 */
#ifdef CONFIG_NO_SMP
DEFINE_PUBLIC_ALIAS(cpu_private_function_callbuf, cpu_private_function_callbuf_ex);
#else /* CONFIG_NO_SMP */
PUBLIC NONNULL((1, 2)) void KCALL
cpu_private_function_callbuf(struct task *__restrict thread,
                          cpu_private_function_t func, void *stack_buf,
                          size_t bufsize, size_t bufalign)
		THROWS(E_BADALLOC, E_INTERRUPT) {
	void *ptr;
	ptr = cpu_private_function_callbuf_ex(thread, func, stack_buf, bufsize, bufalign);
	if (ptr != stack_buf) {
		memcpy(stack_buf, ptr, bufsize);
		cpu_private_function_do_finibuf_ex(ptr);
	}
}
#endif /* !CONFIG_NO_SMP */




DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_PRIVATE_C */
