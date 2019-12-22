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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_LCALL7_64_S
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_LCALL7_64_S 1

#include <hybrid/compiler.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/movzxq.h>
#include <asm/unistd.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/gdt.h>



.section .text
PUBLIC_FUNCTION(x86_syscall32_lcall7)
	/* Main entry point for `lcall $7'-style system calls */
	.cfi_startproc simple
	.cfi_signal_frame
	EXTERN(x86_syscall_personality_asm32_lcall7)
	.cfi_personality 0, x86_syscall_personality_asm32_lcall7
	/* NOTE: Right now our stack looks like this:
	 *  - 0(%rsp)  == RETURN_IP
	 *  - 8(%rsp)  == RETURN_CS
	 *  - 16(%rsp) == RETURN_SP
	 *  - 24(%rsp) == RETURN_SS
	 * Notice that this doesn't match `struct irregs_user',
	 * since RFLAGS is missing between CS and SP.
	 * The user-space RFLAGS value hasn't been changed and
	 * is still stored in our current RFLAGS value. */

	/* !!!FIXME!!!
	 * When lcall is used by user-space, preemption is _NOT_ disabled, and for the
	 * duration of a single instruction we could get interrupted whilst having the
	 * incorrect value set for %gs.base!
	 * -> Solution: Don't actually make use of call gates _at_ _all_!
	 *              Instead, define LDT[0] as something different in such a way
	 *              that trying to perform an lcall using it causes a #GPF (which
	 *              includes a regular IRET tail). Then, add a special case in its
	 *              instruction decoder to emulate lcall instructions!
	 * -> Given the fact that lcall isn't actually used that often, and on-top of
	 *    that: is only ever used by 32-bit code, and even then is quite the rarity,
	 *    there is no need to do this properly, as in: add special cases to _all_
	 *    interrupt handlers that check if the interrupt originated from lcall7 prior
	 *    to %gs.base has been exchanged, and manually exchange %gs.base if that is
	 *    the case. This would not only be extremely confusing, but also highly error-
	 *    prone, with all of it being only for a feature that is rarely used at best.
	 */

	.cfi_def_cfa %rsp, 0
	.cfi_rel_offset %rip, 0
	.cfi_rel_offset %cs, 8
	.cfi_rel_offset %rsp, 16
	.cfi_rel_offset %ss, 24
	cli /* Disable preemption (NOTE: user-space RPC redirection contains a special case
	     * to detect us not having a proper IRET tail and fixes this for us if we get
	     * interrupted before we're able to disable interrupts with this instruction!) */
	swapgs /* Fixup the GS.BASE register */
	/* Must transform to { IP, CS, RFLAGS, SP, SS } */
	pushfq_cfi
	xchgq  0(%rsp), %rax  /* { RAX, IP, CS, SP, SS }      (RAX == RFLAGS) */
	.cfi_rel_offset %rax, 0

	orq    $(EFLAGS_IF), %rax   /* Re-add the #IF flag to RFLAGS (was cleared since we called `cli' above) */
	.cfi_register %rflags, %rax

	xchgq  16(%rsp), %rax  /* { RAX, IP, RFLAGS, SP, SS }  (RAX == CS) */
	.cfi_rel_offset %rflags, 16
	.cfi_register %cs, %rax

	xchgq  8(%rsp), %rax  /* { RAX, CS, RFLAGS, SP, SS }  (RAX == IP) */
	.cfi_rel_offset %cs, 8
	.cfi_register %rip, %rax

	xchgq  0(%rsp), %rax  /* { IP, CS, RFLAGS, SP, SS }   (RAX == RAX) */
	.cfi_rel_offset %rip, 0
	.cfi_same_value %rax

	/* And with that, our IRET tail has been fixed! (and we can re-enable interrupts) */
	sti
PUBLIC_FUNCTION(x86_syscall32_lcall7_iret)
	.cfi_restore_iret_rip
	.cfi_restore_iret_cs
	.cfi_restore_iret_rflags
	.cfi_restore_iret_rsp
	.cfi_restore_iret_ss
	.cfi_def_cfa_offset 0

	/* Save scratch registers */
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %rax

	/* At this point, we need to mirror the behavior or UKERN segment system calls in
	 * that we take arguments from the user-space stack, rather than from registers.
	 * When it comes to which system call should be invoked, that depends 2 factors:
	 *  >> lcall $7, $0     -- sysno == %rax
	 *  >> lcall $7, $1234  -- sysno == 1234
	 * Or in other words, when the segment-offset of the lcall instruction used is ZERO,
	 * or if the caller used something other than an lcall instruction, use %rax as sysno.
	 * Otherwise, use the segment offset as sysno */

	movq   %rax, %rsi
	/* + 72: %rax, %rdi, %rsi, %rdx, %rcx, %r8, %r9, %r10, %r11 */
	movq   (72 + OFFSET_IRREGS_RIP)(%rsp), %rcx /* USER_EIP */
	/* lcall $7, $? -- { 0x9a, ?, ?, ?, ?, 0x07, 0x00 } */
	movb   -7(%rcx), %al
	cmpb   $(0x9a), %al
	jne    2f             /* Not invoked as `lcall $7, $?' */
	movw   -2(%rcx), %ax
	cmpw   $(0x0007), %ax
	jne    2f             /* Not invoked as `lcall $7, $?' */
	movl   -6(%rcx), %eax /* EAX = ? (from `lcall $7, $?') */
	testl  %eax, %eax
	jz     2f             /* Invoked as `lcall $7, $0' (use the original %rax as sysno) */
	movzlq %eax, %rsi
2:	/* At this point we've got the intended sysno (in `%rsi')! */

	/* %rsi:     l7_sysno: u32;
	 * 0(%rsp):  l7_eax:   u32;
	 * 4(%rsp):  l7_ecx:   u32;
	 * 8(%rsp):  l7_edx:   u32;
	 * 24(%rsp): l7_iret:  struct irregs_user; */
	movq   %rsp, %rdi
	EXTERN(x86_syscall32_lcall7_main)
	call   x86_syscall32_lcall7_main

	popq_cfi %rdi /* popq <void> */
	.cfi_restore %rax
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	popq_cfi_r %r8
	popq_cfi_r %r9
	popq_cfi_r %r10
	popq_cfi_r %r11

	iret
	.cfi_endproc
END(x86_syscall32_lcall7_iret)
END(x86_syscall32_lcall7)

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_LCALL7_64_S */
