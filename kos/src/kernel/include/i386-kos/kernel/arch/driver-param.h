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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_DRIVER_PARAM_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_DRIVER_PARAM_H 1

#include <kernel/compiler.h>

#ifdef BUILDING_KERNEL_CORE
#ifdef __CC__
#include <hybrid/host.h>
#ifdef __x86_64__
#define DEFINE_KERNEL_COMMANDLINE_OPTION_IMPL(section, addr, type, name) \
	__asm__(".pushsection " section "\n\t"                               \
	        ".quad " PP_PRIVATE_STR(addr) "\n\t"                         \
	        ".byte " PP_STR(type) "\n\t"                                 \
	        ".asciz " PP_PRIVATE_STR(name) "\n\t"                        \
	        ".align 8\n\t"                                               \
	        ".popsection")
#else /* __x86_64__ */
#define DEFINE_KERNEL_COMMANDLINE_OPTION_IMPL(section, addr, type, name) \
	__asm__(".pushsection " section "\n\t"                               \
	        ".long " PP_PRIVATE_STR(addr) "\n\t"                         \
	        ".byte " PP_STR(type) "\n\t"                                 \
	        ".asciz " PP_PRIVATE_STR(name) "\n\t"                        \
	        ".align 4\n\t"                                               \
	        ".popsection")
#endif /* !__x86_64__ */
#define DEFINE_VERY_EARLY_KERNEL_COMMANDLINE_OPTION(addr, type, name) \
	DEFINE_KERNEL_COMMANDLINE_OPTION_IMPL(".rodata.free.commandline_options.very_early", addr, type, name)
#define DEFINE_EARLY_KERNEL_COMMANDLINE_OPTION(addr, type, name) \
	DEFINE_KERNEL_COMMANDLINE_OPTION_IMPL(".rodata.free.commandline_options.early", addr, type, name)
#define DEFINE_KERNEL_COMMANDLINE_OPTION(addr, type, name) \
	DEFINE_KERNEL_COMMANDLINE_OPTION_IMPL(".rodata.free.commandline_options.stable", addr, type, name)
#define DEFINE_LATE_KERNEL_COMMANDLINE_OPTION(addr, type, name) \
	DEFINE_KERNEL_COMMANDLINE_OPTION_IMPL(".rodata.free.commandline_options.late", addr, type, name)
#endif /* __CC__ */
#endif /* BUILDING_KERNEL_CORE */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_DRIVER_PARAM_H */
