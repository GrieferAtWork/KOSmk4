/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ARM_KOS_KOS_BITS_NOPF_H
#define _ARM_KOS_KOS_BITS_NOPF_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/host.h>

#include <bits/types.h>
#include <kos/anno.h>

/* Figure out how we should call nofp functions. */
#if defined(__KOS__) && defined(__KERNEL__)
#define __ARM_NOPF_AVAILABLE
#elif defined(__CRT_KOS) && defined(__BUILDING_LIBC)
#define __ARM_NOPF_AVAILABLE
#endif /* ... */

#if defined(__CRT_HAVE_arm_nopf_ldrb_r0_Br0B) || defined(__ARM_NOPF_AVAILABLE)
#define __arch_readb_nopf __arch_readb_nopf
#endif /* __CRT_HAVE_arm_nopf_ldrb_r0_Br0B || __ARM_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_arm_nopf_ldrh_r0_Br0B) || defined(__ARM_NOPF_AVAILABLE)
#define __arch_readw_nopf __arch_readw_nopf
#endif /* __CRT_HAVE_arm_nopf_ldrh_r0_Br0B || __ARM_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_arm_nopf_ldr_r0_Br0B) || defined(__ARM_NOPF_AVAILABLE)
#define __arch_readl_nopf __arch_readl_nopf
#endif /* __CRT_HAVE_arm_nopf_ldr_r0_Br0B || __ARM_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_arm_nopf_ldrd_r0_r1_Br0B) || defined(__ARM_NOPF_AVAILABLE)
#define __arch_readq_nopf __arch_readq_nopf
#endif /* __CRT_HAVE_arm_nopf_ldrd_r0_r1_Br0B || __ARM_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_arm_nopf_strb_r0_Br0B) || defined(__ARM_NOPF_AVAILABLE)
#define __arch_writeb_nopf __arch_writeb_nopf
#endif /* __CRT_HAVE_arm_nopf_strb_r0_Br0B || __ARM_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_arm_nopf_strh_r0_Br0B) || defined(__ARM_NOPF_AVAILABLE)
#define __arch_writew_nopf __arch_writew_nopf
#endif /* __CRT_HAVE_arm_nopf_strh_r0_Br0B || __ARM_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_arm_nopf_str_r0_Br0B) || defined(__ARM_NOPF_AVAILABLE)
#define __arch_writel_nopf __arch_writel_nopf
#endif /* __CRT_HAVE_arm_nopf_str_r0_Br0B || __ARM_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_arm_nopf_strd_r0_r1_Br0B) || defined(__ARM_NOPF_AVAILABLE)
#define __arch_writeq_nopf __arch_writeq_nopf
#endif /* __CRT_HAVE_arm_nopf_strd_r0_r1_Br0B || __ARM_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_arm_nopf_cmpxchb) || defined(__ARM_NOPF_AVAILABLE)
#define __arch_atomic_cmpxchb_nopf __arch_atomic_cmpxchb_nopf
#endif /* __CRT_HAVE_arm_nopf_cmpxchb || __ARM_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_arm_nopf_cmpxchh) || defined(__ARM_NOPF_AVAILABLE)
#define __arch_atomic_cmpxchw_nopf __arch_atomic_cmpxchw_nopf
#endif /* __CRT_HAVE_arm_nopf_cmpxchh || __ARM_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_arm_nopf_cmpxch) || defined(__ARM_NOPF_AVAILABLE)
#define __arch_atomic_cmpxchl_nopf __arch_atomic_cmpxchl_nopf
#endif /* __CRT_HAVE_arm_nopf_cmpxch || __ARM_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_arm_nopf_cmpxchd) || defined(__ARM_NOPF_AVAILABLE)
#define __arch_atomic_cmpxchq_nopf __arch_atomic_cmpxchq_nopf
#endif /* __CRT_HAVE_arm_nopf_cmpxchd || __ARM_NOPF_AVAILABLE */

#ifdef __CC__
__DECL_BEGIN

#ifndef __ASMCALL
#define __ASMCALL /* nothing */
#endif /* !__ASMCALL */

#ifndef __COMPILER_ASM_BUFFER
#define __COMPILER_ASM_BUFFER(T, s, p) (*(T *)(p))
#endif /* !__COMPILER_ASM_BUFFER */

/* Figure out how we should call nofp functions. */
#if defined(__KOS__) && defined(__KERNEL__)
#define __ARM_NOPF_CALLASM(name) "bl " #name
#define __ARM_NOPF_CALLARG(name) /* nothing */
#elif defined(__CRT_KOS) && defined(__BUILDING_LIBC)
#define __ARM_NOPF_CALLASM(name) "bl libc_" #name
#define __ARM_NOPF_CALLARG(name) /* nothing */
#else /* ... */
/* Fallback: just call directly. */
#define __ARM_NOPF_CALLASM(name) "bl libc_" #name
#define __ARM_NOPF_CALLARG(name) /* nothing */
#endif /* !... */

#define __ARM_NOPF_CALLCLB  : "lr"
#define __ARM_NOPF_CALLCLB_ : "lr",

#ifndef __ARM_NOPF_DEFFUN
#define __ARM_NOPF_DEFFUN(name) /* nothing */
#endif /* !__ARM_NOPF_DEFFUN */


/* All of the arm_nopf_* assembly functions behave as follows:
 *  #1 Clear all flag bits (every function starts with `msr APSR_nzcvq, #0')
 *  #2 Execute the instruction that is apart of function's name.
 *     e.g. `arm_nopf_ldrb_r0_Br0B'
 *      will execute `ldrb r0, [r0]'
 *  #3 Return to the caller (i.e. `bx lr')
 *  #4 If a "Data Abort" (#PF) is triggered during any of this, the function will
 *     return  to the caller with all registers  unaltered from the point in time
 *     when  the "Data Abort" (#PF) happened, except that `APSR.Z' will have also
 *     been set (iow: `msr APSR_nzcvq, #CPSR_Z').
 */


/* The following functions are defined by the ARM NOPF ABI for KOS:
 * - arm_nopf_ldrb_r0_Br0B      # ldrb   r0, [r0]
 * - arm_nopf_ldrh_r0_Br0B      # ldrh   r0, [r0]
 * - arm_nopf_ldr_r0_Br0B       # ldr    r0, [r0]
 * - arm_nopf_ldrd_r0_r1_Br0B   # ldrd   r0, r1, [r0]
 * - arm_nopf_strb_r0_Br1B      # strb   r0, [r1]
 * - arm_nopf_strh_r0_Br1B      # strh   r0, [r1]
 * - arm_nopf_str_r0_Br1B       # str    r0, [r1]
 * - arm_nopf_strd_r0_r1_Br2B   # strd   r0, r1, [r2]
 */


#ifdef __arch_readb_nopf
__ARM_NOPF_DEFFUN(arm_nopf_ldrb_r0_Br0B) /* ldrb r0, [r0] # read byte */
/* Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
#define __arch_readb_nopf __arch_readb_nopf
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __BOOL
__NOTHROW(__arch_readb_nopf)(__NCX void const *__addr, __uint8_t *__presult) {
	__BOOL __error;
	__register_var(__uint32_t, __r0, "r0");
	__asm__ __volatile__(__ARM_NOPF_CALLASM(arm_nopf_ldrb_r0_Br0B)
	                     : "=r" (__r0)
	                     , "=@cceq" (__error)
	                     : "0" (__addr)
	                     __ARM_NOPF_CALLARG(arm_nopf_ldrb_r0_Br0B)
	                     __ARM_NOPF_CALLCLB);
	*__presult = (__uint8_t)__r0;
	return !__error;
}
#endif /* __arch_readb_nopf */

#ifdef __arch_readw_nopf
__ARM_NOPF_DEFFUN(arm_nopf_ldrh_r0_Br0B) /* ldrh r0, [r0] # read word */
/* Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
#define __arch_readw_nopf __arch_readw_nopf
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __BOOL
__NOTHROW(__arch_readw_nopf)(__NCX void const *__addr, __uint16_t *__presult) {
	__BOOL __error;
	__register_var(__uint32_t, __r0, "r0");
	__asm__ __volatile__(__ARM_NOPF_CALLASM(arm_nopf_ldrh_r0_Br0B)
	                     : "=r" (__r0)
	                     , "=@cceq" (__error)
	                     : "0" (__addr)
	                     __ARM_NOPF_CALLARG(arm_nopf_ldrh_r0_Br0B)
	                     __ARM_NOPF_CALLCLB);
	*__presult = (__uint16_t)__r0;
	return !__error;
}
#endif /* __arch_readw_nopf */

#ifdef __arch_readl_nopf
__ARM_NOPF_DEFFUN(arm_nopf_ldr_r0_Br0B) /* ldr r0, [r0] # read dword */
/* Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
#define __arch_readl_nopf __arch_readl_nopf
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __BOOL
__NOTHROW(__arch_readl_nopf)(__NCX void const *__addr, __uint32_t *__presult) {
	__BOOL __error;
	__register_var(__uint32_t, __r0, "r0");
	__asm__ __volatile__(__ARM_NOPF_CALLASM(arm_nopf_ldr_r0_Br0B)
	                     : "=r" (__r0)
	                     , "=@cceq" (__error)
	                     : "0" (__addr)
	                     __ARM_NOPF_CALLARG(arm_nopf_ldr_r0_Br0B)
	                     __ARM_NOPF_CALLCLB);
	*__presult = __r0;
	return !__error;
}
#endif /* __arch_readl_nopf */


#ifdef __arch_readq_nopf
__ARM_NOPF_DEFFUN(arm_nopf_ldrd_r0_r1_Br0B) /* ldrd r0, r1, [r0] # read qword */

/* Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
#define __arch_readq_nopf __arch_readq_nopf
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __BOOL
__NOTHROW(__arch_readq_nopf)(__NCX void const *__addr, __uint64_t *__presult) {
	__BOOL __error;
	__register_var(__uint32_t, __r0, "r0");
	__register_var(__uint32_t, __r1, "r1");
	__asm__ __volatile__(__ARM_NOPF_CALLASM(arm_nopf_ldrd_r0_r1_Br0B)
	                     : "=r" (__r0)
	                     , "=r" (__r1)
	                     , "=@cceq" (__error)
	                     : "0" (__addr)
	                     __ARM_NOPF_CALLARG(arm_nopf_ldrd_r0_r1_Br0B)
	                     __ARM_NOPF_CALLCLB);
	*__presult = (((__uint64_t)__r0) |
	              ((__uint64_t)__r1 << 32));
	return !__error;
}
#endif /* __arch_readq_nopf */


#ifdef __arch_writeb_nopf
__ARM_NOPF_DEFFUN(arm_nopf_strb_r0_Br1B) /* strb r0, [r1] # write byte */
/* Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
#define __arch_writeb_nopf __arch_writeb_nopf
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__arch_writeb_nopf)(__NCX void const *__addr, __uint8_t __val) {
	__BOOL __error;
	__register_var(__uint32_t, __r0, "r0") = (__uint32_t)__val;
	__register_var(__uint32_t, __r1, "r1") = (__uint32_t)__addr;
	__asm__ __volatile__(__ARM_NOPF_CALLASM(arm_nopf_strb_r0_Br1B)
	                     : "=@cceq" (__error)
	                     : "r" (__r0)
	                     , "r" (__r1)
	                     __ARM_NOPF_CALLARG(arm_nopf_strb_r0_Br1B)
	                     __ARM_NOPF_CALLCLB);
	return !__error;
}
#endif /* __arch_writeb_nopf */

#ifdef __arch_writew_nopf
__ARM_NOPF_DEFFUN(arm_nopf_strh_r0_Br1B) /* strh r0, [r1] # write word */
/* Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
#define __arch_writew_nopf __arch_writew_nopf
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__arch_writew_nopf)(__NCX void const *__addr, __uint16_t __val) {
	__BOOL __error;
	__register_var(__uint32_t, __r0, "r0") = (__uint32_t)__val;
	__register_var(__uint32_t, __r1, "r1") = (__uint32_t)__addr;
	__asm__ __volatile__(__ARM_NOPF_CALLASM(arm_nopf_strh_r0_Br1B)
	                     : "=@cceq" (__error)
	                     : "r" (__r0)
	                     , "r" (__r1)
	                     __ARM_NOPF_CALLARG(arm_nopf_strh_r0_Br1B)
	                     __ARM_NOPF_CALLCLB);
	return !__error;
}
#endif /* __arch_writew_nopf */

#ifdef __arch_writel_nopf
__ARM_NOPF_DEFFUN(arm_nopf_str_r0_Br1B) /* str r0, [r1] # write dword */
/* Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
#define __arch_writel_nopf __arch_writel_nopf
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__arch_writel_nopf)(__NCX void const *__addr, __uint32_t __val) {
	__BOOL __error;
	__register_var(__uint32_t, __r0, "r0") = (__uint32_t)__val;
	__register_var(__uint32_t, __r1, "r1") = (__uint32_t)__addr;
	__asm__ __volatile__(__ARM_NOPF_CALLASM(arm_nopf_str_r0_Br1B)
	                     : "=@cceq" (__error)
	                     : "r" (__r0)
	                     , "r" (__r1)
	                     __ARM_NOPF_CALLARG(arm_nopf_str_r0_Br1B)
	                     __ARM_NOPF_CALLCLB);
	return !__error;
}
#endif /* __arch_writel_nopf */


#ifdef __arch_writeq_nopf
__ARM_NOPF_DEFFUN(arm_nopf_strd_r0_r1_Br2B) /* strd r0, r1, [r2] # write qword */

/* Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
#define __arch_writeq_nopf __arch_writeq_nopf
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__arch_writeq_nopf)(__NCX void const *__addr, __uint64_t __val) {
	__BOOL __error;
	__register_var(__uint32_t, __r0, "r0") = (__uint32_t)__val;
	__register_var(__uint32_t, __r1, "r1") = (__uint32_t)(__val >> 32);
	__register_var(__uint32_t, __r2, "r2") = (__uint32_t)__addr;
	__asm__ __volatile__(__ARM_NOPF_CALLASM(arm_nopf_strd_r0_r1_Br2B)
	                     : "=@cceq" (__error)
	                     : "r" (__r0)
	                     , "r" (__r1)
	                     , "r" (__r2)
	                     __ARM_NOPF_CALLARG(arm_nopf_strd_r0_r1_Br2B)
	                     __ARM_NOPF_CALLCLB);
	return !__error;
}
#endif /* __arch_writeq_nopf */


/* In order to support atomic operations, the following aliases are also defined:
 * - arm_nopf_cmpxchb
 * - arm_nopf_cmpxchh
 * - arm_nopf_cmpxch
 *   >> .L_begin_pf_handling:
 *   >> 1:  ldaex* r3, [r0]
 *   >>     cmp    r3, r1
 *   >>     bne    2f
 *   >>     stlex* r12, r2, [r0]
 *   >>     cmp    r12, #1      @ Check status (also sets APSR.Z=0 in case of no-branch)
 *   >>     bhs    1b           @ Repeat if STATUS >= 1
 *   >> 2:  bx     lr
 *   >> .L_end_pf_handling:
 *   >> .L_do_pf_handling:
 *   >>     cmp    r0, r0       @ Force APSR.Z=1
 *   >>     bx     lr
 *   @in  T  *r0: Pointer
 *   @in  T   r1: Old value
 *   @in  T   r2: New value
 *   @out T   r3: Real old value (only valid when APSR.Z=0)
 *   @out APSR.Z: If set: PF error happened
 *   @clobber r12
 *
 * Dependent on hardware, listed code may not be correct, but effective behavior (when viewed
 * as an atomic block of instructions; i.e. affected/clobberred/presered registers/flags)  is
 * always the same! */
#ifdef __arch_atomic_cmpxchb_nopf
__ARM_NOPF_DEFFUN(arm_nopf_cmpxchb) /* ... */

#define __arch_atomic_cmpxchb_nopf __arch_atomic_cmpxchb_nopf
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((4)) __BOOL
__NOTHROW(__arch_atomic_cmpxchb_nopf)(__NCX void *__addr,
                                      __uint8_t __oldval, __uint8_t __newval,
                                      __uint8_t *__preal_oldval) {
	__BOOL __error;
	__register_var(__uint32_t, __r0, "r0") = (__uint32_t)__addr;
	__register_var(__uint32_t, __r1, "r1") = (__uint32_t)__oldval;
	__register_var(__uint32_t, __r2, "r2") = (__uint32_t)__newval;
	__register_var(__uint32_t, __r3, "r3");
	__asm__ __volatile__(__ARM_NOPF_CALLASM(arm_nopf_cmpxchb)
	                     : "=@cceq" (__error)
	                     , "=r" (__r3)
	                     : "r" (__r0)
	                     , "r" (__r1)
	                     , "r" (__r2)
	                     __ARM_NOPF_CALLARG(arm_nopf_cmpxchb)
	                     __ARM_NOPF_CALLCLB_ "memory", "r12");
	*__preal_oldval = (__uint8_t)__r3;
	return !__error;
}
#endif /* __arch_atomic_cmpxchb_nopf */

#ifdef __arch_atomic_cmpxchw_nopf
__ARM_NOPF_DEFFUN(arm_nopf_cmpxchh) /* ... */

#define __arch_atomic_cmpxchw_nopf __arch_atomic_cmpxchw_nopf
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((4)) __BOOL
__NOTHROW(__arch_atomic_cmpxchw_nopf)(__NCX void *__addr,
                                      __uint16_t __oldval, __uint16_t __newval,
                                      __uint16_t *__preal_oldval) {
	__BOOL __error;
	__register_var(__uint32_t, __r0, "r0") = (__uint32_t)__addr;
	__register_var(__uint32_t, __r1, "r1") = (__uint32_t)__oldval;
	__register_var(__uint32_t, __r2, "r2") = (__uint32_t)__newval;
	__register_var(__uint32_t, __r3, "r3");
	__asm__ __volatile__(__ARM_NOPF_CALLASM(arm_nopf_cmpxchh)
	                     : "=@cceq" (__error)
	                     , "=r" (__r3)
	                     : "r" (__r0)
	                     , "r" (__r1)
	                     , "r" (__r2)
	                     __ARM_NOPF_CALLARG(arm_nopf_cmpxchh)
	                     __ARM_NOPF_CALLCLB_ "memory", "r12");
	*__preal_oldval = (__uint16_t)__r3;
	return !__error;
}
#endif /* __arch_atomic_cmpxchw_nopf */

#ifdef __arch_atomic_cmpxchl_nopf
__ARM_NOPF_DEFFUN(arm_nopf_cmpxch) /* ... */

#define __arch_atomic_cmpxchl_nopf __arch_atomic_cmpxchl_nopf
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((4)) __BOOL
__NOTHROW(__arch_atomic_cmpxchl_nopf)(__NCX void *__addr,
                                      __uint32_t __oldval, __uint32_t __newval,
                                      __uint32_t *__preal_oldval) {
	__BOOL __error;
	__register_var(__uint32_t, __r0, "r0") = (__uint32_t)__addr;
	__register_var(__uint32_t, __r1, "r1") = __oldval;
	__register_var(__uint32_t, __r2, "r2") = __newval;
	__register_var(__uint32_t, __r3, "r3");
	__asm__ __volatile__(__ARM_NOPF_CALLASM(arm_nopf_cmpxch)
	                     : "=@cceq" (__error)
	                     , "=r" (__r3)
	                     : "r" (__r0)
	                     , "r" (__r1)
	                     , "r" (__r2)
	                     __ARM_NOPF_CALLARG(arm_nopf_cmpxch)
	                     __ARM_NOPF_CALLCLB_ "memory", "r12");
	*__preal_oldval = __r3;
	return !__error;
}
#endif /* __arch_atomic_cmpxchl_nopf */

/* 64-bit atomic-compare-exchange:
 * - arm_nopf_cmpxchd
 *   >> .L_begin_pf_handling:
 *   >> 1:  ldaexd r4, r5, [r6]
 *   >>     cmp    r5, r1
 *   >>     cmpeq  r4, r0
 *   >>     bne    2f
 *   >>     stlexd r12, r2, r3, [r6]
 *   >>     cmp    r12, #1      @ Check status (also sets APSR.Z=0 in case of no-branch)
 *   >>     bhs    1b           @ Repeat if STATUS >= 1
 *   >> 2:  bx     lr
 *   >> .L_end_pf_handling:
 *   >> .L_do_pf_handling:
 *   >>     cmp    r0, r0       @ Force APSR.Z=1
 *   >>     bx     lr
 *   @in  u64*r6: Pointer
 *   @in  u32 r0: Old value (lo32)
 *   @in  u32 r1: Old value (hi32)
 *   @in  u32 r2: New value (lo32)
 *   @in  u32 r3: New value (hi32)
 *   @out u32 r4: Real old value (lo32)
 *   @out u32 r5: Real old value (hi32)
 *   @out APSR.Z: If set: PF error happened
 *   @clobber r12
 *
 * Dependent on hardware, listed code may not be correct, but effective behavior (when viewed
 * as an atomic block of instructions; i.e. affected/clobberred/presered registers/flags)  is
 * always the same! */
#ifdef __arch_atomic_cmpxchq_nopf
__ARM_NOPF_DEFFUN(arm_nopf_cmpxchd) /* ... */

#define __arch_atomic_cmpxchq_nopf __arch_atomic_cmpxchq_nopf
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((4)) __BOOL
__NOTHROW(__arch_atomic_cmpxchq_nopf)(__NCX void *__addr,
                                      __uint64_t __oldval, __uint64_t __newval,
                                      __uint64_t *__preal_oldval) {
	__BOOL __error;
	__register_var(__uint32_t, __r0, "r0") = (__uint32_t)__oldval;
	__register_var(__uint32_t, __r1, "r1") = (__uint32_t)(__oldval >> 32);
	__register_var(__uint32_t, __r2, "r2") = (__uint32_t)__newval;
	__register_var(__uint32_t, __r3, "r3") = (__uint32_t)(__newval >> 32);
	__register_var(__uint32_t, __r4, "r4");
	__register_var(__uint32_t, __r5, "r5");
	__register_var(__uint32_t, __r6, "r6") = (__uint32_t)__addr;
	__asm__ __volatile__(__ARM_NOPF_CALLASM(arm_nopf_cmpxchd)
	                     : "=@cceq" (__error)
	                     , "=r" (__r4)
	                     , "=r" (__r5)
	                     : "r" (__r0)
	                     , "r" (__r1)
	                     , "r" (__r2)
	                     , "r" (__r3)
	                     , "r" (__r6)
	                     __ARM_NOPF_CALLARG(arm_nopf_cmpxchd)
	                     __ARM_NOPF_CALLCLB_ "memory", "r12");
	*__preal_oldval = (((__uint64_t)__r4) |
	                   ((__uint64_t)__r5 << 32));
	return !__error;
}
#endif /* __arch_atomic_cmpxchq_nopf */


#undef __ARM_NOPF_CALLASM
#undef __ARM_NOPF_CALLARG
#undef __ARM_NOPF_CALLCLB

__DECL_END
#endif /* __CC__ */

#endif /* !_ARM_KOS_KOS_BITS_NOPF_H */
