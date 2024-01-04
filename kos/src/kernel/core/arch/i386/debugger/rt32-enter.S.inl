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
#ifdef __INTELLISENSE__
#include "rt32.S"
#define DEFINE_DBG_ENTER_ICPUSTATE 1
#endif /* __INTELLISENSE__ */

#include <debugger/entry.h>
#include <debugger/rt.h>
#include <kernel/x86/apic.h>

#include <asm/cpu-flags.h>
#include <asm/instr/ttest.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>

#include <cfi.h>

#if defined(DEFINE_DBG_ENTER_FCPUSTATE)
#define L(x)                         x##_dbg_enter_fcpustate
#define DBG_STATE_NAME               fcpustate
#define DBG_STATE_NAME_U             FCPUSTATE
#define DEFINE_DBG_ENTER_XCPUSTATE_R dbg_enter_fcpustate_r
#define DEFINE_DBG_ENTER_XCPUSTATE   dbg_enter_fcpustate
#define DBG_RT_STATEKIND_XCPU       DBG_RT_STATEKIND_FCPU
#elif defined(DEFINE_DBG_ENTER_UCPUSTATE)
#define L(x)                         x##_dbg_enter_ucpustate
#define DBG_STATE_NAME               ucpustate
#define DBG_STATE_NAME_U             UCPUSTATE
#define DEFINE_DBG_ENTER_XCPUSTATE_R dbg_enter_ucpustate_r
#define DEFINE_DBG_ENTER_XCPUSTATE   dbg_enter_ucpustate
#define DBG_RT_STATEKIND_XCPU       DBG_RT_STATEKIND_UCPU
#elif defined(DEFINE_DBG_ENTER_LCPUSTATE)
#define L(x)                         x##_dbg_enter_lcpustate
#define DBG_STATE_NAME               lcpustate
#define DBG_STATE_NAME_U             LCPUSTATE
#define DEFINE_DBG_ENTER_XCPUSTATE_R dbg_enter_lcpustate_r
#define DEFINE_DBG_ENTER_XCPUSTATE   dbg_enter_lcpustate
#define DBG_RT_STATEKIND_XCPU       DBG_RT_STATEKIND_LCPU
#elif defined(DEFINE_DBG_ENTER_KCPUSTATE)
#define L(x)                         x##_dbg_enter_kcpustate
#define DBG_STATE_NAME               kcpustate
#define DBG_STATE_NAME_U             KCPUSTATE
#define DEFINE_DBG_ENTER_XCPUSTATE_R dbg_enter_kcpustate_r
#define DEFINE_DBG_ENTER_XCPUSTATE   dbg_enter_kcpustate
#define DBG_RT_STATEKIND_XCPU       DBG_RT_STATEKIND_KCPU
#elif defined(DEFINE_DBG_ENTER_ICPUSTATE)
#define L(x)                         x##_dbg_enter_icpustate
#define DBG_STATE_NAME               icpustate
#define DBG_STATE_NAME_U             ICPUSTATE
#define DEFINE_DBG_ENTER_XCPUSTATE_R dbg_enter_icpustate_r
#define DEFINE_DBG_ENTER_XCPUSTATE   dbg_enter_icpustate
#define DBG_RT_STATEKIND_XCPU       DBG_RT_STATEKIND_ICPU
#elif defined(DEFINE_DBG_ENTER_SCPUSTATE)
#define L(x)                         x##_dbg_enter_scpustate
#define DBG_STATE_NAME               scpustate
#define DBG_STATE_NAME_U             SCPUSTATE
#define DEFINE_DBG_ENTER_XCPUSTATE_R dbg_enter_scpustate_r
#define DEFINE_DBG_ENTER_XCPUSTATE   dbg_enter_scpustate
#define DBG_RT_STATEKIND_XCPU       DBG_RT_STATEKIND_SCPU
#elif defined(DEFINE_DBG_ENTER_HERE)
#define L(x)                         x##_dbg_enter_here
#elif defined(DEFINE_DBG)
#define L(x)                         x##_dbg
#endif /* ... */


#ifdef DEFINE_DBG_ENTER_XCPUSTATE
.section .text.cold
PUBLIC_FUNCTION(DEFINE_DBG_ENTER_XCPUSTATE)
	.cfi_startproc simple
	.cfi_def_cfa %edx, 0
	.cfi_signal_frame
#ifdef DEFINE_DBG_ENTER_ICPUSTATE
	ASM_CFI_OFFSET_RESTORE_ICPUSTATE(0)
#elif defined(DEFINE_DBG_ENTER_SCPUSTATE)
	ASM_CFI_OFFSET_RESTORE_SCPUSTATE(0)
#else /* DEFINE_DBG_ENTER_... */
#define ASM_CFI_REL_OFFSET_RESTORE_XCPUSTATE2(func, offset) func(offset)
#define ASM_CFI_REL_OFFSET_RESTORE_XCPUSTATE(offset) ASM_CFI_REL_OFFSET_RESTORE_XCPUSTATE2(PP_CAT2(ASM_CFI_REL_OFFSET_RESTORE_,DBG_STATE_NAME_U), offset)
	ASM_CFI_REL_OFFSET_RESTORE_XCPUSTATE(0)
#undef ASM_CFI_REL_OFFSET_RESTORE_XCPUSTATE
#undef ASM_CFI_REL_OFFSET_RESTORE_XCPUSTATE2
#endif /* !DEFINE_DBG_ENTER_... */
	/* %ecx: struct dbg_entry_info const *info
	 * %edx: struct Xcpustate *state */
	EXTERN(DEFINE_DBG_ENTER_XCPUSTATE_R)
	call   DEFINE_DBG_ENTER_XCPUSTATE_R
#ifdef DEFINE_DBG_ENTER_SCPUSTATE
	cli
	movl   %eax, %esp
	EXTERN(cpu_apply_scpustate_esp)
	jmp    cpu_apply_scpustate_esp
#elif defined(DEFINE_DBG_ENTER_ICPUSTATE)
	cli
	movl   %eax, %esp
	EXTERN(cpu_apply_icpustate_esp)
	jmp    cpu_apply_icpustate_esp
#else /* ... */
	movl   %eax, %ecx
	EXTERN(PP_CAT2(cpu_apply_,DBG_STATE_NAME))
	jmp    PP_CAT2(cpu_apply_,DBG_STATE_NAME)
#endif /* !... */
	.cfi_endproc
END(DEFINE_DBG_ENTER_XCPUSTATE)
#endif /* DEFINE_DBG_ENTER_XCPUSTATE */


#ifdef DEFINE_DBG_ENTER_XCPUSTATE_R
#define DBG_ENTER_NAME  DEFINE_DBG_ENTER_XCPUSTATE_R
#elif defined(DEFINE_DBG_ENTER_HERE)
#define DBG_ENTER_NAME  dbg_enter_here
#else
#define DBG_ENTER_NAME  dbg
#endif





/* struct Xcpustate *FCALL
 * dbg_enter_Xcpustate_r(struct dbg_entry_info const *info,
 *                       struct Xcpustate *state); */
.section .text.cold
PUBLIC_FUNCTION(DBG_ENTER_NAME)
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %esp, 4
	.cfi_rel_offset %eip, 0
	pushl_cfi_r %eax
	pushfl_cfi_r
	cli /* Disable interrupts */

	/* Acquire the LAPIC lock. */
#ifndef CONFIG_NO_SMP
	/* Figure out the calling CPU, so we can acquire the primary DBG-mode lock.
	 * On x86, we use the LAPIC ID for this purpose. */
L(.Lacquire_lapicid_lock):
	EXTERN(x86_lapicbase)
	movl   %ss:x86_lapicbase, %eax
	testl  %eax, %eax
	jz     L(.Lsingle_lapicid_lock) /* No LAPIC --> We're the only CPU! */
	movl   %ss:APIC_ID(%eax), %eax
	andl   $(APIC_ID_FMASK), %eax
	shrl   $(APIC_ID_FSHIFT), %eax
#ifndef X86_DBG_LAPICTEMPORARY_DEFINED
#define X86_DBG_LAPICTEMPORARY_DEFINED 1
	.pushsection .bss.cold
	PRIVATE_OBJECT(x86_dbg_lapictemporary)
		.skip 256 * 4
	END(x86_dbg_lapictemporary)
	.popsection
#endif /* !X86_DBG_LAPICTEMPORARY_DEFINED */
	movl   %ecx, %ss:x86_dbg_lapictemporary(,%eax,4) /* Preserve %ecx */
	leal   1(%eax), %ecx
	xorl   %eax, %eax
	EXTERN(x86_dbg_owner_lapicid)
	lock   cmpxchgw %cx, %ss:x86_dbg_owner_lapicid
	jz     L(.Lfirst_lapicid_lock) /* First time the debugger is entered. */
	cmpw   %ax, %cx /* PREVIOUS_LAPIC_ID == MY_LAPIC_ID */
	je     L(.Lfirst_lapicid_lock) /* Recursive debugger entry (handled later) */
	movl   %ss:x86_dbg_lapictemporary-4(,%ecx,4), %ecx /* Restore %ecx */
	/* This is where we get if some other CPU is currently inside the debugger...
	 * At  this point, either re-enable interrupts (if they were enabled before),
	 * and always idle a bit (pause) before trying once again. */
	ttest  mask=EFLAGS_IF, loc=0(%esp), seg=%ss
	jz     1f /* Not allowed to block... */
	sti
	/* A secondary pause is used  because `sti' only enables  interrupts after the next  instruction.
	 * The intend here is that we execute `pause' at least once with interrupts enabled (if possible) */
	pause
	pause
	cli
	jmp    L(.Lacquire_lapicid_lock)
1:	/* We can't get into the debugger because some other thread is trying to get
	 * in at this very moment. - However, in order to enter debugger mode, that
	 * other CPU will have send out an IPI to get all other CPUs to suspend their
	 * operations.
	 *
	 * The problem is that we can't enable preemption right now, and so we can't
	 * respond to that interrupt request like we normally would.
	 *
	 * As such, the only way to work around this is by directly triggering the
	 * interrupt used for IPI communications. (even though by doing so, we make
	 * use of more stack space than our caller has given us permission to use...) */
	pause
	/* TODO: Don't trigger intee, but instead call `debugger_wait_for_done' directly.
	 *       There's no reason to invoke arbitrary IPIs here! */
	int    $(0xee) /* #define IDT_X86_ee apic_ipi */

	jmp    L(.Lacquire_lapicid_lock)
L(.Lsingle_lapicid_lock):
	EXTERN(x86_dbg_owner_lapicid)
	movw   $(1), %ss:x86_dbg_owner_lapicid
	jmp    L(.Ldone_lapicid_lock)
L(.Lfirst_lapicid_lock):
	movl   %ss:x86_dbg_lapictemporary-4(,%ecx,4), %ecx /* Restore %ecx */
L(.Ldone_lapicid_lock):
#else /* !CONFIG_NO_SMP */
	EXTERN(x86_dbg_owner_lapicid)
	movw   $(1), %ss:x86_dbg_owner_lapicid
#endif /* CONFIG_NO_SMP */

	/* As  far  as scheduling  semantics go,  we're  now in  debugger mode.
	 * However,  we still have a lot to do  in order to set up the expected
	 * debug-mode environment (including stack, segments, scheduling, etc.) */

	/* First step: Check if  we've already  been  in debugger  mode  before.
	 *             If  we were, then the debugger has tried to enter itself,
	 *             in which case we mustn't override `DBG_RT_REGLEVEL_EXIT',
	 *             but  should instead  reset the  stack and  invoke the new
	 *             debugger entry point. */
	EXTERN(dbg_active)
	cmpb   $(0), %ss:dbg_active
	jne    L(.Lalready_active)

	/* Save the register for the caller of our function in `x86_dbg_exitstate' */
	EXTERN(x86_dbg_exitstate)
	movl   %ss:0(%esp), %eax        /* %eflags */
	movl   %eax, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_EFLAGS)
	movl   %ss:4(%esp), %eax        /* %eax */
	movl   %eax, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EAX)
	movl   %edi, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EDI)
	movl   %esi, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_ESI)
	movl   %ebp, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EBP)
	leal   12(%esp), %eax           /* %esp */
	movl   %eax, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_ESP)
	movl   %ebx, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EBX)
	movl   %edx, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EDX)
	movl   %ecx, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_ECX)
	movl   %ss:8(%esp), %eax        /* %eip */
	movl   %eax, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_EIP)
	movl   %es, %eax
	movl   %eax, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_ES)
	movl   %cs, %eax
	movl   %eax, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_CS)
	movl   %ss, %eax
	movl   %eax, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_SS)
	movl   %ds, %eax
	movl   %eax, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_DS)
	movl   %fs, %eax
	movl   %eax, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_FS)
	movl   %gs, %eax
	movl   %eax, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_GS)
	movl   $(0), %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_TR)
	strw   %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_TR)
	movl   $(0), %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_LDT)
	sldtw  %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_LDT)
	movl   %cr0, %eax
	movl   %eax, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR0)
	movl   %cr2, %eax
	movl   %eax, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR2)
	movl   %cr3, %eax
	movl   %eax, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR3)
	movl   %cr4, %eax
	movl   %eax, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR4)
	movl   %dr0, %eax
	movl   %eax, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR0)
	movl   %dr1, %eax
	movl   %eax, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR1)
	movl   %dr2, %eax
	movl   %eax, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR2)
	movl   %dr3, %eax
	movl   %eax, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR3)
	movl   %dr6, %eax
	movl   %eax, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR6)
	movl   %dr7, %eax
	movl   %eax, %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR7)
	sgdtl  %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_GDT)
	sidtl  %ss:(x86_dbg_exitstate + OFFSET_FCPUSTATE_IDT)

L(.Lalready_active):

	/* Encode CFA as `x86_dbg_exitstate' */
	EXTERN(x86_dbg_exitstate_b0)
	EXTERN(x86_dbg_exitstate_b1)
	EXTERN(x86_dbg_exitstate_b2)
	EXTERN(x86_dbg_exitstate_b3)
	.cfi_escape DW_CFA_def_cfa_expression, 5
	.cfi_escape DW_OP_addr, x86_dbg_exitstate_b0, x86_dbg_exitstate_b1, \
	                        x86_dbg_exitstate_b2, x86_dbg_exitstate_b3
	ASM_CFI_OFFSET_RESTORE_FCPUSTATE(0)

	/* Fixup control registers. */
	movl   $(pagedir_kernel_phys), %eax
	movl   %eax, %cr3

	movl   %cr0, %eax
	orl    $(CR0_PE | CR0_PG), %eax
	andl   $~(CR0_TS | CR0_WP), %eax
	movl   %eax, %cr0

	/* Load the debugger-specific GDT / IDT */
	EXTERN(x86_dbggdt_ptr)
	lgdtl  %ss:x86_dbggdt_ptr
	EXTERN(x86_dbgidt_ptr)
	lidtl  %ss:x86_dbgidt_ptr

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

	/* x86_dbggdt[SEGMENT_CPU_TSS].busy = 0; */
	EXTERN(x86_dbggdt)
	andb   $(0b11111101), x86_dbggdt+SEGMENT_CPU_TSS+5
	movw   $(SEGMENT_CPU_TSS), %ax
	ltrw   %ax  /* %tr = SEGMENT_CPU_TSS */

	movw   $(SEGMENT_CPU_LDT), %ax
	lldtw  %ax  /* %ldtr = SEGMENT_CPU_LDT */

	EXTERN(dbg_active)
	cmpb   $(0), dbg_active
	jne    L(.Ldont_reset_dbg_stack)
	/* Check if we're actually running from the debugger stack. */
	cmpl   $(dbg_stack), %esp
	jb     L(.Ldont_reset_dbg_stack) /* if (%esp < dbg_stack) goto L(.Ldont_reset_dbg_stack); */
	cmpl   $(dbg_stack + KERNEL_DEBUG_STACKSIZE - 768), %esp
	jae    L(.Ldont_reset_dbg_stack) /* if (%esp >= dbg_stack + KERNEL_DEBUG_STACKSIZE - 768) goto L(.Ldont_reset_dbg_stack); */
	EXTERN(x86_dbg_reset_dbg_stack)
	call   x86_dbg_reset_dbg_stack
L(.Ldont_reset_dbg_stack):

	/* Load the debugger stack. */
	EXTERN(dbg_stack)
	movl   $(dbg_stack + KERNEL_DEBUG_STACKSIZE), %esp

	/* Fill in TRAP-level cpu state information.
	 * NOTE: Don't do so if the debugger is being entered recursively!
	 *       In  the later case, we must keep the original trap state. */
	cmpb   $(0), dbg_active
	jne    1f
	EXTERN(dbg_rt_trapstate)
	EXTERN(dbg_rt_trapstatekind)
#ifdef DBG_RT_STATEKIND_XCPU
	movl   $(DBG_RT_STATEKIND_XCPU), dbg_rt_trapstatekind
	movl   %edx, dbg_rt_trapstate
#else /* DBG_RT_STATEKIND_XCPU */
	movl   $(DBG_RT_STATEKIND_NONE), dbg_rt_trapstatekind
	movl   $(0), dbg_rt_trapstate
#endif /* !DBG_RT_STATEKIND_XCPU */
1:

	/* Setup the debugger entry point callback.
	 * This needs to be done immediately after loading the debugger stack,
	 * since  in the case  of a recursive  debugger invocation, `%ecx' may
	 * actually point into the debugger stack, meaning we have to copy  it
	 * before   actually   starting   to   make   use   of   the    stack!
	 * For this purpose, we set-up the stack as:
	 *  0(%esp):    OFFSET_DBG_ENTRY_INFO_ENTRY(%ecx)
	 *  4(%esp):    &dbg_exit
	 *  8(%esp):    OFFSET_DBG_ENTRY_INFO_ARGV(%ecx)[0]
	 * 12(%esp):    OFFSET_DBG_ENTRY_INFO_ARGV(%ecx)[1]
	 * 16(%esp):    OFFSET_DBG_ENTRY_INFO_ARGV(%ecx)[2]
	 *              [...]
	 *              <END-OF-STACK>
	 * For which we do:
	 *     memmovel(<END-OF-STACK> - (OFFSET_DBG_ENTRY_INFO_ARGC(%ecx) * 4),
	 *              OFFSET_DBG_ENTRY_INFO_ARGV(%ecx),
	 *              OFFSET_DBG_ENTRY_INFO_ARGC(%ecx));
	 */
#ifndef DEFINE_DBG
	testl  %ecx, %ecx
	jz     L(.Lcall_default)
	/* XXX: Do some additional  verification of  `struct dbg_entry_info const *%ecx'
	 *      After all: If there is anything wrong with it, we're in _deep_ troubles! */
	movl   %ecx, %ebp
	movl   OFFSET_DBG_ENTRY_INFO_ENTRY(%ebp), %ebx
	movl   OFFSET_DBG_ENTRY_INFO_ARGC(%ebp), %ecx
	testl  %ecx, %ecx
	jz     L(.Lafter_copy_dbg_args)
	movl   %ecx, %eax
	shll   $(2), %eax /* %eax = ARGC * 4 */
	movl   %esp, %edi
	subl   %eax, %edi
	leal   OFFSET_DBG_ENTRY_INFO_ARGV(0)(%ebp), %esi
	movl   %ecx, %edx /* Backup of ARGC */
	/* Check the relation of `%edi' and `%esi' */
	cmpl   %esi, %edi
	ja     L(.Lcopy_args_up)   /* EDI > ESI */
	jb     L(.Lcopy_args_down) /* EDI < ESI */
	/* case: %esi == %edi */
L(.Lafter_copy_dbg_args):
	shll   $(2), %edx  /* %edx = ARGC * 4 */
	subl   %edx, %esp  /* Skip stack space for arguments */
	EXTERN(dbg_exit)
	pushl  $(dbg_exit) /* Return address. */
	pushl  %ebx        /* Debugger entry point. */
	jmp    L(.Ldebug_stack_setup)

L(.Lcopy_args_up):    /* EDI > ESI */
	/* Copy memory top->bottom */
	std
	leal   -4(%edi,%ecx,4), %edi
	leal   -4(%esi,%ecx,4), %esi
1:	movsl
	loop   1b
	jmp    L(.Lafter_copy_dbg_args)

L(.Lcopy_args_down):  /* EDI < ESI */
	/* Copy memory bottom->top */
	cld
1:	movsl
	loop   1b
	jmp    L(.Lafter_copy_dbg_args)

L(.Lcall_default):
#endif /* !DEFINE_DBG */
	/* Call the default debugger entry point. */
	pushl  $(1)        /* dbg_main:show_welcome. */
	EXTERN(dbg_exit)
	pushl  $(dbg_exit) /* Return address. */
	EXTERN(dbg_main)
	pushl  $(dbg_main)
L(.Ldebug_stack_setup):

	/* At this point, we have the debugger stack fully set-up, and must now
	 * invoke  all  of  the high-level  debugger  initialization callbacks. */

	/* Check if this is a recursive callback. */
	cmpb   $(0), dbg_active
	jne    1f
	EXTERN(x86_dbg_init)
	call   x86_dbg_init /* Initialize first time around */
	/* NOTE: `x86_dbg_init()' will have suspended other CPUs */
	movb   $(1), dbg_active /* Indicate that the debugger is now active */
1:

	/* Reset the current debugger state. */
	EXTERN(x86_dbg_reset)
	call   x86_dbg_reset

	/* Enable interrupts */
	sti

	/* Actually invoke the debugger entry point.
	 * NOTE: The address of the used entry point address was pushed above. */
	ret
	.cfi_endproc
END(DBG_ENTER_NAME)


#undef DBG_ENTER_NAME
#undef DBG_STATE_NAME
#undef DBG_STATE_NAME_U
#undef DEFINE_DBG_ENTER_XCPUSTATE_R
#undef DEFINE_DBG_ENTER_XCPUSTATE
#undef DBG_RT_STATEKIND_XCPU

#undef DEFINE_DBG_ENTER_SCPUSTATE
#undef DEFINE_DBG_ENTER_ICPUSTATE
#undef DEFINE_DBG_ENTER_KCPUSTATE
#undef DEFINE_DBG_ENTER_LCPUSTATE
#undef DEFINE_DBG_ENTER_UCPUSTATE
#undef DEFINE_DBG_ENTER_FCPUSTATE
#undef DEFINE_DBG_ENTER_HERE
#undef DEFINE_DBG
#undef L
