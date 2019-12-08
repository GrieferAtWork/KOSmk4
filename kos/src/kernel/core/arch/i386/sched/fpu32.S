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

#include <kernel/compiler.h>

#include <kernel/fpu.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/jccN.h>
#include <kos/kernel/fpu-sstate.h>
#include <kos/kernel/fpu-state32.h>


#define MIN_DISTANCE(to, dist) \
	.if dist > (.- to);        \
	.skip dist - (.- to);      \
	.endif


.section .text
	.cfi_startproc
PUBLIC_FUNCTION(x86_fpustate_load)
	/* void FCALL x86_fpustate_load(struct fpustate const *__restrict state); */
	fxrstor (%ecx)
	ret
	MIN_DISTANCE(x86_fpustate_load, 5)
END(x86_fpustate_load)

PUBLIC_FUNCTION(x86_fpustate_save)
	/* void FCALL x86_fpustate_save(struct fpustate *__restrict state); */
	fxsave (%ecx)
	ret
	MIN_DISTANCE(x86_fpustate_save, 5)
END(x86_fpustate_save)

PUBLIC_FUNCTION(x86_fpustate_save_noreset)
	/* void FCALL x86_fpustate_save_noreset(struct fpustate *__restrict state); */
	fxsave (%ecx)
	ret
	MIN_DISTANCE(x86_fpustate_save_noreset, 5)
END(x86_fpustate_save_noreset)

PUBLIC_FUNCTION(x86_fpustate_init)
	/* void FCALL x86_fpustate_init(struct fpustate *__restrict state); */

	/* >> movw   $(FCW_IM | FCW_DM | FCW_ZM | FCW_OM | \
	 * >>          FCW_UM | FCW_PM | 0x40 (???) | \
	 * >>          FCW_PC_EXTEND | FCW_RC_NEAREST),  \
	 * >>        OFFSET_XFPUSTATE_FCW(%ecx) */
#if OFFSET_XFPUSTATE_FCW == 0
	.byte  0x66, 0xc7, 0x01
#else /* OFFSET_XFPUSTATE_FCW == 0 */
	.byte  0x66, 0xc7, 0x41
	.byte  OFFSET_XFPUSTATE_FCW
#endif /* OFFSET_XFPUSTATE_FCW != 0 */
	.word  (FCW_IM | FCW_DM | FCW_ZM | FCW_OM | \
	        FCW_UM | FCW_PM | 0x40 | /* ??? */ \
	        FCW_PC_EXTEND | FCW_RC_NEAREST)

	/* movw   $(FTW_ALLEMPTY),  OFFSET_XFPUSTATE_FTW(%ecx) */
	.byte  0x66, 0xc7, 0x41
INTERN_FUNCTION(x86_fpustate_init_ftw_offset_byte)
	.byte  OFFSET_XFPUSTATE_FTW
END(x86_fpustate_init_ftw_offset_byte)
INTERN_FUNCTION(x86_fpustate_init_ftw_value)
	.word  FTW_ALLEMPTY
END(x86_fpustate_init_ftw_value)

	/* movw   $(MXCSR_...),  OFFSET_XFPUSTATE_MXCSR(%ecx) */
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
	fnsave (%ecx)
	frstor (%ecx) /* Restore fenv since `fnsave' also did `finit' */

	movw   OFFSET_SFPUSTATE_FSW(%ecx), %ax
	movw   %ax, OFFSET_XFPUSTATE_FSW(%ecx)

	/* Compress the FTW word:
	 * >> u8 res = 0;
	 * >> for (unsigned int i = 0; i < 8; ++i) {
	 * >>     if ((ftw & FTW_MASK(i)) != FTW_EMPTY(i))
	 * >>         res |= 1 << i;
	 * >> } */
	pushl_cfi_r %ecx
	EXTERN(x86_fxsave_compress_ftw)
	call   x86_fxsave_compress_ftw
	popl_cfi_r %ecx
	movb   %al, OFFSET_XFPUSTATE_FTW(%ecx)

	movw   OFFSET_SFPUSTATE_FOP(%ecx), %ax
	movw   %ax, OFFSET_XFPUSTATE_FOP(%ecx)
	movl   OFFSET_SFPUSTATE_FIP(%ecx), %eax
	movl   %eax, OFFSET_XFPUSTATE_FIP(%ecx)
	movw   OFFSET_SFPUSTATE_FCS(%ecx), %ax
	movw   %ax, OFFSET_XFPUSTATE_FCS(%ecx)
	movl   OFFSET_SFPUSTATE_FDP(%ecx), %eax
	movl   %eax, OFFSET_XFPUSTATE_FDP(%ecx)
	movw   OFFSET_SFPUSTATE_FDS(%ecx), %ax
	movw   %ax, OFFSET_XFPUSTATE_FDS(%ecx)

	/* Expand %st(i) registers */
	pushl_cfi_r %edi
	pushl_cfi_r %esi
	cld
	leal   (OFFSET_SFPUSTATE_ST(8) - 4)(%ecx), %esi
	leal   (OFFSET_XFPUSTATE_ST(8) - 4)(%ecx), %edi
	xorl   %eax, %eax
.rept 8
	stosl /* ------------0000 */
	stosw /* ----------000000 */
	movsw /* --------CC000000 */
	movsl /* ----CCCCCC000000 */
	movsl /* CCCCCCCCCC000000 */
.endr
	std

	/* NOTE: FPU initialization code assumes that %eax==0 at this point! */
INTERN_FUNCTION(x86_fxsave_section_stmxcsr)
	stmxcsr OFFSET_XFPUSTATE_MXCSR(%ecx)
END(x86_fxsave_section_stmxcsr)

	/* movl $*x86_fxsave_mxcsr_mask, OFFSET_XFPUSTATE_MXCSR_MASK(%ecx) */
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
	movaps %xmm0, OFFSET_XFPUSTATE_XMM(0)(%ecx)
	movaps %xmm1, OFFSET_XFPUSTATE_XMM(1)(%ecx)
	movaps %xmm2, OFFSET_XFPUSTATE_XMM(2)(%ecx)
	movaps %xmm3, OFFSET_XFPUSTATE_XMM(3)(%ecx)
	movaps %xmm4, OFFSET_XFPUSTATE_XMM(4)(%ecx)
	movaps %xmm5, OFFSET_XFPUSTATE_XMM(5)(%ecx)
	movaps %xmm6, OFFSET_XFPUSTATE_XMM(6)(%ecx)
	movaps %xmm7, OFFSET_XFPUSTATE_XMM(7)(%ecx)
END(x86_fxsave_section_savexmm)

	popl_cfi_r %esi
	popl_cfi_r %edi
	ret
	.cfi_endproc
END(x86_fxsave)




.section .text
PUBLIC_FUNCTION(x86_fxrstor)
	/* void FCALL x86_fxrstor(struct xfpustate const *state); */
	.cfi_startproc

	pushl_cfi_r %edi
	pushl_cfi_r %esi
	subl  $(SIZEOF_SFPUSTATE), %esp
	.cfi_adjust_cfa_offset SIZEOF_SFPUSTATE

	/* Load the primary part of the FPU by converting the xfpustate
	 * into an `sfpustate' which we'll keep ontop of the stack. */
	movzwl OFFSET_XFPUSTATE_FCW(%ecx), %eax
	movl   %eax, OFFSET_SFPUSTATE_FCW(%esp)
	movzwl OFFSET_XFPUSTATE_FSW(%ecx), %eax
	movl   %eax, OFFSET_SFPUSTATE_FSW(%esp)
	pushl_cfi_r %ecx
	EXTERN(x86_fxsave_decompress_ftw)
	call   x86_fxsave_decompress_ftw
	popl_cfi_r %ecx
	movl   %eax, OFFSET_SFPUSTATE_FTW(%esp)
	movl   OFFSET_XFPUSTATE_FIP(%ecx), %eax
	movl   %eax, OFFSET_SFPUSTATE_FIP(%esp)
	movw   OFFSET_XFPUSTATE_FCS(%ecx), %ax
	movw   %ax, OFFSET_SFPUSTATE_FCS(%esp)
	movw   OFFSET_XFPUSTATE_FOP(%ecx), %ax
	movw   %ax, OFFSET_SFPUSTATE_FOP(%esp)
	movl   OFFSET_XFPUSTATE_FDP(%ecx), %eax
	movl   %eax, OFFSET_SFPUSTATE_FDP(%esp)
	movzwl OFFSET_XFPUSTATE_FDS(%ecx), %eax
	movl   %eax, OFFSET_SFPUSTATE_FDS(%esp)

	/* Reduce %st(i) registers */
	leal   OFFSET_XFPUSTATE_ST(0)(%ecx), %esi
	leal   OFFSET_SFPUSTATE_ST(0)(%esp), %edi
.rept 8
	movsl             /* CCCC------...... */
	movsl             /* CCCCCCCC--...... */
	movsw             /* CCCCCCCCCC...... */
	addl   $(6), %esi /* CCCCCCCCCC------ */
.endr

	frstor (%esp)
	addl  $(SIZEOF_SFPUSTATE), %esp
	.cfi_adjust_cfa_offset -SIZEOF_SFPUSTATE
	popl_cfi_r %esi
	popl_cfi_r %edi

INTERN_FUNCTION(x86_fxrstor_section_ldmxcsr)
	ldmxcsr OFFSET_XFPUSTATE_MXCSR(%ecx)
END(x86_fxrstor_section_ldmxcsr)

INTERN_FUNCTION(x86_fxrstor_section_loadxmm)
	/* Load XMM registers. */
	movaps OFFSET_XFPUSTATE_XMM(0)(%ecx), %xmm0
	movaps OFFSET_XFPUSTATE_XMM(1)(%ecx), %xmm1
	movaps OFFSET_XFPUSTATE_XMM(2)(%ecx), %xmm2
	movaps OFFSET_XFPUSTATE_XMM(3)(%ecx), %xmm3
	movaps OFFSET_XFPUSTATE_XMM(4)(%ecx), %xmm4
	movaps OFFSET_XFPUSTATE_XMM(5)(%ecx), %xmm5
	movaps OFFSET_XFPUSTATE_XMM(6)(%ecx), %xmm6
	movaps OFFSET_XFPUSTATE_XMM(7)(%ecx), %xmm7
END(x86_fxrstor_section_loadxmm)

	ret
	.cfi_endproc
END(x86_fxrstor)























