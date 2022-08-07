/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_RT_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_RT_C 1
#define NDEBUG_EXCEPT_NESTING
#define DISABLE_BRANCH_PROFILING
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER

#include <debugger/entry.h>
#include <debugger/hook.h>
#include <debugger/rt.h>
#include <kernel/except.h>
#include <kernel/mman.h>
#include <kernel/mman/phys.h>
#include <kernel/panic.h>
#include <kernel/types.h>
#include <kernel/x86/apic.h>
#include <kernel/x86/gdt.h>
#include <kernel/x86/idt.h>
#include <kernel/x86/pic.h>
#include <sched/async.h>
#include <sched/cpu.h>
#include <sched/scheduler.h>
#include <sched/task-clone.h>
#include <sched/task.h>
#include <sched/x86/tss.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/host.h>
#include <hybrid/sched/preemption.h>

#include <asm/farptr.h>
#include <asm/intrin.h>
#include <kos/except.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/x86/tss-compat.h>
#include <kos/kernel/x86/tss.h>
#include <sys/io.h>

#include <alloca.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <libcpustate/apply.h>

DECL_BEGIN

/* [1..1] The cpu that is hosting the debugger (== THIS_TASK->t_cpu).
 *        Set to non-NULL before `dbg_active' becomes `true', and set
 *        to   `NULL'    before    `dbg_active'    becomes    `false' */
DATDEF ATTR_DBGBSS struct cpu *dbg_cpu_ ASMNAME("dbg_cpu");


/* Host-thread special-state backup data. (saved/restored by `dbg_init()' and `dbg_fini()') */
PUBLIC ATTR_DBGBSS struct x86_dbg_hoststate x86_dbg_hostbackup = {};
PUBLIC ATTR_DBGBSS struct x86_dbg_exitstate_struct x86_dbg_exitstate = {};

/* [0..1] The thread who's view state is currently cached
 *        in `x86_dbg_viewstate' and `x86_dbg_origstate' */
INTDEF struct task *x86_dbg_viewthread;

/* DBG trap state information. */
PUBLIC ATTR_DBGBSS void *x86_dbg_trapstate            = NULL;
PUBLIC ATTR_DBGBSS unsigned int x86_dbg_trapstatekind = X86_DBG_STATEKIND_NONE;

/* 1 + the LAPIC ID of the CPU currently holding the debugger lock.
 * This value is used with `lock cmpxchgw' to describe the  primary
 * lock used to ensure  that only a single  thread can ever be  the
 * controller of debugger mode. */
PUBLIC ATTR_DBGBSS WEAK u16 x86_dbg_owner_lapicid = 0;

/* Invoke globally defined debugger hooks matching the given `type' */
PRIVATE ATTR_DBGTEXT void FCALL dbg_runhooks(dbg_hook_type_t type) {
	struct dbg_inithook *current;
	struct dbg_hookiterator iter;
	dbg_hookiterator_init(&iter);
	for (;;) {
		current = (struct dbg_inithook *)dbg_hookiterator_next_filtered(&iter, type);
		if (!current)
			break;
		TRY {
			(*current->di_func)();
		} EXCEPT {
		}
	}
	dbg_hookiterator_fini(&iter);
}


DATDEF ATTR_PERTASK uintptr_t this_x86_kernel_psp0_ ASMNAME("this_x86_kernel_psp0");
DATDEF ATTR_PERTASK struct mnode this_kernel_stacknode_ ASMNAME("this_kernel_stacknode");
DATDEF ATTR_PERTASK struct mpart this_kernel_stackpart_ ASMNAME("this_kernel_stackpart");

#ifdef CONFIG_NO_SMP
#define x86_failsafe_getcpu() &bootcpu
#else /* CONFIG_NO_SMP */
INTDEF ATTR_COLDTEXT ATTR_RETNONNULL WUNUSED struct cpu *
NOTHROW(KCALL x86_failsafe_getcpu)(void);
#endif /* !CONFIG_NO_SMP */




#ifndef CONFIG_NO_SMP
union ac_int { /* AltCore_Interrupt */
	struct {
		u8 ai_sender; /* [valid_if(!0)]
		               * [lock(SET(ATOMIC(!dbg_cpu)), CLEAR(dbg_cpu))]
		               * The sending CPU id +1 */
		u8 ai_vector; /* The interrupt that was triggered. */
	};
	u16    ai_word;   /* Control word. */
};

/*[[[config CONFIG_KERNEL_X86_DEBUGGER_ALTCORE_MAX_INTERRUPTS! = 2]]]*/
#ifndef CONFIG_KERNEL_X86_DEBUGGER_ALTCORE_MAX_INTERRUPTS
#define CONFIG_KERNEL_X86_DEBUGGER_ALTCORE_MAX_INTERRUPTS 2
#endif /* !CONFIG_KERNEL_X86_DEBUGGER_ALTCORE_MAX_INTERRUPTS */
/*[[[end]]]*/

/* Pending interrupt from a secondary CPU. */
PRIVATE ATTR_DBGBSS union ac_int
ac_ints[CONFIG_KERNEL_X86_DEBUGGER_ALTCORE_MAX_INTERRUPTS] = { };

/* Handle  an  interrupt happening  on  a CPU  that  isn't `dbg_cpu'
 * while  the  debugger is  active.  When this  function  is called,
 * we know that our caller is the `PREEMPTION_ENABLE_WAIT_DISABLE()'
 * statement  inside  of  `debugger_wait_for_done()',  and  our  job
 * is to filter out `vector == 0xf1' */
INTERN ATTR_DBGTEXT NOBLOCK void
NOTHROW(FCALL x86_dbg_altcore_interrupt)(u8 vector) {
	struct cpu *me = x86_failsafe_getcpu();
	union ac_int aint;
	if ((uintptr_t)me < KERNELSPACE_BASE)
		return;
	aint.ai_sender = (me->c_id % CONFIG_MAX_CPU_COUNT) + 1;
	aint.ai_vector = vector;
	for (;;) {
		unsigned int i;
		for (i = 0; i < CONFIG_KERNEL_X86_DEBUGGER_ALTCORE_MAX_INTERRUPTS; ++i) {
			union ac_int existing;
again_index_i:
			existing.ai_word = ATOMIC_READ(ac_ints[i].ai_word);
			if (existing.ai_sender != 0)
				continue; /* Already in use. */
			if (!ATOMIC_CMPXCH_WEAK(ac_ints[i].ai_word,
			                        existing.ai_word,
			                        aint.ai_word))
				goto again_index_i;
			/* Marked as pending! */
			if (i == 0 && X86_HAVE_LAPIC) {
				/* First pending interrupt -> Send an IPI to `dbg_cpu' */
				struct cpu *target = ATOMIC_READ(dbg_cpu);
				if ((uintptr_t)target >= KERNELSPACE_BASE) {
					while (lapic_read(APIC_ICR0) & APIC_ICR0_FPENDING)
						__pause();
					lapic_write(APIC_ICR1, APIC_ICR1_MKDEST(FORCPU(target, thiscpu_x86_lapicid)));
					lapic_write(APIC_ICR0,
					            X86_INTERRUPT_APIC_IPI |
					            APIC_ICR0_TYPE_FNORMAL |
					            APIC_ICR0_DEST_PHYSICAL |
					            APIC_ICR0_FASSERT |
					            APIC_ICR0_TARGET_FICR1);
					while (lapic_read(APIC_ICR0) & APIC_ICR0_FPENDING)
						__pause();
				}
			}
			return;
		}
		__pause();
	}
}

INTDEF NOBLOCK void NOTHROW(KCALL x86_handle_dbg_ps2_interrupt)(void);

/* High-level  function   for   handling   an   AltCoreInterrupt
 * originating from `sender', and having been caused by `vector'
 * @return: true:  Successfully handled the interrupt.
 * @return: false: Interrupt  cannot   be   handled   in   debug-mode.
 *                 Mark the interrupt as pending, and have the sending
 *                 CPU execute the vector's normal handler once debug-
 *                 mode is left. */
PRIVATE ATTR_DBGTEXT NOBLOCK bool
NOTHROW(FCALL x86_dbg_handle_aci)(struct cpu *__restrict sender,
                                  u8 vector) {
	(void)sender;
	if (vector == 0xf1) {
		/* Keyboard interrupt! */
		x86_handle_dbg_ps2_interrupt();
		outb(X86_PIC1_CMD, X86_PIC_CMD_EOI);
		return true;
	}
	/* XXX: Handle other interrupts? */
	if (vector >= X86_INTERRUPT_PIC1_BASE)
		X86_PIC_EOI(vector);
	return false;
}


/* Called by the APIC-IPI interrupt handler in the context of `dbg_cpu' */
INTERN ATTR_DBGTEXT NOBLOCK void
NOTHROW(FCALL x86_dbg_handle_altcore_interrupt)(void) {
	bool did_something;
	unsigned int i;
again:
	did_something = false;
	/* Look for something to do. */
	for (i = 0; i < CONFIG_KERNEL_X86_DEBUGGER_ALTCORE_MAX_INTERRUPTS; ++i) {
		union ac_int job;
		struct cpu *sender_cpu;
		struct x86_dbg_cpuammend *sender_ammend;
		bool handled;
		job.ai_word = ATOMIC_XCH(ac_ints[i].ai_word, 0);
		if (job.ai_sender == 0)
			continue; /* Unused */
		--job.ai_sender;
		if unlikely(job.ai_sender >= CONFIG_MAX_CPU_COUNT)
			continue; /* Shouldn't happen. */
		sender_cpu = cpu_vector[job.ai_sender];
		if unlikely((uintptr_t)sender_cpu < KERNELSPACE_BASE)
			continue; /* Shouldn't happen. */
		if unlikely(sender_cpu->c_id != job.ai_sender)
			continue; /* Shouldn't happen. */
		if unlikely(!x86_dbg_hostbackup.dhs_cpus[job.ai_sender].dcs_istate)
			continue; /* Shouldn't happen. */
		sender_ammend = x86_dbg_hostbackup.dhs_cpus[job.ai_sender].dcs_iammend;
		if unlikely(!sender_ammend)
			continue; /* Shouldn't happen. */
		/* Try to handle the interrupt in the context of the debugger. */
		handled = x86_dbg_handle_aci(sender_cpu, job.ai_vector);
		if (!handled) {
			/* Enqueue the interrupt for execution by `sender_cpu'
			 * once debugger mode is exited. */
			u8 mask;
			unsigned int index;
			mask  = (u8)1 << (job.ai_vector % 8);
			index = job.ai_vector / 8;
			ATOMIC_OR(sender_ammend->dca_intr[index], mask);
		}
		did_something = true;
	}
	if (did_something)
		goto again;
}


PRIVATE ATTR_DBGTEXT NOBLOCK NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL debugger_wait_for_done)(struct icpustate *__restrict state,
                                      void *args[CPU_IPI_ARGCOUNT]) {
	struct x86_dbg_cpuammend ammend;
	unsigned int mycpuid;
	/* Quick check: Are we even supposed to become suspended? */
	if unlikely(ATOMIC_READ(dbg_cpu_) == NULL)
		goto done;
	PREEMPTION_DISABLE();
	(void)args;
	/* Figure out the calling CPU. */
	ammend.dca_cpu = x86_failsafe_getcpu();

	/* Load the calling thread pointer. */
	ammend.dca_thread = FORCPU(ammend.dca_cpu, thiscpu_sched_current);
	if (!ADDR_ISKERN(ammend.dca_thread))
		ammend.dca_thread = &FORCPU(ammend.dca_cpu, thiscpu_idle);

	mycpuid = ammend.dca_cpu->c_id % CONFIG_MAX_CPU_COUNT;

	/* Set the KEEPCORE flag for our current thread. */
	ammend.dca_taskflags = ATOMIC_FETCHOR(ammend.dca_thread->t_flags, TASK_FKEEPCORE);

	/* Set our own thread as the scheduling override. */
	ammend.dca_override = FORCPU(ammend.dca_cpu, thiscpu_sched_override);
	FORCPU(ammend.dca_cpu, thiscpu_sched_override) = ammend.dca_thread;

	/* Save additional registers. */
	ammend.dca_tr  = __str();
	ammend.dca_ldt = __sldt();
	__sidt(&ammend.dca_idt);
	__sgdt(&ammend.dca_gdt);
	ammend.dca_coregs.co_cr0 = __rdcr0();
	ammend.dca_coregs.co_cr2 = __rdcr2();
	ammend.dca_coregs.co_cr3 = __rdcr3();
	ammend.dca_coregs.co_cr4 = __rdcr4();
	ammend.dca_drregs.dr_dr0 = __rddr0();
	ammend.dca_drregs.dr_dr1 = __rddr1();
	ammend.dca_drregs.dr_dr2 = __rddr2();
	ammend.dca_drregs.dr_dr3 = __rddr3();
	ammend.dca_drregs.dr_dr6 = __rddr6();
	ammend.dca_drregs.dr_dr7 = __rddr7();
#ifdef __x86_64__
	ammend.dca_kgsbase          = __rdgsbaseq();
	ammend.dca_sgbase.sg_fsbase = __rdfsbaseq();
	ammend.dca_sgbase.sg_gsbase = __rdmsr(IA32_KERNEL_GS_BASE);
	ammend.dca_sgregs.sg_gs     = __rdgs();
	ammend.dca_sgregs.sg_fs     = __rdfs();
	ammend.dca_sgregs.sg_es     = __rdes();
	ammend.dca_sgregs.sg_ds     = __rdds();
#else /* __x86_64__ */
	ammend.dca_gs = __rdgs();
	ammend.dca_ss = __rdss();
#endif /* !__x86_64__ */

	/* Clear the set of pending interrupts. */
	bzero(ammend.dca_intr, sizeof(ammend.dca_intr));

	/* Fill in  the host-backup  area  of our  CPU,  thus
	 * ACK-ing the fact that we're now supposed to sleep. */
	ATOMIC_WRITE(x86_dbg_hostbackup.dhs_cpus[mycpuid].dcs_iammend, &ammend);
	ATOMIC_WRITE(x86_dbg_hostbackup.dhs_cpus[mycpuid].dcs_istate, state);

	/* Load the IDT for use by secondary CPUs while one specific CPU is hosting the debugger.
	 * WARNING: INTERRUPT HANDLERS OF THIS IDT _DONT_ PRESERVE THE (R|E)AX REGISTER!
	 * TODO: Preemptive interrupts should continue to fire and account for passed time! */
	__lidt_p(&x86_dbgaltcoreidt_ptr);

	/* Make sure that other IPIs also get handled!
	 * This is important because HW-IPIs may only be send when there  aren't
	 * any pending SW-IPIs, meaning that we wouldn't get the memo if we were
	 * to wait for other CPUs while there are still more pending SW-IPIs! */
	cpu_ipi_service_nopr();

	/* While for the debugger to become inactive. */
	while (ATOMIC_READ(dbg_cpu_) != NULL) {
		COMPILER_BARRIER();
		/* NOTE: Mark (R|E)AX as clobbered, since the interrupt handlers (which may only be
		 *       executed during the `hlt' instruction  in this inline assembly  statement)
		 *       may override that register during execution! */
		__asm__ __volatile__("sti\n\t"
		                     "hlt\n\t"
		                     "cli"
		                     :
		                     :
		                     : "memory"
#ifdef __x86_64__
		                     , "%rax"
#else /* __x86_64__ */
		                     , "%eax"
#endif /* !__x86_64__ */
		                     );
		COMPILER_BARRIER();
	}

	/* Re-load the saved return state. */
	state = ATOMIC_XCH(x86_dbg_hostbackup.dhs_cpus[mycpuid].dcs_istate, NULL);

	/* Re-load overwritten configuration variables and additional registers. */
	__wrcr0(ammend.dca_coregs.co_cr0);
	__wrcr2(ammend.dca_coregs.co_cr2);
	__wrcr3(ammend.dca_coregs.co_cr3);
	__wrcr4(ammend.dca_coregs.co_cr4);
	__wrdr0(ammend.dca_drregs.dr_dr0);
	__wrdr1(ammend.dca_drregs.dr_dr1);
	__wrdr2(ammend.dca_drregs.dr_dr2);
	__wrdr3(ammend.dca_drregs.dr_dr3);
	__wrdr6(ammend.dca_drregs.dr_dr6);
	__wrdr7(ammend.dca_drregs.dr_dr7);
	__lgdt_p(&ammend.dca_gdt);
	__lidt_p(&ammend.dca_idt);
#ifdef __x86_64__
	__wrgs(ammend.dca_sgregs.sg_gs);
	__wrgsbaseq(ammend.dca_kgsbase);
	__wrfs(ammend.dca_sgregs.sg_fs);
	__wrfsbaseq(ammend.dca_sgbase.sg_fsbase);
	__wres(ammend.dca_sgregs.sg_es);
	__wrds(ammend.dca_sgregs.sg_ds);
	__wrmsr(IA32_KERNEL_GS_BASE, ammend.dca_sgbase.sg_gsbase);
#else /* __x86_64__ */
	__wrgs(ammend.dca_gs);
	__wrss(ammend.dca_ss);
#endif /* !__x86_64__ */
	__lldt(ammend.dca_ldt);
	{
		struct segment *gdt;
		gdt = (struct segment *)ammend.dca_gdt.dt_base;
		gdt[SEGMENT_INDEX(ammend.dca_tr)].s_tss.t_type_bits.ttb_busy = 0; /* BUSY=0 */
		__ltr(ammend.dca_tr);
	}

	/* Restore the old state of the KEEPCORE flag. */
	if (!(ammend.dca_taskflags & TASK_FKEEPCORE))
		ATOMIC_AND(ammend.dca_thread->t_flags, ~TASK_FKEEPCORE);

	/* Restore the previous override. */
	FORCPU(ammend.dca_cpu, thiscpu_sched_override) = ammend.dca_override;

	/* TODO: Service interrupts for all 1-bits in `ammend.dca_intr' */
done:
	return state;
}
#endif /* !CONFIG_NO_SMP */


#ifndef CONFIG_NO_SMP

/* Return the number of CPUs that have ACKed having been suspended. */
PRIVATE NOBLOCK ATTR_DBGTEXT unsigned int
NOTHROW(KCALL x86_dbg_hostbackup_cpu_suspended_count)(void) {
	unsigned int i, result = 0;
	for (i = 0; i < cpu_count; ++i) {
		if (ATOMIC_READ(x86_dbg_hostbackup.dhs_cpus[i].dcs_istate) != NULL)
			++result;
	}
	return result;
}

INTDEF ATTR_PERCPU uintptr_t thiscpu_idle_x86_kernel_psp0;

PRIVATE NOBLOCK ATTR_DBGTEXT NONNULL((1, 2)) unsigned int
NOTHROW(KCALL cpu_broadcastipi_notthis_early_boot_aware)(cpu_ipi_t func,
                                                         void *args[CPU_IPI_ARGCOUNT],
                                                         unsigned int flags,
                                                         struct cpu *calling_cpu) {
	unsigned int i, result = 0;
	preemption_flag_t was;
	preemption_pushoff(&was);
	for (i = 0; i < cpu_count; ++i) {
		struct cpu *target;
		struct task *thread;
		target = cpu_vector[i];
		if (target == calling_cpu)
			continue;
		/* At one point during early boot, the entries of the `cpu_vector'
		 * are used to carry a 16-bit  block of information about the  how
		 * the associated CPU will be addressed physically.
		 * Since we known  that the  kernel lives  in upper  memory, and  that
		 * this type  of  address  information only  uses  the  lower-most  16
		 * bits, we can infer that anything  that isn't >= 0xc000000 in  i386,
		 * or `0xffff800000000000' on x86_64 isn't an initialized CPU pointer. */
		if ((uintptr_t)target < KERNELSPACE_BASE)
			continue;

		/* One of the last things done during init is setting TTS.PSP0
		 * Check   if   that  field   has  already   been  initialized */
		thread = FORCPU(target, thiscpu_sched_current);
		if ((uintptr_t)thread < KERNELSPACE_BASE)
			continue;
		{
			uintptr_t const *ppsp0;
			ppsp0 = &FORTASK(thread, this_x86_kernel_psp0);
			if ((uintptr_t)ppsp0 < KERNELSPACE_BASE)
				continue;
			if (FORCPU(target, thiscpu_x86_tss).t_psp0 != *ppsp0)
				continue;
		}
		if (cpu_sendipi(target, func, args, flags))
			++result;
	}
	preemption_pop(&was);
	return result;
}
#endif /* !CONFIG_NO_SMP */


PRIVATE ATTR_DBGTEXT void KCALL
x86_dbg_initialize_segments(struct cpu *me, struct task *mythread) {
	/* Set segment base values */
	segment_wrbaseX(&x86_dbggdt[SEGMENT_INDEX(SEGMENT_CPU_TSS)], (uintptr_t)&FORCPU(me, thiscpu_x86_tss));
	segment_wrbaseX(&x86_dbggdt[SEGMENT_INDEX(SEGMENT_CPU_LDT)], (uintptr_t)&FORCPU(me, thiscpu_x86_ldt));
#ifndef __x86_64__
	segment_wrbaseX(&x86_dbggdt[SEGMENT_INDEX(SEGMENT_CPU_TSS_DF)], (uintptr_t)&FORCPU(me, thiscpu_x86_tssdf));
	segment_wrbaseX(&x86_dbggdt[SEGMENT_INDEX(SEGMENT_KERNEL_FSBASE)], (uintptr_t)mythread);
	segment_wrbaseX(&x86_dbggdt[SEGMENT_INDEX(SEGMENT_USER_FSBASE)], (uintptr_t)FORTASK(mythread, this_x86_user_fsbase));
	segment_wrbaseX(&x86_dbggdt[SEGMENT_INDEX(SEGMENT_USER_GSBASE)], (uintptr_t)FORTASK(mythread, this_x86_user_gsbase));
#endif /* !__x86_64__ */

	/* Reload segment registers. */
	x86_dbggdt[SEGMENT_INDEX(SEGMENT_CPU_TSS)].s_tss.t_type_bits.ttb_busy = 0; /* BUSY=0 */
	__ltr(SEGMENT_CPU_TSS);
	__lldt(SEGMENT_CPU_LDT);
#ifdef __x86_64__
	__wrgsbase(mythread);
#else /* __x86_64__ */
	__wrfs(SEGMENT_KERNEL_FSBASE);
	__wrgs(SEGMENT_USER_GSBASE_RPL);
#endif /* !__x86_64__ */
}



/* Verify the integrity of a given set of task connections. */
PRIVATE ATTR_DBGTEXT bool
NOTHROW(KCALL verify_task_connections)(struct task_connections *self) {
	TRY {
		struct task_connection *con;
		if (!ADDR_ISKERN(self))
			goto nope;
		if (self->tcs_thread && !ADDR_ISKERN(self->tcs_thread))
			goto nope;
		if (self->tsc_prev && !ADDR_ISKERN(self->tsc_prev))
			goto nope;
		for (con = self->tcs_con; con; con = con->tc_connext) {
			if (!ADDR_ISKERN(con))
				goto nope;
			if (!ADDR_ISKERN(con->tc_sig))
				goto nope;
		}
		return true;
	} EXCEPT {
	}
nope:
	return false;
}




INTDEF void NOTHROW(KCALL x86_initialize_pic)(void);

INTDEF void KCALL dbg_initialize_tty(void);
INTDEF void KCALL dbg_finalize_tty(void);
INTDEF void KCALL dbg_reset_tty(void);

INTDEF void KCALL x86_debug_initialize_ps2_keyboard(void);
INTDEF void KCALL x86_debug_finalize_ps2_keyboard(void);

/* Flagset  of components that could be preserved (used to make the
 * debugger initialization more robust against recursively entering
 * itself) (set of `INITOK_*') */
PRIVATE ATTR_DBGBSS volatile u8 initok = 0;
#define INITOK_THIS_EXCEPTION_INFO   0x01
#define INITOK_TASKSELF              0x02
#define INITOK_TASKFLAGS             0x04
#define INITOK_PSP0                  0x08
#define INITOK_SCHED_OVERRIDE        0x10
#define INITOK_CONNECTIONS           0x20

PRIVATE ATTR_DBGTEXT void FCALL
x86_dbg_psp0threadstate_save_stacknode(struct x86_dbg_psp0threadstate *__restrict self,
                                       struct mnode const *__restrict src) {
	void const *p;
	memcpy(self->_dpts_this_kernel_stacknode, src, offsetof(struct mnode, mn_mement));
	p = &src->mn_mement + 1;
	COMPILER_DELETE_ASSUMPTIONS(p);
	memcpy(self->_dpts_this_kernel_stacknode + offsetof(struct mnode, mn_mement),
	       p, sizeof(struct mnode) - offsetafter(struct mnode, mn_mement));
}
PRIVATE ATTR_DBGTEXT void FCALL
x86_dbg_psp0threadstate_load_stacknode(struct x86_dbg_psp0threadstate const *__restrict self,
                                       struct mnode *__restrict dst) {
	uintptr_t saved_flags;
	void *p;
	saved_flags = dst->mn_flags;
	memcpy(dst, self->_dpts_this_kernel_stacknode, offsetof(struct mnode, mn_mement));
	p = &dst->mn_mement + 1;
	COMPILER_DELETE_ASSUMPTIONS(p);
	memcpy(p, self->_dpts_this_kernel_stacknode + offsetof(struct mnode, mn_mement),
	       sizeof(struct mnode) - offsetafter(struct mnode, mn_mement));
	/* The `MNODE_F__RBRED' flag must not be overwritten during  restore.
	 * It falls under the same category as the `mn_mement' field, meaning
	 * that the debugger may have  been in its right  to modify it if  it
	 * wasn't corrupted before the debugger was entered! */
	dst->mn_flags &= ~MNODE_F__RBRED;
	dst->mn_flags |= saved_flags & MNODE_F__RBRED;
}

PRIVATE ATTR_DBGTEXT void FCALL
x86_save_psp0_thread(struct x86_dbg_psp0threadstate *__restrict state,
                     struct task const *__restrict thread) {
	state->dpts_this_psp0 = FORTASK(thread, this_x86_kernel_psp0_);
	memcpy(&state->dpts_this_kernel_stackpart, &FORTASK(thread, this_kernel_stackpart_), sizeof(struct mpart));
	x86_dbg_psp0threadstate_save_stacknode(state, &FORTASK(thread, this_kernel_stacknode_));
}

PRIVATE ATTR_DBGTEXT void FCALL
x86_load_psp0_thread(struct x86_dbg_psp0threadstate const *__restrict state,
                     struct task *__restrict thread) {
	FORTASK(thread, this_x86_kernel_psp0_) = state->dpts_this_psp0;
	memcpy(&FORTASK(thread, this_kernel_stackpart_), &state->dpts_this_kernel_stackpart, sizeof(struct mpart));
	x86_dbg_psp0threadstate_load_stacknode(state, &FORTASK(thread, this_kernel_stacknode_));
}

INTDEF byte_t __kernel_boottask_stack[];
INTDEF byte_t __kernel_boottask_stack_page_p[];
INTDEF byte_t __kernel_bootidle_stack[];
INTDEF byte_t __kernel_bootidle_stack_page_p[];
INTDEF byte_t __kernel_asyncwork_stack[];
INTDEF byte_t __kernel_asyncwork_stack_page_p[];

PRIVATE ATTR_DBGTEXT void FCALL
x86_init_psp0_thread(struct task *__restrict thread, size_t stack_size) {
	struct mnode *node = &FORTASK(thread, this_kernel_stacknode_);
	struct mpart *part = &FORTASK(thread, this_kernel_stackpart_);
	node->mn_part           = part;
	node->mn_link.le_prev   = &part->mp_share.lh_first;
	node->mn_link.le_next   = NULL;
	part->mp_share.lh_first = node;
	part->mp_flags &= ~(MPART_F_LOCKBIT);
	if (thread == &boottask) {
		part->mp_state        = MPART_ST_MEM;
		node->mn_minaddr      = __kernel_boottask_stack;
		part->mp_mem.mc_start = (physpage_t)loadfarptr(__kernel_boottask_stack_page_p);
	} else if (thread == &bootidle) {
		part->mp_state        = MPART_ST_MEM;
		node->mn_minaddr      = __kernel_bootidle_stack;
		part->mp_mem.mc_start = (physpage_t)loadfarptr(__kernel_bootidle_stack_page_p);
	} else if (thread == &asyncwork) {
		part->mp_state        = MPART_ST_MEM;
		node->mn_minaddr      = __kernel_asyncwork_stack;
		part->mp_mem.mc_start = (physpage_t)loadfarptr(__kernel_asyncwork_stack_page_p);
	}
	if (part->mp_state != MPART_ST_MEM &&
	    part->mp_state != MPART_ST_MEM_SC)
		part->mp_state = MPART_ST_MEM;
	if (part->mp_state == MPART_ST_MEM)
		part->mp_mem.mc_size = stack_size / PAGESIZE;
	node->mn_maxaddr = node->mn_minaddr + stack_size - 1;
	part->mp_maxaddr = part->mp_minaddr + stack_size - 1;
	FORTASK(thread, _this_x86_kernel_psp0) = (uintptr_t)mnode_getendaddr(node);
}

PRIVATE ATTR_DBGTEXT void FCALL
x86_save_psp0(struct cpu *me, struct task *mythread) {
	struct task *myidle = &FORCPU(me, thiscpu_idle);
	x86_save_psp0_thread(&x86_dbg_hostbackup.dhs_psp0.dps_thistask, mythread);
	x86_save_psp0_thread(&x86_dbg_hostbackup.dhs_psp0.dps_thisidle, myidle);
}

PRIVATE ATTR_DBGTEXT void FCALL
x86_init_psp0(struct cpu *me, struct task *mythread) {
	struct task *myidle = &FORCPU(me, thiscpu_idle);
	if (mythread != myidle)
		x86_init_psp0_thread(mythread, KERNEL_STACKSIZE);
	x86_init_psp0_thread(myidle, KERNEL_IDLE_STACKSIZE);
}

PRIVATE ATTR_DBGTEXT void FCALL
x86_load_psp0(struct cpu *me, struct task *mythread) {
	struct task *myidle = &FORCPU(me, thiscpu_idle);
	x86_load_psp0_thread(&x86_dbg_hostbackup.dhs_psp0.dps_thistask, mythread);
	x86_load_psp0_thread(&x86_dbg_hostbackup.dhs_psp0.dps_thisidle, myidle);
}


INTERN ATTR_DBGTEXT void KCALL x86_dbg_init(void) {
	struct cpu *me;
	struct task *mythread;
	/* Figure out which one's our own CPU. */
	me    = x86_failsafe_getcpu();

	mythread = FORCPU(me, thiscpu_sched_current);
	if unlikely(!mythread) /* Shouldn't happen, but better be safe! */
		mythread = &FORCPU(me, thiscpu_idle);

	/* Set segment base values */
	x86_dbg_initialize_segments(me, mythread);

	/* Re-configure the hosting cpu/thread */
	if (!(initok & INITOK_THIS_EXCEPTION_INFO)) {
		memcpy(&x86_dbg_hostbackup.dhs_except,
		       &FORTASK(mythread, this_exception_info),
		       sizeof(struct exception_info));
		initok |= INITOK_THIS_EXCEPTION_INFO;
	}
	if (!(initok & INITOK_TASKSELF)) {
		x86_dbg_hostbackup.dhs_taskself = mythread->t_self;
		initok |= INITOK_TASKSELF;
	}
	mythread->t_self = mythread;
	if (!(initok & INITOK_TASKFLAGS)) {
		x86_dbg_hostbackup.dhs_taskflags = ATOMIC_FETCHOR(mythread->t_flags, TASK_FKEEPCORE);
		initok |= INITOK_TASKFLAGS;
	} else {
		ATOMIC_OR(mythread->t_flags, TASK_FKEEPCORE);
	}
	if (!(initok & INITOK_PSP0)) {
		x86_save_psp0(me, mythread);
		initok |= INITOK_PSP0;
	}
	x86_init_psp0(me, mythread);
	if (!(initok & INITOK_SCHED_OVERRIDE)) {
		x86_dbg_hostbackup.dhs_override = FORCPU(me, thiscpu_sched_override);
		initok |= INITOK_SCHED_OVERRIDE;
	}
	FORCPU(me, thiscpu_sched_override) = mythread;

	/* Make sure that the signal connections sub-system is initialized. */
	pertask_fix_task_connections(mythread);

	/* Push active connections. */
	if (!(initok & INITOK_CONNECTIONS)) {
		/* NOTE: Also guard  against attempts  to re-push  the same  connection
		 *       set, as might happen if something after this point goes wrong,
		 *       and  the debugger tries  to enter itself,  which would lead to
		 *       an assertion failure in `task_pushconnections()':
		 *       `Connection <addressof(x86_dbg_hostbackup.dhs_signals)> set was already pushed'
		 * Technically, this should already be prevented by `initok & INITOK_CONNECTIONS',
		 * however  given that this is all about making this code be robust against broken
		 * code elsewhere within the kernel, double-checking isn't a problem here! */
		if unlikely(!verify_task_connections(FORTASK(mythread, this_connections))) {
			/* Connections are all f'ed up. - Fully reset them, so
			 * we can at least get ~some~ kind of working state... */
fully_reset_task_connections:
			FORTASK(mythread, this_connections) = NULL;
			bzero(&FORTASK(mythread, this_root_connections), sizeof(this_root_connections));
			pertask_fix_task_connections(mythread);
			task_pushconnections(&x86_dbg_hostbackup.dhs_signals);
		} else if likely(FORTASK(mythread, this_connections) != &x86_dbg_hostbackup.dhs_signals) {
			task_pushconnections(&x86_dbg_hostbackup.dhs_signals);
		} else {
			/* Already set??? */
			if (verify_task_connections(&x86_dbg_hostbackup.dhs_signals)) {
				task_disconnectall();
			} else {
				goto fully_reset_task_connections;
			}
		}
		initok |= INITOK_CONNECTIONS;
	}

	/* NOTE: Clear `dbg_cpu_' _BEFORE_ sending the IPI to stop execution
	 *       on other CPUs. - This  field being non-NULL is the  trigger
	 *       that causes other CPUs to stay suspended! */
	COMPILER_BARRIER();
	dbg_cpu_ = me;
	COMPILER_BARRIER();

	/* Suspend execution on all other CPUs. */
#ifndef CONFIG_NO_SMP
	{
		void *args[CPU_IPI_ARGCOUNT];
		unsigned int count;
		bzero(x86_dbg_hostbackup.dhs_cpus, sizeof(x86_dbg_hostbackup.dhs_cpus));
		COMPILER_BARRIER();
		count = cpu_broadcastipi_notthis_early_boot_aware(&debugger_wait_for_done, args,
		                                                  CPU_IPI_FWAITFOR, me);
		if (count) {
			/* Wait for other CPUs to ACK becoming suspended. */
			unsigned int volatile timeout = 1000000;

			/* NOTE: We  need a timeout here, since this can dead-lock if one of the other
			 *       CPUs  is itself  in a dead-lock,  which could easily  happen when the
			 *       debugger was entered while the caller was holding some kind of atomic
			 *       lock, which another CPU is now  trying to acquire. (all while  having
			 *       preemption, and thus all types of interrupts disabled)
			 * When this happens, the other CPU will never respond to us until the user is
			 * ready to return from debugger mode, but assuming that the above  assumption
			 * is correct, the secondary core that's not responding, while being unable to
			 * halt in the mean time,  still shouldn't be able to  do any real harm  until
			 * that point, so this is actually (kind-of) ok. */
			while (x86_dbg_hostbackup_cpu_suspended_count() < count) {
				if (!timeout)
					break;
				--timeout;
				__pause();
			}
		}
	}
#endif /* !CONFIG_NO_SMP */

	/* Set our own thread as the current thread. */
	dbg_current        = mythread;
	x86_dbg_viewthread = NULL;

	/* Make sure that the PIC is initialized properly, as the debugger's
	 * PS/2 keyboard driver requires  interrupts to be mapped  properly. */
	x86_initialize_pic();

	/* Configure VGA + PS/2 keyboard. */
	dbg_initialize_tty();
	x86_debug_initialize_ps2_keyboard();

	/* Invoke global callbacks. */
	dbg_active = true; /* Some callbacks require that `dbg_active = true'! */
	dbg_runhooks(DBG_HOOK_INIT);
	dbg_active = false;
}

#ifdef __x86_64__
PRIVATE ATTR_DBGTEXT void KCALL
reset_pdir_p64(struct p64_pdir *__restrict self, u64 phys_self) {
	/* kernel-space */
	memcpyq(self->p_e4 + 256, P64_PDIR_E4_IDENTITY + 256, 256);
	/* Set the control word for the page directory identity mapping. */
	self->p_e4[257].p_word = (u64)phys_self | P64_PAGE_FACCESSED | P64_PAGE_FWRITE | P64_PAGE_FPRESENT;
}
#else /* __x86_64__ */
#ifndef CONFIG_NO_KERNEL_X86_PAGING_PAE
PRIVATE ATTR_DBGTEXT bool KCALL
reset_pdir_pae(struct pae_pdir *__restrict self) {
	u64 e3[4];
	unsigned int i;
	for (i = 0; i < 4; ++i) {
		e3[i] = self->p_e3[i].p_word;
		if (!(e3[i] & PAE_PAGE_FPRESENT))
			return false;
	}
	/* Kernel share (copy from our own page directory) */
	copytophys_onepage((physaddr_t)e3[3] & PAE_PAGE_FVECTOR,
	                   PAE_PDIR_E2_IDENTITY[3], 508 * 8);
	e3[0] |= PAE_PAGE_FACCESSED | PAE_PAGE_FWRITE | PAE_PAGE_FPRESENT;
	e3[1] |= PAE_PAGE_FACCESSED | PAE_PAGE_FWRITE | PAE_PAGE_FPRESENT;
	e3[2] |= PAE_PAGE_FACCESSED | PAE_PAGE_FWRITE | PAE_PAGE_FPRESENT;
	e3[3] |= PAE_PAGE_FACCESSED | PAE_PAGE_FWRITE | PAE_PAGE_FPRESENT;
	/* Identity mapping */
	copytophys_onepage((physaddr_t)(e3[3] & PAE_PAGE_FVECTOR) +
	                   508 * 8,
	                   e3,
	                   4 * 8); /* Identity mapping */
	return true;
}
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_PAE */

#ifndef CONFIG_NO_KERNEL_X86_PAGING_P32
PRIVATE ATTR_DBGTEXT void KCALL
reset_pdir_p32(struct p32_pdir *__restrict self, u32 phys_self) {
	/* Copy P2 pointers that are shared with the kernel. */
	memcpyl(&self->p_e2[768], &P32_PDIR_E2_IDENTITY[768], 1023 - 768);

	/* Create the identity mapping */
	self->p_e2[1023].p_word = ((u32)phys_self |
	                           (P32_PAGE_FACCESSED | P32_PAGE_FWRITE |
	                            P32_PAGE_FPRESENT));
}
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_P32 */
#endif /* !__x86_64__ */

PRIVATE ATTR_DBGTEXT void KCALL
reset_pdir(struct task *mythread) {
	struct mman *mymm;
	mymm = mythread->t_mman;
	if unlikely((uintptr_t)mymm < KERNELSPACE_BASE)
		return;
	if unlikely((physaddr_t)mymm->mm_pagedir_p != pagedir_translate(&mymm->mm_pagedir))
		return;
	if unlikely(((uintptr_t)mymm->mm_pagedir_p & PAGEMASK) != 0)
		return;
	if (mymm == &mman_kernel)
		return; /* nothing to do here. */

	/* Make sure that the kernel-share segment of `mymm' is initialized correctly! */
#ifdef __x86_64__
	reset_pdir_p64(&mymm->mm_pagedir, (u64)mymm->mm_pagedir_p);
#elif defined(CONFIG_NO_KERNEL_X86_PAGING_PAE)
	reset_pdir_p32(&mymm->mm_pagedir.pd_p32, (u32)mymm->mm_pagedir_p);
#elif defined(CONFIG_NO_KERNEL_X86_PAGING_P32)
	if (!reset_pdir_pae(&mymm->mm_pagedir.pd_pae))
		return;
#else
	if (X86_PAGEDIR_USES_PAE()) {
		if (!reset_pdir_pae(&mymm->mm_pagedir.pd_pae))
			return;
	} else {
		reset_pdir_p32(&mymm->mm_pagedir.pd_p32, (u32)mymm->mm_pagedir_p);
	}
#endif

	/* The page directory seems to be consistent. -> Use it instead to
	 * minimize the number of  necessary page directory switches  when
	 * inspecting memory. */
	pagedir_set(mymm->mm_pagedir_p);
}


/* Called to  perform reset  operations that  must be  performed  before
 * the debugger stack is reset as part of the debugger resetting itself.
 * This  function  should perform  any  reset that  interacts  with data
 * structures which may be located on the debugger stack. */
INTERN ATTR_DBGTEXT void KCALL x86_dbg_reset_dbg_stack(void) {
	struct cpu *me;
	struct task *mythread;
	/* Figure out which one's our own CPU. */
	me    = x86_failsafe_getcpu();
	dbg_cpu_ = me;

	mythread = FORCPU(me, thiscpu_sched_current);
	if unlikely(!mythread) /* Shouldn't happen, but better be safe! */
		mythread = &FORCPU(me, thiscpu_idle);

	/* Set segment base values */
	x86_dbg_initialize_segments(me, mythread);

	/* Make sure that the signal connections sub-system is (still) initialized. */
	pertask_fix_task_connections(mythread);

	/* When the debugger is reset after a prior call to `task_pushconnections()',
	 * then we  must take  special care  to pop  the pushed  set of  connections.
	 * This  case  can be  detected by  looking at  connection set  pointers, and
	 * checking if  they are  apart of  the  debugger stack  (if they  are,  then
	 * the debugger was reset with at least one set of pushed connections) */
	if (likely(initok & INITOK_CONNECTIONS) &&
	    likely(&FORTASK(mythread, this_connections) == &PERTASK(this_connections))) {
		if unlikely(FORTASK(mythread, this_connections) != &x86_dbg_hostbackup.dhs_signals) {
			struct task_connections *chain;
			chain = FORTASK(mythread, this_connections);
			/* Validate  the chain of  pushed connections. If  we're able to detect
			 * any faults, then we will not actually disconnect from them properly.
			 * Otherwise,  we essentially  pop connections  until we  reach the one
			 * we've been expecting to find. */
			TRY {
				struct task_connections *iter;
				if unlikely(!verify_task_connections(&x86_dbg_hostbackup.dhs_signals))
					goto reset_all_connections; /* Something is insanely broken here. */
				for (iter = chain; iter != &x86_dbg_hostbackup.dhs_signals;
				     iter = iter->tsc_prev) {
					if unlikely(!verify_task_connections(iter))
						goto dont_pop_connections;
				}
				/* Everything looks good. - Pop connections until we reach `x86_dbg_hostbackup.dhs_signals' */
				while (FORTASK(mythread, this_connections) != &x86_dbg_hostbackup.dhs_signals)
					task_popconnections();
			} EXCEPT {
			}
dont_pop_connections:
			FORTASK(mythread, this_connections) = &x86_dbg_hostbackup.dhs_signals;
		}
	} else if unlikely(!verify_task_connections(FORTASK(mythread, this_connections))){
reset_all_connections:
		FORTASK(mythread, this_connections) = NULL;
		bzero(&FORTASK(mythread, this_root_connections), sizeof(this_root_connections));
		pertask_fix_task_connections(mythread);
		if (initok & INITOK_CONNECTIONS)
			task_pushconnections(&x86_dbg_hostbackup.dhs_signals);
	}
}

INTERN ATTR_DBGTEXT void KCALL x86_dbg_reset(void) {
	struct cpu *me;
	struct task *mythread;
	/* Figure out which one's our own CPU. */
	me    = x86_failsafe_getcpu();
	dbg_cpu_ = me;

	mythread = FORCPU(me, thiscpu_sched_current);
	if unlikely(!mythread) /* Shouldn't happen, but better be safe! */
		mythread = &FORCPU(me, thiscpu_idle);

	/* Set segment base values */
	x86_dbg_initialize_segments(me, mythread);

	/* Re-configure the hosting cpu/thread */
	mythread->t_self = mythread;
	ATOMIC_OR(mythread->t_flags, TASK_FKEEPCORE);
	FORCPU(me, thiscpu_sched_override) = mythread;
	x86_init_psp0(me, mythread);

	/* Make sure that the signal connections sub-system is (still) initialized. */
	pertask_fix_task_connections(mythread);
	if (FORTASK(mythread, this_connections) != &x86_dbg_hostbackup.dhs_signals) {
		if (initok & INITOK_CONNECTIONS)
			FORTASK(mythread, this_connections) = x86_dbg_hostbackup.dhs_signals.tsc_prev;
		task_pushconnections(&x86_dbg_hostbackup.dhs_signals);
		initok |= INITOK_CONNECTIONS;
	}

	/* Set our own thread as the current thread. */
	dbg_current        = mythread;
	x86_dbg_viewthread = NULL;

	/* Try to make use of the ~real~ page directory of `mythread' */
	reset_pdir(mythread);

	/* Reset the debugger TTY */
	dbg_reset_tty();

	/* Re-enable managed memory access. */
	dbg_memory_managed = true;

	/* Invoke global callbacks. */
	dbg_runhooks(DBG_HOOK_RESET);

	/* Finally, handle any pending SW-ipis for our CPU.
	 * There may still be some unhandled ones if the debugger was  reset
	 * from within an IPI callback, in which case we may not have gotten
	 * around to handling any potentially remaining IPIs.
	 *
	 * One example where this might happen would be the F12-reset trick,
	 * in  which case the  debugger gets reset  from within an interrupt
	 * handler, which may actually be  the IPI-handler if the  debug-cpu
	 * isn't the boot cpu! */
	{
		preemption_flag_t was;
		preemption_pushoff(&was);
		cpu_ipi_service_nopr();
		preemption_pop(&was);
	}

}

#ifndef CONFIG_NO_SMP
PRIVATE NOBLOCK ATTR_DBGTEXT NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL debugger_wake_after_done)(struct icpustate *__restrict state,
                                        void *args[CPU_IPI_ARGCOUNT]) {
	(void)args;
	return state;
}
#endif /* !CONFIG_NO_SMP */


INTERN ATTR_DBGTEXT void KCALL x86_dbg_fini(void) {
	struct cpu *me;
	struct task *mythread;
	/* Figure out which one's our own CPU. */
	me = x86_failsafe_getcpu();

	mythread = FORCPU(me, thiscpu_sched_current);
	if unlikely(!mythread) /* Shouldn't happen, but better be safe! */
		mythread = &FORCPU(me, thiscpu_idle);

	/* Set segment base values */
	x86_dbg_initialize_segments(me, mythread);

	/* Invoke global callbacks. */
	dbg_active = true; /* Some callbacks require that `dbg_active = true'! */
	dbg_runhooks(DBG_HOOK_FINI);
	dbg_active = false;

	x86_debug_finalize_ps2_keyboard();
	dbg_finalize_tty();

	/* NOTE: Clear `dbg_cpu_' _BEFORE_ sending the IPI to resume execution
	 *       on  other CPUs. -  This field being NULL  is the trigger that
	 *       causes other CPUs to resume! */
	COMPILER_BARRIER();
	dbg_cpu_ = NULL;
	COMPILER_BARRIER();

	/* Wake-up other CPUs */
#ifndef CONFIG_NO_SMP
	{
		void *args[CPU_IPI_ARGCOUNT];
		COMPILER_BARRIER();
		/* Send a sporadic IPI to all CPUs other than the caller. */
		cpu_broadcastipi_notthis_early_boot_aware(&debugger_wake_after_done, args,
		                                          CPU_IPI_FWAITFOR, me);
		/* Wait for other CPUs to resume execution. */
		while (x86_dbg_hostbackup_cpu_suspended_count() != 0)
			__pause();
		bzero(x86_dbg_hostbackup.dhs_cpus, sizeof(x86_dbg_hostbackup.dhs_cpus));
	}
#endif /* !CONFIG_NO_SMP */

	/* Restore per-thread context information from the hostbackup restore area. */
	if (initok & INITOK_THIS_EXCEPTION_INFO) {
		memcpy(&FORTASK(mythread, this_exception_info),
		       &x86_dbg_hostbackup.dhs_except,
		       sizeof(struct exception_info));
	}
	if (initok & INITOK_TASKSELF)
		mythread->t_self = x86_dbg_hostbackup.dhs_taskself;
	if (initok & INITOK_TASKFLAGS) {
		if (!(x86_dbg_hostbackup.dhs_taskflags & TASK_FKEEPCORE))
			ATOMIC_AND(mythread->t_flags, ~TASK_FKEEPCORE);
	}
	if (initok & INITOK_PSP0)
		x86_load_psp0(me, mythread);
	if (initok & INITOK_SCHED_OVERRIDE)
		FORCPU(me, thiscpu_sched_override) = x86_dbg_hostbackup.dhs_override;
	if (initok & INITOK_CONNECTIONS) {
		if (FORTASK(mythread, this_connections) == &x86_dbg_hostbackup.dhs_signals)
			task_popconnections();
	}

	/* Update the debugger  exit state to  have `dbg_enter_r()'  return
	 * the updated trap state descriptor  pointer. This pointer has  to
	 * be updated in case the trap state was moved, as is required when
	 * setting the kernel_esp  register of a  32-bit irregs  structure,
	 * as found in  icpustate or  scpustate, both of  which may  appear
	 * within the `x86_dbg_trapstate' pointer. */
	if (x86_dbg_trapstatekind != X86_DBG_STATEKIND_NONE)
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_Pax = (uintptr_t)x86_dbg_trapstate;
	initok = 0;
}


/* Construct a debugger entry info descriptor which will invoke the given entry
 * by  passing  a pointer  to a  stack-allocated copy  of the  given structure.
 * Note that this copy is allocated on the debugger stack! */
#ifdef __x86_64__
#define MAKEINFO(entry, data, num_bytes)                                              \
	struct dbg_entry_info *info;                                                      \
	info = (struct dbg_entry_info *)alloca(offsetof(struct dbg_entry_info, ei_argv) + \
	                                       48 + CEIL_ALIGN(num_bytes, 8));            \
	memcpy(&info->ei_argv[6], data, num_bytes);                                       \
	info->ei_entry   = (dbg_entry_t)entry;                                            \
	info->ei_argc    = 6 + CEILDIV(num_bytes, 8);                                     \
	info->ei_argv[0] = (dbg_stack + KERNEL_DEBUG_STACKSIZE) - CEIL_ALIGN(num_bytes, 8)
#else /* __x86_64__ */
#define MAKEINFO(entry, data, num_bytes)                                              \
	struct dbg_entry_info *info;                                                      \
	info = (struct dbg_entry_info *)alloca(offsetof(struct dbg_entry_info, ei_argv) + \
	                                       4 + CEIL_ALIGN(num_bytes, 4));             \
	memcpy(&info->ei_argv[1], data, num_bytes);                                       \
	info->ei_entry   = (dbg_entry_t)entry;                                            \
	info->ei_argc    = 1 + CEILDIV(num_bytes, 4);                                     \
	info->ei_argv[0] = (dbg_stack + KERNEL_DEBUG_STACKSIZE) - CEIL_ALIGN(num_bytes, 4)
#endif /* !__x86_64__ */



PUBLIC NONNULL((1, 2)) void FCALL
dbg_enter_here_c(dbg_entry_c_t entry, void const *data, size_t num_bytes) {
	MAKEINFO(entry, data, num_bytes);
	dbg_enter_here(info);
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct fcpustate *FCALL
dbg_enter_fcpustate_cr(dbg_entry_c_t entry, void const *data,
                       size_t num_bytes, struct fcpustate *__restrict state) {
	struct fcpustate *result;
	MAKEINFO(entry, data, num_bytes);
	result = dbg_enter_fcpustate_r(info, state);
	return result;
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct ucpustate *FCALL
dbg_enter_ucpustate_cr(dbg_entry_c_t entry, void const *data,
                       size_t num_bytes, struct ucpustate *__restrict state) {
	struct ucpustate *result;
	MAKEINFO(entry, data, num_bytes);
	result = dbg_enter_ucpustate_r(info, state);
	return result;
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct lcpustate *FCALL
dbg_enter_lcpustate_cr(dbg_entry_c_t entry, void const *data,
                       size_t num_bytes, struct lcpustate *__restrict state) {
	struct lcpustate *result;
	MAKEINFO(entry, data, num_bytes);
	result = dbg_enter_lcpustate_r(info, state);
	return result;
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct kcpustate *FCALL
dbg_enter_kcpustate_cr(dbg_entry_c_t entry, void const *data,
                       size_t num_bytes, struct kcpustate *__restrict state) {
	struct kcpustate *result;
	MAKEINFO(entry, data, num_bytes);
	result = dbg_enter_kcpustate_r(info, state);
	return result;
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct icpustate *FCALL
dbg_enter_icpustate_cr(dbg_entry_c_t entry, void const *data,
                       size_t num_bytes, struct icpustate *__restrict state) {
	struct icpustate *result;
	MAKEINFO(entry, data, num_bytes);
	result = dbg_enter_icpustate_r(info, state);
	return result;
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct scpustate *FCALL
dbg_enter_scpustate_cr(dbg_entry_c_t entry, void const *data,
                       size_t num_bytes, struct scpustate *__restrict state) {
	struct scpustate *result;
	MAKEINFO(entry, data, num_bytes);
	result = dbg_enter_scpustate_r(info, state);
	return result;
}

PUBLIC ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL
dbg_enter_fcpustate_c(dbg_entry_c_t entry, void const *data,
                      size_t num_bytes, struct fcpustate *__restrict state) {
	struct fcpustate *new_state;
	new_state = dbg_enter_fcpustate_cr(entry, data, num_bytes, state);
	cpu_apply_fcpustate(new_state);
}

PUBLIC ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL
dbg_enter_ucpustate_c(dbg_entry_c_t entry, void const *data,
                      size_t num_bytes, struct ucpustate *__restrict state) {
	struct ucpustate *new_state;
	new_state = dbg_enter_ucpustate_cr(entry, data, num_bytes, state);
	cpu_apply_ucpustate(new_state);
}

PUBLIC ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL
dbg_enter_lcpustate_c(dbg_entry_c_t entry, void const *data,
                      size_t num_bytes, struct lcpustate *__restrict state) {
	struct lcpustate *new_state;
	new_state = dbg_enter_lcpustate_cr(entry, data, num_bytes, state);
	cpu_apply_lcpustate(new_state);
}

PUBLIC ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL
dbg_enter_kcpustate_c(dbg_entry_c_t entry, void const *data,
                      size_t num_bytes, struct kcpustate *__restrict state) {
	struct kcpustate *new_state;
	new_state = dbg_enter_kcpustate_cr(entry, data, num_bytes, state);
	cpu_apply_kcpustate(new_state);
}

PUBLIC ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL
dbg_enter_icpustate_c(dbg_entry_c_t entry, void const *data,
                      size_t num_bytes, struct icpustate *__restrict state) {
	struct icpustate *new_state;
	new_state = dbg_enter_icpustate_cr(entry, data, num_bytes, state);
	cpu_apply_icpustate(new_state);
}

PUBLIC ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL
dbg_enter_scpustate_c(dbg_entry_c_t entry, void const *data,
                      size_t num_bytes, struct scpustate *__restrict state) {
	struct scpustate *new_state;
	new_state = dbg_enter_scpustate_cr(entry, data, num_bytes, state);
	cpu_apply_scpustate(new_state);
}

DECL_END

#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_RT_C */
