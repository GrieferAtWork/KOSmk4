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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_UNHANDLED_IDT_C
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_UNHANDLED_IDT_C 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/entry.h>
#include <debugger/function.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <kernel/addr2line.h>
#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/paging.h>
#include <kernel/pic.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/vm.h>
#include <sched/cpu.h>
#include <sched/task.h>

#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <signal.h>
#include <stddef.h>

#include <libinstrlen/instrlen.h>
#include <libregdump/cpu-state.h>
#include <libregdump/x86.h>
#include <libunwind/unwind.h>

DECL_BEGIN



PRIVATE ATTR_CONST char const *FCALL get_interrupt_name(uintptr_t intno) {
	char const *result;
	switch (intno & 0xff) {

	case X86_E_SYSTEM_DE & 0xff: result = "DIVIDE_BY_ZERO"; break;
	case X86_E_SYSTEM_DB & 0xff: result = "DEBUG"; break;
	case X86_E_SYSTEM_NMI & 0xff: result = "NON_MASKABLE_INTERRUPT"; break;
	case X86_E_SYSTEM_BP & 0xff: result = "BREAKPOINT"; break;
	case X86_E_SYSTEM_OF & 0xff: result = "OVERFLOW"; break;
	case X86_E_SYSTEM_BR & 0xff: result = "BOUND_RANGE_EXCEEDED"; break;
	case X86_E_SYSTEM_UD & 0xff: result = "INVALID_OPCODE"; break;
	case X86_E_SYSTEM_NM & 0xff: result = "DEVICE_NOT_AVAILABLE"; break;
	case X86_E_SYSTEM_DF & 0xff: result = "DOUBLE_FAULT"; break;
	case X86_E_SYSTEM_TS & 0xff: result = "INVALID_TSS"; break;
	case X86_E_SYSTEM_NP & 0xff: result = "SEGMENT_NOT_PRESENT"; break;
	case X86_E_SYSTEM_SS & 0xff: result = "STACK_SEGMENT_FAULT"; break;
	case X86_E_SYSTEM_GP & 0xff: result = "GENERAL_PROTECTION_FAULT"; break;
	case X86_E_SYSTEM_PF & 0xff: result = "PAGE_FAULT"; break;
	case X86_E_SYSTEM_MF & 0xff: result = "X87_FLOATING_POINT_EXCEPTION"; break;
	case X86_E_SYSTEM_AC & 0xff: result = "ALIGNMENT_CHECK"; break;
	case X86_E_SYSTEM_MC & 0xff: result = "MACHINE_CHECK"; break;
	case X86_E_SYSTEM_XM & 0xff: result = "SIMD_FLOATING_POINT_EXCEPTION"; break;
	case X86_E_SYSTEM_VE & 0xff: result = "VIRTUALIZATION_EXCEPTION"; break;
	case X86_E_SYSTEM_SX & 0xff: result = "SECURITY_EXCEPTION"; break;

	default: result = NULL; break;
	}
	return result;
}

PRIVATE char const *FCALL
get_interrupt_desc(uintptr_t intno, uintptr_t ecode) {
	char const *result = NULL;
	switch (intno & 0xff) {

	case X86_E_SYSTEM_PF & 0xff:
		if (!(ecode & 1))
			result = "PAGE_NOT_PRESENT";
		else if (ecode & 8)
			result = "RESERVED_PAGING_BIT_SET";
		else if (ecode & 16)
			result = "INSTRUCTION_FETCH";
		else if (ecode & 2)
			result = "ILLEGAL_WRITE";
		break;

	default:
		break;
	}
	return result;
}


INTERN ssize_t LIBREGDUMP_CC
indent_regdump_print_format(struct regdump_printer *__restrict self,
                            unsigned int format_option) {
	switch (format_option) {

	case REGDUMP_FORMAT_INDENT:
		return (*self->rdp_printer)(self->rdp_printer_arg, "    ", 4);

	default:
		break;
	}
	return 0;
}


INTERN void FCALL
x86_dump_ucpustate_register_state(struct ucpustate *__restrict ustate,
                                  PHYS pagedir_t *cr3) {
	unsigned int error;
	bool is_first;
	struct regdump_printer rd_printer;
	struct desctab tab;
	rd_printer.rdp_printer     = &kprinter;
	rd_printer.rdp_printer_arg = (void *)KERN_EMERG;
	rd_printer.rdp_format      = &indent_regdump_print_format;
	regdump_gpregs(&rd_printer, &ustate->ucs_gpregs);
	regdump_ip(&rd_printer, ucpustate_getpc(ustate));
	regdump_flags(&rd_printer, ustate->ucs_pflags);
	printk(KERN_EMERG "\n");
	regdump_sgregs_with_cs_ss_tr_ldt(&rd_printer, &ustate->ucs_sgregs,
	                                 ustate->ucs_cs, ustate->ucs_ss,
	                                 __str(), __sldt());
	__sgdt(&tab);
	regdump_gdt(&rd_printer, &tab);
	__sidt(&tab);
	regdump_idt(&rd_printer, &tab);
	regdump_cr0(&rd_printer, __rdcr0());
	printk(KERN_EMERG "    %%cr2 %p\n", __rdcr2());
	regdump_cr4(&rd_printer, __rdcr4());
	printk(KERN_EMERG "    %%cr3 %p\n", (void *)cr3);
	addr2line_printf(&kprinter, (void *)KERN_RAW,
	                 ucpustate_getpc(ustate),
	                 (uintptr_t)instruction_trysucc((void const *)ucpustate_getpc(ustate)),
	                 "Caused here [sp=%p]",
	                 ucpustate_getsp(ustate));
	is_first = true;
	for (;;) {
		struct ucpustate old_state;
		old_state = *ustate;
		error = unwind((void *)(is_first
		                        ? ucpustate_getpc(&old_state)
		                        : ucpustate_getpc(&old_state) - 1),
		               &unwind_getreg_ucpustate, &old_state,
		               &unwind_setreg_ucpustate, ustate);
		if (error != UNWIND_SUCCESS)
			break;
		is_first = false;
		addr2line_printf(&kprinter, (void *)KERN_RAW,
		                 (uintptr_t)instruction_trypred((void const *)ucpustate_getpc(ustate)),
		                 ucpustate_getpc(ustate), "Called here [sp=%p]",
		                 ucpustate_getsp(ustate));
	}
	if (error != UNWIND_NO_FRAME)
		printk(KERN_EMERG "Unwind failure: %u\n", error);
}


#ifdef CONFIG_HAVE_DEBUGGER
struct panic_args {
	uintptr_t ecode;
	uintptr_t intno;
};

PRIVATE ATTR_DBGTEXT void KCALL
panic_uhi_dbg_main(void *arg) {
	struct panic_args *args;
	char const *name;
	args = (struct panic_args *)arg;
	dbg_printf(DBGSTR(DF_COLOR(DBG_COLOR_WHITE, DBG_COLOR_MAROON, "Unhandled interrupt")
	                  " [int: " DF_WHITE("%#.2I8x") " (" DF_WHITE("%I8u") ")]"),
	           (u8)args->intno,
	           (u8)args->intno);
	if (args->ecode)
		dbg_printf(DBGSTR(" [ecode=" DF_WHITE("%#.8I32x") "]"), (u32)args->ecode);
	name = get_interrupt_name(args->intno);
	if (name != NULL) {
		char const *desc;
		desc = get_interrupt_desc(args->intno, args->ecode);
		dbg_printf(DBGSTR(" [" DF_WHITE("%s")), name);
		if (desc)
			dbg_printf(DBGSTR(":" DF_WHITE("%s")), desc);
		dbg_putc(']');
	}
	dbg_printf(DBGSTR("\n"
	                  "%[vinfo:"
	                  "file: " DF_WHITE("%f") " (line " DF_WHITE("%l") ", column " DF_WHITE("%c") ")\n"
	                  "func: " DF_WHITE("%n") "\n"
	                  "addr: " DF_WHITE("%p") "\n"
	                  "]"),
	           fcpustate_getpc(&x86_dbg_exitstate.de_state));
	dbg_main(0);
}
#endif /* CONFIG_HAVE_DEBUGGER */


INTERN struct icpustate *FCALL
x86_handle_unhandled_idt(struct icpustate *__restrict state,
                         uintptr_t ecode, uintptr_t intno) {
	struct ucpustate ustate;
	__cli();
	icpustate_to_ucpustate(state, &ustate);
	printk(KERN_EMERG "Unhandled interrupt %Ix (%Iu)", intno, intno);
	{
		char const *name, *desc;
		name = get_interrupt_name(intno);
		desc = get_interrupt_desc(intno, ecode);
		if (name) {
			printk(KERN_EMERG " [%s%s%s]",
			       name, desc ? ":" : "", desc ? desc : "");
		}
	}
	if (ecode != 0)
		printk(KERN_EMERG " [ecode=%#Ix]", ecode);
	if (intno == 0xe)
		printk(KERN_EMERG " [%%cr2=%p]", __rdcr2());
	printk(KERN_EMERG "\n");
	x86_dump_ucpustate_register_state(&ustate, (PHYS pagedir_t *)__rdcr3());
	if (THIS_TASK != &_boottask) {
		printk(KERN_EMERG "Boot task state:\n");
		scpustate_to_ucpustate(_boottask.t_sched.s_state, &ustate);
		x86_dump_ucpustate_register_state(&ustate, _boottask.t_vm->v_pdir_phys_ptr);
	}
	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_enabled() && (kernel_debugtrap_on & KERNEL_DEBUGTRAP_ON_UNHANDLED_INTERRUPT))
		kernel_debugtrap(state, SIGBUS);
#ifdef CONFIG_HAVE_DEBUGGER
	{
		struct panic_args args;
		if (intno >= X86_INTERRUPT_PIC1_BASE)
			X86_PIC_EOI(intno);
		args.ecode = ecode;
		args.intno = intno;
		state = dbg_enter_r(&panic_uhi_dbg_main,
		                    &args, state);
	}
#else /* CONFIG_HAVE_DEBUGGER */
	PREEMPTION_HALT();
#endif /* !CONFIG_HAVE_DEBUGGER */
	return state;
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_UNHANDLED_IDT_C */
