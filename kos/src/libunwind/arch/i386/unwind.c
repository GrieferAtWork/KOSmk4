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
#ifndef GUARD_LIBUNWIND_ARCH_I386_UNWIND_C
#define GUARD_LIBUNWIND_ARCH_I386_UNWIND_C 1
#define _KOS_KERNEL_SOURCE 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include "../../unwind.h"

#include <hybrid/compiler.h>

#include <hybrid/limits.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/fpu-state.h>
#include <kos/kernel/gdt.h>
#include <kos/kernel/paging.h>
#include <kos/kernel/types.h>
#include <kos/types.h>
#include <sys/ucontext.h>

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include <libunwind/cfi.h>
#include <libunwind/unwind.h>

#include "../../api.h"

#ifdef __KERNEL__
#include <kernel/paging.h>
#endif /* __KERNEL__ */


DECL_BEGIN


struct lcpustate;
struct ucpustate;
struct kcpustate;
struct scpustate;
struct icpustate;
struct fcpustate;
#ifndef __KERNEL__
struct ucontext;
struct mcontext;
#endif /* !__KERNEL__ */

/* Register accessor callbacks for a variety of known cpu context structures. */
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libuw_unwind_getreg_lcpustate)(struct lcpustate const *__restrict self, uintptr_half_t regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libuw_unwind_setreg_lcpustate)(struct lcpustate *__restrict self, uintptr_half_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libuw_unwind_getreg_ucpustate)(struct ucpustate const *__restrict self, uintptr_half_t regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libuw_unwind_setreg_ucpustate)(struct ucpustate *__restrict self, uintptr_half_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libuw_unwind_getreg_kcpustate)(struct kcpustate const *__restrict self, uintptr_half_t regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libuw_unwind_setreg_kcpustate)(struct kcpustate *__restrict self, uintptr_half_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libuw_unwind_getreg_scpustate)(struct scpustate const *__restrict self, uintptr_half_t regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libuw_unwind_setreg_scpustate)(struct scpustate *__restrict self, uintptr_half_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libuw_unwind_getreg_icpustate)(struct icpustate const *__restrict self, uintptr_half_t regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libuw_unwind_setreg_icpustate)(struct icpustate *__restrict self, uintptr_half_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libuw_unwind_getreg_fcpustate)(struct fcpustate const *__restrict self, uintptr_half_t regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libuw_unwind_setreg_fcpustate)(struct fcpustate *__restrict self, uintptr_half_t regno, void const *__restrict src);
#ifndef __KERNEL__
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libuw_unwind_getreg_ucontext)(struct ucontext const *__restrict self, uintptr_half_t regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libuw_unwind_setreg_ucontext)(struct ucontext *__restrict self, uintptr_half_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libuw_unwind_getreg_mcontext)(struct mcontext const *__restrict self, uintptr_half_t regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libuw_unwind_setreg_mcontext)(struct mcontext *__restrict self, uintptr_half_t regno, void const *__restrict src);
#endif /* !__KERNEL__ */




#ifdef __x86_64__

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_getreg_lcpustate)(struct lcpustate const *__restrict self,
                                              uintptr_half_t regno,
                                              void *__restrict dst) {
	switch (regno) {
	case CFI_X86_64_UNWIND_REGISTER_R15: *(u64 *)dst = self->lcs_r15; break;
	case CFI_X86_64_UNWIND_REGISTER_R14: *(u64 *)dst = self->lcs_r14; break;
	case CFI_X86_64_UNWIND_REGISTER_R13: *(u64 *)dst = self->lcs_r13; break;
	case CFI_X86_64_UNWIND_REGISTER_R12: *(u64 *)dst = self->lcs_r12; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP: *(u64 *)dst = self->lcs_rbp; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP: *(u64 *)dst = self->lcs_rsp; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX: *(u64 *)dst = self->lcs_rbx; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP: *(u64 *)dst = self->lcs_rip; break;
	default:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_setreg_lcpustate)(struct lcpustate *__restrict self,
                                              uintptr_half_t regno,
                                              void const *__restrict src) {
	switch (regno) {
	case CFI_X86_64_UNWIND_REGISTER_R15: self->lcs_r15 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R14: self->lcs_r14 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R13: self->lcs_r13 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R12: self->lcs_r12 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP: self->lcs_rbp = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP: self->lcs_rsp = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX: self->lcs_rbx = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP: self->lcs_rip = *(u64 const *)src; break;
	default:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_getreg_ucpustate)(struct ucpustate const *__restrict self,
                                              uintptr_half_t regno,
                                              void *__restrict dst) {
	switch (regno) {
	case CFI_X86_64_UNWIND_REGISTER_RAX:    *(u64 *)dst = self->ucs_gpregs.gp_rax; break;
	case CFI_X86_64_UNWIND_REGISTER_RDX:    *(u64 *)dst = self->ucs_gpregs.gp_rdx; break;
	case CFI_X86_64_UNWIND_REGISTER_RCX:    *(u64 *)dst = self->ucs_gpregs.gp_rcx; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX:    *(u64 *)dst = self->ucs_gpregs.gp_rbx; break;
	case CFI_X86_64_UNWIND_REGISTER_RSI:    *(u64 *)dst = self->ucs_gpregs.gp_rsi; break;
	case CFI_X86_64_UNWIND_REGISTER_RDI:    *(u64 *)dst = self->ucs_gpregs.gp_rdi; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP:    *(u64 *)dst = self->ucs_gpregs.gp_rbp; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP:    *(u64 *)dst = self->ucs_gpregs.gp_rsp; break;
	case CFI_X86_64_UNWIND_REGISTER_R8:     *(u64 *)dst = self->ucs_gpregs.gp_r8; break;
	case CFI_X86_64_UNWIND_REGISTER_R9:     *(u64 *)dst = self->ucs_gpregs.gp_r9; break;
	case CFI_X86_64_UNWIND_REGISTER_R10:    *(u64 *)dst = self->ucs_gpregs.gp_r10; break;
	case CFI_X86_64_UNWIND_REGISTER_R11:    *(u64 *)dst = self->ucs_gpregs.gp_r11; break;
	case CFI_X86_64_UNWIND_REGISTER_R12:    *(u64 *)dst = self->ucs_gpregs.gp_r12; break;
	case CFI_X86_64_UNWIND_REGISTER_R13:    *(u64 *)dst = self->ucs_gpregs.gp_r13; break;
	case CFI_X86_64_UNWIND_REGISTER_R14:    *(u64 *)dst = self->ucs_gpregs.gp_r14; break;
	case CFI_X86_64_UNWIND_REGISTER_R15:    *(u64 *)dst = self->ucs_gpregs.gp_r15; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP:    *(u64 *)dst = self->ucs_rip; break;
	case CFI_X86_64_UNWIND_REGISTER_RFLAGS: *(u64 *)dst = self->ucs_rflags; break;
	case CFI_X86_64_UNWIND_REGISTER_FSBASE: *(u64 *)dst = self->ucs_sgbase.sg_fsbase; break;
	case CFI_X86_64_UNWIND_REGISTER_GSBASE: *(u64 *)dst = self->ucs_sgbase.sg_gsbase; break;
	case CFI_X86_64_UNWIND_REGISTER_ES:     *(u64 *)dst = self->ucs_sgregs.sg_es; break;
	case CFI_X86_64_UNWIND_REGISTER_CS:     *(u64 *)dst = self->ucs_cs; break;
	case CFI_X86_64_UNWIND_REGISTER_SS:     *(u64 *)dst = self->ucs_ss; break;
	case CFI_X86_64_UNWIND_REGISTER_DS:     *(u64 *)dst = self->ucs_sgregs.sg_ds; break;
	case CFI_X86_64_UNWIND_REGISTER_FS:     *(u64 *)dst = self->ucs_sgregs.sg_fs; break;
	case CFI_X86_64_UNWIND_REGISTER_GS:     *(u64 *)dst = self->ucs_sgregs.sg_gs; break;
	default:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_setreg_ucpustate)(struct ucpustate *__restrict self,
                                              uintptr_half_t regno,
                                              void const *__restrict src) {
	switch (regno) {
	case CFI_X86_64_UNWIND_REGISTER_RAX:    self->ucs_gpregs.gp_rax = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RDX:    self->ucs_gpregs.gp_rdx = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RCX:    self->ucs_gpregs.gp_rcx = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX:    self->ucs_gpregs.gp_rbx = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RSI:    self->ucs_gpregs.gp_rsi = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RDI:    self->ucs_gpregs.gp_rdi = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP:    self->ucs_gpregs.gp_rbp = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP:    self->ucs_gpregs.gp_rsp = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R8:     self->ucs_gpregs.gp_r8 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R9:     self->ucs_gpregs.gp_r9 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R10:    self->ucs_gpregs.gp_r10 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R11:    self->ucs_gpregs.gp_r11 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R12:    self->ucs_gpregs.gp_r12 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R13:    self->ucs_gpregs.gp_r13 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R14:    self->ucs_gpregs.gp_r14 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R15:    self->ucs_gpregs.gp_r15 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP:    self->ucs_rip = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RFLAGS: self->ucs_rflags = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_FSBASE: self->ucs_sgbase.sg_fsbase = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_GSBASE: self->ucs_sgbase.sg_gsbase = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_ES:     self->ucs_sgregs.sg_es = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_CS:     self->ucs_cs = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_SS:     self->ucs_ss = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_DS:     self->ucs_sgregs.sg_ds = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_FS:     self->ucs_sgregs.sg_fs = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_GS:     self->ucs_sgregs.sg_gs = *(u64 const *)src; break;
	default:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_getreg_kcpustate)(struct kcpustate const *__restrict self,
                                              uintptr_half_t regno,
                                              void *__restrict dst) {
	switch (regno) {
	case CFI_X86_64_UNWIND_REGISTER_RAX:    *(u64 *)dst = self->kcs_gpregs.gp_rax; break;
	case CFI_X86_64_UNWIND_REGISTER_RDX:    *(u64 *)dst = self->kcs_gpregs.gp_rdx; break;
	case CFI_X86_64_UNWIND_REGISTER_RCX:    *(u64 *)dst = self->kcs_gpregs.gp_rcx; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX:    *(u64 *)dst = self->kcs_gpregs.gp_rbx; break;
	case CFI_X86_64_UNWIND_REGISTER_RSI:    *(u64 *)dst = self->kcs_gpregs.gp_rsi; break;
	case CFI_X86_64_UNWIND_REGISTER_RDI:    *(u64 *)dst = self->kcs_gpregs.gp_rdi; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP:    *(u64 *)dst = self->kcs_gpregs.gp_rbp; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP:    *(u64 *)dst = self->kcs_gpregs.gp_rsp; break;
	case CFI_X86_64_UNWIND_REGISTER_R8:     *(u64 *)dst = self->kcs_gpregs.gp_r8; break;
	case CFI_X86_64_UNWIND_REGISTER_R9:     *(u64 *)dst = self->kcs_gpregs.gp_r9; break;
	case CFI_X86_64_UNWIND_REGISTER_R10:    *(u64 *)dst = self->kcs_gpregs.gp_r10; break;
	case CFI_X86_64_UNWIND_REGISTER_R11:    *(u64 *)dst = self->kcs_gpregs.gp_r11; break;
	case CFI_X86_64_UNWIND_REGISTER_R12:    *(u64 *)dst = self->kcs_gpregs.gp_r12; break;
	case CFI_X86_64_UNWIND_REGISTER_R13:    *(u64 *)dst = self->kcs_gpregs.gp_r13; break;
	case CFI_X86_64_UNWIND_REGISTER_R14:    *(u64 *)dst = self->kcs_gpregs.gp_r14; break;
	case CFI_X86_64_UNWIND_REGISTER_R15:    *(u64 *)dst = self->kcs_gpregs.gp_r15; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP:    *(u64 *)dst = self->kcs_rip; break;
	case CFI_X86_64_UNWIND_REGISTER_RFLAGS: *(u64 *)dst = self->kcs_rflags; break;
	default:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_setreg_kcpustate)(struct kcpustate *__restrict self,
                                              uintptr_half_t regno,
                                              void const *__restrict src) {
	switch (regno) {
	case CFI_X86_64_UNWIND_REGISTER_RAX:    self->kcs_gpregs.gp_rax = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RDX:    self->kcs_gpregs.gp_rdx = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RCX:    self->kcs_gpregs.gp_rcx = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX:    self->kcs_gpregs.gp_rbx = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RSI:    self->kcs_gpregs.gp_rsi = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RDI:    self->kcs_gpregs.gp_rdi = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP:    self->kcs_gpregs.gp_rbp = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP:    self->kcs_gpregs.gp_rsp = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R8:     self->kcs_gpregs.gp_r8 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R9:     self->kcs_gpregs.gp_r9 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R10:    self->kcs_gpregs.gp_r10 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R11:    self->kcs_gpregs.gp_r11 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R12:    self->kcs_gpregs.gp_r12 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R13:    self->kcs_gpregs.gp_r13 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R14:    self->kcs_gpregs.gp_r14 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R15:    self->kcs_gpregs.gp_r15 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP:    self->kcs_rip = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RFLAGS: self->kcs_rflags = *(u64 const *)src; break;
	default:
		return false;
	}
	return true;
}

#ifdef __KERNEL__
INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_getreg_scpustate)(struct scpustate const *__restrict self,
                                              uintptr_half_t regno,
                                              void *__restrict dst) {
	switch (regno) {
	case CFI_X86_64_UNWIND_REGISTER_RAX:    *(u64 *)dst = self->scs_gpregs.gp_rax; break;
	case CFI_X86_64_UNWIND_REGISTER_RDX:    *(u64 *)dst = self->scs_gpregs.gp_rdx; break;
	case CFI_X86_64_UNWIND_REGISTER_RCX:    *(u64 *)dst = self->scs_gpregs.gp_rcx; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX:    *(u64 *)dst = self->scs_gpregs.gp_rbx; break;
	case CFI_X86_64_UNWIND_REGISTER_RSI:    *(u64 *)dst = self->scs_gpregs.gp_rsi; break;
	case CFI_X86_64_UNWIND_REGISTER_RDI:    *(u64 *)dst = self->scs_gpregs.gp_rdi; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP:    *(u64 *)dst = self->scs_gpregs.gp_rbp; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP:    *(u64 *)dst = self->scs_irregs.ir_rsp; break;
	case CFI_X86_64_UNWIND_REGISTER_R8:     *(u64 *)dst = self->scs_gpregs.gp_r8; break;
	case CFI_X86_64_UNWIND_REGISTER_R9:     *(u64 *)dst = self->scs_gpregs.gp_r9; break;
	case CFI_X86_64_UNWIND_REGISTER_R10:    *(u64 *)dst = self->scs_gpregs.gp_r10; break;
	case CFI_X86_64_UNWIND_REGISTER_R11:    *(u64 *)dst = self->scs_gpregs.gp_r11; break;
	case CFI_X86_64_UNWIND_REGISTER_R12:    *(u64 *)dst = self->scs_gpregs.gp_r12; break;
	case CFI_X86_64_UNWIND_REGISTER_R13:    *(u64 *)dst = self->scs_gpregs.gp_r13; break;
	case CFI_X86_64_UNWIND_REGISTER_R14:    *(u64 *)dst = self->scs_gpregs.gp_r14; break;
	case CFI_X86_64_UNWIND_REGISTER_R15:    *(u64 *)dst = self->scs_gpregs.gp_r15; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP:    *(u64 *)dst = self->scs_irregs.ir_rip; break;
	case CFI_X86_64_UNWIND_REGISTER_RFLAGS: *(u64 *)dst = self->scs_irregs.ir_rflags; break;
	case CFI_X86_64_UNWIND_REGISTER_ES:     *(u64 *)dst = self->scs_sgregs.sg_es; break;
	case CFI_X86_64_UNWIND_REGISTER_CS:     *(u64 *)dst = self->scs_irregs.ir_cs; break;
	case CFI_X86_64_UNWIND_REGISTER_SS:     *(u64 *)dst = self->scs_irregs.ir_ss; break;
	case CFI_X86_64_UNWIND_REGISTER_DS:     *(u64 *)dst = self->scs_sgregs.sg_ds; break;
	case CFI_X86_64_UNWIND_REGISTER_FS:     *(u64 *)dst = self->scs_sgregs.sg_fs; break;
	case CFI_X86_64_UNWIND_REGISTER_GS:     *(u64 *)dst = self->scs_sgregs.sg_gs; break;
	case CFI_X86_64_UNWIND_REGISTER_FSBASE: *(u64 *)dst = self->scs_sgbase.sg_fsbase; break;
	case CFI_X86_64_UNWIND_REGISTER_GSBASE: *(u64 *)dst = self->scs_sgbase.sg_gsbase; break;
	default:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_setreg_scpustate)(struct scpustate *__restrict self,
                                              uintptr_half_t regno,
                                              void const *__restrict src) {
	switch (regno) {
	case CFI_X86_64_UNWIND_REGISTER_RAX:    self->scs_gpregs.gp_rax = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RDX:    self->scs_gpregs.gp_rdx = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RCX:    self->scs_gpregs.gp_rcx = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX:    self->scs_gpregs.gp_rbx = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RSI:    self->scs_gpregs.gp_rsi = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RDI:    self->scs_gpregs.gp_rdi = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP:    self->scs_gpregs.gp_rbp = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP:    self->scs_irregs.ir_rsp = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R8:     self->scs_gpregs.gp_r8 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R9:     self->scs_gpregs.gp_r9 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R10:    self->scs_gpregs.gp_r10 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R11:    self->scs_gpregs.gp_r11 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R12:    self->scs_gpregs.gp_r12 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R13:    self->scs_gpregs.gp_r13 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R14:    self->scs_gpregs.gp_r14 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R15:    self->scs_gpregs.gp_r15 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP:    self->scs_irregs.ir_rip = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RFLAGS: self->scs_irregs.ir_rflags = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_ES:     self->scs_sgregs.sg_es = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_CS:     self->scs_irregs.ir_cs = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_SS:     self->scs_irregs.ir_ss = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_DS:     self->scs_sgregs.sg_ds = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_FS:     self->scs_sgregs.sg_fs = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_GS:     self->scs_sgregs.sg_gs = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_FSBASE: self->scs_sgbase.sg_fsbase = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_GSBASE: self->scs_sgbase.sg_gsbase = *(u64 const *)src; break;
	default:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_getreg_icpustate)(struct icpustate const *__restrict self,
                                              uintptr_half_t regno,
                                              void *__restrict dst) {
	switch (regno) {
	case CFI_X86_64_UNWIND_REGISTER_RAX:    *(u64 *)dst = self->ics_gpregs.gp_rax; break;
	case CFI_X86_64_UNWIND_REGISTER_RDX:    *(u64 *)dst = self->ics_gpregs.gp_rdx; break;
	case CFI_X86_64_UNWIND_REGISTER_RCX:    *(u64 *)dst = self->ics_gpregs.gp_rcx; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX:    *(u64 *)dst = self->ics_gpregs.gp_rbx; break;
	case CFI_X86_64_UNWIND_REGISTER_RSI:    *(u64 *)dst = self->ics_gpregs.gp_rsi; break;
	case CFI_X86_64_UNWIND_REGISTER_RDI:    *(u64 *)dst = self->ics_gpregs.gp_rdi; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP:    *(u64 *)dst = self->ics_gpregs.gp_rbp; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP:    *(u64 *)dst = self->ics_irregs.ir_rsp; break;
	case CFI_X86_64_UNWIND_REGISTER_R8:     *(u64 *)dst = self->ics_gpregs.gp_r8; break;
	case CFI_X86_64_UNWIND_REGISTER_R9:     *(u64 *)dst = self->ics_gpregs.gp_r9; break;
	case CFI_X86_64_UNWIND_REGISTER_R10:    *(u64 *)dst = self->ics_gpregs.gp_r10; break;
	case CFI_X86_64_UNWIND_REGISTER_R11:    *(u64 *)dst = self->ics_gpregs.gp_r11; break;
	case CFI_X86_64_UNWIND_REGISTER_R12:    *(u64 *)dst = self->ics_gpregs.gp_r12; break;
	case CFI_X86_64_UNWIND_REGISTER_R13:    *(u64 *)dst = self->ics_gpregs.gp_r13; break;
	case CFI_X86_64_UNWIND_REGISTER_R14:    *(u64 *)dst = self->ics_gpregs.gp_r14; break;
	case CFI_X86_64_UNWIND_REGISTER_R15:    *(u64 *)dst = self->ics_gpregs.gp_r15; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP:    *(u64 *)dst = self->ics_irregs.ir_rip; break;
	case CFI_X86_64_UNWIND_REGISTER_RFLAGS: *(u64 *)dst = self->ics_irregs.ir_rflags; break;
	case CFI_X86_64_UNWIND_REGISTER_CS:     *(u64 *)dst = self->ics_irregs.ir_cs; break;
	case CFI_X86_64_UNWIND_REGISTER_SS:     *(u64 *)dst = self->ics_irregs.ir_ss; break;
	default:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_setreg_icpustate)(struct icpustate *__restrict self,
                                              uintptr_half_t regno,
                                              void const *__restrict src) {
	switch (regno) {
	case CFI_X86_64_UNWIND_REGISTER_RAX:    self->ics_gpregs.gp_rax = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RDX:    self->ics_gpregs.gp_rdx = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RCX:    self->ics_gpregs.gp_rcx = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX:    self->ics_gpregs.gp_rbx = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RSI:    self->ics_gpregs.gp_rsi = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RDI:    self->ics_gpregs.gp_rdi = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP:    self->ics_gpregs.gp_rbp = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP:    self->ics_irregs.ir_rsp = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R8:     self->ics_gpregs.gp_r8 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R9:     self->ics_gpregs.gp_r9 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R10:    self->ics_gpregs.gp_r10 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R11:    self->ics_gpregs.gp_r11 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R12:    self->ics_gpregs.gp_r12 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R13:    self->ics_gpregs.gp_r13 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R14:    self->ics_gpregs.gp_r14 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R15:    self->ics_gpregs.gp_r15 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP:    self->ics_irregs.ir_rip = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RFLAGS: self->ics_irregs.ir_rflags = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_CS:     self->ics_irregs.ir_cs = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_SS:     self->ics_irregs.ir_ss = *(u64 const *)src; break;
	default:
		return false;
	}
	return true;
}
#endif /* __KERNEL__ */

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_getreg_fcpustate)(struct fcpustate const *__restrict self,
                                              uintptr_half_t regno,
                                              void *__restrict dst) {
	switch (regno) {
	case CFI_X86_64_UNWIND_REGISTER_RAX:    *(u64 *)dst = self->fcs_gpregs.gp_rax; break;
	case CFI_X86_64_UNWIND_REGISTER_RDX:    *(u64 *)dst = self->fcs_gpregs.gp_rdx; break;
	case CFI_X86_64_UNWIND_REGISTER_RCX:    *(u64 *)dst = self->fcs_gpregs.gp_rcx; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX:    *(u64 *)dst = self->fcs_gpregs.gp_rbx; break;
	case CFI_X86_64_UNWIND_REGISTER_RSI:    *(u64 *)dst = self->fcs_gpregs.gp_rsi; break;
	case CFI_X86_64_UNWIND_REGISTER_RDI:    *(u64 *)dst = self->fcs_gpregs.gp_rdi; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP:    *(u64 *)dst = self->fcs_gpregs.gp_rbp; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP:    *(u64 *)dst = self->fcs_gpregs.gp_rsp; break;
	case CFI_X86_64_UNWIND_REGISTER_R8:     *(u64 *)dst = self->fcs_gpregs.gp_r8; break;
	case CFI_X86_64_UNWIND_REGISTER_R9:     *(u64 *)dst = self->fcs_gpregs.gp_r9; break;
	case CFI_X86_64_UNWIND_REGISTER_R10:    *(u64 *)dst = self->fcs_gpregs.gp_r10; break;
	case CFI_X86_64_UNWIND_REGISTER_R11:    *(u64 *)dst = self->fcs_gpregs.gp_r11; break;
	case CFI_X86_64_UNWIND_REGISTER_R12:    *(u64 *)dst = self->fcs_gpregs.gp_r12; break;
	case CFI_X86_64_UNWIND_REGISTER_R13:    *(u64 *)dst = self->fcs_gpregs.gp_r13; break;
	case CFI_X86_64_UNWIND_REGISTER_R14:    *(u64 *)dst = self->fcs_gpregs.gp_r14; break;
	case CFI_X86_64_UNWIND_REGISTER_R15:    *(u64 *)dst = self->fcs_gpregs.gp_r15; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP:    *(u64 *)dst = self->fcs_rip; break;
	case CFI_X86_64_UNWIND_REGISTER_RFLAGS: *(u64 *)dst = self->fcs_rflags; break;
	case CFI_X86_64_UNWIND_REGISTER_ES:     *(u64 *)dst = self->fcs_sgregs.sg_es; break;
	case CFI_X86_64_UNWIND_REGISTER_CS:     *(u64 *)dst = self->fcs_sgregs.sg_cs; break;
	case CFI_X86_64_UNWIND_REGISTER_SS:     *(u64 *)dst = self->fcs_sgregs.sg_ss; break;
	case CFI_X86_64_UNWIND_REGISTER_DS:     *(u64 *)dst = self->fcs_sgregs.sg_ds; break;
	case CFI_X86_64_UNWIND_REGISTER_FS:     *(u64 *)dst = self->fcs_sgregs.sg_fs; break;
	case CFI_X86_64_UNWIND_REGISTER_GS:     *(u64 *)dst = self->fcs_sgregs.sg_gs; break;
	case CFI_X86_64_UNWIND_REGISTER_FSBASE: *(u64 *)dst = self->fcs_sgbase.sg_fsbase; break;
	case CFI_X86_64_UNWIND_REGISTER_GSBASE: *(u64 *)dst = self->fcs_sgbase.sg_gsbase; break;
	case CFI_X86_64_UNWIND_REGISTER_TR:     *(u64 *)dst = self->fcs_sgregs.sg_tr; break;
	case CFI_X86_64_UNWIND_REGISTER_LDTR:   *(u64 *)dst = self->fcs_sgregs.sg_ldt; break;
	default:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_setreg_fcpustate)(struct fcpustate *__restrict self,
                                              uintptr_half_t regno,
                                              void const *__restrict src) {
	switch (regno) {
	case CFI_X86_64_UNWIND_REGISTER_RAX:    self->fcs_gpregs.gp_rax = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RDX:    self->fcs_gpregs.gp_rdx = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RCX:    self->fcs_gpregs.gp_rcx = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX:    self->fcs_gpregs.gp_rbx = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RSI:    self->fcs_gpregs.gp_rsi = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RDI:    self->fcs_gpregs.gp_rdi = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP:    self->fcs_gpregs.gp_rbp = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP:    self->fcs_gpregs.gp_rsp = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R8:     self->fcs_gpregs.gp_r8 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R9:     self->fcs_gpregs.gp_r9 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R10:    self->fcs_gpregs.gp_r10 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R11:    self->fcs_gpregs.gp_r11 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R12:    self->fcs_gpregs.gp_r12 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R13:    self->fcs_gpregs.gp_r13 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R14:    self->fcs_gpregs.gp_r14 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_R15:    self->fcs_gpregs.gp_r15 = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP:    self->fcs_rip = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_RFLAGS: self->fcs_rflags = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_ES:     self->fcs_sgregs.sg_es = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_CS:     self->fcs_sgregs.sg_cs = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_SS:     self->fcs_sgregs.sg_ss = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_DS:     self->fcs_sgregs.sg_ds = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_FS:     self->fcs_sgregs.sg_fs = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_GS:     self->fcs_sgregs.sg_gs = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_FSBASE: self->fcs_sgbase.sg_fsbase = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_GSBASE: self->fcs_sgbase.sg_gsbase = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_TR:     self->fcs_sgregs.sg_tr = *(u64 const *)src; break;
	case CFI_X86_64_UNWIND_REGISTER_LDTR:   self->fcs_sgregs.sg_ldt = *(u64 const *)src; break;
	default:
		return false;
	}
	return true;
}

#ifndef __KERNEL__
DEFINE_INTERN_ALIAS(libuw_unwind_getreg_ucontext, libuw_unwind_getreg_mcontext);
DEFINE_INTERN_ALIAS(libuw_unwind_setreg_ucontext, libuw_unwind_setreg_mcontext);
INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_getreg_mcontext)(struct mcontext const *__restrict self,
                                             uintptr_half_t regno,
                                             void *__restrict dst) {
	switch (regno) {

	case CFI_X86_64_UNWIND_REGISTER_MM0 ... CFI_X86_64_UNWIND_REGISTER_MM7:
		regno -= CFI_X86_64_UNWIND_REGISTER_MM0;
		goto do_fpreg;
	case CFI_X86_64_UNWIND_REGISTER_ST0 ... CFI_X86_64_UNWIND_REGISTER_ST7:
		regno -= CFI_X86_64_UNWIND_REGISTER_ST0;
do_fpreg:
		if (self->mc_flags & MCONTEXT_FLAG_HAVEXFPU) {
			memcpy((byte_t *)dst, &self->mc_fpu.f_xsave.fs_regs[regno], 16);
		} else if (self->mc_flags & MCONTEXT_FLAG_HAVESFPU) {
			memcpy((byte_t *)dst, &self->mc_fpu.f_ssave.fs_regs[regno], 10);
			memset((byte_t *)dst + 10, 0, 6);
		} else {
			goto nope;
		}
		break;

	case CFI_X86_64_UNWIND_REGISTER_XMM0 ... CFI_X86_64_UNWIND_REGISTER_XMM15:
		regno -= CFI_X86_64_UNWIND_REGISTER_XMM0;
		if (self->mc_flags & MCONTEXT_FLAG_HAVEXFPU) {
			memcpy((byte_t *)dst, &self->mc_fpu.f_xsave.fs_xmm[regno], 16);
		} else {
			goto nope;
		}
		break;

	case CFI_X86_64_UNWIND_REGISTER_FCW:
		if (self->mc_flags & MCONTEXT_FLAG_HAVEXFPU) {
			*(u32 *)dst = self->mc_fpu.f_xsave.fs_fcw;
		} else if (self->mc_flags & MCONTEXT_FLAG_HAVESFPU) {
			*(u32 *)dst = self->mc_fpu.f_ssave.fs_fcw;
		} else {
			goto nope;
		}
		break;

	case CFI_X86_64_UNWIND_REGISTER_FSW:
		if (self->mc_flags & MCONTEXT_FLAG_HAVEXFPU) {
			*(u32 *)dst = self->mc_fpu.f_xsave.fs_fsw;
		} else if (self->mc_flags & MCONTEXT_FLAG_HAVESFPU) {
			*(u32 *)dst = self->mc_fpu.f_ssave.fs_fsw;
		} else {
			goto nope;
		}
		break;

	case CFI_X86_64_UNWIND_REGISTER_MXCSR:
		if (self->mc_flags & MCONTEXT_FLAG_HAVEXFPU) {
			*(u32 *)dst = self->mc_fpu.f_xsave.fs_mxcsr;
		} else {
			goto nope;
		}
		break;

	default:
		return libuw_unwind_getreg_ucpustate(&self->mc_context, regno, dst);
nope:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_setreg_mcontext)(struct mcontext *__restrict self,
                                             uintptr_half_t regno,
                                             void const *__restrict src) {
	switch (regno) {

	case CFI_X86_64_UNWIND_REGISTER_MM0 ... CFI_X86_64_UNWIND_REGISTER_MM7:
		regno -= CFI_X86_64_UNWIND_REGISTER_MM0;
		goto do_fpreg;
	case CFI_X86_64_UNWIND_REGISTER_ST0 ... CFI_X86_64_UNWIND_REGISTER_ST7:
		regno -= CFI_X86_64_UNWIND_REGISTER_ST0;
do_fpreg:
		if (self->mc_flags & MCONTEXT_FLAG_HAVEXFPU) {
			memcpy(&self->mc_fpu.f_xsave.fs_regs[regno], src, 16);
		} else if (self->mc_flags & MCONTEXT_FLAG_HAVESFPU) {
			memcpy(&self->mc_fpu.f_ssave.fs_regs[regno], src, 10);
		} else {
			goto nope;
		}
		break;

	case CFI_X86_64_UNWIND_REGISTER_XMM0 ... CFI_X86_64_UNWIND_REGISTER_XMM15:
		regno -= CFI_X86_64_UNWIND_REGISTER_XMM0;
		if (self->mc_flags & MCONTEXT_FLAG_HAVEXFPU) {
			memcpy(&self->mc_fpu.f_xsave.fs_xmm[regno], src, 16);
		} else {
			goto nope;
		}
		break;

	case CFI_X86_64_UNWIND_REGISTER_FCW:
		if (self->mc_flags & MCONTEXT_FLAG_HAVEXFPU) {
			self->mc_fpu.f_xsave.fs_fcw = (u16)*(u32 const *)src;
		} else if (self->mc_flags & MCONTEXT_FLAG_HAVESFPU) {
			self->mc_fpu.f_ssave.fs_fcw = (u16)*(u32 const *)src;
		} else {
			goto nope;
		}
		break;

	case CFI_X86_64_UNWIND_REGISTER_FSW:
		if (self->mc_flags & MCONTEXT_FLAG_HAVEXFPU) {
			self->mc_fpu.f_xsave.fs_fsw = (u16)*(u32 const *)src;
		} else if (self->mc_flags & MCONTEXT_FLAG_HAVESFPU) {
			self->mc_fpu.f_ssave.fs_fsw = (u16)*(u32 const *)src;
		} else {
			goto nope;
		}
		break;

	case CFI_X86_64_UNWIND_REGISTER_MXCSR:
		if (self->mc_flags & MCONTEXT_FLAG_HAVEXFPU) {
			self->mc_fpu.f_xsave.fs_mxcsr = *(u32 const *)src;
		} else {
			goto nope;
		}
		break;

	default:
		return libuw_unwind_setreg_ucpustate(&self->mc_context, regno, src);
nope:
		return false;
	}
	return true;
}
#endif /* !__KERNEL__ */


#else /* __x86_64__ */

STATIC_ASSERT(offsetof(struct gpregs, gp_edi) == OFFSET_GPREGS_EDI);
STATIC_ASSERT(offsetof(struct gpregs, gp_esi) == OFFSET_GPREGS_ESI);
STATIC_ASSERT(offsetof(struct gpregs, gp_ebp) == OFFSET_GPREGS_EBP);
STATIC_ASSERT(offsetof(struct gpregs, gp_esp) == OFFSET_GPREGS_ESP);
STATIC_ASSERT(offsetof(struct gpregs, gp_ebx) == OFFSET_GPREGS_EBX);
STATIC_ASSERT(offsetof(struct gpregs, gp_edx) == OFFSET_GPREGS_EDX);
STATIC_ASSERT(offsetof(struct gpregs, gp_ecx) == OFFSET_GPREGS_ECX);
STATIC_ASSERT(offsetof(struct gpregs, gp_eax) == OFFSET_GPREGS_EAX);
STATIC_ASSERT(sizeof(struct gpregs)          == SIZEOF_GPREGS);

STATIC_ASSERT(offsetof(struct sgregs, sg_gs) == OFFSET_SGREGS_GS);
STATIC_ASSERT(offsetof(struct sgregs, sg_fs) == OFFSET_SGREGS_FS);
STATIC_ASSERT(offsetof(struct sgregs, sg_es) == OFFSET_SGREGS_ES);
STATIC_ASSERT(offsetof(struct sgregs, sg_ds) == OFFSET_SGREGS_DS);
STATIC_ASSERT(sizeof(struct sgregs)          == SIZEOF_SGREGS);

STATIC_ASSERT(offsetof(struct coregs, co_cr0) == OFFSET_COREGS_CR0);
STATIC_ASSERT(offsetof(struct coregs, co_cr2) == OFFSET_COREGS_CR2);
STATIC_ASSERT(offsetof(struct coregs, co_cr3) == OFFSET_COREGS_CR3);
STATIC_ASSERT(offsetof(struct coregs, co_cr4) == OFFSET_COREGS_CR4);
STATIC_ASSERT(sizeof(struct coregs)           == SIZEOF_COREGS);

STATIC_ASSERT(offsetof(struct drregs, dr_dr0) == OFFSET_DRREGS_DR0);
STATIC_ASSERT(offsetof(struct drregs, dr_dr1) == OFFSET_DRREGS_DR1);
STATIC_ASSERT(offsetof(struct drregs, dr_dr2) == OFFSET_DRREGS_DR2);
STATIC_ASSERT(offsetof(struct drregs, dr_dr3) == OFFSET_DRREGS_DR3);
STATIC_ASSERT(offsetof(struct drregs, dr_dr6) == OFFSET_DRREGS_DR6);
STATIC_ASSERT(offsetof(struct drregs, dr_dr7) == OFFSET_DRREGS_DR7);
STATIC_ASSERT(sizeof(struct drregs)           == SIZEOF_DRREGS);

STATIC_ASSERT(sizeof(struct irregs_kernel)              == SIZEOF_IRREGS_KERNEL);
STATIC_ASSERT(sizeof(struct irregs_user)                == SIZEOF_IRREGS_USER);
STATIC_ASSERT(sizeof(struct irregs_vm86)                == SIZEOF_IRREGS_VM86);
STATIC_ASSERT(offsetof(struct irregs_kernel, ir_eip)    == OFFSET_IRREGS_EIP);
STATIC_ASSERT(offsetof(struct irregs_user, ir_eip)      == OFFSET_IRREGS_EIP);
STATIC_ASSERT(offsetof(struct irregs_vm86, ir_eip)      == OFFSET_IRREGS_EIP);
STATIC_ASSERT(offsetof(struct irregs_kernel, ir_cs)     == OFFSET_IRREGS_CS);
STATIC_ASSERT(offsetof(struct irregs_user, ir_cs)       == OFFSET_IRREGS_CS);
STATIC_ASSERT(offsetof(struct irregs_vm86, ir_cs)       == OFFSET_IRREGS_CS);
STATIC_ASSERT(offsetof(struct irregs_kernel, ir_eflags) == OFFSET_IRREGS_EFLAGS);
STATIC_ASSERT(offsetof(struct irregs_user, ir_eflags)   == OFFSET_IRREGS_EFLAGS);
STATIC_ASSERT(offsetof(struct irregs_vm86, ir_eflags)   == OFFSET_IRREGS_EFLAGS);
STATIC_ASSERT(offsetof(struct irregs_user, ir_esp)      == OFFSET_IRREGS_ESP);
STATIC_ASSERT(offsetof(struct irregs_vm86, ir_esp)      == OFFSET_IRREGS_ESP);
STATIC_ASSERT(offsetof(struct irregs_user, ir_ss)       == OFFSET_IRREGS_SS);
STATIC_ASSERT(offsetof(struct irregs_vm86, ir_ss)       == OFFSET_IRREGS_SS);
STATIC_ASSERT(offsetof(struct irregs_vm86, ir_es)       == OFFSET_IRREGS_ES);
STATIC_ASSERT(offsetof(struct irregs_vm86, ir_ds)       == OFFSET_IRREGS_DS);
STATIC_ASSERT(offsetof(struct irregs_vm86, ir_fs)       == OFFSET_IRREGS_FS);
STATIC_ASSERT(offsetof(struct irregs_vm86, ir_gs)       == OFFSET_IRREGS_GS);

#ifdef __KERNEL__
#define MY_CS  SEGMENT_KERNEL_CODE
#define MY_SS  SEGMENT_KERNEL_DATA
#define MY_FS  SEGMENT_KERNEL_FSBASE
#define MY_GS  __rdgs()
#else /* __KERNEL__ */
#define MY_CS  SEGMENT_USER_CODE_RPL
#define MY_SS  SEGMENT_USER_DATA_RPL
#define MY_FS  __rdfs()
#define MY_GS  __rdgs()
#endif /* !__KERNEL__ */
#define MY_DS  SEGMENT_USER_DATA_RPL
#define MY_ES  SEGMENT_USER_DATA_RPL


INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_getreg_lcpustate)(struct lcpustate const *__restrict self,
                                              uintptr_half_t regno,
                                              void *__restrict dst) {
	switch (regno) {
	case CFI_386_UNWIND_REGISTER_EDI:    *(u32 *)dst = self->lcs_edi; break;
	case CFI_386_UNWIND_REGISTER_ESI:    *(u32 *)dst = self->lcs_esi; break;
	case CFI_386_UNWIND_REGISTER_EBP:    *(u32 *)dst = self->lcs_ebp; break;
	case CFI_386_UNWIND_REGISTER_ESP:    *(u32 *)dst = self->lcs_esp; break;
	case CFI_386_UNWIND_REGISTER_EBX:    *(u32 *)dst = self->lcs_ebx; break;
	case CFI_386_UNWIND_REGISTER_EIP:    *(u32 *)dst = self->lcs_eip; break;
	case CFI_386_UNWIND_REGISTER_GS:     *(u32 *)dst = MY_GS; break;
	case CFI_386_UNWIND_REGISTER_FS:     *(u32 *)dst = MY_FS; break;
	case CFI_386_UNWIND_REGISTER_ES:     *(u32 *)dst = MY_ES; break;
	case CFI_386_UNWIND_REGISTER_DS:     *(u32 *)dst = MY_DS; break;
	case CFI_386_UNWIND_REGISTER_CS:     *(u32 *)dst = MY_CS; break;
	case CFI_386_UNWIND_REGISTER_SS:     *(u32 *)dst = MY_SS; break;
	case CFI_386_UNWIND_REGISTER_EFLAGS: *(u32 *)dst = EFLAGS_IF; break;
	default:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_setreg_lcpustate)(struct lcpustate *__restrict self,
                                              uintptr_half_t regno,
                                              void const *__restrict src) {
	switch (regno) {
	case CFI_386_UNWIND_REGISTER_EDI:    self->lcs_edi = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ESI:    self->lcs_esi = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EBP:    self->lcs_ebp = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ESP:    self->lcs_esp = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EBX:    self->lcs_ebx = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EIP:    self->lcs_eip = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_GS:     return *(u32 const *)src == MY_GS; break;
	case CFI_386_UNWIND_REGISTER_FS:     return *(u32 const *)src == MY_FS; break;
	case CFI_386_UNWIND_REGISTER_ES:     return *(u32 const *)src == MY_ES; break;
	case CFI_386_UNWIND_REGISTER_DS:     return *(u32 const *)src == MY_DS; break;
	case CFI_386_UNWIND_REGISTER_CS:     return *(u32 const *)src == MY_CS; break;
	case CFI_386_UNWIND_REGISTER_SS:     return *(u32 const *)src == MY_SS; break;
	case CFI_386_UNWIND_REGISTER_EFLAGS: return (*(u32 const *)src & EFLAGS_IF) != 0; break;
	default:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_getreg_ucpustate)(struct ucpustate const *__restrict self,
                                              uintptr_half_t regno,
                                              void *__restrict dst) {
	switch (regno) {
	case CFI_386_UNWIND_REGISTER_EDI:    *(u32 *)dst = self->ucs_gpregs.gp_edi; break;
	case CFI_386_UNWIND_REGISTER_ESI:    *(u32 *)dst = self->ucs_gpregs.gp_esi; break;
	case CFI_386_UNWIND_REGISTER_EBP:    *(u32 *)dst = self->ucs_gpregs.gp_ebp; break;
	case CFI_386_UNWIND_REGISTER_ESP:    *(u32 *)dst = self->ucs_gpregs.gp_esp; break;
	case CFI_386_UNWIND_REGISTER_EBX:    *(u32 *)dst = self->ucs_gpregs.gp_ebx; break;
	case CFI_386_UNWIND_REGISTER_EDX:    *(u32 *)dst = self->ucs_gpregs.gp_edx; break;
	case CFI_386_UNWIND_REGISTER_ECX:    *(u32 *)dst = self->ucs_gpregs.gp_ecx; break;
	case CFI_386_UNWIND_REGISTER_EAX:    *(u32 *)dst = self->ucs_gpregs.gp_eax; break;
	case CFI_386_UNWIND_REGISTER_GS:     *(u32 *)dst = self->ucs_sgregs.sg_gs; break;
	case CFI_386_UNWIND_REGISTER_FS:     *(u32 *)dst = self->ucs_sgregs.sg_fs; break;
	case CFI_386_UNWIND_REGISTER_ES:     *(u32 *)dst = self->ucs_sgregs.sg_es; break;
	case CFI_386_UNWIND_REGISTER_DS:     *(u32 *)dst = self->ucs_sgregs.sg_ds; break;
	case CFI_386_UNWIND_REGISTER_CS:     *(u32 *)dst = self->ucs_cs; break;
	case CFI_386_UNWIND_REGISTER_SS:     *(u32 *)dst = self->ucs_ss; break;
	case CFI_386_UNWIND_REGISTER_EFLAGS: *(u32 *)dst = self->ucs_eflags; break;
	case CFI_386_UNWIND_REGISTER_EIP:    *(u32 *)dst = self->ucs_eip; break;
	default:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_setreg_ucpustate)(struct ucpustate *__restrict self,
                                              uintptr_half_t regno,
                                              void const *__restrict src) {
	switch (regno) {
	case CFI_386_UNWIND_REGISTER_EDI:    self->ucs_gpregs.gp_edi = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ESI:    self->ucs_gpregs.gp_esi = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EBP:    self->ucs_gpregs.gp_ebp = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ESP:    self->ucs_gpregs.gp_esp = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EBX:    self->ucs_gpregs.gp_ebx = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EDX:    self->ucs_gpregs.gp_edx = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ECX:    self->ucs_gpregs.gp_ecx = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EAX:    self->ucs_gpregs.gp_eax = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_GS:     self->ucs_sgregs.sg_gs = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_FS:     self->ucs_sgregs.sg_fs = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ES:     self->ucs_sgregs.sg_es = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_DS:     self->ucs_sgregs.sg_ds = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_CS:     self->ucs_cs = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_SS:     self->ucs_ss = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EFLAGS: self->ucs_eflags = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EIP:    self->ucs_eip = *(u32 const *)src; break;
	default:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_getreg_kcpustate)(struct kcpustate const *__restrict self,
                                              uintptr_half_t regno,
                                              void *__restrict dst) {
	switch (regno) {
	case CFI_386_UNWIND_REGISTER_EDI:    *(u32 *)dst = self->kcs_gpregs.gp_edi; break;
	case CFI_386_UNWIND_REGISTER_ESI:    *(u32 *)dst = self->kcs_gpregs.gp_esi; break;
	case CFI_386_UNWIND_REGISTER_EBP:    *(u32 *)dst = self->kcs_gpregs.gp_ebp; break;
	case CFI_386_UNWIND_REGISTER_ESP:    *(u32 *)dst = self->kcs_gpregs.gp_esp; break;
	case CFI_386_UNWIND_REGISTER_EBX:    *(u32 *)dst = self->kcs_gpregs.gp_ebx; break;
	case CFI_386_UNWIND_REGISTER_EDX:    *(u32 *)dst = self->kcs_gpregs.gp_edx; break;
	case CFI_386_UNWIND_REGISTER_ECX:    *(u32 *)dst = self->kcs_gpregs.gp_ecx; break;
	case CFI_386_UNWIND_REGISTER_EAX:    *(u32 *)dst = self->kcs_gpregs.gp_eax; break;
	case CFI_386_UNWIND_REGISTER_EFLAGS: *(u32 *)dst = self->kcs_eflags; break;
	case CFI_386_UNWIND_REGISTER_EIP:    *(u32 *)dst = self->kcs_eip; break;
	case CFI_386_UNWIND_REGISTER_GS:     *(u32 *)dst = MY_GS; break;
	case CFI_386_UNWIND_REGISTER_FS:     *(u32 *)dst = MY_FS; break;
	case CFI_386_UNWIND_REGISTER_ES:     *(u32 *)dst = MY_ES; break;
	case CFI_386_UNWIND_REGISTER_DS:     *(u32 *)dst = MY_DS; break;
	case CFI_386_UNWIND_REGISTER_CS:     *(u32 *)dst = MY_CS; break;
	case CFI_386_UNWIND_REGISTER_SS:     *(u32 *)dst = MY_SS; break;
	default:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_setreg_kcpustate)(struct kcpustate *__restrict self,
                                              uintptr_half_t regno,
                                              void const *__restrict src) {
	switch (regno) {
	case CFI_386_UNWIND_REGISTER_EDI:    self->kcs_gpregs.gp_edi = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ESI:    self->kcs_gpregs.gp_esi = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EBP:    self->kcs_gpregs.gp_ebp = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ESP:    self->kcs_gpregs.gp_esp = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EBX:    self->kcs_gpregs.gp_ebx = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EDX:    self->kcs_gpregs.gp_edx = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ECX:    self->kcs_gpregs.gp_ecx = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EAX:    self->kcs_gpregs.gp_eax = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EFLAGS: self->kcs_eflags = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EIP:    self->kcs_eip = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_GS:     return *(u32 const *)src == MY_GS; break;
	case CFI_386_UNWIND_REGISTER_FS:     return *(u32 const *)src == MY_FS; break;
	case CFI_386_UNWIND_REGISTER_ES:     return *(u32 const *)src == MY_ES; break;
	case CFI_386_UNWIND_REGISTER_DS:     return *(u32 const *)src == MY_DS; break;
	case CFI_386_UNWIND_REGISTER_CS:     return *(u32 const *)src == MY_CS; break;
	case CFI_386_UNWIND_REGISTER_SS:     return *(u32 const *)src == MY_SS; break;
	default:
		return false;
	}
	return true;
}


#ifdef __KERNEL__
INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_getreg_scpustate)(struct scpustate const *__restrict self,
                                              uintptr_half_t regno,
                                              void *__restrict dst) {
	switch (regno) {
	case CFI_386_UNWIND_REGISTER_EDI:    *(u32 *)dst = self->scs_gpregs.gp_edi; break;
	case CFI_386_UNWIND_REGISTER_ESI:    *(u32 *)dst = self->scs_gpregs.gp_esi; break;
	case CFI_386_UNWIND_REGISTER_EBP:    *(u32 *)dst = self->scs_gpregs.gp_ebp; break;
	case CFI_386_UNWIND_REGISTER_ESP:    *(u32 *)dst = SCPUSTATE_SP(*self); break;
	case CFI_386_UNWIND_REGISTER_EBX:    *(u32 *)dst = self->scs_gpregs.gp_ebx; break;
	case CFI_386_UNWIND_REGISTER_EDX:    *(u32 *)dst = self->scs_gpregs.gp_edx; break;
	case CFI_386_UNWIND_REGISTER_ECX:    *(u32 *)dst = self->scs_gpregs.gp_ecx; break;
	case CFI_386_UNWIND_REGISTER_EAX:    *(u32 *)dst = self->scs_gpregs.gp_eax; break;
	case CFI_386_UNWIND_REGISTER_GS:     *(u32 *)dst = SCPUSTATE_GS(*self); break;
	case CFI_386_UNWIND_REGISTER_FS:     *(u32 *)dst = SCPUSTATE_FS(*self); break;
	case CFI_386_UNWIND_REGISTER_ES:     *(u32 *)dst = SCPUSTATE_ES(*self); break;
	case CFI_386_UNWIND_REGISTER_DS:     *(u32 *)dst = SCPUSTATE_DS(*self); break;
	case CFI_386_UNWIND_REGISTER_CS:     *(u32 *)dst = self->scs_irregs_k.ir_cs; break;
	case CFI_386_UNWIND_REGISTER_SS:     *(u32 *)dst = SCPUSTATE_SS(*self); break;
	case CFI_386_UNWIND_REGISTER_EFLAGS: *(u32 *)dst = self->scs_irregs_k.ir_eflags; break;
	case CFI_386_UNWIND_REGISTER_EIP:    *(u32 *)dst = self->scs_irregs_k.ir_eip; break;
	default:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_setreg_scpustate)(struct scpustate *__restrict self,
                                              uintptr_half_t regno,
                                              void const *__restrict src) {
	switch (regno) {
	case CFI_386_UNWIND_REGISTER_EDI:    self->scs_gpregs.gp_edi = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ESI:    self->scs_gpregs.gp_esi = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EBP:    self->scs_gpregs.gp_ebp = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ESP:    return SCPUSTATE_WRSP(*self,*(u32 const *)src);
	case CFI_386_UNWIND_REGISTER_EBX:    self->scs_gpregs.gp_ebx = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EDX:    self->scs_gpregs.gp_edx = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ECX:    self->scs_gpregs.gp_ecx = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EAX:    self->scs_gpregs.gp_eax = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_GS:     SCPUSTATE_WRGS(*self,*(u32 const *)src); break;
	case CFI_386_UNWIND_REGISTER_FS:     SCPUSTATE_WRFS(*self,*(u32 const *)src); break;
	case CFI_386_UNWIND_REGISTER_ES:     SCPUSTATE_WRES(*self,*(u32 const *)src); break;
	case CFI_386_UNWIND_REGISTER_DS:     SCPUSTATE_WRDS(*self,*(u32 const *)src); break;
	case CFI_386_UNWIND_REGISTER_SS:     SCPUSTATE_WRSS(*self,*(u32 const *)src); break;
	case CFI_386_UNWIND_REGISTER_EIP:    self->scs_irregs_k.ir_eip = *(u32 const *)src; break;

	case CFI_386_UNWIND_REGISTER_CS: {
		u32 newval;
		newval = *(u32 const *)src;
		/* Must not switch between user-space/kernel-space contexts. */
		if (((newval & 3) != 0) !=
		    ((self->scs_irregs_k.ir_cs & 3) != 0))
			return false;
		self->scs_irregs_k.ir_cs = newval;
	}	break;

	case CFI_386_UNWIND_REGISTER_EFLAGS: {
		u32 newval;
		newval = *(u32 const *)src;
		/* Must not switch to/from vm86 contexts. */
		if ((self->scs_irregs_k.ir_eflags & EFLAGS_VM) !=
		    (newval & EFLAGS_VM))
			return false;
		self->scs_irregs_k.ir_eflags = newval;
	}	break;

	default:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_getreg_icpustate)(struct icpustate const *__restrict self,
                                              uintptr_half_t regno,
                                              void *__restrict dst) {
	switch (regno) {
	case CFI_386_UNWIND_REGISTER_EDI:    *(u32 *)dst = self->ics_gpregs.gp_edi; break;
	case CFI_386_UNWIND_REGISTER_ESI:    *(u32 *)dst = self->ics_gpregs.gp_esi; break;
	case CFI_386_UNWIND_REGISTER_EBP:    *(u32 *)dst = self->ics_gpregs.gp_ebp; break;
	case CFI_386_UNWIND_REGISTER_ESP:    *(u32 *)dst = ICPUSTATE_SP(*self); break;
	case CFI_386_UNWIND_REGISTER_EBX:    *(u32 *)dst = self->ics_gpregs.gp_ebx; break;
	case CFI_386_UNWIND_REGISTER_EDX:    *(u32 *)dst = self->ics_gpregs.gp_edx; break;
	case CFI_386_UNWIND_REGISTER_ECX:    *(u32 *)dst = self->ics_gpregs.gp_ecx; break;
	case CFI_386_UNWIND_REGISTER_EAX:    *(u32 *)dst = self->ics_gpregs.gp_eax; break;
	case CFI_386_UNWIND_REGISTER_GS:     *(u32 *)dst = ICPUSTATE_GS(*self); break;
	case CFI_386_UNWIND_REGISTER_FS:     *(u32 *)dst = ICPUSTATE_FS(*self); break;
	case CFI_386_UNWIND_REGISTER_ES:     *(u32 *)dst = ICPUSTATE_ES(*self); break;
	case CFI_386_UNWIND_REGISTER_DS:     *(u32 *)dst = ICPUSTATE_DS(*self); break;
	case CFI_386_UNWIND_REGISTER_CS:     *(u32 *)dst = self->ics_irregs_k.ir_cs; break;
	case CFI_386_UNWIND_REGISTER_SS:     *(u32 *)dst = ICPUSTATE_SS(*self); break;
	case CFI_386_UNWIND_REGISTER_EFLAGS: *(u32 *)dst = self->ics_irregs_k.ir_eflags; break;
	case CFI_386_UNWIND_REGISTER_EIP:    *(u32 *)dst = self->ics_irregs_k.ir_eip; break;
	default:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_setreg_icpustate)(struct icpustate *__restrict self,
                                              uintptr_half_t regno,
                                              void const *__restrict src) {
	switch (regno) {
	case CFI_386_UNWIND_REGISTER_EDI:    self->ics_gpregs.gp_edi = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ESI:    self->ics_gpregs.gp_esi = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EBP:    self->ics_gpregs.gp_ebp = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ESP:    return ICPUSTATE_WRSP(*self,*(u32 const *)src);
	case CFI_386_UNWIND_REGISTER_EBX:    self->ics_gpregs.gp_ebx = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EDX:    self->ics_gpregs.gp_edx = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ECX:    self->ics_gpregs.gp_ecx = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EAX:    self->ics_gpregs.gp_eax = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_GS:     ICPUSTATE_WRGS(*self,*(u32 const *)src); break;
	case CFI_386_UNWIND_REGISTER_FS:     ICPUSTATE_WRFS(*self,*(u32 const *)src); break;
	case CFI_386_UNWIND_REGISTER_ES:     ICPUSTATE_WRES(*self,*(u32 const *)src); break;
	case CFI_386_UNWIND_REGISTER_DS:     ICPUSTATE_WRDS(*self,*(u32 const *)src); break;
	case CFI_386_UNWIND_REGISTER_SS:     ICPUSTATE_WRSS(*self,*(u32 const *)src); break;
	case CFI_386_UNWIND_REGISTER_EIP:    self->ics_irregs_k.ir_eip = *(u32 const *)src; break;

	case CFI_386_UNWIND_REGISTER_CS: {
		u32 newval;
		newval = *(u32 const *)src;
		/* Must not switch between user-space/kernel-space contexts. */
		if (((newval & 3) != 0) != 
		    ((self->ics_irregs_k.ir_cs & 3) != 0))
			return false;
		self->ics_irregs_k.ir_cs = newval;
	}	break;

	case CFI_386_UNWIND_REGISTER_EFLAGS: {
		u32 newval;
		newval = *(u32 const *)src;
		/* Must not switch to/from vm86 contexts. */
		if ((self->ics_irregs_k.ir_eflags & EFLAGS_VM) !=
		    (newval & EFLAGS_VM))
			return false;
		self->ics_irregs_k.ir_eflags = newval;
	}	break;

	default:
		return false;
	}
	return true;
}
#endif /* __KERNEL__ */

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_getreg_fcpustate)(struct fcpustate const *__restrict self,
                                              uintptr_half_t regno,
                                              void *__restrict dst) {
	switch (regno) {
	case CFI_386_UNWIND_REGISTER_EDI:    *(u32 *)dst = self->fcs_gpregs.gp_edi; break;
	case CFI_386_UNWIND_REGISTER_ESI:    *(u32 *)dst = self->fcs_gpregs.gp_esi; break;
	case CFI_386_UNWIND_REGISTER_EBP:    *(u32 *)dst = self->fcs_gpregs.gp_ebp; break;
	case CFI_386_UNWIND_REGISTER_ESP:    *(u32 *)dst = self->fcs_gpregs.gp_esp; break;
	case CFI_386_UNWIND_REGISTER_EBX:    *(u32 *)dst = self->fcs_gpregs.gp_ebx; break;
	case CFI_386_UNWIND_REGISTER_EDX:    *(u32 *)dst = self->fcs_gpregs.gp_edx; break;
	case CFI_386_UNWIND_REGISTER_ECX:    *(u32 *)dst = self->fcs_gpregs.gp_ecx; break;
	case CFI_386_UNWIND_REGISTER_EAX:    *(u32 *)dst = self->fcs_gpregs.gp_eax; break;
	case CFI_386_UNWIND_REGISTER_GS:     *(u32 *)dst = self->fcs_sgregs.sg_gs; break;
	case CFI_386_UNWIND_REGISTER_FS:     *(u32 *)dst = self->fcs_sgregs.sg_fs; break;
	case CFI_386_UNWIND_REGISTER_ES:     *(u32 *)dst = self->fcs_sgregs.sg_es; break;
	case CFI_386_UNWIND_REGISTER_DS:     *(u32 *)dst = self->fcs_sgregs.sg_ds; break;
	case CFI_386_UNWIND_REGISTER_CS:     *(u32 *)dst = self->fcs_sgregs.sg_cs; break;
	case CFI_386_UNWIND_REGISTER_SS:     *(u32 *)dst = self->fcs_sgregs.sg_ss; break;
	case CFI_386_UNWIND_REGISTER_EFLAGS: *(u32 *)dst = self->fcs_eflags; break;
	case CFI_386_UNWIND_REGISTER_EIP:    *(u32 *)dst = self->fcs_eip; break;
	case CFI_386_UNWIND_REGISTER_TR:     *(u32 *)dst = self->fcs_sgregs.sg_tr; break;
	case CFI_386_UNWIND_REGISTER_LDTR:   *(u32 *)dst = self->fcs_sgregs.sg_ldt; break;
	default:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_setreg_fcpustate)(struct fcpustate *__restrict self,
                                              uintptr_half_t regno,
                                              void const *__restrict src) {
	switch (regno) {
	case CFI_386_UNWIND_REGISTER_EDI:    self->fcs_gpregs.gp_edi = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ESI:    self->fcs_gpregs.gp_esi = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EBP:    self->fcs_gpregs.gp_ebp = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ESP:    self->fcs_gpregs.gp_esp = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EBX:    self->fcs_gpregs.gp_ebx = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EDX:    self->fcs_gpregs.gp_edx = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ECX:    self->fcs_gpregs.gp_ecx = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EAX:    self->fcs_gpregs.gp_eax = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_GS:     self->fcs_sgregs.sg_gs = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_FS:     self->fcs_sgregs.sg_fs = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ES:     self->fcs_sgregs.sg_es = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_DS:     self->fcs_sgregs.sg_ds = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_CS:     self->fcs_sgregs.sg_cs = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_SS:     self->fcs_sgregs.sg_ss = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EFLAGS: self->fcs_eflags = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EIP:    self->fcs_eip = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_TR:     self->fcs_sgregs.sg_tr = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_LDTR:   self->fcs_sgregs.sg_ldt = *(u32 const *)src; break;
	default:
		return false;
	}
	return true;
}

#ifndef __KERNEL__
DEFINE_INTERN_ALIAS(libuw_unwind_getreg_ucontext, libuw_unwind_getreg_mcontext);
DEFINE_INTERN_ALIAS(libuw_unwind_setreg_ucontext, libuw_unwind_setreg_mcontext);

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_getreg_mcontext)(struct mcontext const *__restrict self,
                                             uintptr_half_t regno,
                                             void *__restrict dst) {
	switch (regno) {

	case CFI_386_UNWIND_REGISTER_EDI:    *(u32 *)dst = self->mc_context.ucs_gpregs.gp_edi; break;
	case CFI_386_UNWIND_REGISTER_ESI:    *(u32 *)dst = self->mc_context.ucs_gpregs.gp_esi; break;
	case CFI_386_UNWIND_REGISTER_EBP:    *(u32 *)dst = self->mc_context.ucs_gpregs.gp_ebp; break;
	case CFI_386_UNWIND_REGISTER_ESP:    *(u32 *)dst = self->mc_context.ucs_gpregs.gp_esp; break;
	case CFI_386_UNWIND_REGISTER_EBX:    *(u32 *)dst = self->mc_context.ucs_gpregs.gp_ebx; break;
	case CFI_386_UNWIND_REGISTER_EDX:    *(u32 *)dst = self->mc_context.ucs_gpregs.gp_edx; break;
	case CFI_386_UNWIND_REGISTER_ECX:    *(u32 *)dst = self->mc_context.ucs_gpregs.gp_ecx; break;
	case CFI_386_UNWIND_REGISTER_EAX:    *(u32 *)dst = self->mc_context.ucs_gpregs.gp_eax; break;
	case CFI_386_UNWIND_REGISTER_GS:     *(u32 *)dst = self->mc_context.ucs_sgregs.sg_gs; break;
	case CFI_386_UNWIND_REGISTER_FS:     *(u32 *)dst = self->mc_context.ucs_sgregs.sg_fs; break;
	case CFI_386_UNWIND_REGISTER_ES:     *(u32 *)dst = self->mc_context.ucs_sgregs.sg_es; break;
	case CFI_386_UNWIND_REGISTER_DS:     *(u32 *)dst = self->mc_context.ucs_sgregs.sg_ds; break;
	case CFI_386_UNWIND_REGISTER_CS:     *(u32 *)dst = self->mc_context.ucs_cs; break;
	case CFI_386_UNWIND_REGISTER_SS:     *(u32 *)dst = self->mc_context.ucs_ss; break;
	case CFI_386_UNWIND_REGISTER_EFLAGS: *(u32 *)dst = self->mc_context.ucs_eflags; break;
	case CFI_386_UNWIND_REGISTER_EIP:    *(u32 *)dst = self->mc_context.ucs_eip; break;

	case CFI_386_UNWIND_REGISTER_MM0 ... CFI_386_UNWIND_REGISTER_MM7:
		regno -= CFI_386_UNWIND_REGISTER_MM0;
		goto do_fpreg;
	case CFI_386_UNWIND_REGISTER_ST0 ... CFI_386_UNWIND_REGISTER_ST7:
		regno -= CFI_386_UNWIND_REGISTER_ST0;
do_fpreg:
		if (self->mc_flags & MCONTEXT_FLAG_HAVEXFPU) {
			memcpy((byte_t *)dst, &self->mc_fpu.f_xsave.fs_regs[regno], 16);
		} else if (self->mc_flags & MCONTEXT_FLAG_HAVESFPU) {
			memcpy((byte_t *)dst, &self->mc_fpu.f_ssave.fs_regs[regno], 10);
			memset((byte_t *)dst + 10, 0, 6);
		} else {
			goto nope;
		}
		break;

	case CFI_386_UNWIND_REGISTER_XMM0 ... CFI_386_UNWIND_REGISTER_XMM7:
		regno -= CFI_386_UNWIND_REGISTER_XMM0;
		if (self->mc_flags & MCONTEXT_FLAG_HAVEXFPU) {
			memcpy((byte_t *)dst, &self->mc_fpu.f_xsave.fs_xmm[regno], 16);
		} else {
			goto nope;
		}
		break;

	case CFI_386_UNWIND_REGISTER_FCW:
		if (self->mc_flags & MCONTEXT_FLAG_HAVEXFPU) {
			*(u32 *)dst = self->mc_fpu.f_xsave.fs_fcw;
		} else if (self->mc_flags & MCONTEXT_FLAG_HAVESFPU) {
			*(u32 *)dst = self->mc_fpu.f_ssave.fs_fcw;
		} else {
			goto nope;
		}
		break;

	case CFI_386_UNWIND_REGISTER_FSW:
		if (self->mc_flags & MCONTEXT_FLAG_HAVEXFPU) {
			*(u32 *)dst = self->mc_fpu.f_xsave.fs_fsw;
		} else if (self->mc_flags & MCONTEXT_FLAG_HAVESFPU) {
			*(u32 *)dst = self->mc_fpu.f_ssave.fs_fsw;
		} else {
			goto nope;
		}
		break;

	case CFI_386_UNWIND_REGISTER_MXCSR:
		if (self->mc_flags & MCONTEXT_FLAG_HAVEXFPU) {
			*(u32 *)dst = self->mc_fpu.f_xsave.fs_mxcsr;
		} else {
			goto nope;
		}
		break;

	default:
nope:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_setreg_mcontext)(struct mcontext *__restrict self,
                                             uintptr_half_t regno,
                                             void const *__restrict src) {
	switch (regno) {

	case CFI_386_UNWIND_REGISTER_EDI:    self->mc_context.ucs_gpregs.gp_edi = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ESI:    self->mc_context.ucs_gpregs.gp_esi = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EBP:    self->mc_context.ucs_gpregs.gp_ebp = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ESP:    self->mc_context.ucs_gpregs.gp_esp = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EBX:    self->mc_context.ucs_gpregs.gp_ebx = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EDX:    self->mc_context.ucs_gpregs.gp_edx = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ECX:    self->mc_context.ucs_gpregs.gp_ecx = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EAX:    self->mc_context.ucs_gpregs.gp_eax = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_GS:     self->mc_context.ucs_sgregs.sg_gs = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_FS:     self->mc_context.ucs_sgregs.sg_fs = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_ES:     self->mc_context.ucs_sgregs.sg_es = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_DS:     self->mc_context.ucs_sgregs.sg_ds = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_CS:     self->mc_context.ucs_cs = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_SS:     self->mc_context.ucs_ss = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EFLAGS: self->mc_context.ucs_eflags = *(u32 const *)src; break;
	case CFI_386_UNWIND_REGISTER_EIP:    self->mc_context.ucs_eip = *(u32 const *)src; break;

	case CFI_386_UNWIND_REGISTER_MM0 ... CFI_386_UNWIND_REGISTER_MM7:
		regno -= CFI_386_UNWIND_REGISTER_MM0;
		goto do_fpreg;
	case CFI_386_UNWIND_REGISTER_ST0 ... CFI_386_UNWIND_REGISTER_ST7:
		regno -= CFI_386_UNWIND_REGISTER_ST0;
do_fpreg:
		if (self->mc_flags & MCONTEXT_FLAG_HAVEXFPU) {
			memcpy(&self->mc_fpu.f_xsave.fs_regs[regno], src, 16);
		} else if (self->mc_flags & MCONTEXT_FLAG_HAVESFPU) {
			memcpy(&self->mc_fpu.f_ssave.fs_regs[regno], src, 10);
		} else {
			goto nope;
		}
		break;

	case CFI_386_UNWIND_REGISTER_XMM0 ... CFI_386_UNWIND_REGISTER_XMM7:
		regno -= CFI_386_UNWIND_REGISTER_XMM0;
		if (self->mc_flags & MCONTEXT_FLAG_HAVEXFPU) {
			memcpy(&self->mc_fpu.f_xsave.fs_xmm[regno], src, 16);
		} else {
			goto nope;
		}
		break;

	case CFI_386_UNWIND_REGISTER_FCW:
		if (self->mc_flags & MCONTEXT_FLAG_HAVEXFPU) {
			self->mc_fpu.f_xsave.fs_fcw = (u16)*(u32 const *)src;
		} else if (self->mc_flags & MCONTEXT_FLAG_HAVESFPU) {
			self->mc_fpu.f_ssave.fs_fcw = (u16)*(u32 const *)src;
		} else {
			goto nope;
		}
		break;

	case CFI_386_UNWIND_REGISTER_FSW:
		if (self->mc_flags & MCONTEXT_FLAG_HAVEXFPU) {
			self->mc_fpu.f_xsave.fs_fsw = (u16)*(u32 const *)src;
		} else if (self->mc_flags & MCONTEXT_FLAG_HAVESFPU) {
			self->mc_fpu.f_ssave.fs_fsw = (u16)*(u32 const *)src;
		} else {
			goto nope;
		}
		break;

	case CFI_386_UNWIND_REGISTER_MXCSR:
		if (self->mc_flags & MCONTEXT_FLAG_HAVEXFPU) {
			self->mc_fpu.f_xsave.fs_mxcsr = *(u32 const *)src;
		} else {
			goto nope;
		}
		break;

	default:
nope:
		return false;
	}
	return true;
}
#endif /* !__KERNEL__ */

#endif /* !__x86_64__ */



#ifdef __x86_64__
#define CFI_UNWIND_REGISTER_XMM0   CFI_X86_64_UNWIND_REGISTER_XMM0
#define CFI_UNWIND_REGISTER_XMM1   CFI_X86_64_UNWIND_REGISTER_XMM1
#define CFI_UNWIND_REGISTER_XMM2   CFI_X86_64_UNWIND_REGISTER_XMM2
#define CFI_UNWIND_REGISTER_XMM3   CFI_X86_64_UNWIND_REGISTER_XMM3
#define CFI_UNWIND_REGISTER_XMM4   CFI_X86_64_UNWIND_REGISTER_XMM4
#define CFI_UNWIND_REGISTER_XMM5   CFI_X86_64_UNWIND_REGISTER_XMM5
#define CFI_UNWIND_REGISTER_XMM6   CFI_X86_64_UNWIND_REGISTER_XMM6
#define CFI_UNWIND_REGISTER_XMM7   CFI_X86_64_UNWIND_REGISTER_XMM7
#define CFI_UNWIND_REGISTER_XMM8   CFI_X86_64_UNWIND_REGISTER_XMM8
#define CFI_UNWIND_REGISTER_XMM9   CFI_X86_64_UNWIND_REGISTER_XMM9
#define CFI_UNWIND_REGISTER_XMM10  CFI_X86_64_UNWIND_REGISTER_XMM10
#define CFI_UNWIND_REGISTER_XMM11  CFI_X86_64_UNWIND_REGISTER_XMM11
#define CFI_UNWIND_REGISTER_XMM12  CFI_X86_64_UNWIND_REGISTER_XMM12
#define CFI_UNWIND_REGISTER_XMM13  CFI_X86_64_UNWIND_REGISTER_XMM13
#define CFI_UNWIND_REGISTER_XMM14  CFI_X86_64_UNWIND_REGISTER_XMM14
#define CFI_UNWIND_REGISTER_XMM15  CFI_X86_64_UNWIND_REGISTER_XMM15
#define CFI_UNWIND_REGISTER_ST0    CFI_X86_64_UNWIND_REGISTER_ST0
#define CFI_UNWIND_REGISTER_ST1    CFI_X86_64_UNWIND_REGISTER_ST1
#define CFI_UNWIND_REGISTER_ST2    CFI_X86_64_UNWIND_REGISTER_ST2
#define CFI_UNWIND_REGISTER_ST3    CFI_X86_64_UNWIND_REGISTER_ST3
#define CFI_UNWIND_REGISTER_ST4    CFI_X86_64_UNWIND_REGISTER_ST4
#define CFI_UNWIND_REGISTER_ST5    CFI_X86_64_UNWIND_REGISTER_ST5
#define CFI_UNWIND_REGISTER_ST6    CFI_X86_64_UNWIND_REGISTER_ST6
#define CFI_UNWIND_REGISTER_ST7    CFI_X86_64_UNWIND_REGISTER_ST7
#define CFI_UNWIND_REGISTER_MM0    CFI_X86_64_UNWIND_REGISTER_MM0
#define CFI_UNWIND_REGISTER_MM1    CFI_X86_64_UNWIND_REGISTER_MM1
#define CFI_UNWIND_REGISTER_MM2    CFI_X86_64_UNWIND_REGISTER_MM2
#define CFI_UNWIND_REGISTER_MM3    CFI_X86_64_UNWIND_REGISTER_MM3
#define CFI_UNWIND_REGISTER_MM4    CFI_X86_64_UNWIND_REGISTER_MM4
#define CFI_UNWIND_REGISTER_MM5    CFI_X86_64_UNWIND_REGISTER_MM5
#define CFI_UNWIND_REGISTER_MM6    CFI_X86_64_UNWIND_REGISTER_MM6
#define CFI_UNWIND_REGISTER_MM7    CFI_X86_64_UNWIND_REGISTER_MM7
#define CFI_UNWIND_REGISTER_MXCSR  CFI_X86_64_UNWIND_REGISTER_MXCSR
#define CFI_UNWIND_REGISTER_FCW    CFI_X86_64_UNWIND_REGISTER_FCW
#define CFI_UNWIND_REGISTER_FSW    CFI_X86_64_UNWIND_REGISTER_FSW
#else /* __x86_64__ */
#define CFI_UNWIND_REGISTER_XMM0   CFI_386_UNWIND_REGISTER_XMM0
#define CFI_UNWIND_REGISTER_XMM1   CFI_386_UNWIND_REGISTER_XMM1
#define CFI_UNWIND_REGISTER_XMM2   CFI_386_UNWIND_REGISTER_XMM2
#define CFI_UNWIND_REGISTER_XMM3   CFI_386_UNWIND_REGISTER_XMM3
#define CFI_UNWIND_REGISTER_XMM4   CFI_386_UNWIND_REGISTER_XMM4
#define CFI_UNWIND_REGISTER_XMM5   CFI_386_UNWIND_REGISTER_XMM5
#define CFI_UNWIND_REGISTER_XMM6   CFI_386_UNWIND_REGISTER_XMM6
#define CFI_UNWIND_REGISTER_XMM7   CFI_386_UNWIND_REGISTER_XMM7
#define CFI_UNWIND_REGISTER_ST0    CFI_386_UNWIND_REGISTER_ST0
#define CFI_UNWIND_REGISTER_ST1    CFI_386_UNWIND_REGISTER_ST1
#define CFI_UNWIND_REGISTER_ST2    CFI_386_UNWIND_REGISTER_ST2
#define CFI_UNWIND_REGISTER_ST3    CFI_386_UNWIND_REGISTER_ST3
#define CFI_UNWIND_REGISTER_ST4    CFI_386_UNWIND_REGISTER_ST4
#define CFI_UNWIND_REGISTER_ST5    CFI_386_UNWIND_REGISTER_ST5
#define CFI_UNWIND_REGISTER_ST6    CFI_386_UNWIND_REGISTER_ST6
#define CFI_UNWIND_REGISTER_ST7    CFI_386_UNWIND_REGISTER_ST7
#define CFI_UNWIND_REGISTER_MM0    CFI_386_UNWIND_REGISTER_MM0
#define CFI_UNWIND_REGISTER_MM1    CFI_386_UNWIND_REGISTER_MM1
#define CFI_UNWIND_REGISTER_MM2    CFI_386_UNWIND_REGISTER_MM2
#define CFI_UNWIND_REGISTER_MM3    CFI_386_UNWIND_REGISTER_MM3
#define CFI_UNWIND_REGISTER_MM4    CFI_386_UNWIND_REGISTER_MM4
#define CFI_UNWIND_REGISTER_MM5    CFI_386_UNWIND_REGISTER_MM5
#define CFI_UNWIND_REGISTER_MM6    CFI_386_UNWIND_REGISTER_MM6
#define CFI_UNWIND_REGISTER_MM7    CFI_386_UNWIND_REGISTER_MM7
#define CFI_UNWIND_REGISTER_MXCSR  CFI_386_UNWIND_REGISTER_MXCSR
#define CFI_UNWIND_REGISTER_FCW    CFI_386_UNWIND_REGISTER_FCW
#define CFI_UNWIND_REGISTER_FSW    CFI_386_UNWIND_REGISTER_FSW
#endif /* !__x86_64__ */



INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_getreg_sfpustate)(struct sfpustate const *__restrict self,
                                              uintptr_half_t regno,
                                              void *__restrict dst) {
	switch (regno) {

	case CFI_UNWIND_REGISTER_MM0 ... CFI_UNWIND_REGISTER_MM7:
		regno -= CFI_UNWIND_REGISTER_MM0;
		goto do_fpreg;
	case CFI_UNWIND_REGISTER_ST0 ... CFI_UNWIND_REGISTER_ST7:
		regno -= CFI_UNWIND_REGISTER_ST0;
do_fpreg:
		memcpy((byte_t *)dst, &self->fs_regs[regno], 10);
		memset((byte_t *)dst + 10, 0, 6);
		break;

	case CFI_UNWIND_REGISTER_FCW:
		*(uintptr_t *)dst = self->fs_fcw;
		break;

	case CFI_UNWIND_REGISTER_FSW:
		*(uintptr_t *)dst = self->fs_fsw;
		break;

	default:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_setreg_sfpustate)(struct sfpustate *__restrict self,
                                              uintptr_half_t regno,
                                              void const *__restrict src) {
	switch (regno) {

	case CFI_UNWIND_REGISTER_MM0 ... CFI_UNWIND_REGISTER_MM7:
		regno -= CFI_UNWIND_REGISTER_MM0;
		goto do_fpreg;
	case CFI_UNWIND_REGISTER_ST0 ... CFI_UNWIND_REGISTER_ST7:
		regno -= CFI_UNWIND_REGISTER_ST0;
do_fpreg:
		memcpy(&self->fs_regs[regno], src, 10);
		break;

	case CFI_UNWIND_REGISTER_FCW:
		self->fs_fcw = (u16)*(uintptr_t const *)src;
		break;

	case CFI_UNWIND_REGISTER_FSW:
		self->fs_fsw = (u16)*(uintptr_t const *)src;
		break;

	default:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_getreg_xfpustate)(struct xfpustate const *__restrict self,
                                              uintptr_half_t regno,
                                              void *__restrict dst) {
	switch (regno) {

	case CFI_UNWIND_REGISTER_MM0 ... CFI_UNWIND_REGISTER_MM7:
		regno -= CFI_UNWIND_REGISTER_MM0;
		goto do_fpreg;
	case CFI_UNWIND_REGISTER_ST0 ... CFI_UNWIND_REGISTER_ST7:
		regno -= CFI_UNWIND_REGISTER_ST0;
do_fpreg:
		memcpy(dst, &self->fs_regs[regno], 16);
		break;

	case CFI_UNWIND_REGISTER_FCW:
		*(uintptr_t *)dst = self->fs_fcw;
		break;

	case CFI_UNWIND_REGISTER_FSW:
		*(uintptr_t *)dst = self->fs_fsw;
		break;

	case CFI_UNWIND_REGISTER_MXCSR:
		*(uintptr_t *)dst = self->fs_mxcsr;
		break;

#ifdef __x86_64__
	case CFI_UNWIND_REGISTER_XMM0 ... CFI_UNWIND_REGISTER_XMM15:
#else /* __x86_64__ */
	case CFI_UNWIND_REGISTER_XMM0 ... CFI_UNWIND_REGISTER_XMM7:
#endif /* !__x86_64__ */
		memcpy(dst, &self->fs_xmm[regno - CFI_UNWIND_REGISTER_XMM0], 16);
		break;

	default:
		return false;
	}
	return true;
}

INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libuw_unwind_setreg_xfpustate)(struct xfpustate *__restrict self,
                                              uintptr_half_t regno,
                                              void const *__restrict src) {
	switch (regno) {

	case CFI_UNWIND_REGISTER_MM0 ... CFI_UNWIND_REGISTER_MM7:
		regno -= CFI_UNWIND_REGISTER_MM0;
		goto do_fpreg;
	case CFI_UNWIND_REGISTER_ST0 ... CFI_UNWIND_REGISTER_ST7:
		regno -= CFI_UNWIND_REGISTER_ST0;
do_fpreg:
		memcpy(&self->fs_regs[regno], src, 16);
		break;

	case CFI_UNWIND_REGISTER_FCW:
		self->fs_fcw = (u16)*(uintptr_t const *)src;
		break;

	case CFI_UNWIND_REGISTER_FSW:
		self->fs_fsw = (u16)*(uintptr_t const *)src;
		break;

	case CFI_UNWIND_REGISTER_MXCSR:
		self->fs_mxcsr = (u32)*(uintptr_t const *)src;
		break;

#ifdef __x86_64__
	case CFI_UNWIND_REGISTER_XMM0 ... CFI_UNWIND_REGISTER_XMM15:
#else /* __x86_64__ */
	case CFI_UNWIND_REGISTER_XMM0 ... CFI_UNWIND_REGISTER_XMM7:
#endif /* !__x86_64__ */
		memcpy(&self->fs_xmm[regno - CFI_UNWIND_REGISTER_XMM0], src, 16);
		break;

	default:
		return false;
	}
	return true;
}




DEFINE_PUBLIC_ALIAS(unwind_getreg_lcpustate, libuw_unwind_getreg_lcpustate);
DEFINE_PUBLIC_ALIAS(unwind_setreg_lcpustate, libuw_unwind_setreg_lcpustate);
DEFINE_PUBLIC_ALIAS(unwind_getreg_ucpustate, libuw_unwind_getreg_ucpustate);
DEFINE_PUBLIC_ALIAS(unwind_setreg_ucpustate, libuw_unwind_setreg_ucpustate);
DEFINE_PUBLIC_ALIAS(unwind_getreg_kcpustate, libuw_unwind_getreg_kcpustate);
DEFINE_PUBLIC_ALIAS(unwind_setreg_kcpustate, libuw_unwind_setreg_kcpustate);
DEFINE_PUBLIC_ALIAS(unwind_getreg_fcpustate, libuw_unwind_getreg_fcpustate);
DEFINE_PUBLIC_ALIAS(unwind_setreg_fcpustate, libuw_unwind_setreg_fcpustate);
DEFINE_PUBLIC_ALIAS(unwind_getreg_sfpustate, libuw_unwind_getreg_sfpustate);
DEFINE_PUBLIC_ALIAS(unwind_setreg_sfpustate, libuw_unwind_setreg_sfpustate);
DEFINE_PUBLIC_ALIAS(unwind_getreg_xfpustate, libuw_unwind_getreg_xfpustate);
DEFINE_PUBLIC_ALIAS(unwind_setreg_xfpustate, libuw_unwind_setreg_xfpustate);

#ifdef __KERNEL__
DEFINE_PUBLIC_ALIAS(unwind_getreg_scpustate, libuw_unwind_getreg_scpustate);
DEFINE_PUBLIC_ALIAS(unwind_setreg_scpustate, libuw_unwind_setreg_scpustate);
DEFINE_PUBLIC_ALIAS(unwind_getreg_icpustate, libuw_unwind_getreg_icpustate);
DEFINE_PUBLIC_ALIAS(unwind_setreg_icpustate, libuw_unwind_setreg_icpustate);
#endif /* __KERNEL__ */

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(unwind_getreg_ucontext, libuw_unwind_getreg_ucontext);
DEFINE_PUBLIC_ALIAS(unwind_setreg_ucontext, libuw_unwind_setreg_ucontext);
DEFINE_PUBLIC_ALIAS(unwind_getreg_mcontext, libuw_unwind_getreg_mcontext);
DEFINE_PUBLIC_ALIAS(unwind_setreg_mcontext, libuw_unwind_setreg_mcontext);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBUNWIND_ARCH_I386_UNWIND_C */
