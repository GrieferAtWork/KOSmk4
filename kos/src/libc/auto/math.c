/* HASH CRC-32:0x6fe82005 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_MATH_C
#define GUARD_LIBC_AUTO_MATH_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/math.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <libm/matherr.h>
#include <libm/inf.h>
#include <libm/atan.h>
/* Arc tangent of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_atan)(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2(isgreaterequal, __LIBM_MATHFUN(fabs, x), 1.0)) {
		return __kernel_standard(x, x, __LIBM_MATHFUN0(inf),
		                         __LIBM_MATHFUN(fabs, x) > 1.0
		                         ? __LIBM_KMATHERR_ATANH_PLUSONE /* atanh(|x|>1) */
		                         : __LIBM_KMATHERR_ATANH_ONE);   /* atanh(|x|==1) */
	}
	return __LIBM_MATHFUN(atan, x);
}
#include <bits/math-constants.h>
#include <libm/matherr.h>
#include <libm/atan2.h>
/* Arc tangent of Y/X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_atan2)(double y,
                             double x) {
	if (__LIBM_LIB_VERSION == __LIBM_SVID && x == 0.0 && y == 0.0)
		return __kernel_standard(y, x, __HUGE_VAL, __LIBM_KMATHERR_ATAN2); /* atan2(+-0,+-0) */
	return __LIBM_MATHFUN2(atan2, y, x);
}
/* Arc cosine of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_acosf)(float x) {
	return (float)libc_acos((double)x);
}
/* Arc sine of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_asinf)(float x) {
	return (float)libc_asin((double)x);
}
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <libm/matherr.h>
#include <libm/inf.h>
#include <libm/atan.h>
/* Arc tangent of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_atanf)(float x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2F(isgreaterequal, __LIBM_MATHFUNF(fabs, x), 1.0f)) {
		return __kernel_standard_f(x, x, __LIBM_MATHFUN0F(inf),
		                         __LIBM_MATHFUNF(fabs, x) > 1.0f
		                         ? __LIBM_KMATHERR_ATANH_PLUSONE /* atanh(|x|>1) */
		                         : __LIBM_KMATHERR_ATANH_ONE);   /* atanh(|x|==1) */
	}
	return __LIBM_MATHFUNF(atan, x);
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)libc_atan((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
#include <bits/math-constants.h>
#include <libm/matherr.h>
#include <libm/atan2.h>
/* Arc tangent of Y/X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_atan2f)(float y,
                              float x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	if (__LIBM_LIB_VERSION == __LIBM_SVID && x == 0.0f && y == 0.0f)
		return __kernel_standard_f(y, x, __HUGE_VALF, __LIBM_KMATHERR_ATAN2); /* atan2(+-0,+-0) */
	return __LIBM_MATHFUN2F(atan2, y, x);
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)libc_atan2((double)y, (double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
/* Cosine of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_cosf float
NOTHROW(LIBCCALL libc_cosf)(float x) {
	return (float)libc_cos((double)x);
}
/* Sine of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_sinf float
NOTHROW(LIBCCALL libc_sinf)(float x) {
	return (float)libc_sin((double)x);
}
/* Tangent of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_tanf)(float x) {
	return (float)libc_tan((double)x);
}
/* Arc cosine of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_acosl)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_acos((double)x);
}
/* Arc sine of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_asinl)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_asin((double)x);
}
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <libm/matherr.h>
#include <libm/inf.h>
#include <libm/atan.h>
/* Arc tangent of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_atanl)(__LONGDOUBLE x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2L(isgreaterequal, __LIBM_MATHFUNL(fabs, x), 1.0L)) {
		return __kernel_standard_l(x, x, __LIBM_MATHFUN0L(inf),
		                         __LIBM_MATHFUNL(fabs, x) > 1.0L
		                         ? __LIBM_KMATHERR_ATANH_PLUSONE /* atanh(|x|>1) */
		                         : __LIBM_KMATHERR_ATANH_ONE);   /* atanh(|x|==1) */
	}
	return __LIBM_MATHFUNL(atan, x);
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)libc_atan((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
#include <bits/math-constants.h>
#include <libm/matherr.h>
#include <libm/atan2.h>
/* Arc tangent of Y/X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_atan2l)(__LONGDOUBLE y,
                              __LONGDOUBLE x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	if (__LIBM_LIB_VERSION == __LIBM_SVID && x == 0.0L && y == 0.0L)
		return __kernel_standard_l(y, x, __HUGE_VALL, __LIBM_KMATHERR_ATAN2); /* atan2(+-0,+-0) */
	return __LIBM_MATHFUN2L(atan2, y, x);
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)libc_atan2((double)y, (double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
/* Cosine of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_cosl __LONGDOUBLE
NOTHROW(LIBCCALL libc_cosl)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_cos((double)x);
}
/* Sine of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_sinl __LONGDOUBLE
NOTHROW(LIBCCALL libc_sinl)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_sin((double)x);
}
/* Tangent of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_tanl)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_tan((double)x);
}
/* Hyperbolic cosine of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_coshf)(float x) {
	return (float)libc_cosh((double)x);
}
/* Hyperbolic sine of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_sinhf)(float x) {
	return (float)libc_sinh((double)x);
}
/* Hyperbolic tangent of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_tanhf)(float x) {
	return (float)libc_tanh((double)x);
}
/* Hyperbolic cosine of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_coshl)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_cosh((double)x);
}
/* Hyperbolic sine of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_sinhl)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_sinh((double)x);
}
/* Hyperbolic tangent of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_tanhl)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_tanh((double)x);
}
/* Hyperbolic arc cosine of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_acoshf)(float x) {
	return (float)libc_acosh((double)x);
}
/* Hyperbolic arc sine of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_asinhf)(float x) {
	return (float)libc_asinh((double)x);
}
/* Hyperbolic arc tangent of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_atanhf)(float x) {
	return (float)libc_atanh((double)x);
}
/* Hyperbolic arc cosine of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_acoshl)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_acosh((double)x);
}
/* Hyperbolic arc sine of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_asinhl)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_asinh((double)x);
}
/* Hyperbolic arc tangent of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_atanhl)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_atanh((double)x);
}
#include <libm/signbit.h>
#include <libm/finite.h>
#include <libm/matherr.h>
#include <libm/exp.h>
/* Exponential function of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_exp double
NOTHROW(LIBCCALL libc_exp)(double x) {
	double result;
	result = __LIBM_MATHFUN(exp, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (!__LIBM_MATHFUN(finite, result) || result == 0.0) &&
	    __LIBM_MATHFUN(finite, x)) {
		return __kernel_standard(x, x, result,
		                         __LIBM_MATHFUN(signbit, x)
		                         ? __LIBM_KMATHERR_EXP_UNDERFLOW
		                         : __LIBM_KMATHERR_EXP_OVERFLOW);
	}
	return result;
}
#include <libm/frexp.h>
/* Break VALUE into a normalized fraction and an integral power of 2 */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED NONNULL((2)) double
NOTHROW_NCX(LIBCCALL libc_frexp)(double x,
                                 int *pexponent) {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_frexp((__IEEE754_DOUBLE_TYPE__)x, pexponent);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (double)__ieee754_frexpf((__IEEE754_FLOAT_TYPE__)x, pexponent);
#else /* ... */
	return (double)__ieee854_frexpl((__IEEE854_LONG_DOUBLE_TYPE__)x, pexponent);
#endif /* !... */
}
#include <parts/errno.h>
#include <libm/finite.h>
#include <libm/ldexp.h>
/* X times (two to the EXP power) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_ldexp)(double x,
                             int exponent) {
	double result;
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	result = (double)__ieee754_ldexp((__IEEE754_DOUBLE_TYPE__)x, exponent);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	result = (double)__ieee754_ldexpf((__IEEE754_FLOAT_TYPE__)x, exponent);
#else /* ... */
	result = (double)__ieee854_ldexpl((__IEEE854_LONG_DOUBLE_TYPE__)x, exponent);
#endif /* !... */
#ifdef ERANGE
	if unlikely(!__LIBM_MATHFUN(finite, result) || result == 0.0)
		__libc_seterrno(ERANGE);
#endif /* ERANGE */
	return result;
}
#include <libm/modf.h>
/* Break VALUE into integral and fractional parts */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED NONNULL((2)) double
NOTHROW_NCX(LIBCCALL libc_modf)(double x,
                                double *iptr) {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_modf((__IEEE754_DOUBLE_TYPE__)x, (__IEEE754_DOUBLE_TYPE__ *)iptr);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (double)__ieee754_modff((__IEEE754_FLOAT_TYPE__)x, (__IEEE754_FLOAT_TYPE__ *)iptr);
#else /* ... */
	return (double)__ieee854_modfl((__IEEE854_LONG_DOUBLE_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__ *)iptr);
#endif /* !... */
}
#include <libm/signbit.h>
#include <libm/finite.h>
#include <libm/matherr.h>
#include <libm/exp.h>
/* Exponential function of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_expf float
NOTHROW(LIBCCALL libc_expf)(float x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	float result;
	result = __LIBM_MATHFUNF(exp, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (!__LIBM_MATHFUNF(finite, result) || result == 0.0f) &&
	    __LIBM_MATHFUNF(finite, x)) {
		return __kernel_standard_f(x, x, result,
		                         __LIBM_MATHFUNF(signbit, x)
		                         ? __LIBM_KMATHERR_EXP_UNDERFLOW
		                         : __LIBM_KMATHERR_EXP_OVERFLOW);
	}
	return result;
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)libc_exp((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
#include <libm/frexp.h>
/* Break VALUE into a normalized fraction and an integral power of 2 */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED NONNULL((2)) float
NOTHROW_NCX(LIBCCALL libc_frexpf)(float x,
                                  int *pexponent) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	
#ifdef __IEEE754_DOUBLE_TYPE_IS_FLOAT__
	return (float)__ieee754_frexp((__IEEE754_DOUBLE_TYPE__)x, pexponent);
#elif defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
	return (float)__ieee754_frexpf((__IEEE754_FLOAT_TYPE__)x, pexponent);
#else /* ... */
	return (float)__ieee854_frexpl((__IEEE854_LONG_DOUBLE_TYPE__)x, pexponent);
#endif /* !... */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)libc_frexp((double)x, pexponent);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
#include <parts/errno.h>
#include <libm/finite.h>
#include <libm/ldexp.h>
/* X times (two to the EXP power) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_ldexpf)(float x,
                              int exponent) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	float result;
#ifdef __IEEE754_DOUBLE_TYPE_IS_FLOAT__
	result = (float)__ieee754_ldexp((__IEEE754_DOUBLE_TYPE__)x, exponent);
#elif defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
	result = (float)__ieee754_ldexpf((__IEEE754_FLOAT_TYPE__)x, exponent);
#else /* ... */
	result = (float)__ieee854_ldexpl((__IEEE854_LONG_DOUBLE_TYPE__)x, exponent);
#endif /* !... */
#ifdef ERANGE
	if unlikely(!__LIBM_MATHFUNF(finite, result) || result == 0.0f)
		__libc_seterrno(ERANGE);
#endif /* ERANGE */
	return result;
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)libc_ldexp((double)x, exponent);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
/* Natural logarithm of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_logf float
NOTHROW(LIBCCALL libc_logf)(float x) {
	return (float)libc_log((double)x);
}
/* Base-ten logarithm of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_log10f)(float x) {
	return (float)libc_log10((double)x);
}
#include <libm/modf.h>
/* Break VALUE into integral and fractional parts */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED NONNULL((2)) float
NOTHROW_NCX(LIBCCALL libc_modff)(float x,
                                 float *iptr) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	
#ifdef __IEEE754_DOUBLE_TYPE_IS_FLOAT__
	return (float)__ieee754_modf((__IEEE754_DOUBLE_TYPE__)x, (__IEEE754_DOUBLE_TYPE__ *)iptr);
#elif defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
	return (float)__ieee754_modff((__IEEE754_FLOAT_TYPE__)x, (__IEEE754_FLOAT_TYPE__ *)iptr);
#else /* ... */
	return (float)__ieee854_modfl((__IEEE854_LONG_DOUBLE_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__ *)iptr);
#endif /* !... */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)libc_modf((double)x, (double *)iptr);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
#include <libm/signbit.h>
#include <libm/finite.h>
#include <libm/matherr.h>
#include <libm/exp.h>
/* Exponential function of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_expl __LONGDOUBLE
NOTHROW(LIBCCALL libc_expl)(__LONGDOUBLE x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	__LONGDOUBLE result;
	result = __LIBM_MATHFUNL(exp, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (!__LIBM_MATHFUNL(finite, result) || result == 0.0L) &&
	    __LIBM_MATHFUNL(finite, x)) {
		return __kernel_standard_l(x, x, result,
		                         __LIBM_MATHFUNL(signbit, x)
		                         ? __LIBM_KMATHERR_EXP_UNDERFLOW
		                         : __LIBM_KMATHERR_EXP_OVERFLOW);
	}
	return result;
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)libc_exp((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
#include <libm/frexp.h>
/* Break VALUE into a normalized fraction and an integral power of 2 */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED NONNULL((2)) __LONGDOUBLE
NOTHROW_NCX(LIBCCALL libc_frexpl)(__LONGDOUBLE x,
                                  int *pexponent) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	
#ifdef __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return (__LONGDOUBLE)__ieee754_frexp((__IEEE754_DOUBLE_TYPE__)x, pexponent);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_frexpf((__IEEE754_FLOAT_TYPE__)x, pexponent);
#else /* ... */
	return (__LONGDOUBLE)__ieee854_frexpl((__IEEE854_LONG_DOUBLE_TYPE__)x, pexponent);
#endif /* !... */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)libc_frexp((double)x, pexponent);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
#include <parts/errno.h>
#include <libm/finite.h>
#include <libm/ldexp.h>
/* X times (two to the EXP power) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_ldexpl)(__LONGDOUBLE x,
                              int exponent) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	__LONGDOUBLE result;
#ifdef __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__
	result = (__LONGDOUBLE)__ieee754_ldexp((__IEEE754_DOUBLE_TYPE__)x, exponent);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	result = (__LONGDOUBLE)__ieee754_ldexpf((__IEEE754_FLOAT_TYPE__)x, exponent);
#else /* ... */
	result = (__LONGDOUBLE)__ieee854_ldexpl((__IEEE854_LONG_DOUBLE_TYPE__)x, exponent);
#endif /* !... */
#ifdef ERANGE
	if unlikely(!__LIBM_MATHFUNL(finite, result) || result == 0.0L)
		__libc_seterrno(ERANGE);
#endif /* ERANGE */
	return result;
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)libc_ldexp((double)x, exponent);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
/* Natural logarithm of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_logl __LONGDOUBLE
NOTHROW(LIBCCALL libc_logl)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_log((double)x);
}
/* Base-ten logarithm of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_log10l)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_log10((double)x);
}
#include <libm/modf.h>
/* Break VALUE into integral and fractional parts */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED NONNULL((2)) __LONGDOUBLE
NOTHROW_NCX(LIBCCALL libc_modfl)(__LONGDOUBLE x,
                                 __LONGDOUBLE *iptr) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	
#ifdef __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return (__LONGDOUBLE)__ieee754_modf((__IEEE754_DOUBLE_TYPE__)x, (__IEEE754_DOUBLE_TYPE__ *)iptr);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_modff((__IEEE754_FLOAT_TYPE__)x, (__IEEE754_FLOAT_TYPE__ *)iptr);
#else /* ... */
	return (__LONGDOUBLE)__ieee854_modfl((__IEEE854_LONG_DOUBLE_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__ *)iptr);
#endif /* !... */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)libc_modf((double)x, (double *)iptr);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
#include <libm/matherr.h>
#include <libm/signbit.h>
#include <libm/finite.h>
#include <libm/expm1.h>
/* Return exp(X) - 1 */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_expm1)(double x) {
	double result;
	result = __LIBM_MATHFUN(expm1, x);
	if ((!__LIBM_MATHFUN(finite, result) || result == -1.0) &&
	    __LIBM_MATHFUN(finite , x) && __LIBM_LIB_VERSION != __LIBM_IEEE) {
		return __kernel_standard(x, x, result,
		                         __LIBM_MATHFUN(signbit, x)
		                         ? __LIBM_KMATHERRL_EXPM1_UNDERFLOW
		                         : __LIBM_KMATHERRL_EXPM1_OVERFLOW);
	}
	return result;
}
#include <libm/matherr.h>
#include <libm/signbit.h>
#include <libm/finite.h>
#include <libm/expm1.h>
/* Return exp(X) - 1 */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_expm1f)(float x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	float result;
	result = __LIBM_MATHFUNF(expm1, x);
	if ((!__LIBM_MATHFUNF(finite, result) || result == -1.0f) &&
	    __LIBM_MATHFUNF(finite , x) && __LIBM_LIB_VERSION != __LIBM_IEEE) {
		return __kernel_standard_f(x, x, result,
		                         __LIBM_MATHFUNF(signbit, x)
		                         ? __LIBM_KMATHERRL_EXPM1_UNDERFLOW
		                         : __LIBM_KMATHERRL_EXPM1_OVERFLOW);
	}
	return result;
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)libc_expm1((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
/* Return log(1 + X) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_log1pf)(float x) {
	return (float)libc_log1p((double)x);
}
/* Return the base 2 signed integral exponent of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_logbf)(float x) {
	return (float)libc_logb((double)x);
}
#include <libm/matherr.h>
#include <libm/signbit.h>
#include <libm/finite.h>
#include <libm/expm1.h>
/* Return exp(X) - 1 */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_expm1l)(__LONGDOUBLE x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	__LONGDOUBLE result;
	result = __LIBM_MATHFUNL(expm1, x);
	if ((!__LIBM_MATHFUNL(finite, result) || result == -1.0L) &&
	    __LIBM_MATHFUNL(finite , x) && __LIBM_LIB_VERSION != __LIBM_IEEE) {
		return __kernel_standard_l(x, x, result,
		                         __LIBM_MATHFUNL(signbit, x)
		                         ? __LIBM_KMATHERRL_EXPM1_UNDERFLOW
		                         : __LIBM_KMATHERRL_EXPM1_OVERFLOW);
	}
	return result;
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)libc_expm1((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
/* Return log(1 + X) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_log1pl)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_log1p((double)x);
}
/* Return the base 2 signed integral exponent of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_logbl)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_logb((double)x);
}
/* Compute base-2 exponential of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_exp2f)(float x) {
	return (float)libc_exp2((double)x);
}
/* Compute base-2 logarithm of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_log2f)(float x) {
	return (float)libc_log2((double)x);
}
/* Compute base-2 exponential of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_exp2l)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_exp2((double)x);
}
/* Compute base-2 logarithm of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_log2l)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_log2((double)x);
}
#include <libm/finite.h>
#include <libm/isnan.h>
#include <libm/matherr.h>
#include <libm/pow.h>
/* Return X to the Y power */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_pow double
NOTHROW(LIBCCALL libc_pow)(double x,
                           double y) {
	double result;
	result = __LIBM_MATHFUN2(pow, x, y);
	/*
	 * ====================================================
	 * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Permission to use, copy, modify, and distribute this
	 * software is freely granted, provided that this notice 
	 * is preserved.
	 * ====================================================
	 */
	if (!__LIBM_MATHFUNI(finite, result)) {
		if (__LIBM_MATHFUNI(isnan, y) && x == 1.0) {
			result = 1.0;
		} else if (__LIBM_LIB_VERSION != __LIBM_IEEE) {
			if (__LIBM_MATHFUNI(isnan, x)) {
				if (y == 0.0) /* pow(NaN,0.0) */
					return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_NAN);
			} else if (__LIBM_MATHFUNI(finite, x) && __LIBM_MATHFUNI(finite, y)) {
				if (__LIBM_MATHFUNI(isnan, result)) { /* pow neg**non-int */
					return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_NONINT);
				} else if (x == 0.0 && y < 0.0) {
					if (__LIBM_MATHFUNI(signbit, x) && __LIBM_MATHFUNI(signbit, result)) { /* pow(-0.0,negative) */
						return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_MINUS);
					} else { /* pow(+0.0,negative) */
						return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_ZEROMINUS);
					}
				} else {
					/* pow overflow */
					return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_OVERFLOW);
				}
			}
		}
	} else if (result == 0.0 &&
	           __LIBM_MATHFUNI(finite, x) &&
	           __LIBM_MATHFUNI(finite, y) &&
	           __LIBM_LIB_VERSION != __LIBM_IEEE) {
		if (x == 0.0) {
			if (y == 0.0) {
				/* pow(0.0, 0.0) */
				return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_ZERO);
			}
		} else {
			/* pow underflow */
			return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_UNDERFLOW);
		}
	}
	return result;
}
#include <libm/fcomp.h>
#include <libm/nan.h>
#include <libm/matherr.h>
#include <libm/sqrt.h>
/* Return the square root of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_sqrt)(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2(isless, x, 0.0))
		return __kernel_standard(x, x, __LIBM_MATHFUN1I(nan, ""), __LIBM_KMATHERR_SQRT); /* sqrt(negative) */
	return __LIBM_MATHFUN(sqrt, x);
}
#include <libm/finite.h>
#include <libm/isnan.h>
#include <libm/matherr.h>
#include <libm/pow.h>
/* Return X to the Y power */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_powf float
NOTHROW(LIBCCALL libc_powf)(float x,
                            float y) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	float result;
	result = __LIBM_MATHFUN2F(pow, x, y);
	/*
	 * ====================================================
	 * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Permission to use, copy, modify, and distribute this
	 * software is freely granted, provided that this notice 
	 * is preserved.
	 * ====================================================
	 */
	if (!__LIBM_MATHFUNIF(finite, result)) {
		if (__LIBM_MATHFUNIF(isnan, y) && x == 1.0f) {
			result = 1.0f;
		} else if (__LIBM_LIB_VERSION != __LIBM_IEEE) {
			if (__LIBM_MATHFUNIF(isnan, x)) {
				if (y == 0.0f) /* pow(NaN,0.0) */
					return __kernel_standard_f(x, y, result, __LIBM_KMATHERR_POW_NAN);
			} else if (__LIBM_MATHFUNIF(finite, x) && __LIBM_MATHFUNIF(finite, y)) {
				if (__LIBM_MATHFUNIF(isnan, result)) { /* pow neg**non-int */
					return __kernel_standard_f(x, y, result, __LIBM_KMATHERR_POW_NONINT);
				} else if (x == 0.0f && y < 0.0f) {
					if (__LIBM_MATHFUNIF(signbit, x) && __LIBM_MATHFUNIF(signbit, result)) { /* pow(-0.0,negative) */
						return __kernel_standard_f(x, y, result, __LIBM_KMATHERR_POW_MINUS);
					} else { /* pow(+0.0,negative) */
						return __kernel_standard_f(x, y, result, __LIBM_KMATHERR_POW_ZEROMINUS);
					}
				} else {
					/* pow overflow */
					return __kernel_standard_f(x, y, result, __LIBM_KMATHERR_POW_OVERFLOW);
				}
			}
		}
	} else if (result == 0.0f &&
	           __LIBM_MATHFUNIF(finite, x) &&
	           __LIBM_MATHFUNIF(finite, y) &&
	           __LIBM_LIB_VERSION != __LIBM_IEEE) {
		if (x == 0.0f) {
			if (y == 0.0f) {
				/* pow(0.0, 0.0) */
				return __kernel_standard_f(x, y, result, __LIBM_KMATHERR_POW_ZERO);
			}
		} else {
			/* pow underflow */
			return __kernel_standard_f(x, y, result, __LIBM_KMATHERR_POW_UNDERFLOW);
		}
	}
	return result;
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)libc_pow((double)x, (double)y);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
#include <libm/fcomp.h>
#include <libm/nan.h>
#include <libm/matherr.h>
#include <libm/sqrt.h>
/* Return the square root of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_sqrtf)(float x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2F(isless, x, 0.0f))
		return __kernel_standard_f(x, x, __LIBM_MATHFUN1IF(nan, ""), __LIBM_KMATHERR_SQRT); /* sqrt(negative) */
	return __LIBM_MATHFUNF(sqrt, x);
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)libc_sqrt((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
#include <libm/finite.h>
#include <libm/isnan.h>
#include <libm/matherr.h>
#include <libm/pow.h>
/* Return X to the Y power */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_powl __LONGDOUBLE
NOTHROW(LIBCCALL libc_powl)(__LONGDOUBLE x,
                            __LONGDOUBLE y) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	__LONGDOUBLE result;
	result = __LIBM_MATHFUN2L(pow, x, y);
	/*
	 * ====================================================
	 * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Permission to use, copy, modify, and distribute this
	 * software is freely granted, provided that this notice 
	 * is preserved.
	 * ====================================================
	 */
	if (!__LIBM_MATHFUNIL(finite, result)) {
		if (__LIBM_MATHFUNIL(isnan, y) && x == 1.0L) {
			result = 1.0L;
		} else if (__LIBM_LIB_VERSION != __LIBM_IEEE) {
			if (__LIBM_MATHFUNIL(isnan, x)) {
				if (y == 0.0L) /* pow(NaN,0.0) */
					return __kernel_standard_l(x, y, result, __LIBM_KMATHERR_POW_NAN);
			} else if (__LIBM_MATHFUNIL(finite, x) && __LIBM_MATHFUNIL(finite, y)) {
				if (__LIBM_MATHFUNIL(isnan, result)) { /* pow neg**non-int */
					return __kernel_standard_l(x, y, result, __LIBM_KMATHERR_POW_NONINT);
				} else if (x == 0.0L && y < 0.0L) {
					if (__LIBM_MATHFUNIL(signbit, x) && __LIBM_MATHFUNIL(signbit, result)) { /* pow(-0.0,negative) */
						return __kernel_standard_l(x, y, result, __LIBM_KMATHERR_POW_MINUS);
					} else { /* pow(+0.0,negative) */
						return __kernel_standard_l(x, y, result, __LIBM_KMATHERR_POW_ZEROMINUS);
					}
				} else {
					/* pow overflow */
					return __kernel_standard_l(x, y, result, __LIBM_KMATHERR_POW_OVERFLOW);
				}
			}
		}
	} else if (result == 0.0L &&
	           __LIBM_MATHFUNIL(finite, x) &&
	           __LIBM_MATHFUNIL(finite, y) &&
	           __LIBM_LIB_VERSION != __LIBM_IEEE) {
		if (x == 0.0L) {
			if (y == 0.0L) {
				/* pow(0.0, 0.0) */
				return __kernel_standard_l(x, y, result, __LIBM_KMATHERR_POW_ZERO);
			}
		} else {
			/* pow underflow */
			return __kernel_standard_l(x, y, result, __LIBM_KMATHERR_POW_UNDERFLOW);
		}
	}
	return result;
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)libc_pow((double)x, (double)y);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
#include <libm/fcomp.h>
#include <libm/nan.h>
#include <libm/matherr.h>
#include <libm/sqrt.h>
/* Return the square root of X */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_sqrtl)(__LONGDOUBLE x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2L(isless, x, 0.0L))
		return __kernel_standard_l(x, x, __LIBM_MATHFUN1IL(nan, ""), __LIBM_KMATHERR_SQRT); /* sqrt(negative) */
	return __LIBM_MATHFUNL(sqrt, x);
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)libc_sqrt((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
/* Return `sqrt(X*X + Y*Y)' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_hypotf)(float x,
                              float y) {
	return (float)libc_hypot((double)x, (double)y);
}
/* Return `sqrt(X*X + Y*Y)' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_hypotl)(__LONGDOUBLE x,
                              __LONGDOUBLE y) {
	return (__LONGDOUBLE)libc_hypot((double)x, (double)y);
}
#include <libm/cbrt.h>
/* Return the cube root of X */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_cbrt)(double x) {
	return __LIBM_MATHFUN(cbrt, x);
}
#include <libm/cbrt.h>
/* Return the cube root of X */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_cbrtf)(float x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	return __LIBM_MATHFUNF(cbrt, x);
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)libc_cbrt((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
#include <libm/cbrt.h>
/* Return the cube root of X */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_cbrtl)(__LONGDOUBLE x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	return __LIBM_MATHFUNL(cbrt, x);
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)libc_cbrt((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
#include <hybrid/typecore.h>
#include <libm/ceil.h>
/* Smallest integral value not less than X */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_ceil)(double x) {
#ifdef __LIBM_MATHFUN
	return __LIBM_MATHFUN(ceil, x);
#else /* __LIBM_MATHFUN */
	double result;
	result = (double)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result < x)
		result += 1.0;
	return result;
#endif /* !__LIBM_MATHFUN */
}
#include <libm/fabs.h>
/* Absolute value of X */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_fabs)(double x) {
#ifdef __LIBM_MATHFUN
	return __LIBM_MATHFUN(fabs, x);
#else /* __LIBM_MATHFUN */
	return x < 0.0 ? -x : x;
#endif /* !__LIBM_MATHFUN */
}
#include <hybrid/typecore.h>
#include <libm/floor.h>
/* Largest integer not greater than X */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_floor)(double x) {
#ifdef __LIBM_MATHFUN
	return __LIBM_MATHFUN(floor, x);
#else /* __LIBM_MATHFUN */
	double result;
	result = (double)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result > x)
		result -= 1.0;
	return result;
#endif /* !__LIBM_MATHFUN */
}
#include <libm/isinf.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
#include <libm/fmod.h>
/* Floating-point modulo remainder of X/Y */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_fmod)(double x,
                            double y) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUN(isinf, x) || y == 0.0) &&
	    !__LIBM_MATHFUN2(isunordered, x, y))
		return __kernel_standard(x, y, y, __LIBM_KMATHERR_FMOD); /* fmod(+-Inf,y) or fmod(x,0) */
	return __LIBM_MATHFUN2(fmod, x, y);
}
#include <hybrid/typecore.h>
#include <libm/ceil.h>
/* Smallest integral value not less than X */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_ceilf)(float x) {
#ifdef __LIBM_MATHFUNF
	return __LIBM_MATHFUNF(ceil, x);
#else /* __LIBM_MATHFUNF */
	float result;
	result = (float)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result < x)
		result += 1.0f;
	return result;
#endif /* !__LIBM_MATHFUNF */
}
#include <libm/fabs.h>
/* Absolute value of X */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_fabsf)(float x) {
#ifdef __LIBM_MATHFUNF
	return __LIBM_MATHFUNF(fabs, x);
#else /* __LIBM_MATHFUNF */
	return x < 0.0f ? -x : x;
#endif /* !__LIBM_MATHFUNF */
}
#include <hybrid/typecore.h>
#include <libm/floor.h>
/* Largest integer not greater than X */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_floorf)(float x) {
#ifdef __LIBM_MATHFUNF
	return __LIBM_MATHFUNF(floor, x);
#else /* __LIBM_MATHFUNF */
	float result;
	result = (float)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result > x)
		result -= 1.0f;
	return result;
#endif /* !__LIBM_MATHFUNF */
}
#include <libm/isinf.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
#include <libm/fmod.h>
/* Floating-point modulo remainder of X/Y */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_fmodf)(float x,
                             float y) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUNF(isinf, x) || y == 0.0f) &&
	    !__LIBM_MATHFUN2F(isunordered, x, y))
		return __kernel_standard_f(x, y, y, __LIBM_KMATHERR_FMOD); /* fmod(+-Inf,y) or fmod(x,0) */
	return __LIBM_MATHFUN2F(fmod, x, y);
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)libc_fmod((double)x, (double)y);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
#include <hybrid/typecore.h>
#include <libm/ceil.h>
/* Smallest integral value not less than X */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_ceill)(__LONGDOUBLE x) {
#ifdef __LIBM_MATHFUNL
	return __LIBM_MATHFUNL(ceil, x);
#else /* __LIBM_MATHFUNL */
	__LONGDOUBLE result;
	result = (__LONGDOUBLE)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result < x)
		result += 1.0L;
	return result;
#endif /* !__LIBM_MATHFUNL */
}
#include <libm/fabs.h>
/* Absolute value of X */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_fabsl)(__LONGDOUBLE x) {
#ifdef __LIBM_MATHFUNL
	return __LIBM_MATHFUNL(fabs, x);
#else /* __LIBM_MATHFUNL */
	return x < 0.0L ? -x : x;
#endif /* !__LIBM_MATHFUNL */
}
#include <hybrid/typecore.h>
#include <libm/floor.h>
/* Largest integer not greater than X */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_floorl)(__LONGDOUBLE x) {
#ifdef __LIBM_MATHFUNL
	return __LIBM_MATHFUNL(floor, x);
#else /* __LIBM_MATHFUNL */
	__LONGDOUBLE result;
	result = (__LONGDOUBLE)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result > x)
		result -= 1.0L;
	return result;
#endif /* !__LIBM_MATHFUNL */
}
#include <libm/isinf.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
#include <libm/fmod.h>
/* Floating-point modulo remainder of X/Y */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_fmodl)(__LONGDOUBLE x,
                             __LONGDOUBLE y) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUNL(isinf, x) || y == 0.0L) &&
	    !__LIBM_MATHFUN2L(isunordered, x, y))
		return __kernel_standard_l(x, y, y, __LIBM_KMATHERR_FMOD); /* fmod(+-Inf,y) or fmod(x,0) */
	return __LIBM_MATHFUN2L(fmod, x, y);
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)libc_fmod((double)x, (double)y);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
#include <libm/copysign.h>
/* Return X with its signed changed to Y's */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_copysign)(double num,
                                double sign) {
#ifdef __LIBM_MATHFUN2
	return __LIBM_MATHFUN2(copysign, num, sign);
#else /* __LIBM_MATHFUN2 */
	if ((num < 0.0) != (sign < 0.0))
		num = -num;
	return num;
#endif /* !__LIBM_MATHFUN2 */
}
#include <libm/nan.h>
/* Return representation of qNaN for double type */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_nan)(char const *tagb) {
	return __LIBM_MATHFUN1I(nan, tagb);
}
#include <libm/copysign.h>
/* Return X with its signed changed to Y's */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_copysignf)(float num,
                                 float sign) {
#ifdef __LIBM_MATHFUN2F
	return __LIBM_MATHFUN2F(copysign, num, sign);
#else /* __LIBM_MATHFUN2F */
	if ((num < 0.0f) != (sign < 0.0f))
		num = -num;
	return num;
#endif /* !__LIBM_MATHFUN2F */
}
#include <libm/nan.h>
/* Return representation of qNaN for double type */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_nanf)(char const *tagb) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	return __LIBM_MATHFUN1IF(nan, tagb);
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)libc_nan(tagb);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
#include <libm/copysign.h>
/* Return X with its signed changed to Y's */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_copysignl)(__LONGDOUBLE num,
                                 __LONGDOUBLE sign) {
#ifdef __LIBM_MATHFUN2L
	return __LIBM_MATHFUN2L(copysign, num, sign);
#else /* __LIBM_MATHFUN2L */
	if ((num < 0.0L) != (sign < 0.0L))
		num = -num;
	return num;
#endif /* !__LIBM_MATHFUN2L */
}
#include <libm/nan.h>
/* Return representation of qNaN for double type */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_nanl)(char const *tagb) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	return __LIBM_MATHFUN1IL(nan, tagb);
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)libc_nan(tagb);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_erff)(float x) {
	return (float)libc_erf((double)x);
}
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_erfcf)(float x) {
	return (float)libc_erfc((double)x);
}
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_lgammaf)(float x) {
	return (float)libc_lgamma((double)x);
}
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_erfl)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_erf((double)x);
}
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_erfcl)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_erfc((double)x);
}
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_lgammal)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_lgamma((double)x);
}
/* True gamma function */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_tgammaf)(float x) {
	return (float)libc_tgamma((double)x);
}
/* True gamma function */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_tgammal)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_tgamma((double)x);
}
#include <libm/rint.h>
/* Return the integer nearest X in the direction of the prevailing rounding mode */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_rint)(double x) {
	return __LIBM_MATHFUN(rint, x);
}
#include <libm/nextafter.h>
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_nextafter)(double x,
                                 double y) {
	return __LIBM_MATHFUN2(nextafter, x, y);
}
#include <libm/matherr.h>
#include <libm/isnan.h>
#include <libm/isinf.h>
#include <libm/remainder.h>
/* Return the remainder of integer division X/P with infinite precision */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_remainder)(double x,
                                 double p) {
	if (((p == 0.0 && !__LIBM_MATHFUN(isnan, x)) ||
	     (__LIBM_MATHFUN(isinf, x) && !__LIBM_MATHFUN(isnan, p))) &&
	    __LIBM_LIB_VERSION != __LIBM_IEEE)
		return __kernel_standard(x, p, p, __LIBM_KMATHERR_REMAINDER); /* remainder domain */
	return __LIBM_MATHFUN2(remainder, x, p);
}
#include <libm/ilogb.h>
#include <libm/matherr.h>
#include <bits/mathdef.h>
/* Return the binary exponent of X, which must be nonzero */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED int
NOTHROW(LIBCCALL libc_ilogb)(double x) {
	int result;
	result = __LIBM_MATHFUNI(ilogb, x);
	if (result == __FP_ILOGB0 || result == __FP_ILOGBNAN || result == INT_MAX)
		__kernel_standard(x, x, x, __LIBM_KMATHERRF_ILOGB);
	return result;
}
#include <libm/rint.h>
/* Return the integer nearest X in the direction of the prevailing rounding mode */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_rintf)(float x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	return __LIBM_MATHFUNF(rint, x);
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)libc_rint((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
#include <libm/nextafter.h>
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_nextafterf)(float x,
                                  float y) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	return __LIBM_MATHFUN2F(nextafter, x, y);
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)libc_nextafter((double)x, (double)y);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
#include <libm/matherr.h>
#include <libm/isnan.h>
#include <libm/isinf.h>
#include <libm/remainder.h>
/* Return the remainder of integer division X/P with infinite precision */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_remainderf)(float x,
                                  float p) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	if (((p == 0.0f && !__LIBM_MATHFUNF(isnan, x)) ||
	     (__LIBM_MATHFUNF(isinf, x) && !__LIBM_MATHFUNF(isnan, p))) &&
	    __LIBM_LIB_VERSION != __LIBM_IEEE)
		return __kernel_standard_f(x, p, p, __LIBM_KMATHERR_REMAINDER); /* remainder domain */
	return __LIBM_MATHFUN2F(remainder, x, p);
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)libc_remainder((double)x, (double)p);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
#include <libm/ilogb.h>
#include <libm/matherr.h>
#include <bits/mathdef.h>
/* Return the binary exponent of X, which must be nonzero */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED int
NOTHROW(LIBCCALL libc_ilogbf)(float x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)


	int result;
	result = __LIBM_MATHFUNIF(ilogb, x);
	if (result == __FP_ILOGB0 || result == __FP_ILOGBNAN || result == INT_MAX)
		__kernel_standard_f(x, x, x, __LIBM_KMATHERRF_ILOGB);
	return result;
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ */
	return libc_ilogb((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ */
}
#include <libm/rint.h>
/* Return the integer nearest X in the direction of the prevailing rounding mode */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_rintl)(__LONGDOUBLE x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	return __LIBM_MATHFUNL(rint, x);
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)libc_rint((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
#include <libm/nextafter.h>
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_nextafterl)(__LONGDOUBLE x,
                                  __LONGDOUBLE y) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	return __LIBM_MATHFUN2L(nextafter, x, y);
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)libc_nextafter((double)x, (double)y);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
#include <libm/matherr.h>
#include <libm/isnan.h>
#include <libm/isinf.h>
#include <libm/remainder.h>
/* Return the remainder of integer division X/P with infinite precision */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_remainderl)(__LONGDOUBLE x,
                                  __LONGDOUBLE p) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	if (((p == 0.0L && !__LIBM_MATHFUNL(isnan, x)) ||
	     (__LIBM_MATHFUNL(isinf, x) && !__LIBM_MATHFUNL(isnan, p))) &&
	    __LIBM_LIB_VERSION != __LIBM_IEEE)
		return __kernel_standard_l(x, p, p, __LIBM_KMATHERR_REMAINDER); /* remainder domain */
	return __LIBM_MATHFUN2L(remainder, x, p);
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)libc_remainder((double)x, (double)p);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
#include <libm/ilogb.h>
#include <libm/matherr.h>
#include <bits/mathdef.h>
/* Return the binary exponent of X, which must be nonzero */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED int
NOTHROW(LIBCCALL libc_ilogbl)(__LONGDOUBLE x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)


	int result;
	result = __LIBM_MATHFUNIL(ilogb, x);
	if (result == __FP_ILOGB0 || result == __FP_ILOGBNAN || result == INT_MAX)
		__kernel_standard_l(x, x, x, __LIBM_KMATHERRF_ILOGB);
	return result;
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ */
	return libc_ilogb((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ */
}
#include <libm/nexttoward.h>
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_nexttoward)(double x,
                                  __LONGDOUBLE y) {
#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_nexttoward((__IEEE754_DOUBLE_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__)y);
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
	return (double)__ieee754_nexttowardf((__IEEE754_FLOAT_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__)y);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
#else /* __IEEE854_LONG_DOUBLE_TYPE__ */
	return (double)libc_nextafterl((__LONGDOUBLE)x, y);
#endif /* !__IEEE854_LONG_DOUBLE_TYPE__ */
}
#include <libm/scalbn.h>
/* Return X times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_scalbn)(double x,
                              int n) {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_scalbn((__IEEE754_DOUBLE_TYPE__)x, n);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (double)__ieee754_scalbnf((__IEEE754_FLOAT_TYPE__)x, n);
#else /* ... */
	return (double)__ieee854_scalbnl((__IEEE854_LONG_DOUBLE_TYPE__)x, n);
#endif /* !... */
}
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_scalbln, libc_scalbn);
#else /* __SIZEOF_INT__ == __SIZEOF_LONG__ */
#include <libm/scalbn.h>
/* Return X times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_scalbln)(double x,
                               long int n) {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_scalbln((__IEEE754_DOUBLE_TYPE__)x, n);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (double)__ieee754_scalblnf((__IEEE754_FLOAT_TYPE__)x, n);
#else /* ... */
	return (double)__ieee854_scalblnl((__IEEE854_LONG_DOUBLE_TYPE__)x, n);
#endif /* !... */
}
#endif /* __SIZEOF_INT__ != __SIZEOF_LONG__ */
#include <hybrid/typecore.h>
#include <libm/round.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_round)(double x) {
#ifdef __LIBM_MATHFUN
	return (double)__LIBM_MATHFUN(round, x);
#else /* __LIBM_MATHFUN */
	double result;
	result = (double)(__INTMAX_TYPE__)x;
	if (x < 0.0) {
		/* result >= x */
		if ((result - x) >= 0.5)
			result -= 1.0;
	} else {
		/* result <= x */
		if ((x - result) >= 0.5)
			result += 1.0;
	}
	return result;
#endif /* !__LIBM_MATHFUN */
}
#include <hybrid/typecore.h>
#include <libm/trunc.h>
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_trunc)(double x) {
#ifdef __LIBM_MATHFUN
	return __LIBM_MATHFUN(trunc, x);
#else /* __LIBM_MATHFUN */
	return (double)(__INTMAX_TYPE__)x;
#endif /* !__LIBM_MATHFUN */
}
#include <hybrid/typecore.h>
#include <libm/lrint.h>
/* Round X to nearest integral value according to current rounding direction */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED long int
NOTHROW(LIBCCALL libc_lrint)(double x) {
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(lrint, x);
#else /* __LIBM_MATHFUNI */
	return (long int)libc_rint(x);
#endif /* !__LIBM_MATHFUNI */
}
#include <hybrid/typecore.h>
#include <libm/lround.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED long int
NOTHROW(LIBCCALL libc_lround)(double x) {
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(lround, x);
#else /* __LIBM_MATHFUNI */
	return (long int)libc_round(x);
#endif /* !__LIBM_MATHFUNI */
}
/* Return positive difference between X and Y */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_fdim)(double x,
                            double y) {
	/* TODO: ieee754-specific function */
	return libc_fabs(y - x);
}
/* Return maximum numeric value from X and Y */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_fmax)(double x,
                            double y) {
	/* TODO: ieee754-specific function */
	return x < y ? y : x;
}
/* Return minimum numeric value from X and Y */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_fmin)(double x,
                            double y) {
	/* TODO: ieee754-specific function */
	return x < y ? x : y;
}
/* Multiply-add function computed as a ternary operation */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_fma)(double x,
                           double y,
                           double z) {
	/* TODO: ieee754-specific function */
	return (x * y) + z;
}
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS(libc_llrint, libc_lrint);
#else /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
#include <hybrid/typecore.h>
#include <libm/lrint.h>
/* Round X to nearest integral value according to current rounding direction */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGLONG
NOTHROW(LIBCCALL libc_llrint)(double x) {
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(llrint, x);
#else /* __LIBM_MATHFUNI */
	return (__LONGLONG)libc_rint(x);
#endif /* !__LIBM_MATHFUNI */
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_LONG_LONG__ */
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS(libc_llround, libc_lround);
#else /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
#include <hybrid/typecore.h>
#include <libm/lround.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGLONG
NOTHROW(LIBCCALL libc_llround)(double x) {
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(llround, x);
#else /* __LIBM_MATHFUNI */
	return (__LONGLONG)libc_round(x);
#endif /* !__LIBM_MATHFUNI */
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_LONG_LONG__ */
#include <libm/nexttoward.h>
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_nexttowardf)(float x,
                                   __LONGDOUBLE y) {
#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (float)__ieee754_nexttowardf((__IEEE754_FLOAT_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__)y);
#else /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ */
	return (float)__ieee754_nexttoward((__IEEE754_DOUBLE_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__)y);
#endif /* !__IEEE754_FLOAT_TYPE_IS_FLOAT__ */
#else /* __IEEE854_LONG_DOUBLE_TYPE__ */
	return (float)libc_nextafterl((__LONGDOUBLE)x, y);
#endif /* !__IEEE854_LONG_DOUBLE_TYPE__ */
}
#include <libm/scalbn.h>
/* Return X times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_scalbnf)(float x,
                               int n) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	
#ifdef __IEEE754_DOUBLE_TYPE_IS_FLOAT__
	return (float)__ieee754_scalbn((__IEEE754_DOUBLE_TYPE__)x, n);
#elif defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
	return (float)__ieee754_scalbnf((__IEEE754_FLOAT_TYPE__)x, n);
#else /* ... */
	return (float)__ieee854_scalbnl((__IEEE854_LONG_DOUBLE_TYPE__)x, n);
#endif /* !... */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)libc_scalbn((double)x, n);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_scalblnf, libc_scalbnf);
#else /* __SIZEOF_INT__ == __SIZEOF_LONG__ */
#include <libm/scalbn.h>
/* Return X times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_scalblnf)(float x,
                                long int n) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	
#ifdef __IEEE754_DOUBLE_TYPE_IS_FLOAT__
	return (float)__ieee754_scalbln((__IEEE754_DOUBLE_TYPE__)x, n);
#elif defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
	return (float)__ieee754_scalblnf((__IEEE754_FLOAT_TYPE__)x, n);
#else /* ... */
	return (float)__ieee854_scalblnl((__IEEE854_LONG_DOUBLE_TYPE__)x, n);
#endif /* !... */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)libc_scalbln((double)x, n);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
#endif /* __SIZEOF_INT__ != __SIZEOF_LONG__ */
#include <hybrid/typecore.h>
#include <libm/round.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_roundf)(float x) {
#ifdef __LIBM_MATHFUNF
	return (float)__LIBM_MATHFUNF(round, x);
#else /* __LIBM_MATHFUNF */
	float result;
	result = (float)(__INTMAX_TYPE__)x;
	if (x < 0.0f) {
		/* result >= x */
		if ((result - x) >= 0.5f)
			result -= 1.0f;
	} else {
		/* result <= x */
		if ((x - result) >= 0.5f)
			result += 1.0f;
	}
	return result;
#endif /* !__LIBM_MATHFUNF */
}
#include <hybrid/typecore.h>
#include <libm/trunc.h>
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_truncf)(float x) {
#ifdef __LIBM_MATHFUNF
	return __LIBM_MATHFUNF(trunc, x);
#else /* __LIBM_MATHFUNF */
	return (float)(__INTMAX_TYPE__)x;
#endif /* !__LIBM_MATHFUNF */
}
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_remquof)(float x,
                               float y,
                               int *pquo) {
	return (float)libc_remquo((double)x, (double)y, pquo);
}
#include <hybrid/typecore.h>
#include <libm/lrint.h>
/* Round X to nearest integral value according to current rounding direction */
INTERN ATTR_SECTION(".text.crt.math.math") long int
NOTHROW_NCX(LIBCCALL libc_lrintf)(float x) {
#ifdef __LIBM_MATHFUNIF
	return __LIBM_MATHFUNIF(lrint, x);
#else /* __LIBM_MATHFUNIF */
	return (long int)libc_rintf(x);
#endif /* !__LIBM_MATHFUNIF */
}
#include <hybrid/typecore.h>
#include <libm/lround.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED long int
NOTHROW(LIBCCALL libc_lroundf)(float x) {
#ifdef __LIBM_MATHFUNIF
	return __LIBM_MATHFUNIF(lround, x);
#else /* __LIBM_MATHFUNIF */
	return (long int)libc_roundf(x);
#endif /* !__LIBM_MATHFUNIF */
}
/* Return positive difference between X and Y */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_fdimf)(float x,
                             float y) {
	/* TODO: ieee754-specific function */
	return libc_fabsf(y - x);
}
/* Return maximum numeric value from X and Y */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_fmaxf)(float x,
                             float y) {
	/* TODO: ieee754-specific function */
	return x < y ? y : x;
}
/* Return minimum numeric value from X and Y */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_fminf)(float x,
                             float y) {
	/* TODO: ieee754-specific function */
	return x < y ? x : y;
}
/* Multiply-add function computed as a ternary operation */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_fmaf)(float x,
                            float y,
                            float z) {
	/* TODO: ieee754-specific function */
	return (x * y) + z;
}
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS(libc_llrintf, libc_lrintf);
#else /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
#include <hybrid/typecore.h>
#include <libm/lrint.h>
/* Round X to nearest integral value according to current rounding direction */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGLONG
NOTHROW(LIBCCALL libc_llrintf)(float x) {
#ifdef __LIBM_MATHFUNIF
	return __LIBM_MATHFUNIF(llrint, x);
#else /* __LIBM_MATHFUNIF */
	return (__LONGLONG)libc_rintf(x);
#endif /* !__LIBM_MATHFUNIF */
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_LONG_LONG__ */
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS(libc_llroundf, libc_lroundf);
#else /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
#include <hybrid/typecore.h>
#include <libm/lround.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGLONG
NOTHROW(LIBCCALL libc_llroundf)(float x) {
#ifdef __LIBM_MATHFUNIF
	return __LIBM_MATHFUNIF(llround, x);
#else /* __LIBM_MATHFUNIF */
	return (__LONGLONG)libc_roundf(x);
#endif /* !__LIBM_MATHFUNIF */
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_LONG_LONG__ */
#include <libm/scalbn.h>
/* Return X times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_scalbnl)(__LONGDOUBLE x,
                               int n) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	
#ifdef __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return (__LONGDOUBLE)__ieee754_scalbn((__IEEE754_DOUBLE_TYPE__)x, n);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_scalbnf((__IEEE754_FLOAT_TYPE__)x, n);
#else /* ... */
	return (__LONGDOUBLE)__ieee854_scalbnl((__IEEE854_LONG_DOUBLE_TYPE__)x, n);
#endif /* !... */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)libc_scalbn((double)x, n);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_scalblnl, libc_scalbnl);
#else /* __SIZEOF_INT__ == __SIZEOF_LONG__ */
#include <libm/scalbn.h>
/* Return X times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_scalblnl)(__LONGDOUBLE x,
                                long int n) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	
#ifdef __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return (__LONGDOUBLE)__ieee754_scalbln((__IEEE754_DOUBLE_TYPE__)x, n);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_scalblnf((__IEEE754_FLOAT_TYPE__)x, n);
#else /* ... */
	return (__LONGDOUBLE)__ieee854_scalblnl((__IEEE854_LONG_DOUBLE_TYPE__)x, n);
#endif /* !... */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)libc_scalbln((double)x, n);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
#endif /* __SIZEOF_INT__ != __SIZEOF_LONG__ */
#include <hybrid/typecore.h>
#include <libm/round.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_roundl)(__LONGDOUBLE x) {
#ifdef __LIBM_MATHFUNL
	return (__LONGDOUBLE)__LIBM_MATHFUNL(round, x);
#else /* __LIBM_MATHFUNL */
	__LONGDOUBLE result;
	result = (__LONGDOUBLE)(__INTMAX_TYPE__)x;
	if (x < 0.0L) {
		/* result >= x */
		if ((result - x) >= 0.5L)
			result -= 1.0L;
	} else {
		/* result <= x */
		if ((x - result) >= 0.5L)
			result += 1.0L;
	}
	return result;
#endif /* !__LIBM_MATHFUNL */
}
#include <hybrid/typecore.h>
#include <libm/trunc.h>
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_truncl)(__LONGDOUBLE x) {
#ifdef __LIBM_MATHFUNL
	return __LIBM_MATHFUNL(trunc, x);
#else /* __LIBM_MATHFUNL */
	return (__LONGDOUBLE)(__INTMAX_TYPE__)x;
#endif /* !__LIBM_MATHFUNL */
}
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_remquol)(__LONGDOUBLE x,
                               __LONGDOUBLE y,
                               int *pquo) {
	return (__LONGDOUBLE)libc_remquo((double)x, (double)y, pquo);
}
#include <hybrid/typecore.h>
#include <libm/lrint.h>
/* Round X to nearest integral value according to current rounding direction */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED long int
NOTHROW(LIBCCALL libc_lrintl)(__LONGDOUBLE x) {
#ifdef __LIBM_MATHFUNIL
	return __LIBM_MATHFUNIL(lrint, x);
#else /* __LIBM_MATHFUNIL */
	return (long int)libc_rintl(x);
#endif /* !__LIBM_MATHFUNIL */
}
#include <hybrid/typecore.h>
#include <libm/lround.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED long int
NOTHROW(LIBCCALL libc_lroundl)(__LONGDOUBLE x) {
#ifdef __LIBM_MATHFUNIL
	return __LIBM_MATHFUNIL(lround, x);
#else /* __LIBM_MATHFUNIL */
	return (long int)libc_roundl(x);
#endif /* !__LIBM_MATHFUNIL */
}
/* Return positive difference between X and Y */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_fdiml)(__LONGDOUBLE x,
                             __LONGDOUBLE y) {
	/* TODO: ieee754-specific function */
	return libc_fabsl(y - x);
}
/* Return maximum numeric value from X and Y */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_fmaxl)(__LONGDOUBLE x,
                             __LONGDOUBLE y) {
	/* TODO: ieee754-specific function */
	return x < y ? y : x;
}
/* Return minimum numeric value from X and Y */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_fminl)(__LONGDOUBLE x,
                             __LONGDOUBLE y) {
	/* TODO: ieee754-specific function */
	return x < y ? x : y;
}
/* Multiply-add function computed as a ternary operation */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_fmal)(__LONGDOUBLE x,
                            __LONGDOUBLE y,
                            __LONGDOUBLE z) {
	/* TODO: ieee754-specific function */
	return (x * y) + z;
}
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS(libc_llrintl, libc_lrintl);
#else /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
#include <hybrid/typecore.h>
#include <libm/lrint.h>
/* Round X to nearest integral value according to current rounding direction */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGLONG
NOTHROW(LIBCCALL libc_llrintl)(__LONGDOUBLE x) {
#ifdef __LIBM_MATHFUNIL
	return __LIBM_MATHFUNIL(llrint, x);
#else /* __LIBM_MATHFUNIL */
	return (__LONGLONG)libc_rintl(x);
#endif /* !__LIBM_MATHFUNIL */
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_LONG_LONG__ */
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS(libc_llroundl, libc_lroundl);
#else /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
#include <hybrid/typecore.h>
#include <libm/lround.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGLONG
NOTHROW(LIBCCALL libc_llroundl)(__LONGDOUBLE x) {
#ifdef __LIBM_MATHFUNIL
	return __LIBM_MATHFUNIL(llround, x);
#else /* __LIBM_MATHFUNIL */
	return (__LONGLONG)libc_roundl(x);
#endif /* !__LIBM_MATHFUNIL */
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_LONG_LONG__ */
/* Another name occasionally used */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_pow10)(double x) {
	return libc_pow(10.0, x);
}
/* Cosine and sine of X */
INTERN ATTR_SECTION(".text.crt.math.math") __DECL_SIMD_sincosf NONNULL((2, 3)) void
NOTHROW(LIBCCALL libc_sincosf)(float x,
                               float *psinx,
                               float *pcosx) {
	double sinx, cosx;
	libc_sincos((double)x, &sinx, &cosx);
	*psinx = (float)sinx;
	*pcosx = (float)cosx;
}
/* A function missing in all standards: compute exponent to base ten */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_exp10f)(float x) {
	return (float)libc_exp10((double)x);
}
/* Another name occasionally used */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_pow10f)(float x) {
#if defined(__CRT_HAVE_powf) || defined(__CRT_HAVE___powf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
	return libc_powf(10.0f, x);
#else /* __CRT_HAVE_powf || __CRT_HAVE___powf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_pow || __CRT_HAVE___pow || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
	return (float)libc_pow10((double)x);
#endif /* !__CRT_HAVE_powf && !__CRT_HAVE___powf && !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_pow && !__CRT_HAVE___pow && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
}
/* Cosine and sine of X */
INTERN ATTR_SECTION(".text.crt.math.math") __DECL_SIMD_sincosl NONNULL((2, 3)) void
NOTHROW(LIBCCALL libc_sincosl)(__LONGDOUBLE x,
                               __LONGDOUBLE *psinx,
                               __LONGDOUBLE *pcosx) {
	double sinx, cosx;
	libc_sincos((double)x, &sinx, &cosx);
	*psinx = (__LONGDOUBLE)sinx;
	*pcosx = (__LONGDOUBLE)cosx;
}
/* A function missing in all standards: compute exponent to base ten */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_exp10l)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_exp10((double)x);
}
/* Another name occasionally used */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_pow10l)(__LONGDOUBLE x) {
#if defined(__CRT_HAVE_powl) || defined(__CRT_HAVE___powl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
	return libc_powl(10.0L, x);
#else /* __CRT_HAVE_powl || __CRT_HAVE___powl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_pow || __CRT_HAVE___pow || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
	return (__LONGDOUBLE)libc_pow10((double)x);
#endif /* !__CRT_HAVE_powl && !__CRT_HAVE___powl && !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__CRT_HAVE_pow && !__CRT_HAVE___pow && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
}
#include <libm/isinf.h>
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isinf)(double x) {
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(isinf, x);
#elif defined(__INFINITY)
	return x == __INFINITY;
#else /* ... */
	return x == __HUGE_VAL;
#endif /* !... */
}
#include <libm/isinf.h>
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isinff)(float x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__INFINITYF) || defined(__HUGE_VALF)



	
#ifdef __LIBM_MATHFUNIF
	return __LIBM_MATHFUNIF(isinf, x);
#elif defined(__INFINITYF)
	return x == __INFINITYF;
#else /* ... */
	return x == __HUGE_VALF;
#endif /* !... */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __INFINITYF || __HUGE_VALF */
	return libc_isinf((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__INFINITYF && !__HUGE_VALF */
}
#include <libm/isinf.h>
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isinfl)(__LONGDOUBLE x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__INFINITYL) || defined(__HUGE_VALL)



	
#ifdef __LIBM_MATHFUNIL
	return __LIBM_MATHFUNIL(isinf, x);
#elif defined(__INFINITYL)
	return x == __INFINITYL;
#else /* ... */
	return x == __HUGE_VALL;
#endif /* !... */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __INFINITYL || __HUGE_VALL */
	return libc_isinf((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__INFINITYL && !__HUGE_VALL */
}
#include <libm/finite.h>
/* Return nonzero if VALUE is finite and not NaN */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_finite)(double x) {
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(finite, x);
#else /* __LIBM_MATHFUNI */
	return !libc_isinf(x) && !libc_isnan(x);
#endif /* !__LIBM_MATHFUNI */
}
#include <libm/significand.h>
/* Return the fractional part of X after dividing out `ilogb(X)' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_significand)(double x) {
	return __LIBM_MATHFUN(significand, x);
}
#include <libm/finite.h>
/* Return nonzero if VALUE is finite and not NaN */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_finitef)(float x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || ((defined(__CRT_HAVE_isinff) || defined(__CRT_HAVE___isinff) || defined(__INFINITYF) || defined(__HUGE_VALF) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnanf) || defined(__CRT_HAVE___isnanf) || defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE___isnan) || defined(__CRT_HAVE__isnan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)))



	
#ifdef __LIBM_MATHFUNIF
	return __LIBM_MATHFUNIF(finite, x);
#else /* __LIBM_MATHFUNIF */
	return !libc_isinff(x) && !libc_isnanf(x);
#endif /* !__LIBM_MATHFUNIF */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || ((__CRT_HAVE_isinff || __CRT_HAVE___isinff || __INFINITYF || __HUGE_VALF || __CRT_HAVE_isinf || __CRT_HAVE___isinf || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __INFINITY || __HUGE_VAL) && (__CRT_HAVE_isnanf || __CRT_HAVE___isnanf || __CRT_HAVE_isnan || __CRT_HAVE___isnan || __CRT_HAVE__isnan || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) */
	return libc_finite((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && ((!__CRT_HAVE_isinff && !__CRT_HAVE___isinff && !__INFINITYF && !__HUGE_VALF && !__CRT_HAVE_isinf && !__CRT_HAVE___isinf && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && !__INFINITY && !__HUGE_VAL) || (!__CRT_HAVE_isnanf && !__CRT_HAVE___isnanf && !__CRT_HAVE_isnan && !__CRT_HAVE___isnan && !__CRT_HAVE__isnan && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) */
}
#include <libm/significand.h>
/* Return the fractional part of X after dividing out `ilogb(X)' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_significandf)(float x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	return __LIBM_MATHFUNF(significand, x);
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)libc_significand((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
#include <libm/finite.h>
/* Return nonzero if VALUE is finite and not NaN */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_finitel)(__LONGDOUBLE x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || ((defined(__CRT_HAVE_isinfl) || defined(__CRT_HAVE___isinfl) || defined(__INFINITYL) || defined(__HUGE_VALL) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnanl) || defined(__CRT_HAVE___isnanl) || defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE___isnan) || defined(__CRT_HAVE__isnan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)))



	
#ifdef __LIBM_MATHFUNIL
	return __LIBM_MATHFUNIL(finite, x);
#else /* __LIBM_MATHFUNIL */
	return !libc_isinfl(x) && !libc_isnanl(x);
#endif /* !__LIBM_MATHFUNIL */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || ((__CRT_HAVE_isinfl || __CRT_HAVE___isinfl || __INFINITYL || __HUGE_VALL || __CRT_HAVE_isinf || __CRT_HAVE___isinf || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __INFINITY || __HUGE_VAL) && (__CRT_HAVE_isnanl || __CRT_HAVE___isnanl || __CRT_HAVE_isnan || __CRT_HAVE___isnan || __CRT_HAVE__isnan || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) */
	return libc_finite((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && ((!__CRT_HAVE_isinfl && !__CRT_HAVE___isinfl && !__INFINITYL && !__HUGE_VALL && !__CRT_HAVE_isinf && !__CRT_HAVE___isinf && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && !__INFINITY && !__HUGE_VAL) || (!__CRT_HAVE_isnanl && !__CRT_HAVE___isnanl && !__CRT_HAVE_isnan && !__CRT_HAVE___isnan && !__CRT_HAVE__isnan && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) */
}
#include <libm/significand.h>
/* Return the fractional part of X after dividing out `ilogb(X)' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_significandl)(__LONGDOUBLE x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	return __LIBM_MATHFUNL(significand, x);
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)libc_significand((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
#include <libm/isnan.h>
/* Return nonzero if VALUE is not a number */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isnan)(double x) {
	return __LIBM_MATHFUNI(isnan, x);
}
#include <libm/isnan.h>
/* Return nonzero if VALUE is not a number */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isnanf)(float x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	return __LIBM_MATHFUNIF(isnan, x);
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return libc_isnan((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
#include <libm/isnan.h>
/* Return nonzero if VALUE is not a number */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isnanl)(__LONGDOUBLE x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	return __LIBM_MATHFUNIL(isnan, x);
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return libc_isnan((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_j0f)(float x) {
	return (float)libc_j0((double)x);
}
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_j1f)(float x) {
	return (float)libc_j1((double)x);
}
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_jnf)(int n,
                           float x) {
	return (float)libc_jn(n, (double)x);
}
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_y0f)(float x) {
	return (float)libc_y0((double)x);
}
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_y1f)(float x) {
	return (float)libc_y1((double)x);
}
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_ynf)(int n,
                           float x) {
	return (float)libc_yn(n, (double)x);
}
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_j0l)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_j0((double)x);
}
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_j1l)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_j1((double)x);
}
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_jnl)(int n,
                           __LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_jn(n, (double)x);
}
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_y0l)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_y0((double)x);
}
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_y1l)(__LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_y1((double)x);
}
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_ynl)(int n,
                           __LONGDOUBLE x) {
	return (__LONGDOUBLE)libc_yn(n, (double)x);
}
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW_NCX(LIBCCALL libc_lgammaf_r)(float x,
                                     int *signgamp) {
	return (float)libc_lgamma_r((double)x, signgamp);
}
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW_NCX(LIBCCALL libc_lgammal_r)(__LONGDOUBLE x,
                                     int *signgamp) {
	return (__LONGDOUBLE)libc_lgamma_r((double)x, signgamp);
}
#include <libm/isnan.h>
#include <libm/finite.h>
#include <libm/isinf.h>
#include <libm/matherr.h>
#include <parts/errno.h>
#include <libm/scalb.h>
/* Return X times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_scalb)(double x,
                             double fn) {
	/*
	 * ====================================================
	 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Developed at SunSoft, a Sun Microsystems, Inc. business.
	 * Permission to use, copy, modify, and distribute this
	 * software is freely granted, provided that this notice
	 * is preserved.
	 * ====================================================
	 */
	double result;
	result = __LIBM_MATHFUN2(scalb, x, fn);
	if (__LIBM_LIB_VERSION == __LIBM_SVID) {
		if (__LIBM_MATHFUN(isinf, result)) {
			if (__LIBM_MATHFUN(finite, x)) {
				return __kernel_standard(x, fn, result, __LIBM_KMATHERR_SCALB_OVERFLOW); /* scalb overflow */
			} else {
#ifdef __ERANGE
				__libc_seterrno(__ERANGE);
#endif /* __ERANGE */
			}
		} else if (result == 0.0 && result != x) {
			return __kernel_standard(x, fn, result, __LIBM_KMATHERR_SCALB_UNDERFLOW); /* scalb underflow */
		}
	} else {
		if (!__LIBM_MATHFUN(finite, result) || result == 0.0) {
			if (__LIBM_MATHFUN(isnan, result)) {
				if (!__LIBM_MATHFUN(isnan, x) && !__LIBM_MATHFUN(isnan, fn))
					result = __kernel_standard(x, fn, result, __LIBM_KMATHERR_SCALB_INVALID);
			} else if (__LIBM_MATHFUN(isinf, result)) {
				if (!__LIBM_MATHFUN(isinf, x) && !__LIBM_MATHFUN(isinf, fn))
					result = __kernel_standard(x, fn, result, __LIBM_KMATHERR_SCALB_OVERFLOW);
			} else {
				/* result == 0.  */
				if (x != 0.0 && !__LIBM_MATHFUN(isinf, fn))
					result = __kernel_standard(x, fn, result, __LIBM_KMATHERR_SCALB_UNDERFLOW);
			}
		}
	}
	return result;
}
#include <libm/isnan.h>
#include <libm/finite.h>
#include <libm/isinf.h>
#include <libm/matherr.h>
#include <parts/errno.h>
#include <libm/scalb.h>
/* Return X times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_scalbf)(float x,
                              float fn) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	/*
	 * ====================================================
	 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Developed at SunSoft, a Sun Microsystems, Inc. business.
	 * Permission to use, copy, modify, and distribute this
	 * software is freely granted, provided that this notice
	 * is preserved.
	 * ====================================================
	 */
	float result;
	result = __LIBM_MATHFUN2F(scalb, x, fn);
	if (__LIBM_LIB_VERSION == __LIBM_SVID) {
		if (__LIBM_MATHFUNF(isinf, result)) {
			if (__LIBM_MATHFUNF(finite, x)) {
				return __kernel_standard_f(x, fn, result, __LIBM_KMATHERR_SCALB_OVERFLOW); /* scalb overflow */
			} else {
#ifdef __ERANGE
				__libc_seterrno(__ERANGE);
#endif /* __ERANGE */
			}
		} else if (result == 0.0f && result != x) {
			return __kernel_standard_f(x, fn, result, __LIBM_KMATHERR_SCALB_UNDERFLOW); /* scalb underflow */
		}
	} else {
		if (!__LIBM_MATHFUNF(finite, result) || result == 0.0f) {
			if (__LIBM_MATHFUNF(isnan, result)) {
				if (!__LIBM_MATHFUNF(isnan, x) && !__LIBM_MATHFUNF(isnan, fn))
					result = __kernel_standard_f(x, fn, result, __LIBM_KMATHERR_SCALB_INVALID);
			} else if (__LIBM_MATHFUNF(isinf, result)) {
				if (!__LIBM_MATHFUNF(isinf, x) && !__LIBM_MATHFUNF(isinf, fn))
					result = __kernel_standard_f(x, fn, result, __LIBM_KMATHERR_SCALB_OVERFLOW);
			} else {
				/* result == 0.  */
				if (x != 0.0f && !__LIBM_MATHFUNF(isinf, fn))
					result = __kernel_standard_f(x, fn, result, __LIBM_KMATHERR_SCALB_UNDERFLOW);
			}
		}
	}
	return result;
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)libc_scalb((double)x, (double)fn);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
#include <libm/isnan.h>
#include <libm/finite.h>
#include <libm/isinf.h>
#include <libm/matherr.h>
#include <parts/errno.h>
#include <libm/scalb.h>
/* Return X times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_scalbl)(__LONGDOUBLE x,
                              __LONGDOUBLE fn) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	/*
	 * ====================================================
	 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Developed at SunSoft, a Sun Microsystems, Inc. business.
	 * Permission to use, copy, modify, and distribute this
	 * software is freely granted, provided that this notice
	 * is preserved.
	 * ====================================================
	 */
	__LONGDOUBLE result;
	result = __LIBM_MATHFUN2L(scalb, x, fn);
	if (__LIBM_LIB_VERSION == __LIBM_SVID) {
		if (__LIBM_MATHFUNL(isinf, result)) {
			if (__LIBM_MATHFUNL(finite, x)) {
				return __kernel_standard_l(x, fn, result, __LIBM_KMATHERR_SCALB_OVERFLOW); /* scalb overflow */
			} else {
#ifdef __ERANGE
				__libc_seterrno(__ERANGE);
#endif /* __ERANGE */
			}
		} else if (result == 0.0L && result != x) {
			return __kernel_standard_l(x, fn, result, __LIBM_KMATHERR_SCALB_UNDERFLOW); /* scalb underflow */
		}
	} else {
		if (!__LIBM_MATHFUNL(finite, result) || result == 0.0L) {
			if (__LIBM_MATHFUNL(isnan, result)) {
				if (!__LIBM_MATHFUNL(isnan, x) && !__LIBM_MATHFUNL(isnan, fn))
					result = __kernel_standard_l(x, fn, result, __LIBM_KMATHERR_SCALB_INVALID);
			} else if (__LIBM_MATHFUNL(isinf, result)) {
				if (!__LIBM_MATHFUNL(isinf, x) && !__LIBM_MATHFUNL(isinf, fn))
					result = __kernel_standard_l(x, fn, result, __LIBM_KMATHERR_SCALB_OVERFLOW);
			} else {
				/* result == 0.  */
				if (x != 0.0L && !__LIBM_MATHFUNL(isinf, fn))
					result = __kernel_standard_l(x, fn, result, __LIBM_KMATHERR_SCALB_UNDERFLOW);
			}
		}
	}
	return result;
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)libc_scalb((double)x, (double)fn);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
#include <libm/fpclassify.h>
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc___fpclassify)(double x) {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return __ieee754_fpclassify((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return __ieee754_fpclassifyf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	return __ieee854_fpclassifyl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#endif /* !... */
}
#include <libm/signbit.h>
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc___signbit)(double x) {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return __ieee754_signbit((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return __ieee754_signbitf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
	return __ieee854_signbitl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
	return x < 0.0;
#endif /* !... */
}
#include <libm/fpclassify.h>
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc___fpclassifyf)(float x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	
#ifdef __IEEE754_DOUBLE_TYPE_IS_FLOAT__
	return __ieee754_fpclassify((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
	return __ieee754_fpclassifyf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	return __ieee854_fpclassifyl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#endif /* !... */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return libc___fpclassify((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
#include <libm/signbit.h>
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc___signbitf)(float x) {
#ifdef __IEEE754_DOUBLE_TYPE_IS_FLOAT__
	return __ieee754_signbit((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
	return __ieee754_signbitf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
	return __ieee854_signbitl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
	return x < 0.0f;
#endif /* !... */
}
#include <libm/fpclassify.h>
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc___fpclassifyl)(__LONGDOUBLE x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	
#ifdef __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return __ieee754_fpclassify((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return __ieee754_fpclassifyf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	return __ieee854_fpclassifyl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#endif /* !... */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return libc___fpclassify((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
#include <libm/signbit.h>
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc___signbitl)(__LONGDOUBLE x) {
#ifdef __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return __ieee754_signbit((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return __ieee754_signbitf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)
	return __ieee854_signbitl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
	return x < 0.0L;
#endif /* !... */
}
#include <libm/issignaling.h>
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc___issignaling)(double x) {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return __ieee754_issignaling((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return __ieee754_issignalingf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	return __ieee854_issignalingl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#endif /* !... */
}
#include <libm/issignaling.h>
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc___issignalingf)(float x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	
#ifdef __IEEE754_DOUBLE_TYPE_IS_FLOAT__
	return __ieee754_issignaling((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
	return __ieee754_issignalingf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	return __ieee854_issignalingl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#endif /* !... */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return libc___issignaling((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
#include <libm/issignaling.h>
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc___issignalingl)(__LONGDOUBLE x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	
#ifdef __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return __ieee754_issignaling((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return __ieee754_issignalingf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	return __ieee854_issignalingl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#endif /* !... */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return libc___issignaling((double)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__atan, libc_atan);
DEFINE_PUBLIC_ALIAS(atan, libc_atan);
DEFINE_PUBLIC_ALIAS(__atan2, libc_atan2);
DEFINE_PUBLIC_ALIAS(atan2, libc_atan2);
DEFINE_PUBLIC_ALIAS(__acosf, libc_acosf);
DEFINE_PUBLIC_ALIAS(acosf, libc_acosf);
DEFINE_PUBLIC_ALIAS(__asinf, libc_asinf);
DEFINE_PUBLIC_ALIAS(asinf, libc_asinf);
DEFINE_PUBLIC_ALIAS(__atanf, libc_atanf);
DEFINE_PUBLIC_ALIAS(atanf, libc_atanf);
DEFINE_PUBLIC_ALIAS(__atan2f, libc_atan2f);
DEFINE_PUBLIC_ALIAS(atan2f, libc_atan2f);
DEFINE_PUBLIC_ALIAS(__cosf, libc_cosf);
DEFINE_PUBLIC_ALIAS(cosf, libc_cosf);
DEFINE_PUBLIC_ALIAS(__sinf, libc_sinf);
DEFINE_PUBLIC_ALIAS(sinf, libc_sinf);
DEFINE_PUBLIC_ALIAS(__tanf, libc_tanf);
DEFINE_PUBLIC_ALIAS(tanf, libc_tanf);
DEFINE_PUBLIC_ALIAS(__acosl, libc_acosl);
DEFINE_PUBLIC_ALIAS(acosl, libc_acosl);
DEFINE_PUBLIC_ALIAS(__asinl, libc_asinl);
DEFINE_PUBLIC_ALIAS(asinl, libc_asinl);
DEFINE_PUBLIC_ALIAS(__atanl, libc_atanl);
DEFINE_PUBLIC_ALIAS(atanl, libc_atanl);
DEFINE_PUBLIC_ALIAS(__atan2l, libc_atan2l);
DEFINE_PUBLIC_ALIAS(atan2l, libc_atan2l);
DEFINE_PUBLIC_ALIAS(__cosl, libc_cosl);
DEFINE_PUBLIC_ALIAS(cosl, libc_cosl);
DEFINE_PUBLIC_ALIAS(__sinl, libc_sinl);
DEFINE_PUBLIC_ALIAS(sinl, libc_sinl);
DEFINE_PUBLIC_ALIAS(__tanl, libc_tanl);
DEFINE_PUBLIC_ALIAS(tanl, libc_tanl);
DEFINE_PUBLIC_ALIAS(__coshf, libc_coshf);
DEFINE_PUBLIC_ALIAS(coshf, libc_coshf);
DEFINE_PUBLIC_ALIAS(__sinhf, libc_sinhf);
DEFINE_PUBLIC_ALIAS(sinhf, libc_sinhf);
DEFINE_PUBLIC_ALIAS(__tanhf, libc_tanhf);
DEFINE_PUBLIC_ALIAS(tanhf, libc_tanhf);
DEFINE_PUBLIC_ALIAS(__coshl, libc_coshl);
DEFINE_PUBLIC_ALIAS(coshl, libc_coshl);
DEFINE_PUBLIC_ALIAS(__sinhl, libc_sinhl);
DEFINE_PUBLIC_ALIAS(sinhl, libc_sinhl);
DEFINE_PUBLIC_ALIAS(__tanhl, libc_tanhl);
DEFINE_PUBLIC_ALIAS(tanhl, libc_tanhl);
DEFINE_PUBLIC_ALIAS(__acoshf, libc_acoshf);
DEFINE_PUBLIC_ALIAS(acoshf, libc_acoshf);
DEFINE_PUBLIC_ALIAS(__asinhf, libc_asinhf);
DEFINE_PUBLIC_ALIAS(asinhf, libc_asinhf);
DEFINE_PUBLIC_ALIAS(__atanhf, libc_atanhf);
DEFINE_PUBLIC_ALIAS(atanhf, libc_atanhf);
DEFINE_PUBLIC_ALIAS(__acoshl, libc_acoshl);
DEFINE_PUBLIC_ALIAS(acoshl, libc_acoshl);
DEFINE_PUBLIC_ALIAS(__asinhl, libc_asinhl);
DEFINE_PUBLIC_ALIAS(asinhl, libc_asinhl);
DEFINE_PUBLIC_ALIAS(__atanhl, libc_atanhl);
DEFINE_PUBLIC_ALIAS(atanhl, libc_atanhl);
DEFINE_PUBLIC_ALIAS(__exp, libc_exp);
DEFINE_PUBLIC_ALIAS(exp, libc_exp);
DEFINE_PUBLIC_ALIAS(__frexp, libc_frexp);
DEFINE_PUBLIC_ALIAS(frexp, libc_frexp);
DEFINE_PUBLIC_ALIAS(__ldexp, libc_ldexp);
DEFINE_PUBLIC_ALIAS(ldexp, libc_ldexp);
DEFINE_PUBLIC_ALIAS(__modf, libc_modf);
DEFINE_PUBLIC_ALIAS(modf, libc_modf);
DEFINE_PUBLIC_ALIAS(__expf, libc_expf);
DEFINE_PUBLIC_ALIAS(expf, libc_expf);
DEFINE_PUBLIC_ALIAS(__frexpf, libc_frexpf);
DEFINE_PUBLIC_ALIAS(frexpf, libc_frexpf);
DEFINE_PUBLIC_ALIAS(__ldexpf, libc_ldexpf);
DEFINE_PUBLIC_ALIAS(ldexpf, libc_ldexpf);
DEFINE_PUBLIC_ALIAS(__logf, libc_logf);
DEFINE_PUBLIC_ALIAS(logf, libc_logf);
DEFINE_PUBLIC_ALIAS(__log10f, libc_log10f);
DEFINE_PUBLIC_ALIAS(log10f, libc_log10f);
DEFINE_PUBLIC_ALIAS(__modff, libc_modff);
DEFINE_PUBLIC_ALIAS(modff, libc_modff);
DEFINE_PUBLIC_ALIAS(__expl, libc_expl);
DEFINE_PUBLIC_ALIAS(expl, libc_expl);
DEFINE_PUBLIC_ALIAS(__frexpl, libc_frexpl);
DEFINE_PUBLIC_ALIAS(frexpl, libc_frexpl);
DEFINE_PUBLIC_ALIAS(__ldexpl, libc_ldexpl);
DEFINE_PUBLIC_ALIAS(ldexpl, libc_ldexpl);
DEFINE_PUBLIC_ALIAS(__logl, libc_logl);
DEFINE_PUBLIC_ALIAS(logl, libc_logl);
DEFINE_PUBLIC_ALIAS(__log10l, libc_log10l);
DEFINE_PUBLIC_ALIAS(log10l, libc_log10l);
DEFINE_PUBLIC_ALIAS(__modfl, libc_modfl);
DEFINE_PUBLIC_ALIAS(modfl, libc_modfl);
DEFINE_PUBLIC_ALIAS(__expm1, libc_expm1);
DEFINE_PUBLIC_ALIAS(expm1, libc_expm1);
DEFINE_PUBLIC_ALIAS(__expm1f, libc_expm1f);
DEFINE_PUBLIC_ALIAS(expm1f, libc_expm1f);
DEFINE_PUBLIC_ALIAS(__log1pf, libc_log1pf);
DEFINE_PUBLIC_ALIAS(log1pf, libc_log1pf);
DEFINE_PUBLIC_ALIAS(__logbf, libc_logbf);
DEFINE_PUBLIC_ALIAS(logbf, libc_logbf);
DEFINE_PUBLIC_ALIAS(__expm1l, libc_expm1l);
DEFINE_PUBLIC_ALIAS(expm1l, libc_expm1l);
DEFINE_PUBLIC_ALIAS(__log1pl, libc_log1pl);
DEFINE_PUBLIC_ALIAS(log1pl, libc_log1pl);
DEFINE_PUBLIC_ALIAS(__logbl, libc_logbl);
DEFINE_PUBLIC_ALIAS(logbl, libc_logbl);
DEFINE_PUBLIC_ALIAS(__exp2f, libc_exp2f);
DEFINE_PUBLIC_ALIAS(exp2f, libc_exp2f);
DEFINE_PUBLIC_ALIAS(__log2f, libc_log2f);
DEFINE_PUBLIC_ALIAS(log2f, libc_log2f);
DEFINE_PUBLIC_ALIAS(__exp2l, libc_exp2l);
DEFINE_PUBLIC_ALIAS(exp2l, libc_exp2l);
DEFINE_PUBLIC_ALIAS(__log2l, libc_log2l);
DEFINE_PUBLIC_ALIAS(log2l, libc_log2l);
DEFINE_PUBLIC_ALIAS(__pow, libc_pow);
DEFINE_PUBLIC_ALIAS(pow, libc_pow);
DEFINE_PUBLIC_ALIAS(__sqrt, libc_sqrt);
DEFINE_PUBLIC_ALIAS(sqrt, libc_sqrt);
DEFINE_PUBLIC_ALIAS(__powf, libc_powf);
DEFINE_PUBLIC_ALIAS(powf, libc_powf);
DEFINE_PUBLIC_ALIAS(__sqrtf, libc_sqrtf);
DEFINE_PUBLIC_ALIAS(sqrtf, libc_sqrtf);
DEFINE_PUBLIC_ALIAS(__powl, libc_powl);
DEFINE_PUBLIC_ALIAS(powl, libc_powl);
DEFINE_PUBLIC_ALIAS(__sqrtl, libc_sqrtl);
DEFINE_PUBLIC_ALIAS(sqrtl, libc_sqrtl);
DEFINE_PUBLIC_ALIAS(__hypotf, libc_hypotf);
DEFINE_PUBLIC_ALIAS(hypotf, libc_hypotf);
DEFINE_PUBLIC_ALIAS(__hypotl, libc_hypotl);
DEFINE_PUBLIC_ALIAS(hypotl, libc_hypotl);
DEFINE_PUBLIC_ALIAS(__cbrt, libc_cbrt);
DEFINE_PUBLIC_ALIAS(cbrt, libc_cbrt);
DEFINE_PUBLIC_ALIAS(__cbrtf, libc_cbrtf);
DEFINE_PUBLIC_ALIAS(cbrtf, libc_cbrtf);
DEFINE_PUBLIC_ALIAS(__cbrtl, libc_cbrtl);
DEFINE_PUBLIC_ALIAS(cbrtl, libc_cbrtl);
DEFINE_PUBLIC_ALIAS(__ceil, libc_ceil);
DEFINE_PUBLIC_ALIAS(ceil, libc_ceil);
DEFINE_PUBLIC_ALIAS(__fabs, libc_fabs);
DEFINE_PUBLIC_ALIAS(fabs, libc_fabs);
DEFINE_PUBLIC_ALIAS(__floor, libc_floor);
DEFINE_PUBLIC_ALIAS(floor, libc_floor);
DEFINE_PUBLIC_ALIAS(__fmod, libc_fmod);
DEFINE_PUBLIC_ALIAS(fmod, libc_fmod);
DEFINE_PUBLIC_ALIAS(__ceilf, libc_ceilf);
DEFINE_PUBLIC_ALIAS(ceilf, libc_ceilf);
DEFINE_PUBLIC_ALIAS(__fabsf, libc_fabsf);
DEFINE_PUBLIC_ALIAS(fabsf, libc_fabsf);
DEFINE_PUBLIC_ALIAS(__floorf, libc_floorf);
DEFINE_PUBLIC_ALIAS(floorf, libc_floorf);
DEFINE_PUBLIC_ALIAS(__fmodf, libc_fmodf);
DEFINE_PUBLIC_ALIAS(fmodf, libc_fmodf);
DEFINE_PUBLIC_ALIAS(__ceill, libc_ceill);
DEFINE_PUBLIC_ALIAS(ceill, libc_ceill);
DEFINE_PUBLIC_ALIAS(__fabsl, libc_fabsl);
DEFINE_PUBLIC_ALIAS(fabsl, libc_fabsl);
DEFINE_PUBLIC_ALIAS(__floorl, libc_floorl);
DEFINE_PUBLIC_ALIAS(floorl, libc_floorl);
DEFINE_PUBLIC_ALIAS(__fmodl, libc_fmodl);
DEFINE_PUBLIC_ALIAS(fmodl, libc_fmodl);
DEFINE_PUBLIC_ALIAS(__copysign, libc_copysign);
DEFINE_PUBLIC_ALIAS(_copysign, libc_copysign);
DEFINE_PUBLIC_ALIAS(copysign, libc_copysign);
DEFINE_PUBLIC_ALIAS(__nan, libc_nan);
DEFINE_PUBLIC_ALIAS(nan, libc_nan);
DEFINE_PUBLIC_ALIAS(__copysignf, libc_copysignf);
DEFINE_PUBLIC_ALIAS(copysignf, libc_copysignf);
DEFINE_PUBLIC_ALIAS(__nanf, libc_nanf);
DEFINE_PUBLIC_ALIAS(nanf, libc_nanf);
DEFINE_PUBLIC_ALIAS(__copysignl, libc_copysignl);
DEFINE_PUBLIC_ALIAS(copysignl, libc_copysignl);
DEFINE_PUBLIC_ALIAS(__nanl, libc_nanl);
DEFINE_PUBLIC_ALIAS(nanl, libc_nanl);
DEFINE_PUBLIC_ALIAS(__erff, libc_erff);
DEFINE_PUBLIC_ALIAS(erff, libc_erff);
DEFINE_PUBLIC_ALIAS(__erfcf, libc_erfcf);
DEFINE_PUBLIC_ALIAS(erfcf, libc_erfcf);
DEFINE_PUBLIC_ALIAS(gammaf, libc_lgammaf);
DEFINE_PUBLIC_ALIAS(__lgammaf, libc_lgammaf);
DEFINE_PUBLIC_ALIAS(__gammaf, libc_lgammaf);
DEFINE_PUBLIC_ALIAS(lgammaf, libc_lgammaf);
DEFINE_PUBLIC_ALIAS(__erfl, libc_erfl);
DEFINE_PUBLIC_ALIAS(erfl, libc_erfl);
DEFINE_PUBLIC_ALIAS(__erfcl, libc_erfcl);
DEFINE_PUBLIC_ALIAS(erfcl, libc_erfcl);
DEFINE_PUBLIC_ALIAS(gammal, libc_lgammal);
DEFINE_PUBLIC_ALIAS(__lgammal, libc_lgammal);
DEFINE_PUBLIC_ALIAS(__gammal, libc_lgammal);
DEFINE_PUBLIC_ALIAS(lgammal, libc_lgammal);
DEFINE_PUBLIC_ALIAS(__tgammaf, libc_tgammaf);
DEFINE_PUBLIC_ALIAS(tgammaf, libc_tgammaf);
DEFINE_PUBLIC_ALIAS(__tgammal, libc_tgammal);
DEFINE_PUBLIC_ALIAS(tgammal, libc_tgammal);
DEFINE_PUBLIC_ALIAS(nearbyint, libc_rint);
DEFINE_PUBLIC_ALIAS(__rint, libc_rint);
DEFINE_PUBLIC_ALIAS(__nearbyint, libc_rint);
DEFINE_PUBLIC_ALIAS(rint, libc_rint);
DEFINE_PUBLIC_ALIAS(nexttoward, libc_nextafter);
DEFINE_PUBLIC_ALIAS(__nextafter, libc_nextafter);
DEFINE_PUBLIC_ALIAS(_nextafter, libc_nextafter);
DEFINE_PUBLIC_ALIAS(__nexttoward, libc_nextafter);
DEFINE_PUBLIC_ALIAS(nextafter, libc_nextafter);
DEFINE_PUBLIC_ALIAS(drem, libc_remainder);
DEFINE_PUBLIC_ALIAS(__remainder, libc_remainder);
DEFINE_PUBLIC_ALIAS(__drem, libc_remainder);
DEFINE_PUBLIC_ALIAS(remainder, libc_remainder);
DEFINE_PUBLIC_ALIAS(__ilogb, libc_ilogb);
DEFINE_PUBLIC_ALIAS(ilogb, libc_ilogb);
DEFINE_PUBLIC_ALIAS(nearbyintf, libc_rintf);
DEFINE_PUBLIC_ALIAS(__rintf, libc_rintf);
DEFINE_PUBLIC_ALIAS(__nearbyintf, libc_rintf);
DEFINE_PUBLIC_ALIAS(rintf, libc_rintf);
DEFINE_PUBLIC_ALIAS(nexttowardf, libc_nextafterf);
DEFINE_PUBLIC_ALIAS(__nextafterf, libc_nextafterf);
DEFINE_PUBLIC_ALIAS(__nexttowardf, libc_nextafterf);
DEFINE_PUBLIC_ALIAS(nextafterf, libc_nextafterf);
DEFINE_PUBLIC_ALIAS(dremf, libc_remainderf);
DEFINE_PUBLIC_ALIAS(__remainderf, libc_remainderf);
DEFINE_PUBLIC_ALIAS(__dremf, libc_remainderf);
DEFINE_PUBLIC_ALIAS(remainderf, libc_remainderf);
DEFINE_PUBLIC_ALIAS(__ilogbf, libc_ilogbf);
DEFINE_PUBLIC_ALIAS(ilogbf, libc_ilogbf);
DEFINE_PUBLIC_ALIAS(nearbyintl, libc_rintl);
DEFINE_PUBLIC_ALIAS(__rintl, libc_rintl);
DEFINE_PUBLIC_ALIAS(__nearbyintl, libc_rintl);
DEFINE_PUBLIC_ALIAS(rintl, libc_rintl);
DEFINE_PUBLIC_ALIAS(nexttowardl, libc_nextafterl);
DEFINE_PUBLIC_ALIAS(__nextafterl, libc_nextafterl);
DEFINE_PUBLIC_ALIAS(__nexttowardl, libc_nextafterl);
DEFINE_PUBLIC_ALIAS(nextafterl, libc_nextafterl);
DEFINE_PUBLIC_ALIAS(dreml, libc_remainderl);
DEFINE_PUBLIC_ALIAS(__remainderl, libc_remainderl);
DEFINE_PUBLIC_ALIAS(__dreml, libc_remainderl);
DEFINE_PUBLIC_ALIAS(remainderl, libc_remainderl);
DEFINE_PUBLIC_ALIAS(__ilogbl, libc_ilogbl);
DEFINE_PUBLIC_ALIAS(ilogbl, libc_ilogbl);
DEFINE_PUBLIC_ALIAS(__nexttoward, libc_nexttoward);
DEFINE_PUBLIC_ALIAS(nexttoward, libc_nexttoward);
DEFINE_PUBLIC_ALIAS(__scalbn, libc_scalbn);
DEFINE_PUBLIC_ALIAS(scalbn, libc_scalbn);
DEFINE_PUBLIC_ALIAS(__scalbln, libc_scalbln);
DEFINE_PUBLIC_ALIAS(scalbln, libc_scalbln);
DEFINE_PUBLIC_ALIAS(__round, libc_round);
DEFINE_PUBLIC_ALIAS(round, libc_round);
DEFINE_PUBLIC_ALIAS(__trunc, libc_trunc);
DEFINE_PUBLIC_ALIAS(trunc, libc_trunc);
DEFINE_PUBLIC_ALIAS(__lrint, libc_lrint);
DEFINE_PUBLIC_ALIAS(lrint, libc_lrint);
DEFINE_PUBLIC_ALIAS(__lround, libc_lround);
DEFINE_PUBLIC_ALIAS(lround, libc_lround);
DEFINE_PUBLIC_ALIAS(__fdim, libc_fdim);
DEFINE_PUBLIC_ALIAS(fdim, libc_fdim);
DEFINE_PUBLIC_ALIAS(__fmax, libc_fmax);
DEFINE_PUBLIC_ALIAS(fmax, libc_fmax);
DEFINE_PUBLIC_ALIAS(__fmin, libc_fmin);
DEFINE_PUBLIC_ALIAS(fmin, libc_fmin);
DEFINE_PUBLIC_ALIAS(__fma, libc_fma);
DEFINE_PUBLIC_ALIAS(fma, libc_fma);
DEFINE_PUBLIC_ALIAS(__llrint, libc_llrint);
DEFINE_PUBLIC_ALIAS(llrint, libc_llrint);
DEFINE_PUBLIC_ALIAS(__llround, libc_llround);
DEFINE_PUBLIC_ALIAS(llround, libc_llround);
DEFINE_PUBLIC_ALIAS(__nexttowardf, libc_nexttowardf);
DEFINE_PUBLIC_ALIAS(nexttowardf, libc_nexttowardf);
DEFINE_PUBLIC_ALIAS(__scalbnf, libc_scalbnf);
DEFINE_PUBLIC_ALIAS(scalbnf, libc_scalbnf);
DEFINE_PUBLIC_ALIAS(__scalblnf, libc_scalblnf);
DEFINE_PUBLIC_ALIAS(scalblnf, libc_scalblnf);
DEFINE_PUBLIC_ALIAS(__roundf, libc_roundf);
DEFINE_PUBLIC_ALIAS(roundf, libc_roundf);
DEFINE_PUBLIC_ALIAS(__truncf, libc_truncf);
DEFINE_PUBLIC_ALIAS(truncf, libc_truncf);
DEFINE_PUBLIC_ALIAS(__remquof, libc_remquof);
DEFINE_PUBLIC_ALIAS(remquof, libc_remquof);
DEFINE_PUBLIC_ALIAS(__lrintf, libc_lrintf);
DEFINE_PUBLIC_ALIAS(lrintf, libc_lrintf);
DEFINE_PUBLIC_ALIAS(__lroundf, libc_lroundf);
DEFINE_PUBLIC_ALIAS(lroundf, libc_lroundf);
DEFINE_PUBLIC_ALIAS(__fdimf, libc_fdimf);
DEFINE_PUBLIC_ALIAS(fdimf, libc_fdimf);
DEFINE_PUBLIC_ALIAS(__fmaxf, libc_fmaxf);
DEFINE_PUBLIC_ALIAS(fmaxf, libc_fmaxf);
DEFINE_PUBLIC_ALIAS(__fminf, libc_fminf);
DEFINE_PUBLIC_ALIAS(fminf, libc_fminf);
DEFINE_PUBLIC_ALIAS(__fmaf, libc_fmaf);
DEFINE_PUBLIC_ALIAS(fmaf, libc_fmaf);
DEFINE_PUBLIC_ALIAS(__llrintf, libc_llrintf);
DEFINE_PUBLIC_ALIAS(llrintf, libc_llrintf);
DEFINE_PUBLIC_ALIAS(__llroundf, libc_llroundf);
DEFINE_PUBLIC_ALIAS(llroundf, libc_llroundf);
DEFINE_PUBLIC_ALIAS(__scalbnl, libc_scalbnl);
DEFINE_PUBLIC_ALIAS(scalbnl, libc_scalbnl);
DEFINE_PUBLIC_ALIAS(__scalblnl, libc_scalblnl);
DEFINE_PUBLIC_ALIAS(scalblnl, libc_scalblnl);
DEFINE_PUBLIC_ALIAS(__roundl, libc_roundl);
DEFINE_PUBLIC_ALIAS(roundl, libc_roundl);
DEFINE_PUBLIC_ALIAS(__truncl, libc_truncl);
DEFINE_PUBLIC_ALIAS(truncl, libc_truncl);
DEFINE_PUBLIC_ALIAS(__remquol, libc_remquol);
DEFINE_PUBLIC_ALIAS(remquol, libc_remquol);
DEFINE_PUBLIC_ALIAS(__lrintl, libc_lrintl);
DEFINE_PUBLIC_ALIAS(lrintl, libc_lrintl);
DEFINE_PUBLIC_ALIAS(__lroundl, libc_lroundl);
DEFINE_PUBLIC_ALIAS(lroundl, libc_lroundl);
DEFINE_PUBLIC_ALIAS(__fdiml, libc_fdiml);
DEFINE_PUBLIC_ALIAS(fdiml, libc_fdiml);
DEFINE_PUBLIC_ALIAS(__fmaxl, libc_fmaxl);
DEFINE_PUBLIC_ALIAS(fmaxl, libc_fmaxl);
DEFINE_PUBLIC_ALIAS(__fminl, libc_fminl);
DEFINE_PUBLIC_ALIAS(fminl, libc_fminl);
DEFINE_PUBLIC_ALIAS(__fmal, libc_fmal);
DEFINE_PUBLIC_ALIAS(fmal, libc_fmal);
DEFINE_PUBLIC_ALIAS(__llrintl, libc_llrintl);
DEFINE_PUBLIC_ALIAS(llrintl, libc_llrintl);
DEFINE_PUBLIC_ALIAS(__llroundl, libc_llroundl);
DEFINE_PUBLIC_ALIAS(llroundl, libc_llroundl);
DEFINE_PUBLIC_ALIAS(__pow10, libc_pow10);
DEFINE_PUBLIC_ALIAS(pow10, libc_pow10);
DEFINE_PUBLIC_ALIAS(__sincosf, libc_sincosf);
DEFINE_PUBLIC_ALIAS(sincosf, libc_sincosf);
DEFINE_PUBLIC_ALIAS(__exp10f, libc_exp10f);
DEFINE_PUBLIC_ALIAS(exp10f, libc_exp10f);
DEFINE_PUBLIC_ALIAS(__pow10f, libc_pow10f);
DEFINE_PUBLIC_ALIAS(pow10f, libc_pow10f);
DEFINE_PUBLIC_ALIAS(__sincosl, libc_sincosl);
DEFINE_PUBLIC_ALIAS(sincosl, libc_sincosl);
DEFINE_PUBLIC_ALIAS(__exp10l, libc_exp10l);
DEFINE_PUBLIC_ALIAS(exp10l, libc_exp10l);
DEFINE_PUBLIC_ALIAS(__pow10l, libc_pow10l);
DEFINE_PUBLIC_ALIAS(pow10l, libc_pow10l);
DEFINE_PUBLIC_ALIAS(__isinf, libc_isinf);
DEFINE_PUBLIC_ALIAS(isinf, libc_isinf);
DEFINE_PUBLIC_ALIAS(__isinff, libc_isinff);
DEFINE_PUBLIC_ALIAS(isinff, libc_isinff);
DEFINE_PUBLIC_ALIAS(__isinfl, libc_isinfl);
DEFINE_PUBLIC_ALIAS(isinfl, libc_isinfl);
DEFINE_PUBLIC_ALIAS(__finite, libc_finite);
DEFINE_PUBLIC_ALIAS(_finite, libc_finite);
DEFINE_PUBLIC_ALIAS(finite, libc_finite);
DEFINE_PUBLIC_ALIAS(__significand, libc_significand);
DEFINE_PUBLIC_ALIAS(significand, libc_significand);
DEFINE_PUBLIC_ALIAS(__finitef, libc_finitef);
DEFINE_PUBLIC_ALIAS(finitef, libc_finitef);
DEFINE_PUBLIC_ALIAS(__significandf, libc_significandf);
DEFINE_PUBLIC_ALIAS(significandf, libc_significandf);
DEFINE_PUBLIC_ALIAS(__finitel, libc_finitel);
DEFINE_PUBLIC_ALIAS(finitel, libc_finitel);
DEFINE_PUBLIC_ALIAS(__significandl, libc_significandl);
DEFINE_PUBLIC_ALIAS(significandl, libc_significandl);
DEFINE_PUBLIC_ALIAS(__isnan, libc_isnan);
DEFINE_PUBLIC_ALIAS(_isnan, libc_isnan);
DEFINE_PUBLIC_ALIAS(isnan, libc_isnan);
DEFINE_PUBLIC_ALIAS(__isnanf, libc_isnanf);
DEFINE_PUBLIC_ALIAS(isnanf, libc_isnanf);
DEFINE_PUBLIC_ALIAS(__isnanl, libc_isnanl);
DEFINE_PUBLIC_ALIAS(isnanl, libc_isnanl);
DEFINE_PUBLIC_ALIAS(__j0f, libc_j0f);
DEFINE_PUBLIC_ALIAS(j0f, libc_j0f);
DEFINE_PUBLIC_ALIAS(__j1f, libc_j1f);
DEFINE_PUBLIC_ALIAS(j1f, libc_j1f);
DEFINE_PUBLIC_ALIAS(__jnf, libc_jnf);
DEFINE_PUBLIC_ALIAS(jnf, libc_jnf);
DEFINE_PUBLIC_ALIAS(__y0f, libc_y0f);
DEFINE_PUBLIC_ALIAS(y0f, libc_y0f);
DEFINE_PUBLIC_ALIAS(__y1f, libc_y1f);
DEFINE_PUBLIC_ALIAS(y1f, libc_y1f);
DEFINE_PUBLIC_ALIAS(__ynf, libc_ynf);
DEFINE_PUBLIC_ALIAS(ynf, libc_ynf);
DEFINE_PUBLIC_ALIAS(__j0l, libc_j0l);
DEFINE_PUBLIC_ALIAS(j0l, libc_j0l);
DEFINE_PUBLIC_ALIAS(__j1l, libc_j1l);
DEFINE_PUBLIC_ALIAS(j1l, libc_j1l);
DEFINE_PUBLIC_ALIAS(__jnl, libc_jnl);
DEFINE_PUBLIC_ALIAS(jnl, libc_jnl);
DEFINE_PUBLIC_ALIAS(__y0l, libc_y0l);
DEFINE_PUBLIC_ALIAS(y0l, libc_y0l);
DEFINE_PUBLIC_ALIAS(__y1l, libc_y1l);
DEFINE_PUBLIC_ALIAS(y1l, libc_y1l);
DEFINE_PUBLIC_ALIAS(__ynl, libc_ynl);
DEFINE_PUBLIC_ALIAS(ynl, libc_ynl);
DEFINE_PUBLIC_ALIAS(__lgammaf_r, libc_lgammaf_r);
DEFINE_PUBLIC_ALIAS(lgammaf_r, libc_lgammaf_r);
DEFINE_PUBLIC_ALIAS(__lgammal_r, libc_lgammal_r);
DEFINE_PUBLIC_ALIAS(lgammal_r, libc_lgammal_r);
DEFINE_PUBLIC_ALIAS(__scalb, libc_scalb);
DEFINE_PUBLIC_ALIAS(_scalb, libc_scalb);
DEFINE_PUBLIC_ALIAS(scalb, libc_scalb);
DEFINE_PUBLIC_ALIAS(__scalbf, libc_scalbf);
DEFINE_PUBLIC_ALIAS(_scalbf, libc_scalbf);
DEFINE_PUBLIC_ALIAS(scalbf, libc_scalbf);
DEFINE_PUBLIC_ALIAS(__scalbl, libc_scalbl);
DEFINE_PUBLIC_ALIAS(scalbl, libc_scalbl);
DEFINE_PUBLIC_ALIAS(_dclass, libc___fpclassify);
DEFINE_PUBLIC_ALIAS(fpclassify, libc___fpclassify);
DEFINE_PUBLIC_ALIAS(__fpclassify, libc___fpclassify);
DEFINE_PUBLIC_ALIAS(_dsign, libc___signbit);
DEFINE_PUBLIC_ALIAS(__signbit, libc___signbit);
DEFINE_PUBLIC_ALIAS(_fdclass, libc___fpclassifyf);
DEFINE_PUBLIC_ALIAS(fpclassifyf, libc___fpclassifyf);
DEFINE_PUBLIC_ALIAS(__fpclassifyf, libc___fpclassifyf);
DEFINE_PUBLIC_ALIAS(_fdsign, libc___signbitf);
DEFINE_PUBLIC_ALIAS(__signbitf, libc___signbitf);
DEFINE_PUBLIC_ALIAS(_ldclass, libc___fpclassifyl);
DEFINE_PUBLIC_ALIAS(fpclassifyl, libc___fpclassifyl);
DEFINE_PUBLIC_ALIAS(__fpclassifyl, libc___fpclassifyl);
DEFINE_PUBLIC_ALIAS(_ldsign, libc___signbitl);
DEFINE_PUBLIC_ALIAS(__signbitl, libc___signbitl);
DEFINE_PUBLIC_ALIAS(issignaling, libc___issignaling);
DEFINE_PUBLIC_ALIAS(__issignaling, libc___issignaling);
DEFINE_PUBLIC_ALIAS(issignalingf, libc___issignalingf);
DEFINE_PUBLIC_ALIAS(__issignalingf, libc___issignalingf);
DEFINE_PUBLIC_ALIAS(issignalingl, libc___issignalingl);
DEFINE_PUBLIC_ALIAS(__issignalingl, libc___issignalingl);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_MATH_C */
