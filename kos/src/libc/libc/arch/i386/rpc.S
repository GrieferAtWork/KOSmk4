/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_LIBC_ARCH_I386_RPC_S
#define GUARD_LIBC_LIBC_ARCH_I386_RPC_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <cfi.h>
#include <asm/instr/compat.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>
#include <kos/rpc.h>

#include <syscall.h>

#ifndef SIZEOF_POINTER
#define SIZEOF_POINTER __SIZEOF_POINTER__
#endif /* !SIZEOF_POINTER */

#ifdef __x86_64__
#define _STACKPARAM_SIZE 0
#else /* __x86_64__ */
#define _STACKPARAM_SIZE 8 /* CDECL: `struct rpc_context *ctx', `void *cookie' */
#endif /* !__x86_64__ */

/* Offsets within `struct rpc_context' */
#define rc_context (_STACKPARAM_SIZE + 0)
#define rc_state   (_STACKPARAM_SIZE + SIZEOF_POINTER)
#define rc_scinfo  (_STACKPARAM_SIZE + (2 * SIZEOF_POINTER))

/* Parameter registers for `sys_[rt_]sigreturn()' */
#define R_sigreturn_cpu     Pbp
#define R_sigreturn_fpu     Pbx
#ifdef __x86_64__
#define R_sigreturn_sigmask r12
#define R_sigreturn_sc_info r13
#else /* __x86_64__ */
#define R_sigreturn_sigmask esi
#define R_sigreturn_sc_info edi
#define syscall             int $0x80
#endif /* !__x86_64__ */


.section .text.crt.sched.rpc
/* Restorer wrapper function for `rpc_exec_program' and `rpc_interrupt_program' */
/* INTDEF void ASMCALL libc_x86_rpc_restorer(void); */
	.cfi_startproc simple
	.cfi_signal_frame
	/* Upon entry, `%Psp' points at a `struct rpc_context *ctx', and we must:
	 *  - Set-up CFI to restore `ctx->rc_state'
	 *  - Make a call to `sys_sigreturn(2)' if `ctx->rc_context == RPC_REASONCTX_SYSCALL'
	 *  - Restore the register state from `ctx->rc_state' */
/*[[[cfi{arch='x86', register='%cfa'}
	push   %Psp
#ifdef __x86_64__
	add    $8               # rc_state
#else // __x86_64__
	add    $12              # rc_state
#endif // !__x86_64__
	deref                   # Read the value of `ctx->rc_state'
]]]*/
#ifdef __x86_64__
	.cfi_escape 15,5,119,0,35,8,6
#else /* __x86_64__ */
	.cfi_escape 15,5,116,0,35,12,6
#endif /* !__x86_64__ */
/*[[[end]]]*/
	ASM_CFI_OFFSET_RESTORE_UCPUSTATE(0)
	nop /* For unwinding... */
INTERN_FUNCTION(libc_x86_rpc_restorer)

	movP   rc_state(%Psp), %R_sigreturn_cpu
	.cfi_def_cfa_register %R_sigreturn_cpu
	xorP   %R_sigreturn_fpu, %R_sigreturn_fpu          /* Don't have FPU state to restore */
	xorP   %R_sigreturn_sigmask, %R_sigreturn_sigmask  /* Don't have signal mask to restore */
	leaP   rc_scinfo(%Psp), %R_sigreturn_sc_info
	cmpP   $(RPC_REASONCTX_SYSCALL), rc_context(%Psp)  /* Check if we must restart a system call. */
	cmovneP %R_sigreturn_sigmask, %R_sigreturn_sc_info /* if (rc_context != RPC_REASONCTX_SYSCALL) sc_info = NULL; */
	movP   $(SYS_ksigreturn), %Pax
	std    /* Enable  exceptions (this syscall shouldn't fail, but
	        * if it does, it shouldn't return with a normal error,
	        * but with an exception that  will likely turn into  a
	        * coredump) */
	syscall

	/* Really shouldn't get here, but should we ever, intentionally crash */
	hlt
END(libc_x86_rpc_restorer)
	.cfi_endproc





#endif /* !GUARD_LIBC_LIBC_ARCH_I386_RPC_S */
