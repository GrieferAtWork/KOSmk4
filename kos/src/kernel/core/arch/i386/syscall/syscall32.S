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
EXTERN(x86_sysroute0_asm32_int80)
EXTERN(x86_sysroute1_asm32_int80)


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
	movl   %ecx, %esp /* No need to disable interrupts, since this stack switch is atomic! */
	.cfi_def_cfa_register %esp
	/* Restore user-space registers. */
	popal_cfi_r

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
#endif /* !CONFIG_NO_SYSCALL_TRACING */
	jmp    x86_idt_syscall
	.cfi_endproc
END(x86_syscall_emulate_int80h_r)




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

