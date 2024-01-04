/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_DIVIDE_BY_ZERO_C
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_DIVIDE_BY_ZERO_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/rt/except-handler.h>
#include <kernel/types.h>
#include <kernel/x86/fault.h> /* x86_handle_divide_by_zero() */
#include <kernel/x86/idt.h>   /* IDT_CONFIG_ISTRAP() */

#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <assert.h>

#include <libinstrlen/instrlen.h>

DECL_BEGIN

INTERN ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL
x86_handle_divide_by_zero(struct icpustate *__restrict state) {
	static_assert(IDT_CONFIG_ISTRAP(0x00)); /* #DE  Divide by zero */
	byte_t const *curr_pc, *next_pc;
	unsigned int i;
	/* NOTE: Must load `next_pc' before setting the exception code,
	 *       since inspecting program  text may  clobber the  error
	 *       code when a segfault happens. */
	curr_pc = icpustate_getpc(state);
	next_pc = instruction_succ_nx(curr_pc, icpustate_getisa(state));

	/* TODO: This function can also get called due to divide overflow! */
	/* TODO: This function can also get called due to `aam $0' */

	PERTASK_SET(this_exception_code, EXCEPT_CODEOF(E_DIVIDE_BY_ZERO));
	for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i)
		PERTASK_SET(this_exception_args.e_pointers[i], 0);
	PERTASK_SET(this_exception_faultaddr, curr_pc);
	if (next_pc)
		icpustate_setpc(state, next_pc);
	except_throw_current_at_icpustate(state);
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_DIVIDE_BY_ZERO_C */
