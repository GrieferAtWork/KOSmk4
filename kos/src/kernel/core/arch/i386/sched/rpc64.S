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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_RPC64_S
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_RPC64_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/x86/gdt.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/interrupt.h>
#include <asm/instr/movzxq.h>
#include <asm/instr/ttest.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>



.section .data.pertask.early
PUBLIC_OBJECT(this_x86_rpc_redirection_iret)
	.quad  0  /* ir_rip */
	.quad  0  /* ir_cs */
	.quad  0  /* ir_rflags */
	.quad  0  /* ir_rsp */
	.quad  0  /* ir_ss */
END(this_x86_rpc_redirection_iret)

.section .text
	.cfi_startproc simple
	.cfi_signal_frame
	EXTERN(x86_rpc_user_redirection_personality)
	.cfi_personality 0, x86_rpc_user_redirection_personality
/*[[[deemon
import compileExpression from ......misc.libgen.cfi.compiler;
for (local reg: ["rip", "cs", "rflags", "rsp", "ss"]) {
	compileExpression('x86_64', '%' + reg, r'
		ifnotimpl "KOS", 1f
		push_tls_address
		plus     $@(this_x86_rpc_redirection_iret + OFFSET_IRREGS_' + reg.upper() + r')
		deref
		skip     2f
	1:	push     %' + reg + r'
		uninit
	2:');
}
]]]*/
__ASM_L(	.cfi_escape 0x16,0x10,0x12,0x2f,0x03,0x00,0x4b,0x4f)
__ASM_L(	.cfi_escape 0x53,0x2f,0x07,0x00,0xe0,0x23,(this_x86_rpc_redirection_iret + OFFSET_IRREGS_RIP),0x06)
__ASM_L(	.cfi_escape 0x2f,0x02,0x00,0x60,0xf0)
__ASM_L(	.cfi_escape 0x16,0x33,0x13,0x2f,0x03,0x00,0x4b,0x4f)
__ASM_L(	.cfi_escape 0x53,0x2f,0x07,0x00,0xe0,0x23,(this_x86_rpc_redirection_iret + OFFSET_IRREGS_CS),0x06)
__ASM_L(	.cfi_escape 0x2f,0x03,0x00,0x90,0x33,0xf0)
__ASM_L(	.cfi_escape 0x16,0x31,0x13,0x2f,0x03,0x00,0x4b,0x4f)
__ASM_L(	.cfi_escape 0x53,0x2f,0x07,0x00,0xe0,0x23,(this_x86_rpc_redirection_iret + OFFSET_IRREGS_RFLAGS),0x06)
__ASM_L(	.cfi_escape 0x2f,0x03,0x00,0x90,0x31,0xf0)
__ASM_L(	.cfi_escape 0x16,0x07,0x12,0x2f,0x03,0x00,0x4b,0x4f)
__ASM_L(	.cfi_escape 0x53,0x2f,0x07,0x00,0xe0,0x23,(this_x86_rpc_redirection_iret + OFFSET_IRREGS_RSP),0x06)
__ASM_L(	.cfi_escape 0x2f,0x02,0x00,0x57,0xf0)
__ASM_L(	.cfi_escape 0x16,0x34,0x13,0x2f,0x03,0x00,0x4b,0x4f)
__ASM_L(	.cfi_escape 0x53,0x2f,0x07,0x00,0xe0,0x23,(this_x86_rpc_redirection_iret + OFFSET_IRREGS_SS),0x06)
__ASM_L(	.cfi_escape 0x2f,0x03,0x00,0x90,0x34,0xf0)
//[[[end]]]
	.cfi_def_cfa %rsp, 0

	nop /* Required to allow for detection during unwinding. */
PUBLIC_FUNCTION(x86_rpc_user_redirection)

	/* Entry point for redirected RPC callbacks
	 * Note that our current %gs.base still points to kernel-space. */

	pushq_cfi  %gs:(this_x86_rpc_redirection_iret + 32) /* ir_ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi  %gs:(this_x86_rpc_redirection_iret + 24) /* ir_rsp */
	.cfi_rel_offset %rsp, 0
	pushq_cfi  %gs:(this_x86_rpc_redirection_iret + 16) /* ir_rflags */
	.cfi_rel_offset %rflags, 0
	pushq_cfi  %gs:(this_x86_rpc_redirection_iret + 8)  /* ir_cs */
	.cfi_rel_offset %cs, 0
	pushq_cfi  %gs:(this_x86_rpc_redirection_iret + 0)  /* ir_rip */
	.cfi_rel_offset %rip, 0

	/* Re-enable interrupts, now that everything important has been saved. */
	sti

	/* Now save all of the user-space GP registers to create an icpustate. */
	ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R

INTERN_FUNCTION(x86_serve_user_rpc_and_propagate_exceptions)

	/* Actually serve RPC callbacks! */
	movq   %rsp, %rdi

	/* System call interrupts do their own user-RPC handling. */
	EXTERN(rpc_serve_async_user_redirection)
	call   rpc_serve_async_user_redirection

	movq   %rax, %rsp
	.cfi_def_cfa_register %rsp

	/* Check for additional RPC callbacks. */
	EXTERN(this_rpcs_pending)
	cmpq   $(0), %gs:this_rpcs_pending
	jne    x86_serve_user_rpc_and_propagate_exceptions

	/* Check if an exception has been set for user-space. */
	EXTERN(this_rpcs_pending)
	cmpq   $(0), %gs:this_exception_code
	je     1f

	/* Check if exceptions are propagated to user-space, or kernel-space */
	ttest  mask=3, loc=(OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_CS)(%rsp)
	jnz    2f
	/* Kernel-space target! */

	/* Check if the only reason we're still directed to kernel-space
	 * was another IRET redirection to `x86_rpc_user_redirection' */
	cmpq   $(x86_rpc_user_redirection), (OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_RIP)(%rsp)
	/* Load the saved CPU state, which will bring us back up to the
	 * start of `x86_rpc_user_redirection'.
	 * From there, we automatically restore the actual user-space
	 * iret tail, handle additional RPC requests, before eventually
	 * getting here while the current IRET tail still points into
	 * userspace when `x86_userexcept_propagate()' is invoked! */
	je     1f
	PUBLIC(x86_userexcept_unwind_interrupt_kernel_rsp)
	jmp    x86_userexcept_unwind_interrupt_kernel_rsp

2:	/* User-space target */
	movq   %rsp, %rdi /* struct icpustate *__restrict state */
	xorq   %rsi, %rsi /* struct rpc_syscall_info *sc_info */
	PUBLIC(x86_userexcept_propagate)
	call   x86_userexcept_propagate
	movq   %rax, %rsp
	.cfi_def_cfa_register %rsp

1:	/* Restore the state after exception propagation. */
	ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R
	intr_exit
	.cfi_endproc
END(x86_serve_user_rpc_and_propagate_exceptions)
END(x86_rpc_user_redirection)









.section .text
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %rbp, 0
	ASM_CFI_REL_OFFSET_RESTORE_ICPUSTATE(0)
	EXTERN(x86_rpc_kernel_redirection_personality)
	.cfi_personality 0, x86_rpc_kernel_redirection_personality
	nop /* Required to allow for detection during unwinding. */
INTERN_FUNCTION(x86_rpc_kernel_redirection)
	/* RAX:    <task_rpc_t func>
	 * RDI:    <void *arg>
	 * RSI:    <struct icpustate *>    (contains the return location; also used for CFI)
	 * RDX:    <unsigned int reason>
	 * RCX:    <(struct rpc_syscall_info *)0>
	 * RSP:    <struct icpustate *>    (Alias for `RSI')
	 * EFLAGS: <0>                     (interrupts are disabled)
	 * CS:     <SEGMENT_KERNEL_CODE>
	 * SS:     <SEGMENT_KERNEL_DATA0>
	 * GS.BASE:<THIS_TASK>
	 * *:      Undefined */
	call   *%rax
	movq   %rax, %rsp
	.cfi_def_cfa_register %rsp
	ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R
	intr_exit
END(x86_rpc_kernel_redirection)
.cfi_endproc


.section .text
INTERN_FUNCTION(x86_rpc_kernel_redirection_handler)
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %rbp, 0
	ASM_CFI_REL_OFFSET_RESTORE_ICPUSTATE(0)
	/* RAX:    <task_rpc_t func>
	 * RDI:    <void *arg>
	 * RSI:    <struct icpustate *>    (contains the return location; also used for CFI)
	 * RDX:    <unsigned int reason>
	 * RCX:    <(struct rpc_syscall_info *)0>
	 * RSP:    <struct icpustate *>    (Alias for `RSI')
	 * EFLAGS: <0>                     (interrupts are disabled)
	 * CS:     <SEGMENT_KERNEL_CODE>
	 * SS:     <SEGMENT_KERNEL_DATA0>
	 * GS.BASE:<THIS_TASK>
	 * *:      Undefined */
	call   *%rax
	movq   %rax, %rsp
	.cfi_def_cfa_register %rsp
	/* Continue unwinding the exception that brought us here. */
	EXTERN(x86_userexcept_unwind_interrupt_rsp)
	jmp    x86_userexcept_unwind_interrupt_rsp
END(x86_rpc_kernel_redirection_handler)
.cfi_endproc






.section .text
PUBLIC_FUNCTION(task_rpc_exec_here)
	.cfi_startproc
	.cfi_signal_frame
	/* RDI:    <task_rpc_t func>
	 * RSI:    <void *arg>
	 * 0(RSP): <return address>
	 */
	popq_cfi %rax
	.cfi_register %rip, %rax
	movq   %rsp, %rcx
	pushq_cfi $(SEGMENT_KERNEL_DATA0) /* ir_ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %rcx                    /* ir_rsp */
	.cfi_rel_offset %rsp, 0
	pushfq_cfi_r                      /* ir_rflags */
	pushq_cfi $(SEGMENT_KERNEL_CODE)  /* ir_cs */
	.cfi_rel_offset %cs, 0
	pushq_cfi %rax                    /* ir_rip */
	.cfi_rel_offset %rip, 0
	ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R

	movq   %rdi, %rax                     /* <task_rpc_t func> */
	movq   %rsi, %rdi                     /* <void *arg> */
	leaq   8(%rsp), %rsi                  /* <struct icpustate *state> */
	movq   $(TASK_RPC_REASON_ASYNC), %rdx /* <unsigned int reason> */
	xorq   %rcx, %rcx                     /* <struct rpc_syscall_info *sc_info> */
	call   *%rax
	movq   %rax, %rsp

	ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R
	intr_exit
	.cfi_endproc
END(task_rpc_exec_here)


.section .text
PUBLIC_FUNCTION(task_rpc_exec_here_onexit)
	.cfi_startproc
	/* RDI:    <task_rpc_t func>
	 * RSI:    <void *arg>
	 * 0(RSP): <return address>
	 */
	pushq_cfi $(SEGMENT_KERNEL_DATA0) /* ir_ss */
	leaq   16(%rsp), %rax
	pushq_cfi %rax                    /* ir_rsp */
	pushfq_cfi                        /* ir_rflags */
	pushq_cfi $(SEGMENT_KERNEL_CODE)  /* ir_cs */
	pushq_cfi (5 * 8)(%rsp)           /* ir_rip */
	ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R

	movq   %rdi, %rax                        /* <task_rpc_t func> */
	movq   %rsi, %rdi                        /* <void *arg> */
	movq   %rsp, %rsi                        /* <struct icpustate *__restrict state> */
	movq   $(TASK_RPC_REASON_SHUTDOWN), %rdx /* <unsigned int reason> */
	xorq   %rcx, %rcx                        /* <struct rpc_syscall_info const *sc_info> */

	call   *%rax

	addq   $(SIZEOF_ICPUSTATE64), %rsp
	.cfi_adjust_cfa_offset -SIZEOF_ICPUSTATE64
	ret
	.cfi_endproc
END(task_rpc_exec_here_onexit)




.section .text
PUBLIC_FUNCTION(task_serve)
	.cfi_startproc
	EXTERN(this_rpc_pending_sync_count)
	cmpq   $(0), %gs:this_rpc_pending_sync_count
	jne    1f
#if 1 /* Service blocking cleanup operations. */
	EXTERN(blocking_cleanup_service)
	call   blocking_cleanup_service
	/* If there are pending X-RPCs, service them below. */
	cmpq   $(BLOCKING_CLEANUP_SERVICE_XRPC), %rax
	je     1f
	/* return EAX == BLOCKING_CLEANUP_SERVICE_DONE */
	cmpq   $(BLOCKING_CLEANUP_SERVICE_DONE), %rax
	sete   %cl
	movzbq %cl, %rax
	ret
#else
	xorq   %rax, %rax
	ret
#endif
1:	/* Must service synchronous RPC functions!
	 * -> Construct an icpustate. */
	sti
	popq_cfi %rax
	.cfi_register %rip, %rax
	movq     %rsp, %rcx
	pushq_cfi $(SEGMENT_KERNEL_DATA0) /* ir_ss */
	pushq_cfi %rcx                    /* ir_rsp */
	pushfq_cfi                        /* ir_rflags */
	pushq_cfi $(SEGMENT_KERNEL_CODE)  /* ir_cs */
	pushq_cfi %rax                    /* ir_rip */
	.cfi_endproc

	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0

	movq   $(1), %rax /* Return $1 later on (unless overwritten by RPC functions themself) */

	ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R

1:	movq   %rsp, %rdi
	/* Service a single RPC function */
	EXTERN(task_serve_one_impl)
	call   task_serve_one_impl
	/* Load the modified register state. */
	movq   %rax, %rsp
	/* Check if there are more pending RPC callbacks. */
	EXTERN(this_rpc_pending_sync_count)
	cmpq   $(0), %gs:this_rpc_pending_sync_count
	jne    1b

#if 1 /* Service blocking cleanup operations. */
	EXTERN(blocking_cleanup_service)
	call   blocking_cleanup_service
	cmpq   $(BLOCKING_CLEANUP_SERVICE_XRPC), %rax
	je     1b
#endif

	ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R
	intr_exit
	.cfi_endproc
END(task_serve)




.section .text
PUBLIC_FUNCTION(task_serve_nx)
	.cfi_startproc
	cmpq   $(0), %gs:this_rpc_pending_sync_count_nx
#if 1
	je     blocking_cleanup_service
#else
	jne    1f
#if TASK_SERVE_NX_XPENDING == 1
	xorq   %rax, %rax
	cmpq   $(0), %gs:this_rpc_pending_sync_count
	setne  %al
#else
	cmpq   $(0), %gs:this_rpc_pending_sync_count
	movq   $(TASK_SERVE_NX_DIDRUN), %rcx
	cmovne %rcx, %rax
#endif
	ret
1:
#endif
	/* Must service synchronous RPC functions!
	 * -> Construct an icpustate. */
	sti
	popq_cfi %rax
	.cfi_register %rip, %rax
	movq     %rsp, %rcx
	pushq_cfi $(SEGMENT_KERNEL_DATA0) /* ir_ss */
	pushq_cfi %rcx                    /* ir_rsp */
	pushfq_cfi                        /* ir_rflags */
	pushq_cfi $(SEGMENT_KERNEL_CODE)  /* ir_cs */
	pushq_cfi %rax                    /* ir_rip */
	.cfi_endproc

	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0

	/* Return $1 later on (unless overwritten by RPC functions themself) */
	movq   $(TASK_SERVE_NX_DIDRUN), %rax
	ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R

1:	movq   %rsp, %rdi
	/* Service a single RPC function */
	call   task_serve_one_nx_impl
	/* Load the modified register state. */
	movq   %rax, %rsp
	/* Check if there are more pending RPC callbacks. */
	cmpq   $(0), %gs:this_rpc_pending_sync_count_nx
	jne    1b

#if 1 /* Service blocking cleanup operations. */
	call   blocking_cleanup_service
	orq    %rax, (OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RAX)(%rsp)
#endif

	ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R
	cmpq   $(0), %gs:this_rpc_pending_sync_count
	je     1f
	orq    $(TASK_SERVE_NX_XPENDING), %rax
1:	intr_exit
	.cfi_endproc
END(task_serve_nx)



#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_RPC64_S */
