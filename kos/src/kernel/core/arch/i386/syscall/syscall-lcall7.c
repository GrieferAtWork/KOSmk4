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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_LCALL7_C
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_LCALL7_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/paging.h>
#include <kernel/syscall-properties.h>
#include <kernel/syscall-tables.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
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
#include <libunwind/unwind.h>

DECL_BEGIN

LOCAL void
NOTHROW(FCALL scinfo_get32_lcall7)(struct rpc_syscall_info *__restrict self,
                                   struct ucpustate const *__restrict state) {
	unsigned int argc;
	/* NOTE: By being a program counter from user-space, PC
	 *       is implicitly checked by the fact that user-space
	 *       will have invoked the instruction from user-space. */
	USER CHECKED byte_t *pc;
	self->rsi_flags = RPC_SYSCALL_INFO_METHOD_LCALL7_32;
	if (ucpustate_getpflags(state) & EFLAGS_CF)
		self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	self->rsi_sysno = gpregs_getpax(&state->ucs_gpregs);
	/* lcall $7, $? -- { 0x9a, ?, ?, ?, ?, 0x07, 0x00 } */
	pc = (USER CHECKED byte_t *)ucpustate_getpc(state);
	if (*(u8 *)(pc - 7) == 0x9a &&
		UNALIGNED_GET16((u16 *)(pc - 2)) == 0x0007) {
		/* This really is an lcall7 instruction */
		u32 lcall_arg;
		lcall_arg = UNALIGNED_GET32((u32 *)(pc - 6));
		if (lcall_arg != 0)
			self->rsi_sysno = lcall_arg;
	}
	argc = kernel_syscall32_regcnt(self->rsi_sysno);
	if (argc != 0) {
		USER UNCHECKED u32 *sp;
		sp = (USER UNCHECKED u32 *)gpregs_getpsp(&state->ucs_gpregs);
		if (ADDR_ISUSER(sp)) {
			struct exception_info old_info;
			unsigned int i;
			memcpy(&old_info, &THIS_EXCEPTION_INFO, sizeof(struct exception_info));
			TRY {
				for (i = 0; i < argc; ++i) {
					self->rsi_args[i] = __hybrid_atomic_load(sp[i], __ATOMIC_ACQUIRE);
					self->rsi_flags |= RPC_SYSCALL_INFO_FARGVALID(i);
				}
			} EXCEPT {
				goto restore_exception;
			}
			__IF0 {
restore_exception:
					memcpy(&THIS_EXCEPTION_INFO, &old_info, sizeof(struct exception_info));
			}
		}
	}
}




struct x86_syscall32_lcall7_args {
#ifdef __x86_64__
	u64           l7_rax;
	u64           l7_rdi;
	u64           l7_rsi;
	u64           l7_rdx;
	u64           l7_rcx;
	u64           l7_r8;
	u64           l7_r9;
	u64           l7_r10;
	u64           l7_r11;
	struct irregs l7_iret;
#else /* __x86_64__ */
	u32                l7_eax;
	u32                l7_ecx;
	u32                l7_edx;
	u32                l7_fs;
	u32                l7_es;
	u32                l7_ds;
	struct irregs_user l7_iret;
#endif /* !__x86_64__ */
};

INTDEF void FCALL /* TODO: Get rid of this */
halt_unhandled_exception(unsigned int error,
                         struct kcpustate *__restrict unwind_state);

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
	scinfo_get32_lcall7(&info, &ustate);
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
		if (!(irregs_getpflags(&args->l7_iret) & EFLAGS_CF))
			return (syscall_ulong_t)-ENOSYS;
		rpc_flags = RPC_SYSCALL_INFO_METHOD_LCALL7_32 |
		            RPC_SYSCALL_INFO_FEXCEPT;
		if likely(ADDR_ISUSER(usp)) {
			TRY {
				argv[0] = ATOMIC_READ(usp[0]);
				rpc_flags |= RPC_SYSCALL_INFO_FARGVALID(0);
				argv[1] = ATOMIC_READ(usp[1]);
				rpc_flags |= RPC_SYSCALL_INFO_FARGVALID(1);
				argv[2] = ATOMIC_READ(usp[2]);
				rpc_flags |= RPC_SYSCALL_INFO_FARGVALID(2);
				argv[3] = ATOMIC_READ(usp[3]);
				rpc_flags |= RPC_SYSCALL_INFO_FARGVALID(3);
				argv[4] = ATOMIC_READ(usp[4]);
				rpc_flags |= RPC_SYSCALL_INFO_FARGVALID(4);
				argv[5] = ATOMIC_READ(usp[5]);
				rpc_flags |= RPC_SYSCALL_INFO_FARGVALID(5);
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
#ifdef __x86_64__
		args->l7_rdx = (u64)(u32)(result64 >> 32);
#else /* __x86_64__ */
		args->l7_edx = (u32)(result64 >> 32);
#endif /* !__x86_64__ */
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


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_LCALL7_C */
