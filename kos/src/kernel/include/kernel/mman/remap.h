/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_REMAP_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_REMAP_H 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/types.h>

#include <asm/os/mman.h> /* __MREMAP_* constants */


/************************************************************************/
/* Flags for `mman_remap()'                                             */
/************************************************************************/

/* Allowed to move to a different location */
#if !defined(MREMAP_MAYMOVE) && defined(__MREMAP_MAYMOVE)
#define MREMAP_MAYMOVE __MREMAP_MAYMOVE
#endif /* !MREMAP_MAYMOVE && __MREMAP_MAYMOVE */

/* A 5th argument `new_address' is accepted that specifies the absolute, new position */
#if !defined(MREMAP_FIXED) && defined(__MREMAP_FIXED)
#define MREMAP_FIXED __MREMAP_FIXED
#endif /* !MREMAP_FIXED && __MREMAP_FIXED */


/* The following flags are accepted  by `mremap(2)', and affect  what
 * addresses are selected when the kernel has to choose a new address
 * for the resulting mapping. */
#if !defined(MREMAP_32BIT) && defined(__MREMAP_32BIT)
#define MREMAP_32BIT           __MREMAP_32BIT
#endif /* !MREMAP_32BIT && __MREMAP_32BIT */
#if !defined(MREMAP_GROWSDOWN) && defined(__MREMAP_GROWSDOWN)
#define MREMAP_GROWSDOWN       __MREMAP_GROWSDOWN
#endif /* !MREMAP_GROWSDOWN && __MREMAP_GROWSDOWN */
#if !defined(MREMAP_GROWSUP) && defined(__MREMAP_GROWSUP)
#define MREMAP_GROWSUP         __MREMAP_GROWSUP
#endif /* !MREMAP_GROWSUP && __MREMAP_GROWSUP */
#if !defined(MREMAP_STACK) && defined(__MREMAP_STACK)
#define MREMAP_STACK           __MREMAP_STACK
#endif /* !MREMAP_STACK && __MREMAP_STACK */
#if !defined(MREMAP_POPULATE) && defined(__MREMAP_POPULATE)
#define MREMAP_POPULATE        __MREMAP_POPULATE
#endif /* !MREMAP_POPULATE && __MREMAP_POPULATE */
#if !defined(MREMAP_NONBLOCK) && defined(__MREMAP_NONBLOCK)
#define MREMAP_NONBLOCK        __MREMAP_NONBLOCK
#endif /* !MREMAP_NONBLOCK && __MREMAP_NONBLOCK */
#if !defined(MREMAP_FIXED_NOREPLACE) && defined(__MREMAP_FIXED_NOREPLACE)
#define MREMAP_FIXED_NOREPLACE __MREMAP_FIXED_NOREPLACE
#endif /* !MREMAP_FIXED_NOREPLACE && __MREMAP_FIXED_NOREPLACE */
#if !defined(MREMAP_NOASLR) && defined(__MREMAP_NOASLR)
#define MREMAP_NOASLR          __MREMAP_NOASLR
#endif /* !MREMAP_NOASLR && __MREMAP_NOASLR */


#ifdef __CC__
DECL_BEGIN

struct mman;

/* Remap an existing mapping at `old_address'.
 *  - The given `new_address' (if `MREMAP_FIXED' was given)
 *    must  have the same  in-page offset as `old_address'.
 *    s.a.  `E_INVALID_ARGUMENT_CONTEXT_MREMAP_NEW_ADDRESS'
 *  - The  given `old_address' is  floor-aligned to whole pages.
 *    The resulting addend is added to `old_size' (if non-zero),
 *    `new_size', as well as the eventual `return' value.
 *  - the given `old_size' is ceil-aligned to whole pages.
 *  - the given `new_size' is ceil-aligned to whole pages.
 * This function operates in 1 of 2 ways:
 *
 * if (old_size == 0):
 *     requires:
 *       - The `MREMAP_MAYMOVE' flag _must_ be set
 *       - The mnode at `old_address' must point to a non-anonymous mpart,
 *         and have the `MNODE_F_SHARED' flag set.
 *     action:
 *       - Create   another  memory  mapping  with  the  same  protection
 *         and  share  characteristics as  that from  `old_address', such
 *         that `return...+=new_size' is mapped, `return != old_address',
 *         and the  in-file offset  at `old_address'  equals the  in-file
 *         offset at `return'. Use  `MREMAP_FIXED' and other flags  so-as
 *         to choose where to put the new mapping.
 *       - The existing mapping is kept in this case.
 * else:
 *     requires:
 *       - `old_address...+=old_size' must point to some kind of uninterrupted
 *         mapping of a singular file (such that in-file offsets for all bytes
 *         from the given range map linearly to virtual addresses).
 *     action:
 *       - When `new_size <= old_size', unmap trailing pages. For this purpose,
 *         all  pages touched by `old_address...+=new_size' will remain mapped.
 *         When `MREMAP_FIXED'  is given,  all of  the remaining  mappings  are
 *         moved  over  to `new_address...+=new_size',  and  `new_address' will
 *         be returned. Otherwise, `old_address' will be re-returned.
 *       - When `new_size > old_size', allocate more mnode/mpart pairs to fill
 *         in the missing portion of the file mapping.
 *         When `MREMAP_FIXED' is given, move the (now larger) file mapping to
 *         that address, removing the  old mapping from `old_address',  before
 *         returning the mapping at `new_address'
 *         Otherwise,  check if the  missing portion can  simply be mapped above
 *         the existing mapping (`old_address+old_size...+=(new_size-old_size)')
 *         If it can, put it at that position. Otherwise, use `MREMAP_FIXED' and
 *         other flags to choose where to put the new mapping.
 *
 * @param: self:        The relevant memory manager.
 * @param: old_address: Address of the already-existing mapping.
 * @param: old_size:    The size of the already-existing mapping (at `old_address')
 *                      Set  to  zero  for  duplication  of  PROT_SHARED  mappings.
 * @param: new_size:    The size of the to-be returned mapping.
 * @param: flags:       Set of `MREMAP_MAYMOVE | MREMAP_FIXED | MREMAP_32BIT | MREMAP_GROWSDOWN  |
 *                      MREMAP_GROWSUP | MREMAP_STACK | MREMAP_POPULATE | MREMAP_FIXED_NOREPLACE |
 *                      MREMAP_NOASLR'
 * @param: new_address: When `MREMAP_FIXED' is given: the new address of the mapping.
 * @throws: E_SEGFAULT_UNMAPPED: No mapping (or a kernel-mapping) at `old_address'
 * @throws: *:E_INVALID_ARGUMENT_CONTEXT_MREMAP_NEW_SIZE:             `new_size == 0'
 * @throws: *:E_INVALID_ARGUMENT_CONTEXT_MREMAP_FIXED_NO_MAYMOVE:     `MREMAP_FIXED' w/o `MREMAP_MAYMOVE'
 * @throws: *:E_INVALID_ARGUMENT_CONTEXT_MREMAP_NEW_ADDRESS:          `new_address & PAGEMASK != old_address & PAGEMASK'
 * @throws: *:E_INVALID_ARGUMENT_CONTEXT_MREMAP_OLDSZ0_NO_MAYMOVE:    `old_size == 0 && !MREMAP_MAYMOVE'
 * @throws: *:E_INVALID_ARGUMENT_CONTEXT_MREMAP_OLDSZ0_NOT_SHAREABLE: Mapping at `old_address' isn't `PROT_SHARED' */
FUNDEF BLOCKING_IF(flags & MREMAP_POPULATE) NONNULL((1)) void *KCALL
mman_remap(struct mman *__restrict self, UNCHECKED void *old_address,
           size_t old_size, size_t new_size, unsigned int flags,
           UNCHECKED void *new_address DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_INVALID_ARGUMENT, ...);


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_REMAP_H */
