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
#ifndef __GUARD_HYBRID___UNALIGNED_H
#define __GUARD_HYBRID___UNALIGNED_H 1

#include "../__stdinc.h"
#include "__byteswap.h"
#include "__debug-alignment.h"
#include "host.h"
#include "typecore.h"
#include "byteorder.h"


/* ======================== API ========================
 * >> T       __hybrid_unaligned_get(T const *p);       // Only for unsigned types
 * >> T       __hybrid_unaligned_get_swap(T const *p);  // Only for unsigned types
 * >> T       __hybrid_unaligned_getle(T const *p);     // Only for unsigned types
 * >> T       __hybrid_unaligned_getbe(T const *p);     // Only for unsigned types
 * >> void    __hybrid_unaligned_set(T *p, T v);
 * >> void    __hybrid_unaligned_set_swap(T *p, T v);
 * >> void    __hybrid_unaligned_setle(T *p, T v);
 * >> void    __hybrid_unaligned_setbe(T *p, T v);
 * >> uintN_t __hybrid_unaligned_getN(void const *p);
 * >> uintN_t __hybrid_unaligned_getN_swap(void const *p);
 * >> uintN_t __hybrid_unaligned_getleN(void const *p);
 * >> uintN_t __hybrid_unaligned_getbeN(void const *p);
 * >> void    __hybrid_unaligned_setN(void *p, uintN_t v);
 * >> void    __hybrid_unaligned_setN_swap(void *p, uintN_t v);
 * >> void    __hybrid_unaligned_setleN(void *p, uintN_t v);
 * >> void    __hybrid_unaligned_setbeN(void *p, uintN_t v);
 */
#ifdef __CC__
__DECL_BEGIN
#ifdef __INTELLISENSE__
#ifdef __cplusplus
extern "C++" {
#define __hybrid_unaligned_get __hybrid_unaligned_get
#define __hybrid_unaligned_set __hybrid_unaligned_set
extern __UINT8_TYPE__ (__hybrid_unaligned_get)(__INT8_TYPE__ const *__restrict __p);
extern __UINT8_TYPE__ (__hybrid_unaligned_get)(__UINT8_TYPE__ const *__restrict __p);
extern __UINT16_TYPE__ (__hybrid_unaligned_get)(__INT16_TYPE__ const *__restrict __p);
extern __UINT16_TYPE__ (__hybrid_unaligned_get)(__UINT16_TYPE__ const *__restrict __p);
extern __UINT32_TYPE__ (__hybrid_unaligned_get)(__INT32_TYPE__ const *__restrict __p);
extern __UINT32_TYPE__ (__hybrid_unaligned_get)(__UINT32_TYPE__ const *__restrict __p);
extern void (__hybrid_unaligned_set)(__INT8_TYPE__ *__restrict __p, __UINT8_TYPE__ __val);
extern void (__hybrid_unaligned_set)(__UINT8_TYPE__ *__restrict __p, __UINT8_TYPE__ __val);
extern void (__hybrid_unaligned_set)(__INT16_TYPE__ *__restrict __p, __UINT16_TYPE__ __val);
extern void (__hybrid_unaligned_set)(__UINT16_TYPE__ *__restrict __p, __UINT16_TYPE__ __val);
extern void (__hybrid_unaligned_set)(__INT32_TYPE__ *__restrict __p, __UINT32_TYPE__ __val);
extern void (__hybrid_unaligned_set)(__UINT32_TYPE__ *__restrict __p, __UINT32_TYPE__ __val);
#ifdef __UFIFTHINT_TYPE__
extern __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get)(__FIFTHINT_TYPE__ const *__restrict __p);
extern __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get)(__UFIFTHINT_TYPE__ const *__restrict __p);
extern void (__hybrid_unaligned_set)(__FIFTHINT_TYPE__ *__restrict __p, __UFIFTHINT_ALIAS_TYPE__ __val);
extern void (__hybrid_unaligned_set)(__UFIFTHINT_TYPE__ *__restrict __p, __UFIFTHINT_ALIAS_TYPE__ __val);
#endif /* __UFIFTHINT_TYPE__ */
#ifdef __UINT64_TYPE__
extern __UINT64_TYPE__ (__hybrid_unaligned_get)(__INT64_TYPE__ const *__restrict __p);
extern __UINT64_TYPE__ (__hybrid_unaligned_get)(__UINT64_TYPE__ const *__restrict __p);
extern void (__hybrid_unaligned_set)(__INT64_TYPE__ *__restrict __p, __UINT64_TYPE__ __val);
extern void (__hybrid_unaligned_set)(__UINT64_TYPE__ *__restrict __p, __UINT64_TYPE__ __val);
#ifdef __UINT128_TYPE__
extern __UINT128_TYPE__ (__hybrid_unaligned_get)(__INT128_TYPE__ const *__restrict __p);
extern __UINT128_TYPE__ (__hybrid_unaligned_get)(__UINT128_TYPE__ const *__restrict __p);
extern void (__hybrid_unaligned_set)(__INT128_TYPE__ *__restrict __p, __UINT128_TYPE__ __val);
extern void (__hybrid_unaligned_set)(__UINT128_TYPE__ *__restrict __p, __UINT128_TYPE__ __val);
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
} /* extern "C++" */
#endif /* __cplusplus */
#define __hybrid_unaligned_get16 __hybrid_unaligned_get16
#define __hybrid_unaligned_set16 __hybrid_unaligned_set16
#define __hybrid_unaligned_get32 __hybrid_unaligned_get32
#define __hybrid_unaligned_set32 __hybrid_unaligned_set32
extern __UINT16_TYPE__ (__hybrid_unaligned_get16)(void const *__restrict __p);
extern __UINT32_TYPE__ (__hybrid_unaligned_get32)(void const *__restrict __p);
extern void (__hybrid_unaligned_set16)(void *__restrict __p, __UINT16_TYPE__ __val);
extern void (__hybrid_unaligned_set32)(void *__restrict __p, __UINT32_TYPE__ __val);
#ifdef __UINT64_TYPE__
#define __hybrid_unaligned_get64 __hybrid_unaligned_get64
#define __hybrid_unaligned_set64 __hybrid_unaligned_set64
extern __UINT64_TYPE__ (__hybrid_unaligned_get64)(void const *__restrict __p);
extern void (__hybrid_unaligned_set64)(void *__restrict __p, __UINT64_TYPE__ __val);
#ifdef __UINT128_TYPE__
#define __hybrid_unaligned_get128 __hybrid_unaligned_get128
#define __hybrid_unaligned_set128 __hybrid_unaligned_set128
extern __UINT128_TYPE__ (__hybrid_unaligned_get128)(void const *__restrict __p);
extern void (__hybrid_unaligned_set128)(void *__restrict __p, __UINT128_TYPE__ __val);
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#elif !defined(__NO_hybrid_dbg_alignment)
#define __hybrid_unaligned_get16 __hybrid_unaligned_get16
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__
(__hybrid_unaligned_get16)(void const *__restrict __p) {
	__UINT16_TYPE__ __res;
	__hybrid_dbg_alignment_disable();
	__res = *(__UINT16_TYPE__ const *)__p;
	__hybrid_dbg_alignment_enable();
	return __res;
}
#define __hybrid_unaligned_set16 __hybrid_unaligned_set16
__LOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
(__hybrid_unaligned_set16)(void *__restrict __p, __UINT16_TYPE__ __val) {
	__hybrid_dbg_alignment_disable();
	*(__UINT16_TYPE__ *)__p = __val;
	__hybrid_dbg_alignment_enable();
}
#define __hybrid_unaligned_get32 __hybrid_unaligned_get32
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__
(__hybrid_unaligned_get32)(void const *__restrict __p) {
	__UINT32_TYPE__ __res;
	__hybrid_dbg_alignment_disable();
	__res = *(__UINT32_TYPE__ const *)__p;
	__hybrid_dbg_alignment_enable();
	return __res;
}
#define __hybrid_unaligned_set32 __hybrid_unaligned_set32
__LOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
(__hybrid_unaligned_set32)(void *__restrict __p, __UINT32_TYPE__ __val) {
	__hybrid_dbg_alignment_disable();
	*(__UINT32_TYPE__ *)__p = __val;
	__hybrid_dbg_alignment_enable();
}
#ifdef __UINT64_TYPE__
#define __hybrid_unaligned_get64 __hybrid_unaligned_get64
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__
(__hybrid_unaligned_get64)(void const *__restrict __p) {
	__UINT64_TYPE__ __res;
	__hybrid_dbg_alignment_disable();
	__res = *(__UINT64_TYPE__ const *)__p;
	__hybrid_dbg_alignment_enable();
	return __res;
}
#define __hybrid_unaligned_set64 __hybrid_unaligned_set64
__LOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
(__hybrid_unaligned_set64)(void *__restrict __p, __UINT64_TYPE__ __val) {
	__hybrid_dbg_alignment_disable();
	*(__UINT64_TYPE__ *)__p = __val;
	__hybrid_dbg_alignment_enable();
}
#ifdef __UINT128_TYPE__
#define __hybrid_unaligned_get128 __hybrid_unaligned_get128
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__
(__hybrid_unaligned_get128)(void const *__restrict __p) {
	__UINT128_TYPE__ __res;
	__hybrid_dbg_alignment_disable();
	__res = *(__UINT128_TYPE__ const *)__p;
	__hybrid_dbg_alignment_enable();
	return __res;
}
#define __hybrid_unaligned_set128 __hybrid_unaligned_set128
__LOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
(__hybrid_unaligned_set128)(void *__restrict __p, __UINT128_TYPE__ __val) {
	__hybrid_dbg_alignment_disable();
	*(__UINT128_TYPE__ *)__p = __val;
	__hybrid_dbg_alignment_enable();
}
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#elif defined(__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS)
#define __hybrid_unaligned_get(p)      (*(p))
#define __hybrid_unaligned_set(p, v)   (void)(*(p) = (v))
#define __hybrid_unaligned_get16(p)    (*(__UINT16_TYPE__ const *)(void const *)(p))
#define __hybrid_unaligned_set16(p, v) (void)(*(__UINT16_TYPE__ *)(void *)(p) = (v))
#define __hybrid_unaligned_get32(p)    (*(__UINT32_TYPE__ const *)(void const *)(p))
#define __hybrid_unaligned_set32(p, v) (void)(*(__UINT32_TYPE__ *)(void *)(p) = (v))
#ifdef __UINT64_TYPE__
#define __hybrid_unaligned_get64(p)    (*(__UINT64_TYPE__ const *)(void const *)(p))
#define __hybrid_unaligned_set64(p, v) (void)(*(__UINT64_TYPE__ *)(void *)(p) = (v))
#ifdef __UINT128_TYPE__
#define __hybrid_unaligned_get128(p)    (*(__UINT128_TYPE__ const *)(void const *)(p))
#define __hybrid_unaligned_set128(p, v) (void)(*(__UINT128_TYPE__ *)(void *)(p) = (v))
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#elif defined(__ARMCC_VERSION) || defined(__CC_ARM)
#define __hybrid_unaligned_get16(p)    (*(__packed __UINT16_TYPE__ const *)(void const *)(p))
#define __hybrid_unaligned_set16(p, v) (void)(*(__packed __UINT16_TYPE__ *)(void *)(p) = (v))
#define __hybrid_unaligned_get32(p)    (*(__packed __UINT32_TYPE__ const *)(void const *)(p))
#define __hybrid_unaligned_set32(p, v) (void)(*(__packed __UINT32_TYPE__ *)(void *)(p) = (v))
#ifdef __UINT64_TYPE__
#define __hybrid_unaligned_get64(p)    (*(__packed __UINT64_TYPE__ const *)(void const *)(p))
#define __hybrid_unaligned_set64(p, v) (void)(*(__packed __UINT64_TYPE__ *)(void *)(p) = (v))
#ifdef __UINT128_TYPE__
#define __hybrid_unaligned_get128(p)    (*(__packed __UINT128_TYPE__ const *)(void const *)(p))
#define __hybrid_unaligned_set128(p, v) (void)(*(__packed __UINT128_TYPE__ *)(void *)(p) = (v))
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#elif !defined(__NO_ATTR_PACKED)
__NAMESPACE_INT_BEGIN
struct __ATTR_PACKED __hybrid_unaligned_16 { __UINT16_TYPE__ __val; };
struct __ATTR_PACKED __hybrid_unaligned_32 { __UINT32_TYPE__ __val; };
#define __hybrid_unaligned_get16(p)    (((struct __NAMESPACE_INT_SYM __hybrid_unaligned_16 const *)(p))->__val)
#define __hybrid_unaligned_set16(p, v) (void)(((struct __NAMESPACE_INT_SYM __hybrid_unaligned_16 *)(void *)(p))->__val = (v))
#define __hybrid_unaligned_get32(p)    (((struct __NAMESPACE_INT_SYM __hybrid_unaligned_32 const *)(void const *)(p))->__val)
#define __hybrid_unaligned_set32(p, v) (void)(((struct __NAMESPACE_INT_SYM __hybrid_unaligned_32 *)(void *)(p))->__val = (v))
#ifdef __UINT64_TYPE__
struct __ATTR_PACKED __hybrid_unaligned_64 { __UINT64_TYPE__ __val; };
#define __hybrid_unaligned_get64(p)    (((struct __NAMESPACE_INT_SYM __hybrid_unaligned_64 const *)(void const *)(p))->__val)
#define __hybrid_unaligned_set64(p, v) (void)(((struct __NAMESPACE_INT_SYM __hybrid_unaligned_64 *)(void *)(p))->__val = (v))
#ifdef __UINT128_TYPE__
struct __ATTR_PACKED __hybrid_unaligned_128 { __UINT128_TYPE__ __val; };
#define __hybrid_unaligned_get128(p)    (((struct __NAMESPACE_INT_SYM __hybrid_unaligned_128 const *)(void const *)(p))->__val)
#define __hybrid_unaligned_set128(p, v) (void)(((struct __NAMESPACE_INT_SYM __hybrid_unaligned_128 *)(void *)(p))->__val = (v))
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
__NAMESPACE_INT_END
#else /* ... */
/* Fallback: use byte-level access to perform unaligned reads/writes */
#define __hybrid_unaligned_get16 __hybrid_unaligned_get16
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__
(__hybrid_unaligned_get16)(void const *__restrict __p) {
	union {
		__UINT16_TYPE__ __v16;
		__UINT8_TYPE__ __v8[2];
	} __res;
	if (!((__UINTPTR_TYPE__)__p & 1))
		return *(__UINT16_TYPE__ const *)__p;
	__res.__v8[0] = ((__UINT8_TYPE__ const *)__p)[0];
	__res.__v8[1] = ((__UINT8_TYPE__ const *)__p)[1];
	return __res.__v16;
}
#define __hybrid_unaligned_set16 __hybrid_unaligned_set16
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_unaligned_set16)(void *__restrict __p, __UINT16_TYPE__ __val) {
	union {
		__UINT16_TYPE__ __v16;
		__UINT8_TYPE__ __v8[2];
	} __res;
	if (!((__UINTPTR_TYPE__)__p & 1)) {
		*(__UINT16_TYPE__ *)__p = __val;
	} else {
		__res.__v16 = __val;
		((__UINT8_TYPE__ *)__p)[0] = __res.__v8[0];
		((__UINT8_TYPE__ *)__p)[1] = __res.__v8[1];
	}
}
#define __hybrid_unaligned_get16_swap __hybrid_unaligned_get16_swap
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__
(__hybrid_unaligned_get16_swap)(void const *__restrict __p) {
	union {
		__UINT16_TYPE__ __v16;
		__UINT8_TYPE__ __v8[2];
	} __res;
	if (!((__UINTPTR_TYPE__)__p & 1))
		return __hybrid_bswap16(*(__UINT16_TYPE__ const *)__p);
	__res.__v8[1] = ((__UINT8_TYPE__ const *)__p)[0];
	__res.__v8[0] = ((__UINT8_TYPE__ const *)__p)[1];
	return __res.__v16;
}
#define __hybrid_unaligned_set16_swap __hybrid_unaligned_set16_swap
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_unaligned_set16_swap)(void *__restrict __p, __UINT16_TYPE__ __val) {
	union {
		__UINT16_TYPE__ __v16;
		__UINT8_TYPE__ __v8[2];
	} __res;
	if (!((__UINTPTR_TYPE__)__p & 1)) {
		*(__UINT16_TYPE__ *)__p = __hybrid_bswap16(__val);
	} else {
		__res.__v16 = __val;
		((__UINT8_TYPE__ *)__p)[0] = __res.__v8[1];
		((__UINT8_TYPE__ *)__p)[1] = __res.__v8[0];
	}
}
#define __hybrid_unaligned_get32 __hybrid_unaligned_get32
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__
(__hybrid_unaligned_get32)(void const *__restrict __p) {
	union {
		__UINT32_TYPE__ __v32;
		__UINT16_TYPE__ __v16[2];
		__UINT8_TYPE__  __v8[4];
	} __res;
	if (!((__UINTPTR_TYPE__)__p & 3))
		return *(__UINT32_TYPE__ const *)__p;
	if (!((__UINTPTR_TYPE__)__p & 1)) {
		__res.__v16[0] = ((__UINT16_TYPE__ const *)__p)[0];
		__res.__v16[1] = ((__UINT16_TYPE__ const *)__p)[1];
	} else {
		__res.__v8[0] = ((__UINT8_TYPE__ const *)__p)[0];
		__res.__v8[1] = ((__UINT8_TYPE__ const *)__p)[1];
		__res.__v8[2] = ((__UINT8_TYPE__ const *)__p)[2];
		__res.__v8[3] = ((__UINT8_TYPE__ const *)__p)[3];
	}
	return __res.__v32;
}
#define __hybrid_unaligned_set32 __hybrid_unaligned_set32
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_unaligned_set32)(void *__restrict __p, __UINT32_TYPE__ __val) {
	union {
		__UINT32_TYPE__ __v32;
		__UINT16_TYPE__ __v16[2];
		__UINT8_TYPE__  __v8[4];
	} __res;
	if (!((__UINTPTR_TYPE__)__p & 3)) {
		*(__UINT32_TYPE__ *)__p = __val;
	} else {
		__res.__v32 = __val;
		if (!((__UINTPTR_TYPE__)__p & 1)) {
			((__UINT16_TYPE__ *)__p)[0] = __res.__v16[0];
			((__UINT16_TYPE__ *)__p)[1] = __res.__v16[1];
		} else {
			((__UINT8_TYPE__ *)__p)[0] = __res.__v8[0];
			((__UINT8_TYPE__ *)__p)[1] = __res.__v8[1];
			((__UINT8_TYPE__ *)__p)[2] = __res.__v8[2];
			((__UINT8_TYPE__ *)__p)[3] = __res.__v8[3];
		}
	}
}
#define __hybrid_unaligned_get32_swap __hybrid_unaligned_get32_swap
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__
(__hybrid_unaligned_get32_swap)(void const *__restrict __p) {
	union {
		__UINT32_TYPE__ __v32;
		__UINT16_TYPE__ __v16[2];
		__UINT8_TYPE__  __v8[4];
	} __res;
	if (!((__UINTPTR_TYPE__)__p & 3))
		return __hybrid_bswap32(*(__UINT32_TYPE__ const *)__p);
	if (!((__UINTPTR_TYPE__)__p & 1)) {
		__res.__v16[1] = __hybrid_bswap16(((__UINT16_TYPE__ const *)__p)[0]);
		__res.__v16[0] = __hybrid_bswap16(((__UINT16_TYPE__ const *)__p)[1]);
	} else {
		__res.__v8[3] = ((__UINT8_TYPE__ const *)__p)[0];
		__res.__v8[2] = ((__UINT8_TYPE__ const *)__p)[1];
		__res.__v8[1] = ((__UINT8_TYPE__ const *)__p)[2];
		__res.__v8[0] = ((__UINT8_TYPE__ const *)__p)[3];
	}
	return __res.__v32;
}
#define __hybrid_unaligned_set32_swap __hybrid_unaligned_set32_swap
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_unaligned_set32_swap)(void *__restrict __p, __UINT32_TYPE__ __val) {
	union {
		__UINT32_TYPE__ __v32;
		__UINT16_TYPE__ __v16[2];
		__UINT8_TYPE__  __v8[4];
	} __res;
	if (!((__UINTPTR_TYPE__)__p & 3)) {
		*(__UINT32_TYPE__ *)__p = __hybrid_bswap32(__val);
	} else {
		__res.__v32 = __val;
		if (!((__UINTPTR_TYPE__)__p & 1)) {
			((__UINT16_TYPE__ *)__p)[0] = __hybrid_bswap16(__res.__v16[1]);
			((__UINT16_TYPE__ *)__p)[1] = __hybrid_bswap16(__res.__v16[0]);
		} else {
			((__UINT8_TYPE__ *)__p)[0] = __res.__v8[3];
			((__UINT8_TYPE__ *)__p)[1] = __res.__v8[2];
			((__UINT8_TYPE__ *)__p)[2] = __res.__v8[1];
			((__UINT8_TYPE__ *)__p)[3] = __res.__v8[0];
		}
	}
}
#ifdef __UINT64_TYPE__
#define __hybrid_unaligned_get64 __hybrid_unaligned_get64
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__
(__hybrid_unaligned_get64)(void const *__restrict __p) {
	union {
		__UINT64_TYPE__ __v64;
		__UINT32_TYPE__ __v32[2];
		__UINT16_TYPE__ __v16[4];
		__UINT8_TYPE__  __v8[8];
	} __res;
	if (!((__UINTPTR_TYPE__)__p & 7))
		return *(__UINT64_TYPE__ const *)__p;
	if (!((__UINTPTR_TYPE__)__p & 3)) {
		__res.__v32[0] = ((__UINT32_TYPE__ const *)__p)[0];
		__res.__v32[1] = ((__UINT32_TYPE__ const *)__p)[1];
	} else if (!((__UINTPTR_TYPE__)__p & 1)) {
		__res.__v16[0] = ((__UINT16_TYPE__ const *)__p)[0];
		__res.__v16[1] = ((__UINT16_TYPE__ const *)__p)[1];
		__res.__v16[2] = ((__UINT16_TYPE__ const *)__p)[2];
		__res.__v16[3] = ((__UINT16_TYPE__ const *)__p)[3];
	} else {
		__res.__v8[0] = ((__UINT8_TYPE__ const *)__p)[0];
		__res.__v8[1] = ((__UINT8_TYPE__ const *)__p)[1];
		__res.__v8[2] = ((__UINT8_TYPE__ const *)__p)[2];
		__res.__v8[3] = ((__UINT8_TYPE__ const *)__p)[3];
		__res.__v8[4] = ((__UINT8_TYPE__ const *)__p)[4];
		__res.__v8[5] = ((__UINT8_TYPE__ const *)__p)[5];
		__res.__v8[6] = ((__UINT8_TYPE__ const *)__p)[6];
		__res.__v8[7] = ((__UINT8_TYPE__ const *)__p)[7];
	}
	return __res.__v64;
}
#define __hybrid_unaligned_set64 __hybrid_unaligned_set64
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_unaligned_set64)(void *__restrict __p, __UINT64_TYPE__ __val) {
	union {
		__UINT64_TYPE__ __v64;
		__UINT32_TYPE__ __v32[2];
		__UINT16_TYPE__ __v16[4];
		__UINT8_TYPE__  __v8[8];
	} __res;
	if (!((__UINTPTR_TYPE__)__p & 7)) {
		*(__UINT64_TYPE__ *)__p = __val;
	} else {
		__res.__v64 = __val;
		if (!((__UINTPTR_TYPE__)__p & 3)) {
			((__UINT32_TYPE__ *)__p)[0] = __res.__v32[0];
			((__UINT32_TYPE__ *)__p)[1] = __res.__v32[1];
		} else if (!((__UINTPTR_TYPE__)__p & 1)) {
			((__UINT16_TYPE__ *)__p)[0] = __res.__v16[0];
			((__UINT16_TYPE__ *)__p)[1] = __res.__v16[1];
			((__UINT16_TYPE__ *)__p)[2] = __res.__v16[2];
			((__UINT16_TYPE__ *)__p)[3] = __res.__v16[3];
		} else {
			((__UINT8_TYPE__ *)__p)[0] = __res.__v8[0];
			((__UINT8_TYPE__ *)__p)[1] = __res.__v8[1];
			((__UINT8_TYPE__ *)__p)[2] = __res.__v8[2];
			((__UINT8_TYPE__ *)__p)[3] = __res.__v8[3];
			((__UINT8_TYPE__ *)__p)[4] = __res.__v8[4];
			((__UINT8_TYPE__ *)__p)[5] = __res.__v8[5];
			((__UINT8_TYPE__ *)__p)[6] = __res.__v8[6];
			((__UINT8_TYPE__ *)__p)[7] = __res.__v8[7];
		}
	}
}
#define __hybrid_unaligned_get64_swap __hybrid_unaligned_get64_swap
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__
(__hybrid_unaligned_get64_swap)(void const *__restrict __p) {
	union {
		__UINT64_TYPE__ __v64;
		__UINT32_TYPE__ __v32[2];
		__UINT16_TYPE__ __v16[4];
		__UINT8_TYPE__  __v8[8];
	} __res;
	if (!((__UINTPTR_TYPE__)__p & 7))
		return __hybrid_bswap64(*(__UINT64_TYPE__ const *)__p);
	if (!((__UINTPTR_TYPE__)__p & 3)) {
		__res.__v32[1] = __hybrid_bswap32(((__UINT32_TYPE__ const *)__p)[0]);
		__res.__v32[0] = __hybrid_bswap32(((__UINT32_TYPE__ const *)__p)[1]);
	} else if (!((__UINTPTR_TYPE__)__p & 1)) {
		__res.__v16[3] = __hybrid_bswap16(((__UINT16_TYPE__ const *)__p)[0]);
		__res.__v16[2] = __hybrid_bswap16(((__UINT16_TYPE__ const *)__p)[1]);
		__res.__v16[1] = __hybrid_bswap16(((__UINT16_TYPE__ const *)__p)[2]);
		__res.__v16[0] = __hybrid_bswap16(((__UINT16_TYPE__ const *)__p)[3]);
	} else {
		__res.__v8[7] = ((__UINT8_TYPE__ const *)__p)[0];
		__res.__v8[6] = ((__UINT8_TYPE__ const *)__p)[1];
		__res.__v8[5] = ((__UINT8_TYPE__ const *)__p)[2];
		__res.__v8[4] = ((__UINT8_TYPE__ const *)__p)[3];
		__res.__v8[3] = ((__UINT8_TYPE__ const *)__p)[4];
		__res.__v8[2] = ((__UINT8_TYPE__ const *)__p)[5];
		__res.__v8[1] = ((__UINT8_TYPE__ const *)__p)[6];
		__res.__v8[0] = ((__UINT8_TYPE__ const *)__p)[7];
	}
	return __res.__v64;
}
#define __hybrid_unaligned_set64_swap __hybrid_unaligned_set64_swap
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_unaligned_set64_swap)(void *__restrict __p, __UINT64_TYPE__ __val) {
	union {
		__UINT64_TYPE__ __v64;
		__UINT32_TYPE__ __v32[2];
		__UINT16_TYPE__ __v16[4];
		__UINT8_TYPE__  __v8[8];
	} __res;
	if (!((__UINTPTR_TYPE__)__p & 7)) {
		*(__UINT64_TYPE__ *)__p = __hybrid_bswap64(__val);
	} else {
		__res.__v64 = __val;
		if (!((__UINTPTR_TYPE__)__p & 3)) {
			((__UINT32_TYPE__ *)__p)[0] = __hybrid_bswap32(__res.__v32[1]);
			((__UINT32_TYPE__ *)__p)[1] = __hybrid_bswap32(__res.__v32[0]);
		} else if (!((__UINTPTR_TYPE__)__p & 1)) {
			((__UINT16_TYPE__ *)__p)[0] = __hybrid_bswap16(__res.__v16[3]);
			((__UINT16_TYPE__ *)__p)[1] = __hybrid_bswap16(__res.__v16[2]);
			((__UINT16_TYPE__ *)__p)[2] = __hybrid_bswap16(__res.__v16[1]);
			((__UINT16_TYPE__ *)__p)[3] = __hybrid_bswap16(__res.__v16[0]);
		} else {
			((__UINT8_TYPE__ *)__p)[0] = __res.__v8[7];
			((__UINT8_TYPE__ *)__p)[1] = __res.__v8[6];
			((__UINT8_TYPE__ *)__p)[2] = __res.__v8[5];
			((__UINT8_TYPE__ *)__p)[3] = __res.__v8[4];
			((__UINT8_TYPE__ *)__p)[4] = __res.__v8[3];
			((__UINT8_TYPE__ *)__p)[5] = __res.__v8[2];
			((__UINT8_TYPE__ *)__p)[6] = __res.__v8[1];
			((__UINT8_TYPE__ *)__p)[7] = __res.__v8[0];
		}
	}
}
#ifdef __UINT128_TYPE__
#define __hybrid_unaligned_get128 __hybrid_unaligned_get128
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__
(__hybrid_unaligned_get128)(void const *__restrict __p) {
	union {
		__UINT128_TYPE__ __v128;
		__UINT64_TYPE__  __v64[2];
		__UINT32_TYPE__  __v32[4];
		__UINT16_TYPE__  __v16[8];
		__UINT8_TYPE__   __v8[16];
	} __res;
	if (!((__UINTPTR_TYPE__)__p & 15))
		return *(__UINT128_TYPE__ const *)__p;
	if (!((__UINTPTR_TYPE__)__p & 7)) {
		__res.__v64[0] = ((__UINT64_TYPE__ const *)__p)[0];
		__res.__v64[1] = ((__UINT64_TYPE__ const *)__p)[1];
	} else if (!((__UINTPTR_TYPE__)__p & 3)) {
		__res.__v32[0] = ((__UINT32_TYPE__ const *)__p)[0];
		__res.__v32[1] = ((__UINT32_TYPE__ const *)__p)[1];
		__res.__v32[2] = ((__UINT32_TYPE__ const *)__p)[2];
		__res.__v32[3] = ((__UINT32_TYPE__ const *)__p)[3];
	} else if (!((__UINTPTR_TYPE__)__p & 1)) {
		__res.__v16[0] = ((__UINT16_TYPE__ const *)__p)[0];
		__res.__v16[1] = ((__UINT16_TYPE__ const *)__p)[1];
		__res.__v16[2] = ((__UINT16_TYPE__ const *)__p)[2];
		__res.__v16[3] = ((__UINT16_TYPE__ const *)__p)[3];
		__res.__v16[4] = ((__UINT16_TYPE__ const *)__p)[4];
		__res.__v16[5] = ((__UINT16_TYPE__ const *)__p)[5];
		__res.__v16[6] = ((__UINT16_TYPE__ const *)__p)[6];
		__res.__v16[7] = ((__UINT16_TYPE__ const *)__p)[7];
	} else {
		__res.__v8[0x0] = ((__UINT8_TYPE__ const *)__p)[0x0];
		__res.__v8[0x1] = ((__UINT8_TYPE__ const *)__p)[0x1];
		__res.__v8[0x2] = ((__UINT8_TYPE__ const *)__p)[0x2];
		__res.__v8[0x3] = ((__UINT8_TYPE__ const *)__p)[0x3];
		__res.__v8[0x4] = ((__UINT8_TYPE__ const *)__p)[0x4];
		__res.__v8[0x5] = ((__UINT8_TYPE__ const *)__p)[0x5];
		__res.__v8[0x6] = ((__UINT8_TYPE__ const *)__p)[0x6];
		__res.__v8[0x7] = ((__UINT8_TYPE__ const *)__p)[0x7];
		__res.__v8[0x8] = ((__UINT8_TYPE__ const *)__p)[0x8];
		__res.__v8[0x9] = ((__UINT8_TYPE__ const *)__p)[0x9];
		__res.__v8[0xa] = ((__UINT8_TYPE__ const *)__p)[0xa];
		__res.__v8[0xb] = ((__UINT8_TYPE__ const *)__p)[0xb];
		__res.__v8[0xc] = ((__UINT8_TYPE__ const *)__p)[0xc];
		__res.__v8[0xd] = ((__UINT8_TYPE__ const *)__p)[0xd];
		__res.__v8[0xe] = ((__UINT8_TYPE__ const *)__p)[0xe];
		__res.__v8[0xf] = ((__UINT8_TYPE__ const *)__p)[0xf];
	}
	return __res.__v128;
}
#define __hybrid_unaligned_set128 __hybrid_unaligned_set128
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_unaligned_set128)(void *__restrict __p, __UINT128_TYPE__ __val) {
	union {
		__UINT128_TYPE__ __v128;
		__UINT64_TYPE__  __v64[2];
		__UINT32_TYPE__  __v32[4];
		__UINT16_TYPE__  __v16[8];
		__UINT8_TYPE__   __v8[16];
	} __res;
	if (!((__UINTPTR_TYPE__)__p & 15)) {
		*(__UINT128_TYPE__ *)__p = __val;
	} else {
		__res.__v128 = __val;
		if (!((__UINTPTR_TYPE__)__p & 7)) {
			((__UINT64_TYPE__ *)__p)[0] = __res.__v64[0];
			((__UINT64_TYPE__ *)__p)[1] = __res.__v64[1];
		} else if (!((__UINTPTR_TYPE__)__p & 3)) {
			((__UINT32_TYPE__ *)__p)[0] = __res.__v32[0];
			((__UINT32_TYPE__ *)__p)[1] = __res.__v32[1];
			((__UINT32_TYPE__ *)__p)[2] = __res.__v32[2];
			((__UINT32_TYPE__ *)__p)[3] = __res.__v32[3];
		} else if (!((__UINTPTR_TYPE__)__p & 1)) {
			((__UINT16_TYPE__ *)__p)[0] = __res.__v16[0];
			((__UINT16_TYPE__ *)__p)[1] = __res.__v16[1];
			((__UINT16_TYPE__ *)__p)[2] = __res.__v16[2];
			((__UINT16_TYPE__ *)__p)[3] = __res.__v16[3];
			((__UINT16_TYPE__ *)__p)[4] = __res.__v16[4];
			((__UINT16_TYPE__ *)__p)[5] = __res.__v16[5];
			((__UINT16_TYPE__ *)__p)[6] = __res.__v16[6];
			((__UINT16_TYPE__ *)__p)[7] = __res.__v16[7];
		} else {
			((__UINT8_TYPE__ *)__p)[0x0] = __res.__v8[0x0];
			((__UINT8_TYPE__ *)__p)[0x1] = __res.__v8[0x1];
			((__UINT8_TYPE__ *)__p)[0x2] = __res.__v8[0x2];
			((__UINT8_TYPE__ *)__p)[0x3] = __res.__v8[0x3];
			((__UINT8_TYPE__ *)__p)[0x4] = __res.__v8[0x4];
			((__UINT8_TYPE__ *)__p)[0x5] = __res.__v8[0x5];
			((__UINT8_TYPE__ *)__p)[0x6] = __res.__v8[0x6];
			((__UINT8_TYPE__ *)__p)[0x7] = __res.__v8[0x7];
			((__UINT8_TYPE__ *)__p)[0x8] = __res.__v8[0x8];
			((__UINT8_TYPE__ *)__p)[0x9] = __res.__v8[0x9];
			((__UINT8_TYPE__ *)__p)[0xa] = __res.__v8[0xa];
			((__UINT8_TYPE__ *)__p)[0xb] = __res.__v8[0xb];
			((__UINT8_TYPE__ *)__p)[0xc] = __res.__v8[0xc];
			((__UINT8_TYPE__ *)__p)[0xd] = __res.__v8[0xd];
			((__UINT8_TYPE__ *)__p)[0xe] = __res.__v8[0xe];
			((__UINT8_TYPE__ *)__p)[0xf] = __res.__v8[0xf];
		}
	}
}
#define __hybrid_unaligned_get128_swap __hybrid_unaligned_get128_swap
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__
(__hybrid_unaligned_get128_swap)(void const *__restrict __p) {
	union {
		__UINT128_TYPE__ __v128;
		__UINT64_TYPE__  __v64[2];
		__UINT32_TYPE__  __v32[4];
		__UINT16_TYPE__  __v16[8];
		__UINT8_TYPE__   __v8[16];
	} __res;
	if (!((__UINTPTR_TYPE__)__p & 15))
		return *(__UINT128_TYPE__ const *)__p;
	if (!((__UINTPTR_TYPE__)__p & 7)) {
		__res.__v64[0] = ((__UINT64_TYPE__ const *)__p)[0];
		__res.__v64[1] = ((__UINT64_TYPE__ const *)__p)[1];
	} else if (!((__UINTPTR_TYPE__)__p & 3)) {
		__res.__v32[0] = ((__UINT32_TYPE__ const *)__p)[0];
		__res.__v32[1] = ((__UINT32_TYPE__ const *)__p)[1];
		__res.__v32[2] = ((__UINT32_TYPE__ const *)__p)[2];
		__res.__v32[3] = ((__UINT32_TYPE__ const *)__p)[3];
	} else if (!((__UINTPTR_TYPE__)__p & 1)) {
		__res.__v16[0] = ((__UINT16_TYPE__ const *)__p)[0];
		__res.__v16[1] = ((__UINT16_TYPE__ const *)__p)[1];
		__res.__v16[2] = ((__UINT16_TYPE__ const *)__p)[2];
		__res.__v16[3] = ((__UINT16_TYPE__ const *)__p)[3];
		__res.__v16[4] = ((__UINT16_TYPE__ const *)__p)[4];
		__res.__v16[5] = ((__UINT16_TYPE__ const *)__p)[5];
		__res.__v16[6] = ((__UINT16_TYPE__ const *)__p)[6];
		__res.__v16[7] = ((__UINT16_TYPE__ const *)__p)[7];
	} else {
		__res.__v8[0x0] = ((__UINT8_TYPE__ const *)__p)[0x0];
		__res.__v8[0x1] = ((__UINT8_TYPE__ const *)__p)[0x1];
		__res.__v8[0x2] = ((__UINT8_TYPE__ const *)__p)[0x2];
		__res.__v8[0x3] = ((__UINT8_TYPE__ const *)__p)[0x3];
		__res.__v8[0x4] = ((__UINT8_TYPE__ const *)__p)[0x4];
		__res.__v8[0x5] = ((__UINT8_TYPE__ const *)__p)[0x5];
		__res.__v8[0x6] = ((__UINT8_TYPE__ const *)__p)[0x6];
		__res.__v8[0x7] = ((__UINT8_TYPE__ const *)__p)[0x7];
		__res.__v8[0x8] = ((__UINT8_TYPE__ const *)__p)[0x8];
		__res.__v8[0x9] = ((__UINT8_TYPE__ const *)__p)[0x9];
		__res.__v8[0xa] = ((__UINT8_TYPE__ const *)__p)[0xa];
		__res.__v8[0xb] = ((__UINT8_TYPE__ const *)__p)[0xb];
		__res.__v8[0xc] = ((__UINT8_TYPE__ const *)__p)[0xc];
		__res.__v8[0xd] = ((__UINT8_TYPE__ const *)__p)[0xd];
		__res.__v8[0xe] = ((__UINT8_TYPE__ const *)__p)[0xe];
		__res.__v8[0xf] = ((__UINT8_TYPE__ const *)__p)[0xf];
	}
	return __res.__v128;
}
#define __hybrid_unaligned_set128_swap __hybrid_unaligned_set128_swap
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_unaligned_set128_swap)(void *__restrict __p, __UINT128_TYPE__ __val) {
	union {
		__UINT128_TYPE__ __v128;
		__UINT64_TYPE__  __v64[2];
		__UINT32_TYPE__  __v32[4];
		__UINT16_TYPE__  __v16[8];
		__UINT8_TYPE__   __v8[16];
	} __res;
	if (!((__UINTPTR_TYPE__)__p & 15)) {
		*(__UINT128_TYPE__ *)__p = __hybrid_bswap128(__val);
	} else {
		__res.__v128 = __val;
		if (!((__UINTPTR_TYPE__)__p & 7)) {
			((__UINT64_TYPE__ *)__p)[0] = __hybrid_bswap64(__res.__v64[1]);
			((__UINT64_TYPE__ *)__p)[1] = __hybrid_bswap64(__res.__v64[0]);
		} else if (!((__UINTPTR_TYPE__)__p & 3)) {
			((__UINT32_TYPE__ *)__p)[0] = __hybrid_bswap32(__res.__v32[3]);
			((__UINT32_TYPE__ *)__p)[1] = __hybrid_bswap32(__res.__v32[2]);
			((__UINT32_TYPE__ *)__p)[2] = __hybrid_bswap32(__res.__v32[1]);
			((__UINT32_TYPE__ *)__p)[3] = __hybrid_bswap32(__res.__v32[0]);
		} else if (!((__UINTPTR_TYPE__)__p & 1)) {
			((__UINT16_TYPE__ *)__p)[0] = __hybrid_bswap16(__res.__v16[7]);
			((__UINT16_TYPE__ *)__p)[1] = __hybrid_bswap16(__res.__v16[6]);
			((__UINT16_TYPE__ *)__p)[2] = __hybrid_bswap16(__res.__v16[5]);
			((__UINT16_TYPE__ *)__p)[3] = __hybrid_bswap16(__res.__v16[4]);
			((__UINT16_TYPE__ *)__p)[4] = __hybrid_bswap16(__res.__v16[3]);
			((__UINT16_TYPE__ *)__p)[5] = __hybrid_bswap16(__res.__v16[2]);
			((__UINT16_TYPE__ *)__p)[6] = __hybrid_bswap16(__res.__v16[1]);
			((__UINT16_TYPE__ *)__p)[7] = __hybrid_bswap16(__res.__v16[0]);
		} else {
			((__UINT8_TYPE__ *)__p)[0x0] = __res.__v8[0xf];
			((__UINT8_TYPE__ *)__p)[0x1] = __res.__v8[0xe];
			((__UINT8_TYPE__ *)__p)[0x2] = __res.__v8[0xd];
			((__UINT8_TYPE__ *)__p)[0x3] = __res.__v8[0xc];
			((__UINT8_TYPE__ *)__p)[0x4] = __res.__v8[0xb];
			((__UINT8_TYPE__ *)__p)[0x5] = __res.__v8[0xa];
			((__UINT8_TYPE__ *)__p)[0x6] = __res.__v8[0x9];
			((__UINT8_TYPE__ *)__p)[0x7] = __res.__v8[0x8];
			((__UINT8_TYPE__ *)__p)[0x8] = __res.__v8[0x7];
			((__UINT8_TYPE__ *)__p)[0x9] = __res.__v8[0x6];
			((__UINT8_TYPE__ *)__p)[0xa] = __res.__v8[0x5];
			((__UINT8_TYPE__ *)__p)[0xb] = __res.__v8[0x4];
			((__UINT8_TYPE__ *)__p)[0xc] = __res.__v8[0x3];
			((__UINT8_TYPE__ *)__p)[0xd] = __res.__v8[0x2];
			((__UINT8_TYPE__ *)__p)[0xe] = __res.__v8[0x1];
			((__UINT8_TYPE__ *)__p)[0xf] = __res.__v8[0x0];
		}
	}
}
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#endif /* !... */

#define __hybrid_unaligned_get8(p)    (*(__UINT8_TYPE__ const *)(void const *)(p))
#define __hybrid_unaligned_set8(p, v) (void)(*(__UINT8_TYPE__ *)(void *)(p) = (v))
#define __hybrid_unaligned_get8_swap  __hybrid_unaligned_get8
#define __hybrid_unaligned_set8_swap  __hybrid_unaligned_set8
#define __hybrid_unaligned_getle8     __hybrid_unaligned_get8
#define __hybrid_unaligned_setle8     __hybrid_unaligned_set8
#define __hybrid_unaligned_getbe8     __hybrid_unaligned_get8
#define __hybrid_unaligned_setbe8     __hybrid_unaligned_set8

#ifndef __hybrid_unaligned_get16_swap
#define __hybrid_unaligned_get16_swap(p) __hybrid_bswap16(__hybrid_unaligned_get16(p))
#endif /* !__hybrid_unaligned_get16_swap */
#ifndef __hybrid_unaligned_set16_swap
#define __hybrid_unaligned_set16_swap(p, v) __hybrid_unaligned_set16(p, __hybrid_bswap16(v))
#endif /* !__hybrid_unaligned_set16_swap */
#ifndef __hybrid_unaligned_get32_swap
#define __hybrid_unaligned_get32_swap(p) __hybrid_bswap32(__hybrid_unaligned_get32(p))
#endif /* !__hybrid_unaligned_get32_swap */
#ifndef __hybrid_unaligned_set32_swap
#define __hybrid_unaligned_set32_swap(p, v) __hybrid_unaligned_set32(p, __hybrid_bswap32(v))
#endif /* !__hybrid_unaligned_set32_swap */
#ifdef __UINT64_TYPE__
#ifndef __hybrid_unaligned_get64_swap
#define __hybrid_unaligned_get64_swap(p) __hybrid_bswap64(__hybrid_unaligned_get64(p))
#endif /* !__hybrid_unaligned_get64_swap */
#ifndef __hybrid_unaligned_set64_swap
#define __hybrid_unaligned_set64_swap(p, v) __hybrid_unaligned_set64(p, __hybrid_bswap64(v))
#endif /* !__hybrid_unaligned_set64_swap */
#ifdef __UINT128_TYPE__
#ifndef __hybrid_unaligned_get128_swap
#define __hybrid_unaligned_get128_swap(p) __hybrid_bswap128(__hybrid_unaligned_get128(p))
#endif /* !__hybrid_unaligned_get128_swap */
#ifndef __hybrid_unaligned_set128_swap
#define __hybrid_unaligned_set128_swap(p, v) __hybrid_unaligned_set128(p, __hybrid_bswap128(v))
#endif /* !__hybrid_unaligned_set128_swap */
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */

/* clang-format off */
#ifndef __hybrid_unaligned_set
#ifndef __NO_builtin_choose_expr
#ifdef __UINT128_TYPE__
#define __hybrid_unaligned_set(p, v) \
	__builtin_choose_expr(sizeof(*(p)) <= 1, __hybrid_unaligned_set8(p, (__UINT8_TYPE__)(v)), \
	__builtin_choose_expr(sizeof(*(p)) <= 2, __hybrid_unaligned_set16(p, (__UINT16_TYPE__)(v)), \
	__builtin_choose_expr(sizeof(*(p)) <= 4, __hybrid_unaligned_set32(p, (__UINT32_TYPE__)(v)), \
	__builtin_choose_expr(sizeof(*(p)) <= 8, __hybrid_unaligned_set64(p, (__UINT64_TYPE__)(v)), \
	                                         __hybrid_unaligned_set128(p, (__UINT128_TYPE__)(v))))))
#elif defined(__UINT64_TYPE__)
#define __hybrid_unaligned_set(p, v) \
	__builtin_choose_expr(sizeof(*(p)) <= 1, __hybrid_unaligned_set8(p, (__UINT8_TYPE__)(v)), \
	__builtin_choose_expr(sizeof(*(p)) <= 2, __hybrid_unaligned_set16(p, (__UINT16_TYPE__)(v)), \
	__builtin_choose_expr(sizeof(*(p)) <= 4, __hybrid_unaligned_set32(p, (__UINT32_TYPE__)(v)), \
	                                         __hybrid_unaligned_set64(p, (__UINT64_TYPE__)(v)))))
#else /* ... */
#define __hybrid_unaligned_set(p, v) \
	__builtin_choose_expr(sizeof(*(p)) <= 1, __hybrid_unaligned_set8(p, (__UINT8_TYPE__)(v)), \
	__builtin_choose_expr(sizeof(*(p)) <= 2, __hybrid_unaligned_set16(p, (__UINT16_TYPE__)(v)), \
	                                         __hybrid_unaligned_set32(p, (__UINT32_TYPE__)(v))))
#endif /* !... */
#else /* !__NO_builtin_choose_expr */
#ifdef __UINT128_TYPE__
#define __hybrid_unaligned_set(p, v) \
	(sizeof(*(p)) <= 1 ? __hybrid_unaligned_set8(p, (__UINT8_TYPE__)(v)) : \
	 sizeof(*(p)) <= 2 ? __hybrid_unaligned_set16(p, (__UINT16_TYPE__)(v)) : \
	 sizeof(*(p)) <= 4 ? __hybrid_unaligned_set32(p, (__UINT32_TYPE__)(v)) : \
	 sizeof(*(p)) <= 8 ? __hybrid_unaligned_set64(p, (__UINT64_TYPE__)(v)) : \
	                     __hybrid_unaligned_set128(p, (__UINT128_TYPE__)(v)))
#elif defined(__UINT64_TYPE__)
#define __hybrid_unaligned_set(p, v) \
	(sizeof(*(p)) <= 1 ? __hybrid_unaligned_set8(p, (__UINT8_TYPE__)(v)) : \
	 sizeof(*(p)) <= 2 ? __hybrid_unaligned_set16(p, (__UINT16_TYPE__)(v)) : \
	 sizeof(*(p)) <= 4 ? __hybrid_unaligned_set32(p, (__UINT32_TYPE__)(v)) : \
	                     __hybrid_unaligned_set64(p, (__UINT64_TYPE__)(v)))
#else /* ... */
#define __hybrid_unaligned_set(p, v) \
	(sizeof(*(p)) <= 1 ? __hybrid_unaligned_set8(p, (__UINT8_TYPE__)(v)) : \
	 sizeof(*(p)) <= 2 ? __hybrid_unaligned_set16(p, (__UINT16_TYPE__)(v)) : \
	                     __hybrid_unaligned_set32(p, (__UINT32_TYPE__)(v)))
#endif /* !... */
#endif /* __NO_builtin_choose_expr */
#endif /* !__hybrid_unaligned_set */

#ifndef __hybrid_unaligned_set_swap
#ifndef __NO_builtin_choose_expr
#ifdef __UINT128_TYPE__
#define __hybrid_unaligned_set_swap(p, v) \
	__builtin_choose_expr(sizeof(*(p)) <= 1, __hybrid_unaligned_set8_swap(p, (__UINT8_TYPE__)(v)), \
	__builtin_choose_expr(sizeof(*(p)) <= 2, __hybrid_unaligned_set16_swap(p, (__UINT16_TYPE__)(v)), \
	__builtin_choose_expr(sizeof(*(p)) <= 4, __hybrid_unaligned_set32_swap(p, (__UINT32_TYPE__)(v)), \
	__builtin_choose_expr(sizeof(*(p)) <= 8, __hybrid_unaligned_set64_swap(p, (__UINT64_TYPE__)(v)), \
	                                         __hybrid_unaligned_set128_swap(p, (__UINT128_TYPE__)(v))))))
#elif defined(__UINT64_TYPE__)
#define __hybrid_unaligned_set_swap(p, v) \
	__builtin_choose_expr(sizeof(*(p)) <= 1, __hybrid_unaligned_set8_swap(p, (__UINT8_TYPE__)(v)), \
	__builtin_choose_expr(sizeof(*(p)) <= 2, __hybrid_unaligned_set16_swap(p, (__UINT16_TYPE__)(v)), \
	__builtin_choose_expr(sizeof(*(p)) <= 4, __hybrid_unaligned_set32_swap(p, (__UINT32_TYPE__)(v)), \
	                                         __hybrid_unaligned_set64_swap(p, (__UINT64_TYPE__)(v)))))
#else /* ... */
#define __hybrid_unaligned_set_swap(p, v) \
	__builtin_choose_expr(sizeof(*(p)) <= 1, __hybrid_unaligned_set8_swap(p, (__UINT8_TYPE__)(v)), \
	__builtin_choose_expr(sizeof(*(p)) <= 2, __hybrid_unaligned_set16_swap(p, (__UINT16_TYPE__)(v)), \
	                                         __hybrid_unaligned_set32_swap(p, (__UINT32_TYPE__)(v))))
#endif /* !... */
#else /* !__NO_builtin_choose_expr */
#ifdef __UINT128_TYPE__
#define __hybrid_unaligned_set_swap(p, v) \
	(sizeof(*(p)) <= 1 ? __hybrid_unaligned_set8_swap(p, (__UINT8_TYPE__)(v)) : \
	 sizeof(*(p)) <= 2 ? __hybrid_unaligned_set16_swap(p, (__UINT16_TYPE__)(v)) : \
	 sizeof(*(p)) <= 4 ? __hybrid_unaligned_set32_swap(p, (__UINT32_TYPE__)(v)) : \
	 sizeof(*(p)) <= 8 ? __hybrid_unaligned_set64_swap(p, (__UINT64_TYPE__)(v)) : \
	                     __hybrid_unaligned_set128_swap(p, (__UINT128_TYPE__)(v)))
#elif defined(__UINT64_TYPE__)
#define __hybrid_unaligned_set_swap(p, v) \
	(sizeof(*(p)) <= 1 ? __hybrid_unaligned_set8_swap(p, (__UINT8_TYPE__)(v)) : \
	 sizeof(*(p)) <= 2 ? __hybrid_unaligned_set16_swap(p, (__UINT16_TYPE__)(v)) : \
	 sizeof(*(p)) <= 4 ? __hybrid_unaligned_set32_swap(p, (__UINT32_TYPE__)(v)) : \
	                     __hybrid_unaligned_set64_swap(p, (__UINT64_TYPE__)(v)))
#else /* ... */
#define __hybrid_unaligned_set_swap(p, v) \
	(sizeof(*(p)) <= 1 ? __hybrid_unaligned_set8_swap(p, (__UINT8_TYPE__)(v)) : \
	 sizeof(*(p)) <= 2 ? __hybrid_unaligned_set16_swap(p, (__UINT16_TYPE__)(v)) : \
	                     __hybrid_unaligned_set32_swap(p, (__UINT32_TYPE__)(v)))
#endif /* !... */
#endif /* __NO_builtin_choose_expr */
#endif /* !__hybrid_unaligned_set_swap */

#ifndef __hybrid_unaligned_get
#ifndef __NO_builtin_choose_expr
#ifdef __UINT128_TYPE__
#define __hybrid_unaligned_get(p) \
	__builtin_choose_expr(sizeof(*(p)) <= 1, __hybrid_unaligned_get8(p), \
	__builtin_choose_expr(sizeof(*(p)) <= 2, __hybrid_unaligned_get16(p), \
	__builtin_choose_expr(sizeof(*(p)) <= 4, __hybrid_unaligned_get32(p), \
	__builtin_choose_expr(sizeof(*(p)) <= 8, __hybrid_unaligned_get64(p), \
	                                         __hybrid_unaligned_get128(p)))))
#elif defined(__UINT64_TYPE__)
#define __hybrid_unaligned_get(p) \
	__builtin_choose_expr(sizeof(*(p)) <= 1, __hybrid_unaligned_get8(p), \
	__builtin_choose_expr(sizeof(*(p)) <= 2, __hybrid_unaligned_get16(p), \
	__builtin_choose_expr(sizeof(*(p)) <= 4, __hybrid_unaligned_get32(p), \
	                                         __hybrid_unaligned_get64(p))))
#else /* ... */
#define __hybrid_unaligned_get(p) \
	__builtin_choose_expr(sizeof(*(p)) <= 1, __hybrid_unaligned_get8(p), \
	__builtin_choose_expr(sizeof(*(p)) <= 2, __hybrid_unaligned_get16(p), \
	                                         __hybrid_unaligned_get32(p)))
#endif /* !... */
#elif defined(__cplusplus)
extern "C++" {
#define __hybrid_unaligned_get __hybrid_unaligned_get
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ (__hybrid_unaligned_get)(__INT8_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get8(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ (__hybrid_unaligned_get)(__UINT8_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get8(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ (__hybrid_unaligned_get)(__INT16_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get16(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ (__hybrid_unaligned_get)(__UINT16_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get16(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ (__hybrid_unaligned_get)(__INT32_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get32(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ (__hybrid_unaligned_get)(__UINT32_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get32(__p); }
#ifdef __UINT64_TYPE__
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ (__hybrid_unaligned_get)(__INT64_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get64(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ (__hybrid_unaligned_get)(__UINT64_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get64(__p); }
#ifdef __UINT128_TYPE__
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__ (__hybrid_unaligned_get)(__INT128_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get128(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__ (__hybrid_unaligned_get)(__UINT128_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get128(__p); }
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#ifdef __UFIFTHINT_TYPE__
#if __SIZEOF_FIFTHINT__ == 1
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get)(__FIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get8(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get)(__UFIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get8(__p); }
#elif __SIZEOF_FIFTHINT__ == 2
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get)(__FIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get16(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get)(__UFIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get16(__p); }
#elif __SIZEOF_FIFTHINT__ == 4
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get)(__FIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get32(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get)(__UFIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get32(__p); }
#elif __SIZEOF_FIFTHINT__ == 8
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get)(__FIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get64(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get)(__UFIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get64(__p); }
#elif __SIZEOF_FIFTHINT__ == 16
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get)(__FIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get128(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get)(__UFIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get128(__p); }
#else /* __SIZEOF_FIFTHINT__ == ... */
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get)(__FIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get((__UFIFTHINT_ALIAS_TYPE__ const *)__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get)(__UFIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get((__UFIFTHINT_ALIAS_TYPE__ const *)__p); }
#endif /* __SIZEOF_FIFTHINT__ != ... */
#endif /* __UFIFTHINT_TYPE__ */
} /* extern "C++" */
#else /* !... */
#ifdef __COMPILER_HAVE_TYPEOF
#define __HYBRID_UNALIGNED_RECAST(p, y) ((__typeof__(*(p)))(y))
#elif 1
#define __HYBRID_UNALIGNED_RECAST(p, y) (1 ? (y) : *(p))
#else /* ... */
#define __HYBRID_UNALIGNED_RECAST(p, y) (y)
#endif /* !... */
#ifdef __UINT128_TYPE__
#define __hybrid_unaligned_get(p) __HYBRID_UNALIGNED_RECAST(p, \
	sizeof(*(p)) <= 1 ? __hybrid_unaligned_get8(p) : \
	sizeof(*(p)) <= 2 ? __hybrid_unaligned_get16(p) : \
	sizeof(*(p)) <= 4 ? __hybrid_unaligned_get32(p) : \
	sizeof(*(p)) <= 8 ? __hybrid_unaligned_get64(p) : \
	                    __hybrid_unaligned_get128(p))
#elif defined(__UINT64_TYPE__)
#define __hybrid_unaligned_get(p) __HYBRID_UNALIGNED_RECAST(p, \
	sizeof(*(p)) <= 1 ? __hybrid_unaligned_get8(p) : \
	sizeof(*(p)) <= 2 ? __hybrid_unaligned_get16(p) : \
	sizeof(*(p)) <= 4 ? __hybrid_unaligned_get32(p) : \
	                    __hybrid_unaligned_get64(p))
#else /* ... */
#define __hybrid_unaligned_get(p) __HYBRID_UNALIGNED_RECAST(p, \
	sizeof(*(p)) <= 1 ? __hybrid_unaligned_get8(p) : \
	sizeof(*(p)) <= 2 ? __hybrid_unaligned_get16(p) : \
	                    __hybrid_unaligned_get32(p))
#endif /* !... */
#endif /* ... */
#endif /* !__hybrid_unaligned_get */

#ifndef __hybrid_unaligned_get_swap
#ifndef __NO_builtin_choose_expr
#ifdef __UINT128_TYPE__
#define __hybrid_unaligned_get_swap(p) \
	__builtin_choose_expr(sizeof(*(p)) <= 1, __hybrid_unaligned_get8_swap(p), \
	__builtin_choose_expr(sizeof(*(p)) <= 2, __hybrid_unaligned_get16_swap(p), \
	__builtin_choose_expr(sizeof(*(p)) <= 4, __hybrid_unaligned_get32_swap(p), \
	__builtin_choose_expr(sizeof(*(p)) <= 8, __hybrid_unaligned_get64_swap(p), \
	                                         __hybrid_unaligned_get128_swap(p)))))
#elif defined(__UINT64_TYPE__)
#define __hybrid_unaligned_get_swap(p) \
	__builtin_choose_expr(sizeof(*(p)) <= 1, __hybrid_unaligned_get8_swap(p), \
	__builtin_choose_expr(sizeof(*(p)) <= 2, __hybrid_unaligned_get16_swap(p), \
	__builtin_choose_expr(sizeof(*(p)) <= 4, __hybrid_unaligned_get32_swap(p), \
	                                         __hybrid_unaligned_get64_swap(p))))
#else /* ... */
#define __hybrid_unaligned_get_swap(p) \
	__builtin_choose_expr(sizeof(*(p)) <= 1, __hybrid_unaligned_get8_swap(p), \
	__builtin_choose_expr(sizeof(*(p)) <= 2, __hybrid_unaligned_get16_swap(p), \
	                                         __hybrid_unaligned_get32_swap(p)))
#endif /* !... */
#elif defined(__cplusplus)
extern "C++" {
#define __hybrid_unaligned_get_swap __hybrid_unaligned_get_swap
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ (__hybrid_unaligned_get_swap)(__INT8_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get8_swap(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ (__hybrid_unaligned_get_swap)(__UINT8_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get8_swap(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ (__hybrid_unaligned_get_swap)(__INT16_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get16_swap(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ (__hybrid_unaligned_get_swap)(__UINT16_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get16_swap(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ (__hybrid_unaligned_get_swap)(__INT32_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get32_swap(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ (__hybrid_unaligned_get_swap)(__UINT32_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get32_swap(__p); }
#ifdef __UINT64_TYPE__
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ (__hybrid_unaligned_get_swap)(__INT64_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get64_swap(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ (__hybrid_unaligned_get_swap)(__UINT64_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get64_swap(__p); }
#ifdef __UINT128_TYPE__
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__ (__hybrid_unaligned_get_swap)(__INT128_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get128_swap(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__ (__hybrid_unaligned_get_swap)(__UINT128_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get128_swap(__p); }
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#ifdef __UFIFTHINT_TYPE__
#if __SIZEOF_FIFTHINT__ == 1
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get_swap)(__FIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get8_swap(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get_swap)(__UFIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get8_swap(__p); }
#elif __SIZEOF_FIFTHINT__ == 2
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get_swap)(__FIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get16_swap(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get_swap)(__UFIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get16_swap(__p); }
#elif __SIZEOF_FIFTHINT__ == 4
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get_swap)(__FIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get32_swap(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get_swap)(__UFIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get32_swap(__p); }
#elif __SIZEOF_FIFTHINT__ == 8
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get_swap)(__FIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get64_swap(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get_swap)(__UFIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get64_swap(__p); }
#elif __SIZEOF_FIFTHINT__ == 16
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get_swap)(__FIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get128_swap(__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get_swap)(__UFIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get128_swap(__p); }
#else /* __SIZEOF_FIFTHINT__ == ... */
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get_swap)(__FIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get_swap((__UFIFTHINT_ALIAS_TYPE__ const *)__p); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_ALIAS_TYPE__ (__hybrid_unaligned_get_swap)(__UFIFTHINT_TYPE__ const *__restrict __p) { return __hybrid_unaligned_get_swap((__UFIFTHINT_ALIAS_TYPE__ const *)__p); }
#endif /* __SIZEOF_FIFTHINT__ != ... */
#endif /* __UFIFTHINT_TYPE__ */
} /* extern "C++" */
#else /* !... */
#ifdef __COMPILER_HAVE_TYPEOF
#define __HYBRID_UNALIGNED_RECAST(p, y) ((__typeof__(*(p)))(y))
#elif 1
#define __HYBRID_UNALIGNED_RECAST(p, y) (1 ? (y) : *(p))
#else /* ... */
#define __HYBRID_UNALIGNED_RECAST(p, y) (y)
#endif /* !... */
#ifdef __UINT128_TYPE__
#define __hybrid_unaligned_get_swap(p) __HYBRID_UNALIGNED_RECAST(p, \
	sizeof(*(p)) <= 1 ? __hybrid_unaligned_get8_swap(p) : \
	sizeof(*(p)) <= 2 ? __hybrid_unaligned_get16_swap(p) : \
	sizeof(*(p)) <= 4 ? __hybrid_unaligned_get32_swap(p) : \
	sizeof(*(p)) <= 8 ? __hybrid_unaligned_get64_swap(p) : \
	                    __hybrid_unaligned_get128_swap(p))
#elif defined(__UINT64_TYPE__)
#define __hybrid_unaligned_get_swap(p) __HYBRID_UNALIGNED_RECAST(p, \
	sizeof(*(p)) <= 1 ? __hybrid_unaligned_get8_swap(p) : \
	sizeof(*(p)) <= 2 ? __hybrid_unaligned_get16_swap(p) : \
	sizeof(*(p)) <= 4 ? __hybrid_unaligned_get32_swap(p) : \
	                    __hybrid_unaligned_get64_swap(p))
#else /* ... */
#define __hybrid_unaligned_get_swap(p) __HYBRID_UNALIGNED_RECAST(p, \
	sizeof(*(p)) <= 1 ? __hybrid_unaligned_get8_swap(p) : \
	sizeof(*(p)) <= 2 ? __hybrid_unaligned_get16_swap(p) : \
	                    __hybrid_unaligned_get32_swap(p))
#endif /* !... */
#endif /* ... */
#endif /* !__hybrid_unaligned_get_swap */
/* clang-format on */

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define __hybrid_unaligned_getle   __hybrid_unaligned_get
#define __hybrid_unaligned_setle   __hybrid_unaligned_set
#define __hybrid_unaligned_getbe   __hybrid_unaligned_get_swap
#define __hybrid_unaligned_setbe   __hybrid_unaligned_set_swap
#define __hybrid_unaligned_getle16 __hybrid_unaligned_get16
#define __hybrid_unaligned_setle16 __hybrid_unaligned_set16
#define __hybrid_unaligned_getbe16 __hybrid_unaligned_get16_swap
#define __hybrid_unaligned_setbe16 __hybrid_unaligned_set16_swap
#define __hybrid_unaligned_getle32 __hybrid_unaligned_get32
#define __hybrid_unaligned_setle32 __hybrid_unaligned_set32
#define __hybrid_unaligned_getbe32 __hybrid_unaligned_get32_swap
#define __hybrid_unaligned_setbe32 __hybrid_unaligned_set32_swap
#ifdef __UINT64_TYPE__
#define __hybrid_unaligned_getle64 __hybrid_unaligned_get64
#define __hybrid_unaligned_getbe64 __hybrid_unaligned_get64_swap
#define __hybrid_unaligned_setle64 __hybrid_unaligned_set64
#define __hybrid_unaligned_setbe64 __hybrid_unaligned_set64_swap
#ifdef __UINT128_TYPE__
#define __hybrid_unaligned_getle128 __hybrid_unaligned_get128
#define __hybrid_unaligned_getbe128 __hybrid_unaligned_get128_swap
#define __hybrid_unaligned_setle128 __hybrid_unaligned_set128
#define __hybrid_unaligned_setbe128 __hybrid_unaligned_set128_swap
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __hybrid_unaligned_getle   __hybrid_unaligned_get_swap
#define __hybrid_unaligned_setle   __hybrid_unaligned_set_swap
#define __hybrid_unaligned_getbe   __hybrid_unaligned_get
#define __hybrid_unaligned_setbe   __hybrid_unaligned_set
#define __hybrid_unaligned_getle16 __hybrid_unaligned_get16_swap
#define __hybrid_unaligned_setle16 __hybrid_unaligned_set16_swap
#define __hybrid_unaligned_getbe16 __hybrid_unaligned_get16
#define __hybrid_unaligned_setbe16 __hybrid_unaligned_set16
#define __hybrid_unaligned_getle32 __hybrid_unaligned_get32_swap
#define __hybrid_unaligned_setle32 __hybrid_unaligned_set32_swap
#define __hybrid_unaligned_getbe32 __hybrid_unaligned_get32
#define __hybrid_unaligned_setbe32 __hybrid_unaligned_set32
#ifdef __UINT64_TYPE__
#define __hybrid_unaligned_getle64 __hybrid_unaligned_get64_swap
#define __hybrid_unaligned_getbe64 __hybrid_unaligned_get64
#define __hybrid_unaligned_setle64 __hybrid_unaligned_set64_swap
#define __hybrid_unaligned_setbe64 __hybrid_unaligned_set64
#ifdef __UINT128_TYPE__
#define __hybrid_unaligned_getle128 __hybrid_unaligned_get128_swap
#define __hybrid_unaligned_getbe128 __hybrid_unaligned_get128
#define __hybrid_unaligned_setle128 __hybrid_unaligned_set128_swap
#define __hybrid_unaligned_setbe128 __hybrid_unaligned_set128
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#endif /* ... */

__DECL_END
#endif /* __CC__ */

#endif /* !__GUARD_HYBRID___UNALIGNED_H */
