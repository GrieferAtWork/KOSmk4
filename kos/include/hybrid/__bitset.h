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
#ifndef __GUARD_HYBRID___BITSET_H
#define __GUARD_HYBRID___BITSET_H 1

#include "../__stdinc.h"
/**/

#include "__assert.h"
#include "__bit.h"
#include "__overflow.h"
#include "__string.h"
#include "typecore.h"

#ifndef __HYBRID_BITSET_WORD_BITS
#define __HYBRID_BITSET_WORD_BITS __CHAR_BIT__
#endif /* !__HYBRID_BITSET_WORD_BITS */

#if __HYBRID_BITSET_WORD_BITS == 8
#define __hybrid_bitset_t             __UINT8_TYPE__
#define __HYBRID_BITSET_WORD_BMAX     __UINT8_C(0xff)
#define __HYBRID_BITSET_WORD_BMSK     7
#define __HYBRID_BITSET_WORD_SHFT     3
#define __HYBRID_BITSET_WORD_POPCOUNT __hybrid_popcount8
#define __HYBRID_BITSET_WORD_CLZ      __hybrid_clz8
#define __HYBRID_BITSET_WORD_CTZ      __hybrid_ctz8
#elif __HYBRID_BITSET_WORD_BITS == 16
#define __hybrid_bitset_t             __UINT16_TYPE__
#define __HYBRID_BITSET_WORD_BMAX     __UINT16_C(0xffff)
#define __HYBRID_BITSET_WORD_BMSK     15
#define __HYBRID_BITSET_WORD_SHFT     4
#define __HYBRID_BITSET_WORD_POPCOUNT __hybrid_popcount16
#define __HYBRID_BITSET_WORD_CLZ      __hybrid_clz16
#define __HYBRID_BITSET_WORD_CTZ      __hybrid_ctz16
#define __HYBRID_BITSET_WORD_MEMMOVE  __hybrid_memcpyw
#elif __HYBRID_BITSET_WORD_BITS == 32
#define __hybrid_bitset_t             __UINT32_TYPE__
#define __HYBRID_BITSET_WORD_BMAX     __UINT32_C(0xffffffff)
#define __HYBRID_BITSET_WORD_BMSK     31
#define __HYBRID_BITSET_WORD_SHFT     5
#define __HYBRID_BITSET_WORD_POPCOUNT __hybrid_popcount32
#define __HYBRID_BITSET_WORD_CLZ      __hybrid_clz32
#define __HYBRID_BITSET_WORD_CTZ      __hybrid_ctz32
#define __HYBRID_BITSET_WORD_MEMMOVE  __hybrid_memcpyl
#elif __HYBRID_BITSET_WORD_BITS == 64
#define __hybrid_bitset_t             __UINT64_TYPE__
#define __HYBRID_BITSET_WORD_BMAX     __UINT64_C(0xffffffffffffffff)
#define __HYBRID_BITSET_WORD_BMSK     63
#define __HYBRID_BITSET_WORD_SHFT     6
#define __HYBRID_BITSET_WORD_POPCOUNT __hybrid_popcount64
#define __HYBRID_BITSET_WORD_CLZ      __hybrid_clz64
#define __HYBRID_BITSET_WORD_CTZ      __hybrid_ctz64
#define __HYBRID_BITSET_WORD_MEMMOVE  __hybrid_memcpyq
#else /* __HYBRID_BITSET_WORD_BITS == ... */
#define __hybrid_bitset_t             __TYPEFOR_UINTIB(__HYBRID_BITSET_WORD_BITS/8)
#define __HYBRID_BITSET_WORD_BMAX     ((__CCAST(__hybrid_bitset_t)1 << __HYBRID_BITSET_WORD_BITS) - 1)
#define __HYBRID_BITSET_WORD_BMSK     (__HYBRID_BITSET_WORD_BITS - 1)
#define __HYBRID_BITSET_WORD_SHFT     log2(__HYBRID_BITSET_WORD_BITS)
#define __HYBRID_BITSET_WORD_POPCOUNT __hybrid_popcount
#define __HYBRID_BITSET_WORD_CLZ      __hybrid_clz
#define __HYBRID_BITSET_WORD_CTZ      __hybrid_ctz
#error "Unsuppported `__HYBRID_BITSET_WORD_BITS'"
#endif /* __HYBRID_BITSET_WORD_BITS != ... */
#ifndef __HYBRID_BITSET_WORD_MEMMOVE
#define __HYBRID_BITSET_WORD_MEMMOVE(dst, src, n_words) \
	__hybrid_memmove(dst, src, (n_words) * sizeof(__hybrid_bitset_t))
#endif /* !__HYBRID_BITSET_WORD_MEMMOVE */
#ifndef __HYBRID_BITSET_WORD_BCMP
#define __HYBRID_BITSET_WORD_BCMP(dst, src, n_words) \
	__hybrid_bcmp(dst, src, (n_words) * sizeof(__hybrid_bitset_t))
#endif /* !__HYBRID_BITSET_WORD_BCMP */

/* UNDEFINED WHEN `x == 0xff'
 * >> result = 0;
 * >> while (x & 0x80) {
 * >>     ++result;
 * >>     x <<= 1;
 * >> } */
#define __HYBRID_BITSET_WORD_CLO(x) __HYBRID_BITSET_WORD_CLZ(~(x))

/* UNDEFINED WHEN `x == 0x00'
 * >> result = 0;
 * >> while (x & 1) {
 * >>     ++result;
 * >>     x >>= 1;
 * >> } */
#define __HYBRID_BITSET_WORD_CTO(x) __HYBRID_BITSET_WORD_CTZ(~(x))


#define __HYBRID_BITSET_WORD(bitno)      ((bitno) >> __HYBRID_BITSET_WORD_SHFT)
#define __HYBRID_BITSET_MASK(bitno)      (__CCAST(__hybrid_bitset_t) 1 << ((bitno) & __HYBRID_BITSET_WORD_BMSK))
#define __HYBRID_BITSET_LENGTHOF(n_bits) (((n_bits) + __HYBRID_BITSET_WORD_BMSK) >> __HYBRID_BITSET_WORD_SHFT)

#if __HYBRID_BITSET_WORD_BITS == __CHAR_BIT__
#define __HYBRID_BITSET_WORD_SIZE      1
#define __HYBRID_BITSET_SIZEOF(n_bits) __HYBRID_BITSET_LENGTHOF(n_bits)
#else /* __HYBRID_BITSET_WORD_BITS == __CHAR_BIT__ */
#define __HYBRID_BITSET_WORD_SIZE      (__HYBRID_BITSET_WORD_BITS / __CHAR_BIT__)
#define __HYBRID_BITSET_SIZEOF(n_bits) (__HYBRID_BITSET_LENGTHOF(n_bits) * __HYBRID_BITSET_WORD_SIZE)
#endif /* __HYBRID_BITSET_WORD_BITS != __CHAR_BIT__ */


/* >> __HYBRID_BITSET_LO_MASKIN(0) == 0xb00000000
 * >> __HYBRID_BITSET_LO_MASKIN(1) == 0xb00000001
 * >> __HYBRID_BITSET_LO_MASKIN(2) == 0xb00000011
 * >> __HYBRID_BITSET_LO_MASKIN(6) == 0xb00111111
 * >> __HYBRID_BITSET_LO_MASKIN(7) == 0xb01111111
 * >> __HYBRID_BITSET_LO_MASKIN(8) == 0xb11111111 // requires use of __HYBRID_BITSET_LO_MASKIN_P1
 *
 * >> __HYBRID_BITSET_LO_MASKOU(0) == 0xb11111111
 * >> __HYBRID_BITSET_LO_MASKOU(1) == 0xb11111110
 * >> __HYBRID_BITSET_LO_MASKOU(2) == 0xb11111100
 * >> __HYBRID_BITSET_LO_MASKOU(6) == 0xb11000000
 * >> __HYBRID_BITSET_LO_MASKOU(7) == 0xb10000000
 * >> __HYBRID_BITSET_LO_MASKOU(8) == 0xb00000000 // requires use of __HYBRID_BITSET_LO_MASKOU_P1
 *
 * >> __HYBRID_BITSET_HI_MASKIN(0) == 0xb00000000
 * >> __HYBRID_BITSET_HI_MASKIN(1) == 0xb10000000
 * >> __HYBRID_BITSET_HI_MASKIN(2) == 0xb11000000
 * >> __HYBRID_BITSET_HI_MASKIN(6) == 0xb11111100
 * >> __HYBRID_BITSET_HI_MASKIN(7) == 0xb11111110
 * >> __HYBRID_BITSET_HI_MASKIN(8) == 0xb11111111 // requires use of __HYBRID_BITSET_HI_MASKIN_P1
 *
 * >> __HYBRID_BITSET_HI_MASKOU(0) == 0xb11111111
 * >> __HYBRID_BITSET_HI_MASKOU(1) == 0xb01111111
 * >> __HYBRID_BITSET_HI_MASKOU(2) == 0xb00111111
 * >> __HYBRID_BITSET_HI_MASKOU(6) == 0xb00000011
 * >> __HYBRID_BITSET_HI_MASKOU(7) == 0xb00000001
 * >> __HYBRID_BITSET_HI_MASKOU(8) == 0xb00000000 // requires use of __HYBRID_BITSET_HI_MASKOU_P1
 *
 * NOTE: When  "n >= 8", behavior is HARD undefined. If you
 *       need to value of `__HYBRID_BITSET_*_MASK*(n + 1)',
 *       the `*_P1' variant must be used.
 */
#define __HYBRID_BITSET_LO_MASKIN(n) __CCAST(__hybrid_bitset_t)(~(__HYBRID_BITSET_WORD_BMAX << (n)))
#define __HYBRID_BITSET_LO_MASKOU(n) __CCAST(__hybrid_bitset_t)(__HYBRID_BITSET_WORD_BMAX << (n))
#define __HYBRID_BITSET_HI_MASKIN(n) __CCAST(__hybrid_bitset_t)(__CCAST(__hybrid_bitset_t)((__HYBRID_BITSET_WORD_BMAX << __HYBRID_BITSET_WORD_BITS) >> (n)))
#define __HYBRID_BITSET_HI_MASKOU(n) __CCAST(__hybrid_bitset_t)(~(__CCAST(__hybrid_bitset_t)((__HYBRID_BITSET_WORD_BMAX << __HYBRID_BITSET_WORD_BITS) >> (n))))

#define __HYBRID_BITSET_LO_MASKIN_P1(n) __CCAST(__hybrid_bitset_t)(~((__HYBRID_BITSET_WORD_BMAX << 1) << (n)))
#define __HYBRID_BITSET_LO_MASKOU_P1(n) __CCAST(__hybrid_bitset_t)((__HYBRID_BITSET_WORD_BMAX << 1) << (n))
#define __HYBRID_BITSET_HI_MASKIN_P1(n) __CCAST(__hybrid_bitset_t)(__CCAST(__hybrid_bitset_t)((__HYBRID_BITSET_WORD_BMAX << (__HYBRID_BITSET_WORD_BITS - 1)) >> (n)))
#define __HYBRID_BITSET_HI_MASKOU_P1(n) __CCAST(__hybrid_bitset_t)(~(__CCAST(__hybrid_bitset_t)((__HYBRID_BITSET_WORD_BMAX << (__HYBRID_BITSET_WORD_BITS - 1)) >> (n))))



#ifdef __CC__
__DECL_BEGIN

#define __hybrid_memset_one(p, n)  __hybrid_memset(p, __HYBRID_BITSET_WORD_BMAX, n)
#define __hybrid_memset_zero(p, n) __hybrid_bzero(p, n)

/* >> __hybrid_bitset_t __hybrid_bitset_decl(self, 256); */
#define __hybrid_bitset_decl(self, nbits) \
	((self)[__HYBRID_BITSET_LENGTHOF(nbits)])

/* >> bool __hybrid_bitset_test(__hybrid_bitset_t const *self, size_t bitno); */
#define __hybrid_bitset_test(self, bitno) \
	((self)[__HYBRID_BITSET_WORD(bitno)] & __HYBRID_BITSET_MASK(bitno))

/* >> void __hybrid_bitset_set(__hybrid_bitset_t *self, size_t bitno); */
#define __hybrid_bitset_set(self, bitno) \
	(void)((self)[__HYBRID_BITSET_WORD(bitno)] |= __HYBRID_BITSET_MASK(bitno))

/* >> void __hybrid_bitset_clear(__hybrid_bitset_t *self, size_t bitno); */
#define __hybrid_bitset_clear(self, bitno) \
	(void)((self)[__HYBRID_BITSET_WORD(bitno)] &= ~__HYBRID_BITSET_MASK(bitno))

/* >> void __hybrid_bitset_flip(__hybrid_bitset_t *self, size_t bitno); */
#define __hybrid_bitset_flip(self, bitno) \
	(void)((self)[__HYBRID_BITSET_WORD(bitno)] ^= __HYBRID_BITSET_MASK(bitno))


/* >> void __hybrid_bitset_setall(__hybrid_bitset_t *self, size_t n_bits); */
#define __hybrid_bitset_setall(self, n_bits) \
	__hybrid_memset_one(self, __HYBRID_BITSET_SIZEOF(n_bits))

/* >> void __hybrid_bitset_clearall(__hybrid_bitset_t *self, size_t n_bits); */
#define __hybrid_bitset_clearall(self, n_bits) \
	__hybrid_memset_zero(self, __HYBRID_BITSET_SIZEOF(n_bits))

/* >> void __hybrid_bitset_flipall(__hybrid_bitset_t *self, size_t n_bits); */
#define __hybrid_bitset_flipall(self, n_bits)                                    \
	do {                                                                         \
		__SIZE_TYPE__ __bfa_i;                                                   \
		for (__bfa_i = 0; __bfa_i < __HYBRID_BITSET_LENGTHOF(n_bits); ++__bfa_i) \
			(self)[__bfa_i] ^= __HYBRID_BITSET_WORD_BMAX;                        \
	}	__WHILE0

/* Atomic bitset operations. */
#ifdef __GUARD_HYBRID___ATOMIC_H
#define __hybrid_bitset_atomic_set(self, bitno)        __hybrid_atomic_or(&(self)[__HYBRID_BITSET_WORD(bitno)], __HYBRID_BITSET_MASK(bitno), __ATOMIC_SEQ_CST)
#define __hybrid_bitset_atomic_clear(self, bitno)      __hybrid_atomic_and(&(self)[__HYBRID_BITSET_WORD(bitno)], ~__HYBRID_BITSET_MASK(bitno), __ATOMIC_SEQ_CST)
#define __hybrid_bitset_atomic_flip(self, bitno)       __hybrid_atomic_xor(&(self)[__HYBRID_BITSET_WORD(bitno)], __HYBRID_BITSET_MASK(bitno), __ATOMIC_SEQ_CST)
#define __hybrid_bitset_atomic_fetchset(self, bitno)   (__hybrid_atomic_fetchor(&(self)[__HYBRID_BITSET_WORD(bitno)], __HYBRID_BITSET_MASK(bitno), __ATOMIC_SEQ_CST) & __HYBRID_BITSET_MASK(bitno))
#define __hybrid_bitset_atomic_fetchclear(self, bitno) (__hybrid_atomic_fetchand(&(self)[__HYBRID_BITSET_WORD(bitno)], ~__HYBRID_BITSET_MASK(bitno), __ATOMIC_SEQ_CST) & __HYBRID_BITSET_MASK(bitno))
#define __hybrid_bitset_atomic_fetchflip(self, bitno)  (__hybrid_atomic_fetchxor(&(self)[__HYBRID_BITSET_WORD(bitno)], __HYBRID_BITSET_MASK(bitno), __ATOMIC_SEQ_CST) & __HYBRID_BITSET_MASK(bitno))
#endif /* __GUARD_HYBRID___ATOMIC_H */

/* >> size_t bitno;
 * >> __hybrid_bitset_t bitset[__HYBRID_BITSET_LENGTHOF(42)];
 * >> ...
 * >> __hybrid_bitset_foreach (bitno, bitset, 42) {
 * >>     printf("bit is on: %Iu\n", bitno);
 * >> } */
#define __hybrid_bitset_foreach(bitno, self, n_bits) \
	for ((bitno) = 0; (bitno) < (n_bits); ++(bitno)) \
		if (!__hybrid_bitset_test(self, bitno))      \
			;                                        \
		else
#define __hybrid_bitset_nforeach(bitno, self, startbitno, endbitno) \
	for ((bitno) = (startbitno); (bitno) < (endbitno); ++(bitno))   \
		if (!__hybrid_bitset_test(self, bitno))                     \
			;                                                       \
		else
#define __hybrid_bitset_nforeach_r(bitno, self, startbitno, maxbitno) \
	for ((bitno) = (startbitno); (bitno) <= (maxbitno); ++(bitno))    \
		if (!__hybrid_bitset_test(self, bitno))                       \
			;                                                         \
		else



/* Turn off bits [minbitno, maxbitno] (inclusive) in `self'
 * NOTE: When  `minbitno > maxbitno', the result  is weak undefined behavior,
 *       in that the way in which `self' is modified is undefined, though the
 *       function still guaranties that nothing but `self' gets modified. */
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_bitset_nclear_r)(__hybrid_bitset_t *__restrict __self,
                           __SIZE_TYPE__ __minbitno, __SIZE_TYPE__ __maxbitno) {
	__SIZE_TYPE__ __minword = __HYBRID_BITSET_WORD(__minbitno);
	__SIZE_TYPE__ __maxword = __HYBRID_BITSET_WORD(__maxbitno);
	if (__minword == __maxword) {
		__self[(__SIZE_TYPE__)__maxword] &= (__HYBRID_BITSET_LO_MASKIN(__minbitno & __HYBRID_BITSET_WORD_BMSK) |
		                                     __HYBRID_BITSET_LO_MASKOU_P1(__maxbitno & __HYBRID_BITSET_WORD_BMSK));
	} else if __likely(__minbitno <= __maxbitno) {
		__self[(__SIZE_TYPE__)__minword] &= __HYBRID_BITSET_LO_MASKIN(__minbitno & __HYBRID_BITSET_WORD_BMSK);
		__hybrid_memset_zero(&__self[(__SIZE_TYPE__)__minword + 1], (__SIZE_TYPE__)__maxword - ((__SIZE_TYPE__)__minword + 1));
		__self[(__SIZE_TYPE__)__maxword] &= __HYBRID_BITSET_LO_MASKOU_P1(__maxbitno & __HYBRID_BITSET_WORD_BMSK);
	}
}

/* Turn off bits [startbitno, endbitno) (non-inclusive) in `self'
 * NOTE: When `startbitno > endbitno', the result is weak undefined behavior,
 *       in that the way in which `self' is modified is undefined, though the
 *       function still guaranties that nothing but `self' gets modified. */
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_bitset_nclear)(__hybrid_bitset_t *__restrict __self,
                         __SIZE_TYPE__ __startbitno, __SIZE_TYPE__ __endbitno) {
	__SIZE_TYPE__ __maxbitno;
	if __likely(!__hybrid_overflow_usub(__endbitno, 1, &__maxbitno))
		__hybrid_bitset_nclear_r(__self, __startbitno, __maxbitno);
}

/* Turn on bits [minbitno, maxbitno] (inclusive) in `self'
 * NOTE: When  `minbitno > maxbitno', the result  is weak undefined behavior,
 *       in that the way in which `self' is modified is undefined, though the
 *       function still guaranties that nothing but `self' gets modified. */
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_bitset_nset_r)(__hybrid_bitset_t *__restrict __self,
                         __SIZE_TYPE__ __minbitno, __SIZE_TYPE__ __maxbitno) {
	__SIZE_TYPE__ __minword = __HYBRID_BITSET_WORD(__minbitno);
	__SIZE_TYPE__ __maxword = __HYBRID_BITSET_WORD(__maxbitno);
	if (__minword == __maxword) {
		__self[(__SIZE_TYPE__)__maxword] |= (__HYBRID_BITSET_LO_MASKOU(__minbitno & __HYBRID_BITSET_WORD_BMSK) &
		                                     __HYBRID_BITSET_LO_MASKIN_P1(__maxbitno & __HYBRID_BITSET_WORD_BMSK));
	} else if __likely(__minbitno <= __maxbitno) {
		__self[(__SIZE_TYPE__)__minword] |= __HYBRID_BITSET_LO_MASKOU(__minbitno & __HYBRID_BITSET_WORD_BMSK);
		__hybrid_memset_one(&__self[__minword + 1], (__SIZE_TYPE__)__maxword - ((__SIZE_TYPE__)__minword + 1));
		__self[(__SIZE_TYPE__)__maxword] |= __HYBRID_BITSET_LO_MASKIN_P1(__maxbitno & __HYBRID_BITSET_WORD_BMSK);
	}
}

/* Turn on bits [startbitno, endbitno) (non-inclusive) in `self'
 * NOTE: When `startbitno > endbitno', the result is weak undefined behavior,
 *       in that the way in which `self' is modified is undefined, though the
 *       function still guaranties that nothing but `self' gets modified. */
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_bitset_nset)(__hybrid_bitset_t *__restrict __self,
                       __SIZE_TYPE__ __startbitno, __SIZE_TYPE__ __endbitno) {
	__SIZE_TYPE__ __maxbitno;
	if __likely(!__hybrid_overflow_usub(__endbitno, 1, &__maxbitno))
		__hybrid_bitset_nset_r(__self, __startbitno, __maxbitno);
}

/* Flip bits [minbitno, maxbitno] (inclusive) in `self'
 * NOTE: When  `minbitno > maxbitno', the result  is weak undefined behavior,
 *       in that the way in which `self' is modified is undefined, though the
 *       function still guaranties that nothing but `self' gets modified. */
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_bitset_nflip_r)(__hybrid_bitset_t *__restrict __self,
                          __SIZE_TYPE__ __minbitno, __SIZE_TYPE__ __maxbitno) {
	__SIZE_TYPE__ __minword = __HYBRID_BITSET_WORD(__minbitno);
	__SIZE_TYPE__ __maxword = __HYBRID_BITSET_WORD(__maxbitno);
	if (__minword == __maxword) {
		__self[(__SIZE_TYPE__)__maxword] ^= (__HYBRID_BITSET_LO_MASKOU(__minbitno & __HYBRID_BITSET_WORD_BMSK) &
		                                     __HYBRID_BITSET_LO_MASKIN_P1(__maxbitno & __HYBRID_BITSET_WORD_BMSK));
	} else if __likely(__minbitno <= __maxbitno) {
		__SIZE_TYPE__ __i;
		__self[(__SIZE_TYPE__)__minword] ^= __HYBRID_BITSET_LO_MASKOU(__minbitno & __HYBRID_BITSET_WORD_BMSK);
		for (__i = __minword + 1; __i < __maxword; ++__i)
			__self[(__SIZE_TYPE__)__i] ^= __HYBRID_BITSET_WORD_BMAX;
		__self[(__SIZE_TYPE__)__maxword] ^= __HYBRID_BITSET_LO_MASKIN_P1(__maxbitno & __HYBRID_BITSET_WORD_BMSK);
	}
}

/* Flip bits [startbitno, endbitno) (non-inclusive) in `self'
 * NOTE: When `startbitno > endbitno', the result is weak undefined behavior,
 *       in that the way in which `self' is modified is undefined, though the
 *       function still guaranties that nothing but `self' gets modified. */
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_bitset_nflip)(__hybrid_bitset_t *__restrict __self,
                        __SIZE_TYPE__ __startbitno, __SIZE_TYPE__ __endbitno) {
	__SIZE_TYPE__ __maxbitno;
	if __likely(!__hybrid_overflow_usub(__endbitno, 1, &__maxbitno))
		__hybrid_bitset_nflip_r(__self, __startbitno, __maxbitno);
}


#define __HYBRID_PRIVATE_BITSET_FFC_I_IMPL(self, n_bits, result)               \
	__SIZE_TYPE__ __bffc_bindex, __bffc_endword;                               \
	__bffc_endbyte = __HYBRID_BITSET_WORD(n_bits + __HYBRID_BITSET_WORD_BMSK); \
	result         = -1;                                                       \
	for (__bffc_bindex = 0; __bffc_bindex < __bffc_endword; ++__bffc_bindex) { \
		__hybrid_bitset_t __word = self[__bffc_bindex];                        \
		if (__word == __HYBRID_BITSET_WORD_BMAX)                               \
			continue;                                                          \
		result = __bffc_bindex << __HYBRID_BITSET_WORD_SHFT;                   \
		result += __HYBRID_BITSET_WORD_CTO(__word);                            \
		if __unlikely((__SIZE_TYPE__)result >= (__SIZE_TYPE__)nbits)           \
			result = -1;                                                       \
		break;                                                                 \
	}
#define __HYBRID_PRIVATE_BITSET_FFS_I_IMPL(self, n_bits, result)               \
	__SIZE_TYPE__ __bffs_bindex, __bffs_endbyte;                               \
	__bffs_endbyte = __HYBRID_BITSET_WORD(n_bits + __HYBRID_BITSET_WORD_BMSK); \
	result         = -1;                                                       \
	for (__bffs_bindex = 0; __bffs_bindex < __bffs_endbyte; ++__bffs_bindex) { \
		__hybrid_bitset_t __word = self[__bffs_bindex];                        \
		if (__word == 0)                                                       \
			continue;                                                          \
		result = (__bffs_bindex << __HYBRID_BITSET_WORD_SHFT);                 \
		result += __HYBRID_BITSET_WORD_CTZ(__word);                            \
		if __unlikely((__SIZE_TYPE__)result >= (__SIZE_TYPE__)nbits)           \
			result = -1;                                                       \
		break;                                                                 \
	}


/* >> void __hybrid_bitset_ffc_i(__hybrid_bitset_t const *self, size_t n_bits, ssize_t *p_value);
 * Find the first bitno within [0, n_bits) that is off and store its
 * index in `*p_value'. If no such bit exists, write `-1' into `*p_value'. */
#define __hybrid_bitset_ffc_i(self, n_bits, p_value)                                  \
	do {                                                                              \
		__hybrid_bitset_t const *__bffc_self = (self);                                \
		__SIZE_TYPE__ __bffc_nbits = (nbits);                                         \
		__SSIZE_TYPE__ __bffc_result;                                                 \
		__HYBRID_PRIVATE_BITSET_FFC_I_IMPL(__bffc_self, __bffc_nbits, __bffc_result); \
		*(p_value) = __bffc_result;                                                   \
	}	__WHILE0

/* >> void __hybrid_bitset_ffs_i(__hybrid_bitset_t const *self, size_t n_bits, ssize_t *p_value);
 * Find the first bitno within [0, n_bits) that is on and store its
 * index in `*p_value'. If no such bit exists, write `-1' into `*p_value'. */
#define __hybrid_bitset_ffs_i(self, n_bits, p_value)                                  \
	do {                                                                              \
		__hybrid_bitset_t const *__bffc_self = (self);                                \
		__SIZE_TYPE__ __bffc_nbits           = (nbits);                               \
		__SSIZE_TYPE__ __bffc_result;                                                 \
		__HYBRID_PRIVATE_BITSET_FFS_I_IMPL(__bffc_self, __bffc_nbits, __bffc_result); \
		*(p_value) = __bffc_result;                                                   \
	}	__WHILE0


/* Find the first bitno within [0,  n_bits) that is off and  return
 * its index. If no such bit exists, return some value `>= n_bits'. */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_ffc)(__hybrid_bitset_t const *__restrict __self, __SIZE_TYPE__ __n_bits) {
	__SIZE_TYPE__ __result, __bffc_bindex, __bffc_endword;
	__bffc_endword = __HYBRID_BITSET_WORD(__n_bits + __HYBRID_BITSET_WORD_BMSK);
	__result       = __n_bits;
	for (__bffc_bindex = 0; __bffc_bindex < __bffc_endword; ++__bffc_bindex) {
		__hybrid_bitset_t __word = __self[__bffc_bindex];
		if (__word == __HYBRID_BITSET_WORD_BMAX)
			continue;
		__result = __bffc_bindex << __HYBRID_BITSET_WORD_SHFT;
		__result += __HYBRID_BITSET_WORD_CTO(__word);
		break;
	}
	return __result;
}

/* Find  the first bitno  within [0, n_bits) that  is on and return
 * its index. If no such bit exists, return some value `>= n_bits'. */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_ffs)(__hybrid_bitset_t const *__restrict __self, __SIZE_TYPE__ __n_bits) {
	__SIZE_TYPE__ __result, __bffs_bindex, __bffs_endword;
	__bffs_endword = __HYBRID_BITSET_WORD(__n_bits + __HYBRID_BITSET_WORD_BMSK);
	__result       = __n_bits;
	for (__bffs_bindex = 0; __bffs_bindex < __bffs_endword; ++__bffs_bindex) {
		__hybrid_bitset_t __word = __self[(__SIZE_TYPE__)__bffs_bindex];
		if (__word == 0)
			continue;
		__result = __bffs_bindex << __HYBRID_BITSET_WORD_SHFT;
		__result += __HYBRID_BITSET_WORD_CTZ(__word);
		break;
	}
	return __result;
}

/* Find  the last bitno  within [0, n_bits) that  is off and return
 * its index. If no such bit exists, return some value `>= n_bits'. */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_flc)(__hybrid_bitset_t const *__restrict __self, __SIZE_TYPE__ __n_bits) {
	__SIZE_TYPE__ __result, __bflc_endword;
	__bflc_endword = __HYBRID_BITSET_WORD(__n_bits + __HYBRID_BITSET_WORD_BMSK);
	if (__n_bits & __HYBRID_BITSET_WORD_BMSK) {
		__hybrid_bitset_t __word;
		--__bflc_endword;
		__word = __self[__bflc_endword];
		__word |= __HYBRID_BITSET_LO_MASKOU(__n_bits & __HYBRID_BITSET_WORD_BMSK);
		if (__word != __HYBRID_BITSET_WORD_BMAX) {
			__result = __bflc_endword << __HYBRID_BITSET_WORD_SHFT;
			__result += (__HYBRID_BITSET_WORD_BMSK - __HYBRID_BITSET_WORD_CLO(__word));
			return __result;
		}
	}
	__result = __n_bits;
	while (__bflc_endword > 0) {
		__hybrid_bitset_t __word;
		--__bflc_endword;
		__word = __self[__bflc_endword];
		if (__word != __HYBRID_BITSET_WORD_BMAX) {
			__result = __bflc_endword << __HYBRID_BITSET_WORD_SHFT;
			__result += (__HYBRID_BITSET_WORD_BMSK - __HYBRID_BITSET_WORD_CLO(__word));
			break;
		}
	}
	return __result;
}

/* Find  the last  bitno within [0,  n_bits) that is  on and return
 * its index. If no such bit exists, return some value `>= n_bits'. */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_fls)(__hybrid_bitset_t const *__restrict __self, __SIZE_TYPE__ __n_bits) {
	__SIZE_TYPE__ __result, __bfls_endword;
	__bfls_endword = __HYBRID_BITSET_WORD(__n_bits + __HYBRID_BITSET_WORD_BMSK);
	if (__n_bits & __HYBRID_BITSET_WORD_BMSK) {
		__hybrid_bitset_t __word;
		--__bfls_endword;
		__word = __self[__bfls_endword] & __HYBRID_BITSET_LO_MASKIN(__n_bits & __HYBRID_BITSET_WORD_BMSK);
		if (__word != 0) {
			__result = (__SIZE_TYPE__)__bfls_endword << __HYBRID_BITSET_WORD_SHFT;
			__result += (__HYBRID_BITSET_WORD_BMSK - __HYBRID_BITSET_WORD_CLZ(__word));
			return __result;
		}
	}
	__result = __n_bits;
	while (__bfls_endword > 0) {
		__hybrid_bitset_t __word;
		--__bfls_endword;
		__word = __self[(__SIZE_TYPE__)__bfls_endword];
		if (__word != 0) {
			__result = (__SIZE_TYPE__)__bfls_endword << __HYBRID_BITSET_WORD_SHFT;
			__result += (__HYBRID_BITSET_WORD_BMSK - __HYBRID_BITSET_WORD_CLZ(__word));
			break;
		}
	}
	return __result;
}

/* Find the first bitno within [minbitno,maxbitno] that is on and return
 * its index. If  no such  bit exists, return  some value  `> maxbitno'. */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_nffs_r)(__hybrid_bitset_t const *__restrict __self,
                                      __SIZE_TYPE__ __minbitno, __SIZE_TYPE__ __maxbitno) {
	__SIZE_TYPE__ __minword = __HYBRID_BITSET_WORD(__minbitno);
	__SIZE_TYPE__ __maxword = __HYBRID_BITSET_WORD(__maxbitno);
	if (__minword >= __maxword) {
		if __likely(__minbitno <= __maxbitno) {
			__hybrid_bitset_t __word;
			__word = __self[__maxword] & (__HYBRID_BITSET_LO_MASKOU(__minbitno & __HYBRID_BITSET_WORD_BMSK) &
			                              __HYBRID_BITSET_LO_MASKIN_P1(__maxbitno & __HYBRID_BITSET_WORD_BMSK));
			if (__word != 0) {
				__word >>= __minbitno & __HYBRID_BITSET_WORD_BMSK;
				return __minbitno + __HYBRID_BITSET_WORD_CTZ(__word);
			}
		}
	} else {
		__SIZE_TYPE__ __i;
		__hybrid_bitset_t __word;
		__word = __self[__minword] & __HYBRID_BITSET_LO_MASKOU(__minbitno & __HYBRID_BITSET_WORD_BMSK);
		if (__word != 0) {
			__word >>= __minbitno & __HYBRID_BITSET_WORD_BMSK;
			return __minbitno + __HYBRID_BITSET_WORD_CTZ(__word);
		}
		for (__i = __minword + 1; __i < __maxword; ++__i) {
			__word = __self[__i];
			if (__word != 0)
				return (__i << __HYBRID_BITSET_WORD_SHFT) + __HYBRID_BITSET_WORD_CTZ(__word);
		}
		__word = __self[__maxword] & __HYBRID_BITSET_LO_MASKIN_P1(__maxbitno & __HYBRID_BITSET_WORD_BMSK);
		if (__word != 0)
			return (__maxword << __HYBRID_BITSET_WORD_SHFT) + __HYBRID_BITSET_WORD_CTZ(__word);
	}
	return __maxbitno + 1;
}

/* Find the first bitno within [startbitno,endbitno) that is on and return
 * its index.  If no  such bit  exists, return  some value  `>= endbitno'. */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_nffs)(__hybrid_bitset_t const *__restrict __self,
                                    __SIZE_TYPE__ __startbitno, __SIZE_TYPE__ __endbitno) {
	__SIZE_TYPE__ __maxbitno;
	if __likely(!__hybrid_overflow_usub(__endbitno, 1, &__maxbitno))
		return __hybrid_bitset_nffs_r(__self, __startbitno, __maxbitno);
	return 0; /* Because `__endbitno' must be `0' */
}

/* Find the first bitno within [minbitno,maxbitno] that is off and return
 * its index.  If no  such bit  exists, return  some value  `> maxbitno'. */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_nffc_r)(__hybrid_bitset_t const *__restrict __self,
                                      __SIZE_TYPE__ __minbitno, __SIZE_TYPE__ __maxbitno) {
	__SIZE_TYPE__ __minword = __HYBRID_BITSET_WORD(__minbitno);
	__SIZE_TYPE__ __maxword = __HYBRID_BITSET_WORD(__maxbitno);
	if (__minword >= __maxword) {
		if __likely(__minbitno <= __maxbitno) {
			__hybrid_bitset_t __word;
			__hybrid_bitset_t __mask;
			__mask = (__HYBRID_BITSET_LO_MASKOU(__minbitno & __HYBRID_BITSET_WORD_BMSK) &
			          __HYBRID_BITSET_LO_MASKIN_P1(__maxbitno & __HYBRID_BITSET_WORD_BMSK));
			__word = __self[__maxword] & __mask;
			if (__word != __mask) {
				__word >>= __minbitno & __HYBRID_BITSET_WORD_BMSK;
				return __minbitno + __HYBRID_BITSET_WORD_CTO(__word);
			}
		}
	} else {
		__SIZE_TYPE__ __i;
		__hybrid_bitset_t __word;
		__hybrid_bitset_t __mask;
		__mask = __HYBRID_BITSET_LO_MASKOU(__minbitno & __HYBRID_BITSET_WORD_BMSK);
		__word = __self[__minword] & __mask;
		if (__word != __mask) {
			__word >>= __minbitno & __HYBRID_BITSET_WORD_BMSK;
			return __minbitno + __HYBRID_BITSET_WORD_CTO(__word);
		}
		for (__i = __minword + 1; __i < __maxword; ++__i) {
			__word = __self[__i];
			if (__word != __HYBRID_BITSET_WORD_BMAX)
				return (__i << __HYBRID_BITSET_WORD_SHFT) + __HYBRID_BITSET_WORD_CTO(__word);
		}
		__mask = __HYBRID_BITSET_LO_MASKIN_P1(__maxbitno & __HYBRID_BITSET_WORD_BMSK);
		__word = __self[__maxword] & __mask;
		if (__word != __mask)
			return (__maxword << __HYBRID_BITSET_WORD_SHFT) + __HYBRID_BITSET_WORD_CTO(__word);
	}
	return __maxbitno + 1;
}

/* Find the first bitno within [startbitno,endbitno) that is off and return
 * its  index.  If no  such bit  exists,  return some  value `>= endbitno'. */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_nffc)(__hybrid_bitset_t const *__restrict __self,
                                    __SIZE_TYPE__ __startbitno, __SIZE_TYPE__ __endbitno) {
	__SIZE_TYPE__ __maxbitno;
	if __likely(!__hybrid_overflow_usub(__endbitno, 1, &__maxbitno))
		return __hybrid_bitset_nffc_r(__self, __startbitno, __maxbitno);
	return 0; /* Because `__endbitno' must be `0' */
}

/* Find the last bitno within [minbitno,maxbitno] that is on and return
 * its  index. If no  such bit exists,  return some value `> maxbitno'. */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_nfls_r)(__hybrid_bitset_t const *__restrict __self,
                                      __SIZE_TYPE__ __minbitno, __SIZE_TYPE__ __maxbitno) {
	__SIZE_TYPE__ __minword = __HYBRID_BITSET_WORD(__minbitno);
	__SIZE_TYPE__ __maxword = __HYBRID_BITSET_WORD(__maxbitno);
	if (__minword >= __maxword) {
		if __likely(__minbitno <= __maxbitno) {
			__hybrid_bitset_t __word;
			__word = __self[__maxword] & (__HYBRID_BITSET_LO_MASKOU(__minbitno & __HYBRID_BITSET_WORD_BMSK) &
			                              __HYBRID_BITSET_LO_MASKIN_P1(__maxbitno & __HYBRID_BITSET_WORD_BMSK));
			if (__word != 0) {
				__word <<= __HYBRID_BITSET_WORD_BMSK - (__maxbitno & __HYBRID_BITSET_WORD_BMSK);
				return (__SIZE_TYPE__)(__maxbitno - __HYBRID_BITSET_WORD_CLZ(__word));
			}
		}
	} else {
		__SIZE_TYPE__ __i;
		__hybrid_bitset_t __word;
		__word = __self[__maxword] & __HYBRID_BITSET_LO_MASKIN_P1(__maxbitno & __HYBRID_BITSET_WORD_BMSK);
		if (__word != 0) {
			__word <<= __HYBRID_BITSET_WORD_BMSK - (__maxbitno & __HYBRID_BITSET_WORD_BMSK);
			return (__SIZE_TYPE__)(__maxbitno - __HYBRID_BITSET_WORD_CLZ(__word));
		}
		for (__i = __maxword - 1; __i > __minword; --__i) {
			__word = __self[__i];
			if (__word != 0) {
				return (__i << __HYBRID_BITSET_WORD_SHFT) +
				       (__HYBRID_BITSET_WORD_BMSK - __HYBRID_BITSET_WORD_CLZ(__word));
			}
		}
		__word = __self[__minword] & __HYBRID_BITSET_LO_MASKOU(__minbitno & __HYBRID_BITSET_WORD_BMSK);
		if (__word != 0) {
			return (__minword << __HYBRID_BITSET_WORD_SHFT) +
			       (__HYBRID_BITSET_WORD_BMSK - __HYBRID_BITSET_WORD_CLZ(__word));
		}
	}
	return __maxbitno + 1;
}

/* Find the last bitno within [startbitno,endbitno) that is on and return
 * its index. If  no such  bit exists, return  some value  `>= endbitno'. */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_nfls)(__hybrid_bitset_t const *__restrict __self,
                                    __SIZE_TYPE__ __startbitno, __SIZE_TYPE__ __endbitno) {
	__SIZE_TYPE__ __maxbitno;
	if __likely(!__hybrid_overflow_usub(__endbitno, 1, &__maxbitno))
		return __hybrid_bitset_nfls_r(__self, __startbitno, __maxbitno);
	return 0; /* Because `__endbitno' must be `0' */
}

/* Find the last bitno within [minbitno,maxbitno] that is off and return
 * its index. If  no such  bit exists, return  some value  `> maxbitno'. */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_nflc_r)(__hybrid_bitset_t const *__restrict __self,
                                      __SIZE_TYPE__ __minbitno, __SIZE_TYPE__ __maxbitno) {
	__SIZE_TYPE__ __minword = __HYBRID_BITSET_WORD(__minbitno);
	__SIZE_TYPE__ __maxword = __HYBRID_BITSET_WORD(__maxbitno);
	if (__minword >= __maxword) {
		if __likely(__minbitno <= __maxbitno) {
			__hybrid_bitset_t __word;
			__hybrid_bitset_t __mask;
			__mask = (__HYBRID_BITSET_LO_MASKOU(__minbitno & __HYBRID_BITSET_WORD_BMSK) &
			          __HYBRID_BITSET_LO_MASKIN_P1(__maxbitno & __HYBRID_BITSET_WORD_BMSK));
			__word = __self[__maxword] & __mask;
			if (__word != __mask) {
				__word <<= __HYBRID_BITSET_WORD_BMSK - (__maxbitno & __HYBRID_BITSET_WORD_BMSK);
				return (__SIZE_TYPE__)(__maxbitno - __HYBRID_BITSET_WORD_CLO(__word));
			}
		}
	} else {
		__SIZE_TYPE__ __i;
		__hybrid_bitset_t __mask;
		__hybrid_bitset_t __word;
		__mask = __HYBRID_BITSET_LO_MASKIN_P1(__maxbitno & __HYBRID_BITSET_WORD_BMSK);
		__word = __self[__maxword] & __mask;
		if (__word != __mask) {
			__word <<= __HYBRID_BITSET_WORD_BMSK - (__maxbitno & __HYBRID_BITSET_WORD_BMSK);
			return (__SIZE_TYPE__)(__maxbitno - __HYBRID_BITSET_WORD_CLO(__word));
		}
		for (__i = __maxword - 1; __i > __minword; --__i) {
			__word = __self[__i];
			if (__word != __HYBRID_BITSET_WORD_BMAX) {
				return (__i << __HYBRID_BITSET_WORD_SHFT) +
				       (__HYBRID_BITSET_WORD_BMSK - __HYBRID_BITSET_WORD_CLO(__word));
			}
		}
		__mask = __HYBRID_BITSET_LO_MASKOU(__minbitno & __HYBRID_BITSET_WORD_BMSK);
		__word = __self[__minword] & __mask;
		if (__word != __mask) {
			return (__minword << __HYBRID_BITSET_WORD_SHFT) +
			       (__HYBRID_BITSET_WORD_BMSK - __HYBRID_BITSET_WORD_CLO(__word));
		}
	}
	return __maxbitno + 1;
}

/* Find the last bitno within [startbitno,endbitno) that is off and return
 * its index.  If no  such bit  exists, return  some value  `>= endbitno'. */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_nflc)(__hybrid_bitset_t const *__restrict __self,
                                    __SIZE_TYPE__ __startbitno, __SIZE_TYPE__ __endbitno) {
	__SIZE_TYPE__ __maxbitno;
	if __likely(!__hybrid_overflow_usub(__endbitno, 1, &__maxbitno))
		return __hybrid_bitset_nflc_r(__self, __startbitno, __maxbitno);
	return 0; /* Because `__endbitno' must be `0' */
}


/* Check if the bitset contains any 1-elements */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__NOTHROW_NCX(__hybrid_bitset_anyset)(__hybrid_bitset_t const *__restrict __self, __SIZE_TYPE__ __n_bits) {
	__SIZE_TYPE__ __i;
	for (__i = 0; __i < (__n_bits >> __HYBRID_BITSET_WORD_SHFT); ++__i) {
		if (__self[__i] != 0)
			return 1;
	}
	if (__n_bits & __HYBRID_BITSET_WORD_BMSK) {
		if (__self[__i] & ((1 << (__n_bits & __HYBRID_BITSET_WORD_BMSK)) - 1))
			return 1;
	}
	return 0;
}


/* Check if the bitset contains only 1-elements */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__NOTHROW_NCX(__hybrid_bitset_allset)(__hybrid_bitset_t const *__restrict __self, __SIZE_TYPE__ __n_bits) {
	__SIZE_TYPE__ __i;
	for (__i = 0; __i < (__n_bits >> __HYBRID_BITSET_WORD_SHFT); ++__i) {
		if (__self[__i] != __HYBRID_BITSET_WORD_BMAX)
			return 0;
	}
	if (__n_bits & __HYBRID_BITSET_WORD_BMSK) {
		__hybrid_bitset_t __mask = ((1 << (__n_bits & __HYBRID_BITSET_WORD_BMSK)) - 1);
		if ((__self[__i] & __mask) != __mask)
			return 0;
	}
	return 1;
}


/* Check if the bitset contains any 1-elements within the given range */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__NOTHROW_NCX(__hybrid_bitset_nanyset_r)(__hybrid_bitset_t const *__restrict __self,
                                         __SIZE_TYPE__ __minbitno, __SIZE_TYPE__ __maxbitno) {
	__SIZE_TYPE__ __minword = __HYBRID_BITSET_WORD(__minbitno);
	__SIZE_TYPE__ __maxword = __HYBRID_BITSET_WORD(__maxbitno);
	if (__minword >= __maxword) {
		if (__self[__maxword] & (__HYBRID_BITSET_LO_MASKOU(__minbitno & __HYBRID_BITSET_WORD_BMSK) &
		                         __HYBRID_BITSET_LO_MASKIN_P1(__maxbitno & __HYBRID_BITSET_WORD_BMSK)))
			return 1;
	} else {
		__SIZE_TYPE__ __i;
		if (__self[__minword] & __HYBRID_BITSET_LO_MASKOU(__minbitno & __HYBRID_BITSET_WORD_BMSK))
			return 1;
		for (__i = __minword + 1; __i < __maxword; ++__i) {
			if (__self[__i] != 0)
				return 1;
		}
		if (__self[__maxword] & __HYBRID_BITSET_LO_MASKIN_P1(__maxbitno & __HYBRID_BITSET_WORD_BMSK))
			return 1;
	}
	return 0;
}

/* Check if the bitset contains any 1-elements within the given range */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__NOTHROW_NCX(__hybrid_bitset_nanyset)(__hybrid_bitset_t const *__restrict __self,
                                       __SIZE_TYPE__ __startbitno, __SIZE_TYPE__ __endbitno) {
	__SIZE_TYPE__ __maxbitno;
	if __likely(!__hybrid_overflow_usub(__endbitno, 1, &__maxbitno))
		return __hybrid_bitset_nanyset_r(__self, __startbitno, __maxbitno);
	return 0;
}

/* Check if the bitset contains only 1-elements within the given range */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__NOTHROW_NCX(__hybrid_bitset_nallset_r)(__hybrid_bitset_t const *__restrict __self,
                                         __SIZE_TYPE__ __minbitno, __SIZE_TYPE__ __maxbitno) {
	__SIZE_TYPE__ __minword = __HYBRID_BITSET_WORD(__minbitno);
	__SIZE_TYPE__ __maxword = __HYBRID_BITSET_WORD(__maxbitno);
	if (__minword >= __maxword) {
		__hybrid_bitset_t __mask = (__HYBRID_BITSET_LO_MASKOU(__minbitno & __HYBRID_BITSET_WORD_BMSK) &
		                            __HYBRID_BITSET_LO_MASKIN_P1(__maxbitno & __HYBRID_BITSET_WORD_BMSK));
		if ((__self[__maxword] & __mask) != __mask)
			return 0;
	} else {
		__SIZE_TYPE__ __i;
		__hybrid_bitset_t __mask;
		__mask = __HYBRID_BITSET_LO_MASKOU(__minbitno & __HYBRID_BITSET_WORD_BMSK);
		if ((__self[__minword] & __mask) != __mask)
			return 0;
		for (__i = __minword + 1; __i < __maxword; ++__i) {
			if (__self[__i] != __HYBRID_BITSET_WORD_BMAX)
				return 0;
		}
		__mask = __HYBRID_BITSET_LO_MASKIN_P1(__maxbitno & __HYBRID_BITSET_WORD_BMSK);
		if ((__self[__maxword] & __mask) != __mask)
			return 0;
	}
	return 1;
}

/* Check if the bitset contains only 1-elements within the given range */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__NOTHROW_NCX(__hybrid_bitset_nallset)(__hybrid_bitset_t const *__restrict __self,
                                       __SIZE_TYPE__ __startbitno, __SIZE_TYPE__ __endbitno) {
	__SIZE_TYPE__ __maxbitno;
	if __likely(!__hybrid_overflow_usub(__endbitno, 1, &__maxbitno))
		return __hybrid_bitset_nallset_r(__self, __startbitno, __maxbitno);
	return 1;
}


/* Returns the # of 1-bits in `self' */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_popcount)(__hybrid_bitset_t const *__restrict __self, __SIZE_TYPE__ __n_bits) {
	__SIZE_TYPE__ __i, __result = 0;
	for (__i = 0; __i < (__n_bits >> __HYBRID_BITSET_WORD_SHFT); ++__i)
		__result += __HYBRID_BITSET_WORD_POPCOUNT(__self[__i]);
	if (__n_bits & __HYBRID_BITSET_WORD_BMSK) {
		__hybrid_bitset_t __mask = ((1 << (__n_bits & __HYBRID_BITSET_WORD_BMSK)) - 1);
		__result += __HYBRID_BITSET_WORD_POPCOUNT(__self[__i] & __mask);
	}
	return __result;
}

/* Returns the # of 1-bits within the given range */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_npopcount_r)(__hybrid_bitset_t const *__restrict __self,
                                           __SIZE_TYPE__ __minbitno, __SIZE_TYPE__ __maxbitno) {
	__SIZE_TYPE__ __result;
	__SIZE_TYPE__ __minword = __HYBRID_BITSET_WORD(__minbitno);
	__SIZE_TYPE__ __maxword = __HYBRID_BITSET_WORD(__maxbitno);
	if (__minword >= __maxword) {
		__hybrid_bitset_t __mask = (__HYBRID_BITSET_LO_MASKOU(__minbitno & __HYBRID_BITSET_WORD_BMSK) &
		                            __HYBRID_BITSET_LO_MASKIN_P1(__maxbitno & __HYBRID_BITSET_WORD_BMSK));
		__result = __HYBRID_BITSET_WORD_POPCOUNT(__self[__maxword] & __mask);
	} else {
		__SIZE_TYPE__ __i;
		__result = __HYBRID_BITSET_WORD_POPCOUNT(__self[__minword] & __HYBRID_BITSET_LO_MASKOU(__minbitno & __HYBRID_BITSET_WORD_BMSK));
		for (__i = __minword + 1; __i < __maxword; ++__i)
			__result += __HYBRID_BITSET_WORD_POPCOUNT(__self[__i]);
		__result += __HYBRID_BITSET_WORD_POPCOUNT(__self[__maxword] & __HYBRID_BITSET_LO_MASKIN_P1(__maxbitno & __HYBRID_BITSET_WORD_BMSK));
	}
	return __result;
}

/* Returns the # of 1-bits within the given range */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_npopcount)(__hybrid_bitset_t const *__restrict __self,
                                         __SIZE_TYPE__ __startbitno, __SIZE_TYPE__ __endbitno) {
	__SIZE_TYPE__ __maxbitno;
	if __likely(!__hybrid_overflow_usub(__endbitno, 1, &__maxbitno))
		return __hybrid_bitset_npopcount_r(__self, __startbitno, __maxbitno);
	return 0;
}

/* Count-leading-zeroes (returns ">= n_bits" when `self' doesn't contain any set bits) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_clz)(__hybrid_bitset_t const *__restrict __self, __SIZE_TYPE__ __n_bits) {
	__SIZE_TYPE__ __result = 0;
	__SIZE_TYPE__ __endword = __HYBRID_BITSET_WORD(__n_bits + __HYBRID_BITSET_WORD_BMSK);
	if (__n_bits & __HYBRID_BITSET_WORD_BMSK) {
		__hybrid_bitset_t __word;
		--__endword;
		__word = __self[__endword];
		__word <<= __HYBRID_BITSET_WORD_BITS - (__n_bits & __HYBRID_BITSET_WORD_BMSK);
		if (__word != 0)
			return __HYBRID_BITSET_WORD_CLZ(__word);
		__result = __n_bits & __HYBRID_BITSET_WORD_BMSK;
	}
	if (__endword > 0) {
		__hybrid_bitset_t __word;
		for (;;) {
			if (__endword <= 0)
				return __n_bits;
			--__endword;
			__word = __self[__endword];
			if (__word != 0)
				break;
			__result += __HYBRID_BITSET_WORD_BITS;
		}
		__result += __HYBRID_BITSET_WORD_CLZ(__word);
	}
	return __result;
}

/* Count-trailing-zeroes (returns ">= n_bits" when `self' doesn't contain any set bits) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_ctz)(__hybrid_bitset_t const *__restrict __self, __SIZE_TYPE__ __n_bits) {
	__hybrid_bitset_t __word;
	__SIZE_TYPE__ __result = 0;
	for (;;) {
		if (__n_bits < __HYBRID_BITSET_WORD_BITS)
			break;
		__word = *__self;
		if (__word != 0)
			return __result + __HYBRID_BITSET_WORD_CTZ(__word);
		__result += __HYBRID_BITSET_WORD_BITS;
		++__self;
	}
	if (__n_bits) {
		__word = *__self & (((__hybrid_bitset_t)1 << (__n_bits /*& __HYBRID_BITSET_WORD_BMSK*/)) - 1);
		__result += __HYBRID_BITSET_WORD_CTZ(__word);
	}
	return __result;
}

/* Count-leading-zeroes (hard undefined behavior when `self' doesn't contain any set bits) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_rawclz)(__hybrid_bitset_t const *__restrict __self, __SIZE_TYPE__ __n_bits) {
	__hybrid_bitset_t __word;
	__SIZE_TYPE__ __result  = 0;
	__SIZE_TYPE__ __endword = __HYBRID_BITSET_WORD(__n_bits + __HYBRID_BITSET_WORD_BMSK);
	if (__n_bits & __HYBRID_BITSET_WORD_BMSK) {
		--__endword;
		__word = __self[__endword];
		__word <<= __HYBRID_BITSET_WORD_BITS - (__n_bits & __HYBRID_BITSET_WORD_BMSK);
		if (__word != 0)
			return __HYBRID_BITSET_WORD_CLZ(__word);
		__result = __n_bits & __HYBRID_BITSET_WORD_BMSK;
	}
	for (;;) {
		__hybrid_assert(__endword > 0);
		--__endword;
		__word = __self[__endword];
		if (__word != 0)
			break;
		__result += __HYBRID_BITSET_WORD_BITS;
	}
	__result += __HYBRID_BITSET_WORD_CLZ(__word);
	return __result;
}

/* Count-trailing-zeroes (hard undefined behavior when `self' doesn't contain any set bits) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_rawctz)(__hybrid_bitset_t const *__restrict __self) {
	__SIZE_TYPE__ __result = 0;
	for (; *__self == 0; ++__self)
		__result += __HYBRID_BITSET_WORD_BITS;
	return __result + __HYBRID_BITSET_WORD_CTZ(*__self);
}


#define __hybrid_bitset_ncopy0(dst, src, src_startbitno, n_bits) \
	__hybrid_bitset_ncopy(dst, 0, src, src_startbitno, n_bits)

/* Take "n_bits" from "src:src_startbitno" and store them to "dst:dst_startbitno".
 * NOTE: Overlap is allowed! */
__LOCAL __ATTR_NONNULL((1, 3)) void
(__hybrid_bitset_ncopy)(__hybrid_bitset_t *__dst, __SIZE_TYPE__ __dst_startbitno,
                        __hybrid_bitset_t const *__src, __SIZE_TYPE__ __src_startbitno,
                        __SIZE_TYPE__ __n_bits) {
	if (__dst_startbitno > __HYBRID_BITSET_WORD_BMSK) {
		__dst += __dst_startbitno >> __HYBRID_BITSET_WORD_SHFT;
		__dst_startbitno &= __HYBRID_BITSET_WORD_BMSK;
	}
	if (__src_startbitno > __HYBRID_BITSET_WORD_BMSK) {
		__src += __src_startbitno >> __HYBRID_BITSET_WORD_SHFT;
		__src_startbitno &= __HYBRID_BITSET_WORD_BMSK;
	}
	__hybrid_assert(__dst_startbitno <= __HYBRID_BITSET_WORD_BMSK);
	__hybrid_assert(__src_startbitno <= __HYBRID_BITSET_WORD_BMSK);
	if (__src_startbitno == __dst_startbitno) {
		__SIZE_TYPE__ __whole_words;
		if (__dst_startbitno) {
			__SIZE_TYPE__ __copy;
			__hybrid_bitset_t __mask;
			__copy = __HYBRID_BITSET_WORD_BITS - __dst_startbitno;
			if (__copy >= __n_bits) {
				/* Copy only within the first word. */
				__mask = (((__hybrid_bitset_t)1 << __n_bits) - 1) << __dst_startbitno;
				*__dst = (*__src & __mask) | (*__dst & ~__mask);
				return;
			}
			__mask = __HYBRID_BITSET_HI_MASKIN(__copy);
			*__dst = (*__src & __mask) | (*__dst & ~__mask);
			++__dst;
			++__src;
			__n_bits -= __copy;
		}
		__whole_words = __n_bits >> __HYBRID_BITSET_WORD_SHFT;
		__HYBRID_BITSET_WORD_MEMMOVE(__dst, __src, __whole_words);
		if (__n_bits & __HYBRID_BITSET_WORD_BMSK) {
			__hybrid_bitset_t __mask;
			__dst += __whole_words;
			__src += __whole_words;
			__mask = __HYBRID_BITSET_LO_MASKIN(__n_bits & __HYBRID_BITSET_WORD_BMSK);
			*__dst = (*__src & __mask) | (*__dst & ~__mask);
		}
	} else {
		/* Bitsets aren't aligned -> copy 1 bit at-a-time */
		__SIZE_TYPE__ __i;
		if (__dst <= __src) {
			for (__i = 0; __i < __n_bits; ++__i) {
				if (__hybrid_bitset_test(__src, __src_startbitno + __i)) {
					__hybrid_bitset_set(__dst, __dst_startbitno + __i);
				} else {
					__hybrid_bitset_clear(__dst, __dst_startbitno + __i);
				}
			}
		} else {
			__i = __n_bits;
			while (__i) {
				--__i;
				if (__hybrid_bitset_test(__src, __src_startbitno + __i)) {
					__hybrid_bitset_set(__dst, __dst_startbitno + __i);
				} else {
					__hybrid_bitset_clear(__dst, __dst_startbitno + __i);
				}
			}
		}
	}
}


/* Check if "n_bits" at "lhs:lhs_startbitno" and "rhs:rhs_startbitno" are equal. */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __BOOL
(__hybrid_bitset_ncmpeq)(__hybrid_bitset_t const *__lhs, __SIZE_TYPE__ __lhs_startbitno,
                         __hybrid_bitset_t const *__rhs, __SIZE_TYPE__ __rhs_startbitno,
                         __SIZE_TYPE__ __n_bits) {
	if (__lhs_startbitno > __HYBRID_BITSET_WORD_BMSK) {
		__lhs += __lhs_startbitno >> __HYBRID_BITSET_WORD_SHFT;
		__lhs_startbitno &= __HYBRID_BITSET_WORD_BMSK;
	}
	if (__rhs_startbitno > __HYBRID_BITSET_WORD_BMSK) {
		__rhs += __rhs_startbitno >> __HYBRID_BITSET_WORD_SHFT;
		__rhs_startbitno &= __HYBRID_BITSET_WORD_BMSK;
	}
	__hybrid_assert(__lhs_startbitno <= __HYBRID_BITSET_WORD_BMSK);
	__hybrid_assert(__rhs_startbitno <= __HYBRID_BITSET_WORD_BMSK);
	if (__rhs_startbitno == __lhs_startbitno) {
		__SIZE_TYPE__ __whole_words;
		if (__lhs_startbitno) {
			__SIZE_TYPE__ __copy;
			__hybrid_bitset_t __mask;
			__copy = __HYBRID_BITSET_WORD_BITS - __lhs_startbitno;
			if (__copy >= __n_bits) {
				/* Copy only within the first word. */
				__mask = (((__hybrid_bitset_t)1 << __n_bits) - 1) << __lhs_startbitno;
				return (*__lhs & __mask) == (*__rhs & __mask);
			}
			__mask = __HYBRID_BITSET_HI_MASKIN(__copy);
			if ((*__lhs & __mask) != (*__rhs & __mask))
				return 0;
			++__lhs;
			++__rhs;
			__n_bits -= __copy;
		}
		__whole_words = __n_bits >> __HYBRID_BITSET_WORD_SHFT;
		if (__HYBRID_BITSET_WORD_BCMP(__lhs, __rhs, __whole_words) != 0)
			return 0;
		if (__n_bits & __HYBRID_BITSET_WORD_BMSK) {
			__hybrid_bitset_t __mask;
			__lhs += __whole_words;
			__rhs += __whole_words;
			__mask = __HYBRID_BITSET_LO_MASKIN(__n_bits & __HYBRID_BITSET_WORD_BMSK);
			if ((*__lhs & __mask) != (*__rhs & __mask))
				return 0;
		}
	} else {
		/* Bitsets aren't aligned -> cmopare 1 bit at-a-time */
		__SIZE_TYPE__ __i;
		for (__i = 0; __i < __n_bits; ++__i) {
			if ((!!__hybrid_bitset_test(__lhs, __lhs_startbitno + __i)) !=
			    (!!__hybrid_bitset_test(__rhs, __rhs_startbitno + __i)))
				return 0;
		}
	}
	return 1;
}

/* Check if all 1-bits from `lhs:lhs_startbitno...+=n_bits' also appear in `rhs:rhs_startbitno...+=n_bits'.
 * This function implements the a is-subset-or-equal check. */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __BOOL
(__hybrid_bitset_ncmple)(__hybrid_bitset_t const *__lhs, __SIZE_TYPE__ __lhs_startbitno,
                         __hybrid_bitset_t const *__rhs, __SIZE_TYPE__ __rhs_startbitno,
                         __SIZE_TYPE__ __n_bits) {
	if (__lhs_startbitno > __HYBRID_BITSET_WORD_BMSK) {
		__lhs += __lhs_startbitno >> __HYBRID_BITSET_WORD_SHFT;
		__lhs_startbitno &= __HYBRID_BITSET_WORD_BMSK;
	}
	if (__rhs_startbitno > __HYBRID_BITSET_WORD_BMSK) {
		__rhs += __rhs_startbitno >> __HYBRID_BITSET_WORD_SHFT;
		__rhs_startbitno &= __HYBRID_BITSET_WORD_BMSK;
	}
	__hybrid_assert(__lhs_startbitno <= __HYBRID_BITSET_WORD_BMSK);
	__hybrid_assert(__rhs_startbitno <= __HYBRID_BITSET_WORD_BMSK);
	if (__rhs_startbitno == __lhs_startbitno) {
		__SIZE_TYPE__ __i, __whole_words;
		if (__lhs_startbitno) {
			__SIZE_TYPE__ __copy;
			__hybrid_bitset_t __mask, __lval, __rval;
			__copy = __HYBRID_BITSET_WORD_BITS - __lhs_startbitno;
			if (__copy >= __n_bits) {
				/* Copy only within the first word. */
				__mask = (((__hybrid_bitset_t)1 << __n_bits) - 1) << __lhs_startbitno;
				__lval = *__lhs & __mask;
				__rval = *__rhs & __mask;
				return (__lval & __rval) == __lval;
			}
			__mask = __HYBRID_BITSET_HI_MASKIN(__copy);
			__lval = *__lhs & __mask;
			__rval = *__rhs & __mask;
			if ((__lval & __rval) != __lval)
				return 0;
			++__lhs;
			++__rhs;
			__n_bits -= __copy;
		}
		__whole_words = __n_bits >> __HYBRID_BITSET_WORD_SHFT;
		for (__i = 0; __i < __whole_words; ++__i) {
			__hybrid_bitset_t __lval = *__lhs;
			__hybrid_bitset_t __rval = *__rhs;
			if ((__lval & __rval) != __lval)
				return 0;
			++__lhs;
			++__rhs;
		}
		if (__n_bits & __HYBRID_BITSET_WORD_BMSK) {
			__hybrid_bitset_t __mask, __lval, __rval;
			__mask = __HYBRID_BITSET_LO_MASKIN(__n_bits & __HYBRID_BITSET_WORD_BMSK);
			__lval = *__lhs & __mask;
			__rval = *__rhs & __mask;
			if ((__lval & __rval) != __lval)
				return 0;
		}
	} else {
		/* Bitsets aren't aligned -> compare 1 bit at-a-time */
		__SIZE_TYPE__ __i;
		for (__i = 0; __i < __n_bits; ++__i) {
			if ((__hybrid_bitset_test(__lhs, __lhs_startbitno + __i)) &&
			    !__hybrid_bitset_test(__rhs, __rhs_startbitno + __i))
				return 0;
		}
	}
	return 1;
}


/* All of the other compare operator */
#define __hybrid_bitset_ncmpne(lhs, lhs_startbitno, rhs, rhs_startbitno, n_bits) \
	(!__hybrid_bitset_ncmpeq(rhs, rhs_startbitno, lhs, lhs_startbitno, n_bits))
#define __hybrid_bitset_ncmpge(lhs, lhs_startbitno, rhs, rhs_startbitno, n_bits) \
	__hybrid_bitset_ncmple(rhs, rhs_startbitno, lhs, lhs_startbitno, n_bits)
#define __hybrid_bitset_ncmplo(lhs, lhs_startbitno, rhs, rhs_startbitno, n_bits) \
	(!__hybrid_bitset_ncmpge(lhs, lhs_startbitno, rhs, rhs_startbitno, n_bits))
#define __hybrid_bitset_ncmpgr(lhs, lhs_startbitno, rhs, rhs_startbitno, n_bits) \
	(!__hybrid_bitset_ncmple(lhs, lhs_startbitno, rhs, rhs_startbitno, n_bits))

#define __hybrid_bitset_ncmpeq0(lhs, rhs, rhs_startbitno, n_bits) __hybrid_bitset_ncmpeq(lhs, 0, rhs, rhs_startbitno, n_bits)
#define __hybrid_bitset_ncmpne0(lhs, rhs, rhs_startbitno, n_bits) __hybrid_bitset_ncmpne(lhs, 0, rhs, rhs_startbitno, n_bits)
#define __hybrid_bitset_ncmplo0(lhs, rhs, rhs_startbitno, n_bits) __hybrid_bitset_ncmplo(lhs, 0, rhs, rhs_startbitno, n_bits)
#define __hybrid_bitset_ncmple0(lhs, rhs, rhs_startbitno, n_bits) __hybrid_bitset_ncmple(lhs, 0, rhs, rhs_startbitno, n_bits)
#define __hybrid_bitset_ncmpgr0(lhs, rhs, rhs_startbitno, n_bits) __hybrid_bitset_ncmpgr(lhs, 0, rhs, rhs_startbitno, n_bits)
#define __hybrid_bitset_ncmpge0(lhs, rhs, rhs_startbitno, n_bits) __hybrid_bitset_ncmpge(lhs, 0, rhs, rhs_startbitno, n_bits)


/* Possible values for `__hybrid_bitset_nbitop::op' */
#ifndef __HYBRID_BITSET_OP_AND
#define __HYBRID_BITSET_OP_AND 0
#define __HYBRID_BITSET_OP_OR  1
#define __HYBRID_BITSET_OP_XOR 2
#endif /* !__HYBRID_BITSET_OP_AND */

__LOCAL __ATTR_NONNULL((1, 2)) void
(__hybrid_private_bitset_bitop)(__hybrid_bitset_t *__dst,
                                __hybrid_bitset_t const *__src,
                                __hybrid_bitset_t __mask, unsigned int __op) {
	switch (__op) {
	case __HYBRID_BITSET_OP_AND:
		*__dst &= (*__src & __mask) | ~__mask;
		break;
	case __HYBRID_BITSET_OP_OR:
		*__dst |= (*__src & __mask);
		break;
	case __HYBRID_BITSET_OP_XOR:
		*__dst ^= (*__src & __mask);
		break;
	default: __builtin_unreachable();
	}
}

#define __hybrid_bitset_nbitop0(dst, src, src_startbitno, n_bits, op) \
	__hybrid_bitset_nbitop(dst, 0, src, src_startbitno, n_bits, op)

/* Perform  a  bit-operation  "op"  on  the  "n_bits"  from  "src:src_startbitno",
 * together with "dst:dst_startbitno", storing the result at "dst:dst_startbitno".
 * NOTE: Overlap is allowed!
 * @param: op: One of `__HYBRID_BITSET_OP_*' */
__LOCAL __ATTR_NONNULL((1, 3)) void
(__hybrid_bitset_nbitop)(__hybrid_bitset_t *__dst, __SIZE_TYPE__ __dst_startbitno,
                         __hybrid_bitset_t const *__src, __SIZE_TYPE__ __src_startbitno,
                         __SIZE_TYPE__ __n_bits, unsigned int __op) {
	if (__dst_startbitno > __HYBRID_BITSET_WORD_BMSK) {
		__dst += __dst_startbitno >> __HYBRID_BITSET_WORD_SHFT;
		__dst_startbitno &= __HYBRID_BITSET_WORD_BMSK;
	}
	if (__src_startbitno > __HYBRID_BITSET_WORD_BMSK) {
		__src += __src_startbitno >> __HYBRID_BITSET_WORD_SHFT;
		__src_startbitno &= __HYBRID_BITSET_WORD_BMSK;
	}
	__hybrid_assert(__dst_startbitno <= __HYBRID_BITSET_WORD_BMSK);
	__hybrid_assert(__src_startbitno <= __HYBRID_BITSET_WORD_BMSK);
	if (__src_startbitno == __dst_startbitno) {
		__SIZE_TYPE__ __whole_words, __i;
		if (__dst_startbitno) {
			__SIZE_TYPE__ __copy;
			__hybrid_bitset_t __mask;
			__copy = __HYBRID_BITSET_WORD_BITS - __dst_startbitno;
			if (__copy >= __n_bits) {
				/* Operate only within the first word. */
				__mask = (((__hybrid_bitset_t)1 << __n_bits) - 1) << __dst_startbitno;
				__hybrid_private_bitset_bitop(__dst, __src, __mask, __op);
				return;
			}
			__mask = __HYBRID_BITSET_HI_MASKIN(__copy);
			__hybrid_private_bitset_bitop(__dst, __src, __mask, __op);
			++__dst;
			++__src;
			__n_bits -= __copy;
		}
		__whole_words = __n_bits >> __HYBRID_BITSET_WORD_SHFT;
		if (__dst <= __src) {
			switch (__op) {
			case __HYBRID_BITSET_OP_AND:
				for (__i = 0; __i < __whole_words; ++__i)
					__dst[__i] &= __src[__i];
				break;
			case __HYBRID_BITSET_OP_OR:
				for (__i = 0; __i < __whole_words; ++__i)
					__dst[__i] |= __src[__i];
				break;
			case __HYBRID_BITSET_OP_XOR:
				for (__i = 0; __i < __whole_words; ++__i)
					__dst[__i] ^= __src[__i];
				break;
			default: __builtin_unreachable();
			}
		} else {
			__i = __whole_words;
			switch (__op) {
			case __HYBRID_BITSET_OP_AND:
				while (__i) {
					--__i;
					__dst[__i] &= __src[__i];
				}
				break;
			case __HYBRID_BITSET_OP_OR:
				while (__i) {
					--__i;
					__dst[__i] |= __src[__i];
				}
				break;
			case __HYBRID_BITSET_OP_XOR:
				while (__i) {
					--__i;
					__dst[__i] ^= __src[__i];
				}
				break;
			default: __builtin_unreachable();
			}
		}
		if (__n_bits & __HYBRID_BITSET_WORD_BMSK) {
			__hybrid_bitset_t __mask;
			__dst += __whole_words;
			__src += __whole_words;
			__mask = __HYBRID_BITSET_LO_MASKIN(__n_bits & __HYBRID_BITSET_WORD_BMSK);
			__hybrid_private_bitset_bitop(__dst, __src, __mask, __op);
		}
	} else {
		/* Bitsets aren't aligned -> copy 1 bit at-a-time */
		__SIZE_TYPE__ __i;
		if (__dst <= __src) {
			switch (__op) {
			case __HYBRID_BITSET_OP_AND:
				for (__i = 0; __i < __n_bits; ++__i) {
					if (!__hybrid_bitset_test(__src, __src_startbitno + __i))
						__hybrid_bitset_clear(__dst, __dst_startbitno + __i);
				}
				break;
			case __HYBRID_BITSET_OP_OR:
				for (__i = 0; __i < __n_bits; ++__i) {
					if (__hybrid_bitset_test(__src, __src_startbitno + __i))
						__hybrid_bitset_set(__dst, __dst_startbitno + __i);
				}
				break;
			case __HYBRID_BITSET_OP_XOR:
				for (__i = 0; __i < __n_bits; ++__i) {
					if (__hybrid_bitset_test(__src, __src_startbitno + __i))
						__hybrid_bitset_flip(__dst, __dst_startbitno + __i);
				}
				break;
			default: __builtin_unreachable();
			}
		} else {
			__i = __n_bits;
			switch (__op) {
			case __HYBRID_BITSET_OP_AND:
				while (__i) {
					--__i;
					if (!__hybrid_bitset_test(__src, __src_startbitno + __i))
						__hybrid_bitset_clear(__dst, __dst_startbitno + __i);
				}
				break;
			case __HYBRID_BITSET_OP_OR:
				while (__i) {
					--__i;
					if (__hybrid_bitset_test(__src, __src_startbitno + __i))
						__hybrid_bitset_set(__dst, __dst_startbitno + __i);
				}
				break;
			case __HYBRID_BITSET_OP_XOR:
				while (__i) {
					--__i;
					if (__hybrid_bitset_test(__src, __src_startbitno + __i))
						__hybrid_bitset_flip(__dst, __dst_startbitno + __i);
				}
				break;
			default: __builtin_unreachable();
			}
		}
	}
}


__DECL_END
#endif /* __CC__ */

#endif /* !__GUARD_HYBRID___BITSET_H */
