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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_IPI_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_IPI_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/x86/apic.h>
#include <kernel/x86/idt.h>
#include <kernel/x86/pit.h>
#include <sched/cpu.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/scheduler.h>
#include <sched/task.h>
#include <sched/x86/smp.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <asm/cpu-flags.h>
#include <sys/io.h>

#include <assert.h>
#include <inttypes.h>
#include <string.h>

#ifndef NDEBUG
#include <kernel/rand.h>
#endif /* !NDEBUG */

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

#if 0
#define IPI_DEBUG(...) (printk(KERN_DEBUG "[cpu:%u] ", THIS_CPU->c_id), printk(KERN_DEBUG __VA_ARGS__))
#else
#define IPI_DEBUG(...) (void)0
#endif


#ifndef CONFIG_NO_SMP

INTERN NOBLOCK void
NOTHROW(KCALL apic_send_init)(u8 procid) {
	lapic_write(APIC_ICR1, APIC_ICR1_MKDEST(procid));
	lapic_write(APIC_ICR0,
	            APIC_ICR0_TYPE_FINIT |
	            APIC_ICR0_DEST_PHYSICAL |
	            APIC_ICR0_FASSERT |
	            APIC_ICR0_TARGET_FICR1);
	while (lapic_read(APIC_ICR0) & APIC_ICR0_FPENDING)
		task_pause();
}

INTERN NOBLOCK void
NOTHROW(KCALL apic_send_startup)(u8 procid, u8 pageno) {
	lapic_write(APIC_ICR1, APIC_ICR1_MKDEST(procid));
	lapic_write(APIC_ICR0, pageno |
	                       APIC_ICR0_TYPE_FSIPI |
	                       APIC_ICR0_DEST_PHYSICAL |
	                       APIC_ICR0_FASSERT |
	                       APIC_ICR0_TARGET_FICR1);
	while (lapic_read(APIC_ICR0) & APIC_ICR0_FPENDING)
		task_pause();
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL send_init_ipi)(struct cpu *__restrict target) {
	pflag_t was;
	assert(target != THIS_CPU);
	/* Make sure that our outgoing interrupt line isn't
	 * still  pending  due to  another,  unrelated IPI. */
	while (lapic_read(APIC_ICR0) & APIC_ICR0_FPENDING)
		task_pause();

	/* Send an INIT IPI to the target CPU. */
	apic_send_init(FORCPU(target, thiscpu_x86_lapicid));

	/* Wait for 10 milliseconds. */
	x86_pit_lock_acquire_smp();
	outb(PIT_PCSPEAKER,
	     (inb(PIT_PCSPEAKER) &
	      ~(PIT_PCSPEAKER_FSYNCPIT | PIT_PCSPEAKER_FINOUT)) |
	     PIT_PCSPEAKER_FSYNCPIT);
	outb(PIT_COMMAND,
	     PIT_COMMAND_SELECT_F2 |
	     PIT_COMMAND_ACCESS_FLOHI |
	     PIT_COMMAND_MODE_FONESHOT);
	/* 1s == 1000ms; 10ms --> 1000/10 --> 100HZ */
	outb_p(PIT_DATA2, (PIT_HZ_DIV(100) & 0xff));
	outb(PIT_DATA2, (PIT_HZ_DIV(100) >> 8) & 0xff);
	{
		u8 temp = inb(PIT_PCSPEAKER) & ~PIT_PCSPEAKER_FINOUT;
		outb(PIT_PCSPEAKER, temp);
		outb(PIT_PCSPEAKER, temp | PIT_PCSPEAKER_OUT);
	}
	while (inb(PIT_PCSPEAKER) & PIT_PCSPEAKER_FPIT2OUT)
		task_pause();
	x86_pit_lock_release_smp();

	/* Send the startup IPI */
	apic_send_startup(FORCPU(target, thiscpu_x86_lapicid), x86_smp_entry_page);

	/* Wait for the other CPU to come online. */
#if 1 /* Best case: The CPU comes online without us having to do another PIT-wait */
	{
		unsigned int poll_timeout = 1000;
		do {
			if (ATOMIC_READ(target->c_state) != CPU_STATE_GETTING_UP)
				return;
		} while (--poll_timeout);
	}
#endif

	/* Explicitly wait for 1 millisecond. */
	was = PREEMPTION_PUSHOFF();
	while (!x86_pit_lock_tryacquire()) {
		if (ATOMIC_READ(target->c_state) != CPU_STATE_GETTING_UP)
			goto done_ppop;
		PREEMPTION_POP(was);
		task_tryyield_or_pause();
		was = PREEMPTION_PUSHOFF();
		if (ATOMIC_READ(target->c_state) != CPU_STATE_GETTING_UP)
			goto done_ppop;
	}
	outb(PIT_PCSPEAKER,
	     (inb(PIT_PCSPEAKER) &
	      ~(PIT_PCSPEAKER_FSYNCPIT | PIT_PCSPEAKER_FINOUT)) |
	     PIT_PCSPEAKER_FSYNCPIT);
	outb(PIT_COMMAND,
	     PIT_COMMAND_SELECT_F2 |
	     PIT_COMMAND_ACCESS_FLOHI |
	     PIT_COMMAND_MODE_FONESHOT);
	/* 1s == 1000ms; 1ms --> 1000/1 --> 1000HZ */
	outb_p(PIT_DATA2, (PIT_HZ_DIV(1000) & 0xff));
	outb(PIT_DATA2, (PIT_HZ_DIV(1000) >> 8) & 0xff);
	{
		u8 temp = inb(PIT_PCSPEAKER) & ~PIT_PCSPEAKER_FINOUT;
		outb(PIT_PCSPEAKER, temp);
		outb(PIT_PCSPEAKER, temp | PIT_PCSPEAKER_OUT);
	}
	while (inb(PIT_PCSPEAKER) & PIT_PCSPEAKER_FPIT2OUT) {
		if (ATOMIC_READ(target->c_state) != CPU_STATE_GETTING_UP) {
done_ppop_endwrite:
			x86_pit_lock_release_nopr();
done_ppop:
			PREEMPTION_POP(was);
			return;
		}
		task_pause();
		if (ATOMIC_READ(target->c_state) != CPU_STATE_GETTING_UP)
			goto done_ppop_endwrite;
	}
	x86_pit_lock_release_nopr();
	PREEMPTION_POP(was);
	if (ATOMIC_READ(target->c_state) != CPU_STATE_GETTING_UP)
		return;

	/* Send the startup IPI again */
	apic_send_startup(FORCPU(target, thiscpu_x86_lapicid), x86_smp_entry_page);

	/* Wait for up to 1 second. */
	was = PREEMPTION_PUSHOFF();
	while (!x86_pit_lock_tryacquire()) {
		if (ATOMIC_READ(target->c_state) != CPU_STATE_GETTING_UP)
			goto done_ppop;
		PREEMPTION_POP(was);
		task_tryyield_or_pause();
		was = PREEMPTION_PUSHOFF();
		if (ATOMIC_READ(target->c_state) != CPU_STATE_GETTING_UP)
			goto done_ppop;
	}
	outb(PIT_PCSPEAKER,
	     (inb(PIT_PCSPEAKER) &
	      ~(PIT_PCSPEAKER_FSYNCPIT | PIT_PCSPEAKER_FINOUT)) |
	     PIT_PCSPEAKER_FSYNCPIT);
	outb(PIT_COMMAND,
	     PIT_COMMAND_SELECT_F2 |
	     PIT_COMMAND_ACCESS_FLOHI |
	     PIT_COMMAND_MODE_FONESHOT);

	/* 1s == 1000ms; 1000ms --> 1000 / 1000 --> 1HZ */
	outb_p(PIT_DATA2, (PIT_HZ_DIV(1) & 0xff));
	outb(PIT_DATA2, (PIT_HZ_DIV(1) >> 8) & 0xff);
	{
		u8 temp = inb(PIT_PCSPEAKER) & ~PIT_PCSPEAKER_FINOUT;
		outb(PIT_PCSPEAKER, temp);
		outb(PIT_PCSPEAKER, temp | PIT_PCSPEAKER_OUT);
	}
	while (inb(PIT_PCSPEAKER) & PIT_PCSPEAKER_FPIT2OUT) {
		if (ATOMIC_READ(target->c_state) != CPU_STATE_GETTING_UP)
			goto done_ppop_endwrite;
		task_pause();
		if (ATOMIC_READ(target->c_state) != CPU_STATE_GETTING_UP)
			goto done_ppop_endwrite;
	}
	x86_pit_lock_release_nopr();
	PREEMPTION_POP(was);
	if (ATOMIC_READ(target->c_state) != CPU_STATE_GETTING_UP)
		return;
	kernel_panic("Failed to re-initialize previously functional CPU #%u (hardware failure?)",
	             target->c_id);
}



struct pending_ipi {
	cpu_ipi_t pi_func;                   /* [1..1] IPI Function. */
	void     *pi_args[CPU_IPI_ARGCOUNT]; /* [?..?][*] Function arguments. */
};

/* Vector of pending IPI. */
/* XXX: This right here makes up 98% of .percpu! You know that, right? */
PRIVATE ATTR_PERCPU struct pending_ipi
thiscpu_x86_ipi_pending[CPU_IPI_BUFFER_SIZE];

/* [lock(SET(ATOMIC, IF_SET_IN(thiscpu_x86_ipi_alloc)),
 *       CLEAR(ATOMIC, THIS_CPU))]
 * Bitset of fully initialized IPIs. */
INTERN ATTR_PERCPU WEAK uintptr_t
thiscpu_x86_ipi_inuse[CEILDIV(CPU_IPI_BUFFER_SIZE, BITS_PER_POINTER)] = { 0, };

/* [lock(SET(ATOMIC), CLEAR(ATOMIC, THIS_CPU, IF_SET_IN(thiscpu_x86_ipi_alloc))
 *                    CLEAR(ATOMIC, <OWNER>, !IF_SET_IN(thiscpu_x86_ipi_alloc)))]
 * Bitset of allocated IPIs. */
PRIVATE ATTR_PERCPU WEAK uintptr_t
thiscpu_x86_ipi_alloc[CEILDIV(CPU_IPI_BUFFER_SIZE, BITS_PER_POINTER)] = { 0, };


/* Check  if  there   are  any  non-interrupting   software-based  IPIs   pending.
 * If some are present, these must be serviced by calling `cpu_ipi_service_nopr()' */
PUBLIC NOBLOCK WUNUSED NOPREEMPT bool
NOTHROW(FCALL arch_cpu_swipi_pending_nopr)(struct cpu *__restrict me) {
	unsigned int i;
	assert(!PREEMPTION_ENABLED());
	for (i = 0; i < CEILDIV(CPU_IPI_BUFFER_SIZE, BITS_PER_POINTER); ++i) {
		if (ATOMIC_READ(FORCPU(me, thiscpu_x86_ipi_inuse[i])) != 0)
			return true;
	}
	return false;
}

INTERN NOPREEMPT NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL x86_serve_ipi)(struct cpu *__restrict me,
                             struct icpustate *__restrict state) {
	unsigned int i, j;
	struct icpustate *new_state;
	struct icpustate *result = state;
	assert(!PREEMPTION_ENABLED());
	IPI_DEBUG("x86_serve_ipi(%p,%p)\n",
	          state, FORCPU(me, thiscpu_sched_current));
	i = CEILDIV(CPU_IPI_BUFFER_SIZE, BITS_PER_POINTER);

	/* Must iterate in reverse, since assembly only checks the first word
	 * of the in-use bitset to  determine if unhandled IPIs are  present. */
	while (i) {
		uintptr_t bits, mask;
		--i;
		bits = ATOMIC_READ(FORCPU(me, thiscpu_x86_ipi_inuse[i]));
		if (!bits)
			continue;
		for (j = 0, mask = 1; bits; ++j, mask <<= 1) {
			unsigned int slot;
			struct pending_ipi ipi;
			if (!(bits & mask))
				continue;

			/* Figure out the absolute allocation slot for the IPI */
			slot = i * BITS_PER_POINTER + j;

			/* Deallocate this IPI. */
			memcpy(&ipi, &FORCPU(me, thiscpu_x86_ipi_pending[slot]), sizeof(ipi));
			DBG_memset(&FORCPU(me, thiscpu_x86_ipi_pending[slot]), 0xcc, sizeof(ipi));

			/* Free up the IPI slot.
			 * This must  happen for  every in-use  slot individually,  since  the
			 * IPI  callback itself may recursively call `cpu_ipi_service_nopr()',
			 * which must be able  to handle any additional  IPIs, and if we  were
			 * to  clear  the in-use  bits for  multiple IPIs  at once,  then we'd
			 * essentially commit to executing all of those IPIs without blocking!
			 *
			 * NOTE: The write order here is also important:
			 *       We must unset  the IPI's  bit in the  IN-USE bitset  first,
			 *       and only then clear  it in the ALLOC  bitset. If we did  it
			 *       the other way  around, then  there might be  a chance  that
			 *       the IPI get allocated immediately, and we'd end up clearing
			 *       a in-use bit of a whole different IPI! */
			ATOMIC_AND(FORCPU(me, thiscpu_x86_ipi_inuse[i]), ~mask);
			ATOMIC_AND(FORCPU(me, thiscpu_x86_ipi_alloc[i]), ~mask);

			/* Execute the IPI callback. */
			IPI_DEBUG("x86_serve_ipi:%p [slot=%u,i=%u,mask=%#" PRIxPTR "]\n",
			          ipi.pi_func, slot, i, mask);
			new_state = (*ipi.pi_func)(state, ipi.pi_args);
			if (CPU_IPI_MODE_ISSPECIAL(new_state)) {
				if ((uintptr_t)result < (uintptr_t)new_state)
					result = new_state;
			} else {
				if unlikely(new_state != state)
					return new_state; /* Switch states. */
			}
			bits &= ~mask;
		}
	}
	return result;
}


PRIVATE NONNULL((1)) void
NOTHROW(PRPC_EXEC_CALLBACK_CC task_rpc_serve_ipi)(struct rpc_context *__restrict ctx,
                                                  void *UNUSED(cookie)) {
	pflag_t was;
	struct cpu *mycpu;
	/* Disable  preemption  to prevent  CPU switches  and to
	 * comply with `x86_serve_ipi()'s NOPREEMPT requirement. */
	was   = PREEMPTION_PUSHOFF();
	mycpu = THIS_CPU;

	/* Serve IPIs */
	ctx->rc_state = x86_serve_ipi(mycpu, ctx->rc_state);
	PREEMPTION_POP(was);
}


/* Modify the  scheduler state  of  `thread' to  have  it
 * service IPIs before resuming what it was doing before. */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL x86_task_push_serve_ipi)(struct task *__restrict thread) {
	struct scpustate *state;
	state = FORTASK(thread, this_sstate);
	state = task_asyncrpc_push(state, &task_rpc_serve_ipi, NULL);
	FORTASK(thread, this_sstate) = state;
}





INTDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL x86_execute_direct_ipi_nopr)(cpu_ipi_t func,
                                           void *args[CPU_IPI_ARGCOUNT]);
INTDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL x86_execute_direct_ipi)(cpu_ipi_t func,
                                      void *args[CPU_IPI_ARGCOUNT]);


/* TODO: Add dedicated `cpu_broadcastipi()' and `cpu_broadcastipi_notthis()'
 *       functions,  which collect a set of CPUs  to signal, and make use of
 *       the BROADCAST / BROADCAST_EXCEPT_SELF functionality found in LAPIC. */

PUBLIC NOBLOCK NONNULL((1, 2, 3)) bool
NOTHROW(KCALL cpu_sendipi)(struct cpu *__restrict target,
                           cpu_ipi_t func, void *args[CPU_IPI_ARGCOUNT],
                           unsigned int flags) {
	unsigned int i, attempt = 0;
	unsigned int slot;
	pflag_t was;
	IPI_DEBUG("cpu_sendipi:%p,%p\n", target, func);
#ifndef NDEBUG
	/* Make it easier for race conditions  related to IPI races to  surface
	 * by randomly introducing a couple of pause instructions, thus causing
	 * the calling CPU to randomly slow down before actually sending an IPI */
	if (krand32() >= UINT32_C(0x80000000)) {
		task_pause();
		task_pause();
	}
#endif /* !NDEBUG */
	was = PREEMPTION_PUSHOFF();
	if (target == THIS_CPU) {
		/* Special case: The current CPU is being targeted. */
		if (flags & CPU_IPI_FNOINTR) {
			x86_execute_direct_ipi_nopr(func, args);
			goto done_success;
		}
		if (PREEMPTION_WASENABLED(was)) {
			x86_execute_direct_ipi(func, args);
			assert(PREEMPTION_ENABLED());
			goto done_success;
		}
		/* Don't  allow sending  an IPI to  our own CPU  when preemption is
		 * disabled. The caller may attempt to send another, at which point
		 * the  `while (lapic_read(APIC_ICR0) & APIC_ICR0_FPENDING)'   loop
		 * below will block indefinitely! */
		goto done_failure;
	}
again:
	for (i = 0; i < CEILDIV(CPU_IPI_BUFFER_SIZE, BITS_PER_POINTER); ++i) {
		uintptr_t word, mask;
		unsigned int j;
again_i:
		word = ATOMIC_READ(FORCPU(target, thiscpu_x86_ipi_alloc[i]));
		if unlikely(word == (uintptr_t)-1)
			continue; /* Word is fully allocated. */
		j    = 0;
		mask = 1;
		while (word & mask) {
			++j;
			mask <<= 1;
		}
		if (!ATOMIC_CMPXCH_WEAK(FORCPU(target, thiscpu_x86_ipi_alloc[i]), word, word | mask)) {
			attempt = 0;
			goto again_i;
		}
		/* Successfully allocated a slot. */
		slot = i * BITS_PER_POINTER + j;
		COMPILER_WRITE_BARRIER();
		FORCPU(target, thiscpu_x86_ipi_pending[slot].pi_func) = func;
		memcpy(FORCPU(target, thiscpu_x86_ipi_pending[slot]).pi_args,
		       args, CPU_IPI_ARGCOUNT, sizeof(void *));
		COMPILER_WRITE_BARRIER();

		/* If we haven't seen any other IPIs, tell the caller that they will have
		 * to send an IPI to the cpu in order to get it to serve the new command.
		 *
		 * Otherwise, we can just hi-jack whatever previous IPIs had already been there. */
		if (i == 0 && word == 0) {
			if (ATOMIC_READ(target->c_state) == CPU_STATE_RUNNING) {
				/* Indicate that the IPI is now ready for handling by the core. */
				IPI_DEBUG("cpu_sendipi:ipi_first [slot=%u,i=%u,mask=%#" PRIxPTR "]\n", slot, i, mask);
				ATOMIC_OR(FORCPU(target, thiscpu_x86_ipi_inuse[i]), mask);
do_send_ipi:
				IPI_DEBUG("cpu_sendipi:do_send_ipi\n");

				/* Make sure that no other IPI is still pending to be delivered by our LAPIC */
				while (lapic_read(APIC_ICR0) & APIC_ICR0_FPENDING)
					task_pause();

				/* There were no other IPIs already, meaning it's our job to send the first! */
				lapic_write(APIC_ICR1, APIC_ICR1_MKDEST(FORCPU(target, thiscpu_x86_lapicid)));
				lapic_write(APIC_ICR0,
				            X86_INTERRUPT_APIC_IPI |
				            APIC_ICR0_TYPE_FNORMAL |
				            APIC_ICR0_DEST_PHYSICAL |
				            APIC_ICR0_FASSERT |
				            APIC_ICR0_TARGET_FICR1);
				if (flags & CPU_IPI_FWAITFOR) {
					while (lapic_read(APIC_ICR0) & APIC_ICR0_FPENDING)
						task_pause();
				}
			} else if (flags & CPU_IPI_FWAKEUP) {
				/* Indicate that the IPI is now ready for handling by the core. */
				IPI_DEBUG("cpu_sendipi:ipi_wakeup [slot=%u,i=%u,mask=%#" PRIxPTR "]\n", slot, i, mask);
				ATOMIC_OR(FORCPU(target, thiscpu_x86_ipi_inuse[i]), mask);
do_wake_target:
				IPI_DEBUG("cpu_sendipi:cpu_wake\n");
				cpu_wake(target);
			} else {
				/* Failed to wake the task (deallocate the IPI) */
				ATOMIC_AND(FORCPU(target, thiscpu_x86_ipi_alloc[i]), ~mask);
				goto done_failure;
			}
		} else {
			/* Indicate that the IPI is now ready for handling by the core. */
			IPI_DEBUG("cpu_sendipi:ipi_secondary [slot=%u,i=%u,mask=%#" PRIxPTR "]\n", slot, i, mask);
			ATOMIC_OR(FORCPU(target, thiscpu_x86_ipi_inuse[i]), mask);
			if ((flags & CPU_IPI_FWAITFOR) ||
			    /* Check for race condition: If the first IPI slot became available in the
			     * mean  time, then we still have to send out a HW-IPI, just so the target
			     * CPU will actually handle it! */
			    !(ATOMIC_READ(FORCPU(target, thiscpu_x86_ipi_inuse[0])) & 1)) {
				/* Must still synchronize with the target CPU's reception of the IPI... */
				if (ATOMIC_READ(target->c_state) == CPU_STATE_RUNNING)
					goto do_send_ipi;
				goto do_wake_target;
			}
		}
done_success:
		PREEMPTION_POP(was);
		return true;
	}

	/* Re-attempt the allocation a couple of times. */
	if (++attempt < 64)
		goto again;
done_failure:
	PREEMPTION_POP(was);
	return false;
}





/* Wake up a CPU, regardless of which ever state it may be in, potentially
 * not  even waking it at all, but simply sending an IPI, such that sooner
 * or later it will check its chain of pending task (`FORCPU(target, thiscpu_sched_pending)'),
 * causing  it   to   load   all  threads   found   within   that  chain,   so-as   to   allow
 * those tasks to continue running on it.
 * On X86, this function is implemented as:
 * >> for (;;) {
 * >>     u16 state = ATOMIC_READ(target->c_state);
 * >>     switch (state) {
 * >>     case CPU_STATE_DREAMING:
 * >>         // Take on the responsibility of waking up the CPU.
 * >>         if (!ATOMIC_CMPXCH_WEAK(target->c_state,state,CPU_STATE_GETTING_UP))
 * >>             continue;
 * >>         SEND_IPI(INIT,target);
 * >>         ATTR_FALLTHROUGH
 * >>     case CPU_STATE_GETTING_UP:
 * >>         // The CPU has been instructed to wake up / is currently waking up
 * >>         // In this state, we can be sure that (when not considering possible
 * >>         // hardware failure), it will load pending tasks after switching to
 * >>         // `CPU_STATE_RUNNING' mode.
 * >>         return;
 * >>     case CPU_STATE_FALLING_ASLEEP:
 * >>         // The CPU is currently falling asleep. - If it already went past the
 * >>         // point of checking for pending tasks, then it will switch states to
 * >>         // `CPU_STATE_DREAMING' in just a moment.
 * >>         // If it didn't and is currently loading those tasks, the state will
 * >>         // shortly change to `CPU_STATE_RUNNING'
 * >>         // In either case, wait for something to happen, but do so in a busy
 * >>         // loop, so-as to not block, fulfilling the `NOBLOCK' requirement.
 * >>         task_pause();
 * >>         continue;
 * >>     case CPU_STATE_RUNNING:
 * >>         // The CPU should still be able to receive regular IPIs, so use those
 * >>         SEND_IPI(LOAD_PENDING_TASKS,target);
 * >>         // NOTE: If the CPU changed states to one where IPIs can no longer be
 * >>         //       received (aka. from `CPU_STATE_RUNNING' to `CPU_STATE_FALLING_ASLEEP'),
 * >>         //       it would have already loaded pending tasks during that transition,
 * >>         //       so regardless of the IPI actually being delivered, we know that
 * >>         //       the CPU _has_ loaded any pending tasks!
 * >>         return;
 * >>
 * >>     default:
 * >>         __builtin_unreachable();
 * >>     }
 * >>     break;
 * >> }
 */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL cpu_wake)(struct cpu *__restrict target) {
	for (;;) {
		u16 state = ATOMIC_READ(target->c_state);
		IPI_DEBUG("cpu_wake:%" PRIu16 "\n", state);
		switch (state) {

		case CPU_STATE_DREAMING:
			/* Take on the responsibility of waking up the CPU. */
			if (!ATOMIC_CMPXCH_WEAK(target->c_state, state, CPU_STATE_GETTING_UP))
				continue;
			send_init_ipi(target);
			ATTR_FALLTHROUGH
		case CPU_STATE_GETTING_UP:
			/* The CPU has been instructed to wake up / is currently waking  up.
			 * In this state, we can be sure that (when not considering possible
			 * hardware failure), it will load pending tasks after switching  to
			 * `CPU_STATE_RUNNING' mode. */
			return;

		case CPU_STATE_FALLING_ASLEEP:
			/* The CPU is currently falling asleep. - If it already went past the
			 * point of checking for pending tasks, then it will switch states to
			 * `CPU_STATE_DREAMING' in just a moment.
			 * If it didn't and is currently loading those tasks, the state will
			 * shortly change to `CPU_STATE_RUNNING'
			 * In either case, wait for something to happen, but do so in a busy
			 * loop, so-as to not  block, fulfilling the `NOBLOCK'  requirement. */
			task_pause();
			continue;

		case CPU_STATE_RUNNING:
			/* The CPU should still be able to receive regular IPIs, so use those
			 * NOTE: If there are  already IPIs  pending, then we  can assume  that
			 *       the CPU will have already gotten an interrupt (or has manually
			 *       switched its state back to RUNNING, in which case it will have
			 *       checked for pending IPIs) */
			if (ATOMIC_READ(FORCPU(target, thiscpu_x86_ipi_inuse[0])) == 0) {
				/* Make sure that no other IPI is still pending to be delivered by our LAPIC */
				while (lapic_read(APIC_ICR0) & APIC_ICR0_FPENDING)
					task_pause();
				/* Send an IPI to the CPU, forcing it to load pending tasks. */
				IPI_DEBUG("cpu_sendipi:deliver_ipi\n");
				lapic_write(APIC_ICR1, APIC_ICR1_MKDEST(FORCPU(target, thiscpu_x86_lapicid)));
				lapic_write(APIC_ICR0, X86_INTERRUPT_APIC_IPI |
				                       APIC_ICR0_TYPE_FNORMAL |
				                       APIC_ICR0_DEST_PHYSICAL |
				                       APIC_ICR0_FASSERT |
				                       APIC_ICR0_TARGET_FICR1);
			}
			/* NOTE: If the CPU changed states to one  where IPIs can no longer be  received
			 *       (aka. from `CPU_STATE_RUNNING' to `CPU_STATE_FALLING_ASLEEP'), it would
			 *       have already loaded pending tasks during that transition, so regardless
			 *       of the IPI actually being delivered, we know that the CPU _has_  loaded
			 *       any pending tasks! */
			return;

		default:
			__builtin_unreachable();
		}
		break;
	}
}

#endif /* !CONFIG_NO_SMP */

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_IPI_C */
