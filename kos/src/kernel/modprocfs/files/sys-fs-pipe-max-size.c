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
#ifndef GUARD_MODPROCFS_FILES_SYS_FS_PIPE_MAX_SIZE_C
#define GUARD_MODPROCFS_FILES_SYS_FS_PIPE_MAX_SIZE_C 1
#define _KOS_SOURCE 1 /* snprintf returns size_t */

#include <kernel/compiler.h>

#include <fs/pipe.h>
#include <kernel/except.h>
#include <sched/pid.h>

#include <hybrid/atomic.h>

#include <kos/except/inval.h>

#include <format-printer.h>
#include <stdio.h>
#include <stdlib.h>
#include <unicode.h>

#include "../procfs.h"
#include "../util.h"

DECL_BEGIN

INTERN NONNULL((1)) ssize_t KCALL
ProcFS_Sys_Fs_PipeMaxSize_Print(struct regular_node *__restrict UNUSED(self),
                                pformatprinter printer, void *arg) {
	return ProcFS_PrintSize(printer, arg, ATOMIC_READ(pipe_max_bufsize_unprivileged));
}

INTERN NONNULL((1)) void KCALL
ProcFS_Sys_Fs_PipeMaxSize_Write(struct regular_node *__restrict UNUSED(self),
                                USER CHECKED void const *buf,
                                size_t bufsize) {
	size_t newsize;
	/* Setting it lower than the default limit can't be done, since the default
	 * limit is set regardless of what `pipe_max_bufsize_unprivileged' is set to. */
	newsize = ProcFS_ParseSize(buf, bufsize, RINGBUFFER_DEFAULT_LIMIT, (size_t)-1);
	ATOMIC_WRITE(pipe_max_bufsize_unprivileged, newsize);
}


DECL_END

#endif /* !GUARD_MODPROCFS_FILES_SYS_FS_PIPE_MAX_SIZE_C */
