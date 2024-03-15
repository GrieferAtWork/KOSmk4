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
#ifndef __GUARD_HYBRID_BITSET_H
#define __GUARD_HYBRID_BITSET_H 1

#include "__bitset.h"

#ifdef __CC__
__DECL_BEGIN

#define _BITSET_WORD_BMAX       __HYBRID_BITSET_WORD_BMAX        /* 0xff:  bitset_t-word with all bits set */
#define _BITSET_WORD_BITS       __HYBRID_BITSET_WORD_BITS        /* 8:     # of bits in a bitset_t-word */
#define _BITSET_WORD_BMSK       __HYBRID_BITSET_WORD_BMSK        /* 7:     # of bits in a bitset_t-word minus 1 */
#define _BITSET_WORD_SHFT       __HYBRID_BITSET_WORD_SHFT        /* 3:     log2(_BITSET_BITS) */
#define _BITSET_BYTE(bitno)     __HYBRID_BITSET_BYTE(bitno)      /* Index of `bitno' in `bitset_t[]' */
#define _BITSET_MASK(bitno)     __HYBRID_BITSET_MASK(bitno)      /* Mask for `bitno' in `bitset_t[]' */
#define BITSET_LENGTHOF(n_bits) __HYBRID_BITSET_LENGTHOF(n_bits) /* Length of `bitset_t[]' for `n_bits' bits */
#define BITSET_SIZEOF(n_bits)   __HYBRID_BITSET_SIZEOF(n_bits)   /* Size (in bytes) of `bitset_t[]' for `n_bits' bits */

/* >> bitset_t bitset_decl(self, 256); */
#define bitset_decl(self, nbits) __hybrid_bitset_decl(self, nbits)


#ifdef __INTELLISENSE__
/* >> bitset_t bitset_decl(bitset, 42);
 * >> bitset_clearall(bitset, 42);
 * >> ... */
typedef __hybrid_bitset_t bitset_t;

/* Check if a given "bitset" is set. */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL bitset_test(bitset_t const *self, __SIZE_TYPE__ bitno);

/* Change the state of a single "bitno". */
__ATTR_NONNULL((1)) void bitset_set(bitset_t *self, __SIZE_TYPE__ bitno);
__ATTR_NONNULL((1)) void bitset_clear(bitset_t *self, __SIZE_TYPE__ bitno);
__ATTR_NONNULL((1)) void bitset_flip(bitset_t *self, __SIZE_TYPE__ bitno);

/* Change the state of the first "n_bits". */
__ATTR_NONNULL((1)) void bitset_setall(bitset_t *self, __SIZE_TYPE__ n_bits);
__ATTR_NONNULL((1)) void bitset_clearall(bitset_t *self, __SIZE_TYPE__ n_bits);
__ATTR_NONNULL((1)) void bitset_flipall(bitset_t *self, __SIZE_TYPE__ n_bits);

/* Turn off bits [minbitno, maxbitno] (inclusive) in `self'
 * NOTE: When  `minbitno > maxbitno', the result  is weak undefined behavior,
 *       in that the way in which `self' is modified is undefined, though the
 *       function still guaranties that nothing but `self' gets modified. */
__ATTR_NONNULL((1)) void bitset_nclear(bitset_t *self, __SIZE_TYPE__ minbitno, __SIZE_TYPE__ maxbitno);

/* Turn on bits [minbitno, maxbitno] (inclusive) in `self'
 * NOTE: When  `minbitno > maxbitno', the result  is weak undefined behavior,
 *       in that the way in which `self' is modified is undefined, though the
 *       function still guaranties that nothing but `self' gets modified. */
__ATTR_NONNULL((1)) void bitset_nset(bitset_t *self, __SIZE_TYPE__ minbitno, __SIZE_TYPE__ maxbitno);

/* Find the  first bitno  within [0,  n_bits) that  is off  and store  its
 * index in `*p_value'. If no such bit exists, write `-1' into `*p_value'. */
__ATTR_PURE __ATTR_NONNULL((1)) void bitset_ffc_i(bitset_t const *self, __SIZE_TYPE__ n_bits, __SSIZE_TYPE__ *p_value);

/* Find the  first bitno  within [0,  n_bits)  that is  on and  store  its
 * index in `*p_value'. If no such bit exists, write `-1' into `*p_value'. */
__ATTR_PURE __ATTR_NONNULL((1)) void bitset_ffs_i(bitset_t const *self, __SIZE_TYPE__ n_bits, __SSIZE_TYPE__ *p_value);

/* Find the first bitno within [0,  n_bits) that is off and  return
 * its index. If no such bit exists, return some value `>= n_bits'. */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ bitset_ffc(bitset_t const *self, __SIZE_TYPE__ n_bits);

/* Find  the first bitno  within [0, n_bits) that  is on and return
 * its index. If no such bit exists, return some value `>= n_bits'. */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ bitset_ffs(bitset_t const *self, __SIZE_TYPE__ n_bits);

/* Check if the bitset contains any 1-elements */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL bitset_anyset(bitset_t const *self, __SIZE_TYPE__ n_bits);

/* Check if the bitset contains only 1-elements */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL bitset_allset(bitset_t const *self, __SIZE_TYPE__ n_bits);

/* Check if the bitset contains any 1-elements within the given range */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL bitset_nanyset(bitset_t const *self, __SIZE_TYPE__ minbitno, __SIZE_TYPE__ maxbitno);

/* Check if the bitset contains only 1-elements within the given range */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL bitset_nallset(bitset_t const *self, __SIZE_TYPE__ minbitno, __SIZE_TYPE__ maxbitno);

/* Returns the # of 1-bits in `self' */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ bitset_popcount(bitset_t const *__restrict self, __SIZE_TYPE__ n_bits);

/* Returns the # of 1-bits within the given range */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ bitset_npopcount(bitset_t const *self, __SIZE_TYPE__ minbitno, __SIZE_TYPE__ maxbitno);

/* Count-leading-zeroes (undefined when `self' doesn't contain any set bits) */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ bitset_clz(bitset_t const *__restrict self);

/* Count-trailing-zeroes (undefined when `self' doesn't contain any set bits) */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ bitset_ctz(bitset_t const *__restrict self, __SIZE_TYPE__ n_bits);
#else /* __INTELLISENSE__ */
#define bitset_t                                   __hybrid_bitset_t
#define bitset_test(self, bitno)                   __hybrid_bitset_test(self, bitno)
#define bitset_set(self, bitno)                    __hybrid_bitset_set(self, bitno)
#define bitset_clear(self, bitno)                  __hybrid_bitset_clear(self, bitno)
#define bitset_flip(self, bitno)                   __hybrid_bitset_flip(self, bitno)
#define bitset_setall(self, n_bits)                __hybrid_bitset_setall(self, n_bits)
#define bitset_clearall(self, n_bits)              __hybrid_bitset_clearall(self, n_bits)
#define bitset_flipall(self, n_bits)               __hybrid_bitset_flipall(self, n_bits)
#define bitset_nclear(self, minbitno, maxbitno)    __hybrid_bitset_nclear(self, minbitno, maxbitno)
#define bitset_nset(self, minbitno, maxbitno)      __hybrid_bitset_nset(self, minbitno, maxbitno)
#define bitset_ffc_i(self, n_bits, p_value)        __hybrid_bitset_ffc_i(self, n_bits, p_value)
#define bitset_ffs_i(self, n_bits, p_value)        __hybrid_bitset_ffs_i(self, n_bits, p_value)
#define bitset_ffc(self, n_bits)                   __hybrid_bitset_ffc(self, n_bits)
#define bitset_ffs(self, n_bits)                   __hybrid_bitset_ffs(self, n_bits)
#define bitset_anyset(self, n_bits)                __hybrid_bitset_anyset(self, n_bits)
#define bitset_allset(self, n_bits)                __hybrid_bitset_allset(self, n_bits)
#define bitset_nanyset(self, minbitno, maxbitno)   __hybrid_bitset_nanyset(self, minbitno, maxbitno)
#define bitset_nallset(self, minbitno, maxbitno)   __hybrid_bitset_nallset(self, minbitno, maxbitno)
#define bitset_popcount(self, n_bits)              __hybrid_bitset_popcount(self, n_bits)
#define bitset_npopcount(self, minbitno, maxbitno) __hybrid_bitset_npopcount(self, minbitno, maxbitno)
#define bitset_clz(self)                           __hybrid_bitset_clz(self)
#define bitset_ctz(self, n_bits)                   __hybrid_bitset_ctz(self, n_bits)
#endif /* !__INTELLISENSE__ */

/* >> size_t bitno;
 * >> bitset_t bitset[_BITSET_LENGTHOF(42)];
 * >> ...
 * >> bitset_foreach (bitno, bitset, 42) {
 * >>     printf("bit is on: %Iu\n", bitno);
 * >> } */
#define bitset_foreach(bitno, self, n_bits) \
	__hybrid_bitset_foreach(bitno, self, n_bits)

__DECL_END
#endif /* __CC__ */

#endif /* !__GUARD_HYBRID_BITSET_H */
