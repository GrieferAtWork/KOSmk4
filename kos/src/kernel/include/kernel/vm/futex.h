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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_VM_FUTEX_H
#define GUARD_KERNEL_INCLUDE_KERNEL_VM_FUTEX_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <kernel/vm.h>

DECL_BEGIN

struct vm_futex {
	WEAK refcnt_t                                f_refcnt; /* Futex reference counter. */
	ATREE_NODE_SINGLE(struct vm_futex,uintptr_t) f_tree;   /* [lock(:dp_lock)] The tree of futex objects that exist within the data part. */
	struct sig                                   f_signal; /* The signal used to implement the futex. */
};

struct vm_futex_controller {
	struct atomic_rwlock        fc_lock;   /* Lock for this tree. */
	WEAK struct vm_futex       *fc_dead;   /* Chain of dead futex objects. */
	ATREE_HEAD(struct vm_futex) fc_tree;   /* [lock(fc_lock)] Futex tree. */
	uintptr_t                   fc_semi0;  /* [lock(fc_lock)] Futex tree SEMI0 value. */
	unsigned int                fc_level0; /* [lock(fc_lock)] Futex tree LEVEL0 value. */
};



FUNDEF ATTR_RETNONNULL NONNULL((1)) REF struct vm_futex *
(KCALL vm_datapart_lockfutex)(struct vm_datapart *__restrict self,
                              uintptr_t addr)
		THROWS(E_BADALLOC, E_WOULDBLOCK);
FUNDEF NONNULL((1)) REF struct vm_futex *
NOTHROW(KCALL vm_datapart_lockfutex_nx)(struct vm_datapart *__restrict self,
                                        uintptr_t addr);


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_VM_FUTEX_H */
