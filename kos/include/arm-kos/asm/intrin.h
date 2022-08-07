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
#ifndef _ARM_KOS_ASM_INTRIN_H
#define _ARM_KOS_ASM_INTRIN_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_GCC_ASM

/* Get/set ApplicationProgramStatusRegister (only status flags are writable) */
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdapsr)(void) { __UINT32_TYPE__ __apsr; __asm__ __volatile__("mrs %0, APSR" : "=r" (__apsr)); return __apsr; }
__FORCELOCAL void (__wrapsr)(__UINT32_TYPE__ __apsr) { __asm__ __volatile__("msr APSR_nzcvq, %0" : : "Ir" (__apsr)); }

/* Get/set CurrentProgramStatusRegister (super-set of APSR; only accessible to kernel) */
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdcpsr)(void) { __UINT32_TYPE__ __cpsr; __asm__ __volatile__("mrs %0, CPSR" : "=r" (__cpsr)); return __cpsr; }
__FORCELOCAL void (__wrcpsr)(__UINT32_TYPE__ __cpsr) { __asm__ __volatile__("msr CPSR_fcxs, %0" : : "Ir" (__cpsr)); }

/* Get/set SavedProgramStatusRegister (in kernel: user-space program status register)
 * NOTE: Not valid if called from user-mode (which doesn't have an SPSR register) */
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdspsr)(void) { __UINT32_TYPE__ __spsr; __asm__ __volatile__("mrs %0, SPSR" : "=r" (__spsr)); return __spsr; }
__FORCELOCAL void (__wrspsr)(__UINT32_TYPE__ __spsr) { __asm__ __volatile__("msr SPSR_fcxs, %0" : : "Ir" (__spsr)); }


/* General purpose registers */
#ifdef __COMPILER_HAVE_REGISTER_VARS
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr0)(void) { __register_var(__UINT32_TYPE__, __r0, "r0"); return __r0; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr1)(void) { __register_var(__UINT32_TYPE__, __r1, "r1"); return __r1; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr2)(void) { __register_var(__UINT32_TYPE__, __r2, "r2"); return __r2; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr3)(void) { __register_var(__UINT32_TYPE__, __r3, "r3"); return __r3; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr4)(void) { __register_var(__UINT32_TYPE__, __r4, "r4"); return __r4; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr5)(void) { __register_var(__UINT32_TYPE__, __r5, "r5"); return __r5; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr6)(void) { __register_var(__UINT32_TYPE__, __r6, "r6"); return __r6; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr7)(void) { __register_var(__UINT32_TYPE__, __r7, "r7"); return __r7; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr8)(void) { __register_var(__UINT32_TYPE__, __r8, "r8"); return __r8; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr9)(void) { __register_var(__UINT32_TYPE__, __r9, "r9"); return __r9; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr10)(void) { __register_var(__UINT32_TYPE__, __r10, "r10"); return __r10; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr11)(void) { __register_var(__UINT32_TYPE__, __r11, "r11"); return __r11; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr12)(void) { __register_var(__UINT32_TYPE__, __r12, "r12"); return __r12; }
__FORCELOCAL __ATTR_WUNUSED void *(__rdsp)(void) { __register_var(void *, __sp, "sp"); return __sp; }
__FORCELOCAL __ATTR_WUNUSED void *(__rdlr)(void) { __register_var(void *, __lr, "lr"); return __lr; }
__FORCELOCAL void (__wrr0)(__UINT32_TYPE__ __val) { __register_var(__UINT32_TYPE__, __r0, "r0"); __r0 = __val; }
__FORCELOCAL void (__wrr1)(__UINT32_TYPE__ __val) { __register_var(__UINT32_TYPE__, __r1, "r1"); __r1 = __val; }
__FORCELOCAL void (__wrr2)(__UINT32_TYPE__ __val) { __register_var(__UINT32_TYPE__, __r2, "r2"); __r2 = __val; }
__FORCELOCAL void (__wrr3)(__UINT32_TYPE__ __val) { __register_var(__UINT32_TYPE__, __r3, "r3"); __r3 = __val; }
__FORCELOCAL void (__wrr4)(__UINT32_TYPE__ __val) { __register_var(__UINT32_TYPE__, __r4, "r4"); __r4 = __val; }
__FORCELOCAL void (__wrr5)(__UINT32_TYPE__ __val) { __register_var(__UINT32_TYPE__, __r5, "r5"); __r5 = __val; }
__FORCELOCAL void (__wrr6)(__UINT32_TYPE__ __val) { __register_var(__UINT32_TYPE__, __r6, "r6"); __r6 = __val; }
__FORCELOCAL void (__wrr7)(__UINT32_TYPE__ __val) { __register_var(__UINT32_TYPE__, __r7, "r7"); __r7 = __val; }
__FORCELOCAL void (__wrr8)(__UINT32_TYPE__ __val) { __register_var(__UINT32_TYPE__, __r8, "r8"); __r8 = __val; }
__FORCELOCAL void (__wrr9)(__UINT32_TYPE__ __val) { __register_var(__UINT32_TYPE__, __r9, "r9"); __r9 = __val; }
__FORCELOCAL void (__wrr10)(__UINT32_TYPE__ __val) { __register_var(__UINT32_TYPE__, __r10, "r10"); __r10 = __val; }
__FORCELOCAL void (__wrr11)(__UINT32_TYPE__ __val) { __register_var(__UINT32_TYPE__, __r11, "r11"); __r11 = __val; }
__FORCELOCAL void (__wrr12)(__UINT32_TYPE__ __val) { __register_var(__UINT32_TYPE__, __r12, "r12"); __r12 = __val; }
__FORCELOCAL void (__wrsp)(void *__val) { __register_var(void *, __sp, "sp"); __sp = __val; }
__FORCELOCAL void (__wrlr)(void *__val) { __register_var(void *, __lr, "lr"); __lr = __val; }
#else /* __COMPILER_HAVE_REGISTER_VARS */
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr0)(void) { __UINT32_TYPE__ __res; __asm__ __volatile__("mov %0, r0" : "=r" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr1)(void) { __UINT32_TYPE__ __res; __asm__ __volatile__("mov %0, r1" : "=r" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr2)(void) { __UINT32_TYPE__ __res; __asm__ __volatile__("mov %0, r2" : "=r" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr3)(void) { __UINT32_TYPE__ __res; __asm__ __volatile__("mov %0, r3" : "=r" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr4)(void) { __UINT32_TYPE__ __res; __asm__ __volatile__("mov %0, r4" : "=r" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr5)(void) { __UINT32_TYPE__ __res; __asm__ __volatile__("mov %0, r5" : "=r" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr6)(void) { __UINT32_TYPE__ __res; __asm__ __volatile__("mov %0, r6" : "=r" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr7)(void) { __UINT32_TYPE__ __res; __asm__ __volatile__("mov %0, r7" : "=r" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr8)(void) { __UINT32_TYPE__ __res; __asm__ __volatile__("mov %0, r8" : "=r" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr9)(void) { __UINT32_TYPE__ __res; __asm__ __volatile__("mov %0, r9" : "=r" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr10)(void) { __UINT32_TYPE__ __res; __asm__ __volatile__("mov %0, r10" : "=r" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr11)(void) { __UINT32_TYPE__ __res; __asm__ __volatile__("mov %0, r11" : "=r" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdr12)(void) { __UINT32_TYPE__ __res; __asm__ __volatile__("mov %0, r12" : "=r" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED void *(__rdsp)(void) { void *__res; __asm__ __volatile__("mov %0, sp" : "=r" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED void *(__rdlr)(void) { void *__res; __asm__ __volatile__("mov %0, lr" : "=r" (__res)); return __res; }
__FORCELOCAL void (__wrr0)(__UINT32_TYPE__ __val) { __asm__ __volatile__("mov r0, %0" : : "r" (__val) : "r0"); }
__FORCELOCAL void (__wrr1)(__UINT32_TYPE__ __val) { __asm__ __volatile__("mov r1, %0" : : "r" (__val) : "r1"); }
__FORCELOCAL void (__wrr2)(__UINT32_TYPE__ __val) { __asm__ __volatile__("mov r2, %0" : : "r" (__val) : "r2"); }
__FORCELOCAL void (__wrr3)(__UINT32_TYPE__ __val) { __asm__ __volatile__("mov r3, %0" : : "r" (__val) : "r3"); }
__FORCELOCAL void (__wrr4)(__UINT32_TYPE__ __val) { __asm__ __volatile__("mov r4, %0" : : "r" (__val) : "r4"); }
__FORCELOCAL void (__wrr5)(__UINT32_TYPE__ __val) { __asm__ __volatile__("mov r5, %0" : : "r" (__val) : "r5"); }
__FORCELOCAL void (__wrr6)(__UINT32_TYPE__ __val) { __asm__ __volatile__("mov r6, %0" : : "r" (__val) : "r6"); }
__FORCELOCAL void (__wrr7)(__UINT32_TYPE__ __val) { __asm__ __volatile__("mov r7, %0" : : "r" (__val) : "r7"); }
__FORCELOCAL void (__wrr8)(__UINT32_TYPE__ __val) { __asm__ __volatile__("mov r8, %0" : : "r" (__val) : "r8"); }
__FORCELOCAL void (__wrr9)(__UINT32_TYPE__ __val) { __asm__ __volatile__("mov r9, %0" : : "r" (__val) : "r9"); }
__FORCELOCAL void (__wrr10)(__UINT32_TYPE__ __val) { __asm__ __volatile__("mov r10, %0" : : "r" (__val) : "r10"); }
__FORCELOCAL void (__wrr11)(__UINT32_TYPE__ __val) { __asm__ __volatile__("mov r11, %0" : : "r" (__val) : "r11"); }
__FORCELOCAL void (__wrr12)(__UINT32_TYPE__ __val) { __asm__ __volatile__("mov r12, %0" : : "r" (__val) : "r12"); }
__FORCELOCAL void (__wrsp)(void *__val) { __asm__ __volatile__("mov sp, %0" : : "r" (__val) : "sp"); }
__FORCELOCAL void (__wrlr)(void *__val) { __asm__ __volatile__("mov lr, %0" : : "r" (__val) : "lr"); }
#endif /* !__COMPILER_HAVE_REGISTER_VARS */

__FORCELOCAL __ATTR_WUNUSED void *(__rdpc)(void) { void *__res; __asm__ __volatile__("mov %0, pc" : "=r" (__res)); return __res; }
__FORCELOCAL __ATTR_NORETURN void (__wrpc)(void *__val) { __asm__ __volatile__("mov pc, %0" : : "r" (__val)); __builtin_unreachable(); }


/* Bank-independent, explicit register access */
#ifdef __KERNEL__
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdR8_usr)(void) { __UINT32_TYPE__ __result; __asm__ __volatile__("@ TODO" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED void (__wrR8_usr)(__UINT32_TYPE__ __val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdR9_usr)(void) { __UINT32_TYPE__ __result; __asm__ __volatile__("@ TODO" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED void (__wrR9_usr)(__UINT32_TYPE__ __val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdR10_usr)(void) { __UINT32_TYPE__ __result; __asm__ __volatile__("@ TODO" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED void (__wrR10_usr)(__UINT32_TYPE__ __val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdR11_usr)(void) { __UINT32_TYPE__ __result; __asm__ __volatile__("@ TODO" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED void (__wrR11_usr)(__UINT32_TYPE__ __val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdR12_usr)(void) { __UINT32_TYPE__ __result; __asm__ __volatile__("@ TODO" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED void (__wrR12_usr)(__UINT32_TYPE__ __val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }
__FORCELOCAL __ATTR_WUNUSED void *(__rdSP_usr)(void) { void *__result; __asm__ __volatile__("@ TODO" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED void (__wrSP_usr)(void *__val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }
__FORCELOCAL __ATTR_WUNUSED void *(__rdLR_usr)(void) { void *__result; __asm__ __volatile__("@ TODO" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED void (__wrLR_usr)(void *__val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }
#else /* __KERNEL__ */
/* Outside of kernel-space, *_usr-registers are always the ones that are active! */
#define __rdR8_usr  __rdr8
#define __rdR9_usr  __rdr9
#define __rdR10_usr __rdr10
#define __rdR11_usr __rdr11
#define __rdR12_usr __rdr12
#define __rdSP_usr  __rdsp
#define __rdLR_usr  __rdlr
#define __wrR8_usr  __wrr8
#define __wrR9_usr  __wrr9
#define __wrR10_usr __wrr10
#define __wrR11_usr __wrr11
#define __wrR12_usr __wrr12
#define __wrSP_usr  __wrsp
#define __wrLR_usr  __wrlr
#endif /* !__KERNEL__ */

__FORCELOCAL __ATTR_WUNUSED void *(__rdSP_svc)(void) { void *__result; __asm__ __volatile__("@ TODO" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED void (__wrSP_svc)(void *__val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }
__FORCELOCAL __ATTR_WUNUSED void *(__rdLR_svc)(void) { void *__result; __asm__ __volatile__("@ TODO" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED void (__wrLR_svc)(void *__val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdSPSR_svc)(void) { __UINT32_TYPE__ __spsr; __asm__ __volatile__("@ TODO" : "=r" (__spsr)); return __spsr; }
__FORCELOCAL __ATTR_WUNUSED void (__wrSPSR_svc)(__UINT32_TYPE__ __val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }

__FORCELOCAL __ATTR_WUNUSED void *(__rdSP_abt)(void) { void *__result; __asm__ __volatile__("@ TODO" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED void (__wrSP_abt)(void *__val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }
__FORCELOCAL __ATTR_WUNUSED void *(__rdLR_abt)(void) { void *__result; __asm__ __volatile__("@ TODO" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED void (__wrLR_abt)(void *__val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdSPSR_abt)(void) { __UINT32_TYPE__ __spsr; __asm__ __volatile__("@ TODO" : "=r" (__spsr)); return __spsr; }
__FORCELOCAL __ATTR_WUNUSED void (__wrSPSR_abt)(__UINT32_TYPE__ __val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }

__FORCELOCAL __ATTR_WUNUSED void *(__rdSP_und)(void) { void *__result; __asm__ __volatile__("@ TODO" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED void (__wrSP_und)(void *__val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }
__FORCELOCAL __ATTR_WUNUSED void *(__rdLR_und)(void) { void *__result; __asm__ __volatile__("@ TODO" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED void (__wrLR_und)(void *__val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdSPSR_und)(void) { __UINT32_TYPE__ __spsr; __asm__ __volatile__("@ TODO" : "=r" (__spsr)); return __spsr; }
__FORCELOCAL __ATTR_WUNUSED void (__wrSPSR_und)(__UINT32_TYPE__ __val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }

__FORCELOCAL __ATTR_WUNUSED void *(__rdSP_irq)(void) { void *__result; __asm__ __volatile__("@ TODO" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED void (__wrSP_irq)(void *__val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }
__FORCELOCAL __ATTR_WUNUSED void *(__rdLR_irq)(void) { void *__result; __asm__ __volatile__("@ TODO" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED void (__wrLR_irq)(void *__val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdSPSR_irq)(void) { __UINT32_TYPE__ __spsr; __asm__ __volatile__("@ TODO" : "=r" (__spsr)); return __spsr; }
__FORCELOCAL __ATTR_WUNUSED void (__wrSPSR_irq)(__UINT32_TYPE__ __val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }

__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdR8_fiq)(void) { __UINT32_TYPE__ __result; __asm__ __volatile__("@ TODO" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED void (__wrR8_fiq)(__UINT32_TYPE__ __val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdR9_fiq)(void) { __UINT32_TYPE__ __result; __asm__ __volatile__("@ TODO" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED void (__wrR9_fiq)(__UINT32_TYPE__ __val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdR10_fiq)(void) { __UINT32_TYPE__ __result; __asm__ __volatile__("@ TODO" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED void (__wrR10_fiq)(__UINT32_TYPE__ __val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdR11_fiq)(void) { __UINT32_TYPE__ __result; __asm__ __volatile__("@ TODO" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED void (__wrR11_fiq)(__UINT32_TYPE__ __val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdR12_fiq)(void) { __UINT32_TYPE__ __result; __asm__ __volatile__("@ TODO" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED void (__wrR12_fiq)(__UINT32_TYPE__ __val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }
__FORCELOCAL __ATTR_WUNUSED void *(__rdSP_fiq)(void) { void *__result; __asm__ __volatile__("@ TODO" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED void (__wrSP_fiq)(void *__val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }
__FORCELOCAL __ATTR_WUNUSED void *(__rdLR_fiq)(void) { void *__result; __asm__ __volatile__("@ TODO" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED void (__wrLR_fiq)(void *__val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdSPSR_fiq)(void) { __UINT32_TYPE__ __spsr; __asm__ __volatile__("@ TODO" : "=r" (__spsr)); return __spsr; }
__FORCELOCAL __ATTR_WUNUSED void (__wrSPSR_fiq)(__UINT32_TYPE__ __val) { __asm__ __volatile__("@ TODO" : : "r" (__val)); }

#endif /* __COMPILER_HAVE_GCC_ASM */

/* Flush the instruction cache by executing a fencing instruction. */
#define __flush_instruction_cache() (void)0 /* TODO */

__DECL_END
#endif /* __CC__ */


#endif /* !_ARM_KOS_ASM_INTRIN_H */
