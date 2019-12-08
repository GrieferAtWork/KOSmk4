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
#ifndef _I386_KOS_KOS_KERNEL_CPU_STATE_ASM32_H
#define _I386_KOS_KOS_KERNEL_CPU_STATE_ASM32_H 1

#include <hybrid/host.h>

#include "cpu-state32.h"

#if defined(__i386__) && !defined(__x86_64__)
#include <hybrid/__asm.h>

#define ASM_CFI_REL_OFFSET_RESTORE_GPREGSNSP(offset)              \
	__ASM_L(.cfi_rel_offset %edi, ((offset) + OFFSET_GPREGS_EDI)) \
	__ASM_L(.cfi_rel_offset %esi, ((offset) + OFFSET_GPREGS_ESI)) \
	__ASM_L(.cfi_rel_offset %ebp, ((offset) + OFFSET_GPREGS_EBP)) \
	__ASM_L(.cfi_rel_offset %ebx, ((offset) + OFFSET_GPREGS_EBX)) \
	__ASM_L(.cfi_rel_offset %edx, ((offset) + OFFSET_GPREGS_EDX)) \
	__ASM_L(.cfi_rel_offset %ecx, ((offset) + OFFSET_GPREGS_ECX)) \
	__ASM_L(.cfi_rel_offset %eax, ((offset) + OFFSET_GPREGS_EAX))

#define ASM_CFI_OFFSET_RESTORE_GPREGSNSP(offset)              \
	__ASM_L(.cfi_offset %edi, ((offset) + OFFSET_GPREGS_EDI)) \
	__ASM_L(.cfi_offset %esi, ((offset) + OFFSET_GPREGS_ESI)) \
	__ASM_L(.cfi_offset %ebp, ((offset) + OFFSET_GPREGS_EBP)) \
	__ASM_L(.cfi_offset %ebx, ((offset) + OFFSET_GPREGS_EBX)) \
	__ASM_L(.cfi_offset %edx, ((offset) + OFFSET_GPREGS_EDX)) \
	__ASM_L(.cfi_offset %ecx, ((offset) + OFFSET_GPREGS_ECX)) \
	__ASM_L(.cfi_offset %eax, ((offset) + OFFSET_GPREGS_EAX))

#define ASM_CFI_REL_OFFSET_RESTORE_GPREGS(offset) \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGSNSP(offset)  \
	__ASM_L(.cfi_rel_offset %esp, ((offset) + OFFSET_GPREGS_ESP))

#define ASM_CFI_OFFSET_RESTORE_GPREGS(offset) \
	ASM_CFI_OFFSET_RESTORE_GPREGSNSP(offset)  \
	__ASM_L(.cfi_offset %esp, ((offset) + OFFSET_GPREGS_ESP))

#define ASM_CFI_REL_OFFSET_RESTORE_SGREGS(offset)               \
	__ASM_L(.cfi_rel_offset %gs, ((offset) + OFFSET_SGREGS_GS)) \
	__ASM_L(.cfi_rel_offset %fs, ((offset) + OFFSET_SGREGS_FS)) \
	__ASM_L(.cfi_rel_offset %es, ((offset) + OFFSET_SGREGS_ES)) \
	__ASM_L(.cfi_rel_offset %ds, ((offset) + OFFSET_SGREGS_DS))

#define ASM_CFI_REL_OFFSET_RESTORE_ICPUSTATE_NOIRET(offset)                  \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGSNSP((offset) + OFFSET_ICPUSTATE_GPREGS) \
	__ASM_L(.cfi_rel_offset %fs, ((offset) + OFFSET_ICPUSTATE_FS))           \
	__ASM_L(.cfi_rel_offset %es, ((offset) + OFFSET_ICPUSTATE_ES))           \
	__ASM_L(.cfi_rel_offset %ds, ((offset) + OFFSET_ICPUSTATE_DS))

#define ASM_CFI_REL_OFFSET_RESTORE_SCPUSTATE_NOIRET(offset)                  \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGSNSP((offset) + OFFSET_SCPUSTATE_GPREGS) \
	ASM_CFI_REL_OFFSET_RESTORE_SGREGS((offset) + OFFSET_SCPUSTATE_SGREGS)

#define ASM_CFI_REL_OFFSET_RESTORE_UCPUSTATE(offset)                         \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGSNSP((offset) + OFFSET_SCPUSTATE_GPREGS) \
	ASM_CFI_REL_OFFSET_RESTORE_SGREGS((offset) + OFFSET_SCPUSTATE_SGREGS)

#define ASM_CFI_REL_OFFSET_RESTORE_FCPUSTATE(offset)                       \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGS((offset) + OFFSET_FCPUSTATE_GPREGS)  \
	__ASM_L(.cfi_rel_offset %eflags, ((offset) + OFFSET_FCPUSTATE_EFLAGS)) \
	__ASM_L(.cfi_rel_offset %eip, ((offset) + OFFSET_FCPUSTATE_EIP))       \
	__ASM_L(.cfi_rel_offset %es, ((offset) + OFFSET_FCPUSTATE_ES))         \
	__ASM_L(.cfi_rel_offset %cs, ((offset) + OFFSET_FCPUSTATE_CS))         \
	__ASM_L(.cfi_rel_offset %ss, ((offset) + OFFSET_FCPUSTATE_SS))         \
	__ASM_L(.cfi_rel_offset %ds, ((offset) + OFFSET_FCPUSTATE_DS))         \
	__ASM_L(.cfi_rel_offset %fs, ((offset) + OFFSET_FCPUSTATE_FS))         \
	__ASM_L(.cfi_rel_offset %gs, ((offset) + OFFSET_FCPUSTATE_GS))         \
	__ASM_L(.cfi_rel_offset %tr, ((offset) + OFFSET_FCPUSTATE_TR))         \
	__ASM_L(.cfi_rel_offset %ldtr, ((offset) + OFFSET_FCPUSTATE_LDT))

#define ASM_CFI_OFFSET_RESTORE_FCPUSTATE(offset)                       \
	ASM_CFI_OFFSET_RESTORE_GPREGS((offset) + OFFSET_FCPUSTATE_GPREGS)  \
	__ASM_L(.cfi_offset %eflags, ((offset) + OFFSET_FCPUSTATE_EFLAGS)) \
	__ASM_L(.cfi_offset %eip, ((offset) + OFFSET_FCPUSTATE_EIP))       \
	__ASM_L(.cfi_offset %es, ((offset) + OFFSET_FCPUSTATE_ES))         \
	__ASM_L(.cfi_offset %cs, ((offset) + OFFSET_FCPUSTATE_CS))         \
	__ASM_L(.cfi_offset %ss, ((offset) + OFFSET_FCPUSTATE_SS))         \
	__ASM_L(.cfi_offset %ds, ((offset) + OFFSET_FCPUSTATE_DS))         \
	__ASM_L(.cfi_offset %fs, ((offset) + OFFSET_FCPUSTATE_FS))         \
	__ASM_L(.cfi_offset %gs, ((offset) + OFFSET_FCPUSTATE_GS))         \
	__ASM_L(.cfi_offset %tr, ((offset) + OFFSET_FCPUSTATE_TR))         \
	__ASM_L(.cfi_offset %ldtr, ((offset) + OFFSET_FCPUSTATE_LDT))

#define ASM_CFI_REL_OFFSET_RESTORE_KCPUSTATE(offset)                       \
	ASM_CFI_REL_OFFSET_RESTORE_GPREGS((offset) + OFFSET_KCPUSTATE_GPREGS)  \
	__ASM_L(.cfi_rel_offset %eflags, ((offset) + OFFSET_KCPUSTATE_EFLAGS)) \
	__ASM_L(.cfi_rel_offset %eip, ((offset) + OFFSET_KCPUSTATE_EIP))

#define ASM_CFI_REL_OFFSET_RESTORE_LCPUSTATE(offset)                 \
	__ASM_L(.cfi_rel_offset %edi, ((offset) + OFFSET_LCPUSTATE_EDI)) \
	__ASM_L(.cfi_rel_offset %esi, ((offset) + OFFSET_LCPUSTATE_ESI)) \
	__ASM_L(.cfi_rel_offset %ebp, ((offset) + OFFSET_LCPUSTATE_EBP)) \
	__ASM_L(.cfi_rel_offset %esp, ((offset) + OFFSET_LCPUSTATE_ESP)) \
	__ASM_L(.cfi_rel_offset %ebx, ((offset) + OFFSET_LCPUSTATE_EBX)) \
	__ASM_L(.cfi_rel_offset %eip, ((offset) + OFFSET_LCPUSTATE_EIP))

#endif /* __i386__ && !__x86_64__ */


#endif /* !_I386_KOS_KOS_KERNEL_CPU_STATE_ASM32_H */
