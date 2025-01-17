/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_DOUBLE_FAULT_C
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_DOUBLE_FAULT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/entry.h>
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <kernel/debugtrap.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/x86/apic.h>
#include <kernel/x86/fault.h> /* x86_handle_double_fault() */
#include <kernel/x86/gdt.h>
#include <kernel/x86/idt.h> /* IDT_CONFIG_ISTRAP() */
#include <sched/cpu.h>
#include <sched/scheduler.h>

#include <asm/registers.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>

#include <libinstrlen/instrlen.h>


/* NOTE: This also prevents `x == NULL', since `ADDR_ISKERN(NULL) == false'! */
#define VERIFY_ADDR(x) ADDR_ISKERN(x)

DECL_BEGIN

/* Note that  unlike all  other interrupt  handlers, the  double-fault  handler
 * gets invoked with a ucpustate, rather than an icpustate (at least on  i386).
 * This is required  since a double  fault isn't  handled on the  stack of  the
 * thread that caused the exception, but rather on its own stack, meaning  that
 * its return-sp isn't at the end of the irregs field when it points to kernel-
 * space.
 * On x86_64, this isn't the case since all irregs always contain a stack pointer,
 * with the double-fault  handler simply using  the alternate-stack mechanism  for
 * safely executing on an alternate stack. */
struct df_cpustate {
#ifdef __x86_64__
	struct icpustate dcs_regs;
#else /* __x86_64__ */
	struct cpu      *dcs_cpu;  /* [1..1] The current CPU. */
	PHYS pagedir_t  *dcs_cr3;
	struct ucpustate dcs_regs;
#endif /* !__x86_64__ */
};


#ifdef CONFIG_NO_SMP
#define x86_failsafe_getcpu() &bootcpu
#else /* CONFIG_NO_SMP */
INTERN ATTR_COLDTEXT ATTR_RETNONNULL WUNUSED struct cpu *
NOTHROW(KCALL x86_failsafe_getcpu)(void) {
	struct cpu *result;
	/* Try to  figure out  which task  we are  (but
	 * don't do anything that could break stuff...) */
	if (cpu_count <= 1) {
		/* Simple case: There's only 1 CPU, so that has to be us! */
		result = &bootcpu;
	} else if (X86_HAVE_LAPIC) {
		/* Use the LAPIC id to determine the current CPU. */
		unsigned int i;
		u8 id = (u8)(lapic_read(APIC_ID) >> APIC_ID_FSHIFT);
		result = &bootcpu;
		for (i = 0; i < cpu_count; ++i) {
			if unlikely(!ADDR_ISKERN(cpu_vector[i]))
				continue; /* At one point during booting, `cpu_vector' contains LAPIC IDs. */
			if (FORCPU(cpu_vector[i], thiscpu_x86_lapicid) == id) {
				result = cpu_vector[i];
				break;
			}
		}
	} else {
		/* XXX: Use pointers from `x86_dbg_exitstate' to determine the calling CPU */
		result = &bootcpu;
	}
	return result;
}
#endif /* !CONFIG_NO_SMP */



INTDEF void FCALL
x86_dump_ucpustate_register_state(struct ucpustate *__restrict ustate,
                                  PHYS pagedir_t *cr3);

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
INTDEF struct task *x86_dbg_viewthread;
INTDEF struct fcpustate x86_dbg_origstate;
INTDEF struct fcpustate x86_dbg_viewstate;

#ifdef __x86_64__
PRIVATE ATTR_DBGTEXT void KCALL
panic_df_dbg_main(void)
#else /* __x86_64__ */
PRIVATE ATTR_DBGTEXT void KCALL
panic_df_dbg_main(void *cr3)
#endif /* !__x86_64__ */
{
	static_assert(!IDT_CONFIG_ISTRAP(0x08)); /* #DF  Double Fault. */
	/* Inject the correct information about the CR3 register */
#ifndef __x86_64__
	x86_dbg_exitstate.de_state.fcs_coregs.co_cr3 = (uintptr_t)cr3;
	if (x86_dbg_viewthread == THIS_TASK) {
		if (x86_dbg_viewstate.fcs_coregs.co_cr3 == x86_dbg_origstate.fcs_coregs.co_cr3)
			x86_dbg_viewstate.fcs_coregs.co_cr3 = (uintptr_t)cr3;
		x86_dbg_origstate.fcs_coregs.co_cr3 = (uintptr_t)cr3;
	}
#endif /* !__x86_64__ */
	dbg_printf(DBGSTR(AC_WITHCOLOR(ANSITTY_CL_WHITE, ANSITTY_CL_MAROON, "Double fault") "\n"
	                  "%[vinfo:"
	                  "file: " AC_WHITE("%f") " (line " AC_WHITE("%l") ", column " AC_WHITE("%c") ")\n"
	                  "func: " AC_WHITE("%n") "\n"
	                  "addr: " AC_WHITE("%p") "\n"
	                  "]"),
	           dbg_getpcreg(DBG_RT_REGLEVEL_VIEW));
	dbg_main(0);
}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */


PRIVATE NOBLOCK ATTR_RETNONNULL NONNULL((1)) struct task *
NOTHROW(KCALL x86_repair_broken_tls_state_impl)(struct cpu *__restrict me) {
	struct task *mythread;
	mythread = FORCPU(me, thiscpu_sched_current);
	if unlikely(!VERIFY_ADDR(mythread))
		mythread = &FORCPU(me, thiscpu_idle);
#ifdef __x86_64__
	__wrgsbase(mythread);
#else /* __x86_64__ */
	segment_wrbaseX(&FORCPU(me, thiscpu_x86_gdt[SEGMENT_INDEX(SEGMENT_USER_GSBASE)]),
	                (uintptr_t)mythread);
	__lgdt(sizeof(thiscpu_x86_gdt) - 1, FORCPU(me, thiscpu_x86_gdt));
	__wrfs(SEGMENT_KERNEL_FSBASE);
#endif /* !__x86_64__ */
	return mythread;
}

INTERN NOBLOCK ATTR_RETNONNULL WUNUSED struct task *
NOTHROW(KCALL x86_repair_broken_tls_state)(void) {
	struct cpu *me = x86_failsafe_getcpu();
	return x86_repair_broken_tls_state_impl(me);
}


/* Double fault handler. */
INTERN ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct df_cpustate *FCALL
x86_handle_double_fault(struct df_cpustate *__restrict state) {
	void *pc;
	struct cpu *me;
#ifdef __x86_64__
	pc = (void *)state->dcs_regs.ics_irregs.ir_rip;
#else /* __x86_64__ */
	pc = (void *)state->dcs_regs.ucs_eip;
#endif /* !__x86_64__ */

	/* In order to even  be able to write  to the system log,  we must be able  to
	 * identify ourselves. As such, try to fix the `THIS_TASK' pointer by changing
	 * it to become the thiscpu_sched_current pointer  of our current CPU, or,  if
	 * that pointer is broken, use the current CPU's IDLE thread instead. */
#ifdef __x86_64__
	me = x86_failsafe_getcpu();
#else /* __x86_64__ */
	me = state->dcs_cpu;
	if unlikely(!VERIFY_ADDR(me))
		me = x86_failsafe_getcpu();
#endif /* !__x86_64__ */
	x86_repair_broken_tls_state_impl(me);
	COMPILER_BARRIER();
	/* Ok. If we're still alive, then the above ~should~ have just
	 * giving us  ~some~  semblance  of a  consistent  TLS  state. */

	printk(KERN_EMERG "Double fault at %p\n", pc);
	{
		struct ucpustate ustate;
#ifdef __x86_64__
		icpustate_to_ucpustate(&state->dcs_regs, &ustate);
		x86_dump_ucpustate_register_state(&ustate, (PHYS pagedir_t *)__rdcr3());
#else /* __x86_64__ */
		ucpustate_to_ucpustate(&state->dcs_regs, &ustate);
		x86_dump_ucpustate_register_state(&ustate, state->dcs_cr3);
#endif /* !__x86_64__ */
	}
	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_shouldtrap(KERNEL_DEBUGTRAP_ON_UNHANDLED_INTERRUPT))
		kernel_debugtrap(&state->dcs_regs, SIGBUS);
#ifndef CONFIG_NO_KERNEL_DEBUGGER
#ifdef __x86_64__
	dbg_enter(&panic_df_dbg_main, &state->dcs_regs);
#else /* __x86_64__ */
	dbg_enter(&panic_df_dbg_main, state->dcs_cr3, &state->dcs_regs);
#endif /* !__x86_64__ */
#else /* !CONFIG_NO_KERNEL_DEBUGGER */
	PREEMPTION_HALT();
#endif /* CONFIG_NO_KERNEL_DEBUGGER */
	__builtin_unreachable();
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_DOUBLE_FAULT_C */
