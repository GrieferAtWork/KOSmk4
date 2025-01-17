/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODGDBSERVER_BREAKPOINT_C
#define GUARD_MODGDBSERVER_BREAKPOINT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/mman.h>
#include <sched/task.h>

#include "gdb.h"

DECL_BEGIN

/* GDB breakpoint API
 * @param: kind: arch-specific
 * @return: EOK:      Success
 * @return: ENOSYS:   The specified breakpoint type isn't supported, or breakpoints aren't supported in general
 * @return: EALREADY: [GDB_AddBreak] A breakpoint already exists for the specified location.
 * @return: ENOMEM:   [GDB_AddBreak] Failed to add the breakpoint (too many breakpoints already defined)
 * @return: EFAULT:   [GDB_AddBreak] Attempted to define a software-breakpoint at a faulty memory location.
 * @return: ENOENT:   [GDB_DelBreak] The specified breakpoint doesn't exist. */
INTERN WUNUSED errno_t
NOTHROW(FCALL GDB_AddBreak)(struct task *__restrict thread,
                            unsigned int type,
                            VIRT void *addr, unsigned int kind) {
	errno_t result;
	if (ADDR_ISKERN(addr)) {
		result = GDB_MMan_AddBreak(&mman_kernel, type, addr, kind);
	} else {
		REF struct mman *effective_mm;
		effective_mm = task_getmman(thread);
		result = GDB_MMan_AddBreak(effective_mm, type, addr, kind);
		decref_unlikely(effective_mm);
	}
	return result;
}

INTERN WUNUSED errno_t
NOTHROW(FCALL GDB_DelBreak)(struct task *__restrict thread,
                            unsigned int type,
                            VIRT void *addr, unsigned int kind) {
	errno_t result;
	if (ADDR_ISKERN(addr)) {
		result = GDB_MMan_DelBreak(&mman_kernel, type, addr, kind);
	} else {
		REF struct mman *effective_mm;
		effective_mm = task_getmman(thread);
		result = GDB_MMan_DelBreak(effective_mm, type, addr, kind);
		decref_unlikely(effective_mm);
	}
	return result;
}


DECL_END

#endif /* !GUARD_MODGDBSERVER_BREAKPOINT_C */
