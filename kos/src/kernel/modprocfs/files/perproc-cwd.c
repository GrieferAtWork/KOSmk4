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
#ifndef GUARD_MODPROCFS_FILES_PERPROC_CWD_C
#define GUARD_MODPROCFS_FILES_PERPROC_CWD_C 1
#define _KOS_SOURCE 1 /* snprintf returns size_t */

#include <kernel/compiler.h>
#include <sched/pid.h>
#include <fs/vfs.h>
#include <stdio.h>

#include "../procfs.h"

DECL_BEGIN

INTERN NONNULL((1)) size_t KCALL
ProcFS_PerProc_FsLink_Printer(struct symlink_node *__restrict self,
                              USER CHECKED /*utf-8*/ char *buf,
                              size_t bufsize,
                              ptrdiff_t offsetof_path_from_fs) {
	size_t result;
	upid_t pid;
	struct fs *threadfs;
	REF struct task *thread;
	REF struct path *pth;
	pid    = (upid_t)(self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK);
	thread = pidns_trylookup_task(THIS_PIDNS, pid);
	if unlikely(!thread) {
err:
		return snprintf(buf, bufsize, "/");
	}
	{
		FINALLY_DECREF_UNLIKELY(thread);
		threadfs = FORTASK(thread, _this_fs);
		if unlikely(!threadfs)
			goto err;
		sync_read(&threadfs->f_pathlock);
		pth = incref(*(REF struct path **)((byte_t *)threadfs +
		                                   offsetof_path_from_fs));
		sync_endread(&threadfs->f_pathlock);
	}
	{
		FINALLY_DECREF_UNLIKELY(pth);
		result = path_sprint(buf, bufsize, pth);
	}
	return result;
}

INTERN NONNULL((1)) size_t KCALL
ProcFS_PerProc_Cwd_Printer(struct symlink_node *__restrict self,
                           USER CHECKED /*utf-8*/ char *buf,
                           size_t bufsize) {
	return ProcFS_PerProc_FsLink_Printer(self, buf, bufsize,
	                                     offsetof(struct fs, f_cwd));
}

INTERN NONNULL((1)) size_t KCALL
ProcFS_PerProc_Root_Printer(struct symlink_node *__restrict self,
                            USER CHECKED /*utf-8*/ char *buf,
                            size_t bufsize) {
	return ProcFS_PerProc_FsLink_Printer(self, buf, bufsize,
	                                     offsetof(struct fs, f_root));
}


DECL_END

#endif /* !GUARD_MODPROCFS_FILES_PERPROC_CWD_C */
