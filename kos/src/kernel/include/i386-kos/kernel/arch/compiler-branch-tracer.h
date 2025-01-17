/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_COMPILER_BRANCH_TRACER_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_COMPILER_BRANCH_TRACER_H 1

#include <hybrid/compiler.h>
#include <hybrid/typecore.h>
#include <hybrid/__atomic.h>
#include <hybrid/__asm.h>
#include <hybrid/host.h>
#ifdef __x86_64__
#include <kos/kernel/paging.h>
#endif /* __x86_64__ */

__ASM_BEGIN
__ASM_L(.macro _x86_call_predict_update expr_reg:req)
#ifdef __x86_64__
#define __VARIANT_BWLQ(b, w, l, q)                                          \
	__ASM_L(.ifc __ASM_ARG(\expr_reg),%b; call __predict_update_##b; .else) \
	__ASM_L(.ifc __ASM_ARG(\expr_reg),%w; call __predict_update_##w; .else) \
	__ASM_L(.ifc __ASM_ARG(\expr_reg),%l; call __predict_update_##l; .else) \
	__ASM_L(.ifc __ASM_ARG(\expr_reg),%q; call __predict_update_##q; .else)
/* One variant for every non-REX scratch register, in every width (except for %rdi) */
__VARIANT_BWLQ(al,ax,eax,rax)
__VARIANT_BWLQ(cl,cx,ecx,rcx)
__VARIANT_BWLQ(dl,dx,edx,rdx)
__VARIANT_BWLQ(sil,si,esi,rsi)
#undef __VARIANT_BWLQ
#else /* __x86_64__ */
/* One variant for every scratch register, in every width (except for %ecx) */
__ASM_L(.ifc __ASM_ARG(\expr_reg),%dl; call __predict_update_dl; .else)
__ASM_L(.ifc __ASM_ARG(\expr_reg),%dx; call __predict_update_dx; .else)
__ASM_L(.ifc __ASM_ARG(\expr_reg),%edx; call __predict_update_edx; .else)
__ASM_L(.ifc __ASM_ARG(\expr_reg),%al; call __predict_update_al; .else)
__ASM_L(.ifc __ASM_ARG(\expr_reg),%ax; call __predict_update_ax; .else)
__ASM_L(.ifc __ASM_ARG(\expr_reg),%eax; call __predict_update_eax; .else)
#endif /* !__x86_64__ */
#ifdef __ASSEMBLER__
__ASM_L(.error "Invalid register used: \expr_reg")
#else /* __ASSEMBLER__ */
__ASM_L(.error "Invalid register used: \\expr_reg")
#endif /* !__ASSEMBLER__ */
#ifdef __x86_64__
__ASM_L(.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
#else /* __x86_64__ */
__ASM_L(.endif;.endif;.endif;.endif;.endif;.endif)
#endif /* !__x86_64__ */
__ASM_L(.endm)
__ASM_END


#ifdef __CC__
DECL_BEGIN

/* struct branch_prediction; */
#ifdef __x86_64__
#ifdef BUILDING_KERNEL_CORE
#define __predict_dotrace(section, expr, expected)      \
	__asm__ __volatile__(".weak .Ltracepoint_%=\n\t"    \
	                     ".local .Ltracepoint_%=\n\t"   \
	                     ".hidden .Ltracepoint_%=\n\t"  \
	                     ".pushsection " section "\n\t" \
	                     "991:\n\t"                     \
	                     "\t.int .Ltracepoint_%= - 0xffffffff80000000\n\t" \
	                     "\t.int 0\n\t"                 \
	                     "\t.int 0\n\t"                 \
	                     "\t.int %p0\n\t"               \
	                     ".popsection\n\t"              \
	                     ".Ltracepoint_%=:\n\t"         \
	                     "movq $991b,%%rdi\n\t"         \
	                     "_x86_call_predict_update %1"  \
	                     :                              \
	                     : "X" (expected)               \
	                     , "acdS" (expr)                \
	                     : "rdi")
#else /* BUILDING_KERNEL_CORE */
/* NOTE: I am well aware that `R_X86_64_64' isn't the correct type here!
 *       However, LD will refuse to link `R_X86_64_32' or `R_X86_64_32S'
 *       relocations in ~shared libraries~ (drivers)
 *       So instead we use a 64-bit relocation of which we know that the
 *       upper 32-bit will always be  0 (because the driver will  always
 *       be mapped above `0xffffffff80000000'), and have those upper  32
 *       0-bits overflow into the `bp_wrong' field (which doesn't matter
 *       since that field has to be initialized as 0 anyways...) */
#define __predict_dotrace(section, expr, expected)      \
	__asm__ __volatile__(".weak .Ltracepoint_%=\n\t"    \
	                     ".local .Ltracepoint_%=\n\t"   \
	                     ".hidden .Ltracepoint_%=\n\t"  \
	                     ".pushsection " section "\n\t" \
	                     "991:\n\t"                     \
	                     "\t.reloc ., R_X86_64_64, .Ltracepoint_%= - 0xffffffff80000000\n\t" \
	                     "\t.int 0\n\t"                 \
	                     "\t.int 0\n\t"                 \
	                     "\t.int 0\n\t"                 \
	                     "\t.int %p0\n\t"               \
	                     ".popsection\n\t"              \
	                     ".Ltracepoint_%=:\n\t"         \
	                     "leaq 991b(%%rip),%%rdi\n\t"   \
	                     "_x86_call_predict_update %1"  \
	                     :                              \
	                     : "X" (expected)               \
	                     , "acdS" (expr)                \
	                     : "rdi")
#endif /* !BUILDING_KERNEL_CORE */
#else /* __x86_64__ */
#define __predict_dotrace(section,expr,expected)        \
	__asm__ __volatile__(".weak .Ltracepoint_%=\n\t"    \
	                     ".local .Ltracepoint_%=\n\t"   \
	                     ".hidden .Ltracepoint_%=\n\t"  \
	                     ".pushsection " section "\n\t" \
	                     "991:\n\t"                     \
	                     "\t.long .Ltracepoint_%=\n\t"  \
	                     "\t.long 0\n\t"                \
	                     "\t.long 0\n\t"                \
	                     "\t.long %p0\n\t"              \
	                     ".popsection\n\t"              \
	                     ".Ltracepoint_%=:\n\t"         \
	                     "movl $991b,%%ecx\n\t"         \
	                     "_x86_call_predict_update %1"  \
	                     :                              \
	                     : "X" (expected)               \
	                     , "ad" (expr)                  \
	                     : "ecx")
#endif /* !__x86_64__ */




DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_COMPILER_BRANCH_TRACER_H */
