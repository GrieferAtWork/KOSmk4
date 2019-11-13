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
#ifndef GUARD_KERNEL_SRC_DEBUGGER_IO_C
#define GUARD_KERNEL_SRC_DEBUGGER_IO_C 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <kernel/debugger.h>
#ifndef CONFIG_NO_DEBUGGER
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/vm.h>
#include <sched/task.h>

#include <hybrid/align.h>

#include <kos/kernel/cpu-state-helpers.h>
#include <sys/io.h>

#include <stdio.h>
#include <string.h>

#include <libdisasm/disassembler.h>
#include <libinstrlen/instrlen.h>
#include <libunwind/unwind.h>

DECL_BEGIN

DEFINE_DEBUG_FUNCTION(
		"freeze",
		"freeze\n"
		"\tFree the debugger in an infinite loop (used to test the F12-reset function)\n",
		argc, argv) {
	for (;;)
		PREEMPTION_WAIT();
	return 0;
}

DEFINE_DEBUG_FUNCTION(
		"apply",
		"apply\n"
		"\tApply modifications made to the currently viewed register\n"
		"\tstate onto the return state (loaded when `exit' is typed)\n"
		, argc, argv) {
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	dbg_applyreg();
	return 0;
}

DEFINE_DEBUG_FUNCTION(
		"undo",
		"undo\n"
		"\tUndo all unapplied changes to the return register state\n"
		, argc, argv) {
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	if (THIS_TASK != debug_original_thread)
		dbg_impersonate_thread(debug_original_thread);
	memcpy(&dbg_viewstate, &dbg_origstate, sizeof(dbg_origstate));
	return 0;
}


#define LOG_STACK_REMAINDER 1

DEFINE_DEBUG_FUNCTION(
		"inb",
		"inb PORT\n"
		"\tRead from PORT and display the read value on-screen\n",
		argc, argv) {
	uintptr_t port;
	u8 val;
	if (argc != 2)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	if (!dbg_evaladdr(argv[1], &port))
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	val = inb((port_t)port);
	dbg_printf(DBGSTR("inb %#.4I16x: %#.2I8x (%I8u)\n"), (u16)port, val, val);
	return (uintptr_t)val;
}
DEFINE_DEBUG_FUNCTION(
		"inw",
		"inw PORT\n"
		"\tRead from PORT and display the read value on-screen\n",
		argc, argv) {
	uintptr_t port;
	u16 val;
	if (argc != 2)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	if (!dbg_evaladdr(argv[1], &port))
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	val = inw((port_t)port);
	dbg_printf(DBGSTR("inw %#.4I16x: %#.4I16x (%I16u)\n"), (u16)port, val, val);
	return (uintptr_t)val;
}

DEFINE_DEBUG_FUNCTION(
		"inl",
		"inl PORT\n"
		"\tRead from PORT and display the read value on-screen\n",
		argc, argv) {
	uintptr_t port;
	u32 val;
	if (argc != 2)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	if (!dbg_evaladdr(argv[1], &port))
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	val = inl((port_t)port);
	dbg_printf(DBGSTR("inl %#.4I16x: %#.8I32x (%I32u)\n"), (u16)port, val, val);
	return (uintptr_t)val;
}

DEFINE_DEBUG_FUNCTION(
		"outb",
		"outb PORT VAL\n"
		"\tOutput a given VAL to PORT\n",
		argc, argv) {
	uintptr_t port, val;
	if (argc != 3)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	if (!dbg_evaladdr(argv[1], &port) || !dbg_evalexpr(argv[2], &val))
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	dbg_printf(DBGSTR("outb %#.4I16x, %#.2I8x (%I8u)\n"), (u16)port, (u8)val, (u8)val);
	outb((port_t)port, (u8)val);
	return val;
}

DEFINE_DEBUG_FUNCTION(
		"outw",
		"outw PORT VAL\n"
		"\tOutput a given VAL to PORT\n",
		argc, argv) {
	uintptr_t port, val;
	if (argc != 3)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	if (!dbg_evaladdr(argv[1], &port) || !dbg_evalexpr(argv[2], &val))
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	dbg_printf(DBGSTR("outw %#.4I16x, %#.4I16x (%I16u)\n"), (u16)port, (u16)val, (u16)val);
	outw((port_t)port, (u16)val);
	return val;
}

DEFINE_DEBUG_FUNCTION(
		"outl",
		"outl PORT VAL\n"
		"\tOutput a given VAL to PORT\n",
		argc, argv) {
	uintptr_t port, val;
	if (argc != 3)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	if (!dbg_evaladdr(argv[1], &port) || !dbg_evalexpr(argv[2], &val))
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	dbg_printf(DBGSTR("outl %#.4I16x, %#.8I32x (%I32u)\n"), (u16)port, (u32)val, (u32)val);
	outl((port_t)port, (u32)val);
	return val;
}


DEFINE_DEBUG_FUNCTION(
		"m",
		"m [-bwlqp] ADDR [COUNT=16|page]\n"
		"\tPrint a hexdump of COUNT bytes of memory, starting at ADDR\n",
		argc, argv) {
	uintptr_t count, addr;
	unsigned int size = 1;
	while (argc > 2 && argv[1][0] == '-') {
		/**/ if (!strcmp(argv[1], DBGSTR("-p")))
			size = sizeof(void *);
		else if (!strcmp(argv[1], DBGSTR("-b")))
			size = 1;
		else if (!strcmp(argv[1], DBGSTR("-w")))
			size = 2;
		else if (!strcmp(argv[1], DBGSTR("-l")))
			size = 4;
		else if (!strcmp(argv[1], DBGSTR("-q")))
			size = 8;
		else
			return DBG_FUNCTION_INVALID_ARGUMENTS;
		--argc;
		++argv;
	}
	if (argc <= 2)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	count = 16;
	if (!dbg_evaladdr(argv[1], &addr))
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	if (argc >= 3) {
		if (!strcmp(argv[2], DBGSTR("page")))
			count = pagedir_pagesize() - (addr & (pagedir_pagesize() - 1));
		else if (!dbg_evalexpr(argv[2], &count)) {
			return DBG_FUNCTION_INVALID_ARGUMENTS;
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

DEFINE_DEBUG_FUNCTION(
		"mp",
		"mp ADDR [COUNT=16|page]\n"
		"\tAlias for " DF_WHITE("m -p ...") "\n",
		argc, argv) {
	uintptr_t count, addr;
	if (argc <= 2)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	count = 16;
	if (!dbg_evaladdr(argv[1], &addr))
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	if (argc >= 3) {
		if (!strcmp(argv[2], DBGSTR("page")))
			count = pagedir_pagesize() - (addr & (pagedir_pagesize() - 1));
		else if (!dbg_evalexpr(argv[2], &count)) {
			return DBG_FUNCTION_INVALID_ARGUMENTS;
		}
	}
	dbg_printf(DBGSTR("%$I[hex]\n"), (size_t)count, (uintptr_t)addr);
	return 0;
}


PRIVATE ATTR_DBGTEXT NOBLOCK bool
NOTHROW(KCALL is_pc)(uintptr_t pc) {
	struct vm_node *node;
	if (pc < KERNEL_BASE)
		return false;
	node = vm_getnodeof(&vm_kernel, VM_ADDR2PAGE((vm_virt_t)pc));
	if (!node)
		return false;
	return (node->vn_prot & VM_PROT_EXEC) != 0;
}

PRIVATE ATTR_DBGTEXT NONNULL((1)) ssize_t __LIBCCALL
debug_da_formater(struct disassembler *__restrict self,
                  unsigned int format_option) {
	char const *string;
	if (DISASSEMBLER_FORMAT_ISSUFFIX(format_option))
		string = DF_RESETATTR;
	else {
		switch (format_option) {
		case DISASSEMBLER_FORMAT_REGISTER_PREFIX: string = DF_SETCOLOR(DBG_COLOR_BLACK, DBG_COLOR_LIGHT_GRAY); break;
		case DISASSEMBLER_FORMAT_IMMEDIATE_PREFIX:
		case DISASSEMBLER_FORMAT_OFFSET_PREFIX:
		case DISASSEMBLER_FORMAT_SCALE_PREFIX: string = DF_SETFGCOLOR(DBG_COLOR_RED); break;
		case DISASSEMBLER_FORMAT_SYMBOL_PREFIX: string = DF_SETWHITE; break;
		case DISASSEMBLER_FORMAT_PSEUDOOP_PREFIX: string = DF_SETFGCOLOR(DBG_COLOR_DARK_GRAY); break;
		case DISASSEMBLER_FORMAT_MNEMONIC_PREFIX: string = DF_SETFGCOLOR(DBG_COLOR_PURPLE); break;
		default: return 0;
		}
	}
	dbg_print(string);
	return 0;
}



DEFINE_DEBUG_FUNCTION(
		"disasm",
		"disasm [PC=registers.PC] [COUNT=<1 instruction>]\n"
		"\tPrint the disassembly of the given address range\n",
		argc, argv) {
	uintptr_t addr, current_pc, count;
	struct disassembler da;
	current_pc = fcpustate_getpc(&dbg_viewstate);
	current_pc = (uintptr_t)instruction_trypred((void const *)current_pc);
	addr = current_pc;
	if (argc >= 2) {
		if (!dbg_evaladdr(argv[1], &addr))
			return DBG_FUNCTION_INVALID_ARGUMENTS;
	}
	disasm_init(&da, &dbg_printer, NULL, (void *)addr,
	            DISASSEMBLER_TARGET_CURRENT,
	            DISASSEMBLER_FNORMAL, 0);
	da.d_format = &debug_da_formater;
	if (argc >= 3) {
		if (sscanf(argv[2], DBGSTR("%lU"), &count) != 1)
			return DBG_FUNCTION_INVALID_ARGUMENTS;
		disasm_print_until(&da, (byte_t *)addr + (size_t)count);
	} else {
		disasm_print_instruction(&da);
		dbg_putc('\n');
	}
	return 0;
}

DEFINE_DEBUG_FUNCTION(
		"instrlen",
		"instrlen [PC=registers.PC]\n"
		"\tPrint the length of the specified instruction\n",
		argc, argv) {
	uintptr_t addr, current_pc, length;
	current_pc = fcpustate_getpc(&dbg_viewstate);
	current_pc = (uintptr_t)instruction_trypred((void const *)current_pc);
	addr = current_pc;
	if (argc >= 2) {
		if (!dbg_evaladdr(argv[1], &addr))
			return DBG_FUNCTION_INVALID_ARGUMENTS;
	}
	length = instruction_length((void *)addr);
	dbg_printf(DBGSTR("%Iu\n"), length);
	return 0;
}

DEFINE_DEBUG_FUNCTION(
		"trace",
		"\tDisplay a traceback for the current source location\n"
		"\tInlined functions are displayed in blue\n"
		"\tPC       IS   Name           Off   File    Line  Info\n"
		"\tC01936B0+5   [dwarf_fde_find+245] [dwarf.c:262] [...]\n"
		"\tPC:   Program counter position\n"
		"\tIS:   Instriction/inline size\n"
		"\tName: Name of the surrounding function\n"
		"\tOff:  Offset of PC from the surrounding function's start\n"
		"\tFile: Last component of the associated source's filename\n"
		"\tLine: Line number within File of the associated source code\n"
		"\tInfo: Additional information\n",
		argc, argv) {
	struct ucpustate state;
	unsigned int error;
#ifdef LOG_STACK_REMAINDER
	uintptr_t last_good_sp;
#endif /* LOG_STACK_REMAINDER */
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	fcpustate_to_ucpustate(&dbg_viewstate, &state);
#ifdef LOG_STACK_REMAINDER
	last_good_sp = ucpustate_getsp(&state);
#endif /* LOG_STACK_REMAINDER */
	dbg_addr2line_printf((uintptr_t)instruction_trypred((void const *)ucpustate_getpc(&state)),
	                     (uintptr_t)ucpustate_getpc(&state),
	                     DBGSTR("sp=%p"), (void *)ucpustate_getsp(&state));
	for (;;) {
		struct ucpustate old_state;
		memcpy(&old_state, &state, sizeof(struct ucpustate));
		error = unwind((void *)(ucpustate_getpc(&old_state) - 1),
		               &unwind_getreg_ucpustate, &old_state,
		               &unwind_setreg_ucpustate, &state);
		if (error != UNWIND_SUCCESS)
			break;
		dbg_addr2line_printf((uintptr_t)instruction_trypred((void const *)ucpustate_getpc(&state)),
		                     (uintptr_t)ucpustate_getpc(&state), DBGSTR("sp=%p"),
		                     (void *)ucpustate_getsp(&state));
#ifdef LOG_STACK_REMAINDER
		last_good_sp = ucpustate_getsp(&state);
#endif /* LOG_STACK_REMAINDER */
	}
	if (error != UNWIND_NO_FRAME)
		dbg_printf(DBGSTR("Unwind failure: %u\n"), error);
#ifdef LOG_STACK_REMAINDER
	{
		void *minaddr, *endaddr;
		get_stack_for(&minaddr, &endaddr, (void *)last_good_sp);
		if (last_good_sp >= (uintptr_t)minaddr &&
		    last_good_sp < (uintptr_t)endaddr) {
			bool is_first = true;
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
			uintptr_t iter;
			iter = FLOOR_ALIGN(last_good_sp, sizeof(void *));
			for (; iter < (uintptr_t)endaddr; iter += sizeof(void *))
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
			uintptr_t iter;
			iter  = CEIL_ALIGN(last_good_sp, sizeof(void *));
			while (iter > (uintptr_t)minaddr)
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
			{
				void *pc;
#ifndef __ARCH_STACK_GROWS_DOWNWARDS
				iter -= sizeof(void *);
#endif /* __ARCH_STACK_GROWS_DOWNWARDS */
				pc = *(void **)iter;
				if (!is_pc((uintptr_t)pc))
					continue;
				if (is_first) {
					dbg_printf(DBGSTR("Analyzing remainder of stack:\n"));
					is_first = false;
				}
				dbg_addr2line_printf((uintptr_t)instruction_trypred(pc),
				                     (uintptr_t)pc, DBGSTR("pc@%p"),
				                     iter);
			}
		}
	}
#endif /* LOG_STACK_REMAINDER */
	return 0;
}

DEFINE_DEBUG_FUNCTION(
		"u",
		"u\n"
		"\tUnwind the current source location to its call-site\n"
		, argc, argv) {
	struct fcpustate newstate;
	unsigned int error;
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	memcpy(&newstate, &dbg_viewstate, sizeof(struct fcpustate));
	error = unwind((void *)fcpustate_getpc(&dbg_viewstate) - 1,
	               &unwind_getreg_fcpustate, &dbg_viewstate,
	               &unwind_setreg_fcpustate, &newstate);
	if (error != UNWIND_SUCCESS) {
		dbg_printf(DBGSTR("Unwind failure: %u\n"), error);
	} else {
		memcpy(&dbg_viewstate, &newstate, sizeof(struct fcpustate));
	}
	dbg_addr2line_printf((uintptr_t)instruction_trypred((void const *)fcpustate_getpc(&dbg_viewstate)),
	                     (uintptr_t)fcpustate_getpc(&dbg_viewstate),
	                     DBGSTR("sp=%p"), (void *)fcpustate_getsp(&dbg_viewstate));
	return 0;
}



DEFINE_DEBUG_FUNCTION(
		"a2l",
		"a2l [ADDR=PC] [ADDR...]\n"
		"\tPrint the source location name for the given ADDR\n",
		argc, argv) {
	uintptr_t addr, current_pc;
again:
	--argc;
	++argv;
	current_pc = fcpustate_getpc(&dbg_viewstate);
	current_pc = (uintptr_t)instruction_trypred((void const *)current_pc);
	addr = current_pc;
	if (argc >= 1) {
		if (!dbg_evaladdr(argv[0], &addr))
			return DBG_FUNCTION_INVALID_ARGUMENTS;
		current_pc = (uintptr_t)instruction_trysucc((void const *)addr);
	}
	dbg_addr2line_printf((uintptr_t)addr, (uintptr_t)current_pc, NULL);
	if (argc > 1)
		goto again;
	return 0;
}

DEFINE_DEBUG_FUNCTION(
		"eval",
		"eval EXPR...\n"
		"\tEvaluate the given expression and print the result\n",
		argc, argv) {
	--argc;
	++argv;
	for (; argc; --argc, ++argv) {
		uintptr_t result;
		char *expr = argv[0];
		if (!dbg_evalexpr(expr, &result))
			return 1;
		dbg_printf("%q: " DF_WHITE("%#Ix") " (" DF_WHITE("%Iu") ")\n",
		           expr, result, result);
	}
	return 0;
}

DEFINE_DEBUG_FUNCTION(
		"rawmagic",
		"rawmagic message\n"
		"\tOutput a given " DF_WHITE("message") " to magic\n",
		argc, argv) {
	if (argc != 2)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	printk(KERN_RAW "%%{%s}", argv[1]);
	return 0;
}


DECL_END
#endif /* !CONFIG_NO_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_IO_C */
