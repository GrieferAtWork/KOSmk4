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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MM_MAP_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MM_MAP_H 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/types.h>

#include <hybrid/host.h> /* __ARCH_STACK_GROWS_DOWNWARDS */

#include <asm/os/mman.h> /* __PROT_* and __MAP_* constants */



/************************************************************************/
/* Flags for `mman_map*::prot'                                          */
/************************************************************************/

/* Data cannot be accessed. */
#if !defined(PROT_NONE) && defined(__PROT_NONE)
#define PROT_NONE __PROT_NONE
#endif /* !PROT_NONE && __PROT_NONE */

/* Data can be executed. */
#if !defined(PROT_EXEC) && defined(__PROT_EXEC)
#define PROT_EXEC __PROT_EXEC
#endif /* !PROT_EXEC && __PROT_EXEC */

/* Data can be written. */
#if !defined(PROT_WRITE) && defined(__PROT_WRITE)
#define PROT_WRITE __PROT_WRITE
#endif /* !PROT_WRITE && __PROT_WRITE */

/* Data can be read. */
#if !defined(PROT_READ) && defined(__PROT_READ)
#define PROT_READ __PROT_READ
#endif /* !PROT_READ && __PROT_READ */

/* Changes are shared, even after the VM was cloned (`CLONE_VM').
 * NOTE: Same as the `MAP_SHARED' map flag, but
 *       can be set like any other protection. */
#if !defined(PROT_SHARED) && defined(__PROT_SHARED)
#define PROT_SHARED __PROT_SHARED
#endif /* !PROT_SHARED && __PROT_SHARED */


/************************************************************************/
/* Flags for `mman_map*::flags'                                         */
/************************************************************************/

/* Interpret addr exactly. */
#if !defined(MAP_FIXED) && defined(__MAP_FIXED)
#define MAP_FIXED __MAP_FIXED
#endif /* !MAP_FIXED && __MAP_FIXED */

/* Only give out 32-bit addresses. */
#if !defined(MAP_32BIT) && defined(__MAP_32BIT)
#define MAP_32BIT __MAP_32BIT
#endif /* !MAP_32BIT && __MAP_32BIT */

/* Stack-like segment. */
#if !defined(MAP_GROWSDOWN) && defined(__MAP_GROWSDOWN)
#define MAP_GROWSDOWN __MAP_GROWSDOWN
#endif /* !MAP_GROWSDOWN && __MAP_GROWSDOWN */

/* Stack-like segment growing upwards. */
#if !defined(MAP_GROWSUP) && defined(__MAP_GROWSUP)
#define MAP_GROWSUP __MAP_GROWSUP
#endif /* !MAP_GROWSUP && __MAP_GROWSUP */

/* Lock the mapping. */
#if !defined(MAP_LOCKED) && defined(__MAP_LOCKED)
#define MAP_LOCKED __MAP_LOCKED
#endif /* !MAP_LOCKED && __MAP_LOCKED */

/* Populate (prefault) pagetables. */
#if !defined(MAP_POPULATE) && defined(__MAP_POPULATE)
#define MAP_POPULATE __MAP_POPULATE
#endif /* !MAP_POPULATE && __MAP_POPULATE */

/* Do not block on IO. */
#if !defined(MAP_NONBLOCK) && defined(__MAP_NONBLOCK)
#define MAP_NONBLOCK __MAP_NONBLOCK
#endif /* !MAP_NONBLOCK && __MAP_NONBLOCK */

/* Allocation is for a stack.
 * NOTE: KOS uses this flag to determine where
 *       automatic memory mappings are allocated at. */
#if !defined(MAP_STACK) && defined(__MAP_STACK)
#define MAP_STACK __MAP_STACK
#endif /* !MAP_STACK && __MAP_STACK */

/* Don't override existing mappings when `MAP_FIXED' is passed.
 * Instead, throw an exception `E_BADALLOC_ADDRESS_ALREADY_EXISTS'. */
#if !defined(MAP_FIXED_NOREPLACE) && defined(__MAP_FIXED_NOREPLACE)
#define MAP_FIXED_NOREPLACE __MAP_FIXED_NOREPLACE
#endif /* !MAP_FIXED_NOREPLACE && __MAP_FIXED_NOREPLACE */

/* Disable ASLR (iow: don't randomize automatically determined mmap addresses)  */
#if !defined(MAP_NO_ASLR) && defined(__MAP_NO_ASLR)
#define MAP_NO_ASLR __MAP_NO_ASLR
#endif /* !MAP_NO_ASLR && __MAP_NO_ASLR */

/* Kernel-only mmap flag: Set the `MNODE_F_MPREPARED' node flag,
 * and ensure that the backing page directory address range is kept
 * prepared for the duration of the node's lifetime. */
#define MAP_PREPARED 0x0800

#ifdef __CC__
DECL_BEGIN

struct mman;
struct mfile;
struct path;
struct directory_entry;

#ifndef __mfile_ndef_defined
#define __mfile_ndef_defined 1
DATDEF struct mfile mfile_ndef;     /* Random, uninitialized, anonymous memory. */
#endif /* !__mfile_ndef_defined */

#ifndef __mfile_zero_defined
#define __mfile_zero_defined 1
DATDEF struct mfile mfile_zero;     /* Zero-initialized, anonymous memory. */
#endif /* !__mfile_zero_defined */


/* Map a given file into the specified mman.
 * @param: hint:          s.a. `mman_findunmapped'
 * @param: prot:          Set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SHARED' (Other bits are silently ignored)
 * @param: flags:         Set of `MAP_LOCKED | MAP_POPULATE | MAP_NONBLOCK | MAP_PREPARED' (Other bits are silently ignored)
 *                        Additionally, the following flags may be set to customize the behavior of how
 *                        a suitable address is located (s.a. `mman_findunmapped()' for more info):
 *                        `MAP_FIXED | MAP_32BIT | MAP_GROWSDOWN | MAP_GROWSUP | MAP_STACK | MAP_FIXED_NOREPLACE'
 * @param: file:          The file that is being mapped.
 * @param: file_fspath:   Optional mapping path (only used for memory->disk mapping listings)
 * @param: file_fsname:   Optional mapping name (only used for memory->disk mapping listings)
 * @param: file_pos:      Offset into the file being mapped, of where the mapping should start.
 *                        If this value isn't page-aligned, then its sub-page offset is added
 *                        to the return value eventually returned by this function.
 *                        But that that when `MAP_FIXED' flag is also set, then the sub-page
 *                        offset of `hint' will be silently ignored, meaning that in this case
 *                        the return value may differ from `hint'!
 * @param: min_alignment: s.a. `mman_findunmapped'
 * @return: * : The effective mapping base at which `file->DATA.BYTES[file_pos]' can be found,
 *              unless `num_bytes' was given as `0', in which case the return value is undefined,
 *              but arguably valid (e.g. will be a user-/kernel-space location as it would have
 *              been when `num_bytes' was non-zero). */
FUNDEF NONNULL((1, 6)) void *KCALL
mman_map(struct mman *__restrict self,
         UNCHECKED void *hint, size_t num_bytes,
         unsigned int prot DFL(PROT_READ | PROT_WRITE | PROT_SHARED),
         unsigned int flags DFL(0),
         struct mfile *__restrict file DFL(&mfile_zero),
         struct path *file_fspath DFL(__NULLPTR),
         struct directory_entry *file_fsname DFL(__NULLPTR),
         pos_t file_pos DFL(0),
         size_t min_alignment DFL(PAGESIZE))
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS);


/* Same as `mman_map()', but only allow pages entirely contained within
 * the file-relative address range `file_map_minaddr...file_map_maxaddr'
 * to be mapped. Attempting to map file contents beyond this range will
 * instead result in `&mfile_zero' getting mapped instead.
 * This function is mainly used to restrict access to raw physical memory
 * when user-space is allowed to directly mmap() device ram, but the driver
 * want's to prevent user-space from mapping more than the physical address
 * ranges actually associated with a device. */
FUNDEF NONNULL((1, 6)) void *KCALL
mman_map_subrange(struct mman *__restrict self,
                  UNCHECKED void *hint, size_t num_bytes,
                  unsigned int prot DFL(PROT_READ | PROT_WRITE | PROT_SHARED),
                  unsigned int flags DFL(0),
                  struct mfile *__restrict file DFL(&mfile_zero),
                  struct path *file_fspath DFL(__NULLPTR),
                  struct directory_entry *file_fsname DFL(__NULLPTR),
                  pos_t file_pos DFL(0),
                  pos_t file_map_minaddr DFL(0),
                  pos_t file_map_maxaddr DFL((pos_t)-1),
                  size_t min_alignment DFL(PAGESIZE))
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS);


/* Same as `mman_map()', but instead of actually mapping something, leave the
 * address range as empty (but possibly prepared), making it a reserved address range.
 * @param: flags: Set of `MAP_PREPARED' (Other bits are silently ignored)
 *                Additionally, the usual bits relating to `mman_findunmapped()' are accepted:
 *                `MAP_FIXED | MAP_32BIT | MAP_GROWSDOWN | MAP_GROWSUP | MAP_STACK | MAP_FIXED_NOREPLACE' */
FUNDEF NONNULL((1)) void *KCALL
mman_map_res(struct mman *__restrict self,
             UNCHECKED void *hint, size_t num_bytes,
             unsigned int flags DFL(0),
             size_t min_alignment DFL(PAGESIZE))
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS);


/* Flags for `mman_unmap()' and `mman_protect()' */
#define MMAN_UNMAP_FAULTIFUNUSED 0x0001 /* Throw an `E_SEGFAULT_UNMAPPED' exception with the lowest address of
                                         * the first segment of memory apart of the given range that isn't mapped
                                         * to some node that's allowed to be unmapped. This check is done such that
                                         * it happens before any memory may get unmapped, meaning that when given,
                                         * the function will only succeed when the entire range can be unmapped at
                                         * once, and fail with an E_SEGFAULT otherwise. When not set, unmapped
                                         * portions of the given address range are silently ignored. */
#define MMAN_UNMAP_NOSPLIT       0x0002 /* Don't split nodes in order to be able to partially unmap one of them.
                                         * Instead, only unmap whole nodes, or nothing at all. */
#define MMAN_UNMAP_NOKERNPART    0x0004 /* Instead of causing kernel panic when attempting to unmap
                                         * a kernel part, simply ignore the request (this flag is set
                                         * when user-space tries to unmap memory) */

/* Unmap all memory mappings within the given address range.
 * The actual range is widened to include all whole pages that overlap the given range.
 * @param: addr:      The base address at which to start unmapping memory.
 * @param: num_bytes: The # of continuous bytes of memory to unmap, starting at `addr'
 * @param: flags:     Set of `MMAN_UNMAP_*'
 * @return: * :       The actual # of unmapped bytes of memory. */
FUNDEF NONNULL((1)) size_t KCALL
mman_unmap(struct mman *__restrict self,
           UNCHECKED void *addr, size_t num_bytes,
           unsigned int flags DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);



/* Update access protection flags within the given address range.
 * @param: addr:       The base address at which to start changing protection.
 * @param: num_bytes:  The number of continuous bytes of memory to change, starting at `addr'
 * @param: prot_mask:  Mask of protection bits that should be kept (Set of `PROT_EXEC | PROT_WRITE | PROT_READ').
 * @param: prot_flags: Set of protection bits that should be added (Set of `PROT_EXEC | PROT_WRITE | PROT_READ').
 * @param: flags:      Set of `MMAN_UNMAP_*'
 * @return: * :        The actual # of (possibly) altered bytes of memory. */
FUNDEF NONNULL((1)) size_t KCALL
mman_protect(struct mman *__restrict self,
             UNCHECKED void *addr, size_t num_bytes,
             unsigned int prot_mask, unsigned int prot_flags,
             unsigned int how DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);


/* Sync all changes made to file mappings within the given
 * address range with on-disk file images. (s.a. `mfile_sync()')
 * NOTE: Memory ranges that aren't actually mapped, aren't mapped
 *       with WRITE and SHARED, or aren't mapped to write-back files
 *       are simply ignored. */
FUNDEF void FCALL
mman_syncmem(struct mman *__restrict self,
             PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
             PAGEDIR_PAGEALIGNED size_t num_bytes)
		THROWS(E_WOULDBLOCK, ...);



#ifndef __gfp_t_defined
#define __gfp_t_defined 1
typedef unsigned int gfp_t;
#endif /* !__gfp_t_defined */


/************************************************************************/
/* Additional GFP_* flags for `mmap_map_kernel_ram()'                   */
/************************************************************************/

#define GFP_MAP_32BIT        0x0040 /* The backing _physical_ memory will use 32-bit addresses.
                                     * This differs from the normal meaning of the `MAP_32BIT' flag!!! */
#define GFP_MAP_PREPARED     0x0800 /* Set the `MNODE_F_MPREPARED' node flag, and ensure that
                                     * the backing page directory address range is kept prepared
                                     * for the duration of the node's lifetime. */
#define GFP_MAP_BELOW        0x0100 /* s.a. `MMAN_GETUNMAPPED_F_BELOW' */
#define GFP_MAP_ABOVE        0x0200 /* s.a. `MMAN_GETUNMAPPED_F_ABOVE' */
#define GFP_MAP_NOASLR   0x40000000 /* s.a. `MMAN_GETUNMAPPED_F_NO_ASLR' */


/* @param: gfp: Set of:
 *   - GFP_LOCKED:       Normal behavior
 *   - GFP_PREFLT:       Prefault everything
 *   - GFP_CALLOC:       Allocate from `mfile_zero' instead of `mfile_ndef'
 *   - GFP_ATOMIC:       Don't block when waiting to acquire any sort of lock.
 *   - GFP_NOMMAP:       Unconditionally throw `E_WOULDBLOCK_PREEMPTED'
 *   - GFP_VCBASE:       Allocate the mnode and mpart from the core-part heap.
 *                       This also causes the `MNODE_F_COREPART' / `MPART_F_COREPART'
 *                       flags to be set for each resp. This flag is used internally
 *                       to resolve the dependency loop between this function needing
 *                       to call kmalloc() and kmalloc() needing to call this function.
 *   - GFP_MAP_32BIT:    Allocate 32-bit physical memory addresses. This flag
 *                       must be combined with `MAP_POPULATE', and should also
 *                       be combined with `GFP_LOCKED' to prevent the backing
 *                       physical memory from being altered.
 *   - GFP_MAP_PREPARED: Ensure that all mapped pages are prepared, and left as such
 *   - GFP_MAP_BELOW:    s.a. `MMAN_GETUNMAPPED_F_BELOW'
 *   - GFP_MAP_ABOVE:    s.a. `MMAN_GETUNMAPPED_F_ABOVE'
 *   - GFP_MAP_NOASLR:   s.a. `MMAN_GETUNMAPPED_F_NO_ASLR'
 *   - GFP_NOCLRC:       Don't call `system_clearcaches()' to try to free up memory
 *   - GFP_NOSWAP:       Don't move memory to swap to free up memory
 *   - Other flags are silently ignored, but will be forwarded onto
 *     other calls to kmalloc() that may need to be made internally. */
FUNDEF NOBLOCK_IF(gfp & GFP_ATOMIC) PAGEDIR_PAGEALIGNED void *FCALL
mmap_map_kernel_ram(PAGEDIR_PAGEALIGNED void *hint,
                    PAGEDIR_PAGEALIGNED size_t num_bytes,
                    gfp_t gfp, size_t min_alignment DFL(PAGESIZE));
/* Non-throwing version of `mmap_map_kernel_ram()'.
 * returns `MMAP_MAP_KERNEL_RAM_NX_ERROR' on error. */
FUNDEF NOBLOCK_IF(gfp & GFP_ATOMIC) PAGEDIR_PAGEALIGNED void *
NOTHROW(FCALL mmap_map_kernel_ram_nx)(PAGEDIR_PAGEALIGNED void *hint,
                                      PAGEDIR_PAGEALIGNED size_t num_bytes,
                                      gfp_t gfp, size_t min_alignment DFL(PAGESIZE));
#define MMAP_MAP_KERNEL_RAM_NX_ERROR ((void *)-1)

/* Without blocking, unmap a given region of kernel RAM.
 * These functions will attempt to acquire a lock to the kernel mman, and
 * if that fails, will instead inject a pending lock operation into the
 * kernel mman's `mman_kernel_lockops', which will then perform the actual
 * job of unmapping the associated address range as soon as doing so becomes
 * possible.
 * These functions may only be used to unmap nodes mapped with the `MNODE_F_NO_MERGE'
 * flag, as well as read+write permissions. Additionally, if preparing the backing
 * page directory fails, as might happen if the associated node didn't have the
 * `MNODE_F_MPREPARED' flag set, then a warning is written to the system (unless
 * an internal rate-limit check fails), and the unmap operation is re-inserted as
 * a pending lock operation into `mman_kernel_lockops' (meaning that the unmap will
 * be re-attempted repeatedly until it (hopefully) succeeds at some point)
 * @param: is_zero: When true, allows the memory management system to assume that
 *                  the backing physical memory is zero-initialized. If you're not
 *                  sure if this is the case, better pass `false'. If you lie here,
 *                  calloc() might arbitrarily break... */
FUNDEF NOBLOCK void
NOTHROW(FCALL mman_unmap_kernel_ram)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
                                     PAGEDIR_PAGEALIGNED size_t num_bytes,
                                     __BOOL is_zero DFL(0));

/* Try to unmap kernel raw while the caller is holding a lock to the kernel mman.
 * @return: NULL: Successfully unmapped kernel ram.
 * @return: * :   Failed to prepare the underlying page directory.
 *                The returned value is a freshly initialized pending mman-
 *                lock-operation which the caller must enqueue for execution.
 *                (s.a. `mman_kernel_lockop()' and `mlockop_callback_t') */
FUNDEF WUNUSED NOBLOCK struct mlockop *
NOTHROW(FCALL mman_unmap_kernel_ram_locked)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
                                            PAGEDIR_PAGEALIGNED size_t num_bytes,
                                            __BOOL is_zero DFL(0));

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MM_MAP_H */
