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
#ifdef __UINT64_TYPE__
#define __hybrid_int128_vec64(var)     ((__INT64_TYPE__ *)&(var))
#define __hybrid_uint128_vec64(var)    ((__UINT64_TYPE__ *)&(var))
#endif /* __UINT64_TYPE__ */

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define __hybrid_int128_vec8_significand(var, i)   __hybrid_int128_vec8(var)[i]
#define __hybrid_int128_vec16_significand(var, i)  __hybrid_int128_vec16(var)[i]
#define __hybrid_int128_vec32_significand(var, i)  __hybrid_int128_vec32(var)[i]
#define __hybrid_uint128_vec8_significand(var, i)  __hybrid_uint128_vec8(var)[i]
#define __hybrid_uint128_vec16_significand(var, i) __hybrid_uint128_vec16(var)[i]
#define __hybrid_uint128_vec32_significand(var, i) __hybrid_uint128_vec32(var)[i]
#ifdef __UINT64_TYPE__
#define __hybrid_int128_vec64_significand(var, i)  __hybrid_int128_vec64(var)[i]
#define __hybrid_uint128_vec64_significand(var, i) __hybrid_uint128_vec64(var)[i]
#endif /* __UINT64_TYPE__ */
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __hybrid_int128_vec8_significand(var, i)   __hybrid_int128_vec8(var)[15 - (i)]
#define __hybrid_int128_vec16_significand(var, i)  __hybrid_int128_vec16(var)[7 - (i)]
#define __hybrid_int128_vec32_significand(var, i)  __hybrid_int128_vec32(var)[3 - (i)]
#define __hybrid_uint128_vec8_significand(var, i)  __hybrid_uint128_vec8(var)[15 - (i)]
#define __hybrid_uint128_vec16_significand(var, i) __hybrid_uint128_vec16(var)[7 - (i)]
#define __hybrid_uint128_vec32_significand(var, i) __hybrid_uint128_vec32(var)[3 - (i)]
#ifdef __UINT64_TYPE__
#define __hybrid_int128_vec64_significand(var, i)  __hybrid_int128_vec64(var)[1 - (i)]
#define __hybrid_uint128_vec64_significand(var, i) __hybrid_uint128_vec64(var)[1 - (i)]
#endif /* __UINT64_TYPE__ */
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
#ifdef __UINT64_TYPE__
#define __hybrid_int128_get64(var)     ((__INT64_TYPE__)(var))
#define __hybrid_int128_set64(var, v)  ((var) = (__INT128_TYPE__)(__INT64_TYPE__)(v))
#define __hybrid_uint128_get64(var)    ((__UINT64_TYPE__)(var))
#define __hybrid_uint128_set64(var, v) ((var) = (__UINT128_TYPE__)(__UINT64_TYPE__)(v))
#endif /* __UINT64_TYPE__ */
#define __hybrid_int128_set(var, v)    ((var) = (__INT128_TYPE__)(v))
#define __hybrid_uint128_set(var, v)   ((var) = (__UINT128_TYPE__)(v))

#else /* __INT128_TYPE__ && __UINT128_TYPE__ */

#include "__byteorder.h"

__DECL_BEGIN

typedef union {
	__UINT8_TYPE__  __i128_u8[16];
	__UINT16_TYPE__ __i128_u16[8];
	__UINT32_TYPE__ __i128_u32[4];
	__INT8_TYPE__   __i128_s8[16];
	__INT16_TYPE__  __i128_s16[8];
	__INT32_TYPE__  __i128_s32[4];
#ifdef __UINT64_TYPE__
	__UINT64_TYPE__ __i128_64[2];
	__UINT64_TYPE__ __i128_u64[2];
	__INT64_TYPE__  __i128_s64[2];
#endif /* __UINT64_TYPE__ */
} __hybrid_int128_t, __hybrid_uint128_t;
#define __hybrid_int128_t  __hybrid_int128_t
#define __hybrid_uint128_t __hybrid_uint128_t

__DECL_END


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
#define __hybrid_int128_is64bit(var) \
	(__hybrid_int128_vec64_significand(var, 1) == (__hybrid_int128_vec64_significand(var, 0) < 0 ? -1 : 0))
#else /* __UINT64_TYPE__ */
#define __hybrid_int128_is64bit(var)                                                           \
	(__hybrid_int128_vec32_significand(var, 3) == __hybrid_int128_vec32_significand(var, 2) && \
	 __hybrid_int128_vec32_significand(var, 2) == (__hybrid_int128_vec32_significand(var, 1) < 0 ? -1 : 0))
#endif /* !__UINT64_TYPE__ */

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


/* TODO: __hybrid_(u)int128_iszero */
/* TODO: __hybrid_(u)int128_is8bit (does the value fit into (u)int8_t) */
/* TODO: __hybrid_(u)int128_is16bit (does the value fit into (u)int16_t) */
/* TODO: __hybrid_(u)int128_is32bit (does the value fit into (u)int32_t) */
/* TODO: __hybrid_(u)int128_is64bit (does the value fit into (u)int64_t) */
/* TODO: __hybrid_(u)int128_equals */
/* TODO: __hybrid_(u)int128_equals8 */
/* TODO: __hybrid_(u)int128_equals16 */
/* TODO: __hybrid_(u)int128_equals32 */
/* TODO: __hybrid_(u)int128_equals64 */

#endif /* !__INT128_TYPE__ || !__UINT128_TYPE__ */
#endif /* __CC__ */


#endif /* !__GUARD_HYBRID_INT128_H */
