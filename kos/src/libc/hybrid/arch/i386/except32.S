/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_HYBRID_ARCH_I386_EXCEPT32_S
#define GUARD_LIBC_HYBRID_ARCH_I386_EXCEPT32_S 1
#define __ASSEMBLER__ 1
#define _KOS_KERNEL_SOURCE 1

#include <hybrid/compiler.h>

#include <cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/ttest.h>
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

#define FIELD_EXCEPT_CODE          %fs:this_exception_code
#define FIELD_ERROR_FLAGS          %fs:this_exception_flags
#define FIELD_ERROR_TRACE(off)     %fs:this_exception_trace + (off)
#define FIELD_ERROR_POINTERS(off)  %fs:this_exception_args + (off)
#define FIELD_ERROR_FAULTADDR      %fs:this_exception_faultaddr
#define FIELD_ERROR_REGISTERS(off) %fs:this_exception_state + (off)
#define SECTION_EXCEPT_TEXT        .text
#else /* __KERNEL__ */
#define FIELD_EXCEPT_CODE          OFFSET_EXCEPTION_INFO_CODE(%eax)
#define FIELD_ERROR_FLAGS          OFFSET_EXCEPTION_INFO_FLAGS(%eax)
#define FIELD_ERROR_POINTERS(off)  (OFFSET_EXCEPTION_INFO_POINTERS + (off))(%eax)
#define FIELD_ERROR_FAULTADDR      (OFFSET_EXCEPTION_INFO_DATA + __OFFSET_EXCEPTION_DATA_FAULTADDR)(%eax)
#define FIELD_ERROR_TRACE(off)     (OFFSET_EXCEPTION_INFO_TRACE + (off))(%eax)
#define FIELD_ERROR_REGISTERS(off) (OFFSET_EXCEPTION_INFO_STATE + (off))(%eax)
#define SECTION_EXCEPT_TEXT        .text.crt.except
#endif /* !__KERNEL__ */

#ifdef __KERNEL__
#define IK(...) __VA_ARGS__
#define IU(...) /* nothing */
#else /* __KERNEL__ */
#define IK(...) /* nothing */
#define IU(...) __VA_ARGS__
#endif /* !__KERNEL__ */


#define PUSH_KCPUSTATE_ON_FUNCTION_ENTRY                                              \
	/* pushed by the caller: `0(%esp) == %eip' */                                     \
	pushfl_cfi_r;                                                                     \
	pushal_cfi_r;                                                                     \
	addl   $((SIZEOF_KCPUSTATE - OFFSET_KCPUSTATE_GPREGS) - OFFSET_KCPUSTATE_EFLAGS), \
	          OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP(%esp);                      \
/*	.cfi_rel_offset %esp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP */

#define PUSH_KCPUSTATE_ON_FUNCTION_ENTRY_WITH_CFI_FOR_ESP \
	PUSH_KCPUSTATE_ON_FUNCTION_ENTRY                      \
	.cfi_rel_offset %esp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP;



.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(except_rethrow, libc_except_rethrow)
INTERN_FUNCTION(libc_except_rethrow)
	/* ATTR_NORETURN void except_rethrow(void) */
	.cfi_startproc
	.cfi_signal_frame
	PUSH_KCPUSTATE_ON_FUNCTION_ENTRY_WITH_CFI_FOR_ESP
IU(	INTERN(libc_except_info))
IU(	call   libc_except_info)
#ifndef NDEBUG
	.cfi_remember_state
	cmpl   $(EXCEPT_CODEOF(E_OK)), FIELD_EXCEPT_CODE
	je     .Llibc_except_rethrow_outside_catch
#endif /* !NDEBUG */
	orb    $(EXCEPT_FRETHROW), FIELD_ERROR_FLAGS
.Ldo_unwind_esp:
	movl   %esp, %ecx
	INTERN(libc_except_unwind)
	call   libc_except_unwind
.Lload_kcpustate_eax:
	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDI(%eax), %edi
	.cfi_same_value %edi
	.cfi_def_cfa_register %eax
	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESI(%eax), %esi
	.cfi_same_value %esi
	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EBP(%eax), %ebp
	.cfi_same_value %ebp
	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EBX(%eax), %ebx
	.cfi_same_value %ebx
	/* Push    registers    that   we're    going   to    restore   later!
	 * This  must  be done  before  we write  to  the target  ESP  in case
	 * that  target ESP  overlaps with  the kcpustate  structure (in which
	 * case  we'll be  overwriting the  kcpustate during  the stack setup,
	 * meaning that any read from the structure has to happen before then) */
	pushl  OFFSET_KCPUSTATE_EFLAGS(%eax)
	pushl  OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX(%eax)
	pushl  OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX(%eax)
	/* Push %ecx and the return address onto the target stack */
	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP(%eax), %ecx
	subl   $(8), %ecx
	/* NOTE: Push EIP first, since that one is stored closer to the bottom
	 *       of the kcpustate structure, meaning it would get  overwritten
	 *       first! */
	movl   OFFSET_KCPUSTATE_EIP(%eax), %edx
	movl   %edx, 4(%ecx)
	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX(%eax), %edx
	movl   %edx, 0(%ecx)
	/* Restore pushed registers */
	popl   %edx
	.cfi_same_value %edx
	popl   %eax
	.cfi_same_value %eax
	popfl
	.cfi_same_value %eflags
	/* Load the target stack. */
	movl   %ecx, %esp
	.cfi_def_cfa %esp, 8
	.cfi_rel_offset %ecx, 0
	.cfi_rel_offset %eip, 4
	/* Restore %ecx and %eip. */
	popl_cfi_r %ecx
	ret
#ifndef NDEBUG
.Llibc_except_rethrow_outside_catch:
	.cfi_restore_state
	movl   %esp, %ecx
	EXTERN(libc_except_badusage_rethrow_outside_catch)
	call   libc_except_badusage_rethrow_outside_catch
#endif /* !NDEBUG */
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
	.cfi_signal_frame
	PUSH_KCPUSTATE_ON_FUNCTION_ENTRY
	jmp    .Ldo_unwind_esp
	.cfi_endproc
END(libc_Unwind_Resume)
DEFINE_PUBLIC_ALIAS(_Unwind_Resume, libc_Unwind_Resume)

#else /* __KERNEL__ */

.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_RaiseException)
	.cfi_startproc
	.cfi_signal_frame
	PUSH_KCPUSTATE_ON_FUNCTION_ENTRY
	movl   %esp, %ecx                       /* except_register_state_t *__restrict state */
	movl   SIZEOF_KCPUSTATE(%esp), %edx     /* struct _Unwind_Exception *__restrict exception_object */
	INTERN(libc_Unwind_RaiseException_impl)
	call   libc_Unwind_RaiseException_impl
	jmp    .Lload_kcpustate_eax
	.cfi_endproc
END(libc_Unwind_RaiseException)
DEFINE_PUBLIC_ALIAS(_Unwind_RaiseException, libc_Unwind_RaiseException)


.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_Resume)
	.cfi_startproc
	.cfi_signal_frame
	PUSH_KCPUSTATE_ON_FUNCTION_ENTRY
	movl   %esp, %ecx                       /* except_register_state_t *__restrict state */
	movl   SIZEOF_KCPUSTATE(%esp), %edx     /* struct _Unwind_Exception *__restrict exception_object */
	INTERN(libc_Unwind_Resume_impl)
	call   libc_Unwind_Resume_impl
	jmp    .Lload_kcpustate_eax
	.cfi_endproc
END(libc_Unwind_Resume)
DEFINE_PUBLIC_ALIAS(_Unwind_Resume, libc_Unwind_Resume)


.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_Resume_or_Rethrow)
	.cfi_startproc
	.cfi_signal_frame
	PUSH_KCPUSTATE_ON_FUNCTION_ENTRY
	movl   %esp, %ecx                       /* except_register_state_t *__restrict state */
	movl   SIZEOF_KCPUSTATE(%esp), %edx     /* struct _Unwind_Exception *__restrict exception_object */
	INTERN(libc_Unwind_Resume_or_Rethrow_impl)
	call   libc_Unwind_Resume_or_Rethrow_impl
	jmp    .Lload_kcpustate_eax
	.cfi_endproc
END(libc_Unwind_Resume_or_Rethrow)
DEFINE_PUBLIC_ALIAS(_Unwind_Resume_or_Rethrow, libc_Unwind_Resume_or_Rethrow)


.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_ForcedUnwind)
	.cfi_startproc
	.cfi_signal_frame
	PUSH_KCPUSTATE_ON_FUNCTION_ENTRY
	movl   %esp, %ecx                       /* except_register_state_t *__restrict state */
	movl   SIZEOF_KCPUSTATE(%esp), %edx     /* struct _Unwind_Exception *__restrict exception_object */
	pushl_cfi (SIZEOF_KCPUSTATE + 12)(%esp) /* void *stop_arg */
	pushl_cfi (SIZEOF_KCPUSTATE + 12)(%esp) /* _Unwind_Stop_Fn stop */
	INTERN(libc_Unwind_ForcedUnwind_impl)
	call   libc_Unwind_ForcedUnwind_impl
	.cfi_adjust_cfa_offset -8
	jmp    .Lload_kcpustate_eax
	.cfi_endproc
END(libc_Unwind_ForcedUnwind)
DEFINE_PUBLIC_ALIAS(_Unwind_ForcedUnwind, libc_Unwind_ForcedUnwind)


.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_Backtrace)
	.cfi_startproc
	.cfi_signal_frame
	PUSH_KCPUSTATE_ON_FUNCTION_ENTRY
	movl   %esp, %ecx                       /* except_register_state_t *__restrict state */
	movl   SIZEOF_KCPUSTATE(%esp), %edx     /* _Unwind_Trace_Fn func */
	pushl_cfi (SIZEOF_KCPUSTATE + 12)(%esp) /* void *arg */
	INTERN(libc_Unwind_Backtrace_impl)
	call   libc_Unwind_Backtrace_impl
	.cfi_adjust_cfa_offset -4
	addl   $(SIZEOF_KCPUSTATE - 4), %esp    /* -4: EIP */
	.cfi_adjust_cfa_offset -(SIZEOF_KCPUSTATE - 4)
	ret
	.cfi_endproc
END(libc_Unwind_Backtrace)
DEFINE_PUBLIC_ALIAS(_Unwind_Backtrace, libc_Unwind_Backtrace)


#define CFI_REL_OFFSET_KCPUSTATE_DEFS(offset)                                       \
	.cfi_rel_offset %edi, ((offset) + OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDI); \
	.cfi_rel_offset %esi, ((offset) + OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESI); \
	.cfi_rel_offset %ebp, ((offset) + OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EBP); \
	.cfi_rel_offset %esp, ((offset) + OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP); \
	.cfi_rel_offset %ebx, ((offset) + OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EBX); \
	.cfi_rel_offset %edx, ((offset) + OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX); \
	.cfi_rel_offset %ecx, ((offset) + OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX); \
	.cfi_rel_offset %eax, ((offset) + OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX); \
	.cfi_rel_offset %eflags, ((offset) + OFFSET_KCPUSTATE_EFLAGS);                  \
	.cfi_rel_offset %eip, ((offset) + OFFSET_KCPUSTATE_EIP);


.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_except_handler3)
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %ecx, SIZEOF_KCPUSTATE
	CFI_REL_OFFSET_KCPUSTATE_DEFS(0)
	movl   %ecx, %ebp /* Preserve `except_register_state_t *__restrict state' for unwinding. */
	.cfi_def_cfa_register %ebp
	INTERN(libc_except_handler3_impl)
	call   libc_except_handler3_impl
	jmp    .Lload_kcpustate_eax
	.cfi_endproc
END(libc_except_handler3)
DEFINE_PUBLIC_ALIAS(except_handler3, libc_except_handler3)

.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_except_handler4)
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %ecx, SIZEOF_KCPUSTATE
	CFI_REL_OFFSET_KCPUSTATE_DEFS(0)
	movl   %ecx, %ebp /* Preserve `except_register_state_t *__restrict state' for unwinding. */
	.cfi_def_cfa_register %ebp
	INTERN(libc_except_handler4_impl)
	call   libc_except_handler4_impl
	jmp    .Lload_kcpustate_eax
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
DEFINE_PUBLIC_ALIAS(except_thrown, libc_except_thrown)
INTERN_FUNCTION(libc_except_thrown)
	/* ATTR_NORETURN void except_thrown(except_code_t code, unsigned int argc, ...) */
	.cfi_startproc
	pushfl_cfi_r
IK(	cld) /* User-space may have set this one (must clear it because kernel is compiled with "-mcld") */
	pushal_cfi_r
IU(	INTERN(libc_except_info))
IU(	call   libc_except_info)
#ifndef NDEBUG
	.cfi_remember_state
	cmpl   $(EXCEPT_CODEOF(E_OK)), FIELD_EXCEPT_CODE
	jne    .Llibc_except_thrown_inside_catch /* ERROR: Call to `THROW()' inside of `catch' */
#endif /* !NDEBUG */
/*	.cfi_rel_offset %esp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP */
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
	movl   %ebp, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EBP)
	movl   %esi, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESI)
	movl   %edi, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDI)
	movl   OFFSET_KCPUSTATE_EFLAGS(%esp), %ecx
	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_EFLAGS)
	movl   OFFSET_KCPUSTATE_EIP(%esp), %ecx
	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_EIP)
	movl   %ecx, FIELD_ERROR_FAULTADDR
	/* Copy exception information. */
	movb   $(EXCEPT_FNORMAL), FIELD_ERROR_FLAGS
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
	jmp    .Ldo_unwind_rsp_maybe_fill_trace
#ifndef NDEBUG
	.cfi_restore_state
.Llibc_except_thrown_inside_catch:
	/* Fix %esp within `state' */
	addl   $((SIZEOF_KCPUSTATE - OFFSET_KCPUSTATE_GPREGS) - OFFSET_KCPUSTATE_EFLAGS), \
	          OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP(%esp)
	/* Pass arguments */
	leal   SIZEOF_KCPUSTATE(%esp), %esi /* %esi = &code */
	lodsl  /* %eax = code */
	movl   %esp, %ecx /* except_register_state_t const *state */
	movl   %eax, %edx /* except_code_t code */
	lodsl  /* %eax = argc, %edi == &[argv] */
	pushl_cfi %edi    /* va_list args */
	pushl_cfi %eax    /* size_t argc */
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
	jmp    .Ldo_unwind_esp
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
END(libc_except_throw_current)
	.cfi_endproc
END(libc_except_throw)


#ifndef __INTELLISENSE__
#undef FIELD_EXCEPT_CODE
#undef FIELD_ERROR_FLAGS
#undef FIELD_ERROR_TRACE
#undef FIELD_ERROR_POINTERS
#undef FIELD_ERROR_FAULTADDR
#undef FIELD_ERROR_REGISTERS
#undef SECTION_EXCEPT_TEXT
#include "except.S"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_LIBC_HYBRID_ARCH_I386_EXCEPT32_S */
