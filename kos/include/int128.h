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
#ifndef _INT128_H
#define _INT128_H 1

#include <__stdinc.h>

#include <hybrid/int128.h>

#include <bits/types.h>

/* HINT: If your compiling your program with C++, you can enable c++ operator
 *       integration for (u)int128_t  for (most) standard  operators by  pre-
 *       defining  a  macro  `#define WANT_INT128_CXX_INTEGRATION 1'  at  the
 *       start of your source file. */

#ifdef __CC__
__SYSDECL_BEGIN

/* 128-bit integer types. */
#ifndef __int128_t_defined
#define __int128_t_defined
typedef __hybrid_int128_t int128_t;
typedef __hybrid_uint128_t uint128_t;
#endif /* !__int128_t_defined */

/* Static initializers. */
#define INT128_INIT8(val)                                                                     __HYBRID_INT128_INIT8(val)
#define INT128_INIT16(val)                                                                    __HYBRID_INT128_INIT16(val)
#define INT128_INIT32(val)                                                                    __HYBRID_INT128_INIT32(val)
#define UINT128_INIT8(val)                                                                    __HYBRID_UINT128_INIT8(val)
#define UINT128_INIT16(val)                                                                   __HYBRID_UINT128_INIT16(val)
#define UINT128_INIT32(val)                                                                   __HYBRID_UINT128_INIT32(val)
#define INT128_INIT8N(_16, _15, _14, _13, _12, _11, _10, _9, _8, _7, _6, _5, _4, _3, _2, _1)  __HYBRID_INT128_INIT8N(_16, _15, _14, _13, _12, _11, _10, _9, _8, _7, _6, _5, _4, _3, _2, _1)
#define UINT128_INIT8N(_16, _15, _14, _13, _12, _11, _10, _9, _8, _7, _6, _5, _4, _3, _2, _1) __HYBRID_UINT128_INIT8N(_16, _15, _14, _13, _12, _11, _10, _9, _8, _7, _6, _5, _4, _3, _2, _1)
#define INT128_INIT16N(_8, _7, _6, _5, _4, _3, _2, _1)                                        __HYBRID_INT128_INIT16N(_8, _7, _6, _5, _4, _3, _2, _1)
#define UINT128_INIT16N(_8, _7, _6, _5, _4, _3, _2, _1)                                       __HYBRID_UINT128_INIT16N(_8, _7, _6, _5, _4, _3, _2, _1)
#define INT128_INIT32N(_4, _3, _2, _1)                                                        __HYBRID_INT128_INIT32N(_4, _3, _2, _1)
#define UINT128_INIT32N(_4, _3, _2, _1)                                                       __HYBRID_UINT128_INIT32N(_4, _3, _2, _1)
#ifdef __UINT64_TYPE__
#define INT128_INIT64(val)                                                                    __HYBRID_INT128_INIT64(val)
#define UINT128_INIT64(val)                                                                   __HYBRID_UINT128_INIT64(val)
#define INT128_INIT64N(_2, _1)                                                                __HYBRID_INT128_INIT64N(_2, _1)
#define UINT128_INIT64N(_2, _1)                                                               __HYBRID_UINT128_INIT64N(_2, _1)
#define INT128_INIT(val)  __HYBRID_INT128_INIT64(val)
#define UINT128_INIT(val) __HYBRID_UINT128_INIT64(val)
#else /* __UINT64_TYPE__ */
#define INT128_INIT(val)  __HYBRID_INT128_INIT32(val)
#define UINT128_INIT(val) __HYBRID_UINT128_INIT32(val)
#endif /* !__UINT64_TYPE__ */

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
__ATTR_WUNUSED __ATTR_CONST __int64_t (&int128_vec64(int128_t &__var))[2];
__ATTR_WUNUSED __ATTR_CONST __int64_t const (&int128_vec64(int128_t const &__var))[2];
__ATTR_WUNUSED __ATTR_CONST __uint64_t (&uint128_vec64(uint128_t &__var))[2];
__ATTR_WUNUSED __ATTR_CONST __uint64_t const (&uint128_vec64(uint128_t const &__var))[2];
#endif /* __UINT64_TYPE__ */

/* Return a reference to the  I'th least significant word,  where 0 is the  least
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
__ATTR_PURE __ATTR_WUNUSED __int8_t int128_get8(int128_t const &__var);
__ATTR_PURE __ATTR_WUNUSED __uint8_t uint128_get8(uint128_t const &__var);
__ATTR_PURE __ATTR_WUNUSED __int16_t int128_get16(int128_t const &__var);
__ATTR_PURE __ATTR_WUNUSED __uint16_t uint128_get16(uint128_t const &__var);
__ATTR_PURE __ATTR_WUNUSED __int32_t int128_get32(int128_t const &__var);
__ATTR_PURE __ATTR_WUNUSED __uint32_t uint128_get32(uint128_t const &__var);
#ifdef __UINT64_TYPE__
__ATTR_PURE __ATTR_WUNUSED __int64_t int128_get64(int128_t const &__var);
__ATTR_PURE __ATTR_WUNUSED __uint64_t uint128_get64(uint128_t const &__var);
#endif /* __UINT64_TYPE__ */

/* Construct a 128-bit integer, given its individual words in least->most significand order. */
void int128_pack8(int128_t &__var,
                  __uint8_t a, __uint8_t b, __uint8_t c, __uint8_t d,
                  __uint8_t e, __uint8_t f, __uint8_t g, __uint8_t h,
                  __uint8_t i, __uint8_t j, __uint8_t k, __uint8_t l,
                  __uint8_t m, __uint8_t n, __uint8_t o, __uint8_t p);
void int128_pack16(int128_t &__var,
                   __uint16_t a, __uint16_t b, __uint16_t c, __uint16_t d,
                   __uint16_t e, __uint16_t f, __uint16_t g, __uint16_t h);
void int128_pack32(int128_t &__var, __uint32_t a, __uint32_t b, __uint32_t c, __uint32_t d);
void uint128_pack8(uint128_t &__var,
                   __uint8_t a, __uint8_t b, __uint8_t c, __uint8_t d,
                   __uint8_t e, __uint8_t f, __uint8_t g, __uint8_t h,
                   __uint8_t i, __uint8_t j, __uint8_t k, __uint8_t l,
                   __uint8_t m, __uint8_t n, __uint8_t o, __uint8_t p);
void uint128_pack16(uint128_t &__var,
                    __uint16_t a, __uint16_t b, __uint16_t c, __uint16_t d,
                    __uint16_t e, __uint16_t f, __uint16_t g, __uint16_t h);
void uint128_pack32(uint128_t &__var, __uint32_t a, __uint32_t b, __uint32_t c, __uint32_t d);
#ifdef __UINT64_TYPE__
void int128_pack64(int128_t &__var, __uint64_t lo, __uint64_t hi);
void uint128_pack64(uint128_t &__var, __uint64_t lo, __uint64_t hi);
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
#ifndef __CHAR_UNSIGNED__
void int128_set(int128_t &__var, char __value);
#endif /* !__CHAR_UNSIGNED__ */
void int128_set(int128_t &__var, signed char __value);
void int128_set(int128_t &__var, short __value);
void int128_set(int128_t &__var, int __value);
void int128_set(int128_t &__var, long __value);
#ifdef __CHAR_UNSIGNED__
void uint128_set(uint128_t &__var, char __value);
#endif /* __CHAR_UNSIGNED__ */
void uint128_set(uint128_t &__var, unsigned char __value);
void uint128_set(uint128_t &__var, unsigned short __value);
void uint128_set(uint128_t &__var, unsigned int __value);
void uint128_set(uint128_t &__var, unsigned long __value);
#ifdef __COMPILER_HAVE_LONGLONG
void int128_set(int128_t &__var, __LONGLONG __value);
void uint128_set(uint128_t &__var, __ULONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
void int128_set(int128_t &__var, __int8 __value);
void uint128_set(uint128_t &__var, unsigned __int8 __value);
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
void int128_set(int128_t &__var, __int16 __value);
void uint128_set(uint128_t &__var, unsigned __int16 __value);
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
void int128_set(int128_t &__var, __int32 __value);
void uint128_set(uint128_t &__var, unsigned __int32 __value);
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
void int128_set(int128_t &__var, __int64 __value);
void uint128_set(uint128_t &__var, unsigned __int64 __value);
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */

/* `++var' */
void uint128_inc(uint128_t &__var);
void int128_inc(int128_t &__var);

/* `--var' */
void uint128_dec(uint128_t &__var);
void int128_dec(int128_t &__var);

/* `var = ~var' */
void uint128_inv(uint128_t &__var);
void int128_inv(int128_t &__var);

/* `var = -var' */
void int128_neg(int128_t &__var);

/* `var < 0' */
__ATTR_PURE __ATTR_WUNUSED bool int128_isneg(int128_t const &__var);

/* `var &= value' */
#ifdef __CHAR_UNSIGNED__
void uint128_and(uint128_t &__var, char __value);
#endif /* __CHAR_UNSIGNED__ */
void uint128_and(uint128_t &__var, unsigned char __value);
void uint128_and(uint128_t &__var, unsigned short __value);
void uint128_and(uint128_t &__var, unsigned int __value);
void uint128_and(uint128_t &__var, unsigned long __value);
#ifdef __COMPILER_HAVE_LONGLONG
void uint128_and(uint128_t &__var, __ULONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
void uint128_and8(uint128_t &__var, __UINT8_TYPE__ __value);
void uint128_and16(uint128_t &__var, __UINT16_TYPE__ __value);
void uint128_and32(uint128_t &__var, __UINT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void uint128_and64(uint128_t &__var, __UINT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void uint128_and128(uint128_t &__var, int128_t const &__value);
void uint128_and128(uint128_t &__var, uint128_t const &__value);
#ifndef __CHAR_UNSIGNED__
void int128_and(int128_t &__var, char __value);
#endif /* !__CHAR_UNSIGNED__ */
void int128_and(int128_t &__var, signed char __value);
void int128_and(int128_t &__var, short __value);
void int128_and(int128_t &__var, int __value);
void int128_and(int128_t &__var, long __value);
#ifdef __COMPILER_HAVE_LONGLONG
void int128_and(int128_t &__var, __LONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
void int128_and8(int128_t &__var, __INT8_TYPE__ __value);
void int128_and16(int128_t &__var, __INT16_TYPE__ __value);
void int128_and32(int128_t &__var, __INT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void int128_and64(int128_t &__var, __INT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void int128_and128(int128_t &__var, int128_t const &__value);
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
void int128_and(int128_t &__var, __int8 __value);
void uint128_and(uint128_t &__var, unsigned __int8 __value);
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
void int128_and(int128_t &__var, __int16 __value);
void uint128_and(uint128_t &__var, unsigned __int16 __value);
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
void int128_and(int128_t &__var, __int32 __value);
void uint128_and(uint128_t &__var, unsigned __int32 __value);
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
void int128_and(int128_t &__var, __int64 __value);
void uint128_and(uint128_t &__var, unsigned __int64 __value);
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */

/* `var |= value' */
#ifdef __CHAR_UNSIGNED__
void uint128_or(uint128_t &__var, char __value);
#endif /* __CHAR_UNSIGNED__ */
void uint128_or(uint128_t &__var, unsigned char __value);
void uint128_or(uint128_t &__var, unsigned short __value);
void uint128_or(uint128_t &__var, unsigned int __value);
void uint128_or(uint128_t &__var, unsigned long __value);
#ifdef __COMPILER_HAVE_LONGLONG
void uint128_or(uint128_t &__var, __ULONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
void uint128_or8(uint128_t &__var, __UINT8_TYPE__ __value);
void uint128_or16(uint128_t &__var, __UINT16_TYPE__ __value);
void uint128_or32(uint128_t &__var, __UINT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void uint128_or64(uint128_t &__var, __UINT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void uint128_or128(uint128_t &__var, int128_t const &__value);
void uint128_or128(uint128_t &__var, uint128_t const &__value);
#ifndef __CHAR_UNSIGNED__
void int128_or(int128_t &__var, char __value);
#endif /* !__CHAR_UNSIGNED__ */
void int128_or(int128_t &__var, signed char __value);
void int128_or(int128_t &__var, short __value);
void int128_or(int128_t &__var, int __value);
void int128_or(int128_t &__var, long __value);
#ifdef __COMPILER_HAVE_LONGLONG
void int128_or(int128_t &__var, __LONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
void int128_or8(int128_t &__var, __INT8_TYPE__ __value);
void int128_or16(int128_t &__var, __INT16_TYPE__ __value);
void int128_or32(int128_t &__var, __INT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void int128_or64(int128_t &__var, __INT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void int128_or128(int128_t &__var, int128_t const &__value);
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
void int128_or(int128_t &__var, __int8 __value);
void uint128_or(uint128_t &__var, unsigned __int8 __value);
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
void int128_or(int128_t &__var, __int16 __value);
void uint128_or(uint128_t &__var, unsigned __int16 __value);
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
void int128_or(int128_t &__var, __int32 __value);
void uint128_or(uint128_t &__var, unsigned __int32 __value);
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
void int128_or(int128_t &__var, __int64 __value);
void uint128_or(uint128_t &__var, unsigned __int64 __value);
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */

/* `var ^= value' */
#ifdef __CHAR_UNSIGNED__
void uint128_xor(uint128_t &__var, char __value);
#endif /* __CHAR_UNSIGNED__ */
void uint128_xor(uint128_t &__var, unsigned char __value);
void uint128_xor(uint128_t &__var, unsigned short __value);
void uint128_xor(uint128_t &__var, unsigned int __value);
void uint128_xor(uint128_t &__var, unsigned long __value);
#ifdef __COMPILER_HAVE_LONGLONG
void uint128_xor(uint128_t &__var, __ULONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
void uint128_xor8(uint128_t &__var, __UINT8_TYPE__ __value);
void uint128_xor16(uint128_t &__var, __UINT16_TYPE__ __value);
void uint128_xor32(uint128_t &__var, __UINT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void uint128_xor64(uint128_t &__var, __UINT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void uint128_xor128(uint128_t &__var, int128_t const &__value);
void uint128_xor128(uint128_t &__var, uint128_t const &__value);
#ifndef __CHAR_UNSIGNED__
void int128_xor(int128_t &__var, char __value);
#endif /* !__CHAR_UNSIGNED__ */
void int128_xor(int128_t &__var, signed char __value);
void int128_xor(int128_t &__var, short __value);
void int128_xor(int128_t &__var, int __value);
void int128_xor(int128_t &__var, long __value);
#ifdef __COMPILER_HAVE_LONGLONG
void int128_xor(int128_t &__var, __LONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
void int128_xor8(int128_t &__var, __INT8_TYPE__ __value);
void int128_xor16(int128_t &__var, __INT16_TYPE__ __value);
void int128_xor32(int128_t &__var, __INT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void int128_xor64(int128_t &__var, __INT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void int128_xor128(int128_t &__var, int128_t const &__value);
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
void int128_xor(int128_t &__var, __int8 __value);
void uint128_xor(uint128_t &__var, unsigned __int8 __value);
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
void int128_xor(int128_t &__var, __int16 __value);
void uint128_xor(uint128_t &__var, unsigned __int16 __value);
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
void int128_xor(int128_t &__var, __int32 __value);
void uint128_xor(uint128_t &__var, unsigned __int32 __value);
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
void int128_xor(int128_t &__var, __int64 __value);
void uint128_xor(uint128_t &__var, unsigned __int64 __value);
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */

/* `var += value' */
#ifdef __CHAR_UNSIGNED__
void uint128_add(uint128_t &__var, char __value);
#endif /* __CHAR_UNSIGNED__ */
void uint128_add(uint128_t &__var, unsigned char __value);
void uint128_add(uint128_t &__var, unsigned short __value);
void uint128_add(uint128_t &__var, unsigned int __value);
void uint128_add(uint128_t &__var, unsigned long __value);
#ifdef __COMPILER_HAVE_LONGLONG
void uint128_add(uint128_t &__var, __ULONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
void uint128_add8(uint128_t &__var, __UINT8_TYPE__ __value);
void uint128_add16(uint128_t &__var, __UINT16_TYPE__ __value);
void uint128_add32(uint128_t &__var, __UINT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void uint128_add64(uint128_t &__var, __UINT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void uint128_add128(uint128_t &__var, int128_t const &__value);
void uint128_add128(uint128_t &__var, uint128_t const &__value);
#ifndef __CHAR_UNSIGNED__
void int128_add(int128_t &__var, char __value);
#endif /* !__CHAR_UNSIGNED__ */
void int128_add(int128_t &__var, signed char __value);
void int128_add(int128_t &__var, short __value);
void int128_add(int128_t &__var, int __value);
void int128_add(int128_t &__var, long __value);
#ifdef __COMPILER_HAVE_LONGLONG
void int128_add(int128_t &__var, __LONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
void int128_add8(int128_t &__var, __INT8_TYPE__ __value);
void int128_add16(int128_t &__var, __INT16_TYPE__ __value);
void int128_add32(int128_t &__var, __INT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void int128_add64(int128_t &__var, __INT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void int128_add128(int128_t &__var, int128_t const &__value);
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
void int128_add(int128_t &__var, __int8 __value);
void uint128_add(uint128_t &__var, unsigned __int8 __value);
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
void int128_add(int128_t &__var, __int16 __value);
void uint128_add(uint128_t &__var, unsigned __int16 __value);
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
void int128_add(int128_t &__var, __int32 __value);
void uint128_add(uint128_t &__var, unsigned __int32 __value);
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
void int128_add(int128_t &__var, __int64 __value);
void uint128_add(uint128_t &__var, unsigned __int64 __value);
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */

/* `var -= value' */
#ifdef __CHAR_UNSIGNED__
void uint128_sub(uint128_t &__var, char __value);
#endif /* __CHAR_UNSIGNED__ */
void uint128_sub(uint128_t &__var, unsigned char __value);
void uint128_sub(uint128_t &__var, unsigned short __value);
void uint128_sub(uint128_t &__var, unsigned int __value);
void uint128_sub(uint128_t &__var, unsigned long __value);
#ifdef __COMPILER_HAVE_LONGLONG
void uint128_sub(uint128_t &__var, __ULONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
void uint128_sub8(uint128_t &__var, __UINT8_TYPE__ __value);
void uint128_sub16(uint128_t &__var, __UINT16_TYPE__ __value);
void uint128_sub32(uint128_t &__var, __UINT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void uint128_sub64(uint128_t &__var, __UINT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void uint128_sub128(uint128_t &__var, int128_t const &__value);
void uint128_sub128(uint128_t &__var, uint128_t const &__value);
#ifndef __CHAR_UNSIGNED__
void int128_sub(int128_t &__var, char __value);
#endif /* !__CHAR_UNSIGNED__ */
void int128_sub(int128_t &__var, signed char __value);
void int128_sub(int128_t &__var, short __value);
void int128_sub(int128_t &__var, int __value);
void int128_sub(int128_t &__var, long __value);
#ifdef __COMPILER_HAVE_LONGLONG
void int128_sub(int128_t &__var, __LONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
void int128_sub8(int128_t &__var, __INT8_TYPE__ __value);
void int128_sub16(int128_t &__var, __INT16_TYPE__ __value);
void int128_sub32(int128_t &__var, __INT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void int128_sub64(int128_t &__var, __INT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void int128_sub128(int128_t &__var, int128_t const &__value);
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
void int128_sub(int128_t &__var, __int8 __value);
void uint128_sub(uint128_t &__var, unsigned __int8 __value);
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
void int128_sub(int128_t &__var, __int16 __value);
void uint128_sub(uint128_t &__var, unsigned __int16 __value);
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
void int128_sub(int128_t &__var, __int32 __value);
void uint128_sub(uint128_t &__var, unsigned __int32 __value);
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
void int128_sub(int128_t &__var, __int64 __value);
void uint128_sub(uint128_t &__var, unsigned __int64 __value);
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */

/* `var *= value' */
#ifdef __CHAR_UNSIGNED__
void uint128_mul(uint128_t &__var, char __value);
#endif /* __CHAR_UNSIGNED__ */
void uint128_mul(uint128_t &__var, unsigned char __value);
void uint128_mul(uint128_t &__var, unsigned short __value);
void uint128_mul(uint128_t &__var, unsigned int __value);
void uint128_mul(uint128_t &__var, unsigned long __value);
#ifdef __COMPILER_HAVE_LONGLONG
void uint128_mul(uint128_t &__var, __ULONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
void uint128_mul8(uint128_t &__var, __UINT8_TYPE__ __value);
void uint128_mul16(uint128_t &__var, __UINT16_TYPE__ __value);
void uint128_mul32(uint128_t &__var, __UINT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void uint128_mul64(uint128_t &__var, __UINT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void uint128_mul128(uint128_t &__var, int128_t const &__value);
void uint128_mul128(uint128_t &__var, uint128_t const &__value);
#ifndef __CHAR_UNSIGNED__
void int128_mul(int128_t &__var, char __value);
#endif /* !__CHAR_UNSIGNED__ */
void int128_mul(int128_t &__var, signed char __value);
void int128_mul(int128_t &__var, short __value);
void int128_mul(int128_t &__var, int __value);
void int128_mul(int128_t &__var, long __value);
#ifdef __COMPILER_HAVE_LONGLONG
void int128_mul(int128_t &__var, __LONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
void int128_mul8(int128_t &__var, __INT8_TYPE__ __value);
void int128_mul16(int128_t &__var, __INT16_TYPE__ __value);
void int128_mul32(int128_t &__var, __INT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void int128_mul64(int128_t &__var, __INT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void int128_mul128(int128_t &__var, int128_t const &__value);
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
void int128_mul(int128_t &__var, __int8 __value);
void uint128_mul(uint128_t &__var, unsigned __int8 __value);
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
void int128_mul(int128_t &__var, __int16 __value);
void uint128_mul(uint128_t &__var, unsigned __int16 __value);
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
void int128_mul(int128_t &__var, __int32 __value);
void uint128_mul(uint128_t &__var, unsigned __int32 __value);
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
void int128_mul(int128_t &__var, __int64 __value);
void uint128_mul(uint128_t &__var, unsigned __int64 __value);
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */

/* `var /= value' */
#ifdef __CHAR_UNSIGNED__
void uint128_div(uint128_t &__var, char __value);
#endif /* __CHAR_UNSIGNED__ */
void uint128_div(uint128_t &__var, unsigned char __value);
void uint128_div(uint128_t &__var, unsigned short __value);
void uint128_div(uint128_t &__var, unsigned int __value);
void uint128_div(uint128_t &__var, unsigned long __value);
#ifdef __COMPILER_HAVE_LONGLONG
void uint128_div(uint128_t &__var, __ULONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
void uint128_div8(uint128_t &__var, __UINT8_TYPE__ __value);
void uint128_div16(uint128_t &__var, __UINT16_TYPE__ __value);
void uint128_div32(uint128_t &__var, __UINT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void uint128_div64(uint128_t &__var, __UINT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void uint128_div128(uint128_t &__var, int128_t const &__value);
void uint128_div128(uint128_t &__var, uint128_t const &__value);
#ifndef __CHAR_UNSIGNED__
void int128_div(int128_t &__var, char __value);
#endif /* !__CHAR_UNSIGNED__ */
void int128_div(int128_t &__var, signed char __value);
void int128_div(int128_t &__var, short __value);
void int128_div(int128_t &__var, int __value);
void int128_div(int128_t &__var, long __value);
#ifdef __COMPILER_HAVE_LONGLONG
void int128_div(int128_t &__var, __LONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
void int128_div8(int128_t &__var, __INT8_TYPE__ __value);
void int128_div16(int128_t &__var, __INT16_TYPE__ __value);
void int128_div32(int128_t &__var, __INT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void int128_div64(int128_t &__var, __INT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void int128_div128(int128_t &__var, int128_t const &__value);
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
void int128_div(int128_t &__var, __int8 __value);
void uint128_div(uint128_t &__var, unsigned __int8 __value);
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
void int128_div(int128_t &__var, __int16 __value);
void uint128_div(uint128_t &__var, unsigned __int16 __value);
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
void int128_div(int128_t &__var, __int32 __value);
void uint128_div(uint128_t &__var, unsigned __int32 __value);
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
void int128_div(int128_t &__var, __int64 __value);
void uint128_div(uint128_t &__var, unsigned __int64 __value);
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */

/* `var %= value' */
#ifdef __CHAR_UNSIGNED__
void uint128_mod(uint128_t &__var, char __value);
#endif /* __CHAR_UNSIGNED__ */
void uint128_mod(uint128_t &__var, unsigned char __value);
void uint128_mod(uint128_t &__var, unsigned short __value);
void uint128_mod(uint128_t &__var, unsigned int __value);
void uint128_mod(uint128_t &__var, unsigned long __value);
#ifdef __COMPILER_HAVE_LONGLONG
void uint128_mod(uint128_t &__var, __ULONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
void uint128_mod8(uint128_t &__var, __UINT8_TYPE__ __value);
void uint128_mod16(uint128_t &__var, __UINT16_TYPE__ __value);
void uint128_mod32(uint128_t &__var, __UINT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void uint128_mod64(uint128_t &__var, __UINT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void uint128_mod128(uint128_t &__var, uint128_t const &__value);
#ifndef __CHAR_UNSIGNED__
void int128_mod(int128_t &__var, char __value);
#endif /* !__CHAR_UNSIGNED__ */
void int128_mod(int128_t &__var, signed char __value);
void int128_mod(int128_t &__var, short __value);
void int128_mod(int128_t &__var, int __value);
void int128_mod(int128_t &__var, long __value);
#ifdef __COMPILER_HAVE_LONGLONG
void int128_mod(int128_t &__var, __LONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
void int128_mod8(int128_t &__var, __INT8_TYPE__ __value);
void int128_mod16(int128_t &__var, __INT16_TYPE__ __value);
void int128_mod32(int128_t &__var, __INT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void int128_mod64(int128_t &__var, __INT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void int128_mod128(int128_t &__var, int128_t const &__value);
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
void int128_mod(int128_t &__var, __int8 __value);
void uint128_mod(uint128_t &__var, unsigned __int8 __value);
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
void int128_mod(int128_t &__var, __int16 __value);
void uint128_mod(uint128_t &__var, unsigned __int16 __value);
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
void int128_mod(int128_t &__var, __int32 __value);
void uint128_mod(uint128_t &__var, unsigned __int32 __value);
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
void int128_mod(int128_t &__var, __int64 __value);
void uint128_mod(uint128_t &__var, unsigned __int64 __value);
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */

/* `res = var % value' */
#ifdef __CHAR_UNSIGNED__
void uint128_divmod(uint128_t const &__var, char __value, uint128_t &__divres, char &__modres);
#endif /* __CHAR_UNSIGNED__ */
void uint128_divmod(uint128_t const &__var, unsigned char __value, uint128_t &__divres, unsigned char &__modres);
void uint128_divmod(uint128_t const &__var, unsigned short __value, uint128_t &__divres, unsigned short &__modres);
void uint128_divmod(uint128_t const &__var, unsigned int __value, uint128_t &__divres, unsigned int &__modres);
void uint128_divmod(uint128_t const &__var, unsigned long __value, uint128_t &__divres, unsigned long &__modres);
#ifdef __COMPILER_HAVE_LONGLONG
void uint128_divmod(uint128_t const &__var, __ULONGLONG __value, uint128_t &__divres, __ULONGLONG &__modres);
#endif /* __COMPILER_HAVE_LONGLONG */
void uint128_divmod8(uint128_t const &__var, __UINT8_TYPE__ __value, uint128_t &__divres, __UINT8_TYPE__ &__modres);
void uint128_divmod16(uint128_t const &__var, __UINT16_TYPE__ __value, uint128_t &__divres, __UINT16_TYPE__ &__modres);
void uint128_divmod32(uint128_t const &__var, __UINT32_TYPE__ __value, uint128_t &__divres, __UINT32_TYPE__ &__modres);
#ifdef __UINT64_TYPE__
void uint128_divmod64(uint128_t const &__var, __UINT64_TYPE__ __value, uint128_t &__divres, __UINT64_TYPE__ &__modres);
#endif /* __UINT64_TYPE__ */
void uint128_divmod128(uint128_t const &__var, uint128_t const &__value, uint128_t &__divres, uint128_t &__modres);
#ifndef __CHAR_UNSIGNED__
void int128_divmod(int128_t const &__var, char __value, int128_t &__divres, char &__modres);
#endif /* !__CHAR_UNSIGNED__ */
void int128_divmod(int128_t const &__var, signed char __value, int128_t &__divres, signed char &__modres);
void int128_divmod(int128_t const &__var, short __value, int128_t &__divres, short &__modres);
void int128_divmod(int128_t const &__var, int __value, int128_t &__divres, int &__modres);
void int128_divmod(int128_t const &__var, long __value, int128_t &__divres, long &__modres);
#ifdef __COMPILER_HAVE_LONGLONG
void int128_divmod(int128_t const &__var, __LONGLONG __value, int128_t &__divres, __LONGLONG &__modres);
#endif /* __COMPILER_HAVE_LONGLONG */
void int128_divmod8(int128_t const &__var, __INT8_TYPE__ __value, int128_t &__divres, __INT8_TYPE__ &__modres);
void int128_divmod16(int128_t const &__var, __INT16_TYPE__ __value, int128_t &__divres, __INT16_TYPE__ &__modres);
void int128_divmod32(int128_t const &__var, __INT32_TYPE__ __value, int128_t &__divres, __INT32_TYPE__ &__modres);
#ifdef __UINT64_TYPE__
void int128_divmod64(int128_t const &__var, __INT64_TYPE__ __value, int128_t &__divres, __INT64_TYPE__ &__modres);
#endif /* __UINT64_TYPE__ */
void int128_divmod128(int128_t const &__var, int128_t const &__value, int128_t &__divres, int128_t &__modres);
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
void int128_divmod(int128_t const &__var, __int8 __value, int128_t &__divres, __int8 &__modres);
void uint128_divmod(uint128_t const &__var, unsigned __int8 __value, int128_t &__divres, unsigned __int8 &__modres);
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
void int128_divmod(int128_t const &__var, __int16 __value, int128_t &__divres, __int16 &__modres);
void uint128_divmod(uint128_t const &__var, unsigned __int16 __value, int128_t &__divres, unsigned __int16 &__modres);
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
void int128_divmod(int128_t const &__var, __int32 __value, int128_t &__divres, __int32 &__modres);
void uint128_divmod(uint128_t const &__var, unsigned __int32 __value, int128_t &__divres, unsigned __int32 &__modres);
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
void int128_divmod(int128_t const &__var, __int64 __value, int128_t &__divres, __int64 &__modres);
void uint128_divmod(uint128_t const &__var, unsigned __int64 __value, int128_t &__divres, unsigned __int64 &__modres);
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */

/* `res = var % value' */
void uint128_mod8_r(uint128_t const &__var, __UINT8_TYPE__ __value, __UINT8_TYPE__ &__res);
void uint128_mod16_r(uint128_t const &__var, __UINT16_TYPE__ __value, __UINT16_TYPE__ &__res);
void uint128_mod32_r(uint128_t const &__var, __UINT32_TYPE__ __value, __UINT32_TYPE__ &__res);
void int128_mod8_r(int128_t const &__var, __INT8_TYPE__ __value, __INT8_TYPE__ &__res);
void int128_mod16_r(int128_t const &__var, __INT16_TYPE__ __value, __INT16_TYPE__ &__res);
void int128_mod32_r(int128_t const &__var, __INT32_TYPE__ __value, __INT32_TYPE__ &__res);
#ifdef __UINT64_TYPE__
void uint128_mod64_r(uint128_t const &__var, __UINT64_TYPE__ __value, __UINT64_TYPE__ &__res);
void int128_mod64_r(int128_t const &__var, __INT64_TYPE__ __value, __INT64_TYPE__ &__res);
#endif /* __UINT64_TYPE__ */

/* `var = var <FLOOR_DIV> value' */
#ifndef __CHAR_UNSIGNED__
void int128_floordiv(int128_t &__var, char __value);
#endif /* !__CHAR_UNSIGNED__ */
void int128_floordiv(int128_t &__var, signed char __value);
void int128_floordiv(int128_t &__var, short __value);
void int128_floordiv(int128_t &__var, int __value);
void int128_floordiv(int128_t &__var, long __value);
#ifdef __COMPILER_HAVE_LONGLONG
void int128_floordiv(int128_t &__var, __LONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
void int128_floordiv8(int128_t &__var, __INT8_TYPE__ __value);
void int128_floordiv16(int128_t &__var, __INT16_TYPE__ __value);
void int128_floordiv32(int128_t &__var, __INT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void int128_floordiv64(int128_t &__var, __INT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void int128_floordiv128(int128_t &__var, int128_t const &__value);
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
void int128_floordiv(int128_t &__var, __int8 __value);
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
void int128_floordiv(int128_t &__var, __int16 __value);
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
void int128_floordiv(int128_t &__var, __int32 __value);
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
void int128_floordiv(int128_t &__var, __int64 __value);
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */

/* `var = var <FLOOR_MOD> value' */
#ifndef __CHAR_UNSIGNED__
void int128_floormod(int128_t &__var, char __value);
#endif /* !__CHAR_UNSIGNED__ */
void int128_floormod(int128_t &__var, signed char __value);
void int128_floormod(int128_t &__var, short __value);
void int128_floormod(int128_t &__var, int __value);
void int128_floormod(int128_t &__var, long __value);
#ifdef __COMPILER_HAVE_LONGLONG
void int128_floormod(int128_t &__var, __LONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
void int128_floormod8(int128_t &__var, __INT8_TYPE__ __value);
void int128_floormod16(int128_t &__var, __INT16_TYPE__ __value);
void int128_floormod32(int128_t &__var, __INT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
void int128_floormod64(int128_t &__var, __INT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
void int128_floormod128(int128_t &__var, int128_t const &__value);
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
void int128_floormod(int128_t &__var, __int8 __value);
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
void int128_floormod(int128_t &__var, __int16 __value);
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
void int128_floormod(int128_t &__var, __int32 __value);
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
void int128_floormod(int128_t &__var, __int64 __value);
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */

/* `res = var % value' */
#ifndef __CHAR_UNSIGNED__
void int128_floordivmod(int128_t const &__var, char __value, int128_t &__divres, unsigned char &__modres);
#endif /* !__CHAR_UNSIGNED__ */
void int128_floordivmod(int128_t const &__var, signed char __value, int128_t &__divres, unsigned char &__modres);
void int128_floordivmod(int128_t const &__var, short __value, int128_t &__divres, unsigned short &__modres);
void int128_floordivmod(int128_t const &__var, int __value, int128_t &__divres, unsigned int &__modres);
void int128_floordivmod(int128_t const &__var, long __value, int128_t &__divres, unsigned long &__modres);
#ifdef __COMPILER_HAVE_LONGLONG
void int128_floordivmod(int128_t const &__var, __LONGLONG __value, int128_t &__divres, __ULONGLONG &__modres);
#endif /* __COMPILER_HAVE_LONGLONG */
void int128_floordivmod8(int128_t const &__var, __INT8_TYPE__ __value, int128_t &__divres, __UINT8_TYPE__ &__modres);
void int128_floordivmod16(int128_t const &__var, __INT16_TYPE__ __value, int128_t &__divres, __UINT16_TYPE__ &__modres);
void int128_floordivmod32(int128_t const &__var, __INT32_TYPE__ __value, int128_t &__divres, __UINT32_TYPE__ &__modres);
#ifdef __UINT64_TYPE__
void int128_floordivmod64(int128_t const &__var, __INT64_TYPE__ __value, int128_t &__divres, __UINT64_TYPE__ &__modres);
#endif /* __UINT64_TYPE__ */
void int128_floordivmod128(int128_t const &__var, int128_t const &__value, int128_t &__divres, uint128_t &__modres);
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
void int128_floordivmod(int128_t const &__var, __int8 __value, int128_t &__divres, unsigned __int8 &__modres);
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
void int128_floordivmod(int128_t const &__var, __int16 __value, int128_t &__divres, unsigned __int16 &__modres);
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
void int128_floordivmod(int128_t const &__var, __int32 __value, int128_t &__divres, unsigned __int32 &__modres);
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
void int128_floordivmod(int128_t const &__var, __int64 __value, int128_t &__divres, unsigned __int64 &__modres);
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */

/* `res = var <FLOOR_MOD> value' */
void int128_floormod8_r(int128_t const &__var, __INT8_TYPE__ __value, __INT8_TYPE__ &__res);
void int128_floormod16_r(int128_t const &__var, __INT16_TYPE__ __value, __INT16_TYPE__ &__res);
void int128_floormod32_r(int128_t const &__var, __INT32_TYPE__ __value, __INT32_TYPE__ &__res);
#ifdef __UINT64_TYPE__
void int128_floormod64_r(int128_t const &__var, __INT64_TYPE__ __value, __INT64_TYPE__ &__res);
#endif /* __UINT64_TYPE__ */

/* `var == value' */
#ifdef __CHAR_UNSIGNED__
__ATTR_PURE __ATTR_WUNUSED bool uint128_eq(uint128_t const &__var, char __value);
#endif /* __CHAR_UNSIGNED__ */
__ATTR_PURE __ATTR_WUNUSED bool uint128_eq(uint128_t const &__var, unsigned char __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_eq(uint128_t const &__var, unsigned short __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_eq(uint128_t const &__var, unsigned int __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_eq(uint128_t const &__var, unsigned long __value);
#ifdef __COMPILER_HAVE_LONGLONG
__ATTR_PURE __ATTR_WUNUSED bool uint128_eq(uint128_t const &__var, __ULONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
__ATTR_PURE __ATTR_WUNUSED bool uint128_eq8(uint128_t const &__var, __UINT8_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_eq16(uint128_t const &__var, __UINT16_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_eq32(uint128_t const &__var, __UINT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
__ATTR_PURE __ATTR_WUNUSED bool uint128_eq64(uint128_t const &__var, __UINT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
__ATTR_PURE __ATTR_WUNUSED bool uint128_eq128(uint128_t const &__var, uint128_t const &__value);
#ifndef __CHAR_UNSIGNED__
__ATTR_PURE __ATTR_WUNUSED bool int128_eq(int128_t const &__var, char __value);
#endif /* !__CHAR_UNSIGNED__ */
__ATTR_PURE __ATTR_WUNUSED bool int128_eq(int128_t const &__var, signed char __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_eq(int128_t const &__var, short __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_eq(int128_t const &__var, int __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_eq(int128_t const &__var, long __value);
#ifdef __COMPILER_HAVE_LONGLONG
__ATTR_PURE __ATTR_WUNUSED bool int128_eq(int128_t const &__var, __LONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
__ATTR_PURE __ATTR_WUNUSED bool int128_eq8(int128_t const &__var, __INT8_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_eq16(int128_t const &__var, __INT16_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_eq32(int128_t const &__var, __INT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
__ATTR_PURE __ATTR_WUNUSED bool int128_eq64(int128_t const &__var, __INT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
__ATTR_PURE __ATTR_WUNUSED bool int128_eq128(int128_t const &__var, int128_t const &__value);
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_eq(int128_t const &__var, __int8 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_eq(uint128_t const &__var, unsigned __int8 __value);
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_eq(int128_t const &__var, __int16 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_eq(uint128_t const &__var, unsigned __int16 __value);
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_eq(int128_t const &__var, __int32 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_eq(uint128_t const &__var, unsigned __int32 __value);
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_eq(int128_t const &__var, __int64 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_eq(uint128_t const &__var, unsigned __int64 __value);
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */

/* `var != value' */
#ifdef __CHAR_UNSIGNED__
__ATTR_PURE __ATTR_WUNUSED bool uint128_ne(uint128_t const &__var, char __value);
#endif /* __CHAR_UNSIGNED__ */
__ATTR_PURE __ATTR_WUNUSED bool uint128_ne(uint128_t const &__var, unsigned char __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_ne(uint128_t const &__var, unsigned short __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_ne(uint128_t const &__var, unsigned int __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_ne(uint128_t const &__var, unsigned long __value);
#ifdef __COMPILER_HAVE_LONGLONG
__ATTR_PURE __ATTR_WUNUSED bool uint128_ne(uint128_t const &__var, __ULONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
__ATTR_PURE __ATTR_WUNUSED bool uint128_ne8(uint128_t const &__var, __UINT8_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_ne16(uint128_t const &__var, __UINT16_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_ne32(uint128_t const &__var, __UINT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
__ATTR_PURE __ATTR_WUNUSED bool uint128_ne64(uint128_t const &__var, __UINT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
__ATTR_PURE __ATTR_WUNUSED bool uint128_ne128(uint128_t const &__var, uint128_t const &__value);
#ifndef __CHAR_UNSIGNED__
__ATTR_PURE __ATTR_WUNUSED bool int128_ne(int128_t const &__var, char __value);
#endif /* !__CHAR_UNSIGNED__ */
__ATTR_PURE __ATTR_WUNUSED bool int128_ne(int128_t const &__var, signed char __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_ne(int128_t const &__var, short __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_ne(int128_t const &__var, int __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_ne(int128_t const &__var, long __value);
#ifdef __COMPILER_HAVE_LONGLONG
__ATTR_PURE __ATTR_WUNUSED bool int128_ne(int128_t const &__var, __LONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
__ATTR_PURE __ATTR_WUNUSED bool int128_ne8(int128_t const &__var, __INT8_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_ne16(int128_t const &__var, __INT16_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_ne32(int128_t const &__var, __INT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
__ATTR_PURE __ATTR_WUNUSED bool int128_ne64(int128_t const &__var, __INT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
__ATTR_PURE __ATTR_WUNUSED bool int128_ne128(int128_t const &__var, int128_t const &__value);
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_ne(int128_t const &__var, __int8 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_ne(uint128_t const &__var, unsigned __int8 __value);
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_ne(int128_t const &__var, __int16 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_ne(uint128_t const &__var, unsigned __int16 __value);
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_ne(int128_t const &__var, __int32 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_ne(uint128_t const &__var, unsigned __int32 __value);
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_ne(int128_t const &__var, __int64 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_ne(uint128_t const &__var, unsigned __int64 __value);
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */

/* `var < value' */
#ifdef __CHAR_UNSIGNED__
__ATTR_PURE __ATTR_WUNUSED bool uint128_lo(uint128_t const &__var, char __value);
#endif /* __CHAR_UNSIGNED__ */
__ATTR_PURE __ATTR_WUNUSED bool uint128_lo(uint128_t const &__var, unsigned char __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_lo(uint128_t const &__var, unsigned short __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_lo(uint128_t const &__var, unsigned int __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_lo(uint128_t const &__var, unsigned long __value);
#ifdef __COMPILER_HAVE_LONGLONG
__ATTR_PURE __ATTR_WUNUSED bool uint128_lo(uint128_t const &__var, __ULONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
__ATTR_PURE __ATTR_WUNUSED bool uint128_lo8(uint128_t const &__var, __UINT8_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_lo16(uint128_t const &__var, __UINT16_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_lo32(uint128_t const &__var, __UINT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
__ATTR_PURE __ATTR_WUNUSED bool uint128_lo64(uint128_t const &__var, __UINT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
__ATTR_PURE __ATTR_WUNUSED bool uint128_lo128(uint128_t const &__var, uint128_t const &__value);
#ifndef __CHAR_UNSIGNED__
__ATTR_PURE __ATTR_WUNUSED bool int128_lo(int128_t const &__var, char __value);
#endif /* !__CHAR_UNSIGNED__ */
__ATTR_PURE __ATTR_WUNUSED bool int128_lo(int128_t const &__var, signed char __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_lo(int128_t const &__var, short __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_lo(int128_t const &__var, int __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_lo(int128_t const &__var, long __value);
#ifdef __COMPILER_HAVE_LONGLONG
__ATTR_PURE __ATTR_WUNUSED bool int128_lo(int128_t const &__var, __LONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
__ATTR_PURE __ATTR_WUNUSED bool int128_lo8(int128_t const &__var, __INT8_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_lo16(int128_t const &__var, __INT16_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_lo32(int128_t const &__var, __INT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
__ATTR_PURE __ATTR_WUNUSED bool int128_lo64(int128_t const &__var, __INT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
__ATTR_PURE __ATTR_WUNUSED bool int128_lo128(int128_t const &__var, int128_t const &__value);
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_lo(int128_t const &__var, __int8 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_lo(uint128_t const &__var, unsigned __int8 __value);
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_lo(int128_t const &__var, __int16 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_lo(uint128_t const &__var, unsigned __int16 __value);
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_lo(int128_t const &__var, __int32 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_lo(uint128_t const &__var, unsigned __int32 __value);
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_lo(int128_t const &__var, __int64 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_lo(uint128_t const &__var, unsigned __int64 __value);
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */

/* `var <= value' */
#ifdef __CHAR_UNSIGNED__
__ATTR_PURE __ATTR_WUNUSED bool uint128_le(uint128_t const &__var, char __value);
#endif /* __CHAR_UNSIGNED__ */
__ATTR_PURE __ATTR_WUNUSED bool uint128_le(uint128_t const &__var, unsigned char __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_le(uint128_t const &__var, unsigned short __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_le(uint128_t const &__var, unsigned int __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_le(uint128_t const &__var, unsigned long __value);
#ifdef __COMPILER_HAVE_LONGLONG
__ATTR_PURE __ATTR_WUNUSED bool uint128_le(uint128_t const &__var, __ULONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
__ATTR_PURE __ATTR_WUNUSED bool uint128_le8(uint128_t const &__var, __UINT8_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_le16(uint128_t const &__var, __UINT16_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_le32(uint128_t const &__var, __UINT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
__ATTR_PURE __ATTR_WUNUSED bool uint128_le64(uint128_t const &__var, __UINT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
__ATTR_PURE __ATTR_WUNUSED bool uint128_le128(uint128_t const &__var, uint128_t const &__value);
#ifndef __CHAR_UNSIGNED__
__ATTR_PURE __ATTR_WUNUSED bool int128_le(int128_t const &__var, char __value);
#endif /* !__CHAR_UNSIGNED__ */
__ATTR_PURE __ATTR_WUNUSED bool int128_le(int128_t const &__var, signed char __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_le(int128_t const &__var, short __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_le(int128_t const &__var, int __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_le(int128_t const &__var, long __value);
#ifdef __COMPILER_HAVE_LONGLONG
__ATTR_PURE __ATTR_WUNUSED bool int128_le(int128_t const &__var, __LONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
__ATTR_PURE __ATTR_WUNUSED bool int128_le8(int128_t const &__var, __INT8_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_le16(int128_t const &__var, __INT16_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_le32(int128_t const &__var, __INT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
__ATTR_PURE __ATTR_WUNUSED bool int128_le64(int128_t const &__var, __INT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
__ATTR_PURE __ATTR_WUNUSED bool int128_le128(int128_t const &__var, int128_t const &__value);
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_le(int128_t const &__var, __int8 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_le(uint128_t const &__var, unsigned __int8 __value);
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_le(int128_t const &__var, __int16 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_le(uint128_t const &__var, unsigned __int16 __value);
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_le(int128_t const &__var, __int32 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_le(uint128_t const &__var, unsigned __int32 __value);
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_le(int128_t const &__var, __int64 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_le(uint128_t const &__var, unsigned __int64 __value);
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */

/* `var > value' */
#ifdef __CHAR_UNSIGNED__
__ATTR_PURE __ATTR_WUNUSED bool uint128_gr(uint128_t const &__var, char __value);
#endif /* __CHAR_UNSIGNED__ */
__ATTR_PURE __ATTR_WUNUSED bool uint128_gr(uint128_t const &__var, unsigned char __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_gr(uint128_t const &__var, unsigned short __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_gr(uint128_t const &__var, unsigned int __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_gr(uint128_t const &__var, unsigned long __value);
#ifdef __COMPILER_HAVE_LONGLONG
__ATTR_PURE __ATTR_WUNUSED bool uint128_gr(uint128_t const &__var, __ULONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
__ATTR_PURE __ATTR_WUNUSED bool uint128_gr8(uint128_t const &__var, __UINT8_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_gr16(uint128_t const &__var, __UINT16_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_gr32(uint128_t const &__var, __UINT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
__ATTR_PURE __ATTR_WUNUSED bool uint128_gr64(uint128_t const &__var, __UINT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
__ATTR_PURE __ATTR_WUNUSED bool uint128_gr128(uint128_t const &__var, uint128_t const &__value);
#ifndef __CHAR_UNSIGNED__
__ATTR_PURE __ATTR_WUNUSED bool int128_gr(int128_t const &__var, char __value);
#endif /* !__CHAR_UNSIGNED__ */
__ATTR_PURE __ATTR_WUNUSED bool int128_gr(int128_t const &__var, signed char __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_gr(int128_t const &__var, short __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_gr(int128_t const &__var, int __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_gr(int128_t const &__var, long __value);
#ifdef __COMPILER_HAVE_LONGLONG
__ATTR_PURE __ATTR_WUNUSED bool int128_gr(int128_t const &__var, __LONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
__ATTR_PURE __ATTR_WUNUSED bool int128_gr8(int128_t const &__var, __INT8_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_gr16(int128_t const &__var, __INT16_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_gr32(int128_t const &__var, __INT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
__ATTR_PURE __ATTR_WUNUSED bool int128_gr64(int128_t const &__var, __INT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
__ATTR_PURE __ATTR_WUNUSED bool int128_gr128(int128_t const &__var, int128_t const &__value);
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_gr(int128_t const &__var, __int8 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_gr(uint128_t const &__var, unsigned __int8 __value);
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_gr(int128_t const &__var, __int16 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_gr(uint128_t const &__var, unsigned __int16 __value);
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_gr(int128_t const &__var, __int32 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_gr(uint128_t const &__var, unsigned __int32 __value);
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_gr(int128_t const &__var, __int64 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_gr(uint128_t const &__var, unsigned __int64 __value);
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */

/* `var >= value' */
#ifdef __CHAR_UNSIGNED__
__ATTR_PURE __ATTR_WUNUSED bool uint128_ge(uint128_t const &__var, char __value);
#endif /* __CHAR_UNSIGNED__ */
__ATTR_PURE __ATTR_WUNUSED bool uint128_ge(uint128_t const &__var, unsigned char __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_ge(uint128_t const &__var, unsigned short __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_ge(uint128_t const &__var, unsigned int __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_ge(uint128_t const &__var, unsigned long __value);
#ifdef __COMPILER_HAVE_LONGLONG
__ATTR_PURE __ATTR_WUNUSED bool uint128_ge(uint128_t const &__var, __ULONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
__ATTR_PURE __ATTR_WUNUSED bool uint128_ge8(uint128_t const &__var, __UINT8_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_ge16(uint128_t const &__var, __UINT16_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool uint128_ge32(uint128_t const &__var, __UINT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
__ATTR_PURE __ATTR_WUNUSED bool uint128_ge64(uint128_t const &__var, __UINT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
__ATTR_PURE __ATTR_WUNUSED bool uint128_ge128(uint128_t const &__var, uint128_t const &__value);
#ifndef __CHAR_UNSIGNED__
__ATTR_PURE __ATTR_WUNUSED bool int128_ge(int128_t const &__var, char __value);
#endif /* !__CHAR_UNSIGNED__ */
__ATTR_PURE __ATTR_WUNUSED bool int128_ge(int128_t const &__var, signed char __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_ge(int128_t const &__var, short __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_ge(int128_t const &__var, int __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_ge(int128_t const &__var, long __value);
#ifdef __COMPILER_HAVE_LONGLONG
__ATTR_PURE __ATTR_WUNUSED bool int128_ge(int128_t const &__var, __LONGLONG __value);
#endif /* __COMPILER_HAVE_LONGLONG */
__ATTR_PURE __ATTR_WUNUSED bool int128_ge8(int128_t const &__var, __INT8_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_ge16(int128_t const &__var, __INT16_TYPE__ __value);
__ATTR_PURE __ATTR_WUNUSED bool int128_ge32(int128_t const &__var, __INT32_TYPE__ __value);
#ifdef __UINT64_TYPE__
__ATTR_PURE __ATTR_WUNUSED bool int128_ge64(int128_t const &__var, __INT64_TYPE__ __value);
#endif /* __UINT64_TYPE__ */
__ATTR_PURE __ATTR_WUNUSED bool int128_ge128(int128_t const &__var, int128_t const &__value);
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_ge(int128_t const &__var, __int8 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_ge(uint128_t const &__var, unsigned __int8 __value);
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_ge(int128_t const &__var, __int16 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_ge(uint128_t const &__var, unsigned __int16 __value);
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_ge(int128_t const &__var, __int32 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_ge(uint128_t const &__var, unsigned __int32 __value);
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
__ATTR_PURE __ATTR_WUNUSED void int128_ge(int128_t const &__var, __int64 __value);
__ATTR_PURE __ATTR_WUNUSED void uint128_ge(uint128_t const &__var, unsigned __int64 __value);
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */

/* Perform inplace-shift operations in `VAR'
 * NOTES:
 *  - *32: The SHIFT argument must be < 32
 *  - *64: The SHIFT argument must be < 64
 *  - *:   The SHIFT argument must be < 128 */
void uint128_shl32(uint128_t &__var, __SHIFT_TYPE__ __shift /*<32*/);
void uint128_shl64(uint128_t &__var, __SHIFT_TYPE__ __shift /*<64*/);
void uint128_shl(uint128_t &__var, __SHIFT_TYPE__ __shift /*<128*/);
void int128_shl32(int128_t &__var, __SHIFT_TYPE__ __shift /*<32*/);
void int128_shl64(int128_t &__var, __SHIFT_TYPE__ __shift /*<64*/);
void int128_shl(int128_t &__var, __SHIFT_TYPE__ __shift /*<128*/);
void uint128_shr32(uint128_t &__var, __SHIFT_TYPE__ __shift /*<32*/);
void uint128_shr64(uint128_t &__var, __SHIFT_TYPE__ __shift /*<64*/);
void uint128_shr(uint128_t &__var, __SHIFT_TYPE__ __shift /*<128*/);
void int128_shr32(int128_t &__var, __SHIFT_TYPE__ __shift /*<32*/);
void int128_shr64(int128_t &__var, __SHIFT_TYPE__ __shift /*<64*/);
void int128_shr(int128_t &__var, __SHIFT_TYPE__ __shift /*<128*/);

/* Check if a shift operation would cause data to become lost. */
__ATTR_PURE __ATTR_WUNUSED bool uint128_shl32_overflows(uint128_t const &__var, __SHIFT_TYPE__ __shift /*<32*/);
__ATTR_PURE __ATTR_WUNUSED bool int128_shl32_overflows(int128_t const &__var, __SHIFT_TYPE__ __shift /*<32*/);
__ATTR_PURE __ATTR_WUNUSED bool uint128_shl64_overflows(uint128_t const &__var, __SHIFT_TYPE__ __shift /*<64*/);
__ATTR_PURE __ATTR_WUNUSED bool int128_shl64_overflows(int128_t const &__var, __SHIFT_TYPE__ __shift /*<64*/);
__ATTR_PURE __ATTR_WUNUSED bool uint128_shl_overflows(uint128_t const &__var, __SHIFT_TYPE__ __shift /*<128*/);
__ATTR_PURE __ATTR_WUNUSED bool int128_shl_overflows(int128_t const &__var, __SHIFT_TYPE__ __shift /*<128*/);
__ATTR_PURE __ATTR_WUNUSED bool uint128_shr32_overflows(uint128_t const &__var, __SHIFT_TYPE__ __shift /*<32*/);
__ATTR_PURE __ATTR_WUNUSED bool int128_shr32_overflows(int128_t const &__var, __SHIFT_TYPE__ __shift /*<32*/);
__ATTR_PURE __ATTR_WUNUSED bool uint128_shr64_overflows(uint128_t const &__var, __SHIFT_TYPE__ __shift /*<64*/);
__ATTR_PURE __ATTR_WUNUSED bool int128_shr64_overflows(int128_t const &__var, __SHIFT_TYPE__ __shift /*<64*/);
__ATTR_PURE __ATTR_WUNUSED bool uint128_shr_overflows(uint128_t const &__var, __SHIFT_TYPE__ __shift /*<128*/);
__ATTR_PURE __ATTR_WUNUSED bool int128_shr_overflows(int128_t const &__var, __SHIFT_TYPE__ __shift /*<128*/);

/* Assign special value to the given 128-bit integer */
void int128_setzero(int128_t &__var);     /* `var = 0' */
void uint128_setzero(uint128_t &__var);   /* `var = 0' */
void int128_setone(int128_t &__var);      /* `var = 1' */
void uint128_setone(uint128_t &__var);    /* `var = 1' */
void int128_setminusone(int128_t &__var); /* `var = -1' */
void int128_setmin(int128_t &__var);      /* `var = INT128_MIN' */
void int128_setmax(int128_t &__var);      /* `var = INT128_MAX' */
void uint128_setmin(uint128_t &__var);    /* `var = UINT128_MIN (== 0)' */
void uint128_setmax(uint128_t &__var);    /* `var = UINT128_MAX' */

/* Test for special values within a 128-bit integer */
__ATTR_PURE __ATTR_WUNUSED bool int128_iszero(int128_t const &__var);     /* `var == 0' */
__ATTR_PURE __ATTR_WUNUSED bool uint128_iszero(uint128_t const &__var);   /* `var == 0' */
__ATTR_PURE __ATTR_WUNUSED bool int128_isone(int128_t const &__var);      /* `var == 1' */
__ATTR_PURE __ATTR_WUNUSED bool uint128_isone(uint128_t const &__var);    /* `var == 1' */
__ATTR_PURE __ATTR_WUNUSED bool int128_isminusone(int128_t const &__var); /* `var == -1' */
__ATTR_PURE __ATTR_WUNUSED bool int128_ismin(int128_t const &__var);      /* `var == INT128_MIN' */
__ATTR_PURE __ATTR_WUNUSED bool int128_ismax(int128_t const &__var);      /* `var == INT128_MAX' */
__ATTR_PURE __ATTR_WUNUSED bool uint128_ismin(uint128_t const &__var);    /* `var == UINT128_MIN (== 0)' */
__ATTR_PURE __ATTR_WUNUSED bool uint128_ismax(uint128_t const &__var);    /* `var == UINT128_MAX' */

/* Test is the given 128-bit integer can fit into a smaller data-word without being truncated. */
__ATTR_PURE __ATTR_WUNUSED bool uint128_is8bit(uint128_t const &__var);  /* `var <= UINT8_MAX' */
__ATTR_PURE __ATTR_WUNUSED bool uint128_is16bit(uint128_t const &__var); /* `var <= UINT16_MAX' */
__ATTR_PURE __ATTR_WUNUSED bool uint128_is32bit(uint128_t const &__var); /* `var <= UINT32_MAX' */
__ATTR_PURE __ATTR_WUNUSED bool uint128_is64bit(uint128_t const &__var); /* `var <= UINT64_MAX' */
__ATTR_PURE __ATTR_WUNUSED bool int128_is8bit(int128_t const &__var);    /* `var >= INT8_MIN && var <= INT8_MAX' */
__ATTR_PURE __ATTR_WUNUSED bool int128_is16bit(int128_t const &__var);   /* `var >= INT16_MIN && var <= INT16_MAX' */
__ATTR_PURE __ATTR_WUNUSED bool int128_is32bit(int128_t const &__var);   /* `var >= INT32_MIN && var <= INT32_MAX' */
__ATTR_PURE __ATTR_WUNUSED bool int128_is64bit(int128_t const &__var);   /* `var >= INT64_MIN && var <= INT64_MAX' */

} /* extern "C++" */
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
#define int128_pack8(var, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)  __hybrid_int128_pack8(var, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)
#define int128_pack16(var, a, b, c, d, e, f, g, h) __hybrid_int128_pack16(var, a, b, c, d, e, f, g, h)
#define int128_pack32(var, a, b, c, d)      __hybrid_int128_pack32(var, a, b, c, d)
#define uint128_pack8(var, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) __hybrid_uint128_pack8(var, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)
#define uint128_pack16(var, a, b, c, d, e, f, g, h) __hybrid_uint128_pack16(var, a, b, c, d, e, f, g, h)
#define uint128_pack32(var, a, b, c, d)     __hybrid_uint128_pack32(var, a, b, c, d)
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
#define uint128_add(var, v)                 __hybrid_uint128_add(var, v)
#define uint128_add8(var, v)                __hybrid_uint128_add8(var, v)
#define uint128_add16(var, v)               __hybrid_uint128_add16(var, v)
#define uint128_add32(var, v)               __hybrid_uint128_add32(var, v)
#define uint128_add128(var, v)              __hybrid_uint128_add128(var, v)
#define int128_add(var, v)                  __hybrid_int128_add(var, v)
#define int128_add8(var, v)                 __hybrid_int128_add8(var, v)
#define int128_add16(var, v)                __hybrid_int128_add16(var, v)
#define int128_add32(var, v)                __hybrid_int128_add32(var, v)
#define int128_add128(var, v)               __hybrid_int128_add128(var, v)
#define uint128_sub(var, v)                 __hybrid_uint128_sub(var, v)
#define uint128_sub8(var, v)                __hybrid_uint128_sub8(var, v)
#define uint128_sub16(var, v)               __hybrid_uint128_sub16(var, v)
#define uint128_sub32(var, v)               __hybrid_uint128_sub32(var, v)
#define uint128_sub128(var, v)              __hybrid_uint128_sub128(var, v)
#define int128_sub(var, v)                  __hybrid_int128_sub(var, v)
#define int128_sub8(var, v)                 __hybrid_int128_sub8(var, v)
#define int128_sub16(var, v)                __hybrid_int128_sub16(var, v)
#define int128_sub32(var, v)                __hybrid_int128_sub32(var, v)
#define int128_sub128(var, v)               __hybrid_int128_sub128(var, v)
#define uint128_mul(var, v)                 __hybrid_uint128_mul(var, v)
#define uint128_mul8(var, v)                __hybrid_uint128_mul8(var, v)
#define uint128_mul16(var, v)               __hybrid_uint128_mul16(var, v)
#define uint128_mul32(var, v)               __hybrid_uint128_mul32(var, v)
#define uint128_mul128(var, v)              __hybrid_uint128_mul128(var, v)
#define int128_mul(var, v)                  __hybrid_int128_mul(var, v)
#define int128_mul8(var, v)                 __hybrid_int128_mul8(var, v)
#define int128_mul16(var, v)                __hybrid_int128_mul16(var, v)
#define int128_mul32(var, v)                __hybrid_int128_mul32(var, v)
#define int128_mul128(var, v)               __hybrid_int128_mul128(var, v)
#define uint128_div(var, v)                 __hybrid_uint128_div(var, v)
#define uint128_div8(var, v)                __hybrid_uint128_div8(var, v)
#define uint128_div16(var, v)               __hybrid_uint128_div16(var, v)
#define uint128_div32(var, v)               __hybrid_uint128_div32(var, v)
#define uint128_div128(var, v)              __hybrid_uint128_div128(var, v)
#define int128_div(var, v)                  __hybrid_int128_div(var, v)
#define int128_div8(var, v)                 __hybrid_int128_div8(var, v)
#define int128_div16(var, v)                __hybrid_int128_div16(var, v)
#define int128_div32(var, v)                __hybrid_int128_div32(var, v)
#define int128_div128(var, v)               __hybrid_int128_div128(var, v)
#define uint128_mod(var, v)                 __hybrid_uint128_mod(var, v)
#define uint128_mod8(var, v)                __hybrid_uint128_mod8(var, v)
#define uint128_mod16(var, v)               __hybrid_uint128_mod16(var, v)
#define uint128_mod32(var, v)               __hybrid_uint128_mod32(var, v)
#define uint128_mod128(var, v)              __hybrid_uint128_mod128(var, v)
#define int128_mod(var, v)                  __hybrid_int128_mod(var, v)
#define int128_mod8(var, v)                 __hybrid_int128_mod8(var, v)
#define int128_mod16(var, v)                __hybrid_int128_mod16(var, v)
#define int128_mod32(var, v)                __hybrid_int128_mod32(var, v)
#define int128_mod128(var, v)               __hybrid_int128_mod128(var, v)
#define uint128_mod8_r(var, v, res)         __hybrid_uint128_mod8_r(var, v, res)
#define uint128_mod16_r(var, v, res)        __hybrid_uint128_mod16_r(var, v, res)
#define uint128_mod32_r(var, v, res)        __hybrid_uint128_mod32_r(var, v, res)
#define int128_mod8_r(var, v, res)          __hybrid_int128_mod8_r(var, v, res)
#define int128_mod16_r(var, v, res)         __hybrid_int128_mod16_r(var, v, res)
#define int128_mod32_r(var, v, res)         __hybrid_int128_mod32_r(var, v, res)
#define uint128_divmod(var, v, divres, modres)    __hybrid_uint128_divmod(var, v, divres, modres)
#define uint128_divmod8(var, v, divres, modres)   __hybrid_uint128_divmod8(var, v, divres, modres)
#define uint128_divmod16(var, v, divres, modres)  __hybrid_uint128_divmod16(var, v, divres, modres)
#define uint128_divmod32(var, v, divres, modres)  __hybrid_uint128_divmod32(var, v, divres, modres)
#define uint128_divmod128(var, v, divres, modres) __hybrid_uint128_divmod128(var, v, divres, modres)
#define int128_divmod(var, v, divres, modres)     __hybrid_int128_divmod(var, v, divres, modres)
#define int128_divmod8(var, v, divres, modres)    __hybrid_int128_divmod8(var, v, divres, modres)
#define int128_divmod16(var, v, divres, modres)   __hybrid_int128_divmod16(var, v, divres, modres)
#define int128_divmod32(var, v, divres, modres)   __hybrid_int128_divmod32(var, v, divres, modres)
#define int128_divmod128(var, v, divres, modres)  __hybrid_int128_divmod128(var, v, divres, modres)
#define int128_floordiv(var, v)             __hybrid_int128_floordiv(var, v)
#define int128_floordiv8(var, v)            __hybrid_int128_floordiv8(var, v)
#define int128_floordiv16(var, v)           __hybrid_int128_floordiv16(var, v)
#define int128_floordiv32(var, v)           __hybrid_int128_floordiv32(var, v)
#define int128_floordiv128(var, v)          __hybrid_int128_floordiv128(var, v)
#define int128_floormod(var, v)             __hybrid_int128_floormod(var, v)
#define int128_floormod8(var, v)            __hybrid_int128_floormod8(var, v)
#define int128_floormod16(var, v)           __hybrid_int128_floormod16(var, v)
#define int128_floormod32(var, v)           __hybrid_int128_floormod32(var, v)
#define int128_floormod128(var, v)          __hybrid_int128_floormod128(var, v)
#define int128_floormod8_r(var, v, res)     __hybrid_int128_floormod8_r(var, v, res)
#define int128_floormod16_r(var, v, res)    __hybrid_int128_floormod16_r(var, v, res)
#define int128_floormod32_r(var, v, res)    __hybrid_int128_floormod32_r(var, v, res)
#define int128_floordivmod(var, v, floordivres, modres)    __hybrid_int128_floordivmod(var, v, floordivres, modres)
#define int128_floordivmod8(var, v, floordivres, modres)   __hybrid_int128_floordivmod8(var, v, floordivres, modres)
#define int128_floordivmod16(var, v, floordivres, modres)  __hybrid_int128_floordivmod16(var, v, floordivres, modres)
#define int128_floordivmod32(var, v, floordivres, modres)  __hybrid_int128_floordivmod32(var, v, floordivres, modres)
#define int128_floordivmod128(var, v, floordivres, modres) __hybrid_int128_floordivmod128(var, v, floordivres, modres)
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
#define uint128_ne(var, v)                  __hybrid_uint128_ne(var, v)
#define uint128_ne8(var, v)                 __hybrid_uint128_ne8(var, v)
#define uint128_ne16(var, v)                __hybrid_uint128_ne16(var, v)
#define uint128_ne32(var, v)                __hybrid_uint128_ne32(var, v)
#define uint128_ne128(var, v)               __hybrid_uint128_ne128(var, v)
#define int128_ne(var, v)                   __hybrid_int128_ne(var, v)
#define int128_ne8(var, v)                  __hybrid_int128_ne8(var, v)
#define int128_ne16(var, v)                 __hybrid_int128_ne16(var, v)
#define int128_ne32(var, v)                 __hybrid_int128_ne32(var, v)
#define int128_ne128(var, v)                __hybrid_int128_ne128(var, v)
#define uint128_lo(var, v)                  __hybrid_uint128_lo(var, v)
#define uint128_lo8(var, v)                 __hybrid_uint128_lo8(var, v)
#define uint128_lo16(var, v)                __hybrid_uint128_lo16(var, v)
#define uint128_lo32(var, v)                __hybrid_uint128_lo32(var, v)
#define uint128_lo128(var, v)               __hybrid_uint128_lo128(var, v)
#define int128_lo(var, v)                   __hybrid_int128_lo(var, v)
#define int128_lo8(var, v)                  __hybrid_int128_lo8(var, v)
#define int128_lo16(var, v)                 __hybrid_int128_lo16(var, v)
#define int128_lo32(var, v)                 __hybrid_int128_lo32(var, v)
#define int128_lo128(var, v)                __hybrid_int128_lo128(var, v)
#define uint128_le(var, v)                  __hybrid_uint128_le(var, v)
#define uint128_le8(var, v)                 __hybrid_uint128_le8(var, v)
#define uint128_le16(var, v)                __hybrid_uint128_le16(var, v)
#define uint128_le32(var, v)                __hybrid_uint128_le32(var, v)
#define uint128_le128(var, v)               __hybrid_uint128_le128(var, v)
#define int128_le(var, v)                   __hybrid_int128_le(var, v)
#define int128_le8(var, v)                  __hybrid_int128_le8(var, v)
#define int128_le16(var, v)                 __hybrid_int128_le16(var, v)
#define int128_le32(var, v)                 __hybrid_int128_le32(var, v)
#define int128_le128(var, v)                __hybrid_int128_le128(var, v)
#define uint128_gr(var, v)                  __hybrid_uint128_gr(var, v)
#define uint128_gr8(var, v)                 __hybrid_uint128_gr8(var, v)
#define uint128_gr16(var, v)                __hybrid_uint128_gr16(var, v)
#define uint128_gr32(var, v)                __hybrid_uint128_gr32(var, v)
#define uint128_gr128(var, v)               __hybrid_uint128_gr128(var, v)
#define int128_gr(var, v)                   __hybrid_int128_gr(var, v)
#define int128_gr8(var, v)                  __hybrid_int128_gr8(var, v)
#define int128_gr16(var, v)                 __hybrid_int128_gr16(var, v)
#define int128_gr32(var, v)                 __hybrid_int128_gr32(var, v)
#define int128_gr128(var, v)                __hybrid_int128_gr128(var, v)
#define uint128_ge(var, v)                  __hybrid_uint128_ge(var, v)
#define uint128_ge8(var, v)                 __hybrid_uint128_ge8(var, v)
#define uint128_ge16(var, v)                __hybrid_uint128_ge16(var, v)
#define uint128_ge32(var, v)                __hybrid_uint128_ge32(var, v)
#define uint128_ge128(var, v)               __hybrid_uint128_ge128(var, v)
#define int128_ge(var, v)                   __hybrid_int128_ge(var, v)
#define int128_ge8(var, v)                  __hybrid_int128_ge8(var, v)
#define int128_ge16(var, v)                 __hybrid_int128_ge16(var, v)
#define int128_ge32(var, v)                 __hybrid_int128_ge32(var, v)
#define int128_ge128(var, v)                __hybrid_int128_ge128(var, v)
#ifdef __UINT64_TYPE__
#define int128_vec64(var)                   __hybrid_int128_vec64(var)
#define uint128_vec64(var)                  __hybrid_uint128_vec64(var)
#define int128_vec64_significand(var, i)    __hybrid_int128_vec64_significand(var, i)
#define uint128_vec64_significand(var, i)   __hybrid_uint128_vec64_significand(var, i)
#define int128_pack64(var, lo, hi)          __hybrid_int128_pack64(var, lo, hi)
#define uint128_pack64(var, lo, hi)         __hybrid_uint128_pack64(var, lo, hi)
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
#define uint128_add64(var, v)               __hybrid_uint128_add64(var, v)
#define int128_add64(var, v)                __hybrid_int128_add64(var, v)
#define uint128_sub64(var, v)               __hybrid_uint128_sub64(var, v)
#define int128_sub64(var, v)                __hybrid_int128_sub64(var, v)
#define uint128_mul64(var, v)               __hybrid_uint128_mul64(var, v)
#define int128_mul64(var, v)                __hybrid_int128_mul64(var, v)
#define uint128_div64(var, v)               __hybrid_uint128_div64(var, v)
#define int128_div64(var, v)                __hybrid_int128_div64(var, v)
#define uint128_mod64(var, v)               __hybrid_uint128_mod64(var, v)
#define int128_mod64(var, v)                __hybrid_int128_mod64(var, v)
#define uint128_mod64_r(var, v, res)        __hybrid_uint128_mod64_r(var, v, res)
#define int128_mod64_r(var, v, res)         __hybrid_int128_mod64_r(var, v, res)
#define uint128_divmod64(var, v, divres, modres) __hybrid_uint128_divmod64(var, v, divres, modres)
#define int128_divmod64(var, v, divres, modres) __hybrid_int128_divmod64(var, v, divres, modres)
#define int128_floordiv64(var, v)           __hybrid_int128_floordiv64(var, v)
#define int128_floormod64(var, v)           __hybrid_int128_floormod64(var, v)
#define int128_floormod64_r(var, v, res)    __hybrid_int128_floormod64_r(var, v, res)
#define int128_floordivmod64(var, v, divres, modres) __hybrid_int128_floordivmod64(var, v, divres, modres)
#define uint128_eq64(var, v)                __hybrid_uint128_eq64(var, v)
#define int128_eq64(var, v)                 __hybrid_int128_eq64(var, v)
#define uint128_ne64(var, v)                __hybrid_uint128_ne64(var, v)
#define int128_ne64(var, v)                 __hybrid_int128_ne64(var, v)
#define uint128_lo64(var, v)                __hybrid_uint128_lo64(var, v)
#define int128_lo64(var, v)                 __hybrid_int128_lo64(var, v)
#define uint128_le64(var, v)                __hybrid_uint128_le64(var, v)
#define int128_le64(var, v)                 __hybrid_int128_le64(var, v)
#define uint128_gr64(var, v)                __hybrid_uint128_gr64(var, v)
#define int128_gr64(var, v)                 __hybrid_int128_gr64(var, v)
#define uint128_ge64(var, v)                __hybrid_uint128_ge64(var, v)
#define int128_ge64(var, v)                 __hybrid_int128_ge64(var, v)
#endif /* __UINT64_TYPE__ */
#endif /* !__INTELLISENSE__ || !__cplusplus */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_INT128_H */
