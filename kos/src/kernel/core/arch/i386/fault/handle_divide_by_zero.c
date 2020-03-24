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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_DIVIDE_BY_ZERO_C
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_DIVIDE_BY_ZERO_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/fault.h>
#include <kernel/types.h>
#include <sched/except-handler.h>

#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <libinstrlen/instrlen.h>

DECL_BEGIN

INTERN struct icpustate *FCALL
x86_handle_divide_by_zero(struct icpustate *__restrict state) {
	byte_t *pc, *next_pc;
	unsigned int i;
	PERTASK_SET(this_exception_code,
	            ERROR_CODEOF(E_DIVIDE_BY_ZERO));
	/* TODO: This function can also get called due to divide overflow! */
	/* TODO: This function can also get called due to `aam $0' */
	for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i)
		PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
#if EXCEPT_BACKTRACE_SIZE != 0
	for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i)
		PERTASK_SET(this_exception_trace[i], (void *)0);
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	pc = (byte_t *)icpustate_getpc(state);
	PERTASK_SET(this_exception_faultaddr, (void *)pc);
	next_pc = (byte_t *)instruction_succ(pc);
	if (next_pc)
		icpustate_setpc(state, (uintptr_t)next_pc);
	x86_userexcept_unwind_interrupt(state);
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_DIVIDE_BY_ZERO_C */
