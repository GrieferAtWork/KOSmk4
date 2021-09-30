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
#ifndef GUARD_LIBC_HYBRID_ARCH_I386_EXCEPT64_S
#define GUARD_LIBC_HYBRID_ARCH_I386_EXCEPT64_S 1
#define __ASSEMBLER__ 1
#define _KOS_KERNEL_SOURCE 1

#include <hybrid/compiler.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/movzxq.h>
#include <asm/instr/ttest.h>
#include <bits/va_list-struct64.h>
#include <kos/except.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>

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

#define FIELD_ERROR_CODE           %gs:this_exception_code
#define FIELD_ERROR_FLAGS          %gs:this_exception_flags
#define FIELD_ERROR_TRACE(off)     %gs:this_exception_trace + (off)
#define FIELD_ERROR_POINTERS(off)  %gs:this_exception_args + (off)
#define FIELD_ERROR_FAULTADDR      %gs:this_exception_faultaddr
#define FIELD_ERROR_REGISTERS(off) %gs:this_exception_state + (off)
#define SECTION_EXCEPT_TEXT        .text
#else /* __KERNEL__ */
#define FIELD_ERROR_CODE            OFFSET_EXCEPTION_INFO_CODE(%rax)
#define FIELD_ERROR_FLAGS           OFFSET_EXCEPTION_INFO_FLAGS(%rax)
#define FIELD_ERROR_POINTERS(off)  (OFFSET_EXCEPTION_INFO_POINTERS + (off))(%rax)
#define FIELD_ERROR_FAULTADDR      (OFFSET_EXCEPTION_INFO_DATA + __OFFSET_EXCEPTION_DATA_FAULTADDR)(%rax)
#define FIELD_ERROR_TRACE(off)     (OFFSET_EXCEPTION_INFO_TRACE + (off))(%rax)
#define FIELD_ERROR_REGISTERS(off) (OFFSET_EXCEPTION_INFO_STATE + (off))(%rax)
#define SECTION_EXCEPT_TEXT        .text.crt.except
#endif /* !__KERNEL__ */

#ifdef __KERNEL__
#define IK(...) __VA_ARGS__
#define IU(...) /* nothing */
#else /* __KERNEL__ */
#define IK(...) /* nothing */
#define IU(...) __VA_ARGS__
#endif /* !__KERNEL__ */


.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(error_rethrow, libc_error_rethrow)
INTERN_FUNCTION(libc_error_rethrow)
	/* ATTR_NORETURN void error_rethrow(void) */
	.cfi_startproc
	.cfi_signal_frame
	ASM_PUSH_KCPUSTATE_AFTER_RIP
IU(	INTERN(libc_error_info))
IU(	call   libc_error_info)
#ifndef NDEBUG
	.cfi_remember_state
	cmpq   $(ERROR_CODEOF(E_OK)), FIELD_ERROR_CODE
	je     .Llibc_error_rethrow_outside_catch
#endif /* !NDEBUG */
	orb    $(EXCEPT_FRETHROW), FIELD_ERROR_FLAGS
.Ldo_unwind_rsp:
	movq   %rsp, %rdi
	INTERN(libc_error_unwind)
	call   libc_error_unwind
#ifndef NDEBUG
	/* Inline the call to `libc_error_unwind'  so that tracebacks will  include
	 * more information about how unwinding was actually initiated if something
	 * goes wrong. */
#define goto_Ldo_unwind_rsp    \
	movq   %rsp, %rdi;         \
	INTERN(libc_error_unwind); \
	call   libc_error_unwind;  \
	jmp    .Lload_kcpustate_rax
#else /* !NDEBUG */
#define goto_Ldo_unwind_rsp  jmp .Ldo_unwind_rsp
#endif /* NDEBUG */

.Lload_kcpustate_rax:
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R15)(%rax), %r15
	.cfi_same_value %r15
	.cfi_def_cfa_register %rax
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
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RDI)(%rax), %rdi
	.cfi_same_value %rdi
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RSI)(%rax), %rsi
	.cfi_same_value %rsi
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RBP)(%rax), %rbp
	.cfi_same_value %rbp
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RBX)(%rax), %rbx
	.cfi_same_value %rbx
	/* Push    registers    that   we're    going   to    restore   later!
	 * This  must  be done  before  we write  to  the target  ESP  in case
	 * that  target ESP  overlaps with  the kcpustate  structure (in which
	 * case  we'll be  overwriting the  kcpustate during  the stack setup,
	 * meaning that any read from the structure has to happen before then) */
	pushq  OFFSET_KCPUSTATE_RFLAGS(%rax)
	pushq  (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RAX)(%rax)
	pushq  (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RDX)(%rax)
	/* Push %rcx and the return address onto the target stack */
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RSP)(%rax), %rcx
	subq   $(16), %rcx
	/* NOTE: Push EIP first, since that one is stored closer to the bottom
	 *       of the kcpustate structure, meaning it would get  overwritten
	 *       first! */
	movq   OFFSET_KCPUSTATE_RIP(%rax), %rdx
	movq   %rdx, 8(%rcx)
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RCX)(%rax), %rdx
	movq   %rdx, 0(%rcx)
	/* Restore pushed registers */
	popq   %rdx
	.cfi_same_value %rdx
	popq   %rax
	.cfi_same_value %rax
	popfq
	.cfi_same_value %rflags
	/* Load the target stack. */
	movq   %rcx, %rsp
	.cfi_def_cfa %rsp, 16
	.cfi_rel_offset %rcx, 0
	.cfi_rel_offset %rip, 8
	/* Restore %rcx and %rip. */
	popq_cfi_r %rcx
	ret
#ifndef NDEBUG
.Llibc_error_rethrow_outside_catch:
	.cfi_restore_state
	movq   %rsp, %rdi
	EXTERN(libc_except_badusage_rethrow_outside_catch)
	call   libc_except_badusage_rethrow_outside_catch
#endif /* !NDEBUG */
	.cfi_endproc
END(libc_error_rethrow)

/* This function is called when the c++ `throw;' expression is used. */
DEFINE_PUBLIC_WEAK_ALIAS(__cxa_rethrow, libc_error_rethrow)

#ifdef __KERNEL__
/* NOTE: _Unwind_Resume() is more akin to deemon's `end finally' instruction
 *      (with the exception of not being invoked when a finally wasn't entered
 *       because of an exception), rather than `error_rethrow()', which is
 *       equivalent to `throw except'.
 *       However, since kernel exception handling is rather simplistic, we can
 *       simply handle it the same way we handle rethrow! */
.section .text
PUBLIC_FUNCTION(_Unwind_Resume)
	.cfi_startproc
	.cfi_signal_frame
	ASM_PUSH_KCPUSTATE_AFTER_RIP
	goto_Ldo_unwind_rsp
	.cfi_endproc
END(_Unwind_Resume)

#else /* __KERNEL__ */

.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_RaiseException)
	.cfi_startproc
	.cfi_signal_frame
	ASM_PUSH_KCPUSTATE_AFTER_RIP
	movq   %rdi, %rsi /* struct _Unwind_Exception *__restrict exception_object */
	movq   %rsp, %rdi /* error_register_state_t *__restrict state */
	INTERN(libc_Unwind_RaiseException_impl)
	call   libc_Unwind_RaiseException_impl
	jmp    .Lload_kcpustate_rax
	.cfi_endproc
END(libc_Unwind_RaiseException)
DEFINE_PUBLIC_ALIAS(_Unwind_RaiseException, libc_Unwind_RaiseException)


.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_Resume)
	.cfi_startproc
	.cfi_signal_frame
	ASM_PUSH_KCPUSTATE_AFTER_RIP
	movq   %rdi, %rsi /* struct _Unwind_Exception *__restrict exception_object */
	movq   %rsp, %rdi /* error_register_state_t *__restrict state */
	INTERN(libc_Unwind_Resume_impl)
	call   libc_Unwind_Resume_impl
	jmp    .Lload_kcpustate_rax
	.cfi_endproc
END(libc_Unwind_Resume)
DEFINE_PUBLIC_ALIAS(_Unwind_Resume, libc_Unwind_Resume)


.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_Resume_or_Rethrow)
	.cfi_startproc
	.cfi_signal_frame
	ASM_PUSH_KCPUSTATE_AFTER_RIP
	movq   %rdi, %rsi /* struct _Unwind_Exception *__restrict exception_object */
	movq   %rsp, %rdi /* error_register_state_t *__restrict state */
	INTERN(libc_Unwind_Resume_or_Rethrow_impl)
	call   libc_Unwind_Resume_or_Rethrow_impl
	jmp    .Lload_kcpustate_rax
	.cfi_endproc
END(libc_Unwind_Resume_or_Rethrow)
DEFINE_PUBLIC_ALIAS(_Unwind_Resume_or_Rethrow, libc_Unwind_Resume_or_Rethrow)


.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_ForcedUnwind)
	.cfi_startproc
	.cfi_signal_frame
	ASM_PUSH_KCPUSTATE_AFTER_RIP
	movq   %rdx, %rcx /* void *stop_arg */
	movq   %rsi, %rdx /* _Unwind_Stop_Fn stop */
	movq   %rdi, %rsi /* struct _Unwind_Exception *__restrict exception_object */
	movq   %rsp, %rdi /* error_register_state_t *__restrict state */
	INTERN(libc_Unwind_ForcedUnwind_impl)
	call   libc_Unwind_ForcedUnwind_impl
	.cfi_adjust_cfa_offset -8
	jmp    .Lload_kcpustate_rax
	.cfi_endproc
END(libc_Unwind_ForcedUnwind)
DEFINE_PUBLIC_ALIAS(_Unwind_ForcedUnwind, libc_Unwind_ForcedUnwind)


.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_Backtrace)
	.cfi_startproc
	.cfi_signal_frame
	ASM_PUSH_KCPUSTATE_AFTER_RIP
	movq   %rsi, %rdx /* void *arg */
	movq   %rdi, %rsi /* _Unwind_Trace_Fn func */
	movq   %rsp, %rdi /* error_register_state_t *__restrict state */
	INTERN(libc_Unwind_Backtrace_impl)
	call   libc_Unwind_Backtrace_impl
	addq   $(SIZEOF_KCPUSTATE - 8), %rsp /* -8: EIP */
	.cfi_adjust_cfa_offset -(SIZEOF_KCPUSTATE - 8)
	ret
	.cfi_endproc
END(libc_Unwind_Backtrace)
DEFINE_PUBLIC_ALIAS(_Unwind_Backtrace, libc_Unwind_Backtrace)




.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_except_handler3)
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %rdi, SIZEOF_KCPUSTATE
	ASM_CFI_REL_OFFSET_RESTORE_KCPUSTATE(0)
	movq   %rdi, %rbp /* Preserve `error_register_state_t *__restrict state' for unwinding. */
	.cfi_def_cfa_register %rbp
	INTERN(libc_except_handler3_impl)
	call   libc_except_handler3_impl
	jmp    .Lload_kcpustate_rax
	.cfi_endproc
END(libc_except_handler3)
DEFINE_PUBLIC_ALIAS(except_handler3, libc_except_handler3)

.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_except_handler4)
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %rdi, SIZEOF_KCPUSTATE
	ASM_CFI_REL_OFFSET_RESTORE_KCPUSTATE(0)
	movq   %rdi, %rbp /* Preserve `error_register_state_t *__restrict state' for unwinding. */
	.cfi_def_cfa_register %rbp
	INTERN(libc_except_handler4_impl)
	call   libc_except_handler4_impl
	jmp    .Lload_kcpustate_rax
	.cfi_endproc
END(libc_except_handler4)
DEFINE_PUBLIC_ALIAS(except_handler4, libc_except_handler4)

#endif /* !__KERNEL__ */



#if EXCEPT_BACKTRACE_SIZE != 0
#define Ldo_unwind_rsp_maybe_fill_trace Ldo_fill_trace
#else /* EXCEPT_BACKTRACE_SIZE != 0 */
#define Ldo_unwind_rsp_maybe_fill_trace Ldo_unwind_rsp
#endif /* EXCEPT_BACKTRACE_SIZE == 0 */


.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(error_thrown, libc_error_thrown)
INTERN_FUNCTION(libc_error_thrown)
	/* ATTR_NORETURN void error_thrown(error_code_t code, unsigned int argc, ...) */
	.cfi_startproc
	ASM_PUSH_KCPUSTATE_AFTER_RIP
IU(	INTERN(libc_error_info))
IU(	call   libc_error_info)
#ifndef NDEBUG
	.cfi_remember_state
	cmpq   $(ERROR_CODEOF(E_OK)), FIELD_ERROR_CODE
	jne    .Llibc_error_thrown_inside_catch /* ERROR: Call to `THROW()' inside of `catch' */
#endif /* !NDEBUG */
/*	.cfi_rel_offset %rsp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RSP */
	/* Fill in the per-task exception context. */
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
	/* The call to `libc_error_info()' (may) have clobbered rax, rcx, rdx
	 * So  instead,  we  must  copy  these  registers  from  the   stack. */
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
	/* Copy exception information. */
	movb   $(EXCEPT_FNORMAL), FIELD_ERROR_FLAGS

	/* %edi:                          error_code_t code
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
	movq   %rdi, FIELD_ERROR_CODE
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
IU(	leaq   (OFFSET_EXCEPTION_INFO_POINTERS + (4 * 8))(%rax), %rdi /* %rdi = &libc_error_info()->ei_pointers */)
	rep    movsq
	movq   %rdx, %rsi
#endif /* EXCEPTION_DATA_POINTERS >= 5 */
.Lclear_unused_exception_pointers:
	/* Check if `%rdx < EXCEPTION_DATA_POINTERS', and fill
	 * any pointers that  weren't given  with all  zeroes. */
	cmpq   $(EXCEPTION_DATA_POINTERS), %rsi
	jae    .Ldo_unwind_rsp_maybe_fill_trace

IK(	movq   $(this_exception_args), %rdi)
IK(	addq   %gs:0, %rdi                                /* %rdi = &%gs:this_exception_args */)
IU(	leaq   OFFSET_EXCEPTION_INFO_POINTERS(%rax), %rdi /* %rdi = &libc_error_info()->ei_pointers */)
	leaq   (%rdi, %rsi, 8), %rdi
	movq   $(EXCEPTION_DATA_POINTERS), %rcx
	subq   %rsi, %rcx /* RCX = EXCEPTION_DATA_POINTERS - RSI */
IU(	pushq_cfi %rax)
	xorq   %rax, %rax
	rep    stosq
IU(	popq_cfi  %rax)
	jmp    .Ldo_unwind_rsp_maybe_fill_trace
#ifndef NDEBUG
	.cfi_restore_state
.Llibc_error_thrown_inside_catch:
	/* Pass arguments */
	/* ATTR_NORETURN void error_thrown(error_code_t code, unsigned int argc, ...) */
	pushq_cfi %r9
	pushq_cfi %r8
	pushq_cfi %rcx
	pushq_cfi %rdx

	movq   %rsi, %rdx  /* size_t argc */
	movq   %rdi, %rsi  /* error_code_t code */
	leaq   (4*8)(%rsp), %rdi /* error_register_state_t const *state */
	leaq   -OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_RDX(%rsp), %rax
	pushq_cfi %rax     /* vl_reg_save_area */
	pushq_cfi (OFFSET_KCPUSTATE64_GPREGS + OFFSET_GPREGS64_RSP)(%rdi) /* vl_overflow_arg_area (== state->kcs_gpregs.gp_rsp) */
	pushq_cfi $(5 * 8) /* vl_gp_offset */
	movq   %rsp, %rcx  /* va_list args */

	EXTERN(libc_except_badusage_throw_inside_catch)
	call   libc_except_badusage_throw_inside_catch
	nop    /* For unwinding */
#endif /* !NDEBUG */
	.cfi_endproc
END(libc_error_thrown)



.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(error_throw, libc_error_throw)
INTERN_FUNCTION(libc_error_throw)
	.cfi_startproc
	/* ATTR_NORETURN void FCALL error_throw(error_code_t code) */

IU(	.cfi_remember_state)
IU(	ASM_PUSH_KCPUSTATE_AFTER_RIP)
IU(	INTERN(libc_error_info))
IU(	call   libc_error_info)
IU(	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RDI)(%rsp), %rdi)
#ifndef NDEBUG
IK(	.cfi_remember_state)
	cmpq   $(ERROR_CODEOF(E_OK)), FIELD_ERROR_CODE
	jne    .Llibc_error_throw_inside_catch /* ERROR: Call to `THROW()' inside of `catch' */
#endif /* !NDEBUG */
	movq   %rdi, FIELD_ERROR_CODE
#if EXCEPTION_DATA_POINTERS != 0
	.Lindex = 0
	.rept EXCEPTION_DATA_POINTERS
	movq   $(0), FIELD_ERROR_POINTERS(.Lindex)
	.Lindex = .Lindex + 8
	.endr
#endif /* EXCEPTION_DATA_POINTERS != 0 */
IU(	jmp    1f)
IU(	.cfi_restore_state)
DEFINE_PUBLIC_ALIAS(error_throw_current, libc_error_throw_current)
INTERN_FUNCTION(libc_error_throw_current)
	/* ATTR_NORETURN void error_throw_current(void) */
	ASM_PUSH_KCPUSTATE_AFTER_RIP
IU(	INTERN(libc_error_info))
IU(	call   libc_error_info)
IU(1:)
	/* Fill in the per-task exception context. */
IK(	movq   %rax, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RAX))
IK(	movq   %rcx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RCX))
IK(	movq   %rdx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RDX))
	/* The call to `libc_error_info()' (may) have clobbered rax, rcx, rdx
	 * So  instead,  we  must  copy  these  registers  from  the   stack. */
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
	.rept EXCEPT_BACKTRACE_SIZE-1
	movq   $(0), FIELD_ERROR_TRACE(.Lindex)
	.Lindex = .Lindex + 8
	.endr
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	goto_Ldo_unwind_rsp
#ifndef NDEBUG
IK(	.cfi_restore_state)
.Llibc_error_throw_inside_catch:
IK(	ASM_PUSH_KCPUSTATE_AFTER_RIP)
	/* Pass arguments */
	movq   %rdi, %rsi  /* error_code_t code */
	movq   %rsp, %rdi  /* error_register_state_t const *state */
	xorq   %rdx, %rdx  /* size_t argc */
	pushq_cfi %rsp     /* vl_reg_save_area (must be a readable pointer, but doesn't matter) */
	pushq_cfi %rsp     /* vl_overflow_arg_area (must be a readable pointer, but doesn't matter) */
	pushq_cfi $(6 * 8) /* vl_gp_offset */
	movq   %rsp, %rcx  /* va_list args */
	EXTERN(libc_except_badusage_throw_inside_catch)
	call   libc_except_badusage_throw_inside_catch
	nop    /* For unwinding */
#endif /* !NDEBUG */
END(libc_error_throw_current)
	.cfi_endproc
END(libc_error_throw)






#ifdef __KERNEL__
#include <kernel/compiler.h>
#ifndef CONFIG_USE_NEW_RPC


.section .text
PUBLIC_FUNCTION(x86_userexcept_unwind_interrupt)
#ifndef NDEBUG
	.cfi_startproc
	/* Assert that an exception is actually set!
	 * This is once again checked by `libc_error_unwind()', but by first checking it
	 * here,  we've still go the correct return  address for where the problem lies. */
	cmpq   $(E_OK), %gs:this_exception_code
	jne    1f
	int3   /* Assertion failed! */
1:	.cfi_endproc
#endif /* !NDEBUG */
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %rdi, 0
	ASM_CFI_OFFSET_RESTORE_ICPUSTATE(0)
	movq   %rdi, %rsp
	.cfi_def_cfa_register %rsp
PUBLIC_FUNCTION(x86_userexcept_unwind_interrupt_rsp)
	/* Check if the interrupt state points into user-space. */
	ttest  mask=3, loc=(OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_CS)(%rsp)
	EXTERN(x86_serve_user_rpc_and_propagate_exceptions)
	jnz    x86_serve_user_rpc_and_propagate_exceptions

#if 0 /* Not required, since icpustate64 (excluding the iret tail portion) doesn't
       * contain  any  registers   that  can't  also   be  found  in   kcpustate64 */
	/* Another special case: If the  interrupt state  was re-directed,  then we  must
	 *                       load it immediately (and have `x86_rpc_user_redirection'
	 *                       take care of propagating the exception), since it  still
	 *                       actually points into user-space.
	 * This is necessrary because otherwise we'd not be restoring the original user-space
	 * register that aren't  also found in  `struct kcpustate' (because the  kernel-space
	 * variant uses `.Ldo_unwind_rsp', which work with that cpu state variant) */
	cmpq   $(x86_rpc_user_redirection), OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_RIP(%rsp)
	EXTERN(cpu_apply_icpustate_rsp)
	je     cpu_apply_icpustate_rsp
#endif

	/* The interrupt points into kernel-space (or possibly towards
	 * `x86_rpc_user_redirection', which  is  also  kernel-space). */
	.cfi_same_value %cs
	.cfi_same_value %ss

PUBLIC_FUNCTION(x86_userexcept_unwind_interrupt_kernel_rsp)

	/* NOTE: RPC guaranties never to modify a kernel-target iret tail, meaning
	 *       we're  entirely safe to  modify the tail  without having to worry
	 *       about intervention of RPC callbacks! */
#if EXCEPT_BACKTRACE_SIZE != 0
	.Lindex = 0
	.rept EXCEPT_BACKTRACE_SIZE-1
	movq   $(0), %gs:this_exception_trace + .Lindex
	.Lindex = .Lindex + 8
	.endr
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */

	/* Turn the icpustate into a kcpustate and set it as exception origin */
#define COPYSTATE(reg, src, dst)                  \
	movq   src(%rsp), %rax;                       \
	movq   %rax, %gs:this_exception_state + dst; \
.if src != dst;                                   \
	.cfi_rel_offset reg, dst;                     \
	movq   %rax, dst(%rsp);                       \
.endif
	/* Start by handling the simple registers (aka: Those that share memory locations) */
	COPYSTATE(%r15, OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R15, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R15)
	COPYSTATE(%r14, OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R14, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R14)
	COPYSTATE(%r13, OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R13, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R13)
	COPYSTATE(%r12, OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R12, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R12)
	COPYSTATE(%r11, OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R11, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R11)
	COPYSTATE(%r10, OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R10, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R10)
	COPYSTATE(%r9,  OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R9,  OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R9)
	COPYSTATE(%r8,  OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R8,  OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R8)
	COPYSTATE(%rdi, OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RDI, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RDI)
	COPYSTATE(%rsi, OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RSI, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RSI)
	COPYSTATE(%rbp, OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RBP, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RBP)
#if OFFSET_KCPUSTATE_RFLAGS != OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_CS
#error "This code assumes that kcpustate:%rflags shares its offset with icpustate:%cs"
#endif /* OFFSET_KCPUSTATE_RFLAGS != OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_CS */
	COPYSTATE(%rflags, OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_RFLAGS, OFFSET_KCPUSTATE_RFLAGS)
#if OFFSET_KCPUSTATE_RIP != OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_RFLAGS
#error "This code assumes that kcpustate:%rip shares its offset with icpustate:%rflags"
#endif /* OFFSET_KCPUSTATE_RIP != OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_RFLAGS */
	COPYSTATE(%rip, OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_RIP, OFFSET_KCPUSTATE_RIP)
	/* Copy unaligned  GP  registers  from  the  back  to  the  first,  thus  not
	 * overwriting anything in regards to the gap that has to be created for %rsp */
	COPYSTATE(%rax, OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RAX, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RAX)
	COPYSTATE(%rcx, OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RCX, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RCX)
	COPYSTATE(%rdx, OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RDX, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RDX)
	COPYSTATE(%rbx, OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RBX, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RBX)
	/* Finally, copy %rsp from the irregs portion of the cpu state. */
	COPYSTATE(%rsp, OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_RSP, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RSP)
#undef COPYSTATE

	goto_Ldo_unwind_rsp
	.cfi_endproc
END(x86_userexcept_unwind_interrupt_kernel_rsp)
END(x86_userexcept_unwind_interrupt_rsp)
END(x86_userexcept_unwind_interrupt)

#endif /* !CONFIG_USE_NEW_RPC */
#endif /* __KERNEL__ */

#endif /* !GUARD_LIBC_HYBRID_ARCH_I386_EXCEPT64_S */
