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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_FPU_S
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_FPU_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <kernel/fpu.h>

#ifdef CONFIG_HAVE_FPU
#include <hybrid/host.h>

#include <cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/compat.h>
#include <asm/instr/jccN.h>
#include <asm/instr/movzxq.h>
#include <kos/kernel/bits/fpu-sstate.h>
#include <kos/kernel/bits/fpu-state32.h>

#ifdef __x86_64__
#include <asm/instr/movzxq.h>
#include <kos/kernel/bits/fpu-state64.h>
#endif /* __x86_64__ */


#ifdef __x86_64__
#define RNO_fcall0 7 /* RDI */
#define fxrstorP  fxrstor64
#define fxsaveP   fxsave64
#else /* __x86_64__ */
#define RNO_fcall0 1 /* ECX */
#define fxrstorP  fxrstor
#define fxsaveP   fxsave
#endif /* !__x86_64__ */

#define MIN_DISTANCE(to, dist) \
	.if dist > (.- to);        \
	.skip dist - (.- to);      \
	.endif


.section .text
	.cfi_startproc
PUBLIC_FUNCTION(x86_fpustate_load)
	/* void FCALL x86_fpustate_load(struct fpustate const *__restrict state); */
	fxrstorP (%R_fcall0P)
	ret
	MIN_DISTANCE(x86_fpustate_load, 5)
END(x86_fpustate_load)

PUBLIC_FUNCTION(x86_fpustate_save)
	/* void FCALL x86_fpustate_save(struct fpustate *__restrict state); */
	fxsaveP (%R_fcall0P)
	ret
	MIN_DISTANCE(x86_fpustate_save, 5)
END(x86_fpustate_save)

PUBLIC_FUNCTION(x86_fpustate_save_noreset)
	/* void FCALL x86_fpustate_save_noreset(struct fpustate *__restrict state); */
	fxsaveP (%R_fcall0P)
	ret
	MIN_DISTANCE(x86_fpustate_save_noreset, 5)
END(x86_fpustate_save_noreset)

PUBLIC_FUNCTION(x86_fpustate_init)
	/* void FCALL x86_fpustate_init(struct fpustate *__restrict state); */

	/* >> movw   $(FCW_IM | FCW_DM | FCW_ZM | FCW_OM |
	 * >>          FCW_UM | FCW_PM | 0x40 (???) |
	 * >>          FCW_PC_EXTEND | FCW_RC_NEAREST),
	 * >>        OFFSET_XFPUSTATE_FCW(%R_fcall0P) */
#if OFFSET_XFPUSTATE_FCW == 0
	.byte  0x66, 0xc7, (0x00 | RNO_fcall0)
#else /* OFFSET_XFPUSTATE_FCW == 0 */
	.byte  0x66, 0xc7, (0x40 | RNO_fcall0)
	.byte  OFFSET_XFPUSTATE_FCW
#endif /* OFFSET_XFPUSTATE_FCW != 0 */
	.word  (FCW_IM | FCW_DM | FCW_ZM | FCW_OM | \
	        FCW_UM | FCW_PM | 0x40 | /* ??? */ \
	        FCW_PC_EXTEND | FCW_RC_NEAREST)

	/* movw   $(FTW_ALLEMPTY),  OFFSET_XFPUSTATE_FTW(%R_fcall0P) */
	.byte  0x66, 0xc7, (0x40 | RNO_fcall0)
INTERN_FUNCTION(x86_fpustate_init_ftw_offset_byte)
	.byte  OFFSET_XFPUSTATE_FTW
END(x86_fpustate_init_ftw_offset_byte)
INTERN_FUNCTION(x86_fpustate_init_ftw_value)
	.word  FTW_ALLEMPTY
END(x86_fpustate_init_ftw_value)

	/* movw   $(MXCSR_...),  OFFSET_XFPUSTATE_MXCSR(%R_fcall0P) */
INTERN_FUNCTION(x86_fpustate_init_mxcsr)
	.byte  0xc7, (0x40 | RNO_fcall0)
	.byte  OFFSET_XFPUSTATE_MXCSR
INTERN_FUNCTION(x86_fpustate_init_mxcsr_value)
	.long  (MXCSR_IM | MXCSR_DM | MXCSR_ZM | MXCSR_OM | MXCSR_UM | MXCSR_PM)
END(x86_fpustate_init_mxcsr_value)
END(x86_fpustate_init_mxcsr)
	ret
END(x86_fpustate_init)
	.cfi_endproc






.section .text
PUBLIC_FUNCTION(x86_fxsave)
	/* void FCALL x86_fxsave(struct xfpustate *state); */
	.cfi_startproc
	fnsave (%R_fcall0P)
	frstor (%R_fcall0P) /* Restore fenv since `fnsave' also did `finit' */

	movw   OFFSET_SFPUSTATE_FSW(%R_fcall0P), %ax
	movw   %ax, OFFSET_XFPUSTATE_FSW(%R_fcall0P)

	/* Compress the FTW word:
	 * >> u8 res = 0;
	 * >> for (unsigned int i = 0; i < 8; ++i) {
	 * >>     if ((ftw & FTW_MASK(i)) != FTW_EMPTY(i))
	 * >>         res |= 1 << i;
	 * >> } */
	pushP_cfi_r %R_fcall0P
	EXTERN(x86_fxsave_compress_ftw)
	call   x86_fxsave_compress_ftw
	popP_cfi_r %R_fcall0P
	movb   %al, OFFSET_XFPUSTATE_FTW(%R_fcall0P)


	movw   OFFSET_SFPUSTATE_FOP(%R_fcall0P), %ax
	movw   %ax, OFFSET_XFPUSTATE_FOP(%R_fcall0P)
#ifdef __x86_64__
	movzlP OFFSET_SFPUSTATE_FIP(%R_fcall0P), %Pax
	movP   %Pax, OFFSET_XFPUSTATE_FIP(%R_fcall0P)
	movzlP OFFSET_SFPUSTATE_FDP(%R_fcall0P), %Pax
	movP   %Pax, OFFSET_XFPUSTATE_FDP(%R_fcall0P)
#else /* __x86_64__ */
	movl   OFFSET_SFPUSTATE_FIP(%R_fcall0P), %eax
	movl   %eax, OFFSET_XFPUSTATE_FIP(%R_fcall0P)
	movw   OFFSET_SFPUSTATE_FCS(%R_fcall0P), %ax
	movw   %ax, OFFSET_XFPUSTATE_FCS(%R_fcall0P)
	movl   OFFSET_SFPUSTATE_FDP(%R_fcall0P), %eax
	movl   %eax, OFFSET_XFPUSTATE_FDP(%R_fcall0P)
	movw   OFFSET_SFPUSTATE_FDS(%R_fcall0P), %ax
	movw   %ax, OFFSET_XFPUSTATE_FDS(%R_fcall0P)
#endif /* !__x86_64__ */

	/* Expand %st(i) registers */
	pushP_cfi_r %Pdi
#ifndef __x86_64__
	pushP_cfi_r %Psi
#endif /* !__x86_64__ */
	cld
	leaP   (OFFSET_SFPUSTATE_ST(8) - 4)(%R_fcall0P), %Psi
	leaP   (OFFSET_XFPUSTATE_ST(8) - 4)(%R_fcall0P), %Pdi
	xorl   %eax, %eax
.rept 8
	stosl /* ------------0000 */
	stosw /* ----------000000 */
	movsw /* --------CC000000 */
#ifdef __x86_64__
	movsq /* CCCCCCCCCC000000 */
#else /* __x86_64__ */
	movsl /* ----CCCCCC000000 */
	movsl /* CCCCCCCCCC000000 */
#endif /* !__x86_64__ */
.endr
	std
#ifdef __x86_64__
	popP_cfi_r %Pdi
#endif /* !__x86_64__ */

	/* NOTE: FPU initialization code assumes that %eax==0 at this point! */
INTERN_FUNCTION(x86_fxsave_section_stmxcsr)
	stmxcsr OFFSET_XFPUSTATE_MXCSR(%R_fcall0P)
END(x86_fxsave_section_stmxcsr)

	/* movl $*x86_fxsave_mxcsr_mask, OFFSET_XFPUSTATE_MXCSR_MASK(%R_fcall0P) */
#if OFFSET_XFPUSTATE_MXCSR_MASK <= 0x7f
	.byte  0xc7, (0x40 | RNO_fcall0), OFFSET_XFPUSTATE_MXCSR_MASK
#else /* OFFSET_XFPUSTATE_MXCSR_MASK <= 0x7f */
	.byte  0xc7, (0x80 | RNO_fcall0)
	.long  OFFSET_XFPUSTATE_MXCSR_MASK
#endif /* OFFSET_XFPUSTATE_MXCSR_MASK > 0x7f */
PUBLIC_FUNCTION(x86_fxsave_mxcsr_mask)
	/* NOTE: We set the default value, as specified by:
	 *   - 11.6.6 Guidelines for Writing to the MXCSR Register
	 */
	.long  0x0000ffbf /* Set of MXCSR_* */
END(x86_fxsave_mxcsr_mask)

	/* NOTE: FPU initialization code assumes that %eax==0 at this point! */
INTERN_FUNCTION(x86_fxsave_section_savexmm)
	/* Save XMM registers. */
	movaps %xmm0, OFFSET_XFPUSTATE_XMM(0)(%R_fcall0P)
	movaps %xmm1, OFFSET_XFPUSTATE_XMM(1)(%R_fcall0P)
	movaps %xmm2, OFFSET_XFPUSTATE_XMM(2)(%R_fcall0P)
	movaps %xmm3, OFFSET_XFPUSTATE_XMM(3)(%R_fcall0P)
	movaps %xmm4, OFFSET_XFPUSTATE_XMM(4)(%R_fcall0P)
	movaps %xmm5, OFFSET_XFPUSTATE_XMM(5)(%R_fcall0P)
	movaps %xmm6, OFFSET_XFPUSTATE_XMM(6)(%R_fcall0P)
	movaps %xmm7, OFFSET_XFPUSTATE_XMM(7)(%R_fcall0P)
#ifdef __x86_64__
	movaps %xmm8, OFFSET_XFPUSTATE_XMM(8)(%R_fcall0P)
	movaps %xmm9, OFFSET_XFPUSTATE_XMM(9)(%R_fcall0P)
	movaps %xmm10, OFFSET_XFPUSTATE_XMM(10)(%R_fcall0P)
	movaps %xmm11, OFFSET_XFPUSTATE_XMM(11)(%R_fcall0P)
	movaps %xmm12, OFFSET_XFPUSTATE_XMM(12)(%R_fcall0P)
	movaps %xmm13, OFFSET_XFPUSTATE_XMM(13)(%R_fcall0P)
	movaps %xmm14, OFFSET_XFPUSTATE_XMM(14)(%R_fcall0P)
	movaps %xmm15, OFFSET_XFPUSTATE_XMM(15)(%R_fcall0P)
#endif /* __x86_64__ */
END(x86_fxsave_section_savexmm)
#ifndef __x86_64__
	popP_cfi_r %Psi
	popP_cfi_r %Pdi
#endif /* !__x86_64__ */
	ret
	.cfi_endproc
END(x86_fxsave)




.section .text
PUBLIC_FUNCTION(x86_fxrstor)
	/* void FCALL x86_fxrstor(struct xfpustate const *state); */
	.cfi_startproc

	pushP_cfi_r %Pdi
#ifndef __x86_64__
	pushP_cfi_r %Psi
#endif /* !__x86_64__ */
	subP  $(SIZEOF_SFPUSTATE), %Psp
	.cfi_adjust_cfa_offset SIZEOF_SFPUSTATE

	/* Load the primary part of the FPU by converting the xfpustate
	 * into  an `sfpustate'  which we'll  keep ontop  of the stack. */
	movzwl OFFSET_XFPUSTATE_FCW(%R_fcall0P), %eax
	movl   %eax, OFFSET_SFPUSTATE_FCW(%Psp)
	movzwl OFFSET_XFPUSTATE_FSW(%R_fcall0P), %eax
	movl   %eax, OFFSET_SFPUSTATE_FSW(%Psp)
#ifndef __x86_64__
	pushP_cfi_r %Pcx
#endif /* !__x86_64__ */
	EXTERN(x86_fxsave_decompress_ftw)
	call   x86_fxsave_decompress_ftw
#ifdef __x86_64__
	movq   SIZEOF_SFPUSTATE(%rsp), %rdi /* Re-load RDI (%R_fcall0P) */
#else /* __x86_64__ */
	popP_cfi_r %Pcx
#endif /* !__x86_64__ */
	movl   %eax, OFFSET_SFPUSTATE_FTW(%Psp)
	movl   OFFSET_XFPUSTATE_FIP(%R_fcall0P), %eax
	movl   %eax, OFFSET_SFPUSTATE_FIP(%Psp)
#ifdef __x86_64__
	movw   $(0), OFFSET_SFPUSTATE_FCS(%rsp)
#else /* __x86_64__ */
	movw   OFFSET_XFPUSTATE_FCS(%R_fcall0P), %ax
	movw   %ax, OFFSET_SFPUSTATE_FCS(%Psp)
#endif /* !__x86_64__ */
	movw   OFFSET_XFPUSTATE_FOP(%R_fcall0P), %ax
	movw   %ax, OFFSET_SFPUSTATE_FOP(%Psp)
	movl   OFFSET_XFPUSTATE_FDP(%R_fcall0P), %eax
	movl   %eax, OFFSET_SFPUSTATE_FDP(%Psp)
#ifdef __x86_64__
	movl   $(0), OFFSET_SFPUSTATE_FDS(%rsp)
#else /* __x86_64__ */
	movzwl OFFSET_XFPUSTATE_FDS(%R_fcall0P), %eax
	movl   %eax, OFFSET_SFPUSTATE_FDS(%Psp)
#endif /* !__x86_64__ */

	/* Reduce %st(i) registers */
	cld
	leaP   OFFSET_XFPUSTATE_ST(0)(%R_fcall0P), %Psi
	leaP   OFFSET_SFPUSTATE_ST(0)(%Psp), %Pdi
.rept 8
#ifdef __x86_64__
	movsq             /* CCCCCCCC--...... */
#else /* __x86_64__ */
	movsl             /* CCCC------...... */
	movsl             /* CCCCCCCC--...... */
#endif /* !__x86_64__ */
	movsw             /* CCCCCCCCCC...... */
	addP   $(6), %Psi /* CCCCCCCCCC------ */
.endr

	frstor (%Psp)
	addP  $(SIZEOF_SFPUSTATE), %Psp
	.cfi_adjust_cfa_offset -SIZEOF_SFPUSTATE
#ifndef __x86_64__
	popP_cfi_r %Psi
#endif /* !__x86_64__ */
	popP_cfi_r %Pdi

INTERN_FUNCTION(x86_fxrstor_section_ldmxcsr)
	ldmxcsr OFFSET_XFPUSTATE_MXCSR(%R_fcall0P)
END(x86_fxrstor_section_ldmxcsr)

INTERN_FUNCTION(x86_fxrstor_section_loadxmm)
	/* Load XMM registers. */
	movaps OFFSET_XFPUSTATE_XMM(0)(%R_fcall0P), %xmm0
	movaps OFFSET_XFPUSTATE_XMM(1)(%R_fcall0P), %xmm1
	movaps OFFSET_XFPUSTATE_XMM(2)(%R_fcall0P), %xmm2
	movaps OFFSET_XFPUSTATE_XMM(3)(%R_fcall0P), %xmm3
	movaps OFFSET_XFPUSTATE_XMM(4)(%R_fcall0P), %xmm4
	movaps OFFSET_XFPUSTATE_XMM(5)(%R_fcall0P), %xmm5
	movaps OFFSET_XFPUSTATE_XMM(6)(%R_fcall0P), %xmm6
	movaps OFFSET_XFPUSTATE_XMM(7)(%R_fcall0P), %xmm7
#ifdef __x86_64__
	movaps OFFSET_XFPUSTATE_XMM(8)(%R_fcall0P), %xmm8
	movaps OFFSET_XFPUSTATE_XMM(9)(%R_fcall0P), %xmm9
	movaps OFFSET_XFPUSTATE_XMM(10)(%R_fcall0P), %xmm10
	movaps OFFSET_XFPUSTATE_XMM(11)(%R_fcall0P), %xmm11
	movaps OFFSET_XFPUSTATE_XMM(12)(%R_fcall0P), %xmm12
	movaps OFFSET_XFPUSTATE_XMM(13)(%R_fcall0P), %xmm13
	movaps OFFSET_XFPUSTATE_XMM(14)(%R_fcall0P), %xmm14
	movaps OFFSET_XFPUSTATE_XMM(15)(%R_fcall0P), %xmm15
#endif /* __x86_64__ */
END(x86_fxrstor_section_loadxmm)

	ret
	.cfi_endproc
END(x86_fxrstor)
#endif /* CONFIG_HAVE_FPU */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_FPU_S */
