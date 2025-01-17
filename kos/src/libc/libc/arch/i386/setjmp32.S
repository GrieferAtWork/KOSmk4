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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_SETJMP32_S
#define GUARD_LIBC_LIBC_ARCH_I386_SETJMP32_S 1
#define __ASSEMBLER__ 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <hybrid/compiler.h>

#include <cfi.h>

#include <setjmp.h>
#include <signal.h>

#undef setjmp
#undef longjmp

#define OFFSET_JMPBUF_EBX 0
#define OFFSET_JMPBUF_ESP 4
#define OFFSET_JMPBUF_EBP 8
#define OFFSET_JMPBUF_ESI 12
#define OFFSET_JMPBUF_EDI 16
#define OFFSET_JMPBUF_EIP 20
#define OFFSET_JMPBUF_PA0 24
#define OFFSET_JMPBUF_PA1 28
#define OFFSET_JMPBUF_SIG 32

.section .text.crt.utility.setjmp
INTERN_FUNCTION(libc_setjmp)
	.cfi_startproc
	movl   4(%esp), %eax /* jmp_buf */
	movl   %ebx, OFFSET_JMPBUF_EBX(%eax)
	leal   4(%esp), %ecx
	movl   %ecx, OFFSET_JMPBUF_ESP(%eax)
	movl   %ebp, OFFSET_JMPBUF_EBP(%eax)
	movl   %esi, OFFSET_JMPBUF_ESI(%eax)
	movl   %edi, OFFSET_JMPBUF_EDI(%eax)
	movl   0(%esp), %ecx
	movl   %ecx, OFFSET_JMPBUF_EIP(%eax)
	xorl   %ecx, %ecx
	movl   %ecx, OFFSET_JMPBUF_PA0(%eax)
	movl   %ecx, OFFSET_JMPBUF_PA1(%eax)
	movl   %ecx, %eax
	ret
	.cfi_endproc
END(libc_setjmp)
DEFINE_PUBLIC_ALIAS(setjmp, libc_setjmp)
DEFINE_PUBLIC_ALIAS(_setjmp, libc_setjmp)
DEFINE_PUBLIC_ALIAS(__setjmp, libc_setjmp)
DEFINE_PUBLIC_ALIAS(_setjmp3, libc_setjmp)


.section .text.crt.utility.setjmp
INTERN_FUNCTION(libc_longjmp)
	.cfi_startproc
	.cfi_signal_frame
	movl   8(%esp), %eax
	testl  %eax, %eax
	jnz    1f
	incl   %eax
	jmp    1f
INTERN_FUNCTION(libc___fast_longjmp)
	movl   8(%esp), %eax
1:	movl   4(%esp), %ecx
	movl   OFFSET_JMPBUF_EBX(%ecx), %ebx
/*	.cfi_same_value %ebx */
	movl   OFFSET_JMPBUF_ESP(%ecx), %esp
	.cfi_same_value %esp
	movl   OFFSET_JMPBUF_EBP(%ecx), %ebp
/*	.cfi_same_value %ebp */
	movl   OFFSET_JMPBUF_ESI(%ecx), %esi
/*	.cfi_same_value %esi */
	movl   OFFSET_JMPBUF_EDI(%ecx), %edi
/*	.cfi_same_value %edi */
	jmp    *OFFSET_JMPBUF_EIP(%ecx)
	.cfi_endproc
END(libc___fast_longjmp)
END(libc_longjmp)
DEFINE_PUBLIC_ALIAS(longjmp, libc_longjmp)
DEFINE_PUBLIC_ALIAS(_longjmp, libc_longjmp)
DEFINE_PUBLIC_ALIAS(__longjmp, libc_longjmp)
DEFINE_PUBLIC_ALIAS(__libc_longjmp, libc_longjmp)
DEFINE_PUBLIC_ALIAS(__fast_longjmp, libc___fast_longjmp)



.section .text.crt.utility.setjmp
INTERN_FUNCTION(libc__setjmpex)
	.cfi_startproc
	movl   $(1), %edx
	jmp    1f
INTERN_FUNCTION(libc_sigsetjmp)
	movl   8(%esp), %edx /* savemask */
1:	movl   4(%esp), %eax /* jmp_buf */
	movl   %ebx, OFFSET_JMPBUF_EBX(%eax)
	leal   4(%esp), %ecx
	movl   %ecx, OFFSET_JMPBUF_ESP(%eax)
	movl   %ebp, OFFSET_JMPBUF_EBP(%eax)
	movl   %esi, OFFSET_JMPBUF_ESI(%eax)
	movl   %edi, OFFSET_JMPBUF_EDI(%eax)
	movl   0(%esp), %ecx
	movl   %ecx, OFFSET_JMPBUF_EIP(%eax)
	movl   %edx, OFFSET_JMPBUF_PA0(%eax)
	movl   $(0), OFFSET_JMPBUF_PA1(%eax)
	testl  %edx, %edx
	jz     1f
	/* Save the signal mask. */
	leal   OFFSET_JMPBUF_SIG(%eax), %eax
	pushl_cfi %eax             /* sigset_t *oset */
	pushl_cfi $(0)             /* sigset_t const *set */
	pushl_cfi $(SIG_SETMASK)   /* syscall_ulong_t how */
	EXTERN(libc_sigprocmask)
	call   libc_sigprocmask
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
1:	xorl   %eax, %eax
	ret
	.cfi_endproc
END(libc_sigsetjmp)
END(libc__setjmpex)

DEFINE_PUBLIC_ALIAS(_setjmpex, libc__setjmpex)
DEFINE_PUBLIC_ALIAS(sigsetjmp, libc_sigsetjmp)
DEFINE_PUBLIC_ALIAS(__sigsetjmp, libc_sigsetjmp)
DEFINE_PUBLIC_ALIAS(__libc_siglongjmp, libc_sigsetjmp)

.section .text.crt.utility.setjmp
INTERN_FUNCTION(libc_siglongjmp)
	.cfi_startproc
	.cfi_signal_frame
	movl   4(%esp), %ecx
	cmpl   $(0), OFFSET_JMPBUF_PA0(%ecx)
	je     libc_longjmp /* No signal mask */
	/* Restore signal mask */
	leal   OFFSET_JMPBUF_SIG(%ecx), %eax
	pushl_cfi $(0)             /* sigset_t *oset */
	pushl_cfi %eax             /* sigset_t *set */
	pushl_cfi $(SIG_SETMASK)   /* syscall_ulong_t how */
	EXTERN(libc_sigprocmask)
	call   libc_sigprocmask
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	jmp    libc_longjmp
	.cfi_endproc
END(libc_siglongjmp)

DEFINE_PUBLIC_ALIAS(siglongjmp, libc_siglongjmp)
DEFINE_PUBLIC_ALIAS(__siglongjmp, libc_siglongjmp)

#endif /* !GUARD_LIBC_LIBC_ARCH_I386_SETJMP32_S */
