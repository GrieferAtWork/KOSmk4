/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_INT80H_64_S
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_INT80H_64_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <kernel/except.h>

#include <cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/compat.h>
#include <asm/instr/interrupt.h>
#include <asm/instr/movzxq.h>
#include <asm/instr/ttest.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/x86/gdt.h>
#include <kos/rpc.h>

#include <errno.h>

#include "../../../../../../include/i386-kos/asm/syscalls32_d.h"
#include "../../../../../../include/i386-kos/asm/syscalls64_d.h"







/************************************************************************/
/* INT 80H ENTRY                                                        */
/************************************************************************/
.section .text.hot
INTERN_CONST(x86_idtdpl_syscall, 3)
PUBLIC_FUNCTION(x86_idt_syscall)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	/* Because we can assume that we only get here from user-space with #IF enabled,
	 * we don't have to swapgs  or sti conditionally, but  can simply always do  so. */
	swapgs
	sti
PUBLIC_FUNCTION(x86_syscall64_int80_after_swapgs)
	/* Check if the system call was invoked from compatibility mode. */
	cmpq   $(SEGMENT_USER_CODE32_RPL), OFFSET_IRREGS_CS(%rsp)
	je     x86_syscall64x32_int80

	/* Invocation of int80h from 64-bit code. */
PUBLIC_FUNCTION(x86_syscall64x64_int80)
	cmpq   $(__NR64_syscall0_max), %rax
	ja     1f
	EXTERN(x86_sysroute0_asm64_syscall)
	jmpq   *(x86_sysroute0_asm64_syscall - ((__NR64_syscall0_min * 8) & 0xffffffffffffffff))(,%rax,8)
1:	cmpq   $(__NR64_syscall1_min), %rax
	EXTERN(__x86_asm64_syscall_break)
	jb     __x86_asm64_syscall_break
	cmpq   $(__NR64_syscall1_max), %rax
	ja     __x86_asm64_syscall_break
	jmpq   *(x86_sysroute1_asm64_syscall - ((__NR64_syscall1_min * 8) & 0xffffffffffffffff))(,%rax,8)
END(x86_syscall64x64_int80)

PUBLIC_FUNCTION(x86_syscall64x32_int80)
	movzlq %eax, %rax /* Zero-extend to ensure that the upper 32 bit are zero */
	cmpl   $(__NR32_syscall0_max), %eax
	ja     1f
	EXTERN(x86_sysroute0_asm32_int80)
	jmpq   *(x86_sysroute0_asm32_int80 - ((__NR32_syscall0_min * 8) & 0xffffffffffffffff))(,%rax,8)
1:	cmpl   $(__NR32_syscall1_min), %eax
	EXTERN(__x86_asm32_int80_break)
	jb     __x86_asm32_int80_break
	cmpl   $(__NR32_syscall1_max), %eax
	ja     __x86_asm32_int80_break

	pushq_cfi_r %rax
	subl   $(__NR32_syscall1_min), %eax
	EXTERN(x86_sysroute1_asm32_int80)
	movq   x86_sysroute1_asm32_int80(,%rax,8), %rax
	xchgq  0(%rsp), %rax /* Restore RAX and store syscall entry in 0(%rsp) */
	.cfi_restore %rax
	ret                  /* Jump to the syscall entry */
END(x86_syscall64x32_int80)
	.cfi_endproc
END(x86_syscall64_int80_after_swapgs)
END(x86_idt_syscall)













/************************************************************************/
/* INT 80H TRACED ENTRY                                                 */
/************************************************************************/
#ifndef CONFIG_NO_KERNEL_SYSCALL_TRACING
.section .text.hot
PUBLIC_FUNCTION(x86_idt_syscall_traced)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	/* Only get here from user-space, so we can do an unconditional swapgs on entry! */
	swapgs
PUBLIC_FUNCTION(x86_syscall64_int80_after_swapgs_traced)
	/* Check if we got here from compatibility mode.
	 * Note that this check must be done before re-enabling interrupts, since
	 * once  that is  done, our iret  tail may have  already been redirected! */
	cmpq   $(SEGMENT_USER_CODE32_RPL), OFFSET_IRREGS64_CS(%rsp)
	/* Unconditionally re-enable interrupts (only get here from user-space) */
	sti
	je     x86_syscall64x32_int80_traced /* Compatibility mode */

PUBLIC_FUNCTION(x86_syscall64x64_int80_traced)
	pushq_cfi_r %rcx
	pushq_cfi_r %r11
	pushq_cfi_r %r9  /* ARG[5] */
	pushq_cfi_r %r8  /* ARG[4] */
	pushq_cfi_r %r10 /* ARG[3] */
	pushq_cfi_r %rdx /* ARG[2] */
	pushq_cfi_r %rsi /* ARG[1] */
	pushq_cfi_r %rdi /* ARG[0] */
	pushq_cfi_r %rax /* SYSNO */

	pushq_cfi $(RPC_SYSCALL_INFO_FREGVALID(0) | RPC_SYSCALL_INFO_FREGVALID(1) | \
	            RPC_SYSCALL_INFO_FREGVALID(2) | RPC_SYSCALL_INFO_FREGVALID(3) | \
	            RPC_SYSCALL_INFO_FREGVALID(4) | RPC_SYSCALL_INFO_FREGVALID(5) | \
	            RPC_SYSCALL_INFO_METHOD_INT80H_64)
	/* Check if exceptions are enabled. */
	ttest  mask=EFLAGS_DF, loc=(80 + OFFSET_IRREGS_RFLAGS)(%rsp)
	jz     1f
	orw    $(RPC_SYSCALL_INFO_FEXCEPT), 0(%rsp)
1:

	movq   %rsp, %rdi
	EXTERN(syscall_trace)
	call   syscall_trace

	popq_cfi %rax /* flags (pop_void) */
	popq_cfi_r %rax /* SYSNO */
	popq_cfi_r %rdi /* ARG[0] */
	popq_cfi_r %rsi /* ARG[1] */
	popq_cfi_r %rdx /* ARG[2] */
	popq_cfi_r %r10 /* ARG[3] */
	popq_cfi_r %r8  /* ARG[4] */
	popq_cfi_r %r9  /* ARG[5] */
	popq_cfi_r %r11
	popq_cfi_r %rcx
	jmp    x86_syscall64x64_int80
END(x86_syscall64x64_int80_traced)

PUBLIC_FUNCTION(x86_syscall64x32_int80_traced)
	movzlq %eax, %rax
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

	pushq_cfi $(RPC_SYSCALL_INFO_FREGVALID(0) | RPC_SYSCALL_INFO_FREGVALID(1) | \
	            RPC_SYSCALL_INFO_FREGVALID(2) | RPC_SYSCALL_INFO_FREGVALID(3) | \
	            RPC_SYSCALL_INFO_FREGVALID(4) | RPC_SYSCALL_INFO_FREGVALID(5) | \
	            RPC_SYSCALL_INFO_METHOD_INT80H_32)
	/* Check if exceptions are enabled. */
	ttest  mask=EFLAGS_DF, loc=(96 + OFFSET_IRREGS_RFLAGS)(%rsp)
	jz     1f
	orw    $(RPC_SYSCALL_INFO_FEXCEPT), 0(%rsp)
1:
	movq   %rsp, %rdi
	EXTERN(syscall_trace)
	call   syscall_trace

	popq_cfi %rax /* flags (pop_void) */
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
	jmp    x86_syscall64x32_int80
END(x86_syscall64x32_int80_traced)
	.cfi_endproc
END(x86_syscall64_int80_after_swapgs_traced)
END(x86_idt_syscall_traced)
#endif /* !CONFIG_NO_KERNEL_SYSCALL_TRACING */













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
	ASM_CFI_OFFSET_RESTORE_ICPUSTATE(0)
	movq   %rdi, %rsp /* No need to disable interrupts, since this stack switch is atomic! */
	.cfi_def_cfa_register %rsp
	/* Restore user-space registers. (except for RAX) */
	ASM_POP_GPREGSNSP_NORAX_CFI_R

	/* Must account for IRET redirection when selecting compatibility mode!
	 * >> temp = IRET.CS;
	 * >> if unlikely(temp == SEGMENT_KERNEL_CODE)
	 * >>     temp = PERTASK_GET(this_x86_sysret_iret.ir_cs);
	 * >> if (temp == SEGMENT_USER_CODE32_RPL)
	 * >>     DO_X32();
	 * >> DO_X64(); */
	movw   (8 + OFFSET_IRREGS64_CS)(%rsp), %ax
	cmpw   $(SEGMENT_KERNEL_CODE), %ax
	.cfi_remember_state
	je     .Lsyscall_emulate_rpc_redirection_cs
1:	cmpw   $(SEGMENT_USER_CODE32_RPL), %ax
	popq_cfi_r %rax

	/* Define internal labels to allow for self-modifying code! */
	.byte  0x0f, 0x85 /* jne */
INTERN_OBJECT(x86_syscall_emulate_int80h_r_rel_x86_syscall64x64_int80)
	.reloc ., R_X86_64_PC32, x86_syscall64x64_int80 - 4
	.long  0
END(x86_syscall_emulate_int80h_r_rel_x86_syscall64x64_int80)

	.byte  0xe9 /* jmp */
INTERN_OBJECT(x86_syscall_emulate_int80h_r_rel_x86_syscall64x32_int80)
	.reloc ., R_X86_64_PC32, x86_syscall64x32_int80 - 4
	.long  0
END(x86_syscall_emulate_int80h_r_rel_x86_syscall64x32_int80)
.Lsyscall_emulate_rpc_redirection_cs:
	.cfi_restore_state
	movw   %gs:(this_x86_sysret_iret + OFFSET_IRREGS64_CS), %ax
	jmp    1b
	.cfi_endproc
END(x86_syscall_emulate_int80h_r)

.section .text
PUBLIC_FUNCTION(x86_syscall_emulate32_int80h_r)
	.cfi_startproc simple
	/* `struct icpustate *%rdi'
	 * NOTE: ENDOF(%rdi->IRREGS) is located at the end (top) of our kernel-stack! */
	.cfi_signal_frame
	.cfi_def_cfa %rdi, 0
	ASM_CFI_OFFSET_RESTORE_ICPUSTATE(0)
	movq   %rdi, %rsp /* No need to disable interrupts, since this stack switch is atomic! */
	.cfi_def_cfa_register %rsp
	/* Restore user-space registers. */
	ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R

	.byte  0xe9 /* jmp */
INTERN_OBJECT(x86_syscall_emulate32_int80h_r_rel_x86_syscall64x32_int80)
	.reloc ., R_X86_64_PC32, x86_syscall64x32_int80 - 4
	.long  0
END(x86_syscall_emulate32_int80h_r_rel_x86_syscall64x32_int80)
	.cfi_endproc
END(x86_syscall_emulate32_int80h_r)

.section .text
PUBLIC_FUNCTION(x86_syscall_emulate64_int80h_r)
	.cfi_startproc simple
	/* `struct icpustate *%rdi'
	 * NOTE: ENDOF(%rdi->IRREGS) is located at the end (top) of our kernel-stack! */
	.cfi_signal_frame
	.cfi_def_cfa %rdi, 0
	ASM_CFI_OFFSET_RESTORE_ICPUSTATE(0)
	movq   %rdi, %rsp /* No need to disable interrupts, since this stack switch is atomic! */
	.cfi_def_cfa_register %rsp
	/* Restore user-space registers. */
	ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R

	.byte  0xe9 /* jmp */
INTERN_OBJECT(x86_syscall_emulate64_int80h_r_rel_x86_syscall64x64_int80)
	.reloc ., R_X86_64_PC32, x86_syscall64x64_int80 - 4
	.long  0
END(x86_syscall_emulate64_int80h_r_rel_x86_syscall64x64_int80)
	.cfi_endproc
END(x86_syscall_emulate64_int80h_r)


.section .text.cold
INTERN_FUNCTION(__x86_asm64_syscall_break)
	/* For `int 80h' system calls:
	 *   Called when a system call number hasn't been assigned (%rax:sysno) */
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0

	/* Check IRET.EFLAGS.DF if an exception should be thrown */
	ttest  mask=EFLAGS_DF, loc=OFFSET_IRREGS_RFLAGS(%rsp)
	jnz    1f
	movq   $-ENOSYS, %rax
	intr_exit
1:
	/* Construct a `struct icpustate' */
	ASM_PUSH_ICPUSTATE_AFTER_HW_IRET_CFI_R

	/* Construct an on-stack `struct rpc_syscall_info' */
	pushP_cfi %Pdi
	pushP_cfi %Psi
	pushP_cfi %Pdx
	pushP_cfi %r10
	pushP_cfi %r8
	pushP_cfi %r9
	pushP_cfi %Pax
	pushP_cfi $(RPC_SYSCALL_INFO_METHOD_INT80H_64 | RPC_SYSCALL_INFO_FEXCEPT |  \
	            RPC_SYSCALL_INFO_FREGVALID(0) | RPC_SYSCALL_INFO_FREGVALID(1) | \
	            RPC_SYSCALL_INFO_FREGVALID(2) | RPC_SYSCALL_INFO_FREGVALID(3) | \
	            RPC_SYSCALL_INFO_FREGVALID(4) | RPC_SYSCALL_INFO_FREGVALID(5))

	/* Throw the `E_UNKNOWN_SYSTEMCALL' exception. */
	leaP   SIZEOF_RPC_SYSCALL_INFO(%Psp), %R_fcall0P
	movP   %Psp,                          %R_fcall1P
	EXTERN(userexcept_handler_nosys)
	call   userexcept_handler_nosys

	.cfi_endproc
END(__x86_asm64_syscall_break)

#ifndef __INTELLISENSE__
#include "syscall-int80h.S"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_INT80H_64_S */
