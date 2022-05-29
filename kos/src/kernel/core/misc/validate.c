/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MISC_VALIDATE_C
#define GUARD_KERNEL_SRC_MISC_VALIDATE_C 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/paging.h> /* ADDR_ISUSER, ADDRRANGE_ISUSER */
#include <kernel/types.h>
#include <kernel/user.h>

#include <hybrid/overflow.h>

DECL_BEGIN

PUBLIC ATTR_COLDTEXT ATTR_COLD ATTR_NORETURN void FCALL
except_throw_unmapped_user_rd(UNCHECKED USER void const *addr)
		THROWS(E_SEGFAULT_UNMAPPED) {
	uintptr_t flags = E_SEGFAULT_CONTEXT_USERCODE;
#ifdef ADDR_IS_NONCANON
	if (!ADDR_IS_NONCANON(addr))
		flags |= E_SEGFAULT_CONTEXT_NONCANON;
#endif /* ADDR_IS_NONCANON */
	THROW(E_SEGFAULT_UNMAPPED, addr, flags);
}

PUBLIC ATTR_COLDTEXT ATTR_COLD ATTR_NORETURN void FCALL
except_throw_unmapped_user_wr(UNCHECKED USER void const *addr)
		THROWS(E_SEGFAULT_UNMAPPED) {
	uintptr_t flags = E_SEGFAULT_CONTEXT_USERCODE | E_SEGFAULT_CONTEXT_WRITING;
#ifdef ADDR_IS_NONCANON
	if (!ADDR_IS_NONCANON(addr))
		flags |= E_SEGFAULT_CONTEXT_NONCANON;
#endif /* ADDR_IS_NONCANON */
	THROW(E_SEGFAULT_UNMAPPED, addr, flags);
}

PUBLIC ATTR_COLDTEXT ATTR_COLD ATTR_NORETURN void FCALL
except_throw_noexec_user(UNCHECKED USER void const *addr)
		THROWS(E_SEGFAULT_NOTEXECUTABLE) {
	uintptr_t flags = E_SEGFAULT_CONTEXT_USERCODE;
#ifdef ADDR_IS_NONCANON
	if (!ADDR_IS_NONCANON(addr))
		flags |= E_SEGFAULT_CONTEXT_NONCANON;
#endif /* ADDR_IS_NONCANON */
	THROW(E_SEGFAULT_NOTEXECUTABLE, addr, flags);
}



/* Validate user-pointers for being allowed to be used for the specified operations.
 * Since the kernel  is allowed to  access memory that  is marked as  `PROT_NOUSER',
 * user-pointers passed from user-space must  be checked for the same  restrictions.
 * In order words: If  the  user passes  a pointer  that  is part  of kernel-space,
 *                 these functions are used to deny the user access to such memory.
 * @throw E_SEGFAULT: User-space has not been granted access to the given address range. */
PUBLIC USER CHECKED void const *FCALL
validate_readableaddr(UNCHECKED USER void const *addr) THROWS(E_SEGFAULT) {
	if unlikely(!ADDR_ISUSER(addr))
		except_throw_unmapped_user_rd(addr);
	return addr;
}

PUBLIC USER CHECKED void *FCALL
validate_writableaddr(UNCHECKED USER void *addr) THROWS(E_SEGFAULT) {
	if unlikely(!_ADDR_ISUSER(addr))
		except_throw_unmapped_user_wr(addr);
	return addr;
}

PUBLIC USER CHECKED void const *FCALL
validate_executable(UNCHECKED USER void const *addr) THROWS(E_SEGFAULT) {
	if unlikely(!_ADDR_ISUSER(addr))
		except_throw_noexec_user(addr);
	return addr;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_VALIDATE_C */
