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
#ifndef _LIBEMU86_EFLAGS_H
#define _LIBEMU86_EFLAGS_H 1

#include "api.h"

#include <hybrid/__overflow.h>

#include <asm/sar.h>
#include <bits/types.h>
#include <i386-kos/asm/cpu-flags.h>

/* Helpers for calculating %eflags */
#ifdef __CC__
__DECL_BEGIN

/* ShiftArithmeticRight */
#define emu86_sarb(val, num_bits) sar((__int8_t)(val), num_bits)
#define emu86_sarw(val, num_bits) sar((__int16_t)(val), num_bits)
#define emu86_sarl(val, num_bits) sar((__int32_t)(val), num_bits)
#if LIBEMU86_CONFIG_WANT_64BIT
#define emu86_sarq(val, num_bits) sar((__int64_t)(val), num_bits)
#endif /* LIBEMU86_CONFIG_WANT_64BIT */

#define emu86_geteflags_SFb(value) ((__int8_t)(value) < 0 ? EFLAGS_SF : 0)
#define emu86_geteflags_SFw(value) ((__int16_t)(value) < 0 ? EFLAGS_SF : 0)
#define emu86_geteflags_SFl(value) ((__int32_t)(value) < 0 ? EFLAGS_SF : 0)

#define emu86_geteflags_ZFb(value) ((__uint8_t)(value) == 0 ? EFLAGS_ZF : 0)
#define emu86_geteflags_ZFw(value) ((__uint16_t)(value) == 0 ? EFLAGS_ZF : 0)
#define emu86_geteflags_ZFl(value) ((__uint32_t)(value) == 0 ? EFLAGS_ZF : 0)

/* Parity flag (s.a. `https://en.wikipedia.org/wiki/Parity_flag') */
__LOCAL __ATTR_CONST __uint32_t
__NOTHROW(LIBEMU86_CC emu86_geteflags_PFb)(__uint8_t value) {
	/* == POPCOUNT(value) & 1 ? 0 : EFLAGS_PF */
	value ^= value >> 4; /* 0xff -> 0x0f */
	value ^= value >> 2; /* 0x0f -> 0x03 */
	value ^= value >> 1; /* 0x03 -> 0x01 */
	return (value & 1)
	       ? /* Odd  parity */ 0
	       : /* Even parity */ EFLAGS_PF;
}

/* According to Wikipedia (see link above), x86 only considers the
 * least significant bit  in the calculation  of the parity  flag. */
#define emu86_geteflags_PFw(v) emu86_geteflags_PFb((__uint8_t)(v))
#define emu86_geteflags_PFl(v) emu86_geteflags_PFb((__uint8_t)(v))
#if LIBEMU86_CONFIG_WANT_64BIT
#define emu86_geteflags_SFq(value) ((__int64_t)(value) < 0 ? EFLAGS_SF : 0)
#define emu86_geteflags_ZFq(value) ((__uint64_t)(value) == 0 ? EFLAGS_ZF : 0)
#define emu86_geteflags_PFq(v) emu86_geteflags_PFb((__uint8_t)(v))
#endif /* LIBEMU86_CONFIG_WANT_64BIT */

/* Return a set of `EFLAGS_(SF|ZF|PF)' */
#define emu86_geteflags_testb(value) (emu86_geteflags_SFb(value) | emu86_geteflags_ZFb(value) | emu86_geteflags_PFb(value))
#define emu86_geteflags_testw(value) (emu86_geteflags_SFw(value) | emu86_geteflags_ZFw(value) | emu86_geteflags_PFw(value))
#define emu86_geteflags_testl(value) (emu86_geteflags_SFl(value) | emu86_geteflags_ZFl(value) | emu86_geteflags_PFl(value))
#if LIBEMU86_CONFIG_WANT_64BIT
#define emu86_geteflags_testq(value) (emu86_geteflags_SFq(value) | emu86_geteflags_ZFq(value) | emu86_geteflags_PFq(value))
#endif /* LIBEMU86_CONFIG_WANT_64BIT */

#define emu86_getflags_AF_add(lhs, rhs) \
	((__uint8_t)((__uint8_t)(lhs & 0xf) + (__uint8_t)(rhs & 0xf)) >= (__uint8_t)0x10)
#define emu86_getflags_AF_sub(lhs, rhs) \
	((__uint8_t)(lhs & 0xf) < (__uint8_t)(rhs & 0xf))


/* Return a set of `EFLAGS_(CF|OF|SF|ZF|AF|PF)' */
#define EMU86_GETEFLAGS_CMP_MASK         \
	(EFLAGS_CF | EFLAGS_OF | EFLAGS_SF | \
	 EFLAGS_ZF | EFLAGS_AF | EFLAGS_PF)
#define EMU86_DEFINE_CMP(bwlq, Nbits)                                         \
	__LOCAL __ATTR_CONST __uint32_t                                           \
	__NOTHROW(LIBEMU86_CC emu86_geteflags_cmp##bwlq)(__uint##Nbits##_t lhs,   \
	                                                 __uint##Nbits##_t rhs) { \
		__uint##Nbits##_t newval;                                             \
		__uint32_t result = 0;                                                \
		if (__hybrid_overflow_ssub((__int##Nbits##_t)lhs,                     \
		                           (__int##Nbits##_t)rhs,                     \
		                           (__int##Nbits##_t *)&newval))              \
			result |= EFLAGS_OF;                                              \
		if (__hybrid_overflow_usub(lhs, rhs, &newval))                        \
			result |= EFLAGS_CF;                                              \
		if (emu86_getflags_AF_sub(lhs, rhs))                                  \
			result |= EFLAGS_AF;                                              \
		result |= emu86_geteflags_test##bwlq(newval);                         \
		return result;                                                        \
	}
EMU86_DEFINE_CMP(b, 8)
EMU86_DEFINE_CMP(w, 16)
EMU86_DEFINE_CMP(l, 32)
#if LIBEMU86_CONFIG_WANT_64BIT
EMU86_DEFINE_CMP(q, 64)
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
#undef EMU86_DEFINE_CMP


__DECL_END
#endif /* __CC__ */


#endif /* !_LIBEMU86_EFLAGS_H */
