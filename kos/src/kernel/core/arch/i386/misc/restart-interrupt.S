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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_RESTART_INTERRUPT_S
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_RESTART_INTERRUPT_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <kernel/restart-interrupt.h>

#include <hybrid/host.h>

#include <cfi.h>
#include <asm/instr/compat.h>
#include <kos/kernel/cpu-state-asm.h>


#ifdef __x86_64__
#define libcpu_apply_icpustate_Psp libcpu_apply_icpustate_rsp
#else /* __x86_64__ */
#define libcpu_apply_icpustate_Psp libcpu_apply_icpustate_esp
#endif /* !__x86_64__ */

/* Hard-set the current stack depth to `state' and invoke `cb()' by passing `state' to it.
 * Once  `cb()' returns, the cpu state returned by it is loaded, and execution is resumed.
 * WARNING: When this function is called, the caller's stack is _NOT_ unwound until `state'
 *          is reached. - No TRY-EXCEPT/FINALLY blocks or destructors are invoked, and this
 *          function does  not  return  in  any  way that  is  observable  to  the  caller.
 *          Rather,  it behaves similar to `longjmp()', in that `cb()' is made to return to
 *          the origin of `state' after being injected ontop of that location. */
/* FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2)) void
 * NOTHROW(FCALL kernel_restart_interrupt)(struct icpustate *__restrict state,
 *                                         kernel_interrupt_callback_t cb); */
.section .text
PUBLIC_FUNCTION(kernel_restart_interrupt)
	.cfi_startproc simple
	.cfi_def_cfa %R_fcall0P, 0
	ASM_CFI_OFFSET_RESTORE_ICPUSTATE(0)
	movP   %R_fcall0P, %Psp
	.cfi_def_cfa_register %Psp
	callP  *%R_fcall1P /* %Pax = (*cb)(state); */
	movP   %Pax, %Psp
	EXTERN(libcpu_apply_icpustate_Psp)
	jmp    libcpu_apply_icpustate_Psp
	.cfi_endproc
END(kernel_restart_interrupt)

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_RESTART_INTERRUPT_S */
