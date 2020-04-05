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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_VBOXGDB32_S
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_VBOXGDB32_S 1

#include <kernel/compiler.h>

#ifndef CONFIG_NO_VBOXGDB
#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <kos/kernel/cpu-state.h>

#define VBOXGDB_TRAPCTL_NTRAP 0x00 /* Don't trap */
#define VBOXGDB_TRAPCTL_SSTEP 0x01 /* Trap single-step events */
#define VBOXGDB_TRAPCTL_TRIGG 0x02 /* Trap was triggered */

.section .bss.cold
PUBLIC_OBJECT(_vboxgdb_trapctl)
	.byte 0x00 /* vboxgdb trap control byte (one of VBOXGDB_TRAPCTL_*) */
	.byte 0x00 /* Should-continue control byte */
END(_vboxgdb_trapctl)

.section .text.cold
INTERN_FUNCTION(_vboxgdb_debugtrap) /* int1 */
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	cmpb   $(VBOXGDB_TRAPCTL_SSTEP), _vboxgdb_trapctl
	je     _vboxgdb_debugtrap_chk_step
.Ldont_step:
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
	testl  $(DR6_BS), %eax
	jz     99f
	andl   $(~DR6_BS), %eax
	movl   %eax, %dr6
	.cfi_remember_state
	popl_cfi_r %eax

	/* Clear the trap flag (will be re-enabled by vboxgdb if needed) */
	andl   $(~EFLAGS_TF), OFFSET_IRREGS_EFLAGS(%esp)

	/* Indicate that a trap was triggered */
	movw   $(0x0000 | VBOXGDB_TRAPCTL_TRIGG), _vboxgdb_trapctl

	/* This the vboxgdb single-step break loop.
	 * In order to resume execution, vboxgdb will advance
	 * our EIP to point after this loop whenever it wishes
	 * to continue. (s.a. _vmIsStepLoopPaused) */
PUBLIC_OBJECT(_vboxgdb_steploop)
	cmpb   $(0), _vboxgdb_trapctl + 1
	je     _vboxgdb_steploop
END(_vboxgdb_steploop)
	nop /* DONT REMOVE THIS NOP! IT'S IMPORTANT TO vboxgdb! */

	movb   $(0), _vboxgdb_trapctl + 1
	iret

	.cfi_restore_state
99:	popl_cfi_r %eax
	PRIVATE(.Ldont_step)
	jmp   .Ldont_step
END(_vboxgdb_debugtrap_chk_step)

	.cfi_endproc
END(_vboxgdb_debugtrap)


#endif /* !CONFIG_NO_VBOXGDB */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_VBOXGDB32_S */
