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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_ARCH_COMPILER_H
#define GUARD_KERNEL_INCLUDE_KERNEL_ARCH_COMPILER_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>

#ifdef __ASSEMBLER__
#if __SIZEOF_POINTER__ > 8
#define DEFINE_ABS_CALLBACK(sect, func) \
	.pushsection sect; \
		.quad func; \
	.popsection
#else
#define DEFINE_ABS_CALLBACK(sect, func) \
	.pushsection sect; \
		.long func; \
	.popsection
#endif
#else
#if __SIZEOF_POINTER__ > 8
#define DEFINE_ABS_CALLBACK(sect,func) \
	__asm__(".pushsection " sect "\n\t" \
	        "\t.quad " PP_PRIVATE_STR(func) "\n\t" \
	        ".popsection")
#else
#define DEFINE_ABS_CALLBACK(sect,func) \
	__asm__(".pushsection " sect "\n\t" \
	        "\t.long " PP_PRIVATE_STR(func) "\n\t" \
	        ".popsection")
#endif
#endif

#ifdef BUILDING_KERNEL_CORE
#define DEFINE_CALLBACK(sect,func) DEFINE_ABS_CALLBACK(sect,func)
#endif /* BUILDING_KERNEL_CORE */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_ARCH_COMPILER_H */
