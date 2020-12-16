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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MM_UNMAPPED_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MM_UNMAPPED_H 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/types.h>

#include <asm/os/mman.h>

#ifdef __CC__
DECL_BEGIN

/* Flags for `mman_getunmapped()' and friends */
#define MMAN_GETUNMAPPED_F_CLOSEBY         0x0000                /* Same as `MMAN_GETUNMAPPED_F_ABOVE | MMAN_GETUNMAPPED_F_BELOW' (Try to return an address that is close to `addr') */
#define MMAN_GETUNMAPPED_F_ABOVE           __MAP_GROWSUP         /* [valid_if(!MMAN_GETUNMAPPED_F_FIXED)] Try to return an address `return >= addr' (but also allow returning anything else) */
#define MMAN_GETUNMAPPED_F_BELOW           __MAP_GROWSDOWN       /* [valid_if(!MMAN_GETUNMAPPED_F_FIXED)] Try to return an address `return + num_bytes <= addr' (but also allow returning anything else) */
#define MMAN_GETUNMAPPED_F_STACK           __MAP_STACK           /* [valid_if(!MMAN_GETUNMAPPED_F_FIXED)] Allocate stack memory:
                                                                  *  - When `MMAN_GETUNMAPPED_F_CLOSEBY' is given, use the proper stack
                                                                  *    growth direction `MMAN_GETUNMAPPED_F_(ABOVE|BELOW)' instead.
                                                                  *  - The given `addr' is ignored, and `mman_getunmapped_user_stkbase' is used instead.
                                                                  *  - Try to leave a gap of at least 1 page between the returned, and some
                                                                  *    adjacent memory mapping. (preventing 1 thread's stack from overflowing
                                                                  *    onto the stack of another thread, rather than crashing immediately) */
#define MMAN_GETUNMAPPED_F_FIXED           __MAP_FIXED           /* Always re-return `FLOOR_ALIGN(addr, PAGESIZE)' (but see `MMAN_GETUNMAPPED_F_FIXED_NOREPLACE')
                                                                  * NOTE: An error (either `E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY' or `E_BADALLOC_ADDRESS_ALREADY_EXISTS')
                                                                  *       is still returned if the address range `return...+=num_bytes-1' attempts to cross the user-kernel
                                                                  *       address space boundary. */
#define MMAN_GETUNMAPPED_F_FIXED_NOREPLACE __MAP_FIXED_NOREPLACE /* [valid_if(MMAN_GETUNMAPPED_F_FIXED)] Throw `E_BADALLOC_ADDRESS_ALREADY_EXISTS' if range is already in-use */
#define MMAN_GETUNMAPPED_F_32BIT           __MAP_32BIT           /* [valid_if(!MMAN_GETUNMAPPED_F_FIXED)] Only return addresses such that `return + num_bytes - 1 <= (void *)0xffffffff' */
#define MMAN_GETUNMAPPED_F_NO_ASLR         __MAP_NO_ASLR         /* [valid_if(!MMAN_GETUNMAPPED_F_FIXED)] Disable ASLR (iow: don't randomize automatically determined mmap addresses) */

/* Error return value for mman_getunmapped[_aligned]_nx */
#define MMAN_GETUNMAPPED_ERROR ((void *)-1)


/* The lowest (user-space) address that might ever be automatically
 * selected for mapping by `mman_getunmapped()'. Note that the user
 * may still employ `MMAN_GETUNMAPPED_F_FIXED' to overrule this limit,
 * allowing them to mmap anywhere (in user-space)
 * When `addr' is less than this value, it will be clamped to be equal
 * to this value. Furthermore, attempting to search for free memory
 * mappings below this address always fails.
 *
 * The value of this variable is exposed in `/proc/sys/vm/mmap_min_addr' */
DATDEF USER CHECKED void *mman_getunmapped_user_minaddr;

/* Base address from where user-space stack mappings originate from. */
DATDEF USER CHECKED void *mman_getunmapped_user_stkbase;

/* [lock(ATOMIC)]
 * Additional flags that are always or'd to those given to `mman_getunmapped()'
 * NOTE: _ONLY_ use this always force the `MMAN_GETUNMAPPED_F_NO_ASLR' flag to
 *       be set, thus allowing you to force-disable ASLR system-wide. Using this
 *       for other flags does what you'd think, but the results would probably
 *       be catastrophic.
 *       Also note that modifications to this variable must be done atomically! */
DATDEF unsigned int mman_getunmapped_extflags;


/* Try to find a suitable, unmapped address range:
 * @param: addr:      A hint for where to search for free memory.
 *                    This argument also controls if this function should return
 *                    addresses from from `THIS_MMAN' or `mman_kernel', the later
 *                    being used when `ADDR_ISKERN(addr)' (in which case you may
 *                    also assume that `ADDRRANGE_ISKERN(return, num_bytes)'), and
 *                    the former being used when `ADDR_ISUSER(addr)' (in which case
 *                    you may also assume that `ADDRRANGE_ISUSER(return, num_bytes)')
 *                    As such, the caller must something like a call to mmap(2)
 *                    will not allow the user to attempt to map something into
 *                    kernel memory!
 *                    Also note that (unless `MMAN_GETUNMAPPED_F_FIXED' is used),
 *                    the return value when `ADDR_ISUSER(addr)' is given will always
 *                    be `>= mman_getunmapped_user_minaddr'!
 * @param: num_bytes: The min. number of bytes that should not already be in use,
 *                    starting at the returned address. For this purpose, you may
 *                    assume that this function actually guaranties that at least
 *                    `CEIL_ALIGN(num_bytes, PAGESIZE)' bytes are available, unless
 *                    `MMAN_GETUNMAPPED_F_FIXED' was used
 * @param: min_alignment: The minimum alignment of the return value. Note that no matter
 *                    what is passed for this value, the actual return value will always
 *                    be aligned by at least the size of a single page. If this argument
 *                    isn't a pointer-of-2, then the alignment guarantied for the return
 *                    value is undefined, except that it will still be at least PAGESIZE!
 * @param: flags:     Set of `MMAN_GETUNMAPPED_F_*' (unknown flags are silently ignored)
 *                    HINT: values of flags are chosen to such that they are compatible
 *                          with those from the `flags' argument of `mmap(2)'
 * @return: PAGEDIR_PAGEALIGNED * : The base address where the caller's mapping should go
 * @return: MMAN_GETUNMAPPED_ERROR: Error. */
FUNDEF NOBLOCK WUNUSED void *
NOTHROW(FCALL mman_getunmapped_nx)(void *addr, size_t num_bytes, unsigned int flags,
                                   PAGEDIR_PAGEALIGNED size_t min_alignment DFL(PAGESIZE));

/* Same as above, but never return `MMAN_GETUNMAPPED_ERROR'. Instead,
 * the given mman is unlocked on error, and an exception is thrown.
 * @throws: E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY: Failed to locate a suitably large address
 *                                                  range that fits the given constraints.
 * @throws: E_BADALLOC_ADDRESS_ALREADY_EXISTS:      Both `MMAN_GETUNMAPPED_F_FIXED' and
 *                                                  `MMAN_GETUNMAPPED_F_FIXED_NOREPLACE' were
 *                                                  given, and a pre-existing mapping already
 *                                                  exists within the given address range.
 */
FUNDEF NOBLOCK WUNUSED PAGEDIR_PAGEALIGNED void *FCALL
mman_getunmapped_or_unlock(void *addr, size_t num_bytes, unsigned int flags,
                           PAGEDIR_PAGEALIGNED size_t min_alignment DFL(PAGESIZE))
		THROWS(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS);


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MM_UNMAPPED_H */
