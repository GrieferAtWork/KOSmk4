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
#ifndef __GUARD_HYBRID_SEQUENCE_BITSET_H
#define __GUARD_HYBRID_SEQUENCE_BITSET_H 1

#include "../../__stdinc.h"
#include "../__atomic.h"

/* !!!!!!         DEPRECATED API         !!!!!! */
/* !!!!!!         DEPRECATED API         !!!!!! */
/* !!!!!!         DEPRECATED API         !!!!!! */
/* !!!!!!                                !!!!!! */
/* !!!!!! USE <hybrid/bitset.h> INSTEAD  !!!!!! */
/* !!!!!!                                !!!!!! */
/* !!!!!!         DEPRECATED API         !!!!!! */
/* !!!!!!         DEPRECATED API         !!!!!! */
/* !!!!!!         DEPRECATED API         !!!!!! */

#ifdef __CC__

/* The word type used by bitsets */
#ifndef BITSET_WORDTYPE
#include "../typecore.h"
#define BITSET_WORDTYPE __UINTPTR_TYPE__
#endif /* !BITSET_WORDTYPE */

__DECL_BEGIN

/* Bitset type declarator */
#define BITSET(num_bits)                                               \
	struct {                                                           \
		BITSET_WORDTYPE _bs_bits[((num_bits) +                         \
		                          (sizeof(BITSET_WORDTYPE) * 8) - 1) / \
		                         (sizeof(BITSET_WORDTYPE) * 8)];       \
	}

/* Bitset helper functions */
#define BITSET_WORDOF(bit) \
	((bit) / (sizeof(BITSET_WORDTYPE) * 8))
#define BITSET_MASKOF(bit) \
	((BITSET_WORDTYPE)1 << ((bit) % (sizeof(BITSET_WORDTYPE) * 8)))
#define BITSET_GET(self, bit) \
	(((self)->_bs_bits[BITSET_WORDOF(bit)] & BITSET_MASKOF(bit)) != 0)
#define BITSET_TURNON(self, bit) \
	((self)->_bs_bits[BITSET_WORDOF(bit)] |= BITSET_MASKOF(bit))
#define BITSET_TURNOFF(self, bit) \
	((self)->_bs_bits[BITSET_WORDOF(bit)] &= ~BITSET_MASKOF(bit))
#define BITSET_TOGGLE(self, bit) \
	((self)->_bs_bits[BITSET_WORDOF(bit)] ^= BITSET_MASKOF(bit))
#define BITSET_SET(self, bit, turn_on) \
	((turn_on) ? BITSET_TURNON(self, bit) : BITSET_TURNOFF(self, bit))

/* Atomic bitset helper functions */
#define BITSET_ATOMIC_GET(self, bit) \
	((__hybrid_atomic_load(&(self)->_bs_bits[BITSET_WORDOF(bit)], __ATOMIC_ACQUIRE) & BITSET_MASKOF(bit)) != 0)
#define BITSET_ATOMIC_FETCH_TURNON(self, bit) \
	((__hybrid_atomic_fetchor(&(self)->_bs_bits[BITSET_WORDOF(bit)], BITSET_MASKOF(bit), __ATOMIC_SEQ_CST) & BITSET_MASKOF(bit)) != 0)
#define BITSET_ATOMIC_FETCH_TURNOFF(self, bit) \
	((__hybrid_atomic_fetchand(&(self)->_bs_bits[BITSET_WORDOF(bit)], ~BITSET_MASKOF(bit), __ATOMIC_SEQ_CST) & BITSET_MASKOF(bit)) != 0)
#define BITSET_ATOMIC_FETCH_TOGGLE(self, bit) \
	((__hybrid_atomic_fetchxor(&(self)->_bs_bits[BITSET_WORDOF(bit)], BITSET_MASKOF(bit), __ATOMIC_SEQ_CST) & BITSET_MASKOF(bit)) != 0)
#define BITSET_ATOMIC_XCH(self, bit, turn_on) \
	((turn_on) ? BITSET_ATOMIC_FETCH_TURNON(self, bit) : BITSET_ATOMIC_FETCH_TURNOFF(self, bit))
#define BITSET_ATOMIC_CMPXCH(self, bit, old_ison, new_ison)             \
	__hybrid_bitset_atomic_cmpxch((self)->_bs_bits[BITSET_WORDOF(bit)], \
	                              BITSET_MASKOF(bit), old_ison, new_ison)
__LOCAL __ATTR_WUNUSED __ATTR_LEAF __ATTR_NONNULL((1)) __BOOL
__NOTHROW_NCX(__hybrid_bitset_atomic_cmpxch)(BITSET_WORDTYPE *__restrict __pword,
                                             BITSET_WORDTYPE __mask,
                                             __BOOL __old_ison,
                                             __BOOL __new_ison) {
	__UINTPTR_TYPE__ __oldword, __oldval, __newval;
	__oldval = __newval = 0;
	if (__old_ison)
		__oldval = __mask;
	if (__new_ison)
		__newval = __mask;
	do {
		__oldword = __hybrid_atomic_load(__pword, __ATOMIC_ACQUIRE);
		if ((__oldword & __mask) != __oldval)
			return 0;
	} while (!__hybrid_atomic_cmpxch_weak(__pword, __oldword,
	                                      (__oldword & ~__mask) | __newval,
	                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));
	return 1;
}



__DECL_END
#endif /* __CC__ */

#endif /* !__GUARD_HYBRID_SEQUENCE_BITSET_H */
