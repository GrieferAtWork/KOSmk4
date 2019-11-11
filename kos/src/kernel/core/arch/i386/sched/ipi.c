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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_IPI_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_IPI_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/apic.h>
#include <kernel/idt.h>
#include <kernel/panic.h>
#include <kernel/pit.h>
#include <kernel/printk.h>
#include <sched/cpu.h>
#include <sched/smp.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <asm/param.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

#if 0
#define IPI_DEBUG(...) printk(KERN_DEBUG __VA_ARGS__)
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
		__pause();
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
		__pause();
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL send_init_ipi)(struct cpu *__restrict target) {
	pflag_t was;
	assert(target != THIS_CPU);
	/* Make sure that our outgoing interrupt line isn't
	 * still pending due to another, unrelated IPI. */
	while (lapic_read(APIC_ICR0) & APIC_ICR0_FPENDING)
		__pause();

	/* Send an INIT IPI to the target CPU. */
	apic_send_init(FORCPU(target, x86_lapic_id));

	/* Wait for 10 milliseconds. */
	was = PREEMPTION_PUSHOFF();
	while (!sync_trywrite(&x86_pit_lock))
		__pause();
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
		__pause();
	sync_endwrite(&x86_pit_lock);
	PREEMPTION_POP(was);
	/* Send the startup IPI */
	apic_send_startup(FORCPU(target, x86_lapic_id), x86_smp_entry_page);

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
	while (!sync_trywrite(&x86_pit_lock)) {
		if (ATOMIC_READ(target->c_state) != CPU_STATE_GETTING_UP)
			goto done_ppop;
		__pause();
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
			sync_endwrite(&x86_pit_lock);
done_ppop:
			PREEMPTION_POP(was);
			return;
		}
		__pause();
		if (ATOMIC_READ(target->c_state) != CPU_STATE_GETTING_UP)
			goto done_ppop_endwrite;
	}
	sync_endwrite(&x86_pit_lock);
	PREEMPTION_POP(was);
	if (ATOMIC_READ(target->c_state) != CPU_STATE_GETTING_UP)
		return;
	/* Send the startup IPI again */
	apic_send_startup(FORCPU(target, x86_lapic_id), x86_smp_entry_page);
	/* Wait for up to 1 second. */
	was = PREEMPTION_PUSHOFF();
	while (!sync_trywrite(&x86_pit_lock)) {
		if (ATOMIC_READ(target->c_state) != CPU_STATE_GETTING_UP)
			goto done_ppop;
		__pause();
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
		__pause();
		if (ATOMIC_READ(target->c_state) != CPU_STATE_GETTING_UP)
			goto done_ppop_endwrite;
	}
	sync_endwrite(&x86_pit_lock);
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
PRIVATE ATTR_PERCPU struct pending_ipi ipi_pending[CPU_IPI_BUFFER_SIZE];

/* [lock(SET(ATOMIC,IF_SET_IN(ipi_alloc)),CLEAR(ATOMIC,THIS_CPU))] Bitset of fully initialized IPIs. */
INTERN ATTR_PERCPU WEAK uintptr_t ipi_inuse[CEILDIV(CPU_IPI_BUFFER_SIZE, BITS_PER_POINTER)] = { 0, };

/* [lock(SET(ATOMIC),CLEAR(ATOMIC,THIS_CPU))] Bitset of allocated IPIs. */
PRIVATE ATTR_PERCPU WEAK uintptr_t ipi_alloc[CEILDIV(CPU_IPI_BUFFER_SIZE, BITS_PER_POINTER)] = { 0, };


/* Check if there are any non-interrupting software-based IPIs pending. */
PUBLIC NOBLOCK WUNUSED bool
NOTHROW(KCALL cpu_swipi_pending)(void) {
	unsigned int i;
	struct cpu *me = THIS_CPU;
	assert(!PREEMPTION_ENABLED());
	for (i = 0; i < CEILDIV(CPU_IPI_BUFFER_SIZE, BITS_PER_POINTER); ++i) {
		if (ATOMIC_READ(FORCPU(me, ipi_inuse[i])) != 0)
			return true;
	}
	return false;
}


INTERN NONNULL((1)) struct icpustate *
NOTHROW(FCALL x86_serve_ipi)(struct icpustate *__restrict state) {
	unsigned int i, j;
	struct icpustate *new_state;
	struct icpustate *result = state;
	struct cpu *me           = THIS_CPU;
	IPI_DEBUG("x86_serve_ipi\n");
	for (i = 0; i < CEILDIV(CPU_IPI_BUFFER_SIZE, BITS_PER_POINTER); ++i) {
		uintptr_t bits, mask;
		bits = ATOMIC_XCH(FORCPU(me, ipi_inuse[i]), 0);
		if (!bits)
			continue;
		for (j = 0, mask = 1; bits; ++j, mask <<= 1) {
			struct pending_ipi ipi;
			if (!(bits & mask))
				continue;
			/* Deallocate this IPI. */
			memcpy(&ipi, &FORCPU(me, ipi_pending[i]), sizeof(ipi));
			ATOMIC_FETCHAND(FORCPU(me, ipi_alloc[i]), ~mask);
			/* Execute the IPI callback. */
			IPI_DEBUG("x86_serve_ipi:%p\n", ipi.pi_func);
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



INTDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL x86_execute_direct_ipi_nopr)(cpu_ipi_t func,
                                           void *args[CPU_IPI_ARGCOUNT]);
INTDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL x86_execute_direct_ipi)(cpu_ipi_t func,
                                      void *args[CPU_IPI_ARGCOUNT]);


/* TODO: Add dedicated cpu_broadcastipi() and cpu_broadcastipi_notthis() functions,
 *       which collect a set of CPUs to signal, and make use of the
 *       BROADCAST / BROADCAST_EXCEPT_SELF functionality found in LAPIC. */

PUBLIC NOBLOCK NONNULL((1, 2, 3)) bool
NOTHROW(KCALL cpu_sendipi)(struct cpu *__restrict target,
                           cpu_ipi_t func, void *args[CPU_IPI_ARGCOUNT],
                           unsigned int flags) {
	unsigned int i, attempt = 0;
	unsigned int slot;
	pflag_t was;
	was = PREEMPTION_PUSHOFF();
	if (target == THIS_CPU) {
		/* Special case: The current CPU is being targeted. */
		if (flags & CPU_IPI_FNOINTR) {
			x86_execute_direct_ipi_nopr(func, args);
			goto done_success;
		}
		if (was & EFLAGS_IF) {
			x86_execute_direct_ipi(func, args);
			assert(PREEMPTION_ENABLED());
			goto done_success;
		}
		/* Don't allow sending an IPI to our own CPU when preemption is disabled.
		 * The caller may attempt to send another, at which point the
		 * `while (lapic_read(APIC_ICR0) & APIC_ICR0_FPENDING)' loop
		 * below will block indefinitely! */
		goto done_failure;
	}
again:
	for (i = 0; i < CEILDIV(CPU_IPI_BUFFER_SIZE, BITS_PER_POINTER); ++i) {
		uintptr_t word, mask;
		unsigned int j;
again_i:
		word = ATOMIC_READ(FORCPU(target, ipi_alloc[i]));
		if unlikely(word == (uintptr_t)-1)
			continue; /* Word is fully allocated. */
		j    = 0;
		mask = 1;
		while (word & mask) {
			++j;
			mask <<= 1;
		}
		if (!ATOMIC_CMPXCH_WEAK(FORCPU(target, ipi_alloc[i]), word, word | mask)) {
			attempt = 0;
			goto again_i;
		}
		/* Successfully allocated a slot. */
		slot = i * BITS_PER_POINTER + j;
		COMPILER_WRITE_BARRIER();
		FORCPU(target, ipi_pending[slot].pi_func) = func;
		memcpy(FORCPU(target, ipi_pending[slot]).pi_args,
		       args, CPU_IPI_ARGCOUNT * sizeof(void *));
		COMPILER_WRITE_BARRIER();

		/* If we haven't seen any other IPIs, tell the caller that they will have
		 * to send an IPI to the cpu in order to get it to serve the new command.
		 * Otherwise, we can just hi-jack whatever previous IPIs had already been there. */
		if (i == 0 && word == 0) {
			if (target->c_state == CPU_STATE_RUNNING) {
				/* Indicate that the IPI is now ready for handling by the core. */
				ATOMIC_FETCHOR(FORCPU(target, ipi_inuse[i]), mask);
do_send_ipi:
				IPI_DEBUG("cpu_sendipi:do_send_ipi\n");
				/* Make sure that no other IPI is still pending to be delivered by our LAPIC */
				while (lapic_read(APIC_ICR0) & APIC_ICR0_FPENDING)
					__pause();
				/* There were no other IPIs already, meaning it's our job to send the first! */
				lapic_write(APIC_ICR1, APIC_ICR1_MKDEST(FORCPU(target, x86_lapic_id)));
				lapic_write(APIC_ICR0,
				            X86_INTERRUPT_APIC_IPI |
				            APIC_ICR0_TYPE_FNORMAL |
				            APIC_ICR0_DEST_PHYSICAL |
				            APIC_ICR0_FASSERT |
				            APIC_ICR0_TARGET_FICR1);
				if (flags & CPU_IPI_FWAITFOR) {
					while (lapic_read(APIC_ICR0) & APIC_ICR0_FPENDING)
						__pause();
				}
			} else if (flags & CPU_IPI_FWAKEUP) {
				/* Indicate that the IPI is now ready for handling by the core. */
				ATOMIC_FETCHOR(FORCPU(target, ipi_inuse[i]), mask);
do_wake_target:
				IPI_DEBUG("cpu_sendipi:cpu_wake\n");
				cpu_wake(target);
			} else {
				/* Failed to wake the task (deallocate the IPI) */
				ATOMIC_FETCHAND(FORCPU(target, ipi_alloc[i]), ~mask);
				goto done_failure;
			}
		} else {
			/* Indicate that the IPI is now ready for handling by the core. */
			IPI_DEBUG("cpu_sendipi:secondary_ipi\n");
			ATOMIC_FETCHOR(FORCPU(target, ipi_inuse[i]), mask);
			if (flags & CPU_IPI_FWAITFOR) {
				/* Must still synchronize with the target CPU's reception of the IPI... */
				if (target->c_state == CPU_STATE_RUNNING)
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
 * not even waking it at all, but simply sending an IPI, such that sooner
 * or later it will check its chain of pending task (`target->c_pending'),
 * causing it to load all threads found within that chain, so-as to allow
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
 * >>         __pause();
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
		IPI_DEBUG("cpu_wake:%I16u\n", state);
		switch (state) {

		case CPU_STATE_DREAMING:
			/* Take on the responsibility of waking up the CPU. */
			if (!ATOMIC_CMPXCH_WEAK(target->c_state, state, CPU_STATE_GETTING_UP))
				continue;
			send_init_ipi(target);
			ATTR_FALLTHROUGH
		case CPU_STATE_GETTING_UP:
			/* The CPU has been instructed to wake up / is currently waking up.
			 * In this state, we can be sure that (when not considering possible
			 * hardware failure), it will load pending tasks after switching to
			 * `CPU_STATE_RUNNING' mode. */
			return;

		case CPU_STATE_FALLING_ASLEEP:
			/* The CPU is currently falling asleep. - If it already went past the
			 * point of checking for pending tasks, then it will switch states to
			 * `CPU_STATE_DREAMING' in just a moment.
			 * If it didn't and is currently loading those tasks, the state will
			 * shortly change to `CPU_STATE_RUNNING'
			 * In either case, wait for something to happen, but do so in a busy
			 * loop, so-as to not block, fulfilling the `NOBLOCK' requirement. */
			__pause();
			continue;

		case CPU_STATE_RUNNING:
			/* The CPU should still be able to receive regular IPIs, so use those
			 * NOTE: If there are already IPIs pending, then we can assume that
			 *       the CPU will have already gotten an interrupt (or has manually
			 *       switched its state back to RUNNING, in which case it will have
			 *       checked for pending IPIs) */
			if (ATOMIC_READ(FORCPU(target, ipi_inuse[0])) == 0) {
				/* Make sure that no other IPI is still pending to be delivered by our LAPIC */
				while (lapic_read(APIC_ICR0) & APIC_ICR0_FPENDING)
					__pause();
				/* Send an IPI to the CPU, forcing it to load pending tasks. */
				IPI_DEBUG("cpu_sendipi:deliver_ipi\n");
				lapic_write(APIC_ICR1, APIC_ICR1_MKDEST(FORCPU(target, x86_lapic_id)));
				lapic_write(APIC_ICR0, X86_INTERRUPT_APIC_IPI |
				                       APIC_ICR0_TYPE_FNORMAL |
				                       APIC_ICR0_DEST_PHYSICAL |
				                       APIC_ICR0_FASSERT |
				                       APIC_ICR0_TARGET_FICR1);
			}
			/* NOTE: If the CPU changed states to one where IPIs can no longer be
			 *       received (aka. from `CPU_STATE_RUNNING' to `CPU_STATE_FALLING_ASLEEP'),
			 *       it would have already loaded pending tasks during that transition,
			 *       so regardless of the IPI actually being delivered, we know that
			 *       the CPU _has_ loaded any pending tasks! */
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
