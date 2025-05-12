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
#ifdef __INTELLISENSE__
#include "assert.S"
//#define DEFINE___afail
#define DEFINE___acheck
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE___afail) + defined(DEFINE___acheck)) != 1
#error "Must #define exactly one of these"
#endif /* ... */


#ifdef DEFINE___acheck
#define LOCAL_libc_assertion_failure_core libc_assertion_check_core
#define LOCAL___afail                     __acheck
#define LOCAL_libc___afail                libc___acheck
#define LOCAL___afailf                    __acheckf
#define LOCAL_libc___afailf               libc___acheckf
#define LOCAL___apfail                    __apcheck
#define LOCAL_libc___apfail               libc___apcheck
#define LOCAL___apfailf                   __apcheckf
#define LOCAL_libc___apfailf              libc___apcheckf
#else /* DEFINE___acheck */
#define LOCAL_libc_assertion_failure_core libc_assertion_failure_core
#define LOCAL___afail                     __afail
#define LOCAL_libc___afail                libc___afail
#define LOCAL___afailf                    __afailf
#define LOCAL_libc___afailf               libc___afailf
#define LOCAL___apfail                    __apfail
#define LOCAL_libc___apfail               libc___apfail
#define LOCAL___apfailf                   __apfailf
#define LOCAL_libc___apfailf              libc___apfailf
#endif /* !DEFINE___acheck */


/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> __afail(char const *expr,
 * >>         char const *file,
 * >>         unsigned int line,
 * >>         char const *func); */
.section ASSERTION_SECTION
INTERN_FUNCTION(LOCAL_libc___afail)
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
	pushP_cfi Pn(5)(%Psp)  /* aa_state.kcs_Pip */
	.cfi_rel_offset %Pip, 0
	ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(%Pax, Pn(6)) /* 6 = # of preceding `pushP_cfi' */
	subP_imm_cfi SIZEOF_X86_64_VA_LIST_STRUCT, %Psp /* aa_args */
#else /* __x86_64__ */
	/* char const *expr, char const *file, unsigned int line, char const *func */
	pushP_cfi 0(%Psp)  /* aa_state.kcs_Pip */
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
	INTERN(LOCAL_libc_assertion_failure_core)
	call   LOCAL_libc_assertion_failure_core

#ifndef DEFINE___acheck
#define LOCAL_jmp_Lload_kcpustate_Pax /* nothing */
#else /* !DEFINE___acheck */
#define LOCAL_jmp_Lload_kcpustate_Pax jmp .Lload_kcpustate_Pax
	nop    /* For tracebacks */
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
#endif /* DEFINE___acheck */
	.cfi_endproc
END(LOCAL_libc___afail)
DEFINE_PUBLIC_ALIAS(LOCAL___afail, LOCAL_libc___afail)



/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> __afailf(char const *expr,
 * >>          char const *file,
 * >>          unsigned int line,
 * >>          char const *func,
 * >>          char const *format,
 * >>          ...); */
.section ASSERTION_SECTION
INTERN_FUNCTION(LOCAL_libc___afailf)
	.cfi_startproc
#ifdef __x86_64__
	/* %R_sysvabi0P: char const *expr
	 * %R_sysvabi1P: char const *file
	 * %R_sysvabi2P: unsigned int line
	 * %R_sysvabi3P: char const *func
	 * %R_sysvabi4P: char const *format
	 * %R_sysvabi5P: VA(0)
	 * 8(%Psp):      VA(1)
	 * 16(%Psp):     VA(2)
	 * ... */
	pushP_cfi %R_sysvabi4P  /* aa_format */
	pushP_cfi %R_sysvabi3P  /* aa_func */
	pushP_cfi %R_sysvabi2P  /* aa_line */
	pushP_cfi %R_sysvabi1P  /* aa_file */
	pushP_cfi %R_sysvabi0P  /* aa_expr */
	pushP_cfi Pn(5)(%Psp)   /* aa_state.kcs_Pip */
	.cfi_rel_offset %Pip, 0
	ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(%Pdx, Pn(6)) /* 6 = # of preceding `pushP_cfi' */
	leaP   (Pn(6) - OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_R9)(%Psp), %Pcx
	pushP_cfi %Pcx          /* vl_reg_save_area (== &aa_state.kcs_gpregs.gp_r9 - OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_R9) */
	pushP_cfi %Pdx          /* vl_overflow_arg_area (== aa_state.kcs_gpregs.gp_rsp) */
	pushP_cfi $(Pn(5))      /* vl_gp_offset */
	movP   %Psp, %R_fcall0P /* libc_assertion_check_core:args */
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
	INTERN(LOCAL_libc_assertion_failure_core)
	call   LOCAL_libc_assertion_failure_core
	LOCAL_jmp_Lload_kcpustate_Pax
1:	.cfi_restore_state
#endif /* !__NO_FPU */
	movl   $(SIZEOF_X86_64_VA_LIST_REG_SAVE_AREA), OFFSET_X86_64_VA_LIST_STRUCT_FP_OFFSET(%R_fcall0P)
#else /* __x86_64__ */
	/* char const *expr, char const *file, unsigned int line, char const *func, char const *format, ... */

	/* Generate a full `struct kcpustate' */
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R
	leaP   (SIZEOF_KCPUSTATE + Pn(5))(%Psp), %Pax
	pushP_cfi %Pax          /* aa_args */

	movP   %Psp, %R_fcall0P /* LOCAL_libc_assertion_failure_core:args */
#endif /* !__x86_64__ */

	/* Call the high-level handler */
	INTERN(LOCAL_libc_assertion_failure_core)
	call   LOCAL_libc_assertion_failure_core
	LOCAL_jmp_Lload_kcpustate_Pax
	.cfi_endproc
END(LOCAL_libc___afailf)
DEFINE_PUBLIC_ALIAS(LOCAL___afailf, LOCAL_libc___afailf)




/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> __apfail(struct __apfail_struct const *specs); */
.section ASSERTION_SECTION
INTERN_FUNCTION(LOCAL_libc___apfail)
	.cfi_startproc
#ifdef __x86_64__
	/* %R_sysvabi0P: struct __apfail_struct const *specs */
	pushP_cfi struct_apfail__afs_func(%R_sysvabi0P) /* aa_func */
	pushP_cfi struct_apfail__afs_line(%R_sysvabi0P) /* aa_line */
	pushP_cfi struct_apfail__afs_file(%R_sysvabi0P) /* aa_file */
	pushP_cfi struct_apfail__afs_expr(%R_sysvabi0P) /* aa_expr */
	pushP_cfi Pn(4)(%Psp)                           /* aa_state.kcs_Pip */
	.cfi_rel_offset %Pip, 0
	movP   $(0), Pn(5)(%Psp)                        /* aa_format */
	ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(%Pax, Pn(6)) /* 6 = # of preceding `pushP_cfi' */
	subP_imm_cfi SIZEOF_X86_64_VA_LIST_STRUCT, %Psp /* aa_args */
#else /* __x86_64__ */
	/* struct __apfail_struct const *specs */
	subP_imm_cfi Pn(4), %Psp                      /* aa_func, aa_line, aa_file, aa_expr */
	pushP_cfi Pn(4)(%Psp)                         /* aa_state.kcs_Pip */
	.cfi_rel_offset %Pip, 0
	movP   $(0), Pn(5)(%Psp)                      /* aa_format */
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R_EX(Pn(5))  /* 5 = # of preceding `pushP_cfi'+subP_imm_cfi */
	movP   (SIZEOF_KCPUSTATE + Pn(5))(%Psp), %Pcx /* struct __apfail_struct const *specs */
	movP   struct_apfail__afs_expr(%Pcx), %Pax    /* char const *expr */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(0))(%Psp) /* aa_expr */
	movP   struct_apfail__afs_file(%Pcx), %Pax    /* char const *file */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(1))(%Psp) /* aa_file */
	movP   struct_apfail__afs_line(%Pcx), %Pax    /* unsigned int line */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(2))(%Psp) /* aa_line */
	movP   struct_apfail__afs_func(%Pcx), %Pax    /* char const *func */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(3))(%Psp) /* aa_func */
	pushP_cfi $(0)                                /* aa_args */
#endif /* !__x86_64__ */

	/* Call the high-level handler */
	movP   %Psp, %R_fcall0P
	INTERN(LOCAL_libc_assertion_failure_core)
	call   LOCAL_libc_assertion_failure_core
	LOCAL_jmp_Lload_kcpustate_Pax
	.cfi_endproc
END(LOCAL_libc___apfail)
DEFINE_PUBLIC_ALIAS(LOCAL___apfail, LOCAL_libc___apfail)



/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> __apfailf(struct __apfail_struct const *specs,
 * >>           char const *format,
 * >>           ...); */
.section ASSERTION_SECTION
INTERN_FUNCTION(LOCAL_libc___apfailf)
	.cfi_startproc
#ifdef __x86_64__
	/* %R_sysvabi0P: struct __apfail_struct const *specs
	 * %R_sysvabi1P: char const *format
	 * %R_sysvabi2P: VA(0)
	 * %R_sysvabi3P: VA(1)
	 * %R_sysvabi4P: VA(2)
	 * %R_sysvabi5P: VA(3)
	 * 8(%Psp):      VA(4)
	 * 16(%Psp):     VA(5)
	 * ... */
	pushP_cfi %R_sysvabi5P /* vl_reg_save_area... */
	pushP_cfi %R_sysvabi4P /* vl_reg_save_area... */
	pushP_cfi %R_sysvabi3P /* vl_reg_save_area... */
	pushP_cfi %R_sysvabi2P /* vl_reg_save_area... */

	pushP_cfi %R_sysvabi1P  /* aa_format */
	pushP_cfi struct_apfail__afs_func(%R_sysvabi0P)  /* aa_func */
	pushP_cfi struct_apfail__afs_line(%R_sysvabi0P)  /* aa_line */
	pushP_cfi struct_apfail__afs_file(%R_sysvabi0P)  /* aa_file */
	pushP_cfi struct_apfail__afs_expr(%R_sysvabi0P)  /* aa_expr */
	pushP_cfi Pn(9)(%Psp)   /* aa_state.kcs_Pip */
	ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(%Pdx, Pn(10)) /* 10 = # of preceding `pushP_cfi' */
	leaP   ((SIZEOF_KCPUSTATE + Pn(6)) /* [pushP_cfi %R_sysvabi2P] */ \
	        - OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_RDX)(%Psp), %Pcx
	pushP_cfi %Pcx          /* vl_reg_save_area (== [pushP_cfi %R_sysvabi2P] - OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_RDX) */
	pushP_cfi %Pdx          /* vl_overflow_arg_area (== aa_state.kcs_gpregs.gp_rsp) */
	pushP_cfi $(Pn(2))      /* vl_gp_offset */
	movP   %Psp, %R_fcall0P /* libc_assertion_check_core:args */
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
	INTERN(LOCAL_libc_assertion_failure_core)
	call   LOCAL_libc_assertion_failure_core
	LOCAL_jmp_Lload_kcpustate_Pax
1:	.cfi_restore_state
#endif /* !__NO_FPU */
	movl   $(SIZEOF_X86_64_VA_LIST_REG_SAVE_AREA), OFFSET_X86_64_VA_LIST_STRUCT_FP_OFFSET(%R_fcall0P)
#else /* __x86_64__ */
	/* struct __apfail_struct const *specs, char const *format, ...
	 * NOTE: <RETURN_PC>  will become  aa_format */
	subP_imm_cfi Pn(4), %Psp   /* aa_func, aa_line, aa_file, aa_expr */
	pushP_cfi Pn(4)(%Psp)      /* aa_state.kcs_Pip */
	.cfi_rel_offset %Pip, 0
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R_EX(Pn(5))  /* 5 = # of preceding `pushP_cfi'+subP_imm_cfi */
	movP   (SIZEOF_KCPUSTATE + Pn(6))(%Psp), %Pax /* char const *format */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(4))(%Psp) /* aa_format  (was: <RETURN_PC>) */
	movP   (SIZEOF_KCPUSTATE + Pn(5))(%Psp), %Pcx /* struct __apfail_struct const *specs */
	movP   struct_apfail__afs_func(%Pcx), %Pax
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(3))(%Psp) /* aa_func */
	movP   struct_apfail__afs_line(%Pcx), %Pax
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(2))(%Psp) /* aa_line */
	movP   struct_apfail__afs_file(%Pcx), %Pax
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(1))(%Psp) /* aa_file */
	movP   struct_apfail__afs_expr(%Pcx), %Pax
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(0))(%Psp) /* aa_expr */
	leaP   (SIZEOF_KCPUSTATE + Pn(7))(%Psp), %Pax /* va_args */
	pushP_cfi %Pax                                /* aa_args */
	movP   %Psp, %R_fcall0P
#endif /* !__x86_64__ */

	/* Call the high-level handler */
	INTERN(LOCAL_libc_assertion_failure_core)
	call   LOCAL_libc_assertion_failure_core
	LOCAL_jmp_Lload_kcpustate_Pax
	.cfi_endproc
END(LOCAL_libc___apfailf)
DEFINE_PUBLIC_ALIAS(LOCAL___apfailf, LOCAL_libc___apfailf)


#undef LOCAL_jmp_Lload_kcpustate_Pax

#undef LOCAL_libc_assertion_failure_core
#undef LOCAL___afail
#undef LOCAL_libc___afail
#undef LOCAL___afailf
#undef LOCAL_libc___afailf
#undef LOCAL___apfail
#undef LOCAL_libc___apfail
#undef LOCAL___apfailf
#undef LOCAL_libc___apfailf

#undef DEFINE___afail
#undef DEFINE___acheck
