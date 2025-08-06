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
#ifndef _ARM_KOS_KOS_KERNEL_BITS_CPU_STATE_ASM_H
#define _ARM_KOS_KOS_KERNEL_BITS_CPU_STATE_ASM_H 1

#include <__stdinc.h>

#include <asm/arm.h>

#include <cfi.h>

/* clang-format off */

#ifdef NDEBUG
#define __ARM_ASM_DBGY(...) /* nothing */
#define __ARM_ASM_DBGN(...) __VA_ARGS__
#else /* NDEBUG */
#define __ARM_ASM_DBGY(...) __VA_ARGS__
#define __ARM_ASM_DBGN(...) /* nothing */
#endif /* !NDEBUG */


/* Push a `struct ucpustate' upon entry to some function. The pushed
 * structure describes the CPU state as it was for the caller of the
 * function (as closely as possible).
 *
 * Note that the `lr' register will have already been lost, so a stub
 * value is pushed for it instead.
 *
 * NOTE: Only for use in ARM code (NO thumb allowed)
 * @clobber: r12 */
#define ASM_PUSH_UCPUSTATE_ON_ENTRY_CFI_R                                     \
	/* Push (and save) all of the *actual* GP registers */                    \
	__ASM_L(push_cfi_r {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12})           \
	__ASM_L(mrs    r12, CPSR)     /* Load current CPSR */                     \
	__ASM_L(tst    lr, #1)        /* Check if we return to thumb-mode */      \
	__ASM_L(orrne  r12, #0x20)    /* Set `CPSR.T' based on LR */              \
	__ASM_L(push_cfi {r12})       /* Save `CPSR' */                           \
	__ASM_L(.cfi_rel_offset 128, 0)                                           \
	__ASM_L(sub    r12, sp, #56)  /* Calculate `sp' at function entry */      \
	__ASM_L(push_cfi {r12})       /* Save `sp' */                             \
	__ARM_ASM_DBGN(__ASM_L(sub sp, sp, #4)) /* Skip over `lr' (unknown) */    \
	__ARM_ASM_DBGY(__ASM_L(ldr r12, =0xCCCCCCCC))                             \
	__ARM_ASM_DBGY(__ASM_L(push {r12}))                                       \
	__ASM_L(.cfi_adjust_cfa_offset 4)                                         \
	__ASM_L(bic    r12, lr, #1)   /* Clear thumb-mode bit */                  \
	__ASM_L(push_cfi {r12})       /* Save `pc' */                             \
	__ASM_L(.cfi_rel_offset 15, 0)
#define ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R ASM_PUSH_UCPUSTATE_ON_ENTRY_CFI_R
#define ASM_PUSH_ICPUSTATE_ON_ENTRY_CFI_R ASM_PUSH_UCPUSTATE_ON_ENTRY_CFI_R
#define ASM_PUSH_SCPUSTATE_ON_ENTRY_CFI_R ASM_PUSH_UCPUSTATE_ON_ENTRY_CFI_R

/* Restore registers from a `struct ucpustate' at `%cfa + offset' */
#define ASM_CFI_OFFSET_RESTORE_UCPUSTATE(offset)               \
	__ASM_L(.cfi_offset 0,  ((offset) + OFFSET_UCPUSTATE_R0))  \
	__ASM_L(.cfi_offset 1,  ((offset) + OFFSET_UCPUSTATE_R1))  \
	__ASM_L(.cfi_offset 2,  ((offset) + OFFSET_UCPUSTATE_R2))  \
	__ASM_L(.cfi_offset 3,  ((offset) + OFFSET_UCPUSTATE_R3))  \
	__ASM_L(.cfi_offset 4,  ((offset) + OFFSET_UCPUSTATE_R4))  \
	__ASM_L(.cfi_offset 5,  ((offset) + OFFSET_UCPUSTATE_R5))  \
	__ASM_L(.cfi_offset 6,  ((offset) + OFFSET_UCPUSTATE_R6))  \
	__ASM_L(.cfi_offset 7,  ((offset) + OFFSET_UCPUSTATE_R7))  \
	__ASM_L(.cfi_offset 8,  ((offset) + OFFSET_UCPUSTATE_R8))  \
	__ASM_L(.cfi_offset 9,  ((offset) + OFFSET_UCPUSTATE_R9))  \
	__ASM_L(.cfi_offset 10, ((offset) + OFFSET_UCPUSTATE_R10)) \
	__ASM_L(.cfi_offset 11, ((offset) + OFFSET_UCPUSTATE_R11)) \
	__ASM_L(.cfi_offset 12, ((offset) + OFFSET_UCPUSTATE_R12)) \
	__ASM_L(.cfi_offset 13, ((offset) + OFFSET_UCPUSTATE_SP))  \
	__ASM_L(.cfi_offset 14, ((offset) + OFFSET_UCPUSTATE_LR))  \
	__ASM_L(.cfi_offset 15, ((offset) + OFFSET_UCPUSTATE_PC))  \
	__ASM_L(.cfi_offset 128, ((offset) + OFFSET_UCPUSTATE_CPSR))
#define ASM_CFI_OFFSET_RESTORE_KCPUSTATE ASM_CFI_OFFSET_RESTORE_UCPUSTATE
#define ASM_CFI_OFFSET_RESTORE_ICPUSTATE ASM_CFI_OFFSET_RESTORE_UCPUSTATE
#define ASM_CFI_OFFSET_RESTORE_SCPUSTATE ASM_CFI_OFFSET_RESTORE_UCPUSTATE


/* clang-format on */

#endif /* !_ARM_KOS_KOS_KERNEL_BITS_CPU_STATE_ASM_H */
