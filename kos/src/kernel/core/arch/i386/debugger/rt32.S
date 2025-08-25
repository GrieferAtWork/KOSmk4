/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_RT32_S
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_RT32_S 1
#define __ASSEMBLER__ 1

#include <debugger/rt.h>

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <asm/cpu-flags.h>
#include <asm/instr/ttest.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>

#include <libunwind/cfi.h>

.section .text.cold
	.cfi_startproc simple
	/* Setup CFI to restore from `x86_dbg_exitstate' */
	EXTERN(x86_dbg_exitstate_b0);
	EXTERN(x86_dbg_exitstate_b1);
	EXTERN(x86_dbg_exitstate_b2);
	EXTERN(x86_dbg_exitstate_b3);

	/* Encode CFA as `x86_dbg_exitstate' */
	.cfi_escape DW_CFA_def_cfa_expression
	.cfi_escape 5
	.cfi_escape DW_OP_addr
	.cfi_escape (x86_dbg_exitstate_b0 + 0)
	.cfi_escape (x86_dbg_exitstate_b1 + 0)
	.cfi_escape (x86_dbg_exitstate_b2 + 0)
	.cfi_escape (x86_dbg_exitstate_b3 + 0)
	ASM_CFI_OFFSET_RESTORE_FCPUSTATE(0)
	nop /* For tracebacks. */
PUBLIC_FUNCTION(dbg_exit)
	cli
	/* Assert that debugger mode is enabled. */
	EXTERN(x86_dbg_owner_lapicid)
	cmpw   $(0), x86_dbg_owner_lapicid
	jne    1f
	int3   /* Assertion failed: Not in debugger mode! */
1:
	/* Reset the debugger stack before calling `x86_dbg_fini()'. */
	EXTERN(dbg_stack)
	movl   $(dbg_stack + KERNEL_DEBUG_STACKSIZE), %esp

	/* Load the current CPU (may be needed to get somewhere to put the IRET tail) */
	movl   %fs:this_cpu, %ebp

	/* Clear the dbg-active flag.
	 * NOTE: Since this flag is also cleared during `x86_dbg_init()',
	 *       we do so before `x86_dbg_fini()' */
	EXTERN(dbg_active)
	movb   $(0), dbg_active

	/* Finalize the debugger. */
	EXTERN(x86_dbg_fini)
	call   x86_dbg_fini

	cli /* Shouldn't be necessary, but better be safe */

	/* === Start loading the exit state === */

	/* Restore descriptor table registers */
	lidtl  (x86_dbg_exitstate + OFFSET_FCPUSTATE_IDT)
	lgdtl  (x86_dbg_exitstate + OFFSET_FCPUSTATE_GDT)

	/* Restore debug registers */
	movl   (x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR7), %eax
	movl   %eax, %dr7
	movl   (x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR6), %eax
	movl   %eax, %dr6
	movl   (x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR3), %eax
	movl   %eax, %dr3
	movl   (x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR2), %eax
	movl   %eax, %dr2
	movl   (x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR1), %eax
	movl   %eax, %dr1
	movl   (x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR0), %eax
	movl   %eax, %dr0

	/* Restore control registers */
	movl   (x86_dbg_exitstate + OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR4), %eax
	movl   %eax, %cr4
	movl   (x86_dbg_exitstate + OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR3), %eax
	movl   %eax, %cr3
	movl   (x86_dbg_exitstate + OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR2), %eax
	movl   %eax, %cr2
	movl   (x86_dbg_exitstate + OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR0), %eax
	movl   %eax, %cr0

	/* Restore the LDT and TR registers */
	lldtw  (x86_dbg_exitstate + OFFSET_FCPUSTATE_LDT)
	movzwl (x86_dbg_exitstate + OFFSET_FCPUSTATE_TR), %eax
	movl   %eax, %edx
	andl   $~0x7, %edx
	movl   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GDT + OFFSET_DESCTAB_BASE), %ecx
	andb   $(0b11111101), 5(%ecx,%edx,1)
	ltrw   %ax

	/* Restore most general-purpose registers */
	movl   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EDI), %edi
	movl   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_ESI), %esi
	movl   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EBX), %ebx
	movl   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EDX), %edx
	movl   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_ECX), %ecx
	movl   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EAX), %eax

	/* Check if we're about to return to VM86 */
#ifndef __I386_NO_VM86
	ttest  mask=EFLAGS_VM, loc=(x86_dbg_exitstate + OFFSET_FCPUSTATE_EFLAGS)
	jz     1f
	EXTERN(thiscpu_idle_x86_kernel_psp0)
	movl   thiscpu_idle_x86_kernel_psp0(%ebp), %esp
	subl   $(KERNEL_IDLE_STACKSIZE - SIZEOF_IRREGS_VM86), %esp
	movl   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EBP), %ebp
	pushl  (x86_dbg_exitstate + OFFSET_FCPUSTATE_GS)
	pushl  (x86_dbg_exitstate + OFFSET_FCPUSTATE_FS)
	pushl  (x86_dbg_exitstate + OFFSET_FCPUSTATE_DS)
	pushl  (x86_dbg_exitstate + OFFSET_FCPUSTATE_ES)
	pushl  (x86_dbg_exitstate + OFFSET_FCPUSTATE_SS)
	pushl  (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_ESP)
	pushl  (x86_dbg_exitstate + OFFSET_FCPUSTATE_EFLAGS)
	pushl  (x86_dbg_exitstate + OFFSET_FCPUSTATE_CS)
	pushl  (x86_dbg_exitstate + OFFSET_FCPUSTATE_EIP)
	jmp    .Lunlock_and_iret
#endif /* !__I386_NO_VM86 */

	/* Restore segment registers. */
1:	movw   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GS), %gs
	movw   (x86_dbg_exitstate + OFFSET_FCPUSTATE_FS), %fs
	movw   (x86_dbg_exitstate + OFFSET_FCPUSTATE_DS), %ds
	movw   (x86_dbg_exitstate + OFFSET_FCPUSTATE_ES), %es

	/* Check if we're about to return to user-space */
	ttest  mask=3, loc=(x86_dbg_exitstate + OFFSET_FCPUSTATE_CS)
	jz     1f
	EXTERN(thiscpu_idle_x86_kernel_psp0)
	movl   thiscpu_idle_x86_kernel_psp0(%ebp), %esp
	subl   $(KERNEL_IDLE_STACKSIZE - SIZEOF_IRREGS_USER), %esp
	pushl  (x86_dbg_exitstate + OFFSET_FCPUSTATE_SS)
	pushl  (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_ESP)
	pushl  (x86_dbg_exitstate + OFFSET_FCPUSTATE_EFLAGS)
	pushl  (x86_dbg_exitstate + OFFSET_FCPUSTATE_CS)
	pushl  (x86_dbg_exitstate + OFFSET_FCPUSTATE_EIP)
	movl   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EBP), %ebp
	jmp    .Lunlock_and_iret

	/* Return to kernel-space (in this scenario, we need to assume a valid destination SP) */
1:	movw   (x86_dbg_exitstate + OFFSET_FCPUSTATE_SS), %ss
	movl   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_ESP), %esp
	pushl  (x86_dbg_exitstate + OFFSET_FCPUSTATE_EFLAGS)
	pushl  (x86_dbg_exitstate + OFFSET_FCPUSTATE_CS)
	pushl  (x86_dbg_exitstate + OFFSET_FCPUSTATE_EIP)
	movl   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_EBP), %ebp

.Lunlock_and_iret:
	/* Release  the master debugger lock now that  all that's missing for us to
	 * do is to perform an IRET to return to the origin of `x86_dbg_exitstate'. */
	EXTERN(x86_dbg_owner_lapicid)
	movw   $(0), x86_dbg_owner_lapicid

	iret
	.cfi_endproc
END(dbg_exit)


#ifndef __INTELLISENSE__
#define DEFINE_DBG_ENTER_SCPUSTATE 1
#include "rt32-enter.S.inl"
#define DEFINE_DBG_ENTER_ICPUSTATE 1
#include "rt32-enter.S.inl"
#define DEFINE_DBG_ENTER_KCPUSTATE 1
#include "rt32-enter.S.inl"
#define DEFINE_DBG_ENTER_LCPUSTATE 1
#include "rt32-enter.S.inl"
#define DEFINE_DBG_ENTER_UCPUSTATE 1
#include "rt32-enter.S.inl"
#define DEFINE_DBG_ENTER_FCPUSTATE 1
#include "rt32-enter.S.inl"
#define DEFINE_DBG_ENTER_HERE 1
#include "rt32-enter.S.inl"
#define DEFINE_DBG 1
#include "rt32-enter.S.inl"
#endif /* !__INTELLISENSE__ */

#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_RT32_S */
