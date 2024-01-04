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
#ifndef __GUARD_HYBRID___BYTESWAP_H
#define __GUARD_HYBRID___BYTESWAP_H 1

#include "../__stdinc.h"
#include "byteorder.h"
#include "typecore.h"

#define __hybrid_bswap16_c(x) ((((x) & 0xff) << 8) | (((x) >> 8) & 0xff))
#define __hybrid_bswap32_c(x) ((__hybrid_bswap16_c(x) << 16) | __hybrid_bswap16_c((x) >> 16))
#ifdef __UINT64_TYPE__
#define __hybrid_bswap64_c(x) ((__hybrid_bswap32_c(x) << 32) | __hybrid_bswap32_c((x) >> 32))
#ifdef __UINT128_TYPE__
#define __hybrid_bswap128_c(x) ((__hybrid_bswap64_c(x) << 64) | __hybrid_bswap64_c((x) >> 64))
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */

#ifdef __CC__
__DECL_BEGIN
#ifdef _MSC_VER
extern unsigned short (_byteswap_ushort)(unsigned short __x);
extern unsigned long (_byteswap_ulong)(unsigned long __x);
extern unsigned __int64 (_byteswap_uint64)(unsigned __int64 __x);
#pragma intrinsic(_byteswap_ushort)
#pragma intrinsic(_byteswap_ulong)
#pragma intrinsic(_byteswap_uint64)
#define __impl_hybrid_bswap16 _byteswap_ushort
#define __impl_hybrid_bswap32 _byteswap_ulong
#define __impl_hybrid_bswap64 _byteswap_uint64
#else /* _MSC_VER */
#if __has_builtin(__builtin_bswap16)
#define __impl_hybrid_bswap16 __builtin_bswap16
#else /* __GNUC__ || __has_builtin(__builtin_bswap16) */
__LOCAL __ATTR_CONST __ATTR_ARTIFICIAL __UINT16_TYPE__
__NOTHROW(__impl_hybrid_bswap16)(__UINT16_TYPE__ __x) {
	return (__UINT16_TYPE__)__hybrid_bswap16_c(__x);
}
#endif /* !__GNUC__ && !__has_builtin(__builtin_bswap16) */
#if __has_builtin(__builtin_bswap32)
#define __impl_hybrid_bswap32 __builtin_bswap32
#else /* __GNUC__ || __has_builtin(__builtin_bswap32) */
__LOCAL __ATTR_CONST __ATTR_ARTIFICIAL __UINT32_TYPE__
__NOTHROW(__impl_hybrid_bswap32)(__UINT32_TYPE__ __x) {
	return ((__UINT32_TYPE__)__impl_hybrid_bswap16((__UINT16_TYPE__)__x) << 16) |
	       (__UINT32_TYPE__)__impl_hybrid_bswap16((__UINT16_TYPE__)(__x >> 16));
}
#endif /* !__GNUC__ && !__has_builtin(__builtin_bswap32) */
#ifdef __UINT64_TYPE__
#if __has_builtin(__builtin_bswap64)
#define __impl_hybrid_bswap64 __builtin_bswap64
#else /* __GNUC__ || __has_builtin(__builtin_bswap64) */
__LOCAL __ATTR_CONST __ATTR_ARTIFICIAL __UINT64_TYPE__
__NOTHROW(__impl_hybrid_bswap64)(__UINT64_TYPE__ __x) {
	return ((__UINT64_TYPE__)__impl_hybrid_bswap32((__UINT32_TYPE__)__x) << 32) |
	       (__UINT64_TYPE__)__impl_hybrid_bswap32((__UINT32_TYPE__)(__x >> 32));
}
#endif /* !__GNUC__ && !__has_builtin(__builtin_bswap64) */
#endif /* __UINT64_TYPE__ */
#endif /* !_MSC_VER */

#ifdef __UINT128_TYPE__
#if __has_builtin(__builtin_bswap128)
#define __impl_hybrid_bswap128 __builtin_bswap128
#else /* __GNUC__ || __has_builtin(__builtin_bswap128) */
__LOCAL __ATTR_CONST __ATTR_ARTIFICIAL __UINT128_TYPE__
__NOTHROW(__impl_hybrid_bswap128)(__UINT128_TYPE__ __x) {
	return ((__UINT128_TYPE__)__impl_hybrid_bswap64((__UINT64_TYPE__)__x) << 64) |
	       (__UINT128_TYPE__)__impl_hybrid_bswap64((__UINT64_TYPE__)(__x >> 64));
}
#endif /* !__GNUC__ && !__has_builtin(__builtin_bswap128) */
#endif /* __UINT128_TYPE__ */
__DECL_END
#endif /* __CC__ */

#ifndef __CC__
#define __hybrid_bswap16 __hybrid_bswap16_c
#define __hybrid_bswap32 __hybrid_bswap32_c
#ifdef __UINT64_TYPE__
#define __hybrid_bswap64 __hybrid_bswap64_c
#ifdef __UINT128_TYPE__
#define __hybrid_bswap128 __hybrid_bswap128_c
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#elif !defined(__NO_builtin_choose_expr) && !defined(__NO_builtin_constant_p) && !defined(__CHECKER__)
#define __hybrid_bswap16(x) __builtin_choose_expr(__builtin_constant_p(x), __hybrid_bswap16_c(x), __impl_hybrid_bswap16(x))
#define __hybrid_bswap32(x) __builtin_choose_expr(__builtin_constant_p(x), __hybrid_bswap32_c(x), __impl_hybrid_bswap32(x))
#ifdef __UINT64_TYPE__
#define __hybrid_bswap64(x) __builtin_choose_expr(__builtin_constant_p(x), __hybrid_bswap64_c(x), __impl_hybrid_bswap64(x))
#ifdef __UINT128_TYPE__
#define __hybrid_bswap128(x) __builtin_choose_expr(__builtin_constant_p(x), __hybrid_bswap128_c(x), __impl_hybrid_bswap128(x))
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#else /* Without constant optimizations... */
#define __hybrid_bswap16 __impl_hybrid_bswap16
#define __hybrid_bswap32 __impl_hybrid_bswap32
#ifdef __UINT64_TYPE__
#define __hybrid_bswap64 __impl_hybrid_bswap64
#ifdef __UINT128_TYPE__
#define __hybrid_bswap128 __impl_hybrid_bswap128
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#endif /* ... */


#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ || \
     __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define __HYBRID_HTOLE_IS_LETOH 1 /* __hybrid_htoleNN is binary compatible with __hybrid_letohNN */
#define __HYBRID_HTOBE_IS_BETOH 1 /* __hybrid_htobeNN is binary compatible with __hybrid_betohNN */
#endif /* ... */


/* LE/BE Converter bindings */
#ifdef __INTELLISENSE__
#ifndef ____INTELLISENSE_STDINC_COMMON_H
#include "../compiler/intellisense-common.h"
#endif /* !____INTELLISENSE_STDINC_COMMON_H */
#define __hybrid_htole16 __intern::__intellisense_htole16
#define __hybrid_htobe16 __intern::__intellisense_htobe16
#define __hybrid_letoh16 __intern::__intellisense_letoh16
#define __hybrid_betoh16 __intern::__intellisense_betoh16
#define __hybrid_htole32 __intern::__intellisense_htole32
#define __hybrid_htobe32 __intern::__intellisense_htobe32
#define __hybrid_letoh32 __intern::__intellisense_letoh32
#define __hybrid_betoh32 __intern::__intellisense_betoh32
#ifdef __UINT64_TYPE__
#define __hybrid_htole64 __intern::__intellisense_htole64
#define __hybrid_htobe64 __intern::__intellisense_htobe64
#define __hybrid_letoh64 __intern::__intellisense_letoh64
#define __hybrid_betoh64 __intern::__intellisense_betoh64
#ifdef __UINT128_TYPE__
#define __hybrid_htole128 __intern::__intellisense_htole128
#define __hybrid_htobe128 __intern::__intellisense_htobe128
#define __hybrid_letoh128 __intern::__intellisense_letoh128
#define __hybrid_betoh128 __intern::__intellisense_betoh128
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __hybrid_htole16 __hybrid_bswap16
#define __hybrid_htobe16 /* nothing */
#define __hybrid_letoh16 __hybrid_bswap16
#define __hybrid_betoh16 /* nothing */
#define __hybrid_htole32 __hybrid_bswap32
#define __hybrid_htobe32 /* nothing */
#define __hybrid_letoh32 __hybrid_bswap32
#define __hybrid_betoh32 /* nothing */
#ifdef __UINT64_TYPE__
#define __hybrid_htole64 __hybrid_bswap64
#define __hybrid_htobe64 /* nothing */
#define __hybrid_letoh64 __hybrid_bswap64
#define __hybrid_betoh64 /* nothing */
#ifdef __UINT128_TYPE__
#define __hybrid_htole128 __hybrid_bswap128
#define __hybrid_htobe128 /* nothing */
#define __hybrid_letoh128 __hybrid_bswap128
#define __hybrid_betoh128 /* nothing */
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define __hybrid_htole16 /* nothing */
#define __hybrid_htobe16 __hybrid_bswap16
#define __hybrid_letoh16 /* nothing */
#define __hybrid_betoh16 __hybrid_bswap16
#define __hybrid_htole32 /* nothing */
#define __hybrid_htobe32 __hybrid_bswap32
#define __hybrid_letoh32 /* nothing */
#define __hybrid_betoh32 __hybrid_bswap32
#ifdef __UINT64_TYPE__
#define __hybrid_htole64 /* nothing */
#define __hybrid_htobe64 __hybrid_bswap64
#define __hybrid_letoh64 /* nothing */
#define __hybrid_betoh64 __hybrid_bswap64
#ifdef __UINT128_TYPE__
#define __hybrid_htole128 /* nothing */
#define __hybrid_htobe128 __hybrid_bswap128
#define __hybrid_letoh128 /* nothing */
#define __hybrid_betoh128 __hybrid_bswap128
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#else /* __BYTE_ORDER__ == ... */
#error "Unsupported endian"
#endif /* __BYTE_ORDER__ != ... */

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __hybrid_htole16_c __hybrid_bswap16_c
#define __hybrid_htobe16_c /* nothing */
#define __hybrid_letoh16_c __hybrid_bswap16_c
#define __hybrid_betoh16_c /* nothing */
#define __hybrid_htole32_c __hybrid_bswap32_c
#define __hybrid_htobe32_c /* nothing */
#define __hybrid_letoh32_c __hybrid_bswap32_c
#define __hybrid_betoh32_c /* nothing */
#ifdef __UINT64_TYPE__
#define __hybrid_htole64_c __hybrid_bswap64_c
#define __hybrid_htobe64_c /* nothing */
#define __hybrid_letoh64_c __hybrid_bswap64_c
#define __hybrid_betoh64_c /* nothing */
#ifdef __UINT128_TYPE__
#define __hybrid_htole128_c __hybrid_bswap128_c
#define __hybrid_htobe128_c /* nothing */
#define __hybrid_letoh128_c __hybrid_bswap128_c
#define __hybrid_betoh128_c /* nothing */
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define __hybrid_htole16_c /* nothing */
#define __hybrid_htobe16_c __hybrid_bswap16_c
#define __hybrid_letoh16_c /* nothing */
#define __hybrid_betoh16_c __hybrid_bswap16_c
#define __hybrid_htole32_c /* nothing */
#define __hybrid_htobe32_c __hybrid_bswap32_c
#define __hybrid_letoh32_c /* nothing */
#define __hybrid_betoh32_c __hybrid_bswap32_c
#ifdef __UINT64_TYPE__
#define __hybrid_htole64_c /* nothing */
#define __hybrid_htobe64_c __hybrid_bswap64_c
#define __hybrid_letoh64_c /* nothing */
#define __hybrid_betoh64_c __hybrid_bswap64_c
#ifdef __UINT128_TYPE__
#define __hybrid_htole128_c /* nothing */
#define __hybrid_htobe128_c __hybrid_bswap128_c
#define __hybrid_letoh128_c /* nothing */
#define __hybrid_betoh128_c __hybrid_bswap128_c
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#else /* __BYTE_ORDER__ == ... */
#error "Unsupported endian"
#endif /* __BYTE_ORDER__ != ... */


#endif /* !__GUARD_HYBRID___BYTESWAP_H */
