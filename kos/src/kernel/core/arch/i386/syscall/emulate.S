/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_EMULATE_S
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_EMULATE_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <kernel/except.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <cfi.h>
#include <asm/instr/compat.h>
#include <asm/instr/interrupt.h>
#include <asm/instr/jccN.h>
#include <asm/instr/ttest.h>
#include <asm/syscalls32_d.h>
#include <asm/unistd.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/bits/cpu-state-asm32.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/x86/gdt.h>
#include <kos/rpc.h>

#include <errno.h>

#ifdef __x86_64__
#include <asm/syscalls64_d.h>
#endif /* __x86_64__ */

#ifdef __x86_64__
#define IF_X86_64(...) __VA_ARGS__
#else /* __x86_64__ */
#define IF_X86_64(...) /* nothing */
#endif /* !__x86_64__ */

#ifndef __x86_64__
#define kernel_syscall0_regcnt32 kernel_syscall0_regcnt
#define kernel_syscall1_regcnt32 kernel_syscall1_regcnt
#endif /* !__x86_64__ */

#ifndef SIZEOF_POINTER
#define SIZEOF_POINTER __SIZEOF_POINTER__
#endif /* !SIZEOF_POINTER */
#define Pn(n) (SIZEOF_POINTER * (n))


#define TEST_DOUBLE_WIDE32(sysno_reg_b, sysno_reg_l, sysno_reg_P,            \
                           tempreg_b, tempreg_l, tempreg_P, segment_prefix)  \
	cmpl   $(__NR32_syscall0_max), sysno_reg_l;                              \
	ja     1234f;                                                            \
	movP   sysno_reg_P, tempreg_P;                                           \
	shrP   $(1), tempreg_P;                                                  \
	EXTERN(kernel_syscall0_regcnt32);                                        \
	movb   segment_prefix kernel_syscall0_regcnt32(,tempreg_P,1), tempreg_b; \
	jmp    1235f;                                                            \
1234:                                                                        \
	leal   ((-__NR32_syscall1_min) & 0xffffffff)(sysno_reg_l), tempreg_l;    \
	shrl   $(1), tempreg_l;                                                  \
	IF_X86_64(movzlq tempreg_l, tempreg_P;)                                  \
	EXTERN(kernel_syscall1_regcnt32);                                        \
	movb   segment_prefix kernel_syscall1_regcnt32(,tempreg_P,1), tempreg_b; \
1235:                                                                        \
	testb  $(1), sysno_reg_b;                                                \
	jz     1234f;                                                            \
	shrb   $(4), tempreg_b;                                                  \
1234:                                                                        \
	testb  $(0x8), tempreg_b;


/* Emulate the execution of a system call.
 * NOTE: `syscall_emulate_r()'   is  the  same  as  `syscall_emulate()',  however
 *       will  reset the  kernel-space stack  to `state',  and immediately return
 *       to userspace after the system call has returned (or unwind any exception
 *       that  was thrown by  the system call, also  dealing with the possibility
 *       of RPC function handling, as well as system call restarting) */

/* >> FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1)) void
 * >> NOTHROW(FCALL syscall_emulate_r)(struct icpustate *__restrict state,
 * >>                                  struct rpc_syscall_info *__restrict sc_info); */
.section .text
	.cfi_startproc simple
	EXTERN(syscall_emulate_r_personality)
	.cfi_personality 0, syscall_emulate_r_personality
	.cfi_signal_frame
	ASM_CFI_OFFSET_RESTORE_ICPUSTATE(-OFFSET_ICPUSTATE_IRREGS)
INTERN_FUNCTION(x86_syscall_emulate_traced_r)
	.cfi_def_cfa %Pdi, (SIZEOF_POINTER + SIZEOF_RPC_SYSCALL_INFO + OFFSET_ICPUSTATE_IRREGS)
	leaP   SIZEOF_POINTER(%Pdi), %Psp /* Unwind the stack */
	.cfi_def_cfa %Psp, (SIZEOF_RPC_SYSCALL_INFO + OFFSET_ICPUSTATE_IRREGS)
	movP   %Psp, %R_fcall0P
	EXTERN(syscall_trace)
	call   syscall_trace
	jmp8   .Lsyscall_emulate_r_after_tracing
END(x86_syscall_emulate_traced_r)

PUBLIC_FUNCTION(syscall_emulate_r)
	.cfi_def_cfa %R_fcall0P, OFFSET_ICPUSTATE_IRREGS

	/* Start by copying `sc_info' (%R_fcall1P) just infront of `state' (%R_fcall0P)
	 * Note  that that  sc_info may already  be overlapping with  said target area,
	 * meaning that we have to use memmoveup() semantics copying data from the  top
	 * down to the bottom */

#ifdef __x86_64__
	subP   $(SIZEOF_POINTER),                           %Pdi /* Because %R_fcall0P <=> %Pdi */
	.cfi_adjust_cfa_offset SIZEOF_POINTER
	addP   $(SIZEOF_RPC_SYSCALL_INFO - SIZEOF_POINTER), %Psi /* Because %R_fcall1P <=> %Psi */
#else /* __x86_64__ */
	leaP   -SIZEOF_POINTER(%R_fcall0P),                            %Pdi
	leaP   (SIZEOF_RPC_SYSCALL_INFO - SIZEOF_POINTER)(%R_fcall1P), %Psi
#endif /* !__x86_64__ */
	std    /* Set the direction bit, meaning that movsX now advances downwards */
	/* Copy the syscall info structure */
.rept SIZEOF_RPC_SYSCALL_INFO / SIZEOF_POINTER
	movsP
#ifdef __x86_64__
	.cfi_adjust_cfa_offset SIZEOF_POINTER /* Because movsP modifies %R_fcall0P <=> %Pdi, which is our CFA register */
#endif /* __x86_64__ */
.endr
	/* When system  calls  are  being  traced, this  `rep; movsP'  is  re-written  as
	 * `jmp8 x86_syscall_emulate_traced_r'.   Note  that  in  this  case,  the  entry
	 * point  of  `x86_syscall_emulate_traced_r'  will  do  the  missed  `rep; movsP'
	 * before performing tracing and returning to `.Lsyscall_emulate_r_after_tracing' */

	/* Unwind the stack */
	/* leaP   SIZEOF_POINTER(%Pdi), %Psp */
INTERN_OBJECT(x86_syscall_emulate_r_redirection)
#ifdef __x86_64__
	.byte 0x48 /* REX.W */
	.byte 0x8d /* leaq */
INTERN_CONST(x86_syscall_emulate_r_redirection_inl, 0x48 | (0x8d << 8))
#else /* __x86_64__ */
	.byte 0x8d  /* leal */
	.byte 0x67  /* modrm: [disp8 + %edi], %esp */
INTERN_CONST(x86_syscall_emulate_r_redirection_inl, 0x8d | (0x67 << 8))
#endif /* !__x86_64__ */
.if (. - x86_syscall_emulate_traced_r) > 0x7f
.error "Offset to `x86_syscall_emulate_traced_r' would be large"
.endif
	/* NOTE: `x86_syscall_emulate_r_redirection_jmp' are the little-endian 2-bytes for an instruction:
	 *       `jmp8 x86_syscall_emulate_traced_r' when  placed at  `x86_syscall_emulate_r_redirection'. */
INTERN_CONST(x86_syscall_emulate_r_redirection_jmp, 0xeb | (((x86_syscall_emulate_traced_r - .) & 0xff) << 8))
END(x86_syscall_emulate_r_redirection)
#ifdef __x86_64__
	.byte 0x67 /* modrm: [disp8 + %edi], %esp */
	.byte 0x08 /* disp8 */
#else /* __x86_64__ */
	.byte SIZEOF_POINTER /* disp8 */
#endif /* !__x86_64__ */
	.cfi_def_cfa %Psp, (SIZEOF_RPC_SYSCALL_INFO + OFFSET_ICPUSTATE_IRREGS)
.Lsyscall_emulate_r_after_tracing:

	/* At this point, our stack looks like this:
	 * >> 0(%Psp):                                                 struct rpc_syscall_info sc_info;
	 * >> SIZEOF_RPC_SYSCALL_INFO(%Psp):                           struct icpustate state;
	 * >> SIZEOF_RPC_SYSCALL_INFO + OFFSET_ICPUSTATE_IRREGS(%Psp): <END-OF-STACK> */

#ifdef __x86_64__
	/* Needed for unwinding: A pointer to `sc_info' (s.a. `syscall_emulate_r_personality()') */
	movP   %Psp, %Pbx
#endif /* __x86_64__ */

#ifdef __x86_64__
	/* Check if this a 32-bit or 64-bit system call. */
	movw   (SIZEOF_RPC_SYSCALL_INFO + OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_CS)(%Psp), %ax
	cmpw   $(SEGMENT_USER_CODE64_RPL), %ax
	jne    .Lsyscall_emulate_not_direct_64
#endif /* __x86_64__ */


INTERN_LABEL(__x86_syscall_emulate_r_protect_start):
	/* Native (x86-64: 64, i386: 32)-bit system call */
.Lsyscall_emulate_r:
	/* Figure out which system call is actually being invoked. */
	movP   OFFSET_RPC_SYSCALL_INFO_SYSNO(%Psp), %Pax

	/* Load system call arguments (from `sc_info') */
#ifdef __x86_64__
	movP   (OFFSET_RPC_SYSCALL_INFO_REG(0))(%Psp), %R_sysvabi0P
	movP   (OFFSET_RPC_SYSCALL_INFO_REG(1))(%Psp), %R_sysvabi1P
	movP   (OFFSET_RPC_SYSCALL_INFO_REG(2))(%Psp), %R_sysvabi2P
	movP   (OFFSET_RPC_SYSCALL_INFO_REG(3))(%Psp), %R_sysvabi3P
	movP   (OFFSET_RPC_SYSCALL_INFO_REG(4))(%Psp), %R_sysvabi4P
	movP   (OFFSET_RPC_SYSCALL_INFO_REG(5))(%Psp), %R_sysvabi5P
#define SYSCALL_ARGUMENT_SP_OFFSET 0
#else /* __x86_64__ */
	pushP_cfi (Pn(0) + OFFSET_RPC_SYSCALL_INFO_REG(5))(%Psp)
	pushP_cfi (Pn(1) + OFFSET_RPC_SYSCALL_INFO_REG(4))(%Psp)
	pushP_cfi (Pn(2) + OFFSET_RPC_SYSCALL_INFO_REG(3))(%Psp)
	pushP_cfi (Pn(3) + OFFSET_RPC_SYSCALL_INFO_REG(2))(%Psp)
	pushP_cfi (Pn(4) + OFFSET_RPC_SYSCALL_INFO_REG(1))(%Psp)
	pushP_cfi (Pn(5) + OFFSET_RPC_SYSCALL_INFO_REG(0))(%Psp)
#define SYSCALL_ARGUMENT_SP_OFFSET Pn(6)
#endif /* __x86_64__ */

	cmpP   $(__NR_syscall0_max), %Pax
	ja     .Lcall_sysex
	pushP_cfi $.Lnormal_return
	EXTERN(x86_sysroute0_c)
	jmpP   *x86_sysroute0_c(,%Pax,SIZEOF_POINTER)
	.cfi_adjust_cfa_offset -Pn(1)

.Lbad_sysno:
	/* %Pax is a system call number that doesn't exist. */
	ttest  mask=RPC_SYSCALL_INFO_FEXCEPT, loc=(SYSCALL_ARGUMENT_SP_OFFSET + OFFSET_RPC_SYSCALL_INFO_FLAGS)(%Psp)
	jz     .Lbad_sysno_ENOSYS

.Lthrow_unknown_systemcall:
	/* Throw an actual `E_UNKNOWN_SYSTEMCALL' exception! */
#ifdef __x86_64__
	pushP_cfi %r9                                              /* ARGS[5] */
	pushP_cfi %r8                                              /* ARGS[4] */
	pushP_cfi %r10                                             /* ARGS[3] */
	pushP_cfi %rdx                                             /* ARGS[2] */
	movq   %rsi, %r9                                           /* ARGS[1] */
	movq   %rdi, %r8                                           /* ARGS[0] */
	movq   %rax, %rcx                                          /* sysno */
	movq   (Pn(4) + OFFSET_RPC_SYSCALL_INFO_FLAGS)(%Psp), %rdx /* flags */
	movq   $(8), %rsi                                          /* argc */
	movq   $(EXCEPT_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi        /* ecode */
#else /* __x86_64__ */
	pushP_cfi %eax                                          /* sysno */
	pushP_cfi (Pn(7) + OFFSET_RPC_SYSCALL_INFO_FLAGS)(%Psp) /* flags */
	pushP_cfi $(8)                                          /* argc */
	pushP_cfi $(EXCEPT_CODEOF(E_UNKNOWN_SYSTEMCALL))        /* ecode */
#endif /* !__x86_64__ */
	call   except_thrown
	.cfi_adjust_cfa_offset -Pn(4)

.Lbad_sysno_ENOSYS:
	/* Just return -ENOSYS (no need to go through all the hassle of throwing an exception) */
	movP   $-ENOSYS, %Pax
#ifndef __x86_64__ /* There are no 128-bit system calls, so no need */
	movP   $-1, %Pdx
#endif /* !__x86_64__ */
	jmp    .Lnormal_return

.Lcall_sysex:
	cmpP   $(__NR_syscall1_max), %Pax
	ja     .Lbad_sysno
#ifdef __x86_64__
	subP   $(__NR_syscall1_min), %Pax
#else /* __x86_64__ */
	cmpP   $(__NR_syscall1_min), %Pax
#endif /* !__x86_64__ */
	jb     .Lbad_sysno
	EXTERN(x86_sysroute1_c)
#ifdef __x86_64__
	callP  *x86_sysroute1_c(,%Pax,SIZEOF_POINTER)
#else /* __x86_64__ */
	callP  *(x86_sysroute1_c - (Pn(__NR_syscall1_min) & 0xffffffff))(,%Pax,SIZEOF_POINTER)
#endif /* !__x86_64__ */
.Lnormal_return:

#ifndef __x86_64__
INTERN_LABEL(__x86_syscall_emulate_r_protect_end):
#endif /* !__x86_64__ */

#ifdef __x86_64__
	.cfi_remember_state
#endif /* __x86_64__ */

	/* Return to user-space. */
#ifdef __x86_64__
#define SYSCALL_ARGUMENT_SP_OFFSET 0
#else /* __x86_64__ */
#define SYSCALL_ARGUMENT_SP_OFFSET Pn(6)
#endif /* !__x86_64__ */
	addP   $(SYSCALL_ARGUMENT_SP_OFFSET + SIZEOF_RPC_SYSCALL_INFO), %Psp
	.cfi_adjust_cfa_offset -(SYSCALL_ARGUMENT_SP_OFFSET + SIZEOF_RPC_SYSCALL_INFO)
#undef SYSCALL_ARGUMENT_SP_OFFSET

	/* Check if we must sign-extend the error return value. */
#ifndef __x86_64__
	TEST_DOUBLE_WIDE32(%al, %eax, %Pax, %cl, %ecx, %Pcx, )
	jz     1f
	movP   %Pdx, (OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_PDX)(%Psp)
1:
#endif /* !__x86_64__ */

	/* Restore GP registers (except for %eax, which holds the syscall return value) */
#ifdef __x86_64__
	ASM_POP_GPREGSNSP_NORAX_CFI_R
#else /* __x86_64__ */
	popP_cfi_r %Pdi       /* [P] Destination pointer */
	popP_cfi_r %Psi       /* [P] Source pointer */
	popP_cfi_r %Pbp       /* [P] Frame base pointer */
	popP_cfi   %Pcx       /* [P] Stack pointer (skip) */
	popP_cfi_r %Pbx       /* [P] Base register */
	popP_cfi_r %Pdx       /* [C] Data register */
	popP_cfi_r %Pcx       /* [C] Count register */
#endif /* !__x86_64__ */

	addP   $(Pn(1)), %Psp /* [C] Accumulator register */
	.cfi_adjust_cfa_offset -Pn(1)

#ifdef __x86_64__
	intr_exit
#else /* __x86_64__ */
	popP_cfi %fs
	.cfi_restore_iret_fs
	popP_cfi %es
	.cfi_restore_iret_es
	popP_cfi %ds
	.cfi_restore_iret_ds
	iret
#endif /* !__x86_64__ */

#ifdef __x86_64__
	/* Support for 32-bit system calls */
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

	/* Load the actual CS value from `this_x86_sysret_iret' */
	EXTERN(this_x86_sysret_iret)
	movw   %segtls:(this_x86_sysret_iret + OFFSET_IRREGS_CS), %ax
	cmpw   $(SEGMENT_USER_CODE64_RPL), %ax
	je     .Lsyscall_emulate_r
#ifndef NDEBUG
	cmpw   $(SEGMENT_USER_CODE32_RPL), %ax
	je     1f
	int3   /* ASSERTION FAILED: Invalid %cs value: <%ax> */
1:
#endif /* !NDEBUG */

.Lsyscall_emulate32_r:
	/* Figure out which system call is actually being invoked. */
	movzlP OFFSET_RPC_SYSCALL_INFO_SYSNO(%Psp), %Pax

	/* Load the system call argument vector (from `sc_info') */
	leaP   (OFFSET_RPC_SYSCALL_INFO_REG(0))(%Psp), %Pdi

	cmpl   $(__NR32_syscall0_max), %eax /* Yes: 32-bit compare! */
	ja     .Lcall_sysex32
	pushP_cfi $.Lnormal_return32
	EXTERN(x86_sysroute0_runc32)
	jmpP   *x86_sysroute0_runc32(,%Pax,SIZEOF_POINTER)
	.cfi_adjust_cfa_offset -Pn(1)
.Lbad_sysno32:
	/* %rax is a system call number that doesn't exist. */
	ttest  mask=RPC_SYSCALL_INFO_FEXCEPT, loc=OFFSET_RPC_SYSCALL_INFO_FLAGS(%Psp)
	jnz    .Lthrow_unknown_systemcall /* Throw an actual `E_UNKNOWN_SYSTEMCALL' exception! */
	/* Just return -ENOSYS (no need to go through all the hassle of throwing an exception) */
	movP   $-ENOSYS, %Pax
	movP   $-1, %Pdx
	jmp    .Lnormal_return32

.Lcall_sysex32:
	cmpl   $(__NR32_syscall1_max), %eax /* Yes: 32-bit compare! */
	ja     .Lbad_sysno32
	subl   $(__NR32_syscall1_min), %eax /* Yes: 32-bit compare! */
	jb     .Lbad_sysno32
	EXTERN(x86_sysroute1_runc32)
	callP  *x86_sysroute1_runc32(,%Pax,SIZEOF_POINTER)
.Lnormal_return32:


INTERN_LABEL(__x86_syscall_emulate_r_protect_end):
	/* Return to user-space. */
	addP   $(SIZEOF_RPC_SYSCALL_INFO), %Psp
	.cfi_adjust_cfa_offset -SIZEOF_RPC_SYSCALL_INFO

	/* Check if we must sign-extend the error return value. */
	TEST_DOUBLE_WIDE32(%al, %eax, %Pax, %cl, %ecx, %Pcx, )
	jz     1f
	/* Store the upper 32 bit of the return value in %rdx */
	movP   %Pax, %Pdx
	shrP   $(32), %Pdx
	movP   %Pdx, (OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGS_RDX)(%Psp)
1:
	/* Restore GP registers (except for %eax, which holds the syscall return value) */
	ASM_POP_GPREGSNSP_NORAX_CFI_R
	addP   $(Pn(1)), %Psp /* [C] Accumulator register */
	.cfi_adjust_cfa_offset -Pn(1)
	intr_exit
#endif /* __x86_64__ */
	.cfi_endproc
END(syscall_emulate_r)


#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_EMULATE_S */
