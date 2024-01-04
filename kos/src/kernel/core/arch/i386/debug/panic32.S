/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
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
#include <cfi.h>

/* ATTR_NORETURN void FCALL kernel_panic_here(void) */
.section .text.cold
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
	pushl_cfi  $(0)      /* char const *format */
	leal   8(%esp), %edx /* struct ucpustate *state */
	xorl   %ecx, %ecx    /* unsigned int n_skip */
	PUBLIC(kernel_vpanic_ucpustate_n)
	call   kernel_vpanic_ucpustate_n
	nop /* For tracebacks... */
	.cfi_endproc
END(kernel_panic_here)

/* ATTR_NORETURN void FCALL kernel_panic_here_n(unsigned int n_skip) */
.section .text.cold
PUBLIC_FUNCTION(kernel_panic_here_n)
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
	pushl_cfi  $(0)      /* char const *format */
	leal   8(%esp), %edx /* struct ucpustate *state */
	PUBLIC(kernel_vpanic_ucpustate_n)
	call   kernel_vpanic_ucpustate_n
	nop /* For tracebacks... */
	.cfi_endproc
END(kernel_panic_here_n)

/* ATTR_NORETURN void FCALL kernel_vpanic(char const *format, va_list args) */
.section .text.cold
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

/* ATTR_NORETURN void FCALL kernel_vpanic_n(unsigned int n_skip, char const *format, va_list args) */
.section .text.cold
PUBLIC_FUNCTION(kernel_vpanic_n)
	.cfi_startproc
	pushfl_cfi_r
	pushl_cfi_r %ss
	pushl_cfi_r %cs
	pushl_cfi_r %ds
	pushl_cfi_r %es
	pushl_cfi_r %fs
	pushl_cfi_r %gs
	pushal_cfi_r
	pushl_cfi SIZEOF_UCPUSTATE(%esp) /* va_list args */
	pushl_cfi %edx                   /* char const *format */
	leal   8(%esp), %edx             /* struct ucpustate *state */
//	movl   %ecx, %ecx                /* unsigned int n_skip */
	PUBLIC(kernel_vpanic_ucpustate_n)
	call   kernel_vpanic_ucpustate_n
	nop /* For tracebacks... */
	.cfi_endproc
END(kernel_vpanic_n)

/* ATTR_NORETURN void VCALL kernel_panic(char const *format, ...) */
.section .text.cold
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
	pushl_cfi %eax                          /* ... */
	PUBLIC(kernel_vpanic_ucpustate)
	call   kernel_vpanic_ucpustate
	nop /* For tracebacks... */
	.cfi_endproc
END(kernel_panic)

/* ATTR_NORETURN void VCALL kernel_panic_n(unsigned int n_skip, char const *format, ...) */
.section .text.cold
PUBLIC_FUNCTION(kernel_panic_n)
	.cfi_startproc
	pushfl_cfi_r
	pushl_cfi_r %ss
	pushl_cfi_r %cs
	pushl_cfi_r %ds
	pushl_cfi_r %es
	pushl_cfi_r %fs
	pushl_cfi_r %gs
	pushal_cfi_r
	movl   %esp, %edx                       /* struct ucpustate *state */
	movl   (SIZEOF_UCPUSTATE+0)(%esp), %ecx /* unsigned int n_skip */
	leal   (SIZEOF_UCPUSTATE+8)(%esp), %eax /* va_list args */
	pushl_cfi %eax                          /* ... */
	pushl_cfi (SIZEOF_UCPUSTATE+8)(%esp)    /* char const *format */
	PUBLIC(kernel_vpanic_ucpustate_n)
	call   kernel_vpanic_ucpustate_n
	nop /* For tracebacks... */
	.cfi_endproc
END(kernel_panic_n)

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUG_PANIC32_S */
