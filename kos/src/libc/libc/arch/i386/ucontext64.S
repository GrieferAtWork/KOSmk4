/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_LIBC_ARCH_I386_UCONTEXT64_S
#define GUARD_LIBC_LIBC_ARCH_I386_UCONTEXT64_S 1
#define _GNU_SOURCE 1
#define __ASSEMBLER__ 1

#include "../../../api.h"
/**/
#include <hybrid/compiler.h>

#include <asm/cfi.h>
#include <asm/cpu-cpuid.h>
#include <asm/instr/fsgsbase.h>
#include <asm/instr/ttest.h>
#include <asm/pagesize.h>
#include <bits/os/kos/mcontext64.h>
#include <bits/os/kos/ucontext64.h>

#include <pthread.h>
#include <signal.h>
#include <syscall.h>
#include <ucontext.h>

#include "ucontext.h"
/**/


#ifdef ENVIRON_HW_SSE
.section .rodata.crt.cpu.ucontext
PRIVATE_OBJECT(str_HW_SSE)
	.asciz ENVIRON_HW_SSE
END(str_HW_SSE)
#endif /* ENVIRON_HW_SSE */

.section .bss.crt.cpu.ucontext
/* Either `__MCONTEXTX64_FLAG_HAVEXFPU' or `__MCONTEXTX64_FLAG_HAVESFPU' */
PRIVATE_OBJECT(fpu_flags)
	.8byte  0x00000000 /* Uninitialized */
END(fpu_flags)


.section .text.crt.cpu.ucontext
/* Figure out how to preserve FPU registers.
 * Returns:    %rax = fpu_flags
 * Clobber:    %rcx, %rdx, %rsi, %rflags */
PRIVATE_FUNCTION(get_fpu_flags)
	.cfi_startproc
	movq   fpu_flags(%rip), %rax
	testq  %rax, %rax
	jz     .Lget_fpu_flags_firstcall
	ret
.Lget_fpu_flags_firstcall:
	/* Not yet calculated.
	 * In order to determine support, we do the following:
	 * >> char const *env = getenv("HW_SSE");
	 * >> #ifdef ENVIRON_HW_SSE
	 * >> if (env && env[0] && !env[1]) {
	 * >>     if (env[0] == '1')
	 * >>         return __MCONTEXTX64_FLAG_HAVEXFPU;
	 * >>     if (env[0] == '0')
	 * >>         return __MCONTEXTX64_FLAG_HAVESFPU;
	 * >> }
	 * >> #endif // ENVIRON_HW_SSE
	 * >> if (cpuid[1].edx & CPUID_1D_SSE)
	 * >>     return __MCONTEXTX64_FLAG_HAVEXFPU;
	 * >> return __MCONTEXTX64_FLAG_HAVESFPU;
	 */
#ifdef ENVIRON_HW_SSE
	leaq   str_HW_SSE(%rip), %rdi
	EXTERN(libc_getenv)
	call   libc_getenv
	testq  %rax, %rax
	jz     .Lget_fpu_flags_noenv
	cmpb   $(0), 0(%rax)
	je     .Lget_fpu_flags_noenv /* strlen(env) == 0 */
	cmpb   $(0), 1(%rax)
	jne    .Lget_fpu_flags_noenv /* strlen(env) != 1 */
	cmpb   $('1'), 1(%rax)
	je     .Lget_fpu_flags_XFPU
	cmpb   $('0'), 1(%rax)
	je     .Lget_fpu_flags_SFPU
.Lget_fpu_flags_noenv:
#endif /* ENVIRON_HW_SSE */
	movl   $(1), %eax
	pushq_cfi_r %rbx
	cpuid
	popq_cfi_r %rbx
	ttest  mask=CPUID_1D_SSE, loc=%edx
	jz     .Lget_fpu_flags_SFPU
.Lget_fpu_flags_XFPU:
	movq   $(__MCONTEXTX64_FLAG_HAVEXFPU), %rax
	jmp    1f
.Lget_fpu_flags_SFPU:
	movq   $(__MCONTEXTX64_FLAG_HAVESFPU), %rax
1:	movq   %rax, fpu_flags(%rip)
	ret
	.cfi_endproc
END(get_fpu_flags)






.section .text.crt.cpu.ucontext
INTERN_FUNCTION(libc_getcontext)
	/* IN: ucontext_t *%rdi = old_context; */
	.cfi_startproc
#define UC_(offset) (offset)
#define UC(offset)  (offset)(%rdi)
#define MC_(offset) (__OFFSET_UCONTEXTX64_MCONTEXT + (offset))
#define MC(offset)  (__OFFSET_UCONTEXTX64_MCONTEXT + (offset))(%rdi)
#define R_(regno)   MC_(__OFFSET_MCONTEXTX64_CPU + (regno) * 8)
#define R(regno)    MC(__OFFSET_MCONTEXTX64_CPU + (regno) * 8)

	/* Save general purpose registers. */
/*	movq   %rax, R(__MCONTEXTX64_REGNO_RAX) */
	movq   %rcx, R(__MCONTEXTX64_REGNO_RCX)
	movq   %rdx, R(__MCONTEXTX64_REGNO_RDX)
	movq   %rbx, R(__MCONTEXTX64_REGNO_RBX)
	movq   %rsp, R(__MCONTEXTX64_REGNO_RSP)
	movq   %rbp, R(__MCONTEXTX64_REGNO_RBP)
	movq   %rsi, R(__MCONTEXTX64_REGNO_RSI)
	movq   %rdi, R(__MCONTEXTX64_REGNO_RDI)
	movq   %r8,  R(__MCONTEXTX64_REGNO_R8)
	movq   %r9,  R(__MCONTEXTX64_REGNO_R9)
	movq   %r10, R(__MCONTEXTX64_REGNO_R10)
	movq   %r11, R(__MCONTEXTX64_REGNO_R11)
	movq   %r12, R(__MCONTEXTX64_REGNO_R12)
	movq   %r13, R(__MCONTEXTX64_REGNO_R13)
	movq   %r14, R(__MCONTEXTX64_REGNO_R14)
	movq   %r15, R(__MCONTEXTX64_REGNO_R15)

	/* Save %rflags */
	pushfq_cfi
	popq_cfi %rax
	movq   %rax, R(__MCONTEXTX64_REGNO_RFLAGS)

	/* Save %rip */
	movq   0(%rsp), %rax
	movq   %rax, R(__MCONTEXTX64_REGNO_RIP)

	/* Save segment register indices. */
	xorq   %rax, %rax
	movl   %gs, %eax
	movq   %rax, R(__MCONTEXTX64_REGNO_GS)
	movl   %fs, %eax
	movq   %rax, R(__MCONTEXTX64_REGNO_FS)
	movl   %es, %eax
	movq   %rax, R(__MCONTEXTX64_REGNO_ES)
	movl   %ds, %eax
	movq   %rax, R(__MCONTEXTX64_REGNO_DS)
	movl   %cs, %eax
	movq   %rax, R(__MCONTEXTX64_REGNO_CS)
	movl   %ss, %eax
	movq   %rax, R(__MCONTEXTX64_REGNO_SS)

	/* Save %fs/%gs base addresses. */
	rdgsbaseq %rax
	movq   %rax, R(__MCONTEXTX64_REGNO_GSBASE)
	rdfsbaseq %rax
	movq   %rax, R(__MCONTEXTX64_REGNO_FSBASE)

	/* Fill in information about the caller's stack. */
	EXTERN(libc_pthread_self)
	call   libc_pthread_self

	ttest  mask=PTHREAD_FNOSTACK, loc=__OFFSET_PTHREAD_FLAGS(%rax)
	jnz    .Lgetcontext_generic_stack
	movq   __OFFSET_PTHREAD_STACKADDR(%rax), %rsi
	movq   %rsi, UC(__OFFSET_UCONTEXTX64_STACK + __OFFSET_SIGALTSTACKX64_SP)
	movq   __OFFSET_PTHREAD_STACKSIZE(%rax), %rsi
	movq   %rsi, UC(__OFFSET_UCONTEXTX64_STACK + __OFFSET_SIGALTSTACKX64_SIZE)
.Lgetcontext_got_stack:
	xorq   %rsi, %rsi
	movl   %esi, UC(__OFFSET_UCONTEXTX64_STACK + __OFFSET_SIGALTSTACKX64_FLAGS)

	/* Load the current signal mask */
	movq   $(__SIZEOF_SIGSET_T__),           %r10 /* sigsetsize */
	leaq   UC(__OFFSET_UCONTEXTX64_SIGMASK), %rdx /* oset = &ucp->uc_sigmask */
/*	xorq   %rsi, %rsi */                          /* set  = NULL  (Already cleared; s.a. above) */
	/* TODO: Integrate w/ the userprocmask mechanism */
	movq   $(SYS_rt_sigprocmask), %rax
	syscall

	/* Now all that's left to save is the FPU context.
	 * For this, we first have to figure out which format we should use for it.
	 * This can be done with `get_fpu_flags',  which returns the value that  we
	 * should use for the `mc_flags' field. */
	call   get_fpu_flags
	movq   %rax, MC(__OFFSET_MCONTEXTX64_FLAGS)

	/* Check if we're using fxsave64, or fnsave */
	ttest  mask=__MCONTEXTX64_FLAG_HAVEXFPU, loc=%rax
	jz     .Lgetcontext_use_fnsave
	fxsave64 MC(__OFFSET_MCONTEXTX64_FPU)
.Lgetcontext_done_fpu:

	/* Return `0' to indicate success. */
	xorq   %rax, %rax
	movq   %rax, R(__MCONTEXTX64_REGNO_RAX) /* Also return 0 the second time around! */
	movq   %rax, UC(__OFFSET_UCONTEXTX64_LINK)
	ret

.Lgetcontext_use_fnsave:
	.cfi_remember_state
	fnsave MC(__OFFSET_MCONTEXTX64_FPU)
	frstor MC(__OFFSET_MCONTEXTX64_FPU)
	jmp    .Lgetcontext_done_fpu

.Lgetcontext_generic_stack:
	/* Use the current %rsp as orientation for the stack's size */
#ifndef ASSUMED_ADDITIONAL_STACK_PAGES
#define ASSUMED_ADDITIONAL_STACK_PAGES 2
#endif /* !ASSUMED_ADDITIONAL_STACK_PAGES */
	movq   %rsp, %rsi
	andq   $(__ARCH_PAGEMASK), %rsi
#if ASSUMED_ADDITIONAL_STACK_PAGES != 0
	subq   $(ASSUMED_ADDITIONAL_STACK_PAGES * __ARCH_PAGESIZE), %rsi
#endif /* ASSUMED_ADDITIONAL_STACK_PAGES != 0 */
	movq   %rsi, UC(__OFFSET_UCONTEXTX64_STACK + __OFFSET_SIGALTSTACKX64_SP)
	movq   $((1 + ASSUMED_ADDITIONAL_STACK_PAGES) * __ARCH_PAGESIZE), \
	       UC(__OFFSET_UCONTEXTX64_STACK + __OFFSET_SIGALTSTACKX64_SIZE)
	jmp    .Lgetcontext_got_stack
	.cfi_endproc
END(libc_getcontext)



.section .text.crt.cpu.ucontext
INTERN_FUNCTION(libc_x86_setcontext_rbx)
	.cfi_startproc
	movq   %rbx, %rdi
INTERN_FUNCTION(libc_setcontext)
	/* IN: ucontext_t const *%rdi = new_context; */

	/* TODO */
	hlt
	.cfi_endproc
END(libc_setcontext)
END(libc_x86_setcontext_rbx)



.section .text.crt.cpu.ucontext
INTERN_FUNCTION(libc_swapcontext)
	/* IN: ucontext_t       *%rdi = old_context; */
	/* IN: ucontext_t const *%rsi = new_context; */
	.cfi_startproc

	/* TODO */
	hlt
	.cfi_endproc
END(libc_swapcontext)


.section .text.crt.cpu.ucontext
INTERN_FUNCTION(libc_makecontext_exit_thread)
	/* No CFI annotation, because we don't return! */
	xorq   %rdi, %rdi
	EXTERN(libc_pthread_exit)
	call   libc_pthread_exit
	hlt
END(libc_makecontext_exit_thread)




DEFINE_PUBLIC_ALIAS(getcontext, libc_getcontext)
DEFINE_PUBLIC_ALIAS(setcontext, libc_setcontext)
DEFINE_PUBLIC_ALIAS(swapcontext, libc_swapcontext)


#endif /* GUARD_LIBC_LIBC_ARCH_I386_UCONTEXT64_S */
