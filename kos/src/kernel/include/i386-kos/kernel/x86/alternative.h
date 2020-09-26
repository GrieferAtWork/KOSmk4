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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_ALTERNATIVE_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_ALTERNATIVE_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/__asm.h>

#include <asm/asmword.h>
#include <asm/cpu-feature.h>

#ifdef __CC__
DECL_BEGIN

struct x86_alternative {
	/* NOTE: Adjacent feature descriptors with the same xa_start/xa_end are skipped
	 *       once the first feature descriptor for which `xa_feature' is true has
	 *       been found. */
	u32       xa_feature; /* Feature code specifying when this alternative should be
	                       * used (s.a. `X86_FEATURE()' from <asm/cpu-features.h>) */
	u32       xa_altlen;  /* Length of `xa_altcode' */
	uintptr_t xa_start;   /* (Module-relative) starting address of where to apply this alternative. */
	uintptr_t xa_end;     /* (Module-relative) end address of where to apply this alternative. */
	uintptr_t xa_altcode; /* (Module-relative) starting address of the alternate code blob. */
};

#ifdef CONFIG_BUILDING_KERNEL_CORE
INTDEF FREE struct x86_alternative const __x86_alternatives_start[];
INTDEF FREE struct x86_alternative const __x86_alternatives_end[];
#endif /* CONFIG_BUILDING_KERNEL_CORE */

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

__ASM_L(.macro .alt_if feature:req)
__ASM_L(.Lalt_maxlength = 0)
__ASM_L(	.pushsection .alternatives, "a")
__ASM_L(		.word32 __ASM_ARG(\feature))
__ASM_L(		.word32 (774f - 773f))
#ifdef CONFIG_BUILDING_KERNEL_CORE
__ASM_L(		.wordptr 771f)
__ASM_L(		.wordptr 772f)
__ASM_L(		.wordptr 773f)
#else /* CONFIG_BUILDING_KERNEL_CORE */
__ASM_L(		.wordrel 771f)
__ASM_L(		.wordrel 772f)
__ASM_L(		.wordrel 773f)
#endif /* !CONFIG_BUILDING_KERNEL_CORE */
__ASM_L(	.popsection)
__ASM_L(	.pushsection %S.alternative)
__ASM_L(773:)
__ASM_L(.endm)

__ASM_L(.macro .alt_elif feature:req)
__ASM_L(774:)
__ASM_L(.if (. - 773b) > .Lalt_maxlength)
__ASM_L(.Lalt_maxlength = (. - 773b))
__ASM_L(.endif)
__ASM_L(	.pushsection .alternatives, "a")
__ASM_L(		.word32 __ASM_ARG(\feature))
__ASM_L(		.word32 (774f - 773f))
#ifdef CONFIG_BUILDING_KERNEL_CORE
__ASM_L(		.wordptr 771f)
__ASM_L(		.wordptr 772f)
__ASM_L(		.wordptr 773f)
#else /* CONFIG_BUILDING_KERNEL_CORE */
__ASM_L(		.wordrel 771f)
__ASM_L(		.wordrel 772f)
__ASM_L(		.wordrel 773f)
#endif /* !CONFIG_BUILDING_KERNEL_CORE */
__ASM_L(	.popsection)
__ASM_L(773:)
__ASM_L(.endm)

__ASM_L(.macro .alt_else)
__ASM_L(774:)
__ASM_L(.if (. - 773b) > .Lalt_maxlength)
__ASM_L(.Lalt_maxlength = (. - 773b))
__ASM_L(.endif)
__ASM_L(	.popsection)
__ASM_L(	.pushsection .alternatives, "a")
__ASM_L(		.word32 X86_FEAT_TRUE)
__ASM_L(		.word32 (774f - 773f))
#ifdef CONFIG_BUILDING_KERNEL_CORE
__ASM_L(		.wordptr 771f)
__ASM_L(		.wordptr 772f)
__ASM_L(		.wordptr 773f)
#else /* CONFIG_BUILDING_KERNEL_CORE */
__ASM_L(		.wordrel 771f)
__ASM_L(		.wordrel 772f)
__ASM_L(		.wordrel 773f)
#endif /* !CONFIG_BUILDING_KERNEL_CORE */
__ASM_L(	.popsection)
__ASM_L(771:)
__ASM_L(.endm)

__ASM_L(.macro .alt_endif)
__ASM_L(774:)
__ASM_L(.if .Lalt_maxlength > (. - 771b))
__ASM_L(.skip .Lalt_maxlength - (. - 771b), 0x90)
__ASM_L(.endif)
__ASM_L(773:)
__ASM_L(.endm)
__ASM_END



#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_ALTERNATIVE_H */
