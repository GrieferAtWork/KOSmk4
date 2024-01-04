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
#include "rt64.S"
#define DEFINE_DBG_ENTER_ICPUSTATE 1
#endif /* __INTELLISENSE__ */

#include <debugger/entry.h>
#include <debugger/rt.h>
#include <kernel/x86/apic.h>

#include <cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/movzxq.h>
#include <asm/instr/ttest.h>
#include <kos/kernel/bits/cpu-state-asm64.h>
#include <kos/kernel/bits/cpu-state64.h>

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
#endif


#ifdef DEFINE_DBG_ENTER_XCPUSTATE
.section .text.cold
PUBLIC_FUNCTION(DEFINE_DBG_ENTER_XCPUSTATE)
	.cfi_startproc simple
	.cfi_def_cfa %rsi, 0
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
	/* %rdi: struct dbg_entry_info const *info
	 * %rsi: struct Xcpustate *state */
	EXTERN(DEFINE_DBG_ENTER_XCPUSTATE_R)
	call   DEFINE_DBG_ENTER_XCPUSTATE_R
#ifdef DEFINE_DBG_ENTER_SCPUSTATE
	cli
	movq   %rax, %rsp
	EXTERN(cpu_apply_scpustate_rsp)
	jmp    cpu_apply_scpustate_rsp
#elif defined(DEFINE_DBG_ENTER_ICPUSTATE)
	cli
	movq   %rax, %rsp
	EXTERN(cpu_apply_icpustate_rsp)
	jmp    cpu_apply_icpustate_rsp
#else /* ... */
	movq   %rax, %rdi
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
	.cfi_startproc
	pushq_cfi_r %rax
	pushfq_cfi_r
	cli /* Disable interrupts */

	/* Acquire the LAPIC lock. */
#ifndef CONFIG_NO_SMP
	/* Figure out the calling CPU, so we can acquire the primary DBG-mode lock.
	 * On x86, we use the LAPIC ID for this purpose. */
L(.Lacquire_lapicid_lock):
	EXTERN(x86_lapicbase)
	movq   x86_lapicbase, %rax
	testq  %rax, %rax
	jz     L(.Lsingle_lapicid_lock) /* No LAPIC --> We're the only CPU! */
	movzlq APIC_ID(%rax), %rax
	andl   $(APIC_ID_FMASK), %eax
	shrl   $(APIC_ID_FSHIFT), %eax
#ifndef X86_DBG_LAPICTEMPORARY_DEFINED
#define X86_DBG_LAPICTEMPORARY_DEFINED 1
	.pushsection .bss.cold
	PRIVATE_OBJECT(x86_dbg_lapictemporary)
		.skip 256 * 8
	END(x86_dbg_lapictemporary)
	.popsection
#endif /* !X86_DBG_LAPICTEMPORARY_DEFINED */
	movq   %rcx, x86_dbg_lapictemporary(,%rax,8) /* Preserve %rcx */
	leal   1(%eax), %ecx
	xorq   %rax, %rax
	EXTERN(x86_dbg_owner_lapicid)
	lock   cmpxchgw %cx, x86_dbg_owner_lapicid
	jz     L(.Lfirst_lapicid_lock) /* First time the debugger is entered. */
	cmpw   %ax, %cx /* PREVIOUS_LAPIC_ID == MY_LAPIC_ID */
	je     L(.Lfirst_lapicid_lock) /* Recursive debugger entry (handled later) */
	movq   x86_dbg_lapictemporary-8(,%rcx,8), %rcx /* Restore %rcx */
	/* This is where we get if some other CPU is currently inside the debugger...
	 * At  this point, either re-enable interrupts (if they were enabled before),
	 * and always idle a bit (pause) before trying once again. */
	ttest  mask=EFLAGS_IF, loc=0(%rsp)
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
	movw   $(1), x86_dbg_owner_lapicid
	jmp    L(.Ldone_lapicid_lock)
L(.Lfirst_lapicid_lock):
	movq   x86_dbg_lapictemporary-8(,%rcx,8), %rcx /* Restore %rcx */
L(.Ldone_lapicid_lock):
#else /* !CONFIG_NO_SMP */
	EXTERN(x86_dbg_owner_lapicid)
	movw   $(1), x86_dbg_owner_lapicid
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
	cmpb   $(0), dbg_active
	jne    L(.Lalready_active)

	/* Save the register for the caller of our function in `x86_dbg_exitstate' */
	EXTERN(x86_dbg_exitstate)
	movq   0(%rsp), %rax        /* %rflags */
	movq   %rax, (x86_dbg_exitstate + OFFSET_FCPUSTATE_RFLAGS)
	movq   8(%rsp), %rax        /* %rax */
	movq   %rax, (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RAX)
	movq   %rdi, (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RDI)
	movq   %rsi, (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RSI)
	movq   %rbp, (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RBP)
	leaq   24(%rsp), %rax       /* %rsp */
	movq   %rax, (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RSP)
	movq   %rbx, (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RBX)
	movq   %rdx, (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RDX)
	movq   %rcx, (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RCX)
	movq   %r15, (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R15)
	movq   %r14, (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R14)
	movq   %r13, (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R13)
	movq   %r12, (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R12)
	movq   %r11, (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R11)
	movq   %r10, (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R10)
	movq   %r9,  (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R9)
	movq   %r8,  (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R8)
	movq   16(%rsp), %rax        /* %rip */
	movq   %rax, (x86_dbg_exitstate + OFFSET_FCPUSTATE_RIP)
	movq   %es, %rax
	movq   %rax, (x86_dbg_exitstate + OFFSET_FCPUSTATE_ES)
	movq   %cs, %rax
	movq   %rax, (x86_dbg_exitstate + OFFSET_FCPUSTATE_CS)
	movq   %ss, %rax
	movq   %rax, (x86_dbg_exitstate + OFFSET_FCPUSTATE_SS)
	movq   %ds, %rax
	movq   %rax, (x86_dbg_exitstate + OFFSET_FCPUSTATE_DS)
	movq   %fs, %rax
	movq   %rax, (x86_dbg_exitstate + OFFSET_FCPUSTATE_FS)
	movq   %gs, %rax
	movq   %rax, (x86_dbg_exitstate + OFFSET_FCPUSTATE_GS)
	movq   $(0), (x86_dbg_exitstate + OFFSET_FCPUSTATE_TR)
	strw   (x86_dbg_exitstate + OFFSET_FCPUSTATE_TR)
	movq   $(0), (x86_dbg_exitstate + OFFSET_FCPUSTATE_LDT)
	sldtw  (x86_dbg_exitstate + OFFSET_FCPUSTATE_LDT)
	rdgsbaseq %rax
	movq   %rax, (x86_dbg_exitstate + SIZEOF_FCPUSTATE) /* %kernel_gs.base */
	rdfsbaseq %rax
	movq   %rax, (x86_dbg_exitstate + OFFSET_FCPUSTATE_SGBASE + OFFSET_SGBASE_FSBASE)
	rdkgsbaseq (x86_dbg_exitstate + OFFSET_FCPUSTATE_SGBASE + OFFSET_SGBASE_GSBASE)
	movq   %cr0, %rax
	movq   %rax, (x86_dbg_exitstate + OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR0)
	movq   %cr2, %rax
	movq   %rax, (x86_dbg_exitstate + OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR2)
	movq   %cr3, %rax
	movq   %rax, (x86_dbg_exitstate + OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR3)
	movq   %cr4, %rax
	movq   %rax, (x86_dbg_exitstate + OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR4)
	movq   %dr0, %rax
	movq   %rax, (x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR0)
	movq   %dr1, %rax
	movq   %rax, (x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR1)
	movq   %dr2, %rax
	movq   %rax, (x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR2)
	movq   %dr3, %rax
	movq   %rax, (x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR3)
	movq   %dr6, %rax
	movq   %rax, (x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR6)
	movq   %dr7, %rax
	movq   %rax, (x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR7)
	sgdtq  (x86_dbg_exitstate + OFFSET_FCPUSTATE_GDT)
	sidtq  (x86_dbg_exitstate + OFFSET_FCPUSTATE_IDT)

L(.Lalready_active):

	/* Encode CFA as `x86_dbg_exitstate' */
	EXTERN(x86_dbg_exitstate_b0); EXTERN(x86_dbg_exitstate_b1)
	EXTERN(x86_dbg_exitstate_b2); EXTERN(x86_dbg_exitstate_b3)
	EXTERN(x86_dbg_exitstate_b4); EXTERN(x86_dbg_exitstate_b5)
	EXTERN(x86_dbg_exitstate_b6); EXTERN(x86_dbg_exitstate_b7)
	.cfi_escape DW_CFA_def_cfa_expression, 9
	.cfi_escape DW_OP_addr, x86_dbg_exitstate_b0, x86_dbg_exitstate_b1, \
	                        x86_dbg_exitstate_b2, x86_dbg_exitstate_b3, \
	                        x86_dbg_exitstate_b4, x86_dbg_exitstate_b5, \
	                        x86_dbg_exitstate_b6, x86_dbg_exitstate_b7
	ASM_CFI_OFFSET_RESTORE_FCPUSTATE(0)

	/* Fixup control registers. */
	movq   $(pagedir_kernel_phys), %rax
	movq   %rax, %cr3

	movq   %cr0, %rax
	movzlq $(CR0_PE|CR0_PG), %rdx
	orq    %rdx, %rax
	andq   $~(CR0_TS|CR0_WP), %rax
	movq   %rax, %cr0

	/* Load the debugger-specific GDT / IDT */
	EXTERN(x86_dbggdt_ptr)
	lgdtq  x86_dbggdt_ptr
	EXTERN(x86_dbgidt_ptr)
	lidtq  x86_dbgidt_ptr

	/* Load segment registers. */
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   %ax, %fs
	movw   %ax, %gs


	EXTERN(dbg_active)
	cmpb   $(0), dbg_active
	jne    L(.Ldont_reset_dbg_stack)
	/* Check if we're actually running from the debugger stack. */
	cmpq   $(dbg_stack), %rsp
	jb     L(.Ldont_reset_dbg_stack) /* if (%rsp < dbg_stack) goto L(.Ldont_reset_dbg_stack); */
	cmpq   $(dbg_stack + KERNEL_DEBUG_STACKSIZE - 1024), %rsp
	jae    L(.Ldont_reset_dbg_stack) /* if (%rsp >= dbg_stack + KERNEL_DEBUG_STACKSIZE - 1024) goto L(.Ldont_reset_dbg_stack); */
	/* Load %ss and %cs */
	movq   %rsp, %rax
	pushq  $(SEGMENT_KERNEL_DATA0) /* %ss */
	pushq  %rax                    /* %rsp */
	pushfq                         /* %rflags */
	pushq  $(SEGMENT_KERNEL_CODE)  /* %cs */
	pushq  $(1f)                   /* %rip */
	iretq
1:	EXTERN(x86_dbg_reset_dbg_stack)
	call   x86_dbg_reset_dbg_stack
L(.Ldont_reset_dbg_stack):

	/* Load the debugger stack. */
	EXTERN(dbg_stack)
	movq   $(dbg_stack + KERNEL_DEBUG_STACKSIZE), %rsp

	/* Load %ss and %cs */
	pushq  $(SEGMENT_KERNEL_DATA0)               /* %ss */
	pushq  $(dbg_stack + KERNEL_DEBUG_STACKSIZE) /* %rsp */
	pushfq                                       /* %rflags */
	pushq  $(SEGMENT_KERNEL_CODE)                /* %cs */
	pushq  $(1f)                                 /* %rip */
	iretq
1:

	/* x86_dbggdt[SEGMENT_CPU_TSS].busy = 0; */
	EXTERN(x86_dbggdt)
	andb   $(0b11111101), x86_dbggdt+SEGMENT_CPU_TSS+5
	movw   $(SEGMENT_CPU_TSS), %ax
	ltrw   %ax  /* %tr = SEGMENT_CPU_TSS */

	movw   $(SEGMENT_CPU_LDT), %ax
	lldtw  %ax  /* %ldtr = SEGMENT_CPU_LDT */

	/* Fill in TRAP-level cpu state information.
	 * NOTE: Don't do so if the debugger is being entered recursively!
	 *       In  the later case, we must keep the original trap state. */
	cmpb   $(0), dbg_active
	jne    1f
	EXTERN(dbg_rt_trapstate)
	EXTERN(dbg_rt_trapstatekind)
#ifdef DBG_RT_STATEKIND_XCPU
	movl   $(DBG_RT_STATEKIND_XCPU), dbg_rt_trapstatekind
	movq   %rsi, dbg_rt_trapstate
#else /* DBG_RT_STATEKIND_XCPU */
	movl   $(DBG_RT_STATEKIND_NONE), dbg_rt_trapstatekind
	movq   $(0), dbg_rt_trapstate
#endif /* !DBG_RT_STATEKIND_XCPU */
1:

	/* Setup the debugger entry point callback.
	 * This needs to be done immediately after loading the debugger stack,
	 * since  in the case  of a recursive  debugger invocation, `%rdi' may
	 * actually point into the debugger stack, meaning we have to copy  it
	 * before   actually   starting   to   make   use   of   the    stack!
	 * For this purpose, we set-up the stack as:
	 *    %rbx:    OFFSET_DBG_ENTRY_INFO_ENTRY(%rdi)
	 *  0(%rsp):    entry:%rdi   (either `OFFSET_DBG_ENTRY_INFO_ARGV(0)(%rdi)' or <undefined>)
	 *  8(%rsp):    entry:%rsi   (either `OFFSET_DBG_ENTRY_INFO_ARGV(1)(%rdi)' or <undefined>)
	 * 16(%rsp):    entry:%rdx   (either `OFFSET_DBG_ENTRY_INFO_ARGV(2)(%rdi)' or <undefined>)
	 * 24(%rsp):    entry:%rcx   (either `OFFSET_DBG_ENTRY_INFO_ARGV(3)(%rdi)' or <undefined>)
	 * 32(%rsp):    entry:%r8    (either `OFFSET_DBG_ENTRY_INFO_ARGV(4)(%rdi)' or <undefined>)
	 * 40(%rsp):    entry:%r9    (either `OFFSET_DBG_ENTRY_INFO_ARGV(5)(%rdi)' or <undefined>)
	 *              -- Additional arguments are passed on the stack, and are optional --
	 * 48(%rsp):    OFFSET_DBG_ENTRY_INFO_ARGV(%rdi)[6]
	 * 56(%rsp):    OFFSET_DBG_ENTRY_INFO_ARGV(%rdi)[7]
	 * 64(%rsp):    OFFSET_DBG_ENTRY_INFO_ARGV(%rdi)[8]
	 *              [...]
	 *              <END-OF-STACK>
	 */
	/* XXX: Do some additional  verification of  `struct dbg_entry_info const *%ecx'
	 *      After all: If there is anything wrong with it, we're in _deep_ troubles! */
#ifndef DEFINE_DBG                                /* >> #ifndef DEFINE_DBG                                     */
	testq  %rdi, %rdi                             /* >> if (%rdi != NULL)                                      */
	jz     L(.Lcall_default)                      /* >> {                                                      */
	movq   %rdi, %rbp                             /* >>     %rbp = %rdi;                                       */
	movq   OFFSET_DBG_ENTRY_INFO_ENTRY(%rbp), %rbx/* >>     %rbx = OFFSET_DBG_ENTRY_INFO_ENTRY(%rbp);          */
	movq   OFFSET_DBG_ENTRY_INFO_ARGC(%rbp), %rcx /* >>     %rcx = OFFSET_DBG_ENTRY_INFO_ARGC(%rbp);           */
	cmpq   $(6), %rcx                             /* >>     if (%rcx < 6)                                      */
	jnb    1f                                     /* >>     {                                                  */
	movq   $(6), %rdx                             /* >>         %rdx = 6;                                      */
	subq   %rcx, %rdx                             /* >>         %rdx = %rdx - %rcx; // %rdx = 6 - %rcx         */
	leaq   (,%rdx,8), %rdx                        /* >>         %rdx = %rdx * 8;    // %rdx = (6 - %rcx) * 8   */
	subq   %rdx, %rsp                             /* >>         %rsp = %rsp - %rdx; // %rsp = %rsp - (6 - %rcx) * 8 */
	testq  %rcx, %rcx                             /* >>         if (!%rcx)                                     */
	jz     L(.Ldone_copy)                         /* >>             goto done_copy;                            */
1:	                                              /* >>     }                                                  */
	leaq   (,%rcx,8), %rdx                        /* >>     %rdx = %rcx * 8;                                   */
	subq   %rdx, %rsp                             /* >>     %rsp = %rsp - %rdx; // %rsp = %rsp - %rcx * 8;     */
	movq   %rsp, %rdi                             /* >>     %rdi = %rsp;                                       */
	leaq   OFFSET_DBG_ENTRY_INFO_ARGV(0)(%rbp), %rsi/*>     %rsi = &OFFSET_DBG_ENTRY_INFO_ARGV(0)(%rbp);       */
	cmpq   %rsi, %rdi                             /* >>     if (%rdi > %rsi)                                   */
	ja     L(.Lcopy_down)                         /* >>         goto copy_down;                                */
	jb     L(.Lcopy_up)                           /* >>     if (%rdi < %rsi) goto copy_up;                     */
	jmp    L(.Ldone_copy)                         /* >>     goto push_entry;                                   */
L(.Lcopy_down):                                   /* >> copy_down:                                             */
	std                                           /* >>         RFLAGS.DF = 1;                                 */
	leaq   -8(%rdi,%rcx,8), %rdi                  /* >>         %rdi = (%rdi + (%rcx * 8)) - 8;                */
	leaq   -8(%rsi,%rcx,8), %rsi                  /* >>         %rsi = (%rsi + (%rcx * 8)) - 8;                */
1:	movsq                                         /* >>         do { movsq;                                    */
	loop   1b                                     /* >>         } loop;                                        */
	jmp    L(.Ldone_copy)                         /* >>     goto done_copy;                                    */
L(.Lcopy_up):                                     /* >> copy_up:                                               */
	cld                                           /* >>         RFLAGS.DF = 0;                                 */
1:	movsq                                         /* >>         do { movsq;                                    */
	loop   1b                                     /* >>         } loop;                                        */
L(.Ldone_copy):                                   /* >> done_copy: ;                                           */
	jmp    L(.Ldebug_stack_setup)                 /* >> } else                                                 */
L(.Lcall_default):                                /* >> {                                                      */
#endif /* !DEFINE_DBG */                          /* >> #endif // !DEFINE_DBG                                  */
	                                              /* >>     // Call the default debugger entry point.          */
	leaq   -40(%rsp), %rsp                        /* >>     %rsp = %rsp - 40; // 5 * 8                         */
	pushq  $(1)                                   /* >>     pushq(1);         // == dbg_main:%rdi=show_welcome */
	EXTERN(dbg_main)                              /* >>     EXTERN(dbg_main);                                  */
	movq   $(dbg_main), %rbx                      /* >>     %rbx = &dbg_main;                                  */
L(.Ldebug_stack_setup):                           /* >> }                                                      */

	/* At this point, we have the debugger stack fully set-up, and must now
	 * invoke  all  of  the high-level  debugger  initialization callbacks. */

	/* Check if this is a recursive callback. */
	cmpb   $(0), dbg_active
	jne    1f
	EXTERN(x86_dbg_init)
	call   x86_dbg_init     /* Initialize first time around */
	/* NOTE: `x86_dbg_init()' will have suspended other CPUs */
	movb   $(1), dbg_active /* Indicate that the debugger is now active */
1:

	/* Reset the current debugger state. */
	EXTERN(x86_dbg_reset)
	call   x86_dbg_reset

	/* Enable interrupts */
	sti

	/* Actually invoke the debugger entry point.
	 * NOTE: The address of the used entry point address is stored in `%rbx'. */

	/* Load register-based arguments. */
	popq   %rdi
	popq   %rsi
	popq   %rdx
	popq   %rcx
	popq   %r8
	popq   %r9
	/* NOTE: Additional, stack-based registers would now be accessible, starting at `0(%rsp)' */
	/* Push `dbg_exit' as the return address for the entry point function. */
	EXTERN(dbg_exit)
	pushq  $(dbg_exit)
	/* Actually jump to the debugger entry point that is being used. */
	jmpq   *%rbx
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
