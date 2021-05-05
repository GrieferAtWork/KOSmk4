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
#ifndef __GUARD_HYBRID___UNALIGNED_H
#define __GUARD_HYBRID___UNALIGNED_H 1

#include "../__stdinc.h"
#include "typecore.h"
#include "host.h"
#include "__debug-alignment.h"

__DECL_BEGIN

#ifdef __cplusplus
#define __IMPL_HYBRID_UNALIGNED_GETTER(n)      __hybrid_unaligned_get
#define __IMPL_HYBRID_UNALIGNED_SETTER(n)      __hybrid_unaligned_set
#define __IMPL_HYBRID_UNALIGNED_GETTER_SWAP(n) __hybrid_unaligned_get_swap
#define __IMPL_HYBRID_UNALIGNED_SETTER_SWAP(n) __hybrid_unaligned_set_swap
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__
__NOTHROW_NCX(__hybrid_unaligned_get)(__UINT8_TYPE__ const *__restrict __ptr) {
	return *__ptr;
}
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__
__NOTHROW_NCX(__hybrid_unaligned_get_swap)(__UINT8_TYPE__ const *__restrict __ptr) {
	return *__ptr;
}
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__hybrid_unaligned_set)(__UINT8_TYPE__ *__restrict __ptr, __UINT8_TYPE__ __val) {
	*__ptr = __val;
}
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__hybrid_unaligned_set_swap)(__UINT8_TYPE__ *__restrict __ptr, __UINT8_TYPE__ __val) {
	*__ptr = __val;
}
#else /* __cplusplus */
#define __IMPL_HYBRID_UNALIGNED_GETTER(n)      __hybrid_unaligned_get##n
#define __IMPL_HYBRID_UNALIGNED_SETTER(n)      __hybrid_unaligned_set##n
#define __IMPL_HYBRID_UNALIGNED_GETTER_SWAP(n) __hybrid_unaligned_get##n##_swap
#define __IMPL_HYBRID_UNALIGNED_SETTER_SWAP(n) __hybrid_unaligned_set##n##_swap
#endif /* !__cplusplus */

#if (defined(__i386__) || defined(__x86_64__)) && 1
#ifndef __NO_hybrid_dbg_alignment
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER(16))(__UINT16_TYPE__ const *__restrict __ptr) {
	__UINT16_TYPE__ __res;
	__hybrid_dbg_alignment_disable();
	__res = *__ptr;
	__hybrid_dbg_alignment_enable();
	return __res;
}
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER(16))(__UINT16_TYPE__ *__restrict __ptr, __UINT16_TYPE__ __val) {
	__hybrid_dbg_alignment_disable();
	*__ptr = __val;
	__hybrid_dbg_alignment_enable();
}
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER(32))(__UINT32_TYPE__ const *__restrict __ptr) {
	__UINT32_TYPE__ __res;
	__hybrid_dbg_alignment_disable();
	__res = *__ptr;
	__hybrid_dbg_alignment_enable();
	return __res;
}
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER(32))(__UINT32_TYPE__ *__restrict __ptr, __UINT32_TYPE__ __val) {
	__hybrid_dbg_alignment_disable();
	*__ptr = __val;
	__hybrid_dbg_alignment_enable();
}
#ifdef __UINT64_TYPE__
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER(64))(__UINT64_TYPE__ const *__restrict __ptr) {
	__UINT64_TYPE__ __res;
	__hybrid_dbg_alignment_disable();
	__res = *__ptr;
	__hybrid_dbg_alignment_enable();
	return __res;
}
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER(64))(__UINT64_TYPE__ *__restrict __ptr, __UINT64_TYPE__ __val) {
	__hybrid_dbg_alignment_disable();
	*__ptr = __val;
	__hybrid_dbg_alignment_enable();
}
#ifdef __UINT128_TYPE__
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER(128))(__UINT128_TYPE__ const *__restrict __ptr) {
	__UINT128_TYPE__ __res;
	__hybrid_dbg_alignment_disable();
	__res = *__ptr;
	__hybrid_dbg_alignment_enable();
	return __res;
}
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER(128))(__UINT128_TYPE__ *__restrict __ptr, __UINT128_TYPE__ __val) {
	__hybrid_dbg_alignment_disable();
	*__ptr = __val;
	__hybrid_dbg_alignment_enable();
}
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#elif defined(__cplusplus)
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER(16))(__UINT16_TYPE__ const *__restrict __ptr) {
	return *__ptr;
}
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER(16))(__UINT16_TYPE__ *__restrict __ptr, __UINT16_TYPE__ __val) {
	*__ptr = __val;
}
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER(32))(__UINT32_TYPE__ const *__restrict __ptr) {
	return *__ptr;
}
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER(32))(__UINT32_TYPE__ *__restrict __ptr, __UINT32_TYPE__ __val) {
	*__ptr = __val;
}
#ifdef __UINT64_TYPE__
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER(64))(__UINT64_TYPE__ const *__restrict __ptr) {
	return *__ptr;
}
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER(64))(__UINT64_TYPE__ *__restrict __ptr, __UINT64_TYPE__ __val) {
	*__ptr = __val;
}
#ifdef __UINT128_TYPE__
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER(128))(__UINT128_TYPE__ const *__restrict __ptr) {
	return *__ptr;
}
__FORCELOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER(128))(__UINT128_TYPE__ *__restrict __ptr, __UINT128_TYPE__ __val) {
	*__ptr = __val;
}
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#else /* __cplusplus */
#define __hybrid_unaligned_get16(ptr)    (*(__UINT16_TYPE__ *)(ptr))
#define __hybrid_unaligned_set16(ptr,v)  (void)(*(__UINT16_TYPE__ *)(ptr)=(__UINT16_TYPE__)(v))
#define __hybrid_unaligned_get32(ptr)    (*(__UINT32_TYPE__ *)(ptr))
#define __hybrid_unaligned_set32(ptr,v)  (void)(*(__UINT32_TYPE__ *)(ptr)=(__UINT32_TYPE__)(v))
#ifdef __UINT64_TYPE__
#define __hybrid_unaligned_get64(ptr)    (*(__UINT64_TYPE__ *)(ptr))
#define __hybrid_unaligned_set64(ptr,v)  (void)(*(__UINT64_TYPE__ *)(ptr)=(__UINT64_TYPE__)(v))
#ifdef __UINT128_TYPE__
#define __hybrid_unaligned_get128(ptr)   (*(__UINT128_TYPE__ *)(ptr))
#define __hybrid_unaligned_set128(ptr,v) (void)(*(__UINT128_TYPE__ *)(ptr)=(__UINT128_TYPE__)(v))
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#endif /* !__cplusplus */
#elif defined(__ARMCC_VERSION) || defined(__CC_ARM)
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER(16))(__UINT16_TYPE__ const *__restrict __ptr) {
	return *(__packed __UINT16_TYPE__ const *)__ptr;
}
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER(16))(__UINT16_TYPE__ *__restrict __ptr, __UINT16_TYPE__ __val) {
	*(__packed __UINT16_TYPE__ *)__ptr = __val;
}
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER(32))(__UINT32_TYPE__ const *__restrict __ptr) {
	return *(__packed __UINT32_TYPE__ const *)__ptr;
}
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER(32))(__UINT32_TYPE__ *__restrict __ptr, __UINT32_TYPE__ __val) {
	*(__packed __UINT32_TYPE__ *)__ptr = __val;
}
#ifdef __UINT64_TYPE__
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER(64))(__UINT64_TYPE__ const *__restrict __ptr) {
	return *(__packed __UINT64_TYPE__ const *)__ptr;
}
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER(64))(__UINT64_TYPE__ *__restrict __ptr, __UINT64_TYPE__ __val) {
	*(__packed __UINT64_TYPE__ *)__ptr = __val;
}
#ifdef __UINT128_TYPE__
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER(128))(__UINT128_TYPE__ const *__restrict __ptr) {
	return *(__packed __UINT128_TYPE__ const *)__ptr;
}
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER(128))(__UINT128_TYPE__ *__restrict __ptr, __UINT128_TYPE__ __val) {
	*(__packed __UINT128_TYPE__ *)__ptr = __val;
}
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#elif !defined(__NO_ATTR_PACKED)
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER(16))(__UINT16_TYPE__ const *__restrict __ptr) {
	struct __ATTR_PACKED __unaligned_ptr16 { __UINT16_TYPE__ __val; };
	return ((struct __unaligned_ptr16 const *)__ptr)->__val;
}
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER(16))(__UINT16_TYPE__ *__restrict __ptr, __UINT16_TYPE__ __val) {
	struct __ATTR_PACKED __unaligned_ptr16 { __UINT16_TYPE__ __val; };
	((struct __unaligned_ptr16 *)__ptr)->__val = __val;
}
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER(32))(__UINT32_TYPE__ const *__restrict __ptr) {
	struct __ATTR_PACKED __unaligned_ptr32 { __UINT32_TYPE__ __val; };
	return ((struct __unaligned_ptr32 const *)__ptr)->__val;
}
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER(32))(__UINT32_TYPE__ *__restrict __ptr, __UINT32_TYPE__ __val) {
	struct __ATTR_PACKED __unaligned_ptr32 { __UINT32_TYPE__ __val; };
	((struct __unaligned_ptr32 *)__ptr)->__val = __val;
}
#ifdef __UINT64_TYPE__
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER(64))(__UINT64_TYPE__ const *__restrict __ptr) {
	struct __ATTR_PACKED __unaligned_ptr64 { __UINT64_TYPE__ __val; };
	return ((struct __unaligned_ptr64 const *)__ptr)->__val;
}
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER(64))(__UINT64_TYPE__ *__restrict __ptr, __UINT64_TYPE__ __val) {
	struct __ATTR_PACKED __unaligned_ptr64 { __UINT64_TYPE__ __val; };
	((struct __unaligned_ptr64 *)__ptr)->__val = __val;
}
#ifdef __UINT128_TYPE__
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER(128))(__UINT128_TYPE__ const *__restrict __ptr) {
	struct __ATTR_PACKED __unaligned_ptr128 { __UINT128_TYPE__ __val; };
	return ((struct __unaligned_ptr128 const *)__ptr)->__val;
}
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER(128))(__UINT128_TYPE__ *__restrict __ptr, __UINT128_TYPE__ __val) {
	struct __ATTR_PACKED __unaligned_ptr128 { __UINT128_TYPE__ __val; };
	((struct __unaligned_ptr128 *)__ptr)->__val = __val;
}
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#else
#ifdef __cplusplus
}
#endif /* __cplusplus */
#include "__byteswap.h"
#ifdef __cplusplus
extern "C++" {
#endif /* __cplusplus */
#define __IMPL_HYBRID_UNALIGNED_HAVE_SWAPPED 1
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER(16))(__UINT16_TYPE__ const *__restrict __ptr) {
	union {
		__UINT16_TYPE__ __v16;
		__UINT8_TYPE__ __v8[2];
	} __res;
	if (!((__UINTPTR_TYPE__)__ptr & 1))
		return *__ptr;
	__res.__v8[0] = ((__UINT8_TYPE__ const *)__ptr)[0];
	__res.__v8[1] = ((__UINT8_TYPE__ const *)__ptr)[1];
	return __res.__v16;
}
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER(16))(__UINT16_TYPE__ *__restrict __ptr, __UINT16_TYPE__ __val) {
	union {
		__UINT16_TYPE__ __v16;
		__UINT8_TYPE__ __v8[2];
	} __res;
	if (!((__UINTPTR_TYPE__)__ptr & 1)) {
		*__ptr = __val;
	} else {
		__res.__v16 = __val;
		((__UINT8_TYPE__ *)__ptr)[0] = __res.__v8[0];
		((__UINT8_TYPE__ *)__ptr)[1] = __res.__v8[1];
	}
}
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER_SWAP(16))(__UINT16_TYPE__ const *__restrict __ptr) {
	union {
		__UINT16_TYPE__ __v16;
		__UINT8_TYPE__ __v8[2];
	} __res;
	if (!((__UINTPTR_TYPE__)__ptr & 1))
		return __hybrid_bswap16(*__ptr);
	__res.__v8[1] = ((__UINT8_TYPE__ const *)__ptr)[0];
	__res.__v8[0] = ((__UINT8_TYPE__ const *)__ptr)[1];
	return __res.__v16;
}
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER_SWAP(16))(__UINT16_TYPE__ *__restrict __ptr, __UINT16_TYPE__ __val) {
	union {
		__UINT16_TYPE__ __v16;
		__UINT8_TYPE__ __v8[2];
	} __res;
	if (!((__UINTPTR_TYPE__)__ptr & 1)) {
		*__ptr = __hybrid_bswap16(__val);
	} else {
		__res.__v16 = __val;
		((__UINT8_TYPE__ *)__ptr)[0] = __res.__v8[1];
		((__UINT8_TYPE__ *)__ptr)[1] = __res.__v8[0];
	}
}
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER(32))(__UINT32_TYPE__ const *__restrict __ptr) {
	union {
		__UINT32_TYPE__ __v32;
		__UINT16_TYPE__ __v16[2];
		__UINT8_TYPE__  __v8[4];
	} __res;
	if (!((__UINTPTR_TYPE__)__ptr & 3))
		return *__ptr;
	if (!((__UINTPTR_TYPE__)__ptr & 1)) {
		__res.__v16[0] = ((__UINT16_TYPE__ const *)__ptr)[0];
		__res.__v16[1] = ((__UINT16_TYPE__ const *)__ptr)[1];
	} else {
		__res.__v8[0] = ((__UINT8_TYPE__ const *)__ptr)[0];
		__res.__v8[1] = ((__UINT8_TYPE__ const *)__ptr)[1];
		__res.__v8[2] = ((__UINT8_TYPE__ const *)__ptr)[2];
		__res.__v8[3] = ((__UINT8_TYPE__ const *)__ptr)[3];
	}
	return __res.__v32;
}
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER(32))(__UINT32_TYPE__ *__restrict __ptr, __UINT32_TYPE__ __val) {
	union {
		__UINT32_TYPE__ __v32;
		__UINT16_TYPE__ __v16[2];
		__UINT8_TYPE__  __v8[4];
	} __res;
	if (!((__UINTPTR_TYPE__)__ptr & 3)) {
		*__ptr = __val;
	} else {
		__res.__v32 = __val;
		if (!((__UINTPTR_TYPE__)__ptr & 1)) {
			((__UINT16_TYPE__ *)__ptr)[0] = __res.__v16[0];
			((__UINT16_TYPE__ *)__ptr)[1] = __res.__v16[1];
		} else {
			((__UINT8_TYPE__ *)__ptr)[0] = __res.__v8[0];
			((__UINT8_TYPE__ *)__ptr)[1] = __res.__v8[1];
			((__UINT8_TYPE__ *)__ptr)[2] = __res.__v8[2];
			((__UINT8_TYPE__ *)__ptr)[3] = __res.__v8[3];
		}
	}
}
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER_SWAP(32))(__UINT32_TYPE__ const *__restrict __ptr) {
	union {
		__UINT32_TYPE__ __v32;
		__UINT16_TYPE__ __v16[2];
		__UINT8_TYPE__  __v8[4];
	} __res;
	if (!((__UINTPTR_TYPE__)__ptr & 3))
		return __hybrid_bswap32(*__ptr);
	if (!((__UINTPTR_TYPE__)__ptr & 1)) {
		__res.__v16[1] = __hybrid_bswap16(((__UINT16_TYPE__ const *)__ptr)[0]);
		__res.__v16[0] = __hybrid_bswap16(((__UINT16_TYPE__ const *)__ptr)[1]);
	} else {
		__res.__v8[3] = ((__UINT8_TYPE__ const *)__ptr)[0];
		__res.__v8[2] = ((__UINT8_TYPE__ const *)__ptr)[1];
		__res.__v8[1] = ((__UINT8_TYPE__ const *)__ptr)[2];
		__res.__v8[0] = ((__UINT8_TYPE__ const *)__ptr)[3];
	}
	return __res.__v32;
}
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER_SWAP(32))(__UINT32_TYPE__ *__restrict __ptr, __UINT32_TYPE__ __val) {
	union {
		__UINT32_TYPE__ __v32;
		__UINT16_TYPE__ __v16[2];
		__UINT8_TYPE__  __v8[4];
	} __res;
	if (!((__UINTPTR_TYPE__)__ptr & 3)) {
		*__ptr = __hybrid_bswap32(__val);
	} else {
		__res.__v32 = __val;
		if (!((__UINTPTR_TYPE__)__ptr & 1)) {
			((__UINT16_TYPE__ *)__ptr)[0] = __hybrid_bswap16(__res.__v16[1]);
			((__UINT16_TYPE__ *)__ptr)[1] = __hybrid_bswap16(__res.__v16[0]);
		} else {
			((__UINT8_TYPE__ *)__ptr)[0] = __res.__v8[3];
			((__UINT8_TYPE__ *)__ptr)[1] = __res.__v8[2];
			((__UINT8_TYPE__ *)__ptr)[2] = __res.__v8[1];
			((__UINT8_TYPE__ *)__ptr)[3] = __res.__v8[0];
		}
	}
}
#ifdef __UINT64_TYPE__
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER(64))(__UINT64_TYPE__ const *__restrict __ptr) {
	union {
		__UINT64_TYPE__ __v64;
		__UINT32_TYPE__ __v32[2];
		__UINT16_TYPE__ __v16[4];
		__UINT8_TYPE__  __v8[8];
	} __res;
	if (!((__UINTPTR_TYPE__)__ptr & 7))
		return *__ptr;
	if (!((__UINTPTR_TYPE__)__ptr & 3)) {
		__res.__v32[0] = ((__UINT32_TYPE__ const *)__ptr)[0];
		__res.__v32[1] = ((__UINT32_TYPE__ const *)__ptr)[1];
	} else if (!((__UINTPTR_TYPE__)__ptr & 1)) {
		__res.__v16[0] = ((__UINT16_TYPE__ const *)__ptr)[0];
		__res.__v16[1] = ((__UINT16_TYPE__ const *)__ptr)[1];
		__res.__v16[2] = ((__UINT16_TYPE__ const *)__ptr)[2];
		__res.__v16[3] = ((__UINT16_TYPE__ const *)__ptr)[3];
	} else {
		__res.__v8[0] = ((__UINT8_TYPE__ const *)__ptr)[0];
		__res.__v8[1] = ((__UINT8_TYPE__ const *)__ptr)[1];
		__res.__v8[2] = ((__UINT8_TYPE__ const *)__ptr)[2];
		__res.__v8[3] = ((__UINT8_TYPE__ const *)__ptr)[3];
		__res.__v8[4] = ((__UINT8_TYPE__ const *)__ptr)[4];
		__res.__v8[5] = ((__UINT8_TYPE__ const *)__ptr)[5];
		__res.__v8[6] = ((__UINT8_TYPE__ const *)__ptr)[6];
		__res.__v8[7] = ((__UINT8_TYPE__ const *)__ptr)[7];
	}
	return __res.__v64;
}
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER(64))(__UINT64_TYPE__ *__restrict __ptr, __UINT64_TYPE__ __val) {
	union {
		__UINT64_TYPE__ __v64;
		__UINT32_TYPE__ __v32[2];
		__UINT16_TYPE__ __v16[4];
		__UINT8_TYPE__  __v8[8];
	} __res;
	if (!((__UINTPTR_TYPE__)__ptr & 7)) {
		*__ptr = __val;
	} else {
		__res.__v64 = __val;
		if (!((__UINTPTR_TYPE__)__ptr & 3)) {
			((__UINT32_TYPE__ *)__ptr)[0] = __res.__v32[0];
			((__UINT32_TYPE__ *)__ptr)[1] = __res.__v32[1];
		} else if (!((__UINTPTR_TYPE__)__ptr & 1)) {
			((__UINT16_TYPE__ *)__ptr)[0] = __res.__v16[0];
			((__UINT16_TYPE__ *)__ptr)[1] = __res.__v16[1];
			((__UINT16_TYPE__ *)__ptr)[2] = __res.__v16[2];
			((__UINT16_TYPE__ *)__ptr)[3] = __res.__v16[3];
		} else {
			((__UINT8_TYPE__ *)__ptr)[0] = __res.__v8[0];
			((__UINT8_TYPE__ *)__ptr)[1] = __res.__v8[1];
			((__UINT8_TYPE__ *)__ptr)[2] = __res.__v8[2];
			((__UINT8_TYPE__ *)__ptr)[3] = __res.__v8[3];
			((__UINT8_TYPE__ *)__ptr)[4] = __res.__v8[4];
			((__UINT8_TYPE__ *)__ptr)[5] = __res.__v8[5];
			((__UINT8_TYPE__ *)__ptr)[6] = __res.__v8[6];
			((__UINT8_TYPE__ *)__ptr)[7] = __res.__v8[7];
		}
	}
}
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER_SWAP(64))(__UINT64_TYPE__ const *__restrict __ptr) {
	union {
		__UINT64_TYPE__ __v64;
		__UINT32_TYPE__ __v32[2];
		__UINT16_TYPE__ __v16[4];
		__UINT8_TYPE__  __v8[8];
	} __res;
	if (!((__UINTPTR_TYPE__)__ptr & 7))
		return __hybrid_bswap64(*__ptr);
	if (!((__UINTPTR_TYPE__)__ptr & 3)) {
		__res.__v32[1] = __hybrid_bswap32(((__UINT32_TYPE__ const *)__ptr)[0]);
		__res.__v32[0] = __hybrid_bswap32(((__UINT32_TYPE__ const *)__ptr)[1]);
	} else if (!((__UINTPTR_TYPE__)__ptr & 1)) {
		__res.__v16[3] = __hybrid_bswap16(((__UINT16_TYPE__ const *)__ptr)[0]);
		__res.__v16[2] = __hybrid_bswap16(((__UINT16_TYPE__ const *)__ptr)[1]);
		__res.__v16[1] = __hybrid_bswap16(((__UINT16_TYPE__ const *)__ptr)[2]);
		__res.__v16[0] = __hybrid_bswap16(((__UINT16_TYPE__ const *)__ptr)[3]);
	} else {
		__res.__v8[7] = ((__UINT8_TYPE__ const *)__ptr)[0];
		__res.__v8[6] = ((__UINT8_TYPE__ const *)__ptr)[1];
		__res.__v8[5] = ((__UINT8_TYPE__ const *)__ptr)[2];
		__res.__v8[4] = ((__UINT8_TYPE__ const *)__ptr)[3];
		__res.__v8[3] = ((__UINT8_TYPE__ const *)__ptr)[4];
		__res.__v8[2] = ((__UINT8_TYPE__ const *)__ptr)[5];
		__res.__v8[1] = ((__UINT8_TYPE__ const *)__ptr)[6];
		__res.__v8[0] = ((__UINT8_TYPE__ const *)__ptr)[7];
	}
	return __res.__v64;
}
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER_SWAP(64))(__UINT64_TYPE__ *__restrict __ptr, __UINT64_TYPE__ __val) {
	union {
		__UINT64_TYPE__ __v64;
		__UINT32_TYPE__ __v32[2];
		__UINT16_TYPE__ __v16[4];
		__UINT8_TYPE__  __v8[8];
	} __res;
	if (!((__UINTPTR_TYPE__)__ptr & 7)) {
		*__ptr = __hybrid_bswap64(__val);
	} else {
		__res.__v64 = __val;
		if (!((__UINTPTR_TYPE__)__ptr & 3)) {
			((__UINT32_TYPE__ *)__ptr)[0] = __hybrid_bswap32(__res.__v32[1]);
			((__UINT32_TYPE__ *)__ptr)[1] = __hybrid_bswap32(__res.__v32[0]);
		} else if (!((__UINTPTR_TYPE__)__ptr & 1)) {
			((__UINT16_TYPE__ *)__ptr)[0] = __hybrid_bswap16(__res.__v16[3]);
			((__UINT16_TYPE__ *)__ptr)[1] = __hybrid_bswap16(__res.__v16[2]);
			((__UINT16_TYPE__ *)__ptr)[2] = __hybrid_bswap16(__res.__v16[1]);
			((__UINT16_TYPE__ *)__ptr)[3] = __hybrid_bswap16(__res.__v16[0]);
		} else {
			((__UINT8_TYPE__ *)__ptr)[7] = __res.__v8[0];
			((__UINT8_TYPE__ *)__ptr)[6] = __res.__v8[1];
			((__UINT8_TYPE__ *)__ptr)[5] = __res.__v8[2];
			((__UINT8_TYPE__ *)__ptr)[4] = __res.__v8[3];
			((__UINT8_TYPE__ *)__ptr)[3] = __res.__v8[4];
			((__UINT8_TYPE__ *)__ptr)[2] = __res.__v8[5];
			((__UINT8_TYPE__ *)__ptr)[1] = __res.__v8[6];
			((__UINT8_TYPE__ *)__ptr)[0] = __res.__v8[7];
		}
	}
}
#ifdef __UINT128_TYPE__
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER(128))(__UINT128_TYPE__ const *__restrict __ptr) {
	union {
		__UINT128_TYPE__ __v128;
		__UINT64_TYPE__  __v64[2];
		__UINT32_TYPE__  __v32[4];
		__UINT16_TYPE__  __v16[8];
		__UINT8_TYPE__   __v8[16];
	} __res;
	if (!((__UINTPTR_TYPE__)__ptr & 15))
		return *__ptr;
	if (!((__UINTPTR_TYPE__)__ptr & 7)) {
		__res.__v64[0] = ((__UINT64_TYPE__ const *)__ptr)[0];
		__res.__v64[1] = ((__UINT64_TYPE__ const *)__ptr)[1];
	} else if (!((__UINTPTR_TYPE__)__ptr & 3)) {
		__res.__v32[0] = ((__UINT32_TYPE__ const *)__ptr)[0];
		__res.__v32[1] = ((__UINT32_TYPE__ const *)__ptr)[1];
		__res.__v32[2] = ((__UINT32_TYPE__ const *)__ptr)[2];
		__res.__v32[3] = ((__UINT32_TYPE__ const *)__ptr)[3];
	} else if (!((__UINTPTR_TYPE__)__ptr & 1)) {
		__res.__v16[0] = ((__UINT16_TYPE__ const *)__ptr)[0];
		__res.__v16[1] = ((__UINT16_TYPE__ const *)__ptr)[1];
		__res.__v16[2] = ((__UINT16_TYPE__ const *)__ptr)[2];
		__res.__v16[3] = ((__UINT16_TYPE__ const *)__ptr)[3];
		__res.__v16[4] = ((__UINT16_TYPE__ const *)__ptr)[4];
		__res.__v16[5] = ((__UINT16_TYPE__ const *)__ptr)[5];
		__res.__v16[6] = ((__UINT16_TYPE__ const *)__ptr)[6];
		__res.__v16[7] = ((__UINT16_TYPE__ const *)__ptr)[7];
	} else {
		__res.__v8[0x0] = ((__UINT8_TYPE__ const *)__ptr)[0x0];
		__res.__v8[0x1] = ((__UINT8_TYPE__ const *)__ptr)[0x1];
		__res.__v8[0x2] = ((__UINT8_TYPE__ const *)__ptr)[0x2];
		__res.__v8[0x3] = ((__UINT8_TYPE__ const *)__ptr)[0x3];
		__res.__v8[0x4] = ((__UINT8_TYPE__ const *)__ptr)[0x4];
		__res.__v8[0x5] = ((__UINT8_TYPE__ const *)__ptr)[0x5];
		__res.__v8[0x6] = ((__UINT8_TYPE__ const *)__ptr)[0x6];
		__res.__v8[0x7] = ((__UINT8_TYPE__ const *)__ptr)[0x7];
		__res.__v8[0x8] = ((__UINT8_TYPE__ const *)__ptr)[0x8];
		__res.__v8[0x9] = ((__UINT8_TYPE__ const *)__ptr)[0x9];
		__res.__v8[0xa] = ((__UINT8_TYPE__ const *)__ptr)[0xa];
		__res.__v8[0xb] = ((__UINT8_TYPE__ const *)__ptr)[0xb];
		__res.__v8[0xc] = ((__UINT8_TYPE__ const *)__ptr)[0xc];
		__res.__v8[0xd] = ((__UINT8_TYPE__ const *)__ptr)[0xd];
		__res.__v8[0xe] = ((__UINT8_TYPE__ const *)__ptr)[0xe];
		__res.__v8[0xf] = ((__UINT8_TYPE__ const *)__ptr)[0xf];
	}
	return __res.__v128;
}
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER(128))(__UINT128_TYPE__ const *__restrict __ptr, __UINT128_TYPE__ __val) {
	union {
		__UINT128_TYPE__ __v128;
		__UINT64_TYPE__  __v64[2];
		__UINT32_TYPE__  __v32[4];
		__UINT16_TYPE__  __v16[8];
		__UINT8_TYPE__   __v8[16];
	} __res;
	if (!((__UINTPTR_TYPE__)__ptr & 15)) {
		*__ptr = __val;
	} else {
		__res.__v128 = __val;
		if (!((__UINTPTR_TYPE__)__ptr & 7)) {
			((__UINT64_TYPE__ *)__ptr)[0] = __res.__v64[0];
			((__UINT64_TYPE__ *)__ptr)[1] = __res.__v64[1];
		} else if (!((__UINTPTR_TYPE__)__ptr & 3)) {
			((__UINT32_TYPE__ *)__ptr)[0] = __res.__v32[0];
			((__UINT32_TYPE__ *)__ptr)[1] = __res.__v32[1];
			((__UINT32_TYPE__ *)__ptr)[2] = __res.__v32[2];
			((__UINT32_TYPE__ *)__ptr)[3] = __res.__v32[3];
		} else if (!((__UINTPTR_TYPE__)__ptr & 1)) {
			((__UINT16_TYPE__ *)__ptr)[0] = __res.__v16[0];
			((__UINT16_TYPE__ *)__ptr)[1] = __res.__v16[1];
			((__UINT16_TYPE__ *)__ptr)[2] = __res.__v16[2];
			((__UINT16_TYPE__ *)__ptr)[3] = __res.__v16[3];
			((__UINT16_TYPE__ *)__ptr)[4] = __res.__v16[4];
			((__UINT16_TYPE__ *)__ptr)[5] = __res.__v16[5];
			((__UINT16_TYPE__ *)__ptr)[6] = __res.__v16[6];
			((__UINT16_TYPE__ *)__ptr)[7] = __res.__v16[7];
		} else {
			((__UINT8_TYPE__ *)__ptr)[0x0] = __res.__v8[0x0];
			((__UINT8_TYPE__ *)__ptr)[0x1] = __res.__v8[0x1];
			((__UINT8_TYPE__ *)__ptr)[0x2] = __res.__v8[0x2];
			((__UINT8_TYPE__ *)__ptr)[0x3] = __res.__v8[0x3];
			((__UINT8_TYPE__ *)__ptr)[0x4] = __res.__v8[0x4];
			((__UINT8_TYPE__ *)__ptr)[0x5] = __res.__v8[0x5];
			((__UINT8_TYPE__ *)__ptr)[0x6] = __res.__v8[0x6];
			((__UINT8_TYPE__ *)__ptr)[0x7] = __res.__v8[0x7];
			((__UINT8_TYPE__ *)__ptr)[0x8] = __res.__v8[0x8];
			((__UINT8_TYPE__ *)__ptr)[0x9] = __res.__v8[0x9];
			((__UINT8_TYPE__ *)__ptr)[0xa] = __res.__v8[0xa];
			((__UINT8_TYPE__ *)__ptr)[0xb] = __res.__v8[0xb];
			((__UINT8_TYPE__ *)__ptr)[0xc] = __res.__v8[0xc];
			((__UINT8_TYPE__ *)__ptr)[0xd] = __res.__v8[0xd];
			((__UINT8_TYPE__ *)__ptr)[0xe] = __res.__v8[0xe];
			((__UINT8_TYPE__ *)__ptr)[0xf] = __res.__v8[0xf];
		}
	}
}
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER_SWAP(128))(__UINT128_TYPE__ const *__restrict __ptr) {
	union {
		__UINT128_TYPE__ __v128;
		__UINT64_TYPE__  __v64[2];
		__UINT32_TYPE__  __v32[4];
		__UINT16_TYPE__  __v16[8];
		__UINT8_TYPE__   __v8[16];
	} __res;
	if (!((__UINTPTR_TYPE__)__ptr & 15))
		return *__ptr;
	if (!((__UINTPTR_TYPE__)__ptr & 7)) {
		__res.__v64[1] = __hybrid_bswap64(((__UINT64_TYPE__ const *)__ptr)[0]);
		__res.__v64[0] = __hybrid_bswap64(((__UINT64_TYPE__ const *)__ptr)[1]);
	} else if (!((__UINTPTR_TYPE__)__ptr & 3)) {
		__res.__v32[3] = __hybrid_bswap32(((__UINT32_TYPE__ const *)__ptr)[0]);
		__res.__v32[2] = __hybrid_bswap32(((__UINT32_TYPE__ const *)__ptr)[1]);
		__res.__v32[1] = __hybrid_bswap32(((__UINT32_TYPE__ const *)__ptr)[2]);
		__res.__v32[0] = __hybrid_bswap32(((__UINT32_TYPE__ const *)__ptr)[3]);
	} else if (!((__UINTPTR_TYPE__)__ptr & 1)) {
		__res.__v16[7] = __hybrid_bswap16(((__UINT16_TYPE__ const *)__ptr)[0]);
		__res.__v16[6] = __hybrid_bswap16(((__UINT16_TYPE__ const *)__ptr)[1]);
		__res.__v16[5] = __hybrid_bswap16(((__UINT16_TYPE__ const *)__ptr)[2]);
		__res.__v16[4] = __hybrid_bswap16(((__UINT16_TYPE__ const *)__ptr)[3]);
		__res.__v16[3] = __hybrid_bswap16(((__UINT16_TYPE__ const *)__ptr)[4]);
		__res.__v16[2] = __hybrid_bswap16(((__UINT16_TYPE__ const *)__ptr)[5]);
		__res.__v16[1] = __hybrid_bswap16(((__UINT16_TYPE__ const *)__ptr)[6]);
		__res.__v16[0] = __hybrid_bswap16(((__UINT16_TYPE__ const *)__ptr)[7]);
	} else {
		__res.__v8[0xf] = ((__UINT8_TYPE__ const *)__ptr)[0x0];
		__res.__v8[0xe] = ((__UINT8_TYPE__ const *)__ptr)[0x1];
		__res.__v8[0xd] = ((__UINT8_TYPE__ const *)__ptr)[0x2];
		__res.__v8[0xc] = ((__UINT8_TYPE__ const *)__ptr)[0x3];
		__res.__v8[0xb] = ((__UINT8_TYPE__ const *)__ptr)[0x4];
		__res.__v8[0xa] = ((__UINT8_TYPE__ const *)__ptr)[0x5];
		__res.__v8[0x9] = ((__UINT8_TYPE__ const *)__ptr)[0x6];
		__res.__v8[0x8] = ((__UINT8_TYPE__ const *)__ptr)[0x7];
		__res.__v8[0x7] = ((__UINT8_TYPE__ const *)__ptr)[0x8];
		__res.__v8[0x6] = ((__UINT8_TYPE__ const *)__ptr)[0x9];
		__res.__v8[0x5] = ((__UINT8_TYPE__ const *)__ptr)[0xa];
		__res.__v8[0x4] = ((__UINT8_TYPE__ const *)__ptr)[0xb];
		__res.__v8[0x3] = ((__UINT8_TYPE__ const *)__ptr)[0xc];
		__res.__v8[0x2] = ((__UINT8_TYPE__ const *)__ptr)[0xd];
		__res.__v8[0x1] = ((__UINT8_TYPE__ const *)__ptr)[0xe];
		__res.__v8[0x0] = ((__UINT8_TYPE__ const *)__ptr)[0xf];
	}
	return __res.__v128;
}
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER_SWAP(128))(__UINT128_TYPE__ const *__restrict __ptr, __UINT128_TYPE__ __val) {
	union {
		__UINT128_TYPE__ __v128;
		__UINT64_TYPE__  __v64[2];
		__UINT32_TYPE__  __v32[4];
		__UINT16_TYPE__  __v16[8];
		__UINT8_TYPE__   __v8[16];
	} __res;
	if (!((__UINTPTR_TYPE__)__ptr & 15)) {
		*__ptr = __hybrid_bswap128(__val);
	} else {
		__res.__v128 = __val;
		if (!((__UINTPTR_TYPE__)__ptr & 7)) {
			((__UINT64_TYPE__ *)__ptr)[0] = __hybrid_bswap64(__res.__v64[1]);
			((__UINT64_TYPE__ *)__ptr)[1] = __hybrid_bswap64(__res.__v64[0]);
		} else if (!((__UINTPTR_TYPE__)__ptr & 3)) {
			((__UINT32_TYPE__ *)__ptr)[0] = __hybrid_bswap32(__res.__v32[3]);
			((__UINT32_TYPE__ *)__ptr)[1] = __hybrid_bswap32(__res.__v32[2]);
			((__UINT32_TYPE__ *)__ptr)[2] = __hybrid_bswap32(__res.__v32[1]);
			((__UINT32_TYPE__ *)__ptr)[3] = __hybrid_bswap32(__res.__v32[0]);
		} else if (!((__UINTPTR_TYPE__)__ptr & 1)) {
			((__UINT16_TYPE__ *)__ptr)[0] = __hybrid_bswap16(__res.__v16[7]);
			((__UINT16_TYPE__ *)__ptr)[1] = __hybrid_bswap16(__res.__v16[6]);
			((__UINT16_TYPE__ *)__ptr)[2] = __hybrid_bswap16(__res.__v16[5]);
			((__UINT16_TYPE__ *)__ptr)[3] = __hybrid_bswap16(__res.__v16[4]);
			((__UINT16_TYPE__ *)__ptr)[4] = __hybrid_bswap16(__res.__v16[3]);
			((__UINT16_TYPE__ *)__ptr)[5] = __hybrid_bswap16(__res.__v16[2]);
			((__UINT16_TYPE__ *)__ptr)[6] = __hybrid_bswap16(__res.__v16[1]);
			((__UINT16_TYPE__ *)__ptr)[7] = __hybrid_bswap16(__res.__v16[0]);
		} else {
			((__UINT8_TYPE__ *)__ptr)[0x0] = __res.__v8[0xf];
			((__UINT8_TYPE__ *)__ptr)[0x1] = __res.__v8[0xe];
			((__UINT8_TYPE__ *)__ptr)[0x2] = __res.__v8[0xd];
			((__UINT8_TYPE__ *)__ptr)[0x3] = __res.__v8[0xc];
			((__UINT8_TYPE__ *)__ptr)[0x4] = __res.__v8[0xb];
			((__UINT8_TYPE__ *)__ptr)[0x5] = __res.__v8[0xa];
			((__UINT8_TYPE__ *)__ptr)[0x6] = __res.__v8[0x9];
			((__UINT8_TYPE__ *)__ptr)[0x7] = __res.__v8[0x8];
			((__UINT8_TYPE__ *)__ptr)[0x8] = __res.__v8[0x7];
			((__UINT8_TYPE__ *)__ptr)[0x9] = __res.__v8[0x6];
			((__UINT8_TYPE__ *)__ptr)[0xa] = __res.__v8[0x5];
			((__UINT8_TYPE__ *)__ptr)[0xb] = __res.__v8[0x4];
			((__UINT8_TYPE__ *)__ptr)[0xc] = __res.__v8[0x3];
			((__UINT8_TYPE__ *)__ptr)[0xd] = __res.__v8[0x2];
			((__UINT8_TYPE__ *)__ptr)[0xe] = __res.__v8[0x1];
			((__UINT8_TYPE__ *)__ptr)[0xf] = __res.__v8[0x0];
		}
	}
}
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#endif /* ... */

#ifdef __IMPL_HYBRID_UNALIGNED_HAVE_SWAPPED
#undef __IMPL_HYBRID_UNALIGNED_HAVE_SWAPPED
#else /* __IMPL_HYBRID_UNALIGNED_HAVE_SWAPPED */
#include "__byteswap.h"
#ifdef __cplusplus
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER_SWAP(16))(__UINT16_TYPE__ const *__restrict __ptr) {
	return __hybrid_bswap16(__IMPL_HYBRID_UNALIGNED_GETTER(16)(__ptr));
}
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER_SWAP(16))(__UINT16_TYPE__ *__restrict __ptr, __UINT16_TYPE__ __val) {
	__IMPL_HYBRID_UNALIGNED_SETTER(16)(__ptr,__hybrid_bswap16(__val));
}
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER_SWAP(32))(__UINT32_TYPE__ const *__restrict __ptr) {
	return __hybrid_bswap32(__IMPL_HYBRID_UNALIGNED_GETTER(32)(__ptr));
}
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER_SWAP(32))(__UINT32_TYPE__ *__restrict __ptr, __UINT32_TYPE__ __val) {
	__IMPL_HYBRID_UNALIGNED_SETTER(32)(__ptr,__hybrid_bswap32(__val));
}
#ifdef __UINT64_TYPE__
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER_SWAP(64))(__UINT64_TYPE__ const *__restrict __ptr) {
	return __hybrid_bswap64(__IMPL_HYBRID_UNALIGNED_GETTER(64)(__ptr));
}
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER_SWAP(64))(__UINT64_TYPE__ *__restrict __ptr, __UINT64_TYPE__ __val) {
	__IMPL_HYBRID_UNALIGNED_SETTER(64)(__ptr,__hybrid_bswap64(__val));
}
#ifdef __UINT128_TYPE__
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_GETTER_SWAP(128))(__UINT128_TYPE__ const *__restrict __ptr) {
	return __hybrid_bswap128(__IMPL_HYBRID_UNALIGNED_GETTER(128)(__ptr));
}
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__IMPL_HYBRID_UNALIGNED_SETTER_SWAP(128))(__UINT128_TYPE__ *__restrict __ptr, __UINT128_TYPE__ __val) {
	__IMPL_HYBRID_UNALIGNED_SETTER(128)(__ptr,__hybrid_bswap128(__val));
}
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#else /* __cplusplus */
#define __hybrid_unaligned_get16_swap(ptr)    __hybrid_bswap16(__hybrid_unaligned_get16(ptr))
#define __hybrid_unaligned_set16_swap(ptr, v) __hybrid_unaligned_set16(ptr, __hybrid_bswap16(v))
#define __hybrid_unaligned_get32_swap(ptr)    __hybrid_bswap32(__hybrid_unaligned_get32(ptr))
#define __hybrid_unaligned_set32_swap(ptr, v) __hybrid_unaligned_set32(ptr, __hybrid_bswap32(v))
#ifdef __UINT64_TYPE__
#define __hybrid_unaligned_get64_swap(ptr)    __hybrid_bswap64(__hybrid_unaligned_get64(ptr))
#define __hybrid_unaligned_set64_swap(ptr, v) __hybrid_unaligned_set64(ptr, __hybrid_bswap64(v))
#ifdef __UINT128_TYPE__
#define __hybrid_unaligned_get128_swap(ptr)    __hybrid_bswap128(__hybrid_unaligned_get128(ptr))
#define __hybrid_unaligned_set128_swap(ptr, v) __hybrid_unaligned_set128(ptr, __hybrid_bswap128(v))
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#endif /* !__cplusplus */
#endif /* !__IMPL_HYBRID_UNALIGNED_HAVE_SWAPPED */

#undef __IMPL_HYBRID_UNALIGNED_GETTER
#undef __IMPL_HYBRID_UNALIGNED_SETTER
#undef __IMPL_HYBRID_UNALIGNED_GETTER_SWAP
#undef __IMPL_HYBRID_UNALIGNED_SETTER_SWAP
#ifdef __cplusplus

#ifdef __UFIFTHINT_TYPE__
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_TYPE__
__NOTHROW_NCX(__hybrid_unaligned_get)(__UFIFTHINT_TYPE__ const *__restrict __ptr) {
	return __hybrid_unaligned_get((__UFIFTHINT_ALIAS_TYPE__ const *)__ptr);
}
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UFIFTHINT_TYPE__
__NOTHROW_NCX(__hybrid_unaligned_get_swap)(__UFIFTHINT_TYPE__ const *__restrict __ptr) {
	return __hybrid_unaligned_get_swap((__UFIFTHINT_ALIAS_TYPE__ const *)__ptr);
}
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__hybrid_unaligned_set)(__UFIFTHINT_TYPE__ *__restrict __ptr, __UFIFTHINT_TYPE__ __val) {
	__hybrid_unaligned_set((__UFIFTHINT_ALIAS_TYPE__ *)__ptr, (__UFIFTHINT_ALIAS_TYPE__)__val);
}
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__hybrid_unaligned_set_swap)(__UFIFTHINT_TYPE__ *__restrict __ptr, __UFIFTHINT_TYPE__ __val) {
	__hybrid_unaligned_set_swap((__UFIFTHINT_ALIAS_TYPE__ *)__ptr, (__UFIFTHINT_ALIAS_TYPE__)__val);
}
#endif /* __UFIFTHINT_TYPE__ */
} /* extern "C++" */

#ifdef __INTELLISENSE__
extern "C++" { namespace __intern {
void *____intellisense_reqptr(void *);
void const *____intellisense_reqcptr(void const *);
} }
#define __hybrid_unaligned_get16(ptr)         (*(__UINT16_TYPE__ const *)::__intern::____intellisense_reqcptr(ptr))
#define __hybrid_unaligned_get16_swap(ptr)    (*(__UINT16_TYPE__ const *)::__intern::____intellisense_reqcptr(ptr))
#define __hybrid_unaligned_set16(ptr, v)      (void)(*(__UINT16_TYPE__ *)::__intern::____intellisense_reqptr(ptr) = (__UINT16_TYPE__)(v))
#define __hybrid_unaligned_set16_swap(ptr, v) (void)(*(__UINT16_TYPE__ *)::__intern::____intellisense_reqptr(ptr) = (__UINT16_TYPE__)(v))
#define __hybrid_unaligned_get32(ptr)         (*(__UINT32_TYPE__ const *)::__intern::____intellisense_reqcptr(ptr))
#define __hybrid_unaligned_get32_swap(ptr)    (*(__UINT32_TYPE__ const *)::__intern::____intellisense_reqcptr(ptr))
#define __hybrid_unaligned_set32(ptr, v)      (void)(*(__UINT32_TYPE__ *)::__intern::____intellisense_reqptr(ptr) = (__UINT32_TYPE__)(v))
#define __hybrid_unaligned_set32_swap(ptr, v) (void)(*(__UINT32_TYPE__ *)::__intern::____intellisense_reqptr(ptr) = (__UINT32_TYPE__)(v))
#ifdef __UINT64_TYPE__
#define __hybrid_unaligned_get64(ptr)         (*(__UINT64_TYPE__ const *)::__intern::____intellisense_reqcptr(ptr))
#define __hybrid_unaligned_get64_swap(ptr)    (*(__UINT64_TYPE__ const *)::__intern::____intellisense_reqcptr(ptr))
#define __hybrid_unaligned_set64(ptr, v)      (void)(*(__UINT64_TYPE__ *)::__intern::____intellisense_reqptr(ptr) = (__UINT64_TYPE__)(v))
#define __hybrid_unaligned_set64_swap(ptr, v) (void)(*(__UINT64_TYPE__ *)::__intern::____intellisense_reqptr(ptr) = (__UINT64_TYPE__)(v))
#ifdef __UINT128_TYPE__
#define __hybrid_unaligned_get128(ptr)         (*(__UINT128_TYPE__ const *)::__intern::____intellisense_reqcptr(ptr))
#define __hybrid_unaligned_get128_swap(ptr)    (*(__UINT128_TYPE__ const *)::__intern::____intellisense_reqcptr(ptr))
#define __hybrid_unaligned_set128(ptr, v)      (void)(*(__UINT128_TYPE__ *)::__intern::____intellisense_reqptr(ptr) = (__UINT128_TYPE__)(v))
#define __hybrid_unaligned_set128_swap(ptr, v) (void)(*(__UINT128_TYPE__ *)::__intern::____intellisense_reqptr(ptr) = (__UINT128_TYPE__)(v))
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#else  /* __INTELLISENSE__ */
#define __hybrid_unaligned_get16(ptr)         __hybrid_unaligned_get((__UINT16_TYPE__ const *)(ptr))
#define __hybrid_unaligned_set16(ptr, v)      __hybrid_unaligned_set((__UINT16_TYPE__ *)(ptr), v)
#define __hybrid_unaligned_get16_swap(ptr)    __hybrid_unaligned_get_swap((__UINT16_TYPE__ const *)(ptr))
#define __hybrid_unaligned_set16_swap(ptr, v) __hybrid_unaligned_set_swap((__UINT16_TYPE__ *)(ptr), v)
#define __hybrid_unaligned_get32(ptr)         __hybrid_unaligned_get((__UINT32_TYPE__ const *)(ptr))
#define __hybrid_unaligned_set32(ptr, v)      __hybrid_unaligned_set((__UINT32_TYPE__ *)(ptr), v)
#define __hybrid_unaligned_get32_swap(ptr)    __hybrid_unaligned_get_swap((__UINT32_TYPE__ const *)(ptr))
#define __hybrid_unaligned_set32_swap(ptr, v) __hybrid_unaligned_set_swap((__UINT32_TYPE__ *)(ptr), v)
#ifdef __UINT64_TYPE__
#define __hybrid_unaligned_get64(ptr)         __hybrid_unaligned_get((__UINT64_TYPE__ const *)(ptr))
#define __hybrid_unaligned_set64(ptr, v)      __hybrid_unaligned_set((__UINT64_TYPE__ *)(ptr), v)
#define __hybrid_unaligned_get64_swap(ptr)    __hybrid_unaligned_get_swap((__UINT64_TYPE__ const *)(ptr))
#define __hybrid_unaligned_set64_swap(ptr, v) __hybrid_unaligned_set_swap((__UINT64_TYPE__ *)(ptr), v)
#ifdef __UINT128_TYPE__
#define __hybrid_unaligned_get128(ptr)         __hybrid_unaligned_get((__UINT128_TYPE__ const *)(ptr))
#define __hybrid_unaligned_set128(ptr, v)      __hybrid_unaligned_set((__UINT128_TYPE__ *)(ptr), v)
#define __hybrid_unaligned_get128_swap(ptr)    __hybrid_unaligned_get_swap((__UINT128_TYPE__ const *)(ptr))
#define __hybrid_unaligned_set128_swap(ptr, v) __hybrid_unaligned_set_swap((__UINT128_TYPE__ *)(ptr), v)
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#endif /* !__INTELLISENSE__ */

#endif /* __cplusplus */

#ifndef __cplusplus
#ifndef __NO_builtin_choose_expr
#ifndef __UINT64_TYPE__
#define __hybrid_unaligned_get(ptr)                                                                      \
	__builtin_choose_expr(sizeof(*(ptr)) == 1, *(__UINT8_TYPE__ const *)(ptr),                           \
	__builtin_choose_expr(sizeof(*(ptr)) == 2, __hybrid_unaligned_get16((__UINT16_TYPE__ const *)(ptr)), \
	                                           __hybrid_unaligned_get32((__UINT32_TYPE__ const *)(ptr))))
#define __hybrid_unaligned_set(ptr, v)                                                                                  \
	__builtin_choose_expr(sizeof(*(ptr)) == 1, (void)(*(__UINT8_TYPE__ *)(ptr) = (__UINT8_TYPE__)(v)),                  \
	__builtin_choose_expr(sizeof(*(ptr)) == 2, __hybrid_unaligned_set16((__UINT16_TYPE__ *)(ptr), (__UINT8_TYPE__)(v)), \
	                                           __hybrid_unaligned_set32((__UINT32_TYPE__ *)(ptr), (__UINT16_TYPE__)(v))))
#define __hybrid_unaligned_get_swap(ptr)                                                                      \
	__builtin_choose_expr(sizeof(*(ptr)) == 1, *(__UINT8_TYPE__ const *)(ptr),                                \
	__builtin_choose_expr(sizeof(*(ptr)) == 2, __hybrid_unaligned_get16_swap((__UINT16_TYPE__ const *)(ptr)), \
	                                           __hybrid_unaligned_get32_swap((__UINT32_TYPE__ const *)(ptr))))
#define __hybrid_unaligned_set_swap(ptr, v)                                                                                  \
	__builtin_choose_expr(sizeof(*(ptr)) == 1, (void)(*(__UINT8_TYPE__ *)(ptr) = (__UINT8_TYPE__)(v)),                       \
	__builtin_choose_expr(sizeof(*(ptr)) == 2, __hybrid_unaligned_set16_swap((__UINT16_TYPE__ *)(ptr), (__UINT8_TYPE__)(v)), \
	                                           __hybrid_unaligned_set32_swap((__UINT32_TYPE__ *)(ptr), (__UINT16_TYPE__)(v))))
#elif !defined(__UINT128_TYPE__) /* 64-bit integer type */
#define __hybrid_unaligned_get(ptr)                                                                      \
	__builtin_choose_expr(sizeof(*(ptr)) == 1, *(__UINT8_TYPE__ const *)(ptr),                           \
	__builtin_choose_expr(sizeof(*(ptr)) == 2, __hybrid_unaligned_get16((__UINT16_TYPE__ const *)(ptr)), \
	__builtin_choose_expr(sizeof(*(ptr)) == 4, __hybrid_unaligned_get32((__UINT32_TYPE__ const *)(ptr)), \
	                                           __hybrid_unaligned_get64((__UINT64_TYPE__ const *)(ptr)))))
#define __hybrid_unaligned_set(ptr, v)                                                                                   \
	__builtin_choose_expr(sizeof(*(ptr)) == 1, (void)(*(__UINT8_TYPE__ *)(ptr) = (__UINT8_TYPE__)(v)),                   \
	__builtin_choose_expr(sizeof(*(ptr)) == 2, __hybrid_unaligned_set16((__UINT16_TYPE__ *)(ptr), (__UINT16_TYPE__)(v)), \
	__builtin_choose_expr(sizeof(*(ptr)) == 4, __hybrid_unaligned_set32((__UINT32_TYPE__ *)(ptr), (__UINT32_TYPE__)(v)), \
	                                           __hybrid_unaligned_set64((__UINT64_TYPE__ *)(ptr), (__UINT64_TYPE__)(v)))))
#define __hybrid_unaligned_get_swap(ptr)                                                                      \
	__builtin_choose_expr(sizeof(*(ptr)) == 1, *(__UINT8_TYPE__ const *)(ptr),                                \
	__builtin_choose_expr(sizeof(*(ptr)) == 2, __hybrid_unaligned_get16_swap((__UINT16_TYPE__ const *)(ptr)), \
	__builtin_choose_expr(sizeof(*(ptr)) == 4, __hybrid_unaligned_get32_swap((__UINT32_TYPE__ const *)(ptr)), \
	                                           __hybrid_unaligned_get64_swap((__UINT64_TYPE__ const *)(ptr)))))
#define __hybrid_unaligned_set_swap(ptr, v)                                                                                   \
	__builtin_choose_expr(sizeof(*(ptr)) == 1, (void)(*(__UINT8_TYPE__ *)(ptr) = (__UINT8_TYPE__)(v)),                        \
	__builtin_choose_expr(sizeof(*(ptr)) == 2, __hybrid_unaligned_set16_swap((__UINT16_TYPE__ *)(ptr), (__UINT16_TYPE__)(v)), \
	__builtin_choose_expr(sizeof(*(ptr)) == 4, __hybrid_unaligned_set32_swap((__UINT32_TYPE__ *)(ptr), (__UINT32_TYPE__)(v)), \
	                                           __hybrid_unaligned_set64_swap((__UINT64_TYPE__ *)(ptr), (__UINT64_TYPE__)(v)))))
#else /* 128-bit integer type */
#define __hybrid_unaligned_get(ptr)                                                                      \
	__builtin_choose_expr(sizeof(*(ptr)) == 1, *(__UINT8_TYPE__ const *)(ptr),                           \
	__builtin_choose_expr(sizeof(*(ptr)) == 2, __hybrid_unaligned_get16((__UINT16_TYPE__ const *)(ptr)), \
	__builtin_choose_expr(sizeof(*(ptr)) == 4, __hybrid_unaligned_get32((__UINT32_TYPE__ const *)(ptr)), \
	__builtin_choose_expr(sizeof(*(ptr)) == 8, __hybrid_unaligned_get64((__UINT64_TYPE__ const *)(ptr)), \
	                                           __hybrid_unaligned_get128((__UINT128_TYPE__ const *)(ptr))))))
#define __hybrid_unaligned_set(ptr, v)                                                                                   \
	__builtin_choose_expr(sizeof(*(ptr)) == 1, (void)(*(__UINT8_TYPE__ *)(ptr) = (__UINT8_TYPE__)(v)),                   \
	__builtin_choose_expr(sizeof(*(ptr)) == 2, __hybrid_unaligned_set16((__UINT16_TYPE__ *)(ptr), (__UINT16_TYPE__)(v)), \
	__builtin_choose_expr(sizeof(*(ptr)) == 4, __hybrid_unaligned_set32((__UINT32_TYPE__ *)(ptr), (__UINT32_TYPE__)(v)), \
	__builtin_choose_expr(sizeof(*(ptr)) == 8, __hybrid_unaligned_set64((__UINT64_TYPE__ *)(ptr), (__UINT64_TYPE__)(v)), \
	                                           __hybrid_unaligned_set128((__UINT128_TYPE__ *)(ptr), (__UINT128_TYPE__)(v))))))
#define __hybrid_unaligned_get_swap(ptr)                                                                      \
	__builtin_choose_expr(sizeof(*(ptr)) == 1, *(__UINT8_TYPE__ const *)(ptr),                                \
	__builtin_choose_expr(sizeof(*(ptr)) == 2, __hybrid_unaligned_get16_swap((__UINT16_TYPE__ const *)(ptr)), \
	__builtin_choose_expr(sizeof(*(ptr)) == 4, __hybrid_unaligned_get32_swap((__UINT32_TYPE__ const *)(ptr)), \
	__builtin_choose_expr(sizeof(*(ptr)) == 8, __hybrid_unaligned_get64_swap((__UINT64_TYPE__ const *)(ptr)), \
	                                           __hybrid_unaligned_get128_swap((__UINT128_TYPE__ const *)(ptr))))))
#define __hybrid_unaligned_set_swap(ptr, v)                                                                                   \
	__builtin_choose_expr(sizeof(*(ptr)) == 1, (void)(*(__UINT8_TYPE__ *)(ptr) = (__UINT8_TYPE__)(v)),                        \
	__builtin_choose_expr(sizeof(*(ptr)) == 2, __hybrid_unaligned_set16_swap((__UINT16_TYPE__ *)(ptr), (__UINT16_TYPE__)(v)), \
	__builtin_choose_expr(sizeof(*(ptr)) == 4, __hybrid_unaligned_set32_swap((__UINT32_TYPE__ *)(ptr), (__UINT32_TYPE__)(v)), \
	__builtin_choose_expr(sizeof(*(ptr)) == 8, __hybrid_unaligned_set64_swap((__UINT64_TYPE__ *)(ptr), (__UINT64_TYPE__)(v)), \
	                                           __hybrid_unaligned_set128_swap((__UINT128_TYPE__ *)(ptr), (__UINT128_TYPE__)(v))))))
#endif
#else /* !__NO_builtin_choose_expr */
#ifndef __UINT64_TYPE__
#define __hybrid_unaligned_get(ptr)                                                   \
	(sizeof(*(ptr)) == 1 ? *(__UINT8_TYPE__ const *)(ptr) :                           \
	 sizeof(*(ptr)) == 2 ? __hybrid_unaligned_get16((__UINT16_TYPE__ const *)(ptr)) : \
	                       __hybrid_unaligned_get32((__UINT32_TYPE__ const *)(ptr)))
#define __hybrid_unaligned_set(ptr, v)                                                               \
	(sizeof(*(ptr)) == 1 ? (void)(*(__UINT8_TYPE__ *)(ptr) = (__UINT8_TYPE__)(v)) :                  \
	 sizeof(*(ptr)) == 2 ? __hybrid_unaligned_set16((__UINT16_TYPE__ *)(ptr), (__UINT8_TYPE__)(v)) : \
	                       __hybrid_unaligned_set32((__UINT32_TYPE__ *)(ptr), (__UINT16_TYPE__)(v)))
#define __hybrid_unaligned_get_swap(ptr)                                                   \
	(sizeof(*(ptr)) == 1 ? *(__UINT8_TYPE__ const *)(ptr) :                                \
	 sizeof(*(ptr)) == 2 ? __hybrid_unaligned_get16_swap((__UINT16_TYPE__ const *)(ptr)) : \
	                       __hybrid_unaligned_get32_swap((__UINT32_TYPE__ const *)(ptr)))
#define __hybrid_unaligned_set_swap(ptr, v)                                                               \
	(sizeof(*(ptr)) == 1 ? (void)(*(__UINT8_TYPE__ *)(ptr) = (__UINT8_TYPE__)(v)) :                       \
	 sizeof(*(ptr)) == 2 ? __hybrid_unaligned_set16_swap((__UINT16_TYPE__ *)(ptr), (__UINT8_TYPE__)(v)) : \
	                       __hybrid_unaligned_set32_swap((__UINT32_TYPE__ *)(ptr), (__UINT16_TYPE__)(v)))
#elif !defined(__UINT128_TYPE__) /* 64-bit integer type */
#define __hybrid_unaligned_get(ptr)                                                   \
	(sizeof(*(ptr)) == 1 ? *(__UINT8_TYPE__ const *)(ptr) :                           \
	 sizeof(*(ptr)) == 2 ? __hybrid_unaligned_get16((__UINT16_TYPE__ const *)(ptr)) : \
	 sizeof(*(ptr)) == 4 ? __hybrid_unaligned_get32((__UINT32_TYPE__ const *)(ptr)) : \
	                       __hybrid_unaligned_get64((__UINT64_TYPE__ const *)(ptr)))
#define __hybrid_unaligned_set(ptr, v)                                                                \
	(sizeof(*(ptr)) == 1 ? (void)(*(__UINT8_TYPE__ *)(ptr) = (__UINT8_TYPE__)(v)) :                   \
	 sizeof(*(ptr)) == 2 ? __hybrid_unaligned_set16((__UINT16_TYPE__ *)(ptr), (__UINT16_TYPE__)(v)) : \
	 sizeof(*(ptr)) == 4 ? __hybrid_unaligned_set32((__UINT32_TYPE__ *)(ptr), (__UINT32_TYPE__)(v)) : \
	                       __hybrid_unaligned_set64((__UINT64_TYPE__ *)(ptr), (__UINT64_TYPE__)(v)))
#define __hybrid_unaligned_get_swap(ptr)                                                   \
	(sizeof(*(ptr)) == 1 ? *(__UINT8_TYPE__ const *)(ptr) :                                \
	 sizeof(*(ptr)) == 2 ? __hybrid_unaligned_get16_swap((__UINT16_TYPE__ const *)(ptr)) : \
	 sizeof(*(ptr)) == 4 ? __hybrid_unaligned_get32_swap((__UINT32_TYPE__ const *)(ptr)) : \
	                       __hybrid_unaligned_get64_swap((__UINT64_TYPE__ const *)(ptr)))
#define __hybrid_unaligned_set_swap(ptr, v)                                                                \
	(sizeof(*(ptr)) == 1 ? (void)(*(__UINT8_TYPE__ *)(ptr) = (__UINT8_TYPE__)(v)) :                        \
	 sizeof(*(ptr)) == 2 ? __hybrid_unaligned_set16_swap((__UINT16_TYPE__ *)(ptr), (__UINT16_TYPE__)(v)) : \
	 sizeof(*(ptr)) == 4 ? __hybrid_unaligned_set32_swap((__UINT32_TYPE__ *)(ptr), (__UINT32_TYPE__)(v)) : \
	                       __hybrid_unaligned_set64_swap((__UINT64_TYPE__ *)(ptr), (__UINT64_TYPE__)(v)))
#else /* 128-bit integer type */
#define __hybrid_unaligned_get(ptr)                                                   \
	(sizeof(*(ptr)) == 1 ? *(__UINT8_TYPE__ const *)(ptr) :                           \
	 sizeof(*(ptr)) == 2 ? __hybrid_unaligned_get16((__UINT16_TYPE__ const *)(ptr)) : \
	 sizeof(*(ptr)) == 4 ? __hybrid_unaligned_get32((__UINT32_TYPE__ const *)(ptr)) : \
	 sizeof(*(ptr)) == 8 ? __hybrid_unaligned_get64((__UINT64_TYPE__ const *)(ptr)) : \
	                       __hybrid_unaligned_get128((__UINT128_TYPE__ const *)(ptr)))
#define __hybrid_unaligned_set(ptr, v)                                                                \
	(sizeof(*(ptr)) == 1 ? (void)(*(__UINT8_TYPE__ *)(ptr) = (__UINT8_TYPE__)(v)) :                   \
	 sizeof(*(ptr)) == 2 ? __hybrid_unaligned_set16((__UINT16_TYPE__ *)(ptr), (__UINT16_TYPE__)(v)) : \
	 sizeof(*(ptr)) == 4 ? __hybrid_unaligned_set32((__UINT32_TYPE__ *)(ptr), (__UINT32_TYPE__)(v)) : \
	 sizeof(*(ptr)) == 8 ? __hybrid_unaligned_set64((__UINT64_TYPE__ *)(ptr), (__UINT64_TYPE__)(v)) : \
	                       __hybrid_unaligned_set128((__UINT128_TYPE__ *)(ptr), (__UINT128_TYPE__)(v)))
#define __hybrid_unaligned_get_swap(ptr)                                                   \
	(sizeof(*(ptr)) == 1 ? *(__UINT8_TYPE__ const *)(ptr) :                                \
	 sizeof(*(ptr)) == 2 ? __hybrid_unaligned_get16_swap((__UINT16_TYPE__ const *)(ptr)) : \
	 sizeof(*(ptr)) == 4 ? __hybrid_unaligned_get32_swap((__UINT32_TYPE__ const *)(ptr)) : \
	 sizeof(*(ptr)) == 8 ? __hybrid_unaligned_get64_swap((__UINT64_TYPE__ const *)(ptr)) : \
	                       __hybrid_unaligned_get128_swap((__UINT128_TYPE__ const *)(ptr)))
#define __hybrid_unaligned_set_swap(ptr, v)                                                                \
	(sizeof(*(ptr)) == 1 ? (void)(*(__UINT8_TYPE__ *)(ptr) = (__UINT8_TYPE__)(v)) :                        \
	 sizeof(*(ptr)) == 2 ? __hybrid_unaligned_set16_swap((__UINT16_TYPE__ *)(ptr), (__UINT16_TYPE__)(v)) : \
	 sizeof(*(ptr)) == 4 ? __hybrid_unaligned_set32_swap((__UINT32_TYPE__ *)(ptr), (__UINT32_TYPE__)(v)) : \
	 sizeof(*(ptr)) == 8 ? __hybrid_unaligned_set64_swap((__UINT64_TYPE__ *)(ptr), (__UINT64_TYPE__)(v)) : \
	                       __hybrid_unaligned_set128_swap((__UINT128_TYPE__ *)(ptr), (__UINT128_TYPE__)(v)))
#endif
#endif /* __NO_builtin_choose_expr */
#endif /* !__cplusplus */


#include "byteorder.h"
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#ifdef __cplusplus
#define __hybrid_unaligned_getle   __hybrid_unaligned_get
#define __hybrid_unaligned_setle   __hybrid_unaligned_set
#define __hybrid_unaligned_getbe   __hybrid_unaligned_get_swap
#define __hybrid_unaligned_setbe   __hybrid_unaligned_set_swap
#endif /* __cplusplus */
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
#ifdef __cplusplus
#define __hybrid_unaligned_getle   __hybrid_unaligned_get_swap
#define __hybrid_unaligned_setle   __hybrid_unaligned_set_swap
#define __hybrid_unaligned_getbe   __hybrid_unaligned_get
#define __hybrid_unaligned_setbe   __hybrid_unaligned_set
#endif /* __cplusplus */
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

#endif /* !__GUARD_HYBRID___UNALIGNED_H */
