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
#ifndef __GUARD_HYBRID_UNALIGNED_H
#define __GUARD_HYBRID_UNALIGNED_H 1

#include <__stdinc.h>
#include "__unaligned.h"

#define UNALIGNED_GET(ptr)              __hybrid_unaligned_get(ptr)
#define UNALIGNED_GET_SWAP(ptr)         __hybrid_unaligned_get_swap(ptr)
#define UNALIGNED_SET(ptr, v)           __hybrid_unaligned_set(ptr, v)
#define UNALIGNED_SET_SWAP(ptr, v)      __hybrid_unaligned_set_swap(ptr, v)
#define UNALIGNED_GET16(ptr)            __hybrid_unaligned_get16(ptr)
#define UNALIGNED_GET16_SWAP(ptr)       __hybrid_unaligned_get16_swap(ptr)
#define UNALIGNED_SET16(ptr, v)         __hybrid_unaligned_set16(ptr, v)
#define UNALIGNED_SET16_SWAP(ptr, v)    __hybrid_unaligned_set16_swap(ptr, v)
#define UNALIGNED_GET32(ptr)            __hybrid_unaligned_get32(ptr)
#define UNALIGNED_GET32_SWAP(ptr)       __hybrid_unaligned_get32_swap(ptr)
#define UNALIGNED_SET32(ptr, v)         __hybrid_unaligned_set32(ptr, v)
#define UNALIGNED_SET32_SWAP(ptr, v)    __hybrid_unaligned_set32_swap(ptr, v)
#ifdef __UINT64_TYPE__
#define UNALIGNED_GET64(ptr)            __hybrid_unaligned_get64(ptr)
#define UNALIGNED_GET64_SWAP(ptr)       __hybrid_unaligned_get64_swap(ptr)
#define UNALIGNED_SET64(ptr, v)         __hybrid_unaligned_set64(ptr, v)
#define UNALIGNED_SET64_SWAP(ptr, v)    __hybrid_unaligned_set64_swap(ptr, v)
#ifdef __UINT128_TYPE__
#define UNALIGNED_GET128(ptr)           __hybrid_unaligned_get128(ptr)
#define UNALIGNED_GET128_SWAP(ptr)      __hybrid_unaligned_get128_swap(ptr)
#define UNALIGNED_SET128(ptr, v)        __hybrid_unaligned_set128(ptr, v)
#define UNALIGNED_SET128_SWAP(ptr, v)   __hybrid_unaligned_set128_swap(ptr, v)
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */


#ifdef __GUARD_HYBRID_BYTESWAP_H
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
#endif /* __GUARD_HYBRID_BYTESWAP_H */

#endif /* !__GUARD_HYBRID_UNALIGNED_H */
