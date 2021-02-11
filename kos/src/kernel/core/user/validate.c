/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_USER_VALIDATE_C
#define GUARD_KERNEL_SRC_USER_VALIDATE_C 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/paging.h> /* ADDR_ISUSER, ADDRRANGE_ISUSER */
#include <kernel/types.h>
#include <kernel/user.h>

#include <hybrid/overflow.h>

DECL_BEGIN

/* Validate user-pointers for being allowed to be used for the specified operations.
 * Since the kernel  is allowed to  access memory that  is marked as  `PROT_NOUSER',
 * user-pointers passed from user-space must  be checked for the same  restrictions.
 * In order words: If  the  user passes  a pointer  that  is part  of kernel-space,
 *                 these functions are used to deny the user access to such memory.
 * @throw E_SEGFAULT: User-space has not been granted access to the given address range. */
PUBLIC void KCALL
validate_user(UNCHECKED USER void const *base, size_t num_bytes) THROWS(E_SEGFAULT) {
	uintptr_t endaddr;
	if unlikely(OVERFLOW_UADD((uintptr_t)base, num_bytes, &endaddr) ||
	            !ADDRRANGE_ISUSER(base, endaddr)) {
		THROW(E_SEGFAULT_UNMAPPED, base, E_SEGFAULT_CONTEXT_USERCODE);
	}
}

PUBLIC void KCALL
validate_userm(UNCHECKED USER void const *base, size_t num_items, size_t item_size_in_bytes) THROWS(E_SEGFAULT) {
	size_t total_size;
	uintptr_t endaddr;
	if unlikely(OVERFLOW_UMUL(num_items, item_size_in_bytes, &total_size) ||
	            OVERFLOW_UADD((uintptr_t)base, total_size, &endaddr) ||
	            !ADDRRANGE_ISUSER(base, endaddr)) {
		THROW(E_SEGFAULT_UNMAPPED, base, E_SEGFAULT_CONTEXT_USERCODE);
	}
}

DEFINE_PUBLIC_ALIAS(validate_readable, validate_user);
DEFINE_PUBLIC_ALIAS(validate_readwrite, validate_user);
DEFINE_PUBLIC_ALIAS(validate_readablem, validate_userm);
DEFINE_PUBLIC_ALIAS(validate_readwritem, validate_userm);

PUBLIC void KCALL
validate_writable(UNCHECKED USER void *base, size_t num_bytes) THROWS(E_SEGFAULT) {
	uintptr_t endaddr;
	if unlikely(OVERFLOW_UADD((uintptr_t)base, num_bytes, &endaddr) ||
	            !ADDRRANGE_ISUSER(base, endaddr)) {
		THROW(E_SEGFAULT_UNMAPPED, base, E_SEGFAULT_CONTEXT_USERCODE | E_SEGFAULT_CONTEXT_WRITING);
	}
}

PUBLIC void KCALL
validate_writablem(UNCHECKED USER void *base, size_t num_items, size_t item_size_in_bytes) THROWS(E_SEGFAULT) {
	size_t total_size;
	uintptr_t endaddr;
	if unlikely(OVERFLOW_UMUL(num_items, item_size_in_bytes, &total_size) ||
	            OVERFLOW_UADD((uintptr_t)base, total_size, &endaddr) ||
	            !ADDRRANGE_ISUSER(base, endaddr)) {
		THROW(E_SEGFAULT_UNMAPPED, base, E_SEGFAULT_CONTEXT_USERCODE | E_SEGFAULT_CONTEXT_WRITING);
	}
}

PUBLIC void KCALL
validate_executable(UNCHECKED USER void const *base) THROWS(E_SEGFAULT) {
	if unlikely(!ADDR_ISUSER(base))
		THROW(E_SEGFAULT_NOTEXECUTABLE, base, E_SEGFAULT_CONTEXT_USERCODE);
}

#ifndef KERNELSPACE_LOWMEM
DEFINE_PUBLIC_ALIAS(validate_readable_opt, validate_readable);
DEFINE_PUBLIC_ALIAS(validate_readablem_opt, validate_readablem);
DEFINE_PUBLIC_ALIAS(validate_writable_opt, validate_writable);
DEFINE_PUBLIC_ALIAS(validate_writablem_opt, validate_writablem);
DEFINE_PUBLIC_ALIAS(validate_executable_opt, validate_executable);
DEFINE_PUBLIC_ALIAS(validate_readwrite_opt, validate_readwrite);
DEFINE_PUBLIC_ALIAS(validate_readwritem_opt, validate_readwritem);
#else /* KERNELSPACE_LOWMEM */

PUBLIC void KCALL
validate_readable_opt(UNCHECKED USER void const *base,
                      size_t num_bytes) THROWS(E_SEGFAULT) {
	if (base)
		validate_readable(base, num_bytes);
}

PUBLIC void KCALL
validate_readablem_opt(UNCHECKED USER void const *base,
                       size_t num_items,
                       size_t item_size_in_bytes) THROWS(E_SEGFAULT) {
	if (base)
		validate_readablem(base, num_items, item_size_in_bytes);
}

PUBLIC void KCALL
validate_writable_opt(UNCHECKED USER void *base,
                      size_t num_bytes) THROWS(E_SEGFAULT) {
	if (base)
		validate_writable(base, num_bytes);
}

PUBLIC void KCALL
validate_writablem_opt(UNCHECKED USER void *base,
                       size_t num_items,
                       size_t item_size_in_bytes) THROWS(E_SEGFAULT) {
	if (base)
		validate_writablem(base, num_items, item_size_in_bytes);
}

PUBLIC void KCALL
validate_readwrite_opt(UNCHECKED USER void *base,
                       size_t num_bytes) THROWS(E_SEGFAULT) {
	if (base)
		validate_readwrite(base, num_bytes);
}

PUBLIC void KCALL
validate_readwritem_opt(UNCHECKED USER void *base,
                        size_t num_items,
                        size_t item_size_in_bytes) THROWS(E_SEGFAULT) {
	if (base)
		validate_readwritem(base, num_items, item_size_in_bytes);
}

PUBLIC void KCALL
validate_executable_opt(UNCHECKED USER void const *base) THROWS(E_SEGFAULT) {
	if (base)
		validate_executable(base);
}

#endif /* !KERNELSPACE_LOWMEM */


DECL_END

#endif /* !GUARD_KERNEL_SRC_USER_VALIDATE_C */
