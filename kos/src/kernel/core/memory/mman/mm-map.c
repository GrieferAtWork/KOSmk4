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

#include <kernel/mman/mfile.h>
#include <kernel/mman/mm-map.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>

#include <kos/except.h>

#include <assert.h>
#include <stdbool.h>
#include <string.h>

DECL_BEGIN

#if __SIZEOF_POINTER__ == 4 && MPART_BLOCK_STBITS == 2
#define MPART_BLOCK_REPEAT(st) (__UINT32_C(0x55555555) * (st))
#elif __SIZEOF_POINTER__ == 8 && MPART_BLOCK_STBITS == 2
#define MPART_BLOCK_REPEAT(st) (__UINT64_C(0x5555555555555555) * (st))
#elif __SIZEOF_POINTER__ == 2 && MPART_BLOCK_STBITS == 2
#define MPART_BLOCK_REPEAT(st) (__UINT16_C(0x5555) * (st))
#elif __SIZEOF_POINTER__ == 1 && MPART_BLOCK_STBITS == 2
#define MPART_BLOCK_REPEAT(st) (__UINT8_C(0x55) * (st))
#elif __SIZEOF_POINTER__ == 4 && MPART_BLOCK_STBITS == 1
#define MPART_BLOCK_REPEAT(st) (__UINT32_C(0xffffffff) * (st))
#elif __SIZEOF_POINTER__ == 8 && MPART_BLOCK_STBITS == 1
#define MPART_BLOCK_REPEAT(st) (__UINT64_C(0xffffffffffffffff) * (st))
#elif __SIZEOF_POINTER__ == 2 && MPART_BLOCK_STBITS == 1
#define MPART_BLOCK_REPEAT(st) (__UINT16_C(0xffff) * (st))
#elif __SIZEOF_POINTER__ == 1 && MPART_BLOCK_STBITS == 1
#define MPART_BLOCK_REPEAT(st) (__UINT8_C(0xff) * (st))
#else
#error "Unsupported __SIZEOF_POINTER__ and/or MPART_BLOCK_STBITS"
#endif

#ifndef NDEBUG
#define DBG_memset(dst, byte, num_bytes) memset(dst, byte, num_bytes)
#else /* !NDEBUG */
#define DBG_memset(dst, byte, num_bytes) (void)0
#endif /* NDEBUG */

#ifdef __INTELLISENSE__
typedef typeof(((struct mpart *)0)->mp_blkst_inl) bitset_word_t;
#else /* __INTELLISENSE__ */
#define bitset_word_t typeof(((struct mpart *)0)->mp_blkst_inl)
#endif /* !__INTELLISENSE__ */
#define BITSET_ITEMS_PER_WORD (BITSOF(bitset_word_t) / MPART_BLOCK_STBITS)


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


DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_mman_map
#include "mm-map.c.inl"
#define DEFINE_mman_map_subrange
#include "mm-map.c.inl"
#define DEFINE_mman_map_res
#include "mm-map.c.inl"
#endif /* !__INTELLISENSE__ */


#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MM_MAP_C */
