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
#ifndef GUARD_LIBC_HYBRID_ARCH_ARM_EXCEPT32_S
#define GUARD_LIBC_HYBRID_ARCH_ARM_EXCEPT32_S 1
#define __ASSEMBLER__ 1
#define _KOS_KERNEL_SOURCE 1

#include <hybrid/compiler.h>

#include <asm/arm.h>
#include <asm/cpu-flags.h>
#include <kos/bits/exception_data.h>
#include <kos/bits/exception_info.h>
#include <kos/except.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>

#include <cfi.h>

#ifdef __KERNEL__
#define SECTION_EXCEPT_TEXT ".text"
#else /* __KERNEL__ */
#define SECTION_EXCEPT_TEXT ".text.crt.except"
#endif /* !__KERNEL__ */

/* >> struct ucpustate { */
#define ucs_pc   OFFSET_UCPUSTATE_PC
#define ucs_lr   OFFSET_UCPUSTATE_LR
#define ucs_sp   OFFSET_UCPUSTATE_SP
#define ucs_cpsr OFFSET_UCPUSTATE_CPSR
#define ucs_r0   OFFSET_UCPUSTATE_R0
#define ucs_r1   OFFSET_UCPUSTATE_R1
#define ucs_r2   OFFSET_UCPUSTATE_R2
#define ucs_r3   OFFSET_UCPUSTATE_R3
#define ucs_r4   OFFSET_UCPUSTATE_R4
#define ucs_r5   OFFSET_UCPUSTATE_R5
#define ucs_r6   OFFSET_UCPUSTATE_R6
#define ucs_r7   OFFSET_UCPUSTATE_R7
#define ucs_r8   OFFSET_UCPUSTATE_R8
#define ucs_r9   OFFSET_UCPUSTATE_R9
#define ucs_r10  OFFSET_UCPUSTATE_R10
#define ucs_r11  OFFSET_UCPUSTATE_R11
#define ucs_r12  OFFSET_UCPUSTATE_R12
/* >> }; */

/* >> struct exception_data { */
#define e_code      __OFFSET_EXCEPTION_DATA_CODE
#define e_class     __OFFSET_EXCEPTION_DATA_CLASS
#define e_subclass  __OFFSET_EXCEPTION_DATA_SUBCLASS
#define e_args      __OFFSET_EXCEPTION_DATA_ARGS
#define e_pointer   __OFFSET_EXCEPTION_DATA_POINTER
#define e_faultaddr __OFFSET_EXCEPTION_DATA_FAULTADDR
/* >> }; */

/* >> struct exception_info { */
#define ei_state    OFFSET_EXCEPTION_INFO_STATE
#define ei_data     OFFSET_EXCEPTION_INFO_DATA
#define ei_code     OFFSET_EXCEPTION_INFO_CODE
#define ei_pointers OFFSET_EXCEPTION_INFO_POINTERS
#define ei_trace    OFFSET_EXCEPTION_INFO_TRACE
#define ei_flags    OFFSET_EXCEPTION_INFO_FLAGS
/* >> }; */



/* PUBLIC ATTR_NORETURN void except_rethrow(void); */
.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(except_rethrow, libc_except_rethrow)
INTERN_FUNCTION(libc_except_rethrow)
	.cfi_startproc
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R
	ASM_STACK_ALIGN_AFTER(SIZEOF_KCPUSTATE)

	EXTERN(libc_except_info)
	bl     libc_except_info /* r0 = &current.pt_except */

	/* Assert that an exception was actually thrown */
#ifndef NDEBUG
	.cfi_remember_state
	ldr    r12, [r0, #ei_code]
	cmp    r12, #EXCEPT_CODEOF(E_OK)
	beq    .Llibc_except_rethrow_outside_catch
#endif /* !NDEBUG */

	/* Set the `EXCEPT_FRETHROW' flag */
	ldrb   r12, [r0, #ei_flags]
	orr    r12, r12, #EXCEPT_FRETHROW
	strb   r12, [r0, #ei_flags]

.Ldo_unwind_sp:
	ASM_STACK_GET_BEFORE_ALIGN(r0, SIZEOF_KCPUSTATE)
	INTERN(libc_except_unwind)
	bl     libc_except_unwind
	nop /* For unwinding */

INTERN_FUNCTION(libc___arm_cpu_apply_kcpustate)
	.cfi_def_cfa r0, 0
	ASM_CFI_OFFSET_RESTORE_KCPUSTATE(0)
	ldr    lr, [r0, #OFFSET_KCPUSTATE_PC]   /* Load untyped %pc into %lr */
	ldr    r1, [r0, #OFFSET_KCPUSTATE_CPSR] /* Load %cpsr into %r1 */
	tst    r1, #CPSR_T
	orrne  lr, #1         /* Set THUMB bit */
	add    r0, r0, #OFFSET_KCPUSTATE_R1
	.cfi_adjust_cfa_offset -OFFSET_KCPUSTATE_R1
	msr    APSR_nzcvq, r1 /* Load APSR flags (ignoring flags from CPSR) */

/*[[[cfi{arch='arm', register='%cpsr'}
	# Encode how the THUMB bit should be restored
	push   %cpsr     # [%cpsr]
	push   %lr       # [%cpsr, %lr]
	and    $1        # [%cpsr, %lr & 1]
	jf     pop, 1f   # [%cpsr]
	or     $CPSR_T   # [%cpsr | CPSR_T]
1:]]]*/
	.cfi_escape 22,128,1,15,146,128,1,0,126,0,49,26,32,40,3,0
	.cfi_escape 9,32,33
/*[[[end]]]*/

/*[[[cfi{arch='arm', register='%pc'}
	# Encode how to restore 'pc'
	push   %lr       # [%lr]
	and    ~$1       # [%lr & ~1]
1:]]]*/
	.cfi_escape 22,15,5,126,0,9,254,26
/*[[[end]]]*/

	ldm    r0, {r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12} /* Restore GP registers */
	.cfi_restore r1; .cfi_restore r2; .cfi_restore r3; .cfi_restore r4;  .cfi_restore r5;  .cfi_restore r6
	.cfi_restore r7; .cfi_restore r8; .cfi_restore r9; .cfi_restore r10; .cfi_restore r11; .cfi_restore r12
	ldr    sp, [r0, #(OFFSET_KCPUSTATE_SP - OFFSET_KCPUSTATE_R1)] /* Restore stack */
	.cfi_restore sp
	ldr    r0, [r0, #(OFFSET_KCPUSTATE_R0 - OFFSET_KCPUSTATE_R1)] /* Restore r0 */
	bx     lr             /* Resume execution */
END(libc___arm_cpu_apply_kcpustate)
DEFINE_PUBLIC_ALIAS(__arm_cpu_apply_kcpustate, libc___arm_cpu_apply_kcpustate)
#ifndef NDEBUG
.Llibc_except_rethrow_outside_catch:
	.cfi_restore_state
	mov    r0, sp
	EXTERN(libc_except_badusage_rethrow_outside_catch)
	bl     libc_except_badusage_rethrow_outside_catch
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
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R
	ASM_STACK_ALIGN_AFTER(SIZEOF_KCPUSTATE)
	b      .Ldo_unwind_sp
	.cfi_endproc
END(libc_Unwind_Resume)
DEFINE_PUBLIC_ALIAS(_Unwind_Resume, libc_Unwind_Resume)

#else /* __KERNEL__ */

.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_RaiseException)
	.cfi_startproc
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R
	ASM_STACK_ALIGN_AFTER(SIZEOF_KCPUSTATE)
	mov    r1, r0               /* struct _Unwind_Exception *exception_object */
	ASM_STACK_GET_BEFORE_ALIGN(r0, SIZEOF_KCPUSTATE)      /* except_register_state_t *state */
	INTERN(libc_Unwind_RaiseException_impl)
	bl     libc_Unwind_RaiseException_impl
	b      libc___arm_cpu_apply_kcpustate
	.cfi_endproc
END(libc_Unwind_RaiseException)
DEFINE_PUBLIC_ALIAS(_Unwind_RaiseException, libc_Unwind_RaiseException)

.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_Resume)
	.cfi_startproc
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R
	ASM_STACK_ALIGN_AFTER(SIZEOF_KCPUSTATE)
	mov    r1, r0               /* struct _Unwind_Exception *exception_object */
	ASM_STACK_GET_BEFORE_ALIGN(r0, SIZEOF_KCPUSTATE)      /* except_register_state_t *state */
	INTERN(libc_Unwind_Resume_impl)
	bl     libc_Unwind_Resume_impl
	b      libc___arm_cpu_apply_kcpustate
	.cfi_endproc
END(libc_Unwind_Resume)
DEFINE_PUBLIC_ALIAS(_Unwind_Resume, libc_Unwind_Resume)


.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_Resume_or_Rethrow)
	.cfi_startproc
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R
	ASM_STACK_ALIGN_AFTER(SIZEOF_KCPUSTATE)
	mov    r1, r0               /* struct _Unwind_Exception *exception_object */
	ASM_STACK_GET_BEFORE_ALIGN(r0, SIZEOF_KCPUSTATE)      /* except_register_state_t *state */
	INTERN(libc_Unwind_Resume_or_Rethrow_impl)
	bl     libc_Unwind_Resume_or_Rethrow_impl
	b      libc___arm_cpu_apply_kcpustate
	.cfi_endproc
END(libc_Unwind_Resume_or_Rethrow)
DEFINE_PUBLIC_ALIAS(_Unwind_Resume_or_Rethrow, libc_Unwind_Resume_or_Rethrow)


.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_ForcedUnwind)
	.cfi_startproc
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R
	ASM_STACK_ALIGN_AFTER(SIZEOF_KCPUSTATE)
	/* TODO: Register shuffling here could be  simplified by adding an  arch-specific
	 *       override for the parameter order of `libc_Unwind_Resume_or_Rethrow_impl' */
	mov    r3, r2               /* void *stop_arg */
	mov    r2, r1               /* _Unwind_Stop_Fn stop */
	mov    r1, r0               /* struct _Unwind_Exception *exception_object */
	ASM_STACK_GET_BEFORE_ALIGN(r0, SIZEOF_KCPUSTATE)      /* except_register_state_t *state */
	INTERN(libc_Unwind_Resume_or_Rethrow_impl)
	bl     libc_Unwind_Resume_or_Rethrow_impl
	b      libc___arm_cpu_apply_kcpustate
	.cfi_endproc
END(libc_Unwind_ForcedUnwind)
DEFINE_PUBLIC_ALIAS(_Unwind_ForcedUnwind, libc_Unwind_ForcedUnwind)


.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_Unwind_Backtrace)
	.cfi_startproc
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R
	ASM_STACK_ALIGN_AFTER(SIZEOF_KCPUSTATE)
	/* TODO: Register shuffling here could be simplified by adding an arch-specific
	 *       override  for  the  parameter  order  of  `libc_Unwind_Backtrace_impl' */
	mov    r2, r1               /* void *arg */
	mov    r1, r0               /* _Unwind_Trace_Fn func */
	ASM_STACK_GET_BEFORE_ALIGN(r0, SIZEOF_KCPUSTATE)      /* except_register_state_t *state */
	INTERN(libc_Unwind_Backtrace_impl)
	bl     libc_Unwind_Backtrace_impl
	b      libc___arm_cpu_apply_kcpustate
	.cfi_endproc
END(libc_Unwind_Backtrace)
DEFINE_PUBLIC_ALIAS(_Unwind_Backtrace, libc_Unwind_Backtrace)


.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_except_handler3)
	.cfi_startproc simple
	.cfi_def_cfa r0, 0
	ASM_CFI_OFFSET_RESTORE_KCPUSTATE(0)
	mov    lr, r0 /* Preserve `except_register_state_t *state' for unwinding. */
	.cfi_def_cfa_register lr
	INTERN(libc_except_handler3_impl)
	bl     libc_except_handler3_impl
	b      libc___arm_cpu_apply_kcpustate
	.cfi_endproc
END(libc_except_handler3)
DEFINE_PUBLIC_ALIAS(except_handler3, libc_except_handler3)

.section SECTION_EXCEPT_TEXT
INTERN_FUNCTION(libc_except_handler4)
	.cfi_startproc simple
	.cfi_def_cfa r0, 0
	ASM_CFI_OFFSET_RESTORE_KCPUSTATE(0)
	mov    lr, r0 /* Preserve `except_register_state_t *state' for unwinding. */
	.cfi_def_cfa_register lr
	INTERN(libc_except_handler4_impl)
	bl     libc_except_handler4_impl
	b      libc___arm_cpu_apply_kcpustate
	.cfi_endproc
END(libc_except_handler4)
DEFINE_PUBLIC_ALIAS(except_handler4, libc_except_handler4)

#endif /* !__KERNEL__ */


#if EXCEPT_BACKTRACE_SIZE > 0
#define Ldo_unwind_sp_maybe_fill_trace_with_r0_on_faultaddr Ldo_fill_trace_with_r0_on_faultaddr
#else /* EXCEPT_BACKTRACE_SIZE > 0 */
#define Ldo_unwind_sp_maybe_fill_trace_with_r0_on_faultaddr Ldo_unwind_sp
#endif /* EXCEPT_BACKTRACE_SIZE < 0 */




/* PUBLIC ATTR_NORETURN void except_thrown(except_code_t code, unsigned int argc, ...); */
.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(except_thrown, libc_except_thrown)
INTERN_FUNCTION(libc_except_thrown)
	.cfi_startproc
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R /* `lvar_state' */
	ASM_STACK_ALIGN_AFTER(SIZEOF_KCPUSTATE)

	/* Load TLS context */
	INTERN(libc_except_info)
	bl     libc_except_info

#ifndef NDEBUG
	ldr    r12, [r0, #ei_code]
	cmp    r12, #EXCEPT_CODEOF(E_OK)
	bne    .Llibc_except_thrown_inside_catch /* ERROR: Call to `THROW()' inside of `catch' */
#endif /* !NDEBUG */

	/* Set exception flags */
	mov    r12, #EXCEPT_FNORMAL
	strb   r12, [r0, #ei_flags]

	/* Fill in the TLS exception register state. */
#if (ei_state + ucs_pc) != 0
#error "This is assumed for the `stm' below"
#endif /* (ei_state + ucs_pc) != 0 */
#if STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE)
	ASM_STACK_GET_BEFORE_ALIGN(lr, SIZEOF_KCPUSTATE)
	ldm    lr,  {r1,r2,r3,r12}             /* ucs_pc, ucs_lr, ucs_sp, ucs_cpsr */
#else /* STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE) */
	ldm    sp,  {r1,r2,r3,r12}             /* ucs_pc, ucs_lr, ucs_sp, ucs_cpsr */
#endif /* !STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE) */
	str    r1,  [r0, #ei_data+e_faultaddr] /* Also set `e_faultaddr' to `pc' */

	stm    r0!, {r1,r2,r3,r12} /* ucs_pc, ucs_lr, ucs_sp, ucs_cpsr */

	/* NOTE: At this point, `r0' points at `&libc_except_info()->ei_state.ucs_r0' */
	add    r12, sp, #(STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE) + 16) /* r12 = &lvar_state->ucs_r0 */
	ldm    r12!,{r1,r2,r3,lr}  /* ucs_r0, ucs_r1, ucs_r2, ucs_r3 */
	stm    r0!, {r1,r2,r3,lr}  /* ucs_r0, ucs_r1, ucs_r2, ucs_r3 */

	/* Register r4-r11 are marked callee-preserve and thus weren't clobbered
	 * by  our call to `libc_except_info()'. And since we didn't modify them
	 * either, we can just store them to the TLS register buffer as-is! */
	ldr    r12, [sp, #(STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE) + ucs_r12)] /* Restore r12 */
	stm    r0!, {r4,r5,r6,r7,r8,r9,r10,r11,r12} /* ucs_r4, ..., ucs_r12 */

	/* r0 now points to `&libc_except_info()->ei_data'
	 * Also note that from above, registers are still loaded as follows:
	 *  - r1 = lvar_state.ucs_r0 = {except_code_t code}
	 *  - r2 = lvar_state.ucs_r1 = {unsigned int argc}
	 *  - r3 = lvar_state.ucs_r2 = {<argv[0]>}
	 *  - lr = lvar_state.ucs_r3 = {<argv[1]>}
	 */

	/* Clear varargs registers if `argc' is too low */
	cmp    r2, #1 /* if (argc < 1) */
	movlo  r3, #0 /*     argv[0] = 0; */
	cmp    r2, #2 /* if (argc < 2) */
	movlo  lr, #0 /*     argv[1] = 0; */

	/* Also fill in `ei_code' and the first 2 exception registers */
	stm    r0!, {r1,r3,lr}  /* r1: {code}, r3: {<argv[0]>}, lr: {<argv[1]>} */

	/* At  this point, `r0' points at `&libc_except_info()->ei_data.e_args.e_pointers[2]'
	 * We now have to copy up to `EXCEPTION_DATA_POINTERS - 2 = 6' values from-stack, and
	 * write them back to `r0!' */
.LargI = 2
.rept EXCEPTION_DATA_POINTERS - 2
	mov    r3, #0                                       /* r3 = 0 */
	cmp    r2, #(.LargI + 1)                            /* if (argc >= I+1) */
	ldrhs  r3, [sp, #(STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE) + \
	                  SIZEOF_KCPUSTATE + (.LargI * 4))] /*     r3 = argv[I]; */
	stm    r0!, {r3}
	.LargI = .LargI + 1
.endr

	/* At this point, `r0' points at `&libc_except_info()->ei_data.e_faultaddr' */
	b      .Ldo_unwind_sp_maybe_fill_trace_with_r0_on_faultaddr
#ifndef NDEBUG
.Llibc_except_thrown_inside_catch:
	sub    sp, sp, #(EXCEPTION_DATA_POINTERS * 4)
	.cfi_adjust_cfa_offset (EXCEPTION_DATA_POINTERS * 4)

	/* Copy varargs to form a flat array at `[sp, #0]' */
	ldr    r2, [sp, #((EXCEPTION_DATA_POINTERS * 4) +        \
	                  STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE) + \
	                  OFFSET_KCPUSTATE_R1)]
.LargI = 0
.rept EXCEPTION_DATA_POINTERS
	mov    r3, #0                                        /* r3 = 0 */
	cmp    r2, #(.LargI + 1)                             /* if (argc >= I+1) */
.if .LargI < 2
	ldrhs  r3, [sp, #((EXCEPTION_DATA_POINTERS * 4) + STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE) + \
	                  OFFSET_KCPUSTATE_R2  + (.LargI * 4))]  /* r3 = argv[I]; */
.else
	ldrhs  r3, [sp, #((EXCEPTION_DATA_POINTERS * 4) + STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE) + \
	                  SIZEOF_KCPUSTATE + (.LargI * 4))]  /*     r3 = argv[I]; */
.endif
	str    r3, [sp, #(.LargI * 4)]
	.LargI = .LargI + 1
.endr

	/* Load arguments for `libc_except_badusage_throw_inside_catch' */
	mov    r3, sp                                                                                                  /* va_list args */
	ldr    r2, [sp, #((EXCEPTION_DATA_POINTERS * 4) + STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE) + OFFSET_KCPUSTATE_R1)] /* size_t argc */
	ldr    r1, [sp, #((EXCEPTION_DATA_POINTERS * 4) + STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE) + OFFSET_KCPUSTATE_R0)] /* except_code_t code */
	add    r0, sp, #((EXCEPTION_DATA_POINTERS * 4) + STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE))                         /* except_register_state_t const *state */

	EXTERN(libc_except_badusage_throw_inside_catch)
	bl     libc_except_badusage_throw_inside_catch
	nop    /* For unwinding */
#endif /* !NDEBUG */
	.cfi_endproc
END(libc_except_thrown)



/* PUBLIC ATTR_NORETURN void FCALL except_throw(except_code_t code); */
.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(except_throw, libc_except_throw)
INTERN_FUNCTION(libc_except_throw)
	.cfi_startproc
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R /* `lvar_state' */
	ASM_STACK_ALIGN_AFTER(SIZEOF_KCPUSTATE)

	/* Load TLS context */
	INTERN(libc_except_info)
	bl     libc_except_info

#ifndef NDEBUG
	ldr    r12, [r0, #ei_code]
	cmp    r12, #EXCEPT_CODEOF(E_OK)
	bne    .Llibc_except_throw_inside_catch /* ERROR: Call to `THROW()' inside of `catch' */
#endif /* !NDEBUG */

	/* Set exception flags */
	mov    r12, #EXCEPT_FNORMAL
	strb   r12, [r0, #ei_flags]

	/* Fill in the TLS exception register state. */
#if (ei_state + ucs_pc) != 0
#error "This is assumed for the `stm' below"
#endif /* (ei_state + ucs_pc) != 0 */
#if STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE)
	ASM_STACK_GET_BEFORE_ALIGN(lr, SIZEOF_KCPUSTATE)
	ldm    lr,  {r1,r2,r3,r12}             /* ucs_pc, ucs_lr, ucs_sp, ucs_cpsr */
#else /* STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE) */
	ldm    sp,  {r1,r2,r3,r12}             /* ucs_pc, ucs_lr, ucs_sp, ucs_cpsr */
#endif /* !STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE) */
	str    r1,  [r0, #ei_data+e_faultaddr] /* Also set `e_faultaddr' to `pc' */

	stm    r0!, {r1,r2,r3,r12} /* ucs_pc, ucs_lr, ucs_sp, ucs_cpsr */
	/* NOTE: At this point, `r0' points at `&libc_except_info()->ei_state.ucs_r0' */
	add    r12, sp, #(STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE) + 16) /* r12 = &lvar_state->ucs_r0 */
	ldm    r12!,{r1,r2,r3,lr}  /* ucs_r0, ucs_r1, ucs_r2, ucs_r3 */
	stm    r0!, {r1,r2,r3,lr}  /* ucs_r0, ucs_r1, ucs_r2, ucs_r3 */

	/* Register r4-r11 are marked callee-preserve and thus weren't clobbered
	 * by  our call to `libc_except_info()'. And since we didn't modify them
	 * either, we can just store them to the TLS register buffer as-is! */
	ldr    r12, [sp, #(STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE) + ucs_r12)] /* Restore r12 */
	stm    r0!, {r4,r5,r6,r7,r8,r9,r10,r11,r12} /* ucs_r4, ..., ucs_r12 */

	/* r0 now points to `&libc_except_info()->ei_data'
	 * Also note that from above, registers are still loaded as follows:
	 *  - r1 = lvar_state.ucs_r0 = {except_code_t code} */

	/* Fill in `ei_code' and the first exception register */
	mov    r2,  #0
	stm    r0!, {r1, r2}
.rept EXCEPTION_DATA_POINTERS - 1
	stm    r0!, {r2} /* Write `0' to all of the other exception registers */
.endr

	/* At this point, `r0' points at `&libc_except_info()->ei_data.e_faultaddr' */
#if EXCEPT_BACKTRACE_SIZE > 0
.Ldo_fill_trace_with_r0_on_faultaddr:
	add    r0, r0, #(ei_trace - (ei_data + e_faultaddr))
	mov    r2,  #0
.rept EXCEPT_BACKTRACE_SIZE
	stm    r0!, {r2} /* Write `0' to traceback register */
.endr
#endif /* EXCEPT_BACKTRACE_SIZE > 0 */
	b      .Ldo_unwind_sp

#ifndef NDEBUG
.Llibc_except_throw_inside_catch:

	/* Load arguments for `libc_except_badusage_throw_inside_catch' */
	mov    r3, #0                                                                  /* va_list args */
	mov    r2, #0                                                                  /* size_t argc */
	ldr    r1, [sp, #(STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE) + OFFSET_KCPUSTATE_R0)] /* except_code_t code */
	ASM_STACK_GET_BEFORE_ALIGN(r0, SIZEOF_KCPUSTATE)                               /* except_register_state_t const *state */

	EXTERN(libc_except_badusage_throw_inside_catch)
	bl     libc_except_badusage_throw_inside_catch
	nop    /* For unwinding */
#endif /* !NDEBUG */
	.cfi_endproc
END(libc_except_throw)


/* PUBLIC ATTR_NORETURN void FCALL except_throw_current(void); */
.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(except_throw_current, libc_except_throw_current)
INTERN_FUNCTION(libc_except_throw_current)
	.cfi_startproc
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R /* `lvar_state' */

	/* Load TLS context */
	INTERN(libc_except_info)
	bl     libc_except_info

	/* Set exception flags */
	mov    r12, #EXCEPT_FNORMAL
	strb   r12, [r0, #ei_flags]

	/* Fill in the TLS exception register state. */
#if (ei_state + ucs_pc) != 0
#error "This is assumed for the `stm' below"
#endif /* (ei_state + ucs_pc) != 0 */
#if STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE)
	ASM_STACK_GET_BEFORE_ALIGN(lr, SIZEOF_KCPUSTATE)
	ldm    lr,  {r1,r2,r3,r12}             /* ucs_pc, ucs_lr, ucs_sp, ucs_cpsr */
#else /* STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE) */
	ldm    sp,  {r1,r2,r3,r12}             /* ucs_pc, ucs_lr, ucs_sp, ucs_cpsr */
#endif /* !STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE) */
	str    r1,  [r0, #ei_data+e_faultaddr] /* Also set `e_faultaddr' to `pc' */

	stm    r0!, {r1,r2,r3,r12} /* ucs_pc, ucs_lr, ucs_sp, ucs_cpsr */
	/* NOTE: At this point, `r0' points at `&libc_except_info()->ei_state.ucs_r0' */
	add    r12, sp, #(STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE) + 16) /* r12 = &lvar_state->ucs_r0 */
	ldm    r12!,{r1,r2,r3,lr}  /* ucs_r0, ucs_r1, ucs_r2, ucs_r3 */
	stm    r0!, {r1,r2,r3,lr}  /* ucs_r0, ucs_r1, ucs_r2, ucs_r3 */

	/* Register r4-r11 are marked callee-preserve and thus weren't clobbered
	 * by  our call to `libc_except_info()'. And since we didn't modify them
	 * either, we can just store them to the TLS register buffer as-is! */
	ldr    r12, [sp, #(STACK_ALIGN_OFFSET(SIZEOF_KCPUSTATE) + ucs_r12)] /* Restore r12 */
	stm    r0!, {r4,r5,r6,r7,r8,r9,r10,r11,r12} /* ucs_r4, ..., ucs_r12 */

	/* r0 now points to `&libc_except_info()->e_code' */
	add    r0, r0, #(4 + (EXCEPTION_DATA_POINTERS * 4)) /* Skip over `e_code' and exception registers */

	/* At this point, `r0' points at `&libc_except_info()->ei_data.e_faultaddr' */
	b      .Ldo_unwind_sp_maybe_fill_trace_with_r0_on_faultaddr
	.cfi_endproc
END(libc_except_throw_current)


.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(_except_check_no_nesting, libc__except_check_no_nesting)
DEFINE_PUBLIC_ALIAS(_except_badusage_no_nesting, libc__except_badusage_no_nesting)

	/* >> void _except_check_no_nesting(void); */
INTERN_FUNCTION(libc__except_check_no_nesting)
	.cfi_startproc
	push_cfi_r {lr}

	ASM_STACK_ALIGN_AFTER(4)
	INTERN(libc_except_code)
	bl     libc_except_code
	ASM_STACK_UNALIGN_AFTER(4)

	cmp    r0, #EXCEPT_CODEOF(E_OK)
	popeq  {pc} /* If no exception is active, return to caller */
	pop_cfi_r {lr}
	/* fallthru to `_except_badusage_no_nesting()' */

	/* >> ATTR_NORETURN void _except_badusage_no_nesting(void); */
INTERN_FUNCTION(libc__except_badusage_no_nesting)
	ASM_PUSH_KCPUSTATE_ON_ENTRY_CFI_R
	mov    r0, sp
	ASM_STACK_ALIGN_AFTER(SIZEOF_KCPUSTATE)

	EXTERN(libc_except_badusage_no_nesting)
	bl     libc_except_badusage_no_nesting
	nop    /* For unwinding... */
END(libc__except_badusage_no_nesting)
	.cfi_endproc
END(libc__except_check_no_nesting)



/* ARM-specific exception-related functions */
.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(__aeabi_unwind_cpp_pr0, libc___aeabi_unwind_cpp_pr0)
INTERN_FUNCTION(libc___aeabi_unwind_cpp_pr0)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc___aeabi_unwind_cpp_pr0)

.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(__aeabi_unwind_cpp_pr1, libc___aeabi_unwind_cpp_pr1)
INTERN_FUNCTION(libc___aeabi_unwind_cpp_pr1)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc___aeabi_unwind_cpp_pr1)

.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(__cxa_end_cleanup, libc___cxa_end_cleanup)
INTERN_FUNCTION(libc___cxa_end_cleanup)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc___cxa_end_cleanup)


#endif /* !GUARD_LIBC_HYBRID_ARCH_ARM_EXCEPT32_S */
