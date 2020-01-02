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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_KOS_KERNEL_PAGING_H
#define _I386_KOS_KOS_KERNEL_PAGING_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <kos/bits/types.h>


#undef KERNELSPACE_BASE
#undef KERNEL_CORE_BASE

#undef KERNELSPACE_END
#undef KERNELSPACE_LOWMEM
#define KERNELSPACE_HIGHMEM 1

#ifdef __x86_64__
#define USERSPACE_END    __UINT64_C(0x0000800000000000) /* Upper address space limit for user-space (first invalid address) */
#define KERNELSPACE_BASE __UINT64_C(0xffff800000000000) /* Lower address space limit for kernel-space */
#define KERNEL_CORE_BASE __UINT64_C(0xffffffff80000000) /* Load address of the kernel core. (-2GB) */

/* Check if a given physical address range is identity mapped. */
#if 0 /* TODO: Add a configuration option for this.
       * TODO: Must test the x86_64 kernel (once its working) with _and_ without the phyiscal identity mapping! */

/* First first half of the kernel address space is used as identity mapping
 * for the first 64TiB (yes: that is Terrabyte) of physical memory. */
#define KERNEL_PHYS2VIRT_BASE __UINT64_C(0xffff880000000000) /* Start of the physical identity mapping */
#define KERNEL_PHYS2VIRT_SIZE     __UINT64_C(0x400000000000) /* Size of the physical identity mapping (== 64TiB) */
#define KERNEL_PHYS2VIRT_MIN  KERNEL_PHYS2VIRT_BASE          /* Lowest address apart of the physical identity mapping */
#define KERNEL_PHYS2VIRT_MAX  __UINT64_C(0xffffc7ffffffffff) /* Greatest address apart of the physical identity mapping */

/* Accessor macros for physical identity translation. */
#define PHYS_IS_IDENTITY(base, num_bytes) (((__u64)(base) + (__u64)(num_bytes)) <= KERNEL_PHYS2VIRT_SIZE)
#define PHYS_TO_IDENTITY(base)            ((void *)((__u64)(base) + KERNEL_PHYS2VIRT_BASE))
#define PHYS_IS_IDENTITY_PAGE(pageno)     ((__u64)(pageno) <= KERNEL_PHYS2VIRT_PAGECOUNT)
#define PHYS_TO_IDENTITY_PAGE(pageno)     ((void *)(((__u64)(pageno) * 4096) + KERNEL_PHYS2VIRT_BASE))
#endif

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
#define USERSPACE_END         __UINT32_C(0xc0000000)         /* Upper address space limit for user-space */
#define KERNELSPACE_BASE           __UINT32_C(0xc0000000)         /* lower address space limit for kernel-space */
#define KERNEL_CORE_BASE      __UINT32_C(0xc0000000)         /* Load address of the kernel core. */
#define ADDR_IS_NONCANON(addr)  0
#define ADDR_IS_CANON(addr)     1
#endif /* !__x86_64__ */

/* VM hints for where to map different, dynamic kernel components. */
#ifdef __x86_64__
#define __KERNEL_VMHINT(addr32, addr64, mode) (__CCAST(void *)__UINT64_C(addr64), mode)
#else /* __x86_64__ */
#define __KERNEL_VMHINT(addr32, addr64, mode) (__CCAST(void *)__UINT32_C(addr32), mode)
#endif /* !__x86_64__ */
/* TODO: Adjust these hints to work better in a 64-bit address space */
#define KERNEL_VMHINT_HEAP         __KERNEL_VMHINT(0xe1200000, 0xffffffffe1200000, VM_GETFREE_ABOVE) /* Hint for the regular kernel heap. */
#define KERNEL_VMHINT_LHEAP        __KERNEL_VMHINT(0xe1a00000, 0xffffffffe1a00000, VM_GETFREE_ABOVE) /* Hint for the locked kernel heap. */
#define KERNEL_VMHINT_SLAB         __KERNEL_VMHINT(0xe8000000, 0xffffffffe8000000, VM_GETFREE_BELOW) /* Hint for the slab allocator. */
#define KERNEL_VMHINT_DHEAP        __KERNEL_VMHINT(0xe0000000, 0xffffffffe0000000, VM_GETFREE_BELOW) /* Hint for the kernel heap used for allocating debug controllers. */
#define KERNEL_VMHINT_COREPAGE     __KERNEL_VMHINT(0xf0000000, 0xfffffffff0000000, VM_GETFREE_BELOW) /* Hint for core-base pointers. */
#define KERNEL_VMHINT_PHYSINFO     __KERNEL_VMHINT(0xf0000000, 0xfffffffff0000000, VM_GETFREE_BELOW) /* Hint for physical memory information/controller data. */
#define KERNEL_VMHINT_LAPIC        __KERNEL_VMHINT(0xf0000000, 0xfffffffff0000000, VM_GETFREE_BELOW) /* Hint for the LAPIC (if present). */
#define KERNEL_VMHINT_TRAMPOLINE   __KERNEL_VMHINT(0xeffe0000, 0xffffffffeffe0000, VM_GETFREE_BELOW) /* Hint for per-task trampoline pages. */
#define KERNEL_VMHINT_KERNSTACK    __KERNEL_VMHINT(0xeb000000, 0xffffffffeb000000, VM_GETFREE_BELOW) /* Hint for kernel stacks. */
#define KERNEL_VMHINT_ALTCORE      __KERNEL_VMHINT(0xeeeee000, 0xffffffffeeeee000, VM_GETFREE_ABOVE) /* Hint for secondary CPU control structures. */
#define KERNEL_VMHINT_IDLESTACK    __KERNEL_VMHINT(0xf0000000, 0xfffffffff0000000, VM_GETFREE_BELOW) /* Hint for per-cpu IDLE stacks. */
#define KERNEL_VMHINT_DFSTACK      __KERNEL_VMHINT(0xf0000000, 0xfffffffff0000000, VM_GETFREE_BELOW) /* Hint for per-cpu #DF stacks. */
#define KERNEL_VMHINT_DRIVER       __KERNEL_VMHINT(0xd0000000, 0xffffffffd0000000, VM_GETFREE_ABOVE) /* Hint for the custom kernel-space drivers. */
#define KERNEL_VMHINT_DEVICE       __KERNEL_VMHINT(0xf0000000, 0xfffffffff0000000, VM_GETFREE_BELOW) /* Hint for device memory mappings. */
#define KERNEL_VMHINT_TEMPORARY    __KERNEL_VMHINT(0xf0000000, 0xfffffffff0000000, VM_GETFREE_ABOVE) /* Hint for temporary memory mappings. */
#define KERNEL_VMHINT_USER_HEAP    __KERNEL_VMHINT(0x10000000, 0x0000000010000000, VM_GETFREE_ABOVE | VM_GETFREE_ASLR) /* Hint for user-space heap memory. */
#define KERNEL_VMHINT_USER_STACK   __KERNEL_VMHINT(0x80000000, 0x0000000080000000, VM_GETFREE_BELOW | VM_GETFREE_ASLR) /* Hint for user-space stack memory. */
#define KERNEL_VMHINT_USER_LIBRARY __KERNEL_VMHINT(0x0e000000, 0x000000000e000000, VM_GETFREE_BELOW | VM_GETFREE_ASLR) /* Hint for user-space dynamic libraries. */
#define KERNEL_VMHINT_USER_DYNLINK __KERNEL_VMHINT(0xbf100000, 0x00000000bf100000, VM_GETFREE_ABOVE | VM_GETFREE_ASLR) /* Hint for user-space dynamic linkers. */
#define KERNEL_VMHINT_USER_PEB     __KERNEL_VMHINT(0xc0000000, 0x00000000c0000000, VM_GETFREE_BELOW | VM_GETFREE_ASLR) /* Hint for user-space process environment blocks. */



#ifndef KERNEL_STACKSIZE
#ifdef __x86_64__
#define KERNEL_STACKSIZE      49152    /* 4096*12 */
#else /* __x86_64__ */
#define KERNEL_STACKSIZE      32768    /* 4096*8 */
#endif /* !__x86_64__ */
#endif /* !KERNEL_STACKSIZE */
#ifndef KERNEL_DF_STACKSIZE
#ifdef __x86_64__
#define KERNEL_DF_STACKSIZE   12288    /* 4096*3 */
#else /* __x86_64__ */
#define KERNEL_DF_STACKSIZE   8192     /* 4096*2 */
#endif /* !__x86_64__ */
#endif /* !KERNEL_DF_STACKSIZE */
#ifndef KERNEL_IDLE_STACKSIZE
#ifdef __x86_64__
#define KERNEL_IDLE_STACKSIZE 8192     /* 4096*2 */
#else /* __x86_64__ */
#define KERNEL_IDLE_STACKSIZE 4096     /* 4096 */
#endif /* !__x86_64__ */
#endif /* !KERNEL_IDLE_STACKSIZE */
#ifndef KERNEL_DEBUG_STACKSIZE
#define KERNEL_DEBUG_STACKSIZE (KERNEL_STACKSIZE * 4)
#endif /* !KERNEL_DEBUG_STACKSIZE */

#endif /* !_I386_KOS_KOS_KERNEL_PAGING_H */
