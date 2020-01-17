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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_EMULATE64_S
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_EMULATE64_S 1

#include <kernel/compiler.h>

#include <kernel/except.h>

#include <asm/cfi.h>
#include <asm/instr/interrupt.h>
#include <asm/instr/jccN.h>
#include <asm/syscalls32_d.h>
#include <asm/syscalls64_d.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/gdt.h>

#include <errno.h>

#include <librpc/rpc.h>

#define TEST_DOUBLE_WIDE32(sysno_reg_b, sysno_reg_l, sysno_reg_q,            \
                           tempreg_b, tempreg_l, tempreg_q, segment_prefix)  \
	cmpl   $(__NR32_syscall0_max), sysno_reg_l;                              \
	ja     1234f;                                                            \
	movq   sysno_reg_q, tempreg_q;                                           \
	shrq   $(1), tempreg_q;                                                  \
	EXTERN(kernel_syscall0_regcnt32);                                        \
	movb   segment_prefix kernel_syscall0_regcnt32(,tempreg_q,1), tempreg_b; \
	jmp    1235f;                                                            \
1234:                                                                        \
	leal   ((-__NR32_syscall1_min) & 0xffffffff)(sysno_reg_l), tempreg_l;    \
	shrl   $(1), tempreg_l;                                                  \
	movzlq tempreg_l, tempreg_q;                                             \
	EXTERN(kernel_syscall1_regcnt32);                                        \
	movb   segment_prefix kernel_syscall1_regcnt32(,tempreg_q,1), tempreg_b; \
1235:                                                                        \
	testb  $(1), sysno_reg_b;                                                \
	jz     1234f;                                                            \
	shrb   $(4), tempreg_b;                                                  \
1234:                                                                        \
	testb  $(0x8), tempreg_b;


/* Emulate the execution of a system call.
 * NOTE: `syscall_emulate_r()' is the same as `syscall_emulate()', however
 *       will reset the kernel-space stack to `state', and immediately return
 *       to userspace after the system call has returned (or unwind any exception
 *       that was thrown by the system call, also dealing with the possibility
 *       of RPC function handling, as well as system call restarting) */


/* FUNDEF ATTR_NORETURN void FCALL
 * syscall_emulate_r(struct icpustate *__restrict state,
 *                   struct rpc_syscall_info *__restrict sc_info); */
.section .text
	.cfi_startproc simple
	EXTERN(syscall_emulate_r_personality)
	.cfi_personality 0, syscall_emulate_r_personality
	.cfi_signal_frame
	ASM_CFI_REL_OFFSET_RESTORE_ICPUSTATE(0)
INTERN_FUNCTION(x86_syscall_emulate_traced_r)
	.cfi_def_cfa %rsp, (SIZEOF_RPC_SYSCALL_INFO + OFFSET_ICPUSTATE_IRREGS)
	rep;   movsq
	movq   %rsp, %rdi
	EXTERN(syscall_trace)
	call   syscall_trace
	jmp8   .Lsyscall_emulate_r_after_tracing
END(x86_syscall_emulate_traced_r)

PUBLIC_FUNCTION(syscall_emulate_r)
	.cfi_def_cfa %rdi, OFFSET_ICPUSTATE_IRREGS
	/* Start by copying `sc_info' (%rsi) just infront of `state' (%rdi)
	 * Note that that sc_info may already be overlapping with said target
	 * area, meaning that we have to use memmove() semantics copying data
	 * from the top down to the bottom */
	leaq   -SIZEOF_RPC_SYSCALL_INFO(%rdi), %rsp /* Load %rsp to point to the start of the copied `sc_info' */
	movq   %rsp, %rbx
	.cfi_def_cfa %rsp, (SIZEOF_RPC_SYSCALL_INFO + OFFSET_ICPUSTATE_IRREGS)
	subq   $(8), %rdi
	addq   $(SIZEOF_RPC_SYSCALL_INFO - 8), %rsi
	movq   $(SIZEOF_RPC_SYSCALL_INFO / 8), %rcx /* It's ok that this clobbers %rcx. - We can just load `%edi+4' once we're done */
	std    /* Set the direction bit, meaning that movsX now advances downwards */

	/* memmove((byte_t *)state - SIZEOF_RPC_SYSCALL_INFO, sc_info, SIZEOF_RPC_SYSCALL_INFO); */
INTERN_OBJECT(x86_syscall_emulate_r_redirection)
	/* When system calls are being traced, this `rep; movsq' is re-written as
	 * `jmp8 x86_syscall_emulate_traced_r'. Note that in this case, the entry
	 * point of `x86_syscall_emulate_traced_r' will do the missed `rep; movsq'
	 * before performing tracing and returning to `.Lsyscall_emulate_r_after_tracing' */
	.byte  0xf3 /* rep */
	.byte  0x48 /* REX.W */
.if (. - x86_syscall_emulate_traced_r) > 0x7f
.error "Offset to `x86_syscall_emulate_traced_r' would be large"
.endif
	/* NOTE: `x86_syscall_emulate_r_redirection_jmp' are the little-enable 2-bytes for an instruction:
	 *       `jmp8 x86_syscall_emulate_traced_r' */
INTERN_CONST(x86_syscall_emulate_r_redirection_jmp, 0xeb | (((x86_syscall_emulate_traced_r - .) & 0xff) << 8))
END(x86_syscall_emulate_r_redirection)
	.byte  0xa5 /* `movsq' (actually `movsl', but part of the same instruction as the REX.W above, making it `movsq') */
.Lsyscall_emulate_r_after_tracing:

	/* At this point, our stack looks like this:
	 * %rbx = %rsp
	 * 0(%rsp):                                                 struct rpc_syscall_info sc_info;
	 * SIZEOF_RPC_SYSCALL_INFO(%rsp):                           struct icpustate state;
	 * SIZEOF_RPC_SYSCALL_INFO + OFFSET_ICPUSTATE_IRREGS(%rsp): <END-OF-STACK> */

	/* Check if this a 32-bit or 64-bit system call. */
	movw   (SIZEOF_RPC_SYSCALL_INFO + OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_CS)(%rbx), %ax
	cmpw   $(SEGMENT_USER_CODE64_RPL), %ax
	jne    .Lsyscall_emulate_not_direct_64

INTERN_LABEL(__x86_syscall_emulate_r_protect_start):
	/* 64-bit system call */
.Lsyscall_emulate64_r:
	/* Figure out which system call is actually being invoked. */
	movq   OFFSET_RPC_SYSCALL_INFO_SYSNO(%rbx), %rax
	/* Load system call arguments (from `sc_info') */
	movq   (OFFSET_RPC_SYSCALL_INFO_REG(0))(%rbx), %rdi
	movq   (OFFSET_RPC_SYSCALL_INFO_REG(1))(%rbx), %rsi
	movq   (OFFSET_RPC_SYSCALL_INFO_REG(2))(%rbx), %rdx
	movq   (OFFSET_RPC_SYSCALL_INFO_REG(3))(%rbx), %rcx
	movq   (OFFSET_RPC_SYSCALL_INFO_REG(4))(%rbx), %r8
	movq   (OFFSET_RPC_SYSCALL_INFO_REG(5))(%rbx), %r9

	cmpq   $(__NR64_syscall0_max), %rax
	ja     .Lcall_sysex64
	pushq_cfi $.Lnormal_return64
	EXTERN(x86_sysroute0_c)
	jmpq   *x86_sysroute0_c(,%rax,8)
	.cfi_adjust_cfa_offset -8
.Lbad_sysno64:
	/* %rax is a system call number that doesn't exist. */
	testq  $(RPC_SYSCALL_INFO_FEXCEPT), OFFSET_RPC_SYSCALL_INFO_FLAGS(%rbx)
	jz     .Lbad_sysno64_ENOSYS

.Lthrow_unknown_systemcall:
	/* Throw an actual `E_UNKNOWN_SYSTEMCALL' exception! */
	pushq_cfi %r9                                      /* ARGS[5] */
	pushq_cfi %r8                                      /* ARGS[4] */
	pushq_cfi %r10                                     /* ARGS[3] */
	pushq_cfi %rdx                                     /* ARGS[2] */
	movq   %rsi, %r9                                   /* ARGS[1] */
	movq   %rdi, %r8                                   /* ARGS[0] */
	movq   %rax, %rcx                                  /* sysno */
	movq   OFFSET_RPC_SYSCALL_INFO_FLAGS(%rbx), %rdx   /* flags */
	movq   $(8), %rsi                                  /* argc */
	movq   $(ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* ecode */
	call   error_thrown
	.cfi_adjust_cfa_offset -32

.Lbad_sysno64_ENOSYS:
	/* Just return -ENOSYS (no need to go through all the hassle of throwing an exception) */
	movq   $-ENOSYS, %rax
/*	movq   $-1, %rdx * There are no 128-bit system calls, so no need */
	jmp    .Lnormal_return64

.Lcall_sysex64:
	cmpq   $(__NR64_syscall1_max), %rax
	ja     .Lbad_sysno64
	subq   $(__NR64_syscall1_min), %rax
	jb     .Lbad_sysno64
	EXTERN(x86_sysroute1_c)
	callq  *x86_sysroute1_c(,%rax,8)
.Lnormal_return64:
	.cfi_remember_state
	/* Return to user-space. */
	addq   $(SIZEOF_RPC_SYSCALL_INFO), %rsp
	.cfi_adjust_cfa_offset -SIZEOF_RPC_SYSCALL_INFO
	ASM_POP_GPREGSNSP_NORAX_CFI_R
	addq   $(8), %rsp /* [C] Accumulator register */
	.cfi_adjust_cfa_offset -8
	intr_exit
	.cfi_restore_state

.Lsyscall_emulate_not_direct_64:
	cmpw   $(SEGMENT_USER_CODE32_RPL), %ax
	je     .Lsyscall_emulate32_r
#ifndef NDEBUG
	cmpw   $(SEGMENT_KERNEL_CODE), %ax
	je     1f
	int3   /* ASSERTION FAILED: Invalid %cs value: <%ax> */
1:
#endif /* !NDEBUG */
	/* Load the actual CS value from `this_x86_rpc_redirection_iret' */
	movw   %gs:(this_x86_rpc_redirection_iret + OFFSET_IRREGS_CS), %ax
	cmpw   $(SEGMENT_USER_CODE64_RPL), %ax
	je     .Lsyscall_emulate64_r
#ifndef NDEBUG
	cmpw   $(SEGMENT_USER_CODE32_RPL), %ax
	je     1f
	int3   /* ASSERTION FAILED: Invalid %cs value: <%ax> */
1:
#endif /* !NDEBUG */

.Lsyscall_emulate32_r:
	/* Figure out which system call is actually being invoked. */
	movzlq OFFSET_RPC_SYSCALL_INFO_SYSNO(%rbx), %rax

	/* Load the system call argument vector (from `sc_info') */
	leaq   (OFFSET_RPC_SYSCALL_INFO_REG(0))(%rbx), %rdi

	cmpl   $(__NR32_syscall0_max), %eax
	ja     .Lcall_sysex32
	pushq_cfi $.Lnormal_return32
	EXTERN(x86_sysroute0_runc32)
	jmpq   *x86_sysroute0_runc32(,%rax,8)
	.cfi_adjust_cfa_offset -8
.Lbad_sysno32:
	/* %rax is a system call number that doesn't exist. */
	testq  $(RPC_SYSCALL_INFO_FEXCEPT), OFFSET_RPC_SYSCALL_INFO_FLAGS(%rbx)
	jnz    .Lthrow_unknown_systemcall /* Throw an actual `E_UNKNOWN_SYSTEMCALL' exception! */
	/* Just return -ENOSYS (no need to go through all the hassle of throwing an exception) */
	movq   $-ENOSYS, %rax
	movq   $-1, %rdx
	jmp    .Lnormal_return32

.Lcall_sysex32:
	cmpl   $(__NR32_syscall1_max), %eax
	ja     .Lbad_sysno32
	subl   $(__NR32_syscall1_min), %eax
	jb     .Lbad_sysno32
	EXTERN(x86_sysroute1_runc32)
	callq  *x86_sysroute1_runc32(,%rax,8)
.Lnormal_return32:


INTERN_LABEL(__x86_syscall_emulate_r_protect_end):
	/* Return to user-space. */
	addq   $(SIZEOF_RPC_SYSCALL_INFO), %rsp
	.cfi_adjust_cfa_offset -SIZEOF_RPC_SYSCALL_INFO

	/* Check if we must sign-extend the error return value. */
	TEST_DOUBLE_WIDE32(%al, %eax, %rax, %cl, %ecx, %rcx, )
	jz     1f
	/* Store the upper 32 bit of the return value in %rdx */
	movq   %rax, %rdx
	shrq   $(32), %rdx
	movq   %rdx, (OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGS_RDX)(%rsp)
1:
	/* Restore GP registers (except for %eax, which holds the syscall return value) */
	ASM_POP_GPREGSNSP_NORAX_CFI_R
	addq   $(8), %rsp /* [C] Accumulator register */
	.cfi_adjust_cfa_offset -8
	intr_exit
	.cfi_endproc
END(syscall_emulate_r)

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_EMULATE64_S */
