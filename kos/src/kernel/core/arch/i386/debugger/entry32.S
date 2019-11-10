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
#include <asm/cpu-flags.h>
#include <asm/cfi.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/paging.h>
#include <kos/kernel/gdt.h>
#include <libunwind/cfi.h>


INTERN(__kernel_debug_stack)

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
	.skip  0x100 * 4
END(dbg_cpu_temporary)
#endif /* !CONFIG_NO_SMP */


.section .text.cold
	/* Define register locations for CFI unwinding (mainly so that GDB unwinding works) */
	INTERN(__x86_dbg_exitstate_temporary_b0)
	INTERN(__x86_dbg_exitstate_temporary_b1)
	INTERN(__x86_dbg_exitstate_temporary_b2)
	INTERN(__x86_dbg_exitstate_temporary_b3)
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %esp, 0
/*[[[deemon
import * from deemon;
import compileExpression from .......misc.libgen.cfi.compiler;
function encodeRegister(reg: string, offset: string) {
	compileExpression('i386', reg, r'
		.cfi_escape $@DW_OP_addr
		.cfi_escape $@__x86_dbg_exitstate_temporary_b0
		.cfi_escape $@__x86_dbg_exitstate_temporary_b1
		.cfi_escape $@__x86_dbg_exitstate_temporary_b2
		.cfi_escape $@__x86_dbg_exitstate_temporary_b3
		plus $@(' + offset + r')
	', deref_after: true);
}
encodeRegister("%edi", "OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDI");
encodeRegister("%esi", "OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESI");
encodeRegister("%ebp", "OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBP");
encodeRegister("%esp", "OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESP");
encodeRegister("%ebx", "OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBX");
encodeRegister("%edx", "OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDX");
encodeRegister("%ecx", "OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ECX");
encodeRegister("%eax", "OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EAX");
encodeRegister("%eflags", "OFFSET_FCPUSTATE_EFLAGS");
encodeRegister("%eip", "OFFSET_FCPUSTATE_EIP");
encodeRegister("%es", "OFFSET_FCPUSTATE_ES");
encodeRegister("%cs", "OFFSET_FCPUSTATE_CS");
encodeRegister("%ss", "OFFSET_FCPUSTATE_SS");
encodeRegister("%ds", "OFFSET_FCPUSTATE_DS");
encodeRegister("%fs", "OFFSET_FCPUSTATE_FS");
encodeRegister("%gs", "OFFSET_FCPUSTATE_GS");
]]]*/
__ASM_L(	.cfi_escape 0x10,0x07,0x07,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDI))
__ASM_L(	.cfi_escape 0x10,0x06,0x07,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESI))
__ASM_L(	.cfi_escape 0x10,0x05,0x07,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBP))
__ASM_L(	.cfi_escape 0x10,0x04,0x07,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESP))
__ASM_L(	.cfi_escape 0x10,0x03,0x07,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBX))
__ASM_L(	.cfi_escape 0x10,0x02,0x07,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDX))
__ASM_L(	.cfi_escape 0x10,0x01,0x07,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ECX))
__ASM_L(	.cfi_escape 0x10,0x00,0x07,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EAX))
__ASM_L(	.cfi_escape 0x10,0x09,0x07,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_FCPUSTATE_EFLAGS))
__ASM_L(	.cfi_escape 0x10,0x08,0x07,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_FCPUSTATE_EIP))
__ASM_L(	.cfi_escape 0x10,0x28,0x07,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_FCPUSTATE_ES))
__ASM_L(	.cfi_escape 0x10,0x29,0x07,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_FCPUSTATE_CS))
__ASM_L(	.cfi_escape 0x10,0x2a,0x07,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_FCPUSTATE_SS))
__ASM_L(	.cfi_escape 0x10,0x2b,0x07,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_FCPUSTATE_DS))
__ASM_L(	.cfi_escape 0x10,0x2c,0x07,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_FCPUSTATE_FS))
__ASM_L(	.cfi_escape 0x10,0x2d,0x07,DW_OP_addr,__x86_dbg_exitstate_temporary_b0,__x86_dbg_exitstate_temporary_b1,__x86_dbg_exitstate_temporary_b2,__x86_dbg_exitstate_temporary_b3)
__ASM_L(	.cfi_escape 0x23,(OFFSET_FCPUSTATE_GS))
//[[[end]]]
	nop    /* For tracebacks */
PUBLIC_FUNCTION(dbg_exit)
	cli
	cmpl   $0, dbg_active
	jne    1f
	int3   /* Assertion failed: Not in debugger mode! */
1:	movl   $(dbg_exitstate), %esi
	.cfi_endproc

	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %esi, 0
	.cfi_rel_offset %edi, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDI
	.cfi_rel_offset %esi, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESI
	.cfi_rel_offset %ebp, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBP
	.cfi_rel_offset %esp, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESP
	.cfi_rel_offset %ebx, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBX
	.cfi_rel_offset %edx, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDX
	.cfi_rel_offset %ecx, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ECX
	.cfi_rel_offset %eax, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EAX
	.cfi_rel_offset %eflags, OFFSET_FCPUSTATE_EFLAGS
	.cfi_rel_offset %eip, OFFSET_FCPUSTATE_EIP
	.cfi_rel_offset %es, OFFSET_FCPUSTATE_ES
	.cfi_rel_offset %cs, OFFSET_FCPUSTATE_CS
	.cfi_rel_offset %ss, OFFSET_FCPUSTATE_SS
	.cfi_rel_offset %ds, OFFSET_FCPUSTATE_DS
	.cfi_rel_offset %fs, OFFSET_FCPUSTATE_FS
	.cfi_rel_offset %gs, OFFSET_FCPUSTATE_GS

	INTERN(__kernel_debug_stack)
	movl   $(__kernel_debug_stack + KERNEL_DEBUG_STACKSIZE), %esp

	/* Finalize debugger mode. */
	INTERN(dbg_fini)
	call   dbg_fini

	/* Copy `dbg_exitstate' */
#ifndef CONFIG_NO_SMP
	INTERN(debug_mycpu)
	movl   debug_mycpu, %edi
	INTERN(_this_idle_x86_this_kernel_sp0)
	movl   _this_idle_x86_this_kernel_sp0(%edi), %edi
	addl   $(SIZEOF_IRREGS_VM86), %edi /* Worst-cast stack requirement for IRET */
	movl   $(SIZEOF_FCPUSTATE/4), %ecx
	rep;   movsl   /* Copy the exit-state to the end of the calling CPU's IDLE-thread's stack */
	.cfi_def_cfa %edi, -SIZEOF_FCPUSTATE
#endif /* !CONFIG_NO_SMP */

	/* Indicate that debugger mode has ended. */
	movl   $0, dbg_active
	movl   $0, dbg_activator_lapic_id
#ifndef CONFIG_NO_SMP
	INTERN(dbg_wake_other_cpus)
	call   dbg_wake_other_cpus
#endif /* !CONFIG_NO_SMP */

#ifdef CONFIG_NO_SMP
#define EXIT_STATE(offset) dbg_exitstate+offset
#else /* CONFIG_NO_SMP */
#define EXIT_STATE(offset) ((-SIZEOF_FCPUSTATE)+offset)(%edi)
#endif /* !CONFIG_NO_SMP */

	/* Restore descriptor table registers */
	lidtl  EXIT_STATE(OFFSET_FCPUSTATE_IDT)
	lgdtl  EXIT_STATE(OFFSET_FCPUSTATE_GDT)

	/* Restore debug registers */
	movl   EXIT_STATE(OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR7), %eax
	movl   %eax, %dr7
	movl   EXIT_STATE(OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR6), %eax
	movl   %eax, %dr6
	movl   EXIT_STATE(OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR3), %eax
	movl   %eax, %dr3
	movl   EXIT_STATE(OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR2), %eax
	movl   %eax, %dr2
	movl   EXIT_STATE(OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR1), %eax
	movl   %eax, %dr1
	movl   EXIT_STATE(OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR0), %eax
	movl   %eax, %dr0

	/* Restore control registers */
	movl   EXIT_STATE(OFFSET_FCPUSTATE_COREGS+OFFSET_COREGS_CR4), %eax
	movl   %eax, %cr4
	movl   EXIT_STATE(OFFSET_FCPUSTATE_COREGS+OFFSET_COREGS_CR3), %eax
	movl   %eax, %cr3
	movl   EXIT_STATE(OFFSET_FCPUSTATE_COREGS+OFFSET_COREGS_CR2), %eax
	movl   %eax, %cr2
	movl   EXIT_STATE(OFFSET_FCPUSTATE_COREGS+OFFSET_COREGS_CR0), %eax
	movl   %eax, %cr0

	/* Restore the LDT and TR registers */
	lldt   EXIT_STATE(OFFSET_FCPUSTATE_LDT)
	movzwl EXIT_STATE(OFFSET_FCPUSTATE_TR), %eax
	movl   %eax, %edx
	andl   $~0x7, %edx
	movl   EXIT_STATE(OFFSET_FCPUSTATE_GDT+OFFSET_DESCTAB_BASE), %ecx
	andb   $0b11111101, 5(%ecx,%edx,1)
	ltr    %ax

	/* Restore gp. registers */
#ifdef CONFIG_NO_SMP
	movl   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDI), %edi
#endif /* CONFIG_NO_SMP */
	movl   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESI), %esi
	movl   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBP), %ebp
	movl   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBX), %ebx
	movl   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDX), %edx
	movl   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ECX), %ecx

	/* Check if we're about to return to VM86 */
	testl  $EFLAGS_VM, EXIT_STATE(OFFSET_FCPUSTATE_EFLAGS)
	jz     1f
	pushl  EXIT_STATE(OFFSET_FCPUSTATE_GS)
	pushl  EXIT_STATE(OFFSET_FCPUSTATE_FS)
	pushl  EXIT_STATE(OFFSET_FCPUSTATE_DS)
	pushl  EXIT_STATE(OFFSET_FCPUSTATE_ES)
	pushl  EXIT_STATE(OFFSET_FCPUSTATE_SS)
	pushl  EXIT_STATE(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESP)
	pushl  EXIT_STATE(OFFSET_FCPUSTATE_EFLAGS)
	pushl  EXIT_STATE(OFFSET_FCPUSTATE_CS)
	pushl  EXIT_STATE(OFFSET_FCPUSTATE_EIP)
	movl   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EAX), %eax
#ifndef CONFIG_NO_SMP
	movl   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDI), %edi
#endif /* !CONFIG_NO_SMP */
	iret
1:	/* Restore segment registers. */
	movw   EXIT_STATE(OFFSET_FCPUSTATE_GS), %ax
	movw   %ax, %gs
	movw   EXIT_STATE(OFFSET_FCPUSTATE_FS), %ax
	movw   %ax, %fs
	movw   EXIT_STATE(OFFSET_FCPUSTATE_DS), %ax
	movw   %ax, %ds
	movw   EXIT_STATE(OFFSET_FCPUSTATE_ES), %ax
	movw   %ax, %es

	movl   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EAX), %eax
	/* Check if we're about to return to user-space */
	testl  $3, EXIT_STATE(OFFSET_FCPUSTATE_CS)
	jz     1f
	pushl  EXIT_STATE(OFFSET_FCPUSTATE_SS)
	pushl  EXIT_STATE(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESP)
	pushl  EXIT_STATE(OFFSET_FCPUSTATE_EFLAGS)
	pushl  EXIT_STATE(OFFSET_FCPUSTATE_CS)
	pushl  EXIT_STATE(OFFSET_FCPUSTATE_EIP)
#ifndef CONFIG_NO_SMP
	movl   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDI), %edi
#endif /* !CONFIG_NO_SMP */
	iret
1:	/* Return to kernel-space (in this scenario, we need to assume a valid destination SP) */
	movw   EXIT_STATE(OFFSET_FCPUSTATE_SS), %ss
	movl   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESP), %esp
	pushl  EXIT_STATE(OFFSET_FCPUSTATE_EFLAGS)
	pushl  EXIT_STATE(OFFSET_FCPUSTATE_CS)
	pushl  EXIT_STATE(OFFSET_FCPUSTATE_EIP)
#ifndef CONFIG_NO_SMP
	movl   EXIT_STATE(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDI), %edi
#endif /* !CONFIG_NO_SMP */
	iret
	.cfi_endproc
END(dbg_exit)


#define ENTER_HERE 1
#include "entry32-enter-here.S.inl"
#include "entry32-enter-here.S.inl"

#define ENTER_AT_FCPUSTATE 1
#include "entry32-enter-at.S.inl"
#define ENTER_AT_UCPUSTATE 1
#include "entry32-enter-at.S.inl"
#define ENTER_AT_LCPUSTATE 1
#include "entry32-enter-at.S.inl"
#define ENTER_AT_KCPUSTATE 1
#include "entry32-enter-at.S.inl"
#define ENTER_AT_ICPUSTATE 1
#include "entry32-enter-at.S.inl"
#define ENTER_AT_SCPUSTATE 1
#include "entry32-enter-at.S.inl"



#endif /* !CONFIG_NO_DEBUGGER */
