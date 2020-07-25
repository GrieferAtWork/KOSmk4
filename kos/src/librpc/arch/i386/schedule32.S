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
#ifndef GUARD_LIBRPC_ARCH_I386_SCHEDULE32_S
#define GUARD_LIBRPC_ARCH_I386_SCHEDULE32_S 1

#include <hybrid/compiler.h>

#include <asm/cfi.h>
#include <asm/instr/ttest.h>

#include <errno.h>

#include <librpc/rpc.h>


.section .text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl  __x86.get_pc_thunk.bx
	.hidden __x86.get_pc_thunk.bx
	.type   __x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
	.cfi_startproc
	movl   (%esp), %ebx
	ret
	.cfi_endproc


.section .rodata
PRIVATE_OBJECT(rpc_program_386)
	.byte RPC_PROGRAM_OP_plda | RPC_386_REGISTER_EIP      /* >> psh  %eip                         *
	                                                       * >> lod  %eip, %arg[0]                */
	.byte RPC_PROGRAM_OP_pshr | RPC_386_REGISTER_EFLAGS   /* >> psh  %eflags                      */
	.byte RPC_PROGRAM_OP_pshr | RPC_386_REGISTER_EBX      /* >> psh  %ebx                         */
	.byte RPC_PROGRAM_OP_pshr | RPC_386_REGISTER_EBP      /* >> psh  %ebp                         */
	.byte RPC_PROGRAM_OP_pshr | RPC_386_REGISTER_EDX      /* >> psh  %edx                         */
	.byte RPC_PROGRAM_OP_pshr | RPC_386_REGISTER_ECX      /* >> psh  %ecx                         */
	.byte RPC_PROGRAM_OP_plda | RPC_386_REGISTER_EAX      /* >> psh  %eax                         *
	                                                       * >> lod  %eax, %arg[1]                */
	.byte RPC_PROGRAM_OP_mov                              /* >> mov  %esp, %ebp                   */
	.byte RPC_PROGRAM_OP_arg | RPC_386_REGISTER_ESP       /* >>                                   */
	.byte RPC_PROGRAM_OP_arg | RPC_386_REGISTER_EBP       /* >>                                   */
	.byte RPC_PROGRAM_OP_psh_sys                          /* >> psh  syscall_info                 */
	.byte RPC_PROGRAM_OP_lod_rsn | RPC_386_REGISTER_EBX   /* >> lod  %ebx, reason                 */
	.byte RPC_PROGRAM_OP_rep_stftx_psha                   /* >> rep  %arg[2]                      *
	                                                       * >> [stftx %arg[3]]                   *
	                                                       * >> psh  %arg[(3|4) + n...]           */
	.byte RPC_PROGRAM_OP_resume                           /* >> resume                            */
END(rpc_program_386)

.section .text
PRIVATE_FUNCTION(librpc_schedule_rpc_entry)
	/* Register state:
	 *   - %ebx:     RPC reason (One of { RPC_REASON_ASYNC, RPC_REASON_SYSCALL })
	 *   - %eax:     User-callback to invoke
	 *   - 0(%ebp):  Saved EAX
	 *   - 4(%ebp):  Saved ECX
	 *   - 8(%ebp):  Saved EDX
	 *   - 12(%ebp): Saved EBP
	 *   - 16(%ebp): Saved EBX
	 *   - 20(%ebp): Saved EFLAGS
	 *   - 24(%ebp): Saved EIP
	 *   - 28(%ebp): <LEA: Old ESP>
	 *   - -SIZEOF_RPC_SYSCALL_INFO(%ebp): System call info (if EBX == RPC_REASON_SYSCALL)
	 *   - 0(%esp):  ARG[0]
	 *   - 4(%esp):  ARG[1]
	 *   - 8(%esp):  ...
	 */
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %ebp, 28
	.cfi_rel_offset %eax, 0
	.cfi_rel_offset %ecx, 4
	.cfi_rel_offset %edx, 8
	.cfi_rel_offset %ebp, 12
	.cfi_rel_offset %ebx, 16
	.cfi_rel_offset %eflags, 20
	.cfi_rel_offset %eip, 24

	/* Invoke the user-level RPC callback */
	call  *%eax
	/* Check if we should restart an interrupted system call. */
	ttest  mask=RPC_REASON_SYSCALL, loc=%ebx
	jnz    .Lrestart_system_call
	/* Restore the interrupted register state. */
	movl   %ebp, %esp
	.cfi_def_cfa_register %esp
	popl_cfi_r %eax
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %ebp
	popl_cfi_r %ebx
	popfl_cfi_r
	ret
	.cfi_endproc
.Lrestart_system_call:
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %esp, 0
	/* Restart the interrupted system call
	 * -> Information about how the system call was invoked (and can be re-invoked)
	 *    is stored at negative offsets from %ebp */
	.cfi_reg_offset %ebp, 12, %ebp
	.cfi_reg_offset %eax, 0, %ebp
	.cfi_reg_offset %ecx, 4, %ebp
	.cfi_reg_offset %edx, 8, %ebp
	.cfi_reg_offset %ebx, 16, %ebp
	.cfi_reg_offset %eflags, 20, %ebp
	.cfi_reg_offset %eip, 24, %ebp
	.cfi_reg_value %esp, 28, %ebp
	pushl %edi
	.cfi_reg_offset %edi, 0, %esp
	pushl %esi
	.cfi_reg_offset %edi, 4, %esp
	.cfi_reg_offset %esi, 0, %esp
	.cfi_remember_state
	pushl %ebp

	/* Define register restore rules for CFI
	 * This gets a bit complicated, since we need to introduce 2-layer indirection
	 * due to the fact that there we've used EBP as base register up until this point,
	 * however now need to re-assign that register because it's used to pass system
	 * call arguments...
	 */

/*[[[deemon
import * from deemon;
import compileExpression from .....misc.libgen.cfi.compiler;
function restoreAtOffset(reg: string, offset: int, deref_after = true) {
	compileExpression('i386', reg, r'
		push %esp
		deref
		plus   $' + offset + r'
	', deref_after: deref_after);
}
restoreAtOffset("%eax", 0);
restoreAtOffset("%ecx", 4);
restoreAtOffset("%edx", 8);
restoreAtOffset("%ebp", 12);
restoreAtOffset("%ebx", 16);
restoreAtOffset("%eflags", 20);
restoreAtOffset("%eip", 24);
restoreAtOffset("%esp", 28, deref_after: false);
]]]*/
__ASM_L(	.cfi_escape 0x10,0x00,0x02,0x54,0x06)
__ASM_L(	.cfi_escape 0x10,0x01,0x04,0x54,0x06,0x23,0x04)
__ASM_L(	.cfi_escape 0x10,0x02,0x04,0x54,0x06,0x23,0x08)
__ASM_L(	.cfi_escape 0x10,0x05,0x04,0x54,0x06,0x23,0x0c)
__ASM_L(	.cfi_escape 0x10,0x03,0x04,0x54,0x06,0x23,0x10)
__ASM_L(	.cfi_escape 0x10,0x09,0x04,0x54,0x06,0x23,0x14)
__ASM_L(	.cfi_escape 0x10,0x08,0x04,0x54,0x06,0x23,0x18)
__ASM_L(	.cfi_escape 0x16,0x04,0x04,0x54,0x06,0x23,0x1c)
//[[[end]]]
	.cfi_reg_offset %edi, 8, %esp
	.cfi_reg_offset %esi, 4, %esp

#define SYSINFO(off) (-SIZEOF_RPC_SYSCALL_INFO+(off))(%ebp)
	/* Repeat the interrupted system call. */
	movl   SYSINFO(OFFSET_RPC_SYSCALL_INFO_SYSNO), %eax
	movl   SYSINFO(OFFSET_RPC_SYSCALL_INFO_REG(0)), %eax
	movl   SYSINFO(OFFSET_RPC_SYSCALL_INFO_REG(1)), %ecx
	movl   SYSINFO(OFFSET_RPC_SYSCALL_INFO_REG(2)), %edx
	movl   SYSINFO(OFFSET_RPC_SYSCALL_INFO_REG(3)), %esi
	movl   SYSINFO(OFFSET_RPC_SYSCALL_INFO_REG(4)), %edi
	movl   SYSINFO(OFFSET_RPC_SYSCALL_INFO_REG(5)), %ebp
	int    $(0x80)
#undef SYSINFO
	popl   %ebp
	.cfi_restore_state
	.cfi_endproc
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %ebp, 36
	.cfi_rel_offset %esi, 0
	.cfi_rel_offset %edi, 4
	.cfi_same_value %eax
/*	.cfi_rel_offset %eax, 8 */
	.cfi_rel_offset %ecx, 12
	.cfi_same_value %edx /* XXX: Should only be the case for double-wide system calls... */
/*	.cfi_rel_offset %edx, 16 */
	.cfi_rel_offset %ebp, 20
	.cfi_rel_offset %ebx, 24
	.cfi_rel_offset %eflags, 28
	.cfi_rel_offset %eip, 32
	popl_cfi_r %esi
	popl_cfi_r %edi
	movl   %ebp, %esp
	.cfi_def_cfa_register %esp
	addl   $(4), %esp /* EAX */
	.cfi_adjust_cfa_offset -4
	popl_cfi_r %ecx
	addl   $(4), %esp /* EDX */
	.cfi_adjust_cfa_offset -4
	popl_cfi_r %ebp
	popl_cfi_r %ebx
	popfl_cfi_r
	ret
	.cfi_endproc
END(librpc_schedule_rpc_entry)


/* >> rpc_schedule(3)
 * Portable wrapper for `rpc_schedule_ex()'
 * Schedule a simple RPC for execution on a given `target' thread.
 * The scheduled RPC assumes that `target' has a valid stack, while
 * taking a `callback' to-be invoked, which itself will take `argc'
 * pointer-sized arguments from the variable argument list of this
 * function. (When `RPC_SCHEDULE_FLAG_STATUSFUTEX' is given, `callback'
 * takes `argc - 1' arguments, with the first variable argument being
 * a pointer to the status futex)
 * HINT: This function is entirely implemented using `rpc_schedule_ex()'
 * HINT: On i386, the RPC program used by this function is:
 *       >> psh  %eip                        RPC_PROGRAM_OP_plda | RPC_386_REGISTER_EIP
 *       >> lod  %eip, %arg[0]
 *       >> psh  %eflags                     RPC_PROGRAM_OP_pshr | RPC_386_REGISTER_EFLAGS
 *       >> psh  %ebx                        RPC_PROGRAM_OP_pshr | RPC_386_REGISTER_EBX
 *       >> psh  %ebp                        RPC_PROGRAM_OP_pshr | RPC_386_REGISTER_EBP
 *       >> psh  %edx                        RPC_PROGRAM_OP_pshr | RPC_386_REGISTER_EDX
 *       >> psh  %ecx                        RPC_PROGRAM_OP_pshr | RPC_386_REGISTER_ECX
 *       >> psh  %eax                        RPC_PROGRAM_OP_plda | RPC_386_REGISTER_EAX
 *       >> lod  %eax, %arg[1]
 *       >> mov  %esp, %ebp                  RPC_PROGRAM_OP_mov
 *       >>                                  RPC_PROGRAM_OP_arg | RPC_386_REGISTER_ESP
 *       >>                                  RPC_PROGRAM_OP_arg | RPC_386_REGISTER_EBP
 *       >> psh  syscall_info                RPC_PROGRAM_OP_psh_sys
 *       >> lod  %ebx, reason                RPC_PROGRAM_OP_lod_rsn | RPC_386_REGISTER_EBX
 *       >> rep  %arg[2]                     RPC_PROGRAM_OP_rep_stftx_psha
 *       >> [stftx %arg[3]]
 *       >> psh  %arg[(3|4) + n...]
 *       >> resume                           RPC_PROGRAM_OP_resume
 *       When `callback' returns, an internal wrapper is called that will restore
 *       registers, as well as optionally restart an interrupted system call,
 *       depending on the reason code loaded into `%ebx', before restoring registers
 *       using the data pointed to by `%ebp'
 *       With all of this in mind, the register state when librpc's internal RPC
 *       wrapper is entered looks as follows:
 *        - %ebx:     RPC reason (One of { RPC_REASON_ASYNC, RPC_REASON_SYSCALL })
 *        - %eax:     User-callback to invoke
 *        - 0(%ebp):  Saved EAX
 *        - 4(%ebp):  Saved ECX
 *        - 8(%ebp):  Saved EDX
 *        - 12(%ebp): Saved EBP
 *        - 16(%ebp): Saved EBX
 *        - 20(%ebp): Saved EFLAGS
 *        - 24(%ebp): Saved EIP
 *        - 28(%ebp): <LEA: Old ESP>
 *        - -SIZEOF_RPC_SYSCALL_INFO(%ebp): System call info (if EBX == RPC_REASON_SYSCALL)
 *        - 0(%esp):  ARG[0]
 *        - 4(%esp):  ARG[1]
 *        - 8(%esp):  ...
 * @param: target:   The targeted thread.
 * @param: flags:    RPC flags (one of `RPC_SCHEDULE_*', or'd with a set of `RPC_SCHEDULE_FLAG_*')
 * @param: callback: The callback to invoke
 * @param: argc:     The number of arguments to-be passed to `callback'
 * @param: ...:      Arguments passed to `callback', potentially preceded by
 *                   the status futex when the `RPC_SCHEDULE_FLAG_STATUSFUTEX'
 *                   flag was set.
 * @return: 1:  The specified `target' thread has already terminated.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno')
 * @throws: E_PROCESS_EXITED:  `target' does not reference a valid process
 * @throws: E_INVALID_ARGUMENT: The given `flag' is invalid. */
.section .text
INTERN_FUNCTION(librpc_schedule)
	.cfi_startproc
	pushl_cfi_r %ebx
	call   __x86.get_pc_thunk.bx
	addl   $_GLOBAL_OFFSET_TABLE_, %ebx
	/*  4(%esp): RETURN_ADDRESS
	 *  8(%esp): target
	 * 12(%esp): flags
	 * 16(%esp): callback
	 * 20(%esp): args...
	 */
	leal   12(%esp), %eax
	pushl_cfi %eax      /* push(&flags) */
	leal   rpc_program_386@GOTOFF(%ebx), %ecx
	pushl_cfi %ecx      /* push(&rpc_program_386) */
	pushl_cfi (%eax)    /* push(flags) */
	pushl_cfi -4(%eax)  /* push(target) */
	leal   librpc_schedule_rpc_entry@GOTOFF(%ebx), %ecx
	movl   %ecx, (%eax) /* ARGS[0] = flags = &librpc_schedule_rpc_entry */
	INTERN(librpc_schedule_ex)
	call   librpc_schedule_ex
	addl   $(16), %esp
	.cfi_adjust_cfa_offset -16
	popl_cfi_r %ebx
	ret
	.cfi_endproc
END(librpc_schedule)

DEFINE_PUBLIC_ALIAS(rpc_schedule, librpc_schedule);

#endif /* !GUARD_LIBRPC_ARCH_I386_SCHEDULE32_S */
