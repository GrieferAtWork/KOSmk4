/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MPART_BLKST_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MPART_BLKST_H 1

#include <kernel/compiler.h>

#include <kernel/mman/mpart.h>

#include <hybrid/typecore.h>

/************************************************************************/
/* Helpers for operating with the block-status bitset found in `struct mpart' */
/************************************************************************/


/* Repeat a given block-status (one of `MPART_BLOCK_ST_*')
 * to fill a whole `mpart_blkst_word_t'. */
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
#elif __SIZEOF_POINTER__ == 4 && MPART_BLOCK_STBITS == 4
#define MPART_BLOCK_REPEAT(st) (__UINT32_C(0x11111111) * (st))
#elif __SIZEOF_POINTER__ == 8 && MPART_BLOCK_STBITS == 4
#define MPART_BLOCK_REPEAT(st) (__UINT64_C(0x1111111111111111) * (st))
#elif __SIZEOF_POINTER__ == 2 && MPART_BLOCK_STBITS == 4
#define MPART_BLOCK_REPEAT(st) (__UINT16_C(0x1111) * (st))
#elif __SIZEOF_POINTER__ == 1 && MPART_BLOCK_STBITS == 4
#define MPART_BLOCK_REPEAT(st) (__UINT8_C(0x11) * (st))
#elif __SIZEOF_POINTER__ == 4 && MPART_BLOCK_STBITS == 8
#define MPART_BLOCK_REPEAT(st) (__UINT32_C(0x01010101) * (st))
#elif __SIZEOF_POINTER__ == 8 && MPART_BLOCK_STBITS == 8
#define MPART_BLOCK_REPEAT(st) (__UINT64_C(0x0101010101010101) * (st))
#elif __SIZEOF_POINTER__ == 2 && MPART_BLOCK_STBITS == 8
#define MPART_BLOCK_REPEAT(st) (__UINT16_C(0x0101) * (st))
#elif __SIZEOF_POINTER__ == 1 && MPART_BLOCK_STBITS == 8
#define MPART_BLOCK_REPEAT(st) (__UINT8_C(0x01) * (st))
#else /* ... */
#error "Unsupported __SIZEOF_POINTER__ and/or MPART_BLOCK_STBITS"
#endif /* !... */

/* The word-type used by `struct mpart::mp_blkst_inl' (and `struct mpart::mp_blkst_ptr') */
#ifdef __INTELLISENSE__
typedef uintptr_t mpart_blkst_word_t;
#else /* __INTELLISENSE__ */
#define mpart_blkst_word_t uintptr_t
#endif /* !__INTELLISENSE__ */

/* The # of blocks per bitset word. */
#define MPART_BLKST_BLOCKS_PER_WORD \
	(BITSOF(mpart_blkst_word_t) / MPART_BLOCK_STBITS)

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MPART_BLKST_H */
