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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_SETJMP64_S
#define GUARD_LIBC_LIBC_ARCH_I386_SETJMP64_S 1
#define __ASSEMBLER__ 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <hybrid/compiler.h>

#include <cfi.h>

#include <setjmp.h>
#include <signal.h>

#undef setjmp
#undef longjmp


#define OFFSET_JMPBUF_RBX    0
#define OFFSET_JMPBUF_RBP    8
#define OFFSET_JMPBUF_R12    16
#define OFFSET_JMPBUF_R13    24
#define OFFSET_JMPBUF_R14    32
#define OFFSET_JMPBUF_R15    40
#define OFFSET_JMPBUF_RSP    48
#define OFFSET_JMPBUF_RIP    56
#define OFFSET_JMPBUF_HASSIG 64
#define OFFSET_JMPBUF_SIG    72

.section .text.crt.utility.setjmp
INTERN_FUNCTION(libc_setjmp)
	.cfi_startproc
	movq   %rbx, OFFSET_JMPBUF_RBX(%rdi)
	movq   %rbp, OFFSET_JMPBUF_RBP(%rdi)
	movq   %r12, OFFSET_JMPBUF_R12(%rdi)
	movq   %r13, OFFSET_JMPBUF_R13(%rdi)
	movq   %r14, OFFSET_JMPBUF_R14(%rdi)
	movq   %r15, OFFSET_JMPBUF_R15(%rdi)
	leaq   8(%rsp), %rax
	movq   %rax, OFFSET_JMPBUF_RSP(%rdi)
	popq_cfi %rcx
	.cfi_register %rip, %rcx
	movq   %rcx, OFFSET_JMPBUF_RIP(%rdi)
	xorq   %rax, %rax
	jmp    *%rcx
	.cfi_endproc
END(libc_setjmp)
DEFINE_PUBLIC_ALIAS(setjmp, libc_setjmp)
DEFINE_PUBLIC_ALIAS(_setjmp, libc_setjmp)
DEFINE_PUBLIC_ALIAS(__setjmp, libc_setjmp)


.section .text.crt.utility.setjmp
INTERN_FUNCTION(libc_longjmp)
	.cfi_startproc
	.cfi_signal_frame__entry
	testq  %rsi, %rsi
	jnz    libc___fast_longjmp
	incq   %rsi
INTERN_FUNCTION(libc___fast_longjmp)
	movq   OFFSET_JMPBUF_RSP(%rdi), %rsp
	.cfi_same_value %rsp
	movq   OFFSET_JMPBUF_R15(%rdi), %r15
	movq   OFFSET_JMPBUF_R14(%rdi), %r14
	movq   OFFSET_JMPBUF_R13(%rdi), %r13
	movq   OFFSET_JMPBUF_R12(%rdi), %r12
	movq   OFFSET_JMPBUF_RBP(%rdi), %rbp
	movq   OFFSET_JMPBUF_RBX(%rdi), %rbx
	movq   %rsi, %rax
	jmp    *OFFSET_JMPBUF_RIP(%rdi)
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
	movq   $(1), %rsi
INTERN_FUNCTION(libc_sigsetjmp)
	movq   %rbx, OFFSET_JMPBUF_RBX(%rdi)
	movq   %rbp, OFFSET_JMPBUF_RBP(%rdi)
	movq   %r12, OFFSET_JMPBUF_R12(%rdi)
	movq   %r13, OFFSET_JMPBUF_R13(%rdi)
	movq   %r14, OFFSET_JMPBUF_R14(%rdi)
	movq   %r15, OFFSET_JMPBUF_R15(%rdi)
	leaq   8(%rsp), %rax
	movq   %rax, OFFSET_JMPBUF_RSP(%rdi)
	movq   %rsi, OFFSET_JMPBUF_HASSIG(%rdi)
	testq  %rsi, %rsi
	jz     1f
	movq   0(%rsp), %rcx
	movq   %rcx, OFFSET_JMPBUF_RIP(%rdi)
	leaq   OFFSET_JMPBUF_SIG(%rdi), %rdi /* sigset_t *oset */
	xorq   %rsi, %rsi                    /* sigset_t const *set */
	movq   $(SIG_SETMASK), %rdx          /* syscall_ulong_t how */
	movq   $(__SIZEOF_SIGSET_T__), %rcx  /* size_t sigsetsize */
	EXTERN(libc_sigprocmask)
#if defined(NDEBUG) || defined(__OPTIMIZE_SIZE__)
	jmp    libc_sigprocmask /* call + ret */
#else /* NDEBUG || __OPTIMIZE_SIZE__ */
	call   libc_sigprocmask
	ret
#endif /* !NDEBUG && !__OPTIMIZE_SIZE__ */
1:	popq_cfi %rcx
	.cfi_register %rip, %rcx
	movq   %rcx, OFFSET_JMPBUF_RIP(%rdi)
	xorq   %rax, %rax
	jmp    *%rcx
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
	.cfi_signal_frame__entry
	cmpq   $(0), OFFSET_JMPBUF_HASSIG(%rdi)
	je     libc_longjmp
	/* Restore signal mask. */
	pushq_cfi %rdi
	pushq_cfi %rsi
	movq   $(__SIZEOF_SIGSET_T__), %rcx  /* size_t sigsetsize */
	movq   $(SIG_SETMASK), %rdx          /* syscall_ulong_t how */
	leaq   OFFSET_JMPBUF_SIG(%rdi), %rsi /* sigset_t *set */
	xorq   %rdi, %rdi                    /* sigset_t *oset */
	EXTERN(libc_sigprocmask)
	call   libc_sigprocmask
	popq_cfi %rsi
	popq_cfi %rdi
	jmp    libc_longjmp
	.cfi_endproc
END(libc_siglongjmp)

DEFINE_PUBLIC_ALIAS(siglongjmp, libc_siglongjmp)
DEFINE_PUBLIC_ALIAS(__siglongjmp, libc_siglongjmp)

#endif /* !GUARD_LIBC_LIBC_ARCH_I386_SETJMP64_S */
