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
#ifndef _LIBEMU86_HELPERS_H
#define _LIBEMU86_HELPERS_H 1

#include "api.h"

#include <bits/types.h>
#include <i386-kos/asm/cpu-flags.h>

/* Misc. helper functions */
#ifdef __CC__
__DECL_BEGIN

#define EMU86_DEFINE_TZCNT(bwlq, Nbits)                                                      \
	__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((2)) unsigned int                                  \
	__NOTHROW(LIBEMU86_CC emu86_tzcnt##bwlq)(__uint##Nbits##_t i,                            \
	                                         /*out:CF|ZF*/ __uint32_t *__restrict peflags) { \
		unsigned int result    = 0;                                                          \
		__uint##Nbits##_t mask = 1;                                                          \
		*peflags               = 0;                                                          \
		if (!i)                                                                              \
			*peflags |= EFLAGS_CF;                                                           \
		for (; !((__uint##Nbits##_t)(i)&mask) && result < Nbits;                             \
		     mask <<= 1, ++result)                                                           \
			;                                                                                \
		if (!result)                                                                         \
			*peflags |= EFLAGS_ZF;                                                           \
		return result;                                                                       \
	}

#define EMU86_DEFINE_LZCNT(bwlq, Nbits)                                                      \
	__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((2)) unsigned int                                  \
	__NOTHROW(LIBEMU86_CC emu86_lzcnt##bwlq)(__uint##Nbits##_t i,                            \
	                                         /*out:CF|ZF*/ __uint32_t *__restrict peflags) { \
		unsigned int result    = 0;                                                          \
		__uint##Nbits##_t mask = (__uint##Nbits##_t)1 << (Nbits - 1);                        \
		*peflags               = 0;                                                          \
		if (!i)                                                                              \
			*peflags |= EFLAGS_CF;                                                           \
		for (; !((__uint##Nbits##_t)(i)&mask) && mask;                                       \
		     mask >>= 1, ++result)                                                           \
			;                                                                                \
		if (!result)                                                                         \
			*peflags |= EFLAGS_ZF;                                                           \
		return result;                                                                       \
	}

#define EMU86_DEFINE_RCL(bwlq, Nbits, msb_bit_set)                                         \
	__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __uint##Nbits##_t                           \
	__NOTHROW(LIBEMU86_CC emu86_rcl##bwlq)(__uint##Nbits##_t i, __uint8_t num_bits,        \
	                                       /*in|out:CF*/ __uint32_t *__restrict peflags) { \
		bool cf = (*peflags & EFLAGS_CF) != 0;                                             \
		for (; num_bits; --num_bits) {                                                     \
			bool new_cf;                                                                   \
			new_cf = (i & msb_bit_set) != 0;                                               \
			i <<= 1;                                                                       \
			if (cf)                                                                        \
				i |= 1;                                                                    \
			cf = new_cf;                                                                   \
		}                                                                                  \
		*peflags &= ~EFLAGS_CF;                                                            \
		if (cf)                                                                            \
			*peflags |= EFLAGS_CF;                                                         \
		return i;                                                                          \
	}
#define EMU86_DEFINE_RCR(bwlq, Nbits, msb_bit_set)                                         \
	__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __uint##Nbits##_t                           \
	__NOTHROW(LIBEMU86_CC emu86_rcr##bwlq)(__uint##Nbits##_t i, __uint8_t num_bits,        \
	                                       /*in|out:CF*/ __uint32_t *__restrict peflags) { \
		bool cf = (*peflags & EFLAGS_CF) != 0;                                             \
		for (; num_bits; --num_bits) {                                                     \
			bool new_cf;                                                                   \
			new_cf = (i & 1) != 0;                                                         \
			i >>= 1;                                                                       \
			if (cf)                                                                        \
				i |= msb_bit_set;                                                          \
			cf = new_cf;                                                                   \
		}                                                                                  \
		*peflags &= ~EFLAGS_CF;                                                            \
		if (cf)                                                                            \
			*peflags |= EFLAGS_CF;                                                         \
		return i;                                                                          \
	}

EMU86_DEFINE_TZCNT(b, 8)
EMU86_DEFINE_TZCNT(w, 16)
EMU86_DEFINE_TZCNT(l, 32)
EMU86_DEFINE_LZCNT(b, 8)
EMU86_DEFINE_LZCNT(w, 16)
EMU86_DEFINE_LZCNT(l, 32)
EMU86_DEFINE_RCL(b, 8, __UINT8_C(0x80))
EMU86_DEFINE_RCL(w, 16, __UINT16_C(0x8000))
EMU86_DEFINE_RCL(l, 32, __UINT32_C(0x80000000))
EMU86_DEFINE_RCR(b, 8, __UINT8_C(0x80))
EMU86_DEFINE_RCR(w, 16, __UINT16_C(0x8000))
EMU86_DEFINE_RCR(l, 32, __UINT32_C(0x80000000))
#if LIBEMU86_CONFIG_WANT_64BIT
EMU86_DEFINE_TZCNT(q, 64)
EMU86_DEFINE_LZCNT(q, 64)
EMU86_DEFINE_RCL(q, 64, __UINT64_C(0x8000000000000000))
EMU86_DEFINE_RCR(q, 64, __UINT64_C(0x8000000000000000))
#endif /* LIBEMU86_CONFIG_WANT_64BIT */

#undef EMU86_DEFINE_RCR
#undef EMU86_DEFINE_RCL
#undef EMU86_DEFINE_LZCNT
#undef EMU86_DEFINE_TZCNT

__DECL_END
#endif /* __CC__ */


#endif /* !_LIBEMU86_HELPERS_H */
