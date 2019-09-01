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

#include <kernel/compiler.h>
#include <kernel/realmode.h>
#include <kernel/paging.h>
#include <asm/cfi.h>
#include <asm/cpu-flags.h>


#ifndef CONFIG_USE_LIBVM86_FOR_REALMODE

/* Realmode GDT indices (s.a. `x86_realmode_gdt') */
#define RM_SEGMENT_NULL   0x0000
#define RM_SEGMENT_CODE32 0x0008
#define RM_SEGMENT_DATA32 0x0010
#define RM_SEGMENT_CODE16 0x0018
#define RM_SEGMENT_DATA16 0x0020
#define RM_SEGMENT_COUNT  0x0028

#define STACKSIZE  256

.section .text.free
.weak x86_realmode_interrupt
INTERN_FUNCTION(x86_realmode_interrupt)
	.cfi_startproc
	pushfl_cfi_r
	/* Disable interrupts */
	cli
	/* Save callee-preserve registers. */
	pushl_cfi_r %edi
	pushl_cfi_r %esi
	pushl_cfi_r %ebx
	pushl_cfi_r %ebp
	pushl_cfi_r %ds
	pushl_cfi_r %es
	pushl_cfi_r %fs
	pushl_cfi_r %gs
	/* Save the current GDT & IDT, so we can load
	 * the BIOS one and restore our's later */
	subl   $18, %esp
	.cfi_adjust_cfa_offset 18
	sgdtl  12(%esp)
	sidtl  6(%esp)
	movw   $0x03ff, 0(%esp) /* LIMIT */
	movl   $0,      2(%esp) /* BASE */
	lidtl  (%esp)
	/* Jump to physical memory */
	jmp    1f - KERNEL_BASE
1:	leal   -KERNEL_BASE(%esp), %esp

	INTERN(x86_realmode_gdt)
	movw   $(RM_SEGMENT_COUNT - 1),           0(%esp) /* LIMIT */
	movl   $(x86_realmode_gdt - KERNEL_BASE), 2(%esp) /* BASE */
	lgdtl  (%esp)
	addl   $6, %esp
	.cfi_adjust_cfa_offset -6

	movl   %cr0, %eax
	pushl_cfi %eax
	andl   $~(CR0_PG), %eax /* Disable paging. */
	movl   %eax, %cr0
	movl   %cr3, %eax
	pushl_cfi %eax
	xorl   %eax, %eax
	movl   %eax, %cr3

	/* realmode base address */
	leal   -KERNEL_BASE(%ecx), %eax /* Update the CPU state location. */
	pushl_cfi %eax /* The register buffer given by the caller. */
	movl   x86_realmode_base - KERNEL_BASE, %ebp

	/* Copy the given CPU state onto the realmode stack. */
	leal   x86_realmode_interrupt_16_size + STACKSIZE - (SIZEOF_RMCPUSTATE + 4)(%ebp), %edi
	/* %esp == 0x423f08 */
	/* %edi == 0x7d4a */
	movl   %esp, SIZEOF_RMCPUSTATE(%edi) /* Store the original ESP after the state */
	movl   %edi, %esp /* Load the stack for realmode */
	movl   %eax, %esi
	movl   $SIZEOF_RMCPUSTATE, %ecx
	rep;   movsb
	movzwl x86_realmode_segment - KERNEL_BASE, %eax

	/* Jump into 16-bit code. */
	/* ljmpl $RM_SEGMENT_CODE16, x86_realmode_base */
	.byte  0xea
INTERN(x86_realmode_base)
x86_realmode_base:
	.long  0x00000000
END(x86_realmode_base)
	.word  RM_SEGMENT_CODE16
.Lx86_realmode_return:
	/* Ensure that proper segments have been loaded. */
	movw   $RM_SEGMENT_DATA32, %ax
	movw   %ax, %ss
	movw   %ax, %ds
	movw   %ax, %es
	movl   x86_realmode_base - KERNEL_BASE, %ebp
	movl   x86_realmode_interrupt_16_size + STACKSIZE - 4(%ebp), %esp /* Restore ESP */
	leal   x86_realmode_interrupt_16_size + STACKSIZE - (SIZEOF_RMCPUSTATE + 4)(%ebp), %esi
	popl_cfi %edi
	/* Copy the updated CPU state */
	movl   $SIZEOF_RMCPUSTATE, %ecx
	rep;   movsb

	/* Restore control registers. */
	popl_cfi %eax
	movl   %eax, %cr3
	popl_cfi %ecx
	movl   %ecx, %cr0

	/* Jump to virtual memory */
	leal   KERNEL_BASE(%esp), %esp
	jmp    1f + KERNEL_BASE
1:	/* Restore the original GDT & IDT */
	lidtl  0(%esp)
	lgdtl  6(%esp)
	addl   $12, %esp
	.cfi_adjust_cfa_offset -12
	/* Restore registers */
	popl_cfi_r  %gs
	popl_cfi_r  %fs
	popl_cfi_r  %es
	popl_cfi_r  %ds
	popl_cfi_r  %ebp
	popl_cfi_r  %ebx
	popl_cfi_r  %esi
	popl_cfi_r  %edi
	popfl_cfi_r
	ret
	.cfi_endproc
END(x86_realmode_interrupt)

INTERN_FUNCTION(x86_realmode_interrupt_16_entry)
	.code16
	/* STATE:
	 *   - %ax                     -- Data segment for `x86_realmode_interrupt_16_entry'
	 *   - %bp                     -- Offset into segment `%ax', where `x86_realmode_interrupt_16_entry' begins
	 *   - %sp                     -- Pointer to `x86_realmode_interrupt_16_entry + x86_realmode_interrupt_16_size + STACKSIZE - (SIZEOF_RMCPUSTATE + 4)'
	 *   - 0(%esp)                 -- struct rmcpustate state;
	 *   - SIZEOF_RMCPUSTATE(%esp) -- u32 return_esp;
	 */
	/* Compatibility mode with 16-bit code segment. */
	movw   $RM_SEGMENT_DATA16, %dx
	movw   %dx, %ss
	movw   %dx, %ds
	movw   %dx, %es
	leaw   (.Lentry_realmode - x86_realmode_interrupt_16_entry)(%bp), %dx
	movw   %dx, (1f - x86_realmode_interrupt_16_entry)(%bp)
	movw   %ax, (2f - x86_realmode_interrupt_16_entry)(%bp)

	/* Set the intended interrupt vector */
	movb   0(%esp), %al /* %al = intno */
	movb   %al, (77f - x86_realmode_interrupt_16_entry)(%bp)
	/* Load registers. */
	addw   $4,  %sp

	/* Disable protected mode */
	movl   %cr0, %eax
	andl   $~(CR0_PE | CR0_PG), %eax
	movl   %eax, %cr0

	/* Now to enter true real-mode */
	/* ljmpw $..., $.Lentry_realmode */
	.byte  0xea
1:	.word  0x0000 /* offset */
2:	.word  0x0000 /* segment */
.Lentry_realmode:
	movw   %cs, %ax
	movw   %ax, %ss
	nop
	popw   %ds
	popw   %es
	popw   %fs
	popw   %gs
	popfl
	popl   %eax
	popl   %ecx
	popl   %edx
	popl   %ebx
	popl   %ebp
	popl   %esi
	popl   %edi

	/* Perform the actual interrupt. */
	.byte  0xcd /* int $N */
77:	.byte  0x00

	/* Save new registers. */
	pushl  %edi
	pushl  %esi
	pushl  %ebp
	pushl  %ebx
	pushl  %edx
	pushl  %ecx
	pushl  %eax
	pushfl
	pushw  %gs
	pushw  %fs
	pushw  %es
	pushw  %ds
	subw   $4,  %sp
	cli

	/* Re-enable protected mode */
	movl   %cr0, %eax
	orl    $CR0_PE, %eax
	movl   %eax, %cr0

	/* Jmp back to 32-bit protected mode */
	ljmpl $RM_SEGMENT_CODE32, $.Lx86_realmode_return - KERNEL_BASE

	.code32
END(x86_realmode_interrupt_16_entry)
	/* There is a STACKSIZE-long stack located here */
INTERN(x86_realmode_interrupt_16_size)
x86_realmode_interrupt_16_size = . - x86_realmode_interrupt_16_entry

#endif /* !CONFIG_USE_LIBVM86_FOR_REALMODE */

