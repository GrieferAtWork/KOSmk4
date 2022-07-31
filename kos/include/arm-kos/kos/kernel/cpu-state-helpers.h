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
#ifndef _ARM_KOS_KOS_KERNEL_CPU_STATE_HELPERS_H
#define _ARM_KOS_KOS_KERNEL_CPU_STATE_HELPERS_H 1

#include <__stdinc.h>

#include <bits/types.h>
#include <kos/kernel/cpu-state.h>

#ifndef __INTELLISENSE__
#include <asm/intrin.h>
#endif /* !__INTELLISENSE__ */

 /* These are the cpu-state helpers that may be used portably across all architectures:
 * - pc: Program Counter
 * - sp: Stack Pointer
 *
 * Architectures may define additional macros to get/set arch-specific registers.
 */
#ifdef __CC__
__DECL_BEGIN

__FORCELOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(ucpustate_current)(struct ucpustate *__restrict __result) {
	/* TODO: I have a feeling that this can be encoded more efficiently using multi-register stores */
	__asm__ __volatile__("str r0, [%1, #0]\n\t"
	                     "str r1, [%1, #4]\n\t"
	                     "str r2, [%1, #8]\n\t"
	                     "str r3, [%1, #12]\n\t"
	                     "str r4, [%1, #16]\n\t"
	                     "str r5, [%1, #20]\n\t"
	                     "str r6, [%1, #24]\n\t"
	                     "str r7, [%1, #28]\n\t"
	                     "str r8, [%1, #32]\n\t"
	                     "str r9, [%1, #36]\n\t"
	                     "str r10, [%1, #40]\n\t"
	                     "str r11, [%1, #44]\n\t"
	                     "str r12, [%1, #48]\n\t"
	                     "str r13, [%1, #52]\n\t"
	                     "str r14, [%1, #56]\n\t"
	                     "str r15, [%1, #60]\n\t"
	                     : "=m" /*0*/ (*__result)
	                     : "r" /*1*/ (__result));
#ifndef __INTELLISENSE__
	__result->ucs_cpsr = __rdcpsr();
#endif /* !__INTELLISENSE__ */
}

__FORCELOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(lcpustate_current)(struct lcpustate *__restrict __result) {
	/* TODO: I have a feeling that this can be encoded more efficiently using multi-register stores */
	__asm__ __volatile__("str r4, [%1, #0]\n\t"
	                     "str r5, [%1, #4]\n\t"
	                     "str r6, [%1, #8]\n\t"
	                     "str r7, [%1, #12]\n\t"
	                     "str r8, [%1, #16]\n\t"
	                     "str r9, [%1, #20]\n\t"
	                     "str r10, [%1, #24]\n\t"
	                     "str r11, [%1, #28]\n\t"
	                     "str r13, [%1, #32]\n\t"
	                     "str r14, [%1, #36]\n\t"
	                     "str r15, [%1, #40]\n\t"
	                     : "=m" /*0*/ (*__result)
	                     : "r" /*1*/ (__result));
}

__DECL_END

#define ucpustate_getpc(state)     ((__byte_t const *)(state)->ucs_pc)
#define ucpustate_setpc(state, pc) (void)((state)->ucs_pc = (__uintptr_t)__COMPILER_REQTYPE(void const *, pc))
#define ucpustate_getsp(state)     ((__byte_t *)(state)->ucs_sp)
#define ucpustate_setsp(state, sp) (void)((state)->ucs_sp = (__uintptr_t)__COMPILER_REQTYPE(void const *, sp))

#define lcpustate_getpc(state)     ((__byte_t const *)(state)->lcs_pc)
#define lcpustate_setpc(state, pc) (void)((state)->lcs_pc = (__uintptr_t)__COMPILER_REQTYPE(void const *, pc))
#define lcpustate_getsp(state)     ((__byte_t *)(state)->lcs_sp)
#define lcpustate_setsp(state, sp) (void)((state)->lcs_sp = (__uintptr_t)__COMPILER_REQTYPE(void const *, sp))

#define kcpustate_getpc   ucpustate_getpc
#define kcpustate_setpc   ucpustate_setpc
#define kcpustate_getsp   ucpustate_getsp
#define kcpustate_setsp   ucpustate_setsp
#define kcpustate_current ucpustate_current

#define icpustate_getpc ucpustate_getpc
#define icpustate_setpc ucpustate_setpc
#define icpustate_getsp ucpustate_getsp
#define icpustate_setsp ucpustate_setsp

#define scpustate_getpc ucpustate_getpc
#define scpustate_setpc ucpustate_setpc
#define scpustate_getsp ucpustate_getsp
#define scpustate_setsp ucpustate_setsp

#define fcpustate_getpc   ucpustate_getpc
#define fcpustate_setpc   ucpustate_setpc
#define fcpustate_getsp   ucpustate_getsp
#define fcpustate_setsp   ucpustate_setsp
#define fcpustate_current ucpustate_current
#endif /* __CC__ */

#endif /* !_ARM_KOS_KOS_KERNEL_CPU_STATE_HELPERS_H */
