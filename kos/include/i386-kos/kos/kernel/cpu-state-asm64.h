/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_KOS_KERNEL_CPU_STATE_ASM64_H
#define _I386_KOS_KOS_KERNEL_CPU_STATE_ASM64_H 1

#include <hybrid/host.h>

#include "cpu-state64.h"

#ifdef __x86_64__
#include <hybrid/__asm.h>

#include <asm/cfi.h>
#include <asm/instr/kgsbase.h>

/* Helper macros for restoring registers from cpu-state structures */
#define ASM_CFI_REL_OFFSET_RESTORE_GPREGSNSP(offset)                 \
	__ASM_L(.cfi_rel_offset %rax, ((offset) + OFFSET_GPREGSNSP_RAX)) \
	__ASM_L(.cfi_rel_offset %rcx, ((offset) + OFFSET_GPREGSNSP_RCX)) \
	__ASM_L(.cfi_rel_offset %rdx, ((offset) + OFFSET_GPREGSNSP_RDX)) \
	__ASM_L(.cfi_rel_offset %rbx, ((offset) + OFFSET_GPREGSNSP_RBX)) \
	__ASM_L(.cfi_rel_offset %rbp, ((offset) + OFFSET_GPREGSNSP_RBP)) \
	__ASM_L(.cfi_rel_offset %rsi, ((offset) + OFFSET_GPREGSNSP_RSI)) \
	__ASM_L(.cfi_rel_offset %rdi, ((offset) + OFFSET_GPREGSNSP_RDI)) \
	__ASM_L(.cfi_rel_offset %r8, ((offset) + OFFSET_GPREGSNSP_R8))   \
	__ASM_L(.cfi_rel_offset %r9, ((offset) + OFFSET_GPREGSNSP_R9))   \
	__ASM_L(.cfi_rel_offset %r10, ((offset) + OFFSET_GPREGSNSP_R10)) \
	__ASM_L(.cfi_rel_offset %r11, ((offset) + OFFSET_GPREGSNSP_R11)) \
	__ASM_L(.cfi_rel_offset %r12, ((offset) + OFFSET_GPREGSNSP_R12)) \
	__ASM_L(.cfi_rel_offset %r13, ((offset) + OFFSET_GPREGSNSP_R13)) \
	__ASM_L(.cfi_rel_offset %r14, ((offset) + OFFSET_GPREGSNSP_R14)) \
	__ASM_L(.cfi_rel_offset %r15, ((offset) + OFFSET_GPREGSNSP_R15))

#define ASM_CFI_REG_OFFSET_RESTORE_GPREGSNSP(offset, reg)                 \
	__ASM_L(.cfi_reg_offset %rax, ((offset) + OFFSET_GPREGSNSP_RAX), reg) \
	__ASM_L(.cfi_reg_offset %rcx, ((offset) + OFFSET_GPREGSNSP_RCX), reg) \
	__ASM_L(.cfi_reg_offset %rdx, ((offset) + OFFSET_GPREGSNSP_RDX), reg) \
	__ASM_L(.cfi_reg_offset %rbx, ((offset) + OFFSET_GPREGSNSP_RBX), reg) \
	__ASM_L(.cfi_reg_offset %rbp, ((offset) + OFFSET_GPREGSNSP_RBP), reg) \
	__ASM_L(.cfi_reg_offset %rsi, ((offset) + OFFSET_GPREGSNSP_RSI), reg) \
	__ASM_L(.cfi_reg_offset %rdi, ((offset) + OFFSET_GPREGSNSP_RDI), reg) \
	__ASM_L(.cfi_reg_offset %r8, ((offset) + OFFSET_GPREGSNSP_R8), reg)   \
	__ASM_L(.cfi_reg_offset %r9, ((offset) + OFFSET_GPREGSNSP_R9), reg)   \
	__ASM_L(.cfi_reg_offset %r10, ((offset) + OFFSET_GPREGSNSP_R10), reg) \
	__ASM_L(.cfi_reg_offset %r11, ((offset) + OFFSET_GPREGSNSP_R11), reg) \
	__ASM_L(.cfi_reg_offset %r12, ((offset) + OFFSET_GPREGSNSP_R12), reg) \
	__ASM_L(.cfi_reg_offset %r13, ((offset) + OFFSET_GPREGSNSP_R13), reg) \
	__ASM_L(.cfi_reg_offset %r14, ((offset) + OFFSET_GPREGSNSP_R14), reg) \
	__ASM_L(.cfi_reg_offset %r15, ((offset) + OFFSET_GPREGSNSP_R15), reg)

#define ASM_CFI_REL_OFFSET_RESTORE_SGREGS(offset)               \
	__ASM_L(.cfi_rel_offset %ds, ((offset) + OFFSET_SGREGS_DS)) \
	__ASM_L(.cfi_rel_offset %es, ((offset) + OFFSET_SGREGS_ES)) \
	__ASM_L(.cfi_rel_offset %fs, ((offset) + OFFSET_SGREGS_FS)) \
	__ASM_L(.cfi_rel_offset %gs, ((offset) + OFFSET_SGREGS_GS))

#define ASM_CFI_REG_OFFSET_RESTORE_SGREGS(offset, reg)               \
	__ASM_L(.cfi_reg_offset %ds, ((offset) + OFFSET_SGREGS_DS), reg) \
	__ASM_L(.cfi_reg_offset %es, ((offset) + OFFSET_SGREGS_ES), reg) \
	__ASM_L(.cfi_reg_offset %fs, ((offset) + OFFSET_SGREGS_FS), reg) \
	__ASM_L(.cfi_reg_offset %gs, ((offset) + OFFSET_SGREGS_GS), reg)

#ifdef __KERNEL__
#define ASM_CFI_OFFSET_RESTORE_SGBASE(offset) \
	__ASM_L(.cfi_offset %fs.base, ((offset) + OFFSET_SGBASE_FSBASE))
#define ASM_CFI_REL_OFFSET_RESTORE_SGBASE(offset) \
	__ASM_L(.cfi_rel_offset %fs.base, ((offset) + OFFSET_SGBASE_FSBASE))
#define ASM_CFI_REG_OFFSET_RESTORE_SGBASE(offset) \
	__ASM_L(.cfi_reg_offset %fs.base, ((offset) + OFFSET_SGBASE_FSBASE), reg)
#else /* __KERNEL__ */
#define ASM_CFI_OFFSET_RESTORE_SGBASE(offset)                        \
	__ASM_L(.cfi_offset %fs.base, ((offset) + OFFSET_SGBASE_FSBASE)) \
	__ASM_L(.cfi_offset %gs.base, ((offset) + OFFSET_SGBASE_GSBASE))
#define ASM_CFI_REL_OFFSET_RESTORE_SGBASE(offset)                        \
	__ASM_L(.cfi_rel_offset %fs.base, ((offset) + OFFSET_SGBASE_FSBASE)) \
	__ASM_L(.cfi_rel_offset %gs.base, ((offset) + OFFSET_SGBASE_GSBASE))
#define ASM_CFI_REG_OFFSET_RESTORE_SGBASE(offset, reg)                        \
	__ASM_L(.cfi_reg_offset %fs.base, ((offset) + OFFSET_SGBASE_FSBASE), reg) \
	__ASM_L(.cfi_reg_offset %gs.base, ((offset) + OFFSET_SGBASE_GSBASE), reg)
#endif /* !__KERNEL__ */

#define ASM_CFI_OFFSET_RESTORE_GPREGS(offset)                 \
	__ASM_L(.cfi_offset %rax, ((offset) + OFFSET_GPREGS_RAX)) \
	__ASM_L(.cfi_offset %rcx, ((offset) + OFFSET_GPREGS_RCX)) \
	__ASM_L(.cfi_offset %rdx, ((offset) + OFFSET_GPREGS_RDX)) \
	__ASM_L(.cfi_offset %rbx, ((offset) + OFFSET_GPREGS_RBX)) \
	__ASM_L(.cfi_offset %rsp, ((offset) + OFFSET_GPREGS_RSP)) \
	__ASM_L(.cfi_offset %rbp, ((offset) + OFFSET_GPREGS_RBP)) \
	__ASM_L(.cfi_offset %rsi, ((offset) + OFFSET_GPREGS_RSI)) \
	__ASM_L(.cfi_offset %rdi, ((offset) + OFFSET_GPREGS_RDI)) \
	__ASM_L(.cfi_offset %r8, ((offset) + OFFSET_GPREGS_R8))   \
	__ASM_L(.cfi_offset %r9, ((offset) + OFFSET_GPREGS_R9))   \
	__ASM_L(.cfi_offset %r10, ((offset) + OFFSET_GPREGS_R10)) \
	__ASM_L(.cfi_offset %r11, ((offset) + OFFSET_GPREGS_R11)) \
	__ASM_L(.cfi_offset %r12, ((offset) + OFFSET_GPREGS_R12)) \
	__ASM_L(.cfi_offset %r13, ((offset) + OFFSET_GPREGS_R13)) \
	__ASM_L(.cfi_offset %r14, ((offset) + OFFSET_GPREGS_R14)) \
	__ASM_L(.cfi_offset %r15, ((offset) + OFFSET_GPREGS_R15))

#define ASM_CFI_REL_OFFSET_RESTORE_GPREGS(offset)                 \
	__ASM_L(.cfi_rel_offset %rax, ((offset) + OFFSET_GPREGS_RAX)) \
	__ASM_L(.cfi_rel_offset %rcx, ((offset) + OFFSET_GPREGS_RCX)) \
	__ASM_L(.cfi_rel_offset %rdx, ((offset) + OFFSET_GPREGS_RDX)) \
	__ASM_L(.cfi_rel_offset %rbx, ((offset) + OFFSET_GPREGS_RBX)) \
	__ASM_L(.cfi_rel_offset %rsp, ((offset) + OFFSET_GPREGS_RSP)) \
	__ASM_L(.cfi_rel_offset %rbp, ((offset) + OFFSET_GPREGS_RBP)) \
	__ASM_L(.cfi_rel_offset %rsi, ((offset) + OFFSET_GPREGS_RSI)) \
	__ASM_L(.cfi_rel_offset %rdi, ((offset) + OFFSET_GPREGS_RDI)) \
	__ASM_L(.cfi_rel_offset %r8, ((offset) + OFFSET_GPREGS_R8))   \
	__ASM_L(.cfi_rel_offset %r9, ((offset) + OFFSET_GPREGS_R9))   \
	__ASM_L(.cfi_rel_offset %r10, ((offset) + OFFSET_GPREGS_R10)) \
	__ASM_L(.cfi_rel_offset %r11, ((offset) + OFFSET_GPREGS_R11)) \
	__ASM_L(.cfi_rel_offset %r12, ((offset) + OFFSET_GPREGS_R12)) \
	__ASM_L(.cfi_rel_offset %r13, ((offset) + OFFSET_GPREGS_R13)) \
	__ASM_L(.cfi_rel_offset %r14, ((offset) + OFFSET_GPREGS_R14)) \
	__ASM_L(.cfi_rel_offset %r15, ((offset) + OFFSET_GPREGS_R15))

#define ASM_CFI_REG_OFFSET_RESTORE_GPREGS(offset, reg)                 \
	__ASM_L(.cfi_reg_offset %rax, ((offset) + OFFSET_GPREGS_RAX), reg) \
	__ASM_L(.cfi_reg_offset %rcx, ((offset) + OFFSET_GPREGS_RCX), reg) \
	__ASM_L(.cfi_reg_offset %rdx, ((offset) + OFFSET_GPREGS_RDX), reg) \
	__ASM_L(.cfi_reg_offset %rbx, ((offset) + OFFSET_GPREGS_RBX), reg) \
	__ASM_L(.cfi_reg_offset %rsp, ((offset) + OFFSET_GPREGS_RSP), reg) \
	__ASM_L(.cfi_reg_offset %rbp, ((offset) + OFFSET_GPREGS_RBP), reg) \
	__ASM_L(.cfi_reg_offset %rsi, ((offset) + OFFSET_GPREGS_RSI), reg) \
	__ASM_L(.cfi_reg_offset %rdi, ((offset) + OFFSET_GPREGS_RDI), reg) \
	__ASM_L(.cfi_reg_offset %r8, ((offset) + OFFSET_GPREGS_R8), reg)   \
	__ASM_L(.cfi_reg_offset %r9, ((offset) + OFFSET_GPREGS_R9), reg)   \
	__ASM_L(.cfi_reg_offset %r10, ((offset) + OFFSET_GPREGS_R10), reg) \
	__ASM_L(.cfi_reg_offset %r11, ((offset) + OFFSET_GPREGS_R11), reg) \
	__ASM_L(.cfi_reg_offset %r12, ((offset) + OFFSET_GPREGS_R12), reg) \
	__ASM_L(.cfi_reg_offset %r13, ((offset) + OFFSET_GPREGS_R13), reg) \
	__ASM_L(.cfi_reg_offset %r14, ((offset) + OFFSET_GPREGS_R14), reg) \
	__ASM_L(.cfi_reg_offset %r15, ((offset) + OFFSET_GPREGS_R15), reg)

#define ASM_CFI_REL_OFFSET_RESTORE_IRREGS(offset)                       \
	__ASM_L(.cfi_rel_offset %ss, ((offset) + OFFSET_IRREGS_SS))         \
	__ASM_L(.cfi_rel_offset %rsp, ((offset) + OFFSET_IRREGS_RSP))       \
	__ASM_L(.cfi_rel_offset %rflags, ((offset) + OFFSET_IRREGS_RFLAGS)) \
	__ASM_L(.cfi_rel_offset %cs, ((offset) + OFFSET_IRREGS_CS))         \
	__ASM_L(.cfi_rel_offset %rip, ((offset) + OFFSET_IRREGS_RIP))

#define ASM_CFI_REG_OFFSET_RESTORE_IRREGS(offset, reg)                       \
	__ASM_L(.cfi_reg_offset %ss, ((offset) + OFFSET_IRREGS_SS), reg)         \
	__ASM_L(.cfi_reg_offset %rsp, ((offset) + OFFSET_IRREGS_RSP), reg)       \
	__ASM_L(.cfi_reg_offset %rflags, ((offset) + OFFSET_IRREGS_RFLAGS), reg) \
	__ASM_L(.cfi_reg_offset %cs, ((offset) + OFFSET_IRREGS_CS), reg)         \
	__ASM_L(.cfi_reg_offset %rip, ((offset) + OFFSET_IRREGS_RIP), reg)

#define ASM_CFI_REL_OFFSET_RESTORE_KCPUSTATE(offset)                       \
	__ASM_L(.cfi_rel_offset %rip, ((offset) + OFFSET_KCPUSTATE_RIP))       \
	__ASM_L(.cfi_rel_offset %rflags, ((offset) + OFFSET_KCPUSTATE_RFLAGS)) \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGS((offset) + OFFSET_KCPUSTATE_GPREGS)

#define ASM_CFI_REG_OFFSET_RESTORE_KCPUSTATE(offset, reg)                       \
	__ASM_L(.cfi_reg_offset %rip, ((offset) + OFFSET_KCPUSTATE_RIP), reg)       \
	__ASM_L(.cfi_reg_offset %rflags, ((offset) + OFFSET_KCPUSTATE_RFLAGS), reg) \
	ASM_CFI_REG_OFFSET_RESTORE_GPREGS((offset) + OFFSET_KCPUSTATE_GPREGS, reg)

#define ASM_CFI_REL_OFFSET_RESTORE_SCPUSTATE(offset)                            \
	ASM_CFI_REL_OFFSET_RESTORE_IRREGS((offset) + OFFSET_SCPUSTATE_IRREGS)       \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGSNSP((offset) + OFFSET_SCPUSTATE_GPREGSNSP) \
	ASM_CFI_REL_OFFSET_RESTORE_SGBASE((offset) + OFFSET_SCPUSTATE_SGBASE)       \
	ASM_CFI_REL_OFFSET_RESTORE_SGREGS((offset) + OFFSET_SCPUSTATE_SGREGS)

#define ASM_CFI_REG_OFFSET_RESTORE_SCPUSTATE(offset, reg)                            \
	ASM_CFI_REG_OFFSET_RESTORE_IRREGS((offset) + OFFSET_SCPUSTATE_IRREGS, reg)       \
	ASM_CFI_REG_OFFSET_RESTORE_GPREGSNSP((offset) + OFFSET_SCPUSTATE_GPREGSNSP, reg) \
	ASM_CFI_REG_OFFSET_RESTORE_SGBASE((offset) + OFFSET_SCPUSTATE_SGBASE, reg)       \
	ASM_CFI_REG_OFFSET_RESTORE_SGREGS((offset) + OFFSET_SCPUSTATE_SGREGS, reg)

#define ASM_CFI_REL_OFFSET_RESTORE_ICPUSTATE(offset)                      \
	ASM_CFI_REL_OFFSET_RESTORE_IRREGS((offset) + OFFSET_ICPUSTATE_IRREGS) \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGSNSP((offset) + OFFSET_ICPUSTATE_GPREGSNSP)

#define ASM_CFI_REG_OFFSET_RESTORE_ICPUSTATE(offset, reg)                      \
	ASM_CFI_REG_OFFSET_RESTORE_IRREGS((offset) + OFFSET_ICPUSTATE_IRREGS, reg) \
	ASM_CFI_REG_OFFSET_RESTORE_GPREGSNSP((offset) + OFFSET_ICPUSTATE_GPREGSNSP, reg)

#define ASM_CFI_REL_OFFSET_RESTORE_UCPUSTATE(offset)                      \
	__ASM_L(.cfi_rel_offset %rip, (offset) + OFFSET_UCPUSTATE_RIP)        \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGS((offset) + OFFSET_UCPUSTATE_GPREGS) \
	__ASM_L(.cfi_rel_offset %rflags, (offset) + OFFSET_UCPUSTATE_RFLAGS)  \
	__ASM_L(.cfi_rel_offset %ss, (offset) + OFFSET_UCPUSTATE_SS)          \
	__ASM_L(.cfi_rel_offset %cs, (offset) + OFFSET_UCPUSTATE_CS)          \
	ASM_CFI_REL_OFFSET_RESTORE_SGREGS((offset) + OFFSET_UCPUSTATE_SGREGS) \
	ASM_CFI_REL_OFFSET_RESTORE_SGBASE((offset) + OFFSET_UCPUSTATE_SGBASE)

#define ASM_CFI_REG_OFFSET_RESTORE_UCPUSTATE(offset, reg)                      \
	__ASM_L(.cfi_reg_offset %rip, (offset) + OFFSET_UCPUSTATE_RIP, reg)        \
	ASM_CFI_REG_OFFSET_RESTORE_GPREGS((offset) + OFFSET_UCPUSTATE_GPREGS, reg) \
	__ASM_L(.cfi_reg_offset %rflags, (offset) + OFFSET_UCPUSTATE_RFLAGS, reg)  \
	__ASM_L(.cfi_reg_offset %ss, (offset) + OFFSET_UCPUSTATE_SS, reg)          \
	__ASM_L(.cfi_reg_offset %cs, (offset) + OFFSET_UCPUSTATE_CS, reg)          \
	ASM_CFI_REG_OFFSET_RESTORE_SGREGS((offset) + OFFSET_UCPUSTATE_SGREGS, reg) \
	ASM_CFI_REG_OFFSET_RESTORE_SGBASE((offset) + OFFSET_UCPUSTATE_SGBASE, reg)

#define ASM_CFI_REL_OFFSET_RESTORE_LCPUSTATE(offset)               \
	__ASM_L(.cfi_rel_offset %r15, (offset) + OFFSET_LCPUSTATE_R15) \
	__ASM_L(.cfi_rel_offset %r14, (offset) + OFFSET_LCPUSTATE_R14) \
	__ASM_L(.cfi_rel_offset %r13, (offset) + OFFSET_LCPUSTATE_R13) \
	__ASM_L(.cfi_rel_offset %r12, (offset) + OFFSET_LCPUSTATE_R12) \
	__ASM_L(.cfi_rel_offset %rbp, (offset) + OFFSET_LCPUSTATE_RBP) \
	__ASM_L(.cfi_rel_offset %rsp, (offset) + OFFSET_LCPUSTATE_RSP) \
	__ASM_L(.cfi_rel_offset %rbx, (offset) + OFFSET_LCPUSTATE_RBX) \
	__ASM_L(.cfi_rel_offset %rip, (offset) + OFFSET_LCPUSTATE_RIP)

#define ASM_CFI_REG_OFFSET_RESTORE_LCPUSTATE(offset, reg)               \
	__ASM_L(.cfi_reg_offset %r15, (offset) + OFFSET_LCPUSTATE_R15, reg) \
	__ASM_L(.cfi_reg_offset %r14, (offset) + OFFSET_LCPUSTATE_R14, reg) \
	__ASM_L(.cfi_reg_offset %r13, (offset) + OFFSET_LCPUSTATE_R13, reg) \
	__ASM_L(.cfi_reg_offset %r12, (offset) + OFFSET_LCPUSTATE_R12, reg) \
	__ASM_L(.cfi_reg_offset %rbp, (offset) + OFFSET_LCPUSTATE_RBP, reg) \
	__ASM_L(.cfi_reg_offset %rsp, (offset) + OFFSET_LCPUSTATE_RSP, reg) \
	__ASM_L(.cfi_reg_offset %rbx, (offset) + OFFSET_LCPUSTATE_RBX, reg) \
	__ASM_L(.cfi_reg_offset %rip, (offset) + OFFSET_LCPUSTATE_RIP, reg)

#define ASM_CFI_OFFSET_RESTORE_FCPUSTATE(offset)                      \
	ASM_CFI_OFFSET_RESTORE_GPREGS((offset) + OFFSET_FCPUSTATE_GPREGS) \
	__ASM_L(.cfi_offset %rflags, (offset) + OFFSET_FCPUSTATE_RFLAGS)  \
	__ASM_L(.cfi_offset %rip, (offset) + OFFSET_FCPUSTATE_RIP)        \
	__ASM_L(.cfi_offset %es, (offset) + OFFSET_FCPUSTATE_ES)          \
	__ASM_L(.cfi_offset %cs, (offset) + OFFSET_FCPUSTATE_CS)          \
	__ASM_L(.cfi_offset %ss, (offset) + OFFSET_FCPUSTATE_SS)          \
	__ASM_L(.cfi_offset %ds, (offset) + OFFSET_FCPUSTATE_DS)          \
	__ASM_L(.cfi_offset %fs, (offset) + OFFSET_FCPUSTATE_FS)          \
	__ASM_L(.cfi_offset %gs, (offset) + OFFSET_FCPUSTATE_GS)          \
	__ASM_L(.cfi_offset %tr, (offset) + OFFSET_FCPUSTATE_TR)          \
	__ASM_L(.cfi_offset %ldtr, (offset) + OFFSET_FCPUSTATE_LDT)       \
	ASM_CFI_OFFSET_RESTORE_SGBASE((offset) + OFFSET_FCPUSTATE_SGBASE)

#define ASM_CFI_REL_OFFSET_RESTORE_FCPUSTATE(offset)                      \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGS((offset) + OFFSET_FCPUSTATE_GPREGS) \
	__ASM_L(.cfi_rel_offset %rflags, (offset) + OFFSET_FCPUSTATE_RFLAGS)  \
	__ASM_L(.cfi_rel_offset %rip, (offset) + OFFSET_FCPUSTATE_RIP)        \
	__ASM_L(.cfi_rel_offset %es, (offset) + OFFSET_FCPUSTATE_ES)          \
	__ASM_L(.cfi_rel_offset %cs, (offset) + OFFSET_FCPUSTATE_CS)          \
	__ASM_L(.cfi_rel_offset %ss, (offset) + OFFSET_FCPUSTATE_SS)          \
	__ASM_L(.cfi_rel_offset %ds, (offset) + OFFSET_FCPUSTATE_DS)          \
	__ASM_L(.cfi_rel_offset %fs, (offset) + OFFSET_FCPUSTATE_FS)          \
	__ASM_L(.cfi_rel_offset %gs, (offset) + OFFSET_FCPUSTATE_GS)          \
	__ASM_L(.cfi_rel_offset %tr, (offset) + OFFSET_FCPUSTATE_TR)          \
	__ASM_L(.cfi_rel_offset %ldtr, (offset) + OFFSET_FCPUSTATE_LDT)       \
	ASM_CFI_REL_OFFSET_RESTORE_SGBASE((offset) + OFFSET_FCPUSTATE_SGBASE)

#define ASM_CFI_REG_OFFSET_RESTORE_FCPUSTATE(offset, reg)                      \
	ASM_CFI_REG_OFFSET_RESTORE_GPREGS((offset) + OFFSET_FCPUSTATE_GPREGS, reg) \
	__ASM_L(.cfi_reg_offset %rflags, (offset) + OFFSET_FCPUSTATE_RFLAGS, reg)  \
	__ASM_L(.cfi_reg_offset %rip, (offset) + OFFSET_FCPUSTATE_RIP, reg)        \
	__ASM_L(.cfi_reg_offset %es, (offset) + OFFSET_FCPUSTATE_ES, reg)          \
	__ASM_L(.cfi_reg_offset %cs, (offset) + OFFSET_FCPUSTATE_CS, reg)          \
	__ASM_L(.cfi_reg_offset %ss, (offset) + OFFSET_FCPUSTATE_SS, reg)          \
	__ASM_L(.cfi_reg_offset %ds, (offset) + OFFSET_FCPUSTATE_DS, reg)          \
	__ASM_L(.cfi_reg_offset %fs, (offset) + OFFSET_FCPUSTATE_FS, reg)          \
	__ASM_L(.cfi_reg_offset %gs, (offset) + OFFSET_FCPUSTATE_GS, reg)          \
	__ASM_L(.cfi_reg_offset %tr, (offset) + OFFSET_FCPUSTATE_TR, reg)          \
	__ASM_L(.cfi_reg_offset %ldtr, (offset) + OFFSET_FCPUSTATE_LDT, reg)       \
	ASM_CFI_REG_OFFSET_RESTORE_SGBASE((offset) + OFFSET_FCPUSTATE_SGBASE, reg)


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

/* Push all current general-purpose registers to form a a `struct gpregsnsp64'
 * that will be stored at `0(%rsp)' upon return. Additionally, generate cfi
 * instrumentation to allow all pushed registered to be restored during unwinding. */
#define ASM_PUSH_GPREGSNSP_CFI_R                             \
	__ASM_L(pushq_cfi_r %rax) /* [C] Accumulator register */ \
	ASM_PUSH_GPREGSNSP_NORAX_CFI_R

/* Restore general purpose registers from a `struct gpregsnsp64' stored
 * at `0(%rsp)', as well as increment `%rsp += SIZEOF_GPREGSNSP64'
 * Additionally, generate CFI instrumentation to indicate that registers
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
 * from an `irregs' structure onto the stack. */
#define ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R  \
	ASM_PUSH_GPREGSNSP_CFI_R

/* Do the reverse of `ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R' */
#define ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R  \
	ASM_POP_GPREGSNSP_CFI_R

/* Same as `ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R', but must
 * be used on i386 if the IRET tail was generated by the CPU.
 *
 * A special macro is needed for this case, due to the fact
 * that in case of a vm86 IRET tail, unwinding of segment
 * registers has to be altered. */
#define ASM_PUSH_ICPUSTATE_AFTER_HW_IRET_CFI_R \
	ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R

/* Do the reverse of `ASM_PUSH_ICPUSTATE_AFTER_HM_IRET_CFI_R' */
#define ASM_POP_ICPUSTATE_BEFORE_HM_IRET_CFI_R \
	ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R

/* Push everything necessary to create an `scpustate'
 * from an `irregs' structure onto the stack.
 * CLOBBER: %rax, %rcx, %rdx and %rflags */
#define ASM_PUSH_SCPUSTATE_AFTER_IRET_CFI_R \
	ASM_PUSH_GPREGSNSP_CFI_R                \
	ASM_PUSH_SGBASE_CFI_R                   \
	ASM_PUSH_SGREGS_CFI_R(%rax)

/* Push everything necessary to create an `scpustate'
 * from an `icpustate' structure onto the stack.
 * CLOBBER: %rax, %rcx, %rdx and %rflags */
#define ASM_PUSH_SCPUSTATE_AFTER_ICPUSTATE_CFI_R \
	ASM_PUSH_SGBASE_CFI_R                        \
	ASM_PUSH_SGREGS_CFI_R(%rax)

/* Push everything necessary to create an `kcpustate'.
 * This macro assumes that before being used, `%rip' already exists in `0(%rsp)'.
 * @param: clobber_gpreg: 64-bit gp-register which may be clobbered.
 *                        Must be one of `%rax', `%rcx', `%rdx' or `%rbx' */
#define ASM_PUSH_KCPUSTATE_AFTER_RIP_EX(clobber_gpreg, sp_addend)    \
	__ASM_L(pushfq_cfi_r)                                            \
	__ASM_L(pushq_cfi_r %rax) /* [C] Accumulator register */         \
	__ASM_L(pushq_cfi_r %rcx) /* [C] Count register */               \
	__ASM_L(pushq_cfi_r %rdx) /* [C] Data register */                \
	__ASM_L(pushq_cfi_r %rbx) /* [P] Base register */                \
	__ASM_L(leaq   ((6*8) + (sp_addend))(%rsp), clobber_gpreg)       \
	__ASM_L(pushq_cfi   clobber_gpreg) /* [P] Stack pointer */       \
	__ASM_L(.cfi_rel_offset %rsp, 0)   /* [P] Stack pointer */       \
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
#define ASM_PUSH_KCPUSTATE_AFTER_RIP \
	ASM_PUSH_KCPUSTATE_AFTER_RIP_EX(%rax, 0)

#endif /* __x86_64__ */


#endif /* !_I386_KOS_KOS_KERNEL_CPU_STATE_ASM64_H */
