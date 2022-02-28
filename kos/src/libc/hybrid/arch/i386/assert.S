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
#ifndef GUARD_LIBC_HYBRID_ARCH_I386_ASSERT_S
#define GUARD_LIBC_HYBRID_ARCH_I386_ASSERT_S 1
#define __ASSEMBLER__ 1
#define _KOS_KERNEL_SOURCE 1

#include <hybrid/compiler.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/compat.h>
#include <bits/va_list-struct.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state.h>

#ifndef SIZEOF_POINTER
#include <hybrid/typecore.h>
#define SIZEOF_POINTER __SIZEOF_POINTER__
#endif /* !SIZEOF_POINTER */

#define Pn(n) (SIZEOF_POINTER * (n))


#ifdef __KERNEL__
#define ASSERTION_SECTION   .text.cold
#else /* __KERNEL__ */
#define ASSERTION_SECTION   .text.crt.assert
#endif /* !__KERNEL__ */

/* >> PUBLIC ATTR_NORETURN void LIBCCALL __stack_chk_fail(void);
 * >> INTERN ATTR_NORETURN void LIBCCALL __stack_chk_fail_local(void); */
.section ASSERTION_SECTION
PUBLIC_FUNCTION(__stack_chk_fail)
	.cfi_startproc
	/* Generate a full `struct kcpustate' */
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R

	/* Call the high-level handler */
	movP   %Psp, %R_fcall0P
	EXTERN(libc_stack_failure_core)
	call   libc_stack_failure_core
	.cfi_endproc
END(__stack_chk_fail)
DEFINE_INTERN_ALIAS(__stack_chk_fail_local, __stack_chk_fail)


/* >> PUBLIC ATTR_NORETURN void LIBCCALL abort(void); */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc_abort)
	.cfi_startproc
	/* Generate a full `struct kcpustate' */
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R

	/* Call the high-level handler */
	movP   %Psp, %R_fcall0P
	EXTERN(libc_abort_failure_core)
	call   libc_abort_failure_core
	.cfi_endproc
END(libc_abort)

DEFINE_PUBLIC_ALIAS(abort, libc_abort)

/* Provide debugging facilities for __builtin_unreachable() (s.a. <__crt.h>) */
DEFINE_PUBLIC_ALIAS(__crt_unreachable, libc_abort)
DEFINE_INTERN_ALIAS(libc___crt_unreachable, libc_abort)
DEFINE_PUBLIC_ALIAS(_ZSt9terminatev, libc_abort) /* std::terminate(void) */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(terminate, libc_abort)           /* std::terminate(void) */
DEFINE_PUBLIC_ALIAS("?terminate@@YAXXZ", libc_abort) /* std::terminate(void) */
#endif /* !__KERNEL__ */



.section ASSERTION_SECTION
INTERN_FUNCTION(libc___afail)
	.cfi_startproc
#ifdef __x86_64__
	/* %R_sysvabi0P: char const *expr
	 * %R_sysvabi1P: char const *file
	 * %R_sysvabi2P: unsigned int line
	 * %R_sysvabi3P: char const *func */
	pushP_cfi $(0)         /* aa_format */
	pushP_cfi %R_sysvabi3P /* aa_func */
	pushP_cfi %R_sysvabi2P /* aa_line */
	pushP_cfi %R_sysvabi1P /* aa_file */
	pushP_cfi %R_sysvabi0P /* aa_expr */
	pushP_cfi Pn(5)(%Psp)  /* aa_state.kcs_rip */
	ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(%Pax, Pn(6)) /* 6 = # of preceding `pushP_cfi' */
	subP_imm_cfi SIZEOF_X86_64_VA_LIST_STRUCT, %Psp /* aa_args */
#else /* __x86_64__ */
	/* char const *expr, char const *file, unsigned int line, char const *func */
	pushP_cfi 0(%Psp)  /* RETURN_PC */
	.cfi_rel_offset %Pip, 0
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R_EX(SIZEOF_POINTER)
	movP   (SIZEOF_KCPUSTATE + Pn(1))(%Psp), %Pax /* char const *expr */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(0))(%Psp) /* aa_expr */
	movP   (SIZEOF_KCPUSTATE + Pn(2))(%Psp), %Pax /* char const *file */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(1))(%Psp) /* aa_file */
	movP   (SIZEOF_KCPUSTATE + Pn(3))(%Psp), %Pax /* unsigned int line */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(2))(%Psp) /* aa_line */
	movP   (SIZEOF_KCPUSTATE + Pn(4))(%Psp), %Pax /* char const *func */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(3))(%Psp) /* aa_func */
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(4))(%Psp) /* aa_format */
	pushP_cfi $(0)                                /* aa_args */
#endif /* !__x86_64__ */

	/* Call the high-level handler */
	movP   %Psp, %R_fcall0P
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
	.cfi_endproc
END(libc___afail)
DEFINE_PUBLIC_ALIAS(__afail, libc___afail)





.section ASSERTION_SECTION
INTERN_FUNCTION(libc___afailf)
	.cfi_startproc
#ifdef __x86_64__
	/* %R_sysvabi0P: char const *expr
	 * %R_sysvabi1P: char const *file
	 * %R_sysvabi2P: unsigned int line
	 * %R_sysvabi3P: char const *func
	 * %R_sysvabi4P: char const *format
	 * %R_sysvabi5P: VA(0)
	 * 8(%Psp):      VA(1)
	 * 16(%Psp):     VA(2) */
	pushP_cfi %R_sysvabi4P /* aa_format */
	pushP_cfi %R_sysvabi3P /* aa_func */
	pushP_cfi %R_sysvabi2P /* aa_line */
	pushP_cfi %R_sysvabi1P /* aa_file */
	pushP_cfi %R_sysvabi0P /* aa_expr */
	pushP_cfi Pn(5)(%Psp)  /* aa_state.kcs_rip */
	ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(%Pdx, Pn(6)) /* 6 = # of preceding `pushP_cfi' */
	leaP   (Pn(6) - OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_R9)(%Psp), %Pcx
	pushP_cfi %Pcx         /* vl_reg_save_area (== &aa_state.kcs_gpregs.gp_r9 - OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_R9) */
	pushP_cfi %Pdx         /* vl_overflow_arg_area (== aa_state.kcs_gpregs.gp_rsp) */
	pushP_cfi $(Pn(5))     /* vl_gp_offset */
	movP   %Psp, %R_fcall0P /* libc_assertion_failure_core:args */
#ifndef __NO_FPU
	/* Check if FPU registers need saving */
	testb  %al, %al
	jz     1f
	.cfi_remember_state
	subP_imm_cfi (Pn(1) + X86_64_VA_LIST_XMM_COUNT * 16), %Psp
	leaP   -OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_R9(%Psp), %Pcx
	movq   %Pcx, OFFSET_X86_64_VA_LIST_STRUCT_REG_SAVE_AREA(%R_fcall0P)
	movl   $(0), OFFSET_X86_64_VA_LIST_STRUCT_FP_OFFSET(%R_fcall0P)
	movP   %R_sysvabi5P, Pn(0)(%Psp)
	X86_64_VA_LIST_SAVE_XMM(Pn(1)(%Psp))
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
1:	.cfi_restore_state
#endif /* !__NO_FPU */
	movl   $(SIZEOF_X86_64_VA_LIST_REG_SAVE_AREA), OFFSET_X86_64_VA_LIST_STRUCT_FP_OFFSET(%R_fcall0P)
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
#else /* __x86_64__ */
	/* char const *expr, char const *file, unsigned int line, char const *func, char const *format */

	/* Generate a full `struct kcpustate' */
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R
	leaP   (SIZEOF_KCPUSTATE + Pn(5))(%Psp), %Pax
	pushP_cfi %Pax                         /* aa_args */

	/* Call the high-level handler */
	movP   %Psp, %R_fcall0P
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
#endif /* !__x86_64__ */
	.cfi_endproc
END(libc___afailf)
DEFINE_PUBLIC_ALIAS(__afailf, libc___afailf)



#if defined(__KERNEL__) || defined(__INTELLISENSE__)
/* Support for __acheck[f]() */

.section ASSERTION_SECTION
INTERN_FUNCTION(libc___acheck)
	.cfi_startproc
#ifdef __x86_64__
	/* %R_sysvabi0P: char const *expr
	 * %R_sysvabi1P: char const *file
	 * %R_sysvabi2P: unsigned int line
	 * %R_sysvabi3P: char const *func */
	pushP_cfi $(0)         /* aa_format */
	pushP_cfi %R_sysvabi3P /* aa_func */
	pushP_cfi %R_sysvabi2P /* aa_line */
	pushP_cfi %R_sysvabi1P /* aa_file */
	pushP_cfi %R_sysvabi0P /* aa_expr */
	pushP_cfi Pn(5)(%Psp)  /* aa_state.kcs_rip */
	ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(%Pax, Pn(6)) /* 6 = # of preceding `pushP_cfi' */
	subP_imm_cfi SIZEOF_X86_64_VA_LIST_STRUCT, %Psp /* aa_args */
#else /* __x86_64__ */
	/* char const *expr, char const *file, unsigned int line, char const *func */
	pushP_cfi 0(%Psp)  /* RETURN_PC */
	.cfi_rel_offset %Pip, 0
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R_EX(SIZEOF_POINTER)
	movP   (SIZEOF_KCPUSTATE + Pn(1))(%Psp), %Pax /* char const *expr */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(0))(%Psp) /* aa_expr */
	movP   (SIZEOF_KCPUSTATE + Pn(2))(%Psp), %Pax /* char const *file */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(1))(%Psp) /* aa_file */
	movP   (SIZEOF_KCPUSTATE + Pn(3))(%Psp), %Pax /* unsigned int line */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(2))(%Psp) /* aa_line */
	movP   (SIZEOF_KCPUSTATE + Pn(4))(%Psp), %Pax /* char const *func */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(3))(%Psp) /* aa_func */
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(4))(%Psp) /* aa_format */
	pushP_cfi $(0)                                /* aa_args */
#endif /* !__x86_64__ */

	/* Call the high-level handler */
	movP   %Psp, %R_fcall0P
	INTERN(libc_assertion_check_core)
	call   libc_assertion_check_core

.Lload_kcpustate_Pax:
	.cfi_def_cfa %Pax, 0
	ASM_CFI_OFFSET_RESTORE_KCPUSTATE(0)
	movP   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_PCX)(%Pax), %Pcx
	.cfi_same_value %Pcx
	movP   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_PDX)(%Pax), %Pdx
	.cfi_same_value %Pdx
	movP   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_PBX)(%Pax), %Pbx
	.cfi_same_value %Pbx
	movP   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_PSP)(%Pax), %Psp
	.cfi_same_value %Psp
	movP   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_PBP)(%Pax), %Pbp
	.cfi_same_value %Pbp
	movP   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_PSI)(%Pax), %Psi
	.cfi_same_value %Psi
	movP   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_PDI)(%Pax), %Pdi
	.cfi_same_value %Pdi
#ifdef __x86_64__
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R8)(%Pax), %r8
	.cfi_same_value %r8
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R9)(%Pax), %r9
	.cfi_same_value %r9
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R10)(%Pax), %r10
	.cfi_same_value %r10
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R11)(%Pax), %r11
	.cfi_same_value %r11
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R12)(%Pax), %r12
	.cfi_same_value %r12
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R13)(%Pax), %r13
	.cfi_same_value %r13
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R14)(%Pax), %r14
	.cfi_same_value %r14
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R15)(%Pax), %r15
	.cfi_same_value %r15
#endif /* __x86_64__ */
	pushP  OFFSET_KCPUSTATE_PIP(%Pax)
	.cfi_def_cfa %Psp, Pn(1)
	.cfi_rel_offset %Pip, 0
	.cfi_reg_offset %Pax, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_PAX, %Pax
	pushP_cfi OFFSET_KCPUSTATE_PFLAGS(%Pax)
	.cfi_rel_offset %Pflags, 0
	movP   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_PAX)(%Pax), %Pax
	.cfi_same_value %Pax
	popfP_cfi_r
	ret
	.cfi_endproc
END(libc___acheck)
DEFINE_PUBLIC_ALIAS(__acheck, libc___acheck)


.section ASSERTION_SECTION
INTERN_FUNCTION(libc___acheckf)
	.cfi_startproc
#ifdef __x86_64__
	/* %R_sysvabi0P: char const *expr
	 * %R_sysvabi1P: char const *file
	 * %R_sysvabi2P: unsigned int line
	 * %R_sysvabi3P: char const *func
	 * %R_sysvabi4P: char const *format
	 * %R_sysvabi5P: VA(0)
	 * 8(%Psp):      VA(1)
	 * 16(%Psp):     VA(2) */
	pushP_cfi %R_sysvabi4P  /* aa_format */
	pushP_cfi %R_sysvabi3P  /* aa_func */
	pushP_cfi %R_sysvabi2P  /* aa_line */
	pushP_cfi %R_sysvabi1P  /* aa_file */
	pushP_cfi %R_sysvabi0P  /* aa_expr */
	pushP_cfi Pn(5)(%Psp)   /* aa_state.kcs_rip */
	ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(%Pdx, Pn(6)) /* 6 = # of preceding `pushP_cfi' */
	leaP   (Pn(6) - OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_R9)(%Psp), %Pcx
	pushP_cfi %Pcx          /* vl_reg_save_area (== &aa_state.kcs_gpregs.gp_r9 - OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_R9) */
	pushP_cfi %Pdx          /* vl_overflow_arg_area (== aa_state.kcs_gpregs.gp_rsp) */
	pushP_cfi $(Pn(5))      /* vl_gp_offset */
	movP   %Psp, %R_fcall0P /* libc_assertion_failure_core:args */
#ifndef __NO_FPU
	/* Check if FPU registers need saving */
	testb  %al, %al
	jz     1f
	.cfi_remember_state
	subP_imm_cfi (Pn(1) + X86_64_VA_LIST_XMM_COUNT * 16), %Psp
	leaP   -OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_R9(%Psp), %Pcx
	movq   %Pcx, OFFSET_X86_64_VA_LIST_STRUCT_REG_SAVE_AREA(%R_fcall0P)
	movl   $(0), OFFSET_X86_64_VA_LIST_STRUCT_FP_OFFSET(%R_fcall0P)
	movP   %R_sysvabi5P, Pn(0)(%Psp)
	X86_64_VA_LIST_SAVE_XMM(Pn(1)(%Psp))
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
	jmp    .Lload_kcpustate_Pax
1:	.cfi_restore_state
#endif /* !__NO_FPU */
	movl   $(SIZEOF_X86_64_VA_LIST_REG_SAVE_AREA), OFFSET_X86_64_VA_LIST_STRUCT_FP_OFFSET(%R_fcall0P)
#else /* __x86_64__ */
	/* char const *expr, char const *file, unsigned int line, char const *func, char const *format */
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R
	leaP   (SIZEOF_KCPUSTATE + Pn(5))(%Psp), %Pax
	pushP_cfi %Pax           /* aa_args */
	movP   %Psp, %R_fcall0P
#endif /* !__x86_64__ */

	/* Call the high-level handler */
	INTERN(libc_assertion_check_core)
	call   libc_assertion_check_core
	jmp    .Lload_kcpustate_Pax
	.cfi_endproc
END(libc___acheckf)
DEFINE_PUBLIC_ALIAS(__acheckf, libc___acheckf)
#endif /* __KERNEL__ || __INTELLISENSE__ */



#if !defined(__KERNEL__) || defined(__INTELLISENSE__)

DEFINE_INTERN_ALIAS(libc___assert_fail, libc___afail)
DEFINE_PUBLIC_ALIAS(__assert_fail, libc___assert_fail)

.section ASSERTION_SECTION
INTERN_FUNCTION(libc___assert_func)
	.cfi_startproc

#ifdef __x86_64__
	/* %R_sysvabi0P: char const *file
	 * %R_sysvabi1P: unsigned int line
	 * %R_sysvabi2P: char const *func
	 * %R_sysvabi3P: char const *expr */
	pushP_cfi $(0)         /* aa_format */
	pushP_cfi %R_sysvabi2P /* aa_func */
	pushP_cfi %R_sysvabi1P /* aa_line */
	pushP_cfi %R_sysvabi0P /* aa_file */
	pushP_cfi %R_sysvabi3P /* aa_expr */
	pushP_cfi Pn(5)(%Psp)  /* aa_state.kcs_rip */
	ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(%Pax, Pn(6)) /* 6 = # of preceding `pushP_cfi' */
	subP_imm_cfi SIZEOF_X86_64_VA_LIST_STRUCT, %Psp /* aa_args */
#else /* __x86_64__ */
	/* char const *file, unsigned int line, char const *func, char const *expr */
	pushP_cfi 0(%Psp)  /* RETURN_PC */
	.cfi_rel_offset %Pip, 0
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R_EX(SIZEOF_POINTER)
	movP   (SIZEOF_KCPUSTATE + Pn(4))(%Psp), %Pax /* char const *expr */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(0))(%Psp) /* aa_expr */
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(4))(%Psp) /* aa_format */
	pushP_cfi $(0)                                /* aa_args */
#endif /* !__x86_64__ */

	/* Call the high-level handler */
	movP   %Psp, %R_fcall0P
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
	.cfi_endproc
END(libc___assert_func)
DEFINE_PUBLIC_ALIAS(__assert_func, libc___assert_func)


#ifdef __x86_64__
DEFINE_INTERN_ALIAS(libc___assertfail, libc___afail)
#else /* __x86_64__ */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc___assertfail)
	.cfi_startproc
	/* char const *expr, char const *file, unsigned int line, char const *func, size_t charsize */
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(4))(%Psp) /* aa_format */
	pushP_cfi $(0)                                /* aa_args */
	movP   %Psp, %R_fcall0P
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
	.cfi_endproc
END(libc___assertfail)
#endif /* !__x86_64__ */
DEFINE_PUBLIC_ALIAS(__assertfail, libc___assertfail)



.section ASSERTION_SECTION
INTERN_FUNCTION(libc___assert)
	.cfi_startproc
#ifdef __x86_64__
	/* %R_sysvabi0P: char const *file
	 * %R_sysvabi1P: unsigned int line
	 * %R_sysvabi2P: char const *expr */
	pushP_cfi $(0)         /* aa_format */
	pushP_cfi $(0)         /* aa_func */
	pushP_cfi %R_sysvabi1P /* aa_line */
	pushP_cfi %R_sysvabi0P /* aa_file */
	pushP_cfi %R_sysvabi2P /* aa_expr */
	pushP_cfi Pn(5)(%Psp)  /* aa_state.kcs_rip */
	ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(%Pax, Pn(6)) /* 6 = # of preceding `pushP_cfi' */
	subP_imm_cfi SIZEOF_X86_64_VA_LIST_STRUCT, %Psp /* aa_args */
#else /* __x86_64__ */
	/* char const *file, unsigned int line, char const *expr */
	pushP_cfi 0(%Psp)  /* RETURN_PC */
	pushP_cfi 0(%Psp)  /* RETURN_PC */
	.cfi_rel_offset %Pip, 0
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R_EX(Pn(2))
	/*                -,                -, char const  *file, unsigned int line, char const *expr */
	/* char const *expr, char const *file, unsigned int line, char const  *func, char const *format */
	movP   (SIZEOF_KCPUSTATE + Pn(2))(%Psp), %Pax /* char const *file */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(1))(%Psp) /* aa_file */
	movP   (SIZEOF_KCPUSTATE + Pn(3))(%Psp), %Pax /* unsigned int line */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(2))(%Psp) /* aa_line */
	movP   (SIZEOF_KCPUSTATE + Pn(4))(%Psp), %Pax /* char const *expr */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(0))(%Psp) /* aa_expr */
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(3))(%Psp) /* aa_func */
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(4))(%Psp) /* aa_format */
	pushP_cfi $(0)                                /* aa_args */
#endif /* !__x86_64__ */

	/* Call the high-level handler */
	movP   %Psp, %R_fcall0P
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
	.cfi_endproc
END(libc___assert)
DEFINE_PUBLIC_ALIAS(__assert, libc___assert)



.section ASSERTION_SECTION
INTERN_FUNCTION(libc__assert)
	.cfi_startproc
#ifdef __x86_64__
	/* %R_sysvabi0P: char const *expr
	 * %R_sysvabi1P: char const *file
	 * %R_sysvabi2P: unsigned int line */
	pushP_cfi $(0)         /* aa_format */
	pushP_cfi $(0)         /* aa_func */
	pushP_cfi %R_sysvabi2P /* aa_line */
	pushP_cfi %R_sysvabi1P /* aa_file */
	pushP_cfi %R_sysvabi0P /* aa_expr */
	pushP_cfi Pn(5)(%Psp)  /* aa_state.kcs_rip */
	ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(%Pax, Pn(6)) /* 6 = # of preceding `pushP_cfi' */
	subP_imm_cfi SIZEOF_X86_64_VA_LIST_STRUCT, %Psp     /* aa_args */
#else /* __x86_64__ */
	/* char const *expr, char const *file, unsigned int line */
	pushP_cfi 0(%Psp)  /* RETURN_PC */
	pushP_cfi 0(%Psp)  /* RETURN_PC */
	.cfi_rel_offset %Pip, 0
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R_EX(Pn(2))
	/*                -,                -, char const  *expr, char const *file, unsigned int line */
	/* char const *expr, char const *file, unsigned int line, char const *func, char const  *format */
	movP   (SIZEOF_KCPUSTATE + Pn(2))(%Psp), %Pax /* char const *expr */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(0))(%Psp) /* aa_expr */
	movP   (SIZEOF_KCPUSTATE + Pn(3))(%Psp), %Pax /* char const *file */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(1))(%Psp) /* aa_file */
	movP   (SIZEOF_KCPUSTATE + Pn(4))(%Psp), %Pax /* unsigned int line */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(2))(%Psp) /* aa_line */
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(3))(%Psp) /* aa_func */
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(4))(%Psp) /* aa_format */
	pushP_cfi $(0)                                /* aa_args */
#endif /* !__x86_64__ */

	/* Call the high-level handler */
	movP   %Psp, %R_fcall0P
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
	.cfi_endproc
END(libc__assert)
DEFINE_PUBLIC_ALIAS(_assert, libc__assert)


.section ".text.crt.dos.assert"
INTERN_FUNCTION(libc__wassert)
	.cfi_startproc
#ifdef __x86_64__
	/* %R_sysvabi0P: char32_t const *expr
	 * %R_sysvabi1P: char32_t const *file
	 * %R_sysvabi2P: unsigned int line */
	pushP_cfi $(0)         /* aa_format */
	pushP_cfi $(0)         /* aa_func */
	pushP_cfi %R_sysvabi2P /* aa_line */
	pushP_cfi %R_sysvabi1P /* aa_file */
	pushP_cfi %R_sysvabi0P /* aa_expr */
	pushP_cfi Pn(5)(%Psp)  /* aa_state.kcs_rip */
	ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(%Pax, Pn(6)) /* 6 = # of preceding `pushP_cfi' */
	subP_imm_cfi SIZEOF_X86_64_VA_LIST_STRUCT, %Psp     /* aa_args */
#else /* __x86_64__ */
	/* char32_t const *expr, char32_t const *file, unsigned int line */
	pushP_cfi 0(%Psp)  /* RETURN_PC */
	pushP_cfi 0(%Psp)  /* RETURN_PC */
	.cfi_rel_offset %Pip, 0
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R_EX(Pn(2))
	/*                    -,                    -, char32_t const *expr, char32_t const *file, unsigned int line */
	/* char32_t const *expr, char32_t const *file, unsigned int    line, char     const *func, char const  *format */
	movP   (SIZEOF_KCPUSTATE + Pn(2))(%Psp), %Pax /* char32_t const *expr */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(0))(%Psp) /* aa_expr */
	movP   (SIZEOF_KCPUSTATE + Pn(3))(%Psp), %Pax /* char32_t const *file */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(1))(%Psp) /* aa_file */
	movP   (SIZEOF_KCPUSTATE + Pn(4))(%Psp), %Pax /* unsigned int line */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(2))(%Psp) /* aa_line */
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(3))(%Psp) /* aa_func */
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(4))(%Psp) /* aa_format */
	pushP_cfi $(0)                                /* aa_args */
#endif /* !__x86_64__ */

	/* Call the high-level handler */
	movP   %Psp, %R_fcall0P
	INTERN(libc_assertion_failure_core_c32)
	call   libc_assertion_failure_core_c32
	.cfi_endproc
END(libc__wassert)
DEFINE_PUBLIC_ALIAS(_wassert, libc__wassert)


.section ".text.crt.dos.assert"
INTERN_FUNCTION(libd__wassert)
	.cfi_startproc
#ifdef __x86_64__
	/* NOTE: Because we're NORETURN, no need to do `MSABI_SAVEZONE_PUSH()'! */

	/* %R_msabi0P: char16_t const *expr
	 * %R_msabi1P: char16_t const *file
	 * %R_msabi2P: unsigned int line */
	pushP_cfi $(0)        /* aa_format */
	pushP_cfi $(0)        /* aa_func */
	pushP_cfi %R_msabi2P  /* aa_line */
	pushP_cfi %R_msabi1P  /* aa_file */
	pushP_cfi %R_msabi0P  /* aa_expr */
	pushP_cfi Pn(5)(%Psp) /* aa_state.kcs_rip */
	ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(%Pax, Pn(6)) /* 6 = # of preceding `pushP_cfi' */
	subP_imm_cfi SIZEOF_X86_64_VA_LIST_STRUCT, %Psp     /* aa_args */
#else /* __x86_64__ */
	/* char16_t const *expr, char16_t const *file, unsigned int line */
	pushP_cfi 0(%Psp)  /* RETURN_PC */
	pushP_cfi 0(%Psp)  /* RETURN_PC */
	.cfi_rel_offset %Pip, 0
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R_EX(Pn(2))
	/*                    -,                    -, char16_t const *expr, char16_t const *file, unsigned int line */
	/* char16_t const *expr, char16_t const *file, unsigned int    line, char const     *func, char const  *format */
	movP   (SIZEOF_KCPUSTATE + Pn(2))(%Psp), %Pax /* char16_t const *expr */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(0))(%Psp) /* aa_expr */
	movP   (SIZEOF_KCPUSTATE + Pn(3))(%Psp), %Pax /* char16_t const *file */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(1))(%Psp) /* aa_file */
	movP   (SIZEOF_KCPUSTATE + Pn(4))(%Psp), %Pax /* unsigned int line */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(2))(%Psp) /* aa_line */
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(3))(%Psp) /* aa_func */
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(4))(%Psp) /* aa_format */
	pushP_cfi $(0)                                /* aa_args */
#endif /* !__x86_64__ */

	/* Call the high-level handler */
	movP   %Psp, %R_fcall0P
	INTERN(libc_assertion_failure_core_c16)
	call   libc_assertion_failure_core_c16
	.cfi_endproc
END(libd__wassert)
DEFINE_PUBLIC_ALIAS(DOS$_wassert, libd__wassert)



.section ".text.crt.glibc.assert"
INTERN_FUNCTION(libc___assert_perror_fail)
	/* >> void __assert_perror_fail(int errnum, char const *file,
	 * >>                           unsigned int line, char const *func) */
	.cfi_startproc
#ifdef __x86_64__
	/* %R_sysvabi0P: int errnum
	 * %R_sysvabi1P: char const *file
	 * %R_sysvabi2P: unsigned int line
	 * %R_sysvabi3P: char const *func */
	pushP_cfi $(0)         /* aa_format */
	pushP_cfi %R_sysvabi3P /* aa_func */
	pushP_cfi %R_sysvabi2P /* aa_line */
	pushP_cfi %R_sysvabi1P /* aa_file */
	pushP_cfi %R_sysvabi0P /* aa_expr */
	pushP_cfi Pn(5)(%Psp)  /* aa_state.kcs_rip */
	ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(%Pax, Pn(6)) /* 6 = # of preceding `pushP_cfi' */
	subP_imm_cfi SIZEOF_X86_64_VA_LIST_STRUCT, %Psp /* aa_args */
#else /* __x86_64__ */
	/* int errnum, char const *file, unsigned int line, char const *func */
	pushP_cfi 0(%Psp)  /* RETURN_PC */
	.cfi_rel_offset %Pip, 0
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R_EX(SIZEOF_POINTER)
	movP   (SIZEOF_KCPUSTATE + Pn(1))(%Psp), %Pax /* char const *expr */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(0))(%Psp) /* aa_expr */
	movP   (SIZEOF_KCPUSTATE + Pn(2))(%Psp), %Pax /* char const *file */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(1))(%Psp) /* aa_file */
	movP   (SIZEOF_KCPUSTATE + Pn(3))(%Psp), %Pax /* unsigned int line */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(2))(%Psp) /* aa_line */
	movP   (SIZEOF_KCPUSTATE + Pn(4))(%Psp), %Pax /* char const *func */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(3))(%Psp) /* aa_func */
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(4))(%Psp) /* aa_format */
	pushP_cfi $(0)                                /* aa_args */
#endif /* !__x86_64__ */

	/* Call the high-level handler */
	movP   %Psp, %R_fcall0P
	INTERN(libc_assertion_failure_perror)
	call   libc_assertion_failure_perror
	.cfi_endproc
END(libc___assert_perror_fail)
DEFINE_PUBLIC_ALIAS(__assert_perror_fail, libc___assert_perror_fail)

#endif /* !__KERNEL__ || __INTELLISENSE__ */

#endif /* !GUARD_LIBC_HYBRID_ARCH_I386_ASSERT_S */
