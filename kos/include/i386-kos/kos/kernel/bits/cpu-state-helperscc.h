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
#ifndef _I386_KOS_KOS_KERNEL_BITS_CPU_STATE_HELPERSCC_H
#define _I386_KOS_KOS_KERNEL_BITS_CPU_STATE_HELPERSCC_H 1

/* HINT: The `cc' in this file's name stands for CrossCompat
 *      (as in compatibility between 32-bit and 64-bit modes) */

#include <hybrid/__assert.h>
#include <hybrid/host.h>

#include <asm/intrin.h>
#include <bits/types.h>
#include <kos/anno.h>

#include <libc/string.h>

#include "../x86/gdt.h"
#include "cpu-state-helpers32.h"
#include "cpu-state-helpers64.h"
#include "cpu-state32.h"
#include "cpu-state64.h"

#ifndef __CPUSTATE_GET_USER_FSBASE
#ifdef __KERNEL__
#include <kernel/arch/gdt.h> /* x86_get_user_(fs|gs)base() */
#define __CPUSTATE_GET_USER_FSBASE() x86_get_user_fsbase()
#define __CPUSTATE_GET_USER_GSBASE() x86_get_user_gsbase()
#else /* __KERNEL__ */
#define __CPUSTATE_GET_USER_FSBASE() ((__uintptr_t)__rdfsbase())
#define __CPUSTATE_GET_USER_GSBASE() ((__uintptr_t)__rdgsbase())
#endif /* !__KERNEL__ */
#endif /* !__CPUSTATE_GET_USER_FSBASE */


#if defined(__CC__) || defined(__DEEMON__)
__DECL_BEGIN

/************************************************************************/
/* `struct gpregs32'                                                    */
/************************************************************************/
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(gpregs32_to_gpregsnsp64_ex)(struct gpregs32 const *__restrict __self,
                                          struct gpregsnsp64 *__restrict __result,
                                          __u64 __v_gp_r15, __u64 __v_gp_r14,
                                          __u64 __v_gp_r13, __u64 __v_gp_r12,
                                          __u64 __v_gp_r11, __u64 __v_gp_r10,
                                          __u64 __v_gp_r9, __u64 __v_gp_r8) {
	__result->gp_r15 = __v_gp_r15;
	__result->gp_r14 = __v_gp_r14;
	__result->gp_r13 = __v_gp_r13;
	__result->gp_r12 = __v_gp_r12;
	__result->gp_r11 = __v_gp_r11;
	__result->gp_r10 = __v_gp_r10;
	__result->gp_r9  = __v_gp_r9;
	__result->gp_r8  = __v_gp_r8;
	__result->gp_rdi = __self->gp_edi;
	__result->gp_rsi = __self->gp_esi;
	__result->gp_rbp = __self->gp_ebp;
	__result->gp_rbx = __self->gp_ebx;
	__result->gp_rdx = __self->gp_edx;
	__result->gp_rcx = __self->gp_ecx;
	__result->gp_rax = __self->gp_eax;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(gpregs32_to_gpregs64_ex)(struct gpregs32 const *__restrict __self,
                                       struct gpregs64 *__restrict __result,
                                       __u64 __v_gp_r15, __u64 __v_gp_r14,
                                       __u64 __v_gp_r13, __u64 __v_gp_r12,
                                       __u64 __v_gp_r11, __u64 __v_gp_r10,
                                       __u64 __v_gp_r9, __u64 __v_gp_r8) {
	__result->gp_r15 = __v_gp_r15;
	__result->gp_r14 = __v_gp_r14;
	__result->gp_r13 = __v_gp_r13;
	__result->gp_r12 = __v_gp_r12;
	__result->gp_r11 = __v_gp_r11;
	__result->gp_r10 = __v_gp_r10;
	__result->gp_r9  = __v_gp_r9;
	__result->gp_r8  = __v_gp_r8;
	__result->gp_rdi = __self->gp_edi;
	__result->gp_rsi = __self->gp_esi;
	__result->gp_rbp = __self->gp_ebp;
	__result->gp_rsp = __self->gp_esp;
	__result->gp_rbx = __self->gp_ebx;
	__result->gp_rdx = __self->gp_edx;
	__result->gp_rcx = __self->gp_ecx;
	__result->gp_rax = __self->gp_eax;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(gpregs32_to_gpregs64_spex)(struct gpregs32 const *__restrict __self,
                                         struct gpregs64 *__restrict __result,
                                         __u32 __v_esp,
                                         __u64 __v_gp_r15, __u64 __v_gp_r14,
                                         __u64 __v_gp_r13, __u64 __v_gp_r12,
                                         __u64 __v_gp_r11, __u64 __v_gp_r10,
                                         __u64 __v_gp_r9, __u64 __v_gp_r8) {
	__result->gp_r15 = __v_gp_r15;
	__result->gp_r14 = __v_gp_r14;
	__result->gp_r13 = __v_gp_r13;
	__result->gp_r12 = __v_gp_r12;
	__result->gp_r11 = __v_gp_r11;
	__result->gp_r10 = __v_gp_r10;
	__result->gp_r9  = __v_gp_r9;
	__result->gp_r8  = __v_gp_r8;
	__result->gp_rdi = __self->gp_edi;
	__result->gp_rsi = __self->gp_esi;
	__result->gp_rbp = __self->gp_ebp;
	__result->gp_rsp = __v_esp;
	__result->gp_rbx = __self->gp_ebx;
	__result->gp_rdx = __self->gp_edx;
	__result->gp_rcx = __self->gp_ecx;
	__result->gp_rax = __self->gp_eax;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(gpregs32_to_gpregsnsp64)(struct gpregs32 const *__restrict __self,
                                       struct gpregsnsp64 *__restrict __result) {
	gpregs32_to_gpregsnsp64_ex(__self, __result, 0, 0, 0, 0, 0, 0, 0, 0);
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(gpregs32_to_gpregs64)(struct gpregs32 const *__restrict __self,
                                    struct gpregs64 *__restrict __result) {
	gpregs32_to_gpregs64_ex(__self, __result, 0, 0, 0, 0, 0, 0, 0, 0);
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(gpregs32_to_gpregs64_sp)(struct gpregs32 const *__restrict __self,
                                       struct gpregs64 *__restrict __result,
                                       __u32 __v_esp) {
	gpregs32_to_gpregs64_spex(__self, __result, __v_esp, 0, 0, 0, 0, 0, 0, 0, 0);
}
/************************************************************************/




/************************************************************************/
/* `struct gpregs64'                                                    */
/************************************************************************/
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(gpregs64_to_gpregs32)(struct gpregs64 const *__restrict __self,
                                    struct gpregs32 *__restrict __result) {
	__result->gp_edi = (__u32)__self->gp_rdi;
	__result->gp_esi = (__u32)__self->gp_rsi;
	__result->gp_ebp = (__u32)__self->gp_rbp;
	__result->gp_esp = (__u32)__self->gp_rsp;
	__result->gp_ebx = (__u32)__self->gp_rbx;
	__result->gp_edx = (__u32)__self->gp_rdx;
	__result->gp_ecx = (__u32)__self->gp_rcx;
	__result->gp_eax = (__u32)__self->gp_rax;
}
/************************************************************************/




/************************************************************************/
/* `struct gpregsnsp64'                                                    */
/************************************************************************/
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(gpregsnsp64_to_gpregs32)(struct gpregsnsp64 const *__restrict __self,
                                       struct gpregs32 *__restrict __result,
                                       __u32 __v_esp) {
	__result->gp_edi = (__u32)__self->gp_rdi;
	__result->gp_esi = (__u32)__self->gp_rsi;
	__result->gp_ebp = (__u32)__self->gp_rbp;
	__result->gp_esp = __v_esp;
	__result->gp_ebx = (__u32)__self->gp_rbx;
	__result->gp_edx = (__u32)__self->gp_rdx;
	__result->gp_ecx = (__u32)__self->gp_rcx;
	__result->gp_eax = (__u32)__self->gp_rax;
}
/************************************************************************/




/************************************************************************/
/* `struct kcpustate32'                                                 */
/************************************************************************/
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(kcpustate32_to_kcpustate64_ex)(struct kcpustate32 const *__restrict __self,
                                             struct kcpustate64 *__restrict __result,
                                             __u64 __v_gp_r15, __u64 __v_gp_r14,
                                             __u64 __v_gp_r13, __u64 __v_gp_r12,
                                             __u64 __v_gp_r11, __u64 __v_gp_r10,
                                             __u64 __v_gp_r9, __u64 __v_gp_r8) {
	gpregs32_to_gpregs64_ex(&__self->kcs_gpregs, &__result->kcs_gpregs,
	                        __v_gp_r15, __v_gp_r14, __v_gp_r13, __v_gp_r12,
	                        __v_gp_r11, __v_gp_r10, __v_gp_r9, __v_gp_r8);
	__result->kcs_rflags = __self->kcs_eflags;
	__result->kcs_rip    = __self->kcs_eip;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(kcpustate32_to_kcpustate64)(struct kcpustate32 const *__restrict __self,
                                          struct kcpustate64 *__restrict __result) {
	kcpustate32_to_kcpustate64_ex(__self, __result, 0, 0, 0, 0, 0, 0, 0, 0);
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(kcpustate32_to_ucpustate64_ex)(struct kcpustate32 const *__restrict __self,
                                             struct ucpustate64 *__restrict __result,
                                             __u64 __v_gp_r15, __u64 __v_gp_r14,
                                             __u64 __v_gp_r13, __u64 __v_gp_r12,
                                             __u64 __v_gp_r11, __u64 __v_gp_r10,
                                             __u64 __v_gp_r9, __u64 __v_gp_r8,
                                             __u16 __v_gs, __u16 __v_fs,
                                             __u16 __v_es, __u16 __v_ds,
                                             __u16 __v_cs, __u16 __v_ss) {
	gpregs32_to_gpregs64_ex(&__self->kcs_gpregs, &__result->ucs_gpregs,
	                        __v_gp_r15, __v_gp_r14, __v_gp_r13, __v_gp_r12,
	                        __v_gp_r11, __v_gp_r10, __v_gp_r9, __v_gp_r8);
	__result->ucs_sgregs.sg_gs = __v_gs;
	__result->ucs_sgregs.sg_fs = __v_fs;
	__result->ucs_sgregs.sg_es = __v_es;
	__result->ucs_sgregs.sg_ds = __v_ds;
	__result->ucs_cs           = __v_cs;
	__result->ucs_ss           = __v_ss;
	__result->ucs_rflags       = __self->kcs_eflags;
	__result->ucs_rip          = __self->kcs_eip;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(kcpustate32_to_ucpustate64)(struct kcpustate32 const *__restrict __self,
                                          struct ucpustate64 *__restrict __result) {
	kcpustate32_to_ucpustate64_ex(__self, __result, 0, 0, 0, 0, 0, 0, 0, 0,
	                              __rdgs(),
#if defined(__KERNEL__) && !defined(__x86_64__)
	                              SEGMENT_KERNEL_FSBASE,
	                              SEGMENT_USER_DATA_RPL,
	                              SEGMENT_USER_DATA_RPL,
#else /* __KERNEL__ && !__x86_64__ */
	                              __rdfs(), __rdes(), __rdds(),
#endif /* !__KERNEL__ || __x86_64__ */
	                              SEGMENT_CURRENT_CODE_RPL,
	                              SEGMENT_CURRENT_DATA_RPL);
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct icpustate64 *
__NOTHROW_NCX(kcpustate32_to_icpustate64_p_ex)(struct kcpustate32 const *__restrict __self,
                                               void *__restrict __kernel_rsp,
                                               __u64 __v_gp_r15, __u64 __v_gp_r14,
                                               __u64 __v_gp_r13, __u64 __v_gp_r12,
                                               __u64 __v_gp_r11, __u64 __v_gp_r10,
                                               __u64 __v_gp_r9, __u64 __v_gp_r8,
                                               __u16 __v_cs, __u16 __v_ss) {
	struct icpustate64 *__result;
	__result = (struct icpustate64 *)((__byte_t *)__kernel_rsp - SIZEOF_ICPUSTATE64);
	gpregs32_to_gpregsnsp64_ex(&__self->kcs_gpregs, &__result->ics_gpregs,
	                           __v_gp_r15, __v_gp_r14, __v_gp_r13, __v_gp_r12,
	                           __v_gp_r11, __v_gp_r10, __v_gp_r9, __v_gp_r8);
	__result->ics_irregs.ir_rip    = __self->kcs_eip;
	__result->ics_irregs.ir_cs     = __v_cs;
	__result->ics_irregs.ir_rflags = __self->kcs_eflags;
	__result->ics_irregs.ir_rsp    = __self->kcs_gpregs.gp_esp;
	__result->ics_irregs.ir_ss     = __v_ss;
	return __result;
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct icpustate64 *
__NOTHROW_NCX(kcpustate32_to_icpustate64_p)(struct kcpustate32 const *__restrict __self,
                                            void *__restrict __kernel_rsp) {
	return kcpustate32_to_icpustate64_p_ex(__self, __kernel_rsp,
	                                       0, 0, 0, 0, 0, 0, 0, 0,
	                                       SEGMENT_CURRENT_CODE_RPL,
	                                       SEGMENT_CURRENT_DATA_RPL);
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct scpustate64 *
__NOTHROW_NCX(kcpustate32_to_scpustate64_p_ex)(struct kcpustate32 const *__restrict __self,
                                               void *__restrict __kernel_rsp,
                                               __u64 __v_sg_gsbase, __u64 __v_sg_fsbase,
                                               __u64 __v_gp_r15, __u64 __v_gp_r14,
                                               __u64 __v_gp_r13, __u64 __v_gp_r12,
                                               __u64 __v_gp_r11, __u64 __v_gp_r10,
                                               __u64 __v_gp_r9, __u64 __v_gp_r8,
                                               __u16 __v_gs, __u16 __v_fs,
                                               __u16 __v_es, __u16 __v_ds,
                                               __u16 __v_cs, __u16 __v_ss) {
	struct scpustate64 *__result;
	__result->scs_sgbase.sg_gsbase = __v_sg_gsbase;
	__result->scs_sgbase.sg_fsbase = __v_sg_fsbase;
	__result->scs_sgregs.sg_gs     = __v_gs;
	__result->scs_sgregs.sg_fs     = __v_fs;
	__result->scs_sgregs.sg_es     = __v_es;
	__result->scs_sgregs.sg_ds     = __v_ds;
	__result = (struct scpustate64 *)((__byte_t *)__kernel_rsp - SIZEOF_SCPUSTATE64);
	gpregs32_to_gpregsnsp64_ex(&__self->kcs_gpregs, &__result->scs_gpregs,
	                           __v_gp_r15, __v_gp_r14, __v_gp_r13, __v_gp_r12,
	                           __v_gp_r11, __v_gp_r10, __v_gp_r9, __v_gp_r8);
	__result->scs_irregs.ir_rip    = __self->kcs_eip;
	__result->scs_irregs.ir_cs     = __v_cs;
	__result->scs_irregs.ir_rflags = __self->kcs_eflags;
	__result->scs_irregs.ir_rsp    = __self->kcs_gpregs.gp_esp;
	__result->scs_irregs.ir_ss     = __v_ss;
	return __result;
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct scpustate64 *
__NOTHROW_NCX(kcpustate32_to_scpustate64_p)(struct kcpustate32 const *__restrict __self,
                                            void *__restrict __kernel_rsp) {
	return kcpustate32_to_scpustate64_p_ex(__self, __kernel_rsp,
	                                       __CPUSTATE_GET_USER_GSBASE(),
	                                       __CPUSTATE_GET_USER_FSBASE(),
	                                       0, 0, 0, 0, 0, 0, 0, 0,
	                                       __rdgs(),
#if defined(__KERNEL__) && !defined(__x86_64__)
	                                       SEGMENT_KERNEL_FSBASE,
	                                       SEGMENT_USER_DATA_RPL,
	                                       SEGMENT_USER_DATA_RPL,
#else /* __KERNEL__ && !__x86_64__ */
	                                       __rdfs(), __rdes(), __rdds(),
#endif /* !__KERNEL__ || __x86_64__ */
	                                       SEGMENT_CURRENT_CODE_RPL,
	                                       SEGMENT_CURRENT_DATA_RPL);
}
/************************************************************************/




/************************************************************************/
/* `struct kcpustate64'                                                 */
/************************************************************************/
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(kcpustate64_to_kcpustate32)(struct kcpustate64 const *__restrict __self,
                                          struct kcpustate32 *__restrict __result) {
	gpregs64_to_gpregs32(&__self->kcs_gpregs, &__result->kcs_gpregs);
	__result->kcs_eflags = (__u32)__self->kcs_rflags;
	__result->kcs_eip    = (__u32)__self->kcs_rip;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(kcpustate64_to_ucpustate32_ex)(struct kcpustate64 const *__restrict __self,
                                             struct ucpustate32 *__restrict __result,
                                             __u16 __v_gs, __u16 __v_fs,
                                             __u16 __v_es, __u16 __v_ds,
                                             __u16 __v_cs, __u16 __v_ss) {
	gpregs64_to_gpregs32(&__self->kcs_gpregs, &__result->ucs_gpregs);
	__result->ucs_sgregs.sg_gs = __v_gs;
	__result->ucs_sgregs.sg_fs = __v_fs;
	__result->ucs_sgregs.sg_es = __v_es;
	__result->ucs_sgregs.sg_ds = __v_ds;
	__result->ucs_cs           = __v_cs;
	__result->ucs_ss           = __v_ss;
	__result->ucs_eflags       = (__u32)__self->kcs_rflags;
	__result->ucs_eip          = (__u32)__self->kcs_rip;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(kcpustate64_to_ucpustate32)(struct kcpustate64 const *__restrict __self,
                                          struct ucpustate32 *__restrict __result) {
	kcpustate64_to_ucpustate32_ex(__self, __result,
	                              __rdgs(),
#if defined(__KERNEL__) && !defined(__x86_64__)
	                              SEGMENT_KERNEL_FSBASE,
	                              SEGMENT_USER_DATA_RPL,
	                              SEGMENT_USER_DATA_RPL,
#else /* __KERNEL__ && !__x86_64__ */
	                              __rdfs(), __rdes(), __rdds(),
#endif /* !__KERNEL__ || __x86_64__ */
	                              SEGMENT_CURRENT_CODE_RPL,
	                              SEGMENT_CURRENT_DATA_RPL);
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(kcpustate64_to_lcpustate32)(struct kcpustate64 const *__restrict __self,
                                          struct lcpustate32 *__restrict __result) {
	__result->lcs_edi = (__u32)__self->kcs_gpregs.gp_rdi;
	__result->lcs_esi = (__u32)__self->kcs_gpregs.gp_rsi;
	__result->lcs_ebp = (__u32)__self->kcs_gpregs.gp_rbp;
	__result->lcs_esp = (__u32)__self->kcs_gpregs.gp_rsp;
	__result->lcs_ebx = (__u32)__self->kcs_gpregs.gp_rbx;
	__result->lcs_eip = (__u32)__self->kcs_rip;
}
/************************************************************************/




/************************************************************************/
/* `struct icpustate32'                                                 */
/************************************************************************/
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(icpustate32_to_ucpustate64_ex)(struct icpustate32 const *__restrict __self,
                                             struct ucpustate64 *__restrict __result,
                                             __u64 __v_sg_gsbase, __u64 __v_sg_fsbase,
                                             __u16 __v_gs_vm86,
                                             __u64 __v_gp_r15, __u64 __v_gp_r14,
                                             __u64 __v_gp_r13, __u64 __v_gp_r12,
                                             __u64 __v_gp_r11, __u64 __v_gp_r10,
                                             __u64 __v_gp_r9, __u64 __v_gp_r8) {
	__u32 __effective_esp;
	__result->ucs_sgbase.sg_gsbase = __v_sg_gsbase;
	__result->ucs_sgbase.sg_fsbase = __v_sg_fsbase;
	__result->ucs_rflags = icpustate32_geteflags(__self);
	__result->ucs_cs     = icpustate32_getcs(__self);
#ifndef __I386_NO_VM86
	if (__result->ucs_rflags & 0x20000) {
		__result->ucs_sgregs.sg_gs = __self->ics_irregs_v.ir_gs16;
		__result->ucs_sgregs.sg_fs = __self->ics_irregs_v.ir_fs16;
		__result->ucs_sgregs.sg_es = __self->ics_irregs_v.ir_es16;
		__result->ucs_sgregs.sg_ds = __self->ics_irregs_v.ir_ds16;
		__result->ucs_ss           = icpustate32_getuserss(__self);
		__effective_esp            = icpustate32_getuseresp(__self);
	} else
#endif /* !__I386_NO_VM86 */
	{
		if (__result->ucs_cs & 3) {
			__result->ucs_ss = icpustate32_getuserss(__self);
			__effective_esp  = icpustate32_getuseresp(__self);
		} else {
			__result->ucs_ss = icpustate32_getkernelss(__self);
			__effective_esp  = icpustate32_getkernelesp(__self);
		}
		__result->ucs_sgregs.sg_gs = __v_gs_vm86;
		__result->ucs_sgregs.sg_fs = __self->ics_fs16;
		__result->ucs_sgregs.sg_es = __self->ics_es16;
		__result->ucs_sgregs.sg_ds = __self->ics_ds16;
	}
	gpregs32_to_gpregs64_spex(&__self->ics_gpregs, &__result->ucs_gpregs,
	                          __effective_esp,
	                          __v_gp_r15, __v_gp_r14, __v_gp_r13, __v_gp_r12,
	                          __v_gp_r11, __v_gp_r10, __v_gp_r9, __v_gp_r8);
	__result->ucs_rip = icpustate32_geteip(__self);
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(icpustate32_to_ucpustate64)(struct icpustate32 const *__restrict __self,
                                          struct ucpustate64 *__restrict __result) {
	icpustate32_to_ucpustate64_ex(__self, __result,
	                              __CPUSTATE_GET_USER_GSBASE(),
	                              __CPUSTATE_GET_USER_FSBASE(),
	                              __rdgs(), 0, 0, 0, 0, 0, 0, 0, 0);
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(icpustate32_to_kcpustate64_ex)(struct icpustate32 const *__restrict __self,
                                             struct kcpustate64 *__restrict __result,
                                             __u64 __v_gp_r15, __u64 __v_gp_r14,
                                             __u64 __v_gp_r13, __u64 __v_gp_r12,
                                             __u64 __v_gp_r11, __u64 __v_gp_r10,
                                             __u64 __v_gp_r9, __u64 __v_gp_r8) {
	gpregs32_to_gpregs64_spex(&__self->ics_gpregs, &__result->kcs_gpregs,
	                          icpustate32_getesp(__self),
	                          __v_gp_r15, __v_gp_r14, __v_gp_r13, __v_gp_r12,
	                          __v_gp_r11, __v_gp_r10, __v_gp_r9, __v_gp_r8);
	__result->kcs_rflags = icpustate32_geteflags(__self);
	__result->kcs_rip    = icpustate32_geteip(__self);
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(icpustate32_to_kcpustate64)(struct icpustate32 const *__restrict __self,
                                          struct kcpustate64 *__restrict __result) {
	icpustate32_to_kcpustate64_ex(__self, __result, 0, 0, 0, 0, 0, 0, 0, 0);
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(icpustate32_user_to_kcpustate64_ex)(struct icpustate32 const *__restrict __self,
                                                  struct kcpustate64 *__restrict __result,
                                                  __u64 __v_gp_r15, __u64 __v_gp_r14,
                                                  __u64 __v_gp_r13, __u64 __v_gp_r12,
                                                  __u64 __v_gp_r11, __u64 __v_gp_r10,
                                                  __u64 __v_gp_r9, __u64 __v_gp_r8) {
	gpregs32_to_gpregs64_spex(&__self->ics_gpregs, &__result->kcs_gpregs,
	                          icpustate32_getuseresp(__self),
	                          __v_gp_r15, __v_gp_r14, __v_gp_r13, __v_gp_r12,
	                          __v_gp_r11, __v_gp_r10, __v_gp_r9, __v_gp_r8);
	__result->kcs_rflags = icpustate32_geteflags(__self);
	__result->kcs_rip    = icpustate32_geteip(__self);
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(icpustate32_user_to_kcpustate64)(struct icpustate32 const *__restrict __self,
                                               struct kcpustate64 *__restrict __result) {
	icpustate32_user_to_kcpustate64_ex(__self, __result, 0, 0, 0, 0, 0, 0, 0, 0);
}
/************************************************************************/




/************************************************************************/
/* `struct icpustate64'                                                 */
/************************************************************************/
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(icpustate64_to_ucpustate32_ex)(struct icpustate64 const *__restrict __self,
                                             struct ucpustate32 *__restrict __result,
                                             __u16 __v_gs, __u16 __v_fs,
                                             __u16 __v_es, __u16 __v_ds) {
	gpregsnsp64_to_gpregs32(&__self->ics_gpregs,
	                        &__result->ucs_gpregs,
	                        (__u32)icpustate64_getrsp(__self));
	__result->ucs_sgregs.sg_gs = __v_gs;
	__result->ucs_sgregs.sg_fs = __v_fs;
	__result->ucs_sgregs.sg_es = __v_es;
	__result->ucs_sgregs.sg_ds = __v_ds;
	__result->ucs_cs           = icpustate64_getcs(__self);
	__result->ucs_ss           = icpustate64_getss(__self);
	__result->ucs_eflags       = (__u32)icpustate64_getrflags(__self);
	__result->ucs_eip          = (__u32)icpustate64_getrip(__self);
}
#define icpustate64_user_to_ucpustate32_ex icpustate64_to_ucpustate32_ex
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(icpustate64_to_ucpustate32)(struct icpustate64 const *__restrict __self,
                                          struct ucpustate32 *__restrict __result) {
	icpustate64_to_ucpustate32_ex(__self, __result, __rdgs(), __rdfs(), __rdes(), __rdds());
}
#define icpustate64_user_to_ucpustate32 icpustate64_to_ucpustate32
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(icpustate64_to_kcpustate32)(struct icpustate64 const *__restrict __self,
                                          struct kcpustate32 *__restrict __result) {
	__result->kcs_gpregs.gp_edi = (__u32)__self->ics_gpregs.gp_rdi;
	__result->kcs_gpregs.gp_esi = (__u32)__self->ics_gpregs.gp_rsi;
	__result->kcs_gpregs.gp_ebp = (__u32)__self->ics_gpregs.gp_rbp;
	__result->kcs_gpregs.gp_esp = (__u32)icpustate64_getrsp(__self);
	__result->kcs_gpregs.gp_ebx = (__u32)__self->ics_gpregs.gp_rbx;
	__result->kcs_gpregs.gp_edx = (__u32)__self->ics_gpregs.gp_rdx;
	__result->kcs_gpregs.gp_ecx = (__u32)__self->ics_gpregs.gp_rcx;
	__result->kcs_gpregs.gp_eax = (__u32)__self->ics_gpregs.gp_rax;
	__result->kcs_eflags        = (__u32)icpustate64_getrflags(__self);
	__result->kcs_eip           = (__u32)icpustate64_getrip(__self);
}
#define icpustate64_user_to_kcpustate32 icpustate64_to_kcpustate32
/************************************************************************/




/************************************************************************/
/* `struct scpustate32'                                                 */
/************************************************************************/
/* TO-DO: scpustate32_to_ucpustate64 */
/* TO-DO: scpustate32_to_kcpustate64 */
/* TO-DO: scpustate32_to_lcpustate64 */
/* TO-DO: scpustate32_to_icpustate64_p */
/* TO-DO: scpustate32_to_scpustate64_p */
/************************************************************************/




/************************************************************************/
/* `struct scpustate64'                                                 */
/************************************************************************/
/* TO-DO: scpustate64_to_ucpustate32 */
/* TO-DO: scpustate64_to_kcpustate32 */
/* TO-DO: scpustate64_to_lcpustate32 */
/************************************************************************/




/************************************************************************/
/* `struct ucpustate32'                                                 */
/************************************************************************/
/* TODO: ucpustate32_to_icpustate64_p */
/* TODO: ucpustate32_to_scpustate64_p */
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(ucpustate32_to_ucpustate64_ex)(struct ucpustate32 const *__restrict __self,
                                             struct ucpustate64 *__restrict __result,
                                             __u64 __v_sg_gsbase, __u64 __v_sg_fsbase,
                                             __u64 __v_gp_r15, __u64 __v_gp_r14,
                                             __u64 __v_gp_r13, __u64 __v_gp_r12,
                                             __u64 __v_gp_r11, __u64 __v_gp_r10,
                                             __u64 __v_gp_r9, __u64 __v_gp_r8) {
	__result->ucs_sgbase.sg_fsbase = __v_sg_gsbase;
	__result->ucs_sgbase.sg_gsbase = __v_sg_fsbase;
	gpregs32_to_gpregs64_ex(&__self->ucs_gpregs, &__result->ucs_gpregs,
	                        __v_gp_r15, __v_gp_r14, __v_gp_r13, __v_gp_r12,
	                        __v_gp_r11, __v_gp_r10, __v_gp_r9, __v_gp_r8);
	__result->ucs_sgregs.sg_gs = __self->ucs_sgregs.sg_gs16;
	__result->ucs_sgregs.sg_fs = __self->ucs_sgregs.sg_fs16;
	__result->ucs_sgregs.sg_es = __self->ucs_sgregs.sg_es16;
	__result->ucs_sgregs.sg_ds = __self->ucs_sgregs.sg_ds16;
	__result->ucs_cs           = __self->ucs_cs16;
	__result->ucs_ss           = __self->ucs_ss16;
	__result->ucs_rflags       = __self->ucs_eflags;
	__result->ucs_rip          = __self->ucs_eip;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(ucpustate32_to_ucpustate64)(struct ucpustate32 const *__restrict __self,
                                          struct ucpustate64 *__restrict __result) {
	ucpustate32_to_ucpustate64_ex(__self, __result,
	                              __CPUSTATE_GET_USER_GSBASE(),
	                              __CPUSTATE_GET_USER_FSBASE(),
	                              0, 0, 0, 0, 0, 0, 0, 0);
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(ucpustate32_to_kcpustate64_ex)(struct ucpustate32 const *__restrict __self,
                                             struct kcpustate64 *__restrict __result,
                                             __u64 __v_gp_r15, __u64 __v_gp_r14,
                                             __u64 __v_gp_r13, __u64 __v_gp_r12,
                                             __u64 __v_gp_r11, __u64 __v_gp_r10,
                                             __u64 __v_gp_r9, __u64 __v_gp_r8) {
	gpregs32_to_gpregs64_ex(&__self->ucs_gpregs, &__result->kcs_gpregs,
	                        __v_gp_r15, __v_gp_r14, __v_gp_r13, __v_gp_r12,
	                        __v_gp_r11, __v_gp_r10, __v_gp_r9, __v_gp_r8);
	__result->kcs_rflags       = __self->ucs_eflags;
	__result->kcs_rip          = __self->ucs_eip;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(ucpustate32_to_kcpustate64)(struct ucpustate32 const *__restrict __self,
                                          struct kcpustate64 *__restrict __result) {
	ucpustate32_to_kcpustate64_ex(__self, __result, 0, 0, 0, 0, 0, 0, 0, 0);
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(ucpustate32_to_lcpustate64_ex)(struct ucpustate32 const *__restrict __self,
                                             struct lcpustate64 *__restrict __result,
                                             __u64 __v_gp_r15, __u64 __v_gp_r14,
                                             __u64 __v_gp_r13, __u64 __v_gp_r12) {
	__result->lcs_r15 = __v_gp_r15;
	__result->lcs_r14 = __v_gp_r14;
	__result->lcs_r13 = __v_gp_r13;
	__result->lcs_r12 = __v_gp_r12;
	__result->lcs_rbp = __self->ucs_gpregs.gp_ebp;
	__result->lcs_rsp = __self->ucs_gpregs.gp_esp;
	__result->lcs_rbx = __self->ucs_gpregs.gp_ebx;
	__result->lcs_rip = __self->ucs_eip;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(ucpustate32_to_lcpustate64)(struct ucpustate32 const *__restrict __self,
                                          struct lcpustate64 *__restrict __result) {
	ucpustate32_to_lcpustate64_ex(__self, __result, 0, 0, 0, 0);
}
/************************************************************************/




/************************************************************************/
/* `struct ucpustate64'                                                 */
/************************************************************************/
/* TODO: ucpustate64_to_ucpustate32 */
/* TODO: ucpustate64_to_kcpustate32 */
/* TODO: ucpustate64_to_lcpustate32 */
/************************************************************************/




/************************************************************************/
/* `struct fcpustate32'                                                 */
/************************************************************************/
/* TODO: fcpustate32_to_fcpustate64 */
/* TODO: fcpustate32_to_ucpustate64 */
/* TODO: fcpustate32_to_kcpustate64 */
/* TODO: fcpustate32_to_lcpustate64 */
/* TODO: fcpustate32_to_icpustate64_p */
/* TODO: fcpustate32_to_scpustate64_p */
/************************************************************************/




/************************************************************************/
/* `struct fcpustate64'                                                 */
/************************************************************************/
/* TODO: fcpustate64_to_fcpustate32 */
/* TODO: fcpustate64_to_ucpustate32 */
/* TODO: fcpustate64_to_kcpustate32 */
/* TODO: fcpustate64_to_lcpustate32 */
/************************************************************************/










/*[[[deemon
local functions = {
	"gpregs32_to_gpregsnsp64_ex",
	"gpregs32_to_gpregs64_ex",
	"gpregs32_to_gpregs64_spex",
	"gpregs32_to_gpregsnsp64",
	"gpregs32_to_gpregs64",
	"gpregs32_to_gpregs64_sp",

	"gpregs64_to_gpregs32",

	"gpregsnsp64_to_gpregs32",

	"kcpustate32_to_kcpustate64_ex",
	"kcpustate32_to_kcpustate64",
	"kcpustate32_to_ucpustate64_ex",
	"kcpustate32_to_ucpustate64",
	"kcpustate32_to_icpustate64_p_ex",
	"kcpustate32_to_icpustate64_p",
	"kcpustate32_to_scpustate64_p_ex",
	"kcpustate32_to_scpustate64_p",

	"kcpustate64_to_kcpustate32",
	"kcpustate64_to_ucpustate32_ex",
	"kcpustate64_to_ucpustate32",
	"kcpustate64_to_lcpustate32",

	"icpustate32_to_ucpustate64_ex",
	"icpustate32_to_ucpustate64",
	"icpustate32_to_kcpustate64_ex",
	"icpustate32_to_kcpustate64",
	"icpustate32_user_to_kcpustate64_ex",
	"icpustate32_user_to_kcpustate64",

	"icpustate64_to_kcpustate32",
	"icpustate64_user_to_kcpustate32",
	"icpustate64_to_ucpustate32_ex",
	"icpustate64_user_to_ucpustate32_ex",
	"icpustate64_to_ucpustate32",
	"icpustate64_user_to_ucpustate32",

	"ucpustate32_to_ucpustate64_ex",
	"ucpustate32_to_ucpustate64",
	"ucpustate32_to_kcpustate64_ex",
	"ucpustate32_to_kcpustate64",
	"ucpustate32_to_lcpustate64_ex",
	"ucpustate32_to_lcpustate64",
};

local longest_name_length = functions.each.length > ...;
print "#ifdef __x86_64__";
for (local x: functions)
	print "#define", x.replace("64", ""), " " * (longest_name_length - #x), x;
print "#else /" "* __x86_64__ *" "/";
for (local x: functions)
	print "#define", x.replace("32", ""), " " * (longest_name_length - #x), x;
print "#endif /" "* !__x86_64__ *" "/";

]]]*/
#ifdef __x86_64__
#define gpregs32_to_gpregsnsp_ex          gpregs32_to_gpregsnsp64_ex
#define gpregs32_to_gpregs_ex             gpregs32_to_gpregs64_ex
#define gpregs32_to_gpregs_spex           gpregs32_to_gpregs64_spex
#define gpregs32_to_gpregsnsp             gpregs32_to_gpregsnsp64
#define gpregs32_to_gpregs                gpregs32_to_gpregs64
#define gpregs32_to_gpregs_sp             gpregs32_to_gpregs64_sp
#define gpregs_to_gpregs32                gpregs64_to_gpregs32
#define gpregsnsp_to_gpregs32             gpregsnsp64_to_gpregs32
#define kcpustate32_to_kcpustate_ex       kcpustate32_to_kcpustate64_ex
#define kcpustate32_to_kcpustate          kcpustate32_to_kcpustate64
#define kcpustate32_to_ucpustate_ex       kcpustate32_to_ucpustate64_ex
#define kcpustate32_to_ucpustate          kcpustate32_to_ucpustate64
#define kcpustate32_to_icpustate_p_ex     kcpustate32_to_icpustate64_p_ex
#define kcpustate32_to_icpustate_p        kcpustate32_to_icpustate64_p
#define kcpustate32_to_scpustate_p_ex     kcpustate32_to_scpustate64_p_ex
#define kcpustate32_to_scpustate_p        kcpustate32_to_scpustate64_p
#define kcpustate_to_kcpustate32          kcpustate64_to_kcpustate32
#define kcpustate_to_ucpustate32_ex       kcpustate64_to_ucpustate32_ex
#define kcpustate_to_ucpustate32          kcpustate64_to_ucpustate32
#define kcpustate_to_lcpustate32          kcpustate64_to_lcpustate32
#define icpustate32_to_ucpustate_ex       icpustate32_to_ucpustate64_ex
#define icpustate32_to_ucpustate          icpustate32_to_ucpustate64
#define icpustate32_to_kcpustate_ex       icpustate32_to_kcpustate64_ex
#define icpustate32_to_kcpustate          icpustate32_to_kcpustate64
#define icpustate32_user_to_kcpustate_ex  icpustate32_user_to_kcpustate64_ex
#define icpustate32_user_to_kcpustate     icpustate32_user_to_kcpustate64
#define icpustate_to_kcpustate32          icpustate64_to_kcpustate32
#define icpustate_user_to_kcpustate32     icpustate64_user_to_kcpustate32
#define icpustate_to_ucpustate32_ex       icpustate64_to_ucpustate32_ex
#define icpustate_user_to_ucpustate32_ex  icpustate64_user_to_ucpustate32_ex
#define icpustate_to_ucpustate32          icpustate64_to_ucpustate32
#define icpustate_user_to_ucpustate32     icpustate64_user_to_ucpustate32
#define ucpustate32_to_ucpustate_ex       ucpustate32_to_ucpustate64_ex
#define ucpustate32_to_ucpustate          ucpustate32_to_ucpustate64
#define ucpustate32_to_kcpustate_ex       ucpustate32_to_kcpustate64_ex
#define ucpustate32_to_kcpustate          ucpustate32_to_kcpustate64
#define ucpustate32_to_lcpustate_ex       ucpustate32_to_lcpustate64_ex
#define ucpustate32_to_lcpustate          ucpustate32_to_lcpustate64
#else /* __x86_64__ */
#define gpregs_to_gpregsnsp64_ex          gpregs32_to_gpregsnsp64_ex
#define gpregs_to_gpregs64_ex             gpregs32_to_gpregs64_ex
#define gpregs_to_gpregs64_spex           gpregs32_to_gpregs64_spex
#define gpregs_to_gpregsnsp64             gpregs32_to_gpregsnsp64
#define gpregs_to_gpregs64                gpregs32_to_gpregs64
#define gpregs_to_gpregs64_sp             gpregs32_to_gpregs64_sp
#define gpregs64_to_gpregs                gpregs64_to_gpregs32
#define gpregsnsp64_to_gpregs             gpregsnsp64_to_gpregs32
#define kcpustate_to_kcpustate64_ex       kcpustate32_to_kcpustate64_ex
#define kcpustate_to_kcpustate64          kcpustate32_to_kcpustate64
#define kcpustate_to_ucpustate64_ex       kcpustate32_to_ucpustate64_ex
#define kcpustate_to_ucpustate64          kcpustate32_to_ucpustate64
#define kcpustate_to_icpustate64_p_ex     kcpustate32_to_icpustate64_p_ex
#define kcpustate_to_icpustate64_p        kcpustate32_to_icpustate64_p
#define kcpustate_to_scpustate64_p_ex     kcpustate32_to_scpustate64_p_ex
#define kcpustate_to_scpustate64_p        kcpustate32_to_scpustate64_p
#define kcpustate64_to_kcpustate          kcpustate64_to_kcpustate32
#define kcpustate64_to_ucpustate_ex       kcpustate64_to_ucpustate32_ex
#define kcpustate64_to_ucpustate          kcpustate64_to_ucpustate32
#define kcpustate64_to_lcpustate          kcpustate64_to_lcpustate32
#define icpustate_to_ucpustate64_ex       icpustate32_to_ucpustate64_ex
#define icpustate_to_ucpustate64          icpustate32_to_ucpustate64
#define icpustate_to_kcpustate64_ex       icpustate32_to_kcpustate64_ex
#define icpustate_to_kcpustate64          icpustate32_to_kcpustate64
#define icpustate_user_to_kcpustate64_ex  icpustate32_user_to_kcpustate64_ex
#define icpustate_user_to_kcpustate64     icpustate32_user_to_kcpustate64
#define icpustate64_to_kcpustate          icpustate64_to_kcpustate32
#define icpustate64_user_to_kcpustate     icpustate64_user_to_kcpustate32
#define icpustate64_to_ucpustate_ex       icpustate64_to_ucpustate32_ex
#define icpustate64_user_to_ucpustate_ex  icpustate64_user_to_ucpustate32_ex
#define icpustate64_to_ucpustate          icpustate64_to_ucpustate32
#define icpustate64_user_to_ucpustate     icpustate64_user_to_ucpustate32
#define ucpustate_to_ucpustate64_ex       ucpustate32_to_ucpustate64_ex
#define ucpustate_to_ucpustate64          ucpustate32_to_ucpustate64
#define ucpustate_to_kcpustate64_ex       ucpustate32_to_kcpustate64_ex
#define ucpustate_to_kcpustate64          ucpustate32_to_kcpustate64
#define ucpustate_to_lcpustate64_ex       ucpustate32_to_lcpustate64_ex
#define ucpustate_to_lcpustate64          ucpustate32_to_lcpustate64
#endif /* !__x86_64__ */
//[[[end]]]


__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_KOS_KERNEL_BITS_CPU_STATE_HELPERSCC_H */
