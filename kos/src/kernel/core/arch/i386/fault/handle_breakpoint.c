/*[[[magic
// Optimize this file for size
local opt = options.setdefault("GCC.options", []);
opt.removeif([](e) -> e.startswith("-O"));
opt.append("-Os");
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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_HANDLE_BREAKPOINT_C
#define GUARD_KERNEL_CORE_ARCH_I386_HANDLE_BREAKPOINT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/debugger.h>
#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/path.h>
#include <kernel/mman/execinfo.h>
#include <kernel/panic.h>
#include <kernel/rt/except-handler.h>
#include <kernel/x86/fault.h> /* x86_handle_stackfault(), x86_handle_gpf(), x86_handle_illegal_instruction() */
#include <kernel/x86/idt.h>
#include <sched/group.h>
#include <sched/task.h>

#include <kos/kernel/cpu-state-helpers.h>

#include <assert.h>
#include <inttypes.h>
#include <signal.h>
#include <stddef.h>

#include <libinstrlen/instrlen.h>

DECL_BEGIN

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
PRIVATE void KCALL
dbg_handle_breakpoint(void *faultpc, void *resumepc) {
	/* We are now in debugger-mode. */
	dbg_savecolor();
	/* If the kernel hasn't been poisoned, tell the user that they are
	 * free to CTRL+D the debugger to resume normal system operations. */
	if (!kernel_poisoned()) {
		PRIVATE ATTR_DBGSTRINGS char const nonfatal_msg[] = "Non-fatal! (press CTRL+D to resume)";
		dbg_setcolor(ANSITTY_CL_LIME, ANSITTY_CL_DARK_GRAY);
		dbg_pprint(0, dbg_screen_height - 1, nonfatal_msg);
	}
	{
		struct mexecinfo *ei;
		ei = &FORMMAN(dbg_current->t_mman, thismman_execinfo);
		dbg_setcolor(ANSITTY_CL_RED, ANSITTY_CL_GREY);
		dbg_print(DBGSTR("Breakpoint "));
		if (ei->mei_path && ei->mei_dent) {
			path_printent(ei->mei_path,
			              ei->mei_dent->fd_name,
			              ei->mei_dent->fd_namelen,
			              &dbg_printer, NULL);
			dbg_putc(' ');
		}
	}
	{
		pid_t tid, pid;
		tid = task_getroottid_of(dbg_current);
		dbg_printf(DBGSTR("tid:%" PRIuN(__SIZEOF_PID_T__)), tid);
		pid = task_getrootpid_of(dbg_current);
		if (pid != tid)
			dbg_printf(DBGSTR(" pid:%" PRIuN(__SIZEOF_PID_T__)), pid);
	}
	dbg_loadcolor();
	dbg_putc('\n');
	{
		char const *reason_message = DBGSTR(AC_RED("Unknown cause"));
		byte_t opcode_byte;
		if (dbg_readmemory(faultpc, &opcode_byte, 1) == 0) {
			if (opcode_byte == 0xcc) {
				reason_message = DBGSTR(AC_WHITE("int3"));
			} else if (opcode_byte == 0xcd) {
				if (dbg_readmemory((byte_t *)faultpc + 1, &opcode_byte, 1) == 0 && opcode_byte == 0x03)
					reason_message = DBGSTR(AC_WHITE("int $3"));
			}
		}
		dbg_addr2line_printf(faultpc, resumepc, reason_message);
	}

	/* Switch over to the debugger CLI */
	dbg_main(0);
}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */



INTERN ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL
x86_handle_breakpoint(struct icpustate *__restrict state) {
	static_assert(!IDT_CONFIG_ISTRAP(0x03)); /* #BP  Breakpoint */
	byte_t const *pc, *faultpc;
	bool isuser;
	pc      = icpustate_getpc(state);
	isuser  = icpustate_isuser(state);
	faultpc = pc - 1;
	if (faultpc[0] == 0xcc) {
		/* int3 instruction */
	} else if (faultpc[0] == 0x03 && faultpc[-1] == 0xcd) {
		/* int $0x03 instruction */
		--faultpc;
	} else {
		/* Fallback: Some other kind of instruction?
		 * >> shouldn't really happen, unless user-space is tinkering
		 *    with  backing   memory  on   a  multi-core   machine... */
		faultpc = pc;
		pc      = instruction_trysucc(pc, icpustate_getisa(state));
		icpustate_setpc(state, pc);
	}

	/* First case: If enabled, let debug traps handle this. */
	if (kernel_debugtrap_enabled()) {
		if (isuser ? (kernel_debugtrap_on & KERNEL_DEBUGTRAP_ON_USER_BREAKPOINT)
		           : (kernel_debugtrap_on & KERNEL_DEBUGTRAP_ON_KERNEL_BREAKPOINT)) {
			struct debugtrap_reason reason;
			reason.dtr_signo  = SIGTRAP;
			reason.dtr_reason = DEBUGTRAP_REASON_SWBREAK;
			reason.dtr_ptrarg = (void *)faultpc;
			/* Trigger a debugger trap at last valid text location. */
			state = kernel_debugtrap_r(state, &reason);
			return state;
		}
	}

	/* Next up: Let the builtin debugger deal with it. */
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
	if (isuser ? (kernel_debug_on & KERNEL_DEBUG_ON_USER_BREAKPOINT)
	           : (kernel_debug_on & KERNEL_DEBUG_ON_KERNEL_BREAKPOINT)) {
		STRUCT_DBG_ENTRY_INFO(2) entry;
		entry.ei_argc    = 2;
		entry.ei_argv[0] = (void *)faultpc;
		entry.ei_argv[1] = (void *)pc;
		entry.ei_entry   = (dbg_entry_t)&dbg_handle_breakpoint;
		/* Enter the debugger. */
		dbg_enter((struct dbg_entry_info *)&entry, state);
		__builtin_unreachable();
	}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

	/* Fallback: Throw an E_BREAKPOINT exception. */
	PERTASK_SET(this_exception_code, EXCEPT_CODEOF(E_BREAKPOINT));
	PERTASK_SET(this_exception_faultaddr, faultpc);
	{
		unsigned int i;
		for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i)
			PERTASK_SET(this_exception_args.e_pointers[i], 0);
	}
	except_throw_current_at_icpustate(state);
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_HANDLE_BREAKPOINT_C */
