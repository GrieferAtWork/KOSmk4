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
#ifndef __GUARD_HYBRID___OVERFLOW_H
#define __GUARD_HYBRID___OVERFLOW_H 1

#include "../__stdinc.h"
/**/

#include "__assert.h"
#include "typecore.h"

/* >> bool __hybrid_overflow_uadd(S lhs, U rhs, T *res);
 * >> bool __hybrid_overflow_sadd(S lhs, U rhs, T *res);
 * >> bool __hybrid_overflow_usub(S lhs, U rhs, T *res);
 * >> bool __hybrid_overflow_ssub(S lhs, U rhs, T *res);
 * >> bool __hybrid_overflow_umul(S lhs, U rhs, T *res);
 * >> bool __hybrid_overflow_smul(S lhs, U rhs, T *res);
 * @return: true:  Overflow  occurred (unlikely; `*res' contains the truncated result)
 *                 Overflow here means that the finite result stored in `*res' doesn't
 *                 match a value that would have been produced when infinite precision
 *                 was available.
 *                 e.g.: `UINT_MAX + 42u' and `11u - 19u' overflow, but `32u + 42u'
 *                       or `11 - 19' don't
 * @return: false: `*res' contains the correct result. */
#ifdef ____INTELLISENSE_STDINC_COMMON_H
#ifdef __cplusplus
#define __hybrid_overflow_uadd __intern::__intellisense_overflow_uadd
#define __hybrid_overflow_sadd __intern::__intellisense_overflow_sadd
#define __hybrid_overflow_usub __intern::__intellisense_overflow_usub
#define __hybrid_overflow_ssub __intern::__intellisense_overflow_ssub
#define __hybrid_overflow_umul __intern::__intellisense_overflow_umul
#define __hybrid_overflow_smul __intern::__intellisense_overflow_smul
#else /* __cplusplus */
#define __hybrid_overflow_uadd(x, y, res) __builtin_add_overflow(x, y, res)
#define __hybrid_overflow_sadd(x, y, res) __builtin_add_overflow(x, y, res)
#define __hybrid_overflow_usub(x, y, res) __builtin_sub_overflow(x, y, res)
#define __hybrid_overflow_ssub(x, y, res) __builtin_sub_overflow(x, y, res)
#define __hybrid_overflow_umul(x, y, res) __builtin_mul_overflow(x, y, res)
#define __hybrid_overflow_smul(x, y, res) __builtin_mul_overflow(x, y, res)
#endif /* !__cplusplus */
#elif ((__has_builtin(__builtin_add_overflow) && !defined(__ibmxl__)) || \
       (defined(__GNUC__) && (__GNUC__ >= 5) && !defined(__INTEL_COMPILER)))
#define __HYBRID_OVERFLOW_USES_BUILTINS
#ifdef __NO_builtin_expect
#define __hybrid_overflow_uadd __builtin_add_overflow
#define __hybrid_overflow_sadd __builtin_add_overflow
#define __hybrid_overflow_usub __builtin_sub_overflow
#define __hybrid_overflow_ssub __builtin_sub_overflow
#define __hybrid_overflow_umul __builtin_mul_overflow
#define __hybrid_overflow_smul __builtin_mul_overflow
#else /* __NO_builtin_expect */
#define __hybrid_overflow_uadd(x, y, res) __builtin_expect(__builtin_add_overflow(x, y, res), 0)
#define __hybrid_overflow_sadd(x, y, res) __builtin_expect(__builtin_add_overflow(x, y, res), 0)
#define __hybrid_overflow_usub(x, y, res) __builtin_expect(__builtin_sub_overflow(x, y, res), 0)
#define __hybrid_overflow_ssub(x, y, res) __builtin_expect(__builtin_sub_overflow(x, y, res), 0)
#define __hybrid_overflow_umul(x, y, res) __builtin_expect(__builtin_mul_overflow(x, y, res), 0)
#define __hybrid_overflow_smul(x, y, res) __builtin_expect(__builtin_mul_overflow(x, y, res), 0)
#endif /* !__NO_builtin_expect */
#else /* End:Builtin; Begin:Fallback */

/* Check for overflow via integer promotion */
#define __PRIVATE_HYBRID_DEFINE_PROMOTION_API(Nargbits, Nprombits, Nresbits)                                    \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                                         \
	(__PRIVATE_hybrid_overflow_uadd##Nargbits##_##Nresbits)(__UINT##Nargbits##_TYPE__ __lhs,                    \
	                                                        __UINT##Nargbits##_TYPE__ __rhs,                    \
	                                                        __UINT##Nresbits##_TYPE__ *__p_result) {            \
		__UINT##Nprombits##_TYPE__ __true_res = (__UINT##Nprombits##_TYPE__)__lhs +                             \
		                                        (__UINT##Nprombits##_TYPE__)__rhs;                              \
		return (__UINT##Nprombits##_TYPE__)(*__p_result = (__UINT##Nresbits##_TYPE__)__true_res) != __true_res; \
	}                                                                                                           \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                                         \
	(__PRIVATE_hybrid_overflow_sadd##Nargbits##_##Nresbits)(__INT##Nargbits##_TYPE__ __lhs,                     \
	                                                        __INT##Nargbits##_TYPE__ __rhs,                     \
	                                                        __INT##Nresbits##_TYPE__ *__p_result) {             \
		__INT##Nprombits##_TYPE__ __true_res = (__INT##Nprombits##_TYPE__)__lhs +                               \
		                                       (__INT##Nprombits##_TYPE__)__rhs;                                \
		return (__INT##Nprombits##_TYPE__)(*__p_result = (__INT##Nresbits##_TYPE__)__true_res) != __true_res;   \
	}                                                                                                           \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                                         \
	(__PRIVATE_hybrid_overflow_usub##Nargbits##_##Nresbits)(__UINT##Nargbits##_TYPE__ __lhs,                    \
	                                                        __UINT##Nargbits##_TYPE__ __rhs,                    \
	                                                        __UINT##Nresbits##_TYPE__ *__p_result) {            \
		__INT##Nprombits##_TYPE__ __true_res = (__INT##Nprombits##_TYPE__)__lhs -                               \
		                                       (__INT##Nprombits##_TYPE__)__rhs;                                \
		return (__INT##Nprombits##_TYPE__)(*__p_result = (__UINT##Nresbits##_TYPE__)__true_res) != __true_res;  \
	}                                                                                                           \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                                         \
	(__PRIVATE_hybrid_overflow_ssub##Nargbits##_##Nresbits)(__INT##Nargbits##_TYPE__ __lhs,                     \
	                                                        __INT##Nargbits##_TYPE__ __rhs,                     \
	                                                        __INT##Nresbits##_TYPE__ *__p_result) {             \
		__INT##Nprombits##_TYPE__ __true_res = (__INT##Nprombits##_TYPE__)__lhs -                               \
		                                       (__INT##Nprombits##_TYPE__)__rhs;                                \
		return (__INT##Nprombits##_TYPE__)(*__p_result = (__INT##Nresbits##_TYPE__)__true_res) != __true_res;   \
	}                                                                                                           \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                                         \
	(__PRIVATE_hybrid_overflow_umul##Nargbits##_##Nresbits)(__UINT##Nargbits##_TYPE__ __lhs,                    \
	                                                        __UINT##Nargbits##_TYPE__ __rhs,                    \
	                                                        __UINT##Nresbits##_TYPE__ *__p_result) {            \
		__UINT##Nprombits##_TYPE__ __true_res = (__UINT##Nprombits##_TYPE__)__lhs *                             \
		                                        (__UINT##Nprombits##_TYPE__)__rhs;                              \
		return (__UINT##Nprombits##_TYPE__)(*__p_result = (__UINT##Nresbits##_TYPE__)__true_res) != __true_res; \
	}                                                                                                           \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                                         \
	(__PRIVATE_hybrid_overflow_smul##Nargbits##_##Nresbits)(__INT##Nargbits##_TYPE__ __lhs,                     \
	                                                        __INT##Nargbits##_TYPE__ __rhs,                     \
	                                                        __INT##Nresbits##_TYPE__ *__p_result) {             \
		__INT##Nprombits##_TYPE__ __true_res = (__INT##Nprombits##_TYPE__)__lhs *                               \
		                                       (__INT##Nprombits##_TYPE__)__rhs;                                \
		return (__INT##Nprombits##_TYPE__)(*__p_result = (__INT##Nresbits##_TYPE__)__true_res) != __true_res;   \
	}

/* Check for overflow via range checks */
#define __PRIVATE_HYBRID_DEFINE_RANGECHECK_API(Nargbits, Nresbits, if_argbits_gt_resbits)                       \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                                         \
	(__PRIVATE_hybrid_overflow_uadd##Nargbits##_##Nresbits)(__UINT##Nargbits##_TYPE__ __lhs,                    \
	                                                        __UINT##Nargbits##_TYPE__ __rhs,                    \
	                                                        __UINT##Nresbits##_TYPE__ *__p_result) {            \
		__UINT##Nargbits##_TYPE__ __trunc_res = (__UINT##Nargbits##_TYPE__)__lhs +                              \
		                                        (__UINT##Nargbits##_TYPE__)__rhs;                               \
		*__p_result = (__UINT##Nresbits##_TYPE__)__trunc_res;                                                   \
		return __lhs > (__UINT##Nargbits##_MAX__ - __rhs)                                                       \
		       if_argbits_gt_resbits(|| __trunc_res != (__UINT##Nargbits##_TYPE__)*__p_result);                 \
	}                                                                                                           \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                                         \
	(__PRIVATE_hybrid_overflow_sadd##Nargbits##_##Nresbits)(__INT##Nargbits##_TYPE__ __lhs,                     \
	                                                        __INT##Nargbits##_TYPE__ __rhs,                     \
	                                                        __INT##Nresbits##_TYPE__ *__p_result) {             \
		__INT##Nargbits##_TYPE__ __trunc_res = (__INT##Nargbits##_TYPE__)__lhs +                                \
		                                       (__INT##Nargbits##_TYPE__)__rhs;                                 \
		*__p_result = (__INT##Nresbits##_TYPE__)__trunc_res;                                                    \
		return (__rhs > 0 && __lhs > (__INT##Nargbits##_MAX__ - __rhs)) ||                                      \
		       (__rhs < 0 && __lhs < (__INT##Nargbits##_MIN__ - __rhs))                                         \
		       if_argbits_gt_resbits(|| __trunc_res != (__INT##Nargbits##_TYPE__)*__p_result);                  \
	}                                                                                                           \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                                         \
	(__PRIVATE_hybrid_overflow_usub##Nargbits##_##Nresbits)(__UINT##Nargbits##_TYPE__ __lhs,                    \
	                                                        __UINT##Nargbits##_TYPE__ __rhs,                    \
	                                                        __UINT##Nresbits##_TYPE__ *__p_result) {            \
		__UINT##Nargbits##_TYPE__ __trunc_res = (__UINT##Nargbits##_TYPE__)__lhs -                              \
		                                        (__UINT##Nargbits##_TYPE__)__rhs;                               \
		*__p_result = (__UINT##Nresbits##_TYPE__)__trunc_res;                                                   \
		return __lhs < __rhs                                                                                    \
		       if_argbits_gt_resbits(|| __trunc_res != (__UINT##Nargbits##_TYPE__)*__p_result);                 \
	}                                                                                                           \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                                         \
	(__PRIVATE_hybrid_overflow_ssub##Nargbits##_##Nresbits)(__INT##Nargbits##_TYPE__ __lhs,                     \
	                                                        __INT##Nargbits##_TYPE__ __rhs,                     \
	                                                        __INT##Nresbits##_TYPE__ *__p_result) {             \
		__INT##Nargbits##_TYPE__ __trunc_res = (__INT##Nargbits##_TYPE__)__lhs -                                \
		                                       (__INT##Nargbits##_TYPE__)__rhs;                                 \
		*__p_result = (__INT##Nresbits##_TYPE__)__trunc_res;                                                    \
		return (__rhs > 0 && __lhs < (__INT##Nargbits##_MIN__ + __rhs)) ||                                      \
		       (__rhs < 0 && __lhs > (__INT##Nargbits##_MAX__ + __rhs))                                         \
		       if_argbits_gt_resbits(|| __trunc_res != (__INT##Nargbits##_TYPE__)*__p_result);                  \
	}                                                                                                           \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                                         \
	(__PRIVATE_hybrid_overflow_umul##Nargbits##_##Nresbits)(__UINT##Nargbits##_TYPE__ __lhs,                    \
	                                                        __UINT##Nargbits##_TYPE__ __rhs,                    \
	                                                        __UINT##Nresbits##_TYPE__ *__p_result) {            \
		__UINT##Nargbits##_TYPE__ __trunc_res = (__UINT##Nargbits##_TYPE__)__lhs *                              \
		                                        (__UINT##Nargbits##_TYPE__)__rhs;                               \
		*__p_result = (__UINT##Nresbits##_TYPE__)__trunc_res;                                                   \
		return __lhs && __rhs &&                                                                                \
		       ((__lhs > (__UINT##Nargbits##_MAX__ / __rhs))                                                    \
		        if_argbits_gt_resbits(|| __trunc_res != (__UINT##Nargbits##_TYPE__)*__p_result));               \
	}                                                                                                           \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                                         \
	(__PRIVATE_hybrid_overflow_smul##Nargbits##_##Nresbits)(__INT##Nargbits##_TYPE__ __lhs,                     \
	                                                        __INT##Nargbits##_TYPE__ __rhs,                     \
	                                                        __INT##Nresbits##_TYPE__ *__p_result) {             \
		__INT##Nargbits##_TYPE__ __trunc_res = (__INT##Nargbits##_TYPE__)__lhs *                                \
		                                       (__INT##Nargbits##_TYPE__)__rhs;                                 \
		*__p_result = (__INT##Nresbits##_TYPE__)__trunc_res;                                                    \
		if (__lhs > 0) {                                                                                        \
			if (__rhs > 0) {                                                                                    \
				/* +x * +y */                                                                                   \
				if (__lhs > (__INT##Nargbits##_MAX__ / __rhs))                                                  \
					return 1;                                                                                   \
			} else {                                                                                            \
				/* +x * -y */                                                                                   \
				if (__rhs < (__INT##Nargbits##_MIN__ / __lhs))                                                  \
					return 1;                                                                                   \
			}                                                                                                   \
		} else if (__rhs > 0) {                                                                                 \
			/* -x * +y */                                                                                       \
			if (__lhs < (__INT##Nargbits##_MIN__ / __rhs))                                                      \
				return 1;                                                                                       \
		} else {                                                                                                \
			/* -x * -y */                                                                                       \
			if (__lhs && (__rhs < (__INT##Nargbits##_MAX__ / __lhs)))                                           \
				return 1;                                                                                       \
		}                                                                                                       \
		if_argbits_gt_resbits(                                                                                  \
		if (__trunc_res != (__INT##Nargbits##_TYPE__)*__p_result)                                               \
			return 1);                                                                                          \
		return 0;                                                                                               \
	}

#include "limitcore.h" /* Helper functions need type limits. */

/* Define helper functions */
#define __PRIVATE_HYBRID_IF0(x) /* nothing */
#define __PRIVATE_HYBRID_IF1(x) x

__DECL_BEGIN

__PRIVATE_HYBRID_DEFINE_PROMOTION_API(8, 16, 8)
__PRIVATE_HYBRID_DEFINE_PROMOTION_API(16, 32, 8)
__PRIVATE_HYBRID_DEFINE_PROMOTION_API(16, 32, 16)
#if !defined(__UINT64_TYPE__) || __SIZEOF_REGISTER__ < 8
__PRIVATE_HYBRID_DEFINE_RANGECHECK_API(32, 8, __PRIVATE_HYBRID_IF1)
__PRIVATE_HYBRID_DEFINE_RANGECHECK_API(32, 16, __PRIVATE_HYBRID_IF1)
__PRIVATE_HYBRID_DEFINE_RANGECHECK_API(32, 32, __PRIVATE_HYBRID_IF0)
#else /* !__UINT64_TYPE__ || __SIZEOF_REGISTER__ < 8 */
__PRIVATE_HYBRID_DEFINE_PROMOTION_API(32, 64, 8)
__PRIVATE_HYBRID_DEFINE_PROMOTION_API(32, 64, 16)
__PRIVATE_HYBRID_DEFINE_PROMOTION_API(32, 64, 32)
#endif /* __UINT64_TYPE__ && __SIZEOF_REGISTER__ >= 8 */
#ifdef __UINT64_TYPE__
#if !defined(__UINT128_TYPE__) || __SIZEOF_REGISTER__ < 16
__PRIVATE_HYBRID_DEFINE_RANGECHECK_API(64, 8, __PRIVATE_HYBRID_IF1)
__PRIVATE_HYBRID_DEFINE_RANGECHECK_API(64, 16, __PRIVATE_HYBRID_IF1)
__PRIVATE_HYBRID_DEFINE_RANGECHECK_API(64, 32, __PRIVATE_HYBRID_IF1)
__PRIVATE_HYBRID_DEFINE_RANGECHECK_API(64, 64, __PRIVATE_HYBRID_IF0)
#else /* !__UINT128_TYPE__ || __SIZEOF_REGISTER__ < 16 */
__PRIVATE_HYBRID_DEFINE_PROMOTION_API(64, 128, 8)
__PRIVATE_HYBRID_DEFINE_PROMOTION_API(64, 128, 16)
__PRIVATE_HYBRID_DEFINE_PROMOTION_API(64, 128, 32)
__PRIVATE_HYBRID_DEFINE_PROMOTION_API(64, 128, 64)
#endif /* __UINT128_TYPE__ && __SIZEOF_REGISTER__ >= 16 */
#ifdef __UINT128_TYPE__
__PRIVATE_HYBRID_DEFINE_RANGECHECK_API(128, 8, __PRIVATE_HYBRID_IF1)
__PRIVATE_HYBRID_DEFINE_RANGECHECK_API(128, 16, __PRIVATE_HYBRID_IF1)
__PRIVATE_HYBRID_DEFINE_RANGECHECK_API(128, 32, __PRIVATE_HYBRID_IF1)
__PRIVATE_HYBRID_DEFINE_RANGECHECK_API(128, 64, __PRIVATE_HYBRID_IF1)
__PRIVATE_HYBRID_DEFINE_RANGECHECK_API(128, 128, __PRIVATE_HYBRID_IF0)
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */

__DECL_END

#undef __PRIVATE_HYBRID_DEFINE_RANGECHECK_API
#undef __PRIVATE_HYBRID_DEFINE_PROMOTION_API
#undef __PRIVATE_HYBRID_IF1
#undef __PRIVATE_HYBRID_IF0

/* Operations that never overflow (except for USUB, but that one can just be implemented as a macro) */
#define __PRIVATE_hybrid_overflow_uadd8_16(lhs, rhs, p_result)  (*(p_result) = (__UINT16_TYPE__)((__UINT16_TYPE__)(lhs) + (__UINT16_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_usub8_16(lhs, rhs, p_result)  ((__INT16_TYPE__)(*(p_result) = (__UINT16_TYPE__)(__INT16_TYPE__)((__INT16_TYPE__)(lhs) - (__INT16_TYPE__)(rhs))) >= 0)
#define __PRIVATE_hybrid_overflow_umul8_16(lhs, rhs, p_result)  (*(p_result) = (__UINT16_TYPE__)((__UINT16_TYPE__)(lhs) * (__UINT16_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_sadd8_16(lhs, rhs, p_result)  (*(p_result) = (__INT16_TYPE__)((__INT16_TYPE__)(lhs) + (__INT16_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_ssub8_16(lhs, rhs, p_result)  (*(p_result) = (__INT16_TYPE__)((__INT16_TYPE__)(lhs) - (__INT16_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_smul8_16(lhs, rhs, p_result)  (*(p_result) = (__INT16_TYPE__)((__INT16_TYPE__)(lhs) * (__INT16_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_uadd8_32(lhs, rhs, p_result)  (*(p_result) = (__UINT32_TYPE__)((__UINT16_TYPE__)(lhs) + (__UINT16_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_usub8_32(lhs, rhs, p_result)  ((__INT32_TYPE__)(*(p_result) = (__UINT32_TYPE__)(__INT32_TYPE__)((__INT16_TYPE__)(lhs) - (__INT16_TYPE__)(rhs))) >= 0)
#define __PRIVATE_hybrid_overflow_umul8_32(lhs, rhs, p_result)  (*(p_result) = (__UINT32_TYPE__)((__UINT16_TYPE__)(lhs) * (__UINT16_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_sadd8_32(lhs, rhs, p_result)  (*(p_result) = (__INT32_TYPE__)((__INT16_TYPE__)(lhs) + (__INT16_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_ssub8_32(lhs, rhs, p_result)  (*(p_result) = (__INT32_TYPE__)((__INT16_TYPE__)(lhs) - (__INT16_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_smul8_32(lhs, rhs, p_result)  (*(p_result) = (__INT32_TYPE__)((__INT16_TYPE__)(lhs) * (__INT16_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_uadd16_32(lhs, rhs, p_result) (*(p_result) = (__UINT32_TYPE__)(lhs) + (__UINT32_TYPE__)(rhs), 0)
#define __PRIVATE_hybrid_overflow_usub16_32(lhs, rhs, p_result) ((__INT32_TYPE__)(*(p_result) = (__UINT32_TYPE__)((__INT32_TYPE__)(lhs) - (__INT32_TYPE__)(rhs))) >= 0)
#define __PRIVATE_hybrid_overflow_umul16_32(lhs, rhs, p_result) (*(p_result) = (__UINT32_TYPE__)(lhs) * (__UINT32_TYPE__)(rhs), 0)
#define __PRIVATE_hybrid_overflow_sadd16_32(lhs, rhs, p_result) (*(p_result) = (__INT32_TYPE__)(lhs) + (__INT32_TYPE__)(rhs), 0)
#define __PRIVATE_hybrid_overflow_ssub16_32(lhs, rhs, p_result) (*(p_result) = (__INT32_TYPE__)(lhs) - (__INT32_TYPE__)(rhs), 0)
#define __PRIVATE_hybrid_overflow_smul16_32(lhs, rhs, p_result) (*(p_result) = (__INT32_TYPE__)(lhs) * (__INT32_TYPE__)(rhs), 0)
#ifdef __UINT64_TYPE__
#define __PRIVATE_hybrid_overflow_uadd8_64(lhs, rhs, p_result)  (*(p_result) = (__UINT64_TYPE__)((__UINT16_TYPE__)(lhs) + (__UINT16_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_usub8_64(lhs, rhs, p_result)  ((__INT64_TYPE__)(*(p_result) = (__UINT64_TYPE__)(__INT64_TYPE__)((__INT16_TYPE__)(lhs) - (__INT16_TYPE__)(rhs))) >= 0)
#define __PRIVATE_hybrid_overflow_umul8_64(lhs, rhs, p_result)  (*(p_result) = (__UINT64_TYPE__)((__UINT16_TYPE__)(lhs) * (__UINT16_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_sadd8_64(lhs, rhs, p_result)  (*(p_result) = (__INT64_TYPE__)((__INT16_TYPE__)(lhs) + (__INT16_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_ssub8_64(lhs, rhs, p_result)  (*(p_result) = (__INT64_TYPE__)((__INT16_TYPE__)(lhs) - (__INT16_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_smul8_64(lhs, rhs, p_result)  (*(p_result) = (__INT64_TYPE__)((__INT16_TYPE__)(lhs) * (__INT16_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_uadd16_64(lhs, rhs, p_result) (*(p_result) = (__UINT64_TYPE__)((__UINT32_TYPE__)(lhs) + (__UINT32_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_usub16_64(lhs, rhs, p_result) ((__INT64_TYPE__)(*(p_result) = (__UINT64_TYPE__)(__INT64_TYPE__)((__INT32_TYPE__)(lhs) - (__INT32_TYPE__)(rhs))) >= 0)
#define __PRIVATE_hybrid_overflow_umul16_64(lhs, rhs, p_result) (*(p_result) = (__UINT64_TYPE__)((__UINT32_TYPE__)(lhs) * (__UINT32_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_sadd16_64(lhs, rhs, p_result) (*(p_result) = (__INT64_TYPE__)((__INT32_TYPE__)(lhs) + (__INT32_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_ssub16_64(lhs, rhs, p_result) (*(p_result) = (__INT64_TYPE__)((__INT32_TYPE__)(lhs) - (__INT32_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_smul16_64(lhs, rhs, p_result) (*(p_result) = (__INT64_TYPE__)((__INT32_TYPE__)(lhs) * (__INT32_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_uadd32_64(lhs, rhs, p_result) (*(p_result) = (__UINT64_TYPE__)(lhs) + (__UINT64_TYPE__)(rhs), 0)
#define __PRIVATE_hybrid_overflow_usub32_64(lhs, rhs, p_result) ((__INT64_TYPE__)(*(p_result) = (__UINT64_TYPE__)((__INT64_TYPE__)(lhs) - (__INT64_TYPE__)(rhs))) >= 0)
#define __PRIVATE_hybrid_overflow_umul32_64(lhs, rhs, p_result) (*(p_result) = (__UINT64_TYPE__)(lhs) * (__UINT64_TYPE__)(rhs), 0)
#define __PRIVATE_hybrid_overflow_sadd32_64(lhs, rhs, p_result) (*(p_result) = (__INT64_TYPE__)(lhs) + (__INT64_TYPE__)(rhs), 0)
#define __PRIVATE_hybrid_overflow_ssub32_64(lhs, rhs, p_result) (*(p_result) = (__INT64_TYPE__)(lhs) - (__INT64_TYPE__)(rhs), 0)
#define __PRIVATE_hybrid_overflow_smul32_64(lhs, rhs, p_result) (*(p_result) = (__INT64_TYPE__)(lhs) * (__INT64_TYPE__)(rhs), 0)
#ifdef __UINT128_TYPE__
#define __PRIVATE_hybrid_overflow_uadd8_128(lhs, rhs, p_result)  (*(p_result) = (__UINT128_TYPE__)((__UINT16_TYPE__)(lhs) + (__UINT16_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_usub8_128(lhs, rhs, p_result)  ((__INT128_TYPE__)(*(p_result) = (__UINT128_TYPE__)(__INT128_TYPE__)((__INT16_TYPE__)(lhs) - (__INT16_TYPE__)(rhs))) >= 0)
#define __PRIVATE_hybrid_overflow_umul8_128(lhs, rhs, p_result)  (*(p_result) = (__UINT128_TYPE__)((__UINT16_TYPE__)(lhs) * (__UINT16_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_sadd8_128(lhs, rhs, p_result)  (*(p_result) = (__INT128_TYPE__)((__INT16_TYPE__)(lhs) + (__INT16_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_ssub8_128(lhs, rhs, p_result)  (*(p_result) = (__INT128_TYPE__)((__INT16_TYPE__)(lhs) - (__INT16_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_smul8_128(lhs, rhs, p_result)  (*(p_result) = (__INT128_TYPE__)((__INT16_TYPE__)(lhs) * (__INT16_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_uadd16_128(lhs, rhs, p_result) (*(p_result) = (__UINT128_TYPE__)((__UINT32_TYPE__)(lhs) + (__UINT32_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_usub16_128(lhs, rhs, p_result) ((__INT128_TYPE__)(*(p_result) = (__UINT128_TYPE__)(__INT128_TYPE__)((__INT32_TYPE__)(lhs) - (__INT32_TYPE__)(rhs))) >= 0)
#define __PRIVATE_hybrid_overflow_umul16_128(lhs, rhs, p_result) (*(p_result) = (__UINT128_TYPE__)((__UINT32_TYPE__)(lhs) * (__UINT32_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_sadd16_128(lhs, rhs, p_result) (*(p_result) = (__INT128_TYPE__)((__INT32_TYPE__)(lhs) + (__INT32_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_ssub16_128(lhs, rhs, p_result) (*(p_result) = (__INT128_TYPE__)((__INT32_TYPE__)(lhs) - (__INT32_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_smul16_128(lhs, rhs, p_result) (*(p_result) = (__INT128_TYPE__)((__INT32_TYPE__)(lhs) * (__INT32_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_uadd32_128(lhs, rhs, p_result) (*(p_result) = (__UINT128_TYPE__)((__UINT64_TYPE__)(lhs) + (__UINT64_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_usub32_128(lhs, rhs, p_result) ((__INT128_TYPE__)(*(p_result) = (__UINT128_TYPE__)(__INT128_TYPE__)((__INT64_TYPE__)(lhs) - (__INT64_TYPE__)(rhs))) >= 0)
#define __PRIVATE_hybrid_overflow_umul32_128(lhs, rhs, p_result) (*(p_result) = (__UINT128_TYPE__)((__UINT64_TYPE__)(lhs) * (__UINT64_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_sadd32_128(lhs, rhs, p_result) (*(p_result) = (__INT128_TYPE__)((__INT64_TYPE__)(lhs) + (__INT64_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_ssub32_128(lhs, rhs, p_result) (*(p_result) = (__INT128_TYPE__)((__INT64_TYPE__)(lhs) - (__INT64_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_smul32_128(lhs, rhs, p_result) (*(p_result) = (__INT128_TYPE__)((__INT64_TYPE__)(lhs) * (__INT64_TYPE__)(rhs)), 0)
#define __PRIVATE_hybrid_overflow_uadd64_128(lhs, rhs, p_result) (*(p_result) = (__UINT128_TYPE__)(lhs) + (__UINT128_TYPE__)(rhs), 0)
#define __PRIVATE_hybrid_overflow_usub64_128(lhs, rhs, p_result) ((__INT128_TYPE__)(*(p_result) = (__UINT128_TYPE__)((__INT128_TYPE__)(lhs) - (__INT128_TYPE__)(rhs))) >= 0)
#define __PRIVATE_hybrid_overflow_umul64_128(lhs, rhs, p_result) (*(p_result) = (__UINT128_TYPE__)(lhs) * (__UINT128_TYPE__)(rhs), 0)
#define __PRIVATE_hybrid_overflow_sadd64_128(lhs, rhs, p_result) (*(p_result) = (__INT128_TYPE__)(lhs) + (__INT128_TYPE__)(rhs), 0)
#define __PRIVATE_hybrid_overflow_ssub64_128(lhs, rhs, p_result) (*(p_result) = (__INT128_TYPE__)(lhs) - (__INT128_TYPE__)(rhs), 0)
#define __PRIVATE_hybrid_overflow_smul64_128(lhs, rhs, p_result) (*(p_result) = (__INT128_TYPE__)(lhs) * (__INT128_TYPE__)(rhs), 0)
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */

/* Auto-select overload based on operand size. */
#define __PRIVATE_hybrid_overflow_size2(lhs, rhs) (sizeof(lhs) > sizeof(rhs) ? sizeof(lhs) : sizeof(rhs))

/* clang-format off */
/*[[[deemon
import * from deemon;
function define_hybrid_overflow_op_n(op: string, n: int, argSizes: {int...}, useChooseExpr: bool) {
	local US = op.startswith("u") ? "U" : "";
	print("#define __hybrid_overflow_", op, n, "(lhs, rhs, p_result) __builtin_expect( \\");
	if (useChooseExpr) {
		for (local argSize: argSizes) {
			if (argSize != argSizes.last) {
				print("	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= ", argSize / 8, ", "),;
			} else {
				print("	                                                                      "),;
			}
			print("__PRIVATE_hybrid_overflow_", op, argSize, "_", n,
				  "((__", US, "INT", argSize, "_TYPE__)(lhs), (__", US, "INT", argSize, "_TYPE__)(rhs), p_result)"),;
			if (argSize != argSizes.last) {
				print(", \\");
			} else {
				print(")" * (#argSizes - 1), ", 0)");
			}
		}
	} else {
		for (local argSize: argSizes) {
			print("	"),;
			if (argSize != argSizes.last) {
				print("__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= ", argSize / 8, " ? "),;
			} else {
				print("                                                 "),;
			}
			print("__PRIVATE_hybrid_overflow_", op, argSize, "_", n,
				  "((__", US, "INT", argSize, "_TYPE__)(lhs), (__", US, "INT", argSize, "_TYPE__)(rhs), p_result)"),;
			if (argSize != argSizes.last) {
				print(" : \\");
			} else {
				print(", 0)");
			}
		}
	}
}

function define_hybrid_overflow_op(op: string, argSizes: {int...}, useChooseExpr: bool) {
	local US = op.startswith("u") ? "U" : "";
	print("#define __hybrid_overflow_", op, "(lhs, rhs, p_result) \\");
	if (useChooseExpr) {
		for (local argSize: argSizes) {
			if (argSize != argSizes.last) {
				print("	__builtin_choose_expr(sizeof(*(p_result)) <= ", argSize / 8, ", "),;
			} else {
				print("	                                                "),;
			}
			print("__hybrid_overflow_", op, argSize,
				  "(lhs, rhs, (__", US, "INT", argSize, "_TYPE__ *)(p_result))"),;
			if (argSize != argSizes.last) {
				print(", \\");
			} else {
				print(")" * (#argSizes - 1));
			}
		}
	} else {
		for (local argSize: argSizes) {
			print("	"),;
			print(argSize == argSizes.first ? "(" : " "),;
			if (argSize != argSizes.last) {
				print("sizeof(*(p_result)) <= ", argSize / 8, " ? "),;
			} else {
				print("                           "),;
			}
			print("__hybrid_overflow_", op, argSize,
				  "(lhs, rhs, (__", US, "INT", argSize, "_TYPE__ *)(p_result))"),;
			if (argSize != argSizes.last) {
				print(" : \\");
			} else {
				print(")");
			}
		}
	}
}

local functions = ["uadd", "sadd", "usub", "ssub", "umul", "smul"];

print("#ifndef __NO_builtin_choose_expr");
print("#ifdef __UINT128_TYPE__");
for (local fun: functions) {
	define_hybrid_overflow_op_n(fun, 8, [8, 16, 32, 64, 128], true);
	define_hybrid_overflow_op_n(fun, 16, [8, 16, 32, 64, 128], true);
	define_hybrid_overflow_op_n(fun, 32, [8, 16, 32, 64, 128], true);
	define_hybrid_overflow_op_n(fun, 64, [8, 16, 32, 64, 128], true);
	define_hybrid_overflow_op_n(fun, 128, [8, 16, 32, 64, 128], true);
	define_hybrid_overflow_op(fun, [8, 16, 32, 64, 128], true);
}
print("#elif defined(__UINT64_TYPE__)");
for (local fun: functions) {
	define_hybrid_overflow_op_n(fun, 8, [8, 16, 32, 64], true);
	define_hybrid_overflow_op_n(fun, 16, [8, 16, 32, 64], true);
	define_hybrid_overflow_op_n(fun, 32, [8, 16, 32, 64], true);
	define_hybrid_overflow_op_n(fun, 64, [8, 16, 32, 64], true);
	define_hybrid_overflow_op(fun, [8, 16, 32, 64], true);
}
print("#else /" "* ... *" "/");
for (local fun: functions) {
	define_hybrid_overflow_op_n(fun, 8, [8, 16, 32], true);
	define_hybrid_overflow_op_n(fun, 16, [8, 16, 32], true);
	define_hybrid_overflow_op_n(fun, 32, [8, 16, 32], true);
	define_hybrid_overflow_op(fun, [8, 16, 32], true);
}
print("#endif /" "* !... *" "/");
print("#else /" "* __NO_builtin_choose_expr *" "/");
print("#ifdef __UINT128_TYPE__");
for (local fun: functions) {
	define_hybrid_overflow_op_n(fun, 8, [8, 16, 32, 64, 128], false);
	define_hybrid_overflow_op_n(fun, 16, [8, 16, 32, 64, 128], false);
	define_hybrid_overflow_op_n(fun, 32, [8, 16, 32, 64, 128], false);
	define_hybrid_overflow_op_n(fun, 64, [8, 16, 32, 64, 128], false);
	define_hybrid_overflow_op_n(fun, 128, [8, 16, 32, 64, 128], false);
	define_hybrid_overflow_op(fun, [8, 16, 32, 64, 128], false);
}
print("#elif defined(__UINT64_TYPE__)");
for (local fun: functions) {
	define_hybrid_overflow_op_n(fun, 8, [8, 16, 32, 64], false);
	define_hybrid_overflow_op_n(fun, 16, [8, 16, 32, 64], false);
	define_hybrid_overflow_op_n(fun, 32, [8, 16, 32, 64], false);
	define_hybrid_overflow_op_n(fun, 64, [8, 16, 32, 64], false);
	define_hybrid_overflow_op(fun, [8, 16, 32, 64], false);
}
print("#else /" "* ... *" "/");
for (local fun: functions) {
	define_hybrid_overflow_op_n(fun, 8, [8, 16, 32], false);
	define_hybrid_overflow_op_n(fun, 16, [8, 16, 32], false);
	define_hybrid_overflow_op_n(fun, 32, [8, 16, 32], false);
	define_hybrid_overflow_op(fun, [8, 16, 32], false);
}
print("#endif /" "* !... *" "/");
print("#endif /" "* !__NO_builtin_choose_expr *" "/");

]]]*/
#ifndef __NO_builtin_choose_expr
#ifdef __UINT128_TYPE__
#define __hybrid_overflow_uadd8(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_uadd8_8((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_uadd16_8((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_uadd32_8((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_uadd64_8((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_uadd128_8((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_uadd16(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_uadd8_16((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_uadd16_16((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_uadd32_16((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_uadd64_16((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_uadd128_16((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_uadd32(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_uadd8_32((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_uadd16_32((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_uadd32_32((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_uadd64_32((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_uadd128_32((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_uadd64(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_uadd8_64((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_uadd16_64((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_uadd32_64((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_uadd64_64((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_uadd128_64((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_uadd128(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_uadd8_128((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_uadd16_128((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_uadd32_128((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_uadd64_128((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_uadd128_128((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_uadd(lhs, rhs, p_result) \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_uadd8(lhs, rhs, (__UINT8_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_uadd16(lhs, rhs, (__UINT16_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_overflow_uadd32(lhs, rhs, (__UINT32_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 8, __hybrid_overflow_uadd64(lhs, rhs, (__UINT64_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_uadd128(lhs, rhs, (__UINT128_TYPE__ *)(p_result))))))
#define __hybrid_overflow_sadd8(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_sadd8_8((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_sadd16_8((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_sadd32_8((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_sadd64_8((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_sadd128_8((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_sadd16(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_sadd8_16((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_sadd16_16((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_sadd32_16((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_sadd64_16((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_sadd128_16((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_sadd32(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_sadd8_32((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_sadd16_32((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_sadd32_32((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_sadd64_32((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_sadd128_32((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_sadd64(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_sadd8_64((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_sadd16_64((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_sadd32_64((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_sadd64_64((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_sadd128_64((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_sadd128(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_sadd8_128((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_sadd16_128((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_sadd32_128((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_sadd64_128((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_sadd128_128((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_sadd(lhs, rhs, p_result) \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_sadd8(lhs, rhs, (__INT8_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_sadd16(lhs, rhs, (__INT16_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_overflow_sadd32(lhs, rhs, (__INT32_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 8, __hybrid_overflow_sadd64(lhs, rhs, (__INT64_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_sadd128(lhs, rhs, (__INT128_TYPE__ *)(p_result))))))
#define __hybrid_overflow_usub8(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_usub8_8((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_usub16_8((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_usub32_8((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_usub64_8((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_usub128_8((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_usub16(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_usub8_16((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_usub16_16((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_usub32_16((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_usub64_16((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_usub128_16((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_usub32(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_usub8_32((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_usub16_32((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_usub32_32((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_usub64_32((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_usub128_32((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_usub64(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_usub8_64((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_usub16_64((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_usub32_64((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_usub64_64((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_usub128_64((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_usub128(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_usub8_128((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_usub16_128((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_usub32_128((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_usub64_128((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_usub128_128((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_usub(lhs, rhs, p_result) \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_usub8(lhs, rhs, (__UINT8_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_usub16(lhs, rhs, (__UINT16_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_overflow_usub32(lhs, rhs, (__UINT32_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 8, __hybrid_overflow_usub64(lhs, rhs, (__UINT64_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_usub128(lhs, rhs, (__UINT128_TYPE__ *)(p_result))))))
#define __hybrid_overflow_ssub8(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_ssub8_8((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_ssub16_8((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_ssub32_8((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_ssub64_8((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_ssub128_8((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_ssub16(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_ssub8_16((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_ssub16_16((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_ssub32_16((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_ssub64_16((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_ssub128_16((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_ssub32(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_ssub8_32((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_ssub16_32((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_ssub32_32((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_ssub64_32((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_ssub128_32((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_ssub64(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_ssub8_64((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_ssub16_64((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_ssub32_64((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_ssub64_64((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_ssub128_64((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_ssub128(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_ssub8_128((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_ssub16_128((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_ssub32_128((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_ssub64_128((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_ssub128_128((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_ssub(lhs, rhs, p_result) \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_ssub8(lhs, rhs, (__INT8_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_ssub16(lhs, rhs, (__INT16_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_overflow_ssub32(lhs, rhs, (__INT32_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 8, __hybrid_overflow_ssub64(lhs, rhs, (__INT64_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_ssub128(lhs, rhs, (__INT128_TYPE__ *)(p_result))))))
#define __hybrid_overflow_umul8(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_umul8_8((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_umul16_8((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_umul32_8((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_umul64_8((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_umul128_8((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_umul16(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_umul8_16((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_umul16_16((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_umul32_16((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_umul64_16((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_umul128_16((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_umul32(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_umul8_32((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_umul16_32((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_umul32_32((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_umul64_32((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_umul128_32((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_umul64(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_umul8_64((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_umul16_64((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_umul32_64((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_umul64_64((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_umul128_64((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_umul128(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_umul8_128((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_umul16_128((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_umul32_128((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_umul64_128((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_umul128_128((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_umul(lhs, rhs, p_result) \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_umul8(lhs, rhs, (__UINT8_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_umul16(lhs, rhs, (__UINT16_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_overflow_umul32(lhs, rhs, (__UINT32_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 8, __hybrid_overflow_umul64(lhs, rhs, (__UINT64_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_umul128(lhs, rhs, (__UINT128_TYPE__ *)(p_result))))))
#define __hybrid_overflow_smul8(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_smul8_8((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_smul16_8((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_smul32_8((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_smul64_8((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_smul128_8((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_smul16(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_smul8_16((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_smul16_16((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_smul32_16((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_smul64_16((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_smul128_16((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_smul32(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_smul8_32((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_smul16_32((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_smul32_32((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_smul64_32((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_smul128_32((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_smul64(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_smul8_64((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_smul16_64((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_smul32_64((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_smul64_64((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_smul128_64((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_smul128(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_smul8_128((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_smul16_128((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_smul32_128((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8, __PRIVATE_hybrid_overflow_smul64_128((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_smul128_128((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result))))), 0)
#define __hybrid_overflow_smul(lhs, rhs, p_result) \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_smul8(lhs, rhs, (__INT8_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_smul16(lhs, rhs, (__INT16_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_overflow_smul32(lhs, rhs, (__INT32_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 8, __hybrid_overflow_smul64(lhs, rhs, (__INT64_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_smul128(lhs, rhs, (__INT128_TYPE__ *)(p_result))))))
#elif defined(__UINT64_TYPE__)
#define __hybrid_overflow_uadd8(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_uadd8_8((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_uadd16_8((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_uadd32_8((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_uadd64_8((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_uadd16(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_uadd8_16((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_uadd16_16((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_uadd32_16((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_uadd64_16((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_uadd32(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_uadd8_32((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_uadd16_32((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_uadd32_32((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_uadd64_32((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_uadd64(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_uadd8_64((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_uadd16_64((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_uadd32_64((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_uadd64_64((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_uadd(lhs, rhs, p_result) \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_uadd8(lhs, rhs, (__UINT8_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_uadd16(lhs, rhs, (__UINT16_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_overflow_uadd32(lhs, rhs, (__UINT32_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_uadd64(lhs, rhs, (__UINT64_TYPE__ *)(p_result)))))
#define __hybrid_overflow_sadd8(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_sadd8_8((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_sadd16_8((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_sadd32_8((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_sadd64_8((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_sadd16(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_sadd8_16((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_sadd16_16((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_sadd32_16((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_sadd64_16((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_sadd32(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_sadd8_32((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_sadd16_32((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_sadd32_32((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_sadd64_32((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_sadd64(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_sadd8_64((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_sadd16_64((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_sadd32_64((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_sadd64_64((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_sadd(lhs, rhs, p_result) \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_sadd8(lhs, rhs, (__INT8_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_sadd16(lhs, rhs, (__INT16_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_overflow_sadd32(lhs, rhs, (__INT32_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_sadd64(lhs, rhs, (__INT64_TYPE__ *)(p_result)))))
#define __hybrid_overflow_usub8(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_usub8_8((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_usub16_8((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_usub32_8((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_usub64_8((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_usub16(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_usub8_16((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_usub16_16((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_usub32_16((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_usub64_16((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_usub32(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_usub8_32((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_usub16_32((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_usub32_32((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_usub64_32((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_usub64(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_usub8_64((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_usub16_64((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_usub32_64((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_usub64_64((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_usub(lhs, rhs, p_result) \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_usub8(lhs, rhs, (__UINT8_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_usub16(lhs, rhs, (__UINT16_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_overflow_usub32(lhs, rhs, (__UINT32_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_usub64(lhs, rhs, (__UINT64_TYPE__ *)(p_result)))))
#define __hybrid_overflow_ssub8(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_ssub8_8((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_ssub16_8((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_ssub32_8((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_ssub64_8((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_ssub16(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_ssub8_16((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_ssub16_16((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_ssub32_16((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_ssub64_16((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_ssub32(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_ssub8_32((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_ssub16_32((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_ssub32_32((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_ssub64_32((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_ssub64(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_ssub8_64((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_ssub16_64((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_ssub32_64((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_ssub64_64((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_ssub(lhs, rhs, p_result) \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_ssub8(lhs, rhs, (__INT8_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_ssub16(lhs, rhs, (__INT16_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_overflow_ssub32(lhs, rhs, (__INT32_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_ssub64(lhs, rhs, (__INT64_TYPE__ *)(p_result)))))
#define __hybrid_overflow_umul8(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_umul8_8((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_umul16_8((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_umul32_8((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_umul64_8((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_umul16(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_umul8_16((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_umul16_16((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_umul32_16((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_umul64_16((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_umul32(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_umul8_32((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_umul16_32((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_umul32_32((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_umul64_32((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_umul64(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_umul8_64((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_umul16_64((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_umul32_64((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_umul64_64((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_umul(lhs, rhs, p_result) \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_umul8(lhs, rhs, (__UINT8_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_umul16(lhs, rhs, (__UINT16_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_overflow_umul32(lhs, rhs, (__UINT32_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_umul64(lhs, rhs, (__UINT64_TYPE__ *)(p_result)))))
#define __hybrid_overflow_smul8(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_smul8_8((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_smul16_8((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_smul32_8((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_smul64_8((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_smul16(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_smul8_16((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_smul16_16((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_smul32_16((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_smul64_16((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_smul32(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_smul8_32((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_smul16_32((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_smul32_32((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_smul64_32((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_smul64(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_smul8_64((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_smul16_64((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4, __PRIVATE_hybrid_overflow_smul32_64((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_smul64_64((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result)))), 0)
#define __hybrid_overflow_smul(lhs, rhs, p_result) \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_smul8(lhs, rhs, (__INT8_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_smul16(lhs, rhs, (__INT16_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_overflow_smul32(lhs, rhs, (__INT32_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_smul64(lhs, rhs, (__INT64_TYPE__ *)(p_result)))))
#else /* ... */
#define __hybrid_overflow_uadd8(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_uadd8_8((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_uadd16_8((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_uadd32_8((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result))), 0)
#define __hybrid_overflow_uadd16(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_uadd8_16((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_uadd16_16((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_uadd32_16((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result))), 0)
#define __hybrid_overflow_uadd32(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_uadd8_32((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_uadd16_32((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_uadd32_32((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result))), 0)
#define __hybrid_overflow_uadd(lhs, rhs, p_result) \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_uadd8(lhs, rhs, (__UINT8_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_uadd16(lhs, rhs, (__UINT16_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_uadd32(lhs, rhs, (__UINT32_TYPE__ *)(p_result))))
#define __hybrid_overflow_sadd8(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_sadd8_8((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_sadd16_8((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_sadd32_8((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result))), 0)
#define __hybrid_overflow_sadd16(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_sadd8_16((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_sadd16_16((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_sadd32_16((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result))), 0)
#define __hybrid_overflow_sadd32(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_sadd8_32((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_sadd16_32((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_sadd32_32((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result))), 0)
#define __hybrid_overflow_sadd(lhs, rhs, p_result) \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_sadd8(lhs, rhs, (__INT8_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_sadd16(lhs, rhs, (__INT16_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_sadd32(lhs, rhs, (__INT32_TYPE__ *)(p_result))))
#define __hybrid_overflow_usub8(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_usub8_8((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_usub16_8((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_usub32_8((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result))), 0)
#define __hybrid_overflow_usub16(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_usub8_16((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_usub16_16((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_usub32_16((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result))), 0)
#define __hybrid_overflow_usub32(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_usub8_32((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_usub16_32((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_usub32_32((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result))), 0)
#define __hybrid_overflow_usub(lhs, rhs, p_result) \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_usub8(lhs, rhs, (__UINT8_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_usub16(lhs, rhs, (__UINT16_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_usub32(lhs, rhs, (__UINT32_TYPE__ *)(p_result))))
#define __hybrid_overflow_ssub8(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_ssub8_8((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_ssub16_8((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_ssub32_8((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result))), 0)
#define __hybrid_overflow_ssub16(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_ssub8_16((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_ssub16_16((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_ssub32_16((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result))), 0)
#define __hybrid_overflow_ssub32(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_ssub8_32((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_ssub16_32((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_ssub32_32((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result))), 0)
#define __hybrid_overflow_ssub(lhs, rhs, p_result) \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_ssub8(lhs, rhs, (__INT8_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_ssub16(lhs, rhs, (__INT16_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_ssub32(lhs, rhs, (__INT32_TYPE__ *)(p_result))))
#define __hybrid_overflow_umul8(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_umul8_8((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_umul16_8((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_umul32_8((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result))), 0)
#define __hybrid_overflow_umul16(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_umul8_16((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_umul16_16((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_umul32_16((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result))), 0)
#define __hybrid_overflow_umul32(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_umul8_32((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_umul16_32((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_umul32_32((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result))), 0)
#define __hybrid_overflow_umul(lhs, rhs, p_result) \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_umul8(lhs, rhs, (__UINT8_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_umul16(lhs, rhs, (__UINT16_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_umul32(lhs, rhs, (__UINT32_TYPE__ *)(p_result))))
#define __hybrid_overflow_smul8(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_smul8_8((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_smul16_8((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_smul32_8((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result))), 0)
#define __hybrid_overflow_smul16(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_smul8_16((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_smul16_16((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_smul32_16((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result))), 0)
#define __hybrid_overflow_smul32(lhs, rhs, p_result) __builtin_expect( \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1, __PRIVATE_hybrid_overflow_smul8_32((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result), \
	__builtin_choose_expr(__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2, __PRIVATE_hybrid_overflow_smul16_32((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result), \
	                                                                      __PRIVATE_hybrid_overflow_smul32_32((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result))), 0)
#define __hybrid_overflow_smul(lhs, rhs, p_result) \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_smul8(lhs, rhs, (__INT8_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_smul16(lhs, rhs, (__INT16_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_smul32(lhs, rhs, (__INT32_TYPE__ *)(p_result))))
#endif /* !... */
#else /* __NO_builtin_choose_expr */
#ifdef __UINT128_TYPE__
#define __hybrid_overflow_uadd8(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_uadd8_8((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_uadd16_8((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_uadd32_8((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_uadd64_8((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_uadd128_8((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_uadd16(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_uadd8_16((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_uadd16_16((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_uadd32_16((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_uadd64_16((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_uadd128_16((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_uadd32(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_uadd8_32((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_uadd16_32((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_uadd32_32((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_uadd64_32((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_uadd128_32((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_uadd64(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_uadd8_64((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_uadd16_64((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_uadd32_64((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_uadd64_64((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_uadd128_64((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_uadd128(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_uadd8_128((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_uadd16_128((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_uadd32_128((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_uadd64_128((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_uadd128_128((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_uadd(lhs, rhs, p_result) \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_uadd8(lhs, rhs, (__UINT8_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_uadd16(lhs, rhs, (__UINT16_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_overflow_uadd32(lhs, rhs, (__UINT32_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 8 ? __hybrid_overflow_uadd64(lhs, rhs, (__UINT64_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_uadd128(lhs, rhs, (__UINT128_TYPE__ *)(p_result)))
#define __hybrid_overflow_sadd8(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_sadd8_8((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_sadd16_8((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_sadd32_8((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_sadd64_8((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_sadd128_8((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_sadd16(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_sadd8_16((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_sadd16_16((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_sadd32_16((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_sadd64_16((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_sadd128_16((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_sadd32(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_sadd8_32((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_sadd16_32((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_sadd32_32((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_sadd64_32((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_sadd128_32((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_sadd64(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_sadd8_64((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_sadd16_64((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_sadd32_64((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_sadd64_64((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_sadd128_64((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_sadd128(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_sadd8_128((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_sadd16_128((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_sadd32_128((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_sadd64_128((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_sadd128_128((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_sadd(lhs, rhs, p_result) \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_sadd8(lhs, rhs, (__INT8_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_sadd16(lhs, rhs, (__INT16_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_overflow_sadd32(lhs, rhs, (__INT32_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 8 ? __hybrid_overflow_sadd64(lhs, rhs, (__INT64_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_sadd128(lhs, rhs, (__INT128_TYPE__ *)(p_result)))
#define __hybrid_overflow_usub8(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_usub8_8((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_usub16_8((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_usub32_8((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_usub64_8((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_usub128_8((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_usub16(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_usub8_16((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_usub16_16((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_usub32_16((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_usub64_16((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_usub128_16((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_usub32(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_usub8_32((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_usub16_32((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_usub32_32((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_usub64_32((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_usub128_32((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_usub64(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_usub8_64((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_usub16_64((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_usub32_64((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_usub64_64((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_usub128_64((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_usub128(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_usub8_128((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_usub16_128((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_usub32_128((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_usub64_128((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_usub128_128((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_usub(lhs, rhs, p_result) \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_usub8(lhs, rhs, (__UINT8_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_usub16(lhs, rhs, (__UINT16_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_overflow_usub32(lhs, rhs, (__UINT32_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 8 ? __hybrid_overflow_usub64(lhs, rhs, (__UINT64_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_usub128(lhs, rhs, (__UINT128_TYPE__ *)(p_result)))
#define __hybrid_overflow_ssub8(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_ssub8_8((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_ssub16_8((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_ssub32_8((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_ssub64_8((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_ssub128_8((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_ssub16(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_ssub8_16((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_ssub16_16((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_ssub32_16((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_ssub64_16((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_ssub128_16((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_ssub32(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_ssub8_32((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_ssub16_32((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_ssub32_32((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_ssub64_32((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_ssub128_32((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_ssub64(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_ssub8_64((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_ssub16_64((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_ssub32_64((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_ssub64_64((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_ssub128_64((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_ssub128(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_ssub8_128((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_ssub16_128((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_ssub32_128((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_ssub64_128((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_ssub128_128((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_ssub(lhs, rhs, p_result) \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_ssub8(lhs, rhs, (__INT8_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_ssub16(lhs, rhs, (__INT16_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_overflow_ssub32(lhs, rhs, (__INT32_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 8 ? __hybrid_overflow_ssub64(lhs, rhs, (__INT64_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_ssub128(lhs, rhs, (__INT128_TYPE__ *)(p_result)))
#define __hybrid_overflow_umul8(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_umul8_8((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_umul16_8((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_umul32_8((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_umul64_8((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_umul128_8((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_umul16(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_umul8_16((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_umul16_16((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_umul32_16((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_umul64_16((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_umul128_16((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_umul32(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_umul8_32((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_umul16_32((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_umul32_32((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_umul64_32((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_umul128_32((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_umul64(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_umul8_64((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_umul16_64((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_umul32_64((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_umul64_64((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_umul128_64((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_umul128(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_umul8_128((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_umul16_128((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_umul32_128((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_umul64_128((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_umul128_128((__UINT128_TYPE__)(lhs), (__UINT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_umul(lhs, rhs, p_result) \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_umul8(lhs, rhs, (__UINT8_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_umul16(lhs, rhs, (__UINT16_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_overflow_umul32(lhs, rhs, (__UINT32_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 8 ? __hybrid_overflow_umul64(lhs, rhs, (__UINT64_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_umul128(lhs, rhs, (__UINT128_TYPE__ *)(p_result)))
#define __hybrid_overflow_smul8(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_smul8_8((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_smul16_8((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_smul32_8((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_smul64_8((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_smul128_8((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_smul16(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_smul8_16((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_smul16_16((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_smul32_16((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_smul64_16((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_smul128_16((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_smul32(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_smul8_32((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_smul16_32((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_smul32_32((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_smul64_32((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_smul128_32((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_smul64(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_smul8_64((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_smul16_64((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_smul32_64((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_smul64_64((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_smul128_64((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_smul128(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_smul8_128((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_smul16_128((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_smul32_128((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 8 ? __PRIVATE_hybrid_overflow_smul64_128((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_smul128_128((__INT128_TYPE__)(lhs), (__INT128_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_smul(lhs, rhs, p_result) \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_smul8(lhs, rhs, (__INT8_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_smul16(lhs, rhs, (__INT16_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_overflow_smul32(lhs, rhs, (__INT32_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 8 ? __hybrid_overflow_smul64(lhs, rhs, (__INT64_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_smul128(lhs, rhs, (__INT128_TYPE__ *)(p_result)))
#elif defined(__UINT64_TYPE__)
#define __hybrid_overflow_uadd8(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_uadd8_8((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_uadd16_8((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_uadd32_8((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_uadd64_8((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_uadd16(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_uadd8_16((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_uadd16_16((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_uadd32_16((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_uadd64_16((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_uadd32(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_uadd8_32((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_uadd16_32((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_uadd32_32((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_uadd64_32((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_uadd64(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_uadd8_64((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_uadd16_64((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_uadd32_64((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_uadd64_64((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_uadd(lhs, rhs, p_result) \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_uadd8(lhs, rhs, (__UINT8_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_uadd16(lhs, rhs, (__UINT16_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_overflow_uadd32(lhs, rhs, (__UINT32_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_uadd64(lhs, rhs, (__UINT64_TYPE__ *)(p_result)))
#define __hybrid_overflow_sadd8(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_sadd8_8((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_sadd16_8((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_sadd32_8((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_sadd64_8((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_sadd16(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_sadd8_16((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_sadd16_16((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_sadd32_16((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_sadd64_16((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_sadd32(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_sadd8_32((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_sadd16_32((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_sadd32_32((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_sadd64_32((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_sadd64(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_sadd8_64((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_sadd16_64((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_sadd32_64((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_sadd64_64((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_sadd(lhs, rhs, p_result) \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_sadd8(lhs, rhs, (__INT8_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_sadd16(lhs, rhs, (__INT16_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_overflow_sadd32(lhs, rhs, (__INT32_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_sadd64(lhs, rhs, (__INT64_TYPE__ *)(p_result)))
#define __hybrid_overflow_usub8(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_usub8_8((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_usub16_8((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_usub32_8((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_usub64_8((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_usub16(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_usub8_16((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_usub16_16((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_usub32_16((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_usub64_16((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_usub32(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_usub8_32((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_usub16_32((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_usub32_32((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_usub64_32((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_usub64(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_usub8_64((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_usub16_64((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_usub32_64((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_usub64_64((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_usub(lhs, rhs, p_result) \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_usub8(lhs, rhs, (__UINT8_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_usub16(lhs, rhs, (__UINT16_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_overflow_usub32(lhs, rhs, (__UINT32_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_usub64(lhs, rhs, (__UINT64_TYPE__ *)(p_result)))
#define __hybrid_overflow_ssub8(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_ssub8_8((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_ssub16_8((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_ssub32_8((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_ssub64_8((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_ssub16(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_ssub8_16((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_ssub16_16((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_ssub32_16((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_ssub64_16((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_ssub32(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_ssub8_32((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_ssub16_32((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_ssub32_32((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_ssub64_32((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_ssub64(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_ssub8_64((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_ssub16_64((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_ssub32_64((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_ssub64_64((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_ssub(lhs, rhs, p_result) \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_ssub8(lhs, rhs, (__INT8_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_ssub16(lhs, rhs, (__INT16_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_overflow_ssub32(lhs, rhs, (__INT32_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_ssub64(lhs, rhs, (__INT64_TYPE__ *)(p_result)))
#define __hybrid_overflow_umul8(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_umul8_8((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_umul16_8((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_umul32_8((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_umul64_8((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_umul16(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_umul8_16((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_umul16_16((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_umul32_16((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_umul64_16((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_umul32(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_umul8_32((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_umul16_32((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_umul32_32((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_umul64_32((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_umul64(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_umul8_64((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_umul16_64((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_umul32_64((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_umul64_64((__UINT64_TYPE__)(lhs), (__UINT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_umul(lhs, rhs, p_result) \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_umul8(lhs, rhs, (__UINT8_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_umul16(lhs, rhs, (__UINT16_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_overflow_umul32(lhs, rhs, (__UINT32_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_umul64(lhs, rhs, (__UINT64_TYPE__ *)(p_result)))
#define __hybrid_overflow_smul8(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_smul8_8((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_smul16_8((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_smul32_8((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_smul64_8((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_smul16(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_smul8_16((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_smul16_16((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_smul32_16((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_smul64_16((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_smul32(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_smul8_32((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_smul16_32((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_smul32_32((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_smul64_32((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_smul64(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_smul8_64((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_smul16_64((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 4 ? __PRIVATE_hybrid_overflow_smul32_64((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_smul64_64((__INT64_TYPE__)(lhs), (__INT64_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_smul(lhs, rhs, p_result) \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_smul8(lhs, rhs, (__INT8_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_smul16(lhs, rhs, (__INT16_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_overflow_smul32(lhs, rhs, (__INT32_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_smul64(lhs, rhs, (__INT64_TYPE__ *)(p_result)))
#else /* ... */
#define __hybrid_overflow_uadd8(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_uadd8_8((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_uadd16_8((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_uadd32_8((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_uadd16(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_uadd8_16((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_uadd16_16((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_uadd32_16((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_uadd32(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_uadd8_32((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_uadd16_32((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_uadd32_32((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_uadd(lhs, rhs, p_result) \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_uadd8(lhs, rhs, (__UINT8_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_uadd16(lhs, rhs, (__UINT16_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_uadd32(lhs, rhs, (__UINT32_TYPE__ *)(p_result)))
#define __hybrid_overflow_sadd8(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_sadd8_8((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_sadd16_8((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_sadd32_8((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_sadd16(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_sadd8_16((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_sadd16_16((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_sadd32_16((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_sadd32(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_sadd8_32((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_sadd16_32((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_sadd32_32((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_sadd(lhs, rhs, p_result) \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_sadd8(lhs, rhs, (__INT8_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_sadd16(lhs, rhs, (__INT16_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_sadd32(lhs, rhs, (__INT32_TYPE__ *)(p_result)))
#define __hybrid_overflow_usub8(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_usub8_8((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_usub16_8((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_usub32_8((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_usub16(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_usub8_16((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_usub16_16((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_usub32_16((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_usub32(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_usub8_32((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_usub16_32((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_usub32_32((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_usub(lhs, rhs, p_result) \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_usub8(lhs, rhs, (__UINT8_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_usub16(lhs, rhs, (__UINT16_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_usub32(lhs, rhs, (__UINT32_TYPE__ *)(p_result)))
#define __hybrid_overflow_ssub8(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_ssub8_8((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_ssub16_8((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_ssub32_8((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_ssub16(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_ssub8_16((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_ssub16_16((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_ssub32_16((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_ssub32(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_ssub8_32((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_ssub16_32((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_ssub32_32((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_ssub(lhs, rhs, p_result) \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_ssub8(lhs, rhs, (__INT8_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_ssub16(lhs, rhs, (__INT16_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_ssub32(lhs, rhs, (__INT32_TYPE__ *)(p_result)))
#define __hybrid_overflow_umul8(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_umul8_8((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_umul16_8((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_umul32_8((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_umul16(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_umul8_16((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_umul16_16((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_umul32_16((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_umul32(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_umul8_32((__UINT8_TYPE__)(lhs), (__UINT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_umul16_32((__UINT16_TYPE__)(lhs), (__UINT16_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_umul32_32((__UINT32_TYPE__)(lhs), (__UINT32_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_umul(lhs, rhs, p_result) \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_umul8(lhs, rhs, (__UINT8_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_umul16(lhs, rhs, (__UINT16_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_umul32(lhs, rhs, (__UINT32_TYPE__ *)(p_result)))
#define __hybrid_overflow_smul8(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_smul8_8((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_smul16_8((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_smul32_8((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_smul16(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_smul8_16((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_smul16_16((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_smul32_16((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_smul32(lhs, rhs, p_result) __builtin_expect( \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 1 ? __PRIVATE_hybrid_overflow_smul8_32((__INT8_TYPE__)(lhs), (__INT8_TYPE__)(rhs), p_result) : \
	__PRIVATE_hybrid_overflow_size2(lhs, rhs) <= 2 ? __PRIVATE_hybrid_overflow_smul16_32((__INT16_TYPE__)(lhs), (__INT16_TYPE__)(rhs), p_result) : \
	                                                 __PRIVATE_hybrid_overflow_smul32_32((__INT32_TYPE__)(lhs), (__INT32_TYPE__)(rhs), p_result), 0)
#define __hybrid_overflow_smul(lhs, rhs, p_result) \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_smul8(lhs, rhs, (__INT8_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_smul16(lhs, rhs, (__INT16_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_smul32(lhs, rhs, (__INT32_TYPE__ *)(p_result)))
#endif /* !... */
#endif /* !__NO_builtin_choose_expr */
/*[[[end]]]*/
/* clang-format on */
#endif /* End:Fallback */


/* Optional variants that may compile faster when operand sizes are known to be fixed.
 * e.g.: `__hybrid_overflow_uadd8(__UINT8_TYPE__ a, __UINT8_TYPE__ b, __UINT8_TYPE__ *c)'
 *       `__hybrid_overflow_sadd8(__INT8_TYPE__ a, __INT8_TYPE__ b, __INT8_TYPE__ *c)'
 * etc... */
#ifndef __hybrid_overflow_uadd8
#define __hybrid_overflow_uadd8  __hybrid_overflow_uadd
#define __hybrid_overflow_sadd8  __hybrid_overflow_sadd
#define __hybrid_overflow_usub8  __hybrid_overflow_usub
#define __hybrid_overflow_ssub8  __hybrid_overflow_ssub
#define __hybrid_overflow_umul8  __hybrid_overflow_umul
#define __hybrid_overflow_smul8  __hybrid_overflow_smul
#define __hybrid_overflow_uadd16 __hybrid_overflow_uadd
#define __hybrid_overflow_sadd16 __hybrid_overflow_sadd
#define __hybrid_overflow_usub16 __hybrid_overflow_usub
#define __hybrid_overflow_ssub16 __hybrid_overflow_ssub
#define __hybrid_overflow_umul16 __hybrid_overflow_umul
#define __hybrid_overflow_smul16 __hybrid_overflow_smul
#define __hybrid_overflow_uadd32 __hybrid_overflow_uadd
#define __hybrid_overflow_sadd32 __hybrid_overflow_sadd
#define __hybrid_overflow_usub32 __hybrid_overflow_usub
#define __hybrid_overflow_ssub32 __hybrid_overflow_ssub
#define __hybrid_overflow_umul32 __hybrid_overflow_umul
#define __hybrid_overflow_smul32 __hybrid_overflow_smul
#ifdef __UINT64_TYPE__
#define __hybrid_overflow_uadd64 __hybrid_overflow_uadd
#define __hybrid_overflow_sadd64 __hybrid_overflow_sadd
#define __hybrid_overflow_usub64 __hybrid_overflow_usub
#define __hybrid_overflow_ssub64 __hybrid_overflow_ssub
#define __hybrid_overflow_umul64 __hybrid_overflow_umul
#define __hybrid_overflow_smul64 __hybrid_overflow_smul
#ifdef __UINT128_TYPE__
#define __hybrid_overflow_uadd128 __hybrid_overflow_uadd
#define __hybrid_overflow_sadd128 __hybrid_overflow_sadd
#define __hybrid_overflow_usub128 __hybrid_overflow_usub
#define __hybrid_overflow_ssub128 __hybrid_overflow_ssub
#define __hybrid_overflow_umul128 __hybrid_overflow_umul
#define __hybrid_overflow_smul128 __hybrid_overflow_smul
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#endif /* !__hybrid_overflow_uadd8 */


/* >> bool __hybrid_overflow_sneg(T x, T *p_result);
 * >> bool __hybrid_overflow_sneg_p2n(T x, T *p_result);    -- @assume(x >= 0)
 * >> bool __hybrid_overflow_sneg_n2p(T x, T *p_result);    -- @assume(x < 0)
 * Do the operation `*p_result = -x'
 * @return: true:  Overflow happened
 * @return: false: Overflow didn't happen */
#ifdef __HYBRID_OVERFLOW_USES_BUILTINS
#define __hybrid_overflow_sneg(x, p_result) __hybrid_overflow_ssub(0, x, p_result)
#define __hybrid_overflow_sneg8(x, p_result) __hybrid_overflow_ssub8(0, x, p_result)
#define __hybrid_overflow_sneg16(x, p_result) __hybrid_overflow_ssub16(0, x, p_result)
#define __hybrid_overflow_sneg32(x, p_result) __hybrid_overflow_ssub32(0, x, p_result)
#ifdef __UINT64_TYPE__
#define __hybrid_overflow_sneg64(x, p_result) __hybrid_overflow_ssub64(0, x, p_result)
#ifdef __UINT128_TYPE__
#define __hybrid_overflow_sneg128(x, p_result) __hybrid_overflow_ssub128(0, x, p_result)
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#else /* __HYBRID_OVERFLOW_USES_BUILTINS */
#ifdef __NO_builtin_expect
#define __hybrid_overflow_sneg8(x, p_result)  (((__UINT8_TYPE__)(*(p_result) = (__INT8_TYPE__)-(__UINT8_TYPE__)(x))) == __UINT8_C(0x80))
#define __hybrid_overflow_sneg16(x, p_result) (((__UINT16_TYPE__)(*(p_result) = (__INT16_TYPE__)-(__UINT16_TYPE__)(x))) == __UINT16_C(0x8000))
#define __hybrid_overflow_sneg32(x, p_result) (((__UINT32_TYPE__)(*(p_result) = (__INT32_TYPE__)-(__UINT32_TYPE__)(x))) == __UINT32_C(0x80000000))
#ifdef __UINT64_TYPE__
#define __hybrid_overflow_sneg64(x, p_result) (((__UINT64_TYPE__)(*(p_result) = (__INT64_TYPE__)-(__UINT64_TYPE__)(x))) == __UINT64_C(0x8000000000000000))
#ifdef __UINT128_TYPE__
#define __hybrid_overflow_sneg128(x, p_result) (((__UINT128_TYPE__)(*(p_result) = (__INT128_TYPE__)-(__UINT128_TYPE__)(x))) == __UINT128_C(0x80000000000000000000000000000000))
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#else /* __NO_builtin_expect */
#define __hybrid_overflow_sneg8(x, p_result)  __builtin_expect(((__UINT8_TYPE__)(*(p_result) = (__INT8_TYPE__)-(__UINT8_TYPE__)(x))) == __UINT8_C(0x80), 0)
#define __hybrid_overflow_sneg16(x, p_result) __builtin_expect(((__UINT16_TYPE__)(*(p_result) = (__INT16_TYPE__)-(__UINT16_TYPE__)(x))) == __UINT16_C(0x8000), 0)
#define __hybrid_overflow_sneg32(x, p_result) __builtin_expect(((__UINT32_TYPE__)(*(p_result) = (__INT32_TYPE__)-(__UINT32_TYPE__)(x))) == __UINT32_C(0x80000000), 0)
#ifdef __UINT64_TYPE__
#define __hybrid_overflow_sneg64(x, p_result) __builtin_expect(((__UINT64_TYPE__)(*(p_result) = (__INT64_TYPE__)-(__UINT64_TYPE__)(x))) == __UINT64_C(0x8000000000000000), 0)
#ifdef __UINT128_TYPE__
#define __hybrid_overflow_sneg128(x, p_result) __builtin_expect(((__UINT128_TYPE__)(*(p_result) = (__INT128_TYPE__)-(__UINT128_TYPE__)(x))) == __UINT128_C(0x80000000000000000000000000000000), 0)
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#endif /* !__NO_builtin_expect */
#ifdef __NO_builtin_choose_expr
#ifdef __UINT128_TYPE__
#define __hybrid_overflow_sneg(x, p_result)                                                 \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_sneg8(x, (__INT8_TYPE__ *)(p_result)) :   \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_sneg16(x, (__INT16_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_overflow_sneg32(x, (__INT32_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 8 ? __hybrid_overflow_sneg64(x, (__INT64_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_sneg128(x, (__INT128_TYPE__ *)(p_result)))
#elif defined(__UINT64_TYPE__)
#define __hybrid_overflow_sneg(x, p_result)                                                 \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_sneg8(x, (__INT8_TYPE__ *)(p_result)) :   \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_sneg16(x, (__INT16_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_overflow_sneg32(x, (__INT32_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_sneg64(x, (__INT64_TYPE__ *)(p_result)))
#else /* ... */
#define __hybrid_overflow_sneg(x, p_result)                                                 \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_sneg8(x, (__INT8_TYPE__ *)(p_result)) :   \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_sneg16(x, (__INT16_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_sneg32(x, (__INT32_TYPE__ *)(p_result)))
#endif /* !... */
#else /* __NO_builtin_choose_expr */
#ifdef __UINT128_TYPE__
#define __hybrid_overflow_sneg(x, p_result)                                                                    \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_sneg8(x, (__INT8_TYPE__ *)(p_result)),   \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_sneg16(x, (__INT16_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_overflow_sneg32(x, (__INT32_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 8, __hybrid_overflow_sneg64(x, (__INT64_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_sneg128(x, (__INT128_TYPE__ *)(p_result))))))
#elif defined(__UINT64_TYPE__)
#define __hybrid_overflow_sneg(x, p_result)                                                                    \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_sneg8(x, (__INT8_TYPE__ *)(p_result)),   \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_sneg16(x, (__INT16_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_overflow_sneg32(x, (__INT32_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_sneg64(x, (__INT64_TYPE__ *)(p_result)))))
#else /* ... */
#define __hybrid_overflow_sneg(x, p_result)                                                                    \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_sneg8(x, (__INT8_TYPE__ *)(p_result)),   \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_sneg16(x, (__INT16_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_sneg32(x, (__INT32_TYPE__ *)(p_result))))
#endif /* !... */
#endif /* !__NO_builtin_choose_expr */
#endif /* !__HYBRID_OVERFLOW_USES_BUILTINS */
#ifdef NDEBUG
#define __hybrid_overflow_sneg8_p2n(x, p_result)  (*(p_result) = (__INT8_TYPE__)-(__UINT8_TYPE__)(x), 0)
#define __hybrid_overflow_sneg16_p2n(x, p_result) (*(p_result) = (__INT16_TYPE__)-(__UINT16_TYPE__)(x), 0)
#define __hybrid_overflow_sneg32_p2n(x, p_result) (*(p_result) = (__INT32_TYPE__)-(__UINT32_TYPE__)(x), 0)
#ifdef __UINT64_TYPE__
#define __hybrid_overflow_sneg64_p2n(x, p_result) (*(p_result) = (__INT64_TYPE__)-(__UINT64_TYPE__)(x), 0)
#ifdef __UINT128_TYPE__
#define __hybrid_overflow_sneg128_p2n(x, p_result) (*(p_result) = (__INT128_TYPE__)-(__UINT128_TYPE__)(x), 0)
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#else /* NDEBUG */
#define __hybrid_overflow_sneg8_p2n(x, p_result)  (__hybrid_asserte((__INT8_TYPE__)(*(p_result) = (__INT8_TYPE__)-(__UINT8_TYPE__)(x)) < 0), 0)
#define __hybrid_overflow_sneg16_p2n(x, p_result) (__hybrid_asserte((__INT16_TYPE__)(*(p_result) = (__INT16_TYPE__)-(__UINT16_TYPE__)(x)) < 0), 0)
#define __hybrid_overflow_sneg32_p2n(x, p_result) (__hybrid_asserte((__INT32_TYPE__)(*(p_result) = (__INT32_TYPE__)-(__UINT32_TYPE__)(x)) < 0), 0)
#ifdef __UINT64_TYPE__
#define __hybrid_overflow_sneg64_p2n(x, p_result) (__hybrid_asserte((__INT64_TYPE__)(*(p_result) = (__INT64_TYPE__)-(__UINT64_TYPE__)(x)) < 0), 0)
#ifdef __UINT128_TYPE__
#define __hybrid_overflow_sneg128_p2n(x, p_result) (__hybrid_asserte((__INT128_TYPE__)(*(p_result) = (__INT128_TYPE__)-(__UINT128_TYPE__)(x)) < 0), 0)
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#endif /* !NDEBUG */
#ifdef __NO_builtin_choose_expr
#ifdef __UINT128_TYPE__
#define __hybrid_overflow_sneg_p2n(x, p_result)                                                 \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_sneg8_p2n(x, (__INT8_TYPE__ *)(p_result)) :   \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_sneg16_p2n(x, (__INT16_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_overflow_sneg32_p2n(x, (__INT32_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 8 ? __hybrid_overflow_sneg64_p2n(x, (__INT64_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_sneg128_p2n(x, (__INT128_TYPE__ *)(p_result)))
#elif defined(__UINT64_TYPE__)
#define __hybrid_overflow_sneg_p2n(x, p_result)                                                 \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_sneg8_p2n(x, (__INT8_TYPE__ *)(p_result)) :   \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_sneg16_p2n(x, (__INT16_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_overflow_sneg32_p2n(x, (__INT32_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_sneg64_p2n(x, (__INT64_TYPE__ *)(p_result)))
#else /* ... */
#define __hybrid_overflow_sneg_p2n(x, p_result)                                                 \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_sneg8_p2n(x, (__INT8_TYPE__ *)(p_result)) :   \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_sneg16_p2n(x, (__INT16_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_sneg32_p2n(x, (__INT32_TYPE__ *)(p_result)))
#endif /* !... */
#else /* __NO_builtin_choose_expr */
#ifdef __UINT128_TYPE__
#define __hybrid_overflow_sneg_p2n(x, p_result)                                                                    \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_sneg8_p2n(x, (__INT8_TYPE__ *)(p_result)),   \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_sneg16_p2n(x, (__INT16_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_overflow_sneg32_p2n(x, (__INT32_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 8, __hybrid_overflow_sneg64_p2n(x, (__INT64_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_sneg128_p2n(x, (__INT128_TYPE__ *)(p_result))))))
#elif defined(__UINT64_TYPE__)
#define __hybrid_overflow_sneg_p2n(x, p_result)                                                                    \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_sneg8_p2n(x, (__INT8_TYPE__ *)(p_result)),   \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_sneg16_p2n(x, (__INT16_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_overflow_sneg32_p2n(x, (__INT32_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_sneg64_p2n(x, (__INT64_TYPE__ *)(p_result)))))
#else /* ... */
#define __hybrid_overflow_sneg_p2n(x, p_result)                                                                    \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_sneg8_p2n(x, (__INT8_TYPE__ *)(p_result)),   \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_sneg16_p2n(x, (__INT16_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_sneg32_p2n(x, (__INT32_TYPE__ *)(p_result))))
#endif /* !... */
#endif /* !__NO_builtin_choose_expr */
#define __hybrid_overflow_sneg_n2p   __hybrid_overflow_sneg
#define __hybrid_overflow_sneg8_n2p  __hybrid_overflow_sneg8
#define __hybrid_overflow_sneg16_n2p __hybrid_overflow_sneg16
#define __hybrid_overflow_sneg32_n2p __hybrid_overflow_sneg32
#ifdef __UINT64_TYPE__
#define __hybrid_overflow_sneg64_n2p __hybrid_overflow_sneg64
#ifdef __UINT128_TYPE__
#define __hybrid_overflow_sneg128_n2p __hybrid_overflow_sneg128
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */



/* >> bool __hybrid_overflow_scast(V x, T *p_result);
 * >> bool __hybrid_overflow_ucast(V x, T *p_result);
 * Do the operation `*p_result = (T)x'
 * @return: true:  Overflow happened
 * @return: false: Overflow didn't happen */
#define __hybrid_overflow_ucast8(x, p_result)  __builtin_expect((*(p_result) = (__UINT8_TYPE__)(x)) != (x) && sizeof(x) > 1, 0)
#define __hybrid_overflow_ucast16(x, p_result) __builtin_expect((*(p_result) = (__UINT16_TYPE__)(x)) != (x) && sizeof(x) > 2, 0)
#define __hybrid_overflow_ucast32(x, p_result) __builtin_expect((*(p_result) = (__UINT32_TYPE__)(x)) != (x) && sizeof(x) > 4, 0)
#define __hybrid_overflow_scast8(x, p_result)  __builtin_expect((*(p_result) = (__INT8_TYPE__)(x)) != (x) && sizeof(x) > 1, 0)
#define __hybrid_overflow_scast16(x, p_result) __builtin_expect((*(p_result) = (__INT16_TYPE__)(x)) != (x) && sizeof(x) > 2, 0)
#define __hybrid_overflow_scast32(x, p_result) __builtin_expect((*(p_result) = (__INT32_TYPE__)(x)) != (x) && sizeof(x) > 4, 0)
#ifdef __UINT64_TYPE__
#define __hybrid_overflow_ucast64(x, p_result) __builtin_expect((*(p_result) = (__UINT64_TYPE__)(x)) != (x) && sizeof(x) > 8, 0)
#define __hybrid_overflow_scast64(x, p_result) __builtin_expect((*(p_result) = (__INT64_TYPE__)(x)) != (x) && sizeof(x) > 8, 0)
#ifdef __UINT128_TYPE__
#define __hybrid_overflow_ucast128(x, p_result) __builtin_expect((*(p_result) = (__UINT128_TYPE__)(x)) != (x) && sizeof(x) > 8, 0)
#define __hybrid_overflow_scast128(x, p_result) __builtin_expect((*(p_result) = (__INT128_TYPE__)(x)) != (x) && sizeof(x) > 8, 0)
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#ifdef __COMPILER_HAVE_TYPEOF
#define __hybrid_overflow_ucast(x, p_result) __builtin_expect((*(p_result) = (__typeof__(*(p_result)))(x)) != (x) && sizeof(x) > sizeof(*(p_result)), 0)
#define __hybrid_overflow_scast(x, p_result) __builtin_expect((*(p_result) = (__typeof__(*(p_result)))(x)) != (x) && sizeof(x) > sizeof(*(p_result)), 0)
#elif !defined(__NO_builtin_choose_expr)
#ifdef __UINT128_TYPE__
#define __hybrid_overflow_ucast(x, p_result)                                                \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_ucast8(x, p_result),  \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_ucast16(x, p_result), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_overflow_ucast32(x, p_result), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 8, __hybrid_overflow_ucast64(x, p_result), \
	                                                __hybrid_overflow_ucast128(x, p_result)))))
#define __hybrid_overflow_scast(x, p_result)                                                \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_scast8(x, p_result),  \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_scast16(x, p_result), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_overflow_scast32(x, p_result), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 8, __hybrid_overflow_scast64(x, p_result), \
	                                                __hybrid_overflow_scast128(x, p_result)))))
#elif defined(__UINT64_TYPE__)
#define __hybrid_overflow_ucast(x, p_result)                                                \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_ucast8(x, p_result),  \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_ucast16(x, p_result), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_overflow_ucast32(x, p_result), \
	                                                __hybrid_overflow_ucast64(x, p_result))))
#define __hybrid_overflow_scast(x, p_result)                                                \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_scast8(x, p_result),  \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_scast16(x, p_result), \
	__builtin_choose_expr(sizeof(*(p_result)) <= 4, __hybrid_overflow_scast32(x, p_result), \
	                                                __hybrid_overflow_scast64(x, p_result))))
#else /* ... */
#define __hybrid_overflow_ucast(x, p_result)                                                \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_ucast8(x, p_result),  \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_ucast16(x, p_result), \
	                                                __hybrid_overflow_ucast32(x, p_result)))
#define __hybrid_overflow_scast(x, p_result)                                                \
	__builtin_choose_expr(sizeof(*(p_result)) <= 1, __hybrid_overflow_scast8(x, p_result),  \
	__builtin_choose_expr(sizeof(*(p_result)) <= 2, __hybrid_overflow_scast16(x, p_result), \
	                                                __hybrid_overflow_scast32(x, p_result)))
#endif /* !... */
#else /* ... */
#ifdef __UINT128_TYPE__
#define __hybrid_overflow_ucast(x, p_result)                             \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_ucast8(x, p_result) :  \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_ucast16(x, p_result) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_overflow_ucast32(x, p_result) : \
	 sizeof(*(p_result)) <= 8 ? __hybrid_overflow_ucast64(x, p_result) : \
	                            __hybrid_overflow_ucast128(x, p_result))
#define __hybrid_overflow_scast(x, p_result)                             \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_scast8(x, p_result) :  \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_scast16(x, p_result) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_overflow_scast32(x, p_result) : \
	 sizeof(*(p_result)) <= 8 ? __hybrid_overflow_scast64(x, p_result) : \
	                            __hybrid_overflow_scast128(x, p_result))
#elif defined(__UINT64_TYPE__)
#define __hybrid_overflow_ucast(x, p_result)                             \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_ucast8(x, p_result) :  \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_ucast16(x, p_result) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_overflow_ucast32(x, p_result) : \
	                            __hybrid_overflow_ucast64(x, p_result))
#define __hybrid_overflow_scast(x, p_result)                             \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_scast8(x, p_result) :  \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_scast16(x, p_result) : \
	 sizeof(*(p_result)) <= 4 ? __hybrid_overflow_scast32(x, p_result) : \
	                            __hybrid_overflow_scast64(x, p_result))
#else /* ... */
#define __hybrid_overflow_ucast(x, p_result)                             \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_ucast8(x, p_result) :  \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_ucast16(x, p_result) : \
	                            __hybrid_overflow_ucast32(x, p_result))
#define __hybrid_overflow_scast(x, p_result)                             \
	(sizeof(*(p_result)) <= 1 ? __hybrid_overflow_scast8(x, p_result) :  \
	 sizeof(*(p_result)) <= 2 ? __hybrid_overflow_scast16(x, p_result) : \
	                            __hybrid_overflow_scast32(x, p_result))
#endif /* !... */
#endif /* !... */

#endif /* !__GUARD_HYBRID___OVERFLOW_H */
