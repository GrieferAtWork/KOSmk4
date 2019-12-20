/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID_INT128_H
#define __GUARD_HYBRID_INT128_H 1

#include "../__stdinc.h"
#include "typecore.h"
#if defined(__cplusplus) && defined(WANT_INT128_CXX_INTEGRATION)
#include "../__stdcxx.h"
#endif /* __cplusplus && WANT_INT128_CXX_INTEGRATION */

#ifdef __CC__
#if defined(__INT128_TYPE__) && defined(__UINT128_TYPE__)
#define __hybrid_int128_t  __INT128_TYPE__
#define __hybrid_uint128_t __UINT128_TYPE__

#define __hybrid_int128_vec8(var)    ((__INT8_TYPE__ *)&(var))
#define __hybrid_int128_vec16(var)   ((__INT16_TYPE__ *)&(var))
#define __hybrid_int128_vec32(var)   ((__INT32_TYPE__ *)&(var))
#define __hybrid_uint128_vec8(var)   ((__UINT8_TYPE__ *)&(var))
#define __hybrid_uint128_vec16(var)  ((__UINT16_TYPE__ *)&(var))
#define __hybrid_uint128_vec32(var)  ((__UINT32_TYPE__ *)&(var))
#define __hybrid_int128_vec64(var)     ((__INT64_TYPE__ *)&(var))
#define __hybrid_uint128_vec64(var)    ((__UINT64_TYPE__ *)&(var))

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
#else
#error "Unsupported byteorder"
#endif

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
#define __hybrid_int128_setmin(var)                  (void)((var) = (__INT128_TYPE__)__PRIVATE_MIN_S16)
#define __hybrid_int128_ismin(var)                   ((var) == (__INT128_TYPE__)__PRIVATE_MIN_S16)
#define __hybrid_int128_setmax(var)                  (void)((var) = (__INT128_TYPE__)__PRIVATE_MIN_S16)
#define __hybrid_int128_ismax(var)                   ((var) == (__INT128_TYPE__)__PRIVATE_MAX_S16)
#define __hybrid_int128_setzero_minus_min(var)       (void)((var) = (__INT128_TYPE__)((__UINT128_TYPE__)0 - __PRIVATE_MIN_S16))
#define __hybrid_int128_iszero_minus_min(var)        ((var) == (__INT128_TYPE__)((__UINT128_TYPE__)0 - __PRIVATE_MIN_S16))
#define __hybrid_uint128_setmin                      __hybrid_uint128_setzero
#define __hybrid_uint128_ismax(var)                  ((var) == (__UINT128_TYPE__)-1)
#define __hybrid_uint128_ismin                       __hybrid_uint128_iszero
#define __hybrid_uint128_setmax(var)                 ((var) == (__UINT128_TYPE__)-1)
#define __hybrid_uint128_is8bit(var)                 ((__UINT128_TYPE__)(var) <= __UINT8_C(0xff))
#define __hybrid_uint128_is16bit(var)                ((__UINT128_TYPE__)(var) <= __UINT8_C(0xffff))
#define __hybrid_uint128_is32bit(var)                ((__UINT128_TYPE__)(var) <= __UINT8_C(0xffffff))
#define __hybrid_uint128_is64bit(var)                ((__UINT128_TYPE__)(var) <= __UINT8_C(0xffffffff))
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

#else /* __INT128_TYPE__ && __UINT128_TYPE__ */

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
#else
#error "Unsupported byteorder"
#endif


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
#else
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
#endif

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
#else
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
#endif

#ifdef __UINT64_TYPE__
#define __hybrid_uint128_inc(var)                               \
	(void)(++__hybrid_uint128_vec64_significand(var, 0) != 0 || \
	       (++__hybrid_uint128_vec64_significand(var, 1), 0))
#define __hybrid_uint128_dec(var)                                                            \
	(void)(--__hybrid_uint128_vec64_significand(var, 0) != __UINT64_C(0xffffffffffffffff) || \
	       (--__hybrid_uint128_vec64_significand(var, 1), 0))
#define __hybrid_uint128_inv(var)                                            \
	(void)(__hybrid_uint128_vec64(var)[0] = ~__hybrid_uint128_vec64(var)[0], \
	       __hybrid_uint128_vec64(var)[1] = ~__hybrid_uint128_vec64(var)[1])
#else /* __UINT64_TYPE__ */
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
#endif /* !__UINT64_TYPE__ */
#define __hybrid_int128_inc __hybrid_uint128_inc
#define __hybrid_int128_dec __hybrid_uint128_dec
#define __hybrid_int128_inv __hybrid_uint128_inv
#define __hybrid_int128_neg(var) (__hybrid_int128_dec(var), __hybrid_int128_inv(var))
#define __hybrid_int128_isneg(var) (__hybrid_uint128_vec8_significand(var, 15) & 0x80)

#ifdef __UINT64_TYPE__
#define __hybrid_uint128_and64(var, v) __hybrid_uint128_set64(var, __hybrid_uint128_get64(var) & (__UINT64_TYPE__)(v))
#define __hybrid_int128_and64(var, v)  __hybrid_int128_set64(var, __hybrid_int128_get64(var) & (__INT64_TYPE__)(v))
#define __hybrid_uint128_and128(var, v)                                    \
	(void)(__hybrid_uint128_vec64(var)[0] &= __hybrid_uint128_vec64(v)[0], \
	       __hybrid_uint128_vec64(var)[1] &= __hybrid_uint128_vec64(v)[1])
#define __hybrid_uint128_or64(var, v) __hybrid_uint128_set64(var, __hybrid_uint128_get64(var) | (__UINT64_TYPE__)(v))
#define __hybrid_int128_or64(var, v)  __hybrid_int128_set64(var, __hybrid_int128_get64(var) | (__INT64_TYPE__)(v))
#define __hybrid_uint128_or128(var, v)                                    \
	(void)(__hybrid_uint128_vec64(var)[0] |= __hybrid_uint128_vec64(v)[0], \
	       __hybrid_uint128_vec64(var)[1] |= __hybrid_uint128_vec64(v)[1])
#define __hybrid_uint128_xor64(var, v) __hybrid_uint128_set64(var, __hybrid_uint128_get64(var) ^ (__UINT64_TYPE__)(v))
#define __hybrid_int128_xor64(var, v)  __hybrid_int128_set64(var, __hybrid_int128_get64(var) ^ (__INT64_TYPE__)(v))
#define __hybrid_uint128_xor128(var, v)                                    \
	(void)(__hybrid_uint128_vec64(var)[0] ^= __hybrid_uint128_vec64(v)[0], \
	       __hybrid_uint128_vec64(var)[1] ^= __hybrid_uint128_vec64(v)[1])
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
#define __hybrid_int128_and128 __hybrid_uint128_and128
#define __hybrid_uint128_and8(var, v)   __hybrid_uint128_set8(var, __hybrid_uint128_get8(var) & (__UINT8_TYPE__)(v))
#define __hybrid_uint128_and16(var, v)  __hybrid_uint128_set16(var, __hybrid_uint128_get16(var) & (__UINT16_TYPE__)(v))
#define __hybrid_uint128_and32(var, v)  __hybrid_uint128_set32(var, __hybrid_uint128_get32(var) & (__UINT32_TYPE__)(v))
#define __hybrid_int128_and8(var, v)   __hybrid_int128_set8(var, __hybrid_int128_get8(var) & (__INT8_TYPE__)(v))
#define __hybrid_int128_and16(var, v)  __hybrid_int128_set16(var, __hybrid_int128_get16(var) & (__INT16_TYPE__)(v))
#define __hybrid_int128_and32(var, v)  __hybrid_int128_set32(var, __hybrid_int128_get32(var) & (__INT32_TYPE__)(v))
#define __hybrid_int128_or128 __hybrid_uint128_or128
#define __hybrid_uint128_or8(var, v)   __hybrid_uint128_set8(var, __hybrid_uint128_get8(var) | (__UINT8_TYPE__)(v))
#define __hybrid_uint128_or16(var, v)  __hybrid_uint128_set16(var, __hybrid_uint128_get16(var) | (__UINT16_TYPE__)(v))
#define __hybrid_uint128_or32(var, v)  __hybrid_uint128_set32(var, __hybrid_uint128_get32(var) | (__UINT32_TYPE__)(v))
#define __hybrid_int128_or8(var, v)   __hybrid_int128_set8(var, __hybrid_int128_get8(var) | (__INT8_TYPE__)(v))
#define __hybrid_int128_or16(var, v)  __hybrid_int128_set16(var, __hybrid_int128_get16(var) | (__INT16_TYPE__)(v))
#define __hybrid_int128_or32(var, v)  __hybrid_int128_set32(var, __hybrid_int128_get32(var) | (__INT32_TYPE__)(v))
#define __hybrid_int128_xor128 __hybrid_uint128_xor128
#define __hybrid_uint128_xor8(var, v)   __hybrid_uint128_set8(var, __hybrid_uint128_get8(var) ^ (__UINT8_TYPE__)(v))
#define __hybrid_uint128_xor16(var, v)  __hybrid_uint128_set16(var, __hybrid_uint128_get16(var) ^ (__UINT16_TYPE__)(v))
#define __hybrid_uint128_xor32(var, v)  __hybrid_uint128_set32(var, __hybrid_uint128_get32(var) ^ (__UINT32_TYPE__)(v))
#define __hybrid_int128_xor8(var, v)   __hybrid_int128_set8(var, __hybrid_int128_get8(var) ^ (__INT8_TYPE__)(v))
#define __hybrid_int128_xor16(var, v)  __hybrid_int128_set16(var, __hybrid_int128_get16(var) ^ (__INT16_TYPE__)(v))
#define __hybrid_int128_xor32(var, v)  __hybrid_int128_set32(var, __hybrid_int128_get32(var) ^ (__INT32_TYPE__)(v))

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
#define __hybrid_int128_iszero_minus_min(var) \
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
#define __hybrid_int128_is8bit(var)                                                   \
	(__hybrid_int128_isneg(var) ? (__hybrid_int128_vec8_significand(var, 0) < 0 &&    \
	                               __hybrid_int128_vec8_significand(var, 1) == -1 &&  \
	                               __hybrid_int128_vec16_significand(var, 1) == -1 && \
	                               __hybrid_int128_vec32_significand(var, 1) == -1 && \
	                               __hybrid_int128_vec64_significand(var, 1) == -1)   \
	                            : (__hybrid_int128_vec8_significand(var, 0) >= 0 &&   \
	                               __hybrid_int128_vec8_significand(var, 1) == 0 &&   \
	                               __hybrid_int128_vec16_significand(var, 1) == 0 &&  \
	                               __hybrid_int128_vec32_significand(var, 1) == 0 &&  \
	                               __hybrid_int128_vec64_significand(var, 1) == 0))
#define __hybrid_int128_is16bit(var)                                                  \
	(__hybrid_int128_isneg(var) ? (__hybrid_int128_vec16_significand(var, 0) < 0 &&   \
	                               __hybrid_int128_vec16_significand(var, 1) == -1 && \
	                               __hybrid_int128_vec32_significand(var, 1) == -1 && \
	                               __hybrid_int128_vec64_significand(var, 1) == -1)   \
	                            : (__hybrid_int128_vec16_significand(var, 0) >= 0 &&  \
	                               __hybrid_int128_vec16_significand(var, 1) == 0 &&  \
	                               __hybrid_int128_vec32_significand(var, 1) == 0 &&  \
	                               __hybrid_int128_vec64_significand(var, 1) == 0))
#define __hybrid_int128_is32bit(var)                                                  \
	(__hybrid_int128_isneg(var) ? (__hybrid_int128_vec32_significand(var, 0) < 0 &&   \
	                               __hybrid_int128_vec32_significand(var, 1) == -1 && \
	                               __hybrid_int128_vec64_significand(var, 1) == -1)   \
	                            : (__hybrid_int128_vec32_significand(var, 0) >= 0 &&  \
	                               __hybrid_int128_vec32_significand(var, 1) == 0 &&  \
	                               __hybrid_int128_vec64_significand(var, 1) == 0))
#define __hybrid_int128_is64bit(var)                                                 \
	(__hybrid_int128_isneg(var) ? (__hybrid_int128_vec64_significand(var, 0) < 0 &&  \
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
#define __hybrid_int128_is8bit(var)                                                   \
	(__hybrid_int128_isneg(var) ? (__hybrid_int128_vec8_significand(var, 0) < 0 &&    \
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
#define __hybrid_int128_is16bit(var)                                                  \
	(__hybrid_int128_isneg(var) ? (__hybrid_int128_vec16_significand(var, 0) < 0 &&   \
	                               __hybrid_int128_vec16_significand(var, 1) == -1 && \
	                               __hybrid_int128_vec32_significand(var, 1) == -1 && \
	                               __hybrid_int128_vec32_significand(var, 2) == -1 && \
	                               __hybrid_int128_vec32_significand(var, 3) == -1)   \
	                            : (__hybrid_int128_vec16_significand(var, 0) >= 0 &&  \
	                               __hybrid_int128_vec16_significand(var, 1) == 0 &&  \
	                               __hybrid_int128_vec32_significand(var, 1) == 0 &&  \
	                               __hybrid_int128_vec32_significand(var, 2) == 0 &&  \
	                               __hybrid_int128_vec32_significand(var, 3) == 0))
#define __hybrid_int128_is32bit(var)                                                  \
	(__hybrid_int128_isneg(var) ? (__hybrid_int128_vec32_significand(var, 0) < 0 &&   \
	                               __hybrid_int128_vec32_significand(var, 1) == -1 && \
	                               __hybrid_int128_vec32_significand(var, 2) == -1 && \
	                               __hybrid_int128_vec32_significand(var, 3) == -1)   \
	                            : (__hybrid_int128_vec32_significand(var, 0) >= 0 &&  \
	                               __hybrid_int128_vec32_significand(var, 1) == 0 &&  \
	                               __hybrid_int128_vec32_significand(var, 2) == 0 &&  \
	                               __hybrid_int128_vec32_significand(var, 3) == 0))
#define __hybrid_int128_is64bit(var)                                                  \
	(__hybrid_int128_isneg(var) ? (__hybrid_int128_vec32_significand(var, 1) < 0 &&   \
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
#define __hybrid_uint128_eq(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_uint128_eq8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_uint128_eq16(var, v) : \
	                  __hybrid_uint128_eq32(var, v))
#define __hybrid_int128_eq(var, v)                   \
	(sizeof(v) == 1 ? __hybrid_int128_eq8(var, v) :  \
	 sizeof(v) == 2 ? __hybrid_int128_eq16(var, v) : \
	                  __hybrid_int128_eq32(var, v))
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
#define __hybrid_uint128_eq(var, v)                                      \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_eq8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_eq16(var, v), \
	                                      __hybrid_uint128_eq32(var, v)))
#define __hybrid_int128_eq(var, v)                                       \
	__builtin_choose_expr(sizeof(v) == 1, __hybrid_uint128_eq8(var, v),  \
	__builtin_choose_expr(sizeof(v) == 2, __hybrid_uint128_eq16(var, v), \
	                                      __hybrid_uint128_eq32(var, v)))
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
union __hybrid_uint128_struct;
extern "C++" {
__NAMESPACE_INT_BEGIN
template<class __T> struct __hybrid_int128_isint { enum { __val = false }; };
template<> struct __hybrid_int128_isint<char> { enum { __val = true }; };
template<> struct __hybrid_int128_isint<signed char> { enum { __val = true }; };
template<> struct __hybrid_int128_isint<unsigned char> { enum { __val = true }; };
template<> struct __hybrid_int128_isint<short> { enum { __val = true }; };
template<> struct __hybrid_int128_isint<unsigned short> { enum { __val = true }; };
template<> struct __hybrid_int128_isint<int> { enum { __val = true }; };
template<> struct __hybrid_int128_isint<unsigned int> { enum { __val = true }; };
template<> struct __hybrid_int128_isint<long> { enum { __val = true }; };
template<> struct __hybrid_int128_isint<unsigned long> { enum { __val = true }; };
#ifdef __COMPILER_HAVE_LONGLONG
template<> struct __hybrid_int128_isint<long long> { enum { __val = true }; };
template<> struct __hybrid_int128_isint<unsigned long long> { enum { __val = true }; };
#endif /* __COMPILER_HAVE_LONGLONG */
template<bool __V, class __T> struct __hybrid_int128_enableif { typedef __T __type; };
template<class __T> struct __hybrid_int128_enableif<false, __T> {};
__NAMESPACE_INT_END
#define __HYBRID_INT128_ENABLE_IF_ARITH(ArithType, Type) \
	typename ::__intern::__hybrid_int128_enableif< ::__intern::__hybrid_int128_isint<ArithType>::__val, Type>::__type
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
	__CXX_CLASSMEMBER __CXX_DEFAULT_COPY_NOEXCEPT(__hybrid_int128_struct, __v, {
		__i128_s32[0] = __v.__i128_s32[0];
		__i128_s32[1] = __v.__i128_s32[1];
		__i128_s32[2] = __v.__i128_s32[2];
		__i128_s32[3] = __v.__i128_s32[3];
	});
	__CXX_CLASSMEMBER __hybrid_int128_struct(__hybrid_uint128_struct const &__v) __CXX_NOEXCEPT;
	template<class __ValType> __CXX_CLASSMEMBER __hybrid_int128_struct(__ValType __v, __HYBRID_INT128_ENABLE_IF_ARITH(__ValType, int *) = 0) __CXX_NOEXCEPT { __hybrid_int128_set(*this, __v); }
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
	__CXX_CLASSMEMBER explicit operator long long() const __CXX_NOEXCEPT { return __hybrid_int128_as(*this, __SIZEOF_LONG_LONG__); }
	__CXX_CLASSMEMBER explicit operator unsigned long long() const __CXX_NOEXCEPT { return (unsigned long long)__hybrid_int128_as(*this, __SIZEOF_LONG_LONG__); }
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
	__CXX_CLASSMEMBER __CXX_DEFAULT_COPY_NOEXCEPT(__hybrid_uint128_struct, __v, {
		__i128_u32[0] = __v.__i128_u32[0];
		__i128_u32[1] = __v.__i128_u32[1];
		__i128_u32[2] = __v.__i128_u32[2];
		__i128_u32[3] = __v.__i128_u32[3];
	});
	__CXX_CLASSMEMBER __hybrid_uint128_struct(__hybrid_int128_struct const &__v) __CXX_NOEXCEPT;
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
	__CXX_CLASSMEMBER explicit operator long long() const __CXX_NOEXCEPT { return (long long)__hybrid_uint128_as(*this, __SIZEOF_LONG_LONG__); }
	__CXX_CLASSMEMBER explicit operator unsigned long long() const __CXX_NOEXCEPT { return __hybrid_uint128_as(*this, __SIZEOF_LONG_LONG__); }
#endif /* __COMPILER_HAVE_LONGLONG */
	__CXX_CLASSMEMBER bool operator!() const __CXX_NOEXCEPT { return __hybrid_uint128_iszero(*this); }
#endif /* defined(__cplusplus) && WANT_INT128_CXX_INTEGRATION */
} __hybrid_uint128_t;
#define __hybrid_uint128_t __hybrid_uint128_t


#if defined(__cplusplus) && defined(WANT_INT128_CXX_INTEGRATION)
__CXX_CLASSMEMBER __hybrid_int128_struct::
__hybrid_int128_struct(__hybrid_uint128_struct const &__v) __CXX_NOEXCEPT {
	__i128_u32[0] = __v.__i128_u32[0];
	__i128_u32[1] = __v.__i128_u32[1];
	__i128_u32[2] = __v.__i128_u32[2];
	__i128_u32[3] = __v.__i128_u32[3];
}
__CXX_CLASSMEMBER __hybrid_uint128_struct::
__hybrid_uint128_struct(__hybrid_int128_struct const &__v) __CXX_NOEXCEPT {
	__i128_u32[0] = __v.__i128_u32[0];
	__i128_u32[1] = __v.__i128_u32[1];
	__i128_u32[2] = __v.__i128_u32[2];
	__i128_u32[3] = __v.__i128_u32[3];
}

__LOCAL __ATTR_WUNUSED __ATTR_PURE __hybrid_int128_t operator - (__hybrid_int128_t const &__self) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __hybrid_int128_neg(__res); return __res; }
__LOCAL __hybrid_int128_t &operator ++ (__hybrid_int128_t &__self) __CXX_NOEXCEPT { __hybrid_int128_inc(__self); return __self; }
__LOCAL __hybrid_int128_t operator ++ (__hybrid_int128_t &__self, int) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __hybrid_int128_inc(__self); return __res; }
__LOCAL __hybrid_int128_t &operator -- (__hybrid_int128_t &__self) __CXX_NOEXCEPT { __hybrid_int128_dec(__self); return __self; }
__LOCAL __hybrid_int128_t operator -- (__hybrid_int128_t &__self, int) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __hybrid_int128_dec(__self); return __res; }
__LOCAL __hybrid_uint128_t &operator ++ (__hybrid_uint128_t &__self) __CXX_NOEXCEPT { __hybrid_uint128_inc(__self); return __self; }
__LOCAL __hybrid_uint128_t operator ++ (__hybrid_uint128_t &__self, int) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __hybrid_uint128_inc(__self); return __res; }
__LOCAL __hybrid_uint128_t &operator -- (__hybrid_uint128_t &__self) __CXX_NOEXCEPT { __hybrid_uint128_dec(__self); return __self; }
__LOCAL __hybrid_uint128_t operator -- (__hybrid_uint128_t &__self, int) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __hybrid_uint128_dec(__self); return __res; }
template<class __ValType> __LOCAL __HYBRID_INT128_ENABLE_IF_ARITH(__ValType, __hybrid_uint128_t &) operator &= (__hybrid_uint128_t &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_uint128_and(__self, __v); return __self; }
template<class __ValType> __LOCAL __HYBRID_INT128_ENABLE_IF_ARITH(__ValType, __hybrid_uint128_t &) operator |= (__hybrid_uint128_t &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_uint128_or(__self, __v); return __self; }
template<class __ValType> __LOCAL __HYBRID_INT128_ENABLE_IF_ARITH(__ValType, __hybrid_uint128_t &) operator ^= (__hybrid_uint128_t &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_uint128_xor(__self, __v); return __self; }
template<class __ValType> __LOCAL __HYBRID_INT128_ENABLE_IF_ARITH(__ValType, __hybrid_int128_t &) operator &= (__hybrid_int128_t &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_int128_and(__self, __v); return __self; }
template<class __ValType> __LOCAL __HYBRID_INT128_ENABLE_IF_ARITH(__ValType, __hybrid_int128_t &) operator |= (__hybrid_int128_t &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_int128_or(__self, __v); return __self; }
template<class __ValType> __LOCAL __HYBRID_INT128_ENABLE_IF_ARITH(__ValType, __hybrid_int128_t &) operator ^= (__hybrid_int128_t &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_int128_xor(__self, __v); return __self; }
template<class __ValType> __LOCAL __ATTR_WUNUSED __ATTR_PURE __HYBRID_INT128_ENABLE_IF_ARITH(__ValType, __hybrid_uint128_t) operator & (__hybrid_uint128_t const &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __res &= __v; return __res; }
template<class __ValType> __LOCAL __ATTR_WUNUSED __ATTR_PURE __HYBRID_INT128_ENABLE_IF_ARITH(__ValType, __hybrid_uint128_t) operator | (__hybrid_uint128_t const &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __res |= __v; return __res; }
template<class __ValType> __LOCAL __ATTR_WUNUSED __ATTR_PURE __HYBRID_INT128_ENABLE_IF_ARITH(__ValType, __hybrid_uint128_t) operator ^ (__hybrid_uint128_t const &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __res ^= __v; return __res; }
template<class __ValType> __LOCAL __ATTR_WUNUSED __ATTR_PURE __HYBRID_INT128_ENABLE_IF_ARITH(__ValType, __hybrid_int128_t) operator & (__hybrid_int128_t const &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __res &= __v; return __res; }
template<class __ValType> __LOCAL __ATTR_WUNUSED __ATTR_PURE __HYBRID_INT128_ENABLE_IF_ARITH(__ValType, __hybrid_int128_t) operator | (__hybrid_int128_t const &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __res |= __v; return __res; }
template<class __ValType> __LOCAL __ATTR_WUNUSED __ATTR_PURE __HYBRID_INT128_ENABLE_IF_ARITH(__ValType, __hybrid_int128_t) operator ^ (__hybrid_int128_t const &__self, __ValType __v) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __res ^= __v; return __res; }
template<class __ValType> __LOCAL __ATTR_WUNUSED __ATTR_PURE __HYBRID_INT128_ENABLE_IF_ARITH(__ValType, bool) operator == (__hybrid_int128_t const &__self, __ValType __v) __CXX_NOEXCEPT { return __hybrid_int128_eq(__self, __v); }
template<class __ValType> __LOCAL __ATTR_WUNUSED __ATTR_PURE __HYBRID_INT128_ENABLE_IF_ARITH(__ValType, bool) operator != (__hybrid_int128_t const &__self, __ValType __v) __CXX_NOEXCEPT { return !(__self == __v); }
template<class __ValType> __LOCAL __ATTR_WUNUSED __ATTR_PURE __HYBRID_INT128_ENABLE_IF_ARITH(__ValType, bool) operator == (__hybrid_uint128_t const &__self, __ValType __v) __CXX_NOEXCEPT { return __hybrid_uint128_eq(__self, __v); }
template<class __ValType> __LOCAL __ATTR_WUNUSED __ATTR_PURE __HYBRID_INT128_ENABLE_IF_ARITH(__ValType, bool) operator != (__hybrid_uint128_t const &__self, __ValType __v) __CXX_NOEXCEPT { return !(__self == __v); }
__LOCAL __ATTR_WUNUSED __ATTR_PURE bool operator == (__hybrid_int128_t const &__self, __hybrid_int128_t const &__v) __CXX_NOEXCEPT { return __hybrid_int128_eq128(__self, __v); }
__LOCAL __ATTR_WUNUSED __ATTR_PURE bool operator == (__hybrid_int128_t const &__self, __hybrid_uint128_t const &__v) __CXX_NOEXCEPT { return __hybrid_int128_eq128(__self, __v); }
__LOCAL __ATTR_WUNUSED __ATTR_PURE bool operator != (__hybrid_int128_t const &__self, __hybrid_int128_t const &__v) __CXX_NOEXCEPT { return !(__self == __v); }
__LOCAL __ATTR_WUNUSED __ATTR_PURE bool operator != (__hybrid_int128_t const &__self, __hybrid_uint128_t const &__v) __CXX_NOEXCEPT { return !(__self == __v); }
__LOCAL __ATTR_WUNUSED __ATTR_PURE bool operator == (__hybrid_uint128_t const &__self, __hybrid_int128_t const &__v) __CXX_NOEXCEPT { return __hybrid_uint128_eq128(__self, __v); }
__LOCAL __ATTR_WUNUSED __ATTR_PURE bool operator == (__hybrid_uint128_t const &__self, __hybrid_uint128_t const &__v) __CXX_NOEXCEPT { return __hybrid_uint128_eq128(__self, __v); }
__LOCAL __ATTR_WUNUSED __ATTR_PURE bool operator != (__hybrid_uint128_t const &__self, __hybrid_int128_t const &__v) __CXX_NOEXCEPT { return !(__self == __v); }
__LOCAL __ATTR_WUNUSED __ATTR_PURE bool operator != (__hybrid_uint128_t const &__self, __hybrid_uint128_t const &__v) __CXX_NOEXCEPT { return !(__self == __v); }
__LOCAL __hybrid_int128_t &operator <<= (__hybrid_int128_t &__self, unsigned int __shift) __CXX_NOEXCEPT { __hybrid_int128_shl(__self, __shift); return __self; }
__LOCAL __hybrid_int128_t &operator >>= (__hybrid_int128_t &__self, unsigned int __shift) __CXX_NOEXCEPT { __hybrid_int128_shr(__self, __shift); return __self; }
__LOCAL __hybrid_uint128_t &operator <<= (__hybrid_uint128_t &__self, unsigned int __shift) __CXX_NOEXCEPT { __hybrid_uint128_shl(__self, __shift); return __self; }
__LOCAL __hybrid_uint128_t &operator >>= (__hybrid_uint128_t &__self, unsigned int __shift) __CXX_NOEXCEPT { __hybrid_uint128_shr(__self, __shift); return __self; }
__LOCAL __ATTR_WUNUSED __ATTR_PURE __hybrid_int128_t operator << (__hybrid_int128_t const &__self, unsigned int __shift) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __res <<= __shift; return __res; }
__LOCAL __ATTR_WUNUSED __ATTR_PURE __hybrid_int128_t operator >> (__hybrid_int128_t const &__self, unsigned int __shift) __CXX_NOEXCEPT { __hybrid_int128_t __res = __self; __res >>= __shift; return __res; }
__LOCAL __ATTR_WUNUSED __ATTR_PURE __hybrid_uint128_t operator << (__hybrid_uint128_t const &__self, unsigned int __shift) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __res <<= __shift; return __res; }
__LOCAL __ATTR_WUNUSED __ATTR_PURE __hybrid_uint128_t operator >> (__hybrid_uint128_t const &__self, unsigned int __shift) __CXX_NOEXCEPT { __hybrid_uint128_t __res = __self; __res >>= __shift; return __res; }
#undef __HYBRID_INT128_ENABLE_IF_ARITH
}
#endif /* __cplusplus && WANT_INT128_CXX_INTEGRATION */

__DECL_END

#endif /* !__INT128_TYPE__ || !__UINT128_TYPE__ */
#endif /* __CC__ */


#endif /* !__GUARD_HYBRID_INT128_H */
