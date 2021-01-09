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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MM_UNMAPPED_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MM_UNMAPPED_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/mman.h>
#include <kernel/mman/mm-unmapped.h>
#include <kernel/mman/mnode.h>
#include <kernel/paging.h>

#include <kos/kernel/paging.h> /* Default mapping hints */

DECL_BEGIN

#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x

#ifndef KERNEL_VMHINT_USER_MINADDR
#define KERNEL_VMHINT_USER_MINADDR (0, 0)
#endif /* !KERNEL_VMHINT_USER_MINADDR */

/* The lowest (user-space) address that might ever be automatically
 * selected for mapping by `mman_getunmapped()'. Note that the user
 * may still employ `MMAN_GETUNMAPPED_F_FIXED' to overrule this limit,
 * allowing them to mmap anywhere (in user-space)
 * When `addr' is less than this value, it will be clamped to be equal
 * to this value. Furthermore, attempting to search for free memory
 * mappings below this address always fails.
 *
 * The value of this variable is exposed in `/proc/sys/vm/mmap_min_addr' */
PUBLIC USER CHECKED void *mman_getunmapped_user_minaddr = HINT_GETADDR(KERNEL_VMHINT_USER_MINADDR);

/* Default base address for user-space memory mappings. When trying to
 * find an unmapped area within a user-space mman, the FIXED flag isn't
 * given, and the given hint-address is less than `mman_getunmapped_user_minaddr'
 * then MAX(mman_getunmapped_user_minaddr, mman_getunmapped_user_defbase)
 * will be used as initial hint instead.
 * Afterwards, the actual address to-be returned will be calculated normally.
 * By default, this variable is set to `KERNEL_VMHINT_USER_HEAP' */
PUBLIC USER CHECKED void *mman_getunmapped_user_defbase = HINT_GETADDR(KERNEL_VMHINT_USER_HEAP);

/* Same as `mman_getunmapped_user_defbase', but used instead when
 * the `MMAN_GETUNMAPPED_F_STACK' flag is given. */
PUBLIC USER CHECKED void *mman_getunmapped_user_stkbase = HINT_GETADDR(KERNEL_VMHINT_USER_STACK);

/* [lock(ATOMIC)]
 * Additional flags that are always or'd to those given to `mman_getunmapped()'
 * NOTE: _ONLY_ use this always force the `MMAN_GETUNMAPPED_F_NO_ASLR' flag to
 *       be set, thus allowing you to force-disable ASLR system-wide. Using this
 *       for other flags does what you'd think, but the results would probably
 *       be catastrophic.
 *       Also note that modifications to this variable must be done atomically! */
PUBLIC unsigned int mman_getunmapped_extflags = 0;

DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_mman_getunmapped_nx
#include "mm-unmapped.c.inl"
#define DEFINE_mman_getunmapped_or_unlock
#include "mm-unmapped.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MM_UNMAPPED_C */
