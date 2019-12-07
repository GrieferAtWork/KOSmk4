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

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_DEBUGGER

#include <kernel/apic.h>
#include <kernel/gdt.h>
#include <kernel/types.h>
#include <sched/cpu.h>
#include <sched/task.h>
#include <sched/tss.h>

#include <hybrid/atomic.h>

#include <asm/intrin.h>
#include <debugger/function.h>
#include <debugger/rt.h>
#include <kos/kernel/cpu-state.h>

#include <string.h>

DECL_BEGIN

/* Host-thread special-state backup data. (saved/restored by `dbg_init()' and `dbg_fini()') */
PUBLIC ATTR_DBGBSS struct x86_dbg_hoststate x86_dbg_hostbackup = {};
PUBLIC ATTR_DBGBSS struct fcpustate x86_dbg_exitstate          = {};
PUBLIC ATTR_DBGBSS struct fcpustate x86_dbg_origstate          = {};
PUBLIC ATTR_DBGBSS struct fcpustate x86_dbg_viewstate          = {};

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


#ifndef CONFIG_NO_SMP
PRIVATE ATTR_DBGTEXT NOBLOCK NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL debugger_wait_for_done)(struct icpustate *__restrict state,
                                      void *args[CPU_IPI_ARGCOUNT]) {
	(void)args;
	cpu_disable_preemptive_interrupts_nopr();
	while (dbg_active)
		PREEMPTION_ENABLE_WAIT_DISABLE();
	cpu_enable_preemptive_interrupts_nopr(); /* XXX: Don't account for lost time! */
	return state;
}
#endif /* !CONFIG_NO_SMP */


#ifndef CONFIG_NO_SMP
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

	x86_dbg_hostbackup.dhs_pint = true; /* TODO: `cpu_are_preemptive_interrupts_enabled()' */
	if (x86_dbg_hostbackup.dhs_pint)
		cpu_disable_preemptive_interrupts_nopr();

	/* Suspend execution on all other CPUs. */
#ifndef CONFIG_NO_SMP
	{
		void *args[CPU_IPI_ARGCOUNT];
		cpu_broadcastipi_notthis_early_boot_aware(&debugger_wait_for_done, args,
		                                          CPU_IPI_FNORMAL, mycpu);
	}
#endif /* !CONFIG_NO_SMP */

	/* Set the currently viewed state to be the exit state. */
	memcpy(&x86_dbg_viewstate, &x86_dbg_exitstate, sizeof(struct fcpustate));
	memcpy(&x86_dbg_origstate, &x86_dbg_exitstate, sizeof(struct fcpustate));

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

	/* Set the currently viewed state to be the exit state. */
	dbg_current = mythread;
	memcpy(&x86_dbg_viewstate, &x86_dbg_exitstate, sizeof(struct fcpustate));
	memcpy(&x86_dbg_origstate, &x86_dbg_exitstate, sizeof(struct fcpustate));

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
		/* Send a sporadic IPI to all CPUs other than the caller. */
		cpu_broadcastipi_notthis_early_boot_aware(&debugger_wake_after_done, args,
		                                          CPU_IPI_FNORMAL, mycpu);
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
}


DECL_END

#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_RT_C */
