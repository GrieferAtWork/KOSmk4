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
#include <hybrid/compiler.h>
#include <asm/cfi.h>
#include <kos/kernel/cpu-state.h>
#include <asm/cpu-flags.h>


#ifdef __KERNEL__
#define ASSERTION_SECTION(n)   .text.cold
#else /* __KERNEL__ */
#define ASSERTION_SECTION(n)   .text.crt.assert.n
#endif /* !__KERNEL__ */
#define ADJUST_ESP(additional_offset) \
	addl   $(((SIZEOF_KCPUSTATE - OFFSET_KCPUSTATE_GPREGS) - OFFSET_KCPUSTATE_EFLAGS) + (additional_offset)), \
	          OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP(%esp)



.section ASSERTION_SECTION(__stack_chk_fail)
PUBLIC_FUNCTION(__stack_chk_fail)
	.cfi_startproc
	/* Generate a full `struct kcpustate' */
	pushfl_cfi_r
	pushal_cfi_r
	ADJUST_ESP(0)
	movl   %esp, %ecx
	INTERN(libc_stack_failure_core)
	call   libc_stack_failure_core
	.cfi_endproc
END(__stack_chk_fail)
DEFINE_INTERN_ALIAS(__stack_chk_fail_local, __stack_chk_fail)

.section ASSERTION_SECTION(abort)
INTERN_FUNCTION(libc_abort)
	.cfi_startproc
	/* Generate a full `struct kcpustate' */
	pushfl_cfi_r
	pushal_cfi_r
	ADJUST_ESP(0)
	movl   %esp, %ecx
	INTERN(libc_abort_failure_core)
	call   libc_abort_failure_core
	.cfi_endproc
END(libc_abort)

DEFINE_PUBLIC_ALIAS(_ZSt9terminatev, libc_abort) /* std::terminate(void) */
DEFINE_PUBLIC_ALIAS(abort, libc_abort)
/* Provide debugging facilities for __builtin_unreachable() (s.a. <__crt.h>) */
DEFINE_PUBLIC_ALIAS(__crt_unreachable, libc_abort)
DEFINE_INTERN_ALIAS(libc___crt_unreachable, libc_abort)


.section ASSERTION_SECTION(__afail)
INTERN_FUNCTION(libc___afail)
	.cfi_startproc
	/* char const *expr, char const *file, unsigned int line, char const *func */
	pushl  0(%esp)  /* RETURN_PC */
	.cfi_def_cfa %esp, 4
	.cfi_rel_offset %eip, 0
	pushfl_cfi_r
	pushal_cfi_r
	ADJUST_ESP(4)
	movl   SIZEOF_KCPUSTATE+4(%esp), %eax  /* char const *expr */
	movl   %eax, SIZEOF_KCPUSTATE+0(%esp)  /* aa_expr */
	movl   SIZEOF_KCPUSTATE+8(%esp), %eax  /* char const *file */
	movl   %eax, SIZEOF_KCPUSTATE+4(%esp)  /* aa_file */
	movl   SIZEOF_KCPUSTATE+12(%esp), %eax /* unsigned int line */
	movl   %eax, SIZEOF_KCPUSTATE+8(%esp)  /* aa_line */
	movl   SIZEOF_KCPUSTATE+16(%esp), %eax /* char const *func */
	movl   %eax, SIZEOF_KCPUSTATE+12(%esp) /* aa_func */
	movl   $0, SIZEOF_KCPUSTATE+16(%esp)   /* aa_format */
	pushl_cfi $0                           /* aa_args */
	movl   %esp, %ecx
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
	.cfi_endproc
END(libc___afail)
DEFINE_PUBLIC_ALIAS(__afail, libc___afail)

.section ASSERTION_SECTION(__afailf)
INTERN_FUNCTION(libc___afailf)
	.cfi_startproc
	/* char const *expr, char const *file, unsigned int line, char const *func, char const *format */
	pushfl_cfi_r
	pushal_cfi_r
	ADJUST_ESP(0) /* This one is CDECL, so we never need to adjust for argument count! */
	leal   SIZEOF_KCPUSTATE+20(%esp), %eax
	pushl_cfi %eax                         /* aa_args */
	movl   %esp, %ecx
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
	.cfi_endproc
END(libc___afailf)
DEFINE_PUBLIC_ALIAS(__afailf, libc___afailf)




#ifdef __KERNEL__
/* Support for __acheck[f]() */

.section ASSERTION_SECTION(__acheck)
INTERN_FUNCTION(libc___acheck)
	.cfi_startproc
	/* char const *expr, char const *file, unsigned int line, char const *func */
	pushl  0(%esp)  /* RETURN_PC */
	.cfi_def_cfa %esp, 4
	.cfi_rel_offset %eip, 0
	pushfl_cfi_r
	pushal_cfi_r
	ADJUST_ESP(4)
	movl   SIZEOF_KCPUSTATE+4(%esp), %eax  /* char const *expr */
	movl   %eax, SIZEOF_KCPUSTATE+0(%esp)  /* aa_expr */
	movl   SIZEOF_KCPUSTATE+8(%esp), %eax  /* char const *file */
	movl   %eax, SIZEOF_KCPUSTATE+4(%esp)  /* aa_file */
	movl   SIZEOF_KCPUSTATE+12(%esp), %eax /* unsigned int line */
	movl   %eax, SIZEOF_KCPUSTATE+8(%esp)  /* aa_line */
	movl   SIZEOF_KCPUSTATE+16(%esp), %eax /* char const *func */
	movl   %eax, SIZEOF_KCPUSTATE+12(%esp) /* aa_func */
	movl   $0, SIZEOF_KCPUSTATE+16(%esp)   /* aa_format */
	pushl_cfi $0                           /* aa_args */
	movl   %esp, %ecx
	INTERN(libc_assertion_check_core)
	call   libc_assertion_check_core
	.cfi_endproc
.Lload_kcpustate_eax:
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %esp, 0
	.cfi_reg_offset %eax, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EAX, %eax
	.cfi_reg_offset %ecx, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_ECX, %eax
	.cfi_reg_offset %edx, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EDX, %eax
	.cfi_reg_offset %ebx, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EBX, %eax
	.cfi_reg_offset %esp, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_ESP, %eax
	.cfi_reg_offset %ebp, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EBP, %eax
	.cfi_reg_offset %esi, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_ESI, %eax
	.cfi_reg_offset %edi, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EDI, %eax
	.cfi_reg_offset %eflags, OFFSET_KCPUSTATE_EFLAGS, %eax
	.cfi_reg_offset %eip, OFFSET_KCPUSTATE_EIP, %eax
	movl   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_ECX(%eax), %ecx
	.cfi_same_value %ecx
	movl   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EDX(%eax), %edx
	.cfi_same_value %edx
	movl   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EBX(%eax), %ebx
	.cfi_same_value %ebx
	movl   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_ESP(%eax), %esp
	.cfi_same_value %esp
	movl   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EBP(%eax), %ebp
	.cfi_same_value %ebp
	movl   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_ESI(%eax), %esi
	.cfi_same_value %esi
	movl   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EDI(%eax), %edi
	.cfi_same_value %edi
	pushl  OFFSET_KCPUSTATE_EIP(%eax)
	.cfi_reg_value %esp, 4, %esp
	pushl  OFFSET_KCPUSTATE_EFLAGS(%eax)
	.cfi_reg_value %esp, 8, %esp
	.cfi_reg_offset %eflags, 0, %esp
	.cfi_reg_offset %eip, 4, %esp
	movl   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EAX(%eax), %eax
	.cfi_same_value %eax
	popfl
	.cfi_same_value %eflags
	.cfi_reg_value %esp, 4, %esp
	.cfi_reg_offset %eip, 0, %esp
	ret
	.cfi_endproc
END(libc___acheck)
DEFINE_PUBLIC_ALIAS(__acheck, libc___acheck)

.section ASSERTION_SECTION(__acheckf)
INTERN_FUNCTION(libc___acheckf)
	.cfi_startproc
	/* char const *expr, char const *file, unsigned int line, char const *func, char const *format */
	pushfl_cfi_r
	pushal_cfi_r
	ADJUST_ESP(0) /* This one is CDECL, so we never need to adjust for argument count! */
	leal   SIZEOF_KCPUSTATE+20(%esp), %eax
	pushl_cfi %eax                         /* aa_args */
	movl   %esp, %ecx
	INTERN(libc_assertion_check_core)
	call   libc_assertion_check_core
	jmp    .Lload_kcpustate_eax
	.cfi_endproc
END(libc___acheckf)
DEFINE_PUBLIC_ALIAS(__acheckf, libc___acheckf)
#endif /* __KERNEL__ */



#ifndef __KERNEL__
DEFINE_INTERN_ALIAS(libc___assert_fail, libc___afail)
DEFINE_PUBLIC_ALIAS(__assert_fail, libc___assert_fail)

.section ASSERTION_SECTION(__assert_func)
INTERN_FUNCTION(libc___assert_func)
	.cfi_startproc
	/* char const *file, unsigned int line, char const *func, char const *expr */
	pushl  0(%esp)  /* RETURN_PC */
	.cfi_def_cfa %esp, 4
	.cfi_rel_offset %eip, 0
	pushfl_cfi_r
	pushal_cfi_r
	ADJUST_ESP(4)
	movl   SIZEOF_KCPUSTATE+16(%esp), %eax /* char const *expr */
	movl   %eax, SIZEOF_KCPUSTATE+0(%esp)  /* aa_expr */
	movl   $0, SIZEOF_KCPUSTATE+16(%esp)   /* aa_format */
	pushl_cfi $0                           /* aa_args */
	movl   %esp, %ecx
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
	.cfi_endproc
END(libc___assert_func)
DEFINE_PUBLIC_ALIAS(__assert_func, libc___assert_func)


.section ASSERTION_SECTION(__assertfail)
INTERN_FUNCTION(libc___assertfail)
	.cfi_startproc
	/* char const *expr, char const *file, unsigned int line, char const *func, size_t charsize */
	pushfl_cfi_r
	pushal_cfi_r
	ADJUST_ESP(0)
	movl   $0, SIZEOF_KCPUSTATE+16(%esp)   /* aa_format */
	pushl_cfi $0                           /* aa_args */
	movl   %esp, %ecx
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
	.cfi_endproc
END(libc___assertfail)
DEFINE_PUBLIC_ALIAS(__assertfail, libc___assertfail)



.section ASSERTION_SECTION(__assert)
INTERN_FUNCTION(libc___assert)
	.cfi_startproc
	/* char const *file, unsigned int line, char const *expr */
	pushl  0(%esp)  /* RETURN_PC */
	.cfi_def_cfa %esp, 4
	.cfi_rel_offset %eip, 0
	pushl  0(%esp)  /* RETURN_PC */
	.cfi_def_cfa %esp, 8
	.cfi_rel_offset %eip, 0
	pushfl_cfi_r
	pushal_cfi_r
	ADJUST_ESP(8)
	/*                -,                -, char const  *file, unsigned int line, char const *expr */
	/* char const *expr, char const *file, unsigned int line, char const  *func, char const *format */
	movl   SIZEOF_KCPUSTATE+8(%esp), %eax  /* char const *file */
	movl   %eax, SIZEOF_KCPUSTATE+4(%esp)  /* aa_file */
	movl   SIZEOF_KCPUSTATE+12(%esp), %eax /* unsigned int line */
	movl   %eax, SIZEOF_KCPUSTATE+8(%esp)  /* aa_line */
	movl   SIZEOF_KCPUSTATE+16(%esp), %eax /* char const *expr */
	movl   %eax, SIZEOF_KCPUSTATE+0(%esp)  /* aa_expr */
	movl   $0, SIZEOF_KCPUSTATE+12(%esp)   /* aa_func */
	movl   $0, SIZEOF_KCPUSTATE+16(%esp)   /* aa_format */
	pushl_cfi $0                           /* aa_args */
	movl   %esp, %ecx
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
	.cfi_endproc
END(libc___assert)
DEFINE_PUBLIC_ALIAS(__assert, libc___assert)



.section ASSERTION_SECTION(_assert)
INTERN_FUNCTION(libc__assert)
	.cfi_startproc
	/* char const *expr, char const *file, unsigned int line */
	pushl  0(%esp)  /* RETURN_PC */
	.cfi_def_cfa %esp, 4
	.cfi_rel_offset %eip, 0
	pushl  0(%esp)  /* RETURN_PC */
	.cfi_def_cfa %esp, 8
	.cfi_rel_offset %eip, 0
	pushfl_cfi_r
	pushal_cfi_r
	ADJUST_ESP(8)
	/*                -,                -, char const  *expr, char const *file, unsigned int line */
	/* char const *expr, char const *file, unsigned int line, char const *func, char const  *format */
	movl   SIZEOF_KCPUSTATE+8(%esp), %eax  /* char const *expr */
	movl   %eax, SIZEOF_KCPUSTATE+0(%esp)  /* aa_expr */
	movl   SIZEOF_KCPUSTATE+12(%esp), %eax /* char const *file */
	movl   %eax, SIZEOF_KCPUSTATE+4(%esp)  /* aa_file */
	movl   SIZEOF_KCPUSTATE+16(%esp), %eax /* unsigned int line */
	movl   %eax, SIZEOF_KCPUSTATE+8(%esp)  /* aa_line */
	movl   $0, SIZEOF_KCPUSTATE+12(%esp)   /* aa_func */
	movl   $0, SIZEOF_KCPUSTATE+16(%esp)   /* aa_format */
	pushl_cfi $0                           /* aa_args */
	movl   %esp, %ecx
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
	.cfi_endproc
END(libc__assert)
DEFINE_PUBLIC_ALIAS(_assert, libc__assert)
#endif /* !__KERNEL__ */






