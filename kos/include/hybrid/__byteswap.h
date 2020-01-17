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
#ifndef __GUARD_HYBRID___BYTESWAP_H
#define __GUARD_HYBRID___BYTESWAP_H 1

#include "../__stdinc.h"
#include "typecore.h"
#include "__byteorder.h"

__DECL_BEGIN


#define __hybrid_bswap16_c(x)  ((((x)&0xffu) << 8)|(((x) >> 8)&0xffu))
#define __hybrid_bswap32_c(x)  ((__hybrid_bswap16_c(x) << 16)|__hybrid_bswap16_c((x) >> 16))
#ifdef __UINT64_TYPE__
#define __hybrid_bswap64_c(x)  ((__hybrid_bswap32_c(x) << 32)|__hybrid_bswap32_c((x) >> 32))
#ifdef __UINT128_TYPE__
#define __hybrid_bswap128_c(x) ((__hybrid_bswap64_c(x) << 64)|__hybrid_bswap64_c((x) >> 64))
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */


#ifdef _MSC_VER
extern unsigned short (_byteswap_ushort)(unsigned short x);
extern unsigned long (_byteswap_ulong)(unsigned long x);
extern unsigned __int64 (_byteswap_uint64)(unsigned __int64 x);
#pragma intrinsic(_byteswap_ushort)
#pragma intrinsic(_byteswap_ulong)
#pragma intrinsic(_byteswap_uint64)
#define __impl_hybrid_bswap16(x)   _byteswap_ushort(x)
#define __impl_hybrid_bswap32(x)   _byteswap_ulong(x)
#define __impl_hybrid_bswap64(x)   _byteswap_uint64(x)
#else /* _MSC_VER */
#if __has_builtin(__builtin_bswap16)
#define __impl_hybrid_bswap16(x)  __builtin_bswap16(x)
#else /* __GNUC__ || __has_builtin(__builtin_bswap16) */
__LOCAL __ATTR_CONST __UINT16_TYPE__
__NOTHROW(__impl_hybrid_bswap16)(__UINT16_TYPE__ __x) {
	return __hybrid_bswap16_c(__x);
}
#endif /* !__GNUC__ && !__has_builtin(__builtin_bswap16) */
#if __has_builtin(__builtin_bswap32)
#define __impl_hybrid_bswap32(x)  __builtin_bswap32(x)
#else /* __GNUC__ || __has_builtin(__builtin_bswap32) */
__LOCAL __ATTR_CONST __UINT32_TYPE__
__NOTHROW(__impl_hybrid_bswap32)(__UINT32_TYPE__ __x) {
	return ((__UINT32_TYPE__)__impl_hybrid_bswap16((__UINT16_TYPE__)__x) << 16) |
	        (__UINT32_TYPE__)__impl_hybrid_bswap16((__UINT16_TYPE__)((__x) >> 16));
}
#endif /* !__GNUC__ && !__has_builtin(__builtin_bswap32) */
#ifdef __UINT64_TYPE__
#if __has_builtin(__builtin_bswap64)
#define __impl_hybrid_bswap64(x)  __builtin_bswap64(x)
#else /* __GNUC__ || __has_builtin(__builtin_bswap64) */
__LOCAL __ATTR_CONST __UINT64_TYPE__
__NOTHROW(__impl_hybrid_bswap64)(__UINT64_TYPE__ __x) {
	return ((__UINT64_TYPE__)__impl_hybrid_bswap32((__UINT32_TYPE__)__x) << 32) |
	        (__UINT64_TYPE__)__impl_hybrid_bswap32((__UINT32_TYPE__)((__x) >> 32));
}
#endif /* !__GNUC__ && !__has_builtin(__builtin_bswap64) */
#endif /* __UINT64_TYPE__ */
#endif /* !_MSC_VER */

#ifdef __UINT128_TYPE__
#if __has_builtin(__builtin_bswap128)
#define __impl_hybrid_bswap128(x)  __builtin_bswap128(x)
#else /* __GNUC__ || __has_builtin(__builtin_bswap128) */
__LOCAL __ATTR_CONST __UINT128_TYPE__
__NOTHROW(__impl_hybrid_bswap128)(__UINT128_TYPE__ __x) {
	return ((__UINT128_TYPE__)__impl_hybrid_bswap64((__UINT64_TYPE__)__x) << 64) |
	        (__UINT128_TYPE__)__impl_hybrid_bswap64((__UINT64_TYPE__)((__x) >> 64));
}
#endif /* !__GNUC__ && !__has_builtin(__builtin_bswap128) */
#endif /* __UINT128_TYPE__ */

#ifndef __CC__
#define __hybrid_bswap16(x)  __hybrid_bswap16_c(x)
#define __hybrid_bswap32(x)  __hybrid_bswap32_c(x)
#ifdef __UINT64_TYPE__
#define __hybrid_bswap64(x)  __hybrid_bswap64_c(x)
#ifdef __UINT128_TYPE__
#define __hybrid_bswap128(x) __hybrid_bswap128_c(x)
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#elif !defined(__NO_builtin_choose_expr) && !defined(__NO_builtin_constant_p)
#define __hybrid_bswap16(x)  __builtin_choose_expr(__builtin_constant_p(x), __hybrid_bswap16_c(x), __impl_hybrid_bswap16(x))
#define __hybrid_bswap32(x)  __builtin_choose_expr(__builtin_constant_p(x), __hybrid_bswap32_c(x), __impl_hybrid_bswap32(x))
#ifdef __UINT64_TYPE__
#define __hybrid_bswap64(x)  __builtin_choose_expr(__builtin_constant_p(x), __hybrid_bswap64_c(x), __impl_hybrid_bswap64(x))
#ifdef __UINT128_TYPE__
#define __hybrid_bswap128(x) __builtin_choose_expr(__builtin_constant_p(x), __hybrid_bswap128_c(x), __impl_hybrid_bswap128(x))
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#else /* Without constant optimizations... */
#define __hybrid_bswap16(x)  __impl_hybrid_bswap16(x)
#define __hybrid_bswap32(x)  __impl_hybrid_bswap32(x)
#ifdef __UINT64_TYPE__
#define __hybrid_bswap64(x)  __impl_hybrid_bswap64(x)
#ifdef __UINT128_TYPE__
#define __hybrid_bswap128(x) __impl_hybrid_bswap128(x)
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#endif /* ... */


#ifdef ____INTELLISENSE_ENDIAN
#define __hybrid_leswap16         __intern::__intellisense_leswap16
#define __hybrid_leswap32         __intern::__intellisense_leswap32
#define __hybrid_beswap16         __intern::__intellisense_beswap16
#define __hybrid_beswap32         __intern::__intellisense_beswap32
#ifdef __UINT64_TYPE__
#define __hybrid_leswap64         __intern::__intellisense_leswap64
#define __hybrid_beswap64         __intern::__intellisense_beswap64
#ifdef __UINT128_TYPE__
#define __hybrid_leswap128        __intern::__intellisense_leswap128
#define __hybrid_beswap128        __intern::__intellisense_beswap128
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define __hybrid_leswap16_c(x)  ((__UINT16_TYPE__)(x))
#define __hybrid_leswap32_c(x)  ((__UINT32_TYPE__)(x))
#define __hybrid_beswap16_c(x)    __hybrid_bswap16_c(x)
#define __hybrid_beswap32_c(x)    __hybrid_bswap32_c(x)
#ifdef __UINT64_TYPE__
#define __hybrid_leswap64_c(x)  ((__UINT64_TYPE__)(x))
#define __hybrid_beswap64_c(x)    __hybrid_bswap64_c(x)
#ifdef __UINT128_TYPE__
#define __hybrid_leswap128_c(x) ((__UINT128_TYPE__)(x))
#define __hybrid_beswap128_c(x)   __hybrid_bswap128_c(x)
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __hybrid_leswap16_c(x)    __hybrid_bswap16_c(x)
#define __hybrid_leswap32_c(x)    __hybrid_bswap32_c(x)
#define __hybrid_beswap16_c(x)  ((__UINT16_TYPE__)(x))
#define __hybrid_beswap32_c(x)  ((__UINT32_TYPE__)(x))
#ifdef __UINT64_TYPE__
#define __hybrid_leswap64_c(x)    __hybrid_bswap64_c(x)
#define __hybrid_beswap64_c(x)  ((__UINT64_TYPE__)(x))
#ifdef __UINT128_TYPE__
#define __hybrid_leswap128_c(x)   __hybrid_bswap128_c(x)
#define __hybrid_beswap128_c(x) ((__UINT128_TYPE__)(x))
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#endif
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define __hybrid_leswap16(x)    ((__UINT16_TYPE__)(x))
#define __hybrid_leswap16_c(x)  ((__UINT16_TYPE__)(x))
#define __hybrid_leswap32(x)    ((__UINT32_TYPE__)(x))
#define __hybrid_leswap32_c(x)  ((__UINT32_TYPE__)(x))
#define __hybrid_beswap16(x)      __hybrid_bswap16(x)
#define __hybrid_beswap16_c(x)    __hybrid_bswap16_c(x)
#define __hybrid_beswap32(x)      __hybrid_bswap32(x)
#define __hybrid_beswap32_c(x)    __hybrid_bswap32_c(x)
#ifdef __UINT64_TYPE__
#define __hybrid_leswap64(x)    ((__UINT64_TYPE__)(x))
#define __hybrid_leswap64_c(x)  ((__UINT64_TYPE__)(x))
#define __hybrid_beswap64(x)      __hybrid_bswap64(x)
#define __hybrid_beswap64_c(x)    __hybrid_bswap64_c(x)
#ifdef __UINT128_TYPE__
#define __hybrid_leswap128(x)   ((__UINT128_TYPE__)(x))
#define __hybrid_leswap128_c(x) ((__UINT128_TYPE__)(x))
#define __hybrid_beswap128(x)     __hybrid_bswap128(x)
#define __hybrid_beswap128_c(x)   __hybrid_bswap128_c(x)
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __hybrid_leswap16(x)      __hybrid_bswap16(x)
#define __hybrid_leswap16_c(x)    __hybrid_bswap16_c(x)
#define __hybrid_leswap32(x)      __hybrid_bswap32(x)
#define __hybrid_leswap32_c(x)    __hybrid_bswap32_c(x)
#define __hybrid_beswap16(x)    ((__UINT16_TYPE__)(x))
#define __hybrid_beswap16_c(x)  ((__UINT16_TYPE__)(x))
#define __hybrid_beswap32(x)    ((__UINT32_TYPE__)(x))
#define __hybrid_beswap32_c(x)  ((__UINT32_TYPE__)(x))
#ifdef __UINT64_TYPE__
#define __hybrid_leswap64(x)      __hybrid_bswap64(x)
#define __hybrid_leswap64_c(x)    __hybrid_bswap64_c(x)
#define __hybrid_beswap64(x)    ((__UINT64_TYPE__)(x))
#define __hybrid_beswap64_c(x)  ((__UINT64_TYPE__)(x))
#ifdef __UINT128_TYPE__
#define __hybrid_leswap128(x)     __hybrid_bswap128(x)
#define __hybrid_leswap128_c(x)   __hybrid_bswap128_c(x)
#define __hybrid_beswap128(x)   ((__UINT128_TYPE__)(x))
#define __hybrid_beswap128_c(x) ((__UINT128_TYPE__)(x))
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#endif


__DECL_END

#endif /* !__GUARD_HYBRID___BYTESWAP_H */
