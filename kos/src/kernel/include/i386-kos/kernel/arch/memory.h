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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_MEMORY_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_MEMORY_H 1

#include <kernel/compiler.h>
#include <hybrid/host.h>

#undef CONFIG_MEMORY_NEED_PAGE_ALLOC32

/* With PAE enabled, we need the `page_alloc32()' function to allocate a VM, since
 * the page directory itself (the 32-byte vector of 4 8-byte entries) needs to be
 * located within the confines of the 32-bit physical address space, as `%cr3' only
 * accepts a 32-bit (and 4096-byte aligned) base address, even in PAE mode. */
#ifndef __x86_64__
#ifndef CONFIG_NO_PAGING_PAE
#define CONFIG_MEMORY_NEED_PAGE_ALLOC32 1
#endif /* !CONFIG_NO_PAGING_PAE */
#endif /* !__x86_64__ */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_MEMORY_H */
