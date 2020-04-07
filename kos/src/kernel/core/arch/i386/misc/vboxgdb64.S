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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_VBOXGDB64_S
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_VBOXGDB64_S 1

#include <kernel/compiler.h>

#ifndef CONFIG_NO_VBOXGDB
#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <kos/kernel/cpu-state.h>

#define VBOXGDB_TRAPCTL_NTRAP 0x00 /* Don't trap */
#define VBOXGDB_TRAPCTL_SSTEP 0x01 /* Trap single-step events */
#define VBOXGDB_TRAPCTL_TRIGG 0x02 /* Trap was triggered */

.section .bss.cold
.align 8
PUBLIC_OBJECT(_vboxgdb_trapctl)
	.byte 0x00               /* vboxgdb trap control byte (one of VBOXGDB_TRAPCTL_*) */
	.byte 0x00               /* Should-continue control byte */
	.word 0x0000             /* tc_pad;    pad... */
	.int  0x00000000         /* tc_pad2;   pad... */
	.quad 0x0000000000000000 /* tc_teaddr; Address of the current trap-enter instruction + 1 */
END(_vboxgdb_trapctl)


.section .text.cold
INTERN_FUNCTION(_vboxgdb_breakpoint) /* int3 */
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	pushq_cfi_r %rax
	movq   (8 + OFFSET_IRREGS_RIP)(%rsp), %rax
	cmpq   %rax, _vboxgdb_trapctl + 8 /* tc_teaddr */
	popq_cfi_r %rax
	je     .Lenter_steploop /* Enter the debugger step-loop */

	/* Repeat the piece of code that was overwritten by the code injection */
	testq  $(3), OFFSET_IRREGS_CS(%rsp)
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
	cmpb   $(VBOXGDB_TRAPCTL_SSTEP), _vboxgdb_trapctl
	je     _vboxgdb_debugtrap_chk_step
PRIVATE_LABEL(.Lnormal_debugtrap):
	.cfi_remember_state

	/* Repeat the piece of code that was overwritten by the code injection */
	testq  $(3), OFFSET_IRREGS_CS(%rsp)
	EXTERN(_x86_idt_debugtrap_after_enter)
	jz     _x86_idt_debugtrap_after_enter
	swapgs
	jmp    _x86_idt_debugtrap_after_enter

	.cfi_restore_state
PRIVATE_FUNCTION(_vboxgdb_debugtrap_chk_step)
	pushq_cfi_r %rax
	movq   %dr6, %rax
	testq  $(DR6_BS), %rax
	jz     99f
	andq   $(~DR6_BS), %rax
	movq   %rax, %dr6
	.cfi_remember_state
	popq_cfi_r %rax

	/* Clear the trap flag (will be re-enabled by vboxgdb if needed) */
	andq   $(~EFLAGS_TF), OFFSET_IRREGS_RFLAGS(%rsp)

PRIVATE_LABEL(.Lenter_steploop):
	/* Indicate that a trap was triggered */
	movw   $(0x0000 | VBOXGDB_TRAPCTL_TRIGG), _vboxgdb_trapctl

	/* This the vboxgdb single-step break loop.
	 * In order to resume execution, vboxgdb will advance
	 * our RIP to point after this loop whenever it wishes
	 * to continue. (s.a. _vmIsStepLoopPaused)
	 * Alternatively, VirtualBox may  */
PUBLIC_OBJECT(_vboxgdb_steploop)
	cmpb   $(0), _vboxgdb_trapctl + 1
	je     _vboxgdb_steploop
END(_vboxgdb_steploop)
	nop /* DONT REMOVE THIS NOP! IT'S IMPORTANT TO vboxgdb! */

	movb   $(0), _vboxgdb_trapctl + 1
	iretq

	.cfi_restore_state
99:	popq_cfi_r %rax
	jmp   .Lnormal_debugtrap
END(_vboxgdb_debugtrap_chk_step)

	.cfi_endproc
END(_vboxgdb_debugtrap)


#endif /* !CONFIG_NO_VBOXGDB */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_VBOXGDB64_S */
