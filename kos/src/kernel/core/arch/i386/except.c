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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_EXCEPT_C
#define GUARD_KERNEL_CORE_ARCH_I386_EXCEPT_C 1
#define _KOS_SOURCE 1

#include "except.h"

#include <kernel/compiler.h>

#include <kernel/addr2line.h>
#include <kernel/debugger.h>
#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <asm/registers.h>

#include <format-printer.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <wait.h>

#include <libdebuginfo/dwarf.h>
#include <libinstrlen/instrlen.h>
#include <libregdump/x86.h>
#include <libunwind/eh_frame.h>
#include <libunwind/unwind.h>
#include <kos/kernel/cpu-state-helpers.h>


/* TODO: This file needs some _major_ cleanup! */
/* TODO: This file should be merged with libc's except.c file, and be
 *       implemented as part of the hybrid-interface (though obviously
 *       there are some major differences between the two) */

DECL_BEGIN

PUBLIC ATTR_PERTASK struct exception_info _this_exception_info;

INTERN char const *NOTHROW(FCALL get_exception_name)(error_code_t code) {
	char const *result;
#undef END
#undef CLASS
#undef SUBCLASS
	switch (code) {
#define SUBCLASS(name, ...) \
	case ERROR_CODE name:   \
		result = #name;     \
		break;
#include <kos/except-codes.def>
#undef SUBCLASS
	default:
		switch (ERROR_CLASS(code)) {
#define CLASS(name, ...) \
	case name:           \
		result = #name;  \
		break;
#include <kos/except-codes.def>
#undef SUBCLASS
		default:
			result = NULL;
			break;
		}
	}
	return result;
}


PRIVATE char const gp32_names[8][4] = {
	/* [X86_REGISTER_GENERAL_PURPOSE_EAX & 7] = */"eax",
	/* [X86_REGISTER_GENERAL_PURPOSE_ECX & 7] = */"ecx",
	/* [X86_REGISTER_GENERAL_PURPOSE_EDX & 7] = */"edx",
	/* [X86_REGISTER_GENERAL_PURPOSE_EBX & 7] = */"ebx",
	/* [X86_REGISTER_GENERAL_PURPOSE_ESP & 7] = */"esp",
	/* [X86_REGISTER_GENERAL_PURPOSE_EBP & 7] = */"ebp",
	/* [X86_REGISTER_GENERAL_PURPOSE_ESI & 7] = */"esi",
	/* [X86_REGISTER_GENERAL_PURPOSE_EDI & 7] = */"edi",
};
PRIVATE char const gp16_names[8][3] = {
	/* [X86_REGISTER_GENERAL_PURPOSE_AX & 7] = */"ax",
	/* [X86_REGISTER_GENERAL_PURPOSE_CX & 7] = */"cx",
	/* [X86_REGISTER_GENERAL_PURPOSE_DX & 7] = */"dx",
	/* [X86_REGISTER_GENERAL_PURPOSE_BX & 7] = */"bx",
	/* [X86_REGISTER_GENERAL_PURPOSE_SP & 7] = */"sp",
	/* [X86_REGISTER_GENERAL_PURPOSE_BP & 7] = */"bp",
	/* [X86_REGISTER_GENERAL_PURPOSE_SI & 7] = */"si",
	/* [X86_REGISTER_GENERAL_PURPOSE_DI & 7] = */"di",
};
PRIVATE char const gp8_names[8][3] = {
	/* [X86_REGISTER_GENERAL_PURPOSE_AL & 7] = */"al",
	/* [X86_REGISTER_GENERAL_PURPOSE_CL & 7] = */"cl",
	/* [X86_REGISTER_GENERAL_PURPOSE_DL & 7] = */"dl",
	/* [X86_REGISTER_GENERAL_PURPOSE_BL & 7] = */"bl",
	/* [X86_REGISTER_GENERAL_PURPOSE_AH & 7] = */"ah",
	/* [X86_REGISTER_GENERAL_PURPOSE_CH & 7] = */"ch",
	/* [X86_REGISTER_GENERAL_PURPOSE_DH & 7] = */"dh",
	/* [X86_REGISTER_GENERAL_PURPOSE_BH & 7] = */"bh",
};

PRIVATE char const seg_names[6][3] = {
	/* [X86_REGISTER_SEGMENT_ES & 7] = */"es",
	/* [X86_REGISTER_SEGMENT_CS & 7] = */"cs",
	/* [X86_REGISTER_SEGMENT_SS & 7] = */"ss",
	/* [X86_REGISTER_SEGMENT_DS & 7] = */"ds",
	/* [X86_REGISTER_SEGMENT_FS & 7] = */"fs",
	/* [X86_REGISTER_SEGMENT_GS & 7] = */"gs",
};
PRIVATE char const cr_names[5][4] = {
	"cr0",
	"",
	"cr2",
	"cr3",
	"cr4",
};
PRIVATE char const xmm_names[8][5] = {
	/* [X86_REGISTER_XMM_XMM0 & 7] = */"xmm0",
	/* [X86_REGISTER_XMM_XMM1 & 7] = */"xmm1",
	/* [X86_REGISTER_XMM_XMM2 & 7] = */"xmm2",
	/* [X86_REGISTER_XMM_XMM3 & 7] = */"xmm3",
	/* [X86_REGISTER_XMM_XMM4 & 7] = */"xmm4",
	/* [X86_REGISTER_XMM_XMM5 & 7] = */"xmm5",
	/* [X86_REGISTER_XMM_XMM6 & 7] = */"xmm6",
	/* [X86_REGISTER_XMM_XMM7 & 7] = */"xmm7",
};
PRIVATE char const st_names[8][6] = {
	/* [X86_REGISTER_FLOAT_ST0 & 7] = */"st(0)",
	/* [X86_REGISTER_FLOAT_ST1 & 7] = */"st(1)",
	/* [X86_REGISTER_FLOAT_ST2 & 7] = */"st(2)",
	/* [X86_REGISTER_FLOAT_ST3 & 7] = */"st(3)",
	/* [X86_REGISTER_FLOAT_ST4 & 7] = */"st(4)",
	/* [X86_REGISTER_FLOAT_ST5 & 7] = */"st(5)",
	/* [X86_REGISTER_FLOAT_ST6 & 7] = */"st(6)",
	/* [X86_REGISTER_FLOAT_ST7 & 7] = */"st(7)",
};
PRIVATE char const dr_names[8][4] = {
	/* [X86_REGISTER_DEBUG_DR0 & 7] = */"dr0",
	/* [X86_REGISTER_DEBUG_DR1 & 7] = */"dr1",
	/* [X86_REGISTER_DEBUG_DR2 & 7] = */"dr2",
	/* [X86_REGISTER_DEBUG_DR3 & 7] = */"dr3",
	/* [X86_REGISTER_DEBUG_DR4 & 7] = */"dr4",
	/* [X86_REGISTER_DEBUG_DR5 & 7] = */"dr5",
	/* [X86_REGISTER_DEBUG_DR6 & 7] = */"dr6",
	/* [X86_REGISTER_DEBUG_DR7 & 7] = */"dr7",
};


PRIVATE char const *FCALL
register_name(uintptr_t id) {
	char const *result = NULL;
	switch (id & X86_REGISTER_CLASSMASK) {

	case X86_REGISTER_GENERAL_PURPOSE:
		switch (id & X86_REGISTER_SIZEMASK) {
		case X86_REGISTER_GENERAL_PURPOSE_EAX &X86_REGISTER_SIZEMASK:
			result = gp32_names[id & 7];
			break;
		case X86_REGISTER_GENERAL_PURPOSE_AX &X86_REGISTER_SIZEMASK:
			result = gp16_names[id & 7];
			break;
		case X86_REGISTER_GENERAL_PURPOSE_AL &X86_REGISTER_SIZEMASK:
			result = gp8_names[id & 7];
			break;
		default: break;
		}
		break;

	case X86_REGISTER_SEGMENT:
		if ((id & 7) < COMPILER_LENOF(seg_names))
			result = seg_names[id & 7];
		break;

	case X86_REGISTER_CONTROL:
		if ((id & 7) < COMPILER_LENOF(cr_names)) {
			result = cr_names[id & 7];
			if (!*result)
				result = NULL;
		}
		break;

	case X86_REGISTER_MMX:
		result = xmm_names[id & 7] + 1;
		break;

	case X86_REGISTER_XMM:
		result = xmm_names[id & 7];
		break;

	case X86_REGISTER_FLOAT:
		result = st_names[id & 7];
		break;

	case X86_REGISTER_DEBUG:
		result = dr_names[id & 7];
		break;

	case X86_REGISTER_MISC:
		switch (id) {
#ifdef X86_REGISTER_MISC_RFLAGS
		case X86_REGISTER_MISC_RFLAGS:
			result = "rflags";
			break;
#endif /* X86_REGISTER_MISC_RFLAGS */
		case X86_REGISTER_MISC_EFLAGS:
			result = "eflags";
			break;
		case X86_REGISTER_MISC_FLAGS:
			result = "flags";
			break;
		case X86_REGISTER_MISC_TR:
			result = "tr";
			break;
		case X86_REGISTER_MISC_LDT:
			result = "ldt";
			break;
		case X86_REGISTER_MISC_GDT:
			result = "gdt";
			break;
		case X86_REGISTER_MISC_IDT:
			result = "idt";
			break;
		default: break;
		}
		break;

	default: break;
	}
	return result;
}


PRIVATE void
NOTHROW(KCALL print_opcode)(pformatprinter printer, void *arg, uintptr_t opcode) {
	uintptr_t opno = E_ILLEGAL_INSTRUCTION_X86_OPCODE_GETOPC(opcode);
	if (opno <= 0xff) {
		format_printf(printer, arg, " [opcode=%#.2Ix", opno);
	} else if (opno <= 0xffff) {
		format_printf(printer, arg, " [opcode=%#.4Ix", opno);
	} else {
		format_printf(printer, arg, " [opcode=%#Ix", opno);
	}
	if (E_ILLEGAL_INSTRUCTION_X86_OPCODE_HASREG(opcode))
		format_printf(printer, arg, "/%u",
		              (unsigned int)E_ILLEGAL_INSTRUCTION_X86_OPCODE_GETREG(opcode));
	(*printer)(arg, "]", 1);
}

INTERN void
NOTHROW(KCALL print_exception_desc_of)(struct exception_data const *__restrict data,
                                       pformatprinter printer, void *arg) {
	switch (data->e_class) {

	case E_SEGFAULT:
		format_printf(printer, arg, " [cr2=%p] [%c%c%c%c]",
		              data->e_pointers[0],
		              data->e_pointers[1] & E_SEGFAULT_CONTEXT_FAULT ? 'f' : '-',
		              data->e_pointers[1] & E_SEGFAULT_CONTEXT_WRITING ? 'w' : '-',
		              data->e_pointers[1] & E_SEGFAULT_CONTEXT_USERCODE ? 'u' : '-',
		              data->e_pointers[1] & E_SEGFAULT_CONTEXT_NONCANON ? 'c' : '-');
		break;

	case E_ILLEGAL_INSTRUCTION:
		print_opcode(printer, arg, data->e_pointers[0]);
		switch (data->e_subclass) {

		case E_ILLEGAL_INSTRUCTION_X86_INTERRUPT:
			format_printf(printer, arg, " [int=%#.2Ix:%#Ix] [seg=%#Ix]",
			              data->e_pointers[1],
			              data->e_pointers[2],
			              data->e_pointers[3]);
			break;

		case E_ILLEGAL_INSTRUCTION_BAD_OPERAND: {
			char const *what_name;
			switch (data->e_pointers[1]) {
			case E_ILLEGAL_INSTRUCTION_BAD_OPERAND_ADDRMODE:
				what_name = "addrmode";
				break;
			default: what_name = NULL; break;
			}
			if (what_name) {
				format_printf(printer, arg, " [what=%s]", what_name);
			} else {
				format_printf(printer, arg, " [what=?(%#Ix)]",
				              data->e_pointers[1]);
			}
		}
		break;

		case E_ILLEGAL_INSTRUCTION_REGISTER: {
			char const *name;
			switch (data->e_pointers[1]) {
			case E_ILLEGAL_INSTRUCTION_REGISTER_RDINV: name = "rdinv"; break; /* Read from invalid register */
			case E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV: name = "rdprv"; break; /* Read from privileged register */
			case E_ILLEGAL_INSTRUCTION_REGISTER_WRINV: name = "wrinv"; break; /* Write to invalid register */
			case E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV: name = "wrprv"; break; /* Write to privileged register */
			case E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD: name = "wrbad"; break; /* Bad value written to register */
			default: name = NULL;
			}
			if (name) {
				format_printf(printer, arg, " [%s:", name);
			} else {
				format_printf(printer, arg, " [?(%#Ix):", data->e_pointers[1]);
			}
			if (data->e_pointers[2] == X86_REGISTER_MSR) {
				format_printf(printer, arg, "%%msr(%#Ix),%#I64x]",
				              data->e_pointers[3],
				              (uint64_t)data->e_pointers[4] |
				              (uint64_t)data->e_pointers[5] << 32);
			} else {
				name = register_name(data->e_pointers[2]);
				if (name)
					format_printf(printer, arg, "%%%s,", name);
				else
					format_printf(printer, arg, "?(%#x),", data->e_pointers[2]);
				format_printf(printer, arg, "%#Ix]", data->e_pointers[3]);
			}
		}	break;

		case E_ILLEGAL_INSTRUCTION_VIO_UNRECOGNIZED:
			format_printf(printer, arg, " [addr=%p]", data->e_pointers[1]);
			break;
		case E_ILLEGAL_INSTRUCTION_VIO_NONATOMIC_OPERAND:
			format_printf(printer, arg, " [addr=%p+%Iu]",
			              data->e_pointers[1],
			              data->e_pointers[2]);
			break;
		case E_ILLEGAL_INSTRUCTION_VIO_INVALID_KERNEL_SP:
			format_printf(printer, arg, " [%%esp=%p]",
			              data->e_pointers[1]);
			break;

		default: break;
		}
		break;

	case E_INVALID_ALIGNMENT:
		switch (data->e_subclass) {
		case E_INVALID_ALIGNMENT_POINTER:
			format_printf(printer, arg, " [ptr=%p,%p]",
			              data->e_pointers[0],
			              data->e_pointers[1]);
			break;
		default: break;
		}
		break;
	}
}

PRIVATE void
NOTHROW(KCALL print_exception_desc)(pformatprinter printer, void *arg) {
	print_exception_desc_of(&PERTASK(_this_exception_info).ei_data, printer, arg);
}

INTDEF ssize_t LIBREGDUMP_CC
indent_regdump_print_format(struct regdump_printer *__restrict self,
                            unsigned int format_option);


PRIVATE void
NOTHROW(KCALL print_unhandled_exception)(pformatprinter printer, void *arg,
                                         pformatprinter tb_printer, void *tb_arg,
                                         char const *reason, va_list args) {
	unsigned int i;
	bool is_first_pointer;
	char const *name;
	struct exception_info *info = &PERTASK(_this_exception_info);
	struct regdump_printer rd_printer;

	/* Dump the exception that occurred. */
	format_printf(printer, arg, "Unhandled exception %.4I16X:%.4I16X",
	              info->ei_class, info->ei_subclass);
	name = get_exception_name(info->ei_code);
	if (name)
		format_printf(printer, arg, " [%s]", name);
	print_exception_desc(printer, arg);
	if (reason) {
		(*printer)(arg, "\nThrown when: ", COMPILER_STRLEN("\nThrown when: "));
		format_vprintf(printer, arg, reason, args);
	}
	(*printer)(arg, "\nRegister state:\n", COMPILER_STRLEN("\nRegister state:\n"));
	rd_printer.rdp_printer     = printer;
	rd_printer.rdp_printer_arg = arg;
	rd_printer.rdp_format      = &indent_regdump_print_format;
	regdump_gpregs(&rd_printer, &info->ei_state.kcs_gpregs);
	regdump_ip(&rd_printer, kcpustate_getpc(&info->ei_state));
	regdump_flags(&rd_printer, kcpustate_getpflags(&info->ei_state));
	(*printer)(arg, "\n", 1);
	is_first_pointer = true;
	/* Print exception pointers. */
	for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i) {
		if (info->ei_data.e_pointers[i] == 0)
			continue;
		if (is_first_pointer) {
			(*printer)(arg, "Exception pointers:\n", COMPILER_STRLEN("Exception pointers:\n"));
			is_first_pointer = false;
		}
		format_printf(printer, arg, "    [%u] = %p (%Iu)\n", i,
		              info->ei_data.e_pointers[i],
		              info->ei_data.e_pointers[i]);
	}
	addr2line_printf(tb_printer, tb_arg,
	                 (uintptr_t)instruction_trypred((void const *)kcpustate_getpc(&info->ei_state)),
	                 kcpustate_getpc(&info->ei_state), "Thrown here");
#if EXCEPT_BACKTRACE_SIZE != 0
	for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i) {
		if (!info->ei_trace[i])
			break;
		addr2line_printf(tb_printer, tb_arg,
		                 (uintptr_t)instruction_trypred(info->ei_trace[i]),
		                 (uintptr_t)info->ei_trace[i], "Called here");
	}
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
}


/* Print information about the current exception into `printer' */
PUBLIC ssize_t
NOTHROW(KCALL error_print_into)(pformatprinter printer, void *arg) {
	va_list empty_args;
	memset((void *)&empty_args, 0, sizeof(empty_args));
	print_unhandled_exception(printer, arg, printer, arg, NULL, empty_args);
	/* TODO: Track `printer' return values. */
	return 0;
}

PUBLIC void
NOTHROW(KCALL error_vprintf)(char const *__restrict reason, va_list args) {
	char *level = (char *)reason;
	if (!level || level[0] != '\001' || !level[0])
		level = (char *)KERN_EMERG;
	print_unhandled_exception(&kprinter, level,
	                          &kprinter, (void *)KERN_RAW,
	                          reason, args);
}
PUBLIC void
NOTHROW(VCALL error_printf)(char const *__restrict reason, ...) {
	va_list args;
	va_start(args, reason);
	error_vprintf(reason, args);
	va_end(args);
}

#ifndef CONFIG_NO_DEBUGGER
struct panic_args {
	unsigned int           error;
	uintptr_t              last_pc;
	struct exception_info *info;
};

PRIVATE void KCALL
panic_uhe_dbg_main(void *arg) {
	struct panic_args *args;
	unsigned int i;
	bool is_first_pointer;
	char const *name;
	struct exception_info *info;
	args = (struct panic_args *)arg;
	info = args->info;
	dbg_printf(DF_COLOR(DBG_COLOR_WHITE, DBG_COLOR_MAROON, "Unhandled exception") " "
	           DF_WHITE("%.4I16X") " " DF_WHITE("%.4I16X"),
	           info->ei_class, info->ei_subclass);

	/* Dump the exception that occurred. */
	name = get_exception_name(info->ei_code);
	if (name)
		dbg_printf(" [" DF_WHITE("%s") "]", name);
	print_exception_desc(&dbg_printer, NULL);
	dbg_putc('\n');
	is_first_pointer = true;
	/* Print exception pointers. */
	for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i) {
		if (info->ei_data.e_pointers[i] == 0)
			continue;
		if (is_first_pointer) {
			dbg_print("Exception pointers:\n");
			is_first_pointer = false;
		}
		dbg_printf("    [" DF_WHITE("%u") "] = " DF_WHITE("%p") " (" DF_WHITE("%Iu") ")\n",
		           i,
		           info->ei_data.e_pointers[i],
		           info->ei_data.e_pointers[i]);
	}
	dbg_addr2line_printf((uintptr_t)instruction_trypred((void const *)kcpustate_getpc(&info->ei_state)),
	                     kcpustate_getpc(&info->ei_state), "Thrown here");
#if EXCEPT_BACKTRACE_SIZE != 0
	for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i) {
		if (!info->ei_trace[i])
			break;
		dbg_addr2line_printf((uintptr_t)instruction_trypred(info->ei_trace[i]),
		                     (uintptr_t)info->ei_trace[i], "Called here");
	}
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
#if EXCEPT_BACKTRACE_SIZE != 0
	{
		struct exception_info *info = &PERTASK(_this_exception_info);
		uintptr_t prev_last_pc;
		unsigned int i;
		uintptr_t my_last_pc = args->last_pc;
		for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i)
			if (!info->ei_trace[i])
				break;
		prev_last_pc = i ? (uintptr_t)info->ei_trace[i - 1] : kcpustate_getpc(&info->ei_state);
		if (!my_last_pc)
			my_last_pc = prev_last_pc;
		else if (my_last_pc != prev_last_pc) {
			dbg_print("...\n");
			addr2line_printf(&kprinter, (void *)KERN_RAW,
			                 (uintptr_t)instruction_trypred((void const *)my_last_pc),
			                 my_last_pc, "Traceback ends here");
		}
	}
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	if (args->error == UNWIND_SUCCESS) {
		dbg_printf("Unwinding stopped when " DF_FGCOLOR(DBG_COLOR_PURPLE, "NOTHROW")
		           "() function " "%[vinfo:" DF_WHITE("%n") "] was reached\n",
		           instruction_trypred((void const *)args->last_pc));
	} else if (args->error != UNWIND_NO_FRAME) {
		dbg_printf(DF_COLOR(DBG_COLOR_WHITE, DBG_COLOR_MAROON, "Unwinding failed")
		           ": " DF_WHITE("%u") "\n", args->error);
	}
	dbg_main(0);
}

#endif /* !CONFIG_NO_DEBUGGER */


INTDEF void KCALL
kernel_halt_dump_traceback(pformatprinter printer, void *arg,
                           struct ucpustate *__restrict state);

INTERN void FCALL
halt_unhandled_exception(unsigned int unwind_error,
                         struct kcpustate *__restrict unwind_state) {
	struct exception_info *info;
	uintptr_t last_pc = kcpustate_getpc(unwind_state);
	printk(KERN_RAW "\n\n\n");
	print_unhandled_exception(&kprinter, (void *)KERN_EMERG,
	                          &kprinter, (void *)KERN_RAW,
	                          NULL, NULL);
	info = &PERTASK(_this_exception_info);
#if EXCEPT_BACKTRACE_SIZE != 0
	{
		uintptr_t prev_last_pc;
		unsigned int i;
		uintptr_t my_last_pc = last_pc;
		for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i) {
			if (!info->ei_trace[i])
				break;
		}
		prev_last_pc = i < EXCEPT_BACKTRACE_SIZE
		               ? (uintptr_t)info->ei_trace[i - 1]
		               : kcpustate_getpc(&info->ei_state);
		if (!my_last_pc)
			my_last_pc = prev_last_pc;
		else if (my_last_pc != prev_last_pc) {
			printk(KERN_RAW "...\n");
			addr2line_printf(&kprinter, (void *)KERN_RAW,
			                 (uintptr_t)instruction_trypred((void const *)my_last_pc),
			                 my_last_pc, "Traceback ends here");
		}
	}
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	if (unwind_error == UNWIND_SUCCESS) {
		printk(KERN_EMERG
		       "Unwinding stopped when NOTHROW() function "
		       "`%[vinfo:%n:%p]:%p' was reached (see last traceback entry)\n",
		       instruction_trypred((void const *)last_pc), last_pc);
	} else if (unwind_error != UNWIND_NO_FRAME) {
		printk(KERN_EMERG "Unwinding failed: %u\n", unwind_error);
	}
	{
		struct ucpustate ustate;
		/* Dump the remainder of the stack after the caller stopped unwinding. */
		kcpustate_to_ucpustate(unwind_state, &ustate);
		kernel_halt_dump_traceback(&kprinter, (void *)KERN_RAW, &ustate);
	}
#ifndef CONFIG_NO_DEBUGGER
	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_enabled() &&
		(kernel_debugtrap_on & KERNEL_DEBUGTRAP_ON_UNHANDLED_EXCEPT)) {
		uintptr_t trapno = SIGBUS;
		if (info->ei_class == E_SEGFAULT) {
			trapno = SIGSEGV;
		} else if (info->ei_class == E_ILLEGAL_INSTRUCTION) {
			trapno = SIGILL;
		} else if (info->ei_class == E_DIVIDE_BY_ZERO) {
			trapno = SIGFPE;
		} else if (info->ei_class == E_BREAKPOINT) {
			trapno = SIGTRAP;
		}
		kernel_debugtrap(&info->ei_state, trapno);
	}
	{
		struct panic_args args;
		/* Enter the debugger */
		args.error   = unwind_error;
		args.last_pc = last_pc;
		args.info    = info;
		dbg_enter(unwind_state, &panic_uhe_dbg_main, &args);
	}
#else /* !CONFIG_NO_DEBUGGER */
	kernel_panic(unwind_state, "Unhandled exception\n");
#endif /* CONFIG_NO_DEBUGGER */
}


DEFINE_PUBLIC_ALIAS(error_unwind, libc_error_unwind);
INTERN struct kcpustate *
NOTHROW(FCALL libc_error_unwind)(struct kcpustate *__restrict state) {
	unsigned int error;
	unwind_fde_t fde;
	unwind_cfa_state_t cfa;
	struct kcpustate old_state;
	void *pc;
	DEFINE_INTERN_SYMBOL(_this_exception_code, &_this_exception_info.ei_code, sizeof(_this_exception_info.ei_code));
	DEFINE_INTERN_SYMBOL(_this_exception_state, &_this_exception_info.ei_state, sizeof(_this_exception_info.ei_state));
	DEFINE_INTERN_SYMBOL(_this_exception_pointers, &_this_exception_info.ei_data.e_pointers, sizeof(_this_exception_info.ei_data.e_pointers));
	DEFINE_INTERN_SYMBOL(_this_exception_flags, &_this_exception_info.ei_flags, sizeof(_this_exception_info.ei_flags));
#if EXCEPT_BACKTRACE_SIZE != 0
	DEFINE_INTERN_SYMBOL(_this_exception_trace, &_this_exception_info.ei_trace[0], sizeof(_this_exception_info.ei_trace));
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */

search_fde:
	/* unwind `state' until the nearest exception handler, or until user-space is reached.
	 * If the later happens, then we must propagate the exception to it instead.
	 * NOTE: -1 because the state we're being given has its PC pointer
	 *       set to be directed after the faulting instruction. */
	memcpy(&old_state, state, sizeof(old_state));
	pc = (void *)(kcpustate_getpc(&old_state) - 1);
	error = unwind_fde_find(pc, &fde);
	if unlikely(error != UNWIND_SUCCESS)
		goto err;
	/* Check if there is a personality function for us to execute. */
	if (fde.f_persofun) {
		unsigned int perso_code;
		perso_code = (*(dwarf_perso_t)fde.f_persofun)(&fde, state,
		                                              (void *)fde.f_lsdaaddr);
		switch (perso_code) {
		case DWARF_PERSO_EXECUTE_HANDLER:
			/* When unwinding a landing pad, we must check if there is an active
			 * `DW_CFA_GNU_args_size' instruction.
			 * If there is, we must add its value to ESP before resuming execution!
			 * s.a.: https://reviews.llvm.org/D38680 */
			{
				uintptr_t adjustment;
				error = unwind_fde_exec_landing_pad_adjustment(&fde, &adjustment, pc);
				if likely(error == UNWIND_SUCCESS) {
					kcpustate_setsp(state, kcpustate_getsp(state) + adjustment);
				} else if unlikely(error != UNWIND_NO_FRAME) {
					goto err;
				}
			}
			ATTR_FALLTHROUGH
		case DWARF_PERSO_EXECUTE_HANDLER_NOW:
			return state; /* Execute a new handler. */
		case DWARF_PERSO_ABORT_SEARCH:
			halt_unhandled_exception(UNWIND_SUCCESS, state);
			return state;
		default: break;
		}
	}
	error = unwind_fde_exec(&fde, &cfa, pc);
	if unlikely(error != UNWIND_SUCCESS)
		goto err;
	error = unwind_cfa_apply(&cfa, &fde, pc,
	                         &unwind_getreg_kcpustate, &old_state,
	                         &unwind_setreg_kcpustate, state);

	/* When unwinding to user-space, well get an error `UNWIND_INVALID_REGISTER',
	 * when trying to assign a user-space value to the CS register. */
	if (error == UNWIND_INVALID_REGISTER) {
		struct ucpustate ustate;
		unwind_cfa_sigframe_state_t sigframe_cfa;
		kcpustate_to_ucpustate(&old_state, &ustate);
		/* Assume that we're unwinding a signal frame when returning to user-space. */
		error = unwind_fde_sigframe_exec(&fde, &sigframe_cfa, pc);
		if unlikely(error != UNWIND_SUCCESS)
			goto err_old_state;
		error = unwind_cfa_sigframe_apply(&sigframe_cfa, &fde, pc,
		                                  &unwind_getreg_kcpustate, &old_state,
		                                  &unwind_setreg_ucpustate, &ustate);
		if unlikely(error != UNWIND_SUCCESS)
			goto err_old_state;
		if (ucpustate_isuser(&ustate)) {
			/* At this point, we've got an exception that should be unwound
			 * into user-space, with the user-space context at the unwind
			 * location within user-space.
			 * Now we must use that state to build a full `struct icpustate',
			 * then pass that state to `x86_propagate_userspace_exception' */
			x86_handle_except_before_userspace(&ustate,
			                                   TASK_RPC_REASON_ASYNCUSER);
		}
		{
			u16 expected_gs = __rdgs();
			u16 expected_fs = __rdfs();
			u16 expected_es = __rdes();
			u16 expected_ds = __rdds();
			if unlikely(ustate.ucs_cs != SEGMENT_KERNEL_CODE ||
			            ustate.ucs_ss != SEGMENT_KERNEL_DATA ||
			            ustate.ucs_sgregs.sg_gs != expected_gs ||
			            ustate.ucs_sgregs.sg_fs != expected_fs ||
			            ustate.ucs_sgregs.sg_es != expected_es ||
			            ustate.ucs_sgregs.sg_ds != expected_ds) {
#define LOG_SEGNENT_INCONSISTENCY(name, isval, wantval)                                               \
				do {                                                                                  \
					if (isval != wantval) {                                                           \
						printk(KERN_WARNING "[except] Inconsistent unwind %%%cs: %#I16x != %#I16x\n", \
						       name, isval, wantval);                                                 \
					}                                                                                 \
				} __WHILE0
				/* NOTE: Some x86 processors behave kind-of weird:
				 * [warn  ] [except] Inconsistent unwind %cs: 0x80000008 != 0x8
				 * [warn  ] [except] Inconsistent unwind %fs: 0xeafe0040 != 0x40
				 * [warn  ] [except] Inconsistent unwind %es: 0x10000023 != 0x23
				 * -> Testing indicates that bochs implements (and is allowed to implement) `pushl %ds' as:
				 * >> ESP -= 4;
				 * >> *(u16 *)ESP = DS;
				 * In other words, it leaves the upper 2 bytes of the pushed DWORD
				 * undefined (or rather: have them keep their previous values)
				 * -> To fix this, we libunwind (and also some other components
				 *    that use segment registers) have been adjusted, in order
				 *    to either ignore the upper 2 bytes during reads, and fill
				 *    them as all zeroes during writes.
				 * Intel manuals:
				 * ... if the operand size is 32-bits, either a zero-extended value is
				 * pushed on the stack or the segment selector is written on the stack
				 * using a 16-bit move. For the last case, all recent Core and Atom
				 * processors perform a 16-bit move, leaving the upper portion of the
				 * stack location unmodified. ...
				 * -> In other words: Bochs is entirely correct in its emulation, and
				 *    I'm a fault here, in which case. Honestly: Thank you Bochs. That's
				 *    one less Problem for me to figure out the hard way once testing
				 *    on real Hardware is going to start...
				 */
				LOG_SEGNENT_INCONSISTENCY('c', ustate.ucs_cs, SEGMENT_KERNEL_CODE);
				LOG_SEGNENT_INCONSISTENCY('s', ustate.ucs_ss, SEGMENT_KERNEL_DATA);
				LOG_SEGNENT_INCONSISTENCY('g', ustate.ucs_sgregs.sg_gs, expected_gs);
				LOG_SEGNENT_INCONSISTENCY('f', ustate.ucs_sgregs.sg_fs, expected_fs);
				LOG_SEGNENT_INCONSISTENCY('e', ustate.ucs_sgregs.sg_es, expected_es);
				LOG_SEGNENT_INCONSISTENCY('d', ustate.ucs_sgregs.sg_ds, expected_ds);
#undef LOG_SEGNENT_INCONSISTENCY
				error = UNWIND_INVALID_REGISTER;
				goto err_old_state;
			}
		}
		ucpustate_to_kcpustate(&ustate, state);
	} else {
		if unlikely(error != UNWIND_SUCCESS)
			goto err_old_state;
	}

#if EXCEPT_BACKTRACE_SIZE != 0
	/* Remember the current state PC as a new entry in the exception's traceback. */
	if (PERTASK_GET(_this_exception_info.ei_trace[EXCEPT_BACKTRACE_SIZE - 1]) == NULL) {
#if EXCEPT_BACKTRACE_SIZE > 1
		unsigned int i;
		for (i = 0; i < EXCEPT_BACKTRACE_SIZE - 1; ++i) {
			if (!PERTASK_GET(_this_exception_info.ei_trace[i]))
				break;
		}
		PERTASK_SET(_this_exception_info.ei_trace[i], (void *)kcpustate_getpc(state));
#else /* EXCEPT_BACKTRACE_SIZE > 1 */
		PERTASK_SET(_this_exception_info.ei_trace[0], (void *)kcpustate_getpc(state));
#endif /* EXCEPT_BACKTRACE_SIZE <= 1 */
	}
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */

	/* Continue searching for handlers. */
	goto search_fde;
err_old_state:
	memcpy(state, &old_state, sizeof(*state));
err:
	halt_unhandled_exception(error, state);
	return state;
}






PUBLIC unsigned int
NOTHROW(KCALL __gxx_personality_v0)(struct unwind_fde_struct *__restrict fde,
                                    struct kcpustate *__restrict state,
                                    byte_t *__restrict reader) {
	u8 temp, callsite_encoding;
	uintptr_t landingpad;
	uint8_t *callsite_end;
	size_t callsite_size;

	/* This function is hooked by CFI under `struct unwind_fde_struct::f_encperso'
	 * It's exact prototype and behavior are therefor not mandated by how GCC uses it. */
	landingpad = (uintptr_t)fde->f_pcstart;

	/* NOTE: `reader' points to a `struct gcc_lsda' */
	temp = *reader++; /* gl_landing_enc */
	if (temp != DW_EH_PE_omit) {
		landingpad = dwarf_decode_pointer((byte_t **)&reader, temp, sizeof(void *), 0, 0, (uintptr_t)fde->f_pcstart); /* gl_landing_pad */
	}
	temp = *reader++; /* gl_typetab_enc */
	if (temp != DW_EH_PE_omit) {
		dwarf_decode_uleb128((byte_t **)&reader); /* gl_typetab_off */
	}
	callsite_encoding = *reader++; /* gl_callsite_enc */
	callsite_size     = dwarf_decode_uleb128((byte_t **)&reader);
	callsite_end      = reader + callsite_size;
	while (reader < callsite_end) {
		uintptr_t start, size, handler, action;
		start   = dwarf_decode_pointer((byte_t **)&reader, callsite_encoding, sizeof(void *), 0, 0, (uintptr_t)fde->f_pcstart); /* gcs_start */
		size    = dwarf_decode_pointer((byte_t **)&reader, callsite_encoding, sizeof(void *), 0, 0, (uintptr_t)fde->f_pcstart); /* gcs_size */
		handler = dwarf_decode_pointer((byte_t **)&reader, callsite_encoding, sizeof(void *), 0, 0, (uintptr_t)fde->f_pcstart); /* gcs_handler */
		action  = dwarf_decode_pointer((byte_t **)&reader, callsite_encoding, sizeof(void *), 0, 0, (uintptr_t)fde->f_pcstart); /* gcs_action */
		start += landingpad;

#if 1 /* Compare pointers like this, as `kcs_eip' is the _RETURN_ address \
       * (i.e. the address after the piece of code that caused the exception) */
		if (kcpustate_getpc(state) > start && kcpustate_getpc(state) <= start + size)
#else
		if (kcpustate_getpc(state) >= start && kcpustate_getpc(state) < start + size)
#endif
		{
			if (handler == 0)
				return DWARF_PERSO_CONTINUE_UNWIND; /* No handler -> exception should be propagated. */
			/* Just to the associated handler */
			kcpustate_setpc(state, landingpad + handler);
			if (action != 0) {
				/* The ABI wants us to fill %eax with a pointer to the exception (`_Unwind_Exception').
				 * However, since KOS exception is kept a bit simpler (so-as to allow it to function
				 * without the need of dynamic memory allocation), the current exception isn't an internal
				 * implementation detail of the runtime, but rather stored in an exposed, per-task variable.
				 * So while what we write here really doesn't matter at all, let's just put in something
				 * that at the very least makes a bit of sense. */
#ifdef __x86_64__
				state->kcs_gpregs.gp_rax = (uintptr_t)&PERTASK(_this_exception_info);
#else /* __x86_64__ */
				state->kcs_gpregs.gp_eax = (uintptr_t)&PERTASK(_this_exception_info);
#endif /* !__x86_64__ */
			}
			return DWARF_PERSO_EXECUTE_HANDLER;
		}
	}
	/* Default behavior: abort exception handling (this function was marked as NOTHROW) */
	return DWARF_PERSO_ABORT_SEARCH;
}




PUBLIC unsigned int
NOTHROW(KCALL x86_asm_except_personality)(struct unwind_fde_struct *__restrict fde,
                                          struct kcpustate *__restrict state,
                                          void *lsda) {
	struct x86_asm_except_entry *ent;
	uintptr_t pc = kcpustate_getpc(state);
	ent = (struct x86_asm_except_entry *)lsda;
	if (ent) {
		for (; ent->ee_entry != 0; ++ent) {
			/* NOTE: Adjust for the fact that `pc' */
			if (pc > ent->ee_start && pc <= ent->ee_end) {
				if (ent->ee_mask != (uintptr_t)-1) {
					error_code_t code = error_code();
					if (ERROR_SUBCLASS(ent->ee_mask) != 0
					    ? ent->ee_mask != code
					    : ERROR_CLASS(ent->ee_mask) != ERROR_CLASS(code))
						continue; /* Different mask. */
				}
				kcpustate_setpc(state, ent->ee_entry);
				return DWARF_PERSO_EXECUTE_HANDLER;
			}
		}
	}
	return DWARF_PERSO_CONTINUE_UNWIND;
}




PUBLIC void *__cxa_begin_catch(void *ptr) {
	/* This function returns the address that would
	 * be assigned to the exception storage object:
	 * >> try {
	 * >>     ...
	 * >> } catch (MyException &exc) {
	 * >>     printk("exc @ %p\n", &exc); // Prints the address that this function returns.
	 * >> }
	 * The given `ptr' is what `libc_error_unwind()' originally set as value
	 * for the `UNWIND_REGISTER_EXCEPTION' register. */
	return ptr;
}
PUBLIC void __cxa_end_catch(void) {
	/* This function is called at the end of any user-defined catch-block
	 * (that isn't noexcept), similar to how `__cxa_begin_catch()' is always
	 * called at the start:
	 * >> try {
	 * >>     ...
	 * >> } catch (MyException) {
	 * >>     MyException &exc = *__cxa_begin_catch(?);
	 * >>     try {
	 * >>         printk("exc @ %p\n", &exc);
	 * >>     } finally {
	 * >>         __cxa_end_catch();
	 * >>     }
	 * >> }
	 * Looking at this, you should realize that it is therefor guarantied that
	 * every call to `__cxa_begin_catch()' is followed by `__cxa_end_catch()'.
	 * The book recommends that these functions should be used for reference
	 * counting of the number of recursive location where the exception object
	 * is being used. */

	/* For our purposes, we only get here when an EXCEPT block reaches
	 * its end, and we delete the exception if it wasn't re-thrown. */
	struct exception_info *info = &PERTASK(_this_exception_info);
	if (!(info->ei_flags & EXCEPT_FRETHROW))
		info->ei_code = E_OK;
	info->ei_flags &= ~EXCEPT_FRETHROW;
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_EXCEPT_C */
