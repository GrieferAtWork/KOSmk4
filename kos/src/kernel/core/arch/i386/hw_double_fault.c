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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_HW_DOUBLE_FAULT_C
#define GUARD_KERNEL_CORE_ARCH_I386_HW_DOUBLE_FAULT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/debugger.h>
#include <kernel/debugtrap.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/types.h>

#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <signal.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/* Note that unlike all other interrupt handlers, the double-fault handler
 * gets invoked with a ucpustate, rather than an icpustate (at least on i386).
 * This is required since a double fault isn't handled on the stack of the
 * thread that caused the exception, but rather on its own stack, meaning that
 * its return-sp isn't at the end of the irregs field when it points to kernel-
 * space.
 * On x86_64, this isn't the case since all irregs always contain a stack pointer,
 * with the double-fault handler simply using the alternate-stack mechanism for
 * safely executing on an alternate stack. */
struct df_cpustate {
	PHYS pagedir_t  *dcs_cr3;
#ifdef __x86_64__
	struct icpustate dcs_regs;
#else /* __x86_64__ */
	struct ucpustate dcs_regs;
#endif /* !__x86_64__ */
};


INTDEF void FCALL
x86_dump_ucpustate_register_state(struct ucpustate *__restrict ustate, PHYS pagedir_t *cr3);

#ifndef CONFIG_NO_DEBUGGER
PRIVATE void KCALL
panic_df_dbg_main(void *cr3) {
	dbg_exitstate.fcs_coregs.co_cr3 = (uintptr_t)cr3;
	dbg_viewstate.fcs_coregs.co_cr3 = (uintptr_t)cr3;
	dbg_printf(DF_COLOR(DBG_COLOR_WHITE, DBG_COLOR_MAROON, "Double fault"));
	dbg_printf("\n"
	           "%[vinfo:"
	           "file: " DF_WHITE("%f") " (line " DF_WHITE("%l") ", column " DF_WHITE("%c") ")\n"
	           "func: " DF_WHITE("%n") "\n"
	           "addr: " DF_WHITE("%p") "\n"
	           "]",
	           fcpustate_getpc(&dbg_exitstate));
	dbg_main(0);
}
#endif


/* Double fault handler. */
INTERN struct df_cpustate *FCALL
x86_cirq_08(struct df_cpustate *__restrict state) {
#ifdef __x86_64__
	printk(KERN_EMERG "Double fault at %p\n", state->dcs_regs.ucs_rip);
#else /* __x86_64__ */
	printk(KERN_EMERG "Double fault at %p\n", state->dcs_regs.ucs_eip);
#endif /* !__x86_64__ */
	{
		struct ucpustate ustate;
		memcpy(&ustate, &state->dcs_regs, sizeof(ustate));
		x86_dump_ucpustate_register_state(&ustate, state->dcs_cr3);
	}
	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_enabled() && (kernel_debugtrap_on & KERNEL_DEBUGTRAP_ON_UNHANDLED_INTERRUPT))
		kernel_debugtrap(&state->dcs_regs, SIGBUS);
#ifndef CONFIG_NO_DEBUGGER
	dbg_enter(&state->dcs_regs, &panic_df_dbg_main, state->dcs_cr3);
#else
	PREEMPTION_HALT();
#endif
	return state;
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_HW_DOUBLE_FAULT_C */
