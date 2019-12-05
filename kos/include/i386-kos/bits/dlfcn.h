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
#ifndef _I386_KOS_BITS_DLFCN_H
#define _I386_KOS_BITS_DLFCN_H 1

#include <__stdinc.h>
#include <hybrid/host.h>

#undef __DL_REGISTER_CACHE
#ifdef __CC__
#ifdef __x86_64__
#define __DL_REGISTER_CACHE(function_name)                        \
	__asm__(".pushsection .dl_caches, \"\"\n\t"                   \
	        ".align 8\n\t"                                        \
	        ".reloc ., R_X86_64_RELATIVE, " #function_name "\n\t" \
	        ".quad 0\n\t"                                         \
	        ".popsection");                                       \
	__PRIVATE __ATTR_USED int (__ATTR_SYSVABI function_name)(void)
#else /* __x86_64__ */
#define __DL_REGISTER_CACHE(function_name)                     \
	__asm__(".pushsection .dl_caches, \"\"\n\t"                \
	        ".align 4\n\t"                                     \
	        ".reloc ., R_386_RELATIVE, " #function_name "\n\t" \
	        ".long 0\n\t"                                      \
	        ".popsection");                                    \
	__PRIVATE __ATTR_USED int (__ATTR_CDECL function_name)(void)
#endif /* !__x86_64__ */
#else /* __CC__ */
#ifdef __x86_64__
#define __DL_REGISTER_CACHE(function_name)          \
	.pushsection .dl_caches, "";                    \
		.align 8;                                   \
		.reloc ., R_X86_64_RELATIVE, function_name; \
		.quad 0;                                    \
	.popsection;
#else /* __x86_64__ */
#define __DL_REGISTER_CACHE(function_name)       \
	.pushsection .dl_caches, "";                 \
		.align 4;                                \
		.reloc ., R_386_RELATIVE, function_name; \
		.long 0;                                 \
	.popsection;
#endif /* !__x86_64__ */
#endif /* !__CC__ */

#include "../../bits/dlfcn.h"

#endif /* !_I386_KOS_BITS_DLFCN_H */
