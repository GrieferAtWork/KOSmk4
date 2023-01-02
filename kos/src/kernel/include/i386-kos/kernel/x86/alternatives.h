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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_ALTERNATIVES_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_ALTERNATIVES_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/__asm.h>

#include <asm/asmword.h>
#include <asm/cpu-features.h>

#ifdef __CC__
DECL_BEGIN

struct x86_alternative {
	/* NOTE: Adjacent feature descriptors with the same xa_start/xa_end are skipped
	 *       once the first feature descriptor  for which `xa_feature' is true  has
	 *       been found. */
	u32       xa_feature; /* Feature code specifying when this alternative should be
	                       * used (s.a.  `X86_FEATURE()' from  <asm/cpu-features.h>) */
	u32       xa_altlen;  /* Length of `xa_altcode' */
	uintptr_t xa_start;   /* (Module-relative) starting address of where to apply this alternative. */
	uintptr_t xa_end;     /* (Module-relative) end address of where to apply this alternative. */
	uintptr_t xa_altcode; /* (Module-relative) starting address of the alternate code blob. */
};

#ifdef BUILDING_KERNEL_CORE
INTDEF FREE struct x86_alternative const __x86_alternatives_start[];
INTDEF FREE struct x86_alternative const __x86_alternatives_end[];
#endif /* BUILDING_KERNEL_CORE */

DECL_END
#endif /* __CC__ */

/* Assembler macros for constructing feature-specific program text.
 * WARNING: These macros cannot be nested!
 * >>     movl $SYS_exit, %eax
 * >> .alt_if X86_FEAT_SEP
 * >>     sysenter
 * >> .alt_else
 * >>     int $0x80
 * >> .alt_endif
 */
__ASM_BEGIN

/* Local labels:
 *    771: Start of base-code in primary section
 *    772: Start of current alt-code
 *    773: End of current alt-code
 *    774: End of base-code in primary section
 */

__ASM_L(.macro .alt_if feature:req)
__ASM_L(771:)
__ASM_L(.Lalt_maxlength = 0)
__ASM_L(	.pushsection .alternatives, "a")
__ASM_L(		.word32 __ASM_ARG(\feature))
__ASM_L(		.word32 (773f - 772f))
#ifdef BUILDING_KERNEL_CORE
__ASM_L(		.wordptr 771b)
__ASM_L(		.wordptr 774f)
__ASM_L(		.wordptr 772f)
#else /* BUILDING_KERNEL_CORE */
__ASM_L(		.wordrel 771b)
__ASM_L(		.wordrel 774f)
__ASM_L(		.wordrel 772f)
#endif /* !BUILDING_KERNEL_CORE */
__ASM_L(	.popsection)
__ASM_L(	.pushsection .text.free.alternatives)
__ASM_L(772:)
__ASM_L(.endm)

__ASM_L(.macro .alt_elseif feature:req)
__ASM_L(773:)
__ASM_L(.if (. - 772b) > .Lalt_maxlength)
__ASM_L(.Lalt_maxlength = (. - 772b))
__ASM_L(.endif)
__ASM_L(	.popsection)
__ASM_L(	.pushsection .alternatives, "a")
__ASM_L(		.word32 __ASM_ARG(\feature))
__ASM_L(		.word32 (773f - 772f))
#ifdef BUILDING_KERNEL_CORE
__ASM_L(		.wordptr 771b)
__ASM_L(		.wordptr 774f)
__ASM_L(		.wordptr 772f)
#else /* BUILDING_KERNEL_CORE */
__ASM_L(		.wordrel 771b)
__ASM_L(		.wordrel 774f)
__ASM_L(		.wordrel 772f)
#endif /* !BUILDING_KERNEL_CORE */
__ASM_L(	.popsection)
__ASM_L(	.pushsection .text.free.alternatives)
__ASM_L(772:)
__ASM_L(.endm)

__ASM_L(.macro .alt_else)
__ASM_L(773:)
__ASM_L(.if (. - 772b) > .Lalt_maxlength)
__ASM_L(.Lalt_maxlength = (. - 772b))
__ASM_L(.endif)
__ASM_L(	.popsection)
__ASM_L(772:) /* Only needed for consistency (772b is always the start of the current ALT-block) */
__ASM_L(.endm)

__ASM_L(.macro .alt_endif)
__ASM_L(.if .Lalt_maxlength > (. - 771b))
__ASM_L(.skip .Lalt_maxlength - (. - 771b), 0x90)
__ASM_L(.endif)
__ASM_L(774:)
__ASM_L(.endm)

/* Helper macros: Conditional jump/call instruction for use within .alt-code */
__ASM_L(.macro alt_jmp8   sym:req; .byte 0xeb; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jo8    sym:req; .byte 0x70; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jno8   sym:req; .byte 0x71; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jb8    sym:req; .byte 0x72; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jc8    sym:req; .byte 0x72; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jnae8  sym:req; .byte 0x72; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jae8   sym:req; .byte 0x73; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jnb8   sym:req; .byte 0x73; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jnc8   sym:req; .byte 0x73; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_je8    sym:req; .byte 0x74; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jz8    sym:req; .byte 0x74; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jne8   sym:req; .byte 0x75; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jnz8   sym:req; .byte 0x75; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jbe8   sym:req; .byte 0x76; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jna8   sym:req; .byte 0x76; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_ja8    sym:req; .byte 0x77; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jnbe8  sym:req; .byte 0x77; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_js8    sym:req; .byte 0x78; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jns8   sym:req; .byte 0x79; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jp8    sym:req; .byte 0x7a; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jpe8   sym:req; .byte 0x7a; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jnp8   sym:req; .byte 0x7b; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jpo8   sym:req; .byte 0x7b; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jl8    sym:req; .byte 0x7c; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jnge8  sym:req; .byte 0x7c; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jge8   sym:req; .byte 0x7d; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jnl8   sym:req; .byte 0x7d; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jle8   sym:req; .byte 0x7e; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jng8   sym:req; .byte 0x7e; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jg8    sym:req; .byte 0x7f; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jnle8  sym:req; .byte 0x7f; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jcxz8  sym:req; .byte 0x66, 0xe3; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
__ASM_L(.macro alt_jecxz8 sym:req; .byte 0xe3; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
#ifdef __x86_64__
__ASM_L(.macro alt_jrcxz8 sym:req; .byte 0x48, 0xe3; .byte __ASM_ARG(\sym) - ((771b+(.-772b))+1); .endm)
#endif /* __x86_64__ */
__ASM_L(.macro alt_jmp32   sym:req; .byte 0xe9; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jo32    sym:req; .byte 0x0f, 0x80; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jno32   sym:req; .byte 0x0f, 0x81; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jb32    sym:req; .byte 0x0f, 0x82; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jc32    sym:req; .byte 0x0f, 0x82; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jnae32  sym:req; .byte 0x0f, 0x82; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jae32   sym:req; .byte 0x0f, 0x83; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jnb32   sym:req; .byte 0x0f, 0x83; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jnc32   sym:req; .byte 0x0f, 0x83; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_je32    sym:req; .byte 0x0f, 0x84; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jz32    sym:req; .byte 0x0f, 0x84; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jne32   sym:req; .byte 0x0f, 0x85; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jnz32   sym:req; .byte 0x0f, 0x85; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jbe32   sym:req; .byte 0x0f, 0x86; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jna32   sym:req; .byte 0x0f, 0x86; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_ja32    sym:req; .byte 0x0f, 0x87; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jnbe32  sym:req; .byte 0x0f, 0x87; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_js32    sym:req; .byte 0x0f, 0x88; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jns32   sym:req; .byte 0x0f, 0x89; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jp32    sym:req; .byte 0x0f, 0x8a; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jpe32   sym:req; .byte 0x0f, 0x8a; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jnp32   sym:req; .byte 0x0f, 0x8b; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jpo32   sym:req; .byte 0x0f, 0x8b; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jl32    sym:req; .byte 0x0f, 0x8c; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jnge32  sym:req; .byte 0x0f, 0x8c; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jge32   sym:req; .byte 0x0f, 0x8d; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jnl32   sym:req; .byte 0x0f, 0x8d; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jle32   sym:req; .byte 0x0f, 0x8e; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jng32   sym:req; .byte 0x0f, 0x8e; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jg32    sym:req; .byte 0x0f, 0x8f; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_jnle32  sym:req; .byte 0x0f, 0x8f; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_L(.macro alt_call    sym:req; .byte 0xe8; .long __ASM_ARG(\sym) - ((771b+(.-772b))+4); .endm)
__ASM_END



#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_ALTERNATIVES_H */
