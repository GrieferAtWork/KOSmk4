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
#ifndef GUARD_MODPROCFS_FILES_SYS_FS_PIPE_MAX_SIZE_C
#define GUARD_MODPROCFS_FILES_SYS_FS_PIPE_MAX_SIZE_C 1
#define _KOS_SOURCE 1 /* snprintf returns size_t */

#include <kernel/compiler.h>

#include <fs/pipe.h>
#include <kernel/except.h>
#include <sched/pid.h>

#include <hybrid/atomic.h>

#include <kos/except-inval.h>

#include <format-printer.h>
#include <stdio.h>
#include <stdlib.h>
#include <unicode.h>

#include "../procfs.h"

DECL_BEGIN

INTERN NONNULL((1)) ssize_t KCALL
ProcFS_Sys_Fs_PipeMaxSize_Print(struct regular_node *__restrict UNUSED(self),
                                pformatprinter printer, void *arg) {
	return format_printf(printer, arg, "%Iu\n",
	                     ATOMIC_READ(pipe_max_bufsize_unprivileged));
}

INTERN NONNULL((1)) void KCALL
ProcFS_Sys_Fs_PipeMaxSize_Write(struct regular_node *__restrict UNUSED(self),
                                USER CHECKED void const *buf,
                                size_t bufsize) {
	USER CHECKED char *endp;
	size_t newsize;
	while (bufsize && unicode_isspace(((char *)buf)[0])) {
		buf = (USER CHECKED char *)buf + 1;
		--bufsize;
	}
	if unlikely(!bufsize)
		goto err_badval;
#if __SIZEOF_SIZE_T__ > 4
	newsize = (size_t)strto64((USER CHECKED char *)buf, &endp, 0);
#else /* __SIZEOF_SIZE_T__ > 4 */
	newsize = (size_t)strto32((USER CHECKED char *)buf, &endp, 0);
#endif /* __SIZEOF_SIZE_T__ <= 4 */
	while (endp < (USER CHECKED char *)buf + bufsize) {
		if (!unicode_isspace(*endp))
			goto err_badval;
		++endp;
	}
	/* Setting it lower than the default limit can't be done, since the default
	 * limit is set regardless of what `pipe_max_bufsize_unprivileged' is set to. */
	if (newsize < RINGBUFFER_DEFAULT_LIMIT)
		goto err_badval;
	ATOMIC_WRITE(pipe_max_bufsize_unprivileged, newsize);
	return;
err_badval:
	THROW(E_INVALID_ARGUMENT_BAD_VALUE,
	      E_INVALID_ARGUMENT_CONTEXT_BAD_INTEGER);
}


DECL_END

#endif /* !GUARD_MODPROCFS_FILES_SYS_FS_PIPE_MAX_SIZE_C */
