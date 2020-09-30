/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID_INT128_H
#define __GUARD_HYBRID_INT128_H 1

#include "../__stdinc.h"
#include "typecore.h"

#ifdef __CC__
#if defined(__INT128_TYPE__) && defined(__UINT128_TYPE__)
#define __hybrid_int128_t  __INT128_TYPE__
#define __hybrid_uint128_t __UINT128_TYPE__

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
#define __hybrid_int128_set8(var, v)   ((var) = (__INT128_TYPE__)(__INT8_TYPE__)(v))
#define __hybrid_uint128_get8(var)     ((__UINT8_TYPE__)(var))
#define __hybrid_uint128_set8(var, v)  ((var) = (__UINT128_TYPE__)(__UINT8_TYPE__)(v))
#define __hybrid_int128_get16(var)     ((__INT16_TYPE__)(var))
#define __hybrid_int128_set16(var, v)  ((var) = (__INT128_TYPE__)(__INT16_TYPE__)(v))
#define __hybrid_uint128_get16(var)    ((__UINT16_TYPE__)(var))
#define __hybrid_uint128_set16(var, v) ((var) = (__UINT128_TYPE__)(__UINT16_TYPE__)(v))
#define __hybrid_int128_get32(var)     ((__INT32_TYPE__)(var))
#define __hybrid_int128_set32(var, v)  ((var) = (__INT128_TYPE__)(__INT32_TYPE__)(v))
#define __hybrid_uint128_get32(var)    ((__UINT32_TYPE__)(var))
#define __hybrid_uint128_set32(var, v) ((var) = (__UINT128_TYPE__)(__UINT32_TYPE__)(v))
#define __hybrid_int128_get64(var)     ((__INT64_TYPE__)(var))
#define __hybrid_int128_set64(var, v)  ((var) = (__INT128_TYPE__)(__INT64_TYPE__)(v))
#define __hybrid_uint128_get64(var)    ((__UINT64_TYPE__)(var))
#define __hybrid_uint128_set64(var, v) ((var) = (__UINT128_TYPE__)(__UINT64_TYPE__)(v))
#define __hybrid_int128_set(var, v)    ((var) = (__INT128_TYPE__)(v))
#define __hybrid_uint128_set(var, v)   ((var) = (__UINT128_TYPE__)(v))


#define __hybrid_uint128_inc(var)                    (void)(++(var))
#define __hybrid_int128_inc(var)                     (void)(++(var))
#define __hybrid_uint128_dec(var)                    (void)(--(var))
#define __hybrid_int128_dec(var)                     (void)(--(var))
#define __hybrid_uint128_inv(var)                    (void)((var) = ~(var))
#define __hybrid_int128_inv(var)                     (void)((var) = ~(var))
#define __hybrid_int128_neg(var)                     (void)((var) = -(var))
#define __hybrid_int128_isneg(var)                   ((var) < 0)
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
#define __hybrid_uint128_div(var, v)                 (void)((var) /= (__UINT128_TYPE__)(v))
#define __hybrid_uint128_div8(var, v)                (void)((var) /= (__UINT128_TYPE__)(__UINT8_TYPE__)(v))
#define __hybrid_uint128_div16(var, v)               (void)((var) /= (__UINT128_TYPE__)(__UINT16_TYPE__)(v))
#define __hybrid_uint128_div32(var, v)               (void)((var) /= (__UINT128_TYPE__)(__UINT32_TYPE__)(v))
#define __hybrid_uint128_div64(var, v)               (void)((var) /= (__UINT128_TYPE__)(__UINT64_TYPE__)(v))
#define __hybrid_uint128_div128(var, v)              (void)((var) /= (__UINT128_TYPE__)(v))
#define __hybrid_int128_div(var, v)                  (void)((var) /= (__INT128_TYPE__)(v))
#define __hybrid_int128_div8(var, v)                 (void)((var) /= (__INT128_TYPE__)(__INT8_TYPE__)(v))
#define __hybrid_int128_div16(var, v)                (void)((var) /= (__INT128_TYPE__)(__INT16_TYPE__)(v))
#define __hybrid_int128_div32(var, v)                (void)((var) /= (__INT128_TYPE__)(__INT32_TYPE__)(v))
#define __hybrid_int128_div64(var, v)                (void)((var) /= (__INT128_TYPE__)(__INT64_TYPE__)(v))
#define __hybrid_int128_div128(var, v)               (void)((var) /= (__INT128_TYPE__)(v))
#define __hybrid_uint128_mod(var, v)                 (void)((var) %= (__UINT128_TYPE__)(v))
#define __hybrid_uint128_mod8(var, v)                (void)((var) %= (__UINT128_TYPE__)(__UINT8_TYPE__)(v))
#define __hybrid_uint128_mod16(var, v)               (void)((var) %= (__UINT128_TYPE__)(__UINT16_TYPE__)(v))
#define __hybrid_uint128_mod32(var, v)               (void)((var) %= (__UINT128_TYPE__)(__UINT32_TYPE__)(v))
#define __hybrid_uint128_mod64(var, v)               (void)((var) %= (__UINT128_TYPE__)(__UINT64_TYPE__)(v))
#define __hybrid_uint128_mod128(var, v)              (void)((var) %= (__UINT128_TYPE__)(v))
#define __hybrid_int128_mod(var, v)                  (void)((var) %= (__INT128_TYPE__)(v))
#define __hybrid_int128_mod8(var, v)                 (void)((var) %= (__INT128_TYPE__)(__INT8_TYPE__)(v))
#define __hybrid_int128_mod16(var, v)                (void)((var) %= (__INT128_TYPE__)(__INT16_TYPE__)(v))
#define __hybrid_int128_mod32(var, v)                (void)((var) %= (__INT128_TYPE__)(__INT32_TYPE__)(v))
#define __hybrid_int128_mod64(var, v)                (void)((var) %= (__INT128_TYPE__)(__INT64_TYPE__)(v))
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
#define __hybrid_uint128_shl_overflows(var, shift)   (((__UINT128_TYPE__)((__UINT128_TYPE__)(var) << (shift)) >> (shift)) != (__UINT128_TYPE__)(var))
#define __hybrid_int128_shl_overflows(var, shift)    (((__INT128_TYPE__)((__INT128_TYPE__)(var) << (shift)) >> (shift)) != (__INT128_TYPE__)(var))
#define __hybrid_uint128_shl32_overflows             __hybrid_uint128_shl_overflows
#define __hybrid_int128_shl32_overflows              __hybrid_int128_shl_overflows
#define __hybrid_uint128_shl64_overflows             __hybrid_uint128_shl_overflows
#define __hybrid_int128_shl64_overflows              __hybrid_int128_shl_overflows
#define __hybrid_uint128_shr_overflows(var, shift)   (((var) & ((__UINT128_C(1) << (shift)) - 1)) != 0)
#define __hybrid_int128_shr_overflows(var, shift)    (((var) & ((__INT128_C(1) << (shift)) - 1)) != 0)
#define __hybrid_uint128_shr32_overflows             __hybrid_uint128_shr_overflows
#define __hybrid_int128_shr32_overflows              __hybrid_int128_shr_overflows
#define __hybrid_uint128_shr64_overflows             __hybrid_uint128_shr_overflows
#define __hybrid_int128_shr64_overflows              __hybrid_int128_shr_overflows
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
#define __hybrid_int128_setzero_minus_min(var)       (void)((var) = (__INT128_TYPE__)((__UINT128_TYPE__)0 - __PRIVATE_HYBRID_INT128_SMIN))
#define __hybrid_int128_iszero_minus_min(var)        ((var) == (__INT128_TYPE__)((__UINT128_TYPE__)0 - __PRIVATE_HYBRID_INT128_SMIN))
#define __hybrid_uint128_setmin                      __hybrid_uint128_setzero
#define __hybrid_uint128_ismax(var)                  ((var) == (__UINT128_TYPE__)-1)
#define __hybrid_uint128_ismin                       __hybrid_uint128_iszero
#define __hybrid_uint128_setmax(var)                 ((var) == (__UINT128_TYPE__)-1)
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

#else /* __INT128_TYPE__ && __UINT128_TYPE__ */
#if defined(__cplusplus) && defined(WANT_INT128_CXX_INTEGRATION)
#include "../__stdcxx.h"
#endif /* __cplusplus && WANT_INT128_CXX_INTEGRATION */

#include "__overflow.h"
#include "__byteorder.h"

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


#ifdef __UINT64_TYPE__
#define __hybrid_int128_get64(var) __hybrid_int128_vec64_significand(var, 0)
#define __hybrid_int128_set64(var, v)                                 \
	(__hybrid_int128_vec64_significand(var, 0) = (__INT64_TYPE__)(v), \
	 __hybrid_int128_vec64_significand(var, 1) = __hybrid_int128_vec64_significand(var, 0) < 0 ? -1 : 0)
#define __hybrid_uint128_get64(var) \
	__hybrid_uint128_vec64_significand(var, 0)
#define __hybrid_uint128_set64(var, v)                                  \
	(__hybrid_uint128_vec64_significand(var, 0) = (__UINT64_TYPE__)(v), \
	 __hybrid_uint128_vec64_significand(var, 1) = 0)
#endif /* __UINT64_TYPE__ */

#define __hybrid_int128_get32(var)  __hybrid_int128_vec32_significand(var, 0)
#define __hybrid_uint128_get32(var) __hybrid_uint128_vec32_significand(var, 0)
#if defined(__UINT64_TYPE__) && __SIZEOF_BUSINT__ >= 8
#define __hybrid_int128_set32(var, v)  __hybrid_int128_set64(var, v)
#define __hybrid_uint128_set32(var, v) __hybrid_uint128_set64(var, v)
#else /* __UINT64_TYPE__ && __SIZEOF_BUSINT__ >= 8 */
#define __hybrid_int128_set32(var, v)                                                                    \
	(__hybrid_int128_vec32_significand(var, 0) = (__INT32_TYPE__)(v),                                    \
	 __hybrid_int128_vec32_significand(var, 1) = __hybrid_int128_vec32_significand(var, 0) < 0 ? -1 : 0, \
	 __hybrid_int128_vec32_significand(var, 2) = __hybrid_int128_vec32_significand(var, 1),              \
	 __hybrid_int128_vec32_significand(var, 3) = __hybrid_int128_vec32_significand(var, 1))
#define __hybrid_uint128_set32(var, v)                                  \
	(__hybrid_uint128_vec32_significand(var, 0) = (__UINT32_TYPE__)(v), \
	 __hybrid_uint128_vec32_significand(var, 0) = 0,                    \
	 __hybrid_uint128_vec32_significand(var, 0) = 0,                    \
	 __hybrid_uint128_vec32_significand(var, 0) = 0)
#endif /* !__UINT64_TYPE__ || __SIZEOF_BUSINT__ < 8 */

#define __hybrid_int128_get16(var)  __hybrid_int128_vec16_significand(var, 0)
#define __hybrid_uint128_get16(var) __hybrid_uint128_vec16_significand(var, 0)
#if defined(__UINT64_TYPE__) && __SIZEOF_BUSINT__ >= 8
#define __hybrid_int128_set16(var, v)  __hybrid_int128_set64(var, v)
#define __hybrid_uint128_set16(var, v) __hybrid_uint128_set64(var, v)
#elif __SIZEOF_BUSINT__ >= 4
#define __hybrid_int128_set16(var, v)  __hybrid_int128_set32(var, v)
#define __hybrid_uint128_set16(var, v) __hybrid_uint128_set32(var, v)
#else /* __SIZEOF_BUSINT__ >= ... */
#define __hybrid_int128_set16(var, v)                                                                    \
	(__hybrid_int128_vec16_significand(var, 0) = (__INT16_TYPE__)(v),                                    \
	 __hybrid_int128_vec16_significand(var, 1) = __hybrid_int128_vec16_significand(var, 0) < 0 ? -1 : 0, \
	 __hybrid_int128_vec16_significand(var, 2) = __hybrid_int128_vec16_significand(var, 1),              \
	 __hybrid_int128_vec16_significand(var, 3) = __hybrid_int128_vec16_significand(var, 1),              \
	 __hybrid_int128_vec16_significand(var, 4) = __hybrid_int128_vec16_significand(var, 1),              \
	 __hybrid_int128_vec16_significand(var, 5) = __hybrid_int128_vec16_significand(var, 1),              \
	 __hybrid_int128_vec16_significand(var, 6) = __hybrid_int128_vec16_significand(var, 1),              \
	 __hybrid_int128_vec16_significand(var, 7) = __hybrid_int128_vec16_significand(var, 1))
#define __hybrid_uint128_set16(var, v)                                  \
	(__hybrid_uint128_vec16_significand(var, 0) = (__UINT16_TYPE__)(v), \
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
#if defined(__UINT64_TYPE__) && __SIZEOF_BUSINT__ >= 8
#define __hybrid_int128_set8(var, v)  __hybrid_int128_set64(var, v)
#define __hybrid_uint128_set8(var, v) __hybrid_uint128_set64(var, v)
#define __hybrid_int128_set(var, v)   __hybrid_int128_set64(var, v)
#define __hybrid_uint128_set(var, v)  __hybrid_uint128_set64(var, v)
#elif __SIZEOF_BUSINT__ >= 4
#define __hybrid_int128_set8(var, v)  __hybrid_int128_set32(var, v)
#define __hybrid_uint128_set8(var, v) __hybrid_uint128_set32(var, v)
#ifdef __UINT64_TYPE__
#ifdef __NO_builtin_choose_expr
#define __hybrid_int128_set(var, v)   (sizeof(v) == 8 ? __hybrid_int128_set64(var, v) : __hybrid_int128_set32(var, v))
#define __hybrid_uint128_set(var, v)  (sizeof(v) == 8 ? __hybrid_uint128_set64(var, v) : __hybrid_uint128_set32(var, v))
#else /* __NO_builtin_choose_expr */
#define __hybrid_int128_set(var, v)   __builtin_choose_expr(sizeof(v) == 8, __hybrid_int128_set64(var, v), __hybrid_int128_set32(var, v))
#define __hybrid_uint128_set(var, v)  __builtin_choose_expr(sizeof(v) == 8, __hybrid_uint128_set64(var, v), __hybrid_uint128_set32(var, v))
#endif /* !__NO_builtin_choose_expr */
#else /* __UINT64_TYPE__ */
#define __hybrid_int128_set(var, v)   __hybrid_int128_set32(var, v)
#define __hybrid_uint128_set(var, v)  __hybrid_uint128_set32(var, v)
#endif /* !__UINT64_TYPE__ */
#else /* __SIZEOF_BUSINT__ >= ... */
#define __hybrid_int128_set8(var, v)  __hybrid_int128_set16(var, v)
#define __hybrid_uint128_set8(var, v) __hybrid_uint128_set16(var, v)
#ifdef __UINT64_TYPE__
#ifdef __NO_builtin_choose_expr
#define __hybrid_int128_set(var, v)   (sizeof(v) == 8 ? __hybrid_int128_set64(var, v) : sizeof(v) == 4 ? __hybrid_int128_set32(var, v) : __hybrid_int128_set16(var, v))
#define __hybrid_uint128_set(var, v)  (sizeof(v) == 8 ? __hybrid_uint128_set64(var, v) : sizeof(v) == 4 ? __hybrid_uint128_set32(var, v) : __hybrid_uint128_set16(var, v))
#else /* __NO_builtin_choose_expr */
#define __hybrid_int128_set(var, v)   __builtin_choose_expr(sizeof(v) == 8, __hybrid_int128_set64(var, v), __builtin_choose_expr(sizeof(v) == 4, __hybrid_int128_set32(var, v), __hybrid_int128_set16(var, v)))
#define __hybrid_uint128_set(var, v)  __builtin_choose_expr(sizeof(v) == 8, __hybrid_uint128_set64(var, v), __builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_set32(var, v), __hybrid_uint128_set16(var, v)))
#endif /* !__NO_builtin_choose_expr */
#else /* __UINT64_TYPE__ */
#ifdef __NO_builtin_choose_expr
#define __hybrid_int128_set(var, v)   (sizeof(v) == 4 ? __hybrid_int128_set32(var, v) : __hybrid_int128_set16(var, v))
#define __hybrid_uint128_set(var, v)  (sizeof(v) == 4 ? __hybrid_uint128_set32(var, v) : __hybrid_uint128_set16(var, v))
#else /* __NO_builtin_choose_expr */
#define __hybrid_int128_set(var, v)   __builtin_choose_expr(sizeof(v) == 4, __hybrid_int128_set32(var, v), __hybrid_int128_set16(var, v))
#define __hybrid_uint128_set(var, v)  __builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_set32(var, v), __hybrid_uint128_set16(var, v))
#endif /* !__NO_builtin_choose_expr */
#endif /* !__UINT64_TYPE__ */
#endif /* __SIZEOF_BUSINT__ < ... */

#if defined(__UINT64_TYPE__) && __SIZEOF_BUSINT__ >= 8
#define __hybrid_uint128_inc(var)                               \
	(void)(++__hybrid_uint128_vec64_significand(var, 0) != 0 || \
	       (++__hybrid_uint128_vec64_significand(var, 1), 0))
#define __hybrid_uint128_dec(var)                                                            \
	(void)(--__hybrid_uint128_vec64_significand(var, 0) != __UINT64_C(0xffffffffffffffff) || \
	       (--__hybrid_uint128_vec64_significand(var, 1), 0))
#define __hybrid_uint128_inv(var)                                            \
	(void)(__hybrid_uint128_vec64(var)[0] = ~__hybrid_uint128_vec64(var)[0], \
	       __hybrid_uint128_vec64(var)[1] = ~__hybrid_uint128_vec64(var)[1])
#else /* __UINT64_TYPE__ && __SIZEOF_BUSINT__ >= 8 */
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
#endif /* !__UINT64_TYPE__ || __SIZEOF_BUSINT__ < 8 */
#define __hybrid_int128_inc __hybrid_uint128_inc
#define __hybrid_int128_dec __hybrid_uint128_dec
#define __hybrid_int128_inv __hybrid_uint128_inv
#define __hybrid_int128_neg(var) (__hybrid_int128_dec(var), __hybrid_int128_inv(var))
#define __hybrid_int128_isneg(var) (__hybrid_uint128_vec8_significand(var, 15) & 0x80)

#ifdef __UINT64_TYPE__
#define __hybrid_uint128_and128(var, v)                                    \
	(void)(__hybrid_uint128_vec64(var)[0] &= __hybrid_uint128_vec64(v)[0], \
	       __hybrid_uint128_vec64(var)[1] &= __hybrid_uint128_vec64(v)[1])
#define __hybrid_uint128_and64(var, v) __hybrid_uint128_set64(var, __hybrid_uint128_get64(var) & (__UINT64_TYPE__)(v))
#define __hybrid_int128_and64(var, v)  __hybrid_int128_set64(var, __hybrid_int128_get64(var) & (__INT64_TYPE__)(v))
#define __hybrid_uint128_or128(var, v)                                     \
	(void)(__hybrid_uint128_vec64(var)[0] |= __hybrid_uint128_vec64(v)[0], \
	       __hybrid_uint128_vec64(var)[1] |= __hybrid_uint128_vec64(v)[1])
#define __hybrid_uint128_or64(var, v) (void)(__hybrid_uint128_vec64_significand(var, 0) |= (v))
#define __hybrid_int128_or64(var, v)                                   \
	(__hybrid_int128_vec64_significand(var, 0) |= (__INT64_TYPE__)(v), \
	 (__INT64_TYPE__)(v) < 0 ? (void)(__hybrid_int128_vec64_significand(var, 1) = -1) : (void)0)
#define __hybrid_uint128_xor128(var, v)                                    \
	(void)(__hybrid_uint128_vec64(var)[0] ^= __hybrid_uint128_vec64(v)[0], \
	       __hybrid_uint128_vec64(var)[1] ^= __hybrid_uint128_vec64(v)[1])
#define __hybrid_uint128_xor64(var, v) (void)(__hybrid_uint128_vec64_significand(var, 0) ^= (v))
#define __hybrid_int128_xor64(var, v)                                   \
	(__hybrid_int128_vec64_significand(var, 0) ^= (__INT64_TYPE__)(v), \
	 (__INT64_TYPE__)(v) < 0 ? (void)(__hybrid_int128_vec64_significand(var, 1) ^= -1) : (void)0)
#else /* __UINT64_TYPE__ */
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
#endif /* !__UINT64_TYPE__ */
#define __hybrid_int128_and128         __hybrid_uint128_and128
#define __hybrid_uint128_and8(var, v)  __hybrid_uint128_set8(var, __hybrid_uint128_get8(var) & (__UINT8_TYPE__)(v))
#define __hybrid_uint128_and16(var, v) __hybrid_uint128_set16(var, __hybrid_uint128_get16(var) & (__UINT16_TYPE__)(v))
#define __hybrid_uint128_and32(var, v) __hybrid_uint128_set32(var, __hybrid_uint128_get32(var) & (__UINT32_TYPE__)(v))
#define __hybrid_int128_and8(var, v)   __hybrid_int128_set8(var, __hybrid_int128_get8(var) & (__INT8_TYPE__)(v))
#define __hybrid_int128_and16(var, v)  __hybrid_int128_set16(var, __hybrid_int128_get16(var) & (__INT16_TYPE__)(v))
#define __hybrid_int128_and32(var, v)  __hybrid_int128_set32(var, __hybrid_int128_get32(var) & (__INT32_TYPE__)(v))
#define __hybrid_int128_or128          __hybrid_uint128_or128
#define __hybrid_uint128_or8(var, v)   (void)(__hybrid_uint128_vec8_significand(var, 0) |= (v))
#define __hybrid_uint128_or16(var, v)  (void)(__hybrid_uint128_vec16_significand(var, 0) |= (v))
#define __hybrid_uint128_or32(var, v)  (void)(__hybrid_uint128_vec32_significand(var, 0) |= (v))
#define __hybrid_int128_xor128         __hybrid_uint128_xor128
#define __hybrid_uint128_xor8(var, v)  (void)(__hybrid_uint128_vec8_significand(var, 0) ^= (v))
#define __hybrid_uint128_xor16(var, v) (void)(__hybrid_uint128_vec16_significand(var, 0) ^= (v))
#define __hybrid_uint128_xor32(var, v) (void)(__hybrid_uint128_vec32_significand(var, 0) ^= (v))

#if defined(__UINT64_TYPE__) && __SIZEOF_BUSINT__ >= 8
#define __hybrid_int128_or8(var, v)    (__hybrid_uint128_vec8_significand(var, 0) |= (v), (v) < 0  ? (void)(__hybrid_int128_vec64_significand(var, 1) = -1, __hybrid_int128_vec32_significand(var, 1) = -1, __hybrid_int128_vec16_significand(var, 1) = -1, __hybrid_int128_vec8_significand(var, 1) = -1) : (void)0)
#define __hybrid_int128_or16(var, v)   (__hybrid_uint128_vec16_significand(var, 0) |= (v), (v) < 0 ? (void)(__hybrid_int128_vec64_significand(var, 1) = -1, __hybrid_int128_vec32_significand(var, 1) = -1, __hybrid_int128_vec16_significand(var, 1) = -1) : (void)0)
#define __hybrid_int128_or32(var, v)   (__hybrid_uint128_vec32_significand(var, 0) |= (v), (v) < 0 ? (void)(__hybrid_int128_vec64_significand(var, 1) = -1, __hybrid_int128_vec32_significand(var, 1) = -1) : (void)0)
#define __hybrid_int128_xor8(var, v)   (__hybrid_uint128_vec8_significand(var, 0) ^= (v), (v) < 0  ? (void)(__hybrid_int128_vec64_significand(var, 1) ^= -1, __hybrid_int128_vec32_significand(var, 1) ^= -1, __hybrid_int128_vec16_significand(var, 1) ^= -1, __hybrid_int128_vec8_significand(var, 1) ^= -1) : (void)0)
#define __hybrid_int128_xor16(var, v)  (__hybrid_uint128_vec16_significand(var, 0) ^= (v), (v) < 0 ? (void)(__hybrid_int128_vec64_significand(var, 1) ^= -1, __hybrid_int128_vec32_significand(var, 1) ^= -1, __hybrid_int128_vec16_significand(var, 1) ^= -1) : (void)0)
#define __hybrid_int128_xor32(var, v)  (__hybrid_uint128_vec32_significand(var, 0) ^= (v), (v) < 0 ? (void)(__hybrid_int128_vec64_significand(var, 1) ^= -1, __hybrid_int128_vec32_significand(var, 1) ^= -1) : (void)0)
#else /* __UINT64_TYPE__ && __SIZEOF_BUSINT__ >= 8 */
#define __hybrid_int128_or8(var, v)    (__hybrid_uint128_vec8_significand(var, 0) |= (v), (v) < 0  ? (void)(__hybrid_int128_vec32_significand(var, 3) = -1, __hybrid_int128_vec32_significand(var, 2) = -1, __hybrid_int128_vec32_significand(var, 1) = -1, __hybrid_int128_vec16_significand(var, 1) = -1, __hybrid_int128_vec8_significand(var, 1) = -1) : (void)0)
#define __hybrid_int128_or16(var, v)   (__hybrid_uint128_vec16_significand(var, 0) |= (v), (v) < 0 ? (void)(__hybrid_int128_vec32_significand(var, 3) = -1, __hybrid_int128_vec32_significand(var, 2) = -1, __hybrid_int128_vec32_significand(var, 1) = -1, __hybrid_int128_vec16_significand(var, 1) = -1) : (void)0)
#define __hybrid_int128_or32(var, v)   (__hybrid_uint128_vec32_significand(var, 0) |= (v), (v) < 0 ? (void)(__hybrid_int128_vec32_significand(var, 3) = -1, __hybrid_int128_vec32_significand(var, 2) = -1, __hybrid_int128_vec32_significand(var, 1) = -1) : (void)0)
#define __hybrid_int128_xor8(var, v)   (__hybrid_uint128_vec8_significand(var, 0) ^= (v), (v) < 0  ? (void)(__hybrid_int128_vec32_significand(var, 3) ^= -1, __hybrid_int128_vec32_significand(var, 2) ^= -1, __hybrid_int128_vec32_significand(var, 1) ^= -1, __hybrid_int128_vec16_significand(var, 1) ^= -1, __hybrid_int128_vec8_significand(var, 1) ^= -1) : (void)0)
#define __hybrid_int128_xor16(var, v)  (__hybrid_uint128_vec16_significand(var, 0) ^= (v), (v) < 0 ? (void)(__hybrid_int128_vec32_significand(var, 3) ^= -1, __hybrid_int128_vec32_significand(var, 2) ^= -1, __hybrid_int128_vec32_significand(var, 1) ^= -1, __hybrid_int128_vec16_significand(var, 1) ^= -1) : (void)0)
#define __hybrid_int128_xor32(var, v)  (__hybrid_uint128_vec32_significand(var, 0) ^= (v), (v) < 0 ? (void)(__hybrid_int128_vec32_significand(var, 3) ^= -1, __hybrid_int128_vec32_significand(var, 2) ^= -1, __hybrid_int128_vec32_significand(var, 1) ^= -1) : (void)0)
#endif /* !__UINT64_TYPE__ || __SIZEOF_BUSINT__ < 8 */



#if defined(__UINT64_TYPE__) && __SIZEOF_BUSINT__ >= 8
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
	       --__hybrid_uint128_vec64_significand(var, 1),                             \
	       __hybrid_uint128_vec64_significand(var, 1) += __hybrid_uint128_vec64_significand(v, 1))
#else /* __UINT64_TYPE__ && __SIZEOF_BUSINT__ >= 8 */
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
#define __hybrid_uint128_add128(var, v)                                              \
	(void)(!__hybrid_overflow_uadd32(__hybrid_uint128_vec32_significand(var, 0),     \
	                                 __hybrid_uint128_vec32_significand(v, 0),       \
	                                 &__hybrid_uint128_vec32_significand(var, 0)) || \
	       ++__hybrid_uint128_vec32_significand(var, 1) != 0 ||                      \
	       ++__hybrid_uint128_vec32_significand(var, 2) != 0 ||                      \
	       (++__hybrid_uint128_vec32_significand(var, 3), 0),                        \
	       !__hybrid_overflow_uadd32(__hybrid_uint128_vec32_significand(var, 1),     \
	                                 __hybrid_uint128_vec32_significand(v, 1),       \
	                                 &__hybrid_uint128_vec32_significand(var, 1)) || \
	       ++__hybrid_uint128_vec32_significand(var, 2) != 0 ||                      \
	       (++__hybrid_uint128_vec32_significand(var, 3), 0),                        \
	       !__hybrid_overflow_uadd32(__hybrid_uint128_vec32_significand(var, 2),     \
	                                 __hybrid_uint128_vec32_significand(v, 2),       \
	                                 &__hybrid_uint128_vec32_significand(var, 2)) || \
	       (++__hybrid_uint128_vec32_significand(var, 3), 0),                        \
	       __hybrid_uint128_vec32_significand(var, 3) += __hybrid_uint128_vec32_significand(v, 3))
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
#define __hybrid_uint128_sub128(var, v)                                              \
	(void)(!__hybrid_overflow_usub32(__hybrid_uint128_vec32_significand(var, 0),     \
	                                 __hybrid_uint128_vec32_significand(v, 0),       \
	                                 &__hybrid_uint128_vec32_significand(var, 0)) || \
	       --__hybrid_uint128_vec32_significand(var, 1) != __UINT32_C(0xffffffff) || \
	       --__hybrid_uint128_vec32_significand(var, 2) != __UINT32_C(0xffffffff) || \
	       (--__hybrid_uint128_vec32_significand(var, 3), 0),                        \
	       !__hybrid_overflow_uadd32(__hybrid_uint128_vec32_significand(var, 1),     \
	                                 __hybrid_uint128_vec32_significand(v, 1),       \
	                                 &__hybrid_uint128_vec32_significand(var, 1)) || \
	       --__hybrid_uint128_vec32_significand(var, 2) != __UINT32_C(0xffffffff) || \
	       (--__hybrid_uint128_vec32_significand(var, 3), 0),                        \
	       !__hybrid_overflow_uadd32(__hybrid_uint128_vec32_significand(var, 2),     \
	                                 __hybrid_uint128_vec32_significand(v, 2),       \
	                                 &__hybrid_uint128_vec32_significand(var, 2)) || \
	       (--__hybrid_uint128_vec32_significand(var, 3), 0),                        \
	       __hybrid_uint128_vec32_significand(var, 3) -= __hybrid_uint128_vec32_significand(v, 3))
#endif /* !__UINT64_TYPE__ || __SIZEOF_BUSINT__ < 8 */

#define __hybrid_int128_add8(var, v)  ((__INT8_TYPE__)(v) >= 0 ? __hybrid_uint128_add8(var, v) : __hybrid_uint128_sub8(var, -(v)))
#define __hybrid_int128_add16(var, v) ((__INT16_TYPE__)(v) >= 0 ? __hybrid_uint128_add16(var, v) : __hybrid_uint128_sub16(var, -(v)))
#define __hybrid_int128_add32(var, v) ((__INT32_TYPE__)(v) >= 0 ? __hybrid_uint128_add32(var, v) : __hybrid_uint128_sub32(var, -(v)))
#define __hybrid_int128_sub8(var, v)  ((__INT8_TYPE__)(v) >= 0 ? __hybrid_uint128_sub8(var, v) : __hybrid_uint128_add8(var, -(v)))
#define __hybrid_int128_sub16(var, v) ((__INT16_TYPE__)(v) >= 0 ? __hybrid_uint128_sub16(var, v) : __hybrid_uint128_add16(var, -(v)))
#define __hybrid_int128_sub32(var, v) ((__INT32_TYPE__)(v) >= 0 ? __hybrid_uint128_sub32(var, v) : __hybrid_uint128_add32(var, -(v)))
#ifdef __UINT64_TYPE__
#define __hybrid_int128_add64(var, v) ((__INT64_TYPE__)(v) >= 0 ? __hybrid_uint128_add64(var, v) : __hybrid_uint128_sub64(var, -(v)))
#define __hybrid_int128_sub64(var, v) ((__INT64_TYPE__)(v) >= 0 ? __hybrid_uint128_sub64(var, v) : __hybrid_uint128_add64(var, -(v)))
#endif /* __UINT64_TYPE__ */
#define __hybrid_int128_add128(var, v) (__hybrid_int128_isneg(v) ? __hybrid_uint128_sub128_neg((__hybrid_uint128_t *)&(var), (__hybrid_int128_t const *)&(v)) : __hybrid_uint128_add128(var, v))
#define __hybrid_int128_sub128(var, v) (__hybrid_int128_isneg(v) ? __hybrid_uint128_add128_neg((__hybrid_uint128_t *)&(var), (__hybrid_int128_t const *)&(v)) : __hybrid_uint128_sub128(var, v))


#define __HYBRID_PRIVATE_UINT128_MULN_BITINT(v, i) (((v) >> (i)) & 1)
#define __HYBRID_PRIVATE_UINT128_MULN_BIT128(v, i) (((v).__i128_u32[(i) / 32] >> ((i) % 32)) & 1)
#define __HYBRID_PRIVATE_UINT128_MULN(T, var, n, v, v_bit, shl)      \
	do {                                                             \
		unsigned int _i128_muli;                                     \
		T _i128_mulres, _i128_multmp;                                \
		__hybrid_int128_setzero(_i128_mulres);                       \
		for (_i128_muli = 0; _i128_muli < n; ++_i128_muli) {         \
			if (v_bit(v, _i128_muli)) {                              \
				_i128_multmp = (var);                                \
				shl(_i128_multmp, _i128_muli);                       \
				__hybrid_uint128_add128(_i128_mulres, _i128_multmp); \
			}                                                        \
		}                                                            \
		(var) = _i128_mulres;                                        \
	}	__WHILE0
#define __HYBRID_PRIVATE_INT128_MULN(var, n, v, v_bit, shl)          \
	do {                                                             \
		__UINT##n##_TYPE__ _abs_v = (__UINT##n##_TYPE__)(v);         \
		__BOOL _i128_isneg        = __hybrid_int128_isneg(var);      \
		if ((__INT##n##_TYPE__)_abs_v < (__INT##n##_TYPE__)0) {      \
			_abs_v = (__UINT##n##_TYPE__)-(__INT##n##_TYPE__)_abs_v; \
			_i128_isneg = !_i128_isneg;                              \
		}                                                            \
		if (_i128_isneg)                                             \
			__hybrid_int128_neg(var);                                \
		__HYBRID_PRIVATE_UINT128_MULN(__hybrid_int128_t, var,        \
		                              n, _abs_v, v_bit, shl);        \
		if (_i128_isneg)                                             \
			__hybrid_int128_neg(var);                                \
	}	__WHILE0

#define __hybrid_uint128_mul8(var, v)                __HYBRID_PRIVATE_UINT128_MULN(__hybrid_uint128_t, var, 8, (__UINT8_TYPE__)(v), __HYBRID_PRIVATE_UINT128_MULN_BITINT, __hybrid_uint128_shl32)
#define __hybrid_uint128_mul16(var, v)               __HYBRID_PRIVATE_UINT128_MULN(__hybrid_uint128_t, var, 16, (__UINT16_TYPE__)(v), __HYBRID_PRIVATE_UINT128_MULN_BITINT, __hybrid_uint128_shl32)
#define __hybrid_uint128_mul32(var, v)               __HYBRID_PRIVATE_UINT128_MULN(__hybrid_uint128_t, var, 32, (__UINT32_TYPE__)(v), __HYBRID_PRIVATE_UINT128_MULN_BITINT, __hybrid_uint128_shl32)
#ifdef __UINT64_TYPE__
#define __hybrid_uint128_mul64(var, v)               __HYBRID_PRIVATE_UINT128_MULN(__hybrid_uint128_t, var, 64, (__UINT64_TYPE__)(v), __HYBRID_PRIVATE_UINT128_MULN_BITINT, __hybrid_uint128_shl64)
#endif /* __UINT64_TYPE__ */
#define __hybrid_uint128_mul128(var, v)              __HYBRID_PRIVATE_UINT128_MULN(__hybrid_uint128_t, var, 128, v, __HYBRID_PRIVATE_UINT128_MULN_BIT128, __hybrid_uint128_shl)
#define __hybrid_int128_mul8(var, v)                 __HYBRID_PRIVATE_INT128_MULN(var, 8, (__UINT8_TYPE__)(v), __HYBRID_PRIVATE_UINT128_MULN_BITINT, __hybrid_uint128_shl32)
#define __hybrid_int128_mul16(var, v)                __HYBRID_PRIVATE_INT128_MULN(var, 16, (__UINT16_TYPE__)(v), __HYBRID_PRIVATE_UINT128_MULN_BITINT, __hybrid_uint128_shl32)
#define __hybrid_int128_mul32(var, v)                __HYBRID_PRIVATE_INT128_MULN(var, 32, (__UINT32_TYPE__)(v), __HYBRID_PRIVATE_UINT128_MULN_BITINT, __hybrid_uint128_shl32)
#ifdef __UINT64_TYPE__
#define __hybrid_int128_mul64(var, v)                __HYBRID_PRIVATE_INT128_MULN(var, 64, (__UINT64_TYPE__)(v), __HYBRID_PRIVATE_UINT128_MULN_BITINT, __hybrid_uint128_shl64)
#endif /* __UINT64_TYPE__ */
#define __hybrid_int128_mul128(var, v)                                      \
	do {                                                                    \
		__hybrid_int128_t _abs_v = (v);                                     \
		__BOOL _i128_isneg = __hybrid_int128_isneg(var);                    \
		if (__hybrid_int128_isneg(_abs_v)) {                                \
			__hybrid_int128_neg(_abs_v);                                    \
			_i128_isneg = !_i128_isneg;                                     \
		}                                                                   \
		if (_i128_isneg)                                                    \
			__hybrid_int128_neg(var);                                       \
		__HYBRID_PRIVATE_UINT128_MULN(__hybrid_int128_t, var, 128, _abs_v,  \
		                              __HYBRID_PRIVATE_UINT128_MULN_BIT128, \
		                              __hybrid_uint128_shl);                \
		if (_i128_isneg)                                                    \
			__hybrid_int128_neg(var);                                       \
	}	__WHILE0

#define __hybrid_uint128_div8(var, v)   TODO
#define __hybrid_uint128_div16(var, v)  TODO
#define __hybrid_uint128_div32(var, v)  TODO
#define __hybrid_uint128_div64(var, v)  TODO
#define __hybrid_uint128_div128(var, v) TODO
#define __hybrid_int128_div8(var, v)    TODO
#define __hybrid_int128_div16(var, v)   TODO
#define __hybrid_int128_div32(var, v)   TODO
#define __hybrid_int128_div64(var, v)   TODO
#define __hybrid_int128_div128(var, v)  TODO
#define __hybrid_uint128_mod8(var, v)   TODO
#define __hybrid_uint128_mod16(var, v)  TODO
#define __hybrid_uint128_mod32(var, v)  TODO
#define __hybrid_uint128_mod64(var, v)  TODO
#define __hybrid_uint128_mod128(var, v) TODO
#define __hybrid_int128_mod8(var, v)    TODO
#define __hybrid_int128_mod16(var, v)   TODO
#define __hybrid_int128_mod32(var, v)   TODO
#define __hybrid_int128_mod64(var, v)   TODO
#define __hybrid_int128_mod128(var, v)  TODO

#define __hybrid_uint128_shl32_overflows(var, shift) \
	((__hybrid_uint128_vec32_significand(var, 3) >> (32 - (shift))) != 0)
#ifdef __UINT64_TYPE__
/* Unsigned <<= shift-left for `shift < 64' */
#define __hybrid_uint128_shl64(var, shift)                                                       \
	(__hybrid_uint128_vec64_significand(var, 1) <<= (shift),                                     \
	 __hybrid_uint128_vec64_significand(var, 1) |= (__hybrid_uint128_vec64_significand(var, 0) & \
	                                                ((__UINT64_C(1) << (64 - (shift))) - 1)) >>  \
	                                               (64 - (shift)),                               \
	 __hybrid_uint128_vec64_significand(var, 0) <<= (shift))
#define __hybrid_uint128_shl64_overflows(var, shift) \
	((__hybrid_uint128_vec64_significand(var, 3) >> (64 - (shift))) != 0)
#define __hybrid_uint128_shl32 __hybrid_uint128_shl64
#else /* __UINT64_TYPE__ */
/* Unsigned <<= shift-left for `shift < 32' */
#define __hybrid_uint128_shl32(var, shift)                                                       \
	(__hybrid_uint128_vec32_significand(var, 3) <<= (shift),                                     \
	 __hybrid_uint128_vec32_significand(var, 3) |= (__hybrid_uint128_vec64_significand(var, 2) & \
	                                                ((__UINT32_C(1) << (32 - (shift))) - 1)) >>  \
	                                               (32 - (shift)),                               \
	 __hybrid_uint128_vec32_significand(var, 2) <<= (shift),                                     \
	 __hybrid_uint128_vec32_significand(var, 2) |= (__hybrid_uint128_vec64_significand(var, 1) & \
	                                                ((__UINT32_C(1) << (32 - (shift))) - 1)) >>  \
	                                               (32 - (shift)),                               \
	 __hybrid_uint128_vec32_significand(var, 1) <<= (shift),                                     \
	 __hybrid_uint128_vec32_significand(var, 1) |= (__hybrid_uint128_vec64_significand(var, 0) & \
	                                                ((__UINT32_C(1) << (32 - (shift))) - 1)) >>  \
	                                               (32 - (shift)),                               \
	 __hybrid_uint128_vec64_significand(var, 0) <<= (shift))
/* Unsigned <<= shift-left for `shift < 64' */
#define __hybrid_uint128_shl64(var, shift)                                                                                      \
	((shift) < 32 ? __hybrid_uint128_shl32(var, shift)                                                                          \
	              : (__hybrid_uint128_vec32_significand(var, 3) = __hybrid_uint128_vec32_significand(var, 2) << ((shift) % 32), \
	                 __hybrid_uint128_vec32_significand(var, 2) = __hybrid_uint128_vec32_significand(var, 1) << ((shift) % 32), \
	                 __hybrid_uint128_vec32_significand(var, 1) = __hybrid_uint128_vec32_significand(var, 0) << ((shift) % 32), \
	                 __hybrid_uint128_vec32_significand(var, 0) = 0))
#define __hybrid_uint128_shl64_overflows(var, shift)                    \
	((shift) < 32 ? __hybrid_uint128_shl32_overflows(var, shift)        \
	              : (__hybrid_uint128_vec32_significand(var, 3) != 0 || \
	                 (__hybrid_uint128_vec32_significand(var, 2) >> (32 - ((shift) % 32))) != 0))
#endif /* !__UINT64_TYPE__ */

/* Unsigned <<= shift-left for `shift < 128' */
#ifdef __UINT64_TYPE__
#define __hybrid_uint128_shl(var, shift)                                                                                        \
	((shift) < 64 ? __hybrid_uint128_shl64(var, shift)                                                                          \
	              : (__hybrid_uint128_vec64_significand(var, 1) = __hybrid_uint128_vec64_significand(var, 0) << ((shift) % 64), \
	                 __hybrid_uint128_vec64_significand(var, 0) = 0))
#define __hybrid_uint128_shl_overflows(var, shift)                                                                                        \
	((shift) < 64 ? __hybrid_uint128_shl64_overflows(var, shift)        \
	              : (__hybrid_uint128_vec64_significand(var, 1) != 0 || \
	                 (__hybrid_uint128_vec64_significand(var, 0) >> (64 - ((shift) % 64))) != 0))
#else /* __UINT64_TYPE__ */
#define __hybrid_uint128_shl(var, shift)                                                                                                        \
	((shift) < 64 ? __hybrid_uint128_shl64(var, shift)                                                                                          \
	              : ((shift) < 96 ? (__hybrid_uint128_vec32_significand(var, 3) = __hybrid_uint128_vec32_significand(var, 1) << ((shift) % 32), \
	                                 __hybrid_uint128_vec32_significand(var, 2) = __hybrid_uint128_vec32_significand(var, 0) << ((shift) % 32)) \
	                              : (__hybrid_uint128_vec32_significand(var, 3) = __hybrid_uint128_vec32_significand(var, 0) << ((shift) % 32), \
	                                 __hybrid_uint128_vec32_significand(var, 2) = 0),                                                           \
	                 __hybrid_uint128_vec32_significand(var, 1) = 0,                                                                            \
	                 __hybrid_uint128_vec32_significand(var, 0) = 0))
#define __hybrid_uint128_shl_overflows(var, shift)                                                              \
	((shift) < 64 ? __hybrid_uint128_shl64_overflows(var, shift)                                                \
	              : (__hybrid_uint128_vec32_significand(var, 3) != 0 ||                                         \
	                 __hybrid_uint128_vec32_significand(var, 2) != 0 ||                                         \
	                 ((shift) < 96 ? (__hybrid_uint128_vec32_significand(var, 1) >> (32 - ((shift) % 32))) != 0 \
	                               : (__hybrid_uint128_vec32_significand(var, 1) != 0 ||                        \
	                                  __hybrid_uint128_vec32_significand(var, 0) >> (32 - ((shift) % 32))) != 0)))
#endif /* !__UINT64_TYPE__ */

/* Signed <<= shift-left */
#define __hybrid_int128_shl __hybrid_uint128_shl
#define __hybrid_int128_shl_overflows __hybrid_uint128_shl_overflows
#define __hybrid_int128_shl32 __hybrid_uint128_shl32
#define __hybrid_int128_shl32_overflows __hybrid_uint128_shl32_overflows
#define __hybrid_int128_shl64 __hybrid_uint128_shl64
#define __hybrid_int128_shl64_overflows __hybrid_uint128_shl64_overflows

#define __hybrid_uint128_shr32_overflows(var, shift) \
	((__hybrid_int128_vec32_significand(var, 0) & ((__UINT32_C(1) << (shift)) - 1)) != 0)
#ifdef __UINT64_TYPE__
/* Unsigned >>= shift-right for `shift < 64' */
#define __hybrid_uint128_shr64(var, shift)                                                       \
	(__hybrid_uint128_vec64_significand(var, 0) >>= (shift),                                     \
	 __hybrid_uint128_vec64_significand(var, 0) |= (__hybrid_uint128_vec64_significand(var, 1) & \
	                                                ((__UINT64_C(1) << (shift)) - 1))            \
	                                               << (64 - (shift)),                            \
	 __hybrid_uint128_vec64_significand(var, 1) >>= (shift))
#define __hybrid_uint128_shr64_overflows(var, shift) \
	((__hybrid_int128_vec64_significand(var, 0) & ((__UINT64_C(1) << (shift)) - 1)) != 0)
#define __hybrid_uint128_shr32 __hybrid_uint128_shr64
#else /* __UINT64_TYPE__ */
/* Unsigned >>= shift-right for `shift < 32' */
#define __hybrid_uint128_shr32(var, shift)                                                       \
	(__hybrid_uint128_vec32_significand(var, 0) >>= (shift),                                     \
	 __hybrid_uint128_vec32_significand(var, 0) |= (__hybrid_uint128_vec32_significand(var, 1) & \
	                                                ((__UINT32_C(1) << (shift)) - 1))            \
	                                               << (32 - (shift)),                            \
	 __hybrid_uint128_vec32_significand(var, 1) >>= (shift),                                     \
	 __hybrid_uint128_vec32_significand(var, 1) |= (__hybrid_uint128_vec32_significand(var, 2) & \
	                                                ((__UINT32_C(1) << (shift)) - 1))            \
	                                               << (32 - (shift)),                            \
	 __hybrid_uint128_vec32_significand(var, 2) >>= (shift),                                     \
	 __hybrid_uint128_vec32_significand(var, 2) |= (__hybrid_uint128_vec32_significand(var, 3) & \
	                                                ((__UINT32_C(1) << (shift)) - 1))            \
	                                               << (32 - (shift)),                            \
	 __hybrid_uint128_vec32_significand(var, 3) >>= (shift))
/* Unsigned >>= shift-right for `shift < 64' */
#define __hybrid_uint128_shr64(var, shift)                                                                                      \
	((shift) < 32 ? __hybrid_uint128_shr32(var, shift)                                                                          \
	              : (__hybrid_uint128_vec32_significand(var, 0) = __hybrid_uint128_vec32_significand(var, 1) >> ((shift) % 32), \
	                 __hybrid_uint128_vec32_significand(var, 1) = __hybrid_uint128_vec32_significand(var, 2) >> ((shift) % 32), \
	                 __hybrid_uint128_vec32_significand(var, 2) = __hybrid_uint128_vec32_significand(var, 3) >> ((shift) % 32), \
	                 __hybrid_uint128_vec32_significand(var, 3) = 0))
#define __hybrid_uint128_shr64_overflows(var, shift)                    \
	((shift) < 32 ? __hybrid_uint128_shr32_overflows(var, shift)        \
	              : (__hybrid_uint128_vec32_significand(var, 0) != 0 || \
	                 (__hybrid_uint128_vec32_significand(var, 1) & ((__UINT32_C(1) << ((shift) % 32)) - 1)) != 0))
#endif /* !__UINT64_TYPE__ */

/* Unsigned >>= shift-right for `shift < 128' */
#ifdef __UINT64_TYPE__
#define __hybrid_uint128_shr(var, shift)                                                                                        \
	((shift) < 64 ? __hybrid_uint128_shr64(var, shift)                                                                          \
	              : (__hybrid_uint128_vec64_significand(var, 0) = __hybrid_uint128_vec64_significand(var, 1) >> ((shift) % 64), \
	                 __hybrid_uint128_vec64_significand(var, 1) = 0))
#define __hybrid_uint128_shr_overflows(var, shift)                                                                                        \
	((shift) < 64 ? __hybrid_uint128_shr64_overflows(var, shift)        \
	              : (__hybrid_uint128_vec64_significand(var, 0) != 0 || \
	                 (__hybrid_uint128_vec64_significand(var, 1) & ((__UINT64_C(1) << ((shift) % 64)) - 1)) != 0))
#else /* __UINT64_TYPE__ */
#define __hybrid_uint128_shr(var, shift)                                                                                                        \
	((shift) < 64 ? __hybrid_uint128_shr64(var, shift)                                                                                          \
	              : ((shift) < 96 ? (__hybrid_uint128_vec32_significand(var, 0) = __hybrid_uint128_vec32_significand(var, 2) >> ((shift) % 32), \
	                                 __hybrid_uint128_vec32_significand(var, 1) = __hybrid_uint128_vec32_significand(var, 3) >> ((shift) % 32)) \
	                              : (__hybrid_uint128_vec32_significand(var, 0) = __hybrid_uint128_vec32_significand(var, 3) >> ((shift) % 32), \
	                                 __hybrid_uint128_vec32_significand(var, 1) = 0),                                                           \
	                 __hybrid_uint128_vec32_significand(var, 2) = 0,                                                                            \
	                 __hybrid_uint128_vec32_significand(var, 3) = 0))
#define __hybrid_uint128_shr_overflows(var, shift)                                                                               \
	((shift) < 64 ? __hybrid_uint128_shr64_overflows(var, shift)                                                                 \
	              : (__hybrid_uint128_vec32_significand(var, 0) != 0 ||                                                          \
	                 __hybrid_uint128_vec32_significand(var, 1) != 0 ||                                                          \
	                 ((shift) < 96 ? (__hybrid_uint128_vec32_significand(var, 2) & ((__UINT32_C(1) << ((shift) % 32)) - 1)) != 0 \
	                               : (__hybrid_uint128_vec32_significand(var, 2) != 0 ||                                         \
	                                  __hybrid_uint128_vec32_significand(var, 3) & ((__UINT32_C(1) << ((shift) % 32)) - 1)) != 0)))
#endif /* !__UINT64_TYPE__ */


#define __hybrid_int128_shr_overflows   __hybrid_uint128_shr_overflows
#define __hybrid_int128_shr32_overflows __hybrid_uint128_shr32_overflows
#define __hybrid_int128_shr64_overflows __hybrid_uint128_shr64_overflows
#ifdef __UINT64_TYPE__
/* Signed >>= shift-right for `shift < 64' */
#define __hybrid_int128_shr64(var, shift)                                                        \
	(__hybrid_uint128_vec64_significand(var, 0) >>= (shift),                                     \
	 __hybrid_uint128_vec64_significand(var, 0) |= (__hybrid_uint128_vec64_significand(var, 1) & \
	                                                ((__UINT64_C(1) << (shift)) - 1))            \
	                                               << (64 - (shift)),                            \
	 __hybrid_int128_vec64_significand(var, 1) >>= (shift))
#define __hybrid_int128_shr32 __hybrid_int128_shr64
#else /* __UINT64_TYPE__ */
/* Signed >>= shift-right for `shift < 32' */
#define __hybrid_int128_shr32(var, shift)                                                        \
	(__hybrid_uint128_vec32_significand(var, 0) >>= (shift),                                     \
	 __hybrid_uint128_vec32_significand(var, 0) |= (__hybrid_uint128_vec32_significand(var, 1) & \
	                                                ((__UINT32_C(1) << (shift)) - 1))            \
	                                               << (32 - (shift)),                            \
	 __hybrid_uint128_vec32_significand(var, 1) >>= (shift),                                     \
	 __hybrid_uint128_vec32_significand(var, 1) |= (__hybrid_uint128_vec32_significand(var, 2) & \
	                                                ((__UINT32_C(1) << (shift)) - 1))            \
	                                               << (32 - (shift)),                            \
	 __hybrid_uint128_vec32_significand(var, 2) >>= (shift),                                     \
	 __hybrid_uint128_vec32_significand(var, 2) |= (__hybrid_uint128_vec32_significand(var, 3) & \
	                                                ((__UINT32_C(1) << (shift)) - 1))            \
	                                               << (32 - (shift)),                            \
	 __hybrid_int128_vec32_significand(var, 3) >>= (shift))
/* Signed >>= shift-right for `shift < 64' */
#define __hybrid_int128_shr64(var, shift)                                                                                       \
	((shift) < 32 ? __hybrid_int128_shr32(var, shift)                                                                           \
	              : (__hybrid_uint128_vec32_significand(var, 0) = __hybrid_uint128_vec32_significand(var, 1) >> ((shift) % 32), \
	                 __hybrid_uint128_vec32_significand(var, 1) = __hybrid_uint128_vec32_significand(var, 2) >> ((shift) % 32), \
	                 __hybrid_uint128_vec32_significand(var, 2) = __hybrid_uint128_vec32_significand(var, 3) >> ((shift) % 32), \
	                 __hybrid_int128_vec32_significand(var, 3) = __hybrid_int128_isneg(var) ? -1 : 0))
#endif /* !__UINT64_TYPE__ */

/* Signed >>= shift-right for `shift < 128' */
#ifdef __UINT64_TYPE__
#define __hybrid_int128_shr(var, shift)                                                                                         \
	((shift) < 64 ? __hybrid_int128_shr64(var, shift)                                                                           \
	              : (__hybrid_uint128_vec64_significand(var, 0) = __hybrid_uint128_vec64_significand(var, 1) >> ((shift) % 64), \
	                 __hybrid_int128_vec64_significand(var, 1) = __hybrid_int128_isneg(var) ? -1 : 0))
#else /* __UINT64_TYPE__ */
#define __hybrid_int128_shr(var, shift)                                                                                                       \
	((shift) < 64 ? __hybrid_int128_shr64(var, shift)                                                                                         \
	              : ((shift) < 96 ? (__hybrid_int128_vec32_significand(var, 0) = __hybrid_int128_vec32_significand(var, 2) >> ((shift) % 32), \
	                                 __hybrid_int128_vec32_significand(var, 1) = __hybrid_int128_vec32_significand(var, 3) >> ((shift) % 32), \
	                                 __hybrid_int128_vec32_significand(var, 2) = __hybrid_int128_isneg(var) ? -1 : 0,                         \
	                                 __hybrid_int128_vec32_significand(var, 3) = __hybrid_int128_vec32_significand(var, 2))                   \
	                              : (__hybrid_int128_vec32_significand(var, 0) = __hybrid_int128_vec32_significand(var, 3) >> ((shift) % 32), \
	                                 __hybrid_int128_vec32_significand(var, 1) = __hybrid_int128_isneg(var) ? -1 : 0,                         \
	                                 __hybrid_int128_vec32_significand(var, 2) = __hybrid_int128_vec32_significand(var, 1),                   \
	                                 __hybrid_int128_vec32_significand(var, 3) = __hybrid_int128_vec32_significand(var, 1))))
#endif /* !__UINT64_TYPE__ */


#ifdef __UINT64_TYPE__
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
#define __hybrid_int128_iszero_minus_min(var) \
	(__hybrid_int128_vec64_significand(var, 0) == 1 && \
	 __hybrid_int128_vec64_significand(var, 1) == __PRIVATE_MIN_S8)
#define __hybrid_int128_setzero_minus_min(var)            \
	(void)(__hybrid_int128_vec64_significand(var, 0) = 1, \
	       __hybrid_int128_vec64_significand(var, 1) = __PRIVATE_MIN_S8)
#else /* __UINT64_TYPE__ */
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
#define __hybrid_int128_iszero_minus_min(var)          \
	(__hybrid_int128_vec32_significand(var, 0) == 1 && \
	 __hybrid_int128_vec32_significand(var, 1) == 1 && \
	 __hybrid_int128_vec32_significand(var, 2) == 1 && \
	 __hybrid_int128_vec32_significand(var, 3) == __PRIVATE_MIN_S4)
#define __hybrid_int128_setzero_minus_min(var)            \
	(void)(__hybrid_int128_vec32_significand(var, 0) = 1, \
	       __hybrid_int128_vec32_significand(var, 1) = 1, \
	       __hybrid_int128_vec32_significand(var, 2) = 1, \
	       __hybrid_int128_vec32_significand(var, 3) = __PRIVATE_MIN_S4)
#endif /* !__UINT64_TYPE__ */
#define __hybrid_int128_iszero  __hybrid_uint128_iszero
#define __hybrid_int128_setzero __hybrid_uint128_setzero
#define __hybrid_int128_isone   __hybrid_uint128_isone
#define __hybrid_int128_setone  __hybrid_uint128_setone
#define __hybrid_uint128_ismin  __hybrid_uint128_iszero
#define __hybrid_uint128_setmin __hybrid_uint128_setzero
#define __hybrid_uint128_ismax  __hybrid_int128_isminusone
#define __hybrid_uint128_setmax __hybrid_int128_setminusone


#ifdef __UINT64_TYPE__
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
#else /* __UINT64_TYPE__ */
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
#endif /* !__UINT64_TYPE__ */

#define __hybrid_uint128_eq8(var, v)  (__hybrid_uint128_is8bit(var) && __hybrid_uint128_vec8_significand(var, 0) == (__UINT8_TYPE__)(v))
#define __hybrid_uint128_eq16(var, v) (__hybrid_uint128_is16bit(var) && __hybrid_uint128_vec16_significand(var, 0) == (__UINT16_TYPE__)(v))
#define __hybrid_uint128_eq32(var, v) (__hybrid_uint128_is32bit(var) && __hybrid_uint128_vec32_significand(var, 0) == (__UINT32_TYPE__)(v))
#define __hybrid_int128_eq8(var, v)   (__hybrid_int128_is8bit(var) && __hybrid_int128_vec8_significand(var, 0) == (__INT8_TYPE__)(v))
#define __hybrid_int128_eq16(var, v)  (__hybrid_int128_is16bit(var) && __hybrid_int128_vec16_significand(var, 0) == (__INT16_TYPE__)(v))
#define __hybrid_int128_eq32(var, v)  (__hybrid_int128_is32bit(var) && __hybrid_int128_vec32_significand(var, 0) == (__INT32_TYPE__)(v))
#ifdef __UINT64_TYPE__
#define __hybrid_uint128_eq64(var, v) (__hybrid_uint128_is64bit(var) && __hybrid_uint128_vec64_significand(var, 0) == (__UINT64_TYPE__)(v))
#define __hybrid_int128_eq64(var, v)  (__hybrid_int128_is64bit(var) && __hybrid_int128_vec64_significand(var, 0) == (__INT64_TYPE__)(v))
#define __hybrid_int128_eq128(var, v)                                                        \
	(__hybrid_int128_vec64_significand(var, 1) == __hybrid_int128_vec64_significand(v, 1) && \
	 __hybrid_int128_vec64_significand(var, 0) == __hybrid_int128_vec64_significand(v, 0))
#else /* __UINT64_TYPE__ */
#define __hybrid_int128_eq128(var, v)                                                        \
	(__hybrid_int128_vec32_significand(var, 3) == __hybrid_int128_vec32_significand(v, 3) && \
	 __hybrid_int128_vec32_significand(var, 2) == __hybrid_int128_vec32_significand(v, 2) && \
	 __hybrid_int128_vec32_significand(var, 1) == __hybrid_int128_vec32_significand(v, 1) && \
	 __hybrid_int128_vec32_significand(var, 0) == __hybrid_int128_vec32_significand(v, 0))
#endif /* !__UINT64_TYPE__ */
#define __hybrid_uint128_eq128 __hybrid_int128_eq128

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
#ifdef __UINT64_TYPE__
#define __hybrid_uint128_lo64(var, v) (__hybrid_uint128_is64bit(var) && __hybrid_uint128_vec64_significand(var, 0) < (__UINT64_TYPE__)(v))
#define __hybrid_uint128_le64(var, v) (__hybrid_uint128_is64bit(var) && __hybrid_uint128_vec64_significand(var, 0) <= (__UINT64_TYPE__)(v))
#define __hybrid_int128_lo64(var, v)  (__hybrid_int128_is64bit(var) && __hybrid_int128_vec64_significand(var, 0) < (__INT64_TYPE__)(v))
#define __hybrid_int128_le64(var, v)  (__hybrid_int128_is64bit(var) && __hybrid_int128_vec64_significand(var, 0) <= (__INT64_TYPE__)(v))
#define __hybrid_uint128_lo128(var, v)                                                          \
	(__hybrid_uint128_vec64_significand(var, 1) < __hybrid_uint128_vec64_significand(v, 1) ||   \
	 (__hybrid_uint128_vec64_significand(var, 1) == __hybrid_uint128_vec64_significand(v, 1) && \
	  __hybrid_uint128_vec64_significand(var, 0) < __hybrid_uint128_vec64_significand(v, 0)))
#define __hybrid_uint128_le128(var, v)                                                          \
	(__hybrid_uint128_vec64_significand(var, 1) < __hybrid_uint128_vec64_significand(v, 1) ||   \
	 (__hybrid_uint128_vec64_significand(var, 1) == __hybrid_uint128_vec64_significand(v, 1) && \
	  __hybrid_uint128_vec64_significand(var, 0) <= __hybrid_uint128_vec64_significand(v, 0)))
#else /* __UINT64_TYPE__ */
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
#endif /* !__UINT64_TYPE__ */
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
#define __hybrid_int128_and(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_and8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_and16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_and32(var, v), \
	                                      __hybrid_uint128_and64(var, v))))
#define __hybrid_uint128_or(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_or8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_or16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_or32(var, v), \
	                                      __hybrid_uint128_or64(var, v))))
#define __hybrid_int128_or(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_or8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_or16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_or32(var, v), \
	                                      __hybrid_uint128_or64(var, v))))
#define __hybrid_uint128_xor(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_xor8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_xor16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_xor32(var, v), \
	                                      __hybrid_uint128_xor64(var, v))))
#define __hybrid_int128_xor(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_xor8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_xor16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_xor32(var, v), \
	                                      __hybrid_uint128_xor64(var, v))))
#define __hybrid_uint128_add(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_add8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_add16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_add32(var, v), \
	                                      __hybrid_uint128_add64(var, v))))
#define __hybrid_int128_add(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_add8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_add16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_add32(var, v), \
	                                      __hybrid_uint128_add64(var, v))))
#define __hybrid_uint128_sub(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_sub8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_sub16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_sub32(var, v), \
	                                      __hybrid_uint128_sub64(var, v))))
#define __hybrid_int128_sub(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_sub8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_sub16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_sub32(var, v), \
	                                      __hybrid_uint128_sub64(var, v))))
#define __hybrid_uint128_mul(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_mul8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_mul16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_mul32(var, v), \
	                                      __hybrid_uint128_mul64(var, v))))
#define __hybrid_int128_mul(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_mul8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_mul16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_mul32(var, v), \
	                                      __hybrid_uint128_mul64(var, v))))
#define __hybrid_uint128_div(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_div8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_div16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_div32(var, v), \
	                                      __hybrid_uint128_div64(var, v))))
#define __hybrid_int128_div(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_div8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_div16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_div32(var, v), \
	                                      __hybrid_uint128_div64(var, v))))
#define __hybrid_uint128_mod(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_mod8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_mod16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_mod32(var, v), \
	                                      __hybrid_uint128_mod64(var, v))))
#define __hybrid_int128_mod(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_mod8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_mod16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_mod32(var, v), \
	                                      __hybrid_uint128_mod64(var, v))))
#define __hybrid_uint128_eq(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_eq8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_eq16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_eq32(var, v), \
	                                      __hybrid_uint128_eq64(var, v))))
#define __hybrid_int128_eq(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_eq8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_eq16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_eq32(var, v), \
	                                      __hybrid_uint128_eq64(var, v))))
#define __hybrid_uint128_lo(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_lo8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_lo16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_lo32(var, v), \
	                                      __hybrid_uint128_lo64(var, v))))
#define __hybrid_int128_lo(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_lo8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_lo16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_lo32(var, v), \
	                                      __hybrid_uint128_lo64(var, v))))
#define __hybrid_uint128_le(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_le8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_le16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_le32(var, v), \
	                                      __hybrid_uint128_le64(var, v))))
#define __hybrid_int128_le(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_le8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_le16(var, v), \
	__builtin_choose_expr(sizeof(v) == 4, __hybrid_uint128_le32(var, v), \
	                                      __hybrid_uint128_le64(var, v))))
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
#define __hybrid_int128_and(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_and8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_and16(var, v), \
	                                      __hybrid_uint128_and32(var, v)))
#define __hybrid_uint128_or(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_or8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_or16(var, v), \
	                                      __hybrid_uint128_or32(var, v)))
#define __hybrid_int128_or(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_or8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_or16(var, v), \
	                                      __hybrid_uint128_or32(var, v)))
#define __hybrid_uint128_xor(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_xor8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_xor16(var, v), \
	                                      __hybrid_uint128_xor32(var, v)))
#define __hybrid_int128_xor(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_xor8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_xor16(var, v), \
	                                      __hybrid_uint128_xor32(var, v)))
#define __hybrid_uint128_add(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_add8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_add16(var, v), \
	                                      __hybrid_uint128_add32(var, v)))
#define __hybrid_int128_add(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_add8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_add16(var, v), \
	                                      __hybrid_uint128_add32(var, v)))
#define __hybrid_uint128_sub(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_sub8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_sub16(var, v), \
	                                      __hybrid_uint128_sub32(var, v)))
#define __hybrid_int128_sub(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_sub8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_sub16(var, v), \
	                                      __hybrid_uint128_sub32(var, v)))
#define __hybrid_uint128_mul(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_mul8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_mul16(var, v), \
	                                      __hybrid_uint128_mul32(var, v)))
#define __hybrid_int128_mul(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_mul8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_mul16(var, v), \
	                                      __hybrid_uint128_mul32(var, v)))
#define __hybrid_uint128_div(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_div8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_div16(var, v), \
	                                      __hybrid_uint128_div32(var, v)))
#define __hybrid_int128_div(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_div8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_div16(var, v), \
	                                      __hybrid_uint128_div32(var, v)))
#define __hybrid_uint128_mod(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_mod8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_mod16(var, v), \
	                                      __hybrid_uint128_mod32(var, v)))
#define __hybrid_int128_mod(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_mod8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_mod16(var, v), \
	                                      __hybrid_uint128_mod32(var, v)))
#define __hybrid_uint128_eq(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_eq8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_eq16(var, v), \
	                                      __hybrid_uint128_eq32(var, v)))
#define __hybrid_int128_eq(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_eq8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_eq16(var, v), \
	                                      __hybrid_uint128_eq32(var, v)))
#define __hybrid_uint128_lo(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_lo8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_lo16(var, v), \
	                                      __hybrid_uint128_lo32(var, v)))
#define __hybrid_int128_lo(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_lo8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_lo16(var, v), \
	                                      __hybrid_uint128_lo32(var, v)))
#define __hybrid_uint128_le(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_le8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_le16(var, v), \
	                                      __hybrid_uint128_le32(var, v)))
#define __hybrid_int128_le(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_le8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_le16(var, v), \
	                                      __hybrid_uint128_le32(var, v)))
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
	__CXX_CLASSMEMBER __hybrid_int128_struct &operator = (__hybrid_uint128_struct const &__v) __CXX_NOEXCEPT;
	template<class __ValType> __CXX_CLASSMEMBER explicit __hybrid_int128_struct(__ValType __v, __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, int *) = 0) __CXX_NOEXCEPT { __hybrid_int128_set(*this, __v); }
	template<class __ValType> __CXX_CLASSMEMBER explicit __hybrid_int128_struct(__ValType __v, __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, int *) = 0) __CXX_NOEXCEPT { __hybrid_uint128_set(*this, __v); }
	template<class __ValType> __CXX_CLASSMEMBER __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, __hybrid_int128_struct &) operator = (__ValType __v) __CXX_NOEXCEPT { __hybrid_int128_set(*this, __v); return *this; }
	template<class __ValType> __CXX_CLASSMEMBER __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, __hybrid_int128_struct &) operator = (__ValType __v) __CXX_NOEXCEPT { __hybrid_uint128_set(*this, __v); return *this; }
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
	__CXX_CLASSMEMBER __hybrid_uint128_struct &operator = (__hybrid_int128_struct const &__v) __CXX_NOEXCEPT;
	template<class __ValType> __CXX_CLASSMEMBER explicit __hybrid_uint128_struct(__ValType __v, __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, int *) = 0) __CXX_NOEXCEPT { __hybrid_int128_set(*this, __v); }
	template<class __ValType> __CXX_CLASSMEMBER explicit __hybrid_uint128_struct(__ValType __v, __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, int *) = 0) __CXX_NOEXCEPT { __hybrid_uint128_set(*this, __v); }
	template<class __ValType> __CXX_CLASSMEMBER __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, __hybrid_uint128_struct &) operator = (__ValType __v) __CXX_NOEXCEPT { __hybrid_int128_set(*this, __v); return *this; }
	template<class __ValType> __CXX_CLASSMEMBER __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, __hybrid_uint128_struct &) operator = (__ValType __v) __CXX_NOEXCEPT { __hybrid_uint128_set(*this, __v); return *this; }
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


__LOCAL __ATTR_NONNULL((1, 2)) void
(__hybrid_uint128_add128_neg)(__hybrid_uint128_t *__var, __hybrid_int128_t const *__v) {
	__hybrid_uint128_t __negv;
#ifdef __UINT64_TYPE__
	__negv.__i128_u64[0] = __v->__i128_u64[0];
	__negv.__i128_u64[1] = __v->__i128_u64[1];
#else /* __UINT64_TYPE__ */
	__negv.__i128_u32[0] = __v->__i128_u32[0];
	__negv.__i128_u32[1] = __v->__i128_u32[1];
	__negv.__i128_u32[2] = __v->__i128_u32[2];
	__negv.__i128_u32[3] = __v->__i128_u32[3];
#endif /* !__UINT64_TYPE__ */
	__hybrid_int128_neg(__negv);
	__hybrid_uint128_add128(*__var, __negv);
}

__LOCAL __ATTR_NONNULL((1, 2)) void
(__hybrid_uint128_sub128_neg)(__hybrid_uint128_t *__var, __hybrid_int128_t const *__v) {
	__hybrid_uint128_t __negv;
#ifdef __UINT64_TYPE__
	__negv.__i128_u64[0] = __v->__i128_u64[0];
	__negv.__i128_u64[1] = __v->__i128_u64[1];
#else /* __UINT64_TYPE__ */
	__negv.__i128_u32[0] = __v->__i128_u32[0];
	__negv.__i128_u32[1] = __v->__i128_u32[1];
	__negv.__i128_u32[2] = __v->__i128_u32[2];
	__negv.__i128_u32[3] = __v->__i128_u32[3];
#endif /* !__UINT64_TYPE__ */
	__hybrid_int128_neg(__negv);
	__hybrid_uint128_sub128(*__var, __negv);
}


#if defined(__cplusplus) && defined(WANT_INT128_CXX_INTEGRATION)
__CXX_CLASSMEMBER __hybrid_int128_struct::
__hybrid_int128_struct(__hybrid_uint128_struct const &__v) __CXX_NOEXCEPT {
	__i128_u32[0] = __v.__i128_u32[0];
	__i128_u32[1] = __v.__i128_u32[1];
	__i128_u32[2] = __v.__i128_u32[2];
	__i128_u32[3] = __v.__i128_u32[3];
}
__CXX_CLASSMEMBER __hybrid_int128_struct &__hybrid_int128_struct::
operator = (__hybrid_uint128_struct const &__v) __CXX_NOEXCEPT {
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
operator = (__hybrid_int128_struct const &__v) __CXX_NOEXCEPT {
	__i128_u32[0] = __v.__i128_u32[0];
	__i128_u32[1] = __v.__i128_u32[1];
	__i128_u32[2] = __v.__i128_u32[2];
	__i128_u32[3] = __v.__i128_u32[3];
	return *this;
}

__LOCAL __ATTR_WUNUSED __ATTR_PURE __hybrid_int128_t operator - (__hybrid_int128_t const &__self) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __hybrid_int128_neg(__res); return __res; }
__LOCAL __ATTR_WUNUSED __ATTR_PURE __hybrid_int128_t operator ~ (__hybrid_int128_t const &__self) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __hybrid_int128_inv(__res); return __res; }
__LOCAL __ATTR_WUNUSED __ATTR_PURE __hybrid_uint128_t operator ~ (__hybrid_uint128_t const &__self) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __hybrid_uint128_inv(__res); return __res; }
__LOCAL __hybrid_int128_t &operator ++ (__hybrid_int128_t &__self) __CXX_NOEXCEPT { __hybrid_int128_inc(__self); return __self; }
__LOCAL __hybrid_int128_t operator ++ (__hybrid_int128_t &__self, int) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __hybrid_int128_inc(__self); return __res; }
__LOCAL __hybrid_int128_t &operator -- (__hybrid_int128_t &__self) __CXX_NOEXCEPT { __hybrid_int128_dec(__self); return __self; }
__LOCAL __hybrid_int128_t operator -- (__hybrid_int128_t &__self, int) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __hybrid_int128_dec(__self); return __res; }
__LOCAL __hybrid_uint128_t &operator ++ (__hybrid_uint128_t &__self) __CXX_NOEXCEPT { __hybrid_uint128_inc(__self); return __self; }
__LOCAL __hybrid_uint128_t operator ++ (__hybrid_uint128_t &__self, int) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __hybrid_uint128_inc(__self); return __res; }
__LOCAL __hybrid_uint128_t &operator -- (__hybrid_uint128_t &__self) __CXX_NOEXCEPT { __hybrid_uint128_dec(__self); return __self; }
__LOCAL __hybrid_uint128_t operator -- (__hybrid_uint128_t &__self, int) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __hybrid_uint128_dec(__self); return __res; }
#define __HYBRID_INT128_DEFINE_BINARY_CXX_OPERATOR(op, name)                                                                                                                                                                                                                          \
	template<class __ValType> __LOCAL __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, __hybrid_uint128_t &) operator op##= (__hybrid_uint128_t &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_uint128_##name(__self, __v); return __self; }                                          \
	template<class __ValType> __LOCAL __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, __hybrid_int128_t &) operator op##= (__hybrid_int128_t &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_uint128_##name(__self, __v); return __self; }                                            \
	template<class __ValType> __LOCAL __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, __hybrid_uint128_t &) operator op##= (__hybrid_uint128_t &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_int128_##name(__self, __v); return __self; }                                             \
	template<class __ValType> __LOCAL __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, __hybrid_int128_t &) operator op##= (__hybrid_int128_t &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_int128_##name(__self, __v); return __self; }                                               \
	template<class __ValType> __LOCAL __ATTR_WUNUSED __ATTR_PURE __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, __hybrid_uint128_t) operator op (__hybrid_uint128_t const &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __res op##= __v; return __res; } \
	template<class __ValType> __LOCAL __ATTR_WUNUSED __ATTR_PURE __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, __hybrid_int128_t) operator op (__hybrid_int128_t const &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __res op##= __v; return __res; }    \
	template<class __ValType> __LOCAL __ATTR_WUNUSED __ATTR_PURE __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, __hybrid_uint128_t) operator op (__hybrid_uint128_t const &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __res op##= __v; return __res; }   \
	template<class __ValType> __LOCAL __ATTR_WUNUSED __ATTR_PURE __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, __hybrid_int128_t) operator op (__hybrid_int128_t const &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __res op##= __v; return __res; }      \
	__LOCAL __hybrid_uint128_t &operator op##= (__hybrid_uint128_t &__self, __hybrid_uint128_t const &__v) __CXX_NOEXCEPT { __hybrid_uint128_##name##128(__self, __v); return __self; }                                                                                               \
	__LOCAL __hybrid_uint128_t &operator op##= (__hybrid_uint128_t &__self, __hybrid_int128_t const &__v) __CXX_NOEXCEPT { __hybrid_int128_##name##128(__self, __v); return __self; }                                                                                                 \
	__LOCAL __hybrid_int128_t &operator op##= (__hybrid_int128_t &__self, __hybrid_uint128_t const &__v) __CXX_NOEXCEPT { __hybrid_uint128_##name##128(__self, __v); return __self; }                                                                                                 \
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
	template<class __ValType> __LOCAL __ATTR_WUNUSED __ATTR_PURE __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, bool) operator op (__hybrid_uint128_t const &__self, __ValType __v) __CXX_NOEXCEPT { return __hybrid_uint128_##name(__self, __v); } \
	template<class __ValType> __LOCAL __ATTR_WUNUSED __ATTR_PURE __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, bool) operator np (__hybrid_uint128_t const &__self, __ValType __v) __CXX_NOEXCEPT { return !(__self op __v); }                     \
	template<class __ValType> __LOCAL __ATTR_WUNUSED __ATTR_PURE __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, bool) operator op (__hybrid_int128_t const &__self, __ValType __v) __CXX_NOEXCEPT { return __hybrid_uint128_##name(__self, __v); }  \
	template<class __ValType> __LOCAL __ATTR_WUNUSED __ATTR_PURE __HYBRID_INT128_ENABLE_IF_UNSIGNED(__ValType, bool) operator np (__hybrid_int128_t const &__self, __ValType __v) __CXX_NOEXCEPT { return !(__self op __v); }                      \
	template<class __ValType> __LOCAL __ATTR_WUNUSED __ATTR_PURE __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, bool) operator op (__hybrid_uint128_t const &__self, __ValType __v) __CXX_NOEXCEPT { return __hybrid_int128_##name(__self, __v); }    \
	template<class __ValType> __LOCAL __ATTR_WUNUSED __ATTR_PURE __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, bool) operator np (__hybrid_uint128_t const &__self, __ValType __v) __CXX_NOEXCEPT { return !(__self op __v); }                       \
	template<class __ValType> __LOCAL __ATTR_WUNUSED __ATTR_PURE __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, bool) operator op (__hybrid_int128_t const &__self, __ValType __v) __CXX_NOEXCEPT { return __hybrid_int128_##name(__self, __v); }     \
	template<class __ValType> __LOCAL __ATTR_WUNUSED __ATTR_PURE __HYBRID_INT128_ENABLE_IF_SIGNED(__ValType, bool) operator np (__hybrid_int128_t const &__self, __ValType __v) __CXX_NOEXCEPT { return !(__self op __v); }                        \
	__LOCAL __ATTR_WUNUSED __ATTR_PURE bool operator op (__hybrid_int128_t const &__self, __hybrid_int128_t const &__v) __CXX_NOEXCEPT { return __hybrid_int128_##name##128(__self, __v); }                                                        \
	__LOCAL __ATTR_WUNUSED __ATTR_PURE bool operator op (__hybrid_int128_t const &__self, __hybrid_uint128_t const &__v) __CXX_NOEXCEPT { return __hybrid_int128_##name##128(__self, __v); }                                                       \
	__LOCAL __ATTR_WUNUSED __ATTR_PURE bool operator np (__hybrid_int128_t const &__self, __hybrid_int128_t const &__v) __CXX_NOEXCEPT { return !(__self op __v); }                                                                                \
	__LOCAL __ATTR_WUNUSED __ATTR_PURE bool operator np (__hybrid_int128_t const &__self, __hybrid_uint128_t const &__v) __CXX_NOEXCEPT { return !(__self op __v); }                                                                               \
	__LOCAL __ATTR_WUNUSED __ATTR_PURE bool operator op (__hybrid_uint128_t const &__self, __hybrid_int128_t const &__v) __CXX_NOEXCEPT { return __hybrid_uint128_##name##128(__self, __v); }                                                      \
	__LOCAL __ATTR_WUNUSED __ATTR_PURE bool operator op (__hybrid_uint128_t const &__self, __hybrid_uint128_t const &__v) __CXX_NOEXCEPT { return __hybrid_uint128_##name##128(__self, __v); }                                                     \
	__LOCAL __ATTR_WUNUSED __ATTR_PURE bool operator np (__hybrid_uint128_t const &__self, __hybrid_int128_t const &__v) __CXX_NOEXCEPT { return !(__self op __v); }                                                                               \
	__LOCAL __ATTR_WUNUSED __ATTR_PURE bool operator np (__hybrid_uint128_t const &__self, __hybrid_uint128_t const &__v) __CXX_NOEXCEPT { return !(__self op __v); }
__HYBRID_INT128_DEFINE_COMPARE_CXX_OPERATOR(==, !=, eq)
__HYBRID_INT128_DEFINE_COMPARE_CXX_OPERATOR(<, >=, lo)
__HYBRID_INT128_DEFINE_COMPARE_CXX_OPERATOR(<=, >, le)
#undef __HYBRID_INT128_DEFINE_COMPARE_CXX_OPERATOR
__LOCAL __hybrid_int128_t &operator <<= (__hybrid_int128_t &__self, unsigned int __shift) __CXX_NOEXCEPT { __hybrid_int128_shl(__self, __shift); return __self; }
__LOCAL __hybrid_int128_t &operator >>= (__hybrid_int128_t &__self, unsigned int __shift) __CXX_NOEXCEPT { __hybrid_int128_shr(__self, __shift); return __self; }
__LOCAL __hybrid_uint128_t &operator <<= (__hybrid_uint128_t &__self, unsigned int __shift) __CXX_NOEXCEPT { __hybrid_uint128_shl(__self, __shift); return __self; }
__LOCAL __hybrid_uint128_t &operator >>= (__hybrid_uint128_t &__self, unsigned int __shift) __CXX_NOEXCEPT { __hybrid_uint128_shr(__self, __shift); return __self; }
__LOCAL __ATTR_WUNUSED __ATTR_PURE __hybrid_int128_t operator << (__hybrid_int128_t const &__self, unsigned int __shift) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __res <<= __shift; return __res; }
__LOCAL __ATTR_WUNUSED __ATTR_PURE __hybrid_int128_t operator >> (__hybrid_int128_t const &__self, unsigned int __shift) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __res >>= __shift; return __res; }
__LOCAL __ATTR_WUNUSED __ATTR_PURE __hybrid_uint128_t operator << (__hybrid_uint128_t const &__self, unsigned int __shift) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __res <<= __shift; return __res; }
__LOCAL __ATTR_WUNUSED __ATTR_PURE __hybrid_uint128_t operator >> (__hybrid_uint128_t const &__self, unsigned int __shift) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __res >>= __shift; return __res; }
#undef __HYBRID_INT128_ENABLE_IF_SIGNED
#undef __HYBRID_INT128_ENABLE_IF_UNSIGNED
}
#endif /* __cplusplus && WANT_INT128_CXX_INTEGRATION */

__DECL_END

#endif /* !__INT128_TYPE__ || !__UINT128_TYPE__ */

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
