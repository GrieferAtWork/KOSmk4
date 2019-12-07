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

#include <kernel/debugger.h>

#ifndef CONFIG_NO_DEBUGGER
#include <kernel/compiler.h>

#include <kernel/apic.h>
#include <kernel/idt.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/fsgsbase.h>
#include <asm/instr/kgsbase.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/gdt.h>
#include <kos/kernel/paging.h>

#include <libunwind/cfi.h>


EXTERN(__kernel_debug_stack)

.section .rodata.cold
PRIVATE_OBJECT(dbg_gdt_pointer)
	.word  (SEGMENT_COUNT * SIZEOF_SEGMENT_DESCRIPTOR) - 1
	PUBLIC(x86_debug_gdt)
	.long  x86_debug_gdt
END(dbg_gdt_pointer)

.section .rodata.cold
PRIVATE_OBJECT(dbg_idt_pointer)
	.word  (256 * SIZEOF_IDT_SEGMENT) - 1
	PUBLIC(x86_dbgidt)
	.long  x86_dbgidt
END(dbg_idt_pointer)

#ifndef CONFIG_NO_SMP
.section .bss.cold
PRIVATE_OBJECT(dbg_activator_lapic_id)
	.long  0
END(dbg_activator_lapic_id)

.section .bss.cold
INTERN_OBJECT(dbg_cpu_temporary)
	.skip  0x100 * 8
END(dbg_cpu_temporary)
#endif /* !CONFIG_NO_SMP */


.section .text.cold
	/* Define register locations for CFI unwinding (mainly so that GDB unwinding works) */
	EXTERN(__x86_dbg_exitstate_temporary_b0)
	EXTERN(__x86_dbg_exitstate_temporary_b1)
	EXTERN(__x86_dbg_exitstate_temporary_b2)
	EXTERN(__x86_dbg_exitstate_temporary_b3)
	EXTERN(__x86_dbg_exitstate_temporary_b4)
	EXTERN(__x86_dbg_exitstate_temporary_b5)
	EXTERN(__x86_dbg_exitstate_temporary_b6)
	EXTERN(__x86_dbg_exitstate_temporary_b7)
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %rsp, 0
/*[[[deemon
import * from deemon;
import compileExpression from .......misc.libgen.cfi.compiler;
function encodeRegister(reg: string, offset: string) {
	compileExpression('x86_64', reg, r'
		.cfi_escape $@DW_OP_addr
		.cfi_escape $@__x86_dbg_exitstate_temporary_b0
		.cfi_escape $@__x86_dbg_exitstate_temporary_b1
		.cfi_escape $@__x86_dbg_exitstate_temporary_b2
		.cfi_escape $@__x86_dbg_exitstate_temporary_b3
		.cfi_escape $@__x86_dbg_exitstate_temporary_b4
		.cfi_escape $@__x86_dbg_exitstate_temporary_b5
		.cfi_escape $@__x86_dbg_exitstate_temporary_b6
		.cfi_escape $@__x86_dbg_exitstate_temporary_b7
		plus $@(' + offset + r')
	', deref_after: true);
}
for (local i: [8:15+1])
	encodeRegister("%r" + i, "OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R" + i);
encodeRegister("%rdi", "OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RDI");
encodeRegister("%rsi", "OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RSI");
encodeRegister("%rbp", "OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RBP");
encodeRegister("%rsp", "OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RSP");
encodeRegister("%rbx", "OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RBX");
encodeRegister("%rdx", "OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RDX");
encodeRegister("%rcx", "OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RCX");
encodeRegister("%rax", "OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RAX");
encodeRegister("%rflags", "OFFSET_FCPUSTATE_RFLAGS");
encodeRegister("%rip", "OFFSET_FCPUSTATE_RIP");
encodeRegister("%es", "OFFSET_FCPUSTATE_ES");
encodeRegister("%cs", "OFFSET_FCPUSTATE_CS");
encodeRegister("%ss", "OFFSET_FCPUSTATE_SS");
encodeRegister("%ds", "OFFSET_FCPUSTATE_DS");
encodeRegister("%fs", "OFFSET_FCPUSTATE_FS");
encodeRegister("%gs", "OFFSET_FCPUSTATE_GS");
]]]*/
__ASM_L(	.cfi_escape 0x10,0x08,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R8))
__ASM_L(	.cfi_escape 0x10,0x09,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R9))
__ASM_L(	.cfi_escape 0x10,0x0a,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R10))
__ASM_L(	.cfi_escape 0x10,0x0b,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R11))
__ASM_L(	.cfi_escape 0x10,0x0c,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R12))
__ASM_L(	.cfi_escape 0x10,0x0d,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R13))
__ASM_L(	.cfi_escape 0x10,0x0e,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R14))
__ASM_L(	.cfi_escape 0x10,0x0f,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R15))
__ASM_L(	.cfi_escape 0x10,0x05,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RDI))
__ASM_L(	.cfi_escape 0x10,0x04,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RSI))
__ASM_L(	.cfi_escape 0x10,0x06,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RBP))
__ASM_L(	.cfi_escape 0x10,0x07,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RSP))
__ASM_L(	.cfi_escape 0x10,0x03,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RBX))
__ASM_L(	.cfi_escape 0x10,0x01,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RDX))
__ASM_L(	.cfi_escape 0x10,0x02,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RCX))
__ASM_L(	.cfi_escape 0x10,0x00,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RAX))
__ASM_L(	.cfi_escape 0x10,0x31,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_RFLAGS))
__ASM_L(	.cfi_escape 0x10,0x10,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_RIP))
__ASM_L(	.cfi_escape 0x10,0x32,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_ES))
__ASM_L(	.cfi_escape 0x10,0x33,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_CS))
__ASM_L(	.cfi_escape 0x10,0x34,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_SS))
__ASM_L(	.cfi_escape 0x10,0x35,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_DS))
__ASM_L(	.cfi_escape 0x10,0x36,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_FS))
__ASM_L(	.cfi_escape 0x10,0x37,0x0b,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape __x86_dbg_exitstate_temporary_b4,__x86_dbg_exitstate_temporary_b5,__x86_dbg_exitstate_temporary_b6,__x86_dbg_exitstate_temporary_b7,0x23,(OFFSET_FCPUSTATE_GS))
//[[[end]]]
	nop    /* For tracebacks */
PUBLIC_FUNCTION(dbg_exit)
	cli
	cmpl   $(0), dbg_active
	jne    1f
	int3   /* Assertion failed: Not in debugger mode! */
1:	movq   $(dbg_exitstate), %rbx
	.cfi_endproc

	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %rbx, 0
	ASM_CFI_REL_OFFSET_RESTORE_FCPUSTATE(0)

	EXTERN(__kernel_debug_stack)
	movq   $(__kernel_debug_stack + KERNEL_DEBUG_STACKSIZE), %rsp

	/* Finalize debugger mode. */
	EXTERN(dbg_fini)
	call   dbg_fini

	/* Copy `dbg_exitstate' */
#ifndef CONFIG_NO_SMP
	EXTERN(debug_mycpu)
	movq   debug_mycpu, %rdi
	EXTERN(this_idle_x86_kernel_psp0)
	movq   this_idle_x86_kernel_psp0(%rdi), %rdi
	subq   $(SIZEOF_IRREGS), %rdi /* Worst-cast stack requirement for IRET */
	movq   $(SIZEOF_FCPUSTATE / 8), %rcx
	rep;   movsq   /* Copy the exit-state to the end of the calling CPU's IDLE-thread's stack */
	.cfi_def_cfa %rdi, -SIZEOF_FCPUSTATE
#endif /* !CONFIG_NO_SMP */

	/* Indicate that debugger mode has ended. */
	EXTERN(dbg_active)
	movl   $(0), dbg_active
	EXTERN(dbg_activator_lapic_id)
	movl   $(0), dbg_activator_lapic_id
#ifndef CONFIG_NO_SMP
	EXTERN(dbg_wake_other_cpus)
	call   dbg_wake_other_cpus
#endif /* !CONFIG_NO_SMP */

#ifdef CONFIG_NO_SMP
#define EXIT_STATE(offset) dbg_exitstate + offset
#else /* CONFIG_NO_SMP */
#define EXIT_STATE(offset) ((-SIZEOF_FCPUSTATE) + offset)(%rdi)
#endif /* !CONFIG_NO_SMP */

	/* Restore descriptor table registers */
	lidtq  EXIT_STATE(OFFSET_FCPUSTATE_IDT)
	lgdtq  EXIT_STATE(OFFSET_FCPUSTATE_GDT)

	/* Restore debug registers */
	movq   EXIT_STATE(OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR7), %rax
	movq   %rax, %dr7
	movq   EXIT_STATE(OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR6), %rax
	movq   %rax, %dr6
	movq   EXIT_STATE(OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR3), %rax
	movq   %rax, %dr3
	movq   EXIT_STATE(OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR2), %rax
	movq   %rax, %dr2
	movq   EXIT_STATE(OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR1), %rax
	movq   %rax, %dr1
	movq   EXIT_STATE(OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR0), %rax
	movq   %rax, %dr0

	/* Restore control registers */
	movq   EXIT_STATE(OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR4), %rax
	movq   %rax, %cr4
	movq   EXIT_STATE(OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR3), %rax
	movq   %rax, %cr3
	movq   EXIT_STATE(OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR2), %rax
	movq   %rax, %cr2
	movq   EXIT_STATE(OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR0), %rax
	movq   %rax, %cr0

	/* Restore the LDT and TR registers */
	lldtw  EXIT_STATE(OFFSET_FCPUSTATE_LDT)
	movzwq EXIT_STATE(OFFSET_FCPUSTATE_TR), %rax
	movq   %rax, %rdx
	andq   $(~0x7), %rdx
	movq   EXIT_STATE(OFFSET_FCPUSTATE_GDT + OFFSET_DESCTAB_BASE), %rcx
	andb   $(0b11111101), 5(%rcx,%rdx,1)
	ltrw   %ax

	/* Restore segment registers. */
	movw   EXIT_STATE(OFFSET_FCPUSTATE_GS), %ax
	movw   %ax, %gs
	movw   EXIT_STATE(OFFSET_FCPUSTATE_FS), %ax
	movw   %ax, %fs
	movw   EXIT_STATE(OFFSET_FCPUSTATE_DS), %ax
	movw   %ax, %ds
	movw   EXIT_STATE(OFFSET_FCPUSTATE_ES), %ax
	movw   %ax, %es

	/* Restore segment base values. */
	movq   EXIT_STATE(OFFSET_FCPUSTATE_SGBASE + OFFSET_SGBASE_FSBASE), %rax
	wrfsbaseq %rax
	wrkgsbaseq EXIT_STATE(OFFSET_FCPUSTATE_SGBASE + OFFSET_SGBASE_GSBASE)

	/* Load the proper value for the current %gs.base */
#ifdef CONFIG_NO_SMP
	EXTERN(debug_mycpu)
	movq   debug_mycpu, %rax
	EXTERN(thiscpu_current)
	movq   thiscpu_current(%rax), %rax
#else /* CONFIG_NO_SMP */
	movq   thiscpu_current, %rax
#endif /* !CONFIG_NO_SMP */
	wrgsbaseq %rax

	/* Restore gp. registers */
	movq   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R15), %r15
	movq   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R14), %r14
	movq   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R13), %r13
	movq   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R12), %r12
	movq   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R11), %r11
	movq   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R10), %r10
	movq   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R9), %r9
	movq   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R8), %r8
#ifdef CONFIG_NO_SMP
	movq   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RDI), %rdi
#endif /* CONFIG_NO_SMP */
	movq   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RSI), %rsi
	movq   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RBP), %rbp
	movq   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RBX), %rbx
	movq   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RDX), %rdx
	movq   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RCX), %rcx
	movq   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RAX), %rax
	pushq  EXIT_STATE(OFFSET_FCPUSTATE_SS)
	pushq  EXIT_STATE(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RSP)
	pushq  EXIT_STATE(OFFSET_FCPUSTATE_RFLAGS)
	pushq  EXIT_STATE(OFFSET_FCPUSTATE_CS)
	pushq  EXIT_STATE(OFFSET_FCPUSTATE_RIP)
#ifndef CONFIG_NO_SMP
	movq   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RDI), %rdi
#endif /* !CONFIG_NO_SMP */
	intr_exit
	.cfi_endproc
END(dbg_exit)


#define ENTER_HERE 1
#include "entry64-enter-here.S.inl"
#include "entry64-enter-here.S.inl"

//TODO:#define ENTER_AT_FCPUSTATE 1
//TODO:#include "entry64-enter-at.S.inl"
//TODO:#define ENTER_AT_UCPUSTATE 1
//TODO:#include "entry64-enter-at.S.inl"
//TODO:#define ENTER_AT_LCPUSTATE 1
//TODO:#include "entry64-enter-at.S.inl"
//TODO:#define ENTER_AT_KCPUSTATE 1
//TODO:#include "entry64-enter-at.S.inl"
//TODO:#define ENTER_AT_ICPUSTATE 1
//TODO:#include "entry64-enter-at.S.inl"
//TODO:#define ENTER_AT_SCPUSTATE 1
//TODO:#include "entry64-enter-at.S.inl"



#endif /* !CONFIG_NO_DEBUGGER */
