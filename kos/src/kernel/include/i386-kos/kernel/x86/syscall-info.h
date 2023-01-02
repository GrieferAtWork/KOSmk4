/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_SYSCALL_INFO_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_SYSCALL_INFO_H 1

#include <kernel/compiler.h>

#ifndef __INTELLISENSE__
#include <kernel/except.h>
#include <kernel/paging.h>
#endif /* !__INTELLISENSE__ */
#include <kernel/syscall-properties.h>
#include <kernel/types.h>
#include <kernel/user.h>

#include <hybrid/__atomic.h>
#include <hybrid/__unaligned.h>
#include <hybrid/host.h>

#include <asm/cpu-flags.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/rpc.h>

#ifdef __CC__
DECL_BEGIN

/* Retrieve RPC system call information, given the user-space
 * CPU-state that  was  used  to  perform  the  system  call. */

#ifdef __cplusplus
extern "C++" {
#define rpc_syscall_info_get32_int80h_ucpustate      rpc_syscall_info_get32_int80h
#define rpc_syscall_info_get32_int80h_icpustate      rpc_syscall_info_get32_int80h
#define rpc_syscall_info_get32_sysenter_icpustate    rpc_syscall_info_get32_sysenter
#define rpc_syscall_info_get32_sysenter_ucpustate_nx rpc_syscall_info_get32_sysenter_nx
#define rpc_syscall_info_get32_lcall7_icpustate      rpc_syscall_info_get32_lcall7
#define rpc_syscall_info_get32_lcall7_ucpustate_nx   rpc_syscall_info_get32_lcall7_nx
#define rpc_syscall_info_get32_cdecl_icpustate       rpc_syscall_info_get32_cdecl
#ifdef __x86_64__
#define rpc_syscall_info_get64_int80h_ucpustate      rpc_syscall_info_get64_int80h
#define rpc_syscall_info_get64_int80h_icpustate      rpc_syscall_info_get64_int80h
#define rpc_syscall_info_get64_sysvabi_icpustate     rpc_syscall_info_get64_sysvabi
#endif /* __x86_64__ */
#endif /* __cplusplus */

/* 32-bit: int 80h */
LOCAL NONNULL((1, 2)) void
NOTHROW(FCALL rpc_syscall_info_get32_int80h_ucpustate)(struct rpc_syscall_info *__restrict self,
                                                       struct ucpustate const *__restrict state) {
	self->rsi_flags = RPC_SYSCALL_INFO_METHOD_INT80H_32 |
	                  RPC_SYSCALL_INFO_FREGVALID(0) |
	                  RPC_SYSCALL_INFO_FREGVALID(1) |
	                  RPC_SYSCALL_INFO_FREGVALID(2) |
	                  RPC_SYSCALL_INFO_FREGVALID(3) |
	                  RPC_SYSCALL_INFO_FREGVALID(4) |
	                  RPC_SYSCALL_INFO_FREGVALID(5);
	if (ucpustate_getpflags(state) & EFLAGS_DF)
		self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	self->rsi_sysno   = gpregs_getpax(&state->ucs_gpregs);
	self->rsi_regs[0] = gpregs_getpbx(&state->ucs_gpregs);
	self->rsi_regs[1] = gpregs_getpcx(&state->ucs_gpregs);
	self->rsi_regs[2] = gpregs_getpdx(&state->ucs_gpregs);
	self->rsi_regs[3] = gpregs_getpsi(&state->ucs_gpregs);
	self->rsi_regs[4] = gpregs_getpdi(&state->ucs_gpregs);
	self->rsi_regs[5] = gpregs_getpbp(&state->ucs_gpregs);
}

/* 32-bit: int 80h */
LOCAL NONNULL((1, 2)) void
NOTHROW(FCALL rpc_syscall_info_get32_int80h_icpustate)(struct rpc_syscall_info *__restrict self,
                                                       struct icpustate const *__restrict state) {
	self->rsi_flags = RPC_SYSCALL_INFO_METHOD_INT80H_32 |
	                  RPC_SYSCALL_INFO_FREGVALID(0) |
	                  RPC_SYSCALL_INFO_FREGVALID(1) |
	                  RPC_SYSCALL_INFO_FREGVALID(2) |
	                  RPC_SYSCALL_INFO_FREGVALID(3) |
	                  RPC_SYSCALL_INFO_FREGVALID(4) |
	                  RPC_SYSCALL_INFO_FREGVALID(5);
	if (icpustate_getpflags(state) & EFLAGS_DF)
		self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	self->rsi_sysno   = gpregs_getpax(&state->ics_gpregs);
	self->rsi_regs[0] = gpregs_getpbx(&state->ics_gpregs);
	self->rsi_regs[1] = gpregs_getpcx(&state->ics_gpregs);
	self->rsi_regs[2] = gpregs_getpdx(&state->ics_gpregs);
	self->rsi_regs[3] = gpregs_getpsi(&state->ics_gpregs);
	self->rsi_regs[4] = gpregs_getpdi(&state->ics_gpregs);
	self->rsi_regs[5] = gpregs_getpbp(&state->ics_gpregs);
}

/* 32-bit: sysenter */
LOCAL NONNULL((1, 2)) void FCALL
rpc_syscall_info_get32_sysenter_icpustate(struct rpc_syscall_info *__restrict self,
                                          struct icpustate const *__restrict state)
		THROWS(E_SEGFAULT) {
	unsigned int regcount;
	self->rsi_flags = RPC_SYSCALL_INFO_METHOD_SYSENTER_32 |
	                  RPC_SYSCALL_INFO_FREGVALID(0) |
	                  RPC_SYSCALL_INFO_FREGVALID(1) |
	                  RPC_SYSCALL_INFO_FREGVALID(2) |
	                  RPC_SYSCALL_INFO_FREGVALID(3);
	if (icpustate_getpflags(state) & EFLAGS_DF)
		self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	self->rsi_sysno   = gpregs_getpax(&state->ics_gpregs);
	self->rsi_regs[0] = gpregs_getpbx(&state->ics_gpregs);
	self->rsi_regs[1] = gpregs_getpcx(&state->ics_gpregs);
	self->rsi_regs[2] = gpregs_getpdx(&state->ics_gpregs);
	self->rsi_regs[3] = gpregs_getpsi(&state->ics_gpregs);
	regcount = kernel_syscall32_regcnt(self->rsi_sysno);
	if (regcount >= 5) {
		USER u32 *ebp;
		ebp = (USER u32 *)(uintptr_t)(u32)gpregs_getpbp(&state->ics_gpregs);
		validate_readable(ebp, 4);
		self->rsi_regs[4] = __hybrid_atomic_load(ebp[0], __ATOMIC_ACQUIRE);
		self->rsi_flags |= RPC_SYSCALL_INFO_FREGVALID(4);
		if (regcount >= 6) {
			self->rsi_flags |= RPC_SYSCALL_INFO_FREGVALID(5);
			self->rsi_regs[5] = __hybrid_atomic_load(ebp[1], __ATOMIC_ACQUIRE);
		}
	}
}

/* 32-bit: sysenter */
LOCAL NONNULL((1, 2)) void
NOTHROW(FCALL rpc_syscall_info_get32_sysenter_ucpustate_nx)(struct rpc_syscall_info *__restrict self,
                                                            struct ucpustate const *__restrict state) {
	unsigned int regcount;
	self->rsi_flags = RPC_SYSCALL_INFO_METHOD_SYSENTER_32 |
	                  RPC_SYSCALL_INFO_FREGVALID(0) |
	                  RPC_SYSCALL_INFO_FREGVALID(1) |
	                  RPC_SYSCALL_INFO_FREGVALID(2) |
	                  RPC_SYSCALL_INFO_FREGVALID(3);
	if (ucpustate_getpflags(state) & EFLAGS_DF)
		self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	self->rsi_sysno   = gpregs_getpax(&state->ucs_gpregs);
	self->rsi_regs[0] = gpregs_getpbx(&state->ucs_gpregs);
	self->rsi_regs[1] = gpregs_getpcx(&state->ucs_gpregs);
	self->rsi_regs[2] = gpregs_getpdx(&state->ucs_gpregs);
	self->rsi_regs[3] = gpregs_getpsi(&state->ucs_gpregs);
	regcount = kernel_syscall32_regcnt(self->rsi_sysno);
	if (regcount >= 5) {
		u32 *ebp = (u32 *)(uintptr_t)(u32)gpregs_getpbp(&state->ucs_gpregs);
#ifndef __INTELLISENSE__
		if (ADDR_ISUSER(ebp)) {
			NESTED_TRY {
				self->rsi_regs[4] = __hybrid_atomic_load(ebp[0], __ATOMIC_ACQUIRE);
				self->rsi_flags |= RPC_SYSCALL_INFO_FREGVALID(4);
				if (regcount >= 6) {
					self->rsi_flags |= RPC_SYSCALL_INFO_FREGVALID(5);
					self->rsi_regs[5] = __hybrid_atomic_load(ebp[1], __ATOMIC_ACQUIRE);
				}
			} EXCEPT {
				except_class_t cls = except_class();
				if (EXCEPTCLASS_ISRTLPRIORITY(cls))
					RETHROW();
			}
		}
#endif /* !__INTELLISENSE__ */
	}
}

/* 32-bit: ATTR_CDECL */
LOCAL NONNULL((1, 2)) void FCALL
rpc_syscall_info_get32_cdecl_icpustate(struct rpc_syscall_info *__restrict self,
                                       struct icpustate const *__restrict state,
                                       u32 sysno, bool enable_except) {
	unsigned int regcount;
	self->rsi_flags = RPC_SYSCALL_INFO_METHOD_CDECL_32;
	if (enable_except)
		self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	self->rsi_sysno = sysno;
	regcount = kernel_syscall32_regcnt(sysno);
	if (regcount) {
		USER u32 *esp;
		unsigned int i;
		esp = (USER u32 *)(uintptr_t)(u32)icpustate_getuserpsp(state);
		validate_readable(esp, (size_t)regcount * 4);
		for (i = 0; i < regcount; ++i) {
			self->rsi_regs[i] = __hybrid_atomic_load(esp[i], __ATOMIC_ACQUIRE);
			self->rsi_flags |= RPC_SYSCALL_INFO_FREGVALID(i);
		}
	}
}



/* 32-bit: lcall7 */
LOCAL NONNULL((1, 2)) void
NOTHROW(FCALL rpc_syscall_info_get32_lcall7_ucpustate_nx)(struct rpc_syscall_info *__restrict self,
                                                          struct ucpustate const *__restrict state) {
	unsigned int argc;
	/* NOTE: By  being  a program  counter from  user-space, PC
	 *       is  implicitly checked by the fact that user-space
	 *       will have invoked the instruction from user-space. */
	USER CHECKED byte_t const *pc;
	self->rsi_flags = RPC_SYSCALL_INFO_METHOD_LCALL7_32;
	if (ucpustate_getpflags(state) & EFLAGS_DF)
		self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	self->rsi_sysno = gpregs_getpax(&state->ucs_gpregs);
	/* lcall $7, $? -- { 0x9a, ?, ?, ?, ?, 0x07, 0x00 } */
	pc = (USER CHECKED byte_t const *)ucpustate_getpc(state);
	if (*(u8 const *)(pc - 7) == 0x9a &&
		__hybrid_unaligned_getle16((u16 const *)(pc - 2)) == 0x0007) {
		/* This really is an lcall7 instruction */
		u32 lcall_arg;
		lcall_arg = __hybrid_unaligned_getle32((u32 const *)(pc - 6));
		if (lcall_arg != 0)
			self->rsi_sysno = lcall_arg;
	}
	argc = kernel_syscall32_regcnt(self->rsi_sysno);
	if (argc != 0) {
		USER UNCHECKED u32 const *sp;
		sp = (USER UNCHECKED u32 const *)gpregs_getpsp(&state->ucs_gpregs);
#ifndef __INTELLISENSE__
		if (ADDR_ISUSER(sp)) {
			NESTED_TRY {
				unsigned int i;
				for (i = 0; i < argc; ++i) {
					self->rsi_regs[i] = __hybrid_atomic_load(sp[i], __ATOMIC_ACQUIRE);
					self->rsi_flags |= RPC_SYSCALL_INFO_FREGVALID(i);
				}
			} EXCEPT {
				except_class_t cls = except_class();
				if (EXCEPTCLASS_ISRTLPRIORITY(cls))
					RETHROW();
			}
		}
#endif /* !__INTELLISENSE__ */
	}
}


#ifdef __x86_64__

/* 64-bit: syscall / int 80h */
LOCAL NONNULL((1, 2)) void /* or `rpc_syscall_info_get64_syscall_ucpustate' */
NOTHROW(FCALL rpc_syscall_info_get64_int80h_ucpustate)(struct rpc_syscall_info *__restrict self,
                                                       struct ucpustate const *__restrict state) {
	self->rsi_flags = RPC_SYSCALL_INFO_METHOD_INT80H_64 |
	                  RPC_SYSCALL_INFO_FREGVALID(0) |
	                  RPC_SYSCALL_INFO_FREGVALID(1) |
	                  RPC_SYSCALL_INFO_FREGVALID(2) |
	                  RPC_SYSCALL_INFO_FREGVALID(3) |
	                  RPC_SYSCALL_INFO_FREGVALID(4) |
	                  RPC_SYSCALL_INFO_FREGVALID(5);
	if (ucpustate_getpflags(state) & EFLAGS_DF)
		self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	self->rsi_sysno   = gpregs_getpax(&state->ucs_gpregs);
	self->rsi_regs[0] = gpregs_getpdi(&state->ucs_gpregs);
	self->rsi_regs[1] = gpregs_getpsi(&state->ucs_gpregs);
	self->rsi_regs[2] = gpregs_getpdx(&state->ucs_gpregs);
	self->rsi_regs[3] = gpregs_getp10(&state->ucs_gpregs);
	self->rsi_regs[4] = gpregs_getp8(&state->ucs_gpregs);
	self->rsi_regs[5] = gpregs_getp9(&state->ucs_gpregs);
}

/* 64-bit: syscall / int 80h */
LOCAL NONNULL((1, 2)) void /* or `rpc_syscall_info_get64_syscall_icpustate' */
NOTHROW(FCALL rpc_syscall_info_get64_int80h_icpustate)(struct rpc_syscall_info *__restrict self,
                                                       struct icpustate const *__restrict state) {
	self->rsi_flags = RPC_SYSCALL_INFO_METHOD_INT80H_64 |
	                  RPC_SYSCALL_INFO_FREGVALID(0) |
	                  RPC_SYSCALL_INFO_FREGVALID(1) |
	                  RPC_SYSCALL_INFO_FREGVALID(2) |
	                  RPC_SYSCALL_INFO_FREGVALID(3) |
	                  RPC_SYSCALL_INFO_FREGVALID(4) |
	                  RPC_SYSCALL_INFO_FREGVALID(5);
	if (icpustate_getpflags(state) & EFLAGS_DF)
		self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	self->rsi_sysno   = gpregs_getpax(&state->ics_gpregs);
	self->rsi_regs[0] = gpregs_getpdi(&state->ics_gpregs);
	self->rsi_regs[1] = gpregs_getpsi(&state->ics_gpregs);
	self->rsi_regs[2] = gpregs_getpdx(&state->ics_gpregs);
	self->rsi_regs[3] = gpregs_getp10(&state->ics_gpregs);
	self->rsi_regs[4] = gpregs_getp8(&state->ics_gpregs);
	self->rsi_regs[5] = gpregs_getp9(&state->ics_gpregs);
}

/* 64-bit: ATTR_SYSVABI */
LOCAL NONNULL((1, 2)) void FCALL
rpc_syscall_info_get64_sysvabi_icpustate(struct rpc_syscall_info *__restrict self,
                                         struct icpustate const *__restrict state,
                                         u64 sysno, bool enable_except) {
	self->rsi_flags = RPC_SYSCALL_INFO_METHOD_SYSVABI_64 |
	                  RPC_SYSCALL_INFO_FREGVALID(0) |
	                  RPC_SYSCALL_INFO_FREGVALID(1) |
	                  RPC_SYSCALL_INFO_FREGVALID(2) |
	                  RPC_SYSCALL_INFO_FREGVALID(3) |
	                  RPC_SYSCALL_INFO_FREGVALID(4) |
	                  RPC_SYSCALL_INFO_FREGVALID(5);
	if (enable_except)
		self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	self->rsi_sysno   = sysno;
	self->rsi_regs[0] = gpregs_getpdi(&state->ics_gpregs);
	self->rsi_regs[1] = gpregs_getpsi(&state->ics_gpregs);
	self->rsi_regs[2] = gpregs_getpdx(&state->ics_gpregs);
	self->rsi_regs[3] = gpregs_getpcx(&state->ics_gpregs);
	self->rsi_regs[4] = gpregs_getp8(&state->ics_gpregs);
	self->rsi_regs[5] = gpregs_getp9(&state->ics_gpregs);
}
#endif /* __x86_64__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_SYSCALL_INFO_H */
