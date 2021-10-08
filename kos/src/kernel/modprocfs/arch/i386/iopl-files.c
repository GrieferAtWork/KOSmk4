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
#ifndef GUARD_MODPROCFS_ARCH_I386_IOPL_FILES_C
#define GUARD_MODPROCFS_ARCH_I386_IOPL_FILES_C 1
#define _KOS_SOURCE 1 /* snprintf returns size_t */

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/except.h>
#include <sched/cred.h>
#include <sched/pid.h>
#include <sched/x86/eflags-mask.h>
#include <sched/x86/iopl.h>

#include <hybrid/atomic.h>

#include <asm/cpu-flags.h>
#include <kos/except/reason/inval.h>

#include <string.h>
#include <unicode.h>

#include "../../procfs.h"
#include "../../util.h"

DECL_BEGIN

PRIVATE NONNULL((1)) void KCALL
KeepIopl_Write(USER CHECKED void const *buf, size_t bufsize, bool *pvalue) {
	bool new_value;
	new_value = ProcFS_ParseBool(buf, bufsize);
	for (;;) {
		bool old_value;
		old_value = ATOMIC_READ(*pvalue);
		if (old_value == new_value)
			break; /* Nothing to do here! */
		/* Need sysadmin to change the value. */
		cred_require_sysadmin();
		/* Need hwio to turn one of these on! */
		if (new_value)
			require(CAP_SYS_RAWIO);
		/* Change the value. */
		if (ATOMIC_CMPXCH_WEAK(*pvalue, old_value, new_value))
			break;
	}
}


/* /proc/sys/x86/keepiopl/fork */
INTERN NONNULL((1)) ssize_t KCALL
ProcFS_Sys_X86_KeepIopl_Fork_Print(struct regular_node *__restrict UNUSED(self),
                                   pformatprinter printer, void *arg) {
	return ProcFS_PrintBool(printer, arg, x86_iopl_keep_after_fork);
}

INTERN NONNULL((1)) void KCALL
ProcFS_Sys_X86_KeepIopl_Fork_Write(struct regular_node *__restrict UNUSED(self),
                                   USER CHECKED void const *buf,
                                   size_t bufsize) {
	KeepIopl_Write(buf, bufsize, &x86_iopl_keep_after_fork);
}


/* /proc/sys/x86/keepiopl/clone */
INTERN NONNULL((1)) ssize_t KCALL
ProcFS_Sys_X86_KeepIopl_Clone_Print(struct regular_node *__restrict UNUSED(self),
                                    pformatprinter printer, void *arg) {
	return ProcFS_PrintBool(printer, arg, x86_iopl_keep_after_clone);
}

INTERN NONNULL((1)) void KCALL
ProcFS_Sys_X86_KeepIopl_Clone_Write(struct regular_node *__restrict UNUSED(self),
                                    USER CHECKED void const *buf,
                                    size_t bufsize) {
	KeepIopl_Write(buf, bufsize, &x86_iopl_keep_after_clone);
}


/* /proc/sys/x86/keepiopl/exec */
INTERN NONNULL((1)) ssize_t KCALL
ProcFS_Sys_X86_KeepIopl_Exec_Print(struct regular_node *__restrict UNUSED(self),
                                   pformatprinter printer, void *arg) {
	bool keep;
	union x86_user_eflags_mask_union mask;
	mask.uem_word = atomic64_read(&x86_exec_eflags_mask);
	keep = (mask.uem_mask & EFLAGS_IOPLMASK) == EFLAGS_IOPLMASK;
	return ProcFS_PrintBool(printer, arg, keep);
}

INTERN NONNULL((1)) void KCALL
ProcFS_Sys_X86_KeepIopl_Exec_Write(struct regular_node *__restrict UNUSED(self),
                                   USER CHECKED void const *buf,
                                   size_t bufsize) {
	bool keep;
	union x86_user_eflags_mask_union oldmask, newmask;
	KeepIopl_Write(buf, bufsize, &keep);
	for (;;) {
		oldmask.uem_word = atomic64_read(&x86_exec_eflags_mask);
		newmask.uem_word = oldmask.uem_word;
		newmask.uem_mask &= ~EFLAGS_IOPLMASK;
		if (keep)
			newmask.uem_mask |= EFLAGS_IOPLMASK;
		if (oldmask.uem_mask == newmask.uem_mask)
			break; /* Unchanged. */
		if (atomic64_cmpxch(&x86_exec_eflags_mask, oldmask.uem_word, newmask.uem_word))
			break;
	}
}



/* /proc/[PID]/x86/iopl */
INTERN NONNULL((1)) ssize_t KCALL
ProcFS_PerProc_X86_Iopl_Print(struct regular_node *__restrict self,
                              pformatprinter printer, void *arg) {
	upid_t pid;
	unsigned int iopl;
	REF struct task *thread;
	pid    = (upid_t)(self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK);
	thread = pidns_lookup_task(THIS_PIDNS, pid);
	{
		FINALLY_DECREF_UNLIKELY(thread);
		iopl = x86_getiopl(thread);
	}
	return ProcFS_PrintUInt(printer, arg, iopl);
}

INTERN NONNULL((1)) void KCALL
ProcFS_PerProc_X86_Iopl_Write(struct regular_node *__restrict self,
                              USER CHECKED void const *buf, size_t bufsize) {
	upid_t pid;
	REF struct task *thread;
	unsigned int new_iopl;
	new_iopl = ProcFS_ParseUInt(buf, bufsize, 0, 3);
	pid    = (upid_t)(self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK);
	thread = pidns_lookup_task(THIS_PIDNS, pid);
	{
		FINALLY_DECREF_UNLIKELY(thread);
		x86_setiopl(thread, new_iopl, /* check_creds: */ true);
	}
}



DECL_END

#endif /* !GUARD_MODPROCFS_ARCH_I386_IOPL_FILES_C */
