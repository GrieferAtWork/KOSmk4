/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_COMPILER_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_COMPILER_H 1

#include <__stdinc.h>
#include <hybrid/host.h>

#ifdef __ASSEMBLER__
#ifdef __x86_64__
#define DEFINE_ABS_CALLBACK(sect, func) \
	.pushsection sect; \
		.quad func; \
	.popsection
#define DEFINE_REL_CALLBACK(sect, func) \
	.pushsection sect; \
		.reloc ., R_X86_64_RELATIVE, func; .quad 0; \
	.popsection
#else /* __x86_64__ */
#define DEFINE_ABS_CALLBACK(sect, func) \
	.pushsection sect; \
		.long func; \
	.popsection
#define DEFINE_REL_CALLBACK(sect, func) \
	.pushsection sect; \
		.reloc ., R_386_RELATIVE, func; .long 0; \
	.popsection
#endif /* !__x86_64__ */
#else /* __ASSEMBLER__ */
#ifdef __x86_64__
#define LOAD_FAR_POINTER(x) \
	__XBLOCK({                                        \
		register __UINT64_TYPE__ __lfp_res;           \
		__asm__("movabs $" __PP_PRIVATE_STR(x) ", %0" \
		        : "=r"(__lfp_res));                   \
		__XRETURN __lfp_res;                          \
	})


#define DEFINE_ABS_CALLBACK(sect, func) \
	__asm__(".pushsection " sect "\n\t"            \
	        "\t.quad " PP_PRIVATE_STR(func) "\n\t" \
	        ".popsection")
#define DEFINE_REL_CALLBACK(sect, func) \
	__asm__(".pushsection " sect "\n\t"                                 \
	        "\t.reloc .,R_X86_64_RELATIVE," PP_PRIVATE_STR(func) "\n\t" \
	        "\t.quad 0\n\t"                                             \
	        ".popsection")
#else /* __x86_64__ */
#define DEFINE_ABS_CALLBACK(sect, func) \
    __asm__(".pushsection " sect "\n\t"            \
	        "\t.long " PP_PRIVATE_STR(func) "\n\t" \
	        ".popsection")
#define DEFINE_REL_CALLBACK(sect, func) \
    __asm__(".pushsection " sect "\n\t"                              \
	        "\t.reloc .,R_386_RELATIVE," PP_PRIVATE_STR(func) "\n\t" \
	        "\t.long 0\n\t"                                          \
	        ".popsection")
#endif /* !__x86_64__ */
#endif /* !__ASSEMBLER__ */

#ifdef BUILDING_KERNEL_CORE
#define DEFINE_CALLBACK(sect, func) DEFINE_ABS_CALLBACK(sect, func)
#else /* BUILDING_KERNEL_CORE */
#define DEFINE_CALLBACK(sect, func) DEFINE_REL_CALLBACK(sect, func)
#endif /* !BUILDING_KERNEL_CORE */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_COMPILER_H */
