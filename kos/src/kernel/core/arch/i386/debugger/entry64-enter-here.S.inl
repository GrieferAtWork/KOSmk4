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

#include <asm/cfi.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>

.section .text.cold
#ifdef ENTER_HERE
PUBLIC_FUNCTION(dbg_enter_here)
#else /* ENTER_HERE */
PUBLIC_FUNCTION(dbg)
#endif /* !ENTER_HERE */
	.cfi_startproc
	/* Assume as little as possible about our current CPU state:
	 *   - Assume that %ss and %cs is a valid segment (else: how would we have even gotten here?)
	 *   - Assume that the return instruction pointer is stored at 0(%rsp)
	 *   - Assume that paging is either disabled, or that the kernel remains properly
	 *     mapped where we expect it to (else: how would we have even gotten here?)
	 *   - Assume that at least 16 more bytes can be pushed onto the stack at (%rsp)
	 */
	pushq_cfi_r %rax /* Save EAX */
	pushfq_cfi_r     /* Save %rflags */
	cli              /* Disable interrupts as soon as possible! */
	/* At this point, both %eax and %rflags have been saved */

#ifndef CONFIG_NO_SMP
	/* Figure out our LAPIC ID so we can try to acquire `dbg_activator_lapic_id',
	 * and check if the debugger was invoked recursively.
	 * Note that during this part, we can only clobber %eax and %rflags!
	 * Also: to prevent problems with CPUs having a LAPIC ID #0, we add +1 to
	 *       the ID, so that 0 is always an indicator for not-in-debugger-mode.
	 * NOTE: When LAPIC is disabled, we can assume that there are no other cores
	 *       that may already be locking debugger mode. */
L(acquire_lapic_lock):
	movq   x86_lapicbase, %rax
	testq  %rax, %rax
	jz     1f  /* No LAPIC --> We're the only CPU! */
	movzlq APIC_ID(%rax), %rax
	andq   $(APIC_ID_FMASK), %rax
	shrq   $(APIC_ID_FSHIFT), %rax
	movq   %rcx, dbg_cpu_temporary(,%rax,8)
	leaq   1(%rax), %rcx
	xorl   %eax, %eax
	lock;  cmpxchgl %ecx, dbg_activator_lapic_id
	jz     2f /* First time the debugger is entered. */
	/* Check if this is a recursive entry? */
	cmpl   %eax, %ecx /* PREVIOUS_LAPIC_ID == MY_LAPIC_ID */
	je     2f /* Recursive debugger entry */
	movq   dbg_cpu_temporary-8(,%rcx,8), %rcx
	/* This is where we get if some other CPU is currently inside the debugger...
	 * At this point, either re-enable interrupts (if they were enabled before),
	 * and hlt to wait for the locking core to exit debugger mode, at which point
	 * it should send an IPI to let us know that our turn has come, or keep on
	 * idling (only using pause) if we're not allowed to turn on interrupts. */
	pause
	testq  $(EFLAGS_IF), 0(%rsp)
	jz     L(acquire_lapic_lock) /* Not allowed to block... */
	sti
	hlt
	cli
	jmp    L(acquire_lapic_lock)
2:	movl   dbg_cpu_temporary-8(,%rcx,8), %rcx
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
	cmpl   $(0), dbg_active
	jne    L(recursive_debugger)

	/* Save registers */
	movq   0(%rsp), %rax        /* %rflags */
	movq   %rax, dbg_exitstate+OFFSET_FCPUSTATE_RFLAGS
	movq   8(%rsp), %rax        /* %rax */
	movq   %rax, dbg_exitstate+OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_RAX
	movq   %edi, dbg_exitstate+OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_RDI
	movq   %esi, dbg_exitstate+OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_RSI
	movq   %ebp, dbg_exitstate+OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_RBP
	leaq   24(%rsp), %rax
	movq   %rax, dbg_exitstate+OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_RSP
	movq   %ebx, dbg_exitstate+OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_RBX
	movq   %edx, dbg_exitstate+OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_RDX
	movq   %ecx, dbg_exitstate+OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_RCX
	movq   16(%rsp), %rax       /* %rip */
	movq   %rax, dbg_exitstate+OFFSET_FCPUSTATE_RIP
	movq   %es, %rax
	movq   %rax, dbg_exitstate+OFFSET_FCPUSTATE_ES
	movq   %cs, %rax
	movq   %rax, dbg_exitstate+OFFSET_FCPUSTATE_CS
	movq   %ss, %rax
	movq   %rax, dbg_exitstate+OFFSET_FCPUSTATE_SS
	movq   %ds, %rax
	movq   %rax, dbg_exitstate+OFFSET_FCPUSTATE_DS
	movq   %fs, %rax
	movq   %rax, dbg_exitstate+OFFSET_FCPUSTATE_FS
	movq   %gs, %rax
	movq   %rax, dbg_exitstate+OFFSET_FCPUSTATE_GS
	movq   $(0), dbg_exitstate+OFFSET_FCPUSTATE_TR
	strw   dbg_exitstate+OFFSET_FCPUSTATE_TR
	movq   $(0), dbg_exitstate+OFFSET_FCPUSTATE_LDT
	sldtw  dbg_exitstate+OFFSET_FCPUSTATE_LDT
	movq   %cr0, %rax
	movq   %rax, dbg_exitstate+OFFSET_FCPUSTATE_COREGS+OFFSET_COREGS_CR0
	movq   %cr2, %rax
	movq   %rax, dbg_exitstate+OFFSET_FCPUSTATE_COREGS+OFFSET_COREGS_CR2
	movq   %cr3, %rax
	movq   %rax, dbg_exitstate+OFFSET_FCPUSTATE_COREGS+OFFSET_COREGS_CR3
	movq   %cr4, %rax
	movq   %rax, dbg_exitstate+OFFSET_FCPUSTATE_COREGS+OFFSET_COREGS_CR4
	movq   %dr0, %rax
	movq   %rax, dbg_exitstate+OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR0
	movq   %dr1, %rax
	movq   %rax, dbg_exitstate+OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR1
	movq   %dr2, %rax
	movq   %rax, dbg_exitstate+OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR2
	movq   %dr3, %rax
	movq   %rax, dbg_exitstate+OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR3
	movq   %dr6, %rax
	movq   %rax, dbg_exitstate+OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR6
	movq   %dr7, %rax
	movq   %rax, dbg_exitstate+OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR7
	sgdtq  dbg_exitstate+OFFSET_FCPUSTATE_GDT
	sidtq  dbg_exitstate+OFFSET_FCPUSTATE_IDT

	.cfi_endproc
L(recursive_debugger):
	/* TODO: No CFI function set for this instruction! */
	/* Setup CFI to restore from `dbg_exitstate' */
	movq   $(dbg_exitstate), %rbx
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %rbx, SIZEOF_FCPUSTATE
	ASM_CFI_REL_OFFSET_RESTORE_FCPUSTATE(0)
	/* The debugger was entered recursively!
	 * Reset parts of the debugger control state, and restore the expected
	 * debugger CPU context. */
	movq   $(pagedir_kernel_phys), %rax
	movq   %rax, %cr3
	movq   %cr0, %rax
	orq    $(CR0_PE|CR0_PG), %rax
	andq   $~(CR0_TS|CR0_WP), %rax
	movq   %rax, %cr0

	/* Load the debugger-specific GDT / IDT */
	lgdtq  dbg_gdt_pointer
	lidtq  dbg_idt_pointer

	/* Load segment registers. */
	movw   $(SEGMENT_USER_DATA64_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   %ax, %fs
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
	movq   $(__kernel_debug_stack + KERNEL_DEBUG_STACKSIZE), %rsp
#ifdef ENTER_HERE
	pushq  $(dbg_exit) /* Return address... */
	pushq  %rdi        /* void (KCALL *main)(void *arg) */
	movq   %rsi, %rdi  /* void *arg */
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
	ret                /* (*main)(arg) --> return to `dbg_exit()' */
#else /* ENTER_HERE */
	movq   $(1), %rdi  /* uintptr_t show_welcome */
	pushq  $(dbg_exit) /* Return address... */
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
