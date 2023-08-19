/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif(x -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MISC_PANIC_C
#define GUARD_KERNEL_SRC_MISC_PANIC_C 1
#define DISABLE_BRANCH_PROFILING
#define _KOS_SOURCE 1

/* Disable exception nesting assertions. Kernel panic handling
 * uses TRY a lot to deal with situations where trying to dump
 * exception information might result in more errors.
 *
 * Since we're already talking about undefined behavior here,
 * we'd only make our life harder by introducing more asserts
 * for  `!except_active()' who's failure would mean the panic
 * system recursing in on itself. */
#define NDEBUG_EXCEPT_NESTING

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/entry.h>
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <debugger/util.h>
#include <kernel/addr2line.h>
#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/memory.h>
#include <kernel/mman.h>
#include <kernel/mman/mnode.h>
#include <kernel/panic.h>
#include <kernel/poison-heap.h>
#include <kernel/printk.h>
#include <kernel/syslog.h>
#include <sched/async.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/host.h>
#include <hybrid/sched/preemption.h>

#include <asm/intrin.h>
#include <kos/except.h>
#include <kos/kernel/cpu-state-helpers.h>

#include <atomic.h>
#include <format-printer.h>
#include <inttypes.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>

#include <libdebuginfo/unwind.h>
#include <libinstrlen/instrlen.h>
#include <libunwind/errno.h>
#include <libunwind/register.h>
#include <libunwind/unwind.h>

#include "../../../libc/libc/assert.h" /* struct assert_args */

DECL_BEGIN

DATDEF uint8_t const _kernel_poisoned;
DATDEF uint8_t __kernel_poisoned ASMNAME("_kernel_poisoned");
PUBLIC uint8_t __kernel_poisoned = false;


#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
DBG_COMMAND(unpoison,
            "unpoison\n"
            "\tClears the PANIC bit after kernel panic\n"
            "\tThe NO_WARRANTY bit is not altered\n") {
	atomic_and(&__kernel_poisoned, ~_KERNEL_POISON_PANIC);
	return 0;
}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */


#undef LOG_STACK_REMAINDER
#if 1
#define LOG_STACK_REMAINDER 1
#endif

LOCAL NOBLOCK ATTR_COLDTEXT NONNULL((1)) void
NOTHROW(KCALL fixup_uninitialized_thread)(struct task *__restrict thread) {
	if (thread->t_self != thread)
		thread->t_self = thread; /* Shouldn't happen... */
	pertask_fix_task_connections(thread);
}

#if defined(__x86_64__) || defined(__i386__)
INTERN NOBLOCK ATTR_RETNONNULL struct task *
NOTHROW(KCALL x86_repair_broken_tls_state)(void);
#endif /* __x86_64__ || __i386__ */

/* Poison the kernel.
 * This operation cannot be undone and may (under rare  circumstances)
 * itself cause the kernel to crash (due to race conditions with other
 * CPUs). Use with caution, or better yet: Don't use at all!
 *
 * Additionally, this function will attempt to fix some common system
 * integrity  violations in order to allow other kernel panic code to
 * at least somewhat function correctly. (as far as that may still be
 * possible,  given that this  function is meant to  be used when the
 * kernel has become unstable) */
PUBLIC NOBLOCK ATTR_COLD void
NOTHROW(KCALL _kernel_poison)(void) {
	/* Fix some  potential  system  inconsistencies  that  may
	 * otherwise  cause infinite loops  when an assertion gets
	 * triggered (after all: there is code that can get called
	 * from within an assertion handler, which in turn is able
	 * to cause other assertions) */
	struct task *mythread;
	preemption_flag_t was;
	preemption_pushoff(&was);

	/* Try  to repair  a broken  TLS state,  since we'll need
	 * a (somewhat) working one in order to even do anything! */
#if defined(__x86_64__) || defined(__i386__)
	mythread = x86_repair_broken_tls_state();
#else /* __x86_64__ || __i386__ */
	mythread = THIS_TASK;
#endif /* !__x86_64__ && !__i386__ */

	fixup_uninitialized_thread(&boottask);
	fixup_uninitialized_thread(&asyncwork);
	fixup_uninitialized_thread(&bootidle);
	if (mythread != &boottask &&
	    mythread != &asyncwork &&
	    mythread != &bootidle)
		fixup_uninitialized_thread(mythread);

	/* Poison the kernel (indicating  that the kernel has  become
	 * inconsistent, and can no longer be trusted not to randomly
	 * crash and burn) */
	COMPILER_WRITE_BARRIER();
	atomic_store(&__kernel_poisoned, 0xff); /* Set all of the poison bits! */
	COMPILER_WRITE_BARRIER();

	/* Redirect heap functions to use the poison heap */
#ifdef CONFIG_HAVE_KERNEL_POISON_HEAP
	ph_install();
#endif /* CONFIG_HAVE_KERNEL_POISON_HEAP */

	/* TODO: Turn system_clearcache() into a no-op.
	 *       With the poison-heap, kfree() also becomes a no-op,
	 *       so system_clearcache() won't actually do  anything.
	 * However, that function  has an insanely  large range  of
	 * call-sites, any of whom may have been compromised by the
	 * kernel panic, so in trying to maintain system  integrity
	 * for  a little while longer, it's in our test interest to
	 * prevent any  unnecessary callbacks  to sub-systems  that
	 * depend on too many other sub-systems, or contain dynamic
	 * callbacks (both of which are the case for this function) */

	preemption_pop(&was);
}


PRIVATE void
NOTHROW(KCALL handle_except_during_panic_info)(void) {
	except_printf("printing panic info");
}


PRIVATE NOBLOCK ATTR_COLDTEXT ATTR_PURE WUNUSED bool
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

INTERN ATTR_COLD ATTR_COLDTEXT NONNULL((1, 3)) void KCALL
kernel_halt_dump_traceback(pformatprinter printer, void *arg,
                           struct ucpustate const *__restrict dumpstate) {
	unwind_errno_t error;
	struct ucpustate state;
	struct exception_info saved_info;
	struct exception_info *tls_info;
	isa_t isa;
#ifdef LOG_STACK_REMAINDER
	byte_t *last_good_sp;
#endif /* LOG_STACK_REMAINDER */
	_kernel_poison();
	memcpy(&state, dumpstate, sizeof(struct ucpustate));
	tls_info = except_info();
	memcpy(&saved_info, tls_info, sizeof(struct exception_info));
	tls_info->ei_code = EXCEPT_CODEOF(E_OK);
#ifdef LOG_STACK_REMAINDER
	last_good_sp = ucpustate_getsp(&state);
#endif /* LOG_STACK_REMAINDER */
	isa = ucpustate_getisa(&state);
	TRY {
		addr2line_printf(printer, arg,
		                 instruction_trypred(ucpustate_getpc(&state), isa),
		                 ucpustate_getpc(&state),
		                 "Caused here [sp=%p]",
		                 ucpustate_getsp(&state));
	} EXCEPT {
		format_printf(printer, arg, "%p: Caused here\n", ucpustate_getpc(&state));
	}
	for (;;) {
		struct ucpustate old_state;
		memcpy(&old_state, &state, sizeof(struct ucpustate));
		TRY {
			error = unwind_for_debug(ucpustate_getpc(&old_state) - 1,
			                         &unwind_getreg_ucpustate, &old_state,
			                         &unwind_setreg_ucpustate, &state);
		} EXCEPT {
			error = UNWIND_SEGFAULT;
		}
		if (error != UNWIND_SUCCESS)
			break;
		TRY {
			addr2line_printf(printer, arg,
			                 instruction_trypred(ucpustate_getpc(&state),
			                                     ucpustate_getisa(&state)),
			                 ucpustate_getpc(&state),
			                 "Called here [sp=%p]",
			                 ucpustate_getsp(&state));
		} EXCEPT {
			format_printf(printer, arg, "%p: Called here\n", ucpustate_getpc(&state));
		}
#ifdef LOG_STACK_REMAINDER
		last_good_sp = ucpustate_getsp(&state);
#endif /* LOG_STACK_REMAINDER */
	}
	if (error != UNWIND_NO_FRAME)
		format_printf(printer, arg, "Unwind failure: %u\n", error);
#ifdef LOG_STACK_REMAINDER
	TRY {
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
				void *pc;
#ifndef __ARCH_STACK_GROWS_DOWNWARDS
				iter -= sizeof(void *);
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
				TRY {
					pc = *(void **)iter;
				} EXCEPT {
					break;
				}
				if (!is_pc(pc))
					continue;
				if (is_first) {
					format_printf(printer, arg, "Analyzing remainder of stack\n");
					is_first = false;
				}
				TRY {
					addr2line_printf(printer, arg,
					                 instruction_trypred(pc, isa), pc,
					                 "Return address from [sp=%p]",
					                 iter);
				} EXCEPT {
					format_printf(printer, arg, "%p: Return address from [sp=%p]\n",
					              pc, iter);
				}
			}
		}
	} EXCEPT {
	}
#endif /* LOG_STACK_REMAINDER */
	memcpy(tls_info, &saved_info, sizeof(struct exception_info));
}


#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
PRIVATE ATTR_DBGTEXT void KCALL
panic_assert_dbg_main(void *arg) {
	struct assert_args *args;
	args = (struct assert_args *)arg;
	TRY {
		dbg_print(DBGSTR(AC_WITHCOLOR(ANSITTY_CL_WHITE, ANSITTY_CL_MAROON, "Assertion failure") "\n"));
		if (args->aa_expr)
			dbg_printf(DBGSTR("expr: "  AC_WITHFG(ANSITTY_CL_WHITE, "%s") "\n"), args->aa_expr);
		dbg_printf(DBGSTR("file: "  AC_WITHFG(ANSITTY_CL_WHITE, "%s")
		                  " (line " AC_WITHFG(ANSITTY_CL_WHITE, "%u") ")\n"),
		           args->aa_file, args->aa_line);
		if (args->aa_func)
			dbg_printf(DBGSTR("func: " AC_WITHFG(ANSITTY_CL_WHITE, "%s") "\n"), args->aa_func);
		if (args->aa_format) {
			dbg_print(DBGSTR("mesg: " AC_COLOR(ANSITTY_CL_TEAL, ANSITTY_CL_BLACK)));
			dbg_indent += 6;
			format_vprintf(&dbg_printer, NULL, args->aa_format, args->aa_args);
			dbg_indent -= 6;
			dbg_print(DBGSTR(AC_DEFCOLOR "\n"));
		}
	} EXCEPT {
		handle_except_during_panic_info();
	}
	dbg_printf(DBGSTR("addr: " AC_WITHFG(ANSITTY_CL_WHITE, "%p") "\n"),
	           kcpustate_getpc(&args->aa_state));
	dbg_main(0);
}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */


INTERN ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NOINLINE ATTR_NORETURN void
NOTHROW(FCALL libc_assertion_failure_core)(struct assert_args *__restrict args) {
	PREEMPTION_DISABLE();
	_kernel_poison();
	printk(KERN_RAW "\n\n\n");
	printk(KERN_EMERG "Assertion Failure [pc=%p]\n",
	       kcpustate_getpc(&args->aa_state));
	TRY {
		printk(KERN_RAW "%s(%d) : %s%s%s\n",
		       args->aa_file, args->aa_line,
		       args->aa_func ? args->aa_func : "",
		       args->aa_func ? " : " : "",
		       args->aa_expr);
		if (args->aa_format) {
			va_list vargs_copy;
			va_copy(vargs_copy, args->aa_args);
			format_vprintf(&syslog_printer, SYSLOG_LEVEL_RAW, args->aa_format, vargs_copy);
			va_end(vargs_copy);
			printk(KERN_RAW "\n");
		}
	} EXCEPT {
		handle_except_during_panic_info();
	}
#ifdef KCPUSTATE_IS_UCPUSTATE
	kernel_halt_dump_traceback(&syslog_printer, SYSLOG_LEVEL_RAW,
	                           &args->aa_state);
#else /* KCPUSTATE_IS_UCPUSTATE */
	{
		struct ucpustate temp;
		kcpustate_to_ucpustate(&args->aa_state, &temp);
		kernel_halt_dump_traceback(&syslog_printer, SYSLOG_LEVEL_RAW, &temp);
	}
#endif /* !KCPUSTATE_IS_UCPUSTATE */
	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_enabled())
		kernel_debugtrap(&args->aa_state, SIGTRAP);
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
	/* Enter the debugger */
	dbg_enter(&panic_assert_dbg_main, args,
	          sizeof(*args), &args->aa_state);
#else /* CONFIG_HAVE_KERNEL_DEBUGGER */
	PREEMPTION_HALT();
#endif /* !CONFIG_HAVE_KERNEL_DEBUGGER */
}




#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
PRIVATE ATTR_DBGTEXT void KCALL
panic_assert_chk_print_message(void *arg) {
	struct assert_args *args;
	args = (struct assert_args *)arg;
	TRY {
		if (args->aa_expr)
			dbg_printf(DBGSTR("expr: " AC_WITHFG(ANSITTY_CL_WHITE, "%s") "\n"), args->aa_expr);
		dbg_printf(DBGSTR("file: " AC_WITHFG(ANSITTY_CL_WHITE, "%s")
		                  " (line " AC_WITHFG(ANSITTY_CL_WHITE, "%u") ")\n"),
		           args->aa_file, args->aa_line);
		if (args->aa_func)
			dbg_printf(DBGSTR("func: " AC_WITHFG(ANSITTY_CL_WHITE, "%s") "\n"), args->aa_func);
		if (args->aa_format) {
			va_list vargs_copy;
			dbg_print(DBGSTR("mesg: " AC_COLOR(ANSITTY_CL_TEAL, ANSITTY_CL_BLACK)));
			dbg_indent += 6;
			va_copy(vargs_copy, args->aa_args);
			format_vprintf(&dbg_printer, NULL, args->aa_format, vargs_copy);
			va_end(vargs_copy);
			dbg_indent -= 6;
			dbg_print(DBGSTR(AC_DEFCOLOR "\n"));
		}
	} EXCEPT {
		handle_except_during_panic_info();
	}
	dbg_printf(DBGSTR("addr: " AC_WITHFG(ANSITTY_CL_WHITE, "%p") "\n"),
	           kcpustate_getpc(&args->aa_state));
}


#define ASSERTION_OPTION_RETRY          0
#define ASSERTION_OPTION_DEBUG          1
#define ASSERTION_OPTION_IGNORE         2
#define ASSERTION_OPTION_IGNORE_ALWAYS  3

PRIVATE ATTR_DBGRODATA char const *const assert_chk_options[] = {
	[ASSERTION_OPTION_RETRY]         = "retry",
	[ASSERTION_OPTION_DEBUG]         = "debug",
	[ASSERTION_OPTION_IGNORE]        = "ignore",
	[ASSERTION_OPTION_IGNORE_ALWAYS] = "ignore (always)",
	NULL
};

PRIVATE ATTR_DBGBSS void const *always_ignored_assertions[64] = { 0 };
PRIVATE NOBLOCK ATTR_COLDTEXT ATTR_PURE bool
NOTHROW(KCALL is_pc_always_ignored)(void const *pc) {
	unsigned int i;
	for (i = 0; i < lengthof(always_ignored_assertions); ++i) {
		if (pc == always_ignored_assertions[i])
			return true;
	}
	return false;
}

PRIVATE ATTR_COLD ATTR_COLDTEXT void KCALL
panic_assert_chk_dbg_main(void *arg) {
	struct assert_args *args;
	unsigned int option;
	args = (struct assert_args *)arg;
	if (is_pc_always_ignored(dbg_getpcreg(DBG_RT_REGLEVEL_TRAP))) {
		option = ASSERTION_OPTION_IGNORE;
		goto handle_retry_or_ignore;
	}

	/* Display a menu to let the user select what to do about the assertion... */
	option = dbg_menuex(AC_COLOR(ANSITTY_CL_WHITE, ANSITTY_CL_MAROON)
	                    "Assertion failure" AC_DEFCOLOR,
	                    assert_chk_options,
	                    0,
	                    &panic_assert_chk_print_message,
	                    args);
	if (option == ASSERTION_OPTION_IGNORE_ALWAYS) {
		unsigned int i;
		for (i = 0; i < lengthof(always_ignored_assertions); ++i) {
			if (always_ignored_assertions[i])
				continue;
			always_ignored_assertions[i] = dbg_getpcreg(DBG_RT_REGLEVEL_TRAP);
			break;
		}
		option = ASSERTION_OPTION_IGNORE;
	}
	if (option == ASSERTION_OPTION_RETRY ||
	    option == ASSERTION_OPTION_IGNORE) {
		uintptr_t acheck_result;
handle_retry_or_ignore:
		acheck_result = option == ASSERTION_OPTION_RETRY ? 1 : 0;
		/* Select the current thread as target for register accessors. */
		dbg_current = THIS_TASK;
		/* TODO: Make this part arch-independent */
#ifdef __x86_64__
		dbg_rt_setregbyidp(DBG_RT_REGLEVEL_TRAP, X86_REGISTER_GENERAL_PURPOSE_RAX, acheck_result);
#elif defined(__i386__)
		dbg_rt_setregbyidp(DBG_RT_REGLEVEL_TRAP, X86_REGISTER_GENERAL_PURPOSE_EAX, acheck_result);
#elif defined(__arm__)
		dbg_rt_setregbyidp(DBG_RT_REGLEVEL_TRAP, ARM_REGISTER_R0, acheck_result);
#else /* ... */
#error "Unsupported arch"
#endif /* !... */
		return;
	}
	/* Enter debugger mode. */
	dbg_fillscreen(' ');
	dbg_setcur(0, 0);
	panic_assert_dbg_main(arg);
}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

INTERN ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_RETNONNULL WUNUSED NONNULL((1)) struct kcpustate *
NOTHROW(FCALL libc_assertion_check_core)(struct assert_args *__restrict args) {
	/* Check if assertion failures at the caller's PC should always be ignored. */
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
	if (is_pc_always_ignored(kcpustate_getpc(&args->aa_state))) {
		/* Have `__acheck()' return `false' to break out of loop in:
		 * >> do if (expr) break; while (__acheck(expr_str));
		 * (as is part of `assert(3)' when assertion checks are supported)
		 * NOTE: If we returned `true', the to-be asserted expression
		 *       would be checked a second time (retry). */
		kcpustate_setreturnbool(&args->aa_state, false);
		return &args->aa_state;
	}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */
	PREEMPTION_DISABLE();
	_kernel_poison();
	printk(KERN_RAW "\n\n\n");
	printk(KERN_EMERG "Assertion Check [pc=%p]\n",
	       kcpustate_getpc(&args->aa_state));
	TRY {
		printk(KERN_RAW "%s(%d) : %s%s%s\n",
		       args->aa_file, args->aa_line,
		       args->aa_func ? args->aa_func : "",
		       args->aa_func ? " : " : "",
		       args->aa_expr);
		if (args->aa_format) {
			va_list vargs_copy;
			va_copy(vargs_copy, args->aa_args);
			format_vprintf(&syslog_printer, SYSLOG_LEVEL_RAW, args->aa_format, vargs_copy);
			va_end(vargs_copy);
			printk(KERN_RAW "\n");
		}
	} EXCEPT {
		handle_except_during_panic_info();
	}
	TRY {
#ifdef KCPUSTATE_IS_UCPUSTATE
		kernel_halt_dump_traceback(&syslog_printer, SYSLOG_LEVEL_RAW,
		                           &args->aa_state);
#else /* KCPUSTATE_IS_UCPUSTATE */
		struct ucpustate temp;
		kcpustate_to_ucpustate(&args->aa_state, &temp);
		kernel_halt_dump_traceback(&syslog_printer, SYSLOG_LEVEL_RAW, &temp);
#endif /* !KCPUSTATE_IS_UCPUSTATE */
	} EXCEPT {
	}
	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_enabled())
		kernel_debugtrap(&args->aa_state, SIGTRAP);
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
	/* Enter the debugger */
	dbg_enter(&panic_assert_chk_dbg_main,
	          args, sizeof(*args),
	          &args->aa_state);
#else /* CONFIG_HAVE_KERNEL_DEBUGGER */
	PREEMPTION_HALT();
#endif /* !CONFIG_HAVE_KERNEL_DEBUGGER */
}



#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
PRIVATE ATTR_DBGTEXT void KCALL
panic_genfail_dbg_main(/*char const **/ void *message) {
	void const *pc, *prev_pc;
	isa_t isa;
	pc      = dbg_getpcreg(DBG_RT_REGLEVEL_TRAP);
	isa     = dbg_rt_getisa(DBG_RT_REGLEVEL_TRAP);
	prev_pc = instruction_trypred(pc, isa);
	dbg_printf(DBGSTR(AC_COLOR(ANSITTY_CL_WHITE, ANSITTY_CL_MAROON) "%s" AC_DEFCOLOR "%[vinfo:"
	                  "file: " AC_WHITE("%f") " (line " AC_WHITE("%l") ", column " AC_WHITE("%c") ")\n"
	                  "func: " AC_WHITE("%n") "\n]"
	                  "addr: " AC_WHITE("%p") "+" AC_WHITE("%" PRIuSIZ) "\n"),
	           message, prev_pc, prev_pc,
	           (size_t)((byte_t const *)pc - (byte_t const *)prev_pc));
	dbg_main(0);
}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */


/* The `__stack_chk_guard' global is read _very_ often,
 * so   place   in   in   the   COMPACT_DATA   segment. */
#ifndef NDEBUG
INTERN ATTR_READMOSTLY uintptr_t libc_stack_chk_guard = 0x123baf37;
#else /* !NDEBUG */
INTERN ATTR_COLDDATA uintptr_t libc_stack_chk_guard = 0x123baf37;
#endif /* NDEBUG */
DEFINE_PUBLIC_ALIAS(__stack_chk_guard, libc_stack_chk_guard);


INTERN ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN void
NOTHROW(FCALL libc_stack_failure_core)(struct kcpustate *__restrict state) {
	PREEMPTION_DISABLE();
	_kernel_poison();
	printk(KERN_RAW "\n\n\n");
	printk(KERN_EMERG "Stack check failure [pc=%p]\n", kcpustate_getpc(state));
#ifdef KCPUSTATE_IS_UCPUSTATE
	kernel_halt_dump_traceback(&syslog_printer, SYSLOG_LEVEL_RAW, state);
#else /* KCPUSTATE_IS_UCPUSTATE */
	{
		struct ucpustate ustate;
		kcpustate_to_ucpustate(state, &ustate);
		kernel_halt_dump_traceback(&syslog_printer, SYSLOG_LEVEL_RAW, &ustate);
	}
#endif /* !KCPUSTATE_IS_UCPUSTATE */
	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_enabled())
		kernel_debugtrap(state, SIGSEGV);
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
	/* Enter the debugger */
	dbg_enter(&panic_genfail_dbg_main,
	          (void *)DBGSTR("Stack check failure (corrupted cookie)\n"),
	          state);
#else /* CONFIG_HAVE_KERNEL_DEBUGGER */
	PREEMPTION_HALT();
#endif /* !CONFIG_HAVE_KERNEL_DEBUGGER */
}

INTERN ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN void
NOTHROW(FCALL libc_abort_failure_core)(struct kcpustate *__restrict state) {
	PREEMPTION_DISABLE();
	_kernel_poison();
	printk(KERN_RAW "\n\n\n");
	printk(KERN_EMERG "Kernel aborted [pc=%p]\n", kcpustate_getpc(state));
#ifdef KCPUSTATE_IS_UCPUSTATE
	kernel_halt_dump_traceback(&syslog_printer, SYSLOG_LEVEL_RAW, state);
#else /* KCPUSTATE_IS_UCPUSTATE */
	{
		struct ucpustate ustate;
		kcpustate_to_ucpustate(state, &ustate);
		kernel_halt_dump_traceback(&syslog_printer, SYSLOG_LEVEL_RAW, &ustate);
	}
#endif /* !KCPUSTATE_IS_UCPUSTATE */
	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_enabled())
		kernel_debugtrap(state, SIGABRT);
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
	/* Enter the debugger */
	dbg_enter(&panic_genfail_dbg_main,
	          (void *)DBGSTR("Kernel called abort()\n"),
	          state);
#else /* CONFIG_HAVE_KERNEL_DEBUGGER */
	PREEMPTION_HALT();
#endif /* !CONFIG_HAVE_KERNEL_DEBUGGER */
}


#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
struct panic_args {
	char const *format;
	va_list     args;
};
PRIVATE ATTR_DBGTEXT void KCALL
panic_kernel_dbg_main(void *arg) {
	struct panic_args *args;
	void const *pc, *prev_pc;
	isa_t isa;
	args = (struct panic_args *)arg;
	pc      = dbg_getpcreg(DBG_RT_REGLEVEL_TRAP);
	isa     = dbg_rt_getisa(DBG_RT_REGLEVEL_TRAP);
	prev_pc = instruction_trypred(pc, isa);
	dbg_printf(DBGSTR("Kernel Panic\n"
	                  "%[vinfo:" "file: " AC_WHITE("%f") " (line " AC_WHITE("%l") ", column " AC_WHITE("%c") ")\n"
	                             "func: " AC_WHITE("%n") "\n"
	                  "]"),
	           prev_pc);
	if (args->format) {
		dbg_print(DBGSTR("mesg: " AC_COLOR(ANSITTY_CL_TEAL, ANSITTY_CL_BLACK)));
		dbg_indent += 6;
		TRY {
			format_vprintf(&dbg_printer, NULL, args->format, args->args);
		} EXCEPT {
			handle_except_during_panic_info();
		}
		dbg_indent -= 6;
		dbg_print(DBGSTR(AC_DEFCOLOR "\n"));
	}
	dbg_printf(DBGSTR("addr: " AC_WHITE("%p") "+" AC_WHITE("%" PRIuSIZ) "\n"),
	           prev_pc, (size_t)((byte_t const *)pc - (byte_t const *)prev_pc));
	dbg_main(0);
}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN void
NOTHROW(FCALL kernel_vpanic_ucpustate_n)(unsigned int n_skip,
                                         struct ucpustate *__restrict state,
                                         char const *format, va_list args) {
	(void)n_skip; /* TODO: Support for `n_skip'! */
	PREEMPTION_DISABLE();
	_kernel_poison();
	printk(KERN_RAW "\n\n\n");
	printk(KERN_EMERG "Kernel Panic [pc=%p]\n",
	       ucpustate_getpc(state));
	if (format) {
		va_list vargs_copy;
		va_copy(vargs_copy, args);
		TRY {
			format_vprintf(&syslog_printer, SYSLOG_LEVEL_EMERG, format, vargs_copy);
		} EXCEPT {
			handle_except_during_panic_info();
		}
		va_end(vargs_copy);
		printk(KERN_EMERG "\n");
	}
	kernel_halt_dump_traceback(&syslog_printer, SYSLOG_LEVEL_RAW, state);
	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_enabled())
		kernel_debugtrap(state, SIGABRT);
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
	/* Enter the debugger */
	{
		struct panic_args pargs;
		if (format)
			va_copy(pargs.args, args);
		pargs.format = format;
		dbg_enter(&panic_kernel_dbg_main, &pargs, state);
	}
#else /* CONFIG_HAVE_KERNEL_DEBUGGER */
	PREEMPTION_HALT();
#endif /* !CONFIG_HAVE_KERNEL_DEBUGGER */
}

PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN void
NOTHROW(FCALL kernel_vpanic_ucpustate)(struct ucpustate *__restrict state,
                                       char const *format, va_list args) {
	kernel_vpanic_ucpustate_n(0, state, format, args);
}

PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN NONNULL((1)) void
NOTHROW(VCALL kernel_panic_ucpustate)(struct ucpustate *__restrict state,
                                      char const *format, ...) {
	va_list args;
	va_start(args, format);
	kernel_vpanic_ucpustate_n(0, state, format, args);
}

PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN NONNULL((2)) void
NOTHROW(VCALL kernel_panic_ucpustate_n)(unsigned int n_skip,
                                        struct ucpustate *__restrict state,
                                        char const *format, ...) {
	va_list args;
	va_start(args, format);
	kernel_vpanic_ucpustate_n(n_skip, state, format, args);
}



/************************************************************************/
/* LCPUSTATE                                                            */
/************************************************************************/
#ifndef LCPUSTATE_ALIAS
PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN NONNULL((2)) void
NOTHROW(FCALL kernel_vpanic_lcpustate_n)(unsigned int n_skip,
                                         struct lcpustate *__restrict state,
                                         char const *format, va_list args) {
	struct ucpustate ustate;
	lcpustate_to_ucpustate(state, &ustate);
	kernel_vpanic_ucpustate_n(n_skip, &ustate, format, args);
}

PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL kernel_vpanic_lcpustate)(struct lcpustate *__restrict state,
                                       char const *format, va_list args) {
	kernel_vpanic_lcpustate_n(0, state, format, args);
}

PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN NONNULL((1)) void
NOTHROW(VCALL kernel_panic_lcpustate)(struct lcpustate *__restrict state,
                                      char const *format, ...) {
	va_list args;
	va_start(args, format);
	kernel_vpanic_lcpustate_n(0, state, format, args);
}

PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN NONNULL((2)) void
NOTHROW(VCALL kernel_panic_lcpustate_n)(unsigned int n_skip,
                                        struct lcpustate *__restrict state,
                                        char const *format, ...) {
	va_list args;
	va_start(args, format);
	kernel_vpanic_lcpustate_n(n_skip, state, format, args);
}
#endif /* !LCPUSTATE_ALIAS */




/************************************************************************/
/* KCPUSTATE                                                            */
/************************************************************************/
#ifndef KCPUSTATE_ALIAS
PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN NONNULL((2)) void
NOTHROW(FCALL kernel_vpanic_kcpustate_n)(unsigned int n_skip,
                                         struct kcpustate *__restrict state,
                                         char const *format, va_list args) {
	struct ucpustate ustate;
	kcpustate_to_ucpustate(state, &ustate);
	kernel_vpanic_ucpustate_n(n_skip, &ustate, format, args);
}

PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL kernel_vpanic_kcpustate)(struct kcpustate *__restrict state,
                                       char const *format, va_list args) {
	kernel_vpanic_kcpustate_n(0, state, format, args);
}

PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN NONNULL((1)) void
NOTHROW(VCALL kernel_panic_kcpustate)(struct kcpustate *__restrict state,
                                      char const *format, ...) {
	va_list args;
	va_start(args, format);
	kernel_vpanic_kcpustate_n(0, state, format, args);
}

PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN NONNULL((2)) void
NOTHROW(VCALL kernel_panic_kcpustate_n)(unsigned int n_skip,
                                        struct kcpustate *__restrict state,
                                        char const *format, ...) {
	va_list args;
	va_start(args, format);
	kernel_vpanic_kcpustate_n(n_skip, state, format, args);
}
#endif /* !KCPUSTATE_ALIAS */




/************************************************************************/
/* ICPUSTATE                                                            */
/************************************************************************/
#ifndef ICPUSTATE_ALIAS
PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN NONNULL((2)) void
NOTHROW(FCALL kernel_vpanic_icpustate_n)(unsigned int n_skip,
                                         struct icpustate *__restrict state,
                                         char const *format, va_list args) {
	struct ucpustate ustate;
	icpustate_to_ucpustate(state, &ustate);
	kernel_vpanic_ucpustate_n(n_skip, &ustate, format, args);
}

PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL kernel_vpanic_icpustate)(struct icpustate *__restrict state,
                                       char const *format, va_list args) {
	kernel_vpanic_icpustate_n(0, state, format, args);
}

PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN NONNULL((1)) void
NOTHROW(VCALL kernel_panic_icpustate)(struct icpustate *__restrict state,
                                      char const *format, ...) {
	va_list args;
	va_start(args, format);
	kernel_vpanic_icpustate_n(0, state, format, args);
}

PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN NONNULL((2)) void
NOTHROW(VCALL kernel_panic_icpustate_n)(unsigned int n_skip,
                                        struct icpustate *__restrict state,
                                        char const *format, ...) {
	va_list args;
	va_start(args, format);
	kernel_vpanic_icpustate_n(n_skip, state, format, args);
}
#endif /* !ICPUSTATE_ALIAS */




/************************************************************************/
/* SCPUSTATE                                                            */
/************************************************************************/
#ifndef SCPUSTATE_ALIAS
PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN NONNULL((2)) void
NOTHROW(FCALL kernel_vpanic_scpustate_n)(unsigned int n_skip,
                                         struct scpustate *__restrict state,
                                         char const *format, va_list args) {
	struct ucpustate ustate;
	scpustate_to_ucpustate(state, &ustate);
	kernel_vpanic_ucpustate_n(n_skip, &ustate, format, args);
}

PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL kernel_vpanic_scpustate)(struct scpustate *__restrict state,
                                       char const *format, va_list args) {
	kernel_vpanic_scpustate_n(0, state, format, args);
}

PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN NONNULL((1)) void
NOTHROW(VCALL kernel_panic_scpustate)(struct scpustate *__restrict state,
                                      char const *format, ...) {
	va_list args;
	va_start(args, format);
	kernel_vpanic_scpustate_n(0, state, format, args);
}

PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN NONNULL((2)) void
NOTHROW(VCALL kernel_panic_scpustate_n)(unsigned int n_skip,
                                        struct scpustate *__restrict state,
                                        char const *format, ...) {
	va_list args;
	va_start(args, format);
	kernel_vpanic_scpustate_n(n_skip, state, format, args);
}
#endif /* !SCPUSTATE_ALIAS */





/************************************************************************/
/* FCPUSTATE                                                            */
/************************************************************************/
#ifndef FCPUSTATE_ALIAS
PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN NONNULL((2)) void
NOTHROW(FCALL kernel_vpanic_fcpustate_n)(unsigned int n_skip,
                                         struct fcpustate *__restrict state,
                                         char const *format, va_list args) {
	struct ucpustate ustate;
	/* XXX: Don't convert to ucpustate. - This causes information to be lost... */
	fcpustate_to_ucpustate(state, &ustate);
	kernel_vpanic_ucpustate_n(n_skip, &ustate, format, args);
}

PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL kernel_vpanic_fcpustate)(struct fcpustate *__restrict state,
                                       char const *format, va_list args) {
	kernel_vpanic_fcpustate_n(0, state, format, args);
}

PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN NONNULL((1)) void
NOTHROW(VCALL kernel_panic_fcpustate)(struct fcpustate *__restrict state,
                                      char const *format, ...) {
	va_list args;
	va_start(args, format);
	kernel_vpanic_fcpustate_n(0, state, format, args);
}

PUBLIC ABNORMAL_RETURN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN NONNULL((2)) void
NOTHROW(VCALL kernel_panic_fcpustate_n)(unsigned int n_skip,
                                        struct fcpustate *__restrict state,
                                        char const *format, ...) {
	va_list args;
	va_start(args, format);
	kernel_vpanic_fcpustate_n(n_skip, state, format, args);
}
#endif /* !FCPUSTATE_ALIAS */


DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_PANIC_C */
