/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_RPC_S
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_RPC_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_RPC
#include <sched/rpc.h>
#include <kernel/rt/except-handler.h>

#include <asm/cfi.h>
#include <asm/instr/compat.h>


/* >> PUBLIC NOBLOCK NONNULL((1, 2)) void FCALL
 * >> task_asyncrpc_execnow(struct rpc_context *__restrict context,
 * >>                       prpc_exec_callback_t func, void *cookie);
 * Arch-specific function:
 * Execute the given `func' using the register state at the time of
 * the call to this function,  whilst passing the given  `context'. */
.section .text
PUBLIC_FUNCTION(task_asyncrpc_execnow)
	.cfi_startproc

	/* TODO */
	int3

	ret
	.cfi_endproc
END(task_asyncrpc_execnow)


/* Arch-specific function:
 * Serve pending, synchronous (and asynchronous) RPCs.
 * NOTE: If the caller was previously  disabled preemption, it will  remain
 *       disabled  if  there  were no  RPC  functions had  to  be executed.
 *       Otherwise, preemption will become enabled, and `true' is returned,
 *       or an exception thrown by an RPC function gets propagated.
 * WARNING: Do not call this function unconditionally!
 *          Only call it if you're certain to be about to start  blocking
 *          in a context where a reset of your current context would have
 *          the potential to resolve the  block. (Reset here meaning  the
 *          current system call being restarted)
 * @return: true:  At   least  one  RPC   function  was  executed,  and
 *                 preemption was re-enabled if it was disabled before.
 * @return: false: No  RPC needed to be served, and preemption
 *                 remains disabled if it was disabled before. */
/* FUNDEF bool KCALL task_serve(void) THROWS(...); */
.section .text
PUBLIC_FUNCTION(task_serve)
	.cfi_startproc

	/* TODO */
	int3

	ret
	.cfi_endproc
END(task_serve)



/* Arch-specific function:
 * Same as `task_serve()', but only sevice RPCs that were scheduled as no-throw.
 * @return: * : Set of `TASK_SERVE_*' */
/* FUNDEF WUNUSED unsigned int NOTHROW(KCALL task_serve_nx)(void); */
.section .text
PUBLIC_FUNCTION(task_serve_nx)
	.cfi_startproc

	/* TODO */
	int3

	ret
	.cfi_endproc
END(task_serve_nx)



/* Entry point for IRET tails that have been re-directed for sysret.
 * Used to  redirect  how  the kernel  will  return  to  user-space:
 * >> redirect_iret_for_sysret() {
 * >>     struct irregs_kernel *irr;
 * >>     PREEMPTION_DISABLE(); // Redirection is only
 * >>     if (IS_VM86_TASK) {
 * >>         irr = GET_KERNEL_STACK_BASE() - sizeof(struct irregs_vm86);
 * >>     } else {
 * >>         irr = GET_KERNEL_STACK_BASE() - sizeof(struct irregs_user);
 * >>     }
 * >>     memcpy(&PERTASK(this_x86_rpc_redirection_iret),irr,
 * >>            sizeof(struct irregs_kernel));
 * >>     irr->ir_eip    = &x86_userexcept_sysret;
 * >>     irr->ir_cs     = SEGMENT_KERNEL_CS;
 * >>     irr->ir_eflags = 0; // Most importantly: disable interrupts
 * >> }
 * WARNING:
 *    Because of the redirection, in order to get/set any of the kernel  IRET
 *    registers when inside of an interrupt/syscall with preemption  enabled,
 *    you must always use the functions below, so-as to ensure that you don't
 *    re-override  the sysret redirection, but modify the saved state when it
 *    comes to the IRET tail. */
/* FUNDEF void ASMCALL x86_userexcept_sysret(void); */
.section .text
PUBLIC_FUNCTION(x86_userexcept_sysret)
	.cfi_startproc

	/* TODO */
	int3

	ret
	.cfi_endproc
END(x86_userexcept_sysret)



#endif /* !CONFIG_USE_NEW_RPC */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_RPC_S */
