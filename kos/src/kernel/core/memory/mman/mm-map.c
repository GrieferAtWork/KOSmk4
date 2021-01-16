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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MM_MAP_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MM_MAP_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/mman.h>
#include <kernel/mman/mm-map.h>
#include <kernel/paging.h>

#include <kos/except.h>

#include <stdbool.h>

DECL_BEGIN

/* Map a given file into the specified mman.
 * @param: hint:          s.a. `mman_getunmapped_nx'
 * @param: prot:          Set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SHARED' (Other bits are silently ignored)
 * @param: flags:         Set of `MAP_LOCKED | MAP_POPULATE | MAP_NONBLOCK | MAP_PREPARED | MAP_FIXED_NOREPLACE' (Other bits are silently ignored)
 *                        Additionally, the following flags may be set to customize the behavior of how
 *                        a suitable address is located (s.a. `mman_getunmapped_nx()' for more info):
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
 * @param: min_alignment: s.a. `mman_getunmapped_nx'
 * @return: * : The effective mapping base at which `file->DATA.BYTES[file_pos]' can be found,
 *              unless `num_bytes' was given as `0', in which case the return value is undefined,
 *              but arguably valid (e.g. will be a user-/kernel-space location as it would have
 *              been when `num_bytes' was non-zero). */
PUBLIC NONNULL((1, 6)) void *KCALL
mman_map(struct mman *__restrict self,
         UNCHECKED void *hint, size_t num_bytes,
         unsigned int prot, unsigned int flags,
         struct mfile *__restrict file,
         struct path *file_fspath,
         struct directory_entry *file_fsname,
         pos_t file_pos, size_t min_alignment)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS) {
	/* TODO */
	THROW(E_NOT_IMPLEMENTED_TODO);
}



/* Same as `mman_map()', but only allow pages entirely contained within
 * the file-relative address range `file_map_minaddr...file_map_maxaddr'
 * to be mapped. Attempting to map file contents beyond this range will
 * instead result in `&mfile_zero' getting mapped instead.
 * This function is mainly used to restrict access to raw physical memory
 * when user-space is allowed to directly mmap() device ram, but the driver
 * want's to prevent user-space from mapping more than the physical address
 * ranges actually associated with a device. */
PUBLIC NONNULL((1, 6)) void *KCALL
mman_map_subrange(struct mman *__restrict self,
                  UNCHECKED void *hint, size_t num_bytes,
                  unsigned int prot, unsigned int flags,
                  struct mfile *__restrict file,
                  struct path *file_fspath,
                  struct directory_entry *file_fsname,
                  pos_t file_pos,
                  pos_t file_map_minaddr,
                  pos_t file_map_maxaddr,
                  size_t min_alignment)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS) {
	/* TODO */
	THROW(E_NOT_IMPLEMENTED_TODO);
}



/* Same as `mman_map()', but instead of actually mapping something, leave the
 * address range as empty (but possibly prepared), making it a reserved address range.
 * @param: flags: Set of `MAP_PREPARED | MAP_FIXED_NOREPLACE' (Other bits are silently ignored)
 *                Additionally, the usual bits relating to `mman_getunmapped_nx()' are accepted:
 *                `MAP_FIXED | MAP_32BIT | MAP_GROWSDOWN | MAP_GROWSUP | MAP_STACK | MAP_FIXED_NOREPLACE' */
PUBLIC NONNULL((1)) void *KCALL
mman_map_res(struct mman *__restrict self,
             UNCHECKED void *hint, size_t num_bytes,
             unsigned int flags,
             size_t min_alignment)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS) {
	/* TODO */
	THROW(E_NOT_IMPLEMENTED_TODO);
}



/* Unmap all memory mappings within the given address range.
 * The actual range is widened to include all whole pages that overlap the given range.
 * @param: addr:      The base address at which to start unmapping memory.
 * @param: num_bytes: The # of continuous bytes of memory to unmap, starting at `addr'
 * @param: flags:     Set of `MMAN_UNMAP_*'
 * @return: * :       The actual # of unmapped bytes of memory. */
PUBLIC NONNULL((1)) size_t KCALL
mman_unmap(struct mman *__restrict self,
           UNCHECKED void *addr, size_t num_bytes,
           unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT) {
	/* TODO */
	THROW(E_NOT_IMPLEMENTED_TODO);
}



/* Update access protection flags within the given address range.
 * @param: addr:       The base address at which to start changing protection.
 * @param: num_bytes:  The number of continuous bytes of memory to change, starting at `addr'
 * @param: prot_mask:  Mask of protection bits that should be kept (Set of `PROT_EXEC | PROT_WRITE | PROT_READ').
 * @param: prot_flags: Set of protection bits that should be added (Set of `PROT_EXEC | PROT_WRITE | PROT_READ').
 * @param: flags:      Set of `MMAN_UNMAP_*'
 * @return: * :        The actual # of (possibly) altered bytes of memory. */
PUBLIC NONNULL((1)) size_t KCALL
mman_protect(struct mman *__restrict self,
             UNCHECKED void *addr, size_t num_bytes,
             unsigned int prot_mask, unsigned int prot_flags,
             unsigned int how)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT) {
	/* TODO */
	THROW(E_NOT_IMPLEMENTED_TODO);
}



/* Sync all changes made to file mappings within the given
 * address range with on-disk file images. (s.a. `mfile_sync()')
 * NOTE: Memory ranges that aren't actually mapped, aren't mapped
 *       with WRITE and SHARED, or aren't mapped to write-back files
 *       are simply ignored. */
PUBLIC void FCALL
mman_syncmem(struct mman *__restrict self,
             PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
             PAGEDIR_PAGEALIGNED size_t num_bytes)
		THROWS(E_WOULDBLOCK, ...) {
	/* TODO */
	THROW(E_NOT_IMPLEMENTED_TODO);
}



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
PUBLIC NOBLOCK_IF(gfp & GFP_ATOMIC) PAGEDIR_PAGEALIGNED void *FCALL
mmap_map_kernel_ram(PAGEDIR_PAGEALIGNED void *hint,
                    PAGEDIR_PAGEALIGNED size_t num_bytes,
                    gfp_t gfp, size_t min_alignment) {
	/* TODO */
	THROW(E_NOT_IMPLEMENTED_TODO);
}



/* Non-throwing version of `mmap_map_kernel_ram()'.
 * returns `MMAP_MAP_KERNEL_RAM_NX_ERROR' on error. */
PUBLIC NOBLOCK_IF(gfp & GFP_ATOMIC) PAGEDIR_PAGEALIGNED void *
NOTHROW(FCALL mmap_map_kernel_ram_nx)(PAGEDIR_PAGEALIGNED void *hint,
                                      PAGEDIR_PAGEALIGNED size_t num_bytes,
                                      gfp_t gfp, size_t min_alignment) {
	/* TODO */
	return MMAP_MAP_KERNEL_RAM_NX_ERROR;
}

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
PUBLIC NOBLOCK void
NOTHROW(FCALL mman_unmap_kernel_ram)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
                                     PAGEDIR_PAGEALIGNED size_t num_bytes,
                                     bool is_zero) {
	/* TODO */
}

/* Try to unmap kernel raw while the caller is holding a lock to the kernel mman.
 * @return: true:  Successfully unmapped kernel ram.
 * @return: false: Failed to prepare the underlying page directory. In
 *                 this case, the ram mapping will not have been deleted. */
PUBLIC NOBLOCK bool
NOTHROW(FCALL mman_unmap_kernel_ram_locked)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
                                            PAGEDIR_PAGEALIGNED size_t num_bytes,
                                            bool is_zero) {
	/* TODO */
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MM_MAP_C */
