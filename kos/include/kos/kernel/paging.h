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
#ifndef _KOS_KERNEL_PAGING_H
#define _KOS_KERNEL_PAGING_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <asm/os/mman.h>
#include <kos/kernel/asm/paging.h>

#ifndef ADDR_IS_NONCANON
#define ADDR_IS_NONCANON(addr) 0
#define ADDR_IS_CANON(addr)    1
#endif /* !ADDR_IS_NONCANON */

/* MMan hints for where to map different, dynamic kernel/user-space components. */
#if __SIZEOF_POINTER__ >= 8
#define __KERNEL_MHINT(addr32, addr64, mode) (__CCAST(void *)__UINT64_C(addr64), mode)
#else /* __SIZEOF_POINTER__ >= 8 */
#define __KERNEL_MHINT(addr32, addr64, mode) (__CCAST(void *)__UINT32_C(addr32), mode)
#endif /* __SIZEOF_POINTER__ < 8 */

/* TODO: Adjust these hints to work better in a 64-bit address space */
#ifndef KERNEL_MHINT_HEAP
#define KERNEL_MHINT_HEAP         __KERNEL_MHINT(0xe1000000, 0xffffffffe1000000, __MAP_GROWSUP)   /* Hint for the regular kernel heap. */
#endif /* !KERNEL_MHINT_HEAP */
#ifndef KERNEL_MHINT_LHEAP
#define KERNEL_MHINT_LHEAP        __KERNEL_MHINT(0xe2000000, 0xffffffffe2000000, __MAP_GROWSUP)   /* Hint for the locked kernel heap. */
#endif /* !KERNEL_MHINT_LHEAP */
#ifndef KERNEL_MHINT_MMAN
#define KERNEL_MHINT_MMAN         __KERNEL_MHINT(0xe8100000, 0xffffffffe8100000, __MAP_GROWSUP)   /* Hint for memory managers. */
#endif /* !KERNEL_MHINT_MMAN */
#ifndef KERNEL_MHINT_SLAB
#define KERNEL_MHINT_SLAB         __KERNEL_MHINT(0xe8000000, 0xffffffffe8000000, __MAP_GROWSDOWN) /* Hint for the slab allocator. */
#endif /* !KERNEL_MHINT_SLAB */
#ifndef KERNEL_MHINT_DHEAP
#define KERNEL_MHINT_DHEAP        __KERNEL_MHINT(0xe0000000, 0xffffffffe0000000, __MAP_GROWSDOWN) /* Hint for the kernel heap used for allocating debug controllers. */
#endif /* !KERNEL_MHINT_DHEAP */
#ifndef KERNEL_MHINT_COREPAGE
#define KERNEL_MHINT_COREPAGE     __KERNEL_MHINT(0xf0000000, 0xfffffffff0000000, __MAP_GROWSDOWN) /* Hint for core-base pointers. */
#endif /* !KERNEL_MHINT_COREPAGE */
#ifndef KERNEL_MHINT_PHYSINFO
#define KERNEL_MHINT_PHYSINFO     __KERNEL_MHINT(0xf0000000, 0xfffffffff0000000, __MAP_GROWSDOWN) /* Hint for physical memory information/controller data. */
#endif /* !KERNEL_MHINT_PHYSINFO */
#ifndef KERNEL_MHINT_LAPIC
#define KERNEL_MHINT_LAPIC        __KERNEL_MHINT(0xf0000000, 0xfffffffff0000000, __MAP_GROWSDOWN) /* Hint for the LAPIC (if present). */
#endif /* !KERNEL_MHINT_LAPIC */
#ifndef KERNEL_MHINT_TRAMPOLINE
#define KERNEL_MHINT_TRAMPOLINE   __KERNEL_MHINT(0xeffe0000, 0xffffffffeffe0000, __MAP_GROWSDOWN) /* Hint for per-task trampoline pages. */
#endif /* !KERNEL_MHINT_TRAMPOLINE */
#ifndef KERNEL_MHINT_KERNSTACK
#define KERNEL_MHINT_KERNSTACK    __KERNEL_MHINT(0xeb000000, 0xffffffffeb000000, __MAP_GROWSDOWN) /* Hint for kernel stacks. */
#endif /* !KERNEL_MHINT_KERNSTACK */
#ifndef KERNEL_MHINT_ALTCORE
#define KERNEL_MHINT_ALTCORE      __KERNEL_MHINT(0xeeeee000, 0xffffffffeeeee000, __MAP_GROWSUP)   /* Hint for secondary CPU control structures. */
#endif /* !KERNEL_MHINT_ALTCORE */
#ifndef KERNEL_MHINT_IDLESTACK
#define KERNEL_MHINT_IDLESTACK    __KERNEL_MHINT(0xf0000000, 0xfffffffff0000000, __MAP_GROWSDOWN) /* Hint for per-cpu IDLE stacks. */
#endif /* !KERNEL_MHINT_IDLESTACK */
#ifndef KERNEL_MHINT_DFSTACK
#define KERNEL_MHINT_DFSTACK      __KERNEL_MHINT(0xf0000000, 0xfffffffff0000000, __MAP_GROWSDOWN) /* Hint for per-cpu #DF stacks. */
#endif /* !KERNEL_MHINT_DFSTACK */
#ifndef KERNEL_MHINT_DRIVER
#define KERNEL_MHINT_DRIVER       __KERNEL_MHINT(0xd0000000, 0xffffffffd0000000, __MAP_GROWSUP)   /* Hint for the custom kernel-space drivers. */
#endif /* !KERNEL_MHINT_DRIVER */
#ifndef KERNEL_MHINT_DEVICE
#define KERNEL_MHINT_DEVICE       __KERNEL_MHINT(0xf0000000, 0xfffffffff0000000, __MAP_GROWSDOWN) /* Hint for device memory mappings. */
#endif /* !KERNEL_MHINT_DEVICE */
#ifndef KERNEL_MHINT_TEMPORARY
#define KERNEL_MHINT_TEMPORARY    __KERNEL_MHINT(0xf0000000, 0xfffffffff0000000, __MAP_GROWSUP)   /* Hint for temporary memory mappings. */
#endif /* !KERNEL_MHINT_TEMPORARY */
#ifndef KERNEL_MHINT_USER_MINADDR
#define KERNEL_MHINT_USER_MINADDR __KERNEL_MHINT(0x00010000, 0x0000000000010000, 0)               /* Default value for `mman_getunmapped_user_minaddr'. */
#endif /* !KERNEL_MHINT_USER_MINADDR */
#ifndef KERNEL_MHINT_USER_HEAP
#define KERNEL_MHINT_USER_HEAP    __KERNEL_MHINT(0x10000000, 0x0000000010000000, __MAP_GROWSUP)   /* Hint for user-space heap memory. */
#endif /* !KERNEL_MHINT_USER_HEAP */
#ifndef KERNEL_MHINT_USER_STACK
#define KERNEL_MHINT_USER_STACK   __KERNEL_MHINT(0x80000000, 0x0000000080000000, __MAP_GROWSDOWN) /* Hint for user-space stack memory. */
#endif /* !KERNEL_MHINT_USER_STACK */
#ifndef KERNEL_MHINT_USER_LIBRARY
#define KERNEL_MHINT_USER_LIBRARY __KERNEL_MHINT(0x0e000000, 0x000000000e000000, __MAP_GROWSDOWN) /* Hint for user-space dynamic libraries. */
#endif /* !KERNEL_MHINT_USER_LIBRARY */
#ifndef KERNEL_MHINT_USER_DYNLINK
#define KERNEL_MHINT_USER_DYNLINK __KERNEL_MHINT(0xbf100000, 0x00000000bf100000, __MAP_GROWSUP)   /* Hint for user-space dynamic linkers. */
#endif /* !KERNEL_MHINT_USER_DYNLINK */
#ifndef KERNEL_MHINT_USER_PEB
#define KERNEL_MHINT_USER_PEB     __KERNEL_MHINT(0xc0000000, 0x00000000c0000000, __MAP_GROWSDOWN) /* Hint for user-space process environment blocks. */
#endif /* !KERNEL_MHINT_USER_PEB */


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
