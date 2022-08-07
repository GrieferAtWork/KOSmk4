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
#ifndef _I386_KOS_KOS_KERNEL_BITS_CPU_STATE_ASM64_H
#define _I386_KOS_KOS_KERNEL_BITS_CPU_STATE_ASM64_H 1

#include <hybrid/host.h>

#include "cpu-state64.h"

#ifdef __x86_64__
#include <hybrid/__asm.h>

#include <asm/cfi.h>
#include <asm/instr/kgsbase.h>

/* Helper macros for restoring registers from cpu-state structures */

/* RESTORE: ... = *(struct gpregsnsp64 const *)(CFA + CFA_OFFSET + offset) */
#define ASM_CFI_REL_OFFSET_RESTORE_GPREGSNSP(offset)                   \
	__ASM_L(.cfi_rel_offset %rax, ((offset) + OFFSET_GPREGSNSP64_RAX)) \
	__ASM_L(.cfi_rel_offset %rcx, ((offset) + OFFSET_GPREGSNSP64_RCX)) \
	__ASM_L(.cfi_rel_offset %rdx, ((offset) + OFFSET_GPREGSNSP64_RDX)) \
	__ASM_L(.cfi_rel_offset %rbx, ((offset) + OFFSET_GPREGSNSP64_RBX)) \
	__ASM_L(.cfi_rel_offset %rbp, ((offset) + OFFSET_GPREGSNSP64_RBP)) \
	__ASM_L(.cfi_rel_offset %rsi, ((offset) + OFFSET_GPREGSNSP64_RSI)) \
	__ASM_L(.cfi_rel_offset %rdi, ((offset) + OFFSET_GPREGSNSP64_RDI)) \
	__ASM_L(.cfi_rel_offset %r8, ((offset) + OFFSET_GPREGSNSP64_R8))   \
	__ASM_L(.cfi_rel_offset %r9, ((offset) + OFFSET_GPREGSNSP64_R9))   \
	__ASM_L(.cfi_rel_offset %r10, ((offset) + OFFSET_GPREGSNSP64_R10)) \
	__ASM_L(.cfi_rel_offset %r11, ((offset) + OFFSET_GPREGSNSP64_R11)) \
	__ASM_L(.cfi_rel_offset %r12, ((offset) + OFFSET_GPREGSNSP64_R12)) \
	__ASM_L(.cfi_rel_offset %r13, ((offset) + OFFSET_GPREGSNSP64_R13)) \
	__ASM_L(.cfi_rel_offset %r14, ((offset) + OFFSET_GPREGSNSP64_R14)) \
	__ASM_L(.cfi_rel_offset %r15, ((offset) + OFFSET_GPREGSNSP64_R15))

/* RESTORE: ... = *(struct gpregsnsp64 const *)(CFA + offset) */
#define ASM_CFI_OFFSET_RESTORE_GPREGSNSP(offset)                   \
	__ASM_L(.cfi_offset %rax, ((offset) + OFFSET_GPREGSNSP64_RAX)) \
	__ASM_L(.cfi_offset %rcx, ((offset) + OFFSET_GPREGSNSP64_RCX)) \
	__ASM_L(.cfi_offset %rdx, ((offset) + OFFSET_GPREGSNSP64_RDX)) \
	__ASM_L(.cfi_offset %rbx, ((offset) + OFFSET_GPREGSNSP64_RBX)) \
	__ASM_L(.cfi_offset %rbp, ((offset) + OFFSET_GPREGSNSP64_RBP)) \
	__ASM_L(.cfi_offset %rsi, ((offset) + OFFSET_GPREGSNSP64_RSI)) \
	__ASM_L(.cfi_offset %rdi, ((offset) + OFFSET_GPREGSNSP64_RDI)) \
	__ASM_L(.cfi_offset %r8, ((offset) + OFFSET_GPREGSNSP64_R8))   \
	__ASM_L(.cfi_offset %r9, ((offset) + OFFSET_GPREGSNSP64_R9))   \
	__ASM_L(.cfi_offset %r10, ((offset) + OFFSET_GPREGSNSP64_R10)) \
	__ASM_L(.cfi_offset %r11, ((offset) + OFFSET_GPREGSNSP64_R11)) \
	__ASM_L(.cfi_offset %r12, ((offset) + OFFSET_GPREGSNSP64_R12)) \
	__ASM_L(.cfi_offset %r13, ((offset) + OFFSET_GPREGSNSP64_R13)) \
	__ASM_L(.cfi_offset %r14, ((offset) + OFFSET_GPREGSNSP64_R14)) \
	__ASM_L(.cfi_offset %r15, ((offset) + OFFSET_GPREGSNSP64_R15))

/* RESTORE: ... = *(struct gpregsnsp64 const *)(%reg + offset) */
#define ASM_CFI_REG_OFFSET_RESTORE_GPREGSNSP(offset, reg)                   \
	__ASM_L(.cfi_reg_offset %rax, ((offset) + OFFSET_GPREGSNSP64_RAX), reg) \
	__ASM_L(.cfi_reg_offset %rcx, ((offset) + OFFSET_GPREGSNSP64_RCX), reg) \
	__ASM_L(.cfi_reg_offset %rdx, ((offset) + OFFSET_GPREGSNSP64_RDX), reg) \
	__ASM_L(.cfi_reg_offset %rbx, ((offset) + OFFSET_GPREGSNSP64_RBX), reg) \
	__ASM_L(.cfi_reg_offset %rbp, ((offset) + OFFSET_GPREGSNSP64_RBP), reg) \
	__ASM_L(.cfi_reg_offset %rsi, ((offset) + OFFSET_GPREGSNSP64_RSI), reg) \
	__ASM_L(.cfi_reg_offset %rdi, ((offset) + OFFSET_GPREGSNSP64_RDI), reg) \
	__ASM_L(.cfi_reg_offset %r8, ((offset) + OFFSET_GPREGSNSP64_R8), reg)   \
	__ASM_L(.cfi_reg_offset %r9, ((offset) + OFFSET_GPREGSNSP64_R9), reg)   \
	__ASM_L(.cfi_reg_offset %r10, ((offset) + OFFSET_GPREGSNSP64_R10), reg) \
	__ASM_L(.cfi_reg_offset %r11, ((offset) + OFFSET_GPREGSNSP64_R11), reg) \
	__ASM_L(.cfi_reg_offset %r12, ((offset) + OFFSET_GPREGSNSP64_R12), reg) \
	__ASM_L(.cfi_reg_offset %r13, ((offset) + OFFSET_GPREGSNSP64_R13), reg) \
	__ASM_L(.cfi_reg_offset %r14, ((offset) + OFFSET_GPREGSNSP64_R14), reg) \
	__ASM_L(.cfi_reg_offset %r15, ((offset) + OFFSET_GPREGSNSP64_R15), reg)



/* RESTORE: ... = *(struct sgregs64 const *)(CFA + CFA_OFFSET + offset) */
#define ASM_CFI_REL_OFFSET_RESTORE_SGREGS(offset)                 \
	__ASM_L(.cfi_rel_offset %gs, ((offset) + OFFSET_SGREGS64_GS)) \
	__ASM_L(.cfi_rel_offset %fs, ((offset) + OFFSET_SGREGS64_FS)) \
	__ASM_L(.cfi_rel_offset %es, ((offset) + OFFSET_SGREGS64_ES)) \
	__ASM_L(.cfi_rel_offset %ds, ((offset) + OFFSET_SGREGS64_DS))

/* RESTORE: ... = *(struct sgregs64 const *)(CFA + offset) */
#define ASM_CFI_OFFSET_RESTORE_SGREGS(offset)                 \
	__ASM_L(.cfi_offset %gs, ((offset) + OFFSET_SGREGS64_GS)) \
	__ASM_L(.cfi_offset %fs, ((offset) + OFFSET_SGREGS64_FS)) \
	__ASM_L(.cfi_offset %es, ((offset) + OFFSET_SGREGS64_ES)) \
	__ASM_L(.cfi_offset %ds, ((offset) + OFFSET_SGREGS64_DS))

/* RESTORE: ... = *(struct sgregs64 const *)(%reg + offset) */
#define ASM_CFI_REG_OFFSET_RESTORE_SGREGS(offset, reg)               \
	__ASM_L(.cfi_reg_offset %gs, ((offset) + OFFSET_SGREGS_GS), reg) \
	__ASM_L(.cfi_reg_offset %fs, ((offset) + OFFSET_SGREGS_FS), reg) \
	__ASM_L(.cfi_reg_offset %es, ((offset) + OFFSET_SGREGS_ES), reg) \
	__ASM_L(.cfi_reg_offset %ds, ((offset) + OFFSET_SGREGS_DS), reg)



#ifdef __KERNEL__
/* RESTORE: %fs.base = (struct sgbase64 const *)(CFA + offset)->sg_fsbase */
#define ASM_CFI_OFFSET_RESTORE_SGBASE(offset) \
	__ASM_L(.cfi_offset %fs.base, ((offset) + OFFSET_SGBASE64_FSBASE))

/* RESTORE: %fs.base = (struct sgbase64 const *)(CFA + CFA_OFFSET + offset)->sg_fsbase */
#define ASM_CFI_REL_OFFSET_RESTORE_SGBASE(offset) \
	__ASM_L(.cfi_rel_offset %fs.base, ((offset) + OFFSET_SGBASE64_FSBASE))

/* RESTORE: %fs.base = (struct sgbase64 const *)(%reg + offset)->sg_fsbase */
#define ASM_CFI_REG_OFFSET_RESTORE_SGBASE(offset) \
	__ASM_L(.cfi_reg_offset %fs.base, ((offset) + OFFSET_SGBASE64_FSBASE), reg)
#else /* __KERNEL__ */
/* RESTORE: ... = *(struct sgbase64 const *)(CFA + offset) */
#define ASM_CFI_OFFSET_RESTORE_SGBASE(offset)                          \
	__ASM_L(.cfi_offset %fs.base, ((offset) + OFFSET_SGBASE64_FSBASE)) \
	__ASM_L(.cfi_offset %gs.base, ((offset) + OFFSET_SGBASE64_GSBASE))

/* RESTORE: ... = *(struct sgbase64 const *)(CFA + CFA_OFFSET + offset) */
#define ASM_CFI_REL_OFFSET_RESTORE_SGBASE(offset)                          \
	__ASM_L(.cfi_rel_offset %fs.base, ((offset) + OFFSET_SGBASE64_FSBASE)) \
	__ASM_L(.cfi_rel_offset %gs.base, ((offset) + OFFSET_SGBASE64_GSBASE))

/* RESTORE: ... = *(struct sgbase64 const *)(%reg + offset) */
#define ASM_CFI_REG_OFFSET_RESTORE_SGBASE(offset, reg)                          \
	__ASM_L(.cfi_reg_offset %fs.base, ((offset) + OFFSET_SGBASE64_FSBASE), reg) \
	__ASM_L(.cfi_reg_offset %gs.base, ((offset) + OFFSET_SGBASE64_GSBASE), reg)
#endif /* !__KERNEL__ */



/* RESTORE: ... = *(struct gpregs64 const *)(CFA + offset) */
#define ASM_CFI_OFFSET_RESTORE_GPREGS(offset)                   \
	__ASM_L(.cfi_offset %rax, ((offset) + OFFSET_GPREGS64_RAX)) \
	__ASM_L(.cfi_offset %rcx, ((offset) + OFFSET_GPREGS64_RCX)) \
	__ASM_L(.cfi_offset %rdx, ((offset) + OFFSET_GPREGS64_RDX)) \
	__ASM_L(.cfi_offset %rbx, ((offset) + OFFSET_GPREGS64_RBX)) \
	__ASM_L(.cfi_offset %rsp, ((offset) + OFFSET_GPREGS64_RSP)) \
	__ASM_L(.cfi_offset %rbp, ((offset) + OFFSET_GPREGS64_RBP)) \
	__ASM_L(.cfi_offset %rsi, ((offset) + OFFSET_GPREGS64_RSI)) \
	__ASM_L(.cfi_offset %rdi, ((offset) + OFFSET_GPREGS64_RDI)) \
	__ASM_L(.cfi_offset %r8, ((offset) + OFFSET_GPREGS64_R8))   \
	__ASM_L(.cfi_offset %r9, ((offset) + OFFSET_GPREGS64_R9))   \
	__ASM_L(.cfi_offset %r10, ((offset) + OFFSET_GPREGS64_R10)) \
	__ASM_L(.cfi_offset %r11, ((offset) + OFFSET_GPREGS64_R11)) \
	__ASM_L(.cfi_offset %r12, ((offset) + OFFSET_GPREGS64_R12)) \
	__ASM_L(.cfi_offset %r13, ((offset) + OFFSET_GPREGS64_R13)) \
	__ASM_L(.cfi_offset %r14, ((offset) + OFFSET_GPREGS64_R14)) \
	__ASM_L(.cfi_offset %r15, ((offset) + OFFSET_GPREGS64_R15))

/* RESTORE: ... = *(struct gpregs64 const *)(CFA + CFA_OFFSET + offset) */
#define ASM_CFI_REL_OFFSET_RESTORE_GPREGS(offset)                   \
	__ASM_L(.cfi_rel_offset %rax, ((offset) + OFFSET_GPREGS64_RAX)) \
	__ASM_L(.cfi_rel_offset %rcx, ((offset) + OFFSET_GPREGS64_RCX)) \
	__ASM_L(.cfi_rel_offset %rdx, ((offset) + OFFSET_GPREGS64_RDX)) \
	__ASM_L(.cfi_rel_offset %rbx, ((offset) + OFFSET_GPREGS64_RBX)) \
	__ASM_L(.cfi_rel_offset %rsp, ((offset) + OFFSET_GPREGS64_RSP)) \
	__ASM_L(.cfi_rel_offset %rbp, ((offset) + OFFSET_GPREGS64_RBP)) \
	__ASM_L(.cfi_rel_offset %rsi, ((offset) + OFFSET_GPREGS64_RSI)) \
	__ASM_L(.cfi_rel_offset %rdi, ((offset) + OFFSET_GPREGS64_RDI)) \
	__ASM_L(.cfi_rel_offset %r8, ((offset) + OFFSET_GPREGS64_R8))   \
	__ASM_L(.cfi_rel_offset %r9, ((offset) + OFFSET_GPREGS64_R9))   \
	__ASM_L(.cfi_rel_offset %r10, ((offset) + OFFSET_GPREGS64_R10)) \
	__ASM_L(.cfi_rel_offset %r11, ((offset) + OFFSET_GPREGS64_R11)) \
	__ASM_L(.cfi_rel_offset %r12, ((offset) + OFFSET_GPREGS64_R12)) \
	__ASM_L(.cfi_rel_offset %r13, ((offset) + OFFSET_GPREGS64_R13)) \
	__ASM_L(.cfi_rel_offset %r14, ((offset) + OFFSET_GPREGS64_R14)) \
	__ASM_L(.cfi_rel_offset %r15, ((offset) + OFFSET_GPREGS64_R15))

/* RESTORE: ... = *(struct gpregs64 const *)(%reg + offset) */
#define ASM_CFI_REG_OFFSET_RESTORE_GPREGS(offset, reg)                   \
	__ASM_L(.cfi_reg_offset %rax, ((offset) + OFFSET_GPREGS64_RAX), reg) \
	__ASM_L(.cfi_reg_offset %rcx, ((offset) + OFFSET_GPREGS64_RCX), reg) \
	__ASM_L(.cfi_reg_offset %rdx, ((offset) + OFFSET_GPREGS64_RDX), reg) \
	__ASM_L(.cfi_reg_offset %rbx, ((offset) + OFFSET_GPREGS64_RBX), reg) \
	__ASM_L(.cfi_reg_offset %rsp, ((offset) + OFFSET_GPREGS64_RSP), reg) \
	__ASM_L(.cfi_reg_offset %rbp, ((offset) + OFFSET_GPREGS64_RBP), reg) \
	__ASM_L(.cfi_reg_offset %rsi, ((offset) + OFFSET_GPREGS64_RSI), reg) \
	__ASM_L(.cfi_reg_offset %rdi, ((offset) + OFFSET_GPREGS64_RDI), reg) \
	__ASM_L(.cfi_reg_offset %r8, ((offset) + OFFSET_GPREGS64_R8), reg)   \
	__ASM_L(.cfi_reg_offset %r9, ((offset) + OFFSET_GPREGS64_R9), reg)   \
	__ASM_L(.cfi_reg_offset %r10, ((offset) + OFFSET_GPREGS64_R10), reg) \
	__ASM_L(.cfi_reg_offset %r11, ((offset) + OFFSET_GPREGS64_R11), reg) \
	__ASM_L(.cfi_reg_offset %r12, ((offset) + OFFSET_GPREGS64_R12), reg) \
	__ASM_L(.cfi_reg_offset %r13, ((offset) + OFFSET_GPREGS64_R13), reg) \
	__ASM_L(.cfi_reg_offset %r14, ((offset) + OFFSET_GPREGS64_R14), reg) \
	__ASM_L(.cfi_reg_offset %r15, ((offset) + OFFSET_GPREGS64_R15), reg)



/* RESTORE: ... = *(struct irregs64 const *)(CFA + offset) */
#define ASM_CFI_OFFSET_RESTORE_IRREGS(offset)                         \
	__ASM_L(.cfi_offset %ss, ((offset) + OFFSET_IRREGS64_SS))         \
	__ASM_L(.cfi_offset %rsp, ((offset) + OFFSET_IRREGS64_RSP))       \
	__ASM_L(.cfi_offset %rflags, ((offset) + OFFSET_IRREGS64_RFLAGS)) \
	__ASM_L(.cfi_offset %cs, ((offset) + OFFSET_IRREGS64_CS))         \
	__ASM_L(.cfi_offset %rip, ((offset) + OFFSET_IRREGS64_RIP))

/* RESTORE: ... = *(struct irregs64 const *)(CFA + CFA_OFFSET + offset) */
#define ASM_CFI_REL_OFFSET_RESTORE_IRREGS(offset)                         \
	__ASM_L(.cfi_rel_offset %ss, ((offset) + OFFSET_IRREGS64_SS))         \
	__ASM_L(.cfi_rel_offset %rsp, ((offset) + OFFSET_IRREGS64_RSP))       \
	__ASM_L(.cfi_rel_offset %rflags, ((offset) + OFFSET_IRREGS64_RFLAGS)) \
	__ASM_L(.cfi_rel_offset %cs, ((offset) + OFFSET_IRREGS64_CS))         \
	__ASM_L(.cfi_rel_offset %rip, ((offset) + OFFSET_IRREGS64_RIP))

/* RESTORE: ... = *(struct irregs64 const *)(%reg + offset) */
#define ASM_CFI_REG_OFFSET_RESTORE_IRREGS(offset, reg)                         \
	__ASM_L(.cfi_reg_offset %ss, ((offset) + OFFSET_IRREGS64_SS), reg)         \
	__ASM_L(.cfi_reg_offset %rsp, ((offset) + OFFSET_IRREGS64_RSP), reg)       \
	__ASM_L(.cfi_reg_offset %rflags, ((offset) + OFFSET_IRREGS64_RFLAGS), reg) \
	__ASM_L(.cfi_reg_offset %cs, ((offset) + OFFSET_IRREGS64_CS), reg)         \
	__ASM_L(.cfi_reg_offset %rip, ((offset) + OFFSET_IRREGS64_RIP), reg)



/* RESTORE: ... = *(struct kcpustate64 const *)(CFA + offset) */
#define ASM_CFI_OFFSET_RESTORE_KCPUSTATE(offset)                         \
	__ASM_L(.cfi_offset %rip, ((offset) + OFFSET_KCPUSTATE64_RIP))       \
	__ASM_L(.cfi_offset %rflags, ((offset) + OFFSET_KCPUSTATE64_RFLAGS)) \
	ASM_CFI_OFFSET_RESTORE_GPREGS((offset) + OFFSET_KCPUSTATE64_GPREGS)

/* RESTORE: ... = *(struct kcpustate64 const *)(CFA + CFA_OFFSET + offset) */
#define ASM_CFI_REL_OFFSET_RESTORE_KCPUSTATE(offset)                         \
	__ASM_L(.cfi_rel_offset %rip, ((offset) + OFFSET_KCPUSTATE64_RIP))       \
	__ASM_L(.cfi_rel_offset %rflags, ((offset) + OFFSET_KCPUSTATE64_RFLAGS)) \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGS((offset) + OFFSET_KCPUSTATE64_GPREGS)

/* RESTORE: ... = *(struct kcpustate64 const *)(%reg + offset) */
#define ASM_CFI_REG_OFFSET_RESTORE_KCPUSTATE(offset, reg)                         \
	__ASM_L(.cfi_reg_offset %rip, ((offset) + OFFSET_KCPUSTATE64_RIP), reg)       \
	__ASM_L(.cfi_reg_offset %rflags, ((offset) + OFFSET_KCPUSTATE64_RFLAGS), reg) \
	ASM_CFI_REG_OFFSET_RESTORE_GPREGS((offset) + OFFSET_KCPUSTATE64_GPREGS, reg)



/* RESTORE: ... = *(struct scpustate64 const *)(CFA + offset) */
#define ASM_CFI_OFFSET_RESTORE_SCPUSTATE(offset)                              \
	ASM_CFI_OFFSET_RESTORE_IRREGS((offset) + OFFSET_SCPUSTATE64_IRREGS)       \
	ASM_CFI_OFFSET_RESTORE_GPREGSNSP((offset) + OFFSET_SCPUSTATE64_GPREGSNSP) \
	ASM_CFI_OFFSET_RESTORE_SGBASE((offset) + OFFSET_SCPUSTATE64_SGBASE)       \
	ASM_CFI_OFFSET_RESTORE_SGREGS((offset) + OFFSET_SCPUSTATE64_SGREGS)

/* RESTORE: ... = *(struct scpustate64 const *)(CFA + CFA_OFFSET + offset) */
#define ASM_CFI_REL_OFFSET_RESTORE_SCPUSTATE(offset)                              \
	ASM_CFI_REL_OFFSET_RESTORE_IRREGS((offset) + OFFSET_SCPUSTATE64_IRREGS)       \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGSNSP((offset) + OFFSET_SCPUSTATE64_GPREGSNSP) \
	ASM_CFI_REL_OFFSET_RESTORE_SGBASE((offset) + OFFSET_SCPUSTATE64_SGBASE)       \
	ASM_CFI_REL_OFFSET_RESTORE_SGREGS((offset) + OFFSET_SCPUSTATE64_SGREGS)

/* RESTORE: ... = *(struct scpustate64 const *)(%reg + offset) */
#define ASM_CFI_REG_OFFSET_RESTORE_SCPUSTATE(offset, reg)                              \
	ASM_CFI_REG_OFFSET_RESTORE_IRREGS((offset) + OFFSET_SCPUSTATE64_IRREGS, reg)       \
	ASM_CFI_REG_OFFSET_RESTORE_GPREGSNSP((offset) + OFFSET_SCPUSTATE64_GPREGSNSP, reg) \
	ASM_CFI_REG_OFFSET_RESTORE_SGBASE((offset) + OFFSET_SCPUSTATE64_SGBASE, reg)       \
	ASM_CFI_REG_OFFSET_RESTORE_SGREGS((offset) + OFFSET_SCPUSTATE64_SGREGS, reg)



/* RESTORE: ... = *(struct icpustate64 const *)(CFA + offset) */
#define ASM_CFI_OFFSET_RESTORE_ICPUSTATE(offset)                        \
	ASM_CFI_OFFSET_RESTORE_IRREGS((offset) + OFFSET_ICPUSTATE64_IRREGS) \
	ASM_CFI_OFFSET_RESTORE_GPREGSNSP((offset) + OFFSET_ICPUSTATE64_GPREGSNSP)

/* RESTORE: ... = *(struct icpustate64 const *)(CFA + CFA_OFFSET + offset) */
#define ASM_CFI_REL_OFFSET_RESTORE_ICPUSTATE(offset)                        \
	ASM_CFI_REL_OFFSET_RESTORE_IRREGS((offset) + OFFSET_ICPUSTATE64_IRREGS) \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGSNSP((offset) + OFFSET_ICPUSTATE64_GPREGSNSP)

/* RESTORE: ... = *(struct icpustate64 const *)(%reg + offset) */
#define ASM_CFI_REG_OFFSET_RESTORE_ICPUSTATE(offset, reg)                        \
	ASM_CFI_REG_OFFSET_RESTORE_IRREGS((offset) + OFFSET_ICPUSTATE64_IRREGS, reg) \
	ASM_CFI_REG_OFFSET_RESTORE_GPREGSNSP((offset) + OFFSET_ICPUSTATE64_GPREGSNSP, reg)



/* RESTORE: ... = *(struct ucpustate64 const *)(CFA + offset) */
#define ASM_CFI_OFFSET_RESTORE_UCPUSTATE(offset)                        \
	__ASM_L(.cfi_offset %rip, (offset) + OFFSET_UCPUSTATE64_RIP)        \
	ASM_CFI_OFFSET_RESTORE_GPREGS((offset) + OFFSET_UCPUSTATE64_GPREGS) \
	__ASM_L(.cfi_offset %rflags, (offset) + OFFSET_UCPUSTATE64_RFLAGS)  \
	__ASM_L(.cfi_offset %ss, (offset) + OFFSET_UCPUSTATE64_SS)          \
	__ASM_L(.cfi_offset %cs, (offset) + OFFSET_UCPUSTATE64_CS)          \
	ASM_CFI_OFFSET_RESTORE_SGREGS((offset) + OFFSET_UCPUSTATE64_SGREGS) \
	ASM_CFI_OFFSET_RESTORE_SGBASE((offset) + OFFSET_UCPUSTATE64_SGBASE)

/* RESTORE: ... = *(struct ucpustate64 const *)(CFA + CFA_OFFSET + offset) */
#define ASM_CFI_REL_OFFSET_RESTORE_UCPUSTATE(offset)                        \
	__ASM_L(.cfi_rel_offset %rip, (offset) + OFFSET_UCPUSTATE64_RIP)        \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGS((offset) + OFFSET_UCPUSTATE64_GPREGS) \
	__ASM_L(.cfi_rel_offset %rflags, (offset) + OFFSET_UCPUSTATE64_RFLAGS)  \
	__ASM_L(.cfi_rel_offset %ss, (offset) + OFFSET_UCPUSTATE64_SS)          \
	__ASM_L(.cfi_rel_offset %cs, (offset) + OFFSET_UCPUSTATE64_CS)          \
	ASM_CFI_REL_OFFSET_RESTORE_SGREGS((offset) + OFFSET_UCPUSTATE64_SGREGS) \
	ASM_CFI_REL_OFFSET_RESTORE_SGBASE((offset) + OFFSET_UCPUSTATE64_SGBASE)

/* RESTORE: ... = *(struct ucpustate64 const *)(%reg + offset) */
#define ASM_CFI_REG_OFFSET_RESTORE_UCPUSTATE(offset, reg)                        \
	__ASM_L(.cfi_reg_offset %rip, (offset) + OFFSET_UCPUSTATE64_RIP, reg)        \
	ASM_CFI_REG_OFFSET_RESTORE_GPREGS((offset) + OFFSET_UCPUSTATE64_GPREGS, reg) \
	__ASM_L(.cfi_reg_offset %rflags, (offset) + OFFSET_UCPUSTATE64_RFLAGS, reg)  \
	__ASM_L(.cfi_reg_offset %ss, (offset) + OFFSET_UCPUSTATE64_SS, reg)          \
	__ASM_L(.cfi_reg_offset %cs, (offset) + OFFSET_UCPUSTATE64_CS, reg)          \
	ASM_CFI_REG_OFFSET_RESTORE_SGREGS((offset) + OFFSET_UCPUSTATE64_SGREGS, reg) \
	ASM_CFI_REG_OFFSET_RESTORE_SGBASE((offset) + OFFSET_UCPUSTATE64_SGBASE, reg)



/* RESTORE: ... = *(struct lcpustate64 const *)(CFA + offset) */
#define ASM_CFI_OFFSET_RESTORE_LCPUSTATE(offset)                 \
	__ASM_L(.cfi_offset %r15, (offset) + OFFSET_LCPUSTATE64_R15) \
	__ASM_L(.cfi_offset %r14, (offset) + OFFSET_LCPUSTATE64_R14) \
	__ASM_L(.cfi_offset %r13, (offset) + OFFSET_LCPUSTATE64_R13) \
	__ASM_L(.cfi_offset %r12, (offset) + OFFSET_LCPUSTATE64_R12) \
	__ASM_L(.cfi_offset %rbp, (offset) + OFFSET_LCPUSTATE64_RBP) \
	__ASM_L(.cfi_offset %rsp, (offset) + OFFSET_LCPUSTATE64_RSP) \
	__ASM_L(.cfi_offset %rbx, (offset) + OFFSET_LCPUSTATE64_RBX) \
	__ASM_L(.cfi_offset %rip, (offset) + OFFSET_LCPUSTATE64_RIP)

/* RESTORE: ... = *(struct lcpustate64 const *)(CFA + CFA_OFFSET + offset) */
#define ASM_CFI_REL_OFFSET_RESTORE_LCPUSTATE(offset)                 \
	__ASM_L(.cfi_rel_offset %r15, (offset) + OFFSET_LCPUSTATE64_R15) \
	__ASM_L(.cfi_rel_offset %r14, (offset) + OFFSET_LCPUSTATE64_R14) \
	__ASM_L(.cfi_rel_offset %r13, (offset) + OFFSET_LCPUSTATE64_R13) \
	__ASM_L(.cfi_rel_offset %r12, (offset) + OFFSET_LCPUSTATE64_R12) \
	__ASM_L(.cfi_rel_offset %rbp, (offset) + OFFSET_LCPUSTATE64_RBP) \
	__ASM_L(.cfi_rel_offset %rsp, (offset) + OFFSET_LCPUSTATE64_RSP) \
	__ASM_L(.cfi_rel_offset %rbx, (offset) + OFFSET_LCPUSTATE64_RBX) \
	__ASM_L(.cfi_rel_offset %rip, (offset) + OFFSET_LCPUSTATE64_RIP)

/* RESTORE: ... = *(struct lcpustate64 const *)(%reg + offset) */
#define ASM_CFI_REG_OFFSET_RESTORE_LCPUSTATE(offset, reg)                 \
	__ASM_L(.cfi_reg_offset %r15, (offset) + OFFSET_LCPUSTATE64_R15, reg) \
	__ASM_L(.cfi_reg_offset %r14, (offset) + OFFSET_LCPUSTATE64_R14, reg) \
	__ASM_L(.cfi_reg_offset %r13, (offset) + OFFSET_LCPUSTATE64_R13, reg) \
	__ASM_L(.cfi_reg_offset %r12, (offset) + OFFSET_LCPUSTATE64_R12, reg) \
	__ASM_L(.cfi_reg_offset %rbp, (offset) + OFFSET_LCPUSTATE64_RBP, reg) \
	__ASM_L(.cfi_reg_offset %rsp, (offset) + OFFSET_LCPUSTATE64_RSP, reg) \
	__ASM_L(.cfi_reg_offset %rbx, (offset) + OFFSET_LCPUSTATE64_RBX, reg) \
	__ASM_L(.cfi_reg_offset %rip, (offset) + OFFSET_LCPUSTATE64_RIP, reg)



/* RESTORE: ... = *(struct fcpustate64 const *)(CFA + offset) */
#define ASM_CFI_OFFSET_RESTORE_FCPUSTATE(offset)                        \
	ASM_CFI_OFFSET_RESTORE_GPREGS((offset) + OFFSET_FCPUSTATE64_GPREGS) \
	__ASM_L(.cfi_offset %rflags, (offset) + OFFSET_FCPUSTATE64_RFLAGS)  \
	__ASM_L(.cfi_offset %rip, (offset) + OFFSET_FCPUSTATE64_RIP)        \
	__ASM_L(.cfi_offset %es, (offset) + OFFSET_FCPUSTATE64_ES)          \
	__ASM_L(.cfi_offset %cs, (offset) + OFFSET_FCPUSTATE64_CS)          \
	__ASM_L(.cfi_offset %ss, (offset) + OFFSET_FCPUSTATE64_SS)          \
	__ASM_L(.cfi_offset %ds, (offset) + OFFSET_FCPUSTATE64_DS)          \
	__ASM_L(.cfi_offset %fs, (offset) + OFFSET_FCPUSTATE64_FS)          \
	__ASM_L(.cfi_offset %gs, (offset) + OFFSET_FCPUSTATE64_GS)          \
	__ASM_L(.cfi_offset %tr, (offset) + OFFSET_FCPUSTATE64_TR)          \
	__ASM_L(.cfi_offset %ldtr, (offset) + OFFSET_FCPUSTATE64_LDT)       \
	ASM_CFI_OFFSET_RESTORE_SGBASE((offset) + OFFSET_FCPUSTATE64_SGBASE)

/* RESTORE: ... = *(struct fcpustate64 const *)(CFA + CFA_OFFSET + offset) */
#define ASM_CFI_REL_OFFSET_RESTORE_FCPUSTATE(offset)                        \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGS((offset) + OFFSET_FCPUSTATE64_GPREGS) \
	__ASM_L(.cfi_rel_offset %rflags, (offset) + OFFSET_FCPUSTATE64_RFLAGS)  \
	__ASM_L(.cfi_rel_offset %rip, (offset) + OFFSET_FCPUSTATE64_RIP)        \
	__ASM_L(.cfi_rel_offset %es, (offset) + OFFSET_FCPUSTATE64_ES)          \
	__ASM_L(.cfi_rel_offset %cs, (offset) + OFFSET_FCPUSTATE64_CS)          \
	__ASM_L(.cfi_rel_offset %ss, (offset) + OFFSET_FCPUSTATE64_SS)          \
	__ASM_L(.cfi_rel_offset %ds, (offset) + OFFSET_FCPUSTATE64_DS)          \
	__ASM_L(.cfi_rel_offset %fs, (offset) + OFFSET_FCPUSTATE64_FS)          \
	__ASM_L(.cfi_rel_offset %gs, (offset) + OFFSET_FCPUSTATE64_GS)          \
	__ASM_L(.cfi_rel_offset %tr, (offset) + OFFSET_FCPUSTATE64_TR)          \
	__ASM_L(.cfi_rel_offset %ldtr, (offset) + OFFSET_FCPUSTATE64_LDT)       \
	ASM_CFI_REL_OFFSET_RESTORE_SGBASE((offset) + OFFSET_FCPUSTATE64_SGBASE)

/* RESTORE: ... = *(struct fcpustate64 const *)(%reg + offset) */
#define ASM_CFI_REG_OFFSET_RESTORE_FCPUSTATE(offset, reg)                        \
	ASM_CFI_REG_OFFSET_RESTORE_GPREGS((offset) + OFFSET_FCPUSTATE64_GPREGS, reg) \
	__ASM_L(.cfi_reg_offset %rflags, (offset) + OFFSET_FCPUSTATE64_RFLAGS, reg)  \
	__ASM_L(.cfi_reg_offset %rip, (offset) + OFFSET_FCPUSTATE64_RIP, reg)        \
	__ASM_L(.cfi_reg_offset %es, (offset) + OFFSET_FCPUSTATE64_ES, reg)          \
	__ASM_L(.cfi_reg_offset %cs, (offset) + OFFSET_FCPUSTATE64_CS, reg)          \
	__ASM_L(.cfi_reg_offset %ss, (offset) + OFFSET_FCPUSTATE64_SS, reg)          \
	__ASM_L(.cfi_reg_offset %ds, (offset) + OFFSET_FCPUSTATE64_DS, reg)          \
	__ASM_L(.cfi_reg_offset %fs, (offset) + OFFSET_FCPUSTATE64_FS, reg)          \
	__ASM_L(.cfi_reg_offset %gs, (offset) + OFFSET_FCPUSTATE64_GS, reg)          \
	__ASM_L(.cfi_reg_offset %tr, (offset) + OFFSET_FCPUSTATE64_TR, reg)          \
	__ASM_L(.cfi_reg_offset %ldtr, (offset) + OFFSET_FCPUSTATE64_LDT, reg)       \
	ASM_CFI_REG_OFFSET_RESTORE_SGBASE((offset) + OFFSET_FCPUSTATE64_SGBASE, reg)





/* Same as `ASM_PUSH_GPREGSNSP_CFI_R', but don't push %rax */
#define ASM_PUSH_GPREGSNSP_NORAX_CFI_R                               \
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

/* Same as `ASM_POP_GPREGSNSP_CFI_R', but don't pop %rax */
#define ASM_POP_GPREGSNSP_NORAX_CFI_R                               \
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
	__ASM_L(popq_cfi_r %rcx) /* [C] Count register */

/* Push  all current  general-purpose registers  to form  a a `struct gpregsnsp64'
 * that  will  be  stored at  `0(%rsp)'  upon return.  Additionally,  generate cfi
 * instrumentation to allow all pushed registered to be restored during unwinding. */
#define ASM_PUSH_GPREGSNSP_CFI_R                             \
	__ASM_L(pushq_cfi_r %rax) /* [C] Accumulator register */ \
	ASM_PUSH_GPREGSNSP_NORAX_CFI_R

/* Restore  general  purpose registers  from a  `struct gpregsnsp64' stored
 * at  `0(%rsp)',   as  well   as  increment   `%rsp += SIZEOF_GPREGSNSP64'
 * Additionally, generate CFI  instrumentation to  indicate that  registers
 * loaded with stack-values have re-gained their original values and should
 * not be modified during unwinding (s.a. `.cfi_restore') */
#define ASM_POP_GPREGSNSP_CFI_R   \
	ASM_POP_GPREGSNSP_NORAX_CFI_R \
	__ASM_L(popq_cfi_r %rax) /* [C] Accumulator register */

/* @param: clobber_gpreg: 64-bit gp-register which may be clobbered. */
#define ASM_PUSH_SGREGS_CFI_R(clobber_gpreg)    \
	__ASM_L(pushq_cfi_seg_r %ds, clobber_gpreg) \
	__ASM_L(pushq_cfi_seg_r %es, clobber_gpreg) \
	__ASM_L(pushq_cfi_r %fs)                    \
	__ASM_L(pushq_cfi_r %gs)

/* @param: clobber_gpreg: 64-bit gp-register which may be clobbered.
 * WARNING: THIS MACRO WILL CLOBBER %fs.base and %gs.base!!! */
#define ASM_POP_SGREGS_CFI_R(clobber_gpreg)    \
	__ASM_L(popq_cfi_r %gs)                    \
	__ASM_L(popq_cfi_r %fs)                    \
	__ASM_L(popq_cfi_seg_r %es, clobber_gpreg) \
	__ASM_L(popq_cfi_seg_r %ds, clobber_gpreg)

#ifdef __KERNEL__
/* CLOBBER: %rax, %rcx, %rdx and %rflags */
#define ASM_PUSH_SGBASE_CFI_R               \
	__ASM_L(pushq_cfi_seg_r %fs.base, %rax) \
	__ASM_L(pushq_cfi_kgsbase)
/* CLOBBER: %rax, %rcx, %rdx and %rflags */
#define ASM_POP_SGBASE_CFI_R  \
	__ASM_L(popq_cfi_kgsbase) \
	__ASM_L(popq_cfi_seg_r %fs.base, %rax)
#else /* __KERNEL__ */
/* CLOBBER: %rax */
#define ASM_PUSH_SGBASE_CFI_R               \
	__ASM_L(pushq_cfi_seg_r %fs.base, %rax) \
	__ASM_L(pushq_cfi_seg_r %gs.base, %rax)
/* CLOBBER: %rax */
#define ASM_POP_SGBASE_CFI_R               \
	__ASM_L(popq_cfi_seg_r %gs.base, %rax) \
	__ASM_L(popq_cfi_seg_r %fs.base, %rax)
#endif /* !__KERNEL__ */

/* Push everything necessary to create an `icpustate'
 * from  an  `irregs'   structure  onto  the   stack. */
#define ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R \
	ASM_PUSH_GPREGSNSP_CFI_R

/* Do the reverse of `ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R' */
#define ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R \
	ASM_POP_GPREGSNSP_CFI_R

/* Same as  `ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R',  but  must
 * be used on i386 if the IRET tail was generated by the CPU.
 *
 * A special macro is needed for this case, due to the fact
 * that in case of a  vm86 IRET tail, unwinding of  segment
 * registers has to be altered. */
#define ASM_PUSH_ICPUSTATE_AFTER_HW_IRET_CFI_R \
	ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R

/* Do the reverse of `ASM_PUSH_ICPUSTATE_AFTER_HW_IRET_CFI_R' */
#define ASM_POP_ICPUSTATE_BEFORE_HW_IRET_CFI_R \
	ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R

/* Push everything necessary to create an `scpustate'
 * from  an  `irregs'   structure  onto  the   stack.
 * CLOBBER: %rax, %rcx, %rdx and %rflags */
#define ASM_PUSH_SCPUSTATE_AFTER_IRET_CFI_R \
	ASM_PUSH_GPREGSNSP_CFI_R                \
	ASM_PUSH_SGBASE_CFI_R                   \
	ASM_PUSH_SGREGS_CFI_R(%rax)

/* Do the reverse of `ASM_PUSH_SCPUSTATE_AFTER_IRET_CFI_R' */
#define ASM_POP_SCPUSTATE_BEFORE_IRET_CFI_R \
	ASM_POP_SGREGS_CFI_R(%rax)              \
	ASM_POP_SGBASE_CFI_R                    \
	ASM_POP_GPREGSNSP_CFI_R

/* Push everything necessary to create an `scpustate'
 * from an  `icpustate'  structure  onto  the  stack.
 * CLOBBER: %rax, %rcx, %rdx and %rflags */
#define ASM_PUSH_SCPUSTATE_AFTER_ICPUSTATE_CFI_R \
	ASM_PUSH_SGBASE_CFI_R                        \
	ASM_PUSH_SGREGS_CFI_R(%rax)

/* Push  everything necessary to create an `scpustate'
 * from an hardware-`irregs' structure onto the stack. */
#define ASM_PUSH_SCPUSTATE_AFTER_HW_IRET_CFI_R \
	ASM_PUSH_SCPUSTATE_AFTER_IRET_CFI_R

/* Do the reverse of `ASM_PUSH_SCPUSTATE_AFTER_HW_IRET_CFI_R' */
#define ASM_POP_SCPUSTATE_BEFORE_HW_IRET_CFI_R \
	ASM_POP_SCPUSTATE_BEFORE_IRET_CFI_R


/* Push everything necessary to create an `kcpustate'.
 * This macro assumes that before being used, `%rip' already exists in `0(%rsp)'.
 * @param: clobber_gpreg: 64-bit  gp-register  which  may  be  clobbered.
 *                        Must be one of `%rax', `%rcx', `%rdx' or `%rbx' */
#define ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(clobber_gpreg, sp_addend) \
	__ASM_L(pushfq_cfi_r)                                                \
	__ASM_L(pushq_cfi_r %rax) /* [C] Accumulator register */             \
	__ASM_L(pushq_cfi_r %rcx) /* [C] Count register */                   \
	__ASM_L(pushq_cfi_r %rdx) /* [C] Data register */                    \
	__ASM_L(pushq_cfi_r %rbx) /* [P] Base register */                    \
	__ASM_L(leaq   ((6*8) + (sp_addend))(%rsp), clobber_gpreg)           \
	__ASM_L(pushq_cfi   clobber_gpreg) /* [P] Stack pointer */           \
	__ASM_L(.cfi_rel_offset %rsp, 0)   /* [P] Stack pointer */           \
	__ASM_L(pushq_cfi_r %rbp) /* [P] Frame base pointer */               \
	__ASM_L(pushq_cfi_r %rsi) /* [C] Source pointer */                   \
	__ASM_L(pushq_cfi_r %rdi) /* [C] Destination pointer */              \
	__ASM_L(pushq_cfi_r %r8)  /* [C] General purpose register #8 */      \
	__ASM_L(pushq_cfi_r %r9)  /* [C] General purpose register #9 */      \
	__ASM_L(pushq_cfi_r %r10) /* [C] General purpose register #10 */     \
	__ASM_L(pushq_cfi_r %r11) /* [C] General purpose register #11 */     \
	__ASM_L(pushq_cfi_r %r12) /* [P] General purpose register #12 */     \
	__ASM_L(pushq_cfi_r %r13) /* [P] General purpose register #13 */     \
	__ASM_L(pushq_cfi_r %r14) /* [P] General purpose register #14 */     \
	__ASM_L(pushq_cfi_r %r15) /* [P] General purpose register #15 */
#define ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX(sp_addend) ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(%rax, sp_addend)
#define ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R               ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX(0)
#define ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R_EX            ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX
#define ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R               ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R

#endif /* __x86_64__ */


#endif /* !_I386_KOS_KOS_KERNEL_BITS_CPU_STATE_ASM64_H */
