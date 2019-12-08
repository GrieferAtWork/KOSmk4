/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.remove("-O3"))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_RT_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_RT_C 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_DEBUGGER

#include <debugger/function.h>
#include <debugger/rt.h>
#include <kernel/apic.h>
#include <kernel/gdt.h>
#include <kernel/types.h>
#include <sched/cpu.h>
#include <sched/task.h>
#include <sched/tss.h>

#include <hybrid/atomic.h>

#include <asm/intrin.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state.h>

#include <string.h>

DECL_BEGIN

/* Host-thread special-state backup data. (saved/restored by `dbg_init()' and `dbg_fini()') */
PUBLIC ATTR_DBGBSS struct x86_dbg_hoststate x86_dbg_hostbackup = {};
PUBLIC ATTR_DBGBSS struct fcpustate x86_dbg_exitstate          = {};

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
INTDEF NOBLOCK void NOTHROW(KCALL init_this_x86_kernel_psp0)(struct task *__restrict self);

/* Check if preemptive interrupts are enabled on the calling CPU */
PRIVATE ATTR_DBGTEXT NOBLOCK WUNUSED ATTR_PURE bool
NOTHROW(KCALL are_preemptive_interrupts_enabled)(void) {
	COMPILER_IMPURE();
	/* TODO */
	return true;
}


#ifndef CONFIG_NO_SMP
PRIVATE ATTR_DBGTEXT NOBLOCK NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL debugger_wait_for_done)(struct icpustate *__restrict state,
                                      void *args[CPU_IPI_ARGCOUNT]) {
	struct x86_dbg_cpuammend ammend;
	cpuid_t mycpuid;
	(void)args;
	ammend.dca_thread = THIS_TASK;
	ammend.dca_cpu    = ammend.dca_thread->t_cpu;
	mycpuid           = ammend.dca_cpu->c_id;

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

	/* Disable preemptive interrupts. */
	ammend.dca_pint = are_preemptive_interrupts_enabled();
	if (ammend.dca_pint)
		cpu_disable_preemptive_interrupts_nopr();

	/* Fill in the host-backup area of our CPU, thus
	 * ACK-ing the fact that we're now supposed to sleep. */
	ATOMIC_WRITE(x86_dbg_hostbackup.dhs_cpus[mycpuid].dcs_iammend, &ammend);
	ATOMIC_WRITE(x86_dbg_hostbackup.dhs_cpus[mycpuid].dcs_istate, state);

	/* While for the debugger to become inactive. */
	while (dbg_active)
		PREEMPTION_ENABLE_WAIT_DISABLE();

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
	__wrfs(ammend.dca_sgregs.sg_fs);
	__wres(ammend.dca_sgregs.sg_es);
	__wrds(ammend.dca_sgregs.sg_ds);
	__wrfsbaseq(ammend.dca_sgbase.sg_fsbase);
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
		cpu_enable_preemptive_interrupts_nopr(); /* XXX: Don't account for lost time! */

	return state;
}
#endif /* !CONFIG_NO_SMP */


#ifndef CONFIG_NO_SMP

/* Return the number of CPUs that have ACKed having been suspended. */
PRIVATE ATTR_DBGTEXT NOBLOCK cpuid_t
NOTHROW(KCALL x86_dbg_hostbackup_cpu_suspended_count)(void) {
	cpuid_t i, result = 0;
	for (i = 0; i < cpu_count; ++i) {
		if (ATOMIC_READ(x86_dbg_hostbackup.dhs_cpus[i].dcs_istate) != NULL)
			++result;
	}
	return result;
}

PRIVATE ATTR_DBGTEXT NOBLOCK NONNULL((1, 2)) cpuid_t
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
		if ((uintptr_t)target < KERNEL_BASE)
			continue;
		if (cpu_sendipi(target, func, args, flags))
			++result;
	}
	PREEMPTION_POP(was);
	return result;
}
#endif /* !CONFIG_NO_SMP */


PRIVATE ATTR_DBGTEXT struct cpu *
NOTHROW(KCALL x86_dbg_get_hostcpu)(void) {
	struct cpu *result;
#ifndef CONFIG_NO_SMP
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
			if unlikely((uintptr_t)cpu_vector[i] < KERNEL_BASE)
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
#endif /* !CONFIG_NO_SMP */
	return result;
}


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


INTERN ATTR_DBGTEXT void KCALL x86_dbg_init(void) {
	struct cpu *mycpu;
	struct task *mythread;
	/* Figure out which one's our own CPU. */
	mycpu = x86_dbg_get_hostcpu();

	mythread = mycpu->c_current;
	if unlikely(!mythread) /* Shouldn't happen, but better be safe! */
		mythread = &FORCPU(mycpu, thiscpu_idle);

	/* Set segment base values */
	x86_dbg_initialize_segments(mycpu, mythread);

	/* Re-configure the hosting cpu/thread */
	memcpy(&x86_dbg_hostbackup.dhs_except,
	       &FORTASK(mythread, this_exception_info),
	       sizeof(struct exception_info));
	x86_dbg_hostbackup.dhs_taskself  = mythread->t_self;
	mythread->t_self                 = mythread;
	x86_dbg_hostbackup.dhs_taskflags = ATOMIC_FETCHOR(mythread->t_flags, TASK_FKEEPCORE);
	x86_dbg_hostbackup.dhs_override  = mycpu->c_override;
	mycpu->c_override                = mythread;

	x86_dbg_hostbackup.dhs_psp0 = FORTASK(mythread, this_x86_kernel_psp0_);
	init_this_x86_kernel_psp0(mythread);

	/* Save held read-locks, and re-initialize the per-thread descriptor. */
	memcpy(&x86_dbg_hostbackup.dhs_readlocks,
	       &FORTASK(mythread, this_read_locks),
	       sizeof(struct read_locks));
	pertask_readlocks_init(mythread);

	/* Make sure that the signal connections sub-system is initialized. */
	if (!FORTASK(mythread, this_connections).tc_static_v ||
	    FORTASK(mythread, this_connections).tc_signals.ts_thread != mythread)
		pertask_init_task_connections(mythread);
	/* Push active connections. */
	task_pushconnections(&x86_dbg_hostbackup.dhs_signals);

	x86_dbg_hostbackup.dhs_pint = are_preemptive_interrupts_enabled();
	if (x86_dbg_hostbackup.dhs_pint)
		cpu_disable_preemptive_interrupts_nopr();

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
			while (count < x86_dbg_hostbackup_cpu_suspended_count())
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


INTERN ATTR_DBGTEXT void KCALL x86_dbg_reset(void) {
	struct cpu *mycpu;
	struct task *mythread;
	/* Figure out which one's our own CPU. */
	mycpu = x86_dbg_get_hostcpu();

	mythread = mycpu->c_current;
	if unlikely(!mythread) /* Shouldn't happen, but better be safe! */
		mythread = &FORCPU(mycpu, thiscpu_idle);

	/* Set segment base values */
	x86_dbg_initialize_segments(mycpu, mythread);

	/* Re-configure the hosting cpu/thread */
	memset(&FORTASK(mythread, this_exception_info),
	       0, sizeof(struct exception_info));
	mythread->t_self = mythread;
	ATOMIC_FETCHOR(mythread->t_flags, TASK_FKEEPCORE);
	mycpu->c_override = mythread;
	init_this_x86_kernel_psp0(mythread);
	pertask_readlocks_init(mythread);

	/* Make sure that the signal connections sub-system is (still) initialized. */
	if (!FORTASK(mythread, this_connections).tc_static_v ||
	    FORTASK(mythread, this_connections).tc_signals.ts_thread != mythread)
		pertask_init_task_connections(mythread);

	/* Set our own thread as the current thread. */
	dbg_current        = mythread;
	x86_dbg_viewthread = NULL;

	/* Reset the debugger TTY */
	dbg_reset_tty();

	/* Invoke global callbacks. */
	CALL_FUNCTIONS(__kernel_dbg_reset_start,
	               __kernel_dbg_reset_end);
}

#ifndef CONFIG_NO_SMP
PRIVATE ATTR_DBGTEXT NOBLOCK NONNULL((1, 2)) struct icpustate *
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

	/* Load per-thread context information from the hostbackup restore area. */
	memcpy(&FORTASK(mythread, this_exception_info),
	       &x86_dbg_hostbackup.dhs_except,
	       sizeof(struct exception_info));
	mythread->t_self = x86_dbg_hostbackup.dhs_taskself;
	if (!(x86_dbg_hostbackup.dhs_taskflags & TASK_FKEEPCORE))
		ATOMIC_FETCHAND(mythread->t_self, ~TASK_FKEEPCORE);
	FORTASK(mythread, this_x86_kernel_psp0_) = x86_dbg_hostbackup.dhs_psp0;
	mycpu->c_override = x86_dbg_hostbackup.dhs_override;
	memcpy(&FORTASK(mythread, this_read_locks),
	       &x86_dbg_hostbackup.dhs_readlocks,
	       sizeof(struct read_locks));
	task_popconnections(&x86_dbg_hostbackup.dhs_signals);

	if (x86_dbg_hostbackup.dhs_pint)
		cpu_enable_preemptive_interrupts_nopr();

	/* Update the debugger exit state to have `dbg_enter_r()' return
	 * the updated trap state descriptor pointer. This pointer has to
	 * be updated in case the trap state was moved, as is required when
	 * setting the kernel_esp register of a 32-bit irregs structure,
	 * as found in icpustate or scpustate, both of which may appear
	 * within the `x86_dbg_trapstate' pointer. */
	if (x86_dbg_trapstatekind != X86_DBG_STATEKIND_NONE)
		x86_dbg_exitstate.fcs_gpregs.gp_pax = (uintptr_t)x86_dbg_trapstate;
}


DECL_END

#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_RT_C */
