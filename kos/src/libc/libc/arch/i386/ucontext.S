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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_UCONTEXT_S
#define GUARD_LIBC_LIBC_ARCH_I386_UCONTEXT_S 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1
#define __ASSEMBLER__ 1

#include "../../../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <asm/asmword.h>
#include <asm/cfi.h>
#include <asm/cpu-cpuid.h>
#include <asm/instr/compat.h>
#include <asm/instr/fsgsbase.h>
#include <asm/instr/movzxq.h>
#include <asm/instr/ttest.h>
#include <asm/pagesize.h>
#include <bits/os/kos/mcontext32.h>
#include <bits/os/kos/ucontext32.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state.h>

#include <pthread.h>
#include <signal.h>
#include <syscall.h>
#include <ucontext.h>

#include "ucontext.h"
/**/

#ifndef SIZEOF_POINTER
#define SIZEOF_POINTER __SIZEOF_POINTER__
#endif /* !SIZEOF_POINTER */
#ifndef PAGEMASK
#define PAGEMASK __ARCH_PAGEMASK
#endif /* !PAGEMASK */
#ifndef PAGESIZE
#define PAGESIZE __ARCH_PAGESIZE
#endif /* !PAGESIZE */
#ifndef SIZEOF_SIGSET_T
#define SIZEOF_SIGSET_T __SIZEOF_SIGSET_T__
#endif /* !SIZEOF_SIGSET_T */
#define Pn(n) (SIZEOF_POINTER * (n))

/* Prettyfied offset constants */

/* struct sigaltstack */
#define OFFSET_SIGALTSTACK_SP    __OFFSET_SIGALTSTACK_SP
#define OFFSET_SIGALTSTACK_FLAGS __OFFSET_SIGALTSTACK_FLAGS
#define OFFSET_SIGALTSTACK_SIZE  __OFFSET_SIGALTSTACK_SIZE
#define SIZEOF_SIGALTSTACK       __SIZEOF_SIGALTSTACK

/* ucontext_t */
#define OFFSET_UCONTEXT_MCONTEXT __OFFSET_UCONTEXT_MCONTEXT
#define OFFSET_UCONTEXT_SIGMASK  __OFFSET_UCONTEXT_SIGMASK
#define OFFSET_UCONTEXT_STACK    __OFFSET_UCONTEXT_STACK
#define OFFSET_UCONTEXT_LINK     __OFFSET_UCONTEXT_LINK
#define SIZEOF_UCONTEXT          __SIZEOF_UCONTEXT

/* mcontext_t */
#define OFFSET_MCONTEXT_CPU      __OFFSET_MCONTEXT_CPU
#define OFFSET_MCONTEXT_FPU      __OFFSET_MCONTEXT_FPU
#define OFFSET_MCONTEXT_FLAGS    __OFFSET_MCONTEXT_FLAGS
#define OFFSET_MCONTEXT_CR2      __OFFSET_MCONTEXT_CR2
#define SIZEOF_MCONTEXT          __SIZEOF_MCONTEXT

/* pthread_t */
#define OFFSET_PTHREAD_TID       __OFFSET_PTHREAD_TID
#define OFFSET_PTHREAD_REFCNT    __OFFSET_PTHREAD_REFCNT
#define OFFSET_PTHREAD_RETVAL    __OFFSET_PTHREAD_RETVAL
#define OFFSET_PTHREAD_TLS       __OFFSET_PTHREAD_TLS
#define OFFSET_PTHREAD_STACKADDR __OFFSET_PTHREAD_STACKADDR
#define OFFSET_PTHREAD_STACKSIZE __OFFSET_PTHREAD_STACKSIZE
#define OFFSET_PTHREAD_FLAGS     __OFFSET_PTHREAD_FLAGS


#ifdef __x86_64__
#define IF64(...)               __VA_ARGS__
#define IF32(...)               /* nothing */
#define native_fxsave           fxsave64
#define native_fxrstor          fxrstor64
#define libc_x86_getcontext_Pax libc_x86_getcontext_rax
#define libc_x86_setcontext_Pbp libc_x86_setcontext_rbp
#else /* __x86_64__ */
#define IF64(...)               /* nothing */
#define IF32(...)               __VA_ARGS__
#define native_fxsave           fxsave
#define native_fxrstor          fxrstor
#define libc_x86_getcontext_Pax libc_x86_getcontext_eax
#define libc_x86_setcontext_Pbp libc_x86_setcontext_ebp
#endif /* !__x86_64__ */


#ifdef ENVIRON_HW_SSE
.section .rodata.crt.cpu.ucontext
PRIVATE_OBJECT(str_HW_SSE)
	.asciz ENVIRON_HW_SSE
END(str_HW_SSE)
#endif /* ENVIRON_HW_SSE */

#undef STATIC_ASSERT
#define STATIC_ASSERT(expr) \
	.if (!(expr));          \
	.error #expr;           \
	.endif


/* Flags for `fpu_flags' */
#define FPU_FLAGS_NORMAL  0x0000                /* Normal flags */
#define FPU_FLAGS_INIT    0x0010                /* FPU flags have been initialized */
#define FPU_FLAGS_HAVESSE 0x0020                /* SSE support is present */
#define FPU_FLAGS_HAVEFPU MCONTEXT_FLAG_HAVEFPU /* FPU support is present */
STATIC_ASSERT(FPU_FLAGS_HAVESSE != MCONTEXT_FLAG_HAVEFPU);
STATIC_ASSERT(FPU_FLAGS_HAVESSE != MCONTEXT_FLAG_HAVECR2);
STATIC_ASSERT(FPU_FLAGS_INIT != MCONTEXT_FLAG_HAVEFPU);
STATIC_ASSERT(FPU_FLAGS_INIT != MCONTEXT_FLAG_HAVECR2);


/* Set of `FPU_FLAGS_*' */
.section .bss.crt.cpu.ucontext
PRIVATE_OBJECT(fpu_flags)
	.wordptr FPU_FLAGS_NORMAL /* Uninitialized */
END(fpu_flags)


#ifdef __x86_64__
#define GOT_LOAD(Pgot_register)         /* nothing */
#define GOT_ADDR(symbol, Pgot_register) symbol(%rip)
#else /* __x86_64__ */
#define GOT_LOAD(Pgot_register)            \
	call   1f;                             \
	.cfi_adjust_cfa_offset SIZEOF_POINTER; \
1:	popP_cfi Pgot_register;                \
	addP   $(_GLOBAL_OFFSET_TABLE_ + (. - 1b)), Pgot_register
#define GOT_ADDR(symbol, Pgot_register) symbol@GOTOFF(Pgot_register)
#endif /* !__x86_64__ */



/* Figure out how to preserve FPU registers.
 * Returns:    %Pax = fpu_flags
 * Clobber:    %Pcx, %Pdx, %Psi, %Pflags */
.section .text.crt.cpu.ucontext
PRIVATE_FUNCTION(get_fpu_flags)
	.cfi_startproc
	GOT_LOAD(%Psi)
	movP   GOT_ADDR(fpu_flags, %Psi), %Pax
	ttest  mask=FPU_FLAGS_INIT, loc=%Pax
	jz     .Lget_fpu_flags_firstcall
	ret
.Lget_fpu_flags_firstcall:
	/* Not yet calculated.
	 * In order to determine support, we do the following:
	 * >> #ifdef ENVIRON_HW_SSE
	 * >> char const *env = getenv(ENVIRON_HW_SSE);
	 * >> if (env && env[0] && !env[1]) {
	 * >>     if (env[0] == '1')
	 * >>         return MCONTEXT_FLAG_HAVEXFPU;
	 * >>     if (env[0] == '0')
	 * >>         return MCONTEXT_FLAG_HAVESFPU;
	 * >> }
	 * >> #endif // ENVIRON_HW_SSE
	 * >> if (cpuid[1].edx & CPUID_1D_SSE)
	 * >>     return MCONTEXT_FLAG_HAVEXFPU;
	 * >> return MCONTEXT_FLAG_HAVESFPU;
	 */
#ifdef ENVIRON_HW_SSE
#ifdef __x86_64__
	leaP   GOT_ADDR(str_HW_SSE, %Psi), %R_sysvabi0P
#else /* __x86_64__ */
	leaP   GOT_ADDR(str_HW_SSE, %Psi), %Pax
	pushP_cfi %Pax
#endif /* !__x86_64__ */
	EXTERN(libc_getenv)
	call   libc_getenv
#ifndef __x86_64__
	addP   $(Pn(1)), %Psp
	.cfi_adjust_cfa_offset -Pn(1)
#endif /* !__x86_64__ */

	testP  %Pax, %Pax
	jz     .Lget_fpu_flags_noenv
	cmpb   $(0), 0(%Pax)
	je     .Lget_fpu_flags_noenv /* strlen(env) == 0 */
	cmpb   $(0), 1(%Pax)
	jne    .Lget_fpu_flags_noenv /* strlen(env) != 1 */
	cmpb   $('1'), 1(%Pax)
	je     .Lget_fpu_flags_XFPU
	cmpb   $('0'), 1(%Pax)
	je     .Lget_fpu_flags_SFPU
.Lget_fpu_flags_noenv:
#endif /* ENVIRON_HW_SSE */

	movl   $(1), %eax
	pushP_cfi_r %Pbx
	cpuid
	popP_cfi_r %Pbx
	ttest  mask=CPUID_1D_SSE, loc=%edx
	jz     .Lget_fpu_flags_SFPU
.Lget_fpu_flags_XFPU:
	movP   $(FPU_FLAGS_INIT | FPU_FLAGS_HAVEFPU | FPU_FLAGS_HAVESSE), %Pax
	jmp    1f
.Lget_fpu_flags_SFPU:
	movP   $(FPU_FLAGS_INIT | FPU_FLAGS_HAVEFPU), %Pax
1:	movP   %Pax, GOT_ADDR(fpu_flags, %Psi)
	ret
	.cfi_endproc
END(get_fpu_flags)






/* INTERN NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_getcontext)(ucontext_t *__restrict ucp); */
.section .text.crt.cpu.ucontext
	.cfi_startproc
#ifdef __x86_64__
INTERN_FUNCTION(libc_x86_getcontext_Pax)
	movP   %Pdi, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PDI(%Pax)
	movP   %Pax, %Pdi
	jmp    1f
#endif /* __x86_64__ */
INTERN_FUNCTION(libc_getcontext)
#ifdef __x86_64__
	/* IN: ucontext_t *%rdi = ucp; */
#define R_ucpP Pdi
#else /* __x86_64__ */
	/* IN: ucontext_t *4(%Psp) = ucp; */
	movP  4(%Psp), %Pax /* %Pax is saved as `0' anyways, so early clobber is OK */
#define R_ucpP Pax
INTERN_FUNCTION(libc_x86_getcontext_Pax)
#endif /* !__x86_64__ */

	/* Save general purpose registers. */
	movP   %Pdi, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PDI(%R_ucpP)
1:	movP   %Pcx, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PCX(%R_ucpP)
	movP   %Pdx, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PDX(%R_ucpP)
	movP   %Pbx, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PBX(%R_ucpP)
	movP   %Pbp, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PBP(%R_ucpP)
	movP   %Psi, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PSI(%R_ucpP)
#ifdef __x86_64__
	movq   %r8,  OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R8(%R_ucpP)
	movq   %r9,  OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R9(%R_ucpP)
	movq   %r10, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R10(%R_ucpP)
	movq   %r11, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R11(%R_ucpP)
	movq   %r12, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R12(%R_ucpP)
	movq   %r13, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R13(%R_ucpP)
	movq   %r14, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R14(%R_ucpP)
	movq   %r15, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R15(%R_ucpP)
#endif /* __x86_64__ */

	/* Save %Pip and %Psp */
	popP_cfi %Pcx
	.cfi_register %Pip, %Pcx
	movP   %Pcx, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_PIP(%R_ucpP)
	movP   %Psp, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PSP(%R_ucpP)

	/* Set-up CFI annotation over to restore from the saved CPU state. */
	.cfi_def_cfa %R_ucpP, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU
	.cfi_offset %Pip, OFFSET_UCPUSTATE_PIP
	.cfi_offset %Psp, OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PSP
	.cfi_offset %Pcx, OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PCX
	.cfi_offset %Pdx, OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PDX
	.cfi_offset %Pbx, OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PBX
	.cfi_offset %Pbp, OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PBP
	.cfi_offset %Psi, OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PSI
	.cfi_offset %Pdi, OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PDI
#ifdef __x86_64__
	.cfi_offset %r8,  OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R8
	.cfi_offset %r9,  OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R9
	.cfi_offset %r10, OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R10
	.cfi_offset %r11, OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R11
	.cfi_offset %r12, OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R12
	.cfi_offset %r13, OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R13
	.cfi_offset %r14, OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R14
	.cfi_offset %r15, OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R15
#endif /* __x86_64__ */

	/* Save %Pflags */
	pushfP
	popP   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_PFLAGS(%R_ucpP)
	.cfi_offset %Pflags, OFFSET_UCPUSTATE_PFLAGS

	/* Fill in some 0-fields. */
	xorP   %Pcx, %Pcx
	movP   %Pcx, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PAX(%R_ucpP) /* Return 0 the second time around! */
	.cfi_offset %Pax, OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PAX
	movP   %Pcx, OFFSET_UCONTEXT_LINK(%R_ucpP)                           /* May as well do this here... */
	movP   %Pcx, OFFSET_UCONTEXT_STACK+OFFSET_SIGALTSTACK_FLAGS(%R_ucpP) /* *ditto* */

	/* Save segment register indices. */
	movw   %gs, %cx
	movP   %Pcx, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_GS(%R_ucpP)
	.cfi_offset %gs, OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_GS
	movw   %fs, %cx
	movP   %Pcx, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_FS(%R_ucpP)
	.cfi_offset %fs, OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_FS
	movw   %es, %cx
	movP   %Pcx, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_ES(%R_ucpP)
	.cfi_offset %es, OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_ES
	movw   %ds, %cx
	movP   %Pcx, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_DS(%R_ucpP)
	.cfi_offset %ds, OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_DS
	movw   %cs, %cx
	movP   %Pcx, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_CS(%R_ucpP)
	.cfi_offset %cs, OFFSET_UCPUSTATE_CS
	movw   %ss, %cx
	movP   %Pcx, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_SS(%R_ucpP)
	.cfi_offset %ss, OFFSET_UCPUSTATE_SS

	/* Save %fs/%gs base addresses. */
#ifdef __x86_64__
	rdgsbaseP %Pcx
	movP   %Pcx, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_SGBASE+OFFSET_SGBASE_GSBASE(%R_ucpP)
	.cfi_offset %gs.base, OFFSET_UCPUSTATE_SGBASE+OFFSET_SGBASE_GSBASE
	rdfsbaseP %Pcx
	movP   %Pcx, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_SGBASE+OFFSET_SGBASE_FSBASE(%R_ucpP)
	.cfi_offset %fs.base, OFFSET_UCPUSTATE_SGBASE+OFFSET_SGBASE_FSBASE
#endif /* __x86_64__ */

	/* Preserve `%R_ucpP' inside of `%Pbp', since it may be
	 * clobbered by  the upcoming  library function  calls. */
	movP   %R_ucpP, %Pbp
#undef R_ucpP
	.cfi_def_cfa_register %Pbp
#define R_ucpP Pbp

	/* Fill in information about the caller's stack. */
	EXTERN(libc_pthread_self)
	call   libc_pthread_self

	ttest  mask=PTHREAD_FNOSTACK, loc=OFFSET_PTHREAD_FLAGS(%Pax)
	jnz    .Lgetcontext_generic_stack
	.cfi_remember_state
	movP   OFFSET_PTHREAD_STACKADDR(%Pax), %Pcx
	movP   %Pcx, OFFSET_UCONTEXT_STACK+OFFSET_SIGALTSTACK_SP(%R_ucpP)
	movP   OFFSET_PTHREAD_STACKSIZE(%Pax), %Pcx
	movP   %Pcx, OFFSET_UCONTEXT_STACK+OFFSET_SIGALTSTACK_SIZE(%R_ucpP)
.Lgetcontext_got_stack:

	/* Load the current signal mask */
	EXTERN(libc_getsigmaskptr)
	call   libc_getsigmaskptr

	/* Copy the signal mask buffer into the given ucontext. */
	leaP   OFFSET_UCONTEXT_SIGMASK(%R_ucpP), %Pdi /* dest */
	movP   %Pax, %Psi                             /* source */
#if (SIZEOF_SIGSET_T % SIZEOF_POINTER) == 0
	movP   $(SIZEOF_SIGSET_T / SIZEOF_POINTER), %Pcx /* count */
	rep    movsP
#else /* (SIZEOF_SIGSET_T % 8) == 0 */
	movP   $(SIZEOF_SIGSET_T), %Pcx                  /* count */
	rep    movsb
#endif /* (SIZEOF_SIGSET_T % 8) != 0 */


	/* Now all that's left to save is the FPU context.
	 * For this, we first have to figure out which format we should use for it.
	 * This can be done with `get_fpu_flags',  which returns the value that  we
	 * should use for the `mc_flags' field. */
	call   get_fpu_flags

	/* Save ucontext flags. (which we define identical to FPU flags)
	 * NOTE: The additional flags `FPU_FLAGS_INIT' and `FPU_FLAGS_HAVESSE'
	 *       also get saved by this, but that's OK since any unknown  flag
	 *       is silently ignored by any other APIs that use them. */
	movP   %Pax, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_FLAGS(%R_ucpP) /* Save the fpu-flags value. */

	/* Check if we're using fxsave[64], fnsave, or neither */
	ttest  mask=FPU_FLAGS_HAVESSE, loc=%Pax
	jz     .Lgetcontext_fpu_no_sse
	native_fxsave OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_FPU(%R_ucpP)
	andw   $(0x07ff), OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_FPU+OFFSET_XFPUSTATE_FOP(%R_ucpP)
	.cfi_remember_state
.Lgetcontext_fpu_done:

#ifndef __x86_64__
	/* `%Psi' was clobbered by `get_fpu_flags()' */
	movP   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PSI(%R_ucpP), %Psi
#endif /* !__x86_64__ */

	/* Load return instruction pointer */
	movP   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_PIP(%R_ucpP), %Pcx
	.cfi_register %Pip, %Pcx

	/* `%Pbp' was used for `%R_ucpP' */
	movP   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PBP(%R_ucpP), %Pbp
	.cfi_same_value %Pbp

	xorP   %Pax, %Pax /* Return `0' to indicate success. */
	jmpP   *%Pcx

	.cfi_restore_state
.Lgetcontext_fpu_no_sse:
	ttest  mask=FPU_FLAGS_HAVEFPU, loc=%Pax
	jz     .Lgetcontext_fpu_done /* No FPU at all! */
	fnsave OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_FPU(%R_ucpP)
	frstor OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_FPU(%R_ucpP)
	movw   $(0xffff), OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_FPU+OFFSET_SFPUSTATE___PAD2(%R_ucpP)
	jmp    .Lgetcontext_fpu_done

.Lgetcontext_generic_stack:
	/* Use the current %Psp as orientation for the stack's size */
#ifndef ASSUMED_ADDITIONAL_STACK_PAGES
#define ASSUMED_ADDITIONAL_STACK_PAGES 2
#endif /* !ASSUMED_ADDITIONAL_STACK_PAGES */
	movP   %Psp, %Pcx
	andP   $(PAGEMASK), %Pcx
#if ASSUMED_ADDITIONAL_STACK_PAGES != 0
	subP   $(ASSUMED_ADDITIONAL_STACK_PAGES * PAGESIZE), %Pcx
#endif /* ASSUMED_ADDITIONAL_STACK_PAGES != 0 */
	movP   %Pcx, OFFSET_UCONTEXT_STACK + OFFSET_SIGALTSTACK_SP(%R_ucpP)
	movP   $((1 + ASSUMED_ADDITIONAL_STACK_PAGES) * PAGESIZE), OFFSET_UCONTEXT_STACK + OFFSET_SIGALTSTACK_SIZE(%R_ucpP)
	jmp    .Lgetcontext_got_stack
	.cfi_endproc
#undef R_ucpP
END(libc_getcontext)
END(libc_x86_getcontext_Pax)

DEFINE_PUBLIC_ALIAS(getcontext, libc_getcontext)
#ifdef __x86_64__
DEFINE_PUBLIC_ALIAS(__x86_getcontext_rax, libc_x86_getcontext_rax)
#else /* __x86_64__ */
DEFINE_PUBLIC_ALIAS(__x86_getcontext_eax, libc_x86_getcontext_eax)
#endif /* !__x86_64__ */






/* INTERN NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_setcontext)(ucontext_t const *__restrict ucp); */
.section .text.crt.cpu.ucontext
	.cfi_startproc simple
	.cfi_signal_frame
	/* Define register unwind rules */
	.cfi_offset %Pip, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_PIP
	.cfi_offset %Pax, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PAX
	.cfi_offset %Pcx, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PCX
	.cfi_offset %Pdx, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PDX
	.cfi_offset %Pbx, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PBX
	.cfi_offset %Psp, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PSP
	.cfi_offset %Pbp, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PBP
	.cfi_offset %Psi, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PSI
	.cfi_offset %Pdi, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PDI
#if __x86_64__
	.cfi_offset %r8,  OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R8
	.cfi_offset %r9,  OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R9
	.cfi_offset %r10, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R10
	.cfi_offset %r11, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R11
	.cfi_offset %r12, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R12
	.cfi_offset %r13, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R13
	.cfi_offset %r14, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R14
	.cfi_offset %r15, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R15
#endif /* __x86_64__ */
	.cfi_offset %Pflags, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_PFLAGS
	.cfi_offset %gs, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_GS
	.cfi_offset %fs, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_FS
	.cfi_offset %es, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_ES
	.cfi_offset %ds, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_DS
	.cfi_offset %cs, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_CS
	.cfi_offset %ss, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_SS
#ifdef __x86_64__
	.cfi_offset %gs.base, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_SGBASE+OFFSET_SGBASE_GSBASE
	.cfi_offset %fs.base, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_SGBASE+OFFSET_SGBASE_FSBASE
#endif /* __x86_64__ */
INTERN_FUNCTION(libc_swapcontext)
#ifdef __x86_64__
	/* IN: ucontext_t       *%rdi = old_context;
	 * IN: ucontext_t const *%rsi = new_context; */
	.cfi_def_cfa %R_sysvabi1P, 0
#else /* __x86_64__ */
	/* IN: ucontext_t       *4(%Psp) = old_context;
	 * IN: ucontext_t const *8(%Psp) = new_context; */
/*[[[cfi{arch='i386', register='%cfa'} push %esp; add $8; deref]]]*/
	.cfi_escape 15,5,116,0,35,8,6
/*[[[end]]]*/
#endif /* !__x86_64__ */

	/* Preserve the current CPU state */
#ifdef __x86_64__
	pushP  %R_sysvabi1P
	pushP  %R_sysvabi0P
	call   libc_getcontext
	popP   %R_sysvabi0P
	popP   %R_sysvabi1P
#else /* __x86_64__ */
	movP   Pn(1)(%Psp), %Pax
	call   libc_x86_getcontext_Pax
	movP   Pn(1)(%Psp), %R_fcall0P
#endif /* !__x86_64__ */

	/* Override the registers that the previous call filled in incorrectly. */
	movP   Pn(0)(%Psp), %Pax   /* %Pip */
	movP   %Pax, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_PIP(%R_fcall0P)
	leaP   Pn(1)(%Psp), %Pax   /* %Psp */
	movP   %Pax, OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PSP(%R_fcall0P)

	/* Load the given `new_context' by use of `libc_setcontext()' */
#ifdef __x86_64__
	movP   %R_sysvabi1P, %R_sysvabi0P
	/* fallthru */
#else /* __x86_64__ */
	movP   Pn(2)(%Psp), %Pbp
	jmp    libc_x86_setcontext_Pbp
#endif /* !__x86_64__ */
END(libc_swapcontext)


INTERN_FUNCTION(libc_setcontext)
#ifdef __x86_64__
	/* IN: ucontext_t const *%rdi = ucp; */
	.cfi_def_cfa %R_sysvabi0P, 0
#else /* __x86_64__ */
	/* IN: ucontext_t const *4(%Psp) = ucp; */
/*[[[cfi{arch='i386', register='%cfa'} push %esp; add $4; deref]]]*/
	.cfi_escape 15,5,116,0,35,4,6
/*[[[end]]]*/
#endif /* !__x86_64__ */

	/* Load the given ucontext into %Pbp */
#ifdef __x86_64__
	movP   %R_fcall0P, %Pbp
#else /* __x86_64__ */
	movP   4(%Psp), %Pbp
#endif /* !__x86_64__ */
	.cfi_def_cfa %Pbp, 0
#define R_ucpP Pbp
INTERN_FUNCTION(libc_x86_setcontext_Pbp)

	/* Load the new stack pointer registers */
	movP   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PSP(%R_ucpP), %Psp

	/* Load the FPU context. (if there is one) */
	ttest  mask=FPU_FLAGS_HAVEFPU, loc=OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_FLAGS(%R_ucpP)
	jz     .Lsetcontext_donefpu
	/* Check what kind of FPU state we're dealing with. */
	cmpw   $(0xffff), OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_FPU+OFFSET_SFPUSTATE___PAD2(%R_ucpP)
	je     .Lsetcontext_noxfpu
	native_fxrstor OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_FPU(%R_ucpP)
.Lsetcontext_donefpu:
	.cfi_remember_state

	/* Load target segment registers & bases.
	 * Note  that during this, we must disable signals because the act
	 * of writing to `%gs' or `%fs' may alter the base-values, causing
	 * them to be inconsistent until we reload them manually. */
	EXTERN(libc_setsigmaskfullptr)
	call   libc_setsigmaskfullptr  /* %Pax = OLD_PROC_MASK_PTR */

	/* Copy the new ucontext's signal mask into the soon-to-be
	 * restored old signal mask buffer (which is pointed-to by
	 * `%Pax' right now)
	 *
	 * FIXME: %Pax may point into read-only memory, because of which
	 *        we may only make any  writes if the pointed-to  signal
	 *        sets  actually differ. Trying  to write otherwise must
	 *        not be done! */
	movP   %Pax, %Pdi
	leaP   OFFSET_UCONTEXT_SIGMASK(%R_ucpP), %Psi
#if (SIZEOF_SIGSET_T % SIZEOF_POINTER) == 0
	movzlP $(SIZEOF_SIGSET_T / SIZEOF_POINTER), %Pcx
	rep    movsP
#else /* (SIZEOF_SIGSET_T % SIZEOF_POINTER) == 0 */
	movzlP $(SIZEOF_SIGSET_T), %Pcx
	rep    movsb
#endif /* (SIZEOF_SIGSET_T % SIZEOF_POINTER) != 0 */

	/* Restore segment register indices */
	IF32(rdgsbaseP %Pcx) /* NOTE: Us having to save %gs.base  across this call needs to  be
	                      *       done due to a shortcoming of the x86_64 KOS kernel, which
	                      *       is set-up to clobber %gs.base during a write to %gs, even
	                      *       when the process is running in compatibility mode.
	                      * Note that this doesn't happen under the i386 KOS kernel! */
	movw   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_GS(%R_ucpP), %gs
	IF32(wrgsbaseP %Pcx)
	.cfi_same_value %gs

	IF32(rdfsbaseP %Pcx) /* See note above */
	movw   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_FS(%R_ucpP), %fs
	IF32(wrfsbaseP %Pcx)
	.cfi_same_value %fs

	/* Load the new segment base addresses. */
#ifdef __x86_64__
	movP   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_SGBASE+OFFSET_SGBASE_GSBASE(%R_ucpP), %Pcx
	wrgsbaseP %Pcx
	movP   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_SGBASE+OFFSET_SGBASE_FSBASE(%R_ucpP), %Pcx
	wrfsbaseP %Pcx
#endif /* __x86_64__ */

	/* Restore the old procmask  buffer (which in the  mean
	 * time got filled with the new ucontext's signal mask) */
#ifdef __x86_64__
	movP   %Pax, %R_sysvabi0P
	EXTERN(libc_setsigmaskptr)
	call   libc_setsigmaskptr
#else /* __x86_64__ */
	pushP  %Pax
	EXTERN(libc_setsigmaskptr)
	call   libc_setsigmaskptr
	popP   %Pax /* This pops meaningless garbage, but is needed to re-adjust the stack! */
#endif /* !__x86_64__ */

	/* Load general purpose registers except for `%Pbp'
	 * Also note that  %Psp already  got loaded  above! */
#ifdef __x86_64__
	movq   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R15(%R_ucpP), %r15
	.cfi_same_value %r15
	movq   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R14(%R_ucpP), %r14
	.cfi_same_value %r14
	movq   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R13(%R_ucpP), %r13
	.cfi_same_value %r13
	movq   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R12(%R_ucpP), %r12
	.cfi_same_value %r12
	movq   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R11(%R_ucpP), %r11
	.cfi_same_value %r11
	movq   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R10(%R_ucpP), %r10
	.cfi_same_value %r10
	movq   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R9(%R_ucpP), %r9
	.cfi_same_value %r9
	movq   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_R8(%R_ucpP), %r8
	.cfi_same_value %r8
#endif /* __x86_64__ */
	movP   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PDI(%R_ucpP), %Pdi
	.cfi_same_value %Pdi
	movP   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PSI(%R_ucpP), %Psi
	.cfi_same_value %Psi
	movP   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PBX(%R_ucpP), %Pbx
	.cfi_same_value %Pbx
	movP   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PDX(%R_ucpP), %Pdx
	.cfi_same_value %Pdx
	movP   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PCX(%R_ucpP), %Pcx
	.cfi_same_value %Pcx
	movP   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PAX(%R_ucpP), %Pax
	.cfi_same_value %Pax

	/* Push some new registers into the new stack. */
	pushP  OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_CS(%R_ucpP)     /* Return %cs */
	pushP  OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_PIP(%R_ucpP)    /* Return %Pip */
	pushP  OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_PFLAGS(%R_ucpP) /* Return %Pflags */
	popfP                                                                                /* Load %Pflags */
	.cfi_same_value %Pflags

	/* Only load %ss, %es and %ds after all of the pushs and pops above! */
	movw   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_SS(%R_ucpP), %ss
	.cfi_same_value %ss
	movw   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_ES(%R_ucpP), %es
	.cfi_same_value %es
	movw   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_DS(%R_ucpP), %ds
	.cfi_same_value %ds

	/* Restore %Pbp */
	movP   OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_CPU+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_PBP(%R_ucpP), %Pbp
	.cfi_same_value %Pbp

	/* With %Pbp now gone, tell CFI how to restore the remaining registers. */
	.cfi_reg_offset %Pip, Pn(0), %Psp
	.cfi_reg_offset %cs, Pn(1), %Psp
	.cfi_reg_value %Psp, Pn(2), %Psp

	lretP
	.cfi_restore_state
.Lsetcontext_noxfpu:
	frstor OFFSET_UCONTEXT_MCONTEXT+OFFSET_MCONTEXT_FPU(%R_ucpP)
	jmp    .Lsetcontext_donefpu
END(libc_x86_setcontext_Pbp)
#undef R_ucpP
	.cfi_endproc
END(libc_setcontext)
DEFINE_PUBLIC_ALIAS(setcontext, libc_setcontext)
DEFINE_PUBLIC_ALIAS(swapcontext, libc_swapcontext)

#ifdef __x86_64__
DEFINE_PUBLIC_ALIAS(__x86_setcontext_rbp, libc_x86_setcontext_rbp)
#else /* __x86_64__ */
DEFINE_PUBLIC_ALIAS(__x86_setcontext_ebp, libc_x86_setcontext_ebp)
#endif /* !__x86_64__ */





.section .text.crt.cpu.ucontext
	nop /* For unwinding... */
INTERN_FUNCTION(libc_makecontext_exit_thread)
	/* No CFI annotation, because we don't return! */
#ifdef __x86_64__
	xorP   %R_sysvabi0P, %R_sysvabi0P
#else /* __x86_64__ */
	pushP  $(0)
#endif /* !__x86_64__ */
	EXTERN(libc_pthread_exit)
	call   libc_pthread_exit
	hlt
END(libc_makecontext_exit_thread)







#endif /* GUARD_LIBC_LIBC_ARCH_I386_UCONTEXT_S */
