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

#include <kernel/except.h>
#include <kernel/paging.h>
#include <kernel/syscall-properties.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <kernel/x86/syscall-info.h>
#include <kernel/x86/syscall-tables.h> /* CONFIG_X86_EMULATE_LCALL7 */
#include <sched/except-handler.h>

#include <hybrid/atomic.h>
#include <hybrid/host.h>
#include <hybrid/unaligned.h>

#include <asm/cpu-flags.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <errno.h>
#include <string.h>

#include <librpc/rpc.h>
#include <libunwind/eh_frame.h>
#include <libunwind/unwind.h>

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
	byte_t *pc;
	/* Check if the exception happened while actually in the process of
	 * servicing the system call.
	 * Technically, there shouldn't be a chance of an exception happening
	 * for another reason, but better be careful and do this check properly. */
	pc = (byte_t *)kcpustate_getpc(state);
	if (pc <= __x86_syscall_emulate_r_protect_start ||
	    pc > __x86_syscall_emulate_r_protect_end)
		return DWARF_PERSO_CONTINUE_UNWIND;
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


#ifndef CONFIG_X86_EMULATE_LCALL7

struct x86_syscall32_lcall7_args {
	u32                l7_eax;
	u32                l7_ecx;
	u32                l7_edx;
	u32                l7_fs;
	u32                l7_es;
	u32                l7_ds;
	struct irregs_user l7_iret;
};

INTERN unsigned int
NOTHROW(KCALL x86_syscall_personality_asm32_lcall7)(struct unwind_fde_struct *__restrict fde,
                                                    struct kcpustate *__restrict state,
                                                    byte_t *__restrict UNUSED(lsda)) {
	struct ucpustate ustate;
	unsigned int error;
	struct rpc_syscall_info info;
	kcpustate_to_ucpustate(state, &ustate);
	{
		unwind_cfa_sigframe_state_t cfa;
		void *pc = (void *)(ucpustate_getpc(&ustate) - 1);
		error = unwind_fde_sigframe_exec(fde, &cfa, pc);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
		error = unwind_cfa_sigframe_apply(&cfa, fde, pc,
		                                  &unwind_getreg_kcpustate, state,
		                                  &unwind_setreg_ucpustate, &ustate);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
	}
	/* Check if the return state actually points into user-space,
	 * or alternatively: indicates a user-space redirection. */
	if (ucpustate_iskernel(&ustate) &&
	    ucpustate_getpc(&ustate) != (uintptr_t)&x86_rpc_user_redirection)
		return DWARF_PERSO_ABORT_SEARCH;
	rpc_syscall_info_get32_lcall7_nx(&info, &ustate);
	x86_userexcept_unwind(&ustate, &info);
err:
	halt_unhandled_exception(error, state);
	return DWARF_PERSO_ABORT_SEARCH;
}


typedef syscall_ulong_t (__ARCH_SYSCALLCC *syscall_proto_t)(syscall_ulong_t arg0, syscall_ulong_t arg1,
                                                            syscall_ulong_t arg2, syscall_ulong_t arg3,
                                                            syscall_ulong_t arg4, syscall_ulong_t arg5);
typedef u64 (__ARCH_SYSCALLCC *syscall_proto64_t)(syscall_ulong_t arg0, syscall_ulong_t arg1,
                                                  syscall_ulong_t arg2, syscall_ulong_t arg3,
                                                  syscall_ulong_t arg4, syscall_ulong_t arg5);

/* Don't warn about the fact that parts of `argv' below may be
 * uninitialized when `proto()' gets invoked. This is intended,
 * as the uninitialized portion makes up the arguments that
 * aren't actually being used. */
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif /* __GNUC__ */

INTERN syscall_ulong_t FCALL
x86_syscall32_lcall7_main(struct x86_syscall32_lcall7_args *__restrict args,
                          u32 sysno) {
	unsigned int argc;
	syscall_ulong_t result;
	syscall_ulong_t argv[6];
	USER UNCHECKED u32 *usp;
	bool double_wide;
	void *proto;
	usp = (USER UNCHECKED u32 *)irregs_getuserpsp(&args->l7_iret);
	if (sysno <= __NR32_syscall0_max) {
		proto       = x86_sysroute0_c32[sysno];
		argc        = __kernel_syscall_regcnt(kernel_syscall0_regcnt32, sysno);
		double_wide = __kernel_syscall_doublewide(kernel_syscall0_regcnt32, sysno);
	} else if (sysno >= __NR32_syscall1_min && sysno <= __NR32_syscall1_max) {
		proto       = x86_sysroute1_c32[sysno - __NR32_syscall1_min];
		argc        = __kernel_syscall_regcnt(kernel_syscall1_regcnt32, sysno - __NR32_syscall1_min);
		double_wide = __kernel_syscall_doublewide(kernel_syscall1_regcnt32, sysno - __NR32_syscall1_min);
	} else {
		syscall_ulong_t rpc_flags;
		if (!(irregs_getpflags(&args->l7_iret) & EFLAGS_DF))
			return (syscall_ulong_t)-ENOSYS;
		rpc_flags = RPC_SYSCALL_INFO_METHOD_LCALL7_32 |
		            RPC_SYSCALL_INFO_FEXCEPT;
		if likely(ADDR_ISUSER(usp)) {
			TRY {
				argv[0] = ATOMIC_READ(usp[0]);
				rpc_flags |= RPC_SYSCALL_INFO_FREGVALID(0);
				argv[1] = ATOMIC_READ(usp[1]);
				rpc_flags |= RPC_SYSCALL_INFO_FREGVALID(1);
				argv[2] = ATOMIC_READ(usp[2]);
				rpc_flags |= RPC_SYSCALL_INFO_FREGVALID(2);
				argv[3] = ATOMIC_READ(usp[3]);
				rpc_flags |= RPC_SYSCALL_INFO_FREGVALID(3);
				argv[4] = ATOMIC_READ(usp[4]);
				rpc_flags |= RPC_SYSCALL_INFO_FREGVALID(4);
				argv[5] = ATOMIC_READ(usp[5]);
				rpc_flags |= RPC_SYSCALL_INFO_FREGVALID(5);
			} EXCEPT {
			}
		}
		THROW(E_UNKNOWN_SYSTEMCALL,
		      rpc_flags,
		      sysno,
		      argv[0], argv[1], argv[2],
		      argv[3], argv[4], argv[5]);
	}
	if unlikely(!ADDR_ISUSER(usp)) {
		if (argc != 0)
			THROW(E_SEGFAULT_UNMAPPED, usp, E_SEGFAULT_CONTEXT_USERCODE);
	} else {
		switch (argc) {
		case 6:
			argv[5] = ATOMIC_READ(usp[5]);
			ATTR_FALLTHROUGH
		case 5:
			argv[4] = ATOMIC_READ(usp[4]);
			ATTR_FALLTHROUGH
		case 4:
			argv[3] = ATOMIC_READ(usp[3]);
			ATTR_FALLTHROUGH
		case 3:
			argv[2] = ATOMIC_READ(usp[2]);
			ATTR_FALLTHROUGH
		case 2:
			argv[1] = ATOMIC_READ(usp[1]);
			ATTR_FALLTHROUGH
		case 1:
			argv[0] = ATOMIC_READ(usp[0]);
			ATTR_FALLTHROUGH
		case 0:
			break;
		default: __builtin_unreachable();
		}
	}
	if (double_wide) {
		u64 result64;
		result64 = (*(syscall_proto64_t)proto)(argv[0], argv[1],
		                                       argv[2], argv[3],
		                                       argv[4], argv[5]);
		args->l7_edx = (u32)(result64 >> 32);
		result = (syscall_ulong_t)(u32)result64;
	} else {
		result = (*(syscall_proto_t)proto)(argv[0], argv[1],
		                                   argv[2], argv[3],
		                                   argv[4], argv[5]);
	}
	return result;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif /* __GNUC__ */

#endif /* !CONFIG_X86_EMULATE_LCALL7 */

DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_NORMAL 1
#include "personality-impl.c.inl"
#define DEFINE_BREAK 1
#include "personality-impl.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_PERSONALITY_C */
