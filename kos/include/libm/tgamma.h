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
#ifndef _LIBM_TGAMMA_H
#define _LIBM_TGAMMA_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <fpu_control.h>

#include <libc/fenv.h>
#include <libm/copysign.h>
#include <libm/cos.h>
#include <libm/exp.h>
#include <libm/exp2.h>
#include <libm/fdlibm.h>
#include <libm/frexp.h>
#include <libm/isinf.h>
#include <libm/lgamma.h>
#include <libm/log.h>
#include <libm/pow.h>
#include <libm/rint.h>
#include <libm/round.h>
#include <libm/scalbn.h>
#include <libm/sin.h>
#include <libm/trunc.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
/* Implementation of gamma function according to ISO C.
   Copyright (C) 1997-2013 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1997.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

__LIBM_LOCAL_DECLARE_BEGIN
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_FLOAT_TYPE__, gamma_coefff, 3) {
	__IEEE754_FLOAT_C(0x1.555556p-4),
	__IEEE754_FLOAT_C(-0xb.60b61p-12),
	__IEEE754_FLOAT_C(0x3.403404p-12)
};
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(gamma_productf) __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_gamma_productf)(__IEEE754_FLOAT_TYPE__ __x,
                                      __IEEE754_FLOAT_TYPE__ __x_eps, int __n,
                                      __IEEE754_FLOAT_TYPE__ *__eps) {
	int __i;
	__IEEE754_FLOAT_TYPE__ volatile __fret;
	__IEEE754_DOUBLE_TYPE__ __x_full, __ret;
	__x_full = (__IEEE754_DOUBLE_TYPE__)__x +
	           (__IEEE754_DOUBLE_TYPE__)__x_eps;
	__ret  = __x_full;
	for (__i = 1; __i < __n; __i++)
		__ret *= __x_full + __i;
	__fret = (__IEEE754_FLOAT_TYPE__)__ret;
	*__eps = (__ret - (__IEEE754_DOUBLE_TYPE__)__fret) / (__IEEE754_DOUBLE_TYPE__)__fret;
	return __fret;
}

__LIBM_LOCAL_FUNC(gammaf_positive) __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_gammaf_positive)(__IEEE754_FLOAT_TYPE__ __x, int *__exp2_adj) {
	int __local_signgam;
	if (__x < __IEEE754_FLOAT_C(0.5)) {
		*__exp2_adj = 0;
		return __ieee754_expf(__ieee754_lgammaf(__x + __IEEE754_FLOAT_C(1.0), &__local_signgam)) / __x;
	} else if (__x <= __IEEE754_FLOAT_C(1.5)) {
		*__exp2_adj = 0;
		return __ieee754_expf(__ieee754_lgammaf(__x, &__local_signgam));
	} else if (__x < __IEEE754_FLOAT_C(2.5)) {
		__IEEE754_FLOAT_TYPE__ __x_adj;
		__x_adj     = __x - __IEEE754_FLOAT_C(1.0);
		*__exp2_adj = 0;
		return __ieee754_expf(__ieee754_lgammaf(__x_adj, &__local_signgam)) * __x_adj;
	} else {
		__IEEE754_FLOAT_TYPE__ __eps   = __IEEE754_FLOAT_C(0.0);
		__IEEE754_FLOAT_TYPE__ __x_eps = __IEEE754_FLOAT_C(0.0);
		__IEEE754_FLOAT_TYPE__ __x_adj = __x;
		__IEEE754_FLOAT_TYPE__ __prod  = __IEEE754_FLOAT_C(1.0);
		__IEEE754_FLOAT_TYPE__ __exp_adj, __x_adj_int, __x_adj_frac;
		__IEEE754_FLOAT_TYPE__ __x_adj_mant, __ret, __bsum, __x_adj2;
		int __x_adj_log2;
		__size_t __i;
		if (__x < __IEEE754_FLOAT_C(4.0)) {
			__IEEE754_FLOAT_TYPE__ __n;
			__IEEE754_FLOAT_TYPE__ volatile __x_tmp;
			__n     = __ieee754_ceilf(__IEEE754_FLOAT_C(4.0) - __x);
			__x_tmp = __x + __n;
			__x_adj = __x_tmp;
			__x_eps = (__x - (__x_adj - __n));
			__prod  = __ieee754_gamma_productf(__x_adj - __n, __x_eps, __n, &__eps);
		}
		__exp_adj    = -__eps;
		__x_adj_int  = __ieee754_roundf(__x_adj);
		__x_adj_frac = __x_adj - __x_adj_int;
		__x_adj_mant = __ieee754_frexpf(__x_adj, &__x_adj_log2);
		if (__x_adj_mant < (__IEEE754_FLOAT_TYPE__)0.70710678118654752440 /*M_SQRT1_2*/) {
			--__x_adj_log2;
			__x_adj_mant *= __IEEE754_FLOAT_C(2.0);
		}
		*__exp2_adj = __x_adj_log2 * (int)__x_adj_int;
		__ret = __ieee754_powf(__x_adj_mant, __x_adj) *
		        __ieee754_exp2f(__x_adj_log2 * __x_adj_frac) *
		        __ieee754_expf(-__x_adj) *
		        __ieee754_sqrtf(__IEEE754_FLOAT_C(2.0) *
		                        (__IEEE754_FLOAT_TYPE__)3.14159265358979323846 /*M_PI*/ / __x_adj) /
		        __prod;
		__exp_adj += __x_eps * __ieee754_logf(__x_adj);
		__bsum   = __LIBM_LOCAL_VALUE(gamma_coefff)[2];
		__x_adj2 = __x_adj * __x_adj;
		for (__i = 1; __i < 3; __i++)
			__bsum = __bsum / __x_adj2 + __LIBM_LOCAL_VALUE(gamma_coefff)[2 - __i];
		__exp_adj += __bsum / __x_adj;
		__ret += __ret * __ieee754_expm1f(__exp_adj);
		return __ret;
	}
}

__LIBM_LOCAL_FUNC(tgammaf_r) __ATTR_WUNUSED __ATTR_NONNULL((2)) __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_tgammaf)(__IEEE754_FLOAT_TYPE__ __x, int *__signgamp) {
	__int32_t __hx;
	__IEEE754_FLOAT_TYPE__ volatile __ret;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	if ((__hx & __INT32_C(0x7fffffff)) == 0) {
		*__signgamp = 0;
		return __IEEE754_FLOAT_C(1.0) / __x;
	}
	if (__hx < 0 && (__uint32_t) __hx < __UINT32_C(0xff800000) && __ieee754_rintf(__x) == __x) {
		*__signgamp = 0;
		return (__x - __x) / (__x - __x);
	}
	if (__hx == __INT32_C(0xff800000)) {
		*__signgamp = 0;
		return __x - __x;
	}
	if ((__hx & __INT32_C(0x7f800000)) == __INT32_C(0x7f800000)) {
		*__signgamp = 0;
		return __x + __x;
	}
	if (__x >= __IEEE754_FLOAT_C(36.0)) {
		*__signgamp = 0;
		__ret = __IEEE754_FLOAT_C(3.40282346638528859812e+38) /*FLT_MAX*/ *
		        __IEEE754_FLOAT_C(3.40282346638528859812e+38) /*FLT_MAX*/;
		return __ret;
	} else {
		__libc_fepushround_FE_TONEAREST();
		if (__x > __IEEE754_FLOAT_C(0.0)) {
			int __exp2_adj;
			__IEEE754_FLOAT_TYPE__ __tret;
			*__signgamp = 0;
			__tret      = __ieee754_gammaf_positive(__x, &__exp2_adj);
			__ret       = __ieee754_scalbnf(__tret, __exp2_adj);
		} else if (__x >= -(__IEEE754_FLOAT_C(1.19209289550781250000e-7) /*FLT_EPSILON*/) / __IEEE754_FLOAT_C(4.0)) {
			*__signgamp = 0;
			__ret       = __IEEE754_FLOAT_C(1.0) / __x;
		} else {
			__IEEE754_FLOAT_TYPE__ __tx;
			__tx        = __ieee754_truncf(__x);
			*__signgamp = (__tx == __IEEE754_FLOAT_C(2.0) *
			                       __ieee754_truncf(__tx / __IEEE754_FLOAT_C(2.0)))
			              ? -1
			              : 1;
			if (__x <= -__IEEE754_FLOAT_C(42.0)) {
				__ret = __IEEE754_FLOAT_C(1.17549435082228750797e-38) /*FLT_MIN*/ *
				        __IEEE754_FLOAT_C(1.17549435082228750797e-38) /*FLT_MIN*/; /* Underflow.  */
			} else {
				__IEEE754_FLOAT_TYPE__ __frac;
				__IEEE754_FLOAT_TYPE__ __sinpix;
				__IEEE754_FLOAT_TYPE__ __tret;
				int __exp2_adj;
				__frac = __tx - __x;
				if (__frac > __IEEE754_FLOAT_C(0.5))
					__frac = __IEEE754_FLOAT_C(1.0) - __frac;
				__sinpix = (__frac <= __IEEE754_FLOAT_C(0.25)
				            ? __ieee754_sinf((__IEEE754_FLOAT_TYPE__)3.14159265358979323846 /*M_PI*/ * __frac)
				            : __ieee754_cosf((__IEEE754_FLOAT_TYPE__)3.14159265358979323846 /*M_PI*/ * (__IEEE754_FLOAT_C(0.5) - __frac)));
				__tret   = (__IEEE754_FLOAT_TYPE__)3.14159265358979323846 /*M_PI*/ /
				         (-__x * __sinpix * __ieee754_gammaf_positive(-__x, &__exp2_adj));
				__ret = __ieee754_scalbnf(__tret, -__exp2_adj);
			}
		}
		__libc_fepopround_FE_TONEAREST();
	}
	if (__ieee754_isinff(__ret) && __x != __IEEE754_FLOAT_C(0.0)) {
		if (*__signgamp < 0) {
			__ret = -__ieee754_copysignf(__IEEE754_FLOAT_C(3.40282346638528859812e+38) /*FLT_MAX*/,
			                             __ret) *
			        __IEEE754_FLOAT_C(3.40282346638528859812e+38) /*FLT_MAX*/;
			__ret = -__ret;
		} else {
			__ret = __ieee754_copysignf(__IEEE754_FLOAT_C(3.40282346638528859812e+38) /*FLT_MAX*/,
			                            __ret) *
			        __IEEE754_FLOAT_C(3.40282346638528859812e+38) /*FLT_MAX*/;
		}
	} else if (__ret == __IEEE754_FLOAT_C(0.0)) {
		if (*__signgamp < 0) {
			__ret = -__ieee754_copysignf(__IEEE754_FLOAT_C(1.17549435082228750797e-38) /*FLT_MIN*/,
			                             __ret) *
			        __IEEE754_FLOAT_C(1.17549435082228750797e-38) /*FLT_MIN*/;
			__ret = -__ret;
		} else {
			__ret = __ieee754_copysignf(__IEEE754_FLOAT_C(1.17549435082228750797e-38) /*FLT_MIN*/,
			                            __ret) *
			        __IEEE754_FLOAT_C(1.17549435082228750797e-38) /*FLT_MIN*/;
		}
	}
	return __ret;
}
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
/* Implementation of gamma function according to ISO C.
   Copyright (C) 1997-2013 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1997.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

__LIBM_LOCAL_DECLARE_BEGIN
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_DOUBLE_TYPE__, gamma_coeff, 6) {
	0x1.5555555555555p-4,
	-0xb.60b60b60b60b8p-12,
	0x3.4034034034034p-12,
	-0x2.7027027027028p-12,
	0x3.72a3c5631fe46p-12,
	-0x7.daac36664f1f4p-12
};
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(gamma_mul_split) void
(__LIBCCALL __ieee754_gamma_mul_split)(__IEEE754_DOUBLE_TYPE__ *__hi,
                                       __IEEE754_DOUBLE_TYPE__ *__lo,
                                       __IEEE754_DOUBLE_TYPE__ __x,
                                       __IEEE754_DOUBLE_TYPE__ __y) {
#if __has_builtin(__builtin_fma) && defined(__FP_FAST_FMA)
	/* Fast built-in fused multiply-add. */
	*__hi = __x * __y;
	*__lo = __builtin_fma(__x, __y, -*__hi);
#elif defined(FP_FAST_FMA) && 0 /* TODO */
	*__hi = __x * __y;
	*__lo = fma(__x, __y, -*__hi);
#else /* ... */
	__IEEE754_DOUBLE_TYPE__ __x1, __y1;
	__IEEE754_DOUBLE_TYPE__ __x2, __y2;
	__IEEE754_DOUBLE_TYPE__ volatile __tmp, __tmp2;
	__tmp  = __x * __y;
	*__hi  = __tmp;
	__tmp  = __x * __IEEE754_DOUBLE_C(134217729.0); /* (((__int32_t)1 << ((DBL_MANT_DIG + 1) / 2)) + 1) */
	__x1   = __tmp;
	__tmp  = __y * __IEEE754_DOUBLE_C(134217729.0);
	__y1   = __tmp;
	__tmp  = __x - __x1;
	__tmp  = __tmp + __x1;
	__x1   = __tmp;
	__tmp  = __y - __y1;
	__tmp  = __tmp + __y1;
	__y1   = __tmp;
	__tmp  = __x - __x1;
	__x2   = __tmp;
	__tmp  = __y - __y1;
	__y2   = __tmp;
	__tmp  = __x1 * __y1;
	__tmp  = __tmp - *__hi;
	__tmp2 = __x1 * __y2;
	__tmp += __tmp2;
	__tmp2 = __x2 * __y1;
	__tmp += __tmp2;
	__tmp2 = __x2 * __y2;
	__tmp += __tmp2;
	*__lo = __tmp;
#endif /* !... */
}

__LIBM_LOCAL_FUNC(gamma_product) __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_gamma_product)(__IEEE754_DOUBLE_TYPE__ __x,
                                     __IEEE754_DOUBLE_TYPE__ __x_eps, int __n,
                                     __IEEE754_DOUBLE_TYPE__ *__eps) {
	__IEEE754_DOUBLE_TYPE__ __ret = __x;
	int __i;
	__libc_fepushround_FE_TONEAREST();
	*__eps = __x_eps / __x;
	for (__i = 1; __i < __n; __i++) {
		__IEEE754_DOUBLE_TYPE__ __lo;
		__IEEE754_DOUBLE_TYPE__ __tmp = __x + __i;
		*__eps += __x_eps / __tmp;
		__ieee754_gamma_mul_split(&__ret, &__lo, __ret, __tmp);
		__tmp = __lo / __ret;
		*__eps += __tmp;
	}
	__libc_fepopround_FE_TONEAREST();
	return __ret;
}


#ifndef __FE_ROUNDING_MASK
#define __FE_ROUNDING_MASK (__FE_TONEAREST | __FE_DOWNWARD | __FE_UPWARD | __FE_TOWARDZERO)
#endif /* !__FE_ROUNDING_MASK */
#ifndef __FE_PRECISION_MASK
#define __FE_PRECISION_MASK (_FPU_EXTENDED | _FPU_DOUBLE | _FPU_SINGLE)
#endif /* !__FE_PRECISION_MASK */

#if defined(__i386__) || defined(__x86_64__)
#define __LIBM_SET_ROUND_53BIT_FE_TONEAREST() \
	fpu_control_t __cw;                       \
	_FPU_GETCW(__cw);                         \
	__ieee754_gamma_feholdexcept_setround_387_prec(__cw)
__FORCELOCAL __ATTR_ARTIFICIAL void
__ieee754_gamma_feholdexcept_setround_387_prec(fpu_control_t __cw) {
	__cw &= ~(__FE_ROUNDING_MASK | __FE_PRECISION_MASK);
	__cw |= __FE_TONEAREST | _FPU_DOUBLE | 0x3f;
	_FPU_SETCW(__cw);
}
#define __LIBM_RESTORE_ROUND_PREC() \
	_FPU_SETCW(__cw)
#elif defined(__mc68000__)
#define __LIBM_SET_ROUND_53BIT_FE_TONEAREST() \
	fpu_control_t __cw;                       \
	_FPU_GETCW(__cw);                         \
	__ieee754_gamma_feholdexcept_setround_68k_prec(__cw)
__FORCELOCAL __ATTR_ARTIFICIAL void
__ieee754_gamma_feholdexcept_setround_68k_prec(fpu_control_t __cw) {
	__cw &= ~(__FE_ROUNDING_MASK | __FE_PRECISION_MASK);
	__cw &= ~(__FE_ALL_EXCEPT << 6);
	__cw |= __FE_TONEAREST | _FPU_DOUBLE;
	_FPU_SETCW(__cw);
}
#define __LIBM_RESTORE_ROUND_PREC() \
	_FPU_SETCW(__cw)
#else /* ... */
#define __LIBM_SET_ROUND_53BIT_FE_TONEAREST() __libc_fepushround_FE_TONEAREST()
#define __LIBM_RESTORE_ROUND_PREC()           __libc_fepopround_FE_TONEAREST()
#endif /* !... */

__LIBM_LOCAL_FUNC(gamma_positive) __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_gamma_positive)(__IEEE754_DOUBLE_TYPE__ __x, int *__exp2_adj) {
	int __local_signgam;
	if (__x < __IEEE754_DOUBLE_C(0.5)) {
		*__exp2_adj = 0;
		return __ieee754_exp(__ieee754_lgamma(__x + 1, &__local_signgam)) / __x;
	} else if (__x <= __IEEE754_DOUBLE_C(1.5)) {
		*__exp2_adj = 0;
		return __ieee754_exp(__ieee754_lgamma(__x, &__local_signgam));
	} else if (__x < __IEEE754_DOUBLE_C(6.5)) {
		/* Adjust into the range for using exp (lgamma).  */
		__IEEE754_DOUBLE_TYPE__ __n, __x_adj, __eps, __prod;
		__n         = __ieee754_ceil(__x - __IEEE754_DOUBLE_C(1.5));
		__x_adj     = __x - __n;
		__prod      = __ieee754_gamma_product(__x_adj, 0.0, (int)__n, &__eps);
		*__exp2_adj = 0;
		return __ieee754_exp(__ieee754_lgamma(__x_adj, &__local_signgam)) *
		       __prod * (1.0 + __eps);
	} else {
		__IEEE754_DOUBLE_TYPE__ __x_adj = __x;
		__IEEE754_DOUBLE_TYPE__ __eps   = __IEEE754_DOUBLE_C(0.0);
		__IEEE754_DOUBLE_TYPE__ __x_eps = __IEEE754_DOUBLE_C(0.0);
		__IEEE754_DOUBLE_TYPE__ __prod  = __IEEE754_DOUBLE_C(1.0);
		__IEEE754_DOUBLE_TYPE__ __exp_adj, __x_adj_int, __x_adj_frac;
		__IEEE754_DOUBLE_TYPE__ __x_adj_mant, __ret, __bsum, __x_adj2;
		int __x_adj_log2;
		__size_t __i;
		__LIBM_SET_ROUND_53BIT_FE_TONEAREST();
		if (__x < __IEEE754_DOUBLE_C(12.0)) {
			__IEEE754_DOUBLE_TYPE__ __n;
			__IEEE754_DOUBLE_TYPE__ volatile __x_tmp;
			__n     = __ieee754_ceil(__IEEE754_DOUBLE_C(12.0) - __x);
			__x_tmp = __x + __n;
			__x_adj = __x_tmp;
			__x_eps = (__x - (__x_adj - __n));
			__prod  = __ieee754_gamma_product(__x_adj - __n, __x_eps, __n, &__eps);
		}
		__exp_adj    = -__eps;
		__x_adj_int  = __ieee754_round(__x_adj);
		__x_adj_frac = __x_adj - __x_adj_int;
		__x_adj_mant = __ieee754_frexp(__x_adj, &__x_adj_log2);
		if (__x_adj_mant < __IEEE754_DOUBLE_C(0.70710678118654752440) /*M_SQRT1_2*/) {
			--__x_adj_log2;
			__x_adj_mant *= __IEEE754_DOUBLE_C(2.0);
		}
		*__exp2_adj = __x_adj_log2 * (int)__x_adj_int;
		__ret = __ieee754_pow(__x_adj_mant, __x_adj) *
		        __ieee754_exp2(__x_adj_log2 * __x_adj_frac) *
		        __ieee754_exp(-__x_adj) *
		        __ieee754_sqrt(__IEEE754_DOUBLE_C(2.0) *
		                       __IEEE754_DOUBLE_C(3.14159265358979323846) /*M_PI*/ / __x_adj) /
		        __prod;
		__exp_adj += __x_eps * __ieee754_log(__x_adj);
		__bsum = __LIBM_LOCAL_VALUE(gamma_coeff)[5];
		__x_adj2 = __x_adj * __x_adj;
		for (__i = 1; __i < 6; __i++)
			__bsum = __bsum / __x_adj2 + __LIBM_LOCAL_VALUE(gamma_coeff)[5 - __i];
		__exp_adj += __bsum / __x_adj;
		__ret += __ret * __ieee754_expm1(__exp_adj);
		__LIBM_RESTORE_ROUND_PREC();
		return __ret;
	}
}

__LIBM_LOCAL_FUNC(tgamma_r) __ATTR_WUNUSED __ATTR_NONNULL((2)) __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_tgamma)(__IEEE754_DOUBLE_TYPE__ __x, int *__signgamp) {
	__int32_t __hx;
	__uint32_t __lx;
	__IEEE754_DOUBLE_TYPE__ volatile __ret;
	__LIBM_GET_DOUBLE_WORDS(__hx, __lx, __x);
	if (((__hx & __INT32_C(0x7fffffff)) | __lx) == 0) {
		*__signgamp = 0;
		return __IEEE754_DOUBLE_C(1.0) / __x;
	}
	if (__hx < 0 && (__uint32_t)__hx < __UINT32_C(0xfff00000) && __ieee754_rint(__x) == __x) {
		*__signgamp = 0;
		return (__x - __x) / (__x - __x);
	}
	if ((__uint32_t)__hx == __UINT32_C(0xfff00000) && __lx == 0) {
		*__signgamp = 0;
		return __x - __x;
	}
	if ((__hx & __INT32_C(0x7ff00000)) == __INT32_C(0x7ff00000)) {
		*__signgamp = 0;
		return __x + __x;
	}
	if (__x >= __IEEE754_DOUBLE_C(172.0)) {
		*__signgamp = 0;
		__ret = (__IEEE754_DOUBLE_TYPE__)1.79769313486231570815e+308L /*DBL_MAX*/ *
		        (__IEEE754_DOUBLE_TYPE__)1.79769313486231570815e+308L /*DBL_MAX*/;
		return __ret;
	} else {
		__libc_fepushround_FE_TONEAREST();
		if (__x > __IEEE754_DOUBLE_C(0.0)) {
			int __exp2_adj;
			__IEEE754_DOUBLE_TYPE__ __tret;
			*__signgamp = 0;
			__tret      = __ieee754_gamma_positive(__x, &__exp2_adj);
			__ret       = __ieee754_scalbn(__tret, __exp2_adj);
		} else if (__x >= -((__IEEE754_DOUBLE_TYPE__)2.22044604925031308085e-16L /*DBL_EPSILON*/) / __IEEE754_DOUBLE_C(4.0)) {
			*__signgamp = 0;
			__ret       = __IEEE754_DOUBLE_C(1.0) / __x;
		} else {
			__IEEE754_DOUBLE_TYPE__ __tx;
			__tx        = __ieee754_trunc(__x);
			*__signgamp = (__tx == __IEEE754_DOUBLE_C(2.0) * __ieee754_trunc(__tx / __IEEE754_DOUBLE_C(2.0))) ? -1 : 1;
			if (__x <= -__IEEE754_DOUBLE_C(184.0)) {
				__ret = (__IEEE754_DOUBLE_TYPE__)2.22507385850720138309e-308L /*DBL_MIN*/ *
				        (__IEEE754_DOUBLE_TYPE__)2.22507385850720138309e-308L /*DBL_MIN*/;
			} else {
				__IEEE754_DOUBLE_TYPE__ __frac, __sinpix, __tret;
				int __exp2_adj;
				__frac = __tx - __x;
				if (__frac > __IEEE754_DOUBLE_C(0.5))
					__frac = __IEEE754_DOUBLE_C(1.0) - __frac;
				__sinpix = (__frac <= __IEEE754_DOUBLE_C(0.25)
				            ? __ieee754_sin(__IEEE754_DOUBLE_C(3.14159265358979323846) /*M_PI*/ * __frac)
				            : __ieee754_cos(__IEEE754_DOUBLE_C(3.14159265358979323846) /*M_PI*/ * (__IEEE754_DOUBLE_C(0.5) - __frac)));
				__tret = __IEEE754_DOUBLE_C(3.14159265358979323846) /*M_PI*/ /
				         (-__x * __sinpix * __ieee754_gamma_positive(-__x, &__exp2_adj));
				__ret  = __ieee754_scalbn(__tret, -__exp2_adj);
			}
		}
		__libc_fepopround_FE_TONEAREST();
	}
	if (__ieee754_isinf(__ret) && __x != 0.0) {
		if (*__signgamp < 0) {
			__ret = -__ieee754_copysign((__IEEE754_DOUBLE_TYPE__)1.79769313486231570815e+308L /*DBL_MAX*/,
			                            __ret) *
			        (__IEEE754_DOUBLE_TYPE__)1.79769313486231570815e+308L /*DBL_MAX*/;
			__ret = -__ret;
		} else {
			__ret = __ieee754_copysign((__IEEE754_DOUBLE_TYPE__)1.79769313486231570815e+308L /*DBL_MAX*/,
			                           __ret) *
			        (__IEEE754_DOUBLE_TYPE__)1.79769313486231570815e+308L /*DBL_MAX*/;
		}
	} else if (__ret == 0.0) {
		if (*__signgamp < 0) {
			__ret = -__ieee754_copysign((__IEEE754_DOUBLE_TYPE__)2.22507385850720138309e-308L /*DBL_MIN*/,
			                            __ret) *
			        (__IEEE754_DOUBLE_TYPE__)2.22507385850720138309e-308L /*DBL_MIN*/;
			__ret = -__ret;
		} else {
			__ret = __ieee754_copysign((__IEEE754_DOUBLE_TYPE__)2.22507385850720138309e-308L /*DBL_MIN*/,
			                           __ret) *
			        (__IEEE754_DOUBLE_TYPE__)2.22507385850720138309e-308L /*DBL_MIN*/;
		}
	}
	return __ret;
}
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
/* Implementation of gamma function according to ISO C.
   Copyright (C) 1997-2015 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1997.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

__LIBM_LOCAL_DECLARE_BEGIN
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE854_LONG_DOUBLE_TYPE__, gamma_coeffl, 8) {
	__IEEE854_LONG_DOUBLE_C(0x1.5555555555555556p-4),
	__IEEE854_LONG_DOUBLE_C(-0xb.60b60b60b60b60bp-12),
	__IEEE854_LONG_DOUBLE_C(0x3.4034034034034034p-12),
	__IEEE854_LONG_DOUBLE_C(-0x2.7027027027027028p-12),
	__IEEE854_LONG_DOUBLE_C(0x3.72a3c5631fe46aep-12),
	__IEEE854_LONG_DOUBLE_C(-0x7.daac36664f1f208p-12),
	__IEEE854_LONG_DOUBLE_C(0x1.a41a41a41a41a41ap-8),
	__IEEE854_LONG_DOUBLE_C(-0x7.90a1b2c3d4e5f708p-8),
};
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(gamma_mul_splitl) void
(__LIBCCALL __ieee854_gamma_mul_splitl)(__IEEE854_LONG_DOUBLE_TYPE__ *__hi,
                                        __IEEE854_LONG_DOUBLE_TYPE__ *__lo,
                                        __IEEE854_LONG_DOUBLE_TYPE__ __x,
                                        __IEEE854_LONG_DOUBLE_TYPE__ __y) {
#if __has_builtin(__builtin_fmal) && defined(__FP_FAST_FMAL)
	*__hi = __x * __y;
	*__lo = __builtin_fmal(__x, __y, -*__hi);
#elif defined(FP_FAST_FMAL) && 0 /* TODO */
	*__hi = __x * __y;
	*__lo = fmal(__x, __y, -*__hi);
#else /* ... */
	__IEEE854_LONG_DOUBLE_TYPE__ __x1, __y1;
	__IEEE854_LONG_DOUBLE_TYPE__ __x2, __y2;
	*__hi = __x * __y;
	__x1  = __x * __IEEE854_LONG_DOUBLE_C(4294967297.0); /* ((1LL << ((LDBL_MANT_DIG + 1) / 2)) + 1) */
	__y1  = __y * __IEEE854_LONG_DOUBLE_C(4294967297.0); /* ((1LL << ((LDBL_MANT_DIG + 1) / 2)) + 1) */
	__x1  = (__x - __x1) + __x1;
	__y1  = (__y - __y1) + __y1;
	__x2  = __x - __x1;
	__y2  = __y - __y1;
	*__lo = (((__x1 * __y1 - *__hi) + __x1 * __y2) + __x2 * __y1) + __x2 * __y2;
#endif /* !... */
}

__LIBM_LOCAL_FUNC(gamma_productl) __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_gamma_productl)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                                      __IEEE854_LONG_DOUBLE_TYPE__ __x_eps, int __n,
                                      __IEEE854_LONG_DOUBLE_TYPE__ *__eps) {
	__IEEE854_LONG_DOUBLE_TYPE__ __ret = __x;
	int __i;
	__libc_fepushround_FE_TONEAREST();
	*__eps = __x_eps / __x;
	for (__i = 1; __i < __n; __i++) {
		__IEEE854_LONG_DOUBLE_TYPE__ __lo;
		*__eps += __x_eps / (__x + __i);
		__ieee854_gamma_mul_splitl(&__ret, &__lo, __ret, __x + __i);
		*__eps += __lo / __ret;
	}
	__libc_fepopround_FE_TONEAREST();
	return __ret;
}

__LIBM_LOCAL_FUNC(gammal_positive) __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_gammal_positive)(__IEEE854_LONG_DOUBLE_TYPE__ __x, int *__exp2_adj) {
	int __local_signgam;
	if (__x < __IEEE854_LONG_DOUBLE_C(0.5)) {
		*__exp2_adj = 0;
		return __ieee854_expl(__ieee854_lgammal(__x + __IEEE854_LONG_DOUBLE_C(1.0), &__local_signgam)) / __x;
	} else if (__x <= __IEEE854_LONG_DOUBLE_C(1.5)) {
		*__exp2_adj = 0;
		return __ieee854_expl(__ieee854_lgammal(__x, &__local_signgam));
	} else if (__x < __IEEE854_LONG_DOUBLE_C(7.5)) {
		__IEEE854_LONG_DOUBLE_TYPE__ __n, __x_adj, __eps, __prod;
		__n         = __ieee854_ceill(__x - __IEEE854_LONG_DOUBLE_C(1.5));
		__x_adj     = __x - __n;
		__prod      = __ieee854_gamma_productl(__x_adj, __IEEE854_LONG_DOUBLE_C(0.0), __n, &__eps);
		*__exp2_adj = 0;
		return __ieee854_expl(__ieee854_lgammal(__x_adj, &__local_signgam)) *
		       __prod * (__IEEE854_LONG_DOUBLE_C(1.0) + __eps);
	} else {
		__IEEE854_LONG_DOUBLE_TYPE__ __eps = __IEEE854_LONG_DOUBLE_C(0.0);
		__IEEE854_LONG_DOUBLE_TYPE__ __x_eps = __IEEE854_LONG_DOUBLE_C(0.0);
		__IEEE854_LONG_DOUBLE_TYPE__ __x_adj = __x, __prod = __IEEE854_LONG_DOUBLE_C(1.0);
		__IEEE854_LONG_DOUBLE_TYPE__ __exp_adj, __x_adj_int, __x_adj_frac;
		__IEEE854_LONG_DOUBLE_TYPE__ __x_adj_mant, __ret, __bsum, __x_adj2;
		int __x_adj_log2;
		__size_t __i;
		if (__x < __IEEE854_LONG_DOUBLE_C(13.0)) {
			__IEEE854_LONG_DOUBLE_TYPE__ __n;
			__n     = __ieee854_ceill(__IEEE854_LONG_DOUBLE_C(13.0) - __x);
			__x_adj = __x + __n;
			__x_eps = (__x - (__x_adj - __n));
			__prod  = __ieee854_gamma_productl(__x_adj - __n, __x_eps, __n, &__eps);
		}
		__exp_adj    = -__eps;
		__x_adj_int  = __ieee854_roundl(__x_adj);
		__x_adj_frac = __x_adj - __x_adj_int;
		__x_adj_mant = __ieee854_frexpl(__x_adj, &__x_adj_log2);
		if (__x_adj_mant < __IEEE854_LONG_DOUBLE_C(0.707106781186547524400844362104849039) /*M_SQRT1_2l*/) {
			--__x_adj_log2;
			__x_adj_mant *= __IEEE854_LONG_DOUBLE_C(2.0);
		}
		*__exp2_adj = __x_adj_log2 * (int)__x_adj_int;
		__ret = __ieee854_powl(__x_adj_mant, __x_adj) *
		        __ieee854_exp2l(__x_adj_log2 * __x_adj_frac) *
		        __ieee854_expl(-__x_adj) *
		        __ieee854_sqrtl(__IEEE854_LONG_DOUBLE_C(2.0) *
		                        __IEEE854_LONG_DOUBLE_C(3.141592653589793238462643383279502884) /*M_PIl*/ /
		                        __x_adj) /
		        __prod;
		__exp_adj += __x_eps * __ieee854_logl(__x_adj);
		__bsum   = __LIBM_LOCAL_VALUE(gamma_coeffl)[7];
		__x_adj2 = __x_adj * __x_adj;
		for (__i = 1; __i < 8; __i++)
			__bsum = __bsum / __x_adj2 + __LIBM_LOCAL_VALUE(gamma_coeffl)[7 - __i];
		__exp_adj += __bsum / __x_adj;
		return __ret + __ret * __ieee854_expm1l(__exp_adj);
	}
}

__LIBM_LOCAL_FUNC(tgammal_r) __ATTR_WUNUSED __ATTR_NONNULL((2)) __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_tgammal)(__IEEE854_LONG_DOUBLE_TYPE__ __x, int *__signgamp) {
	__uint32_t __es, __hx, __lx;
	__IEEE854_LONG_DOUBLE_TYPE__ __ret;
	__LIBM_GET_LDOUBLE_WORDS(__es, __hx, __lx, __x);
	if (((__es & __LIBM_IEEE854_LONG_DOUBLE_MAXEXP) | __hx | __lx) == 0) {
		*__signgamp = 0;
		return __IEEE854_LONG_DOUBLE_C(1.0) / __x;
	}
	if (__es == __UINT32_C(0xffffffff) && ((__hx & __UINT32_C(0x7fffffff)) | __lx) == 0) {
		*__signgamp = 0;
		return __x - __x;
	}
	if ((__es & __LIBM_IEEE854_LONG_DOUBLE_MAXEXP) == __LIBM_IEEE854_LONG_DOUBLE_MAXEXP) {
		*__signgamp = 0;
		return __x + __x;
	}
	if ((__es & 0x8000) != 0 && __ieee854_rintl(__x) == __x) {
		*__signgamp = 0;
		return (__x - __x) / (__x - __x);
	}

	if (__x >= __IEEE854_LONG_DOUBLE_C(1756.0)) {
		*__signgamp = 0;
		return __IEEE854_LONG_DOUBLE_C(1.18973149535723176502e+4932) /*LDBL_MAX*/ *
		       __IEEE854_LONG_DOUBLE_C(1.18973149535723176502e+4932) /*LDBL_MAX*/;
	} else {
		__libc_fepushround_FE_TONEAREST();
		if (__x > __IEEE854_LONG_DOUBLE_C(0.0)) {
			int __exp2_adj;
			*__signgamp = 0;
			__ret       = __ieee854_gammal_positive(__x, &__exp2_adj);
			__ret       = __ieee854_scalbnl(__ret, __exp2_adj);
		} else if (__x >= -(__IEEE854_LONG_DOUBLE_C(1.08420217248550443401e-19) /*LDBL_EPSILON*/) / __IEEE854_LONG_DOUBLE_C(4.0)) {
			*__signgamp = 0;
			__ret       = __IEEE854_LONG_DOUBLE_C(1.0) / __x;
		} else {
			__IEEE854_LONG_DOUBLE_TYPE__ __tx;
			__tx        = __ieee854_truncl(__x);
			*__signgamp = (__tx == __IEEE854_LONG_DOUBLE_C(2.0) * __ieee854_truncl(__tx / __IEEE854_LONG_DOUBLE_C(2.0))) ? -1 : 1;
			if (__x <= -__IEEE854_LONG_DOUBLE_C(1766.0)) {
				/* Underflow.  */
				__ret = __IEEE854_LONG_DOUBLE_C(3.36210314311209350626e-4932) /*LDBL_MIN*/ *
				        __IEEE854_LONG_DOUBLE_C(3.36210314311209350626e-4932) /*LDBL_MIN*/;
			} else {
				__IEEE854_LONG_DOUBLE_TYPE__ __frac = __tx - __x;
				__IEEE854_LONG_DOUBLE_TYPE__ __sinpix;
				int __exp2_adj;
				if (__frac > __IEEE854_LONG_DOUBLE_C(0.5))
					__frac = __IEEE854_LONG_DOUBLE_C(1.0) - __frac;
				__sinpix = (__frac <= __IEEE854_LONG_DOUBLE_C(0.25)
				            ? __ieee854_sinl(__IEEE854_LONG_DOUBLE_C(3.141592653589793238462643383279502884) /*M_PIl*/ * __frac)
				            : __ieee854_cosl(__IEEE854_LONG_DOUBLE_C(3.141592653589793238462643383279502884) /*M_PIl*/ * (__IEEE854_LONG_DOUBLE_C(0.5) - __frac)));
				__ret    = __IEEE854_LONG_DOUBLE_C(3.141592653589793238462643383279502884) /*M_PIl*/ / (-__x * __sinpix * __ieee854_gammal_positive(-__x, &__exp2_adj));
				__ret    = __ieee854_scalbnl(__ret, -__exp2_adj);
			}
		}
		__libc_fepopround_FE_TONEAREST();
	}
	if (__ieee854_isinfl(__ret) && __x != __IEEE854_LONG_DOUBLE_C(0.0)) {
		if (*__signgamp < 0) {
			__ret = -__ieee854_copysignl(__IEEE854_LONG_DOUBLE_C(1.18973149535723176502e+4932) /*LDBL_MAX*/,
			                             __ret) *
			        __IEEE854_LONG_DOUBLE_C(1.18973149535723176502e+4932) /*LDBL_MAX*/;
			__ret = -__ret;
		} else {
			__ret = __ieee854_copysignl(__IEEE854_LONG_DOUBLE_C(1.18973149535723176502e+4932) /*LDBL_MAX*/,
			                            __ret) *
			        __IEEE854_LONG_DOUBLE_C(1.18973149535723176502e+4932) /*LDBL_MAX*/;
		}
	} else if (__ret == __IEEE854_LONG_DOUBLE_C(0.0)) {
		if (*__signgamp < 0) {
			__ret = -__ieee854_copysignl(__IEEE854_LONG_DOUBLE_C(3.36210314311209350626e-4932) /*LDBL_MIN*/,
			                             __ret) *
			        __IEEE854_LONG_DOUBLE_C(3.36210314311209350626e-4932) /*LDBL_MIN*/;
			__ret = -__ret;
		} else {
			__ret = __ieee854_copysignl(__IEEE854_LONG_DOUBLE_C(3.36210314311209350626e-4932) /*LDBL_MIN*/,
			                            __ret) *
			        __IEEE854_LONG_DOUBLE_C(3.36210314311209350626e-4932) /*LDBL_MIN*/;
		}
	}
	return __ret;
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_TGAMMA_H */
