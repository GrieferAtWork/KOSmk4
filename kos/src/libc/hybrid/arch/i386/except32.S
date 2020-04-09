/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_HYBRID_ARCH_I386_EXCEPT32_S
#define GUARD_LIBC_HYBRID_ARCH_I386_EXCEPT32_S 1
#define _KOS_KERNEL_SOURCE 1

#include <hybrid/compiler.h>
#include <asm/cfi.h>
#include <kos/except.h>
#include <kos/kernel/cpu-state.h>
#include <asm/cpu-flags.h>

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
EXTERN(this_exception_pointers)
EXTERN(this_exception_faultaddr)
EXTERN(this_exception_state)

#define FIELD_ERROR_CODE           %fs:this_exception_code
#define FIELD_ERROR_FLAGS          %fs:this_exception_flags
#define FIELD_ERROR_TRACE(off)     %fs:this_exception_trace + (off)
#define FIELD_ERROR_POINTERS(off)  %fs:this_exception_pointers + (off)
#define FIELD_ERROR_FAULTADDR      %fs:this_exception_faultaddr
#define FIELD_ERROR_REGISTERS(off) %fs:this_exception_state + (off)
#define S_EXCEPT_TEXT(name)    .text
#define S_EXCEPT_DATA(name)    .data
#define S_EXCEPT_RODATA(name)  .rodata
#define S_EXCEPT_STRING(name)  .rodata
#else /* __KERNEL__ */
#define FIELD_ERROR_CODE            OFFSET_EXCEPTION_INFO_CODE(%eax)
#define FIELD_ERROR_FLAGS           OFFSET_EXCEPTION_INFO_FLAGS(%eax)
#define FIELD_ERROR_POINTERS(off)  (OFFSET_EXCEPTION_INFO_POINTERS + (off))(%eax)
#define FIELD_ERROR_FAULTADDR      (OFFSET_EXCEPTION_INFO_DATA + __OFFSET_EXCEPTION_DATA_FAULTADDR)(%eax)
#define FIELD_ERROR_TRACE(off)     (OFFSET_EXCEPTION_INFO_TRACE + (off))(%eax)
#define FIELD_ERROR_REGISTERS(off) (OFFSET_EXCEPTION_INFO_STATE + (off))(%eax)
#define S_EXCEPT_TEXT(name)    .text.crt.except.name
#define S_EXCEPT_DATA(name)    .data.crt.except.name
#define S_EXCEPT_RODATA(name)  .rodata.crt.except.name
#define S_EXCEPT_STRING(name)  .rodata.crt.except.name
#endif /* !__KERNEL__ */

#ifdef __KERNEL__
#define IK(...) __VA_ARGS__
#define IU(...) /* nothing */
#else /* __KERNEL__ */
#define IK(...) /* nothing */
#define IU(...) __VA_ARGS__
#endif /* !__KERNEL__ */



.section S_EXCEPT_TEXT(error_rethrow)
DEFINE_PUBLIC_ALIAS(error_rethrow, libc_error_rethrow)
INTERN_FUNCTION(libc_error_rethrow)
	/* ATTR_NORETURN void error_rethrow(void) */
	.cfi_startproc
	.cfi_signal_frame
	pushfl_cfi_r
	pushal_cfi_r
	addl   $((SIZEOF_KCPUSTATE - OFFSET_KCPUSTATE_GPREGS) - OFFSET_KCPUSTATE_EFLAGS), \
	          OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP(%esp)
	.cfi_rel_offset %esp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP
IU(	INTERN(libc_error_info))
IU(	call   libc_error_info)
	orl    $(EXCEPT_FRETHROW), FIELD_ERROR_FLAGS
.Ldo_unwind_esp:
	movl   %esp, %ecx
	INTERN(libc_error_unwind)
	call   libc_error_unwind
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
	/* Push registers that we're going to restore later!
	 * This must be done before we write to the target ESP in case
	 * that target ESP overlaps with the kcpustate structure (in which
	 * case we'll be overwriting the kcpustate during the stack setup,
	 * meaning that any read from the structure has to happen before then) */
	pushl  OFFSET_KCPUSTATE_EFLAGS(%eax)
	pushl  OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX(%eax)
	pushl  OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX(%eax)
	/* Push %ecx and the return address onto the target stack */
	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP(%eax), %ecx
	subl   $(8), %ecx
	/* NOTE: Push EIP first, since that one is stored closer to the bottom
	 *       of the kcpustate structure, meaning it would get overwritten
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
#if 1
.section .text
PUBLIC_FUNCTION(_Unwind_Resume)
	.cfi_startproc
	.cfi_signal_frame
	pushfl_cfi_r
	pushal_cfi_r
	addl   $((SIZEOF_KCPUSTATE - OFFSET_KCPUSTATE_GPREGS) - OFFSET_KCPUSTATE_EFLAGS), \
	          OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP(%esp)
/*	.cfi_rel_offset %esp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP */
	jmp    .Ldo_unwind_esp
	.cfi_endproc
END(_Unwind_Resume)
#else
DEFINE_PUBLIC_ALIAS(_Unwind_Resume, error_rethrow)
#endif

#else /* __KERNEL__ */

.section S_EXCEPT_TEXT(_Unwind_RaiseException)
INTERN_FUNCTION(libc_Unwind_RaiseException)
	.cfi_startproc
	.cfi_signal_frame
	pushfl_cfi_r
	pushal_cfi_r
	addl   $((SIZEOF_KCPUSTATE - OFFSET_KCPUSTATE_GPREGS) - OFFSET_KCPUSTATE_EFLAGS), \
	          OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP(%esp)
/*	.cfi_rel_offset %esp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP */
	movl   %esp, %ecx /* error_register_state_t *__restrict state */
	movl   SIZEOF_KCPUSTATE(%esp), %edx /* struct _Unwind_Exception *__restrict exception_object */
	INTERN(libc_Unwind_RaiseException_impl)
	call   libc_Unwind_RaiseException_impl
	jmp    .Lload_kcpustate_eax
	.cfi_endproc
END(libc_Unwind_RaiseException)
DEFINE_PUBLIC_ALIAS(_Unwind_RaiseException, libc_Unwind_RaiseException)


.section S_EXCEPT_TEXT(_Unwind_Resume)
INTERN_FUNCTION(libc_Unwind_Resume)
	.cfi_startproc
	.cfi_signal_frame
	pushfl_cfi_r
	pushal_cfi_r
	addl   $((SIZEOF_KCPUSTATE - OFFSET_KCPUSTATE_GPREGS) - OFFSET_KCPUSTATE_EFLAGS), \
	          OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP(%esp)
/*	.cfi_rel_offset %esp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP */
	movl   %esp, %ecx /* error_register_state_t *__restrict state */
	movl   SIZEOF_KCPUSTATE(%esp), %edx /* struct _Unwind_Exception *__restrict exception_object */
	INTERN(libc_Unwind_Resume_impl)
	call   libc_Unwind_Resume_impl
	jmp    .Lload_kcpustate_eax
	.cfi_endproc
END(libc_Unwind_Resume)
DEFINE_PUBLIC_ALIAS(_Unwind_Resume, libc_Unwind_Resume)


.section S_EXCEPT_TEXT(_Unwind_Resume_or_Rethrow)
INTERN_FUNCTION(libc_Unwind_Resume_or_Rethrow)
	.cfi_startproc
	.cfi_signal_frame
	pushfl_cfi_r
	pushal_cfi_r
	addl   $((SIZEOF_KCPUSTATE - OFFSET_KCPUSTATE_GPREGS) - OFFSET_KCPUSTATE_EFLAGS), \
	          OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP(%esp)
/*	.cfi_rel_offset %esp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP */
	movl   %esp, %ecx /* error_register_state_t *__restrict state */
	movl   SIZEOF_KCPUSTATE(%esp), %edx /* struct _Unwind_Exception *__restrict exception_object */
	INTERN(libc_Unwind_Resume_or_Rethrow_impl)
	call   libc_Unwind_Resume_or_Rethrow_impl
	jmp    .Lload_kcpustate_eax
	.cfi_endproc
END(libc_Unwind_Resume_or_Rethrow)
DEFINE_PUBLIC_ALIAS(_Unwind_Resume_or_Rethrow, libc_Unwind_Resume_or_Rethrow)


.section S_EXCEPT_TEXT(_Unwind_ForcedUnwind)
INTERN_FUNCTION(libc_Unwind_ForcedUnwind)
	.cfi_startproc
	.cfi_signal_frame
	pushfl_cfi_r
	pushal_cfi_r
	addl   $((SIZEOF_KCPUSTATE - OFFSET_KCPUSTATE_GPREGS) - OFFSET_KCPUSTATE_EFLAGS), \
	          OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP(%esp)
/*	.cfi_rel_offset %esp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP */
	movl   %esp, %ecx /* error_register_state_t *__restrict state */
	movl   SIZEOF_KCPUSTATE(%esp), %edx /* struct _Unwind_Exception *__restrict exception_object */
	pushl_cfi (SIZEOF_KCPUSTATE + 12)(%esp)   /* void *stop_arg */
	pushl_cfi (SIZEOF_KCPUSTATE + 12)(%esp)   /* _Unwind_Stop_Fn stop */
	INTERN(libc_Unwind_ForcedUnwind_impl)
	call   libc_Unwind_ForcedUnwind_impl
	.cfi_adjust_cfa_offset -8
	jmp    .Lload_kcpustate_eax
	.cfi_endproc
END(libc_Unwind_ForcedUnwind)
DEFINE_PUBLIC_ALIAS(_Unwind_ForcedUnwind, libc_Unwind_ForcedUnwind)


.section S_EXCEPT_TEXT(_Unwind_Backtrace)
INTERN_FUNCTION(libc_Unwind_Backtrace)
	.cfi_startproc
	.cfi_signal_frame
	pushfl_cfi_r
	pushal_cfi_r
	addl   $((SIZEOF_KCPUSTATE - OFFSET_KCPUSTATE_GPREGS) - OFFSET_KCPUSTATE_EFLAGS), \
	          OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP(%esp)
/*	.cfi_rel_offset %esp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP */
	movl   %esp, %ecx /* error_register_state_t *__restrict state */
	movl   SIZEOF_KCPUSTATE(%esp), %edx /* _Unwind_Trace_Fn func */
	pushl_cfi (SIZEOF_KCPUSTATE + 12)(%esp)   /* void *arg */
	INTERN(libc_Unwind_Backtrace_impl)
	call   libc_Unwind_Backtrace_impl
	.cfi_adjust_cfa_offset -4
	addl   $(SIZEOF_KCPUSTATE - 4), %esp /* -4: EIP */
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


.section S_EXCEPT_TEXT(except_handler3)
INTERN_FUNCTION(libc_except_handler3)
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %ecx, SIZEOF_KCPUSTATE
	CFI_REL_OFFSET_KCPUSTATE_DEFS(0)
	movl   %ecx, %ebp /* Preserve `error_register_state_t *__restrict state' for unwinding. */
	.cfi_def_cfa_register %ebp
	INTERN(libc_except_handler3_impl)
	call   libc_except_handler3_impl
	jmp    .Lload_kcpustate_eax
	.cfi_endproc
END(libc_except_handler3)
DEFINE_PUBLIC_ALIAS(except_handler3, libc_except_handler3)

.section S_EXCEPT_TEXT(except_handler4)
INTERN_FUNCTION(libc_except_handler4)
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %ecx, SIZEOF_KCPUSTATE
	CFI_REL_OFFSET_KCPUSTATE_DEFS(0)
	movl   %ecx, %ebp /* Preserve `error_register_state_t *__restrict state' for unwinding. */
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



.section S_EXCEPT_TEXT(error_thrown)
DEFINE_PUBLIC_ALIAS(error_thrown, libc_error_thrown)
INTERN_FUNCTION(libc_error_thrown)
	/* ATTR_NORETURN void error_thrown(error_code_t code, unsigned int argc, ...) */
	.cfi_startproc
	pushfl_cfi_r
	pushal_cfi_r
IU(	INTERN(libc_error_info))
IU(	call   libc_error_info)
/*	.cfi_rel_offset %esp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP */
	/* Fill in the per-task exception context. */
IK(	movl   %eax, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX))
IK(	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX))
IK(	movl   %edx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX))
	/* The call to `libc_error_info()' (may) have clobbered eax, ecx, edx
	 * So instead, we must copy these registers from the stack. */
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
	movl   %ecx, FIELD_ERROR_FAULTADDR
	/* Copy exception information. */
	movl   $(EXCEPT_FNORMAL), FIELD_ERROR_FLAGS
	leal   SIZEOF_KCPUSTATE(%esp), %esi /* %esi = &code */
IK(	movl   $(this_exception_code), %edi)
IK(	addl   %fs:0, %edi                            /* %edi = &%fs:this_exception_code */)
IU(	leal   OFFSET_EXCEPTION_INFO_CODE(%eax), %edi /* %edi = &libc_error_info()->ei_code */)
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
	shrl   $(2), %eax  /* EAX = (P - this_exception_pointers) / 4 */
	movl   $EXCEPTION_DATA_POINTERS, %ecx
	subl   %eax, %ecx  /* ECX = EXCEPTION_DATA_POINTERS - EAX; (Number of unset pointers) */
	xorl   %eax, %eax
	rep    stosl       /* Set all unset pointers to NULL */
#if EXCEPT_BACKTRACE_SIZE != 0
IU(	popl_cfi %eax)
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	jmp    .Ldo_unwind_rsp_maybe_fill_trace
	.cfi_endproc
END(libc_error_thrown)



.section S_EXCEPT_TEXT(error_throw)
DEFINE_PUBLIC_ALIAS(error_throw, libc_error_throw)
INTERN_FUNCTION(libc_error_throw)
	.cfi_startproc
	/* ATTR_NORETURN void FCALL error_throw(error_code_t code) */
IU(	.cfi_remember_state)
IU(	pushfl_cfi_r)
IU(	pushal_cfi_r)
IU(	INTERN(libc_error_info))
IU(	call   libc_error_info)
IU(	movl   OFFSET_GPREGS_ECX(%esp), %ecx) /* Reload %ecx, which may have been clobbered by `libc_error_info()' */
	movl   %ecx, FIELD_ERROR_CODE
#if EXCEPTION_DATA_POINTERS != 0
	.Lindex = 0
	.rept EXCEPTION_DATA_POINTERS
	movl   $(0), FIELD_ERROR_POINTERS(.Lindex)
	.Lindex = .Lindex + 4
	.endr
#endif /* EXCEPTION_DATA_POINTERS != 0 */
IU(	jmp    1f)
IU(	.cfi_restore_state)
DEFINE_PUBLIC_ALIAS(error_throw_current, libc_error_throw_current)
INTERN_FUNCTION(libc_error_throw_current)
	/* ATTR_NORETURN void error_throw_current(void) */
	pushfl_cfi_r
	pushal_cfi_r
IU(	INTERN(libc_error_info))
IU(	call   libc_error_info)
IU(1:)
	/* Fill in the per-task exception context. */
IK(	movl   %eax, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX))
IK(	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX))
IK(	movl   %edx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX))
	/* The call to `libc_error_info()' (may) have clobbered eax, ecx, edx
	 * So instead, we must copy these registers from the stack. */
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
	movl   $(EXCEPT_FNORMAL), FIELD_ERROR_FLAGS
#if EXCEPT_BACKTRACE_SIZE != 0
.Ldo_fill_trace:
	.Lindex = 0
	.rept EXCEPT_BACKTRACE_SIZE-1
	movl   $(0), FIELD_ERROR_TRACE(.Lindex)
	.Lindex = .Lindex + 4
	.endr
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	jmp    .Ldo_unwind_esp
END(libc_error_throw_current)
	.cfi_endproc
END(libc_error_throw)






#ifdef __KERNEL__

/* ECX: <struct icpustate *> */
INTERN(x86_serve_user_rpc_and_propagate_exceptions)

.section .text
PUBLIC_FUNCTION(x86_userexcept_unwind_interrupt)
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %ecx, OFFSET_ICPUSTATE_IRREGS
	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss
	.cfi_rel_offset %edi, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDI
	.cfi_rel_offset %esi, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ESI
	.cfi_rel_offset %ebp, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBP
/*	.cfi_rel_offset %esp, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ESP */
	.cfi_rel_offset %ebx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBX
	.cfi_rel_offset %edx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDX
	.cfi_rel_offset %ecx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ECX
	.cfi_rel_offset %eax, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX
	.cfi_restore_iret_es_or_offset (OFFSET_ICPUSTATE_ES - OFFSET_ICPUSTATE_IRREGS)
	.cfi_restore_iret_ds_or_offset (OFFSET_ICPUSTATE_DS - OFFSET_ICPUSTATE_IRREGS)
	.cfi_restore_iret_fs_or_offset (OFFSET_ICPUSTATE_FS - OFFSET_ICPUSTATE_IRREGS)
	.cfi_restore_iret_gs
	movl   %ecx, %esp
	.cfi_def_cfa_register %esp
PUBLIC_FUNCTION(x86_userexcept_unwind_interrupt_esp)
	/* Check if the interrupt state points into user-space. */
	testl  $(3), OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_CS(%esp)
	jnz    x86_serve_user_rpc_and_propagate_exceptions
	testl  $(EFLAGS_VM), OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_EFLAGS(%esp)
	jnz    x86_serve_user_rpc_and_propagate_exceptions
	/* Another special case: If the interrupt state was re-directed, then we must
	 *                       load it immediatly (and have `x86_rpc_user_redirection'
	 *                       take care of propagating the exception), since it still
	 *                       actually points into user-space.
	 * This is necessrary because otherwise we'd not be restoring the original user-space
	 * register that aren't also found in `struct kcpustate' (because the kernel-space
	 * variant uses `.Ldo_unwind_esp', which work with that cpu state variant)
	 * These registers are:
	 *   - %fs: Would be 0 during `iret', since it used to contain SEGMENT_KERNEL_FSBASE,
	 *          which cannot be accessed by ring#3 code, causing the CPU to clear it as a
	 *          safely precaution.
	 *   - %ds: Would become `SEGMENT_USER_DATA32_RPL'
	 *   - %es: Would become `SEGMENT_USER_DATA32_RPL'
	 * NOTE: %gs wouldn't be clobbered since it is never used by the kernel. */
	cmpl   $(x86_rpc_user_redirection), OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_EIP(%esp)
	EXTERN(cpu_apply_icpustate_esp)
	je     cpu_apply_icpustate_esp
	.cfi_endproc


	/* The interrupt points into kernel-space (or possibly towards
	 * `x86_rpc_user_redirection', which is also kernel-space). */
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %esp, OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL
	.cfi_rel_offset %edi, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDI
	.cfi_rel_offset %esi, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ESI
	.cfi_rel_offset %ebp, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBP
/*	.cfi_rel_offset %esp, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ESP */
	.cfi_rel_offset %ebx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBX
	.cfi_rel_offset %edx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDX
	.cfi_rel_offset %ecx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ECX
	.cfi_rel_offset %eax, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX
	.cfi_rel_offset %eflags, OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_EFLAGS
	.cfi_rel_offset %eip, OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_EIP
/*	.cfi_rel_offset %cs, OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_CS */

PUBLIC_FUNCTION(x86_userexcept_unwind_interrupt_kernel_esp)
	/* NOTE: RPC guaranties never to modify a kernel-target iret tail, meaning
	 *       we're entirely safe to modify the tail without having to worry
	 *       about intervention of RPC callbacks! */
#if EXCEPT_BACKTRACE_SIZE != 0
	.Lindex = 0
	.rept EXCEPT_BACKTRACE_SIZE-1
	movl   $(0), %fs:this_exception_trace + .Lindex
	.Lindex = .Lindex + 4
	.endr
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */

	/* Turn the icpustate into a kcpustate and set it as exception origin */
#define COPYSTATE(reg, src, dst)                 \
	movl   src(%esp), %eax;                      \
	movl   %eax, %fs:this_exception_state + dst; \
.if src != dst;                                  \
	.cfi_rel_offset reg, dst;                    \
	movl   %eax, dst(%esp);                      \
.endif
	COPYSTATE(%eip, OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_EIP, OFFSET_KCPUSTATE_EIP)
	COPYSTATE(%eflags, OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_EFLAGS, OFFSET_KCPUSTATE_EFLAGS)
	COPYSTATE(%edi, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDI, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDI)
	COPYSTATE(%esi, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ESI, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESI)
	COPYSTATE(%ebp, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBP, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EBP)
	leal   OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL(%esp), %eax /* ESP */
	movl   %eax, %fs:this_exception_state + OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP
	movl   %eax, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP(%esp)
	COPYSTATE(%ebx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBX, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EBX)
	COPYSTATE(%edx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDX, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX)
	COPYSTATE(%ecx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ECX, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX)
	COPYSTATE(%eax, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX)
#undef COPYSTATE

	jmp    .Ldo_unwind_esp
	.cfi_endproc
END(x86_userexcept_unwind_interrupt_kernel_esp)
END(x86_userexcept_unwind_interrupt_esp)
END(x86_userexcept_unwind_interrupt)

#endif /* __KERNEL__ */

#endif /* !GUARD_LIBC_HYBRID_ARCH_I386_EXCEPT32_S */
