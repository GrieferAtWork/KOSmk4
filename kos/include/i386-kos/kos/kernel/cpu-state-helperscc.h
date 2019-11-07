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
#ifndef _I386_KOS_KOS_KERNEL_CPU_STATE_HELPERSCC_H
#define _I386_KOS_KOS_KERNEL_CPU_STATE_HELPERSCC_H 1

#include <hybrid/host.h>

#include <asm/intrin.h>
#include <bits/types.h>
#include <kos/anno.h>
#include <kos/kernel/gdt.h>
#include <hybrid/__assert.h>
#include <libc/string.h>

#include "cpu-state32.h"
#include "cpu-state64.h"
#include "cpu-state-helpers32.h"
#include "cpu-state-helpers64.h"

#ifdef __CC__
__DECL_BEGIN

/************************************************************************/
/* `struct gpregs32'                                                    */
/************************************************************************/
__LOCAL __NOBLOCK void
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
__LOCAL __NOBLOCK void
__NOTHROW_NCX(gpregs32_to_gpregs64)(struct gpregs32 const *__restrict __self,
                                    struct gpregs64 *__restrict __result) {
	gpregs32_to_gpregs64_ex(__self, __result, 0, 0, 0, 0, 0, 0, 0, 0);
}
/************************************************************************/




/************************************************************************/
/* `struct gpregsnsp64'                                                    */
/************************************************************************/
__LOCAL __NOBLOCK void
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
/* `struct gpregs64'                                                    */
/************************************************************************/
__LOCAL __NOBLOCK void
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
/* `struct kcpustate32'                                                 */
/************************************************************************/
__LOCAL __NOBLOCK void
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
__LOCAL __NOBLOCK void
__NOTHROW_NCX(kcpustate32_to_kcpustate64)(struct kcpustate32 const *__restrict __self,
                                          struct kcpustate64 *__restrict __result) {
	kcpustate32_to_kcpustate64_ex(__self, __result, 0, 0, 0, 0, 0, 0, 0, 0);
}
__LOCAL __NOBLOCK void
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
__LOCAL __NOBLOCK void
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
/************************************************************************/




/************************************************************************/
/* `struct kcpustate64'                                                 */
/************************************************************************/
__LOCAL __NOBLOCK void
__NOTHROW_NCX(kcpustate64_to_kcpustate32)(struct kcpustate64 const *__restrict __self,
                                          struct kcpustate32 *__restrict __result) {
	gpregs64_to_gpregs32(&__self->kcs_gpregs, &__result->kcs_gpregs);
	__result->kcs_eflags = (__u32)__self->kcs_rflags;
	__result->kcs_eip    = (__u32)__self->kcs_rip;
}
__LOCAL __NOBLOCK void
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
__LOCAL __NOBLOCK void
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
__LOCAL __NOBLOCK void
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



/* TODO: icpustate64_to_ucpustate32 */
/* TODO: icpustate64_to_kcpustate32 */

/* TODO: scpustate64_to_ucpustate32 */
/* TODO: scpustate64_to_kcpustate32 */

/* TODO: ucpustate32_to_icpustate64_p */
/* TODO: ucpustate32_to_scpustate64_p */
/* TODO: ucpustate32_to_ucpustate64 */
/* TODO: ucpustate32_to_kcpustate64 */
/* TODO: ucpustate32_to_lcpustate64 */

/* TODO: ucpustate64_to_ucpustate32 */
/* TODO: ucpustate64_to_kcpustate32 */
/* TODO: ucpustate64_to_lcpustate32 */

/* TODO: kcpustate32_to_icpustate64_p */
/* TODO: kcpustate32_to_scpustate64_p */
/* TODO: kcpustate32_to_ucpustate64 */

/* TODO: fcpustate64_to_fcpustate32 */
/* TODO: fcpustate64_to_ucpustate32 */
/* TODO: fcpustate64_to_kcpustate32 */

/* TODO: fcpustate32_to_fcpustate64 */
/* TODO: fcpustate32_to_ucpustate64 */
/* TODO: fcpustate32_to_kcpustate64 */



__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_KOS_KERNEL_CPU_STATE_HELPERSCC_H */
