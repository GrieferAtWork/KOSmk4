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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_INT80H_64_S
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_INT80H_64_S 1

#include <hybrid/compiler.h>

#include <kernel/except.h>

#include <asm/cfi.h>
#include <asm/instr/interrupt.h>
#include <asm/instr/movzxq.h>
#include <asm/syscalls32_d.h>
#include <asm/syscalls64_d.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/gdt.h>

#include <errno.h>

#include <librpc/rpc.h>








/************************************************************************/
/* INT 80H ENTRY                                                        */
/************************************************************************/
.section .text.hot
INTERN_CONST(__x86_idtdpl_syscall, 3)
PUBLIC_FUNCTION(x86_idt_syscall)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	/* Because we can assume that we only get here from user-space with #IF enabled,
	 * we don't have to swapgs or sti conditionally, but can simply always do so. */
	swapgs
	sti
	/* Check if the system call was invoked from compatibility mode. */
	cmpq   $(SEGMENT_USER_CODE32_RPL), OFFSET_IRREGS_CS(%rsp)
	je     .Lsyscall_int80_32bit

	/* Invocation of int80h from 64-bit code. */
.Lsyscall_int80_64bit:
	cmpq   $(__NR64_syscall0_max), %rax
	ja     1f
	EXTERN(x86_sysroute0_asm64_syscall)
	jmpq   *(x86_sysroute0_asm64_syscall - ((__NR64_syscall0_min * 8) & 0xffffffffffffffff))(,%rax,8)
1:	cmpq   $(__NR64_syscall1_min), %rax
	EXTERN(__x86_asm64_syscall_break)
	jb     __x86_asm64_syscall_break
	cmpq   $(__NR64_syscall1_max), %rax
	ja     __x86_asm64_syscall_break
	pushq_cfi_r %rax
	subq   $(__NR64_syscall1_min), %rax
	EXTERN(x86_sysroute1_asm64_syscall)
	movq   x86_sysroute1_asm64_syscall(,%rax,8), %rax
	xchgq  0(%rsp), %rax /* Restore RAX and store syscall entry in 0(%rsp) */
	ret                  /* Jump to the syscall entry */

.Lsyscall_int80_32bit:
	movzlq %eax, %rax /* Zero-extend to ensure that the upper 32 bit are zero */
	cmpl   $(__NR32_syscall0_max), %eax
	ja     1f
	EXTERN(x86_sysroute0_asm32_int80)
	jmpq   *x86_sysroute0_asm32_int80(,%rax,8)
1:	cmpl   $(__NR32_syscall1_min), %eax
	EXTERN(__x86_asm32_int80_break)
	jb     __x86_asm32_int80_break
	cmpl   $(__NR32_syscall1_max), %eax
	ja     __x86_asm32_int80_break
	EXTERN(x86_sysroute1_asm32_int80)
	jmpq   *(x86_sysroute1_asm32_int80 - ((__NR32_syscall1_min * 8) & 0xffffffff))(,%rax,8)
	.cfi_endproc
END(x86_idt_syscall)













/************************************************************************/
/* INT 80H TRACED ENTRY                                                 */
/************************************************************************/
#ifndef CONFIG_NO_SYSCALL_TRACING
.section .text.hot
PUBLIC_FUNCTION(x86_idt_syscall_traced)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	/* Only get here from user-space, so we can do an unconditional swapgs on entry! */
	swapgs
	/* Check if we got here from compatibility mode.
	 * Note that this check must be done before re-enabling interrupts, since
	 * once that is done, our iret tail may have already been redirected! */
	cmpq   $(SEGMENT_USER_CODE32_RPL), OFFSET_IRREGS64_CS(%rsp)
	/* Unconditionally re-enable interrupts (only get here from user-space) */
	sti
	je     1f /* Compatibility mode */

	pushq_cfi_r %rcx
	pushq_cfi_r %r11
	pushq_cfi_r %r9  /* ARG[5] */
	pushq_cfi_r %r8  /* ARG[4] */
	pushq_cfi_r %r10 /* ARG[3] */
	pushq_cfi_r %rdx /* ARG[2] */
	pushq_cfi_r %rsi /* ARG[1] */
	pushq_cfi_r %rdi /* ARG[0] */
	pushq_cfi_r %rax /* SYSNO */

	movq   %rsp, %rdi
	EXTERN(syscall_trace)
	call   syscall_trace

	popq_cfi_r %rax /* SYSNO */
	popq_cfi_r %rdi /* ARG[0] */
	popq_cfi_r %rsi /* ARG[1] */
	popq_cfi_r %rdx /* ARG[2] */
	popq_cfi_r %r10 /* ARG[3] */
	popq_cfi_r %r8  /* ARG[4] */
	popq_cfi_r %r9  /* ARG[5] */
	popq_cfi_r %r11
	popq_cfi_r %rcx
	jmp    .Lsyscall_int80_64bit

1:	movzlq %eax, %rax
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	pushq_cfi_r %rbp /* ARG[5] */
	pushq_cfi_r %rdi /* ARG[4] */
	pushq_cfi_r %rsi /* ARG[3] */
	pushq_cfi_r %rdx /* ARG[2] */
	pushq_cfi_r %rcx /* ARG[1] */
	pushq_cfi_r %rbx /* ARG[0] */
	pushq_cfi_r %rax /* SYSNO */

	movq   %rsp, %rdi
	EXTERN(syscall_trace_compat)
	call   syscall_trace_compat

	popq_cfi_r %rax /* SYSNO */
	popq_cfi_r %rbx /* ARG[0] */
	popq_cfi_r %rcx /* ARG[1] */
	popq_cfi_r %rdx /* ARG[2] */
	popq_cfi_r %rsi /* ARG[3] */
	popq_cfi_r %rdi /* ARG[4] */
	popq_cfi_r %rbp /* ARG[5] */
	popq_cfi_r %r11
	popq_cfi_r %r10
	popq_cfi_r %r9
	popq_cfi_r %r8
	jmp    .Lsyscall_int80_32bit
	.cfi_endproc
END(x86_idt_syscall_traced)
#endif /* !CONFIG_NO_SYSCALL_TRACING */













/************************************************************************/
/* INT 80H EMULATION ENTRY                                              */
/************************************************************************/
.section .text
PUBLIC_FUNCTION(x86_syscall_emulate_int80h_r)
	.cfi_startproc simple
	/* `struct icpustate *%rdi'
	 * NOTE: ENDOF(%rdi->IRREGS) is located at the end (top) of our kernel-stack! */
	.cfi_signal_frame
	.cfi_def_cfa %rdi, 0
	ASM_CFI_REL_OFFSET_RESTORE_ICPUSTATE(0)
	movq   %rdi, %rsp /* No need to disable interrupts, since this stack switch is atomic! */
	.cfi_def_cfa_register %rsp
	/* Restore user-space registers. */
	ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R

	/* At this point, most of the original user-space CPU context from the point
	 * when the `sysenter' instruction was executed has been restored. Additionally,
	 * we have already applied the required register transformations for safely
	 * returning to user-space once we're done here.
	 * -> With all of this done, we can now continue handling the sysenter as
	 *    though the CPU had supported the instruction from the get-go, using
	 *    the same assembly-level wrappers that would normally be used for
	 *    routing a real sysenter system call invocation. */
#ifndef CONFIG_NO_SYSCALL_TRACING
	EXTERN(syscall_tracing_enabled)
	cmpb   $(0), syscall_tracing_enabled
	EXTERN(x86_idt_syscall_traced)
	jne    x86_idt_syscall_traced /* With tracing enabled... */
#endif /* !CONFIG_NO_SYSCALL_TRACING */
	EXTERN(x86_idt_syscall)
	jmp    x86_idt_syscall
	.cfi_endproc
END(x86_syscall_emulate_int80h_r)


.section .text.cold
INTERN_FUNCTION(__x86_asm64_syscall_break)
	/* For `int 80h' system calls:
	 *   Called when a system call number hasn't been assigned (%eax:sysno) */
	.cfi_startproc simple
	EXTERN(x86_syscall_personality_asm64_syscall_break)
	.cfi_personality 0, x86_syscall_personality_asm64_syscall_break
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0

	/* Check IRET.EFLAGS.CF if an exception should be thrown */
	testq  $(EFLAGS_CF), OFFSET_IRREGS_RFLAGS(%rsp)
	jnz    1f
	movq   $-ENOSYS, %rax
	intr_exit
1:	pushq_cfi_r %r9  /* ARG[5] */
	pushq_cfi_r %r8  /* ARG[4] */
	pushq_cfi_r %r10 /* ARG[3] */
	pushq_cfi_r %rdx /* ARG[2] */
	movq   %rsi, %r9 /* ARG[1] */
	.cfi_register %rsi, %r9
	movq   %rdi, %r8 /* ARG[0] */
	.cfi_register %rdi, %r8
	movq   %rax, %rcx /* SYSNO */
	.cfi_register %rax, %rcx

	/* Throw an `E_UNKNOWN_SYSTEMCALL' exception */
	movq   $(RPC_SYSCALL_INFO_METHOD_INT80H_64 | RPC_SYSCALL_INFO_FEXCEPT |  \
	         RPC_SYSCALL_INFO_FARGVALID(0) | RPC_SYSCALL_INFO_FARGVALID(1) | \
	         RPC_SYSCALL_INFO_FARGVALID(2) | RPC_SYSCALL_INFO_FARGVALID(3) | \
	         RPC_SYSCALL_INFO_FARGVALID(4) | RPC_SYSCALL_INFO_FARGVALID(5)), %rdx
	movq   $(8), %rsi
	movq   $(ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi
	EXTERN(error_thrown)
	call   error_thrown
	.cfi_endproc
END(__x86_asm64_syscall_break)




.section .text.cold
INTERN_FUNCTION(__x86_asm32_int80_break)
	/* For `int 80h' system calls:
	 *   Called when a system call number hasn't been assigned (%eax:sysno) */
	.cfi_startproc simple
	EXTERN(x86_syscall_personality_asm32_int80_break)
	.cfi_personality 0, x86_syscall_personality_asm32_int80_break
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0

	/* Check IRET.EFLAGS.CF if an exception should be thrown */
	testq  $(EFLAGS_CF), OFFSET_IRREGS_RFLAGS(%rsp)
	jnz    1f
	movq   $-ENOSYS, %rax
	intr_exit
1:	pushq_cfi_r %rbp /* ARG[5] */
	pushq_cfi_r %rdi /* ARG[4] */
	pushq_cfi_r %rsi /* ARG[3] */
	pushq_cfi_r %rdx /* ARG[2] */
	movq   %rcx, %r9 /* ARG[1] */
	.cfi_register %rcx, %r9
	movq   %rbx, %r8 /* ARG[0] */
	.cfi_register %rbx, %r8
	movq   %rax, %rcx /* SYSNO */
	.cfi_register %rax, %rcx

	/* Throw an `E_UNKNOWN_SYSTEMCALL' exception */
	movq   $(RPC_SYSCALL_INFO_METHOD_INT80H_32 | RPC_SYSCALL_INFO_FEXCEPT |  \
	         RPC_SYSCALL_INFO_FARGVALID(0) | RPC_SYSCALL_INFO_FARGVALID(1) | \
	         RPC_SYSCALL_INFO_FARGVALID(2) | RPC_SYSCALL_INFO_FARGVALID(3) | \
	         RPC_SYSCALL_INFO_FARGVALID(4) | RPC_SYSCALL_INFO_FARGVALID(5)), %rdx
	movq   $(8), %rsi
	movq   $(ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi
	EXTERN(error_thrown)
	call   error_thrown
	.cfi_endproc
END(__x86_asm32_int80_break)

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_INT80H_64_S */
