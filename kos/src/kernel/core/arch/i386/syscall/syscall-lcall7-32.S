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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_LCALL7_32_S
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_LCALL7_32_S 1

#include <kernel/compiler.h>

#include <kernel/syscall-tables.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <asm/unistd.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/gdt.h>


#ifndef CONFIG_X86_EMULATE_LCALL7
.section .text
PUBLIC_FUNCTION(x86_syscall32_lcall7)
	/* Main entry point for `lcall $7'-style system calls */
	.cfi_startproc simple
	.cfi_signal_frame
	EXTERN(x86_syscall_personality_asm32_lcall7)
	.cfi_personality 0, x86_syscall_personality_asm32_lcall7
	/* NOTE: Right now our stack looks like this:
	 *  - 0(%esp)  == RETURN_IP
	 *  - 4(%esp)  == RETURN_CS
	 *  - 8(%esp)  == RETURN_SP
	 *  - 12(%esp) == RETURN_SS
	 * Notice that this doesn't match `struct irregs_user',
	 * since EFLAGS is missing between CS and SP.
	 * The user-space EFLAGS value hasn't been changed and
	 * is still stored in our current EFLAGS value. */
	.cfi_def_cfa %esp, 0
	.cfi_rel_offset %eip, 0
	.cfi_rel_offset %cs, 4
	.cfi_rel_offset %esp, 8
	.cfi_rel_offset %ss, 12
	cli /* Disable preemption (NOTE: user-space RPC redirection contains a special case
	     * to detect us not having a proper IRET tail and fixes this for us if we get
	     * interrupted before we're able to disable interrupts with this instruction!) */
	/* Must transform to { IP, CS, EFLAGS, SP, SS } */
	pushfl_cfi
	xchgl  %ss:0(%esp), %eax  /* { EAX, IP, CS, SP, SS }      (EAX == EFLAGS) */
	.cfi_rel_offset %eax, 0

	orl    $(EFLAGS_IF), %eax   /* Re-add the #IF flag to EFLAGS (was cleared since we called `cli' above) */
	.cfi_register %eflags, %eax

	xchgl  %ss:8(%esp), %eax  /* { EAX, IP, EFLAGS, SP, SS }  (EAX == CS) */
	.cfi_rel_offset %eflags, 8
	.cfi_register %cs, %eax

	xchgl  %ss:4(%esp), %eax  /* { EAX, CS, EFLAGS, SP, SS }  (EAX == IP) */
	.cfi_rel_offset %cs, 4
	.cfi_register %eip, %eax

	xchgl  %ss:0(%esp), %eax  /* { IP, CS, EFLAGS, SP, SS }   (EAX == EAX) */
	.cfi_rel_offset %eip, 0
	.cfi_same_value %eax

	/* And with that, our IRET tail has been fixed! (and we can re-enable interrupts) */
	sti
PUBLIC_FUNCTION(x86_syscall32_lcall7_iret)
	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss
	.cfi_def_cfa_offset 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12

	/* Save callee-clobber register */
	pushl_cfi_r %edx
	pushl_cfi_r %ecx
	pushl_cfi_r %eax

	/* Load kernel segments. */
	movl   $(SEGMENT_USER_DATA_RPL), %ecx
	movl   %ecx, %ds
	movl   %ecx, %es
	movl   $(SEGMENT_KERNEL_FSBASE), %ecx
	movl   %ecx, %fs

	/* At this point, we need to mirror the behavior or UKERN segment system calls in
	 * that we take arguments from the user-space stack, rather than from registers.
	 * When it comes to which system call should be invoked, that depends 2 factors:
	 *  >> lcall $7, $0     -- sysno == %eax
	 *  >> lcall $7, $1234  -- sysno == 1234
	 * Or in other words, when the segment-offset of the lcall instruction used is ZERO,
	 * or if the caller used something other than an lcall instruction, use %eax as sysno.
	 * Otherwise, use the segment offset as sysno */

	movl   %eax, %edx
	/* + 12: %eax, %ecx, %edx */
	/* + 12: %fs, %es, %ds */
	movl   (12 + 12 + OFFSET_IRREGS_EIP)(%esp), %ecx /* USER_EIP */
	/* lcall $7, $? -- { 0x9a, ?, ?, ?, ?, 0x07, 0x00 } */
	movb   -7(%ecx), %al
	cmpb   $(0x9a), %al
	jne    2f             /* Not invoked as `lcall $7, $?' */
	movw   -2(%ecx), %ax
	cmpw   $(0x0007), %ax
	jne    2f             /* Not invoked as `lcall $7, $?' */
	movl   -6(%ecx), %eax /* EAX = ? (from `lcall $7, $?') */
	testl  %eax, %eax
	jz     2f             /* Invoked as `lcall $7, $0' (use the original %eax as sysno) */
	movl   %eax, %edx
2:	/* At this point we've got the intended sysno (in `%edx')! */

	/* %edx:     l7_sysno: u32;
	 * 0(%esp):  l7_eax:   u32;
	 * 4(%esp):  l7_ecx:   u32;
	 * 8(%esp):  l7_edx:   u32;
	 * 12(%esp): l7_fs:    u32;
	 * 16(%esp): l7_es:    u32;
	 * 20(%esp): l7_ds:    u32;
	 * 24(%esp): l7_iret:  struct irregs_user; */
	movl   %esp, %ecx
	EXTERN(x86_syscall32_lcall7_main)
	call   x86_syscall32_lcall7_main

	popl_cfi %ecx /* popl <void> */
	.cfi_restore %eax
	popl_cfi_r %ecx
	popl_cfi_r %edx

	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds

	iret
	.cfi_endproc
END(x86_syscall32_lcall7_iret)
END(x86_syscall32_lcall7)
#endif /* !CONFIG_X86_EMULATE_LCALL7 */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_LCALL7_32_S */
