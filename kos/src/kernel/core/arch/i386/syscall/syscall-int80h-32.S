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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_INT80H_32_S
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_INT80H_32_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <kernel/except.h>

#include <cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/ttest.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/x86/gdt.h>
#include <kos/rpc.h>

#include <errno.h>

#include "../../../../../../include/i386-kos/asm/syscalls32.h"



/************************************************************************/
/* INT 80H ENTRY                                                        */
/************************************************************************/
.section .text.hot
INTERN_CONST(x86_idtdpl_syscall, 3)
PUBLIC_FUNCTION(x86_idt_syscall)
	.cfi_startproc simple
	.cfi_restore_iret
	.cfi_def_cfa %esp, 0
	cmpl   $(__NR_syscall0_max), %eax
	ja     1f
	EXTERN(x86_sysroute0_asm32_int80)
	jmpl   *%ss:x86_sysroute0_asm32_int80(,%eax,4)
1:	cmpl   $(__NR_syscall1_min), %eax
	EXTERN(__x86_asm32_int80_break)
	jb     __x86_asm32_int80_break
	cmpl   $(__NR_syscall1_max), %eax
	ja     __x86_asm32_int80_break
	EXTERN(x86_sysroute1_asm32_int80)
	jmpl   *%ss:(x86_sysroute1_asm32_int80 - ((__NR_syscall1_min * 4) & 0xffffffff))(,%eax,4)
	.cfi_endproc
END(x86_idt_syscall)













/************************************************************************/
/* INT 80H TRACED ENTRY                                                 */
/************************************************************************/
#ifndef CONFIG_NO_KERNEL_SYSCALL_TRACING
.section .text.hot
PUBLIC_FUNCTION(x86_idt_syscall_traced)
	.cfi_startproc simple
	.cfi_restore_iret
	.cfi_def_cfa %esp, 0
	/* Trace this system call invocation! */
	pushfl_cfi_r

	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -8
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -12
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -16

	pushl_cfi_r %ebp /* ARG[5] */
	pushl_cfi_r %edi /* ARG[4] */
	pushl_cfi_r %esi /* ARG[3] */
	pushl_cfi_r %edx /* ARG[2] */
	pushl_cfi_r %ecx /* ARG[1] */
	pushl_cfi_r %ebx /* ARG[0] */
	pushl_cfi_r %eax /* SYSNO */

	/* Load kernel segments. */
	movl   $(SEGMENT_USER_DATA_RPL), %eax
	movl   %eax, %ds
	movl   %eax, %es
	movl   $(SEGMENT_KERNEL_FSBASE), %eax
	movl   %eax, %fs

	pushl_cfi $(RPC_SYSCALL_INFO_FREGVALID(0) | RPC_SYSCALL_INFO_FREGVALID(1) | \
	            RPC_SYSCALL_INFO_FREGVALID(2) | RPC_SYSCALL_INFO_FREGVALID(3) | \
	            RPC_SYSCALL_INFO_FREGVALID(4) | RPC_SYSCALL_INFO_FREGVALID(5) | \
	            RPC_SYSCALL_INFO_METHOD_INT80H_32)
	/* Check if exceptions are enabled. */
	ttest  mask=EFLAGS_DF, loc=(48 + OFFSET_IRREGS_EFLAGS)(%esp)
	jz     1f
	orw    $(RPC_SYSCALL_INFO_FEXCEPT), 0(%esp)
1:

	movl   %esp, %ecx
	EXTERN(syscall_trace)
	call   syscall_trace

	popl_cfi %eax /* flags (pop_void) */
	popl_cfi_r %eax /* SYSNO */
	popl_cfi_r %ebx /* ARG[0] */
	popl_cfi_r %ecx /* ARG[1] */
	popl_cfi_r %edx /* ARG[2] */
	popl_cfi_r %esi /* ARG[3] */
	popl_cfi_r %edi /* ARG[4] */
	popl_cfi_r %ebp /* ARG[5] */

	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds

	popfl_cfi_r

	cmpl   $(__NR_syscall0_max), %eax
	ja     1f
	EXTERN(x86_sysroute0_asm32_int80)
	jmpl   *%ss:x86_sysroute0_asm32_int80(,%eax,4)
1:	cmpl   $(__NR_syscall1_min), %eax
	EXTERN(__x86_asm32_int80_break)
	jb     __x86_asm32_int80_break
	cmpl   $(__NR_syscall1_max), %eax
	ja     __x86_asm32_int80_break
	EXTERN(x86_sysroute1_asm32_int80)
	jmpl   *%ss:x86_sysroute1_asm32_int80 - ((__NR_syscall1_min * 4) & 0xffffffff)(,%eax,4)
	.cfi_endproc
END(x86_idt_syscall_traced)
#endif /* !CONFIG_NO_KERNEL_SYSCALL_TRACING */













/************************************************************************/
/* INT 80H EMULATION ENTRY                                              */
/************************************************************************/
.section .text
PUBLIC_FUNCTION(x86_syscall_emulate_int80h_r)
	.cfi_startproc simple
	/* `struct icpustate *%ecx'
	 * NOTE: ENDOF(%ecx->IRREGS) is located at the end (top) of our kernel-stack! */
	.cfi_restore_iret
	.cfi_def_cfa %ecx, OFFSET_ICPUSTATE_IRREGS
	.cfi_rel_offset %ds, OFFSET_ICPUSTATE_DS
	.cfi_rel_offset %es, OFFSET_ICPUSTATE_ES
	.cfi_rel_offset %fs, OFFSET_ICPUSTATE_FS
	.cfi_same_value %gs
	.cfi_rel_offset %edi, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EDI
	.cfi_rel_offset %esi, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_ESI
	.cfi_rel_offset %ebp, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EBP
	.cfi_rel_offset %ebx, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EBX
	.cfi_rel_offset %edx, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EDX
	.cfi_rel_offset %ecx, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_ECX
	.cfi_rel_offset %eax, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EAX
	movl   %ecx, %esp /* No need to disable interrupts, since this stack switch is atomic! */
	.cfi_def_cfa_register %esp
	/* Restore user-space registers. */
	popal_cfi_r

	/* Restore user-space segment registers (NOTE: %gs already contains the user-space value) */
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds

	/* Define internal labels to allow for self-modifying code! */
	.byte  0xe9 /* jmp */
INTERN_OBJECT(x86_syscall_emulate_int80h_r_rel_x86_idt_syscall)
	.reloc ., R_386_PC32, x86_idt_syscall
	.long -4
END(x86_syscall_emulate_int80h_r_rel_x86_idt_syscall)
	.cfi_endproc
END(x86_syscall_emulate_int80h_r)

#ifndef __INTELLISENSE__
#include "syscall-int80h.S"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_INT80H_32_S */
