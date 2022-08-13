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

#include <cfi.h>

#ifdef __KERNEL__
#define ASSERTION_SECTION   .text.cold
#else /* __KERNEL__ */
#define ASSERTION_SECTION   .text.crt.assert
#endif /* !__KERNEL__ */

/* >> PUBLIC ATTR_NORETURN void LIBCCALL __stack_chk_fail(void);
 * >> PUBLIC ATTR_NORETURN void LIBCCALL __stack_chk_fail_local(void); */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc_stack_chk_fail)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc_stack_chk_fail)
DEFINE_PUBLIC_ALIAS(__stack_chk_fail, libc_stack_chk_fail)
DEFINE_PUBLIC_ALIAS(__stack_chk_fail_local, libc_stack_chk_fail)


/* >> PUBLIC ATTR_NORETURN void LIBCCALL abort(void); */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc_abort)
	.cfi_startproc
	b      . /* TODO */
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
 * >> __afail(char const *expr,
 * >>         char const *file,
 * >>         unsigned int line,
 * >>         char const *func); */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc___afail)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc___afail)
DEFINE_PUBLIC_ALIAS(__afail, libc___afail)





/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> __afailf(char const *expr,
 * >>          char const *file,
 * >>          unsigned int line,
 * >>          char const *func,
 * >>          char const *format,
 * >>          ...); */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc___afailf)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc___afailf)
DEFINE_PUBLIC_ALIAS(__afailf, libc___afailf)



#if defined(__KERNEL__) || defined(__INTELLISENSE__)
/* Support for __acheck[f]() */

/* >> PUBLIC bool VLIBCCALL
 * >> __acheck(char const *expr,
 * >>          char const *file,
 * >>          unsigned int line,
 * >>          char const *func); */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc___acheck)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc___acheck)
DEFINE_PUBLIC_ALIAS(__acheck, libc___acheck)


/* >> PUBLIC bool VLIBCCALL
 * >> __acheckf(char const *expr,
 * >>           char const *file,
 * >>           unsigned int line,
 * >>           char const *func,
 * >>           char const *format,
 * >>           ...); */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc___acheckf)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc___acheckf)
DEFINE_PUBLIC_ALIAS(__acheckf, libc___acheckf)
#endif /* __KERNEL__ || __INTELLISENSE__ */



#if !defined(__KERNEL__) || defined(__INTELLISENSE__)

DEFINE_INTERN_ALIAS(libc___assert_fail, libc___afail)
DEFINE_PUBLIC_ALIAS(__assert_fail, libc___assert_fail)

/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> __assert_func(char const *file,
 * >>               unsigned int line,
 * >>               char const *func,
 * >>               char const *expr); */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc___assert_func)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc___assert_func)
DEFINE_PUBLIC_ALIAS(__assert_func, libc___assert_func)


/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> __assertfail(char const *expr,
 * >>              char const *file,
 * >>              unsigned int line,
 * >>              char const *func,
 * >>              size_t charsize); */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc___assertfail)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc___assertfail)
DEFINE_PUBLIC_ALIAS(__assertfail, libc___assertfail)



/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> __assert(char const *file,
 * >>          unsigned int line,
 * >>          char const *expr); */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc___assert)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc___assert)
DEFINE_PUBLIC_ALIAS(__assert, libc___assert)



/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> _assert(char const *expr,
 * >>         char const *file,
 * >>         unsigned int line); */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc__assert)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc__assert)
DEFINE_PUBLIC_ALIAS(_assert, libc__assert)


/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> _wassert(char32_t const *expr,
 * >>          char32_t const *file,
 * >>          unsigned int line); */
.section ".text.crt.dos.assert"
INTERN_FUNCTION(libc__wassert)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc__wassert)
DEFINE_PUBLIC_ALIAS(_wassert, libc__wassert)


/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> DOS$_wassert(char16_t const *expr,
 * >>              char16_t const *file,
 * >>              unsigned int line); */
.section ".text.crt.dos.assert"
INTERN_FUNCTION(libd__wassert)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libd__wassert)
DEFINE_PUBLIC_ALIAS(DOS$_wassert, libd__wassert)



/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> __assert_perror_fail(int errnum,
 * >>                      char const *file,
 * >>                      unsigned int line,
 * >>                      char const *func) */
.section ".text.crt.glibc.assert"
INTERN_FUNCTION(libc___assert_perror_fail)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc___assert_perror_fail)
DEFINE_PUBLIC_ALIAS(__assert_perror_fail, libc___assert_perror_fail)

#endif /* !__KERNEL__ || __INTELLISENSE__ */

#endif /* !GUARD_LIBC_HYBRID_ARCH_ARM_ASSERT_S */
