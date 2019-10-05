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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_INTRIN_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_INTRIN_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <kernel/debugger.h>

#ifndef CONFIG_NO_DEBUGGER
#include <kernel/addr2line.h>
#include <kernel/except.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/kernel/cpu-state.h>
#include <sys/io.h>

#include <libdisasm/disassembler.h>
#include <libinstrlen/instrlen.h>
#include <libregdump/cpu-state.h>
#include <libregdump/x86.h>

#include <format-printer.h>
#include <stdio.h>
#include <string.h>

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
#define fcs_Xflags fcs_rflags
#else
#define fcs_Xflags fcs_eflags
#endif


DEFINE_DEBUG_FUNCTION(
		"cli",
		"cli\n"
		"\tSet " DF_COLOR(DBG_COLOR_DARK_GRAY, DBG_COLOR_LIGHT_GRAY, "EFLAGS.IF = 0") "\n"
		, argc, argv) {
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	dbg_printf(DBGSTR("cli EFLAGS.IF = 0 (was %u)\n"),
	           dbg_viewstate.fcs_Xflags & EFLAGS_IF ? 1 : 0);
	dbg_viewstate.fcs_Xflags &= ~EFLAGS_IF;
	return 0;
}
DEFINE_DEBUG_FUNCTION(
		"sti",
		"sti\n"
		"\tSet " DF_COLOR(DBG_COLOR_DARK_GRAY, DBG_COLOR_LIGHT_GRAY, "EFLAGS.IF = 1") "\n"
		, argc, argv) {
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	dbg_printf(DBGSTR("sti EFLAGS.IF = 1 (was %u)\n"),
	           dbg_viewstate.fcs_Xflags & EFLAGS_IF ? 1 : 0);
	dbg_viewstate.fcs_Xflags |= EFLAGS_IF;
	return 0;
}
DEFINE_DEBUG_FUNCTION(
		"cld",
		"cld\n"
		"\tSet " DF_COLOR(DBG_COLOR_DARK_GRAY, DBG_COLOR_LIGHT_GRAY, "EFLAGS.DF = 0") "\n"
		, argc, argv) {
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	dbg_printf(DBGSTR("cld EFLAGS.DF = 0 (was %u)\n"),
	           dbg_viewstate.fcs_Xflags & EFLAGS_DF ? 1 : 0);
	dbg_viewstate.fcs_Xflags &= ~EFLAGS_DF;
	return 0;
}
DEFINE_DEBUG_FUNCTION(
		"std",
		"std\n"
		"\tSet " DF_COLOR(DBG_COLOR_DARK_GRAY, DBG_COLOR_LIGHT_GRAY, "EFLAGS.DF = 1") "\n"
		, argc, argv) {
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	dbg_printf(DBGSTR("std EFLAGS.DF = 1 (was %u)\n"),
	           dbg_viewstate.fcs_Xflags & EFLAGS_DF ? 1 : 0);
	dbg_viewstate.fcs_Xflags |= EFLAGS_DF;
	return 0;
}
DEFINE_DEBUG_FUNCTION(
		"clc",
		"clc\n"
		"\tSet " DF_COLOR(DBG_COLOR_DARK_GRAY, DBG_COLOR_LIGHT_GRAY, "EFLAGS.CF = 0") "\n"
		, argc, argv) {
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	dbg_printf(DBGSTR("clc EFLAGS.CF = 0 (was %u)\n"),
	           dbg_viewstate.fcs_Xflags & EFLAGS_CF ? 1 : 0);
	dbg_viewstate.fcs_Xflags &= ~EFLAGS_CF;
	return 0;
}
DEFINE_DEBUG_FUNCTION(
		"stc",
		"stc\n"
		"\tSet " DF_COLOR(DBG_COLOR_DARK_GRAY, DBG_COLOR_LIGHT_GRAY, "EFLAGS.CF = 1") "\n"
		, argc, argv) {
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	dbg_printf(DBGSTR("stc EFLAGS.CF = 1 (was %u)\n"),
	           dbg_viewstate.fcs_Xflags & EFLAGS_CF ? 1 : 0);
	dbg_viewstate.fcs_Xflags |= EFLAGS_CF;
	return 0;
}
DEFINE_DEBUG_FUNCTION(
		"cmc",
		"cmc\n"
		"\tSet " DF_COLOR(DBG_COLOR_DARK_GRAY, DBG_COLOR_LIGHT_GRAY, "EFLAGS.CF = -EFLAGS.CF") "\n"
		, argc, argv) {
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	dbg_printf(DBGSTR("stc EFLAGS.CF = %u (was %u)\n"),
	           dbg_viewstate.fcs_Xflags & EFLAGS_CF ? 0 : 1,
	           dbg_viewstate.fcs_Xflags & EFLAGS_CF ? 1 : 0);
	dbg_viewstate.fcs_Xflags ^= EFLAGS_CF;
	return 0;
}

DEFINE_DEBUG_FUNCTION(
		"lgdt",
		"lgdt LIMIT BASE\n"
		"\tSet a new Global Descriptor Table\n"
		, argc, argv) {
	u16 limit;
	uintptr_t base;
	if (argc != 3 ||
	    sscanf(argv[1], DBGSTR("%I16U"), &limit) != 1 ||
	    sscanf(argv[2], DBGSTR("%Ix"), &base) != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	dbg_printf("lgdt #%.4I16x (%I16u), %p\n", limit, limit, base);
	dbg_viewstate.fcs_gdt.dt_limit = limit;
	dbg_viewstate.fcs_gdt.dt_base  = base;
	return 0;
}
DEFINE_DEBUG_FUNCTION(
		"sgdt",
		"sgdt\n"
		"\tPrint the base and limit of the current Global Descriptor Table\n"
		, argc, argv) {
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	dbg_printf(DBGSTR("sgdt %#.4I16x (%I16u), %p\n"),
	           dbg_viewstate.fcs_gdt.dt_limit,
	           dbg_viewstate.fcs_gdt.dt_limit,
	           dbg_viewstate.fcs_gdt.dt_base);
	return 0;
}

DEFINE_DEBUG_FUNCTION(
		"lidt",
		"lidt LIMIT BASE\n"
		"\tSet a new Interrupt Descriptor Table\n"
		, argc, argv) {
	u16 limit;
	uintptr_t base;
	if (argc != 3 ||
	    sscanf(argv[1], "%I16U", &limit) != 1 ||
	    sscanf(argv[2], "%Ix", &base) != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	dbg_printf(DBGSTR("lidt %#.4I16x (%I16u), %p\n"),
	           limit, limit, base);
	dbg_viewstate.fcs_idt.dt_limit = limit;
	dbg_viewstate.fcs_idt.dt_base  = base;
	return 0;
}
DEFINE_DEBUG_FUNCTION(
		"sidt",
		"sidt\n"
		"\tPrint the base and limit of the current Interrupt Descriptor Table\n"
		, argc, argv) {
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	dbg_printf(DBGSTR("sidt %#.4I16x (%I16u), %p\n"),
	           dbg_viewstate.fcs_idt.dt_limit,
	           dbg_viewstate.fcs_idt.dt_limit,
	           dbg_viewstate.fcs_idt.dt_base);
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


DEFINE_DEBUG_FUNCTION(
		"r",
		"r\n"
		"\tDisplay a dump of the current register state\n"
		, argc, argv) {
	struct regdump_printer re_printer;
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	re_printer.rdp_printer     = &dbg_printer;
	re_printer.rdp_printer_arg = NULL;
	re_printer.rdp_format      = &debug_regdump_print_format;
	regdump_fcpustate(&re_printer, &dbg_viewstate);
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
#endif /* !CONFIG_NO_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_INTRIN_C */
