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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MM_KRAM_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MM_KRAM_H 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/types.h>

#include <hybrid/host.h> /* __ARCH_STACK_GROWS_DOWNWARDS */

#include <asm/os/mman.h> /* __MAP_FAILED */

#ifdef __CC__
DECL_BEGIN

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
#define GFP_MAP_BELOW        0x0100 /* s.a. `MAP_GROWSDOWN' */
#define GFP_MAP_ABOVE        0x0200 /* s.a. `MAP_GROWSUP' */
#define GFP_MAP_NOASLR   0x40000000 /* s.a. `MAP_NOASLR' */


/* @param: gfp: Set of:
 *   - GFP_LOCKED:       Normal behavior
 *   - GFP_PREFLT:       Prefault everything
 *   - GFP_CALLOC:       Allocate from `mfile_zero' instead of `mfile_ndef'
 *   - GFP_ATOMIC:       Don't block when waiting to acquire any sort of lock.
 *   - GFP_NOMMAP:       Unconditionally throw `E_WOULDBLOCK_PREEMPTED'
 *   - GFP_VCBASE:       Allocate the mnode and mpart using `mcoreheap_alloc_locked_nx()'.
 *                       This also causes the `MNODE_F_COREPART' / `MPART_F_COREPART'
 *                       flags to be set for each resp. This flag is used internally
 *                       to resolve the dependency loop between this function needing
 *                       to call kmalloc() and kmalloc() needing to call this function.
 *   - GFP_MAP_32BIT:    Allocate 32-bit physical memory addresses. This flag
 *                       must be combined with `MAP_POPULATE', and should also
 *                       be combined with `GFP_LOCKED' to prevent the backing
 *                       physical memory from being altered.
 *   - GFP_MAP_PREPARED: Ensure that all mapped pages are prepared, and left as such
 *   - GFP_MAP_BELOW:    s.a. `MAP_GROWSDOWN'
 *   - GFP_MAP_ABOVE:    s.a. `MAP_GROWSUP'
 *   - GFP_MAP_NOASLR:   s.a. `MAP_NOASLR'
 *   - GFP_NOCLRC:       Don't call `system_clearcaches()' to try to free up memory
 *   - GFP_NOSWAP:       Don't move memory to swap to free up memory
 *   - Other flags are silently ignored, but will be forwarded onto
 *     other calls to kmalloc() that may need to be made internally. */
FUNDEF NOBLOCK_IF(gfp & GFP_ATOMIC) PAGEDIR_PAGEALIGNED void *FCALL
mmap_map_kernel_ram(PAGEDIR_PAGEALIGNED void *hint,
                    PAGEDIR_PAGEALIGNED size_t num_bytes,
                    gfp_t gfp, size_t min_alignment DFL(PAGESIZE));
/* Non-throwing version of `mmap_map_kernel_ram()'. Returns `MAP_FAILED' on error. */
FUNDEF NOBLOCK_IF(gfp & GFP_ATOMIC) PAGEDIR_PAGEALIGNED void *
NOTHROW(FCALL mmap_map_kernel_ram_nx)(PAGEDIR_PAGEALIGNED void *hint,
                                      PAGEDIR_PAGEALIGNED size_t num_bytes,
                                      gfp_t gfp, size_t min_alignment DFL(PAGESIZE));

/* Error return value for `mmap_map_kernel_ram_nx()' */
#if !defined(MAP_FAILED) && defined(__MAP_FAILED)
#define MAP_FAILED __MAP_FAILED
#endif /* !MAP_FAILED && __MAP_FAILED */


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
 * @param: flags:   Set of `GFP_*'. When `GFP_CALLOC' is given, allows the memory
 *                  management system to assume that the backing physical memory
 *                  is zero-initialized. If you're not sure if this is the case,
 *                  better pass `false'. If you lie here, calloc() might arbitrarily
 *                  break...
 *                  Must always contain at least `GFP_ATOMIC' */
FUNDEF NOBLOCK void
NOTHROW(FCALL mman_unmap_kernel_ram)(PAGEDIR_PAGEALIGNED void *addr,
                                     PAGEDIR_PAGEALIGNED size_t num_bytes,
                                     gfp_t flags DFL(0x0400 /*GFP_ATOMIC*/));

/* Try to unmap kernel raw while the caller is holding a lock to the kernel mman.
 * @param: flags: Set of `GFP_*' (Must always contain at least `GFP_ATOMIC')
 * @return: NULL: Successfully unmapped kernel ram.
 * @return: * :   Failed to allocate needed memory.
 *                The returned value is a freshly initialized pending mman-
 *                lock-operation which the caller must enqueue for execution.
 *                (s.a. `mman_kernel_lockop()' and `mlockop_callback_t') */
FUNDEF WUNUSED NOBLOCK struct mlockop *
NOTHROW(FCALL mman_unmap_kernel_ram_locked)(PAGEDIR_PAGEALIGNED void *addr,
                                            PAGEDIR_PAGEALIGNED size_t num_bytes,
                                            gfp_t flags DFL(0x0400 /*GFP_ATOMIC*/));

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MM_KRAM_H */
