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
#ifndef GUARD_MODPROCFS_FILES_SYS_KERNEL_SCHED_CHILD_RUNS_FIRST_C
#define GUARD_MODPROCFS_FILES_SYS_KERNEL_SCHED_CHILD_RUNS_FIRST_C 1
#define _KOS_SOURCE 1 /* snprintf returns size_t */

#include <kernel/compiler.h>

#include <sched/task.h>

#include <hybrid/atomic.h>

#include <kos/except-inval.h>

#include <unicode.h>

#include "../procfs.h"
#include "../util.h"

DECL_BEGIN

INTERN NONNULL((1)) ssize_t KCALL
ProcFS_Sys_Kernel_SchedChildRunsFirst_Print(struct regular_node *__restrict UNUSED(self),
                                            pformatprinter printer, void *arg) {
	return ProcFS_PrintBool(printer, arg, (task_start_default_flags & TASK_START_FHIGHPRIO) != 0);
}

INTERN NONNULL((1)) void KCALL
ProcFS_Sys_Kernel_SchedChildRunsFirst_Write(struct regular_node *__restrict UNUSED(self),
                                            USER CHECKED void const *buf,
                                            size_t bufsize) {
	bool mode;
	mode = ProcFS_ParseBool(buf, bufsize);
	if (mode) {
		ATOMIC_FETCHOR(task_start_default_flags, TASK_START_FHIGHPRIO);
	} else {
		ATOMIC_FETCHAND(task_start_default_flags, ~TASK_START_FHIGHPRIO);
	}
}


DECL_END

#endif /* !GUARD_MODPROCFS_FILES_SYS_KERNEL_SCHED_CHILD_RUNS_FIRST_C */
