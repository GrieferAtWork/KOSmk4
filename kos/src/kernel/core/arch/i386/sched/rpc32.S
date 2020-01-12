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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_RPC32_S
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_RPC32_S 1

#include <kernel/compiler.h>
#include <kernel/gdt.h>
#include <kernel/except.h>
#include <sched/task.h>
#include <sched/rpc.h>
#include <kos/kernel/cpu-state.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>



.section .data.pertask.early
PUBLIC_OBJECT(this_x86_rpc_redirection_iret)
	.long  0  /* ir_eip */
	.long  0  /* ir_cs */
	.long  0  /* ir_eflags */
END(this_x86_rpc_redirection_iret)

.section .text
	.cfi_startproc simple
	.cfi_signal_frame
	EXTERN(x86_rpc_user_redirection_personality)
	.cfi_personality 0, x86_rpc_user_redirection_personality
/*[[[deemon
import compileExpression from .......misc.libgen.cfi.compiler;
for (local reg: ["eip", "cs", "eflags"]) {
	compileExpression('i386', '%' + reg, r'
		ifnotimpl "KOS", 1f
		push_tls_address
		plus     $@(this_x86_rpc_redirection_iret + OFFSET_IRREGS_' + reg.upper() + r')
		deref
		skip     2f
	1:	push     %' + reg + r'
		uninit
	2:');
}
for (local reg: { "es", "ds", "fs", "gs" }) {
	compileExpression('i386', '%' + reg, r'
		ifnotimpl "KOS", 1f
		push_tls_address
		plus     $@(this_x86_rpc_redirection_iret + OFFSET_IRREGS_EFLAGS)
		deref
		const2u  $@EFLAGS_VM
		and
		not
		bra      1f                        # Not a vm86 thread
		breg     %esp, $@(OFFSET_IRREGS_' + reg.upper() + r' - SIZEOF_IRREGS_KERNEL)
		deref                              # Load from the vm86 IRET tail
		skip     2f
	1:	push     %' + reg + r'             # Unchanged
		uninit
	2:');
}
]]]*/
__ASM_L(	.cfi_escape 0x16,0x08,0x12,0x2f,0x03,0x00,0x4b,0x4f)
__ASM_L(	.cfi_escape 0x53,0x2f,0x07,0x00,0xe0,0x23,(this_x86_rpc_redirection_iret + OFFSET_IRREGS_EIP),0x06)
__ASM_L(	.cfi_escape 0x2f,0x02,0x00,0x58,0xf0)
__ASM_L(	.cfi_escape 0x16,0x29,0x13,0x2f,0x03,0x00,0x4b,0x4f)
__ASM_L(	.cfi_escape 0x53,0x2f,0x07,0x00,0xe0,0x23,(this_x86_rpc_redirection_iret + OFFSET_IRREGS_CS),0x06)
__ASM_L(	.cfi_escape 0x2f,0x03,0x00,0x90,0x29,0xf0)
__ASM_L(	.cfi_escape 0x16,0x09,0x12,0x2f,0x03,0x00,0x4b,0x4f)
__ASM_L(	.cfi_escape 0x53,0x2f,0x07,0x00,0xe0,0x23,(this_x86_rpc_redirection_iret + OFFSET_IRREGS_EFLAGS),0x06)
__ASM_L(	.cfi_escape 0x2f,0x02,0x00,0x59,0xf0)
__ASM_L(	.cfi_escape 0x16,0x28,0x1e,0x2f,0x03,0x00,0x4b,0x4f)
__ASM_L(	.cfi_escape 0x53,0x2f,0x12,0x00,0xe0,0x23,(this_x86_rpc_redirection_iret + OFFSET_IRREGS_EFLAGS),0x06)
__ASM_L(	.cfi_escape 0x0a,(EFLAGS_VM) & 0xff,(EFLAGS_VM >> 8) & 0xff,0x1a,0x20,0x28,0x06,0x00)
__ASM_L(	.cfi_escape 0x74,(OFFSET_IRREGS_ES - SIZEOF_IRREGS_KERNEL),0x06,0x2f,0x03,0x00,0x90,0x28)
__ASM_L(	.cfi_escape 0xf0)
__ASM_L(	.cfi_escape 0x16,0x2b,0x1e,0x2f,0x03,0x00,0x4b,0x4f)
__ASM_L(	.cfi_escape 0x53,0x2f,0x12,0x00,0xe0,0x23,(this_x86_rpc_redirection_iret + OFFSET_IRREGS_EFLAGS),0x06)
__ASM_L(	.cfi_escape 0x0a,(EFLAGS_VM) & 0xff,(EFLAGS_VM >> 8) & 0xff,0x1a,0x20,0x28,0x06,0x00)
__ASM_L(	.cfi_escape 0x74,(OFFSET_IRREGS_DS - SIZEOF_IRREGS_KERNEL),0x06,0x2f,0x03,0x00,0x90,0x2b)
__ASM_L(	.cfi_escape 0xf0)
__ASM_L(	.cfi_escape 0x16,0x2c,0x1e,0x2f,0x03,0x00,0x4b,0x4f)
__ASM_L(	.cfi_escape 0x53,0x2f,0x12,0x00,0xe0,0x23,(this_x86_rpc_redirection_iret + OFFSET_IRREGS_EFLAGS),0x06)
__ASM_L(	.cfi_escape 0x0a,(EFLAGS_VM) & 0xff,(EFLAGS_VM >> 8) & 0xff,0x1a,0x20,0x28,0x06,0x00)
__ASM_L(	.cfi_escape 0x74,(OFFSET_IRREGS_FS - SIZEOF_IRREGS_KERNEL),0x06,0x2f,0x03,0x00,0x90,0x2c)
__ASM_L(	.cfi_escape 0xf0)
__ASM_L(	.cfi_escape 0x16,0x2d,0x1e,0x2f,0x03,0x00,0x4b,0x4f)
__ASM_L(	.cfi_escape 0x53,0x2f,0x12,0x00,0xe0,0x23,(this_x86_rpc_redirection_iret + OFFSET_IRREGS_EFLAGS),0x06)
__ASM_L(	.cfi_escape 0x0a,(EFLAGS_VM) & 0xff,(EFLAGS_VM >> 8) & 0xff,0x1a,0x20,0x28,0x06,0x00)
__ASM_L(	.cfi_escape 0x74,(OFFSET_IRREGS_GS - SIZEOF_IRREGS_KERNEL),0x06,0x2f,0x03,0x00,0x90,0x2d)
__ASM_L(	.cfi_escape 0xf0)
//[[[end]]]
	.cfi_reg_offset %esp, (OFFSET_IRREGS_ESP - SIZEOF_IRREGS_KERNEL), %esp
	.cfi_reg_offset %ss, (OFFSET_IRREGS_SS - SIZEOF_IRREGS_KERNEL), %esp
	.cfi_def_cfa %esp, 0

	nop /* Required to allow for detection during unwinding. */
PUBLIC_FUNCTION(x86_rpc_user_redirection)

	/* Entry point for redirected RPC callbacks */
	movl   %eax, %ss:OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX - (SIZEOF_IRREGS_KERNEL + OFFSET_ICPUSTATE_IRREGS)(%esp)
	.cfi_reg_offset %eax, (OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX - (SIZEOF_IRREGS_KERNEL + OFFSET_ICPUSTATE_IRREGS)), %esp
	movl   %fs, %eax
	.cfi_register %fs, %eax
	.cfi_reg_offset %eax, (OFFSET_ICPUSTATE_FS - (SIZEOF_IRREGS_KERNEL + OFFSET_ICPUSTATE_IRREGS)), %esp
	movl   %eax, %ss:OFFSET_ICPUSTATE_FS - (SIZEOF_IRREGS_KERNEL + OFFSET_ICPUSTATE_IRREGS)(%esp)
	.cfi_reg_offset %fs, (OFFSET_ICPUSTATE_FS - (SIZEOF_IRREGS_KERNEL + OFFSET_ICPUSTATE_IRREGS)), %esp
	/* EAX and FS have now been saved. */
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs

	movl   %fs:this_x86_rpc_redirection_iret + 8, %eax
	pushl  %eax     /* ir_eflags */
	.cfi_reg_offset %esp, 4, %esp
	.cfi_reg_offset %ss, 4, %esp
	.cfi_reg_offset %eax, (4 + OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX - (SIZEOF_IRREGS_KERNEL + OFFSET_ICPUSTATE_IRREGS)), %esp
	.cfi_reg_offset %fs, (4 + OFFSET_ICPUSTATE_FS - (SIZEOF_IRREGS_KERNEL + OFFSET_ICPUSTATE_IRREGS)), %esp
	movl   %fs:this_x86_rpc_redirection_iret + 4, %eax
	pushl  %eax     /* ir_cs */
	.cfi_reg_offset %esp, 8, %esp
	.cfi_reg_offset %ss, 4, %esp
	.cfi_reg_offset %eax, (8 + OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX - (SIZEOF_IRREGS_KERNEL + OFFSET_ICPUSTATE_IRREGS)), %esp
	.cfi_reg_offset %fs, (8 + OFFSET_ICPUSTATE_FS - (SIZEOF_IRREGS_KERNEL + OFFSET_ICPUSTATE_IRREGS)), %esp
	movl   %fs:this_x86_rpc_redirection_iret + 0, %eax
	pushl  %eax     /* ir_eip */
	.cfi_reg_offset %esp, 12, %esp
	.cfi_reg_offset %ss, 8, %esp
	.cfi_reg_offset %eax, (12 + OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX - (SIZEOF_IRREGS_KERNEL + OFFSET_ICPUSTATE_IRREGS)), %esp
	.cfi_reg_offset %fs, (12 + OFFSET_ICPUSTATE_FS - (SIZEOF_IRREGS_KERNEL + OFFSET_ICPUSTATE_IRREGS)), %esp
	pushl  %ds      /* ir_ds */
	.cfi_reg_offset %esp, 16, %esp
	.cfi_reg_offset %ss, 12, %esp
	.cfi_reg_offset %eax, (16 + OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX - (SIZEOF_IRREGS_KERNEL + OFFSET_ICPUSTATE_IRREGS)), %esp
	.cfi_reg_offset %fs, (16 + OFFSET_ICPUSTATE_FS - (SIZEOF_IRREGS_KERNEL + OFFSET_ICPUSTATE_IRREGS)), %esp
	pushl  %es      /* ir_es */
	.cfi_reg_offset %esp, 20, %esp
	.cfi_reg_offset %ss, 16, %esp
	.cfi_reg_offset %eax, (20 + OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX - (SIZEOF_IRREGS_KERNEL + OFFSET_ICPUSTATE_IRREGS)), %esp
	.cfi_reg_offset %fs, (20 + OFFSET_ICPUSTATE_FS - (SIZEOF_IRREGS_KERNEL + OFFSET_ICPUSTATE_IRREGS)), %esp
	subl   $(8), %esp /* ir_fs + gp_eax */
/*	.cfi_reg_offset %esp, 28, %esp */
/*	.cfi_reg_offset %ss, 24, %esp */
/*	.cfi_reg_offset %eax, (28 + OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX - (SIZEOF_IRREGS_KERNEL + OFFSET_ICPUSTATE_IRREGS)), %esp */
/*	.cfi_reg_offset %fs, (28 + OFFSET_ICPUSTATE_FS - (SIZEOF_IRREGS_KERNEL + OFFSET_ICPUSTATE_IRREGS)), %esp */
	.cfi_endproc

	/* With all saved registers now apart of the stack, and the
	 * entire IRET tail having been fully restored, create a new
	 * CFI procedure that is then implemented as a signal-frame,
	 * making further stack unwinding much simpler, as we can
	 * once again make life simpler by defining a CFA. */
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_def_cfa %esp, 16 /* Offset to the IRET tail (eax, fs, ds, es) */
	.cfi_rel_offset %eax, 0
	.cfi_restore_iret_gs
	.cfi_restore_iret_fs_or_offset -12
	.cfi_restore_iret_ds_or_offset -8
	.cfi_restore_iret_es_or_offset -4

	/* Re-enable interrupts, now that everything important has been saved. */
	sti

	/* Now save all of the other registers. */
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx
	pushl_cfi_r %esp
	pushl_cfi_r %ebp
	pushl_cfi_r %esi
	pushl_cfi_r %edi

	/* Load missing segment registers. */
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es

INTERN_FUNCTION(x86_serve_user_rpc_and_propagate_exceptions)

	/* Actually serve RPC callbacks! */
	movl   %esp, %ecx

	/* System call interrupts do their own user-RPC handling. */
	EXTERN(rpc_serve_async_user_redirection)
	call   rpc_serve_async_user_redirection
	movl   %eax, %esp

	/* Check for additional RPC callbacks. */
	cmpl   $(0), %fs:this_rpcs_pending
	jne    x86_serve_user_rpc_and_propagate_exceptions

	/* Check if an exception has been set for user-space. */
	cmpl   $(0), %fs:this_exception_code
	je     1f

	/* Check if exceptions are propagated to user-space, or kernel-space */
	testl  $(3), OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_CS(%esp)
	jnz    2f
	testl  $(EFLAGS_VM), OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_EFLAGS(%esp)
	jnz    2f
	/* Kernel-space target! */

	/* Check if the only reason we're still directed to kernel-space
	 * was another IRET redirection to `x86_rpc_user_redirection' */
	cmpl   $(x86_rpc_user_redirection), OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_EIP(%esp)
	/* Load the saved CPU state, which will bring us back up to the
	 * start of `x86_rpc_user_redirection'.
	 * From there, we automatically restore the actual user-space
	 * iret tail, handle additional RPC requests, before eventually
	 * getting here while the current IRET tail still points into
	 * userspace when `x86_userexcept_propagate()' is invoked! */
	je     1f
	EXTERN(x86_userexcept_unwind_interrupt_kernel_esp)
	jmp    x86_userexcept_unwind_interrupt_kernel_esp

2:	/* User-space target */
	movl   %esp, %ecx /* struct icpustate *__restrict state */
	xorl   %edx, %edx /* struct rpc_syscall_info *sc_info */
	EXTERN(x86_userexcept_propagate)
	call   x86_userexcept_propagate
	movl   %eax, %esp

1:	/* Restore the state after exception propagation. */
	popal_cfi_r
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(x86_serve_user_rpc_and_propagate_exceptions)
END(x86_rpc_user_redirection)









.section .text
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss
	.cfi_def_cfa %ebp, OFFSET_ICPUSTATE_IRREGS
	.cfi_rel_offset %edi, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDI
	.cfi_rel_offset %esi, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ESI
	.cfi_rel_offset %ebp, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBP
	.cfi_rel_offset %ebx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBX
	.cfi_rel_offset %edx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDX
	.cfi_rel_offset %ecx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ECX
	.cfi_rel_offset %eax, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX
	.cfi_restore_iret_gs
	.cfi_restore_iret_fs_or_offset (OFFSET_ICPUSTATE_FS - OFFSET_ICPUSTATE_IRREGS)
	.cfi_restore_iret_es_or_offset (OFFSET_ICPUSTATE_ES - OFFSET_ICPUSTATE_IRREGS)
	.cfi_restore_iret_ds_or_offset (OFFSET_ICPUSTATE_DS - OFFSET_ICPUSTATE_IRREGS)

	EXTERN(x86_rpc_kernel_redirection_personality)
	.cfi_personality 0, x86_rpc_kernel_redirection_personality
	nop /* Required to allow for detection during unwinding. */
INTERN_FUNCTION(x86_rpc_kernel_redirection)
	/* EAX:    <task_rpc_t func>
	 * ECX:    <void *arg>
	 * EDX:    <struct icpustate *>    (contains the return location; also used for CFI)
	 * EBX:    <unsigned int reason>
	 * EBP:    <struct icpustate *>    (Alias for `EDX')
	 * ESP:    { EDI, ESI, EBP, IGNORED, EBX, EDX, ECX, EAX, FS, ES, DS, IRREGS }
	 * EFLAGS: <0>                     (interrupts are disabled)
	 * CS:     <SEGMENT_KERNEL_CODE>
	 * SS:     <SEGMENT_KERNEL_DATA>
	 * DS:     <SEGMENT_USER_DATA_RPL>
	 * ES:     <SEGMENT_USER_DATA_RPL>
	 * FS:     <SEGMENT_KERNEL_FSBASE>
	 * GS:     Already restored
	 * *:      Undefined */
	pushl  $(0)  /* `struct rpc_syscall_info *sc_info' */
	pushl  %ebx  /* `unsigned int reason' */
	call   *%eax
	movl   %eax, %esp
	.cfi_def_cfa_register %esp

	/* Load the updated CPU state */
	popal_cfi_r
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
END(x86_rpc_kernel_redirection)
.cfi_endproc


.section .text
INTERN_FUNCTION(x86_rpc_kernel_redirection_handler)
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss
	.cfi_def_cfa %ebp, OFFSET_ICPUSTATE_IRREGS
	.cfi_rel_offset %edi, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDI
	.cfi_rel_offset %esi, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ESI
	.cfi_rel_offset %ebp, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBP
	.cfi_rel_offset %ebx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBX
	.cfi_rel_offset %edx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDX
	.cfi_rel_offset %ecx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ECX
	.cfi_rel_offset %eax, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX
	.cfi_restore_iret_gs
	.cfi_restore_iret_fs_or_offset (OFFSET_ICPUSTATE_FS - OFFSET_ICPUSTATE_IRREGS)
	.cfi_restore_iret_es_or_offset (OFFSET_ICPUSTATE_ES - OFFSET_ICPUSTATE_IRREGS)
	.cfi_restore_iret_ds_or_offset (OFFSET_ICPUSTATE_DS - OFFSET_ICPUSTATE_IRREGS)
	/* EAX:    <task_rpc_t func>
	 * ECX:    <void *arg>
	 * EDX:    <struct icpustate *>    (contains the return location; also used for CFI)
	 * EBX:    <unsigned int reason>
	 * EBP:    <struct icpustate *>    (Alias for `EDX')
	 * ESP:    { EDI, ESI, EBP, IGNORED, EBX, EDX, ECX, EAX, FS, ES, DS, IRREGS }
	 * EFLAGS: <0>                     (interrupts are disabled)
	 * CS:     <SEGMENT_KERNEL_CODE>
	 * SS:     <SEGMENT_KERNEL_DATA>
	 * DS:     <SEGMENT_USER_DATA_RPL>
	 * ES:     <SEGMENT_USER_DATA_RPL>
	 * FS:     <SEGMENT_KERNEL_FSBASE>
	 * GS:     Already restored
	 * *:      Undefined */
	pushl  $(0)   /* `struct rpc_syscall_info *sc_info' */
	pushl  %ebx /* reason */
	call   *%eax
	movl   %eax, %esp
	.cfi_def_cfa_register %esp
	/* Continue unwinding the exception that brought us here. */
	EXTERN(x86_userexcept_unwind_interrupt_esp)
	jmp    x86_userexcept_unwind_interrupt_esp
END(x86_rpc_kernel_redirection_handler)
.cfi_endproc






.section .text
PUBLIC_FUNCTION(task_rpc_exec_here)
	.cfi_startproc
	.cfi_signal_frame
	.cfi_def_cfa %esp, 0
	/* ECX:    <task_rpc_t func>
	 * EDX:    <void *arg>
	 * 0(ESP): <return address> */
	popl_cfi %eax
	.cfi_register %eip, %eax
	pushfl_cfi_r                     /* %eflags */
	pushl_cfi $(SEGMENT_KERNEL_CODE) /* %cs */
	pushl     %eax                   /* %eip */
	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss
	.cfi_restore_iret_gs
	.cfi_def_cfa %esp, 0
	/* ECX:    <task_rpc_t func>
	 * EDX:    <void *arg> */

	/* Generate a full ICPUSTATE */
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12

	pushal_cfi_r

	movl   %ecx, %eax                  /* <task_rpc_t func> */
	movl   %edx, %ecx                  /* <void *arg> */
	movl   %esp, %edx                  /* <struct icpustate *state> */
	pushl_cfi $(0)                     /* <struct rpc_syscall_info *sc_info> */
	pushl_cfi $(TASK_RPC_REASON_ASYNC) /* <unsigned int reason> */
	call   *%eax
	.cfi_adjust_cfa_offset -8
	movl   %eax, %esp

	popal_cfi_r

	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds

	iret
	.cfi_endproc
END(task_rpc_exec_here)


.section .text
PUBLIC_FUNCTION(task_rpc_exec_here_onexit)
	.cfi_startproc
	pushfl_cfi         /* irregs_kernel:ir_eflags */
	pushl_cfi %cs      /* irregs_kernel:ir_cs */
	pushl_cfi 12(%esp) /* irregs_kernel:ir_eip */
	pushl_cfi %fs      /* icpustate::ics_fs */
	pushl_cfi %es      /* icpustate::ics_es */
	pushl_cfi %ds      /* icpustate::ics_ds */
	pushal_cfi
	movl   %ecx, %eax                     /* task_rpc_t func */
	movl   %edx, %ecx                     /* void *arg */
	movl   %esp, %edx                     /* struct icpustate *state */
	pushl_cfi $(0)                        /* struct rpc_syscall_info const *sc_info */
	pushl_cfi $(TASK_RPC_REASON_SHUTDOWN) /* unsigned int reason */
	call   *%eax
	.cfi_adjust_cfa_offset -8
	addl   $(OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL), %esp
	.cfi_adjust_cfa_offset -(OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL)
	ret
	.cfi_endproc
END(task_rpc_exec_here_onexit)




.section .text
PUBLIC_FUNCTION(task_serve)
	.cfi_startproc
	cmpl   $(0), %fs:this_rpc_pending_sync_count
	jne    1f
#if 1 /* Service blocking cleanup operations. */
	call   blocking_cleanup_service
	/* If there are pending X-RPCs, service them below. */
	cmpl   $(BLOCKING_CLEANUP_SERVICE_XRPC), %eax
	je     1f
	/* return EAX == BLOCKING_CLEANUP_SERVICE_DONE */
	cmpl   $(BLOCKING_CLEANUP_SERVICE_DONE), %eax
	sete   %cl
	movzbl %cl, %eax
	ret
#else
	xorl   %eax, %eax
	ret
#endif
1:	/* Must service synchronous RPC functions!
	 * -> Construct an icpustate. */
	sti
	popl_cfi %eax
	.cfi_register %eip, %eax
	pushfl_cfi
	pushl_cfi %cs
	pushl_cfi %eax
	.cfi_endproc

	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss
	.cfi_restore_iret_gs
	.cfi_def_cfa %esp, 0

	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12

	movl   $(1), %eax /* Return $(1) later on (unless overwritten by RPC functions themself) */
	pushal_cfi_r

1:	movl   %esp, %ecx
	call   task_serve_one_impl /* Service a single RPC function */
	movl   %eax, %esp          /* Load the modified register state. */
	/* Check if there are more pending RPC callbacks. */
	cmpl   $(0), %fs:this_rpc_pending_sync_count
	jne    1b

#if 1 /* Service blocking cleanup operations. */
	call   blocking_cleanup_service
	cmpl   $(BLOCKING_CLEANUP_SERVICE_XRPC), %eax
	je     1b
#endif

	popal_cfi_r
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(task_serve)




.section .text
PUBLIC_FUNCTION(task_serve_nx)
	.cfi_startproc
	cmpl   $(0), %fs:this_rpc_pending_sync_count_nx
#if 1
	je     blocking_cleanup_service
#else
	jne    1f
#if TASK_SERVE_NX_XPENDING == 1
	xorl   %eax, %eax
	cmpl   $(0), %fs:this_rpc_pending_sync_count
	setne  %al
#else
	cmpl   $(0), %fs:this_rpc_pending_sync_count
	movl   $(TASK_SERVE_NX_DIDRUN), %ecx
	cmovne %ecx, %eax
#endif
	ret
1:
#endif
	/* Must service synchronous RPC functions!
	 * -> Construct an icpustate. */
	sti
	popl_cfi %eax
	.cfi_register %eip, %eax
	pushfl_cfi
	pushl_cfi %cs
	pushl_cfi %eax
	.cfi_endproc

	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss
	.cfi_restore_iret_gs
	.cfi_def_cfa %esp, 0

	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12

	/* Return $1 later on (unless overwritten by RPC functions themself) */
	movl   $(TASK_SERVE_NX_DIDRUN), %eax
	pushal_cfi_r

1:	movl   %esp, %ecx
	call   task_serve_one_nx_impl /* Service a single RPC function */
	movl   %eax, %esp             /* Load the modified register state. */
	/* Check if there are more pending RPC callbacks. */
	cmpl   $(0), %fs:this_rpc_pending_sync_count_nx
	jne    1b

#if 1 /* Service blocking cleanup operations. */
	call   blocking_cleanup_service
	orl    %eax, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX(%esp)
#endif

	popal_cfi_r
	cmpl   $(0), %fs:this_rpc_pending_sync_count
	je     1f
	orl    $TASK_SERVE_NX_XPENDING, %eax
1:
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds

	iret
	.cfi_endproc
END(task_serve_nx)

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_RPC32_S */
