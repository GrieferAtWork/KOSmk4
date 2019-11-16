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
#ifndef GUARD_MODPROCFS_ARCH_I386_IOPL_FILES_C
#define GUARD_MODPROCFS_ARCH_I386_IOPL_FILES_C 1
#define _KOS_SOURCE 1 /* snprintf returns size_t */

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/except.h>
#include <sched/cred.h>
#include <sched/iopl.h>

#include <hybrid/atomic.h>

#include <kos/except-inval.h>

#include <string.h>
#include <unicode.h>

#include "../../procfs.h"

DECL_BEGIN

PRIVATE NONNULL((1)) ssize_t KCALL
KeepIopl_Print(pformatprinter printer, void *arg, bool value) {
	char buf[2];
	buf[0] = value ? '1' : '0';
	buf[1] = '\n';
	return (*printer)(arg, buf, 2);
}

PRIVATE NONNULL((1)) void KCALL
KeepIopl_Write(bool *pvalue, USER CHECKED void const *buf, size_t bufsize) {
	USER CHECKED char const *endp;
	char new_mode;
	bool old_value, new_value;
	endp = (USER CHECKED char const *)buf + bufsize;
	while (endp > (USER CHECKED char const *)buf &&
	       unicode_isspace(endp[-1]))
		--endp;
	while ((USER CHECKED char const *)buf < endp &&
	       unicode_isspace(((char const *)buf)[0]))
		buf = (char *)buf + 1;
	bufsize = (size_t)(endp - (USER CHECKED char const *)buf);
	if (bufsize != 1)
		THROW(E_BUFFER_TOO_SMALL, bufsize, 1);
	new_mode = ATOMIC_READ(*(char *)buf);
	if (new_mode == '0')
		new_value = false;
	else if (new_mode == '1')
		new_value = true;
	else {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_BAD_INTEGER);
	}
	for (;;) {
		old_value = ATOMIC_READ(*pvalue);
		if (old_value == new_value)
			break; /* Nothing to do here! */
		/* Need sysadmin to change the value. */
		cred_require_sysadmin();
		/* Need hwio to turn one of these on! */
		if (new_value)
			cred_require_hwio();
		/* Change the value. */
		if (ATOMIC_CMPXCH_WEAK(*pvalue, old_value, new_value))
			break;
	}
}


/* /proc/sys/x86/keepiopl/fork */
INTERN NONNULL((1)) ssize_t KCALL
ProcFS_Sys_X86_KeepIopl_Fork_Print(struct regular_node *__restrict UNUSED(self),
                                   pformatprinter printer, void *arg) {
	return KeepIopl_Print(printer, arg, x86_iopl_keep_after_fork);
}
INTERN NONNULL((1)) void KCALL
ProcFS_Sys_X86_KeepIopl_Fork_Write(struct regular_node *__restrict UNUSED(self),
                                   USER CHECKED void const *buf,
                                   size_t bufsize) {
	KeepIopl_Write(&x86_iopl_keep_after_fork, buf, bufsize);
}


/* /proc/sys/x86/keepiopl/clone */
INTERN NONNULL((1)) ssize_t KCALL
ProcFS_Sys_X86_KeepIopl_Clone_Print(struct regular_node *__restrict UNUSED(self),
                                    pformatprinter printer, void *arg) {
	return KeepIopl_Print(printer, arg, x86_iopl_keep_after_clone);
}
INTERN NONNULL((1)) void KCALL
ProcFS_Sys_X86_KeepIopl_Clone_Write(struct regular_node *__restrict UNUSED(self),
                                    USER CHECKED void const *buf,
                                    size_t bufsize) {
	KeepIopl_Write(&x86_iopl_keep_after_clone, buf, bufsize);
}


/* /proc/sys/x86/keepiopl/exec */
INTERN NONNULL((1)) ssize_t KCALL
ProcFS_Sys_X86_KeepIopl_Exec_Print(struct regular_node *__restrict UNUSED(self),
                                   pformatprinter printer, void *arg) {
	return KeepIopl_Print(printer, arg, x86_iopl_keep_after_exec);
}
INTERN NONNULL((1)) void KCALL
ProcFS_Sys_X86_KeepIopl_Exec_Write(struct regular_node *__restrict UNUSED(self),
                                   USER CHECKED void const *buf,
                                   size_t bufsize) {
	KeepIopl_Write(&x86_iopl_keep_after_exec, buf, bufsize);
}



DECL_END

#endif /* !GUARD_MODPROCFS_ARCH_I386_IOPL_FILES_C */
