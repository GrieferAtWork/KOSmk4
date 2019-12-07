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

#ifdef ENTER_HERE
#define L(x) .L##x##2
#else /* ENTER_HERE */
#define L(x) .L##x
#endif /* !ENTER_HERE */


.section .text.cold
#ifdef ENTER_HERE
PUBLIC_FUNCTION(dbg_enter_here)
#else /* ENTER_HERE */
PUBLIC_FUNCTION(dbg)
#endif /* !ENTER_HERE */
	.cfi_startproc
	/* Assume as little as possible about our current CPU state:
	 *   - Assume that %ss and %cs is a valid segment (else: how would we have even gotten here?)
	 *   - Assume that the return instruction pointer is stored at %ss:0(%esp)
	 *   - Assume that paging is either disabled, or that the kernel remains properly
	 *     mapped where we expect it to (else: how would we have even gotten here?)
	 *   - Assume that at least 8 more bytes can be pushed onto the stack at %ss:(%esp)
	 */
	leal   -8(%esp), %esp    /* Allocate 8 bytes. */
	.cfi_adjust_cfa_offset 8
	movl   %eax, %ss:4(%esp) /* Save EAX (using %ss) as base register */
	.cfi_rel_offset %eax, 4
	movl   %ss, %eax
	movl   %eax, %ss:0(%esp) /* Save %ss (using %ss) as base register */
	.cfi_rel_offset %ss, 0
	movl   $(SEGMENT_KERNEL_DATA), %eax
	movl   %eax, %ss         /* Ensure that a valid stack-segment is set */
	nop                      /* Make sure that the stack-segment is applied... */
	popl_cfi %eax            /* Load EAX = SAVED_SS */
	.cfi_register %ss, %eax
	pushfl_cfi_r             /* Save %eflags (while %ss is still valid-flat) */
	cli                      /* Disable interrupts as soon as possible! */
	movl   %eax, %ss         /* Restore the original %ss register */
	nop                      /* Make sure that the stack-segment is applied... */
	/* At this point, both %eax and %eflags have been saved */

#ifndef CONFIG_NO_SMP
	/* Figure out our LAPIC ID so we can try to acquire `dbg_activator_lapic_id',
	 * and check if the debugger was invoked recursively.
	 * Note that during this part, we can only clobber %eax and %eflags!
	 * Also: to prevent problems with CPUs having a LAPIC ID #0, we add +1 to
	 *       the ID, so that 0 is always an indicator for not-in-debugger-mode.
	 * NOTE: When LAPIC is disabled, we can assume that there are no other cores
	 *       that may already be locking debugger mode. */
L(acquire_lapic_lock):
	movl   %ss:x86_lapicbase, %eax
	testl  %eax, %eax
	jz     1f  /* No LAPIC --> We're the only CPU! */
	movl   %ss:APIC_ID(%eax), %eax
	andl   $(APIC_ID_FMASK), %eax
	shrl   $(APIC_ID_FSHIFT), %eax
	movl   %ecx, %ss:dbg_cpu_temporary(,%eax,4)
	leal   1(%eax), %ecx
	xorl   %eax, %eax
	lock;  cmpxchgl %ecx, %ss:dbg_activator_lapic_id
	jz     2f /* First time the debugger is entered. */
	/* Check if this is a recursive entry? */
	cmpl   %eax, %ecx /* PREVIOUS_LAPIC_ID == MY_LAPIC_ID */
	je     2f /* Recursive debugger entry */
	movl   %ss:dbg_cpu_temporary-4(,%ecx,4), %ecx
	/* This is where we get if some other CPU is currently inside the debugger...
	 * At this point, either re-enable interrupts (if they were enabled before),
	 * and hlt to wait for the locking core to exit debugger mode, at which point
	 * it should send an IPI to let us know that our turn has come, or keep on
	 * idling (only using pause) if we're not allowed to turn on interrupts. */
	pause
	testl  $(EFLAGS_IF), %ss:0(%esp)
	jz     L(acquire_lapic_lock) /* Not allowed to block... */
	sti
	hlt
	cli
	jmp    L(acquire_lapic_lock)
2:	movl   %ss:dbg_cpu_temporary-4(,%ecx,4), %ecx
1:
#endif /* !CONFIG_NO_SMP */

	/* We're now in debugger mode! (or at least: we're now holding the debugger mode lock)
	 * At this point, we must check if the caller was already in debugger mode (as is the
	 * case when `dbg_active' is already non-zero), in which case we musn't override the
	 * currently saved `dbg_exitstate' or `dbg_viewstate', but simply re-set the debugger
	 * stack and re-initialize the debugger CPU context, but not change anything about
	 * where to return (this is what happens when the user holds F12 when the debugger
	 * command-line driver is active, allowing them to soft-reset the debugger commandline
	 * in case the current command gets stuck inside of a loop) */
	EXTERN(dbg_active)
	cmpl   $(0), %ss:dbg_active
	jne    L(recursive_debugger)

	/* Save registers */
	movl   %ss:0(%esp), %eax        /* %eflags */
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_EFLAGS
	movl   %ss:4(%esp), %eax        /* %eax */
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EAX
	movl   %edi, %ss:dbg_exitstate+OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDI
	movl   %esi, %ss:dbg_exitstate+OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESI
	movl   %ebp, %ss:dbg_exitstate+OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBP
	leal   12(%esp), %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESP
	movl   %ebx, %ss:dbg_exitstate+OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBX
	movl   %edx, %ss:dbg_exitstate+OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDX
	movl   %ecx, %ss:dbg_exitstate+OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ECX
	movl   %ss:8(%esp), %eax        /* %eip */
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_EIP
	movl   %es, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_ES
	movl   %cs, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_CS
	movl   %ss, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_SS
	movl   %ds, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_DS
	movl   %fs, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_FS
	movl   %gs, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_GS
	movl   $(0), %ss:dbg_exitstate+OFFSET_FCPUSTATE_TR
	strw   %ss:dbg_exitstate+OFFSET_FCPUSTATE_TR
	movl   $(0), %ss:dbg_exitstate+OFFSET_FCPUSTATE_LDT
	sldtw  %ss:dbg_exitstate+OFFSET_FCPUSTATE_LDT
	movl   %cr0, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_COREGS+OFFSET_COREGS_CR0
	movl   %cr2, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_COREGS+OFFSET_COREGS_CR2
	movl   %cr3, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_COREGS+OFFSET_COREGS_CR3
	movl   %cr4, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_COREGS+OFFSET_COREGS_CR4
	movl   %dr0, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR0
	movl   %dr1, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR1
	movl   %dr2, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR2
	movl   %dr3, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR3
	movl   %dr6, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR6
	movl   %dr7, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR7
	sgdtl  %ss:dbg_exitstate+OFFSET_FCPUSTATE_GDT
	sidtl  %ss:dbg_exitstate+OFFSET_FCPUSTATE_IDT

	.cfi_endproc
L(recursive_debugger):
	/* TODO: No CFI function set for this instruction! */
	/* Setup CFI to restore from `dbg_exitstate' */
	movl   $(dbg_exitstate), %esi
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %esi, SIZEOF_FCPUSTATE
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
	/* The debugger was entered recursively!
	 * Reset parts of the debugger control state, and restore the expected
	 * debugger CPU context. */
	movl   $(pagedir_kernel_phys), %eax
	movl   %eax, %cr3
	movl   %cr0, %eax
	orl    $(CR0_PE|CR0_PG), %eax
	andl   $~(CR0_TS|CR0_WP), %eax
	movl   %eax, %cr0

	/* Load the debugger-specific GDT / IDT */
	lgdtl  %ss:dbg_gdt_pointer
	lidtl  %ss:dbg_idt_pointer

	/* Load segment registers. */
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	movw   $(SEGMENT_USER_GSBASE_RPL), %ax
	movw   %ax, %gs
	movw   $(SEGMENT_KERNEL_DATA), %ax
	movw   %ax, %ss
	ljmpl  $(SEGMENT_KERNEL_CODE), $(1f) /* movl $(SEGMENT_KERNEL_CODE), %cs */
1:

	/* x86_debug_gdt[SEGMENT_CPU_TSS].busy = 0; */
	andb   $(0b11111101), x86_debug_gdt+SEGMENT_CPU_TSS+5
	movw   $(SEGMENT_CPU_TSS), %ax
	ltrw   %ax

	movw   $(SEGMENT_CPU_LDT), %ax
	lldtw  %ax

	EXTERN(__kernel_debug_stack)
	movl   $(__kernel_debug_stack + KERNEL_DEBUG_STACKSIZE), %esp
#ifdef ENTER_HERE
	pushl  %edx       /* void *arg */
	pushl  $dbg_exit  /* Return address... */
	pushl  %ecx       /* void (KCALL *main)(void *arg) */
#endif /* ENTER_HERE */

	/* Check if we need to initialize the debugger? */
	cmpl   $(0), dbg_active
	jne    1f
	movl   $(1), dbg_active /* Indicate that the debugger is now active */
	EXTERN(dbg_init)
	call   dbg_init       /* Initialize first time around */
1:

	/* Reset the current debugger state. */
	EXTERN(dbg_reset)
	call   dbg_reset

	/* Enable interrupts while in debugger-mode */
	sti

#ifdef ENTER_HERE
	ret               /* (*main)(arg) --> return to `dbg_exit()' */
#else /* ENTER_HERE */
	pushl  $(1)         /* uintptr_t show_welcome */
	pushl  $dbg_exit  /* Return address... */
	EXTERN(dbg_main)
	jmp    dbg_main
#endif /* !ENTER_HERE */
	.cfi_endproc
#ifdef ENTER_HERE
END(dbg_enter_here)
#else /* ENTER_HERE */
END(dbg)
#endif /* !ENTER_HERE */

#undef ENTER_HERE
#undef L
