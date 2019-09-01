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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_NODEAPI_H
#define GUARD_KERNEL_SRC_MEMORY_VM_NODEAPI_H 1

#include <kernel/compiler.h>

#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/vm.h>

#ifndef VM_PAGE_UNUSED_BITS
#define VM_PAGE_UNUSED_BITS   PAGESHIFT
#endif /* !VM_PAGE_UNUSED_BITS */


/* Since KOSmk3 now uses page-based VM addressing, rather than byte-based,
 * that leads to the fact that our address tree doesn't make use of a
 * portion of the SEMI-address bits any more.
 * To be more precise: The most significant `VM_PAGE_UNUSED_BITS'
 *                     bits of any `vm_vpage_t' are always ZERO(0)
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
       * to take advantage of fixed-value bits in `vm_vpage_t' */
#undef VM_PAGE_UNUSED_BITS
#define VM_PAGE_UNUSED_BITS 0
#endif


#ifdef VM_ADDRBITS
#define VM_PAGE_BITS   (VM_ADDRBITS-VM_PAGE_UNUSED_BITS)
#elif __SIZEOF_POINTER__ == 4
#define VM_PAGE_BITS   (32-VM_PAGE_UNUSED_BITS)
#elif __SIZEOF_POINTER__ == 8
#define VM_PAGE_BITS   (64-VM_PAGE_UNUSED_BITS)
#else
#define VM_PAGE_BITS   ((__SIZEOF_POINTER__*8)-VM_PAGE_UNUSED_BITS)
#endif
#if VM_PAGE_UNUSED_BITS == 0
#define VM_SEMI0         ATREE_SEMI0(VIRT vm_vpage_t)
#define VM_LEVEL0        ATREE_LEVEL0(VIRT vm_vpage_t)
#else
#define VM_SEMI0         ATREE_SEMI0_BITS(VIRT vm_vpage_t,VM_PAGE_BITS)
#define VM_LEVEL0        ATREE_LEVEL0_BITS(VIRT vm_vpage_t,VM_PAGE_BITS)
#endif


/* Define the ABI for the address tree used by vm. */
#define ATREE(x)                 vm_nodetree_##x
#define ATREE_FUN                INTDEF
#define ATREE_CALL               KCALL
#define Tkey                     vm_vpage_t
#define T                        struct vm_node
#define N_NODEPATH               vn_node
#define ATREE_LOCAL_SEMI0(Tkey)  VM_SEMI0
#define ATREE_LOCAL_LEVEL0(Tkey) VM_LEVEL0
#define ATREE_HEADER_ONLY 1
#include <hybrid/sequence/atree-abi.h>
#undef ATREE_HEADER_ONLY


#define ATREE(x)                 vm_futextree_##x
#define ATREE_FUN                INTDEF
#define ATREE_CALL               KCALL
#define Tkey                     uintptr_t
#define T                        struct vm_futex
#define N_NODEPATH               f_tree
#define ATREE_HEADER_ONLY 1
#define ATREE_SINGLE 1
#include <hybrid/sequence/atree-abi.h>
#undef ATREE_SINGLE
#undef ATREE_HEADER_ONLY

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_NODEAPI_H */
