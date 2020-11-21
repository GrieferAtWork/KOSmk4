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
#ifndef GUARD_MODDBX_OBNOTE_C
#define GUARD_MODDBX_OBNOTE_C 1
#define _KOS_SOURCE 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_DEBUGGER

/**/
#include <fs/vfs.h>
#include <kernel/except.h>
#include <kernel/vm/exec.h>
#include <sched/pid.h>
#include <sched/task.h>

#include <sys/mmio.h>

#include <format-printer.h>
#include <inttypes.h>
#include <string.h>

#include "include/obnote.h"

DECL_BEGIN

#define DO(expr)                 \
	do {                         \
		if ((temp = (expr)) < 0) \
			goto err;            \
		result += temp;          \
	}	__WHILE0
#define RAWPRINT(str)     (*printer)(arg, str, COMPILER_STRLEN(str))
#define PRINT(str)        DO(RAWPRINT(str))
#define REPEAT(ch, count) DO(format_repeat(printer, arg, ch, count))
#define PRINTF(...)       DO(format_printf(printer, arg, __VA_ARGS__))


PRIVATE NONNULL((1, 3, 4)) ssize_t
NOTHROW(KCALL task_note)(pformatprinter printer, void *arg,
                         KERNEL CHECKED void const *pointer,
                         unsigned int *__restrict pstatus) {
	ssize_t temp, result = 0;
	struct task *thread = (struct task *)pointer;
	struct vm_execinfo_struct *execinfo;
	char const *exec_name = NULL;
	u16 exec_namelen      = 0;
	uintptr_t thread_flags;
	pid_t pid, tid;
	TRY {
		REF struct directory_entry *dent;
		/* Do some basic verification of the task header. */
		if (thread->t_self != thread)
			goto badobj;
		if (thread->t_refcnt == 0)
			goto badobj;
		thread_flags = thread->t_flags;
		execinfo     = &FORVM(thread->t_vm, thisvm_execinfo);
		dent         = execinfo->ei_dent;
		if (dent) {
			exec_name    = dent->de_name;
			exec_namelen = dent->de_namelen;
			if (exec_namelen > 16)
				exec_namelen = 16;
			peekb(exec_name);
			peekb(exec_name + exec_namelen - 1);
		}
		pid = task_getrootpid_of_s(thread);
		tid = task_getroottid_of_s(thread);
	} EXCEPT {
		goto badobj;
	}
	/* Print  */
	if (exec_namelen) {
		DO((*printer)(arg, exec_name, exec_namelen));
	} else if (thread_flags & TASK_FKERNTHREAD) {
		PRINT("kernel");
	} else {
		PRINT("??" "?");
	}
	PRINTF(" %" PRIuN(__SIZEOF_PID_T__), pid);
	if (pid != tid)
		PRINTF(" %" PRIuN(__SIZEOF_PID_T__), tid);
	return result;
err:
	return temp;
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}

PRIVATE struct obnote_entry const notes[] = {
	{ "task", &task_note }
};


/* Print extended information (if available)
 * that related to the given `name'.
 * @param: pstatus: [out] Set to one of `OBNOTE_PRINT_STATUS_*'.
 * @return: * :     The usual pformatprinter return value. */
PUBLIC NONNULL((1, 3, 4, 5)) ssize_t
NOTHROW(KCALL obnote_print)(pformatprinter printer, void *arg,
                            KERNEL CHECKED void const *pointer,
                            char const *__restrict name,
                            unsigned int *__restrict pstatus) {
	size_t i;
	for (i = 0; i < COMPILER_LENOF(notes); ++i) {
		if (strcmp(notes[i].one_name, name) == 0) {
			/* Found the note! */
			*pstatus = OBNOTE_PRINT_STATUS_SUCCESS;
			return (*notes[i].one_cb)(printer, arg, pointer, pstatus);
		}
	}
	*pstatus = OBNOTE_PRINT_STATUS_BADNAME;
	return 0;
}


DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_OBNOTE_C */
