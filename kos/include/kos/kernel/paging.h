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
#ifndef _KOS_KERNEL_PAGING_H
#define _KOS_KERNEL_PAGING_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <asm/os/mman.h>


#undef KERNELSPACE_BASE
#undef KERNEL_CORE_BASE

#undef KERNELSPACE_END
#undef KERNELSPACE_LOWMEM
#define KERNELSPACE_HIGHMEM 1

#if __SIZEOF_POINTER__ >= 8
#define USERSPACE_END    __UINT64_C(0x0000800000000000) /* Upper address space limit for user-space (first invalid address) */
#define KERNELSPACE_BASE __UINT64_C(0xffff800000000000) /* Lower address space limit for kernel-space */
#define KERNEL_CORE_BASE __UINT64_C(0xffffffff80000000) /* Load address of the kernel core. (-2GB) */
#else /* __SIZEOF_POINTER__ >= 8 */
#define USERSPACE_END    __UINT32_C(0xc0000000) /* Upper address space limit for user-space */
#define KERNELSPACE_BASE __UINT32_C(0xc0000000) /* lower address space limit for kernel-space */
#define KERNEL_CORE_BASE __UINT32_C(0xc0000000) /* Load address of the kernel core. */
#endif /* __SIZEOF_POINTER__ < 8 */
#define ADDR_IS_NONCANON(addr) 0
#define ADDR_IS_CANON(addr)    1

/* MMan hints for where to map different, dynamic kernel/user-space components. */
#if __SIZEOF_POINTER__ >= 8
#define __KERNEL_MHINT(addr32, addr64, mode) (__CCAST(void *)__UINT64_C(addr64), mode)
#else /* __SIZEOF_POINTER__ >= 8 */
#define __KERNEL_MHINT(addr32, addr64, mode) (__CCAST(void *)__UINT32_C(addr32), mode)
#endif /* __SIZEOF_POINTER__ < 8 */

/* TODO: Adjust these hints to work better in a 64-bit address space */
#define KERNEL_MHINT_HEAP         __KERNEL_MHINT(0xe1000000, 0xffffffffe1000000, __MAP_GROWSUP)   /* Hint for the regular kernel heap. */
#define KERNEL_MHINT_LHEAP        __KERNEL_MHINT(0xe2000000, 0xffffffffe2000000, __MAP_GROWSUP)   /* Hint for the locked kernel heap. */
#define KERNEL_MHINT_MMAN         __KERNEL_MHINT(0xe8100000, 0xffffffffe8100000, __MAP_GROWSUP)   /* Hint for memory managers. */
#define KERNEL_MHINT_SLAB         __KERNEL_MHINT(0xe8000000, 0xffffffffe8000000, __MAP_GROWSDOWN) /* Hint for the slab allocator. */
#define KERNEL_MHINT_DHEAP        __KERNEL_MHINT(0xe0000000, 0xffffffffe0000000, __MAP_GROWSDOWN) /* Hint for the kernel heap used for allocating debug controllers. */
#define KERNEL_MHINT_COREPAGE     __KERNEL_MHINT(0xf0000000, 0xfffffffff0000000, __MAP_GROWSDOWN) /* Hint for core-base pointers. */
#define KERNEL_MHINT_PHYSINFO     __KERNEL_MHINT(0xf0000000, 0xfffffffff0000000, __MAP_GROWSDOWN) /* Hint for physical memory information/controller data. */
#define KERNEL_MHINT_LAPIC        __KERNEL_MHINT(0xf0000000, 0xfffffffff0000000, __MAP_GROWSDOWN) /* Hint for the LAPIC (if present). */
#define KERNEL_MHINT_TRAMPOLINE   __KERNEL_MHINT(0xeffe0000, 0xffffffffeffe0000, __MAP_GROWSDOWN) /* Hint for per-task trampoline pages. */
#define KERNEL_MHINT_KERNSTACK    __KERNEL_MHINT(0xeb000000, 0xffffffffeb000000, __MAP_GROWSDOWN) /* Hint for kernel stacks. */
#define KERNEL_MHINT_ALTCORE      __KERNEL_MHINT(0xeeeee000, 0xffffffffeeeee000, __MAP_GROWSUP)   /* Hint for secondary CPU control structures. */
#define KERNEL_MHINT_IDLESTACK    __KERNEL_MHINT(0xf0000000, 0xfffffffff0000000, __MAP_GROWSDOWN) /* Hint for per-cpu IDLE stacks. */
#define KERNEL_MHINT_DFSTACK      __KERNEL_MHINT(0xf0000000, 0xfffffffff0000000, __MAP_GROWSDOWN) /* Hint for per-cpu #DF stacks. */
#define KERNEL_MHINT_DRIVER       __KERNEL_MHINT(0xd0000000, 0xffffffffd0000000, __MAP_GROWSUP)   /* Hint for the custom kernel-space drivers. */
#define KERNEL_MHINT_DEVICE       __KERNEL_MHINT(0xf0000000, 0xfffffffff0000000, __MAP_GROWSDOWN) /* Hint for device memory mappings. */
#define KERNEL_MHINT_TEMPORARY    __KERNEL_MHINT(0xf0000000, 0xfffffffff0000000, __MAP_GROWSUP)   /* Hint for temporary memory mappings. */
#define KERNEL_MHINT_USER_MINADDR __KERNEL_MHINT(0x00010000, 0x0000000000010000, 0)               /* Default value for `mman_getunmapped_user_minaddr'. */
#define KERNEL_MHINT_USER_HEAP    __KERNEL_MHINT(0x10000000, 0x0000000010000000, __MAP_GROWSUP)   /* Hint for user-space heap memory. */
#define KERNEL_MHINT_USER_STACK   __KERNEL_MHINT(0x80000000, 0x0000000080000000, __MAP_GROWSDOWN) /* Hint for user-space stack memory. */
#define KERNEL_MHINT_USER_LIBRARY __KERNEL_MHINT(0x0e000000, 0x000000000e000000, __MAP_GROWSDOWN) /* Hint for user-space dynamic libraries. */
#define KERNEL_MHINT_USER_DYNLINK __KERNEL_MHINT(0xbf100000, 0x00000000bf100000, __MAP_GROWSUP)   /* Hint for user-space dynamic linkers. */
#define KERNEL_MHINT_USER_PEB     __KERNEL_MHINT(0xc0000000, 0x00000000c0000000, __MAP_GROWSDOWN) /* Hint for user-space process environment blocks. */


#ifndef KERNEL_STACKSIZE
#if __SIZEOF_POINTER__ >= 8
#define KERNEL_STACKSIZE      49152    /* 4096*12 */
#else /* __SIZEOF_POINTER__ >= 8 */
#define KERNEL_STACKSIZE      32768    /* 4096*8 */
#endif /* __SIZEOF_POINTER__ < 8 */
#endif /* !KERNEL_STACKSIZE */
#ifndef KERNEL_DF_STACKSIZE
#if __SIZEOF_POINTER__ >= 8
#define KERNEL_DF_STACKSIZE   12288    /* 4096*3 */
#else /* __SIZEOF_POINTER__ >= 8 */
#define KERNEL_DF_STACKSIZE   8192     /* 4096*2 */
#endif /* __SIZEOF_POINTER__ < 8 */
#endif /* !KERNEL_DF_STACKSIZE */
#ifndef KERNEL_IDLE_STACKSIZE
#if __SIZEOF_POINTER__ >= 8
#define KERNEL_IDLE_STACKSIZE 24576    /* 4096*6 */
#else /* __SIZEOF_POINTER__ >= 8 */
#define KERNEL_IDLE_STACKSIZE 16384    /* 4096*4 */
#endif /* __SIZEOF_POINTER__ < 8 */
#endif /* !KERNEL_IDLE_STACKSIZE */
#ifndef KERNEL_DEBUG_STACKSIZE
#define KERNEL_DEBUG_STACKSIZE (KERNEL_STACKSIZE * 2)
#endif /* !KERNEL_DEBUG_STACKSIZE */

#endif /* !_KOS_KERNEL_PAGING_H */
