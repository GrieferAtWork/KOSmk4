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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_PERSONALITY_C
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_PERSONALITY_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_RPC
#include <kernel/except.h>
#include <kernel/paging.h>
#include <kernel/rt/except-personality.h>
#include <kernel/syscall-properties.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <kernel/x86/syscall-info.h>
#include <sched/except-handler.h>

#include <hybrid/atomic.h>
#include <hybrid/host.h>
#include <hybrid/unaligned.h>

#include <asm/cpu-flags.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <errno.h>
#include <string.h>

#include <libunwind/eh_frame.h>
#include <libunwind/unwind.h>

DECL_BEGIN

INTDEF byte_t __x86_syscall_emulate_r_protect_start[];
INTDEF byte_t __x86_syscall_emulate_r_protect_end[];


/* The personality function used  to handle exceptions propagated  through
 * system calls. - Specifically, the special handling that is required for
 * servicing an RPC as `rpc_serve_user_redirection_all' */
INTERN WUNUSED NONNULL((1, 2)) unsigned int
NOTHROW(EXCEPT_PERSONALITY_CC syscall_emulate_r_personality)(struct unwind_fde_struct *__restrict UNUSED(fde),
                                                             struct kcpustate *__restrict state) {
	struct icpustate *return_cpustate;
	struct rpc_syscall_info *sc_info;
	byte_t const *pc;
	/* Check if the exception happened while actually in the process of
	 * servicing the system call.
	 * Technically, there shouldn't  be a chance  of an exception  happening
	 * for another reason, but better be careful and do this check properly. */
	pc = kcpustate_getpc(state);
	if (pc <= __x86_syscall_emulate_r_protect_start ||
	    pc > __x86_syscall_emulate_r_protect_end)
		return EXCEPT_PERSONALITY_CONTINUE_UNWIND;
	/* Load cpu state structures from the base of the kernel stack. */
#ifdef __x86_64__
	sc_info = (struct rpc_syscall_info *)state->kcs_gpregs.gp_rbx;
#else /* __x86_64__ */
	sc_info = (struct rpc_syscall_info *)(state->kcs_gpregs.gp_edi + 4);
#endif /* !__x86_64__ */
	return_cpustate = (struct icpustate *)(sc_info + 1);
	COMPILER_IMPURE(); /* Suppress incorrect -Wsuggest-attribute=pure */
	x86_userexcept_unwind_i(return_cpustate, sc_info);
}

DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_NORMAL 1
#include "personality-impl.c.inl"
#define DEFINE_BREAK 1
#include "personality-impl.c.inl"
#endif /* !__INTELLISENSE__ */
#endif /* !CONFIG_USE_NEW_RPC */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_PERSONALITY_C */
