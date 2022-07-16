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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_SYSENTER_64_S
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_SYSENTER_64_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <kernel/except.h>
#include <kernel/syscall.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/interrupt.h>
#include <asm/instr/movzxq.h>
#include <asm/instr/ttest.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/gdt.h>
#include <kos/kernel/paging.h>
#include <kos/rpc.h>

#include <errno.h>

#include "../../../../../../include/i386-kos/asm/syscalls32_d.h"








/************************************************************************/
/* SYSENTER ENTRY                                                       */
/************************************************************************/
.section .text.hot
PUBLIC_FUNCTION(x86_syscall32_sysenter)
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %rsp, 0
	.cfi_register %rsp, %rbp /* RBP is the designated return-sp register */
	.cfi_register %rip, %rdi /* RDI is the designated return-pc register */
	/* `IA32_SYSENTER_ESP' points at the RSP0 field of the CPU's TSS
	 * In other words:  we only  need to  replace RSP  with its  own
	 * dereference, and  we  already  have  `THIS_TASK->t_stackend'. */
	movq   0(%rsp), %rsp
	swapgs
	/* Construct an IRET tail. */
	pushq  $(SEGMENT_USER_DATA32_RPL) /* %ss */
	pushq  %rbp                       /* %userrsp */
	pushfq                            /* %rflags */
	orq    $(EFLAGS_IF), (%rsp)
	.cfi_reg_offset %rflags, 0, %rsp
	pushq  $(SEGMENT_USER_CODE32_RPL) /* %cs */
	.cfi_reg_offset %rflags, 8, %rsp
	pushq  %rdi                       /* %rip */
/*	.cfi_reg_offset %rflags, 16, %rsp */

	/* Switch over to IRET signal framing */
/*	.cfi_def_cfa %rsp, 0 */
	.cfi_restore_iret_rip
	.cfi_restore_iret_cs
	.cfi_restore_iret_rflags
	.cfi_restore_iret_rsp
	.cfi_restore_iret_ss
	/* Enable interrupts. */
	sti

	movzlq %eax, %rax
.Ldo_prepared_sysenter:
	cmpl   $(__NR32_syscall0_max), %eax
	ja     1f
	EXTERN(x86_sysroute0_asm32_sysenter)
	jmpq   *(x86_sysroute0_asm32_sysenter - ((__NR32_syscall0_min * 8) & 0xffffffffffffffff))(,%rax,8)
1:	cmpl   $(__NR32_syscall1_min), %eax
	EXTERN(__x86_asm32_sysenter_break)
	jb     __x86_asm32_sysenter_break
	cmpl   $(__NR32_syscall1_max), %eax
	ja     __x86_asm32_sysenter_break
	pushq_cfi_r %rax
	subl   $(__NR32_syscall1_min), %eax
	EXTERN(x86_sysroute1_asm32_sysenter)
	movq   x86_sysroute1_asm32_sysenter(,%rax,8), %rax
	xchgq  0(%rsp), %rax /* Restore RAX and store syscall entry in 0(%rsp) */
	ret                  /* Jump to the syscall entry */
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
	.cfi_def_cfa %rsp, 0
	.cfi_register %rsp, %rbp /* RBP is the designated return-sp register */
	.cfi_register %rip, %rdi /* RDI is the designated return-pc register */
	/* `IA32_SYSENTER_ESP' points at the ESP0 field of the CPU's TSS
	 * In other words:  we only  need to  replace RSP  with its  own
	 * dereference, and  we  already  have  `THIS_TASK->t_stackend'. */
	movq   0(%rsp), %rsp
	swapgs
	/* Construct an IRET tail. */
	pushq  $(SEGMENT_USER_DATA32_RPL) /* %ss */
	pushq  %rbp                       /* %userrsp */
	pushfq                            /* %rflags */
	orq    $(EFLAGS_IF), (%rsp)
	.cfi_reg_offset %rflags, 0, %rsp
	pushq  $(SEGMENT_USER_CODE32_RPL) /* %cs */
	.cfi_reg_offset %rflags, 8, %rsp
	pushq  %rdi                       /* %rip */

	/* With the IRET tail constructed, start a new CFI function with the SIGNAL_FRAME
	 * property enabled,  thus  allowing  for normal  system  call  return  behavior. */
/*	.cfi_def_cfa %rsp, 0 */
	.cfi_restore_iret_rip
	.cfi_restore_iret_cs
	.cfi_restore_iret_rflags
	.cfi_restore_iret_rsp
	.cfi_restore_iret_ss
	/* Enable interrupts. */
	sti
.Ldo_prepared_sysenter_traced:

	/* Trace this system call invocation! */
	movzlq %eax, %rax

	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	pushq_cfi_r %rdi
	pushq_cfi $(0)   /* ARG[5] */
	pushq_cfi $(0)   /* ARG[4] */
	pushq_cfi_r %rsi /* ARG[3] */
	pushq_cfi_r %rdx /* ARG[2] */
	pushq_cfi_r %rcx /* ARG[1] */
	pushq_cfi_r %rbx /* ARG[0] */
	pushq_cfi_r %rax /* SYSNO */

	pushq_cfi $(RPC_SYSCALL_INFO_FREGVALID(0) | RPC_SYSCALL_INFO_FREGVALID(1) | \
	            RPC_SYSCALL_INFO_FREGVALID(2) | RPC_SYSCALL_INFO_FREGVALID(3) | \
	            RPC_SYSCALL_INFO_METHOD_SYSENTER_32)
	/* Check if exceptions are enabled. */
	ttest  mask=EFLAGS_DF, loc=(104 + OFFSET_IRREGS_RFLAGS)(%rsp)
	jz     1f
	orw    $(RPC_SYSCALL_INFO_FEXCEPT), 0(%rsp)
1:

	/* Load ARG[4] / ARG[5] if necessary */
	cmpl   $(__NR32_syscall0_max), %eax
	ja     1f
	movq   %rax, %rcx
	shrq   $(1), %rcx
	EXTERN(kernel_syscall0_regcnt32)
	movb   kernel_syscall0_regcnt32(,%rcx,1), %cl
	jmp   .Lgot_mask
1:	subl   $(__NR32_syscall1_min), %eax
	jb    .Lgot_sysenter_args
	cmpl   $(__NR32_syscall1_max - __NR32_syscall1_min), %eax
	ja    .Lgot_sysenter_args
	movq   %rax, %rcx
	shrq   $(1), %rcx
	EXTERN(kernel_syscall1_regcnt32)
	movb   kernel_syscall1_regcnt32(,%rcx,1), %cl
.Lgot_mask:
	testb  $(1), %al
	jz     1f
	shrb   $(4), %cl
1:	andb   $(0x7), %cl
	cmpb   $(4), %cl
	jbe    .Lgot_sysenter_args
	/* Must load one (%cl == 5) or two (%cl == 6) arguments */
	movzlq %ebp, %rbp
	movzlq 0(%rbp), %rax
	movq   %rax, 48(%rsp) /* ARG[4] */
	orw    $(RPC_SYSCALL_INFO_FREGVALID(4)), 0(%rsp)
	cmpb   $(5), %cl
	jbe    .Lgot_sysenter_args
	/* Must also load the six'th argument! */
	movzlq 4(%rbp), %rax
	movq   %rax, 56(%rsp) /* ARG[5] */
	orw    $(RPC_SYSCALL_INFO_FREGVALID(5)), 0(%rsp)
.Lgot_sysenter_args:

	/* Actually call through to the system call tracer. */
	movq   %rsp, %rdi
	EXTERN(syscall_trace)
	call   syscall_trace

	popq_cfi %rax /* flags (pop_void) */
	popq_cfi_r %rax /* SYSNO */
	popq_cfi_r %rbx /* ARG[0] */
	popq_cfi_r %rcx /* ARG[1] */
	popq_cfi_r %rdx /* ARG[2] */
	popq_cfi_r %rsi /* ARG[3] */
	addq   $(16), %rsp
	.cfi_adjust_cfa_offset -16
	popq_cfi_r %rdi
	popq_cfi_r %r11
	popq_cfi_r %r10
	popq_cfi_r %r9
	popq_cfi_r %r8

	jmp    .Ldo_prepared_sysenter
	.cfi_endproc
END(x86_syscall32_sysenter_traced)
#endif /* !CONFIG_NO_KERNEL_SYSCALL_TRACING */













/************************************************************************/
/* SYSENTER EMULATION ENTRY                                             */
/************************************************************************/
.section .text
PUBLIC_FUNCTION(x86_syscall_emulate_sysenter_r)
	.cfi_startproc simple
	/* `struct icpustate *%rdi'
	 * NOTE: ENDOF(%ecx->IRREGS) is located at the end (top) of our kernel-stack! */
	.cfi_iret_signal_frame
	.cfi_def_cfa %rdi, 0
	ASM_CFI_OFFSET_RESTORE_ICPUSTATE(0)
	cli    /* Prevent corruptions while we're juggling with our stack. */
	movq   %rdi, %rsp
	.cfi_def_cfa_register %rsp
	/* Restore user-space registers. */
	ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R

	/* Check if our user-space return location got re-directed.
	 * If it was, we need to apply the register override at the
	 * saved return location, rather than the active one.
	 *
	 * After all: we don't ~actually~ do a sysret here; we just
	 *            barely  scrape by the edge of kernel-space in
	 *            order to fully reset our stack. */
	EXTERN(x86_userexcept_sysret)
	cmpq   $(x86_userexcept_sysret), OFFSET_IRREGS_RIP(%rsp)
	jne    1f
	EXTERN(this_x86_sysret_iret)
	movq   %rdi, %gs:(this_x86_sysret_iret + OFFSET_IRREGS_RIP) /* RIP := RDI */
	jmp    2f
1:	movq   %rdi, OFFSET_IRREGS_RIP(%rsp) /* RIP := RDI */
2:	movq   %rbp, OFFSET_IRREGS_RSP(%rsp) /* RSP := RBP */
	sti    /* Re-enable interrupts now that all async-critical components were serviced. */

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
	cmpb   $(0), syscall_tracing_enabled
	jne    .Ldo_prepared_sysenter_traced /* With tracing enabled... */
#endif /* !CONFIG_NO_KERNEL_SYSCALL_TRACING */
	jmp    .Ldo_prepared_sysenter
	.cfi_endproc
END(x86_syscall_emulate_sysenter_r)


#ifndef __INTELLISENSE__
#include "syscall-sysenter.S"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_SYSENTER_64_S */
