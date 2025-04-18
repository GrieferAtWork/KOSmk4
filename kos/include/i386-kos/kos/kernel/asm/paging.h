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
/*!replace_with_include <kos/kernel/paging.h>*/
#ifndef _I386_KOS_KOS_KERNEL_ASM_PAGING_H
#define _I386_KOS_KOS_KERNEL_ASM_PAGING_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#undef KERNELSPACE_BASE
#undef KERNEL_CORE_BASE

#undef KERNELSPACE_END
#undef KERNELSPACE_LOWMEM
#define KERNELSPACE_HIGHMEM 1

#ifdef __x86_64__
#define USERSPACE_END    __UINT64_C(0x0000800000000000) /* Upper address space limit for user-space (first invalid address) */
#define KERNELSPACE_BASE __UINT64_C(0xffff800000000000) /* Lower address space limit for kernel-space */
#define KERNEL_CORE_BASE __UINT64_C(0xffffffff80000000) /* Load address of the kernel core. (-2GB) */

#define COMPAT_USERSPACE_END    __UINT32_C(0xc0000000) /* Upper address space limit for user-space (as exposed to programs running in compatibility mode) */
#define COMPAT_KERNELSPACE_BASE __UINT32_C(0xc0000000) /* lower address space limit for kernel-space (as exposed to programs running in compatibility mode) */

/* Check if a given physical address range is identity mapped. */
#if 1 /* TODO: Add a configuration option for this. */

/* First first half of the kernel address space is used as identity mapping
 * for the  first  64TiB  (yes:  that is  Terrabyte)  of  physical  memory. */
#define KERNEL_PHYS2VIRT_BASE __UINT64_C(0xffff880000000000) /* Start of the physical identity mapping */
#define KERNEL_PHYS2VIRT_SIZE __UINT64_C(0x0000400000000000) /* Size of the physical identity mapping (== 64TiB) */
#define KERNEL_PHYS2VIRT_MIN  KERNEL_PHYS2VIRT_BASE          /* Lowest address apart of the physical identity mapping */
#define KERNEL_PHYS2VIRT_MAX  __UINT64_C(0xffffc7ffffffffff) /* Greatest address apart of the physical identity mapping */

/* Accessor macros for physical identity translation. */
#define PHYS_IS_IDENTITY(base, num_bytes) (((__UINT64_TYPE__)(base) + (__UINT64_TYPE__)(num_bytes)) <= KERNEL_PHYS2VIRT_SIZE)
#define PHYS_TO_IDENTITY(base)            ((__BYTE_TYPE__ *)((__UINT64_TYPE__)(base) + KERNEL_PHYS2VIRT_BASE))
#define PHYS_IS_IDENTITY_PAGE(pageno)     ((__UINT64_TYPE__)(pageno) < __UINT64_C(0x400000000))
#define PHYS_TO_IDENTITY_PAGE(pageno)     ((__BYTE_TYPE__ *)(((__UINT64_TYPE__)(pageno) * 4096) + KERNEL_PHYS2VIRT_BASE))
#endif /* Phys-identity-enabled */


/* NOTE: All non-canonical bits must be equal to the most significant canonical bit.
 *       In other words: Memory addresses behave as signed with the bits 48-63 being
 *       a sign-extension of bit 47 */
#define X86_64_ADDRBUS_CANONBITS    48
#define X86_64_ADDRBUS_CANONMASK    __UINT64_C(0x0000ffffffffffff)
#define X86_64_ADDRBUS_NONCANONBITS 16
#define X86_64_ADDRBUS_NONCANONMASK __UINT64_C(0xffff000000000000)

#define X86_64_ADDRBUS_NONCANON_MIN __UINT64_C(0x0000800000000000)
#define X86_64_ADDRBUS_NONCANON_MAX __UINT64_C(0xffff7fffffffffff)
#define ADDR_IS_NONCANON(addr)                                        \
	(__CCAST(__UINT64_TYPE__)(addr) >= X86_64_ADDRBUS_NONCANON_MIN && \
	 __CCAST(__UINT64_TYPE__)(addr) <= X86_64_ADDRBUS_NONCANON_MAX)
#define ADDR_IS_CANON(addr)                                          \
	(__CCAST(__UINT64_TYPE__)(addr) < X86_64_ADDRBUS_NONCANON_MIN || \
	 __CCAST(__UINT64_TYPE__)(addr) > X86_64_ADDRBUS_NONCANON_MAX)

#else /* __x86_64__ */
#define USERSPACE_END         __UINT32_C(0xc0000000) /* Upper address space limit for user-space */
#define KERNELSPACE_BASE      __UINT32_C(0xc0000000) /* lower address space limit for kernel-space */
#define KERNEL_CORE_BASE      __UINT32_C(0xc0000000) /* Load address of the kernel core. */
#endif /* !__x86_64__ */

#endif /* !_I386_KOS_KOS_KERNEL_ASM_PAGING_H */
