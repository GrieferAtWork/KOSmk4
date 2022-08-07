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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_INVALID_TSS_C
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_INVALID_TSS_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/x86/fault.h> /* x86_handle_invalid_tss() */
#include <kernel/x86/idt.h>   /* IDT_CONFIG_ISTRAP() */

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/except.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/x86/gdt.h>

#include <assert.h>

DECL_BEGIN

INTERN ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL
x86_handle_invalid_tss(struct icpustate *__restrict state, uintptr_t ecode) {
	static_assert(!IDT_CONFIG_ISTRAP(X86_E_SYSTEM_TS & 0xff)); /* #TS  Invalid TSS */

	/* TODO:
	 * """
	 * If  the NT flag is set and  the processor is in IA-32e mode
	 * the IRET instruction causes a general protection exception.
	 * """
	 * Maybe we should add explicit handling for this? */

	/* Because  user-space programs are able to set `EFLAGS.NT=1', and the KOS
	 * kernel doesn't make use of hardware  task switching, but does make  use
	 * of `iret' for the purpose of loading  PSP+PIP at the same time, we  run
	 * into a problem because the behavior of `iret' is altered when said flag
	 * is set (`EFLAGS.NT=1').
	 *
	 * Instead of doing a normal iret, the instruction will try to do:
	 * >> __ltr(PERCPU(thiscpu_x86_tss).t_link);
	 *
	 * Because `PERCPU(thiscpu_x86_tss).t_link == 0', this will always
	 * fail because it  would try to  load a NULL-segment  descriptor.
	 *
	 * The  solution to this  problem is to simply  detect this situation and
	 * manually clear EFLAGS.NT before re-attempting the iret. This does mean
	 * that  we clear said  flag in situations where  user-space might not be
	 * expecting this, but without this hack,  it'd be the kernel that  would
	 * crash  when (as far  as I'm concerned) correct  use of "iret" suddenly
	 * starts causing exceptions and going into the debugger and so on... */
	if (ecode == 0) { /* This `0' is the same `0' from `PERCPU(thiscpu_x86_tss).t_link' */
		uintptr_t eflags;
		byte_t const *pc;
		eflags = icpustate_getpflags(state);
		if (!(eflags & EFLAGS_NT))
			goto not_iret_with_nt;
		pc = (byte_t const *)icpustate_getpc(state);
		if (!ADDR_ISUSER(pc)) {
			byte_t const *iter = pc;
			/* Check that the faulting instruction is "iret" */
#ifdef __x86_64__
			if (*iter == 0x48)
				++iter; /* REX.W */
#endif /* __x86_64__ */
			if (*iter == 0xcf) {
				/* iret */
			} else {
				goto not_iret_with_nt;
			}
		}

		/* Yup: it's the EFLAGS.NT problem... (clear the flag and resume execution) */
		printk(KERN_WARNING "[x86] Clear EFLAGS.NT after failed iret at %p\n", pc);
		eflags &= ~EFLAGS_NT;
		icpustate_setpflags(state, eflags);
		return state;
	}
not_iret_with_nt:

	if (icpustate_isuser(state)) {
		/* TODO: Should probably throw some kind of exception */
	}

	/* Fallback: handle as an unhandled interrupt. */
	return x86_handle_unhandled_idt(state, ecode, X86_E_SYSTEM_TS & 0xff);
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_INVALID_TSS_C */
