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
#ifndef GUARD_MODGDB_ENUM_C
#define GUARD_MODGDB_ENUM_C 1

#include <kernel/compiler.h>
#include <kernel/vm.h>
#include <sched/cpu.h>
#include <sched/task.h>
#include <sched/pid.h>
#include <assert.h>

#include "gdb.h"

DECL_BEGIN

#define ENUM_THREADS_ST_INITIAL  0
#define ENUM_THREADS_ST_SIBLING  1
#define ENUM_THREADS_ST_IDLES    2
#define ENUM_THREADS_ST_RUNNING  3
#define ENUM_THREADS_ST_SLEEPING 4
#define ENUM_THREADS_ST_PENDING  5

#if 1
#define SHOULD_ENUMERATE_ALL_THREADS  (GDB_RemoteFeatures & GDB_REMOTEFEATURE_ATTACHED)
#elif 1
#define SHOULD_ENUMERATE_ALL_THREADS  1
#elif 1
#define SHOULD_ENUMERATE_ALL_THREADS  (!(GDB_RemoteFeatures & GDB_REMOTEFEATURE_MULTIPROCESS))
#else
#define SHOULD_ENUMERATE_ALL_THREADS  0
#endif


/* Initialize a thread/process enumerator. */
INTERN NONNULL((1)) void
NOTHROW(FCALL GDBEnumThreads_Init)(GDBEnumThreadsIterator *__restrict self) {
	self->eti_state = ENUM_THREADS_ST_INITIAL;
	if (SHOULD_ENUMERATE_ALL_THREADS) {
		self->eti_next = incref(&_bootidle);
	} else {
		self->eti_next = incref(GDB_GetCurrentProcess());
	}
}

INTERN NONNULL((1)) void
NOTHROW(FCALL GDBEnumThreads_Fini)(GDBEnumThreadsIterator *__restrict self) {
	if (self->eti_next)
		decref(self->eti_next);
}

PRIVATE void
NOTHROW(FCALL enumend)(GDBEnumThreadsIterator *__restrict self) {
	self->eti_next = NULL;
}

#ifndef CONFIG_NO_SMP
PRIVATE void
NOTHROW(FCALL enumbegin_pending)(GDBEnumThreadsIterator *__restrict self) {
	struct task *thread;
	self->eti_state2 = 0;
	GDB_SuspendAllOtherCPUsNow(); /* XXX: This is kind-of hacky... */
again:
	thread = cpu_vector[self->eti_state2]->c_pending;
	if (thread == &FORCPU(cpu_vector[self->eti_state2], _this_idle))
		thread = thread->t_sched.s_pending.ss_pennxt;
	assert(thread != &FORCPU(cpu_vector[self->eti_state2], _this_idle));
	if (!thread || thread == CPU_PENDING_ENDOFCHAIN) {
		if (++self->eti_state2 < cpu_count)
			goto again;
		enumend(self);
		return;
	}
	self->eti_next  = incref(thread);
	self->eti_state = ENUM_THREADS_ST_PENDING;
}
#else /* !CONFIG_NO_SMP */
#define enumbegin_pending(self) enumend(self)
#endif /* CONFIG_NO_SMP */

PRIVATE void
NOTHROW(FCALL enumbegin_sleeping)(GDBEnumThreadsIterator *__restrict self) {
	struct task *thread;
	self->eti_state2 = 0;
	GDB_SuspendAllOtherCPUsNow(); /* XXX: This is kind-of hacky... */
again:
	thread = cpu_vector[self->eti_state2]->c_sleeping;
	if (thread == &FORCPU(cpu_vector[self->eti_state2], _this_idle))
		thread = thread->t_sched.s_asleep.ss_tmonxt;
	assert(thread != &FORCPU(cpu_vector[self->eti_state2], _this_idle));
	if (!thread) {
		if (++self->eti_state2 < cpu_count)
			goto again;
		enumbegin_pending(self);
		return;
	}
	self->eti_next  = incref(thread);
	self->eti_state = ENUM_THREADS_ST_SLEEPING;
}

PRIVATE void
NOTHROW(FCALL enumbegin_running)(GDBEnumThreadsIterator *__restrict self) {
	struct task *thread;
	self->eti_state2 = 0;
	GDB_SuspendAllOtherCPUsNow(); /* XXX: This is kind-of hacky... */
again:
	thread = cpu_vector[self->eti_state2]->c_current;
	if (thread == &FORCPU(cpu_vector[self->eti_state2], _this_idle)) {
		thread = thread->t_sched.s_running.sr_runnxt;
		if (thread == cpu_vector[self->eti_state2]->c_current) {
			if (++self->eti_state2 < cpu_count)
				goto again;
			enumbegin_sleeping(self);
			return;
		}
	}
	self->eti_next  = incref(thread);
	self->eti_state = ENUM_THREADS_ST_RUNNING;
}

PRIVATE void
NOTHROW(FCALL enumbegin_idles)(GDBEnumThreadsIterator *__restrict self) {
	if (cpu_count < 2)
		enumbegin_running(self);
	else {
		self->eti_next   = incref(&FORCPU(cpu_vector[1], _this_idle));
		self->eti_state  = ENUM_THREADS_ST_IDLES;
		self->eti_state2 = 2;
	}
}

PRIVATE WUNUSED bool
NOTHROW(FCALL isakernthread)(struct task *__restrict self) {
	if (self->t_flags & TASK_FKERNTHREAD)
		return true;
	if (self->t_vm == &vm_kernel)
		return true;
	return false;
}



/* Yield the next thread/process from a given thread/process enumerator.
 * NOTE: In the case of `GDBEnumProcess_Next()', only processes leaders are enumerated,
 *       when `&_bootidle' is returned as the placeholder for a leader for the kernel
 *       core process.
 * @return: NULL: All threads/processes have already been enumerated. */
INTERN WUNUSED NONNULL((1)) REF struct task *
NOTHROW(FCALL GDBEnumThreads_Next)(GDBEnumThreadsIterator *__restrict self) {
	REF struct task *result;
	result = self->eti_next;
	if (result) {
again_switch:
		switch (self->eti_state) {

		case ENUM_THREADS_ST_INITIAL:
			if (result == &_bootidle) {
				/* Enumerate kernel threads. */
				enumbegin_idles(self);
			} else {
				struct taskpid *threads;
				assert(result == task_getprocess_of(result));
				if (!GDB_DidSuspendOtherCPUs)
					sync_read(&FORTASK(result, _this_taskgroup).tg_proc_threads_lock);
				self->eti_next = NULL;
				for (threads = FORTASK(result, _this_taskgroup).tg_proc_threads;
				     threads; threads = threads->tp_siblings.ln_next) {
					self->eti_next = taskpid_gettask(threads);
					if (self->eti_next)
						break;
				}
				if (!GDB_DidSuspendOtherCPUs)
					sync_endread(&FORTASK(result, _this_taskgroup).tg_proc_threads_lock);
				self->eti_state = ENUM_THREADS_ST_SIBLING;
			}
			goto done;

		case ENUM_THREADS_ST_SIBLING: {
			struct taskpid *threads;
			threads = FORTASK(result, _this_taskpid);
			self->eti_next = NULL;
			if (threads) {
				if (!GDB_DidSuspendOtherCPUs)
					sync_read(&FORTASK(task_getprocess_of(result), _this_taskgroup).tg_proc_threads_lock);
				for (;;) {
					threads = threads->tp_siblings.ln_next;
					if (!threads)
						break;
					self->eti_next = taskpid_gettask(threads);
					if (self->eti_next)
						break;
				}
				if (!GDB_DidSuspendOtherCPUs)
					sync_endread(&FORTASK(task_getprocess_of(result), _this_taskgroup).tg_proc_threads_lock);
			}
			goto done;
		}	break;

		case ENUM_THREADS_ST_IDLES:
			if (self->eti_state2 < cpu_count) {
				self->eti_next = incref(&FORCPU(cpu_vector[self->eti_state2], _this_idle));
				++self->eti_state2;
				break;
			}
			enumbegin_running(self);
			break;

		case ENUM_THREADS_ST_RUNNING:
			do {
				assert(self->eti_next->t_cpu == cpu_vector[self->eti_state2]);
				self->eti_next = self->eti_next->t_sched.s_running.sr_runnxt;
				if (self->eti_next == cpu_vector[self->eti_state2]->c_current) {
					if (++self->eti_state2 < cpu_count) {
						self->eti_next = cpu_vector[self->eti_state2]->c_current;
						goto again_running;
					}
					enumbegin_sleeping(self);
					goto done;
				}
again_running:
				;
			} while (self->eti_next == &FORCPU(cpu_vector[self->eti_state2], _this_idle));
			incref(self->eti_next);
			break;

		case ENUM_THREADS_ST_SLEEPING:
			do {
				assert(self->eti_next->t_cpu == cpu_vector[self->eti_state2]);
				self->eti_next = self->eti_next->t_sched.s_asleep.ss_tmonxt;
				if (self->eti_next == NULL) {
					while (++self->eti_state2 < cpu_count) {
						self->eti_next = cpu_vector[self->eti_state2]->c_sleeping;
						if (self->eti_next != NULL)
							goto again_sleeping;
					}
					enumbegin_pending(self);
					goto done;
				}
again_sleeping:
				;
			} while (self->eti_next == &FORCPU(cpu_vector[self->eti_state2], _this_idle));
			incref(self->eti_next);
			break;

#ifndef CONFIG_NO_SMP
		case ENUM_THREADS_ST_PENDING:
			do {
				assert(self->eti_next->t_cpu == cpu_vector[self->eti_state2]);
				self->eti_next = self->eti_next->t_sched.s_pending.ss_pennxt;
				if (self->eti_next == NULL) {
					while (++self->eti_state2 < cpu_count) {
						self->eti_next = cpu_vector[self->eti_state2]->c_pending;
						if (self->eti_next != NULL &&
						    self->eti_next != CPU_PENDING_ENDOFCHAIN)
							goto again_pending;
					}
					self->eti_state = 0;
					self->eti_next  = NULL;
					goto done;
				}
again_pending:
				;
			} while (self->eti_next == &FORCPU(cpu_vector[self->eti_state2], _this_idle));
			incref(self->eti_next);
			break;
#endif /* !CONFIG_NO_SMP */

		default:
			self->eti_next = NULL;
			break;
		}
		/* Check if the thread is a kernel-thread */
		if (!SHOULD_ENUMERATE_ALL_THREADS &&
		    !isakernthread(result)) {
			decref_unlikely(result);
			goto again_switch;
		}
	}
done:
	return result;
}



INTERN NONNULL((1)) void
NOTHROW(FCALL GDBEnumProcess_Init)(GDBEnumProcessIterator *__restrict self) {
	self->epi_index = 0;
}

INTERN NONNULL((1)) void
NOTHROW(FCALL GDBEnumProcess_Fini)(GDBEnumProcessIterator *__restrict self) {
	(void)self;
	/* nothing (for now) */
}

INTERN WUNUSED NONNULL((1)) REF struct task *
NOTHROW(FCALL GDBEnumProcess_Next)(GDBEnumProcessIterator *__restrict self) {
	REF struct task *result = NULL;
	/* Simply enumerate all processes within the  */
	if (!GDB_DidSuspendOtherCPUs)
		sync_read(&pidns_root);
	if (self->epi_index == pidns_root.pn_mask + 1) {
		/* Special case: Enumerate the kernel ~process~ (if you want to call it that...) */
		++self->epi_index;
		result = incref(&_bootidle);
	} else {
		while (self->epi_index <= pidns_root.pn_mask) {
			struct taskpid *pid;
			pid = pidns_root.pn_list[self->epi_index++].pe_pid;
			if (pid == NULL || pid == PIDNS_ENTRY_DELETED)
				continue;
			result = taskpid_gettask(pid);
			if (!result)
				continue;
			if (!task_isprocessleader_p(result)) {
				decref_unlikely(result);
				continue;
			}
			/* Found another process! */
			break;
		}
	}
	if (!GDB_DidSuspendOtherCPUs)
		sync_endread(&pidns_root);
	return result;
}


DECL_END

#endif /* !GUARD_MODGDB_ENUM_C */
