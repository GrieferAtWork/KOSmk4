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
/* (#) Portability: DragonFly BSD (/sys/sys/bitstring.h) */
/* (#) Portability: FreeBSD       (/sys/sys/bitstring.h) */
/* (#) Portability: libbsd        (/include/bsd/sys/bitstring.h) */
#ifndef _SYS_BITSTRING_H
#define _SYS_BITSTRING_H 1

#include <__stdinc.h>

#include <bits/types.h>
#include <hybrid/__bit.h>

#include <libc/stdlib.h>
#include <libc/string.h>

#define _bit_byte(bitno) ((bitno) >> 3)                /*       bitno / 8 */
#define _bit_mask(bitno) (__UINT8_C(1) << ((bitno)&7)) /* 1 << (bitno % 8) */

/* Return the # of bytes needed to represent `nbits' bits */
#define bitstr_size(nbits) (((nbits) + 7) >> 3) /* CEILDIV(nbits, 8) */

#ifdef __CC__
__DECL_BEGIN

typedef unsigned char bitstr_t;

/* Allocate  a  zero-initialized   bitstring  on  the   heap.
 * If the allocation fails, then this function returns `NULL' */
#ifdef __INTELLISENSE__
__ATTR_MALLOC __ATTR_WUNUSED bitstr_t *(bit_alloc)(int nbits);
#else /* __INTELLISENSE__ */
#define bit_alloc(nbits) (bitstr_t *)__libc_calloc((__size_t)bitstr_size(nbits), sizeof(bitstr_t))
#endif /* !__INTELLISENSE__ */

/* Declare a bitstring  variable `self'  that can  hold at  least `nbits'  bits:
 * >> bitstr_t bit_decl(mybitstr, 42); // `mybitstr' can hold at least `42' bits */
#define bit_decl(self, nbits) \
	((self)[bitstr_size(nbits)])

#ifdef __USE_KOS
#ifdef __INTELLISENSE__
__ATTR_NONNULL((1)) void (bit_setall)(bitstr_t *self, int nbits);
__ATTR_NONNULL((1)) void (bit_clearall)(bitstr_t *self, int nbits);
__ATTR_NONNULL((1)) void (bit_flipall)(bitstr_t *self, int nbits);
#else /* __INTELLISENSE__ */
#define bit_setall(self, nbits)   __libc_memset(self, 0xff, bitstr_size(nbits) * sizeof(bitstr_t))
#define bit_clearall(self, nbits) __libc_bzero(self, bitstr_size(nbits) * sizeof(bitstr_t))
#define bit_flipall(self, nbits)                                   \
	do {                                                           \
		__SIZE_TYPE__ __bfa_i;                                     \
		for (__bfa_i = 0; __bfa_i < bitstr_size(nbits); ++__bfa_i) \
			(self)[__bfa_i] ^= 0xff;                               \
	}	__WHILE0
#endif /* !__INTELLISENSE__ */
#define bit_foreach(bitno, self, nbits)             \
	for ((bitno) = 0; (bitno) < (nbits); ++(bitno)) \
		if (!bit_test(self, bitno))                 \
			;                                       \
		else
#endif /* __USE_KOS */

/* Check if `bitno' of `self' set */
#ifdef __INTELLISENSE__
__ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL (bit_test)(bitstr_t const *self, int bitno);
#else /* __INTELLISENSE__ */
#define bit_test(self, bitno) ((self)[_bit_byte(bitno)] & _bit_mask(bitno))
#endif /* !__INTELLISENSE__ */

/* Turn on `bitno' of `self' */
#ifdef __INTELLISENSE__
__ATTR_NONNULL((1)) void (bit_set)(bitstr_t *__restrict self, int bitno);
#else /* __INTELLISENSE__ */
#define bit_set(self, bitno) (void)((self)[_bit_byte(bitno)] |= _bit_mask(bitno))
#endif /* !__INTELLISENSE__ */

/* Turn off `bitno' of `self' */
#ifdef __INTELLISENSE__
__ATTR_NONNULL((1)) void (bit_clear)(bitstr_t *__restrict self, int bitno);
#else /* __INTELLISENSE__ */
#define bit_clear(self, bitno) (void)((self)[_bit_byte(bitno)] &= ~_bit_mask(bitno))
#endif /* !__INTELLISENSE__ */

#ifdef __USE_KOS
/* Flip the state of `bitno' of `self' */
#ifdef __INTELLISENSE__
__ATTR_NONNULL((1)) void (bit_flip)(bitstr_t *__restrict self, int bitno);
#else /* __INTELLISENSE__ */
#define bit_flip(self, bitno) (void)((self)[_bit_byte(bitno)] ^= _bit_mask(bitno))
#endif /* !__INTELLISENSE__ */
#endif /* __USE_KOS */

#define __bit_nclear_impl(self, minbyte, maxbyte, minbyte_bitno, maxbyte_bitno) \
	((minbyte >= maxbyte)                                                       \
	 ? (self[maxbyte] &= ((0xff >> (8 - minbyte_bitno)) |                       \
	                      (0xff << (maxbyte_bitno + 1))))                       \
	 : (self[minbyte] &= 0xff >> (8 - minbyte_bitno),                           \
	    __libc_bzero(&self[minbyte + 1], maxbyte - (minbyte + 1)),              \
	    self[maxbyte] &= 0xff << (maxbyte_bitno + 1)))
#define __bit_nset_impl(self, minbyte, maxbyte, minbyte_bitno, maxbyte_bitno) \
	((minbyte >= maxbyte)                                                     \
	 ? (self[maxbyte] |= ((0xff << minbyte_bitno) |                           \
	                      (0xff >> (7 - maxbyte_bitno))))                     \
	 : (self[minbyte] |= 0xff << minbyte_bitno,                               \
	    __libc_memset(&self[minbyte + 1], 0xff, maxbyte - (minbyte + 1)),     \
	    self[maxbyte] |= 0xff >> (7 - maxbyte_bitno)))
#define __bit_nclear(self, minbitno, maxbitno)                     \
	__register __size_t __minbyte = (__size_t)_bit_byte(minbitno); \
	__register __size_t __maxbyte = (__size_t)_bit_byte(maxbitno); \
	__bit_nclear_impl(self, __minbyte, __maxbyte, (minbitno & 7), (maxbitno & 7))
#define __bit_nset(self, minbitno, maxbitno)                       \
	__register __size_t __minbyte = (__size_t)_bit_byte(minbitno); \
	__register __size_t __maxbyte = (__size_t)_bit_byte(maxbitno); \
	__bit_nset_impl(self, __minbyte, __maxbyte, (minbitno & 7), (maxbitno & 7))


#ifdef __INTELLISENSE__
/* Turn off bits [minbitno, maxbitno] (inclusive) in `self'
 * NOTE: When  `minbitno > maxbitno', the result  is weak undefined behavior,
 *       in that the way in which `self' is modified is undefined, though the
 *       function still guaranties that nothing but `self' gets modified. */
__ATTR_NONNULL((1)) void (bit_nclear)(bitstr_t *__restrict self, int minbitno, int maxbitno);

/* Turn on bits [minbitno, maxbitno] (inclusive) in `self'
 * NOTE: When  `minbitno > maxbitno', the result  is weak undefined behavior,
 *       in that the way in which `self' is modified is undefined, though the
 *       function still guaranties that nothing but `self' gets modified. */
__ATTR_NONNULL((1)) void (bit_nset)(bitstr_t *__restrict self, int minbitno, int maxbitno);
#elif !defined(__NO_XBLOCK)
#define bit_nclear(self, minbitno, maxbitno)          \
	__XBLOCK({                                        \
		__register bitstr_t *__self = (self);         \
		__register int __minbitno   = (minbitno);     \
		__register int __maxbitno   = (maxbitno);     \
		__bit_nclear(__self, __minbitno, __maxbitno); \
		(void)0;                                      \
	})
#define bit_nset(self, minbitno, maxbitno)          \
	__XBLOCK({                                      \
		__register bitstr_t *__self = (self);       \
		__register int __minbitno   = (minbitno);   \
		__register int __maxbitno   = (maxbitno);   \
		__bit_nset(__self, __minbitno, __maxbitno); \
		(void)0;                                    \
	})
#else /* ... */
__LOCAL __ATTR_NONNULL((1)) void
(bit_nclear)(bitstr_t *__restrict __self, int __minbitno, int __maxbitno) {
	__bit_nclear(__self, __minbitno, __maxbitno);
}
__LOCAL __ATTR_NONNULL((1)) void
(bit_nset)(bitstr_t *__restrict __self, int __minbitno, int __maxbitno) {
	__bit_nset(__self, __minbitno, __maxbitno);
}
#endif /* !... */



#define __bit_ffc_impl(self, nbits, result)                 \
	__register int __bindex, __maxbyte;                     \
	__maxbyte = _bit_byte(nbits - 1);                       \
	result    = -1;                                         \
	for (__bindex = 0; __bindex <= __maxbyte; ++__bindex) { \
		bitstr_t __byte = self[__bindex];                   \
		if (__byte == 0xff)                                 \
			continue;                                       \
		result = __bindex << 3;                             \
		while (__byte & 1) {                                \
			++result;                                       \
			__byte >>= 1;                                   \
		}                                                   \
		break;                                              \
	}                                                       \
	if __unlikely(result >= nbits)                          \
		result = -1;

#define __bit_ffs_impl(self, nbits, result)                 \
	__register int __bindex, __maxbyte;                     \
	__maxbyte = _bit_byte(nbits - 1);                       \
	result    = -1;                                         \
	for (__bindex = 0; __bindex <= __maxbyte; ++__bindex) { \
		bitstr_t __byte = self[__bindex];                   \
		if (__byte == 0)                                    \
			continue;                                       \
		result = (__bindex << 3) + __hybrid_ctz8(__byte);   \
		break;                                              \
	}                                                       \
	if __unlikely(result >= nbits)                          \
		result = -1

#ifdef __INTELLISENSE__
/* Find the first bitno  within [0, nbits) that  is off and store  its
 * index in `*value'. If no such bit exists, write `-1' into `*value'. */
__ATTR_NONNULL((1, 3)) void (bit_ffc)(bitstr_t *__restrict self, int nbits, int *value);
/* Find the first  bitno within [0,  nbits) that is  on and store  its
 * index in `*value'. If no such bit exists, write `-1' into `*value'. */
__ATTR_NONNULL((1, 3)) void (bit_ffs)(bitstr_t *__restrict self, int nbits, int *value);
#elif !defined(__NO_XBLOCK)
#define bit_ffc(self, nbits, value)                 \
	__XBLOCK({                                      \
		__register bitstr_t *__self = (self);       \
		__register int __result, __nbits = (nbits); \
		__bit_ffc_impl(__self, __nbits, __result);  \
		*(value) = __result;                        \
		(void)0;                                    \
	})
#define bit_ffs(self, nbits, value)                 \
	__XBLOCK({                                      \
		__register bitstr_t *__self = (self);       \
		__register int __result, __nbits = (nbits); \
		__bit_ffs_impl(__self, __nbits, __result);  \
		*(value) = __result;                        \
		(void)0;                                    \
	})
#else /* ... */
__LOCAL __ATTR_NONNULL((1, 3)) void
(bit_ffc)(bitstr_t *__restrict __self, int __nbits, int *__value) {
	__register int __result;
	__bit_ffc_impl(__self, __nbits, __result);
	*(__value) = __result;
}
__LOCAL __ATTR_NONNULL((1, 3)) void
(bit_ffs)(bitstr_t *__restrict __self, int __nbits, int *__value) {
	__register int __result;
	__bit_ffs_impl(__self, __nbits, __result);
	*(__value) = __result;
}
#endif /* !... */

#ifdef __USE_KOS
#define bit_noneset(self, nbits) (!bit_anyset(self, nbits))
__LOCAL __ATTR_NONNULL((1)) __BOOL
(bit_anyset)(bitstr_t *__restrict __self, unsigned int __nbits) {
	unsigned int __i;
	for (__i = 0; __i < (__nbits >> 3); ++__i) {
		if (__self[__i] != 0)
			return 1;
	}
	if (__nbits & 7) {
		if (__self[__i] & ((1 << (__nbits & 7)) - 1))
			return 1;
	}
	return 0;
}
__LOCAL __ATTR_NONNULL((1)) __BOOL
(bit_allset)(bitstr_t *__restrict __self, unsigned int __nbits) {
	unsigned int __i;
	for (__i = 0; __i < (__nbits >> 3); ++__i) {
		if (__self[__i] != 0xff)
			return 0;
	}
	if (__nbits & 7) {
		bitstr_t __mask = ((1 << (__nbits & 7)) - 1);
		if ((__self[__i] & __mask) != __mask)
			return 0;
	}
	return 1;
}
__LOCAL __ATTR_NONNULL((1)) __BOOL
(bit_nanyset)(bitstr_t *__restrict __self, unsigned int __minbitno, unsigned int __maxbitno) {
	__register __size_t __minbyte = (__size_t)_bit_byte(__minbitno);
	__register __size_t __maxbyte = (__size_t)_bit_byte(__maxbitno);
	if (__minbyte >= __maxbyte) {
		if (__self[__maxbyte] & ~((0xff >> (8 - (__minbitno & 7))) |
		                          (0xff << ((__maxbitno & 7) + 1))))
			return 1;
	} else {
		__register __size_t __i;
		if (__self[__minbyte] & ~(0xff >> (8 - (__minbitno & 7))))
			return 1;
		for (__i = __minbyte + 1; __i < __maxbyte; ++__i) {
			if (__self[__i] != 0)
				return 1;
		}
		if (__self[__maxbyte] & ~(0xff << ((__maxbitno & 7) + 1)))
			return 1;
	}
	return 0;
}
__LOCAL __ATTR_NONNULL((1)) unsigned int
(bit_popcount)(bitstr_t *__restrict __self, unsigned int __nbits) {
	unsigned int __result = 0;
	unsigned int __i;
	for (__i = 0; __i < (__nbits >> 3); ++__i) {
		__result += __hybrid_popcount8(__self[__i]);
	}
	if (__nbits & 7) {
		bitstr_t __mask = ((1 << (__nbits & 7)) - 1);
		__result += __hybrid_popcount8(__self[__i] & __mask);
	}
	return __result;
}

/* Count-leading-zeroes (undefined when `self' doesn't contain any set bits) */
__LOCAL __ATTR_NONNULL((1)) unsigned int
(bit_clz)(bitstr_t *__restrict __self) {
	bitstr_t __word;
	unsigned int __result = 0;
	for (; *__self == 0; ++__self)
		__result += 8;
	__word = *__self;
	while (!(__word & 1)) {
		++__result;
		__word >>= 1;
	}
	return __result;
}

/* Count-trailing-zeroes (undefined when `self' doesn't contain any set bits) */
__LOCAL __ATTR_NONNULL((1)) unsigned int
(bit_ctz)(bitstr_t *__restrict __self, unsigned int __nbits) {
	bitstr_t __word;
	unsigned int __result  = 0;
	unsigned int __byteoff = __nbits >> 3;
	if (__nbits & 7) {
		__word = __self[__byteoff];
		__word <<= 8 - (__nbits & 7);
		if (__word) {
			while (!(__word & 0x80)) {
				__word <<= 1;
				++__result;
			}
			return __result;
		}
		__result = __nbits & 7;
	}
	if (__byteoff) {
		--__byteoff;
		for (; __self[__byteoff] == 0; --__byteoff)
			__result += 8;
		__word = __self[__byteoff];
		while (!(__word & 0x80)) {
			++__result;
			__word <<= 1;
		}
	}
	return __result;
}
#endif /* __USE_KOS */


__DECL_END
#endif /* __CC__ */

#endif /* !_SYS_BITSTRING_H */
