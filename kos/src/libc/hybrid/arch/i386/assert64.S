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
#define _KOS_KERNEL_SOURCE 1
#include <__crt.h> /* __NO_FPU */
#include <hybrid/compiler.h>
#include <asm/cfi.h>
#include <kos/kernel/cpu-state.h>
#include <asm/cpu-flags.h>
#include <bits/va_list-struct.h>


#ifdef __KERNEL__
#define ASSERTION_SECTION(n)   .text.cold
#else /* __KERNEL__ */
#define ASSERTION_SECTION(n)   .text.crt.assert.n
#endif /* !__KERNEL__ */


.section ASSERTION_SECTION(__stack_chk_fail)
PUBLIC_FUNCTION(__stack_chk_fail)
	.cfi_startproc
	/* Generate a full `struct kcpustate' */
	pushfq_cfi_r
	pushq_cfi_r %rax    /* [C] Accumulator register */
	pushq_cfi_r %rcx    /* [C] Count register */
	pushq_cfi_r %rdx    /* [C] Data register */
	pushq_cfi_r %rbx    /* [P] Base register */
	leaq   (6*8)(%rsp), %rax
	pushq_cfi   %rax    /* [P] Stack pointer */
	pushq_cfi_r %rbp    /* [P] Frame base pointer */
	pushq_cfi_r %rsi    /* [C] Source pointer */
	pushq_cfi_r %rdi    /* [C] Destination pointer */
	pushq_cfi_r %r8     /* [C] General purpose register #8 */
	pushq_cfi_r %r9     /* [C] General purpose register #9 */
	pushq_cfi_r %r10    /* [C] General purpose register #10 */
	pushq_cfi_r %r11    /* [C] General purpose register #11 */
	pushq_cfi_r %r12    /* [P] General purpose register #12 */
	pushq_cfi_r %r13    /* [P] General purpose register #13 */
	pushq_cfi_r %r14    /* [P] General purpose register #14 */
	pushq_cfi_r %r15    /* [P] General purpose register #15 */

	movq   %rsp, %rdi
	INTERN(libc_stack_failure_core)
	call   libc_stack_failure_core
	.cfi_endproc
END(__stack_chk_fail)
DEFINE_INTERN_ALIAS(__stack_chk_fail_local, __stack_chk_fail)

.section ASSERTION_SECTION(abort)
INTERN_FUNCTION(libc_abort)
	.cfi_startproc
	/* Generate a full `struct kcpustate' */
	pushfq_cfi_r
	pushq_cfi_r %rax    /* [C] Accumulator register */
	pushq_cfi_r %rcx    /* [C] Count register */
	pushq_cfi_r %rdx    /* [C] Data register */
	pushq_cfi_r %rbx    /* [P] Base register */
	leaq   (6*8)(%rsp), %rax
	pushq_cfi   %rax    /* [P] Stack pointer */
	pushq_cfi_r %rbp    /* [P] Frame base pointer */
	pushq_cfi_r %rsi    /* [C] Source pointer */
	pushq_cfi_r %rdi    /* [C] Destination pointer */
	pushq_cfi_r %r8     /* [C] General purpose register #8 */
	pushq_cfi_r %r9     /* [C] General purpose register #9 */
	pushq_cfi_r %r10    /* [C] General purpose register #10 */
	pushq_cfi_r %r11    /* [C] General purpose register #11 */
	pushq_cfi_r %r12    /* [P] General purpose register #12 */
	pushq_cfi_r %r13    /* [P] General purpose register #13 */
	pushq_cfi_r %r14    /* [P] General purpose register #14 */
	pushq_cfi_r %r15    /* [P] General purpose register #15 */

	movq   %rsp, %rdi
	INTERN(libc_abort_failure_core)
	call   libc_abort_failure_core
	.cfi_endproc
END(libc_abort)

DEFINE_PUBLIC_ALIAS(_ZSt9terminatev, libc_abort) /* std::terminate(void) */
DEFINE_PUBLIC_ALIAS(abort, libc_abort)
/* Provide debugging facilities for __builtin_unreachable() (s.a. <__crt.h>) */
DEFINE_PUBLIC_ALIAS(__crt_unreachable, libc_abort)
DEFINE_INTERN_ALIAS(libc___crt_unreachable, libc_abort)
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS("?terminate@@YAXXZ", libc_abort) /* std::terminate(void) */
#endif /* !__KERNEL__ */




.section ASSERTION_SECTION(__afail)
INTERN_FUNCTION(libc___afail)
	.cfi_startproc
	/* %rdi: char const *expr
	 * %rsi: char const *file
	 * %rdx: unsigned int line
	 * %rcx: char const *func */
	pushq_cfi $0   /* aa_format */
	pushq_cfi %rcx /* aa_func */
	pushq_cfi %rdx /* aa_line */
	pushq_cfi %rsi /* aa_file */
	pushq_cfi %rdi /* aa_expr */
	pushq_cfi (6*8)(%rsp) /* aa_state.kcs_rip */
	pushfq_cfi_r          /* aa_state.kcs_rflags */
	pushq_cfi_r %rax    /* [C] Accumulator register */
	pushq_cfi_r %rcx    /* [C] Count register */
	pushq_cfi_r %rdx    /* [C] Data register */
	pushq_cfi_r %rbx    /* [P] Base register */
	leaq   (12*8)(%rsp), %rax
	pushq_cfi   %rax    /* [P] Stack pointer */
	pushq_cfi_r %rbp    /* [P] Frame base pointer */
	pushq_cfi_r %rsi    /* [C] Source pointer */
	pushq_cfi_r %rdi    /* [C] Destination pointer */
	pushq_cfi_r %r8     /* [C] General purpose register #8 */
	pushq_cfi_r %r9     /* [C] General purpose register #9 */
	pushq_cfi_r %r10    /* [C] General purpose register #10 */
	pushq_cfi_r %r11    /* [C] General purpose register #11 */
	pushq_cfi_r %r12    /* [P] General purpose register #12 */
	pushq_cfi_r %r13    /* [P] General purpose register #13 */
	pushq_cfi_r %r14    /* [P] General purpose register #14 */
	pushq_cfi_r %r15    /* [P] General purpose register #15 */
	subq   $(SIZEOF_X86_64_VA_LIST_STRUCT), %rsp /* aa_args */
	movq   %rsp, %rdi
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
	.cfi_endproc
END(libc___afail)
DEFINE_PUBLIC_ALIAS(__afail, libc___afail)

#ifndef __KERNEL__
DEFINE_INTERN_ALIAS(libc___assertfail, libc___afail)
DEFINE_PUBLIC_ALIAS(__assertfail, libc___assertfail)
#endif /* !__KERNEL__ */


.section ASSERTION_SECTION(__afailf)
INTERN_FUNCTION(libc___afailf)
	.cfi_startproc
	/* %rdi:     char const *expr
	 * %rsi:     char const *file
	 * %rdx:     unsigned int line
	 * %rcx:     char const *func
	 * %r8:      char const *format
	 * %r9:      VA(0)
	 * 8(%rsp):  VA(1)
	 * 16(%rsp): VA(2)
	 */
	pushq_cfi %r8  /* aa_format */
	pushq_cfi %rcx /* aa_func */
	pushq_cfi %rdx /* aa_line */
	pushq_cfi %rsi /* aa_file */
	pushq_cfi %rdi /* aa_expr */
	pushq_cfi (6*8)(%rsp) /* aa_state.kcs_rip */
	pushfq_cfi_r          /* aa_state.kcs_rflags */
	pushq_cfi_r %rax    /* [C] Accumulator register */
	pushq_cfi_r %rcx    /* [C] Count register */
	pushq_cfi_r %rdx    /* [C] Data register */
	pushq_cfi_r %rbx    /* [P] Base register */
	leaq   (12*8)(%rsp), %rdx
	pushq_cfi   %rdx    /* [P] Stack pointer */
	pushq_cfi_r %rbp    /* [P] Frame base pointer */
	pushq_cfi_r %rsi    /* [C] Source pointer */
	pushq_cfi_r %rdi    /* [C] Destination pointer */
	pushq_cfi_r %r8     /* [C] General purpose register #8 */
	pushq_cfi_r %r9     /* [C] General purpose register #9 */
	pushq_cfi_r %r10    /* [C] General purpose register #10 */
	pushq_cfi_r %r11    /* [C] General purpose register #11 */
	pushq_cfi_r %r12    /* [P] General purpose register #12 */
	pushq_cfi_r %r13    /* [P] General purpose register #13 */
	pushq_cfi_r %r14    /* [P] General purpose register #14 */
	pushq_cfi_r %r15    /* [P] General purpose register #15 */
	leaq   ((6*8) - OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_R9)(%rsp), %rcx
	pushq_cfi %rcx      /* vl_reg_save_area (== &aa_state.kcs_gpregs.gp_r9 - OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_R9) */
	pushq_cfi %rdx      /* vl_overflow_arg_area (== aa_state.kcs_gpregs.gp_rsp) */
	pushq  $(5 * 8)     /* vl_gp_offset */
	movq   %rsp, %rdi   /* libc_assertion_failure_core:args */
#ifndef __NO_FPU
	/* Check if FPU registers need saving */
	testq  %rax, %rax
	jz     1f
	.cfi_remember_state
	subq_imm_cfi (1 * 8 + X86_64_VA_LIST_XMM_COUNT * 16), %rsp
	leaq   -OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_R9(%rsp), %rcx
	movq   %rcx, OFFSET_X86_64_VA_LIST_STRUCT_REG_SAVE_AREA(%rdi)
	movl   $0,   OFFSET_X86_64_VA_LIST_STRUCT_FP_OFFSET(%rdi)
	movq   %r9,  0(%rsp)
	X86_64_VA_LIST_SAVE_XMM(8(%rsp))
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
1:	.cfi_restore_state
#endif /* !__NO_FPU */
	movl   $SIZEOF_X86_64_VA_LIST_REG_SAVE_AREA, OFFSET_X86_64_VA_LIST_STRUCT_FP_OFFSET(%rdi)
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
	.cfi_endproc
END(libc___afailf)
DEFINE_PUBLIC_ALIAS(__afailf, libc___afailf)




#if defined(__KERNEL__) || defined(__INTELLISENSE__)
.section ASSERTION_SECTION(__acheck)
INTERN_FUNCTION(libc___acheck)
	.cfi_startproc
	/* %rdi: char const *expr
	 * %rsi: char const *file
	 * %rdx: unsigned int line
	 * %rcx: char const *func */
	pushq_cfi $0   /* aa_format */
	pushq_cfi %rcx /* aa_func */
	pushq_cfi %rdx /* aa_line */
	pushq_cfi %rsi /* aa_file */
	pushq_cfi %rdi /* aa_expr */
	pushq_cfi (6*8)(%rsp) /* aa_state.kcs_rip */
	pushfq_cfi_r          /* aa_state.kcs_rflags */
	pushq_cfi_r %rax    /* [C] Accumulator register */
	pushq_cfi_r %rcx    /* [C] Count register */
	pushq_cfi_r %rdx    /* [C] Data register */
	pushq_cfi_r %rbx    /* [P] Base register */
	leaq   (12*8)(%rsp), %rax
	pushq_cfi   %rax    /* [P] Stack pointer */
	pushq_cfi_r %rbp    /* [P] Frame base pointer */
	pushq_cfi_r %rsi    /* [C] Source pointer */
	pushq_cfi_r %rdi    /* [C] Destination pointer */
	pushq_cfi_r %r8     /* [C] General purpose register #8 */
	pushq_cfi_r %r9     /* [C] General purpose register #9 */
	pushq_cfi_r %r10    /* [C] General purpose register #10 */
	pushq_cfi_r %r11    /* [C] General purpose register #11 */
	pushq_cfi_r %r12    /* [P] General purpose register #12 */
	pushq_cfi_r %r13    /* [P] General purpose register #13 */
	pushq_cfi_r %r14    /* [P] General purpose register #14 */
	pushq_cfi_r %r15    /* [P] General purpose register #15 */
	subq   $(SIZEOF_X86_64_VA_LIST_STRUCT), %rsp /* aa_args */
	movq   %rsp, %rdi
	INTERN(libc_assertion_check_core)
	call   libc_assertion_check_core
	.cfi_endproc
.Lload_kcpustate_eax:
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %rsp, 0
	.cfi_reg_offset %rax, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_RAX, %rax
	.cfi_reg_offset %rcx, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_RCX, %rax
	.cfi_reg_offset %rdx, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_RDX, %rax
	.cfi_reg_offset %rbx, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_RBX, %rax
	.cfi_reg_offset %rsp, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_RSP, %rax
	.cfi_reg_offset %rbp, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_RBP, %rax
	.cfi_reg_offset %rsi, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_RSI, %rax
	.cfi_reg_offset %rdi, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_RDI, %rax
	.cfi_reg_offset %r8, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_R8, %rax
	.cfi_reg_offset %r9, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_R9, %rax
	.cfi_reg_offset %r10, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_R10, %rax
	.cfi_reg_offset %r11, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_R11, %rax
	.cfi_reg_offset %r12, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_R12, %rax
	.cfi_reg_offset %r13, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_R13, %rax
	.cfi_reg_offset %r14, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_R14, %rax
	.cfi_reg_offset %r15, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_R15, %rax
	.cfi_reg_offset %rflags, OFFSET_KCPUSTATE_RFLAGS, %rax
	.cfi_reg_offset %rip, OFFSET_KCPUSTATE_RIP, %rax
	movq   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_RCX(%rax), %rcx
	.cfi_same_value %rcx
	movq   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_RDX(%rax), %rdx
	.cfi_same_value %rdx
	movq   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_RBX(%rax), %rbx
	.cfi_same_value %rbx
	movq   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_RSP(%rax), %rsp
	.cfi_same_value %rsp
	movq   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_RBP(%rax), %rbp
	.cfi_same_value %rbp
	movq   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_RSI(%rax), %rsi
	.cfi_same_value %rsi
	movq   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_RDI(%rax), %rdi
	.cfi_same_value %rdi
	movq   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_R8(%rax), %r8
	.cfi_same_value %r8
	movq   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_R9(%rax), %r9
	.cfi_same_value %r9
	movq   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_R10(%rax), %r10
	.cfi_same_value %r10
	movq   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_R11(%rax), %r11
	.cfi_same_value %r11
	movq   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_R12(%rax), %r12
	.cfi_same_value %r12
	movq   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_R13(%rax), %r13
	.cfi_same_value %r13
	movq   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_R14(%rax), %r14
	.cfi_same_value %r14
	movq   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_R15(%rax), %r15
	.cfi_same_value %r15
	pushq  OFFSET_KCPUSTATE_RIP(%eax)
	.cfi_reg_value %rsp, 8, %rsp
	pushq  OFFSET_KCPUSTATE_RFLAGS(%eax)
	.cfi_reg_value %rsp, 16, %rsp
	.cfi_reg_offset %rflags, 0, %rsp
	.cfi_reg_offset %rip, 8, %rsp
	movq   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_RAX(%rax), %rax
	.cfi_same_value %rax
	popfq
	.cfi_same_value %rflags
	.cfi_reg_value %rsp, 8, %rsp
	.cfi_reg_offset %rip, 0, %rsp
	ret
	.cfi_endproc
END(libc___acheck)
DEFINE_PUBLIC_ALIAS(__acheck, libc___acheck)


.section ASSERTION_SECTION(__acheckf)
INTERN_FUNCTION(libc___acheckf)
	.cfi_startproc
	/* %rdi:     char const *expr
	 * %rsi:     char const *file
	 * %rdx:     unsigned int line
	 * %rcx:     char const *func
	 * %r8:      char const *format
	 * %r9:      VA(0)
	 * 8(%rsp):  VA(1)
	 * 16(%rsp): VA(2)
	 */
	pushq_cfi %r8  /* aa_format */
	pushq_cfi %rcx /* aa_func */
	pushq_cfi %rdx /* aa_line */
	pushq_cfi %rsi /* aa_file */
	pushq_cfi %rdi /* aa_expr */
	pushq_cfi (6*8)(%rsp) /* aa_state.kcs_rip */
	pushfq_cfi_r          /* aa_state.kcs_rflags */
	pushq_cfi_r %rax    /* [C] Accumulator register */
	pushq_cfi_r %rcx    /* [C] Count register */
	pushq_cfi_r %rdx    /* [C] Data register */
	pushq_cfi_r %rbx    /* [P] Base register */
	leaq   (12*8)(%rsp), %rdx
	pushq_cfi   %rdx    /* [P] Stack pointer */
	pushq_cfi_r %rbp    /* [P] Frame base pointer */
	pushq_cfi_r %rsi    /* [C] Source pointer */
	pushq_cfi_r %rdi    /* [C] Destination pointer */
	pushq_cfi_r %r8     /* [C] General purpose register #8 */
	pushq_cfi_r %r9     /* [C] General purpose register #9 */
	pushq_cfi_r %r10    /* [C] General purpose register #10 */
	pushq_cfi_r %r11    /* [C] General purpose register #11 */
	pushq_cfi_r %r12    /* [P] General purpose register #12 */
	pushq_cfi_r %r13    /* [P] General purpose register #13 */
	pushq_cfi_r %r14    /* [P] General purpose register #14 */
	pushq_cfi_r %r15    /* [P] General purpose register #15 */
	leaq   ((6*8) - OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_R9)(%rsp), %rcx
	pushq_cfi %rcx      /* vl_reg_save_area (== &aa_state.kcs_gpregs.gp_r9 - OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_R9) */
	pushq_cfi %rdx      /* vl_overflow_arg_area (== aa_state.kcs_gpregs.gp_rsp) */
	pushq  $(5 * 8)     /* vl_gp_offset */
	movq   %rsp, %rdi   /* libc_assertion_failure_core:args */
#ifndef __NO_FPU
	/* Check if FPU registers need saving */
	testq  %rax, %rax
	jz     1f
	.cfi_remember_state
	subq_imm_cfi (1 * 8 + X86_64_VA_LIST_XMM_COUNT * 16), %rsp
	leaq   -OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_R9(%rsp), %rcx
	movq   %rcx, OFFSET_X86_64_VA_LIST_STRUCT_REG_SAVE_AREA(%rdi)
	movl   $0,   OFFSET_X86_64_VA_LIST_STRUCT_FP_OFFSET(%rdi)
	movq   %r9,  0(%rsp)
	X86_64_VA_LIST_SAVE_XMM(8(%rsp))
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
1:	.cfi_restore_state
#endif /* !__NO_FPU */
	movl   $SIZEOF_X86_64_VA_LIST_REG_SAVE_AREA, OFFSET_X86_64_VA_LIST_STRUCT_FP_OFFSET(%rdi)
	INTERN(libc_assertion_check_core)
	call   libc_assertion_check_core
	jmp    .Lload_kcpustate_eax
	.cfi_endproc
END(libc___acheckf)
DEFINE_PUBLIC_ALIAS(__acheckf, libc___acheckf)

#endif /* __KERNEL__ || __INTELLISENSE__ */




#ifndef __KERNEL__
DEFINE_INTERN_ALIAS(libc___assert_fail, libc___afail)
DEFINE_PUBLIC_ALIAS(__assert_fail, libc___assert_fail)

.section ASSERTION_SECTION(__assert_func)
INTERN_FUNCTION(libc___assert_func)
	.cfi_startproc
	/* %rdi: char const *file
	 * %rsi: unsigned int line
	 * %rdx: char const *func
	 * %rcx: char const *expr */
	pushq_cfi $0   /* aa_format */
	pushq_cfi %rdx /* aa_func */
	pushq_cfi %rsi /* aa_line */
	pushq_cfi %rdi /* aa_file */
	pushq_cfi %rcx /* aa_expr */
	pushq_cfi (6*8)(%rsp) /* aa_state.kcs_rip */
	pushfq_cfi_r          /* aa_state.kcs_rflags */
	pushq_cfi_r %rax    /* [C] Accumulator register */
	pushq_cfi_r %rcx    /* [C] Count register */
	pushq_cfi_r %rdx    /* [C] Data register */
	pushq_cfi_r %rbx    /* [P] Base register */
	leaq   (12*8)(%rsp), %rax
	pushq_cfi   %rax    /* [P] Stack pointer */
	pushq_cfi_r %rbp    /* [P] Frame base pointer */
	pushq_cfi_r %rsi    /* [C] Source pointer */
	pushq_cfi_r %rdi    /* [C] Destination pointer */
	pushq_cfi_r %r8     /* [C] General purpose register #8 */
	pushq_cfi_r %r9     /* [C] General purpose register #9 */
	pushq_cfi_r %r10    /* [C] General purpose register #10 */
	pushq_cfi_r %r11    /* [C] General purpose register #11 */
	pushq_cfi_r %r12    /* [P] General purpose register #12 */
	pushq_cfi_r %r13    /* [P] General purpose register #13 */
	pushq_cfi_r %r14    /* [P] General purpose register #14 */
	pushq_cfi_r %r15    /* [P] General purpose register #15 */
	subq   $(SIZEOF_X86_64_VA_LIST_STRUCT), %rsp /* aa_args */
	movq   %rsp, %rdi
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
	.cfi_endproc
END(libc___assert_func)
DEFINE_PUBLIC_ALIAS(__assert_func, libc___assert_func)


.section ASSERTION_SECTION(__assert)
INTERN_FUNCTION(libc___assert)
	.cfi_startproc
	/* %rdi: char const *file
	 * %rsi: unsigned int line
	 * %rdx: char const *expr */
	pushq_cfi $0   /* aa_format */
	pushq_cfi $0   /* aa_func */
	pushq_cfi %rsi /* aa_line */
	pushq_cfi %rdi /* aa_file */
	pushq_cfi %rdx /* aa_expr */
	pushq_cfi (6*8)(%rsp) /* aa_state.kcs_rip */
	pushfq_cfi_r          /* aa_state.kcs_rflags */
	pushq_cfi_r %rax    /* [C] Accumulator register */
	pushq_cfi_r %rcx    /* [C] Count register */
	pushq_cfi_r %rdx    /* [C] Data register */
	pushq_cfi_r %rbx    /* [P] Base register */
	leaq   (12*8)(%rsp), %rax
	pushq_cfi   %rax    /* [P] Stack pointer */
	pushq_cfi_r %rbp    /* [P] Frame base pointer */
	pushq_cfi_r %rsi    /* [C] Source pointer */
	pushq_cfi_r %rdi    /* [C] Destination pointer */
	pushq_cfi_r %r8     /* [C] General purpose register #8 */
	pushq_cfi_r %r9     /* [C] General purpose register #9 */
	pushq_cfi_r %r10    /* [C] General purpose register #10 */
	pushq_cfi_r %r11    /* [C] General purpose register #11 */
	pushq_cfi_r %r12    /* [P] General purpose register #12 */
	pushq_cfi_r %r13    /* [P] General purpose register #13 */
	pushq_cfi_r %r14    /* [P] General purpose register #14 */
	pushq_cfi_r %r15    /* [P] General purpose register #15 */
	subq   $(SIZEOF_X86_64_VA_LIST_STRUCT), %rsp /* aa_args */
	movq   %rsp, %rdi
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
	.cfi_endproc
END(libc___assert)
DEFINE_PUBLIC_ALIAS(__assert, libc___assert)


.section ASSERTION_SECTION(_assert)
INTERN_FUNCTION(libc__assert)
	.cfi_startproc
	/* %rdi: char const *expr
	 * %rsi: char const *file
	 * %rdx: unsigned int line */
	pushq_cfi $0   /* aa_format */
	pushq_cfi $0   /* aa_func */
	pushq_cfi %rdx /* aa_line */
	pushq_cfi %rsi /* aa_file */
	pushq_cfi %rdi /* aa_expr */
	pushq_cfi (6*8)(%rsp) /* aa_state.kcs_rip */
	pushfq_cfi_r          /* aa_state.kcs_rflags */
	pushq_cfi_r %rax    /* [C] Accumulator register */
	pushq_cfi_r %rcx    /* [C] Count register */
	pushq_cfi_r %rdx    /* [C] Data register */
	pushq_cfi_r %rbx    /* [P] Base register */
	leaq   (12*8)(%rsp), %rax
	pushq_cfi   %rax    /* [P] Stack pointer */
	pushq_cfi_r %rbp    /* [P] Frame base pointer */
	pushq_cfi_r %rsi    /* [C] Source pointer */
	pushq_cfi_r %rdi    /* [C] Destination pointer */
	pushq_cfi_r %r8     /* [C] General purpose register #8 */
	pushq_cfi_r %r9     /* [C] General purpose register #9 */
	pushq_cfi_r %r10    /* [C] General purpose register #10 */
	pushq_cfi_r %r11    /* [C] General purpose register #11 */
	pushq_cfi_r %r12    /* [P] General purpose register #12 */
	pushq_cfi_r %r13    /* [P] General purpose register #13 */
	pushq_cfi_r %r14    /* [P] General purpose register #14 */
	pushq_cfi_r %r15    /* [P] General purpose register #15 */
	subq   $(SIZEOF_X86_64_VA_LIST_STRUCT), %rsp /* aa_args */
	movq   %rsp, %rdi
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
	.cfi_endproc
END(libc__assert)
DEFINE_PUBLIC_ALIAS(_assert, libc__assert)
#endif /* !__KERNEL__ */


