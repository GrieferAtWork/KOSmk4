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
#ifndef _I386_KOS_KOS_KERNEL_CPU_STATE_ASM64_H
#define _I386_KOS_KOS_KERNEL_CPU_STATE_ASM64_H 1

#include <hybrid/host.h>

#include "cpu-state64.h"

#ifdef __x86_64__
#include <asm/cfi.h>
#include <hybrid/__asm.h>

/* Helper macros for restoring registers from cpu-state structures */
#define ASM_CFI_REL_OFFSET_RESTORE_GPREGSNSP(offset)                 \
	__ASM_L(.cfi_rel_offset %r15, ((offset) + OFFSET_GPREGSNSP_R15)) \
	__ASM_L(.cfi_rel_offset %r14, ((offset) + OFFSET_GPREGSNSP_R14)) \
	__ASM_L(.cfi_rel_offset %r13, ((offset) + OFFSET_GPREGSNSP_R13)) \
	__ASM_L(.cfi_rel_offset %r12, ((offset) + OFFSET_GPREGSNSP_R12)) \
	__ASM_L(.cfi_rel_offset %r11, ((offset) + OFFSET_GPREGSNSP_R11)) \
	__ASM_L(.cfi_rel_offset %r10, ((offset) + OFFSET_GPREGSNSP_R10)) \
	__ASM_L(.cfi_rel_offset %r9, ((offset) + OFFSET_GPREGSNSP_R9))   \
	__ASM_L(.cfi_rel_offset %r8, ((offset) + OFFSET_GPREGSNSP_R8))   \
	__ASM_L(.cfi_rel_offset %rdi, ((offset) + OFFSET_GPREGSNSP_RDI)) \
	__ASM_L(.cfi_rel_offset %rsi, ((offset) + OFFSET_GPREGSNSP_RSI)) \
	__ASM_L(.cfi_rel_offset %rbp, ((offset) + OFFSET_GPREGSNSP_RBP)) \
	__ASM_L(.cfi_rel_offset %rbx, ((offset) + OFFSET_GPREGSNSP_RBX)) \
	__ASM_L(.cfi_rel_offset %rdx, ((offset) + OFFSET_GPREGSNSP_RDX)) \
	__ASM_L(.cfi_rel_offset %rcx, ((offset) + OFFSET_GPREGSNSP_RCX)) \
	__ASM_L(.cfi_rel_offset %rax, ((offset) + OFFSET_GPREGSNSP_RAX))

#define ASM_CFI_REL_OFFSET_RESTORE_GPREGS(offset)                 \
	__ASM_L(.cfi_rel_offset %r15, ((offset) + OFFSET_GPREGS_R15)) \
	__ASM_L(.cfi_rel_offset %r14, ((offset) + OFFSET_GPREGS_R14)) \
	__ASM_L(.cfi_rel_offset %r13, ((offset) + OFFSET_GPREGS_R13)) \
	__ASM_L(.cfi_rel_offset %r12, ((offset) + OFFSET_GPREGS_R12)) \
	__ASM_L(.cfi_rel_offset %r11, ((offset) + OFFSET_GPREGS_R11)) \
	__ASM_L(.cfi_rel_offset %r10, ((offset) + OFFSET_GPREGS_R10)) \
	__ASM_L(.cfi_rel_offset %r9, ((offset) + OFFSET_GPREGS_R9))   \
	__ASM_L(.cfi_rel_offset %r8, ((offset) + OFFSET_GPREGS_R8))   \
	__ASM_L(.cfi_rel_offset %rdi, ((offset) + OFFSET_GPREGS_RDI)) \
	__ASM_L(.cfi_rel_offset %rsi, ((offset) + OFFSET_GPREGS_RSI)) \
	__ASM_L(.cfi_rel_offset %rbp, ((offset) + OFFSET_GPREGS_RBP)) \
	__ASM_L(.cfi_rel_offset %rsp, ((offset) + OFFSET_GPREGS_RSP)) \
	__ASM_L(.cfi_rel_offset %rbx, ((offset) + OFFSET_GPREGS_RBX)) \
	__ASM_L(.cfi_rel_offset %rdx, ((offset) + OFFSET_GPREGS_RDX)) \
	__ASM_L(.cfi_rel_offset %rcx, ((offset) + OFFSET_GPREGS_RCX)) \
	__ASM_L(.cfi_rel_offset %rax, ((offset) + OFFSET_GPREGS_RAX))

#define ASM_CFI_REL_OFFSET_RESTORE_KCPUSTATE(offset)                       \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGS((offset) + OFFSET_KCPUSTATE_GPREGS); \
	__ASM_L(.cfi_rel_offset %rflags, ((offset) + OFFSET_KCPUSTATE_RFLAGS)) \
	__ASM_L(.cfi_rel_offset %rip, ((offset) + OFFSET_KCPUSTATE_RIP))


/* Push all current general-purpose registers to form a a `struct gpregsnsp64'
 * that will be stored at `0(%rsp)' upon return. Additionally, generate cfi
 * instrumentation to allow all pushed registered to be restored during unwinding. */
#define ASM_PUSH_GPREGSNSP_CFI_R                                     \
	__ASM_L(pushq_cfi_r %rax) /* [C] Accumulator register */         \
	__ASM_L(pushq_cfi_r %rcx) /* [C] Count register */               \
	__ASM_L(pushq_cfi_r %rdx) /* [C] Data register */                \
	__ASM_L(pushq_cfi_r %rbx) /* [P] Base register */                \
	__ASM_L(pushq_cfi_r %rbp) /* [P] Frame base pointer */           \
	__ASM_L(pushq_cfi_r %rsi) /* [C] Source pointer */               \
	__ASM_L(pushq_cfi_r %rdi) /* [C] Destination pointer */          \
	__ASM_L(pushq_cfi_r %r8)  /* [C] General purpose register #8 */  \
	__ASM_L(pushq_cfi_r %r9)  /* [C] General purpose register #9 */  \
	__ASM_L(pushq_cfi_r %r10) /* [C] General purpose register #10 */ \
	__ASM_L(pushq_cfi_r %r11) /* [C] General purpose register #11 */ \
	__ASM_L(pushq_cfi_r %r12) /* [P] General purpose register #12 */ \
	__ASM_L(pushq_cfi_r %r13) /* [P] General purpose register #13 */ \
	__ASM_L(pushq_cfi_r %r14) /* [P] General purpose register #14 */ \
	__ASM_L(pushq_cfi_r %r15) /* [P] General purpose register #15 */

/* Restore general purpose registers from a `struct gpregsnsp64' stored
 * at `0(%rsp)', as well as increment `%rsp += SIZEOF_GPREGSNSP64'
 * Additionally, generate CFI instrumentation to indicate that registers
 * loaded with stack-values have re-gained their original values and should
 * not be modified during unwinding (s.a. `.cfi_restore') */
#define ASM_POP_GPREGSNSP_CFI_R                                     \
	__ASM_L(popq_cfi_r %r15) /* [P] General purpose register #15 */ \
	__ASM_L(popq_cfi_r %r14) /* [P] General purpose register #14 */ \
	__ASM_L(popq_cfi_r %r13) /* [P] General purpose register #13 */ \
	__ASM_L(popq_cfi_r %r12) /* [P] General purpose register #12 */ \
	__ASM_L(popq_cfi_r %r11) /* [C] General purpose register #11 */ \
	__ASM_L(popq_cfi_r %r10) /* [C] General purpose register #10 */ \
	__ASM_L(popq_cfi_r %r9)  /* [C] General purpose register #9 */  \
	__ASM_L(popq_cfi_r %r8)  /* [C] General purpose register #8 */  \
	__ASM_L(popq_cfi_r %rdi) /* [C] Destination pointer */          \
	__ASM_L(popq_cfi_r %rsi) /* [C] Source pointer */               \
	__ASM_L(popq_cfi_r %rbp) /* [P] Frame base pointer */           \
	__ASM_L(popq_cfi_r %rbx) /* [P] Base register */                \
	__ASM_L(popq_cfi_r %rdx) /* [C] Data register */                \
	__ASM_L(popq_cfi_r %rcx) /* [C] Count register */               \
	__ASM_L(popq_cfi_r %rax) /* [C] Accumulator register */         \




#endif /* __x86_64__ */


#endif /* !_I386_KOS_KOS_KERNEL_CPU_STATE_ASM64_H */
