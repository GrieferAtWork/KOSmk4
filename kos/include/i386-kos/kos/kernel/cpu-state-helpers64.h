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
#ifndef _I386_KOS_KOS_KERNEL_CPU_STATE_HELPERS64_H
#define _I386_KOS_KOS_KERNEL_CPU_STATE_HELPERS64_H 1

#include <hybrid/__assert.h>
#include <hybrid/host.h>

#include <asm/intrin.h>
#include <bits/types.h>
#include <kos/anno.h>
#include <kos/kernel/gdt.h>

#include <libc/string.h>

#include "cpu-state64.h"

#if defined(__KERNEL__) && defined(__x86_64__)
#include <sched/arch/task.h>
#endif /* __KERNEL__ && __x86_64__ */

#ifdef __CC__
__DECL_BEGIN

/************************************************************************/
/* `struct gpregsnsp64'                                                    */
/************************************************************************/
__LOCAL __NOBLOCK void
__NOTHROW_NCX(gpregsnsp64_to_gpregs64)(struct gpregsnsp64 const *__restrict __self,
                                       struct gpregs64 *__restrict __result,
                                       __u64 __v_rsp) {
	__result->gp_r15 = __self->gp_r15;
	__result->gp_r14 = __self->gp_r14;
	__result->gp_r13 = __self->gp_r13;
	__result->gp_r12 = __self->gp_r12;
	__result->gp_r11 = __self->gp_r11;
	__result->gp_r10 = __self->gp_r10;
	__result->gp_r9  = __self->gp_r9;
	__result->gp_r8  = __self->gp_r8;
	__result->gp_rdi = __self->gp_rdi;
	__result->gp_rsi = __self->gp_rsi;
	__result->gp_rbp = __self->gp_rbp;
	__result->gp_rsp = __v_rsp;
	__result->gp_rbx = __self->gp_rbx;
	__result->gp_rdx = __self->gp_rdx;
	__result->gp_rcx = __self->gp_rcx;
	__result->gp_rax = __self->gp_rax;
}
/************************************************************************/




/************************************************************************/
/* `struct gpregs64'                                                    */
/************************************************************************/
#define gpregs64_getr15(self)        ((__u64)(self)->gp_r15)
#define gpregs64_setr15(self, value) ((self)->gp_r15 = (value))
#define gpregs64_getr14(self)        ((__u64)(self)->gp_r14)
#define gpregs64_setr14(self, value) ((self)->gp_r14 = (value))
#define gpregs64_getr13(self)        ((__u64)(self)->gp_r13)
#define gpregs64_setr13(self, value) ((self)->gp_r13 = (value))
#define gpregs64_getr12(self)        ((__u64)(self)->gp_r12)
#define gpregs64_setr12(self, value) ((self)->gp_r12 = (value))
#define gpregs64_getr11(self)        ((__u64)(self)->gp_r11)
#define gpregs64_setr11(self, value) ((self)->gp_r11 = (value))
#define gpregs64_getr10(self)        ((__u64)(self)->gp_r10)
#define gpregs64_setr10(self, value) ((self)->gp_r10 = (value))
#define gpregs64_getr9(self)         ((__u64)(self)->gp_r9)
#define gpregs64_setr9(self, value)  ((self)->gp_r9 = (value))
#define gpregs64_getr8(self)         ((__u64)(self)->gp_r8)
#define gpregs64_setr8(self, value)  ((self)->gp_r8 = (value))
#define gpregs64_getrdi(self)        ((__u64)(self)->gp_rdi)
#define gpregs64_setrdi(self, value) ((self)->gp_rdi = (value))
#define gpregs64_getrsi(self)        ((__u64)(self)->gp_rsi)
#define gpregs64_setrsi(self, value) ((self)->gp_rsi = (value))
#define gpregs64_getrbp(self)        ((__u64)(self)->gp_rbp)
#define gpregs64_setrbp(self, value) ((self)->gp_rbp = (value))
#define gpregs64_getrsp(self)        ((__u64)(self)->gp_rsp)
#define gpregs64_setrsp(self, value) ((self)->gp_rsp = (value))
#define gpregs64_getrbx(self)        ((__u64)(self)->gp_rbx)
#define gpregs64_setrbx(self, value) ((self)->gp_rbx = (value))
#define gpregs64_getrdx(self)        ((__u64)(self)->gp_rdx)
#define gpregs64_setrdx(self, value) ((self)->gp_rdx = (value))
#define gpregs64_getrcx(self)        ((__u64)(self)->gp_rcx)
#define gpregs64_setrcx(self, value) ((self)->gp_rcx = (value))
#define gpregs64_getrax(self)        ((__u64)(self)->gp_rax)
#define gpregs64_setrax(self, value) ((self)->gp_rax = (value))
__LOCAL __NOBLOCK void
__NOTHROW_NCX(gpregs64_to_gpregsnsp64)(struct gpregs64 const *__restrict __self,
                                       struct gpregsnsp64 *__restrict __result) {
	__result->gp_r15 = __self->gp_r15;
	__result->gp_r14 = __self->gp_r14;
	__result->gp_r13 = __self->gp_r13;
	__result->gp_r12 = __self->gp_r12;
	__result->gp_r11 = __self->gp_r11;
	__result->gp_r10 = __self->gp_r10;
	__result->gp_r9  = __self->gp_r9;
	__result->gp_r8  = __self->gp_r8;
	__result->gp_rdi = __self->gp_rdi;
	__result->gp_rsi = __self->gp_rsi;
	__result->gp_rbp = __self->gp_rbp;
	__result->gp_rbx = __self->gp_rbx;
	__result->gp_rdx = __self->gp_rdx;
	__result->gp_rcx = __self->gp_rcx;
	__result->gp_rax = __self->gp_rax;
}
/************************************************************************/




/************************************************************************/
/* `struct irregs64'                                                    */
/************************************************************************/
#if defined(__KERNEL__) && defined(__x86_64__)
#define irregs64_isuser(self)            (irregs_isuser)(self)
#define irregs64_iskernel(self)          (!(irregs_isuser)(self))
#define irregs64_getrip(self)            (irregs_rdip)(self)
#define irregs64_setrip(self, value)     (irregs_wrip)(self, value)
#define irregs64_getcs(self)             (irregs_rdcs)(self)
#define irregs64_setcs(self, value)      (irregs_wrcs)(self, value)
#define irregs64_getrflags(self)         (irregs_rdflags)(self)
#define irregs64_setrflags(self, value)  (irregs_wrflags)(self, value)
#define irregs64_mskrflags(self, mask, flags) (irregs_mskflags)(self, mask, flags)
#define irregs64_getrsp(self)            (irregs_rdsp)(self)
#define irregs64_setrsp(self, value)     (irregs_wrsp)(self, value)
#define irregs64_getss(self)             (irregs_rdss)(self)
#define irregs64_setss(self, value)      (irregs_wrss)(self, value)
#else /* __KERNEL__ && __x86_64__ */
#define irregs64_isuser(self)            ((self)->ir_cs16 & 3)
#define irregs64_iskernel(self)          (!((self)->ir_cs16 & 3))
#define irregs64_getrip(self)            ((__u64)(self)->ir_rip)
#define irregs64_setrip(self, value)     ((self)->ir_rip = (value))
#define irregs64_getcs(self)             ((__u16)(self)->ir_cs16)
#define irregs64_setcs(self, value)      ((self)->ir_cs = (value))
#define irregs64_getrflags(self)         ((__u64)(self)->ir_rflags)
#define irregs64_setrflags(self, value)  ((self)->ir_rflags = (value))
#define irregs64_mskrflags(self, mask, flags) ((self)->ir_rflags = ((self)->ir_rflags & (mask)) | (flags))
#define irregs64_getrsp(self)            ((__u64)(self)->ir_rsp)
#define irregs64_setrsp(self, value)     ((self)->ir_rsp = (value))
#define irregs64_getss(self)             ((__u16)(self)->ir_ss16)
#define irregs64_setss(self, value)      ((self)->ir_ss = (value))
#endif /* !__KERNEL__ || !__x86_64__ */
#define irregs64_is32(self)              __KOS64_IS_CS32(irregs64_getcs(self))
#define irregs64_is64(self)              __KOS64_IS_CS64(irregs64_getcs(self))
#define irregs64_getuserrsp              irregs64_getrsp
#define irregs64_setuserrsp              irregs64_setrsp
#define irregs64_getuserss               irregs64_getss
#define irregs64_setuserss               irregs64_setss
#define irregs64_getkernelrsp            irregs64_getrsp
#define irregs64_getkernelss             irregs64_getss
#define irregs64_trysetrsp(self, value)  (irregs64_setrsp(self, value), 1)
#define irregs64_trysetss(self, value)   (irregs64_setss(self, value), 1)
#define irregs64_sizeof(self)            sizeof(struct irregs64)
/************************************************************************/




/************************************************************************/
/* `struct lcpustate64'                                                 */
/************************************************************************/
#define lcpustate64_getrip(self)        ((__u64)(self)->lcs_rip)
#define lcpustate64_setrip(self, value) ((self)->lcs_rip = (value))
#define lcpustate64_getrsp(self)        ((__u64)(self)->lcs_rsp)
#define lcpustate64_setrsp(self, value) ((self)->lcs_rsp = (value))
#ifdef __x86_64__
__FORCELOCAL void __FCALL lcpustate64_current(struct lcpustate64 *__restrict __result) {
	__asm__("movq %%r15, %0\n\t"
			"movq %%r14, %1\n\t"
			"movq %%r13, %2\n\t"
			"movq %%r12, %3\n\t"
			"movq %%rbp, %4\n\t"
			"movq %%rsp, %5\n\t"
			"movq %%rbx, %6\n\t"
			"leaq 991f(%%rip), %7\n\t"
			"991:"
			: "=m" (__result->lcs_r15)
			, "=m" (__result->lcs_r14)
			, "=m" (__result->lcs_r13)
			, "=m" (__result->lcs_r12)
			, "=m" (__result->lcs_rbp)
			, "=m" (__result->lcs_rsp)
			, "=m" (__result->lcs_rbx)
			, "=r" (__result->lcs_rip));
}
#endif /* __x86_64__ */
__LOCAL __NOBLOCK void
__NOTHROW_NCX(lcpustate64_to_gpregs64_ex)(struct lcpustate64 const *__restrict __self,
                                          struct gpregs64 *__restrict __result,
                                          __u64 __v_gp_r11, __u64 __v_gp_r10, __u64 __v_gp_r9,
                                          __u64 __v_gp_r8, __u64 __v_gp_rdi, __u64 __v_gp_rsi,
                                          __u64 __v_gp_rdx, __u64 __v_gp_rcx, __u64 __v_gp_rax) {
	__result->gp_r15 = __self->lcs_r15;
	__result->gp_r14 = __self->lcs_r14;
	__result->gp_r13 = __self->lcs_r13;
	__result->gp_r12 = __self->lcs_r12;
	__result->gp_r11 = __v_gp_r11;
	__result->gp_r10 = __v_gp_r10;
	__result->gp_r9  = __v_gp_r9;
	__result->gp_r8  = __v_gp_r8;
	__result->gp_rdi = __v_gp_rdi;
	__result->gp_rsi = __v_gp_rsi;
	__result->gp_rbp = __self->lcs_rbp;
	__result->gp_rsp = __self->lcs_rsp;
	__result->gp_rbx = __self->lcs_rbx;
	__result->gp_rdx = __v_gp_rdx;
	__result->gp_rcx = __v_gp_rcx;
	__result->gp_rax = __v_gp_rax;
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(lcpustate64_to_gpregs64)(struct lcpustate64 const *__restrict __self,
                                       struct gpregs64 *__restrict __result) {
	lcpustate64_to_gpregs64_ex(__self, __result, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(lcpustate64_to_ucpustate64_ex)(struct lcpustate64 const *__restrict __self,
                                             struct ucpustate64 *__restrict __result,
                                             __u64 __v_sg_gsbase, __u64 __v_sg_fsbase,
                                             __u64 __v_gp_r11, __u64 __v_gp_r10, __u64 __v_gp_r9,
                                             __u64 __v_gp_r8, __u64 __v_gp_rdi, __u64 __v_gp_rsi,
                                             __u64 __v_gp_rdx, __u64 __v_gp_rcx, __u64 __v_gp_rax,
                                             __u16 __v_gs, __u16 __v_fs, __u16 __v_es, __u16 __v_ds,
                                             __u16 __v_cs, __u16 __v_ss, __u64 __v_rflags) {
	lcpustate64_to_gpregs64_ex(__self, &__result->ucs_gpregs,
	                           __v_gp_r11, __v_gp_r10, __v_gp_r9,
	                           __v_gp_r8, __v_gp_rdi, __v_gp_rsi,
	                           __v_gp_rdx, __v_gp_rcx, __v_gp_rax);
	__result->ucs_sgbase.sg_fsbase = __v_sg_fsbase;
	__result->ucs_sgbase.sg_gsbase = __v_sg_gsbase;
	__result->ucs_sgregs.sg_gs  = __v_gs;
	__result->ucs_sgregs.sg_fs  = __v_fs;
	__result->ucs_sgregs.sg_es  = __v_es;
	__result->ucs_sgregs.sg_ds  = __v_ds;
	__result->ucs_cs            = __v_cs;
	__result->ucs_ss            = __v_ss;
	__result->ucs_rflags        = __v_rflags;
	__result->ucs_rip           = __self->lcs_rip;
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(lcpustate64_to_ucpustate64)(struct lcpustate64 const *__restrict __self,
                                          struct ucpustate64 *__restrict __result) {
	lcpustate64_to_ucpustate64_ex(__self, __result,
	                              (__u64)__rdfsbase(),
	                              (__u64)__rdgsbase(),
	                              0, 0, 0, 0, 0, 0, 0, 0, 0,
	                              __rdgs(), __rdfs(), __rdes(), __rdds(),
	                              SEGMENT_CURRENT_CODE_RPL,
	                              SEGMENT_CURRENT_DATA_RPL,
	                              (__u64)__rdflags());
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(lcpustate64_to_kcpustate64_ex)(struct lcpustate64 const *__restrict __self,
                                             struct kcpustate64 *__restrict __result,
                                             __u64 __v_gp_r11, __u64 __v_gp_r10, __u64 __v_gp_r9,
                                             __u64 __v_gp_r8, __u64 __v_gp_rdi, __u64 __v_gp_rsi,
                                             __u64 __v_gp_rdx, __u64 __v_gp_rcx, __u64 __v_gp_rax,
                                             __u64 __v_rflags) {
	lcpustate64_to_gpregs64_ex(__self, &__result->kcs_gpregs,
	                           __v_gp_r11, __v_gp_r10, __v_gp_r9,
	                           __v_gp_r8, __v_gp_rdi, __v_gp_rsi,
	                           __v_gp_rdx, __v_gp_rcx, __v_gp_rax);
	__result->kcs_rflags = __v_rflags;
	__result->kcs_rip    = __self->lcs_rip;
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(lcpustate64_to_kcpustate64)(struct lcpustate64 const *__restrict __self,
                                          struct kcpustate64 *__restrict __result) {
	lcpustate64_to_kcpustate64_ex(__self, __result, 0, 0, 0, 0, 0, 0, 0, 0, 0, (__u64)__rdflags());
}
/************************************************************************/




/************************************************************************/
/* `struct kcpustate64'                                                 */
/************************************************************************/
#define kcpustate64_getrip(self)           ((__u64)(self)->kcs_rip)
#define kcpustate64_setrip(self, value)    ((self)->kcs_rip = (value))
#define kcpustate64_getrsp(self)           ((__u64)(self)->kcs_gpregs.gp_rsp)
#define kcpustate64_setrsp(self, value)    ((self)->kcs_gpregs.gp_rsp = (value))
#define kcpustate64_getrflags(self)        ((__u64)(self)->kcs_rflags)
#define kcpustate64_setrflags(self, value) ((self)->kcs_rflags = (value))
__LOCAL __NOBLOCK void
__NOTHROW_NCX(kcpustate64_to_ucpustate64_ex)(struct kcpustate64 const *__restrict __self,
                                             struct ucpustate64 *__restrict __result,
                                             __u16 __v_gs, __u16 __v_fs, __u16 __v_es,
                                             __u16 __v_ds, __u16 __v_cs, __u16 __v_ss) {
	__result->ucs_gpregs       = __self->kcs_gpregs;
	__result->ucs_sgregs.sg_gs = __v_gs;
	__result->ucs_sgregs.sg_fs = __v_fs;
	__result->ucs_sgregs.sg_es = __v_es;
	__result->ucs_sgregs.sg_ds = __v_ds;
	__result->ucs_cs           = __v_cs;
	__result->ucs_ss           = __v_ss;
	__result->ucs_rflags       = __self->kcs_rflags;
	__result->ucs_rip          = __self->kcs_rip;
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(kcpustate64_to_ucpustate64)(struct kcpustate64 const *__restrict __self,
                                          struct ucpustate64 *__restrict __result) {
	kcpustate64_to_ucpustate64_ex(__self, __result,
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
__NOTHROW_NCX(kcpustate64_to_lcpustate64)(struct kcpustate64 const *__restrict __self,
                                          struct lcpustate64 *__restrict __result) {
	__result->lcs_r15 = __self->kcs_gpregs.gp_r15;
	__result->lcs_r14 = __self->kcs_gpregs.gp_r14;
	__result->lcs_r13 = __self->kcs_gpregs.gp_r13;
	__result->lcs_r12 = __self->kcs_gpregs.gp_r12;
	__result->lcs_rbp = __self->kcs_gpregs.gp_rbp;
	__result->lcs_rsp = __self->kcs_gpregs.gp_rsp;
	__result->lcs_rbx = __self->kcs_gpregs.gp_rbx;
	__result->lcs_rip = __self->kcs_rip;
}
/************************************************************************/




/************************************************************************/
/* `struct icpustate64'                                                 */
/************************************************************************/
#define icpustate64_isuser(self)                 irregs64_isuser(&(self)->ics_irregs)
#define icpustate64_iskernel(self)               irregs64_iskernel(&(self)->ics_irregs)
#define icpustate64_is32(self)                   irregs64_is32(&(self)->ics_irregs)
#define icpustate64_is64(self)                   irregs64_is64(&(self)->ics_irregs)
#define icpustate64_getrip(self)                 irregs64_getrip(&(self)->ics_irregs)
#define icpustate64_setrip(self, value)          irregs64_setrip(&(self)->ics_irregs, value)
#define icpustate64_getrsp(self)                 irregs64_getrsp(&(self)->ics_irregs)
#define icpustate64_getuserrsp(self)             irregs64_getuserrsp(&(self)->ics_irregs)
#define icpustate64_setuserrsp(self, value)      irregs64_setuserrsp(&(self)->ics_irregs, value)
#define icpustate64_getuserss(self)              irregs64_getuserss(&(self)->ics_irregs)
#define icpustate64_setuserss(self, value)       irregs64_setuserss(&(self)->ics_irregs)
#define icpustate64_getkernelss(self)            irregs64_getkernelss(&(self)->ics_irregs)
#define icpustate64_getkernelrsp(self)           irregs64_getkernelrsp(&(self)->ics_irregs)
#define icpustate64_getds(self)                  __rdds()
#define icpustate64_setds(self, value)           __wrds(value)
#define icpustate64_getes(self)                  __rdes()
#define icpustate64_setes(self, value)           __wres(value)
#define icpustate64_getfs(self)                  __rdfs()
#define icpustate64_setfs(self, value)           __wrfs(value)
#define icpustate64_getgs(self)                  __rdgs()
#define icpustate64_setgs(self, value)           __wrgs(value)
#define icpustate64_getrflags(self)              irregs64_getrflags(&(self)->ics_irregs)
#define icpustate64_setrflags(self, value)       irregs64_setrflags(&(self)->ics_irregs, value)
#define icpustate64_mskrflags(self, mask, value) irregs64_mskrflags(&(self)->ics_irregs, mask, value)
#define icpustate64_getcs(self)                  irregs64_getcs(&(self)->ics_irregs)
#define icpustate64_setcs(self, value)           irregs64_setcs(&(self)->ics_irregs, value)
#define icpustate64_getss(self)                  irregs64_getss(&(self)->ics_irregs)
#define icpustate64_setss(self, value)           irregs64_setss(&(self)->ics_irregs, value)
#define icpustate64_trysetss(self, value)        irregs64_trysetss(&(self)->ics_irregs, value)
#define icpustate64_setrsp(self, value)          irregs64_setrsp(&(self)->ics_irregs, value)
#define icpustate64_trysetrsp(self, value)       irregs64_trysetrsp(&(self)->ics_irregs, value)
#define icpustate64_sizeof(self)                 sizeof(struct icpustate64)

__LOCAL __NOBLOCK __ATTR_WUNUSED struct icpustate64 *
__NOTHROW_NCX(icpustate64_setrsp_p)(struct icpustate64 *__restrict __self,
                                    __u64 __v_rsp) {
	icpustate64_setrsp(__self, __v_rsp);
	return __self;
}

__LOCAL __NOBLOCK void
__NOTHROW_NCX(icpustate64_to_ucpustate64_ex)(struct icpustate64 const *__restrict __self,
                                             struct ucpustate64 *__restrict __result,
                                             __u64 __v_gsbase, __u64 __v_fsbase,
                                             __u16 __v_gs, __u16 __v_fs,
                                             __u16 __v_es, __u16 __v_ds) {
	__result->ucs_sgbase.sg_gsbase = __v_gsbase;
	__result->ucs_sgbase.sg_fsbase = __v_fsbase;
	gpregsnsp64_to_gpregs64(&__self->ics_gpregs, &__result->ucs_gpregs,
	                        irregs64_getrsp(&__self->ics_irregs));
	__result->ucs_rip          = irregs64_getrip(&__self->ics_irregs);
	__result->ucs_rflags       = irregs64_getrflags(&__self->ics_irregs);
	__result->ucs_cs           = irregs64_getcs(&__self->ics_irregs);
	__result->ucs_sgregs.sg_gs = __v_gs;
	__result->ucs_sgregs.sg_fs = __v_fs;
	__result->ucs_sgregs.sg_ds = __v_ds;
	__result->ucs_sgregs.sg_es = __v_es;
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(icpustate64_to_ucpustate64)(struct icpustate64 const *__restrict __self,
                                          struct ucpustate64 *__restrict __result) {
	icpustate64_to_ucpustate64_ex(__self, __result,
	                              (__u64)__rdgsbase(), (__u64)__rdfsbase(),
	                              __rdgs(), __rdfs(), __rdes(), __rdds());
}
#define icpustate64_user_to_ucpustate64_ex icpustate64_to_ucpustate64_ex
#define icpustate64_user_to_ucpustate64    icpustate64_to_ucpustate64

/* Create a duplicate of the given interrupt cpu state. */
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct icpustate64 *
__NOTHROW_NCX(icpustate64_to_icpustate64_p)(struct icpustate64 const *__restrict __self,
                                            void *__restrict __kernel_rsp) {
	struct icpustate64 *__result;
	__result = (struct icpustate64 *)((__byte_t *)__kernel_rsp - SIZEOF_ICPUSTATE64);
	__libc_memcpy(__result, __self, SIZEOF_ICPUSTATE64);
	return __result;
}
#define icpustate64_user_to_icpustate64_p icpustate64_to_icpustate64_p
/* Convert the given interrupt CPU state into a scheduler CPU state.
 * NOTE: Unlike the 32-bit variant of this, the kernel-space RSP value
 *       will always be copied, and `KERNEL_RSP' is only used for storage! */
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct scpustate64 *
__NOTHROW_NCX(icpustate64_to_scpustate64_p_ex)(struct icpustate64 const *__restrict __self,
                                               void *__restrict __kernel_rsp,
                                               __u64 __v_gsbase, __u64 __v_fsbase,
                                               __u16 __v_gs, __u16 __v_fs,
                                               __u16 __v_es, __u16 __v_ds) {
	struct scpustate64 *__result;
	__result = (struct scpustate64 *)((__byte_t *)__kernel_rsp - SIZEOF_SCPUSTATE64);
	__result->scs_sgbase.sg_gsbase = __v_gsbase;
	__result->scs_sgbase.sg_fsbase = __v_fsbase;
	__result->scs_sgregs.sg_gs     = __v_gs;
	__result->scs_sgregs.sg_fs     = __v_fs;
	__result->scs_sgregs.sg_es     = __v_es;
	__result->scs_sgregs.sg_ds     = __v_ds;
	__result->scs_gpregs           = __self->ics_gpregs;
	__result->scs_irregs.ir_rip    = icpustate64_getrip(__self);
	__result->scs_irregs.ir_cs     = icpustate64_getcs(__self);
	__result->scs_irregs.ir_rflags = icpustate64_getrflags(__self);
	__result->scs_irregs.ir_rsp    = icpustate64_getrsp(__self);
	__result->scs_irregs.ir_ss     = icpustate64_getss(__self);
	return __result;
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct scpustate64 *
__NOTHROW_NCX(icpustate64_to_scpustate64_p)(struct icpustate64 const *__restrict __self,
                                            void *__restrict __kernel_rsp) {
	return icpustate64_to_scpustate64_p_ex(__self, __kernel_rsp,
	                                       (__u64)__rdgsbase(), (__u64)__rdfsbase(),
	                                       __rdgs(), __rdfs(), __rdes(), __rdds());
}
#define icpustate64_user_to_scpustate64_p_ex icpustate64_to_scpustate64_p_ex
#define icpustate64_user_to_scpustate64_p    icpustate64_to_scpustate64_p
/************************************************************************/




/************************************************************************/
/* `struct scpustate64'                                                 */
/************************************************************************/
#define scpustate64_isuser(self)                 ((self)->scs_irregs.ir_cs16 & 3)
#define scpustate64_iskernel(self)               (!((self)->scs_irregs.ir_cs16 & 3))
#define scpustate64_is32(self)                   __KOS64_IS_CS32(scpustate64_getcs(self))
#define scpustate64_is64(self)                   __KOS64_IS_CS64(scpustate64_getcs(self))
#define scpustate64_getrip(self)                 ((__u64)(self)->scs_irregs.ir_rip)
#define scpustate64_setrip(self, value)          ((self)->scs_irregs.ir_rip = (value))
#define scpustate64_getds(self)                  ((self)->scs_sgregs.sg_ds16)
#define scpustate64_setds(self, value)           ((self)->scs_sgregs.sg_ds = (value))
#define scpustate64_getes(self)                  ((self)->scs_sgregs.sg_es16)
#define scpustate64_setes(self, value)           ((self)->scs_sgregs.sg_es = (value))
#define scpustate64_getfs(self)                  ((self)->scs_sgregs.sg_fs16)
#define scpustate64_setfs(self, value)           ((self)->scs_sgregs.sg_fs = (value))
#define scpustate64_getgs(self)                  ((self)->scs_sgregs.sg_gs16)
#define scpustate64_setgs(self, value)           ((self)->scs_sgregs.sg_gs = (value))
#define scpustate64_getrflags(self)              ((__u64)(self)->scs_irregs.ir_rflags)
#define scpustate64_setrflags(self, value)       ((self)->scs_irregs.ir_rflags = (value))
#define scpustate64_mskrflags(self, mask, value) ((self)->scs_irregs.ir_rflags = ((self)->scs_irregs.ir_rflags & (mask)) | (flags))
#define scpustate64_getcs(self)                  ((__u64)(self)->scs_irregs.ir_cs)
#define scpustate64_setcs(self, value)           ((self)->scs_irregs.ir_cs = (value))
#define scpustate64_getrsp(self)                 ((__u64)(self)->scs_irregs.ir_rsp)
#define scpustate64_setrsp(self, value)          ((self)->scs_irregs.ir_rsp = (value))
#define scpustate64_trysetrsp(self, value)       (scpustate64_setrsp(self, value), 1)
#define scpustate64_getss(self)                  ((__u64)(self)->scs_irregs.ir_ss)
#define scpustate64_setss(self, value)           ((self)->scs_irregs.ir_ss = (value))
#define scpustate64_trysetss(self, value)        (scpustate64_setss(self, value), 1)
#define scpustate64_getuserrsp                   scpustate64_getrsp
#define scpustate64_setuserrsp                   scpustate64_setrsp
#define scpustate64_getuserss                    scpustate64_getss
#define scpustate64_setuserss                    scpustate64_setss
#define scpustate64_getkernelss                  scpustate64_getss
#define scpustate64_getkernelrsp                 scpustate64_getrsp
#define scpustate64_sizeof(self) sizeof(struct scpustate64)

__LOCAL __NOBLOCK __ATTR_WUNUSED struct scpustate64 *
__NOTHROW_NCX(scpustate64_setrsp_p)(struct scpustate64 *__restrict __self,
                                    __u64 __v_rsp) {
	scpustate64_setrsp(__self, __v_rsp);
	return __self;
}

__LOCAL __NOBLOCK void
__NOTHROW_NCX(scpustate64_to_ucpustate64)(struct scpustate64 const *__restrict __self,
                                          struct ucpustate64 *__restrict __result) {
	__result->ucs_sgbase = __self->scs_sgbase;
	gpregsnsp64_to_gpregs64(&__self->scs_gpregs,
	                        &__result->ucs_gpregs,
	                        scpustate64_getrsp(__self));
	__result->ucs_sgregs = __self->scs_sgregs;
	__result->ucs_rip    = irregs64_getrip(&__self->scs_irregs);
	__result->ucs_rflags = irregs64_getrflags(&__self->scs_irregs);
	__result->ucs_cs     = irregs64_getcs(&__self->scs_irregs);
	__result->ucs_ss     = irregs64_getss(&__self->scs_irregs);
}
#define scpustate64_user_to_ucpustate64 scpustate64_to_ucpustate64
/* Convert the given scheduler CPU state into an interrupt CPU state.
 * NOTE: Unlike the 32-bit variant of this, the kernel-space RSP value
 *       will always be copied, and `KERNEL_RSP' is only used for storage! */
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct icpustate64 *
__NOTHROW_NCX(scpustate64_to_icpustate64_p)(struct scpustate64 const *__restrict __self,
                                            void *__restrict __kernel_rsp) {
	struct icpustate64 *__result;
	__result = (struct icpustate64 *)((__byte_t *)__kernel_rsp - SIZEOF_ICPUSTATE64);
	__result->ics_gpregs = __self->scs_gpregs;
	__result->ics_irregs = __self->scs_irregs;
	return __result;
}
#define scpustate64_user_to_icpustate64_p scpustate64_to_icpustate64_p
/* Create a duplicate of the given interrupt cpu state. */
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct scpustate64 *
__NOTHROW_NCX(scpustate64_to_scpustate64_p)(struct scpustate64 const *__restrict __self,
                                            void *__restrict __kernel_rsp) {
	struct scpustate64 *__result;
	__result = (struct scpustate64 *)((__byte_t *)__kernel_rsp - SIZEOF_SCPUSTATE64);
	__libc_memcpy(__result, __self, SIZEOF_SCPUSTATE64);
	return __result;
}
#define scpustate_to_scpustate_p scpustate64_to_scpustate64_p
/************************************************************************/




/************************************************************************/
/* `struct ucpustate64'                                                 */
/************************************************************************/
#define ucpustate64_isuser(self)           ((self)->ucs_cs16 & 3)
#define ucpustate64_iskernel(self)         (!((self)->ucs_cs16 & 3))
#define ucpustate64_is32(self)             __KOS64_IS_CS32((self)->ucs_cs16)
#define ucpustate64_is64(self)             __KOS64_IS_CS64((self)->ucs_cs16)
#define ucpustate64_getrip(self)           ((__u64)(self)->ucs_rip)
#define ucpustate64_setrip(self, value)    ((self)->ucs_rip = (value))
#define ucpustate64_getrsp(self)           ((__u64)(self)->ucs_gpregs.gp_rsp)
#define ucpustate64_setrsp(self, value)    ((self)->ucs_gpregs.gp_rsp = (value))
#define ucpustate64_getrflags(self)        ((__u64)(self)->ucs_rflags)
#define ucpustate64_setrflags(self, value) ((self)->ucs_rflags = (value))
__LOCAL __NOBLOCK void
__NOTHROW_NCX(ucpustate64_to_kcpustate64)(struct ucpustate64 const *__restrict __self,
                                          struct kcpustate64 *__restrict __result) {
	__result->kcs_gpregs = __self->ucs_gpregs;
	__result->kcs_rflags = __self->ucs_rflags;
	__result->kcs_rip    = __self->ucs_rip;
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct icpustate64 *
__NOTHROW_NCX(ucpustate64_to_icpustate64_p)(struct ucpustate64 const *__restrict __self,
                                            void *__restrict __kernel_rsp) {
	struct icpustate64 *__result;
	__result = (struct icpustate64 *)((__byte_t *)__kernel_rsp - SIZEOF_ICPUSTATE64);
	gpregs64_to_gpregsnsp64(&__self->ucs_gpregs, &__result->ics_gpregs);
	__result->ics_irregs.ir_rip    = __self->ucs_rip;
	__result->ics_irregs.ir_cs     = __self->ucs_cs16;
	__result->ics_irregs.ir_rflags = __self->ucs_rflags;
	__result->ics_irregs.ir_rsp    = __self->ucs_gpregs.gp_rsp;
	__result->ics_irregs.ir_ss     = __self->ucs_ss16;
	return __result;
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct scpustate64 *
__NOTHROW_NCX(ucpustate64_to_scpustate64_p)(struct ucpustate64 const *__restrict __self,
                                            void *__restrict __kernel_rsp) {
	struct scpustate64 *__result;
	__result = (struct scpustate64 *)((__byte_t *)__kernel_rsp - SIZEOF_ICPUSTATE64);
	gpregs64_to_gpregsnsp64(&__self->ucs_gpregs, &__result->scs_gpregs);
	__result->scs_sgbase           = __self->ucs_sgbase;
	__result->scs_sgregs           = __self->ucs_sgregs;
	__result->scs_irregs.ir_rip    = __self->ucs_rip;
	__result->scs_irregs.ir_cs     = __self->ucs_cs16;
	__result->scs_irregs.ir_rflags = __self->ucs_rflags;
	__result->scs_irregs.ir_rsp    = __self->ucs_gpregs.gp_rsp;
	__result->scs_irregs.ir_ss     = __self->ucs_ss16;
	return __result;
}
/************************************************************************/




/************************************************************************/
/* `struct fcpustate64'                                                 */
/************************************************************************/
#define fcpustate64_isuser(self)           ((self)->fcs_sgregs.sg_cs16 & 3)
#define fcpustate64_iskernel(self)         (!((self)->fcs_sgregs.sg_cs16 & 3))
#define fcpustate64_is32(self)             __KOS64_IS_CS32((self)->fcs_sgregs.sg_cs16)
#define fcpustate64_is64(self)             __KOS64_IS_CS64((self)->fcs_sgregs.sg_cs16)
#define fcpustate64_getrip(self)           ((__u64)(self)->fcs_rip)
#define fcpustate64_setrip(self, value)    ((self)->fcs_rip = (value))
#define fcpustate64_getrsp(self)           ((__u64)(self)->fcs_gpregs.gp_rsp)
#define fcpustate64_setrsp(self, value)    ((self)->fcs_gpregs.gp_rsp = (value))
#define fcpustate64_getrflags(self)        ((__u64)(self)->fcs_rflags)
#define fcpustate64_setrflags(self, value) ((self)->fcs_rflags = (value))
__LOCAL __NOBLOCK void
__NOTHROW_NCX(fcpustate64_to_lcpustate64)(struct fcpustate64 const *__restrict __self,
                                          struct lcpustate64 *__restrict __result) {
	__result->lcs_r15 = __self->fcs_gpregs.gp_r15;
	__result->lcs_r14 = __self->fcs_gpregs.gp_r14;
	__result->lcs_r13 = __self->fcs_gpregs.gp_r13;
	__result->lcs_r12 = __self->fcs_gpregs.gp_r12;
	__result->lcs_rbp = __self->fcs_gpregs.gp_rbp;
	__result->lcs_rsp = __self->fcs_gpregs.gp_rsp;
	__result->lcs_rbx = __self->fcs_gpregs.gp_rbx;
	__result->lcs_rip = __self->fcs_rip;
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(fcpustate64_to_kcpustate64)(struct fcpustate64 const *__restrict __self,
                                          struct kcpustate64 *__restrict __result) {
	__result->kcs_gpregs = __self->fcs_gpregs;
	__result->kcs_rip    = __self->fcs_rip;
	__result->kcs_rflags = __self->fcs_rflags;
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(fcpustate64_to_ucpustate64)(struct fcpustate64 const *__restrict __self,
                                          struct ucpustate64 *__restrict __result) {
	__result->ucs_sgbase       = __self->fcs_sgbase;
	__result->ucs_gpregs       = __self->fcs_gpregs;
	__result->ucs_rip          = __self->fcs_rip;
	__result->ucs_rflags       = __self->fcs_rflags;
	__result->ucs_sgregs.sg_gs = __self->fcs_sgregs.sg_gs;
	__result->ucs_sgregs.sg_fs = __self->fcs_sgregs.sg_fs;
	__result->ucs_sgregs.sg_es = __self->fcs_sgregs.sg_es;
	__result->ucs_sgregs.sg_ds = __self->fcs_sgregs.sg_ds;
	__result->ucs_cs           = __self->fcs_sgregs.sg_cs;
	__result->ucs_ss           = __self->fcs_sgregs.sg_ss;
}
/* Assign fields from `DATA' (but leave fields not defined by `DATA' as unchanged) */
__LOCAL __NOBLOCK void
__NOTHROW_NCX(fcpustate64_assign_ucpustate64)(struct fcpustate64 *__restrict __self,
                                              struct ucpustate64 const *__restrict __data) {
	__self->fcs_sgbase       = __data->ucs_sgbase;
	__self->fcs_gpregs       = __data->ucs_gpregs;
	__self->fcs_rip          = __data->ucs_rip;
	__self->fcs_rflags       = __data->ucs_rflags;
	__self->fcs_sgregs.sg_gs = __data->ucs_sgregs.sg_gs;
	__self->fcs_sgregs.sg_fs = __data->ucs_sgregs.sg_fs;
	__self->fcs_sgregs.sg_es = __data->ucs_sgregs.sg_es;
	__self->fcs_sgregs.sg_ds = __data->ucs_sgregs.sg_ds;
	__self->fcs_sgregs.sg_cs = __data->ucs_cs;
	__self->fcs_sgregs.sg_ss = __data->ucs_ss;
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(fcpustate64_assign_scpustate64)(struct fcpustate64 *__restrict __self,
                                              struct scpustate64 const *__restrict __data) {
	gpregsnsp64_to_gpregs64(&__data->scs_gpregs, &__self->fcs_gpregs,
	                        scpustate64_getrsp(__data));
	__self->fcs_rip          = scpustate64_getrip(__data);
	__self->fcs_rflags       = scpustate64_getrflags(__data);
	__self->fcs_sgregs.sg_cs = scpustate64_getcs(__data);
	__self->fcs_sgregs.sg_ss = scpustate64_getss(__data);
	__self->fcs_sgregs.sg_gs = __data->scs_sgregs.sg_gs16;
	__self->fcs_sgregs.sg_fs = __data->scs_sgregs.sg_fs16;
	__self->fcs_sgregs.sg_es = __data->scs_sgregs.sg_es16;
	__self->fcs_sgregs.sg_ds = __data->scs_sgregs.sg_ds16;
	__self->fcs_sgbase       = __data->scs_sgbase;
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(fcpustate64_assign_icpustate64_ex)(struct fcpustate64 *__restrict __self,
                                                 struct icpustate64 const *__restrict __data,
                                                 __u64 __v_gsbase, __u64 __v_fsbase,
                                                 __u16 __v_gs, __u16 __v_fs,
                                                 __u16 __v_es, __u16 __v_ds) {
	gpregsnsp64_to_gpregs64(&__data->ics_gpregs, &__self->fcs_gpregs,
	                        icpustate64_getrsp(__data));
	__self->fcs_rip              = icpustate64_getrip(__data);
	__self->fcs_rflags           = icpustate64_getrflags(__data);
	__self->fcs_sgregs.sg_cs     = icpustate64_getcs(__data);
	__self->fcs_sgregs.sg_ss     = icpustate64_getss(__data);
	__self->fcs_sgregs.sg_gs     = __v_gs;
	__self->fcs_sgregs.sg_fs     = __v_fs;
	__self->fcs_sgregs.sg_es     = __v_es;
	__self->fcs_sgregs.sg_ds     = __v_ds;
	__self->fcs_sgbase.sg_gsbase = __v_gsbase;
	__self->fcs_sgbase.sg_fsbase = __v_fsbase;
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(fcpustate64_assign_icpustate64)(struct fcpustate64 *__restrict __self,
                                              struct icpustate64 const *__restrict __data) {
	fcpustate64_assign_icpustate64_ex(__self, __data,
	                                  (__u64)__rdgsbase(), (__u64)__rdfsbase(),
	                                  __rdgs(), __rdfs(), __rdes(), __rdds());
}
/************************************************************************/


/* TODO: kcpustate64_to_icpustate64_p */
/* TODO: kcpustate64_to_scpustate64_p */
/* TODO: fcpustate64_to_icpustate64_p */
/* TODO: fcpustate64_to_scpustate64_p */



#ifdef __x86_64__
#define gpregs_getp15                       gpregs64_getr15
#define gpregs_setp15                       gpregs64_setr15
#define gpregs_getp14                       gpregs64_getr14
#define gpregs_setp14                       gpregs64_setr14
#define gpregs_getp13                       gpregs64_getr13
#define gpregs_setp13                       gpregs64_setr13
#define gpregs_getp12                       gpregs64_getr12
#define gpregs_setp12                       gpregs64_setr12
#define gpregs_getp11                       gpregs64_getr11
#define gpregs_setp11                       gpregs64_setr11
#define gpregs_getp10                       gpregs64_getr10
#define gpregs_setp10                       gpregs64_setr10
#define gpregs_getp9                        gpregs64_getr9
#define gpregs_setp9                        gpregs64_setr9
#define gpregs_getp8                        gpregs64_getr8
#define gpregs_setp8                        gpregs64_setr8
#define gpregs_getpdi                       gpregs64_getrdi
#define gpregs_setpdi                       gpregs64_setrdi
#define gpregs_getpsi                       gpregs64_getrsi
#define gpregs_setpsi                       gpregs64_setrsi
#define gpregs_getpbp                       gpregs64_getrbp
#define gpregs_setpbp                       gpregs64_setrbp
#define gpregs_getpsp                       gpregs64_getrsp
#define gpregs_setpsp                       gpregs64_setrsp
#define gpregs_getpbx                       gpregs64_getrbx
#define gpregs_setpbx                       gpregs64_setrbx
#define gpregs_getpdx                       gpregs64_getrdx
#define gpregs_setpdx                       gpregs64_setrdx
#define gpregs_getpcx                       gpregs64_getrcx
#define gpregs_setpcx                       gpregs64_setrcx
#define gpregs_getpax                       gpregs64_getrax
#define gpregs_setpax                       gpregs64_setrax
#define gpregsnsp_to_gpregs                 gpregsnsp64_to_gpregs64
#define gpregs_to_gpregsnsp                 gpregs64_to_gpregsnsp64

#define irregs_isvm86(self)                 0
#define irregs_isuser(self)                 irregs64_isuser(self)
#define irregs_isuser_novm86(self)          irregs64_isuser(self)
#define irregs_iskernel(self)               irregs64_iskernel(self)
#define irregs_is32(self)                   irregs64_is32(self)
#define irregs_is64(self)                   irregs64_is64(self)
#define irregs_isnative(self)               irregs64_is64(self)
#define irregs_iscompat(self)               irregs64_is32(self)
#define irregs_getpc                        irregs64_getrip
#define irregs_setpc                        irregs64_setrip
#define irregs_getcs                        irregs64_getcs
#define irregs_setcs                        irregs64_setcs
#define irregs_getpflags                    irregs64_getrflags
#define irregs_setpflags                    irregs64_setrflags
#define irregs_mskpflags                    irregs64_mskrflags
#define irregs_getsp                        irregs64_getrsp
#define irregs_getuserpsp                   irregs64_getuserrsp
#define irregs_setuserpsp                   irregs64_setuserrsp
#define irregs_getuserss                    irregs64_getuserss
#define irregs_setuserss                    irregs64_setuserss
#define irregs_getkernelpsp                 irregs64_getkernelrsp
#define irregs_getkernelss                  irregs64_getkernelss
#define irregs_getss                        irregs64_getss
#define irregs_trysetss                     irregs64_trysetss
#define irregs_trysetrsp                    irregs64_trysetrsp
#define irregs_sizeof                       irregs64_sizeof

#define lcpustate_getpc                     lcpustate64_getrip
#define lcpustate_setpc                     lcpustate64_setrip
#define lcpustate_getsp                     lcpustate64_getrsp
#define lcpustate_setsp                     lcpustate64_setrsp
#define lcpustate_current                   lcpustate64_current
#define lcpustate_to_gpregs_ex              lcpustate64_to_gpregs64_ex
#define lcpustate_to_gpregs                 lcpustate64_to_gpregs64
#define lcpustate_to_ucpustate_ex           lcpustate64_to_ucpustate64_ex
#define lcpustate_to_ucpustate              lcpustate64_to_ucpustate64
#define lcpustate_to_kcpustate_ex           lcpustate64_to_kcpustate64_ex
#define lcpustate_to_kcpustate              lcpustate64_to_kcpustate64

#define kcpustate_getpc                     kcpustate64_getrip
#define kcpustate_setpc                     kcpustate64_setrip
#define kcpustate_getsp                     kcpustate64_getrsp
#define kcpustate_setsp                     kcpustate64_setrsp
#define kcpustate_getpflags                 kcpustate64_getrflags
#define kcpustate_setpflags                 kcpustate64_setrflags
#define kcpustate_to_ucpustate_ex           kcpustate64_to_ucpustate64_ex
#define kcpustate_to_ucpustate              kcpustate64_to_ucpustate64
#define kcpustate_to_lcpustate              kcpustate64_to_lcpustate64

#define icpustate_isvm86(self)              0
#define icpustate_isuser_novm86             icpustate64_isuser
#define icpustate_isuser                    icpustate64_isuser
#define icpustate_iskernel                  icpustate64_iskernel
#define icpustate_is32                      icpustate64_is32
#define icpustate_is64                      icpustate64_is64
#define icpustate_isnative                  icpustate64_isnative
#define icpustate_iscompat                  icpustate64_iscompat
#define icpustate_getpc                     icpustate64_getrip
#define icpustate_setpc                     icpustate64_setrip
#define icpustate_getsp                     icpustate64_getrsp
#define icpustate_setsp                     icpustate64_setrsp
#define icpustate_trysetsp                  icpustate64_trysetrsp
#define icpustate_setsp_p                   icpustate64_setrsp_p
#define icpustate_getuserpsp                icpustate64_getuserrsp
#define icpustate_setuserpsp                icpustate64_setuserrsp
#define icpustate_getuserss                 icpustate64_getuserss
#define icpustate_setuserss                 icpustate64_setuserss
#define icpustate_getkernelss               icpustate64_getkernelss
#define icpustate_getkernelpsp              icpustate64_getkernelrsp
#define icpustate_getds                     icpustate64_getds
#define icpustate_setds                     icpustate64_setds
#define icpustate_getes                     icpustate64_getes
#define icpustate_setes                     icpustate64_setes
#define icpustate_getfs                     icpustate64_getfs
#define icpustate_setfs                     icpustate64_setfs
#define icpustate_getgs                     icpustate64_getgs
#define icpustate_setgs                     icpustate64_setgs
#define icpustate_getds_novm86              icpustate64_getds
#define icpustate_setds_novm86              icpustate64_setds
#define icpustate_getes_novm86              icpustate64_getes
#define icpustate_setes_novm86              icpustate64_setes
#define icpustate_getfs_novm86              icpustate64_getfs
#define icpustate_setfs_novm86              icpustate64_setfs
#define icpustate_getgs_novm86              icpustate64_getgs
#define icpustate_setgs_novm86              icpustate64_setgs
#define icpustate_getpflags                 icpustate64_getrflags
#define icpustate_setpflags                 icpustate64_setrflags
#define icpustate_mskpflags                 icpustate64_mskrflags
#define icpustate_getcs                     icpustate64_getcs
#define icpustate_setcs                     icpustate64_setcs
#define icpustate_getss                     icpustate64_getss
#define icpustate_setss                     icpustate64_setss
#define icpustate_trysetss                  icpustate64_trysetss
#define icpustate_sizeof                    icpustate64_sizeof
#define icpustate_to_ucpustate_ex           icpustate64_to_ucpustate64_ex
#define icpustate_to_ucpustate              icpustate64_to_ucpustate64
#define icpustate_user_to_ucpustate_ex      icpustate64_user_to_ucpustate64_ex
#define icpustate_user_to_ucpustate         icpustate64_user_to_ucpustate64
#define icpustate_to_scpustate_p_ex         icpustate64_to_scpustate64_p_ex
#define icpustate_to_scpustate_p            icpustate64_to_scpustate64_p
#define icpustate_to_icpustate_p            icpustate64_to_icpustate64_p
#define icpustate_user_to_scpustate_p_ex    icpustate64_user_to_scpustate64_p_ex
#define icpustate_user_to_scpustate_p       icpustate64_user_to_scpustate64_p
#define icpustate_user_to_icpustate_p       icpustate64_user_to_icpustate64_p

#define scpustate_isvm86(self)              0
#define scpustate_isuser_novm86             scpustate64_isuser
#define scpustate_isuser                    scpustate64_isuser
#define scpustate_iskernel                  scpustate64_iskernel
#define scpustate_is32                      scpustate64_is32
#define scpustate_is64                      scpustate64_is64
#define scpustate_isnative                  scpustate64_isnative
#define scpustate_iscompat                  scpustate64_iscompat
#define scpustate_getpc                     scpustate64_getrip
#define scpustate_setpc                     scpustate64_setrip
#define scpustate_getsp                     scpustate64_getrsp
#define scpustate_setsp                     scpustate64_setrsp
#define scpustate_trysetsp                  scpustate64_trysetrsp
#define scpustate_setsp_p                   scpustate64_setrsp_p
#define scpustate_getuserpsp                scpustate64_getuserrsp
#define scpustate_setuserpsp                scpustate64_setuserrsp
#define scpustate_getuserss                 scpustate64_getuserss
#define scpustate_setuserss                 scpustate64_setuserss
#define scpustate_getkernelss               scpustate64_getkernelss
#define scpustate_getkernelpsp              scpustate64_getkernelrsp
#define scpustate_getds                     scpustate64_getds
#define scpustate_setds                     scpustate64_setds
#define scpustate_getes                     scpustate64_getes
#define scpustate_setes                     scpustate64_setes
#define scpustate_getfs                     scpustate64_getfs
#define scpustate_setfs                     scpustate64_setfs
#define scpustate_getgs                     scpustate64_getgs
#define scpustate_setgs                     scpustate64_setgs
#define scpustate_getds_novm86              scpustate64_getds
#define scpustate_setds_novm86              scpustate64_setds
#define scpustate_getes_novm86              scpustate64_getes
#define scpustate_setes_novm86              scpustate64_setes
#define scpustate_getfs_novm86              scpustate64_getfs
#define scpustate_setfs_novm86              scpustate64_setfs
#define scpustate_getgs_novm86              scpustate64_getgs
#define scpustate_setgs_novm86              scpustate64_setgs
#define scpustate_getpflags                 scpustate64_getrflags
#define scpustate_setpflags                 scpustate64_setrflags
#define scpustate_mskpflags                 scpustate64_mskrflags
#define scpustate_getcs                     scpustate64_getcs
#define scpustate_setcs                     scpustate64_setcs
#define scpustate_getss                     scpustate64_getss
#define scpustate_setss                     scpustate64_setss
#define scpustate_trysetss                  scpustate64_trysetss
#define scpustate_sizeof                    scpustate64_sizeof
#define scpustate_to_ucpustate              scpustate64_to_ucpustate64
#define scpustate_user_to_ucpustate         scpustate64_user_to_ucpustate64
#define scpustate_to_icpustate_p            scpustate64_to_icpustate64_p
#define scpustate_to_scpustate_p            scpustate64_to_scpustate64_p
#define scpustate_user_to_icpustate_p       scpustate64_user_to_icpustate64_p
#define scpustate_user_to_scpustate_p       scpustate64_user_to_scpustate64_p

#define ucpustate_isvm86(self)              0
#define ucpustate_isuser_novm86             ucpustate64_isuser
#define ucpustate_isuser                    ucpustate64_isuser
#define ucpustate_iskernel                  ucpustate64_iskernel
#define ucpustate_is32                      ucpustate64_is32
#define ucpustate_is64                      ucpustate64_is64
#define ucpustate_isnative                  ucpustate64_isnative
#define ucpustate_iscompat                  ucpustate64_iscompat
#define ucpustate_getpc                     ucpustate64_getrip
#define ucpustate_setpc                     ucpustate64_setrip
#define ucpustate_getsp                     ucpustate64_getrsp
#define ucpustate_setsp                     ucpustate64_setrsp
#define ucpustate_getpflags                 ucpustate64_getrflags
#define ucpustate_setpflags                 ucpustate64_setrflags
#define ucpustate_to_kcpustate              ucpustate64_to_kcpustate64
#define ucpustate_to_icpustate_p            ucpustate64_to_icpustate64_p
#define ucpustate_to_scpustate_p            ucpustate64_to_scpustate64_p

#define fcpustate_isvm86(self)              0
#define fcpustate_isuser_novm86             fcpustate64_isuser
#define fcpustate_isuser                    fcpustate64_isuser
#define fcpustate_iskernel                  fcpustate64_iskernel
#define fcpustate_is32                      fcpustate64_is32
#define fcpustate_is64                      fcpustate64_is64
#define fcpustate_isnative                  fcpustate64_isnative
#define fcpustate_iscompat                  fcpustate64_iscompat
#define fcpustate_getpc                     fcpustate64_getrip
#define fcpustate_setpc                     fcpustate64_setrip
#define fcpustate_getsp                     fcpustate64_getrsp
#define fcpustate_setsp                     fcpustate64_setrsp
#define fcpustate_getpflags                 fcpustate64_getrflags
#define fcpustate_setpflags                 fcpustate64_setrflags
#define fcpustate_to_lcpustate              fcpustate64_to_lcpustate64
#define fcpustate_to_kcpustate              fcpustate64_to_kcpustate64
#define fcpustate_to_ucpustate              fcpustate64_to_ucpustate64
#define fcpustate_assign_ucpustate          fcpustate64_assign_ucpustate64
#define fcpustate_assign_scpustate          fcpustate64_assign_scpustate64
#define fcpustate_assign_icpustate_ex       fcpustate64_assign_icpustate64_ex
#define fcpustate_assign_icpustate          fcpustate64_assign_icpustate64

#endif /* __x86_64__ */

__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_KOS_KERNEL_CPU_STATE_HELPERS64_H */
