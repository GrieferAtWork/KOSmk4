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
#define _BITSET_WORD(bitno)     __HYBRID_BITSET_WORD(bitno)      /* Index of `bitno' in `bitset_t[]' */
#define _BITSET_MASK(bitno)     __HYBRID_BITSET_MASK(bitno)      /* Mask for `bitno' in `bitset_t[]' */
#define BITSET_LENGTHOF(n_bits) __HYBRID_BITSET_LENGTHOF(n_bits) /* Length of `bitset_t[]' for `n_bits' bits */
#define BITSET_SIZEOF(n_bits)   __HYBRID_BITSET_SIZEOF(n_bits)   /* Size (in bytes) of `bitset_t[]' for `n_bits' bits */


/* >> _BITSET_LO_MASKIN(0) == 0xb00000000
 * >> _BITSET_LO_MASKIN(1) == 0xb00000001
 * >> _BITSET_LO_MASKIN(2) == 0xb00000011
 * >> _BITSET_LO_MASKIN(6) == 0xb00111111
 * >> _BITSET_LO_MASKIN(7) == 0xb01111111
 * >> _BITSET_LO_MASKIN(8) == 0xb11111111 // requires use of _BITSET_LO_MASKIN_P1
 *
 * >> _BITSET_LO_MASKOU(0) == 0xb11111111
 * >> _BITSET_LO_MASKOU(1) == 0xb11111110
 * >> _BITSET_LO_MASKOU(2) == 0xb11111100
 * >> _BITSET_LO_MASKOU(6) == 0xb11000000
 * >> _BITSET_LO_MASKOU(7) == 0xb10000000
 * >> _BITSET_LO_MASKOU(8) == 0xb00000000 // requires use of _BITSET_LO_MASKOU_P1
 *
 * >> _BITSET_HI_MASKIN(0) == 0xb00000000
 * >> _BITSET_HI_MASKIN(1) == 0xb10000000
 * >> _BITSET_HI_MASKIN(2) == 0xb11000000
 * >> _BITSET_HI_MASKIN(6) == 0xb11111100
 * >> _BITSET_HI_MASKIN(7) == 0xb11111110
 * >> _BITSET_HI_MASKIN(8) == 0xb11111111 // requires use of _BITSET_HI_MASKIN_P1
 *
 * >> _BITSET_HI_MASKOU(0) == 0xb11111111
 * >> _BITSET_HI_MASKOU(1) == 0xb01111111
 * >> _BITSET_HI_MASKOU(2) == 0xb00111111
 * >> _BITSET_HI_MASKOU(6) == 0xb00000011
 * >> _BITSET_HI_MASKOU(7) == 0xb00000001
 * >> _BITSET_HI_MASKOU(8) == 0xb00000000 // requires use of _BITSET_HI_MASKOU_P1
 *
 * NOTE: When "n >= 8", behavior is HARD undefined. If you
 *       need  to  value of  `_BITSET_*_MASK*(n + 1)', the
 *       `*_P1' variant must be used.
 */
#define _BITSET_LO_MASKIN(n)    __HYBRID_BITSET_LO_MASKIN(n)
#define _BITSET_LO_MASKOU(n)    __HYBRID_BITSET_LO_MASKOU(n)
#define _BITSET_HI_MASKIN(n)    __HYBRID_BITSET_HI_MASKIN(n)
#define _BITSET_HI_MASKOU(n)    __HYBRID_BITSET_HI_MASKOU(n)
#define _BITSET_LO_MASKIN_P1(n) __HYBRID_BITSET_LO_MASKIN_P1(n)
#define _BITSET_LO_MASKOU_P1(n) __HYBRID_BITSET_LO_MASKOU_P1(n)
#define _BITSET_HI_MASKIN_P1(n) __HYBRID_BITSET_HI_MASKIN_P1(n)
#define _BITSET_HI_MASKOU_P1(n) __HYBRID_BITSET_HI_MASKOU_P1(n)


/* >> bitset_t(3H)
 * Example:
 * >> bitset_t bitset_decl(self, 256); */
#define bitset_decl(self, nbits) __hybrid_bitset_decl(self, nbits)


#ifdef __INTELLISENSE__
/* >> bitset_t(3H)
 * Example:
 * >> bitset_t bitset_decl(bitset, 42);
 * >> bitset_clearall(bitset, 42);
 * >> ... */
typedef __hybrid_bitset_t bitset_t;

/* >> bitset_test(3H)
 * Check if a given "bitset" is set. */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL bitset_test(bitset_t const *__restrict self, __SIZE_TYPE__ bitno);

/* >> bitset_set(3H), bitset_clear(3H), bitset_flip(3H)
 * Change the state of a single "bitno". */
__ATTR_NONNULL((1)) void bitset_set(bitset_t *__restrict self, __SIZE_TYPE__ bitno);
__ATTR_NONNULL((1)) void bitset_clear(bitset_t *__restrict self, __SIZE_TYPE__ bitno);
__ATTR_NONNULL((1)) void bitset_flip(bitset_t *__restrict self, __SIZE_TYPE__ bitno);

/* >> bitset_setall(3H), bitset_clearall(3H), bitset_flipall(3H)
 * Change the state of the first "n_bits". */
__ATTR_NONNULL((1)) void bitset_setall(bitset_t *__restrict self, __SIZE_TYPE__ n_bits);
__ATTR_NONNULL((1)) void bitset_clearall(bitset_t *__restrict self, __SIZE_TYPE__ n_bits);
__ATTR_NONNULL((1)) void bitset_flipall(bitset_t *__restrict self, __SIZE_TYPE__ n_bits);

/* >> bitset_nclear(3H)
 * Turn off bits [startbitno, endbitno) (non-inclusive) in `self'
 * NOTE: When `startbitno > endbitno', the result is weak undefined behavior,
 *       in that the way in which `self' is modified is undefined, though the
 *       function still guaranties that nothing but `self' gets modified. */
__ATTR_NONNULL((1)) void bitset_nclear(bitset_t *__restrict self, __SIZE_TYPE__ startbitno, __SIZE_TYPE__ endbitno);

/* >> bitset_nset(3H)
 * Turn on bits [startbitno, endbitno) (non-inclusive) in `self'
 * NOTE: When `startbitno > endbitno', the result is weak undefined behavior,
 *       in that the way in which `self' is modified is undefined, though the
 *       function still guaranties that nothing but `self' gets modified. */
__ATTR_NONNULL((1)) void bitset_nset(bitset_t *__restrict self, __SIZE_TYPE__ startbitno, __SIZE_TYPE__ endbitno);

/* >> bitset_nflip(3H)
 * Flip bits [startbitno, endbitno) (non-inclusive) in `self'
 * NOTE: When `startbitno > endbitno', the result is weak undefined behavior,
 *       in that the way in which `self' is modified is undefined, though the
 *       function still guaranties that nothing but `self' gets modified. */
__ATTR_NONNULL((1)) void bitset_nflip(bitset_t *__restrict self, __SIZE_TYPE__ startbitno, __SIZE_TYPE__ endbitno);

/* >> bitset_ffc_i(3H)
 * Find the  first bitno  within [0,  n_bits) that  is off  and store  its
 * index in `*p_value'. If no such bit exists, write `-1' into `*p_value'. */
__ATTR_NONNULL((1)) void bitset_ffc_i(bitset_t const *__restrict self, __SIZE_TYPE__ n_bits, __SSIZE_TYPE__ *p_value);

/* >> bitset_ffs_i(3H)
 * Find the  first bitno  within [0,  n_bits)  that is  on and  store  its
 * index in `*p_value'. If no such bit exists, write `-1' into `*p_value'. */
__ATTR_NONNULL((1)) void bitset_ffs_i(bitset_t const *__restrict self, __SIZE_TYPE__ n_bits, __SSIZE_TYPE__ *p_value);

/* >> bitset_ffc(3H)
 * Find the first bitno within [0,  n_bits) that is off and  return
 * its index. If no such bit exists, return some value `>= n_bits'. */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ bitset_ffc(bitset_t const *__restrict self, __SIZE_TYPE__ n_bits);

/* >> bitset_ffs(3H)
 * Find  the first bitno  within [0, n_bits) that  is on and return
 * its index. If no such bit exists, return some value `>= n_bits'. */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ bitset_ffs(bitset_t const *__restrict self, __SIZE_TYPE__ n_bits);

/* >> bitset_flc(3H)
 * Find  the last bitno  within [0, n_bits) that  is off and return
 * its index. If no such bit exists, return some value `>= n_bits'. */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ bitset_flc(bitset_t const *__restrict self, __SIZE_TYPE__ n_bits);

/* >> bitset_fls(3H)
 * Find  the last  bitno within [0,  n_bits) that is  on and return
 * its index. If no such bit exists, return some value `>= n_bits'. */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ bitset_fls(bitset_t const *__restrict self, __SIZE_TYPE__ n_bits);

/* >> bitset_nffs(3H)
 * Find the first bitno within [startbitno,endbitno) that is on and return
 * its index.  If no  such bit  exists, return  some value  `>= endbitno'. */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ bitset_nffs(bitset_t const *__restrict self, __SIZE_TYPE__ startbitno, __SIZE_TYPE__ endbitno);

/* >> bitset_nffc(3H)
 * Find the first bitno within [startbitno,endbitno) that is off and return
 * its  index.  If no  such bit  exists,  return some  value `>= endbitno'. */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ bitset_nffc(bitset_t const *__restrict self, __SIZE_TYPE__ startbitno, __SIZE_TYPE__ endbitno);

/* >> bitset_nfls(3H)
 * Find the last bitno within [startbitno,endbitno) that is on and return
 * its index. If  no such  bit exists, return  some value  `>= endbitno'. */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ bitset_nfls(bitset_t const *__restrict self, __SIZE_TYPE__ startbitno, __SIZE_TYPE__ endbitno);

/* >> bitset_nflc(3H)
 * Find the last bitno within [startbitno,endbitno) that is off and return
 * its index.  If no  such bit  exists, return  some value  `>= endbitno'. */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ bitset_nflc(bitset_t const *__restrict self, __SIZE_TYPE__ startbitno, __SIZE_TYPE__ endbitno);

/* >> bitset_anyset(3H)
 * Check if the bitset contains any 1-elements */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL bitset_anyset(bitset_t const *__restrict self, __SIZE_TYPE__ n_bits);

/* >> bitset_allset(3H)
 * Check if the bitset contains only 1-elements */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL bitset_allset(bitset_t const *__restrict self, __SIZE_TYPE__ n_bits);

/* >> bitset_nanyset(3H)
 * Check if the bitset contains any 1-elements within the given range */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL bitset_nanyset(bitset_t const *__restrict self, __SIZE_TYPE__ startbitno, __SIZE_TYPE__ endbitno);

/* >> bitset_nallset(3H)
 * Check if the bitset contains only 1-elements within the given range */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL bitset_nallset(bitset_t const *__restrict self, __SIZE_TYPE__ startbitno, __SIZE_TYPE__ endbitno);

/* >> bitset_popcount(3H)
 * Returns the # of 1-bits in `self' */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ bitset_popcount(bitset_t const *__restrict self, __SIZE_TYPE__ n_bits);

/* >> bitset_npopcount(3H)
 * Returns the # of 1-bits within the given range */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ bitset_npopcount(bitset_t const *__restrict self, __SIZE_TYPE__ startbitno, __SIZE_TYPE__ endbitno);

/* >> bitset_clz(3H)
 * Count-leading-zeroes (returns ">= n_bits" when `self' doesn't contain any set bits) */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ bitset_clz(bitset_t const *__restrict self, __SIZE_TYPE__ n_bits);

/* >> bitset_ctz(3H)
 * Count-trailing-zeroes (returns ">= n_bits" when `self' doesn't contain any set bits) */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ bitset_ctz(bitset_t const *__restrict self, __SIZE_TYPE__ n_bits);

/* >> bitset_rawclz(3H)
 * Count-leading-zeroes (hard undefined behavior when `self' doesn't contain any set bits) */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ bitset_rawclz(bitset_t const *__restrict self, __SIZE_TYPE__ n_bits);

/* >> bitset_rawctz(3H)
 * Count-trailing-zeroes (hard undefined behavior when `self' doesn't contain any set bits) */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ bitset_rawctz(bitset_t const *__restrict self);

/* >> bitset_ncopy(3H)
 * Take "n_bits" from "src:src_startbitno" and store them to "dst:dst_startbitno".
 * NOTE: Overlap is allowed! */
__ATTR_NONNULL((1, 3)) void
bitset_ncopy(bitset_t *dst, __SIZE_TYPE__ dst_startbitno,
             bitset_t const *src, __SIZE_TYPE__ src_startbitno,
             __SIZE_TYPE__ n_bits);
__ATTR_NONNULL((1, 2)) void
bitset_ncopy0(bitset_t *dst, bitset_t const *src,
              __SIZE_TYPE__ src_startbitno, __SIZE_TYPE__ n_bits);

/* Possible values for `bitset_nbitop::op' */
#define BITSET_OP_AND __HYBRID_BITSET_OP_AND
#define BITSET_OP_OR  __HYBRID_BITSET_OP_OR
#define BITSET_OP_XOR __HYBRID_BITSET_OP_XOR

/* >> bitset_nbitop(3H)
 * Perform  a  bit-operation  "op"  on  the  "n_bits"  from  "src:src_startbitno",
 * together with "dst:dst_startbitno", storing the result at "dst:dst_startbitno".
 * NOTE: Overlap is allowed!
 * @param: op: One of `BITSET_OP_*' */
__ATTR_NONNULL((1, 3)) void
bitset_nbitop(bitset_t *dst, __SIZE_TYPE__ dst_startbitno,
              bitset_t const *src, __SIZE_TYPE__ src_startbitno,
              __SIZE_TYPE__ n_bits, unsigned int op);
__ATTR_NONNULL((1, 2)) void
bitset_nbitop0(bitset_t *dst, bitset_t const *src,
               __SIZE_TYPE__ src_startbitno,
               __SIZE_TYPE__ n_bits, unsigned int op);

/* >> bitset_ncmpeq(3H)
 * Check if "n_bits" at "lhs:lhs_startbitno" and "rhs:rhs_startbitno" are equal. */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __BOOL
bitset_ncmpeq(bitset_t const *lhs, __SIZE_TYPE__ lhs_startbitno,
              bitset_t const *rhs, __SIZE_TYPE__ rhs_startbitno,
              __SIZE_TYPE__ n_bits);

/* >> bitset_ncmple(3H)
 * Check if all 1-bits from `lhs:lhs_startbitno...+=n_bits' also appear in `rhs:rhs_startbitno...+=n_bits'.
 * This function implements the a is-subset-or-equal check. */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __BOOL
bitset_ncmple(bitset_t const *lhs, __SIZE_TYPE__ lhs_startbitno,
              bitset_t const *rhs, __SIZE_TYPE__ rhs_startbitno,
              __SIZE_TYPE__ n_bits);

/* >> bitset_ncmpne(3H), bitset_ncmpge(3H), bitset_ncmplo(3H), bitset_ncmpgr(3H)
 * All of the other compare operator.
 * @see bitset_ncmpeq, bitset_ncmple */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __BOOL
bitset_ncmpne(bitset_t const *lhs, __SIZE_TYPE__ lhs_startbitno,
              bitset_t const *rhs, __SIZE_TYPE__ rhs_startbitno,
              __SIZE_TYPE__ n_bits);
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __BOOL
bitset_ncmpge(bitset_t const *lhs, __SIZE_TYPE__ lhs_startbitno,
              bitset_t const *rhs, __SIZE_TYPE__ rhs_startbitno,
              __SIZE_TYPE__ n_bits);
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __BOOL
bitset_ncmplo(bitset_t const *lhs, __SIZE_TYPE__ lhs_startbitno,
              bitset_t const *rhs, __SIZE_TYPE__ rhs_startbitno,
              __SIZE_TYPE__ n_bits);
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __BOOL
bitset_ncmpgr(bitset_t const *lhs, __SIZE_TYPE__ lhs_startbitno,
              bitset_t const *rhs, __SIZE_TYPE__ rhs_startbitno,
              __SIZE_TYPE__ n_bits);

__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __BOOL bitset_ncmpeq0(bitset_t const *lhs, bitset_t const *rhs, __SIZE_TYPE__ rhs_startbitno, __SIZE_TYPE__ n_bits);
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __BOOL bitset_ncmple0(bitset_t const *lhs, bitset_t const *rhs, __SIZE_TYPE__ rhs_startbitno, __SIZE_TYPE__ n_bits);
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __BOOL bitset_ncmpne0(bitset_t const *lhs, bitset_t const *rhs, __SIZE_TYPE__ rhs_startbitno, __SIZE_TYPE__ n_bits);
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __BOOL bitset_ncmpge0(bitset_t const *lhs, bitset_t const *rhs, __SIZE_TYPE__ rhs_startbitno, __SIZE_TYPE__ n_bits);
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __BOOL bitset_ncmplo0(bitset_t const *lhs, bitset_t const *rhs, __SIZE_TYPE__ rhs_startbitno, __SIZE_TYPE__ n_bits);
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __BOOL bitset_ncmpgr0(bitset_t const *lhs, bitset_t const *rhs, __SIZE_TYPE__ rhs_startbitno, __SIZE_TYPE__ n_bits);
#else /* __INTELLISENSE__ */
#define bitset_t                                     __hybrid_bitset_t
#define bitset_test(self, bitno)                     __hybrid_bitset_test(self, bitno)
#define bitset_set(self, bitno)                      __hybrid_bitset_set(self, bitno)
#define bitset_clear(self, bitno)                    __hybrid_bitset_clear(self, bitno)
#define bitset_flip(self, bitno)                     __hybrid_bitset_flip(self, bitno)
#define bitset_setall(self, n_bits)                  __hybrid_bitset_setall(self, n_bits)
#define bitset_clearall(self, n_bits)                __hybrid_bitset_clearall(self, n_bits)
#define bitset_flipall(self, n_bits)                 __hybrid_bitset_flipall(self, n_bits)
#define bitset_nclear(self, startbitno, endbitno)    __hybrid_bitset_nclear(self, startbitno, endbitno)
#define bitset_nset(self, startbitno, endbitno)      __hybrid_bitset_nset(self, startbitno, endbitno)
#define bitset_nflip(self, startbitno, endbitno)     __hybrid_bitset_nflip(self, startbitno, endbitno)
#define bitset_ffc_i(self, n_bits, p_value)          __hybrid_bitset_ffc_i(self, n_bits, p_value)
#define bitset_ffs_i(self, n_bits, p_value)          __hybrid_bitset_ffs_i(self, n_bits, p_value)
#define bitset_ffc(self, n_bits)                     __hybrid_bitset_ffc(self, n_bits)
#define bitset_ffs(self, n_bits)                     __hybrid_bitset_ffs(self, n_bits)
#define bitset_flc(self, n_bits)                     __hybrid_bitset_flc(self, n_bits)
#define bitset_fls(self, n_bits)                     __hybrid_bitset_fls(self, n_bits)
#define bitset_nffc(self, startbitno, endbitno)      __hybrid_bitset_nffc(self, startbitno, endbitno)
#define bitset_nffs(self, startbitno, endbitno)      __hybrid_bitset_nffs(self, startbitno, endbitno)
#define bitset_nflc(self, startbitno, endbitno)      __hybrid_bitset_nflc(self, startbitno, endbitno)
#define bitset_nfls(self, startbitno, endbitno)      __hybrid_bitset_nfls(self, startbitno, endbitno)
#define bitset_anyset(self, n_bits)                  __hybrid_bitset_anyset(self, n_bits)
#define bitset_allset(self, n_bits)                  __hybrid_bitset_allset(self, n_bits)
#define bitset_nanyset(self, startbitno, endbitno)   __hybrid_bitset_nanyset(self, startbitno, endbitno)
#define bitset_nallset(self, startbitno, endbitno)   __hybrid_bitset_nallset(self, startbitno, endbitno)
#define bitset_popcount(self, n_bits)                __hybrid_bitset_popcount(self, n_bits)
#define bitset_npopcount(self, startbitno, endbitno) __hybrid_bitset_npopcount(self, startbitno, endbitno)
#define bitset_clz(self, n_bits)                     __hybrid_bitset_clz(self, n_bits)
#define bitset_ctz(self, n_bits)                     __hybrid_bitset_ctz(self, n_bits)
#define bitset_rawclz(self, n_bits)                  __hybrid_bitset_rawclz(self, n_bits)
#define bitset_rawctz(self)                          __hybrid_bitset_rawctz(self)
#define bitset_ncopy(dst, dst_startbitno, src, src_startbitno, n_bits) \
	__hybrid_bitset_ncopy(dst, dst_startbitno, src, src_startbitno, n_bits)
#define bitset_ncopy0(dst, src, src_startbitno, n_bits) \
	__hybrid_bitset_ncopy0(dst, src, src_startbitno, n_bits)
#define BITSET_OP_AND __HYBRID_BITSET_OP_AND
#define BITSET_OP_OR  __HYBRID_BITSET_OP_OR
#define BITSET_OP_XOR __HYBRID_BITSET_OP_XOR
#define bitset_nbitop(dst, dst_startbitno, src, src_startbitno, n_bits, op) \
	__hybrid_bitset_nbitop(dst, dst_startbitno, src, src_startbitno, n_bits, op)
#define bitset_nbitop0(dst, src, src_startbitno, n_bits, op) \
	__hybrid_bitset_nbitop0(dst, src, src_startbitno, n_bits, op)
#define bitset_ncmpeq(lhs, lhs_startbitno, rhs, rhs_startbitno, n_bits) __hybrid_bitset_ncmpeq(lhs, lhs_startbitno, rhs, rhs_startbitno, n_bits)
#define bitset_ncmpne(lhs, lhs_startbitno, rhs, rhs_startbitno, n_bits) __hybrid_bitset_ncmpne(lhs, lhs_startbitno, rhs, rhs_startbitno, n_bits)
#define bitset_ncmplo(lhs, lhs_startbitno, rhs, rhs_startbitno, n_bits) __hybrid_bitset_ncmplo(lhs, lhs_startbitno, rhs, rhs_startbitno, n_bits)
#define bitset_ncmple(lhs, lhs_startbitno, rhs, rhs_startbitno, n_bits) __hybrid_bitset_ncmple(lhs, lhs_startbitno, rhs, rhs_startbitno, n_bits)
#define bitset_ncmpgr(lhs, lhs_startbitno, rhs, rhs_startbitno, n_bits) __hybrid_bitset_ncmpgr(lhs, lhs_startbitno, rhs, rhs_startbitno, n_bits)
#define bitset_ncmpge(lhs, lhs_startbitno, rhs, rhs_startbitno, n_bits) __hybrid_bitset_ncmpge(lhs, lhs_startbitno, rhs, rhs_startbitno, n_bits)
#define bitset_ncmpeq0(lhs, rhs, rhs_startbitno, n_bits)                __hybrid_bitset_ncmpeq0(lhs, rhs, rhs_startbitno, n_bits)
#define bitset_ncmpne0(lhs, rhs, rhs_startbitno, n_bits)                __hybrid_bitset_ncmpne0(lhs, rhs, rhs_startbitno, n_bits)
#define bitset_ncmplo0(lhs, rhs, rhs_startbitno, n_bits)                __hybrid_bitset_ncmplo0(lhs, rhs, rhs_startbitno, n_bits)
#define bitset_ncmple0(lhs, rhs, rhs_startbitno, n_bits)                __hybrid_bitset_ncmple0(lhs, rhs, rhs_startbitno, n_bits)
#define bitset_ncmpgr0(lhs, rhs, rhs_startbitno, n_bits)                __hybrid_bitset_ncmpgr0(lhs, rhs, rhs_startbitno, n_bits)
#define bitset_ncmpge0(lhs, rhs, rhs_startbitno, n_bits)                __hybrid_bitset_ncmpge0(lhs, rhs, rhs_startbitno, n_bits)
#endif /* !__INTELLISENSE__ */

/* >> size_t bitno;
 * >> bitset_t bitset[_BITSET_LENGTHOF(42)];
 * >> ...
 * >> bitset_foreach (bitno, bitset, 42) {
 * >>     printf("bit is on: %Iu\n", bitno);
 * >> } */
#define bitset_foreach(bitno, self, n_bits) \
	__hybrid_bitset_foreach(bitno, self, n_bits)
#define bitset_nforeach(bitno, self, startbitno, endbitno) \
	__hybrid_bitset_nforeach(bitno, self, startbitno, endbitno)

/* Atomic bitset operations. */
#ifdef __GUARD_HYBRID___ATOMIC_H
#define bitset_atomic_set(self, bitno)        __hybrid_bitset_atomic_set(self, bitno)
#define bitset_atomic_clear(self, bitno)      __hybrid_bitset_atomic_clear(self, bitno)
#define bitset_atomic_flip(self, bitno)       __hybrid_bitset_atomic_flip(self, bitno)
#define bitset_atomic_fetchset(self, bitno)   __hybrid_bitset_atomic_fetchset(self, bitno)
#define bitset_atomic_fetchclear(self, bitno) __hybrid_bitset_atomic_fetchclear(self, bitno)
#define bitset_atomic_fetchflip(self, bitno)  __hybrid_bitset_atomic_fetchflip(self, bitno)
#endif /* __GUARD_HYBRID___ATOMIC_H */

__DECL_END
#endif /* __CC__ */

#endif /* !__GUARD_HYBRID_BITSET_H */
