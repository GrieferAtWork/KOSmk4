/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_UNMAPPED_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_UNMAPPED_H 1

#include <kernel/compiler.h>

#include <kernel/mman.h> /* Needed for `struct mman' for `mman_findunmapped_in_usertree()' */
#include <kernel/paging.h>
#include <kernel/types.h>

#include <hybrid/__atomic.h>
#include <hybrid/host.h> /* __ARCH_STACK_GROWS_DOWNWARDS */

#include <asm/os/mman.h>       /* __MAP_* constants */
#include <kos/kernel/paging.h> /* KERNEL_MHINT_* */

#ifdef __CC__
DECL_BEGIN

struct unlockinfo;

/************************************************************************/
/* Flags for `mman_findunmapped()' and friends                          */
/************************************************************************/

/* Always re-return `FLOOR_ALIGN(addr, PAGESIZE)' (but see `MAP_FIXED_NOREPLACE')
 * NOTE: An error (either `E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY' or `E_BADALLOC_ADDRESS_ALREADY_EXISTS')
 *       is still returned if the address range `return...+=num_bytes-1' attempts to cross the user-kernel
 *       address space boundary, or user-space attempts to map into kernel-space. */
#if !defined(MAP_FIXED) && defined(__MAP_FIXED)
#define MAP_FIXED __MAP_FIXED
#endif /* !MAP_FIXED && __MAP_FIXED */

/* [valid_if(MAP_FIXED)]
 * Don't  override  existing mappings  when `MAP_FIXED'  is passed.
 * Instead, throw an exception `E_BADALLOC_ADDRESS_ALREADY_EXISTS'. */
#if !defined(MAP_FIXED_NOREPLACE) && defined(__MAP_FIXED_NOREPLACE)
#define MAP_FIXED_NOREPLACE __MAP_FIXED_NOREPLACE
#endif /* !MAP_FIXED_NOREPLACE && __MAP_FIXED_NOREPLACE */

/* [valid_if(!MAP_FIXED)]
 * Only return addresses such that `return + num_bytes - 1 <= (void *)0xffffffff' */
#if !defined(MAP_32BIT) && defined(__MAP_32BIT)
#define MAP_32BIT __MAP_32BIT
#endif /* !MAP_32BIT && __MAP_32BIT */

/* [valid_if(!MAP_FIXED)]
 * Try to return an address `return + num_bytes <= addr' (only try: also allow returning anything else)
 * If neither this flag, nor `MAP_GROWSUP' is given, try  to return an address that is close to  `addr' */
#if !defined(MAP_GROWSDOWN) && defined(__MAP_GROWSDOWN)
#define MAP_GROWSDOWN __MAP_GROWSDOWN
#endif /* !MAP_GROWSDOWN && __MAP_GROWSDOWN */

/* [valid_if(!MAP_FIXED)]
 * Try  to  return  an  address  `return >= addr'  (only  try:  also  allow  returning  anything  else)
 * If neither this flag, nor `MAP_GROWSDOWN' is given, try to return an address that is close to `addr' */
#if !defined(MAP_GROWSUP) && defined(__MAP_GROWSUP)
#define MAP_GROWSUP __MAP_GROWSUP
#endif /* !MAP_GROWSUP && __MAP_GROWSUP */

/* [valid_if(!MAP_FIXED)] Allocate stack memory:
 *  - When neither `MAP_GROWSDOWN' nor `MAP_GROWSZO' was given, use the proper
 *    stack growth direction (`#ifdef __ARCH_STACK_GROWS_DOWNWARDS')  instead.
 *  - The default for `addr' is `mman_getunmapped_user_stkbase' instead of
 *    `mman_getunmapped_user_defbase'
 *  - Try  to leave a gap of at least  1 page between the returned, and some
 *    adjacent memory mapping. (preventing 1 thread's stack from overflowing
 *    onto the stack of another thread, rather than crashing immediately) */
#if !defined(MAP_STACK) && defined(__MAP_STACK)
#define MAP_STACK __MAP_STACK
#endif /* !MAP_STACK && __MAP_STACK */

/* [valid_if(!MAP_FIXED)]
 * Disable ASLR (iow: don't randomize automatically determined mmap addresses) */
#if !defined(MAP_NOASLR) && defined(__MAP_NOASLR)
#define MAP_NOASLR __MAP_NOASLR
#endif /* !MAP_NOASLR && __MAP_NOASLR */


/* Error return value for `mman_findunmapped()' & friends */
#if !defined(MAP_FAILED) && defined(__MAP_FAILED)
#define MAP_FAILED __MAP_FAILED
#endif /* !MAP_FAILED && __MAP_FAILED */


/* Check if the initial search should only be performed above/below.
 * When both of these are false, the initial search is performed  in
 * in both directions. */
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
#define MMAN_GETUNMAPPED_ISBELOW(x) ((x) & (MAP_GROWSDOWN | MAP_STACK))
#define MMAN_GETUNMAPPED_ISABOVE(x) ((x) & MAP_GROWSUP)
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
#define MMAN_GETUNMAPPED_ISBELOW(x) ((x) & MAP_GROWSDOWN)
#define MMAN_GETUNMAPPED_ISABOVE(x) ((x) & (MAP_GROWSUP | MAP_STACK))
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */


/* Helper macros to extract the addr/flags from KERNEL_MHINT_* macros. */
#ifndef MHINT_GETADDR
#define __PRIVATE_MHINT_ADDR(x, y) x
#define __PRIVATE_MHINT_MODE(x, y) y
#define MHINT_GETADDR(x) __PRIVATE_MHINT_ADDR x
#define MHINT_GETMODE(x) __PRIVATE_MHINT_MODE x
#endif /* !MHINT_GETADDR */



/* The lowest (user-space) address  that might ever be  automatically
 * selected for mapping by `mman_findunmapped()'. Note that the  user
 * may still employ `MAP_FIXED' to overrule this limit, allowing them
 * to mmap anywhere (in user-space).
 *
 * When `addr' is less than this value, it will be clamped to be equal
 * to this value.  Furthermore, attempting to  search for free  memory
 * mappings below this address always fails.
 *
 * The value of this variable is exposed in `/proc/sys/vm/mmap_min_addr' */
DATDEF NCX void *mman_getunmapped_user_minaddr;

/* Default base address for user-space  memory mappings. When trying to  find
 * an unmapped area within a user-space mman, the FIXED flag isn't given, and
 * the  given hint-address is  less than `mman_getunmapped_user_minaddr' then
 * MAX(mman_getunmapped_user_minaddr, mman_getunmapped_user_defbase) will  be
 * used as initial hint instead.
 * Afterwards, the actual address to-be returned will be calculated normally.
 *
 * By default, this variable is set to `KERNEL_MHINT_USER_HEAP' */
DATDEF NCX void *mman_getunmapped_user_defbase;

/* Same as `mman_getunmapped_user_defbase', but used
 * instead  when  the  `MAP_STACK'  flag  is  given. */
DATDEF NCX void *mman_getunmapped_user_stkbase;

/* [lock(ATOMIC)]
 * Additional flags that are always or'd to those given to `mman_findunmapped()'
 * NOTE: _ONLY_ use this always force the  `MAP_NOASLR' flag to be set,  thus
 *       allowing you to force-disable ASLR system-wide. Using this for other
 *       flags  does  what you'd  think, but  the  results would  probably be
 *       catastrophic.
 *       Also note that modifications to this variable must be done atomically! */
DATDEF unsigned int mman_findunmapped_extflags;

/* Helper macros to enable/disable ASLR globally. */
#define mman_findunmapped_aslr_enable()      __hybrid_atomic_and(&mman_findunmapped_extflags, ~MAP_NOASLR, __ATOMIC_SEQ_CST)
#define mman_findunmapped_aslr_disable()     __hybrid_atomic_or(&mman_findunmapped_extflags, MAP_NOASLR, __ATOMIC_SEQ_CST)
#define mman_findunmapped_aslr_getenabled()  (!(__hybrid_atomic_load(&mman_findunmapped_extflags, __ATOMIC_ACQUIRE) & MAP_NOASLR))
#define mman_findunmapped_aslr_setenabled(v) ((v) ? mman_findunmapped_aslr_enable() : mman_findunmapped_aslr_disable())


/* Try to find a suitable, unmapped address range. Note that this function  never
 * throws an exception, but also doesn't allow for use of `MAP_FIXED'. Attempting
 * to  pass that flag is simply ignored, and the function acts as though that bit
 * hadn't actually been set.
 * @param: self:      The mman in which to create the mapping. For this purpose,
 *                    any mman  other than  `mman_kernel' will  always cause  an
 *                    error when trying to map to a kernel-space address.
 *                    NOTE: The caller must be holding a lock to this mman!
 * @param: addr:      A hint for where to search for free memory.
 * @param: num_bytes: The min. number of bytes that  should not already be in  use,
 *                    starting at the returned address.  For this purpose, you  may
 *                    assume that this function  actually guaranties that at  least
 *                    `CEIL_ALIGN(num_bytes, PAGESIZE)' bytes are available, unless
 *                    `MAP_FIXED' was used
 * @param: min_alignment: The minimum alignment of the return value. Note that no matter
 *                    what is passed for this value, the actual return value will  always
 *                    be  aligned by at least the size of a single page. If this argument
 *                    isn't a pointer-of-2, then the alignment guarantied for the  return
 *                    value is undefined, except that it will still be at least PAGESIZE!
 * @param: min_alignment_offset: [valid_if(IS_POWER_OF_TWO(min_alignment) && min_alignment >= PAGESIZE)]
 *                    Offset from `return' at which `min_alignment' shall be applied.
 *                    If  valid, this  argument _must_  be a  multiple of `PAGESIZE'.
 * @param: flags:     Set of `MAP_GROWSDOWN | MAP_GROWSUP | MAP_32BIT | MAP_STACK | MAP_NOASLR'
 *                    Unknown flags are silently ignored.
 * @return: PAGEDIR_PAGEALIGNED * : The base address where the caller's mapping should go
 * @return: MAP_FAILED:             Error: No free space matching requirements was found. */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) void *
NOTHROW(FCALL mman_findunmapped)(struct mman const *__restrict self, void *addr,
                                 size_t num_bytes, unsigned int flags,
                                 size_t min_alignment DFL(PAGESIZE),
                                 ptrdiff_t min_alignment_offset DFL(0));

/* Given a `struct mnode **p_tree_root', try to find a free user-space location.
 * Don't  use this function. - It's a kind-of hacky work-around to allow for the
 * use of `mman_findunmapped()' in implementing `mbuilder_findunmapped()' */
#define mman_findunmapped_in_usertree(p_tree_root, ...) \
	mman_findunmapped(COMPILER_CONTAINER_OF(p_tree_root, struct mman, mm_mappings), __VA_ARGS__)


/* Similar to `mman_findunmapped()', but never return `MAP_FAILED', and automatically split
 * mem-nodes  at the resulting min/max bounds when `MAX_FIXED' w/o `MAP_FIXED_NOREPLACE' is
 * used, and another mapping already existed at  the specified location. If this cannot  be
 * done  without blocking, release all locks, do the split while not holding any locks, and
 * return `MAP_FAILED', indicative of the caller needing to re-acquire locks and re-attempt
 * the call.
 * @param: self:      The mman in which to create the mapping. For this purpose,
 *                    any mman  other than  `mman_kernel' will  always cause  an
 *                    error when trying to map to a kernel-space address.
 *                    NOTE: The caller must be holding a lock to this mman!
 * @param: addr:      A hint for where to search for free memory.
 * @param: num_bytes: The min. number of bytes that  should not already be in  use,
 *                    starting at the returned address.  For this purpose, you  may
 *                    assume that this function  actually guaranties that at  least
 *                    `CEIL_ALIGN(num_bytes, PAGESIZE)' bytes are available, unless
 *                    `MAP_FIXED' was used
 * @param: min_alignment: The minimum alignment of the return value. Note that no matter
 *                    what is passed for this value, the actual return value will  always
 *                    be  aligned by at least the size of a single page. If this argument
 *                    isn't a pointer-of-2, then the alignment guarantied for the  return
 *                    value is undefined, except that it will still be at least PAGESIZE!
 * @param: min_alignment_offset: [valid_if(IS_POWER_OF_TWO(min_alignment) && min_alignment >= PAGESIZE)]
 *                    Offset from `return' at which `min_alignment' shall be applied.
 *                    If  valid, this  argument _must_  be a  multiple of `PAGESIZE'.
 * @param: flags:     Set of `MAP_GROWSDOWN | MAP_GROWSUP | MAP_32BIT | MAP_STACK | MAP_NOASLR'
 *                    Additionally,   `MAP_FIXED'   and  `MAP_FIXED_NOREPLACE'   are  accepted.
 *                    Unknown flags are silently ignored.
 * @return: PAGEDIR_PAGEALIGNED * : The base address where the caller's mapping should go
 * @return: MAP_FAILED:             Locks had to be released, but another attempt might succeed.
 *                                  Reacquire  all  required  locks,  and  re-attempt  the call.
 * @throws: E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY: Failed to locate a suitably large address
 *                                                  range  that  fits the  given constraints.
 * @throws: E_BADALLOC_ADDRESS_ALREADY_EXISTS:      Both  `MAP_FIXED'  and   `MAP_FIXED_NOREPLACE'
 *                                                  were given, and a pre-existing mapping already
 *                                                  exists within the given address range. */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) void *FCALL
mman_getunmapped_or_unlock(struct mman *__restrict self, void *addr,
                           size_t num_bytes, unsigned int flags,
                           size_t min_alignment DFL(PAGESIZE),
                           ptrdiff_t min_alignment_offset DFL(0),
                           struct unlockinfo *unlock DFL(__NULLPTR))
		THROWS(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS);

/* Helpers macros for finding unmapped areas within the kernel for specific purposes. */
#define mman_findunmapped_device(num_bytes, ...)             mman_findunmapped(&mman_kernel, MHINT_GETADDR(KERNEL_MHINT_DEVICE), num_bytes, MHINT_GETMODE(KERNEL_MHINT_DEVICE), ##__VA_ARGS__)
#define mman_findunmapped_temporary(num_bytes, ...)          mman_findunmapped(&mman_kernel, MHINT_GETADDR(KERNEL_MHINT_TEMPORARY), num_bytes, MHINT_GETMODE(KERNEL_MHINT_TEMPORARY), ##__VA_ARGS__)
#define mman_getunmapped_or_unlock_device(num_bytes, ...)    mman_getunmapped_or_unlock(&mman_kernel, MHINT_GETADDR(KERNEL_MHINT_DEVICE), num_bytes, MHINT_GETMODE(KERNEL_MHINT_DEVICE), ##__VA_ARGS__)
#define mman_getunmapped_or_unlock_temporary(num_bytes, ...) mman_getunmapped_or_unlock(&mman_kernel, MHINT_GETADDR(KERNEL_MHINT_TEMPORARY), num_bytes, MHINT_GETMODE(KERNEL_MHINT_TEMPORARY), ##__VA_ARGS__)

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_UNMAPPED_H */
