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
typedef __hybrid_int128_t int128_t;
typedef __hybrid_uint128_t uint128_t;

#if defined(__INTELLISENSE__) && defined(__cplusplus)

__int8_t (&int128_vec8(int128_t &__var))[16];
__int16_t (&int128_vec16(int128_t &__var))[8];
__int32_t (&int128_vec32(int128_t &__var))[4];
__uint8_t (&uint128_vec8(uint128_t &__var))[16];
__uint16_t (&uint128_vec16(uint128_t &__var))[8];
__uint32_t (&uint128_vec32(uint128_t &__var))[4];
__int8_t &int128_vec8_significand(int128_t &__var, unsigned int __i);
__int16_t &int128_vec16_significand(int128_t &__var, unsigned int __i);
__int32_t &int128_vec32_significand(int128_t &__var, unsigned int __i);
__uint8_t &uint128_vec8_significand(uint128_t &__var, unsigned int __i);
__uint16_t &uint128_vec16_significand(uint128_t &__var, unsigned int __i);
__uint32_t &uint128_vec32_significand(uint128_t &__var, unsigned int __i);
__int8_t int128_get8(int128_t &__var);
void int128_set8(int128_t &__var, __int8_t __value);
__uint8_t uint128_get8(uint128_t &__var);
void uint128_set8(uint128_t &__var, __uint8_t __value);
__int16_t int128_get16(int128_t &__var);
void int128_set16(int128_t &__var, __int16_t __value);
__uint16_t uint128_get16(uint128_t &__var);
void uint128_set16(uint128_t &__var, __uint16_t __value);
__int32_t int128_get32(int128_t &__var);
void int128_set32(int128_t &__var, __int32_t __value);
__uint32_t uint128_get32(uint128_t &__var);
void uint128_set32(uint128_t &__var, __uint32_t __value);
#ifdef __UINT64_TYPE__
__int64_t (&int128_vec64(int128_t &__var))[4];
__uint64_t (&uint128_vec64(uint128_t &__var))[4];
__int64_t &int128_vec64_significand(int128_t &__var, unsigned int __i);
__uint64_t &uint128_vec64_significand(uint128_t &__var, unsigned int __i);
__int64_t int128_get64(int128_t &__var);
void int128_set64(int128_t &__var, __int64_t __value);
__uint64_t uint128_get64(uint128_t &__var);
void uint128_set64(uint128_t &__var, __uint64_t __value);
#endif /* __UINT64_TYPE__ */

void int128_set(int128_t &__var, signed char __value);
void int128_set(int128_t &__var, short __value);
void int128_set(int128_t &__var, int __value);
void int128_set(int128_t &__var, long __value);
void int128_set(int128_t &__var, __LONGLONG __value);
void uint128_set(uint128_t &__var, unsigned char __value);
void uint128_set(uint128_t &__var, unsigned short __value);
void uint128_set(uint128_t &__var, unsigned int __value);
void uint128_set(uint128_t &__var, unsigned long __value);
void uint128_set(uint128_t &__var, __ULONGLONG __value);
#ifdef __CHAR_UNSIGNED__
void uint128_set(uint128_t &__var, char __value);
#else /* __CHAR_UNSIGNED__ */
void uint128_set(int128_t &__var, char __value);
#endif /* !__CHAR_UNSIGNED__ */

#else /* __INTELLISENSE__ && __cplusplus */
#define int128_vec8(var)                  __hybrid_int128_vec8(var)
#define int128_vec16(var)                 __hybrid_int128_vec16(var)
#define int128_vec32(var)                 __hybrid_int128_vec32(var)
#define uint128_vec8(var)                 __hybrid_uint128_vec8(var)
#define uint128_vec16(var)                __hybrid_uint128_vec16(var)
#define uint128_vec32(var)                __hybrid_uint128_vec32(var)
#define int128_vec8_significand(var, i)   __hybrid_int128_vec8_significand(var, i)
#define int128_vec16_significand(var, i)  __hybrid_int128_vec16_significand(var, i)
#define int128_vec32_significand(var, i)  __hybrid_int128_vec32_significand(var, i)
#define uint128_vec8_significand(var, i)  __hybrid_uint128_vec8_significand(var, i)
#define uint128_vec16_significand(var, i) __hybrid_uint128_vec16_significand(var, i)
#define uint128_vec32_significand(var, i) __hybrid_uint128_vec32_significand(var, i)
#define int128_get8(var)                  __hybrid_int128_get8(var)
#define int128_set8(var, v)               __hybrid_int128_set8(var, v)
#define uint128_get8(var)                 __hybrid_uint128_get8(var)
#define uint128_set8(var, v)              __hybrid_uint128_set8(var, v)
#define int128_get16(var)                 __hybrid_int128_get16(var)
#define int128_set16(var, v)              __hybrid_int128_set16(var, v)
#define uint128_get16(var)                __hybrid_uint128_get16(var)
#define uint128_set16(var, v)             __hybrid_uint128_set16(var, v)
#define int128_get32(var)                 __hybrid_int128_get32(var)
#define int128_set32(var, v)              __hybrid_int128_set32(var, v)
#define uint128_get32(var)                __hybrid_uint128_get32(var)
#define uint128_set32(var, v)             __hybrid_uint128_set32(var, v)
#define int128_set(var, v)                __hybrid_int128_set(var, v)
#define uint128_set(var, v)               __hybrid_uint128_set(var, v)
#ifdef __UINT64_TYPE__
#define int128_vec64(var)                 __hybrid_int128_vec64(var)
#define uint128_vec64(var)                __hybrid_uint128_vec64(var)
#define int128_vec64_significand(var, i)  __hybrid_int128_vec64_significand(var, i)
#define uint128_vec64_significand(var, i) __hybrid_uint128_vec64_significand(var, i)
#define int128_get64(var)                 __hybrid_int128_get64(var)
#define int128_set64(var, v)              __hybrid_int128_set64(var, v)
#define uint128_get64(var)                __hybrid_uint128_get64(var)
#define uint128_set64(var, v)             __hybrid_uint128_set64(var, v)
#endif /* __UINT64_TYPE__ */
#endif /* !__INTELLISENSE__ || !__cplusplus */


__SYSDECL_END
#endif /* __CC__ */

#endif /* !_INT128_H */
