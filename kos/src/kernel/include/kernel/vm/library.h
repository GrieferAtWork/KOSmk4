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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_VM_LIBRARY_H
#define GUARD_KERNEL_INCLUDE_KERNEL_VM_LIBRARY_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <kernel/vm.h>

#include <kos/exec/library-listdef.h>

DECL_BEGIN

/* Library listing information, as set by user-space.
 * When unavailable, `lld_size' is set to ZERO(0).
 * WARNING: Aside from `lld_size', fields of this structure must be validated
 *          when used! - The set_library_listdef(2) system call does _NOT_
 *          structure fields other than `lld_size'! */
DATDEF ATTR_PERVM struct library_listdef thisvm_library_listdef;
#define THIS_LIBRARY_LISTDEF       PERVM(thisvm_library_listdef)



/* Callback prototype for enumerating user-space libraries though use of `set_library_listdef(2)'
 * @return: < 0:  Error (propagate immediately)
 * @return: >= 0: Success (add to sum to-be returned on success) */
typedef ssize_t
(KCALL *vm_library_enumerate_callback_t)(void *arg,
                                         struct vm *__restrict effective_vm,
                                         USER CHECKED char const *filename,
                                         USER UNCHECKED void *loadaddr,
                                         USER UNCHECKED void *loadstart,
                                         bool filename_may_be_relative)
		/*THROWS(E_SEGFAULT)*/;

/* Using information set through `set_library_listdef(2)', try to enumerate
 * libraries that have been loaded by user-space into the given `effective_vm'.
 * Note that information enumerated by this cannot be trusted in any serious context.
 * Nor can it be guarantied that this enumeration will not result in a SEGFAULT being
 * thrown. - Information enumerated is entirely under the control of user-space, with
 * the kernel having absolutely no control of what's going on. - So care must be taken
 * to _always_ handle the E_SEGFAULT which may be thrown by this function!
 * NOTE: This function does however take care to prevent:
 *   - Infinite loops resulting from user-space creating a
 *     linked list pointing back to one of its previous nodes.
 *   - Kernel-space pointers appearing somewhere where a pointer needs to be dereferenced.
 *     Note however that the loadaddr/loadstart argument are not validated at all!
 * @throws: E_BADALLOC: To prevent loops in the event of a linked list, a pointer set is
 *                      used internally. - However this set may get allocated on the heap...
 * @return: < 0:  Error (First negative return value of `*func')
 * @return: >= 0: Success (sum of all calls to `*func') */
FUNDEF ssize_t KCALL
vm_library_enumerate(struct vm *__restrict effective_vm,
                     vm_library_enumerate_callback_t func,
                     void *arg, size_t maxcount DFL((size_t)-1))
		THROWS(E_SEGFAULT, E_BADALLOC);




DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_VM_LIBRARY_H */
