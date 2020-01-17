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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_SIGNAL32_S
#define GUARD_LIBC_LIBC_ARCH_I386_SIGNAL32_S 1
#define _KOS_KERNEL_SOURCE 1

#include <hybrid/compiler.h>

#include <asm/cfi.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>

#include <syscall.h>

.section .text.crt.sched.signal.sig_restore
INTERN_FUNCTION(libc_sig_restore)
	.cfi_startproc simple
	.cfi_signal_frame
	/* %ebp: [1..1] struct ucpustate const *restore_cpu  CPU context */
	/* %ebx: [0..1] struct fpustate const *restore_fpu   FPU context */
	/* %esi: [0..1] sigset_t const *restore_sigmask      Signal mask */
	/* %edi: [0..1] struct rpc_syscall_info *sc_info     Restartable system call */
	.cfi_def_cfa %ebp, 0
	ASM_CFI_REL_OFFSET_RESTORE_UCPUSTATE(0)

	/* TODO: CFI expressions for conditional restoring of FPU registers:
	 *    >> if (EBX) {
	 *    >>     SOME_FPU_REGISTER = RESTORE_FROM_FPUSTATE(EBX);
	 *    >> } else {
	 *    >>     SOME_FPU_REGISTER = SAME_VALUE;
	 *    >> }
	 * TODO: Add some way for user-code to select the type of FPU context
	 *       that will get loaded by the sigreturn() system call.
	 */

	movl  $(SYS_sigreturn), %eax
	int   $(0x80)
	.cfi_endproc
END(libc_sig_restore)

#endif /* !GUARD_LIBC_LIBC_ARCH_I386_SIGNAL32_S */
