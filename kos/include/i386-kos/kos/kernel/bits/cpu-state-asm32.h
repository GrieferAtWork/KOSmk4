/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_KOS_KERNEL_BITS_CPU_STATE_ASM32_H
#define _I386_KOS_KOS_KERNEL_BITS_CPU_STATE_ASM32_H 1

#include <hybrid/host.h>

#include "cpu-state32.h"

#if defined(__i386__) && !defined(__x86_64__)
#include <hybrid/__asm.h>

#include <cfi.h>

/* RESTORE: ...\%esp = *(struct gpregs32 const *)(CFA + offset) */
#define ASM_CFI_OFFSET_RESTORE_GPREGSNSP(offset)                \
	__ASM_L(.cfi_offset %edi, ((offset) + OFFSET_GPREGS32_EDI)) \
	__ASM_L(.cfi_offset %esi, ((offset) + OFFSET_GPREGS32_ESI)) \
	__ASM_L(.cfi_offset %ebp, ((offset) + OFFSET_GPREGS32_EBP)) \
	__ASM_L(.cfi_offset %ebx, ((offset) + OFFSET_GPREGS32_EBX)) \
	__ASM_L(.cfi_offset %edx, ((offset) + OFFSET_GPREGS32_EDX)) \
	__ASM_L(.cfi_offset %ecx, ((offset) + OFFSET_GPREGS32_ECX)) \
	__ASM_L(.cfi_offset %eax, ((offset) + OFFSET_GPREGS32_EAX))

/* RESTORE: ...\%esp = *(struct gpregs32 const *)(CFA + CFA_OFFSET + offset) */
#define ASM_CFI_REL_OFFSET_RESTORE_GPREGSNSP(offset)                \
	__ASM_L(.cfi_rel_offset %edi, ((offset) + OFFSET_GPREGS32_EDI)) \
	__ASM_L(.cfi_rel_offset %esi, ((offset) + OFFSET_GPREGS32_ESI)) \
	__ASM_L(.cfi_rel_offset %ebp, ((offset) + OFFSET_GPREGS32_EBP)) \
	__ASM_L(.cfi_rel_offset %ebx, ((offset) + OFFSET_GPREGS32_EBX)) \
	__ASM_L(.cfi_rel_offset %edx, ((offset) + OFFSET_GPREGS32_EDX)) \
	__ASM_L(.cfi_rel_offset %ecx, ((offset) + OFFSET_GPREGS32_ECX)) \
	__ASM_L(.cfi_rel_offset %eax, ((offset) + OFFSET_GPREGS32_EAX))

/* RESTORE: ...\%esp = *(struct gpregs32 const *)(%reg + offset) */
#define ASM_CFI_REG_OFFSET_RESTORE_GPREGSNSP(offset, reg)                \
	__ASM_L(.cfi_reg_offset %edi, ((offset) + OFFSET_GPREGS32_EDI), reg) \
	__ASM_L(.cfi_reg_offset %esi, ((offset) + OFFSET_GPREGS32_ESI), reg) \
	__ASM_L(.cfi_reg_offset %ebp, ((offset) + OFFSET_GPREGS32_EBP), reg) \
	__ASM_L(.cfi_reg_offset %ebx, ((offset) + OFFSET_GPREGS32_EBX), reg) \
	__ASM_L(.cfi_reg_offset %edx, ((offset) + OFFSET_GPREGS32_EDX), reg) \
	__ASM_L(.cfi_reg_offset %ecx, ((offset) + OFFSET_GPREGS32_ECX), reg) \
	__ASM_L(.cfi_reg_offset %eax, ((offset) + OFFSET_GPREGS32_EAX), reg)



/* RESTORE: ... = *(struct gpregs32 const *)(CFA + offset) */
#define ASM_CFI_OFFSET_RESTORE_GPREGS(offset) \
	ASM_CFI_OFFSET_RESTORE_GPREGSNSP(offset)  \
	__ASM_L(.cfi_offset %esp, ((offset) + OFFSET_GPREGS32_ESP))

/* RESTORE: ... = *(struct gpregs32 const *)(CFA + CFA_OFFSET + offset) */
#define ASM_CFI_REL_OFFSET_RESTORE_GPREGS(offset) \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGSNSP(offset)  \
	__ASM_L(.cfi_rel_offset %esp, ((offset) + OFFSET_GPREGS32_ESP))

/* RESTORE: ... = *(struct gpregs32 const *)(%reg + offset) */
#define ASM_CFI_REG_OFFSET_RESTORE_GPREGS(offset, reg) \
	ASM_CFI_REG_OFFSET_RESTORE_GPREGSNSP(offset, reg)  \
	__ASM_L(.cfi_reg_offset %esp, ((offset) + OFFSET_GPREGS32_ESP), reg)



/* RESTORE: ... = *(struct sgregs32 const *)(CFA + offset) */
#define ASM_CFI_OFFSET_RESTORE_SGREGS(offset)                 \
	__ASM_L(.cfi_offset %gs, ((offset) + OFFSET_SGREGS32_GS)) \
	__ASM_L(.cfi_offset %fs, ((offset) + OFFSET_SGREGS32_FS)) \
	__ASM_L(.cfi_offset %es, ((offset) + OFFSET_SGREGS32_ES)) \
	__ASM_L(.cfi_offset %ds, ((offset) + OFFSET_SGREGS32_DS))

/* RESTORE: ... = *(struct sgregs32 const *)(CFA + CFA_OFFSET + offset) */
#define ASM_CFI_REL_OFFSET_RESTORE_SGREGS(offset)                 \
	__ASM_L(.cfi_rel_offset %gs, ((offset) + OFFSET_SGREGS32_GS)) \
	__ASM_L(.cfi_rel_offset %fs, ((offset) + OFFSET_SGREGS32_FS)) \
	__ASM_L(.cfi_rel_offset %es, ((offset) + OFFSET_SGREGS32_ES)) \
	__ASM_L(.cfi_rel_offset %ds, ((offset) + OFFSET_SGREGS32_DS))

/* RESTORE: ... = *(struct sgregs32 const *)(%reg + offset) */
#define ASM_CFI_REG_OFFSET_RESTORE_SGREGS(offset, reg)                 \
	__ASM_L(.cfi_reg_offset %gs, ((offset) + OFFSET_SGREGS32_GS), reg) \
	__ASM_L(.cfi_reg_offset %fs, ((offset) + OFFSET_SGREGS32_FS), reg) \
	__ASM_L(.cfi_reg_offset %es, ((offset) + OFFSET_SGREGS32_ES), reg) \
	__ASM_L(.cfi_reg_offset %ds, ((offset) + OFFSET_SGREGS32_DS), reg)



/* RESTORE: ...\{IRET} = *(struct icpustate32 const *)(CFA + offset) */
#define ASM_CFI_OFFSET_RESTORE_ICPUSTATE_NOIRET(offset)                    \
	ASM_CFI_OFFSET_RESTORE_GPREGSNSP((offset) + OFFSET_ICPUSTATE32_GPREGS) \
	__ASM_L(.cfi_offset %fs, ((offset) + OFFSET_ICPUSTATE32_FS))           \
	__ASM_L(.cfi_offset %es, ((offset) + OFFSET_ICPUSTATE32_ES))           \
	__ASM_L(.cfi_offset %ds, ((offset) + OFFSET_ICPUSTATE32_DS))

/* RESTORE: ...\{IRET} = *(struct icpustate32 const *)(CFA + CFA_OFFSET + offset) */
#define ASM_CFI_REL_OFFSET_RESTORE_ICPUSTATE_NOIRET(offset)                    \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGSNSP((offset) + OFFSET_ICPUSTATE32_GPREGS) \
	__ASM_L(.cfi_rel_offset %fs, ((offset) + OFFSET_ICPUSTATE32_FS))           \
	__ASM_L(.cfi_rel_offset %es, ((offset) + OFFSET_ICPUSTATE32_ES))           \
	__ASM_L(.cfi_rel_offset %ds, ((offset) + OFFSET_ICPUSTATE32_DS))

/* RESTORE: ...\{IRET} = *(struct icpustate32 const *)(%reg + offset) */
#define ASM_CFI_REG_OFFSET_RESTORE_ICPUSTATE_NOIRET(offset, reg)                    \
	ASM_CFI_REG_OFFSET_RESTORE_GPREGSNSP((offset) + OFFSET_ICPUSTATE32_GPREGS, reg) \
	__ASM_L(.cfi_reg_offset %fs, ((offset) + OFFSET_ICPUSTATE32_FS), reg)           \
	__ASM_L(.cfi_reg_offset %es, ((offset) + OFFSET_ICPUSTATE32_ES), reg)           \
	__ASM_L(.cfi_reg_offset %ds, ((offset) + OFFSET_ICPUSTATE32_DS), reg)



/* RESTORE: ... = *(struct icpustate32 const *)(CFA + offset) */
#define ASM_CFI_OFFSET_RESTORE_ICPUSTATE(offset)                                                                       \
	ASM_CFI_OFFSET_RESTORE_GPREGSNSP((offset) + OFFSET_ICPUSTATE32_GPREGS)                                             \
	__ASM_L(.cfi_restore_iret_eip ((offset) + OFFSET_ICPUSTATE32_IRREGS))                                              \
	__ASM_L(.cfi_restore_iret_cs ((offset) + OFFSET_ICPUSTATE32_IRREGS))                                               \
	__ASM_L(.cfi_restore_iret_eflags ((offset) + OFFSET_ICPUSTATE32_IRREGS))                                           \
	__ASM_L(.cfi_restore_iret_esp ((offset) + OFFSET_ICPUSTATE32_IRREGS))                                              \
	__ASM_L(.cfi_restore_iret_ss ((offset) + OFFSET_ICPUSTATE32_IRREGS))                                               \
	__ASM_L(.cfi_restore_iret_es_or_offset ((offset) + OFFSET_ICPUSTATE32_ES), ((offset) + OFFSET_ICPUSTATE32_IRREGS)) \
	__ASM_L(.cfi_restore_iret_ds_or_offset ((offset) + OFFSET_ICPUSTATE32_DS), ((offset) + OFFSET_ICPUSTATE32_IRREGS)) \
	__ASM_L(.cfi_restore_iret_fs_or_offset ((offset) + OFFSET_ICPUSTATE32_FS), ((offset) + OFFSET_ICPUSTATE32_IRREGS)) \
	__ASM_L(.cfi_restore_iret_gs ((offset) + OFFSET_ICPUSTATE32_IRREGS))



/* RESTORE: ...\{IRET} = *(struct scpustate32 const *)(CFA + offset) */
#define ASM_CFI_OFFSET_RESTORE_SCPUSTATE_NOIRET(offset)                    \
	ASM_CFI_OFFSET_RESTORE_GPREGSNSP((offset) + OFFSET_SCPUSTATE32_GPREGS) \
	ASM_CFI_OFFSET_RESTORE_SGREGS((offset) + OFFSET_SCPUSTATE32_SGREGS)

/* RESTORE: ...\{IRET} = *(struct scpustate32 const *)(CFA + CFA_OFFSET + offset) */
#define ASM_CFI_REL_OFFSET_RESTORE_SCPUSTATE_NOIRET(offset)                    \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGSNSP((offset) + OFFSET_SCPUSTATE32_GPREGS) \
	ASM_CFI_REL_OFFSET_RESTORE_SGREGS((offset) + OFFSET_SCPUSTATE32_SGREGS)

/* RESTORE: ...\{IRET} = *(struct scpustate32 const *)(%reg + offset) */
#define ASM_CFI_REG_OFFSET_RESTORE_SCPUSTATE_NOIRET(offset, reg)                    \
	ASM_CFI_REG_OFFSET_RESTORE_GPREGSNSP((offset) + OFFSET_SCPUSTATE32_GPREGS, reg) \
	ASM_CFI_REG_OFFSET_RESTORE_SGREGS((offset) + OFFSET_SCPUSTATE32_SGREGS, reg)



/* RESTORE: ... = *(struct scpustate32 const *)(CFA + offset) */
#define ASM_CFI_OFFSET_RESTORE_SCPUSTATE(offset)                                                                                                \
	ASM_CFI_OFFSET_RESTORE_GPREGSNSP((offset) + OFFSET_SCPUSTATE32_GPREGS)                                                                      \
	__ASM_L(.cfi_restore_iret_eip ((offset) + OFFSET_SCPUSTATE32_IRREGS))                                                                       \
	__ASM_L(.cfi_restore_iret_cs ((offset) + OFFSET_SCPUSTATE32_IRREGS))                                                                        \
	__ASM_L(.cfi_restore_iret_eflags ((offset) + OFFSET_SCPUSTATE32_IRREGS))                                                                    \
	__ASM_L(.cfi_restore_iret_esp ((offset) + OFFSET_SCPUSTATE32_IRREGS))                                                                       \
	__ASM_L(.cfi_restore_iret_ss ((offset) + OFFSET_SCPUSTATE32_IRREGS))                                                                        \
	__ASM_L(.cfi_restore_iret_es_or_offset ((offset) + OFFSET_SCPUSTATE32_SGREGS + OFFSET_SGREGS32_ES), ((offset) + OFFSET_SCPUSTATE32_IRREGS)) \
	__ASM_L(.cfi_restore_iret_ds_or_offset ((offset) + OFFSET_SCPUSTATE32_SGREGS + OFFSET_SGREGS32_DS), ((offset) + OFFSET_SCPUSTATE32_IRREGS)) \
	__ASM_L(.cfi_restore_iret_fs_or_offset ((offset) + OFFSET_SCPUSTATE32_SGREGS + OFFSET_SGREGS32_FS), ((offset) + OFFSET_SCPUSTATE32_IRREGS)) \
	__ASM_L(.cfi_restore_iret_gs_or_offset ((offset) + OFFSET_SCPUSTATE32_SGREGS + OFFSET_SGREGS32_GS), ((offset) + OFFSET_SCPUSTATE32_IRREGS))



/* RESTORE: ... = *(struct ucpustate32 const *)(CFA + offset) */
#define ASM_CFI_OFFSET_RESTORE_UCPUSTATE(offset)                         \
	ASM_CFI_OFFSET_RESTORE_GPREGS((offset) + OFFSET_UCPUSTATE32_GPREGS)  \
	ASM_CFI_OFFSET_RESTORE_SGREGS((offset) + OFFSET_UCPUSTATE32_SGREGS)  \
	__ASM_L(.cfi_offset %cs, ((offset) + OFFSET_UCPUSTATE32_CS))         \
	__ASM_L(.cfi_offset %ss, ((offset) + OFFSET_UCPUSTATE32_SS))         \
	__ASM_L(.cfi_offset %eflags, ((offset) + OFFSET_UCPUSTATE32_EFLAGS)) \
	__ASM_L(.cfi_offset %eip, ((offset) + OFFSET_UCPUSTATE32_EIP))

/* RESTORE: ... = *(struct ucpustate32 const *)(CFA + CFA_OFFSET + offset) */
#define ASM_CFI_REL_OFFSET_RESTORE_UCPUSTATE(offset)                         \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGS((offset) + OFFSET_UCPUSTATE32_GPREGS)  \
	ASM_CFI_REL_OFFSET_RESTORE_SGREGS((offset) + OFFSET_UCPUSTATE32_SGREGS)  \
	__ASM_L(.cfi_rel_offset %cs, ((offset) + OFFSET_UCPUSTATE32_CS))         \
	__ASM_L(.cfi_rel_offset %ss, ((offset) + OFFSET_UCPUSTATE32_SS))         \
	__ASM_L(.cfi_rel_offset %eflags, ((offset) + OFFSET_UCPUSTATE32_EFLAGS)) \
	__ASM_L(.cfi_rel_offset %eip, ((offset) + OFFSET_UCPUSTATE32_EIP))

/* RESTORE: ... = *(struct ucpustate32 const *)(%reg + offset) */
#define ASM_CFI_REG_OFFSET_RESTORE_UCPUSTATE(offset, reg)                         \
	ASM_CFI_REG_OFFSET_RESTORE_GPREGS((offset) + OFFSET_UCPUSTATE32_GPREGS, reg)  \
	ASM_CFI_REG_OFFSET_RESTORE_SGREGS((offset) + OFFSET_UCPUSTATE32_SGREGS, reg)  \
	__ASM_L(.cfi_reg_offset %cs, ((offset) + OFFSET_UCPUSTATE32_CS), reg)         \
	__ASM_L(.cfi_reg_offset %ss, ((offset) + OFFSET_UCPUSTATE32_SS), reg)         \
	__ASM_L(.cfi_reg_offset %eflags, ((offset) + OFFSET_UCPUSTATE32_EFLAGS), reg) \
	__ASM_L(.cfi_reg_offset %eip, ((offset) + OFFSET_UCPUSTATE32_EIP), reg)




/* RESTORE: ... = *(struct fcpustate32 const *)(CFA + offset) */
#define ASM_CFI_OFFSET_RESTORE_FCPUSTATE(offset)                         \
	ASM_CFI_OFFSET_RESTORE_GPREGS((offset) + OFFSET_FCPUSTATE32_GPREGS)  \
	__ASM_L(.cfi_offset %eflags, ((offset) + OFFSET_FCPUSTATE32_EFLAGS)) \
	__ASM_L(.cfi_offset %eip, ((offset) + OFFSET_FCPUSTATE32_EIP))       \
	__ASM_L(.cfi_offset %es, ((offset) + OFFSET_FCPUSTATE32_ES))         \
	__ASM_L(.cfi_offset %cs, ((offset) + OFFSET_FCPUSTATE32_CS))         \
	__ASM_L(.cfi_offset %ss, ((offset) + OFFSET_FCPUSTATE32_SS))         \
	__ASM_L(.cfi_offset %ds, ((offset) + OFFSET_FCPUSTATE32_DS))         \
	__ASM_L(.cfi_offset %fs, ((offset) + OFFSET_FCPUSTATE32_FS))         \
	__ASM_L(.cfi_offset %gs, ((offset) + OFFSET_FCPUSTATE32_GS))         \
	__ASM_L(.cfi_offset %tr, ((offset) + OFFSET_FCPUSTATE32_TR))         \
	__ASM_L(.cfi_offset %ldtr, ((offset) + OFFSET_FCPUSTATE32_LDT))

/* RESTORE: ... = *(struct fcpustate32 const *)(CFA + CFA_OFFSET + offset) */
#define ASM_CFI_REL_OFFSET_RESTORE_FCPUSTATE(offset)                         \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGS((offset) + OFFSET_FCPUSTATE32_GPREGS)  \
	__ASM_L(.cfi_rel_offset %eflags, ((offset) + OFFSET_FCPUSTATE32_EFLAGS)) \
	__ASM_L(.cfi_rel_offset %eip, ((offset) + OFFSET_FCPUSTATE32_EIP))       \
	__ASM_L(.cfi_rel_offset %es, ((offset) + OFFSET_FCPUSTATE32_ES))         \
	__ASM_L(.cfi_rel_offset %cs, ((offset) + OFFSET_FCPUSTATE32_CS))         \
	__ASM_L(.cfi_rel_offset %ss, ((offset) + OFFSET_FCPUSTATE32_SS))         \
	__ASM_L(.cfi_rel_offset %ds, ((offset) + OFFSET_FCPUSTATE32_DS))         \
	__ASM_L(.cfi_rel_offset %fs, ((offset) + OFFSET_FCPUSTATE32_FS))         \
	__ASM_L(.cfi_rel_offset %gs, ((offset) + OFFSET_FCPUSTATE32_GS))         \
	__ASM_L(.cfi_rel_offset %tr, ((offset) + OFFSET_FCPUSTATE32_TR))         \
	__ASM_L(.cfi_rel_offset %ldtr, ((offset) + OFFSET_FCPUSTATE32_LDT))

/* RESTORE: ... = *(struct fcpustate32 const *)(%reg + offset) */
#define ASM_CFI_REG_OFFSET_RESTORE_FCPUSTATE(offset, reg)                         \
	ASM_CFI_REG_OFFSET_RESTORE_GPREGS((offset) + OFFSET_FCPUSTATE32_GPREGS, reg)  \
	__ASM_L(.cfi_reg_offset %eflags, ((offset) + OFFSET_FCPUSTATE32_EFLAGS), reg) \
	__ASM_L(.cfi_reg_offset %eip, ((offset) + OFFSET_FCPUSTATE32_EIP), reg)       \
	__ASM_L(.cfi_reg_offset %es, ((offset) + OFFSET_FCPUSTATE32_ES), reg)         \
	__ASM_L(.cfi_reg_offset %cs, ((offset) + OFFSET_FCPUSTATE32_CS), reg)         \
	__ASM_L(.cfi_reg_offset %ss, ((offset) + OFFSET_FCPUSTATE32_SS), reg)         \
	__ASM_L(.cfi_reg_offset %ds, ((offset) + OFFSET_FCPUSTATE32_DS), reg)         \
	__ASM_L(.cfi_reg_offset %fs, ((offset) + OFFSET_FCPUSTATE32_FS), reg)         \
	__ASM_L(.cfi_reg_offset %gs, ((offset) + OFFSET_FCPUSTATE32_GS), reg)         \
	__ASM_L(.cfi_reg_offset %tr, ((offset) + OFFSET_FCPUSTATE32_TR), reg)         \
	__ASM_L(.cfi_reg_offset %ldtr, ((offset) + OFFSET_FCPUSTATE32_LDT), reg)



/* RESTORE: ... = *(struct kcpustate32 const *)(CFA + offset) */
#define ASM_CFI_OFFSET_RESTORE_KCPUSTATE(offset)                         \
	ASM_CFI_OFFSET_RESTORE_GPREGS((offset) + OFFSET_KCPUSTATE32_GPREGS)  \
	__ASM_L(.cfi_offset %eflags, ((offset) + OFFSET_KCPUSTATE32_EFLAGS)) \
	__ASM_L(.cfi_offset %eip, ((offset) + OFFSET_KCPUSTATE32_EIP))

/* RESTORE: ... = *(struct kcpustate32 const *)(CFA + CFA_OFFSET + offset) */
#define ASM_CFI_REL_OFFSET_RESTORE_KCPUSTATE(offset)                         \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGS((offset) + OFFSET_KCPUSTATE32_GPREGS)  \
	__ASM_L(.cfi_rel_offset %eflags, ((offset) + OFFSET_KCPUSTATE32_EFLAGS)) \
	__ASM_L(.cfi_rel_offset %eip, ((offset) + OFFSET_KCPUSTATE32_EIP))

/* RESTORE: ... = *(struct kcpustate32 const *)(%reg + offset) */
#define ASM_CFI_REG_OFFSET_RESTORE_KCPUSTATE(offset, reg)                         \
	ASM_CFI_REG_OFFSET_RESTORE_GPREGS((offset) + OFFSET_KCPUSTATE32_GPREGS, reg)  \
	__ASM_L(.cfi_reg_offset %eflags, ((offset) + OFFSET_KCPUSTATE32_EFLAGS, reg)) \
	__ASM_L(.cfi_reg_offset %eip, ((offset) + OFFSET_KCPUSTATE32_EIP), reg)



/* RESTORE: ... = *(struct lcpustate32 const *)(CFA + offset) */
#define ASM_CFI_OFFSET_RESTORE_LCPUSTATE(offset)                   \
	__ASM_L(.cfi_offset %edi, ((offset) + OFFSET_LCPUSTATE32_EDI)) \
	__ASM_L(.cfi_offset %esi, ((offset) + OFFSET_LCPUSTATE32_ESI)) \
	__ASM_L(.cfi_offset %ebp, ((offset) + OFFSET_LCPUSTATE32_EBP)) \
	__ASM_L(.cfi_offset %esp, ((offset) + OFFSET_LCPUSTATE32_ESP)) \
	__ASM_L(.cfi_offset %ebx, ((offset) + OFFSET_LCPUSTATE32_EBX)) \
	__ASM_L(.cfi_offset %eip, ((offset) + OFFSET_LCPUSTATE32_EIP))

/* RESTORE: ... = *(struct lcpustate32 const *)(CFA + CFA_OFFSET + offset) */
#define ASM_CFI_REL_OFFSET_RESTORE_LCPUSTATE(offset)                   \
	__ASM_L(.cfi_rel_offset %edi, ((offset) + OFFSET_LCPUSTATE32_EDI)) \
	__ASM_L(.cfi_rel_offset %esi, ((offset) + OFFSET_LCPUSTATE32_ESI)) \
	__ASM_L(.cfi_rel_offset %ebp, ((offset) + OFFSET_LCPUSTATE32_EBP)) \
	__ASM_L(.cfi_rel_offset %esp, ((offset) + OFFSET_LCPUSTATE32_ESP)) \
	__ASM_L(.cfi_rel_offset %ebx, ((offset) + OFFSET_LCPUSTATE32_EBX)) \
	__ASM_L(.cfi_rel_offset %eip, ((offset) + OFFSET_LCPUSTATE32_EIP))

/* RESTORE: ... = *(struct lcpustate32 const *)(%reg + offset) */
#define ASM_CFI_REG_OFFSET_RESTORE_LCPUSTATE(offset, reg)                   \
	__ASM_L(.cfi_reg_offset %edi, ((offset) + OFFSET_LCPUSTATE32_EDI), reg) \
	__ASM_L(.cfi_reg_offset %esi, ((offset) + OFFSET_LCPUSTATE32_ESI), reg) \
	__ASM_L(.cfi_reg_offset %ebp, ((offset) + OFFSET_LCPUSTATE32_EBP), reg) \
	__ASM_L(.cfi_reg_offset %esp, ((offset) + OFFSET_LCPUSTATE32_ESP), reg) \
	__ASM_L(.cfi_reg_offset %ebx, ((offset) + OFFSET_LCPUSTATE32_EBX), reg) \
	__ASM_L(.cfi_reg_offset %eip, ((offset) + OFFSET_LCPUSTATE32_EIP), reg)





/* Push everything necessary to create an `icpustate'
 * from  an  `irregs'   structure  onto  the   stack. */
#define ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R  \
	__ASM_L(pushl_cfi_r %ds)                 \
	__ASM_L(pushl_cfi_r %es)                 \
	__ASM_L(pushl_cfi_r %fs)                 \
	__ASM_L(pushal_cfi_r)

/* Do the reverse of `ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R' */
#define ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R \
	__ASM_L(popal_cfi_r)                    \
	__ASM_L(popl_cfi_r %fs)                 \
	__ASM_L(popl_cfi_r %es)                 \
	__ASM_L(popl_cfi_r %ds)


/* Same as  `ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R',  but  must
 * be used on i386 if the IRET tail was generated by the CPU.
 *
 * A special macro is needed for this case, due to the fact
 * that in case of a  vm86 IRET tail, unwinding of  segment
 * registers has to be altered. */
#define ASM_PUSH_ICPUSTATE_AFTER_HW_IRET_CFI_R  \
	__ASM_L(pushl_cfi %ds)                      \
	__ASM_L(.cfi_restore_iret_ds_or_offset -4)  \
	__ASM_L(pushl_cfi %es)                      \
	__ASM_L(.cfi_restore_iret_es_or_offset -8)  \
	__ASM_L(pushl_cfi %fs)                      \
	__ASM_L(.cfi_restore_iret_fs_or_offset -12) \
	__ASM_L(pushal_cfi_r)

/* Do the reverse of `ASM_PUSH_ICPUSTATE_AFTER_HW_IRET_CFI_R' */
#define ASM_POP_ICPUSTATE_BEFORE_HW_IRET_CFI_R \
	__ASM_L(popal_cfi_r)                       \
	__ASM_L(popl_cfi %fs)                      \
	__ASM_L(.cfi_restore_iret_fs)              \
	__ASM_L(popl_cfi %es)                      \
	__ASM_L(.cfi_restore_iret_es)              \
	__ASM_L(popl_cfi %ds)                      \
	__ASM_L(.cfi_restore_iret_ds)


/* Push  everything necessary to create an `scpustate'
 * from an hardware-`irregs' structure onto the stack. */
#define ASM_PUSH_SCPUSTATE_AFTER_HW_IRET_CFI_R  \
	__ASM_L(pushl_cfi %ds)                      \
	__ASM_L(.cfi_restore_iret_ds_or_offset -4)  \
	__ASM_L(pushl_cfi %es)                      \
	__ASM_L(.cfi_restore_iret_es_or_offset -8)  \
	__ASM_L(pushl_cfi %fs)                      \
	__ASM_L(.cfi_restore_iret_fs_or_offset -12) \
	__ASM_L(pushl_cfi %gs)                      \
	__ASM_L(.cfi_restore_iret_gs_or_offset -16) \
	__ASM_L(pushal_cfi_r)

/* Do the reverse of `ASM_PUSH_SCPUSTATE_AFTER_HW_IRET_CFI_R' */
#define ASM_POP_SCPUSTATE_BEFORE_HW_IRET_CFI_R \
	__ASM_L(popal_cfi_r)                       \
	__ASM_L(popl_cfi %gs)                      \
	__ASM_L(.cfi_restore_iret_gs)              \
	__ASM_L(popl_cfi %fs)                      \
	__ASM_L(.cfi_restore_iret_fs)              \
	__ASM_L(popl_cfi %es)                      \
	__ASM_L(.cfi_restore_iret_es)              \
	__ASM_L(popl_cfi %ds)                      \
	__ASM_L(.cfi_restore_iret_ds)

/* Push everything necessary to create an `scpustate'
 * from  an  `irregs'   structure  onto  the   stack. */
#define ASM_PUSH_SCPUSTATE_AFTER_IRET_CFI_R \
	__ASM_L(pushl_cfi_r %ds)                \
	__ASM_L(pushl_cfi_r %es)                \
	__ASM_L(pushl_cfi_r %fs)                \
	__ASM_L(pushl_cfi_r %gs)                \
	__ASM_L(pushal_cfi_r)


/* Push everything necessary to create an `kcpustate'.
 * This macro assumes that before being used, `%eip' already exists in `0(%esp)'. */
#define ASM_PUSH_KCPUSTATE_AFTER_EIP_CFI_R_EX(sp_addend)           \
	__ASM_L(pushfl_cfi_r)                                          \
	__ASM_L(pushal_cfi_r)                                          \
	__ASM_L(addl $(8+(sp_addend)), 12(%esp)) /* fix pushed %esp */ \
	__ASM_L(.cfi_rel_offset %esp, 12) /* %esp can not be restored from-stack */
#define ASM_PUSH_KCPUSTATE_AFTER_EIP_CFI_R                  \
	__ASM_L(pushfl_cfi_r)                                   \
	__ASM_L(pushal_cfi_r)                                   \
	__ASM_L(addl $(8), 12(%esp))      /* fix pushed %esp */ \
	__ASM_L(.cfi_rel_offset %esp, 12) /* %esp can not be restored from-stack */
#define ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R_EX ASM_PUSH_KCPUSTATE_AFTER_EIP_CFI_R_EX
#define ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R    ASM_PUSH_KCPUSTATE_AFTER_EIP_CFI_R


#endif /* __i386__ && !__x86_64__ */


#endif /* !_I386_KOS_KOS_KERNEL_BITS_CPU_STATE_ASM32_H */
