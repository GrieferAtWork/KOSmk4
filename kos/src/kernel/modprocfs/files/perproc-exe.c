/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODPROCFS_FILES_PERPROC_EXE_C
#define GUARD_MODPROCFS_FILES_PERPROC_EXE_C 1
#define _KOS_SOURCE 1 /* snprintf returns size_t */

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/mman.h>
#include <kernel/mman/execinfo.h>
#include <sched/pid.h>

#include <stdio.h>

#include "../procfs.h"

DECL_BEGIN

INTERN NONNULL((1)) size_t KCALL
ProcFS_PerProc_Exe_Printer(struct symlink_node *__restrict self,
                           USER CHECKED /*utf-8*/ char *buf,
                           size_t bufsize) {
	upid_t pid;
	REF struct task *thread;
	REF struct mman *mm;
	struct pidns *myns = THIS_PIDNS;
	REF struct directory_entry *exec_dent;
	REF struct path            *exec_path;
	pid  = (upid_t)(self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK);
	thread = pidns_lookup_task(myns, pid);
	{
		FINALLY_DECREF_UNLIKELY(thread);
		mm = task_getmman(thread);
	}
	FINALLY_DECREF_UNLIKELY(mm);
	sync_read(mm);
	exec_dent = xincref(FORMMAN(mm, thismman_execinfo).mei_dent);
	exec_path = xincref(FORMMAN(mm, thismman_execinfo).mei_path);
	sync_endread(mm);
	if unlikely(!exec_dent || !exec_path) {
		xdecref_unlikely(exec_dent);
		xdecref_unlikely(exec_path);
		THROW(E_PROCESS_EXITED, pid);
	}
	FINALLY_DECREF_UNLIKELY(exec_dent);
	FINALLY_DECREF_UNLIKELY(exec_path);
	return path_sprintent(buf,
	                      bufsize,
	                      exec_path,
	                      exec_dent->de_name,
	                      exec_dent->de_namelen);
}


DECL_END

#endif /* !GUARD_MODPROCFS_FILES_PERPROC_EXE_C */
