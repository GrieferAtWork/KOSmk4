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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_EXECABI_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_EXECABI_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/host.h>

#ifdef __x86_64__
#define CONFIG_EXECABI_ARCH_HEADER_DEFINES_COMPAT_ELFEXEC_SYSTEM_RTLD 1
#define CONFIG_EXECABI_ARCH_HEADER_DEFINES_COMPAT_ELFEXEC_SYSTEM_RTLD_FILE 1
#define compat_execabi_system_rtld      execabi_system_rtld32
#define compat_execabi_system_rtld_size execabi_system_rtld32_size
#define compat_execabi_system_rtld_file execabi_system_rtld32_file
#endif /* __x86_64__ */

#ifdef __CC__
DECL_BEGIN

#ifdef __x86_64__

/* Base address and size symbols for the system RTLD */
DATDEF byte_t execabi_system_rtld32[];
#undef execabi_system_rtld32_size
#ifdef __INTELLISENSE__
DATDEF size_t const execabi_system_rtld32_size;
#else /* __INTELLISENSE__ */
DATDEF byte_t execabi_system_rtld32_size[];
#define execabi_system_rtld32_size ((size_t)execabi_system_rtld32_size)
#endif /* !__INTELLISENSE__ */

/* A static VM file blob for the building RTLD user-space program.
 * This is a raw ELF binary blob that is hard-linked into the kernel
 * core, and is mapped via copy-on-write into any user-space process
 * that requests the use of a dynamic linker
 * NOTE: The associated source code can be found in `/kos/src/libdl/...' */
DATDEF struct vm_ramfile execabi_system_rtld32_file;
#endif /* __x86_64__ */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_EXECABI_H */
