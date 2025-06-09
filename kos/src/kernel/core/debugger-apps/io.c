/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif(x -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_SRC_DEBUGGER_APPS_IO_C
#define GUARD_KERNEL_SRC_DEBUGGER_APPS_IO_C 1
#define DISABLE_BRANCH_PROFILING
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <debugger/util.h>
#include <kernel/except.h>
#include <kernel/mman.h>
#include <kernel/mman/mnode.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <sched/task.h>

#include <hybrid/align.h>

#include <kos/except.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/keyboard.h>
#include <sys/io.h>

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include <libdebuginfo/unwind.h>
#include <libdisasm/disassembler.h>
#include <libinstrlen/instrlen.h>
#include <libunwind/errno.h>
#include <libunwind/register.h>
#include <libunwind/unwind.h>

DECL_BEGIN

DBG_COMMAND(screen,
            "screen\n"
            "\tShow the original screen contents (before the debugger was entered)\n"
            "\tReturn back to the debugger once the user presses any key\n") {
	u16 key;
	dbg_beginshowscreen();
	/* Wait for the user to press a button. */
	do {
		key = dbg_getkey();
	} while (!KEY_ISDOWN(key));
	dbg_endshowscreen();
	return 0;
}

DBG_COMMAND(freeze,
            "freeze\n"
            "\tFree the debugger in an infinite loop (used to test the F12-reset function)\n") {
	for (;;)
		PREEMPTION_WAIT();
	return 0;
}

DBG_COMMAND(apply,
            "apply\n"
            "\tApply modifications made to the currently viewed register\n"
            "\tstate onto the return state (loaded when " AC_WHITE("exit") " is typed)\n") {
	dbg_rt_applyview();
	return 0;
}

DBG_COMMAND(undo,
            "undo\n"
            "\tUndo all unapplied changes to the return register state\n") {
	struct fcpustate fst;
	dbg_current = THIS_TASK;
	/* Reset the view's register state. */
	dbg_rt_getallregs(DBG_RT_REGLEVEL_ORIG, &fst);
	dbg_rt_setallregs(DBG_RT_REGLEVEL_VIEW, &fst);
	return 0;
}



#ifdef __port_t
DBG_COMMAND(inb,
            "inb PORT\n"
            "\tRead from PORT and display the read value on-screen\n",
            argc, argv) {
	uintptr_t port;
	u8 val;
	if (argc != 2)
		return DBG_STATUS_INVALID_ARGUMENTS;
	if (!dbg_evaladdr(argv[1], &port))
		return DBG_STATUS_INVALID_ARGUMENTS;
	val = inb((port_t)port);
	dbg_printf(DBGSTR("inb %#.4" PRIxN(__SIZEOF_PORT_T__) ": %#.2" PRIx8 " (%" PRIu8 ")\n"),
	          (port_t)port, val, val);
	return (uintptr_t)val;
}

DBG_COMMAND(inw,
            "inw PORT\n"
            "\tRead from PORT and display the read value on-screen\n",
            argc, argv) {
	uintptr_t port;
	u16 val;
	if (argc != 2)
		return DBG_STATUS_INVALID_ARGUMENTS;
	if (!dbg_evaladdr(argv[1], &port))
		return DBG_STATUS_INVALID_ARGUMENTS;
	val = inw((port_t)port);
	dbg_printf(DBGSTR("inw %#.4" PRIxN(__SIZEOF_PORT_T__) ": %#.4" PRIx16 " (%" PRIu16 ")\n"),
	           (port_t)port, val, val);
	return (uintptr_t)val;
}

DBG_COMMAND(inl,
            "inl PORT\n"
            "\tRead from PORT and display the read value on-screen\n",
            argc, argv) {
	uintptr_t port;
	u32 val;
	if (argc != 2)
		return DBG_STATUS_INVALID_ARGUMENTS;
	if (!dbg_evaladdr(argv[1], &port))
		return DBG_STATUS_INVALID_ARGUMENTS;
	val = inl((port_t)port);
	dbg_printf(DBGSTR("inl %#.4" PRIxN(__SIZEOF_PORT_T__) ": %#.8" PRIx32 " (%" PRIu32 ")\n"),
	           (port_t)port, val, val);
	return (uintptr_t)val;
}

DBG_COMMAND(outb,
            "outb PORT VAL\n"
            "\tOutput a given VAL to PORT\n",
            argc, argv) {
	uintptr_t port, val;
	if (argc != 3)
		return DBG_STATUS_INVALID_ARGUMENTS;
	if (!dbg_evaladdr(argv[1], &port) || !dbg_evalexpr(argv[2], &val))
		return DBG_STATUS_INVALID_ARGUMENTS;
	dbg_printf(DBGSTR("outb %#.4" PRIxN(__SIZEOF_PORT_T__) ", %#.2" PRIx8 " (%" PRIu8 ")\n"),
	           (port_t)port, (u8)val, (u8)val);
	outb((port_t)port, (u8)val);
	return val;
}

DBG_COMMAND(outw,
            "outw PORT VAL\n"
            "\tOutput a given VAL to PORT\n",
            argc, argv) {
	uintptr_t port, val;
	if (argc != 3)
		return DBG_STATUS_INVALID_ARGUMENTS;
	if (!dbg_evaladdr(argv[1], &port) || !dbg_evalexpr(argv[2], &val))
		return DBG_STATUS_INVALID_ARGUMENTS;
	dbg_printf(DBGSTR("outw %#.4" PRIxN(__SIZEOF_PORT_T__) ", %#.4" PRIx16 " (%" PRIu16 ")\n"),
	           (port_t)port, (u16)val, (u16)val);
	outw((port_t)port, (u16)val);
	return val;
}

DBG_COMMAND(outl,
            "outl PORT VAL\n"
            "\tOutput a given VAL to PORT\n",
            argc, argv) {
	uintptr_t port, val;
	if (argc != 3)
		return DBG_STATUS_INVALID_ARGUMENTS;
	if (!dbg_evaladdr(argv[1], &port) || !dbg_evalexpr(argv[2], &val))
		return DBG_STATUS_INVALID_ARGUMENTS;
	dbg_printf(DBGSTR("outl %#.4" PRIxN(__SIZEOF_PORT_T__) ", %#.8" PRIx32 " (%" PRIu32 ")\n"),
	           (port_t)port, (u32)val, (u32)val);
	outl((port_t)port, (u32)val);
	return val;
}
#endif /* __port_t */



DBG_COMMAND(m,
            "m [-bwlqp] ADDR [COUNT=16|page]\n"
            "\tPrint a hexdump of COUNT bytes of memory, starting at ADDR\n",
            argc, argv) {
	uintptr_t count, addr;
	unsigned int size = 1;
	while (argc > 2 && argv[1][0] == '-') {
		if (strcmp(argv[1], DBGSTR("-p")) == 0) {
			size = sizeof(void *);
		} else if (strcmp(argv[1], DBGSTR("-b")) == 0) {
			size = 1;
		} else if (strcmp(argv[1], DBGSTR("-w")) == 0) {
			size = 2;
		} else if (strcmp(argv[1], DBGSTR("-l")) == 0) {
			size = 4;
		} else if (strcmp(argv[1], DBGSTR("-q")) == 0) {
			size = 8;
		} else {
			return DBG_STATUS_INVALID_ARGUMENTS;
		}
		--argc;
		++argv;
	}
	if (argc <= 2)
		return DBG_STATUS_INVALID_ARGUMENTS;
	count = 16;
	if (!dbg_evaladdr(argv[1], &addr))
		return DBG_STATUS_INVALID_ARGUMENTS;
	if (argc >= 3) {
		if (strcmp(argv[2], DBGSTR("page")) == 0) {
			count = PAGESIZE - (addr & PAGEMASK);
		} else if (!dbg_evalexpr(argv[2], &count)) {
			return DBG_STATUS_INVALID_ARGUMENTS;
		}
	}
	switch (size) {
	case 1: dbg_printf(DBGSTR("%$[hex]\n"), (size_t)count, (uintptr_t)addr); break;
	case 2: dbg_printf(DBGSTR("%$I16[hex]\n"), (size_t)count, (uintptr_t)addr); break;
	case 4: dbg_printf(DBGSTR("%$I32[hex]\n"), (size_t)count, (uintptr_t)addr); break;
	case 8: dbg_printf(DBGSTR("%$I64[hex]\n"), (size_t)count, (uintptr_t)addr); break;
	default: break;
	}
	return 0;
}

DBG_COMMAND(mp,
            "mp ADDR [COUNT=16|page]\n"
            "\tAlias for " AC_WHITE("m -p ...") "\n",
            argc, argv) {
	uintptr_t count, addr;
	if (argc <= 2)
		return DBG_STATUS_INVALID_ARGUMENTS;
	count = 16;
	if (!dbg_evaladdr(argv[1], &addr))
		return DBG_STATUS_INVALID_ARGUMENTS;
	if (argc >= 3) {
		if (strcmp(argv[2], DBGSTR("page")) == 0) {
			count = PAGESIZE - (addr & PAGEMASK);
		} else if (!dbg_evalexpr(argv[2], &count)) {
			return DBG_STATUS_INVALID_ARGUMENTS;
		}
	}
	dbg_printf(DBGSTR("%$I[hex]\n"), (size_t)count, (uintptr_t)addr);
	return 0;
}


PRIVATE NOBLOCK ATTR_DBGTEXT ATTR_PURE WUNUSED bool
NOTHROW(KCALL is_pc)(void const *pc) {
	struct mnode *node;
	if (!ADDR_ISKERN(pc))
		goto nope;
	node = mman_mappings_locate(&mman_kernel, pc);
	if (!node)
		goto nope;
	return (node->mn_flags & MNODE_F_PEXEC) != 0;
nope:
	return false;
}

PRIVATE ATTR_DBGTEXT NONNULL((1)) ssize_t LIBDISASM_CC
debug_da_formater(struct disassembler *__restrict UNUSED(self),
                  unsigned int format_option) {
	char const *string;
	if (DISASSEMBLER_FORMAT_ISSUFFIX(format_option)) {
		string = AC_DEFATTR;
	} else {
		switch (format_option) {

		case DISASSEMBLER_FORMAT_REGISTER_PREFIX:
			string = AC_COLOR(ANSITTY_CL_BLACK, ANSITTY_CL_LIGHT_GRAY);
			break;

		case DISASSEMBLER_FORMAT_IMMEDIATE_PREFIX:
		case DISASSEMBLER_FORMAT_OFFSET_PREFIX:
		case DISASSEMBLER_FORMAT_SCALE_PREFIX:
			string = AC_FG(ANSITTY_CL_RED);
			break;

		case DISASSEMBLER_FORMAT_SYMBOL_PREFIX:
			string = AC_FG_WHITE;
			break;

		case DISASSEMBLER_FORMAT_PSEUDOOP_PREFIX:
			string = AC_FG(ANSITTY_CL_DARK_GRAY);
			break;

		case DISASSEMBLER_FORMAT_MNEMONIC_PREFIX:
			string = AC_FG(ANSITTY_CL_PURPLE);
			break;

		default: return 0;
		}
	}
	dbg_print(string);
	return 0;
}



DBG_COMMAND(disasm,
            "disasm [PC=registers.PC] [COUNT=<1 instruction>]\n"
            "\tPrint the disassembly of the given address range\n",
            argc, argv) {
	void const *addr, *current_pc;
	uintptr_t count;
	struct disassembler da;
	current_pc = dbg_getfaultpcreg(DBG_RT_REGLEVEL_VIEW);
	addr       = current_pc;
	if (argc >= 2) {
		if (!dbg_evaladdr(argv[1], (uintptr_t *)&addr))
			return DBG_STATUS_INVALID_ARGUMENTS;
	}
	disasm_init(&da, &dbg_printer, NULL, addr,
	            DISASSEMBLER_TARGET_CURRENT,
	            DISASSEMBLER_FNORMAL, 0);
	da.d_format = &debug_da_formater;
	if (argc >= 3) {
		if (sscanf(argv[2], DBGSTR("%lU"), &count) != 1)
			return DBG_STATUS_INVALID_ARGUMENTS;
		disasm_print_until(&da, (byte_t const *)addr + (size_t)count);
	} else {
		disasm_print_instruction(&da);
		dbg_putc('\n');
	}
	return 0;
}

DBG_COMMAND(instrlen,
            "instrlen [PC=registers.PC]\n"
            "\tPrint the length of the specified instruction\n",
            argc, argv) {
	void const *addr, *current_pc;
	size_t length;
	current_pc = dbg_getfaultpcreg(DBG_RT_REGLEVEL_VIEW);
	addr       = current_pc;
	if (argc >= 2) {
		if (!dbg_evaladdr(argv[1], (uintptr_t *)&addr))
			return DBG_STATUS_INVALID_ARGUMENTS;
	}
	length = instruction_length(addr, ISA_DEFAULT);
	dbg_printf(DBGSTR("%" PRIuSIZ "\n"), length);
	return 0;
}

DBG_COMMAND(trace,
            "trace\n"
            "\tDisplay a traceback for the current source location\n"
            "\tInlined functions are displayed in blue\n"
            "\tPC       IS   Name           Off   File    Line  Info\n"
            "\tC01936B0+5   [dwarf_fde_find+245] [dwarf.c:262] [...]\n"
            "\tPC:   Program counter position\n"
            "\tIS:   Instruction/inline size\n"
            "\tName: Name of the surrounding function\n"
            "\tOff:  Offset of PC from the surrounding function's start\n"
            "\tFile: Last component of the associated source's filename\n"
            "\tLine: Line number within File of the associated source code\n"
            "\tInfo: Additional information\n") {
#define LOG_STACK_REMAINDER 1
	struct fcpustate state;
	unwind_errno_t error;
#ifdef LOG_STACK_REMAINDER
	byte_t *last_good_sp;
#endif /* LOG_STACK_REMAINDER */
	dbg_rt_getallregs(DBG_RT_REGLEVEL_VIEW, &state);
#ifdef LOG_STACK_REMAINDER
	last_good_sp = fcpustate_getsp(&state);
#endif /* LOG_STACK_REMAINDER */
#if 0
#define SP_ARGS DBGSTR("sp=%p"), fcpustate_getsp(&state)
#else
#define SP_ARGS NULL
#endif

	if (dbg_rt_attrap(DBG_RT_REGLEVEL_VIEW)) {
		void *nextpc = dbg_instruction_trysucc(fcpustate_getpc(&state), fcpustate_getisa(&state));
		dbg_addr2line_printf(fcpustate_getpc(&state), nextpc, SP_ARGS);
		fcpustate_setpc(&state, nextpc);
	} else {
		dbg_addr2line_printf(dbg_instruction_trypred(fcpustate_getpc(&state),
		                                             fcpustate_getisa(&state)),
		                     fcpustate_getpc(&state), SP_ARGS);
	}
	for (;;) {
		struct fcpustate old_state;
		memcpy(&old_state, &state, sizeof(struct fcpustate));
		error = unwind_for_debug(fcpustate_getpc(&old_state) - 1,
		                         &unwind_getreg_fcpustate, &old_state,
		                         &unwind_setreg_fcpustate, &state);
		if (error != UNWIND_SUCCESS)
			break;
		dbg_addr2line_printf(dbg_instruction_trypred(fcpustate_getpc(&state),
		                                             fcpustate_getisa(&state)),
		                     fcpustate_getpc(&state), SP_ARGS);
#ifdef LOG_STACK_REMAINDER
		last_good_sp = fcpustate_getsp(&state);
#endif /* LOG_STACK_REMAINDER */
	}
	if (error != UNWIND_NO_FRAME)
		dbg_printf(DBGSTR("Unwind failure: %u\n"), error);
#ifdef LOG_STACK_REMAINDER
	if (ADDR_ISKERN(last_good_sp)) {
		void *minaddr, *endaddr;
		get_stack_for(&minaddr, &endaddr, last_good_sp);
		if (last_good_sp >= (byte_t *)minaddr &&
		    last_good_sp < (byte_t *)endaddr) {
			bool is_first = true;
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
			uintptr_t iter;
			iter = FLOOR_ALIGN((uintptr_t)last_good_sp, sizeof(void *));
			for (; iter < (uintptr_t)endaddr; iter += sizeof(void *))
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
			uintptr_t iter;
			iter  = CEIL_ALIGN((uintptr_t)last_good_sp, sizeof(void *));
			while (iter > (uintptr_t)minaddr)
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
			{
				void const *pc;
#ifndef __ARCH_STACK_GROWS_DOWNWARDS
				iter -= sizeof(void *);
#endif /* __ARCH_STACK_GROWS_DOWNWARDS */
				TRY {
					pc = *(void const **)iter;
				} EXCEPT {
					break;
				}
				if (!is_pc(pc))
					continue;
				if (is_first) {
					dbg_printf(DBGSTR("Analyzing remainder of stack:\n"));
					is_first = false;
				}
				dbg_addr2line_printf(dbg_instruction_trypred(pc, fcpustate_getisa(&state)),
				                     pc, DBGSTR("pc@%p"), iter);
			}
		}
	}
#endif /* LOG_STACK_REMAINDER */
#undef SP_ARGS
	return 0;
}

DBG_COMMAND(u,
            "u\n"
            "\tUnwind the current source location to its call-site\n") {
	struct fcpustate oldstate, newstate;
	unwind_errno_t error;
	void const *final_pc, *old_pc;
	dbg_rt_getallregs(DBG_RT_REGLEVEL_VIEW, &oldstate);
	memcpy(&newstate, &oldstate, sizeof(struct fcpustate));
	old_pc = fcpustate_getpc(&oldstate);
	if (!dbg_rt_attrap(DBG_RT_REGLEVEL_VIEW))
		old_pc = (byte_t const *)old_pc - 1;
	error = unwind_for_debug(old_pc,
	                         &unwind_getreg_fcpustate, &oldstate,
	                         &unwind_setreg_fcpustate, &newstate);
	if (error != UNWIND_SUCCESS) {
		dbg_printf(DBGSTR("Unwind failure: %u\n"), error);
		memcpy(&newstate, &oldstate, sizeof(struct fcpustate));
	} else {
		dbg_rt_setallregs(DBG_RT_REGLEVEL_VIEW, &newstate);
	}
	final_pc = fcpustate_getpc(&newstate);
	dbg_addr2line_printf(dbg_instruction_trypred(final_pc, fcpustate_getisa(&newstate)),
	                     final_pc, DBGSTR("sp=%p"), final_pc);
	return 0;
}



DBG_COMMAND(a2l,
            "a2l [ADDR=PC] [ADDR...]\n"
            "\tPrint the source location name for the given ADDR\n",
            argc, argv) {
	void const *addr, *current_pc;
	isa_t isa;
	isa = dbg_rt_getisa(DBG_RT_REGLEVEL_VIEW);
again:
	--argc;
	++argv;
	current_pc = dbg_getpcreg(DBG_RT_REGLEVEL_VIEW);
	current_pc = dbg_instruction_trypred(current_pc, isa);
	addr = current_pc;
	if (argc >= 1) {
		if (!dbg_evaladdr(argv[0], (uintptr_t *)&addr))
			return DBG_STATUS_INVALID_ARGUMENTS;
		current_pc = dbg_instruction_trysucc(addr, isa);
	}
	dbg_addr2line_printf(addr, current_pc, NULL);
	if (argc > 1)
		goto again;
	return 0;
}

DBG_COMMAND(_eval,
            "_eval EXPR...\n"
            "\tEvaluate the given expression and print the result\n",
            argc, argv) {
	--argc;
	++argv;
	for (; argc; --argc, ++argv) {
		uintptr_t result;
		char *expr = argv[0];
		if (!dbg_evalexpr(expr, &result))
			return 1;
		dbg_printf(DBGSTR("%q: " AC_WHITE("%#" PRIxSIZ) " (" AC_WHITE("%" PRIuSIZ) ")\n"),
		           expr, result, result);
	}
	return 0;
}

DBG_COMMAND(rawmagic,
            "rawmagic message\n"
            "\tOutput a given " AC_WHITE("message") " to magic\n",
            argc, argv) {
	if (argc != 2)
		return DBG_STATUS_INVALID_ARGUMENTS;
	printk(KERN_RAW "%%{%s}", argv[1]);
	return 0;
}

DBG_COMMAND(except,
            "except\n"
            "\tPrint the currently active exception\n") {
	except_printf(NULL);
	return 0;
}


DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_APPS_IO_C */
