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
#ifndef GUARD_KERNEL_SRC_MISC_COREDUMP_C
#define GUARD_KERNEL_SRC_MISC_COREDUMP_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <kernel/coredump.h>
#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/syslog.h>

#include <kos/coredump.h>
#include <kos/except.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <assert.h>
#include <format-printer.h>
#include <inttypes.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>

#include <libunwind/errno.h>
#include <libunwind/unwind.h>

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/debugger.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/path.h>
#include <kernel/mman/execinfo.h>
#include <sched/group.h>
#include <sched/task.h>

#include <libinstrlen/instrlen.h>
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

DECL_BEGIN

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
PRIVATE void KCALL
dbg_print_siginfo(siginfo_t const *__restrict info) {
	dbg_printf(DBGSTR("signal %" PRIuN(__SIZEOF_SIGNO_T__)
	                  " (" AC_CYAN("SIG%s") ": " AC_WHITE("%s") ")\n"),
	           info->si_signo,
	           sigabbrev_np(info->si_signo),
	           sigdescr_np(info->si_signo));
	if (info->si_code != 0) {
		dbg_printf(DBGSTR("\tcode:  %u (" AC_CYAN("%s") ": " AC_WHITE("%s") ")\n"),
		           (unsigned int)info->si_code,
		           sigcodename_np(info->si_signo, info->si_code),
		           sigcodedesc_np(info->si_signo, info->si_code));
	}
	if (info->si_errno != 0) {
		dbg_printf(DBGSTR("\terrno: %" PRIuN(__SIZEOF_ERRNO_T__)
		                  " (" AC_CYAN("%s") ": " AC_WHITE("%s") ")\n"),
		           info->si_errno,
		           strerrorname_np(info->si_errno),
		           strerrordesc_np(info->si_errno));
	}
}

PRIVATE NONNULL((3)) void KCALL
dbg_coredump(void const *const *traceback_vector,
             size_t traceback_length,
             struct ucpustate const *orig_ustate,
             void const *const *ktraceback_vector,
             size_t ktraceback_length,
             struct kcpustate const *orig_kstate,
             union coredump_info const *reason,
             uintptr_t unwind_error) {
	size_t tbi;
	isa_t isa;
	void const *current_pc;
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
		dbg_print(DBGSTR("Coredump "));
		if (ei->mei_path && ei->mei_dent) {
			path_printent(ei->mei_path,
			              ei->mei_dent->fd_name,
			              ei->mei_dent->fd_namelen,
			              &dbg_printer,
			              NULL);
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

	if (reason) {
		if (COREDUMP_INFO_ISEXCEPT(unwind_error)) {
			siginfo_t siginfo;
			unsigned int i;
			except_print_short_description(&dbg_printer, NULL, &reason->ci_except,
			                               EXCEPT_PRINT_SHORT_DESCRIPTION_FLAG_TTY);
			dbg_putc('\n');
			for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i) {
				if (!reason->ci_except.e_args.e_pointers[i])
					continue;
				dbg_printf(DBGSTR("\tpointer[%u] = " AC_WHITE("%#p") " (" AC_WHITE("%" PRIuPTR) ")\n"),
				           i, reason->ci_except.e_args.e_pointers[i],
				           reason->ci_except.e_args.e_pointers[i]);
			}
			if (except_as_signal(&reason->ci_except, &siginfo))
				dbg_print_siginfo(&siginfo);
			dbg_addr2line_printf(reason->ci_except.e_faultaddr,
			                     instruction_trysucc(reason->ci_except.e_faultaddr,
			                                         kcpustate_getisa(orig_ustate)),
			                     "faultaddr");
		} else if (COREDUMP_INFO_ISSIGNAL(unwind_error)) {
			dbg_print_siginfo(&reason->ci_signal);
		} else if (COREDUMP_INFO_ISDLERROR(unwind_error)) {
			dbg_printf(DBGSTR("dlerror: " AC_YELLOW("%q") "\n"), reason->ci_dlerror);
		} else if (COREDUMP_INFO_ISABORT(unwind_error)) {
			dbg_printf(DBGSTR("abort: " AC_YELLOW("%q") "\n"), reason->ci_abrtmsg);
		} else if (COREDUMP_INFO_ISASSERT(unwind_error)) {
			if (reason->ci_assert.ca_expr)
				dbg_printf(DBGSTR("assert.expr: " AC_YELLOW("%q") "\n"), reason->ci_assert.ca_expr);
			if (reason->ci_assert.ca_file)
				dbg_printf(DBGSTR("assert.file: " AC_YELLOW("%q") "\n"), reason->ci_assert.ca_file);
			if (reason->ci_assert.ca_line)
				dbg_printf(DBGSTR("assert.line: " AC_WHITE("%" PRIuPTR) "\n"), reason->ci_assert.ca_line);
			if (reason->ci_assert.ca_func)
				dbg_printf(DBGSTR("assert.func: " AC_YELLOW("%q") "\n"), reason->ci_assert.ca_func);
			if (reason->ci_assert.ca_mesg)
				dbg_printf(DBGSTR("assert.mesg: " AC_YELLOW("%q") "\n"), reason->ci_assert.ca_mesg);
		}
	}
	isa = ISA_DEFAULT;
	if (orig_kstate) {
		isa = kcpustate_getisa(orig_kstate);
		dbg_addr2line_printf(kcpustate_getpc(orig_kstate),
		                     instruction_trysucc(kcpustate_getpc(orig_kstate), isa),
		                     DBGSTR("orig_kstate"));
	}
	for (tbi = 0; tbi < ktraceback_length; ++tbi) {
		dbg_addr2line_printf(ktraceback_vector[tbi],
		                     instruction_trysucc(ktraceback_vector[tbi], isa),
		                     DBGSTR("ktraceback_vector[%" PRIuSIZ "]"), tbi);
	}
	isa = ucpustate_getisa(orig_ustate);
	dbg_addr2line_printf(ucpustate_getpc(orig_ustate),
	                     instruction_trysucc(ucpustate_getpc(orig_ustate), isa),
	                     DBGSTR("orig_ustate"));
	for (tbi = 0; tbi < traceback_length; ++tbi) {
		dbg_addr2line_printf(traceback_vector[tbi],
		                     instruction_trysucc(traceback_vector[tbi], isa),
		                     DBGSTR("traceback_vector[%" PRIuSIZ "]"),
		                     tbi);
	}
	current_pc = dbg_getpcreg(DBG_RT_REGLEVEL_TRAP);
	if (current_pc != ucpustate_getpc(orig_ustate) &&
	    (traceback_length == 0 ||
	     current_pc != traceback_vector[traceback_length - 1])) {
		isa = dbg_rt_getisa(DBG_RT_REGLEVEL_TRAP);
		dbg_addr2line_printf(current_pc,
		                     instruction_trysucc(current_pc, isa),
		                     DBGSTR("curr_ustate"));
	}

	(void)unwind_error;

	/* Switch over to the debugger CLI */
	dbg_main(0);
}

PRIVATE NONNULL((1, 4)) struct ucpustate const *KCALL
do_dbg_coredump(struct ucpustate const *curr_ustate,
                void const *const *traceback_vector,
                size_t traceback_length,
                struct ucpustate const *orig_ustate,
                void const *const *ktraceback_vector,
                size_t ktraceback_length,
                struct kcpustate const *orig_kstate,
                union coredump_info const *reason,
                unwind_errno_t unwind_error) {
	STRUCT_DBG_ENTRY_INFO(8) entry;
	entry.ei_argc    = 8;
	entry.ei_argv[0] = (void *)(uintptr_t)traceback_vector;
	entry.ei_argv[1] = (void *)(uintptr_t)traceback_length;
	entry.ei_argv[2] = (void *)(uintptr_t)orig_ustate;
	entry.ei_argv[3] = (void *)(uintptr_t)ktraceback_vector;
	entry.ei_argv[4] = (void *)(uintptr_t)ktraceback_length;
	entry.ei_argv[5] = (void *)(uintptr_t)orig_kstate;
	entry.ei_argv[6] = (void *)(uintptr_t)reason;
	entry.ei_argv[7] = (void *)(uintptr_t)unwind_error;
	entry.ei_entry   = (dbg_entry_t)&dbg_coredump;
	/* Enter the debugger. */
	curr_ustate = dbg_enter_r((struct dbg_entry_info *)&entry,
	                          (struct ucpustate *)curr_ustate);
	return curr_ustate;
}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */


PRIVATE void KCALL
printk_err_siginfo(siginfo_t const *__restrict info) {
	printk(KERN_ERR "signal %" PRIuN(__SIZEOF_SIGNO_T__) " (SIG%s: %s)\n",
	       info->si_signo,
	       sigabbrev_np(info->si_signo),
	       sigdescr_np(info->si_signo));
	if (info->si_code != 0) {
		printk(KERN_ERR "\tcode:  %u (%s: %s)\n",
		       (unsigned int)info->si_code,
		       sigcodename_np(info->si_signo, info->si_code),
		       sigcodedesc_np(info->si_signo, info->si_code));
	}
	if (info->si_errno != 0) {
		printk(KERN_ERR "\terrno: %" PRIuN(__SIZEOF_ERRNO_T__) " (%s: %s)\n",
		       info->si_errno,
		       strerrorname_np(info->si_errno),
		       strerrordesc_np(info->si_errno));
	}
}



/* Main entry point for creating coredumps of the calling process.
 * When this function returns, the caller will usually throw an `E_EXIT_PROCESS' exception
 * in order to terminate the calling process.
 * @param: curr_ustate:       The current CPU state after unwinding (points to the call-site
 *                            of  the last use  of `RETHROW()' before  an exception could no
 *                            longer be handled)
 * @param: orig_ustate:       The   original   CPU   state   that   caused   the  exception/signal
 *                            When  unwinding was not  performed at any point,  or if the coredump
 *                            is the result of an unhandled signal, the contents of this structure
 *                            are identical to `curr_ustate'
 *                            Note  that in the later case, the caller must ensure that
 *                            `traceback_vector' is `NULL', and `traceback_length' is 0
 * @param: traceback_vector:  A selection of  known traceback instruction  points that were  traversed
 *                            by the user-space unwind process between `orig_ustate' and `curr_ustate'
 *                            Note that this  vector may  be incomplete  and therefor  is only  useful
 *                            for the purposes of being  displayed to a human  as part of a  traceback
 *                            listing.
 *                            Note that when `traceback_length != 0 && traceback_vector[traceback_length-1] ==
 *                            ucpustate_getpc(curr_ustate)',  it  can  be   assumed  that  the  traceback   is
 *                            complete  and  contains  all  traversed  instruction  locations.  In  this case,
 *                            a  traceback  displayed  to  a  human  should  not  include  the  text  location
 *                            at   `traceback_vector[traceback_length-1]',   since    that   location    would
 *                            also   be   printed   when  unwinding   is   completed  for   the   purposes  of
 *                            displaying a traceback.
 * @param: traceback_length:  The number of instruction pointers within `traceback_vector'
 * @param: reason:            The error that brought forth the coredump. (exact interpretation depends on
 *                            `unwind_error').  May  be set  to `NULL'  if no  additional info  is given.
 * @param: unwind_error:      The unwind error that caused user-space to halt exception handling,
 *                            or `UNWIND_SUCCESS' if the coredump  was triggered by a signal  and
 *                            never caused any unwinding to be done.
 *                            In the former,  it is more  likely that  `unwind_error == UNWIND_USER_NOTHROW',
 *                            which happens  when  an  exception  is propagated  through  a  function  marked
 *                            as  `NOTHROW()'  (or `noexcept'  if  you prefer  that  one), however  any other
 *                            error can also be indicate such as `UNWIND_USER_RECURSION' in case an exception
 *                            was triggered whilst  user-space was  already in  the process  of handling  two
 *                            others, and `UNWIND_USER_DISABLED' in case user-space exception handling  never
 *                            even got triggered.
 * @param: orig_kstate:       The kernel-space CPU state where the exception originally got thrown, or
 *                            `NULL' if it that information has been lost as the result of  user-space
 *                            exception handling, or if the  exception didn't actually originate  from
 *                            the kernel.
 * @param: ktraceback_vector: The vector of kernel-space program pointers traversed during unwinding.
 *                            Always `NULL' when `orig_kstate' is also `NULL'
 * @param: ktraceback_length: The   number   of   program   pointers   found   within   `ktraceback_vector'
 * The complete traceback of any given coredump looks like this (from least-recent address, to most-recent,
 * with  program  pointer  information  which  may  not  necessarily  be  known  written  in   [brackets]):
 *
 *             [orig_kstate]
 *             [ktraceback_vector[0]]
 *             [ktraceback_vector[1]]
 *             [...]
 *             [ktraceback_vector[ktraceback_length - 1]]
 *             orig_ustate
 *             [traceback_vector[0]]
 *             [traceback_vector[1]]
 *             [...]
 *             [traceback_vector[traceback_length - 1]]    // May be identical to `curr_ustate'
 *             curr_ustate                                 // May be identical to `orig_ustate'
 *             [unwind(curr_ustate)]                       // In theory, unwinding would continue here
 *             [unwind(unwind(curr_ustate))]
 *             [...]
 *
 */
PUBLIC NONNULL((1, 4)) void KCALL
coredump_create(struct ucpustate const *curr_ustate,
                void const *const *traceback_vector, size_t traceback_length,
                struct ucpustate const *orig_ustate,
                void const *const *ktraceback_vector, size_t ktraceback_length,
                struct kcpustate const *orig_kstate,
                union coredump_info const *reason,
                unwind_errno_t unwind_error)
		THROWS(...) {
	size_t tbi;
	assert(curr_ustate != NULL);
	assert(orig_ustate != NULL);
	assert(bcmp(curr_ustate, orig_ustate, sizeof(ucpustate)) == 0
	       ? (traceback_vector == NULL && traceback_length == 0)
	       : true);
	assert(orig_kstate == NULL
	       ? (ktraceback_vector == NULL && ktraceback_length == 0)
	       : true);
	printk(KERN_ERR "[coredump] Creating coredump...\n");
#define VINFO_FORMAT  "%[vinfo:%p [%Rf:%l,%c:%n]]"
	if (reason) {
		if (COREDUMP_INFO_ISEXCEPT(unwind_error)) {
			siginfo_t siginfo;
			unsigned int i;
			except_print_short_description(&syslog_printer, SYSLOG_LEVEL_ERR, &reason->ci_except,
			                               EXCEPT_PRINT_SHORT_DESCRIPTION_FLAG_NORMAL);
			printk(KERN_ERR "\n");
			for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i) {
				if (!reason->ci_except.e_args.e_pointers[i])
					continue;
				printk(KERN_ERR "\tpointer[%u] = %p (%" PRIuPTR ")\n",
				       i, reason->ci_except.e_args.e_pointers[i],
				       reason->ci_except.e_args.e_pointers[i]);
			}
			if (except_as_signal(&reason->ci_except, &siginfo))
				printk_err_siginfo(&siginfo);
			printk(KERN_RAW VINFO_FORMAT " faultaddr\n", reason->ci_except.e_faultaddr);
		} else if (COREDUMP_INFO_ISSIGNAL(unwind_error)) {
			printk_err_siginfo(&reason->ci_signal);
		} else if (COREDUMP_INFO_ISDLERROR(unwind_error)) {
			printk(KERN_RAW "dlerror: %q\n", reason->ci_dlerror);
		} else if (COREDUMP_INFO_ISABORT(unwind_error)) {
			printk(KERN_RAW "abort: %q\n", reason->ci_abrtmsg);
		} else if (COREDUMP_INFO_ISASSERT(unwind_error)) {
			if (reason->ci_assert.ca_expr)
				printk(KERN_RAW "assert.expr: %q\n", reason->ci_assert.ca_expr);
			if (reason->ci_assert.ca_file)
				printk(KERN_RAW "assert.file: %q\n", reason->ci_assert.ca_file);
			if (reason->ci_assert.ca_line)
				printk(KERN_RAW "assert.line: %" PRIuPTR "\n", reason->ci_assert.ca_line);
			if (reason->ci_assert.ca_func)
				printk(KERN_RAW "assert.func: %q\n", reason->ci_assert.ca_func);
			if (reason->ci_assert.ca_mesg)
				printk(KERN_RAW "assert.mesg: %q\n", reason->ci_assert.ca_mesg);
		}
	}
	if (orig_kstate)
		printk(KERN_RAW VINFO_FORMAT " orig_kstate\n", kcpustate_getpc(orig_kstate));
	for (tbi = 0; tbi < ktraceback_length; ++tbi) {
		printk(KERN_RAW VINFO_FORMAT " ktraceback_vector[%" PRIuSIZ "]\n",
		       ktraceback_vector[tbi], tbi);
	}
	printk(KERN_RAW VINFO_FORMAT " orig_ustate\n", ucpustate_getpc(orig_ustate));
	for (tbi = 0; tbi < traceback_length; ++tbi) {
		printk(KERN_RAW VINFO_FORMAT " traceback_vector[%" PRIuSIZ "]\n",
		       traceback_vector[tbi], tbi);
	}
	if (ucpustate_getpc(curr_ustate) != ucpustate_getpc(orig_ustate) &&
	    (traceback_length == 0 || ucpustate_getpc(curr_ustate) != traceback_vector[traceback_length - 1])) {
		printk(KERN_RAW VINFO_FORMAT " curr_ustate\n",
		       ucpustate_getpc(curr_ustate));
	}

	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_shouldtrap(KERNEL_DEBUGTRAP_ON_COREDUMP)) {
		siginfo_t siginfo;
		if (!except_as_signal(except_data(), &siginfo))
			siginfo.si_signo = SIGABRT;
#if 1
		/* Trigger a debugger trap at last valid text location. */
		orig_ustate = kernel_debugtrap_r((struct ucpustate *)orig_ustate, siginfo.si_signo);
#else
		/* Trigger a debugger trap at last valid text location. */
		curr_ustate = kernel_debugtrap_r((struct ucpustate *)curr_ustate, siginfo.si_signo);
#endif
	} else {
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
		/* Check if we should enter the builtin debugger. */
		if (kernel_debug_on & KERNEL_DEBUG_ON_COREDUMP) {
			orig_ustate = do_dbg_coredump(curr_ustate,
			                              traceback_vector,
			                              traceback_length,
			                              orig_ustate,
			                              ktraceback_vector,
			                              ktraceback_length,
			                              orig_kstate,
			                              reason,
			                              unwind_error);
		}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */
	}

	/* TODO: Generate an ELF core file for use with gdb. */
	(void)unwind_error;
}




/* Create a coredump because of the currently thrown exception */
PUBLIC ATTR_NOINLINE NONNULL((1, 2)) void FCALL
coredump_create_for_exception(struct icpustate const *__restrict state,
                              struct exception_info const *__restrict info,
                              bool originates_from_kernelspace) {
#ifdef ICPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define LOCAL_p_ust state
#else /* ICPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#define LOCAL_p_ust (&ust)
	struct ucpustate ust;
	icpustate_user_to_ucpustate(state, LOCAL_p_ust);
#endif /* !ICPUSTATE_IS_TRANSITIVE_UCPUSTATE */
	if (!originates_from_kernelspace) {
		/* If the exception doesn't originate from kernel-space, such as
		 * an E_SEGFAULT propagated  by `userexcept_handler()', then  we
		 * mustn't include whatever information is still dangling in the
		 * kernel's  exception state descriptor  (because that info will
		 * still  refer to  the previous  thrown exception,  and not the
		 * current one)
		 * Also: The current exception doesn't actually have a kernel side. */
		coredump_create(LOCAL_p_ust, NULL, 0, LOCAL_p_ust, NULL, 0, NULL,
		                container_of(&info->ei_data, union coredump_info, ci_except),
		                UNWIND_USER_DISABLED);
	} else {
#if EXCEPT_BACKTRACE_SIZE != 0
		{
			size_t i;
			for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i) {
				if (info->ei_trace[i] == NULL)
					break;
			}
			coredump_create(LOCAL_p_ust, NULL, 0, LOCAL_p_ust, i ? info->ei_trace : NULL, i, &info->ei_state,
			                container_of(&info->ei_data, union coredump_info, ci_except),
			                UNWIND_USER_DISABLED);
		}
#else /* EXCEPT_BACKTRACE_SIZE != 0 */
		coredump_create(LOCAL_p_ust, NULL, 0, LOCAL_p_ust, NULL, 0, &info->ei_state,
		                container_of(&info->ei_data, union coredump_info, ci_except),
		                UNWIND_USER_DISABLED);
#endif /* EXCEPT_BACKTRACE_SIZE == 0 */
	}
#undef LOCAL_p_ust
}

/* Create a coredump because of the given signal `si' */
PUBLIC ATTR_NOINLINE NONNULL((1, 2)) void FCALL
coredump_create_for_signal(struct icpustate const *__restrict state,
                           siginfo_t const *__restrict si) {
#ifdef ICPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define LOCAL_p_ust state
#else /* ICPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#define LOCAL_p_ust (&ust)
	struct ucpustate ust;
	icpustate_user_to_ucpustate(state, LOCAL_p_ust);
#endif /* !ICPUSTATE_IS_TRANSITIVE_UCPUSTATE */
	coredump_create(LOCAL_p_ust, NULL, 0, LOCAL_p_ust, NULL, 0, NULL,
	                container_of(si, union coredump_info, ci_signal),
	                UNWIND_SUCCESS);
#undef LOCAL_p_ust
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_COREDUMP_C */
