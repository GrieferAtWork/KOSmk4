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
#include <asm/instr/movzxq.h>
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
	popq_cfi R(__MCONTEXTX64_REGNO_RFLAGS)

	/* Save %rip */
	movq   0(%rsp), %rax
	movq   %rax, R(__MCONTEXTX64_REGNO_RIP)

	/* Fill in some 0-fields. */
	xorq   %rax, %rax
	movq   %rax, R(__MCONTEXTX64_REGNO_RAX) /* Return 0 the second time around! */
	movq   %rax, UC(__OFFSET_UCONTEXTX64_LINK)                                  /* May as well do this here... */
	movl   %eax, UC(__OFFSET_UCONTEXTX64_STACK + __OFFSET_SIGALTSTACKX64_FLAGS) /* *ditto* */

	/* Save segment register indices. */
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

	/* Preserve `%rdi' inside of `%rbp', since it may be
	 * clobbered by the upcoming library functino calls.
	 * Also: The upcoming `rep movsq' will also need to clobber
	 *       that same register, so we'd have to do this sooner
	 *       or later no matter what! */
	movq   %rdi, %rbp
	.cfi_reg_offset %rbp, UC_(__OFFSET_UCONTEXTX64_SIGMASK), %rbp

	/* Fill in information about the caller's stack. */
	EXTERN(libc_pthread_self)
	call   libc_pthread_self

	ttest  mask=PTHREAD_FNOSTACK, loc=__OFFSET_PTHREAD_FLAGS(%rax)
	jnz    .Lgetcontext_generic_stack
	.cfi_remember_state
	movq   __OFFSET_PTHREAD_STACKADDR(%rax), %rcx
	movq   %rcx, UC_(__OFFSET_UCONTEXTX64_STACK + __OFFSET_SIGALTSTACKX64_SP)(%rbp)
	movq   __OFFSET_PTHREAD_STACKSIZE(%rax), %rcx
	movq   %rcx, UC_(__OFFSET_UCONTEXTX64_STACK + __OFFSET_SIGALTSTACKX64_SIZE)(%rbp)
.Lgetcontext_got_stack:

	/* Load the current signal mask */
	EXTERN(libc_getsigmaskptr)
	call   libc_getsigmaskptr

	/* Copy the signal mask buffer into the given ucontext. */
	leaq   UC_(__OFFSET_UCONTEXTX64_SIGMASK)(%rbp), %rdi /* dest */
	movq   %rax, %rsi                                    /* source */
#if (__SIZEOF_SIGSET_T__ % 8) == 0
	movq   $(__SIZEOF_SIGSET_T__ / 8), %rcx       /* count */
	rep;   movsq
#else /* (__SIZEOF_SIGSET_T__ % 8) == 0 */
	movq   $(__SIZEOF_SIGSET_T__), %rcx           /* count */
	rep;   movsb
#endif /* (__SIZEOF_SIGSET_T__ % 8) != 0 */

	/* Now all that's left to save is the FPU context.
	 * For this, we first have to figure out which format we should use for it.
	 * This can be done with `get_fpu_flags',  which returns the value that  we
	 * should use for the `mc_flags' field. */
	call   get_fpu_flags

	movq   %rbp, %rdi                           /* Use `%rdi' once again. */
	movq   R(__MCONTEXTX64_REGNO_RBP), %rbp     /* Restore the original `%rbp' */
	.cfi_same_value %rbp
	movq   %rax, MC(__OFFSET_MCONTEXTX64_FLAGS) /* Save the fpu-flags value. */

	/* Check if we're using fxsave64, or fnsave */
	ttest  mask=__MCONTEXTX64_FLAG_HAVEXFPU, loc=%rax
	jz     .Lgetcontext_use_fnsave
	fxsave64 MC(__OFFSET_MCONTEXTX64_FPU)
.Lgetcontext_done_fpu:

	/* Return `0' to indicate success. */
	xorq   %rax, %rax
	ret

.Lgetcontext_use_fnsave:
	fnsave MC(__OFFSET_MCONTEXTX64_FPU)
	frstor MC(__OFFSET_MCONTEXTX64_FPU)
	jmp    .Lgetcontext_done_fpu

.Lgetcontext_generic_stack:
	.cfi_restore_state
	/* Use the current %rsp as orientation for the stack's size */
#ifndef ASSUMED_ADDITIONAL_STACK_PAGES
#define ASSUMED_ADDITIONAL_STACK_PAGES 2
#endif /* !ASSUMED_ADDITIONAL_STACK_PAGES */
	movq   %rsp, %rsi
	andq   $(__ARCH_PAGEMASK), %rsi
#if ASSUMED_ADDITIONAL_STACK_PAGES != 0
	subq   $(ASSUMED_ADDITIONAL_STACK_PAGES * __ARCH_PAGESIZE), %rsi
#endif /* ASSUMED_ADDITIONAL_STACK_PAGES != 0 */
	movq   %rsi, UC_(__OFFSET_UCONTEXTX64_STACK + __OFFSET_SIGALTSTACKX64_SP)(%rbp)
	movq   $((1 + ASSUMED_ADDITIONAL_STACK_PAGES) * __ARCH_PAGESIZE), \
	       UC_(__OFFSET_UCONTEXTX64_STACK + __OFFSET_SIGALTSTACKX64_SIZE)(%rbp)
	jmp    .Lgetcontext_got_stack
#undef UC_
#undef UC
#undef MC_
#undef MC
#undef R_
#undef R
	.cfi_endproc
END(libc_getcontext)



.section .text.crt.cpu.ucontext
INTERN_FUNCTION(libc_setcontext)
	.cfi_startproc
	movq   %rdi, %rbp
INTERN_FUNCTION(libc_x86_setcontext_rbp)
#define UC_(offset) (offset)
#define UC(offset)  (offset)(%rbp)
#define MC_(offset) (__OFFSET_UCONTEXTX64_MCONTEXT + (offset))
#define MC(offset)  (__OFFSET_UCONTEXTX64_MCONTEXT + (offset))(%rbp)
#define R_(regno)   MC_(__OFFSET_MCONTEXTX64_CPU + (regno) * 8)
#define R(regno)    MC(__OFFSET_MCONTEXTX64_CPU + (regno) * 8)
	/* IN: ucontext_t const *%rbp = new_context; */
	.cfi_def_cfa %rbp, 0
	.cfi_rel_offset %gs.base, R_(__MCONTEXTX64_REGNO_GSBASE)
	.cfi_rel_offset %fs.base, R_(__MCONTEXTX64_REGNO_FSBASE)
	.cfi_rel_offset %r15, R_(__MCONTEXTX64_REGNO_R15)
	.cfi_rel_offset %r14, R_(__MCONTEXTX64_REGNO_R14)
	.cfi_rel_offset %r13, R_(__MCONTEXTX64_REGNO_R13)
	.cfi_rel_offset %r12, R_(__MCONTEXTX64_REGNO_R12)
	.cfi_rel_offset %r11, R_(__MCONTEXTX64_REGNO_R11)
	.cfi_rel_offset %r10, R_(__MCONTEXTX64_REGNO_R10)
	.cfi_rel_offset %r9, R_(__MCONTEXTX64_REGNO_R9)
	.cfi_rel_offset %r8, R_(__MCONTEXTX64_REGNO_R8)
	.cfi_rel_offset %rdi, R_(__MCONTEXTX64_REGNO_RDI)
	.cfi_rel_offset %rsi, R_(__MCONTEXTX64_REGNO_RSI)
	.cfi_rel_offset %rbp, R_(__MCONTEXTX64_REGNO_RBP)
	.cfi_rel_offset %rsp, R_(__MCONTEXTX64_REGNO_RSP)
	.cfi_rel_offset %rbx, R_(__MCONTEXTX64_REGNO_RBX)
	.cfi_rel_offset %rdx, R_(__MCONTEXTX64_REGNO_RDX)
	.cfi_rel_offset %rcx, R_(__MCONTEXTX64_REGNO_RCX)
	.cfi_rel_offset %rax, R_(__MCONTEXTX64_REGNO_RAX)
	.cfi_rel_offset %gs, R_(__MCONTEXTX64_REGNO_GS)
	.cfi_rel_offset %fs, R_(__MCONTEXTX64_REGNO_FS)
	.cfi_rel_offset %es, R_(__MCONTEXTX64_REGNO_ES)
	.cfi_rel_offset %ds, R_(__MCONTEXTX64_REGNO_DS)
	.cfi_rel_offset %cs, R_(__MCONTEXTX64_REGNO_CS)
	.cfi_rel_offset %ss, R_(__MCONTEXTX64_REGNO_SS)
	.cfi_rel_offset %rflags, R_(__MCONTEXTX64_REGNO_RFLAGS)
	.cfi_rel_offset %rip, R_(__MCONTEXTX64_REGNO_RIP)

	/* Load the new stack pointer registers */
	movq   R(__MCONTEXTX64_REGNO_RSP), %rsp

	/* Load target segment registers & bases.
	 * Note that during this, we  must disable signals because the  act
	 * of writing to `%gs' or `%fs' may alter the base-values, causting
	 * them to be inconsistent until we reload them manually. */
	EXTERN(libc_setsigmaskfullptr)
	call   libc_setsigmaskfullptr  /* %rax = OLD_PROC_MASK_PTR */

	/* Copy the new ucontext's signal mask into the soon-to-be
	 * restored old signal mask buffer (which is pointed-to by
	 * `%rax' right now) */
	movq   %rax, %rdi
	leaq   UC(__OFFSET_UCONTEXTX64_SIGMASK), %rsi
#if (__SIZEOF_SIGSET_T__ % 8) == 0
	movzlq $(__SIZEOF_SIGSET_T__ / 8), %rcx
	rep;   movsq
#else /* (__SIZEOF_SIGSET_T__ % 8) == 0 */
	movzlq $(__SIZEOF_SIGSET_T__), %rcx
	rep;   movsb
#endif /* (__SIZEOF_SIGSET_T__ % 8) != 0 */

	movw   R(__MCONTEXTX64_REGNO_GS), %cx
	movw   %cx, %gs
	.cfi_same_value %gs

	movw   R(__MCONTEXTX64_REGNO_FS), %cx
	movw   %cx, %fs
	.cfi_same_value %fs

	movw   R(__MCONTEXTX64_REGNO_ES), %cx
	movw   %cx, %es
	.cfi_same_value %es

	movw   R(__MCONTEXTX64_REGNO_DS), %cx
	movw   %cx, %ds
	.cfi_same_value %ds

	/* Load the new segment base addresses. */
	movq   R(__MCONTEXTX64_REGNO_GSBASE), %rcx
	wrgsbaseq %rcx
	movq   R(__MCONTEXTX64_REGNO_FSBASE), %rcx
	wrfsbaseq %rcx

	/* Restore the old procmask  buffer (which in the  mean
	 * time got filled with the new ucontext's signal mask) */
	movq   %rax, %rdi
	EXTERN(libc_setsigmaskptr)
	call   libc_setsigmaskptr

	/* Load the FPU context. (if there is one) */
	ttest  mask=__MCONTEXTX64_FLAG_HAVEXFPU, loc=MC(__OFFSET_MCONTEXTX64_FLAGS)
	jz     .Lsetcontext_noxfpu
	.cfi_remember_state
	fxrstor64 MC(__OFFSET_MCONTEXTX64_FPU)
.Lsetcontext_donefpu:

	/* Load general purpose registers. */
	movq   R(__MCONTEXTX64_REGNO_R15), %r15
	.cfi_same_value %r15
	movq   R(__MCONTEXTX64_REGNO_R14), %r14
	.cfi_same_value %r14
	movq   R(__MCONTEXTX64_REGNO_R13), %r13
	.cfi_same_value %r13
	movq   R(__MCONTEXTX64_REGNO_R12), %r12
	.cfi_same_value %r12
	movq   R(__MCONTEXTX64_REGNO_R11), %r11
	.cfi_same_value %r11
	movq   R(__MCONTEXTX64_REGNO_R10), %r10
	.cfi_same_value %r10
	movq   R(__MCONTEXTX64_REGNO_R9), %r9
	.cfi_same_value %r9
	movq   R(__MCONTEXTX64_REGNO_R8), %r8
	.cfi_same_value %r8
	movq   R(__MCONTEXTX64_REGNO_RDI), %rdi
	.cfi_same_value %rdi
	movq   R(__MCONTEXTX64_REGNO_RSI), %rsi
	.cfi_same_value %rsi
	movq   R(__MCONTEXTX64_REGNO_RBX), %rbx
	.cfi_same_value %rbx
	movq   R(__MCONTEXTX64_REGNO_RDX), %rdx
	.cfi_same_value %rdx
	movq   R(__MCONTEXTX64_REGNO_RCX), %rcx
	.cfi_same_value %rcx

	/* Push some new registers into the new stack. */
	pushq  R(__MCONTEXTX64_REGNO_CS)     /* Return %cs */
	pushq  R(__MCONTEXTX64_REGNO_RIP)    /* Return %rip */
	pushq  R(__MCONTEXTX64_REGNO_RFLAGS) /* Return %rflags */
	popfq                                /* Load %rflags */
	.cfi_same_value %rflags

	/* Only load %ss after all of the pushs and pops above! */
	movw   R(__MCONTEXTX64_REGNO_SS), %ax
	movw   %ax, %ss
	.cfi_same_value %ss

	movq   R(__MCONTEXTX64_REGNO_RAX), %rax /* Restore %rax */
	.cfi_same_value %rax

	movq   R(__MCONTEXTX64_REGNO_RBP), %rbp /* Restore %rbp */
	.cfi_same_value %rbp

	/* Tell CFI that %rip is stored at 0(%rsp) */
	.cfi_reg_offset %rip, 0, %rsp

	/* Tell CFI that %cs is stored at 8(%rsp) */
	.cfi_reg_offset %cs, 8, %rsp

	/* Tell CFI that %rsp is offset by 16 */
	.cfi_reg_value %rsp, 16, %rsp

	lretq
	.cfi_restore_state
.Lsetcontext_noxfpu:
	ttest  mask=__MCONTEXTX64_FLAG_HAVESFPU, loc=MC(__OFFSET_MCONTEXTX64_FLAGS)
	jz     .Lsetcontext_donefpu
	frstor MC(__OFFSET_MCONTEXTX64_FPU)
	jmp    .Lsetcontext_donefpu
	.cfi_endproc
#undef UC_
#undef UC
#undef MC_
#undef MC
#undef R_
#undef R
END(libc_x86_setcontext_rbp)
END(libc_setcontext)



.section .text.crt.cpu.ucontext
INTERN_FUNCTION(libc_swapcontext)
	/* IN: ucontext_t       *%rdi = old_context; */
	/* IN: ucontext_t const *%rsi = new_context; */
	.cfi_startproc
	pushq_cfi %rsi         /* Preserve... */
	pushq_cfi %rdi         /* Preserve... */
	call   libc_getcontext /* Generate the old-context */

	/* NOTE: The swapping of %rsi/%rdi by the following 2 instruction is INTENTIONAL! */
	popq_cfi %rsi          /* old_context */
	popq_cfi %rdi          /* new_context */

	/* Override the registers that the previous call filled in incorrectly. */
	movq   0(%rsp), %rax   /* %rip */
	movq   %rax, (__OFFSET_UCONTEXTX64_MCONTEXT + __OFFSET_MCONTEXTX64_CPU + 8 * __MCONTEXTX64_REGNO_RIP)(%rsi)
	leaq   8(%rsp), %rax   /* return-%rsp */
	movq   %rax, (__OFFSET_UCONTEXTX64_MCONTEXT + __OFFSET_MCONTEXTX64_CPU + 8 * __MCONTEXTX64_REGNO_RSP)(%rsi)

	/* And with that, the old CPU context has been filled.
	 * Now  we  just  have   to  load  the  new   context! */
	jmp    libc_setcontext /* Load context from %rdi */
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
