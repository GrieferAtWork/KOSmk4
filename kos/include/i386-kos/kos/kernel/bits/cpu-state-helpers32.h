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
#ifndef _I386_KOS_KOS_KERNEL_BITS_CPU_STATE_HELPERS32_H
#define _I386_KOS_KOS_KERNEL_BITS_CPU_STATE_HELPERS32_H 1

#include <hybrid/__assert.h>
#include <hybrid/host.h>

#include <asm/intrin.h>
#include <asm/isa.h>
#include <bits/types.h>
#include <kos/anno.h>

#include <libc/string.h>

#include "../x86/gdt.h"
#include "cpu-state32.h"

#if defined(__KERNEL__) && !defined(__x86_64__)
#include <sched/arch/task.h>
#endif /* __KERNEL__ && !__x86_64__ */

#if defined(__i386__) && !defined(__x86_64__)
#include <hybrid/__asm.h>
#endif /* __i386__ && !__x86_64 */

#ifdef __CC__
__DECL_BEGIN

/************************************************************************/
/* `struct gpregs32'                                                    */
/************************************************************************/
#define gpregs32_foreach_elem(self) \
	((__UINT32_TYPE__ const *)__COMPILER_REQTYPE(struct gpregs32 const *, self))
#define gpregs32_foreach_size(self) 8
#define gpregs32_foreach(self, cb)                                 \
	do {                                                           \
		unsigned int __gpregs32_foreach_i;                         \
		for (__gpregs32_foreach_i = 0;                             \
		     __gpregs32_foreach_i < gpregs32_foreach_size(self);   \
		     ++__gpregs32_foreach_i) {                             \
			cb(gpregs32_foreach_elem(self)[__gpregs32_foreach_i]); \
		}                                                          \
	}	__WHILE0
#define gpregs32_getedi(self)        ((__u32)(self)->gp_edi)
#define gpregs32_setedi(self, value) ((self)->gp_edi = (value))
#define gpregs32_getesi(self)        ((__u32)(self)->gp_esi)
#define gpregs32_setesi(self, value) ((self)->gp_esi = (value))
#define gpregs32_getebp(self)        ((__u32)(self)->gp_ebp)
#define gpregs32_setebp(self, value) ((self)->gp_ebp = (value))
#define gpregs32_getesp(self)        ((__u32)(self)->gp_esp)
#define gpregs32_setesp(self, value) ((self)->gp_esp = (value))
#define gpregs32_getebx(self)        ((__u32)(self)->gp_ebx)
#define gpregs32_setebx(self, value) ((self)->gp_ebx = (value))
#define gpregs32_getedx(self)        ((__u32)(self)->gp_edx)
#define gpregs32_setedx(self, value) ((self)->gp_edx = (value))
#define gpregs32_getecx(self)        ((__u32)(self)->gp_ecx)
#define gpregs32_setecx(self, value) ((self)->gp_ecx = (value))
#define gpregs32_geteax(self)        ((__u32)(self)->gp_eax)
#define gpregs32_seteax(self, value) ((self)->gp_eax = (value))
#define gpregs32_to_gpregs32(self, result)                           \
	__libc_memcpy(__COMPILER_REQTYPE(struct gpregs32 *, result),     \
	              __COMPILER_REQTYPE(struct gpregs32 const *, self), \
	              sizeof(struct gpregs32))
/* Get/set return registers. */
#define gpregs32_getreturn32              gpregs32_geteax
#define gpregs32_getreturn64(self)        ((__u64)gpregs32_geteax(self) | ((__u64)gpregs32_getedx(self) << 32))
#define gpregs32_setreturn32              gpregs32_seteax
#define gpregs32_setreturn64(self, value) (gpregs32_seteax(self, (__u32)(value)), gpregs32_setedx(self, (__u32)((value) >> 32)))
/************************************************************************/




/************************************************************************/
/* `struct irregs32'                                                    */
/************************************************************************/
#if defined(__KERNEL__) && !defined(__x86_64__)
#ifdef __I386_NO_VM86
#define irregs32_isvm86(self)            0
#define irregs32_isuser(self)            (irregs_isuser)((struct irregs_kernel const *)&(self)->ir_eip)
#define irregs32_isuser_novm86(self)     (irregs_isuser)((struct irregs_kernel const *)&(self)->ir_eip)
#define irregs32_getisa(self)            ISA_I386
#else /* __I386_NO_VM86 */
#define irregs32_isvm86(self)            (irregs_isvm86)((struct irregs_kernel const *)&(self)->ir_eip)
#define irregs32_isuser(self)            (irregs_isuser)((struct irregs_kernel const *)&(self)->ir_eip)
#define irregs32_isuser_novm86(self)     (irregs_isuser_novm86)((struct irregs_kernel const *)&(self)->ir_eip)
#define irregs32_getisa(self)            (irregs32_isvm86(self) ? ISA_8086 : ISA_I386)
#endif /* !__I386_NO_VM86 */
#define irregs32_iskernel(self)          (!(irregs_isuser)((struct irregs_kernel const *)&(self)->ir_eip))
#define irregs32_geteip(self)            (irregs_rdip)((struct irregs_kernel const *)&(self)->ir_eip)
#define irregs32_seteip(self, value)     (irregs_wrip)((struct irregs_kernel *)&(self)->ir_eip, value)
#define irregs32_getcs(self)             (irregs_rdcs)((struct irregs_kernel const *)&(self)->ir_eip)
#define irregs32_setcs(self, value)      (irregs_wrcs)((struct irregs_kernel *)&(self)->ir_eip, value)
#define irregs32_geteflags(self)         (irregs_rdflags)((struct irregs_kernel const *)&(self)->ir_eip)
#define irregs32_seteflags(self, value)  (irregs_wrflags)((struct irregs_kernel *)&(self)->ir_eip, value)
#define irregs32_mskeflags(self, mask, flags) (irregs_mskflags)((struct irregs_kernel *)&(self)->ir_eip, mask, flags)
#define irregs32_getesp(self)            (irregs_rdsp)((struct irregs_kernel const *)&(self)->ir_eip)
#else /* __KERNEL__ && !__x86_64__ */
#ifdef __I386_NO_VM86
#define irregs32_isvm86(self)            0
#define irregs32_isuser_novm86(self)     ((self)->ir_cs16 & 3)
#define irregs32_isuser(self)            ((self)->ir_cs16 & 3)
#define irregs32_iskernel(self)          (!((self)->ir_cs16 & 3))
#define irregs32_getisa(self)            ISA_I386
#else /* __I386_NO_VM86 */
#define irregs32_isvm86(self)            ((self)->ir_eflags & 0x20000)
#define irregs32_isuser_novm86(self)     ((self)->ir_cs16 & 3)
#define irregs32_isuser(self)            (((self)->ir_cs16 & 3) || irregs32_isvm86(self))
#define irregs32_iskernel(self)          (!((self)->ir_cs16 & 3) && !irregs32_isvm86(self))
#define irregs32_getisa(self)            (irregs32_isvm86(self) ? ISA_8086 : ISA_I386)
#endif /* !__I386_NO_VM86 */
#define irregs32_geteip(self)            ((__u32)(self)->ir_eip)
#define irregs32_seteip(self, value)     ((self)->ir_eip = (value))
#define irregs32_getcs(self)             ((__u16)(self)->ir_cs16)
#define irregs32_setcs(self, value)      ((self)->ir_cs = (value))
#define irregs32_geteflags(self)         ((__u32)(self)->ir_eflags)
#define irregs32_seteflags(self, value)  ((self)->ir_eflags = (value))
#define irregs32_mskeflags(self, mask, flags) ((self)->ir_eflags = ((self)->ir_eflags & (mask)) | (flags))
#define irregs32_getesp(self)            (irregs32_isuser(self) ? irregs32_getuseresp(self) : irregs32_getkernelesp(self))
#endif /* !__KERNEL__ || __x86_64__ */
#define irregs32_getpreemption(self)     (irregs32_geteflags(self) & 0x200)
#define irregs32_setpreemption(self, turn_on) irregs32_mskeflags(self, ~0x200, (turn_on) ? 0x200 : 0)
#define irregs32_getuseresp(self)        ((struct irregs32_user const *)(self))->ir_esp
#define irregs32_setuseresp(self, value) (((struct irregs32_user *)(self))->ir_esp=(value))
#define irregs32_getuserss(self)         ((struct irregs32_user const *)(self))->ir_ss16
#define irregs32_setuserss(self, value)  (((struct irregs32_user *)(self))->ir_ss=(value))
#define irregs32_getkernelesp(self)      ((__uintptr_t)(self) + SIZEOF_IRREGS32_KERNEL)
#define irregs32_getkernelss(self)       SEGMENT_KERNEL_DATA
#define irregs32_getss(self)             (irregs32_isuser(self) ? irregs32_getuserss(self) : irregs32_getkernelss(self))
#define irregs32_trysetesp(self, value)  (irregs32_isuser(self) ? (irregs32_setuseresp(self, value), 1) : (irregs32_getkernelesp(self) == (value)))
#define irregs32_trysetss(self, value)   (irregs32_isuser(self) ? (irregs32_setuserss(self, value), 1) : (irregs32_getkernelss(self) == (value)))
#define irregs32_trysetuserss(self, value) (irregs32_isuser(self) ? (irregs32_setuserss(self, value), 1) : 0)
#ifndef __I386_NO_VM86
#define irregs32_getvm86ds(self)        ((struct irregs32_vm86 const *)(self))->ir_ds16
#define irregs32_setvm86ds(self, value) (((struct irregs32_vm86 *)(self))->ir_ds16=(value))
#define irregs32_getvm86es(self)        ((struct irregs32_vm86 const *)(self))->ir_es16
#define irregs32_setvm86es(self, value) (((struct irregs32_vm86 *)(self))->ir_es16=(value))
#define irregs32_getvm86fs(self)        ((struct irregs32_vm86 const *)(self))->ir_fs16
#define irregs32_setvm86fs(self, value) (((struct irregs32_vm86 *)(self))->ir_fs16=(value))
#define irregs32_getvm86gs(self)        ((struct irregs32_vm86 const *)(self))->ir_gs16
#define irregs32_setvm86gs(self, value) (((struct irregs32_vm86 *)(self))->ir_gs16=(value))
#define irregs32_getds_ex(self, v_nonvm86_ds)           (irregs32_isvm86(self) ? irregs32_getvm86ds(self) : (v_nonvm86_ds))
#define irregs32_trysetds_ex(self, value, v_nonvm86_ds) (irregs32_isvm86(self) ? (irregs32_setvm86ds(self, value), 1) : ((v_nonvm86_ds) == (value)))
#define irregs32_getes_ex(self, v_nonvm86_es)           (irregs32_isvm86(self) ? irregs32_getvm86es(self) : (v_nonvm86_es))
#define irregs32_trysetes_ex(self, value, v_nonvm86_es) (irregs32_isvm86(self) ? (irregs32_setvm86es(self, value), 1) : ((v_nonvm86_es) == (value)))
#define irregs32_getfs_ex(self, v_nonvm86_fs)           (irregs32_isvm86(self) ? irregs32_getvm86fs(self) : (v_nonvm86_fs))
#define irregs32_trysetfs_ex(self, value, v_nonvm86_fs) (irregs32_isvm86(self) ? (irregs32_setvm86fs(self, value), 1) : ((v_nonvm86_fs) == (value)))
#define irregs32_getgs_ex(self, v_nonvm86_gs)           (irregs32_isvm86(self) ? irregs32_getvm86gs(self) : (v_nonvm86_gs))
#define irregs32_trysetgs_ex(self, value, v_nonvm86_gs) (irregs32_isvm86(self) ? (irregs32_setvm86gs(self, value), 1) : ((v_nonvm86_gs) == (value)))
#else /* !__I386_NO_VM86 */
#define irregs32_getds_ex(self, v_nonvm86_ds)           (v_nonvm86_ds)
#define irregs32_trysetds_ex(self, value, v_nonvm86_ds) ((v_nonvm86_ds) == (value))
#define irregs32_getes_ex(self, v_nonvm86_es)           (v_nonvm86_es)
#define irregs32_trysetes_ex(self, value, v_nonvm86_es) ((v_nonvm86_es) == (value))
#define irregs32_getfs_ex(self, v_nonvm86_fs)           (v_nonvm86_fs)
#define irregs32_trysetfs_ex(self, value, v_nonvm86_fs) ((v_nonvm86_fs) == (value))
#define irregs32_getgs_ex(self, v_nonvm86_gs)           (v_nonvm86_gs)
#define irregs32_trysetgs_ex(self, value, v_nonvm86_gs) ((v_nonvm86_gs) == (value))
#endif /* __I386_NO_VM86 */
#if defined(__KERNEL__) && !defined(__x86_64__)
#define irregs32_getds(self)           irregs32_getds_ex(self, SEGMENT_USER_DATA_RPL)
#define irregs32_trysetds(self, value) irregs32_trysetds_ex(self, value, SEGMENT_USER_DATA_RPL)
#define irregs32_getes(self)           irregs32_getes_ex(self, SEGMENT_USER_DATA_RPL)
#define irregs32_trysetes(self, value) irregs32_trysetes_ex(self, value, SEGMENT_USER_DATA_RPL)
#define irregs32_getfs(self)           irregs32_getfs_ex(self, SEGMENT_KERNEL_FSBASE)
#define irregs32_trysetfs(self, value) irregs32_trysetfs_ex(self, value, SEGMENT_KERNEL_FSBASE)
#else /* __KERNEL__ && !__x86_64__ */
#define irregs32_getds(self)           irregs32_getds_ex(self, __rdds())
#define irregs32_trysetds(self, value) irregs32_trysetds_ex(self, value, __rdds())
#define irregs32_getes(self)           irregs32_getes_ex(self, __rdes())
#define irregs32_trysetes(self, value) irregs32_trysetes_ex(self, value, __rdes())
#define irregs32_getfs(self)           irregs32_getfs_ex(self, __rdfs())
#define irregs32_trysetfs(self, value) irregs32_trysetfs_ex(self, value, __rdfs())
#endif /* !__KERNEL__ || __x86_64__ */
#define irregs32_getgs(self)           irregs32_getgs_ex(self, __rdgs())
#define irregs32_trysetgs(self, value) irregs32_trysetgs_ex(self, value, __rdgs())

/* Returns the total size of the given CPU state. */
#ifdef __I386_NO_VM86
#define irregs32_sizeof(self) \
	(((self)->ir_cs16 & 3)    \
	 ? SIZEOF_IRREGS32_USER   \
	 : SIZEOF_IRREGS32_KERNEL)
#else /* __I386_NO_VM86 */
#define irregs32_sizeof(self) \
	(irregs32_isvm86(self)    \
	 ? SIZEOF_IRREGS32_VM86   \
	 : ((self)->ir_cs16 & 3)  \
	   ? SIZEOF_IRREGS32_USER \
	   : SIZEOF_IRREGS32_KERNEL)
#endif /* !__I386_NO_VM86 */
/************************************************************************/




/************************************************************************/
/* `struct lcpustate32'                                                 */
/************************************************************************/
#define lcpustate32_foreach_gpregs_elem(self) \
	((__UINT32_TYPE__ const *)__COMPILER_REQTYPE(struct lcpustate32 const *, self))
#define lcpustate32_foreach_gpregs_size(self) 6
#define lcpustate32_foreach_gpregs(self, cb)                                    \
	do {                                                                        \
		unsigned int __lcpustate32_foreach_i;                                   \
		for (__lcpustate32_foreach_i = 0;                                       \
		     __lcpustate32_foreach_i < lcpustate32_foreach_gpregs_size(self);   \
		     ++__lcpustate32_foreach_i) {                                       \
			cb(lcpustate32_foreach_gpregs_elem(self)[__lcpustate32_foreach_i]); \
		}                                                                       \
	}	__WHILE0
#define lcpustate32_geteip(self)        ((__u32)(self)->lcs_eip)
#define lcpustate32_seteip(self, value) ((self)->lcs_eip = (value))
#define lcpustate32_getesp(self)        ((__u32)(self)->lcs_esp)
#define lcpustate32_setesp(self, value) ((self)->lcs_esp = (value))
#define lcpustate32_to_lcpustate32(self, result)                        \
	__libc_memcpy(__COMPILER_REQTYPE(struct lcpustate32 *, result),     \
	              __COMPILER_REQTYPE(struct lcpustate32 const *, self), \
	              sizeof(struct lcpustate32))
#ifndef __x86_64__
__FORCELOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(lcpustate32_current)(struct lcpustate32 *__restrict __result) {
	__asm__ __volatile__("movl %%edi, 0(%1)\n\t"
	                     "movl %%esi, 4(%1)\n\t"
	                     "movl %%ebp, 8(%1)\n\t"
	                     "movl %%esp, 12(%1)\n\t"
	                     "movl %%ebx, 16(%1)\n\t"
#ifdef __pic__
	                     "call 991f\n\t"
	                     "991: .cfi_adjust_cfa_offset 4\n\t"
	                     "popl 20(%1)\n\t"
	                     ".cfi_adjust_cfa_offset -4"
#else  /* __pic__ */
	                     "movl $991f, 20(%1)\n\t"
	                     "991:"
#endif /* !__pic__ */
	                     : "=m" /*0*/ (*__result)
	                     : "r" /*1*/ (__result));
}
#endif /* !__x86_64__ */
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(lcpustate32_to_gpregs32_ex)(struct lcpustate32 const *__restrict __self,
                                          struct gpregs32 *__restrict __result,
                                          __u32 __v_edx, __u32 __v_ecx, __u32 __v_eax) {
	__result->gp_edi = __self->lcs_edi;
	__result->gp_esi = __self->lcs_esi;
	__result->gp_ebp = __self->lcs_ebp;
	__result->gp_esp = __self->lcs_esp;
	__result->gp_ebx = __self->lcs_ebx;
	__result->gp_edx = __v_edx;
	__result->gp_ecx = __v_ecx;
	__result->gp_eax = __v_eax;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(lcpustate32_to_gpregs32)(struct lcpustate32 const *__restrict __self,
                                       struct gpregs32 *__restrict __result) {
	lcpustate32_to_gpregs32_ex(__self, __result, 0, 0, 0);
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(lcpustate32_to_ucpustate32_ex)(struct lcpustate32 const *__restrict __self,
                                             struct ucpustate32 *__restrict __result,
                                             __u32 __v_edx, __u32 __v_ecx, __u32 __v_eax,
                                             __u16 __v_gs, __u16 __v_fs, __u16 __v_es, __u16 __v_ds,
                                             __u16 __v_cs, __u16 __v_ss, __u32 __v_eflags) {
	lcpustate32_to_gpregs32_ex(__self, &__result->ucs_gpregs, __v_edx, __v_ecx, __v_eax);
	__result->ucs_sgregs.sg_gs  = __v_gs;
	__result->ucs_sgregs.sg_fs  = __v_fs;
	__result->ucs_sgregs.sg_es  = __v_es;
	__result->ucs_sgregs.sg_ds  = __v_ds;
	__result->ucs_cs            = __v_cs;
	__result->ucs_ss            = __v_ss;
	__result->ucs_eflags        = __v_eflags;
	__result->ucs_eip           = __self->lcs_eip;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(lcpustate32_to_ucpustate32)(struct lcpustate32 const *__restrict __self,
                                          struct ucpustate32 *__restrict __result) {
	lcpustate32_to_ucpustate32_ex(__self, __result, 0, 0, 0,
	                              __rdgs(),
#if defined(__KERNEL__) && !defined(__x86_64__)
	                              SEGMENT_KERNEL_FSBASE,
	                              SEGMENT_USER_DATA_RPL,
	                              SEGMENT_USER_DATA_RPL,
#else /* __KERNEL__ && !__x86_64__ */
	                              __rdfs(), __rdes(), __rdds(),
#endif /* !__KERNEL__ || __x86_64__ */
	                              SEGMENT_CURRENT_CODE_RPL,
	                              SEGMENT_CURRENT_DATA_RPL,
	                              (__u32)__rdflags());
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(lcpustate32_to_kcpustate32_ex)(struct lcpustate32 const *__restrict __self,
                                             struct kcpustate32 *__restrict __result,
                                             __u32 __v_edx, __u32 __v_ecx, __u32 __v_eax,
                                             __u32 __v_eflags) {
	lcpustate32_to_gpregs32_ex(__self, &__result->kcs_gpregs, __v_edx, __v_ecx, __v_eax);
	__result->kcs_eflags = __v_eflags;
	__result->kcs_eip    = __self->lcs_eip;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(lcpustate32_to_kcpustate32)(struct lcpustate32 const *__restrict __self,
                                          struct kcpustate32 *__restrict __result) {
	lcpustate32_to_kcpustate32_ex(__self, __result, 0, 0, 0, (__u32)__rdflags());
}
/************************************************************************/




/************************************************************************/
/* `struct kcpustate32'                                                 */
/************************************************************************/
#define kcpustate32_foreach_gpregs_elem(self)   gpregs32_foreach_elem(&(self)->kcs_gpregs)
#define kcpustate32_foreach_gpregs_size(self)   gpregs32_foreach_size(&(self)->kcs_gpregs)
#define kcpustate32_foreach_gpregs(self, cb)    gpregs32_foreach(&(self)->kcs_gpregs, cb)
#define kcpustate32_geteip(self)                ((__u32)(self)->kcs_eip)
#define kcpustate32_seteip(self, value)         ((self)->kcs_eip = (value))
#define kcpustate32_getesp(self)                ((__u32)(self)->kcs_gpregs.gp_esp)
#define kcpustate32_setesp(self, value)         ((self)->kcs_gpregs.gp_esp = (value))
#define kcpustate32_geteflags(self)             ((__u32)(self)->kcs_eflags)
#define kcpustate32_seteflags(self, value)      ((self)->kcs_eflags = (value))
#define kcpustate32_mskeflags(self, mask, flag) ((self)->kcs_eflags = ((self)->kcs_eflags & (mask)) | (flag))
#define kcpustate32_to_kcpustate32(self, result)                        \
	__libc_memcpy(__COMPILER_REQTYPE(struct kcpustate32 *, result),     \
	              __COMPILER_REQTYPE(struct kcpustate32 const *, self), \
	              sizeof(struct kcpustate32))
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(kcpustate32_to_ucpustate32_ex)(struct kcpustate32 const *__restrict __self,
                                             struct ucpustate32 *__restrict __result,
                                             __u16 __v_gs, __u16 __v_fs, __u16 __v_es,
                                             __u16 __v_ds, __u16 __v_cs, __u16 __v_ss) {
	__libc_memcpy(&__result->ucs_gpregs,
	              &__self->kcs_gpregs,
	              sizeof(struct gpregs32));
	__result->ucs_sgregs.sg_gs = __v_gs;
	__result->ucs_sgregs.sg_fs = __v_fs;
	__result->ucs_sgregs.sg_es = __v_es;
	__result->ucs_sgregs.sg_ds = __v_ds;
	__result->ucs_cs           = __v_cs;
	__result->ucs_ss           = __v_ss;
	__result->ucs_eflags       = __self->kcs_eflags;
	__result->ucs_eip          = __self->kcs_eip;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(kcpustate32_to_ucpustate32)(struct kcpustate32 const *__restrict __self,
                                          struct ucpustate32 *__restrict __result) {
	kcpustate32_to_ucpustate32_ex(__self, __result,
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
__NOTHROW_NCX(kcpustate32_to_lcpustate32)(struct kcpustate32 const *__restrict __self,
                                          struct lcpustate32 *__restrict __result) {
	__result->lcs_edi = __self->kcs_gpregs.gp_edi;
	__result->lcs_esi = __self->kcs_gpregs.gp_esi;
	__result->lcs_ebp = __self->kcs_gpregs.gp_ebp;
	__result->lcs_esp = __self->kcs_gpregs.gp_esp;
	__result->lcs_ebx = __self->kcs_gpregs.gp_ebx;
	__result->lcs_eip = __self->kcs_eip;
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct scpustate32 *
__NOTHROW_NCX(kcpustate32_to_scpustate32_p_ex)(struct kcpustate32 const *__restrict __self,
                                               void *__restrict __kernel_esp,
                                               __u16 __v_gs, __u16 __v_fs, __u16 __v_es,
                                               __u16 __v_ds, __u16 __v_cs, __u16 __v_ss) {
	struct scpustate32 *__result;
#ifndef __I386_NO_VM86
	if (__self->kcs_eflags & 0x20000) {
		__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
		                                  (OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_VM86));
		__result->scs_irregs_v.ir_esp = __self->kcs_gpregs.gp_esp;
		__result->scs_irregs_v.ir_ss  = __v_ss;
		__result->scs_irregs_v.ir_es  = __v_es;
		__result->scs_irregs_v.ir_ds  = __v_ds;
		__result->scs_irregs_v.ir_fs  = __v_fs;
		__result->scs_irregs_v.ir_gs  = __v_gs;
		__result->scs_sgregs.sg_ds = SEGMENT_USER_DATA_RPL;
		__result->scs_sgregs.sg_es = SEGMENT_USER_DATA_RPL;
#ifdef __x86_64__
		__result->scs_sgregs.sg_fs = SEGMENT_USER_DATA_RPL;
		__result->scs_sgregs.sg_gs = SEGMENT_USER_DATA_RPL;
#else /* __x86_64__ */
		__result->scs_sgregs.sg_fs = SEGMENT_USER_FSBASE_RPL;
		__result->scs_sgregs.sg_gs = SEGMENT_USER_GSBASE_RPL;
#endif /* !__x86_64__ */
	} else
#endif /* !__I386_NO_VM86 */
	{
		if (__v_cs & 3) {
			__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
			                                  (OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_USER));
			__result->scs_irregs_u.ir_esp = __self->kcs_gpregs.gp_esp;
			__result->scs_irregs_u.ir_ss  = __v_ss;
		} else {
			__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
			                                  (OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_KERNEL));
		}
		__result->scs_sgregs.sg_fs = __v_fs;
		__result->scs_sgregs.sg_gs = __v_gs;
		__result->scs_sgregs.sg_es = __v_es;
		__result->scs_sgregs.sg_ds = __v_ds;
	}
	__result->scs_irregs.ir_eip    = __self->kcs_eip;
	__result->scs_irregs.ir_eflags = __self->kcs_eflags;
	__result->scs_irregs.ir_cs     = __v_cs;
	__libc_memcpy(&__result->scs_gpregs,
	              &__self->kcs_gpregs,
	              sizeof(struct gpregs32));
	return __result;
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct scpustate32 *
__NOTHROW_NCX(kcpustate32_to_scpustate32_p)(struct kcpustate32 const *__restrict __self,
                                            void *__restrict __kernel_esp) {
	return kcpustate32_to_scpustate32_p_ex(__self, __kernel_esp,
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
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct icpustate32 *
__NOTHROW_NCX(kcpustate32_to_icpustate32_p_ex)(struct kcpustate32 const *__restrict __self,
                                               void *__restrict __kernel_esp,
#ifndef __I386_NO_VM86
                                               __u16 __v_gs_vm86,
#endif /* !__I386_NO_VM86 */
                                               __u16 __v_fs, __u16 __v_es,
                                               __u16 __v_ds, __u16 __v_cs, __u16 __v_ss) {
	struct icpustate32 *__result;
#ifndef __I386_NO_VM86
	if (__self->kcs_eflags & 0x20000) {
		__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
		                                  (OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_VM86));
		__result->ics_irregs_v.ir_esp = __self->kcs_gpregs.gp_esp;
		__result->ics_irregs_v.ir_ss  = __v_ss;
		__result->ics_irregs_v.ir_es  = __v_es;
		__result->ics_irregs_v.ir_ds  = __v_ds;
		__result->ics_irregs_v.ir_fs  = __v_fs;
		__result->ics_irregs_v.ir_gs  = __v_gs_vm86;
		__result->ics_ds = SEGMENT_USER_DATA_RPL;
		__result->ics_es = SEGMENT_USER_DATA_RPL;
#ifdef __x86_64__
		__result->ics_fs = SEGMENT_USER_DATA_RPL;
#else /* __x86_64__ */
		__result->ics_fs = SEGMENT_USER_FSBASE_RPL;
#endif /* !__x86_64__ */
	} else
#endif /* !__I386_NO_VM86 */
	{
		if (__v_cs & 3) {
			__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
			                                  (OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_USER));
			__result->ics_irregs_u.ir_esp = __self->kcs_gpregs.gp_esp;
			__result->ics_irregs_u.ir_ss  = __v_ss;
		} else {
			__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
			                                  (OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_KERNEL));
		}
		__result->ics_fs = __v_fs;
		__result->ics_es = __v_es;
		__result->ics_ds = __v_ds;
	}
	__result->ics_irregs.ir_eip    = __self->kcs_eip;
	__result->ics_irregs.ir_eflags = __self->kcs_eflags;
	__result->ics_irregs.ir_cs     = __v_cs;
	__libc_memcpy(&__result->ics_gpregs,
	              &__self->kcs_gpregs,
	              sizeof(struct gpregs32));
	return __result;
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct icpustate32 *
__NOTHROW_NCX(kcpustate32_to_icpustate32_p)(struct kcpustate32 const *__restrict __self,
                                            void *__restrict __kernel_esp) {
	return kcpustate32_to_icpustate32_p_ex(__self, __kernel_esp,
#ifndef __I386_NO_VM86
	                                       0,
#endif /* !__I386_NO_VM86 */
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
/* `struct icpustate32'                                                 */
/************************************************************************/
#define icpustate32_foreach_gpregs(self, cb)       \
	do {                                           \
		gpregs32_foreach(&(self)->ics_gpregs, cb); \
		if (icpustate32_isuser(self)) {            \
			cb(icpustate32_getuseresp(self));      \
		}                                          \
	}	__WHILE0
#define icpustate32_getisa(self)                 irregs32_getisa(&(self)->ics_irregs)
#define icpustate32_isvm86(self)                 irregs32_isvm86(&(self)->ics_irregs)
#define icpustate32_isuser_novm86(self)          irregs32_isuser_novm86(&(self)->ics_irregs)
#define icpustate32_isuser(self)                 irregs32_isuser(&(self)->ics_irregs)
#define icpustate32_iskernel(self)               irregs32_iskernel(&(self)->ics_irregs)
#define icpustate32_getpreemption(self)          irregs32_getpreemption(&(self)->ics_irregs)
#define icpustate32_setpreemption(self, turn_on) irregs32_setpreemption(&(self)->ics_irregs, turn_on)
#define icpustate32_geteip(self)                 irregs32_geteip(&(self)->ics_irregs)
#define icpustate32_seteip(self, value)          irregs32_seteip(&(self)->ics_irregs, value)
#define icpustate32_getesp(self)                 irregs32_getesp(&(self)->ics_irregs)
#define icpustate32_getuseresp(self)             irregs32_getuseresp(&(self)->ics_irregs)
#define icpustate32_setuseresp(self, value)      irregs32_setuseresp(&(self)->ics_irregs, value)
#define icpustate32_getuserss(self)              irregs32_getuserss(&(self)->ics_irregs)
#define icpustate32_setuserss(self, value)       irregs32_setuserss(&(self)->ics_irregs, value)
#define icpustate32_getkernelss(self)            irregs32_getkernelss(&(self)->ics_irregs)
#define icpustate32_getkernelesp(self)           irregs32_getkernelesp(&(self)->ics_irregs)
#ifndef __I386_NO_VM86
#define icpustate32_getds_vm86(self)             ((self)->ics_irregs_v.ir_ds16)
#define icpustate32_setds_vm86(self, value)      ((self)->ics_irregs_v.ir_ds = (value))
#define icpustate32_getes_vm86(self)             ((self)->ics_irregs_v.ir_es16)
#define icpustate32_setes_vm86(self, value)      ((self)->ics_irregs_v.ir_es = (value))
#define icpustate32_getfs_vm86(self)             ((self)->ics_irregs_v.ir_fs16)
#define icpustate32_setfs_vm86(self, value)      ((self)->ics_irregs_v.ir_fs = (value))
#define icpustate32_getgs_vm86(self)             ((self)->ics_irregs_v.ir_gs16)
#define icpustate32_setgs_vm86(self, value)      ((self)->ics_irregs_v.ir_gs = (value))
#define icpustate32_getds(self)                  (icpustate32_isvm86(self) ? (self)->ics_irregs_v.ir_ds16 : (self)->ics_ds16)
#define icpustate32_setds(self, value)           (icpustate32_isvm86(self) ? ((self)->ics_irregs_v.ir_ds = (value)) : ((self)->ics_ds = (value)))
#define icpustate32_getes(self)                  (icpustate32_isvm86(self) ? (self)->ics_irregs_v.ir_es16 : (self)->ics_es16)
#define icpustate32_setes(self, value)           (icpustate32_isvm86(self) ? ((self)->ics_irregs_v.ir_es = (value)) : ((self)->ics_es = (value)))
#define icpustate32_getfs(self)                  (icpustate32_isvm86(self) ? (self)->ics_irregs_v.ir_fs16 : (self)->ics_fs16)
#define icpustate32_setfs(self, value)           (icpustate32_isvm86(self) ? ((self)->ics_irregs_v.ir_fs = (value)) : ((self)->ics_fs = (value)))
#define icpustate32_getgs_ex(self, v_nonvm86_gs) (icpustate32_isvm86(self) ? (self)->ics_irregs_v.ir_gs16 : (v_nonvm86_gs))
#define icpustate32_setgs(self, value)           (icpustate32_isvm86(self) ? (void)((self)->ics_irregs_v.ir_gs = (value)) : icpustate32_setgs_novm86(self, value))
#define icpustate32_trysetgs(self, value)        (icpustate32_isvm86(self) ? ((self)->ics_irregs_v.ir_gs = (value), 1) : (icpustate32_getgs_novm86(self) == (value)))
#else /* !__I386_NO_VM86 */
#define icpustate32_getds(self)                  ((self)->ics_ds16)
#define icpustate32_setds(self, value)           ((self)->ics_ds = (value))
#define icpustate32_getes(self)                  ((self)->ics_es16)
#define icpustate32_setes(self, value)           ((self)->ics_es = (value))
#define icpustate32_getfs(self)                  ((self)->ics_fs16)
#define icpustate32_setfs(self, value)           ((self)->ics_fs = (value))
#define icpustate32_getgs_ex(self, v_nonvm86_gs) (v_nonvm86_gs)
#define icpustate32_setgs(self, value)           icpustate32_setgs_novm86(self, value)
#define icpustate32_trysetgs(self, value)        (icpustate32_getgs_novm86(self) == (value))
#endif /* __I386_NO_VM86 */
#define icpustate32_getgs(self)                  icpustate32_getgs_ex(self, icpustate32_getgs_novm86(self))
#define icpustate32_getds_novm86(self)           ((__u16)(self)->ics_ds16)
#define icpustate32_setds_novm86(self, value)    ((self)->ics_ds = (value))
#define icpustate32_getes_novm86(self)           ((__u16)(self)->ics_es16)
#define icpustate32_setes_novm86(self, value)    ((self)->ics_es = (value))
#define icpustate32_getfs_novm86(self)           ((__u16)(self)->ics_fs16)
#define icpustate32_setfs_novm86(self, value)    ((self)->ics_fs = (value))
#define icpustate32_getgs_novm86(self)           __rdgs()
#ifdef __x86_64__
#define icpustate32_setgs_novm86(self, value)    __wrgs_keepbase(value)
#else /* __x86_64__ */
#define icpustate32_setgs_novm86(self, value)    __wrgs(value)
#endif /* !__x86_64__ */
#define icpustate32_geteflags(self)              irregs32_geteflags(&(self)->ics_irregs)
#define icpustate32_seteflags(self, value)       irregs32_seteflags(&(self)->ics_irregs, value)
#define icpustate32_mskeflags(self, mask, value) irregs32_mskeflags(&(self)->ics_irregs, mask, value)
#define icpustate32_getcs(self)                  irregs32_getcs(&(self)->ics_irregs)
#define icpustate32_setcs(self, value)           irregs32_setcs(&(self)->ics_irregs, value)
#define icpustate32_getss(self)                  irregs32_getss(&(self)->ics_irregs)
#define icpustate32_trysetss(self, value)        irregs32_trysetss(&(self)->ics_irregs, value)
#define icpustate32_trysetuserss(self, value)    irregs32_trysetuserss(&(self)->ics_irregs, value)
#define icpustate32_trysetesp(self, value)       irregs32_trysetesp(&(self)->ics_irregs, value)
#define icpustate32_sizeof(self)                 (irregs32_sizeof(&(self)->ics_irregs) + OFFSET_ICPUSTATE32_IRREGS)
__LOCAL __NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) struct icpustate32 *
__NOTHROW_NCX(icpustate32_setesp_p)(struct icpustate32 *__restrict __self,
                                    __u32 __v_esp) {
	if (icpustate32_isuser(__self)) {
		icpustate32_setuseresp(__self, __v_esp);
	} else {
		struct icpustate32 *__result;
		__result = (struct icpustate32 *)(__uintptr_t)(__v_esp - (OFFSET_ICPUSTATE32_IRREGS +
		                                                          SIZEOF_IRREGS32_KERNEL));
		__libc_memmove(__result, __self,
		               OFFSET_ICPUSTATE32_IRREGS +
		               SIZEOF_IRREGS32_KERNEL);
		__self = __result;
	}
	return __self;
}

__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(icpustate32_to_ucpustate32_ex)(struct icpustate32 const *__restrict __self,
                                             struct ucpustate32 *__restrict __result,
                                             __u16 __v_nonvm86_gs) {
	__libc_memcpy(&__result->ucs_gpregs,
	              &__self->ics_gpregs,
	              sizeof(struct gpregs32));
	__result->ucs_eip    = icpustate32_geteip(__self);
	__result->ucs_eflags = icpustate32_geteflags(__self);
	__result->ucs_cs     = icpustate32_getcs(__self);
#ifndef __I386_NO_VM86
	if (icpustate32_isvm86(__self)) {
		__result->ucs_gpregs.gp_esp = icpustate32_getuseresp(__self);
		__result->ucs_ss            = icpustate32_getuserss(__self);
		__result->ucs_sgregs.sg_ds  = __self->ics_irregs_v.ir_ds;
		__result->ucs_sgregs.sg_es  = __self->ics_irregs_v.ir_es;
		__result->ucs_sgregs.sg_fs  = __self->ics_irregs_v.ir_fs;
		__result->ucs_sgregs.sg_gs  = __self->ics_irregs_v.ir_gs;
	} else
#endif /* !__I386_NO_VM86 */
	{
		__result->ucs_sgregs.sg_ds = __self->ics_ds;
		__result->ucs_sgregs.sg_es = __self->ics_es;
		__result->ucs_sgregs.sg_fs = __self->ics_fs;
		__result->ucs_sgregs.sg_gs = __v_nonvm86_gs;
		if (icpustate32_isuser(__self)) {
			__result->ucs_gpregs.gp_esp = icpustate32_getuseresp(__self);
			__result->ucs_ss            = icpustate32_getuserss(__self);
		} else {
			__result->ucs_gpregs.gp_esp = icpustate32_getkernelesp(__self);
			__result->ucs_ss            = icpustate32_getkernelss(__self);
		}
	}
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(icpustate32_user_to_ucpustate32_ex)(struct icpustate32 const *__restrict __self,
                                                  struct ucpustate32 *__restrict __result,
                                                  __u16 __v_nonvm86_gs) {
	__hybrid_assert(icpustate32_isuser(__self));
	__libc_memcpy(&__result->ucs_gpregs,
	              &__self->ics_gpregs,
	              sizeof(struct gpregs32));
	__result->ucs_eip    = icpustate32_geteip(__self);
	__result->ucs_eflags = icpustate32_geteflags(__self);
	__result->ucs_cs     = icpustate32_getcs(__self);
	if (icpustate32_isvm86(__self)) {
		__result->ucs_gpregs.gp_esp = icpustate32_getuseresp(__self);
		__result->ucs_ss            = icpustate32_getuserss(__self);
		__result->ucs_sgregs.sg_ds  = __self->ics_irregs_v.ir_ds;
		__result->ucs_sgregs.sg_es  = __self->ics_irregs_v.ir_es;
		__result->ucs_sgregs.sg_fs  = __self->ics_irregs_v.ir_fs;
		__result->ucs_sgregs.sg_gs  = __self->ics_irregs_v.ir_gs;
	} else {
		__result->ucs_sgregs.sg_ds  = __self->ics_ds;
		__result->ucs_sgregs.sg_es  = __self->ics_es;
		__result->ucs_sgregs.sg_fs  = __self->ics_fs;
		__result->ucs_sgregs.sg_gs  = __v_nonvm86_gs;
		__result->ucs_gpregs.gp_esp = icpustate32_getuseresp(__self);
		__result->ucs_ss            = icpustate32_getuserss(__self);
	}
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(icpustate32_to_ucpustate32)(struct icpustate32 const *__restrict __self,
                                          struct ucpustate32 *__restrict __result) {
	icpustate32_to_ucpustate32_ex(__self, __result, __rdgs());
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(icpustate32_user_to_ucpustate32)(struct icpustate32 const *__restrict __self,
                                               struct ucpustate32 *__restrict __result) {
	icpustate32_user_to_ucpustate32_ex(__self, __result, __rdgs());
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(icpustate32_to_kcpustate32)(struct icpustate32 const *__restrict __self,
                                          struct kcpustate32 *__restrict __result) {
	__libc_memcpy(&__result->kcs_gpregs,
	              &__self->ics_gpregs,
	              sizeof(struct gpregs32));
	__result->kcs_eip           = icpustate32_geteip(__self);
	__result->kcs_eflags        = icpustate32_geteflags(__self);
	__result->kcs_gpregs.gp_esp = icpustate32_getesp(__self);
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(icpustate32_user_to_kcpustate32)(struct icpustate32 const *__restrict __self,
                                               struct kcpustate32 *__restrict __result) {
	__hybrid_assert(icpustate32_isuser(__self));
	__libc_memcpy(&__result->kcs_gpregs,
	              &__self->ics_gpregs,
	              sizeof(struct gpregs32));
	__result->kcs_eip           = icpustate32_geteip(__self);
	__result->kcs_eflags        = icpustate32_geteflags(__self);
	__result->kcs_gpregs.gp_esp = icpustate32_getuseresp(__self);
}
/* Create a new scheduler cpu-state from a given interrupt cpu state. */
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct scpustate32 *
__NOTHROW_NCX(icpustate32_to_scpustate32_p_ex)(struct icpustate32 const *__restrict __self,
                                               void *__restrict __kernel_esp,
                                               __u16 __v_nonvm86_gs) {
	struct scpustate32 *__result;
	__u16 __v_cs     = icpustate32_getcs(__self);
	__u32 __v_eflags = icpustate32_geteflags(__self);
#ifndef __I386_NO_VM86
	if (__v_eflags & 0x20000) {
		__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
		                                  (OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_VM86));
		__result->scs_irregs_v.ir_esp = icpustate32_getuseresp(__self);
		__result->scs_irregs_v.ir_ss  = icpustate32_getuserss(__self);
		__result->scs_irregs_v.ir_es  = __self->ics_irregs_v.ir_es16;
		__result->scs_irregs_v.ir_ds  = __self->ics_irregs_v.ir_ds16;
		__result->scs_irregs_v.ir_fs  = __self->ics_irregs_v.ir_fs16;
		__result->scs_irregs_v.ir_gs  = __self->ics_irregs_v.ir_gs16;
		__result->scs_sgregs.sg_ds    = __self->ics_ds16;
		__result->scs_sgregs.sg_es    = __self->ics_es16;
		__result->scs_sgregs.sg_fs    = __self->ics_fs16;
		__result->scs_sgregs.sg_gs    = __v_nonvm86_gs;
	} else
#endif /* !__I386_NO_VM86 */
	{
		if (__v_cs & 3) {
			__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
			                                  (OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_USER));
			__result->scs_irregs_u.ir_esp = icpustate32_getuseresp(__self);
			__result->scs_irregs_u.ir_ss  = icpustate32_getuserss(__self);
		} else {
			__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
			                                  (OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_KERNEL));
		}
		__result->scs_sgregs.sg_gs = __v_nonvm86_gs;
		__result->scs_sgregs.sg_fs = __self->ics_fs16;
		__result->scs_sgregs.sg_es = __self->ics_es16;
		__result->scs_sgregs.sg_ds = __self->ics_ds16;
	}
	__result->scs_irregs.ir_eip    = icpustate32_geteip(__self);
	__result->scs_irregs.ir_eflags = __v_eflags;
	__result->scs_irregs.ir_cs     = __v_cs;
	__libc_memcpy(&__result->scs_gpregs,
	              &__self->ics_gpregs,
	              sizeof(struct gpregs32));
	return __result;
}
/* Create a new scheduler cpu-state from a given interrupt cpu state. */
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct scpustate32 *
__NOTHROW_NCX(icpustate32_user_to_scpustate32_p_ex)(struct icpustate32 const *__restrict __self,
                                                    void *__restrict __kernel_esp,
                                                    __u16 __v_nonvm86_gs) {
	struct scpustate32 *__result;
	__u32 __v_eflags = icpustate32_geteflags(__self);
#ifndef __I386_NO_VM86
	if (__v_eflags & 0x20000) {
		__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
		                                  (OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_VM86));
		__result->scs_irregs_v.ir_esp = icpustate32_getuseresp(__self);
		__result->scs_irregs_v.ir_ss  = icpustate32_getuserss(__self);
		__result->scs_irregs_v.ir_es  = __self->ics_irregs_v.ir_es16;
		__result->scs_irregs_v.ir_ds  = __self->ics_irregs_v.ir_ds16;
		__result->scs_irregs_v.ir_fs  = __self->ics_irregs_v.ir_fs16;
		__result->scs_irregs_v.ir_gs  = __self->ics_irregs_v.ir_gs16;
		__result->scs_sgregs.sg_ds    = __self->ics_ds16;
		__result->scs_sgregs.sg_es    = __self->ics_es16;
		__result->scs_sgregs.sg_fs    = __self->ics_fs16;
		__result->scs_sgregs.sg_gs    = __v_nonvm86_gs;
	} else
#endif /* !__I386_NO_VM86 */
	{
		__hybrid_assert(icpustate32_getcs(__self) & 3);
		__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
		                                  (OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_USER));
		__result->scs_irregs_u.ir_esp = icpustate32_getuseresp(__self);
		__result->scs_irregs_u.ir_ss  = icpustate32_getuserss(__self);
		__result->scs_sgregs.sg_gs = __v_nonvm86_gs;
		__result->scs_sgregs.sg_fs = __self->ics_fs16;
		__result->scs_sgregs.sg_es = __self->ics_es16;
		__result->scs_sgregs.sg_ds = __self->ics_ds16;
	}
	__result->scs_irregs.ir_eip    = icpustate32_geteip(__self);
	__result->scs_irregs.ir_eflags = __v_eflags;
	__result->scs_irregs.ir_cs     = icpustate32_getcs(__self);
	__libc_memcpy(&__result->scs_gpregs,
	              &__self->ics_gpregs,
	              sizeof(struct gpregs32));
	return __result;
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct scpustate32 *
__NOTHROW_NCX(icpustate32_to_scpustate32_p)(struct icpustate32 const *__restrict __self,
                                            void *__restrict __kernel_esp) {
	return icpustate32_to_scpustate32_p_ex(__self, __kernel_esp, __rdgs());
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct scpustate32 *
__NOTHROW_NCX(icpustate32_user_to_scpustate32_p)(struct icpustate32 const *__restrict __self,
                                                 void *__restrict __kernel_esp) {
	return icpustate32_user_to_scpustate32_p_ex(__self, __kernel_esp, __rdgs());
}
/* Create a duplicate of the given interrupt cpu state. */
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct icpustate32 *
__NOTHROW_NCX(icpustate32_to_icpustate32_p)(struct icpustate32 const *__restrict __self,
                                            void *__restrict __kernel_esp) {
	struct icpustate32 *__result;
	__u16 __v_cs     = icpustate32_getcs(__self);
	__u32 __v_eflags = icpustate32_geteflags(__self);
#ifndef __I386_NO_VM86
	if (__v_eflags & 0x20000) {
		__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
		                                  (OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_VM86));
		__result->ics_irregs_v.ir_esp = icpustate32_getuseresp(__self);
		__result->ics_irregs_v.ir_ss  = icpustate32_getuserss(__self);
		__result->ics_irregs_v.ir_es  = __self->ics_irregs_v.ir_es16;
		__result->ics_irregs_v.ir_ds  = __self->ics_irregs_v.ir_ds16;
		__result->ics_irregs_v.ir_fs  = __self->ics_irregs_v.ir_fs16;
		__result->ics_irregs_v.ir_gs  = __self->ics_irregs_v.ir_gs16;
		__result->ics_ds              = __self->ics_ds16;
		__result->ics_es              = __self->ics_es16;
		__result->ics_fs              = __self->ics_fs16;
	} else
#endif /* !__I386_NO_VM86 */
	{
		if (__v_cs & 3) {
			__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
			                                  (OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_USER));
			__result->ics_irregs_u.ir_esp = icpustate32_getuseresp(__self);
			__result->ics_irregs_u.ir_ss  = icpustate32_getuserss(__self);
		} else {
			__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
			                                  (OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_KERNEL));
		}
		__result->ics_fs = __self->ics_fs16;
		__result->ics_es = __self->ics_es16;
		__result->ics_ds = __self->ics_ds16;
	}
	__result->ics_irregs.ir_eip    = icpustate32_geteip(__self);
	__result->ics_irregs.ir_eflags = __v_eflags;
	__result->ics_irregs.ir_cs     = __v_cs;
	__libc_memcpy(&__result->ics_gpregs,
	              &__self->ics_gpregs,
	              sizeof(struct gpregs32));
	return __result;
}
/* Create a duplicate of the given interrupt cpu state. */
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct icpustate32 *
__NOTHROW_NCX(icpustate32_user_to_icpustate32_p)(struct icpustate32 const *__restrict __self,
                                                 void *__restrict __kernel_esp) {
	struct icpustate32 *__result;
	__u32 __v_eflags = icpustate32_geteflags(__self);
#ifndef __I386_NO_VM86
	if (__v_eflags & 0x20000) {
		__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
		                                  (OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_VM86));
		__result->ics_irregs_v.ir_esp = icpustate32_getuseresp(__self);
		__result->ics_irregs_v.ir_ss  = icpustate32_getuserss(__self);
		__result->ics_irregs_v.ir_es  = __self->ics_irregs_v.ir_es16;
		__result->ics_irregs_v.ir_ds  = __self->ics_irregs_v.ir_ds16;
		__result->ics_irregs_v.ir_fs  = __self->ics_irregs_v.ir_fs16;
		__result->ics_irregs_v.ir_gs  = __self->ics_irregs_v.ir_gs16;
		__result->ics_ds              = __self->ics_ds16;
		__result->ics_es              = __self->ics_es16;
		__result->ics_fs              = __self->ics_fs16;
	} else
#endif /* !__I386_NO_VM86 */
	{
		__hybrid_assert(icpustate32_getcs(__self) & 3);
		__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
		                                  (OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_USER));
		__result->ics_irregs_u.ir_esp = icpustate32_getuseresp(__self);
		__result->ics_irregs_u.ir_ss  = icpustate32_getuserss(__self);
		__result->ics_fs = __self->ics_fs16;
		__result->ics_es = __self->ics_es16;
		__result->ics_ds = __self->ics_ds16;
	}
	__result->ics_irregs.ir_eip    = icpustate32_geteip(__self);
	__result->ics_irregs.ir_eflags = __v_eflags;
	__result->ics_irregs.ir_cs     = icpustate32_getcs(__self);
	__libc_memcpy(&__result->ics_gpregs,
	              &__self->ics_gpregs,
	              sizeof(struct gpregs32));
	return __result;
}
/************************************************************************/




/************************************************************************/
/* `struct scpustate32'                                                 */
/************************************************************************/
#define scpustate32_foreach_gpregs(self, cb)       \
	do {                                           \
		gpregs32_foreach(&(self)->scs_gpregs, cb); \
		if (scpustate32_isuser(self)) {            \
			cb(scpustate32_getuseresp(self));      \
		}                                          \
	}	__WHILE0
#ifdef __I386_NO_VM86
#define scpustate32_isvm86(self)                 0
#define scpustate32_isuser_novm86(self)          ((self)->scs_irregs.ir_cs16 & 3)
#define scpustate32_isuser(self)                 ((self)->scs_irregs.ir_cs16 & 3)
#define scpustate32_iskernel(self)               (!((self)->scs_irregs.ir_cs16 & 3))
#define scpustate32_getisa(self)                 ISA_I386
#else /* __I386_NO_VM86 */
#define scpustate32_isvm86(self)                 ((self)->scs_irregs.ir_eflags & 0x20000)
#define scpustate32_isuser_novm86(self)          ((self)->scs_irregs.ir_cs16 & 3)
#define scpustate32_isuser(self)                 (((self)->scs_irregs.ir_cs16 & 3) || scpustate32_isvm86(self))
#define scpustate32_iskernel(self)               (!((self)->scs_irregs.ir_cs16 & 3) && !scpustate32_isvm86(self))
#define scpustate32_getisa(self)                 (scpustate32_isvm86(self) ? ISA_8086 : ISA_I386)
#endif /* !__I386_NO_VM86 */
#define scpustate32_getpreemption(self)          ((self)->scs_irregs.ir_eflags & 0x200)
#define scpustate32_setpreemption(self, turn_on) (turn_on ? (void)((self)->scs_irregs.ir_eflags |= 0x200) : (void)((self)->scs_irregs.ir_eflags &= ~0x200))
#define scpustate32_geteip(self)                 ((__u32)(self)->scs_irregs.ir_eip)
#define scpustate32_seteip(self, value)          ((self)->scs_irregs.ir_eip = (value))
#define scpustate32_getuseresp(self)             ((__u32)(self)->scs_irregs_u.ir_esp)
#define scpustate32_setuseresp(self, value)      ((self)->scs_irregs_u.ir_esp = (value))
#define scpustate32_getuserss(self)              ((__u32)(self)->scs_irregs_u.ir_ss16)
#define scpustate32_setuserss(self, value)       ((self)->scs_irregs_u.ir_ss = (value))
#define scpustate32_getkernelss(self)            SEGMENT_KERNEL_DATA
#define scpustate32_getkernelesp(self)           ((__u32)(__uintptr_t)(&(self)->scs_irregs_k + 1))
#define scpustate32_getds(self)                  (scpustate32_isvm86(self) ? (self)->scs_irregs_v.ir_ds16 : (self)->scs_sgregs.sg_ds16)
#define scpustate32_setds(self, value)           (scpustate32_isvm86(self) ? ((self)->scs_irregs_v.ir_ds = (value)) : ((self)->scs_sgregs.sg_ds = (value)))
#define scpustate32_getes(self)                  (scpustate32_isvm86(self) ? (self)->scs_irregs_v.ir_es16 : (self)->scs_sgregs.sg_es16)
#define scpustate32_setes(self, value)           (scpustate32_isvm86(self) ? ((self)->scs_irregs_v.ir_es = (value)) : ((self)->scs_sgregs.sg_es = (value)))
#define scpustate32_getfs(self)                  (scpustate32_isvm86(self) ? (self)->scs_irregs_v.ir_fs16 : (self)->scs_sgregs.sg_fs16)
#define scpustate32_setfs(self, value)           (scpustate32_isvm86(self) ? ((self)->scs_irregs_v.ir_fs = (value)) : ((self)->scs_sgregs.sg_fs = (value)))
#define scpustate32_getgs(self)                  (scpustate32_isvm86(self) ? (self)->scs_irregs_v.ir_gs16 : (self)->scs_sgregs.sg_gs16)
#define scpustate32_setgs(self, value)           (scpustate32_isvm86(self) ? ((self)->scs_irregs_v.ir_gs = (value)) : ((self)->scs_sgregs.sg_gs = (value)))
#define scpustate32_getds_novm86(self)           ((__u16)(self)->scs_ds16)
#define scpustate32_setds_novm86(self, value)    ((self)->scs_ds = (value))
#define scpustate32_getes_novm86(self)           ((__u16)(self)->scs_es16)
#define scpustate32_setes_novm86(self, value)    ((self)->scs_es = (value))
#define scpustate32_getfs_novm86(self)           ((__u16)(self)->scs_fs16)
#define scpustate32_setfs_novm86(self, value)    ((self)->scs_fs = (value))
#define scpustate32_getgs_novm86(self)           ((__u16)(self)->scs_gs16)
#define scpustate32_setgs_novm86(self, value)    ((self)->scs_gs = (value))
#define scpustate32_geteflags(self)              ((__u32)(self)->scs_irregs.ir_eflags)
#define scpustate32_seteflags(self, value)       ((self)->scs_irregs.ir_eflags = (value))
#define scpustate32_mskeflags(self, mask, value) ((self)->scs_irregs.ir_eflags = ((self)->scs_irregs.ir_eflags & (mask)) | (flags))
#define scpustate32_getcs(self)                  ((__u16)(self)->scs_irregs.ir_cs16)
#define scpustate32_setcs(self, value)           ((self)->scs_irregs.ir_cs = (value))
#define scpustate32_getesp(self)                 (scpustate32_isuser(self) ? scpustate32_getuseresp(self) : scpustate32_getkernelesp(self))
#define scpustate32_getss(self)                  (scpustate32_isuser(self) ? scpustate32_getuserss(self) : scpustate32_getkernelss(self))
#define scpustate32_trysetesp(self, value)       (scpustate32_isuser(self) ? (scpustate32_setuseresp(self, value), 1) : (scpustate32_getkernelesp(self) == (value)))
#define scpustate32_trysetss(self, value)        (scpustate32_isuser(self) ? (scpustate32_setuserss(self, value), 1) : (scpustate32_getkernelss(self) == (value)))
#define scpustate32_trysetuserss(self, value)    (scpustate32_isuser(self) ? (scpustate32_setuserss(self, value), 1) : 0)
#define scpustate32_sizeof(self)                            \
	(scpustate32_isvm86(self)                               \
	 ? (OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_VM86)   \
	 : ((self)->scs_irregs.ir_cs16 & 3)                     \
	   ? (OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_USER) \
	   : (OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_KERNEL))

__LOCAL __NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) struct scpustate32 *
__NOTHROW_NCX(scpustate32_setesp_p)(struct scpustate32 *__restrict __self,
                                    __u32 __v_esp) {
	if (scpustate32_isuser(__self)) {
		scpustate32_setuseresp(__self, __v_esp);
	} else {
		struct scpustate32 *__result;
		__result = (struct scpustate32 *)(__uintptr_t)(__v_esp - (OFFSET_SCPUSTATE32_IRREGS +
		                                                          SIZEOF_IRREGS32_KERNEL));
		__libc_memmove(__result, __self,
		               OFFSET_SCPUSTATE32_IRREGS +
		               SIZEOF_IRREGS32_KERNEL);
		__self = __result;
	}
	return __self;
}

__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(scpustate32_to_ucpustate32)(struct scpustate32 const *__restrict __self,
                                          struct ucpustate32 *__restrict __result) {
	__result->ucs_gpregs = __self->scs_gpregs;
	__result->ucs_eip    = scpustate32_geteip(__self);
	__result->ucs_eflags = scpustate32_geteflags(__self);
	__result->ucs_cs     = scpustate32_getcs(__self);
	if (scpustate32_isvm86(__self)) {
		__result->ucs_gpregs.gp_esp = scpustate32_getuseresp(__self);
		__result->ucs_ss            = scpustate32_getuserss(__self);
		__result->ucs_sgregs.sg_ds  = __self->scs_irregs_v.ir_ds16;
		__result->ucs_sgregs.sg_es  = __self->scs_irregs_v.ir_es16;
		__result->ucs_sgregs.sg_fs  = __self->scs_irregs_v.ir_fs16;
		__result->ucs_sgregs.sg_gs  = __self->scs_irregs_v.ir_gs16;
	} else {
		__result->ucs_sgregs = __self->scs_sgregs;
		if (scpustate32_isuser(__self)) {
			__result->ucs_gpregs.gp_esp = scpustate32_getuseresp(__self);
			__result->ucs_ss            = scpustate32_getuserss(__self);
		} else {
			__result->ucs_gpregs.gp_esp = scpustate32_getkernelesp(__self);
			__result->ucs_ss            = scpustate32_getkernelss(__self);
		}
	}
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(scpustate32_user_to_ucpustate32)(struct scpustate32 const *__restrict __self,
                                               struct ucpustate32 *__restrict __result) {
	__hybrid_assert(scpustate32_isuser(__self));
	__result->ucs_gpregs = __self->scs_gpregs;
	__result->ucs_eip    = scpustate32_geteip(__self);
	__result->ucs_eflags = scpustate32_geteflags(__self);
	__result->ucs_cs     = scpustate32_getcs(__self);
	if (scpustate32_isvm86(__self)) {
		__result->ucs_gpregs.gp_esp = scpustate32_getuseresp(__self);
		__result->ucs_ss            = scpustate32_getuserss(__self);
		__result->ucs_sgregs.sg_ds  = __self->scs_irregs_v.ir_ds16;
		__result->ucs_sgregs.sg_es  = __self->scs_irregs_v.ir_es16;
		__result->ucs_sgregs.sg_fs  = __self->scs_irregs_v.ir_fs16;
		__result->ucs_sgregs.sg_gs  = __self->scs_irregs_v.ir_gs16;
	} else {
		__libc_memcpy(&__result->ucs_sgregs,
		              &__self->scs_sgregs,
		              sizeof(struct sgregs32));
		__result->ucs_gpregs.gp_esp = scpustate32_getuseresp(__self);
		__result->ucs_ss            = scpustate32_getuserss(__self);
	}
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(scpustate32_to_kcpustate32)(struct scpustate32 const *__restrict __self,
                                          struct kcpustate32 *__restrict __result) {
	__libc_memcpy(&__result->kcs_gpregs,
	              &__self->scs_gpregs,
	              sizeof(struct gpregs32));
	__result->kcs_eip           = scpustate32_geteip(__self);
	__result->kcs_eflags        = scpustate32_geteflags(__self);
	__result->kcs_gpregs.gp_esp = scpustate32_getesp(__self);
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(scpustate32_user_to_kcpustate32)(struct scpustate32 const *__restrict __self,
                                               struct kcpustate32 *__restrict __result) {
	__hybrid_assert(scpustate32_isuser(__self));
	__libc_memcpy(&__result->kcs_gpregs,
	              &__self->scs_gpregs,
	              sizeof(struct gpregs32));
	__result->kcs_eip           = scpustate32_geteip(__self);
	__result->kcs_eflags        = scpustate32_geteflags(__self);
	__result->kcs_gpregs.gp_esp = scpustate32_getuseresp(__self);
}
/* Create a new interrupt cpu-state from a given scheduler cpu state. */
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct icpustate32 *
__NOTHROW_NCX(scpustate32_to_icpustate32_p)(struct scpustate32 const *__restrict __self,
                                            void *__restrict __kernel_esp) {
	struct icpustate32 *__result;
	__u16 __v_cs     = scpustate32_getcs(__self);
	__u32 __v_eflags = scpustate32_geteflags(__self);
#ifndef __I386_NO_VM86
	if (__v_eflags & 0x20000) {
		__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
		                                  (OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_VM86));
		__result->ics_irregs_v.ir_esp = scpustate32_getuseresp(__self);
		__result->ics_irregs_v.ir_ss  = scpustate32_getuserss(__self);
		__result->ics_irregs_v.ir_es  = __self->scs_irregs_v.ir_es16;
		__result->ics_irregs_v.ir_ds  = __self->scs_irregs_v.ir_ds16;
		__result->ics_irregs_v.ir_fs  = __self->scs_irregs_v.ir_fs16;
		__result->ics_irregs_v.ir_gs  = __self->scs_irregs_v.ir_gs16;
		__result->ics_ds              = __self->scs_sgregs.sg_ds16;
		__result->ics_es              = __self->scs_sgregs.sg_es16;
		__result->ics_fs              = __self->scs_sgregs.sg_fs16;
	} else
#endif /* !__I386_NO_VM86 */
	{
		if (__v_cs & 3) {
			__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
			                                  (OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_USER));
			__result->ics_irregs_u.ir_esp = scpustate32_getuseresp(__self);
			__result->ics_irregs_u.ir_ss  = scpustate32_getuserss(__self);
		} else {
			__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
			                                  (OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_KERNEL));
		}
		__result->ics_fs = __self->scs_sgregs.sg_fs16;
		__result->ics_es = __self->scs_sgregs.sg_es16;
		__result->ics_ds = __self->scs_sgregs.sg_ds16;
	}
	__result->ics_irregs.ir_eip    = scpustate32_geteip(__self);
	__result->ics_irregs.ir_eflags = __v_eflags;
	__result->ics_irregs.ir_cs     = __v_cs;
	__libc_memcpy(&__result->ics_gpregs,
	              &__self->scs_gpregs,
	              sizeof(struct gpregs32));
	return __result;
}
/* Create a new interrupt cpu-state from a given scheduler cpu state. */
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct icpustate32 *
__NOTHROW_NCX(scpustate32_user_to_icpustate32_p)(struct scpustate32 const *__restrict __self,
                                                 void *__restrict __kernel_esp) {
	struct icpustate32 *__result;
	__u32 __v_eflags = scpustate32_geteflags(__self);
#ifndef __I386_NO_VM86
	if (__v_eflags & 0x20000) {
		__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
		                                  (OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_VM86));
		__result->ics_irregs_v.ir_esp = scpustate32_getuseresp(__self);
		__result->ics_irregs_v.ir_ss  = scpustate32_getuserss(__self);
		__result->ics_irregs_v.ir_es  = __self->scs_irregs_v.ir_es16;
		__result->ics_irregs_v.ir_ds  = __self->scs_irregs_v.ir_ds16;
		__result->ics_irregs_v.ir_fs  = __self->scs_irregs_v.ir_fs16;
		__result->ics_irregs_v.ir_gs  = __self->scs_irregs_v.ir_gs16;
		__result->ics_ds              = __self->scs_sgregs.sg_ds16;
		__result->ics_es              = __self->scs_sgregs.sg_es16;
		__result->ics_fs              = __self->scs_sgregs.sg_fs16;
	} else
#endif /* !__I386_NO_VM86 */
	{
		__hybrid_assert(scpustate32_getcs(__self) & 3);
		__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
		                                  (OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_USER));
		__result->ics_irregs_u.ir_esp = scpustate32_getuseresp(__self);
		__result->ics_irregs_u.ir_ss  = scpustate32_getuserss(__self);
		__result->ics_fs = __self->scs_sgregs.sg_fs16;
		__result->ics_es = __self->scs_sgregs.sg_es16;
		__result->ics_ds = __self->scs_sgregs.sg_ds16;
	}
	__result->ics_irregs.ir_eip    = scpustate32_geteip(__self);
	__result->ics_irregs.ir_eflags = __v_eflags;
	__result->ics_irregs.ir_cs     = scpustate32_getcs(__self);
	__libc_memcpy(&__result->ics_gpregs,
	              &__self->scs_gpregs,
	              sizeof(struct gpregs32));
	return __result;
}
/* Create a duplicate of the given interrupt cpu state. */
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct scpustate32 *
__NOTHROW_NCX(scpustate32_to_scpustate32_p)(struct scpustate32 const *__restrict __self,
                                            void *__restrict __kernel_esp) {
	__size_t __result_size;
	struct scpustate32 *__result;
	if (scpustate32_isvm86(__self)) {
		__result_size = OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_VM86;
	} else if (scpustate32_isuser_novm86(__self)) {
		__result_size = OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_USER;
	} else {
		__result_size = OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_KERNEL;
	}
	__result = (struct scpustate32 *)((__byte_t *)__kernel_esp - __result_size);
	__libc_memcpy(__result, __self, __result_size);
	return __result;
}
/* Create a duplicate of the given interrupt cpu state. */
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct scpustate32 *
__NOTHROW_NCX(scpustate32_user_to_scpustate32_p)(struct scpustate32 const *__restrict __self,
                                                 void *__restrict __kernel_esp) {
	struct scpustate32 *__result;
	__u32 __v_eflags = scpustate32_geteflags(__self);
#ifndef __I386_NO_VM86
	if (__v_eflags & 0x20000) {
		__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
		                                  (OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_VM86));
		__result->scs_irregs_v.ir_esp = scpustate32_getuseresp(__self);
		__result->scs_irregs_v.ir_ss  = scpustate32_getuserss(__self);
		__result->scs_irregs_v.ir_es  = __self->scs_irregs_v.ir_es16;
		__result->scs_irregs_v.ir_ds  = __self->scs_irregs_v.ir_ds16;
		__result->scs_irregs_v.ir_fs  = __self->scs_irregs_v.ir_fs16;
		__result->scs_irregs_v.ir_gs  = __self->scs_irregs_v.ir_gs16;
	} else
#endif /* !__I386_NO_VM86 */
	{
		__hybrid_assert(scpustate32_getcs(__self) & 3);
		__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
		                                  (OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_USER));
		__result->scs_irregs_u.ir_esp = scpustate32_getuseresp(__self);
		__result->scs_irregs_u.ir_ss  = scpustate32_getuserss(__self);
	}
	__libc_memcpy(&__result->scs_sgregs,
	              &__self->scs_sgregs,
	              sizeof(struct sgregs32));
	__result->scs_irregs.ir_eip    = scpustate32_geteip(__self);
	__result->scs_irregs.ir_eflags = __v_eflags;
	__result->scs_irregs.ir_cs     = scpustate32_getcs(__self);
	__libc_memcpy(&__result->scs_gpregs,
	              &__self->scs_gpregs,
	              sizeof(struct gpregs32));
	return __result;
}
/************************************************************************/




/************************************************************************/
/* `struct ucpustate32'                                                 */
/************************************************************************/
#define ucpustate32_foreach_gpregs_elem(self) gpregs32_foreach_elem(&(self)->ucs_gpregs)
#define ucpustate32_foreach_gpregs_size(self) gpregs32_foreach_size(&(self)->ucs_gpregs)
#define ucpustate32_foreach_gpregs(self, cb)  gpregs32_foreach(&(self)->ucs_gpregs, cb)
#ifdef __I386_NO_VM86
#define ucpustate32_isvm86(self)           0
#define ucpustate32_isuser_novm86(self)    ((self)->ucs_cs16 & 3)
#define ucpustate32_isuser(self)           ((self)->ucs_cs16 & 3)
#define ucpustate32_iskernel(self)         (!((self)->ucs_cs16 & 3))
#define ucpustate32_getisa(self)           ISA_I386
#else /* __I386_NO_VM86 */
#define ucpustate32_isvm86(self)           ((self)->ucs_eflags & 0x20000)
#define ucpustate32_isuser_novm86(self)    ((self)->ucs_cs16 & 3)
#define ucpustate32_isuser(self)           (((self)->ucs_cs16 & 3) || ucpustate32_isvm86(self))
#define ucpustate32_iskernel(self)         (!((self)->ucs_cs16 & 3) && !ucpustate32_isvm86(self))
#define ucpustate32_getisa(self)           (ucpustate32_isvm86(self) ? ISA_8086 : ISA_I386)
#endif /* !__I386_NO_VM86 */
#define ucpustate32_geteip(self)           ((__u32)(self)->ucs_eip)
#define ucpustate32_seteip(self, value)    ((self)->ucs_eip = (value))
#define ucpustate32_getesp(self)           ((__u32)(self)->ucs_gpregs.gp_esp)
#define ucpustate32_setesp(self, value)    ((self)->ucs_gpregs.gp_esp = (value))
#define ucpustate32_geteflags(self)        ((__u32)(self)->ucs_eflags)
#define ucpustate32_seteflags(self, value) ((self)->ucs_eflags = (value))
#define ucpustate32_mskeflags(self, mask, flag) ((self)->ucs_eflags = ((self)->ucs_eflags & (mask)) | (flag))
#define ucpustate32_getes(self)            ((self)->ucs_sgregs.sg_es16)
#define ucpustate32_setes(self, value)     ((self)->ucs_sgregs.sg_es = (u16)(value))
#define ucpustate32_getds(self)            ((self)->ucs_sgregs.sg_ds16)
#define ucpustate32_setds(self, value)     ((self)->ucs_sgregs.sg_ds = (u16)(value))
#define ucpustate32_getcs(self)            ((self)->ucs_cs16)
#define ucpustate32_setcs(self, value)     ((self)->ucs_cs = (u16)(value))
#define ucpustate32_getss(self)            ((self)->ucs_ss16)
#define ucpustate32_setss(self, value)     ((self)->ucs_ss = (u16)(value))
#define ucpustate32_getfs(self)            ((self)->ucs_sgregs.sg_fs16)
#define ucpustate32_setfs(self, value)     ((self)->ucs_sgregs.sg_fs = (u16)(value))
#define ucpustate32_getgs(self)            ((self)->ucs_sgregs.sg_gs16)
#define ucpustate32_setgs(self, value)     ((self)->ucs_sgregs.sg_gs = (u16)(value))
#define ucpustate32_to_ucpustate32(self, result)                        \
	__libc_memcpy(__COMPILER_REQTYPE(struct ucpustate32 *, result),     \
	              __COMPILER_REQTYPE(struct ucpustate32 const *, self), \
	              sizeof(struct ucpustate32))
#if !defined(__x86_64__) && defined(__i386__)
__FORCELOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(ucpustate32_current)(struct ucpustate32 *__restrict __result) {
	__COMPILER_BARRIER();
	__asm__ __volatile__("movl %%edi, 0(%1)\n\t"
	                     "movl %%esi, 4(%1)\n\t"
	                     "movl %%ebp, 8(%1)\n\t"
	                     "movl %%esp, 12(%1)\n\t"
	                     "movl %%ebx, 16(%1)\n\t"
	                     "movl %%edx, 20(%1)\n\t"
	                     "movl %%ecx, 24(%1)\n\t"
	                     "movl %%eax, 28(%1)\n\t"
	                     "pushfl\n\t"
	                     ".cfi_adjust_cfa_offset 4\n\t"
	                     "popl 56(%1)\n\t"
	                     ".cfi_adjust_cfa_offset -4\n\t"
#if defined(__pic__) && 0 /* Can't rely on %esp being the CFI base-register */
	                     "call 991f\n\t"
	                     "991: .cfi_adjust_cfa_offset 4\n\t"
	                     "popl 60(%1)\n\t"
	                     ".cfi_adjust_cfa_offset -4"
#else /* __pic__ */
	                     "movl $991f, 60(%1)\n\t"
	                     "991:"
#endif /* !__pic__ */
	                     : "=m" /*0*/ (*__result)
	                     : "r" /*1*/ (__result));
	__result->ucs_cs           = SEGMENT_CURRENT_CODE_RPL;
	__result->ucs_ss           = SEGMENT_CURRENT_DATA_RPL;
	__result->ucs_sgregs.sg_gs = __rdgs();
	__result->ucs_sgregs.sg_fs = __rdfs();
	__result->ucs_sgregs.sg_es = __rdes();
	__result->ucs_sgregs.sg_ds = __rdds();
	__COMPILER_BARRIER();
}
#endif /* !__x86_64__ && __i386__ */
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(ucpustate32_to_kcpustate32)(struct ucpustate32 const *__restrict __self,
                                          struct kcpustate32 *__restrict __result) {
	__libc_memcpy(&__result->kcs_gpregs,
	              &__self->ucs_gpregs,
	              sizeof(struct gpregs32));
	__result->kcs_eflags = __self->ucs_eflags;
	__result->kcs_eip    = __self->ucs_eip;
}
/* NOTE: `KERNEL_ESP' should point onto the kernel-stack where the cpu-state  should
 *       be allocated, and will be initial ESP during execution (note that this last
 *       part  is specific to icpustate32/scpustate32, as the 64-bit variants do not
 *       make this distinction).
 * WARNING: The `%gs' register  is not  applied this  function, and  must therefor  be
 *          set manually by the caller  if this is the  intend (note that the  absence
 *          of the `%gs' register is what differentiates icpustate32 from scpustate32) */
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct icpustate32 *
__NOTHROW_NCX(ucpustate32_to_icpustate32_p)(struct ucpustate32 const *__restrict __self,
                                            void *__restrict __kernel_esp) {
	struct icpustate32 *__result;
	if (ucpustate32_isvm86(__self)) {
		__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
		                                  (OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_VM86));
		__result->ics_irregs_v.ir_esp = __self->ucs_gpregs.gp_esp;
		__result->ics_irregs_v.ir_ss  = __self->ucs_ss16;
		__result->ics_irregs_v.ir_es  = __self->ucs_sgregs.sg_es16;
		__result->ics_irregs_v.ir_ds  = __self->ucs_sgregs.sg_ds16;
		__result->ics_irregs_v.ir_fs  = __self->ucs_sgregs.sg_fs16;
		__result->ics_irregs_v.ir_gs  = __self->ucs_sgregs.sg_gs16;
		__result->ics_ds = SEGMENT_USER_DATA_RPL;
		__result->ics_es = SEGMENT_USER_DATA_RPL;
#ifdef __x86_64__
		__result->ics_fs = SEGMENT_USER_DATA_RPL;
#else /* __x86_64__ */
		__result->ics_fs = SEGMENT_USER_FSBASE_RPL;
#endif /* !__x86_64__ */
	} else {
		if (ucpustate32_isuser_novm86(__self)) {
			__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
			                                  (OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_USER));
			__result->ics_irregs_u.ir_esp = __self->ucs_gpregs.gp_esp;
			__result->ics_irregs_u.ir_ss  = __self->ucs_ss16;
		} else {
			__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
			                                  (OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_KERNEL));
		}
		__result->ics_ds = __self->ucs_sgregs.sg_ds16;
		__result->ics_es = __self->ucs_sgregs.sg_es16;
		__result->ics_fs = __self->ucs_sgregs.sg_fs16;
	}
	__result->ics_irregs.ir_eip    = __self->ucs_eip;
	__result->ics_irregs.ir_eflags = __self->ucs_eflags;
	__result->ics_irregs.ir_cs     = __self->ucs_cs16;
	__libc_memcpy(&__result->ics_gpregs,
	              &__self->ucs_gpregs,
	              sizeof(struct gpregs32));
	return __result;
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct scpustate32 *
__NOTHROW_NCX(ucpustate32_to_scpustate32_p)(struct ucpustate32 const *__restrict __self,
                                            void *__restrict __kernel_esp) {
	struct scpustate32 *__result;
	if (ucpustate32_isvm86(__self)) {
		__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
		                                  (OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_VM86));
		__result->scs_irregs_v.ir_esp = __self->ucs_gpregs.gp_esp;
		__result->scs_irregs_v.ir_ss  = __self->ucs_ss16;
		__result->scs_irregs_v.ir_es  = __self->ucs_sgregs.sg_es16;
		__result->scs_irregs_v.ir_ds  = __self->ucs_sgregs.sg_ds16;
		__result->scs_irregs_v.ir_fs  = __self->ucs_sgregs.sg_fs16;
		__result->scs_irregs_v.ir_gs  = __self->ucs_sgregs.sg_gs16;
		__result->scs_sgregs.sg_ds = SEGMENT_USER_DATA_RPL;
		__result->scs_sgregs.sg_es = SEGMENT_USER_DATA_RPL;
#ifdef __x86_64__
		__result->scs_sgregs.sg_fs = SEGMENT_USER_DATA_RPL;
		__result->scs_sgregs.sg_gs = SEGMENT_USER_DATA_RPL;
#else /* __x86_64__ */
		__result->scs_sgregs.sg_fs = SEGMENT_USER_FSBASE_RPL;
		__result->scs_sgregs.sg_gs = SEGMENT_USER_GSBASE_RPL;
#endif /* !__x86_64__ */
	} else {
		if (ucpustate32_isuser_novm86(__self)) {
			__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
			                                  (OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_USER));
			__result->scs_irregs_u.ir_esp = __self->ucs_gpregs.gp_esp;
			__result->scs_irregs_u.ir_ss  = __self->ucs_ss16;
		} else {
			__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
			                                  (OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_KERNEL));
		}
		__libc_memcpy(&__result->scs_sgregs,
		              &__self->ucs_sgregs,
		              sizeof(struct sgregs32));
	}
	__result->scs_irregs.ir_eip    = __self->ucs_eip;
	__result->scs_irregs.ir_eflags = __self->ucs_eflags;
	__result->scs_irregs.ir_cs     = __self->ucs_cs16;
	__libc_memcpy(&__result->scs_gpregs,
	              &__self->ucs_gpregs,
	              sizeof(struct gpregs32));
	return __result;
}
/************************************************************************/




/************************************************************************/
/* `struct fcpustate32'                                                 */
/************************************************************************/
#define fcpustate32_foreach_gpregs(self, cb)       \
	do {                                           \
		gpregs32_foreach(&(self)->fcs_gpregs, cb); \
		cb((self)->fcs_gdt.dt_base);               \
		cb((self)->fcs_idt.dt_base);               \
	}	__WHILE0
#ifdef __I386_NO_VM86
#define fcpustate32_isvm86(self)           0
#define fcpustate32_isuser_novm86(self)    ((self)->fcs_sgregs.sg_cs16 & 3)
#define fcpustate32_isuser(self)           ((self)->fcs_sgregs.sg_cs16 & 3)
#define fcpustate32_iskernel(self)         (!((self)->fcs_sgregs.sg_cs16 & 3))
#define fcpustate32_getisa(self)           ISA_I386
#else /* __I386_NO_VM86 */
#define fcpustate32_isvm86(self)           ((self)->fcs_eflags & 0x20000)
#define fcpustate32_isuser_novm86(self)    ((self)->fcs_sgregs.sg_cs16 & 3)
#define fcpustate32_isuser(self)           (((self)->fcs_sgregs.sg_cs16 & 3) || fcpustate32_isvm86(self))
#define fcpustate32_iskernel(self)         (!((self)->fcs_sgregs.sg_cs16 & 3) && !fcpustate32_isvm86(self))
#define fcpustate32_getisa(self)           (fcpustate32_isvm86(self) ? ISA_8086 : ISA_I386)
#endif /* !__I386_NO_VM86 */
#define fcpustate32_geteip(self)           ((__u32)(self)->fcs_eip)
#define fcpustate32_seteip(self, value)    ((self)->fcs_eip = (value))
#define fcpustate32_getesp(self)           ((__u32)(self)->fcs_gpregs.gp_esp)
#define fcpustate32_setesp(self, value)    ((self)->fcs_gpregs.gp_esp = (value))
#define fcpustate32_geteflags(self)        ((__u32)(self)->fcs_eflags)
#define fcpustate32_seteflags(self, value) ((self)->fcs_eflags = (value))
#define fcpustate32_mskeflags(self, mask, flag) ((self)->fcs_eflags = ((self)->fcs_eflags & (mask)) | (flag))
#define fcpustate32_to_fcpustate32(self, result)                        \
	__libc_memcpy(__COMPILER_REQTYPE(struct fcpustate32 *, result),     \
	              __COMPILER_REQTYPE(struct fcpustate32 const *, self), \
	              sizeof(struct fcpustate32))
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(fcpustate32_to_lcpustate32)(struct fcpustate32 const *__restrict __self,
                                          struct lcpustate32 *__restrict __result) {
	__result->lcs_edi = __self->fcs_gpregs.gp_edi;
	__result->lcs_esi = __self->fcs_gpregs.gp_esi;
	__result->lcs_ebp = __self->fcs_gpregs.gp_ebp;
	__result->lcs_esp = __self->fcs_gpregs.gp_esp;
	__result->lcs_ebx = __self->fcs_gpregs.gp_ebx;
	__result->lcs_eip = __self->fcs_eip;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(fcpustate32_to_kcpustate32)(struct fcpustate32 const *__restrict __self,
                                          struct kcpustate32 *__restrict __result) {
	__libc_memcpy(&__result->kcs_gpregs,
	              &__self->fcs_gpregs,
	              sizeof(struct gpregs32));
	__result->kcs_eip    = __self->fcs_eip;
	__result->kcs_eflags = __self->fcs_eflags;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(fcpustate32_to_ucpustate32)(struct fcpustate32 const *__restrict __self,
                                          struct ucpustate32 *__restrict __result) {
	__libc_memcpy(&__result->ucs_gpregs,
	              &__self->fcs_gpregs,
	              sizeof(struct gpregs32));
	__result->ucs_eip          = __self->fcs_eip;
	__result->ucs_eflags       = __self->fcs_eflags;
	__result->ucs_sgregs.sg_gs = __self->fcs_sgregs.sg_gs;
	__result->ucs_sgregs.sg_fs = __self->fcs_sgregs.sg_fs;
	__result->ucs_sgregs.sg_es = __self->fcs_sgregs.sg_es;
	__result->ucs_sgregs.sg_ds = __self->fcs_sgregs.sg_ds;
	__result->ucs_cs           = __self->fcs_sgregs.sg_cs;
	__result->ucs_ss           = __self->fcs_sgregs.sg_ss;
}

/* Assign fields from `data' (but leave fields not defined by `data' as unchanged) */
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(fcpustate32_assign_ucpustate32)(struct fcpustate32 *__restrict __self,
                                              struct ucpustate32 const *__restrict __data) {
	__libc_memcpy(&__self->fcs_gpregs,
	              &__data->ucs_gpregs,
	              sizeof(struct gpregs32));
	__self->fcs_eip          = __data->ucs_eip;
	__self->fcs_eflags       = __data->ucs_eflags;
	__self->fcs_sgregs.sg_gs = __data->ucs_sgregs.sg_gs;
	__self->fcs_sgregs.sg_fs = __data->ucs_sgregs.sg_fs;
	__self->fcs_sgregs.sg_es = __data->ucs_sgregs.sg_es;
	__self->fcs_sgregs.sg_ds = __data->ucs_sgregs.sg_ds;
	__self->fcs_sgregs.sg_cs = __data->ucs_cs;
	__self->fcs_sgregs.sg_ss = __data->ucs_ss;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(fcpustate32_assign_lcpustate32)(struct fcpustate32 *__restrict __self,
                                              struct lcpustate32 const *__restrict __data) {
	__self->fcs_gpregs.gp_edi = __data->lcs_edi;
	__self->fcs_gpregs.gp_esi = __data->lcs_esi;
	__self->fcs_gpregs.gp_ebp = __data->lcs_ebp;
	__self->fcs_gpregs.gp_esp = __data->lcs_esp;
	__self->fcs_gpregs.gp_ebx = __data->lcs_ebx;
	__self->fcs_eip           = __data->lcs_eip;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(fcpustate32_assign_kcpustate32)(struct fcpustate32 *__restrict __self,
                                              struct kcpustate32 const *__restrict __data) {
	__libc_memcpy(&__self->fcs_gpregs,
	              &__data->kcs_gpregs,
	              sizeof(struct gpregs32));
	__self->fcs_eflags = __data->kcs_eflags;
	__self->fcs_eip    = __data->kcs_eip;
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(fcpustate32_assign_scpustate32)(struct fcpustate32 *__restrict __self,
                                              struct scpustate32 const *__restrict __data) {
	__libc_memcpy(&__self->fcs_gpregs,
	              &__data->scs_gpregs,
	              sizeof(struct gpregs32));
	__self->fcs_eip          = scpustate32_geteip(__data);
	__self->fcs_eflags       = scpustate32_geteflags(__data);
	__self->fcs_sgregs.sg_cs = scpustate32_getcs(__data);
#ifndef __I386_NO_VM86
	if (__self->fcs_eflags & 0x20000) {
		__self->fcs_sgregs.sg_gs  = __data->scs_irregs_v.ir_gs16;
		__self->fcs_sgregs.sg_fs  = __data->scs_irregs_v.ir_fs16;
		__self->fcs_sgregs.sg_es  = __data->scs_irregs_v.ir_es16;
		__self->fcs_sgregs.sg_ds  = __data->scs_irregs_v.ir_ds16;
		__self->fcs_sgregs.sg_ss  = scpustate32_getuserss(__data);
		__self->fcs_gpregs.gp_esp = scpustate32_getuseresp(__data);
	} else
#endif /* !__I386_NO_VM86 */
	{
		if (__self->fcs_sgregs.sg_cs & 3) {
			__self->fcs_sgregs.sg_ss  = scpustate32_getuserss(__data);
			__self->fcs_gpregs.gp_esp = scpustate32_getuseresp(__data);
		} else {
			__self->fcs_sgregs.sg_ss  = scpustate32_getkernelss(__data);
			__self->fcs_gpregs.gp_esp = scpustate32_getkernelesp(__data);
		}
		__self->fcs_sgregs.sg_gs = __data->scs_sgregs.sg_gs16;
		__self->fcs_sgregs.sg_fs = __data->scs_sgregs.sg_fs16;
		__self->fcs_sgregs.sg_es = __data->scs_sgregs.sg_es16;
		__self->fcs_sgregs.sg_ds = __data->scs_sgregs.sg_ds16;
	}
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(fcpustate32_assign_icpustate32_ex)(struct fcpustate32 *__restrict __self,
                                                 struct icpustate32 const *__restrict __data,
                                                 __u16 __v_nonvm86_gs) {
	__libc_memcpy(&__self->fcs_gpregs,
	              &__data->ics_gpregs,
	              sizeof(struct gpregs32));
	__self->fcs_eip          = icpustate32_geteip(__data);
	__self->fcs_eflags       = icpustate32_geteflags(__data);
	__self->fcs_sgregs.sg_cs = icpustate32_getcs(__data);
#ifndef __I386_NO_VM86
	if (__self->fcs_eflags & 0x20000) {
		__self->fcs_sgregs.sg_gs  = __data->ics_irregs_v.ir_gs16;
		__self->fcs_sgregs.sg_fs  = __data->ics_irregs_v.ir_fs16;
		__self->fcs_sgregs.sg_es  = __data->ics_irregs_v.ir_es16;
		__self->fcs_sgregs.sg_ds  = __data->ics_irregs_v.ir_ds16;
		__self->fcs_sgregs.sg_ss  = icpustate32_getuserss(__data);
		__self->fcs_gpregs.gp_esp = icpustate32_getuseresp(__data);
	} else
#endif /* !__I386_NO_VM86 */
	{
		if (__self->fcs_sgregs.sg_cs & 3) {
			__self->fcs_sgregs.sg_ss  = icpustate32_getuserss(__data);
			__self->fcs_gpregs.gp_esp = icpustate32_getuseresp(__data);
		} else {
			__self->fcs_sgregs.sg_ss  = icpustate32_getkernelss(__data);
			__self->fcs_gpregs.gp_esp = icpustate32_getkernelesp(__data);
		}
		__self->fcs_sgregs.sg_gs = __v_nonvm86_gs;
		__self->fcs_sgregs.sg_fs = __data->ics_fs16;
		__self->fcs_sgregs.sg_es = __data->ics_es16;
		__self->fcs_sgregs.sg_ds = __data->ics_ds16;
	}
}
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(fcpustate32_assign_icpustate32)(struct fcpustate32 *__restrict __self,
                                              struct icpustate32 const *__restrict __data) {
	fcpustate32_assign_icpustate32_ex(__self, __data, __rdgs());
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct icpustate32 *
__NOTHROW_NCX(fcpustate32_to_icpustate32_p)(struct fcpustate32 const *__restrict __self,
                                            void *__restrict __kernel_esp) {
	struct icpustate32 *__result;
	if (fcpustate32_isvm86(__self)) {
		__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
		                                  (OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_VM86));
		__result->ics_irregs_v.ir_esp = __self->fcs_gpregs.gp_esp;
		__result->ics_irregs_v.ir_ss  = __self->fcs_sgregs.sg_ss16;
		__result->ics_irregs_v.ir_es  = __self->fcs_sgregs.sg_es16;
		__result->ics_irregs_v.ir_ds  = __self->fcs_sgregs.sg_ds16;
		__result->ics_irregs_v.ir_fs  = __self->fcs_sgregs.sg_fs16;
		__result->ics_irregs_v.ir_gs  = __self->fcs_sgregs.sg_gs16;
		__result->ics_ds = SEGMENT_USER_DATA_RPL;
		__result->ics_es = SEGMENT_USER_DATA_RPL;
#ifdef __x86_64__
		__result->ics_fs = SEGMENT_USER_DATA_RPL;
#else /* __x86_64__ */
		__result->ics_fs = SEGMENT_USER_FSBASE_RPL;
#endif /* !__x86_64__ */
	} else {
		if (fcpustate32_isuser_novm86(__self)) {
			__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
			                                  (OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_USER));
			__result->ics_irregs_u.ir_esp = __self->fcs_gpregs.gp_esp;
			__result->ics_irregs_u.ir_ss  = __self->fcs_sgregs.sg_ss16;
		} else {
			__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
			                                  (OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_KERNEL));
		}
		__result->ics_ds = __self->fcs_sgregs.sg_ds16;
		__result->ics_es = __self->fcs_sgregs.sg_es16;
		__result->ics_fs = __self->fcs_sgregs.sg_fs16;
	}
	__result->ics_irregs.ir_eip    = __self->fcs_eip;
	__result->ics_irregs.ir_eflags = __self->fcs_eflags;
	__result->ics_irregs.ir_cs     = __self->fcs_sgregs.sg_cs16;
	__libc_memcpy(&__result->ics_gpregs,
	              &__self->fcs_gpregs,
	              sizeof(struct gpregs32));
	return __result;
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) struct scpustate32 *
__NOTHROW_NCX(fcpustate32_to_scpustate32_p)(struct fcpustate32 const *__restrict __self,
                                            void *__restrict __kernel_esp) {
	struct scpustate32 *__result;
	if (fcpustate32_isvm86(__self)) {
		__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
		                                  (OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_VM86));
		__result->scs_irregs_v.ir_esp = __self->fcs_gpregs.gp_esp;
		__result->scs_irregs_v.ir_ss  = __self->fcs_sgregs.sg_ss16;
		__result->scs_irregs_v.ir_es  = __self->fcs_sgregs.sg_es16;
		__result->scs_irregs_v.ir_ds  = __self->fcs_sgregs.sg_ds16;
		__result->scs_irregs_v.ir_fs  = __self->fcs_sgregs.sg_fs16;
		__result->scs_irregs_v.ir_gs  = __self->fcs_sgregs.sg_gs16;
		__result->scs_sgregs.sg_ds = SEGMENT_USER_DATA_RPL;
		__result->scs_sgregs.sg_es = SEGMENT_USER_DATA_RPL;
#ifdef __x86_64__
		__result->scs_sgregs.sg_fs = SEGMENT_USER_DATA_RPL;
		__result->scs_sgregs.sg_gs = SEGMENT_USER_DATA_RPL;
#else /* __x86_64__ */
		__result->scs_sgregs.sg_fs = SEGMENT_USER_FSBASE_RPL;
		__result->scs_sgregs.sg_gs = SEGMENT_USER_GSBASE_RPL;
#endif /* !__x86_64__ */
	} else {
		if (fcpustate32_isuser_novm86(__self)) {
			__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
			                                  (OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_USER));
			__result->scs_irregs_u.ir_esp = __self->fcs_gpregs.gp_esp;
			__result->scs_irregs_u.ir_ss  = __self->fcs_sgregs.sg_ss16;
		} else {
			__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
			                                  (OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_KERNEL));
		}
		__result->scs_sgregs.sg_gs = __self->fcs_sgregs.sg_gs16;
		__result->scs_sgregs.sg_fs = __self->fcs_sgregs.sg_fs16;
		__result->scs_sgregs.sg_es = __self->fcs_sgregs.sg_es16;
		__result->scs_sgregs.sg_ds = __self->fcs_sgregs.sg_ds16;
	}
	__result->scs_irregs.ir_eip    = __self->fcs_eip;
	__result->scs_irregs.ir_eflags = __self->fcs_eflags;
	__result->scs_irregs.ir_cs     = __self->fcs_sgregs.sg_cs16;
	__libc_memcpy(&__result->scs_gpregs,
	              &__self->fcs_gpregs,
	              sizeof(struct gpregs32));
	return __result;
}
/************************************************************************/







#ifndef __x86_64__
#define gpregs_foreach_elem                 gpregs32_foreach_elem
#define gpregs_foreach_size                 gpregs32_foreach_size
#define gpregs_foreach                      gpregs32_foreach
#define gpregs_getpdi                       gpregs32_getedi
#define gpregs_setpdi                       gpregs32_setedi
#define gpregs_getpsi                       gpregs32_getesi
#define gpregs_setpsi                       gpregs32_setesi
#define gpregs_getpbp                       gpregs32_getebp
#define gpregs_setpbp                       gpregs32_setebp
#define gpregs_getpsp                       gpregs32_getesp
#define gpregs_setpsp                       gpregs32_setesp
#define gpregs_getpbx                       gpregs32_getebx
#define gpregs_setpbx                       gpregs32_setebx
#define gpregs_getpdx                       gpregs32_getedx
#define gpregs_setpdx                       gpregs32_setedx
#define gpregs_getpcx                       gpregs32_getecx
#define gpregs_setpcx                       gpregs32_setecx
#define gpregs_getpax                       gpregs32_geteax
#define gpregs_setpax                       gpregs32_seteax
#define gpregs_to_gpregs                    gpregs32_to_gpregs32
#define gpregs_to_gpregs32                  gpregs32_to_gpregs32
#define gpregs32_to_gpregs                  gpregs32_to_gpregs32
#define gpregs_to_gpregsnsp                 gpregs32_to_gpregs32
#define gpregs_to_gpregsnsp32               gpregs32_to_gpregs32
#define gpregs32_to_gpregsnsp               gpregs32_to_gpregs32
#define gpregs_getreturnbool                gpregs32_getreturn32
#define gpregs_getreturn                    gpregs32_getreturn32
#define gpregs_getreturn32                  gpregs32_getreturn32
#define gpregs_getreturn64                  gpregs32_getreturn64
#define gpregs_setreturnbool                gpregs32_setreturn32
#define gpregs_setreturn                    gpregs32_setreturn32
#define gpregs_setreturn32                  gpregs32_setreturn32
#define gpregs_setreturn64                  gpregs32_setreturn64

#define irregs_isvm86(self)                 irregs32_isvm86(self)
#define irregs_isuser_novm86(self)          irregs32_isuser_novm86(self)
#define irregs_isuser(self)                 irregs32_isuser(self)
#define irregs_iskernel(self)               irregs32_iskernel(self)
#define irregs_is32bit(self)                1
#define irregs_is64bit(self)                0
#define irregs_isnative(self)               1
#define irregs_iscompat(self)               0
#define irregs_getisa(self)                 irregs32_getisa(self)
#define irregs_getpreemption                irregs32_getpreemption
#define irregs_setpreemption                irregs32_setpreemption
#define irregs_getpip                       irregs32_geteip
#define irregs_getpc                        (__byte_t const *)irregs32_geteip
#define irregs_setpip                       irregs32_seteip
#define irregs_setpc(self, pc)              irregs32_seteip(self, (__u32)__COMPILER_REQTYPE(void const *, pc))
#define irregs_getcs                        irregs32_getcs
#define irregs_setcs                        irregs32_setcs
#define irregs_getpflags                    irregs32_geteflags
#define irregs_setpflags                    irregs32_seteflags
#define irregs_mskpflags                    irregs32_mskeflags
#define irregs_getpsp                       irregs32_getesp
#define irregs_getsp                        (__byte_t *)irregs32_getesp
#define irregs_getuserpsp                   irregs32_getuseresp
#define irregs_getusersp                    (__byte_t *)irregs32_getuseresp
#define irregs_setuserpsp                   irregs32_setuseresp
#define irregs_setusersp(self, sp)          irregs32_setuseresp(self, (__u32)__COMPILER_REQTYPE(void *, sp))
#define irregs_getuserss                    irregs32_getuserss
#define irregs_setuserss                    irregs32_setuserss
#define irregs_getkernelpsp                 irregs32_getkernelesp
#define irregs_getkernelsp                  (__byte_t *)irregs32_getkernelesp
#define irregs_getkernelss                  irregs32_getkernelss
#define irregs_getss                        irregs32_getss
#define irregs_trysetss                     irregs32_trysetss
#define irregs_trysetuserss                 irregs32_trysetuserss
#define irregs_trysetpsp                    irregs32_trysetesp
#define irregs_trysetsp(self, sp)           irregs32_trysetesp(self, (__u32)__COMPILER_REQTYPE(void *, sp))
#define irregs_sizeof                       irregs32_sizeof
#define irregs_getvm86ds                    irregs32_getvm86ds
#define irregs_setvm86ds                    irregs32_setvm86ds
#define irregs_getvm86es                    irregs32_getvm86es
#define irregs_setvm86es                    irregs32_setvm86es
#define irregs_getvm86fs                    irregs32_getvm86fs
#define irregs_setvm86fs                    irregs32_setvm86fs
#define irregs_getvm86gs                    irregs32_getvm86gs
#define irregs_setvm86gs                    irregs32_setvm86gs
#define irregs_getds_ex                     irregs32_getds_ex
#define irregs_trysetds_ex                  irregs32_trysetds_ex
#define irregs_getes_ex                     irregs32_getes_ex
#define irregs_trysetes_ex                  irregs32_trysetes_ex
#define irregs_getfs_ex                     irregs32_getfs_ex
#define irregs_trysetfs_ex                  irregs32_trysetfs_ex
#define irregs_getgs_ex                     irregs32_getgs_ex
#define irregs_trysetgs_ex                  irregs32_trysetgs_ex
#define irregs_getds                        irregs32_getds
#define irregs_trysetds                     irregs32_trysetds
#define irregs_getes                        irregs32_getes
#define irregs_trysetes                     irregs32_trysetes
#define irregs_getfs                        irregs32_getfs
#define irregs_trysetfs                     irregs32_trysetfs
#define irregs_getgs                        irregs32_getgs
#define irregs_trysetgs                     irregs32_trysetgs

#define lcpustate_foreach_gpregs_elem       lcpustate32_foreach_gpregs_elem
#define lcpustate_foreach_gpregs_size       lcpustate32_foreach_gpregs_size
#define lcpustate_foreach_gpregs            lcpustate32_foreach_gpregs
#define lcpustate_getisa(self)              ISA_I386
#define lcpustate_getpip                    lcpustate32_geteip
#define lcpustate_getpc                     (__byte_t const *)lcpustate32_geteip
#define lcpustate_setpip                    lcpustate32_seteip
#define lcpustate_setpc(self, pc)           lcpustate32_seteip(self, (__u32)__COMPILER_REQTYPE(void const *, pc))
#define lcpustate_getpsp                    lcpustate32_getesp
#define lcpustate_getsp                     (__byte_t *)lcpustate32_getesp
#define lcpustate_setpsp                    lcpustate32_setesp
#define lcpustate_setsp(self, sp)           lcpustate32_setesp(self, (__u32)__COMPILER_REQTYPE(void *, sp))
#define lcpustate_to_lcpustate              lcpustate32_to_lcpustate32
#define lcpustate_to_lcpustate32            lcpustate32_to_lcpustate32
#define lcpustate32_to_lcpustate            lcpustate32_to_lcpustate32
#define lcpustate_current                   lcpustate32_current
#define lcpustate_to_gpregs_ex              lcpustate32_to_gpregs32_ex
#define lcpustate_to_gpregs32_ex            lcpustate32_to_gpregs32_ex
#define lcpustate32_to_gpregs_ex            lcpustate32_to_gpregs32_ex
#define lcpustate_to_gpregs                 lcpustate32_to_gpregs32
#define lcpustate_to_gpregs32               lcpustate32_to_gpregs32
#define lcpustate32_to_gpregs               lcpustate32_to_gpregs32
#define lcpustate_to_ucpustate_ex           lcpustate32_to_ucpustate32_ex
#define lcpustate_to_ucpustate32_ex         lcpustate32_to_ucpustate32_ex
#define lcpustate32_to_ucpustate_ex         lcpustate32_to_ucpustate32_ex
#define lcpustate_to_ucpustate              lcpustate32_to_ucpustate32
#define lcpustate_to_ucpustate32            lcpustate32_to_ucpustate32
#define lcpustate32_to_ucpustate            lcpustate32_to_ucpustate32
#define lcpustate_to_kcpustate_ex           lcpustate32_to_kcpustate32_ex
#define lcpustate_to_kcpustate32_ex         lcpustate32_to_kcpustate32_ex
#define lcpustate32_to_kcpustate_ex         lcpustate32_to_kcpustate32_ex
#define lcpustate_to_kcpustate              lcpustate32_to_kcpustate32
#define lcpustate_to_kcpustate32            lcpustate32_to_kcpustate32
#define lcpustate32_to_kcpustate            lcpustate32_to_kcpustate32

#define kcpustate_foreach_gpregs_elem       kcpustate32_foreach_gpregs_elem
#define kcpustate_foreach_gpregs_size       kcpustate32_foreach_gpregs_size
#define kcpustate_foreach_gpregs            kcpustate32_foreach_gpregs
#define kcpustate_getisa(self)              ISA_I386
#define kcpustate_getpip                    kcpustate32_geteip
#define kcpustate_getpc                     (__byte_t const *)kcpustate32_geteip
#define kcpustate_setpip                    kcpustate32_seteip
#define kcpustate_setpc(self, pc)           kcpustate32_seteip(self, (__u32)__COMPILER_REQTYPE(void const *, pc))
#define kcpustate_getpsp                    kcpustate32_getesp
#define kcpustate_getsp                     (__byte_t *)kcpustate32_getesp
#define kcpustate_setpsp                    kcpustate32_setesp
#define kcpustate_setsp(self, sp)           kcpustate32_setesp(self, (__u32)__COMPILER_REQTYPE(void *, sp))
#define kcpustate_getpflags                 kcpustate32_geteflags
#define kcpustate_setpflags                 kcpustate32_seteflags
#define kcpustate_mskpflags                 kcpustate32_mskeflags
#define kcpustate_to_kcpustate              kcpustate32_to_kcpustate32
#define kcpustate_to_kcpustate32            kcpustate32_to_kcpustate32
#define kcpustate32_to_kcpustate            kcpustate32_to_kcpustate32
#define kcpustate_to_ucpustate_ex           kcpustate32_to_ucpustate32_ex
#define kcpustate_to_ucpustate32_ex         kcpustate32_to_ucpustate32_ex
#define kcpustate32_to_ucpustate_ex         kcpustate32_to_ucpustate32_ex
#define kcpustate_to_ucpustate              kcpustate32_to_ucpustate32
#define kcpustate_to_ucpustate32            kcpustate32_to_ucpustate32
#define kcpustate32_to_ucpustate            kcpustate32_to_ucpustate32
#define kcpustate_to_lcpustate              kcpustate32_to_lcpustate32
#define kcpustate_to_lcpustate32            kcpustate32_to_lcpustate32
#define kcpustate32_to_lcpustate            kcpustate32_to_lcpustate32
#define kcpustate_to_scpustate_p_ex         kcpustate32_to_scpustate32_p_ex
#define kcpustate_to_scpustate32_p_ex       kcpustate32_to_scpustate32_p_ex
#define kcpustate32_to_scpustate_p_ex       kcpustate32_to_scpustate32_p_ex
#define kcpustate_to_scpustate_p            kcpustate32_to_scpustate32_p
#define kcpustate_to_scpustate32_p          kcpustate32_to_scpustate32_p
#define kcpustate32_to_scpustate_p          kcpustate32_to_scpustate32_p
#define kcpustate_to_icpustate_p_ex         kcpustate32_to_icpustate32_p_ex
#define kcpustate_to_icpustate32_p_ex       kcpustate32_to_icpustate32_p_ex
#define kcpustate32_to_icpustate_p_ex       kcpustate32_to_icpustate32_p_ex
#define kcpustate_to_icpustate_p            kcpustate32_to_icpustate32_p
#define kcpustate_to_icpustate32_p          kcpustate32_to_icpustate32_p
#define kcpustate32_to_icpustate_p          kcpustate32_to_icpustate32_p
#define kcpustate_getreturnbool(self)       gpregs_getreturnbool(&(self)->kcs_gpregs)
#define kcpustate_getreturn(self)           gpregs_getreturn(&(self)->kcs_gpregs)
#define kcpustate_getreturn32(self)         gpregs_getreturn32(&(self)->kcs_gpregs)
#define kcpustate_getreturn64(self)         gpregs_getreturn64(&(self)->kcs_gpregs)
#define kcpustate_setreturnbool(self, v)    gpregs_setreturnbool(&(self)->kcs_gpregs, v)
#define kcpustate_setreturn(self, v)        gpregs_setreturn(&(self)->kcs_gpregs, v)
#define kcpustate_setreturn32(self, v)      gpregs_setreturn32(&(self)->kcs_gpregs, v)
#define kcpustate_setreturn64(self, v)      gpregs_setreturn64(&(self)->kcs_gpregs, v)

#define icpustate_foreach_gpregs            icpustate32_foreach_gpregs
#define icpustate_getisa                    icpustate32_getisa
#define icpustate_getpip                    icpustate32_geteip
#define icpustate_getpc                     (__byte_t const *)icpustate32_geteip
#define icpustate_setpip                    icpustate32_seteip
#define icpustate_setpc(self, pc)           icpustate32_seteip(self, (__u32)__COMPILER_REQTYPE(void const *, pc))
#define icpustate_getpsp                    icpustate32_getesp
#define icpustate_getsp                     (__byte_t *)icpustate32_getesp
#define icpustate_trysetpsp                 icpustate32_trysetesp
#define icpustate_trysetsp(self, sp)        icpustate32_trysetesp(self, (__u32)__COMPILER_REQTYPE(void *, sp))
#define icpustate_setpsp_p                  icpustate32_setesp_p
#define icpustate_setsp_p(self, sp)         icpustate32_setesp_p(self, (__u32)__COMPILER_REQTYPE(void *, sp))
#define icpustate_isvm86                    icpustate32_isvm86
#define icpustate_isuser_novm86             icpustate32_isuser_novm86
#define icpustate_isuser                    icpustate32_isuser
#define icpustate_iskernel                  icpustate32_iskernel
#define icpustate_is32bit(self)             1
#define icpustate_is64bit(self)             0
#define icpustate_isnative(self)            1
#define icpustate_iscompat(self)            0
#define icpustate_getpreemption             icpustate32_getpreemption
#define icpustate_setpreemption             icpustate32_setpreemption
#define icpustate_getuserpsp                icpustate32_getuseresp
#define icpustate_getusersp                 (__byte_t *)icpustate32_getuseresp
#define icpustate_setuserpsp                icpustate32_setuseresp
#define icpustate_setusersp(self, sp)       icpustate32_setuseresp(self, (__u32)__COMPILER_REQTYPE(void *, sp))
#define icpustate_getuserss                 icpustate32_getuserss
#define icpustate_setuserss                 icpustate32_setuserss
#define icpustate_getkernelss               icpustate32_getkernelss
#define icpustate_getkernelpsp              icpustate32_getkernelesp
#define icpustate_getkernelsp               (__byte_t *)icpustate32_getkernelesp
#define icpustate_getds                     icpustate32_getds
#define icpustate_setds                     icpustate32_setds
#define icpustate_getes                     icpustate32_getes
#define icpustate_setes                     icpustate32_setes
#define icpustate_getfs                     icpustate32_getfs
#define icpustate_setfs                     icpustate32_setfs
#define icpustate_getgs_ex                  icpustate32_getgs_ex
#define icpustate_getgs                     icpustate32_getgs
#define icpustate_setgs                     icpustate32_setgs
#define icpustate_trysetgs                  icpustate32_trysetgs
#define icpustate_getds_novm86              icpustate32_getds_novm86
#define icpustate_setds_novm86              icpustate32_setds_novm86
#define icpustate_getes_novm86              icpustate32_getes_novm86
#define icpustate_setes_novm86              icpustate32_setes_novm86
#define icpustate_getfs_novm86              icpustate32_getfs_novm86
#define icpustate_setfs_novm86              icpustate32_setfs_novm86
#define icpustate_getgs_novm86              icpustate32_getgs_novm86
#define icpustate_setgs_novm86              icpustate32_setgs_novm86
#define icpustate_getpflags                 icpustate32_geteflags
#define icpustate_setpflags                 icpustate32_seteflags
#define icpustate_mskpflags                 icpustate32_mskeflags
#define icpustate_getcs                     icpustate32_getcs
#define icpustate_setcs                     icpustate32_setcs
#define icpustate_getss                     icpustate32_getss
#define icpustate_trysetss                  icpustate32_trysetss
#define icpustate_trysetuserss              icpustate32_trysetuserss
#define icpustate_sizeof                    icpustate32_sizeof
#define icpustate_to_ucpustate_ex           icpustate32_to_ucpustate32_ex
#define icpustate_to_ucpustate32_ex         icpustate32_to_ucpustate32_ex
#define icpustate32_to_ucpustate_ex         icpustate32_to_ucpustate32_ex
#define icpustate_to_ucpustate              icpustate32_to_ucpustate32
#define icpustate_to_ucpustate32            icpustate32_to_ucpustate32
#define icpustate32_to_ucpustate            icpustate32_to_ucpustate32
#define icpustate_user_to_ucpustate_ex      icpustate32_user_to_ucpustate32_ex
#define icpustate_user_to_ucpustate32_ex    icpustate32_user_to_ucpustate32_ex
#define icpustate32_user_to_ucpustate_ex    icpustate32_user_to_ucpustate32_ex
#define icpustate_user_to_ucpustate         icpustate32_user_to_ucpustate32
#define icpustate_user_to_ucpustate32       icpustate32_user_to_ucpustate32
#define icpustate32_user_to_ucpustate       icpustate32_user_to_ucpustate32
#define icpustate_to_kcpustate              icpustate32_to_kcpustate32
#define icpustate_to_kcpustate32            icpustate32_to_kcpustate32
#define icpustate32_to_kcpustate            icpustate32_to_kcpustate32
#define icpustate_user_to_kcpustate         icpustate32_user_to_kcpustate32
#define icpustate_user_to_kcpustate32       icpustate32_user_to_kcpustate32
#define icpustate32_user_to_kcpustate       icpustate32_user_to_kcpustate32
#define icpustate_to_scpustate_p_ex         icpustate32_to_scpustate32_p_ex
#define icpustate_to_scpustate32_p_ex       icpustate32_to_scpustate32_p_ex
#define icpustate32_to_scpustate_p_ex       icpustate32_to_scpustate32_p_ex
#define icpustate_user_to_scpustate_p_ex    icpustate32_user_to_scpustate32_p_ex
#define icpustate_user_to_scpustate32_p_ex  icpustate32_user_to_scpustate32_p_ex
#define icpustate32_user_to_scpustate_p_ex  icpustate32_user_to_scpustate32_p_ex
#define icpustate_to_scpustate_p            icpustate32_to_scpustate32_p
#define icpustate_to_scpustate32_p          icpustate32_to_scpustate32_p
#define icpustate32_to_scpustate_p          icpustate32_to_scpustate32_p
#define icpustate_user_to_scpustate_p       icpustate32_user_to_scpustate32_p
#define icpustate_user_to_scpustate32_p     icpustate32_user_to_scpustate32_p
#define icpustate32_user_to_scpustate_p     icpustate32_user_to_scpustate32_p
#define icpustate_to_icpustate_p            icpustate32_to_icpustate32_p
#define icpustate_to_icpustate32_p          icpustate32_to_icpustate32_p
#define icpustate32_to_icpustate_p          icpustate32_to_icpustate32_p
#define icpustate_user_to_icpustate_p       icpustate32_user_to_icpustate32_p
#define icpustate_user_to_icpustate32_p     icpustate32_user_to_icpustate32_p
#define icpustate32_user_to_icpustate_p     icpustate32_user_to_icpustate32_p
#define icpustate_getreturnbool(self)       gpregs_getreturnbool(&(self)->ics_gpregs)
#define icpustate_getreturn(self)           gpregs_getreturn(&(self)->ics_gpregs)
#define icpustate_getreturn32(self)         gpregs_getreturn32(&(self)->ics_gpregs)
#define icpustate_getreturn64(self)         gpregs_getreturn64(&(self)->ics_gpregs)
#define icpustate_setreturnbool(self, v)    gpregs_setreturnbool(&(self)->ics_gpregs, v)
#define icpustate_setreturn(self, v)        gpregs_setreturn(&(self)->ics_gpregs, v)
#define icpustate_setreturn32(self, v)      gpregs_setreturn32(&(self)->ics_gpregs, v)
#define icpustate_setreturn64(self, v)      gpregs_setreturn64(&(self)->ics_gpregs, v)

#define scpustate_foreach_gpregs            scpustate32_foreach_gpregs
#define scpustate_getisa                    scpustate32_getisa
#define scpustate_getpip                    scpustate32_geteip
#define scpustate_getpc                     (__byte_t const *)scpustate32_geteip
#define scpustate_setpip                    scpustate32_seteip
#define scpustate_setpc(self, pc)           scpustate32_seteip(self, (__u32)__COMPILER_REQTYPE(void const *, pc))
#define scpustate_getpsp                    scpustate32_getesp
#define scpustate_getsp                     (__byte_t *)scpustate32_getesp
#define scpustate_trysetpsp                 scpustate32_trysetesp
#define scpustate_trysetsp(self, sp)        scpustate32_trysetesp(self, (__u32)__COMPILER_REQTYPE(void *, sp))
#define scpustate_setpsp_p                  scpustate32_setesp_p
#define scpustate_setsp_p(self, sp)         scpustate32_setesp_p(self, (__u32)__COMPILER_REQTYPE(void *, sp))
#define scpustate_isvm86                    scpustate32_isvm86
#define scpustate_isuser_novm86             scpustate32_isuser_novm86
#define scpustate_isuser                    scpustate32_isuser
#define scpustate_iskernel                  scpustate32_iskernel
#define scpustate_is32bit(self)             1
#define scpustate_is64bit(self)             0
#define scpustate_isnative(self)            1
#define scpustate_iscompat(self)            0
#define scpustate_getpreemption             scpustate32_getpreemption
#define scpustate_setpreemption             scpustate32_setpreemption
#define scpustate_getuserpsp                scpustate32_getuseresp
#define scpustate_setuserpsp                scpustate32_setuseresp
#define scpustate_getusersp                 (__byte_t *)scpustate32_getuseresp
#define scpustate_setusersp(self, sp)       scpustate32_setuseresp(self, (__u32)__COMPILER_REQTYPE(void *, sp))
#define scpustate_getuserss                 scpustate32_getuserss
#define scpustate_setuserss                 scpustate32_setuserss
#define scpustate_getkernelss               scpustate32_getkernelss
#define scpustate_getkernelpsp              scpustate32_getkernelesp
#define scpustate_getkernelsp               (__byte_t *)scpustate32_getkernelesp
#define scpustate_getds                     scpustate32_getds
#define scpustate_setds                     scpustate32_setds
#define scpustate_getes                     scpustate32_getes
#define scpustate_setes                     scpustate32_setes
#define scpustate_getfs                     scpustate32_getfs
#define scpustate_setfs                     scpustate32_setfs
#define scpustate_getgs                     scpustate32_getgs
#define scpustate_setgs                     scpustate32_setgs
#define scpustate_getds_novm86              scpustate32_getds_novm86
#define scpustate_setds_novm86              scpustate32_setds_novm86
#define scpustate_getes_novm86              scpustate32_getes_novm86
#define scpustate_setes_novm86              scpustate32_setes_novm86
#define scpustate_getfs_novm86              scpustate32_getfs_novm86
#define scpustate_setfs_novm86              scpustate32_setfs_novm86
#define scpustate_getgs_novm86              scpustate32_getgs_novm86
#define scpustate_setgs_novm86              scpustate32_setgs_novm86
#define scpustate_getpflags                 scpustate32_geteflags
#define scpustate_setpflags                 scpustate32_seteflags
#define scpustate_mskpflags                 scpustate32_mskeflags
#define scpustate_getcs                     scpustate32_getcs
#define scpustate_setcs                     scpustate32_setcs
#define scpustate_getss                     scpustate32_getss
#define scpustate_trysetss                  scpustate32_trysetss
#define scpustate_trysetuserss              scpustate32_trysetuserss
#define scpustate_sizeof                    scpustate32_sizeof
#define scpustate_to_ucpustate              scpustate32_to_ucpustate32
#define scpustate_to_ucpustate32            scpustate32_to_ucpustate32
#define scpustate32_to_ucpustate            scpustate32_to_ucpustate32
#define scpustate_user_to_ucpustate         scpustate32_user_to_ucpustate32
#define scpustate_user_to_ucpustate32       scpustate32_user_to_ucpustate32
#define scpustate32_user_to_ucpustate       scpustate32_user_to_ucpustate32
#define scpustate_to_kcpustate              scpustate32_to_kcpustate32
#define scpustate_to_kcpustate32            scpustate32_to_kcpustate32
#define scpustate32_to_kcpustate            scpustate32_to_kcpustate32
#define scpustate_user_to_kcpustate         scpustate32_user_to_kcpustate32
#define scpustate_user_to_kcpustate32       scpustate32_user_to_kcpustate32
#define scpustate32_user_to_kcpustate       scpustate32_user_to_kcpustate32
#define scpustate_to_icpustate_p            scpustate32_to_icpustate32_p
#define scpustate_to_icpustate32_p          scpustate32_to_icpustate32_p
#define scpustate32_to_icpustate_p          scpustate32_to_icpustate32_p
#define scpustate_user_to_icpustate_p       scpustate32_user_to_icpustate32_p
#define scpustate_user_to_icpustate32_p     scpustate32_user_to_icpustate32_p
#define scpustate32_user_to_icpustate_p     scpustate32_user_to_icpustate32_p
#define scpustate_to_scpustate_p            scpustate32_to_scpustate32_p
#define scpustate_to_scpustate32_p          scpustate32_to_scpustate32_p
#define scpustate32_to_scpustate_p          scpustate32_to_scpustate32_p
#define scpustate_user_to_scpustate_p       scpustate32_user_to_scpustate32_p
#define scpustate_user_to_scpustate32_p     scpustate32_user_to_scpustate32_p
#define scpustate32_user_to_scpustate_p     scpustate32_user_to_scpustate32_p
#define scpustate_getreturnbool(self)       gpregs_getreturnbool(&(self)->scs_gpregs)
#define scpustate_getreturn(self)           gpregs_getreturn(&(self)->scs_gpregs)
#define scpustate_getreturn32(self)         gpregs_getreturn32(&(self)->scs_gpregs)
#define scpustate_getreturn64(self)         gpregs_getreturn64(&(self)->scs_gpregs)
#define scpustate_setreturnbool(self, v)    gpregs_setreturnbool(&(self)->scs_gpregs, v)
#define scpustate_setreturn(self, v)        gpregs_setreturn(&(self)->scs_gpregs, v)
#define scpustate_setreturn32(self, v)      gpregs_setreturn32(&(self)->scs_gpregs, v)
#define scpustate_setreturn64(self, v)      gpregs_setreturn64(&(self)->scs_gpregs, v)

#define ucpustate_foreach_gpregs_elem       ucpustate32_foreach_gpregs_elem
#define ucpustate_foreach_gpregs_size       ucpustate32_foreach_gpregs_size
#define ucpustate_foreach_gpregs            ucpustate32_foreach_gpregs
#define ucpustate_isvm86                    ucpustate32_isvm86
#define ucpustate_isuser_novm86             ucpustate32_isuser_novm86
#define ucpustate_isuser                    ucpustate32_isuser
#define ucpustate_iskernel                  ucpustate32_iskernel
#define ucpustate_is32bit(self)             1
#define ucpustate_is64bit(self)             0
#define ucpustate_isnative(self)            1
#define ucpustate_iscompat(self)            0
#define ucpustate_getisa                    ucpustate32_getisa
#define ucpustate_getpc                     (__byte_t const *)ucpustate32_geteip
#define ucpustate_getpip                    ucpustate32_geteip
#define ucpustate_setpc(self, pc)           ucpustate32_seteip(self, (__u32)__COMPILER_REQTYPE(void const *, pc))
#define ucpustate_getpsp                    ucpustate32_getesp
#define ucpustate_getsp                     (__byte_t *)ucpustate32_getesp
#define ucpustate_setpsp                    ucpustate32_setesp
#define ucpustate_setsp(self, sp)           ucpustate32_setesp(self, (__u32)__COMPILER_REQTYPE(void *, sp))
#define ucpustate_getpflags                 ucpustate32_geteflags
#define ucpustate_setpflags                 ucpustate32_seteflags
#define ucpustate_mskpflags                 ucpustate32_mskeflags
#define ucpustate_getes                     ucpustate32_getes
#define ucpustate_setes                     ucpustate32_setes
#define ucpustate_getds                     ucpustate32_getds
#define ucpustate_setds                     ucpustate32_setds
#define ucpustate_getss                     ucpustate32_getss
#define ucpustate_setss                     ucpustate32_setss
#define ucpustate_getcs                     ucpustate32_getcs
#define ucpustate_setcs                     ucpustate32_setcs
#define ucpustate_getfs                     ucpustate32_getfs
#define ucpustate_setfs                     ucpustate32_setfs
#define ucpustate_getgs                     ucpustate32_getgs
#define ucpustate_setgs                     ucpustate32_setgs
#if !defined(__x86_64__) && defined(__i386__)
#define ucpustate_current                   ucpustate32_current
#endif /* !__x86_64__ && __i386__ */
#define ucpustate_to_ucpustate              ucpustate32_to_ucpustate32
#define ucpustate_to_ucpustate32            ucpustate32_to_ucpustate32
#define ucpustate32_to_ucpustate            ucpustate32_to_ucpustate32
#define ucpustate_to_kcpustate              ucpustate32_to_kcpustate32
#define ucpustate_to_kcpustate32            ucpustate32_to_kcpustate32
#define ucpustate32_to_kcpustate            ucpustate32_to_kcpustate32
#define ucpustate_to_icpustate_p            ucpustate32_to_icpustate32_p
#define ucpustate_to_icpustate32_p          ucpustate32_to_icpustate32_p
#define ucpustate32_to_icpustate_p          ucpustate32_to_icpustate32_p
#define ucpustate_to_scpustate_p            ucpustate32_to_scpustate32_p
#define ucpustate_to_scpustate32_p          ucpustate32_to_scpustate32_p
#define ucpustate32_to_scpustate_p          ucpustate32_to_scpustate32_p
#define ucpustate_getreturnbool(self)       gpregs_getreturnbool(&(self)->ucs_gpregs)
#define ucpustate_getreturn(self)           gpregs_getreturn(&(self)->ucs_gpregs)
#define ucpustate_getreturn32(self)         gpregs_getreturn32(&(self)->ucs_gpregs)
#define ucpustate_getreturn64(self)         gpregs_getreturn64(&(self)->ucs_gpregs)
#define ucpustate_setreturnbool(self, v)    gpregs_setreturnbool(&(self)->ucs_gpregs, v)
#define ucpustate_setreturn(self, v)        gpregs_setreturn(&(self)->ucs_gpregs, v)
#define ucpustate_setreturn32(self, v)      gpregs_setreturn32(&(self)->ucs_gpregs, v)
#define ucpustate_setreturn64(self, v)      gpregs_setreturn64(&(self)->ucs_gpregs, v)

#define fcpustate_foreach_gpregs            fcpustate32_foreach_gpregs
#define fcpustate_isvm86                    fcpustate32_isvm86
#define fcpustate_isuser_novm86             fcpustate32_isuser_novm86
#define fcpustate_isuser                    fcpustate32_isuser
#define fcpustate_iskernel                  fcpustate32_iskernel
#define fcpustate_is32bit(self)             1
#define fcpustate_is64bit(self)             0
#define fcpustate_isnative(self)            1
#define fcpustate_iscompat(self)            0
#define fcpustate_getisa                    fcpustate32_getisa
#define fcpustate_getpip                    fcpustate32_geteip
#define fcpustate_getpc                     (__byte_t const *)fcpustate32_geteip
#define fcpustate_setpip                    fcpustate32_seteip
#define fcpustate_setpc(self, pc)           fcpustate32_seteip(self, (__u32)__COMPILER_REQTYPE(void const *, pc))
#define fcpustate_getpsp                    fcpustate32_getesp
#define fcpustate_getsp                     (__byte_t *)fcpustate32_getesp
#define fcpustate_setpsp                    fcpustate32_setesp
#define fcpustate_setsp(self, sp)           fcpustate32_setesp(self, (__u32)__COMPILER_REQTYPE(void *, sp))
#define fcpustate_getpflags                 fcpustate32_geteflags
#define fcpustate_setpflags                 fcpustate32_seteflags
#define fcpustate_mskpflags                 fcpustate32_mskeflags
#define fcpustate_to_fcpustate              fcpustate32_to_fcpustate32
#define fcpustate_to_fcpustate32            fcpustate32_to_fcpustate32
#define fcpustate32_to_fcpustate            fcpustate32_to_fcpustate32
#define fcpustate_to_lcpustate              fcpustate32_to_lcpustate32
#define fcpustate_to_lcpustate32            fcpustate32_to_lcpustate32
#define fcpustate32_to_lcpustate            fcpustate32_to_lcpustate32
#define fcpustate_to_kcpustate              fcpustate32_to_kcpustate32
#define fcpustate_to_kcpustate32            fcpustate32_to_kcpustate32
#define fcpustate32_to_kcpustate            fcpustate32_to_kcpustate32
#define fcpustate_to_ucpustate              fcpustate32_to_ucpustate32
#define fcpustate_to_ucpustate32            fcpustate32_to_ucpustate32
#define fcpustate32_to_ucpustate            fcpustate32_to_ucpustate32
#define fcpustate_assign_ucpustate          fcpustate32_assign_ucpustate32
#define fcpustate_assign_ucpustate32        fcpustate32_assign_ucpustate32
#define fcpustate32_assign_ucpustate        fcpustate32_assign_ucpustate32
#define fcpustate_assign_lcpustate          fcpustate32_assign_lcpustate32
#define fcpustate_assign_lcpustate32        fcpustate32_assign_lcpustate32
#define fcpustate32_assign_lcpustate        fcpustate32_assign_lcpustate32
#define fcpustate_assign_kcpustate          fcpustate32_assign_kcpustate32
#define fcpustate_assign_kcpustate32        fcpustate32_assign_kcpustate32
#define fcpustate32_assign_kcpustate        fcpustate32_assign_kcpustate32
#define fcpustate_assign_scpustate          fcpustate32_assign_scpustate32
#define fcpustate_assign_scpustate32        fcpustate32_assign_scpustate32
#define fcpustate32_assign_scpustate        fcpustate32_assign_scpustate32
#define fcpustate_assign_icpustate_ex       fcpustate32_assign_icpustate32_ex
#define fcpustate_assign_icpustate32_ex     fcpustate32_assign_icpustate32_ex
#define fcpustate32_assign_icpustate_ex     fcpustate32_assign_icpustate32_ex
#define fcpustate_assign_icpustate          fcpustate32_assign_icpustate32
#define fcpustate_assign_icpustate32        fcpustate32_assign_icpustate32
#define fcpustate32_assign_icpustate        fcpustate32_assign_icpustate32
#define fcpustate_to_icpustate_p            fcpustate32_to_icpustate32_p
#define fcpustate_to_icpustate32_p          fcpustate32_to_icpustate32_p
#define fcpustate32_to_icpustate_p          fcpustate32_to_icpustate32_p
#define fcpustate_to_scpustate_p            fcpustate32_to_scpustate32_p
#define fcpustate_to_scpustate32_p          fcpustate32_to_scpustate32_p
#define fcpustate32_to_scpustate_p          fcpustate32_to_scpustate32_p
#define fcpustate_getreturnbool(self)       gpregs_getreturnbool(&(self)->fcs_gpregs)
#define fcpustate_getreturn(self)           gpregs_getreturn(&(self)->fcs_gpregs)
#define fcpustate_getreturn32(self)         gpregs_getreturn32(&(self)->fcs_gpregs)
#define fcpustate_getreturn64(self)         gpregs_getreturn64(&(self)->fcs_gpregs)
#define fcpustate_setreturnbool(self, v)    gpregs_setreturnbool(&(self)->fcs_gpregs, v)
#define fcpustate_setreturn(self, v)        gpregs_setreturn(&(self)->fcs_gpregs, v)
#define fcpustate_setreturn32(self, v)      gpregs_setreturn32(&(self)->fcs_gpregs, v)
#define fcpustate_setreturn64(self, v)      gpregs_setreturn64(&(self)->fcs_gpregs, v)

#endif /* !__x86_64__ */

__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_KOS_KERNEL_BITS_CPU_STATE_HELPERS32_H */
