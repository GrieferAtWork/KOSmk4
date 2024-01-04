/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_LIBC_ARCH_I386_SIGNAL_S
#define GUARD_LIBC_LIBC_ARCH_I386_SIGNAL_S 1
#define __ASSEMBLER__ 1
#define _KOS_KERNEL_SOURCE 1

#include <hybrid/compiler.h>

#include <cfi.h>
#include <asm/instr/compat.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>

#include <syscall.h>

#ifndef __x86_64__
#define syscall int $(0x80)
#endif /* !__x86_64__ */


.section .text.crt.sched.signal
	.cfi_startproc simple
	.cfi_signal_frame
	/* %Pbp:        [1..1] struct ucpustate const        *restore_cpu        CPU context */
	/* %Pbx:        [0..1] struct fpustate const         *restore_fpu        FPU context */
	/* [%esi,%r12]: [0..1] struct sigset_with_size const *restore_sigmask    Signal mask */
	/* [%edi,%r13]: [0..1] struct rpc_syscall_info       *sc_info            Restartable system call */
	.cfi_def_cfa %Pbp, 0
	ASM_CFI_REL_OFFSET_RESTORE_UCPUSTATE(0)

/*[[[deemon
import outputForAssembly from ......misc.libgen.cfi.comp;
local HYBRID_PROGRAM = r'
	push     %Pbx                     # <fpustate>
	jz       top, 1f
	dup                               # <fpustate, fpustate>
	add      $OFFSET_SFPUSTATE___PAD2 # <fpustate, &fpustate->f_ssave.__fs_pad2>
	deref_size $2                     # <fpustate, fpustate->f_ssave.__fs_pad2>
	eq       $0xffff                  # <fpustate, fpustate->f_ssave.__fs_pad2 == 0xffff>
	jt       pop, 2f
	plus     ${xoffset}               # <fpustate->f_xsave.*>
	jmp      3f
2:	plus     ${soffset}               # <fpustate->f_ssave.*>
3:	deref
	ret
1:	push     %{reg}';

local XONLY_PROGRAM = r'
	push     %Pbx                     # <fpustate>
	jz       top, 1f
	dup                               # <fpustate, fpustate>
	add      $OFFSET_SFPUSTATE___PAD2 # <fpustate, &fpustate->f_ssave.__fs_pad2>
	deref_size $2                     # <fpustate, fpustate->f_ssave.__fs_pad2>
	eq       $0xffff                  # <fpustate, fpustate->f_ssave.__fs_pad2 == 0xffff>
	jt       pop, 1f
	plus     ${offset}                # <fpustate->f_xsave.*>
	deref
	ret
1:	push     %{reg}';

local HYBRID_REGISTERS = {
	("st0", "OFFSET_XFPUSTATE_ST0", "OFFSET_SFPUSTATE_ST0"),
	("st1", "OFFSET_XFPUSTATE_ST1", "OFFSET_SFPUSTATE_ST1"),
	("st2", "OFFSET_XFPUSTATE_ST2", "OFFSET_SFPUSTATE_ST2"),
	("st3", "OFFSET_XFPUSTATE_ST3", "OFFSET_SFPUSTATE_ST3"),
	("st4", "OFFSET_XFPUSTATE_ST4", "OFFSET_SFPUSTATE_ST4"),
	("st5", "OFFSET_XFPUSTATE_ST5", "OFFSET_SFPUSTATE_ST5"),
	("st6", "OFFSET_XFPUSTATE_ST6", "OFFSET_SFPUSTATE_ST6"),
	("st7", "OFFSET_XFPUSTATE_ST7", "OFFSET_SFPUSTATE_ST7"),
	("fcw", "OFFSET_XFPUSTATE_FCW", "OFFSET_SFPUSTATE_FCW"),
	("fsw", "OFFSET_XFPUSTATE_FSW", "OFFSET_SFPUSTATE_FSW"),
};

local XONLY_REGISTERS = {
	("xmm0",  "OFFSET_XFPUSTATE_XMM0"),
	("xmm1",  "OFFSET_XFPUSTATE_XMM1"),
	("xmm2",  "OFFSET_XFPUSTATE_XMM2"),
	("xmm3",  "OFFSET_XFPUSTATE_XMM3"),
	("xmm4",  "OFFSET_XFPUSTATE_XMM4"),
	("xmm5",  "OFFSET_XFPUSTATE_XMM5"),
	("xmm6",  "OFFSET_XFPUSTATE_XMM6"),
	("xmm7",  "OFFSET_XFPUSTATE_XMM7"),
	("mxcsr", "OFFSET_XFPUSTATE_MXCSR"),
};

print("#ifdef __x86_64__");
for (local reg, xoffset, soffset: HYBRID_REGISTERS) {
	outputForAssembly('x86_64', reg, HYBRID_PROGRAM.format({
		.reg = reg,
		.xoffset = xoffset,
		.soffset = soffset,
	}), linePrefix: "", lineSuffix: "", bytesPerLine: 32);
}
for (local reg, offset: {
	XONLY_REGISTERS...,
	("xmm9",  "OFFSET_XFPUSTATE_XMM9"),
	("xmm10", "OFFSET_XFPUSTATE_XMM10"),
	("xmm11", "OFFSET_XFPUSTATE_XMM11"),
	("xmm12", "OFFSET_XFPUSTATE_XMM12"),
	("xmm13", "OFFSET_XFPUSTATE_XMM13"),
	("xmm14", "OFFSET_XFPUSTATE_XMM14"),
	("xmm15", "OFFSET_XFPUSTATE_XMM15"),
}) {
	outputForAssembly('x86_64', reg, XONLY_PROGRAM.format({
		.reg = reg,
		.offset = offset,
	}), linePrefix: "", lineSuffix: "", bytesPerLine: 32);
}
print("#else /" "* __x86_64__ *" "/");
for (local reg, xoffset, soffset: HYBRID_REGISTERS) {
	outputForAssembly('i386', reg, HYBRID_PROGRAM.format({
		.reg = reg,
		.xoffset = xoffset,
		.soffset = soffset,
	}), linePrefix: "", lineSuffix: "", bytesPerLine: 32);
}
for (local reg, offset: XONLY_REGISTERS) {
	outputForAssembly('i386', reg, XONLY_PROGRAM.format({
		.reg = reg,
		.offset = offset,
	}), linePrefix: "", lineSuffix: "", bytesPerLine: 32);
}
print("#endif /" "* !__x86_64__ *" "/");
]]]*/
#ifdef __x86_64__
	.cfi_escape 22,33,33,115,0,18,32,40,23,0,18,35,6,148,2,10,255,255,41,40,5,0,35,32,47,2,0,35,28,6,47,3
	.cfi_escape 0,146,33,0
	.cfi_escape 22,34,33,115,0,18,32,40,23,0,18,35,6,148,2,10,255,255,41,40,5,0,35,48,47,2,0,35,38,6,47,3
	.cfi_escape 0,146,34,0
	.cfi_escape 22,35,33,115,0,18,32,40,23,0,18,35,6,148,2,10,255,255,41,40,5,0,35,64,47,2,0,35,48,6,47,3
	.cfi_escape 0,146,35,0
	.cfi_escape 22,36,33,115,0,18,32,40,23,0,18,35,6,148,2,10,255,255,41,40,5,0,35,80,47,2,0,35,58,6,47,3
	.cfi_escape 0,146,36,0
	.cfi_escape 22,37,33,115,0,18,32,40,23,0,18,35,6,148,2,10,255,255,41,40,5,0,35,96,47,2,0,35,68,6,47,3
	.cfi_escape 0,146,37,0
	.cfi_escape 22,38,33,115,0,18,32,40,23,0,18,35,6,148,2,10,255,255,41,40,5,0,35,112,47,2,0,35,78,6,47,3
	.cfi_escape 0,146,38,0
	.cfi_escape 22,39,34,115,0,18,32,40,24,0,18,35,6,148,2,10,255,255,41,40,6,0,35,128,1,47,2,0,35,88,6,47
	.cfi_escape 3,0,146,39,0
	.cfi_escape 22,40,34,115,0,18,32,40,24,0,18,35,6,148,2,10,255,255,41,40,6,0,35,144,1,47,2,0,35,98,6,47
	.cfi_escape 3,0,146,40,0
	.cfi_escape 22,65,29,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,3,0,47,0,0,6,47,3,0,146,65,0
	.cfi_escape 22,66,33,115,0,18,32,40,23,0,18,35,6,148,2,10,255,255,41,40,5,0,35,2,47,2,0,35,4,6,47,3
	.cfi_escape 0,146,66,0
	.cfi_escape 22,17,28,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,160,1,6,47,2,0,129,0
	.cfi_escape 22,18,28,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,176,1,6,47,2,0,130,0
	.cfi_escape 22,19,28,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,192,1,6,47,2,0,131,0
	.cfi_escape 22,20,28,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,208,1,6,47,2,0,132,0
	.cfi_escape 22,21,28,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,224,1,6,47,2,0,133,0
	.cfi_escape 22,22,28,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,240,1,6,47,2,0,134,0
	.cfi_escape 22,23,28,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,128,2,6,47,2,0,135,0
	.cfi_escape 22,24,28,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,144,2,6,47,2,0,136,0
	.cfi_escape 22,64,28,115,0,18,32,40,18,0,18,35,6,148,2,10,255,255,41,40,6,0,35,24,6,47,3,0,146,64,0
	.cfi_escape 22,26,28,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,176,2,6,47,2,0,138,0
	.cfi_escape 22,27,28,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,192,2,6,47,2,0,139,0
	.cfi_escape 22,28,28,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,208,2,6,47,2,0,140,0
	.cfi_escape 22,29,28,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,224,2,6,47,2,0,141,0
	.cfi_escape 22,30,28,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,240,2,6,47,2,0,142,0
	.cfi_escape 22,31,28,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,128,3,6,47,2,0,143,0
	.cfi_escape 22,32,29,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,144,3,6,47,3,0,146,32,0
#else /* __x86_64__ */
	.cfi_escape 22,11,32,115,0,18,32,40,23,0,18,35,6,148,2,10,255,255,41,40,5,0,35,32,47,2,0,35,28,6,47,2
	.cfi_escape 0,123,0
	.cfi_escape 22,12,32,115,0,18,32,40,23,0,18,35,6,148,2,10,255,255,41,40,5,0,35,48,47,2,0,35,38,6,47,2
	.cfi_escape 0,124,0
	.cfi_escape 22,13,32,115,0,18,32,40,23,0,18,35,6,148,2,10,255,255,41,40,5,0,35,64,47,2,0,35,48,6,47,2
	.cfi_escape 0,125,0
	.cfi_escape 22,14,32,115,0,18,32,40,23,0,18,35,6,148,2,10,255,255,41,40,5,0,35,80,47,2,0,35,58,6,47,2
	.cfi_escape 0,126,0
	.cfi_escape 22,15,32,115,0,18,32,40,23,0,18,35,6,148,2,10,255,255,41,40,5,0,35,96,47,2,0,35,68,6,47,2
	.cfi_escape 0,127,0
	.cfi_escape 22,16,32,115,0,18,32,40,23,0,18,35,6,148,2,10,255,255,41,40,5,0,35,112,47,2,0,35,78,6,47,2
	.cfi_escape 0,128,0
	.cfi_escape 22,17,33,115,0,18,32,40,24,0,18,35,6,148,2,10,255,255,41,40,6,0,35,128,1,47,2,0,35,88,6,47
	.cfi_escape 2,0,129,0
	.cfi_escape 22,18,33,115,0,18,32,40,24,0,18,35,6,148,2,10,255,255,41,40,6,0,35,144,1,47,2,0,35,98,6,47
	.cfi_escape 2,0,130,0
	.cfi_escape 22,37,29,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,3,0,47,0,0,6,47,3,0,146,37,0
	.cfi_escape 22,38,33,115,0,18,32,40,23,0,18,35,6,148,2,10,255,255,41,40,5,0,35,2,47,2,0,35,4,6,47,3
	.cfi_escape 0,146,38,0
	.cfi_escape 22,21,28,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,160,1,6,47,2,0,133,0
	.cfi_escape 22,22,28,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,176,1,6,47,2,0,134,0
	.cfi_escape 22,23,28,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,192,1,6,47,2,0,135,0
	.cfi_escape 22,24,28,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,208,1,6,47,2,0,136,0
	.cfi_escape 22,25,28,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,224,1,6,47,2,0,137,0
	.cfi_escape 22,26,28,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,240,1,6,47,2,0,138,0
	.cfi_escape 22,27,28,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,128,2,6,47,2,0,139,0
	.cfi_escape 22,28,28,115,0,18,32,40,19,0,18,35,6,148,2,10,255,255,41,40,7,0,35,144,2,6,47,2,0,140,0
	.cfi_escape 22,39,28,115,0,18,32,40,18,0,18,35,6,148,2,10,255,255,41,40,6,0,35,24,6,47,3,0,146,39,0
#endif /* !__x86_64__ */
/*[[[end]]]*/

	nop /* For unwinding... */
INTERN_FUNCTION(libc_sig_restore)
	movP  $(SYS_ksigreturn), %Pax
	std   /* Enable  exceptions (this syscall shouldn't fail, but
	       * if it does, it shouldn't return with a normal error,
	       * but with an exception that  will likely turn into  a
	       * coredump) */
	syscall

	/* Really shouldn't get here, but should we ever, intentionally crash */
	hlt
END(libc_sig_restore)
	.cfi_endproc

#endif /* !GUARD_LIBC_LIBC_ARCH_I386_SIGNAL_S */
