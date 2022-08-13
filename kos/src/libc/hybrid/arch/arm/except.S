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
#ifndef GUARD_LIBC_HYBRID_ARCH_ARM_EXCEPT32_S
#define GUARD_LIBC_HYBRID_ARCH_ARM_EXCEPT32_S 1
#define __ASSEMBLER__ 1
#define _KOS_KERNEL_SOURCE 1

#include <hybrid/compiler.h>

#include <asm/arm.h>

#include <cfi.h>

#ifdef __KERNEL__
#define SECTION_EXCEPT_TEXT .text
#else /* __KERNEL__ */
#define SECTION_EXCEPT_TEXT .text.crt.except
#endif /* !__KERNEL__ */


/* PUBLIC ATTR_NORETURN void except_rethrow(void); */
.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(except_rethrow, libc_except_rethrow)
INTERN_FUNCTION(libc_except_rethrow)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc_except_rethrow)

/* This function is called when the c++ `throw;' expression is used. */
DEFINE_PUBLIC_WEAK_ALIAS(__cxa_rethrow, libc_except_rethrow)

#ifdef __KERNEL__
/* NOTE: _Unwind_Resume() is more akin to deemon's `end finally' instruction
  *      (with the exception of not being invoked when a finally wasn't entered
 *       because of an exception), rather than `except_rethrow()', which is
 *       equivalent to `throw except'.
 *       However, since kernel exception handling is rather simplistic, we can
 *       simply handle it the same way we handle rethrow, except that we mustn't
 *       set the `EXCEPT_FRETHROW' flag. */
.section .text
INTERN_FUNCTION(libc_Unwind_Resume)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc_Unwind_Resume)
DEFINE_PUBLIC_ALIAS(_Unwind_Resume, libc_Unwind_Resume)

#else /* __KERNEL__ */

.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_RaiseException)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc_Unwind_RaiseException)
DEFINE_PUBLIC_ALIAS(_Unwind_RaiseException, libc_Unwind_RaiseException)

.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_Resume)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc_Unwind_Resume)
DEFINE_PUBLIC_ALIAS(_Unwind_Resume, libc_Unwind_Resume)


.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_Resume_or_Rethrow)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc_Unwind_Resume_or_Rethrow)
DEFINE_PUBLIC_ALIAS(_Unwind_Resume_or_Rethrow, libc_Unwind_Resume_or_Rethrow)


.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_ForcedUnwind)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc_Unwind_ForcedUnwind)
DEFINE_PUBLIC_ALIAS(_Unwind_ForcedUnwind, libc_Unwind_ForcedUnwind)


.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_Backtrace)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc_Unwind_Backtrace)
DEFINE_PUBLIC_ALIAS(_Unwind_Backtrace, libc_Unwind_Backtrace)


.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_except_handler3)
	.cfi_startproc simple
	b      . /* TODO */
	.cfi_endproc
END(libc_except_handler3)
DEFINE_PUBLIC_ALIAS(except_handler3, libc_except_handler3)

.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_except_handler4)
	.cfi_startproc simple
	b      . /* TODO */
	.cfi_endproc
END(libc_except_handler4)
DEFINE_PUBLIC_ALIAS(except_handler4, libc_except_handler4)

#endif /* !__KERNEL__ */



/* PUBLIC ATTR_NORETURN void except_thrown(except_code_t code, unsigned int argc, ...); */
.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(except_thrown, libc_except_thrown)
INTERN_FUNCTION(libc_except_thrown)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc_except_thrown)



/* PUBLIC ATTR_NORETURN void FCALL except_throw(except_code_t code); */
.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(except_throw, libc_except_throw)
INTERN_FUNCTION(libc_except_throw)
	.cfi_startproc
	b      . /* TODO */
DEFINE_PUBLIC_ALIAS(except_throw_current, libc_except_throw_current)
INTERN_FUNCTION(libc_except_throw_current)
	b      . /* TODO */
END(libc_except_throw_current)
	.cfi_endproc
END(libc_except_throw)


.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(_except_check_no_nesting, libc__except_check_no_nesting)
INTERN_FUNCTION(libc__except_check_no_nesting)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc__except_check_no_nesting)

.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(_except_badusage_no_nesting, libc__except_badusage_no_nesting)
INTERN_FUNCTION(libc__except_badusage_no_nesting)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc__except_badusage_no_nesting)



/* ARM-specific exception-related functions */
.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(__aeabi_unwind_cpp_pr0, libc___aeabi_unwind_cpp_pr0)
INTERN_FUNCTION(libc___aeabi_unwind_cpp_pr0)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc___aeabi_unwind_cpp_pr0)

.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(__aeabi_unwind_cpp_pr1, libc___aeabi_unwind_cpp_pr1)
INTERN_FUNCTION(libc___aeabi_unwind_cpp_pr1)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc___aeabi_unwind_cpp_pr1)

.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(__cxa_end_cleanup, libc___cxa_end_cleanup)
INTERN_FUNCTION(libc___cxa_end_cleanup)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc___cxa_end_cleanup)


#endif /* !GUARD_LIBC_HYBRID_ARCH_ARM_EXCEPT32_S */
