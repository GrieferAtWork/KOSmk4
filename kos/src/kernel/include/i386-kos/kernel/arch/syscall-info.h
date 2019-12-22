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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_SYSCALL_INFO_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_SYSCALL_INFO_H 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/paging.h>
#include <kernel/syscall-properties.h>
#include <kernel/types.h>
#include <kernel/user.h>

#include <hybrid/__atomic.h>
#include <hybrid/__unaligned.h>
#include <hybrid/host.h>

#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <string.h>

#include <librpc/rpc.h>

#ifdef __CC__
DECL_BEGIN

/* Retrieve RPC system call information, given the user-space
 * CPU-state that was used to perform the system call. */

#ifdef __cplusplus
extern "C++" {
#define rpc_syscall_info_get32_int80h_ucpustate   rpc_syscall_info_get32_int80h
#define rpc_syscall_info_get32_sysenter_ucpustate rpc_syscall_info_get32_sysenter
#define rpc_syscall_info_get32_lcall7_ucpustate   rpc_syscall_info_get32_lcall7
#ifdef __x86_64__
#define rpc_syscall_info_get64_int80h_ucpustate   rpc_syscall_info_get64_int80h
#endif /* __x86_64__ */
#endif /* __cplusplus */

/* 32-bit: int 80h */
LOCAL NONNULL((1, 2)) void
NOTHROW(FCALL rpc_syscall_info_get32_int80h_ucpustate)(struct rpc_syscall_info *__restrict self,
                                                       struct ucpustate const *__restrict state) {
	self->rsi_flags = RPC_SYSCALL_INFO_METHOD_INT80H_32 |
	                  RPC_SYSCALL_INFO_FARGVALID(0) |
	                  RPC_SYSCALL_INFO_FARGVALID(1) |
	                  RPC_SYSCALL_INFO_FARGVALID(2) |
	                  RPC_SYSCALL_INFO_FARGVALID(3) |
	                  RPC_SYSCALL_INFO_FARGVALID(4) |
	                  RPC_SYSCALL_INFO_FARGVALID(5);
	if (ucpustate_getpflags(state) & EFLAGS_CF)
		self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	self->rsi_sysno   = gpregs_getpax(&state->ucs_gpregs);
	self->rsi_args[0] = gpregs_getpbx(&state->ucs_gpregs);
	self->rsi_args[1] = gpregs_getpcx(&state->ucs_gpregs);
	self->rsi_args[2] = gpregs_getpdx(&state->ucs_gpregs);
	self->rsi_args[3] = gpregs_getpsi(&state->ucs_gpregs);
	self->rsi_args[4] = gpregs_getpdi(&state->ucs_gpregs);
	self->rsi_args[5] = gpregs_getpbp(&state->ucs_gpregs);
}

/* 32-bit: sysenter */
LOCAL NONNULL((1, 2)) void
NOTHROW(FCALL rpc_syscall_info_get32_sysenter_ucpustate)(struct rpc_syscall_info *__restrict self,
                                                         struct ucpustate const *__restrict state) {
	unsigned int regcount;
	self->rsi_flags = RPC_SYSCALL_INFO_METHOD_SYSENTER_32 |
	                  RPC_SYSCALL_INFO_FARGVALID(0) |
	                  RPC_SYSCALL_INFO_FARGVALID(1) |
	                  RPC_SYSCALL_INFO_FARGVALID(2) |
	                  RPC_SYSCALL_INFO_FARGVALID(3);
	if (ucpustate_getpflags(state) & EFLAGS_CF)
		self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	self->rsi_sysno   = gpregs_getpax(&state->ucs_gpregs);
	self->rsi_args[0] = gpregs_getpbx(&state->ucs_gpregs);
	self->rsi_args[1] = gpregs_getpcx(&state->ucs_gpregs);
	self->rsi_args[2] = gpregs_getpdx(&state->ucs_gpregs);
	self->rsi_args[3] = gpregs_getpsi(&state->ucs_gpregs);
	regcount = kernel_syscall32_regcnt(self->rsi_sysno);
	if (regcount >= 5) {
		u32 *ebp = (u32 *)(uintptr_t)(u32)gpregs_getpbp(&state->ucs_gpregs);
		if (ADDR_ISUSER(ebp)) {
			struct exception_info old_info;
			memcpy(&old_info, &THIS_EXCEPTION_INFO, sizeof(struct exception_info));
			TRY {
				self->rsi_args[4] = __hybrid_atomic_load(ebp[0], __ATOMIC_ACQUIRE);
				self->rsi_flags |= RPC_SYSCALL_INFO_FARGVALID(4);
				if (regcount >= 6) {
					self->rsi_flags |= RPC_SYSCALL_INFO_FARGVALID(5);
					self->rsi_args[5] = __hybrid_atomic_load(ebp[1], __ATOMIC_ACQUIRE);
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



/* 32-bit: lcall7 */
LOCAL NONNULL((1, 2)) void
NOTHROW(FCALL rpc_syscall_info_get32_lcall7_ucpustate)(struct rpc_syscall_info *__restrict self,
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
		__hybrid_unaligned_get16((u16 *)(pc - 2)) == 0x0007) {
		/* This really is an lcall7 instruction */
		u32 lcall_arg;
		lcall_arg = __hybrid_unaligned_get32((u32 *)(pc - 6));
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
			memcpy(&old_info, &THIS_EXCEPTION_INFO,
			       sizeof(struct exception_info));
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
				memcpy(&THIS_EXCEPTION_INFO,
				       &old_info,
				       sizeof(struct exception_info));
			}
		}
	}
}


#ifdef __x86_64__

/* 64-bit: syscall / int 80h */
LOCAL NONNULL((1, 2)) void /* or `rpc_syscall_info_get64_syscall_ucpustate' */
NOTHROW(FCALL rpc_syscall_info_get64_int80h_ucpustate)(struct rpc_syscall_info *__restrict self,
                                                       struct ucpustate const *__restrict state) {
	self->rsi_flags = RPC_SYSCALL_INFO_METHOD_INT80H_64 |
	                  RPC_SYSCALL_INFO_FARGVALID(0) |
	                  RPC_SYSCALL_INFO_FARGVALID(1) |
	                  RPC_SYSCALL_INFO_FARGVALID(2) |
	                  RPC_SYSCALL_INFO_FARGVALID(3) |
	                  RPC_SYSCALL_INFO_FARGVALID(4) |
	                  RPC_SYSCALL_INFO_FARGVALID(5);
	if (ucpustate_getpflags(state) & EFLAGS_CF)
		self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	self->rsi_sysno   = gpregs_getpax(&state->ucs_gpregs);
	self->rsi_args[0] = gpregs_getpdi(&state->ucs_gpregs);
	self->rsi_args[1] = gpregs_getpsi(&state->ucs_gpregs);
	self->rsi_args[2] = gpregs_getpdx(&state->ucs_gpregs);
	self->rsi_args[3] = gpregs_getp10(&state->ucs_gpregs);
	self->rsi_args[4] = gpregs_getp8(&state->ucs_gpregs);
	self->rsi_args[5] = gpregs_getp9(&state->ucs_gpregs);
}
#endif /* __x86_64__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_SYSCALL_INFO_H */
