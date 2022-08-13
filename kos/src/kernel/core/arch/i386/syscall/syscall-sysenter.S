/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_SYSENTER_S
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_SYSENTER_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <kernel/except.h>

#include <cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/compat.h>
#include <asm/instr/interrupt.h>
#include <asm/instr/ttest.h>
#include <kos/except.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/x86/gdt.h>
#include <kos/rpc.h>

#include <errno.h>

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
#ifndef __x86_64__
	cmpP   $(KERNELSPACE_BASE), %Pbp
	jae    .Lsysenter_guard_entry
#endif /* !__x86_64__ */
.Lsysenter_guard_start:
	movzlP 0(%Pbp), %Pax
	movP   %Pax,                             OFFSET_RPC_SYSCALL_INFO_REG(4)(%Psp)
	orP    $(RPC_SYSCALL_INFO_FREGVALID(4)), OFFSET_RPC_SYSCALL_INFO_FLAGS(%Psp)
	movzlP 4(%Pbp), %Pax
.Lsysenter_guard_end:
	movP   %Pax,                             OFFSET_RPC_SYSCALL_INFO_REG(5)(%Psp)
	orP    $(RPC_SYSCALL_INFO_FREGVALID(5)), OFFSET_RPC_SYSCALL_INFO_FLAGS(%Psp)
.Lsysenter_guard_entry:
	ret
	.cfi_endproc
END(copy_extended_user_arguments)









.section .text.cold
INTERN_FUNCTION(__x86_asm32_sysenter_break)
	/* For `sysenter' system calls:
	 *   Called when a system call number hasn't been assigned (%rax:sysno) */
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %Psp, 0

	/* Check IRET.EFLAGS.DF if an exception should be thrown */
#ifdef __x86_64__
	ttest  mask=EFLAGS_DF, loc=OFFSET_IRREGS_PFLAGS(%Psp)
#else /* __x86_64__ */
	ttest  mask=EFLAGS_DF, loc=OFFSET_IRREGS_PFLAGS(%Psp), seg=%ss
#endif /* !__x86_64__ */
	jnz    1f
	movP   $-ENOSYS, %Pax
#ifdef __x86_64__
	/* We can just use `sysret' as a drop-in replacement for `sysexit', since
	 * `sysret' doesn't clobber any  32-bit registers that `sysexit'  doesn't
	 * also clobber! */
	X86_IRET_BUT_PREFER_SYSRET32
#else /* __x86_64__ */
	iret
#endif /* !__x86_64__ */
1:

	/* Construct a `struct icpustate' */
	ASM_PUSH_ICPUSTATE_AFTER_HW_IRET_CFI_R

	/* Load kernel segments. */
#ifndef __x86_64__
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
#endif /* !__x86_64__ */

	/* Construct an on-stack `struct rpc_syscall_info' */
	pushP_cfi $(0) /* Make space for ARG5 */
	pushP_cfi $(0) /* Make space for ARG4 */
	pushP_cfi %Psi /* ARG[3] */
	pushP_cfi %Pdx /* ARG[2] */
	pushP_cfi %Pcx /* ARG[1] */
	pushP_cfi %Pbx /* ARG[0] */
	pushP_cfi %Pax /* SYSNO */
	pushP_cfi $(RPC_SYSCALL_INFO_METHOD_SYSENTER_32 | RPC_SYSCALL_INFO_FEXCEPT |  \
	            RPC_SYSCALL_INFO_FREGVALID(0) | RPC_SYSCALL_INFO_FREGVALID(1) |   \
	            RPC_SYSCALL_INFO_FREGVALID(2) | RPC_SYSCALL_INFO_FREGVALID(3))

	/* Copy additional arguments. */
	call   copy_extended_user_arguments

	/* Throw the `E_UNKNOWN_SYSTEMCALL' exception. */
	leaP   SIZEOF_RPC_SYSCALL_INFO(%Psp), %R_fcall0P
	movP   %Psp,                          %R_fcall1P
	EXTERN(userexcept_handler_nosys)
	call   userexcept_handler_nosys

	EXTERN(except_thrown)
	call   except_thrown
	.cfi_endproc
END(__x86_asm32_sysenter_break)



#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_SYSENTER_S */
