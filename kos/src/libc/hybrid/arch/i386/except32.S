/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
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
EXTERN(_this_exception_code)
EXTERN(_this_exception_state)
EXTERN(_this_exception_pointers)

#define FIELD_ERROR_CODE           %fs:_this_exception_code
#define FIELD_ERROR_FLAGS          %fs:_this_exception_flags
#define FIELD_ERROR_TRACE(off)     %fs:_this_exception_trace + (off)
#define FIELD_ERROR_POINTERS(off)  %fs:_this_exception_pointers + (off)
#define FIELD_ERROR_REGISTERS(off) %fs:_this_exception_state + (off)
#define S_EXCEPT_TEXT(name)    .text
#define S_EXCEPT_DATA(name)    .data
#define S_EXCEPT_RODATA(name)  .rodata
#define S_EXCEPT_STRING(name)  .rodata
#else /* __KERNEL__ */
#define FIELD_ERROR_CODE            OFFSET_EXCEPTION_INFO_CODE(%eax)
#define FIELD_ERROR_FLAGS           OFFSET_EXCEPTION_INFO_FLAGS(%eax)
#define FIELD_ERROR_POINTERS(off)  (OFFSET_EXCEPTION_INFO_POINTERS+(off))(%eax)
#define FIELD_ERROR_TRACE(off)     (OFFSET_EXCEPTION_INFO_TRACE+(off))(%eax)
#define FIELD_ERROR_REGISTERS(off) (OFFSET_EXCEPTION_INFO_STATE+(off))(%eax)
#define S_EXCEPT_TEXT(name)    .text.crt.except.name
#define S_EXCEPT_DATA(name)    .data.crt.except.name
#define S_EXCEPT_RODATA(name)  .rodata.crt.except.name
#define S_EXCEPT_STRING(name)  .rodata.crt.except.name
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
#ifndef __KERNEL__
	INTERN(libc_error_info)
	call   libc_error_info
#endif /* !__KERNEL__ */
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
	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP(%eax), %esp
	.cfi_same_value %esp
	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EBX(%eax), %ebx
	.cfi_same_value %ebx
	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX(%eax), %edx
	.cfi_same_value %edx
	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX(%eax), %ecx
	.cfi_same_value %ecx
	pushl  OFFSET_KCPUSTATE_EIP(%eax)
	.cfi_reg_value %esp, 4, %esp
	pushl  OFFSET_KCPUSTATE_EFLAGS(%eax)
	.cfi_reg_value %esp, 8, %esp
	.cfi_reg_offset %eip, 4, %esp
	.cfi_reg_offset %eflags, 0, %esp
	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX(%eax), %eax
	.cfi_def_cfa_register %esp
	.cfi_same_value %eax
	popfl
	.cfi_same_value %eflags
	.cfi_reg_value %esp, 4, %esp
	.cfi_reg_offset %eip, 0, %esp
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
	.cfi_rel_offset %esp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP
	movl   %esp, %ecx
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
	.cfi_rel_offset %esp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP
	movl   %esp, %ecx
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
	.cfi_rel_offset %esp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP
	movl   %esp, %ecx
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
	.cfi_rel_offset %esp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP
	movl   %esp, %ecx
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
	.cfi_rel_offset %esp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP
	movl   %esp, %ecx
	movl   SIZEOF_KCPUSTATE(%esp), %edx /* _Unwind_Trace_Fn func */
	pushl_cfi (SIZEOF_KCPUSTATE + 12)(%esp)   /* void *arg */
	INTERN(libc_Unwind_Backtrace_impl)
	call   libc_Unwind_Backtrace_impl
	.cfi_adjust_cfa_offset -4
	addl   $(SIZEOF_KCPUSTATE - 4), %esp /* -4: EIP */
	ret
	.cfi_endproc
END(libc_Unwind_Backtrace)
DEFINE_PUBLIC_ALIAS(_Unwind_Backtrace, libc_Unwind_Backtrace)


.section S_EXCEPT_TEXT(except_handler3)
INTERN_FUNCTION(libc_except_handler3)
	.cfi_startproc
	.cfi_signal_frame
	.cfi_def_cfa %ecx, SIZEOF_KCPUSTATE
	.cfi_rel_offset %edi, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDI
	.cfi_rel_offset %esi, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESI
	.cfi_rel_offset %ebp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EBP
	.cfi_rel_offset %esp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP
	.cfi_rel_offset %ebx, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EBX
	.cfi_rel_offset %edx, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX
	.cfi_rel_offset %ecx, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX
	.cfi_rel_offset %eax, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX
	.cfi_rel_offset %eflags, OFFSET_KCPUSTATE_EFLAGS
	.cfi_rel_offset %eip, OFFSET_KCPUSTATE_EIP
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
	.cfi_startproc
	.cfi_signal_frame
	.cfi_def_cfa %ecx, SIZEOF_KCPUSTATE
	.cfi_rel_offset %edi, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDI
	.cfi_rel_offset %esi, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESI
	.cfi_rel_offset %ebp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EBP
	.cfi_rel_offset %esp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP
	.cfi_rel_offset %ebx, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EBX
	.cfi_rel_offset %edx, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX
	.cfi_rel_offset %ecx, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX
	.cfi_rel_offset %eax, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX
	.cfi_rel_offset %eflags, OFFSET_KCPUSTATE_EFLAGS
	.cfi_rel_offset %eip, OFFSET_KCPUSTATE_EIP
	movl   %ecx, %ebp /* Preserve `error_register_state_t *__restrict state' for unwinding. */
	.cfi_def_cfa_register %ebp
	INTERN(libc_except_handler4_impl)
	call   libc_except_handler4_impl
	jmp    .Lload_kcpustate_eax
	.cfi_endproc
END(libc_except_handler4)
DEFINE_PUBLIC_ALIAS(except_handler4, libc_except_handler4)

#endif /* !__KERNEL__ */





.section S_EXCEPT_TEXT(error_thrown)
DEFINE_PUBLIC_ALIAS(error_thrown, libc_error_thrown)
INTERN_FUNCTION(libc_error_thrown)
	/* ATTR_NORETURN void error_thrown(error_code_t code, unsigned int argc, ...) */
	.cfi_startproc
	pushfl_cfi_r
	pushal_cfi_r
#ifndef __KERNEL__
	INTERN(libc_error_info)
	call   libc_error_info
#endif
/*	.cfi_rel_offset %esp, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP */
	/* Fill in the per-task exception context. */
#ifdef __KERNEL__
	movl   %eax, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX)
	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX)
	movl   %edx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX)
#else /* __KERNEL__ */
	/* The call to `libc_error_info()' (may) have clobbered eax, ecx, edx
	 * So instead, we must copy these registers from the stack. */
	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX(%esp), %ecx
	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX)
	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX(%esp), %ecx
	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX)
	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX(%esp), %ecx
	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX)
#endif /* !__KERNEL__ */
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
	/* Copy exception information. */
	movl   $(EXCEPT_FNORMAL), FIELD_ERROR_FLAGS
	leal   SIZEOF_KCPUSTATE(%esp), %esi /* %esi = &code */
#ifdef __KERNEL__
	movl   $(_this_exception_code), %edi
	addl   %fs:0, %edi  /* %edi = &%fs:_this_exception_code */
#else /* __KERNEL__ */
	leal   OFFSET_EXCEPTION_INFO_CODE(%eax), %edi /* %edi = &libc_error_info()->ei_code */
#if EXCEPT_BACKTRACE_SIZE != 0
	pushl_cfi %eax
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
#endif /* !__KERNEL__ */
	lodsl  /* %eax = code */
	stosl  /* %fs:_this_exception_code = code */
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
	shrl   $2,   %eax  /* EAX = (P - _this_exception_pointers) / 4 */
	movl   $EXCEPTION_DATA_POINTERS, %ecx
	subl   %eax, %ecx  /* ECX = EXCEPTION_DATA_POINTERS - EAX; (Number of unset pointers) */
	xorl   %eax, %eax
	rep    stosl       /* Set all unset pointers to NULL */
#if EXCEPT_BACKTRACE_SIZE != 0
#ifndef __KERNEL__
	popl_cfi %eax
#endif /* !__KERNEL__ */
	jmp    .Ldo_fill_trace
#else
	jmp    .Ldo_unwind_esp
#endif
	.cfi_endproc
END(libc_error_thrown)



.section S_EXCEPT_TEXT(error_throw)
DEFINE_PUBLIC_ALIAS(error_throw, libc_error_throw)
INTERN_FUNCTION(libc_error_throw)
	.cfi_startproc
	/* ATTR_NORETURN void FCALL error_throw(error_code_t code) */
#ifndef __KERNEL__
	.cfi_remember_state
	pushfl_cfi_r
	pushal_cfi_r
	INTERN(libc_error_info)
	call   libc_error_info
#endif /* !__KERNEL__ */
	movl   %ecx, FIELD_ERROR_CODE
#if EXCEPTION_DATA_POINTERS != 0
	.Lindex = 0
	.rept EXCEPTION_DATA_POINTERS
	movl   $0, FIELD_ERROR_POINTERS(.Lindex)
	.Lindex = .Lindex + 4
	.endr
#endif /* EXCEPTION_DATA_POINTERS != 0 */
#ifndef __KERNEL__
	jmp    1f
	.cfi_restore_state
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(error_throw_current, libc_error_throw_current)
INTERN_FUNCTION(libc_error_throw_current)
	/* ATTR_NORETURN void error_throw_current(void) */
	pushfl_cfi_r
	pushal_cfi_r
#ifndef __KERNEL__
	INTERN(libc_error_info)
	call   libc_error_info
1:
#endif /* !__KERNEL__ */
	/* Fill in the per-task exception context. */
#ifdef __KERNEL__
	movl   %eax, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX)
	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX)
	movl   %edx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX)
#else /* __KERNEL__ */
	/* The call to `libc_error_info()' (may) have clobbered eax, ecx, edx
	 * So instead, we must copy these registers from the stack. */
	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX(%esp), %ecx
	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX)
	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX(%esp), %ecx
	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX)
	movl   OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX(%esp), %ecx
	movl   %ecx, FIELD_ERROR_REGISTERS(OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX)
#endif /* !__KERNEL__ */
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
	movl   $EXCEPT_FNORMAL, FIELD_ERROR_FLAGS
#if EXCEPT_BACKTRACE_SIZE != 0
.Ldo_fill_trace:
	.Lindex = 0
	.rept EXCEPT_BACKTRACE_SIZE-1
	movl   $0, FIELD_ERROR_TRACE(.Lindex)
	.Lindex = .Lindex + 4
	.endr
#endif
	jmp    .Ldo_unwind_esp
END(libc_error_throw_current)
	.cfi_endproc
END(libc_error_throw)






#ifdef __KERNEL__

/* ECX: <struct icpustate *> */
INTERN(x86_serve_user_rpc_and_propagate_exceptions)

.section .text
INTERN_FUNCTION(x86_unwind_interrupt)
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss
	.cfi_def_cfa %ecx, OFFSET_ICPUSTATE_IRREGS
	.cfi_rel_offset %edi, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDI
	.cfi_rel_offset %esi, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ESI
	.cfi_rel_offset %ebp, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBP
/*	.cfi_rel_offset %esp, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ESP */
	.cfi_rel_offset %ebx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBX
	.cfi_rel_offset %edx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDX
	.cfi_rel_offset %ecx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ECX
	.cfi_rel_offset %eax, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX
	.cfi_restore_iret_gs
	.cfi_restore_iret_fs_or_offset (OFFSET_ICPUSTATE_FS - OFFSET_ICPUSTATE_IRREGS)
	.cfi_restore_iret_es_or_offset (OFFSET_ICPUSTATE_ES - OFFSET_ICPUSTATE_IRREGS)
	.cfi_restore_iret_ds_or_offset (OFFSET_ICPUSTATE_DS - OFFSET_ICPUSTATE_IRREGS)
	movl   %ecx, %esp
	.cfi_def_cfa_register %esp
INTERN_FUNCTION(x86_unwind_interrupt_esp)
	/* Check if the interrupt state points into user-space. */
	testl  $3, OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_CS(%esp)
	jnz    x86_serve_user_rpc_and_propagate_exceptions
	testl  $EFLAGS_VM, OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_EFLAGS(%esp)
	jnz    x86_serve_user_rpc_and_propagate_exceptions
	.cfi_endproc


	/* The interrupt points into kernel-space (or possibly towards
	 * `x86_rpc_user_redirection', which is also kernel-space). */
	.cfi_startproc simple
	.cfi_def_cfa %esp, OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL
	.cfi_rel_offset %edi, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDI
	.cfi_rel_offset %esi, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ESI
	.cfi_rel_offset %ebp, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBP
	.cfi_rel_offset %esp, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ESP
	.cfi_rel_offset %ebx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBX
	.cfi_rel_offset %edx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDX
	.cfi_rel_offset %ecx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ECX
	.cfi_rel_offset %eax, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX
	.cfi_rel_offset %eflags, OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_EFLAGS
	.cfi_rel_offset %eip, OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_EIP
	.cfi_rel_offset %cs, OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_CS

INTERN_FUNCTION(x86_unwind_kernel_interrupt_esp)
	/* NOTE: RPC guaranties never to modify a kernel-target iret tail, meaning
	 *       we're entirely safe to modify the tail without having to worry
	 *       about intervention of RPC callbacks! */
#if EXCEPT_BACKTRACE_SIZE != 0
	.Lindex = 0
	.rept EXCEPT_BACKTRACE_SIZE-1
	movl   $0, %fs:_this_exception_trace + .Lindex
	.Lindex = .Lindex + 4
	.endr
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */

	/* Turn the icpustate into a kcpustate and set it as exception origin */
#define COPYSTATE(reg, src, dst)                  \
	movl   src(%esp), %eax;                       \
	movl   %eax, %fs:_this_exception_state + dst; \
.if src != dst;                                   \
	.cfi_rel_offset reg, dst;                     \
	movl   %eax, dst(%esp);                       \
.endif
	COPYSTATE(%eip, OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_EIP, OFFSET_KCPUSTATE_EIP)
	COPYSTATE(%eflags, OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_EFLAGS, OFFSET_KCPUSTATE_EFLAGS)
	COPYSTATE(%edi, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDI, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDI)
	COPYSTATE(%esi, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ESI, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESI)
	COPYSTATE(%ebp, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBP, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EBP)
	leal   OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL(%esp), %eax /* ESP */
	movl   %eax, %fs:_this_exception_state + OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP
	movl   %eax, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ESP(%esp) /* Fix ESP */
	COPYSTATE(%ebx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBX, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EBX)
	COPYSTATE(%edx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDX, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EDX)
	COPYSTATE(%ecx, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ECX, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_ECX)
	COPYSTATE(%eax, OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX, OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_EAX)
#undef COPYSTATE

	jmp    .Ldo_unwind_esp
	.cfi_endproc
END(x86_unwind_kernel_interrupt_esp)
END(x86_unwind_interrupt_esp)
END(x86_unwind_interrupt)

#endif /* __KERNEL__ */








