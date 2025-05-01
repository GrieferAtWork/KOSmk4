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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_SYSENTER_32_S
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_SYSENTER_32_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <kernel/except.h>
#include <kernel/syscall.h>

#include <cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/compat.h>
#include <asm/instr/ttest.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/x86/gdt.h>
#include <kos/kernel/paging.h>
#include <kos/rpc.h>

#include <errno.h>

#include "../../../../../../include/i386-kos/asm/syscalls32.h"








/************************************************************************/
/* SYSENTER ENTRY                                                       */
/************************************************************************/
.section .text.hot
PUBLIC_FUNCTION(x86_syscall32_sysenter)
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %esp, 0
	.cfi_register %esp, %ebp /* EBP is the designated return-sp register */
	.cfi_register %eip, %edi /* EDI is the designated return-pc register */
	/* `IA32_SYSENTER_ESP' points at the ESP0 field of the CPU's TSS
	 * In other words:  we only  need to  replace ESP  with its  own
	 * dereference, and  we  already  have  `THIS_TASK->t_stackend'. */
	movl   %ss:0(%esp), %esp
	/* Construct an IRET tail. */
	pushl  $(SEGMENT_USER_DATA_RPL) /* %ss */
	pushl  %ebp                     /* %useresp */
	pushfl
	orl    $(EFLAGS_IF), %ss:(%esp)
	.cfi_reg_offset %eflags, 0, %esp
	pushl  $(SEGMENT_USER_CODE_RPL) /* %cs */
	.cfi_reg_offset %eflags, 4, %esp
	pushl  %edi                     /* %eip */
/*	.cfi_reg_offset %eflags, 8, %esp */

	/* Switch over to IRET signal framing */
/*	.cfi_def_cfa %esp, 0 */
	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss
	/* Enable interrupts. */
	sti
.Ldo_prepared_sysenter:
	cmpl   $(__NR_syscall0_max), %eax
	ja     1f
	EXTERN(x86_sysroute0_asm32_sysenter)
	jmpl   *%ss:x86_sysroute0_asm32_sysenter(,%eax,4)
1:	cmpl   $(__NR_syscall1_min), %eax
	EXTERN(__x86_asm32_sysenter_break)
	jb     __x86_asm32_sysenter_break
	cmpl   $(__NR_syscall1_max), %eax
	ja     __x86_asm32_sysenter_break
	EXTERN(x86_sysroute1_asm32_sysenter)
	jmpl   *%ss:x86_sysroute1_asm32_sysenter - ((__NR_syscall1_min * 4) & 0xffffffff)(,%eax,4)
	.cfi_endproc
END(x86_syscall32_sysenter)













/************************************************************************/
/* SYSENTER TRACED ENTRY                                                */
/************************************************************************/
#ifndef CONFIG_NO_KERNEL_SYSCALL_TRACING
.section .text.hot
PUBLIC_FUNCTION(x86_syscall32_sysenter_traced)
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %esp, 0
	.cfi_register %esp, %ebp /* EBP is the designated return-sp register */
	.cfi_register %eip, %edi /* EDI is the designated return-pc register */
	/* `IA32_SYSENTER_ESP' points at the ESP0 field of the CPU's TSS
	 * In other words:  we only  need to  replace ESP  with its  own
	 * dereference, and  we  already  have  `THIS_TASK->t_stackend'. */
	movl   %ss:0(%esp), %esp
	/* Construct an IRET tail. */
	pushl  $(SEGMENT_USER_DATA_RPL) /* %ss */
	pushl  %ebp                     /* %useresp */
	pushfl                          /* %eflags */
	orl    $(EFLAGS_IF), %ss:(%esp)
	.cfi_reg_offset %eflags, 0, %esp
	pushl  $(SEGMENT_USER_CODE_RPL) /* %cs */
	.cfi_reg_offset %eflags, 4, %esp
	pushl  %edi                     /* %eip */

	/* With the IRET tail constructed, start a new CFI function with the SIGNAL_FRAME
	 * property enabled,  thus  allowing  for normal  system  call  return  behavior. */
/*	.cfi_def_cfa %esp, 0 */
	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss
	/* Enable interrupts. */
	sti
.Ldo_prepared_sysenter_traced:

	/* Trace this system call invocation! */

	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -8
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -12
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -16

	pushl_cfi   $(0) /* ARG[5] */
	pushl_cfi   $(0) /* ARG[4] */
	pushl_cfi_r %esi /* ARG[3] */
	pushl_cfi_r %edx /* ARG[2] */
	pushl_cfi_r %ecx /* ARG[1] */
	pushl_cfi_r %ebx /* ARG[0] */
	pushl_cfi_r %eax /* SYSNO */

	pushl_cfi $(RPC_SYSCALL_INFO_FREGVALID(0) | RPC_SYSCALL_INFO_FREGVALID(1) | \
	            RPC_SYSCALL_INFO_FREGVALID(2) | RPC_SYSCALL_INFO_FREGVALID(3) | \
	            RPC_SYSCALL_INFO_METHOD_SYSENTER_32)
	/* Check if exceptions are enabled. */
	ttest  mask=EFLAGS_DF, loc=(44 + OFFSET_IRREGS_EFLAGS)(%esp)
	jz     1f
	orw    $(RPC_SYSCALL_INFO_FEXCEPT), 0(%esp)
1:

	/* Load kernel segments. */
	movw   $(SEGMENT_USER_DATA_RPL), %cx
	movw   %cx, %ds
	movw   %cx, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %cx
	movw   %cx, %fs

	/* Load ARG[4] / ARG[5] if necessary */
	cmpl   $(__NR_syscall0_max), %eax
	ja     1f
	movl   %eax, %ecx
	shrl   $(1), %ecx
	EXTERN(kernel_syscall0_regcnt)
	movb   kernel_syscall0_regcnt(,%ecx,1), %cl
	jmp   .Lgot_mask
1:	subl   $(__NR_syscall1_min), %eax
	jb    .Lgot_sysenter_args
	cmpl   $(__NR_syscall1_max - __NR_syscall1_min), %eax
	ja    .Lgot_sysenter_args
	movl   %eax, %ecx
	shrl   $(1), %ecx
	EXTERN(kernel_syscall1_regcnt)
	movb   kernel_syscall1_regcnt(,%ecx,1), %cl
.Lgot_mask:
	testb  $(1), %al
	jz     1f
	shrb   $(4), %cl
1:	andb   $(0x7), %cl
	cmpb   $(4), %cl
	jbe    .Lgot_sysenter_args
	/* Must load one (%cl == 5) or two (%cl == 6) arguments */
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    .Lbad_args_pointer
	movl   0(%ebp), %eax
	movl   %eax, 24(%esp) /* ARG[4] */
	orw    $(RPC_SYSCALL_INFO_FREGVALID(4)), 0(%esp)
	cmpb   $(5), %cl
	jbe    .Lgot_sysenter_args
	/* Must also load the six'th argument! */
	movl   4(%ebp), %eax
	movl   %eax, 28(%esp) /* ARG[5] */
	orw    $(RPC_SYSCALL_INFO_FREGVALID(5)), 0(%esp)
.Lgot_sysenter_args:



	/* Actually call through to the system call tracer. */
	movl   %esp, %ecx
	EXTERN(syscall_trace)
	call   syscall_trace

	.cfi_remember_state
	popl_cfi %eax /* flags (pop_void) */
	popl_cfi_r %eax /* SYSNO */
	popl_cfi_r %ebx /* ARG[0] */
	popl_cfi_r %ecx /* ARG[1] */
	popl_cfi_r %edx /* ARG[2] */
	popl_cfi_r %esi /* ARG[3] */
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8

	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds


	cmpl   $(__NR_syscall0_max), %eax
	ja     1f
	jmpl   *%ss:x86_sysroute0_asm32_sysenter(,%eax,4)
1:	cmpl   $(__NR_syscall1_min), %eax
	jb     __x86_asm32_sysenter_break
	cmpl   $(__NR_syscall1_max), %eax
	ja     __x86_asm32_sysenter_break
	jmpl   *%ss:x86_sysroute1_asm32_sysenter - ((__NR_syscall1_min * 4) & 0xffffffff)(,%eax,4)
	.cfi_restore_state
.Lbad_args_pointer:
	popl_cfi_r %eax /* SYSNO */
	popl_cfi_r %ebx /* ARG[0] */
	popl_cfi_r %ecx /* ARG[1] */
	popl_cfi_r %edx /* ARG[2] */
	popl_cfi_r %esi /* ARG[3] */
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	jmp    __asm32_bad_sysenter_extension
	.cfi_endproc
END(x86_syscall32_sysenter_traced)
#endif /* !CONFIG_NO_KERNEL_SYSCALL_TRACING */













/************************************************************************/
/* SYSENTER EMULATION ENTRY                                             */
/************************************************************************/
.section .text
PUBLIC_FUNCTION(x86_syscall_emulate_sysenter_r)
	.cfi_startproc simple
	/* `struct icpustate *%ecx'
	 * NOTE: ENDOF(%ecx->IRREGS) is located at the end (top) of our kernel-stack! */
	.cfi_iret_signal_frame
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
	cli    /* Prevent corruptions while we're juggling with our stack. */
	movl   %ecx, %esp
	.cfi_def_cfa_register %esp
	/* Restore user-space registers. */
	popal_cfi_r

	/* Check if our user-space return location got re-directed.
	 * If it was, we need to apply the register override at the
	 * saved return location, rather than the active one.
	 *
	 * After all: we don't ~actually~ do a sysret here; we just
	 *            barely  scrape by the edge of kernel-space in
	 *            order to fully reset our stack. */
	EXTERN(x86_userexcept_sysret)
	cmpl   $(x86_userexcept_sysret), (12 + OFFSET_IRREGS_EIP)(%esp)
	jne    1f
	EXTERN(this_x86_sysret_iret)
	movl   %edi, %fs:(this_x86_sysret_iret + OFFSET_IRREGS_EIP) /* EIP := EDI */
	jmp    2f
1:	movl   %edi, 12+OFFSET_IRREGS_EIP(%esp) /* EIP := EDI */
2:	movl   %ebp, 12+OFFSET_IRREGS_ESP(%esp) /* ESP := EBP */
	sti    /* Re-enable interrupts now that all async-critical components were serviced. */

	/* Restore user-space segment registers (NOTE: %gs already contains the user-space value) */
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds

	/* At this point,  most of the  original user-space CPU  context from the  point
	 * when the `sysenter' instruction was executed has been restored. Additionally,
	 * we have  already applied  the required  register transformations  for  safely
	 * returning to user-space once we're done here.
	 * -> With all of this done, we can now continue handling the sysenter as
	 *    though the CPU had supported the instruction from the get-go, using
	 *    the same assembly-level  wrappers that would  normally be used  for
	 *    routing a real sysenter system call invocation. */
#ifndef CONFIG_NO_KERNEL_SYSCALL_TRACING
	EXTERN(syscall_tracing_enabled)
	cmpb   $(0), %ss:syscall_tracing_enabled
	jne    .Ldo_prepared_sysenter_traced /* With tracing enabled... */
#endif /* !CONFIG_NO_KERNEL_SYSCALL_TRACING */
	jmp    .Ldo_prepared_sysenter
	.cfi_endproc
END(x86_syscall_emulate_sysenter_r)












#define TEST_DOUBLE_WIDE(sysno_reg, sysno_reg_b, tempreg_l, tempreg_b, segment_prefix)  \
	cmpl   $(__NR_syscall0_max), sysno_reg;                                             \
	ja     1234f;                                                                       \
	movl   sysno_reg, tempreg_l;                                                        \
	shrl   $(1), tempreg_l;                                                             \
	EXTERN(kernel_syscall0_regcnt);                                                     \
	movb   segment_prefix kernel_syscall0_regcnt(,tempreg_l,1), tempreg_b;              \
	jmp    1235f;                                                                       \
1234:                                                                                   \
	leal   -__NR_syscall1_min(sysno_reg), tempreg_l;                                    \
	shrl   $(1), tempreg_l;                                                             \
	EXTERN(kernel_syscall1_regcnt);                                                     \
	movb   segment_prefix kernel_syscall1_regcnt(,tempreg_l,1), tempreg_b;              \
1235:                                                                                   \
	testb  $(1), sysno_reg_b;                                                           \
	jz     1234f;                                                                       \
	shrb   $(4), tempreg_b;                                                             \
1234:                                                                                   \
	testb  $(0x8), tempreg_b;


.section .text.cold
INTERN_FUNCTION(__asm32_bad_sysenter_extension)
	/* Called when the %ebp pointer of a sysenter callback
	 * is   faulty   (aka:   points   into   kernel-space) */
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss
	.cfi_def_cfa %esp, 12
	.cfi_restore_iret_gs
	.cfi_restore_iret_fs_or_offset -4
	.cfi_restore_iret_es_or_offset -8
	.cfi_restore_iret_ds_or_offset -12

	/* Check IRET.EFLAGS.DF if an exception should be thrown */
	ttest  mask=EFLAGS_DF, loc=12 + OFFSET_IRREGS_EFLAGS(%esp), seg=%ss
	jnz    1f

	/* Check if we must sign-extend the error return value. */
	pushl_cfi_r %ecx
	TEST_DOUBLE_WIDE(%eax, %al, %ecx, %cl, %ss:)
	popl_cfi_r %ecx
	jz     1f
	movl   $-1, %edx
1:	movl   $-EFAULT, %eax
	.cfi_remember_state

	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds

	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_restore_state
1:
	/* We want to handle the error via `userexcept_handler', thereby kind-of
	 * emulating what is done by  `x86_syscall_personality_asm32_sysenter()' */
	pushal_cfi_r  /* Construct a full `struct icpustate' */

	/* Make sure that kernel segments have been loaded */
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs

	movP   %Psp, %R_fcall0P
	EXTERN(__asm32_bad_sysenter_extension_impl)
	call   __asm32_bad_sysenter_extension_impl

	/* Restart the sysenter system call */
	movP   %Pax, %Psp
	popal_cfi_r
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	jmp    .Ldo_prepared_sysenter
	.cfi_endproc
END(__asm32_bad_sysenter_extension)

#ifndef __INTELLISENSE__
#include "syscall-sysenter.S"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_SYSENTER_32_S */
