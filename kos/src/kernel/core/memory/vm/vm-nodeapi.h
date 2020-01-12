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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_NODEAPI_H
#define GUARD_KERNEL_SRC_MEMORY_VM_NODEAPI_H 1

#include <kernel/compiler.h>

#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/vm.h>
#include <kernel/vm/futex.h>

#include <asm/pageid.h>

#define VM_SEMI0  ATREE_SEMI0_BITS(VIRT pageid_t, __ARCH_PAGEID_BITS)
#define VM_LEVEL0 ATREE_LEVEL0_BITS(VIRT pageid_t, __ARCH_PAGEID_BITS)

/* Define the ABI for the address tree used by vm. */
#define ATREE(x)                 vm_nodetree_##x
#define ATREE_FUN                INTDEF
#define ATREE_CALL               KCALL
#define ATREE_NOTHROW            NOTHROW
#define Tkey                     pageid_t
#define T                        struct vm_node
#define N_NODEPATH               vn_node
#define ATREE_LOCAL_SEMI0(Tkey)  VM_SEMI0
#define ATREE_LOCAL_LEVEL0(Tkey) VM_LEVEL0
#define ATREE_HEADER_ONLY 1
#include <hybrid/sequence/atree-abi.h>
#undef ATREE_HEADER_ONLY

/* Implement the ABI for the address tree used by vm. */
#define ATREE(x)                 vm_parttree_##x
#define ATREE_FUN                INTDEF
#define ATREE_CALL               KCALL
#define ATREE_NOTHROW            NOTHROW
#define Tkey                     datapage_t
#define T                        struct vm_datapart
#define N_NODEPATH               dp_tree
#define ATREE_HEADER_ONLY 1
#include <hybrid/sequence/atree-abi.h>
#undef ATREE_HEADER_ONLY


#define ATREE(x)                 vm_futextree_##x
#define ATREE_FUN                INTDEF
#define ATREE_CALL               KCALL
#define ATREE_NOTHROW            NOTHROW
#define Tkey                     uintptr_t
#define T                        struct vm_futex
#define N_NODEPATH               f_tree
#define ATREE_HEADER_ONLY 1
#define ATREE_SINGLE 1
#include <hybrid/sequence/atree-abi.h>
#undef ATREE_SINGLE
#undef ATREE_HEADER_ONLY

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_NODEAPI_H */
