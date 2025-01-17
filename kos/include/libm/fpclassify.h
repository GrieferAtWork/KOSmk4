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
#ifndef _LIBM_FPCLASSIFY_H
#define _LIBM_FPCLASSIFY_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <asm/crt/fp_type.h>
#include <bits/types.h>

#include <libm/fdlibm.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
/* Copyright (C) 2002, 2007 by  Red Hat, Incorporated. All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software
 * is freely granted, provided that this notice is preserved.
 */

__LIBM_LOCAL_FUNC(fpclassifyf) __ATTR_WUNUSED __ATTR_CONST int
(__LIBCCALL __ieee754_fpclassifyf)(__IEEE754_FLOAT_TYPE__ __x) {
	int __retval = __FP_NORMAL;
	__uint32_t __wx;
	__LIBM_GET_FLOAT_WORD(__wx, __x);
	__wx &= __UINT32_C(0x7fffffff);
	if (__wx == 0) {
		__retval = __FP_ZERO;
	} else if (__wx < __UINT32_C(0x800000)) {
		__retval = __FP_SUBNORMAL;
	} else if (__wx >= __UINT32_C(0x7f800000)) {
		__retval = __wx > __UINT32_C(0x7f800000) ? __FP_NAN : __FP_INFINITE;
	}
	return __retval;
}
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
/* Copyright (C) 2002, 2007 by  Red Hat, Incorporated. All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software
 * is freely granted, provided that this notice is preserved.
 */

__LIBM_LOCAL_FUNC(fpclassify) __ATTR_WUNUSED __ATTR_CONST int
(__LIBCCALL __ieee754_fpclassify)(__IEEE754_DOUBLE_TYPE__ __x) {
	int __retval = __FP_NORMAL;
	__uint32_t __msw, __lsw;
	__LIBM_GET_DOUBLE_WORDS(__msw, __lsw, __x);
	__lsw |= __msw & __UINT32_C(0xfffff);
	__msw &= __UINT32_C(0x7ff00000);
	if ((__msw | __lsw) == 0) {
		__retval = __FP_ZERO;
	} else if (__msw == 0) {
		__retval = __FP_SUBNORMAL;
	} else if (__msw == __UINT32_C(0x7ff00000)) {
		__retval = __lsw != 0 ? __FP_NAN : __FP_INFINITE;
	}
	return __retval;
}
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
/* Copyright (C) 2002, 2007 by  Red Hat, Incorporated. All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software
 * is freely granted, provided that this notice is preserved.
 */

__LIBM_LOCAL_FUNC(fpclassifyl) __ATTR_WUNUSED __ATTR_CONST int
(__LIBCCALL __ieee854_fpclassifyl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	int __retval = __FP_NORMAL;
	__uint32_t __ex, __hx, __lx, __m;
	__LIBM_GET_LDOUBLE_WORDS(__ex, __hx, __lx, __x);
	__m = (__hx & __UINT32_C(0x7fffffff)) | __lx;
	__ex &= IEEE854_LONG_DOUBLE_MAXEXP;
	if ((__ex | __m) == 0) {
		__retval = __FP_ZERO;
	} else if (__ex == 0 && (__hx & __UINT32_C(0x80000000)) == 0) {
		__retval = __FP_SUBNORMAL;
	} else if (__ex == IEEE854_LONG_DOUBLE_MAXEXP) {
		__retval = __m != 0 ? __FP_NAN : __FP_INFINITE;
	}
	return __retval;
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_FPCLASSIFY_H */
