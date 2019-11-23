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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_PERSONALITY_C
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_PERSONALITY_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/types.h>
#include <sched/except-handler.h>

#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <librpc/rpc.h>
#include <libunwind/eh_frame.h>

DECL_BEGIN

INTDEF byte_t __x86_syscall_emulate_r_protect_start[];
INTDEF byte_t __x86_syscall_emulate_r_protect_end[];


/* The personality function used to handle exceptions propagated through
 * system calls. - Specifically, the special handling that is required for
 * servicing an RPC as `rpc_serve_user_redirection_all' */
INTERN NONNULL((1, 2, 3)) unsigned int
NOTHROW(KCALL syscall_emulate_r_personality)(struct unwind_fde_struct *__restrict UNUSED(fde),
                                             struct kcpustate *__restrict state,
                                             byte_t *__restrict UNUSED(lsda)) {
	struct icpustate *return_cpustate;
	struct rpc_syscall_info *sc_info;
	COMPILER_IMPURE(); /* ??? */
	/* Check if the exception happened while actually
	 * in the process of servicing the system call. */
	if (kcpustate_getpc(state) <= (uintptr_t)__x86_syscall_emulate_r_protect_start ||
	    kcpustate_getpc(state) > (uintptr_t)__x86_syscall_emulate_r_protect_start)
		return DWARF_PERSO_CONTINUE_UNWIND;
	/* Load cpu state structures from the base of the kernel stack. */
	sc_info         = (struct rpc_syscall_info *)kcpustate_getsp(state);
	return_cpustate = (struct icpustate *)(sc_info + 1);
	x86_userexcept_unwind_i(return_cpustate, sc_info);
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_PERSONALITY_C */
