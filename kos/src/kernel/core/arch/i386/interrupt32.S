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

#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/pic.h>
#include <kernel/tss.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <kos/kernel/cpu-state.h>
#include <sys/io.h>

#include <libunwind/cfi.h>


/* TODO: This file should be merged with `isr32.S', such that no overlap
 *       between ISR- and fallback interrupt handlers exist. (currently,
 *       some of the interrupt handlers remain linked as part of the kernel,
 *       even though they get overwritten elsewhere)
 * -> This is because we can't use GC to collect the handlers, since LD doesn't
 *    consider placing symbol addresses into memory using linker scripts as valid
 *    use cases of some symbol, and will ~optimize~ away all of our interrupt handlers.
 */


#define INTERRUPT_TYPE_NORMAL 0 /* Normal interrupt */
#define INTERRUPT_TYPE_ERROR  1 /* This interrupt pushes an error code onto the stack. */
#define INTERRUPT_TYPE_SPUR1  2 /* This interrupt may happen spuriously (PIC#1). */
#define INTERRUPT_TYPE_SPUR2  3 /* This interrupt may happen spuriously (PIC#2). */

.macro define_interrupt id, dpl=0, type=INTERRUPT_TYPE_NORMAL
	.weak   x86_cirq_\id
	.hidden x86_cirq_\id
	.global x86_cirq_\id
	.type   x86_cirq_\id, @function
	.weak   x86_asmirq_\id
	.hidden x86_asmirq_\id
	.global x86_asmirq_\id
	.type   x86_asmirq_\id, @function
	.weak   x86_irqdpl_\id
	.hidden x86_irqdpl_\id
	.global x86_irqdpl_\id
x86_irqdpl_\id = \dpl
	.section .text.x86.cirq.\id
x86_cirq_\id:
	.cfi_startproc
.if \type != INTERRUPT_TYPE_ERROR
	movl   $0, %edx
.endif
	pushl_cfi $0x\id
	call   x86_interrupt_generic
	.cfi_adjust_cfa_offset -4
	ret
	.cfi_endproc
.size x86_cirq_\id, . - x86_cirq_\id
	.section .text.x86.asmirq.\id
x86_asmirq_\id:
	.cfi_startproc simple
	.cfi_iret_signal_frame
.if \type == INTERRUPT_TYPE_ERROR
	.cfi_def_cfa %esp, 4 /* Adjust for the error code. */
	popl_cfi %ss:-(12 + SIZEOF_GPREGS + 4)(%esp) /* ECODE */
.else
	.cfi_def_cfa %esp, 0
.endif
	/* Check for spurios interrupts */
.if \type == INTERRUPT_TYPE_SPUR1
	call   x86_check_spurious_interrupt_PIC1
.elseif \type == INTERRUPT_TYPE_SPUR2
	call   x86_check_spurious_interrupt_PIC2
.endif

	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12

	pushal_cfi_r
	/* Load segment registers, as expected in kernel-space */
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
.if \type == INTERRUPT_TYPE_ERROR
	movl   -4(%esp), %edx /* ECODE */
.endif
	movl   %esp, %ecx
	/* Invoke the high-level C-function */
	call   x86_cirq_\id
	movl   %eax, %esp
	/* Start restoring registers. */
	popal_cfi_r

	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds

	iret
	.cfi_endproc
.size x86_asmirq_\id, . - x86_asmirq_\id
#ifndef CONFIG_NO_DEBUGGER
	.weak   x86_debug_asmirq_\id
	.hidden x86_debug_asmirq_\id
	.global x86_debug_asmirq_\id
	.type   x86_debug_asmirq_\id, @function
x86_debug_asmirq_\id = x86_asmirq_\id
#endif /* !CONFIG_NO_DEBUGGER */
.endm




define_interrupt 00                          /* #DE  Divide-by-zero. */
define_interrupt 01                          /* #DB  Debug. */
define_interrupt 02                          /* #NMI Non-maskable Interrupt. */
define_interrupt 03, 3                       /* #BP  Breakpoint. */
define_interrupt 04, 3                       /* #OF  Overflow. */
define_interrupt 05, 3                       /* #BR  Bound Range Exceeded. */
define_interrupt 06                          /* #UD  Invalid Opcode. */
define_interrupt 07                          /* #NM  Device Not Available. */
//define_interrupt 08, 0, INTERRUPT_TYPE_ERROR /* #DF  Double Fault. */
define_interrupt 09
define_interrupt 0a, 0, INTERRUPT_TYPE_ERROR /* #TS  Invalid TSS. */
define_interrupt 0b, 0, INTERRUPT_TYPE_ERROR /* #NP  Segment Not Present. */
define_interrupt 0c, 0, INTERRUPT_TYPE_ERROR /* #SS  Stack-Segment Fault. */
define_interrupt 0d, 0, INTERRUPT_TYPE_ERROR /* #GP  General Protection Fault. */
define_interrupt 0e, 0, INTERRUPT_TYPE_ERROR /* #PF  Page Fault. */
define_interrupt 0f
define_interrupt 10                          /* #MF  x87 Floating-Point Exception. */
define_interrupt 11, 0, INTERRUPT_TYPE_ERROR /* #AC  Alignment Check. */
define_interrupt 12                          /* #MC  Machine Check. */
define_interrupt 13                          /* #XM  SIMD Floating-Point Exception. */
define_interrupt 14                          /* #VE  Virtualization Exception. */
define_interrupt 15
define_interrupt 16
define_interrupt 17
define_interrupt 18
define_interrupt 19
define_interrupt 1a
define_interrupt 1b
define_interrupt 1c
define_interrupt 1d
define_interrupt 1e, 0, INTERRUPT_TYPE_ERROR /* #SX  Security Exception. */
define_interrupt 1f
define_interrupt 20
define_interrupt 21
define_interrupt 22
define_interrupt 23
define_interrupt 24
define_interrupt 25
define_interrupt 26
define_interrupt 27
define_interrupt 28
define_interrupt 29, 3 /* __fastfail() */
define_interrupt 2a
define_interrupt 2b
define_interrupt 2c
define_interrupt 2d
define_interrupt 2e
define_interrupt 2f
define_interrupt 30
define_interrupt 31
define_interrupt 32
define_interrupt 33
define_interrupt 34
define_interrupt 35
define_interrupt 36
define_interrupt 37
define_interrupt 38
define_interrupt 39
define_interrupt 3a
define_interrupt 3b
define_interrupt 3c
define_interrupt 3d
define_interrupt 3e
define_interrupt 3f
define_interrupt 40
define_interrupt 41
define_interrupt 42
define_interrupt 43
define_interrupt 44
define_interrupt 45
define_interrupt 46
define_interrupt 47
define_interrupt 48
define_interrupt 49
define_interrupt 4a
define_interrupt 4b
define_interrupt 4c
define_interrupt 4d
define_interrupt 4e
define_interrupt 4f
define_interrupt 50
define_interrupt 51
define_interrupt 52
define_interrupt 53
define_interrupt 54
define_interrupt 55
define_interrupt 56
define_interrupt 57
define_interrupt 58
define_interrupt 59
define_interrupt 5a
define_interrupt 5b
define_interrupt 5c
define_interrupt 5d
define_interrupt 5e
define_interrupt 5f
define_interrupt 60
define_interrupt 61
define_interrupt 62
define_interrupt 63
define_interrupt 64
define_interrupt 65
define_interrupt 66
define_interrupt 67
define_interrupt 68
define_interrupt 69
define_interrupt 6a
define_interrupt 6b
define_interrupt 6c
define_interrupt 6d
define_interrupt 6e
define_interrupt 6f
define_interrupt 70
define_interrupt 71
define_interrupt 72
define_interrupt 73
define_interrupt 74
define_interrupt 75
define_interrupt 76
define_interrupt 77
define_interrupt 78
define_interrupt 79
define_interrupt 7a
define_interrupt 7b
define_interrupt 7c
define_interrupt 7d
define_interrupt 7e
define_interrupt 7f
define_interrupt 80, 3 /* Syscall */
define_interrupt 81
define_interrupt 82
define_interrupt 83
define_interrupt 84
define_interrupt 85
define_interrupt 86
define_interrupt 87
define_interrupt 88
define_interrupt 89
define_interrupt 8a
define_interrupt 8b
define_interrupt 8c
define_interrupt 8d
define_interrupt 8e
define_interrupt 8f
define_interrupt 90
define_interrupt 91
define_interrupt 92
define_interrupt 93
define_interrupt 94
define_interrupt 95
define_interrupt 96
define_interrupt 97
define_interrupt 98
define_interrupt 99
define_interrupt 9a
define_interrupt 9b
define_interrupt 9c
define_interrupt 9d
define_interrupt 9e
define_interrupt 9f
define_interrupt a0
define_interrupt a1
define_interrupt a2
define_interrupt a3
define_interrupt a4
define_interrupt a5
define_interrupt a6
define_interrupt a7
define_interrupt a8
define_interrupt a9
define_interrupt aa
define_interrupt ab
define_interrupt ac
define_interrupt ad
define_interrupt ae
define_interrupt af
define_interrupt b0
define_interrupt b1
define_interrupt b2
define_interrupt b3
define_interrupt b4
define_interrupt b5
define_interrupt b6
define_interrupt b7
define_interrupt b8
define_interrupt b9
define_interrupt ba
define_interrupt bb
define_interrupt bc
define_interrupt bd
define_interrupt be
define_interrupt bf
define_interrupt c0
define_interrupt c1
define_interrupt c2
define_interrupt c3
define_interrupt c4
define_interrupt c5
define_interrupt c6
define_interrupt c7
define_interrupt c8
define_interrupt c9
define_interrupt ca
define_interrupt cb
define_interrupt cc
define_interrupt cd
define_interrupt ce
define_interrupt cf
define_interrupt d0
define_interrupt d1
define_interrupt d2
define_interrupt d3
define_interrupt d4
define_interrupt d5
define_interrupt d6
define_interrupt d7
define_interrupt d8
define_interrupt d9
define_interrupt da
define_interrupt db
define_interrupt dc
define_interrupt dd
define_interrupt de
define_interrupt df
define_interrupt e0
define_interrupt e1
define_interrupt e2
define_interrupt e3
define_interrupt e4
define_interrupt e5
define_interrupt e6
define_interrupt e7
define_interrupt e8
define_interrupt e9
define_interrupt ea
define_interrupt eb
define_interrupt ec
define_interrupt ed
define_interrupt ee
define_interrupt ef
define_interrupt f0
define_interrupt f1
define_interrupt f2
define_interrupt f3
define_interrupt f4
define_interrupt f5
define_interrupt f6
define_interrupt f7, 0, INTERRUPT_TYPE_SPUR1
define_interrupt f8
define_interrupt f9
define_interrupt fa
define_interrupt fb
define_interrupt fc
define_interrupt fd
define_interrupt fe
define_interrupt ff, 0, INTERRUPT_TYPE_SPUR2






/* Special case: The double-fault handler */
	.hidden x86_irqdpl_08
	.global x86_irqdpl_08
x86_irqdpl_08 = 0
	.hidden x86_asmirq_08
	.global x86_asmirq_08
	.type   x86_asmirq_08, @function
	.section .text.x86.asmirq.08
x86_asmirq_08:
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %ebp, 0
/*[[[deemon
import compileExpression from ......misc.libgen.cfi.compiler;
function restoreRegister(reg, offset) {
	compileExpression('i386', reg, r'
		.cfi_escape $@DW_OP_addr
		.cfi_escape $@__x86_cputss_b0
		.cfi_escape $@__x86_cputss_b1
		.cfi_escape $@__x86_cputss_b2
		.cfi_escape $@__x86_cputss_b3
		plus $@(' + offset + r')
		push %esi
		plus
	', deref_after: true);
}
//restoreRegister('%cr3', 'OFFSET_TSS_CR3');
restoreRegister('%eip', 'OFFSET_TSS_EIP');
restoreRegister('%eflags', 'OFFSET_TSS_EFLAGS');
restoreRegister('%eax', 'OFFSET_TSS_EAX');
restoreRegister('%ecx', 'OFFSET_TSS_ECX');
restoreRegister('%edx', 'OFFSET_TSS_EDX');
restoreRegister('%ebx', 'OFFSET_TSS_EBX');
restoreRegister('%esp', 'OFFSET_TSS_ESP');
restoreRegister('%ebp', 'OFFSET_TSS_EBP');
restoreRegister('%esi', 'OFFSET_TSS_ESI');
restoreRegister('%edi', 'OFFSET_TSS_EDI');
restoreRegister('%es', 'OFFSET_TSS_ES');
restoreRegister('%cs', 'OFFSET_TSS_CS');
restoreRegister('%ss', 'OFFSET_TSS_SS');
restoreRegister('%ds', 'OFFSET_TSS_DS');
restoreRegister('%fs', 'OFFSET_TSS_FS');
restoreRegister('%gs', 'OFFSET_TSS_GS');
restoreRegister('%ldtr', 'OFFSET_TSS_LDTR');
]]]*/
__ASM_L(	.cfi_escape 0x10,0x08,0x09,DW_OP_addr,__x86_cputss_b0,__x86_cputss_b1,__x86_cputss_b2,__x86_cputss_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_TSS_EIP),0x56,0x22)
__ASM_L(	.cfi_escape 0x10,0x09,0x09,DW_OP_addr,__x86_cputss_b0,__x86_cputss_b1,__x86_cputss_b2,__x86_cputss_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_TSS_EFLAGS),0x56,0x22)
__ASM_L(	.cfi_escape 0x10,0x00,0x09,DW_OP_addr,__x86_cputss_b0,__x86_cputss_b1,__x86_cputss_b2,__x86_cputss_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_TSS_EAX),0x56,0x22)
__ASM_L(	.cfi_escape 0x10,0x01,0x09,DW_OP_addr,__x86_cputss_b0,__x86_cputss_b1,__x86_cputss_b2,__x86_cputss_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_TSS_ECX),0x56,0x22)
__ASM_L(	.cfi_escape 0x10,0x02,0x09,DW_OP_addr,__x86_cputss_b0,__x86_cputss_b1,__x86_cputss_b2,__x86_cputss_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_TSS_EDX),0x56,0x22)
__ASM_L(	.cfi_escape 0x10,0x03,0x09,DW_OP_addr,__x86_cputss_b0,__x86_cputss_b1,__x86_cputss_b2,__x86_cputss_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_TSS_EBX),0x56,0x22)
__ASM_L(	.cfi_escape 0x10,0x04,0x09,DW_OP_addr,__x86_cputss_b0,__x86_cputss_b1,__x86_cputss_b2,__x86_cputss_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_TSS_ESP),0x56,0x22)
__ASM_L(	.cfi_escape 0x10,0x05,0x09,DW_OP_addr,__x86_cputss_b0,__x86_cputss_b1,__x86_cputss_b2,__x86_cputss_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_TSS_EBP),0x56,0x22)
__ASM_L(	.cfi_escape 0x10,0x06,0x09,DW_OP_addr,__x86_cputss_b0,__x86_cputss_b1,__x86_cputss_b2,__x86_cputss_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_TSS_ESI),0x56,0x22)
__ASM_L(	.cfi_escape 0x10,0x07,0x09,DW_OP_addr,__x86_cputss_b0,__x86_cputss_b1,__x86_cputss_b2,__x86_cputss_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_TSS_EDI),0x56,0x22)
__ASM_L(	.cfi_escape 0x10,0x28,0x09,DW_OP_addr,__x86_cputss_b0,__x86_cputss_b1,__x86_cputss_b2,__x86_cputss_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_TSS_ES),0x56,0x22)
__ASM_L(	.cfi_escape 0x10,0x29,0x09,DW_OP_addr,__x86_cputss_b0,__x86_cputss_b1,__x86_cputss_b2,__x86_cputss_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_TSS_CS),0x56,0x22)
__ASM_L(	.cfi_escape 0x10,0x2a,0x09,DW_OP_addr,__x86_cputss_b0,__x86_cputss_b1,__x86_cputss_b2,__x86_cputss_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_TSS_SS),0x56,0x22)
__ASM_L(	.cfi_escape 0x10,0x2b,0x09,DW_OP_addr,__x86_cputss_b0,__x86_cputss_b1,__x86_cputss_b2,__x86_cputss_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_TSS_DS),0x56,0x22)
__ASM_L(	.cfi_escape 0x10,0x2c,0x09,DW_OP_addr,__x86_cputss_b0,__x86_cputss_b1,__x86_cputss_b2,__x86_cputss_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_TSS_FS),0x56,0x22)
__ASM_L(	.cfi_escape 0x10,0x2d,0x09,DW_OP_addr,__x86_cputss_b0,__x86_cputss_b1,__x86_cputss_b2,__x86_cputss_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_TSS_GS),0x56,0x22)
__ASM_L(	.cfi_escape 0x10,0x31,0x09,DW_OP_addr,__x86_cputss_b0,__x86_cputss_b1,__x86_cputss_b2,__x86_cputss_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_TSS_LDTR),0x56,0x22)
//[[[end]]]

	/* Our current register state:
	 *   - ESI -- Base address of the current CPU descriptor (THIS_CPU)
	 *   - ESP -- A complete, dedicated stack only for DF exceptions.
	 *   - EBP -- Identical to ESP */

	/* Make sure that our own TSS keep on containing valid values. */
	movl   %esi, x86_cputss_df + OFFSET_TSS_ESI(%esi)
	movl   %esp, x86_cputss_df + OFFSET_TSS_ESP(%esi)
	movl   %ebp, x86_cputss_df + OFFSET_TSS_EBP(%esi)
	movl   $(x86_asmirq_08), x86_cputss_df + OFFSET_TSS_EIP(%esi)

	movl   %ebp, %esp

	pushl  x86_cputss + OFFSET_TSS_EIP(%esi)    /* state->dcs_regs.ucs_eip */
	pushl  x86_cputss + OFFSET_TSS_EFLAGS(%esi) /* state->dcs_regs.ucs_eflags */
	pushl  x86_cputss + OFFSET_TSS_SS(%esi)     /* state->dcs_regs.ucs_ss */
	pushl  x86_cputss + OFFSET_TSS_CS(%esi)     /* state->dcs_regs.ucs_cs */
	pushl  x86_cputss + OFFSET_TSS_DS(%esi)     /* state->dcs_regs.ucs_sgregs.sg_ds */
	pushl  x86_cputss + OFFSET_TSS_ES(%esi)     /* state->dcs_regs.ucs_sgregs.sg_es */
	pushl  x86_cputss + OFFSET_TSS_FS(%esi)     /* state->dcs_regs.ucs_sgregs.sg_fs */
	pushl  x86_cputss + OFFSET_TSS_GS(%esi)     /* state->dcs_regs.ucs_sgregs.sg_gs */
	pushl  x86_cputss + OFFSET_TSS_EAX(%esi)    /* state->dcs_regs.ucs_gpregs.gp_eax */
	pushl  x86_cputss + OFFSET_TSS_ECX(%esi)    /* state->dcs_regs.ucs_gpregs.gp_ecx */
	pushl  x86_cputss + OFFSET_TSS_EDX(%esi)    /* state->dcs_regs.ucs_gpregs.gp_edx */
	pushl  x86_cputss + OFFSET_TSS_EBX(%esi)    /* state->dcs_regs.ucs_gpregs.gp_ebx */
	pushl  x86_cputss + OFFSET_TSS_ESP(%esi)    /* state->dcs_regs.ucs_gpregs.gp_esp */
	pushl  x86_cputss + OFFSET_TSS_EBP(%esi)    /* state->dcs_regs.ucs_gpregs.gp_ebp */
	pushl  x86_cputss + OFFSET_TSS_ESI(%esi)    /* state->dcs_regs.ucs_gpregs.gp_esi */
	pushl  x86_cputss + OFFSET_TSS_EDI(%esi)    /* state->dcs_regs.ucs_gpregs.gp_edi */
	pushl  x86_cputss + OFFSET_TSS_CR3(%esi)    /* state->dcs_cr3 */

#define OFFSET_DF_CPUSTATE_REGS 4

	.cfi_def_cfa %esp, OFFSET_DF_CPUSTATE_REGS+SIZEOF_UCPUSTATE
	.cfi_rel_offset %eip, OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_EIP
	.cfi_rel_offset %eflags, OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_EFLAGS
	.cfi_rel_offset %ss, OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_SS
	.cfi_rel_offset %cs, OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_CS
	.cfi_rel_offset %ds, OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_DS
	.cfi_rel_offset %es, OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_ES
	.cfi_rel_offset %fs, OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_FS
	.cfi_rel_offset %gs, OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_GS
	.cfi_rel_offset %eax, OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EAX
	.cfi_rel_offset %ecx, OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_ECX
	.cfi_rel_offset %edx, OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EDX
	.cfi_rel_offset %ebx, OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EBX
	.cfi_rel_offset %esp, OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_ESP
	.cfi_rel_offset %ebp, OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EBP
	.cfi_rel_offset %esi, OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_ESI
	.cfi_rel_offset %edi, OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EDI

	/* Unwind LTR to allow for recursive DF handling. */
	xorl   %eax, %eax
	movl   %eax, x86_cputss + OFFSET_TSS_LINK(%esi)
	movl   %eax, x86_cputss_df + OFFSET_TSS_LINK(%esi)
	andb   $(0b11111101), x86_cpugdt + SEGMENT_CPU_TSS + 5(%esi)
	andb   $(0b11111101), x86_cpugdt + SEGMENT_CPU_TSS_DF + 5(%esi)
	movw   $(SEGMENT_CPU_TSS), %ax
	ltrw   %ax
	pushfl_cfi
	andl   $(~EFLAGS_NT), 0(%esp)
	popfl_cfi

	/* Invoke the C-level double-fault handler. */
	movl   %esp, %ecx
	INTERN(x86_cirq_08)
	call   x86_cirq_08

	cli
	.cfi_def_cfa_register %eax

	/* Unwind to where the DF handler wants to return. */
	movl   0(%eax), %ecx
	movl   %ecx, %cr3

	testl  $(EFLAGS_VM), OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_EFLAGS(%eax)
	jz     1f
	pushl  OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_GS(%eax) /* ir_es */
	pushl  OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_FS(%eax) /* ir_ds */
	pushl  OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_ES(%eax) /* ir_fs */
	pushl  OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_DS(%eax) /* ir_gs */
	jmp    2f
1:	movw   %cs:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_DS(%eax), %cx
	movw   %cx, %ds
	movw   %cs:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_ES(%eax), %cx
	movw   %cx, %es
	movw   %cs:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_FS(%eax), %cx
	movw   %cx, %fs
	movw   %cs:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_GS(%eax), %cx
	movw   %cx, %gs
	testl  $3, %cs:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_CS(%eax)
	jz     1f
2:	pushl  %cs:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_SS(%eax) /* ir_ss */
	pushl  %cs:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_ESP(%eax) /* ir_esp */
	jmp    3f
1:	movw   %cs:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_SS(%eax), %cx
	movw   %cx, %ss
	movl   %cs:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_ESP(%eax), %esp
3:	pushl  %cs:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_EFLAGS(%eax) /* ir_eflags */
	pushl  %cs:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_CS(%eax)     /* ir_cs */
	pushl  %cs:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_EIP(%eax)    /* ir_eip */

	/* Restore registers from the iret tail from this point forward. */
	.cfi_def_cfa %esp, 0
	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss
	.cfi_restore_iret_es
	.cfi_restore_iret_ds
	.cfi_restore_iret_fs
	.cfi_restore_iret_gs

	/* Restore all of the general-purpose registers. */
	movl   %cs:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EDI(%eax), %edi
	.cfi_same_value %edi
	movl   %cs:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_ESI(%eax), %esi
	.cfi_same_value %esi
	movl   %cs:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EBP(%eax), %ebp
	.cfi_same_value %ebp
	movl   %cs:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EBX(%eax), %ebx
	.cfi_same_value %ebx
	movl   %cs:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EDX(%eax), %edx
	.cfi_same_value %edx
	movl   %cs:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_ECX(%eax), %ecx
	.cfi_same_value %ecx
	movl   %cs:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EAX(%eax), %eax
	.cfi_same_value %eax

	/* Resume execution. */
	iret
	.cfi_endproc
.size x86_asmirq_08, . - x86_asmirq_08



#ifndef CONFIG_NO_DEBUGGER
	.weak   x86_debug_cirq_08
	.hidden x86_debug_cirq_08
	.global x86_debug_cirq_08
	.type   x86_debug_cirq_08, @function
x86_debug_cirq_08 = x86_cirq_08
	.weak   x86_debug_asmirq_08
	.hidden x86_debug_asmirq_08
	.global x86_debug_asmirq_08
	.type   x86_debug_asmirq_08, @function
x86_debug_asmirq_08 = x86_asmirq_08
#endif /* !CONFIG_NO_DEBUGGER */



/* Helper functions: Check for spurious interrupts. */

.section .text
PUBLIC_FUNCTION(x86_check_spurious_interrupt_PIC1)
	/* Check if the interrupt has been spurious
	 * and don't invoke the interrupt if it was */
	.cfi_startproc
	pushl_cfi_r %eax
	/* Check PIC1 */
	movb   $(X86_PIC_READ_ISR), %al
	outb   %al,      $(X86_PIC1_CMD) /* outb(X86_PIC1_CMD,X86_PIC_READ_ISR); */
	inb    $(X86_PIC2_CMD),     %al
	testb  $0x80,               %al
	jz     99f /* if (!(inb(X86_PIC2_CMD) & 0x80)) goto 99f; */
	.cfi_remember_state
	popl_cfi_r %eax
	ret
	.cfi_restore_state
99:	/* Preserve scratch registers. */
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ds
	pushl_cfi_r %es
	pushl_cfi_r %fs
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	movl   %esp, %ecx
	pushl_cfi $98f
	jmp    x86_pic2_spur
	.cfi_endproc
END(x86_check_spurious_interrupt_PIC1)

PUBLIC_FUNCTION(x86_check_spurious_interrupt_PIC2)
	/* Check if the interrupt has been spurious
	 * and don't invoke the interrupt if it was */
	.cfi_startproc
	pushl_cfi_r %eax
	/* Check PIC2 */
	movb   $(X86_PIC_READ_ISR), %al
	outb   %al,      $(X86_PIC2_CMD) /* outb(X86_PIC2_CMD,X86_PIC_READ_ISR); */
	inb    $(X86_PIC2_CMD),     %al
	testb  $0x80,               %al
	jz     99f /* if (!(inb(X86_PIC2_CMD) & 0x80)) goto 2f; */
	.cfi_remember_state
	popl_cfi_r %eax
	ret
	.cfi_restore_state
99:	/* Preserve scratch registers. */
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ds
	pushl_cfi_r %es
	pushl_cfi_r %fs
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	call   x86_pic1_spur
98:
	popl_cfi_r  %fs
	popl_cfi_r  %es
	popl_cfi_r  %ds
	popl_cfi_r  %edx
	popl_cfi_r  %ecx
	popl_cfi_r  %eax
	addl   $4,  %esp
	.cfi_adjust_cfa_offset -4
	iret
	.cfi_endproc
END(x86_check_spurious_interrupt_PIC2)

