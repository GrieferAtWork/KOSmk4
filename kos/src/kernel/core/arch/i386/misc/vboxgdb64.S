/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_VBOXGDB64_S
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_VBOXGDB64_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>
#include <kernel/vboxgdb.h>

#ifdef CONFIG_HAVE_KERNEL_VBOXGDB
#include <cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/ttest.h>
#include <kos/kernel/cpu-state.h>

#define VBOXGDB_TRAPCTL_NTRAP 0x00 /* Don't trap */
#define VBOXGDB_TRAPCTL_SSTEP 0x01 /* Trap single-step events */
#define VBOXGDB_TRAPCTL_TRIGG 0x02 /* Trap was triggered */

.section .bss.cold
.align 8
PUBLIC_OBJECT(_vboxgdb_trapctl)
#define tc_ctrl      0
	.byte 0x00               /* vboxgdb trap control byte (one of VBOXGDB_TRAPCTL_*) */
#define tc_cont      1
	.byte 0x00               /* Should-continue control byte */
	.word 0x0000             /* tc_pad;    pad... */
	.int  0x00000000         /* tc_pad2;   pad... */
#define tc_teaddr    8
	.quad 0x0000000000000000 /* tc_teaddr; Address of the current trap-enter instruction + 1 */
#define tc_rstpst    16
	.quad 0x0000000000000000 /* tc_rstpst; Starting address for range-stepping */
#define tc_rstpen    24
	.quad 0x0000000000000000 /* tc_rstpen; End address for range-stepping */
END(_vboxgdb_trapctl)


.section .text.cold
INTERN_FUNCTION(_vboxgdb_breakpoint) /* int3 */
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	pushq_cfi_r %rax
	movq   (8 + OFFSET_IRREGS_RIP)(%rsp), %rax
	cmpq   %rax, (_vboxgdb_trapctl + tc_teaddr) /* tc_teaddr */
	popq_cfi_r %rax
	je     .Lenter_steploop /* Enter the debugger step-loop */

	/* Repeat the piece of code that was overwritten by the code injection */
	ttest  mask=3, loc=OFFSET_IRREGS_CS(%rsp)
	EXTERN(_x86_idt_breakpoint_after_enter)
	jz     _x86_idt_breakpoint_after_enter
	swapgs
	jmp    _x86_idt_breakpoint_after_enter

	.cfi_endproc
END(_vboxgdb_breakpoint)



.section .text.cold
INTERN_FUNCTION(_vboxgdb_debugtrap) /* int1 */
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	cmpb   $(VBOXGDB_TRAPCTL_SSTEP), (_vboxgdb_trapctl + tc_ctrl)
	je     _vboxgdb_debugtrap_chk_step
PRIVATE_LABEL(.Lnormal_debugtrap):
	.cfi_remember_state

	/* Repeat the piece of code that was overwritten by the code injection */
	ttest  mask=3, loc=OFFSET_IRREGS_CS(%rsp)
	EXTERN(_x86_idt_debugtrap_after_enter)
	jz     _x86_idt_debugtrap_after_enter
	swapgs
	jmp    _x86_idt_debugtrap_after_enter

	.cfi_restore_state
PRIVATE_FUNCTION(_vboxgdb_debugtrap_chk_step)
	pushq_cfi_r %rax
	movq   %dr6, %rax
	ttest  mask=DR6_BS, loc=%rax
	jz     99f
	andq   $(~DR6_BS), %rax
	movq   %rax, %dr6
	/* Check for range-stepping */
	movq   (4 + OFFSET_IRREGS_RIP)(%rsp), %rax
	cmpq   (_vboxgdb_trapctl + tc_rstpst), %rax
	jb     1f  /* if (%rax < tc_rstpst) DO_STEP() */
	cmpq   (_vboxgdb_trapctl + tc_rstpen), %rax
	jb     .Lpop_rax_and_resume /* if (%rax < tc_rstpen) DONT_STEP() */
1:	xorq   %rax, %rax
	movq   %rax, (_vboxgdb_trapctl + tc_rstpst)
	movq   %rax, (_vboxgdb_trapctl + tc_rstpen)
	.cfi_remember_state
	popq_cfi_r %rax

	/* Clear the trap flag (will be re-enabled by vboxgdb if needed) */
	andq   $(~EFLAGS_TF), OFFSET_IRREGS_RFLAGS(%rsp)

PRIVATE_LABEL(.Lenter_steploop):
	/* Indicate that a trap was triggered */
	movw   $(0x0000 | VBOXGDB_TRAPCTL_TRIGG), (_vboxgdb_trapctl + tc_ctrl)

	/* This the vboxgdb single-step break loop.
	 * In  order to resume execution, vboxgdb will advance
	 * our RIP to point after this loop whenever it wishes
	 * to continue. (s.a. _vmIsStepLoopPaused) */
PUBLIC_OBJECT(_vboxgdb_steploop)
	cmpb   $(0), (_vboxgdb_trapctl + tc_cont)
	je     _vboxgdb_steploop
END(_vboxgdb_steploop)
	nop /* DONT REMOVE THIS NOP! IT'S IMPORTANT TO vboxgdb! */

	movb   $(0),  (_vboxgdb_trapctl + tc_cont)
	iretq

PRIVATE_LABEL(.Lpop_rax_and_resume):
	.cfi_restore_state
	.cfi_remember_state
	popq_cfi_r %rax
	iretq

	.cfi_restore_state
99:	popq_cfi_r %rax
	jmp   .Lnormal_debugtrap
END(_vboxgdb_debugtrap_chk_step)

	.cfi_endproc
END(_vboxgdb_debugtrap)


.section .rodata
PRIVATE_OBJECT(.Lprefix)
	.ascii "%{vboxgdb:"
PRIVATE_CONST(.Lprefix_len, . - .Lprefix)
END(.Lprefix)
PRIVATE_OBJECT(.Lsuffix)
	.ascii "}\n"
PRIVATE_CONST(.Lsuffix_len, . - .Lsuffix)
END(.Lsuffix)

/* PUBLIC NOBLOCK NONNULL((1)) void
 * NOTHROW(FCALL vboxgdb_trap)(char const *__restrict name) */
.section .text
PUBLIC_FUNCTION(vboxgdb_trap)
	.cfi_startproc
	.byte  0xc3 /* ret (overwritten with 0x90 (nop) when vboxgdb is enabled during early boot) */
	pushfq_cfi_r
	cli
	pushq_cfi %rdi /* name */
	movq   $(.Lprefix), %rsi
	movq   $(.Lprefix_len), %rcx
	movw   $(0x504), %dx
	rep;   outsb
	movq   0(%rsp), %rdi /* name */
	EXTERN(strlen)
	call   strlen
	popq_cfi %rsi /* name */
	movq   %rax, %rcx
	movw   $(0x504), %dx
	rep;   outsb
	movq   $(.Lsuffix), %rsi
	movq   $(.Lsuffix_len), %rcx
	rep;   outsb
	popq_cfi %rcx /* %rflags */
	.cfi_register %rflags, %rcx
	popq_cfi %rax /* %rip */
	.cfi_register %rip, %rax

	movq   %ss, %rdx
	pushq_cfi %rdx /* IRET.SS */
	leaq   8(%rsp), %rdx
	pushq_cfi %rdx /* IRET.RSP */
	pushq_cfi %rcx /* %rflags */
	movq   %cs, %rdx
	pushq_cfi %rdx /* IRET.CS */
	pushq_cfi %rax /* IRET.RIP */
	jmp    _vboxgdb_steploop
	.cfi_endproc
END(vboxgdb_trap)


#endif /* CONFIG_HAVE_KERNEL_VBOXGDB */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_VBOXGDB64_S */
