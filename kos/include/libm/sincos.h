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
#ifndef _LIBM_SINCOS_H
#define _LIBM_SINCOS_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/cos.h>
#include <libm/fdlibm.h>
#include <libm/kernel_cos.h>
#include <libm/kernel_sin.h>
#include <libm/rem_pio2.h>
#include <libm/sin.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */
__LOCAL __ATTR_NONNULL((2, 3)) void
(__LIBCCALL __ieee754_sincosf)(__IEEE754_FLOAT_TYPE__ __x,
                               __IEEE754_FLOAT_TYPE__ *__psinx,
                               __IEEE754_FLOAT_TYPE__ *__pcosx) {
	__int32_t __ix;

	/* High word of x. */
	__LIBM_GET_FLOAT_WORD(__ix, __x);

	/* |x| ~< pi/4 */
	__ix &= __INT32_C(0x7fffffff);
	if (__ix <= __INT32_C(0x3f490fd8)) {
#ifdef __ieee754_fpu_sincosf
		__ieee754_fpu_sincosf(__x, __psinx, __pcosx);
#else /* __ieee754_fpu_sincosf */
		*__psinx = __ieee754_kernel_sinf(__x, 0.0, 0);
		*__pcosx = __ieee754_kernel_cosf(__x, 0.0);
#endif
	} else if (__ix >= __INT32_C(0x7f800000)) {
		/* sin(Inf or NaN) is NaN */
		*__psinx = *__pcosx = __x - __x;
	} else {
#ifdef __ieee754_fpu_sincosf
		__ieee754_fpu_sincosf(__x, __psinx, __pcosx);
#else /* __ieee754_fpu_sincosf */
		/* Argument reduction needed.  */
		__IEEE754_FLOAT_TYPE__ __y[2];
		__int32_t __n;

		__n = __ieee754_rem_pio2f(__x, __y);
		switch ((int)(__n & 3)) {
		case 0:
			*__psinx = __ieee754_kernel_sinf(__y[0], __y[1], 1);
			*__pcosx = __ieee754_kernel_cosf(__y[0], __y[1]);
			break;
		case 1:
			*__psinx = __ieee754_kernel_cosf(__y[0], __y[1]);
			*__pcosx = -__ieee754_kernel_sinf(__y[0], __y[1], 1);
			break;
		case 2:
			*__psinx = -__ieee754_kernel_sinf(__y[0], __y[1], 1);
			*__pcosx = -__ieee754_kernel_cosf(__y[0], __y[1]);
			break;
		default:
			*__psinx = -__ieee754_kernel_cosf(__y[0], __y[1]);
			*__pcosx = __ieee754_kernel_sinf(__y[0], __y[1], 1);
			break;
		}
#endif /* !__ieee754_fpu_sincosf */
	}
}
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */
__LOCAL __ATTR_NONNULL((2, 3)) void
(__LIBCCALL __ieee754_sincos)(__IEEE754_DOUBLE_TYPE__ __x,
                              __IEEE754_DOUBLE_TYPE__ *__psinx,
                              __IEEE754_DOUBLE_TYPE__ *__pcosx) {
	__int32_t __ix;

	/* High word of x. */
	__LIBM_GET_HIGH_WORD(__ix, __x);

	/* |x| ~< pi/4 */
	__ix &= __INT32_C(0x7fffffff);
	if (__ix >= __INT32_C(0x7ff00000)) {
		/* sin(Inf or NaN) is NaN */
		*__psinx = *__pcosx = __x - __x;
	} else {
#ifdef __ieee754_fpu_sincos
		__ieee754_fpu_sincos(__x, __psinx, __pcosx);
#else /* __ieee754_fpu_sincos */
		*__psinx = __ieee754_sin(__x);
		*__pcosx = __ieee754_cos(__x);
#endif /* !__ieee754_fpu_sincos */
	}
}
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */
__LOCAL __ATTR_NONNULL((2, 3)) void
(__LIBCCALL __ieee854_sincosl)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                               __IEEE854_LONG_DOUBLE_TYPE__ *__psinx,
                               __IEEE854_LONG_DOUBLE_TYPE__ *__pcosx) {
	__int32_t __se;
	__uint32_t __i0, __i1;

	/* High word of x. */
	__LIBM_GET_LDOUBLE_WORDS(__se, __i0, __i1, __x);
	(void)__i1;

	/* |x| ~< pi/4 */
	__se &= 0x7fff;
	if (__se < 0x3ffe || (__se == 0x3ffe && __i0 <= __UINT32_C(0xc90fdaa2))) {
#ifdef __ieee854_fpu_sincosl
		__ieee854_fpu_sincosl(__x, sinx, cosx);
#else /* __ieee854_fpu_sincosl */
		*__psinx = __ieee854_kernel_sinl(__x, 0.0, 0);
		*__pcosx = __ieee854_kernel_cosl(__x, 0.0);
#endif /* !__ieee854_fpu_sincosl */
	} else if (__se == 0x7fff) {
		/* sin(Inf or NaN) is NaN */
		*__psinx = *__pcosx = __x - __x;
	} else {
#ifdef __ieee854_fpu_sincosl
		__ieee854_fpu_sincosl(__x, __psinx, __pcosx);
#else /* __ieee854_fpu_sincosl */
		/* Argument reduction needed.  */
		__IEEE854_LONG_DOUBLE_TYPE__ __y[2];
		__int32_t __n;

		__n = __ieee854_rem_pio2l(__x, __y);
		switch ((int)(__n & 3)) {
		case 0:
			*__psinx = __ieee854_kernel_sinl(__y[0], __y[1], 1);
			*__pcosx = __ieee854_kernel_cosl(__y[0], __y[1]);
			break;
		case 1:
			*__psinx = __ieee854_kernel_cosl(__y[0], __y[1]);
			*__pcosx = -__ieee854_kernel_sinl(__y[0], __y[1], 1);
			break;
		case 2:
			*__psinx = -__ieee854_kernel_sinl(__y[0], __y[1], 1);
			*__pcosx = -__ieee854_kernel_cosl(__y[0], __y[1]);
			break;
		default:
			*__psinx = -__ieee854_kernel_cosl(__y[0], __y[1]);
			*__pcosx = __ieee854_kernel_sinl(__y[0], __y[1], 1);
			break;
		}
#endif /* !__ieee854_fpu_sincosl */
	}
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_SINCOS_H */
