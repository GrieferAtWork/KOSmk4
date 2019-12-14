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

/* Define the ABI for the address tree used by vm. */
#define ATREE(x)                 vm_datapart_tree_##x
#define ATREE_FUN                INTDEF
#define ATREE_CALL               KCALL
#define Tkey                     datapage_t
#define T                        struct vm_datapart
#define N_NODEPATH               dp_tree
#define ATREE_HEADER_ONLY 1
#include <hybrid/sequence/atree-abi.h>
#undef ATREE_HEADER_ONLY

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_PARTAPI_H */
