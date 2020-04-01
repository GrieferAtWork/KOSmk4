/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.remove("-O3"))
	gcc_opt.append("-Os");
]]]*/
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_INTRIN_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_INTRIN_C 1
#define DISABLE_BRANCH_PROFILING 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_DEBUGGER
#include <debugger/function.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <kernel/addr2line.h>
#include <kernel/except.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <sys/io.h>

#include <format-printer.h>
#include <stdio.h>
#include <string.h>

#include <libdisasm/disassembler.h>
#include <libinstrlen/instrlen.h>
#include <libregdump/cpu-state.h>
#include <libregdump/x86.h>

DECL_BEGIN


PRIVATE ATTR_DBGTEXT void KCALL
print_cpuid_reg(u32 leaf, char reg_acdb, u32 reg_value) {
	dbg_printf(DBGSTR("cpuid "    DF_SETFGCOLOR(DBG_COLOR_WHITE) "%#.8I32x" DF_DEFFGCOLOR
	                  ": %%e%cx=" DF_SETFGCOLOR(DBG_COLOR_WHITE) "%#.8I32x" DF_DEFFGCOLOR
	                  " (" DF_SETFGCOLOR(DBG_COLOR_YELLOW) "%$q" DF_DEFFGCOLOR ")"
	                  " (" DF_SETFGCOLOR(DBG_COLOR_WHITE) "%I32u" ")" DF_DEFFGCOLOR "\n"),
	           leaf, reg_acdb, reg_value, 4, &reg_value, reg_value);
}

DEFINE_DEBUG_FUNCTION(
		"cpuid",
		"cpuid LEAF [SUBLEAF]\n"
		"\tInvoke the " DF_COLOR(DBG_COLOR_DARK_GRAY, DBG_COLOR_LIGHT_GRAY, "cpuid") " instruction "
		  "for the given LEAF and display its returned values\n"
		, argc, argv) {
	u32 leaf, a, c, d, b;
	if (argc <= 1 || sscanf(argv[1], DBGSTR("%I32U"), &leaf) != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	if (argc >= 3) {
		u32 leaf2;
		if (sscanf(argv[2], DBGSTR("%I32U"), &leaf2) != 1)
			return DBG_FUNCTION_INVALID_ARGUMENTS;
		__cpuid2(leaf, leaf2, &a, &c, &d, &b);
	} else {
		__cpuid(leaf, &a, &c, &d, &b);
	}
	print_cpuid_reg(leaf, 'a', a);
	print_cpuid_reg(leaf, 'c', c);
	print_cpuid_reg(leaf, 'd', d);
	print_cpuid_reg(leaf, 'b', b);
	return 0;
}


#ifdef __x86_64__
#define CFI_UNWIND_REGISTER_PFLAGS CFI_X86_64_UNWIND_REGISTER_RFLAGS
#else /* __x86_64__ */
#define CFI_UNWIND_REGISTER_PFLAGS CFI_386_UNWIND_REGISTER_EFLAGS
#endif /* !__x86_64__ */


DEFINE_DEBUG_FUNCTION_EX(
		"cli", NULL, DBG_FUNCTION_FLAG_AUTOEXCLUSIVE,
		"cli\n"
		"\tSet " DF_COLOR(DBG_COLOR_DARK_GRAY, DBG_COLOR_LIGHT_GRAY, "EFLAGS.IF = 0") "\n"
		, argc, argv) {
	uintptr_t pflags;
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	(void)argv;
	pflags = dbg_getregp(DBG_REGLEVEL_VIEW, CFI_UNWIND_REGISTER_PFLAGS);
	dbg_printf(DBGSTR("cli EFLAGS.IF = 0 (was %u)\n"),
	           pflags & EFLAGS_IF ? 1 : 0);
	pflags &= ~EFLAGS_IF;
	dbg_setregp(DBG_REGLEVEL_VIEW, CFI_UNWIND_REGISTER_PFLAGS, pflags);
	return 0;
}

DEFINE_DEBUG_FUNCTION_EX(
		"sti", NULL, DBG_FUNCTION_FLAG_AUTOEXCLUSIVE,
		"sti\n"
		"\tSet " DF_COLOR(DBG_COLOR_DARK_GRAY, DBG_COLOR_LIGHT_GRAY, "EFLAGS.IF = 1") "\n"
		, argc, argv) {
	uintptr_t pflags;
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	(void)argv;
	pflags = dbg_getregp(DBG_REGLEVEL_VIEW, CFI_UNWIND_REGISTER_PFLAGS);
	dbg_printf(DBGSTR("sti EFLAGS.IF = 1 (was %u)\n"),
	           pflags & EFLAGS_IF ? 1 : 0);
	pflags |= EFLAGS_IF;
	dbg_setregp(DBG_REGLEVEL_VIEW, CFI_UNWIND_REGISTER_PFLAGS, pflags);
	return 0;
}

DEFINE_DEBUG_FUNCTION_EX(
		"cld", NULL, DBG_FUNCTION_FLAG_AUTOEXCLUSIVE,
		"cld\n"
		"\tSet " DF_COLOR(DBG_COLOR_DARK_GRAY, DBG_COLOR_LIGHT_GRAY, "EFLAGS.DF = 0") "\n"
		, argc, argv) {
	uintptr_t pflags;
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	(void)argv;
	pflags = dbg_getregp(DBG_REGLEVEL_VIEW, CFI_UNWIND_REGISTER_PFLAGS);
	dbg_printf(DBGSTR("cld EFLAGS.DF = 0 (was %u)\n"),
	           pflags & EFLAGS_DF ? 1 : 0);
	pflags &= ~EFLAGS_DF;
	dbg_setregp(DBG_REGLEVEL_VIEW, CFI_UNWIND_REGISTER_PFLAGS, pflags);
	return 0;
}

DEFINE_DEBUG_FUNCTION_EX(
		"std", NULL, DBG_FUNCTION_FLAG_AUTOEXCLUSIVE,
		"std\n"
		"\tSet " DF_COLOR(DBG_COLOR_DARK_GRAY, DBG_COLOR_LIGHT_GRAY, "EFLAGS.DF = 1") "\n"
		, argc, argv) {
	uintptr_t pflags;
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	(void)argv;
	pflags = dbg_getregp(DBG_REGLEVEL_VIEW, CFI_UNWIND_REGISTER_PFLAGS);
	dbg_printf(DBGSTR("std EFLAGS.DF = 1 (was %u)\n"),
	           pflags & EFLAGS_DF ? 1 : 0);
	pflags |= EFLAGS_DF;
	dbg_setregp(DBG_REGLEVEL_VIEW, CFI_UNWIND_REGISTER_PFLAGS, pflags);
	return 0;
}

DEFINE_DEBUG_FUNCTION_EX(
		"clc", NULL, DBG_FUNCTION_FLAG_AUTOEXCLUSIVE,
		"clc\n"
		"\tSet " DF_COLOR(DBG_COLOR_DARK_GRAY, DBG_COLOR_LIGHT_GRAY, "EFLAGS.CF = 0") "\n"
		, argc, argv) {
	uintptr_t pflags;
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	(void)argv;
	pflags = dbg_getregp(DBG_REGLEVEL_VIEW, CFI_UNWIND_REGISTER_PFLAGS);
	dbg_printf(DBGSTR("clc EFLAGS.CF = 0 (was %u)\n"),
	           pflags & EFLAGS_CF ? 1 : 0);
	pflags &= ~EFLAGS_CF;
	dbg_setregp(DBG_REGLEVEL_VIEW, CFI_UNWIND_REGISTER_PFLAGS, pflags);
	return 0;
}

DEFINE_DEBUG_FUNCTION_EX(
		"stc", NULL, DBG_FUNCTION_FLAG_AUTOEXCLUSIVE,
		"stc\n"
		"\tSet " DF_COLOR(DBG_COLOR_DARK_GRAY, DBG_COLOR_LIGHT_GRAY, "EFLAGS.CF = 1") "\n"
		, argc, argv) {
	uintptr_t pflags;
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	(void)argv;
	pflags = dbg_getregp(DBG_REGLEVEL_VIEW, CFI_UNWIND_REGISTER_PFLAGS);
	dbg_printf(DBGSTR("stc EFLAGS.CF = 1 (was %u)\n"),
	           pflags & EFLAGS_CF ? 1 : 0);
	pflags |= EFLAGS_CF;
	dbg_setregp(DBG_REGLEVEL_VIEW, CFI_UNWIND_REGISTER_PFLAGS, pflags);
	return 0;
}

DEFINE_DEBUG_FUNCTION_EX(
		"cmc", NULL, DBG_FUNCTION_FLAG_AUTOEXCLUSIVE,
		"cmc\n"
		"\tSet " DF_COLOR(DBG_COLOR_DARK_GRAY, DBG_COLOR_LIGHT_GRAY, "EFLAGS.CF = -EFLAGS.CF") "\n"
		, argc, argv) {
	uintptr_t pflags;
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	(void)argv;
	pflags = dbg_getregp(DBG_REGLEVEL_VIEW, CFI_UNWIND_REGISTER_PFLAGS);
	dbg_printf(DBGSTR("stc EFLAGS.CF = %u (was %u)\n"),
	           pflags & EFLAGS_CF ? 0 : 1,
	           pflags & EFLAGS_CF ? 1 : 0);
	pflags ^= EFLAGS_CF;
	dbg_setregp(DBG_REGLEVEL_VIEW, CFI_UNWIND_REGISTER_PFLAGS, pflags);
	return 0;
}

DEFINE_DEBUG_FUNCTION(
		"lgdt",
		"lgdt LIMIT BASE\n"
		"\tSet a new Global Descriptor Table\n"
		, argc, argv) {
	u16 limit;
	uintptr_t base;
	struct fcpustate fst;
	if (argc != 3 ||
	    sscanf(argv[1], DBGSTR("%I16U"), &limit) != 1 ||
	    sscanf(argv[2], DBGSTR("%Ix"), &base) != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	dbg_printf("lgdt #%.4I16x (%I16u), %p\n", limit, limit, base);
	dbg_getallregs(DBG_REGLEVEL_VIEW, &fst);
	fst.fcs_gdt.dt_limit = limit;
	fst.fcs_gdt.dt_base  = base;
	dbg_setallregs(DBG_REGLEVEL_VIEW, &fst);
	return 0;
}

DEFINE_DEBUG_FUNCTION_EX(
		"sgdt", NULL, DBG_FUNCTION_FLAG_AUTOEXCLUSIVE,
		"sgdt\n"
		"\tPrint the base and limit of the current Global Descriptor Table\n"
		, argc, argv) {
	struct fcpustate fst;
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	(void)argv;
	dbg_getallregs(DBG_REGLEVEL_VIEW, &fst);
	dbg_printf(DBGSTR("sgdt %#.4I16x (%I16u), %p\n"),
	           fst.fcs_gdt.dt_limit,
	           fst.fcs_gdt.dt_limit,
	           fst.fcs_gdt.dt_base);
	return 0;
}

DEFINE_DEBUG_FUNCTION(
		"lidt",
		"lidt LIMIT BASE\n"
		"\tSet a new Interrupt Descriptor Table\n"
		, argc, argv) {
	u16 limit;
	uintptr_t base;
	struct fcpustate fst;
	if (argc != 3 ||
	    sscanf(argv[1], "%I16U", &limit) != 1 ||
	    sscanf(argv[2], "%Ix", &base) != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	dbg_printf(DBGSTR("lidt %#.4I16x (%I16u), %p\n"),
	           limit, limit, base);
	dbg_getallregs(DBG_REGLEVEL_VIEW, &fst);
	fst.fcs_idt.dt_limit = limit;
	fst.fcs_idt.dt_base  = base;
	dbg_setallregs(DBG_REGLEVEL_VIEW, &fst);
	return 0;
}

DEFINE_DEBUG_FUNCTION_EX(
		"sidt", NULL, DBG_FUNCTION_FLAG_AUTOEXCLUSIVE,
		"sidt\n"
		"\tPrint the base and limit of the current Interrupt Descriptor Table\n"
		, argc, argv) {
	struct fcpustate fst;
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	(void)argv;
	dbg_getallregs(DBG_REGLEVEL_VIEW, &fst);
	dbg_printf(DBGSTR("sidt %#.4I16x (%I16u), %p\n"),
	           fst.fcs_idt.dt_limit,
	           fst.fcs_idt.dt_limit,
	           fst.fcs_idt.dt_base);
	return 0;
}

INTERN ssize_t LIBREGDUMP_CC
debug_regdump_print_format(struct regdump_printer *__restrict self,
                           unsigned int format_option) {
#define PRINT(x) (*self->rdp_printer)(self->rdp_printer_arg, DBGSTR(x), COMPILER_STRLEN(x))
	switch (format_option) {

	case REGDUMP_FORMAT_INDENT:
		return PRINT("    ");

	case REGDUMP_FORMAT_REGISTER_PREFIX:
		return PRINT(DF_SETBLUE);

	case REGDUMP_FORMAT_VALUE_PREFIX:
	case REGDUMP_FORMAT_OFFSET_PREFIX:
	case REGDUMP_FORMAT_FLAG_PREFIX:
		return PRINT(DF_SETWHITE);

	case REGDUMP_FORMAT_ERROR_PREFIX:
		return PRINT(DF_SETMAROON);

	case REGDUMP_FORMAT_REGISTER_SUFFIX:
	case REGDUMP_FORMAT_VALUE_SUFFIX:
	case REGDUMP_FORMAT_OFFSET_SUFFIX:
	case REGDUMP_FORMAT_FLAG_SUFFIX:
	case REGDUMP_FORMAT_ERROR_SUFFIX:
		return PRINT(DF_RESETATTR);

	default:
		break;
	}
#undef PRINT
	return 0;
}


DEFINE_DEBUG_FUNCTION_EX(
		"r", NULL, DBG_FUNCTION_FLAG_AUTOEXCLUSIVE,
		"r\n"
		"\tDisplay a dump of the current register state\n"
		, argc, argv) {
	struct regdump_printer re_printer;
	struct fcpustate fst;
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	(void)argv;
	re_printer.rdp_printer     = &dbg_printer;
	re_printer.rdp_printer_arg = NULL;
	re_printer.rdp_format      = &debug_regdump_print_format;
	dbg_getallregs(DBG_REGLEVEL_VIEW, &fst);
	/* Implement a custom register dumping implementation so that we
	 * can include %kernel_gs.base on x86_64 (because the value of that
	 * register should have a constant value and be implied by ) */
#ifdef __x86_64__
	{
		struct sgregs sg;
		u64 kgsbase;
		regdump_gpregs(&re_printer, &fst.fcs_gpregs);
		regdump_ip(&re_printer, fcpustate_getpc(&fst));
		sg.sg_gs = fst.fcs_sgregs.sg_gs16;
		sg.sg_fs = fst.fcs_sgregs.sg_fs16;
		sg.sg_es = fst.fcs_sgregs.sg_es16;
		sg.sg_ds = fst.fcs_sgregs.sg_ds16;
		regdump_sgregs_with_cs_ss_tr_ldt(&re_printer, &sg,
		                                 fst.fcs_sgregs.sg_cs,
		                                 fst.fcs_sgregs.sg_ss,
		                                 fst.fcs_sgregs.sg_tr,
		                                 fst.fcs_sgregs.sg_ldt);
		debug_regdump_print_format(&re_printer, REGDUMP_FORMAT_INDENT);
		regdump_sgbase(&re_printer, &fst.fcs_sgbase);
		dbg_putc('\n');
		debug_regdump_print_format(&re_printer, REGDUMP_FORMAT_INDENT);
		debug_regdump_print_format(&re_printer, REGDUMP_FORMAT_REGISTER_PREFIX);
		/* Special case: Also print the %kernel_gs.base register! */
		if (x86_dbg_getregbyid(DBG_REGLEVEL_VIEW, X86_REGISTER_MISC_KGSBASEQ, &kgsbase, 8) != 8)
			kgsbase = (u64)dbg_current;
		dbg_print(DBGSTR("%kernel_gs.base"));
		debug_regdump_print_format(&re_printer, REGDUMP_FORMAT_REGISTER_SUFFIX);
		dbg_putc(' ');
		debug_regdump_print_format(&re_printer, REGDUMP_FORMAT_VALUE_PREFIX);
		dbg_printf(DBGSTR("%p"), kgsbase);
		debug_regdump_print_format(&re_printer, REGDUMP_FORMAT_VALUE_SUFFIX);
		if (kgsbase != (u64)dbg_current) {
			/* Print an error indicator if %kernel_gs.base is incorrect
			 * NOTE: There should never be a scenario where this register has a different
			 *       value than the current thread. (even though the kernel is entered
			 *       with the user-space %gs.base register value, there is no case where
			 *       interrupts are enabled while %gs.base is still incorrect, so no thread
			 *       should ever be interruptible with an incorrect %gs.base. If this can
			 *       still happen somewhere, then that is a bug that would be indicate by this)
			 *       Note that the debugger determines the calling thread using a different method.
			 *       Namely: CURRENT_LAPIC_ID -> CURRENT_CPU -> c_current */
			dbg_putc(' ');
			debug_regdump_print_format(&re_printer, REGDUMP_FORMAT_ERROR_PREFIX);
			dbg_printf(DBGSTR("BAD: should be %p"), dbg_current);
			debug_regdump_print_format(&re_printer, REGDUMP_FORMAT_ERROR_SUFFIX);
		}
		dbg_putc('\n');
		debug_regdump_print_format(&re_printer, REGDUMP_FORMAT_INDENT);
		regdump_flags(&re_printer, fcpustate_getpflags(&fst));
		dbg_putc('\n');
		regdump_coregs(&re_printer, &fst.fcs_coregs);
		regdump_drregs(&re_printer, &fst.fcs_drregs);
		regdump_gdt(&re_printer, &fst.fcs_gdt);
		regdump_idt(&re_printer, &fst.fcs_idt);
	}
#else /* __x86_64__ */
	regdump_fcpustate(&re_printer, &fst);
#endif /* !__x86_64__ */
	return 0;
}

DEFINE_DEBUG_FUNCTION(
		"rdmsr",
		"rdmsr ID\n"
		"\tRead and display the current value of the msr referred to by ID\n"
		, argc, argv) {
	u32 id; u64 val;
	if (argc != 2 ||
	    sscanf(argv[1], DBGSTR("%I32x"), &id) != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	val = __rdmsr(id);
	dbg_printf(DBGSTR("rdmsr " DF_WHITE("%#.8I32x") " (" DF_WHITE("%I32u") "): "
	                  DF_WHITE("%#.16I64x") " (" DF_WHITE("%I64u") ")\n"),
	           id, id, val, val);
	return 0;
}

DEFINE_DEBUG_FUNCTION(
		"wrmsr",
		"wrmsr ID VAL\n"
		"\tWrite the given VAL into the msr referred to by ID\n"
		, argc, argv) {
	u32 id; u64 val;
	if (argc != 3 ||
	    sscanf(argv[1], DBGSTR("%I32x"), &id) != 1 ||
	    sscanf(argv[2], DBGSTR("%I64U"), &val) != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	dbg_printf(DBGSTR("wrmsr " DF_WHITE("%#.8I32x") " (" DF_WHITE("%I32u") "): "
	                  DF_WHITE("%#.16I64x") " (" DF_WHITE("%I64u") ")\n"),
	           id, id, val, val);
	__wrmsr(id, val);
	return 0;
}



DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_INTRIN_C */
