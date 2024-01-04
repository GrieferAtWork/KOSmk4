/* HASH CRC-32:0x7722f2ad */
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
#ifndef GUARD_LIBC_AUTO_MATH_C
#define GUARD_LIBC_AUTO_MATH_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/math.h"
#include "../user/fenv.h"

DECL_BEGIN

#include "../libc/globals.h"
#include "../libc/dos-compat.h"

#ifdef __GNUC__
/* Disable strict-overflow warnings (there's a couple, but we _just_ _don't_ _care_)
 * The  reason we don't care is that all of those warnings are super-hard to get rid
 * of, and they all trigger  because of code that's not  even ours (i.e. is part  of
 * fdlibm) */
__pragma_GCC_diagnostic_ignored(Wstrict_overflow)
#endif /* __GNUC__ */

#ifndef __KERNEL__
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <libm/matherr.h>
#include <libm/nan.h>
#include <libm/acos.h>
#include <bits/crt/fenv.h>
/* >> acosf(3), acos(3), acosl(3)
 * Arc cosine of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_acos)(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2(isgreaterequal, __LIBM_MATHFUN(fabs, x), 1.0)) {
		libc_feraiseexcept(FE_INVALID); /* acos(|x|>1) */
		return __kernel_standard(x, x, __LIBM_MATHFUN1I(nan, ""), __LIBM_KMATHERR_ACOS);
	}
	return __LIBM_MATHFUN(acos, x);
}
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <libm/matherr.h>
#include <libm/nan.h>
#include <libm/asin.h>
#include <bits/crt/fenv.h>
/* >> asinf(3), asin(3), asinl(3)
 * Arc sine of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_asin)(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2(isgreaterequal, __LIBM_MATHFUN(fabs, x), 1.0)) {
		libc_feraiseexcept(FE_INVALID); /* asin(|x|>1) */
		return __kernel_standard(x, x, __LIBM_MATHFUN1I(nan, ""), __LIBM_KMATHERR_ASIN);
	}
	return __LIBM_MATHFUN(asin, x);
}
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <libm/matherr.h>
#include <libm/inf.h>
#include <libm/atan.h>
/* >> atanf(3), atan(3), atanl(3)
 * Arc tangent of `x' */
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
/* >> atan2f(3), atan2(3), atan2l(3)
 * Arc tangent of `y / x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_atan2)(double y,
                             double x) {
	if (__LIBM_LIB_VERSION == __LIBM_SVID && x == 0.0 && y == 0.0)
		return __kernel_standard(y, x, __HUGE_VAL, __LIBM_KMATHERR_ATAN2); /* atan2(+-0,+-0) */
	return __LIBM_MATHFUN2(atan2, y, x);
}
#include <libm/isnan.h>
#include <libm/cos.h>
#include <libm/matherr.h>
/* >> cosf(3), cos(3), cosl(3)
 * Cosine of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_cos double
NOTHROW(LIBCCALL libc_cos)(double x) {
	double result = __LIBM_MATHFUN(cos, x);
	if (__LIBM_MATHFUNI(isnan, result) && !__LIBM_MATHFUNI(isnan, x))
		result = __kernel_standard(x, x, result, __LIBM_KMATHERR_COS_INF);
	return result;
}
#include <libm/isnan.h>
#include <libm/sin.h>
#include <libm/matherr.h>
/* >> sinf(3), sin(3), sinl(3)
 * Sine of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_sin double
NOTHROW(LIBCCALL libc_sin)(double x) {
	double result = __LIBM_MATHFUN(sin, x);
	if (__LIBM_MATHFUNI(isnan, result) && !__LIBM_MATHFUNI(isnan, x))
		result = __kernel_standard(x, x, result, __LIBM_KMATHERR_SIN_INF);
	return result;
}
#include <libm/isnan.h>
#include <libm/isinf.h>
#include <libm/tan.h>
#include <libm/matherr.h>
/* >> tanf(3), tan(3), tanl(3)
 * Tangent of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_tan)(double x) {
	double result = __LIBM_MATHFUN(tan, x);
	if (__LIBM_MATHFUNI(isnan, result) && __LIBM_MATHFUNI(isinf, x))
		result = __kernel_standard(x, x, result, __LIBM_KMATHERR_TAN_INF);
	return result;
}
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <libm/matherr.h>
#include <libm/nan.h>
#include <libm/acos.h>
#include <bits/crt/fenv.h>
/* >> acosf(3), acos(3), acosl(3)
 * Arc cosine of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_acosf)(float x) {




	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2F(isgreaterequal, __LIBM_MATHFUNF(fabs, x), 1.0f)) {
		libc_feraiseexcept(FE_INVALID); /* acos(|x|>1) */
		return __kernel_standard_f(x, x, __LIBM_MATHFUN1IF(nan, ""), __LIBM_KMATHERRF_ACOS);
	}
	return __LIBM_MATHFUNF(acos, x);



}
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <libm/matherr.h>
#include <libm/nan.h>
#include <libm/asin.h>
#include <bits/crt/fenv.h>
/* >> asinf(3), asin(3), asinl(3)
 * Arc sine of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_asinf)(float x) {




	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2F(isgreaterequal, __LIBM_MATHFUNF(fabs, x), 1.0f)) {
		libc_feraiseexcept(FE_INVALID); /* asin(|x|>1) */
		return __kernel_standard_f(x, x, __LIBM_MATHFUN1IF(nan, ""), __LIBM_KMATHERRF_ASIN);
	}
	return __LIBM_MATHFUNF(asin, x);



}
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <libm/matherr.h>
#include <libm/inf.h>
#include <libm/atan.h>
/* >> atanf(3), atan(3), atanl(3)
 * Arc tangent of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_atanf)(float x) {



	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2F(isgreaterequal, __LIBM_MATHFUNF(fabs, x), 1.0f)) {
		return __kernel_standard_f(x, x, __LIBM_MATHFUN0F(inf),
		                         __LIBM_MATHFUNF(fabs, x) > 1.0f
		                         ? __LIBM_KMATHERRF_ATANH_PLUSONE /* atanh(|x|>1) */
		                         : __LIBM_KMATHERRF_ATANH_ONE);   /* atanh(|x|==1) */
	}
	return __LIBM_MATHFUNF(atan, x);



}
#include <bits/math-constants.h>
#include <libm/matherr.h>
#include <libm/atan2.h>
/* >> atan2f(3), atan2(3), atan2l(3)
 * Arc tangent of `y / x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_atan2f)(float y,
                              float x) {



	if (__LIBM_LIB_VERSION == __LIBM_SVID && x == 0.0f && y == 0.0f)
		return __kernel_standard_f(y, x, __HUGE_VALF, __LIBM_KMATHERRF_ATAN2); /* atan2(+-0,+-0) */
	return __LIBM_MATHFUN2F(atan2, y, x);



}
#include <libm/isnan.h>
#include <libm/cos.h>
#include <libm/matherr.h>
/* >> cosf(3), cos(3), cosl(3)
 * Cosine of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_cosf float
NOTHROW(LIBCCALL libc_cosf)(float x) {



	float result = __LIBM_MATHFUNF(cos, x);
	if (__LIBM_MATHFUNIF(isnan, result) && !__LIBM_MATHFUNIF(isnan, x))
		result = __kernel_standard_f(x, x, result, __LIBM_KMATHERRF_COS_INF);
	return result;



}
#include <libm/isnan.h>
#include <libm/sin.h>
#include <libm/matherr.h>
/* >> sinf(3), sin(3), sinl(3)
 * Sine of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_sinf float
NOTHROW(LIBCCALL libc_sinf)(float x) {



	float result = __LIBM_MATHFUNF(sin, x);
	if (__LIBM_MATHFUNIF(isnan, result) && !__LIBM_MATHFUNIF(isnan, x))
		result = __kernel_standard_f(x, x, result, __LIBM_KMATHERRF_SIN_INF);
	return result;



}
#include <libm/isnan.h>
#include <libm/isinf.h>
#include <libm/tan.h>
#include <libm/matherr.h>
/* >> tanf(3), tan(3), tanl(3)
 * Tangent of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_tanf)(float x) {



	float result = __LIBM_MATHFUNF(tan, x);
	if (__LIBM_MATHFUNIF(isnan, result) && __LIBM_MATHFUNIF(isinf, x))
		result = __kernel_standard_f(x, x, result, __LIBM_KMATHERRF_TAN_INF);
	return result;



}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_acosl, libc_acos);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <libm/matherr.h>
#include <libm/nan.h>
#include <libm/acos.h>
#include <bits/crt/fenv.h>
/* >> acosf(3), acos(3), acosl(3)
 * Arc cosine of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_acosl)(__LONGDOUBLE x) {




	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2L(isgreaterequal, __LIBM_MATHFUNL(fabs, x), 1.0L)) {
		libc_feraiseexcept(FE_INVALID); /* acos(|x|>1) */
		return __kernel_standard_l(x, x, __LIBM_MATHFUN1IL(nan, ""), __LIBM_KMATHERRL_ACOS);
	}
	return __LIBM_MATHFUNL(acos, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_asinl, libc_asin);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <libm/matherr.h>
#include <libm/nan.h>
#include <libm/asin.h>
#include <bits/crt/fenv.h>
/* >> asinf(3), asin(3), asinl(3)
 * Arc sine of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_asinl)(__LONGDOUBLE x) {




	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2L(isgreaterequal, __LIBM_MATHFUNL(fabs, x), 1.0L)) {
		libc_feraiseexcept(FE_INVALID); /* asin(|x|>1) */
		return __kernel_standard_l(x, x, __LIBM_MATHFUN1IL(nan, ""), __LIBM_KMATHERRL_ASIN);
	}
	return __LIBM_MATHFUNL(asin, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_atanl, libc_atan);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <libm/matherr.h>
#include <libm/inf.h>
#include <libm/atan.h>
/* >> atanf(3), atan(3), atanl(3)
 * Arc tangent of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_atanl)(__LONGDOUBLE x) {



	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2L(isgreaterequal, __LIBM_MATHFUNL(fabs, x), 1.0L)) {
		return __kernel_standard_l(x, x, __LIBM_MATHFUN0L(inf),
		                         __LIBM_MATHFUNL(fabs, x) > 1.0L
		                         ? __LIBM_KMATHERRL_ATANH_PLUSONE /* atanh(|x|>1) */
		                         : __LIBM_KMATHERRL_ATANH_ONE);   /* atanh(|x|==1) */
	}
	return __LIBM_MATHFUNL(atan, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_atan2l, libc_atan2);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <bits/math-constants.h>
#include <libm/matherr.h>
#include <libm/atan2.h>
/* >> atan2f(3), atan2(3), atan2l(3)
 * Arc tangent of `y / x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_atan2l)(__LONGDOUBLE y,
                              __LONGDOUBLE x) {



	if (__LIBM_LIB_VERSION == __LIBM_SVID && x == 0.0L && y == 0.0L)
		return __kernel_standard_l(y, x, __HUGE_VALL, __LIBM_KMATHERRL_ATAN2); /* atan2(+-0,+-0) */
	return __LIBM_MATHFUN2L(atan2, y, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_cosl, libc_cos);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/isnan.h>
#include <libm/cos.h>
#include <libm/matherr.h>
/* >> cosf(3), cos(3), cosl(3)
 * Cosine of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_cosl __LONGDOUBLE
NOTHROW(LIBCCALL libc_cosl)(__LONGDOUBLE x) {



	__LONGDOUBLE result = __LIBM_MATHFUNL(cos, x);
	if (__LIBM_MATHFUNIL(isnan, result) && !__LIBM_MATHFUNIL(isnan, x))
		result = __kernel_standard_l(x, x, result, __LIBM_KMATHERRL_COS_INF);
	return result;



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_sinl, libc_sin);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/isnan.h>
#include <libm/sin.h>
#include <libm/matherr.h>
/* >> sinf(3), sin(3), sinl(3)
 * Sine of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_sinl __LONGDOUBLE
NOTHROW(LIBCCALL libc_sinl)(__LONGDOUBLE x) {



	__LONGDOUBLE result = __LIBM_MATHFUNL(sin, x);
	if (__LIBM_MATHFUNIL(isnan, result) && !__LIBM_MATHFUNIL(isnan, x))
		result = __kernel_standard_l(x, x, result, __LIBM_KMATHERRL_SIN_INF);
	return result;



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_tanl, libc_tan);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/isnan.h>
#include <libm/isinf.h>
#include <libm/tan.h>
#include <libm/matherr.h>
/* >> tanf(3), tan(3), tanl(3)
 * Tangent of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_tanl)(__LONGDOUBLE x) {



	__LONGDOUBLE result = __LIBM_MATHFUNL(tan, x);
	if (__LIBM_MATHFUNIL(isnan, result) && __LIBM_MATHFUNIL(isinf, x))
		result = __kernel_standard_l(x, x, result, __LIBM_KMATHERRL_TAN_INF);
	return result;



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/finite.h>
#include <libm/cosh.h>
#include <libm/matherr.h>
/* >> coshf(3), cosh(3), coshl(3)
 * Hyperbolic   cosine   of   `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_cosh)(double x) {
	double result = __LIBM_MATHFUN(cosh, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
		!__LIBM_MATHFUNI(finite, result) && __LIBM_MATHFUNI(finite, x))
		result = __kernel_standard(x, x, result, __LIBM_KMATHERR_COSH);
	return result;
}
#include <libm/finite.h>
#include <libm/sinh.h>
#include <libm/matherr.h>
/* >> sinhf(3), sinh(3), sinhl(3)
 * Hyperbolic sine of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_sinh)(double x) {
	double result = __LIBM_MATHFUN(sinh, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
		!__LIBM_MATHFUNI(finite, result) && __LIBM_MATHFUNI(finite, x))
		result = __kernel_standard(x, x, result, __LIBM_KMATHERR_SINH);
	return result;
}
#include <libm/tanh.h>
/* >> tanhf(3), tanh(3), tanhl(3)
 * Hyperbolic   tangent   of  `x' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_tanh)(double x) {
	return __LIBM_MATHFUN(tanh, x);
}
#include <libm/finite.h>
#include <libm/cosh.h>
#include <libm/matherr.h>
/* >> coshf(3), cosh(3), coshl(3)
 * Hyperbolic   cosine   of   `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_coshf)(float x) {



	float result = __LIBM_MATHFUNF(cosh, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
		!__LIBM_MATHFUNIF(finite, result) && __LIBM_MATHFUNIF(finite, x))
		result = __kernel_standard_f(x, x, result, __LIBM_KMATHERRF_COSH);
	return result;



}
#include <libm/finite.h>
#include <libm/sinh.h>
#include <libm/matherr.h>
/* >> sinhf(3), sinh(3), sinhl(3)
 * Hyperbolic sine of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_sinhf)(float x) {



	float result = __LIBM_MATHFUNF(sinh, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
		!__LIBM_MATHFUNIF(finite, result) && __LIBM_MATHFUNIF(finite, x))
		result = __kernel_standard_f(x, x, result, __LIBM_KMATHERRF_SINH);
	return result;



}
#include <libm/tanh.h>
/* >> tanhf(3), tanh(3), tanhl(3)
 * Hyperbolic   tangent   of  `x' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_tanhf)(float x) {



	return __LIBM_MATHFUNF(tanh, x);



}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_coshl, libc_cosh);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/finite.h>
#include <libm/cosh.h>
#include <libm/matherr.h>
/* >> coshf(3), cosh(3), coshl(3)
 * Hyperbolic   cosine   of   `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_coshl)(__LONGDOUBLE x) {



	__LONGDOUBLE result = __LIBM_MATHFUNL(cosh, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
		!__LIBM_MATHFUNIL(finite, result) && __LIBM_MATHFUNIL(finite, x))
		result = __kernel_standard_l(x, x, result, __LIBM_KMATHERRL_COSH);
	return result;



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_sinhl, libc_sinh);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/finite.h>
#include <libm/sinh.h>
#include <libm/matherr.h>
/* >> sinhf(3), sinh(3), sinhl(3)
 * Hyperbolic sine of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_sinhl)(__LONGDOUBLE x) {



	__LONGDOUBLE result = __LIBM_MATHFUNL(sinh, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
		!__LIBM_MATHFUNIL(finite, result) && __LIBM_MATHFUNIL(finite, x))
		result = __kernel_standard_l(x, x, result, __LIBM_KMATHERRL_SINH);
	return result;



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_tanhl, libc_tanh);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/tanh.h>
/* >> tanhf(3), tanh(3), tanhl(3)
 * Hyperbolic   tangent   of  `x' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_tanhl)(__LONGDOUBLE x) {



	return __LIBM_MATHFUNL(tanh, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/fcomp.h>
#include <libm/matherr.h>
#include <libm/nan.h>
#include <libm/acosh.h>
/* >> acoshf(3), acosh(3), acoshl(3)
 * Hyperbolic  arc  cosine  of   `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_acosh)(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
		__LIBM_MATHFUNI2(isless, x, 1.0)) /* acosh(x<1) */
		return __kernel_standard(x, x, __LIBM_MATHFUN1I(nan, ""), __LIBM_KMATHERR_ACOSH);
	return __LIBM_MATHFUN(acosh, x);
}
#include <libm/asinh.h>
/* >> asinhf(3), asinh(3), asinhl(3)
 * Hyperbolic  arc   sine   of   `x' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_asinh)(double x) {
	return __LIBM_MATHFUN(asinh, x);
}
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <bits/math-constants.h>
#include <libm/matherr.h>
#include <libm/nan.h>
#include <libm/atanh.h>
/* >> atanhf(3), atanh(3), atanhl(3)
 * Hyperbolic  arc  tangent  of  `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_atanh)(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2(isgreaterequal, __LIBM_MATHFUN(fabs, x), 1.0))
		return __kernel_standard(x, x, __HUGE_VAL,
		                         __LIBM_MATHFUN(fabs, x) > 1.0 ? __LIBM_KMATHERR_ATANH_PLUSONE /* atanh(|x|>1) */
		                                                         : __LIBM_KMATHERR_ATANH_ONE);   /* atanh(|x|==1) */
	return __LIBM_MATHFUN(atanh, x);
}
#include <libm/fcomp.h>
#include <libm/matherr.h>
#include <libm/nan.h>
#include <libm/acosh.h>
/* >> acoshf(3), acosh(3), acoshl(3)
 * Hyperbolic  arc  cosine  of   `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_acoshf)(float x) {



	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
		__LIBM_MATHFUNI2F(isless, x, 1.0f)) /* acosh(x<1) */
		return __kernel_standard_f(x, x, __LIBM_MATHFUN1IF(nan, ""), __LIBM_KMATHERRF_ACOSH);
	return __LIBM_MATHFUNF(acosh, x);



}
#include <libm/asinh.h>
/* >> asinhf(3), asinh(3), asinhl(3)
 * Hyperbolic  arc   sine   of   `x' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_asinhf)(float x) {



	return __LIBM_MATHFUNF(asinh, x);



}
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <bits/math-constants.h>
#include <libm/matherr.h>
#include <libm/nan.h>
#include <libm/atanh.h>
/* >> atanhf(3), atanh(3), atanhl(3)
 * Hyperbolic  arc  tangent  of  `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_atanhf)(float x) {



	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2F(isgreaterequal, __LIBM_MATHFUNF(fabs, x), 1.0f))
		return __kernel_standard_f(x, x, __HUGE_VALF,
		                         __LIBM_MATHFUNF(fabs, x) > 1.0f ? __LIBM_KMATHERRF_ATANH_PLUSONE /* atanh(|x|>1) */
		                                                         : __LIBM_KMATHERRF_ATANH_ONE);   /* atanh(|x|==1) */
	return __LIBM_MATHFUNF(atanh, x);



}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_acoshl, libc_acosh);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/fcomp.h>
#include <libm/matherr.h>
#include <libm/nan.h>
#include <libm/acosh.h>
/* >> acoshf(3), acosh(3), acoshl(3)
 * Hyperbolic  arc  cosine  of   `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_acoshl)(__LONGDOUBLE x) {



	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
		__LIBM_MATHFUNI2L(isless, x, 1.0L)) /* acosh(x<1) */
		return __kernel_standard_l(x, x, __LIBM_MATHFUN1IL(nan, ""), __LIBM_KMATHERRL_ACOSH);
	return __LIBM_MATHFUNL(acosh, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_asinhl, libc_asinh);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/asinh.h>
/* >> asinhf(3), asinh(3), asinhl(3)
 * Hyperbolic  arc   sine   of   `x' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_asinhl)(__LONGDOUBLE x) {



	return __LIBM_MATHFUNL(asinh, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_atanhl, libc_atanh);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <bits/math-constants.h>
#include <libm/matherr.h>
#include <libm/nan.h>
#include <libm/atanh.h>
/* >> atanhf(3), atanh(3), atanhl(3)
 * Hyperbolic  arc  tangent  of  `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_atanhl)(__LONGDOUBLE x) {



	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2L(isgreaterequal, __LIBM_MATHFUNL(fabs, x), 1.0L))
		return __kernel_standard_l(x, x, __HUGE_VALL,
		                         __LIBM_MATHFUNL(fabs, x) > 1.0L ? __LIBM_KMATHERRL_ATANH_PLUSONE /* atanh(|x|>1) */
		                                                         : __LIBM_KMATHERRL_ATANH_ONE);   /* atanh(|x|==1) */
	return __LIBM_MATHFUNL(atanh, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/signbit.h>
#include <libm/finite.h>
#include <libm/matherr.h>
#include <libm/exp.h>
/* >> expf(3), exp(3), expl(3)
 * Exponential function of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_exp double
NOTHROW(LIBCCALL libc_exp)(double x) {
	double result;
	result = __LIBM_MATHFUN(exp, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (!__LIBM_MATHFUNI(finite, result) || result == 0.0) &&
	    __LIBM_MATHFUNI(finite, x)) {
		return __kernel_standard(x, x, result,
		                         __LIBM_MATHFUNI(signbit, x)
		                         ? __LIBM_KMATHERR_EXP_UNDERFLOW
		                         : __LIBM_KMATHERR_EXP_OVERFLOW);
	}
	return result;
}
#include <libm/frexp.h>
/* >> frexpf(3), frexp(3), frexpl(3)
 * Break `value' into a normalized fraction and an integral power of 2 */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_OUT(2) double
NOTHROW_NCX(LIBCCALL libc_frexp)(double x,
                                 int *pexponent) {
	return __LIBM_MATHFUN2I(frexp, x, pexponent);
}
#include <libc/errno.h>
#include <libm/finite.h>
#include <libm/ldexp.h>
/* >> ldexpf(3), ldexp(3), ldexpl(3)
 * `x' times (two to the `exponent' power) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_ldexp)(double x,
                             int exponent) {
	double result;
	result = __LIBM_MATHFUN2I(ldexp, x, exponent);

	if unlikely(!__LIBM_MATHFUNI(finite, result) || result == 0.0)
		(void)libc_seterrno(ERANGE);

	return result;
}
#include <bits/crt/fenv.h>
#include <bits/math-constants.h>
#include <libm/nan.h>
#include <libm/log.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
/* >> logf(3), log(3), logl(3)
 * Natural  logarithm  of  `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_log double
NOTHROW(LIBCCALL libc_log)(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2(islessequal, x, -1.0)) {
		if (x == -1.0) {
			libc_feraiseexcept(FE_DIVBYZERO);
			return __kernel_standard(x, x, -__HUGE_VAL, __LIBM_KMATHERR_LOG_ZERO); /* log(0) */
		} else {
			libc_feraiseexcept(FE_INVALID);
			return __kernel_standard(x, x, __LIBM_MATHFUN1I(nan, ""), __LIBM_KMATHERR_LOG_MINUS); /* log(x<0) */
		}
	}
	return __LIBM_MATHFUN(log, x);
}
#include <bits/crt/fenv.h>
#include <bits/math-constants.h>
#include <libm/nan.h>
#include <libm/log10.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
/* >> log10f(3), log10(3), log10l(3)
 * Base-ten    logarithm    of   `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_log10)(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2(islessequal, x, 0.0)) {
		if (x == 0.0) {
			libc_feraiseexcept(FE_DIVBYZERO);
			return __kernel_standard(x, x, -__HUGE_VAL, __LIBM_KMATHERR_LOG10_ZERO); /* log10(0) */
		} else {
			libc_feraiseexcept(FE_INVALID);
			return __kernel_standard(x, x, __LIBM_MATHFUN1I(nan, ""), __LIBM_KMATHERR_LOG10_MINUS); /* log10(x<0) */
		}
	}
	return __LIBM_MATHFUN(log10, x);
}
#include <libm/modf.h>
/* >> modff(3), modf(3), modfl(3)
 * Break `value' into integral and fractional parts */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED ATTR_OUT(2) double
NOTHROW_NCX(LIBCCALL libc_modf)(double x,
                                double *iptr) {
	return __LIBM_MATHFUN2I(modf, x, (__LIBM_MATHFUN_T *)iptr);
}
#include <libm/signbit.h>
#include <libm/finite.h>
#include <libm/matherr.h>
#include <libm/exp.h>
/* >> expf(3), exp(3), expl(3)
 * Exponential function of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_expf float
NOTHROW(LIBCCALL libc_expf)(float x) {



	float result;
	result = __LIBM_MATHFUNF(exp, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (!__LIBM_MATHFUNIF(finite, result) || result == 0.0f) &&
	    __LIBM_MATHFUNIF(finite, x)) {
		return __kernel_standard_f(x, x, result,
		                         __LIBM_MATHFUNIF(signbit, x)
		                         ? __LIBM_KMATHERRF_EXP_UNDERFLOW
		                         : __LIBM_KMATHERRF_EXP_OVERFLOW);
	}
	return result;



}
#include <libm/frexp.h>
/* >> frexpf(3), frexp(3), frexpl(3)
 * Break `value' into a normalized fraction and an integral power of 2 */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_OUT(2) float
NOTHROW_NCX(LIBCCALL libc_frexpf)(float x,
                                  int *pexponent) {



	return __LIBM_MATHFUN2IF(frexp, x, pexponent);



}
#include <libc/errno.h>
#include <libm/finite.h>
#include <libm/ldexp.h>
/* >> ldexpf(3), ldexp(3), ldexpl(3)
 * `x' times (two to the `exponent' power) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_ldexpf)(float x,
                              int exponent) {



	float result;
	result = __LIBM_MATHFUN2IF(ldexp, x, exponent);

	if unlikely(!__LIBM_MATHFUNIF(finite, result) || result == 0.0f)
		(void)libc_seterrno(ERANGE);

	return result;



}
#include <bits/crt/fenv.h>
#include <bits/math-constants.h>
#include <libm/nan.h>
#include <libm/log.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
/* >> logf(3), log(3), logl(3)
 * Natural  logarithm  of  `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_logf float
NOTHROW(LIBCCALL libc_logf)(float x) {




	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2F(islessequal, x, -1.0f)) {
		if (x == -1.0f) {
			libc_feraiseexcept(FE_DIVBYZERO);
			return __kernel_standard_f(x, x, -__HUGE_VALF, __LIBM_KMATHERRF_LOG_ZERO); /* log(0) */
		} else {
			libc_feraiseexcept(FE_INVALID);
			return __kernel_standard_f(x, x, __LIBM_MATHFUN1IF(nan, ""), __LIBM_KMATHERRF_LOG_MINUS); /* log(x<0) */
		}
	}
	return __LIBM_MATHFUNF(log, x);



}
#include <bits/crt/fenv.h>
#include <bits/math-constants.h>
#include <libm/nan.h>
#include <libm/log10.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
/* >> log10f(3), log10(3), log10l(3)
 * Base-ten    logarithm    of   `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_log10f)(float x) {




	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2F(islessequal, x, 0.0f)) {
		if (x == 0.0f) {
			libc_feraiseexcept(FE_DIVBYZERO);
			return __kernel_standard_f(x, x, -__HUGE_VALF, __LIBM_KMATHERRF_LOG10_ZERO); /* log10(0) */
		} else {
			libc_feraiseexcept(FE_INVALID);
			return __kernel_standard_f(x, x, __LIBM_MATHFUN1IF(nan, ""), __LIBM_KMATHERRF_LOG10_MINUS); /* log10(x<0) */
		}
	}
	return __LIBM_MATHFUNF(log10, x);



}
#include <libm/modf.h>
/* >> modff(3), modf(3), modfl(3)
 * Break `value' into integral and fractional parts */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED ATTR_OUT(2) float
NOTHROW_NCX(LIBCCALL libc_modff)(float x,
                                 float *iptr) {



	return __LIBM_MATHFUN2IF(modf, x, (__LIBM_MATHFUNF_T *)iptr);



}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_expl, libc_exp);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/signbit.h>
#include <libm/finite.h>
#include <libm/matherr.h>
#include <libm/exp.h>
/* >> expf(3), exp(3), expl(3)
 * Exponential function of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_expl __LONGDOUBLE
NOTHROW(LIBCCALL libc_expl)(__LONGDOUBLE x) {



	__LONGDOUBLE result;
	result = __LIBM_MATHFUNL(exp, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (!__LIBM_MATHFUNIL(finite, result) || result == 0.0L) &&
	    __LIBM_MATHFUNIL(finite, x)) {
		return __kernel_standard_l(x, x, result,
		                         __LIBM_MATHFUNIL(signbit, x)
		                         ? __LIBM_KMATHERRL_EXP_UNDERFLOW
		                         : __LIBM_KMATHERRL_EXP_OVERFLOW);
	}
	return result;



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_frexpl, libc_frexp);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/frexp.h>
/* >> frexpf(3), frexp(3), frexpl(3)
 * Break `value' into a normalized fraction and an integral power of 2 */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_OUT(2) __LONGDOUBLE
NOTHROW_NCX(LIBCCALL libc_frexpl)(__LONGDOUBLE x,
                                  int *pexponent) {



	return __LIBM_MATHFUN2IL(frexp, x, pexponent);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_ldexpl, libc_ldexp);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libc/errno.h>
#include <libm/finite.h>
#include <libm/ldexp.h>
/* >> ldexpf(3), ldexp(3), ldexpl(3)
 * `x' times (two to the `exponent' power) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_ldexpl)(__LONGDOUBLE x,
                              int exponent) {



	__LONGDOUBLE result;
	result = __LIBM_MATHFUN2IL(ldexp, x, exponent);

	if unlikely(!__LIBM_MATHFUNIL(finite, result) || result == 0.0L)
		(void)libc_seterrno(ERANGE);

	return result;



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_logl, libc_log);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <bits/crt/fenv.h>
#include <bits/math-constants.h>
#include <libm/nan.h>
#include <libm/log.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
/* >> logf(3), log(3), logl(3)
 * Natural  logarithm  of  `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_logl __LONGDOUBLE
NOTHROW(LIBCCALL libc_logl)(__LONGDOUBLE x) {




	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2L(islessequal, x, -1.0L)) {
		if (x == -1.0L) {
			libc_feraiseexcept(FE_DIVBYZERO);
			return __kernel_standard_l(x, x, -__HUGE_VALL, __LIBM_KMATHERRL_LOG_ZERO); /* log(0) */
		} else {
			libc_feraiseexcept(FE_INVALID);
			return __kernel_standard_l(x, x, __LIBM_MATHFUN1IL(nan, ""), __LIBM_KMATHERRL_LOG_MINUS); /* log(x<0) */
		}
	}
	return __LIBM_MATHFUNL(log, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_log10l, libc_log10);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <bits/crt/fenv.h>
#include <bits/math-constants.h>
#include <libm/nan.h>
#include <libm/log10.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
/* >> log10f(3), log10(3), log10l(3)
 * Base-ten    logarithm    of   `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_log10l)(__LONGDOUBLE x) {




	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2L(islessequal, x, 0.0L)) {
		if (x == 0.0L) {
			libc_feraiseexcept(FE_DIVBYZERO);
			return __kernel_standard_l(x, x, -__HUGE_VALL, __LIBM_KMATHERRL_LOG10_ZERO); /* log10(0) */
		} else {
			libc_feraiseexcept(FE_INVALID);
			return __kernel_standard_l(x, x, __LIBM_MATHFUN1IL(nan, ""), __LIBM_KMATHERRL_LOG10_MINUS); /* log10(x<0) */
		}
	}
	return __LIBM_MATHFUNL(log10, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_modfl, libc_modf);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/modf.h>
/* >> modff(3), modf(3), modfl(3)
 * Break `value' into integral and fractional parts */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED ATTR_OUT(2) __LONGDOUBLE
NOTHROW_NCX(LIBCCALL libc_modfl)(__LONGDOUBLE x,
                                 __LONGDOUBLE *iptr) {



	return __LIBM_MATHFUN2IL(modf, x, (__LIBM_MATHFUNL_T *)iptr);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/matherr.h>
#include <libm/signbit.h>
#include <libm/finite.h>
#include <libm/expm1.h>
/* >> expm1f(3), expm1(3), expm1l(3)
 * Return `exp(x) - 1' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_expm1)(double x) {
	double result;
	result = __LIBM_MATHFUN(expm1, x);
	if ((!__LIBM_MATHFUNI(finite, result) || result == -1.0) &&
	    __LIBM_MATHFUNI(finite , x) && __LIBM_LIB_VERSION != __LIBM_IEEE) {
		return __kernel_standard(x, x, result,
		                         __LIBM_MATHFUNI(signbit, x)
		                         ? __LIBM_KMATHERR_EXPM1_UNDERFLOW
		                         : __LIBM_KMATHERR_EXPM1_OVERFLOW);
	}
	return result;
}
#include <bits/crt/fenv.h>
#include <bits/math-constants.h>
#include <libm/nan.h>
#include <libm/log1p.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
/* >> log1pf(3), log1p(3), log1pl(3)
 * Return `log(1 + x)' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_log1p)(double x) {
	if (__LIBM_MATHFUNI2(islessequal, x, -1.0) && __LIBM_LIB_VERSION != __LIBM_IEEE) {
		if (x == -1.0) {
			libc_feraiseexcept(FE_DIVBYZERO);
			return __kernel_standard(x, x, -__HUGE_VAL, __LIBM_KMATHERR_LOG_ZERO); /* log(0) */
		} else {
			libc_feraiseexcept(FE_INVALID);
			return __kernel_standard(x, x, __LIBM_MATHFUN1I(nan, ""), __LIBM_KMATHERR_LOG_MINUS); /* log(x<0) */
		}
	}
	return __LIBM_MATHFUN(log1p, x);
}
#include <libm/logb.h>
/* >> logbf(3), logb(3), logbl(3)
 * Return the base 2 signed integral exponent of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_logb)(double x) {
	return __LIBM_MATHFUN(logb, x);
}
#include <libm/matherr.h>
#include <libm/signbit.h>
#include <libm/finite.h>
#include <libm/expm1.h>
/* >> expm1f(3), expm1(3), expm1l(3)
 * Return `exp(x) - 1' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_expm1f)(float x) {



	float result;
	result = __LIBM_MATHFUNF(expm1, x);
	if ((!__LIBM_MATHFUNIF(finite, result) || result == -1.0f) &&
	    __LIBM_MATHFUNIF(finite , x) && __LIBM_LIB_VERSION != __LIBM_IEEE) {
		return __kernel_standard_f(x, x, result,
		                         __LIBM_MATHFUNIF(signbit, x)
		                         ? __LIBM_KMATHERRF_EXPM1_UNDERFLOW
		                         : __LIBM_KMATHERRF_EXPM1_OVERFLOW);
	}
	return result;



}
#include <bits/crt/fenv.h>
#include <bits/math-constants.h>
#include <libm/nan.h>
#include <libm/log1p.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
/* >> log1pf(3), log1p(3), log1pl(3)
 * Return `log(1 + x)' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_log1pf)(float x) {




	if (__LIBM_MATHFUNI2F(islessequal, x, -1.0f) && __LIBM_LIB_VERSION != __LIBM_IEEE) {
		if (x == -1.0f) {
			libc_feraiseexcept(FE_DIVBYZERO);
			return __kernel_standard_f(x, x, -__HUGE_VALF, __LIBM_KMATHERRF_LOG_ZERO); /* log(0) */
		} else {
			libc_feraiseexcept(FE_INVALID);
			return __kernel_standard_f(x, x, __LIBM_MATHFUN1IF(nan, ""), __LIBM_KMATHERRF_LOG_MINUS); /* log(x<0) */
		}
	}
	return __LIBM_MATHFUNF(log1p, x);



}
#include <libm/logb.h>
/* >> logbf(3), logb(3), logbl(3)
 * Return the base 2 signed integral exponent of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_logbf)(float x) {



	return __LIBM_MATHFUNF(logb, x);



}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_expm1l, libc_expm1);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/matherr.h>
#include <libm/signbit.h>
#include <libm/finite.h>
#include <libm/expm1.h>
/* >> expm1f(3), expm1(3), expm1l(3)
 * Return `exp(x) - 1' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_expm1l)(__LONGDOUBLE x) {



	__LONGDOUBLE result;
	result = __LIBM_MATHFUNL(expm1, x);
	if ((!__LIBM_MATHFUNIL(finite, result) || result == -1.0L) &&
	    __LIBM_MATHFUNIL(finite , x) && __LIBM_LIB_VERSION != __LIBM_IEEE) {
		return __kernel_standard_l(x, x, result,
		                         __LIBM_MATHFUNIL(signbit, x)
		                         ? __LIBM_KMATHERRL_EXPM1_UNDERFLOW
		                         : __LIBM_KMATHERRL_EXPM1_OVERFLOW);
	}
	return result;



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_log1pl, libc_log1p);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <bits/crt/fenv.h>
#include <bits/math-constants.h>
#include <libm/nan.h>
#include <libm/log1p.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
/* >> log1pf(3), log1p(3), log1pl(3)
 * Return `log(1 + x)' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_log1pl)(__LONGDOUBLE x) {




	if (__LIBM_MATHFUNI2L(islessequal, x, -1.0L) && __LIBM_LIB_VERSION != __LIBM_IEEE) {
		if (x == -1.0L) {
			libc_feraiseexcept(FE_DIVBYZERO);
			return __kernel_standard_l(x, x, -__HUGE_VALL, __LIBM_KMATHERRL_LOG_ZERO); /* log(0) */
		} else {
			libc_feraiseexcept(FE_INVALID);
			return __kernel_standard_l(x, x, __LIBM_MATHFUN1IL(nan, ""), __LIBM_KMATHERRL_LOG_MINUS); /* log(x<0) */
		}
	}
	return __LIBM_MATHFUNL(log1p, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_logbl, libc_logb);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/logb.h>
/* >> logbf(3), logb(3), logbl(3)
 * Return the base 2 signed integral exponent of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_logbl)(__LONGDOUBLE x) {



	return __LIBM_MATHFUNL(logb, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/exp2.h>
#include <libm/matherr.h>
#include <libm/finite.h>
#include <libm/signbit.h>
/* >> exp2f(3), exp2(3), exp2l(3)
 * Compute base-2 exponential of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_exp2)(double x) {
	double result = __LIBM_MATHFUN(exp2, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !__LIBM_MATHFUNI(finite, result) && __LIBM_MATHFUNI(finite, x)) {
		return __kernel_standard(x, x, result,
		                         __LIBM_MATHFUNI(signbit, x)
		                         ? __LIBM_KMATHERR_EXP2_UNDERFLOW
		                         : __LIBM_KMATHERR_EXP2_OVERFLOW);
	}
	return result;
}
#include <bits/crt/fenv.h>
#include <bits/math-constants.h>
#include <libm/nan.h>
#include <libm/log2.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
/* >> log2f(3), log2(3), log2l(3)
 * Compute base-2 logarithm of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_log2)(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2(islessequal, x, 0.0)) {
		if (x == 0.0) {
			libc_feraiseexcept(FE_DIVBYZERO);
			return __kernel_standard(x, x, -__HUGE_VAL,
			                         __LIBM_KMATHERR_LOG2_ZERO); /* log2(0) */
		} else {
			libc_feraiseexcept(FE_INVALID);
			return __kernel_standard(x, x, __LIBM_MATHFUN1I(nan, ""),
			                         __LIBM_KMATHERR_LOG2_MINUS); /* log2(x<0) */
		}
	}
	return __LIBM_MATHFUN(log2, x);
}
#include <libm/exp2.h>
#include <libm/matherr.h>
#include <libm/finite.h>
#include <libm/signbit.h>
/* >> exp2f(3), exp2(3), exp2l(3)
 * Compute base-2 exponential of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_exp2f)(float x) {




	float result = __LIBM_MATHFUNF(exp2, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !__LIBM_MATHFUNIF(finite, result) && __LIBM_MATHFUNIF(finite, x)) {
		return __kernel_standard_f(x, x, result,
		                         __LIBM_MATHFUNIF(signbit, x)
		                         ? __LIBM_KMATHERRF_EXP2_UNDERFLOW
		                         : __LIBM_KMATHERRF_EXP2_OVERFLOW);
	}
	return result;



}
#include <bits/crt/fenv.h>
#include <bits/math-constants.h>
#include <libm/nan.h>
#include <libm/log2.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
/* >> log2f(3), log2(3), log2l(3)
 * Compute base-2 logarithm of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_log2f)(float x) {




	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2F(islessequal, x, 0.0f)) {
		if (x == 0.0f) {
			libc_feraiseexcept(FE_DIVBYZERO);
			return __kernel_standard_f(x, x, -__HUGE_VALF,
			                         __LIBM_KMATHERRF_LOG2_ZERO); /* log2(0) */
		} else {
			libc_feraiseexcept(FE_INVALID);
			return __kernel_standard_f(x, x, __LIBM_MATHFUN1IF(nan, ""),
			                         __LIBM_KMATHERRF_LOG2_MINUS); /* log2(x<0) */
		}
	}
	return __LIBM_MATHFUNF(log2, x);



}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_exp2l, libc_exp2);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/exp2.h>
#include <libm/matherr.h>
#include <libm/finite.h>
#include <libm/signbit.h>
/* >> exp2f(3), exp2(3), exp2l(3)
 * Compute base-2 exponential of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_exp2l)(__LONGDOUBLE x) {




	__LONGDOUBLE result = __LIBM_MATHFUNL(exp2, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !__LIBM_MATHFUNIL(finite, result) && __LIBM_MATHFUNIL(finite, x)) {
		return __kernel_standard_l(x, x, result,
		                         __LIBM_MATHFUNIL(signbit, x)
		                         ? __LIBM_KMATHERRL_EXP2_UNDERFLOW
		                         : __LIBM_KMATHERRL_EXP2_OVERFLOW);
	}
	return result;



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_log2l, libc_log2);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <bits/crt/fenv.h>
#include <bits/math-constants.h>
#include <libm/nan.h>
#include <libm/log2.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
/* >> log2f(3), log2(3), log2l(3)
 * Compute base-2 logarithm of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_log2l)(__LONGDOUBLE x) {




	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2L(islessequal, x, 0.0L)) {
		if (x == 0.0L) {
			libc_feraiseexcept(FE_DIVBYZERO);
			return __kernel_standard_l(x, x, -__HUGE_VALL,
			                         __LIBM_KMATHERRL_LOG2_ZERO); /* log2(0) */
		} else {
			libc_feraiseexcept(FE_INVALID);
			return __kernel_standard_l(x, x, __LIBM_MATHFUN1IL(nan, ""),
			                         __LIBM_KMATHERRL_LOG2_MINUS); /* log2(x<0) */
		}
	}
	return __LIBM_MATHFUNL(log2, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/finite.h>
#include <libm/isnan.h>
#include <libm/matherr.h>
#include <libm/pow.h>
#include <libm/signbit.h>
/* >> powf(3), pow(3), powl(3)
 * Return `x' to the `y' power */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_pow double
NOTHROW(LIBCCALL libc_pow)(double x,
                           double y) {
	double result;
	result = __LIBM_MATHFUN2(pow, x, y);
	/*
	 * ====================================================
	 * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Permission  to use, copy, modify, and distribute this
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
/* >> sqrtf(3), sqrt(3), sqrtl(3)
 * Return the square root of  `x' */
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
#include <libm/signbit.h>
/* >> powf(3), pow(3), powl(3)
 * Return `x' to the `y' power */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_powf float
NOTHROW(LIBCCALL libc_powf)(float x,
                            float y) {



	float result;
	result = __LIBM_MATHFUN2F(pow, x, y);
	/*
	 * ====================================================
	 * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Permission  to use, copy, modify, and distribute this
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
					return __kernel_standard_f(x, y, result, __LIBM_KMATHERRF_POW_NAN);
			} else if (__LIBM_MATHFUNIF(finite, x) && __LIBM_MATHFUNIF(finite, y)) {
				if (__LIBM_MATHFUNIF(isnan, result)) { /* pow neg**non-int */
					return __kernel_standard_f(x, y, result, __LIBM_KMATHERRF_POW_NONINT);
				} else if (x == 0.0f && y < 0.0f) {
					if (__LIBM_MATHFUNIF(signbit, x) && __LIBM_MATHFUNIF(signbit, result)) { /* pow(-0.0,negative) */
						return __kernel_standard_f(x, y, result, __LIBM_KMATHERRF_POW_MINUS);
					} else { /* pow(+0.0,negative) */
						return __kernel_standard_f(x, y, result, __LIBM_KMATHERRF_POW_ZEROMINUS);
					}
				} else {
					/* pow overflow */
					return __kernel_standard_f(x, y, result, __LIBM_KMATHERRF_POW_OVERFLOW);
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
				return __kernel_standard_f(x, y, result, __LIBM_KMATHERRF_POW_ZERO);
			}
		} else {
			/* pow underflow */
			return __kernel_standard_f(x, y, result, __LIBM_KMATHERRF_POW_UNDERFLOW);
		}
	}
	return result;



}
#include <libm/fcomp.h>
#include <libm/nan.h>
#include <libm/matherr.h>
#include <libm/sqrt.h>
/* >> sqrtf(3), sqrt(3), sqrtl(3)
 * Return the square root of  `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_sqrtf)(float x) {



	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2F(isless, x, 0.0f))
		return __kernel_standard_f(x, x, __LIBM_MATHFUN1IF(nan, ""), __LIBM_KMATHERRF_SQRT); /* sqrt(negative) */
	return __LIBM_MATHFUNF(sqrt, x);



}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_powl, libc_pow);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/finite.h>
#include <libm/isnan.h>
#include <libm/matherr.h>
#include <libm/pow.h>
#include <libm/signbit.h>
/* >> powf(3), pow(3), powl(3)
 * Return `x' to the `y' power */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __DECL_SIMD_powl __LONGDOUBLE
NOTHROW(LIBCCALL libc_powl)(__LONGDOUBLE x,
                            __LONGDOUBLE y) {



	__LONGDOUBLE result;
	result = __LIBM_MATHFUN2L(pow, x, y);
	/*
	 * ====================================================
	 * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Permission  to use, copy, modify, and distribute this
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
					return __kernel_standard_l(x, y, result, __LIBM_KMATHERRL_POW_NAN);
			} else if (__LIBM_MATHFUNIL(finite, x) && __LIBM_MATHFUNIL(finite, y)) {
				if (__LIBM_MATHFUNIL(isnan, result)) { /* pow neg**non-int */
					return __kernel_standard_l(x, y, result, __LIBM_KMATHERRL_POW_NONINT);
				} else if (x == 0.0L && y < 0.0L) {
					if (__LIBM_MATHFUNIL(signbit, x) && __LIBM_MATHFUNIL(signbit, result)) { /* pow(-0.0,negative) */
						return __kernel_standard_l(x, y, result, __LIBM_KMATHERRL_POW_MINUS);
					} else { /* pow(+0.0,negative) */
						return __kernel_standard_l(x, y, result, __LIBM_KMATHERRL_POW_ZEROMINUS);
					}
				} else {
					/* pow overflow */
					return __kernel_standard_l(x, y, result, __LIBM_KMATHERRL_POW_OVERFLOW);
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
				return __kernel_standard_l(x, y, result, __LIBM_KMATHERRL_POW_ZERO);
			}
		} else {
			/* pow underflow */
			return __kernel_standard_l(x, y, result, __LIBM_KMATHERRL_POW_UNDERFLOW);
		}
	}
	return result;



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_sqrtl, libc_sqrt);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/fcomp.h>
#include <libm/nan.h>
#include <libm/matherr.h>
#include <libm/sqrt.h>
/* >> sqrtf(3), sqrt(3), sqrtl(3)
 * Return the square root of  `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_sqrtl)(__LONGDOUBLE x) {



	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2L(isless, x, 0.0L))
		return __kernel_standard_l(x, x, __LIBM_MATHFUN1IL(nan, ""), __LIBM_KMATHERRL_SQRT); /* sqrt(negative) */
	return __LIBM_MATHFUNL(sqrt, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/finite.h>
#include <libm/matherr.h>
#include <libm/hypot.h>
/* >> hypotf(3), hypot(3), hypotl(3)
 * Return `sqrt(x*x + y*y)' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_hypot)(double x,
                             double y) {
	double result = __LIBM_MATHFUN2(hypot, y, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !__LIBM_MATHFUNI(finite, result) &&
	    __LIBM_MATHFUNI(finite, x) && __LIBM_MATHFUNI(finite, y))
		return __kernel_standard(x, y, result, __LIBM_KMATHERR_HYPOT); /* hypot overflow */
	return result;
}
#include <libm/finite.h>
#include <libm/matherr.h>
#include <libm/hypot.h>
/* >> hypotf(3), hypot(3), hypotl(3)
 * Return `sqrt(x*x + y*y)' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_hypotf)(float x,
                              float y) {



	float result = __LIBM_MATHFUN2F(hypot, y, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !__LIBM_MATHFUNIF(finite, result) &&
	    __LIBM_MATHFUNIF(finite, x) && __LIBM_MATHFUNIF(finite, y))
		return __kernel_standard_f(x, y, result, __LIBM_KMATHERRF_HYPOT); /* hypot overflow */
	return result;



}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_hypotl, libc_hypot);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/finite.h>
#include <libm/matherr.h>
#include <libm/hypot.h>
/* >> hypotf(3), hypot(3), hypotl(3)
 * Return `sqrt(x*x + y*y)' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_hypotl)(__LONGDOUBLE x,
                              __LONGDOUBLE y) {



	__LONGDOUBLE result = __LIBM_MATHFUN2L(hypot, y, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !__LIBM_MATHFUNIL(finite, result) &&
	    __LIBM_MATHFUNIL(finite, x) && __LIBM_MATHFUNIL(finite, y))
		return __kernel_standard_l(x, y, result, __LIBM_KMATHERRL_HYPOT); /* hypot overflow */
	return result;



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/cbrt.h>
/* >> cbrtf(3), cbrt(3), cbrtl(3)
 * Return  the  cube root  of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_cbrt)(double x) {
	return __LIBM_MATHFUN(cbrt, x);
}
#include <libm/cbrt.h>
/* >> cbrtf(3), cbrt(3), cbrtl(3)
 * Return  the  cube root  of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_cbrtf)(float x) {



	return __LIBM_MATHFUNF(cbrt, x);



}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_cbrtl, libc_cbrt);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/cbrt.h>
/* >> cbrtf(3), cbrt(3), cbrtl(3)
 * Return  the  cube root  of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_cbrtl)(__LONGDOUBLE x) {



	return __LIBM_MATHFUNL(cbrt, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#include <libm/ceil.h>
/* >> ceilf(3), ceil(3), ceill(3)
 * Smallest integral value not less than `x' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_ceil)(double x) {

	return __LIBM_MATHFUN(ceil, x);







}
#include <libm/fabs.h>
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_fabs)(double x) {

	return __LIBM_MATHFUN(fabs, x);



}
#include <hybrid/typecore.h>
#include <libm/floor.h>
/* >> floorf(3), floor(3), floorl(3)
 * Largest integer not greater than `x' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_floor)(double x) {

	return __LIBM_MATHFUN(floor, x);







}
#include <libm/isinf.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
#include <libm/fmod.h>
/* >> fmodf(3), fmod(3), fmodl(3)
 * Floating-point modulo remainder of `x / y' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_fmod)(double x,
                            double y) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUNI(isinf, x) || y == 0.0) &&
	    !__LIBM_MATHFUN2(isunordered, x, y))
		return __kernel_standard(x, y, y, __LIBM_KMATHERR_FMOD); /* fmod(+-Inf,y) or fmod(x,0) */
	return __LIBM_MATHFUN2(fmod, x, y);
}
#include <hybrid/typecore.h>
#include <libm/ceil.h>
/* >> ceilf(3), ceil(3), ceill(3)
 * Smallest integral value not less than `x' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_ceilf)(float x) {

	return __LIBM_MATHFUNF(ceil, x);







}
#include <libm/fabs.h>
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_fabsf)(float x) {

	return __LIBM_MATHFUNF(fabs, x);



}
#include <hybrid/typecore.h>
#include <libm/floor.h>
/* >> floorf(3), floor(3), floorl(3)
 * Largest integer not greater than `x' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_floorf)(float x) {

	return __LIBM_MATHFUNF(floor, x);







}
#include <libm/isinf.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
#include <libm/fmod.h>
/* >> fmodf(3), fmod(3), fmodl(3)
 * Floating-point modulo remainder of `x / y' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_fmodf)(float x,
                             float y) {



	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUNIF(isinf, x) || y == 0.0f) &&
	    !__LIBM_MATHFUN2F(isunordered, x, y))
		return __kernel_standard_f(x, y, y, __LIBM_KMATHERRF_FMOD); /* fmod(+-Inf,y) or fmod(x,0) */
	return __LIBM_MATHFUN2F(fmod, x, y);



}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_ceill, libc_ceil);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/ceil.h>
/* >> ceilf(3), ceil(3), ceill(3)
 * Smallest integral value not less than `x' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_ceill)(__LONGDOUBLE x) {

	return __LIBM_MATHFUNL(ceil, x);







}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_fabsl, libc_fabs);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/fabs.h>
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_fabsl)(__LONGDOUBLE x) {

	return __LIBM_MATHFUNL(fabs, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_floorl, libc_floor);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/floor.h>
/* >> floorf(3), floor(3), floorl(3)
 * Largest integer not greater than `x' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_floorl)(__LONGDOUBLE x) {

	return __LIBM_MATHFUNL(floor, x);







}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_fmodl, libc_fmod);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/isinf.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
#include <libm/fmod.h>
/* >> fmodf(3), fmod(3), fmodl(3)
 * Floating-point modulo remainder of `x / y' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_fmodl)(__LONGDOUBLE x,
                             __LONGDOUBLE y) {



	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUNIL(isinf, x) || y == 0.0L) &&
	    !__LIBM_MATHFUN2L(isunordered, x, y))
		return __kernel_standard_l(x, y, y, __LIBM_KMATHERRL_FMOD); /* fmod(+-Inf,y) or fmod(x,0) */
	return __LIBM_MATHFUN2L(fmod, x, y);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/copysign.h>
/* >> copysignf(3), copysign(3), copysignl(3)
 * Return `x' with its signed changed to `y's */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_copysign)(double num,
                                double sign) {

	return __LIBM_MATHFUN2(copysign, num, sign);





}
#include <libm/nan.h>
/* >> nanf(3), nan(3), nanl(3)
 * Return representation of qNaN for double type */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_nan)(char const *tagb) {
	return __LIBM_MATHFUN1I(nan, tagb);
}
#include <libm/copysign.h>
/* >> copysignf(3), copysign(3), copysignl(3)
 * Return `x' with its signed changed to `y's */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_copysignf)(float num,
                                 float sign) {

	return __LIBM_MATHFUN2F(copysign, num, sign);





}
#include <libm/nan.h>
/* >> nanf(3), nan(3), nanl(3)
 * Return representation of qNaN for double type */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_nanf)(char const *tagb) {



	return __LIBM_MATHFUN1IF(nan, tagb);



}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_copysignl, libc_copysign);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/copysign.h>
/* >> copysignf(3), copysign(3), copysignl(3)
 * Return `x' with its signed changed to `y's */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_copysignl)(__LONGDOUBLE num,
                                 __LONGDOUBLE sign) {

	return __LIBM_MATHFUN2L(copysign, num, sign);





}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_nanl, libc_nan);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/nan.h>
/* >> nanf(3), nan(3), nanl(3)
 * Return representation of qNaN for double type */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_nanl)(char const *tagb) {



	return __LIBM_MATHFUN1IL(nan, tagb);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/erf.h>
/* >> erff(3), erf(3), erfl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_erf)(double x) {
	return __LIBM_MATHFUN(erf, x);
}
#include <libm/erfc.h>
/* >> erfcf(3), erfc(3), erfcl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_erfc)(double x) {
	return __LIBM_MATHFUN(erfc, x);
}
/* >> lgammaf(3), lgamma(3), lgammal(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_lgamma)(double x) {
	return libc_lgamma_r(x, &__LOCAL_signgam);
}
#include <libm/erf.h>
/* >> erff(3), erf(3), erfl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_erff)(float x) {



	return __LIBM_MATHFUNF(erf, x);



}
#include <libm/erfc.h>
/* >> erfcf(3), erfc(3), erfcl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_erfcf)(float x) {



	return __LIBM_MATHFUNF(erfc, x);



}
/* >> lgammaf(3), lgamma(3), lgammal(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_lgammaf)(float x) {
	return libc_lgammaf_r(x, &__LOCAL_signgam);
}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_erfl, libc_erf);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/erf.h>
/* >> erff(3), erf(3), erfl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_erfl)(__LONGDOUBLE x) {



	return __LIBM_MATHFUNL(erf, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_erfcl, libc_erfc);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/erfc.h>
/* >> erfcf(3), erfc(3), erfcl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_erfcl)(__LONGDOUBLE x) {



	return __LIBM_MATHFUNL(erfc, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
/* >> lgammaf(3), lgamma(3), lgammal(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_lgammal)(__LONGDOUBLE x) {
	return libc_lgammal_r(x, &__LOCAL_signgam);
}
#include <libm/fcomp.h>
#include <libm/isinf.h>
#include <libm/finite.h>
#include <libm/matherr.h>
#include <libm/tgamma.h>
#include <libm/floor.h>
/* >> tgammaf(3), tgamma(3), tgammal(3)
 * True gamma function */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_tgamma)(double x) {
	int my_signgam;
	double result = __LIBM_MATHFUN2I(tgamma, x, &my_signgam);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !__LIBM_MATHFUN1I(finite, result) &&
	    (__LIBM_MATHFUN1I(finite, x) || __LIBM_MATHFUN1I(isinf, x) < 0)) {
		if (x == 0.0)
			return __kernel_standard(x, x, result, __LIBM_KMATHERR_TGAMMA_ZERO); /* tgamma pole */
		if (__LIBM_MATHFUN(floor, x) == x && x < 0.0)
			return __kernel_standard(x, x, result, __LIBM_KMATHERR_TGAMMA_MINUS); /* tgamma domain */
		if (result == 0.0)
			return __kernel_standard(x, x, result, __LIBM_KMATHERR_TGAMMA_UNDERFLOW); /* tgamma underflow */
		return __kernel_standard(x, x, result, __LIBM_KMATHERR_TGAMMA_OVERFLOW);      /* tgamma overflow */
	}
	return my_signgam < 0 ? -result : result;
}
#include <libm/fcomp.h>
#include <libm/isinf.h>
#include <libm/finite.h>
#include <libm/matherr.h>
#include <libm/tgamma.h>
#include <libm/floor.h>
/* >> tgammaf(3), tgamma(3), tgammal(3)
 * True gamma function */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_tgammaf)(float x) {



	int my_signgam;
	float result = __LIBM_MATHFUN2IF(tgamma, x, &my_signgam);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !__LIBM_MATHFUN1IF(finite, result) &&
	    (__LIBM_MATHFUN1IF(finite, x) || __LIBM_MATHFUN1IF(isinf, x) < 0)) {
		if (x == 0.0f)
			return __kernel_standard_f(x, x, result, __LIBM_KMATHERRF_TGAMMA_ZERO); /* tgamma pole */
		if (__LIBM_MATHFUNF(floor, x) == x && x < 0.0f)
			return __kernel_standard_f(x, x, result, __LIBM_KMATHERRF_TGAMMA_MINUS); /* tgamma domain */
		if (result == 0.0f)
			return __kernel_standard_f(x, x, result, __LIBM_KMATHERRF_TGAMMA_UNDERFLOW); /* tgamma underflow */
		return __kernel_standard_f(x, x, result, __LIBM_KMATHERRF_TGAMMA_OVERFLOW);      /* tgamma overflow */
	}
	return my_signgam < 0 ? -result : result;



}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_tgammal, libc_tgamma);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/fcomp.h>
#include <libm/isinf.h>
#include <libm/finite.h>
#include <libm/matherr.h>
#include <libm/tgamma.h>
#include <libm/floor.h>
/* >> tgammaf(3), tgamma(3), tgammal(3)
 * True gamma function */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_tgammal)(__LONGDOUBLE x) {



	int my_signgam;
	__LONGDOUBLE result = __LIBM_MATHFUN2IL(tgamma, x, &my_signgam);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !__LIBM_MATHFUN1IL(finite, result) &&
	    (__LIBM_MATHFUN1IL(finite, x) || __LIBM_MATHFUN1IL(isinf, x) < 0)) {
		if (x == 0.0L)
			return __kernel_standard_l(x, x, result, __LIBM_KMATHERRL_TGAMMA_ZERO); /* tgamma pole */
		if (__LIBM_MATHFUNL(floor, x) == x && x < 0.0L)
			return __kernel_standard_l(x, x, result, __LIBM_KMATHERRL_TGAMMA_MINUS); /* tgamma domain */
		if (result == 0.0L)
			return __kernel_standard_l(x, x, result, __LIBM_KMATHERRL_TGAMMA_UNDERFLOW); /* tgamma underflow */
		return __kernel_standard_l(x, x, result, __LIBM_KMATHERRL_TGAMMA_OVERFLOW);      /* tgamma overflow */
	}
	return my_signgam < 0 ? -result : result;



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/rint.h>
/* >> rintf(3), rint(3), rintl(3)
 * Return the integer nearest `x' in the direction of the prevailing rounding mode */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_rint)(double x) {
	return __LIBM_MATHFUN(rint, x);
}
#include <libm/nextafter.h>
/* >> nextafterf(3), nextafter(3), nextafterl(3)
 * Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_nextafter)(double x,
                                 double y) {
	return __LIBM_MATHFUN2(nextafter, x, y);
}
#include <libm/matherr.h>
#include <libm/isnan.h>
#include <libm/isinf.h>
#include <libm/remainder.h>
/* >> remainderf(3), remainder(3), remainderl(3)
 * Return the remainder of integer division `x / p' with infinite precision */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_remainder)(double x,
                                 double p) {
	if (((p == 0.0 && !__LIBM_MATHFUNI(isnan, x)) ||
	     (__LIBM_MATHFUNI(isinf, x) && !__LIBM_MATHFUNI(isnan, p))) &&
	    __LIBM_LIB_VERSION != __LIBM_IEEE)
		return __kernel_standard(x, p, p, __LIBM_KMATHERR_REMAINDER); /* remainder domain */
	return __LIBM_MATHFUN2(remainder, x, p);
}
#include <libm/ilogb.h>
#include <libm/matherr.h>
#include <bits/crt/mathdef.h>
/* >> ilogbf(3), ilogb(3), ilogbl(3)
 * Return the binary exponent of `x', which must be nonzero */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED int
NOTHROW(LIBCCALL libc_ilogb)(double x) {
	int result;
	result = __LIBM_MATHFUNI(ilogb, x);
	if (result == __FP_ILOGB0 || result == __FP_ILOGBNAN || result == INT_MAX)
		__kernel_standard(x, x, x, __LIBM_KMATHERR_ILOGB);
	return result;
}
#include <libm/rint.h>
/* >> rintf(3), rint(3), rintl(3)
 * Return the integer nearest `x' in the direction of the prevailing rounding mode */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_rintf)(float x) {



	return __LIBM_MATHFUNF(rint, x);



}
#include <libm/nextafter.h>
/* >> nextafterf(3), nextafter(3), nextafterl(3)
 * Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_nextafterf)(float x,
                                  float y) {



	return __LIBM_MATHFUN2F(nextafter, x, y);



}
#include <libm/matherr.h>
#include <libm/isnan.h>
#include <libm/isinf.h>
#include <libm/remainder.h>
/* >> remainderf(3), remainder(3), remainderl(3)
 * Return the remainder of integer division `x / p' with infinite precision */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_remainderf)(float x,
                                  float p) {



	if (((p == 0.0f && !__LIBM_MATHFUNIF(isnan, x)) ||
	     (__LIBM_MATHFUNIF(isinf, x) && !__LIBM_MATHFUNIF(isnan, p))) &&
	    __LIBM_LIB_VERSION != __LIBM_IEEE)
		return __kernel_standard_f(x, p, p, __LIBM_KMATHERRF_REMAINDER); /* remainder domain */
	return __LIBM_MATHFUN2F(remainder, x, p);



}
#include <libm/ilogb.h>
#include <libm/matherr.h>
#include <bits/crt/mathdef.h>
/* >> ilogbf(3), ilogb(3), ilogbl(3)
 * Return the binary exponent of `x', which must be nonzero */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED int
NOTHROW(LIBCCALL libc_ilogbf)(float x) {



	int result;
	result = __LIBM_MATHFUNIF(ilogb, x);
	if (result == __FP_ILOGB0 || result == __FP_ILOGBNAN || result == INT_MAX)
		__kernel_standard_f(x, x, x, __LIBM_KMATHERRF_ILOGB);
	return result;



}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_rintl, libc_rint);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/rint.h>
/* >> rintf(3), rint(3), rintl(3)
 * Return the integer nearest `x' in the direction of the prevailing rounding mode */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_rintl)(__LONGDOUBLE x) {



	return __LIBM_MATHFUNL(rint, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_nextafterl, libc_nextafter);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/nextafter.h>
/* >> nextafterf(3), nextafter(3), nextafterl(3)
 * Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_nextafterl)(__LONGDOUBLE x,
                                  __LONGDOUBLE y) {



	return __LIBM_MATHFUN2L(nextafter, x, y);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_remainderl, libc_remainder);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/matherr.h>
#include <libm/isnan.h>
#include <libm/isinf.h>
#include <libm/remainder.h>
/* >> remainderf(3), remainder(3), remainderl(3)
 * Return the remainder of integer division `x / p' with infinite precision */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_remainderl)(__LONGDOUBLE x,
                                  __LONGDOUBLE p) {



	if (((p == 0.0L && !__LIBM_MATHFUNIL(isnan, x)) ||
	     (__LIBM_MATHFUNIL(isinf, x) && !__LIBM_MATHFUNIL(isnan, p))) &&
	    __LIBM_LIB_VERSION != __LIBM_IEEE)
		return __kernel_standard_l(x, p, p, __LIBM_KMATHERRL_REMAINDER); /* remainder domain */
	return __LIBM_MATHFUN2L(remainder, x, p);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_ilogbl, libc_ilogb);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/ilogb.h>
#include <libm/matherr.h>
#include <bits/crt/mathdef.h>
/* >> ilogbf(3), ilogb(3), ilogbl(3)
 * Return the binary exponent of `x', which must be nonzero */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED int
NOTHROW(LIBCCALL libc_ilogbl)(__LONGDOUBLE x) {



	int result;
	result = __LIBM_MATHFUNIL(ilogb, x);
	if (result == __FP_ILOGB0 || result == __FP_ILOGBNAN || result == INT_MAX)
		__kernel_standard_l(x, x, x, __LIBM_KMATHERRL_ILOGB);
	return result;



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_nexttoward, libc_nextafter);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/nexttoward.h>
/* >> nexttowardf(3), nexttoward(3), nexttowardl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_nexttoward)(double x,
                                  __LONGDOUBLE y) {
#ifdef __IEEE854_LONG_DOUBLE_TYPE__

	return (double)__ieee754_nexttoward((__IEEE754_DOUBLE_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__)y);



#else /* __IEEE854_LONG_DOUBLE_TYPE__ */
	return (double)libc_nextafterl((__LONGDOUBLE)x, y);
#endif /* !__IEEE854_LONG_DOUBLE_TYPE__ */
}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/scalbn.h>
/* >> scalbnf(3), scalbn(3), scalbnl(3), scalblnf(3), scalbln(3), scalblnl(3)
 * Return `x' times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_scalbn)(double x,
                              int n) {
	return __LIBM_MATHFUN2I(scalbn, x, n);
}
#include <hybrid/typecore.h>
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_scalbln, libc_scalbn);
#else /* __SIZEOF_INT__ == __SIZEOF_LONG__ */
#include <libm/scalbn.h>
/* >> scalbnf(3), scalbn(3), scalbnl(3), scalblnf(3), scalbln(3), scalblnl(3)
 * Return `x' times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_scalbln)(double x,
                               long int n) {
	return __LIBM_MATHFUN2I(scalbln, x, n);
}
#endif /* __SIZEOF_INT__ != __SIZEOF_LONG__ */
#include <hybrid/typecore.h>
#include <libm/round.h>
/* >> roundf(3), round(3), roundl(3)
 * Round `x' to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_round)(double x) {

	return (double)__LIBM_MATHFUN(round, x);














}
#include <hybrid/typecore.h>
#include <libm/trunc.h>
/* >> truncf(3), trunc(3), truncl(3)
 * Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_trunc)(double x) {

	return __LIBM_MATHFUN(trunc, x);



}
#include <libm/remquo.h>
/* >> remquof(3), remquo(3), remquol(3)
 * Compute remainder of `x' and `p' and put in `*pquo' a value with
 * sign of x/p and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/p, with n >= 3 */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED ATTR_OUT(3) double
NOTHROW(LIBCCALL libc_remquo)(double x,
                              double p,
                              int *pquo) {
	return __LIBM_MATHFUN3I(remquo, x, p, pquo);
}
#include <hybrid/typecore.h>
#include <libm/lrint.h>
/* >> lrintf(3), lrint(3), lrintl(3)
 * Round `x' to nearest integral value according to current rounding direction */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED long int
NOTHROW(LIBCCALL libc_lrint)(double x) {

	return __LIBM_MATHFUNI(lrint, x);



}
#include <hybrid/typecore.h>
#include <libm/lround.h>
/* >> lroundf(3), lround(3), lroundl(3)
 * Round `x' to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED long int
NOTHROW(LIBCCALL libc_lround)(double x) {

	return __LIBM_MATHFUNI(lround, x);



}
/* >> fdimf(3), fdim(3), fdiml(3)
 * Return positive difference between `x' and `y' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_fdim)(double x,
                            double y) {
	/* TODO: ieee754-specific function */
	return libc_fabs(y - x);
}
#include <ieee754.h>
#include <libm/fcomp.h>
#include <libm/isnan.h>
/* >> fmaxf(3), fmax(3), fmaxl(3)
 * Return maximum numeric value from `x' and `y' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_fmax)(double x,
                            double y) {

	if (__LIBM_MATHFUNI2(isgreaterequal, x, y))
		return x;
	if (__LIBM_MATHFUNI(isnan, y))
		return x;




	return y;
}
#include <ieee754.h>
#include <libm/fcomp.h>
#include <libm/isnan.h>
/* >> fminf(3), fmin(3), fminl(3)
 * Return minimum numeric value from `x' and `y' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_fmin)(double x,
                            double y) {

	if (__LIBM_MATHFUNI2(islessequal, x, y))
		return x;
	if (__LIBM_MATHFUNI(isnan, y))
		return x;




	return y;
}
/* >> fmaf(3), fma(3), fmal(3)
 * Multiply-add function computed as a ternary operation */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_fma)(double x,
                           double y,
                           double z) {
	/* TODO: ieee754-specific function */
	return (x * y) + z;
}
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS(libc_llrint, libc_lrint);
#else /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
#include <libm/lrint.h>
/* >> llrintf(3), llrint(3), llrintl(3)
 * Round `x' to nearest integral value according to current rounding direction */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGLONG
NOTHROW(LIBCCALL libc_llrint)(double x) {

	return __LIBM_MATHFUNI(llrint, x);



}
#endif /* __SIZEOF_LONG__ != __SIZEOF_LONG_LONG__ */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS(libc_llround, libc_lround);
#else /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
#include <libm/lround.h>
/* >> llroundf(3), llround(3), llroundl(3)
 * Round `x' to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGLONG
NOTHROW(LIBCCALL libc_llround)(double x) {

	return __LIBM_MATHFUNI(llround, x);



}
#endif /* __SIZEOF_LONG__ != __SIZEOF_LONG_LONG__ */
#include <libm/nexttoward.h>
/* >> nexttowardf(3), nexttoward(3), nexttowardl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_nexttowardf)(float x,
                                   __LONGDOUBLE y) {
#ifdef __IEEE854_LONG_DOUBLE_TYPE__

	return (float)__ieee754_nexttowardf((__IEEE754_FLOAT_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__)y);



#else /* __IEEE854_LONG_DOUBLE_TYPE__ */
	return (float)__ieee754_nexttowardf_d((__IEEE754_FLOAT_TYPE__)x, (__IEEE754_DOUBLE_TYPE__)y);


#endif /* !__IEEE854_LONG_DOUBLE_TYPE__ */
}
#include <libm/scalbn.h>
/* >> scalbnf(3), scalbn(3), scalbnl(3), scalblnf(3), scalbln(3), scalblnl(3)
 * Return `x' times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_scalbnf)(float x,
                               int n) {



	return __LIBM_MATHFUN2IF(scalbn, x, n);



}
#include <hybrid/typecore.h>
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_scalblnf, libc_scalbnf);
#else /* __SIZEOF_INT__ == __SIZEOF_LONG__ */
#include <libm/scalbn.h>
/* >> scalbnf(3), scalbn(3), scalbnl(3), scalblnf(3), scalbln(3), scalblnl(3)
 * Return `x' times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_scalblnf)(float x,
                                long int n) {



	return __LIBM_MATHFUN2IF(scalbln, x, n);



}
#endif /* __SIZEOF_INT__ != __SIZEOF_LONG__ */
#include <hybrid/typecore.h>
#include <libm/round.h>
/* >> roundf(3), round(3), roundl(3)
 * Round `x' to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_roundf)(float x) {

	return (float)__LIBM_MATHFUNF(round, x);














}
#include <hybrid/typecore.h>
#include <libm/trunc.h>
/* >> truncf(3), trunc(3), truncl(3)
 * Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_truncf)(float x) {

	return __LIBM_MATHFUNF(trunc, x);



}
#include <libm/remquo.h>
/* >> remquof(3), remquo(3), remquol(3)
 * Compute remainder of `x' and `p' and put in `*pquo' a value with
 * sign of x/p and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/p, with n >= 3 */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED ATTR_OUT(3) float
NOTHROW(LIBCCALL libc_remquof)(float x,
                               float p,
                               int *pquo) {



	return __LIBM_MATHFUN3IF(remquo, x, p, pquo);



}
#include <hybrid/typecore.h>
#include <libm/lrint.h>
/* >> lrintf(3), lrint(3), lrintl(3)
 * Round `x' to nearest integral value according to current rounding direction */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED long int
NOTHROW(LIBCCALL libc_lrintf)(float x) {

	return __LIBM_MATHFUNIF(lrint, x);



}
#include <hybrid/typecore.h>
#include <libm/lround.h>
/* >> lroundf(3), lround(3), lroundl(3)
 * Round `x' to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED long int
NOTHROW(LIBCCALL libc_lroundf)(float x) {

	return __LIBM_MATHFUNIF(lround, x);



}
/* >> fdimf(3), fdim(3), fdiml(3)
 * Return positive difference between `x' and `y' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_fdimf)(float x,
                             float y) {
	/* TODO: ieee754-specific function */
	return libc_fabsf(y - x);
}
#include <ieee754.h>
#include <libm/fcomp.h>
#include <libm/isnan.h>
/* >> fmaxf(3), fmax(3), fmaxl(3)
 * Return maximum numeric value from `x' and `y' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_fmaxf)(float x,
                             float y) {

	if (__LIBM_MATHFUNI2F(isgreaterequal, x, y))
		return x;
	if (__LIBM_MATHFUNIF(isnan, y))
		return x;




	return y;
}
#include <ieee754.h>
#include <libm/fcomp.h>
#include <libm/isnan.h>
/* >> fminf(3), fmin(3), fminl(3)
 * Return minimum numeric value from `x' and `y' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_fminf)(float x,
                             float y) {

	if (__LIBM_MATHFUNI2F(islessequal, x, y))
		return x;
	if (__LIBM_MATHFUNIF(isnan, y))
		return x;




	return y;
}
/* >> fmaf(3), fma(3), fmal(3)
 * Multiply-add function computed as a ternary operation */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_fmaf)(float x,
                            float y,
                            float z) {
	/* TODO: ieee754-specific function */
	return (x * y) + z;
}
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS(libc_llrintf, libc_lrintf);
#else /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
#include <libm/lrint.h>
/* >> llrintf(3), llrint(3), llrintl(3)
 * Round `x' to nearest integral value according to current rounding direction */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGLONG
NOTHROW(LIBCCALL libc_llrintf)(float x) {

	return __LIBM_MATHFUNIF(llrint, x);



}
#endif /* __SIZEOF_LONG__ != __SIZEOF_LONG_LONG__ */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS(libc_llroundf, libc_lroundf);
#else /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
#include <libm/lround.h>
/* >> llroundf(3), llround(3), llroundl(3)
 * Round `x' to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGLONG
NOTHROW(LIBCCALL libc_llroundf)(float x) {

	return __LIBM_MATHFUNIF(llround, x);



}
#endif /* __SIZEOF_LONG__ != __SIZEOF_LONG_LONG__ */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_scalbnl, libc_scalbn);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/scalbn.h>
/* >> scalbnf(3), scalbn(3), scalbnl(3), scalblnf(3), scalbln(3), scalblnl(3)
 * Return `x' times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_scalbnl)(__LONGDOUBLE x,
                               int n) {



	return __LIBM_MATHFUN2IL(scalbn, x, n);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#if __SIZEOF_INT__ == __SIZEOF_LONG__ && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
DEFINE_INTERN_ALIAS(libc_scalblnl, libc_scalbn);
#elif __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_scalblnl, libc_scalbnl);
#elif defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
DEFINE_INTERN_ALIAS(libc_scalblnl, libc_scalbln);
#else /* ... */
#include <libm/scalbn.h>
/* >> scalbnf(3), scalbn(3), scalbnl(3), scalblnf(3), scalbln(3), scalblnl(3)
 * Return `x' times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_scalblnl)(__LONGDOUBLE x,
                                long int n) {



	return __LIBM_MATHFUN2IL(scalbln, x, n);



}
#endif /* !... */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_roundl, libc_round);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/round.h>
/* >> roundf(3), round(3), roundl(3)
 * Round `x' to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_roundl)(__LONGDOUBLE x) {

	return (__LONGDOUBLE)__LIBM_MATHFUNL(round, x);














}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_truncl, libc_trunc);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/trunc.h>
/* >> truncf(3), trunc(3), truncl(3)
 * Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_truncl)(__LONGDOUBLE x) {

	return __LIBM_MATHFUNL(trunc, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_remquol, libc_remquo);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/remquo.h>
/* >> remquof(3), remquo(3), remquol(3)
 * Compute remainder of `x' and `p' and put in `*pquo' a value with
 * sign of x/p and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/p, with n >= 3 */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED ATTR_OUT(3) __LONGDOUBLE
NOTHROW(LIBCCALL libc_remquol)(__LONGDOUBLE x,
                               __LONGDOUBLE p,
                               int *pquo) {



	return __LIBM_MATHFUN3IL(remquo, x, p, pquo);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_lrintl, libc_remquo);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/lrint.h>
/* >> lrintf(3), lrint(3), lrintl(3)
 * Round `x' to nearest integral value according to current rounding direction */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED long int
NOTHROW(LIBCCALL libc_lrintl)(__LONGDOUBLE x) {

	return __LIBM_MATHFUNIL(lrint, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#include <libm/lround.h>
/* >> lroundf(3), lround(3), lroundl(3)
 * Round `x' to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED long int
NOTHROW(LIBCCALL libc_lroundl)(__LONGDOUBLE x) {

	return __LIBM_MATHFUNIL(lround, x);



}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_fdiml, libc_fdim);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
/* >> fdimf(3), fdim(3), fdiml(3)
 * Return positive difference between `x' and `y' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_fdiml)(__LONGDOUBLE x,
                             __LONGDOUBLE y) {
	/* TODO: ieee754-specific function */
	return libc_fabsl(y - x);
}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_fmaxl, libc_fmax);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <ieee754.h>
#include <libm/fcomp.h>
#include <libm/isnan.h>
/* >> fmaxf(3), fmax(3), fmaxl(3)
 * Return maximum numeric value from `x' and `y' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_fmaxl)(__LONGDOUBLE x,
                             __LONGDOUBLE y) {

	if (__LIBM_MATHFUNI2L(isgreaterequal, x, y))
		return x;
	if (__LIBM_MATHFUNIL(isnan, y))
		return x;




	return y;
}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_fminl, libc_fmin);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <ieee754.h>
#include <libm/fcomp.h>
#include <libm/isnan.h>
/* >> fminf(3), fmin(3), fminl(3)
 * Return minimum numeric value from `x' and `y' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_fminl)(__LONGDOUBLE x,
                             __LONGDOUBLE y) {

	if (__LIBM_MATHFUNI2L(islessequal, x, y))
		return x;
	if (__LIBM_MATHFUNIL(isnan, y))
		return x;




	return y;
}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_fmal, libc_fma);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
/* >> fmaf(3), fma(3), fmal(3)
 * Multiply-add function computed as a ternary operation */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_fmal)(__LONGDOUBLE x,
                            __LONGDOUBLE y,
                            __LONGDOUBLE z) {
	/* TODO: ieee754-specific function */
	return (x * y) + z;
}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
DEFINE_INTERN_ALIAS(libc_llrintl, libc_lrint);
#elif __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS(libc_llrintl, libc_lrintl);
#elif defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
DEFINE_INTERN_ALIAS(libc_llrintl, libc_llrint);
#else /* ... */
#include <libm/lrint.h>
/* >> llrintf(3), llrint(3), llrintl(3)
 * Round `x' to nearest integral value according to current rounding direction */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGLONG
NOTHROW(LIBCCALL libc_llrintl)(__LONGDOUBLE x) {

	return __LIBM_MATHFUNIL(llrint, x);



}
#endif /* !... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
DEFINE_INTERN_ALIAS(libc_llroundl, libc_lround);
#elif __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS(libc_llroundl, libc_lroundl);
#elif defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
DEFINE_INTERN_ALIAS(libc_llroundl, libc_llround);
#else /* ... */
#include <libm/lround.h>
/* >> llroundf(3), llround(3), llroundl(3)
 * Round `x' to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGLONG
NOTHROW(LIBCCALL libc_llroundl)(__LONGDOUBLE x) {

	return __LIBM_MATHFUNIL(llround, x);



}
#endif /* !... */
#include <libm/sincos.h>
/* >> sincosf(3), sincos(3), sincosl(3)
 * Calculate both sine (*psinx) and cosine (*pcosx) of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") __DECL_SIMD_sincos ATTR_OUT(2) ATTR_OUT(3) void
NOTHROW(LIBCCALL libc_sincos)(double x,
                              double *psinx,
                              double *pcosx) {

	__LIBM_MATHFUNX(sincos)(x, (__LIBM_MATHFUN_T *)psinx, (__LIBM_MATHFUN_T *)pcosx);




}
#include <hybrid/floatcore.h>
#include <bits/crt/fenv.h>
#include <libm/matherr.h>
/* >> exp10f(3), exp10(3), exp10l(3)
 * A function missing in all standards: compute exponent to base ten */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_exp10)(double x) {
	double result;
	if (libc_finite(x) && x < __DBL_MIN_10_EXP__ - __DBL_DIG__ - 10) {
		libc_feraiseexcept(FE_UNDERFLOW);
		return 0.0;
	}
	result = libc_exp(2.30258509299404568402 * x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !libc_finite(result) && libc_finite(x)) {
		/* exp10 overflow (46) if x > 0, underflow (47) if x < 0. */
		return __kernel_standard(x, x, result, libc___signbit(x)
		                         ? __LIBM_KMATHERR_EXP10_UNDERFLOW
		                         : __LIBM_KMATHERR_EXP10_OVERFLOW);
	}
	return result;
}
/* >> pow10f(3), pow10(3), pow10l(3)
 * Another  name  occasionally  used */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_pow10)(double x) {
	return libc_pow(10.0, x);
}
#include <libm/sincos.h>
/* >> sincosf(3), sincos(3), sincosl(3)
 * Calculate both sine (*psinx) and cosine (*pcosx) of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") __DECL_SIMD_sincosf ATTR_OUT(2) ATTR_OUT(3) void
NOTHROW(LIBCCALL libc_sincosf)(float x,
                               float *psinx,
                               float *pcosx) {

	__LIBM_MATHFUNXF(sincos)(x, (__LIBM_MATHFUNF_T *)psinx, (__LIBM_MATHFUNF_T *)pcosx);









}
#include <hybrid/floatcore.h>
#include <bits/crt/fenv.h>
#include <libm/matherr.h>
/* >> exp10f(3), exp10(3), exp10l(3)
 * A function missing in all standards: compute exponent to base ten */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_exp10f)(float x) {
	float result;
	result = (float)libc_exp(2.30258509299404568402 * (double)x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !libc_finitef(result) && libc_finitef(x)) {
		/* exp10 overflow (46) if x > 0, underflow (47) if x < 0. */
		return __kernel_standard_f(x, x, result, libc___signbitf(x)
		                           ? __LIBM_KMATHERRF_EXP10_UNDERFLOW
		                           : __LIBM_KMATHERRF_EXP10_OVERFLOW);
	}
	return result;
}
/* >> pow10f(3), pow10(3), pow10l(3)
 * Another  name  occasionally  used */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_pow10f)(float x) {

	return libc_powf(10.0f, x);



}
#include <libm/sincos.h>
/* >> sincosf(3), sincos(3), sincosl(3)
 * Calculate both sine (*psinx) and cosine (*pcosx) of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") __DECL_SIMD_sincosl ATTR_OUT(2) ATTR_OUT(3) void
NOTHROW(LIBCCALL libc_sincosl)(__LONGDOUBLE x,
                               __LONGDOUBLE *psinx,
                               __LONGDOUBLE *pcosx) {

	__LIBM_MATHFUNXL(sincos)(x, (__LIBM_MATHFUNL_T *)psinx, (__LIBM_MATHFUNL_T *)pcosx);









}
#include <hybrid/floatcore.h>
#include <bits/crt/fenv.h>
#include <libm/matherr.h>
/* >> exp10f(3), exp10(3), exp10l(3)
 * A function missing in all standards: compute exponent to base ten */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_exp10l)(__LONGDOUBLE x) {
	__LONGDOUBLE result;
	if (libc_finitel(x) && x < __LDBL_MIN_10_EXP__ - __LDBL_DIG__ - 10) {
		libc_feraiseexcept(FE_UNDERFLOW);
		return 0.0L;
	}
	result = libc_expl(2.302585092994045684017991454684364208L * x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !libc_finitel(result) && libc_finitel(x)) {
		/* exp10 overflow (46) if x > 0, underflow (47) if x < 0. */
		return __kernel_standard_l(x, x, result, libc___signbitl(x)
		                           ? __LIBM_KMATHERRL_EXP10_UNDERFLOW
		                           : __LIBM_KMATHERRL_EXP10_OVERFLOW);
	}
	return result;
}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_pow10l, libc_pow10);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
/* >> pow10f(3), pow10(3), pow10l(3)
 * Another  name  occasionally  used */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_pow10l)(__LONGDOUBLE x) {

	return libc_powl(10.0L, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/isinf.h>
/* >> isinff(3), isinf(3), isinfl(3)
 * Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isinf)(double x) {

	return __LIBM_MATHFUNI(isinf, x);





}
#include <libm/isinf.h>
/* >> isinff(3), isinf(3), isinfl(3)
 * Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isinff)(float x) {




	
	return __LIBM_MATHFUNIF(isinf, x);








}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_isinfl, libc_isinf);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/isinf.h>
/* >> isinff(3), isinf(3), isinfl(3)
 * Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isinfl)(__LONGDOUBLE x) {




	
	return __LIBM_MATHFUNIL(isinf, x);








}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/finite.h>
/* >> finitef(3), finite(3), finitel(3)
 * Return nonzero if `value' is finite and not NaN */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_finite)(double x) {

	return __LIBM_MATHFUNI(finite, x);



}
#include <libm/significand.h>
/* >> significandf(3), significand(3), significandl(3)
 * Return the fractional part of `x' after dividing out `ilogb(x)' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_significand)(double x) {
	return __LIBM_MATHFUN(significand, x);
}
#include <libm/finite.h>
/* >> finitef(3), finite(3), finitel(3)
 * Return nonzero if `value' is finite and not NaN */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_finitef)(float x) {




	
	return __LIBM_MATHFUNIF(finite, x);






}
#include <libm/significand.h>
/* >> significandf(3), significand(3), significandl(3)
 * Return the fractional part of `x' after dividing out `ilogb(x)' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_significandf)(float x) {



	return __LIBM_MATHFUNF(significand, x);



}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_finitel, libc_finite);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/finite.h>
/* >> finitef(3), finite(3), finitel(3)
 * Return nonzero if `value' is finite and not NaN */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_finitel)(__LONGDOUBLE x) {




	
	return __LIBM_MATHFUNIL(finite, x);






}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_significandl, libc_significand);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/significand.h>
/* >> significandf(3), significand(3), significandl(3)
 * Return the fractional part of `x' after dividing out `ilogb(x)' */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_significandl)(__LONGDOUBLE x) {



	return __LIBM_MATHFUNL(significand, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/isnan.h>
/* >> isnanf(3), isnan(3), isnanl(3)
 * Return nonzero if `value' is not a number */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isnan)(double x) {
	return __LIBM_MATHFUNI(isnan, x);
}
#include <libm/isnan.h>
/* >> isnanf(3), isnan(3), isnanl(3)
 * Return nonzero if `value' is not a number */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isnanf)(float x) {



	return __LIBM_MATHFUNIF(isnan, x);



}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_isnanl, libc_isnan);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/isnan.h>
/* >> isnanf(3), isnan(3), isnanl(3)
 * Return nonzero if `value' is not a number */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isnanl)(__LONGDOUBLE x) {



	return __LIBM_MATHFUNIL(isnan, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/j0.h>
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <libm/matherr.h>
/* >> j0f(3), j0(3), j0l(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_j0)(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_LIB_VERSION != __LIBM_POSIX &&
	    __LIBM_MATHFUNI2(isgreater, __LIBM_MATHFUN(fabs, x), 1.41484755040568800000e+16 /*X_TLOSS*/))
		return __kernel_standard(x, x, 0.0, __LIBM_KMATHERR_J0_TLOSS); /* j0(|x|>X_TLOSS) */
	return __LIBM_MATHFUN(j0, x);
}
#include <libm/j1.h>
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <libm/matherr.h>
/* >> j1f(3), j1(3), j1l(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_j1)(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_LIB_VERSION != __LIBM_POSIX &&
	    __LIBM_MATHFUNI2(isgreater, __LIBM_MATHFUN(fabs, x), 1.41484755040568800000e+16 /*X_TLOSS*/))
		return __kernel_standard(x, x, 0.0, __LIBM_KMATHERR_J1_TLOSS); /* j1(|x|>X_TLOSS) */
	return __LIBM_MATHFUN(j1, x);
}
#include <libm/jn.h>
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <libm/matherr.h>
/* >> jnf(3), jn(3), jnl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_jn)(int n,
                          double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_LIB_VERSION != __LIBM_POSIX &&
	    __LIBM_MATHFUNI2(isgreater, __LIBM_MATHFUN(fabs, x), 1.41484755040568800000e+16 /*X_TLOSS*/))
		return __kernel_standard(n, x, 0.0, __LIBM_KMATHERR_JN_TLOSS); /* jn(n,|x|>X_TLOSS) */
	return __LIBM_MATHFUNIM(jn, n, x);
}
#include <libm/fcomp.h>
#include <bits/math-constants.h>
#include <libm/matherr.h>
#include <libm/y0.h>
#include <bits/crt/fenv.h>
/* >> y0f(3), y0(3), y0l(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_y0)(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUNI2(islessequal, x, 0.0) ||
	     __LIBM_MATHFUNI2(isgreater, x, 1.41484755040568800000e+16 /*X_TLOSS*/))) {
		if (x < 0.0) {
			libc_feraiseexcept(FE_INVALID);
			return __kernel_standard(x, x, -__HUGE_VAL, __LIBM_KMATHERR_Y0_MINUS);
		} else if (x == 0.0) {
			return __kernel_standard(x, x, -__HUGE_VAL, __LIBM_KMATHERR_Y0_ZERO);
		} else if (__LIBM_LIB_VERSION != __LIBM_POSIX) {
			return __kernel_standard(x, x, 0.0f, __LIBM_KMATHERR_Y0_TLOSS);
		}
	}
	return __LIBM_MATHFUN(y0, x);
}
#include <libm/fcomp.h>
#include <bits/math-constants.h>
#include <libm/matherr.h>
#include <libm/y1.h>
#include <bits/crt/fenv.h>
/* >> y1f(3), y1(3), y1l(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_y1)(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUNI2(islessequal, x, 0.0) ||
	     __LIBM_MATHFUNI2(isgreater, x, 1.41484755040568800000e+16 /*X_TLOSS*/))) {
		if (x < 0.0) {
			libc_feraiseexcept(FE_INVALID);
			return __kernel_standard(x, x, -__HUGE_VAL, __LIBM_KMATHERR_Y1_MINUS);
		} else if (x == 0.0) {
			return __kernel_standard(x, x, -__HUGE_VAL, __LIBM_KMATHERR_Y1_ZERO);
		} else if (__LIBM_LIB_VERSION != __LIBM_POSIX) {
			return __kernel_standard(x, x, 0.0f, __LIBM_KMATHERR_Y1_TLOSS);
		}
	}
	return __LIBM_MATHFUN(y1, x);
}
#include <libm/fcomp.h>
#include <bits/math-constants.h>
#include <libm/matherr.h>
#include <libm/yn.h>
#include <bits/crt/fenv.h>
/* >> ynf(3), yn(3), ynl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_yn)(int n,
                          double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUNI2(islessequal, x, 0.0) ||
	     __LIBM_MATHFUNI2(isgreater, x, 1.41484755040568800000e+16 /*X_TLOSS*/))) {
		if (x < 0.0) {
			libc_feraiseexcept(FE_INVALID);
			return __kernel_standard(n, x, -__HUGE_VAL, __LIBM_KMATHERR_YN_MINUS);
		} else if (x == 0.0) {
			return __kernel_standard(n, x, -__HUGE_VAL, __LIBM_KMATHERR_YN_ZERO);
		} else if (__LIBM_LIB_VERSION != __LIBM_POSIX) {
			return __kernel_standard(n, x, 0.0f, __LIBM_KMATHERR_YN_TLOSS);
		}
	}
	return __LIBM_MATHFUNIM(yn, n, x);
}
#include <libm/j0.h>
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <libm/matherr.h>
/* >> j0f(3), j0(3), j0l(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_j0f)(float x) {



	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_LIB_VERSION != __LIBM_POSIX &&
	    __LIBM_MATHFUNI2F(isgreater, __LIBM_MATHFUNF(fabs, x), 1.41484755040568800000e+16 /*X_TLOSS*/))
		return __kernel_standard_f(x, x, 0.0f, __LIBM_KMATHERRF_J0_TLOSS); /* j0(|x|>X_TLOSS) */
	return __LIBM_MATHFUNF(j0, x);



}
#include <libm/j1.h>
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <libm/matherr.h>
/* >> j1f(3), j1(3), j1l(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_j1f)(float x) {



	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_LIB_VERSION != __LIBM_POSIX &&
	    __LIBM_MATHFUNI2F(isgreater, __LIBM_MATHFUNF(fabs, x), 1.41484755040568800000e+16 /*X_TLOSS*/))
		return __kernel_standard_f(x, x, 0.0f, __LIBM_KMATHERRF_J1_TLOSS); /* j1(|x|>X_TLOSS) */
	return __LIBM_MATHFUNF(j1, x);



}
#include <libm/jn.h>
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <libm/matherr.h>
/* >> jnf(3), jn(3), jnl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_jnf)(int n,
                           float x) {



	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_LIB_VERSION != __LIBM_POSIX &&
	    __LIBM_MATHFUNI2F(isgreater, __LIBM_MATHFUNF(fabs, x), 1.41484755040568800000e+16 /*X_TLOSS*/))
		return __kernel_standard_f(n, x, 0.0f, __LIBM_KMATHERRF_JN_TLOSS); /* jn(n,|x|>X_TLOSS) */
	return __LIBM_MATHFUNIMF(jn, n, x);



}
#include <libm/fcomp.h>
#include <bits/math-constants.h>
#include <libm/matherr.h>
#include <libm/y0.h>
#include <bits/crt/fenv.h>
/* >> y0f(3), y0(3), y0l(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_y0f)(float x) {




	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUNI2F(islessequal, x, 0.0f) ||
	     __LIBM_MATHFUNI2F(isgreater, x, 1.41484755040568800000e+16 /*X_TLOSS*/))) {
		if (x < 0.0f) {
			libc_feraiseexcept(FE_INVALID);
			return __kernel_standard_f(x, x, -__HUGE_VALF, __LIBM_KMATHERRF_Y0_MINUS);
		} else if (x == 0.0f) {
			return __kernel_standard_f(x, x, -__HUGE_VALF, __LIBM_KMATHERRF_Y0_ZERO);
		} else if (__LIBM_LIB_VERSION != __LIBM_POSIX) {
			return __kernel_standard_f(x, x, 0.0f, __LIBM_KMATHERRF_Y0_TLOSS);
		}
	}
	return __LIBM_MATHFUNF(y0, x);



}
#include <libm/fcomp.h>
#include <bits/math-constants.h>
#include <libm/matherr.h>
#include <libm/y1.h>
#include <bits/crt/fenv.h>
/* >> y1f(3), y1(3), y1l(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_y1f)(float x) {




	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUNI2F(islessequal, x, 0.0f) ||
	     __LIBM_MATHFUNI2F(isgreater, x, 1.41484755040568800000e+16 /*X_TLOSS*/))) {
		if (x < 0.0f) {
			libc_feraiseexcept(FE_INVALID);
			return __kernel_standard_f(x, x, -__HUGE_VALF, __LIBM_KMATHERRF_Y1_MINUS);
		} else if (x == 0.0f) {
			return __kernel_standard_f(x, x, -__HUGE_VALF, __LIBM_KMATHERRF_Y1_ZERO);
		} else if (__LIBM_LIB_VERSION != __LIBM_POSIX) {
			return __kernel_standard_f(x, x, 0.0f, __LIBM_KMATHERRF_Y1_TLOSS);
		}
	}
	return __LIBM_MATHFUNF(y1, x);



}
#include <libm/fcomp.h>
#include <bits/math-constants.h>
#include <libm/matherr.h>
#include <libm/yn.h>
#include <bits/crt/fenv.h>
/* >> ynf(3), yn(3), ynl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_ynf)(int n,
                           float x) {




	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUNI2F(islessequal, x, 0.0f) ||
	     __LIBM_MATHFUNI2F(isgreater, x, 1.41484755040568800000e+16 /*X_TLOSS*/))) {
		if (x < 0.0f) {
			libc_feraiseexcept(FE_INVALID);
			return __kernel_standard_f(n, x, -__HUGE_VALF, __LIBM_KMATHERRF_YN_MINUS);
		} else if (x == 0.0f) {
			return __kernel_standard_f(n, x, -__HUGE_VALF, __LIBM_KMATHERRF_YN_ZERO);
		} else if (__LIBM_LIB_VERSION != __LIBM_POSIX) {
			return __kernel_standard_f(n, x, 0.0f, __LIBM_KMATHERRF_YN_TLOSS);
		}
	}
	return __LIBM_MATHFUNIMF(yn, n, x);



}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_j0l, libc_j0);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/j0.h>
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <libm/matherr.h>
/* >> j0f(3), j0(3), j0l(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_j0l)(__LONGDOUBLE x) {



	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_LIB_VERSION != __LIBM_POSIX &&
	    __LIBM_MATHFUNI2L(isgreater, __LIBM_MATHFUNL(fabs, x), 1.41484755040568800000e+16 /*X_TLOSS*/))
		return __kernel_standard_l(x, x, 0.0L, __LIBM_KMATHERRL_J0_TLOSS); /* j0(|x|>X_TLOSS) */
	return __LIBM_MATHFUNL(j0, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_j1l, libc_j1);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/j1.h>
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <libm/matherr.h>
/* >> j1f(3), j1(3), j1l(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_j1l)(__LONGDOUBLE x) {



	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_LIB_VERSION != __LIBM_POSIX &&
	    __LIBM_MATHFUNI2L(isgreater, __LIBM_MATHFUNL(fabs, x), 1.41484755040568800000e+16 /*X_TLOSS*/))
		return __kernel_standard_l(x, x, 0.0L, __LIBM_KMATHERRL_J1_TLOSS); /* j1(|x|>X_TLOSS) */
	return __LIBM_MATHFUNL(j1, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_jnl, libc_jn);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/jn.h>
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <libm/matherr.h>
/* >> jnf(3), jn(3), jnl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_jnl)(int n,
                           __LONGDOUBLE x) {



	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_LIB_VERSION != __LIBM_POSIX &&
	    __LIBM_MATHFUNI2L(isgreater, __LIBM_MATHFUNL(fabs, x), 1.41484755040568800000e+16 /*X_TLOSS*/))
		return __kernel_standard_l(n, x, 0.0L, __LIBM_KMATHERRL_JN_TLOSS); /* jn(n,|x|>X_TLOSS) */
	return __LIBM_MATHFUNIML(jn, n, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_y0l, libc_y0);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/fcomp.h>
#include <bits/math-constants.h>
#include <libm/matherr.h>
#include <libm/y0.h>
#include <bits/crt/fenv.h>
/* >> y0f(3), y0(3), y0l(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_y0l)(__LONGDOUBLE x) {




	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUNI2L(islessequal, x, 0.0L) ||
	     __LIBM_MATHFUNI2L(isgreater, x, 1.41484755040568800000e+16 /*X_TLOSS*/))) {
		if (x < 0.0L) {
			libc_feraiseexcept(FE_INVALID);
			return __kernel_standard_l(x, x, -__HUGE_VALL, __LIBM_KMATHERRL_Y0_MINUS);
		} else if (x == 0.0L) {
			return __kernel_standard_l(x, x, -__HUGE_VALL, __LIBM_KMATHERRL_Y0_ZERO);
		} else if (__LIBM_LIB_VERSION != __LIBM_POSIX) {
			return __kernel_standard_l(x, x, 0.0f, __LIBM_KMATHERRL_Y0_TLOSS);
		}
	}
	return __LIBM_MATHFUNL(y0, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_y1l, libc_y1);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/fcomp.h>
#include <bits/math-constants.h>
#include <libm/matherr.h>
#include <libm/y1.h>
#include <bits/crt/fenv.h>
/* >> y1f(3), y1(3), y1l(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_y1l)(__LONGDOUBLE x) {




	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUNI2L(islessequal, x, 0.0L) ||
	     __LIBM_MATHFUNI2L(isgreater, x, 1.41484755040568800000e+16 /*X_TLOSS*/))) {
		if (x < 0.0L) {
			libc_feraiseexcept(FE_INVALID);
			return __kernel_standard_l(x, x, -__HUGE_VALL, __LIBM_KMATHERRL_Y1_MINUS);
		} else if (x == 0.0L) {
			return __kernel_standard_l(x, x, -__HUGE_VALL, __LIBM_KMATHERRL_Y1_ZERO);
		} else if (__LIBM_LIB_VERSION != __LIBM_POSIX) {
			return __kernel_standard_l(x, x, 0.0f, __LIBM_KMATHERRL_Y1_TLOSS);
		}
	}
	return __LIBM_MATHFUNL(y1, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_ynl, libc_yn);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/fcomp.h>
#include <bits/math-constants.h>
#include <libm/matherr.h>
#include <libm/yn.h>
#include <bits/crt/fenv.h>
/* >> ynf(3), yn(3), ynl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_ynl)(int n,
                           __LONGDOUBLE x) {




	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUNI2L(islessequal, x, 0.0L) ||
	     __LIBM_MATHFUNI2L(isgreater, x, 1.41484755040568800000e+16 /*X_TLOSS*/))) {
		if (x < 0.0L) {
			libc_feraiseexcept(FE_INVALID);
			return __kernel_standard_l(n, x, -__HUGE_VALL, __LIBM_KMATHERRL_YN_MINUS);
		} else if (x == 0.0L) {
			return __kernel_standard_l(n, x, -__HUGE_VALL, __LIBM_KMATHERRL_YN_ZERO);
		} else if (__LIBM_LIB_VERSION != __LIBM_POSIX) {
			return __kernel_standard_l(n, x, 0.0f, __LIBM_KMATHERRL_YN_TLOSS);
		}
	}
	return __LIBM_MATHFUNIML(yn, n, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/lgamma.h>
#include <libm/matherr.h>
#include <libm/finite.h>
#include <libm/floor.h>
/* >> lgammaf_r(3), lgamma_r(3), lgammal_r(3)
 * Reentrant    version    of     `lgamma(3)' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED ATTR_OUT(2) double
NOTHROW_NCX(LIBCCALL libc_lgamma_r)(double x,
                                    int *signgamp) {
	double result = __LIBM_MATHFUN2I(lgamma, x, signgamp);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    !__LIBM_MATHFUNI(finite, result) && __LIBM_MATHFUNI(finite, x)) {
		return __kernel_standard(x, x, result,
		                         __LIBM_MATHFUN(floor, x) == x &&
		                         x <= 0.0 ? __LIBM_KMATHERR_LGAMMA_MINUS      /* lgamma pole */
		                                  : __LIBM_KMATHERR_LGAMMA_OVERFLOW); /* lgamma overflow */
	}
	return result;
}
#include <libm/lgamma.h>
#include <libm/matherr.h>
#include <libm/finite.h>
#include <libm/floor.h>
/* >> lgammaf_r(3), lgamma_r(3), lgammal_r(3)
 * Reentrant    version    of     `lgamma(3)' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED ATTR_OUT(2) float
NOTHROW_NCX(LIBCCALL libc_lgammaf_r)(float x,
                                     int *signgamp) {



	float result = __LIBM_MATHFUN2IF(lgamma, x, signgamp);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    !__LIBM_MATHFUNIF(finite, result) && __LIBM_MATHFUNIF(finite, x)) {
		return __kernel_standard_f(x, x, result,
		                         __LIBM_MATHFUNF(floor, x) == x &&
		                         x <= 0.0f ? __LIBM_KMATHERRF_LGAMMA_MINUS      /* lgamma pole */
		                                  : __LIBM_KMATHERRF_LGAMMA_OVERFLOW); /* lgamma overflow */
	}
	return result;



}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_lgammal_r, libc_lgamma_r);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/lgamma.h>
#include <libm/matherr.h>
#include <libm/finite.h>
#include <libm/floor.h>
/* >> lgammaf_r(3), lgamma_r(3), lgammal_r(3)
 * Reentrant    version    of     `lgamma(3)' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED ATTR_OUT(2) __LONGDOUBLE
NOTHROW_NCX(LIBCCALL libc_lgammal_r)(__LONGDOUBLE x,
                                     int *signgamp) {



	__LONGDOUBLE result = __LIBM_MATHFUN2IL(lgamma, x, signgamp);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    !__LIBM_MATHFUNIL(finite, result) && __LIBM_MATHFUNIL(finite, x)) {
		return __kernel_standard_l(x, x, result,
		                         __LIBM_MATHFUNL(floor, x) == x &&
		                         x <= 0.0L ? __LIBM_KMATHERRL_LGAMMA_MINUS      /* lgamma pole */
		                                  : __LIBM_KMATHERRL_LGAMMA_OVERFLOW); /* lgamma overflow */
	}
	return result;



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/isnan.h>
#include <libm/finite.h>
#include <libm/isinf.h>
#include <libm/matherr.h>
#include <libc/errno.h>
#include <libm/scalb.h>
/* >> scalbf(3), scalb(3), scalbl(3)
 * Return `x' times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_scalb)(double x,
                             double fn) {
	/*
	 * ====================================================
	 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Developed at SunSoft, a Sun Microsystems, Inc. business.
	 * Permission  to  use, copy,  modify, and  distribute this
	 * software is freely  granted, provided  that this  notice
	 * is preserved.
	 * ====================================================
	 */
	double result;
	result = __LIBM_MATHFUN2(scalb, x, fn);
	if (__LIBM_LIB_VERSION == __LIBM_SVID) {
		if (__LIBM_MATHFUNI(isinf, result)) {
			if (__LIBM_MATHFUNI(finite, x)) {
				return __kernel_standard(x, fn, result, __LIBM_KMATHERR_SCALB_OVERFLOW); /* scalb overflow */
			} else {

				(void)libc_seterrno(ERANGE);

			}
		} else if (result == 0.0 && result != x) {
			return __kernel_standard(x, fn, result, __LIBM_KMATHERR_SCALB_UNDERFLOW); /* scalb underflow */
		}
	} else {
		if (!__LIBM_MATHFUNI(finite, result) || result == 0.0) {
			if (__LIBM_MATHFUNI(isnan, result)) {
				if (!__LIBM_MATHFUNI(isnan, x) && !__LIBM_MATHFUNI(isnan, fn))
					result = __kernel_standard(x, fn, result, __LIBM_KMATHERR_SCALB_INVALID);
			} else if (__LIBM_MATHFUNI(isinf, result)) {
				if (!__LIBM_MATHFUNI(isinf, x) && !__LIBM_MATHFUNI(isinf, fn))
					result = __kernel_standard(x, fn, result, __LIBM_KMATHERR_SCALB_OVERFLOW);
			} else {
				/* result == 0. */
				if (x != 0.0 && !__LIBM_MATHFUNI(isinf, fn))
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
#include <libc/errno.h>
#include <libm/scalb.h>
/* >> scalbf(3), scalb(3), scalbl(3)
 * Return `x' times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED float
NOTHROW(LIBCCALL libc_scalbf)(float x,
                              float fn) {



	/*
	 * ====================================================
	 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Developed at SunSoft, a Sun Microsystems, Inc. business.
	 * Permission  to  use, copy,  modify, and  distribute this
	 * software is freely  granted, provided  that this  notice
	 * is preserved.
	 * ====================================================
	 */
	float result;
	result = __LIBM_MATHFUN2F(scalb, x, fn);
	if (__LIBM_LIB_VERSION == __LIBM_SVID) {
		if (__LIBM_MATHFUNIF(isinf, result)) {
			if (__LIBM_MATHFUNIF(finite, x)) {
				return __kernel_standard_f(x, fn, result, __LIBM_KMATHERRF_SCALB_OVERFLOW); /* scalb overflow */
			} else {

				(void)libc_seterrno(ERANGE);

			}
		} else if (result == 0.0f && result != x) {
			return __kernel_standard_f(x, fn, result, __LIBM_KMATHERRF_SCALB_UNDERFLOW); /* scalb underflow */
		}
	} else {
		if (!__LIBM_MATHFUNIF(finite, result) || result == 0.0f) {
			if (__LIBM_MATHFUNIF(isnan, result)) {
				if (!__LIBM_MATHFUNIF(isnan, x) && !__LIBM_MATHFUNIF(isnan, fn))
					result = __kernel_standard_f(x, fn, result, __LIBM_KMATHERRF_SCALB_INVALID);
			} else if (__LIBM_MATHFUNIF(isinf, result)) {
				if (!__LIBM_MATHFUNIF(isinf, x) && !__LIBM_MATHFUNIF(isinf, fn))
					result = __kernel_standard_f(x, fn, result, __LIBM_KMATHERRF_SCALB_OVERFLOW);
			} else {
				/* result == 0. */
				if (x != 0.0f && !__LIBM_MATHFUNIF(isinf, fn))
					result = __kernel_standard_f(x, fn, result, __LIBM_KMATHERRF_SCALB_UNDERFLOW);
			}
		}
	}
	return result;



}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_scalbl, libc_scalb);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/isnan.h>
#include <libm/finite.h>
#include <libm/isinf.h>
#include <libm/matherr.h>
#include <libc/errno.h>
#include <libm/scalb.h>
/* >> scalbf(3), scalb(3), scalbl(3)
 * Return `x' times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_scalbl)(__LONGDOUBLE x,
                              __LONGDOUBLE fn) {



	/*
	 * ====================================================
	 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Developed at SunSoft, a Sun Microsystems, Inc. business.
	 * Permission  to  use, copy,  modify, and  distribute this
	 * software is freely  granted, provided  that this  notice
	 * is preserved.
	 * ====================================================
	 */
	__LONGDOUBLE result;
	result = __LIBM_MATHFUN2L(scalb, x, fn);
	if (__LIBM_LIB_VERSION == __LIBM_SVID) {
		if (__LIBM_MATHFUNIL(isinf, result)) {
			if (__LIBM_MATHFUNIL(finite, x)) {
				return __kernel_standard_l(x, fn, result, __LIBM_KMATHERRL_SCALB_OVERFLOW); /* scalb overflow */
			} else {

				(void)libc_seterrno(ERANGE);

			}
		} else if (result == 0.0L && result != x) {
			return __kernel_standard_l(x, fn, result, __LIBM_KMATHERRL_SCALB_UNDERFLOW); /* scalb underflow */
		}
	} else {
		if (!__LIBM_MATHFUNIL(finite, result) || result == 0.0L) {
			if (__LIBM_MATHFUNIL(isnan, result)) {
				if (!__LIBM_MATHFUNIL(isnan, x) && !__LIBM_MATHFUNIL(isnan, fn))
					result = __kernel_standard_l(x, fn, result, __LIBM_KMATHERRL_SCALB_INVALID);
			} else if (__LIBM_MATHFUNIL(isinf, result)) {
				if (!__LIBM_MATHFUNIL(isinf, x) && !__LIBM_MATHFUNIL(isinf, fn))
					result = __kernel_standard_l(x, fn, result, __LIBM_KMATHERRL_SCALB_OVERFLOW);
			} else {
				/* result == 0. */
				if (x != 0.0L && !__LIBM_MATHFUNIL(isinf, fn))
					result = __kernel_standard_l(x, fn, result, __LIBM_KMATHERRL_SCALB_UNDERFLOW);
			}
		}
	}
	return result;



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
/* >> fpclassify(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd___fpclassify)(double x) { return fptype_kos2dos(libc___fpclassify(x)); }
#include <libm/fpclassify.h>
/* >> fpclassify(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc___fpclassify)(double x) {
	return __LIBM_MATHFUNI(fpclassify, x);
}
#include <libm/signbit.h>
/* >> signbit(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc___signbit)(double x) {

	return __LIBM_MATHFUNI(signbit, x);



}
/* >> fpclassify(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd___fpclassifyf)(float x) { return fptype_kos2dos(libc___fpclassifyf(x)); }
#include <libm/fpclassify.h>
/* >> fpclassify(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc___fpclassifyf)(float x) {



	return __LIBM_MATHFUNIF(fpclassify, x);



}
#include <libm/signbit.h>
/* >> signbit(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc___signbitf)(float x) {

	return __LIBM_MATHFUNIF(signbit, x);



}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd___fpclassifyl, libd___fpclassify);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
/* >> fpclassify(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd___fpclassifyl)(__LONGDOUBLE x) { return fptype_kos2dos(libc___fpclassifyl(x)); }
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc___fpclassifyl, libc___fpclassify);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/fpclassify.h>
/* >> fpclassify(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc___fpclassifyl)(__LONGDOUBLE x) {



	return __LIBM_MATHFUNIL(fpclassify, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc___signbitl, libc___signbit);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/signbit.h>
/* >> signbit(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc___signbitl)(__LONGDOUBLE x) {

	return __LIBM_MATHFUNIL(signbit, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/issignaling.h>
/* >> issignaling(3), __issignalingf(3), __issignaling(3), __issignalingl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc___issignaling)(double x) {
	return __LIBM_MATHFUNI(issignaling, x);
}
#include <libm/issignaling.h>
/* >> issignaling(3), __issignalingf(3), __issignaling(3), __issignalingl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc___issignalingf)(float x) {



	return __LIBM_MATHFUNIF(issignaling, x);



}
#include <libm/iscanonical.h>
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc___iscanonicall)(__LONGDOUBLE x) {



	(void)x;
	return 1;

}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc___issignalingl, libc___issignaling);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/issignaling.h>
/* >> issignaling(3), __issignalingf(3), __issignaling(3), __issignalingl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc___issignalingl)(__LONGDOUBLE x) {



	return __LIBM_MATHFUNIL(issignaling, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
/* >> nextdownf(3), nextdown(3), nextdownl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_nextdown)(double x) {
	return -libc_nextup(-x);
}
#include <libm/nextup.h>
/* >> nextupf(3), nextup(3), nextupl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_nextup)(double x) {
	return __LIBM_MATHFUN(nextup, x);
}
/* >> nextdownf(3), nextdown(3), nextdownl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_nextdownf)(float x) {

	return -libc_nextupf(-x);



}
#include <libm/nextup.h>
/* >> nextupf(3), nextup(3), nextupl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_nextupf)(float x) {



	return __LIBM_MATHFUNF(nextup, x);



}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_nextdownl, libc_nextdown);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
/* >> nextdownf(3), nextdown(3), nextdownl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_nextdownl)(__LONGDOUBLE x) {

	return -libc_nextupl(-x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_nextupl, libc_nextup);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/nextup.h>
/* >> nextupf(3), nextup(3), nextupl(3) */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_nextupl)(__LONGDOUBLE x) {



	return __LIBM_MATHFUNL(nextup, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_llogb, libc_ilogb);
#else /* __SIZEOF_INT__ == __SIZEOF_LONG__ */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED long int
NOTHROW(LIBCCALL libc_llogb)(double x) {
	return (long int)libc_ilogb(x); /* TODO: support for sizeof(long) > sizeof(int) */
}
#endif /* __SIZEOF_INT__ != __SIZEOF_LONG__ */
#include <libm/roundeven.h>
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_roundeven)(double x) {
	return __LIBM_MATHFUN(roundeven, x);
}
#include <libm/fcomp.h>
#include <libm/fabs.h>
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_fmaxmag)(double x,
                               double y) {
	double x_abs = __LIBM_MATHFUN(fabs, x);
	double y_abs = __LIBM_MATHFUN(fabs, y);
	if (__LIBM_MATHFUN2(isgreater, x_abs, y_abs))
		return x;
	if (__LIBM_MATHFUN2(isless, x_abs, y_abs))
		return y;
	return libc_fmax(x, y);
}
#include <libm/fcomp.h>
#include <libm/fabs.h>
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_fminmag)(double x,
                               double y) {
	double x_abs = __LIBM_MATHFUN(fabs, x);
	double y_abs = __LIBM_MATHFUN(fabs, y);
	if (__LIBM_MATHFUN2(isless, x_abs, y_abs))
		return x;
	if (__LIBM_MATHFUN2(isgreater, x_abs, y_abs))
		return y;
	return libc_fmin(x, y);
}
/* >> canonicalizef(3), canonicalize(3), canonicalizel(3)
 * @param: x:  Pointer to the value to canonicalize.
 * @param: cx: Store the canonicalized value of `*x' here.
 * @return: 0: Success
 * @return: 1: Error (`!iscanonical(*x)') */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_IN(2) ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_canonicalize)(double *cx,
                                        double const *x) {
	double value = *x;




	if (libc___issignaling(value)) {
		*cx = value + value;
	} else {
		*cx = value;
	}
	return 0;
}
#include <hybrid/typecore.h>
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_llogbf, libc_ilogbf);
#else /* __SIZEOF_INT__ == __SIZEOF_LONG__ */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED long int
NOTHROW(LIBCCALL libc_llogbf)(float x) {

	return (long int)libc_ilogbf(x); /* TODO: support for sizeof(long) > sizeof(int) */



}
#endif /* __SIZEOF_INT__ != __SIZEOF_LONG__ */
#include <libm/roundeven.h>
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_roundevenf)(float x) {



	return __LIBM_MATHFUNF(roundeven, x);



}
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED intmax_t
NOTHROW_NCX(LIBCCALL libc_fromfpf)(float x,
                                   int roundf,
                                   unsigned int width) {
	return libc_fromfp((double)x, roundf, width);
}
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED uintmax_t
NOTHROW_NCX(LIBCCALL libc_ufromfpf)(float x,
                                    int roundf,
                                    unsigned int width) {
	return libc_ufromfp((double)x, roundf, width);
}
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED intmax_t
NOTHROW_NCX(LIBCCALL libc_fromfpxf)(float x,
                                    int roundf,
                                    unsigned int width) {
	return libc_fromfpx((double)x, roundf, width);
}
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED uintmax_t
NOTHROW_NCX(LIBCCALL libc_ufromfpxf)(float x,
                                     int roundf,
                                     unsigned int width) {
	return libc_ufromfpx((double)x, roundf, width);
}
#include <libm/fcomp.h>
#include <libm/fabs.h>
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_fmaxmagf)(float x,
                                float y) {




	float x_abs = __LIBM_MATHFUNF(fabs, x);
	float y_abs = __LIBM_MATHFUNF(fabs, y);
	if (__LIBM_MATHFUN2F(isgreater, x_abs, y_abs))
		return x;
	if (__LIBM_MATHFUN2F(isless, x_abs, y_abs))
		return y;
	return libc_fmaxf(x, y);



}
#include <libm/fcomp.h>
#include <libm/fabs.h>
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc_fminmagf)(float x,
                                float y) {




	float x_abs = __LIBM_MATHFUNF(fabs, x);
	float y_abs = __LIBM_MATHFUNF(fabs, y);
	if (__LIBM_MATHFUN2F(isless, x_abs, y_abs))
		return x;
	if (__LIBM_MATHFUN2F(isgreater, x_abs, y_abs))
		return y;
	return libc_fminf(x, y);



}
/* >> canonicalizef(3), canonicalize(3), canonicalizel(3)
 * @param: x:  Pointer to the value to canonicalize.
 * @param: cx: Store the canonicalized value of `*x' here.
 * @return: 0: Success
 * @return: 1: Error (`!iscanonical(*x)') */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_IN(2) ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_canonicalizef)(float *cx,
                                         float const *x) {
	float value = *x;




	if (libc___issignalingf(value)) {
		*cx = value + value;
	} else {
		*cx = value;
	}
	return 0;
}
#include <hybrid/typecore.h>
#if __SIZEOF_INT__ == __SIZEOF_LONG__ && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
DEFINE_INTERN_ALIAS(libc_llogbl, libc_ilogb);
#elif __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_llogbl, libc_ilogbl);
#elif defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
DEFINE_INTERN_ALIAS(libc_llogbl, libc_llogbl);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED long int
NOTHROW(LIBCCALL libc_llogbl)(__LONGDOUBLE x) {

	return (long int)libc_ilogbl(x); /* TODO: support for sizeof(long) > sizeof(int) */



}
#endif /* !... */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_roundevenl, libc_roundeven);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/roundeven.h>
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_roundevenl)(__LONGDOUBLE x) {



	return __LIBM_MATHFUNL(roundeven, x);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_fromfpl, libc_fromfp);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED intmax_t
NOTHROW_NCX(LIBCCALL libc_fromfpl)(__LONGDOUBLE x,
                                   int roundl,
                                   unsigned int width) {
	return libc_fromfp((double)x, roundl, width);
}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_ufromfpl, libc_ufromfp);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED uintmax_t
NOTHROW_NCX(LIBCCALL libc_ufromfpl)(__LONGDOUBLE x,
                                    int roundl,
                                    unsigned int width) {
	return libc_ufromfp((double)x, roundl, width);
}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_fromfpxl, libc_fromfpx);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED intmax_t
NOTHROW_NCX(LIBCCALL libc_fromfpxl)(__LONGDOUBLE x,
                                    int roundl,
                                    unsigned int width) {
	return libc_fromfpx((double)x, roundl, width);
}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_ufromfpxl, libc_ufromfpx);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED uintmax_t
NOTHROW_NCX(LIBCCALL libc_ufromfpxl)(__LONGDOUBLE x,
                                     int roundl,
                                     unsigned int width) {
	return libc_ufromfpx((double)x, roundl, width);
}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_fmaxmagl, libc_fmaxmag);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/fcomp.h>
#include <libm/fabs.h>
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_fmaxmagl)(__LONGDOUBLE x,
                                __LONGDOUBLE y) {




	__LONGDOUBLE x_abs = __LIBM_MATHFUNL(fabs, x);
	__LONGDOUBLE y_abs = __LIBM_MATHFUNL(fabs, y);
	if (__LIBM_MATHFUN2L(isgreater, x_abs, y_abs))
		return x;
	if (__LIBM_MATHFUN2L(isless, x_abs, y_abs))
		return y;
	return libc_fmaxl(x, y);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_fminmagl, libc_fminmag);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/fcomp.h>
#include <libm/fabs.h>
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBCCALL libc_fminmagl)(__LONGDOUBLE x,
                                __LONGDOUBLE y) {




	__LONGDOUBLE x_abs = __LIBM_MATHFUNL(fabs, x);
	__LONGDOUBLE y_abs = __LIBM_MATHFUNL(fabs, y);
	if (__LIBM_MATHFUN2L(isless, x_abs, y_abs))
		return x;
	if (__LIBM_MATHFUN2L(isgreater, x_abs, y_abs))
		return y;
	return libc_fminl(x, y);



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_canonicalizel, libc_canonicalize);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
/* >> canonicalizef(3), canonicalize(3), canonicalizel(3)
 * @param: x:  Pointer to the value to canonicalize.
 * @param: cx: Store the canonicalized value of `*x' here.
 * @return: 0: Success
 * @return: 1: Error (`!iscanonical(*x)') */
INTERN ATTR_SECTION(".text.crt.math.math") ATTR_IN(2) ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_canonicalizel)(__LONGDOUBLE *cx,
                                         __LONGDOUBLE const *x) {
	__LONGDOUBLE value = *x;

	if (!libc___iscanonicall(value))
		return 1;

	if (libc___issignalingl(value)) {
		*cx = value + value;
	} else {
		*cx = value;
	}
	return 0;
}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/fcomp.h>
/* >> _fdpcomp(3), _dpcomp(3), _ldpcomp(3) */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc__dpcomp)(double x,
                               double y) {
	int result = 0;
	if (!__LIBM_MATHFUN2(isunordered, x, y)) {
		if (__LIBM_MATHFUN2(isgreater, x, y))
			result |= 4;
		if (__LIBM_MATHFUN2(isgreaterequal, x, y))
			result |= 2 | 4;
		if (__LIBM_MATHFUN2(isless, x, y))
			result |= 1;
		if (__LIBM_MATHFUN2(islessequal, x, y))
			result |= 1 | 2;
		if (__LIBM_MATHFUN2(islessgreater, x, y))
			result |= 1 | 4;
	}
	return result;
}
#include <libm/fcomp.h>
/* >> _fdpcomp(3), _dpcomp(3), _ldpcomp(3) */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc__fdpcomp)(float x,
                                float y) {



	int result = 0;
	if (!__LIBM_MATHFUN2F(isunordered, x, y)) {
		if (__LIBM_MATHFUN2F(isgreater, x, y))
			result |= 4;
		if (__LIBM_MATHFUN2F(isgreaterequal, x, y))
			result |= 2 | 4;
		if (__LIBM_MATHFUN2F(isless, x, y))
			result |= 1;
		if (__LIBM_MATHFUN2F(islessequal, x, y))
			result |= 1 | 2;
		if (__LIBM_MATHFUN2F(islessgreater, x, y))
			result |= 1 | 4;
	}
	return result;



}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc__ldpcomp, libc__dpcomp);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libm/fcomp.h>
/* >> _fdpcomp(3), _dpcomp(3), _ldpcomp(3) */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc__ldpcomp)(__LONGDOUBLE x,
                                __LONGDOUBLE y) {



	int result = 0;
	if (!__LIBM_MATHFUN2L(isunordered, x, y)) {
		if (__LIBM_MATHFUN2L(isgreater, x, y))
			result |= 4;
		if (__LIBM_MATHFUN2L(isgreaterequal, x, y))
			result |= 2 | 4;
		if (__LIBM_MATHFUN2L(isless, x, y))
			result |= 1;
		if (__LIBM_MATHFUN2L(islessequal, x, y))
			result |= 1 | 2;
		if (__LIBM_MATHFUN2L(islessgreater, x, y))
			result |= 1 | 4;
	}
	return result;



}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#endif /* !__KERNEL__ */
#ifndef __KERNEL__
#undef signgam
#undef __signgam
INTERN ATTR_SECTION(".bss.crt.math.math") int libc_signgam = 0;
DEFINE_PUBLIC_ALIAS(signgam, libc_signgam);
DEFINE_PUBLIC_ALIAS(__signgam, libc___signgam);
#define signgam     GET_NOREL_GLOBAL(signgam)
#define __signgam() (&signgam)
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.math.math") int *
NOTHROW(LIBCCALL libc___signgam)(void) {
	return &signgam;
}
#endif /* !__KERNEL__ */
#ifndef __KERNEL__
/* >> _fdtest(3), _dtest(3), _ldtest(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.math.math") ATTR_PURE WUNUSED ATTR_IN(1) short
NOTHROW_NCX(LIBDCALL libd__dtest)(double __KOS_FIXED_CONST *px) {
	return libd___fpclassify(*px);
}
/* >> _fdtest(3), _dtest(3), _ldtest(3) */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_PURE WUNUSED ATTR_IN(1) short
NOTHROW_NCX(LIBCCALL libc__dtest)(double __KOS_FIXED_CONST *px) {
	return libc___fpclassify(*px);
}
/* >> _fdtest(3), _dtest(3), _ldtest(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.math.math") ATTR_PURE WUNUSED ATTR_IN(1) short
NOTHROW_NCX(LIBDCALL libd__fdtest)(float __KOS_FIXED_CONST *px) {
	return libd___fpclassifyf(*px);
}
/* >> _fdtest(3), _dtest(3), _ldtest(3) */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_PURE WUNUSED ATTR_IN(1) short
NOTHROW_NCX(LIBCCALL libc__fdtest)(float __KOS_FIXED_CONST *px) {
	return libc___fpclassifyf(*px);
}
/* >> _fdtest(3), _dtest(3), _ldtest(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.math.math") ATTR_PURE WUNUSED ATTR_IN(1) short
NOTHROW_NCX(LIBDCALL libd__ldtest)(__LONGDOUBLE __KOS_FIXED_CONST *px) {
	return libd___fpclassifyl(*px);
}
/* >> _fdtest(3), _dtest(3), _ldtest(3) */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_PURE WUNUSED ATTR_IN(1) short
NOTHROW_NCX(LIBCCALL libc__ldtest)(__LONGDOUBLE __KOS_FIXED_CONST *px) {
	return libc___fpclassifyl(*px);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBCCALL libc__chgsignf)(float x) {
	return -x;
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc__chgsign)(double x) {
	return -x;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__acos, libc_acos);
DEFINE_PUBLIC_ALIAS(acos, libc_acos);
DEFINE_PUBLIC_ALIAS(__asin, libc_asin);
DEFINE_PUBLIC_ALIAS(asin, libc_asin);
DEFINE_PUBLIC_ALIAS(__atan, libc_atan);
DEFINE_PUBLIC_ALIAS(atan, libc_atan);
DEFINE_PUBLIC_ALIAS(__atan2, libc_atan2);
DEFINE_PUBLIC_ALIAS(atan2, libc_atan2);
DEFINE_PUBLIC_ALIAS(__cos, libc_cos);
DEFINE_PUBLIC_ALIAS(cos, libc_cos);
DEFINE_PUBLIC_ALIAS(__sin, libc_sin);
DEFINE_PUBLIC_ALIAS(sin, libc_sin);
DEFINE_PUBLIC_ALIAS(__tan, libc_tan);
DEFINE_PUBLIC_ALIAS(tan, libc_tan);
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
DEFINE_PUBLIC_ALIAS(__cosh, libc_cosh);
DEFINE_PUBLIC_ALIAS(cosh, libc_cosh);
DEFINE_PUBLIC_ALIAS(__sinh, libc_sinh);
DEFINE_PUBLIC_ALIAS(sinh, libc_sinh);
DEFINE_PUBLIC_ALIAS(__tanh, libc_tanh);
DEFINE_PUBLIC_ALIAS(tanh, libc_tanh);
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
DEFINE_PUBLIC_ALIAS(__acosh, libc_acosh);
DEFINE_PUBLIC_ALIAS(acosh, libc_acosh);
DEFINE_PUBLIC_ALIAS(__asinh, libc_asinh);
DEFINE_PUBLIC_ALIAS(asinh, libc_asinh);
DEFINE_PUBLIC_ALIAS(__atanh, libc_atanh);
DEFINE_PUBLIC_ALIAS(atanh, libc_atanh);
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
DEFINE_PUBLIC_ALIAS(__log, libc_log);
DEFINE_PUBLIC_ALIAS(log, libc_log);
DEFINE_PUBLIC_ALIAS(__log10, libc_log10);
DEFINE_PUBLIC_ALIAS(log10, libc_log10);
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
DEFINE_PUBLIC_ALIAS(__log1p, libc_log1p);
DEFINE_PUBLIC_ALIAS(log1p, libc_log1p);
DEFINE_PUBLIC_ALIAS(__logb, libc_logb);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_logb, libc_logb);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(logb, libc_logb);
DEFINE_PUBLIC_ALIAS(__expm1f, libc_expm1f);
DEFINE_PUBLIC_ALIAS(expm1f, libc_expm1f);
DEFINE_PUBLIC_ALIAS(__log1pf, libc_log1pf);
DEFINE_PUBLIC_ALIAS(log1pf, libc_log1pf);
DEFINE_PUBLIC_ALIAS(__logbf, libc_logbf);
#if defined(__LIBCCALL_IS_LIBDCALL) && defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(_logbf, libc_logbf);
#endif /* __LIBCCALL_IS_LIBDCALL && __x86_64__ */
DEFINE_PUBLIC_ALIAS(logbf, libc_logbf);
DEFINE_PUBLIC_ALIAS(__expm1l, libc_expm1l);
DEFINE_PUBLIC_ALIAS(expm1l, libc_expm1l);
DEFINE_PUBLIC_ALIAS(__log1pl, libc_log1pl);
DEFINE_PUBLIC_ALIAS(log1pl, libc_log1pl);
DEFINE_PUBLIC_ALIAS(__logbl, libc_logbl);
DEFINE_PUBLIC_ALIAS(logbl, libc_logbl);
DEFINE_PUBLIC_ALIAS(__exp2, libc_exp2);
DEFINE_PUBLIC_ALIAS(exp2, libc_exp2);
DEFINE_PUBLIC_ALIAS(__log2, libc_log2);
DEFINE_PUBLIC_ALIAS(log2, libc_log2);
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
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_hypot, libc_hypot);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__hypot, libc_hypot);
DEFINE_PUBLIC_ALIAS(hypot, libc_hypot);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_hypotf, libc_hypotf);
#endif /* __LIBCCALL_IS_LIBDCALL */
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
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_copysignf, libc_copysignf);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__copysignf, libc_copysignf);
DEFINE_PUBLIC_ALIAS(copysignf, libc_copysignf);
DEFINE_PUBLIC_ALIAS(__nanf, libc_nanf);
DEFINE_PUBLIC_ALIAS(nanf, libc_nanf);
DEFINE_PUBLIC_ALIAS(__copysignl, libc_copysignl);
DEFINE_PUBLIC_ALIAS(copysignl, libc_copysignl);
DEFINE_PUBLIC_ALIAS(__nanl, libc_nanl);
DEFINE_PUBLIC_ALIAS(nanl, libc_nanl);
DEFINE_PUBLIC_ALIAS(__erf, libc_erf);
DEFINE_PUBLIC_ALIAS(erf, libc_erf);
DEFINE_PUBLIC_ALIAS(__erfc, libc_erfc);
DEFINE_PUBLIC_ALIAS(erfc, libc_erfc);
DEFINE_PUBLIC_ALIAS(gamma, libc_lgamma);
DEFINE_PUBLIC_ALIAS(__lgamma, libc_lgamma);
DEFINE_PUBLIC_ALIAS(__gamma, libc_lgamma);
DEFINE_PUBLIC_ALIAS(lgamma, libc_lgamma);
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
DEFINE_PUBLIC_ALIAS(__tgamma, libc_tgamma);
DEFINE_PUBLIC_ALIAS(tgamma, libc_tgamma);
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
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_nextafter, libc_nextafter);
#endif /* __LIBCCALL_IS_LIBDCALL */
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
#if defined(__LIBCCALL_IS_LIBDCALL) && defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(_nextafterf, libc_nextafterf);
#endif /* __LIBCCALL_IS_LIBDCALL && __x86_64__ */
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
DEFINE_PUBLIC_ALIAS(__remquo, libc_remquo);
DEFINE_PUBLIC_ALIAS(remquo, libc_remquo);
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
DEFINE_PUBLIC_ALIAS(__sincos, libc_sincos);
DEFINE_PUBLIC_ALIAS(sincos, libc_sincos);
DEFINE_PUBLIC_ALIAS(__exp10, libc_exp10);
DEFINE_PUBLIC_ALIAS(exp10, libc_exp10);
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
#if defined(__LIBCCALL_IS_LIBDCALL) && defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(_finitef, libc_finitef);
#endif /* __LIBCCALL_IS_LIBDCALL && __x86_64__ */
DEFINE_PUBLIC_ALIAS(finitef, libc_finitef);
DEFINE_PUBLIC_ALIAS(__significandf, libc_significandf);
DEFINE_PUBLIC_ALIAS(significandf, libc_significandf);
DEFINE_PUBLIC_ALIAS(__finitel, libc_finitel);
DEFINE_PUBLIC_ALIAS(finitel, libc_finitel);
DEFINE_PUBLIC_ALIAS(__significandl, libc_significandl);
DEFINE_PUBLIC_ALIAS(significandl, libc_significandl);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_isnan, libc_isnan);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__isnan, libc_isnan);
DEFINE_PUBLIC_ALIAS(isnan, libc_isnan);
DEFINE_PUBLIC_ALIAS(__isnanf, libc_isnanf);
#if defined(__LIBCCALL_IS_LIBDCALL) && defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(_isnanf, libc_isnanf);
#endif /* __LIBCCALL_IS_LIBDCALL && __x86_64__ */
DEFINE_PUBLIC_ALIAS(isnanf, libc_isnanf);
DEFINE_PUBLIC_ALIAS(__isnanl, libc_isnanl);
DEFINE_PUBLIC_ALIAS(isnanl, libc_isnanl);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_j0, libc_j0);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__j0, libc_j0);
DEFINE_PUBLIC_ALIAS(j0, libc_j0);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_j1, libc_j1);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__j1, libc_j1);
DEFINE_PUBLIC_ALIAS(j1, libc_j1);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_jn, libc_jn);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__jn, libc_jn);
DEFINE_PUBLIC_ALIAS(jn, libc_jn);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_y0, libc_y0);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__y0, libc_y0);
DEFINE_PUBLIC_ALIAS(y0, libc_y0);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_y1, libc_y1);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__y1, libc_y1);
DEFINE_PUBLIC_ALIAS(y1, libc_y1);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_yn, libc_yn);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__yn, libc_yn);
DEFINE_PUBLIC_ALIAS(yn, libc_yn);
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
DEFINE_PUBLIC_ALIAS(__lgamma_r, libc_lgamma_r);
DEFINE_PUBLIC_ALIAS(lgamma_r, libc_lgamma_r);
DEFINE_PUBLIC_ALIAS(__lgammaf_r, libc_lgammaf_r);
DEFINE_PUBLIC_ALIAS(lgammaf_r, libc_lgammaf_r);
DEFINE_PUBLIC_ALIAS(__lgammal_r, libc_lgammal_r);
DEFINE_PUBLIC_ALIAS(lgammal_r, libc_lgammal_r);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_scalb, libc_scalb);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__scalb, libc_scalb);
DEFINE_PUBLIC_ALIAS(scalb, libc_scalb);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_scalbf, libc_scalbf);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__scalbf, libc_scalbf);
DEFINE_PUBLIC_ALIAS(scalbf, libc_scalbf);
DEFINE_PUBLIC_ALIAS(__scalbl, libc_scalbl);
DEFINE_PUBLIC_ALIAS(scalbl, libc_scalbl);
DEFINE_PUBLIC_ALIAS(DOS$fpclassify, libd___fpclassify);
DEFINE_PUBLIC_ALIAS(DOS$_dclass, libd___fpclassify);
DEFINE_PUBLIC_ALIAS(DOS$__fpclassify, libd___fpclassify);
DEFINE_PUBLIC_ALIAS(fpclassify, libc___fpclassify);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_dclass, libc___fpclassify);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__fpclassify, libc___fpclassify);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_dsign, libc___signbit);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__signbit, libc___signbit);
DEFINE_PUBLIC_ALIAS(DOS$fpclassifyf, libd___fpclassifyf);
DEFINE_PUBLIC_ALIAS(DOS$_fdclass, libd___fpclassifyf);
DEFINE_PUBLIC_ALIAS(DOS$__fpclassifyf, libd___fpclassifyf);
DEFINE_PUBLIC_ALIAS(fpclassifyf, libc___fpclassifyf);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_fdclass, libc___fpclassifyf);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__fpclassifyf, libc___fpclassifyf);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_fdsign, libc___signbitf);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__signbitf, libc___signbitf);
DEFINE_PUBLIC_ALIAS(DOS$fpclassifyl, libd___fpclassifyl);
DEFINE_PUBLIC_ALIAS(DOS$_ldclass, libd___fpclassifyl);
DEFINE_PUBLIC_ALIAS(DOS$__fpclassifyl, libd___fpclassifyl);
DEFINE_PUBLIC_ALIAS(fpclassifyl, libc___fpclassifyl);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_ldclass, libc___fpclassifyl);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__fpclassifyl, libc___fpclassifyl);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_ldsign, libc___signbitl);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__signbitl, libc___signbitl);
DEFINE_PUBLIC_ALIAS(issignaling, libc___issignaling);
DEFINE_PUBLIC_ALIAS(__issignaling, libc___issignaling);
DEFINE_PUBLIC_ALIAS(issignalingf, libc___issignalingf);
DEFINE_PUBLIC_ALIAS(__issignalingf, libc___issignalingf);
DEFINE_PUBLIC_ALIAS(__iscanonicall, libc___iscanonicall);
DEFINE_PUBLIC_ALIAS(issignalingl, libc___issignalingl);
DEFINE_PUBLIC_ALIAS(__issignalingl, libc___issignalingl);
DEFINE_PUBLIC_ALIAS(nextdown, libc_nextdown);
DEFINE_PUBLIC_ALIAS(nextup, libc_nextup);
DEFINE_PUBLIC_ALIAS(nextdownf, libc_nextdownf);
DEFINE_PUBLIC_ALIAS(nextupf, libc_nextupf);
DEFINE_PUBLIC_ALIAS(nextdownl, libc_nextdownl);
DEFINE_PUBLIC_ALIAS(nextupl, libc_nextupl);
DEFINE_PUBLIC_ALIAS(llogb, libc_llogb);
DEFINE_PUBLIC_ALIAS(roundeven, libc_roundeven);
DEFINE_PUBLIC_ALIAS(fmaxmag, libc_fmaxmag);
DEFINE_PUBLIC_ALIAS(fminmag, libc_fminmag);
DEFINE_PUBLIC_ALIAS(canonicalize, libc_canonicalize);
DEFINE_PUBLIC_ALIAS(llogbf, libc_llogbf);
DEFINE_PUBLIC_ALIAS(roundevenf, libc_roundevenf);
DEFINE_PUBLIC_ALIAS(fromfpf, libc_fromfpf);
DEFINE_PUBLIC_ALIAS(ufromfpf, libc_ufromfpf);
DEFINE_PUBLIC_ALIAS(fromfpxf, libc_fromfpxf);
DEFINE_PUBLIC_ALIAS(ufromfpxf, libc_ufromfpxf);
DEFINE_PUBLIC_ALIAS(fmaxmagf, libc_fmaxmagf);
DEFINE_PUBLIC_ALIAS(fminmagf, libc_fminmagf);
DEFINE_PUBLIC_ALIAS(canonicalizef, libc_canonicalizef);
DEFINE_PUBLIC_ALIAS(llogbl, libc_llogbl);
DEFINE_PUBLIC_ALIAS(roundevenl, libc_roundevenl);
DEFINE_PUBLIC_ALIAS(fromfpl, libc_fromfpl);
DEFINE_PUBLIC_ALIAS(ufromfpl, libc_ufromfpl);
DEFINE_PUBLIC_ALIAS(fromfpxl, libc_fromfpxl);
DEFINE_PUBLIC_ALIAS(ufromfpxl, libc_ufromfpxl);
DEFINE_PUBLIC_ALIAS(fmaxmagl, libc_fmaxmagl);
DEFINE_PUBLIC_ALIAS(fminmagl, libc_fminmagl);
DEFINE_PUBLIC_ALIAS(canonicalizel, libc_canonicalizel);
DEFINE_PUBLIC_ALIAS(_dpcomp, libc__dpcomp);
DEFINE_PUBLIC_ALIAS(_fdpcomp, libc__fdpcomp);
DEFINE_PUBLIC_ALIAS(_ldpcomp, libc__ldpcomp);
DEFINE_PUBLIC_ALIAS(DOS$_dtest, libd__dtest);
DEFINE_PUBLIC_ALIAS(_dtest, libc__dtest);
DEFINE_PUBLIC_ALIAS(DOS$_fdtest, libd__fdtest);
DEFINE_PUBLIC_ALIAS(_fdtest, libc__fdtest);
DEFINE_PUBLIC_ALIAS(DOS$_ldtest, libd__ldtest);
DEFINE_PUBLIC_ALIAS(_ldtest, libc__ldtest);
DEFINE_PUBLIC_ALIAS(_chgsignf, libc__chgsignf);
DEFINE_PUBLIC_ALIAS(_chgsign, libc__chgsign);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_MATH_C */
