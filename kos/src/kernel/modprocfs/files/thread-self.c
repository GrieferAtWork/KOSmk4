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
#ifndef GUARD_MODPROCFS_FILES_THREAD_SELF_C
#define GUARD_MODPROCFS_FILES_THREAD_SELF_C 1
#define _KOS_SOURCE 1 /* snprintf returns size_t */

#include <kernel/compiler.h>

#include <sched/pid.h>

#include <stdio.h>

#include "../procfs.h"

DECL_BEGIN

INTERN NONNULL((1)) size_t KCALL
ProcFS_ThreadSelf_Printer(struct symlink_node *__restrict UNUSED(self),
                          USER CHECKED /*utf-8*/ char *buf,
                          size_t bufsize) {
	upid_t mypid = task_getpid_s();
	upid_t mytid = task_gettid_s();
	return snprintf(buf, bufsize, "%u/task/%u",
	                (unsigned int)mypid,
	                (unsigned int)mytid);
}


DECL_END

#endif /* !GUARD_MODPROCFS_FILES_THREAD_SELF_C */
