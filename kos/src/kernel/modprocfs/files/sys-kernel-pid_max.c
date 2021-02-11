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
#ifndef GUARD_MODPROCFS_FILES_SYS_FS_PIPE_MAX_SIZE_C
#define GUARD_MODPROCFS_FILES_SYS_FS_PIPE_MAX_SIZE_C 1
#define _KOS_SOURCE 1 /* snprintf returns size_t */

#include <kernel/compiler.h>

#include <sched/pid.h>

#include <hybrid/atomic.h>
#include <hybrid/limitcore.h>

#include "../procfs.h"
#include "../util.h"

DECL_BEGIN

INTERN NONNULL((1)) ssize_t KCALL
ProcFS_Sys_Kernel_PidMax_Print(struct regular_node *__restrict UNUSED(self),
                               pformatprinter printer, void *arg) {
	return ProcFS_PrintUPid(printer, arg, ATOMIC_READ(pid_recycle_threshold));
}

INTERN NONNULL((1)) void KCALL
ProcFS_Sys_Kernel_PidMax_Write(struct regular_node *__restrict UNUSED(self),
                               USER CHECKED void const *buf,
                               size_t bufsize) {
	upid_t newvalue;
	/* Don't allow the value to become larger than the max possible
	 * positive, signed PID. While the kernel could deal with going
	 * up to the max unsigned PID internally, various system  calls
	 * that accept pid values have special behavior when the  given
	 * pid becomes negative, such as for example `kill(2)'
	 *
	 * As such, don't raise the limit such that we'd end up with
	 * the kernel generating negative PIDs! */
	newvalue = ProcFS_ParseUPid(buf, bufsize, PIDNS_FIRST_NONRESERVED_PID + 1,
	                            (upid_t)__PRIVATE_MAX_S(__SIZEOF_PID_T__) + 1);
	ATOMIC_WRITE(pid_recycle_threshold, newvalue);
}


DECL_END

#endif /* !GUARD_MODPROCFS_FILES_SYS_FS_PIPE_MAX_SIZE_C */
