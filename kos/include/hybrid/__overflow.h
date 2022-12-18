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
#ifndef __GUARD_HYBRID___OVERFLOW_H
#define __GUARD_HYBRID___OVERFLOW_H 1

#include "../__stdinc.h"
#include "__assert.h"
#include "limitcore.h"
#include "typecore.h"

__DECL_BEGIN

#ifdef ____INTELLISENSE_STDINC_COMMON_H
/* @return: true:  Overflow  occurred (unlikely; `*res' contains the truncated result)
 *                 Overflow here means that the finite result stored in `*res' doesn't
 *                 match a value that would have been produced when infinite precision
 *                 was available.
 *                 e.g.: `UINT_MAX + 42u' and `11u - 19u' overflow, but `32u + 42u'
 *                       or `11 - 19' don't
 * @return: false: `*res' contains the correct result. */
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
/* @return: true:  Overflow  occurred (unlikely; `*res' contains the truncated result)
 *                 Overflow here means that the finite result stored in `*res' doesn't
 *                 match a value that would have been produced when infinite precision
 *                 was available.
 *                 e.g.: `UINT_MAX + 42u' and `11u - 19u' overflow, but `32u + 42u'
 *                       or `11 - 19' don't
 * @return: false: `*res' contains the correct result. */
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

#ifndef __cplusplus
#define __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, opn, resn, x, y, res)   \
	__IMPL_HYBRID_OVERFLOW_NAME(name, opn, resn)((Tpfx##opn##_TYPE__)(x), \
	                                             (Tpfx##opn##_TYPE__)(y), \
	                                             (Tpfx##resn##_TYPE__ *)(res))
#ifdef __NO_builtin_choose_expr
#ifndef __INT64_TYPE__
#define __IMPL_HYBRID_OVERFLOW_SELECT_8(name, Tpfx, x, y, res)                                          \
	((sizeof(x) <= 1 && sizeof(y) <= 1) ? __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 8, 8, x, y, res) :  \
	 (sizeof(x) <= 2 && sizeof(y) <= 2) ? __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 16, 8, x, y, res) : \
	                                      __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 32, 8, x, y, res))
#define __IMPL_HYBRID_OVERFLOW_SELECT_16(name, Tpfx, x, y, res)                                          \
	((sizeof(x) <= 2 && sizeof(y) <= 2) ? __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 16, 16, x, y, res) : \
	                                      __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 32, 16, x, y, res))
#define __IMPL_HYBRID_OVERFLOW_SELECT_32(name, Tpfx, x, y, res) \
        __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 32, 32, x, y, res)
#define __IMPL_HYBRID_OVERFLOW_SELECT(name, Tpfx, x, y, res)                         \
	(sizeof(*(res)) == 1 ? __IMPL_HYBRID_OVERFLOW_SELECT_8(name, Tpfx, x, y, res) :  \
	 sizeof(*(res)) == 2 ? __IMPL_HYBRID_OVERFLOW_SELECT_16(name, Tpfx, x, y, res) : \
	                       __IMPL_HYBRID_OVERFLOW_SELECT_32(name, Tpfx, x, y, res))
#elif !defined(__INT128_TYPE__) /* With 64-bit integer type */
#define __IMPL_HYBRID_OVERFLOW_SELECT_8(name, Tpfx, x, y, res)                                          \
	((sizeof(x) <= 1 && sizeof(y) <= 1) ? __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 8, 8, x, y, res) :  \
	 (sizeof(x) <= 2 && sizeof(y) <= 2) ? __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 16, 8, x, y, res) : \
	 (sizeof(x) <= 4 && sizeof(y) <= 4) ? __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 32, 8, x, y, res) : \
	                                      __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 64, 8, x, y, res))
#define __IMPL_HYBRID_OVERFLOW_SELECT_16(name, Tpfx, x, y, res)                                          \
	((sizeof(x) <= 2 && sizeof(y) <= 2) ? __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 16, 16, x, y, res) : \
	 (sizeof(x) <= 4 && sizeof(y) <= 4) ? __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 32, 16, x, y, res) : \
	                                      __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 64, 16, x, y, res))
#define __IMPL_HYBRID_OVERFLOW_SELECT_32(name, Tpfx, x, y, res)                                          \
	((sizeof(x) <= 4 && sizeof(y) <= 4) ? __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 32, 32, x, y, res) : \
	                                      __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 64, 32, x, y, res))
#define __IMPL_HYBRID_OVERFLOW_SELECT_64(name, Tpfx, x, y, res) \
        __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 64, 64, x, y, res)
#define __IMPL_HYBRID_OVERFLOW_SELECT(name, Tpfx, x, y, res)                         \
	(sizeof(*(res)) == 1 ? __IMPL_HYBRID_OVERFLOW_SELECT_8(name, Tpfx, x, y, res) :  \
	 sizeof(*(res)) == 2 ? __IMPL_HYBRID_OVERFLOW_SELECT_16(name, Tpfx, x, y, res) : \
	 sizeof(*(res)) == 4 ? __IMPL_HYBRID_OVERFLOW_SELECT_32(name, Tpfx, x, y, res) : \
	                       __IMPL_HYBRID_OVERFLOW_SELECT_64(name, Tpfx, x, y, res))
#else /* With 128-bit integer type */
#define __IMPL_HYBRID_OVERFLOW_SELECT_8(name, Tpfx, x, y, res)                                          \
	((sizeof(x) <= 1 && sizeof(y) <= 1) ? __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 8, 8, x, y, res) :  \
	 (sizeof(x) <= 2 && sizeof(y) <= 2) ? __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 16, 8, x, y, res) : \
	 (sizeof(x) <= 4 && sizeof(y) <= 4) ? __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 32, 8, x, y, res) : \
	 (sizeof(x) <= 8 && sizeof(y) <= 8) ? __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 64, 8, x, y, res) : \
	                                      __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 128, 8, x, y, res))
#define __IMPL_HYBRID_OVERFLOW_SELECT_16(name, Tpfx, x, y, res)                                          \
	((sizeof(x) <= 2 && sizeof(y) <= 2) ? __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 16, 16, x, y, res) : \
	 (sizeof(x) <= 4 && sizeof(y) <= 4) ? __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 32, 16, x, y, res) : \
	 (sizeof(x) <= 8 && sizeof(y) <= 8) ? __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 64, 16, x, y, res) : \
	                                      __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 128, 16, x, y, res))
#define __IMPL_HYBRID_OVERFLOW_SELECT_32(name, Tpfx, x, y, res)                                          \
	((sizeof(x) <= 4 && sizeof(y) <= 4) ? __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 32, 32, x, y, res) : \
	 (sizeof(x) <= 8 && sizeof(y) <= 8) ? __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 64, 32, x, y, res) : \
	                                      __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 128, 32, x, y, res))
#define __IMPL_HYBRID_OVERFLOW_SELECT_64(name, Tpfx, x, y, res)                                          \
	((sizeof(x) <= 8 && sizeof(y) <= 8) ? __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 64, 64, x, y, res) : \
	                                      __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 128, 64, x, y, res))
#define __IMPL_HYBRID_OVERFLOW_SELECT_128(name, Tpfx, x, y, res) \
        __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 128, 128, x, y, res)
#define __IMPL_HYBRID_OVERFLOW_SELECT(name, Tpfx, x, y, res)                         \
	(sizeof(*(res)) == 1 ? __IMPL_HYBRID_OVERFLOW_SELECT_8(name, Tpfx, x, y, res) :  \
	 sizeof(*(res)) == 2 ? __IMPL_HYBRID_OVERFLOW_SELECT_16(name, Tpfx, x, y, res) : \
	 sizeof(*(res)) == 4 ? __IMPL_HYBRID_OVERFLOW_SELECT_32(name, Tpfx, x, y, res) : \
	 sizeof(*(res)) == 8 ? __IMPL_HYBRID_OVERFLOW_SELECT_64(name, Tpfx, x, y, res) : \
	                       __IMPL_HYBRID_OVERFLOW_SELECT_128(name, Tpfx, x, y, res))
#endif
#else /* __NO_builtin_choose_expr */
#ifndef __INT64_TYPE__
#define __IMPL_HYBRID_OVERFLOW_SELECT_8(name, Tpfx, x, y, res)                                                           \
	__builtin_choose_expr(sizeof(x) <= 1 && sizeof(y) <= 1, __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 8, 8, x, y, res),  \
	__builtin_choose_expr(sizeof(x) <= 2 && sizeof(y) <= 2, __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 16, 8, x, y, res), \
	                                                        __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 32, 8, x, y, res)))
#define __IMPL_HYBRID_OVERFLOW_SELECT_16(name, Tpfx, x, y, res)                                                           \
	__builtin_choose_expr(sizeof(x) <= 2 && sizeof(y) <= 2, __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 16, 16, x, y, res), \
	                                                        __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 32, 16, x, y, res))
#define __IMPL_HYBRID_OVERFLOW_SELECT_32(name, Tpfx, x, y, res) \
        __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 32, 32, x, y, res)
#define __IMPL_HYBRID_OVERFLOW_SELECT(name, Tpfx, x, y, res)                                            \
	__builtin_choose_expr(sizeof(*(res)) == 1, __IMPL_HYBRID_OVERFLOW_SELECT_8(name, Tpfx, x, y, res),  \
	__builtin_choose_expr(sizeof(*(res)) == 2, __IMPL_HYBRID_OVERFLOW_SELECT_16(name, Tpfx, x, y, res), \
	                                          __IMPL_HYBRID_OVERFLOW_SELECT_32(name, Tpfx, x, y, res)))
#elif !defined(__INT128_TYPE__) /* With 64-bit integer type */
#define __IMPL_HYBRID_OVERFLOW_SELECT_8(name, Tpfx, x, y, res)                                                           \
	__builtin_choose_expr(sizeof(x) <= 1 && sizeof(y) <= 1, __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 8, 8, x, y, res),  \
	__builtin_choose_expr(sizeof(x) <= 2 && sizeof(y) <= 2, __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 16, 8, x, y, res), \
	__builtin_choose_expr(sizeof(x) <= 4 && sizeof(y) <= 4, __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 32, 8, x, y, res), \
	                                                        __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 64, 8, x, y, res))))
#define __IMPL_HYBRID_OVERFLOW_SELECT_16(name, Tpfx, x, y, res)                                                           \
	__builtin_choose_expr(sizeof(x) <= 2 && sizeof(y) <= 2, __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 16, 16, x, y, res), \
	__builtin_choose_expr(sizeof(x) <= 4 && sizeof(y) <= 4, __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 32, 16, x, y, res), \
	                                                        __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 64, 16, x, y, res)))
#define __IMPL_HYBRID_OVERFLOW_SELECT_32(name, Tpfx, x, y, res)                                                           \
	__builtin_choose_expr(sizeof(x) <= 4 && sizeof(y) <= 4, __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 32, 32, x, y, res), \
	                                                        __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 64, 32, x, y, res))
#define __IMPL_HYBRID_OVERFLOW_SELECT_64(name, Tpfx, x, y, res) \
        __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 64, 64, x, y, res)
#define __IMPL_HYBRID_OVERFLOW_SELECT(name, Tpfx, x, y, res)                                            \
	__builtin_choose_expr(sizeof(*(res)) == 1, __IMPL_HYBRID_OVERFLOW_SELECT_8(name, Tpfx, x, y, res),  \
	__builtin_choose_expr(sizeof(*(res)) == 2, __IMPL_HYBRID_OVERFLOW_SELECT_16(name, Tpfx, x, y, res), \
	__builtin_choose_expr(sizeof(*(res)) == 4, __IMPL_HYBRID_OVERFLOW_SELECT_32(name, Tpfx, x, y, res), \
	                                           __IMPL_HYBRID_OVERFLOW_SELECT_64(name, Tpfx, x, y, res))))
#else /* With 128-bit integer type */
#define __IMPL_HYBRID_OVERFLOW_SELECT_8(name, Tpfx, x, y, res)                                                           \
	__builtin_choose_expr(sizeof(x) <= 1 && sizeof(y) <= 1, __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 8, 8, x, y, res),  \
	__builtin_choose_expr(sizeof(x) <= 2 && sizeof(y) <= 2, __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 16, 8, x, y, res), \
	__builtin_choose_expr(sizeof(x) <= 4 && sizeof(y) <= 4, __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 32, 8, x, y, res), \
	__builtin_choose_expr(sizeof(x) <= 8 && sizeof(y) <= 8, __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 64, 8, x, y, res), \
	                                                        __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 128, 8, x, y, res)))))
#define __IMPL_HYBRID_OVERFLOW_SELECT_16(name, Tpfx, x, y, res)                                                           \
	__builtin_choose_expr(sizeof(x) <= 2 && sizeof(y) <= 2, __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 16, 16, x, y, res), \
	__builtin_choose_expr(sizeof(x) <= 4 && sizeof(y) <= 4, __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 32, 16, x, y, res), \
	__builtin_choose_expr(sizeof(x) <= 8 && sizeof(y) <= 8, __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 64, 16, x, y, res), \
	                                                        __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 128, 16, x, y, res))))
#define __IMPL_HYBRID_OVERFLOW_SELECT_32(name, Tpfx, x, y, res)                                                           \
	__builtin_choose_expr(sizeof(x) <= 4 && sizeof(y) <= 4, __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 32, 32, x, y, res), \
	__builtin_choose_expr(sizeof(x) <= 8 && sizeof(y) <= 8, __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 64, 32, x, y, res), \
	                                                        __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 128, 32, x, y, res)))
#define __IMPL_HYBRID_OVERFLOW_SELECT_64(name, Tpfx, x, y, res)                                                           \
	__builtin_choose_expr(sizeof(x) <= 8 && sizeof(y) <= 8, __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 64, 64, x, y, res), \
	                                                        __IMPL_HYBRID_OVERFLOW_INVOKE(name, Tpfx, 128, 64, x, y, res))
#define __IMPL_HYBRID_OVERFLOW_SELECT(name, Tpfx, x, y, res)                                            \
	__builtin_choose_expr(sizeof(*(res)) == 1, __IMPL_HYBRID_OVERFLOW_SELECT_8(name, Tpfx, x, y, res),  \
	__builtin_choose_expr(sizeof(*(res)) == 2, __IMPL_HYBRID_OVERFLOW_SELECT_16(name, Tpfx, x, y, res), \
	__builtin_choose_expr(sizeof(*(res)) == 4, __IMPL_HYBRID_OVERFLOW_SELECT_32(name, Tpfx, x, y, res), \
	__builtin_choose_expr(sizeof(*(res)) == 8, __IMPL_HYBRID_OVERFLOW_SELECT_64(name, Tpfx, x, y, res), \
	                                           __IMPL_HYBRID_OVERFLOW_SELECT_128(name, Tpfx, x, y, res)))))
#endif
#endif /* !__NO_builtin_choose_expr */
#define __IMPL_HYBRID_OVERFLOW_NAME(name, opn, resn)         name##opn##_##resn
#else /* !__cplusplus */
#define __IMPL_HYBRID_OVERFLOW_SELECT(name, Tpfx, x, y, res) name(x, y, res)
#define __IMPL_HYBRID_OVERFLOW_NAME(name, opn, resn)         name
extern "C++" {
#endif /* __cplusplus */

#define __IMPL_HYBRID_DEFINE_PROMOTION_MATH(opn, n, opn_x2)                                           \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                               \
	__NOTHROW_NCX(__IMPL_HYBRID_OVERFLOW_NAME(__impl_hybrid_overflow_uadd, opn, n))                   \
	(__UINT##opn##_TYPE__ __x, __UINT##opn##_TYPE__ __y, __UINT##n##_TYPE__ *__restrict __res) {      \
		__UINT##opn_x2##_TYPE__ __true_res = (__UINT##opn_x2##_TYPE__)((__UINT##opn_x2##_TYPE__)__x + \
		                                                               (__UINT##opn_x2##_TYPE__)__y); \
		__UINT##n##_TYPE__ __false_res = (__UINT##n##_TYPE__)__true_res;                              \
		*__res = __false_res;                                                                         \
		if ((__UINT##opn_x2##_TYPE__)__false_res != __true_res)                                       \
			return 1;                                                                                 \
		return 0;                                                                                     \
	}                                                                                                 \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                               \
	__NOTHROW_NCX(__IMPL_HYBRID_OVERFLOW_NAME(__impl_hybrid_overflow_sadd, opn, n))                   \
	(__INT##opn##_TYPE__ __x, __INT##opn##_TYPE__ __y, __INT##n##_TYPE__ *__restrict __res) {         \
		__INT##opn_x2##_TYPE__ __true_res = (__INT##opn_x2##_TYPE__)((__INT##opn_x2##_TYPE__)__x +    \
		                                                             (__INT##opn_x2##_TYPE__)__y);    \
		__INT##n##_TYPE__ __false_res = (__INT##n##_TYPE__)__true_res;                                \
		*__res = __false_res;                                                                         \
		if ((__INT##opn_x2##_TYPE__)__false_res != __true_res)                                        \
			return 1;                                                                                 \
		return 0;                                                                                     \
	}                                                                                                 \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                               \
	__NOTHROW_NCX(__IMPL_HYBRID_OVERFLOW_NAME(__impl_hybrid_overflow_usub, opn, n))                   \
	(__UINT##opn##_TYPE__ __x, __UINT##opn##_TYPE__ __y, __UINT##n##_TYPE__ *__restrict __res) {      \
		*__res = (__UINT##n##_TYPE__)(__x - __y);                                                     \
		if (!(__x >= __y))                                                                            \
			return 1;                                                                                 \
		return 0;                                                                                     \
	}                                                                                                 \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                               \
	__NOTHROW_NCX(__IMPL_HYBRID_OVERFLOW_NAME(__impl_hybrid_overflow_ssub, opn, n))                   \
	(__INT##opn##_TYPE__ __x, __INT##opn##_TYPE__ __y, __INT##n##_TYPE__ *__restrict __res) {         \
		__INT##opn_x2##_TYPE__ __true_res = (__INT##opn_x2##_TYPE__)((__INT##opn_x2##_TYPE__)__x -    \
		                                                             (__INT##opn_x2##_TYPE__)__y);    \
		__INT##n##_TYPE__ __false_res = (__INT##n##_TYPE__)__true_res;                                \
		*__res = __false_res;                                                                         \
		if ((__INT##opn_x2##_TYPE__)__false_res != __true_res)                                        \
			return 1;                                                                                 \
		return 0;                                                                                     \
	}                                                                                                 \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                               \
	__NOTHROW_NCX(__IMPL_HYBRID_OVERFLOW_NAME(__impl_hybrid_overflow_umul, opn, n))                   \
	(__UINT##opn##_TYPE__ __x, __UINT##opn##_TYPE__ __y, __UINT##n##_TYPE__ *__restrict __res) {      \
		__UINT##opn_x2##_TYPE__ __true_res = (__UINT##opn_x2##_TYPE__)((__UINT##opn_x2##_TYPE__)__x * \
		                                                               (__UINT##opn_x2##_TYPE__)__y); \
		__UINT##n##_TYPE__ __false_res = (__UINT##n##_TYPE__)__true_res;                              \
		*__res = __false_res;                                                                         \
		if ((__UINT##opn_x2##_TYPE__)__false_res != __true_res)                                       \
			return 1;                                                                                 \
		return 0;                                                                                     \
	}                                                                                                 \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                               \
	__NOTHROW_NCX(__IMPL_HYBRID_OVERFLOW_NAME(__impl_hybrid_overflow_smul, opn, n))                   \
	(__INT##opn##_TYPE__ __x, __INT##opn##_TYPE__ __y, __INT##n##_TYPE__ *__restrict __res) {         \
		__INT##opn_x2##_TYPE__ __true_res = (__INT##opn_x2##_TYPE__)((__INT##opn_x2##_TYPE__)__x *    \
		                                                             (__INT##opn_x2##_TYPE__)__y);    \
		__INT##n##_TYPE__ __false_res = (__INT##n##_TYPE__)__true_res;                                \
		*__res = __false_res;                                                                         \
		if ((__INT##opn_x2##_TYPE__)__false_res != __true_res)                                        \
			return 1;                                                                                 \
		return 0;                                                                                     \
	}

#define __IMPL_HYBRID_DEFINE_OVERFLOW_MATH(opn, n)                                               \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                          \
	__NOTHROW_NCX(__IMPL_HYBRID_OVERFLOW_NAME(__impl_hybrid_overflow_uadd, opn, n))              \
	(__UINT##opn##_TYPE__ __x, __UINT##opn##_TYPE__ __y, __UINT##n##_TYPE__ *__restrict __res) { \
		*__res = (__UINT##n##_TYPE__)(__x + __y);                                                \
		if (__x > (__UINT##opn##_MAX__ - __y))                                                   \
			return 1;                                                                            \
		return 0;                                                                                \
	}                                                                                            \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                          \
	__NOTHROW_NCX(__IMPL_HYBRID_OVERFLOW_NAME(__impl_hybrid_overflow_sadd, opn, n))              \
	(__INT##opn##_TYPE__ __x, __INT##opn##_TYPE__ __y, __INT##n##_TYPE__ *__restrict __res) {    \
		*__res = (__INT##n##_TYPE__)(__x + __y);                                                 \
		if ((__y > 0 && __x > (__INT##opn##_MAX__ - __y)) ||                                     \
		    (__y < 0 && __x < (__INT##opn##_MIN__ - __y)))                                       \
			return 1;                                                                            \
		return 0;                                                                                \
	}                                                                                            \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                          \
	__NOTHROW_NCX(__IMPL_HYBRID_OVERFLOW_NAME(__impl_hybrid_overflow_usub, opn, n))              \
	(__UINT##opn##_TYPE__ __x, __UINT##opn##_TYPE__ __y, __UINT##n##_TYPE__ *__restrict __res) { \
		*__res = (__UINT##n##_TYPE__)(__x - __y);                                                \
		if (!(__x >= __y))                                                                       \
			return 1;                                                                            \
		return 0;                                                                                \
	}                                                                                            \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                          \
	__NOTHROW_NCX(__IMPL_HYBRID_OVERFLOW_NAME(__impl_hybrid_overflow_ssub, opn, n))              \
	(__INT##opn##_TYPE__ __x, __INT##opn##_TYPE__ __y, __INT##n##_TYPE__ *__restrict __res) {    \
		*__res = (__INT##n##_TYPE__)(__x - __y);                                                 \
		if ((__y > 0 && __x < (__INT##opn##_MIN__ + __y)) ||                                     \
		    (__y < 0 && __x > (__INT##opn##_MAX__ + __y)))                                       \
			return 1;                                                                            \
		return 0;                                                                                \
	}                                                                                            \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                          \
	__NOTHROW_NCX(__IMPL_HYBRID_OVERFLOW_NAME(__impl_hybrid_overflow_umul, opn, n))              \
	(__UINT##opn##_TYPE__ __x, __UINT##opn##_TYPE__ __y, __UINT##n##_TYPE__ *__restrict __res) { \
		*__res = (__UINT##n##_TYPE__)(__x * __y);                                                \
		if (__x && __y && (__x > (__UINT##opn##_MAX__ / __y)))                                   \
			return 1;                                                                            \
		return 0;                                                                                \
	}                                                                                            \
	__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL                          \
	__NOTHROW_NCX(__IMPL_HYBRID_OVERFLOW_NAME(__impl_hybrid_overflow_smul, opn, n))              \
	(__INT##opn##_TYPE__ __x, __INT##opn##_TYPE__ __y, __INT##n##_TYPE__ *__restrict __res) {    \
		*__res = (__INT##n##_TYPE__)(__x * __y);                                                 \
		if (__x > 0) {                                                                           \
			if (__y > 0) {                                                                       \
				/* +x * +y */                                                                    \
				if (__x > (__INT##opn##_MAX__ / __y))                                            \
					return 1;                                                                    \
			} else {                                                                             \
				/* +x * -y */                                                                    \
				if (__y < (__INT##opn##_MIN__ / __x))                                            \
					return 1;                                                                    \
			}                                                                                    \
		} else if (__y > 0) {                                                                    \
			/* -x * +y */                                                                        \
			if (__x < (__INT##opn##_MIN__ / __y))                                                \
				return 1;                                                                        \
		} else {                                                                                 \
			/* -x * -y */                                                                        \
			if (__x && (__y < (__INT##opn##_MAX__ / __x)))                                       \
				return 1;                                                                        \
		}                                                                                        \
		return 0;                                                                                \
	}


#if __SIZEOF_REGISTER__ >= 2
__IMPL_HYBRID_DEFINE_PROMOTION_MATH(8, 8, 16)
#else /* __SIZEOF_REGISTER__ >= 2 */
__IMPL_HYBRID_DEFINE_OVERFLOW_MATH(8, 8)
#endif /* __SIZEOF_REGISTER__ < 2 */
#if __SIZEOF_REGISTER__ >= 4
__IMPL_HYBRID_DEFINE_PROMOTION_MATH(16, 8, 32)
__IMPL_HYBRID_DEFINE_PROMOTION_MATH(16, 16, 32)
#else /* __SIZEOF_REGISTER__ >= 4 */
__IMPL_HYBRID_DEFINE_OVERFLOW_MATH(16, 8)
__IMPL_HYBRID_DEFINE_OVERFLOW_MATH(16, 16)
#endif /* __SIZEOF_REGISTER__ < 4 */
#if __SIZEOF_REGISTER__ >= 8 && defined(__INT64_TYPE__)
__IMPL_HYBRID_DEFINE_PROMOTION_MATH(32, 8, 64)
__IMPL_HYBRID_DEFINE_PROMOTION_MATH(32, 16, 64)
__IMPL_HYBRID_DEFINE_PROMOTION_MATH(32, 32, 64)
#else /* __SIZEOF_REGISTER__ >= 8 && __INT64_TYPE__ */
__IMPL_HYBRID_DEFINE_OVERFLOW_MATH(32, 8)
__IMPL_HYBRID_DEFINE_OVERFLOW_MATH(32, 16)
__IMPL_HYBRID_DEFINE_OVERFLOW_MATH(32, 32)
#endif /* __SIZEOF_REGISTER__ < 8 || !__INT64_TYPE__ */
#ifdef __INT64_TYPE__
#if __SIZEOF_REGISTER__ >= 16 && defined(__INT128_TYPE__)
__IMPL_HYBRID_DEFINE_PROMOTION_MATH(64, 8, 128)
__IMPL_HYBRID_DEFINE_PROMOTION_MATH(64, 16, 128)
__IMPL_HYBRID_DEFINE_PROMOTION_MATH(64, 32, 128)
__IMPL_HYBRID_DEFINE_PROMOTION_MATH(64, 64, 128)
#else /* __SIZEOF_REGISTER__ >= 16 && __INT128_TYPE__ */
__IMPL_HYBRID_DEFINE_OVERFLOW_MATH(64, 8)
__IMPL_HYBRID_DEFINE_OVERFLOW_MATH(64, 16)
__IMPL_HYBRID_DEFINE_OVERFLOW_MATH(64, 32)
__IMPL_HYBRID_DEFINE_OVERFLOW_MATH(64, 64)
#endif /* __SIZEOF_REGISTER__ < 16 || !__INT128_TYPE__ */
#ifdef __INT128_TYPE__
__IMPL_HYBRID_DEFINE_OVERFLOW_MATH(128, 8)
__IMPL_HYBRID_DEFINE_OVERFLOW_MATH(128, 16)
__IMPL_HYBRID_DEFINE_OVERFLOW_MATH(128, 32)
__IMPL_HYBRID_DEFINE_OVERFLOW_MATH(128, 64)
__IMPL_HYBRID_DEFINE_OVERFLOW_MATH(128, 128)
#endif /* __INT128_TYPE__ */
#endif /* __INT64_TYPE__ */
#undef __IMPL_HYBRID_DEFINE_OVERFLOW_MATH
#undef __IMPL_HYBRID_DEFINE_PROMOTION_MATH

#ifdef __cplusplus
#ifdef __UFIFTHINT_TYPE__
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL __NOTHROW_NCX(__impl_hybrid_overflow_uadd)(__UFIFTHINT_TYPE__ __x, __UFIFTHINT_TYPE__ __y, __UFIFTHINT_TYPE__ *__restrict __res) { return __impl_hybrid_overflow_uadd((__UFIFTHINT_ALIAS_TYPE__)__x, (__UFIFTHINT_ALIAS_TYPE__)__y, (__UFIFTHINT_ALIAS_TYPE__ *)__res); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL __NOTHROW_NCX(__impl_hybrid_overflow_sadd)(__FIFTHINT_TYPE__ __x, __FIFTHINT_TYPE__ __y, __FIFTHINT_TYPE__ *__restrict __res) { return __impl_hybrid_overflow_sadd((__FIFTHINT_ALIAS_TYPE__)__x, (__FIFTHINT_ALIAS_TYPE__)__y, (__FIFTHINT_ALIAS_TYPE__ *)__res); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL __NOTHROW_NCX(__impl_hybrid_overflow_uadd)(__UFIFTHINT_TYPE__ __x, __UFIFTHINT_TYPE__ __y, __UINT8_TYPE__ *__restrict __res) { return __impl_hybrid_overflow_uadd((__UFIFTHINT_ALIAS_TYPE__)__x, (__UFIFTHINT_ALIAS_TYPE__)__y, __res); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL __NOTHROW_NCX(__impl_hybrid_overflow_sadd)(__FIFTHINT_TYPE__ __x, __FIFTHINT_TYPE__ __y, __INT8_TYPE__ *__restrict __res) { return __impl_hybrid_overflow_sadd((__FIFTHINT_ALIAS_TYPE__)__x, (__FIFTHINT_ALIAS_TYPE__)__y, __res); }
#if __SIZEOF_FIFTHINT__ >= 2
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL __NOTHROW_NCX(__impl_hybrid_overflow_uadd)(__UFIFTHINT_TYPE__ __x, __UFIFTHINT_TYPE__ __y, __UINT16_TYPE__ *__restrict __res) { return __impl_hybrid_overflow_uadd((__UFIFTHINT_ALIAS_TYPE__)__x, (__UFIFTHINT_ALIAS_TYPE__)__y, __res); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL __NOTHROW_NCX(__impl_hybrid_overflow_sadd)(__FIFTHINT_TYPE__ __x, __FIFTHINT_TYPE__ __y, __INT16_TYPE__ *__restrict __res) { return __impl_hybrid_overflow_sadd((__FIFTHINT_ALIAS_TYPE__)__x, (__FIFTHINT_ALIAS_TYPE__)__y, __res); }
#endif /* __SIZEOF_FIFTHINT__ >= 2 */
#if __SIZEOF_FIFTHINT__ >= 4
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL __NOTHROW_NCX(__impl_hybrid_overflow_uadd)(__UFIFTHINT_TYPE__ __x, __UFIFTHINT_TYPE__ __y, __UINT32_TYPE__ *__restrict __res) { return __impl_hybrid_overflow_uadd((__UFIFTHINT_ALIAS_TYPE__)__x, (__UFIFTHINT_ALIAS_TYPE__)__y, __res); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL __NOTHROW_NCX(__impl_hybrid_overflow_sadd)(__FIFTHINT_TYPE__ __x, __FIFTHINT_TYPE__ __y, __INT32_TYPE__ *__restrict __res) { return __impl_hybrid_overflow_sadd((__FIFTHINT_ALIAS_TYPE__)__x, (__FIFTHINT_ALIAS_TYPE__)__y, __res); }
#endif /* __SIZEOF_FIFTHINT__ >= 4 */
#if __SIZEOF_FIFTHINT__ >= 8
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL __NOTHROW_NCX(__impl_hybrid_overflow_uadd)(__UFIFTHINT_TYPE__ __x, __UFIFTHINT_TYPE__ __y, __UINT64_TYPE__ *__restrict __res) { return __impl_hybrid_overflow_uadd((__UFIFTHINT_ALIAS_TYPE__)__x, (__UFIFTHINT_ALIAS_TYPE__)__y, __res); }
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL __NOTHROW_NCX(__impl_hybrid_overflow_sadd)(__FIFTHINT_TYPE__ __x, __FIFTHINT_TYPE__ __y, __INT64_TYPE__ *__restrict __res) { return __impl_hybrid_overflow_sadd((__FIFTHINT_ALIAS_TYPE__)__x, (__FIFTHINT_ALIAS_TYPE__)__y, __res); }
#endif /* __SIZEOF_FIFTHINT__ >= 8 */
#endif /* __UFIFTHINT_TYPE__ */
#undef __IMPL_HYBRID_OVERFLOW_NAME
} /* extern "C++" */
#endif /* __cplusplus */

/* @return: true:  Overflow  occurred (unlikely; `*res' contains the truncated result)
 *                 Overflow here means that the finite result stored in `*res' doesn't
 *                 match a value that would have been produced when infinite precision
 *                 was available.
 *                 e.g.: `UINT_MAX + 42u' and `11u - 19u' overflow, but `32u + 42u'
 *                       or `11 - 19' don't
 * @return: false: `*res' contains the correct result. */
#ifdef __NO_builtin_expect
#define __hybrid_overflow_uadd(x, y, res) __IMPL_HYBRID_OVERFLOW_SELECT(__impl_hybrid_overflow_uadd, __UINT, x, y, res)
#define __hybrid_overflow_sadd(x, y, res) __IMPL_HYBRID_OVERFLOW_SELECT(__impl_hybrid_overflow_sadd, __INT, x, y, res)
#define __hybrid_overflow_usub(x, y, res) __IMPL_HYBRID_OVERFLOW_SELECT(__impl_hybrid_overflow_usub, __UINT, x, y, res)
#define __hybrid_overflow_ssub(x, y, res) __IMPL_HYBRID_OVERFLOW_SELECT(__impl_hybrid_overflow_ssub, __INT, x, y, res)
#define __hybrid_overflow_umul(x, y, res) __IMPL_HYBRID_OVERFLOW_SELECT(__impl_hybrid_overflow_umul, __UINT, x, y, res)
#define __hybrid_overflow_smul(x, y, res) __IMPL_HYBRID_OVERFLOW_SELECT(__impl_hybrid_overflow_smul, __INT, x, y, res)
#else /* __NO_builtin_expect */
#define __hybrid_overflow_uadd(x, y, res) __builtin_expect(__IMPL_HYBRID_OVERFLOW_SELECT(__impl_hybrid_overflow_uadd, __UINT, x, y, res), 0)
#define __hybrid_overflow_sadd(x, y, res) __builtin_expect(__IMPL_HYBRID_OVERFLOW_SELECT(__impl_hybrid_overflow_sadd, __INT, x, y, res), 0)
#define __hybrid_overflow_usub(x, y, res) __builtin_expect(__IMPL_HYBRID_OVERFLOW_SELECT(__impl_hybrid_overflow_usub, __UINT, x, y, res), 0)
#define __hybrid_overflow_ssub(x, y, res) __builtin_expect(__IMPL_HYBRID_OVERFLOW_SELECT(__impl_hybrid_overflow_ssub, __INT, x, y, res), 0)
#define __hybrid_overflow_umul(x, y, res) __builtin_expect(__IMPL_HYBRID_OVERFLOW_SELECT(__impl_hybrid_overflow_umul, __UINT, x, y, res), 0)
#define __hybrid_overflow_smul(x, y, res) __builtin_expect(__IMPL_HYBRID_OVERFLOW_SELECT(__impl_hybrid_overflow_smul, __INT, x, y, res), 0)
#endif /* !__NO_builtin_expect */
#endif /* End:Fallback */


/* Optional variants that may compile faster when operand sizes are known to be fixed.
 * e.g.: `__hybrid_overflow_uadd8(__UINT8_TYPE__ a, __UINT8_TYPE__ b, __UINT8_TYPE__ *c)'
 *       `__hybrid_overflow_sadd8(__INT8_TYPE__ a, __INT8_TYPE__ b, __INT8_TYPE__ *c)'
 * etc... */
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
#ifdef __INT64_TYPE__
#define __hybrid_overflow_uadd64 __hybrid_overflow_uadd
#define __hybrid_overflow_sadd64 __hybrid_overflow_sadd
#define __hybrid_overflow_usub64 __hybrid_overflow_usub
#define __hybrid_overflow_ssub64 __hybrid_overflow_ssub
#define __hybrid_overflow_umul64 __hybrid_overflow_umul
#define __hybrid_overflow_smul64 __hybrid_overflow_smul
#endif /* __INT64_TYPE__ */


/* >> bool __hybrid_overflow_sneg(T x, T *p_result);
 * >> bool __hybrid_overflow_sneg_p2n(T x, T *p_result);    -- @assume(x >= 0)
 * >> bool __hybrid_overflow_sneg_n2p(T x, T *p_result);    -- @assume(x < 0)
 * Do the operation `*p_result = -x'
 * @return: true:  Overflow happened
 * @return: false: Overflow didn't happen */
#ifdef __HYBRID_OVERFLOW_USES_BUILTINS
#define __hybrid_overflow_sneg(x, p_result) __hybrid_overflow_ssub(0, x, p_result)
#define __hybrid_overflow_sneg8             __hybrid_overflow_sneg
#define __hybrid_overflow_sneg16            __hybrid_overflow_sneg
#define __hybrid_overflow_sneg32            __hybrid_overflow_sneg
#ifdef __INT64_TYPE__
#define __hybrid_overflow_sneg64 __hybrid_overflow_sneg
#endif /* __INT64_TYPE__ */
#else /* __HYBRID_OVERFLOW_USES_BUILTINS */
#ifdef __NO_builtin_expect
#define __hybrid_overflow_sneg8(x, p_result)  (((__UINT8_TYPE__)(*(p_result) = (__INT8_TYPE__)-(__UINT8_TYPE__)(x))) == __UINT8_C(0x80))
#define __hybrid_overflow_sneg16(x, p_result) (((__UINT16_TYPE__)(*(p_result) = (__INT16_TYPE__)-(__UINT16_TYPE__)(x))) == __UINT16_C(0x8000))
#define __hybrid_overflow_sneg32(x, p_result) (((__UINT32_TYPE__)(*(p_result) = (__INT32_TYPE__)-(__UINT32_TYPE__)(x))) == __UINT32_C(0x80000000))
#ifdef __INT64_TYPE__
#define __hybrid_overflow_sneg64(x, p_result) (((__UINT64_TYPE__)(*(p_result) = (__INT64_TYPE__)-(__UINT64_TYPE__)(x))) == __UINT64_C(0x8000000000000000))
#endif /* __INT64_TYPE__ */
#else /* __NO_builtin_expect */
#define __hybrid_overflow_sneg8(x, p_result)  __builtin_expect(((__UINT8_TYPE__)(*(p_result) = (__INT8_TYPE__)-(__UINT8_TYPE__)(x))) == __UINT8_C(0x80), 0)
#define __hybrid_overflow_sneg16(x, p_result) __builtin_expect(((__UINT16_TYPE__)(*(p_result) = (__INT16_TYPE__)-(__UINT16_TYPE__)(x))) == __UINT16_C(0x8000), 0)
#define __hybrid_overflow_sneg32(x, p_result) __builtin_expect(((__UINT32_TYPE__)(*(p_result) = (__INT32_TYPE__)-(__UINT32_TYPE__)(x))) == __UINT32_C(0x80000000), 0)
#ifdef __INT64_TYPE__
#define __hybrid_overflow_sneg64(x, p_result) __builtin_expect(((__UINT64_TYPE__)(*(p_result) = (__INT64_TYPE__)-(__UINT64_TYPE__)(x))) == __UINT64_C(0x8000000000000000), 0)
#endif /* __INT64_TYPE__ */
#endif /* !__NO_builtin_expect */
#ifdef __NO_builtin_choose_expr
#ifdef __INT64_TYPE__
#define __hybrid_overflow_sneg(x, p_result)                                                 \
	(sizeof(*(p_result)) == 1 ? __hybrid_overflow_sneg8(x, (__INT8_TYPE__ *)(p_result)) :   \
	 sizeof(*(p_result)) == 2 ? __hybrid_overflow_sneg16(x, (__INT16_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) == 4 ? __hybrid_overflow_sneg32(x, (__INT32_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_sneg64(x, (__INT64_TYPE__ *)(p_result)))
#else /* __INT64_TYPE__ */
#define __hybrid_overflow_sneg(x, p_result)                                                 \
	(sizeof(*(p_result)) == 1 ? __hybrid_overflow_sneg8(x, (__INT8_TYPE__ *)(p_result)) :   \
	 sizeof(*(p_result)) == 2 ? __hybrid_overflow_sneg16(x, (__INT16_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_sneg32(x, (__INT32_TYPE__ *)(p_result)))
#endif /* !__INT64_TYPE__ */
#else /* __NO_builtin_choose_expr */
#ifdef __INT64_TYPE__
#define __hybrid_overflow_sneg(x, p_result)                                                                    \
	__builtin_choose_expr(sizeof(*(p_result)) == 1, __hybrid_overflow_sneg8(x, (__INT8_TYPE__ *)(p_result)),   \
	__builtin_choose_expr(sizeof(*(p_result)) == 2, __hybrid_overflow_sneg16(x, (__INT16_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) == 4, __hybrid_overflow_sneg32(x, (__INT32_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_sneg64(x, (__INT64_TYPE__ *)(p_result)))))
#else /* __INT64_TYPE__ */
#define __hybrid_overflow_sneg(x, p_result)                                                                    \
	__builtin_choose_expr(sizeof(*(p_result)) == 1, __hybrid_overflow_sneg8(x, (__INT8_TYPE__ *)(p_result)),   \
	__builtin_choose_expr(sizeof(*(p_result)) == 2, __hybrid_overflow_sneg16(x, (__INT16_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_sneg32(x, (__INT32_TYPE__ *)(p_result))))
#endif /* !__INT64_TYPE__ */
#endif /* !__NO_builtin_choose_expr */
#endif /* !__HYBRID_OVERFLOW_USES_BUILTINS */
#ifdef NDEBUG
#define __hybrid_overflow_sneg8_p2n(x, p_result)  (*(p_result) = (__INT8_TYPE__)-(__UINT8_TYPE__)(x), 0)
#define __hybrid_overflow_sneg16_p2n(x, p_result) (*(p_result) = (__INT16_TYPE__)-(__UINT16_TYPE__)(x), 0)
#define __hybrid_overflow_sneg32_p2n(x, p_result) (*(p_result) = (__INT32_TYPE__)-(__UINT32_TYPE__)(x), 0)
#ifdef __INT64_TYPE__
#define __hybrid_overflow_sneg64_p2n(x, p_result) (*(p_result) = (__INT64_TYPE__)-(__UINT64_TYPE__)(x), 0)
#endif /* __INT64_TYPE__ */
#else /* NDEBUG */
#define __hybrid_overflow_sneg8_p2n(x, p_result)  (__hybrid_asserte((__INT8_TYPE__)(*(p_result) = (__INT8_TYPE__)-(__UINT8_TYPE__)(x)) < 0), 0)
#define __hybrid_overflow_sneg16_p2n(x, p_result) (__hybrid_asserte((__INT16_TYPE__)(*(p_result) = (__INT16_TYPE__)-(__UINT16_TYPE__)(x)) < 0), 0)
#define __hybrid_overflow_sneg32_p2n(x, p_result) (__hybrid_asserte((__INT32_TYPE__)(*(p_result) = (__INT32_TYPE__)-(__UINT32_TYPE__)(x)) < 0), 0)
#ifdef __INT64_TYPE__
#define __hybrid_overflow_sneg64_p2n(x, p_result) (__hybrid_asserte((__INT64_TYPE__)(*(p_result) = (__INT64_TYPE__)-(__UINT64_TYPE__)(x)) < 0), 0)
#endif /* __INT64_TYPE__ */
#endif /* !NDEBUG */
#ifdef __NO_builtin_choose_expr
#ifdef __INT64_TYPE__
#define __hybrid_overflow_sneg_p2n(x, p_result)                                                 \
	(sizeof(*(p_result)) == 1 ? __hybrid_overflow_sneg8_p2n(x, (__INT8_TYPE__ *)(p_result)) :   \
	 sizeof(*(p_result)) == 2 ? __hybrid_overflow_sneg16_p2n(x, (__INT16_TYPE__ *)(p_result)) : \
	 sizeof(*(p_result)) == 4 ? __hybrid_overflow_sneg32_p2n(x, (__INT32_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_sneg64_p2n(x, (__INT64_TYPE__ *)(p_result)))
#else /* __INT64_TYPE__ */
#define __hybrid_overflow_sneg_p2n(x, p_result)                                                 \
	(sizeof(*(p_result)) == 1 ? __hybrid_overflow_sneg8_p2n(x, (__INT8_TYPE__ *)(p_result)) :   \
	 sizeof(*(p_result)) == 2 ? __hybrid_overflow_sneg16_p2n(x, (__INT16_TYPE__ *)(p_result)) : \
	                            __hybrid_overflow_sneg32_p2n(x, (__INT32_TYPE__ *)(p_result)))
#endif /* !__INT64_TYPE__ */
#else /* __NO_builtin_choose_expr */
#ifdef __INT64_TYPE__
#define __hybrid_overflow_sneg_p2n(x, p_result)                                                                    \
	__builtin_choose_expr(sizeof(*(p_result)) == 1, __hybrid_overflow_sneg8_p2n(x, (__INT8_TYPE__ *)(p_result)),   \
	__builtin_choose_expr(sizeof(*(p_result)) == 2, __hybrid_overflow_sneg16_p2n(x, (__INT16_TYPE__ *)(p_result)), \
	__builtin_choose_expr(sizeof(*(p_result)) == 4, __hybrid_overflow_sneg32_p2n(x, (__INT32_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_sneg64_p2n(x, (__INT64_TYPE__ *)(p_result)))))
#else /* __INT64_TYPE__ */
#define __hybrid_overflow_sneg_p2n(x, p_result)                                                                    \
	__builtin_choose_expr(sizeof(*(p_result)) == 1, __hybrid_overflow_sneg8_p2n(x, (__INT8_TYPE__ *)(p_result)),   \
	__builtin_choose_expr(sizeof(*(p_result)) == 2, __hybrid_overflow_sneg16_p2n(x, (__INT16_TYPE__ *)(p_result)), \
	                                                __hybrid_overflow_sneg32_p2n(x, (__INT32_TYPE__ *)(p_result))))
#endif /* !__INT64_TYPE__ */
#endif /* !__NO_builtin_choose_expr */
#define __hybrid_overflow_sneg_n2p   __hybrid_overflow_sneg
#define __hybrid_overflow_sneg8_n2p  __hybrid_overflow_sneg8
#define __hybrid_overflow_sneg16_n2p __hybrid_overflow_sneg16
#define __hybrid_overflow_sneg32_n2p __hybrid_overflow_sneg32
#ifdef __INT64_TYPE__
#define __hybrid_overflow_sneg64_n2p __hybrid_overflow_sneg64
#endif /* __INT64_TYPE__ */



__DECL_END

#endif /* !__GUARD_HYBRID___OVERFLOW_H */
