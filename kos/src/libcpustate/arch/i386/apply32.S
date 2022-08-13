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
#ifndef GUARD_LIBCPUSTATE_ARCH_I386_APPLY32_S
#define GUARD_LIBCPUSTATE_ARCH_I386_APPLY32_S 1

#include "../../api.h"
/**/

#include <hybrid/compiler.h>

#include <cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/ttest.h>
#include <kos/kernel/cpu-state.h>

#include <libcpustate/apply.h>


#ifdef __KERNEL__
#define TEXT_SECTION     .xdata
#define BEGIN_TRAP(name) PUBLIC_FUNCTION(name); .byte 0xe9; .long 0x00000000
#define END_TRAP(name)   END(name)
#else /* __KERNEL__ */
#define TEXT_SECTION     .text
#define BEGIN_TRAP(name) /* nothing */
#define END_TRAP(name)   /* nothing */
#endif /* !__KERNEL__ */


#ifdef __KERNEL__
.section TEXT_SECTION
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %ecx, OFFSET_ICPUSTATE_IRREGS
	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss
	.cfi_restore_iret_es_or_offset (OFFSET_ICPUSTATE_ES - OFFSET_ICPUSTATE_IRREGS)
	.cfi_restore_iret_ds_or_offset (OFFSET_ICPUSTATE_DS - OFFSET_ICPUSTATE_IRREGS)
	.cfi_restore_iret_fs_or_offset (OFFSET_ICPUSTATE_FS - OFFSET_ICPUSTATE_IRREGS)
	.cfi_restore_iret_gs
	.cfi_rel_offset %edi, (OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDI)
	.cfi_rel_offset %esi, (OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ESI)
	.cfi_rel_offset %ebp, (OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBP)
	.cfi_rel_offset %ebx, (OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBX)
	.cfi_rel_offset %edx, (OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDX)
	.cfi_rel_offset %ecx, (OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ECX)
	.cfi_rel_offset %eax, (OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX)
BEGIN_TRAP(kernel_debugtrap_icpustate)
INTERN_FUNCTION(libcpu_apply_icpustate)
	movl  %ecx, %esp
	.cfi_def_cfa_register %esp
INTERN_FUNCTION(libcpu_apply_icpustate_esp)
	popal_cfi_r
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(libcpu_apply_icpustate_esp)
END(libcpu_apply_icpustate)
END_TRAP(kernel_debugtrap_icpustate)
DEFINE_PUBLIC_ALIAS(cpu_apply_icpustate, libcpu_apply_icpustate)
DEFINE_PUBLIC_ALIAS(cpu_apply_icpustate_esp, libcpu_apply_icpustate_esp)



.section TEXT_SECTION
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %ecx, OFFSET_SCPUSTATE_IRREGS
	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss
	.cfi_restore_iret_es_or_offset ((OFFSET_SCPUSTATE_SGREGS + OFFSET_SGREGS_ES) - OFFSET_SCPUSTATE_IRREGS)
	.cfi_restore_iret_ds_or_offset ((OFFSET_SCPUSTATE_SGREGS + OFFSET_SGREGS_DS) - OFFSET_SCPUSTATE_IRREGS)
	.cfi_restore_iret_fs_or_offset ((OFFSET_SCPUSTATE_SGREGS + OFFSET_SGREGS_FS) - OFFSET_SCPUSTATE_IRREGS)
	.cfi_restore_iret_gs_or_offset ((OFFSET_SCPUSTATE_SGREGS + OFFSET_SGREGS_GS) - OFFSET_SCPUSTATE_IRREGS)
	.cfi_rel_offset %edi, (OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_EDI)
	.cfi_rel_offset %esi, (OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_ESI)
	.cfi_rel_offset %ebp, (OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_EBP)
	.cfi_rel_offset %ebx, (OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_EBX)
	.cfi_rel_offset %edx, (OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_EDX)
	.cfi_rel_offset %ecx, (OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_ECX)
	.cfi_rel_offset %eax, (OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_EAX)
BEGIN_TRAP(kernel_debugtrap_scpustate)
INTERN_FUNCTION(libcpu_apply_scpustate)
	movl  %ecx, %esp
	.cfi_def_cfa_register %esp
INTERN_FUNCTION(libcpu_apply_scpustate_esp)
	popal_cfi_r
	popl_cfi %gs
	.cfi_restore_iret_gs
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(libcpu_apply_scpustate_esp)
END(libcpu_apply_scpustate)
END_TRAP(kernel_debugtrap_scpustate)
DEFINE_PUBLIC_ALIAS(cpu_apply_scpustate, libcpu_apply_scpustate)
DEFINE_PUBLIC_ALIAS(cpu_apply_scpustate_esp, libcpu_apply_scpustate_esp)

#endif /* __KERNEL__ */



.section TEXT_SECTION
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %ecx, 0
	.cfi_rel_offset %edi, (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_EDI)
	.cfi_rel_offset %esi, (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_ESI)
	.cfi_rel_offset %ebp, (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_EBP)
	.cfi_rel_offset %esp, (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_ESP)
	.cfi_rel_offset %ebx, (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_EBX)
	.cfi_rel_offset %edx, (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_EDX)
	.cfi_rel_offset %ecx, (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_ECX)
	.cfi_rel_offset %eax, (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_EAX)
	.cfi_rel_offset %ds, (OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_DS)
	.cfi_rel_offset %es, (OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_ES)
	.cfi_rel_offset %fs, (OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_FS)
	.cfi_rel_offset %gs, (OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_GS)
	.cfi_rel_offset %cs, OFFSET_UCPUSTATE_CS
	.cfi_rel_offset %ss, OFFSET_UCPUSTATE_SS
	.cfi_rel_offset %eflags, OFFSET_UCPUSTATE_EFLAGS
	.cfi_rel_offset %eip, OFFSET_UCPUSTATE_EIP
BEGIN_TRAP(kernel_debugtrap_ucpustate)
INTERN_FUNCTION(libcpu_apply_ucpustate)
	/* Immediatly load registers that won't be needed further below! */
	movl   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_EDI)(%ecx), %edi
	.cfi_same_value %edi
	movl   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_ESI)(%ecx), %esi
	.cfi_same_value %esi
	movl   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_EBP)(%ecx), %ebp
	.cfi_same_value %ebp
	movl   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_EBX)(%ecx), %ebx
	.cfi_same_value %ebx
	movl   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_EDX)(%ecx), %edx
	.cfi_same_value %edx
	/* Check if we need to construct a vm86 IRET tail. */
#ifndef __I386_NO_VM86
	ttest  mask=EFLAGS_VM, loc=OFFSET_UCPUSTATE_EFLAGS(%ecx)
	jz     1f
	pushl  (OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_GS)(%ecx)
	pushl  (OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_FS)(%ecx)
	pushl  (OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_DS)(%ecx)
	pushl  (OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_ES)(%ecx)
	jmp    2f
#endif /* !__I386_NO_VM86 */
1:	/* Load segment registers normally. */
	movl   (OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_GS)(%ecx), %eax
	movl   %eax, %gs
	movl   (OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_FS)(%ecx), %eax
	movl   %eax, %fs
	movl   (OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_ES)(%ecx), %eax
	movl   %eax, %es
	movl   (OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_DS)(%ecx), %eax
	movl   %eax, %ds
	/* Check if this leads into ring that is different from ours. */
	ttest  mask=3, loc=OFFSET_UCPUSTATE_CS(%ecx), seg=%ss
#ifdef __KERNEL__
	jz     1f
#else /* __KERNEL__ */
	jnz    1f
#endif /* !__KERNEL__ */
	/* Push what is required for a USER-IRET tail. */
	pushl  %ss:OFFSET_UCPUSTATE_SS(%ecx)
	pushl  %ss:(OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_ESP)(%ecx)
	jmp    2f
1:	movl   %ss:(OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_ESP)(%ecx), %esp
2:	/* Push registers that already need to appear */
	pushl  %ss:OFFSET_UCPUSTATE_EFLAGS(%ecx)
	pushl  %ss:OFFSET_UCPUSTATE_CS(%ecx)
	pushl  %ss:OFFSET_UCPUSTATE_EIP(%ecx)
	/* With the IRET tail fully constructed, set-up CFI to restore registers from there. */
	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss
	.cfi_restore_iret_es
	.cfi_restore_iret_ds
	.cfi_restore_iret_fs
	.cfi_restore_iret_gs
	movl   %ss:(OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_EAX)(%ecx), %eax
	.cfi_same_value %eax
	movl   %ss:(OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_ECX)(%ecx), %ecx
	.cfi_same_value %ecx
	iret
	.cfi_endproc
END(libcpu_apply_ucpustate)
END_TRAP(kernel_debugtrap_ucpustate)
DEFINE_PUBLIC_ALIAS(cpu_apply_ucpustate, libcpu_apply_ucpustate)


.section TEXT_SECTION
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %ecx, 0
	.cfi_rel_offset %edi, (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDI)
	.cfi_rel_offset %esi, (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESI)
	.cfi_rel_offset %ebp, (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EBP)
	.cfi_rel_offset %esp, (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP)
	.cfi_rel_offset %ebx, (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EBX)
	.cfi_rel_offset %edx, (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX)
	.cfi_rel_offset %ecx, (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX)
	.cfi_rel_offset %eax, (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX)
	.cfi_rel_offset %eflags, OFFSET_KCPUSTATE_EFLAGS
	.cfi_rel_offset %eip, OFFSET_KCPUSTATE_EIP
BEGIN_TRAP(kernel_debugtrap_kcpustate)
INTERN_FUNCTION(libcpu_apply_kcpustate)
	movl   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDI)(%ecx), %edi
	.cfi_same_value %edi
	movl   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESI)(%ecx), %esi
	.cfi_same_value %esi
	movl   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EBP)(%ecx), %ebp
	.cfi_same_value %ebp
	movl   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP)(%ecx), %esp
	movl   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EBX)(%ecx), %ebx
	.cfi_same_value %ebx
	movl   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX)(%ecx), %edx
	.cfi_same_value %edx
	movl   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX)(%ecx), %eax
	.cfi_same_value %eax
	pushl   OFFSET_KCPUSTATE_EFLAGS(%ecx)
	popfl
	pushl   OFFSET_KCPUSTATE_EIP(%ecx)
	.cfi_same_value %eflags
	.cfi_same_value %esp
	.cfi_def_cfa %esp, 4
	.cfi_rel_offset %eip, 0
	movl   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX)(%ecx), %ecx
	.cfi_same_value %ecx
	ret
	.cfi_endproc
END(libcpu_apply_kcpustate)
END_TRAP(kernel_debugtrap_kcpustate)
DEFINE_PUBLIC_ALIAS(cpu_apply_kcpustate, libcpu_apply_kcpustate)


.section .xdata
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %ecx, 0
	.cfi_rel_offset %edi, OFFSET_LCPUSTATE_EDI
	.cfi_rel_offset %esi, OFFSET_LCPUSTATE_ESI
	.cfi_rel_offset %ebp, OFFSET_LCPUSTATE_EBP
	.cfi_rel_offset %esp, OFFSET_LCPUSTATE_ESP
	.cfi_rel_offset %ebx, OFFSET_LCPUSTATE_EBX
	.cfi_rel_offset %eip, OFFSET_LCPUSTATE_EIP
BEGIN_TRAP(kernel_debugtrap_lcpustate)
INTERN_FUNCTION(libcpu_apply_lcpustate)
	movl   OFFSET_LCPUSTATE_EDI(%ecx), %edi
	movl   OFFSET_LCPUSTATE_ESI(%ecx), %esi
	movl   OFFSET_LCPUSTATE_EBP(%ecx), %ebp
	movl   OFFSET_LCPUSTATE_ESP(%ecx), %esp
	movl   OFFSET_LCPUSTATE_EBX(%ecx), %ebx
	pushl  OFFSET_LCPUSTATE_EIP(%ecx)
	ret
	.cfi_endproc
END(libcpu_apply_lcpustate)
END_TRAP(kernel_debugtrap_lcpustate)
DEFINE_PUBLIC_ALIAS(cpu_apply_lcpustate, libcpu_apply_lcpustate)


.section TEXT_SECTION
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %ecx, 0
	.cfi_rel_offset %edi, OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EDI
	.cfi_rel_offset %esi, OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_ESI
	.cfi_rel_offset %ebp, OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EBP
	.cfi_rel_offset %esp, OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_ESP
	.cfi_rel_offset %ebx, OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EBX
	.cfi_rel_offset %edx, OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EDX
	.cfi_rel_offset %ecx, OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_ECX
	.cfi_rel_offset %eax, OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EAX
	.cfi_rel_offset %gs, OFFSET_FCPUSTATE_GS
	.cfi_rel_offset %fs, OFFSET_FCPUSTATE_FS
	.cfi_rel_offset %es, OFFSET_FCPUSTATE_ES
	.cfi_rel_offset %ds, OFFSET_FCPUSTATE_DS
	.cfi_rel_offset %cs, OFFSET_FCPUSTATE_CS
	.cfi_rel_offset %ss, OFFSET_FCPUSTATE_SS
	.cfi_rel_offset %tr, OFFSET_FCPUSTATE_TR
	.cfi_rel_offset %ldtr, OFFSET_FCPUSTATE_LDT
	.cfi_rel_offset %eflags, OFFSET_FCPUSTATE_EFLAGS
	.cfi_rel_offset %eip, OFFSET_FCPUSTATE_EIP
BEGIN_TRAP(kernel_debugtrap_fcpustate)
INTERN_FUNCTION(libcpu_apply_fcpustate)
	lgdtl  OFFSET_FCPUSTATE_GDT(%ecx)
	lidtl  OFFSET_FCPUSTATE_IDT(%ecx)
	movw   OFFSET_FCPUSTATE_TR(%ecx), %ax
	ltrw   %ax
	.cfi_same_value %tr
	movw   OFFSET_FCPUSTATE_LDT(%ecx), %ax
	lldtw  %ax
	.cfi_same_value %ldtr
	movl   (OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR0)(%ecx), %eax
	movl   %eax, %cr0
	movl   (OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR2)(%ecx), %eax
	movl   %eax, %cr2
	movl   (OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR3)(%ecx), %eax
	movl   %eax, %cr3
	movl   (OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR4)(%ecx), %eax
	movl   %eax, %cr4
	movl   (OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR0)(%ecx), %eax
	movl   %eax, %dr0
	movl   (OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR1)(%ecx), %eax
	movl   %eax, %dr1
	movl   (OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR2)(%ecx), %eax
	movl   %eax, %dr2
	movl   (OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR3)(%ecx), %eax
	movl   %eax, %dr3
	movl   (OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR6)(%ecx), %eax
	movl   %eax, %dr6
	movl   (OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR7)(%ecx), %eax
	movl   %eax, %dr7
	movl   (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EDI)(%ecx), %edi
	.cfi_same_value %edi
	movl   (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_ESI)(%ecx), %esi
	.cfi_same_value %esi
	movl   (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EBP)(%ecx), %ebp
	.cfi_same_value %ebp
	movl   (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EBX)(%ecx), %ebx
	.cfi_same_value %ebx
	movl   (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EDX)(%ecx), %edx
	.cfi_same_value %edx

#ifndef __I386_NO_VM86
	ttest  mask=EFLAGS_VM, loc=OFFSET_FCPUSTATE_EFLAGS(%ecx)
	jz     1f
	/* Return to vm86 */
	.cfi_remember_state
	pushl  OFFSET_FCPUSTATE_GS(%ecx)
	pushl  OFFSET_FCPUSTATE_FS(%ecx)
	pushl  OFFSET_FCPUSTATE_DS(%ecx)
	pushl  OFFSET_FCPUSTATE_ES(%ecx)
	pushl  OFFSET_FCPUSTATE_SS(%ecx)
	pushl  (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_ESP)(%ecx)
	pushl  OFFSET_FCPUSTATE_EFLAGS(%ecx)
	pushl  OFFSET_FCPUSTATE_CS(%ecx)
	pushl  OFFSET_FCPUSTATE_EIP(%ecx)
	movl   (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EAX)(%ecx), %eax
	.cfi_same_value %eax
	movl   (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_ECX)(%ecx), %ecx
	.cfi_same_value %ecx
	.cfi_reg_offset %eip, 0, %esp
	.cfi_reg_offset %cs, 4, %esp
	.cfi_reg_offset %eflags, 8, %esp
	.cfi_reg_offset %esp, 12, %esp
	.cfi_reg_offset %ss, 16, %esp
	.cfi_reg_offset %es, 20, %esp
	.cfi_reg_offset %ds, 24, %esp
	.cfi_reg_offset %fs, 28, %esp
	.cfi_reg_offset %gs, 32, %esp
	iret
	.cfi_restore_state
#endif /* !__I386_NO_VM86 */

1:	movw   OFFSET_FCPUSTATE_ES(%ecx), %ax
	movw   %ax, %es
	.cfi_same_value %es
	movw   OFFSET_FCPUSTATE_FS(%ecx), %ax
	movw   %ax, %fs
	.cfi_same_value %fs
	movw   OFFSET_FCPUSTATE_GS(%ecx), %ax
	movw   %ax, %gs
	.cfi_same_value %gs
	movw   OFFSET_FCPUSTATE_DS(%ecx), %ax
	movw   %ax, %ds
	.cfi_same_value %ds
	ttest  mask=3, loc=OFFSET_FCPUSTATE_CS(%ecx), seg=%ss
#ifdef __KERNEL__
	jz     1f
#else /* __KERNEL__ */
	jnz    1f
#endif /* !__KERNEL__ */
	/* Return to user-space */
	.cfi_remember_state
	pushl  %ss:OFFSET_FCPUSTATE_SS(%ecx)
	pushl  %ss:(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_ESP)(%ecx)
	pushl  %ss:OFFSET_FCPUSTATE_EFLAGS(%ecx)
	pushl  %ss:OFFSET_FCPUSTATE_CS(%ecx)
	pushl  %ss:OFFSET_FCPUSTATE_EIP(%ecx)
	movl   %ss:(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EAX)(%ecx), %eax
	.cfi_same_value %eax
	movl   %ss:(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_ECX)(%ecx), %ecx
	.cfi_same_value %ecx
	.cfi_reg_offset %eip, 0, %esp
	.cfi_reg_offset %cs, 4, %esp
	.cfi_reg_offset %eflags, 8, %esp
	.cfi_reg_offset %esp, 12, %esp
	.cfi_reg_offset %ss, 16, %esp
	iret
	.cfi_restore_state
1:	/* Return to kernel-space */
	movl   %ss:(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_ESP)(%ecx), %esp
	.cfi_same_value %esp
	movw   %ss:OFFSET_FCPUSTATE_SS(%ecx), %ax
	movw   %ax, %ss
	.cfi_same_value %ss
	pushl  %ss:OFFSET_FCPUSTATE_EFLAGS(%ecx)
	pushl  %ss:OFFSET_FCPUSTATE_CS(%ecx)
	pushl  %ss:OFFSET_FCPUSTATE_EIP(%ecx)
	movl   %ss:(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EAX)(%ecx), %eax
	.cfi_same_value %eax
	movl   %ss:(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_ECX)(%ecx), %ecx
	.cfi_same_value %ecx
	iret
	.cfi_endproc
END(libcpu_apply_fcpustate)
END_TRAP(kernel_debugtrap_fcpustate)
DEFINE_PUBLIC_ALIAS(cpu_apply_fcpustate, libcpu_apply_fcpustate)

#endif /* !GUARD_LIBCPUSTATE_ARCH_I386_APPLY32_S */
