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
#include <sched/cpu.h>
#include <sched/task.h>
#include <sched/pid.h>
#include <assert.h>

#include "gdb.h"

DECL_BEGIN

#define ENUM_THREADS_ST_INITIAL 0
#define ENUM_THREADS_ST_SIBLING 1

/* Initialize a thread/process enumerator. */
INTERN NONNULL((1)) void
NOTHROW(FCALL GDBEnumThreads_Init)(GDBEnumThreadsIterator *__restrict self) {
	self->eti_state = ENUM_THREADS_ST_INITIAL;
	self->eti_next  = incref(GDB_GetCurrentProcess());
}

INTERN NONNULL((1)) void
NOTHROW(FCALL GDBEnumThreads_Fini)(GDBEnumThreadsIterator *__restrict self) {
	xdecref(self->eti_next);
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
		switch (self->eti_state) {

		case ENUM_THREADS_ST_INITIAL:
			if (result == &_bootidle) {
				/* TODO: Enumerate kernel threads. */
				self->eti_next = NULL;
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
			break;

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
		}	break;

		default:
			self->eti_next = NULL;
			break;
		}
	}
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
