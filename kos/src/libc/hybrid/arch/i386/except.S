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
#ifndef GUARD_LIBC_HYBRID_ARCH_I386_EXCEPT_S
#define GUARD_LIBC_HYBRID_ARCH_I386_EXCEPT_S 1
#define __ASSEMBLER__ 1
#define _KOS_KERNEL_SOURCE 1

#include <hybrid/compiler.h>

#include <asm/cpu-flags.h>
#include <asm/instr/compat.h>
#include <asm/instr/movzxq.h>
#include <asm/instr/ttest.h>
#include <bits/va_list-struct64.h>
#include <kos/bits/exception_info.h>
#include <kos/except.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state.h>

#include <cfi.h>

#ifdef __KERNEL__
#include <kernel/compiler.h>
#include <kernel/except.h>
#include <sched/task.h>
#include <sched/rpc.h>
#else /* __KERNEL__ */
#include "../../../libc/except.h"
#endif /* !__KERNEL__ */

#ifdef __KERNEL__
EXTERN(this_exception_code)
EXTERN(this_exception_flags)
EXTERN(this_exception_trace)
EXTERN(this_exception_args)
EXTERN(this_exception_faultaddr)
EXTERN(this_exception_state)

#define FIELD_EXCEPT_CODE          %segtls:this_exception_code
#define FIELD_ERROR_FLAGS          %segtls:this_exception_flags
#define FIELD_ERROR_TRACE(off)     %segtls:this_exception_trace + (off)
#define FIELD_ERROR_POINTERS(off)  %segtls:this_exception_args + (off)
#define FIELD_ERROR_FAULTADDR      %segtls:this_exception_faultaddr
#define FIELD_ERROR_REGISTERS(off) %segtls:this_exception_state + (off)
#define SECTION_EXCEPT_TEXT        .text
#else /* __KERNEL__ */
#define FIELD_EXCEPT_CODE          OFFSET_EXCEPTION_INFO_CODE(%Pax)
#define FIELD_ERROR_FLAGS          OFFSET_EXCEPTION_INFO_FLAGS(%Pax)
#define FIELD_ERROR_POINTERS(off)  (OFFSET_EXCEPTION_INFO_POINTERS + (off))(%Pax)
#define FIELD_ERROR_FAULTADDR      (OFFSET_EXCEPTION_INFO_DATA + __OFFSET_EXCEPTION_DATA_FAULTADDR)(%Pax)
#define FIELD_ERROR_TRACE(off)     (OFFSET_EXCEPTION_INFO_TRACE + (off))(%Pax)
#define FIELD_ERROR_REGISTERS(off) (OFFSET_EXCEPTION_INFO_STATE + (off))(%Pax)
#define SECTION_EXCEPT_TEXT        .text.crt.except
#endif /* !__KERNEL__ */

#ifdef __KERNEL__
#define IK(...) __VA_ARGS__
#define IU(...) /* nothing */
#else /* __KERNEL__ */
#define IK(...) /* nothing */
#define IU(...) __VA_ARGS__
#endif /* !__KERNEL__ */

#ifndef SIZEOF_POINTER
#define SIZEOF_POINTER __SIZEOF_POINTER__
#endif /* !SIZEOF_POINTER */

#define Pn(n) (SIZEOF_POINTER * (n))



.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(except_rethrow, libc_except_rethrow)
INTERN_FUNCTION(libc_except_rethrow)
	/* ATTR_NORETURN void except_rethrow(void) */
	.cfi_startproc
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R
IU(	INTERN(libc_except_info))
IU(	call   libc_except_info)
#ifndef NDEBUG
	.cfi_remember_state
	cmpP   $(EXCEPT_CODEOF(E_OK)), FIELD_EXCEPT_CODE
	je     .Llibc_except_rethrow_outside_catch
#endif /* !NDEBUG */
	orb    $(EXCEPT_FRETHROW), FIELD_ERROR_FLAGS
.Ldo_unwind_Psp:
	movP   %Psp, %R_fcall0P
	INTERN(libc_except_unwind)
	call   libc_except_unwind
#ifndef NDEBUG
	/* Inline the call to `libc_except_unwind' so that tracebacks will  include
	 * more information about how unwinding was actually initiated if something
	 * goes wrong. */
#define goto_Ldo_unwind_Psp     \
	movP   %Psp, %R_fcall0P;    \
	INTERN(libc_except_unwind); \
	call   libc_except_unwind;  \
	jmp    .Lload_kcpustate_Pax
#else /* !NDEBUG */
#define goto_Ldo_unwind_Psp  jmp .Ldo_unwind_Psp
#endif /* NDEBUG */

.Lload_kcpustate_Pax:
	.cfi_def_cfa_register %Pax
#ifdef __x86_64__
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R15)(%rax), %r15
	.cfi_same_value %r15
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R14)(%rax), %r14
	.cfi_same_value %r14
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R13)(%rax), %r13
	.cfi_same_value %r13
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R12)(%rax), %r12
	.cfi_same_value %r12
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R11)(%rax), %r11
	.cfi_same_value %r11
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R10)(%rax), %r10
	.cfi_same_value %r10
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R9)(%rax), %r9
	.cfi_same_value %r9
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R8)(%rax), %r8
	.cfi_same_value %r8
#endif /* __x86_64__ */
	movP   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_PDI)(%Pax), %Pdi
	.cfi_same_value %Pdi
	movP   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_PSI)(%Pax), %Psi
	.cfi_same_value %Psi
	movP   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_PBP)(%Pax), %Pbp
	.cfi_same_value %Pbp
	movP   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_PBX)(%Pax), %Pbx
	.cfi_same_value %Pbx

	/* Push registers that we're going to restore later!
	 *
	 * This must be done before we write  to the target PSP in case  that
	 * target PSP overlaps  with the kcpustate  structure (in which  case
	 * we'll be overwriting the kcpustate during the stack setup, meaning
	 * that any read from the structure has to happen before then) */
	pushP  OFFSET_KCPUSTATE_PFLAGS(%Pax)
	pushP  OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_PAX(%Pax)
	pushP  OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_PDX(%Pax)

	/* Push %Pcx and the return address onto the target stack */
	movP   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_PSP(%Pax), %Pcx
	subP   $(Pn(2)), %Pcx

	/* NOTE: Push PIP first, since that one is stored closer to the bottom
	 *       of the kcpustate structure, meaning it would get  overwritten
	 *       first! */
	movP   OFFSET_KCPUSTATE_PIP(%Pax), %Pdx
	movP   %Pdx, Pn(1)(%Pcx)
	movP   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_PCX(%Pax), %Pdx
	movP   %Pdx, Pn(0)(%Pcx)

	/* Restore pushed registers */
	popP   %Pdx
	.cfi_same_value %Pdx
	popP   %Pax
	.cfi_same_value %Pax
	popfP
	.cfi_same_value %Pflags
	/* Load the target stack. */
	movP   %Pcx, %Psp
	.cfi_def_cfa %Psp, Pn(2)
	.cfi_rel_offset %Pcx, Pn(0)
	.cfi_rel_offset %Pip, Pn(1)
	/* Restore %Pcx and %Pip. */
	popP_cfi_r %Pcx
	ret
#ifndef NDEBUG
.Llibc_except_rethrow_outside_catch:
	.cfi_restore_state
	movP   %Psp, %R_fcall0P
	EXTERN(libc_except_badusage_rethrow_outside_catch)
	call   libc_except_badusage_rethrow_outside_catch
#endif /* !NDEBUG */
	.cfi_endproc
END(libc_except_rethrow)

/* This function is called when the c++ `throw;' expression is used. */
DEFINE_PUBLIC_WEAK_ALIAS(__cxa_rethrow, libc_except_rethrow)


/* NOTE: _Unwind_Resume() is more  akin to  deemon's `end finally'  instruction
 *       (with the exception of not being invoked when a finally wasn't entered
 *       because of  an exception),  rather than  `except_rethrow()', which  is
 *       equivalent to `throw except'.
 * However, since kernel exception handling  is rather simplistic, we  can
 * simply handle it the same way we handle rethrow, except that we mustn't
 * set the `EXCEPT_FRETHROW' flag. */
.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_Resume)
	.cfi_startproc
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R
#define SP_OFFSET (SIZEOF_KCPUSTATE - SIZEOF_POINTER)
#ifdef __KERNEL__
	goto_Ldo_unwind_Psp
#else /* __KERNEL__ */
	movP   L_ccall0P(SP_OFFSET), %R_fcall1P /* struct _Unwind_Exception *__restrict exception_object */
	movP   %Psp,                 %R_fcall0P /* except_register_state_t *__restrict state */
	INTERN(libc_Unwind_Resume_impl)
	call   libc_Unwind_Resume_impl
	jmp    .Lload_kcpustate_Pax
#endif /* !__KERNEL__ */
#undef SP_OFFSET
	.cfi_endproc
END(libc_Unwind_Resume)
DEFINE_PUBLIC_ALIAS(_Unwind_Resume, libc_Unwind_Resume)


#ifndef __KERNEL__
.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_RaiseException)
	.cfi_startproc
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R
#define SP_OFFSET (SIZEOF_KCPUSTATE - SIZEOF_POINTER)
	movP   L_ccall0P(SP_OFFSET), %R_fcall1P /* struct _Unwind_Exception *__restrict exception_object */
	movP   %Psp,                 %R_fcall0P /* except_register_state_t *__restrict state */
	INTERN(libc_Unwind_RaiseException_impl)
	call   libc_Unwind_RaiseException_impl
	jmp    .Lload_kcpustate_Pax
#undef SP_OFFSET
	.cfi_endproc
END(libc_Unwind_RaiseException)
DEFINE_PUBLIC_ALIAS(_Unwind_RaiseException, libc_Unwind_RaiseException)

.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_Resume_or_Rethrow)
	.cfi_startproc
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R
#define SP_OFFSET (SIZEOF_KCPUSTATE - SIZEOF_POINTER)
	movP   L_ccall0P(SP_OFFSET), %R_fcall1P /* struct _Unwind_Exception *__restrict exception_object */
	movP   %Psp,                 %R_fcall0P /* except_register_state_t *__restrict state */
	INTERN(libc_Unwind_Resume_or_Rethrow_impl)
	call   libc_Unwind_Resume_or_Rethrow_impl
	jmp    .Lload_kcpustate_Pax
#undef SP_OFFSET
	.cfi_endproc
END(libc_Unwind_Resume_or_Rethrow)
DEFINE_PUBLIC_ALIAS(_Unwind_Resume_or_Rethrow, libc_Unwind_Resume_or_Rethrow)


.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_ForcedUnwind)
	.cfi_startproc
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R
#ifdef __x86_64__
	movP   %R_sysvabi2P, %R_sysvabi3P /* void *stop_arg */
	movP   %R_sysvabi1P, %R_sysvabi2P /* _Unwind_Stop_Fn stop */
	movP   %R_sysvabi0P, %R_sysvabi1P /* struct _Unwind_Exception *__restrict exception_object */
	movP   %Psp,         %R_sysvabi0P /* except_register_state_t *__restrict state */
	INTERN(libc_Unwind_ForcedUnwind_impl)
	call   libc_Unwind_ForcedUnwind_impl
#else /* __x86_64__ */
	movP   %Psp, %R_fcall0P                   /* except_register_state_t *__restrict state */
	movP   SIZEOF_KCPUSTATE(%Psp), %R_fcall1P /* struct _Unwind_Exception *__restrict exception_object */
	pushP_cfi (SIZEOF_KCPUSTATE + 12)(%Psp)   /* void *stop_arg */
	pushP_cfi (SIZEOF_KCPUSTATE + 12)(%Psp)   /* _Unwind_Stop_Fn stop */
	INTERN(libc_Unwind_ForcedUnwind_impl)
	call   libc_Unwind_ForcedUnwind_impl
	.cfi_adjust_cfa_offset -Pn(2)
#endif /* !__x86_64__ */
	jmp    .Lload_kcpustate_Pax
	.cfi_endproc
END(libc_Unwind_ForcedUnwind)
DEFINE_PUBLIC_ALIAS(_Unwind_ForcedUnwind, libc_Unwind_ForcedUnwind)


.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_Backtrace)
	.cfi_startproc
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R
#ifdef __x86_64__
	movP   %R_sysvabi1P, %R_sysvabi2P /* void *arg */
	movP   %R_sysvabi0P, %R_sysvabi1P /* _Unwind_Trace_Fn func */
	movP   %Psp,         %R_sysvabi0P /* except_register_state_t *__restrict state */
	INTERN(libc_Unwind_Backtrace_impl)
	call   libc_Unwind_Backtrace_impl
#else /* __x86_64__ */
	movP   %Psp,                   %R_fcall0P  /* except_register_state_t *__restrict state */
	movP   SIZEOF_KCPUSTATE(%Psp), %R_fcall1P  /* _Unwind_Trace_Fn func */
	pushP_cfi (SIZEOF_KCPUSTATE + Pn(3))(%Psp) /* void *arg */
	INTERN(libc_Unwind_Backtrace_impl)
	call   libc_Unwind_Backtrace_impl
	.cfi_adjust_cfa_offset -Pn(1)
#endif /* !__x86_64__ */
	addP   $(SIZEOF_KCPUSTATE - Pn(1)), %Psp /* -Pn(1): EIP */
	.cfi_adjust_cfa_offset -(SIZEOF_KCPUSTATE - Pn(1))
	ret
	.cfi_endproc
END(libc_Unwind_Backtrace)
DEFINE_PUBLIC_ALIAS(_Unwind_Backtrace, libc_Unwind_Backtrace)


.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_except_handler3)
	.cfi_startproc simple
	.cfi_def_cfa %R_fcall0P, SIZEOF_KCPUSTATE
	ASM_CFI_REL_OFFSET_RESTORE_KCPUSTATE(0)
#ifdef __x86_64__
	andP   $-16, %Psp /* Align stack to a 16-byte boundary */
#endif /* __x86_64__ */
	movP   %R_fcall0P, %Pbp /* Preserve `except_register_state_t *__restrict state' for unwinding. */
	.cfi_def_cfa_register %Pbp
	INTERN(libc_except_handler3_impl)
	call   libc_except_handler3_impl
	jmp    .Lload_kcpustate_Pax
	.cfi_endproc
END(libc_except_handler3)
DEFINE_PUBLIC_ALIAS(except_handler3, libc_except_handler3)


.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_except_handler4)
	.cfi_startproc simple
	.cfi_def_cfa %R_fcall0P, SIZEOF_KCPUSTATE
	ASM_CFI_REL_OFFSET_RESTORE_KCPUSTATE(0)
#ifdef __x86_64__
	andP   $-16, %Psp /* Align stack to a 16-byte boundary */
#endif /* __x86_64__ */
	movP   %R_fcall0P, %Pbp /* Preserve `except_register_state_t *__restrict state' for unwinding. */
	.cfi_def_cfa_register %Pbp
	INTERN(libc_except_handler4_impl)
	call   libc_except_handler4_impl
	jmp    .Lload_kcpustate_Pax
	.cfi_endproc
END(libc_except_handler4)
DEFINE_PUBLIC_ALIAS(except_handler4, libc_except_handler4)
#endif /* !__KERNEL__ */



#if EXCEPT_BACKTRACE_SIZE != 0
#define Ldo_unwind_Psp_maybe_fill_trace Ldo_fill_trace
#else /* EXCEPT_BACKTRACE_SIZE != 0 */
#define Ldo_unwind_Psp_maybe_fill_trace Ldo_unwind_Psp
#endif /* EXCEPT_BACKTRACE_SIZE == 0 */



.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(except_thrown, libc_except_thrown)
INTERN_FUNCTION(libc_except_thrown)
	/* ATTR_NORETURN void except_thrown(except_code_t code, unsigned int argc, ...) */
	.cfi_startproc
#ifdef __x86_64__
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R
#else /* __x86_64__ */
	pushfl_cfi_r
	pushal_cfi_r
#endif /* !__x86_64__ */
/*	.cfi_rel_offset %Psp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_PSP */

IK(	cld) /* User-space may have set this one (must clear it because kernel is compiled with "-mcld") */
IU(	INTERN(libc_except_info))
IU(	call   libc_except_info)

#ifndef NDEBUG
	.cfi_remember_state
	cmpP   $(EXCEPT_CODEOF(E_OK)), FIELD_EXCEPT_CODE
	jne    .Llibc_except_thrown_inside_catch /* ERROR: Call to `THROW()' inside of `catch' */
#endif /* !NDEBUG */

	/* Fill in the per-task exception context. */
#ifdef __x86_64__
IK(	movq   %rax, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RAX))
IK(	movq   %rcx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RCX))
IK(	movq   %rdx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RDX))
IK(	movq   %rdi, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RDI))
IK(	movq   %rsi, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RSI))
IK(	movq   %r8,  FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R8))
IK(	movq   %r9,  FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R9))
IK(	movq   %r10, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R10))
IK(	movq   %r11, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R11))
	/* Always save %rbx now, since we're using it as a temporary register next. */
	movq   %rbx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RBX)
	/* The call to `libc_except_info()' (may) have clobbered rax, rcx, rdx
	 * So  instead,  we  must  copy   these  registers  from  the   stack. */
IU(	movq   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RAX(%rsp), %rbx)
IU(	movq   %rbx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RAX))
IU(	movq   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RCX(%rsp), %rbx)
IU(	movq   %rbx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RCX))
IU(	movq   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RDX(%rsp), %rbx)
IU(	movq   %rbx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RDX))
IU(	movq   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RDI(%rsp), %rbx)
IU(	movq   %rbx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RDI))
IU(	movq   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RSI(%rsp), %rbx)
IU(	movq   %rbx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RSI))
IU(	movq   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R8(%rsp), %rbx)
IU(	movq   %rbx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R8))
IU(	movq   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R9(%rsp), %rbx)
IU(	movq   %rbx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R9))
IU(	movq   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R10(%rsp), %rbx)
IU(	movq   %rbx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R10))
IU(	movq   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R11(%rsp), %rbx)
IU(	movq   %rbx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R11))
	/* Save registers that will have always been preserved. */
	movq   %r12, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R12)
	movq   %r13, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R13)
	movq   %r14, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R14)
	movq   %r15, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R15)
	leaq   SIZEOF_KCPUSTATE(%rsp), %rbx
	movq   %rbx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RSP)
	movq   %rbp, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RBP)
	movq   OFFSET_KCPUSTATE_RFLAGS(%rsp), %rbx
	movq   %rbx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_RFLAGS)
	movq   OFFSET_KCPUSTATE_RIP(%rsp), %rbx
	movq   %rbx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_RIP)
	movq   %rbx, FIELD_ERROR_FAULTADDR
#else /* __x86_64__ */
	/* The call to `libc_except_info()' (may) have clobbered eax, ecx, edx
	 * So  instead,  we  must  copy   these  registers  from  the   stack. */
IK(	movl   %eax, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX))
IK(	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX))
IK(	movl   %edx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX))
IU(	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX(%esp), %ecx)
IU(	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX))
IU(	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX(%esp), %ecx)
IU(	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX))
IU(	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX(%esp), %ecx)
IU(	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX))
	movl   %ebx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EBX)
	movl   %ebp, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EBP)
	movl   %esi, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESI)
	movl   %edi, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDI)
	movl   OFFSET_KCPUSTATE_EFLAGS(%esp), %ecx
	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_EFLAGS)
	movl   OFFSET_KCPUSTATE_EIP(%esp), %ecx
	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_EIP)
	movl   %ecx, FIELD_ERROR_FAULTADDR
#endif /* !__x86_64__ */


	/* Copy exception information. */
	movb   $(EXCEPT_FNORMAL), FIELD_ERROR_FLAGS
#ifdef __x86_64__
	/* %edi:                          except_code_t code
	 * %esi:                          unsigned int argc
	 * %rdx:                          ptr0
	 * %rcx:                          ptr1
	 * %r8:                           ptr2
	 * %r9:                           ptr3
	 * (SIZEOF_KCPUSTATE + 0)(%rsp):  ptr4
	 * (SIZEOF_KCPUSTATE + 8)(%rsp):  ptr5
	 * (SIZEOF_KCPUSTATE + 16)(%rsp): ptr6
	 * (SIZEOF_KCPUSTATE + 24)(%rsp): ptr7
	 * (SIZEOF_KCPUSTATE + 32)(%rsp): ptr8 */
IU(	movq   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RDI(%rsp), %rdi)
IU(	movzlq OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RSI(%rsp), %rsi)
IK(	movzlq %esi, %rsi)
	movq   %rdi, FIELD_EXCEPT_CODE
	cmpq   $(1), %rsi
	jb     .Lclear_unused_exception_pointers /* 0 */
IU(	movq   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RDX(%rsp), %rdx)
	movq   %rdx, FIELD_ERROR_POINTERS(0 * 8)
	je     .Lclear_unused_exception_pointers /* 1 */
IU(	movq   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RCX(%rsp), %rcx)
	movq   %rcx, FIELD_ERROR_POINTERS(1 * 8)
	cmpq   $(3), %rsi
	jb     .Lclear_unused_exception_pointers /* 2 */
IU(	movq   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R8(%rsp), %r8)
	movq   %r8, FIELD_ERROR_POINTERS(2 * 8)
	je     .Lclear_unused_exception_pointers /* 3 */
IU(	movq   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R9(%rsp), %r9)
	movq   %r9, FIELD_ERROR_POINTERS(3 * 8)
#if EXCEPTION_DATA_POINTERS >= 5
	cmpq   $(4), %rsi
	jbe    .Lclear_unused_exception_pointers /* 4 */
	/* assume(%rsi >= 5); */
	/* Copy any remaining arguments. */
	movq   %rsi, %rdx
	leaq   -4(%rsi), %rcx
	leaq   SIZEOF_KCPUSTATE(%rsp), %rsi /* %rsi = &ptr4 */
IK(	movq   $(this_exception_args + (4 * 8)), %rdi)
IK(	addq   %gs:0, %rdi  /* %rdi = &%gs:this_exception_args */)
IU(	leaq   (OFFSET_EXCEPTION_INFO_POINTERS + (4 * 8))(%rax), %rdi /* %rdi = &libc_except_info()->ei_pointers */)
	rep    movsq
	movq   %rdx, %rsi
#endif /* EXCEPTION_DATA_POINTERS >= 5 */
.Lclear_unused_exception_pointers:
	/* Check if `%rdx < EXCEPTION_DATA_POINTERS', and fill
	 * any pointers that  weren't given  with all  zeroes. */
	cmpq   $(EXCEPTION_DATA_POINTERS), %rsi
	jae    .Ldo_unwind_Psp_maybe_fill_trace

IK(	movq   $(this_exception_args), %rdi)
IK(	addq   %gs:0, %rdi                                /* %rdi = &%gs:this_exception_args */)
IU(	leaq   OFFSET_EXCEPTION_INFO_POINTERS(%rax), %rdi /* %rdi = &libc_except_info()->ei_pointers */)
	leaq   (%rdi, %rsi, 8), %rdi
	movq   $(EXCEPTION_DATA_POINTERS), %rcx
	subq   %rsi, %rcx /* RCX = EXCEPTION_DATA_POINTERS - RSI */
IU(	pushq_cfi %rax)
	xorq   %rax, %rax
	rep    stosq
IU(	popq_cfi  %rax)
	jmp    .Ldo_unwind_Psp_maybe_fill_trace
#else /* __x86_64__ */
	leal   SIZEOF_KCPUSTATE(%esp), %esi /* %esi = &code  (== return-sp) */
	movl   %esi, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP(%esp)
	movl   %esi, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP)
IK(	movl   $(this_exception_code), %edi)
IK(	addl   %fs:0, %edi                            /* %edi = &%fs:this_exception_code */)
IU(	leal   OFFSET_EXCEPTION_INFO_CODE(%eax), %edi /* %edi = &libc_except_info()->ei_code */)
#if EXCEPT_BACKTRACE_SIZE != 0
IU(	pushl_cfi %eax)
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	lodsl  /* %eax = code */
	stosl  /* %fs:this_exception_code = code */
	movl   %edi, %edx
	lodsl  /* %eax = argc */
	movl   %eax, %ecx
	testl  %ecx, %ecx
	jz     2f  /* if (!EAX) goto 2f; */
1:	lodsl  /* %eax = READ_POINTER() */
	stosl  /* WRITE_POINTER(%eax) */
	loop   1b
2:	/* Fill in undefined pointers with NULL */
	movl   %edi, %eax
	subl   %edx, %eax
	shrl   $(2), %eax  /* EAX = (P - this_exception_args) / 4 */
	movl   $EXCEPTION_DATA_POINTERS, %ecx
	subl   %eax, %ecx  /* ECX = EXCEPTION_DATA_POINTERS - EAX; (Number of unset pointers) */
	xorl   %eax, %eax
	rep    stosl       /* Set all unset pointers to NULL */
#if EXCEPT_BACKTRACE_SIZE != 0
IU(	popl_cfi %eax)
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	jmp    .Ldo_unwind_Psp_maybe_fill_trace
#endif /* !__x86_64__ */

#ifndef NDEBUG
	.cfi_restore_state
.Llibc_except_thrown_inside_catch:
	/* ATTR_NORETURN void except_thrown(except_code_t code, unsigned int argc, ...) */
#ifdef __x86_64__
	/* Pass arguments */
	pushq_cfi %r9
	pushq_cfi %r8
	pushq_cfi %rcx
	pushq_cfi %rdx

	movq   %rsi, %rdx  /* size_t argc */
	movq   %rdi, %rsi  /* except_code_t code */
	leaq   (4*8)(%rsp), %rdi /* except_register_state_t const *state */
	leaq   -OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_RDX(%rsp), %rax
	pushq_cfi %rax     /* vl_reg_save_area */
	pushq_cfi (OFFSET_KCPUSTATE64_GPREGS + OFFSET_GPREGS64_RSP)(%rdi) /* vl_overflow_arg_area (== state->kcs_gpregs.gp_rsp) */
	pushq_cfi $(5 * 8) /* vl_gp_offset */
	movq   %rsp, %rcx  /* va_list args */
#else /* __x86_64__ */
	/* Fix %esp within `state' */
	addl   $((SIZEOF_KCPUSTATE - OFFSET_KCPUSTATE_GPREGS) - OFFSET_KCPUSTATE_EFLAGS), \
	          OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP(%esp)
	/* Pass arguments */
	leal   SIZEOF_KCPUSTATE(%esp), %esi /* %esi = &code */
	lodsl             /* %eax = code */
	movl   %esp, %ecx /* except_register_state_t const *state */
	movl   %eax, %edx /* except_code_t code */
	lodsl             /* %eax = argc, %edi == &[argv] */
	pushl_cfi %edi    /* va_list args */
	pushl_cfi %eax    /* size_t argc */
#endif /* !__x86_64__ */
	EXTERN(libc_except_badusage_throw_inside_catch)
	call   libc_except_badusage_throw_inside_catch
	nop    /* For unwinding */
#endif /* !NDEBUG */
	.cfi_endproc
END(libc_except_thrown)



.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(except_throw, libc_except_throw)
INTERN_FUNCTION(libc_except_throw)
	.cfi_startproc
	/* ATTR_NORETURN void FCALL except_throw(except_code_t code) */

#ifdef __x86_64__
IU(	.cfi_remember_state)
IU(	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R)
IU(	INTERN(libc_except_info))
IU(	call   libc_except_info)
IU(	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RDI)(%rsp), %rdi)
#ifndef NDEBUG
IK(	.cfi_remember_state)
	cmpq   $(EXCEPT_CODEOF(E_OK)), FIELD_EXCEPT_CODE
	jne    .Llibc_except_throw_inside_catch /* ERROR: Call to `THROW()' inside of `catch' */
#endif /* !NDEBUG */
	movq   %rdi, FIELD_EXCEPT_CODE
#if EXCEPTION_DATA_POINTERS != 0
	.Lindex = 0
	.rept EXCEPTION_DATA_POINTERS
	movq   $(0), FIELD_ERROR_POINTERS(.Lindex)
	.Lindex = .Lindex + 8
	.endr
#endif /* EXCEPTION_DATA_POINTERS != 0 */
IU(	jmp    1f)
IU(	.cfi_restore_state)
DEFINE_PUBLIC_ALIAS(except_throw_current, libc_except_throw_current)
INTERN_FUNCTION(libc_except_throw_current)
	/* ATTR_NORETURN void except_throw_current(void) */
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R
IU(	INTERN(libc_except_info))
IU(	call   libc_except_info)
IU(1:)
	/* Fill in the per-task exception context. */
IK(	movq   %rax, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RAX))
IK(	movq   %rcx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RCX))
IK(	movq   %rdx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RDX))
	/* The call to `libc_except_info()' (may) have clobbered rax, rcx, rdx
	 * So  instead,  we  must  copy   these  registers  from  the   stack. */
IU(	movq   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RAX(%rsp), %rcx)
IU(	movq   %rcx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RAX))
IU(	movq   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RCX(%rsp), %rcx)
IU(	movq   %rcx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RCX))
IU(	movq   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RDX(%rsp), %rcx)
IU(	movq   %rcx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RDX))
	movq   %rbx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RBX)
	leaq   SIZEOF_KCPUSTATE(%rsp), %rcx
	movq   %rcx, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RSP(%rsp)
	movq   %rcx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RSP)
	movq   %rbp, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RBP)
	movq   %rsi, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RSI)
	movq   %rdi, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RDI)
	movq   OFFSET_KCPUSTATE_RFLAGS(%rsp), %rcx
	movq   %rcx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_RFLAGS)
	movq   OFFSET_KCPUSTATE_RIP(%rsp), %rcx
	movq   %rcx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_RIP)
/*	movq   %rcx, FIELD_ERROR_FAULTADDR */
	movb   $(EXCEPT_FNORMAL), FIELD_ERROR_FLAGS
#if EXCEPT_BACKTRACE_SIZE != 0
.Ldo_fill_trace:
	.Lindex = 0
.rept EXCEPT_BACKTRACE_SIZE
	movq   $(0), FIELD_ERROR_TRACE(.Lindex)
	.Lindex = .Lindex + 8
.endr
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	goto_Ldo_unwind_Psp
#ifndef NDEBUG
IK(	.cfi_restore_state)
.Llibc_except_throw_inside_catch:
IK(	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R)
	/* Pass arguments */
	movq   %rdi, %rsi  /* except_code_t code */
	movq   %rsp, %rdi  /* except_register_state_t const *state */
	xorq   %rdx, %rdx  /* size_t argc */
	pushq_cfi %rsp     /* vl_reg_save_area (must be a readable pointer, but doesn't matter) */
	pushq_cfi %rsp     /* vl_overflow_arg_area (must be a readable pointer, but doesn't matter) */
	pushq_cfi $(6 * 8) /* vl_gp_offset */
	movq   %rsp, %rcx  /* va_list args */
	EXTERN(libc_except_badusage_throw_inside_catch)
	call   libc_except_badusage_throw_inside_catch
	nop    /* For unwinding */
#endif /* !NDEBUG */
#else /* __x86_64__ */
IU(	.cfi_remember_state)
IU(	pushfl_cfi_r)
IU(	pushal_cfi_r)
IU(	INTERN(libc_except_info))
IU(	call   libc_except_info)
IU(	movl   OFFSET_GPREGS_ECX(%esp), %ecx) /* Reload %ecx, which may have been clobbered by `libc_except_info()' */
#ifndef NDEBUG
IK(	.cfi_remember_state)
	cmpl   $(EXCEPT_CODEOF(E_OK)), FIELD_EXCEPT_CODE
	jne    .Llibc_except_throw_inside_catch /* ERROR: Call to `THROW()' inside of `catch' */
#endif /* !NDEBUG */
	movl   %ecx, FIELD_EXCEPT_CODE
#if EXCEPTION_DATA_POINTERS != 0
	.Lindex = 0
	.rept  EXCEPTION_DATA_POINTERS
	movl   $(0), FIELD_ERROR_POINTERS(.Lindex)
	.Lindex = .Lindex + 4
	.endr
#endif /* EXCEPTION_DATA_POINTERS != 0 */
IU(	jmp    1f)
IU(	.cfi_restore_state)
DEFINE_PUBLIC_ALIAS(except_throw_current, libc_except_throw_current)
INTERN_FUNCTION(libc_except_throw_current)
	/* ATTR_NORETURN void except_throw_current(void) */
	pushfl_cfi_r
	pushal_cfi_r
IU(	INTERN(libc_except_info))
IU(	call   libc_except_info)
IU(1:)
	/* Fill in the per-task exception context. */
IK(	movl   %eax, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX))
IK(	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX))
IK(	movl   %edx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX))
	/* The call to `libc_except_info()' (may) have clobbered eax, ecx, edx
	 * So  instead,  we  must  copy   these  registers  from  the   stack. */
IU(	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX(%esp), %ecx)
IU(	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX))
IU(	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX(%esp), %ecx)
IU(	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX))
IU(	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX(%esp), %ecx)
IU(	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX))
	movl   %ebx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EBX)
	leal   SIZEOF_KCPUSTATE(%esp), %ecx
	movl   %ecx, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP(%esp)
	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP)
	movl   %ebp, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EBP)
	movl   %esi, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESI)
	movl   %edi, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDI)
	movl   OFFSET_KCPUSTATE_EFLAGS(%esp), %ecx
	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_EFLAGS)
	movl   OFFSET_KCPUSTATE_EIP(%esp), %ecx
	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_EIP)
/*	movl   %ecx, FIELD_ERROR_FAULTADDR */
	movb   $(EXCEPT_FNORMAL), FIELD_ERROR_FLAGS
#if EXCEPT_BACKTRACE_SIZE != 0
.Ldo_fill_trace:
	.Lindex = 0
	.rept  EXCEPT_BACKTRACE_SIZE-1
	movl   $(0), FIELD_ERROR_TRACE(.Lindex)
	.Lindex = .Lindex + 4
	.endr
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	goto_Ldo_unwind_Psp
#ifndef NDEBUG
IK(	.cfi_restore_state)
.Llibc_except_throw_inside_catch:
IK(	pushfl_cfi_r)
IK(	pushal_cfi_r)
	/* Fix %esp within `state' */
	addl   $((SIZEOF_KCPUSTATE - OFFSET_KCPUSTATE_GPREGS) - OFFSET_KCPUSTATE_EFLAGS), \
	          OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP(%esp)
	/* Pass arguments */
	movl   %ecx, %edx /* except_code_t code */
	movl   %esp, %ecx /* except_register_state_t const *state */
	pushl_cfi $(0)    /* va_list args */
	pushl_cfi $(0)    /* size_t argc */
	EXTERN(libc_except_badusage_throw_inside_catch)
	call   libc_except_badusage_throw_inside_catch
	nop    /* For unwinding */
#endif /* !NDEBUG */
#endif /* !__x86_64__ */
END(libc_except_throw_current)
	.cfi_endproc
END(libc_except_throw)




.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(_except_check_no_nesting, libc__except_check_no_nesting)
DEFINE_PUBLIC_ALIAS(_except_badusage_no_nesting, libc__except_badusage_no_nesting)
INTERN_FUNCTION(libc__except_check_no_nesting)
	.cfi_startproc
IU(	INTERN(libc_except_info))
IU(	call   libc_except_info)
	cmpP   $(EXCEPT_CODEOF(E_OK)), FIELD_EXCEPT_CODE
	jne    libc__except_badusage_no_nesting /* ERROR: Illegal TRY-nesting */
	ret
INTERN_FUNCTION(libc__except_badusage_no_nesting)
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R /* FIXME: User-space call to "libc_except_info()" clobbered a bunch of registers already */
	movP   %Psp, %R_fcall0P
	EXTERN(libc_except_badusage_no_nesting)
	call   libc_except_badusage_no_nesting
	nop    /* For unwinding... */
END(libc__except_badusage_no_nesting)
	.cfi_endproc
END(libc__except_check_no_nesting)


#endif /* !GUARD_LIBC_HYBRID_ARCH_I386_EXCEPT_S */
