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
#ifndef GUARD_KERNEL_SRC_DEBUGGER_APPS_THREAD_C
#define GUARD_KERNEL_SRC_DEBUGGER_APPS_THREAD_C 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_DEBUGGER
#include <debugger/function.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <debugger/util.h>
#include <kernel/addr2line.h>
#include <kernel/vm.h>
#include <sched/cpu.h>
#include <sched/pid.h>
#include <sched/task.h>

#include <asm/intrin.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DECL_BEGIN

#define THREAD_STATE_RUNNING  0
#define THREAD_STATE_SLEEPING 1
#define THREAD_STATE_IDLING   2
#ifndef CONFIG_NO_SMP
#define THREAD_STATE_PENDING  3
#endif /* !CONFIG_NO_SMP */
#define THREAD_STATE_OTHER    4

PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
enum_thread(struct task *__restrict thread, unsigned int state) {
	dbg_attr_t old_attr = dbg_attr;
	if (thread == dbg_current)
		dbg_setfgcolor(DBG_COLOR_GREEN);
	dbg_printf(DBGSTR("%p "), thread);
	dbg_attr = old_attr;
	dbg_printf(DBGSTR("%u\t%s\t%u\t"),
	           task_getroottid_of_s(thread),
	           state == THREAD_STATE_RUNNING
	           ? DBGSTR("running")
	           : state == THREAD_STATE_SLEEPING
	           ? DBGSTR("sleeping")
	           : state == THREAD_STATE_OTHER
	           ? DBGSTR("other")
#ifndef CONFIG_NO_SMP
	           : state == THREAD_STATE_IDLING
	             ? DBGSTR("idling")
	             : DBGSTR("pending")
#else /* !CONFIG_NO_SMP */
	           : DBGSTR("idling")
#endif /* CONFIG_NO_SMP */
	           ,
	           (unsigned int)thread->t_cpu->c_id);
	/* FIXME: Shouldn't access the arch-specific `x86_dbg_exitstate' object.
	 *        Should instead use `' */
	dbg_printf(DBGSTR("%[vinfo:%n(%p)]\t%p"),
	           thread == THIS_TASK ? dbg_getpcreg(DBG_REGLEVEL_EXIT)
	                               : scpustate_getpc(thread->t_sched.s_state),
	           thread == THIS_TASK ? dbg_getspreg(DBG_REGLEVEL_EXIT)
	                               : scpustate_getsp(thread->t_sched.s_state));
	if (thread == &_boottask)
		dbg_print(DBGSTR("\t_boottask"));
	else if (thread == &_bootidle)
		dbg_print(DBGSTR("\t_bootidle"));
	else if (thread == &FORCPU(thread->t_cpu, thiscpu_idle)) {
		dbg_printf(DBGSTR("\t_idle[%u]"), (unsigned int)thread->t_cpu->c_id);
	}
	dbg_putc('\n');
}



LOCAL bool KCALL verify_thread_address_nopid(struct task *p) {
	cpuid_t cpuid;
	for (cpuid = 0; cpuid < cpu_count; ++cpuid) {
		struct task *iter;
		struct cpu *c = cpu_vector[cpuid];
		if (p == &FORCPU(c, thiscpu_idle))
			return true;
		iter = c->c_current;
		do {
			assert(iter->t_cpu == c);
			assert(iter->t_flags & TASK_FRUNNING);
			if (iter == p)
				return true;
		} while ((iter = iter->t_sched.s_running.sr_runnxt) != c->c_current);
		for (iter = c->c_sleeping; iter; iter = iter->t_sched.s_asleep.ss_tmonxt) {
			assert(iter->t_cpu == c);
			assert(!(iter->t_flags & TASK_FRUNNING));
			if (iter == p)
				return true;
		}
#ifndef CONFIG_NO_SMP
		for (iter = c->c_pending; iter != CPU_PENDING_ENDOFCHAIN;
		     iter = iter->t_sched.s_pending.ss_pennxt) {
			assert(iter->t_cpu == c);
			assert(iter->t_flags & TASK_FPENDING);
			assert(!(iter->t_flags & TASK_FRUNNING));
			if (iter == p)
				return true;
		}
#endif /* !CONFIG_NO_SMP */
	}
	return false;
}


LOCAL bool KCALL verify_thread_address(struct task *p) {
	size_t i;
	if (verify_thread_address_nopid(p))
		return true;
	for (i = 0; i <= pidns_root.pn_mask; ++i) {
		struct taskpid *pid;
		pid = pidns_root.pn_list[i].pe_pid;
		if (pid == NULL ||
		    pid == PIDNS_ENTRY_DELETED)
			continue;
		if (wasdestroyed(pid))
			continue;
		if (pid->tp_thread.m_pointer == p)
			return !wasdestroyed(p);
	}
	return false;
}


DEFINE_DEBUG_FUNCTION(
		"lsthread",
		"lsthread\n"
		"\tList all threads running on the system\n",
		argc, argv) {
	cpuid_t cpuid;
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	(void)argv;
	dbg_printf("ID       pid\tstate\tcpu\tpc\tsp\tname\n");
	for (cpuid = 0; cpuid < cpu_count; ++cpuid) {
		struct task *iter;
		struct cpu *c = cpu_vector[cpuid];
		bool did_idle = false;
		iter = c->c_current;
		do {
			assert(iter->t_cpu == c);
			assert(iter->t_flags & TASK_FRUNNING);
			enum_thread(iter, THREAD_STATE_RUNNING);
			if (iter == &FORCPU(c, thiscpu_idle))
				did_idle = true;
		} while ((iter = iter->t_sched.s_running.sr_runnxt) != c->c_current);
		for (iter = c->c_sleeping; iter; iter = iter->t_sched.s_asleep.ss_tmonxt) {
			assert(iter->t_cpu == c);
			assert(!(iter->t_flags & TASK_FRUNNING));
			enum_thread(iter, THREAD_STATE_SLEEPING);
			if (iter == &FORCPU(c, thiscpu_idle))
				did_idle = true;
		}
#ifndef CONFIG_NO_SMP
		for (iter = c->c_pending; iter != CPU_PENDING_ENDOFCHAIN;
		     iter = iter->t_sched.s_pending.ss_pennxt) {
			assert(iter->t_cpu == c);
			assert(iter->t_flags & TASK_FPENDING);
			assert(!(iter->t_flags & TASK_FRUNNING));
			assert(iter != &FORCPU(c, thiscpu_idle));
			enum_thread(iter, THREAD_STATE_PENDING);
		}
#endif /* !CONFIG_NO_SMP */
		if (!did_idle)
			enum_thread(&FORCPU(c, thiscpu_idle), THREAD_STATE_IDLING);
	}
	/* Also enumerate threads found in PID namespaces. */
	{
		size_t i;
		for (i = 0; i <= pidns_root.pn_mask; ++i) {
			struct taskpid *pid;
			pid = pidns_root.pn_list[i].pe_pid;
			if (pid == NULL ||
				pid == PIDNS_ENTRY_DELETED)
				continue;
			if (wasdestroyed(pid))
				continue;
			if (!pid->tp_thread.m_pointer ||
			    wasdestroyed(pid->tp_thread.m_pointer)) {
				dbg_printf(DBGSTR("%p %u\tdead\t?\t?\t?\n"),
				           pid->tp_thread.m_pointer,
				           pid->tp_pids[0]);
				continue;
			}
			if (verify_thread_address_nopid(pid->tp_thread.m_pointer))
				continue; /* Already enumerated. */
			enum_thread(pid->tp_thread.m_pointer, THREAD_STATE_OTHER);
		}
	}
	return 0;
}



PUBLIC ATTR_DBGTEXT struct taskpid *
NOTHROW(KCALL lookup_taskpid)(upid_t pid) {
	REF struct taskpid *result;
	uintptr_t i, perturb;
	i = perturb = pid & pidns_root.pn_mask;
	for (;; PIDNS_HASHNXT(i, perturb)) {
		result = pidns_root.pn_list[i & pidns_root.pn_mask].pe_pid;
		if (result == PIDNS_ENTRY_DELETED)
			continue;
		if unlikely(!result)
			break;
		if (result->tp_pids[pidns_root.pn_indirection] != pid)
			continue;
		/* Found it! (check if it's dead...) */
		if (wasdestroyed(result))
			continue;
		break;
	}
	return result;
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
		pid = lookup_taskpid(pidno);
		if (!pid || !pid->tp_thread.m_pointer ||
		    wasdestroyed(pid->tp_thread.m_pointer)) {
			dbg_printf(DBGSTR("Error: Invalid PID %u\n"), pidno);
			break;
		}
		*presult = pid->tp_thread.m_pointer;
	}	return true;

	/* TODO: Allow selecting by path:
	 *    `c0i'  cpu[0].idle
	 *    `c0c'  cpu[0].current
	 *    `c0s'  cpu[0].sleeping
	 *    `c0s2' cpu[0].sleeping->next
	 *    `bc'   _bootcpu.current
	 *    `bs'   _bootcpu.sleeping
	 *    `bs2'  _bootcpu.sleeping->next */
	/* TODO: Allow selecting by name:
	 *    `b'    _boottask
	 *    `bi'   _bootidle */

	default:
		break;
	}
	return dbg_evaladdr(expr, (uintptr_t *)presult);
}


DEFINE_DEBUG_FUNCTION(
		"thread",
		"thread ADDR\n"
		"\tSet the thread that is being debuged\n"
		"\tWarning: Setting an invalid thread address may triple-fault the kernel\n"
		"\t         Use " DF_WHITE("thread ADDR force") " to override security checks\n",
		argc, argv) {
	struct task *thread;
	if (argc < 2)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	if (!evalthreadexpr(argv[1], &thread))
		return DBG_FUNCTION_INVALID_ARGUMENTS;
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
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_APPS_THREAD_C */
