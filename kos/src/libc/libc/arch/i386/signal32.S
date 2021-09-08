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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_SIGNAL32_S
#define GUARD_LIBC_LIBC_ARCH_I386_SIGNAL32_S 1
#define __ASSEMBLER__ 1
#define _KOS_KERNEL_SOURCE 1

#include <hybrid/compiler.h>

#include <asm/cfi.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>

#include <syscall.h>

.section .text.crt.sched.signal
INTERN_FUNCTION(libc_sig_restore)
	.cfi_startproc simple
	.cfi_signal_frame
	/* %ebp: [1..1] struct ucpustate const *restore_cpu  CPU context */
	/* %ebx: [0..1] struct fpustate const *restore_fpu   FPU context */
	/* %esi: [0..1] sigset_t const *restore_sigmask      Signal mask */
	/* %edi: [0..1] struct rpc_syscall_info *sc_info     Restartable system call */
	.cfi_def_cfa %ebp, 0
	ASM_CFI_REL_OFFSET_RESTORE_UCPUSTATE(0)

/*[[[deemon
import outputForAssembly from ......misc.libgen.cfi.comp;
for (local reg, offset: {
	("st0",   "OFFSET_XFPUSTATE_ST0"),   // TODO: Support for `struct sfpustate'
	("st1",   "OFFSET_XFPUSTATE_ST1"),
	("st2",   "OFFSET_XFPUSTATE_ST2"),
	("st3",   "OFFSET_XFPUSTATE_ST3"),
	("st4",   "OFFSET_XFPUSTATE_ST4"),
	("st5",   "OFFSET_XFPUSTATE_ST5"),
	("st6",   "OFFSET_XFPUSTATE_ST6"),
	("st7",   "OFFSET_XFPUSTATE_ST7"),
	("xmm0",  "OFFSET_XFPUSTATE_XMM0"),
	("xmm1",  "OFFSET_XFPUSTATE_XMM1"),
	("xmm2",  "OFFSET_XFPUSTATE_XMM2"),
	("xmm3",  "OFFSET_XFPUSTATE_XMM3"),
	("xmm4",  "OFFSET_XFPUSTATE_XMM4"),
	("xmm5",  "OFFSET_XFPUSTATE_XMM5"),
	("xmm6",  "OFFSET_XFPUSTATE_XMM6"),
	("xmm7",  "OFFSET_XFPUSTATE_XMM7"),
	("fcw",   "OFFSET_XFPUSTATE_FCW"),
	("fsw",   "OFFSET_XFPUSTATE_FSW"),
	("mxcsr", "OFFSET_XFPUSTATE_MXCSR"),
}) {
	outputForAssembly('i386', reg, r'
		push     %ebx
		jz       top, 1f
		plus     ${offset}
		deref
		ret
1:		push     %{reg}
	'.format({
		.reg = reg,
		.offset = offset
	}), linePrefix: "", lineSuffix: "", bytesPerLine: 32);
}
]]]*/
	.cfi_escape 22,11,15,115,0,18,32,40,6,0,35,32,6,47,2,0,123,0
	.cfi_escape 22,12,15,115,0,18,32,40,6,0,35,48,6,47,2,0,124,0
	.cfi_escape 22,13,15,115,0,18,32,40,6,0,35,64,6,47,2,0,125,0
	.cfi_escape 22,14,15,115,0,18,32,40,6,0,35,80,6,47,2,0,126,0
	.cfi_escape 22,15,15,115,0,18,32,40,6,0,35,96,6,47,2,0,127,0
	.cfi_escape 22,16,15,115,0,18,32,40,6,0,35,112,6,47,2,0,128,0
	.cfi_escape 22,17,16,115,0,18,32,40,7,0,35,128,1,6,47,2,0,129,0
	.cfi_escape 22,18,16,115,0,18,32,40,7,0,35,144,1,6,47,2,0,130,0
	.cfi_escape 22,21,16,115,0,18,32,40,7,0,35,160,1,6,47,2,0,133,0
	.cfi_escape 22,22,16,115,0,18,32,40,7,0,35,176,1,6,47,2,0,134,0
	.cfi_escape 22,23,16,115,0,18,32,40,7,0,35,192,1,6,47,2,0,135,0
	.cfi_escape 22,24,16,115,0,18,32,40,7,0,35,208,1,6,47,2,0,136,0
	.cfi_escape 22,25,16,115,0,18,32,40,7,0,35,224,1,6,47,2,0,137,0
	.cfi_escape 22,26,16,115,0,18,32,40,7,0,35,240,1,6,47,2,0,138,0
	.cfi_escape 22,27,16,115,0,18,32,40,7,0,35,128,2,6,47,2,0,139,0
	.cfi_escape 22,28,16,115,0,18,32,40,7,0,35,144,2,6,47,2,0,140,0
	.cfi_escape 22,37,14,115,0,18,32,40,4,0,6,47,3,0,146,37,0
	.cfi_escape 22,38,16,115,0,18,32,40,6,0,35,2,6,47,3,0,146,38,0
	.cfi_escape 22,39,16,115,0,18,32,40,6,0,35,24,6,47,3,0,146,39,0
/*[[[end]]]*/


	/* TODO: CFI expressions for conditional restoring of FPU registers:
	 *    >> if (EBX) {
	 *    >>     SOME_FPU_REGISTER = RESTORE_FROM_FPUSTATE(EBX);
	 *    >> } else {
	 *    >>     SOME_FPU_REGISTER = SAME_VALUE;
	 *    >> }
	 * TODO: Add some way for user-code to select the type of FPU context
	 *       that  will  get  loaded  by  the  sigreturn()  system  call.
	 *       Idea: Use  the lowest bit  of the `struct fpustate const *restore_fpu' pointer
	 *             Adding a field to the struct is a bad idea, since `fxsave' might already
	 *             be using any of the "reserved" fields.
	 */

	movl  $(SYS_sigreturn), %eax
	int   $(0x80)
	.cfi_endproc
END(libc_sig_restore)

#endif /* !GUARD_LIBC_LIBC_ARCH_I386_SIGNAL32_S */
