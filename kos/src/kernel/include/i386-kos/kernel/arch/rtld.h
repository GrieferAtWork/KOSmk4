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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_RTLD_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_RTLD_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/host.h>

DECL_BEGIN

#ifdef __CC__

/* A static VM file blob for the building RTLD user-space program.
 * This is a raw ELF binary blob that is hard-linked into the kernel
 * core, and is mapped via copy-on-write into any user-space process
 * that requests the use of a dynamic linker
 * NOTE: The associated source code can be found in `/kos/src/libdl/...' */
DATDEF struct vm_ramfile system_rtld32_file;

/* Base address and size symbols for the system RTLD */
DATDEF byte_t system_rtld32[];
#undef system_rtld32_size
#ifdef __INTELLISENSE__
DATDEF size_t const system_rtld32_size;
#else /* __INTELLISENSE__ */
DATDEF byte_t system_rtld32_size[];
#define system_rtld32_size ((size_t)system_rtld32_size)
#endif /* !__INTELLISENSE__ */

#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_RTLD_H */
