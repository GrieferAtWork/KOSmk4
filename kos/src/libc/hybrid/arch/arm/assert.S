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
#ifndef GUARD_LIBC_HYBRID_ARCH_ARM_ASSERT_S
#define GUARD_LIBC_HYBRID_ARCH_ARM_ASSERT_S 1
#define __ASSEMBLER__ 1
#define _KOS_KERNEL_SOURCE 1

#include <hybrid/compiler.h>

#include <asm/arm.h>
#include <asm/cpu-flags.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>

#include <cfi.h>

#ifdef __KERNEL__
#define ASSERTION_SECTION   .text.cold
#else /* __KERNEL__ */
#define ASSERTION_SECTION   .text.crt.assert
#endif /* !__KERNEL__ */

/* Define offsetof helper macros */
#define aa_args            (0)
#define aa_state           (4)
#define aa_expr            (4 + SIZEOF_KCPUSTATE)
#define aa_errno           (4 + SIZEOF_KCPUSTATE)
#define aa_file            (8 + SIZEOF_KCPUSTATE)
#define aa_line            (12 + SIZEOF_KCPUSTATE)
#define aa_func            (16 + SIZEOF_KCPUSTATE)
#define aa_format          (20 + SIZEOF_KCPUSTATE)
#define sizeof_assert_args (24 + SIZEOF_KCPUSTATE)


/* >> PUBLIC ATTR_NORETURN void LIBCCALL __stack_chk_fail(void);
 * >> PUBLIC ATTR_NORETURN void LIBCCALL __stack_chk_fail_local(void); */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc_stack_chk_fail)
	.cfi_startproc
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R
	mov    r0, sp
#if (SIZEOF_KCPUSTATE % 8) != 0
	sub    sp, sp, #4 /* ensure 8-byte alignment */
#endif /* (SIZEOF_KCPUSTATE % 8) != 0 */

	/* Call the high-level handler */
	EXTERN(libc_stack_failure_core)
	bl     libc_stack_failure_core
	.cfi_endproc
END(libc_stack_chk_fail)
DEFINE_PUBLIC_ALIAS(__stack_chk_fail, libc_stack_chk_fail)
DEFINE_PUBLIC_ALIAS(__stack_chk_fail_local, libc_stack_chk_fail)


/* >> PUBLIC ATTR_NORETURN void LIBCCALL abort(void); */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc_abort)
	.cfi_startproc
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R
	mov    r0, sp
#if (SIZEOF_KCPUSTATE % 8) != 0
	sub    sp, sp, #4 /* ensure 8-byte alignment */
#endif /* (SIZEOF_KCPUSTATE % 8) != 0 */

	/* Call the high-level handler */
	EXTERN(libc_abort_failure_core)
	bl     libc_abort_failure_core
	.cfi_endproc
END(libc_abort)

DEFINE_PUBLIC_ALIAS(abort, libc_abort)

/* Provide debugging facilities for __builtin_unreachable() (s.a. <__crt.h>) */
DEFINE_PUBLIC_ALIAS(__ubsan_handle_builtin_unreachable, libc_abort)
DEFINE_INTERN_ALIAS(libc___ubsan_handle_builtin_unreachable, libc_abort)
DEFINE_PUBLIC_ALIAS(_ZSt9terminatev, libc_abort) /* std::terminate(void) */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(terminate, libc_abort)           /* std::terminate(void) */
DEFINE_PUBLIC_ALIAS("?terminate@@YAXXZ", libc_abort) /* std::terminate(void) */
DEFINE_PUBLIC_ALIAS(__chk_fail, libc_abort)
#endif /* !__KERNEL__ */


/* >> PUBLIC ATTR_NORETURN void LIBCCALL
 * >> __afail(char const *expr,  @ r0
 * >>         char const *file,  @ r1
 * >>         unsigned int line, @ r2
 * >>         char const *func); @ r3 */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc___afail)
	.cfi_startproc
	/* Push `struct assert_args' */
	push_cfi {r0,r1,r2,r3,r12}         /* `aa_expr', `aa_file', `aa_line', `aa_func', [r12: placeholder for `aa_format'] */
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R  /* `aa_state' */
	mov    r12, #0
	push_cfi {r12}                     /* `aa_args' */
	str    r12, [sp, #aa_format]       /* override `aa_format' with NULL */
#if (sizeof_assert_args % 8) != 0
	sub    sp, sp, #4 /* ensure 8-byte alignment */
#endif /* (sizeof_assert_args % 8) != 0 */

	/* Call the high-level handler */
	mov    r0, sp
	INTERN(libc_assertion_failure_core)
	bl     libc_assertion_failure_core
	.cfi_endproc
END(libc___afail)
DEFINE_PUBLIC_ALIAS(__afail, libc___afail)





/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> __afailf(char const *expr,   @ r0
 * >>          char const *file,   @ r1
 * >>          unsigned int line,  @ r2
 * >>          char const *func,   @ r3
 * >>          char const *format, @ [sp, #0]
 * >>          ...); */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc___afailf)
	.cfi_startproc
	/* Push `struct assert_args' */
	push_cfi {r0,r1,r2,r3,r12}         /* `aa_expr', `aa_file', `aa_line', `aa_func', [r12: placeholder for `aa_format'] */
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R  /* `aa_state' */
	ldr    r12, [sp, #(sizeof_assert_args - 4)]
	str    r12, [sp, #(aa_format - 4)] /* Copy `format' argument into `aa_format' */
	add    r12, sp, #(sizeof_assert_args - 4 + 4) /* Pointer to varargs */
	push_cfi {r12}                     /* `aa_args' */
#if (sizeof_assert_args % 8) != 0
	sub    sp, sp, #4 /* ensure 8-byte alignment */
#endif /* (sizeof_assert_args % 8) != 0 */

	/* Call the high-level handler */
	mov    r0, sp
	INTERN(libc_assertion_failure_core)
	bl     libc_assertion_failure_core
	.cfi_endproc
END(libc___afailf)
DEFINE_PUBLIC_ALIAS(__afailf, libc___afailf)



#if defined(__KERNEL__) || defined(__INTELLISENSE__)
/* Support for __acheck[f]() */

/* >> PUBLIC bool VLIBCCALL
 * >> __acheck(char const *expr,  @ r0
 * >>          char const *file,  @ r1
 * >>          unsigned int line, @ r2
 * >>          char const *func); @ r3 */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc___acheck)
	.cfi_startproc
	/* Push `struct assert_args' */
	push_cfi {r0,r1,r2,r3,r12}         /* `aa_expr', `aa_file', `aa_line', `aa_func', [r12: placeholder for `aa_format'] */
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R  /* `aa_state' */
	mov    r12, #0
	push_cfi {r12}                     /* `aa_args' */
	str    r12, [sp, #aa_format]       /* override `aa_format' with NULL */
#if (sizeof_assert_args % 8) != 0
	sub    sp, sp, #4 /* ensure 8-byte alignment */
#endif /* (sizeof_assert_args % 8) != 0 */

	/* Call the high-level handler */
	mov    r0, sp
	INTERN(libc_assertion_check_core)
	bl     libc_assertion_check_core
	nop    /* For tracebacks */

.Lload_kcpustate_r0:
	.cfi_def_cfa r0, 0
	ASM_CFI_OFFSET_RESTORE_KCPUSTATE(0)
	ldr    lr, [r0, #OFFSET_KCPUSTATE_PC]
	ldr    r1, [r0, #OFFSET_KCPUSTATE_CPSR]
	tst    r1, #CPSR_T
	orrne  lr, #1         /* Set THUMB bit */
	add    r0, r0, #OFFSET_KCPUSTATE_R1
	.cfi_adjust_cfa_offset -OFFSET_KCPUSTATE_R1
	msr    APSR_nzcvq, r1 /* Load APSR flags (ignoring flags from CPSR) */
/*[[[cfi{arch='arm', register='%cpsr'}
	# Encode how the THUMB bit should be restored
	push   %cpsr     # [%cpsr]
	push   %lr       # [%cpsr, %lr]
	and    $1        # [%cpsr, %lr & 1]
	jf     pop, 1f   # [%cpsr]
	or     $CPSR_T   # [%cpsr | CPSR_T]
1:]]]*/
	.cfi_escape 22,128,1,15,146,128,1,0,126,0,49,26,32,40,3,0
	.cfi_escape 9,32,33
/*[[[end]]]*/
/*[[[cfi{arch='arm', register='%pc'}
	# Encode how to restore 'pc'
	push   %lr       # [%lr]
	and    ~$1       # [%lr & ~1]
1:]]]*/
	.cfi_escape 22,15,5,126,0,9,254,26
/*[[[end]]]*/
	ldm    r0, {r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12} /* Restore GP registers */
	.cfi_restore r1; .cfi_restore r2; .cfi_restore r3; .cfi_restore r4;  .cfi_restore r5;  .cfi_restore r6
	.cfi_restore r7; .cfi_restore r8; .cfi_restore r9; .cfi_restore r10; .cfi_restore r11; .cfi_restore r12
	ldr    sp, [r0, #(OFFSET_KCPUSTATE_SP - OFFSET_KCPUSTATE_R1)] /* Restore stack */
	.cfi_restore sp
	ldr    r0, [r0, #(OFFSET_KCPUSTATE_R0 - OFFSET_KCPUSTATE_R1)] /* Restore r0 */
	bx     lr             /* Resume execution */
	.cfi_endproc
END(libc___acheck)
DEFINE_PUBLIC_ALIAS(__acheck, libc___acheck)


/* >> PUBLIC bool VLIBCCALL
 * >> __acheckf(char const *expr,   @ r0
 * >>           char const *file,   @ r1
 * >>           unsigned int line,  @ r2
 * >>           char const *func,   @ r3
 * >>           char const *format, @ [sp, #0]
 * >>           ...); */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc___acheckf)
	.cfi_startproc
	/* Push `struct assert_args' */
	push_cfi {r0,r1,r2,r3,r12}         /* `aa_expr', `aa_file', `aa_line', `aa_func', [r12: placeholder for `aa_format'] */
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R  /* `aa_state' */
	ldr    r12, [sp, #(sizeof_assert_args - 4)]
	str    r12, [sp, #(aa_format - 4)] /* Copy `format' argument into `aa_format' */
	add    r12, sp, #(sizeof_assert_args - 4 + 4) /* Pointer to varargs */
	push_cfi {r12}                     /* `aa_args' */
#if (sizeof_assert_args % 8) != 0
	sub    sp, sp, #4 /* ensure 8-byte alignment */
#endif /* (sizeof_assert_args % 8) != 0 */

	/* Call the high-level handler */
	mov    r0, sp
	INTERN(libc_assertion_check_core)
	bl     libc_assertion_check_core

	/* Load the returned CPU state */
	b      .Lload_kcpustate_r0
	.cfi_endproc
END(libc___acheckf)
DEFINE_PUBLIC_ALIAS(__acheckf, libc___acheckf)
#endif /* __KERNEL__ || __INTELLISENSE__ */



#if !defined(__KERNEL__) || defined(__INTELLISENSE__)

DEFINE_INTERN_ALIAS(libc___assert_fail, libc___afail)
DEFINE_PUBLIC_ALIAS(__assert_fail, libc___assert_fail)

/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> __assert_func(char const *file,  @ r0
 * >>               unsigned int line, @ r1
 * >>               char const *func,  @ r2
 * >>               char const *expr); @ r3 */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc___assert_func)
	.cfi_startproc
	/* Push `struct assert_args' */
	push_cfi {r0,r1,r2,r12}            /* `aa_file', `aa_line', `aa_func', [r12: placeholder for `aa_format'] */
	push_cfi {r3}                      /* `aa_expr' */
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R  /* `aa_state' */
	mov    r12, #0
	push_cfi {r12}                     /* `aa_args' */
	str    r12, [sp, #aa_format]       /* override `aa_format' with NULL */
#if (sizeof_assert_args % 8) != 0
	sub    sp, sp, #4 /* ensure 8-byte alignment */
#endif /* (sizeof_assert_args % 8) != 0 */

	/* Call the high-level handler */
	mov    r0, sp
	INTERN(libc_assertion_failure_core)
	bl     libc_assertion_failure_core
	.cfi_endproc
END(libc___assert_func)
DEFINE_PUBLIC_ALIAS(__assert_func, libc___assert_func)


/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> __assertfail(char const *expr,  @ r0
 * >>              char const *file,  @ r1
 * >>              unsigned int line, @ r2
 * >>              char const *func,  @ r3
 * >>              size_t charsize);  @ [sp, #0] */
DEFINE_INTERN_ALIAS(libc___assertfail, libc___afail)



/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> __assert(char const *file,  @ r0
 * >>          unsigned int line, @ r1
 * >>          char const *expr); @ r2 */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc___assert)
	.cfi_startproc
	/* Push `struct assert_args' */
	push_cfi {r0,r1,r11,r12}           /* `aa_file', `aa_line', [r11: placeholder for `aa_func'], [r12: placeholder for `aa_format'] */
	push_cfi {r2}                      /* `aa_expr' */
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R  /* `aa_state' */
	mov    r12, #0
	push_cfi {r12}                     /* `aa_args' */
	str    r12, [sp, #aa_func]         /* override `aa_func' with NULL */
	str    r12, [sp, #aa_format]       /* override `aa_format' with NULL */
#if (sizeof_assert_args % 8) != 0
	sub    sp, sp, #4 /* ensure 8-byte alignment */
#endif /* (sizeof_assert_args % 8) != 0 */

	/* Call the high-level handler */
	mov    r0, sp
	INTERN(libc_assertion_failure_core)
	bl     libc_assertion_failure_core
	.cfi_endproc
END(libc___assert)
DEFINE_PUBLIC_ALIAS(__assert, libc___assert)



/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> _assert(char const *expr,   @ r0
 * >>         char const *file,   @ r1
 * >>         unsigned int line); @ r2 */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc__assert)
	.cfi_startproc
	/* Push `struct assert_args' */
	push_cfi {r0,r1,r2,r11,r12}        /* `aa_expr', `aa_file', `aa_line', [r11: placeholder for `aa_func'], [r12: placeholder for `aa_format'] */
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R  /* `aa_state' */
	mov    r12, #0
	push_cfi {r12}                     /* `aa_args' */
	str    r12, [sp, #aa_func]         /* override `aa_func' with NULL */
	str    r12, [sp, #aa_format]       /* override `aa_format' with NULL */
#if (sizeof_assert_args % 8) != 0
	sub    sp, sp, #4 /* ensure 8-byte alignment */
#endif /* (sizeof_assert_args % 8) != 0 */

	/* Call the high-level handler */
	mov    r0, sp
	INTERN(libc_assertion_failure_core)
	bl     libc_assertion_failure_core
	.cfi_endproc
END(libc__assert)
DEFINE_PUBLIC_ALIAS(_assert, libc__assert)


/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> _wassert(char32_t const *expr, @ r0
 * >>          char32_t const *file, @ r1
 * >>          unsigned int line);   @ r2 */
.section ".text.crt.dos.assert"
INTERN_FUNCTION(libc__wassert)
	.cfi_startproc
	/* Push `struct assert_args' */
	push_cfi {r0,r1,r2,r11,r12}        /* `aa_expr', `aa_file', `aa_line', [r11: placeholder for `aa_func'], [r12: placeholder for `aa_format'] */
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R  /* `aa_state' */
	mov    r12, #0
	push_cfi {r12}                     /* `aa_args' */
	str    r12, [sp, #aa_func]         /* override `aa_func' with NULL */
	str    r12, [sp, #aa_format]       /* override `aa_format' with NULL */
#if (sizeof_assert_args % 8) != 0
	sub    sp, sp, #4 /* ensure 8-byte alignment */
#endif /* (sizeof_assert_args % 8) != 0 */

	/* Call the high-level handler */
	mov    r0, sp
	INTERN(libc_assertion_failure_core_c32)
	bl     libc_assertion_failure_core_c32
	.cfi_endproc
END(libc__wassert)
DEFINE_PUBLIC_ALIAS(_wassert, libc__wassert)


/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> DOS$_wassert(char16_t const *expr, @ r0
 * >>              char16_t const *file, @ r1
 * >>              unsigned int line);   @ r2 */
.section ".text.crt.dos.assert"
INTERN_FUNCTION(libd__wassert)
	.cfi_startproc
	/* Push `struct assert_args' */
	push_cfi {r0,r1,r2,r11,r12}        /* `aa_expr', `aa_file', `aa_line', [r11: placeholder for `aa_func'], [r12: placeholder for `aa_format'] */
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R  /* `aa_state' */
	mov    r12, #0
	push_cfi {r12}                     /* `aa_args' */
	str    r12, [sp, #aa_func]         /* override `aa_func' with NULL */
	str    r12, [sp, #aa_format]       /* override `aa_format' with NULL */
#if (sizeof_assert_args % 8) != 0
	sub    sp, sp, #4 /* ensure 8-byte alignment */
#endif /* (sizeof_assert_args % 8) != 0 */

	/* Call the high-level handler */
	mov    r0, sp
	INTERN(libc_assertion_failure_core_c16)
	bl     libc_assertion_failure_core_c16
	.cfi_endproc
END(libd__wassert)
DEFINE_PUBLIC_ALIAS(DOS$_wassert, libd__wassert)



/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> __assert_perror_fail(int errnum,        @ r0
 * >>                      char const *file,  @ r1
 * >>                      unsigned int line, @ r2
 * >>                      char const *func)  @ r3 */
.section ".text.crt.glibc.assert"
INTERN_FUNCTION(libc___assert_perror_fail)
	.cfi_startproc
	/* Push `struct assert_args' */
	push_cfi {r0,r1,r2,r3,r12}         /* `aa_errno', `aa_file', `aa_line', `aa_func', [r12: placeholder for `aa_format'] */
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R  /* `aa_state' */
	mov    r12, #0
	push_cfi {r12}                     /* `aa_args' */
	str    r12, [sp, #aa_format]       /* override `aa_format' with NULL */
#if (sizeof_assert_args % 8) != 0
	sub    sp, sp, #4 /* ensure 8-byte alignment */
#endif /* (sizeof_assert_args % 8) != 0 */

	/* Call the high-level handler */
	mov    r0, sp
	INTERN(libc_assertion_failure_perror)
	bl     libc_assertion_failure_perror
	.cfi_endproc
END(libc___assert_perror_fail)
DEFINE_PUBLIC_ALIAS(__assert_perror_fail, libc___assert_perror_fail)

#endif /* !__KERNEL__ || __INTELLISENSE__ */

#endif /* !GUARD_LIBC_HYBRID_ARCH_ARM_ASSERT_S */
