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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_EXCEPT_C
#define GUARD_KERNEL_CORE_ARCH_I386_EXCEPT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/entry.h>
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/util.h>
#include <kernel/addr2line.h>
#include <kernel/arch/syslog.h>
#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/rt/except-personality.h>
#include <kernel/syslog.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <asm/registers.h>
#include <kos/kernel/cpu-state-helpers.h>

#include <assert.h>
#include <format-printer.h>
#include <inttypes.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <wait.h>

#include <libcpustate/apply.h> /* cpu_apply_ucpustate() */
#include <libinstrlen/instrlen.h>
#include <libregdump/x86.h>
#include <libunwind/dwarf.h>
#include <libunwind/eh_frame.h>
#include <libunwind/unwind.h>


/* TODO: This file needs some _major_ cleanup! */
/* TODO: This  file should be merged with libc's except.c file, and be
 *       implemented as part of the hybrid-interface (though obviously
 *       there are some major differences between the two) */

DECL_BEGIN

INTDEF NONNULL((1)) ssize_t LIBREGDUMP_CC
indent_regdump_print_format(struct regdump_printer *__restrict self,
                            unsigned int format_option);


PRIVATE NONNULL((1, 3)) void KCALL
print_unhandled_exception(pformatprinter printer, void *arg,
                          pformatprinter tb_printer, void *tb_arg,
                          char const *reason, va_list args) {
	unsigned int i;
	bool is_first_pointer;
	struct exception_info info, *tls = except_info();
	struct regdump_printer rd_printer;
	memcpy(&info, tls, sizeof(struct exception_info));
	tls->ei_code = EXCEPT_CODEOF(E_OK);

	/* Dump the exception that occurred. */
	except_print_short_description(printer, arg, &info.ei_data,
	                               EXCEPT_PRINT_SHORT_DESCRIPTION_FLAG_NORMAL);
	if (reason) {
		(*printer)(arg, "\nThrown when: ", COMPILER_STRLEN("\nThrown when: "));
		format_vprintf(printer, arg, reason, args);
	}
	(*printer)(arg, "\nRegister state:\n", COMPILER_STRLEN("\nRegister state:\n"));
	rd_printer.rdp_printer     = printer;
	rd_printer.rdp_printer_arg = arg;
	rd_printer.rdp_format      = &indent_regdump_print_format;
	regdump_gpregs(&rd_printer, &info.ei_state.kcs_gpregs);
	regdump_ip(&rd_printer, kcpustate_getpip(&info.ei_state),
	           instrlen_isa_from_kcpustate(&info.ei_state));
	regdump_flags(&rd_printer, kcpustate_getpflags(&info.ei_state));
	(*printer)(arg, "\n", 1);
	is_first_pointer = true;
	/* Print exception pointers. */
	for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i) {
		if (info.ei_data.e_args.e_pointers[i] == 0)
			continue;
		if (is_first_pointer) {
			(*printer)(arg, "Exception pointers:\n", COMPILER_STRLEN("Exception pointers:\n"));
			is_first_pointer = false;
		}
		format_printf(printer, arg,
		              "    [%u] = %p (%" PRIuPTR ")\n",
		              i,
		              info.ei_data.e_args.e_pointers[i],
		              info.ei_data.e_args.e_pointers[i]);
	}
	addr2line_printf(tb_printer, tb_arg,
	                 instruction_trypred(kcpustate_getpc(&info.ei_state),
	                                     instrlen_isa_from_kcpustate(&info.ei_state)),
	                 kcpustate_getpc(&info.ei_state), "Thrown here");
#if EXCEPT_BACKTRACE_SIZE != 0
	for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i) {
		if (!info.ei_trace[i])
			break;
		addr2line_printf(tb_printer, tb_arg,
		                 instruction_trypred(info.ei_trace[i],
		                                     instrlen_isa_from_kcpustate(&info.ei_state)),
		                 info.ei_trace[i], "Called here");
	}
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	memcpy(tls, &info, sizeof(struct exception_info));
}


/* Print information about the current exception into `printer' */
PUBLIC NONNULL((1)) ssize_t
NOTHROW(KCALL except_print_into)(pformatprinter printer, void *arg) {
	va_list empty_args;
	bzero((void *)&empty_args, sizeof(empty_args));
	print_unhandled_exception(printer, arg, printer, arg, NULL, empty_args);
	/* TODO: Track `printer' return values. */
	return 0;
}

PUBLIC void
NOTHROW(KCALL except_vprintf)(char const *__restrict reason, va_list args) {
	print_unhandled_exception(&syslog_printer, SYSLOG_LEVEL_ERR,
	                          &syslog_printer, SYSLOG_LEVEL_RAW,
	                          reason, args);
}

PUBLIC void
NOTHROW(VCALL except_printf)(char const *__restrict reason, ...) {
	va_list args;
	va_start(args, reason);
	except_vprintf(reason, args);
	va_end(args);
}

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
PRIVATE ATTR_DBGTEXT void KCALL
panic_uhe_dbg_main(unsigned int unwind_error,
                   void const *last_pc,
                   struct exception_info *info) {
	unsigned int i;
	bool is_first_pointer;
	instrlen_isa_t isa;
	/* Dump the exception that occurred. */
	except_print_short_description(&dbg_printer, NULL, &info->ei_data,
	                               EXCEPT_PRINT_SHORT_DESCRIPTION_FLAG_TTY);
	dbg_putc('\n');
	is_first_pointer = true;
	/* Print exception pointers. */
	for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i) {
		if (info->ei_data.e_args.e_pointers[i] == 0)
			continue;
		if (is_first_pointer) {
			dbg_print(DBGSTR("Exception pointers:\n"));
			is_first_pointer = false;
		}
		dbg_printf(DBGSTR("    [" AC_WHITE("%u") "] = " AC_WHITE("%p") " (" AC_WHITE("%" PRIuPTR) ")\n"),
		           i,
		           info->ei_data.e_args.e_pointers[i],
		           info->ei_data.e_args.e_pointers[i]);
	}
	isa = instrlen_isa_from_kcpustate(&info->ei_state);
	dbg_addr2line_printf(instruction_trypred(kcpustate_getpc(&info->ei_state), isa),
	                     kcpustate_getpc(&info->ei_state),
	                     DBGSTR("Thrown here"));
#if EXCEPT_BACKTRACE_SIZE != 0
	for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i) {
		if (!info->ei_trace[i])
			break;
		dbg_addr2line_printf(instruction_trypred(info->ei_trace[i], isa),
		                     info->ei_trace[i],
		                     DBGSTR("Called here"));
	}
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
#if EXCEPT_BACKTRACE_SIZE != 0
	{
		void const *prev_last_pc;
		void const *my_last_pc = last_pc;
		for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i) {
			if (!info->ei_trace[i])
				break;
		}
		prev_last_pc = i ? info->ei_trace[i - 1]
		                 : kcpustate_getpc(&info->ei_state);
		if (!my_last_pc) {
			my_last_pc = prev_last_pc;
		} else if (my_last_pc != prev_last_pc) {
			dbg_print(DBGSTR("...\n"));
			addr2line_printf(&syslog_printer, SYSLOG_LEVEL_RAW,
			                 instruction_trypred(my_last_pc, isa), my_last_pc,
			                 DBGSTR("Traceback ends here"));
		}
	}
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	if (unwind_error == UNWIND_SUCCESS) {
		dbg_printf(DBGSTR("Unwinding stopped when " AC_WITHFG(ANSITTY_CL_PURPLE, "NOTHROW()")
		                  " function %[vinfo:" AC_WHITE("%n") "] was reached\n"),
		           instruction_trypred((void const *)last_pc, isa));
	} else if (unwind_error != UNWIND_NO_FRAME) {
		dbg_printf(DBGSTR(AC_WITHCOLOR(ANSITTY_CL_WHITE, ANSITTY_CL_MAROON, "Unwinding failed")
		                  ": " AC_WHITE("%u") "\n"),
		           unwind_error);
	}
	dbg_main(0);
}

#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */


INTDEF ATTR_COLD NONNULL((1, 3)) void KCALL
kernel_halt_dump_traceback(pformatprinter printer, void *arg,
                           struct ucpustate *__restrict state);

INTERN ATTR_COLD NONNULL((2)) void FCALL
halt_unhandled_exception(unsigned int unwind_error,
                         struct kcpustate *__restrict unwind_state) {
	struct exception_info *info;
	void const *last_pc;
	instrlen_isa_t isa;
	_kernel_poison();
	last_pc = kcpustate_getpc(unwind_state);
	isa     = instrlen_isa_from_kcpustate(unwind_state);
	printk(KERN_RAW "\n\n\n");
	print_unhandled_exception(&syslog_printer, SYSLOG_LEVEL_EMERG,
	                          &syslog_printer, SYSLOG_LEVEL_RAW,
	                          NULL, NULL);
	info = except_info();

#if EXCEPT_BACKTRACE_SIZE != 0
	{
		void const *prev_last_pc;
		unsigned int i;
		void const *my_last_pc = last_pc;
		for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i) {
			if (!info->ei_trace[i])
				break;
		}
		prev_last_pc = i ? info->ei_trace[i - 1]
		                 : kcpustate_getpc(&info->ei_state);
		if (!my_last_pc) {
			my_last_pc = prev_last_pc;
		} else if (my_last_pc != prev_last_pc) {
			printk(KERN_RAW "...\n");
			addr2line_printf(&syslog_printer, SYSLOG_LEVEL_RAW,
			                 instruction_trypred(my_last_pc, isa),
			                 my_last_pc, "Traceback ends here");
		}
	}
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	if (unwind_error == UNWIND_SUCCESS) {
		printk(KERN_EMERG
		       "Unwinding stopped when NOTHROW() function "
		       "`%[vinfo:%n:%p]:%p' was reached (see last traceback entry)\n",
		       instruction_trypred(last_pc, isa), last_pc);
	} else if (unwind_error != UNWIND_NO_FRAME) {
		printk(KERN_EMERG "Unwinding failed: %u\n", unwind_error);
	}
	{
		struct ucpustate ustate;
		/* Dump the remainder of the stack after the caller stopped unwinding. */
		kcpustate_to_ucpustate(unwind_state, &ustate);
		kernel_halt_dump_traceback(&syslog_printer, SYSLOG_LEVEL_RAW, &ustate);
	}
	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_shouldtrap(KERNEL_DEBUGTRAP_ON_UNHANDLED_EXCEPT)) {
		siginfo_t si;
		if (!except_as_signal(&info->ei_data, &si))
			si.si_signo = SIGABRT;
		kernel_debugtrap(&info->ei_state, si.si_signo);
	}
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
	{
		STRUCT_DBG_ENTRY_INFO(3) einfo;
		/* Enter the debugger */
		einfo.ei_entry   = (dbg_entry_t)&panic_uhe_dbg_main;
		einfo.ei_argc    = 3;
		einfo.ei_argv[0] = (void *)(uintptr_t)unwind_error;
		einfo.ei_argv[1] = (void *)last_pc;
		einfo.ei_argv[2] = (void *)info;
		dbg_enter((struct dbg_entry_info *)&einfo, unwind_state);
	}
#else /* CONFIG_HAVE_KERNEL_DEBUGGER */
	kernel_panic(unwind_state, "Unhandled exception\n");
#endif /* !CONFIG_HAVE_KERNEL_DEBUGGER */
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_EXCEPT_C */
