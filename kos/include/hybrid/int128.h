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
#ifndef __GUARD_HYBRID_INT128_H
#define __GUARD_HYBRID_INT128_H 1

#include "../__stdinc.h"
#include "__byteswap.h"
#include "typecore.h"

#ifdef __CC__
#if defined(__INT128_TYPE__) && defined(__UINT128_TYPE__)
#define __hybrid_int128_t  __INT128_TYPE__
#define __hybrid_uint128_t __UINT128_TYPE__

/* Static initializers */
#define __HYBRID_INT128_INIT8(val)   ((__INT128_TYPE__)(__INT8_TYPE__)(val))
#define __HYBRID_INT128_INIT16(val)  ((__INT128_TYPE__)(__INT16_TYPE__)(val))
#define __HYBRID_INT128_INIT32(val)  ((__INT128_TYPE__)(__INT32_TYPE__)(val))
#define __HYBRID_INT128_INIT64(val)  ((__INT128_TYPE__)(__INT64_TYPE__)(val))
#define __HYBRID_UINT128_INIT8(val)  ((__UINT128_TYPE__)(__UINT8_TYPE__)(val))
#define __HYBRID_UINT128_INIT16(val) ((__UINT128_TYPE__)(__UINT16_TYPE__)(val))
#define __HYBRID_UINT128_INIT32(val) ((__UINT128_TYPE__)(__UINT32_TYPE__)(val))
#define __HYBRID_UINT128_INIT64(val) ((__UINT128_TYPE__)(__UINT64_TYPE__)(val))
#define __HYBRID_INT128_INIT8N(_16, _15, _14, _13, _12, _11, _10, _9, _8, _7, _6, _5, _4, _3, _2, _1) \
	((__INT128_TYPE__)(__UINT8_TYPE__)(_1) | (__INT128_TYPE__)(__UINT8_TYPE__)(_2) << 8 |             \
	 (__INT128_TYPE__)(__UINT8_TYPE__)(_3) << 16 | (__INT128_TYPE__)(__UINT8_TYPE__)(_4) << 24 |      \
	 (__INT128_TYPE__)(__UINT8_TYPE__)(_5) << 32 | (__INT128_TYPE__)(__UINT8_TYPE__)(_6) << 40 |      \
	 (__INT128_TYPE__)(__UINT8_TYPE__)(_7) << 48 | (__INT128_TYPE__)(__UINT8_TYPE__)(_8) << 56 |      \
	 (__INT128_TYPE__)(__UINT8_TYPE__)(_9) << 64 | (__INT128_TYPE__)(__UINT8_TYPE__)(_10) << 72 |     \
	 (__INT128_TYPE__)(__UINT8_TYPE__)(_11) << 80 | (__INT128_TYPE__)(__UINT8_TYPE__)(_12) << 88 |    \
	 (__INT128_TYPE__)(__UINT8_TYPE__)(_13) << 96 | (__INT128_TYPE__)(__UINT8_TYPE__)(_14) << 104 |   \
	 (__INT128_TYPE__)(__UINT8_TYPE__)(_15) << 112 | (__INT128_TYPE__)(__UINT8_TYPE__)(_16) << 120)
#define __HYBRID_UINT128_INIT8N(_16, _15, _14, _13, _12, _11, _10, _9, _8, _7, _6, _5, _4, _3, _2, _1) \
	((__UINT128_TYPE__)(__UINT8_TYPE__)(_1) | (__UINT128_TYPE__)(__UINT8_TYPE__)(_2) << 8 |            \
	 (__UINT128_TYPE__)(__UINT8_TYPE__)(_3) << 16 | (__UINT128_TYPE__)(__UINT8_TYPE__)(_4) << 24 |     \
	 (__UINT128_TYPE__)(__UINT8_TYPE__)(_5) << 32 | (__UINT128_TYPE__)(__UINT8_TYPE__)(_6) << 40 |     \
	 (__UINT128_TYPE__)(__UINT8_TYPE__)(_7) << 48 | (__UINT128_TYPE__)(__UINT8_TYPE__)(_8) << 56 |     \
	 (__UINT128_TYPE__)(__UINT8_TYPE__)(_9) << 64 | (__UINT128_TYPE__)(__UINT8_TYPE__)(_10) << 72 |    \
	 (__UINT128_TYPE__)(__UINT8_TYPE__)(_11) << 80 | (__UINT128_TYPE__)(__UINT8_TYPE__)(_12) << 88 |   \
	 (__UINT128_TYPE__)(__UINT8_TYPE__)(_13) << 96 | (__UINT128_TYPE__)(__UINT8_TYPE__)(_14) << 104 |  \
	 (__UINT128_TYPE__)(__UINT8_TYPE__)(_15) << 112 | (__UINT128_TYPE__)(__UINT8_TYPE__)(_16) << 120)
#define __HYBRID_INT128_INIT16N(_8, _7, _6, _5, _4, _3, _2, _1)                                    \
	((__INT128_TYPE__)(__UINT16_TYPE__)(_1) | (__INT128_TYPE__)(__UINT16_TYPE__)(_2) << 16 |       \
	 (__INT128_TYPE__)(__UINT16_TYPE__)(_3) << 32 | (__INT128_TYPE__)(__UINT16_TYPE__)(_4) << 48 | \
	 (__INT128_TYPE__)(__UINT16_TYPE__)(_5) << 64 | (__INT128_TYPE__)(__UINT16_TYPE__)(_6) << 80 | \
	 (__INT128_TYPE__)(__UINT16_TYPE__)(_7) << 96 | (__INT128_TYPE__)(__UINT16_TYPE__)(_8) << 112)
#define __HYBRID_UINT128_INIT16N(_8, _7, _6, _5, _4, _3, _2, _1)                                     \
	((__UINT128_TYPE__)(__UINT16_TYPE__)(_1) | (__UINT128_TYPE__)(__UINT16_TYPE__)(_2) << 16 |       \
	 (__UINT128_TYPE__)(__UINT16_TYPE__)(_3) << 32 | (__UINT128_TYPE__)(__UINT16_TYPE__)(_4) << 48 | \
	 (__UINT128_TYPE__)(__UINT16_TYPE__)(_5) << 64 | (__UINT128_TYPE__)(__UINT16_TYPE__)(_6) << 80 | \
	 (__UINT128_TYPE__)(__UINT16_TYPE__)(_7) << 96 | (__UINT128_TYPE__)(__UINT16_TYPE__)(_8) << 112)
#define __HYBRID_INT128_INIT32N(_4, _3, _2, _1)                                              \
	((__INT128_TYPE__)(__UINT32_TYPE__)(_1) | (__INT128_TYPE__)(__UINT32_TYPE__)(_2) << 32 | \
	 (__INT128_TYPE__)(__UINT32_TYPE__)(_3) << 64 | (__INT128_TYPE__)(__UINT32_TYPE__)(_4) << 96)
#define __HYBRID_UINT128_INIT32N(_4, _3, _2, _1)                                               \
	((__UINT128_TYPE__)(__UINT32_TYPE__)(_1) | (__UINT128_TYPE__)(__UINT32_TYPE__)(_2) << 32 | \
	 (__UINT128_TYPE__)(__UINT32_TYPE__)(_3) << 64 | (__UINT128_TYPE__)(__UINT32_TYPE__)(_4) << 96)
#define __HYBRID_INT128_INIT64N(_2, _1) \
	((__INT128_TYPE__)(__UINT64_TYPE__)(_1) | (__INT128_TYPE__)(__UINT64_TYPE__)(_2) << 64)
#define __HYBRID_UINT128_INIT64N(_2, _1) \
	((__UINT128_TYPE__)(__UINT64_TYPE__)(_1) | (__UINT128_TYPE__)(__UINT64_TYPE__)(_2) << 64)

#define __hybrid_int128_vec8(var)   ((__INT8_TYPE__ *)&(var))
#define __hybrid_int128_vec16(var)  ((__INT16_TYPE__ *)&(var))
#define __hybrid_int128_vec32(var)  ((__INT32_TYPE__ *)&(var))
#define __hybrid_uint128_vec8(var)  ((__UINT8_TYPE__ *)&(var))
#define __hybrid_uint128_vec16(var) ((__UINT16_TYPE__ *)&(var))
#define __hybrid_uint128_vec32(var) ((__UINT32_TYPE__ *)&(var))
#define __hybrid_int128_vec64(var)  ((__INT64_TYPE__ *)&(var))
#define __hybrid_uint128_vec64(var) ((__UINT64_TYPE__ *)&(var))

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define __hybrid_int128_vec8_significand(var, i)   __hybrid_int128_vec8(var)[i]
#define __hybrid_int128_vec16_significand(var, i)  __hybrid_int128_vec16(var)[i]
#define __hybrid_int128_vec32_significand(var, i)  __hybrid_int128_vec32(var)[i]
#define __hybrid_uint128_vec8_significand(var, i)  __hybrid_uint128_vec8(var)[i]
#define __hybrid_uint128_vec16_significand(var, i) __hybrid_uint128_vec16(var)[i]
#define __hybrid_uint128_vec32_significand(var, i) __hybrid_uint128_vec32(var)[i]
#define __hybrid_int128_vec64_significand(var, i)  __hybrid_int128_vec64(var)[i]
#define __hybrid_uint128_vec64_significand(var, i) __hybrid_uint128_vec64(var)[i]
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __hybrid_int128_vec8_significand(var, i)   __hybrid_int128_vec8(var)[15 - (i)]
#define __hybrid_int128_vec16_significand(var, i)  __hybrid_int128_vec16(var)[7 - (i)]
#define __hybrid_int128_vec32_significand(var, i)  __hybrid_int128_vec32(var)[3 - (i)]
#define __hybrid_uint128_vec8_significand(var, i)  __hybrid_uint128_vec8(var)[15 - (i)]
#define __hybrid_uint128_vec16_significand(var, i) __hybrid_uint128_vec16(var)[7 - (i)]
#define __hybrid_uint128_vec32_significand(var, i) __hybrid_uint128_vec32(var)[3 - (i)]
#define __hybrid_int128_vec64_significand(var, i)  __hybrid_int128_vec64(var)[1 - (i)]
#define __hybrid_uint128_vec64_significand(var, i) __hybrid_uint128_vec64(var)[1 - (i)]
#else /* __BYTE_ORDER__ == ... */
#error "Unsupported byteorder"
#endif /* __BYTE_ORDER__ != ... */

#define __hybrid_int128_get8(var)      ((__INT8_TYPE__)(var))
#define __hybrid_int128_set8(var, v)   (void)((var) = (__INT128_TYPE__)(__INT8_TYPE__)(v))
#define __hybrid_uint128_get8(var)     ((__UINT8_TYPE__)(var))
#define __hybrid_uint128_set8(var, v)  (void)((var) = (__UINT128_TYPE__)(__UINT8_TYPE__)(v))
#define __hybrid_int128_get16(var)     ((__INT16_TYPE__)(var))
#define __hybrid_int128_set16(var, v)  (void)((var) = (__INT128_TYPE__)(__INT16_TYPE__)(v))
#define __hybrid_uint128_get16(var)    ((__UINT16_TYPE__)(var))
#define __hybrid_uint128_set16(var, v) (void)((var) = (__UINT128_TYPE__)(__UINT16_TYPE__)(v))
#define __hybrid_int128_get32(var)     ((__INT32_TYPE__)(var))
#define __hybrid_int128_set32(var, v)  (void)((var) = (__INT128_TYPE__)(__INT32_TYPE__)(v))
#define __hybrid_uint128_get32(var)    ((__UINT32_TYPE__)(var))
#define __hybrid_uint128_set32(var, v) (void)((var) = (__UINT128_TYPE__)(__UINT32_TYPE__)(v))
#define __hybrid_int128_get64(var)     ((__INT64_TYPE__)(var))
#define __hybrid_int128_set64(var, v)  (void)((var) = (__INT128_TYPE__)(__INT64_TYPE__)(v))
#define __hybrid_uint128_get64(var)    ((__UINT64_TYPE__)(var))
#define __hybrid_uint128_set64(var, v) (void)((var) = (__UINT128_TYPE__)(__UINT64_TYPE__)(v))
#define __hybrid_int128_set(var, v)    (void)((var) = (__INT128_TYPE__)(v))
#define __hybrid_uint128_set(var, v)   (void)((var) = (__UINT128_TYPE__)(v))

#define __hybrid_PRIVATE_uint128_pack8(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) \
	((__UINT128_TYPE__)(a) | (__UINT128_TYPE__)(b) << 8 |                              \
	 (__UINT128_TYPE__)(c) << 16 | (__UINT128_TYPE__)(d) << 24 |                       \
	 (__UINT128_TYPE__)(e) << 32 | (__UINT128_TYPE__)(f) << 40 |                       \
	 (__UINT128_TYPE__)(g) << 48 | (__UINT128_TYPE__)(h) << 56 |                       \
	 (__UINT128_TYPE__)(i) << 64 | (__UINT128_TYPE__)(j) << 72 |                       \
	 (__UINT128_TYPE__)(k) << 80 | (__UINT128_TYPE__)(l) << 88 |                       \
	 (__UINT128_TYPE__)(m) << 96 | (__UINT128_TYPE__)(n) << 104 |                      \
	 (__UINT128_TYPE__)(o) << 112 | (__UINT128_TYPE__)(p) << 120)
#define __hybrid_PRIVATE_uint128_pack16(a, b, c, d, e, f, g, h)  \
	((__UINT128_TYPE__)(a) | (__UINT128_TYPE__)(b) << 16 |       \
	 (__UINT128_TYPE__)(c) << 32 | (__UINT128_TYPE__)(d) << 48 | \
	 (__UINT128_TYPE__)(e) << 64 | (__UINT128_TYPE__)(f) << 80 | \
	 (__UINT128_TYPE__)(g) << 96 | (__UINT128_TYPE__)(h) << 112)
#define __hybrid_PRIVATE_uint128_pack32(a, b, c, d)        \
	((__UINT128_TYPE__)(a) | (__UINT128_TYPE__)(b) << 32 | \
	 (__UINT128_TYPE__)(c) << 64 | (__UINT128_TYPE__)(d) << 96)
#define __hybrid_PRIVATE_uint128_pack64(lo, hi) \
	((__UINT128_TYPE__)(lo) | ((__UINT128_TYPE__)(hi) << 64))
#define __hybrid_uint128_pack8(var, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) \
	(void)((var) = __hybrid_PRIVATE_uint128_pack8(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p))
#define __hybrid_uint128_pack16(var, a, b, c, d, e, f, g, h) \
	(void)((var) = __hybrid_PRIVATE_uint128_pack16(a, b, c, d, e, f, g, h))
#define __hybrid_uint128_pack32(var, a, b, c, d) \
	(void)((var) = __hybrid_PRIVATE_uint128_pack32(a, b, c, d))
#define __hybrid_uint128_pack64(var, lo, hi) \
	(void)((var) = __hybrid_PRIVATE_uint128_pack64(lo, hi))
#define __hybrid_int128_pack8(var, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) \
	(void)((var) = (__INT128_TYPE__)__hybrid_PRIVATE_uint128_pack8(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p))
#define __hybrid_int128_pack16(var, a, b, c, d, e, f, g, h) \
	(void)((var) = (__INT128_TYPE__)__hybrid_PRIVATE_uint128_pack16(a, b, c, d, e, f, g, h))
#define __hybrid_int128_pack32(var, a, b, c, d) \
	(void)((var) = (__INT128_TYPE__)__hybrid_PRIVATE_uint128_pack32(a, b, c, d))
#define __hybrid_int128_pack64(var, lo, hi) \
	(void)((var) = (__INT128_TYPE__)__hybrid_PRIVATE_uint128_pack64(lo, hi))
#define __hybrid_uint128_inc(var)                    (void)(++(var))
#define __hybrid_int128_inc(var)                     (void)(++(var))
#define __hybrid_uint128_dec(var)                    (void)(--(var))
#define __hybrid_int128_dec(var)                     (void)(--(var))
#define __hybrid_uint128_inv(var)                    (void)((var) = ~(var))
#define __hybrid_int128_inv(var)                     (void)((var) = ~(var))
#define __hybrid_int128_neg(var)                     (void)((var) = -(__INT128_TYPE__)(var))
#define __hybrid_int128_isneg(var)                   ((__INT128_TYPE__)(var) < 0)
#define __hybrid_uint128_and(var, v)                 (void)((var) &= (__UINT128_TYPE__)(v))
#define __hybrid_uint128_and8(var, v)                (void)((var) &= (__UINT128_TYPE__)(__UINT8_TYPE__)(v))
#define __hybrid_uint128_and16(var, v)               (void)((var) &= (__UINT128_TYPE__)(__UINT16_TYPE__)(v))
#define __hybrid_uint128_and32(var, v)               (void)((var) &= (__UINT128_TYPE__)(__UINT32_TYPE__)(v))
#define __hybrid_uint128_and64(var, v)               (void)((var) &= (__UINT128_TYPE__)(__UINT64_TYPE__)(v))
#define __hybrid_uint128_and128(var, v)              (void)((var) &= (__UINT128_TYPE__)(v))
#define __hybrid_int128_and(var, v)                  (void)((var) &= (__INT128_TYPE__)(v))
#define __hybrid_int128_and8(var, v)                 (void)((var) &= (__INT128_TYPE__)(__INT8_TYPE__)(v))
#define __hybrid_int128_and16(var, v)                (void)((var) &= (__INT128_TYPE__)(__INT16_TYPE__)(v))
#define __hybrid_int128_and32(var, v)                (void)((var) &= (__INT128_TYPE__)(__INT32_TYPE__)(v))
#define __hybrid_int128_and64(var, v)                (void)((var) &= (__INT128_TYPE__)(__INT64_TYPE__)(v))
#define __hybrid_int128_and128(var, v)               (void)((var) &= (__INT128_TYPE__)(v))
#define __hybrid_uint128_or(var, v)                  (void)((var) |= (__UINT128_TYPE__)(v))
#define __hybrid_uint128_or8(var, v)                 (void)((var) |= (__UINT128_TYPE__)(__UINT8_TYPE__)(v))
#define __hybrid_uint128_or16(var, v)                (void)((var) |= (__UINT128_TYPE__)(__UINT16_TYPE__)(v))
#define __hybrid_uint128_or32(var, v)                (void)((var) |= (__UINT128_TYPE__)(__UINT32_TYPE__)(v))
#define __hybrid_uint128_or64(var, v)                (void)((var) |= (__UINT128_TYPE__)(__UINT64_TYPE__)(v))
#define __hybrid_uint128_or128(var, v)               (void)((var) |= (__UINT128_TYPE__)(v))
#define __hybrid_int128_or(var, v)                   (void)((var) |= (__INT128_TYPE__)(v))
#define __hybrid_int128_or8(var, v)                  (void)((var) |= (__INT128_TYPE__)(__INT8_TYPE__)(v))
#define __hybrid_int128_or16(var, v)                 (void)((var) |= (__INT128_TYPE__)(__INT16_TYPE__)(v))
#define __hybrid_int128_or32(var, v)                 (void)((var) |= (__INT128_TYPE__)(__INT32_TYPE__)(v))
#define __hybrid_int128_or64(var, v)                 (void)((var) |= (__INT128_TYPE__)(__INT64_TYPE__)(v))
#define __hybrid_int128_or128(var, v)                (void)((var) |= (__INT128_TYPE__)(v))
#define __hybrid_uint128_xor(var, v)                 (void)((var) ^= (__UINT128_TYPE__)(v))
#define __hybrid_uint128_xor8(var, v)                (void)((var) ^= (__UINT128_TYPE__)(__UINT8_TYPE__)(v))
#define __hybrid_uint128_xor16(var, v)               (void)((var) ^= (__UINT128_TYPE__)(__UINT16_TYPE__)(v))
#define __hybrid_uint128_xor32(var, v)               (void)((var) ^= (__UINT128_TYPE__)(__UINT32_TYPE__)(v))
#define __hybrid_uint128_xor64(var, v)               (void)((var) ^= (__UINT128_TYPE__)(__UINT64_TYPE__)(v))
#define __hybrid_uint128_xor128(var, v)              (void)((var) ^= (__UINT128_TYPE__)(v))
#define __hybrid_int128_xor(var, v)                  (void)((var) ^= (__INT128_TYPE__)(v))
#define __hybrid_int128_xor8(var, v)                 (void)((var) ^= (__INT128_TYPE__)(__INT8_TYPE__)(v))
#define __hybrid_int128_xor16(var, v)                (void)((var) ^= (__INT128_TYPE__)(__INT16_TYPE__)(v))
#define __hybrid_int128_xor32(var, v)                (void)((var) ^= (__INT128_TYPE__)(__INT32_TYPE__)(v))
#define __hybrid_int128_xor64(var, v)                (void)((var) ^= (__INT128_TYPE__)(__INT64_TYPE__)(v))
#define __hybrid_int128_xor128(var, v)               (void)((var) ^= (__INT128_TYPE__)(v))
#define __hybrid_uint128_add(var, v)                 (void)((var) += (__UINT128_TYPE__)(v))
#define __hybrid_uint128_add8(var, v)                (void)((var) += (__UINT128_TYPE__)(__UINT8_TYPE__)(v))
#define __hybrid_uint128_add16(var, v)               (void)((var) += (__UINT128_TYPE__)(__UINT16_TYPE__)(v))
#define __hybrid_uint128_add32(var, v)               (void)((var) += (__UINT128_TYPE__)(__UINT32_TYPE__)(v))
#define __hybrid_uint128_add64(var, v)               (void)((var) += (__UINT128_TYPE__)(__UINT64_TYPE__)(v))
#define __hybrid_uint128_add128(var, v)              (void)((var) += (__UINT128_TYPE__)(v))
#define __hybrid_int128_add(var, v)                  (void)((var) += (__INT128_TYPE__)(v))
#define __hybrid_int128_add8(var, v)                 (void)((var) += (__INT128_TYPE__)(__INT8_TYPE__)(v))
#define __hybrid_int128_add16(var, v)                (void)((var) += (__INT128_TYPE__)(__INT16_TYPE__)(v))
#define __hybrid_int128_add32(var, v)                (void)((var) += (__INT128_TYPE__)(__INT32_TYPE__)(v))
#define __hybrid_int128_add64(var, v)                (void)((var) += (__INT128_TYPE__)(__INT64_TYPE__)(v))
#define __hybrid_int128_add128(var, v)               (void)((var) += (__INT128_TYPE__)(v))
#define __hybrid_uint128_sub(var, v)                 (void)((var) -= (__UINT128_TYPE__)(v))
#define __hybrid_uint128_sub8(var, v)                (void)((var) -= (__UINT128_TYPE__)(__UINT8_TYPE__)(v))
#define __hybrid_uint128_sub16(var, v)               (void)((var) -= (__UINT128_TYPE__)(__UINT16_TYPE__)(v))
#define __hybrid_uint128_sub32(var, v)               (void)((var) -= (__UINT128_TYPE__)(__UINT32_TYPE__)(v))
#define __hybrid_uint128_sub64(var, v)               (void)((var) -= (__UINT128_TYPE__)(__UINT64_TYPE__)(v))
#define __hybrid_uint128_sub128(var, v)              (void)((var) -= (__UINT128_TYPE__)(v))
#define __hybrid_int128_sub(var, v)                  (void)((var) -= (__INT128_TYPE__)(v))
#define __hybrid_int128_sub8(var, v)                 (void)((var) -= (__INT128_TYPE__)(__INT8_TYPE__)(v))
#define __hybrid_int128_sub16(var, v)                (void)((var) -= (__INT128_TYPE__)(__INT16_TYPE__)(v))
#define __hybrid_int128_sub32(var, v)                (void)((var) -= (__INT128_TYPE__)(__INT32_TYPE__)(v))
#define __hybrid_int128_sub64(var, v)                (void)((var) -= (__INT128_TYPE__)(__INT64_TYPE__)(v))
#define __hybrid_int128_sub128(var, v)               (void)((var) -= (__INT128_TYPE__)(v))
#define __hybrid_uint128_mul(var, v)                 (void)((var) *= (__UINT128_TYPE__)(v))
#define __hybrid_uint128_mul8(var, v)                (void)((var) *= (__UINT128_TYPE__)(__UINT8_TYPE__)(v))
#define __hybrid_uint128_mul16(var, v)               (void)((var) *= (__UINT128_TYPE__)(__UINT16_TYPE__)(v))
#define __hybrid_uint128_mul32(var, v)               (void)((var) *= (__UINT128_TYPE__)(__UINT32_TYPE__)(v))
#define __hybrid_uint128_mul64(var, v)               (void)((var) *= (__UINT128_TYPE__)(__UINT64_TYPE__)(v))
#define __hybrid_uint128_mul128(var, v)              (void)((var) *= (__UINT128_TYPE__)(v))
#define __hybrid_int128_mul(var, v)                  (void)((var) *= (__INT128_TYPE__)(v))
#define __hybrid_int128_mul8(var, v)                 (void)((var) *= (__INT128_TYPE__)(__INT8_TYPE__)(v))
#define __hybrid_int128_mul16(var, v)                (void)((var) *= (__INT128_TYPE__)(__INT16_TYPE__)(v))
#define __hybrid_int128_mul32(var, v)                (void)((var) *= (__INT128_TYPE__)(__INT32_TYPE__)(v))
#define __hybrid_int128_mul64(var, v)                (void)((var) *= (__INT128_TYPE__)(__INT64_TYPE__)(v))
#define __hybrid_int128_mul128(var, v)               (void)((var) *= (__INT128_TYPE__)(v))
#define __hybrid_uint128_divmod8(var, v, divres, modres) \
	(void)((divres) = (var) / (__UINT8_TYPE__)(v),       \
	       (modres) = (__UINT8_TYPE__)((var) % (__UINT8_TYPE__)(v)))
#define __hybrid_uint128_divmod16(var, v, divres, modres) \
	(void)((divres) = (var) / (__UINT16_TYPE__)(v),       \
	       (modres) = (__UINT16_TYPE__)((var) % (__UINT16_TYPE__)(v)))
#define __hybrid_uint128_divmod32(var, v, divres, modres) \
	(void)((divres) = (var) / (__UINT32_TYPE__)(v),       \
	       (modres) = (__UINT32_TYPE__)((var) % (__UINT32_TYPE__)(v)))
#define __hybrid_uint128_divmod64(var, v, divres, modres) \
	(void)((divres) = (var) / (__UINT64_TYPE__)(v),       \
	       (modres) = (__UINT64_TYPE__)((var) % (__UINT64_TYPE__)(v)))
#define __hybrid_uint128_divmod128(var, v, divres, modres) \
	(void)((divres) = (var) / (__UINT128_TYPE__)(v),       \
	       (modres) = (var) % (__UINT128_TYPE__)(v))
#define __hybrid_int128_divmod8(var, v, divres, modres) \
	(void)((divres) = (var) / (__INT8_TYPE__)(v),       \
	       (modres) = (__INT8_TYPE__)((var) % (__INT8_TYPE__)(v)))
#define __hybrid_int128_divmod16(var, v, divres, modres) \
	(void)((divres) = (var) / (__INT16_TYPE__)(v),       \
	       (modres) = (__INT16_TYPE__)((var) % (__INT16_TYPE__)(v)))
#define __hybrid_int128_divmod32(var, v, divres, modres) \
	(void)((divres) = (var) / (__INT32_TYPE__)(v),       \
	       (modres) = (__INT32_TYPE__)((var) % (__INT32_TYPE__)(v)))
#define __hybrid_int128_divmod64(var, v, divres, modres) \
	(void)((divres) = (var) / (__INT64_TYPE__)(v),       \
	       (modres) = (__INT64_TYPE__)((var) % (__INT64_TYPE__)(v)))
#define __hybrid_int128_divmod128(var, v, divres, modres) \
	(void)((divres) = (var) / (__INT128_TYPE__)(v),       \
	       (modres) = (var) % (__INT128_TYPE__)(v))
#define __hybrid_uint128_mod8_r(var, v, res)         (void)((res) = (__UINT8_TYPE__)((var) % (__UINT8_TYPE__)(v)))
#define __hybrid_uint128_mod16_r(var, v, res)        (void)((res) = (__UINT16_TYPE__)((var) % (__UINT16_TYPE__)(v)))
#define __hybrid_uint128_mod32_r(var, v, res)        (void)((res) = (__UINT32_TYPE__)((var) % (__UINT32_TYPE__)(v)))
#define __hybrid_uint128_mod64_r(var, v, res)        (void)((res) = (__UINT64_TYPE__)((var) % (__UINT64_TYPE__)(v)))
#define __hybrid_int128_mod8_r(var, v, res)          (void)((res) = (__INT8_TYPE__)((var) % (__INT8_TYPE__)(v)))
#define __hybrid_int128_mod16_r(var, v, res)         (void)((res) = (__INT16_TYPE__)((var) % (__INT16_TYPE__)(v)))
#define __hybrid_int128_mod32_r(var, v, res)         (void)((res) = (__INT32_TYPE__)((var) % (__INT32_TYPE__)(v)))
#define __hybrid_int128_mod64_r(var, v, res)         (void)((res) = (__INT64_TYPE__)((var) % (__INT64_TYPE__)(v)))
#define __hybrid_uint128_div(var, v)                 (void)((var) /= (v))
#define __hybrid_uint128_div8(var, v)                (void)((var) /= (__UINT8_TYPE__)(v))
#define __hybrid_uint128_div16(var, v)               (void)((var) /= (__UINT16_TYPE__)(v))
#define __hybrid_uint128_div32(var, v)               (void)((var) /= (__UINT32_TYPE__)(v))
#define __hybrid_uint128_div64(var, v)               (void)((var) /= (__UINT64_TYPE__)(v))
#define __hybrid_uint128_div128(var, v)              (void)((var) /= (__UINT128_TYPE__)(v))
#define __hybrid_int128_div(var, v)                  (void)((var) /= (v))
#define __hybrid_int128_div8(var, v)                 (void)((var) /= (__INT8_TYPE__)(v))
#define __hybrid_int128_div16(var, v)                (void)((var) /= (__INT16_TYPE__)(v))
#define __hybrid_int128_div32(var, v)                (void)((var) /= (__INT32_TYPE__)(v))
#define __hybrid_int128_div64(var, v)                (void)((var) /= (__INT64_TYPE__)(v))
#define __hybrid_int128_div128(var, v)               (void)((var) /= (__INT128_TYPE__)(v))
#define __hybrid_uint128_mod(var, v)                 (void)((var) %= (v))
#define __hybrid_uint128_mod8(var, v)                (void)((var) %= (__UINT8_TYPE__)(v))
#define __hybrid_uint128_mod16(var, v)               (void)((var) %= (__UINT16_TYPE__)(v))
#define __hybrid_uint128_mod32(var, v)               (void)((var) %= (__UINT32_TYPE__)(v))
#define __hybrid_uint128_mod64(var, v)               (void)((var) %= (__UINT64_TYPE__)(v))
#define __hybrid_uint128_mod128(var, v)              (void)((var) %= (__UINT128_TYPE__)(v))
#define __hybrid_int128_mod(var, v)                  (void)((var) %= (v))
#define __hybrid_int128_mod8(var, v)                 (void)((var) %= (__INT8_TYPE__)(v))
#define __hybrid_int128_mod16(var, v)                (void)((var) %= (__INT16_TYPE__)(v))
#define __hybrid_int128_mod32(var, v)                (void)((var) %= (__INT32_TYPE__)(v))
#define __hybrid_int128_mod64(var, v)                (void)((var) %= (__INT64_TYPE__)(v))
#define __hybrid_int128_mod128(var, v)               (void)((var) %= (__INT128_TYPE__)(v))
#define __hybrid_uint128_shl32(var, shift)           (void)((var) <<= (shift))
#define __hybrid_uint128_shr32(var, shift)           (void)((var) >>= (shift))
#define __hybrid_int128_shl32(var, shift)            (void)((var) <<= (shift))
#define __hybrid_int128_shr32(var, shift)            (void)((var) >>= (shift))
#define __hybrid_uint128_shl64(var, shift)           (void)((var) <<= (shift))
#define __hybrid_uint128_shr64(var, shift)           (void)((var) >>= (shift))
#define __hybrid_int128_shl64(var, shift)            (void)((var) <<= (shift))
#define __hybrid_int128_shr64(var, shift)            (void)((var) >>= (shift))
#define __hybrid_uint128_shl(var, shift)             (void)((var) <<= (shift))
#define __hybrid_uint128_shr(var, shift)             (void)((var) >>= (shift))
#define __hybrid_int128_shl(var, shift)              (void)((var) <<= (shift))
#define __hybrid_int128_shr(var, shift)              (void)((var) >>= (shift))
#define __hybrid_uint128_shl_overflows(var, shift)   (((__UINT128_TYPE__)(var) >> (128 - (shift))) != 0)
#define __hybrid_uint128_shr_overflows(var, shift)   ((((__UINT128_TYPE__)(var) >> (shift)) << (shift)) != (__UINT128_TYPE__)(var))
#define __hybrid_int128_shl_overflows                __hybrid_uint128_shl_overflows
#define __hybrid_uint128_shl32_overflows             __hybrid_uint128_shl_overflows
#define __hybrid_int128_shl32_overflows              __hybrid_uint128_shl_overflows
#define __hybrid_uint128_shl64_overflows             __hybrid_uint128_shl_overflows
#define __hybrid_int128_shl64_overflows              __hybrid_uint128_shl_overflows
#define __hybrid_int128_shr_overflows                __hybrid_uint128_shr_overflows
#define __hybrid_uint128_shr32_overflows             __hybrid_uint128_shr_overflows
#define __hybrid_int128_shr32_overflows              __hybrid_uint128_shr_overflows
#define __hybrid_uint128_shr64_overflows             __hybrid_uint128_shr_overflows
#define __hybrid_int128_shr64_overflows              __hybrid_uint128_shr_overflows
#define __hybrid_int128_setzero(var)                 (void)((var) = (__INT128_TYPE__)0)
#define __hybrid_int128_iszero(var)                  ((var) == (__INT128_TYPE__)0)
#define __hybrid_uint128_setzero(var)                (void)((var) = (__UINT128_TYPE__)0)
#define __hybrid_uint128_iszero(var)                 ((var) == (__UINT128_TYPE__)0)
#define __hybrid_int128_setone(var)                  (void)((var) = (__INT128_TYPE__)1)
#define __hybrid_int128_isone(var)                   ((var) == (__INT128_TYPE__)1)
#define __hybrid_uint128_setone(var)                 (void)((var) = (__UINT128_TYPE__)1)
#define __hybrid_uint128_isone(var)                  ((var) == (__UINT128_TYPE__)1)
#define __hybrid_int128_setminusone(var)             (void)((var) = (__INT128_TYPE__)-1)
#define __hybrid_int128_isminusone(var)              ((var) == (__INT128_TYPE__)-1)
#ifdef __PRIVATE_MIN_S16
#define __PRIVATE_HYBRID_INT128_SMIN                 (__INT128_TYPE__)__PRIVATE_MIN_S16
#define __PRIVATE_HYBRID_INT128_SMAX                 (__INT128_TYPE__)__PRIVATE_MAX_S16
#else /* __PRIVATE_MIN_S16 */
#define __PRIVATE_HYBRID_INT128_SMIN                 ((__INT128_TYPE__)__INT64_C(0x8000000000000000) << 64)
#define __PRIVATE_HYBRID_INT128_SMAX                 (((__INT128_TYPE__)__INT64_C(0x7fffffffffffffff) << 64) | (__INT128_TYPE__)__UINT64_C(0xffffffffffffffff))
#endif /* !__PRIVATE_MIN_S16 */
#define __hybrid_int128_setmin(var)                  (void)((var) = __PRIVATE_HYBRID_INT128_SMIN)
#define __hybrid_int128_ismin(var)                   ((var) == __PRIVATE_HYBRID_INT128_SMIN)
#define __hybrid_int128_setmax(var)                  (void)((var) = __PRIVATE_HYBRID_INT128_SMAX)
#define __hybrid_int128_ismax(var)                   ((var) == __PRIVATE_HYBRID_INT128_SMAX)
#define __hybrid_uint128_setmin                      __hybrid_uint128_setzero
#define __hybrid_uint128_ismax(var)                  ((var) == (__UINT128_TYPE__)-1)
#define __hybrid_uint128_ismin                       __hybrid_uint128_iszero
#define __hybrid_uint128_setmax(var)                 ((var) = (__UINT128_TYPE__)-1)
#define __hybrid_uint128_is8bit(var)                 ((__UINT128_TYPE__)(var) <= __UINT8_C(0xff))
#define __hybrid_uint128_is16bit(var)                ((__UINT128_TYPE__)(var) <= __UINT16_C(0xffff))
#define __hybrid_uint128_is32bit(var)                ((__UINT128_TYPE__)(var) <= __UINT32_C(0xffffffff))
#define __hybrid_uint128_is64bit(var)                ((__UINT128_TYPE__)(var) <= __UINT64_C(0xffffffffffffffff))
#define __hybrid_int128_is8bit(var)                  ((__INT128_TYPE__)(var) >= __PRIVATE_MIN_S1 && (__INT128_TYPE__)(var) <= __PRIVATE_MAX_S1)
#define __hybrid_int128_is16bit(var)                 ((__INT128_TYPE__)(var) >= __PRIVATE_MIN_S2 && (__INT128_TYPE__)(var) <= __PRIVATE_MAX_S2)
#define __hybrid_int128_is32bit(var)                 ((__INT128_TYPE__)(var) >= __PRIVATE_MIN_S4 && (__INT128_TYPE__)(var) <= __PRIVATE_MAX_S4)
#define __hybrid_int128_is64bit(var)                 ((__INT128_TYPE__)(var) >= __PRIVATE_MIN_S8 && (__INT128_TYPE__)(var) <= __PRIVATE_MAX_S8)
#define __hybrid_uint128_eq(var, v)                  ((__UINT128_TYPE__)(var) == (__UINT128_TYPE__)(v))
#define __hybrid_uint128_eq8(var, v)                 ((__UINT128_TYPE__)(var) == (__UINT128_TYPE__)(__UINT8_TYPE__)(v))
#define __hybrid_uint128_eq16(var, v)                ((__UINT128_TYPE__)(var) == (__UINT128_TYPE__)(__UINT16_TYPE__)(v))
#define __hybrid_uint128_eq32(var, v)                ((__UINT128_TYPE__)(var) == (__UINT128_TYPE__)(__UINT32_TYPE__)(v))
#define __hybrid_uint128_eq64(var, v)                ((__UINT128_TYPE__)(var) == (__UINT128_TYPE__)(__UINT64_TYPE__)(v))
#define __hybrid_uint128_eq128(var, v)               ((__UINT128_TYPE__)(var) == (__UINT128_TYPE__)(v))
#define __hybrid_int128_eq(var, v)                   ((__INT128_TYPE__)(var) == (__INT128_TYPE__)(v))
#define __hybrid_int128_eq8(var, v)                  ((__INT128_TYPE__)(var) == (__INT128_TYPE__)(__INT8_TYPE__)(v))
#define __hybrid_int128_eq16(var, v)                 ((__INT128_TYPE__)(var) == (__INT128_TYPE__)(__INT16_TYPE__)(v))
#define __hybrid_int128_eq32(var, v)                 ((__INT128_TYPE__)(var) == (__INT128_TYPE__)(__INT32_TYPE__)(v))
#define __hybrid_int128_eq64(var, v)                 ((__INT128_TYPE__)(var) == (__INT128_TYPE__)(__INT64_TYPE__)(v))
#define __hybrid_int128_eq128(var, v)                ((__INT128_TYPE__)(var) == (__INT128_TYPE__)(v))
#define __hybrid_uint128_lo(var, v)                  ((__UINT128_TYPE__)(var) < (__UINT128_TYPE__)(v))
#define __hybrid_uint128_lo8(var, v)                 ((__UINT128_TYPE__)(var) < (__UINT128_TYPE__)(__UINT8_TYPE__)(v))
#define __hybrid_uint128_lo16(var, v)                ((__UINT128_TYPE__)(var) < (__UINT128_TYPE__)(__UINT16_TYPE__)(v))
#define __hybrid_uint128_lo32(var, v)                ((__UINT128_TYPE__)(var) < (__UINT128_TYPE__)(__UINT32_TYPE__)(v))
#define __hybrid_uint128_lo64(var, v)                ((__UINT128_TYPE__)(var) < (__UINT128_TYPE__)(__UINT64_TYPE__)(v))
#define __hybrid_uint128_lo128(var, v)               ((__UINT128_TYPE__)(var) < (__UINT128_TYPE__)(v))
#define __hybrid_int128_lo(var, v)                   ((__INT128_TYPE__)(var) < (__INT128_TYPE__)(v))
#define __hybrid_int128_lo8(var, v)                  ((__INT128_TYPE__)(var) < (__INT128_TYPE__)(__INT8_TYPE__)(v))
#define __hybrid_int128_lo16(var, v)                 ((__INT128_TYPE__)(var) < (__INT128_TYPE__)(__INT16_TYPE__)(v))
#define __hybrid_int128_lo32(var, v)                 ((__INT128_TYPE__)(var) < (__INT128_TYPE__)(__INT32_TYPE__)(v))
#define __hybrid_int128_lo64(var, v)                 ((__INT128_TYPE__)(var) < (__INT128_TYPE__)(__INT64_TYPE__)(v))
#define __hybrid_int128_lo128(var, v)                ((__INT128_TYPE__)(var) < (__INT128_TYPE__)(v))
#define __hybrid_uint128_le(var, v)                  ((__UINT128_TYPE__)(var) <= (__UINT128_TYPE__)(v))
#define __hybrid_uint128_le8(var, v)                 ((__UINT128_TYPE__)(var) <= (__UINT128_TYPE__)(__UINT8_TYPE__)(v))
#define __hybrid_uint128_le16(var, v)                ((__UINT128_TYPE__)(var) <= (__UINT128_TYPE__)(__UINT16_TYPE__)(v))
#define __hybrid_uint128_le32(var, v)                ((__UINT128_TYPE__)(var) <= (__UINT128_TYPE__)(__UINT32_TYPE__)(v))
#define __hybrid_uint128_le64(var, v)                ((__UINT128_TYPE__)(var) <= (__UINT128_TYPE__)(__UINT64_TYPE__)(v))
#define __hybrid_uint128_le128(var, v)               ((__UINT128_TYPE__)(var) <= (__UINT128_TYPE__)(v))
#define __hybrid_int128_le(var, v)                   ((__INT128_TYPE__)(var) <= (__INT128_TYPE__)(v))
#define __hybrid_int128_le8(var, v)                  ((__INT128_TYPE__)(var) <= (__INT128_TYPE__)(__INT8_TYPE__)(v))
#define __hybrid_int128_le16(var, v)                 ((__INT128_TYPE__)(var) <= (__INT128_TYPE__)(__INT16_TYPE__)(v))
#define __hybrid_int128_le32(var, v)                 ((__INT128_TYPE__)(var) <= (__INT128_TYPE__)(__INT32_TYPE__)(v))
#define __hybrid_int128_le64(var, v)                 ((__INT128_TYPE__)(var) <= (__INT128_TYPE__)(__INT64_TYPE__)(v))
#define __hybrid_int128_le128(var, v)                ((__INT128_TYPE__)(var) <= (__INT128_TYPE__)(v))
#define __hybrid_int128_bswap(var)                   (void)((var) = (__INT128_TYPE__)__hybrid_bswap128(var))
#define __hybrid_uint128_bswap(var)                  (void)((var) = (__UINT128_TYPE__)__hybrid_bswap128(var))
#define __hybrid_int128_copy(dst, src)               (void)((dst) = (src))
#define __hybrid_uint128_copy(dst, src)              (void)((dst) = (src))
#define __hybrid_uint128_assigned(var)               ((__INT128_TYPE__)(var))
#define __hybrid_int128_asunsigned(var)              ((__UINT128_TYPE__)(var))

/* Floor division / modulo */
#define __hybrid_PRIVATE_int128_floordivmodT_mustadjust(Ts, rhs, modres) \
	(((Ts)(modres) < 0 && (Ts)(rhs) > 0) || ((Ts)(modres) > 0 && (Ts)(rhs) < 0))
#define __hybrid_PRIVATE_int128_floordivmodT_doadjust_mod(Ts, rhs, modres) \
	(__hybrid_PRIVATE_int128_floordivmodT_mustadjust(Ts, rhs, modres) ? (void)((modres) += (Ts)(rhs)) : (void)0)
#define __hybrid_PRIVATE_int128_floordivmodT_doadjust_div(Ts, rhs, divres, modres) \
	(__hybrid_PRIVATE_int128_floordivmodT_mustadjust(Ts, rhs, modres) ? (void)--(divres) : (void)0)
#define __hybrid_PRIVATE_int128_floordivmodT_doadjust_divmod(Ts, rhs, divres, modres) \
	(__hybrid_PRIVATE_int128_floordivmodT_mustadjust(Ts, rhs, modres) ? (void)((modres) += (Ts)(rhs), --(divres)) : (void)0)
#define __hybrid_PRIVATE_int128_floordivmod_mustadjust(rhs, modres) \
	(((modres) < 0 && (rhs) > 0) || ((modres) > 0 && (rhs) < 0))
#define __hybrid_PRIVATE_int128_floordivmod_doadjust_mod(rhs, modres) \
	(__hybrid_PRIVATE_int128_floordivmod_mustadjust(rhs, modres) ? (void)((modres) += (rhs)) : (void)0)
#define __hybrid_PRIVATE_int128_floordivmod_doadjust_div(rhs, divres, modres) \
	(__hybrid_PRIVATE_int128_floordivmod_mustadjust(rhs, modres) ? (void)--(divres) : (void)0)
#define __hybrid_PRIVATE_int128_floordivmod_doadjust_divmod(rhs, divres, modres) \
	(__hybrid_PRIVATE_int128_floordivmod_mustadjust(rhs, modres) ? (void)((modres) += (rhs), --(divres)) : (void)0)
#define __hybrid_int128_floordivmod(var, v, divres, modres) \
	((divres) = (var) / (v), (modres) = (var) % (v),        \
	 __hybrid_PRIVATE_int128_floordivmod_doadjust_divmod(v, divres, modres))
#define __hybrid_int128_floordivmod8(var, v, divres, modres)  \
	((divres) = (var) / (__INT8_TYPE__)(v),                   \
	 (modres) = (__UINT8_TYPE__)((var) % (__INT8_TYPE__)(v)), \
	 __hybrid_PRIVATE_int128_floordivmodT_doadjust_divmod(__INT8_TYPE__, v, divres, modres))
#define __hybrid_int128_floordivmod16(var, v, divres, modres)   \
	((divres) = (var) / (__INT16_TYPE__)(v),                    \
	 (modres) = (__UINT16_TYPE__)((var) % (__INT16_TYPE__)(v)), \
	 __hybrid_PRIVATE_int128_floordivmodT_doadjust_divmod(__INT16_TYPE__, v, divres, modres))
#define __hybrid_int128_floordivmod32(var, v, divres, modres)   \
	((divres) = (var) / (__INT32_TYPE__)(v),                    \
	 (modres) = (__UINT32_TYPE__)((var) % (__INT32_TYPE__)(v)), \
	 __hybrid_PRIVATE_int128_floordivmodT_doadjust_divmod(__INT32_TYPE__, v, divres, modres))
#define __hybrid_int128_floordivmod64(var, v, divres, modres)   \
	((divres) = (var) / (__INT64_TYPE__)(v),                    \
	 (modres) = (__UINT64_TYPE__)((var) % (__INT64_TYPE__)(v)), \
	 __hybrid_PRIVATE_int128_floordivmodT_doadjust_divmod(__INT64_TYPE__, v, divres, modres))
#define __hybrid_int128_floordivmod128(var, v, divres, modres) \
	((divres) = (var) / (__INT128_TYPE__)(v),                  \
	 (modres) = (var) % (__INT128_TYPE__)(v),                  \
	 __hybrid_PRIVATE_int128_floordivmodT_doadjust_divmod(__INT128_TYPE__, v, divres, modres))
#define __hybrid_int128_floormod8_r(var, v, res)   ((res) = (__UINT8_TYPE__)((var) % (__INT128_TYPE__)(__INT8_TYPE__)(v)), __hybrid_PRIVATE_int128_floordivmodT_doadjust_mod(__INT8_TYPE__, v, res))
#define __hybrid_int128_floormod16_r(var, v, res)  ((res) = (__UINT16_TYPE__)((var) % (__INT128_TYPE__)(__INT16_TYPE__)(v)), __hybrid_PRIVATE_int128_floordivmodT_doadjust_mod(__INT16_TYPE__, v, res))
#define __hybrid_int128_floormod32_r(var, v, res)  ((res) = (__UINT32_TYPE__)((var) % (__INT128_TYPE__)(__INT32_TYPE__)(v)), __hybrid_PRIVATE_int128_floordivmodT_doadjust_mod(__INT32_TYPE__, v, res))
#define __hybrid_int128_floormod64_r(var, v, res)  ((res) = (__UINT64_TYPE__)((var) % (__INT128_TYPE__)(__INT64_TYPE__)(v)), __hybrid_PRIVATE_int128_floordivmodT_doadjust_mod(__INT64_TYPE__, v, res))
#define __hybrid_int128_floormod(var, v)           (void)((var) %= (v), __hybrid_PRIVATE_int128_floordivmod_doadjust_mod(v, var))
#define __hybrid_int128_floormod8(var, v)          (void)((var) %= (__INT8_TYPE__)(v), __hybrid_PRIVATE_int128_floordivmodT_doadjust_mod(__INT8_TYPE__, v, var))
#define __hybrid_int128_floormod16(var, v)         (void)((var) %= (__INT16_TYPE__)(v), __hybrid_PRIVATE_int128_floordivmodT_doadjust_mod(__INT16_TYPE__, v, var))
#define __hybrid_int128_floormod32(var, v)         (void)((var) %= (__INT32_TYPE__)(v), __hybrid_PRIVATE_int128_floordivmodT_doadjust_mod(__INT32_TYPE__, v, var))
#define __hybrid_int128_floormod64(var, v)         (void)((var) %= (__INT64_TYPE__)(v), __hybrid_PRIVATE_int128_floordivmodT_doadjust_mod(__INT64_TYPE__, v, var))
#define __hybrid_int128_floormod128(var, v)        (void)((var) %= (__INT128_TYPE__)(v), __hybrid_PRIVATE_int128_floordivmodT_doadjust_mod(__INT128_TYPE__, v, var))

#define __hybrid_int128_floordiv8(var, v)   __hybrid_PRIVATE_int128_floordiv8(&(var), (__INT8_TYPE__)(v))
#define __hybrid_int128_floordiv16(var, v)  __hybrid_PRIVATE_int128_floordiv16(&(var), (__INT16_TYPE__)(v))
#define __hybrid_int128_floordiv32(var, v)  __hybrid_PRIVATE_int128_floordiv32(&(var), (__INT32_TYPE__)(v))
#define __hybrid_int128_floordiv64(var, v)  __hybrid_PRIVATE_int128_floordiv64(&(var), (__INT64_TYPE__)(v))
#define __hybrid_int128_floordiv128(var, v) __hybrid_PRIVATE_int128_floordiv128(&(var), &(v))

__DECL_BEGIN

__LOCAL __ATTR_INOUT(1) void
(__hybrid_PRIVATE_int128_floordiv8)(__hybrid_int128_t *__self, __INT8_TYPE__ __v) {
	__INT8_TYPE__ __temp = *__self % __v;
	*__self /= __v;
	__hybrid_PRIVATE_int128_floordivmodT_doadjust_div(__INT8_TYPE__, __v, *__self, __temp);
}

__LOCAL __ATTR_INOUT(1) void
(__hybrid_PRIVATE_int128_floordiv16)(__hybrid_int128_t *__self, __INT16_TYPE__ __v) {
	__INT16_TYPE__ __temp = *__self % __v;
	*__self /= __v;
	__hybrid_PRIVATE_int128_floordivmodT_doadjust_div(__INT16_TYPE__, __v, *__self, __temp);
}

__LOCAL __ATTR_INOUT(1) void
(__hybrid_PRIVATE_int128_floordiv32)(__hybrid_int128_t *__self, __INT32_TYPE__ __v) {
	__INT32_TYPE__ __temp = *__self % __v;
	*__self /= __v;
	__hybrid_PRIVATE_int128_floordivmodT_doadjust_div(__INT32_TYPE__, __v, *__self, __temp);
}

__LOCAL __ATTR_INOUT(1) void
(__hybrid_PRIVATE_int128_floordiv64)(__hybrid_int128_t *__self, __INT64_TYPE__ __v) {
	__INT64_TYPE__ __temp = *__self % __v;
	*__self /= __v;
	__hybrid_PRIVATE_int128_floordivmodT_doadjust_div(__INT64_TYPE__, __v, *__self, __temp);
}

__LOCAL __ATTR_INOUT(1) void
(__hybrid_PRIVATE_int128_floordiv128)(__hybrid_int128_t *__self, __INT128_TYPE__ const *__pv) {
	__INT128_TYPE__ __temp = *__self % *__pv;
	*__self /= *__pv;
	__hybrid_PRIVATE_int128_floordivmodT_doadjust_div(__INT128_TYPE__, *__pv, *__self, __temp);
}

__DECL_END

#ifdef __NO_builtin_choose_expr
#define __hybrid_int128_floordiv(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_floordiv8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_floordiv16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_int128_floordiv32(var, v) : \
	                  __hybrid_int128_floordiv64(var, v))
#else /* __NO_builtin_choose_expr */
#define __hybrid_int128_floordiv(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_floordiv8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_floordiv16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_int128_floordiv32(var, v), \
	                                      __hybrid_int128_floordiv64(var, v))))
#endif /* !__NO_builtin_choose_expr */
#else /* __INT128_TYPE__ && __UINT128_TYPE__ */
#if defined(__cplusplus) && defined(WANT_INT128_CXX_INTEGRATION)
#include "../__stdcxx.h"
#endif /* __cplusplus && WANT_INT128_CXX_INTEGRATION */

#include "__overflow.h"
#include "byteorder.h"

/*[[[config __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC: bool = defined(__UINT64_TYPE__) && __SIZEOF_BUSINT__ >= 8]]]*/
#ifdef __HYBRID_INT128_CONFIG_NO_64BIT_ARITHMETIC
#undef __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
#elif !defined(__HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC)
#if defined(__UINT64_TYPE__) && __SIZEOF_BUSINT__ >= 8
#define __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
#else /* __UINT64_TYPE__ && __SIZEOF_BUSINT__ >= 8 */
#define __HYBRID_INT128_CONFIG_NO_64BIT_ARITHMETIC
#endif /* !__UINT64_TYPE__ || __SIZEOF_BUSINT__ < 8 */
#elif (-__HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC - 1) == -1
#undef __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
#define __HYBRID_INT128_CONFIG_NO_64BIT_ARITHMETIC
#endif /* ... */
/*[[[end]]]*/

#define __HYBRID_PRIVATE_INT128_SIGN(val) ((val) < 0 ? 0xff : 0)

/* Static initializers */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define __HYBRID_PRIVATE_INT128_GROUP16(val) (__UINT8_TYPE__)((val) & 0xff), (__UINT8_TYPE__)(((val) >> 8) & 0xff)
#define __HYBRID_PRIVATE_INT128_GROUP32(val) (__UINT8_TYPE__)((val) & 0xff), (__UINT8_TYPE__)(((val) >> 8) & 0xff), (__UINT8_TYPE__)(((val) >> 16) & 0xff), (__UINT8_TYPE__)(((val) >> 24) & 0xff)
#define __HYBRID_INT128_INIT8(val)   { { val, __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val) } }
#define __HYBRID_INT128_INIT16(val)  { { __HYBRID_PRIVATE_INT128_GROUP16(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val) } }
#define __HYBRID_INT128_INIT32(val)  { { __HYBRID_PRIVATE_INT128_GROUP32(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val) } }
#define __HYBRID_UINT128_INIT8(val)  { { val, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } }
#define __HYBRID_UINT128_INIT16(val) { { __HYBRID_PRIVATE_INT128_GROUP16(val), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } }
#define __HYBRID_UINT128_INIT32(val) { { __HYBRID_PRIVATE_INT128_GROUP32(val), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } }
#define __HYBRID_INT128_INIT8N(_16, _15, _14, _13, _12, _11, _10, _9, _8, _7, _6, _5, _4, _3, _2, _1) \
	{ { _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16 } }
#define __HYBRID_INT128_INIT16N(_8, _7, _6, _5, _4, _3, _2, _1) \
	{ { __HYBRID_PRIVATE_INT128_GROUP16(_1), __HYBRID_PRIVATE_INT128_GROUP16(_2), __HYBRID_PRIVATE_INT128_GROUP16(_3), __HYBRID_PRIVATE_INT128_GROUP16(_4), __HYBRID_PRIVATE_INT128_GROUP16(_5), __HYBRID_PRIVATE_INT128_GROUP16(_6), __HYBRID_PRIVATE_INT128_GROUP16(_7), __HYBRID_PRIVATE_INT128_GROUP16(_8) } }
#define __HYBRID_INT128_INIT32N(_4, _3, _2, _1) \
	{ { __HYBRID_PRIVATE_INT128_GROUP32(_1), __HYBRID_PRIVATE_INT128_GROUP32(_2), __HYBRID_PRIVATE_INT128_GROUP32(_3), __HYBRID_PRIVATE_INT128_GROUP32(_4) } }
#ifdef __UINT64_TYPE__
#define __HYBRID_PRIVATE_INT128_GROUP64(val) (__UINT8_TYPE__)((val) & 0xff), (__UINT8_TYPE__)(((val) >> 8) & 0xff), (__UINT8_TYPE__)(((val) >> 16) & 0xff), (__UINT8_TYPE__)(((val) >> 24) & 0xff), (__UINT8_TYPE__)(((val) >> 32) & 0xff), (__UINT8_TYPE__)(((val) >> 40) & 0xff), (__UINT8_TYPE__)(((val) >> 48) & 0xff), (__UINT8_TYPE__)(((val) >> 56) & 0xff)
#define __HYBRID_INT128_INIT64(val)     { { __HYBRID_PRIVATE_INT128_GROUP64(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val) } }
#define __HYBRID_UINT128_INIT64(val)    { { __HYBRID_PRIVATE_INT128_GROUP64(val), 0, 0, 0, 0, 0, 0, 0, 0 } }
#define __HYBRID_INT128_INIT64N(_2, _1) { { __HYBRID_PRIVATE_INT128_GROUP64(_1), __HYBRID_PRIVATE_INT128_GROUP64(_2) } }
#endif /* __UINT64_TYPE__ */
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __HYBRID_PRIVATE_INT128_GROUP16(val) (__UINT8_TYPE__)(((val) >> 8) & 0xff), (__UINT8_TYPE__)((val) & 0xff)
#define __HYBRID_PRIVATE_INT128_GROUP32(val) (__UINT8_TYPE__)(((val) >> 24) & 0xff), (__UINT8_TYPE__)(((val) >> 16) & 0xff), (__UINT8_TYPE__)(((val) >> 8) & 0xff), (__UINT8_TYPE__)((val) & 0xff)
#define __HYBRID_INT128_INIT8(val)   { { __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), val } }
#define __HYBRID_INT128_INIT16(val)  { { __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_GROUP16(val) } }
#define __HYBRID_INT128_INIT32(val)  { { __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_GROUP32(val) } }
#define __HYBRID_UINT128_INIT8(val)  { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, val } }
#define __HYBRID_UINT128_INIT16(val) { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, __HYBRID_PRIVATE_INT128_GROUP16(val) } }
#define __HYBRID_UINT128_INIT32(val) { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, __HYBRID_PRIVATE_INT128_GROUP32(val) } }
#define __HYBRID_INT128_INIT8N(_16, _15, _14, _13, _12, _11, _10, _9, _8, _7, _6, _5, _4, _3, _2, _1) \
	{ { _16, _15, _14, _13, _12, _11, _10, _9, _8, _7, _6, _5, _4, _3, _2, _1 } }
#define __HYBRID_INT128_INIT16N(_8, _7, _6, _5, _4, _3, _2, _1) \
	{ { __HYBRID_PRIVATE_INT128_GROUP16(_8), __HYBRID_PRIVATE_INT128_GROUP16(_7), __HYBRID_PRIVATE_INT128_GROUP16(_6), __HYBRID_PRIVATE_INT128_GROUP16(_5), __HYBRID_PRIVATE_INT128_GROUP16(_4), __HYBRID_PRIVATE_INT128_GROUP16(_3), __HYBRID_PRIVATE_INT128_GROUP16(_2), __HYBRID_PRIVATE_INT128_GROUP16(_1) } }
#define __HYBRID_INT128_INIT32N(_4, _3, _2, _1) \
	{ { __HYBRID_PRIVATE_INT128_GROUP32(_4), __HYBRID_PRIVATE_INT128_GROUP32(_3), __HYBRID_PRIVATE_INT128_GROUP32(_2), __HYBRID_PRIVATE_INT128_GROUP32(_1) } }
#ifdef __UINT64_TYPE__
#define __HYBRID_PRIVATE_INT128_GROUP64(val) (__UINT8_TYPE__)(((val) >> 56) & 0xff), (__UINT8_TYPE__)(((val) >> 48) & 0xff), (__UINT8_TYPE__)(((val) >> 40) & 0xff), (__UINT8_TYPE__)(((val) >> 32) & 0xff), (__UINT8_TYPE__)(((val) >> 24) & 0xff), (__UINT8_TYPE__)(((val) >> 16) & 0xff), (__UINT8_TYPE__)(((val) >> 8) & 0xff), (__UINT8_TYPE__)((val) & 0xff)
#define __HYBRID_INT128_INIT64(val)     { { __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_SIGN(val), __HYBRID_PRIVATE_INT128_GROUP64(val) } }
#define __HYBRID_UINT128_INIT64(val)    { { 0, 0, 0, 0, 0, 0, 0, 0, __HYBRID_PRIVATE_INT128_GROUP64(val) } }
#define __HYBRID_INT128_INIT64N(_2, _1) { { __HYBRID_PRIVATE_INT128_GROUP64(_2), __HYBRID_PRIVATE_INT128_GROUP64(_1) } }
#endif /* __UINT64_TYPE__ */
#else /* __BYTE_ORDER__ == ... */
#error "Unsupported byteorder"
#endif /* __BYTE_ORDER__ != ... */
#define __HYBRID_UINT128_INIT8N  __HYBRID_INT128_INIT8N
#define __HYBRID_UINT128_INIT16N __HYBRID_INT128_INIT16N
#define __HYBRID_UINT128_INIT32N __HYBRID_INT128_INIT32N
#ifdef __UINT64_TYPE__
#define __HYBRID_UINT128_INIT64N __HYBRID_INT128_INIT64N
#endif /* __UINT64_TYPE__ */

#ifdef __INTELLISENSE__ /* Only for syntax highlighting... */
#define __hybrid_int128_vec8(var)                  (var).__s128_8
#define __hybrid_int128_vec16(var)                 (var).__s128_16
#define __hybrid_int128_vec32(var)                 (var).__s128_32
#define __hybrid_uint128_vec8(var)                 (var).__u128_8
#define __hybrid_uint128_vec16(var)                (var).__u128_16
#define __hybrid_uint128_vec32(var)                (var).__u128_32
#define __hybrid_int128_vec8_significand(var, i)   (var).__s128_8[i]
#define __hybrid_int128_vec16_significand(var, i)  (var).__s128_16[i]
#define __hybrid_int128_vec32_significand(var, i)  (var).__s128_32[i]
#define __hybrid_uint128_vec8_significand(var, i)  (var).__u128_8[i]
#define __hybrid_uint128_vec16_significand(var, i) (var).__u128_16[i]
#define __hybrid_uint128_vec32_significand(var, i) (var).__u128_32[i]
#define __hybrid_uint128_assigned(var)             (*(__hybrid_int128_t const *)&(var).__u128_8)
#define __hybrid_int128_asunsigned(var)            (*(__hybrid_uint128_t const *)&(var).__s128_8)
#ifdef __UINT64_TYPE__
#define __hybrid_int128_vec64(var)                 (var).__s128_64
#define __hybrid_uint128_vec64(var)                (var).__u128_64
#define __hybrid_int128_vec64_significand(var, i)  (var).__s128_64[i]
#define __hybrid_uint128_vec64_significand(var, i) (var).__u128_64[i]
#endif /* __UINT64_TYPE__ */
#define __hybrid_int128_pack8(var, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) \
	(void)(__hybrid_int128_vec8_significand(var, 0)  = (a) + (b) + (c) + (d) + (e) + (f) + (g) + (h) + (i) + (j) + (k) + (l) + (m) + (n) + (o) + (p))
#define __hybrid_int128_pack16(var, a, b, c, d, e, f, g, h) \
	(void)(__hybrid_int128_vec16_significand(var, 0) = (a) + (b) + (c) + (d) + (e) + (f) + (g) + (h))
#define __hybrid_int128_pack32(var, a, b, c, d) \
	(void)(__hybrid_int128_vec32_significand(var, 0) = (a) + (b) + (c) + (d))
#define __hybrid_int128_copy(dst, src) (void)(__hybrid_int128_vec64(dst)[0] = __hybrid_int128_vec64(src)[0])
#define __hybrid_int128_inc(var)       (void)++__hybrid_int128_vec64(var)[0]
#define __hybrid_int128_dec(var)       (void)++__hybrid_int128_vec64(var)[0]
#define __hybrid_int128_inv(var)       (void)++__hybrid_int128_vec64(var)[0]
#else /* __INTELLISENSE__ */
#define __hybrid_int128_vec8(var)    (var).__i128_s8
#define __hybrid_int128_vec16(var)   (var).__i128_s16
#define __hybrid_int128_vec32(var)   (var).__i128_s32
#define __hybrid_uint128_vec8(var)   (var).__i128_u8
#define __hybrid_uint128_vec16(var)  (var).__i128_u16
#define __hybrid_uint128_vec32(var)  (var).__i128_u32
#ifdef __UINT64_TYPE__
#define __hybrid_int128_vec64(var)   (var).__i128_s64
#define __hybrid_uint128_vec64(var)  (var).__i128_u64
#endif /* __UINT64_TYPE__ */

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define __hybrid_int128_vec8_significand(var, i)   (var).__i128_s8[i]
#define __hybrid_int128_vec16_significand(var, i)  (var).__i128_s16[i]
#define __hybrid_int128_vec32_significand(var, i)  (var).__i128_s32[i]
#define __hybrid_uint128_vec8_significand(var, i)  (var).__i128_u8[i]
#define __hybrid_uint128_vec16_significand(var, i) (var).__i128_u16[i]
#define __hybrid_uint128_vec32_significand(var, i) (var).__i128_u32[i]
#ifdef __UINT64_TYPE__
#define __hybrid_int128_vec64_significand(var, i)  (var).__i128_s64[i]
#define __hybrid_uint128_vec64_significand(var, i) (var).__i128_u64[i]
#endif /* __UINT64_TYPE__ */
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __hybrid_int128_vec8_significand(var, i)   (var).__i128_s8[15 - (i)]
#define __hybrid_int128_vec16_significand(var, i)  (var).__i128_s16[7 - (i)]
#define __hybrid_int128_vec32_significand(var, i)  (var).__i128_s32[3 - (i)]
#define __hybrid_uint128_vec8_significand(var, i)  (var).__i128_u8[15 - (i)]
#define __hybrid_uint128_vec16_significand(var, i) (var).__i128_u16[7 - (i)]
#define __hybrid_uint128_vec32_significand(var, i) (var).__i128_u32[3 - (i)]
#ifdef __UINT64_TYPE__
#define __hybrid_int128_vec64_significand(var, i)  (var).__i128_s64[1 - (i)]
#define __hybrid_uint128_vec64_significand(var, i) (var).__i128_u64[1 - (i)]
#endif /* __UINT64_TYPE__ */
#else /* __BYTE_ORDER__ == ... */
#error "Unsupported byteorder"
#endif /* __BYTE_ORDER__ != ... */
#define __hybrid_uint128_assigned(var)  (var)
#define __hybrid_int128_asunsigned(var) (var)

#define __hybrid_int128_pack8  __hybrid_uint128_pack8
#define __hybrid_int128_pack16 __hybrid_uint128_pack16
#define __hybrid_int128_pack32 __hybrid_uint128_pack32
#define __hybrid_int128_copy   __hybrid_uint128_copy
#define __hybrid_int128_inc    __hybrid_uint128_inc
#define __hybrid_int128_dec    __hybrid_uint128_dec
#define __hybrid_int128_inv    __hybrid_uint128_inv
#endif /* !__INTELLISENSE__ */


#ifdef __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
#define __hybrid_uint128_copy(dst, src)                                     \
	(void)(__hybrid_uint128_vec64(dst)[0] = __hybrid_uint128_vec64(src)[0], \
	       __hybrid_uint128_vec64(dst)[1] = __hybrid_uint128_vec64(src)[1])
#else /* __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
#define __hybrid_uint128_copy(dst, src)                                     \
	(void)(__hybrid_uint128_vec32(dst)[0] = __hybrid_uint128_vec32(src)[0], \
	       __hybrid_uint128_vec32(dst)[1] = __hybrid_uint128_vec32(src)[1], \
	       __hybrid_uint128_vec32(dst)[2] = __hybrid_uint128_vec32(src)[2], \
	       __hybrid_uint128_vec32(dst)[3] = __hybrid_uint128_vec32(src)[3])
#endif /* !__HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
/* Construct a 128-bit integer, given its individual words in least->most significand order. */
#define __hybrid_uint128_pack8(var, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) \
	(void)(__hybrid_uint128_vec8_significand(var, 0)  = (a),                        \
	       __hybrid_uint128_vec8_significand(var, 1)  = (b),                        \
	       __hybrid_uint128_vec8_significand(var, 2)  = (c),                        \
	       __hybrid_uint128_vec8_significand(var, 3)  = (d),                        \
	       __hybrid_uint128_vec8_significand(var, 4)  = (e),                        \
	       __hybrid_uint128_vec8_significand(var, 5)  = (f),                        \
	       __hybrid_uint128_vec8_significand(var, 6)  = (g),                        \
	       __hybrid_uint128_vec8_significand(var, 7)  = (h),                        \
	       __hybrid_uint128_vec8_significand(var, 8)  = (i),                        \
	       __hybrid_uint128_vec8_significand(var, 9)  = (j),                        \
	       __hybrid_uint128_vec8_significand(var, 10) = (k),                        \
	       __hybrid_uint128_vec8_significand(var, 11) = (l),                        \
	       __hybrid_uint128_vec8_significand(var, 12) = (m),                        \
	       __hybrid_uint128_vec8_significand(var, 13) = (n),                        \
	       __hybrid_uint128_vec8_significand(var, 14) = (o),                        \
	       __hybrid_uint128_vec8_significand(var, 15) = (p))
#define __hybrid_uint128_pack16(var, a, b, c, d, e, f, g, h) \
	(void)(__hybrid_uint128_vec16_significand(var, 0) = (a), \
	       __hybrid_uint128_vec16_significand(var, 1) = (b), \
	       __hybrid_uint128_vec16_significand(var, 2) = (c), \
	       __hybrid_uint128_vec16_significand(var, 3) = (d), \
	       __hybrid_uint128_vec16_significand(var, 4) = (e), \
	       __hybrid_uint128_vec16_significand(var, 5) = (f), \
	       __hybrid_uint128_vec16_significand(var, 6) = (g), \
	       __hybrid_uint128_vec16_significand(var, 7) = (h))
#define __hybrid_uint128_pack32(var, a, b, c, d)             \
	(void)(__hybrid_uint128_vec32_significand(var, 0) = (a), \
	       __hybrid_uint128_vec32_significand(var, 1) = (b), \
	       __hybrid_uint128_vec32_significand(var, 2) = (c), \
	       __hybrid_uint128_vec32_significand(var, 3) = (d))

#ifdef __UINT64_TYPE__
#define __hybrid_uint128_pack64(var, lo, hi)                  \
	(void)(__hybrid_uint128_vec64_significand(var, 0) = (lo), \
	       __hybrid_uint128_vec64_significand(var, 1) = (hi))
#define __hybrid_int128_pack64(var, lo, hi) \
	__hybrid_uint128_pack64(var, lo, hi)
#define __hybrid_int128_get64(var) __hybrid_int128_vec64_significand(var, 0)
#define __hybrid_int128_set64(var, v)                                       \
	(void)(__hybrid_int128_vec64_significand(var, 0) = (__INT64_TYPE__)(v), \
	       __hybrid_int128_vec64_significand(var, 1) = __hybrid_int128_vec64_significand(var, 0) < 0 ? -1 : 0)
#define __hybrid_uint128_get64(var) \
	__hybrid_uint128_vec64_significand(var, 0)
#define __hybrid_uint128_set64(var, v)                                        \
	(void)(__hybrid_uint128_vec64_significand(var, 0) = (__UINT64_TYPE__)(v), \
	       __hybrid_uint128_vec64_significand(var, 1) = 0)
#endif /* __UINT64_TYPE__ */

#define __hybrid_int128_get32(var)  __hybrid_int128_vec32_significand(var, 0)
#define __hybrid_uint128_get32(var) __hybrid_uint128_vec32_significand(var, 0)
#ifdef __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
#define __hybrid_int128_set32(var, v)  __hybrid_int128_set64(var, v)
#define __hybrid_uint128_set32(var, v) __hybrid_uint128_set64(var, v)
#else /* __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
#define __hybrid_int128_set32(var, v)                                                                          \
	(void)(__hybrid_int128_vec32_significand(var, 0) = (__INT32_TYPE__)(v),                                    \
	       __hybrid_int128_vec32_significand(var, 1) = __hybrid_int128_vec32_significand(var, 0) < 0 ? -1 : 0, \
	       __hybrid_int128_vec32_significand(var, 2) = __hybrid_int128_vec32_significand(var, 1),              \
	       __hybrid_int128_vec32_significand(var, 3) = __hybrid_int128_vec32_significand(var, 1))
#define __hybrid_uint128_set32(var, v)                                        \
	(void)(__hybrid_uint128_vec32_significand(var, 0) = (__UINT32_TYPE__)(v), \
	       __hybrid_uint128_vec32_significand(var, 1) = 0,                    \
	       __hybrid_uint128_vec32_significand(var, 2) = 0,                    \
	       __hybrid_uint128_vec32_significand(var, 3) = 0)
#endif /* !__HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */

#define __hybrid_int128_get16(var)  __hybrid_int128_vec16_significand(var, 0)
#define __hybrid_uint128_get16(var) __hybrid_uint128_vec16_significand(var, 0)
#ifdef __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
#define __hybrid_int128_set16(var, v)  __hybrid_int128_set64(var, v)
#define __hybrid_uint128_set16(var, v) __hybrid_uint128_set64(var, v)
#elif __SIZEOF_BUSINT__ >= 4
#define __hybrid_int128_set16(var, v)  __hybrid_int128_set32(var, v)
#define __hybrid_uint128_set16(var, v) __hybrid_uint128_set32(var, v)
#else /* __SIZEOF_BUSINT__ >= ... */
#define __hybrid_int128_set16(var, v)                                                                          \
	(void)(__hybrid_int128_vec16_significand(var, 0) = (__INT16_TYPE__)(v),                                    \
	       __hybrid_int128_vec16_significand(var, 1) = __hybrid_int128_vec16_significand(var, 0) < 0 ? -1 : 0, \
	       __hybrid_int128_vec16_significand(var, 2) = __hybrid_int128_vec16_significand(var, 1),              \
	       __hybrid_int128_vec16_significand(var, 3) = __hybrid_int128_vec16_significand(var, 1),              \
	       __hybrid_int128_vec16_significand(var, 4) = __hybrid_int128_vec16_significand(var, 1),              \
	       __hybrid_int128_vec16_significand(var, 5) = __hybrid_int128_vec16_significand(var, 1),              \
	       __hybrid_int128_vec16_significand(var, 6) = __hybrid_int128_vec16_significand(var, 1),              \
	       __hybrid_int128_vec16_significand(var, 7) = __hybrid_int128_vec16_significand(var, 1))
#define __hybrid_uint128_set16(var, v)                                        \
	(void)(__hybrid_uint128_vec16_significand(var, 0) = (__UINT16_TYPE__)(v), \
	       __hybrid_uint128_vec16_significand(var, 1) = 0,                    \
	       __hybrid_uint128_vec16_significand(var, 2) = 0,                    \
	       __hybrid_uint128_vec16_significand(var, 3) = 0,                    \
	       __hybrid_uint128_vec16_significand(var, 4) = 0,                    \
	       __hybrid_uint128_vec16_significand(var, 5) = 0,                    \
	       __hybrid_uint128_vec16_significand(var, 6) = 0,                    \
	       __hybrid_uint128_vec16_significand(var, 7) = 0)
#endif /* __SIZEOF_BUSINT__ < ... */

#define __hybrid_int128_get8(var)  __hybrid_int128_vec8_significand(var, 0)
#define __hybrid_uint128_get8(var) __hybrid_uint128_vec8_significand(var, 0)
#ifdef __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
#define __hybrid_int128_set8(var, v)  __hybrid_int128_set64(var, v)
#define __hybrid_uint128_set8(var, v) __hybrid_uint128_set64(var, v)
#define __hybrid_int128_set(var, v)   __hybrid_int128_set64(var, v)
#define __hybrid_uint128_set(var, v)  __hybrid_uint128_set64(var, v)
#elif __SIZEOF_BUSINT__ >= 4
#define __hybrid_int128_set8(var, v)  __hybrid_int128_set32(var, v)
#define __hybrid_uint128_set8(var, v) __hybrid_uint128_set32(var, v)
#ifdef __UINT64_TYPE__
#define __hybrid_int128_set(var, v)   __builtin_choose_expr(sizeof(v) == 8, __hybrid_int128_set64(var, v), __hybrid_int128_set32(var, v))
#define __hybrid_uint128_set(var, v)  __builtin_choose_expr(sizeof(v) == 8, __hybrid_uint128_set64(var, v), __hybrid_uint128_set32(var, v))
#else /* __UINT64_TYPE__ */
#define __hybrid_int128_set(var, v)   __hybrid_int128_set32(var, v)
#define __hybrid_uint128_set(var, v)  __hybrid_uint128_set32(var, v)
#endif /* !__UINT64_TYPE__ */
#else /* __SIZEOF_BUSINT__ >= ... */
#define __hybrid_int128_set8(var, v)  __hybrid_int128_set16(var, v)
#define __hybrid_uint128_set8(var, v) __hybrid_uint128_set16(var, v)
#ifdef __UINT64_TYPE__
#define __hybrid_int128_set(var, v)   __builtin_choose_expr(sizeof(v) == 8, __hybrid_int128_set64(var, v), __builtin_choose_expr(sizeof(v) == 4, __hybrid_int128_set32(var, v), __hybrid_int128_set16(var, v)))
#define __hybrid_uint128_set(var, v)  __builtin_choose_expr(sizeof(v) == 8, __hybrid_uint128_set64(var, v), __builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_set32(var, v), __hybrid_uint128_set16(var, v)))
#else /* __UINT64_TYPE__ */
#define __hybrid_int128_set(var, v)   __builtin_choose_expr(sizeof(v) == 4, __hybrid_int128_set32(var, v), __hybrid_int128_set16(var, v))
#define __hybrid_uint128_set(var, v)  __builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_set32(var, v), __hybrid_uint128_set16(var, v))
#endif /* !__UINT64_TYPE__ */
#endif /* __SIZEOF_BUSINT__ < ... */

#ifdef __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
#define __hybrid_uint128_inc(var)                               \
	(void)(++__hybrid_uint128_vec64_significand(var, 0) != 0 || \
	       (++__hybrid_uint128_vec64_significand(var, 1), 0))
#define __hybrid_uint128_dec(var)                                                            \
	(void)(--__hybrid_uint128_vec64_significand(var, 0) != __UINT64_C(0xffffffffffffffff) || \
	       (--__hybrid_uint128_vec64_significand(var, 1), 0))
#define __hybrid_uint128_inv(var)                                            \
	(void)(__hybrid_uint128_vec64(var)[0] = ~__hybrid_uint128_vec64(var)[0], \
	       __hybrid_uint128_vec64(var)[1] = ~__hybrid_uint128_vec64(var)[1])
#else /* __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
#define __hybrid_uint128_inc(var)                               \
	(void)(++__hybrid_uint128_vec32_significand(var, 0) != 0 || \
	       ++__hybrid_uint128_vec32_significand(var, 1) != 0 || \
	       ++__hybrid_uint128_vec32_significand(var, 2) != 0 || \
	       (++__hybrid_uint128_vec32_significand(var, 3), 0))
#define __hybrid_uint128_dec(var)                                                    \
	(void)(--__hybrid_uint128_vec32_significand(var, 0) != __UINT32_C(0xffffffff) || \
	       --__hybrid_uint128_vec32_significand(var, 1) != __UINT32_C(0xffffffff) || \
	       --__hybrid_uint128_vec32_significand(var, 2) != __UINT32_C(0xffffffff) || \
	       (--__hybrid_uint128_vec32_significand(var, 3), 0))
#define __hybrid_uint128_inv(var)                                            \
	(void)(__hybrid_uint128_vec32(var)[0] = ~__hybrid_uint128_vec32(var)[0], \
	       __hybrid_uint128_vec32(var)[1] = ~__hybrid_uint128_vec32(var)[1], \
	       __hybrid_uint128_vec32(var)[2] = ~__hybrid_uint128_vec32(var)[2], \
	       __hybrid_uint128_vec32(var)[3] = ~__hybrid_uint128_vec32(var)[3])
#endif /* !__HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
#define __hybrid_int128_neg(var)   (__hybrid_int128_dec(var), __hybrid_int128_inv(var))
#define __hybrid_int128_isneg(var) (__hybrid_int128_vec8_significand(var, 15) < 0)

#ifdef __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
#define __hybrid_uint128_and128(var, v)                                    \
	(void)(__hybrid_uint128_vec64(var)[0] &= __hybrid_uint128_vec64(v)[0], \
	       __hybrid_uint128_vec64(var)[1] &= __hybrid_uint128_vec64(v)[1])
#define __hybrid_uint128_or128(var, v)                                     \
	(void)(__hybrid_uint128_vec64(var)[0] |= __hybrid_uint128_vec64(v)[0], \
	       __hybrid_uint128_vec64(var)[1] |= __hybrid_uint128_vec64(v)[1])
#define __hybrid_uint128_xor128(var, v)                                    \
	(void)(__hybrid_uint128_vec64(var)[0] ^= __hybrid_uint128_vec64(v)[0], \
	       __hybrid_uint128_vec64(var)[1] ^= __hybrid_uint128_vec64(v)[1])
#else /* __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
#define __hybrid_uint128_and128(var, v)                                    \
	(void)(__hybrid_uint128_vec32(var)[0] &= __hybrid_uint128_vec32(v)[0], \
	       __hybrid_uint128_vec32(var)[1] &= __hybrid_uint128_vec32(v)[1], \
	       __hybrid_uint128_vec32(var)[2] &= __hybrid_uint128_vec32(v)[2], \
	       __hybrid_uint128_vec32(var)[3] &= __hybrid_uint128_vec32(v)[3])
#define __hybrid_uint128_or128(var, v)                                     \
	(void)(__hybrid_uint128_vec32(var)[0] |= __hybrid_uint128_vec32(v)[0], \
	       __hybrid_uint128_vec32(var)[1] |= __hybrid_uint128_vec32(v)[1], \
	       __hybrid_uint128_vec32(var)[2] |= __hybrid_uint128_vec32(v)[2], \
	       __hybrid_uint128_vec32(var)[3] |= __hybrid_uint128_vec32(v)[3])
#define __hybrid_uint128_xor128(var, v)                                    \
	(void)(__hybrid_uint128_vec32(var)[0] ^= __hybrid_uint128_vec32(v)[0], \
	       __hybrid_uint128_vec32(var)[1] ^= __hybrid_uint128_vec32(v)[1], \
	       __hybrid_uint128_vec32(var)[2] ^= __hybrid_uint128_vec32(v)[2], \
	       __hybrid_uint128_vec32(var)[3] ^= __hybrid_uint128_vec32(v)[3])
#endif /* !__HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
#ifdef __UINT64_TYPE__
#define __hybrid_uint128_and64(var, v) \
	__hybrid_uint128_set64(var, __hybrid_uint128_get64(var) & (__UINT64_TYPE__)(v))
#define __hybrid_int128_and64(var, v)  __hybrid_int128_set64(var, __hybrid_int128_get64(var) & (__INT64_TYPE__)(v))
#define __hybrid_uint128_or64(var, v) (void)(__hybrid_uint128_vec64_significand(var, 0) |= (v))
#define __hybrid_int128_or64(var, v)                                   \
	(__hybrid_int128_vec64_significand(var, 0) |= (__INT64_TYPE__)(v), \
	 (__INT64_TYPE__)(v) < 0 ? (void)(__hybrid_int128_vec64_significand(var, 1) = -1) : (void)0)
#define __hybrid_uint128_xor64(var, v) (void)(__hybrid_uint128_vec64_significand(var, 0) ^= (v))
#define __hybrid_int128_xor64(var, v)                                   \
	(__hybrid_int128_vec64_significand(var, 0) ^= (__INT64_TYPE__)(v), \
	 (__INT64_TYPE__)(v) < 0 ? (void)(__hybrid_int128_vec64_significand(var, 1) ^= -1) : (void)0)
#endif /* __UINT64_TYPE__ */

#define __hybrid_uint128_and8(var, v)  __hybrid_uint128_set8(var, __hybrid_uint128_get8(var) & (__UINT8_TYPE__)(v))
#define __hybrid_uint128_and16(var, v) __hybrid_uint128_set16(var, __hybrid_uint128_get16(var) & (__UINT16_TYPE__)(v))
#define __hybrid_uint128_and32(var, v) __hybrid_uint128_set32(var, __hybrid_uint128_get32(var) & (__UINT32_TYPE__)(v))
#define __hybrid_int128_and8(var, v)   __hybrid_int128_set8(var, __hybrid_int128_get8(var) & (__INT8_TYPE__)(v))
#define __hybrid_int128_and16(var, v)  __hybrid_int128_set16(var, __hybrid_int128_get16(var) & (__INT16_TYPE__)(v))
#define __hybrid_int128_and32(var, v)  __hybrid_int128_set32(var, __hybrid_int128_get32(var) & (__INT32_TYPE__)(v))
#define __hybrid_uint128_or8(var, v)   (void)(__hybrid_uint128_vec8_significand(var, 0) |= (v))
#define __hybrid_uint128_or16(var, v)  (void)(__hybrid_uint128_vec16_significand(var, 0) |= (v))
#define __hybrid_uint128_or32(var, v)  (void)(__hybrid_uint128_vec32_significand(var, 0) |= (v))
#define __hybrid_uint128_xor8(var, v)  (void)(__hybrid_uint128_vec8_significand(var, 0) ^= (v))
#define __hybrid_uint128_xor16(var, v) (void)(__hybrid_uint128_vec16_significand(var, 0) ^= (v))
#define __hybrid_uint128_xor32(var, v) (void)(__hybrid_uint128_vec32_significand(var, 0) ^= (v))

#ifdef __INTELLISENSE__ /* Only for syntax highlighting... */
#define __hybrid_int128_and128(var, v) (void)(__hybrid_int128_vec8_significand(var, 0) = __hybrid_int128_vec8_significand(v, 0))
#define __hybrid_int128_or128          __hybrid_int128_and128
#define __hybrid_int128_xor128         __hybrid_int128_and128
#define __hybrid_int128_or8(var, v)    (void)(__hybrid_int128_vec8_significand(var, 0) = (v))
#define __hybrid_int128_or16           __hybrid_int128_or8
#define __hybrid_int128_or32           __hybrid_int128_or8
#define __hybrid_int128_xor8           __hybrid_int128_or8
#define __hybrid_int128_xor16          __hybrid_int128_or8
#define __hybrid_int128_xor32          __hybrid_int128_or8
#else /* __INTELLISENSE__ */
#define __hybrid_int128_and128 __hybrid_uint128_and128
#define __hybrid_int128_or128  __hybrid_uint128_or128
#define __hybrid_int128_xor128 __hybrid_uint128_xor128
#ifdef __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
#define __hybrid_int128_or8(var, v)    (__hybrid_uint128_vec8_significand(var, 0) |= (v), (v) < 0  ? (void)(__hybrid_int128_vec64_significand(var, 1) = -1, __hybrid_int128_vec32_significand(var, 1) = -1, __hybrid_int128_vec16_significand(var, 1) = -1, __hybrid_int128_vec8_significand(var, 1) = -1) : (void)0)
#define __hybrid_int128_or16(var, v)   (__hybrid_uint128_vec16_significand(var, 0) |= (v), (v) < 0 ? (void)(__hybrid_int128_vec64_significand(var, 1) = -1, __hybrid_int128_vec32_significand(var, 1) = -1, __hybrid_int128_vec16_significand(var, 1) = -1) : (void)0)
#define __hybrid_int128_or32(var, v)   (__hybrid_uint128_vec32_significand(var, 0) |= (v), (v) < 0 ? (void)(__hybrid_int128_vec64_significand(var, 1) = -1, __hybrid_int128_vec32_significand(var, 1) = -1) : (void)0)
#define __hybrid_int128_xor8(var, v)   (__hybrid_uint128_vec8_significand(var, 0) ^= (v), (v) < 0  ? (void)(__hybrid_int128_vec64_significand(var, 1) ^= -1, __hybrid_int128_vec32_significand(var, 1) ^= -1, __hybrid_int128_vec16_significand(var, 1) ^= -1, __hybrid_int128_vec8_significand(var, 1) ^= -1) : (void)0)
#define __hybrid_int128_xor16(var, v)  (__hybrid_uint128_vec16_significand(var, 0) ^= (v), (v) < 0 ? (void)(__hybrid_int128_vec64_significand(var, 1) ^= -1, __hybrid_int128_vec32_significand(var, 1) ^= -1, __hybrid_int128_vec16_significand(var, 1) ^= -1) : (void)0)
#define __hybrid_int128_xor32(var, v)  (__hybrid_uint128_vec32_significand(var, 0) ^= (v), (v) < 0 ? (void)(__hybrid_int128_vec64_significand(var, 1) ^= -1, __hybrid_int128_vec32_significand(var, 1) ^= -1) : (void)0)
#else /* __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
#define __hybrid_int128_or8(var, v)    (__hybrid_uint128_vec8_significand(var, 0) |= (v), (v) < 0  ? (void)(__hybrid_int128_vec32_significand(var, 3) = -1, __hybrid_int128_vec32_significand(var, 2) = -1, __hybrid_int128_vec32_significand(var, 1) = -1, __hybrid_int128_vec16_significand(var, 1) = -1, __hybrid_int128_vec8_significand(var, 1) = -1) : (void)0)
#define __hybrid_int128_or16(var, v)   (__hybrid_uint128_vec16_significand(var, 0) |= (v), (v) < 0 ? (void)(__hybrid_int128_vec32_significand(var, 3) = -1, __hybrid_int128_vec32_significand(var, 2) = -1, __hybrid_int128_vec32_significand(var, 1) = -1, __hybrid_int128_vec16_significand(var, 1) = -1) : (void)0)
#define __hybrid_int128_or32(var, v)   (__hybrid_uint128_vec32_significand(var, 0) |= (v), (v) < 0 ? (void)(__hybrid_int128_vec32_significand(var, 3) = -1, __hybrid_int128_vec32_significand(var, 2) = -1, __hybrid_int128_vec32_significand(var, 1) = -1) : (void)0)
#define __hybrid_int128_xor8(var, v)   (__hybrid_uint128_vec8_significand(var, 0) ^= (v), (v) < 0  ? (void)(__hybrid_int128_vec32_significand(var, 3) ^= -1, __hybrid_int128_vec32_significand(var, 2) ^= -1, __hybrid_int128_vec32_significand(var, 1) ^= -1, __hybrid_int128_vec16_significand(var, 1) ^= -1, __hybrid_int128_vec8_significand(var, 1) ^= -1) : (void)0)
#define __hybrid_int128_xor16(var, v)  (__hybrid_uint128_vec16_significand(var, 0) ^= (v), (v) < 0 ? (void)(__hybrid_int128_vec32_significand(var, 3) ^= -1, __hybrid_int128_vec32_significand(var, 2) ^= -1, __hybrid_int128_vec32_significand(var, 1) ^= -1, __hybrid_int128_vec16_significand(var, 1) ^= -1) : (void)0)
#define __hybrid_int128_xor32(var, v)  (__hybrid_uint128_vec32_significand(var, 0) ^= (v), (v) < 0 ? (void)(__hybrid_int128_vec32_significand(var, 3) ^= -1, __hybrid_int128_vec32_significand(var, 2) ^= -1, __hybrid_int128_vec32_significand(var, 1) ^= -1) : (void)0)
#endif /* !__HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
#endif /* !__INTELLISENSE__ */



#ifdef __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
#define __hybrid_uint128_add8(var, v)                                                               \
	(void)(!__hybrid_overflow_uadd8(__hybrid_uint128_vec8_significand(var, 0), (__UINT8_TYPE__)(v), \
	                                &__hybrid_uint128_vec8_significand(var, 0)) ||                  \
	       ++__hybrid_uint128_vec8_significand(var, 1) != 0 ||                                      \
	       ++__hybrid_uint128_vec16_significand(var, 1) != 0 ||                                     \
	       ++__hybrid_uint128_vec32_significand(var, 1) != 0 ||                                     \
	       (++__hybrid_uint128_vec64_significand(var, 1), 0))
#define __hybrid_uint128_add16(var, v)                                                                 \
	(void)(!__hybrid_overflow_uadd16(__hybrid_uint128_vec16_significand(var, 0), (__UINT16_TYPE__)(v), \
	                                 &__hybrid_uint128_vec16_significand(var, 0)) ||                   \
	       ++__hybrid_uint128_vec16_significand(var, 1) != 0 ||                                        \
	       ++__hybrid_uint128_vec32_significand(var, 1) != 0 ||                                        \
	       (++__hybrid_uint128_vec64_significand(var, 1), 0))
#define __hybrid_uint128_add32(var, v)                                                                 \
	(void)(!__hybrid_overflow_uadd32(__hybrid_uint128_vec32_significand(var, 0), (__UINT32_TYPE__)(v), \
	                                 &__hybrid_uint128_vec32_significand(var, 0)) ||                   \
	       ++__hybrid_uint128_vec32_significand(var, 1) != 0 ||                                        \
	       (++__hybrid_uint128_vec64_significand(var, 1), 0))
#define __hybrid_uint128_add64(var, v)                                                                 \
	(void)(!__hybrid_overflow_uadd64(__hybrid_uint128_vec64_significand(var, 0), (__UINT64_TYPE__)(v), \
	                                 &__hybrid_uint128_vec64_significand(var, 0)) ||                   \
	       (++__hybrid_uint128_vec64_significand(var, 1), 0))
#define __hybrid_uint128_add128(var, v)                                              \
	(void)(!__hybrid_overflow_uadd64(__hybrid_uint128_vec64_significand(var, 0),     \
	                                 __hybrid_uint128_vec64_significand(v, 0),       \
	                                 &__hybrid_uint128_vec64_significand(var, 0)) || \
	       ++__hybrid_uint128_vec64_significand(var, 1),                             \
	       __hybrid_uint128_vec64_significand(var, 1) += __hybrid_uint128_vec64_significand(v, 1))
#define __hybrid_uint128_sub8(var, v)                                                               \
	(void)(!__hybrid_overflow_usub8(__hybrid_uint128_vec8_significand(var, 0), (__UINT8_TYPE__)(v), \
	                                &__hybrid_uint128_vec8_significand(var, 0)) ||                  \
	       --__hybrid_uint128_vec8_significand(var, 1) != __UINT8_C(0xff) ||                        \
	       --__hybrid_uint128_vec16_significand(var, 1) != __UINT16_C(0xffff) ||                    \
	       --__hybrid_uint128_vec32_significand(var, 1) != __UINT32_C(0xffffffff) ||                \
	       (--__hybrid_uint128_vec64_significand(var, 1), 0))
#define __hybrid_uint128_sub16(var, v)                                                                 \
	(void)(!__hybrid_overflow_usub16(__hybrid_uint128_vec16_significand(var, 0), (__UINT16_TYPE__)(v), \
	                                 &__hybrid_uint128_vec16_significand(var, 0)) ||                   \
	       --__hybrid_uint128_vec16_significand(var, 1) != __UINT16_C(0xffff) ||                       \
	       --__hybrid_uint128_vec32_significand(var, 1) != __UINT32_C(0xffffffff) ||                   \
	       (--__hybrid_uint128_vec64_significand(var, 1), 0))
#define __hybrid_uint128_sub32(var, v)                                                                 \
	(void)(!__hybrid_overflow_usub32(__hybrid_uint128_vec32_significand(var, 0), (__UINT32_TYPE__)(v), \
	                                 &__hybrid_uint128_vec32_significand(var, 0)) ||                   \
	       --__hybrid_uint128_vec32_significand(var, 1) != __UINT32_C(0xffffffff) ||                   \
	       (--__hybrid_uint128_vec64_significand(var, 1), 0))
#define __hybrid_uint128_sub64(var, v)                                                                 \
	(void)(!__hybrid_overflow_usub64(__hybrid_uint128_vec64_significand(var, 0), (__UINT64_TYPE__)(v), \
	                                 &__hybrid_uint128_vec64_significand(var, 0)) ||                   \
	       (--__hybrid_uint128_vec64_significand(var, 1), 0))
#define __hybrid_uint128_sub128(var, v)                                              \
	(void)(!__hybrid_overflow_usub64(__hybrid_uint128_vec64_significand(var, 0),     \
	                                 __hybrid_uint128_vec64_significand(v, 0),       \
	                                 &__hybrid_uint128_vec64_significand(var, 0)) || \
	       (--__hybrid_uint128_vec64_significand(var, 1), 0),                        \
	       __hybrid_uint128_vec64_significand(var, 1) -= __hybrid_uint128_vec64_significand(v, 1))
#else /* __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
#define __hybrid_uint128_add8(var, v)                                                               \
	(void)(!__hybrid_overflow_uadd8(__hybrid_uint128_vec8_significand(var, 0), (__UINT8_TYPE__)(v), \
	                                &__hybrid_uint128_vec8_significand(var, 0)) ||                  \
	       ++__hybrid_uint128_vec8_significand(var, 1) != 0 ||                                      \
	       ++__hybrid_uint128_vec16_significand(var, 1) != 0 ||                                     \
	       ++__hybrid_uint128_vec32_significand(var, 1) != 0 ||                                     \
	       ++__hybrid_uint128_vec32_significand(var, 2) != 0 ||                                     \
	       (++__hybrid_uint128_vec32_significand(var, 3), 0))
#define __hybrid_uint128_add16(var, v)                                                                 \
	(void)(!__hybrid_overflow_uadd16(__hybrid_uint128_vec16_significand(var, 0), (__UINT16_TYPE__)(v), \
	                                 &__hybrid_uint128_vec16_significand(var, 0)) ||                   \
	       ++__hybrid_uint128_vec16_significand(var, 1) != 0 ||                                        \
	       ++__hybrid_uint128_vec32_significand(var, 1) != 0 ||                                        \
	       ++__hybrid_uint128_vec32_significand(var, 2) != 0 ||                                        \
	       (++__hybrid_uint128_vec32_significand(var, 3), 0))
#define __hybrid_uint128_add32(var, v)                                                                 \
	(void)(!__hybrid_overflow_uadd32(__hybrid_uint128_vec32_significand(var, 0), (__UINT32_TYPE__)(v), \
	                                 &__hybrid_uint128_vec32_significand(var, 0)) ||                   \
	       ++__hybrid_uint128_vec32_significand(var, 1) != 0 ||                                        \
	       ++__hybrid_uint128_vec32_significand(var, 2) != 0 ||                                        \
	       (++__hybrid_uint128_vec32_significand(var, 3), 0))
#ifdef __UINT64_TYPE__
#define __hybrid_uint128_add64(var, v)                                                                 \
	(void)(!__hybrid_overflow_uadd64(__hybrid_uint128_vec64_significand(var, 0), (__UINT64_TYPE__)(v), \
	                                 &__hybrid_uint128_vec64_significand(var, 0)) ||                   \
	       ++__hybrid_uint128_vec32_significand(var, 2) != 0 ||                                        \
	       (++__hybrid_uint128_vec32_significand(var, 3), 0))
#endif /* __UINT64_TYPE__ */
#define __hybrid_uint128_add128(var, v)                                               \
	((void)(!__hybrid_overflow_uadd32(__hybrid_uint128_vec32_significand(var, 0),     \
	                                  __hybrid_uint128_vec32_significand(v, 0),       \
	                                  &__hybrid_uint128_vec32_significand(var, 0)) || \
	        ++__hybrid_uint128_vec32_significand(var, 1) != 0 ||                      \
	        ++__hybrid_uint128_vec32_significand(var, 2) != 0 ||                      \
	        (++__hybrid_uint128_vec32_significand(var, 3), 0)),                       \
	 (void)(!__hybrid_overflow_uadd32(__hybrid_uint128_vec32_significand(var, 1),     \
	                                  __hybrid_uint128_vec32_significand(v, 1),       \
	                                  &__hybrid_uint128_vec32_significand(var, 1)) || \
	        ++__hybrid_uint128_vec32_significand(var, 2) != 0 ||                      \
	        (++__hybrid_uint128_vec32_significand(var, 3), 0)),                       \
	 (void)(!__hybrid_overflow_uadd32(__hybrid_uint128_vec32_significand(var, 2),     \
	                                  __hybrid_uint128_vec32_significand(v, 2),       \
	                                  &__hybrid_uint128_vec32_significand(var, 2)) || \
	        (++__hybrid_uint128_vec32_significand(var, 3), 0)),                       \
	 (void)(__hybrid_uint128_vec32_significand(var, 3) += __hybrid_uint128_vec32_significand(v, 3)))
#define __hybrid_uint128_sub8(var, v)                                                               \
	(void)(!__hybrid_overflow_usub8(__hybrid_uint128_vec8_significand(var, 0), (__UINT8_TYPE__)(v), \
	                                &__hybrid_uint128_vec8_significand(var, 0)) ||                  \
	       --__hybrid_uint128_vec8_significand(var, 1) != __UINT8_C(0xff) ||                        \
	       --__hybrid_uint128_vec16_significand(var, 1) != __UINT16_C(0xffff) ||                    \
	       --__hybrid_uint128_vec32_significand(var, 1) != __UINT32_C(0xffffffff) ||                \
	       --__hybrid_uint128_vec32_significand(var, 2) != __UINT32_C(0xffffffff) ||                \
	       (--__hybrid_uint128_vec32_significand(var, 3), 0))
#define __hybrid_uint128_sub16(var, v)                                                                 \
	(void)(!__hybrid_overflow_usub16(__hybrid_uint128_vec16_significand(var, 0), (__UINT16_TYPE__)(v), \
	                                 &__hybrid_uint128_vec16_significand(var, 0)) ||                   \
	       --__hybrid_uint128_vec16_significand(var, 1) != __UINT16_C(0xffff) ||                       \
	       --__hybrid_uint128_vec32_significand(var, 1) != __UINT32_C(0xffffffff) ||                   \
	       --__hybrid_uint128_vec32_significand(var, 2) != __UINT32_C(0xffffffff) ||                   \
	       (--__hybrid_uint128_vec32_significand(var, 3), 0))
#define __hybrid_uint128_sub32(var, v)                                                                 \
	(void)(!__hybrid_overflow_usub32(__hybrid_uint128_vec32_significand(var, 0), (__UINT32_TYPE__)(v), \
	                                 &__hybrid_uint128_vec32_significand(var, 0)) ||                   \
	       --__hybrid_uint128_vec32_significand(var, 1) != __UINT32_C(0xffffffff) ||                   \
	       --__hybrid_uint128_vec32_significand(var, 2) != __UINT32_C(0xffffffff) ||                   \
	       (--__hybrid_uint128_vec32_significand(var, 3), 0))
#ifdef __UINT64_TYPE__
#define __hybrid_uint128_sub64(var, v)                                                                 \
	(void)(!__hybrid_overflow_usub64(__hybrid_uint128_vec64_significand(var, 0), (__UINT64_TYPE__)(v), \
	                                 &__hybrid_uint128_vec64_significand(var, 0)) ||                   \
	       --__hybrid_uint128_vec32_significand(var, 2) != __UINT32_C(0xffffffff) ||                   \
	       (--__hybrid_uint128_vec32_significand(var, 3), 0))
#endif /* __UINT64_TYPE__ */
#define __hybrid_uint128_sub128(var, v)                                               \
	((void)(!__hybrid_overflow_usub32(__hybrid_uint128_vec32_significand(var, 0),     \
	                                  __hybrid_uint128_vec32_significand(v, 0),       \
	                                  &__hybrid_uint128_vec32_significand(var, 0)) || \
	        --__hybrid_uint128_vec32_significand(var, 1) != __UINT32_C(0xffffffff) || \
	        --__hybrid_uint128_vec32_significand(var, 2) != __UINT32_C(0xffffffff) || \
	        (--__hybrid_uint128_vec32_significand(var, 3), 0)),                       \
	 (void)(!__hybrid_overflow_usub32(__hybrid_uint128_vec32_significand(var, 1),     \
	                                  __hybrid_uint128_vec32_significand(v, 1),       \
	                                  &__hybrid_uint128_vec32_significand(var, 1)) || \
	        --__hybrid_uint128_vec32_significand(var, 2) != __UINT32_C(0xffffffff) || \
	        (--__hybrid_uint128_vec32_significand(var, 3), 0)),                       \
	 (void)(!__hybrid_overflow_usub32(__hybrid_uint128_vec32_significand(var, 2),     \
	                                  __hybrid_uint128_vec32_significand(v, 2),       \
	                                  &__hybrid_uint128_vec32_significand(var, 2)) || \
	        (--__hybrid_uint128_vec32_significand(var, 3), 0)),                       \
	 (void)(__hybrid_uint128_vec32_significand(var, 3) -= __hybrid_uint128_vec32_significand(v, 3)))
#endif /* !__HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */

#ifdef __INTELLISENSE__ /* Only for syntax highlighting... */
#define __hybrid_int128_add8(var, v)  __hybrid_int128_or8(var, v)
#define __hybrid_int128_add16(var, v) __hybrid_int128_or16(var, v)
#define __hybrid_int128_add32(var, v) __hybrid_int128_or32(var, v)
#define __hybrid_int128_sub8(var, v)  __hybrid_int128_or8(var, v)
#define __hybrid_int128_sub16(var, v) __hybrid_int128_or16(var, v)
#define __hybrid_int128_sub32(var, v) __hybrid_int128_or32(var, v)
#ifdef __UINT64_TYPE__
#define __hybrid_int128_add64(var, v) __hybrid_int128_or64(var, v)
#define __hybrid_int128_sub64(var, v) __hybrid_int128_or64(var, v)
#endif /* __UINT64_TYPE__ */
#define __hybrid_int128_add128(var, v) __hybrid_int128_or128(var, v)
#define __hybrid_int128_sub128(var, v) __hybrid_int128_or128(var, v)
#else /* __INTELLISENSE__ */
#define __hybrid_int128_add8(var, v)  ((__INT8_TYPE__)(v) >= 0 ? __hybrid_uint128_add8(var, v) : __hybrid_uint128_sub8(var, -(__INT8_TYPE__)(v)))
#define __hybrid_int128_add16(var, v) ((__INT16_TYPE__)(v) >= 0 ? __hybrid_uint128_add16(var, v) : __hybrid_uint128_sub16(var, -(__INT16_TYPE__)(v)))
#define __hybrid_int128_add32(var, v) ((__INT32_TYPE__)(v) >= 0 ? __hybrid_uint128_add32(var, v) : __hybrid_uint128_sub32(var, -(__INT32_TYPE__)(v)))
#define __hybrid_int128_sub8(var, v)  ((__INT8_TYPE__)(v) >= 0 ? __hybrid_uint128_sub8(var, v) : __hybrid_uint128_add8(var, -(__INT8_TYPE__)(v)))
#define __hybrid_int128_sub16(var, v) ((__INT16_TYPE__)(v) >= 0 ? __hybrid_uint128_sub16(var, v) : __hybrid_uint128_add16(var, -(__INT16_TYPE__)(v)))
#define __hybrid_int128_sub32(var, v) ((__INT32_TYPE__)(v) >= 0 ? __hybrid_uint128_sub32(var, v) : __hybrid_uint128_add32(var, -(__INT32_TYPE__)(v)))
#ifdef __UINT64_TYPE__
#define __hybrid_int128_add64(var, v) ((__INT64_TYPE__)(v) >= 0 ? __hybrid_uint128_add64(var, v) : __hybrid_uint128_sub64(var, -(__INT64_TYPE__)(v)))
#define __hybrid_int128_sub64(var, v) ((__INT64_TYPE__)(v) >= 0 ? __hybrid_uint128_sub64(var, v) : __hybrid_uint128_add64(var, -(__INT64_TYPE__)(v)))
#endif /* __UINT64_TYPE__ */
#define __hybrid_int128_add128(var, v) (__hybrid_int128_isneg(v) ? __hybrid_uint128_sub128_neg((__hybrid_uint128_t *)&(var), (__hybrid_int128_t const *)&(v)) : __hybrid_uint128_add128(var, v))
#define __hybrid_int128_sub128(var, v) (__hybrid_int128_isneg(v) ? __hybrid_uint128_add128_neg((__hybrid_uint128_t *)&(var), (__hybrid_int128_t const *)&(v)) : __hybrid_uint128_sub128(var, v))
#endif /* !__INTELLISENSE__ */


#define __hybrid_uint128_mul8(var, v)   __hybrid_uint128_mul32_impl(&(var), v)
#define __hybrid_uint128_mul16(var, v)  __hybrid_uint128_mul32_impl(&(var), v)
#define __hybrid_uint128_mul32(var, v)  __hybrid_uint128_mul32_impl(&(var), v)
#define __hybrid_uint128_mul128(var, v) __hybrid_uint128_mul128_impl(&(var), &(v))
#define __hybrid_int128_mul8(var, v)    __hybrid_int128_mul32_impl(&(var), v)
#define __hybrid_int128_mul16(var, v)   __hybrid_int128_mul32_impl(&(var), v)
#define __hybrid_int128_mul32(var, v)   __hybrid_int128_mul32_impl(&(var), v)
#define __hybrid_int128_mul128(var, v)  __hybrid_int128_mul128_impl(&(var), &(v))
#ifdef __UINT64_TYPE__
#define __hybrid_uint128_mul64(var, v)  __hybrid_uint128_mul64_impl(&(var), v)
#define __hybrid_int128_mul64(var, v)   __hybrid_int128_mul64_impl(&(var), v)
#endif /* __UINT64_TYPE__ */

#define __hybrid_int128_floordivmod8(var, v, divres, modres)   __hybrid_PRIVATE_int128_floordivmod8(&(var), (__UINT8_TYPE__)(v), &(divres), &(modres))
#define __hybrid_int128_floordivmod16(var, v, divres, modres)  __hybrid_PRIVATE_int128_floordivmod16(&(var), (__UINT16_TYPE__)(v), &(divres), &(modres))
#define __hybrid_int128_floordivmod32(var, v, divres, modres)  __hybrid_PRIVATE_int128_floordivmod32(&(var), (__UINT32_TYPE__)(v), &(divres), &(modres))
#define __hybrid_int128_floordivmod128(var, v, divres, modres) __hybrid_PRIVATE_int128_floordivmod128(&(var), &(v), &(divres), &(modres))

#define __hybrid_int128_floordiv8(var, v)         __hybrid_PRIVATE_int128_floordiv32(&(var), v)
#define __hybrid_int128_floordiv16(var, v)        __hybrid_PRIVATE_int128_floordiv32(&(var), v)
#define __hybrid_int128_floordiv32(var, v)        __hybrid_PRIVATE_int128_floordiv32(&(var), v)
#define __hybrid_int128_floordiv128(var, v)       __hybrid_PRIVATE_int128_floordivmod128(&(var), &(v), &(var), __NULLPTR)
#define __hybrid_int128_floormod8(var, v)         __hybrid_PRIVATE_int128_floormod32(&(var), v)
#define __hybrid_int128_floormod16(var, v)        __hybrid_PRIVATE_int128_floormod32(&(var), v)
#define __hybrid_int128_floormod32(var, v)        __hybrid_PRIVATE_int128_floormod32(&(var), v)
#define __hybrid_int128_floormod128(var, v)       __hybrid_PRIVATE_int128_floordivmod128(&(var), &(v), __NULLPTR, (__hybrid_uint128_t *)&(var))
#define __hybrid_int128_floormod8_r(var, v, res)  __hybrid_PRIVATE_int128_floordivmod8(&(var), v, __NULLPTR, &(res))
#define __hybrid_int128_floormod16_r(var, v, res) __hybrid_PRIVATE_int128_floordivmod16(&(var), v, __NULLPTR, &(res))
#define __hybrid_int128_floormod32_r(var, v, res) __hybrid_PRIVATE_int128_floordivmod32(&(var), v, __NULLPTR, &(res))

#define __hybrid_uint128_divmod8(var, v, divres, modres)   __hybrid_PRIVATE_uint128_divmod8(&(var), (__UINT8_TYPE__)(v), &(divres), &(modres))
#define __hybrid_uint128_divmod16(var, v, divres, modres)  __hybrid_PRIVATE_uint128_divmod16(&(var), (__UINT16_TYPE__)(v), &(divres), &(modres))
#define __hybrid_uint128_divmod32(var, v, divres, modres)  __hybrid_PRIVATE_uint128_divmod32(&(var), (__UINT32_TYPE__)(v), &(divres), &(modres))
#define __hybrid_uint128_divmod128(var, v, divres, modres) __hybrid_PRIVATE_uint128_divmod128(&(var), &(v), &(divres), &(modres))
#define __hybrid_int128_divmod8(var, v, divres, modres)    __hybrid_PRIVATE_int128_divmod8(&(var), (__UINT8_TYPE__)(v), &(divres), &(modres))
#define __hybrid_int128_divmod16(var, v, divres, modres)   __hybrid_PRIVATE_int128_divmod16(&(var), (__UINT16_TYPE__)(v), &(divres), &(modres))
#define __hybrid_int128_divmod32(var, v, divres, modres)   __hybrid_PRIVATE_int128_divmod32(&(var), (__UINT32_TYPE__)(v), &(divres), &(modres))
#define __hybrid_int128_divmod128(var, v, divres, modres)  __hybrid_PRIVATE_int128_divmod128(&(var), &(v), &(divres), &(modres))

#define __hybrid_uint128_div8(var, v)         __hybrid_PRIVATE_uint128_div32(&(var), v)
#define __hybrid_uint128_div16(var, v)        __hybrid_PRIVATE_uint128_div32(&(var), v)
#define __hybrid_uint128_div32(var, v)        __hybrid_PRIVATE_uint128_div32(&(var), v)
#define __hybrid_uint128_div128(var, v)       __hybrid_PRIVATE_uint128_divmod128(&(var), &(v), &(var), __NULLPTR)
#define __hybrid_int128_div8(var, v)          __hybrid_PRIVATE_int128_div32(&(var), v)
#define __hybrid_int128_div16(var, v)         __hybrid_PRIVATE_int128_div32(&(var), v)
#define __hybrid_int128_div32(var, v)         __hybrid_PRIVATE_int128_div32(&(var), v)
#define __hybrid_int128_div128(var, v)        __hybrid_PRIVATE_int128_divmod128(&(var), &(v), &(var), __NULLPTR)
#define __hybrid_uint128_mod8(var, v)         __hybrid_PRIVATE_uint128_mod32(&(var), v)
#define __hybrid_uint128_mod16(var, v)        __hybrid_PRIVATE_uint128_mod32(&(var), v)
#define __hybrid_uint128_mod32(var, v)        __hybrid_PRIVATE_uint128_mod32(&(var), v)
#define __hybrid_uint128_mod128(var, v)       __hybrid_PRIVATE_uint128_divmod128(&(var), &(v), __NULLPTR, &(var))
#define __hybrid_int128_mod8(var, v)          __hybrid_PRIVATE_int128_mod32(&(var), v)
#define __hybrid_int128_mod16(var, v)         __hybrid_PRIVATE_int128_mod32(&(var), v)
#define __hybrid_int128_mod32(var, v)         __hybrid_PRIVATE_int128_mod32(&(var), v)
#define __hybrid_int128_mod128(var, v)        __hybrid_PRIVATE_int128_divmod128(&(var), &(v), __NULLPTR, &(var))
#define __hybrid_uint128_mod8_r(var, v, res)  __hybrid_PRIVATE_uint128_divmod8(&(var), v, __NULLPTR, &(res))
#define __hybrid_uint128_mod16_r(var, v, res) __hybrid_PRIVATE_uint128_divmod16(&(var), v, __NULLPTR, &(res))
#define __hybrid_uint128_mod32_r(var, v, res) __hybrid_PRIVATE_uint128_divmod32(&(var), v, __NULLPTR, &(res))
#define __hybrid_int128_mod8_r(var, v, res)   __hybrid_PRIVATE_int128_divmod8(&(var), v, __NULLPTR, &(res))
#define __hybrid_int128_mod16_r(var, v, res)  __hybrid_PRIVATE_int128_divmod16(&(var), v, __NULLPTR, &(res))
#define __hybrid_int128_mod32_r(var, v, res)  __hybrid_PRIVATE_int128_divmod32(&(var), v, __NULLPTR, &(res))
#ifdef __UINT64_TYPE__
#define __hybrid_int128_floordivmod64(var, v, divres, modres) \
	__hybrid_PRIVATE_int128_floordivmod64(&(var), (__UINT64_TYPE__)(v), &(divres), &(modres))
#define __hybrid_int128_floordiv64(var, v)        __hybrid_PRIVATE_int128_floordiv64(&(var), v)
#define __hybrid_int128_floormod64(var, v)        __hybrid_PRIVATE_int128_floormod64(&(var), v)
#define __hybrid_int128_floormod64_r(var, v, res) __hybrid_PRIVATE_int128_floordivmod64(&(var), v, __NULLPTR, &(res))

#define __hybrid_uint128_divmod64(var, v, divres, modres) \
	__hybrid_PRIVATE_uint128_divmod64(&(var), (__UINT64_TYPE__)(v), &(divres), &(modres))
#define __hybrid_int128_divmod64(var, v, divres, modres) \
	__hybrid_PRIVATE_int128_divmod64(&(var), (__UINT64_TYPE__)(v), &(divres), &(modres))
#define __hybrid_uint128_div64(var, v)        __hybrid_PRIVATE_uint128_div64(&(var), v)
#define __hybrid_int128_div64(var, v)         __hybrid_PRIVATE_int128_div64(&(var), v)
#define __hybrid_uint128_mod64(var, v)        __hybrid_PRIVATE_uint128_mod64(&(var), v)
#define __hybrid_int128_mod64(var, v)         __hybrid_PRIVATE_int128_mod64(&(var), v)
#define __hybrid_uint128_mod64_r(var, v, res) __hybrid_PRIVATE_uint128_divmod64(&(var), v, __NULLPTR, &(res))
#define __hybrid_int128_mod64_r(var, v, res)  __hybrid_PRIVATE_int128_divmod64(&(var), v, __NULLPTR, &(res))
#endif /* __UINT64_TYPE__ */


#ifdef __INTELLISENSE__ /* Only for syntax highlighting... */
#define __hybrid_uint128_shl_overflows(var, shift)   (__hybrid_uint128_vec8_significand(var, 0) && (shift))
#define __hybrid_uint128_shl(var, shift)             (void)(__hybrid_uint128_vec8_significand(var, 0) = (shift))
#define __hybrid_uint128_shl32_overflows             __hybrid_uint128_shl_overflows
#define __hybrid_uint128_shl32                       __hybrid_uint128_shl
#define __hybrid_uint128_shl64_overflows             __hybrid_uint128_shl_overflows
#define __hybrid_uint128_shl64                       __hybrid_uint128_shl
#define __hybrid_uint128_shr_overflows               __hybrid_uint128_shl_overflows
#define __hybrid_uint128_shr                         __hybrid_uint128_shl
#define __hybrid_uint128_shr32_overflows             __hybrid_uint128_shl_overflows
#define __hybrid_uint128_shr32                       __hybrid_uint128_shl
#define __hybrid_uint128_shr64_overflows             __hybrid_uint128_shl_overflows
#define __hybrid_uint128_shr64                       __hybrid_uint128_shl
#define __hybrid_int128_shl_overflows(var, shift)    (__hybrid_int128_vec8_significand(var, 0) && (shift))
#define __hybrid_int128_shl(var, shift)              (void)(__hybrid_int128_vec8_significand(var, 0) = (shift))
#define __hybrid_int128_shl32_overflows              __hybrid_int128_shl_overflows
#define __hybrid_int128_shl32                        __hybrid_int128_shl
#define __hybrid_int128_shl64_overflows              __hybrid_int128_shl_overflows
#define __hybrid_int128_shl64                        __hybrid_int128_shl
#define __hybrid_int128_shr_overflows                __hybrid_int128_shl_overflows
#define __hybrid_int128_shr                          __hybrid_int128_shl
#define __hybrid_int128_shr32_overflows              __hybrid_int128_shl_overflows
#define __hybrid_int128_shr32                        __hybrid_int128_shl
#define __hybrid_int128_shr64_overflows              __hybrid_int128_shl_overflows
#define __hybrid_int128_shr64                        __hybrid_int128_shl
#else /* __INTELLISENSE__ */
#define __hybrid_uint128_shl32_overflows(var, shift) \
	((shift) != 0 && (__hybrid_uint128_vec32_significand(var, 3) >> (32 - (shift))) != 0)
#ifdef __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
/* Unsigned <<= shift-left for `shift < 64' */
#define __hybrid_uint128_shl64(var, shift) (!(shift) ? (void)0 : (void)(                                        \
	__hybrid_uint128_vec64_significand(var, 1) <<= (shift),                                                     \
	__hybrid_uint128_vec64_significand(var, 1) |= __hybrid_uint128_vec64_significand(var, 0) >> (64 - (shift)), \
	__hybrid_uint128_vec64_significand(var, 0) <<= (shift)))
#define __hybrid_uint128_shl64_overflows(var, shift) \
	((shift) != 0 && (__hybrid_uint128_vec64_significand(var, 1) >> (64 - (shift))) != 0)
#define __hybrid_uint128_shl32 __hybrid_uint128_shl64
#else /* __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
/* Unsigned <<= shift-left for `shift < 32' */
#define __hybrid_uint128_shl32(var, shift) (!(shift) ? (void)0 : (void)(                                        \
	__hybrid_uint128_vec32_significand(var, 3) <<= (shift),                                                     \
	__hybrid_uint128_vec32_significand(var, 3) |= __hybrid_uint128_vec32_significand(var, 2) >> (32 - (shift)), \
	__hybrid_uint128_vec32_significand(var, 2) <<= (shift),                                                     \
	__hybrid_uint128_vec32_significand(var, 2) |= __hybrid_uint128_vec32_significand(var, 1) >> (32 - (shift)), \
	__hybrid_uint128_vec32_significand(var, 1) <<= (shift),                                                     \
	__hybrid_uint128_vec32_significand(var, 1) |= __hybrid_uint128_vec32_significand(var, 0) >> (32 - (shift)), \
	__hybrid_uint128_vec32_significand(var, 0) <<= (shift)))
/* Unsigned <<= shift-left for `shift < 64' */
#define __hybrid_uint128_shl64(var, shift)                                                             \
	((shift) >= 32                                                                                     \
	 ? (void)(__hybrid_uint128_vec32_significand(var, 3) = __hybrid_uint128_vec32_significand(var, 2), \
	          __hybrid_uint128_vec32_significand(var, 2) = __hybrid_uint128_vec32_significand(var, 1), \
	          __hybrid_uint128_vec32_significand(var, 1) = __hybrid_uint128_vec32_significand(var, 0), \
	          __hybrid_uint128_vec32_significand(var, 0) = 0)                                          \
	 : (void)0,                                                                                        \
	 __hybrid_uint128_shl32(var, (shift) % 32))
#define __hybrid_uint128_shl64_overflows(var, shift)                                \
	((shift) >= 32                                                                  \
	 ? (__hybrid_uint128_vec32_significand(var, 3) != 0 ||                          \
	    (__hybrid_uint128_vec32_significand(var, 2) >> (32 - ((shift) % 32))) != 0) \
	 : __hybrid_uint128_shl32_overflows(var, shift))
#endif /* !__HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */

/* Unsigned <<= shift-left for `shift < 128' */
#ifdef __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
#define __hybrid_uint128_shl(var, shift)                                                               \
	((shift) >= 64                                                                                     \
	 ? (void)(__hybrid_uint128_vec64_significand(var, 1) = __hybrid_uint128_vec64_significand(var, 0), \
	          __hybrid_uint128_vec64_significand(var, 0) = 0)                                          \
	 : (void)0,                                                                                        \
	 __hybrid_uint128_shl64(var, (shift) % 64))
#define __hybrid_uint128_shl_overflows(var, shift)                                  \
	((shift) >= 64                                                                  \
	 ? (__hybrid_uint128_vec64_significand(var, 1) != 0 ||                          \
	    (__hybrid_uint128_vec64_significand(var, 0) >> (64 - ((shift) % 64))) != 0) \
	 : __hybrid_uint128_shl64_overflows(var, shift))
#else /* __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
#define __hybrid_uint128_shl(var, shift)                                                                   \
	((shift) >= 96                                                                                         \
	 ? (void)(__hybrid_uint128_vec32_significand(var, 3) = __hybrid_uint128_vec32_significand(var, 0),     \
	          __hybrid_uint128_vec32_significand(var, 2) = 0,                                              \
	          __hybrid_uint128_vec32_significand(var, 1) = 0,                                              \
	          __hybrid_uint128_vec32_significand(var, 0) = 0)                                              \
	 : (shift) >= 64                                                                                       \
	   ? (void)(__hybrid_uint128_vec32_significand(var, 3) = __hybrid_uint128_vec32_significand(var, 1),   \
	            __hybrid_uint128_vec32_significand(var, 2) = __hybrid_uint128_vec32_significand(var, 0),   \
	            __hybrid_uint128_vec32_significand(var, 1) = 0,                                            \
	            __hybrid_uint128_vec32_significand(var, 0) = 0)                                            \
	   : (shift) >= 32                                                                                     \
	     ? (void)(__hybrid_uint128_vec32_significand(var, 3) = __hybrid_uint128_vec32_significand(var, 2), \
	              __hybrid_uint128_vec32_significand(var, 2) = __hybrid_uint128_vec32_significand(var, 1), \
	              __hybrid_uint128_vec32_significand(var, 1) = __hybrid_uint128_vec32_significand(var, 0), \
	              __hybrid_uint128_vec32_significand(var, 0) = 0)                                          \
	     : (void)0,                                                                                        \
	 __hybrid_uint128_shl32(var, (shift) % 32))
#define __hybrid_uint128_shl_overflows(var, shift)                                      \
	((shift) >= 96                                                                      \
	 ? (__hybrid_uint128_vec32_significand(var, 3) != 0 ||                              \
	    __hybrid_uint128_vec32_significand(var, 2) != 0 ||                              \
	    __hybrid_uint128_vec32_significand(var, 1) != 0 ||                              \
	    (__hybrid_uint128_vec32_significand(var, 0) >> (32 - ((shift) % 32))) != 0)     \
	 : (shift) >= 64                                                                    \
	   ? (__hybrid_uint128_vec32_significand(var, 3) != 0 ||                            \
	      __hybrid_uint128_vec32_significand(var, 2) != 0 ||                            \
	      (__hybrid_uint128_vec32_significand(var, 1) >> (32 - ((shift) % 32))) != 0)   \
	   : (shift) >= 32                                                                  \
	     ? (__hybrid_uint128_vec32_significand(var, 3) != 0 ||                          \
	        (__hybrid_uint128_vec32_significand(var, 2) >> (32 - ((shift) % 32))) != 0) \
	     : __hybrid_uint128_shl32_overflows(var, shift))
#endif /* !__HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */

/* Signed <<= shift-left */
#define __hybrid_int128_shl             __hybrid_uint128_shl
#define __hybrid_int128_shl_overflows   __hybrid_uint128_shl_overflows
#define __hybrid_int128_shl32           __hybrid_uint128_shl32
#define __hybrid_int128_shl32_overflows __hybrid_uint128_shl32_overflows
#define __hybrid_int128_shl64           __hybrid_uint128_shl64
#define __hybrid_int128_shl64_overflows __hybrid_uint128_shl64_overflows
#define __hybrid_uint128_shr32_overflows(var, shift) \
	((__hybrid_int128_vec32_significand(var, 0) & ((__UINT32_C(1) << (shift)) - 1)) != 0)
#ifdef __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
/* Unsigned >>= shift-right for `shift < 64' */
#define __hybrid_uint128_shr64(var, shift) (!(shift) ? (void)0 : (void)(                                         \
	__hybrid_uint128_vec64_significand(var, 0) >>= (shift),                                                     \
	__hybrid_uint128_vec64_significand(var, 0) |= __hybrid_uint128_vec64_significand(var, 1) << (64 - (shift)), \
	__hybrid_uint128_vec64_significand(var, 1) >>= (shift)))
#define __hybrid_uint128_shr64_overflows(var, shift) \
	((__hybrid_int128_vec64_significand(var, 0) & ((__UINT64_C(1) << (shift)) - 1)) != 0)
#define __hybrid_uint128_shr32 __hybrid_uint128_shr64
#else /* __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
/* Unsigned >>= shift-right for `shift < 32' */
#define __hybrid_uint128_shr32(var, shift) (!(shift) ? (void)0 : (void)(                                        \
	__hybrid_uint128_vec32_significand(var, 0) >>= (shift),                                                     \
	__hybrid_uint128_vec32_significand(var, 0) |= __hybrid_uint128_vec32_significand(var, 1) << (32 - (shift)), \
	__hybrid_uint128_vec32_significand(var, 1) >>= (shift),                                                     \
	__hybrid_uint128_vec32_significand(var, 1) |= __hybrid_uint128_vec32_significand(var, 2) << (32 - (shift)), \
	__hybrid_uint128_vec32_significand(var, 2) >>= (shift),                                                     \
	__hybrid_uint128_vec32_significand(var, 2) |= __hybrid_uint128_vec32_significand(var, 3) << (32 - (shift)), \
	__hybrid_uint128_vec32_significand(var, 3) >>= (shift)))
/* Unsigned >>= shift-right for `shift < 64' */
#define __hybrid_uint128_shr64(var, shift)                                                             \
	((shift) >= 32                                                                                     \
	 ? (void)(__hybrid_uint128_vec32_significand(var, 0) = __hybrid_uint128_vec32_significand(var, 1), \
	          __hybrid_uint128_vec32_significand(var, 1) = __hybrid_uint128_vec32_significand(var, 2), \
	          __hybrid_uint128_vec32_significand(var, 2) = __hybrid_uint128_vec32_significand(var, 3), \
	          __hybrid_uint128_vec32_significand(var, 3) = 0)                                          \
	 : (void)0,                                                                                        \
	 __hybrid_uint128_shr32(var, (shift) % 32))
#define __hybrid_uint128_shr64_overflows(var, shift)                                                 \
	((shift) >= 32                                                                                   \
	 ? (__hybrid_uint128_vec32_significand(var, 0) != 0 ||                                           \
	    (__hybrid_uint128_vec32_significand(var, 1) & ((__UINT32_C(1) << ((shift) % 32)) - 1)) != 0) \
	 : __hybrid_uint128_shr32_overflows(var, shift))
#endif /* !__HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */

/* Unsigned >>= shift-right for `shift < 128' */
#ifdef __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
#define __hybrid_uint128_shr(var, shift)                                                               \
	((shift) >= 64                                                                                     \
	 ? (void)(__hybrid_uint128_vec64_significand(var, 0) = __hybrid_uint128_vec64_significand(var, 1), \
	          __hybrid_uint128_vec64_significand(var, 1) = 0)                                          \
	 : (void)0,                                                                                        \
	 __hybrid_uint128_shr64(var, (shift) % 64))
#define __hybrid_uint128_shr_overflows(var, shift)                                                   \
	((shift) >= 64                                                                                   \
	 ? (__hybrid_uint128_vec64_significand(var, 0) != 0 ||                                           \
	    (__hybrid_uint128_vec64_significand(var, 1) & ((__UINT64_C(1) << ((shift) % 64)) - 1)) != 0) \
	 : __hybrid_uint128_shr64_overflows(var, shift))
#else /* __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
#define __hybrid_uint128_shr(var, shift)                                                                   \
	((shift) >= 96                                                                                         \
	 ? (void)(__hybrid_uint128_vec32_significand(var, 0) = __hybrid_uint128_vec32_significand(var, 3),     \
	          __hybrid_uint128_vec32_significand(var, 1) = 0,                                              \
	          __hybrid_uint128_vec32_significand(var, 2) = 0,                                              \
	          __hybrid_uint128_vec32_significand(var, 3) = 0)                                              \
	 : (shift) >= 64                                                                                       \
	   ? (void)(__hybrid_uint128_vec32_significand(var, 0) = __hybrid_uint128_vec32_significand(var, 2),   \
	            __hybrid_uint128_vec32_significand(var, 1) = __hybrid_uint128_vec32_significand(var, 3),   \
	            __hybrid_uint128_vec32_significand(var, 2) = 0,                                            \
	            __hybrid_uint128_vec32_significand(var, 3) = 0)                                            \
	   : (shift) >= 32                                                                                     \
	     ? (void)(__hybrid_uint128_vec32_significand(var, 0) = __hybrid_uint128_vec32_significand(var, 1), \
	              __hybrid_uint128_vec32_significand(var, 1) = __hybrid_uint128_vec32_significand(var, 2), \
	              __hybrid_uint128_vec32_significand(var, 2) = __hybrid_uint128_vec32_significand(var, 3), \
	              __hybrid_uint128_vec32_significand(var, 3) = 0)                                          \
	     : (void)0,                                                                                        \
	 __hybrid_uint128_shr32(var, (shift) % 32))
#define __hybrid_uint128_shr_overflows(var, shift)                                                       \
	((shift) >= 96                                                                                       \
	 ? (__hybrid_uint128_vec32_significand(var, 0) != 0 ||                                               \
	    __hybrid_uint128_vec32_significand(var, 1) != 0 ||                                               \
	    __hybrid_uint128_vec32_significand(var, 2) != 0 ||                                               \
	    (__hybrid_uint128_vec32_significand(var, 3) & ((__UINT32_C(1) << ((shift) % 32)) - 1)) != 0)     \
	 : (shift) >= 64                                                                                     \
	   ? (__hybrid_uint128_vec32_significand(var, 0) != 0 ||                                             \
	      __hybrid_uint128_vec32_significand(var, 1) != 0 ||                                             \
	      (__hybrid_uint128_vec32_significand(var, 2) & ((__UINT32_C(1) << ((shift) % 32)) - 1)) != 0)   \
	   : (shift) >= 32                                                                                   \
	     ? (__hybrid_uint128_vec32_significand(var, 0) != 0 ||                                           \
	        (__hybrid_uint128_vec32_significand(var, 1) & ((__UINT32_C(1) << ((shift) % 32)) - 1)) != 0) \
	     : __hybrid_uint128_shr32_overflows(var, shift))
#endif /* !__HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */


#define __hybrid_int128_shr32_overflows __hybrid_uint128_shr32_overflows
#define __hybrid_int128_shr64_overflows __hybrid_uint128_shr64_overflows
#define __hybrid_int128_shr_overflows   __hybrid_uint128_shr_overflows
#ifdef __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
/* Unsigned >>= shift-right for `shift < 64' */
#define __hybrid_int128_shr64(var, shift) (!(shift) ? (void)0 : (void)(                                         \
	__hybrid_uint128_vec64_significand(var, 0) >>= (shift),                                                     \
	__hybrid_uint128_vec64_significand(var, 0) |= __hybrid_uint128_vec64_significand(var, 1) << (64 - (shift)), \
	__hybrid_int128_vec64_significand(var, 1) >>= (shift)))
#define __hybrid_int128_shr32 __hybrid_int128_shr64
#else /* __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
/* Unsigned >>= shift-right for `shift < 32' */
#define __hybrid_int128_shr32(var, shift) (!(shift) ? (void)0 : (void)(                                         \
	__hybrid_uint128_vec32_significand(var, 0) >>= (shift),                                                     \
	__hybrid_uint128_vec32_significand(var, 0) |= __hybrid_uint128_vec32_significand(var, 1) << (32 - (shift)), \
	__hybrid_uint128_vec32_significand(var, 1) >>= (shift),                                                     \
	__hybrid_uint128_vec32_significand(var, 1) |= __hybrid_uint128_vec32_significand(var, 2) << (32 - (shift)), \
	__hybrid_uint128_vec32_significand(var, 2) >>= (shift),                                                     \
	__hybrid_uint128_vec32_significand(var, 2) |= __hybrid_uint128_vec32_significand(var, 3) << (32 - (shift)), \
	__hybrid_int128_vec32_significand(var, 3) >>= (shift)))
/* Unsigned >>= shift-right for `shift < 64' */
#define __hybrid_int128_shr64(var, shift)                                                              \
	((shift) >= 32                                                                                     \
	 ? (void)(__hybrid_uint128_vec32_significand(var, 0) = __hybrid_uint128_vec32_significand(var, 1), \
	          __hybrid_uint128_vec32_significand(var, 1) = __hybrid_uint128_vec32_significand(var, 2), \
	          __hybrid_uint128_vec32_significand(var, 2) = __hybrid_uint128_vec32_significand(var, 3), \
	          __hybrid_uint128_vec32_significand(var, 3) = 0)                                          \
	 : (void)0,                                                                                        \
	 __hybrid_int128_shr32(var, (shift) % 32))
#endif /* !__HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */

/* Unsigned >>= shift-right for `shift < 128' */
#ifdef __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
#define __hybrid_int128_shr(var, shift)                                                                \
	((shift) >= 64                                                                                     \
	 ? (void)(__hybrid_uint128_vec64_significand(var, 0) = __hybrid_uint128_vec64_significand(var, 1), \
	          __hybrid_uint128_vec64_significand(var, 1) = 0)                                          \
	 : (void)0,                                                                                        \
	 __hybrid_int128_shr64(var, (shift) % 64))
#else /* __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
#define __hybrid_int128_shr(var, shift)                                                                    \
	((shift) >= 96                                                                                         \
	 ? (void)(__hybrid_uint128_vec32_significand(var, 0) = __hybrid_uint128_vec32_significand(var, 3),     \
	          __hybrid_uint128_vec32_significand(var, 1) = 0,                                              \
	          __hybrid_uint128_vec32_significand(var, 2) = 0,                                              \
	          __hybrid_uint128_vec32_significand(var, 3) = 0)                                              \
	 : (shift) >= 64                                                                                       \
	   ? (void)(__hybrid_uint128_vec32_significand(var, 0) = __hybrid_uint128_vec32_significand(var, 2),   \
	            __hybrid_uint128_vec32_significand(var, 1) = __hybrid_uint128_vec32_significand(var, 3),   \
	            __hybrid_uint128_vec32_significand(var, 2) = 0,                                            \
	            __hybrid_uint128_vec32_significand(var, 3) = 0)                                            \
	   : (shift) >= 32                                                                                     \
	     ? (void)(__hybrid_uint128_vec32_significand(var, 0) = __hybrid_uint128_vec32_significand(var, 1), \
	              __hybrid_uint128_vec32_significand(var, 1) = __hybrid_uint128_vec32_significand(var, 2), \
	              __hybrid_uint128_vec32_significand(var, 2) = __hybrid_uint128_vec32_significand(var, 3), \
	              __hybrid_uint128_vec32_significand(var, 3) = 0)                                          \
	     : (void)0,                                                                                        \
	 __hybrid_int128_shr32(var, (shift) % 32))
#endif /* !__HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
#endif /* !__INTELLISENSE__ */





#ifdef __INTELLISENSE__ /* Only for syntax highlighting... */
#define __hybrid_uint128_iszero(var)  (__hybrid_uint128_vec64(var)[0] == 0)
#define __hybrid_uint128_setzero(var) (void)(__hybrid_uint128_vec64(var)[0] = 0)
#define __hybrid_int128_iszero(var)   (__hybrid_int128_vec64(var)[0] == 0)
#define __hybrid_int128_setzero(var)  (void)(__hybrid_int128_vec64(var)[0] = 0)
#define __hybrid_uint128_isone        __hybrid_uint128_iszero
#define __hybrid_uint128_setone       __hybrid_uint128_setzero
#define __hybrid_int128_isone         __hybrid_int128_iszero
#define __hybrid_int128_setone        __hybrid_int128_setzero
#define __hybrid_int128_isminusone    __hybrid_int128_iszero
#define __hybrid_int128_setminusone   __hybrid_int128_setzero
#define __hybrid_int128_ismin         __hybrid_int128_iszero
#define __hybrid_int128_setmin        __hybrid_int128_setzero
#define __hybrid_uint128_ismax        __hybrid_uint128_iszero
#define __hybrid_uint128_setmax       __hybrid_uint128_setzero
#define __hybrid_int128_ismax         __hybrid_int128_iszero
#define __hybrid_int128_setmax        __hybrid_int128_setzero
#else /* __INTELLISENSE__ */
#ifdef __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
#define __hybrid_uint128_iszero(var)        \
	(__hybrid_uint128_vec64(var)[0] == 0 && \
	 __hybrid_uint128_vec64(var)[1] == 0)
#define __hybrid_uint128_setzero(var)          \
	(void)(__hybrid_uint128_vec64(var)[0] = 0, \
	       __hybrid_uint128_vec64(var)[1] = 0)
#define __hybrid_uint128_isone(var)                     \
	(__hybrid_uint128_vec64_significand(var, 0) == 1 && \
	 __hybrid_uint128_vec64_significand(var, 1) == 0)
#define __hybrid_uint128_setone(var)                       \
	(void)(__hybrid_uint128_vec64_significand(var, 0) = 1, \
	       __hybrid_uint128_vec64_significand(var, 1) = 0)
#define __hybrid_int128_isminusone(var)      \
	(__hybrid_uint128_vec64(var)[0] == -1 && \
	 __hybrid_uint128_vec64(var)[1] == -1)
#define __hybrid_int128_setminusone(var)        \
	(void)(__hybrid_uint128_vec64(var)[0] = -1, \
	       __hybrid_uint128_vec64(var)[1] = -1)
#define __hybrid_int128_ismin(var)                     \
	(__hybrid_int128_vec64_significand(var, 0) == 0 && \
	 __hybrid_int128_vec64_significand(var, 1) == __PRIVATE_MIN_S8)
#define __hybrid_int128_setmin(var)                       \
	(void)(__hybrid_int128_vec64_significand(var, 0) = 0, \
	       __hybrid_int128_vec64_significand(var, 1) = __PRIVATE_MIN_S8)
#define __hybrid_int128_ismax(var)                      \
	(__hybrid_int128_vec64_significand(var, 0) == -1 && \
	 __hybrid_int128_vec64_significand(var, 1) == __PRIVATE_MAX_S8)
#define __hybrid_int128_setmax(var)                        \
	(void)(__hybrid_int128_vec64_significand(var, 0) = -1, \
	       __hybrid_int128_vec64_significand(var, 1) = __PRIVATE_MAX_S8)
#else /* __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
#define __hybrid_uint128_iszero(var)        \
	(__hybrid_uint128_vec32(var)[0] == 0 && \
	 __hybrid_uint128_vec32(var)[1] == 0 && \
	 __hybrid_uint128_vec32(var)[2] == 0 && \
	 __hybrid_uint128_vec32(var)[3] == 0)
#define __hybrid_uint128_setzero(var)          \
	(void)(__hybrid_uint128_vec32(var)[0] = 0, \
	       __hybrid_uint128_vec32(var)[1] = 0, \
	       __hybrid_uint128_vec32(var)[2] = 0, \
	       __hybrid_uint128_vec32(var)[3] = 0)
#define __hybrid_uint128_isone(var)                     \
	(__hybrid_uint128_vec32_significand(var, 0) == 1 && \
	 __hybrid_uint128_vec32_significand(var, 1) == 0 && \
	 __hybrid_uint128_vec32_significand(var, 2) == 0 && \
	 __hybrid_uint128_vec32_significand(var, 3) == 0)
#define __hybrid_uint128_setone(var)                       \
	(void)(__hybrid_uint128_vec32_significand(var, 0) = 1, \
	       __hybrid_uint128_vec32_significand(var, 1) = 0, \
	       __hybrid_uint128_vec32_significand(var, 2) = 0, \
	       __hybrid_uint128_vec32_significand(var, 3) = 0)
#define __hybrid_int128_isminusone(var)                  \
	(__hybrid_int128_vec32_significand(var, 0) == -1 && \
	 __hybrid_int128_vec32_significand(var, 1) == -1 && \
	 __hybrid_int128_vec32_significand(var, 2) == -1 && \
	 __hybrid_int128_vec32_significand(var, 3) == -1)
#define __hybrid_int128_setminusone(var)                   \
	(void)(__hybrid_int128_vec32_significand(var, 0) = -1, \
	       __hybrid_int128_vec32_significand(var, 1) = -1, \
	       __hybrid_int128_vec32_significand(var, 2) = -1, \
	       __hybrid_int128_vec32_significand(var, 3) = -1)
#define __hybrid_int128_ismin(var)                     \
	(__hybrid_int128_vec32_significand(var, 0) == 0 && \
	 __hybrid_int128_vec32_significand(var, 1) == 0 && \
	 __hybrid_int128_vec32_significand(var, 2) == 0 && \
	 __hybrid_int128_vec32_significand(var, 3) == __PRIVATE_MIN_S4)
#define __hybrid_int128_setmin(var)                       \
	(void)(__hybrid_int128_vec32_significand(var, 0) = 0, \
	       __hybrid_int128_vec32_significand(var, 1) = 0, \
	       __hybrid_int128_vec32_significand(var, 2) = 0, \
	       __hybrid_int128_vec32_significand(var, 3) = __PRIVATE_MIN_S4)
#define __hybrid_int128_ismax(var)                      \
	(__hybrid_int128_vec32_significand(var, 0) == -1 && \
	 __hybrid_int128_vec32_significand(var, 1) == -1 && \
	 __hybrid_int128_vec32_significand(var, 2) == -1 && \
	 __hybrid_int128_vec32_significand(var, 3) == __PRIVATE_MAX_S4)
#define __hybrid_int128_setmax(var)                        \
	(void)(__hybrid_int128_vec32_significand(var, 0) = -1, \
	       __hybrid_int128_vec32_significand(var, 1) = -1, \
	       __hybrid_int128_vec32_significand(var, 2) = -1, \
	       __hybrid_int128_vec32_significand(var, 3) = __PRIVATE_MAX_S4)
#endif /* !__HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
#define __hybrid_int128_iszero  __hybrid_uint128_iszero
#define __hybrid_int128_setzero __hybrid_uint128_setzero
#define __hybrid_int128_isone   __hybrid_uint128_isone
#define __hybrid_int128_setone  __hybrid_uint128_setone
#define __hybrid_uint128_ismax  __hybrid_int128_isminusone
#define __hybrid_uint128_setmax __hybrid_int128_setminusone
#endif /* !__INTELLISENSE__ */

#define __hybrid_uint128_ismin  __hybrid_uint128_iszero
#define __hybrid_uint128_setmin __hybrid_uint128_setzero


#ifdef __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
#define __hybrid_uint128_is8bit(var)                    \
	(__hybrid_uint128_vec8_significand(var, 1) == 0 &&  \
	 __hybrid_uint128_vec16_significand(var, 1) == 0 && \
	 __hybrid_uint128_vec32_significand(var, 1) == 0 && \
	 __hybrid_uint128_vec64_significand(var, 1) == 0)
#define __hybrid_uint128_is16bit(var)                   \
	(__hybrid_uint128_vec16_significand(var, 1) == 0 && \
	 __hybrid_uint128_vec32_significand(var, 1) == 0 && \
	 __hybrid_uint128_vec64_significand(var, 1) == 0)
#define __hybrid_uint128_is32bit(var)                   \
	(__hybrid_uint128_vec32_significand(var, 1) == 0 && \
	 __hybrid_uint128_vec64_significand(var, 1) == 0)
#define __hybrid_uint128_is64bit(var) \
	(__hybrid_uint128_vec64_significand(var, 1) == 0)
#define __hybrid_int128_is8bit(var)                        \
	(__hybrid_int128_isneg(var)                            \
	 ? (__hybrid_int128_vec8_significand(var, 0) < 0 &&    \
	    __hybrid_int128_vec8_significand(var, 1) == -1 &&  \
	    __hybrid_int128_vec16_significand(var, 1) == -1 && \
	    __hybrid_int128_vec32_significand(var, 1) == -1 && \
	    __hybrid_int128_vec64_significand(var, 1) == -1)   \
	 : (__hybrid_int128_vec8_significand(var, 0) >= 0 &&   \
	    __hybrid_int128_vec8_significand(var, 1) == 0 &&   \
	    __hybrid_int128_vec16_significand(var, 1) == 0 &&  \
	    __hybrid_int128_vec32_significand(var, 1) == 0 &&  \
	    __hybrid_int128_vec64_significand(var, 1) == 0))
#define __hybrid_int128_is16bit(var)                       \
	(__hybrid_int128_isneg(var)                            \
	 ? (__hybrid_int128_vec16_significand(var, 0) < 0 &&   \
	    __hybrid_int128_vec16_significand(var, 1) == -1 && \
	    __hybrid_int128_vec32_significand(var, 1) == -1 && \
	    __hybrid_int128_vec64_significand(var, 1) == -1)   \
	 : (__hybrid_int128_vec16_significand(var, 0) >= 0 &&  \
	    __hybrid_int128_vec16_significand(var, 1) == 0 &&  \
	    __hybrid_int128_vec32_significand(var, 1) == 0 &&  \
	    __hybrid_int128_vec64_significand(var, 1) == 0))
#define __hybrid_int128_is32bit(var)                       \
	(__hybrid_int128_isneg(var)                            \
	 ? (__hybrid_int128_vec32_significand(var, 0) < 0 &&   \
	    __hybrid_int128_vec32_significand(var, 1) == -1 && \
	    __hybrid_int128_vec64_significand(var, 1) == -1)   \
	 : (__hybrid_int128_vec32_significand(var, 0) >= 0 &&  \
	    __hybrid_int128_vec32_significand(var, 1) == 0 &&  \
	    __hybrid_int128_vec64_significand(var, 1) == 0))
#define __hybrid_int128_is64bit(var)                      \
	(__hybrid_int128_isneg(var)                           \
	 ? (__hybrid_int128_vec64_significand(var, 0) < 0 &&  \
	    __hybrid_int128_vec64_significand(var, 1) == -1)  \
	 : (__hybrid_int128_vec64_significand(var, 0) >= 0 && \
	    __hybrid_int128_vec64_significand(var, 1) == 0))
#else /* __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
#define __hybrid_uint128_is8bit(var)                    \
	(__hybrid_uint128_vec8_significand(var, 1) == 0 &&  \
	 __hybrid_uint128_vec16_significand(var, 1) == 0 && \
	 __hybrid_uint128_vec32_significand(var, 1) == 0 && \
	 __hybrid_uint128_vec32_significand(var, 2) == 0 && \
	 __hybrid_uint128_vec32_significand(var, 3) == 0)
#define __hybrid_uint128_is16bit(var)                   \
	(__hybrid_uint128_vec16_significand(var, 1) == 0 && \
	 __hybrid_uint128_vec32_significand(var, 1) == 0 && \
	 __hybrid_uint128_vec32_significand(var, 2) == 0 && \
	 __hybrid_uint128_vec32_significand(var, 3) == 0)
#define __hybrid_uint128_is32bit(var)                   \
	(__hybrid_uint128_vec32_significand(var, 1) == 0 && \
	 __hybrid_uint128_vec32_significand(var, 2) == 0 && \
	 __hybrid_uint128_vec32_significand(var, 3) == 0)
#define __hybrid_uint128_is64bit(var)                   \
	(__hybrid_uint128_vec32_significand(var, 2) == 0 && \
	 __hybrid_uint128_vec32_significand(var, 3) == 0)
#define __hybrid_int128_is8bit(var)                        \
	(__hybrid_int128_isneg(var)                            \
	 ? (__hybrid_int128_vec8_significand(var, 0) < 0 &&    \
	    __hybrid_int128_vec8_significand(var, 1) == -1 &&  \
	    __hybrid_int128_vec16_significand(var, 1) == -1 && \
	    __hybrid_int128_vec32_significand(var, 1) == -1 && \
	    __hybrid_int128_vec32_significand(var, 2) == -1 && \
	    __hybrid_int128_vec32_significand(var, 3) == -1)   \
	 : (__hybrid_int128_vec8_significand(var, 0) >= 0 &&   \
	    __hybrid_int128_vec8_significand(var, 1) == 0 &&   \
	    __hybrid_int128_vec16_significand(var, 1) == 0 &&  \
	    __hybrid_int128_vec32_significand(var, 1) == 0 &&  \
	    __hybrid_int128_vec32_significand(var, 2) == 0 &&  \
	    __hybrid_int128_vec32_significand(var, 3) == 0))
#define __hybrid_int128_is16bit(var)                       \
	(__hybrid_int128_isneg(var)                            \
	 ? (__hybrid_int128_vec16_significand(var, 0) < 0 &&   \
	    __hybrid_int128_vec16_significand(var, 1) == -1 && \
	    __hybrid_int128_vec32_significand(var, 1) == -1 && \
	    __hybrid_int128_vec32_significand(var, 2) == -1 && \
	    __hybrid_int128_vec32_significand(var, 3) == -1)   \
	 : (__hybrid_int128_vec16_significand(var, 0) >= 0 &&  \
	    __hybrid_int128_vec16_significand(var, 1) == 0 &&  \
	    __hybrid_int128_vec32_significand(var, 1) == 0 &&  \
	    __hybrid_int128_vec32_significand(var, 2) == 0 &&  \
	    __hybrid_int128_vec32_significand(var, 3) == 0))
#define __hybrid_int128_is32bit(var)                       \
	(__hybrid_int128_isneg(var)                            \
	 ? (__hybrid_int128_vec32_significand(var, 0) < 0 &&   \
	    __hybrid_int128_vec32_significand(var, 1) == -1 && \
	    __hybrid_int128_vec32_significand(var, 2) == -1 && \
	    __hybrid_int128_vec32_significand(var, 3) == -1)   \
	 : (__hybrid_int128_vec32_significand(var, 0) >= 0 &&  \
	    __hybrid_int128_vec32_significand(var, 1) == 0 &&  \
	    __hybrid_int128_vec32_significand(var, 2) == 0 &&  \
	    __hybrid_int128_vec32_significand(var, 3) == 0))
#define __hybrid_int128_is64bit(var)                       \
	(__hybrid_int128_isneg(var)                            \
	 ? (__hybrid_int128_vec32_significand(var, 1) < 0 &&   \
	    __hybrid_int128_vec32_significand(var, 2) == -1 && \
	    __hybrid_int128_vec32_significand(var, 3) == -1)   \
	 : (__hybrid_int128_vec32_significand(var, 1) >= 0 &&  \
	    __hybrid_int128_vec32_significand(var, 2) == 0 &&  \
	    __hybrid_int128_vec32_significand(var, 3) == 0))
#endif /* !__HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */

#define __hybrid_uint128_eq8(var, v)  (__hybrid_uint128_is8bit(var) && __hybrid_uint128_vec8_significand(var, 0) == (__UINT8_TYPE__)(v))
#define __hybrid_uint128_eq16(var, v) (__hybrid_uint128_is16bit(var) && __hybrid_uint128_vec16_significand(var, 0) == (__UINT16_TYPE__)(v))
#define __hybrid_uint128_eq32(var, v) (__hybrid_uint128_is32bit(var) && __hybrid_uint128_vec32_significand(var, 0) == (__UINT32_TYPE__)(v))
#define __hybrid_int128_eq8(var, v)   (__hybrid_int128_is8bit(var) && __hybrid_int128_vec8_significand(var, 0) == (__INT8_TYPE__)(v))
#define __hybrid_int128_eq16(var, v)  (__hybrid_int128_is16bit(var) && __hybrid_int128_vec16_significand(var, 0) == (__INT16_TYPE__)(v))
#define __hybrid_int128_eq32(var, v)  (__hybrid_int128_is32bit(var) && __hybrid_int128_vec32_significand(var, 0) == (__INT32_TYPE__)(v))
#ifdef __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
#define __hybrid_uint128_eq128(var, v)                                                         \
	(__hybrid_uint128_vec64_significand(var, 1) == __hybrid_uint128_vec64_significand(v, 1) && \
	 __hybrid_uint128_vec64_significand(var, 0) == __hybrid_uint128_vec64_significand(v, 0))
#else /* __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
#define __hybrid_uint128_eq128(var, v)                                                         \
	(__hybrid_uint128_vec32_significand(var, 3) == __hybrid_uint128_vec32_significand(v, 3) && \
	 __hybrid_uint128_vec32_significand(var, 2) == __hybrid_uint128_vec32_significand(v, 2) && \
	 __hybrid_uint128_vec32_significand(var, 1) == __hybrid_uint128_vec32_significand(v, 1) && \
	 __hybrid_uint128_vec32_significand(var, 0) == __hybrid_uint128_vec32_significand(v, 0))
#endif /* !__HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
#ifdef __UINT64_TYPE__
#define __hybrid_uint128_eq64(var, v) (__hybrid_uint128_is64bit(var) && __hybrid_uint128_vec64_significand(var, 0) == (__UINT64_TYPE__)(v))
#define __hybrid_int128_eq64(var, v)  (__hybrid_int128_is64bit(var) && __hybrid_int128_vec64_significand(var, 0) == (__INT64_TYPE__)(v))
#endif /* __UINT64_TYPE__ */

#define __hybrid_uint128_lo8(var, v)  (__hybrid_uint128_is8bit(var) && __hybrid_uint128_vec8_significand(var, 0) < (__UINT8_TYPE__)(v))
#define __hybrid_uint128_le8(var, v)  (__hybrid_uint128_is8bit(var) && __hybrid_uint128_vec8_significand(var, 0) <= (__UINT8_TYPE__)(v))
#define __hybrid_uint128_lo16(var, v) (__hybrid_uint128_is16bit(var) && __hybrid_uint128_vec16_significand(var, 0) < (__UINT16_TYPE__)(v))
#define __hybrid_uint128_le16(var, v) (__hybrid_uint128_is16bit(var) && __hybrid_uint128_vec16_significand(var, 0) <= (__UINT16_TYPE__)(v))
#define __hybrid_uint128_lo32(var, v) (__hybrid_uint128_is32bit(var) && __hybrid_uint128_vec32_significand(var, 0) < (__UINT32_TYPE__)(v))
#define __hybrid_uint128_le32(var, v) (__hybrid_uint128_is32bit(var) && __hybrid_uint128_vec32_significand(var, 0) <= (__UINT32_TYPE__)(v))
#define __hybrid_int128_lo8(var, v)   (__hybrid_int128_is8bit(var) && __hybrid_int128_vec8_significand(var, 0) < (__INT8_TYPE__)(v))
#define __hybrid_int128_le8(var, v)   (__hybrid_int128_is8bit(var) && __hybrid_int128_vec8_significand(var, 0) <= (__INT8_TYPE__)(v))
#define __hybrid_int128_lo16(var, v)  (__hybrid_int128_is16bit(var) && __hybrid_int128_vec16_significand(var, 0) < (__INT16_TYPE__)(v))
#define __hybrid_int128_le16(var, v)  (__hybrid_int128_is16bit(var) && __hybrid_int128_vec16_significand(var, 0) <= (__INT16_TYPE__)(v))
#define __hybrid_int128_lo32(var, v)  (__hybrid_int128_is32bit(var) && __hybrid_int128_vec32_significand(var, 0) < (__INT32_TYPE__)(v))
#define __hybrid_int128_le32(var, v)  (__hybrid_int128_is32bit(var) && __hybrid_int128_vec32_significand(var, 0) <= (__INT32_TYPE__)(v))

#ifdef __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
#define __hybrid_uint128_lo128(var, v)                                                          \
	(__hybrid_uint128_vec64_significand(var, 1) < __hybrid_uint128_vec64_significand(v, 1) ||   \
	 (__hybrid_uint128_vec64_significand(var, 1) == __hybrid_uint128_vec64_significand(v, 1) && \
	  __hybrid_uint128_vec64_significand(var, 0) < __hybrid_uint128_vec64_significand(v, 0)))
#define __hybrid_uint128_le128(var, v)                                                          \
	(__hybrid_uint128_vec64_significand(var, 1) < __hybrid_uint128_vec64_significand(v, 1) ||   \
	 (__hybrid_uint128_vec64_significand(var, 1) == __hybrid_uint128_vec64_significand(v, 1) && \
	  __hybrid_uint128_vec64_significand(var, 0) <= __hybrid_uint128_vec64_significand(v, 0)))
#else /* __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
#define __hybrid_uint128_lo128(var, v)                                                              \
	(__hybrid_uint128_vec32_significand(var, 3) < __hybrid_uint128_vec32_significand(v, 3) ||       \
	 (__hybrid_uint128_vec32_significand(var, 3) == __hybrid_uint128_vec32_significand(v, 3) &&     \
	  (__hybrid_uint128_vec32_significand(var, 2) < __hybrid_uint128_vec32_significand(v, 2) ||     \
	   (__hybrid_uint128_vec32_significand(var, 2) == __hybrid_uint128_vec32_significand(v, 2) &&   \
	    (__hybrid_uint128_vec32_significand(var, 1) < __hybrid_uint128_vec32_significand(v, 1) ||   \
	     (__hybrid_uint128_vec32_significand(var, 1) == __hybrid_uint128_vec32_significand(v, 1) && \
	      __hybrid_uint128_vec32_significand(var, 0) < __hybrid_uint128_vec32_significand(v, 0)))))))
#define __hybrid_uint128_le128(var, v)                                                              \
	(__hybrid_uint128_vec32_significand(var, 3) < __hybrid_uint128_vec32_significand(v, 3) ||       \
	 (__hybrid_uint128_vec32_significand(var, 3) == __hybrid_uint128_vec32_significand(v, 3) &&     \
	  (__hybrid_uint128_vec32_significand(var, 2) < __hybrid_uint128_vec32_significand(v, 2) ||     \
	   (__hybrid_uint128_vec32_significand(var, 2) == __hybrid_uint128_vec32_significand(v, 2) &&   \
	    (__hybrid_uint128_vec32_significand(var, 1) < __hybrid_uint128_vec32_significand(v, 1) ||   \
	     (__hybrid_uint128_vec32_significand(var, 1) == __hybrid_uint128_vec32_significand(v, 1) && \
	      __hybrid_uint128_vec32_significand(var, 0) <= __hybrid_uint128_vec32_significand(v, 0)))))))
#endif /* !__HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
#ifdef __UINT64_TYPE__
#define __hybrid_uint128_lo64(var, v) (__hybrid_uint128_is64bit(var) && __hybrid_uint128_vec64_significand(var, 0) < (__UINT64_TYPE__)(v))
#define __hybrid_uint128_le64(var, v) (__hybrid_uint128_is64bit(var) && __hybrid_uint128_vec64_significand(var, 0) <= (__UINT64_TYPE__)(v))
#define __hybrid_int128_lo64(var, v)  (__hybrid_int128_is64bit(var) && __hybrid_int128_vec64_significand(var, 0) < (__INT64_TYPE__)(v))
#define __hybrid_int128_le64(var, v)  (__hybrid_int128_is64bit(var) && __hybrid_int128_vec64_significand(var, 0) <= (__INT64_TYPE__)(v))
#endif /* __UINT64_TYPE__ */

#ifdef __INTELLISENSE__
#define __hybrid_int128_eq128(var, v) (__hybrid_int128_vec64_significand(var, 0) == __hybrid_int128_vec64_significand(v, 0))
#define __hybrid_int128_lo128         __hybrid_int128_eq128
#define __hybrid_int128_le128         __hybrid_int128_eq128
#else /* __INTELLISENSE__ */
#define __hybrid_int128_eq128 __hybrid_uint128_eq128
#define __hybrid_int128_lo128(var, v)                                                                               \
	(__hybrid_int128_isneg(var)                                                                                     \
	 ? (__hybrid_int128_isneg(var) ? __hybrid_uint128_lo128(v, var) /* -x < -y  <==> (unsigned)-x > (unsigned)-y */ \
	                               : 1 /* -x < +y --> true */)                                                      \
	 : (__hybrid_int128_isneg(var) ? 0 /* +x < -y --> false */                                                      \
	                               : __hybrid_uint128_lo128(var, v) /* +x < +y  <==> (unsigned)+x < (unsigned)+y */))
#define __hybrid_int128_le128(var, v)                                                                                 \
	(__hybrid_int128_isneg(var)                                                                                       \
	 ? (__hybrid_int128_isneg(var) ? __hybrid_uint128_le128(v, var) /* -x <= -y  <==> (unsigned)-x >= (unsigned)-y */ \
	                               : 1 /* -x <= +y --> true */)                                                       \
	 : (__hybrid_int128_isneg(var) ? 0 /* +x <= -y --> false */                                                       \
	                               : __hybrid_uint128_le128(var, v) /* +x <= +y  <==> (unsigned)+x <= (unsigned)+y */))
#endif /* !__INTELLISENSE__ */

#ifdef __UINT64_TYPE__
#ifdef __NO_builtin_choose_expr
#define __hybrid_uint128_and(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_and8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_and16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_uint128_and32(var, v) : \
	                  __hybrid_uint128_and64(var, v))
#define __hybrid_int128_and(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_and8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_and16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_int128_and32(var, v) : \
	                  __hybrid_int128_and64(var, v))
#define __hybrid_uint128_or(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_or8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_or16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_uint128_or32(var, v) : \
	                  __hybrid_uint128_or64(var, v))
#define __hybrid_int128_or(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_or8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_or16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_int128_or32(var, v) : \
	                  __hybrid_int128_or64(var, v))
#define __hybrid_uint128_xor(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_xor8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_xor16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_uint128_xor32(var, v) : \
	                  __hybrid_uint128_xor64(var, v))
#define __hybrid_int128_xor(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_xor8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_xor16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_int128_xor32(var, v) : \
	                  __hybrid_int128_xor64(var, v))
#define __hybrid_uint128_add(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_add8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_add16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_uint128_add32(var, v) : \
	                  __hybrid_uint128_add64(var, v))
#define __hybrid_int128_add(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_add8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_add16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_int128_add32(var, v) : \
	                  __hybrid_int128_sub64(var, v))
#define __hybrid_uint128_sub(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_sub8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_sub16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_uint128_sub32(var, v) : \
	                  __hybrid_uint128_sub64(var, v))
#define __hybrid_int128_sub(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_sub8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_sub16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_int128_sub32(var, v) : \
	                  __hybrid_int128_sub64(var, v))
#define __hybrid_uint128_mul(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_mul8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_mul16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_uint128_mul32(var, v) : \
	                  __hybrid_uint128_mul64(var, v))
#define __hybrid_int128_mul(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_mul8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_mul16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_int128_mul32(var, v) : \
	                  __hybrid_int128_mul64(var, v))
#define __hybrid_uint128_div(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_div8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_div16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_uint128_div32(var, v) : \
	                  __hybrid_uint128_div64(var, v))
#define __hybrid_int128_div(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_div8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_div16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_int128_div32(var, v) : \
	                  __hybrid_int128_div64(var, v))
#define __hybrid_uint128_mod(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_mod8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_mod16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_uint128_mod32(var, v) : \
	                  __hybrid_uint128_mod64(var, v))
#define __hybrid_int128_mod(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_mod8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_mod16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_int128_mod32(var, v) : \
	                  __hybrid_int128_mod64(var, v))
#define __hybrid_int128_floordiv(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_floordiv8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_floordiv16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_int128_floordiv32(var, v) : \
	                  __hybrid_int128_floordiv64(var, v))
#define __hybrid_int128_floormod(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_floormod8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_floormod16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_int128_floormod32(var, v) : \
	                  __hybrid_int128_floormod64(var, v))
#define __hybrid_uint128_divmod(var, v, divres, modres)                                               \
	(sizeof(modres) == 1 ? __hybrid_uint128_divmod8(var, v, divres, *(__UINT8_TYPE__ *)&(modres)) :   \
	 sizeof(modres) == 2 ? __hybrid_uint128_divmod16(var, v, divres, *(__UINT16_TYPE__ *)&(modres)) : \
	 sizeof(modres) == 4 ? __hybrid_uint128_divmod32(var, v, divres, *(__UINT32_TYPE__ *)&(modres)) : \
	                       __hybrid_uint128_divmod64(var, v, divres, *(__UINT64_TYPE__ *)&(modres)))
#define __hybrid_int128_divmod(var, v, divres, modres)                                              \
	(sizeof(modres) == 1 ? __hybrid_int128_divmod8(var, v, divres, *(__INT8_TYPE__ *)&(modres)) :   \
	 sizeof(modres) == 2 ? __hybrid_int128_divmod16(var, v, divres, *(__INT16_TYPE__ *)&(modres)) : \
	 sizeof(modres) == 4 ? __hybrid_int128_divmod32(var, v, divres, *(__INT32_TYPE__ *)&(modres)) : \
	                       __hybrid_int128_divmod64(var, v, divres, *(__INT64_TYPE__ *)&(modres)))
#define __hybrid_int128_floordivmod(var, v, divres, modres)                                               \
	(sizeof(modres) == 1 ? __hybrid_int128_floordivmod8(var, v, divres, *(__UINT8_TYPE__ *)&(modres)) :   \
	 sizeof(modres) == 2 ? __hybrid_int128_floordivmod16(var, v, divres, *(__UINT16_TYPE__ *)&(modres)) : \
	 sizeof(modres) == 4 ? __hybrid_int128_floordivmod32(var, v, divres, *(__UINT32_TYPE__ *)&(modres)) : \
	                       __hybrid_int128_floordivmod64(var, v, divres, *(__UINT64_TYPE__ *)&(modres)))
#define __hybrid_uint128_eq(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_eq8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_eq16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_uint128_eq32(var, v) : \
	                  __hybrid_uint128_eq64(var, v))
#define __hybrid_int128_eq(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_eq8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_eq16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_int128_eq32(var, v) : \
	                  __hybrid_int128_eq64(var, v))
#define __hybrid_uint128_lo(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_lo8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_lo16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_uint128_lo32(var, v) : \
	                  __hybrid_uint128_lo64(var, v))
#define __hybrid_int128_lo(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_lo8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_lo16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_int128_lo32(var, v) : \
	                  __hybrid_int128_lo64(var, v))
#define __hybrid_uint128_le(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_le8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_le16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_uint128_le32(var, v) : \
	                  __hybrid_uint128_le64(var, v))
#define __hybrid_int128_le(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_le8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_le16(var, v) : \
	 sizeof(v) == 4 ? __hybrid_int128_le32(var, v) : \
	                  __hybrid_int128_le64(var, v))
#else /* __NO_builtin_choose_expr */
#define __hybrid_uint128_and(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_and8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_and16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_and32(var, v), \
	                                      __hybrid_uint128_and64(var, v))))
#define __hybrid_int128_and(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_and8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_and16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_int128_and32(var, v), \
	                                      __hybrid_int128_and64(var, v))))
#define __hybrid_uint128_or(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_or8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_or16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_or32(var, v), \
	                                      __hybrid_uint128_or64(var, v))))
#define __hybrid_int128_or(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_or8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_or16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_int128_or32(var, v), \
	                                      __hybrid_int128_or64(var, v))))
#define __hybrid_uint128_xor(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_xor8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_xor16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_xor32(var, v), \
	                                      __hybrid_uint128_xor64(var, v))))
#define __hybrid_int128_xor(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_xor8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_xor16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_int128_xor32(var, v), \
	                                      __hybrid_int128_xor64(var, v))))
#define __hybrid_uint128_add(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_add8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_add16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_add32(var, v), \
	                                      __hybrid_uint128_add64(var, v))))
#define __hybrid_int128_add(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_add8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_add16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_int128_add32(var, v), \
	                                      __hybrid_int128_add64(var, v))))
#define __hybrid_uint128_sub(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_sub8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_sub16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_sub32(var, v), \
	                                      __hybrid_uint128_sub64(var, v))))
#define __hybrid_int128_sub(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_sub8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_sub16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_int128_sub32(var, v), \
	                                      __hybrid_int128_sub64(var, v))))
#define __hybrid_uint128_mul(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_mul8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_mul16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_mul32(var, v), \
	                                      __hybrid_uint128_mul64(var, v))))
#define __hybrid_int128_mul(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_mul8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_mul16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_int128_mul32(var, v), \
	                                      __hybrid_int128_mul64(var, v))))
#define __hybrid_uint128_div(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_div8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_div16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_div32(var, v), \
	                                      __hybrid_uint128_div64(var, v))))
#define __hybrid_int128_div(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_div8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_div16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_int128_div32(var, v), \
	                                      __hybrid_int128_div64(var, v))))
#define __hybrid_uint128_mod(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_mod8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_mod16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_mod32(var, v), \
	                                      __hybrid_uint128_mod64(var, v))))
#define __hybrid_int128_mod(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_mod8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_mod16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_int128_mod32(var, v), \
	                                      __hybrid_int128_mod64(var, v))))
#define __hybrid_int128_floordiv(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_floordiv8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_floordiv16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_int128_floordiv32(var, v), \
	                                      __hybrid_int128_floordiv64(var, v))))
#define __hybrid_int128_floormod(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_floormod8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_floormod16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_int128_floormod32(var, v), \
	                                      __hybrid_int128_floormod64(var, v))))
#define __hybrid_uint128_divmod(var, v, divres, modres)                                                                  \
	__builtin_choose_expr(sizeof(modres) == 1, __hybrid_uint128_divmod8(var, v, divres, *(__UINT8_TYPE__ *)&(modres)),   \
	__builtin_choose_expr(sizeof(modres) == 2, __hybrid_uint128_divmod16(var, v, divres, *(__UINT16_TYPE__ *)&(modres)), \
	__builtin_choose_expr(sizeof(modres) == 4, __hybrid_uint128_divmod32(var, v, divres, *(__UINT32_TYPE__ *)&(modres)), \
	                                           __hybrid_uint128_divmod64(var, v, divres, *(__UINT64_TYPE__ *)&(modres)))))
#define __hybrid_int128_divmod(var, v, divres, modres)                                                                 \
	__builtin_choose_expr(sizeof(modres) == 1, __hybrid_int128_divmod8(var, v, divres, *(__INT8_TYPE__ *)&(modres)),   \
	__builtin_choose_expr(sizeof(modres) == 2, __hybrid_int128_divmod16(var, v, divres, *(__INT16_TYPE__ *)&(modres)), \
	__builtin_choose_expr(sizeof(modres) == 4, __hybrid_int128_divmod32(var, v, divres, *(__INT32_TYPE__ *)&(modres)), \
	                                           __hybrid_int128_divmod64(var, v, divres, *(__INT64_TYPE__ *)&(modres)))))
#define __hybrid_int128_floordivmod(var, v, divres, modres)                                                                  \
	__builtin_choose_expr(sizeof(modres) == 1, __hybrid_int128_floordivmod8(var, v, divres, *(__UINT8_TYPE__ *)&(modres)),   \
	__builtin_choose_expr(sizeof(modres) == 2, __hybrid_int128_floordivmod16(var, v, divres, *(__UINT16_TYPE__ *)&(modres)), \
	__builtin_choose_expr(sizeof(modres) == 4, __hybrid_int128_floordivmod32(var, v, divres, *(__UINT32_TYPE__ *)&(modres)), \
	                                           __hybrid_int128_floordivmod64(var, v, divres, *(__UINT64_TYPE__ *)&(modres)))))
#define __hybrid_uint128_eq(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_eq8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_eq16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_eq32(var, v), \
	                                      __hybrid_uint128_eq64(var, v))))
#define __hybrid_int128_eq(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_eq8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_eq16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_int128_eq32(var, v), \
	                                      __hybrid_int128_eq64(var, v))))
#define __hybrid_uint128_lo(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_lo8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_lo16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_lo32(var, v), \
	                                      __hybrid_uint128_lo64(var, v))))
#define __hybrid_int128_lo(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_lo8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_lo16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_int128_lo32(var, v), \
	                                      __hybrid_int128_lo64(var, v))))
#define __hybrid_uint128_le(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_le8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_le16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_le32(var, v), \
	                                      __hybrid_uint128_le64(var, v))))
#define __hybrid_int128_le(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_le8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_le16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_int128_le32(var, v), \
	                                      __hybrid_int128_le64(var, v))))
#endif /* !__NO_builtin_choose_expr */
#else /* __UINT64_TYPE__ */
#ifdef __NO_builtin_choose_expr
#define __hybrid_uint128_and(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_and8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_and16(var, v) : \
	                  __hybrid_uint128_and32(var, v))
#define __hybrid_int128_and(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_and8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_and16(var, v) : \
	                  __hybrid_int128_and32(var, v))
#define __hybrid_uint128_or(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_or8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_or16(var, v) : \
	                  __hybrid_uint128_or32(var, v))
#define __hybrid_int128_or(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_or8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_or16(var, v) : \
	                  __hybrid_int128_or32(var, v))
#define __hybrid_uint128_xor(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_xor8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_xor16(var, v) : \
	                  __hybrid_uint128_xor32(var, v))
#define __hybrid_int128_xor(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_xor8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_xor16(var, v) : \
	                  __hybrid_int128_xor32(var, v))
#define __hybrid_uint128_add(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_add8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_add16(var, v) : \
	                  __hybrid_uint128_add32(var, v))
#define __hybrid_int128_add(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_add8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_add16(var, v) : \
	                  __hybrid_int128_add32(var, v))
#define __hybrid_uint128_sub(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_sub8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_sub16(var, v) : \
	                  __hybrid_uint128_sub32(var, v))
#define __hybrid_int128_sub(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_sub8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_sub16(var, v) : \
	                  __hybrid_int128_sub32(var, v))
#define __hybrid_uint128_mul(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_mul8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_mul16(var, v) : \
	                  __hybrid_uint128_mul32(var, v))
#define __hybrid_int128_mul(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_mul8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_mul16(var, v) : \
	                  __hybrid_int128_mul32(var, v))
#define __hybrid_uint128_div(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_div8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_div16(var, v) : \
	                  __hybrid_uint128_div32(var, v))
#define __hybrid_int128_div(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_div8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_div16(var, v) : \
	                  __hybrid_int128_div32(var, v))
#define __hybrid_uint128_mod(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_mod8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_mod16(var, v) : \
	                  __hybrid_uint128_mod32(var, v))
#define __hybrid_int128_mod(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_mod8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_mod16(var, v) : \
	                  __hybrid_int128_mod32(var, v))
#define __hybrid_int128_floordiv(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_floordiv8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_floordiv16(var, v) : \
	                  __hybrid_int128_floordiv32(var, v))
#define __hybrid_int128_floormod(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_floormod8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_floormod16(var, v) : \
	                  __hybrid_int128_floormod32(var, v))
#define __hybrid_uint128_divmod(var, v, divres, modres)                                               \
	(sizeof(modres) == 1 ? __hybrid_uint128_divmod8(var, v, divres, *(__UINT8_TYPE__ *)&(modres)) :   \
	 sizeof(modres) == 2 ? __hybrid_uint128_divmod16(var, v, divres, *(__UINT16_TYPE__ *)&(modres)) : \
	                       __hybrid_uint128_divmod32(var, v, divres, *(__UINT32_TYPE__ *)&(modres)))
#define __hybrid_int128_divmod(var, v, divres, modres)                                              \
	(sizeof(modres) == 1 ? __hybrid_int128_divmod8(var, v, divres, *(__INT8_TYPE__ *)&(modres)) :   \
	 sizeof(modres) == 2 ? __hybrid_int128_divmod16(var, v, divres, *(__INT16_TYPE__ *)&(modres)) : \
	                       __hybrid_int128_divmod32(var, v, divres, *(__INT32_TYPE__ *)&(modres)))
#define __hybrid_int128_floordivmod(var, v, divres, modres)                                               \
	(sizeof(modres) == 1 ? __hybrid_int128_floordivmod8(var, v, divres, *(__UINT8_TYPE__ *)&(modres)) :   \
	 sizeof(modres) == 2 ? __hybrid_int128_floordivmod16(var, v, divres, *(__UINT16_TYPE__ *)&(modres)) : \
	                       __hybrid_int128_floordivmod32(var, v, divres, *(__UINT32_TYPE__ *)&(modres)))
#define __hybrid_uint128_eq(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_eq8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_eq16(var, v) : \
	                  __hybrid_uint128_eq32(var, v))
#define __hybrid_int128_eq(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_eq8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_eq16(var, v) : \
	                  __hybrid_int128_eq32(var, v))
#define __hybrid_uint128_lo(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_lo8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_lo16(var, v) : \
	                  __hybrid_uint128_lo32(var, v))
#define __hybrid_int128_lo(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_lo8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_lo16(var, v) : \
	                  __hybrid_int128_lo32(var, v))
#define __hybrid_uint128_le(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_le8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_le16(var, v) : \
	                  __hybrid_uint128_le32(var, v))
#define __hybrid_int128_le(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_le8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_le16(var, v) : \
	                  __hybrid_int128_le32(var, v))
#else /* __NO_builtin_choose_expr */
#define __hybrid_uint128_and(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_and8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_and16(var, v), \
	                                      __hybrid_uint128_and32(var, v)))
#define __hybrid_int128_and(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_and8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_and16(var, v), \
	                                      __hybrid_int128_and32(var, v)))
#define __hybrid_uint128_or(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_or8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_or16(var, v), \
	                                      __hybrid_uint128_or32(var, v)))
#define __hybrid_int128_or(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_or8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_or16(var, v), \
	                                      __hybrid_int128_or32(var, v)))
#define __hybrid_uint128_xor(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_xor8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_xor16(var, v), \
	                                      __hybrid_uint128_xor32(var, v)))
#define __hybrid_int128_xor(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_xor8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_xor16(var, v), \
	                                      __hybrid_int128_xor32(var, v)))
#define __hybrid_uint128_add(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_add8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_add16(var, v), \
	                                      __hybrid_uint128_add32(var, v)))
#define __hybrid_int128_add(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_add8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_add16(var, v), \
	                                      __hybrid_int128_add32(var, v)))
#define __hybrid_uint128_sub(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_sub8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_sub16(var, v), \
	                                      __hybrid_uint128_sub32(var, v)))
#define __hybrid_int128_sub(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_sub8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_sub16(var, v), \
	                                      __hybrid_int128_sub32(var, v)))
#define __hybrid_uint128_mul(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_mul8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_mul16(var, v), \
	                                      __hybrid_uint128_mul32(var, v)))
#define __hybrid_int128_mul(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_mul8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_mul16(var, v), \
	                                      __hybrid_int128_mul32(var, v)))
#define __hybrid_uint128_div(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_div8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_div16(var, v), \
	                                      __hybrid_uint128_div32(var, v)))
#define __hybrid_int128_div(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_div8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_div16(var, v), \
	                                      __hybrid_int128_div32(var, v)))
#define __hybrid_uint128_mod(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_mod8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_mod16(var, v), \
	                                      __hybrid_uint128_mod32(var, v)))
#define __hybrid_int128_mod(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_mod8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_mod16(var, v), \
	                                      __hybrid_int128_mod32(var, v)))
#define __hybrid_int128_floordiv(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_floordiv8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_floordiv16(var, v), \
	                                      __hybrid_int128_floordiv32(var, v)))
#define __hybrid_int128_floormod(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_floormod8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_floormod16(var, v), \
	                                      __hybrid_int128_floormod32(var, v)))
#define __hybrid_uint128_divmod(var, v, divres, modres)                                                                  \
	__builtin_choose_expr(sizeof(modres) == 1, __hybrid_uint128_divmod8(var, v, divres, *(__UINT8_TYPE__ *)&(modres)),   \
	__builtin_choose_expr(sizeof(modres) == 2, __hybrid_uint128_divmod16(var, v, divres, *(__UINT16_TYPE__ *)&(modres)), \
	                                           __hybrid_uint128_divmod32(var, v, divres, *(__UINT32_TYPE__ *)&(modres))))
#define __hybrid_int128_divmod(var, v, divres, modres)                                                                 \
	__builtin_choose_expr(sizeof(modres) == 1, __hybrid_int128_divmod8(var, v, divres, *(__INT8_TYPE__ *)&(modres)),   \
	__builtin_choose_expr(sizeof(modres) == 2, __hybrid_int128_divmod16(var, v, divres, *(__INT16_TYPE__ *)&(modres)), \
	                                           __hybrid_int128_divmod32(var, v, divres, *(__INT32_TYPE__ *)&(modres))))
#define __hybrid_int128_floordivmod(var, v, divres, modres)                                                                  \
	__builtin_choose_expr(sizeof(modres) == 1, __hybrid_int128_floordivmod8(var, v, divres, *(__UINT8_TYPE__ *)&(modres)),   \
	__builtin_choose_expr(sizeof(modres) == 2, __hybrid_int128_floordivmod16(var, v, divres, *(__UINT16_TYPE__ *)&(modres)), \
	                                           __hybrid_int128_floordivmod32(var, v, divres, *(__UINT32_TYPE__ *)&(modres))))
#define __hybrid_uint128_eq(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_eq8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_eq16(var, v), \
	                                      __hybrid_uint128_eq32(var, v)))
#define __hybrid_int128_eq(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_eq8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_eq16(var, v), \
	                                      __hybrid_int128_eq32(var, v)))
#define __hybrid_uint128_lo(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_lo8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_lo16(var, v), \
	                                      __hybrid_uint128_lo32(var, v)))
#define __hybrid_int128_lo(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_lo8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_lo16(var, v), \
	                                      __hybrid_int128_lo32(var, v)))
#define __hybrid_uint128_le(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_le8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_le16(var, v), \
	                                      __hybrid_uint128_le32(var, v)))
#define __hybrid_int128_le(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_int128_le8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_int128_le16(var, v), \
	                                      __hybrid_int128_le32(var, v)))
#endif /* !__NO_builtin_choose_expr */
#endif /* !__UINT64_TYPE__ */

#define __HYBRID_PRIVATE_INT128_AS1  __hybrid_int128_get8
#define __HYBRID_PRIVATE_INT128_AS2  __hybrid_int128_get16
#define __HYBRID_PRIVATE_INT128_AS4  __hybrid_int128_get32
#define __HYBRID_PRIVATE_UINT128_AS1 __hybrid_uint128_get8
#define __HYBRID_PRIVATE_UINT128_AS2 __hybrid_uint128_get16
#define __HYBRID_PRIVATE_UINT128_AS4 __hybrid_uint128_get32
#ifdef __UINT64_TYPE__
#define __HYBRID_PRIVATE_INT128_AS8  __hybrid_int128_get64
#define __HYBRID_PRIVATE_UINT128_AS8 __hybrid_uint128_get64
#endif /* __UINT64_TYPE__ */
#define __HYBRID_PRIVATE_INT128_AS(sizeof) __HYBRID_PRIVATE_INT128_AS##sizeof
#define __HYBRID_PRIVATE_UINT128_AS(sizeof) __HYBRID_PRIVATE_UINT128_AS##sizeof
#define __hybrid_int128_as(var, sizeof) __HYBRID_PRIVATE_INT128_AS(sizeof)(var)
#define __hybrid_uint128_as(var, sizeof) __HYBRID_PRIVATE_UINT128_AS(sizeof)(var)

#include "__assert.h"

__DECL_BEGIN

#if defined(__cplusplus) && defined(WANT_INT128_CXX_INTEGRATION)
extern "C++" {
__NAMESPACE_INT_BEGIN
template<class __T> struct __hybrid_int128_issigned { enum { __val = false }; };
template<class __T> struct __hybrid_int128_isunsigned { enum { __val = false }; };
#ifdef __CHAR_UNSIGNED__
template<> struct __hybrid_int128_isunsigned<char> { enum { __val = true }; };
#else /* __CHAR_UNSIGNED__ */
template<> struct __hybrid_int128_issigned<char> { enum { __val = true }; };
#endif /* !__CHAR_UNSIGNED__ */
template<> struct __hybrid_int128_issigned<signed char> { enum { __val = true }; };
template<> struct __hybrid_int128_isunsigned<unsigned char> { enum { __val = true }; };
template<> struct __hybrid_int128_issigned<short> { enum { __val = true }; };
template<> struct __hybrid_int128_isunsigned<unsigned short> { enum { __val = true }; };
template<> struct __hybrid_int128_issigned<int> { enum { __val = true }; };
template<> struct __hybrid_int128_isunsigned<unsigned int> { enum { __val = true }; };
template<> struct __hybrid_int128_issigned<long> { enum { __val = true }; };
template<> struct __hybrid_int128_isunsigned<unsigned long> { enum { __val = true }; };
#ifdef __COMPILER_HAVE_LONGLONG
template<> struct __hybrid_int128_issigned<__LONGLONG> { enum { __val = true }; };
template<> struct __hybrid_int128_isunsigned<__ULONGLONG> { enum { __val = true }; };
#endif /* __COMPILER_HAVE_LONGLONG */
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
template<> struct __hybrid_int128_issigned<__int8> { enum { __val = true }; };
template<> struct __hybrid_int128_isunsigned<unsigned __int8> { enum { __val = true }; };
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
template<> struct __hybrid_int128_issigned<__int16> { enum { __val = true }; };
template<> struct __hybrid_int128_isunsigned<unsigned __int16> { enum { __val = true }; };
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
template<> struct __hybrid_int128_issigned<__int32> { enum { __val = true }; };
template<> struct __hybrid_int128_isunsigned<unsigned __int32> { enum { __val = true }; };
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
template<> struct __hybrid_int128_issigned<__int64> { enum { __val = true }; };
template<> struct __hybrid_int128_isunsigned<unsigned __int64> { enum { __val = true }; };
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */
template<bool __V, class __T> struct __hybrid_int128_enableif { typedef __T __type; };
template<class __T> struct __hybrid_int128_enableif<false, __T> {};
__NAMESPACE_INT_END
#define __HYBRID_INT128_ENABLE_IF_SIGNED(ArithType, Type)   __CXX_DEDUCE_TYPENAME ::__intern::__hybrid_int128_enableif< ::__intern::__hybrid_int128_issigned<ArithType>::__val, Type>::__type
#define __HYBRID_INT128_ENABLE_IF_UNSIGNED(ArithType, Type) __CXX_DEDUCE_TYPENAME ::__intern::__hybrid_int128_enableif< ::__intern::__hybrid_int128_isunsigned<ArithType>::__val, Type>::__type
union __hybrid_uint128_struct;
#endif /* __cplusplus && WANT_INT128_CXX_INTEGRATION */

typedef union __hybrid_int128_struct {
#ifdef __INTELLISENSE__
	__INT8_TYPE__ __s128_8[16];
	__INT16_TYPE__ __s128_16[16];
	__INT32_TYPE__ __s128_32[16];
#ifdef __INT64_TYPE__
	__INT64_TYPE__ __s128_64[16];
#endif /* __INT64_TYPE__ */
#endif /* __INTELLISENSE__ */
	__UINT8_TYPE__  __i128_u8[16];
	__UINT16_TYPE__ __i128_u16[8];
	__UINT32_TYPE__ __i128_u32[4];
	__INT8_TYPE__   __i128_s8[16];
	__INT16_TYPE__  __i128_s16[8];
	__INT32_TYPE__  __i128_s32[4];
#ifdef __UINT64_TYPE__
	__UINT64_TYPE__ __i128_u64[2];
	__INT64_TYPE__  __i128_s64[2];
#endif /* __UINT64_TYPE__ */
#if defined(__cplusplus) && defined(WANT_INT128_CXX_INTEGRATION)
	__CXX_CLASSMEMBER __CXX_DEFAULT_DTOR_NOEXCEPT(__hybrid_int128_struct);
	__CXX_CLASSMEMBER __CXX_DEFAULT_CTOR_NOEXCEPT(__hybrid_int128_struct);
	__CXX_DEFAULT_COPY_CTOR_AND_ASSIGN_NOEXCEPT(__CXX_CLASSMEMBER, __hybrid_int128_struct, __v, {
		__i128_s32[0] = __v.__i128_s32[0];
		__i128_s32[1] = __v.__i128_s32[1];
		__i128_s32[2] = __v.__i128_s32[2];
		__i128_s32[3] = __v.__i128_s32[3];
	});
	__CXX_CLASSMEMBER explicit __hybrid_int128_struct(__hybrid_uint128_struct const &__v) __CXX_NOEXCEPT;
	__CXX_CLASSMEMBER __hybrid_int128_struct &operator=(__hybrid_uint128_struct const &__v) __CXX_NOEXCEPT;
	template<class __ValType> __CXX_CLASSMEMBER explicit __hybrid_int128_struct(__ValType __v, __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, int *) = 0) __CXX_NOEXCEPT { __hybrid_int128_set(*this, __v); }
	template<class __ValType> __CXX_CLASSMEMBER explicit __hybrid_int128_struct(__ValType __v, __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, int *) = 0) __CXX_NOEXCEPT { __hybrid_uint128_set(*this, __v); }
	template<class __ValType> __CXX_CLASSMEMBER __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, __hybrid_int128_struct &) operator=(__ValType __v) __CXX_NOEXCEPT { __hybrid_int128_set(*this, __v); return *this; }
	template<class __ValType> __CXX_CLASSMEMBER __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, __hybrid_int128_struct &) operator=(__ValType __v) __CXX_NOEXCEPT { __hybrid_uint128_set(*this, __v); return *this; }
	__CXX_CLASSMEMBER explicit operator bool() const __CXX_NOEXCEPT { return !__hybrid_int128_iszero(*this); }
	__CXX_CLASSMEMBER explicit operator char() const __CXX_NOEXCEPT { return (char)__hybrid_int128_as(*this, __SIZEOF_CHAR__); }
	__CXX_CLASSMEMBER explicit operator signed char() const __CXX_NOEXCEPT { return __hybrid_int128_as(*this, __SIZEOF_CHAR__); }
	__CXX_CLASSMEMBER explicit operator unsigned char() const __CXX_NOEXCEPT { return (unsigned char)__hybrid_int128_as(*this, __SIZEOF_CHAR__); }
	__CXX_CLASSMEMBER explicit operator short() const __CXX_NOEXCEPT { return __hybrid_int128_as(*this, __SIZEOF_SHORT__); }
	__CXX_CLASSMEMBER explicit operator unsigned short() const __CXX_NOEXCEPT { return (unsigned short)__hybrid_int128_as(*this, __SIZEOF_SHORT__); }
	__CXX_CLASSMEMBER explicit operator int() const __CXX_NOEXCEPT { return __hybrid_int128_as(*this, __SIZEOF_INT__); }
	__CXX_CLASSMEMBER explicit operator unsigned int() const __CXX_NOEXCEPT { return (unsigned short)__hybrid_int128_as(*this, __SIZEOF_INT__); }
	__CXX_CLASSMEMBER explicit operator long() const __CXX_NOEXCEPT { return __hybrid_int128_as(*this, __SIZEOF_LONG__); }
	__CXX_CLASSMEMBER explicit operator unsigned long() const __CXX_NOEXCEPT { return (unsigned long)__hybrid_int128_as(*this, __SIZEOF_LONG__); }
#ifdef __COMPILER_HAVE_LONGLONG
	__CXX_CLASSMEMBER explicit operator __LONGLONG() const __CXX_NOEXCEPT { return __hybrid_int128_as(*this, __SIZEOF_LONG_LONG__); }
	__CXX_CLASSMEMBER explicit operator __ULONGLONG() const __CXX_NOEXCEPT { return (__ULONGLONG)__hybrid_int128_as(*this, __SIZEOF_LONG_LONG__); }
#endif /* __COMPILER_HAVE_LONGLONG */
	__CXX_CLASSMEMBER bool operator!() const __CXX_NOEXCEPT { return __hybrid_int128_iszero(*this); }
#endif /* __cplusplus && WANT_INT128_CXX_INTEGRATION */
} __hybrid_int128_t;
#define __hybrid_int128_t  __hybrid_int128_t

typedef union __hybrid_uint128_struct {
#ifdef __INTELLISENSE__
	__UINT8_TYPE__ __u128_8[16];
	__UINT16_TYPE__ __u128_16[16];
	__UINT32_TYPE__ __u128_32[16];
#ifdef __INT64_TYPE__
	__UINT64_TYPE__ __u128_64[16];
#endif /* __INT64_TYPE__ */
#endif /* __INTELLISENSE__ */
	__UINT8_TYPE__  __i128_u8[16];
	__UINT16_TYPE__ __i128_u16[8];
	__UINT32_TYPE__ __i128_u32[4];
	__INT8_TYPE__   __i128_s8[16];
	__INT16_TYPE__  __i128_s16[8];
	__INT32_TYPE__  __i128_s32[4];
#ifdef __UINT64_TYPE__
	__UINT64_TYPE__ __i128_u64[2];
	__INT64_TYPE__  __i128_s64[2];
#endif /* __UINT64_TYPE__ */
#if defined(__cplusplus) && defined(WANT_INT128_CXX_INTEGRATION)
	__CXX_CLASSMEMBER __CXX_DEFAULT_DTOR_NOEXCEPT(__hybrid_uint128_struct);
	__CXX_CLASSMEMBER __CXX_DEFAULT_CTOR_NOEXCEPT(__hybrid_uint128_struct);
	__CXX_DEFAULT_COPY_CTOR_AND_ASSIGN_NOEXCEPT(__CXX_CLASSMEMBER, __hybrid_uint128_struct, __v, {
		__i128_u32[0] = __v.__i128_u32[0];
		__i128_u32[1] = __v.__i128_u32[1];
		__i128_u32[2] = __v.__i128_u32[2];
		__i128_u32[3] = __v.__i128_u32[3];
	});
	__CXX_CLASSMEMBER explicit __hybrid_uint128_struct(__hybrid_int128_struct const &__v) __CXX_NOEXCEPT;
	__CXX_CLASSMEMBER __hybrid_uint128_struct &operator=(__hybrid_int128_struct const &__v) __CXX_NOEXCEPT;
	template<class __ValType> __CXX_CLASSMEMBER explicit __hybrid_uint128_struct(__ValType __v, __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, int *) = 0) __CXX_NOEXCEPT { __hybrid_int128_set(*this, __v); }
	template<class __ValType> __CXX_CLASSMEMBER explicit __hybrid_uint128_struct(__ValType __v, __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, int *) = 0) __CXX_NOEXCEPT { __hybrid_uint128_set(*this, __v); }
	template<class __ValType> __CXX_CLASSMEMBER __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, __hybrid_uint128_struct &) operator=(__ValType __v) __CXX_NOEXCEPT { __hybrid_int128_set(*this, __v); return *this; }
	template<class __ValType> __CXX_CLASSMEMBER __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, __hybrid_uint128_struct &) operator=(__ValType __v) __CXX_NOEXCEPT { __hybrid_uint128_set(*this, __v); return *this; }
	__CXX_CLASSMEMBER explicit operator bool() const __CXX_NOEXCEPT { return !__hybrid_uint128_iszero(*this); }
	__CXX_CLASSMEMBER explicit operator char() const __CXX_NOEXCEPT { return (char)__hybrid_uint128_as(*this, __SIZEOF_CHAR__); }
	__CXX_CLASSMEMBER explicit operator signed char() const __CXX_NOEXCEPT { return (signed char)__hybrid_uint128_as(*this, __SIZEOF_CHAR__); }
	__CXX_CLASSMEMBER explicit operator unsigned char() const __CXX_NOEXCEPT { return __hybrid_uint128_as(*this, __SIZEOF_CHAR__); }
	__CXX_CLASSMEMBER explicit operator short() const __CXX_NOEXCEPT { return (short)__hybrid_uint128_as(*this, __SIZEOF_SHORT__); }
	__CXX_CLASSMEMBER explicit operator unsigned short() const __CXX_NOEXCEPT { return __hybrid_uint128_as(*this, __SIZEOF_SHORT__); }
	__CXX_CLASSMEMBER explicit operator int() const __CXX_NOEXCEPT { return (short)__hybrid_uint128_as(*this, __SIZEOF_INT__); }
	__CXX_CLASSMEMBER explicit operator unsigned int() const __CXX_NOEXCEPT { return __hybrid_uint128_as(*this, __SIZEOF_INT__); }
	__CXX_CLASSMEMBER explicit operator long() const __CXX_NOEXCEPT { return (long)__hybrid_uint128_as(*this, __SIZEOF_LONG__); }
	__CXX_CLASSMEMBER explicit operator unsigned long() const __CXX_NOEXCEPT { return __hybrid_uint128_as(*this, __SIZEOF_LONG__); }
#ifdef __COMPILER_HAVE_LONGLONG
	__CXX_CLASSMEMBER explicit operator __LONGLONG() const __CXX_NOEXCEPT { return (__LONGLONG)__hybrid_uint128_as(*this, __SIZEOF_LONG_LONG__); }
	__CXX_CLASSMEMBER explicit operator __ULONGLONG() const __CXX_NOEXCEPT { return __hybrid_uint128_as(*this, __SIZEOF_LONG_LONG__); }
#endif /* __COMPILER_HAVE_LONGLONG */
	__CXX_CLASSMEMBER bool operator!() const __CXX_NOEXCEPT { return __hybrid_uint128_iszero(*this); }
#endif /* defined(__cplusplus) && WANT_INT128_CXX_INTEGRATION */
} __hybrid_uint128_t;
#define __hybrid_uint128_t __hybrid_uint128_t

#if defined(__cplusplus) && defined(WANT_INT128_CXX_INTEGRATION)
} /* extern "C++" */
#endif /* __cplusplus && WANT_INT128_CXX_INTEGRATION */

#ifdef __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
#define __HYBRID_PRIVATE_UINT128_BIT128(v, i) (((v).__i128_u64[(i) / 64] >> ((i) % 64)) & 1)
#else /* __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
#define __HYBRID_PRIVATE_UINT128_BIT128(v, i) (((v).__i128_u32[(i) / 32] >> ((i) % 32)) & 1)
#endif /* !__HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */

__LOCAL __ATTR_INOUT(1) __ATTR_IN(2) void
(__hybrid_uint128_add128_neg)(__hybrid_uint128_t *__var, __hybrid_int128_t const *__v) {
	__hybrid_int128_t __negv;
	__hybrid_int128_copy(__negv, *__v);
	__hybrid_int128_neg(__negv);
	__hybrid_uint128_add128(*__var, __hybrid_int128_asunsigned(__negv));
}

__LOCAL __ATTR_INOUT(1) __ATTR_IN(2) void
(__hybrid_uint128_sub128_neg)(__hybrid_uint128_t *__var, __hybrid_int128_t const *__v) {
	__hybrid_int128_t __negv;
	__hybrid_int128_copy(__negv, *__v);
	__hybrid_int128_neg(__negv);
	__hybrid_uint128_sub128(*__var, __hybrid_int128_asunsigned(__negv));
}

__LOCAL __ATTR_INOUT(1) __ATTR_IN(2) void
(__hybrid_uint128_mul128_impl)(__hybrid_uint128_t *__lhs, __hybrid_uint128_t const *__rhs) {
	unsigned int __u128_i;
	__hybrid_uint128_t __u128_mulres, __u128_tmp;
	__hybrid_uint128_setzero(__u128_mulres);
	for (__u128_i = 0; __u128_i < 128; ++__u128_i) {
		if (__HYBRID_PRIVATE_UINT128_BIT128(*__rhs, __u128_i)) {
			__u128_tmp = *__lhs;
			__hybrid_uint128_shl(__u128_tmp, __u128_i);
			__hybrid_uint128_add128(__u128_mulres, __u128_tmp);
		}
	}
	*__lhs = __u128_mulres;
}

__LOCAL __ATTR_INOUT(1) void
(__hybrid_uint128_mul32_impl)(__hybrid_uint128_t *__lhs, __UINT32_TYPE__ __rhs) {
	unsigned int __u128_i;
	__hybrid_uint128_t __u128_mulres, __u128_tmp;
	__hybrid_uint128_setzero(__u128_mulres);
	for (__u128_i = 0; __u128_i < 32; ++__u128_i) {
		if (((__rhs >> __u128_i) & 1) != 0) {
			__u128_tmp = *__lhs;
			__hybrid_uint128_shl32(__u128_tmp, __u128_i);
			__hybrid_uint128_add128(__u128_mulres, __u128_tmp);
		}
	}
	*__lhs = __u128_mulres;
}


#ifdef __UINT64_TYPE__
__LOCAL __ATTR_INOUT(1) void
(__hybrid_uint128_mul64_impl)(__hybrid_uint128_t *__lhs, __UINT64_TYPE__ __rhs) {
	unsigned int __u128_i;
	__hybrid_uint128_t __u128_mulres, __u128_tmp;
	__hybrid_uint128_setzero(__u128_mulres);
	for (__u128_i = 0; __u128_i < 64; ++__u128_i) {
		if (((__rhs >> __u128_i) & 1) != 0) {
			__u128_tmp = *__lhs;
			__hybrid_uint128_shl64(__u128_tmp, __u128_i);
			__hybrid_uint128_add128(__u128_mulres, __u128_tmp);
		}
	}
	*__lhs = __u128_mulres;
}
#endif /* __UINT64_TYPE__ */

__LOCAL __ATTR_INOUT(1) __ATTR_IN(2) void
(__hybrid_int128_mul128_impl)(__hybrid_int128_t *__lhs, __hybrid_int128_t const *__rhs) {
	__BOOL __u128_neg = 0;
	__hybrid_int128_t __u128_a, __u128_b;
	__hybrid_int128_copy(__u128_a, *__lhs);
	__hybrid_int128_copy(__u128_b, *__rhs);
	if (__hybrid_int128_isneg(__u128_a)) {
		__hybrid_int128_neg(__u128_a);
		__u128_neg = !__u128_neg;
	}
	if (__hybrid_int128_isneg(__u128_b)) {
		__hybrid_int128_neg(__u128_b);
		__u128_neg = !__u128_neg;
	}
	__hybrid_uint128_mul128_impl((__hybrid_uint128_t *)&__u128_a,
	                             (__hybrid_uint128_t const *)&__u128_b);
	if (__u128_neg)
		__hybrid_int128_neg(__u128_a);
	__hybrid_int128_copy(*__lhs, __u128_a);
}

__LOCAL __ATTR_INOUT(1) void
(__hybrid_int128_mul32_impl)(__hybrid_int128_t *__lhs, __INT32_TYPE__ __rhs) {
	__BOOL __u128_neg = 0;
	__hybrid_int128_t __u128_a;
	__hybrid_int128_copy(__u128_a, *__lhs);
	if (__hybrid_int128_isneg(__u128_a)) {
		__hybrid_int128_neg(__u128_a);
		__u128_neg = !__u128_neg;
	}
	if (__rhs < 0) {
		__rhs = -__rhs;
		__u128_neg = !__u128_neg;
	}
	__hybrid_uint128_mul32_impl((__hybrid_uint128_t *)&__u128_a, (__UINT32_TYPE__)__rhs);
	if (__u128_neg)
		__hybrid_int128_neg(__u128_a);
	__hybrid_int128_copy(*__lhs, __u128_a);
}


#ifdef __UINT64_TYPE__
__LOCAL __ATTR_INOUT(1) void
(__hybrid_int128_mul64_impl)(__hybrid_int128_t *__lhs, __INT64_TYPE__ __rhs) {
	__BOOL __u128_neg = 0;
	__hybrid_int128_t __u128_a;
	__hybrid_int128_copy(__u128_a, *__lhs);
	if (__hybrid_int128_isneg(__u128_a)) {
		__hybrid_int128_neg(__u128_a);
		__u128_neg = !__u128_neg;
	}
	if (__rhs < 0) {
		__rhs = -__rhs;
		__u128_neg = !__u128_neg;
	}
	__hybrid_uint128_mul64_impl((__hybrid_uint128_t *)&__u128_a, (__UINT64_TYPE__)__rhs);
	if (__u128_neg)
		__hybrid_int128_neg(__u128_a);
	__lhs->__i128_u64[0] = __u128_a.__i128_u64[0];
	__lhs->__i128_u64[1] = __u128_a.__i128_u64[1];
}
#endif /* __UINT64_TYPE__ */





__LOCAL __ATTR_IN(1) __ATTR_IN(2) __ATTR_OUT_OPT(3) __ATTR_OUT_OPT(4) void
(__hybrid_PRIVATE_uint128_divmod128)(__hybrid_uint128_t const *__lhs, __hybrid_uint128_t const *__rhs,
                                     __hybrid_uint128_t *__res_div, __hybrid_uint128_t *__res_mod) {
	/* Derived from:
	 * https://stackoverflow.com/questions/5284898/implement-division-with-bit-wise-operator/9345822#9345822 */
	unsigned int __u128_i;
	__hybrid_uint128_t __u128_a, __u128_b;
	__hybrid_uint128_t __u128_res, __u128_mask;
	__u128_a = *__lhs;
	__u128_b = *__rhs;
	for (__u128_i = 128;;) {
		__hybrid_assertf(__u128_i != 0, "Divide by ZERO");
		--__u128_i;
		if (__HYBRID_PRIVATE_UINT128_BIT128(__u128_b, __u128_i)) {
			__u128_i = 127 - __u128_i;
			break;
		}
	}
	__hybrid_uint128_setzero(__u128_res);
	__hybrid_uint128_shl(__u128_b, __u128_i);
	__hybrid_uint128_setone(__u128_mask);
	__hybrid_uint128_shl(__u128_mask, __u128_i);
	for (;;) {
		if (__hybrid_uint128_le128(__u128_b, __u128_a)) {
			__hybrid_uint128_or128(__u128_res, __u128_mask);
			__hybrid_uint128_sub128(__u128_a, __u128_b);
		}
		if (!__u128_i)
			break;
		--__u128_i;
		__hybrid_uint128_shr32(__u128_b, 1);
		__hybrid_uint128_shr32(__u128_mask, 1);
	}
	if (__res_div)
		*__res_div = __u128_res;
	if (__res_mod)
		*__res_mod = __u128_a;
}

__LOCAL __ATTR_IN(1) __ATTR_IN(2) __ATTR_OUT_OPT(3) __ATTR_OUT_OPT(4) void
(__hybrid_PRIVATE_int128_divmod128)(__hybrid_int128_t const *__lhs, __hybrid_int128_t const *__rhs,
                                    __hybrid_int128_t *__res_div, __hybrid_int128_t *__res_mod) {
	__hybrid_int128_t __u128_a, __u128_b;
	__hybrid_int128_t __u128_div, __u128_mod;
	__hybrid_int128_copy(__u128_a, *__lhs);
	__hybrid_int128_copy(__u128_b, *__rhs);

	/* Need to pass the absolute values of operands to the unsigned function */
	if (__hybrid_int128_isneg(__u128_a))
		__hybrid_int128_neg(__u128_a);
	if (__hybrid_int128_isneg(__u128_b))
		__hybrid_int128_neg(__u128_b);

	/* Do the divmod operation. */
	__hybrid_PRIVATE_uint128_divmod128((__hybrid_uint128_t *)&__u128_a,
	                                   (__hybrid_uint128_t *)&__u128_b,
	                                   (__hybrid_uint128_t *)&__u128_div,
	                                   (__hybrid_uint128_t *)&__u128_mod);

	/* Fix the sign of return values. */
	if ((!!__hybrid_int128_isneg(*__lhs)) != (!!__hybrid_int128_isneg(*__rhs)))
		__hybrid_int128_neg(__u128_div);
	if (__hybrid_int128_isneg(*__lhs))
		__hybrid_int128_neg(__u128_mod);
	if (__res_div)
		__hybrid_int128_copy(*__res_div, __u128_div);
	if (__res_mod)
		__hybrid_int128_copy(*__res_mod, __u128_mod);
}

__LOCAL __ATTR_IN(1) __ATTR_IN(2) __ATTR_OUT_OPT(3) __ATTR_OUT_OPT(4) void
(__hybrid_PRIVATE_int128_floordivmod128)(__hybrid_int128_t const *__lhs, __hybrid_int128_t const *__rhs,
                                         __hybrid_int128_t *__res_div, __hybrid_uint128_t *__res_mod) {
	__hybrid_int128_t __u128_a, __u128_b;
	__hybrid_int128_t __u128_div, __u128_mod;
	__hybrid_int128_copy(__u128_a, *__lhs);
	__hybrid_int128_copy(__u128_b, *__rhs);

	/* Need to pass the absolute values of operands to the unsigned function */
	if (__hybrid_int128_isneg(__u128_a))
		__hybrid_int128_neg(__u128_a);
	if (__hybrid_int128_isneg(__u128_b))
		__hybrid_int128_neg(__u128_b);

	/* Do the divmod operation. */
	__hybrid_PRIVATE_uint128_divmod128((__hybrid_uint128_t *)&__u128_a,
	                                   (__hybrid_uint128_t *)&__u128_b,
	                                   (__hybrid_uint128_t *)&__u128_div,
	                                   (__hybrid_uint128_t *)&__u128_mod);

	/* Fix the sign of return values. */
	if ((!!__hybrid_int128_isneg(*__lhs)) != (!!__hybrid_int128_isneg(*__rhs)))
		__hybrid_int128_neg(__u128_div);
	if (__hybrid_int128_isneg(*__lhs))
		__hybrid_int128_neg(__u128_mod);

	/* Floor the result (this is what differentiates us from `__hybrid_PRIVATE_int128_divmod128()') */
	if ((__hybrid_int128_isneg(__u128_mod) && !__hybrid_int128_le8(*__rhs, 0)) ||
	    (!__hybrid_int128_le8(__u128_mod, 0) && __hybrid_int128_isneg(*__rhs))) {
		__hybrid_int128_add128(__u128_mod, *__rhs);
		__hybrid_int128_dec(__u128_div);
	}

	if (__res_div)
		__hybrid_int128_copy(*__res_div, __u128_div);
	if (__res_mod)
		__hybrid_uint128_copy(*__res_mod, __hybrid_int128_asunsigned(__u128_mod));
}

__LOCAL __ATTR_IN(1) __ATTR_OUT_OPT(3) __ATTR_OUT_OPT(4) void
(__hybrid_PRIVATE_int128_divmod8)(__hybrid_int128_t const *__lhs, __INT8_TYPE__ __rhs,
                                  __hybrid_int128_t *__res_div, __INT8_TYPE__ *__res_mod) {
	__hybrid_int128_t __xrhs;
	__hybrid_int128_t __xmod;
	__hybrid_int128_set8(__xrhs, __rhs);
	__hybrid_PRIVATE_int128_divmod128(__lhs, &__xrhs, __res_div, __res_mod ? &__xmod : __NULLPTR);
	if (__res_mod)
		*__res_mod = __hybrid_int128_get8(__xmod);
}

__LOCAL __ATTR_IN(1) __ATTR_OUT_OPT(3) __ATTR_OUT_OPT(4) void
(__hybrid_PRIVATE_int128_floordivmod8)(__hybrid_int128_t const *__lhs, __INT8_TYPE__ __rhs,
                                       __hybrid_int128_t *__res_div, __UINT8_TYPE__ *__res_mod) {
	__hybrid_int128_t __xrhs;
	__hybrid_uint128_t __xmod;
	__hybrid_int128_set8(__xrhs, __rhs);
	__hybrid_PRIVATE_int128_floordivmod128(__lhs, &__xrhs, __res_div, __res_mod ? &__xmod : __NULLPTR);
	if (__res_mod)
		*__res_mod = __hybrid_uint128_get8(__xmod);
}

__LOCAL __ATTR_IN(1) __ATTR_OUT_OPT(3) __ATTR_OUT_OPT(4) void
(__hybrid_PRIVATE_uint128_divmod8)(__hybrid_uint128_t const *__lhs, __UINT8_TYPE__ __rhs,
                                   __hybrid_uint128_t *__res_div, __UINT8_TYPE__ *__res_mod) {
	__hybrid_uint128_t __xrhs;
	__hybrid_uint128_t __xmod;
	__hybrid_uint128_set8(__xrhs, __rhs);
	__hybrid_PRIVATE_uint128_divmod128(__lhs, &__xrhs, __res_div, __res_mod ? &__xmod : __NULLPTR);
	if (__res_mod)
		*__res_mod = __hybrid_uint128_get8(__xmod);
}

__LOCAL __ATTR_IN(1) __ATTR_OUT_OPT(3) __ATTR_OUT_OPT(4) void
(__hybrid_PRIVATE_int128_divmod16)(__hybrid_int128_t const *__lhs, __INT16_TYPE__ __rhs,
                                   __hybrid_int128_t *__res_div, __INT16_TYPE__ *__res_mod) {
	__hybrid_int128_t __xrhs;
	__hybrid_int128_t __xmod;
	__hybrid_int128_set16(__xrhs, __rhs);
	__hybrid_PRIVATE_int128_divmod128(__lhs, &__xrhs, __res_div, __res_mod ? &__xmod : __NULLPTR);
	if (__res_mod)
		*__res_mod = __hybrid_int128_get16(__xmod);
}

__LOCAL __ATTR_IN(1) __ATTR_OUT_OPT(3) __ATTR_OUT_OPT(4) void
(__hybrid_PRIVATE_int128_floordivmod16)(__hybrid_int128_t const *__lhs, __INT16_TYPE__ __rhs,
                                        __hybrid_int128_t *__res_div, __UINT16_TYPE__ *__res_mod) {
	__hybrid_int128_t __xrhs;
	__hybrid_uint128_t __xmod;
	__hybrid_int128_set16(__xrhs, __rhs);
	__hybrid_PRIVATE_int128_floordivmod128(__lhs, &__xrhs, __res_div, __res_mod ? &__xmod : __NULLPTR);
	if (__res_mod)
		*__res_mod = __hybrid_uint128_get16(__xmod);
}

__LOCAL __ATTR_IN(1) __ATTR_OUT_OPT(3) __ATTR_OUT_OPT(4) void
(__hybrid_PRIVATE_uint128_divmod16)(__hybrid_uint128_t const *__lhs, __UINT16_TYPE__ __rhs,
                                    __hybrid_uint128_t *__res_div, __UINT16_TYPE__ *__res_mod) {
	__hybrid_uint128_t __xrhs;
	__hybrid_uint128_t __xmod;
	__hybrid_uint128_set16(__xrhs, __rhs);
	__hybrid_PRIVATE_uint128_divmod128(__lhs, &__xrhs, __res_div, __res_mod ? &__xmod : __NULLPTR);
	if (__res_mod)
		*__res_mod = __hybrid_uint128_get16(__xmod);
}

__LOCAL __ATTR_IN(1) __ATTR_OUT_OPT(3) __ATTR_OUT_OPT(4) void
(__hybrid_PRIVATE_int128_divmod32)(__hybrid_int128_t const *__lhs, __INT32_TYPE__ __rhs,
                                   __hybrid_int128_t *__res_div, __INT32_TYPE__ *__res_mod) {
	__hybrid_int128_t __xrhs;
	__hybrid_int128_t __xmod;
	__hybrid_int128_set32(__xrhs, __rhs);
	__hybrid_PRIVATE_int128_divmod128(__lhs, &__xrhs, __res_div, __res_mod ? &__xmod : __NULLPTR);
	if (__res_mod)
		*__res_mod = __hybrid_int128_get32(__xmod);
}

__LOCAL __ATTR_IN(1) __ATTR_OUT_OPT(3) __ATTR_OUT_OPT(4) void
(__hybrid_PRIVATE_int128_floordivmod32)(__hybrid_int128_t const *__lhs, __INT32_TYPE__ __rhs,
                                        __hybrid_int128_t *__res_div, __UINT32_TYPE__ *__res_mod) {
	__hybrid_int128_t __xrhs;
	__hybrid_uint128_t __xmod;
	__hybrid_int128_set32(__xrhs, __rhs);
	__hybrid_PRIVATE_int128_floordivmod128(__lhs, &__xrhs, __res_div, __res_mod ? &__xmod : __NULLPTR);
	if (__res_mod)
		*__res_mod = __hybrid_uint128_get32(__xmod);
}

__LOCAL __ATTR_IN(1) __ATTR_OUT_OPT(3) __ATTR_OUT_OPT(4) void
(__hybrid_PRIVATE_uint128_divmod32)(__hybrid_uint128_t const *__lhs, __UINT32_TYPE__ __rhs,
                                    __hybrid_uint128_t *__res_div, __UINT32_TYPE__ *__res_mod) {
	__hybrid_uint128_t __xrhs;
	__hybrid_uint128_t __xmod;
	__hybrid_uint128_set32(__xrhs, __rhs);
	__hybrid_PRIVATE_uint128_divmod128(__lhs, &__xrhs, __res_div, __res_mod ? &__xmod : __NULLPTR);
	if (__res_mod)
		*__res_mod = __hybrid_uint128_get32(__xmod);
}

__LOCAL __ATTR_INOUT(1) void
(__hybrid_PRIVATE_int128_div32)(__hybrid_int128_t *__lhs, __INT32_TYPE__ __rhs) {
	__hybrid_int128_t __xrhs;
	__hybrid_int128_set32(__xrhs, __rhs);
	__hybrid_PRIVATE_int128_divmod128(__lhs, &__xrhs, __lhs, __NULLPTR);
}

__LOCAL __ATTR_INOUT(1) void
(__hybrid_PRIVATE_int128_floordiv32)(__hybrid_int128_t *__lhs, __INT32_TYPE__ __rhs) {
	__hybrid_int128_t __xrhs;
	__hybrid_int128_set32(__xrhs, __rhs);
	__hybrid_PRIVATE_int128_floordivmod128(__lhs, &__xrhs, __lhs, __NULLPTR);
}

__LOCAL __ATTR_INOUT(1) void
(__hybrid_PRIVATE_uint128_div32)(__hybrid_uint128_t *__lhs, __UINT32_TYPE__ __rhs) {
	__hybrid_uint128_t __xrhs;
	__hybrid_uint128_set32(__xrhs, __rhs);
	__hybrid_PRIVATE_uint128_divmod128(__lhs, &__xrhs, __lhs, __NULLPTR);
}

__LOCAL __ATTR_INOUT(1) void
(__hybrid_PRIVATE_int128_mod32)(__hybrid_int128_t *__lhs, __INT32_TYPE__ __rhs) {
	__hybrid_int128_t __xrhs;
	__hybrid_int128_set32(__xrhs, __rhs);
	__hybrid_PRIVATE_int128_divmod128(__lhs, &__xrhs, __NULLPTR, __lhs);
}

__LOCAL __ATTR_INOUT(1) void
(__hybrid_PRIVATE_int128_floormod32)(__hybrid_int128_t *__lhs, __INT32_TYPE__ __rhs) {
	__hybrid_int128_t __xrhs;
	__hybrid_int128_set32(__xrhs, __rhs);
	__hybrid_PRIVATE_int128_floordivmod128(__lhs, &__xrhs, __NULLPTR, (__hybrid_uint128_t *)__lhs);
}

__LOCAL __ATTR_INOUT(1) void
(__hybrid_PRIVATE_uint128_mod32)(__hybrid_uint128_t *__lhs, __UINT32_TYPE__ __rhs) {
	__hybrid_uint128_t __xrhs;
	__hybrid_uint128_set32(__xrhs, __rhs);
	__hybrid_PRIVATE_uint128_divmod128(__lhs, &__xrhs, __NULLPTR, __lhs);
}

#ifdef __UINT64_TYPE__
__LOCAL __ATTR_IN(1) __ATTR_OUT_OPT(3) __ATTR_OUT_OPT(4) void
(__hybrid_PRIVATE_int128_divmod64)(__hybrid_int128_t const *__lhs, __INT64_TYPE__ __rhs,
                                   __hybrid_int128_t *__res_div, __INT64_TYPE__ *__res_mod) {
	__hybrid_int128_t __xrhs;
	__hybrid_int128_t __xmod;
	__hybrid_int128_set64(__xrhs, __rhs);
	__hybrid_PRIVATE_int128_divmod128(__lhs, &__xrhs, __res_div, __res_mod ? &__xmod : __NULLPTR);
	if (__res_mod)
		*__res_mod = __hybrid_int128_get64(__xmod);
}

__LOCAL __ATTR_IN(1) __ATTR_OUT_OPT(3) __ATTR_OUT_OPT(4) void
(__hybrid_PRIVATE_int128_floordivmod64)(__hybrid_int128_t const *__lhs, __INT64_TYPE__ __rhs,
                                        __hybrid_int128_t *__res_div, __UINT64_TYPE__ *__res_mod) {
	__hybrid_int128_t __xrhs;
	__hybrid_uint128_t __xmod;
	__hybrid_int128_set64(__xrhs, __rhs);
	__hybrid_PRIVATE_int128_floordivmod128(__lhs, &__xrhs, __res_div, __res_mod ? &__xmod : __NULLPTR);
	if (__res_mod)
		*__res_mod = __hybrid_uint128_get64(__xmod);
}

__LOCAL __ATTR_IN(1) __ATTR_OUT_OPT(3) __ATTR_OUT_OPT(4) void
(__hybrid_PRIVATE_uint128_divmod64)(__hybrid_uint128_t const *__lhs, __UINT64_TYPE__ __rhs,
                                    __hybrid_uint128_t *__res_div, __UINT64_TYPE__ *__res_mod) {
	__hybrid_uint128_t __xrhs;
	__hybrid_uint128_t __xmod;
	__hybrid_uint128_set64(__xrhs, __rhs);
	__hybrid_PRIVATE_uint128_divmod128(__lhs, &__xrhs, __res_div, __res_mod ? &__xmod : __NULLPTR);
	if (__res_mod)
		*__res_mod = __hybrid_uint128_get64(__xmod);
}

__LOCAL __ATTR_INOUT(1) void
(__hybrid_PRIVATE_int128_div64)(__hybrid_int128_t *__lhs, __INT64_TYPE__ __rhs) {
	__hybrid_int128_t __xrhs;
	__hybrid_int128_set64(__xrhs, __rhs);
	__hybrid_PRIVATE_int128_divmod128(__lhs, &__xrhs, __lhs, __NULLPTR);
}

__LOCAL __ATTR_INOUT(1) void
(__hybrid_PRIVATE_int128_floordiv64)(__hybrid_int128_t *__lhs, __INT64_TYPE__ __rhs) {
	__hybrid_int128_t __xrhs;
	__hybrid_int128_set64(__xrhs, __rhs);
	__hybrid_PRIVATE_int128_floordivmod128(__lhs, &__xrhs, __lhs, __NULLPTR);
}

__LOCAL __ATTR_INOUT(1) void
(__hybrid_PRIVATE_uint128_div64)(__hybrid_uint128_t *__lhs, __UINT64_TYPE__ __rhs) {
	__hybrid_uint128_t __xrhs;
	__hybrid_uint128_set64(__xrhs, __rhs);
	__hybrid_PRIVATE_uint128_divmod128(__lhs, &__xrhs, __lhs, __NULLPTR);
}

__LOCAL __ATTR_INOUT(1) void
(__hybrid_PRIVATE_int128_mod64)(__hybrid_int128_t *__lhs, __INT64_TYPE__ __rhs) {
	__hybrid_int128_t __xrhs;
	__hybrid_int128_set64(__xrhs, __rhs);
	__hybrid_PRIVATE_int128_divmod128(__lhs, &__xrhs, __NULLPTR, __lhs);
}

__LOCAL __ATTR_INOUT(1) void
(__hybrid_PRIVATE_int128_floormod64)(__hybrid_int128_t *__lhs, __INT64_TYPE__ __rhs) {
	__hybrid_int128_t __xrhs;
	__hybrid_int128_set64(__xrhs, __rhs);
	__hybrid_PRIVATE_int128_floordivmod128(__lhs, &__xrhs, __NULLPTR, (__hybrid_uint128_t *)__lhs);
}

__LOCAL __ATTR_INOUT(1) void
(__hybrid_PRIVATE_uint128_mod64)(__hybrid_uint128_t *__lhs, __UINT64_TYPE__ __rhs) {
	__hybrid_uint128_t __xrhs;
	__hybrid_uint128_set64(__xrhs, __rhs);
	__hybrid_PRIVATE_uint128_divmod128(__lhs, &__xrhs, __NULLPTR, __lhs);
}
#endif /* __UINT64_TYPE__ */

#define __hybrid_int128_bswap(var)  __hybrid_PRIVATE_uint128_bswap((__hybrid_uint128_t *)&(var))
#define __hybrid_uint128_bswap(var) __hybrid_PRIVATE_uint128_bswap(&(var))

__LOCAL __ATTR_INOUT(1) void
(__hybrid_PRIVATE_uint128_bswap)(__hybrid_uint128_t *__self) {
#ifdef __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC
	__UINT64_TYPE__ __temp;
	__temp = __hybrid_bswap64(__hybrid_uint128_vec64(*__self)[0]);
	__hybrid_uint128_vec64(*__self)[0] = __hybrid_bswap64(__hybrid_uint128_vec64(*__self)[1]);
	__hybrid_uint128_vec64(*__self)[1] = __temp;
#else /* __HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
	__UINT32_TYPE__ __temp;
	__temp = __hybrid_bswap32(__hybrid_uint128_vec32(*__self)[0]);
	__hybrid_uint128_vec32(*__self)[0] = __hybrid_bswap32(__hybrid_uint128_vec32(*__self)[3]);
	__hybrid_uint128_vec32(*__self)[3] = __temp;
	__temp = __hybrid_bswap32(__hybrid_uint128_vec32(*__self)[1]);
	__hybrid_uint128_vec32(*__self)[1] = __hybrid_bswap32(__hybrid_uint128_vec32(*__self)[2]);
	__hybrid_uint128_vec32(*__self)[2] = __temp;
#endif /* !__HYBRID_INT128_CONFIG_USE_64BIT_ARITHMETIC */
}


#if defined(__cplusplus) && defined(WANT_INT128_CXX_INTEGRATION)
extern "C++" {
#endif /* __cplusplus && WANT_INT128_CXX_INTEGRATION */

#if defined(__cplusplus) && defined(WANT_INT128_CXX_INTEGRATION)
__CXX_CLASSMEMBER __hybrid_int128_struct::
__hybrid_int128_struct(__hybrid_uint128_struct const &__v) __CXX_NOEXCEPT {
	__i128_u32[0] = __v.__i128_u32[0];
	__i128_u32[1] = __v.__i128_u32[1];
	__i128_u32[2] = __v.__i128_u32[2];
	__i128_u32[3] = __v.__i128_u32[3];
}
__CXX_CLASSMEMBER __hybrid_int128_struct &__hybrid_int128_struct::
operator=(__hybrid_uint128_struct const &__v) __CXX_NOEXCEPT {
	__i128_u32[0] = __v.__i128_u32[0];
	__i128_u32[1] = __v.__i128_u32[1];
	__i128_u32[2] = __v.__i128_u32[2];
	__i128_u32[3] = __v.__i128_u32[3];
	return *this;
}
__CXX_CLASSMEMBER __hybrid_uint128_struct::
__hybrid_uint128_struct(__hybrid_int128_struct const &__v) __CXX_NOEXCEPT {
	__i128_u32[0] = __v.__i128_u32[0];
	__i128_u32[1] = __v.__i128_u32[1];
	__i128_u32[2] = __v.__i128_u32[2];
	__i128_u32[3] = __v.__i128_u32[3];
}
__CXX_CLASSMEMBER __hybrid_uint128_struct &__hybrid_uint128_struct::
operator=(__hybrid_int128_struct const &__v) __CXX_NOEXCEPT {
	__i128_u32[0] = __v.__i128_u32[0];
	__i128_u32[1] = __v.__i128_u32[1];
	__i128_u32[2] = __v.__i128_u32[2];
	__i128_u32[3] = __v.__i128_u32[3];
	return *this;
}

__LOCAL __ATTR_PURE __ATTR_WUNUSED __hybrid_int128_t operator-(__hybrid_int128_t const &__self) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __hybrid_int128_neg(__res); return __res; }
__LOCAL __ATTR_PURE __ATTR_WUNUSED __hybrid_int128_t operator~(__hybrid_int128_t const &__self) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __hybrid_int128_inv(__res); return __res; }
__LOCAL __ATTR_PURE __ATTR_WUNUSED __hybrid_uint128_t operator~(__hybrid_uint128_t const &__self) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __hybrid_uint128_inv(__res); return __res; }
__LOCAL __hybrid_int128_t &operator++(__hybrid_int128_t &__self) __CXX_NOEXCEPT { __hybrid_int128_inc(__self); return __self; }
__LOCAL __hybrid_int128_t operator++(__hybrid_int128_t &__self, int) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __hybrid_int128_inc(__self); return __res; }
__LOCAL __hybrid_int128_t &operator--(__hybrid_int128_t &__self) __CXX_NOEXCEPT { __hybrid_int128_dec(__self); return __self; }
__LOCAL __hybrid_int128_t operator--(__hybrid_int128_t &__self, int) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __hybrid_int128_dec(__self); return __res; }
__LOCAL __hybrid_uint128_t &operator++(__hybrid_uint128_t &__self) __CXX_NOEXCEPT { __hybrid_uint128_inc(__self); return __self; }
__LOCAL __hybrid_uint128_t operator++(__hybrid_uint128_t &__self, int) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __hybrid_uint128_inc(__self); return __res; }
__LOCAL __hybrid_uint128_t &operator--(__hybrid_uint128_t &__self) __CXX_NOEXCEPT { __hybrid_uint128_dec(__self); return __self; }
__LOCAL __hybrid_uint128_t operator--(__hybrid_uint128_t &__self, int) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __hybrid_uint128_dec(__self); return __res; }
#define __HYBRID_INT128_DEFINE_BINARY_CXX_OPERATOR(op, name)                                                                                                                                                                                                                          \
	template<class __ValType> __LOCAL __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, __hybrid_uint128_t &) operator op##= (__hybrid_uint128_t &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_uint128_##name(__self, __v); return __self; }                                          \
	template<class __ValType> __LOCAL __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, __hybrid_int128_t &) operator op##= (__hybrid_int128_t &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_uint128_##name(__self, __v); return __self; }                                            \
	template<class __ValType> __LOCAL __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, __hybrid_uint128_t &) operator op##= (__hybrid_uint128_t &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_int128_##name(__self, __v); return __self; }                                             \
	template<class __ValType> __LOCAL __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, __hybrid_int128_t &) operator op##= (__hybrid_int128_t &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_int128_##name(__self, __v); return __self; }                                               \
	template<class __ValType> __LOCAL __ATTR_PURE __ATTR_WUNUSED __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, __hybrid_uint128_t) operator op (__hybrid_uint128_t const &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __res op##= __v; return __res; } \
	template<class __ValType> __LOCAL __ATTR_PURE __ATTR_WUNUSED __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, __hybrid_int128_t) operator op (__hybrid_int128_t const &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __res op##= __v; return __res; }    \
	template<class __ValType> __LOCAL __ATTR_PURE __ATTR_WUNUSED __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, __hybrid_uint128_t) operator op (__hybrid_uint128_t const &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __res op##= __v; return __res; }   \
	template<class __ValType> __LOCAL __ATTR_PURE __ATTR_WUNUSED __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, __hybrid_int128_t) operator op (__hybrid_int128_t const &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __res op##= __v; return __res; }      \
	__LOCAL __hybrid_uint128_t &operator op##= (__hybrid_uint128_t &__self, __hybrid_uint128_t const &__v) __CXX_NOEXCEPT { __hybrid_uint128_##name##128(__self, __v); return __self; }                                                                                               \
	__LOCAL __hybrid_uint128_t &operator op##= (__hybrid_uint128_t &__self, __hybrid_int128_t const &__v) __CXX_NOEXCEPT { __hybrid_uint128_##name##128(__self, (__hybrid_uint128_t const &)__v); return __self; }                                                                    \
	__LOCAL __hybrid_int128_t &operator op##= (__hybrid_int128_t &__self, __hybrid_uint128_t const &__v) __CXX_NOEXCEPT { __hybrid_int128_##name##128(__self, (__hybrid_int128_t const &)__v); return __self; }                                                                       \
	__LOCAL __hybrid_int128_t &operator op##= (__hybrid_int128_t &__self, __hybrid_int128_t const &__v) __CXX_NOEXCEPT { __hybrid_int128_##name##128(__self, __v); return __self; }                                                                                                   \
	__LOCAL __hybrid_uint128_t operator op (__hybrid_uint128_t const &__self, __hybrid_uint128_t const &__v) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __res op##= __v; return __res; }                                                                                     \
	__LOCAL __hybrid_uint128_t operator op (__hybrid_uint128_t const &__self, __hybrid_int128_t const &__v) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __res op##= __v; return __res; }                                                                                      \
	__LOCAL __hybrid_int128_t operator op (__hybrid_int128_t const &__self, __hybrid_uint128_t const &__v) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __res op##= __v; return __res; }                                                                                        \
	__LOCAL __hybrid_int128_t operator op (__hybrid_int128_t const &__self, __hybrid_int128_t const &__v) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __res op##= __v; return __res; }
__HYBRID_INT128_DEFINE_BINARY_CXX_OPERATOR(&, and)
__HYBRID_INT128_DEFINE_BINARY_CXX_OPERATOR(|, or)
__HYBRID_INT128_DEFINE_BINARY_CXX_OPERATOR(^, xor)
__HYBRID_INT128_DEFINE_BINARY_CXX_OPERATOR(+, add)
__HYBRID_INT128_DEFINE_BINARY_CXX_OPERATOR(-, sub)
__HYBRID_INT128_DEFINE_BINARY_CXX_OPERATOR(*, mul)
__HYBRID_INT128_DEFINE_BINARY_CXX_OPERATOR(/, div)
__HYBRID_INT128_DEFINE_BINARY_CXX_OPERATOR(%, mod)
#undef __HYBRID_INT128_DEFINE_BINARY_CXX_OPERATOR
#define __HYBRID_INT128_DEFINE_COMPARE_CXX_OPERATOR(op, np, name)                                                                                                                                                                                  \
	template<class __ValType> __LOCAL __ATTR_PURE __ATTR_WUNUSED __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, bool) operator op (__hybrid_uint128_t const &__self, __ValType __v) __CXX_NOEXCEPT { return __hybrid_uint128_##name(__self, __v); } \
	template<class __ValType> __LOCAL __ATTR_PURE __ATTR_WUNUSED __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, bool) operator np (__hybrid_uint128_t const &__self, __ValType __v) __CXX_NOEXCEPT { return !(__self op __v); }                     \
	template<class __ValType> __LOCAL __ATTR_PURE __ATTR_WUNUSED __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, bool) operator op (__hybrid_int128_t const &__self, __ValType __v) __CXX_NOEXCEPT { return __hybrid_uint128_##name(__self, __v); }  \
	template<class __ValType> __LOCAL __ATTR_PURE __ATTR_WUNUSED __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, bool) operator np (__hybrid_int128_t const &__self, __ValType __v) __CXX_NOEXCEPT { return !(__self op __v); }                      \
	template<class __ValType> __LOCAL __ATTR_PURE __ATTR_WUNUSED __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, bool) operator op (__hybrid_uint128_t const &__self, __ValType __v) __CXX_NOEXCEPT { return __hybrid_int128_##name(__self, __v); }    \
	template<class __ValType> __LOCAL __ATTR_PURE __ATTR_WUNUSED __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, bool) operator np (__hybrid_uint128_t const &__self, __ValType __v) __CXX_NOEXCEPT { return !(__self op __v); }                       \
	template<class __ValType> __LOCAL __ATTR_PURE __ATTR_WUNUSED __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, bool) operator op (__hybrid_int128_t const &__self, __ValType __v) __CXX_NOEXCEPT { return __hybrid_int128_##name(__self, __v); }     \
	template<class __ValType> __LOCAL __ATTR_PURE __ATTR_WUNUSED __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, bool) operator np (__hybrid_int128_t const &__self, __ValType __v) __CXX_NOEXCEPT { return !(__self op __v); }                        \
	__LOCAL __ATTR_PURE __ATTR_WUNUSED bool operator op (__hybrid_int128_t const &__self, __hybrid_int128_t const &__v) __CXX_NOEXCEPT { return __hybrid_int128_##name##128(__self, __v); }                                                        \
	__LOCAL __ATTR_PURE __ATTR_WUNUSED bool operator op (__hybrid_int128_t const &__self, __hybrid_uint128_t const &__v) __CXX_NOEXCEPT { return __hybrid_int128_##name##128(__self, __v); }                                                       \
	__LOCAL __ATTR_PURE __ATTR_WUNUSED bool operator np (__hybrid_int128_t const &__self, __hybrid_int128_t const &__v) __CXX_NOEXCEPT { return !(__self op __v); }                                                                                \
	__LOCAL __ATTR_PURE __ATTR_WUNUSED bool operator np (__hybrid_int128_t const &__self, __hybrid_uint128_t const &__v) __CXX_NOEXCEPT { return !(__self op __v); }                                                                               \
	__LOCAL __ATTR_PURE __ATTR_WUNUSED bool operator op (__hybrid_uint128_t const &__self, __hybrid_int128_t const &__v) __CXX_NOEXCEPT { return __hybrid_uint128_##name##128(__self, __v); }                                                      \
	__LOCAL __ATTR_PURE __ATTR_WUNUSED bool operator op (__hybrid_uint128_t const &__self, __hybrid_uint128_t const &__v) __CXX_NOEXCEPT { return __hybrid_uint128_##name##128(__self, __v); }                                                     \
	__LOCAL __ATTR_PURE __ATTR_WUNUSED bool operator np (__hybrid_uint128_t const &__self, __hybrid_int128_t const &__v) __CXX_NOEXCEPT { return !(__self op __v); }                                                                               \
	__LOCAL __ATTR_PURE __ATTR_WUNUSED bool operator np (__hybrid_uint128_t const &__self, __hybrid_uint128_t const &__v) __CXX_NOEXCEPT { return !(__self op __v); }
__HYBRID_INT128_DEFINE_COMPARE_CXX_OPERATOR(==, !=, eq)
__HYBRID_INT128_DEFINE_COMPARE_CXX_OPERATOR(<, >=, lo)
__HYBRID_INT128_DEFINE_COMPARE_CXX_OPERATOR(<=, >, le)
#undef __HYBRID_INT128_DEFINE_COMPARE_CXX_OPERATOR
__LOCAL __hybrid_int128_t &operator<<=(__hybrid_int128_t &__self, __SHIFT_TYPE__ __shift) __CXX_NOEXCEPT { __hybrid_int128_shl(__self, __shift); return __self; }
__LOCAL __hybrid_int128_t &operator>>=(__hybrid_int128_t &__self, __SHIFT_TYPE__ __shift) __CXX_NOEXCEPT { __hybrid_int128_shr(__self, __shift); return __self; }
__LOCAL __hybrid_uint128_t &operator<<=(__hybrid_uint128_t &__self, __SHIFT_TYPE__ __shift) __CXX_NOEXCEPT { __hybrid_uint128_shl(__self, __shift); return __self; }
__LOCAL __hybrid_uint128_t &operator>>=(__hybrid_uint128_t &__self, __SHIFT_TYPE__ __shift) __CXX_NOEXCEPT { __hybrid_uint128_shr(__self, __shift); return __self; }
__LOCAL __ATTR_PURE __ATTR_WUNUSED __hybrid_int128_t operator<<(__hybrid_int128_t const &__self, __SHIFT_TYPE__ __shift) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __res <<= __shift; return __res; }
__LOCAL __ATTR_PURE __ATTR_WUNUSED __hybrid_int128_t operator>>(__hybrid_int128_t const &__self, __SHIFT_TYPE__ __shift) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __res >>= __shift; return __res; }
__LOCAL __ATTR_PURE __ATTR_WUNUSED __hybrid_uint128_t operator<<(__hybrid_uint128_t const &__self, __SHIFT_TYPE__ __shift) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __res <<= __shift; return __res; }
__LOCAL __ATTR_PURE __ATTR_WUNUSED __hybrid_uint128_t operator>>(__hybrid_uint128_t const &__self, __SHIFT_TYPE__ __shift) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __res >>= __shift; return __res; }
#undef __HYBRID_INT128_ENABLE_IF_SIGNED
#undef __HYBRID_INT128_ENABLE_IF_UNSIGNED
} /* extern "C++" */
#endif /* __cplusplus && WANT_INT128_CXX_INTEGRATION */

__DECL_END

#endif /* !__INT128_TYPE__ || !__UINT128_TYPE__ */

#define __hybrid_int128_overflow_cast8(var, p_result)   (*(p_result) = __hybrid_int128_get8(var), __builtin_expect(!__hybrid_int128_is8bit(var), 0))
#define __hybrid_int128_overflow_cast16(var, p_result)  (*(p_result) = __hybrid_int128_get16(var), __builtin_expect(!__hybrid_int128_is16bit(var), 0))
#define __hybrid_int128_overflow_cast32(var, p_result)  (*(p_result) = __hybrid_int128_get32(var), __builtin_expect(!__hybrid_int128_is32bit(var), 0))
#define __hybrid_uint128_overflow_cast8(var, p_result)  (*(p_result) = __hybrid_uint128_get8(var), __builtin_expect(!__hybrid_uint128_is8bit(var), 0))
#define __hybrid_uint128_overflow_cast16(var, p_result) (*(p_result) = __hybrid_uint128_get16(var), __builtin_expect(!__hybrid_uint128_is16bit(var), 0))
#define __hybrid_uint128_overflow_cast32(var, p_result) (*(p_result) = __hybrid_uint128_get32(var), __builtin_expect(!__hybrid_uint128_is32bit(var), 0))
#ifdef __UINT64_TYPE__
#define __hybrid_int128_overflow_cast64(var, p_result)  (*(p_result) = __hybrid_int128_get64(var), __builtin_expect(!__hybrid_int128_is64bit(var), 0))
#define __hybrid_uint128_overflow_cast64(var, p_result) (*(p_result) = __hybrid_uint128_get64(var), __builtin_expect(!__hybrid_uint128_is64bit(var), 0))
#endif /* __UINT64_TYPE__ */
#ifdef __UINT128_TYPE__
#define __hybrid_int128_overflow_cast128(var, p_result)  (*(p_result) = (var), 0)
#define __hybrid_uint128_overflow_cast128(var, p_result) (*(p_result) = (var), 0)
#endif /* __UINT128_TYPE__ */
#ifdef __NO_builtin_choose_expr
#ifdef __UINT128_TYPE__
#define __hybrid_uint128_overflow_cast(x, p_result)                             \
	(sizeof(*(p_result)) <= 1 ? __hybrid_uint128_overflow_cast8(x, p_result) :  \
	 sizeof(*(p_result)) <= 2 ? __hybrid_uint128_overflow_cast16(x, p_result) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_uint128_overflow_cast32(x, p_result) : \
	 sizeof(*(p_result)) <= 8 ? __hybrid_uint128_overflow_cast64(x, p_result) : \
	                            __hybrid_uint128_overflow_cast128(x, p_result))
#define __hybrid_int128_overflow_cast(x, p_result)                             \
	(sizeof(*(p_result)) <= 1 ? __hybrid_int128_overflow_cast8(x, p_result) :  \
	 sizeof(*(p_result)) <= 2 ? __hybrid_int128_overflow_cast16(x, p_result) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_int128_overflow_cast32(x, p_result) : \
	 sizeof(*(p_result)) <= 8 ? __hybrid_int128_overflow_cast64(x, p_result) : \
	                            __hybrid_int128_overflow_cast128(x, p_result))
#elif defined(__UINT64_TYPE__)
#define __hybrid_uint128_overflow_cast(x, p_result)                             \
	(sizeof(*(p_result)) <= 1 ? __hybrid_uint128_overflow_cast8(x, p_result) :  \
	 sizeof(*(p_result)) <= 2 ? __hybrid_uint128_overflow_cast16(x, p_result) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_uint128_overflow_cast32(x, p_result) : \
	                            __hybrid_uint128_overflow_cast64(x, p_result))
#define __hybrid_int128_overflow_cast(x, p_result)                             \
	(sizeof(*(p_result)) <= 1 ? __hybrid_int128_overflow_cast8(x, p_result) :  \
	 sizeof(*(p_result)) <= 2 ? __hybrid_int128_overflow_cast16(x, p_result) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_int128_overflow_cast32(x, p_result) : \
	                            __hybrid_int128_overflow_cast64(x, p_result))
#else /* ... */
#define __hybrid_uint128_overflow_cast(x, p_result)                             \
	(sizeof(*(p_result)) <= 1 ? __hybrid_uint128_overflow_cast8(x, p_result) :  \
	 sizeof(*(p_result)) <= 2 ? __hybrid_uint128_overflow_cast16(x, p_result) : \
	                            __hybrid_uint128_overflow_cast32(x, p_result))
#define __hybrid_int128_overflow_cast(x, p_result)                             \
	(sizeof(*(p_result)) <= 1 ? __hybrid_int128_overflow_cast8(x, p_result) :  \
	 sizeof(*(p_result)) <= 2 ? __hybrid_int128_overflow_cast16(x, p_result) : \
	                            __hybrid_int128_overflow_cast32(x, p_result))
#endif /* !... */
#else /* __NO_builtin_choose_expr */
#ifdef __UINT128_TYPE__
#define __hybrid_uint128_overflow_cast(x, p_result)                                                \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_uint128_overflow_cast8(x, p_result),  \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_uint128_overflow_cast16(x, p_result), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_uint128_overflow_cast32(x, p_result), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 8, __hybrid_uint128_overflow_cast64(x, p_result), \
	                                                __hybrid_uint128_overflow_cast128(x, p_result)))))
#define __hybrid_int128_overflow_cast(x, p_result)                                                \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_int128_overflow_cast8(x, p_result),  \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_int128_overflow_cast16(x, p_result), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_int128_overflow_cast32(x, p_result), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 8, __hybrid_int128_overflow_cast64(x, p_result), \
	                                                __hybrid_int128_overflow_cast128(x, p_result)))))
#elif defined(__UINT64_TYPE__)
#define __hybrid_uint128_overflow_cast(x, p_result)                                                \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_uint128_overflow_cast8(x, p_result),  \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_uint128_overflow_cast16(x, p_result), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_uint128_overflow_cast32(x, p_result), \
	                                                __hybrid_uint128_overflow_cast64(x, p_result))))
#define __hybrid_int128_overflow_cast(x, p_result)                                                \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_int128_overflow_cast8(x, p_result),  \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_int128_overflow_cast16(x, p_result), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_int128_overflow_cast32(x, p_result), \
	                                                __hybrid_int128_overflow_cast64(x, p_result))))
#else /* ... */
#define __hybrid_uint128_overflow_cast(x, p_result)                                                \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_uint128_overflow_cast8(x, p_result),  \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_uint128_overflow_cast16(x, p_result), \
	                                                __hybrid_uint128_overflow_cast32(x, p_result)))
#define __hybrid_int128_overflow_cast(x, p_result)                                                \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_int128_overflow_cast8(x, p_result),  \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_int128_overflow_cast16(x, p_result), \
	                                                __hybrid_int128_overflow_cast32(x, p_result)))
#endif /* !... */
#endif /* !__NO_builtin_choose_expr */


#define __hybrid_uint128_ne(var, v)    (!__hybrid_uint128_eq(var, v))
#define __hybrid_uint128_ne8(var, v)   (!__hybrid_uint128_eq8(var, v))
#define __hybrid_uint128_ne16(var, v)  (!__hybrid_uint128_eq16(var, v))
#define __hybrid_uint128_ne32(var, v)  (!__hybrid_uint128_eq32(var, v))
#define __hybrid_uint128_ne64(var, v)  (!__hybrid_uint128_eq64(var, v))
#define __hybrid_uint128_ne128(var, v) (!__hybrid_uint128_eq128(var, v))
#define __hybrid_int128_ne(var, v)     (!__hybrid_int128_eq(var, v))
#define __hybrid_int128_ne8(var, v)    (!__hybrid_int128_eq8(var, v))
#define __hybrid_int128_ne16(var, v)   (!__hybrid_int128_eq16(var, v))
#define __hybrid_int128_ne32(var, v)   (!__hybrid_int128_eq32(var, v))
#define __hybrid_int128_ne64(var, v)   (!__hybrid_int128_eq64(var, v))
#define __hybrid_int128_ne128(var, v)  (!__hybrid_int128_eq128(var, v))

#define __hybrid_uint128_gr(var, v)    (!__hybrid_uint128_le(var, v))
#define __hybrid_uint128_gr8(var, v)   (!__hybrid_uint128_le8(var, v))
#define __hybrid_uint128_gr16(var, v)  (!__hybrid_uint128_le16(var, v))
#define __hybrid_uint128_gr32(var, v)  (!__hybrid_uint128_le32(var, v))
#define __hybrid_uint128_gr64(var, v)  (!__hybrid_uint128_le64(var, v))
#define __hybrid_uint128_gr128(var, v) (!__hybrid_uint128_le128(var, v))
#define __hybrid_int128_gr(var, v)     (!__hybrid_int128_le(var, v))
#define __hybrid_int128_gr8(var, v)    (!__hybrid_int128_le8(var, v))
#define __hybrid_int128_gr16(var, v)   (!__hybrid_int128_le16(var, v))
#define __hybrid_int128_gr32(var, v)   (!__hybrid_int128_le32(var, v))
#define __hybrid_int128_gr64(var, v)   (!__hybrid_int128_le64(var, v))
#define __hybrid_int128_gr128(var, v)  (!__hybrid_int128_le128(var, v))

#define __hybrid_uint128_ge(var, v)    (!__hybrid_uint128_lo(var, v))
#define __hybrid_uint128_ge8(var, v)   (!__hybrid_uint128_lo8(var, v))
#define __hybrid_uint128_ge16(var, v)  (!__hybrid_uint128_lo16(var, v))
#define __hybrid_uint128_ge32(var, v)  (!__hybrid_uint128_lo32(var, v))
#define __hybrid_uint128_ge64(var, v)  (!__hybrid_uint128_lo64(var, v))
#define __hybrid_uint128_ge128(var, v) (!__hybrid_uint128_lo128(var, v))
#define __hybrid_int128_ge(var, v)     (!__hybrid_int128_lo(var, v))
#define __hybrid_int128_ge8(var, v)    (!__hybrid_int128_lo8(var, v))
#define __hybrid_int128_ge16(var, v)   (!__hybrid_int128_lo16(var, v))
#define __hybrid_int128_ge32(var, v)   (!__hybrid_int128_lo32(var, v))
#define __hybrid_int128_ge64(var, v)   (!__hybrid_int128_lo64(var, v))
#define __hybrid_int128_ge128(var, v)  (!__hybrid_int128_lo128(var, v))

#endif /* __CC__ */


#endif /* !__GUARD_HYBRID_INT128_H */
