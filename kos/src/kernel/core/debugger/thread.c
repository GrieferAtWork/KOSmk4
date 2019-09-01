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
#ifndef GUARD_KERNEL_SRC_DEBUGGER_THREAD_C
#define GUARD_KERNEL_SRC_DEBUGGER_THREAD_C 1
#define _KOS_SOURCE 1 /* fuzzy_strcasecmp() */

#include <kernel/compiler.h>

#include <kernel/debugger.h>
#ifndef CONFIG_NO_DEBUGGER
#include <kernel/addr2line.h>
#include <kernel/vm.h>

#include <sched/cpu.h>
#include <sched/task.h>
#include <sched/pid.h>

#include <kos/kernel/cpu-state.h>
#include <asm/intrin.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

DECL_BEGIN

#define THREAD_STATE_RUNNING  0
#define THREAD_STATE_SLEEPING 1
#define THREAD_STATE_IDLING   2
#ifndef CONFIG_NO_SMP
#define THREAD_STATE_PENDING  3
#endif /* !CONFIG_NO_SMP */

PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
enum_thread(struct task *__restrict thread, unsigned int state) {
	dbg_attr_t old_attr = dbg_attr;
	if (thread == THIS_TASK)
		dbg_setfgcolor(DBG_COLOR_GREEN);
	dbg_printf(DBGSTR("%p "), thread);
	dbg_attr = old_attr;
	dbg_printf(DBGSTR("%u\t%s\t%u\t"),
	           task_getroottid_of_s(thread),
	           state == THREAD_STATE_RUNNING
	           ? DBGSTR("running")
	           : state == THREAD_STATE_SLEEPING
	           ? DBGSTR("sleeping")
#ifndef CONFIG_NO_SMP
	           : state == THREAD_STATE_IDLING
	             ? DBGSTR("idling")
	             : DBGSTR("pending")
#else /* !CONFIG_NO_SMP */
	           : DBGSTR("idling")
#endif /* CONFIG_NO_SMP */
	           ,
	           (unsigned int)thread->t_cpu->c_id);
	dbg_printf(DBGSTR("%[vinfo:%n(%p)]\t%p"),
	           thread == debug_original_thread ? FCPUSTATE_PC(dbg_exitstate)
	                                           : SCPUSTATE_PC(*thread->t_sched.s_state),
	           thread == debug_original_thread ? FCPUSTATE_SP(dbg_exitstate)
	                                           : SCPUSTATE_SP(*thread->t_sched.s_state));
	if (thread == &_boottask)
		dbg_print(DBGSTR("\t_boottask"));
	else if (thread == &_bootidle)
		dbg_print(DBGSTR("\t_bootidle"));
	else if (thread == &FORCPU(thread->t_cpu, _this_idle)) {
		dbg_printf(DBGSTR("\t_idle[%u]"), (unsigned int)thread->t_cpu->c_id);
	}
	dbg_putc('\n');
}


DEFINE_DEBUG_FUNCTION(
		"lsthread",
		"lsthread\n"
		"\tList all threads running on the system\n",
		argc, argv) {
	cpuid_t cpuid;
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
			if (iter == &FORCPU(c, _this_idle))
				did_idle = true;
		} while ((iter = iter->t_sched.s_running.sr_runnxt) != c->c_current);
		for (iter = c->c_sleeping; iter; iter = iter->t_sched.s_asleep.ss_tmonxt) {
			assert(iter->t_cpu == c);
			assert(!(iter->t_flags & TASK_FRUNNING));
			enum_thread(iter, THREAD_STATE_SLEEPING);
			if (iter == &FORCPU(c, _this_idle))
				did_idle = true;
		}
#ifndef CONFIG_NO_SMP
		for (iter = c->c_pending; iter != CPU_PENDING_ENDOFCHAIN;
		     iter = iter->t_sched.s_pending.ss_pennxt) {
			assert(iter->t_cpu == c);
			assert(iter->t_flags & TASK_FPENDING);
			assert(!(iter->t_flags & TASK_FRUNNING));
			assert(iter != &FORCPU(c, _this_idle));
			enum_thread(iter, THREAD_STATE_PENDING);
		}
#endif /* !CONFIG_NO_SMP */
		if (!did_idle)
			enum_thread(&FORCPU(c, _this_idle), THREAD_STATE_IDLING);

	}
	return 0;
}

LOCAL bool KCALL verify_thread_address(struct task *p) {
	cpuid_t cpuid;
	for (cpuid = 0; cpuid < cpu_count; ++cpuid) {
		struct task *iter;
		struct cpu *c = cpu_vector[cpuid];
		iter = c->c_current;
		if (iter == &FORCPU(c, _this_idle))
			return true;
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


DEFINE_DEBUG_FUNCTION(
		"thread",
		"thread ADDR\n"
		"\tSet the thread that is being debuged\n",
		argc, argv) {
	struct task *thread;
	if (argc < 2)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	if (sscanf(argv[1], DBGSTR("%lx"), &thread) != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	if (!verify_thread_address(thread) &&
	    (argc < 3 || strcmp(argv[2], DBGSTR("force")) != 0)) {
		dbg_printf(DBGSTR("Invalid thread %p (use `thread %p force' to override)\n"), thread, thread);
		return 1;
	}
	dbg_impersonate_thread(thread);
	return 0;
}


DECL_END
#endif /* !CONFIG_NO_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_THREAD_C */
