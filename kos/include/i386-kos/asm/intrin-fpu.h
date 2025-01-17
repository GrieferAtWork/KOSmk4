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
#ifndef _I386_KOS_ASM_INTRIN_FPU_H
#define _I386_KOS_ASM_INTRIN_FPU_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

/* FPU intrinsic functions. */
#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __COMPILER_ASM_BUFFER
#define __COMPILER_ASM_BUFFER(T, s, p) (*(T *)(p))
#endif /* !__COMPILER_ASM_BUFFER */


struct xfpustate;
struct sfpustate;
struct sfpuenv;


/* Get/Set the FPU control word (Set of `FCW_*'; s.a. `struct sfpustate::fs_fcw', `struct xfpustate::fs_fcw') */
__FORCELOCAL __ATTR_WUNUSED __UINT16_TYPE__ (__fstcw)(void) { __UINT16_TYPE__ __result; __asm__ __volatile__("fstcw %w0" : "=m" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __UINT16_TYPE__ (__fnstcw)(void) { __UINT16_TYPE__ __result; __asm__ __volatile__("fnstcw %w0" : "=m" (__result)); return __result; }
__FORCELOCAL void (__fldcw)(__UINT16_TYPE__ __cw) { __asm__ __volatile__("fldcw %w0" : : "m" (__cw)); }

/* Get the FPU status word (Set of `FSW_*'; s.a. `struct sfpustate::fs_fsw', `struct xfpustate::fs_fsw') */
__FORCELOCAL __ATTR_WUNUSED __UINT16_TYPE__ (__fstsw)(void) { __UINT16_TYPE__ __result; __asm__ __volatile__("fstsw %w0" : "=am" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __UINT16_TYPE__ (__fnstsw)(void) { __UINT16_TYPE__ __result; __asm__ __volatile__("fnstsw %w0" : "=am" (__result)); return __result; }

/* fclex: FPUStatusWord &= ~(FSW_IE|FSW_DE|FSW_ZE|FSW_OE|FSW_UE|FSW_PE|FSW_SF|FSW_ES|FSW_B) */
__FORCELOCAL void (__fclex)(void) { __asm__ __volatile__("fclex"); }
__FORCELOCAL void (__fnclex)(void) { __asm__ __volatile__("fnclex"); }

/* emms: FPUTagWord = FFFFH (FTW_EMPTY) */
__FORCELOCAL void (__emms)(void) { __asm__ __volatile__("emms"); }

/* Load/Store the FPU environment
 * NOTE: Storing the FPU environment also causes all FPU exceptions to be masked! */
__FORCELOCAL void (__fstenv)(struct sfpuenv *__restrict __dst) { __asm__ __volatile__("fstenv %0" : "=m" (__COMPILER_ASM_BUFFER(__BYTE_TYPE__, 28, __dst))); }
__FORCELOCAL void (__fnstenv)(struct sfpuenv *__restrict __dst) { __asm__ __volatile__("fnstenv %0" : "=m" (__COMPILER_ASM_BUFFER(__BYTE_TYPE__, 28, __dst))); }
__FORCELOCAL void (__fldenv)(struct sfpuenv const *__restrict __src) { __asm__ __volatile__("fldenv %0" : : "m" (__COMPILER_ASM_BUFFER(__BYTE_TYPE__, 28, __src))); }

/* fsave / fnsave: Save and re-initialize FPU state (re-init happens identical to `finit' / `fninit') */
__FORCELOCAL void (__fsave)(struct sfpustate *__restrict __dst) { __asm__ __volatile__("fsave %0" : "=m" (__COMPILER_ASM_BUFFER(__BYTE_TYPE__, 108, __dst))); }
__FORCELOCAL void (__fnsave)(struct sfpustate *__restrict __dst) { __asm__ __volatile__("fnsave %0" : "=m" (__COMPILER_ASM_BUFFER(__BYTE_TYPE__, 108, __dst))); }
__FORCELOCAL void (__frstor)(struct sfpustate const *__restrict __src) { __asm__ __volatile__("frstor %0" : : "m" (__COMPILER_ASM_BUFFER(__BYTE_TYPE__, 108, __src))); }

/* finit / fninit:
 * >> FPUControlWord           = FCW_IM|FCW_DM|FCW_ZM|FCW_OM|FCW_UM|FCW_PM|0x0040|FCW_PC_EXTEND;
 * >> FPUStatusWord            = 0;
 * >> FPUTagWord               = FTW_ALLEMPTY;
 * >> FPUDataPointer           = 0;
 * >> FPUInstructionPointer    = 0;
 * >> FPULastInstructionOpcode = 0; */
__FORCELOCAL void (__finit)(void) { __asm__ __volatile__("finit"); }
__FORCELOCAL void (__fninit)(void) { __asm__ __volatile__("fninit"); }

/* Load/Store the extended FPU state
 * WARNING: When working in kernel-space, be aware that these instruction may not
 *          necessarily be supported by the CPU,  and that emulating them may  be
 *          expensive, or even impossible in certain situations.
 *          For this purpose, kernel-space should instead make use of the functions
 *          exported from <kernel/arch/fpu.h>:
 *           - x86_fxsave(), x86_fxsave32(), x86_fxsave64()
 *           - x86_fxrstor(), x86_fxrstor32(), x86_fxrstor64()
 *          Additionally, kernel-space code should also check the `x86_fpustate_variant'
 *          global  variable which describes which is the preferred mechanism for saving
 *          and loading the FPU context. */
#ifdef __x86_64__
struct xfpustate32;
__FORCELOCAL void (__fxsave)(struct xfpustate32 *__restrict __dst) { __asm__ __volatile__("fxsave %0" : "=m" (__COMPILER_ASM_BUFFER(__BYTE_TYPE__, 512, __dst))); }
__FORCELOCAL void (__fxrstor)(struct xfpustate32 const *__restrict __src) { __asm__ __volatile__("fxrstor %0" : : "m" (__COMPILER_ASM_BUFFER(__BYTE_TYPE__, 512, __src))); }
__FORCELOCAL void (__fxsave64)(struct xfpustate *__restrict __dst) { __asm__ __volatile__("fxsave64 %0" : "=m" (__COMPILER_ASM_BUFFER(__BYTE_TYPE__, 512, __dst))); }
__FORCELOCAL void (__fxrstor64)(struct xfpustate const *__restrict __src) { __asm__ __volatile__("fxrstor64 %0" : : "m" (__COMPILER_ASM_BUFFER(__BYTE_TYPE__, 512, __src))); }
#else /* __x86_64__ */
__FORCELOCAL void (__fxsave)(struct xfpustate *__restrict __dst) { __asm__ __volatile__("fxsave %0" : "=m" (__COMPILER_ASM_BUFFER(__BYTE_TYPE__, 512, __dst))); }
__FORCELOCAL void (__fxrstor)(struct xfpustate const *__restrict __src) { __asm__ __volatile__("fxrstor %0" : : "m" (__COMPILER_ASM_BUFFER(__BYTE_TYPE__, 512, __src))); }
#endif /* !__x86_64__ */

/* Floating point intrinsics. */
__FORCELOCAL void (__ldmxcsr)(__UINT32_TYPE__ __val) {
#ifdef __TINYC__
#ifdef __x86_64__
	__asm__ __volatile__("pushq %%rax\n"
	                     ".byte 0x0f, 0xae, 0x14, 0x24\n" /* ldmxcsr 0(%rsp) */
	                     "popq %%rax\n"
	                     :
	                     : "a" (__val));
#else /* __x86_64__ */
	__asm__ __volatile__("pushl %%eax\n"
	                     ".byte 0x0f, 0xae, 0x14, 0x24\n" /* ldmxcsr 0(%esp) */
	                     "popl %%eax\n"
	                     :
	                     : "a" (__val));
#endif /* !__x86_64__ */
#else /* __TINYC__ */
	__asm__ __volatile__("ldmxcsr %0" : : "m" (__val));
#endif /* !__TINYC__ */
}
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__stmxcsr)(void) {
	__UINT32_TYPE__ __result;
#ifdef __TINYC__
#ifdef __x86_64__
	__asm__ __volatile__("pushq %%rax\n"
	                     ".byte 0x0f, 0xae, 0x1c, 0x24\n" /* stmxcsr 0(%rsp) */
	                     "popq %%rax\n"
	                     : "=a" (__result));
#else /* __x86_64__ */
	__asm__ __volatile__("pushl %%eax\n"
	                     ".byte 0x0f, 0xae, 0x1c, 0x24\n" /* stmxcsr 0(%rsp) */
	                     "popl %%eax\n"
	                     : "=a" (__result));
#endif /* !__x86_64__ */
#else /* __TINYC__ */
	__asm__ __volatile__("stmxcsr %0" : "=m" (__result));
#endif /* !__TINYC__ */
	return __result;
}
__FORCELOCAL void (__clts)(void) { __asm__ __volatile__("clts"); }
__FORCELOCAL void (__fwait)(void) { __asm__ __volatile__("fwait" : : : "memory"); }



__SYSDECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_ASM_INTRIN_FPU_H */
