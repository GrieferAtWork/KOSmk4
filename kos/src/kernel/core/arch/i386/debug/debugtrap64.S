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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUG_DEBUGTRAP64_S
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUG_DEBUGTRAP64_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>
#include <cfi.h>
#include <asm/cpu-flags.h>
#include <kos/kernel/x86/gdt.h>


.section .xdata
PUBLIC_FUNCTION(kernel_debugtrap)
	/* PUBLIC void FCALL
	 * kernel_debugtrap(struct debugtrap_reason *reason); */
	.cfi_startproc
	ret
	popq_cfi  %rax
	.cfi_register %rip, %rax
	movq   %rsp, %rdx
	pushq_cfi $(SEGMENT_KERNEL_DATA0) /* %ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %rdx                    /* %rsp */
	.cfi_rel_offset %rsp, 0
	pushfq_cfi                        /* %rflags */
	pushq_cfi $(SEGMENT_KERNEL_CODE)  /* %cs */
	.cfi_rel_offset %cs, 0
	pushq_cfi %rax                    /* %rip */
	.cfi_rel_offset %rip, 0
	pushq_cfi_r %rax                  /* [C] Accumulator register */
	pushq_cfi_r %rcx                  /* [C] Count register */
	pushq_cfi_r %rdx                  /* [C] Data register */
	pushq_cfi_r %rbx                  /* [P] Base register */
	pushq_cfi_r %rbp                  /* [P] Frame base pointer */
	pushq_cfi_r %rsi                  /* [C] Source pointer */
	pushq_cfi_r %rdi                  /* [C] Destination pointer */
	pushq_cfi_r %r8                   /* [C] General purpose register #8 */
	pushq_cfi_r %r9                   /* [C] General purpose register #9 */
	pushq_cfi_r %r10                  /* [C] General purpose register #10 */
	pushq_cfi_r %r11                  /* [C] General purpose register #11 */
	pushq_cfi_r %r12                  /* [P] General purpose register #12 */
	pushq_cfi_r %r13                  /* [P] General purpose register #13 */
	pushq_cfi_r %r14                  /* [P] General purpose register #14 */
	pushq_cfi_r %r15                  /* [P] General purpose register #15 */
	movq   %rdi, %rsi      /* struct debugtrap_reason *reason */
	movq   %rsp, %rdi      /* struct icpustate *state */
	call   kernel_debugtrap_icpustate
	.cfi_endproc
END(kernel_debugtrap)

#define CPUSTATE_IS_ICPUSTATE
#define CPUSTATE icpustate
#include "debugtrap64-impl.S"

#define CPUSTATE_IS_SCPUSTATE
#define CPUSTATE scpustate
#include "debugtrap64-impl.S"

#define CPUSTATE ucpustate
#include "debugtrap64-impl.S"

#define CPUSTATE kcpustate
#include "debugtrap64-impl.S"

#define CPUSTATE lcpustate
#include "debugtrap64-impl.S"

#define CPUSTATE fcpustate
#include "debugtrap64-impl.S"

#endif /* 1GUARD_KERNEL_CORE_ARCH_I386_DEBUG_DEBUGTRAP64_S */
