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
#ifndef __GUARD_HYBRID_UNALIGNED_H
#define __GUARD_HYBRID_UNALIGNED_H 1

#include <__stdinc.h>

#include "__unaligned.h"

#ifdef __cplusplus
#define UNALIGNED_GET      __hybrid_unaligned_get
#define UNALIGNED_GET_SWAP __hybrid_unaligned_get_swap
#define UNALIGNED_SET      __hybrid_unaligned_set
#define UNALIGNED_SET_SWAP __hybrid_unaligned_set_swap
#endif /* __cplusplus */
#define UNALIGNED_GET16      __hybrid_unaligned_get16
#define UNALIGNED_GET16_SWAP __hybrid_unaligned_get16_swap
#define UNALIGNED_SET16      __hybrid_unaligned_set16
#define UNALIGNED_SET16_SWAP __hybrid_unaligned_set16_swap
#define UNALIGNED_GET32      __hybrid_unaligned_get32
#define UNALIGNED_GET32_SWAP __hybrid_unaligned_get32_swap
#define UNALIGNED_SET32      __hybrid_unaligned_set32
#define UNALIGNED_SET32_SWAP __hybrid_unaligned_set32_swap
#ifdef __UINT64_TYPE__
#define UNALIGNED_GET64      __hybrid_unaligned_get64
#define UNALIGNED_GET64_SWAP __hybrid_unaligned_get64_swap
#define UNALIGNED_SET64      __hybrid_unaligned_set64
#define UNALIGNED_SET64_SWAP __hybrid_unaligned_set64_swap
#ifdef __UINT128_TYPE__
#define UNALIGNED_GET128      __hybrid_unaligned_get128
#define UNALIGNED_GET128_SWAP __hybrid_unaligned_get128_swap
#define UNALIGNED_SET128      __hybrid_unaligned_set128
#define UNALIGNED_SET128_SWAP __hybrid_unaligned_set128_swap
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */


#ifdef __GUARD_HYBRID_BYTESWAP_H
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
#endif /* __GUARD_HYBRID_BYTESWAP_H */

#endif /* !__GUARD_HYBRID_UNALIGNED_H */
