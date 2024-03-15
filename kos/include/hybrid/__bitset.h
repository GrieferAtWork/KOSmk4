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

#include "__bit.h"
#include "__string.h"
#include "typecore.h"

#ifndef __HYBRID_BITSET_WORD_BITS
#define __HYBRID_BITSET_WORD_BITS __CHAR_BIT__
#endif /* !__HYBRID_BITSET_WORD_BITS */

#if __HYBRID_BITSET_WORD_BITS == 8
#define __hybrid_bitset_t             __UINT8_TYPE__
#define __HYBRID_BITSET_WORD_SIGN     __UINT8_C(0x80)
#define __HYBRID_BITSET_WORD_BMAX     __UINT8_C(0xff)
#define __HYBRID_BITSET_WORD_BMSK     7
#define __HYBRID_BITSET_WORD_SHFT     3
#define __HYBRID_BITSET_WORD_POPCOUNT __hybrid_popcount8
#define __HYBRID_BITSET_WORD_CTZ      __hybrid_ctz8
#define __HYBRID_BITSET_WORD_CLZ      __hybrid_clz8
#elif __HYBRID_BITSET_WORD_BITS == 16
#define __hybrid_bitset_t             __UINT16_TYPE__
#define __HYBRID_BITSET_WORD_SIGN     __UINT16_C(0x8000)
#define __HYBRID_BITSET_WORD_BMAX     __UINT16_C(0xffff)
#define __HYBRID_BITSET_WORD_BMSK     15
#define __HYBRID_BITSET_WORD_SHFT     4
#define __HYBRID_BITSET_WORD_POPCOUNT __hybrid_popcount16
#define __HYBRID_BITSET_WORD_CTZ      __hybrid_ctz16
#define __HYBRID_BITSET_WORD_CLZ      __hybrid_clz16
#elif __HYBRID_BITSET_WORD_BITS == 32
#define __hybrid_bitset_t             __UINT32_TYPE__
#define __HYBRID_BITSET_WORD_SIGN     __UINT32_C(0x80000000)
#define __HYBRID_BITSET_WORD_BMAX     __UINT32_C(0xffffffff)
#define __HYBRID_BITSET_WORD_BMSK     31
#define __HYBRID_BITSET_WORD_SHFT     5
#define __HYBRID_BITSET_WORD_POPCOUNT __hybrid_popcount32
#define __HYBRID_BITSET_WORD_CTZ      __hybrid_ctz32
#define __HYBRID_BITSET_WORD_CLZ      __hybrid_clz32
#elif __HYBRID_BITSET_WORD_BITS == 64
#define __hybrid_bitset_t             __UINT64_TYPE__
#define __HYBRID_BITSET_WORD_SIGN     __UINT64_C(0x8000000000000000)
#define __HYBRID_BITSET_WORD_BMAX     __UINT64_C(0xffffffffffffffff)
#define __HYBRID_BITSET_WORD_BMSK     63
#define __HYBRID_BITSET_WORD_SHFT     6
#define __HYBRID_BITSET_WORD_POPCOUNT __hybrid_popcount64
#define __HYBRID_BITSET_WORD_CTZ      __hybrid_ctz64
#define __HYBRID_BITSET_WORD_CLZ      __hybrid_clz64
#else /* __HYBRID_BITSET_WORD_BITS == ... */
#define __hybrid_bitset_t             __TYPEFOR_UINTIB()
#define __HYBRID_BITSET_WORD_SIGN     (__CCAST(__hybrid_bitset_t)1 << (__HYBRID_BITSET_WORD_BITS - 1))
#define __HYBRID_BITSET_WORD_BMAX     ((__CCAST(__hybrid_bitset_t)1 << __HYBRID_BITSET_WORD_BITS) - 1)
#define __HYBRID_BITSET_WORD_BMSK     (__HYBRID_BITSET_WORD_BITS - 1)
#define __HYBRID_BITSET_WORD_SHFT     log2(__HYBRID_BITSET_WORD_BITS)
#define __HYBRID_BITSET_WORD_POPCOUNT __hybrid_popcount
#define __HYBRID_BITSET_WORD_CTZ      __hybrid_ctz
#define __HYBRID_BITSET_WORD_CLZ      __hybrid_clz
#endif /* __HYBRID_BITSET_WORD_BITS != ... */

#define __HYBRID_BITSET_BYTE(bitno)      ((bitno) >> __HYBRID_BITSET_WORD_SHFT)
#define __HYBRID_BITSET_MASK(bitno)      (__CCAST(__hybrid_bitset_t) 1 << ((bitno) & __HYBRID_BITSET_WORD_BMSK))
#define __HYBRID_BITSET_LENGTHOF(n_bits) (((n_bits) + __HYBRID_BITSET_WORD_BMSK) >> __HYBRID_BITSET_WORD_SHFT)

#if __HYBRID_BITSET_WORD_BITS == __CHAR_BIT__
#define __HYBRID_BITSET_WORD_SIZE      1
#define __HYBRID_BITSET_SIZEOF(n_bits) __HYBRID_BITSET_LENGTHOF(n_bits)
#else /* __HYBRID_BITSET_WORD_BITS == __CHAR_BIT__ */
#define __HYBRID_BITSET_WORD_SIZE      (__HYBRID_BITSET_WORD_BITS / __CHAR_BIT__)
#define __HYBRID_BITSET_SIZEOF(n_bits) (__HYBRID_BITSET_LENGTHOF(n_bits) * __HYBRID_BITSET_WORD_SIZE)
#endif /* __HYBRID_BITSET_WORD_BITS != __CHAR_BIT__ */


#ifdef __CC__
__DECL_BEGIN

#define __hybrid_memset_one(p, n)  __hybrid_memset(p, __HYBRID_BITSET_WORD_BMAX, n)
#define __hybrid_memset_zero(p, n) __hybrid_bzero(p, n)

/* >> __hybrid_bitset_t __hybrid_bitset_decl(self, 256); */
#define __hybrid_bitset_decl(self, nbits) \
	((self)[__HYBRID_BITSET_LENGTHOF(nbits)])

/* >> bool __hybrid_bitset_test(__hybrid_bitset_t const *self, size_t bitno); */
#define __hybrid_bitset_test(self, bitno) \
	((self)[__HYBRID_BITSET_BYTE(bitno)] & __HYBRID_BITSET_MASK(bitno))

/* >> void __hybrid_bitset_set(__hybrid_bitset_t *self, size_t bitno); */
#define __hybrid_bitset_set(self, bitno) \
	(void)((self)[__HYBRID_BITSET_BYTE(bitno)] |= __HYBRID_BITSET_MASK(bitno))

/* >> void __hybrid_bitset_clear(__hybrid_bitset_t *self, size_t bitno); */
#define __hybrid_bitset_clear(self, bitno) \
	(void)((self)[__HYBRID_BITSET_BYTE(bitno)] &= ~__HYBRID_BITSET_MASK(bitno))

/* >> void __hybrid_bitset_flip(__hybrid_bitset_t *self, size_t bitno); */
#define __hybrid_bitset_flip(self, bitno) \
	(void)((self)[__HYBRID_BITSET_BYTE(bitno)] ^= __HYBRID_BITSET_MASK(bitno))


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



#define __HYBRID_PRIVATE_BITSET_NCLEAR_IMPL(self, minbyte, maxbyte, minbyte_bitno, maxbyte_bitno)      \
	if (minbyte >= maxbyte) {                                                                          \
		self[maxbyte] &= ((__HYBRID_BITSET_WORD_BMAX >> (__HYBRID_BITSET_WORD_BITS - minbyte_bitno)) | \
		                  (__HYBRID_BITSET_WORD_BMAX << (maxbyte_bitno + 1)));                         \
	} else {                                                                                           \
		self[minbyte] &= __HYBRID_BITSET_WORD_BMAX >> (__HYBRID_BITSET_WORD_BITS - minbyte_bitno);     \
		__hybrid_memset_zero(&self[minbyte + 1], maxbyte - (minbyte + 1));                             \
		self[maxbyte] &= __HYBRID_BITSET_WORD_BMAX << (maxbyte_bitno + 1);                             \
	}
#define __HYBRID_PRIVATE_BITSET_NSET_IMPL(self, minbyte, maxbyte, minbyte_bitno, maxbyte_bitno)        \
	if (minbyte >= maxbyte) {                                                                          \
		self[maxbyte] |= ((__HYBRID_BITSET_WORD_BMAX << minbyte_bitno) |                               \
		                  (__HYBRID_BITSET_WORD_BMAX >> (__HYBRID_BITSET_WORD_BMSK - maxbyte_bitno))); \
	} else {                                                                                           \
		self[minbyte] |= __HYBRID_BITSET_WORD_BMAX << minbyte_bitno;                                   \
		__hybrid_memset_one(&self[minbyte + 1], maxbyte - (minbyte + 1));                              \
		self[maxbyte] |= __HYBRID_BITSET_WORD_BMAX >> (__HYBRID_BITSET_WORD_BMSK - maxbyte_bitno);     \
	}
#define __HYBRID_PRIVATE_BITSET_NCLEAR(self, minbitno, maxbitno)                            \
	__register __SIZE_TYPE__ __hbs_minbyte = (__SIZE_TYPE__)__HYBRID_BITSET_BYTE(minbitno); \
	__register __SIZE_TYPE__ __hbs_maxbyte = (__SIZE_TYPE__)__HYBRID_BITSET_BYTE(maxbitno); \
	__HYBRID_PRIVATE_BITSET_NCLEAR_IMPL(self, __hbs_minbyte, __hbs_maxbyte, (minbitno & __HYBRID_BITSET_WORD_BMSK), (maxbitno & __HYBRID_BITSET_WORD_BMSK))
#define __HYBRID_PRIVATE_BITSET_NSET(self, minbitno, maxbitno)                              \
	__register __SIZE_TYPE__ __hbs_minbyte = (__SIZE_TYPE__)__HYBRID_BITSET_BYTE(minbitno); \
	__register __SIZE_TYPE__ __hbs_maxbyte = (__SIZE_TYPE__)__HYBRID_BITSET_BYTE(maxbitno); \
	__HYBRID_PRIVATE_BITSET_NSET_IMPL(self, __hbs_minbyte, __hbs_maxbyte, (minbitno & __HYBRID_BITSET_WORD_BMSK), (maxbitno & __HYBRID_BITSET_WORD_BMSK))

/* >> void __hybrid_bitset_nclear(__hybrid_bitset_t *self, size_t minbitno, size_t maxbitno);
 * Turn off bits [minbitno, maxbitno] (inclusive) in `self'
 * NOTE: When  `minbitno > maxbitno', the result  is weak undefined behavior,
 *       in that the way in which `self' is modified is undefined, though the
 *       function still guaranties that nothing but `self' gets modified. */
#ifdef __NO_XBLOCK
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_bitset_nclear)(__hybrid_bitset_t *__restrict __self,
                         __SIZE_TYPE__ __minbitno, __SIZE_TYPE__ __maxbitno) {
	__HYBRID_PRIVATE_BITSET_NCLEAR(__self, __minbitno, __maxbitno);
}
#else /* __NO_XBLOCK */
#define __hybrid_bitset_nclear(self, minbitno, maxbitno)                            \
	__XBLOCK({                                                                      \
		__register __hybrid_bitset_t *__bcn_self = (self);                          \
		__register __SIZE_TYPE__ __bnc_minbitno  = (__SIZE_TYPE__)(minbitno);       \
		__register __SIZE_TYPE__ __bnc_maxbitno  = (__SIZE_TYPE__)(maxbitno);       \
		__HYBRID_PRIVATE_BITSET_NCLEAR(__bcn_self, __bnc_minbitno, __bnc_maxbitno); \
		(void)0;                                                                    \
	})
#endif /* !__NO_XBLOCK */

/* >> void __hybrid_bitset_nset(__hybrid_bitset_t *self, size_t minbitno, size_t maxbitno);
 * Turn on bits [minbitno, maxbitno] (inclusive) in `self'
 * NOTE: When  `minbitno > maxbitno', the result  is weak undefined behavior,
 *       in that the way in which `self' is modified is undefined, though the
 *       function still guaranties that nothing but `self' gets modified. */
#ifdef __NO_XBLOCK
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_bitset_nset)(__hybrid_bitset_t *__restrict __self,
                       __SIZE_TYPE__ __minbitno, __SIZE_TYPE__ __maxbitno) {
	__HYBRID_PRIVATE_BITSET_NSET(__self, __minbitno, __maxbitno);
}
#else /* __NO_XBLOCK */
#define __hybrid_bitset_nset(self, minbitno, maxbitno)                            \
	__XBLOCK({                                                                    \
		__register __hybrid_bitset_t *__bns_self = (self);                        \
		__register __SIZE_TYPE__ __bns_minbitno  = (__SIZE_TYPE__)(minbitno);     \
		__register __SIZE_TYPE__ __bns_maxbitno  = (__SIZE_TYPE__)(maxbitno);     \
		__HYBRID_PRIVATE_BITSET_NSET(__bns_self, __bns_minbitno, __bns_maxbitno); \
		(void)0;                                                                  \
	})
#endif /* !__NO_XBLOCK */


#define __HYBRID_PRIVATE_BITSET_FFC_I_IMPL(self, n_bits, result)                \
	__register __SIZE_TYPE__ __bffc_bindex, __bffc_maxbyte;                     \
	__bffc_maxbyte = __HYBRID_BITSET_BYTE(n_bits - 1);                          \
	result         = -1;                                                        \
	for (__bffc_bindex = 0; __bffc_bindex <= __bffc_maxbyte; ++__bffc_bindex) { \
		__hybrid_bitset_t __word = self[__bffc_bindex];                         \
		if (__word == __HYBRID_BITSET_WORD_BMAX)                                \
			continue;                                                           \
		result = __bffc_bindex << __HYBRID_BITSET_WORD_SHFT;                    \
		while (__word & 1) {                                                    \
			++result;                                                           \
			__word >>= 1;                                                       \
		}                                                                       \
		if __unlikely(result >= nbits)                                          \
			result = -1;                                                        \
		break;                                                                  \
	}
#define __HYBRID_PRIVATE_BITSET_FFS_I_IMPL(self, n_bits, result)                                  \
	__register __SIZE_TYPE__ __bffs_bindex, __bffs_maxbyte;                                       \
	__bffs_maxbyte = __HYBRID_BITSET_BYTE(n_bits - 1);                                            \
	result         = -1;                                                                          \
	for (__bffs_bindex = 0; __bffs_bindex <= __bffs_maxbyte; ++__bffs_bindex) {                   \
		__hybrid_bitset_t __word = self[__bffs_bindex];                                           \
		if (__word == 0)                                                                          \
			continue;                                                                             \
		result = (__bffs_bindex << __HYBRID_BITSET_WORD_SHFT) + __HYBRID_BITSET_WORD_CTZ(__word); \
		if __unlikely(result >= nbits)                                                            \
			result = -1;                                                                          \
		break;                                                                                    \
	}
#define __HYBRID_PRIVATE_BITSET_FFC_IMPL(self, n_bits, result)                  \
	__register __SIZE_TYPE__ __bffc_bindex, __bffc_maxbyte;                     \
	__bffc_maxbyte = __HYBRID_BITSET_BYTE(n_bits - 1);                          \
	result         = (n_bits);                                                  \
	for (__bffc_bindex = 0; __bffc_bindex <= __bffc_maxbyte; ++__bffc_bindex) { \
		__hybrid_bitset_t __word = self[__bffc_bindex];                         \
		if (__word == __HYBRID_BITSET_WORD_BMAX)                                \
			continue;                                                           \
		result = __bffc_bindex << __HYBRID_BITSET_WORD_SHFT;                    \
		while (__word & 1) {                                                    \
			++result;                                                           \
			__word >>= 1;                                                       \
		}                                                                       \
		break;                                                                  \
	}
#define __HYBRID_PRIVATE_BITSET_FFS_IMPL(self, n_bits, result)                                    \
	__register __SIZE_TYPE__ __bffs_bindex, __bffs_maxbyte;                                       \
	__bffs_maxbyte = __HYBRID_BITSET_BYTE(n_bits - 1);                                            \
	result         = (n_bits);                                                                    \
	for (__bffs_bindex = 0; __bffs_bindex <= __bffs_maxbyte; ++__bffs_bindex) {                   \
		__hybrid_bitset_t __word = self[__bffs_bindex];                                           \
		if (__word == 0)                                                                          \
			continue;                                                                             \
		result = (__bffs_bindex << __HYBRID_BITSET_WORD_SHFT) + __HYBRID_BITSET_WORD_CTZ(__word); \
		break;                                                                                    \
	}


/* >> void __hybrid_bitset_ffc_i(__hybrid_bitset_t const *self, size_t n_bits, ssize_t *p_value);
 * Find the first bitno within [0, n_bits) that is off and store its
 * index in `*p_value'. If no such bit exists, write `-1' into `*p_value'. */
#define __hybrid_bitset_ffc_i(self, n_bits, p_value)                                  \
	do {                                                                              \
		__register __hybrid_bitset_t const *__bffc_self = (self);                     \
		__register __SIZE_TYPE__ __bffc_nbits = (nbits);                              \
		__register __SSIZE_TYPE__ __bffc_result;                                      \
		__HYBRID_PRIVATE_BITSET_FFC_I_IMPL(__bffc_self, __bffc_nbits, __bffc_result); \
		*(p_value) = __bffc_result;                                                   \
	}	__WHILE0

/* >> void __hybrid_bitset_ffs_i(__hybrid_bitset_t const *self, size_t n_bits, ssize_t *p_value);
 * Find the first bitno within [0, n_bits) that is on and store its
 * index in `*p_value'. If no such bit exists, write `-1' into `*p_value'. */
#define __hybrid_bitset_ffs_i(self, n_bits, p_value)                                  \
	do {                                                                              \
		__register __hybrid_bitset_t const *__bffc_self = (self);                     \
		__register __SIZE_TYPE__ __bffc_nbits           = (nbits);                    \
		__register __SSIZE_TYPE__ __bffc_result;                                      \
		__HYBRID_PRIVATE_BITSET_FFS_I_IMPL(__bffc_self, __bffc_nbits, __bffc_result); \
		*(p_value) = __bffc_result;                                                   \
	}	__WHILE0


/* Find the first bitno within [0,  n_bits) that is off and  return
 * its index. If no such bit exists, return some value `>= n_bits'. */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_ffc)(__hybrid_bitset_t const *__restrict __self, __SIZE_TYPE__ __n_bits) {
	__register __SIZE_TYPE__ __result;
	__HYBRID_PRIVATE_BITSET_FFC_IMPL(__self, __n_bits, __result);
	return __result;
}

/* Find  the first bitno  within [0, n_bits) that  is on and return
 * its index. If no such bit exists, return some value `>= n_bits'. */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_ffs)(__hybrid_bitset_t const *__restrict __self, __SIZE_TYPE__ __n_bits) {
	__register __SIZE_TYPE__ __result;
	__HYBRID_PRIVATE_BITSET_FFS_IMPL(__self, __n_bits, __result);
	return __result;
}


/* Check if the bitset contains any 1-elements */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__NOTHROW_NCX(__hybrid_bitset_anyset)(__hybrid_bitset_t const *__restrict __self, __SIZE_TYPE__ __n_bits) {
	__register __SIZE_TYPE__ __i;
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
	__register __SIZE_TYPE__ __i;
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
__NOTHROW_NCX(__hybrid_bitset_nanyset)(__hybrid_bitset_t const *__restrict __self,
                                       __SIZE_TYPE__ __minbitno, __SIZE_TYPE__ __maxbitno) {
	__register __SIZE_TYPE__ __minbyte = (__SIZE_TYPE__)__HYBRID_BITSET_BYTE(__minbitno);
	__register __SIZE_TYPE__ __maxbyte = (__SIZE_TYPE__)__HYBRID_BITSET_BYTE(__maxbitno);
	if (__minbyte >= __maxbyte) {
		if (__self[__maxbyte] & ~((__HYBRID_BITSET_WORD_BMAX >> (__HYBRID_BITSET_WORD_BITS - (__minbitno & __HYBRID_BITSET_WORD_BMSK))) |
		                          (__HYBRID_BITSET_WORD_BMAX << ((__maxbitno & __HYBRID_BITSET_WORD_BMSK) + 1))))
			return 1;
	} else {
		__register __SIZE_TYPE__ __i;
		if (__self[__minbyte] & ~(__HYBRID_BITSET_WORD_BMAX >> (__HYBRID_BITSET_WORD_BITS - (__minbitno & __HYBRID_BITSET_WORD_BMSK))))
			return 1;
		for (__i = __minbyte + 1; __i < __maxbyte; ++__i) {
			if (__self[__i] != 0)
				return 1;
		}
		if (__self[__maxbyte] & ~(__HYBRID_BITSET_WORD_BMAX << ((__maxbitno & __HYBRID_BITSET_WORD_BMSK) + 1)))
			return 1;
	}
	return 0;
}

/* Check if the bitset contains only 1-elements within the given range */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__NOTHROW_NCX(__hybrid_bitset_nallset)(__hybrid_bitset_t const *__restrict __self,
                                       __SIZE_TYPE__ __minbitno, __SIZE_TYPE__ __maxbitno) {
	__register __SIZE_TYPE__ __minbyte = (__SIZE_TYPE__)__HYBRID_BITSET_BYTE(__minbitno);
	__register __SIZE_TYPE__ __maxbyte = (__SIZE_TYPE__)__HYBRID_BITSET_BYTE(__maxbitno);
	if (__minbyte >= __maxbyte) {
		__hybrid_bitset_t __mask = ~((__HYBRID_BITSET_WORD_BMAX >> (__HYBRID_BITSET_WORD_BITS - (__minbitno & __HYBRID_BITSET_WORD_BMSK))) |
		                             (__HYBRID_BITSET_WORD_BMAX << ((__maxbitno & __HYBRID_BITSET_WORD_BMSK) + 1)));
		if ((__self[__maxbyte] & __mask) != __mask)
			return 0;
	} else {
		__register __SIZE_TYPE__ __i;
		__hybrid_bitset_t __mask;
		__mask = ~(__HYBRID_BITSET_WORD_BMAX >> (__HYBRID_BITSET_WORD_BITS - (__minbitno & __HYBRID_BITSET_WORD_BMSK)));
		if ((__self[__minbyte] & __mask) != __mask)
			return 0;
		for (__i = __minbyte + 1; __i < __maxbyte; ++__i) {
			if (__self[__i] != __HYBRID_BITSET_WORD_BMAX)
				return 0;
		}
		__mask = ~(__HYBRID_BITSET_WORD_BMAX << ((__maxbitno & __HYBRID_BITSET_WORD_BMSK) + 1));
		if ((__self[__maxbyte] & __mask) != __mask)
			return 0;
	}
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
__NOTHROW_NCX(__hybrid_bitset_npopcount)(__hybrid_bitset_t const *__restrict __self,
                                         __SIZE_TYPE__ __minbitno, __SIZE_TYPE__ __maxbitno) {
	__SIZE_TYPE__ __result;
	__register __SIZE_TYPE__ __minbyte = (__SIZE_TYPE__)__HYBRID_BITSET_BYTE(__minbitno);
	__register __SIZE_TYPE__ __maxbyte = (__SIZE_TYPE__)__HYBRID_BITSET_BYTE(__maxbitno);
	if (__minbyte >= __maxbyte) {
		__result = __HYBRID_BITSET_WORD_POPCOUNT(__self[__maxbyte] &
		                                         ~((__HYBRID_BITSET_WORD_BMAX >> (__HYBRID_BITSET_WORD_BITS - (__minbitno & __HYBRID_BITSET_WORD_BMSK))) |
		                                           (__HYBRID_BITSET_WORD_BMAX << ((__maxbitno & __HYBRID_BITSET_WORD_BMSK) + 1))));
	} else {
		__register __SIZE_TYPE__ __i;
		__result = __HYBRID_BITSET_WORD_POPCOUNT(__self[__minbyte] & ~(__HYBRID_BITSET_WORD_BMAX >> (__HYBRID_BITSET_WORD_BITS - (__minbitno & __HYBRID_BITSET_WORD_BMSK))));
		for (__i = __minbyte + 1; __i < __maxbyte; ++__i)
			__result += __HYBRID_BITSET_WORD_POPCOUNT(__self[__i]);
		__result += __HYBRID_BITSET_WORD_POPCOUNT(__self[__maxbyte] & ~(__HYBRID_BITSET_WORD_BMAX << ((__maxbitno & __HYBRID_BITSET_WORD_BMSK) + 1)));
	}
	return __result;
}

/* Count-leading-zeroes (undefined when `self' doesn't contain any set bits) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_clz)(__hybrid_bitset_t const *__restrict __self) {
	__SIZE_TYPE__ __result = 0;
	for (; *__self == 0; ++__self)
		__result += __HYBRID_BITSET_WORD_BITS;
	return __result + __HYBRID_BITSET_WORD_CLZ(*__self);
}

/* Count-trailing-zeroes (undefined when `self' doesn't contain any set bits) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__hybrid_bitset_ctz)(__hybrid_bitset_t const *__restrict __self, __SIZE_TYPE__ __n_bits) {
	__SIZE_TYPE__ __result  = 0;
	__SIZE_TYPE__ __byteoff = __n_bits >> __HYBRID_BITSET_WORD_SHFT;
	if (__n_bits & __HYBRID_BITSET_WORD_BMSK) {
		__hybrid_bitset_t __word = __self[__byteoff];
		__word <<= __HYBRID_BITSET_WORD_BITS - (__n_bits & __HYBRID_BITSET_WORD_BMSK);
		if (__word) {
			while (!(__word & __HYBRID_BITSET_WORD_SIGN)) {
				__word <<= 1;
				++__result;
			}
			return __result;
		}
		__result = __n_bits & __HYBRID_BITSET_WORD_BMSK;
	}
	if (__byteoff) {
		__hybrid_bitset_t __word;
		--__byteoff;
		for (; __self[__byteoff] == 0; --__byteoff)
			__result += __HYBRID_BITSET_WORD_BITS;
		__word = __self[__byteoff];
		while (!(__word & __HYBRID_BITSET_WORD_SIGN)) {
			++__result;
			__word <<= 1;
		}
	}
	return __result;
}


__DECL_END
#endif /* __CC__ */

#endif /* !__GUARD_HYBRID___BITSET_H */
