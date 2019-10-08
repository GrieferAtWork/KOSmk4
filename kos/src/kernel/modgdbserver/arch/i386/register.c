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
#ifndef GUARD_MODGDBSERVER_ARCH_I386_REGISTER_C
#define GUARD_MODGDBSERVER_ARCH_I386_REGISTER_C 1

#include <kernel/compiler.h>

#include <kernel/fpu.h>
#include <sched/task.h>

#include <hybrid/unaligned.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/fpu-state.h>
#include <kos/kernel/gdb-cpu-state.h>

#include <string.h>

#include "../../gdb.h"

#ifndef __INTELLISENSE__
#ifdef __x86_64__

#error TODO

#else /* __x86_64__ */

#define GET_REGISTER 1
#include "register32-impl.c.inl"

#define SET_REGISTER 1
#include "register32-impl.c.inl"

#endif /* !__x86_64__ */
#endif /* !__INTELLISENSE__ */

DECL_BEGIN

#ifdef __x86_64__
#define FLAGS_REGNO GDB_REGISTER_X86_64_RFLAGS
#else /* __x86_64__ */
#define FLAGS_REGNO GDB_REGISTER_I386_EFLAGS
#endif /* !__x86_64__ */

/* Get/Set the single-step mode that is active when execution of the current thread resumes. */
INTERN bool 
NOTHROW(FCALL GDB_GetSingleStep)(struct task *__restrict thread,
                                 bool *__restrict penabled) {
	uintptr_t flags;
	if (!GDB_GetRegister(thread, FLAGS_REGNO, &flags, sizeof(flags)))
		return false;
	*penabled = flags & EFLAGS_TF;
	return true;
}

INTERN bool
NOTHROW(FCALL GDB_SetSingleStep)(struct task *__restrict thread,
                                 bool enabled) {
	uintptr_t flags, new_flags;
	if (!GDB_GetRegister(thread, FLAGS_REGNO,
	                     &flags, sizeof(flags)))
		return false;
	new_flags = flags & ~EFLAGS_TF;
	if (enabled)
		new_flags |= EFLAGS_TF;
	if (new_flags != flags) {
		if (!GDB_SetRegister(thread, FLAGS_REGNO,
		                     &new_flags, sizeof(new_flags)))
			return false;
	}
	return true;
}



DECL_END

#endif /* !GUARD_MODGDBSERVER_ARCH_I386_REGISTER_C */
