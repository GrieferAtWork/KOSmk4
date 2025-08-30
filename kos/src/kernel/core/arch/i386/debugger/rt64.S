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
#include <asm/instr/interrupt.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>

#include <libunwind/cfi.h>

.section .text.cold
	.cfi_startproc simple
	/* Setup CFI to restore from `x86_dbg_exitstate' */
	EXTERN(x86_dbg_exitstate_b0)
	EXTERN(x86_dbg_exitstate_b1)
	EXTERN(x86_dbg_exitstate_b2)
	EXTERN(x86_dbg_exitstate_b3)
	EXTERN(x86_dbg_exitstate_b4)
	EXTERN(x86_dbg_exitstate_b5)
	EXTERN(x86_dbg_exitstate_b6)
	EXTERN(x86_dbg_exitstate_b7)

	/* Encode CFA as `x86_dbg_exitstate' */
	.cfi_escape DW_CFA_def_cfa_expression, 9
	.cfi_escape DW_OP_addr
	.cfi_escape (x86_dbg_exitstate_b0 + 0)
	.cfi_escape (x86_dbg_exitstate_b1 + 0)
	.cfi_escape (x86_dbg_exitstate_b2 + 0)
	.cfi_escape (x86_dbg_exitstate_b3 + 0)
	.cfi_escape (x86_dbg_exitstate_b4 + 0)
	.cfi_escape (x86_dbg_exitstate_b5 + 0)
	.cfi_escape (x86_dbg_exitstate_b6 + 0)
	.cfi_escape (x86_dbg_exitstate_b7 + 0)
	ASM_CFI_REL_OFFSET_RESTORE_FCPUSTATE(0)
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
	movq   $(dbg_stack + KERNEL_DEBUG_STACKSIZE), %rsp

	/* Load the current thread (needed to get someplace that we can put the IRET tail)
	 * NOTE: This must be done before we call `dbg_fini()', since `thiscpu_idle_x86_kernel_psp0(THIS_CPU)'
	 *       is one  of  the  fields which  was  saved  and overwritten  during  debugger  initialization.
	 *       By  leaving  the  debugger,  that  field  once again  gets  restored  and  may  no  longer be
	 *       initialized  in  case  the  debugger  was  entered  early  on  during  booting,  or  in  case
	 *       the field became corrupt for some reason. */
	movq   %gs:0, %rbp /* THIS_TASK */
	EXTERN(this_cpu)
	movq   this_cpu(%rbp), %rbp
	EXTERN(thiscpu_idle_x86_kernel_psp0)
	movq   thiscpu_idle_x86_kernel_psp0(%rbp), %rbp /* thiscpu_idle_x86_kernel_psp0(THIS_CPU) */

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
	lidtq  (x86_dbg_exitstate + OFFSET_FCPUSTATE_IDT)
	lgdtq  (x86_dbg_exitstate + OFFSET_FCPUSTATE_GDT)

	/* Restore debug registers */
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR7), %rax
	movq   %rax, %dr7
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR6), %rax
	movq   %rax, %dr6
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR3), %rax
	movq   %rax, %dr3
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR2), %rax
	movq   %rax, %dr2
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR1), %rax
	movq   %rax, %dr1
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR0), %rax
	movq   %rax, %dr0

	/* Restore control registers */
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR4), %rax
	movq   %rax, %cr4
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR3), %rax
	movq   %rax, %cr3
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR2), %rax
	movq   %rax, %cr2
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR0), %rax
	movq   %rax, %cr0

	/* Restore the LDT and TR registers */
	lldtw  (x86_dbg_exitstate + OFFSET_FCPUSTATE_LDT)
	movzwq (x86_dbg_exitstate + OFFSET_FCPUSTATE_TR), %rax
	movq   %rax, %rdx
	andq   $~0x7, %rdx
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GDT + OFFSET_DESCTAB_BASE), %rcx
	andb   $(0b11111101), 5(%rcx,%rdx,1)
	ltrw   %ax

	/* Restore segment registers. */
	movw   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GS), %gs
	movw   (x86_dbg_exitstate + OFFSET_FCPUSTATE_FS), %fs
	movw   (x86_dbg_exitstate + OFFSET_FCPUSTATE_DS), %ds
	movw   (x86_dbg_exitstate + OFFSET_FCPUSTATE_ES), %es

	/* Restore segment base registers. */
	movq   (x86_dbg_exitstate + SIZEOF_FCPUSTATE), %rax
	wrgsbaseq %rax /* %kernel_gs.base */
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_SGBASE + OFFSET_SGBASE_FSBASE), %rax
	wrfsbaseq %rax
	wrkgsbaseq (x86_dbg_exitstate + OFFSET_FCPUSTATE_SGBASE + OFFSET_SGBASE_GSBASE) /* %user_gs.base */

	/* Restore most general-purpose registers */
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R15), %r15
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R14), %r14
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R13), %r13
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R12), %r12
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R11), %r11
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R10), %r10
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R9),  %r9
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R8),  %r8
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RDI), %rdi
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RSI), %rsi
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RDX), %rdx
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RBX), %rbx
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RCX), %rcx
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RAX), %rax

	/* Load the end of the current cpu's IDLE thread's stack
	 * to (ab-)use as  temporary storage for  an IRET  tail.
	 * NOTE: The stack location we had already loaded above! */
	leaq   -(KERNEL_IDLE_STACKSIZE - SIZEOF_IRREGS)(%rbp), %rsp
	movq   (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RBP), %rbp

	/* Push an IRET tail onto the stack. */
	pushq  (x86_dbg_exitstate + OFFSET_FCPUSTATE_SS)
	pushq  (x86_dbg_exitstate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RSP)
	pushq  (x86_dbg_exitstate + OFFSET_FCPUSTATE_RFLAGS)
	pushq  (x86_dbg_exitstate + OFFSET_FCPUSTATE_CS)
	pushq  (x86_dbg_exitstate + OFFSET_FCPUSTATE_RIP)

	/* Release  the master debugger lock now that  all that's missing for us to
	 * do is to perform an IRET to return to the origin of `x86_dbg_exitstate'. */
	EXTERN(x86_dbg_owner_lapicid)
	movw   $(0), x86_dbg_owner_lapicid

	intr_exit intr_enabled=0
	.cfi_endproc
END(dbg_exit)


#ifndef __INTELLISENSE__
#define DEFINE_DBG_ENTER_SCPUSTATE 1
#include "rt64-enter.S.inl"
#define DEFINE_DBG_ENTER_ICPUSTATE 1
#include "rt64-enter.S.inl"
#define DEFINE_DBG_ENTER_KCPUSTATE 1
#include "rt64-enter.S.inl"
#define DEFINE_DBG_ENTER_LCPUSTATE 1
#include "rt64-enter.S.inl"
#define DEFINE_DBG_ENTER_UCPUSTATE 1
#include "rt64-enter.S.inl"
#define DEFINE_DBG_ENTER_FCPUSTATE 1
#include "rt64-enter.S.inl"
#define DEFINE_DBG_ENTER_HERE 1
#include "rt64-enter.S.inl"
#define DEFINE_DBG 1
#include "rt64-enter.S.inl"
#endif /* !__INTELLISENSE__ */

#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_RT32_S */
