/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_FPU64_S
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_FPU64_S 1

#include <kernel/compiler.h>

#include <kernel/fpu.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/jccN.h>
#include <asm/instr/movzxq.h>
#include <kos/kernel/fpu-sstate.h>
#include <kos/kernel/fpu-state64.h>


#define MIN_DISTANCE(to, dist) \
	.if dist > (.- to);        \
	.skip dist - (.- to);      \
	.endif


.section .text
	.cfi_startproc
PUBLIC_FUNCTION(x86_fpustate_load)
	/* void FCALL x86_fpustate_load(struct fpustate const *__restrict state); */
	fxrstor64 (%rdi)
	ret
	MIN_DISTANCE(x86_fpustate_load, 5)
END(x86_fpustate_load)

PUBLIC_FUNCTION(x86_fpustate_save)
	/* void FCALL x86_fpustate_save(struct fpustate *__restrict state); */
	fxsave64 (%rdi)
	ret
	MIN_DISTANCE(x86_fpustate_save, 5)
END(x86_fpustate_save)

PUBLIC_FUNCTION(x86_fpustate_save_noreset)
	/* void FCALL x86_fpustate_save_noreset(struct fpustate *__restrict state); */
	fxsave64 (%rdi)
	ret
	MIN_DISTANCE(x86_fpustate_save_noreset, 5)
END(x86_fpustate_save_noreset)

PUBLIC_FUNCTION(x86_fpustate_init)
	/* void FCALL x86_fpustate_init(struct fpustate *__restrict state); */

	/* >> movw   $(FCW_IM | FCW_DM | FCW_ZM | FCW_OM | \
	 * >>          FCW_UM | FCW_PM | 0x40 (???) | \
	 * >>          FCW_PC_EXTEND | FCW_RC_NEAREST),  \
	 * >>        OFFSET_XFPUSTATE_FCW(%rdi) */
	movw   $(FCW_IM | FCW_DM | FCW_ZM | FCW_OM | \
	         FCW_UM | FCW_PM | 0x40 | \
	         FCW_PC_EXTEND | FCW_RC_NEAREST),  \
	       OFFSET_XFPUSTATE_FCW(%rdi) /* TODO: Remove me */
#if OFFSET_XFPUSTATE_FCW == 0
	.byte  0x66, 0xc7, 0x01
#else /* OFFSET_XFPUSTATE_FCW == 0 */
	.byte  0x66, 0xc7, 0x41
	.byte  OFFSET_XFPUSTATE_FCW
#endif /* OFFSET_XFPUSTATE_FCW != 0 */
	.word  (FCW_IM | FCW_DM | FCW_ZM | FCW_OM | \
	        FCW_UM | FCW_PM | 0x40 | /* ??? */ \
	        FCW_PC_EXTEND | FCW_RC_NEAREST)

	/* movw   $(FTW_ALLEMPTY),  OFFSET_XFPUSTATE_FTW(%rdi) */
	movw   $(FTW_ALLEMPTY),  OFFSET_XFPUSTATE_FTW(%rdi) /* TODO: Remove me */
	.byte  0x66, 0xc7, 0x41
INTERN_FUNCTION(x86_fpustate_init_ftw_offset_byte)
	.byte  OFFSET_XFPUSTATE_FTW
END(x86_fpustate_init_ftw_offset_byte)
INTERN_FUNCTION(x86_fpustate_init_ftw_value)
	.word  FTW_ALLEMPTY
END(x86_fpustate_init_ftw_value)

	/* movw   $(MXCSR_...),  OFFSET_XFPUSTATE_MXCSR(%rdi) */
	movw   $(0x1234),  OFFSET_XFPUSTATE_MXCSR(%rdi) /* TODO: Remove me */
INTERN_FUNCTION(x86_fpustate_init_mxcsr)
	.byte  0xc7, 0x41
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
	fnsave (%rdi)
	frstor (%rdi) /* Restore fenv since `fnsave' also did `finit' */

	movw   OFFSET_SFPUSTATE_FSW(%rdi), %ax
	movw   %ax, OFFSET_XFPUSTATE_FSW(%rdi)

	/* Compress the FTW word:
	 * >> u8 res = 0;
	 * >> for (unsigned int i = 0; i < 8; ++i) {
	 * >>     if ((ftw & FTW_MASK(i)) != FTW_EMPTY(i))
	 * >>         res |= 1 << i;
	 * >> } */
	pushq_cfi_r %rdi
	EXTERN(x86_fxsave_compress_ftw)
	call   x86_fxsave_compress_ftw
	popq_cfi_r %rdi
	movb   %al, OFFSET_XFPUSTATE_FTW(%rdi)

	movw   OFFSET_SFPUSTATE_FOP(%rdi), %ax
	movw   %ax, OFFSET_XFPUSTATE_FOP(%rdi)
	movzlq OFFSET_SFPUSTATE_FIP(%rdi), %rax
	movq   %rax, OFFSET_XFPUSTATE_FIP(%rdi)
	movzlq OFFSET_SFPUSTATE_FDP(%rdi), %rax
	movq   %rax, OFFSET_XFPUSTATE_FDP(%rdi)

	/* Expand %st(i) registers */
	pushq_cfi_r %rdi
	cld
	leaq   (OFFSET_SFPUSTATE_ST(8) - 4)(%rdi), %rsi
	leaq   (OFFSET_XFPUSTATE_ST(8) - 4)(%rdi), %rdi
	xorl   %eax, %eax
.rept 8
	stosl /* ------------0000 */
	stosw /* ----------000000 */
	movsw /* --------CC000000 */
	movsq /* CCCCCCCCCC000000 */
.endr
	std
	popq_cfi_r %rdi

	/* NOTE: FPU initialization code assumes that %eax==0 at this point! */
INTERN_FUNCTION(x86_fxsave_section_stmxcsr)
	stmxcsr OFFSET_XFPUSTATE_MXCSR(%rdi)
END(x86_fxsave_section_stmxcsr)

	/* movl $*x86_fxsave_mxcsr_mask, OFFSET_XFPUSTATE_MXCSR_MASK(%rdi) */
	movl   $0x12345678, OFFSET_XFPUSTATE_MXCSR_MASK(%rdi) /* TODO: Remove me */
#if OFFSET_XFPUSTATE_MXCSR_MASK <= 0x7f
	.byte  0xc7, 0x41, OFFSET_XFPUSTATE_MXCSR_MASK
#else /* OFFSET_XFPUSTATE_MXCSR_MASK <= 0x7f */
	.byte  0xc7, 0x81
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
	movaps %xmm0, OFFSET_XFPUSTATE_XMM(0)(%rdi)
	movaps %xmm1, OFFSET_XFPUSTATE_XMM(1)(%rdi)
	movaps %xmm2, OFFSET_XFPUSTATE_XMM(2)(%rdi)
	movaps %xmm3, OFFSET_XFPUSTATE_XMM(3)(%rdi)
	movaps %xmm4, OFFSET_XFPUSTATE_XMM(4)(%rdi)
	movaps %xmm5, OFFSET_XFPUSTATE_XMM(5)(%rdi)
	movaps %xmm6, OFFSET_XFPUSTATE_XMM(6)(%rdi)
	movaps %xmm7, OFFSET_XFPUSTATE_XMM(7)(%rdi)
	movaps %xmm8, OFFSET_XFPUSTATE_XMM(8)(%rdi)
	movaps %xmm9, OFFSET_XFPUSTATE_XMM(9)(%rdi)
	movaps %xmm10, OFFSET_XFPUSTATE_XMM(10)(%rdi)
	movaps %xmm11, OFFSET_XFPUSTATE_XMM(11)(%rdi)
	movaps %xmm12, OFFSET_XFPUSTATE_XMM(12)(%rdi)
	movaps %xmm13, OFFSET_XFPUSTATE_XMM(13)(%rdi)
	movaps %xmm14, OFFSET_XFPUSTATE_XMM(14)(%rdi)
	movaps %xmm15, OFFSET_XFPUSTATE_XMM(15)(%rdi)
END(x86_fxsave_section_savexmm)
	ret
	.cfi_endproc
END(x86_fxsave)




.section .text
PUBLIC_FUNCTION(x86_fxrstor)
	/* void FCALL x86_fxrstor(struct xfpustate const *state); */
	.cfi_startproc

	pushq_cfi_r %rdi
	subq  $(SIZEOF_SFPUSTATE), %rsp
	.cfi_adjust_cfa_offset SIZEOF_SFPUSTATE

	/* Load the primary part of the FPU by converting the xfpustate
	 * into an `sfpustate' which we'll keep ontop of the stack. */
	movzwl OFFSET_XFPUSTATE_FCW(%rdi), %eax
	movl   %eax, OFFSET_SFPUSTATE_FCW(%rsp)
	movzwl OFFSET_XFPUSTATE_FSW(%rdi), %eax
	movl   %eax, OFFSET_SFPUSTATE_FSW(%rsp)
	EXTERN(x86_fxsave_decompress_ftw)
	call   x86_fxsave_decompress_ftw
	movq   SIZEOF_SFPUSTATE(%rsp), %rdi /* Re-load RDI */
	movl   %eax, OFFSET_SFPUSTATE_FTW(%rsp)
	movl   OFFSET_XFPUSTATE_FIP(%rdi), %eax
	movl   %eax, OFFSET_SFPUSTATE_FIP(%rsp)
	movw   $(0), OFFSET_SFPUSTATE_FCS(%rsp)
	movw   OFFSET_XFPUSTATE_FOP(%rdi), %ax
	movw   %ax, OFFSET_SFPUSTATE_FOP(%rsp)
	movl   OFFSET_XFPUSTATE_FDP(%rdi), %eax
	movl   %eax, OFFSET_SFPUSTATE_FDP(%rsp)
	movl   $(0), OFFSET_SFPUSTATE_FDS(%rsp)

	/* Reduce %st(i) registers */
	leaq   OFFSET_XFPUSTATE_ST(0)(%rdi), %rsi
	leaq   OFFSET_SFPUSTATE_ST(0)(%rsp), %rdi
.rept 8
	movsl             /* CCCC------...... */
	movsl             /* CCCCCCCC--...... */
	movsw             /* CCCCCCCCCC...... */
	addl   $(6), %esi /* CCCCCCCCCC------ */
.endr

	frstor (%rsp)
	addq  $(SIZEOF_SFPUSTATE), %rsp
	.cfi_adjust_cfa_offset -SIZEOF_SFPUSTATE
	popq_cfi_r %rdi

INTERN_FUNCTION(x86_fxrstor_section_ldmxcsr)
	ldmxcsr OFFSET_XFPUSTATE_MXCSR(%rdi)
END(x86_fxrstor_section_ldmxcsr)

INTERN_FUNCTION(x86_fxrstor_section_loadxmm)
	/* Load XMM registers. */
	movaps OFFSET_XFPUSTATE_XMM(0)(%rdi), %xmm0
	movaps OFFSET_XFPUSTATE_XMM(1)(%rdi), %xmm1
	movaps OFFSET_XFPUSTATE_XMM(2)(%rdi), %xmm2
	movaps OFFSET_XFPUSTATE_XMM(3)(%rdi), %xmm3
	movaps OFFSET_XFPUSTATE_XMM(4)(%rdi), %xmm4
	movaps OFFSET_XFPUSTATE_XMM(5)(%rdi), %xmm5
	movaps OFFSET_XFPUSTATE_XMM(6)(%rdi), %xmm6
	movaps OFFSET_XFPUSTATE_XMM(7)(%rdi), %xmm7
	movaps OFFSET_XFPUSTATE_XMM(8)(%rdi), %xmm8
	movaps OFFSET_XFPUSTATE_XMM(9)(%rdi), %xmm9
	movaps OFFSET_XFPUSTATE_XMM(10)(%rdi), %xmm10
	movaps OFFSET_XFPUSTATE_XMM(11)(%rdi), %xmm11
	movaps OFFSET_XFPUSTATE_XMM(12)(%rdi), %xmm12
	movaps OFFSET_XFPUSTATE_XMM(13)(%rdi), %xmm13
	movaps OFFSET_XFPUSTATE_XMM(14)(%rdi), %xmm14
	movaps OFFSET_XFPUSTATE_XMM(15)(%rdi), %xmm15
END(x86_fxrstor_section_loadxmm)

	ret
	.cfi_endproc
END(x86_fxrstor)

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_FPU64_S */
