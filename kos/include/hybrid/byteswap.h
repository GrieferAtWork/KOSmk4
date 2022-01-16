/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID_BYTESWAP_H
#define __GUARD_HYBRID_BYTESWAP_H 1

#include "__byteswap.h"

#define BSWAP16_C __hybrid_bswap16_c
#define BSWAP32_C __hybrid_bswap32_c
#ifdef __UINT64_TYPE__
#define BSWAP64_C __hybrid_bswap64_c
#ifdef __UINT128_TYPE__
#define BSWAP128_C __hybrid_bswap128_c
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */

#define BSWAP16 __hybrid_bswap16
#define BSWAP32 __hybrid_bswap32
#ifdef __UINT64_TYPE__
#define BSWAP64 __hybrid_bswap64
#ifdef __UINT128_TYPE__
#define BSWAP128 __hybrid_bswap128
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */


/* Convert between host-native and Little/Big-endian */
#define HTOBE16   __hybrid_htobe16
#define HTOLE16   __hybrid_htole16
#define BETOH16   __hybrid_betoh16
#define LETOH16   __hybrid_letoh16
#define HTOBE32   __hybrid_htobe32
#define HTOLE32   __hybrid_htole32
#define BETOH32   __hybrid_betoh32
#define LETOH32   __hybrid_letoh32
#define HTOBE16_C __hybrid_htobe16_c
#define HTOLE16_C __hybrid_htole16_c
#define BETOH16_C __hybrid_betoh16_c
#define LETOH16_C __hybrid_letoh16_c
#define HTOBE32_C __hybrid_htobe32_c
#define HTOLE32_C __hybrid_htole32_c
#define BETOH32_C __hybrid_betoh32_c
#define LETOH32_C __hybrid_letoh32_c
#ifdef __hybrid_htobe64
#define HTOBE64   __hybrid_htobe64
#define HTOLE64   __hybrid_htole64
#define BETOH64   __hybrid_betoh64
#define LETOH64   __hybrid_letoh64
#define HTOBE64_C __hybrid_htobe64_c
#define HTOLE64_C __hybrid_htole64_c
#define BETOH64_C __hybrid_betoh64_c
#define LETOH64_C __hybrid_letoh64_c
#endif /* __hybrid_htobe64 */
#ifdef __hybrid_htobe128
#define HTOBE128   __hybrid_htobe128
#define HTOLE128   __hybrid_htole128
#define BETOH128   __hybrid_betoh128
#define LETOH128   __hybrid_letoh128
#define HTOBE128_C __hybrid_htobe128_c
#define HTOLE128_C __hybrid_htole128_c
#define BETOH128_C __hybrid_betoh128_c
#define LETOH128_C __hybrid_letoh128_c
#endif /* __hybrid_htobe128 */


#ifdef __GUARD_HYBRID_UNALIGNED_H
#define UNALIGNED_GETLE   __hybrid_unaligned_getle
#define UNALIGNED_SETLE   __hybrid_unaligned_setle
#define UNALIGNED_GETBE   __hybrid_unaligned_getbe
#define UNALIGNED_SETBE   __hybrid_unaligned_setbe
#define UNALIGNED_GETLE16 __hybrid_unaligned_getle16
#define UNALIGNED_SETLE16 __hybrid_unaligned_setle16
#define UNALIGNED_GETBE16 __hybrid_unaligned_getbe16
#define UNALIGNED_SETBE16 __hybrid_unaligned_setbe16
#define UNALIGNED_GETLE32 __hybrid_unaligned_getle32
#define UNALIGNED_SETLE32 __hybrid_unaligned_setle32
#define UNALIGNED_GETBE32 __hybrid_unaligned_getbe32
#define UNALIGNED_SETBE32 __hybrid_unaligned_setbe32
#ifdef __UINT64_TYPE__
#define UNALIGNED_GETLE64 __hybrid_unaligned_getle64
#define UNALIGNED_SETLE64 __hybrid_unaligned_setle64
#define UNALIGNED_GETBE64 __hybrid_unaligned_getbe64
#define UNALIGNED_SETBE64 __hybrid_unaligned_setbe64
#ifdef __UINT128_TYPE__
#define UNALIGNED_GETLE128 __hybrid_unaligned_getle128
#define UNALIGNED_SETLE128 __hybrid_unaligned_setle128
#define UNALIGNED_GETBE128 __hybrid_unaligned_getbe128
#define UNALIGNED_SETBE128 __hybrid_unaligned_setbe128
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#endif /* __GUARD_HYBRID_UNALIGNED_H */

#endif /* !__GUARD_HYBRID_BYTESWAP_H */
