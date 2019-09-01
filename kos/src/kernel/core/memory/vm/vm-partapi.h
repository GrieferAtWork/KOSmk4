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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_PARTAPI_H
#define GUARD_KERNEL_SRC_MEMORY_VM_PARTAPI_H 1

#include <kernel/compiler.h>

#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/vm.h>

#ifndef VM_PAGE_UNUSED_BITS
#if PAGESIZE == 0x800000
#define VM_PAGE_UNUSED_BITS   23
#elif PAGESIZE == 0x400000
#define VM_PAGE_UNUSED_BITS   22
#elif PAGESIZE == 0x200000
#define VM_PAGE_UNUSED_BITS   21
#elif PAGESIZE == 0x100000
#define VM_PAGE_UNUSED_BITS   20
#elif PAGESIZE == 0x80000
#define VM_PAGE_UNUSED_BITS   19
#elif PAGESIZE == 0x40000
#define VM_PAGE_UNUSED_BITS   18
#elif PAGESIZE == 0x20000
#define VM_PAGE_UNUSED_BITS   17
#elif PAGESIZE == 0x10000
#define VM_PAGE_UNUSED_BITS   16
#elif PAGESIZE == 0x8000
#define VM_PAGE_UNUSED_BITS   15
#elif PAGESIZE == 0x4000
#define VM_PAGE_UNUSED_BITS   14
#elif PAGESIZE == 0x2000
#define VM_PAGE_UNUSED_BITS   13
#elif PAGESIZE == 0x1000
#define VM_PAGE_UNUSED_BITS   12
#elif PAGESIZE == 0x800
#define VM_PAGE_UNUSED_BITS   11
#elif PAGESIZE == 0x400
#define VM_PAGE_UNUSED_BITS   10
#elif PAGESIZE == 0x200
#define VM_PAGE_UNUSED_BITS    9
#elif PAGESIZE == 0x100
#define VM_PAGE_UNUSED_BITS    8
#elif PAGESIZE == 0x80
#define VM_PAGE_UNUSED_BITS    7
#elif PAGESIZE == 0x40
#define VM_PAGE_UNUSED_BITS    6
#elif PAGESIZE == 0x20
#define VM_PAGE_UNUSED_BITS    5
#elif PAGESIZE == 0x10
#define VM_PAGE_UNUSED_BITS    4
#elif PAGESIZE == 0x8
#define VM_PAGE_UNUSED_BITS    3
#elif PAGESIZE == 0x4
#define VM_PAGE_UNUSED_BITS    2
#elif PAGESIZE == 0x2
#define VM_PAGE_UNUSED_BITS    1
#else
#define VM_PAGE_UNUSED_BITS    0
#endif
#endif /* !VM_PAGE_UNUSED_BITS */


/* Since KOSmk3 now uses page-based VM addressing, rather than byte-based,
 * that leads to the fact that our address tree doesn't make use of a
 * portion of the SEMI-address bits any more.
 * To be more precise: The most significant `VM_PAGE_UNUSED_BITS'
 *                     bits of any `vm_dpage_t' are always ZERO(0)
 * The address tree can still operate in this situation, however because
 * it operates by using the bits of an address (starting at the most
 * significant position) to generate a binary tree, the that would
 * also leave the first `VM_PAGE_UNUSED_BITS' branches to not actually
 * be branches at all, but always point to the left.
 * For that reason, we tell it to only start counting at level
 * `(sizeof(void *)*8) - VM_PAGE_UNUSED_BITS', skipping the first
 * couple of bits, once again resulting in what you would call a tree.
 * HINT: To disable this optimization, replace the following line with `#if 1' */
#if 0 /* Keep set at `0' to optimize the address tree search algorithm
       * to take advantage of fixed-value bits in `vm_dpage_t' */
#undef VM_PAGE_UNUSED_BITS
#define VM_PAGE_UNUSED_BITS 0
#endif


#ifdef VM_PARTADDRBITS
#define VM_PARTPAGE_BITS   (VM_PARTADDRBITS-VM_PAGE_UNUSED_BITS)
#elif __SIZEOF_VM_DADDR_T__ == 4
#define VM_PARTPAGE_BITS   (32-VM_PAGE_UNUSED_BITS)
#elif __SIZEOF_VM_DADDR_T__ == 8
#define VM_PARTPAGE_BITS   (64-VM_PAGE_UNUSED_BITS)
#else
#define VM_PARTPAGE_BITS   ((__SIZEOF_VM_DADDR_T__*8)-VM_PAGE_UNUSED_BITS)
#endif
#if VM_PAGE_UNUSED_BITS == 0
#define VM_DATAPART_SEMI0         ATREE_SEMI0(VIRT vm_dpage_t)
#define VM_DATAPART_LEVEL0        ATREE_LEVEL0(VIRT vm_dpage_t)
#else
#define VM_DATAPART_SEMI0         ATREE_SEMI0_BITS(VIRT vm_dpage_t,VM_PARTPAGE_BITS)
#define VM_DATAPART_LEVEL0        ATREE_LEVEL0_BITS(VIRT vm_dpage_t,VM_PARTPAGE_BITS)
#endif


/* Define the ABI for the address tree used by vm. */
#define ATREE(x)                 vm_datapart_tree_##x
#define ATREE_FUN                INTDEF
#define ATREE_CALL               KCALL
#define Tkey                     vm_dpage_t
#define T                        struct vm_datapart
#define N_NODEPATH               dp_tree
#define ATREE_LOCAL_SEMI0(Tkey)  VM_DATAPART_SEMI0
#define ATREE_LOCAL_LEVEL0(Tkey) VM_DATAPART_LEVEL0
#define ATREE_HEADER_ONLY 1
#include <hybrid/sequence/atree-abi.h>
#undef ATREE_HEADER_ONLY


#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_PARTAPI_H */
