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
#ifndef GUARD_MODPROCFS_FILES_PERPROC_ENVIRON_C
#define GUARD_MODPROCFS_FILES_PERPROC_ENVIRON_C 1

#include <kernel/compiler.h>

#include <kernel/mman.h>
#include <kernel/mman/execinfo.h>
#include <kernel/mman/rw.h>
#include <kernel/user.h>
#include <sched/pid.h>

#include <hybrid/overflow.h>

#include <compat/config.h>
#include <kos/exec/peb.h>

#include <format-printer.h>
#include <stddef.h>
#include <string.h>

#include "../procfs.h"

#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/exec/peb.h>
#include <compat/kos/types.h>
#include <compat/pointer.h>
#endif /* __ARCH_HAVE_COMPAT */

#include <kernel/printk.h>

DECL_BEGIN

INTDEF NONNULL((1, 2)) ssize_t KCALL
ProcFS_PrintUserSpaceStringArray(struct mman *__restrict mm, pformatprinter printer, void *arg,
                                 size_t strc, char const *USER UNCHECKED const *USER CHECKED strv);
#ifdef __ARCH_HAVE_COMPAT
INTDEF NONNULL((1, 2)) ssize_t KCALL
ProcFS_PrintCompatUserSpaceStringArray(struct mman *__restrict mm, pformatprinter printer, void *arg,
                                       size_t strc, compat_uintptr_t USER UNCHECKED const *USER CHECKED strv);
#endif /* __ARCH_HAVE_COMPAT */


struct _peb_environ_buffer {
#if OFFSET_PROCESS_PEB_ENVC < OFFSET_PROCESS_PEB_ENVP
	size_t pp_envc;
#if (OFFSET_PROCESS_PEB_ENVC + __SIZEOF_SIZE_T__) < OFFSET_PROCESS_PEB_ENVP
	byte_t __pp_pad[OFFSET_PROCESS_PEB_ENVP - (OFFSET_PROCESS_PEB_ENVC + __SIZEOF_SIZE_T__)];
#elif (OFFSET_PROCESS_PEB_ENVC + __SIZEOF_SIZE_T__) > OFFSET_PROCESS_PEB_ENVP
#error "Invalid offsets"
#endif /* ... */
	char const *USER UNCHECKED const *USER UNCHECKED pp_envp;
#else /* OFFSET_PROCESS_PEB_ENVC < OFFSET_PROCESS_PEB_ENVP */
	char const *USER UNCHECKED const *USER UNCHECKED pp_envp;
#if (OFFSET_PROCESS_PEB_ENVP + __SIZEOF_SIZE_T__) < OFFSET_PROCESS_PEB_ENVC
	byte_t __pp_pad[OFFSET_PROCESS_PEB_ENVC - (OFFSET_PROCESS_PEB_ENVP + __SIZEOF_SIZE_T__)];
#elif (OFFSET_PROCESS_PEB_ENVP + __SIZEOF_SIZE_T__) > OFFSET_PROCESS_PEB_ENVC
#error "Invalid offsets"
#endif /* ... */
	size_t pp_envc;
#endif /* OFFSET_PROCESS_PEB_ENVC >= OFFSET_PROCESS_PEB_ENVP */
};

PRIVATE NONNULL((1, 2)) ssize_t KCALL
peb_print_environ(struct mman *__restrict mm, pformatprinter printer,
                   void *arg, USER CHECKED struct process_peb const *peb) {
	struct _peb_environ_buffer info;
	mman_read(mm, (byte_t const *)peb + OFFSET_PROCESS_PEB_ENVC, &info, sizeof(info));
	return ProcFS_PrintUserSpaceStringArray(mm, printer, arg, info.pp_envc, info.pp_envp);
}


#ifdef __ARCH_HAVE_COMPAT
struct _compat_peb_environ_buffer {
#if OFFSET_COMPAT_PROCESS_PEB_ENVC < OFFSET_COMPAT_PROCESS_PEB_ENVP
	compat_size_t pp_envc;
#if (OFFSET_COMPAT_PROCESS_PEB_ENVC + __ARCH_COMPAT_SIZEOF_SIZE_T) < OFFSET_COMPAT_PROCESS_PEB_ENVP
	byte_t __pp_pad[OFFSET_COMPAT_PROCESS_PEB_ENVP - (OFFSET_COMPAT_PROCESS_PEB_ENVC + __ARCH_COMPAT_SIZEOF_SIZE_T)];
#elif (OFFSET_COMPAT_PROCESS_PEB_ENVC + __ARCH_COMPAT_SIZEOF_SIZE_T) > OFFSET_COMPAT_PROCESS_PEB_ENVP
#error "Invalid offsets"
#endif /* ... */
	compat_ptr(compat_uintptr_t) pp_envp;
#else /* OFFSET_COMPAT_PROCESS_PEB_ENVC < OFFSET_COMPAT_PROCESS_PEB_ENVP */
	compat_ptr(compat_uintptr_t) pp_envp;
#if (OFFSET_COMPAT_PROCESS_PEB_ENVP + __ARCH_COMPAT_SIZEOF_SIZE_T) < OFFSET_COMPAT_PROCESS_PEB_ENVC
	byte_t __pp_pad[OFFSET_COMPAT_PROCESS_PEB_ENVC - (OFFSET_COMPAT_PROCESS_PEB_ENVP + __ARCH_COMPAT_SIZEOF_SIZE_T)];
#elif (OFFSET_COMPAT_PROCESS_PEB_ENVP + __ARCH_COMPAT_SIZEOF_SIZE_T) > OFFSET_COMPAT_PROCESS_PEB_ENVC
#error "Invalid offsets"
#endif /* ... */
	size_t pp_envc;
#endif /* OFFSET_COMPAT_PROCESS_PEB_ENVC >= OFFSET_COMPAT_PROCESS_PEB_ENVP */
};

PRIVATE NONNULL((1, 2)) ssize_t KCALL
compat_peb_print_environ(struct mman *__restrict mm, pformatprinter printer,
                         void *arg, USER CHECKED struct compat_process_peb const *peb) {
	struct _compat_peb_environ_buffer info;
	mman_read(mm, (byte_t const *)peb + OFFSET_COMPAT_PROCESS_PEB_ENVC, &info, sizeof(info));
	return ProcFS_PrintCompatUserSpaceStringArray(mm, printer, arg, info.pp_envc, info.pp_envp);
}
#endif /* __ARCH_HAVE_COMPAT */



INTERN NONNULL((1)) ssize_t KCALL
ProcFS_PerProc_Environ_Printer(struct regular_node *__restrict self,
                               pformatprinter printer, void *arg) {
	REF struct task *thread;
	REF struct mman *threadmm;
	ssize_t result = 0;
	upid_t pid;
	/* Lookup the associated thread. */
	pid    = (upid_t)(self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK);
	thread = pidns_trylookup_task(THIS_PIDNS, pid);
	if unlikely(!thread)
		goto done;
	/* Lookup the associated mman. */
	{
		FINALLY_DECREF_UNLIKELY(thread);
		threadmm = task_getmman(thread);
	}
	{
		USER CHECKED void *peb;
		FINALLY_DECREF_UNLIKELY(threadmm);
		peb = FORMMAN(threadmm, thismman_execinfo).mei_peb;

#ifdef __ARCH_HAVE_COMPAT
		if (FORMMAN(threadmm, thismman_execinfo).mei_peb_iscompat) {
			result = compat_peb_print_environ(threadmm, printer, arg,
			                                  (USER CHECKED struct compat_process_peb const *)peb);
		} else
#endif /* __ARCH_HAVE_COMPAT */
		{
			result = peb_print_environ(threadmm, printer, arg,
			                           (USER CHECKED struct process_peb const *)peb);
		}
	}
done:
	return result;
}


DECL_END

#endif /* !GUARD_MODPROCFS_FILES_PERPROC_ENVIRON_C */
