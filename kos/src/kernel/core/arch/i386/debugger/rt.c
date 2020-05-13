/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.remove("-O3"))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_RT_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_RT_C 1
#define DISABLE_BRANCH_PROFILING 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_DEBUGGER

#include <debugger/entry.h>
#include <debugger/function.h>
#include <debugger/rt.h>
#include <kernel/apic.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/pic.h>
#include <kernel/types.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>
#include <sched/async.h>
#include <sched/cpu.h>
#include <sched/task.h>
#include <sched/tss.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/host.h>

#include <asm/farptr.h>
#include <asm/intrin.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state.h>
#include <sys/io.h>

#include <alloca.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <libcpustate/apply.h>

DECL_BEGIN

/* [1..1] The cpu that is hosting the debugger (== THIS_TASK->t_cpu).
 *        Set to non-NULL before `dbg_active' becomes `true', and set
 *        to `NULL' before `dbg_active' becomes `false' */
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
 * This value is used with `lock cmpxchgw' to describe the primary
 * lock used to ensure that only a single thread can ever be the
 * controller of debugger mode. */
PUBLIC ATTR_DBGBSS WEAK u16 x86_dbg_owner_lapicid = 0;


typedef void (KCALL *dbg_callback_t)(void);
INTDEF dbg_callback_t const __kernel_dbg_init_start[];
INTDEF dbg_callback_t const __kernel_dbg_init_end[];
INTDEF dbg_callback_t const __kernel_dbg_reset_start[];
INTDEF dbg_callback_t const __kernel_dbg_reset_end[];
INTDEF dbg_callback_t const __kernel_dbg_fini_start[];
INTDEF dbg_callback_t const __kernel_dbg_fini_end[];

#if 1
#define CALL_FUNCTIONS(start, end)             \
	do {                                       \
		dbg_callback_t const *iter;            \
		for (iter = start; iter < end; ++iter) \
			(**iter)();                        \
	} __WHILE0
#define CALL_FUNCTIONS_REV(start, end)    \
	do {                                  \
		dbg_callback_t const *iter = end; \
		while (iter > start) {            \
			--iter;                       \
			(**iter)();                   \
		}                                 \
	} __WHILE0
#else
#define CALL_FUNCTIONS(start, end)     do{}__WHILE0
#define CALL_FUNCTIONS_REV(start, end) do{}__WHILE0
#endif


DATDEF ATTR_PERTASK uintptr_t this_x86_kernel_psp0_ ASMNAME("this_x86_kernel_psp0");
DATDEF ATTR_PERTASK struct vm_node this_kernel_stacknode_ ASMNAME("this_kernel_stacknode");
DATDEF ATTR_PERTASK struct vm_datapart this_kernel_stackpart_ ASMNAME("this_kernel_stackpart");

INTDEF NOBLOCK void NOTHROW(KCALL init_this_x86_kernel_psp0)(struct task *__restrict self);

/* Check if preemptive interrupts are enabled on the calling CPU */
PRIVATE NOBLOCK ATTR_DBGTEXT WUNUSED ATTR_PURE bool
NOTHROW(KCALL are_preemptive_interrupts_enabled)(struct cpu *__restrict me) {
	return !FORCPU(me, arch_cpu_preemptive_interrupts_disabled);
}


#ifdef CONFIG_NO_SMP
#define x86_dbg_get_hostcpu() &_bootcpu
#else /* CONFIG_NO_SMP */
PRIVATE ATTR_DBGTEXT struct cpu *
NOTHROW(KCALL x86_dbg_get_hostcpu)(void) {
	struct cpu *result;
	/* Try to figure out which task we are (but
	 * don't do anything that could break stuff...) */
	if (cpu_count <= 1) {
		/* Simple case: There's only 1 CPU, so that has to be us! */
		result = &_bootcpu;
	} else if (X86_HAVE_LAPIC) {
		/* Use the LAPIC id to determine the current CPU. */
		cpuid_t i;
		u8 id = (u8)(lapic_read(APIC_ID) >> APIC_ID_FSHIFT);
		result = &_bootcpu;
		for (i = 0; i < cpu_count; ++i) {
			if unlikely((uintptr_t)cpu_vector[i] < KERNELSPACE_BASE)
				continue; /* At one point during booting, `cpu_vector' contains LAPIC IDs. */
			if (FORCPU(cpu_vector[i], thiscpu_x86_lapicid) == id) {
				result = cpu_vector[i];
				break;
			}
		}
	} else {
		/* XXX: Use pointers from `x86_dbg_exitstate' to determine the calling CPU */
		result = &_bootcpu;
	}
	return result;
}
#endif /* !CONFIG_NO_SMP */




#ifndef CONFIG_NO_SMP
union ac_int { /* AltCore_Interrupt */
	struct {
		u8 ai_sender; /* [valid_if(!0)]
		               * [lock(SET(ATOMIC(!dbg_cpu)), CLEAR(dbg_cpu))]
		               * The sending CPU id +1 */
		u8 ai_vector; /* The interrupt that was triggered. */
	};
	u16    ai_word;    /* Control word. */
};

#ifndef CONFIG_DBG_ALTCORE_MAX_INTERRUPTS
#define CONFIG_DBG_ALTCORE_MAX_INTERRUPTS 2
#endif /* !CONFIG_DBG_ALTCORE_MAX_INTERRUPTS */

/* Pending interrupt from a secondary CPU. */
PRIVATE ATTR_DBGBSS union ac_int
ac_ints[CONFIG_DBG_ALTCORE_MAX_INTERRUPTS] = { };

/* Handle an interrupt happening on a CPU that isn't `dbg_cpu'
 * while the debugger is active. When this function is called,
 * we know that our caller is the `PREEMPTION_ENABLE_WAIT_DISABLE()'
 * statement inside of `debugger_wait_for_done()', and our job
 * is to filter out `vector == 0xf1' */
INTERN ATTR_DBGTEXT NOBLOCK void
NOTHROW(FCALL x86_dbg_altcore_interrupt)(u8 vector) {
	struct cpu *mycpu = x86_dbg_get_hostcpu();
	union ac_int aint;
	if ((uintptr_t)mycpu < KERNELSPACE_BASE)
		return;
	aint.ai_sender = (mycpu->c_id % CONFIG_MAX_CPU_COUNT) + 1;
	aint.ai_vector = vector;
	for (;;) {
		unsigned int i;
		for (i = 0; i < CONFIG_DBG_ALTCORE_MAX_INTERRUPTS; ++i) {
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

/* High-level function for handling an AltCoreInterrupt
 * originating from `sender', and having been caused by `vector'
 * @return: true:  Successfully handled the interrupt.
 * @return: false: Interrupt cannot be handled in debug-mode.
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
	for (i = 0; i < CONFIG_DBG_ALTCORE_MAX_INTERRUPTS; ++i) {
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
			ATOMIC_FETCHOR(sender_ammend->dca_intr[index], mask);
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
	cpuid_t mycpuid;
	PREEMPTION_DISABLE();
	(void)args;
	/* Figure out the calling CPU. */
	ammend.dca_cpu = x86_dbg_get_hostcpu();

	/* Load the calling thread pointer. */
	ammend.dca_thread = ammend.dca_cpu->c_current;
	if (!ammend.dca_thread)
		ammend.dca_thread = &FORCPU(ammend.dca_cpu, thiscpu_idle);

	mycpuid = ammend.dca_cpu->c_id % CONFIG_MAX_CPU_COUNT;

	/* Set the KEEPCORE flag for our current thread. */
	ammend.dca_taskflags = ATOMIC_FETCHOR(ammend.dca_thread->t_flags, TASK_FKEEPCORE);

	/* Set our own thread as the scheduling override. */
	ammend.dca_override        = ammend.dca_cpu->c_override;
	ammend.dca_cpu->c_override = ammend.dca_thread;

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
	memset(ammend.dca_intr, 0, sizeof(ammend.dca_intr));

	/* Disable preemptive interrupts. */
	ammend.dca_pint = are_preemptive_interrupts_enabled(ammend.dca_cpu);
	if (ammend.dca_pint)
		cpu_disable_preemptive_interrupts_nopr();

	/* TODO: Load an alternate IDT that saves all of the interrupts that happened
	 *       while we're in here, such that once we return from inside here, those
	 *       interrupts will all get serviced. */

	/* Fill in the host-backup area of our CPU, thus
	 * ACK-ing the fact that we're now supposed to sleep. */
	ATOMIC_WRITE(x86_dbg_hostbackup.dhs_cpus[mycpuid].dcs_iammend, &ammend);
	ATOMIC_WRITE(x86_dbg_hostbackup.dhs_cpus[mycpuid].dcs_istate, state);

	/* Load the IDT for use by secondary CPUs while one specific CPU is hosting the debugger.
	 * WARNING: INTERRUPT HANDLERS OF THIS IDT _DONT_ PRESERVE THE (R|E)AX REGISTER! */
	__lidt_p(&x86_dbgaltcoreidt_ptr);

	/* While for the debugger to become inactive. */
	while (ATOMIC_READ(dbg_cpu_) != NULL) {
		COMPILER_BARRIER();
		/* NOTE: Mark (R|E)AX as clobbered, since the interrupt handlers (which may only be
		 *       executed during the `hlt' instruction in this inline assembly statement)
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
		ATOMIC_FETCHAND(ammend.dca_thread->t_flags, ~TASK_FKEEPCORE);

	/* Restore the previous override. */
	ammend.dca_cpu->c_override = ammend.dca_override;

	/* Re-enable preemptive interrupts. */
	if (ammend.dca_pint)
		cpu_enable_preemptive_interrupts_nopr();

	/* TODO: Service interrupts for all 1-bits in `ammend.dca_intr' */

	return state;
}
#endif /* !CONFIG_NO_SMP */


#ifndef CONFIG_NO_SMP

/* Return the number of CPUs that have ACKed having been suspended. */
PRIVATE NOBLOCK ATTR_DBGTEXT cpuid_t
NOTHROW(KCALL x86_dbg_hostbackup_cpu_suspended_count)(void) {
	cpuid_t i, result = 0;
	for (i = 0; i < cpu_count; ++i) {
		if (ATOMIC_READ(x86_dbg_hostbackup.dhs_cpus[i].dcs_istate) != NULL)
			++result;
	}
	return result;
}

INTDEF ATTR_PERCPU uintptr_t thiscpu_idle_x86_kernel_psp0;

PRIVATE NOBLOCK ATTR_DBGTEXT NONNULL((1, 2)) cpuid_t
NOTHROW(KCALL cpu_broadcastipi_notthis_early_boot_aware)(cpu_ipi_t func,
                                                         void *args[CPU_IPI_ARGCOUNT],
                                                         unsigned int flags,
                                                         struct cpu *calling_cpu) {
	cpuid_t i, result = 0;
	pflag_t was = PREEMPTION_PUSHOFF();
	for (i = 0; i < cpu_count; ++i) {
		struct cpu *target;
		target = cpu_vector[i];
		if (target == calling_cpu)
			continue;
		/* At one point during early boot, the entires of the `cpu_vector'
		 * are used to carry a 16-bit block of information about the how
		 * the associated CPU will be addressed physically.
		 * Since we known that the kernel lives in upper memory, and that
		 * this type of address information only uses the lower-most 16
		 * bits, we can infer that anything that isn't >= 0xc000000 in i386,
		 * or `0xffff800000000000' on x86_64 isn't an initialized CPU pointer. */
		if ((uintptr_t)target < KERNELSPACE_BASE)
			continue;

		/* One of the last things done during init is setting TTS.PSP0
		 * Check if that field has already been initialized */
		if ((uintptr_t)target->c_current < KERNELSPACE_BASE)
			continue;
		{
			uintptr_t const *ppsp0;
			ppsp0 = &FORTASK(target->c_current, this_x86_kernel_psp0);
			if ((uintptr_t)ppsp0 < KERNELSPACE_BASE)
				continue;
#ifdef __x86_64__
			if (FORCPU(target, thiscpu_x86_tss).t_rsp0 != *ppsp0)
				continue;
#else /* __x86_64__ */
			if (FORCPU(target, thiscpu_x86_tss).t_esp0 != *ppsp0)
				continue;
#endif /* !__x86_64__ */
		}
		if (cpu_sendipi(target, func, args, flags))
			++result;
	}
	PREEMPTION_POP(was);
	return result;
}
#endif /* !CONFIG_NO_SMP */


PRIVATE ATTR_DBGTEXT void KCALL
x86_dbg_initialize_segments(struct cpu *mycpu, struct task *mythread) {
	/* Set segment base values */
	segment_wrbaseX(&x86_dbggdt[SEGMENT_INDEX(SEGMENT_CPU_TSS)], (uintptr_t)&FORCPU(mycpu, thiscpu_x86_tss));
	segment_wrbaseX(&x86_dbggdt[SEGMENT_INDEX(SEGMENT_CPU_LDT)], (uintptr_t)&FORCPU(mycpu, thiscpu_x86_ldt));
#ifndef __x86_64__
	segment_wrbaseX(&x86_dbggdt[SEGMENT_INDEX(SEGMENT_CPU_TSS_DF)], (uintptr_t)&FORCPU(mycpu, thiscpu_x86_tssdf));
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


INTDEF void NOTHROW(KCALL x86_initialize_pic)(void);

INTDEF void KCALL dbg_initialize_tty(void);
INTDEF void KCALL dbg_finalize_tty(void);
INTDEF void KCALL dbg_reset_tty(void);

INTDEF void KCALL x86_debug_initialize_ps2_keyboard(void);
INTDEF void KCALL x86_debug_finalize_ps2_keyboard(void);

/* Flagset of components that could be preserved (used to make the
 * debugger initialization more robust against recursively entering
 * itself) (set of `INITOK_*') */
PRIVATE ATTR_DBGBSS volatile u8 initok = 0;
#define INITOK_THIS_EXCEPTION_INFO   0x01
#define INITOK_TASKSELF              0x02
#define INITOK_TASKFLAGS             0x04
#define INITOK_PSP0                  0x08
#define INITOK_SCHED_OVERRIDE        0x10
#define INITOK_READLOCKS             0x20
#define INITOK_CONNECTIONS           0x40
#define INITOK_PREEMPTIVE_INTERRUPTS 0x80

PRIVATE ATTR_DBGTEXT void FCALL
x86_save_psp0_thread(struct x86_dbg_psp0threadstate *__restrict state,
                     struct task const *__restrict thread) {
	state->dpts_this_psp0                                  = FORTASK(thread, this_x86_kernel_psp0_);
	state->dpts_this_kernel_stacknode_part                 = FORTASK(thread, this_kernel_stacknode_).vn_part;
	state->dpts_this_kernel_stacknode_link_pself           = FORTASK(thread, this_kernel_stacknode_).vn_link.ln_pself;
	state->dpts_this_kernel_stackpart_srefs                = FORTASK(thread, this_kernel_stackpart_).dp_srefs;
	state->dpts_this_kernel_stackpart_ramdata_blockv       = FORTASK(thread, this_kernel_stackpart_).dp_ramdata.rd_blockv;
	state->dpts_this_kernel_stacknode_node_vmin            = FORTASK(thread, this_kernel_stacknode_).vn_node.a_vmin;
	state->dpts_this_kernel_stacknode_node_vmax            = FORTASK(thread, this_kernel_stacknode_).vn_node.a_vmax;
	state->dpts_this_kernel_stackpart_ramdata_block0_start = FORTASK(thread, this_kernel_stackpart_).dp_ramdata.rd_block0.rb_start;
	state->dpts_this_kernel_stackpart_tree_vmax            = FORTASK(thread, this_kernel_stackpart_).dp_tree.a_vmax;
	state->dpts_this_kernel_stackpart_ramdata_block0_size  = FORTASK(thread, this_kernel_stackpart_).dp_ramdata.rd_block0.rb_size;
}

PRIVATE ATTR_DBGTEXT void FCALL
x86_load_psp0_thread(struct x86_dbg_psp0threadstate const *__restrict state,
                     struct task *__restrict thread) {
	FORTASK(thread, this_x86_kernel_psp0_)                                = state->dpts_this_psp0;
	FORTASK(thread, this_kernel_stacknode_).vn_part                       = state->dpts_this_kernel_stacknode_part;
	FORTASK(thread, this_kernel_stacknode_).vn_link.ln_pself              = state->dpts_this_kernel_stacknode_link_pself;
	FORTASK(thread, this_kernel_stackpart_).dp_srefs                      = state->dpts_this_kernel_stackpart_srefs;
	FORTASK(thread, this_kernel_stackpart_).dp_ramdata.rd_blockv          = state->dpts_this_kernel_stackpart_ramdata_blockv;
	FORTASK(thread, this_kernel_stacknode_).vn_node.a_vmin                = state->dpts_this_kernel_stacknode_node_vmin;
	FORTASK(thread, this_kernel_stacknode_).vn_node.a_vmax                = state->dpts_this_kernel_stacknode_node_vmax;
	FORTASK(thread, this_kernel_stackpart_).dp_ramdata.rd_block0.rb_start = state->dpts_this_kernel_stackpart_ramdata_block0_start;
	FORTASK(thread, this_kernel_stackpart_).dp_tree.a_vmax                = state->dpts_this_kernel_stackpart_tree_vmax;
	FORTASK(thread, this_kernel_stackpart_).dp_ramdata.rd_block0.rb_size  = state->dpts_this_kernel_stackpart_ramdata_block0_size;
}

INTDEF byte_t __kernel_boottask_stack_pageid[];
INTDEF byte_t __kernel_boottask_stack_pageptr[];
INTDEF byte_t __kernel_bootidle_stack_pageid[];
INTDEF byte_t __kernel_bootidle_stack_pageptr[];
INTDEF byte_t __kernel_asyncwork_stack_pageid[];
INTDEF byte_t __kernel_asyncwork_stack_pageptr[];

PRIVATE ATTR_DBGTEXT void FCALL
x86_init_psp0_thread(struct task *__restrict thread, size_t stack_size) {
	FORTASK(thread, this_kernel_stacknode_).vn_part              = &FORTASK(thread, this_kernel_stackpart_);
	FORTASK(thread, this_kernel_stacknode_).vn_link.ln_pself     = &LLIST_HEAD(FORTASK(thread, this_kernel_stackpart_).dp_srefs);
	FORTASK(thread, this_kernel_stackpart_).dp_srefs             = &FORTASK(thread, this_kernel_stacknode_);
	FORTASK(thread, this_kernel_stackpart_).dp_ramdata.rd_blockv = &FORTASK(thread, this_kernel_stackpart_).dp_ramdata.rd_block0;
	if (thread == &_boottask) {
		FORTASK(thread, this_kernel_stacknode_).vn_node.a_vmin = (pageid_t)loadfarptr(__kernel_boottask_stack_pageid);
		FORTASK(thread, this_kernel_stackpart_).dp_ramdata.rd_block0.rb_start = (pageptr_t)loadfarptr(__kernel_boottask_stack_pageptr);
	} else if (thread == &_bootidle) {
		FORTASK(thread, this_kernel_stacknode_).vn_node.a_vmin = (pageid_t)loadfarptr(__kernel_bootidle_stack_pageid);
		FORTASK(thread, this_kernel_stackpart_).dp_ramdata.rd_block0.rb_start = (pageptr_t)loadfarptr(__kernel_bootidle_stack_pageptr);
	} else if (thread == &_asyncwork) {
		FORTASK(thread, this_kernel_stacknode_).vn_node.a_vmin = (pageid_t)loadfarptr(__kernel_asyncwork_stack_pageid);
		FORTASK(thread, this_kernel_stackpart_).dp_ramdata.rd_block0.rb_start = (pageptr_t)loadfarptr(__kernel_asyncwork_stack_pageptr);
	}
	FORTASK(thread, this_kernel_stacknode_).vn_node.a_vmax = FORTASK(thread, this_kernel_stacknode_).vn_node.a_vmin +
	                                                         CEILDIV(stack_size, PAGESIZE) - 1;
	FORTASK(thread, this_kernel_stackpart_).dp_tree.a_vmax = FORTASK(thread, this_kernel_stackpart_).dp_tree.a_vmin +
	                                                         CEILDIV(stack_size, PAGESIZE) - 1;
	FORTASK(thread, this_kernel_stackpart_).dp_ramdata.rd_block0.rb_size = CEILDIV(stack_size, PAGESIZE);
	init_this_x86_kernel_psp0(thread);
}

PRIVATE ATTR_DBGTEXT void FCALL
x86_save_psp0(struct cpu *mycpu, struct task *mythread) {
	struct task *myidle = &FORCPU(mycpu, thiscpu_idle);
	x86_save_psp0_thread(&x86_dbg_hostbackup.dhs_psp0.dps_thistask, mythread);
	x86_save_psp0_thread(&x86_dbg_hostbackup.dhs_psp0.dps_thisidle, myidle);
}

PRIVATE ATTR_DBGTEXT void FCALL
x86_init_psp0(struct cpu *mycpu, struct task *mythread) {
	struct task *myidle = &FORCPU(mycpu, thiscpu_idle);
	x86_init_psp0_thread(mythread, KERNEL_STACKSIZE);
	x86_init_psp0_thread(myidle, KERNEL_IDLE_STACKSIZE);
}

PRIVATE ATTR_DBGTEXT void FCALL
x86_load_psp0(struct cpu *mycpu, struct task *mythread) {
	struct task *myidle = &FORCPU(mycpu, thiscpu_idle);
	x86_load_psp0_thread(&x86_dbg_hostbackup.dhs_psp0.dps_thistask, mythread);
	x86_load_psp0_thread(&x86_dbg_hostbackup.dhs_psp0.dps_thisidle, myidle);
}


INTERN ATTR_DBGTEXT void KCALL x86_dbg_init(void) {
	struct cpu *mycpu;
	struct task *mythread;
	/* Figure out which one's our own CPU. */
	mycpu    = x86_dbg_get_hostcpu();

	mythread = mycpu->c_current;
	if unlikely(!mythread) /* Shouldn't happen, but better be safe! */
		mythread = &FORCPU(mycpu, thiscpu_idle);

	/* Set segment base values */
	x86_dbg_initialize_segments(mycpu, mythread);

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
		ATOMIC_FETCHOR(mythread->t_flags, TASK_FKEEPCORE);
	}
	if (!(initok & INITOK_PSP0)) {
		x86_save_psp0(mycpu, mythread);
		initok |= INITOK_PSP0;
	}
	x86_init_psp0(mycpu, mythread);
	if (!(initok & INITOK_SCHED_OVERRIDE)) {
		x86_dbg_hostbackup.dhs_override = mycpu->c_override;
		initok |= INITOK_SCHED_OVERRIDE;
	}
	mycpu->c_override = mythread;

	/* Save held read-locks, and re-initialize the per-thread descriptor. */
	if (!(initok & INITOK_READLOCKS)) {
		memcpy(&x86_dbg_hostbackup.dhs_readlocks,
		       &FORTASK(mythread, this_read_locks),
		       sizeof(struct read_locks));
		initok |= INITOK_READLOCKS;
	}
	pertask_readlocks_init(mythread);

	/* Make sure that the signal connections sub-system is initialized. */
	if (!FORTASK(mythread, this_connections).tc_static_v ||
	    FORTASK(mythread, this_connections).tc_signals.ts_thread != mythread)
		pertask_init_task_connections(mythread);
	/* Push active connections. */
	if (!(initok & INITOK_CONNECTIONS)) {
		/* NOTE: Also guard against attempts to re-push the same connection
		 *       set, as might happen if something after this point goes wrong,
		 *       and the debugger tries to enter itself, which would lead to
		 *       an assertion failure in `task_pushconnections()':
		 *       `Connection <addressof(x86_dbg_hostbackup.dhs_signals)> set was already pushed'
		 * Technically, this should already be prevented by `initok & INITOK_CONNECTIONS',
		 * however given that this is all about making this code be robust against broken
		 * code elsewhere within the kernel, double-checking isn't a problem here! */
		if (FORTASK(mythread, this_connections).tc_static_v != x86_dbg_hostbackup.dhs_signals.tc_static) {
			task_pushconnections(&x86_dbg_hostbackup.dhs_signals);
			initok |= INITOK_CONNECTIONS;
		}
	}
	if (!(initok & INITOK_PREEMPTIVE_INTERRUPTS)) {
		x86_dbg_hostbackup.dhs_pint = are_preemptive_interrupts_enabled(mycpu);
		if (x86_dbg_hostbackup.dhs_pint)
			cpu_disable_preemptive_interrupts_nopr();
		initok |= INITOK_PREEMPTIVE_INTERRUPTS;
	}

	/* NOTE: Clear `dbg_cpu_' _BEFORE_ sending the IPI to stop execution
	 *       on other CPUs. - This field being non-NULL is the trigger
	 *       that causes other CPUs to stay suspended! */
	COMPILER_BARRIER();
	dbg_cpu_ = mycpu;
	COMPILER_BARRIER();

	/* Suspend execution on all other CPUs. */
#ifndef CONFIG_NO_SMP
	{
		void *args[CPU_IPI_ARGCOUNT];
		cpuid_t count;
		memset(x86_dbg_hostbackup.dhs_cpus, 0, sizeof(x86_dbg_hostbackup.dhs_cpus));
		COMPILER_BARRIER();
		count = cpu_broadcastipi_notthis_early_boot_aware(&debugger_wait_for_done, args,
		                                                  CPU_IPI_FWAITFOR, mycpu);
		if (count) {
			/* Wait for other CPUs to ACK becoming suspended. */
			while (x86_dbg_hostbackup_cpu_suspended_count() < count)
				__pause();
		}
	}
#endif /* !CONFIG_NO_SMP */

	/* Set our own thread as the current thread. */
	dbg_current        = mythread;
	x86_dbg_viewthread = NULL;

	/* Make sure that the PIC is initialized properly, as the debugger's
	 * PS/2 keyboard driver requires interrupts to be mapped properly. */
	x86_initialize_pic();

	/* Configure VGA + PS/2 keyboard. */
	dbg_initialize_tty();
	x86_debug_initialize_ps2_keyboard();

	/* Invoke global callbacks. */
	CALL_FUNCTIONS(__kernel_dbg_init_start,
	               __kernel_dbg_init_end);
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
#ifndef CONFIG_NO_PAGING_PAE
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
	vm_copytophys_onepage((vm_phys_t)e3[3] & PAE_PAGE_FVECTOR,
	                      PAE_PDIR_E2_IDENTITY[3], 508 * 8);
	e3[0] |= PAE_PAGE_FACCESSED | PAE_PAGE_FWRITE | PAE_PAGE_FPRESENT;
	e3[1] |= PAE_PAGE_FACCESSED | PAE_PAGE_FWRITE | PAE_PAGE_FPRESENT;
	e3[2] |= PAE_PAGE_FACCESSED | PAE_PAGE_FWRITE | PAE_PAGE_FPRESENT;
	e3[3] |= PAE_PAGE_FACCESSED | PAE_PAGE_FWRITE | PAE_PAGE_FPRESENT;
	/* Identity mapping */
	vm_copytophys_onepage((vm_phys_t)(e3[3] & PAE_PAGE_FVECTOR) +
	                      508 * 8,
	                      e3,
	                      4 * 8); /* Identity mapping */
	return true;
}
#endif /* !CONFIG_NO_PAGING_PAE */

#ifndef CONFIG_NO_PAGING_P32
PRIVATE ATTR_DBGTEXT void KCALL
reset_pdir_p32(struct p32_pdir *__restrict self, u32 phys_self) {
	/* Copy P2 pointers that are shared with the kernel. */
	memcpyl(&self->p_e2[768], &P32_PDIR_E2_IDENTITY[768], 1023 - 768);

	/* Create the identity mapping */
	self->p_e2[1023].p_word = ((u32)phys_self |
	                           (P32_PAGE_FACCESSED | P32_PAGE_FWRITE |
	                            P32_PAGE_FPRESENT));
}
#endif /* !CONFIG_NO_PAGING_P32 */
#endif /* !__x86_64__ */

PRIVATE ATTR_DBGTEXT void KCALL
reset_pdir(struct task *mythread) {
	struct vm *myvm;
	myvm = mythread->t_vm;
	if unlikely((uintptr_t)myvm < KERNELSPACE_BASE)
		return;
	if unlikely((vm_phys_t)myvm->v_pdir_phys_ptr != pagedir_translate(&myvm->v_pagedir))
		return;
	if unlikely(((uintptr_t)myvm->v_pdir_phys & PAGEMASK) != 0)
		return;
	if (myvm == &vm_kernel)
		return; /* nothing to do here. */

	/* Make sure that the kernel-share segment of `myvm' is initialized correctly! */
#ifdef __x86_64__
	reset_pdir_p64(&myvm->v_pagedir, (u64)myvm->v_pdir_phys_ptr);
#elif defined(CONFIG_NO_PAGING_PAE)
	reset_pdir_p32(&myvm->v_pagedir.pd_p32, (u32)myvm->v_pdir_phys_ptr);
#elif defined(CONFIG_NO_PAGING_P32)
	if (!reset_pdir_pae(&myvm->v_pagedir.pd_pae))
		return;
#else
	if (X86_PAGEDIR_USES_PAE()) {
		if (!reset_pdir_pae(&myvm->v_pagedir.pd_pae))
			return;
	} else {
		reset_pdir_p32(&myvm->v_pagedir.pd_p32, (u32)myvm->v_pdir_phys_ptr);
	}
#endif

	/* The page directory seems to be consistent. -> Use it instead to
	 * minimize the number of necessary page directory switches when
	 * inspecting memory. */
	pagedir_set(myvm->v_pdir_phys_ptr);
}

INTERN ATTR_DBGTEXT void KCALL x86_dbg_reset(void) {
	struct cpu *mycpu;
	struct task *mythread;
	/* Figure out which one's our own CPU. */
	mycpu    = x86_dbg_get_hostcpu();
	dbg_cpu_ = mycpu;

	mythread = mycpu->c_current;
	if unlikely(!mythread) /* Shouldn't happen, but better be safe! */
		mythread = &FORCPU(mycpu, thiscpu_idle);

	/* Set segment base values */
	x86_dbg_initialize_segments(mycpu, mythread);

	/* Re-configure the hosting cpu/thread */
	mythread->t_self = mythread;
	ATOMIC_FETCHOR(mythread->t_flags, TASK_FKEEPCORE);
	mycpu->c_override = mythread;
	x86_init_psp0(mycpu, mythread);
	pertask_readlocks_init(mythread);

	/* Make sure that the signal connections sub-system is (still) initialized. */
	if (!FORTASK(mythread, this_connections).tc_static_v ||
	    FORTASK(mythread, this_connections).tc_signals.ts_thread != mythread)
		pertask_init_task_connections(mythread);

	/* Set our own thread as the current thread. */
	dbg_current        = mythread;
	x86_dbg_viewthread = NULL;

	/* Try to make use of the ~real~ page directory of `mythread' */
	reset_pdir(mythread);

	/* Reset the debugger TTY */
	dbg_reset_tty();

	/* Invoke global callbacks. */
	CALL_FUNCTIONS(__kernel_dbg_reset_start,
	               __kernel_dbg_reset_end);
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
	struct cpu *mycpu;
	struct task *mythread;
	/* Figure out which one's our own CPU. */
	mycpu = x86_dbg_get_hostcpu();

	mythread = mycpu->c_current;
	if unlikely(!mythread) /* Shouldn't happen, but better be safe! */
		mythread = &FORCPU(mycpu, thiscpu_idle);

	/* Set segment base values */
	x86_dbg_initialize_segments(mycpu, mythread);

	/* Invoke global callbacks. */
	CALL_FUNCTIONS_REV(__kernel_dbg_fini_start,
	                   __kernel_dbg_fini_end);

	x86_debug_finalize_ps2_keyboard();
	dbg_finalize_tty();

	/* NOTE: Clear `dbg_cpu_' _BEFORE_ sending the IPI to resume execution
	 *       on other CPUs. - This field being NULL is the trigger that
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
		                                          CPU_IPI_FWAITFOR, mycpu);
		/* Wait for other CPUs to resume execution. */
		while (x86_dbg_hostbackup_cpu_suspended_count() != 0)
			__pause();
		memset(x86_dbg_hostbackup.dhs_cpus, 0, sizeof(x86_dbg_hostbackup.dhs_cpus));
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
			ATOMIC_FETCHAND(mythread->t_self, ~TASK_FKEEPCORE);
	}
	if (initok & INITOK_PSP0)
		x86_load_psp0(mycpu, mythread);
	if (initok & INITOK_SCHED_OVERRIDE)
		mycpu->c_override = x86_dbg_hostbackup.dhs_override;
	if (initok & INITOK_READLOCKS) {
		memcpy(&FORTASK(mythread, this_read_locks),
		       &x86_dbg_hostbackup.dhs_readlocks,
		       sizeof(struct read_locks));
	}
	if (initok & INITOK_CONNECTIONS)
		task_popconnections(&x86_dbg_hostbackup.dhs_signals);
	if (initok & INITOK_PREEMPTIVE_INTERRUPTS) {
		if (x86_dbg_hostbackup.dhs_pint)
			cpu_enable_preemptive_interrupts_nopr();
	}

	/* Update the debugger exit state to have `dbg_enter_r()' return
	 * the updated trap state descriptor pointer. This pointer has to
	 * be updated in case the trap state was moved, as is required when
	 * setting the kernel_esp register of a 32-bit irregs structure,
	 * as found in icpustate or scpustate, both of which may appear
	 * within the `x86_dbg_trapstate' pointer. */
	if (x86_dbg_trapstatekind != X86_DBG_STATEKIND_NONE)
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_pax = (uintptr_t)x86_dbg_trapstate;
	initok = 0;
}


/* Construct a debugger entry info descriptor which will invoke the given entry
 * by passing a pointer to a stack-allocated copy of the given structure.
 * Note that this copy is allocated on the debugger stack! */
#ifdef __x86_64__
#define MAKEINFO(entry, data, num_bytes)                                              \
	struct dbg_entry_info *info;                                                      \
	info = (struct dbg_entry_info *)alloca(offsetof(struct dbg_entry_info, ei_argv) + \
	                                       48 + CEIL_ALIGN(num_bytes, 8));            \
	memcpy(&info->ei_argv[6], data, CEIL_ALIGN(num_bytes, 8));                        \
	info->ei_entry   = (dbg_entry_t)entry;                                            \
	info->ei_argc    = 6 + CEILDIV(num_bytes, 8);                                     \
	info->ei_argv[0] = (dbg_stack + KERNEL_DEBUG_STACKSIZE) - CEIL_ALIGN(num_bytes, 8)
#else /* __x86_64__ */
#define MAKEINFO(entry, data, num_bytes)                                              \
	struct dbg_entry_info *info;                                                      \
	info = (struct dbg_entry_info *)alloca(offsetof(struct dbg_entry_info, ei_argv) + \
	                                       4 + CEIL_ALIGN(num_bytes, 4));             \
	memcpy(&info->ei_argv[1], data, CEIL_ALIGN(num_bytes, 4));                        \
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

PUBLIC ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL
dbg_enter_fcpustate_c(dbg_entry_c_t entry, void const *data,
                      size_t num_bytes, struct fcpustate *__restrict state) {
	struct fcpustate *new_state;
	new_state = dbg_enter_fcpustate_cr(entry, data, num_bytes, state);
	cpu_apply_fcpustate(new_state);
}

PUBLIC ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL
dbg_enter_ucpustate_c(dbg_entry_c_t entry, void const *data,
                      size_t num_bytes, struct ucpustate *__restrict state) {
	struct ucpustate *new_state;
	new_state = dbg_enter_ucpustate_cr(entry, data, num_bytes, state);
	cpu_apply_ucpustate(new_state);
}

PUBLIC ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL
dbg_enter_lcpustate_c(dbg_entry_c_t entry, void const *data,
                      size_t num_bytes, struct lcpustate *__restrict state) {
	struct lcpustate *new_state;
	new_state = dbg_enter_lcpustate_cr(entry, data, num_bytes, state);
	cpu_apply_lcpustate(new_state);
}

PUBLIC ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL
dbg_enter_kcpustate_c(dbg_entry_c_t entry, void const *data,
                      size_t num_bytes, struct kcpustate *__restrict state) {
	struct kcpustate *new_state;
	new_state = dbg_enter_kcpustate_cr(entry, data, num_bytes, state);
	cpu_apply_kcpustate(new_state);
}

PUBLIC ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL
dbg_enter_icpustate_c(dbg_entry_c_t entry, void const *data,
                      size_t num_bytes, struct icpustate *__restrict state) {
	struct icpustate *new_state;
	new_state = dbg_enter_icpustate_cr(entry, data, num_bytes, state);
	cpu_apply_icpustate(new_state);
}

PUBLIC ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL
dbg_enter_scpustate_c(dbg_entry_c_t entry, void const *data,
                      size_t num_bytes, struct scpustate *__restrict state) {
	struct scpustate *new_state;
	new_state = dbg_enter_scpustate_cr(entry, data, num_bytes, state);
	cpu_apply_scpustate(new_state);
}



DECL_END

#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_RT_C */
