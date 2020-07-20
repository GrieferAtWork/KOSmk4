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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUG_PANIC32_S
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUG_PANIC32_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>
#include <kernel/panic.h>
#include <kos/kernel/cpu-state.h>
#include <asm/cfi.h>

.section .text.cold
/* ATTR_NORETURN void KCALL kernel_panic_here(void) */
PUBLIC_FUNCTION(kernel_panic_here)
	.cfi_startproc
	pushfl_cfi_r
	pushl_cfi_r %ss
	pushl_cfi_r %cs
	pushl_cfi_r %ds
	pushl_cfi_r %es
	pushl_cfi_r %fs
	pushl_cfi_r %gs
	pushal_cfi_r
	pushl_cfi  $(0)      /* va_list args */
	xorl   %edx, %edx    /* char const *format */
	leal   4(%esp), %ecx /* struct ucpustate *state */
	PUBLIC(kernel_vpanic_ucpustate)
	call   kernel_vpanic_ucpustate
	nop /* For tracebacks... */
	.cfi_endproc
END(kernel_panic_here)

.section .text.cold
/* ATTR_NORETURN void FCALL kernel_vpanic(char const *format, va_list args) */
PUBLIC_FUNCTION(kernel_vpanic)
	.cfi_startproc
	pushfl_cfi_r
	pushl_cfi_r %ss
	pushl_cfi_r %cs
	pushl_cfi_r %ds
	pushl_cfi_r %es
	pushl_cfi_r %fs
	pushl_cfi_r %gs
	pushal_cfi_r
	pushl_cfi  %edx      /* va_list args */
	movl   %ecx, %edx    /* char const *format */
	leal   4(%esp), %ecx /* struct ucpustate *state */
	PUBLIC(kernel_vpanic_ucpustate)
	call   kernel_vpanic_ucpustate
	nop /* For tracebacks... */
	.cfi_endproc
END(kernel_vpanic)

.section .text.cold
/* ATTR_NORETURN void VCALL kernel_panic(char const *format, ...) */
PUBLIC_FUNCTION(kernel_panic)
	.cfi_startproc
	pushfl_cfi_r
	pushl_cfi_r %ss
	pushl_cfi_r %cs
	pushl_cfi_r %ds
	pushl_cfi_r %es
	pushl_cfi_r %fs
	pushl_cfi_r %gs
	pushal_cfi_r
	movl   %esp, %ecx                       /* struct ucpustate *state */
	movl   (SIZEOF_UCPUSTATE+0)(%esp), %edx /* char const *format */
	leal   (SIZEOF_UCPUSTATE+4)(%esp), %eax /* va_list args */
	pushl_cfi %eax                          /* va_list args */
	PUBLIC(kernel_vpanic_ucpustate)
	call   kernel_vpanic_ucpustate
	nop /* For tracebacks... */
	.cfi_endproc
END(kernel_panic)

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUG_PANIC32_S */
