/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (>) Standard: ISO C23 (ISO/IEC 9899:2024) */
#ifndef _STDCKDINT_H
#define _STDCKDINT_H 1

#include "__stdinc.h"

#define __STDC_VERSION_STDCKDINT_H__ 202311L

#if ((__has_builtin(__builtin_add_overflow) && !defined(__ibmxl__)) || \
     (defined(__GNUC__) && (__GNUC__ >= 5) && !defined(__INTEL_COMPILER)))
#define ckd_add(r, a, b) ((__BOOL)__builtin_add_overflow(a, b, r))
#define ckd_sub(r, a, b) ((__BOOL)__builtin_sub_overflow(a, b, r))
#define ckd_mul(r, a, b) ((__BOOL)__builtin_mul_overflow(a, b, r))
#else /* __GNUC__... */
#include <hybrid/__overflow.h>
#include <hybrid/typecore.h>

/* Figure out some way of detecting if the type of a macro argument is signed... */
#ifdef __COMPILER_HAVE_C11_GENERIC
#ifdef __COMPILER_HAVE_LONGLONG
#define __PRIVATE_CDK_ISSIGNED_LL , long long: 1
#else /* __COMPILER_HAVE_LONGLONG */
#define __PRIVATE_CDK_ISSIGNED_LL /* nothing */
#endif /* !__COMPILER_HAVE_LONGLONG */
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
#define __PRIVATE_CDK_ISSIGNED_I8 , __int8: 1
#else /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#define __PRIVATE_CDK_ISSIGNED_I8 /* nothing */
#endif /* !__COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
#define __PRIVATE_CDK_ISSIGNED_I16 , __int16: 1
#else /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#define __PRIVATE_CDK_ISSIGNED_I16 /* nothing */
#endif /* !__COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
#define __PRIVATE_CDK_ISSIGNED_I32 , __int32: 1
#else /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#define __PRIVATE_CDK_ISSIGNED_I32 /* nothing */
#endif /* !__COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
#define __PRIVATE_CDK_ISSIGNED_I64 , __int64: 1
#else /* __COMPILER_INT64_IS_UNIQUE_TYPE */
#define __PRIVATE_CDK_ISSIGNED_I64 /* nothing */
#endif /* !__COMPILER_INT64_IS_UNIQUE_TYPE */
#ifdef __INT128_TYPE__
#define __PRIVATE_CDK_ISSIGNED_I128 , __INT128_TYPE__: 1
#else /* __INT128_TYPE__ */
#define __PRIVATE_CDK_ISSIGNED_I128 /* nothing */
#endif /* !__INT128_TYPE__ */
#define __PRIVATE_CDK_ISSIGNED(x) \
	_Generic((x), signed char: 1, short: 1, int: 1, long: 1 __PRIVATE_CDK_ISSIGNED_LL __PRIVATE_CDK_ISSIGNED_I8 __PRIVATE_CDK_ISSIGNED_I16 __PRIVATE_CDK_ISSIGNED_I32 __PRIVATE_CDK_ISSIGNED_I64 __PRIVATE_CDK_ISSIGNED_I128, default: 0)
#elif defined(__COMPILER_HAVE_TYPEOF) && !defined(__NO_builtin_types_compatible_p)
#ifdef __COMPILER_HAVE_LONGLONG
#define __PRIVATE_CDK_ISSIGNED_LL(T) || __builtin_types_compatible_p(T, long long)
#else /* __COMPILER_HAVE_LONGLONG */
#define __PRIVATE_CDK_ISSIGNED_LL(T) /* nothing */
#endif /* !__COMPILER_HAVE_LONGLONG */
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
#define __PRIVATE_CDK_ISSIGNED_I8(T) || __builtin_types_compatible_p(T, __int8)
#else /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#define __PRIVATE_CDK_ISSIGNED_I8(T) /* nothing */
#endif /* !__COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
#define __PRIVATE_CDK_ISSIGNED_I16(T) || __builtin_types_compatible_p(T, __int16)
#else /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#define __PRIVATE_CDK_ISSIGNED_I16(T) /* nothing */
#endif /* !__COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
#define __PRIVATE_CDK_ISSIGNED_I32(T) || __builtin_types_compatible_p(T, __int32)
#else /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#define __PRIVATE_CDK_ISSIGNED_I32(T) /* nothing */
#endif /* !__COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
#define __PRIVATE_CDK_ISSIGNED_I64(T) || __builtin_types_compatible_p(T, __int64)
#else /* __COMPILER_INT64_IS_UNIQUE_TYPE */
#define __PRIVATE_CDK_ISSIGNED_I64(T) /* nothing */
#endif /* !__COMPILER_INT64_IS_UNIQUE_TYPE */
#ifdef __INT128_TYPE__
#define __PRIVATE_CDK_ISSIGNED_I128(T) || __builtin_types_compatible_p(T, __INT128_TYPE__)
#else /* __INT128_TYPE__ */
#define __PRIVATE_CDK_ISSIGNED_I128(T) /* nothing */
#endif /* !__INT128_TYPE__ */
#define __PRIVATE_CDK_ISSIGNED_T(T)                  \
	(__builtin_types_compatible_p(T, signed char) || \
	 __builtin_types_compatible_p(T, short) ||       \
	 __builtin_types_compatible_p(T, int) ||         \
	 __builtin_types_compatible_p(T, long)           \
	 __PRIVATE_CDK_ISSIGNED_LL(T)                    \
	 __PRIVATE_CDK_ISSIGNED_I8(T)                    \
	 __PRIVATE_CDK_ISSIGNED_I16(T)                   \
	 __PRIVATE_CDK_ISSIGNED_I32(T)                   \
	 __PRIVATE_CDK_ISSIGNED_I64(T)                   \
	 __PRIVATE_CDK_ISSIGNED_I128(T))
#define __PRIVATE_CDK_ISSIGNED(x) __PRIVATE_CDK_ISSIGNED_T(__typeof__(x))
#elif !defined(__cplusplus)
#if 1 /* WARNING: This version incorrectly returns "true" for "signed char" and "short" */
#define __PRIVATE_CDK_ISSIGNED(x) ((0 ? (x) : -1) < 0 && (sizeof(x) >= __SIZEOF_INT__))
#else /* WARNING: This version incorrectly returns "true" for "unsigned char" and "unsigned short" */
#define __PRIVATE_CDK_ISSIGNED(x) ((0 ? (x) : -1) < 0)
#endif
#endif /* ... */

#ifdef __PRIVATE_CDK_ISSIGNED
#ifdef __NO_builtin_choose_expr
#define ckd_add(r, a, b) ((__BOOL)(__PRIVATE_CDK_ISSIGNED(*(r)) ? __hybrid_overflow_sadd(a, b, r) : __hybrid_overflow_uadd(a, b, r)))
#define ckd_sub(r, a, b) ((__BOOL)(__PRIVATE_CDK_ISSIGNED(*(r)) ? __hybrid_overflow_ssub(a, b, r) : __hybrid_overflow_usub(a, b, r)))
#define ckd_mul(r, a, b) ((__BOOL)(__PRIVATE_CDK_ISSIGNED(*(r)) ? __hybrid_overflow_smul(a, b, r) : __hybrid_overflow_umul(a, b, r)))
#else /* __NO_builtin_choose_expr */
#define ckd_add(r, a, b) ((__BOOL)__builtin_choose_expr(__PRIVATE_CDK_ISSIGNED(*(r)), __hybrid_overflow_sadd(a, b, r), __hybrid_overflow_uadd(a, b, r)))
#define ckd_sub(r, a, b) ((__BOOL)__builtin_choose_expr(__PRIVATE_CDK_ISSIGNED(*(r)), __hybrid_overflow_ssub(a, b, r), __hybrid_overflow_usub(a, b, r)))
#define ckd_mul(r, a, b) ((__BOOL)__builtin_choose_expr(__PRIVATE_CDK_ISSIGNED(*(r)), __hybrid_overflow_smul(a, b, r), __hybrid_overflow_umul(a, b, r)))
#endif /* !__NO_builtin_choose_expr */
#elif defined(__cplusplus)
#include "__stdcxx.h"
__CXXDECL_BEGIN
#undef ckd_add
#undef ckd_sub
#undef ckd_mul
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_add(signed char *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_sadd(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_sub(signed char *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_ssub(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_mul(signed char *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_smul(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_add(unsigned char *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_uadd(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_sub(unsigned char *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_usub(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_mul(unsigned char *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_umul(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_add(short *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_sadd(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_sub(short *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_ssub(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_mul(short *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_smul(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_add(unsigned short *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_uadd(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_sub(unsigned short *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_usub(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_mul(unsigned short *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_umul(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_add(int *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_sadd(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_sub(int *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_ssub(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_mul(int *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_smul(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_add(unsigned int *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_uadd(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_sub(unsigned int *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_usub(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_mul(unsigned int *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_umul(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_add(long *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_sadd(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_sub(long *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_ssub(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_mul(long *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_smul(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_add(unsigned long *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_uadd(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_sub(unsigned long *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_usub(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_mul(unsigned long *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_umul(__a, __b, __r); }
#ifdef __COMPILER_HAVE_LONGLONG
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_add(__LONGLONG *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_sadd(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_sub(__LONGLONG *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_ssub(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_mul(__LONGLONG *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_smul(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_add(__ULONGLONG *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_uadd(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_sub(__ULONGLONG *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_usub(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_mul(__ULONGLONG *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_umul(__a, __b, __r); }
#endif /* __COMPILER_HAVE_LONGLONG */
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_add(__int8 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_sadd(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_sub(__int8 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_ssub(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_mul(__int8 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_smul(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_add(unsigned __int8 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_uadd(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_sub(unsigned __int8 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_usub(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_mul(unsigned __int8 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_umul(__a, __b, __r); }
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_add(__int16 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_sadd(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_sub(__int16 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_ssub(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_mul(__int16 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_smul(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_add(unsigned __int16 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_uadd(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_sub(unsigned __int16 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_usub(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_mul(unsigned __int16 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_umul(__a, __b, __r); }
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_add(__int32 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_sadd(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_sub(__int32 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_ssub(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_mul(__int32 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_smul(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_add(unsigned __int32 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_uadd(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_sub(unsigned __int32 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_usub(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_mul(unsigned __int32 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_umul(__a, __b, __r); }
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_add(__int64 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_sadd(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_sub(__int64 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_ssub(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_mul(__int64 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_smul(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_add(unsigned __int64 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_uadd(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_sub(unsigned __int64 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_usub(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_mul(unsigned __int64 *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_umul(__a, __b, __r); }
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */
#ifdef __INT128_TYPE__
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_add(__INT128_TYPE__ *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_sadd(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_sub(__INT128_TYPE__ *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_ssub(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_mul(__INT128_TYPE__ *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_smul(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_add(__UINT128_TYPE__ *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_uadd(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_sub(__UINT128_TYPE__ *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_usub(__a, __b, __r); }
template<class __Ta, class __Tb> __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) __BOOL ckd_mul(__UINT128_TYPE__ *__r, __Ta __a, __Tb __b) { return __hybrid_overflow_umul(__a, __b, __r); }
#endif /* __INT128_TYPE__ */
#define ckd_add ckd_add
#define ckd_sub ckd_sub
#define ckd_mul ckd_mul
__CXXDECL_END
#else /* ... */
#error "No way to implement 'ckd_add', 'ckd_sub', 'ckd_mul'"
#endif /* !... */
#endif /* !__GNUC__... */

#endif /* !_STDCKDINT_H */
