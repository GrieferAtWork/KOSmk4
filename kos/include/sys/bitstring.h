/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
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
#include <hybrid/__bitset.h>
#include <libc/stdlib.h>

/*
 * !!! NOTE
 *
 * Even though this header *does* define a couple of `__USE_KOS' extensions,
 * these  are only here for the sake of legacy support. If you *truely* wish
 * to target KOS (or maybe even the fully portable "hybrid" API), you should
 * instead make use of <hybrid/bitset.h>
 *
 * !!! ----
 */


#define _bit_byte(bitno) __HYBRID_BITSET_WORD(bitno) /* bitno / 8 */
#define _bit_mask(bitno) __HYBRID_BITSET_MASK(bitno) /* 1 << (bitno % 8) */

/* Return the # of bytes needed to represent `nbits' bits */
#define bitstr_size(nbits) __HYBRID_BITSET_SIZEOF(nbits) /* CEILDIV(nbits, 8) */

#ifdef __CC__
__DECL_BEGIN

typedef __hybrid_bitset_t bitstr_t;

#ifdef ____libc_calloc_defined
/* Allocate  a  zero-initialized   bitstring  on  the   heap.
 * If the allocation fails, then this function returns `NULL' */
#ifdef __INTELLISENSE__
__ATTR_MALLOC __ATTR_WUNUSED bitstr_t *(bit_alloc)(int nbits);
#else /* __INTELLISENSE__ */
#define bit_alloc(nbits) (bitstr_t *)__libc_calloc((__size_t)bitstr_size(nbits), sizeof(bitstr_t))
#endif /* !__INTELLISENSE__ */
#endif /* ____libc_calloc_defined */

/* Declare a bitstring  variable `self'  that can  hold at  least `nbits'  bits:
 * >> bitstr_t bit_decl(mybitstr, 42); // `mybitstr' can hold at least `42' bits */
#define bit_decl(self, nbits) \
	((self)[__HYBRID_BITSET_LENGTHOF(nbits)])

#ifdef __USE_KOS
#ifdef __INTELLISENSE__
__ATTR_NONNULL((1)) void (bit_setall)(bitstr_t *self, int nbits);
__ATTR_NONNULL((1)) void (bit_clearall)(bitstr_t *self, int nbits);
__ATTR_NONNULL((1)) void (bit_flipall)(bitstr_t *self, int nbits);
#else /* __INTELLISENSE__ */
#define bit_setall(self, nbits)   __hybrid_bitset_setall(self, nbits)
#define bit_clearall(self, nbits) __hybrid_bitset_clearall(self, nbits)
#define bit_flipall(self, nbits)  __hybrid_bitset_flipall(self, nbits)
#endif /* !__INTELLISENSE__ */
#define bit_foreach(bitno, self, nbits) __hybrid_bitset_foreach(bitno, self, nbits)
#endif /* __USE_KOS */

/* Check if `bitno' of `self' set */
#ifdef __INTELLISENSE__
__ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL (bit_test)(bitstr_t const *self, int bitno);
#else /* __INTELLISENSE__ */
#define bit_test(self, bitno) __hybrid_bitset_test(self, bitno)
#endif /* !__INTELLISENSE__ */

/* Turn on `bitno' of `self' */
#ifdef __INTELLISENSE__
__ATTR_NONNULL((1)) void (bit_set)(bitstr_t *__restrict self, int bitno);
#else /* __INTELLISENSE__ */
#define bit_set(self, bitno) __hybrid_bitset_set(self, bitno)
#endif /* !__INTELLISENSE__ */

/* Turn off `bitno' of `self' */
#ifdef __INTELLISENSE__
__ATTR_NONNULL((1)) void (bit_clear)(bitstr_t *__restrict self, int bitno);
#else /* __INTELLISENSE__ */
#define bit_clear(self, bitno) __hybrid_bitset_clear(self, bitno)
#endif /* !__INTELLISENSE__ */

#ifdef __USE_KOS
/* Flip the state of `bitno' of `self' */
#ifdef __INTELLISENSE__
__ATTR_NONNULL((1)) void (bit_flip)(bitstr_t *__restrict self, int bitno);
#else /* __INTELLISENSE__ */
#define bit_flip(self, bitno) __hybrid_bitset_flip(self, bitno)
#endif /* !__INTELLISENSE__ */
#endif /* __USE_KOS */

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
#else /* __INTELLISENSE__ */
#define bit_nclear(self, minbitno, maxbitno) __hybrid_bitset_nclear_r(self, (unsigned int)(minbitno), (unsigned int)(maxbitno))
#define bit_nset(self, minbitno, maxbitno)   __hybrid_bitset_nset_r(self, (unsigned int)(minbitno), (unsigned int)(maxbitno))
#endif /* !__INTELLISENSE__ */

#ifdef __INTELLISENSE__
/* Find the first bitno  within [0, nbits) that  is off and store  its
 * index in `*value'. If no such bit exists, write `-1' into `*value'. */
__ATTR_NONNULL((1, 3)) void (bit_ffc)(bitstr_t const *__restrict self, int nbits, int *value);
/* Find the first  bitno within [0,  nbits) that is  on and store  its
 * index in `*value'. If no such bit exists, write `-1' into `*value'. */
__ATTR_NONNULL((1, 3)) void (bit_ffs)(bitstr_t const *__restrict self, int nbits, int *value);
#elif !defined(__NO_XBLOCK)
#define bit_ffc(self, nbits, value) __XBLOCK({ __SSIZE_TYPE__ __bs_ffc_res; __hybrid_bitset_ffc_i(self, nbits, &__bs_ffc_res); *(value) = (int)__bs_ffc_res; (void)0; })
#define bit_ffs(self, nbits, value) __XBLOCK({ __SSIZE_TYPE__ __bs_ffs_res; __hybrid_bitset_ffs_i(self, nbits, &__bs_ffs_res); *(value) = (int)__bs_ffs_res; (void)0; })
#else /* ... */
#define bit_ffc(self, nbits, value) (void)(*(value) = (int)__PRIVATE_bit_ffc(self, nbits))
#define bit_ffs(self, nbits, value) (void)(*(value) = (int)__PRIVATE_bit_ffs(self, nbits))
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SSIZE_TYPE__
__NOTHROW_NCX(__PRIVATE_bit_ffc)(bitstr_t const *__restrict __self, __SIZE_TYPE__ __nbits) {
	__register __SSIZE_TYPE__ __result;
	__hybrid_bitset_ffc_i(__self, __nbits, &__result);
	return __result;
}
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) int
__NOTHROW_NCX(__PRIVATE_bit_ffs)(bitstr_t const *__restrict __self, __SIZE_TYPE__ __nbits) {
	__register __SSIZE_TYPE__ __result;
	__hybrid_bitset_ffs_i(__self, __nbits, &__result);
	return __result;
}
#endif /* !... */

#ifdef __USE_KOS
#define bit_noneset(self, nbits)              (!bit_anyset(self, nbits))
#define bit_anyset(self, nbits)               __hybrid_bitset_anyset(self, nbits)
#define bit_allset(self, nbits)               __hybrid_bitset_allset(self, nbits)
#define bit_nanyset(self, minbitno, maxbitno) __hybrid_bitset_nanyset_r(self, (unsigned int)(minbitno), (unsigned int)(maxbitno))
#define bit_popcount(self, nbits)             __hybrid_bitset_popcount(self, nbits)

/* Count-leading-zeroes (undefined when `self' doesn't contain any set bits) */
#define bit_clz(self, nbits) (unsigned int)__hybrid_bitset_rawclz(self, nbits)

/* Count-trailing-zeroes (undefined when `self' doesn't contain any set bits) */
#define bit_ctz(self) (unsigned int)__hybrid_bitset_rawctz(self)
#endif /* __USE_KOS */

__DECL_END
#endif /* __CC__ */

#endif /* !_SYS_BITSTRING_H */
