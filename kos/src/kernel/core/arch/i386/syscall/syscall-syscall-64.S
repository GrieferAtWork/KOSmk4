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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_SYSCALL_64_S
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_SYSCALL_64_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <kernel/except.h>

#include <cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/interrupt.h>
#include <asm/instr/movzxq.h>
#include <asm/instr/ttest.h>
#include <asm/syscalls64_d.h>
#include <kos/kernel/x86/gdt.h>
#include <kos/rpc.h>

#include <libunwind/cfi.h>









/************************************************************************/
/* SYSCALL ENTRY                                                        */
/************************************************************************/
.section .text.hot
PUBLIC_FUNCTION(x86_syscall64_syscall)
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %rsp, 0
	.cfi_register %rip, %rcx
	.cfi_register %rflags, %r11
	/* Because we can assume that we only get here from user-space with #IF enabled,
	 * we don't have to swapgs  or sti conditionally, but  can simply always do  so. */
	swapgs
	EXTERN(this_x86_sysret_iret)
	movq   %rsp, %gs:(this_x86_sysret_iret + OFFSET_IRREGS_RSP)
/*[[[cfi{arch='x86_64', register='%rsp'}
	ifnotimpl "KOS", 1f   # GDB doesn't understand `form_tls_address', so hide that fact
	push   @(this_x86_sysret_iret + OFFSET_IRREGS_RSP)
	form_tls_address
	deref
	ret
1:	push   %rsp
]]]*/
	.cfi_escape 22,7,18,47,3,0,75,79,83,47,7,0,8,this_x86_sysret_iret + OFFSET_IRREGS_RSP,155,6
	.cfi_escape 47,2,0,119,0
/*[[[end]]]*/

	EXTERN(this_x86_kernel_psp0)
	movq   %gs:this_x86_kernel_psp0, %rsp /* Load our kernel-space stack. */
	pushq_cfi $(SEGMENT_USER_DATA64_RPL)                              /* ir_ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %gs:(this_x86_sysret_iret + OFFSET_IRREGS_RSP) /* ir_rsp */
	.cfi_rel_offset %rsp, 0
	pushq_cfi %r11                                                    /* ir_rflags */
	.cfi_rel_offset %rflags, 0
	pushq_cfi $(SEGMENT_USER_CODE64_RPL)                              /* ir_cs */
	.cfi_rel_offset %cs, 0
	pushq_cfi %rcx                                                    /* ir_rip */
	.cfi_rel_offset %rip, 0
	sti
	/* And with that we've established an IRET tail! */

	/* Invocation of int80h from 64-bit code. */
.Lsyscall_syscall_64bit:
	cmpq   $(__NR64_syscall0_max), %rax
	ja     1f
	EXTERN(x86_sysroute0_asm64_syscall)
	jmpq   *(x86_sysroute0_asm64_syscall - ((__NR64_syscall0_min * 8) & 0xffffffffffffffff))(,%rax,8)
1:	cmpq   $(__NR64_syscall1_min), %rax
	EXTERN(__x86_asm64_syscall_break)
	jb     __x86_asm64_syscall_break
	cmpq   $(__NR64_syscall1_max), %rax
	ja     __x86_asm64_syscall_break
	EXTERN(x86_sysroute1_asm64_syscall)
	jmpq   *(x86_sysroute1_asm64_syscall - ((__NR64_syscall1_min * 8) & 0xffffffffffffffff))(,%rax,8)
	.cfi_endproc
END(x86_syscall64_syscall)













/************************************************************************/
/* INT 80H TRACED ENTRY                                                 */
/************************************************************************/
#ifndef CONFIG_NO_KERNEL_SYSCALL_TRACING
.section .text.hot
PUBLIC_FUNCTION(x86_syscall64_syscall_traced)
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %rsp, 0
	.cfi_register %rip, %rcx
	.cfi_register %rflags, %r11
	/* Because we can assume that we only get here from user-space with #IF enabled,
	 * we don't have to swapgs  or sti conditionally, but  can simply always do  so. */
	swapgs
	EXTERN(this_x86_sysret_iret)
	movq   %rsp, %gs:(this_x86_sysret_iret + OFFSET_IRREGS_RSP)
/*[[[cfi{arch='x86_64', register='%rsp'}
	ifnotimpl "KOS", 1f   # GDB doesn't understand `form_tls_address', so hide that fact
	push   @(this_x86_sysret_iret + OFFSET_IRREGS_RSP)
	form_tls_address
	deref
	ret
1:	push   %rsp
]]]*/
	.cfi_escape 22,7,18,47,3,0,75,79,83,47,7,0,8,this_x86_sysret_iret + OFFSET_IRREGS_RSP,155,6
	.cfi_escape 47,2,0,119,0
/*[[[end]]]*/

	EXTERN(this_x86_kernel_psp0)
	movq   %gs:this_x86_kernel_psp0, %rsp /* Load our kernel-space stack. */
	pushq_cfi $(SEGMENT_USER_DATA64_RPL)                              /* ir_ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %gs:(this_x86_sysret_iret + OFFSET_IRREGS_RSP) /* ir_rsp */
	.cfi_rel_offset %rsp, 0
	pushq_cfi %r11                                                    /* ir_rflags */
	.cfi_rel_offset %rflags, 0
	pushq_cfi $(SEGMENT_USER_CODE64_RPL)                              /* ir_cs */
	.cfi_rel_offset %cs, 0
	pushq_cfi %rcx                                                    /* ir_rip */
	.cfi_rel_offset %rip, 0
	sti
	/* And with that we've established an IRET tail! */

	pushq_cfi_r %rcx
	pushq_cfi_r %r11
	pushq_cfi_r %r9  /* ARG[5] */
	pushq_cfi_r %r8  /* ARG[4] */
	pushq_cfi_r %r10 /* ARG[3] */
	pushq_cfi_r %rdx /* ARG[2] */
	pushq_cfi_r %rsi /* ARG[1] */
	pushq_cfi_r %rdi /* ARG[0] */
	pushq_cfi_r %rax /* SYSNO */

	pushq_cfi $(RPC_SYSCALL_INFO_FREGVALID(0) | RPC_SYSCALL_INFO_FREGVALID(1) | \
	            RPC_SYSCALL_INFO_FREGVALID(2) | RPC_SYSCALL_INFO_FREGVALID(3) | \
	            RPC_SYSCALL_INFO_FREGVALID(4) | RPC_SYSCALL_INFO_FREGVALID(5) | \
	            RPC_SYSCALL_INFO_METHOD_INT80H_64)
	/* Check if exceptions are enabled. */
	ttest  mask=EFLAGS_DF, loc=%r11
	jz     1f
	orw    $(RPC_SYSCALL_INFO_FEXCEPT), 0(%rsp)
1:
	movq   %rsp, %rdi
	EXTERN(syscall_trace)
	call   syscall_trace

	popq_cfi %rax /* flags (pop_void) */
	popq_cfi_r %rax /* SYSNO */
	popq_cfi_r %rdi /* ARG[0] */
	popq_cfi_r %rsi /* ARG[1] */
	popq_cfi_r %rdx /* ARG[2] */
	popq_cfi_r %r10 /* ARG[3] */
	popq_cfi_r %r8  /* ARG[4] */
	popq_cfi_r %r9  /* ARG[5] */
	popq_cfi_r %r11
	popq_cfi_r %rcx
	jmp    .Lsyscall_syscall_64bit
	.cfi_endproc
END(x86_syscall64_syscall_traced)
#endif /* !CONFIG_NO_KERNEL_SYSCALL_TRACING */




#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_SYSCALL_64_S */
