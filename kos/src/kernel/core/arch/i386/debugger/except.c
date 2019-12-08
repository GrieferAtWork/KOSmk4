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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_EXCEPT_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_EXCEPT_C 1
#define DISABLE_BRANCH_PROFILING 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_DEBUGGER
#include <debugger/function.h>
#include <kernel/except.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <sched/except-handler.h>
#include <sched/task.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/kernel/cpu-state.h>

#include <string.h>

#include <libinstrlen/instrlen.h>

DECL_BEGIN

#define PAGEFAULT_F_PRESENT     0x0001 /* FLAG: The accessed page is present (Check for LOA) */
#define PAGEFAULT_F_WRITING     0x0002 /* FLAG: The fault happened as a result of a memory write (Check for COW) */
#define PAGEFAULT_F_USERSPACE   0x0004 /* FLAG: The fault occurred while in user-space */
#define PAGEFAULT_F_RESBIT      0x0008 /* FLAG: A reserved page bit is set */
#define PAGEFAULT_F_INSTRFETCH  0x0010 /* FLAG: The fault happened while fetching instructions.
                                        * NOTE: This flag isn't guarantied to be set, though an
                                        *       instruction-fetch fault can also easily be detected
                                        *       by comparing `%eip' with `%cr2' */

DATDEF byte_t x86_memcpy_nopf_rep_pointer[];
DATDEF byte_t x86_memcpy_nopf_ret_pointer[];

#ifdef __x86_64__
#define ir_pip ir_rip
#else /* __x86_64__ */
#define ir_pip ir_eip
#endif /* !__x86_64__ */

INTERN ATTR_DBGTEXT ATTR_RETNONNULL NONNULL((1)) struct icpustate *
NOTHROW(FCALL x86_handle_dbg_pagefault)(struct icpustate *__restrict state, uintptr_t ecode) {
	/* Use a dedicated #PF handler for the debugger, so-as to prevent crashes arising when
	 * the debugger is invoked for some kind of problem related to page initialization.
	 * Also: This way, the debugger accessing memory will never cause disk activity, or
	 *       other side-effects such as VIO callbacks or the like. */
	uintptr_t pc;
	uintptr_t addr;
	/* Check for memcpy_nopf() */
	if unlikely(state->ics_irregs.ir_pip == (uintptr_t)x86_memcpy_nopf_rep_pointer) {
		state->ics_irregs.ir_pip = (uintptr_t)x86_memcpy_nopf_ret_pointer;
		return state;
	}
	addr = __rdcr2();
#define IS_USER() (ecode & PAGEFAULT_F_USERSPACE)
#ifdef __x86_64__
	if (state->ics_irregs.ir_rflags & EFLAGS_IF)
		__sti();
#else /* __x86_64__ */
	if (state->ics_irregs_k.ir_eflags & EFLAGS_IF)
		__sti();
#endif /* !__x86_64__ */
	pc = irregs_rdip(&state->ics_irregs);
#if 1
	printk(DBGSTR(KERN_DEBUG "[dbg] Page fault at %p [pc=%p] [ecode=%#x]\n"),
	       (uintptr_t)addr, pc, ecode);
#endif
	if (pc == (uintptr_t)addr) {
		/* This can happen when trying to call an invalid function pointer.
		 * -> Try to unwind this happening. */
		uintptr_t old_pip;
		uintptr_t sp = irregs_rdsp(&state->ics_irregs);
		if (sp != (uintptr_t)(&state->ics_irregs + 1) && sp >= KERNEL_BASE)
			goto not_a_badcall;
		TRY {
			old_pip = *(uintptr_t *)sp;
		} EXCEPT {
			if (!was_thrown(E_SEGFAULT))
				RETHROW();
			goto not_a_badcall;
		}
#ifdef __x86_64__
		if (IS_USER() != (old_pip >= KERNEL_BASE))
			goto not_a_badcall;
		irregs_wrip(&state->ics_irregs, old_pip);
		irregs_wrsp(&state->ics_irregs, sp + 8);
#else /* __x86_64__ */
		if (sp != (uintptr_t)(&state->ics_irregs_k + 1) ||
		    IS_USER()) {
			if (old_pip >= KERNEL_BASE)
				goto not_a_badcall;
			irregs_wrip(&state->ics_irregs_k, old_pip);
			state->ics_irregs_u.ir_esp += 4;
		} else {
			if (old_pip < KERNEL_BASE)
				goto not_a_badcall;
			state->ics_irregs_k.ir_eip = old_pip;
			state = (struct icpustate *)memmoveup((byte_t *)state + sizeof(void *), state,
			                                      OFFSET_ICPUSTATE_IRREGS +
			                                      SIZEOF_IRREGS_KERNEL);
		}
#endif /* !__x86_64__ */
		PERTASK_SET(this_exception_faultaddr, (void *)old_pip);
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_NOTEXECUTABLE));
		PERTASK_SET(this_exception_pointers[0], (uintptr_t)addr);
#if PAGEFAULT_F_USERSPACE == E_SEGFAULT_CONTEXT_USERCODE && \
    PAGEFAULT_F_WRITING == E_SEGFAULT_CONTEXT_WRITING
		PERTASK_SET(this_exception_pointers[1],
		            (uintptr_t)(E_SEGFAULT_CONTEXT_FAULT) |
		            (uintptr_t)(ecode & (PAGEFAULT_F_USERSPACE | PAGEFAULT_F_WRITING)));
#else
		PERTASK_SET(this_exception_pointers[1],
		            (uintptr_t)(E_SEGFAULT_CONTEXT_FAULT) |
		            (uintptr_t)(ecode & PAGEFAULT_F_USERSPACE ? E_SEGFAULT_CONTEXT_USERCODE : 0) |
		            (uintptr_t)(ecode & PAGEFAULT_F_WRITING ? E_SEGFAULT_CONTEXT_WRITING : 0));
#endif
		{
			unsigned int i;
			for (i = 2; i < EXCEPTION_DATA_POINTERS; ++i)
				PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
		}
		goto do_unwind_state;
	}
not_a_badcall:
	if (ecode & PAGEFAULT_F_WRITING) {
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_READONLY));
	} else if ((ecode & PAGEFAULT_F_INSTRFETCH) || pc == (uintptr_t)addr) {
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_NOTEXECUTABLE));
	} else {
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_UNMAPPED));
	}
	/*set_exception_pointers:*/
	PERTASK_SET(this_exception_pointers[0], (uintptr_t)addr);
#if PAGEFAULT_F_USERSPACE == E_SEGFAULT_CONTEXT_USERCODE && \
    PAGEFAULT_F_WRITING == E_SEGFAULT_CONTEXT_WRITING
	PERTASK_SET(this_exception_pointers[1],
	            (uintptr_t)(E_SEGFAULT_CONTEXT_FAULT) |
	            (uintptr_t)(ecode & (PAGEFAULT_F_USERSPACE | PAGEFAULT_F_WRITING)));
#else
	PERTASK_SET(this_exception_pointers[1],
	            (uintptr_t)(E_SEGFAULT_CONTEXT_FAULT) |
	            (uintptr_t)(ecode & PAGEFAULT_F_USERSPACE ? E_SEGFAULT_CONTEXT_USERCODE : 0) |
	            (uintptr_t)(ecode & PAGEFAULT_F_WRITING ? E_SEGFAULT_CONTEXT_WRITING : 0));
#endif
	{
		unsigned int i;
		for (i = 2; i < EXCEPTION_DATA_POINTERS; ++i)
			PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
#if EXCEPT_BACKTRACE_SIZE != 0
		for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i)
			PERTASK_SET(this_exception_trace[i], (void *)0);
#endif
	}
	/* Always make the state point to the instruction _after_ the one causing the problem. */
	irregs_wrip(&state->ics_irregs, (uintptr_t)instruction_trysucc((void const *)pc));
	PERTASK_SET(this_exception_faultaddr, (void *)pc);
do_unwind_state:
	x86_userexcept_unwind_interrupt(state);
}


DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_EXCEPT_C */
