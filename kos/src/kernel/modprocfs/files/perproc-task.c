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
#ifndef GUARD_MODPROCFS_FILES_PERPROC_TASK_C
#define GUARD_MODPROCFS_FILES_PERPROC_TASK_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/block.h>
#include <dev/char.h>
#include <fs/file.h>
#include <fs/node.h>
#include <fs/pipe.h>
#include <fs/vfs.h>
#include <kernel/handle.h>
#include <sched/enum.h>
#include <sched/eventfd.h>
#include <sched/pid.h>
#include <sched/signalfd.h>

#include <hybrid/atomic.h>

#include <kos/kernel/handle.h>

#include <assert.h>
#include <format-printer.h>
#include <stdio.h>

#include "../procfs.h"

DECL_BEGIN


PRIVATE NONNULL((1, 2)) REF struct directory_entry *KCALL
ProcFS_PerProc_Task_Lookup(struct directory_node *__restrict self,
                           CHECKED USER /*utf-8*/ char const *__restrict name,
                           u16 namelen, uintptr_t UNUSED(hash), fsmode_t UNUSED(mode))
		THROWS(E_SEGFAULT, E_FSERROR_FILE_NOT_FOUND,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	REF struct directory_entry *result;
	upid_t pidno, leader_pid;
	size_t i;
	char ch;
	/* Evaluate running process PIDs */
	if unlikely(namelen == 0)
		goto notapid;
	ch = ATOMIC_READ(name[0]);
	if unlikely(ch < '1' || ch > '9')
		goto notapid;
	pidno = (upid_t)(ch - '0');
	for (i = 1; i < namelen; ++i) {
		ch = ATOMIC_READ(name[i]);
		if unlikely(ch < '0' || ch > '9')
			goto notapid;
		pidno *= 10;
		pidno += (upid_t)(ch - '0');
	}
	leader_pid = (upid_t)(self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK);
	/* Simple case that's always allowed (s.a. `/proc/thread-self') */
	if (pidno != leader_pid) {
		REF struct task *thread;
		upid_t real_leader_pidno;
		thread = pidns_trylookup_task(THIS_PIDNS, pidno);
		if unlikely(!thread)
			goto notapid;
		/* Verify that the `thread' belongs to `leader_pid' */
		real_leader_pidno = task_getpid_of(thread);
		decref_unlikely(thread);
		if (real_leader_pidno != leader_pid)
			goto notapid;
	}
	result = directory_entry_alloc(namelen);
#ifdef NDEBUG
	sprintf(result->de_name, "%u", (unsigned int)pidno);
#else /* NDEBUG */
	{
		size_t temp;
		temp = sprintf(result->de_name, "%u", (unsigned int)pidno);
		assert(temp == namelen);
	}
#endif /* !NDEBUG */
	/* NOTE: We can't actually trust user-space that `hash' is valid, since
	 *       the user may have changed the string in the mean time... */
	result->de_hash = directory_entry_hash(result->de_name, namelen);
	result->de_ino  = PROCFS_INOMAKE_PERPROC(pidno, PROCFS_PERPROC_ROOT);
	result->de_type = DT_DIR;
	return result;
notapid:
	return NULL;
}

PRIVATE NONNULL((1, 2)) void KCALL
ProcFS_PerProc_Task_Enum(struct directory_node *__restrict self,
                         directory_enum_callback_t callback,
                         void *arg)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	ProcFS_EnumProcessCallback_Data data;
	struct pidns *ns;
	REF struct task *leader;
	upid_t leader_pid;
	leader_pid = (upid_t)(self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK);
	leader     = pidns_trylookup_task(THIS_PIDNS, leader_pid);
	if likely(leader) {
		FINALLY_DECREF_UNLIKELY(leader);
		/* Enumerate threads of `leader' */
		ns              = THIS_PIDNS;
		data.epc_cb     = callback;
		data.epc_arg    = arg;
		data.epc_ns_ind = ns->pn_indirection;
		/* NOTE: Only enumerate worker threads (aka. anything but `leader' itself)
		 *       This is required to prevent recursive directory scanners from ending
		 *       up in an infinite loop `/proc/1/task/1/task/1/task/1/task/1/task/...'
		 *
		 * Note though that you can still lookup `/proc/1/task/1' (similar to how you
		 * can lookup /proc/[tid], rather than only /proc/[pid], although /proc/[tid]
		 * is hidden, and you'll have to guess, or know a valid tid).
		 *
		 * Linux solves this a bit differently, in that `/proc/1/task/1' simply doesn't
		 * contain another `task' sub-directory, but I feel like this is just as valid
		 * a solution. */
		task_enum_process_worker_threads(&ProcFS_EnumProcessCallback,
		                                 &data, leader);
	}
}

INTERN struct inode_type ProcFS_PerProc_Task_Type = {
	/* .it_fini = */ NULL,
	/* .it_attr = */ {
		/* .a_loadattr = */ NULL,
		/* .a_saveattr = */ NULL,
		/* .a_maskattr = */ NULL,
		/* .a_stat     = */ &ProcFS_PerProc_StatInode,
	},
	/* .it_file = */ {
	},
	{
		/* .it_directory = */ {
			/* .d_readdir = */ NULL,
			/* .d_oneshot = */ {
				/* .o_lookup = */ &ProcFS_PerProc_Task_Lookup,
				/* .o_enum   = */ &ProcFS_PerProc_Task_Enum,
			}
		}
	}
};

DECL_END

#endif /* !GUARD_MODPROCFS_FILES_PERPROC_TASK_C */
