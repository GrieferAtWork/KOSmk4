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
#ifndef _INT128_H
#define _INT128_H 1

#include <__stdinc.h>

#include <hybrid/int128.h>

#include <bits/types.h>

#ifdef __CC__
__SYSDECL_BEGIN

/* 128-bit integer types. */
#ifndef __int128_t_defined
#define __int128_t_defined 1
typedef __hybrid_int128_t int128_t;
typedef __hybrid_uint128_t uint128_t;
#endif /* !__int128_t_defined */

#if defined(__INTELLISENSE__) && defined(__cplusplus)
extern "C++" {

/* View the data of a 128-bit integer as an array of smaller integers */
__ATTR_WUNUSED __ATTR_CONST __int8_t (&int128_vec8(int128_t &__var))[16];
__ATTR_WUNUSED __ATTR_CONST __int8_t const (&int128_vec8(int128_t const &__var))[16];
__ATTR_WUNUSED __ATTR_CONST __int16_t (&int128_vec16(int128_t &__var))[8];
__ATTR_WUNUSED __ATTR_CONST __int16_t const (&int128_vec16(int128_t const &__var))[8];
__ATTR_WUNUSED __ATTR_CONST __int32_t (&int128_vec32(int128_t &__var))[4];
__ATTR_WUNUSED __ATTR_CONST __int32_t const (&int128_vec32(int128_t const &__var))[4];
__ATTR_WUNUSED __ATTR_CONST __uint8_t (&uint128_vec8(uint128_t &__var))[16];
__ATTR_WUNUSED __ATTR_CONST __uint8_t const (&uint128_vec8(uint128_t const &__var))[16];
__ATTR_WUNUSED __ATTR_CONST __uint16_t (&uint128_vec16(uint128_t &__var))[8];
__ATTR_WUNUSED __ATTR_CONST __uint16_t const (&uint128_vec16(uint128_t const &__var))[8];
__ATTR_WUNUSED __ATTR_CONST __uint32_t (&uint128_vec32(uint128_t &__var))[4];
__ATTR_WUNUSED __ATTR_CONST __uint32_t const (&uint128_vec32(uint128_t const &__var))[4];
#ifdef __UINT64_TYPE__
__ATTR_WUNUSED __ATTR_CONST __int64_t (&int128_vec64(int128_t &__var))[4];
__ATTR_WUNUSED __ATTR_CONST __int64_t const (&int128_vec64(int128_t const &__var))[4];
__ATTR_WUNUSED __ATTR_CONST __uint64_t (&uint128_vec64(uint128_t &__var))[4];
__ATTR_WUNUSED __ATTR_CONST __uint64_t const (&uint128_vec64(uint128_t const &__var))[4];
#endif /* __UINT64_TYPE__ */

/* Return a reference to the I'th least significant word, where 0 is the least
 * significant word, and ((16 / sizeof(return)) - 1) is the most significant one. */
__ATTR_WUNUSED __ATTR_CONST __int8_t &int128_vec8_significand(int128_t &__var, unsigned int __i);
__ATTR_WUNUSED __ATTR_CONST __int8_t const &int128_vec8_significand(int128_t const &__var, unsigned int __i);
__ATTR_WUNUSED __ATTR_CONST __int16_t &int128_vec16_significand(int128_t &__var, unsigned int __i);
__ATTR_WUNUSED __ATTR_CONST __int16_t const &int128_vec16_significand(int128_t const &__var, unsigned int __i);
__ATTR_WUNUSED __ATTR_CONST __int32_t &int128_vec32_significand(int128_t &__var, unsigned int __i);
__ATTR_WUNUSED __ATTR_CONST __int32_t const &int128_vec32_significand(int128_t const &__var, unsigned int __i);
__ATTR_WUNUSED __ATTR_CONST __uint8_t &uint128_vec8_significand(uint128_t &__var, unsigned int __i);
__ATTR_WUNUSED __ATTR_CONST __uint8_t const &uint128_vec8_significand(uint128_t const &__var, unsigned int __i);
__ATTR_WUNUSED __ATTR_CONST __uint16_t &uint128_vec16_significand(uint128_t &__var, unsigned int __i);
__ATTR_WUNUSED __ATTR_CONST __uint16_t const &uint128_vec16_significand(uint128_t const &__var, unsigned int __i);
__ATTR_WUNUSED __ATTR_CONST __uint32_t &uint128_vec32_significand(uint128_t &__var, unsigned int __i);
__ATTR_WUNUSED __ATTR_CONST __uint32_t const &uint128_vec32_significand(uint128_t const &__var, unsigned int __i);
#ifdef __UINT64_TYPE__
__ATTR_WUNUSED __ATTR_CONST __int64_t &int128_vec64_significand(int128_t &__var, unsigned int __i);
__ATTR_WUNUSED __ATTR_CONST __int64_t const &int128_vec64_significand(int128_t const &__var, unsigned int __i);
__ATTR_WUNUSED __ATTR_CONST __uint64_t &uint128_vec64_significand(uint128_t &__var, unsigned int __i);
__ATTR_WUNUSED __ATTR_CONST __uint64_t const &uint128_vec64_significand(uint128_t const &__var, unsigned int __i);
#endif /* __UINT64_TYPE__ */

/* Truncate and return a given 128-bit integer as a smaller-order integer */
__ATTR_WUNUSED __ATTR_PURE __int8_t int128_get8(int128_t const &__var);
__ATTR_WUNUSED __ATTR_PURE __uint8_t uint128_get8(uint128_t const &__var);
__ATTR_WUNUSED __ATTR_PURE __int16_t int128_get16(int128_t const &__var);
__ATTR_WUNUSED __ATTR_PURE __uint16_t uint128_get16(uint128_t const &__var);
__ATTR_WUNUSED __ATTR_PURE __int32_t int128_get32(int128_t const &__var);
__ATTR_WUNUSED __ATTR_PURE __uint32_t uint128_get32(uint128_t const &__var);
#ifdef __UINT64_TYPE__
__ATTR_WUNUSED __ATTR_PURE __int64_t int128_get64(int128_t const &__var);
__ATTR_WUNUSED __ATTR_PURE __uint64_t uint128_get64(uint128_t const &__var);
#endif /* __UINT64_TYPE__ */

/* Set a 128-bit integer from a given data-word */
void int128_set8(int128_t &__var, __int8_t __value);
void uint128_set8(uint128_t &__var, __uint8_t __value);
void int128_set16(int128_t &__var, __int16_t __value);
void uint128_set16(uint128_t &__var, __uint16_t __value);
void int128_set32(int128_t &__var, __int32_t __value);
void uint128_set32(uint128_t &__var, __uint32_t __value);
#ifdef __UINT64_TYPE__
void int128_set64(int128_t &__var, __int64_t __value);
void uint128_set64(uint128_t &__var, __uint64_t __value);
#endif /* __UINT64_TYPE__ */

/* Helper macros that automatically determine the data-word size when setting a 128-bit integer. */
void int128_set(int128_t &__var, char __value);
void int128_set(int128_t &__var, signed char __value);
void int128_set(int128_t &__var, unsigned char __value);
void int128_set(int128_t &__var, short __value);
void int128_set(int128_t &__var, unsigned short __value);
void int128_set(int128_t &__var, int __value);
void int128_set(int128_t &__var, unsigned int __value);
void int128_set(int128_t &__var, long __value);
void int128_set(int128_t &__var, unsigned long __value);
void int128_set(int128_t &__var, __LONGLONG __value);
void int128_set(int128_t &__var, __ULONGLONG __value);
void uint128_set(uint128_t &__var, char __value);
void uint128_set(uint128_t &__var, signed char __value);
void uint128_set(uint128_t &__var, unsigned char __value);
void uint128_set(uint128_t &__var, short __value);
void uint128_set(uint128_t &__var, unsigned short __value);
void uint128_set(uint128_t &__var, int __value);
void uint128_set(uint128_t &__var, unsigned int __value);
void uint128_set(uint128_t &__var, long __value);
void uint128_set(uint128_t &__var, unsigned long __value);
void uint128_set(uint128_t &__var, __LONGLONG __value);
void uint128_set(uint128_t &__var, __ULONGLONG __value);

/* ++VAR */
void uint128_inc(uint128_t &__var);
void int128_inc(int128_t &__var);

/* --VAR */
void uint128_dec(uint128_t &__var);
void int128_dec(int128_t &__var);

/* VAR = ~VAR */
void uint128_inv(uint128_t &__var);
void int128_inv(int128_t &__var);

/* VAR = -VAR */
void int128_neg(int128_t &__var);

/* VAR < 0 */
__ATTR_WUNUSED __ATTR_PURE bool int128_isneg(int128_t const &__var);

/* VAR &= VALUE */
void uint128_and(uint128_t &__var, char __value);
void uint128_and(uint128_t &__var, signed char __value);
void uint128_and(uint128_t &__var, unsigned char __value);
void uint128_and(uint128_t &__var, short __value);
void uint128_and(uint128_t &__var, unsigned short __value);
void uint128_and(uint128_t &__var, int __value);
void uint128_and(uint128_t &__var, unsigned int __value);
void uint128_and(uint128_t &__var, long __value);
void uint128_and(uint128_t &__var, unsigned long __value);
void uint128_and(uint128_t &__var, __LONGLONG __value);
void uint128_and(uint128_t &__var, __ULONGLONG __value);
void uint128_and8(uint128_t &__var, __UINT8_TYPE__ __value);
void uint128_and16(uint128_t &__var, __UINT16_TYPE__ __value);
void uint128_and32(uint128_t &__var, __UINT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void uint128_and64(uint128_t &__var, __UINT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void uint128_and128(uint128_t &__var, int128_t __value);
void uint128_and128(uint128_t &__var, uint128_t __value);
void int128_and(int128_t &__var, char __value);
void int128_and(int128_t &__var, signed char __value);
void int128_and(int128_t &__var, unsigned char __value);
void int128_and(int128_t &__var, short __value);
void int128_and(int128_t &__var, unsigned short __value);
void int128_and(int128_t &__var, int __value);
void int128_and(int128_t &__var, unsigned int __value);
void int128_and(int128_t &__var, long __value);
void int128_and(int128_t &__var, unsigned long __value);
void int128_and(int128_t &__var, __LONGLONG __value);
void int128_and(int128_t &__var, __ULONGLONG __value);
void int128_and8(int128_t &__var, __UINT8_TYPE__ __value);
void int128_and16(int128_t &__var, __UINT16_TYPE__ __value);
void int128_and32(int128_t &__var, __UINT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void int128_and64(int128_t &__var, __UINT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void int128_and128(int128_t &__var, int128_t __value);
void int128_and128(int128_t &__var, uint128_t __value);

/* VAR |= VALUE */
void uint128_or(uint128_t &__var, char __value);
void uint128_or(uint128_t &__var, signed char __value);
void uint128_or(uint128_t &__var, unsigned char __value);
void uint128_or(uint128_t &__var, short __value);
void uint128_or(uint128_t &__var, unsigned short __value);
void uint128_or(uint128_t &__var, int __value);
void uint128_or(uint128_t &__var, unsigned int __value);
void uint128_or(uint128_t &__var, long __value);
void uint128_or(uint128_t &__var, unsigned long __value);
void uint128_or(uint128_t &__var, __LONGLONG __value);
void uint128_or(uint128_t &__var, __ULONGLONG __value);
void uint128_or8(uint128_t &__var, __UINT8_TYPE__ __value);
void uint128_or16(uint128_t &__var, __UINT16_TYPE__ __value);
void uint128_or32(uint128_t &__var, __UINT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void uint128_or64(uint128_t &__var, __UINT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void uint128_or128(uint128_t &__var, int128_t __value);
void uint128_or128(uint128_t &__var, uint128_t __value);
void int128_or(int128_t &__var, char __value);
void int128_or(int128_t &__var, signed char __value);
void int128_or(int128_t &__var, unsigned char __value);
void int128_or(int128_t &__var, short __value);
void int128_or(int128_t &__var, unsigned short __value);
void int128_or(int128_t &__var, int __value);
void int128_or(int128_t &__var, unsigned int __value);
void int128_or(int128_t &__var, long __value);
void int128_or(int128_t &__var, unsigned long __value);
void int128_or(int128_t &__var, __LONGLONG __value);
void int128_or(int128_t &__var, __ULONGLONG __value);
void int128_or8(int128_t &__var, __UINT8_TYPE__ __value);
void int128_or16(int128_t &__var, __UINT16_TYPE__ __value);
void int128_or32(int128_t &__var, __UINT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void int128_or64(int128_t &__var, __UINT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void int128_or128(int128_t &__var, int128_t __value);
void int128_or128(int128_t &__var, uint128_t __value);

/* VAR ^= VALUE */
void uint128_xor(uint128_t &__var, char __value);
void uint128_xor(uint128_t &__var, signed char __value);
void uint128_xor(uint128_t &__var, unsigned char __value);
void uint128_xor(uint128_t &__var, short __value);
void uint128_xor(uint128_t &__var, unsigned short __value);
void uint128_xor(uint128_t &__var, int __value);
void uint128_xor(uint128_t &__var, unsigned int __value);
void uint128_xor(uint128_t &__var, long __value);
void uint128_xor(uint128_t &__var, unsigned long __value);
void uint128_xor(uint128_t &__var, __LONGLONG __value);
void uint128_xor(uint128_t &__var, __ULONGLONG __value);
void uint128_xor8(uint128_t &__var, __UINT8_TYPE__ __value);
void uint128_xor16(uint128_t &__var, __UINT16_TYPE__ __value);
void uint128_xor32(uint128_t &__var, __UINT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void uint128_xor64(uint128_t &__var, __UINT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void uint128_xor128(uint128_t &__var, int128_t __value);
void uint128_xor128(uint128_t &__var, uint128_t __value);
void int128_xor(int128_t &__var, char __value);
void int128_xor(int128_t &__var, signed char __value);
void int128_xor(int128_t &__var, unsigned char __value);
void int128_xor(int128_t &__var, short __value);
void int128_xor(int128_t &__var, unsigned short __value);
void int128_xor(int128_t &__var, int __value);
void int128_xor(int128_t &__var, unsigned int __value);
void int128_xor(int128_t &__var, long __value);
void int128_xor(int128_t &__var, unsigned long __value);
void int128_xor(int128_t &__var, __LONGLONG __value);
void int128_xor(int128_t &__var, __ULONGLONG __value);
void int128_xor8(int128_t &__var, __UINT8_TYPE__ __value);
void int128_xor16(int128_t &__var, __UINT16_TYPE__ __value);
void int128_xor32(int128_t &__var, __UINT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void int128_xor64(int128_t &__var, __UINT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void int128_xor128(int128_t &__var, int128_t __value);
void int128_xor128(int128_t &__var, uint128_t __value);

/* VAR == VALUE */
__ATTR_WUNUSED __ATTR_PURE bool uint128_eq(uint128_t const &__var, char __value);
__ATTR_WUNUSED __ATTR_PURE bool uint128_eq(uint128_t const &__var, signed char __value);
__ATTR_WUNUSED __ATTR_PURE bool uint128_eq(uint128_t const &__var, unsigned char __value);
__ATTR_WUNUSED __ATTR_PURE bool uint128_eq(uint128_t const &__var, short __value);
__ATTR_WUNUSED __ATTR_PURE bool uint128_eq(uint128_t const &__var, unsigned short __value);
__ATTR_WUNUSED __ATTR_PURE bool uint128_eq(uint128_t const &__var, int __value);
__ATTR_WUNUSED __ATTR_PURE bool uint128_eq(uint128_t const &__var, unsigned int __value);
__ATTR_WUNUSED __ATTR_PURE bool uint128_eq(uint128_t const &__var, long __value);
__ATTR_WUNUSED __ATTR_PURE bool uint128_eq(uint128_t const &__var, unsigned long __value);
__ATTR_WUNUSED __ATTR_PURE bool uint128_eq(uint128_t const &__var, __LONGLONG __value);
__ATTR_WUNUSED __ATTR_PURE bool uint128_eq(uint128_t const &__var, __ULONGLONG __value);
__ATTR_WUNUSED __ATTR_PURE bool uint128_eq8(uint128_t const &__var, __UINT8_TYPE__ __value);
__ATTR_WUNUSED __ATTR_PURE bool uint128_eq16(uint128_t const &__var, __UINT16_TYPE__ __value);
__ATTR_WUNUSED __ATTR_PURE bool uint128_eq32(uint128_t const &__var, __UINT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
__ATTR_WUNUSED __ATTR_PURE bool uint128_eq64(uint128_t const &__var, __UINT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
__ATTR_WUNUSED __ATTR_PURE bool uint128_eq128(uint128_t const &__var, int128_t __value);
__ATTR_WUNUSED __ATTR_PURE bool uint128_eq128(uint128_t const &__var, uint128_t __value);
__ATTR_WUNUSED __ATTR_PURE bool int128_eq(int128_t const &__var, char __value);
__ATTR_WUNUSED __ATTR_PURE bool int128_eq(int128_t const &__var, signed char __value);
__ATTR_WUNUSED __ATTR_PURE bool int128_eq(int128_t const &__var, unsigned char __value);
__ATTR_WUNUSED __ATTR_PURE bool int128_eq(int128_t const &__var, short __value);
__ATTR_WUNUSED __ATTR_PURE bool int128_eq(int128_t const &__var, unsigned short __value);
__ATTR_WUNUSED __ATTR_PURE bool int128_eq(int128_t const &__var, int __value);
__ATTR_WUNUSED __ATTR_PURE bool int128_eq(int128_t const &__var, unsigned int __value);
__ATTR_WUNUSED __ATTR_PURE bool int128_eq(int128_t const &__var, long __value);
__ATTR_WUNUSED __ATTR_PURE bool int128_eq(int128_t const &__var, unsigned long __value);
__ATTR_WUNUSED __ATTR_PURE bool int128_eq(int128_t const &__var, __LONGLONG __value);
__ATTR_WUNUSED __ATTR_PURE bool int128_eq(int128_t const &__var, __ULONGLONG __value);
__ATTR_WUNUSED __ATTR_PURE bool int128_eq8(int128_t const &__var, __UINT8_TYPE__ __value);
__ATTR_WUNUSED __ATTR_PURE bool int128_eq16(int128_t const &__var, __UINT16_TYPE__ __value);
__ATTR_WUNUSED __ATTR_PURE bool int128_eq32(int128_t const &__var, __UINT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
__ATTR_WUNUSED __ATTR_PURE bool int128_eq64(int128_t const &__var, __UINT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
__ATTR_WUNUSED __ATTR_PURE bool int128_eq128(int128_t const &__var, int128_t __value);
__ATTR_WUNUSED __ATTR_PURE bool int128_eq128(int128_t const &__var, uint128_t __value);

/* Perform inplace-shift operations in `VAR'
 * NOTES:
 *  - *32: The SHIFT argument must be < 32
 *  - *64: The SHIFT argument must be < 64
 *  - *:   The SHIFT argument must be < 128 */
void uint128_shl32(uint128_t &__var, unsigned int __shift);
void uint128_shl64(uint128_t &__var, unsigned int __shift);
void uint128_shl(uint128_t &__var, unsigned int __shift);
void int128_shl32(int128_t &__var, unsigned int __shift);
void int128_shl64(int128_t &__var, unsigned int __shift);
void int128_shl(int128_t &__var, unsigned int __shift);
void uint128_shr32(uint128_t &__var, unsigned int __shift);
void uint128_shr64(uint128_t &__var, unsigned int __shift);
void uint128_shr(uint128_t &__var, unsigned int __shift);
void int128_shr32(int128_t &__var, unsigned int __shift);
void int128_shr64(int128_t &__var, unsigned int __shift);
void int128_shr(int128_t &__var, unsigned int __shift);

/* Check if a shift operation would cause data to become lost. */
__ATTR_WUNUSED __ATTR_PURE bool uint128_shl32_overflows(uint128_t const &__var, unsigned int __shift /*<32*/);
__ATTR_WUNUSED __ATTR_PURE bool int128_shl32_overflows(int128_t const &__var, unsigned int __shift /*<32*/);
__ATTR_WUNUSED __ATTR_PURE bool uint128_shl64_overflows(uint128_t const &__var, unsigned int __shift /*<64*/);
__ATTR_WUNUSED __ATTR_PURE bool int128_shl64_overflows(int128_t const &__var, unsigned int __shift /*<64*/);
__ATTR_WUNUSED __ATTR_PURE bool uint128_shl_overflows(uint128_t const &__var, unsigned int __shift /*<128*/);
__ATTR_WUNUSED __ATTR_PURE bool int128_shl_overflows(int128_t const &__var, unsigned int __shift /*<128*/);
__ATTR_WUNUSED __ATTR_PURE bool uint128_shr32_overflows(uint128_t const &__var, unsigned int __shift /*<32*/);
__ATTR_WUNUSED __ATTR_PURE bool int128_shr32_overflows(int128_t const &__var, unsigned int __shift /*<32*/);
__ATTR_WUNUSED __ATTR_PURE bool uint128_shr64_overflows(uint128_t const &__var, unsigned int __shift /*<64*/);
__ATTR_WUNUSED __ATTR_PURE bool int128_shr64_overflows(int128_t const &__var, unsigned int __shift /*<64*/);
__ATTR_WUNUSED __ATTR_PURE bool uint128_shr_overflows(uint128_t const &__var, unsigned int __shift /*<128*/);
__ATTR_WUNUSED __ATTR_PURE bool int128_shr_overflows(int128_t const &__var, unsigned int __shift /*<128*/);

/* Assign special value to the given 128-bit integer */
void int128_setzero(int128_t &__var);
void uint128_setzero(uint128_t &__var);
void int128_setone(int128_t &__var);
void uint128_setone(uint128_t &__var);
void int128_setminusone(int128_t &__var);
void int128_setmin(int128_t &__var);
void int128_setmax(int128_t &__var);
void int128_setzero_minus_min(int128_t &__var);
void uint128_setmin(uint128_t &__var);
void uint128_setmax(uint128_t &__var);

/* Test for special values within a 128-bit integer */
__ATTR_WUNUSED __ATTR_PURE bool int128_iszero(int128_t const &__var);
__ATTR_WUNUSED __ATTR_PURE bool uint128_iszero(uint128_t const &__var);
__ATTR_WUNUSED __ATTR_PURE bool int128_isone(int128_t const &__var);
__ATTR_WUNUSED __ATTR_PURE bool uint128_isone(uint128_t const &__var);
__ATTR_WUNUSED __ATTR_PURE bool int128_isminusone(int128_t const &__var);
__ATTR_WUNUSED __ATTR_PURE bool int128_ismin(int128_t const &__var);
__ATTR_WUNUSED __ATTR_PURE bool int128_ismax(int128_t const &__var);
__ATTR_WUNUSED __ATTR_PURE bool int128_iszero_minus_min(int128_t const &__var);
__ATTR_WUNUSED __ATTR_PURE bool uint128_ismin(uint128_t const &__var);
__ATTR_WUNUSED __ATTR_PURE bool uint128_ismax(uint128_t const &__var);

/* Test is the given 128-bit integer can fit into a smaller data-word without being truncated. */
__ATTR_WUNUSED __ATTR_PURE bool uint128_is8bit(uint128_t const &__var);
__ATTR_WUNUSED __ATTR_PURE bool uint128_is16bit(uint128_t const &__var);
__ATTR_WUNUSED __ATTR_PURE bool uint128_is32bit(uint128_t const &__var);
__ATTR_WUNUSED __ATTR_PURE bool uint128_is64bit(uint128_t const &__var);
__ATTR_WUNUSED __ATTR_PURE bool int128_is8bit(int128_t const &__var);
__ATTR_WUNUSED __ATTR_PURE bool int128_is16bit(int128_t const &__var);
__ATTR_WUNUSED __ATTR_PURE bool int128_is32bit(int128_t const &__var);
__ATTR_WUNUSED __ATTR_PURE bool int128_is64bit(int128_t const &__var);

}
#else /* __INTELLISENSE__ && __cplusplus */
#define int128_vec8(var)                    __hybrid_int128_vec8(var)
#define int128_vec16(var)                   __hybrid_int128_vec16(var)
#define int128_vec32(var)                   __hybrid_int128_vec32(var)
#define uint128_vec8(var)                   __hybrid_uint128_vec8(var)
#define uint128_vec16(var)                  __hybrid_uint128_vec16(var)
#define uint128_vec32(var)                  __hybrid_uint128_vec32(var)
#define int128_vec8_significand(var, i)     __hybrid_int128_vec8_significand(var, i)
#define int128_vec16_significand(var, i)    __hybrid_int128_vec16_significand(var, i)
#define int128_vec32_significand(var, i)    __hybrid_int128_vec32_significand(var, i)
#define uint128_vec8_significand(var, i)    __hybrid_uint128_vec8_significand(var, i)
#define uint128_vec16_significand(var, i)   __hybrid_uint128_vec16_significand(var, i)
#define uint128_vec32_significand(var, i)   __hybrid_uint128_vec32_significand(var, i)
#define int128_get8(var)                    __hybrid_int128_get8(var)
#define int128_set8(var, v)                 __hybrid_int128_set8(var, v)
#define uint128_get8(var)                   __hybrid_uint128_get8(var)
#define uint128_set8(var, v)                __hybrid_uint128_set8(var, v)
#define int128_get16(var)                   __hybrid_int128_get16(var)
#define int128_set16(var, v)                __hybrid_int128_set16(var, v)
#define uint128_get16(var)                  __hybrid_uint128_get16(var)
#define uint128_set16(var, v)               __hybrid_uint128_set16(var, v)
#define int128_get32(var)                   __hybrid_int128_get32(var)
#define int128_set32(var, v)                __hybrid_int128_set32(var, v)
#define uint128_get32(var)                  __hybrid_uint128_get32(var)
#define uint128_set32(var, v)               __hybrid_uint128_set32(var, v)
#define int128_set(var, v)                  __hybrid_int128_set(var, v)
#define uint128_set(var, v)                 __hybrid_uint128_set(var, v)
#define uint128_inc(var)                    __hybrid_uint128_inc(var)
#define int128_inc(var)                     __hybrid_int128_inc(var)
#define uint128_dec(var)                    __hybrid_uint128_dec(var)
#define int128_dec(var)                     __hybrid_int128_dec(var)
#define uint128_inv(var)                    __hybrid_uint128_inv(var)
#define int128_inv(var)                     __hybrid_int128_inv(var)
#define int128_neg(var)                     __hybrid_int128_neg(var)
#define int128_isneg(var)                   __hybrid_int128_isneg(var)
#define uint128_and(var, v)                 __hybrid_uint128_and(var, v)
#define uint128_and8(var, v)                __hybrid_uint128_and8(var, v)
#define uint128_and16(var, v)               __hybrid_uint128_and16(var, v)
#define uint128_and32(var, v)               __hybrid_uint128_and32(var, v)
#define uint128_and128(var, v)              __hybrid_uint128_and128(var, v)
#define int128_and(var, v)                  __hybrid_int128_and(var, v)
#define int128_and8(var, v)                 __hybrid_int128_and8(var, v)
#define int128_and16(var, v)                __hybrid_int128_and16(var, v)
#define int128_and32(var, v)                __hybrid_int128_and32(var, v)
#define int128_and128(var, v)               __hybrid_int128_and128(var, v)
#define uint128_or(var, v)                  __hybrid_uint128_or(var, v)
#define uint128_or8(var, v)                 __hybrid_uint128_or8(var, v)
#define uint128_or16(var, v)                __hybrid_uint128_or16(var, v)
#define uint128_or32(var, v)                __hybrid_uint128_or32(var, v)
#define uint128_or128(var, v)               __hybrid_uint128_or128(var, v)
#define int128_or(var, v)                   __hybrid_int128_or(var, v)
#define int128_or8(var, v)                  __hybrid_int128_or8(var, v)
#define int128_or16(var, v)                 __hybrid_int128_or16(var, v)
#define int128_or32(var, v)                 __hybrid_int128_or32(var, v)
#define int128_or128(var, v)                __hybrid_int128_or128(var, v)
#define uint128_xor(var, v)                 __hybrid_uint128_xor(var, v)
#define uint128_xor8(var, v)                __hybrid_uint128_xor8(var, v)
#define uint128_xor16(var, v)               __hybrid_uint128_xor16(var, v)
#define uint128_xor32(var, v)               __hybrid_uint128_xor32(var, v)
#define uint128_xor128(var, v)              __hybrid_uint128_xor128(var, v)
#define int128_xor(var, v)                  __hybrid_int128_xor(var, v)
#define int128_xor8(var, v)                 __hybrid_int128_xor8(var, v)
#define int128_xor16(var, v)                __hybrid_int128_xor16(var, v)
#define int128_xor32(var, v)                __hybrid_int128_xor32(var, v)
#define int128_xor128(var, v)               __hybrid_int128_xor128(var, v)
#define uint128_shl32(var, shift)           __hybrid_uint128_shl32(var, shift)
#define uint128_shr32(var, shift)           __hybrid_uint128_shr32(var, shift)
#define int128_shl32(var, shift)            __hybrid_int128_shl32(var, shift)
#define int128_shr32(var, shift)            __hybrid_int128_shr32(var, shift)
#define uint128_shl64(var, shift)           __hybrid_uint128_shl64(var, shift)
#define uint128_shr64(var, shift)           __hybrid_uint128_shr64(var, shift)
#define int128_shl64(var, shift)            __hybrid_int128_shl64(var, shift)
#define int128_shr64(var, shift)            __hybrid_int128_shr64(var, shift)
#define uint128_shl(var, shift)             __hybrid_uint128_shl(var, shift)
#define uint128_shr(var, shift)             __hybrid_uint128_shr(var, shift)
#define int128_shl(var, shift)              __hybrid_int128_shl(var, shift)
#define int128_shr(var, shift)              __hybrid_int128_shr(var, shift)
#define uint128_shl32_overflows(var, shift) __hybrid_uint128_shl32_overflows(var, shift)
#define int128_shl32_overflows(var, shift)  __hybrid_int128_shl32_overflows(var, shift)
#define uint128_shl64_overflows(var, shift) __hybrid_uint128_shl64_overflows(var, shift)
#define int128_shl64_overflows(var, shift)  __hybrid_int128_shl64_overflows(var, shift)
#define uint128_shl_overflows(var, shift)   __hybrid_uint128_shl_overflows(var, shift)
#define int128_shl_overflows(var, shift)    __hybrid_int128_shl_overflows(var, shift)
#define uint128_shr32_overflows(var, shift) __hybrid_uint128_shr32_overflows(var, shift)
#define int128_shr32_overflows(var, shift)  __hybrid_int128_shr32_overflows(var, shift)
#define uint128_shr64_overflows(var, shift) __hybrid_uint128_shr64_overflows(var, shift)
#define int128_shr64_overflows(var, shift)  __hybrid_int128_shr64_overflows(var, shift)
#define uint128_shr_overflows(var, shift)   __hybrid_uint128_shr_overflows(var, shift)
#define int128_shr_overflows(var, shift)    __hybrid_int128_shr_overflows(var, shift)
#define int128_setzero(var)                 __hybrid_int128_setzero(var)
#define int128_iszero(var)                  __hybrid_int128_iszero(var)
#define uint128_setzero(var)                __hybrid_uint128_setzero(var)
#define uint128_iszero(var)                 __hybrid_uint128_iszero(var)
#define int128_setone(var)                  __hybrid_int128_setone(var)
#define int128_isone(var)                   __hybrid_int128_isone(var)
#define uint128_setone(var)                 __hybrid_uint128_setone(var)
#define uint128_isone(var)                  __hybrid_uint128_isone(var)
#define int128_setminusone(var)             __hybrid_int128_setminusone(var)
#define int128_isminusone(var)              __hybrid_int128_isminusone(var)
#define int128_setmin(var)                  __hybrid_int128_setmin(var)
#define int128_ismin(var)                   __hybrid_int128_ismin(var)
#define int128_setmax(var)                  __hybrid_int128_setmax(var)
#define int128_ismax(var)                   __hybrid_int128_ismax(var)
#define int128_setzero_minus_min(var)       __hybrid_int128_setzero_minus_min(var)
#define int128_iszero_minus_min(var)        __hybrid_int128_iszero_minus_min(var)
#define uint128_setmin                      __hybrid_uint128_setmin
#define uint128_ismax(var)                  __hybrid_uint128_ismax(var)
#define uint128_ismin                       __hybrid_uint128_ismin
#define uint128_setmax(var)                 __hybrid_uint128_setmax(var)
#define uint128_is8bit(var)                 __hybrid_uint128_is8bit(var)
#define uint128_is16bit(var)                __hybrid_uint128_is16bit(var)
#define uint128_is32bit(var)                __hybrid_uint128_is32bit(var)
#define uint128_is64bit(var)                __hybrid_uint128_is64bit(var)
#define int128_is8bit(var)                  __hybrid_int128_is8bit(var)
#define int128_is16bit(var)                 __hybrid_int128_is16bit(var)
#define int128_is32bit(var)                 __hybrid_int128_is32bit(var)
#define int128_is64bit(var)                 __hybrid_int128_is64bit(var)
#define uint128_eq(var, v)                  __hybrid_uint128_eq(var, v)
#define uint128_eq8(var, v)                 __hybrid_uint128_eq8(var, v)
#define uint128_eq16(var, v)                __hybrid_uint128_eq16(var, v)
#define uint128_eq32(var, v)                __hybrid_uint128_eq32(var, v)
#define uint128_eq128(var, v)               __hybrid_uint128_eq128(var, v)
#define int128_eq(var, v)                   __hybrid_int128_eq(var, v)
#define int128_eq8(var, v)                  __hybrid_int128_eq8(var, v)
#define int128_eq16(var, v)                 __hybrid_int128_eq16(var, v)
#define int128_eq32(var, v)                 __hybrid_int128_eq32(var, v)
#define int128_eq128(var, v)                __hybrid_int128_eq128(var, v)
#ifdef __UINT64_TYPE__
#define int128_vec64(var)                   __hybrid_int128_vec64(var)
#define uint128_vec64(var)                  __hybrid_uint128_vec64(var)
#define int128_vec64_significand(var, i)    __hybrid_int128_vec64_significand(var, i)
#define uint128_vec64_significand(var, i)   __hybrid_uint128_vec64_significand(var, i)
#define int128_get64(var)                   __hybrid_int128_get64(var)
#define int128_set64(var, v)                __hybrid_int128_set64(var, v)
#define uint128_get64(var)                  __hybrid_uint128_get64(var)
#define uint128_set64(var, v)               __hybrid_uint128_set64(var, v)
#define uint128_and64(var, v)               __hybrid_uint128_and64(var, v)
#define int128_and64(var, v)                __hybrid_int128_and64(var, v)
#define uint128_or64(var, v)                __hybrid_uint128_or64(var, v)
#define int128_or64(var, v)                 __hybrid_int128_or64(var, v)
#define uint128_xor64(var, v)               __hybrid_uint128_xor64(var, v)
#define int128_xor64(var, v)                __hybrid_int128_xor64(var, v)
#define uint128_eq64(var, v)                __hybrid_uint128_eq64(var, v)
#define int128_eq64(var, v)                 __hybrid_int128_eq64(var, v)
#endif /* __UINT64_TYPE__ */
#endif /* !__INTELLISENSE__ || !__cplusplus */


__SYSDECL_END
#endif /* __CC__ */

#endif /* !_INT128_H */
