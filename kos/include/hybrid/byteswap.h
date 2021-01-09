/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID_BYTESWAP_H
#define __GUARD_HYBRID_BYTESWAP_H 1

#include "__byteswap.h"

#define BSWAP16_C(x)  __hybrid_bswap16_c(x)
#define BSWAP32_C(x)  __hybrid_bswap32_c(x)
#ifdef __UINT64_TYPE__
#define BSWAP64_C(x)  __hybrid_bswap64_c(x)
#ifdef __UINT128_TYPE__
#define BSWAP128_C(x) __hybrid_bswap128_c(x)
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */

#define BSWAP16(x)  __hybrid_bswap16(x)
#define BSWAP32(x)  __hybrid_bswap32(x)
#ifdef __UINT64_TYPE__
#define BSWAP64(x)  __hybrid_bswap64(x)
#ifdef __UINT128_TYPE__
#define BSWAP128(x) __hybrid_bswap128(x)
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */


/* Convert between host-native and Little/Big-endian */
#define HTOBE16(x)   __hybrid_htobe16(x)
#define HTOLE16(x)   __hybrid_htole16(x)
#define BETOH16(x)   __hybrid_betoh16(x)
#define LETOH16(x)   __hybrid_letoh16(x)
#define HTOBE32(x)   __hybrid_htobe32(x)
#define HTOLE32(x)   __hybrid_htole32(x)
#define BETOH32(x)   __hybrid_betoh32(x)
#define LETOH32(x)   __hybrid_letoh32(x)
#define HTOBE16_C(x) __hybrid_htobe16_c(x)
#define HTOLE16_C(x) __hybrid_htole16_c(x)
#define BETOH16_C(x) __hybrid_betoh16_c(x)
#define LETOH16_C(x) __hybrid_letoh16_c(x)
#define HTOBE32_C(x) __hybrid_htobe32_c(x)
#define HTOLE32_C(x) __hybrid_htole32_c(x)
#define BETOH32_C(x) __hybrid_betoh32_c(x)
#define LETOH32_C(x) __hybrid_letoh32_c(x)
#ifdef __hybrid_htobe64
#define HTOBE64(x)   __hybrid_htobe64(x)
#define HTOLE64(x)   __hybrid_htole64(x)
#define BETOH64(x)   __hybrid_betoh64(x)
#define LETOH64(x)   __hybrid_letoh64(x)
#define HTOBE64_C(x) __hybrid_htobe64_c(x)
#define HTOLE64_C(x) __hybrid_htole64_c(x)
#define BETOH64_C(x) __hybrid_betoh64_c(x)
#define LETOH64_C(x) __hybrid_letoh64_c(x)
#endif /* __hybrid_htobe64 */
#ifdef __hybrid_htobe128
#define HTOBE128(x)   __hybrid_htobe128(x)
#define HTOLE128(x)   __hybrid_htole128(x)
#define BETOH128(x)   __hybrid_betoh128(x)
#define LETOH128(x)   __hybrid_letoh128(x)
#define HTOBE128_C(x) __hybrid_htobe128_c(x)
#define HTOLE128_C(x) __hybrid_htole128_c(x)
#define BETOH128_C(x) __hybrid_betoh128_c(x)
#define LETOH128_C(x) __hybrid_letoh128_c(x)
#endif /* __hybrid_htobe128 */


#ifdef __GUARD_HYBRID_UNALIGNED_H
#define UNALIGNED_GETLE(ptr)       __hybrid_unaligned_getle(ptr)
#define UNALIGNED_SETLE(ptr, v)    __hybrid_unaligned_setle(ptr, v)
#define UNALIGNED_GETBE(ptr)       __hybrid_unaligned_getbe(ptr)
#define UNALIGNED_SETBE(ptr, v)    __hybrid_unaligned_setbe(ptr, v)
#define UNALIGNED_GETLE16(ptr)     __hybrid_unaligned_getle16(ptr)
#define UNALIGNED_SETLE16(ptr, v)  __hybrid_unaligned_setle16(ptr, v)
#define UNALIGNED_GETBE16(ptr)     __hybrid_unaligned_getbe16(ptr)
#define UNALIGNED_SETBE16(ptr, v)  __hybrid_unaligned_setbe16(ptr, v)
#define UNALIGNED_GETLE32(ptr)     __hybrid_unaligned_getle32(ptr)
#define UNALIGNED_SETLE32(ptr, v)  __hybrid_unaligned_setle32(ptr, v)
#define UNALIGNED_GETBE32(ptr)     __hybrid_unaligned_getbe32(ptr)
#define UNALIGNED_SETBE32(ptr, v)  __hybrid_unaligned_setbe32(ptr, v)
#ifdef __UINT64_TYPE__
#define UNALIGNED_GETLE64(ptr)     __hybrid_unaligned_getle64(ptr)
#define UNALIGNED_SETLE64(ptr, v)  __hybrid_unaligned_setle64(ptr, v)
#define UNALIGNED_GETBE64(ptr)     __hybrid_unaligned_getbe64(ptr)
#define UNALIGNED_SETBE64(ptr, v)  __hybrid_unaligned_setbe64(ptr, v)
#ifdef __UINT128_TYPE__
#define UNALIGNED_GETLE128(ptr)    __hybrid_unaligned_getle128(ptr)
#define UNALIGNED_SETLE128(ptr, v) __hybrid_unaligned_setle128(ptr, v)
#define UNALIGNED_GETBE128(ptr)    __hybrid_unaligned_getbe128(ptr)
#define UNALIGNED_SETBE128(ptr, v) __hybrid_unaligned_setbe128(ptr, v)
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#endif /* __GUARD_HYBRID_UNALIGNED_H */

#endif /* !__GUARD_HYBRID_BYTESWAP_H */
