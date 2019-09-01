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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_FUTEX_C
#define GUARD_KERNEL_SRC_MEMORY_VM_FUTEX_C 1

#include <kernel/aio.h>
#include <kernel/malloc.h>
#include <kernel/vm.h>
#include <kernel/vm/futex.h>

#include "vm-nodeapi.h"

#define ATREE(x)                 vm_futextree_##x
#define ATREE_FUN                INTDEF
#define ATREE_IMP                INTERN
#define ATREE_CALL               KCALL
#define Tkey                     uintptr_t
#define T                        struct vm_futex
#define N_NODEPATH               f_tree
#define ATREE_IMPLEMENTATION_ONLY 1
#define ATREE_SINGLE 1
#include <hybrid/sequence/atree-abi.h>
#undef ATREE_IMPLEMENTATION_ONLY
#undef ATREE_SINGLE

DECL_BEGIN

FUNDEF WUNUSED ATTR_CONST ATTR_RETNONNULL NONNULL((1)) struct vm_futex_controller *
(FCALL vm_datapart_futexctl)(struct vm_datapart *__restrict self) THROWS(E_BADALLOC,E_WOULDBLOCK);
FUNDEF WUNUSED ATTR_CONST NONNULL((1)) struct vm_futex_controller *
NOTHROW(FCALL vm_datapart_futexctl_nx)(struct vm_datapart *__restrict self);

/* Broadcast to all thread waiting for a futex at `futex_address' within the current VM */
PUBLIC void
(FCALL vm_futex_broadcast)(void *futex_address)
       THROWS(E_WOULDBLOCK,E_SEGFAULT) {
	/* TODO */
	(void)futex_address;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_FUTEX_C */
