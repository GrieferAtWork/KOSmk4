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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_ROUTER64_S
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_ROUTER64_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <kernel/except.h>

#include <hybrid/host.h>

#include <cfi.h>
#include <asm/instr/movzxq.h>
#include <kos/rpc.h>

/* Include the 32-bit router for compatibility mode. */
#include "router32.S"


/* Define the default break function for the run32 routing table. */
.section .text.cold
INTERN_FUNCTION(__x86_asm32_sysrun32_break)
	.cfi_startproc
	movzlq 40(%rdi), %rax  /* %rax = arg[5] */
	pushq_cfi %rax         /* pointers[7] = %rax */
	movzlq 32(%rdi), %rax  /* %rax = arg[4] */
	pushq_cfi %rax         /* pointers[6] = %rax */
	movzlq 24(%rdi), %rax  /* %rax = arg[3] */
	pushq_cfi %rax         /* pointers[5] = %rax */
	movzlq 16(%rdi), %rax  /* %rax = arg[2] */
	pushq_cfi %rax         /* pointers[4] = %rax */
	movzlq 8(%rdi), %r9    /* pointers[3] = arg[1] */
	movzlq 0(%rdi), %r8    /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(RPC_SYSCALL_INFO_METHOD_OTHER_32 | RPC_SYSCALL_INFO_FEXCEPT | \
	         ((1 << 6) - 1) << RPC_SYSCALL_INFO_FREGVALID_SHIFT), %rdx /* pointers[0] = flags */
	movq   $(8), %rsi                                  /* argc */
	movq   $(EXCEPT_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   except_thrown
	.cfi_endproc
END(__x86_asm32_sysrun32_break)


/* Define `x86_sysrouteN_runc32' */
.section .rodata.x86.syscall32.route_runc
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	PUBLIC_OBJECT(x86_sysroute##table_id##_runc32)
#define __SYSCALL(name)         EXTERN(__x86_asm32_sysrun32_##name); PTR __x86_asm32_sysrun32_##name;
#define __SYSCALL_UNUSED(sysno) PTR __x86_asm32_sysrun32_break;
#define __TSYSCALL_TABLE_END(table_id, ...) \
	END(x86_sysroute##table_id##_runc32)
#include "../../../../../../include/i386-kos/asm/ls-syscalls32.h"

/* Define `x86_sysrouteN_asm64_syscall' */
.section .rodata.x86.syscall64.route_syscall
EXTERN(__x86_asm64_syscall_break)
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	PUBLIC_OBJECT(x86_sysroute##table_id##_asm64_syscall)
#define __SYSCALL(name)         EXTERN(__x86_asm64_syscall_##name); .quad __x86_asm64_syscall_##name;
#define __SYSCALL_UNUSED(sysno) .quad __x86_asm64_syscall_break;
#define __TSYSCALL_TABLE_END(table_id, ...) \
	END(x86_sysroute##table_id##_asm64_syscall)
#include "../../../../../../include/i386-kos/asm/ls-syscalls64.h"


/* Define `x86_sysrouteN_c' */
.section .rodata.x86.syscall64.route_c
EXTERN(sys_break)
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	PUBLIC_OBJECT(x86_sysroute##table_id##_c)
#define __SYSCALL(name)         EXTERN(sys_##name); .quad sys_##name;
#define __SYSCALL_UNUSED(sysno) .quad sys_break;
#define __TSYSCALL_TABLE_END(table_id, ...) \
	END(x86_sysroute##table_id##_c)
#include "../../../../../../include/i386-kos/asm/ls-syscalls64.h"

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_ROUTER64_S */
