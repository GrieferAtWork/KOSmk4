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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_BOOT__START64_S
#define GUARD_KERNEL_CORE_ARCH_I386_BOOT__START64_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <kernel/arch/paging64.h>
#include <kernel/paging.h>
#include <kernel/x86/cpuid.h>

#include <hybrid/align.h>

#include <asm/cpu-cpuid.h>
#include <asm/cpu-flags.h>
#include <asm/cpu-msr.h>
#include <asm/instr/interrupt.h>
#include <asm/instr/ttest.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/bits/cpu-state32.h>
#include <kos/kernel/bits/cpu-state64.h>
#include <kos/kernel/x86/gdt.h>
#include <kos/kernel/x86/segment.h>
#include <kos/kernel/x86/tss.h>

/**/
#include "_objects.S"
/**/

#define P2V(x) ((x) + KERNEL_CORE_BASE)
#define V2P(x) ((x) - KERNEL_CORE_BASE)
#define SYM(x) ((x) - KERNEL_CORE_BASE)

EXTERN(boot_cpustate)
EXTERN(__kernel_boottask_stack)
EXTERN(bootcpu_x86_cpufeatures)
EXTERN(bootcpu_x86_cpuid)

#ifndef CONFIG_NO_KERNEL_X86_BOOT0
/* Include builtin bootloader support */
#include "_boot0.S"
#endif /* !CONFIG_NO_KERNEL_X86_BOOT0 */



#define VGA_BASE   0xb8000
#define VGA_WIDTH  80
#define VGA_HEIGHT 25

.code32

.section .bss.free
INTERN_OBJECT(boot_failure_vga_ptr)
	.long 0
END(boot_failure_vga_ptr)

.section .text.free

/* CLOBBER: [%eflags]
 * OUT: [pointer_to_vga_base: %edi]
 * Clear the VGA screen and re-initialize the VGA pointer. */
PRIVATE_FUNCTION(vga_cls)
	pushl  %eax
	pushl  %ecx
	leal   VGA_BASE, %edi
	movl   %edi, SYM(boot_failure_vga_ptr)
	movl   $(VGA_WIDTH * VGA_HEIGHT), %ecx
	xorl   %eax, %eax
	rep    stosw
	leal   VGA_BASE, %edi
	popl   %ecx
	popl   %eax
	ret
END(vga_cls)

/* CLOBBER: [%eflags]
 * OUT: [pointer_to_start_of_last_line: %edi]
 * Scroll the  VGA  display  by 1  line  and  set
 * the VGA pointer to the start of the last line. */
PRIVATE_FUNCTION(vga_scroll)
	pushl  %esi
	pushl  %ecx
	pushl  %eax
	leal   VGA_BASE, %edi
	leal   VGA_BASE + (VGA_WIDTH * 2), %esi
	movl   $(VGA_WIDTH * (VGA_HEIGHT - 1)), %ecx
	rep    movsw /* Scroll display */
	movl   %edi, SYM(boot_failure_vga_ptr) /* Set to last line */
	movl   $(VGA_WIDTH), %ecx
	xorl   %eax, %eax
	rep    stosw /* Clear text from last line */
	subl   $(VGA_WIDTH * 2), %edi
	popl   %eax
	popl   %ecx
	popl   %esi
	ret
END(vga_scroll)


/* IN:      [ch: %al]
 * CLOBBER: [%eax, %eflags]
 * Output the given character to screen */
PRIVATE_FUNCTION(vga_putc)
	pushl  %edi
	movl   SYM(boot_failure_vga_ptr), %edi
	testl  %edi, %edi
	jnz    1f
	call   vga_cls
1:	cmpl   $(VGA_BASE + (VGA_WIDTH * VGA_HEIGHT * 2)), %edi
	jnae   1f
	call   vga_scroll /* Scroll if past the end */
1:	cmpb   $'\n', %al
	jne    98f
	/* Special character: `\n' */
	pushl  %ecx
	pushl  %edx
	leal   -VGA_BASE(%edi), %ecx
	movl   $(VGA_WIDTH * 2), %edx
	movw   %cx, %ax
	divb   %dl
	/* EDI = VGA_BASE + (ECX + ((VGA_WIDTH * 2) - AH)) */
	leal   (VGA_BASE + (VGA_WIDTH * 2))(%ecx), %edi
	/* EDI = EDI - AH */
	movzbl %ah, %eax
	/* EDI = EDI - EAX */
	subl   %eax, %edi
	popl   %edx
	popl   %ecx
	cmpl   $(VGA_BASE + (VGA_WIDTH * VGA_HEIGHT * 2)), %edi
	jnae   99f
	call   vga_scroll /* Scroll if past the end */
	jmp    99f
98:	movb   $(7 | 0 << 4), %ah /* Light gray on black. */
	stosw  /* Print the character */
99:	movl   %edi, SYM(boot_failure_vga_ptr)
	popl   %edi
	ret
END(vga_putc)


/* IN:      [str: %esi]
 * CLOBBER: [%esi, %eflags]
 * Output the given string to screen. */
PRIVATE_FUNCTION(vga_puts)
	pushl  %eax
1:	lodsb
	testb  %al, %al
	jz     2f
	call   vga_putc
	jmp    1b
2:	popl   %eax
	ret
END(vga_puts)

#define DEFINE_PRIVATE_STRING(name, str) \
	.section .data.free;                 \
		PRIVATE_OBJECT(name);            \
		.asciz str;                      \
		END(name);                       \
	.section .text.free;



/* IN: [reason_string: %esi]
 * Print an error message and abort booting. */
PRIVATE_FUNCTION(boot_failure)
	pushl  %esi
	DEFINE_PRIVATE_STRING(str_bootfailure_1, "Failed to boot into 64-bit mode:\n    ")
	leal   SYM(str_bootfailure_1), %esi
	call   vga_puts
	popl   %esi
	call   vga_puts /* Print the message given by the caller */
	DEFINE_PRIVATE_STRING(str_bootfailure_2, "\n\nPress CTRL+ALT+DEL to reboot")
	leal   SYM(str_bootfailure_2), %esi
	call   vga_puts
1:	hlt
	jmp 1b
END(boot_failure)

/* IN: [reason_string: %esi]
 * CLOBBER: [%eflags]
 * Print a warning message and return. */
PRIVATE_FUNCTION(boot_warning)
	pushl  %esi
	DEFINE_PRIVATE_STRING(str_bootwarning_1, "WARNING: ")
	leal   SYM(str_bootwarning_1), %esi
	call   vga_puts
	popl   %esi
	call   vga_puts
	DEFINE_PRIVATE_STRING(str_bootwarning_2, ".\n\
KOS may behave unexpectedly, crash, or not be able to boot at all.\n\n")
	leal   SYM(str_bootwarning_2), %esi
	call   vga_puts
	/* Only print the warning implication message once */
	movb   $(0), SYM(str_bootwarning_2) + 2
	ret
END(boot_warning)


PRIVATE_FUNCTION(boot_failure_no_cpuid)
	DEFINE_PRIVATE_STRING(str_nocpuid, "The <CPUID> instruction is not supported")
	leal   SYM(str_nocpuid), %esi
	jmp    boot_failure
END(boot_failure_no_cpuid)

PRIVATE_FUNCTION(boot_failure_no_cpuid_0x1)
	DEFINE_PRIVATE_STRING(str_nocpuid_0x1, "The cpuid leaf <1h> is not implemented")
	leal   SYM(str_nocpuid_0x1), %esi
	jmp    boot_failure
END(boot_failure_no_cpuid_0x1)

PRIVATE_FUNCTION(boot_failure_no_cpuid_0x80000001)
	DEFINE_PRIVATE_STRING(str_nocpuid_0x80000001, "The cpuid leaf <80000001h> is not implemented")
	leal   SYM(str_nocpuid_0x80000001), %esi
	jmp    boot_failure
END(boot_failure_no_cpuid_0x80000001)

PRIVATE_FUNCTION(boot_failure_no_longmode)
	DEFINE_PRIVATE_STRING(str_no_longmode, "\
Long mode (64-bit mode) is not supported\n\
    [cpuid leaf 80000001h:%edx is lacking #LM (bit #29)]")
	leal   SYM(str_no_longmode), %esi
	jmp    boot_failure
END(boot_failure_no_longmode)

PRIVATE_FUNCTION(boot_failure_no_pae)
	DEFINE_PRIVATE_STRING(str_no_pae, "\
PAE (Physical Address Extension) Paging is not supported\n\
    [cpuid leaf 80000001h:%edx is lacking #PAE (bit #6)]")
	leal   SYM(str_no_pae), %esi
	jmp    boot_failure
END(boot_failure_no_pae)

PRIVATE_FUNCTION(boot_failure_no_pse)
	DEFINE_PRIVATE_STRING(str_no_pse, "\
PSE (Page Size Extension) Paging is not supported\n\
    [cpuid leaf 80000001h:%edx is lacking #PSE (bit #3)]")
	leal   SYM(str_no_pse), %esi
	jmp    boot_failure
END(boot_failure_no_pse)

PRIVATE_FUNCTION(boot_failure_no_msr)
	DEFINE_PRIVATE_STRING(str_no_msr, "\
MSR (Model Specific Registers) are not implemented\n\
    [cpuid leaf 80000001h:%edx is lacking #PSE (bit #3)]")
	leal   SYM(str_no_msr), %esi
	jmp    boot_failure
END(boot_failure_no_msr)

PRIVATE_FUNCTION(boot_warning_no_sse)
	DEFINE_PRIVATE_STRING(str_no_sse, "SSE is not supported by the host")
	leal   SYM(str_no_sse), %esi
	jmp    boot_warning
END(boot_warning_no_sse)

PRIVATE_FUNCTION(boot_warning_no_sse2)
	DEFINE_PRIVATE_STRING(str_no_sse2, "SSE2 is not supported by the host")
	leal   SYM(str_no_sse2), %esi
	jmp    boot_warning
END(boot_warning_no_sse2)

PRIVATE_FUNCTION(boot_warning_no_mmx)
	DEFINE_PRIVATE_STRING(str_no_mmx, "MMX instruction are not provided by the host")
	leal   SYM(str_no_mmx), %esi
	jmp    boot_warning
END(boot_warning_no_mmx)

PRIVATE_FUNCTION(boot_warning_no_fpu)
	DEFINE_PRIVATE_STRING(str_no_fpu, "No on-board FPU provided by the host")
	leal   SYM(str_no_fpu), %esi
	jmp    boot_warning
END(boot_warning_no_fpu)

PRIVATE_FUNCTION(boot_warning_no_tsc)
	DEFINE_PRIVATE_STRING(str_no_tsc, "The <RDTSC> instruction is not provided by the host")
	leal   SYM(str_no_tsc), %esi
	jmp    boot_warning
END(boot_warning_no_tsc)

PRIVATE_FUNCTION(boot_warning_no_cmov)
	DEFINE_PRIVATE_STRING(str_no_cmov, "The <CMOVcc> instructions are not provided by the host")
	leal   SYM(str_no_cmov), %esi
	jmp    boot_warning
END(boot_warning_no_cmov)

PRIVATE_FUNCTION(boot_warning_no_cx8)
	DEFINE_PRIVATE_STRING(str_no_cx8, "The <cmpxchg8b> instruction is not provided by the host")
	leal   SYM(str_no_cx8), %esi
	jmp    boot_warning
END(boot_warning_no_cx8)

PRIVATE_FUNCTION(boot_warning_no_fxsr)
	DEFINE_PRIVATE_STRING(str_no_fxsr, "The <fxsave> and <fxrstor> instructions are not provided by the host")
	leal   SYM(str_no_fxsr), %esi
	jmp    boot_warning
END(boot_warning_no_fxsr)



.code32
.section .text.free
INTERN_FUNCTION(_start)
	/* Boot loader entry point. */
	movl   %edi, V2P(boot_cpustate + OFFSET_FCPUSTATE32_GPREGS + OFFSET_GPREGS32_EDI)
	movl   %esi, V2P(boot_cpustate + OFFSET_FCPUSTATE32_GPREGS + OFFSET_GPREGS32_ESI)
	movl   %ebp, V2P(boot_cpustate + OFFSET_FCPUSTATE32_GPREGS + OFFSET_GPREGS32_EBP)
	movl   %esp, V2P(boot_cpustate + OFFSET_FCPUSTATE32_GPREGS + OFFSET_GPREGS32_ESP)
	movl   %ebx, V2P(boot_cpustate + OFFSET_FCPUSTATE32_GPREGS + OFFSET_GPREGS32_EBX)
	movl   %edx, V2P(boot_cpustate + OFFSET_FCPUSTATE32_GPREGS + OFFSET_GPREGS32_EDX)
	movl   %ecx, V2P(boot_cpustate + OFFSET_FCPUSTATE32_GPREGS + OFFSET_GPREGS32_ECX)
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_GPREGS + OFFSET_GPREGS32_EAX)
	sgdtl  V2P(boot_cpustate + OFFSET_FCPUSTATE32_GDT + 2)
	sidtl  V2P(boot_cpustate + OFFSET_FCPUSTATE32_IDT + 2)
	movl   $(V2P(_start)), V2P(boot_cpustate + OFFSET_FCPUSTATE32_EIP)
	movw   %gs, V2P(boot_cpustate + OFFSET_FCPUSTATE32_GS)
	movw   %fs, V2P(boot_cpustate + OFFSET_FCPUSTATE32_FS)
	movw   %es, V2P(boot_cpustate + OFFSET_FCPUSTATE32_ES)
	movw   %ds, V2P(boot_cpustate + OFFSET_FCPUSTATE32_DS)
	movw   %cs, V2P(boot_cpustate + OFFSET_FCPUSTATE32_CS)
	movw   %ss, V2P(boot_cpustate + OFFSET_FCPUSTATE32_SS)
	strw   V2P(boot_cpustate + OFFSET_FCPUSTATE32_TR)
	sldtw  V2P(boot_cpustate + OFFSET_FCPUSTATE32_LDT)
	movl   %cr0, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_COREGS + OFFSET_COREGS32_CR0)
	movl   %cr2, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_COREGS + OFFSET_COREGS32_CR2)
	movl   %cr3, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_COREGS + OFFSET_COREGS32_CR3)
	movl   %cr4, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_COREGS + OFFSET_COREGS32_CR4)
	movl   %dr0, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_DRREGS + OFFSET_DRREGS32_DR0)
	movl   %dr1, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_DRREGS + OFFSET_DRREGS32_DR1)
	movl   %dr2, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_DRREGS + OFFSET_DRREGS32_DR2)
	movl   %dr3, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_DRREGS + OFFSET_DRREGS32_DR3)
	movl   %dr6, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_DRREGS + OFFSET_DRREGS32_DR6)
	movl   %dr7, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_DRREGS + OFFSET_DRREGS32_DR7)
	movl   $(V2P(__kernel_boottask_stack + KERNEL_STACKSIZE)), %esp

#if 1 /* Fixup required when loaded via bochs's `load32bitOSImage' function */
	/* Prematurely load our GDT, so we can manually set valid segments for %ds, %es and %ss,
	 * as  we only  want to  rely on  the boot loader  to have  set up  a valid  %ds and %cs */
	.pushsection .rodata.free
1:	.word  (SEGMENT_COUNT * 8 - 1)
	.long  V2P(__templatecpu_x86_gdt)
	.popsection
	lgdtl  %ds:V2P(1b)
	movw   $(SEGMENT_KERNEL_DATA32), %ax
	movw   %ax, %ss
	movw   %ax, %ds
	movw   %ax, %es
#endif

	pushfl
	movl   0(%esp), %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_EFLAGS)
	/* Make sure that %eflags is in a valid state */
	andl   $(~(EFLAGS_IF | /* Disable interrupts */                                      \
	           EFLAGS_TF |                                                               \
	           EFLAGS_DF | /* Clear the direction bit (required for REP instructions) */ \
	           EFLAGS_IOPLMASK |                                                         \
	           EFLAGS_NT |                                                               \
	           EFLAGS_RF |                                                               \
	           EFLAGS_AC                                                                 \
	           )), %eax
	movl   %eax, 0(%esp)
	popfl


#ifndef CONFIG_NO_SMP
	/* memcpy(&bootcpu, __kernel_percpu_start, (size_t)__kernel_percpu_size); */
	EXTERN(bootcpu)
	EXTERN(__kernel_percpu_start)
	EXTERN(__kernel_percpu_size)
	movl   $(V2P(bootcpu)), %edi
	movl   $(V2P(__kernel_percpu_start)), %esi
	movl   $(__kernel_percpu_size), %ecx
	rep    movsb

	/* memcpy(&bootcpu_x86_tss, __kernel_percpu_tss, SIZEOF_TSS); */
	EXTERN(bootcpu_x86_tss)
	EXTERN(__kernel_percpu_tss)
	movl   $(V2P(bootcpu_x86_tss)), %edi
	movl   $(V2P(__kernel_percpu_tss)), %esi
#if IS_ALIGNED(SIZEOF_TSS, 4)
	movl   $(SIZEOF_TSS / 4), %ecx
	rep    movsl
#elif IS_ALIGNED(SIZEOF_TSS, 2)
	movl   $(SIZEOF_TSS / 2), %ecx
	rep    movsw
#else /* ... */
	movl   $(SIZEOF_TSS), %ecx
	rep    movsb
#endif /* !... */
#endif /* !CONFIG_NO_SMP */

	/* memcpy(&bootidle, __kernel_pertask_start, (size_t)__kernel_pertask_size); */
	EXTERN(bootidle)
	EXTERN(__kernel_pertask_start)
	EXTERN(__kernel_pertask_size)
	movl   $(V2P(bootidle)), %edi
	movl   $(V2P(__kernel_pertask_start)), %esi
	movl   $(__kernel_pertask_size), %ecx
	rep    movsb

	/* memcpy(&boottask, __kernel_pertask_start, (size_t)__kernel_pertask_size); */
	EXTERN(boottask)
	movl   $(V2P(boottask)), %edi
	movl   $(V2P(__kernel_pertask_start)), %esi
	movl   $(__kernel_pertask_size), %ecx
	rep    movsb

	/* memcpy(&asyncwork, __kernel_pertask_start, (size_t)__kernel_pertask_size); */
	EXTERN(asyncwork)
	movl   $(V2P(asyncwork)), %edi
	movl   $(V2P(__kernel_pertask_start)), %esi
	movl   $(__kernel_pertask_size), %ecx
	rep    movsb

	/* memcpy((byte_t *)&mman_kernel + PAGEDIR_SIZE, __kernel_permman_start, (size_t)__kernel_permman_size); */
	EXTERN(mman_kernel)
	EXTERN(__kernel_permman_start)
	EXTERN(__kernel_permman_size)
	movl   $(V2P(mman_kernel) + PAGEDIR_SIZE), %edi
	movl   $(V2P(__kernel_permman_start)), %esi
	movl   $(__kernel_permman_size), %ecx
	rep    movsb

	/* Set the DIDINIT flag for the boot cpu's feature table. */
	EXTERN(bootcpu_x86_cpufeatures)
	orl    $(CPU_FEATURE_FDIDINIT), V2P(bootcpu_x86_cpufeatures)

	/* Check if CPUID is supported. */
	pushfl
	pushfl
	xorl   $(EFLAGS_ID), 0(%esp)
	popfl
	pushfl
	popl   %eax
	xorl   0(%esp), %eax
	popfl
	andl   $(EFLAGS_ID), %eax
	jz     boot_failure_no_cpuid

	xorl   %eax, %eax
	cpuid
	cmpl   $(1), %eax
	jb     boot_failure_no_cpuid_0x1
	movl   %eax, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_0A
	movl   %ebx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_0B
	movl   %edx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_0D
	movl   %ecx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_0C

	/* Query additional CPUID features. */
	cmpl   $(7), %eax
	jnae   1f
	movl   $(7), %eax
	movl   $(0), %ecx /* Sub-leaf:0 */
	cpuid
	movl   %edx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_7D
	movl   %ecx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_7C
	movl   %ebx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_7B
1:

	movl   $(0x80000000), %eax
	cpuid
	movl   %eax, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000000A
	cmpl   $(0x80000001), %eax
	jnae   boot_failure_no_cpuid_0x80000001

	movl   $(0x80000001), %eax
	cpuid
	movl   %ecx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000001C
	movl   %edx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000001D


#define CALL_IF_Z(func) \
	jnz    991f;        \
	call   func;        \
991:



	/* Test the LM bit. */
	ttest  mask=CPUID_80000001D_LM, loc=%edx
	jz     boot_failure_no_longmode

	/* Test the PAE bit. */
	ttest  mask=CPUID_80000001D_PAE, loc=%edx
//	jz     boot_failure_no_pae

	/* Test the PSE bit. */
	ttest  mask=CPUID_80000001D_PSE, loc=%edx
//	jz     boot_failure_no_pse

	/* Test the CX8 bit. */
	ttest  mask=CPUID_80000001D_CX8, loc=%edx
	CALL_IF_Z(boot_warning_no_cx8)

	/* Test the FXSR bit. */
	ttest  mask=CPUID_80000001D_FXSR, loc=%edx
	CALL_IF_Z(boot_warning_no_fxsr)

	/* Check if we can extract the brand string from cpuid */
	movl   V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000000A, %eax

	cmpl   $(0x80000007), %eax
	jnae   4f
	movl   $(0x80000007), %eax
	cpuid
	movl   %edx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000007D
	jmp    5f
4:	cmpl   $(0x80000004), %eax
	jnae   3f
5:

	movl   $(0x80000004), %eax
	cpuid
	movl   %eax, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000004A
	movl   %ebx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000004B
	movl   %ecx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000004C
	movl   %edx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000004D

	movl   $(0x80000003), %eax
	cpuid
	movl   %eax, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000003A
	movl   %ebx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000003B
	movl   %ecx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000003C
	movl   %edx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000003D

	movl   $(0x80000002), %eax
	cpuid
	movl   %eax, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000002A
	movl   %ebx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000002B
	movl   %ecx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000002C
	movl   %edx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000002D
3:  /* ci_80000000a < 0x80000004 */


	movl   $(1), %eax
	cpuid
	movl   %eax, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_1A
	movl   %ebx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_1B
	movl   %edx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_1D
	movl   %ecx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_1C

	/* Test the MSR bit. */
	ttest  mask=CPUID_1D_MSR, loc=%edx
	jz     boot_failure_no_msr

	/* Check for SSE support */
	ttest  mask=CPUID_1D_SSE, loc=%edx
	CALL_IF_Z(boot_warning_no_sse)

	/* Check for SSE2 support */
	ttest  mask=CPUID_1D_SSE2, loc=%edx
	CALL_IF_Z(boot_warning_no_sse2)

	/* Check for MMX support */
	ttest  mask=CPUID_1D_MMX, loc=%edx
	CALL_IF_Z(boot_warning_no_mmx)

	/* Check for FPU support */
	ttest  mask=CPUID_1D_FPU, loc=%edx
	CALL_IF_Z(boot_warning_no_fpu)

	/* Check for TSC support */
	ttest  mask=CPUID_1D_TSC, loc=%edx
	CALL_IF_Z(boot_warning_no_tsc)

	/* Check for CMOV support */
	ttest  mask=CPUID_1D_CMOV, loc=%edx
	CALL_IF_Z(boot_warning_no_cmov)

	/* Check for PGE support */
	ttest  mask=CPUID_1D_PGE, loc=%edx
	jnz    1f
	EXTERN(used_pxx_page_fglobal)
	movl   $(0), V2P(used_pxx_page_fglobal)
#if P64_PAGE_FGLOBAL > 0xffffffff
	movl   $(0), V2P(used_pxx_page_fglobal) + 4
#endif /* P64_PAGE_FGLOBAL > 0xffffffff */
1:

	/* if (Family == 6 && Model < 3 && Stepping < 3)
	 *     OFFSET_CPUID_1D &= ~CPUID_1D_SEP; */
	ttest  mask=CPUID_1D_SEP, loc=%edx
	jz     1f
	movl   %eax, %ecx
	andl   $(CPUID_1A_FAMILY_M), %ecx
	cmpl   $(6 << CPUID_1A_FAMILY_S), %ecx
	jne    1f  /* if (Family != 6) goto 1f; */
	movl   %eax, %ecx
	andl   $(CPUID_1A_MODEL_M), %ecx
#if CPUID_1A_MODEL_S != 0
	shrl   $(CPUID_1A_MODEL_S), %ecx
#endif /* CPUID_1A_MODEL_S != 0 */
	cmpl   $(3), %ecx
	jae    1f  /* if (Model >= 3) goto 1f; */
	movl   %eax, %ecx
	andl   $(CPUID_1A_STEPPING_M), %ecx
#if CPUID_1A_STEPPING_S != 0
	shrl   $(CPUID_1A_STEPPING_S), %ecx
#endif /* CPUID_1A_STEPPING_S != 0 */
	cmpl   $(3), %ecx
	/* if (Stepping >= 3) goto 1f; */
	jae    1f
	andl   $~CPUID_1D_SEP, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_1D
1:


	EXTERN(pagedir_kernel)
	EXTERN(__x86_pagedir_kernel_share)
	/* union p64_pdir_e3 ks_share_e3[256][512]; */
#define ks_share_e3(i, j) V2P(__x86_pagedir_kernel_share + ((i) * 4096) + ((j) * 8))
	/* union p64_pdir_e2 ks_share_e2[2][512]; */
#define ks_share_e2(i, j) ks_share_e3(256 + i, j)
#define pagedir_kernel_p_e4(i) V2P(pagedir_kernel + (i) * 8)

#define FLAGS_PAGE2MIB ((P64_PAGE_FACCESSED | P64_PAGE_FWRITE | P64_PAGE_FPRESENT | P64_PAGE_FDIRTY | P64_PAGE_F2MIB) & 0xffffffff)
#define FLAGS_VECTOR   ((P64_PAGE_FACCESSED | P64_PAGE_FWRITE | P64_PAGE_FPRESENT) & 0xffffffff)

	/* Initialize   x86_64   paging:
	 * >> u64 word = FLAGS_PAGE2MIB;
	 * >> for (unsigned int i = 0; i < 2 * 512; ++i) {
	 * >>     ks_share_e2[i / 512][i % 512].p_word = word;
	 * >>     word += 512 * 4096; // 2MiB
	 * >> } */
	movl   $(2 * 512), %ecx
	movl   $(FLAGS_PAGE2MIB), %edx
	movl   $(ks_share_e2(0, 0)), %edi
1:	movl   %edx, %eax
	stosl
	xorl   %eax, %eax
	stosl
	addl   $(512 * 4096), %edx
	loop   1b

	/* Fill in the last two elements of `ks_share_e3'
	 * NOTE: Also fill in the first two, so that our current code can remain
	 *       identity-mapped (since we're currently running from low memory)
	 * >> ks_share_e3[0][0]     = &ks_share_e2[0][0] + FLAGS_VECTOR; // Deleted later
	 * >> ks_share_e3[0][1]     = &ks_share_e2[1][0] + FLAGS_VECTOR; // Deleted later
	 * >> ks_share_e3[255][510] = &ks_share_e2[0][0] + FLAGS_VECTOR;
	 * >> ks_share_e3[255][511] = &ks_share_e2[1][0] + FLAGS_VECTOR; */
	movl   $(ks_share_e2(0, 0) + FLAGS_VECTOR), ks_share_e3(0, 0) /* Deleted later */
	movl   $(ks_share_e2(1, 0) + FLAGS_VECTOR), ks_share_e3(0, 1) /* Deleted later */
	movl   $(ks_share_e2(0, 0) + FLAGS_VECTOR), ks_share_e3(255, 510)
	movl   $(ks_share_e2(1, 0) + FLAGS_VECTOR), ks_share_e3(255, 511)
	/* Set the E3 vector within the page directory.
	 * >> pagedir_kernel.p_e4[0] = &ks_share_e3[0][0] + FLAGS_VECTOR; // Deleted later
	 * >> for (unsigned int i = 0; i < 256; ++i) {
	 * >>     pagedir_kernel.p_e4[256 + i] = &ks_share_e3[i][0] + FLAGS_VECTOR;
	 * >> } */
	movl   $(ks_share_e3(0, 0) + FLAGS_VECTOR), pagedir_kernel_p_e4(0) /* Deleted later */
	movl   $(pagedir_kernel_p_e4(256)), %edi
	movl   $(ks_share_e3(0, 0) + FLAGS_VECTOR), %edx
	movl   $(256), %ecx
1:	movl   %edx, %eax
	stosl
	xorl   %eax, %eax
	stosl
	addl   $(4096), %edx
	loop   1b
	/* Setup the page directory identity mapping
	 * >> pagedir_kernel.p_e4[257] = &pagedir_kernel.p_e4[0] + FLAGS_VECTOR; */
	movl   $(pagedir_kernel_p_e4(0) + FLAGS_VECTOR), pagedir_kernel_p_e4(257)
	/* HINT: Right now our pagedir looks like this:
	 *  - [0] 0000000000000000..000000007fffffff --> 0000000000000000..000000007fffffff
	 *  - [1] ffff800000000000..ffff80007fffffff --> 0000000000000000..000000007fffffff (Redundant, unavoidable, and never used)
	 *  - [2] ffff808000000000..ffff80ffffffffff --> <recursive page-directory self-mapping>
	 *  - [3] ffffffff80000000..ffffffffffffffff --> 0000000000000000..000000007fffffff
	 * We're currently running from [0] and eventually want to end up running from [3]
	 * Once  we're  at [3],  we'll  be deleting  the  mappings producing  [0]  and [1] */

	/* Prepare to enable paging. */
	movl   $(pagedir_kernel_phys), %eax
	movl   %eax, %cr3

	/* Configure the %CR4 register. */
	movl   %cr4, %eax
	/* Enable PageSizeExtension (required for 2Mib pages & long-mode),
	 * as well as  PhysicalAddressExtension (required  for the  48-bit
	 * physical address space needed in long-mode) */
	orl    $(CR4_PSE | CR4_PAE), %eax

	/* Enable PGE if supported by the host (optional feature) */
	ttest  mask=CPUID_1D_PGE, loc=(V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_1D)
	jz     1f
	orl    $(CR4_PGE), %eax
1:
	/* Enable SMAP if supported by the host (optional feature) */
	ttest  mask=CPUID_7B_SMEP, loc=(V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_7B)
	jz     1f
	orl    $(CR4_SMEP), %eax
1:
	/* Enable FSGSBASE if supported by the host (emulated if unsupported) */
	ttest  mask=CPUID_7B_FSGSBASE, loc=(V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_7B)
	jz     1f
	orl    $(CR4_FSGSBASE), %eax
1:
	/* Save the fully configured CR4 register. */
	movl   %eax, %cr4

	/* Set the LME bit in the EFER MSR register. */
	movl   $(IA32_EFER), %ecx
	rdmsr
	orl    $(IA32_EFER_LME), %eax /* LongModeEnabled */
	/* Since we're already here, try to enable some other long-mode extensions,
	 * such   as   the   NXE   bit,   as   well   as   SCE  (SysCallExtensions) */
	ttest  mask=CPUID_80000001D_NX, loc=(V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000001D)
	jz     1f
	orl    $(IA32_EFER_NXE), %eax
1:	ttest  mask=CPUID_80000001D_SYSCALL, loc=(V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000001D)
	jz     1f
	orl    $(IA32_EFER_SCE), %eax
1:	wrmsr  /* Save the new configuration. */

	/* Now to actually enable paging! */
	movl  %cr0, %eax
	orl   $(CR0_PG | CR0_WP), %eax
	movl  %eax, %cr0

	/* Even though paging's been enabled now, we can't unmap the unused identity mappings
	 * just yet, because we're still running from low-memory and can't jump to our target
	 * located at the end of the 64-bit  address space until we've actually entered  long
	 * mode. */

	.pushsection .rodata.free
	.align 8
	PRIVATE_OBJECT(enterlong_gdt)
#define DEFINE_SEGMENT_DESCRIPTOR(TYPE, args) \
		.int SEGMENT_##TYPE##_INIT_UL args;   \
		.int SEGMENT_##TYPE##_INIT_UH args;
		DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0))
		DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_CODE_EXRD, 1, 0, 1, 0, /*L*/ 1, 0, 1))
		DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_DATA_RDWR, 1, 0, 1, 0, /*L*/ 1, 0, 1))
#undef DEFINE_SEGMENT_DESCRIPTOR
	.Lenterlong_gdt_end = .
	END(enterlong_gdt)
	.align 2
	PRIVATE_OBJECT(enterlong_gdt_pointer)
		.word (.Lenterlong_gdt_end - enterlong_gdt) - 1
		.int  SYM(enterlong_gdt)
	END(enterlong_gdt_pointer)
	.popsection

	/* Load a GDT that can be used for entering long mode. */
	lgdtl  SYM(enterlong_gdt_pointer)

	/* Load 64-bit segment registers. */
	movw   $(0x10), %ax /* DATA */
	movw   %ax, %ds
/*	movw   %ax, %es */ /* Not needed */
/*	movw   %ax, %fs */ /* Not needed */
/*	movw   %ax, %gs */ /* Not needed */
/*	movw   %ax, %ss */ /* Not needed */

	/* And finally, jump into 64-bit mode! */
	ljmpl  $(0x08), $(SYM(_start64))
END(_start)


.code64
.section .text.free
INTERN_FUNCTION(_start64)
	/* Do an absolute jump to get out of physical
	 * memory   and   into  the   virtual  world! */
	movabs $(1f), %rax
	jmpq   *%rax
1:	/* Now we're truly in virtual, 64-bit mode! */

	/* Load the ~real~ 64-bit GDT (from virtual memory) */
	/* Load the initial (boot) GDT. (now that it's been copied) */
	.pushsection .rodata.free
		.align 2
1:		.word  (SEGMENT_COUNT * 8) - 1
		EXTERN(bootcpu_x86_gdt)
		.quad  bootcpu_x86_gdt
	.popsection
	lgdtq  1b

	/* With the new GDT now loaded, load the new segments. */
	movw   $(SEGMENT_USER_DATA64_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   %ax, %fs
	movw   %ax, %gs
	movw   $(SEGMENT_CPU_TSS), %ax
	ltrw   %ax
	movw   $(SEGMENT_CPU_LDT), %ax
	lldtw  %ax

	/* Load %ss and %cs (in pmode we'd use `ljmpl' for this,
	 * but there  is no  `ljmpq', so  we must  use  `iretq') */
	movq   $(__kernel_boottask_stack + KERNEL_STACKSIZE), %rsp
	pushq  $(SEGMENT_KERNEL_DATA0)                       /* ir_ss */
	pushq  $(__kernel_boottask_stack + KERNEL_STACKSIZE) /* ir_rsp */
	pushfq                                               /* ir_rflags */
	pushq  $(SEGMENT_KERNEL_CODE)                        /* ir_cs */
	pushq  $(1f)                                         /* ir_cs */
	iretq
1:

	/* With all cpu registers now  updated to use virtual pointers,  delete
	 * page directory mappings that were used to transition to 64-bit mode. */
	movq   $(0), (__x86_pagedir_kernel_share + 0)
	movq   $(0), (__x86_pagedir_kernel_share + 8)
	movq   $(0), (pagedir_kernel + 0)

	/* HINT: Right now our pagedir looks like this:
	 * [0] ffff808000000000..ffff80ffffffffff --> <recursive page-directory self-mapping>
	 * [1] ffffffff80000000..ffffffffffffffff --> 0000000000000000..000000007fffffff
	 * In  this  picture, we're  currently running  from  [1] (mapped  at -2GiB...0) */


	/* Set the `%gs.base' (`THIS_TASK') register to point to  `&boottask'
	 * Normally we'd just use `wrgsbase' for this, however we haven't yet
	 * determined if that instruction even exists, so for now we have  to
	 * use the associated MSR... */
	movq   $(boottask), %rdx
	movl   %edx, %eax
	shrq   $(32), %rdx
	movl   $(IA32_GS_BASE), %ecx
	wrmsr

	/* Initialize the interrupt handling subsystem. */
	EXTERN(x86_idt_ptr)
	lidtq  x86_idt_ptr

	/* And that's all the assembly-based initialization done!
	 * Now we  just  have  to  invoke  `__i386_kernel_main()' */
	subq   $(SIZEOF_ICPUSTATE), %rsp  /* ics_gpregs */
	movq   %rsp, %rdi
	xorq   %rax, %rax
	movq   $(SIZEOF_ICPUSTATE / 8), %rcx
	rep    stosq

	/* Fill in user-space segments registers (these will be used for /bin/init) */
	movb   $(SEGMENT_USER_DATA_RPL), OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_SS(%rsp)
	movb   $(EFLAGS_IF >> 8),        OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_RFLAGS + 1(%rsp)
	movb   $(SEGMENT_USER_CODE_RPL), OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_CS(%rsp)

	movq   %rsp, %rdi
	EXTERN(__i386_kernel_main)
	call   __i386_kernel_main
	movq   %rax, %rsp

	/* TODO: call x86_kernel_unload_free_and_jump_to_userspace */

	/* Load the initial user-space CPU state. */
	popq   %r15    /* [P] General purpose register #15 */
	popq   %r14    /* [P] General purpose register #14 */
	popq   %r13    /* [P] General purpose register #13 */
	popq   %r12    /* [P] General purpose register #12 */
	popq   %r11    /* [C] General purpose register #11 */
	popq   %r10    /* [C] General purpose register #10 */
	popq   %r9     /* [C] General purpose register #9 */
	popq   %r8     /* [C] General purpose register #8 */
	popq   %rdi    /* [C] Destination pointer */
	popq   %rsi    /* [C] Source pointer */
	popq   %rbp    /* [P] Frame base pointer */
	popq   %rbx    /* [P] Base register */
	popq   %rdx    /* [C] Data register */
	popq   %rcx    /* [C] Count register */
	popq   %rax    /* [C] Accumulator register */
	intr_exit
END(_start64)

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_BOOT__START64_S */
