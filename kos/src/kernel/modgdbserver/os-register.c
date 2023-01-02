/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODGDBSERVER_OS_REGISTER_C
#define GUARD_MODGDBSERVER_OS_REGISTER_C 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <sched/group.h>

#include <format-printer.h>
#include <string.h>

#include "gdb.h"


DECL_BEGIN

#define OS_REGISTER_TID       0 /* ThreadID */
#define OS_REGISTER_ROOTTID   1 /* ThreadID (root namespace) */
#define OS_REGISTER_PID       2 /* ProcessID */
#define OS_REGISTER_ROOTPID   3 /* ProcessID (root namespace) */
#define OS_REGISTER_PGID      4 /* ProcessGroupID */
#define OS_REGISTER_ROOTPGID  5 /* ProcessGroupID (root namespace) */
#define OS_REGISTER_SID       6 /* SessionID */
#define OS_REGISTER_ROOTSID   7 /* SessionID (root namespace) */
#define OS_REGISTER_COUNT     7

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(FCALL GDB_GetOsRegisterName)(uintptr_t os_regno) {
	char const *result;
	switch (os_regno) {

	case OS_REGISTER_TID:
		result = "tid";
		break;
	case OS_REGISTER_ROOTTID:
		result = "roottid";
		break;
	case OS_REGISTER_PID:
		result = "pid";
		break;
	case OS_REGISTER_ROOTPID:
		result = "rootpid";
		break;
	case OS_REGISTER_PGID:
		result = "pgid";
		break;
	case OS_REGISTER_ROOTPGID:
		result = "rootpgid";
		break;
	case OS_REGISTER_SID:
		result = "sid";
		break;
	case OS_REGISTER_ROOTSID:
		result = "rootsid";
		break;

	default:
		result = NULL;
		break;
	}
	return result;
}

/* Enumerate/print special OS registers. */
INTERN ATTR_CONST NONNULL((1)) bool
NOTHROW(FCALL GDB_HasOsRegister)(struct task *__restrict thread, uintptr_t os_regno) {
	(void)thread;
	return os_regno < OS_REGISTER_COUNT;
}

INTERN NONNULL((1, 3)) ssize_t
NOTHROW(FCALL GDB_PrintOsRegisterName)(struct task *__restrict thread, uintptr_t os_regno,
                                       pformatprinter printer, void *arg) {
	ssize_t result = 0;
	char const *name;
	(void)thread;
	name = GDB_GetOsRegisterName(os_regno);
	if (name)
		result = (*printer)(arg, name, strlen(name));
	return result;
}

INTERN NONNULL((1, 3)) ssize_t
NOTHROW(FCALL GDB_PrintOsRegisterValue)(struct task *__restrict thread, uintptr_t os_regno,
                                        pformatprinter printer, void *arg) {
	ssize_t result;
	switch (os_regno) {

	case OS_REGISTER_TID:
		result = format_printf(printer, arg, "%u", task_getselftid_of(thread));
		break;

	case OS_REGISTER_ROOTTID:
		result = format_printf(printer, arg, "%u", task_getroottid_of(thread));
		break;

	case OS_REGISTER_PID:
		result = format_printf(printer, arg, "%u", task_getselfpid_of(thread));
		break;

	case OS_REGISTER_ROOTPID:
		result = format_printf(printer, arg, "%u", task_getrootpid_of(thread));
		break;

	case OS_REGISTER_PGID:
	case OS_REGISTER_ROOTPGID: {
		REF struct procgrp *grp;
		grp    = task_getprocgrp_of(thread);
		result = format_printf(printer, arg, "%u",
		                       os_regno == OS_REGISTER_PGID
		                       ? procgrp_getnspgid(grp, grp->pgr_ns)
		                       : procgrp_getrootpgid(grp));
		decref_unlikely(grp);
	}	break;

	case OS_REGISTER_SID:
	case OS_REGISTER_ROOTSID: {
		REF struct procgrp *grp;
		grp    = task_getprocgrp_of(thread);
		result = format_printf(printer, arg, "%u",
		                       os_regno == OS_REGISTER_PGID
		                       ? procgrp_getnssid(grp, grp->pgr_ns)
		                       : procgrp_getrootsid(grp));
		decref_unlikely(grp);
	}	break;

	default:
		result = 0;
		break;
	}
	return result;
}



DECL_END

#endif /* !GUARD_MODGDBSERVER_OS_REGISTER_C */
