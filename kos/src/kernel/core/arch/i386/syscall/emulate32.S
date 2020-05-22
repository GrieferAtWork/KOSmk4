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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_EMULATE32_S
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_EMULATE32_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <kernel/except.h>

#include <asm/cfi.h>
#include <asm/instr/jccN.h>
#include <asm/unistd.h>
#include <kos/kernel/cpu-state-asm32.h>
#include <kos/kernel/cpu-state.h>

#include <errno.h>

#include <librpc/rpc.h>


#define TEST_DOUBLE_WIDE(sysno_reg, tempreg_l, tempreg_b, segment_prefix)  \
	cmpl   $(__NR_syscall0_max), sysno_reg;                                \
	ja     1234f;                                                          \
	movl   sysno_reg, tempreg_l;                                           \
	shrl   $(1), tempreg_l;                                                \
	EXTERN(kernel_syscall0_regcnt);                                        \
	movb   segment_prefix kernel_syscall0_regcnt(,tempreg_l,1), tempreg_b; \
	jmp    1235f;                                                          \
1234:                                                                      \
	leal   ((-__NR_syscall1_min) & 0xffffffff)(sysno_reg), tempreg_l;      \
	shrl   $(1), tempreg_l;                                                \
	EXTERN(kernel_syscall1_regcnt);                                        \
	movb   segment_prefix kernel_syscall1_regcnt(,tempreg_l,1), tempreg_b; \
1235:                                                                      \
	testl  $(1), sysno_reg;                                                \
	jz     1234f;                                                          \
	shrb   $(4), tempreg_b;                                                \
1234:                                                                      \
	testb  $(0x8), tempreg_b;


/* Emulate the execution of a system call.
 * NOTE: `syscall_emulate_r()' is the same as `syscall_emulate()', however
 *       will reset the kernel-space stack to `state', and immediately return
 *       to userspace after the system call has returned (or unwind any exception
 *       that was thrown by the system call, also dealing with the possibility
 *       of RPC function handling, as well as system call restarting) */

/* >> FUNDEF ATTR_NORETURN void FCALL
 * >> syscall_emulate_r(struct icpustate *__restrict state,
 * >>                   struct rpc_syscall_info *__restrict sc_info); */
.section .text
	.cfi_startproc simple
	EXTERN(syscall_emulate_r_personality)
	.cfi_personality 0, syscall_emulate_r_personality
	.cfi_iret_signal_frame
	.cfi_restore_iret_ds_or_offset -4
	.cfi_restore_iret_es_or_offset -8
	.cfi_restore_iret_fs_or_offset -12
	ASM_CFI_REL_OFFSET_RESTORE_GPREGSNSP(OFFSET_ICPUSTATE_GPREGS)
INTERN_FUNCTION(x86_syscall_emulate_traced_r)
	.cfi_def_cfa %esp, (SIZEOF_RPC_SYSCALL_INFO + OFFSET_ICPUSTATE_IRREGS)
	rep;   movsl
	movl   %esp, %ecx
	EXTERN(syscall_trace)
	call   syscall_trace
	jmp8   .Lsyscall_emulate_r_after_tracing
END(x86_syscall_emulate_traced_r)

PUBLIC_FUNCTION(syscall_emulate_r)
	.cfi_def_cfa %ecx, OFFSET_ICPUSTATE_IRREGS
	/* Start by copying `sc_info' (%edx) just infront of `state' (%ecx)
	 * Note that that sc_info may already be overlapping with said target
	 * area, meaning that we have to use memmove() semantics copying data
	 * from the top down to the bottom */
	leal   -4(%ecx), %edi
	leal   -SIZEOF_RPC_SYSCALL_INFO(%ecx), %esp /* Load %esp to point to the start of the copied `sc_info' */
	.cfi_def_cfa %esp, (SIZEOF_RPC_SYSCALL_INFO + OFFSET_ICPUSTATE_IRREGS)
	leal   (SIZEOF_RPC_SYSCALL_INFO-4)(%edx), %esi
	movl   $(SIZEOF_RPC_SYSCALL_INFO / 4), %ecx /* It's ok that this clobbers %ecx. - We can just load `%edi+4' once we're done */
	std    /* Set the direction bit, meaning that movsX now advances downwards */

	/* memmove((byte_t *)state - SIZEOF_RPC_SYSCALL_INFO, sc_info, SIZEOF_RPC_SYSCALL_INFO); */
INTERN_OBJECT(x86_syscall_emulate_r_redirection)
	/* When system calls are being traced, this `rep; movsl' is re-written as
	 * `jmp8 x86_syscall_emulate_traced_r'. Note that in this case, the entry
	 * point of `x86_syscall_emulate_traced_r' will do the missed `rep; movsl'
	 * before performing tracing and returning to `.Lsyscall_emulate_r_after_tracing' */
	.byte  0xf3 /* rep */
	.byte  0xa5 /* movsl */
.if (. - x86_syscall_emulate_traced_r) > 0x7f
.error "Offset to `x86_syscall_emulate_traced_r' would be large"
.endif
	/* NOTE: `x86_syscall_emulate_r_redirection_jmp' are the little-endian 2-bytes for an instruction:
	 *       `jmp8 x86_syscall_emulate_traced_r' */
INTERN_CONST(x86_syscall_emulate_r_redirection_jmp, 0xeb | (((x86_syscall_emulate_traced_r - .) & 0xff) << 8))
END(x86_syscall_emulate_r_redirection)
.Lsyscall_emulate_r_after_tracing:


	/* At this point, our stack looks like this:
	 * %edi = %esp - 4
	 * 0(%esp):                                                 struct rpc_syscall_info sc_info;
	 * SIZEOF_RPC_SYSCALL_INFO(%esp):                           struct icpustate state;
	 * SIZEOF_RPC_SYSCALL_INFO + OFFSET_ICPUSTATE_IRREGS(%esp): <END-OF-STACK> */


INTERN_LABEL(__x86_syscall_emulate_r_protect_start):
	/* Figure out which system call is actually being invoked. */
	movl   (4 + OFFSET_RPC_SYSCALL_INFO_SYSNO)(%edi), %eax
	.cfi_def_cfa %edi, (4 + SIZEOF_RPC_SYSCALL_INFO + OFFSET_ICPUSTATE_IRREGS)

	/* Push system call arguments. */
	pushl  (4 + OFFSET_RPC_SYSCALL_INFO_REG(5))(%edi)
	pushl  (4 + OFFSET_RPC_SYSCALL_INFO_REG(4))(%edi)
	pushl  (4 + OFFSET_RPC_SYSCALL_INFO_REG(3))(%edi)
	pushl  (4 + OFFSET_RPC_SYSCALL_INFO_REG(2))(%edi)
	pushl  (4 + OFFSET_RPC_SYSCALL_INFO_REG(1))(%edi)
	pushl  (4 + OFFSET_RPC_SYSCALL_INFO_REG(0))(%edi)

	cmpl   $(__NR_syscall0_max), %eax
	ja     .Lcall_sysex
	pushl  $.Lnormal_return
	EXTERN(x86_sysroute0_c)
	jmpl   *x86_sysroute0_c(,%eax,4)
.Lbad_sysno:
	/* %eax is a system call number that doesn't exist. */
	testl  $(RPC_SYSCALL_INFO_FEXCEPT), (4 + OFFSET_RPC_SYSCALL_INFO_FLAGS)(%edi)
	jz     .Lbad_sysno_ENOSYS

	/* Throw an actual `E_UNKNOWN_SYSTEMCALL' exception! */
	pushl  %eax                                      /* sysno */
	pushl  (4 + OFFSET_RPC_SYSCALL_INFO_FLAGS)(%edi) /* flags */
	pushl  $(8)                                      /* argc */
	pushl  $(ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL))     /* ecode */
	call   error_thrown

.Lbad_sysno_ENOSYS:
	/* Just return -ENOSYS (no need to go through all the hassle of throwing an exception) */
	movl   $-ENOSYS, %eax
	movl   $-1, %edx
	jmp    .Lnormal_return

.Lcall_sysex:
	cmpl   $(__NR_syscall1_min), %eax
	jb     .Lbad_sysno
	cmpl   $(__NR_syscall1_max), %eax
	ja     .Lbad_sysno
	EXTERN(x86_sysroute1_c)
	calll  *(x86_sysroute1_c - ((__NR_syscall1_min * 4) & 0xffffffff))(,%eax,4)
.Lnormal_return:


INTERN_LABEL(__x86_syscall_emulate_r_protect_end):
	/* Return to user-space. */
	addl   $(24 + SIZEOF_RPC_SYSCALL_INFO), %esp
	.cfi_def_cfa %esp, OFFSET_ICPUSTATE_IRREGS

	/* Check if we must sign-extend the error return value. */
	TEST_DOUBLE_WIDE(%eax, %ecx, %cl, )
	jz     1f
	movl   %edx, (OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDX)(%esp)
1:
	/* Restore GP registers (except for %eax, which holds the syscall return value) */
	popl_cfi_r %edi   /* [P] Destination pointer */
	popl_cfi_r %esi   /* [P] Source pointer */
	popl_cfi_r %ebp   /* [P] Frame base pointer */
	popl_cfi   %ecx   /* [P] Stack pointer (skip) */
	popl_cfi_r %ebx   /* [P] Base register */
	popl_cfi_r %edx   /* [C] Data register */
	popl_cfi_r %ecx   /* [C] Count register */
	addl   $(4), %esp /* [C] Accumulator register */
	.cfi_adjust_cfa_offset -4

	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(syscall_emulate_r)

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_EMULATE32_S */
