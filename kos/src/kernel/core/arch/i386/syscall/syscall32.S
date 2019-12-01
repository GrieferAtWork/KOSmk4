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

#include <librpc/rpc.h>


EXTERN(__x86_asm32_int80_break)
EXTERN(__x86_asm32_sysenter_break)
EXTERN(x86_sysroute0_asm32_int80)
EXTERN(x86_sysroute1_asm32_int80)
EXTERN(x86_sysroute0_asm32_sysenter)
EXTERN(x86_sysroute1_asm32_sysenter)


.section .text
PUBLIC_FUNCTION(x86_syscall_emulate_int80h_r)
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
	EXTERN(x86_rpc_user_redirection)
	cmpl   $x86_rpc_user_redirection, 12+OFFSET_IRREGS_EIP(%esp)
	jne    1f
	EXTERN(this_x86_rpc_redirection_iret)
	movl   %edi, %fs:this_x86_rpc_redirection_iret+OFFSET_IRREGS_EIP /* EIP := EDI */
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
	EXTERN(syscall_tracing_enabled)
	cmpb   $0, %ss:syscall_tracing_enabled
	jne    x86_idt_syscall_traced /* With tracing enabled... */
#endif
	jmp    x86_idt_syscall
	.cfi_endproc
END(x86_syscall_emulate_int80h_r)




.section .text
PUBLIC_FUNCTION(x86_syscall_emulate_sysenter_r)
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
	EXTERN(x86_rpc_user_redirection)
	cmpl  $x86_rpc_user_redirection, 12+OFFSET_IRREGS_EIP(%esp)
	jne    1f
	EXTERN(this_x86_rpc_redirection_iret)
	movl   %edi, %fs:this_x86_rpc_redirection_iret+OFFSET_IRREGS_EIP /* EIP := EDI */
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
	EXTERN(syscall_tracing_enabled)
	cmpb   $(0), %ss:syscall_tracing_enabled
	jne    .Ldo_prepared_sysenter_traced /* With tracing enabled... */
#endif
	jmp    .Ldo_prepared_sysenter
	.cfi_endproc
END(x86_syscall_emulate_sysenter_r)



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
	EXTERN(x86_syscall_lcall7_personality)
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

	EXTERN(x86_lcall7_syscall_main)
	call   x86_lcall7_syscall_main
INTERN_CONST(x86_lcall7_syscall_guard, .)

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
	pushl  %ebp                     /* %useresp */
	pushfl
	orl    $(EFLAGS_IF), %ss:(%esp)
	.cfi_reg_offset %eflags, 0, %esp
	pushl  $(SEGMENT_USER_CODE_RPL) /* %cs */
	.cfi_reg_offset %eflags, 4, %esp
	pushl  %edi                     /* %eip */
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
	cmpl   $(__NR_syscall0_max), %eax
	ja     1f
	jmpl   *%ss:x86_sysroute0_asm32_sysenter(,%eax,4)
1:	cmpl   $(__NR_syscall1_min), %eax
	jb     __x86_asm32_sysenter_break
	cmpl   $(__NR_syscall1_max), %eax
	ja     __x86_asm32_sysenter_break
	jmpl   *%ss:x86_sysroute1_asm32_sysenter - ((__NR_syscall1_min * 4) & 0xffffffff)(,%eax,4)
	.cfi_endproc
END(x86_sysenter_main)

.section .text.hot
INTERN_CONST(__x86_idtdpl_syscall, 3)
INTERN_FUNCTION(x86_idt_syscall)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	cmpl   $(__NR_syscall0_max), %eax
	ja     1f
	jmpl   *%ss:x86_sysroute0_asm32_int80(,%eax,4)
1:	cmpl   $(__NR_syscall1_min), %eax
	jb     __x86_asm32_int80_break
	cmpl   $(__NR_syscall1_max), %eax
	ja     __x86_asm32_int80_break
	jmpl   *%ss:(x86_sysroute1_asm32_int80 - ((__NR_syscall1_min * 4) & 0xffffffff))(,%eax,4)
	.cfi_endproc
END(x86_idt_syscall)


#define TEST_DOUBLE_WIDE(sysno_reg, tempreg_l, tempreg_b, segment_prefix)  \
	cmpl   $(__NR_syscall0_max), sysno_reg;                                \
	ja     1234f;                                                          \
	movl   sysno_reg, tempreg_l;                                           \
	shrl   $1, tempreg_l;                                                  \
	EXTERN(kernel_syscall0_regcnt);                                        \
	movb   segment_prefix kernel_syscall0_regcnt(,tempreg_l,1), tempreg_b; \
	jmp    1235f;                                                          \
1234:                                                                      \
	leal   -__NR_syscall1_min(sysno_reg), tempreg_l;                       \
	shrl   $1, tempreg_l;                                                  \
	EXTERN(kernel_syscall1_regcnt);                                        \
	movb   segment_prefix kernel_syscall1_regcnt(,tempreg_l,1), tempreg_b; \
1235:                                                                      \
	testl  $1, sysno_reg;                                                  \
	jz     1234f;                                                          \
	shrb   $4, tempreg_b;                                                  \
1234:                                                                      \
	testb  $0x8, tempreg_b;


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
	cmpl   $(__NR_syscall0_max), %eax
	ja     1f
	movl   %eax, %ecx
	shrl   $1, %ecx
	EXTERN(kernel_syscall0_regcnt)
	movb   kernel_syscall0_regcnt(,%ecx,1), %cl
	jmp   .Lgot_mask
1:	subl   $(__NR_syscall1_min), %eax
	jb    .Lgot_sysenter_args
	cmpl   $(__NR_syscall1_max - __NR_syscall1_min), %eax
	ja    .Lgot_sysenter_args
	movl   %eax, %ecx
	shrl   $1, %ecx
	EXTERN(kernel_syscall1_regcnt)
	movb   kernel_syscall1_regcnt(,%ecx,1), %cl
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

	cmpl   $(__NR_syscall0_max), %eax
	ja     1f
	jmpl   *%ss:x86_sysroute0_asm32_sysenter(,%eax,4)
1:	cmpl   $(__NR_syscall1_min), %eax
	jb     __x86_asm32_sysenter_break
	cmpl   $(__NR_syscall1_max), %eax
	ja     __x86_asm32_sysenter_break
	jmpl   *%ss:x86_sysroute1_asm32_sysenter - ((__NR_syscall1_min * 4) & 0xffffffff)(,%eax,4)
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

	cmpl   $(__NR_syscall0_max), %eax
	ja     1f
	jmpl   *%ss:x86_sysroute0_asm32_int80(,%eax,4)
1:	cmpl   $(__NR_syscall1_min), %eax
	jb     __x86_asm32_int80_break
	cmpl   $(__NR_syscall1_max), %eax
	ja     __x86_asm32_int80_break
	jmpl   *%ss:x86_sysroute1_asm32_int80 - ((__NR_syscall1_min * 4) & 0xffffffff)(,%eax,4)
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
	testl  $(EFLAGS_CF), %ss:12 + OFFSET_IRREGS_EFLAGS(%esp)
	jnz    1f

	/* Check if we must sign-extend the error return value. */
	pushl_cfi_r %ecx
	TEST_DOUBLE_WIDE(%eax, %ecx, %cl, %ss:)
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
INTERN_FUNCTION(__x86_asm32_int80_break)
	/* For `int 80h' system calls:
	 *   Called when a system call number hasn't been assigned (%eax:sysno) */
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, (-1 & ~0x40000000)
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0

	/* Check IRET.EFLAGS.CF if an exception should be thrown */
	testl  $(EFLAGS_CF), %ss:OFFSET_IRREGS_EFLAGS(%esp)
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
	pushl_cfi $(RPC_SYSCALL_INFO_METHOD_INT80H_32 | RPC_SYSCALL_INFO_FEXCEPT |  \
	            RPC_SYSCALL_INFO_FARGVALID(0) | RPC_SYSCALL_INFO_FARGVALID(1) | \
	            RPC_SYSCALL_INFO_FARGVALID(2) | RPC_SYSCALL_INFO_FARGVALID(3) | \
	            RPC_SYSCALL_INFO_FARGVALID(4) | RPC_SYSCALL_INFO_FARGVALID(5))
	pushl_cfi $(8)
	pushl_cfi $(ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL))
	call   error_thrown
	.cfi_endproc
END(__x86_asm32_int80_break)


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
	movl   $(RPC_SYSCALL_INFO_METHOD_SYSENTER_32 | RPC_SYSCALL_INFO_FEXCEPT |  \
	         RPC_SYSCALL_INFO_FARGVALID(0) | RPC_SYSCALL_INFO_FARGVALID(1) |   \
	         RPC_SYSCALL_INFO_FARGVALID(2) | RPC_SYSCALL_INFO_FARGVALID(3)), %eax
	cmpl   $(KERNEL_BASE), %ebp
	jae    1f
.Lsysenter_guard_start:
	movl   0(%ebp), %ecx
	movl   %ecx, 24(%esp) /* ARG[4] */
	orl    $(RPC_SYSCALL_INFO_FARGVALID(4)), %eax
	movl   4(%ebp), %ecx
.Lsysenter_guard_end:
	movl   %ecx, 28(%esp) /* ARG[5] */
	orl    $(RPC_SYSCALL_INFO_FARGVALID(5)), %eax
.Lsysenter_guard_entry:
1:	ret
	.cfi_endproc
END(copy_extended_user_arguments)

.section .text.cold
INTERN_FUNCTION(__x86_asm32_sysenter_break)
	/* For `sysenter' system calls:
	 *   Called when a system call number hasn't been assigned (%eax:sysno) */
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, -1
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	/* Check IRET.EFLAGS.CF if an exception should be thrown */
	testl  $(EFLAGS_CF), %ss:OFFSET_IRREGS_EFLAGS(%esp)
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
	pushl_cfi %eax /* Returned by `copy_extended_user_arguments()' */
	pushl_cfi $(8)
	pushl_cfi $(ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL))
	call   error_thrown
	.cfi_endproc
END(__x86_asm32_sysenter_break)



.section .text.cold
#define SYS_INVALID_ENCODE_COUNT(count) (count+2)

/* Called when a system call is recognized, but hasn't been implemented yet */
INTERN_FUNCTION(sys_invalid0)
	.cfi_startproc
	movl   $(SYS_INVALID_ENCODE_COUNT(0)), %ecx
.Lsys_invalid_common:
	xchgl  0(%esp), %eax
	.cfi_register %eip, %eax
	pushl_cfi $(0) /* flags (filled in later) */
	pushl_cfi %ecx /* argc */
	/* *(u32 *)(ESP + 4) = (RPC_SYSCALL_INFO_METHOD_OTHER_32 | RPC_SYSCALL_INFO_FEXCEPT |
	 *                      ((1 << (%ecx - 2)) - 1) << RPC_SYSCALL_INFO_FARGVALID_SHIFT); */
	subl   $(2), %ecx
	movl   $1, %edx
	shll   %cl, %edx
	decl   %edx
	shll   $(RPC_SYSCALL_INFO_FARGVALID_SHIFT), %edx
	orl    $(RPC_SYSCALL_INFO_METHOD_OTHER_32 | RPC_SYSCALL_INFO_FEXCEPT), %edx
	movl   %edx, 4(%esp) /* flags */
	pushl_cfi $(ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL))
	call   error_thrown
	.cfi_endproc
END(sys_invalid0)
.cfi_startproc
INTERN_FUNCTION(sys_invalid1)
	movl   $(SYS_INVALID_ENCODE_COUNT(1)), %ecx
	jmp    .Lsys_invalid_common
END(sys_invalid1)
INTERN_FUNCTION(sys_invalid2)
	movl   $(SYS_INVALID_ENCODE_COUNT(2)), %ecx
	jmp    .Lsys_invalid_common
END(sys_invalid2)
INTERN_FUNCTION(sys_invalid3)
	movl   $(SYS_INVALID_ENCODE_COUNT(3)), %ecx
	jmp    .Lsys_invalid_common
END(sys_invalid3)
INTERN_FUNCTION(sys_invalid4)
	movl   $(SYS_INVALID_ENCODE_COUNT(4)), %ecx
	jmp    .Lsys_invalid_common
END(sys_invalid4)
INTERN_FUNCTION(sys_invalid5)
	movl   $(SYS_INVALID_ENCODE_COUNT(5)), %ecx
	jmp    .Lsys_invalid_common
END(sys_invalid5)
INTERN_FUNCTION(sys_invalid6)
	movl   $(SYS_INVALID_ENCODE_COUNT(6)), %ecx
	jmp    .Lsys_invalid_common
END(sys_invalid6)
.cfi_endproc


#ifndef __NR32FEAT_DEFINED_SYSCALL_REGISTER_COUNT
#undef __WANT_SYSCALL_REGISTER_COUNT
#define __WANT_SYSCALL_REGISTER_COUNT 1
#include <asm/syscalls32_d.h>
#endif /* !__NR32FEAT_DEFINED_SYSCALL_REGISTER_COUNT */

/* Define all unimplemented system calls as weak aliases
 * of `sys_invalidN', where N is the register count */
#define __SYSINVALID_OF2(register_count) sys_invalid##register_count
#define __SYSINVALID_OF(register_count) __SYSINVALID_OF2(register_count)
#define __SYSCALL(name) \
	DEFINE_PUBLIC_WEAK_ALIAS(sys_##name, __SYSINVALID_OF(__NR32RC_##name))
#include <asm/ls-syscalls32.h>

