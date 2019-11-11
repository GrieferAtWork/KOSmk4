/* HASH 0x8cf0debf */
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

#include <hybrid/compiler.h>

#include <kernel/except.h>
#include <kernel/paging.h>
#include <kernel/syscall.h>
#include <sched/rpc.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <asm/cpu-msr.h>
#include <asm/unistd.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/gdt.h>

#include <errno.h>
#include <fcntl.h>
#include <syscall.h>



EXTERN(__asm32_int80_invalid)
EXTERN(__asm32_sysenter_invalid)
EXTERN(__asm32_syscallrouter_int80)
EXTERN(__asm32_exsyscallrouter_int80)
EXTERN(__asm32_syscallrouter_sysenter)
EXTERN(__asm32_exsyscallrouter_sysenter)


.section .text
INTERN_FUNCTION(x86_int80_emulation)
	.cfi_startproc simple
	/* `struct icpustate *%ecx'
	 * NOTE: ENDOF(%ecx->IRREGS) is located at the end (top) of our kernel-stack! */
	.cfi_iret_signal_frame
	.cfi_def_cfa %ecx, OFFSET_ICPUSTATE_IRREGS
	.cfi_rel_offset %ds, OFFSET_ICPUSTATE_DS
	.cfi_rel_offset %es, OFFSET_ICPUSTATE_ES
	.cfi_rel_offset %fs, OFFSET_ICPUSTATE_FS
	.cfi_same_value %gs
	.cfi_rel_offset %edi, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EDI
	.cfi_rel_offset %esi, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_ESI
	.cfi_rel_offset %ebp, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EBP
	.cfi_rel_offset %ebx, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EBX
	.cfi_rel_offset %edx, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EDX
	.cfi_rel_offset %ecx, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_ECX
	.cfi_rel_offset %eax, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EAX
	cli    /* Prevent corruptions while we're juggling with our stack. */
	movl   %ecx, %esp
	.cfi_def_cfa_register %esp
	/* Restore user-space registers. */
	popal_cfi_r

	/* Check if our user-space return location got re-directed.
	 * If it was, we need to apply the register override at the
	 * saved return location, rather than the active one. */
	PUBLIC(x86_rpc_user_redirection)
	cmpl   $x86_rpc_user_redirection, 12+OFFSET_IRREGS_EIP(%esp)
	jne    1f
	PUBLIC(x86_rpc_redirection_iret)
	movl   %edi, %fs:x86_rpc_redirection_iret+OFFSET_IRREGS_EIP /* EIP := EDI */
	jmp    2f
1:	movl   %edi, 12+OFFSET_IRREGS_EIP(%esp) /* EIP := EDI */
2:	movl   %ebp, 12+OFFSET_IRREGS_ESP(%esp) /* ESP := EBP */
	sti    /* Re-enable interrupts now that all async-critical components were serviced. */

	/* Restore user-space segment registers (NOTE: %gs already contains the user-space value) */
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds

	/* At this point, most of the original user-space CPU context from the point
	 * when the `sysenter' instruction was executed has been restored. Additionally,
	 * we have already applied the required register transformations for safely
	 * returning to user-space once we're done here.
	 * -> With all of this done, we can now continue handling the sysenter as
	 *    though the CPU had supported the instruction from the get-go, using
	 *    the same assembly-level wrappers that would normally be used for
	 *    routing a real sysenter system call invocation. */
#ifndef CONFIG_NO_SYSCALL_TRACING
	INTERN(syscall_tracing_enabled)
	cmpb   $0, %ss:syscall_tracing_enabled
	jne    x86_idt_syscall_traced /* With tracing enabled... */
#endif
	jmp    x86_idt_syscall
	.cfi_endproc
END(x86_int80_emulation)




.section .text
INTERN_FUNCTION(x86_sysenter_emulation)
	.cfi_startproc simple
	/* `struct icpustate *%ecx'
	 * NOTE: ENDOF(%ecx->IRREGS) is located at the end (top) of our kernel-stack! */
	.cfi_iret_signal_frame
	.cfi_def_cfa %ecx, OFFSET_ICPUSTATE_IRREGS
	.cfi_rel_offset %ds, OFFSET_ICPUSTATE_DS
	.cfi_rel_offset %es, OFFSET_ICPUSTATE_ES
	.cfi_rel_offset %fs, OFFSET_ICPUSTATE_FS
	.cfi_same_value %gs
	.cfi_rel_offset %edi, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EDI
	.cfi_rel_offset %esi, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_ESI
	.cfi_rel_offset %ebp, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EBP
	.cfi_rel_offset %ebx, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EBX
	.cfi_rel_offset %edx, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EDX
	.cfi_rel_offset %ecx, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_ECX
	.cfi_rel_offset %eax, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EAX
	cli    /* Prevent corruptions while we're juggling with our stack. */
	movl   %ecx, %esp
	.cfi_def_cfa_register %esp
	/* Restore user-space registers. */
	popal_cfi_r

	/* Check if our user-space return location got re-directed.
	 * If it was, we need to apply the register override at the
	 * saved return location, rather than the active one. */
	PUBLIC(x86_rpc_user_redirection)
	cmpl  $x86_rpc_user_redirection, 12+OFFSET_IRREGS_EIP(%esp)
	jne    1f
	PUBLIC(x86_rpc_redirection_iret)
	movl   %edi, %fs:x86_rpc_redirection_iret+OFFSET_IRREGS_EIP /* EIP := EDI */
	jmp    2f
1:	movl   %edi, 12+OFFSET_IRREGS_EIP(%esp) /* EIP := EDI */
2:	movl   %ebp, 12+OFFSET_IRREGS_ESP(%esp) /* ESP := EBP */
	sti    /* Re-enable interrupts now that all async-critical components were serviced. */

	/* Restore user-space segment registers (NOTE: %gs already contains the user-space value) */
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds

	/* At this point, most of the original user-space CPU context from the point
	 * when the `sysenter' instruction was executed has been restored. Additionally,
	 * we have already applied the required register transformations for safely
	 * returning to user-space once we're done here.
	 * -> With all of this done, we can now continue handling the sysenter as
	 *    though the CPU had supported the instruction from the get-go, using
	 *    the same assembly-level wrappers that would normally be used for
	 *    routing a real sysenter system call invocation. */
#ifndef CONFIG_NO_SYSCALL_TRACING
	INTERN(syscall_tracing_enabled)
	cmpb   $0, %ss:syscall_tracing_enabled
	jne    .Ldo_prepared_sysenter_traced /* With tracing enabled... */
#endif
	jmp    .Ldo_prepared_sysenter
	.cfi_endproc
END(x86_sysenter_emulation)



.section .text
INTERN_FUNCTION(x86_lcall7_main)
	/* Main entry point for `lcall $7'-style system calls */
	.cfi_startproc simple
	.cfi_signal_frame
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
	.cfi_endproc

INTERN_FUNCTION(x86_lcall7_main_iret)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	INTERN(x86_syscall_lcall7_personality)
	.cfi_personality 0, x86_syscall_lcall7_personality
	.cfi_lsda 0, -1
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12

	/* Save callee-clobber register */
	pushl_cfi_r %ecx
	pushl_cfi_r %edx

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
	movl   20(%esp), %ecx /* USER_EIP */
	/* lcall $7, $? -- { 0x9a, ?, ?, ?, ?, 0x07, 0x00 } */
	movb   -7(%ecx), %al
	cmpb   $0x9a, %al
	jne    2f             /* Not invoked as `lcall $7, $?' */
	movw   -2(%ecx), %ax
	cmpw   $0x0007, %ax
	jne    2f             /* Not invoked as `lcall $7, $?' */
	movl   -6(%ecx), %eax /* EDX = ? (from `lcall $7, $?') */
	testl  %eax, %eax
	jz     2f             /* Invoked as `lcall $7, $0' (use the original %eax as sysno) */
	movl   %eax, %edx
2:	/* At this point we've got the intended sysno (in `%edx')! */
	pushl_cfi %edx
	movl   %esp, %ecx

	INTERN(x86_lcall7_syscall_main)
	call   x86_lcall7_syscall_main
	INTERN(x86_lcall7_syscall_guard)
x86_lcall7_syscall_guard = .

	popl_cfi   %ecx  /* popl <void> */
	popl_cfi_r %edx
	popl_cfi_r %ecx

	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds

	iret
	.cfi_endproc
END(x86_lcall7_main_iret)
END(x86_lcall7_main)



.section .text.hot
INTERN_FUNCTION(x86_sysenter_main)
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %esp, 0
	.cfi_register %esp, %ebp /* EBP is the designated return-sp register */
	.cfi_register %eip, %edi /* EDI is the designated return-pc register */
	/* `IA32_SYSENTER_ESP' points at the ESP0 field of the CPU's TSS
	 * In other words: we only need to replace ESP with its own
	 * dereference, and we already have `THIS_TASK->t_stackend'. */
	movl   %ss:0(%esp), %esp
	/* Construct an IRET tail. */
	pushl  $(SEGMENT_USER_DATA_RPL) /* %ss */
	pushl  %ebp                   /* %useresp */
	pushfl
	orl    $(EFLAGS_IF), %ss:(%esp)
	.cfi_reg_offset %eflags, 0, %esp
	pushl  $(SEGMENT_USER_CODE_RPL) /* %cs */
	.cfi_reg_offset %eflags, 4, %esp
	pushl  %edi                   /* %eip */
	.cfi_reg_offset %eflags, 8, %esp

	/* Switch over to IRET signal framing */
/*	.cfi_def_cfa %esp, 0 */
	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss
	/* Enable interrupts. */
	sti
.Ldo_prepared_sysenter:
	cmpl   $__NR_syscall_max, %eax
	ja     1f
	jmpl   *%ss:__asm32_syscallrouter_sysenter(,%eax,4)
1:	cmpl   $__NR_exsyscall_min, %eax
	jb     __asm32_sysenter_invalid
	cmpl   $__NR_exsyscall_max, %eax
	ja     __asm32_sysenter_invalid
	jmpl   *%ss:__asm32_exsyscallrouter_sysenter - ((__NR_exsyscall_min * 4) & 0xffffffff)(,%eax,4)
	.cfi_endproc
END(x86_sysenter_main)

.section .text.hot
INTERN(__x86_idtdpl_syscall)
	__x86_idtdpl_syscall = 3
INTERN_FUNCTION(x86_idt_syscall)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	cmpl   $__NR_syscall_max, %eax
	ja     1f
	jmpl   *%ss:__asm32_syscallrouter_int80(,%eax,4)
1:	cmpl   $__NR_exsyscall_min, %eax
	jb     __asm32_int80_invalid
	cmpl   $__NR_exsyscall_max, %eax
	ja     __asm32_int80_invalid
	jmpl   *%ss:__asm32_exsyscallrouter_int80 - ((__NR_exsyscall_min * 4) & 0xffffffff)(,%eax,4)
	.cfi_endproc
END(x86_idt_syscall)


#define TEST_DOUBLE_WIDE(sysno_reg,tempreg_l,tempreg_b,segment_prefix)           \
	cmpl   $__NR_syscall_max, sysno_reg;                                         \
	ja     1234f;                                                                \
	movl   sysno_reg, tempreg_l;                                                 \
	shrl   $1, tempreg_l;                                                        \
	EXTERN(x86_syscall_register_count);                                          \
	movb   segment_prefix x86_syscall_register_count(,tempreg_l,1), tempreg_b;   \
	jmp    1235f;                                                                \
1234:                                                                            \
	subl   $__NR_exsyscall_min, sysno_reg;                                       \
	jb    .Lgot_sysenter_args;                                                   \
	cmpl   $(__NR_exsyscall_max - __NR_exsyscall_min), sysno_reg;                \
	ja    .Lgot_sysenter_args;                                                   \
	movl   sysno_reg, tempreg_l;                                                 \
	shrl   $1, tempreg_l;                                                        \
	EXTERN(x86_exsyscall_register_count);                                        \
	movb   segment_prefix x86_exsyscall_register_count(,tempreg_l,1), tempreg_b; \
1235:                                                                            \
	testl  $1, sysno_reg;                                                        \
	jz     1234f;                                                                \
	shrb   $4, tempreg_b;                                                        \
1234:                                                                            \
	testb  $0x8, tempreg_b;                                                      \
/**/


#ifndef CONFIG_NO_SYSCALL_TRACING
.section .text.hot
INTERN_FUNCTION(x86_sysenter_main_traced)
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %esp, 0
	.cfi_register %esp, %ebp /* EBP is the designated return-sp register */
	.cfi_register %eip, %edi /* EDI is the designated return-pc register */
	/* `IA32_SYSENTER_ESP' points at the ESP0 field of the CPU's TSS
	 * In other words: we only need to replace ESP with its own
	 * dereference, and we already have `THIS_TASK->t_stackend'. */
	movl   %ss:0(%esp), %esp
	/* Construct an IRET tail. */
	pushl  $(SEGMENT_USER_DATA_RPL) /* %ss */
	pushl  %ebp                   /* %useresp */
	pushfl
	orl    $(EFLAGS_IF), %ss:(%esp)
	.cfi_reg_offset %eflags, 0, %esp
	pushl  $(SEGMENT_USER_CODE_RPL) /* %cs */
	.cfi_reg_offset %eflags, 4, %esp
	pushl  %edi                   /* %eip */

	/* With the IRET tail constructed, start a new CFI function with the SIGNAL_FRAME
	 * property enabled, thus allowing for normal system call return behavior. */
/*	.cfi_def_cfa %esp, 0 */
	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss
	/* Enable interrupts. */
	sti
.Ldo_prepared_sysenter_traced:

	/* Trace this system call invocation! */
	pushfl_cfi_r

	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -8
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -12
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -16

	pushl_cfi   $0   /* ARG[5] */
	pushl_cfi   $0   /* ARG[4] */
	pushl_cfi_r %esi /* ARG[3] */
	pushl_cfi_r %edx /* ARG[2] */
	pushl_cfi_r %ecx /* ARG[1] */
	pushl_cfi_r %ebx /* ARG[0] */
	pushl_cfi_r %eax /* SYSNO */

	/* Load kernel segments. */
	movl   $(SEGMENT_USER_DATA_RPL), %ecx
	movl   %ecx, %ds
	movl   %ecx, %es
	movl   $(SEGMENT_KERNEL_FSBASE), %ecx
	movl   %ecx, %fs

	/* Load ARG[4] / ARG[5] if necessary */
	cmpl   $__NR_syscall_max, %eax
	ja     1f
	movl   %eax, %ecx
	shrl   $1, %ecx
	EXTERN(x86_syscall_register_count)
	movb   x86_syscall_register_count(,%ecx,1), %cl
	jmp   .Lgot_mask
1:	subl   $__NR_exsyscall_min, %eax
	jb    .Lgot_sysenter_args
	cmpl   $(__NR_exsyscall_max - __NR_exsyscall_min), %eax
	ja    .Lgot_sysenter_args
	movl   %eax, %ecx
	shrl   $1, %ecx
	EXTERN(x86_exsyscall_register_count)
	movb   x86_exsyscall_register_count(,%ecx,1), %cl
.Lgot_mask:
	testl  $1, %eax
	jz     1f
	shrb   $4, %cl
1:	andb   $0x7, %cl
	cmpb   $4, %cl
	jbe    .Lgot_sysenter_args
	/* Must load one (%cl == 5) or two (%cl == 6) arguments */
	cmpl   $KERNEL_BASE, %ebp
	jae    .Lbad_args_pointer
	movl   0(%ebp), %eax
	movl   %eax, 20(%esp) /* ARG[4] */
	cmpb   $5, %cl
	jbe    .Lgot_sysenter_args
	/* Must also load the six'th argument! */
	movl   4(%ebp), %eax
	movl   %eax, 24(%esp) /* ARG[5] */
.Lgot_sysenter_args:

	/* Actually call through to the system call tracer. */
	movl   %esp, %ecx
	call   syscall_trace

	.cfi_remember_state
	popl_cfi_r %eax /* SYSNO */
	popl_cfi_r %ebx /* ARG[0] */
	popl_cfi_r %ecx /* ARG[1] */
	popl_cfi_r %edx /* ARG[2] */
	popl_cfi_r %esi /* ARG[3] */
	addl   $8, %esp
	.cfi_adjust_cfa_offset -8

	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds

	popfl_cfi_r

	cmpl   $__NR_syscall_max, %eax
	ja     1f
	jmpl   *%ss:__asm32_syscallrouter_sysenter(,%eax,4)
1:	cmpl   $__NR_exsyscall_min, %eax
	jb     __asm32_sysenter_invalid
	cmpl   $__NR_exsyscall_max, %eax
	ja     __asm32_sysenter_invalid
	jmpl   *%ss:__asm32_exsyscallrouter_sysenter - ((__NR_exsyscall_min * 4) & 0xffffffff)(,%eax,4)
	.cfi_restore_state
.Lbad_args_pointer:
	popl_cfi_r %eax /* SYSNO */
	popl_cfi_r %ebx /* ARG[0] */
	popl_cfi_r %ecx /* ARG[1] */
	popl_cfi_r %edx /* ARG[2] */
	popl_cfi_r %esi /* ARG[3] */
	addl   $8, %esp
	.cfi_adjust_cfa_offset -8
	jmp    __asm32_bad_sysenter_extension
	.cfi_endproc
END(x86_sysenter_main_traced)
#endif /* !CONFIG_NO_SYSCALL_TRACING */


#ifndef CONFIG_NO_SYSCALL_TRACING
.section .text.hot
INTERN_FUNCTION(x86_idt_syscall_traced)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	/* Trace this system call invocation! */
	pushfl_cfi_r

	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -8
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -12
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -16

	pushl_cfi_r %ebp /* ARG[5] */
	pushl_cfi_r %edi /* ARG[4] */
	pushl_cfi_r %esi /* ARG[3] */
	pushl_cfi_r %edx /* ARG[2] */
	pushl_cfi_r %ecx /* ARG[1] */
	pushl_cfi_r %ebx /* ARG[0] */
	pushl_cfi_r %eax /* SYSNO */

	/* Load kernel segments. */
	movl   $(SEGMENT_USER_DATA_RPL), %eax
	movl   %eax, %ds
	movl   %eax, %es
	movl   $(SEGMENT_KERNEL_FSBASE), %eax
	movl   %eax, %fs

	movl   %esp, %ecx
	call   syscall_trace

	popl_cfi_r %eax /* SYSNO */
	popl_cfi_r %ebx /* ARG[0] */
	popl_cfi_r %ecx /* ARG[1] */
	popl_cfi_r %edx /* ARG[2] */
	popl_cfi_r %esi /* ARG[3] */
	popl_cfi_r %edi /* ARG[4] */
	popl_cfi_r %ebp /* ARG[5] */

	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds

	popfl_cfi_r

	cmpl   $__NR_syscall_max, %eax
	ja     1f
	jmpl   *%ss:__asm32_syscallrouter_int80(,%eax,4)
1:	cmpl   $__NR_exsyscall_min, %eax
	jb     __asm32_int80_invalid
	cmpl   $__NR_exsyscall_max, %eax
	ja     __asm32_int80_invalid
	jmpl   *%ss:__asm32_exsyscallrouter_int80 - ((__NR_exsyscall_min * 4) & 0xffffffff)(,%eax,4)
	.cfi_endproc
END(x86_idt_syscall_traced)
#endif /* !CONFIG_NO_SYSCALL_TRACING */


.section .text.cold
INTERN_FUNCTION(__asm32_bad_sysenter_extension)
	/* Called when the %ebp pointer of a sysenter callback
	 * is faulty (aka: points into kernel-space) */
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, -1
	.cfi_signal_frame
	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss
	.cfi_def_cfa %esp, 12
	.cfi_restore_iret_gs
	.cfi_restore_iret_fs_or_offset -4
	.cfi_restore_iret_es_or_offset -8
	.cfi_restore_iret_ds_or_offset -12

	/* Check IRET.EFLAGS.CF if an exception should be thrown */
	testl  $EFLAGS_CF, %ss:12 + OFFSET_IRREGS_EFLAGS(%esp)
	jnz    1f

	/* Check if we must sign-extend the error return value. */
	pushl_cfi_r %ecx
	TEST_DOUBLE_WIDE(%eax,%ecx,%cl,%ss:)
	popl_cfi_r %ecx
	jz     1f
	movl   $-1, %edx
1:	movl   $-EFAULT, %eax

	movl   $-1, %edx
	.cfi_remember_state

	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds

	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_restore_state
1:	/* Preserve clobber registers for unwinding */
	pushl_cfi_r %edx
	pushl_cfi_r %ecx
	pushl_cfi_r %eax
	/* Make sure that kernel segments have been loaded */
	movl   $(SEGMENT_USER_DATA_RPL), %eax
	movl   %eax, %ds
	movl   %eax, %es
	movl   $(SEGMENT_KERNEL_FSBASE), %eax
	movl   %eax, %fs
	/* Throw an E_SEGFAULT exception! */
	pushl_cfi $E_SEGFAULT_CONTEXT_FAULT
	pushl_cfi %ebp
	pushl_cfi $2
	pushl_cfi $ERROR_CODEOF(E_SEGFAULT_UNMAPPED)
	call   error_thrown
	.cfi_endproc
END(__asm32_bad_sysenter_extension)



.section .text.cold
INTERN_FUNCTION(__asm32_int80_invalid)
	/* For `int 80h' system calls:
	 *   Called when a system call number hasn't been assigned (%eax:sysno) */
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, (-1 & ~0x40000000)
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0

	/* Check IRET.EFLAGS.CF if an exception should be thrown */
	testl  $EFLAGS_CF, %ss:OFFSET_IRREGS_EFLAGS(%esp)
	jnz    1f
	movl   $-ENOSYS, %eax
	iret
1:
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12

	pushl_cfi_r %ebp /* ARG[5] */
	pushl_cfi_r %edi /* ARG[4] */
	pushl_cfi_r %esi /* ARG[3] */
	pushl_cfi_r %edx /* ARG[2] */
	pushl_cfi_r %ecx /* ARG[1] */
	pushl_cfi_r %ebx /* ARG[0] */
	pushl_cfi_r %eax /* SYSNO */

	movl   $(SEGMENT_USER_DATA_RPL), %eax
	movl   %eax, %ds
	movl   %eax, %es
	movl   $(SEGMENT_KERNEL_FSBASE), %eax
	movl   %eax, %fs

	/* Throw an `E_UNKNOWN_SYSTEMCALL' exception */
	pushl_cfi $7
	pushl_cfi $ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)
	call   error_thrown
	.cfi_endproc
END(__asm32_int80_invalid)


.section .text.cold
PRIVATE_FUNCTION(copy_extended_user_arguments)
	.cfi_startproc
	EXCEPT_HANDLERS_START
		EXCEPT_HANDLERS_CATCH(
			E_SEGFAULT,
			.Lsysenter_guard_start,
			.Lsysenter_guard_end,
			.Lsysenter_guard_entry)
	EXCEPT_HANDLERS_END
	cmpl   $KERNEL_BASE, %ebp
	jae    1f
.Lsysenter_guard_start:
	movl   0(%ebp), %eax
	movl   %eax, 24(%esp) /* ARG[4] */
	movl   4(%ebp), %eax
.Lsysenter_guard_end:
	movl   %eax, 28(%esp) /* ARG[5] */
.Lsysenter_guard_entry:
1:	ret
	.cfi_endproc
END(copy_extended_user_arguments)

.section .text.cold
INTERN_FUNCTION(__asm32_sysenter_invalid)
	/* For `sysenter' system calls:
	 *   Called when a system call number hasn't been assigned (%eax:sysno) */
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, -1
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	/* Check IRET.EFLAGS.CF if an exception should be thrown */
	testl  $EFLAGS_CF, %ss:OFFSET_IRREGS_EFLAGS(%esp)
	jnz    1f
	movl   $-ENOSYS, %eax
	iret
1:
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12

	pushl_cfi $0 /* Make space for ARG5 */
	pushl_cfi $0 /* Make space for ARG4 */
	pushl_cfi_r %esi /* ARG[3] */
	pushl_cfi_r %edx /* ARG[2] */
	pushl_cfi_r %ecx /* ARG[1] */
	pushl_cfi_r %ebx /* ARG[0] */
	pushl_cfi_r %eax /* SYSNO */

	/* Load kernel segments. */
	movl   $(SEGMENT_USER_DATA_RPL), %eax
	movl   %eax, %ds
	movl   %eax, %es
	movl   $(SEGMENT_KERNEL_FSBASE), %eax
	movl   %eax, %fs

	call   copy_extended_user_arguments

	/* Throw an `E_UNKNOWN_SYSTEMCALL' exception */
	pushl_cfi $7
	pushl_cfi $ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)
	call   error_thrown
	.cfi_endproc
END(__asm32_sysenter_invalid)



.section .text.cold
#define SYS_INVALID_ENCODE_COUNT(count) (count+1)

/* Called when a system call is recognized, but hasn't been implemented yet */
INTERN_FUNCTION(sys_invalid0)
	.cfi_startproc
	movl   $(SYS_INVALID_ENCODE_COUNT(0)), %ecx
.Lsys_invalid_common:
	xchgl  0(%esp), %eax
	.cfi_register %eip, %eax
	pushl_cfi %ecx
	pushl_cfi $ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)
	call   error_thrown
	.cfi_endproc
END(sys_invalid0)
.cfi_startproc
INTERN_FUNCTION(sys_invalid1)
	movl   $(SYS_INVALID_ENCODE_COUNT(1)), %ecx
	jmp .Lsys_invalid_common
END(sys_invalid1)
INTERN_FUNCTION(sys_invalid2)
	movl   $(SYS_INVALID_ENCODE_COUNT(2)), %ecx
	jmp .Lsys_invalid_common
END(sys_invalid2)
INTERN_FUNCTION(sys_invalid3)
	movl   $(SYS_INVALID_ENCODE_COUNT(3)), %ecx
	jmp .Lsys_invalid_common
END(sys_invalid3)
INTERN_FUNCTION(sys_invalid4)
	movl   $(SYS_INVALID_ENCODE_COUNT(4)), %ecx
	jmp .Lsys_invalid_common
END(sys_invalid4)
INTERN_FUNCTION(sys_invalid5)
	movl   $(SYS_INVALID_ENCODE_COUNT(5)), %ecx
	jmp .Lsys_invalid_common
END(sys_invalid5)
INTERN_FUNCTION(sys_invalid6)
	movl   $(SYS_INVALID_ENCODE_COUNT(6)), %ecx
	jmp .Lsys_invalid_common
END(sys_invalid6)
.cfi_endproc

#include "unimplemented32.c.inl"






/* Emulate a system call invocation, with arguments passed via the
 * standard argument passage mechanism, using the given `regs'.
 * On i386, this means that arguments are found in `regs->ics_irregs_u.ir_esp'
 * @param: sysno:         The system call ID that is being invoked.
 * @param: enable_except: When true, enable support for exceptions.
 *                        Otherwise, translate exceptions to errno codes,
 *                        and write them into the return register of `regs'. */
//PUBLIC struct icpustate *FCALL
//syscall_emulate_callback(struct icpustate *__restrict regs,
//                         uintptr_t sysno,
//                         bool enable_except)
.section .text
PUBLIC_FUNCTION(syscall_emulate_callback)
	.cfi_startproc
	INTERN(x86_syscall_emulate_callback_personality)
	.cfi_personality 0, x86_syscall_emulate_callback_personality
	pushl_cfi   %edx /* Backup `sysno' for unwinding (s.a. `x86_syscall_emulate_callback_personality') */
	pushl_cfi   %ecx /* Backup `regs' for unwinding (s.a. `x86_syscall_emulate_callback_personality') */
	pushl_cfi_r %edi
	pushl_cfi_r %esi
	movl   %ecx, %edi

	/* Allocate stack memory for the system call arguments. */
	subl   $24, %esp
	.cfi_adjust_cfa_offset 24

	/* Figure out how many arguments need to be copied. */
	cmpl   $__NR_syscall_max, %edx
	ja     1f
	movl   %edx, %eax
	shrl   $1, %eax
	EXTERN(x86_syscall_register_count)
	movb   x86_syscall_register_count(,%eax,1), %al
	jmp   .Lgot_mask_emu
1:	subl   $__NR_exsyscall_min, %edx
	jb    .Linvalid_sysno
	cmpl   $(__NR_exsyscall_max - __NR_exsyscall_min), %edx
	ja    .Linvalid_sysno
	movl   %edx, %eax
	shrl   $1, %eax
	EXTERN(x86_exsyscall_register_count)
	movb   x86_exsyscall_register_count(,%eax,1), %al
.Lgot_mask_emu:
	testl  $1, %edx
	jz     1f
	shrb   $4, %al
1:	testb  $0x8, %al
	setnz  %cl  /* Used below by `testb  %cl, %cl /* Check if the return value needs to be extended...' */
	andb   $0x7, %al
	movzbl %al, %eax
	movl   OFFSET_ICPUSTATE_IRREGS+OFFSET_IRREGS_ESP(%edi), %esi
	jmp   *.Larguments_copy_jump_table(,%eax,4)
.pushsection .rodata
INTERN_OBJECT(.Larguments_copy_jump_table)
	.long  .Lcopy0
	.long  .Lcopy1
	.long  .Lcopy2
	.long  .Lcopy3
	.long  .Lcopy4
	.long  .Lcopy5
	.long  .Lcopy6
END(.Larguments_copy_jump_table)
.popsection
INTERN(x86_syscall_emulate_callback_guard_begin)
INTERN(x86_syscall_emulate_callback_guard_end)
x86_syscall_emulate_callback_guard_begin = .

	/* Copy arguments. */
#define COPY_ARGUMENT(offset) movl offset(%esi), %eax; movl %eax, offset(%esp)
.Lcopy6:
	COPY_ARGUMENT(20)
.Lcopy5:
	COPY_ARGUMENT(16)
.Lcopy4:
	COPY_ARGUMENT(12)
.Lcopy3:
	COPY_ARGUMENT(8)
.Lcopy2:
	COPY_ARGUMENT(4)
.Lcopy1:
	COPY_ARGUMENT(0)
#undef COPY_ARGUMENT
.Lcopy0:

	.cfi_remember_state
	/* Load the C-level prototype of the system call that should be invoked. */
	EXTERN(__c32_syscallrouter)
	EXTERN(__c32_exsyscallrouter)
	cmpl   $__NR_syscall_max, %edx
	ja     1f
	movl   __c32_syscallrouter(,%edx,4), %edx
	jmp    2f
1:	cmpl   $__NR_exsyscall_min, %edx
	jb     .Linvalid_sysno
	cmpl   $__NR_exsyscall_max, %edx
	ja     .Linvalid_sysno
	movl   __c32_exsyscallrouter - ((__NR_exsyscall_min * 4) & 0xffffffff)(,%edx,4), %edx
2:

	/* Actually invoke the system call. */
	testb  %cl, %cl /* Check if the return value needs to be extended. */
	jz     1f
	call  *%edx
	movl   %edx, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EDX(%edi)
	jmp    2f
1:	call  *%edx
2:	movl   %eax, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EAX(%edi)

x86_syscall_emulate_callback_guard_end = .

	movl   %edi, %eax
	addl   $24, %esp
	.cfi_adjust_cfa_offset -24
	popl_cfi_r %esi
	popl_cfi_r %edi
	addl   $8, %esp
	.cfi_adjust_cfa_offset -8
	ret    $4
.Linvalid_sysno:
	.cfi_restore_state
	addl   $24, %esp
	.cfi_adjust_cfa_offset -24
	movl   %edi, %eax /* EAX = regs */
	popl_cfi_r %esi
	popl_cfi_r %edi   /* Restore EDI */
	addl   $8, %esp
	.cfi_adjust_cfa_offset -8
	/* Check if we're simply supposed to return -ENOSYS */
	cmpl   $0, 4(%esp)
	jnz    1f
	/* Just return -ENOSYS to user-space */
	movl   $-ENOSYS, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EAX(%eax)
	ret    $4
1:	.cfi_endproc
	.cfi_startproc
	pushl_cfi $0   /* ARG[5] */
	pushl_cfi $0   /* ARG[4] */
	pushl_cfi $0   /* ARG[3] */
	pushl_cfi $0   /* ARG[2] */
	pushl_cfi $0   /* ARG[1] */
	pushl_cfi $0   /* ARG[0] */
	pushl_cfi %edx /* SYSNO */

	/* Try to load as many system call arguments as possible. */
	movl   OFFSET_ICPUSTATE_IRREGS+OFFSET_IRREGS_ESP(%eax), %eax
	cmpl   $KERNEL_BASE, %eax
	jae    1f
	EXCEPT_HANDLERS_START
		EXCEPT_HANDLERS_CATCH(
			E_SEGFAULT,
			.Linvalid_sysno_guard_start,
			.Linvalid_sysno_guard_end,
			.Linvalid_sysno_guard_entry)
	EXCEPT_HANDLERS_END
.Linvalid_sysno_guard_start:
#define COPY_ARGUMENT(offset) movl offset(%eax), %edx; movl %edx, (offset+4)(%esp)
	COPY_ARGUMENT(0)  /* ARG[0] */
	COPY_ARGUMENT(4)  /* ARG[1] */
	COPY_ARGUMENT(8)  /* ARG[2] */
	COPY_ARGUMENT(12) /* ARG[3] */
	COPY_ARGUMENT(16) /* ARG[4] */
	COPY_ARGUMENT(20) /* ARG[5] */
#undef COPY_ARGUMENT
.Linvalid_sysno_guard_end:
.Linvalid_sysno_guard_entry:

1:	/* Throw an `E_UNKNOWN_SYSTEMCALL' exception */
	pushl_cfi $7
	pushl_cfi $ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)
	call   error_thrown
	.cfi_endproc
END(syscall_emulate_callback)





.section .text
PUBLIC_FUNCTION(syscall_emulate_int80)
	.cfi_startproc
	INTERN(syscall_emulate_int80_personality)
	.cfi_personality 0, syscall_emulate_int80_personality

	movl   OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EAX(%ecx), %eax

	/* Push system call arguments. */
	pushl_cfi %ecx /* Backup `regs' for unwinding (s.a. `syscall_emulate_int80_personality') */
	pushl_cfi OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EBP(%ecx) /* ARG[5] */
	pushl_cfi OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EDI(%ecx) /* ARG[4] */
	pushl_cfi OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_ESI(%ecx) /* ARG[3] */
	pushl_cfi OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EDX(%ecx) /* ARG[2] */
	pushl_cfi OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_ECX(%ecx) /* ARG[1] */
	pushl_cfi OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EBX(%ecx) /* ARG[0] */

	/* Load the C-level prototype of the system call that should be invoked. */
	EXTERN(__c32_syscallrouter)
	EXTERN(__c32_exsyscallrouter)
	cmpl   $__NR_syscall_max, %eax
	ja     1f
	movl   __c32_syscallrouter(,%eax,4), %edx
	jmp    2f
1:	cmpl   $__NR_exsyscall_min, %eax
	jb     .Linvalid_sysno_int80
	cmpl   $__NR_exsyscall_max, %eax
	ja     .Linvalid_sysno_int80
	movl   __c32_exsyscallrouter - ((__NR_exsyscall_min * 4) & 0xffffffff)(,%eax,4), %edx
2:
	/* Actually invoke the system call. */
	call   *%edx
INTERN(x86_syscall_emulate_int80_guard)
x86_syscall_emulate_int80_guard = .
	addl   $24, %esp
	.cfi_adjust_cfa_offset -24
	popl_cfi %ecx

	/* Store the regular system call return value. (and check for it being double-wide) */
	xchgl  OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EAX(%ecx), %eax
	pushl_cfi %ecx
	TEST_DOUBLE_WIDE(%eax,%ecx,%cl,)
	popl_cfi %ecx
	jz     1f
	movl   %edx, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EAX(%ecx)
1:	movl   %ecx, %eax
	ret
	.cfi_adjust_cfa_offset 28
.Linvalid_sysno_int80:
	/* Check if we're supposed to return -ENOSYS. */
	testl  $EFLAGS_CF, OFFSET_ICPUSTATE_IRREGS+OFFSET_IRREGS_EFLAGS(%ecx)
	jnz    1f
	addl   $28, %esp
	.cfi_adjust_cfa_offset -28
	movl   $-ENOSYS, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EAX(%ecx)
	movl   %ecx, %eax
	ret
	.cfi_adjust_cfa_offset 28
1:	pushl_cfi %eax /* SYSNO */
	/* Throw an `E_UNKNOWN_SYSTEMCALL' exception */
	pushl_cfi $7
	pushl_cfi $ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)
	call   error_thrown
	.cfi_endproc
END(syscall_emulate_int80)






.section .text
PUBLIC_FUNCTION(syscall_emulate_sysenter)
	.cfi_startproc
	/* Load return registers according to our sysenter ABI. */
	/* state->ics_irregs_u.ir_eip = state->ics_gpregs.gp_edi; */
	movl   OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EDI(%ecx), %eax
	movl   %eax, OFFSET_ICPUSTATE_IRREGS+OFFSET_IRREGS_EIP(%ecx)
	/* state->ics_irregs_u.ir_esp = state->ics_gpregs.gp_ebp; */
	movl   OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EBP(%ecx), %eax
	movl   %eax, OFFSET_ICPUSTATE_IRREGS+OFFSET_IRREGS_ESP(%ecx)

	/* TODO */

	movl   %ecx, %eax
	ret
	.cfi_endproc
END(syscall_emulate_sysenter)


























