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
#ifndef _I386_KOS_KOS_KERNEL_PAGING_H
#define _I386_KOS_KOS_KERNEL_PAGING_H 1

#include <__stdinc.h>
#include <kos/bits/types.h>
#include <hybrid/typecore.h>


#undef KERNEL_BASE
#undef KERNEL_CORE_BASE
#undef KERNEL_BASE_PAGE
#undef KERNEL_NUM_PAGES

#undef LOW_MEMORY_KERNEL
#define HIGH_MEMORY_KERNEL 1

#ifdef __x86_64__
#define USERSPACE_END           __UINT64_C(0x0001000000000000) /* lower address space limit for kernel-space */
#define USERSPACE_END_I                    0x0001000000000000  /* lower address space limit for kernel-space */
#define KERNEL_BASE             __UINT64_C(0xffff800000000000) /* lower address space limit for kernel-space */
#define KERNEL_BASE_I                      0xffff800000000000  /* lower address space limit for kernel-space */
#define KERNEL_CORE_BASE        __UINT64_C(0xffffffff80000000) /* Load address of the kernel core. (-2GB) */
#define KERNEL_CORE_BASE_I                 0xffffffff80000000  /* Load address of the kernel core. (-2GB) */
#define KERNEL_BASE_PAGE        __UINT64_C(0xffff800000000)    /* Page index for the user/kernel address space split. */
#define KERNEL_BASE_PAGE_I                 0xffff800000000     /* Page index for the user/kernel address space split. */
#define KERNEL_CORE_PAGE        __UINT64_C(0xffffffff80000)    /* The page index of the kernel-base */
#define KERNEL_CORE_PAGE_I                 0xffffffff80000     /* The page index of the kernel-base */
#define KERNEL_NUM_PAGES        __UINT64_C(0x0000800000000)    /* The number of pages associated with the kernel. */
#define KERNEL_NUM_PAGES_I                 0x0000800000000     /* The number of pages associated with the kernel. */
#define KERNEL_NUM_CORE_PAGES   __UINT64_C(0x0000000080000)    /* The number of pages associated with the kernel. */
#define KERNEL_NUM_CORE_PAGES_I            0x0000000080000     /* The number of pages associated with the kernel. */


/* NOTE: All non-canonical bits must be equal to the most significant canonical bit.
 *       In other words: Memory addresses behave as signed with the bits 48-63 being
 *       a sign-extension of bit 47 */
#define X86_64_ADDRBUS_CANONBITS        48
#define X86_64_ADDRBUS_CANONMASK        __UINT64_C(0x0000ffffffffffff)
#define X86_64_ADDRBUS_NONCANONBITS     16
#define X86_64_ADDRBUS_NONCANONMASK     __UINT64_C(0xffff000000000000)

#define X86_64_ADDRBUS_NONCANON_MIN     __UINT64_C(0x0001000000000000)
#define X86_64_ADDRBUS_NONCANON_MAX     __UINT64_C(0xffff7fffffffffff)
#define ADDR_IS_NONCANON(addr)  ((addr) >= X86_64_ADDRBUS_NONCANON_MIN && (addr) <= X86_64_ADDRBUS_NONCANON_MAX)
#define ADDR_IS_CANON(addr)     (!ADDR_IS_NONCANON(addr))

#else /* __x86_64__ */
#define USERSPACE_END         __UINT32_C(0xc0000000)         /* Upper address space limit for user-space */
#define KERNEL_BASE           __UINT32_C(0xc0000000)         /* lower address space limit for kernel-space */
#define KERNEL_CORE_BASE      __UINT32_C(0xc0000000)         /* Load address of the kernel core. */
#define KERNEL_BASE_PAGE      __UINT32_C(0xc0000)            /* Page index for the user/kernel address space split. */
#define KERNEL_CORE_PAGE      __UINT32_C(0xc0000)            /* The page index of the kernel-base */
#define KERNEL_NUM_PAGES      __UINT32_C(0x40000)            /* The number of pages associated with the kernel. */
#define KERNEL_NUM_CORE_PAGES __UINT32_C(0x40000)            /* The number of pages associated with the kernel. */
#define ADDR_IS_NONCANON(addr)  0
#define ADDR_IS_CANON(addr)     1
#endif /* !__x86_64__ */

#define ADDR_IS_KERNEL(ptr)            ((__UINTPTR_TYPE__)(ptr) >= KERNEL_BASE)
#define PAGE_IS_KERNEL(ptr)            ((__UINTPTR_TYPE__)(ptr) >= KERNEL_BASE_PAGE)
#define ADDR_IS_USER(ptr)              ((__UINTPTR_TYPE__)(ptr) < KERNEL_BASE)
#define PAGE_IS_USER(ptr)              ((__UINTPTR_TYPE__)(ptr) < KERNEL_BASE_PAGE)
#define ARANGE_IS_KERNEL(start, end)   ((__UINTPTR_TYPE__)(start) >= KERNEL_BASE)
#define PRANGE_IS_KERNEL(start, end)   ((__UINTPTR_TYPE__)(start) >= KERNEL_BASE_PAGE)
#define ARANGE_IS_USER(start, end)     ((__UINTPTR_TYPE__)(end) <= KERNEL_BASE)
#define PRANGE_IS_USER(start, end)     ((__UINTPTR_TYPE__)(end) <= KERNEL_BASE_PAGE)
#define ARANGE_IS_KERNEL_PARTIAL(start, end)   ((__UINTPTR_TYPE__)(end) > KERNEL_BASE)
#define PRANGE_IS_KERNEL_PARTIAL(start, end)   ((__UINTPTR_TYPE__)(end) > KERNEL_BASE_PAGE)
#define ARANGE_IS_USER_PARTIAL(start, end)     ((__UINTPTR_TYPE__)(start) < KERNEL_BASE)
#define PRANGE_IS_USER_PARTIAL(start, end)     ((__UINTPTR_TYPE__)(start) < KERNEL_BASE_PAGE)


/* VM hints for where to map different, dynamic kernel components. */
#define KERNEL_VMHINT_HEAP         (0xe1200, VM_GETFREE_ABOVE) /* Hint for the regular kernel heap. */
#define KERNEL_VMHINT_LHEAP        (0xe1a00, VM_GETFREE_ABOVE) /* Hint for the locked kernel heap. */
#define KERNEL_VMHINT_SLAB         (0xe8000, VM_GETFREE_BELOW) /* Hint for the slab allocator. */
#define KERNEL_VMHINT_DHEAP        (0xe0000, VM_GETFREE_BELOW) /* Hint for the kernel heap used for allocating debug controllers. */
#define KERNEL_VMHINT_COREPAGE     (0xf0000, VM_GETFREE_BELOW) /* Hint for core-base pointers. */
#define KERNEL_VMHINT_PHYSINFO     (0xf0000, VM_GETFREE_BELOW) /* Hint for physical memory information/controller data. */
#define KERNEL_VMHINT_LAPIC        (0xf0000, VM_GETFREE_BELOW) /* Hint for the LAPIC (if present). */
#define KERNEL_VMHINT_TRAMPOLINE   (0xeffe0, VM_GETFREE_BELOW) /* Hint for per-task trampoline pages. */
#define KERNEL_VMHINT_KERNSTACK    (0xeb000, VM_GETFREE_BELOW) /* Hint for kernel stacks. */
#define KERNEL_VMHINT_IDLESTACK    (0xf0000, VM_GETFREE_BELOW) /* Hint for per-cpu IDLE stacks. */
#define KERNEL_VMHINT_DFSTACK      (0xf0000, VM_GETFREE_BELOW) /* Hint for per-cpu #DF stacks. */
#define KERNEL_VMHINT_DRIVER       (0xd0000, VM_GETFREE_ABOVE) /* Hint for the custom kernel-space drivers. */
#define KERNEL_VMHINT_DEVICE       (0xf0000, VM_GETFREE_BELOW) /* Hint for device memory mappings. */
#define KERNEL_VMHINT_TEMPORARY    (0xf0000, VM_GETFREE_ABOVE) /* Hint for temporary memory mappings. */
#define KERNEL_VMHINT_USER_HEAP    (0x10000, VM_GETFREE_ABOVE | VM_GETFREE_ASLR) /* Hint for user-space heap memory. */
#define KERNEL_VMHINT_USER_STACK   (0x80000, VM_GETFREE_BELOW | VM_GETFREE_ASLR) /* Hint for user-space stack memory. */
#define KERNEL_VMHINT_USER_LIBRARY (0x0e000, VM_GETFREE_BELOW | VM_GETFREE_ASLR) /* Hint for user-space dynamic libraries. */
#define KERNEL_VMHINT_USER_DYNLINK (0xbf100, VM_GETFREE_ASLR)  /* Hint for user-space dynamic linkers. */
#define KERNEL_VMHINT_USER_PEB     (0xc0000, VM_GETFREE_BELOW | VM_GETFREE_ASLR) /* Hint for user-space process environment blocks. */



#ifndef KERNEL_STACKSIZE
#ifdef __x86_64__
#define KERNEL_STACKSIZE      49152    /* 4096*12 */
#else
#define KERNEL_STACKSIZE      32768    /* 4096*8 */
#endif
#endif
#ifndef KERNEL_DF_STACKSIZE
#ifdef __x86_64__
#define KERNEL_DF_STACKSIZE   12288    /* 4096*3 */
#else
#define KERNEL_DF_STACKSIZE   8192     /* 4096*2 */
#endif
#endif
#ifndef KERNEL_IDLE_STACKSIZE
#ifdef __x86_64__
#define KERNEL_IDLE_STACKSIZE 8192     /* 4096*2 */
#else
#define KERNEL_IDLE_STACKSIZE 4096     /* 4096 */
#endif
#endif
#ifndef KERNEL_DEBUG_STACKSIZE
#define KERNEL_DEBUG_STACKSIZE (KERNEL_STACKSIZE * 4)
#endif

#ifndef VM_VPAGE_MAX
#define VM_VPAGE_MAX       __VM_VPAGE_MAX
#define VM_PPAGE_MAX       __VM_PPAGE_MAX
#endif /* !VM_VPAGE_MAX */
#ifndef VM_PPAGE2ADDR
#define VM_PPAGE2ADDR(page) __VM_PPAGE2ADDR(page)
#endif /* !VM_PPAGE2ADDR */
#ifndef VM_PAGE2ADDR
#define VM_PAGE2ADDR(page) __VM_PAGE2ADDR(page)
#define VM_ADDR2PAGE(addr) __VM_ADDR2PAGE(addr)
#endif /* !VM_PAGE2ADDR */

#endif /* !_I386_KOS_KOS_KERNEL_PAGING_H */
