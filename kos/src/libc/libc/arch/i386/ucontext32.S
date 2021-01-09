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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_UCONTEXT32_S
#define GUARD_LIBC_LIBC_ARCH_I386_UCONTEXT32_S 1
#define _GNU_SOURCE 1
#define __ASSEMBLER__ 1

#include "../../../api.h"
/**/
#include <hybrid/compiler.h>

#include <asm/cfi.h>
#include <asm/cpu-cpuid.h>
#include <asm/instr/ttest.h>
#include <asm/pagesize.h>
#include <bits/os/kos/mcontext32.h>
#include <bits/os/kos/ucontext32.h>

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
/* Either `__MCONTEXTX32_FLAG_HAVEXFPU' or `__MCONTEXTX32_FLAG_HAVESFPU' */
PRIVATE_OBJECT(fpu_flags)
	.4byte  0x00000000 /* Uninitialized */
END(fpu_flags)



.section .text.crt.cpu.ucontext
/* Figure out how to preserve FPU registers.
 * Returns:    %eax = fpu_flags
 * Clobber:    %ecx, %edx, %ebx, %esi, %eflags */
PRIVATE_FUNCTION(get_fpu_flags)
	.cfi_startproc
	call   1f
	.cfi_adjust_cfa_offset 4
1:	popl_cfi %esi
	addl   $(_GLOBAL_OFFSET_TABLE_ + (. - 1b)), %esi
	movl   fpu_flags@GOTOFF(%esi), %eax
	testl  %eax, %eax
	jz     .Lget_fpu_flags_firstcall
	ret
.Lget_fpu_flags_firstcall:
	/* Not yet calculated.
	 * In order to determine support, we do the following:
	 * >> char const *env = getenv("HW_SSE");
	 * >> #ifdef ENVIRON_HW_SSE
	 * >> if (env && env[0] && !env[1]) {
	 * >>     if (env[0] == '1')
	 * >>         return __MCONTEXTX32_FLAG_HAVEXFPU;
	 * >>     if (env[0] == '0')
	 * >>         return __MCONTEXTX32_FLAG_HAVESFPU;
	 * >> }
	 * >> #endif // ENVIRON_HW_SSE
	 * >> if (cpuid[1].edx & CPUID_1D_SSE)
	 * >>     return __MCONTEXTX32_FLAG_HAVEXFPU;
	 * >> return __MCONTEXTX32_FLAG_HAVESFPU;
	 */
#ifdef ENVIRON_HW_SSE
	leal   str_HW_SSE@GOTOFF(%esi), %eax
	pushl_cfi %eax
	EXTERN(libc_getenv)
	call   libc_getenv
	addl   $(4), %esp
	.cfi_adjust_cfa_offset -4
	testl  %eax, %eax
	jz     .Lget_fpu_flags_noenv
	cmpb   $(0), 0(%eax)
	jz     .Lget_fpu_flags_noenv /* strlen(env) == 0 */
	cmpb   $(0), 1(%eax)
	jnz    .Lget_fpu_flags_noenv /* strlen(env) != 1 */
	cmpb   $('1'), 1(%eax)
	je     .Lget_fpu_flags_XFPU
	cmpb   $('0'), 1(%eax)
	je     .Lget_fpu_flags_SFPU
.Lget_fpu_flags_noenv:
#endif /* ENVIRON_HW_SSE */
	movl   $(1), %eax
	cpuid
	ttest  mask=CPUID_1D_SSE, loc=%edx
	jz     .Lget_fpu_flags_SFPU
.Lget_fpu_flags_XFPU:
	movl   $(__MCONTEXTX32_FLAG_HAVEXFPU), %eax
	jmp    1f
.Lget_fpu_flags_SFPU:
	movl   $(__MCONTEXTX32_FLAG_HAVESFPU), %eax
1:	movl   %eax, fpu_flags@GOTOFF(%esi)
	ret
	.cfi_endproc
END(get_fpu_flags)



.section .text.crt.cpu.ucontext
INTERN_FUNCTION(libc_getcontext)
	.cfi_startproc
	popl_cfi %eax          /* Return address */
	.cfi_register %eip, %eax
	pushl_cfi_r %edi       /* Preserve %edi */
	movl   4(%esp), %edi   /* %edi = ucontext_t *ucp */
#define UC_(offset) (offset)
#define UC(offset)  (offset)(%edi)
#define MC_(offset) (__OFFSET_UCONTEXTX32_MCONTEXT + (offset))
#define MC(offset)  (__OFFSET_UCONTEXTX32_MCONTEXT + (offset))(%edi)
#define R_(regno)   MC_(__OFFSET_MCONTEXTX32_CPU + (regno) * 4)
#define R(regno)    MC(__OFFSET_MCONTEXTX32_CPU + (regno) * 4)
	movl   %eax, R(REG_EIP) /* Return address */
	.cfi_reg_offset %eip, R_(REG_EIP), %edi

	/* Preserve %eflags */
	pushfl_cfi
	popl_cfi %eax
	movl   %eax, R(REG_EFL)
/*	.cfi_rel_offset %eflags, R_(REG_EFL) */

	/* Switch over to using `%edi' (i.e. the `ucontext_t') as CFA */
	.cfi_def_cfa %edi, 0
	.cfi_rel_offset %eip, R_(REG_EIP)
/*	.cfi_rel_offset %eflags, R_(REG_EFL) */ /* Not needed */
	.cfi_reg_offset %edi, 0, %esp
	.cfi_reg_value %esp, 4, %esp
	popl   %eax /* %edi */
	.cfi_same_value %esp
	.cfi_register %edi, %eax
	movl   %eax, R(REG_EDI)
	.cfi_rel_offset %edi, R_(REG_EDI)

	/* Also return 0 the second time around! */
	xorl   %eax, %eax
	movl   %eax, R(REG_EAX)
	movl   %eax, UC(__OFFSET_UCONTEXTX32_LINK)

	/* At this point, we've filled in `REG_EIP', `REG_EDI' and `REG_EAX'
	 * Now to fill in all of the remaining registers with proper values. */
	movl   %gs, %eax
	movl   %eax, R(REG_GS)
/*	.cfi_rel_offset %gs, R_(REG_GS) */

	movl   %fs, %eax
	movl   %eax, R(REG_FS)
/*	.cfi_rel_offset %fs, R_(REG_FS) */

	movl   %es, %eax
	movl   %eax, R(REG_ES)
/*	.cfi_rel_offset %es, R_(REG_ES) */

	movl   %ds, %eax
	movl   %eax, R(REG_DS)
/*	.cfi_rel_offset %ds, R_(REG_DS) */

	movl   %cs, %eax
	movl   %eax, R(REG_CS)
/*	.cfi_rel_offset %cs, R_(REG_CS) */

	movl   %ss, %eax
	movl   %eax, R(REG_SS)
/*	.cfi_rel_offset %ss, R_(REG_SS) */

	movl   %esi, R(REG_ESI)
	.cfi_rel_offset %esi, R_(REG_ESI) /* We're going to clobber this one, so restore during unwind! */

	movl   %ebp, R(REG_EBP)
	.cfi_rel_offset %ebp, R_(REG_EBP)

	movl   %esp, R(REG_ESP)
#if REG_UESP != REG_ESP
	movl   %esp, R(REG_UESP)
#endif /* REG_UESP != REG_ESP */
	.cfi_rel_offset %esp, R_(REG_ESP)

	movl   %ebx, R(REG_EBX)
	.cfi_rel_offset %ebx, R_(REG_EBX) /* We're going to clobber this one, so restore during unwind! */

	movl   %edx, R(REG_EDX)
	.cfi_rel_offset %edx, R_(REG_EDX)

	movl   %ecx, R(REG_ECX)
	.cfi_rel_offset %ecx, R_(REG_ECX)

	/* Fill in information about the caller's stack. */
	EXTERN(libc_pthread_self)
	call   libc_pthread_self

	ttest  mask=PTHREAD_FNOSTACK, loc=__OFFSET_PTHREAD_FLAGS(%eax)
	.cfi_remember_state
	jnz    .Lgetcontext_generic_stack
	movl   __OFFSET_PTHREAD_STACKADDR(%eax), %ecx
	movl   %ecx, UC(__OFFSET_UCONTEXTX32_STACK + __OFFSET_SIGALTSTACKX32_SP)
	movl   __OFFSET_PTHREAD_STACKSIZE(%eax), %ecx
	movl   %ecx, UC(__OFFSET_UCONTEXTX32_STACK + __OFFSET_SIGALTSTACKX32_SIZE)
.Lgetcontext_got_stack:
	xorl   %ecx, %ecx
	movl   %ecx, UC(__OFFSET_UCONTEXTX32_STACK + __OFFSET_SIGALTSTACKX32_FLAGS)

	/* Load the current signal mask */
	movl   $(__SIZEOF_SIGSET_T__),           %esi /* sigsetsize */
	leal   UC(__OFFSET_UCONTEXTX32_SIGMASK), %edx /* oset = &ucp->uc_sigmask */
/*	xorl   %ecx, %ecx */                          /* set  = NULL  (Already cleared; s.a. above) */
	movl   $(SYS_rt_sigprocmask), %eax
	call   libc___i386_syscall

	/* Now all that's left to save is the FPU context.
	 * For this, we first have to figure out which format we should use for it.
	 * This can be done with `get_fpu_flags', which returns the value that we
	 * should use for the `mc_flags' field. */
	call   get_fpu_flags
	movl   %eax, MC(__OFFSET_MCONTEXTX32_FLAGS)

	/* Check if we're using fxsave, or fnsave */
	ttest  mask=__MCONTEXTX32_FLAG_HAVEXFPU, loc=%eax
	jz     .Lgetcontext_use_fnsave
	fxsave MC(__OFFSET_MCONTEXTX32_FPU)
.Lgetcontext_done_fpu:

	/* Restore callee-preserve registers that we've clobberred. */
	movl   R(REG_EBX), %ebx
	.cfi_same_value %ebx
	movl   R(REG_ESI), %esi
	.cfi_same_value %esi
	movl   R(REG_EIP), %ecx /* %ecx = RETURN_PC */
	.cfi_register %eip, %ecx
	movl   R(REG_EDI), %edi
	.cfi_same_value %edi
	.cfi_def_cfa %esp, 0
	xorl   %eax, %eax /* Return 0 */
	jmpl   *%ecx      /* Return the caller */

	.cfi_restore_state
.Lgetcontext_use_fnsave:
	.cfi_remember_state
	fnsave MC(__OFFSET_MCONTEXTX32_FPU)
	frstor MC(__OFFSET_MCONTEXTX32_FPU)
	jmp    .Lgetcontext_done_fpu

	.cfi_restore_state
.Lgetcontext_generic_stack:
	/* Use the current %esp as orientation for the stack's size */
#ifndef ASSUMED_ADDITIONAL_STACK_PAGES
#define ASSUMED_ADDITIONAL_STACK_PAGES 2
#endif /* !ASSUMED_ADDITIONAL_STACK_PAGES */
	movl   %esp, %ecx
	andl   $(__ARCH_PAGEMASK), %ecx
#if ASSUMED_ADDITIONAL_STACK_PAGES != 0
	subl   $(ASSUMED_ADDITIONAL_STACK_PAGES * __ARCH_PAGESIZE), %ecx
#endif /* ASSUMED_ADDITIONAL_STACK_PAGES != 0 */
	movl   %ecx, UC(__OFFSET_UCONTEXTX32_STACK + __OFFSET_SIGALTSTACKX32_SP)
	movl   $((1 + ASSUMED_ADDITIONAL_STACK_PAGES) * __ARCH_PAGESIZE), \
	       UC(__OFFSET_UCONTEXTX32_STACK + __OFFSET_SIGALTSTACKX32_SIZE)
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
	.cfi_signal_frame /* We need to modify %esp, so this is required! */
	movl   4(%esp), %edi
INTERN_FUNCTION(libc_x86_setcontext_edi)
#define UC_(offset) (offset)
#define UC(offset)  (offset)(%edi)
#define MC_(offset) (__OFFSET_UCONTEXTX32_MCONTEXT + (offset))
#define MC(offset)  (__OFFSET_UCONTEXTX32_MCONTEXT + (offset))(%edi)
#define R_(regno)   MC_(__OFFSET_MCONTEXTX32_CPU + (regno) * 4)
#define R(regno)    MC(__OFFSET_MCONTEXTX32_CPU + (regno) * 4)
	/* Define CFI annotations to load the CPU context from `%edi' */
	.cfi_def_cfa %edi, 0
	.cfi_rel_offset %gs, R_(REG_GS)
	.cfi_rel_offset %fs, R_(REG_FS)
	.cfi_rel_offset %es, R_(REG_ES)
	.cfi_rel_offset %ds, R_(REG_DS)
	.cfi_rel_offset %edi, R_(REG_EDI)
	.cfi_rel_offset %esi, R_(REG_ESI)
	.cfi_rel_offset %ebp, R_(REG_EBP)
	.cfi_rel_offset %esp, R_(REG_ESP)
	.cfi_rel_offset %ebx, R_(REG_EBX)
	.cfi_rel_offset %edx, R_(REG_EDX)
	.cfi_rel_offset %ecx, R_(REG_ECX)
	.cfi_rel_offset %eax, R_(REG_EAX)
	.cfi_rel_offset %eip, R_(REG_EIP)
	.cfi_rel_offset %cs, R_(REG_CS)
	.cfi_rel_offset %eflags, R_(REG_EFL)
#if REG_UESP != REG_ESP
/*	.cfi_rel_offset %uesp, R_(REG_UESP) */
#endif /* REG_UESP != REG_ESP */
	.cfi_rel_offset %ss, R_(REG_SS)
	/* Load the correct value into %esp so we can use the target's
	 * stack as temporary storage during the transition. */
	movl   R(REG_ESP), %esp

	/* Load the FPU context. (if there is one) */
	ttest  mask=__MCONTEXTX32_FLAG_HAVEXFPU, loc=MC(__OFFSET_MCONTEXTX32_FLAGS)
	jz     .Lsetcontext_noxfpu
	.cfi_remember_state
	fxrstor MC(__OFFSET_MCONTEXTX32_FPU)
.Lsetcontext_donefpu:

	/* Load the target's signal mask. */
	movl   $(__SIZEOF_SIGSET_T__),           %esi /* sigsetsize */
	xorl   %edx, %edx                             /* oset = NULL */
	leal   UC(__OFFSET_UCONTEXTX32_SIGMASK), %ecx /* set  = &ucp->uc_sigmask */
	movl   $(SIG_SETMASK),                   %ebx /* how */
	movl   $(SYS_rt_sigprocmask), %eax
	call   libc___i386_syscall

	/* Load GP registers, except for `%edi' and `%eax' */
	movl   R(REG_ECX), %ecx
	.cfi_same_value %ecx
	movl   R(REG_EDX), %edx
	.cfi_same_value %edx
	movl   R(REG_EBX), %ebx
	.cfi_same_value %ebx
	movl   R(REG_EDI), %edi
	.cfi_same_value %edi
	movl   R(REG_ESI), %esi
	.cfi_same_value %esi
	movl   R(REG_EBP), %ebp
	.cfi_same_value %ebp
	/* Load target segment registers. */

	movw   R(REG_GS), %ax
	movw   %ax, %gs
	.cfi_same_value %gs

	movw   R(REG_FS), %ax
	movw   %ax, %fs
	.cfi_same_value %fs

	movw   R(REG_ES), %ax
	movw   %ax, %es
	.cfi_same_value %es

	movw   R(REG_DS), %ax
	movw   %ax, %ds
	.cfi_same_value %ds

	pushl  %cs:R(REG_CS)    /* Return %cs */
	pushl  %cs:R(REG_EIP)   /* Return %eip */
	pushl  %cs:R(REG_EFL)   /* Return %eflags */
	popfl                   /* Load %eflags */
	.cfi_same_value %eflags

	/* Only load %ss after all of the pushs and pops above! */
	movw   %cs:R(REG_SS), %ax
	movw   %ax, %ss
	.cfi_same_value %ss

	movl   %cs:R(REG_EAX), %eax /* Restore %eax */
	movl   %cs:R(REG_EDI), %edi /* Restore %edi */
	/* Inform CFI that all GP registers have now been restored */
	.cfi_same_value %eax
	/* Tell CFI that %eip is stored at 0(%esp) */
	.cfi_reg_offset %eip, 0, %esp
	/* Tell CFI that %cs is stored at 4(%esp) */
	.cfi_reg_offset %eip, 4, %esp
	/* Tell CFI that %esp is offset by 8 */
	.cfi_reg_value %esp, 8, %esp
	/* Return to the caller */
	lret

	.cfi_restore_state
.Lsetcontext_noxfpu:
	ttest  mask=__MCONTEXTX32_FLAG_HAVESFPU, loc=MC(__OFFSET_MCONTEXTX32_FLAGS)
	jz     .Lsetcontext_donefpu
	frstor MC(__OFFSET_MCONTEXTX32_FPU)
	jmp    .Lsetcontext_donefpu
#undef UC_
#undef UC
#undef MC_
#undef MC
#undef R_
#undef R
	.cfi_endproc
END(libc_x86_setcontext_edi)
END(libc_setcontext)



.section .text.crt.cpu.ucontext
INTERN_FUNCTION(libc_swapcontext)
	.cfi_startproc
	pushl_cfi 4(%esp)      /* oucp */
	call   libc_getcontext /* Generate the old-context */
	addl   $(4), %esp
	.cfi_adjust_cfa_offset -4
	movl   4(%esp), %edi   /* oucp */
	/* Override the registers that the previous call filled in incorrectly. */
	movl   0(%esp), %eax   /* %eip */
	movl   %eax, (__OFFSET_UCONTEXTX32_MCONTEXT + __OFFSET_MCONTEXTX32_CPU + 4 * REG_EIP)(%edi)
	leal   4(%esp), %eax   /* return-%esp */
	movl   %eax, (__OFFSET_UCONTEXTX32_MCONTEXT + __OFFSET_MCONTEXTX32_CPU + 4 * REG_ESP)(%edi)
#if REG_UESP != REG_ESP
	movl   %eax, (__OFFSET_UCONTEXTX32_MCONTEXT + __OFFSET_MCONTEXTX32_CPU + 4 * REG_UESP)(%edi)
#endif /* REG_UESP != REG_ESP */

	/* And with that, the old CPU context has been filled.
	 * Now we just have to load the new context! */
	movl   8(%esp), %edi   /* ucp */
	jmp    libc_x86_setcontext_edi /* Load context from %edi */
	.cfi_endproc
END(libc_swapcontext)


.section .text.crt.cpu.ucontext
INTERN_FUNCTION(libc_makecontext_exit_thread)
	/* No CFI annotation, because we don't return! */
	pushl  $(0)
	EXTERN(libc_pthread_exit)
	call   libc_pthread_exit
	hlt
END(libc_makecontext_exit_thread)


DEFINE_PUBLIC_ALIAS(getcontext, libc_getcontext)
DEFINE_PUBLIC_ALIAS(setcontext, libc_setcontext)
DEFINE_PUBLIC_ALIAS(__x86_setcontext_edi, libc_x86_setcontext_edi)
DEFINE_PUBLIC_ALIAS(swapcontext, libc_swapcontext)


#endif /* GUARD_LIBC_LIBC_ARCH_I386_UCONTEXT32_S */
