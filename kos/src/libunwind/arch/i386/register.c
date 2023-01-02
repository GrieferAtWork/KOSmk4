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
#ifndef GUARD_LIBUNWIND_ARCH_I386_REGISTER_C
#define GUARD_LIBUNWIND_ARCH_I386_REGISTER_C 1
#define _KOS_KERNEL_SOURCE 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include "../../api.h"
/**/

#include "../../register.h"
#include <hybrid/compiler.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/fpu-state.h>
#include <kos/kernel/paging.h>
#include <kos/kernel/types.h>
#include <kos/kernel/x86/gdt.h>
#include <kos/types.h>
#include <sys/ucontext.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include <libunwind/cfi.h>
#include <libunwind/cfi/i386.h>
#include <libunwind/cfi/x86_64.h>
#include <libunwind/register.h>
#include <libunwind/unwind.h>

#include "../../unwind.h"

#ifdef __KERNEL__
#include <kernel/paging.h>
#endif /* __KERNEL__ */

#if 1
#define rdpptr_as16(p_ptr) (*(u16 const *)(p_ptr))
#define rdpptr_as32(p_ptr) (*(u32 const *)(p_ptr))
#define rdpptr_as64(p_ptr) (*(u64 const *)(p_ptr))
#else
#define rdpptr_as16(p_ptr) ((u16)(*(uintptr_t const *)(p_ptr)))
#define rdpptr_as32(p_ptr) ((u32)(*(uintptr_t const *)(p_ptr)))
#define rdpptr_as64(p_ptr) ((u64)(*(uintptr_t const *)(p_ptr)))
#endif
#define wrpptr(p_ptr, value) (*(uintptr_t *)(p_ptr) = (value))



DECL_BEGIN

#ifdef __x86_64__
#define IRREGS_LOADSELF(T) /* nothing */
#define IRREGS_SELF        self
#define IRREGS_INDIRECTION *
#define IRREGS_NAME(x)     x
#else /* __x86_64__ */
#define IRREGS_LOADSELF(T) T *self = *pself;
#define IRREGS_SELF        pself
#define IRREGS_INDIRECTION **
#define IRREGS_NAME(x)     x##_p
#endif /* !__x86_64__ */

struct lcpustate;
struct ucpustate;
struct kcpustate;
struct scpustate;
struct icpustate;
struct fcpustate;
struct ucontext;
struct mcontext;

#define MY_CS     SEGMENT_CURRENT_CODE_RPL
#define MY_SS     SEGMENT_CURRENT_DATA_RPL
#ifdef __x86_64__
#define MY_FS     __rdfs()
#define MY_DS     __rdds()
#define MY_ES     __rdes()
#define MY_FSBASE ((uintptr_t)__rdfsbase())
#define MY_GSBASE ((uintptr_t)__rdgsbase())
#else /* __x86_64__ */
#ifdef __KERNEL__
#define MY_FS     SEGMENT_KERNEL_FSBASE
#else /* __KERNEL__ */
#define MY_FS     __rdfs()
#endif /* !__KERNEL__ */
#define MY_DS     SEGMENT_USER_DATA_RPL
#define MY_ES     SEGMENT_USER_DATA_RPL
#endif /* !__x86_64__ */
#define MY_TR     __str()
#define MY_LDTR   __sldt()
#define MY_GS     __rdgs()


PRIVATE NONNULL((2)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_getreg_implicit)(unwind_regno_t dw_regno,
                                             void *__restrict dst) {
	uintptr_t value;
	switch (dw_regno) {
#ifdef __x86_64__
	case CFI_X86_64_UNWIND_REGISTER_ES:     value = MY_ES; break;
	case CFI_X86_64_UNWIND_REGISTER_CS:     value = MY_CS; break;
	case CFI_X86_64_UNWIND_REGISTER_SS:     value = MY_SS; break;
	case CFI_X86_64_UNWIND_REGISTER_DS:     value = MY_DS; break;
	case CFI_X86_64_UNWIND_REGISTER_FS:     value = MY_FS; break;
	case CFI_X86_64_UNWIND_REGISTER_GS:     value = MY_GS; break;
	case CFI_X86_64_UNWIND_REGISTER_FSBASE: value = MY_FSBASE; break;
	case CFI_X86_64_UNWIND_REGISTER_GSBASE: value = MY_GSBASE; break;
	case CFI_X86_64_UNWIND_REGISTER_TR:     value = MY_TR; break;
	case CFI_X86_64_UNWIND_REGISTER_LDTR:   value = MY_LDTR; break;
#else /* __x86_64__ */
	case CFI_386_UNWIND_REGISTER_ES:   value = MY_ES; break;
	case CFI_386_UNWIND_REGISTER_CS:   value = MY_CS; break;
	case CFI_386_UNWIND_REGISTER_SS:   value = MY_SS; break;
	case CFI_386_UNWIND_REGISTER_DS:   value = MY_DS; break;
	case CFI_386_UNWIND_REGISTER_FS:   value = MY_FS; break;
	case CFI_386_UNWIND_REGISTER_GS:   value = MY_GS; break;
	case CFI_386_UNWIND_REGISTER_TR:   value = MY_TR; break;
	case CFI_386_UNWIND_REGISTER_LDTR: value = MY_LDTR; break;
#endif /* !__x86_64__ */
	default:
		return UNWIND_INVALID_REGISTER;
	}
	wrpptr(dst, value);
	return UNWIND_SUCCESS;
}

PRIVATE NONNULL((2)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_setreg_implicit)(unwind_regno_t dw_regno,
                                             void const *__restrict src) {
	u16 expected_value;
	switch (dw_regno) {
#ifdef __x86_64__
	case CFI_X86_64_UNWIND_REGISTER_ES:     expected_value = MY_ES; break;
	case CFI_X86_64_UNWIND_REGISTER_CS:     expected_value = MY_CS; break;
	case CFI_X86_64_UNWIND_REGISTER_SS:     expected_value = MY_SS; break;
	case CFI_X86_64_UNWIND_REGISTER_DS:     expected_value = MY_DS; break;
	case CFI_X86_64_UNWIND_REGISTER_FS:     expected_value = MY_FS; break;
	case CFI_X86_64_UNWIND_REGISTER_GS:     expected_value = MY_GS; break;
	case CFI_X86_64_UNWIND_REGISTER_TR:     expected_value = MY_TR; break;
	case CFI_X86_64_UNWIND_REGISTER_LDTR:   expected_value = MY_LDTR; break;
	case CFI_X86_64_UNWIND_REGISTER_FSBASE:
		if (rdpptr_as64(src) != MY_FSBASE)
			goto badreg;
		return UNWIND_SUCCESS;
	case CFI_X86_64_UNWIND_REGISTER_GSBASE:
		if (rdpptr_as64(src) != MY_GSBASE)
			goto badreg;
		return UNWIND_SUCCESS;
#else /* __x86_64__ */
	case CFI_386_UNWIND_REGISTER_ES:   expected_value = MY_ES; break;
	case CFI_386_UNWIND_REGISTER_CS:   expected_value = MY_CS; break;
	case CFI_386_UNWIND_REGISTER_SS:   expected_value = MY_SS; break;
	case CFI_386_UNWIND_REGISTER_DS:   expected_value = MY_DS; break;
	case CFI_386_UNWIND_REGISTER_FS:   expected_value = MY_FS; break;
	case CFI_386_UNWIND_REGISTER_GS:   expected_value = MY_GS; break;
	case CFI_386_UNWIND_REGISTER_TR:   expected_value = MY_TR; break;
	case CFI_386_UNWIND_REGISTER_LDTR: expected_value = MY_LDTR; break;
#endif /* !__x86_64__ */
	default: goto badreg;
	}
	if (rdpptr_as16(src) != expected_value)
		goto badreg;
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}


#ifdef __x86_64__


LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_getreg_lcpustate_base)(struct lcpustate const *__restrict self,
                                                   unwind_regno_t dw_regno,
                                                   void *__restrict dst) {
	uintptr_t value;
	switch (dw_regno) {
	case CFI_X86_64_UNWIND_REGISTER_R15: value = self->lcs_r15; break;
	case CFI_X86_64_UNWIND_REGISTER_R14: value = self->lcs_r14; break;
	case CFI_X86_64_UNWIND_REGISTER_R13: value = self->lcs_r13; break;
	case CFI_X86_64_UNWIND_REGISTER_R12: value = self->lcs_r12; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP: value = self->lcs_rbp; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP: value = self->lcs_rsp; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX: value = self->lcs_rbx; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP: value = self->lcs_rip; break;
	default: goto badreg;
	}
	wrpptr(dst, value);
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_setreg_lcpustate_base)(struct lcpustate *__restrict self,
                                                   unwind_regno_t dw_regno,
                                                   void const *__restrict src) {
	uintptr_t value = rdpptr_as64(src);
	switch (dw_regno) {
	case CFI_X86_64_UNWIND_REGISTER_R15: self->lcs_r15 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R14: self->lcs_r14 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R13: self->lcs_r13 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R12: self->lcs_r12 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP: self->lcs_rbp = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP: self->lcs_rsp = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX: self->lcs_rbx = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP: self->lcs_rip = value; break;
	default: goto badreg;
	}
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_getreg_ucpustate_base)(struct ucpustate const *__restrict self,
                                                   unwind_regno_t dw_regno,
                                                   void *__restrict dst) {
	uintptr_t value;
	switch (dw_regno) {
	case CFI_X86_64_UNWIND_REGISTER_RAX:    value = self->ucs_gpregs.gp_rax; break;
	case CFI_X86_64_UNWIND_REGISTER_RDX:    value = self->ucs_gpregs.gp_rdx; break;
	case CFI_X86_64_UNWIND_REGISTER_RCX:    value = self->ucs_gpregs.gp_rcx; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX:    value = self->ucs_gpregs.gp_rbx; break;
	case CFI_X86_64_UNWIND_REGISTER_RSI:    value = self->ucs_gpregs.gp_rsi; break;
	case CFI_X86_64_UNWIND_REGISTER_RDI:    value = self->ucs_gpregs.gp_rdi; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP:    value = self->ucs_gpregs.gp_rbp; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP:    value = self->ucs_gpregs.gp_rsp; break;
	case CFI_X86_64_UNWIND_REGISTER_R8:     value = self->ucs_gpregs.gp_r8; break;
	case CFI_X86_64_UNWIND_REGISTER_R9:     value = self->ucs_gpregs.gp_r9; break;
	case CFI_X86_64_UNWIND_REGISTER_R10:    value = self->ucs_gpregs.gp_r10; break;
	case CFI_X86_64_UNWIND_REGISTER_R11:    value = self->ucs_gpregs.gp_r11; break;
	case CFI_X86_64_UNWIND_REGISTER_R12:    value = self->ucs_gpregs.gp_r12; break;
	case CFI_X86_64_UNWIND_REGISTER_R13:    value = self->ucs_gpregs.gp_r13; break;
	case CFI_X86_64_UNWIND_REGISTER_R14:    value = self->ucs_gpregs.gp_r14; break;
	case CFI_X86_64_UNWIND_REGISTER_R15:    value = self->ucs_gpregs.gp_r15; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP:    value = self->ucs_rip; break;
	case CFI_X86_64_UNWIND_REGISTER_RFLAGS: value = self->ucs_rflags; break;
	case CFI_X86_64_UNWIND_REGISTER_ES:     value = self->ucs_sgregs.sg_es16; break;
	case CFI_X86_64_UNWIND_REGISTER_CS:     value = self->ucs_cs16; break;
	case CFI_X86_64_UNWIND_REGISTER_SS:     value = self->ucs_ss16; break;
	case CFI_X86_64_UNWIND_REGISTER_DS:     value = self->ucs_sgregs.sg_ds16; break;
	case CFI_X86_64_UNWIND_REGISTER_FS:     value = self->ucs_sgregs.sg_fs16; break;
	case CFI_X86_64_UNWIND_REGISTER_GS:     value = self->ucs_sgregs.sg_gs16; break;
	case CFI_X86_64_UNWIND_REGISTER_FSBASE: value = self->ucs_sgbase.sg_fsbase; break;
	case CFI_X86_64_UNWIND_REGISTER_GSBASE: value = self->ucs_sgbase.sg_gsbase; break;
	default: goto badreg;
	}
	wrpptr(dst, value);
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_setreg_ucpustate_base)(struct ucpustate *__restrict self,
                                                   unwind_regno_t dw_regno,
                                                   void const *__restrict src) {
	uintptr_t value = rdpptr_as64(src);
	switch (dw_regno) {
	case CFI_X86_64_UNWIND_REGISTER_RAX:    self->ucs_gpregs.gp_rax = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RDX:    self->ucs_gpregs.gp_rdx = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RCX:    self->ucs_gpregs.gp_rcx = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX:    self->ucs_gpregs.gp_rbx = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RSI:    self->ucs_gpregs.gp_rsi = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RDI:    self->ucs_gpregs.gp_rdi = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP:    self->ucs_gpregs.gp_rbp = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP:    self->ucs_gpregs.gp_rsp = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R8:     self->ucs_gpregs.gp_r8 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R9:     self->ucs_gpregs.gp_r9 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R10:    self->ucs_gpregs.gp_r10 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R11:    self->ucs_gpregs.gp_r11 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R12:    self->ucs_gpregs.gp_r12 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R13:    self->ucs_gpregs.gp_r13 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R14:    self->ucs_gpregs.gp_r14 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R15:    self->ucs_gpregs.gp_r15 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP:    self->ucs_rip = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RFLAGS: self->ucs_rflags = value; break;
	case CFI_X86_64_UNWIND_REGISTER_ES:     self->ucs_sgregs.sg_es = value & 0xffff; break;
	case CFI_X86_64_UNWIND_REGISTER_CS:     self->ucs_cs = value & 0xffff; break;
	case CFI_X86_64_UNWIND_REGISTER_SS:     self->ucs_ss = value & 0xffff; break;
	case CFI_X86_64_UNWIND_REGISTER_DS:     self->ucs_sgregs.sg_ds = value & 0xffff; break;
	case CFI_X86_64_UNWIND_REGISTER_FS:     self->ucs_sgregs.sg_fs = value & 0xffff; break;
	case CFI_X86_64_UNWIND_REGISTER_GS:     self->ucs_sgregs.sg_gs = value & 0xffff; break;
	case CFI_X86_64_UNWIND_REGISTER_FSBASE: self->ucs_sgbase.sg_fsbase = value; break;
	case CFI_X86_64_UNWIND_REGISTER_GSBASE: self->ucs_sgbase.sg_gsbase = value; break;
	default: goto badreg;
	}
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_getreg_kcpustate_base)(struct kcpustate const *__restrict self,
                                                   unwind_regno_t dw_regno,
                                                   void *__restrict dst) {
	uintptr_t value;
	switch (dw_regno) {
	case CFI_X86_64_UNWIND_REGISTER_RAX:    value = self->kcs_gpregs.gp_rax; break;
	case CFI_X86_64_UNWIND_REGISTER_RDX:    value = self->kcs_gpregs.gp_rdx; break;
	case CFI_X86_64_UNWIND_REGISTER_RCX:    value = self->kcs_gpregs.gp_rcx; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX:    value = self->kcs_gpregs.gp_rbx; break;
	case CFI_X86_64_UNWIND_REGISTER_RSI:    value = self->kcs_gpregs.gp_rsi; break;
	case CFI_X86_64_UNWIND_REGISTER_RDI:    value = self->kcs_gpregs.gp_rdi; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP:    value = self->kcs_gpregs.gp_rbp; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP:    value = self->kcs_gpregs.gp_rsp; break;
	case CFI_X86_64_UNWIND_REGISTER_R8:     value = self->kcs_gpregs.gp_r8; break;
	case CFI_X86_64_UNWIND_REGISTER_R9:     value = self->kcs_gpregs.gp_r9; break;
	case CFI_X86_64_UNWIND_REGISTER_R10:    value = self->kcs_gpregs.gp_r10; break;
	case CFI_X86_64_UNWIND_REGISTER_R11:    value = self->kcs_gpregs.gp_r11; break;
	case CFI_X86_64_UNWIND_REGISTER_R12:    value = self->kcs_gpregs.gp_r12; break;
	case CFI_X86_64_UNWIND_REGISTER_R13:    value = self->kcs_gpregs.gp_r13; break;
	case CFI_X86_64_UNWIND_REGISTER_R14:    value = self->kcs_gpregs.gp_r14; break;
	case CFI_X86_64_UNWIND_REGISTER_R15:    value = self->kcs_gpregs.gp_r15; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP:    value = self->kcs_rip; break;
	case CFI_X86_64_UNWIND_REGISTER_RFLAGS: value = self->kcs_rflags; break;
	default: goto badreg;
	}
	wrpptr(dst, value);
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_setreg_kcpustate_base)(struct kcpustate *__restrict self,
                                                   unwind_regno_t dw_regno,
                                                   void const *__restrict src) {
	uintptr_t value = rdpptr_as64(src);
	switch (dw_regno) {
	case CFI_X86_64_UNWIND_REGISTER_RAX:    self->kcs_gpregs.gp_rax = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RDX:    self->kcs_gpregs.gp_rdx = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RCX:    self->kcs_gpregs.gp_rcx = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX:    self->kcs_gpregs.gp_rbx = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RSI:    self->kcs_gpregs.gp_rsi = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RDI:    self->kcs_gpregs.gp_rdi = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP:    self->kcs_gpregs.gp_rbp = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP:    self->kcs_gpregs.gp_rsp = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R8:     self->kcs_gpregs.gp_r8 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R9:     self->kcs_gpregs.gp_r9 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R10:    self->kcs_gpregs.gp_r10 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R11:    self->kcs_gpregs.gp_r11 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R12:    self->kcs_gpregs.gp_r12 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R13:    self->kcs_gpregs.gp_r13 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R14:    self->kcs_gpregs.gp_r14 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R15:    self->kcs_gpregs.gp_r15 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP:    self->kcs_rip = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RFLAGS: self->kcs_rflags = value; break;
	default: goto badreg;
	}
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

#if defined(__KERNEL__) || defined(__INTELLISENSE__)
LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_getreg_scpustate_base)(struct scpustate const *__restrict self,
                                                   unwind_regno_t dw_regno,
                                                   void *__restrict dst) {
	uintptr_t value;
	switch (dw_regno) {
	case CFI_X86_64_UNWIND_REGISTER_RAX:    value = self->scs_gpregs.gp_rax; break;
	case CFI_X86_64_UNWIND_REGISTER_RDX:    value = self->scs_gpregs.gp_rdx; break;
	case CFI_X86_64_UNWIND_REGISTER_RCX:    value = self->scs_gpregs.gp_rcx; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX:    value = self->scs_gpregs.gp_rbx; break;
	case CFI_X86_64_UNWIND_REGISTER_RSI:    value = self->scs_gpregs.gp_rsi; break;
	case CFI_X86_64_UNWIND_REGISTER_RDI:    value = self->scs_gpregs.gp_rdi; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP:    value = self->scs_gpregs.gp_rbp; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP:    value = self->scs_irregs.ir_rsp; break;
	case CFI_X86_64_UNWIND_REGISTER_R8:     value = self->scs_gpregs.gp_r8; break;
	case CFI_X86_64_UNWIND_REGISTER_R9:     value = self->scs_gpregs.gp_r9; break;
	case CFI_X86_64_UNWIND_REGISTER_R10:    value = self->scs_gpregs.gp_r10; break;
	case CFI_X86_64_UNWIND_REGISTER_R11:    value = self->scs_gpregs.gp_r11; break;
	case CFI_X86_64_UNWIND_REGISTER_R12:    value = self->scs_gpregs.gp_r12; break;
	case CFI_X86_64_UNWIND_REGISTER_R13:    value = self->scs_gpregs.gp_r13; break;
	case CFI_X86_64_UNWIND_REGISTER_R14:    value = self->scs_gpregs.gp_r14; break;
	case CFI_X86_64_UNWIND_REGISTER_R15:    value = self->scs_gpregs.gp_r15; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP:    value = self->scs_irregs.ir_rip; break;
	case CFI_X86_64_UNWIND_REGISTER_RFLAGS: value = self->scs_irregs.ir_rflags; break;
	case CFI_X86_64_UNWIND_REGISTER_ES:     value = self->scs_sgregs.sg_es16; break;
	case CFI_X86_64_UNWIND_REGISTER_CS:     value = self->scs_irregs.ir_cs16; break;
	case CFI_X86_64_UNWIND_REGISTER_SS:     value = self->scs_irregs.ir_ss16; break;
	case CFI_X86_64_UNWIND_REGISTER_DS:     value = self->scs_sgregs.sg_ds16; break;
	case CFI_X86_64_UNWIND_REGISTER_FS:     value = self->scs_sgregs.sg_fs16; break;
	case CFI_X86_64_UNWIND_REGISTER_GS:     value = self->scs_sgregs.sg_gs16; break;
	case CFI_X86_64_UNWIND_REGISTER_FSBASE: value = self->scs_sgbase.sg_fsbase; break;
	case CFI_X86_64_UNWIND_REGISTER_GSBASE: value = self->scs_sgbase.sg_gsbase; break;
	default: goto badreg;
	}
	wrpptr(dst, value);
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_setreg_scpustate_base)(struct scpustate *__restrict self,
                                                   unwind_regno_t dw_regno,
                                                   void const *__restrict src) {
	uintptr_t value = rdpptr_as64(src);
	switch (dw_regno) {
	case CFI_X86_64_UNWIND_REGISTER_RAX:    self->scs_gpregs.gp_rax = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RDX:    self->scs_gpregs.gp_rdx = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RCX:    self->scs_gpregs.gp_rcx = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX:    self->scs_gpregs.gp_rbx = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RSI:    self->scs_gpregs.gp_rsi = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RDI:    self->scs_gpregs.gp_rdi = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP:    self->scs_gpregs.gp_rbp = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP:    self->scs_irregs.ir_rsp = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R8:     self->scs_gpregs.gp_r8 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R9:     self->scs_gpregs.gp_r9 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R10:    self->scs_gpregs.gp_r10 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R11:    self->scs_gpregs.gp_r11 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R12:    self->scs_gpregs.gp_r12 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R13:    self->scs_gpregs.gp_r13 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R14:    self->scs_gpregs.gp_r14 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R15:    self->scs_gpregs.gp_r15 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP:    self->scs_irregs.ir_rip = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RFLAGS: self->scs_irregs.ir_rflags = value; break;
	case CFI_X86_64_UNWIND_REGISTER_ES:     self->scs_sgregs.sg_es = value & 0xffff; break;
	case CFI_X86_64_UNWIND_REGISTER_CS:     self->scs_irregs.ir_cs = value & 0xffff; break;
	case CFI_X86_64_UNWIND_REGISTER_SS:     self->scs_irregs.ir_ss = value & 0xffff; break;
	case CFI_X86_64_UNWIND_REGISTER_DS:     self->scs_sgregs.sg_ds = value & 0xffff; break;
	case CFI_X86_64_UNWIND_REGISTER_FS:     self->scs_sgregs.sg_fs = value & 0xffff; break;
	case CFI_X86_64_UNWIND_REGISTER_GS:     self->scs_sgregs.sg_gs = value & 0xffff; break;
	case CFI_X86_64_UNWIND_REGISTER_FSBASE: self->scs_sgbase.sg_fsbase = value; break;
	case CFI_X86_64_UNWIND_REGISTER_GSBASE: self->scs_sgbase.sg_gsbase = value; break;
	default: goto badreg;
	}
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_getreg_icpustate_base)(struct icpustate const *__restrict self,
                                                   unwind_regno_t dw_regno,
                                                   void *__restrict dst) {
	uintptr_t value;
	switch (dw_regno) {
	case CFI_X86_64_UNWIND_REGISTER_RAX:    value = self->ics_gpregs.gp_rax; break;
	case CFI_X86_64_UNWIND_REGISTER_RDX:    value = self->ics_gpregs.gp_rdx; break;
	case CFI_X86_64_UNWIND_REGISTER_RCX:    value = self->ics_gpregs.gp_rcx; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX:    value = self->ics_gpregs.gp_rbx; break;
	case CFI_X86_64_UNWIND_REGISTER_RSI:    value = self->ics_gpregs.gp_rsi; break;
	case CFI_X86_64_UNWIND_REGISTER_RDI:    value = self->ics_gpregs.gp_rdi; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP:    value = self->ics_gpregs.gp_rbp; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP:    value = self->ics_irregs.ir_rsp; break;
	case CFI_X86_64_UNWIND_REGISTER_R8:     value = self->ics_gpregs.gp_r8; break;
	case CFI_X86_64_UNWIND_REGISTER_R9:     value = self->ics_gpregs.gp_r9; break;
	case CFI_X86_64_UNWIND_REGISTER_R10:    value = self->ics_gpregs.gp_r10; break;
	case CFI_X86_64_UNWIND_REGISTER_R11:    value = self->ics_gpregs.gp_r11; break;
	case CFI_X86_64_UNWIND_REGISTER_R12:    value = self->ics_gpregs.gp_r12; break;
	case CFI_X86_64_UNWIND_REGISTER_R13:    value = self->ics_gpregs.gp_r13; break;
	case CFI_X86_64_UNWIND_REGISTER_R14:    value = self->ics_gpregs.gp_r14; break;
	case CFI_X86_64_UNWIND_REGISTER_R15:    value = self->ics_gpregs.gp_r15; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP:    value = self->ics_irregs.ir_rip; break;
	case CFI_X86_64_UNWIND_REGISTER_RFLAGS: value = self->ics_irregs.ir_rflags; break;
	case CFI_X86_64_UNWIND_REGISTER_CS:     value = self->ics_irregs.ir_cs16; break;
	case CFI_X86_64_UNWIND_REGISTER_SS:     value = self->ics_irregs.ir_ss16; break;
	default: goto badreg;
	}
	wrpptr(dst, value);
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_setreg_icpustate_base)(struct icpustate *__restrict self,
                                                   unwind_regno_t dw_regno,
                                                   void const *__restrict src) {
	uintptr_t value = rdpptr_as64(src);
	switch (dw_regno) {
	case CFI_X86_64_UNWIND_REGISTER_RAX:    self->ics_gpregs.gp_rax = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RDX:    self->ics_gpregs.gp_rdx = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RCX:    self->ics_gpregs.gp_rcx = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX:    self->ics_gpregs.gp_rbx = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RSI:    self->ics_gpregs.gp_rsi = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RDI:    self->ics_gpregs.gp_rdi = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP:    self->ics_gpregs.gp_rbp = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP:    self->ics_irregs.ir_rsp = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R8:     self->ics_gpregs.gp_r8 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R9:     self->ics_gpregs.gp_r9 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R10:    self->ics_gpregs.gp_r10 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R11:    self->ics_gpregs.gp_r11 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R12:    self->ics_gpregs.gp_r12 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R13:    self->ics_gpregs.gp_r13 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R14:    self->ics_gpregs.gp_r14 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R15:    self->ics_gpregs.gp_r15 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP:    self->ics_irregs.ir_rip = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RFLAGS: self->ics_irregs.ir_rflags = value; break;
	case CFI_X86_64_UNWIND_REGISTER_CS:     self->ics_irregs.ir_cs = (u16)value; break;
	case CFI_X86_64_UNWIND_REGISTER_SS:     self->ics_irregs.ir_ss = (u16)value; break;
	default: goto badreg;
	}
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}
#endif /* __KERNEL__ || __INTELLISENSE__ */

DEFINE_INTERN_ALIAS(libuw_unwind_getreg_fcpustate_exclusive, libuw_unwind_getreg_fcpustate);
INTERN NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_getreg_fcpustate)(struct fcpustate const *__restrict self,
                                              unwind_regno_t dw_regno,
                                              void *__restrict dst) {
	uintptr_t value;
	switch (dw_regno) {
	case CFI_X86_64_UNWIND_REGISTER_RAX:    value = self->fcs_gpregs.gp_rax; break;
	case CFI_X86_64_UNWIND_REGISTER_RDX:    value = self->fcs_gpregs.gp_rdx; break;
	case CFI_X86_64_UNWIND_REGISTER_RCX:    value = self->fcs_gpregs.gp_rcx; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX:    value = self->fcs_gpregs.gp_rbx; break;
	case CFI_X86_64_UNWIND_REGISTER_RSI:    value = self->fcs_gpregs.gp_rsi; break;
	case CFI_X86_64_UNWIND_REGISTER_RDI:    value = self->fcs_gpregs.gp_rdi; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP:    value = self->fcs_gpregs.gp_rbp; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP:    value = self->fcs_gpregs.gp_rsp; break;
	case CFI_X86_64_UNWIND_REGISTER_R8:     value = self->fcs_gpregs.gp_r8; break;
	case CFI_X86_64_UNWIND_REGISTER_R9:     value = self->fcs_gpregs.gp_r9; break;
	case CFI_X86_64_UNWIND_REGISTER_R10:    value = self->fcs_gpregs.gp_r10; break;
	case CFI_X86_64_UNWIND_REGISTER_R11:    value = self->fcs_gpregs.gp_r11; break;
	case CFI_X86_64_UNWIND_REGISTER_R12:    value = self->fcs_gpregs.gp_r12; break;
	case CFI_X86_64_UNWIND_REGISTER_R13:    value = self->fcs_gpregs.gp_r13; break;
	case CFI_X86_64_UNWIND_REGISTER_R14:    value = self->fcs_gpregs.gp_r14; break;
	case CFI_X86_64_UNWIND_REGISTER_R15:    value = self->fcs_gpregs.gp_r15; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP:    value = self->fcs_rip; break;
	case CFI_X86_64_UNWIND_REGISTER_RFLAGS: value = self->fcs_rflags; break;
	case CFI_X86_64_UNWIND_REGISTER_ES:     value = self->fcs_sgregs.sg_es16; break;
	case CFI_X86_64_UNWIND_REGISTER_CS:     value = self->fcs_sgregs.sg_cs16; break;
	case CFI_X86_64_UNWIND_REGISTER_SS:     value = self->fcs_sgregs.sg_ss16; break;
	case CFI_X86_64_UNWIND_REGISTER_DS:     value = self->fcs_sgregs.sg_ds16; break;
	case CFI_X86_64_UNWIND_REGISTER_FS:     value = self->fcs_sgregs.sg_fs16; break;
	case CFI_X86_64_UNWIND_REGISTER_GS:     value = self->fcs_sgregs.sg_gs16; break;
	case CFI_X86_64_UNWIND_REGISTER_FSBASE: value = self->fcs_sgbase.sg_fsbase; break;
	case CFI_X86_64_UNWIND_REGISTER_GSBASE: value = self->fcs_sgbase.sg_gsbase; break;
	case CFI_X86_64_UNWIND_REGISTER_TR:     value = self->fcs_sgregs.sg_tr16; break;
	case CFI_X86_64_UNWIND_REGISTER_LDTR:   value = self->fcs_sgregs.sg_ldt16; break;
	default: goto badreg;
	}
	wrpptr(dst, value);
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

DEFINE_INTERN_ALIAS(libuw_unwind_setreg_fcpustate_exclusive, libuw_unwind_setreg_fcpustate);
INTERN NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_setreg_fcpustate)(struct fcpustate *__restrict self,
                                              unwind_regno_t dw_regno,
                                              void const *__restrict src) {
	uintptr_t value = rdpptr_as64(src);
	switch (dw_regno) {
	case CFI_X86_64_UNWIND_REGISTER_RAX:    self->fcs_gpregs.gp_rax = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RDX:    self->fcs_gpregs.gp_rdx = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RCX:    self->fcs_gpregs.gp_rcx = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RBX:    self->fcs_gpregs.gp_rbx = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RSI:    self->fcs_gpregs.gp_rsi = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RDI:    self->fcs_gpregs.gp_rdi = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RBP:    self->fcs_gpregs.gp_rbp = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RSP:    self->fcs_gpregs.gp_rsp = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R8:     self->fcs_gpregs.gp_r8 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R9:     self->fcs_gpregs.gp_r9 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R10:    self->fcs_gpregs.gp_r10 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R11:    self->fcs_gpregs.gp_r11 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R12:    self->fcs_gpregs.gp_r12 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R13:    self->fcs_gpregs.gp_r13 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R14:    self->fcs_gpregs.gp_r14 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_R15:    self->fcs_gpregs.gp_r15 = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RIP:    self->fcs_rip = value; break;
	case CFI_X86_64_UNWIND_REGISTER_RFLAGS: self->fcs_rflags = value; break;
	case CFI_X86_64_UNWIND_REGISTER_ES:     self->fcs_sgregs.sg_es = value & 0xffff; break;
	case CFI_X86_64_UNWIND_REGISTER_CS:     self->fcs_sgregs.sg_cs = value & 0xffff; break;
	case CFI_X86_64_UNWIND_REGISTER_SS:     self->fcs_sgregs.sg_ss = value & 0xffff; break;
	case CFI_X86_64_UNWIND_REGISTER_DS:     self->fcs_sgregs.sg_ds = value & 0xffff; break;
	case CFI_X86_64_UNWIND_REGISTER_FS:     self->fcs_sgregs.sg_fs = value & 0xffff; break;
	case CFI_X86_64_UNWIND_REGISTER_GS:     self->fcs_sgregs.sg_gs = value & 0xffff; break;
	case CFI_X86_64_UNWIND_REGISTER_FSBASE: self->fcs_sgbase.sg_fsbase = value; break;
	case CFI_X86_64_UNWIND_REGISTER_GSBASE: self->fcs_sgbase.sg_gsbase = value; break;
	case CFI_X86_64_UNWIND_REGISTER_TR:     self->fcs_sgregs.sg_tr = value & 0xffff; break;
	case CFI_X86_64_UNWIND_REGISTER_LDTR:   self->fcs_sgregs.sg_ldt = value & 0xffff; break;
	default: goto badreg;
	}
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

#else /* __x86_64__ */

static_assert(offsetof(struct gpregs, gp_edi) == OFFSET_GPREGS_EDI);
static_assert(offsetof(struct gpregs, gp_esi) == OFFSET_GPREGS_ESI);
static_assert(offsetof(struct gpregs, gp_ebp) == OFFSET_GPREGS_EBP);
static_assert(offsetof(struct gpregs, gp_esp) == OFFSET_GPREGS_ESP);
static_assert(offsetof(struct gpregs, gp_ebx) == OFFSET_GPREGS_EBX);
static_assert(offsetof(struct gpregs, gp_edx) == OFFSET_GPREGS_EDX);
static_assert(offsetof(struct gpregs, gp_ecx) == OFFSET_GPREGS_ECX);
static_assert(offsetof(struct gpregs, gp_eax) == OFFSET_GPREGS_EAX);
static_assert(sizeof(struct gpregs)           == SIZEOF_GPREGS);

static_assert(offsetof(struct sgregs, sg_gs) == OFFSET_SGREGS_GS);
static_assert(offsetof(struct sgregs, sg_fs) == OFFSET_SGREGS_FS);
static_assert(offsetof(struct sgregs, sg_es) == OFFSET_SGREGS_ES);
static_assert(offsetof(struct sgregs, sg_ds) == OFFSET_SGREGS_DS);
static_assert(sizeof(struct sgregs)          == SIZEOF_SGREGS);

static_assert(offsetof(struct coregs, co_cr0) == OFFSET_COREGS_CR0);
static_assert(offsetof(struct coregs, co_cr2) == OFFSET_COREGS_CR2);
static_assert(offsetof(struct coregs, co_cr3) == OFFSET_COREGS_CR3);
static_assert(offsetof(struct coregs, co_cr4) == OFFSET_COREGS_CR4);
static_assert(sizeof(struct coregs)           == SIZEOF_COREGS);

static_assert(offsetof(struct drregs, dr_dr0) == OFFSET_DRREGS_DR0);
static_assert(offsetof(struct drregs, dr_dr1) == OFFSET_DRREGS_DR1);
static_assert(offsetof(struct drregs, dr_dr2) == OFFSET_DRREGS_DR2);
static_assert(offsetof(struct drregs, dr_dr3) == OFFSET_DRREGS_DR3);
static_assert(offsetof(struct drregs, dr_dr6) == OFFSET_DRREGS_DR6);
static_assert(offsetof(struct drregs, dr_dr7) == OFFSET_DRREGS_DR7);
static_assert(sizeof(struct drregs)           == SIZEOF_DRREGS);

static_assert(sizeof(struct irregs_kernel)              == SIZEOF_IRREGS_KERNEL);
static_assert(sizeof(struct irregs_user)                == SIZEOF_IRREGS_USER);
static_assert(sizeof(struct irregs_vm86)                == SIZEOF_IRREGS_VM86);
static_assert(offsetof(struct irregs_kernel, ir_eip)    == OFFSET_IRREGS_EIP);
static_assert(offsetof(struct irregs_user, ir_eip)      == OFFSET_IRREGS_EIP);
static_assert(offsetof(struct irregs_vm86, ir_eip)      == OFFSET_IRREGS_EIP);
static_assert(offsetof(struct irregs_kernel, ir_cs)     == OFFSET_IRREGS_CS);
static_assert(offsetof(struct irregs_user, ir_cs)       == OFFSET_IRREGS_CS);
static_assert(offsetof(struct irregs_vm86, ir_cs)       == OFFSET_IRREGS_CS);
static_assert(offsetof(struct irregs_kernel, ir_eflags) == OFFSET_IRREGS_EFLAGS);
static_assert(offsetof(struct irregs_user, ir_eflags)   == OFFSET_IRREGS_EFLAGS);
static_assert(offsetof(struct irregs_vm86, ir_eflags)   == OFFSET_IRREGS_EFLAGS);
static_assert(offsetof(struct irregs_user, ir_esp)      == OFFSET_IRREGS_ESP);
static_assert(offsetof(struct irregs_vm86, ir_esp)      == OFFSET_IRREGS_ESP);
static_assert(offsetof(struct irregs_user, ir_ss)       == OFFSET_IRREGS_SS);
static_assert(offsetof(struct irregs_vm86, ir_ss)       == OFFSET_IRREGS_SS);
static_assert(offsetof(struct irregs_vm86, ir_es)       == OFFSET_IRREGS_ES);
static_assert(offsetof(struct irregs_vm86, ir_ds)       == OFFSET_IRREGS_DS);
static_assert(offsetof(struct irregs_vm86, ir_fs)       == OFFSET_IRREGS_FS);
static_assert(offsetof(struct irregs_vm86, ir_gs)       == OFFSET_IRREGS_GS);


LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_getreg_lcpustate_base)(struct lcpustate const *__restrict self,
                                                   unwind_regno_t dw_regno,
                                                   void *__restrict dst) {
	uintptr_t value;
	switch (dw_regno) {
	case CFI_386_UNWIND_REGISTER_EDI: value = self->lcs_edi; break;
	case CFI_386_UNWIND_REGISTER_ESI: value = self->lcs_esi; break;
	case CFI_386_UNWIND_REGISTER_EBP: value = self->lcs_ebp; break;
	case CFI_386_UNWIND_REGISTER_ESP: value = self->lcs_esp; break;
	case CFI_386_UNWIND_REGISTER_EBX: value = self->lcs_ebx; break;
	case CFI_386_UNWIND_REGISTER_EIP: value = self->lcs_eip; break;
	default: goto badreg;
	}
	wrpptr(dst, value);
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_setreg_lcpustate_base)(struct lcpustate *__restrict self,
                                                   unwind_regno_t dw_regno,
                                                   void const *__restrict src) {
	uintptr_t value = rdpptr_as32(src);
	switch (dw_regno) {
	case CFI_386_UNWIND_REGISTER_EDI: self->lcs_edi = value; break;
	case CFI_386_UNWIND_REGISTER_ESI: self->lcs_esi = value; break;
	case CFI_386_UNWIND_REGISTER_EBP: self->lcs_ebp = value; break;
	case CFI_386_UNWIND_REGISTER_ESP: self->lcs_esp = value; break;
	case CFI_386_UNWIND_REGISTER_EBX: self->lcs_ebx = value; break;
	case CFI_386_UNWIND_REGISTER_EIP: self->lcs_eip = value; break;
	default: goto badreg;
	}
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_getreg_ucpustate_base)(struct ucpustate const *__restrict self,
                                                   unwind_regno_t dw_regno,
                                                   void *__restrict dst) {
	uintptr_t value;
	switch (dw_regno) {
	case CFI_386_UNWIND_REGISTER_EDI:    value = self->ucs_gpregs.gp_edi; break;
	case CFI_386_UNWIND_REGISTER_ESI:    value = self->ucs_gpregs.gp_esi; break;
	case CFI_386_UNWIND_REGISTER_EBP:    value = self->ucs_gpregs.gp_ebp; break;
	case CFI_386_UNWIND_REGISTER_ESP:    value = self->ucs_gpregs.gp_esp; break;
	case CFI_386_UNWIND_REGISTER_EBX:    value = self->ucs_gpregs.gp_ebx; break;
	case CFI_386_UNWIND_REGISTER_EDX:    value = self->ucs_gpregs.gp_edx; break;
	case CFI_386_UNWIND_REGISTER_ECX:    value = self->ucs_gpregs.gp_ecx; break;
	case CFI_386_UNWIND_REGISTER_EAX:    value = self->ucs_gpregs.gp_eax; break;
	case CFI_386_UNWIND_REGISTER_GS:     value = self->ucs_sgregs.sg_gs16; break;
	case CFI_386_UNWIND_REGISTER_FS:     value = self->ucs_sgregs.sg_fs16; break;
	case CFI_386_UNWIND_REGISTER_ES:     value = self->ucs_sgregs.sg_es16; break;
	case CFI_386_UNWIND_REGISTER_DS:     value = self->ucs_sgregs.sg_ds16; break;
	case CFI_386_UNWIND_REGISTER_CS:     value = self->ucs_cs16; break;
	case CFI_386_UNWIND_REGISTER_SS:     value = self->ucs_ss16; break;
	case CFI_386_UNWIND_REGISTER_EFLAGS: value = self->ucs_eflags; break;
	case CFI_386_UNWIND_REGISTER_EIP:    value = self->ucs_eip; break;
	default: goto badreg;
	}
	wrpptr(dst, value);
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_setreg_ucpustate_base)(struct ucpustate *__restrict self,
                                                   unwind_regno_t dw_regno,
                                                   void const *__restrict src) {
	uintptr_t value = rdpptr_as32(src);
	switch (dw_regno) {
	case CFI_386_UNWIND_REGISTER_EDI:    self->ucs_gpregs.gp_edi = value; break;
	case CFI_386_UNWIND_REGISTER_ESI:    self->ucs_gpregs.gp_esi = value; break;
	case CFI_386_UNWIND_REGISTER_EBP:    self->ucs_gpregs.gp_ebp = value; break;
	case CFI_386_UNWIND_REGISTER_ESP:    self->ucs_gpregs.gp_esp = value; break;
	case CFI_386_UNWIND_REGISTER_EBX:    self->ucs_gpregs.gp_ebx = value; break;
	case CFI_386_UNWIND_REGISTER_EDX:    self->ucs_gpregs.gp_edx = value; break;
	case CFI_386_UNWIND_REGISTER_ECX:    self->ucs_gpregs.gp_ecx = value; break;
	case CFI_386_UNWIND_REGISTER_EAX:    self->ucs_gpregs.gp_eax = value; break;
	case CFI_386_UNWIND_REGISTER_GS:     self->ucs_sgregs.sg_gs = value & 0xffff; break;
	case CFI_386_UNWIND_REGISTER_FS:     self->ucs_sgregs.sg_fs = value & 0xffff; break;
	case CFI_386_UNWIND_REGISTER_ES:     self->ucs_sgregs.sg_es = value & 0xffff; break;
	case CFI_386_UNWIND_REGISTER_DS:     self->ucs_sgregs.sg_ds = value & 0xffff; break;
	case CFI_386_UNWIND_REGISTER_CS:     self->ucs_cs = value & 0xffff; break;
	case CFI_386_UNWIND_REGISTER_SS:     self->ucs_ss = value & 0xffff; break;
	case CFI_386_UNWIND_REGISTER_EFLAGS: self->ucs_eflags = value; break;
	case CFI_386_UNWIND_REGISTER_EIP:    self->ucs_eip = value; break;
	default: goto badreg;
	}
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_getreg_kcpustate_base)(struct kcpustate const *__restrict self,
                                                   unwind_regno_t dw_regno,
                                                   void *__restrict dst) {
	uintptr_t value;
	switch (dw_regno) {
	case CFI_386_UNWIND_REGISTER_EDI:    value = self->kcs_gpregs.gp_edi; break;
	case CFI_386_UNWIND_REGISTER_ESI:    value = self->kcs_gpregs.gp_esi; break;
	case CFI_386_UNWIND_REGISTER_EBP:    value = self->kcs_gpregs.gp_ebp; break;
	case CFI_386_UNWIND_REGISTER_ESP:    value = self->kcs_gpregs.gp_esp; break;
	case CFI_386_UNWIND_REGISTER_EBX:    value = self->kcs_gpregs.gp_ebx; break;
	case CFI_386_UNWIND_REGISTER_EDX:    value = self->kcs_gpregs.gp_edx; break;
	case CFI_386_UNWIND_REGISTER_ECX:    value = self->kcs_gpregs.gp_ecx; break;
	case CFI_386_UNWIND_REGISTER_EAX:    value = self->kcs_gpregs.gp_eax; break;
	case CFI_386_UNWIND_REGISTER_EFLAGS: value = self->kcs_eflags; break;
	case CFI_386_UNWIND_REGISTER_EIP:    value = self->kcs_eip; break;
	default: goto badreg;
	}
	wrpptr(dst, value);
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_setreg_kcpustate_base)(struct kcpustate *__restrict self,
                                                   unwind_regno_t dw_regno,
                                                   void const *__restrict src) {
	uintptr_t value = rdpptr_as32(src);
	switch (dw_regno) {
	case CFI_386_UNWIND_REGISTER_EDI:    self->kcs_gpregs.gp_edi = value; break;
	case CFI_386_UNWIND_REGISTER_ESI:    self->kcs_gpregs.gp_esi = value; break;
	case CFI_386_UNWIND_REGISTER_EBP:    self->kcs_gpregs.gp_ebp = value; break;
	case CFI_386_UNWIND_REGISTER_ESP:    self->kcs_gpregs.gp_esp = value; break;
	case CFI_386_UNWIND_REGISTER_EBX:    self->kcs_gpregs.gp_ebx = value; break;
	case CFI_386_UNWIND_REGISTER_EDX:    self->kcs_gpregs.gp_edx = value; break;
	case CFI_386_UNWIND_REGISTER_ECX:    self->kcs_gpregs.gp_ecx = value; break;
	case CFI_386_UNWIND_REGISTER_EAX:    self->kcs_gpregs.gp_eax = value; break;
	case CFI_386_UNWIND_REGISTER_EFLAGS: self->kcs_eflags = value; break;
	case CFI_386_UNWIND_REGISTER_EIP:    self->kcs_eip = value; break;
	default: goto badreg;
	}
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}


#if defined(__KERNEL__) || defined(__INTELLISENSE__)
LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_getreg_scpustate_base)(struct scpustate const *__restrict self,
                                                   unwind_regno_t dw_regno,
                                                   void *__restrict dst) {
	uintptr_t value;
	switch (dw_regno) {
	case CFI_386_UNWIND_REGISTER_EDI:    value = self->scs_gpregs.gp_edi; break;
	case CFI_386_UNWIND_REGISTER_ESI:    value = self->scs_gpregs.gp_esi; break;
	case CFI_386_UNWIND_REGISTER_EBP:    value = self->scs_gpregs.gp_ebp; break;
	case CFI_386_UNWIND_REGISTER_ESP:    value = scpustate_getpsp(self); break;
	case CFI_386_UNWIND_REGISTER_EBX:    value = self->scs_gpregs.gp_ebx; break;
	case CFI_386_UNWIND_REGISTER_EDX:    value = self->scs_gpregs.gp_edx; break;
	case CFI_386_UNWIND_REGISTER_ECX:    value = self->scs_gpregs.gp_ecx; break;
	case CFI_386_UNWIND_REGISTER_EAX:    value = self->scs_gpregs.gp_eax; break;
	case CFI_386_UNWIND_REGISTER_GS:     value = scpustate_getgs(self); break;
	case CFI_386_UNWIND_REGISTER_FS:     value = scpustate_getfs(self); break;
	case CFI_386_UNWIND_REGISTER_ES:     value = scpustate_getes(self); break;
	case CFI_386_UNWIND_REGISTER_DS:     value = scpustate_getds(self); break;
	case CFI_386_UNWIND_REGISTER_CS:     value = scpustate_getcs(self); break;
	case CFI_386_UNWIND_REGISTER_SS:     value = scpustate_getss(self); break;
	case CFI_386_UNWIND_REGISTER_EFLAGS: value = scpustate_getpflags(self); break;
	case CFI_386_UNWIND_REGISTER_EIP:    value = scpustate_getpip(self); break;
	default: goto badreg;
	}
	wrpptr(dst, value);
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_setreg_scpustate_base_p)(struct scpustate **__restrict pself,
                                                     unwind_regno_t dw_regno,
                                                     void const *__restrict src) {
	struct scpustate *self = *pself;
	uintptr_t value = rdpptr_as32(src);
	switch (dw_regno) {
	case CFI_386_UNWIND_REGISTER_EDI: self->scs_gpregs.gp_edi = value; break;
	case CFI_386_UNWIND_REGISTER_ESI: self->scs_gpregs.gp_esi = value; break;
	case CFI_386_UNWIND_REGISTER_EBP: self->scs_gpregs.gp_ebp = value; break;
	case CFI_386_UNWIND_REGISTER_ESP: *pself = scpustate_setpsp_p(self, value); break;
	case CFI_386_UNWIND_REGISTER_EBX: self->scs_gpregs.gp_ebx = value; break;
	case CFI_386_UNWIND_REGISTER_EDX: self->scs_gpregs.gp_edx = value; break;
	case CFI_386_UNWIND_REGISTER_ECX: self->scs_gpregs.gp_ecx = value; break;
	case CFI_386_UNWIND_REGISTER_EAX: self->scs_gpregs.gp_eax = value; break;
	case CFI_386_UNWIND_REGISTER_GS:  scpustate_setgs(self, value & 0xffff); break;
	case CFI_386_UNWIND_REGISTER_FS:  scpustate_setfs(self, value & 0xffff); break;
	case CFI_386_UNWIND_REGISTER_ES:  scpustate_setes(self, value & 0xffff); break;
	case CFI_386_UNWIND_REGISTER_DS:  scpustate_setds(self, value & 0xffff); break;
	case CFI_386_UNWIND_REGISTER_EIP: scpustate_setpip(self, value); break;
	case CFI_386_UNWIND_REGISTER_SS:
		if (!scpustate_trysetuserss(self, value))
			goto badreg;
		break;

	case CFI_386_UNWIND_REGISTER_CS: {
		u16 newval, oldval;
		newval = value & 0xffff;
		oldval = scpustate_getcs(self);
		/* Must not switch between user-space/kernel-space contexts. */
		if (((newval & 3) != 0) != ((oldval & 3) != 0))
			goto badreg;
		scpustate_setcs(self, newval);
	}	break;

	case CFI_386_UNWIND_REGISTER_EFLAGS: {
		u32 newval, oldval;
		newval = value;
		oldval = scpustate_getpflags(self);

		/* Must not switch to/from vm86 contexts. */
		if ((oldval & EFLAGS_VM) != (newval & EFLAGS_VM))
			goto badreg;
		scpustate_setpflags(self, newval);
	}	break;

	default: goto badreg;
	}
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_getreg_icpustate_base)(struct icpustate const *__restrict self,
                                                   unwind_regno_t dw_regno,
                                                   void *__restrict dst) {
	uintptr_t value;
	switch (dw_regno) {
	case CFI_386_UNWIND_REGISTER_EDI:    value = self->ics_gpregs.gp_edi; break;
	case CFI_386_UNWIND_REGISTER_ESI:    value = self->ics_gpregs.gp_esi; break;
	case CFI_386_UNWIND_REGISTER_EBP:    value = self->ics_gpregs.gp_ebp; break;
	case CFI_386_UNWIND_REGISTER_ESP:    value = icpustate_getpsp(self); break;
	case CFI_386_UNWIND_REGISTER_EBX:    value = self->ics_gpregs.gp_ebx; break;
	case CFI_386_UNWIND_REGISTER_EDX:    value = self->ics_gpregs.gp_edx; break;
	case CFI_386_UNWIND_REGISTER_ECX:    value = self->ics_gpregs.gp_ecx; break;
	case CFI_386_UNWIND_REGISTER_EAX:    value = self->ics_gpregs.gp_eax; break;
	case CFI_386_UNWIND_REGISTER_GS:     value = icpustate_getgs(self); break;
	case CFI_386_UNWIND_REGISTER_FS:     value = icpustate_getfs(self); break;
	case CFI_386_UNWIND_REGISTER_ES:     value = icpustate_getes(self); break;
	case CFI_386_UNWIND_REGISTER_DS:     value = icpustate_getds(self); break;
	case CFI_386_UNWIND_REGISTER_CS:     value = icpustate_getcs(self); break;
	case CFI_386_UNWIND_REGISTER_SS:     value = icpustate_getss(self); break;
	case CFI_386_UNWIND_REGISTER_EFLAGS: value = icpustate_getpflags(self); break;
	case CFI_386_UNWIND_REGISTER_EIP:    value = icpustate_getpip(self); break;
	default: goto badreg;
	}
	wrpptr(dst, value);
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_setreg_icpustate_base_p)(struct icpustate **__restrict pself,
                                                     unwind_regno_t dw_regno,
                                                     void const *__restrict src) {
	struct icpustate *self = *pself;
	uintptr_t value = rdpptr_as32(src);
	switch (dw_regno) {
	case CFI_386_UNWIND_REGISTER_EDI:    self->ics_gpregs.gp_edi = value; break;
	case CFI_386_UNWIND_REGISTER_ESI:    self->ics_gpregs.gp_esi = value; break;
	case CFI_386_UNWIND_REGISTER_EBP:    self->ics_gpregs.gp_ebp = value; break;
	case CFI_386_UNWIND_REGISTER_ESP:    *pself = icpustate_setpsp_p(self, value); break;
	case CFI_386_UNWIND_REGISTER_EBX:    self->ics_gpregs.gp_ebx = value; break;
	case CFI_386_UNWIND_REGISTER_EDX:    self->ics_gpregs.gp_edx = value; break;
	case CFI_386_UNWIND_REGISTER_ECX:    self->ics_gpregs.gp_ecx = value; break;
	case CFI_386_UNWIND_REGISTER_EAX:    self->ics_gpregs.gp_eax = value; break;
	case CFI_386_UNWIND_REGISTER_GS:     icpustate_setgs(self, value & 0xffff); break;
	case CFI_386_UNWIND_REGISTER_FS:     icpustate_setfs(self, value & 0xffff); break;
	case CFI_386_UNWIND_REGISTER_ES:     icpustate_setes(self, value & 0xffff); break;
	case CFI_386_UNWIND_REGISTER_DS:     icpustate_setds(self, value & 0xffff); break;
	case CFI_386_UNWIND_REGISTER_EIP:    icpustate_setpip(self, value); break;
	case CFI_386_UNWIND_REGISTER_SS:
		if (!icpustate_trysetuserss(self, value))
			goto badreg;
		break;

	case CFI_386_UNWIND_REGISTER_CS: {
		u16 newval, oldval;
		newval = value & 0xffff;
		oldval = icpustate_getcs(self);
		if (oldval == newval)
			break;
		/* Must not switch between user-space/kernel-space contexts. */
		if (((newval & 3) != 0) != ((oldval & 3) != 0))
			goto badreg;
		icpustate_setcs(self, newval);
	}	break;

	case CFI_386_UNWIND_REGISTER_EFLAGS: {
		u32 newval, oldval;
		newval = value;
		oldval = icpustate_getpflags(self);

		/* Must not switch to/from vm86 contexts. */
		if ((oldval & EFLAGS_VM) != (newval & EFLAGS_VM))
			goto badreg;
		icpustate_setpflags(self, newval);
	}	break;

	default: goto badreg;
	}
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}
#endif /* __KERNEL__ */

DEFINE_INTERN_ALIAS(libuw_unwind_getreg_fcpustate_exclusive, libuw_unwind_getreg_fcpustate);
INTERN NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_getreg_fcpustate)(struct fcpustate const *__restrict self,
                                              unwind_regno_t dw_regno,
                                              void *__restrict dst) {
	uintptr_t value;
	switch (dw_regno) {
	case CFI_386_UNWIND_REGISTER_EDI:    value = self->fcs_gpregs.gp_edi; break;
	case CFI_386_UNWIND_REGISTER_ESI:    value = self->fcs_gpregs.gp_esi; break;
	case CFI_386_UNWIND_REGISTER_EBP:    value = self->fcs_gpregs.gp_ebp; break;
	case CFI_386_UNWIND_REGISTER_ESP:    value = self->fcs_gpregs.gp_esp; break;
	case CFI_386_UNWIND_REGISTER_EBX:    value = self->fcs_gpregs.gp_ebx; break;
	case CFI_386_UNWIND_REGISTER_EDX:    value = self->fcs_gpregs.gp_edx; break;
	case CFI_386_UNWIND_REGISTER_ECX:    value = self->fcs_gpregs.gp_ecx; break;
	case CFI_386_UNWIND_REGISTER_EAX:    value = self->fcs_gpregs.gp_eax; break;
	case CFI_386_UNWIND_REGISTER_GS:     value = self->fcs_sgregs.sg_gs16; break;
	case CFI_386_UNWIND_REGISTER_FS:     value = self->fcs_sgregs.sg_fs16; break;
	case CFI_386_UNWIND_REGISTER_ES:     value = self->fcs_sgregs.sg_es16; break;
	case CFI_386_UNWIND_REGISTER_DS:     value = self->fcs_sgregs.sg_ds16; break;
	case CFI_386_UNWIND_REGISTER_CS:     value = self->fcs_sgregs.sg_cs16; break;
	case CFI_386_UNWIND_REGISTER_SS:     value = self->fcs_sgregs.sg_ss16; break;
	case CFI_386_UNWIND_REGISTER_EFLAGS: value = self->fcs_eflags; break;
	case CFI_386_UNWIND_REGISTER_EIP:    value = self->fcs_eip; break;
	case CFI_386_UNWIND_REGISTER_TR:     value = self->fcs_sgregs.sg_tr16; break;
	case CFI_386_UNWIND_REGISTER_LDTR:   value = self->fcs_sgregs.sg_ldt16; break;
	default: goto badreg;
	}
	wrpptr(dst, value);
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

DEFINE_INTERN_ALIAS(libuw_unwind_setreg_fcpustate_exclusive, libuw_unwind_setreg_fcpustate);
INTERN NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_setreg_fcpustate)(struct fcpustate *__restrict self,
                                              unwind_regno_t dw_regno,
                                              void const *__restrict src) {
	uintptr_t value = rdpptr_as32(src);
	switch (dw_regno) {
	case CFI_386_UNWIND_REGISTER_EDI:    self->fcs_gpregs.gp_edi = value; break;
	case CFI_386_UNWIND_REGISTER_ESI:    self->fcs_gpregs.gp_esi = value; break;
	case CFI_386_UNWIND_REGISTER_EBP:    self->fcs_gpregs.gp_ebp = value; break;
	case CFI_386_UNWIND_REGISTER_ESP:    self->fcs_gpregs.gp_esp = value; break;
	case CFI_386_UNWIND_REGISTER_EBX:    self->fcs_gpregs.gp_ebx = value; break;
	case CFI_386_UNWIND_REGISTER_EDX:    self->fcs_gpregs.gp_edx = value; break;
	case CFI_386_UNWIND_REGISTER_ECX:    self->fcs_gpregs.gp_ecx = value; break;
	case CFI_386_UNWIND_REGISTER_EAX:    self->fcs_gpregs.gp_eax = value; break;
	case CFI_386_UNWIND_REGISTER_GS:     self->fcs_sgregs.sg_gs = value & 0xffff; break;
	case CFI_386_UNWIND_REGISTER_FS:     self->fcs_sgregs.sg_fs = value & 0xffff; break;
	case CFI_386_UNWIND_REGISTER_ES:     self->fcs_sgregs.sg_es = value & 0xffff; break;
	case CFI_386_UNWIND_REGISTER_DS:     self->fcs_sgregs.sg_ds = value & 0xffff; break;
	case CFI_386_UNWIND_REGISTER_CS:     self->fcs_sgregs.sg_cs = value & 0xffff; break;
	case CFI_386_UNWIND_REGISTER_SS:     self->fcs_sgregs.sg_ss = value & 0xffff; break;
	case CFI_386_UNWIND_REGISTER_EFLAGS: self->fcs_eflags = value; break;
	case CFI_386_UNWIND_REGISTER_EIP:    self->fcs_eip = value; break;
	case CFI_386_UNWIND_REGISTER_TR:     self->fcs_sgregs.sg_tr = value & 0xffff; break;
	case CFI_386_UNWIND_REGISTER_LDTR:   self->fcs_sgregs.sg_ldt = value & 0xffff; break;
	default: goto badreg;
	}
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}
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



LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_getreg_sfpustate_base)(struct sfpustate const *__restrict self,
                                                   unwind_regno_t dw_regno,
                                                   void *__restrict dst) {
	switch (dw_regno) {

	case CFI_UNWIND_REGISTER_MM0 ... CFI_UNWIND_REGISTER_MM7:
		dw_regno -= CFI_UNWIND_REGISTER_MM0;
		goto do_fpreg;
	case CFI_UNWIND_REGISTER_ST0 ... CFI_UNWIND_REGISTER_ST7:
		dw_regno -= CFI_UNWIND_REGISTER_ST0;
do_fpreg:
		bzero(mempcpy((byte_t *)dst, &self->fs_regs[dw_regno], 10), 6);
		break;

	case CFI_UNWIND_REGISTER_FCW:
		wrpptr(dst, self->fs_fcw);
		break;

	case CFI_UNWIND_REGISTER_FSW:
		wrpptr(dst, self->fs_fsw);
		break;

	default: goto badreg;
	}
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_setreg_sfpustate_base)(struct sfpustate *__restrict self,
                                                   unwind_regno_t dw_regno,
                                                   void const *__restrict src) {
	switch (dw_regno) {

	case CFI_UNWIND_REGISTER_MM0 ... CFI_UNWIND_REGISTER_MM7:
		dw_regno -= CFI_UNWIND_REGISTER_MM0;
		goto do_fpreg;
	case CFI_UNWIND_REGISTER_ST0 ... CFI_UNWIND_REGISTER_ST7:
		dw_regno -= CFI_UNWIND_REGISTER_ST0;
do_fpreg:
		memcpy(&self->fs_regs[dw_regno], src, 10);
		break;

	case CFI_UNWIND_REGISTER_FCW:
		self->fs_fcw = rdpptr_as16(src);
		break;

	case CFI_UNWIND_REGISTER_FSW:
		self->fs_fsw = rdpptr_as16(src);
		break;

	default: goto badreg;
	}
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_getreg_xfpustate_base)(struct xfpustate const *__restrict self,
                                                   unwind_regno_t dw_regno,
                                                   void *__restrict dst) {
	switch (dw_regno) {

	case CFI_UNWIND_REGISTER_MM0 ... CFI_UNWIND_REGISTER_MM7:
		dw_regno -= CFI_UNWIND_REGISTER_MM0;
		goto do_fpreg;
	case CFI_UNWIND_REGISTER_ST0 ... CFI_UNWIND_REGISTER_ST7:
		dw_regno -= CFI_UNWIND_REGISTER_ST0;
do_fpreg:
		memcpy(dst, &self->fx_regs[dw_regno], 16);
		break;

	case CFI_UNWIND_REGISTER_FCW:
		wrpptr(dst, self->fx_fcw);
		break;

	case CFI_UNWIND_REGISTER_FSW:
		wrpptr(dst, self->fx_fsw);
		break;

	case CFI_UNWIND_REGISTER_MXCSR:
		wrpptr(dst, self->fx_mxcsr);
		break;

#ifdef __x86_64__
	case CFI_UNWIND_REGISTER_XMM0 ... CFI_UNWIND_REGISTER_XMM15:
#else /* __x86_64__ */
	case CFI_UNWIND_REGISTER_XMM0 ... CFI_UNWIND_REGISTER_XMM7:
#endif /* !__x86_64__ */
		memcpy(dst, &self->fx_xmm[dw_regno - CFI_UNWIND_REGISTER_XMM0], 16);
		break;

	default: goto badreg;
	}
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_setreg_xfpustate_base)(struct xfpustate *__restrict self,
                                                   unwind_regno_t dw_regno,
                                                   void const *__restrict src) {
	switch (dw_regno) {

	case CFI_UNWIND_REGISTER_MM0 ... CFI_UNWIND_REGISTER_MM7:
		dw_regno -= CFI_UNWIND_REGISTER_MM0;
		goto do_fpreg;
	case CFI_UNWIND_REGISTER_ST0 ... CFI_UNWIND_REGISTER_ST7:
		dw_regno -= CFI_UNWIND_REGISTER_ST0;
do_fpreg:
		memcpy(&self->fx_regs[dw_regno], src, 16);
		break;

	case CFI_UNWIND_REGISTER_FCW:
		self->fx_fcw = rdpptr_as16(src);
		break;

	case CFI_UNWIND_REGISTER_FSW:
		self->fx_fsw = rdpptr_as16(src);
		break;

	case CFI_UNWIND_REGISTER_MXCSR:
		self->fx_mxcsr = rdpptr_as32(src);
		break;

#ifdef __x86_64__
	case CFI_UNWIND_REGISTER_XMM0 ... CFI_UNWIND_REGISTER_XMM15:
#else /* __x86_64__ */
	case CFI_UNWIND_REGISTER_XMM0 ... CFI_UNWIND_REGISTER_XMM7:
#endif /* !__x86_64__ */
		memcpy(&self->fx_xmm[dw_regno - CFI_UNWIND_REGISTER_XMM0], src, 16);
		break;

	default: goto badreg;
	}
	return UNWIND_SUCCESS;
badreg:
	return UNWIND_INVALID_REGISTER;
}

LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_getreg_fpustate_base)(struct fpustate const *__restrict self,
                                                  unwind_regno_t dw_regno,
                                                  void *__restrict dst) {
	unwind_errno_t result;
	if (fpustate_isssave(self)) {
		result = libuw_unwind_getreg_sfpustate_base(&self->f_ssave, dw_regno, dst);
	} else {
		result = libuw_unwind_getreg_xfpustate_base(&self->f_xsave, dw_regno, dst);
	}
	return result;
}

LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_setreg_fpustate_base)(struct fpustate *__restrict self,
                                                  unwind_regno_t dw_regno,
                                                  void const *__restrict src) {
	unwind_errno_t result;
	if (fpustate_isssave(self)) {
		result = libuw_unwind_setreg_sfpustate_base(&self->f_ssave, dw_regno, src);
	} else {
		result = libuw_unwind_setreg_xfpustate_base(&self->f_xsave, dw_regno, src);
	}
	return result;
}


#if !defined(__KERNEL__) || defined(__INTELLISENSE__)
LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_getreg_mcontext_base)(struct mcontext const *__restrict self,
                                                  unwind_regno_t dw_regno,
                                                  void *__restrict dst) {
	unwind_errno_t result;
	result = libuw_unwind_getreg_ucpustate_base(&self->mc_context, dw_regno, dst);
	if (result == UNWIND_INVALID_REGISTER) {
		if (self->mc_flags & MCONTEXT_FLAG_HAVEFPU) {
			result = libuw_unwind_getreg_fpustate_base(&self->mc_fpu, dw_regno, dst);
		}
	}
	return result;
}

LOCAL NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_setreg_mcontext_base)(struct mcontext *__restrict self,
                                                  unwind_regno_t dw_regno,
                                                  void const *__restrict src) {
	unwind_errno_t result;
	result = libuw_unwind_setreg_ucpustate_base(&self->mc_context, dw_regno, src);
	if (result == UNWIND_INVALID_REGISTER) {
		if (self->mc_flags & MCONTEXT_FLAG_HAVEFPU) {
			result = libuw_unwind_setreg_fpustate_base(&self->mc_fpu, dw_regno, src);
		}
	}
	return result;
}
#endif /* !__KERNEL__ || __INTELLISENSE__ */





#define DEFINE_CPUSTATE_GETTERS(get_struct_xcpustate,                                             \
                                set_struct_xcpustate,                                             \
                                libuw_unwind_getreg_xcpustate,                                    \
                                libuw_unwind_getreg_xcpustate_base,                               \
                                libuw_unwind_getreg_xcpustate_exclusive,                          \
                                libuw_unwind_setreg_xcpustate,                                    \
                                libuw_unwind_setreg_xcpustate_base,                               \
                                libuw_unwind_setreg_xcpustate_exclusive)                          \
	INTERN NONNULL((1, 3)) unwind_errno_t                                                         \
	NOTHROW_NCX(CC libuw_unwind_getreg_xcpustate)(get_struct_xcpustate __restrict self,           \
	                                              unwind_regno_t dw_regno,                        \
	                                              void *__restrict dst) {                         \
		unwind_errno_t result;                                                                    \
		result = libuw_unwind_getreg_xcpustate_base(self, dw_regno, dst);                         \
		if (result != UNWIND_SUCCESS)                                                             \
			result = libuw_unwind_getreg_implicit(dw_regno, dst);                                 \
		return result;                                                                            \
	}                                                                                             \
	INTERN NONNULL((1, 3)) unwind_errno_t                                                         \
	NOTHROW_NCX(CC libuw_unwind_setreg_xcpustate)(set_struct_xcpustate __restrict self,           \
	                                              unwind_regno_t dw_regno,                        \
	                                              void const *__restrict src) {                   \
		unwind_errno_t result;                                                                    \
		result = libuw_unwind_setreg_xcpustate_base(self, dw_regno, src);                         \
		if (result != UNWIND_SUCCESS)                                                             \
			result = libuw_unwind_setreg_implicit(dw_regno, src);                                 \
		return result;                                                                            \
	}                                                                                             \
	INTERN NONNULL((1, 3)) unwind_errno_t                                                         \
	NOTHROW_NCX(CC libuw_unwind_getreg_xcpustate_exclusive)(get_struct_xcpustate __restrict self, \
	                                                        unwind_regno_t dw_regno,              \
	                                                        void *__restrict dst) {               \
		return libuw_unwind_getreg_xcpustate_base(self, dw_regno, dst);                           \
	}                                                                                             \
	INTERN NONNULL((1, 3)) unwind_errno_t                                                         \
	NOTHROW_NCX(CC libuw_unwind_setreg_xcpustate_exclusive)(set_struct_xcpustate __restrict self, \
	                                                        unwind_regno_t dw_regno,              \
	                                                        void const *__restrict src) {         \
		return libuw_unwind_setreg_xcpustate_base(self, dw_regno, src);                           \
	}

DEFINE_CPUSTATE_GETTERS(struct lcpustate const *,
                        struct lcpustate *,
                        libuw_unwind_getreg_lcpustate,
                        libuw_unwind_getreg_lcpustate_base,
                        libuw_unwind_getreg_lcpustate_exclusive,
                        libuw_unwind_setreg_lcpustate,
                        libuw_unwind_setreg_lcpustate_base,
                        libuw_unwind_setreg_lcpustate_exclusive)
DEFINE_CPUSTATE_GETTERS(struct ucpustate const *,
                        struct ucpustate *,
                        libuw_unwind_getreg_ucpustate,
                        libuw_unwind_getreg_ucpustate_base,
                        libuw_unwind_getreg_ucpustate_exclusive,
                        libuw_unwind_setreg_ucpustate,
                        libuw_unwind_setreg_ucpustate_base,
                        libuw_unwind_setreg_ucpustate_exclusive)
DEFINE_CPUSTATE_GETTERS(struct kcpustate const *,
                        struct kcpustate *,
                        libuw_unwind_getreg_kcpustate,
                        libuw_unwind_getreg_kcpustate_base,
                        libuw_unwind_getreg_kcpustate_exclusive,
                        libuw_unwind_setreg_kcpustate,
                        libuw_unwind_setreg_kcpustate_base,
                        libuw_unwind_setreg_kcpustate_exclusive)
#if defined(__KERNEL__) || defined(__INTELLISENSE__)
DEFINE_CPUSTATE_GETTERS(struct scpustate const *,
                        struct scpustate IRREGS_INDIRECTION,
                        libuw_unwind_getreg_scpustate,
                        libuw_unwind_getreg_scpustate_base,
                        libuw_unwind_getreg_scpustate_exclusive,
                        IRREGS_NAME(libuw_unwind_setreg_scpustate),
                        IRREGS_NAME(libuw_unwind_setreg_scpustate_base),
                        IRREGS_NAME(libuw_unwind_setreg_scpustate_exclusive))
DEFINE_CPUSTATE_GETTERS(struct icpustate const *,
                        struct icpustate IRREGS_INDIRECTION,
                        libuw_unwind_getreg_icpustate,
                        libuw_unwind_getreg_icpustate_base,
                        libuw_unwind_getreg_icpustate_exclusive,
                        IRREGS_NAME(libuw_unwind_setreg_icpustate),
                        IRREGS_NAME(libuw_unwind_setreg_icpustate_base),
                        IRREGS_NAME(libuw_unwind_setreg_icpustate_exclusive))
#undef IRREGS_INDIRECTION
#endif /* __KERNEL__ || __INTELLISENSE__ */

#if !defined(__KERNEL__) || defined(__INTELLISENSE__)
DEFINE_CPUSTATE_GETTERS(struct mcontext const *,
                        struct mcontext *,
                        libuw_unwind_getreg_mcontext,
                        libuw_unwind_getreg_mcontext_base,
                        libuw_unwind_getreg_mcontext_exclusive,
                        libuw_unwind_setreg_mcontext,
                        libuw_unwind_setreg_mcontext_base,
                        libuw_unwind_setreg_mcontext_exclusive)
DEFINE_INTERN_ALIAS(libuw_unwind_getreg_ucontext, libuw_unwind_getreg_mcontext);
DEFINE_INTERN_ALIAS(libuw_unwind_setreg_ucontext, libuw_unwind_setreg_mcontext);
DEFINE_INTERN_ALIAS(libuw_unwind_getreg_ucontext_exclusive, libuw_unwind_getreg_mcontext_exclusive);
DEFINE_INTERN_ALIAS(libuw_unwind_setreg_ucontext_exclusive, libuw_unwind_setreg_mcontext_exclusive);
#endif /* !__KERNEL__ || __INTELLISENSE__ */
DEFINE_CPUSTATE_GETTERS(struct fpustate const *,
                        struct fpustate *,
                        libuw_unwind_getreg_fpustate,
                        libuw_unwind_getreg_fpustate_base,
                        libuw_unwind_getreg_fpustate_exclusive,
                        libuw_unwind_setreg_fpustate,
                        libuw_unwind_setreg_fpustate_base,
                        libuw_unwind_setreg_fpustate_exclusive)
#undef DEFINE_CPUSTATE_GETTERS

DEFINE_PUBLIC_ALIAS(unwind_getreg_lcpustate, libuw_unwind_getreg_lcpustate);
DEFINE_PUBLIC_ALIAS(unwind_setreg_lcpustate, libuw_unwind_setreg_lcpustate);
DEFINE_PUBLIC_ALIAS(unwind_getreg_ucpustate, libuw_unwind_getreg_ucpustate);
DEFINE_PUBLIC_ALIAS(unwind_setreg_ucpustate, libuw_unwind_setreg_ucpustate);
DEFINE_PUBLIC_ALIAS(unwind_getreg_kcpustate, libuw_unwind_getreg_kcpustate);
DEFINE_PUBLIC_ALIAS(unwind_setreg_kcpustate, libuw_unwind_setreg_kcpustate);
DEFINE_PUBLIC_ALIAS(unwind_getreg_fcpustate, libuw_unwind_getreg_fcpustate);
DEFINE_PUBLIC_ALIAS(unwind_setreg_fcpustate, libuw_unwind_setreg_fcpustate);
DEFINE_PUBLIC_ALIAS(unwind_getreg_lcpustate_exclusive, libuw_unwind_getreg_lcpustate_exclusive);
DEFINE_PUBLIC_ALIAS(unwind_setreg_lcpustate_exclusive, libuw_unwind_setreg_lcpustate_exclusive);
DEFINE_PUBLIC_ALIAS(unwind_getreg_ucpustate_exclusive, libuw_unwind_getreg_ucpustate_exclusive);
DEFINE_PUBLIC_ALIAS(unwind_setreg_ucpustate_exclusive, libuw_unwind_setreg_ucpustate_exclusive);
DEFINE_PUBLIC_ALIAS(unwind_getreg_kcpustate_exclusive, libuw_unwind_getreg_kcpustate_exclusive);
DEFINE_PUBLIC_ALIAS(unwind_setreg_kcpustate_exclusive, libuw_unwind_setreg_kcpustate_exclusive);
DEFINE_PUBLIC_ALIAS(unwind_getreg_fcpustate_exclusive, libuw_unwind_getreg_fcpustate_exclusive);
DEFINE_PUBLIC_ALIAS(unwind_setreg_fcpustate_exclusive, libuw_unwind_setreg_fcpustate_exclusive);

#if defined(__KERNEL__) || defined(__INTELLISENSE__)
DEFINE_PUBLIC_ALIAS(unwind_getreg_scpustate, libuw_unwind_getreg_scpustate);
DEFINE_PUBLIC_ALIAS(IRREGS_NAME(unwind_setreg_scpustate), IRREGS_NAME(libuw_unwind_setreg_scpustate));
DEFINE_PUBLIC_ALIAS(unwind_getreg_icpustate, libuw_unwind_getreg_icpustate);
DEFINE_PUBLIC_ALIAS(IRREGS_NAME(unwind_setreg_icpustate), IRREGS_NAME(libuw_unwind_setreg_icpustate));
DEFINE_PUBLIC_ALIAS(unwind_getreg_scpustate_exclusive, libuw_unwind_getreg_scpustate_exclusive);
DEFINE_PUBLIC_ALIAS(IRREGS_NAME(unwind_setreg_scpustate_exclusive), IRREGS_NAME(libuw_unwind_setreg_scpustate_exclusive));
DEFINE_PUBLIC_ALIAS(unwind_getreg_icpustate_exclusive, libuw_unwind_getreg_icpustate_exclusive);
DEFINE_PUBLIC_ALIAS(IRREGS_NAME(unwind_setreg_icpustate_exclusive), IRREGS_NAME(libuw_unwind_setreg_icpustate_exclusive));
#endif /* __KERNEL__ || __INTELLISENSE__ */

#if !defined(__KERNEL__) || defined(__INTELLISENSE__)
DEFINE_PUBLIC_ALIAS(unwind_getreg_ucontext, libuw_unwind_getreg_ucontext);
DEFINE_PUBLIC_ALIAS(unwind_setreg_ucontext, libuw_unwind_setreg_ucontext);
DEFINE_PUBLIC_ALIAS(unwind_getreg_mcontext, libuw_unwind_getreg_mcontext);
DEFINE_PUBLIC_ALIAS(unwind_setreg_mcontext, libuw_unwind_setreg_mcontext);
DEFINE_PUBLIC_ALIAS(unwind_getreg_ucontext_exclusive, libuw_unwind_getreg_ucontext_exclusive);
DEFINE_PUBLIC_ALIAS(unwind_setreg_ucontext_exclusive, libuw_unwind_setreg_ucontext_exclusive);
DEFINE_PUBLIC_ALIAS(unwind_getreg_mcontext_exclusive, libuw_unwind_getreg_mcontext_exclusive);
DEFINE_PUBLIC_ALIAS(unwind_setreg_mcontext_exclusive, libuw_unwind_setreg_mcontext_exclusive);
#endif /* !__KERNEL__ || __INTELLISENSE__ */

DEFINE_PUBLIC_ALIAS(unwind_getreg_fpustate, libuw_unwind_getreg_fpustate);
DEFINE_PUBLIC_ALIAS(unwind_setreg_fpustate, libuw_unwind_setreg_fpustate);
DEFINE_PUBLIC_ALIAS(unwind_getreg_fpustate_exclusive, libuw_unwind_getreg_fpustate_exclusive);
DEFINE_PUBLIC_ALIAS(unwind_setreg_fpustate_exclusive, libuw_unwind_setreg_fpustate_exclusive);

#undef IRREGS_NAME
#undef IRREGS_INDIRECTION
#undef IRREGS_SELF
#undef IRREGS_LOADSELF

#ifdef LIBUNWIND_HAVE_GETSETREG_COMPAT
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_getreg_compat)(/*struct unwind_getreg_compat_data **/ void const *arg, unwind_regno_t regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_compat)(/*struct unwind_setreg_compat_data **/ void *arg, unwind_regno_t regno, void const *__restrict src);

/*[[[deemon
import fs;
import * from deemon;
import * from .....misc.libgen.strendN;
import * from .....misc.libgen.converter;
local macros: {string: int} = Dict();
function loadMacros(m: {string: string}) {
	for (local name, value: m) {
		if (name.startswith("CFI_386_UNWIND_REGISTER_E") || name.startswith("CFI_386_UNWIND_REGISTER_R"))
			name = "CFI_386_UNWIND_REGISTER_P" + name[#"CFI_386_UNWIND_REGISTER_E":];
		if (name.startswith("CFI_X86_64_UNWIND_REGISTER_E") || name.startswith("CFI_X86_64_UNWIND_REGISTER_R"))
			name = "CFI_X86_64_UNWIND_REGISTER_P" + name[#"CFI_X86_64_UNWIND_REGISTER_R":];
		macros[name] = value;
	}
}
loadMacros(enumerateIntegerMacrosFromFile(fs.headof(__FILE__) + "/../../../../include/libunwind/cfi/i386.h"));
loadMacros(enumerateIntegerMacrosFromFile(fs.headof(__FILE__) + "/../../../../include/libunwind/cfi/x86_64.h"));
del macros["CFI_386_UNWIND_GPR_REGISTER_SIZE"];
del macros["CFI_X86_64_UNWIND_GPR_REGISTER_SIZE"];
printArrayDefineMacro("DEFINE_386_to_amd64",
	generateArrayMapping(macros, "CFI_386_UNWIND_REGISTER_", "CFI_X86_64_UNWIND_REGISTER_"));
]]]*/
#define DEFINE_386_to_amd64(name)                                                                                      \
	__UINT8_TYPE__ const name[102] = { 0,   2,   1,   3,   7,   6,   4,   5,   16,  49,  255, 33,  34,  35,  36,  37,  \
	                                   38,  39,  40,  255, 255, 17,  18,  19,  20,  21,  22,  23,  24,  41,  42,  43,  \
	                                   44,  45,  46,  47,  48,  65,  66,  64,  50,  51,  52,  53,  54,  55,  255, 255, \
	                                   62,  63,  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 118, 119, 120, \
	                                   121, 122, 123, 124, 125, 126 }
/*[[[end]]]*/

/* Convert a given `CFI_386_UNWIND_REGISTER_*' register number to `CFI_X86_64_UNWIND_REGISTER_*' */
PRIVATE ATTR_CONST WUNUSED unwind_regno_t
NOTHROW(CC regno_i386_to_amd64)(unwind_regno_t regno) {
	unwind_regno_t result;
	PRIVATE DEFINE_386_to_amd64(i386_to_amd64);
	result = CFI_X86_64_UNWIND_REGISTER_COUNT;
	if likely(regno < lengthof(i386_to_amd64))
		result = i386_to_amd64[regno];
	return result;
}


INTERN NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_getreg_compat)(/*struct unwind_getreg_compat_data **/ void const *arg,
                                           unwind_regno_t regno, void *__restrict dst) {
	unwind_errno_t result;
	struct unwind_getreg_compat_data const *me;
	me     = (struct unwind_getreg_compat_data const *)arg;
	regno  = regno_i386_to_amd64(regno);
	result = (*me->ugcd_getreg)(me->ugcd_arg, regno, dst);
	return result;
}

#if 1
/* Abuse  the fact that getreg/setreg are actually the same here, and
 * the only difference lies in what's the deal with the function that
 * is being called. */
static_assert(offsetof(struct unwind_setreg_compat_data, uscd_setreg) ==
              offsetof(struct unwind_getreg_compat_data, ugcd_getreg));
static_assert(offsetof(struct unwind_setreg_compat_data, uscd_arg) ==
              offsetof(struct unwind_getreg_compat_data, ugcd_arg));
DEFINE_INTERN_ALIAS(libuw_unwind_setreg_compat, libuw_unwind_getreg_compat);
#else
INTERN NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_setreg_compat)(/*struct unwind_setreg_compat_data **/ void *arg,
                                           unwind_regno_t regno, void const *__restrict src) {
	unwind_errno_t result;
	struct unwind_setreg_compat_data const *me;
	me     = (struct unwind_setreg_compat_data const *)arg;
	regno  = regno_i386_to_amd64(regno);
	result = (*me->uscd_setreg)(me->uscd_arg, regno, src);
	return result;
}
#endif


DEFINE_PUBLIC_ALIAS(unwind_getreg_compat, libuw_unwind_getreg_compat);
DEFINE_PUBLIC_ALIAS(unwind_setreg_compat, libuw_unwind_setreg_compat);
#endif /* LIBUNWIND_HAVE_GETSETREG_COMPAT */

DECL_END

#endif /* !GUARD_LIBUNWIND_ARCH_I386_REGISTER_C */
