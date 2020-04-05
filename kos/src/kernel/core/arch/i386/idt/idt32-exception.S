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
#ifdef __INTELLISENSE__
#include "idt32.S"
#define IDT_VECTOR 0e
#endif /* __INTELLISENSE__ */


#if IDT_CONFIG_GETDPL(IDT_VECTOR_ID) == 3
IDT_HANDLER_SETDPL(3)
#endif /* IDT_CONFIG_GETDPL(IDT_VECTOR_ID) == 3 */

IDT_HANDLER_BEGIN
	.cfi_startproc simple
#if IDT_VECTOR_ID == 0x08 || defined(__DEEMON__)
	/* Double Fault */
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
	movl   %esi, thiscpu_x86_tssdf + OFFSET_TSS_ESI(%esi)
	movl   %esp, thiscpu_x86_tssdf + OFFSET_TSS_ESP(%esi)
	movl   %ebp, thiscpu_x86_tssdf + OFFSET_TSS_EBP(%esi)
	movl   $(PP_CAT2(x86_idt_, IDT_VECTOR_NAME)), thiscpu_x86_tssdf + OFFSET_TSS_EIP(%esi)

	movl   %ebp, %esp

	PUBLIC(thiscpu_x86_tss)
	pushl  thiscpu_x86_tss + OFFSET_TSS_EIP(%esi)    /* state->dcs_regs.ucs_eip */
	pushl  thiscpu_x86_tss + OFFSET_TSS_EFLAGS(%esi) /* state->dcs_regs.ucs_eflags */
	pushl  thiscpu_x86_tss + OFFSET_TSS_SS(%esi)     /* state->dcs_regs.ucs_ss */
	pushl  thiscpu_x86_tss + OFFSET_TSS_CS(%esi)     /* state->dcs_regs.ucs_cs */
	pushl  thiscpu_x86_tss + OFFSET_TSS_DS(%esi)     /* state->dcs_regs.ucs_sgregs.sg_ds */
	pushl  thiscpu_x86_tss + OFFSET_TSS_ES(%esi)     /* state->dcs_regs.ucs_sgregs.sg_es */
	pushl  thiscpu_x86_tss + OFFSET_TSS_FS(%esi)     /* state->dcs_regs.ucs_sgregs.sg_fs */
	pushl  thiscpu_x86_tss + OFFSET_TSS_GS(%esi)     /* state->dcs_regs.ucs_sgregs.sg_gs */
	pushl  thiscpu_x86_tss + OFFSET_TSS_EAX(%esi)    /* state->dcs_regs.ucs_gpregs.gp_eax */
	pushl  thiscpu_x86_tss + OFFSET_TSS_ECX(%esi)    /* state->dcs_regs.ucs_gpregs.gp_ecx */
	pushl  thiscpu_x86_tss + OFFSET_TSS_EDX(%esi)    /* state->dcs_regs.ucs_gpregs.gp_edx */
	pushl  thiscpu_x86_tss + OFFSET_TSS_EBX(%esi)    /* state->dcs_regs.ucs_gpregs.gp_ebx */
	pushl  thiscpu_x86_tss + OFFSET_TSS_ESP(%esi)    /* state->dcs_regs.ucs_gpregs.gp_esp */
	pushl  thiscpu_x86_tss + OFFSET_TSS_EBP(%esi)    /* state->dcs_regs.ucs_gpregs.gp_ebp */
	pushl  thiscpu_x86_tss + OFFSET_TSS_ESI(%esi)    /* state->dcs_regs.ucs_gpregs.gp_esi */
	pushl  thiscpu_x86_tss + OFFSET_TSS_EDI(%esi)    /* state->dcs_regs.ucs_gpregs.gp_edi */
	pushl  thiscpu_x86_tss + OFFSET_TSS_CR3(%esi)    /* state->dcs_cr3 */

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
	movl   %eax, thiscpu_x86_tss + OFFSET_TSS_LINK(%esi)
	movl   %eax, thiscpu_x86_tssdf + OFFSET_TSS_LINK(%esi)
	andb   $(0b11111101), thiscpu_x86_gdt + SEGMENT_CPU_TSS + 5(%esi)
	andb   $(0b11111101), thiscpu_x86_gdt + SEGMENT_CPU_TSS_DF + 5(%esi)
	movw   $(SEGMENT_CPU_TSS), %ax
	ltrw   %ax
	pushfl_cfi
	andl   $(~EFLAGS_NT), 0(%esp)
	popfl_cfi

	/* Invoke the C-level double-fault handler. */
	movl   %esp, %ecx
	EXTERN(PP_CAT2(x86_handle_, IDT_VECTOR_NAME))
	call   PP_CAT2(x86_handle_, IDT_VECTOR_NAME)

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
1:	movw   %ss:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_DS(%eax), %cx
	movw   %cx, %ds
	movw   %ss:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_ES(%eax), %cx
	movw   %cx, %es
	movw   %ss:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_FS(%eax), %cx
	movw   %cx, %fs
	movw   %ss:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_GS(%eax), %cx
	movw   %cx, %gs
	testl  $(3), %ss:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_CS(%eax)
	jz     1f
2:	pushl  %ss:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_SS(%eax) /* ir_ss */
	pushl  %ss:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_ESP(%eax) /* ir_esp */
	jmp    3f
1:	movw   %ss:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_SS(%eax), %cx
	movw   %cx, %ss
	movl   %ss:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_ESP(%eax), %esp
3:	pushl  %ss:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_EFLAGS(%eax) /* ir_eflags */
	pushl  %ss:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_CS(%eax)     /* ir_cs */
	pushl  %ss:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_EIP(%eax)    /* ir_eip */

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
	movl   %ss:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EDI(%eax), %edi
	.cfi_same_value %edi
	movl   %ss:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_ESI(%eax), %esi
	.cfi_same_value %esi
	movl   %ss:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EBP(%eax), %ebp
	.cfi_same_value %ebp
	movl   %ss:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EBX(%eax), %ebx
	.cfi_same_value %ebx
	movl   %ss:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EDX(%eax), %edx
	.cfi_same_value %edx
	movl   %ss:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_ECX(%eax), %ecx
	.cfi_same_value %ecx
	movl   %ss:OFFSET_DF_CPUSTATE_REGS+OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EAX(%eax), %eax
	.cfi_same_value %eax

	/* Resume execution. */
	iret
#undef OFFSET_DF_CPUSTATE_REGS
#else /* IDT_VECTOR_ID == 0x08 */
	.cfi_iret_signal_frame
#if IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID)
	.cfi_def_cfa %esp, 4 /* Adjust for the error code. */
	popl_cfi %ss:-(12 + SIZEOF_GPREGS + 4)(%esp) /* ECODE */
#else /* IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID) */
	.cfi_def_cfa %esp, 0
#endif /* !IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID) */

	/* Encode instructions as explicit bytes so it's clear that the
	 * following sequence of instructions is exactly 5 bytes long.
	 * This is important for code that injects interrupt redirection,
	 * which requires exactly 5 bytes of instructions (E9h, DISP32) */
	.byte 0x1e /* pushl %ds */
	.cfi_adjust_cfa_offset 4
	.cfi_restore_iret_ds_or_offset -4

	.byte 0x06 /* pushl %es */
	.cfi_adjust_cfa_offset 4
	.cfi_restore_iret_es_or_offset -8

	.byte 0x0f, 0xa0 /* pushl %fs */
	.cfi_adjust_cfa_offset 4
	.cfi_restore_iret_fs_or_offset -12

	.byte 0x60 /* pushal */
	.cfi_adjust_cfa_offset 32
	.cfi_rel_offset %edi, 0
	.cfi_rel_offset %esi, 4
	.cfi_rel_offset %ebp, 8
	.cfi_rel_offset %esp, 12
	.cfi_rel_offset %ebx, 16
	.cfi_rel_offset %edx, 20
	.cfi_rel_offset %ecx, 24
	.cfi_rel_offset %eax, 28


	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs

	movl   %esp, %ecx     /* struct icpustate *state */
#if IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID)
	movl   -4(%esp), %edx /* uintptr_t ecode */
#endif /* IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID) */

	EXTERN(PP_CAT2(x86_handle_, IDT_VECTOR_NAME))
	call   PP_CAT2(x86_handle_, IDT_VECTOR_NAME)

	popal_cfi_r
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
#endif /* IDT_VECTOR_ID != 0x08 */
	.cfi_endproc
IDT_HANDLER_END


_idt_set_impl_section cirq, IDT_VECTOR_NAME
.weak PP_CAT2(x86_handle_, IDT_VECTOR_NAME)
INTERN_FUNCTION(PP_CAT2(x86_handle_, IDT_VECTOR_NAME))
	.cfi_startproc
#if !IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID)
	xorl   %edx, %edx /* uintptr_t ecode */
#endif /* IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID) */
	pushl_cfi $(IDT_VECTOR_ID) /* uintptr_t vecno */
	EXTERN(x86_handle_unhandled_idt)
	call   x86_handle_unhandled_idt
	.cfi_adjust_cfa_offset -4
	ret
	.cfi_endproc
END(PP_CAT2(x86_handle_, IDT_VECTOR_NAME))

#undef IDT_VECTOR
