/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
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
#ifndef GUARD_KERNEL_SRC_DEBUGGER_APPS_THREAD_C
#define GUARD_KERNEL_SRC_DEBUGGER_APPS_THREAD_C 1
#define DISABLE_BRANCH_PROFILING
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <debugger/util.h>
#include <kernel/addr2line.h>
#include <kernel/fs/dirent.h>
#include <kernel/mman.h>
#include <kernel/mman/execinfo.h>
#include <sched/async.h>
#include <sched/comm.h>
#include <sched/cpu.h>
#include <sched/enum.h>
#include <sched/group.h>
#include <sched/scheduler.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/minmax.h>

#include <asm/intrin.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DECL_BEGIN

#define THREAD_STATE_RUNNING    0
#define THREAD_STATE_SLEEPING   1
#define THREAD_STATE_IDLING     2
#define THREAD_STATE_TERMINATED 3

PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
enum_thread(struct task *__restrict thread, unsigned int state) {
	struct mexecinfo *ei;
	ssize_t len;
	struct task *old_current;
	pid_t pid, tid;
	dbg_savecolor();
	if (thread == dbg_current) {
		dbg_setbgcolor(ANSITTY_CL_DARK_GRAY);
		dbg_hline(0, dbg_getcur_y(), dbg_screen_width, ' ');
	}
	dbg_savecolor();
	if (task_getprocpid_of(thread) == task_getprocpid_of(dbg_current))
		dbg_setbgcolor(ANSITTY_CL_DARK_GRAY);
	ei = &FORMMAN(thread->t_mman, thismman_execinfo);
#ifdef CONFIG_HAVE_KERNEL_TASK_COMM
	if (FORTASK(thread, this_comm[0]) != '\0') {
		len = dbg_print(FORTASK(thread, this_comm));
	} else
#endif /* CONFIG_HAVE_KERNEL_TASK_COMM */
	if (ei->mei_dent) {
		len = dbg_printer(NULL,
		                  ei->mei_dent->fd_name,
		                  ei->mei_dent->fd_namelen);
	} else if (thread->t_flags & TASK_FKERNTHREAD) {
		len = dbg_print(DBGSTR("kernel"));
	} else {
		len = dbg_print(DBGSTR("??" /**/ "?"));
	}
	while (len < 10) {
		dbg_putc(' ');
		++len;
	}
	pid = task_getrootpid_of(thread);
	len = dbg_printf(DBGSTR(" %u"), pid);
	dbg_loadcolor();
	while (len < 4) {
		dbg_putc(' ');
		++len;
	}
	tid = task_getroottid_of(thread);
	len = pid == tid ? 0 : dbg_printf(DBGSTR(" %u"), tid);
	while (len < 5) {
		dbg_putc(' ');
		++len;
	}
	{
		char const *status_indicator;
		switch (state) {

		case THREAD_STATE_RUNNING:
			status_indicator = DBGSTR(AC_FG_GREEN "R");
			break;

		case THREAD_STATE_SLEEPING:
			status_indicator = DBGSTR(AC_FG_YELLOW "S");
			break;

		case THREAD_STATE_IDLING:
			status_indicator = DBGSTR(AC_FG_AQUA "I");
			break;

		case THREAD_STATE_TERMINATED:
			status_indicator = DBGSTR(AC_FG_RED "T");
			break;

		default:
			status_indicator = DBGSTR(AC_COLOR(ANSITTY_CL_BLACK, ANSITTY_CL_LIGHT_GRAY) "?");
			break;
		}
		dbg_savecolor();
		dbg_print(status_indicator);
		dbg_loadcolor();
	}
	dbg_printf(DBGSTR(" #%-2u"), thread->t_cpu->c_id);

	/* When  the thread  is sleeping,  it's current  program location will
	 * always be in `task_sleep()', so there's no need to print this info. */
	if (state != THREAD_STATE_SLEEPING) {
		old_current = dbg_current;
		dbg_current = thread;
		dbg_printf(DBGSTR(" %[vinfo:%p:%Rf:%l:%n]"),
		           dbg_getpcreg(DBG_REGLEVEL_TRAP));
		dbg_current = old_current;
	}
	dbg_loadcolor();
	dbg_putc('\n');
}



PRIVATE ATTR_DBGTEXT ssize_t TASK_ENUM_CC
task_enum_eq_cb(void *arg, struct task *thread) {
	return (struct task *)arg == thread ? -1 : 0;
}

PRIVATE ATTR_DBGTEXT bool KCALL
verify_thread_address(struct task *p) {
	return system_enum_threads_nb(&task_enum_eq_cb, p) < 0;
}

PRIVATE ATTR_DBGTEXT ssize_t TASK_ENUM_CC
task_enum_print_cb(void *UNUSED(arg), struct task *thread) {
	unsigned int state;
	uintptr_t flags;
	flags = ATOMIC_READ(thread->t_flags);
	if (flags & TASK_FRUNNING) {
		state = THREAD_STATE_RUNNING;
	} else if (flags & TASK_FTERMINATING) {
		state = THREAD_STATE_TERMINATED;
	} else if (thread == &FORCPU(thread->t_cpu, thiscpu_idle)) {
		state = THREAD_STATE_IDLING;
	} else {
		state = THREAD_STATE_SLEEPING;
	}
	enum_thread(thread, state);
	return 1;
}


DBG_COMMAND(lsthread,
            "lsthread\n"
            "\tList all threads running on the system\n") {
	dbg_print(DBGSTR("comm       pid tid S cpu location\n"));
	system_enum_threads_nb(&task_enum_print_cb, NULL);
	return 0;
}




PRIVATE ATTR_DBGTEXT bool FCALL
evalthreadexpr(char *expr, struct task **presult) {
	char *p = expr;
	switch (*p++) {

	case 'p': {
		/* Allow selecting by PID */
		unsigned long pidno;
		struct taskpid *pid;
		pidno = strtoul(p, &p, 0);
		if (*p != 0)
			break;
		pid = pidns_lookup_locked(&pidns_root, (pid_t)pidno);
		if (!pid || !awref_ptr(&pid->tp_thread)) {
			dbg_printf(DBGSTR("Error: Invalid PID %lu\n"), pidno);
			break;
		}
		*presult = awref_ptr(&pid->tp_thread);
	}	return true;

	/* TODO: Allow selecting by path:
	 *    `c0i':  cpu[0].idle
	 *    `c0c':  cpu[0].current
	 *    `c0s':  cpu[0].sleeping
	 *    `c0s2': cpu[0].sleeping->next
	 *    `bc':   bootcpu.current
	 *    `bs':   bootcpu.sleeping
	 *    `bs2':  bootcpu.sleeping->next */
	/* TODO: Allow selecting by name:
	 *    `b':    boottask
	 *    `bi':   bootidle */

	default:
		break;
	}
	return dbg_evaladdr(expr, (uintptr_t *)presult);
}


PRIVATE NONNULL((1, 2, 3, 4)) void FCALL
enumerate_thread_tids(char buf[], char const *__restrict format,
                      struct taskpid *__restrict tpid,
                      dbg_autocomplete_cb_t cb, void *arg) {
	size_t len;
again:
	len = sprintf(buf, format, taskpid_getroottid(tpid));
	(*cb)(arg, buf, len);
	if (tpid->tp_pids[0].tps_link.rb_lhs) {
		if (tpid->tp_pids[0].tps_link.rb_rhs)
			enumerate_thread_tids(buf, format, tpid->tp_pids[0].tps_link.rb_rhs, cb, arg);
		tpid = tpid->tp_pids[0].tps_link.rb_lhs;
		goto again;
	}
	if (tpid->tp_pids[0].tps_link.rb_rhs) {
		tpid = tpid->tp_pids[0].tps_link.rb_rhs;
		goto again;
	}
}

DBG_AUTOCOMPLETE(thread,
                 /*size_t*/ argc, /*char **/ argv /*[]*/,
                 /*dbg_autocomplete_cb_t*/ cb, /*void **/arg,
                 /*char const **/ starts_with, /*size_t*/ starts_with_len) {
	(void)argv;
	if (argc == 1) {
		if (!starts_with_len) {
			(*cb)(arg, DBGSTR("p"), 1);
			return;
		}
		if (starts_with[0] == 'p') {
			char pidtext[MAX_C(COMPILER_LENOF("p0" PRIMAXoN(__SIZEOF_PID_T__)),
			                   COMPILER_LENOF("p0x" PRIMAXxN(__SIZEOF_PID_T__)),
			                   COMPILER_LENOF("p0X" PRIMAXXN(__SIZEOF_PID_T__)),
			                   COMPILER_LENOF("p0b" PRIMAXbN(__SIZEOF_PID_T__)))];
			char const *format = DBGSTR("p%lu");
			if (starts_with_len >= 2 && starts_with[1] == '0') {
				format = DBGSTR("p0%" PRIoN(__SIZEOF_PID_T__));
				if (starts_with_len >= 3) {
					char ns = starts_with[2];
					if (ns == 'x') {
						format = DBGSTR("p0x%" PRIxN(__SIZEOF_PID_T__));
					} else if (ns == 'X') {
						format = DBGSTR("p0X%" PRIXN(__SIZEOF_PID_T__));
					} else if (ns == 'b') {
						format = DBGSTR("p0b%" PRIbN(__SIZEOF_PID_T__));
					} else if (ns == 'B') {
						format = DBGSTR("p0B%" PRIbN(__SIZEOF_PID_T__));
					} else if (ns >= '0' && ns <= '7') {
						/* ... */
					} else {
						return;
					}
				}
			}
			if likely(pidns_root.pn_tree != NULL)
				enumerate_thread_tids(pidtext, format, pidns_root.pn_tree, cb, arg);
			return;
		}
	}
}

DBG_COMMAND_AUTO(thread, DBG_HOOKFLAG_NORMAL,
                 "thread ADDR\n"
                 "\tSet the thread that is being debuged\n"
                 "\tWarning: Setting an invalid thread address may triple-fault the kernel\n"
                 "\t         Use " AC_WHITE("thread ADDR force") " to override security checks\n",
                 argc, argv) {
	struct task *thread;
	if (argc < 2)
		return DBG_STATUS_INVALID_ARGUMENTS;
	if (!evalthreadexpr(argv[1], &thread))
		return DBG_STATUS_INVALID_ARGUMENTS;
	if (argc >= 3 && strcmp(argv[2], DBGSTR("force")) == 0) {
		/* Accept any thread as valid. */
	} else if (!verify_thread_address(thread)) {
		dbg_printf(DBGSTR("Invalid thread %p (use `thread %p force' to override)\n"), thread, thread);
		return 1;
	}
	dbg_current = thread;
	return 0;
}

DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_APPS_THREAD_C */
