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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_VBOXGDB32_S
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_VBOXGDB32_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>
#include <kernel/vboxgdb.h>

#ifdef CONFIG_HAVE_KERNEL_VBOXGDB
#include <kernel/except.h>

#include <cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/ttest.h>
#include <kos/kernel/cpu-state.h>

#define VBOXGDB_TRAPCTL_NTRAP 0x00 /* Don't trap */
#define VBOXGDB_TRAPCTL_SSTEP 0x01 /* Trap single-step events */
#define VBOXGDB_TRAPCTL_TRIGG 0xff /* Trap was triggered */

.section .bss.cold
.align 4
PUBLIC_OBJECT(_vboxgdb_trapctl)
#define tc_ctrl      0
	.byte 0x00       /* tc_ctrl;   vboxgdb trap control byte (one of VBOXGDB_TRAPCTL_*) */
#define tc_cont      1
	.byte 0x00       /* tc_cont;   Should-continue control byte */
	.word 0x0000     /* tc_pad;    pad... */
#define tc_teaddr    4
	.long 0x00000000 /* tc_teaddr; Address of the current trap-enter instruction + 1 */
#define tc_rstpst    8
	.long 0x00000000 /* tc_rstpst; Starting address for range-stepping */
#define tc_rstpen    12
	.long 0x00000000 /* tc_rstpen; End address for range-stepping */
END(_vboxgdb_trapctl)



.section .text.cold
INTERN_FUNCTION(_vboxgdb_breakpoint) /* int3 */
	.cfi_startproc simple
	.cfi_restore_iret
	.cfi_def_cfa %esp, 0
	pushl_cfi_r %eax
	movl   %ss:(4 + OFFSET_IRREGS_EIP)(%esp), %eax
	cmpl   %eax, %ss:(_vboxgdb_trapctl + tc_teaddr)
	popl_cfi_r %eax
	je     .Lenter_steploop /* Enter the debugger step-loop */

	/* Repeat the piece of code that was overwritten by the code injection */
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	pushal_cfi_r

	/* Jump into the original breakpoint handler. */
	EXTERN(x86_idt_debugtrap)
	jmp    x86_idt_debugtrap + 5

	.cfi_endproc
END(_vboxgdb_breakpoint)



.section .text.cold
INTERN_FUNCTION(_vboxgdb_debugtrap) /* int1 */
	.cfi_startproc simple
	.cfi_restore_iret
	.cfi_def_cfa %esp, 0
	cmpb   $(VBOXGDB_TRAPCTL_SSTEP), %ss:(_vboxgdb_trapctl + tc_ctrl)
	je     _vboxgdb_debugtrap_chk_step
PRIVATE_LABEL(.Lnormal_debugtrap):
	.cfi_remember_state

	/* Repeat the piece of code that was overwritten by the code injection */
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	pushal_cfi_r

	/* Jump into the original debugtrap handler. */
	EXTERN(x86_idt_debugtrap)
	jmp    x86_idt_debugtrap + 5

	.cfi_restore_state
PRIVATE_FUNCTION(_vboxgdb_debugtrap_chk_step)
	pushl_cfi_r %eax
	movl   %dr6, %eax
	ttest  mask=DR6_BS, loc=%eax
	jz     99f
	andl   $(~DR6_BS), %eax
	movl   %eax, %dr6
	/* Check for range-stepping */
	movl   %ss:(4 + OFFSET_IRREGS_EIP)(%esp), %eax
	cmpl   %ss:(_vboxgdb_trapctl + tc_rstpst), %eax
	jb     1f  /* if (%eax < tc_rstpst) DO_STEP() */
	cmpl   %ss:(_vboxgdb_trapctl + tc_rstpen), %eax
	jb     .Lpop_eax_and_resume /* if (%eax < tc_rstpen) DONT_STEP() */
1:	xorl   %eax, %eax
	movl   %eax, %ss:(_vboxgdb_trapctl + tc_rstpst)
	movl   %eax, %ss:(_vboxgdb_trapctl + tc_rstpen)
	.cfi_remember_state
	popl_cfi_r %eax

	/* Clear the trap flag (will be re-enabled by vboxgdb if needed) */
	andl   $(~EFLAGS_TF), %ss:OFFSET_IRREGS_EFLAGS(%esp)

PRIVATE_LABEL(.Lenter_steploop):
	/* Indicate that a trap was triggered */
	movw   $(0x0000 | VBOXGDB_TRAPCTL_TRIGG), %ss:(_vboxgdb_trapctl + tc_ctrl)

	/* This the vboxgdb single-step break loop.
	 * In  order to resume execution, vboxgdb will advance
	 * our EIP to point after this loop whenever it wishes
	 * to continue. (s.a. _vmIsStepLoopPaused) */
PUBLIC_OBJECT(_vboxgdb_steploop)
	cmpb   $(0), %ss:(_vboxgdb_trapctl + tc_cont)
	je     _vboxgdb_steploop
END(_vboxgdb_steploop)
	nop /* DONT REMOVE THIS NOP! IT'S IMPORTANT TO vboxgdb! */

	movb   $(0),  %ss:(_vboxgdb_trapctl + tc_cont)
	iret

PRIVATE_LABEL(.Lpop_eax_and_resume):
	.cfi_restore_state
	.cfi_remember_state
	popl_cfi_r %eax
	iret

	.cfi_restore_state
99:	popl_cfi_r %eax
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
	pushfl_cfi_r
	cli
	pushl_cfi_r %esi
	pushl_cfi %ecx /* name */
	movl   $(.Lprefix), %esi
	movl   $(.Lprefix_len), %ecx
	movw   $(0x504), %dx
	rep;   outsb
	movl   0(%esp), %esi /* name */
	EXTERN(strlen)
	call   strlen
	.cfi_adjust_cfa_offset -4
	movl   %eax, %ecx
	movw   $(0x504), %dx
	rep;   outsb
	movl   $(.Lsuffix), %esi
	movl   $(.Lsuffix_len), %ecx
	rep;   outsb
	popl_cfi_r %esi

	popl_cfi %ecx /* %eflags */
	.cfi_register %eflags, %ecx
	popl_cfi %eax /* %eip */
	.cfi_register %eip, %eax
	pushl_cfi %ecx /* %eflags */
	pushl_cfi %cs  /* IRET.CS */
	pushl_cfi %eax /* IRET.EIP */
	jmp    _vboxgdb_steploop
	.cfi_endproc
END(vboxgdb_trap)


#endif /* CONFIG_HAVE_KERNEL_VBOXGDB */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_VBOXGDB32_S */
