/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
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

#ifndef __CPUSTATE_GET_USER_GSBASE
#ifdef __KERNEL__
#include <kernel/x86/gdt.h> /* x86_get_user_(fs|gs)base() */
#define __CPUSTATE_GET_USER_GSBASE() x86_get_user_gsbase()
#define __CPUSTATE_GET_USER_FSBASE() x86_get_user_fsbase()
#else /* __KERNEL__ */
#define __CPUSTATE_GET_USER_GSBASE() ((__uintptr_t)__rdgsbase())
#define __CPUSTATE_GET_USER_FSBASE() ((__uintptr_t)__rdfsbase())
#endif /* !__KERNEL__ */
#endif /* !__CPUSTATE_GET_USER_GSBASE */

#ifdef __CC__
__DECL_BEGIN

/************************************************************************/
/* `struct gpregsnsp64'                                                 */
/************************************************************************/
#define gpregsnsp64_foreach_elem(self) \
	((__UINT64_TYPE__ const *)__COMPILER_REQTYPE(struct gpregsnsp64 const *, self))
#define gpregsnsp64_foreach_size(self) 15
#define gpregsnsp64_foreach(self, cb)                                    \
	do {                                                                 \
		unsigned int __gpregsnsp64_foreach_i;                            \
		for (__gpregsnsp64_foreach_i = 0;                                \
		     __gpregsnsp64_foreach_i < gpregsnsp64_foreach_size(self);   \
		     ++__gpregsnsp64_foreach_i) {                                \
			cb(gpregsnsp64_foreach_elem(self)[__gpregsnsp64_foreach_i]); \
		}                                                                \
	}	__WHILE0
#define gpregsnsp64_to_gpregsnsp64(self, result)                        \
	__libc_memcpy(__COMPILER_REQTYPE(struct gpregsnsp64 *, result),     \
	              __COMPILER_REQTYPE(struct gpregsnsp64 const *, self), \
	              sizeof(struct gpregsnsp64))
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
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
#define gpregs64_foreach_elem(self) \
	((__UINT64_TYPE__ const *)__COMPILER_REQTYPE(struct gpregs64 const *, self))
#define gpregs64_foreach_size(self) 16
#define gpregs64_foreach(self, cb)                                 \
	do {                                                           \
		unsigned int __gpregs64_foreach_i;                         \
		for (__gpregs64_foreach_i = 0;                             \
		     __gpregs64_foreach_i < gpregs64_foreach_size(self);   \
		     ++__gpregs64_foreach_i) {                             \
			cb(gpregs64_foreach_elem(self)[__gpregs64_foreach_i]); \
		}                                                          \
	}	__WHILE0
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
#define gpregs64_to_gpregs64(self, result)                           \
	__libc_memcpy(__COMPILER_REQTYPE(struct gpregs64 *, result),     \
	              __COMPILER_REQTYPE(struct gpregs64 const *, self), \
	              sizeof(struct gpregs64))
/* Get/set return registers. */
#define gpregs64_getreturn64 gpregs64_getrax
#define gpregs64_setreturn64 gpregs64_setrax
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
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
#define irregs64_is32bit(self)           __KOS64_IS_CS32BIT(irregs64_getcs(self))
#define irregs64_is64bit(self)           __KOS64_IS_CS64BIT(irregs64_getcs(self))
#define irregs64_getpreemption(self)     (irregs64_getrflags(self) & 0x200)
#define irregs64_setpreemption(self, turn_on) irregs64_mskrflags(self, ~0x200, (turn_on) ? 0x200 : 0)
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

/* NOTE: We don't enumerate `%rip'! */
#define lcpustate64_foreach_gpregs_elem(self) \
	((__UINT64_TYPE__ const *)__COMPILER_REQTYPE(struct lcpustate64 const *, self))
#define lcpustate64_foreach_gpregs_size(self) 7
#define lcpustate64_foreach_gpregs(self, cb)                             \
	do {                                                                 \
		unsigned int __lcpustate64_foreach_i;                            \
		for (__lcpustate64_foreach_i = 0;                                \
		     __lcpustate64_foreach_i < lcpustate64_foreach_size(self);   \
		     ++__lcpustate64_foreach_i) {                                \
			cb(lcpustate64_foreach_elem(self)[__lcpustate64_foreach_i]); \
		}                                                                \
	}	__WHILE0
#define lcpustate64_getrip(self)        ((__u64)(self)->lcs_rip)
#define lcpustate64_setrip(self, value) ((self)->lcs_rip = (value))
#define lcpustate64_getrsp(self)        ((__u64)(self)->lcs_rsp)
#define lcpustate64_setrsp(self, value) ((self)->lcs_rsp = (value))
#define lcpustate64_to_lcpustate64(self, result)                        \
	__libc_memcpy(__COMPILER_REQTYPE(struct lcpustate64 *, result),     \
	              __COMPILER_REQTYPE(struct lcpustate64 const *, self), \
	              sizeof(struct lcpustate64))
#ifdef __x86_64__
__FORCELOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(lcpustate64_current)(struct lcpustate64 *__restrict __result) {
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
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
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
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(lcpustate64_to_gpregs64)(struct lcpustate64 const *__restrict __self,
                                       struct gpregs64 *__restrict __result) {
	lcpustate64_to_gpregs64_ex(__self, __result, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
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
	__result->ucs_sgbase.sg_gsbase = __v_sg_gsbase;
	__result->ucs_sgbase.sg_fsbase = __v_sg_fsbase;
	__result->ucs_sgregs.sg_gs  = __v_gs;
	__result->ucs_sgregs.sg_fs  = __v_fs;
	__result->ucs_sgregs.sg_es  = __v_es;
	__result->ucs_sgregs.sg_ds  = __v_ds;
	__result->ucs_cs            = __v_cs;
	__result->ucs_ss            = __v_ss;
	__result->ucs_rflags        = __v_rflags;
	__result->ucs_rip           = __self->lcs_rip;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(lcpustate64_to_ucpustate64)(struct lcpustate64 const *__restrict __self,
                                          struct ucpustate64 *__restrict __result) {
	lcpustate64_to_ucpustate64_ex(__self, __result,
	                              (__u64)__CPUSTATE_GET_USER_GSBASE(),
	                              (__u64)__CPUSTATE_GET_USER_FSBASE(),
	                              0, 0, 0, 0, 0, 0, 0, 0, 0,
	                              __rdgs(), __rdfs(), __rdes(), __rdds(),
	                              SEGMENT_CURRENT_CODE_RPL,
	                              SEGMENT_CURRENT_DATA_RPL,
	                              (__u64)__rdflags());
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
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
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(lcpustate64_to_kcpustate64)(struct lcpustate64 const *__restrict __self,
                                          struct kcpustate64 *__restrict __result) {
	lcpustate64_to_kcpustate64_ex(__self, __result, 0, 0, 0, 0, 0, 0, 0, 0, 0, (__u64)__rdflags());
}
/************************************************************************/




/************************************************************************/
/* `struct kcpustate64'                                                 */
/************************************************************************/
#define kcpustate64_foreach_gpregs_elem(self)   gpregs64_foreach_elem(&(self)->kcs_gpregs)
#define kcpustate64_foreach_gpregs_size(self)   gpregs64_foreach_size(&(self)->kcs_gpregs)
#define kcpustate64_foreach_gpregs(self, cb)    gpregs64_foreach(&(self)->kcs_gpregs, cb)
#define kcpustate64_getrip(self)                ((__u64)(self)->kcs_rip)
#define kcpustate64_setrip(self, value)         ((self)->kcs_rip = (value))
#define kcpustate64_getrsp(self)                ((__u64)(self)->kcs_gpregs.gp_rsp)
#define kcpustate64_setrsp(self, value)         ((self)->kcs_gpregs.gp_rsp = (value))
#define kcpustate64_getrflags(self)             ((__u64)(self)->kcs_rflags)
#define kcpustate64_setrflags(self, value)      ((self)->kcs_rflags = (value))
#define kcpustate64_mskrflags(self, mask, flag) ((self)->kcs_rflags = ((self)->kcs_rflags & (mask)) | (flag))
#define kcpustate64_to_kcpustate64(self, result)                        \
	__libc_memcpy(__COMPILER_REQTYPE(struct kcpustate64 *, result),     \
	              __COMPILER_REQTYPE(struct kcpustate64 const *, self), \
	              sizeof(struct kcpustate64))
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(kcpustate64_to_ucpustate64_ex)(struct kcpustate64 const *__restrict __self,
                                             struct ucpustate64 *__restrict __result,
                                             __u64 __v_sg_gsbase, __u64 __v_sg_fsbase,
                                             __u16 __v_gs, __u16 __v_fs, __u16 __v_es,
                                             __u16 __v_ds, __u16 __v_cs, __u16 __v_ss) {
	__result->ucs_sgbase.sg_gsbase = __v_sg_gsbase;
	__result->ucs_sgbase.sg_fsbase = __v_sg_fsbase;
	__libc_memcpy(&__result->ucs_gpregs,
	              &__self->kcs_gpregs,
	              sizeof(struct gpregs64));
	__result->ucs_sgregs.sg_gs = __v_gs;
	__result->ucs_sgregs.sg_fs = __v_fs;
	__result->ucs_sgregs.sg_es = __v_es;
	__result->ucs_sgregs.sg_ds = __v_ds;
	__result->ucs_cs           = __v_cs;
	__result->ucs_ss           = __v_ss;
	__result->ucs_rflags       = __self->kcs_rflags;
	__result->ucs_rip          = __self->kcs_rip;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(kcpustate64_to_ucpustate64)(struct kcpustate64 const *__restrict __self,
                                          struct ucpustate64 *__restrict __result) {
	kcpustate64_to_ucpustate64_ex(__self, __result,
	                              (__u64)__CPUSTATE_GET_USER_GSBASE(),
	                              (__u64)__CPUSTATE_GET_USER_FSBASE(),
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
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct scpustate64 *
__NOTHROW_NCX(kcpustate64_to_scpustate64_p_ex)(struct kcpustate64 const *__restrict __self,
                                               void *__restrict __kernel_rsp,
                                               __u64 __v_sg_gsbase, __u64 __v_sg_fsbase,
                                               __u16 __v_gs, __u16 __v_fs, __u16 __v_es,
                                               __u16 __v_ds, __u16 __v_cs, __u16 __v_ss) {
	struct scpustate64 *__result;
	__result = (struct scpustate64 *)((__byte_t *)__kernel_rsp - SIZEOF_SCPUSTATE64);
	__result->scs_sgbase.sg_gsbase = __v_sg_gsbase;
	__result->scs_sgbase.sg_fsbase = __v_sg_fsbase;
	gpregs64_to_gpregsnsp64(&__self->kcs_gpregs, &__result->scs_gpregs);
	__result->scs_sgregs.sg_gs     = __v_gs;
	__result->scs_sgregs.sg_fs     = __v_fs;
	__result->scs_sgregs.sg_es     = __v_es;
	__result->scs_sgregs.sg_ds     = __v_ds;
	__result->scs_irregs.ir_rip    = __self->kcs_rip;
	__result->scs_irregs.ir_cs     = __v_cs;
	__result->scs_irregs.ir_rflags = __self->kcs_rflags;
	__result->scs_irregs.ir_rsp    = __self->kcs_gpregs.gp_rsp;
	__result->scs_irregs.ir_ss     = __v_ss;
	return __result;
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct icpustate64 *
__NOTHROW_NCX(kcpustate64_to_icpustate64_p_ex)(struct kcpustate64 const *__restrict __self,
                                               void *__restrict __kernel_rsp,
                                               __u16 __v_cs, __u16 __v_ss) {
	struct icpustate64 *__result;
	__result = (struct icpustate64 *)((__byte_t *)__kernel_rsp - SIZEOF_ICPUSTATE64);
	gpregs64_to_gpregsnsp64(&__self->kcs_gpregs, &__result->ics_gpregs);
	__result->ics_irregs.ir_rip    = __self->kcs_rip;
	__result->ics_irregs.ir_cs     = __v_cs;
	__result->ics_irregs.ir_rflags = __self->kcs_rflags;
	__result->ics_irregs.ir_rsp    = __self->kcs_gpregs.gp_rsp;
	__result->ics_irregs.ir_ss     = __v_ss;
	return __result;
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct scpustate64 *
__NOTHROW_NCX(kcpustate64_to_scpustate64_p)(struct kcpustate64 const *__restrict __self,
                                            void *__restrict __kernel_rsp) {
	return kcpustate64_to_scpustate64_p_ex(__self, __kernel_rsp,
	                                       (__u64)__CPUSTATE_GET_USER_GSBASE(),
	                                       (__u64)__CPUSTATE_GET_USER_FSBASE(),
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
__NOTHROW_NCX(kcpustate64_to_icpustate64_p)(struct kcpustate64 const *__restrict __self,
                                            void *__restrict __kernel_rsp) {
	return kcpustate64_to_icpustate64_p_ex(__self, __kernel_rsp,
	                                       SEGMENT_CURRENT_CODE_RPL,
	                                       SEGMENT_CURRENT_DATA_RPL);
}
/************************************************************************/




/************************************************************************/
/* `struct icpustate64'                                                 */
/************************************************************************/
#define icpustate64_foreach_gpregs(self, cb)          \
	do {                                              \
		gpregsnsp64_foreach(&(self)->ics_gpregs, cb); \
		cb((self)->ics_irregs.ir_rsp);                \
	}	__WHILE0
#define icpustate64_isuser(self)                 irregs64_isuser(&(self)->ics_irregs)
#define icpustate64_iskernel(self)               irregs64_iskernel(&(self)->ics_irregs)
#define icpustate64_is32bit(self)                irregs64_is32bit(&(self)->ics_irregs)
#define icpustate64_is64bit(self)                irregs64_is64bit(&(self)->ics_irregs)
#define icpustate64_getpreemption(self)          irregs64_getpreemption(&(self)->ics_irregs)
#define icpustate64_setpreemption(self, turn_on) irregs64_setpreemption(&(self)->ics_irregs, turn_on)
#define icpustate64_getrip(self)                 irregs64_getrip(&(self)->ics_irregs)
#define icpustate64_setrip(self, value)          irregs64_setrip(&(self)->ics_irregs, value)
#define icpustate64_getrsp(self)                 irregs64_getrsp(&(self)->ics_irregs)
#define icpustate64_getuserrsp(self)             irregs64_getuserrsp(&(self)->ics_irregs)
#define icpustate64_setuserrsp(self, value)      irregs64_setuserrsp(&(self)->ics_irregs, value)
#define icpustate64_getuserss(self)              irregs64_getuserss(&(self)->ics_irregs)
#define icpustate64_setuserss(self, value)       irregs64_setuserss(&(self)->ics_irregs, value)
#define icpustate64_getkernelss(self)            irregs64_getkernelss(&(self)->ics_irregs)
#define icpustate64_getkernelrsp(self)           irregs64_getkernelrsp(&(self)->ics_irregs)
#define icpustate64_getds(self)                  __rdds()
#define icpustate64_setds(self, value)           __wrds(value)
#define icpustate64_getes(self)                  __rdes()
#define icpustate64_setes(self, value)           __wres(value)
#define icpustate64_getfs(self)                  __rdfs()
#define icpustate64_getgs(self)                  __rdgs()
#ifdef __x86_64__
#define icpustate64_setfs(self, value)           __wrfs_keepbase(value)
#define icpustate64_setgs(self, value)           __wrgs_keepbase(value)
#else /* __x86_64__ */
#define icpustate64_setfs(self, value)           __wrfs(value)
#define icpustate64_setgs(self, value)           __wrgs(value)
#endif /* !__x86_64__ */
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

__LOCAL __NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) struct icpustate64 *
__NOTHROW_NCX(icpustate64_setrsp_p)(struct icpustate64 *__restrict __self,
                                    __u64 __v_rsp) {
	icpustate64_setrsp(__self, __v_rsp);
	return __self;
}

__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
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
	__result->ucs_ss           = irregs64_getss(&__self->ics_irregs);
	__result->ucs_sgregs.sg_gs = __v_gs;
	__result->ucs_sgregs.sg_fs = __v_fs;
	__result->ucs_sgregs.sg_ds = __v_ds;
	__result->ucs_sgregs.sg_es = __v_es;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(icpustate64_to_ucpustate64)(struct icpustate64 const *__restrict __self,
                                          struct ucpustate64 *__restrict __result) {
	icpustate64_to_ucpustate64_ex(__self, __result,
	                              (__u64)__CPUSTATE_GET_USER_GSBASE(),
	                              (__u64)__CPUSTATE_GET_USER_FSBASE(),
	                              __rdgs(),
	                              __rdfs(),
	                              __rdes(),
	                              __rdds());
}
#define icpustate64_user_to_ucpustate64_ex icpustate64_to_ucpustate64_ex
#define icpustate64_user_to_ucpustate64    icpustate64_to_ucpustate64
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(icpustate64_to_kcpustate64)(struct icpustate64 const *__restrict __self,
                                          struct kcpustate64 *__restrict __result) {
	gpregsnsp64_to_gpregs64(&__self->ics_gpregs, &__result->kcs_gpregs,
	                        icpustate64_getrsp(__self));
	__result->kcs_rflags = icpustate64_getrflags(__self);
	__result->kcs_rip    = icpustate64_getrip(__self);
}
#define icpustate64_user_to_kcpustate64 icpustate64_to_kcpustate64

/* Create a duplicate of the given interrupt cpu state. */
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct icpustate64 *
__NOTHROW_NCX(icpustate64_to_icpustate64_p)(struct icpustate64 const *__restrict __self,
                                            void *__restrict __kernel_rsp) {
	struct icpustate64 *__result;
	__result = (struct icpustate64 *)((__byte_t *)__kernel_rsp - SIZEOF_ICPUSTATE64);
	__libc_memcpy(__result, __self, SIZEOF_ICPUSTATE64);
	return __result;
}
#define icpustate64_user_to_icpustate64_p icpustate64_to_icpustate64_p
/* Convert the given interrupt CPU state into a scheduler CPU state.
 * NOTE: Unlike  the 32-bit  variant of  this, the  kernel-space RSP value
 *       will always be copied, and `KERNEL_RSP' is only used for storage! */
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct scpustate64 *
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
	__libc_memcpy(&__result->scs_gpregs,
	              &__self->ics_gpregs,
	              sizeof(struct gpregsnsp64));
	__result->scs_irregs.ir_rip    = icpustate64_getrip(__self);
	__result->scs_irregs.ir_cs     = icpustate64_getcs(__self);
	__result->scs_irregs.ir_rflags = icpustate64_getrflags(__self);
	__result->scs_irregs.ir_rsp    = icpustate64_getrsp(__self);
	__result->scs_irregs.ir_ss     = icpustate64_getss(__self);
	return __result;
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct scpustate64 *
__NOTHROW_NCX(icpustate64_to_scpustate64_p)(struct icpustate64 const *__restrict __self,
                                            void *__restrict __kernel_rsp) {
	return icpustate64_to_scpustate64_p_ex(__self, __kernel_rsp,
	                                       (__u64)__CPUSTATE_GET_USER_GSBASE(),
	                                       (__u64)__CPUSTATE_GET_USER_FSBASE(),
	                                       __rdgs(),
	                                       __rdfs(),
	                                       __rdes(),
	                                       __rdds());
}
#define icpustate64_user_to_scpustate64_p_ex icpustate64_to_scpustate64_p_ex
#define icpustate64_user_to_scpustate64_p    icpustate64_to_scpustate64_p
/************************************************************************/




/************************************************************************/
/* `struct scpustate64'                                                 */
/************************************************************************/
#define scpustate64_foreach_gpregs(self, cb)          \
	do {                                              \
		cb((self)->scs_sgbase.sg_gsbase);             \
		cb((self)->scs_sgbase.sg_fsbase);             \
		gpregsnsp64_foreach(&(self)->scs_gpregs, cb); \
		cb((self)->scs_irregs.ir_rsp);                \
	}	__WHILE0
#define scpustate64_isuser(self)                 ((self)->scs_irregs.ir_cs16 & 3)
#define scpustate64_iskernel(self)               (!((self)->scs_irregs.ir_cs16 & 3))
#define scpustate64_is32bit(self)                __KOS64_IS_CS32BIT(scpustate64_getcs(self))
#define scpustate64_is64bit(self)                __KOS64_IS_CS64BIT(scpustate64_getcs(self))
#define scpustate64_getpreemption(self)          ((self)->scs_irregs.ir_rflags & 0x200)
#define scpustate64_setpreemption(self, turn_on) (turn_on ? (void)((self)->scs_irregs.ir_rflags |= 0x200) : (void)((self)->scs_irregs.ir_rflags &= ~0x200))
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

__LOCAL __NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) struct scpustate64 *
__NOTHROW_NCX(scpustate64_setrsp_p)(struct scpustate64 *__restrict __self,
                                    __u64 __v_rsp) {
	scpustate64_setrsp(__self, __v_rsp);
	return __self;
}

__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(scpustate64_to_ucpustate64)(struct scpustate64 const *__restrict __self,
                                          struct ucpustate64 *__restrict __result) {
	__result->ucs_sgbase = __self->scs_sgbase;
	gpregsnsp64_to_gpregs64(&__self->scs_gpregs,
	                        &__result->ucs_gpregs,
	                        scpustate64_getrsp(__self));
	__libc_memcpy(&__result->ucs_sgregs,
	              &__self->scs_sgregs,
	              sizeof(struct sgregs64));
	__result->ucs_rip    = irregs64_getrip(&__self->scs_irregs);
	__result->ucs_rflags = irregs64_getrflags(&__self->scs_irregs);
	__result->ucs_cs     = irregs64_getcs(&__self->scs_irregs);
	__result->ucs_ss     = irregs64_getss(&__self->scs_irregs);
}
#define scpustate64_user_to_ucpustate64 scpustate64_to_ucpustate64
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(scpustate64_to_kcpustate64)(struct scpustate64 const *__restrict __self,
                                          struct kcpustate64 *__restrict __result) {
	gpregsnsp64_to_gpregs64(&__self->scs_gpregs, &__result->kcs_gpregs,
	                        scpustate64_getrsp(__self));
	__result->kcs_rflags = scpustate64_getrflags(__self);
	__result->kcs_rip    = scpustate64_getrip(__self);
}
#define scpustate64_user_to_kcpustate64 scpustate64_to_kcpustate64
/* Convert the given scheduler CPU state into an interrupt CPU state.
 * NOTE: Unlike  the 32-bit  variant of  this, the  kernel-space RSP value
 *       will always be copied, and `KERNEL_RSP' is only used for storage! */
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct icpustate64 *
__NOTHROW_NCX(scpustate64_to_icpustate64_p)(struct scpustate64 const *__restrict __self,
                                            void *__restrict __kernel_rsp) {
	struct icpustate64 *__result;
	__result = (struct icpustate64 *)((__byte_t *)__kernel_rsp - SIZEOF_ICPUSTATE64);
	__libc_memcpy(&__result->ics_gpregs,
	              &__self->scs_gpregs,
	              sizeof(struct gpregsnsp64));
	__libc_memcpy(&__result->ics_irregs,
	              &__self->scs_irregs,
	              sizeof(struct irregs64));
	return __result;
}
#define scpustate64_user_to_icpustate64_p scpustate64_to_icpustate64_p
/* Create a duplicate of the given interrupt cpu state. */
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct scpustate64 *
__NOTHROW_NCX(scpustate64_to_scpustate64_p)(struct scpustate64 const *__restrict __self,
                                            void *__restrict __kernel_rsp) {
	struct scpustate64 *__result;
	__result = (struct scpustate64 *)((__byte_t *)__kernel_rsp - SIZEOF_SCPUSTATE64);
	__libc_memcpy(__result, __self, SIZEOF_SCPUSTATE64);
	return __result;
}
#define scpustate64_user_to_scpustate64_p scpustate64_to_scpustate64_p
/************************************************************************/




/************************************************************************/
/* `struct ucpustate64'                                                 */
/************************************************************************/
#define ucpustate64_foreach_gpregs(self, cb)       \
	do {                                           \
		cb((self)->ucs_sgbase.sg_gsbase);          \
		cb((self)->ucs_sgbase.sg_fsbase);          \
		gpregs64_foreach(&(self)->ucs_gpregs, cb); \
	}	__WHILE0
#define ucpustate64_isuser(self)           ((self)->ucs_cs16 & 3)
#define ucpustate64_iskernel(self)         (!((self)->ucs_cs16 & 3))
#define ucpustate64_is32bit(self)          __KOS64_IS_CS32BIT((self)->ucs_cs16)
#define ucpustate64_is64bit(self)          __KOS64_IS_CS64BIT((self)->ucs_cs16)
#define ucpustate64_getrip(self)           ((__u64)(self)->ucs_rip)
#define ucpustate64_setrip(self, value)    ((self)->ucs_rip = (value))
#define ucpustate64_getrsp(self)           ((__u64)(self)->ucs_gpregs.gp_rsp)
#define ucpustate64_setrsp(self, value)    ((self)->ucs_gpregs.gp_rsp = (value))
#define ucpustate64_getrflags(self)        ((__u64)(self)->ucs_rflags)
#define ucpustate64_setrflags(self, value) ((self)->ucs_rflags = (value))
#define ucpustate64_mskrflags(self, mask, flag) ((self)->ucs_rflags = ((self)->ucs_rflags & (mask)) | (flag))
#define ucpustate64_getes(self)            ((self)->ucs_sgregs.sg_es16)
#define ucpustate64_setes(self, value)     ((self)->ucs_sgregs.sg_es = (u16)(value))
#define ucpustate64_getds(self)            ((self)->ucs_sgregs.sg_ds16)
#define ucpustate64_setds(self, value)     ((self)->ucs_sgregs.sg_ds = (u16)(value))
#define ucpustate64_getcs(self)            ((self)->ucs_cs16)
#define ucpustate64_setcs(self, value)     ((self)->ucs_cs = (u16)(value))
#define ucpustate64_getss(self)            ((self)->ucs_ss16)
#define ucpustate64_setss(self, value)     ((self)->ucs_ss = (u16)(value))
#define ucpustate64_getfs(self)            ((self)->ucs_sgregs.sg_fs16)
#define ucpustate64_setfs(self, value)     ((self)->ucs_sgregs.sg_fs = (u16)(value))
#define ucpustate64_getgs(self)            ((self)->ucs_sgregs.sg_gs16)
#define ucpustate64_setgs(self, value)     ((self)->ucs_sgregs.sg_gs = (u16)(value))
#define ucpustate64_to_ucpustate64(self, result)                        \
	__libc_memcpy(__COMPILER_REQTYPE(struct ucpustate64 *, result),     \
	              __COMPILER_REQTYPE(struct ucpustate64 const *, self), \
	              sizeof(struct ucpustate64))
#ifdef __x86_64__
__LOCAL __NOBLOCK __ATTR_NONNULL((1)) void
__NOTHROW_NCX(ucpustate64_current)(struct ucpustate64 *__restrict __result) {
	__register __REGISTER_TYPE__ __temp;
	__COMPILER_BARRIER();
	__asm__ __volatile__("movq %%r15, 64(%2)\n\t"
	                     "movq %%r14, 72(%2)\n\t"
	                     "movq %%r13, 80(%2)\n\t"
	                     "movq %%r12, 88(%2)\n\t"
	                     "movq %%r11, 96(%2)\n\t"
	                     "movq %%r10, 104(%2)\n\t"
	                     "movq %%r9, 112(%2)\n\t"
	                     "movq %%r8, 120(%2)\n\t"
	                     "movq %%rdi, 128(%2)\n\t"
	                     "movq %%rsi, 136(%2)\n\t"
	                     "movq %%rbp, 144(%2)\n\t"
	                     "movq %%rsp, 152(%2)\n\t"
	                     "movq %%rbx, 160(%2)\n\t"
	                     "movq %%rdx, 168(%2)\n\t"
	                     "movq %%rcx, 176(%2)\n\t"
	                     "movq %%rax, 184(%2)\n\t"
	                     "pushfq\n\t"
	                     ".cfi_adjust_cfa_offset 8\n\t"
	                     "popq 192(%2)\n\t"
	                     ".cfi_adjust_cfa_offset -8\n\t"
	                     "leaq 991f(%%rip), %1\n\t"
	                     "movq %1, 200(%2)\n\t"
	                     "991:"
	                     : "=m" /*0*/ (*__result)
	                     , "=&r" /*1*/ (__temp)
	                     : "r" /*2*/ (__result));
	__result->ucs_sgbase.sg_gsbase = __CPUSTATE_GET_USER_GSBASE();
	__result->ucs_sgbase.sg_fsbase = __CPUSTATE_GET_USER_FSBASE();
	__result->ucs_cs               = SEGMENT_CURRENT_CODE_RPL;
	__result->ucs_ss               = SEGMENT_CURRENT_DATA_RPL;
	__result->ucs_sgregs.sg_gs     = __rdgs();
	__result->ucs_sgregs.sg_fs     = __rdfs();
	__result->ucs_sgregs.sg_es     = __rdes();
	__result->ucs_sgregs.sg_ds     = __rdds();
	__COMPILER_BARRIER();
}
#endif /* __x86_64__ */

__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(ucpustate64_to_kcpustate64)(struct ucpustate64 const *__restrict __self,
                                          struct kcpustate64 *__restrict __result) {
	__result->kcs_gpregs = __self->ucs_gpregs;
	__result->kcs_rflags = __self->ucs_rflags;
	__result->kcs_rip    = __self->ucs_rip;
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct icpustate64 *
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
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct scpustate64 *
__NOTHROW_NCX(ucpustate64_to_scpustate64_p)(struct ucpustate64 const *__restrict __self,
                                            void *__restrict __kernel_rsp) {
	struct scpustate64 *__result;
	__result = (struct scpustate64 *)((__byte_t *)__kernel_rsp - SIZEOF_SCPUSTATE64);
	gpregs64_to_gpregsnsp64(&__self->ucs_gpregs, &__result->scs_gpregs);
	__libc_memcpy(&__result->scs_sgbase,
	              &__self->ucs_sgbase,
	              sizeof(struct sgbase64));
	__libc_memcpy(&__result->scs_sgregs,
	              &__self->ucs_sgregs,
	              sizeof(struct sgregs64));
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
#define fcpustate64_foreach_gpregs(self, cb)       \
	do {                                           \
		gpregs64_foreach(&(self)->fcs_gpregs, cb); \
		cb((self)->fcs_sgbase.sg_gsbase);          \
		cb((self)->fcs_sgbase.sg_fsbase);          \
		cb((self)->fcs_gdt.dt_base);               \
		cb((self)->fcs_idt.dt_base);               \
	}	__WHILE0
#define fcpustate64_isuser(self)           ((self)->fcs_sgregs.sg_cs16 & 3)
#define fcpustate64_iskernel(self)         (!((self)->fcs_sgregs.sg_cs16 & 3))
#define fcpustate64_is32bit(self)          __KOS64_IS_CS32BIT((self)->fcs_sgregs.sg_cs16)
#define fcpustate64_is64bit(self)          __KOS64_IS_CS64BIT((self)->fcs_sgregs.sg_cs16)
#define fcpustate64_getrip(self)           ((__u64)(self)->fcs_rip)
#define fcpustate64_setrip(self, value)    ((self)->fcs_rip = (value))
#define fcpustate64_getrsp(self)           ((__u64)(self)->fcs_gpregs.gp_rsp)
#define fcpustate64_setrsp(self, value)    ((self)->fcs_gpregs.gp_rsp = (value))
#define fcpustate64_getrflags(self)        ((__u64)(self)->fcs_rflags)
#define fcpustate64_setrflags(self, value) ((self)->fcs_rflags = (value))
#define fcpustate64_mskrflags(self, mask, flag) ((self)->fcs_rflags = ((self)->fcs_rflags & (mask)) | (flag))
#define fcpustate64_to_fcpustate64(self, result)                        \
	__libc_memcpy(__COMPILER_REQTYPE(struct fcpustate64 *, result),     \
	              __COMPILER_REQTYPE(struct fcpustate64 const *, self), \
	              sizeof(struct fcpustate64))
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
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
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(fcpustate64_to_kcpustate64)(struct fcpustate64 const *__restrict __self,
                                          struct kcpustate64 *__restrict __result) {
	__libc_memcpy(&__result->kcs_gpregs,
	              &__self->fcs_gpregs,
	              sizeof(struct gpregs64));
	__result->kcs_rip    = __self->fcs_rip;
	__result->kcs_rflags = __self->fcs_rflags;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(fcpustate64_to_ucpustate64)(struct fcpustate64 const *__restrict __self,
                                          struct ucpustate64 *__restrict __result) {
	__libc_memcpy(&__result->ucs_sgbase,
	              &__self->fcs_sgbase,
	              sizeof(struct sgbase64));
	__libc_memcpy(&__result->ucs_gpregs,
	              &__self->fcs_gpregs,
	              sizeof(struct gpregs64));
	__result->ucs_rip          = __self->fcs_rip;
	__result->ucs_rflags       = __self->fcs_rflags;
	__result->ucs_sgregs.sg_gs = __self->fcs_sgregs.sg_gs;
	__result->ucs_sgregs.sg_fs = __self->fcs_sgregs.sg_fs;
	__result->ucs_sgregs.sg_es = __self->fcs_sgregs.sg_es;
	__result->ucs_sgregs.sg_ds = __self->fcs_sgregs.sg_ds;
	__result->ucs_cs           = __self->fcs_sgregs.sg_cs;
	__result->ucs_ss           = __self->fcs_sgregs.sg_ss;
}
/* Assign fields from `data' (but leave fields not defined by `data' as unchanged) */
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(fcpustate64_assign_ucpustate64)(struct fcpustate64 *__restrict __self,
                                              struct ucpustate64 const *__restrict __data) {
	__libc_memcpy(&__self->fcs_sgbase,
	              &__data->ucs_sgbase,
	              sizeof(struct sgbase64));
	__libc_memcpy(&__self->fcs_gpregs,
	              &__data->ucs_gpregs,
	              sizeof(struct gpregs64));
	__self->fcs_rip          = __data->ucs_rip;
	__self->fcs_rflags       = __data->ucs_rflags;
	__self->fcs_sgregs.sg_gs = __data->ucs_sgregs.sg_gs;
	__self->fcs_sgregs.sg_fs = __data->ucs_sgregs.sg_fs;
	__self->fcs_sgregs.sg_es = __data->ucs_sgregs.sg_es;
	__self->fcs_sgregs.sg_ds = __data->ucs_sgregs.sg_ds;
	__self->fcs_sgregs.sg_cs = __data->ucs_cs;
	__self->fcs_sgregs.sg_ss = __data->ucs_ss;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(fcpustate64_assign_lcpustate64)(struct fcpustate64 *__restrict __self,
                                              struct lcpustate64 const *__restrict __data) {
	__self->fcs_gpregs.gp_r15 = __data->lcs_r15;
	__self->fcs_gpregs.gp_r14 = __data->lcs_r14;
	__self->fcs_gpregs.gp_r13 = __data->lcs_r13;
	__self->fcs_gpregs.gp_r12 = __data->lcs_r12;
	__self->fcs_gpregs.gp_rbp = __data->lcs_rbp;
	__self->fcs_gpregs.gp_rsp = __data->lcs_rsp;
	__self->fcs_gpregs.gp_rbx = __data->lcs_rbx;
	__self->fcs_rip           = __data->lcs_rip;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(fcpustate64_assign_kcpustate64)(struct fcpustate64 *__restrict __self,
                                              struct kcpustate64 const *__restrict __data) {
	__libc_memcpy(&__self->fcs_gpregs,
	              &__data->kcs_gpregs,
	              sizeof(struct gpregs64));
	__self->fcs_rflags = __data->kcs_rflags;
	__self->fcs_rip    = __data->kcs_rip;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
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
	__libc_memcpy(&__self->fcs_sgbase,
	              &__data->scs_sgbase,
	              sizeof(struct sgbase64));
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
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
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(fcpustate64_assign_icpustate64)(struct fcpustate64 *__restrict __self,
                                              struct icpustate64 const *__restrict __data) {
	fcpustate64_assign_icpustate64_ex(__self, __data,
	                                  (__u64)__CPUSTATE_GET_USER_GSBASE(),
	                                  (__u64)__CPUSTATE_GET_USER_FSBASE(),
	                                  __rdgs(),
	                                  __rdfs(),
	                                  __rdes(),
	                                  __rdds());
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct icpustate64 *
__NOTHROW_NCX(fcpustate64_to_icpustate64_p)(struct fcpustate64 const *__restrict __self,
                                            void *__kernel_rsp) {
	struct icpustate64 *__result;
	__result = (struct icpustate64 *)((__byte_t *)__kernel_rsp - SIZEOF_ICPUSTATE64);
	gpregs64_to_gpregsnsp64(&__self->fcs_gpregs, &__result->ics_gpregs);
	__result->ics_irregs.ir_rip    = __self->fcs_rip;
	__result->ics_irregs.ir_cs     = __self->fcs_sgregs.sg_cs16;
	__result->ics_irregs.ir_rflags = __self->fcs_rflags;
	__result->ics_irregs.ir_rsp    = __self->fcs_gpregs.gp_rsp;
	__result->ics_irregs.ir_ss     = __self->fcs_sgregs.sg_ss16;
	return __result;
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct scpustate64 *
__NOTHROW_NCX(fcpustate64_to_scpustate64_p)(struct fcpustate64 const *__restrict __self,
                                            void *__kernel_rsp) {
	struct scpustate64 *__result;
	__result = (struct scpustate64 *)((__byte_t *)__kernel_rsp - SIZEOF_SCPUSTATE64);
	__libc_memcpy(&__result->scs_sgbase,
	              &__self->fcs_sgbase,
	              sizeof(struct sgbase64));
	__result->scs_sgregs.sg_gs = __self->fcs_sgregs.sg_gs;
	__result->scs_sgregs.sg_fs = __self->fcs_sgregs.sg_fs;
	__result->scs_sgregs.sg_es = __self->fcs_sgregs.sg_es;
	__result->scs_sgregs.sg_ds = __self->fcs_sgregs.sg_ds;
	gpregs64_to_gpregsnsp64(&__self->fcs_gpregs, &__result->scs_gpregs);
	__result->scs_irregs.ir_rip    = __self->fcs_rip;
	__result->scs_irregs.ir_cs     = __self->fcs_sgregs.sg_cs16;
	__result->scs_irregs.ir_rflags = __self->fcs_rflags;
	__result->scs_irregs.ir_rsp    = __self->fcs_gpregs.gp_rsp;
	__result->scs_irregs.ir_ss     = __self->fcs_sgregs.sg_ss16;
	return __result;
}
/************************************************************************/




#ifdef __x86_64__
#define gpregsnsp_foreach_elem              gpregsnsp64_foreach_elem
#define gpregsnsp_foreach_size              gpregsnsp64_foreach_size
#define gpregsnsp_foreach                   gpregsnsp64_foreach
#define gpregsnsp_to_gpregsnsp              gpregsnsp64_to_gpregsnsp64
#define gpregsnsp_to_gpregsnsp64            gpregsnsp64_to_gpregsnsp64
#define gpregsnsp64_to_gpregsnsp            gpregsnsp64_to_gpregsnsp64
#define gpregsnsp_to_gpregs                 gpregsnsp64_to_gpregs64
#define gpregsnsp_to_gpregs64               gpregsnsp64_to_gpregs64
#define gpregsnsp64_to_gpregs               gpregsnsp64_to_gpregs64

#define gpregs_foreach_elem                 gpregs64_foreach_elem
#define gpregs_foreach_size                 gpregs64_foreach_size
#define gpregs_foreach                      gpregs64_foreach
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
#define gpregs_to_gpregs                    gpregs64_to_gpregs64
#define gpregs_to_gpregs64                  gpregs64_to_gpregs64
#define gpregs64_to_gpregs                  gpregs64_to_gpregs64
#define gpregs_to_gpregsnsp                 gpregs64_to_gpregsnsp64
#define gpregs_to_gpregsnsp64               gpregs64_to_gpregsnsp64
#define gpregs64_to_gpregsnsp               gpregs64_to_gpregsnsp64
#define gpregs_getreturnbool                gpregs64_getreturn64
#define gpregs_getreturn                    gpregs64_getreturn64
#define gpregs_getreturn32                  gpregs64_getreturn64
#define gpregs_getreturn64                  gpregs64_getreturn64
#define gpregs_setreturnbool                gpregs64_setreturn64
#define gpregs_setreturn                    gpregs64_setreturn64
#define gpregs_setreturn32                  gpregs64_setreturn64
#define gpregs_setreturn64                  gpregs64_setreturn64

#define irregs_isvm86(self)                 0
#define irregs_isuser(self)                 irregs64_isuser(self)
#define irregs_isuser_novm86(self)          irregs64_isuser(self)
#define irregs_iskernel(self)               irregs64_iskernel(self)
#define irregs_is32bit(self)                irregs64_is32bit(self)
#define irregs_is64bit(self)                irregs64_is64bit(self)
#define irregs_isnative(self)               irregs64_is64bit(self)
#define irregs_iscompat(self)               irregs64_is32bit(self)
#define irregs_getpreemption                irregs64_getpreemption
#define irregs_setpreemption                irregs64_setpreemption
#define irregs_getpip                       irregs64_getrip
#define irregs_getpc                        (__byte_t const *)irregs64_getrip
#define irregs_setpip                       irregs64_setrip
#define irregs_setpc(self, pc)              irregs64_setrip(self, (__u64)__COMPILER_REQTYPE(void const *, pc))
#define irregs_getcs                        irregs64_getcs
#define irregs_setcs                        irregs64_setcs
#define irregs_getpflags                    irregs64_getrflags
#define irregs_setpflags                    irregs64_setrflags
#define irregs_mskpflags                    irregs64_mskrflags
#define irregs_getpsp                       irregs64_getrsp
#define irregs_getsp                        (__byte_t *)irregs64_getrsp
#define irregs_getuserpsp                   irregs64_getuserrsp
#define irregs_getusersp                    (__byte_t *)irregs64_getuserrsp
#define irregs_setuserpsp                   irregs64_setuserrsp
#define irregs_setusersp(self, sp)          irregs64_setuserrsp(self, (__u64)__COMPILER_REQTYPE(void const *, sp))
#define irregs_getuserss                    irregs64_getuserss
#define irregs_setuserss                    irregs64_setuserss
#define irregs_getkernelpsp                 irregs64_getkernelrsp
#define irregs_getkernelsp                  (__byte_t *)irregs64_getkernelrsp
#define irregs_getkernelss                  irregs64_getkernelss
#define irregs_getss                        irregs64_getss
#define irregs_trysetss                     irregs64_trysetss
#define irregs_trysetpsp                    irregs64_trysetrsp
#define irregs_trysetsp(self, sp)           irregs64_trysetrsp(self, (__u64)__COMPILER_REQTYPE(void const *, sp))
#define irregs_sizeof                       irregs64_sizeof

#define lcpustate_foreach_gpregs_elem       lcpustate64_foreach_gpregs_elem
#define lcpustate_foreach_gpregs_size       lcpustate64_foreach_gpregs_size
#define lcpustate_foreach_gpregs            lcpustate64_foreach_gpregs
#define lcpustate_getpip                    lcpustate64_getrip
#define lcpustate_getpc                     (__byte_t const *)lcpustate64_getrip
#define lcpustate_setpip                    lcpustate64_setrip
#define lcpustate_setpc(self, pc)           lcpustate64_setrip(self, (__u64)__COMPILER_REQTYPE(void const *, pc))
#define lcpustate_getpsp                    lcpustate64_getrsp
#define lcpustate_getsp                     (__byte_t *)lcpustate64_getrsp
#define lcpustate_setpsp                    lcpustate64_setrsp
#define lcpustate_setsp(self, sp)           lcpustate64_setrsp(self, (__u64)__COMPILER_REQTYPE(void const *, sp))
#define lcpustate_current                   lcpustate64_current
#define lcpustate_to_lcpustate              lcpustate64_to_lcpustate64
#define lcpustate_to_lcpustate64            lcpustate64_to_lcpustate64
#define lcpustate64_to_lcpustate            lcpustate64_to_lcpustate64
#define lcpustate_to_gpregs_ex              lcpustate64_to_gpregs64_ex
#define lcpustate_to_gpregs64_ex            lcpustate64_to_gpregs64_ex
#define lcpustate64_to_gpregs_ex            lcpustate64_to_gpregs64_ex
#define lcpustate_to_gpregs                 lcpustate64_to_gpregs64
#define lcpustate_to_gpregs64               lcpustate64_to_gpregs64
#define lcpustate64_to_gpregs               lcpustate64_to_gpregs64
#define lcpustate_to_ucpustate_ex           lcpustate64_to_ucpustate64_ex
#define lcpustate_to_ucpustate64_ex         lcpustate64_to_ucpustate64_ex
#define lcpustate64_to_ucpustate_ex         lcpustate64_to_ucpustate64_ex
#define lcpustate_to_ucpustate              lcpustate64_to_ucpustate64
#define lcpustate_to_ucpustate64            lcpustate64_to_ucpustate64
#define lcpustate64_to_ucpustate            lcpustate64_to_ucpustate64
#define lcpustate_to_kcpustate_ex           lcpustate64_to_kcpustate64_ex
#define lcpustate_to_kcpustate64_ex         lcpustate64_to_kcpustate64_ex
#define lcpustate64_to_kcpustate_ex         lcpustate64_to_kcpustate64_ex
#define lcpustate_to_kcpustate              lcpustate64_to_kcpustate64
#define lcpustate_to_kcpustate64            lcpustate64_to_kcpustate64
#define lcpustate64_to_kcpustate            lcpustate64_to_kcpustate64

#define kcpustate_foreach_gpregs_elem       kcpustate64_foreach_gpregs_elem
#define kcpustate_foreach_gpregs_size       kcpustate64_foreach_gpregs_size
#define kcpustate_foreach_gpregs            kcpustate64_foreach_gpregs
#define kcpustate_getpip                    kcpustate64_getrip
#define kcpustate_getpc                     (__byte_t const *)kcpustate64_getrip
#define kcpustate_setpip                    kcpustate64_setrip
#define kcpustate_setpc(self, pc)           kcpustate64_setrip(self, (__u64)__COMPILER_REQTYPE(void const *, pc))
#define kcpustate_getpsp                    kcpustate64_getrsp
#define kcpustate_getsp                     (__byte_t *)kcpustate64_getrsp
#define kcpustate_setpsp                    kcpustate64_setrsp
#define kcpustate_setsp(self, sp)           kcpustate64_setrsp(self, (__u64)__COMPILER_REQTYPE(void const *, sp))
#define kcpustate_getpflags                 kcpustate64_getrflags
#define kcpustate_setpflags                 kcpustate64_setrflags
#define kcpustate_mskpflags                 kcpustate64_mskrflags
#define kcpustate_to_kcpustate              kcpustate64_to_kcpustate64
#define kcpustate_to_kcpustate64            kcpustate64_to_kcpustate64
#define kcpustate64_to_kcpustate            kcpustate64_to_kcpustate64
#define kcpustate_to_ucpustate_ex           kcpustate64_to_ucpustate64_ex
#define kcpustate_to_ucpustate64_ex         kcpustate64_to_ucpustate64_ex
#define kcpustate64_to_ucpustate_ex         kcpustate64_to_ucpustate64_ex
#define kcpustate_to_ucpustate              kcpustate64_to_ucpustate64
#define kcpustate_to_ucpustate64            kcpustate64_to_ucpustate64
#define kcpustate64_to_ucpustate            kcpustate64_to_ucpustate64
#define kcpustate_to_lcpustate              kcpustate64_to_lcpustate64
#define kcpustate_to_lcpustate64            kcpustate64_to_lcpustate64
#define kcpustate64_to_lcpustate            kcpustate64_to_lcpustate64
#define kcpustate_to_scpustate_p_ex         kcpustate64_to_scpustate64_p_ex
#define kcpustate_to_scpustate64_p_ex       kcpustate64_to_scpustate64_p_ex
#define kcpustate64_to_scpustate_p_ex       kcpustate64_to_scpustate64_p_ex
#define kcpustate_to_scpustate_p            kcpustate64_to_scpustate64_p
#define kcpustate_to_scpustate64_p          kcpustate64_to_scpustate64_p
#define kcpustate64_to_scpustate_p          kcpustate64_to_scpustate64_p
#define kcpustate_to_icpustate_p_ex         kcpustate64_to_icpustate64_p_ex
#define kcpustate_to_icpustate64_p_ex       kcpustate64_to_icpustate64_p_ex
#define kcpustate64_to_icpustate_p_ex       kcpustate64_to_icpustate64_p_ex
#define kcpustate_to_icpustate_p            kcpustate64_to_icpustate64_p
#define kcpustate_to_icpustate64_p          kcpustate64_to_icpustate64_p
#define kcpustate64_to_icpustate_p          kcpustate64_to_icpustate64_p
#define kcpustate_getreturnbool(self)       gpregs_getreturnbool(&(self)->kcs_gpregs)
#define kcpustate_getreturn(self)           gpregs_getreturn(&(self)->kcs_gpregs)
#define kcpustate_getreturn32(self)         gpregs_getreturn32(&(self)->kcs_gpregs)
#define kcpustate_getreturn64(self)         gpregs_getreturn64(&(self)->kcs_gpregs)
#define kcpustate_setreturnbool(self, v)    gpregs_setreturnbool(&(self)->kcs_gpregs, v)
#define kcpustate_setreturn(self, v)        gpregs_setreturn(&(self)->kcs_gpregs, v)
#define kcpustate_setreturn32(self, v)      gpregs_setreturn32(&(self)->kcs_gpregs, v)
#define kcpustate_setreturn64(self, v)      gpregs_setreturn64(&(self)->kcs_gpregs, v)

#define icpustate_foreach_gpregs            icpustate64_foreach_gpregs
#define icpustate_isvm86(self)              0
#define icpustate_isuser_novm86             icpustate64_isuser
#define icpustate_isuser                    icpustate64_isuser
#define icpustate_iskernel                  icpustate64_iskernel
#define icpustate_is32bit                   icpustate64_is32bit
#define icpustate_is64bit                   icpustate64_is64bit
#define icpustate_isnative                  icpustate64_is64bit
#define icpustate_iscompat                  icpustate64_is32bit
#define icpustate_getpreemption             icpustate64_getpreemption
#define icpustate_setpreemption             icpustate64_setpreemption
#define icpustate_getpip                    icpustate64_getrip
#define icpustate_getpc                     (__byte_t const *)icpustate64_getrip
#define icpustate_setpip                    icpustate64_setrip
#define icpustate_setpc(self, pc)           icpustate64_setrip(self, (__u64)__COMPILER_REQTYPE(void const *, pc))
#define icpustate_getpsp                    icpustate64_getrsp
#define icpustate_getsp                     (__byte_t *)icpustate64_getrsp
#define icpustate_setpsp                    icpustate64_setrsp
#define icpustate_setsp(self, sp)           icpustate64_setrsp(self, (__u64)__COMPILER_REQTYPE(void const *, sp))
#define icpustate_trysetsp                  icpustate64_trysetrsp
#define icpustate_setpsp_p                  icpustate64_setrsp_p
#define icpustate_setsp_p(self, sp)         icpustate64_setrsp_p(self, (__u64)__COMPILER_REQTYPE(void const *, sp))
#define icpustate_getuserpsp                icpustate64_getuserrsp
#define icpustate_getusersp                 (__byte_t *)icpustate64_getuserrsp
#define icpustate_setuserpsp                icpustate64_setuserrsp
#define icpustate_setusersp(self, sp)       icpustate64_setuserrsp(self, (__u64)__COMPILER_REQTYPE(void const *, sp))
#define icpustate_getuserss                 icpustate64_getuserss
#define icpustate_setuserss                 icpustate64_setuserss
#define icpustate_getkernelss               icpustate64_getkernelss
#define icpustate_getkernelpsp              icpustate64_getkernelrsp
#define icpustate_getkernelsp               (__byte_t *)icpustate64_getkernelrsp
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
#define icpustate_to_ucpustate64_ex         icpustate64_to_ucpustate64_ex
#define icpustate64_to_ucpustate_ex         icpustate64_to_ucpustate64_ex
#define icpustate_to_ucpustate              icpustate64_to_ucpustate64
#define icpustate_to_ucpustate64            icpustate64_to_ucpustate64
#define icpustate64_to_ucpustate            icpustate64_to_ucpustate64
#define icpustate_user_to_ucpustate_ex      icpustate64_user_to_ucpustate64_ex
#define icpustate_user_to_ucpustate64_ex    icpustate64_user_to_ucpustate64_ex
#define icpustate64_user_to_ucpustate_ex    icpustate64_user_to_ucpustate64_ex
#define icpustate_user_to_ucpustate         icpustate64_user_to_ucpustate64
#define icpustate_user_to_ucpustate64       icpustate64_user_to_ucpustate64
#define icpustate64_user_to_ucpustate       icpustate64_user_to_ucpustate64
#define icpustate_to_kcpustate              icpustate64_to_kcpustate64
#define icpustate_to_kcpustate64            icpustate64_to_kcpustate64
#define icpustate64_to_kcpustate            icpustate64_to_kcpustate64
#define icpustate_user_to_kcpustate         icpustate64_user_to_kcpustate64
#define icpustate_user_to_kcpustate64       icpustate64_user_to_kcpustate64
#define icpustate64_user_to_kcpustate       icpustate64_user_to_kcpustate64
#define icpustate_to_scpustate_p_ex         icpustate64_to_scpustate64_p_ex
#define icpustate_to_scpustate64_p_ex       icpustate64_to_scpustate64_p_ex
#define icpustate64_to_scpustate_p_ex       icpustate64_to_scpustate64_p_ex
#define icpustate_to_scpustate_p            icpustate64_to_scpustate64_p
#define icpustate_to_scpustate64_p          icpustate64_to_scpustate64_p
#define icpustate64_to_scpustate_p          icpustate64_to_scpustate64_p
#define icpustate_to_icpustate_p            icpustate64_to_icpustate64_p
#define icpustate_to_icpustate64_p          icpustate64_to_icpustate64_p
#define icpustate64_to_icpustate_p          icpustate64_to_icpustate64_p
#define icpustate_user_to_scpustate_p_ex    icpustate64_user_to_scpustate64_p_ex
#define icpustate_user_to_scpustate64_p_ex  icpustate64_user_to_scpustate64_p_ex
#define icpustate64_user_to_scpustate_p_ex  icpustate64_user_to_scpustate64_p_ex
#define icpustate_user_to_scpustate_p       icpustate64_user_to_scpustate64_p
#define icpustate_user_to_scpustate64_p     icpustate64_user_to_scpustate64_p
#define icpustate64_user_to_scpustate_p     icpustate64_user_to_scpustate64_p
#define icpustate_user_to_icpustate_p       icpustate64_user_to_icpustate64_p
#define icpustate_user_to_icpustate64_p     icpustate64_user_to_icpustate64_p
#define icpustate64_user_to_icpustate_p     icpustate64_user_to_icpustate64_p
#define icpustate_getreturnbool(self)       gpregs_getreturnbool(&(self)->ics_gpregs)
#define icpustate_getreturn(self)           gpregs_getreturn(&(self)->ics_gpregs)
#define icpustate_getreturn32(self)         gpregs_getreturn32(&(self)->ics_gpregs)
#define icpustate_getreturn64(self)         gpregs_getreturn64(&(self)->ics_gpregs)
#define icpustate_setreturnbool(self, v)    gpregs_setreturnbool(&(self)->ics_gpregs, v)
#define icpustate_setreturn(self, v)        gpregs_setreturn(&(self)->ics_gpregs, v)
#define icpustate_setreturn32(self, v)      gpregs_setreturn32(&(self)->ics_gpregs, v)
#define icpustate_setreturn64(self, v)      gpregs_setreturn64(&(self)->ics_gpregs, v)

#define scpustate_foreach_gpregs            scpustate64_foreach_gpregs
#define scpustate_isvm86(self)              0
#define scpustate_isuser_novm86             scpustate64_isuser
#define scpustate_isuser                    scpustate64_isuser
#define scpustate_iskernel                  scpustate64_iskernel
#define scpustate_is32bit                   scpustate64_is32bit
#define scpustate_is64bit                   scpustate64_is64bit
#define scpustate_isnative                  scpustate64_is64bit
#define scpustate_iscompat                  scpustate64_is32bit
#define scpustate_getpreemption             scpustate64_getpreemption
#define scpustate_setpreemption             scpustate64_setpreemption
#define scpustate_getpip                    scpustate64_getrip
#define scpustate_getpc                     (__byte_t const *)scpustate64_getrip
#define scpustate_setpip                    scpustate64_setrip
#define scpustate_setpc(self, pc)           scpustate64_setrip(self, (__u64)__COMPILER_REQTYPE(void const *, pc))
#define scpustate_getpsp                    scpustate64_getrsp
#define scpustate_getsp                     (__byte_t *)scpustate64_getrsp
#define scpustate_setpsp                    scpustate64_setrsp
#define scpustate_setsp(self, sp)           scpustate64_setrsp(self, (__u64)__COMPILER_REQTYPE(void const *, sp))
#define scpustate_trysetpsp                 scpustate64_trysetrsp
#define scpustate_trysetsp(self, sp)        scpustate64_trysetrsp(self, (__u64)__COMPILER_REQTYPE(void const *, sp))
#define scpustate_setpsp_p                  scpustate64_setrsp_p
#define scpustate_setsp_p(self, sp)         scpustate64_setrsp_p(self, (__u64)__COMPILER_REQTYPE(void const *, sp))
#define scpustate_getuserpsp                scpustate64_getuserrsp
#define scpustate_getusersp                 (__byte_t *)scpustate64_getuserrsp
#define scpustate_setuserpsp                scpustate64_setuserrsp
#define scpustate_setusersp(self, sp)       scpustate64_setuserrsp(self, (__u64)__COMPILER_REQTYPE(void const *, sp))
#define scpustate_getuserss                 scpustate64_getuserss
#define scpustate_setuserss                 scpustate64_setuserss
#define scpustate_getkernelss               scpustate64_getkernelss
#define scpustate_getkernelpsp              scpustate64_getkernelrsp
#define scpustate_getkernelsp               (__byte_t *)scpustate64_getkernelrsp
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
#define scpustate_to_ucpustate64            scpustate64_to_ucpustate64
#define scpustate64_to_ucpustate            scpustate64_to_ucpustate64
#define scpustate_user_to_ucpustate         scpustate64_user_to_ucpustate64
#define scpustate_user_to_ucpustate64       scpustate64_user_to_ucpustate64
#define scpustate64_user_to_ucpustate       scpustate64_user_to_ucpustate64
#define scpustate_to_kcpustate              scpustate64_to_kcpustate64
#define scpustate_to_kcpustate64            scpustate64_to_kcpustate64
#define scpustate64_to_kcpustate            scpustate64_to_kcpustate64
#define scpustate_user_to_kcpustate         scpustate64_user_to_kcpustate64
#define scpustate_user_to_kcpustate64       scpustate64_user_to_kcpustate64
#define scpustate64_user_to_kcpustate       scpustate64_user_to_kcpustate64
#define scpustate_to_icpustate_p            scpustate64_to_icpustate64_p
#define scpustate_to_icpustate64_p          scpustate64_to_icpustate64_p
#define scpustate64_to_icpustate_p          scpustate64_to_icpustate64_p
#define scpustate_user_to_icpustate_p       scpustate64_user_to_icpustate64_p
#define scpustate_user_to_icpustate64_p     scpustate64_user_to_icpustate64_p
#define scpustate64_user_to_icpustate_p     scpustate64_user_to_icpustate64_p
#define scpustate_to_scpustate_p            scpustate64_to_scpustate64_p
#define scpustate_to_scpustate64_p          scpustate64_to_scpustate64_p
#define scpustate64_to_scpustate_p          scpustate64_to_scpustate64_p
#define scpustate_user_to_scpustate_p       scpustate64_user_to_scpustate64_p
#define scpustate_user_to_scpustate64_p     scpustate64_user_to_scpustate64_p
#define scpustate64_user_to_scpustate_p     scpustate64_user_to_scpustate64_p
#define scpustate_getreturnbool(self)       gpregs_getreturnbool(&(self)->scs_gpregs)
#define scpustate_getreturn(self)           gpregs_getreturn(&(self)->scs_gpregs)
#define scpustate_getreturn32(self)         gpregs_getreturn32(&(self)->scs_gpregs)
#define scpustate_getreturn64(self)         gpregs_getreturn64(&(self)->scs_gpregs)
#define scpustate_setreturnbool(self, v)    gpregs_setreturnbool(&(self)->scs_gpregs, v)
#define scpustate_setreturn(self, v)        gpregs_setreturn(&(self)->scs_gpregs, v)
#define scpustate_setreturn32(self, v)      gpregs_setreturn32(&(self)->scs_gpregs, v)
#define scpustate_setreturn64(self, v)      gpregs_setreturn64(&(self)->scs_gpregs, v)

#define ucpustate_foreach_gpregs            ucpustate64_foreach_gpregs
#define ucpustate_isvm86(self)              0
#define ucpustate_isuser_novm86             ucpustate64_isuser
#define ucpustate_isuser                    ucpustate64_isuser
#define ucpustate_iskernel                  ucpustate64_iskernel
#define ucpustate_is32bit                   ucpustate64_is32bit
#define ucpustate_is64bit                   ucpustate64_is64bit
#define ucpustate_isnative                  ucpustate64_is64bit
#define ucpustate_iscompat                  ucpustate64_is32bit
#define ucpustate_getpip                    ucpustate64_getrip
#define ucpustate_getpc                     (__byte_t const *)ucpustate64_getrip
#define ucpustate_setpip                    ucpustate64_setrip
#define ucpustate_setpc(self, pc)           ucpustate64_setrip(self, (__u64)__COMPILER_REQTYPE(void const *, pc))
#define ucpustate_getpsp                    ucpustate64_getrsp
#define ucpustate_getsp                     (__byte_t *)ucpustate64_getrsp
#define ucpustate_setpsp                    ucpustate64_setrsp
#define ucpustate_setsp(self, sp)           ucpustate64_setrsp(self, (__u64)__COMPILER_REQTYPE(void const *, sp))
#define ucpustate_getpflags                 ucpustate64_getrflags
#define ucpustate_setpflags                 ucpustate64_setrflags
#define ucpustate_mskpflags                 ucpustate64_mskrflags
#define ucpustate_getes                     ucpustate64_getes
#define ucpustate_setes                     ucpustate64_setes
#define ucpustate_getds                     ucpustate64_getds
#define ucpustate_setds                     ucpustate64_setds
#define ucpustate_getss                     ucpustate64_getss
#define ucpustate_setss                     ucpustate64_setss
#define ucpustate_getcs                     ucpustate64_getcs
#define ucpustate_setcs                     ucpustate64_setcs
#define ucpustate_getfs                     ucpustate64_getfs
#define ucpustate_setfs                     ucpustate64_setfs
#define ucpustate_getgs                     ucpustate64_getgs
#define ucpustate_setgs                     ucpustate64_setgs
#define ucpustate_current                   ucpustate64_current
#define ucpustate_to_ucpustate              ucpustate64_to_ucpustate64
#define ucpustate_to_ucpustate64            ucpustate64_to_ucpustate64
#define ucpustate64_to_ucpustate            ucpustate64_to_ucpustate64
#define ucpustate_to_kcpustate              ucpustate64_to_kcpustate64
#define ucpustate_to_kcpustate64            ucpustate64_to_kcpustate64
#define ucpustate64_to_kcpustate            ucpustate64_to_kcpustate64
#define ucpustate_to_icpustate_p            ucpustate64_to_icpustate64_p
#define ucpustate_to_icpustate64_p          ucpustate64_to_icpustate64_p
#define ucpustate64_to_icpustate_p          ucpustate64_to_icpustate64_p
#define ucpustate_to_scpustate_p            ucpustate64_to_scpustate64_p
#define ucpustate_to_scpustate64_p          ucpustate64_to_scpustate64_p
#define ucpustate64_to_scpustate_p          ucpustate64_to_scpustate64_p
#define ucpustate_getreturnbool(self)       gpregs_getreturnbool(&(self)->ucs_gpregs)
#define ucpustate_getreturn(self)           gpregs_getreturn(&(self)->ucs_gpregs)
#define ucpustate_getreturn32(self)         gpregs_getreturn32(&(self)->ucs_gpregs)
#define ucpustate_getreturn64(self)         gpregs_getreturn64(&(self)->ucs_gpregs)
#define ucpustate_setreturnbool(self, v)    gpregs_setreturnbool(&(self)->ucs_gpregs, v)
#define ucpustate_setreturn(self, v)        gpregs_setreturn(&(self)->ucs_gpregs, v)
#define ucpustate_setreturn32(self, v)      gpregs_setreturn32(&(self)->ucs_gpregs, v)
#define ucpustate_setreturn64(self, v)      gpregs_setreturn64(&(self)->ucs_gpregs, v)

#define fcpustate_foreach_gpregs            fcpustate64_foreach_gpregs
#define fcpustate_isvm86(self)              0
#define fcpustate_isuser_novm86             fcpustate64_isuser
#define fcpustate_isuser                    fcpustate64_isuser
#define fcpustate_iskernel                  fcpustate64_iskernel
#define fcpustate_is32bit                   fcpustate64_is32bit
#define fcpustate_is64bit                   fcpustate64_is64bit
#define fcpustate_isnative                  fcpustate64_is64bit
#define fcpustate_iscompat                  fcpustate64_is32bit
#define fcpustate_getpip                    fcpustate64_getrip
#define fcpustate_getpc                     (__byte_t const *)fcpustate64_getrip
#define fcpustate_setpip                    fcpustate64_setrip
#define fcpustate_setpc(self, pc)           fcpustate64_setrip(self, (__u64)__COMPILER_REQTYPE(void const *, pc))
#define fcpustate_getpsp                    fcpustate64_getrsp
#define fcpustate_getsp                     (__byte_t *)fcpustate64_getrsp
#define fcpustate_setpsp                    fcpustate64_setrsp
#define fcpustate_setsp(self, sp)           fcpustate64_setrsp(self, (__u64)__COMPILER_REQTYPE(void const *, sp))
#define fcpustate_getpflags                 fcpustate64_getrflags
#define fcpustate_setpflags                 fcpustate64_setrflags
#define fcpustate_mskpflags                 fcpustate64_mskrflags
#define fcpustate_to_fcpustate              fcpustate64_to_fcpustate64
#define fcpustate_to_fcpustate64            fcpustate64_to_fcpustate64
#define fcpustate64_to_fcpustate            fcpustate64_to_fcpustate64
#define fcpustate_to_lcpustate              fcpustate64_to_lcpustate64
#define fcpustate_to_lcpustate64            fcpustate64_to_lcpustate64
#define fcpustate64_to_lcpustate            fcpustate64_to_lcpustate64
#define fcpustate_to_kcpustate              fcpustate64_to_kcpustate64
#define fcpustate_to_kcpustate64            fcpustate64_to_kcpustate64
#define fcpustate64_to_kcpustate            fcpustate64_to_kcpustate64
#define fcpustate_to_ucpustate              fcpustate64_to_ucpustate64
#define fcpustate_to_ucpustate64            fcpustate64_to_ucpustate64
#define fcpustate64_to_ucpustate            fcpustate64_to_ucpustate64
#define fcpustate_assign_ucpustate          fcpustate64_assign_ucpustate64
#define fcpustate_assign_ucpustate64        fcpustate64_assign_ucpustate64
#define fcpustate64_assign_ucpustate        fcpustate64_assign_ucpustate64
#define fcpustate_assign_lcpustate          fcpustate64_assign_lcpustate64
#define fcpustate_assign_lcpustate64        fcpustate64_assign_lcpustate64
#define fcpustate64_assign_lcpustate        fcpustate64_assign_lcpustate64
#define fcpustate_assign_kcpustate          fcpustate64_assign_kcpustate64
#define fcpustate_assign_kcpustate64        fcpustate64_assign_kcpustate64
#define fcpustate64_assign_kcpustate        fcpustate64_assign_kcpustate64
#define fcpustate_assign_scpustate          fcpustate64_assign_scpustate64
#define fcpustate_assign_scpustate64        fcpustate64_assign_scpustate64
#define fcpustate64_assign_scpustate        fcpustate64_assign_scpustate64
#define fcpustate_assign_icpustate_ex       fcpustate64_assign_icpustate64_ex
#define fcpustate_assign_icpustate64_ex     fcpustate64_assign_icpustate64_ex
#define fcpustate64_assign_icpustate_ex     fcpustate64_assign_icpustate64_ex
#define fcpustate_assign_icpustate          fcpustate64_assign_icpustate64
#define fcpustate_assign_icpustate64        fcpustate64_assign_icpustate64
#define fcpustate64_assign_icpustate        fcpustate64_assign_icpustate64
#define fcpustate_to_icpustate_p            fcpustate64_to_icpustate64_p
#define fcpustate_to_icpustate64_p          fcpustate64_to_icpustate64_p
#define fcpustate64_to_icpustate_p          fcpustate64_to_icpustate64_p
#define fcpustate_to_scpustate_p            fcpustate64_to_scpustate64_p
#define fcpustate_to_scpustate64_p          fcpustate64_to_scpustate64_p
#define fcpustate64_to_scpustate_p          fcpustate64_to_scpustate64_p
#define fcpustate_getreturnbool(self)       gpregs_getreturnbool(&(self)->fcs_gpregs)
#define fcpustate_getreturn(self)           gpregs_getreturn(&(self)->fcs_gpregs)
#define fcpustate_getreturn32(self)         gpregs_getreturn32(&(self)->fcs_gpregs)
#define fcpustate_getreturn64(self)         gpregs_getreturn64(&(self)->fcs_gpregs)
#define fcpustate_setreturnbool(self, v)    gpregs_setreturnbool(&(self)->fcs_gpregs, v)
#define fcpustate_setreturn(self, v)        gpregs_setreturn(&(self)->fcs_gpregs, v)
#define fcpustate_setreturn32(self, v)      gpregs_setreturn32(&(self)->fcs_gpregs, v)
#define fcpustate_setreturn64(self, v)      gpregs_setreturn64(&(self)->fcs_gpregs, v)

#endif /* __x86_64__ */

__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_KOS_KERNEL_CPU_STATE_HELPERS64_H */
