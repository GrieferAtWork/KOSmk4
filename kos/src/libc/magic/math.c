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

%[define_ccompat_header("cmath")]
%[default_impl_section(".text.crt.math.math")]

%[define_double_replacement(__LIBM_MATHFUN = __LIBM_MATHFUNF, __LIBM_MATHFUNL)]
%[define_double_replacement(__LIBM_MATHFUNI = __LIBM_MATHFUNIF, __LIBM_MATHFUNIL)]
%[define_double_replacement(__LIBM_MATHFUN2 = __LIBM_MATHFUN2F, __LIBM_MATHFUN2L)]
%[define_double_replacement(__LIBM_MATHFUNI2 = __LIBM_MATHFUNI2F, __LIBM_MATHFUNI2L)]
%[define_double_replacement(__LIBM_MATHFUN1I = __LIBM_MATHFUN1IF, __LIBM_MATHFUN1IL)]
%[define_double_replacement(__LIBM_MATHFUN0 = __LIBM_MATHFUN0F, __LIBM_MATHFUN0L)]
%[define_double_replacement(__kernel_standard = __kernel_standard_f, __kernel_standard_l)]
%[define_double2float_replacement(__IEEE754_FLOAT_TYPE_IS_DOUBLE__ = __IEEE754_FLOAT_TYPE_IS_FLOAT__)]
%[define_double2float_replacement(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ = __IEEE754_DOUBLE_TYPE_IS_FLOAT__)]
%[define_double2float_replacement(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ = __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)]
%[define_double2ldouble_replacement(__IEEE754_FLOAT_TYPE_IS_DOUBLE__ = __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)]
%[define_double2ldouble_replacement(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ = __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)]
%[define_double2ldouble_replacement(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ = __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)]


%(c, ccompat)#ifndef __NO_FPU
%{
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/huge_val.h>
#include <bits/math-vector.h>

#include <ieee754.h>

#ifdef __USE_ISOC99
#include <bits/huge_valf.h>
#include <bits/huge_vall.h>
#include <bits/inf.h>
#include <bits/nan.h>
#endif /* __USE_ISOC99 */

#include <bits/mathdef.h>

/* Documentation comments have been taken from GLIBc */
/* Declarations for math functions.
   Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

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


__SYSDECL_BEGIN

/* Some useful constants. */
#if defined(__USE_MISC) || defined(__USE_XOPEN)
#define M_E        2.7182818284590452354  /* e */
#define M_LOG2E    1.4426950408889634074  /* log_2 e */
#define M_LOG10E   0.43429448190325182765 /* log_10 e */
#define M_LN2      0.69314718055994530942 /* log_e 2 */
#define M_LN10     2.30258509299404568402 /* log_e 10 */
#define M_PI       3.14159265358979323846 /* pi */
#define M_PI_2     1.57079632679489661923 /* pi/2 */
#define M_PI_4     0.78539816339744830962 /* pi/4 */
#define M_1_PI     0.31830988618379067154 /* 1/pi */
#define M_2_PI     0.63661977236758134308 /* 2/pi */
#define M_2_SQRTPI 1.12837916709551257390 /* 2/sqrt(pi) */
#define M_SQRT2    1.41421356237309504880 /* sqrt(2) */
#define M_SQRT1_2  0.70710678118654752440 /* 1/sqrt(2) */
#endif /* __USE_MISC || __USE_XOPEN */

/* The above constants are not adequate for computation using `long double's.
 * Therefore we provide as an extension constants with similar names as a
 * GNU extension.  Provide enough digits for the 128-bit IEEE quad. */
#if defined(__USE_GNU) && defined(__COMPILER_HAVE_LONGDOUBLE)
#define M_El        2.718281828459045235360287471352662498L /* e */
#define M_LOG2El    1.442695040888963407359924681001892137L /* log_2 e */
#define M_LOG10El   0.434294481903251827651128918916605082L /* log_10 e */
#define M_LN2l      0.693147180559945309417232121458176568L /* log_e 2 */
#define M_LN10l     2.302585092994045684017991454684364208L /* log_e 10 */
#define M_PIl       3.141592653589793238462643383279502884L /* pi */
#define M_PI_2l     1.570796326794896619231321691639751442L /* pi/2 */
#define M_PI_4l     0.785398163397448309615660845819875721L /* pi/4 */
#define M_1_PIl     0.318309886183790671537767526745028724L /* 1/pi */
#define M_2_PIl     0.636619772367581343075535053490057448L /* 2/pi */
#define M_2_SQRTPIl 1.128379167095512573896158903121545172L /* 2/sqrt(pi) */
#define M_SQRT2l    1.414213562373095048801688724209698079L /* sqrt(2) */
#define M_SQRT1_2l  0.707106781186547524400844362104849039L /* 1/sqrt(2) */
#endif /* __USE_GNU && __COMPILER_HAVE_LONGDOUBLE */


#ifdef __CC__
}

%[insert:std]

@@Arc cosine of X
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__acos)][nothrow][crtbuiltin]
acos:(double x) -> double; /* TODO */

@@Arc sine of X
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__asin)][nothrow][crtbuiltin]
asin:(double x) -> double; /* TODO */

@@Arc tangent of X
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__atan)][nothrow][crtbuiltin]
[impl_include("<libm/fcomp.h>")][impl_include("<libm/fabs.h>")]
[impl_include("<libm/matherr.h>")][impl_include("<libm/inf.h>")]
[requires_include("<ieee754.h>")][impl_include("<libm/atan.h>")]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
atan:(double x) -> double {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2(@isgreaterequal@, __LIBM_MATHFUN(@fabs@, x), 1.0)) {
		return __kernel_standard(x, x, __LIBM_MATHFUN0(@inf@),
		                         __LIBM_MATHFUN(@fabs@, x) > 1.0
		                         ? __LIBM_KMATHERR_ATANH_PLUSONE /* atanh(|x|>1) */
		                         : __LIBM_KMATHERR_ATANH_ONE);   /* atanh(|x|==1) */
	}
	return __LIBM_MATHFUN(@atan@, x);
}

@@Arc tangent of Y/X
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__atan2)][nothrow][crtbuiltin]
[impl_include("<bits/huge_val.h>")][impl_include("<libm/matherr.h>")]
[requires_include("<ieee754.h>")][impl_include("<libm/atan2.h>")]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
atan2:(double y, double x) -> double {
	if (__LIBM_LIB_VERSION == __LIBM_SVID && x == 0.0 && y == 0.0)
		return __kernel_standard(y, x, @HUGE_VAL@, __LIBM_KMATHERR_ATAN2); /* atan2(+-0,+-0) */
	return __LIBM_MATHFUN2(@atan2@, y, x);
}

@@Cosine of X
[attribute("__DECL_SIMD_cos")][decl_include("<bits/math-vector.h>")]
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__cos)][nothrow][crtbuiltin]
cos:(double x) -> double; /* TODO */

@@Sine of X
[attribute("__DECL_SIMD_sin")][decl_include("<bits/math-vector.h>")]
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__sin)][nothrow][crtbuiltin]
sin:(double x) -> double; /* TODO */

@@Tangent of X
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__tan)][nothrow][crtbuiltin]
tan:(double x) -> double; /* TODO */



[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__acosf)][nothrow][crtbuiltin]
acosf:(float x) -> float; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__asinf)][nothrow][crtbuiltin]
asinf:(float x) -> float; /* TODO */

[std][[ATTR_WUNUSED, ATTR_CONST]][export_alias(__atanf)][nothrow][crtbuiltin]
atanf:(float x) -> float %{generate(double2float)}

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__atan2f)][nothrow][crtbuiltin]
atan2f:(float y, float x) -> float %{generate(double2float)}

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__cosf)][nothrow][crtbuiltin]
cosf:(float x) -> float; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__sinf)][nothrow][crtbuiltin]
sinf:(float x) -> float; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__tanf)][nothrow][crtbuiltin]
tanf:(float x) -> float; /* TODO */



%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__acosl)][nothrow][crtbuiltin]
acosl:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__asinl)][nothrow][crtbuiltin]
asinl:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */

[std][[ATTR_WUNUSED, ATTR_CONST]][export_alias(__atanl)][nothrow][crtbuiltin]
atanl:(__LONGDOUBLE x) -> __LONGDOUBLE %{generate(double2ldouble)}

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__atan2l)][nothrow][crtbuiltin]
atan2l:(__LONGDOUBLE y, __LONGDOUBLE x) -> __LONGDOUBLE %{generate(double2ldouble)}

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__cosl)][nothrow][crtbuiltin]
cosl:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__sinl)][nothrow][crtbuiltin]
sinl:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__tanl)][nothrow][crtbuiltin]
tanl:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */

%(std, c)
%(std, c)/* Hyperbolic functions. */

@@Hyperbolic cosine of X
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__cosh)][nothrow][crtbuiltin]
cosh:(double x) -> double; /* TODO */

@@Hyperbolic sine of X
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__sinh)][nothrow][crtbuiltin]
sinh:(double x) -> double; /* TODO */

@@Hyperbolic tangent of X
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__tanh)][nothrow][crtbuiltin]
tanh:(double x) -> double; /* TODO */


[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__coshf)][nothrow][crtbuiltin]
coshf:(float x) -> float; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__sinhf)][nothrow][crtbuiltin]
sinhf:(float x) -> float; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__tanhf)][nothrow][crtbuiltin]
tanhf:(float x) -> float; /* TODO */


%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__coshl)][nothrow][crtbuiltin]
coshl:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__sinhl)][nothrow][crtbuiltin]
sinhl:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__tanhl)][nothrow][crtbuiltin]
tanhl:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */


%(std, c)
%(std, c, ccompat)#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
@@Hyperbolic arc cosine of X
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__acosh)][nothrow][crtbuiltin]
acosh:(double x) -> double; /* TODO */

@@Hyperbolic arc sine of X
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__asinh)][nothrow][crtbuiltin]
asinh:(double x) -> double; /* TODO */

@@Hyperbolic arc tangent of X
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__atanh)][nothrow][crtbuiltin]
atanh:(double x) -> double; /* TODO */


[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__acoshf)][nothrow][crtbuiltin]
acoshf:(float x) -> float; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__asinhf)][nothrow][crtbuiltin]
asinhf:(float x) -> float; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__atanhf)][nothrow][crtbuiltin]
atanhf:(float x) -> float; /* TODO */


%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__acoshl)][nothrow][crtbuiltin]
acoshl:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__asinhl)][nothrow][crtbuiltin]
asinhl:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__atanhl)][nothrow][crtbuiltin]
atanhl:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

%(std, c)
%(std, c)/* Exponential and logarithmic functions. */

@@Exponential function of X
[attribute("__DECL_SIMD_exp")][decl_include("<bits/math-vector.h>")]
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__exp)][nothrow][crtbuiltin]
[impl_include("<libm/signbit.h>")]
[impl_include("<libm/matherr.h>")][impl_include(<libm/finite.h>)]
[requires_include("<ieee754.h>")][impl_include(<libm/exp.h>)]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
exp:(double x) -> double {
	double result;
	result = __LIBM_MATHFUN(@exp@, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (!__LIBM_MATHFUN(@finite@, result) || result == 0.0) &&
	    __LIBM_MATHFUN(@finite@, x)) {
		return __kernel_standard(x, x, result,
		                         __LIBM_MATHFUN(@signbit@, x)
		                         ? __LIBM_KMATHERR_EXP_UNDERFLOW
		                         : __LIBM_KMATHERR_EXP_OVERFLOW);
	}
	return result;
}

@@Break VALUE into a normalized fraction and an integral power of 2
[std][[ATTR_WUNUSED]][export_alias(__frexp)][crtbuiltin]
[requires_include("<ieee754.h>")][impl_include(<libm/frexp.h>)]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
frexp:(double x, [[nonnull]] int *pexponent) -> double {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_frexp((__IEEE754_DOUBLE_TYPE__)x, pexponent);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (double)__ieee754_frexpf((__IEEE754_FLOAT_TYPE__)x, pexponent);
#else /* ... */
	return (double)__ieee854_frexpl((__IEEE854_LONG_DOUBLE_TYPE__)x, pexponent);
#endif /* !... */
}

@@X times (two to the EXP power)
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__ldexp)][nothrow][crtbuiltin]
[impl_include("<parts/errno.h>")][impl_include(<libm/finite.h>)]
[requires_include("<ieee754.h>")][impl_include(<libm/ldexp.h>)]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
ldexp:(double x, int exponent) -> double {
	double result;
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	result = (double)__ieee754_ldexp((__IEEE754_DOUBLE_TYPE__)x, exponent);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	result = (double)__ieee754_ldexpf((__IEEE754_FLOAT_TYPE__)x, exponent);
#else /* ... */
	result = (double)__ieee854_ldexpl((__IEEE854_LONG_DOUBLE_TYPE__)x, exponent);
#endif /* !... */
#ifdef ERANGE
	if unlikely(!__LIBM_MATHFUN(@finite@, result) || result == 0.0)
		__libc_seterrno(ERANGE);
#endif /* ERANGE */
	return result;
}

@@Natural logarithm of X
[attribute("__DECL_SIMD_log")][decl_include("<bits/math-vector.h>")]
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__log)][nothrow][crtbuiltin]
log:(double x) -> double; /* TODO */

@@Base-ten logarithm of X
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__log10)][nothrow][crtbuiltin]
log10:(double x) -> double; /* TODO */

@@Break VALUE into integral and fractional parts
[std][[ATTR_WUNUSED]][export_alias(__modf)][crtbuiltin]
[requires_include("<ieee754.h>")][impl_include(<libm/modf.h>)]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
modf:(double x, [[nonnull]] double *iptr) -> double {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_modf((__IEEE754_DOUBLE_TYPE__)x, (__IEEE754_DOUBLE_TYPE__ *)iptr);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (double)__ieee754_modff((__IEEE754_FLOAT_TYPE__)x, (__IEEE754_FLOAT_TYPE__ *)iptr);
#else /* ... */
	return (double)__ieee854_modfl((__IEEE854_LONG_DOUBLE_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__ *)iptr);
#endif /* !... */
}


[attribute("__DECL_SIMD_expf")][decl_include("<bits/math-vector.h>")]
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__expf)][nothrow][crtbuiltin]
expf:(float x) -> float %{generate(double2float)}

[std][[ATTR_WUNUSED]][export_alias(__frexpf)][crtbuiltin]
frexpf:(float x, [[nonnull]] int *pexponent) -> float %{generate(double2float)}

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__ldexpf)][nothrow][crtbuiltin]
ldexpf:(float x, int exponent) -> float %{generate(double2float)}

[attribute("__DECL_SIMD_logf")][decl_include("<bits/math-vector.h>")]
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__logf)][nothrow][crtbuiltin]
logf:(float x) -> float; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__log10f)][nothrow][crtbuiltin]
log10f:(float x) -> float; /* TODO */

[std][export_alias(__modff)][crtbuiltin]
modff:(float x, [[nonnull]] float *iptr) -> float %{generate(double2float)}


%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute("__DECL_SIMD_expl")][decl_include("<bits/math-vector.h>")]
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__expl)][nothrow][crtbuiltin]
expl:(__LONGDOUBLE x) -> __LONGDOUBLE %{generate(double2ldouble)}

[std][[ATTR_WUNUSED]][export_alias(__frexpl)][crtbuiltin]
frexpl:(__LONGDOUBLE x, [[nonnull]] int *pexponent) -> __LONGDOUBLE %{generate(double2ldouble)}

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__ldexpl)][nothrow][crtbuiltin]
ldexpl:(__LONGDOUBLE x, int exponent) -> __LONGDOUBLE %{generate(double2ldouble)}

[attribute("__DECL_SIMD_logl")][decl_include("<bits/math-vector.h>")]
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__logl)][nothrow][crtbuiltin]
logl:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__log10l)][nothrow][crtbuiltin]
log10l:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */

[std][export_alias(__modfl)][crtbuiltin]
modfl:(__LONGDOUBLE x, [[nonnull]] __LONGDOUBLE *iptr) -> __LONGDOUBLE %{generate(double2ldouble)}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */


%(std, c)
%(std, c, ccompat)#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
@@Return exp(X) - 1
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__expm1)][nothrow][crtbuiltin]
[impl_include("<libm/matherr.h>")][impl_include("<libm/signbit.h>")]
[impl_include(<libm/finite.h>)]
[requires_include("<ieee754.h>")][impl_include(<libm/expm1.h>)]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
expm1:(double x) -> double {
	double result;
	result = __LIBM_MATHFUN(@expm1@, x);
	if ((!__LIBM_MATHFUN(@finite@, result) || result == -1.0) &&
	    __LIBM_MATHFUN(@finite @, x) && __LIBM_LIB_VERSION != __LIBM_IEEE) {
		return __kernel_standard(x, x, result,
		                         __LIBM_MATHFUN(@signbit@, x)
		                         ? __LIBM_KMATHERRL_EXPM1_UNDERFLOW
		                         : __LIBM_KMATHERRL_EXPM1_OVERFLOW);
	}
	return result;
}

@@Return log(1 + X)
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__log1p)][nothrow][crtbuiltin]
log1p:(double x) -> double; /* TODO */

@@Return the base 2 signed integral exponent of X
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__logb, _logb)][nothrow][crtbuiltin]
logb:(double x) -> double; /* TODO */


[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__expm1f)][nothrow][crtbuiltin]
expm1f:(float x) -> float %{generate(double2float)}

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__log1pf)][nothrow][crtbuiltin]
log1pf:(float x) -> float; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__logbf)][nothrow][crtbuiltin]
logbf:(float x) -> float; /* TODO */


%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__expm1l)][nothrow][crtbuiltin]
expm1l:(__LONGDOUBLE x) -> __LONGDOUBLE %{generate(double2ldouble)}

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__log1pl)][nothrow][crtbuiltin]
log1pl:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__logbl)][nothrow][crtbuiltin]
logbl:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

%(std, c)
%(std, c, ccompat)#ifdef __USE_ISOC99
@@Compute base-2 exponential of X
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__exp2)][nothrow][crtbuiltin]
exp2:(double x) -> double; /* TODO */

@@Compute base-2 logarithm of X
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__log2)][nothrow][crtbuiltin]
log2:(double x) -> double; /* TODO */


[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__exp2f)][nothrow][crtbuiltin]
exp2f:(float x) -> float; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__log2f)][nothrow][crtbuiltin]
log2f:(float x) -> float; /* TODO */


%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__exp2l)][nothrow][crtbuiltin]
exp2l:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__log2l)][nothrow][crtbuiltin]
log2l:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_ISOC99 */

%(std, c)
%(std, c)/* Power functions. */

@@Return X to the Y power
[attribute("__DECL_SIMD_pow")][decl_include("<bits/math-vector.h>")]
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__pow)][nothrow][crtbuiltin]
[impl_include(<libm/finite.h>)][impl_include("<libm/isnan.h>")]
[impl_include("<libm/matherr.h>")]
[requires_include("<ieee754.h>")][impl_include(<libm/pow.h>)]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
pow:(double x, double y) -> double {
	double result;
	result = __LIBM_MATHFUN2(@pow@, x, y);
	/*
	 * ====================================================
	 * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Permission to use, copy, modify, and distribute this
	 * software is freely granted, provided that this notice 
	 * is preserved.
	 * ====================================================
	 */
	if (!__LIBM_MATHFUNI(@finite@, result)) {
		if (__LIBM_MATHFUNI(@isnan@, y) && x == 1.0) {
			result = 1.0;
		} else if (__LIBM_LIB_VERSION != __LIBM_IEEE) {
			if (__LIBM_MATHFUNI(@isnan@, x)) {
				if (y == 0.0) /* pow(NaN,0.0) */
					return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_NAN);
			} else if (__LIBM_MATHFUNI(@finite@, x) && __LIBM_MATHFUNI(@finite@, y)) {
				if (__LIBM_MATHFUNI(@isnan@, result)) { /* pow neg**non-int */
					return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_NONINT);
				} else if (x == 0.0 && y < 0.0) {
					if (__LIBM_MATHFUNI(@signbit@, x) && __LIBM_MATHFUNI(@signbit@, result)) { /* pow(-0.0,negative) */
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
	           __LIBM_MATHFUNI(@finite@, x) &&
	           __LIBM_MATHFUNI(@finite@, y) &&
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


@@Return the square root of X
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__sqrt)][nothrow][crtbuiltin]
[impl_include("<libm/fcomp.h>")][impl_include("<libm/nan.h>")]
[impl_include("<libm/matherr.h>")]
[requires_include("<ieee754.h>")][impl_include("<libm/sqrt.h>")]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
sqrt:(double x) -> double {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2(@isless@, x, 0.0))
		return __kernel_standard(x, x, __LIBM_MATHFUN1I(@nan@, ""), __LIBM_KMATHERR_SQRT); /* sqrt(negative) */
	return __LIBM_MATHFUN(@sqrt@, x);
}

[attribute("__DECL_SIMD_powf")][decl_include("<bits/math-vector.h>")]
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__powf)][nothrow][crtbuiltin]
powf:(float x, float y) -> float %{generate(double2float)}

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__sqrtf)][nothrow][crtbuiltin]
sqrtf:(float x) -> float %{generate(double2float)}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute("__DECL_SIMD_powl")][decl_include("<bits/math-vector.h>")]
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__powl)][nothrow][crtbuiltin]
powl:(__LONGDOUBLE x, __LONGDOUBLE y) -> __LONGDOUBLE %{generate(double2ldouble)}

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__sqrtl)][nothrow][crtbuiltin]
sqrtl:(__LONGDOUBLE x) -> __LONGDOUBLE %{generate(double2ldouble)}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */


%(std, c)
%(std, c, ccompat)#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
@@Return `sqrt(X*X + Y*Y)'
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__hypot)][nothrow][crtbuiltin]
hypot:(double x, double y) -> double; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__hypotf)][nothrow][crtbuiltin]
hypotf:(float x, float y) -> float;

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][[ATTR_WUNUSED]][ATTR_MCONST][export_alias(__hypotl)][nothrow][crtbuiltin]
hypotl:(__LONGDOUBLE x, __LONGDOUBLE y) -> __LONGDOUBLE;
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN || __USE_ISOC99 */


%(std, c)
%(std, c, ccompat)#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
@@Return the cube root of X
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__cbrt)][crtbuiltin]
[requires_include("<ieee754.h>")][impl_include(<libm/cbrt.h>)]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
cbrt:(double x) -> double {
	return __LIBM_MATHFUN(@cbrt@, x);
}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__cbrtf)][crtbuiltin]
cbrtf:(float x) -> float %{generate(double2float)}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__cbrtl)][crtbuiltin]
cbrtl:(__LONGDOUBLE x) -> __LONGDOUBLE %{generate(double2ldouble)}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

%(std, c)
%(std, c)/* Nearest integer, absolute value, and remainder functions. */

@@Smallest integral value not less than X
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__ceil)]
[impl_include(<hybrid/typecore.h>)][crtbuiltin]
[impl_include(<libm/ceil.h>)]
ceil:(double x) -> double {
#ifdef __LIBM_MATHFUN
	return __LIBM_MATHFUN(@ceil@, x);
#else /* __LIBM_MATHFUN */
	double result;
	result = (double)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result < x)
		result += 1.0;
	return result;
#endif /* !__LIBM_MATHFUN */
}

@@Absolute value of X
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__fabs)][crtbuiltin]
[impl_include("<libm/fabs.h>")]
fabs:(double x) -> double {
#ifdef __LIBM_MATHFUN
	return __LIBM_MATHFUN(@fabs@, x);
#else /* __LIBM_MATHFUN */
	return x < 0.0 ? -x : x;
#endif /* !__LIBM_MATHFUN */
}

@@Largest integer not greater than X
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__floor)]
[impl_include(<hybrid/typecore.h>)][crtbuiltin]
[impl_include(<libm/floor.h>)]
floor:(double x) -> double {
#ifdef __LIBM_MATHFUN
	return __LIBM_MATHFUN(@floor@, x);
#else /* __LIBM_MATHFUN */
	double result;
	result = (double)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result > x)
		result -= 1.0;
	return result;
#endif /* !__LIBM_MATHFUN */
}


@@Floating-point modulo remainder of X/Y
[std][[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__fmod)][crtbuiltin]
[impl_include("<libm/isinf.h>")][impl_include("<libm/fcomp.h>")]
[impl_include("<libm/matherr.h>")]
[requires_include("<ieee754.h>")][impl_include(<libm/fmod.h>)]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
fmod:(double x, double y) -> double {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUN(@isinf@, x) || y == 0.0) &&
	    !__LIBM_MATHFUN2(@isunordered@, x, y))
		return __kernel_standard(x, y, y, __LIBM_KMATHERR_FMOD); /* fmod(+-Inf,y) or fmod(x,0) */
	return __LIBM_MATHFUN2(@fmod@, x, y);
}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__ceilf)][crtbuiltin]
ceilf:(float x) -> float %{generate(double2float)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__fabsf)][crtbuiltin]
fabsf:(float x) -> float %{generate(double2float)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__floorf)][crtbuiltin]
floorf:(float x) -> float %{generate(double2float)}

[std][[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__fmodf)][crtbuiltin]
fmodf:(float x, float y) -> float %{generate(double2float)}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__ceill)][crtbuiltin]
ceill:(__LONGDOUBLE x) -> __LONGDOUBLE %{generate(double2ldouble)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__fabsl)][crtbuiltin]
fabsl:(__LONGDOUBLE x) -> __LONGDOUBLE %{generate(double2ldouble)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__floorl)][crtbuiltin]
floorl:(__LONGDOUBLE x) -> __LONGDOUBLE %{generate(double2ldouble)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__fmodl)][crtbuiltin]
fmodl:(__LONGDOUBLE x, __LONGDOUBLE y) -> __LONGDOUBLE %{generate(double2ldouble)}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */


%(std, c)
%(std, c, ccompat)#ifdef __USE_ISOC99
@@Return X with its signed changed to Y's
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__copysign, _copysign)]
[impl_include(<libm/copysign.h>)][crtbuiltin]
copysign:(double num, double sign) -> double {
#ifdef __LIBM_MATHFUN2
	return __LIBM_MATHFUN2(@copysign@, num, sign);
#else /* __LIBM_MATHFUN2 */
	if ((num < 0.0) != (sign < 0.0))
		num = -num;
	return num;
#endif /* !__LIBM_MATHFUN2 */
}

@@Return representation of qNaN for double type
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__nan)][crtbuiltin]
[requires_include("<ieee754.h>")][impl_include("<libm/nan.h>")]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
nan:(char const *tagb) -> double {
	return __LIBM_MATHFUN1I(@nan@, tagb);
}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__copysignf)][crtbuiltin]
copysignf:(float num, float sign) -> float %{generate(double2float)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__nanf)][crtbuiltin]
nanf:(char const *tagb) -> float %{generate(double2float)}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__copysignl)][crtbuiltin]
copysignl:(__LONGDOUBLE num, __LONGDOUBLE sign) -> __LONGDOUBLE %{generate(double2ldouble)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__nanl)][crtbuiltin]
nanl:(char const *tagb) -> __LONGDOUBLE %{generate(double2ldouble)}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_ISOC99 */



%(std, c)
%(std, c)/* Error and gamma functions. */
%(std, c, ccompat)#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
[std][[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__erf)][crtbuiltin]
erf:(double x) -> double; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__erfc)][crtbuiltin]
erfc:(double x) -> double; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][nothrow][crtbuiltin]
[[if(__has_builtin(__builtin_gamma) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline(gamma, { return __builtin_gamma(x); })]]
[export_alias(gamma, __lgamma, __gamma)]
lgamma:(double x) -> double; /* TODO */


[std][[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__erff)][crtbuiltin]
erff:(float x) -> float; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__erfcf)][crtbuiltin]
erfcf:(float x) -> float; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][nothrow][crtbuiltin]
[[if(__has_builtin(__builtin_gammaf) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline(gammaf, { return __builtin_gammaf(x); })]]
[export_alias(gammaf, __lgammaf, __gammaf)]
lgammaf:(float x) -> float; /* TODO */


%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__erfl)][crtbuiltin]
erfl:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__erfcl)][crtbuiltin]
erfcl:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][nothrow][crtbuiltin]
[[if(__has_builtin(__builtin_gammal) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline(gammal, { return __builtin_gammal(x); })]]
[export_alias(gammal, __lgammal, __gammal)]
lgammal:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN || __USE_ISOC99 */

%(std, c, ccompat)#ifdef __USE_ISOC99
@@True gamma function
[std][[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__tgamma)][crtbuiltin]
tgamma:(double x) -> double; /* TODO */

[std][[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__tgammaf)][crtbuiltin]
tgammaf:(float x) -> float; /* TODO */

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__tgammal)][crtbuiltin]
tgammal:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_ISOC99 */

%(std, c)
%(std, c, ccompat)#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)

@@Return the integer nearest X in the direction of the prevailing rounding mode
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][crtbuiltin]
[[if(__has_builtin(__builtin_nearbyint) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline(nearbyint, { return __builtin_nearbyint(x); })]]
[export_alias(nearbyint, __rint, __nearbyint)]
[requires_include("<ieee754.h>")][impl_include("<libm/rint.h>")]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
rint:(double x) -> double {
	return __LIBM_MATHFUN(@rint@, x);
}


@@Return X + epsilon if X < Y, X - epsilon if X > Y
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][crtbuiltin]
[[if(__has_builtin(__builtin_nexttoward) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline(nexttoward, { return __builtin_nexttoward(x); })]]
[export_alias(nexttoward, __nextafter, _nextafter, __nexttoward)]
[requires_include("<ieee754.h>")][impl_include("<libm/nextafter.h>")]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
nextafter:(double x, double y) -> double {
	return __LIBM_MATHFUN2(@nextafter@, x, y);
}

@@Return the remainder of integer division X/P with infinite precision
[std][[ATTR_WUNUSED]][ATTR_MCONST][nothrow][crtbuiltin]
[[if(__has_builtin(__builtin_drem) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline(drem, { return __builtin_drem(x, p); })]]
[export_alias(drem, __remainder, __drem)]
[impl_include("<libm/matherr.h>")][crtbuiltin]
[impl_include("<libm/isnan.h>")][impl_include("<libm/isinf.h>")]
[requires_include("<ieee754.h>")][impl_include("<libm/remainder.h>")]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
remainder:(double x, double p) -> double {
	if (((p == 0.0 && !__LIBM_MATHFUN(@isnan@, x)) ||
	     (__LIBM_MATHFUN(@isinf@, x) && !__LIBM_MATHFUN(@isnan@, p))) &&
	    __LIBM_LIB_VERSION != __LIBM_IEEE)
		return __kernel_standard(x, p, p, __LIBM_KMATHERR_REMAINDER); /* remainder domain */
	return __LIBM_MATHFUN2(@remainder@, x, p);
}

@@Return the binary exponent of X, which must be nonzero
[std][[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__ilogb)][crtbuiltin]
[impl_include(<libm/ilogb.h>)][impl_include("<libm/matherr.h>")]
[requires_include("<ieee754.h>")]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__))]
ilogb:(double x) -> int {
	int result;
	result = __LIBM_MATHFUNI(@ilogb@, x);
	if (result == __LIBM_FP_ILOGB0 || result == __LIBM_FP_ILOGBNAN || result == INT_MAX)
		__kernel_standard(x, x, x, __LIBM_KMATHERRF_ILOGB);
	return result;
}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][crtbuiltin]
[[if(__has_builtin(__builtin_nearbyintf) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline(nearbyintf, { return __builtin_nearbyintf(x); })]]
[export_alias(nearbyintf, __rintf, __nearbyintf)]
rintf:(float x) -> float %{generate(double2float)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][crtbuiltin]
[[if(__has_builtin(__builtin_nexttowardf) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline(nexttowardf, { return __builtin_nexttowardf(x); })]]
[export_alias(nexttowardf, __nextafterf, __nexttowardf)]
nextafterf:(float x, float y) -> float %{generate(double2float)}

[std][[ATTR_WUNUSED]][ATTR_MCONST][nothrow][crtbuiltin]
[[if(__has_builtin(__builtin_dremf) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline(dremf, { return __builtin_dremf(x, p); })]]
[export_alias(dremf, __remainderf, __dremf)]
remainderf:(float x, float p) -> float %{generate(double2float)}

[std][[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__ilogbf)][crtbuiltin]
ilogbf:(float x) -> int %{generate(double2float)}


%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][crtbuiltin]
[[if(__has_builtin(__builtin_nearbyintl) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline(nearbyintl, { return __builtin_nearbyintl(x); })]]
[export_alias(nearbyintl, __rintl, __nearbyintl)]
rintl:(__LONGDOUBLE x) -> __LONGDOUBLE %{generate(double2ldouble)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][crtbuiltin]
[[if(__has_builtin(__builtin_nexttowardl) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline(nexttowardl, { return __builtin_nexttowardl(x); })]]
[export_alias(nexttowardl, __nextafterl, __nexttowardl)]
nextafterl:(__LONGDOUBLE x, __LONGDOUBLE y) -> __LONGDOUBLE %{generate(double2ldouble)}

[std][[ATTR_WUNUSED]][ATTR_MCONST][nothrow][crtbuiltin]
[[if(__has_builtin(__builtin_dreml) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline(dreml, { return __builtin_dreml(x, p); })]]
[export_alias(dreml, __remainderl, __dreml)]
remainderl:(__LONGDOUBLE x, __LONGDOUBLE p) -> __LONGDOUBLE %{generate(double2ldouble)}

[std][[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__ilogbl)][crtbuiltin]
ilogbl:(__LONGDOUBLE x) -> int %{generate(double2ldouble)}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */



%(std, c)
%(std, c, ccompat)#ifdef __USE_ISOC99

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__nexttoward)][crtbuiltin]
[requires_include("<ieee754.h>")][impl_include(<libm/nexttoward.h>)]
[requires(((defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
            defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)) &&
           defined(__IEEE854_LONG_DOUBLE_TYPE__)) ||
           $has_function(nextafterl))]
nexttoward:(double x, __LONGDOUBLE y) -> double {
#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_nexttoward((__IEEE754_DOUBLE_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__)y);
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
	return (double)__ieee754_nexttowardf((__IEEE754_FLOAT_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__)y);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
#else /* __IEEE854_LONG_DOUBLE_TYPE__ */
	return (double)nextafterl((__LONGDOUBLE)x, y);
#endif /* !__IEEE854_LONG_DOUBLE_TYPE__ */
}

@@Return X times (2 to the Nth power)
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__scalbn)][crtbuiltin]
[if(__SIZEOF_INT__ == __SIZEOF_LONG__), export_alias(scalbln, __scalbln)]
[requires_include("<ieee754.h>")][impl_include(<libm/scalbn.h>)]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
scalbn:(double x, int n) -> double {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_scalbn((__IEEE754_DOUBLE_TYPE__)x, n);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (double)__ieee754_scalbnf((__IEEE754_FLOAT_TYPE__)x, n);
#else /* ... */
	return (double)__ieee854_scalbnl((__IEEE854_LONG_DOUBLE_TYPE__)x, n);
#endif /* !... */
}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__scalbln)][crtbuiltin]
[alt_variant_of(__SIZEOF_INT__ == __SIZEOF_LONG__, scalbn)][doc_alias(scalbn)]
[if(__SIZEOF_INT__ == __SIZEOF_LONG__), export_alias(__scalbn)]
[requires_include("<ieee754.h>")][impl_include(<libm/scalbn.h>)]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
scalbln:(double x, long int n) -> double {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_scalbln((__IEEE754_DOUBLE_TYPE__)x, n);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (double)__ieee754_scalblnf((__IEEE754_FLOAT_TYPE__)x, n);
#else /* ... */
	return (double)__ieee854_scalblnl((__IEEE854_LONG_DOUBLE_TYPE__)x, n);
#endif /* !... */
}

nearbyint(*) = rint;

@@Round X to nearest integral value, rounding halfway cases away from zero
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__round)]
[impl_include(<hybrid/typecore.h>)][crtbuiltin]
[impl_include(<libm/round.h>)]
round:(double x) -> double {
#ifdef __LIBM_MATHFUN
	return (double)__LIBM_MATHFUN(@round@, x);
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

@@Round X to the integral value in floating-point
@@format nearest but not larger in magnitude
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__trunc)]
[impl_include(<hybrid/typecore.h>)][crtbuiltin]
[impl_include(<libm/trunc.h>)]
trunc:(double x) -> double {
#ifdef __LIBM_MATHFUN
	return __LIBM_MATHFUN(@trunc@, x);
#else /* __LIBM_MATHFUN */
	return (double)(__INTMAX_TYPE__)x;
#endif /* !__LIBM_MATHFUN */
}

@@Compute remainder of X and Y and put in *QUO a value with sign
@@of x/y and magnitude congruent `mod 2^n' to the magnitude of
@@the integral quotient x/y, with n >= 3
[std][[ATTR_WUNUSED]][nothrow][export_alias(__remquo)][crtbuiltin]
remquo:(double x, double y, int *pquo) -> double; /* TODO */

@@Round X to nearest integral value according to current rounding direction
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__lrint)]
[impl_include(<hybrid/typecore.h>)][crtbuiltin]
[impl_include(<libm/lrint.h>)]
[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), export_alias(llrint)]
lrint:(double x) -> long int {
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(@lrint@, x);
#else /* __LIBM_MATHFUNI */
	return (long int)rint(x);
#endif /* !__LIBM_MATHFUNI */
}

@@Round X to nearest integral value, rounding halfway cases away from zero
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__lround)]
[impl_include(<hybrid/typecore.h>)][crtbuiltin]
[impl_include(<libm/lround.h>)]
[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), export_alias(llround)]
lround:(double x) -> long int {
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(@lround@, x);
#else /* __LIBM_MATHFUNI */
	return (long int)round(x);
#endif /* !__LIBM_MATHFUNI */
}

@@Return positive difference between X and Y
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__fdim)][crtbuiltin]
fdim:(double x, double y) -> double {
	/* TODO: ieee754-specific function */
	return fabs(y - x);
}

@@Return maximum numeric value from X and Y
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__fmax)][crtbuiltin]
fmax:(double x, double y) -> double {
	/* TODO: ieee754-specific function */
	return x < y ? y : x;
}

@@Return minimum numeric value from X and Y
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__fmin)][crtbuiltin]
fmin:(double x, double y) -> double {
	/* TODO: ieee754-specific function */
	return x < y ? x : y;
}

@@Multiply-add function computed as a ternary operation
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__fma)][crtbuiltin]
fma:(double x, double y, double z) -> double {
	/* TODO: ieee754-specific function */
	return (x * y) + z;
}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGLONG
@@Round X to nearest integral value according to current rounding direction
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__llrint)]
[impl_include(<hybrid/typecore.h>)][crtbuiltin]
[impl_include(<libm/lrint.h>)]
[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__, lrint)]
llrint:(double x) -> __LONGLONG {
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(@llrint@, x);
#else /* __LIBM_MATHFUNI */
	return (__LONGLONG)rint(x);
#endif /* !__LIBM_MATHFUNI */
}

@@Round X to nearest integral value, rounding halfway cases away from zero
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__llround)]
[impl_include(<hybrid/typecore.h>)][crtbuiltin]
[impl_include(<libm/lround.h>)]
[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__, lround)]
llround:(double x) -> __LONGLONG {
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(@llround@, x);
#else /* __LIBM_MATHFUNI */
	return (__LONGLONG)round(x);
#endif /* !__LIBM_MATHFUNI */
}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGLONG */

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__nexttowardf)][crtbuiltin]
[requires_include("<ieee754.h>")][impl_include(<libm/nexttoward.h>)]
[requires(((defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) ||
            defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)) &&
           defined(__IEEE854_LONG_DOUBLE_TYPE__)) ||
           $has_function(nextafterl))]
nexttowardf:(float x, __LONGDOUBLE y) -> float {
#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (float)__ieee754_nexttowardf((__IEEE754_FLOAT_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__)y);
#else /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ */
	return (float)__ieee754_nexttoward((__IEEE754_DOUBLE_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__)y);
#endif /* !__IEEE754_FLOAT_TYPE_IS_FLOAT__ */
#else /* __IEEE854_LONG_DOUBLE_TYPE__ */
	return (float)nextafterl((__LONGDOUBLE)x, y);
#endif /* !__IEEE854_LONG_DOUBLE_TYPE__ */
}



[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__scalbnf)][crtbuiltin]
[if(__SIZEOF_INT__ == __SIZEOF_LONG__), export_alias(scalblnf, __scalblnf)]
scalbnf:(float x, int n) -> float %{generate(double2float)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__scalblnf)][crtbuiltin]
[alt_variant_of(__SIZEOF_INT__ == __SIZEOF_LONG__, scalbnf)]
[if(__SIZEOF_INT__ == __SIZEOF_LONG__), export_alias(__scalbnf)]
scalblnf:(float x, long int n) -> float %{generate(double2float)}

nearbyintf(*) = rintf;

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__roundf)][crtbuiltin]
roundf:(float x) -> float %{generate(double2float)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__truncf)][crtbuiltin]
truncf:(float x) -> float %{generate(double2float)}

[std][[ATTR_WUNUSED]][nothrow][export_alias(__remquof)][crtbuiltin]
remquof:(float x, float y, int *pquo) -> float; /* TODO */

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__lrintf)][crtbuiltin]
[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), export_alias(llrintf)]
lrintf:(float x) -> long int %{generate(double2float)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__lroundf)][crtbuiltin]
[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), export_alias(llroundf)]
lroundf:(float x) -> long int %{generate(double2float)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__fdimf)][crtbuiltin]
fdimf:(float x, float y) -> float %{generate(double2float)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__fmaxf)][crtbuiltin]
fmaxf:(float x, float y) -> float %{generate(double2float)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__fminf)][crtbuiltin]
fminf:(float x, float y) -> float %{generate(double2float)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__fmaf)][crtbuiltin]
fmaf:(float x, float y, float z) -> float %{generate(double2float)}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGLONG
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__llrintf)][crtbuiltin]
[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__, lrintf)]
llrintf:(float x) -> __LONGLONG %{generate(double2float)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__llroundf)][crtbuiltin]
[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__, lroundf)]
llroundf:(float x) -> __LONGLONG %{generate(double2float)}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGLONG */

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
nexttowardl(*) = nextafterl;

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__scalbnl)][crtbuiltin]
[if(__SIZEOF_INT__ == __SIZEOF_LONG__), export_alias(scalblnl, __scalblnl)]
scalbnl:(__LONGDOUBLE x, int n) -> __LONGDOUBLE %{generate(double2ldouble)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__scalblnl)][crtbuiltin]
[alt_variant_of(__SIZEOF_INT__ == __SIZEOF_LONG__, scalbnl)]
[if(__SIZEOF_INT__ == __SIZEOF_LONG__), export_alias(__scalbnl)]
scalblnl:(__LONGDOUBLE x, long int n) -> __LONGDOUBLE %{generate(double2ldouble)}

nearbyintl(*) = rintl;

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__roundl)][crtbuiltin]
roundl:(__LONGDOUBLE x) -> __LONGDOUBLE %{generate(double2ldouble)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__truncl)][crtbuiltin]
truncl:(__LONGDOUBLE x) -> __LONGDOUBLE %{generate(double2ldouble)}

[std][[ATTR_WUNUSED]][nothrow][export_alias(__remquol)][crtbuiltin]
remquol:(__LONGDOUBLE x, __LONGDOUBLE y, int *pquo) -> __LONGDOUBLE; /* TODO */

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__lrintl)][crtbuiltin]
[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), export_alias(llrintl)]
lrintl:(__LONGDOUBLE x) -> long int %{generate(double2ldouble)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__lroundl)][crtbuiltin]
[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), export_alias(llroundl)]
lroundl:(__LONGDOUBLE x) -> long int %{generate(double2ldouble)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__fdiml)][crtbuiltin]
fdiml:(__LONGDOUBLE x, __LONGDOUBLE y) -> __LONGDOUBLE %{generate(double2ldouble)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__fmaxl)][crtbuiltin]
fmaxl:(__LONGDOUBLE x, __LONGDOUBLE y) -> __LONGDOUBLE %{generate(double2ldouble)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__fminl)][crtbuiltin]
fminl:(__LONGDOUBLE x, __LONGDOUBLE y) -> __LONGDOUBLE %{generate(double2ldouble)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__fmal)][crtbuiltin]
fmal:(__LONGDOUBLE x, __LONGDOUBLE y, __LONGDOUBLE z) -> __LONGDOUBLE %{generate(double2ldouble)}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGLONG
[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__llrintl)][crtbuiltin]
[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__, lrintl)]
llrintl:(__LONGDOUBLE x) -> __LONGLONG %{generate(double2ldouble)}

[std][[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__llroundl)][crtbuiltin]
[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__, lroundl)]
llroundl:(__LONGDOUBLE x) -> __LONGLONG %{generate(double2ldouble)}

%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGLONG */
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_ISOC99 */



/* C++ overload aliases */
%(std)#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_MATH_H_PROTO)
%(std)extern "C++" {
%[insert:std_function(acos = acosf, externLinkageOverride: "C++")]
%[insert:std_function(asin = asinf, externLinkageOverride: "C++")]
%[insert:std_function(atan = atanf, externLinkageOverride: "C++")]
%[insert:std_function(atan2 = atan2f, externLinkageOverride: "C++")]
%[insert:std_function(cos = cosf, externLinkageOverride: "C++")]
%[insert:std_function(sin = sinf, externLinkageOverride: "C++")]
%[insert:std_function(tan = tanf, externLinkageOverride: "C++")]
%[insert:std_function(cosh = coshf, externLinkageOverride: "C++")]
%[insert:std_function(sinh = sinhf, externLinkageOverride: "C++")]
%[insert:std_function(tanh = tanhf, externLinkageOverride: "C++")]
%[insert:std_function(exp = expf, externLinkageOverride: "C++")]
%[insert:std_function(frexp = frexpf, externLinkageOverride: "C++")]
%[insert:std_function(ldexp = ldexpf, externLinkageOverride: "C++")]
%[insert:std_function(log = logf, externLinkageOverride: "C++")]
%[insert:std_function(log10 = log10f, externLinkageOverride: "C++")]
%[insert:std_function(modf = modff, externLinkageOverride: "C++")]
%[insert:std_function(pow = powf, externLinkageOverride: "C++")]
%[insert:std_function(sqrt = sqrtf, externLinkageOverride: "C++")]
%[insert:std_function(ceil = ceilf, externLinkageOverride: "C++")]
%[insert:std_function(fabs = fabsf, externLinkageOverride: "C++")]
%[insert:std_function(floor = floorf, externLinkageOverride: "C++")]
%[insert:std_function(fmod = fmodf, externLinkageOverride: "C++")]

%(std)#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:std_function(acos = acosl, externLinkageOverride: "C++")]
%[insert:std_function(asin = asinl, externLinkageOverride: "C++")]
%[insert:std_function(atan = atanl, externLinkageOverride: "C++")]
%[insert:std_function(atan2 = atan2l, externLinkageOverride: "C++")]
%[insert:std_function(cos = cosl, externLinkageOverride: "C++")]
%[insert:std_function(sin = sinl, externLinkageOverride: "C++")]
%[insert:std_function(tan = tanl, externLinkageOverride: "C++")]
%[insert:std_function(cosh = coshl, externLinkageOverride: "C++")]
%[insert:std_function(sinh = sinhl, externLinkageOverride: "C++")]
%[insert:std_function(tanh = tanhl, externLinkageOverride: "C++")]
%[insert:std_function(exp = expl, externLinkageOverride: "C++")]
%[insert:std_function(frexp = frexpl, externLinkageOverride: "C++")]
%[insert:std_function(ldexp = ldexpl, externLinkageOverride: "C++")]
%[insert:std_function(log = logl, externLinkageOverride: "C++")]
%[insert:std_function(log10 = log10l, externLinkageOverride: "C++")]
%[insert:std_function(modf = modfl, externLinkageOverride: "C++")]
%[insert:std_function(pow = powl, externLinkageOverride: "C++")]
%[insert:std_function(sqrt = sqrtl, externLinkageOverride: "C++")]
%[insert:std_function(ceil = ceill, externLinkageOverride: "C++")]
%[insert:std_function(fabs = fabsl, externLinkageOverride: "C++")]
%[insert:std_function(floor = floorl, externLinkageOverride: "C++")]
%[insert:std_function(fmod = fmodl, externLinkageOverride: "C++")]
%(std)#endif /* __COMPILER_HAVE_LONGDOUBLE */


%(std)#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
%[insert:std_function(acosh = acoshf, externLinkageOverride: "C++")]
%[insert:std_function(asinh = asinhf, externLinkageOverride: "C++")]
%[insert:std_function(atanh = atanhf, externLinkageOverride: "C++")]
%[insert:std_function(expm1 = expm1f, externLinkageOverride: "C++")]
%[insert:std_function(log1p = log1pf, externLinkageOverride: "C++")]
%[insert:std_function(logb = logbf, externLinkageOverride: "C++")]
%[insert:std_function(cbrt = cbrtf, externLinkageOverride: "C++")]
%[insert:std_function(rint = rintf, externLinkageOverride: "C++")]
%[insert:std_function(nextafter = nextafterf, externLinkageOverride: "C++")]
%[insert:std_function(remainder = remainderf, externLinkageOverride: "C++")]
%[insert:std_function(ilogb = ilogbf, externLinkageOverride: "C++")]
%(std)#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:std_function(acosh = acoshl, externLinkageOverride: "C++")]
%[insert:std_function(asinh = asinhl, externLinkageOverride: "C++")]
%[insert:std_function(atanh = atanhl, externLinkageOverride: "C++")]
%[insert:std_function(expm1 = expm1l, externLinkageOverride: "C++")]
%[insert:std_function(log1p = log1pl, externLinkageOverride: "C++")]
%[insert:std_function(logb = logbl, externLinkageOverride: "C++")]
%[insert:std_function(cbrt = cbrtl, externLinkageOverride: "C++")]
%[insert:std_function(rint = rintl, externLinkageOverride: "C++")]
%[insert:std_function(nextafter = nextafterl, externLinkageOverride: "C++")]
%[insert:std_function(remainder = remainderl, externLinkageOverride: "C++")]
%[insert:std_function(ilogb = ilogbl, externLinkageOverride: "C++")]
%(std)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std)#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */


%(std)#ifdef __USE_ISOC99
%[insert:std_function(exp2 = exp2f, externLinkageOverride: "C++")]
%[insert:std_function(log2 = log2f, externLinkageOverride: "C++")]
%[insert:std_function(copysign = copysignf, externLinkageOverride: "C++")]
%[insert:std_function(tgamma = tgammaf, externLinkageOverride: "C++")]
%[insert:std_function(nexttoward = nexttowardf, externLinkageOverride: "C++")]
%[insert:std_function(scalbn = scalbnf, externLinkageOverride: "C++")]
%[insert:std_function(scalbln = scalblnf, externLinkageOverride: "C++")]
%[insert:std_function(nearbyint = rintf, externLinkageOverride: "C++")]
%[insert:std_function(round = roundf, externLinkageOverride: "C++")]
%[insert:std_function(trunc = truncf, externLinkageOverride: "C++")]
%[insert:std_function(remquo = remquof, externLinkageOverride: "C++")]
%[insert:std_function(lrint = lrintf, externLinkageOverride: "C++")]
%[insert:std_function(lround = lroundf, externLinkageOverride: "C++")]
%[insert:std_function(fdim = fdimf, externLinkageOverride: "C++")]
%[insert:std_function(fmax = fmaxf, externLinkageOverride: "C++")]
%[insert:std_function(fmin = fminf, externLinkageOverride: "C++")]
%[insert:std_function(fma = fmaf, externLinkageOverride: "C++")]
%(std)#ifdef __COMPILER_HAVE_LONGLONG
%[insert:std_function(llrint = llrintf, externLinkageOverride: "C++")]
%[insert:std_function(llround = llroundf, externLinkageOverride: "C++")]
%(std)#endif /* __COMPILER_HAVE_LONGLONG */
%(std)#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:std_function(exp2 = exp2l, externLinkageOverride: "C++")]
%[insert:std_function(log2 = log2l, externLinkageOverride: "C++")]
%[insert:std_function(copysign = copysignl, externLinkageOverride: "C++")]
%[insert:std_function(tgamma = tgammal, externLinkageOverride: "C++")]
%[insert:std_function(nexttoward = nextafterl, externLinkageOverride: "C++")]
%[insert:std_function(scalbn = scalbnl, externLinkageOverride: "C++")]
%[insert:std_function(scalbln = scalblnl, externLinkageOverride: "C++")]
%[insert:std_function(nearbyint = rintl, externLinkageOverride: "C++")]
%[insert:std_function(round = roundl, externLinkageOverride: "C++")]
%[insert:std_function(trunc = truncl, externLinkageOverride: "C++")]
%[insert:std_function(remquo = remquol, externLinkageOverride: "C++")]
%[insert:std_function(lrint = lrintl, externLinkageOverride: "C++")]
%[insert:std_function(lround = lroundl, externLinkageOverride: "C++")]
%[insert:std_function(fdim = fdiml, externLinkageOverride: "C++")]
%[insert:std_function(fmax = fmaxl, externLinkageOverride: "C++")]
%[insert:std_function(fmin = fminl, externLinkageOverride: "C++")]
%[insert:std_function(fma = fmal, externLinkageOverride: "C++")]
%(std)#ifdef __COMPILER_HAVE_LONGLONG
%[insert:std_function(llrint = llrintl, externLinkageOverride: "C++")]
%[insert:std_function(llround = llroundl, externLinkageOverride: "C++")]
%(std)#endif /* __COMPILER_HAVE_LONGLONG */
%(std)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std)#endif /* __USE_ISOC99 */


%(std)#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
%[insert:std_function(hypot = hypotf, externLinkageOverride: "C++")]
%[insert:std_function(erf = erff, externLinkageOverride: "C++")]
%[insert:std_function(erfc = erfcf, externLinkageOverride: "C++")]
%[insert:std_function(lgamma = lgammaf, externLinkageOverride: "C++")]
%(std)#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:std_function(hypot = hypotl, externLinkageOverride: "C++")]
%[insert:std_function(erf = erfl, externLinkageOverride: "C++")]
%[insert:std_function(erfc = erfcl, externLinkageOverride: "C++")]
%[insert:std_function(lgamma = lgammal, externLinkageOverride: "C++")]
%(std)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std)#endif /* __USE_XOPEN || __USE_ISOC99 */


%(std)} /* extern "C++" */
%(std)#endif /* __cplusplus && __CORRECT_ISO_CPP_MATH_H_PROTO */





%
%#ifdef __USE_GNU
@@Cosine and sine of X
[export_alias(__sincos)][nothrow]
[attribute("__DECL_SIMD_sincos")][decl_include("<bits/math-vector.h>")][crtbuiltin]
sincos:(double x, [[nonnull]] double *psinx, [[nonnull]] double *pcosx); /* TODO */

@@A function missing in all standards: compute exponent to base ten
[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__exp10)][crtbuiltin]
exp10:(double x) -> double; /* TODO */

@@Another name occasionally used
[[crtbuiltin, ATTR_WUNUSED, ATTR_MCONST, nothrow, export_alias(__pow10)]]
[[userimpl, requires($has_function(pow))]]
double pow10(double x) {
	return pow(10.0, x);
}

[[crtbuiltin, export_alias(__sincosf), nothrow, doc_alias(sincos)]]
[[attribute("__DECL_SIMD_sincosf"), decl_include("<bits/math-vector.h>")]]
[[userimpl, requires_function(sincos)]]
void sincosf(float x, [[nonnull]] float *psinx, [[nonnull]] float *pcosx) {
	double sinx, cosx;
	sincos((double)x, &sinx, &cosx);
	*psinx = (float)sinx;
	*pcosx = (float)cosx;
}

[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__exp10f)][crtbuiltin]
exp10f:(float x) -> float; /* TODO */

[[crtbuiltin, export_alias(__pow10f), ATTR_WUNUSED, ATTR_MCONST, nothrow]]
[[userimpl, requires_function("powf")]]
pow10f:(float x) -> float {
	return powf(10.0f, x);
}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[crtbuiltin,  export_alias(__sincosl), nothrow, doc_alias(sincos)]]
[[attribute("__DECL_SIMD_sincosl"), decl_include("<bits/math-vector.h>")]]
[[if(defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), export_alias(__sincos, sincos)]]
[[userimpl, requires_function("sincos")]]
void sincosl(__LONGDOUBLE x, [[nonnull]] __LONGDOUBLE *psinx, [[nonnull]] __LONGDOUBLE *pcosx) {
	double sinx, cosx;
	sincos((double)x, &sinx, &cosx);
	*psinx = (__LONGDOUBLE)sinx;
	*pcosx = (__LONGDOUBLE)cosx;
}

[crtbuiltin][[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__exp10l)]
exp10l:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */

[crtbuiltin][[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__pow10l)]
pow10l:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_GNU */


%
%#ifdef __USE_MISC

%#if !defined(__cplusplus) || !defined(__CORRECT_ISO_CPP11_MATH_H_PROTO_FP) /* isinf conflicts with C++11. */
@@Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity
[[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__isinf)]
[requires_include("<ieee754.h>")][impl_include("<libm/isinf.h>")][crtbuiltin]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
isinf:(double x) -> int {
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(@isinf@, x);
#else /* __LIBM_MATHFUNI */
	return x == @HUGE_VAL@;
#endif /* !__LIBM_MATHFUNI */
}
%#endif /* !__cplusplus || !__CORRECT_ISO_CPP11_MATH_H_PROTO_FP */

[[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__isinff)][crtbuiltin]
isinff:(float x) -> int %{generate(double2float)}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__isinfl)][crtbuiltin]
[if(defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), export_alias(__isinf, isinf)]
isinfl:(__LONGDOUBLE x) -> int %{generate(double2ldouble)}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

@@Return nonzero if VALUE is finite and not NaN
[[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__finite, _finite)][crtbuiltin]
[requires_include("<ieee754.h>")][impl_include(<libm/finite.h>)]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) ||
          ($has_function(isinf) && $has_function(isnan)))]
finite:(double x) -> int {
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(@finite@, x);
#else /* __LIBM_MATHFUNI */
	return !isinf(x) && !isnan(x);
#endif /* !__LIBM_MATHFUNI */
}

drem:(*) = remainder;

@@Return the fractional part of X after dividing out `ilogb(X)'
[[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__significand)][crtbuiltin]
[requires_include("<ieee754.h>")][impl_include(<libm/significand.h>)]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
significand:(double x) -> double {
	return __LIBM_MATHFUN(@significand@, x);
}

[[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__finitef)][crtbuiltin]
finitef:(float x) -> int %{generate(double2float)}

dremf(*) = remainderf;

[[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__significandf)][crtbuiltin]
significandf:(float x) -> float %{generate(double2float)}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__finitel)][crtbuiltin]
[if(defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), export_alias(__finite, finite)]
finitel:(__LONGDOUBLE x) -> int %{generate(double2ldouble)}

dreml(*) = remainderl;

[[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__significandl)][crtbuiltin]
significandl:(__LONGDOUBLE x) -> __LONGDOUBLE %{generate(double2ldouble)}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */

%
%#if defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
%#if !defined(__cplusplus) || !defined(__CORRECT_ISO_CPP11_MATH_H_PROTO_FP) /* isnan conflicts with C++11. */
@@Return nonzero if VALUE is not a number
[[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__isnan, _isnan)][crtbuiltin]
[requires_include("<ieee754.h>")][impl_include("<libm/isnan.h>")]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
isnan:(double x) -> int {
	return __LIBM_MATHFUNI(@isnan@, x);
}
%#endif /* !cplusplus || !__CORRECT_ISO_CPP11_MATH_H_PROTO_FP */

[[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__isnanf)][crtbuiltin]
isnanf:(float x) -> int %{generate(double2float)}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(__isnanl)][crtbuiltin]
[if(defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), export_alias(__isnan, _isnan, isnan)]
isnanl:(__LONGDOUBLE x) -> int %{generate(double2ldouble)}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

%#endif /* __USE_MISC || (__USE_XOPEN && !__USE_XOPEN2K) */

%
%/* Bessel functions. */
%#if defined(__USE_MISC) || (defined(__USE_XOPEN) && __MATH_DECLARING_DOUBLE)
[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__j0)][crtbuiltin]
j0:(double x) -> double; /* TODO */

[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__j1)][crtbuiltin]
j1:(double x) -> double; /* TODO */

[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__jn)][crtbuiltin]
jn:(int n, double x) -> double; /* TODO */

[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__y0)][crtbuiltin]
y0:(double x) -> double; /* TODO */

[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__y1)][crtbuiltin]
y1:(double x) -> double; /* TODO */

[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__yn)][crtbuiltin]
yn:(int n, double x) -> double; /* TODO */


[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__j0f)][crtbuiltin]
j0f:(float x) -> float; /* TODO */

[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__j1f)][crtbuiltin]
j1f:(float x) -> float; /* TODO */

[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__jnf)][crtbuiltin]
jnf:(int n, float x) -> float; /* TODO */

[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__y0f)][crtbuiltin]
y0f:(float x) -> float; /* TODO */

[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__y1f)][crtbuiltin]
y1f:(float x) -> float; /* TODO */

[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__ynf)][crtbuiltin]
ynf:(int n, float x) -> float; /* TODO */


%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__j0l)][crtbuiltin]
j0l:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */

[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__j1l)][crtbuiltin]
j1l:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */

[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__jnl)][crtbuiltin]
jnl:(int n, __LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */

[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__y0l)][crtbuiltin]
y0l:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */

[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__y1l)][crtbuiltin]
y1l:(__LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */

[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__ynl)][crtbuiltin]
ynl:(int n, __LONGDOUBLE x) -> __LONGDOUBLE; /* TODO */
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC || (__USE_XOPEN && __MATH_DECLARING_DOUBLE) */


%
%#if defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
@@Obsolete export_alias for `lgamma'
gamma(*) = lgamma;

@@Obsolete export_alias for `lgammaf'
gammaf(*) = lgammaf;

%#ifdef __COMPILER_HAVE_LONGDOUBLE
@@Obsolete export_alias for `lgammal'
gammal(*) = lgammal;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC || (__USE_XOPEN && !__USE_XOPEN2K) */

%#ifdef __USE_MISC
@@Reentrant version of lgamma. This function uses the global variable
@@`signgam'. The reentrant version instead takes a pointer and stores
@@the value through it
[[ATTR_WUNUSED]][export_alias(__lgamma_r)][crtbuiltin]
lgamma_r:(double x, int *signgamp) -> double; /* TODO */

[[ATTR_WUNUSED]][export_alias(__lgammaf_r)][crtbuiltin]
lgammaf_r:(float x, int *signgamp) -> float /*TODO:%{generate(double2float(lgamma_r)))}*/;

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[ATTR_WUNUSED]][export_alias(__lgammal_r)][crtbuiltin]
lgammal_r:(__LONGDOUBLE x, int *signgamp) -> __LONGDOUBLE /*TODO:%{generate(double2ldouble(lgamma_r)))}*/;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */

%
%#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8))
@@Return X times (2 to the Nth power)
[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__scalb, _scalb)][crtbuiltin]
[impl_include("<libm/isnan.h>")]
[impl_include(<libm/finite.h>)][impl_include("<libm/isinf.h>")]
[impl_include("<libm/matherr.h>")][impl_include("<parts/errno.h>")]
[requires_include("<ieee754.h>")][impl_include(<libm/scalb.h>)]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
scalb:(double x, double fn) -> double {
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
	result = __LIBM_MATHFUN2(@scalb@, x, fn);
	if (__LIBM_LIB_VERSION == __LIBM_SVID) {
		if (__LIBM_MATHFUN(@isinf@, result)) {
			if (__LIBM_MATHFUN(@finite@, x)) {
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
		if (!__LIBM_MATHFUN(@finite@, result) || result == 0.0) {
			if (__LIBM_MATHFUN(@isnan@, result)) {
				if (!__LIBM_MATHFUN(@isnan@, x) && !__LIBM_MATHFUN(@isnan@, fn))
					result = __kernel_standard(x, fn, result, __LIBM_KMATHERR_SCALB_INVALID);
			} else if (__LIBM_MATHFUN(@isinf@, result)) {
				if (!__LIBM_MATHFUN(@isinf@, x) && !__LIBM_MATHFUN(@isinf@, fn))
					result = __kernel_standard(x, fn, result, __LIBM_KMATHERR_SCALB_OVERFLOW);
			} else {
				/* result == 0.  */
				if (x != 0.0 && !__LIBM_MATHFUN(@isinf@, fn))
					result = __kernel_standard(x, fn, result, __LIBM_KMATHERR_SCALB_UNDERFLOW);
			}
		}
	}
	return result;
}
%#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K8) */

%#ifdef __USE_MISC
[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__scalbf, _scalbf)][crtbuiltin]
scalbf:(float x, float fn) -> float %{generate(double2float)}


%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[ATTR_WUNUSED]][ATTR_MCONST][nothrow][export_alias(__scalbl)][crtbuiltin]
[if(defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), export_alias(_scalb)]
scalbl:(__LONGDOUBLE x, __LONGDOUBLE fn) -> __LONGDOUBLE %{generate(double2ldouble)}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */








%
%
%
%#if 1 /* GLIBc aliases */
__acos(*) = acos;
__asin(*) = asin;
__atan(*) = atan;
__atan2(*) = atan2;
__cos(*) = cos;
__sin(*) = sin;
__tan(*) = tan;
__cosh(*) = cosh;
__sinh(*) = sinh;
__tanh(*) = tanh;
__acosf(*) = acosf;
__asinf(*) = asinf;
__atanf(*) = atanf;
__atan2f(*) = atan2f;
__cosf(*) = cosf;
__sinf(*) = sinf;
__tanf(*) = tanf;
__coshf(*) = coshf;
__sinhf(*) = sinhf;
__tanhf(*) = tanhf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
__acosl(*) = acosl;
__asinl(*) = asinl;
__atanl(*) = atanl;
__atan2l(*) = atan2l;
__cosl(*) = cosl;
__sinl(*) = sinl;
__tanl(*) = tanl;
__coshl(*) = coshl;
__sinhl(*) = sinhl;
__tanhl(*) = tanhl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#ifdef __USE_GNU
__sincos(*) = sincos;
__sincosf(*) = sincosf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
__sincosl(*) = sincosl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_GNU */

%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
__acosh(*) = acosh;
__asinh(*) = asinh;
__atanh(*) = atanh;
__acoshf(*) = acoshf;
__asinhf(*) = asinhf;
__atanhf(*) = atanhf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
__acoshl(*) = acoshl;
__asinhl(*) = asinhl;
__atanhl(*) = atanhl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

__exp(*) = exp;
__frexp(*) = frexp;
__ldexp(*) = ldexp;
__log(*) = log;
__log10(*) = log10;
__modf(*) = modf;
__expf(*) = expf;
__frexpf(*) = frexpf;
__ldexpf(*) = ldexpf;
__logf(*) = logf;
__log10f(*) = log10f;
__modff(*) = modff;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
__expl(*) = expl;
__frexpl(*) = frexpl;
__ldexpl(*) = ldexpl;
__logl(*) = logl;
__log10l(*) = log10l;
__modfl(*) = modfl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

%
%#ifdef __USE_GNU
__exp10(*) = exp10;
__pow10(*) = pow10;
__exp10f(*) = exp10f;
__pow10f(*) = pow10f;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
__exp10l(*) = exp10l;
__pow10l(*) = pow10l;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_GNU */

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
__expm1(*) = expm1;
__log1p(*) = log1p;
__logb(*) = logb;
__expm1f(*) = expm1f;
__log1pf(*) = log1pf;
__logbf(*) = logbf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
__expm1l(*) = expm1l;
__log1pl(*) = log1pl;
__logbl(*) = logbl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

%
%#ifdef __USE_ISOC99
__exp2(*) = exp2;
__log2(*) = log2;
__exp2f(*) = exp2f;
__log2f(*) = log2f;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
__exp2l(*) = exp2l;
__log2l(*) = log2l;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_ISOC99 */

__pow(*) = pow;
__sqrt(*) = sqrt;
__powf(*) = powf;
__sqrtf(*) = sqrtf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
__powl(*) = powl;
__sqrtl(*) = sqrtl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

%
%#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
__hypot(*) = hypot;
__hypotf(*) = hypotf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
__hypotl(*) = hypotl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_XOPEN || __USE_ISOC99 */

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
__cbrt(*) = cbrt;
__cbrtf(*) = cbrtf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
__cbrtl(*) = cbrtl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

__ceil(*) = ceil;
__fabs(*) = fabs;
__floor(*) = floor;
__fmod(*) = fmod;
__isinf(*) = isinf;
__finite(*) = finite;
__ceilf(*) = ceilf;
__fabsf(*) = fabsf;
__floorf(*) = floorf;
__fmodf(*) = fmodf;
__isinff(*) = isinff;
__finitef(*) = finitef;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
__ceill(*) = ceill;
__fabsl(*) = fabsl;
__floorl(*) = floorl;
__fmodl(*) = fmodl;
__isinfl(*) = isinfl;
__finitel(*) = finitel;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

%#ifdef __USE_MISC
__drem(*) = remainder;
__significand(*) = significand;
__dremf(*) = remainderf;
__significandf(*) = significandf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
__dreml(*) = remainderl;
__significandl(*) = significandl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */

%
%#ifdef __USE_ISOC99
__copysign(*) = copysign;
__nan(*) = nan;
__copysignf(*) = copysignf;
__nanf(*) = nanf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
__copysignl(*) = copysignl;
__nanl(*) = nanl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_ISOC99 */

%
__isnan(*) = isnan;
__isnanf(*) = isnanf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
__isnanl(*) = isnanl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

%
%/* Bessel functions. */
%#if defined(__USE_MISC) || defined(__USE_XOPEN)
__j0(*) = j0;
__j1(*) = j1;
__jn(*) = jn;
__y0(*) = y0;
__y1(*) = y1;
__yn(*) = yn;
%#endif /* __USE_MISC || __USE_XOPEN */
%#ifdef __USE_MISC
__j0f(*) = j0f;
__j1f(*) = j1f;
__jnf(*) = jnf;
__y0f(*) = y0f;
__y1f(*) = y1f;
__ynf(*) = ynf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
__j0l(*) = j0l;
__j1l(*) = j1l;
__jnl(*) = jnl;
__y0l(*) = y0l;
__y1l(*) = y1l;
__ynl(*) = ynl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */

%
%#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
__erf(*) = erf;
__erfc(*) = erfc;
__lgamma(*) = lgamma;
__erff(*) = erff;
__erfcf(*) = erfcf;
__lgammaf(*) = lgammaf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
__erfl(*) = erfl;
__erfcl(*) = erfcl;
__lgammal(*) = lgammal;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_XOPEN || __USE_ISOC99 */

%
%#ifdef __USE_ISOC99
__tgamma(*) = tgamma;
__tgammaf(*) = tgammaf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
__tgammal(*) = tgammal;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_ISOC99 */

%
%#if defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
__gamma(*) = lgamma;
__gammaf(*) = lgammaf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
__gammal(*) = lgammal;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC || (__USE_XOPEN && !__USE_XOPEN2K) */

%#ifdef __USE_MISC
__lgamma_r(*) = lgamma_r;
__lgammaf_r(*) = lgammaf_r;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
__lgammal_r(*) = lgammal_r;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
__rint(*) = rint;
__nextafter(*) = nextafter;
__remainder(*) = remainder;
__ilogb(*) = ilogb;
__rintf(*) = rintf;
__nextafterf(*) = nextafterf;
__remainderf(*) = remainderf;
__ilogbf(*) = ilogbf;

%#ifdef __COMPILER_HAVE_LONGDOUBLE
__rintl(*) = rintl;
__nextafterl(*) = nextafterl;
__remainderl(*) = remainderl;
__ilogbl(*) = ilogbl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */


%
%#ifdef __USE_ISOC99
__nexttoward(*) = nexttoward;
__scalbn(*) = scalbn;
__scalbln(*) = scalbln;
__nearbyint(*) = rint;
__round(*) = round;
__trunc(*) = trunc;
__remquo(*) = remquo;
__lrint(*) = lrint;
__lround(*) = lround;
__fdim(*) = fdim;
__fmax(*) = fmax;
__fmin(*) = fmin;
__fma(*) = fma;

__nexttowardf(*) = nexttowardf;
__scalbnf(*) = scalbnf;
__scalblnf(*) = scalblnf;
__nearbyintf(*) = rintf;
__roundf(*) = roundf;
__truncf(*) = truncf;
__remquof(*) = remquof;
__lrintf(*) = lrintf;
__lroundf(*) = lroundf;
__fdimf(*) = fdimf;
__fmaxf(*) = fmaxf;
__fminf(*) = fminf;
__fmaf(*) = fmaf;

%#ifdef __COMPILER_HAVE_LONGLONG
__llrint(*) = llrint;
__llround(*) = llround;
__llrintf(*) = llrintf;
__llroundf(*) = llroundf;
%#endif /* __COMPILER_HAVE_LONGLONG */

%#ifdef __COMPILER_HAVE_LONGDOUBLE
__nexttowardl(*) = nextafterl;
__scalbnl(*) = scalbnl;
__scalblnl(*) = scalblnl;
__nearbyintl(*) = rintl;
__roundl(*) = roundl;
__truncl(*) = truncl;
__remquol(*) = remquol;
__lrintl(*) = lrintl;
__lroundl(*) = lroundl;
__fdiml(*) = fdiml;
__fmaxl(*) = fmaxl;
__fminl(*) = fminl;
__fmal(*) = fmal;
%#ifdef __COMPILER_HAVE_LONGLONG
__llrintl(*) = llrintl;
__llroundl(*) = llroundl;
%#endif /* __COMPILER_HAVE_LONGLONG */
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_ISOC99 */

%
%#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8))
__scalb(*) = scalb;
%#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K8) */
%#ifdef __USE_MISC
__scalbf(*) = scalbf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
__scalbl(*) = scalbl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */
%#endif /* GLIBc aliases */



%
%
%/* Floating point classification */
%#ifdef __USE_ISOC99
[[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(_dclass, fpclassify)]
[requires_include("<ieee754.h>")][impl_include("<libm/fpclassify.h>")]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
__fpclassify:(double x) -> int {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return __ieee754_fpclassify((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return __ieee754_fpclassifyf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	return __ieee854_fpclassifyl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#endif /* !... */
}


[[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(_dsign)]
[impl_include("<libm/signbit.h>")]
__signbit:(double x) -> int {
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


[[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(_fdclass, fpclassifyf)]
__fpclassifyf:(float x) -> int %{generate(double2float)}

[[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(_fdsign)]
__signbitf:(float x) -> int %{generate(double2float)}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(_ldclass, fpclassifyl)]
__fpclassifyl:(__LONGDOUBLE x) -> int %{generate(double2ldouble)}

[[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(_ldsign)]
__signbitl:(__LONGDOUBLE x) -> int %{generate(double2ldouble)}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_ISOC99 */

%
%#ifdef __USE_GNU
[[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(issignaling)]
[requires_include("<ieee754.h>")][impl_include("<libm/issignaling.h>")]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
          defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
          defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]
__issignaling:(double x) -> int {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return __ieee754_issignaling((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return __ieee754_issignalingf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	return __ieee854_issignalingl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#endif /* !... */
}

[[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(issignalingf)]
__issignalingf:(float x) -> int %{generate(double2float)}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[ATTR_WUNUSED, ATTR_CONST]][nothrow][export_alias(issignalingl)]
__issignalingl:(__LONGDOUBLE x) -> int %{generate(double2ldouble)}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_GNU */

[[ATTR_WUNUSED, ATTR_CONST, ignore, nocrt, alias(_dpcomp)]]
int _dpcomp:(double x, double y) /* TODO */;
[[ATTR_WUNUSED, ATTR_CONST, ignore, nocrt, alias(_fdpcomp)]]
int _fdpcomp:(float x, float y) /*TODO:%{generate(double2float(_dpcomp))}*/;
[[ATTR_WUNUSED, ATTR_CONST, ignore, nocrt, alias(_ldpcomp)]]
int _ldpcomp:(__LONGDOUBLE x, __LONGDOUBLE y) /*TODO:%{generate(double2ldouble(_dpcomp))}*/;

__dos_dpcomp(*) = _dpcomp;
__dos_fdpcomp(*) = _fdpcomp;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
__dos_ldpcomp(*) = _ldpcomp;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */


%
%{

#if defined(__USE_MISC) || defined(__USE_XOPEN)
/* This variable is used by `gamma' and `lgamma'. */
#ifdef __CRT_HAVE_signgam
#undef signgam
__LIBC int (signgam);
#endif /* __CRT_HAVE_signgam */
#endif /* __USE_MISC || __USE_XOPEN */

#ifdef __COMPILER_HAVE_C11_GENERIC
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __FPFUNC(x, f, d, l)      _Generic(x, float: f(x), double: d(x), default: l(x))
#define __FPFUNC2(x, y, f, d, l)  _Generic((x) + (y), float: f(x, y), double: d(x, y), default: l(x, y))
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __FPFUNC(x, f, d, l)      _Generic(x, float: f(x), default: d(x))
#define __FPFUNC2(x, y, f, d, l)  _Generic((x) + (y), float: f(x, y), default: d(x, y))
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#elif !defined(__NO_builtin_choose_expr) &&        \
      !defined(__NO_builtin_types_compatible_p) && \
       defined(__COMPILER_HAVE_TYPEOF)
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __FPFUNC(x, f, d, l)                                                                     \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (float)0), float), f(x), \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (double)0), double), d(x), l(x)))
#define __FPFUNC2(x, y, f, d, l)                                                                          \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (y) + (float)0), float), f(x, y), \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (y) + (double)0), double), d(x, y), l(x, y)))
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __FPFUNC(x, f, d, l) \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (float)0), float), f(x), d(x))
#define __FPFUNC2(x, y, f, d, l) \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (y) + (float)0), float), f(x, y), d(x, y))
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#elif !defined(__NO_builtin_types_compatible_p) && defined(__COMPILER_HAVE_TYPEOF)
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __FPFUNC(x, f, d, l)                                             \
	(__builtin_types_compatible_p(__typeof__((x) + (float)0), float)     \
	 ? f((float)(x))                                                     \
	 : __builtin_types_compatible_p(__typeof__((x) + (double)0), double) \
	   ? d((double)(x))                                                  \
	   : l((__LONGDOUBLE)(x)))
#define __FPFUNC2(x, y, f, d, l)                                               \
	(__builtin_types_compatible_p(__typeof__((x) + (y) + (float)0), float)     \
	 ? f((float)(x), (float)(y))                                               \
	 : __builtin_types_compatible_p(__typeof__((x) + (y) + (double)0), double) \
	   ? d((double)(x), (double)(y))                                           \
	   : l((__LONGDOUBLE)(x), (__LONGDOUBLE)(y)))
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __FPFUNC(x, f, d, l) \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (float)0), float), f(x), d(x))
#define __FPFUNC2(x, y, f, d, l) \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (y) + (float)0), float), f(x, y), d(x, y))
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#elif defined(__COMPILER_HAVE_LONGDOUBLE)
#define __FPFUNC(x, f, d, l)                     \
	(sizeof((x) + (float)0) == sizeof(float)     \
	 ? f((float)(x))                             \
	 : sizeof((x) + (double)0) == sizeof(double) \
	   ? d((double)(x))                          \
	   : l((__LONGDOUBLE)(x)))
#define __FPFUNC2(x, y, f, d, l)                       \
	(sizeof((x) + (y) + (float)0) == sizeof(float)     \
	 ? f((float)(x), (float)(y))                       \
	 : sizeof((x) + (y) + (double)0) == sizeof(double) \
	   ? d((double)(x), (double)(y))                   \
	   : l((__LONGDOUBLE)(x), (__LONGDOUBLE)(y)))
#else /* ... */
#define __FPFUNC(x, f, d, l)                 \
	(sizeof((x) + (float)0) == sizeof(float) \
	 ? f((float)(x))                         \
	 : d((double)(x)))
#define __FPFUNC2(x, y, f, d, l)                   \
	(sizeof((x) + (y) + (float)0) == sizeof(float) \
	 ? f((float)(x), (float)(y))                   \
	 : d((double)(x), (double)(y)))
#endif /* !... */

#ifdef __USE_ISOC99
/* Get the architecture specific values describing the floating-point
 * evaluation.  The following symbols will get defined:
 *
 *  float_t    floating-point type at least as wide as `float' used
 *      to evaluate `float' expressions
 *  double_t    floating-point type at least as wide as `double' used
 *      to evaluate `double' expressions
 *
 *  FLT_EVAL_METHOD
 *      Defined to
 *        0    if `float_t' is `float' and `double_t' is `double'
 *        1    if `float_t' and `double_t' are `double'
 *        2    if `float_t' and `double_t' are `long double'
 *        else    `float_t' and `double_t' are unspecified
 *
 *  INFINITY    representation of the infinity value of type `float'
 *
 *  FP_FAST_FMA
 *  FP_FAST_FMAF
 *  FP_FAST_FMAL
 *      If defined it indicates that the `fma' function
 *      generally executes about as fast as a multiply and an add.
 *      This macro is defined only iff the `fma' function is
 *      implemented directly with a hardware multiply-add instructions.
 *
 *  FP_ILOGB0    Expands to a value returned by `ilogb(0.0)'.
 *  FP_ILOGBNAN  Expands to a value returned by `ilogb(NAN)'.
 *
 *  DECIMAL_DIG    Number of decimal digits supported by conversion between
 *      decimal and all internal floating-point formats. */

/* All floating-point numbers can be put in one of these categories. */
/* NOTE: These values must match the declarations from <libm/fdlibm.h>! */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	FP_NAN       = 0,
	FP_INFINITE  = 1,
	FP_ZERO      = 2,
	FP_SUBNORMAL = 3,
	FP_NORMAL    = 4
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define FP_NAN       FP_NAN
#define FP_INFINITE  FP_INFINITE
#define FP_ZERO      FP_ZERO
#define FP_SUBNORMAL FP_SUBNORMAL
#define FP_NORMAL    FP_NORMAL
#else /* __COMPILER_PREFERR_ENUMS */
#define FP_NAN       0
#define FP_INFINITE  1
#define FP_ZERO      2
#define FP_SUBNORMAL 3
#define FP_NORMAL    4
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/




#ifndef __OPTIMIZE_SIZE__
#if __has_builtin(__builtin_signbitf) && __has_builtin(__builtin_signbit) && __has_builtin(__builtin_signbitl)
#define signbit(x) __FPFUNC(x, __builtin_signbitf, __builtin_signbit, __builtin_signbitl)
#endif /* __builtin_signbitf && __builtin_signbit && __builtin_signbitl */
#ifndef __SUPPORT_SNAN__
#if __has_builtin(__builtin_fpclassify)
#define fpclassify(x) __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL, FP_SUBNORMAL, FP_ZERO, x)
#endif /* __builtin_fpclassify */
#if __has_builtin(__builtin_isfinite)
#define isfinite(x) __builtin_isfinite(x)
#endif /* __builtin_isfinite */
#if __has_builtin(__builtin_isnormal)
#define isnormal(x) __builtin_isnormal(x)
#endif /* __builtin_isnormal */
#if __has_builtin(__builtin_isnan)
#define isnan(x) __builtin_isnan(x)
#endif /* __builtin_isnan */
#if __has_builtin(__builtin_isinf_sign)
#define isinf(x) __builtin_isinf_sign(x)
#endif /* __builtin_isinf_sign */
#endif /* !__SUPPORT_SNAN__ */
#endif /* !__OPTIMIZE_SIZE__ */

#ifndef fpclassify
#define fpclassify(x) __FPFUNC(x, __fpclassifyf, __fpclassify, __fpclassifyl)
#endif /* !fpclassify */

#ifndef signbit
#define signbit(x) __FPFUNC(x, __signbitf, __signbit, __signbitl)
#endif /* !signbit */

#ifndef isnormal
#ifdef fpclassify
#define isnormal(x) (fpclassify(x) == FP_NORMAL)
#endif /* fpclassify */
#endif /* !isnormal */

#ifndef isfinite
#define isfinite(x) __FPFUNC(x, __finitef, __finite, __finitel)
#endif /* !isfinite */

#ifndef isnan
#define isnan(x) __FPFUNC(x, __isnanf, __isnan, __isnanl)
#endif /* !isnan */

#ifndef isinf
#define isinf(x) __FPFUNC(x, __isinff, __isinf, __isinfl)
#endif /* !isinf */


#ifdef __USE_ISOC99
#if __has_builtin(__builtin_isunordered) && \
   (!defined(__DOS_COMPAT__) || !defined(__OPTIMIZE_SIZE__))
#define isunordered(u, v)    __builtin_isunordered(u, v)
#define isgreater(x, y)      __builtin_isgreater(x, y)
#define isgreaterequal(x, y) __builtin_isgreaterequal(x, y)
#define isless(x, y)         __builtin_isless(x, y)
#define islessequal(x, y)    __builtin_islessequal(x, y)
#define islessgreater(x, y)  __builtin_islessgreater(x, y)
#elif defined(__CRT_HAVE__dpcomp)
#define __DOS_FPCOMPARE(x, y) __FPFUNC2(x, y, __dos_fdpcomp, __dos_dpcomp, __dos_ldpcomp)
#define isgreater(x, y)      ((__DOS_FPCOMPARE(x, y)&4) != 0)
#define isgreaterequal(x, y) ((__DOS_FPCOMPARE(x, y)&6) != 0)
#define isless(x, y)         ((__DOS_FPCOMPARE(x, y)&1) != 0)
#define islessequal(x, y)    ((__DOS_FPCOMPARE(x, y)&3) != 0)
#define islessgreater(x, y)  ((__DOS_FPCOMPARE(x, y)&5) != 0)
#define isunordered(x, y)    (__DOS_FPCOMPARE(x, y) == 0)
#endif


/* Generic... */
#ifndef isunordered
#ifdef fpclassify
#define isunordered(u, v) (fpclassify(u) == FP_NAN || fpclassify(v) == FP_NAN)
#else /* fpclassify */
#define isunordered(u, v) 0
#endif /* !fpclassify */
#endif /* !isunordered */

#ifndef isgreater
#ifdef __NO_XBLOCK
#define isgreater(x, y) (!isunordered(x, y) && (x) > (y))
#else /* __NO_XBLOCK */
#define isgreater(x, y) __XBLOCK({ __typeof__(x) __x = (x); __typeof__(y) __y = (y); __XRETURN !isunordered(__x, __y) && __x > __y; })
#endif /* !__NO_XBLOCK */
#endif /* !isgreater */

#ifndef isgreaterequal
#ifdef __NO_XBLOCK
#define isgreaterequal(x, y) (!isunordered(x, y) && (x) >= (y))
#else /* __NO_XBLOCK */
#define isgreaterequal(x, y) __XBLOCK({ __typeof__(x) __x = (x); __typeof__(y) __y = (y); __XRETURN !isunordered(__x, __y) && __x >= __y; })
#endif /* !__NO_XBLOCK */
#endif /* !isgreaterequal */

#ifndef isless
#ifdef __NO_XBLOCK
#define isless(x, y) (!isunordered(x, y) && (x) < (y))
#else /* __NO_XBLOCK */
#define isless(x, y) __XBLOCK({ __typeof__(x) __x = (x); __typeof__(y) __y = (y); __XRETURN !isunordered(__x, __y) && __x < __y; })
#endif /* !__NO_XBLOCK */
#endif /* !isless */

#ifndef islessequal
#ifdef __NO_XBLOCK
#define islessequal(x, y) (!isunordered(x, y) && (x) <= (y))
#else /* __NO_XBLOCK */
#define islessequal(x, y) __XBLOCK({ __typeof__(x) __x = (x); __typeof__(y) __y = (y); __XRETURN !isunordered(__x, __y) && __x <= __y; })
#endif /* !__NO_XBLOCK */
#endif /* !islessequal */

#ifndef islessgreater
#ifdef __NO_XBLOCK
#define islessgreater(x, y) (!isunordered(x, y) && ((x) < (y) || (y) < (x)))
#else /* __NO_XBLOCK */
#define islessgreater(x, y) __XBLOCK({ __typeof__(x) __x = (x); __typeof__(y) __y = (y); __XRETURN !isunordered(__x, __y) && (__x < __y || __y < __x); })
#endif /* !__NO_XBLOCK */
#endif /* !islessgreater */
#endif /* __USE_ISOC99 */




#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP11_MATH_H_PROTO_FP)
/* Libstdc++ headers need us to define these as functions when also
 * defining `__CORRECT_ISO_CPP11_MATH_H_PROTO_FP', which we need to
 * do in order to get it to stop re-declaring other functions such
 * as `acosh'... *ugh* */
__NAMESPACE_STD_BEGIN
extern "C++" {
#ifdef fpclassify
#ifndef __std_fpclassify_defined
#define __std_fpclassify_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST int __NOTHROW(__LIBCCALL fpclassify)(float __x) { return fpclassify(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST int __NOTHROW(__LIBCCALL fpclassify)(double __x) { return fpclassify(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST int __NOTHROW(__LIBCCALL fpclassify)(__LONGDOUBLE __x) { return fpclassify(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_fpclassify_defined */
#undef fpclassify
#endif /* fpclassify */
#ifdef signbit
#ifndef __std_signbit_defined
#define __std_signbit_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL signbit)(float __x) { return signbit(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL signbit)(double __x) { return signbit(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL signbit)(__LONGDOUBLE __x) { return signbit(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_signbit_defined */
#undef signbit
#endif /* signbit */
#ifdef isnormal
#ifndef __std_isnormal_defined
#define __std_isnormal_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isnormal)(float __x) { return isnormal(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isnormal)(double __x) { return isnormal(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isnormal)(__LONGDOUBLE __x) { return isnormal(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isnormal_defined */
#undef isnormal
#endif /* isnormal */
#ifdef isfinite
#ifndef __std_isfinite_defined
#define __std_isfinite_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isfinite)(float __x) { return isfinite(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isfinite)(double __x) { return isfinite(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isfinite)(__LONGDOUBLE __x) { return isfinite(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isfinite_defined */
#undef isfinite
#endif /* isfinite */
#ifdef isnan
#ifndef __std_isnan_defined
#define __std_isnan_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isnan)(float __x) { return isnan(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isnan)(double __x) { return isnan(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isnan)(__LONGDOUBLE __x) { return isnan(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isnan_defined */
#undef isnan
#endif /* isnan */
#ifdef isinf
#ifndef __std_isinf_defined
#define __std_isinf_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isinf)(float __x) { return isinf(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isinf)(double __x) { return isinf(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isinf)(__LONGDOUBLE __x) { return isinf(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isinf_defined */
#undef isinf
#endif /* isinf */
#ifdef isunordered
#ifndef __std_isunordered_defined
#define __std_isunordered_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isunordered)(float __x, float __y) { return isunordered(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isunordered)(double __x, double __y) { return isunordered(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isunordered)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return isunordered(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isunordered_defined */
#undef isunordered
#endif /* isunordered */
#ifdef isgreater
#ifndef __std_isgreater_defined
#define __std_isgreater_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isgreater)(float __x, float __y) { return isgreater(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isgreater)(double __x, double __y) { return isgreater(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isgreater)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return isgreater(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isgreater_defined */
#undef isgreater
#endif /* isgreater */
#ifdef isgreaterequal
#ifndef __std_isgreaterequal_defined
#define __std_isgreaterequal_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isgreaterequal)(float __x, float __y) { return isgreaterequal(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isgreaterequal)(double __x, double __y) { return isgreaterequal(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isgreaterequal)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return isgreaterequal(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isgreaterequal_defined */
#undef isgreaterequal
#endif /* isgreaterequal */
#ifdef isless
#ifndef __std_isless_defined
#define __std_isless_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isless)(float __x, float __y) { return isless(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isless)(double __x, double __y) { return isless(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isless)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return isless(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isless_defined */
#undef isless
#endif /* isless */
#ifdef islessequal
#ifndef __std_islessequal_defined
#define __std_islessequal_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL islessequal)(float __x, float __y) { return islessequal(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL islessequal)(double __x, double __y) { return islessequal(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL islessequal)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return islessequal(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_islessequal_defined */
#undef islessequal
#endif /* islessequal */
#ifdef islessgreater
#ifndef __std_islessgreater_defined
#define __std_islessgreater_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL islessgreater)(float __x, float __y) { return islessgreater(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL islessgreater)(double __x, double __y) { return islessgreater(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL islessgreater)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return islessgreater(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_islessgreater_defined */
#undef islessgreater
#endif /* islessgreater */
} /* extern "C++" */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifdef __std_fpclassify_defined
__NAMESPACE_STD_USING(fpclassify)
#endif /* __std_fpclassify_defined */
#ifdef __std_signbit_defined
__NAMESPACE_STD_USING(signbit)
#endif /* __std_signbit_defined */
#ifdef __std_isnormal_defined
__NAMESPACE_STD_USING(isnormal)
#endif /* __std_isnormal_defined */
#ifdef __std_isfinite_defined
__NAMESPACE_STD_USING(isfinite)
#endif /* __std_isfinite_defined */
#ifdef __std_isnan_defined
__NAMESPACE_STD_USING(isnan)
#endif /* __std_isnan_defined */
#ifdef __std_isinf_defined
__NAMESPACE_STD_USING(isinf)
#endif /* __std_isinf_defined */
#ifdef __std_isunordered_defined
__NAMESPACE_STD_USING(isunordered)
#endif /* __std_isunordered_defined */
#ifdef __std_isgreater_defined
__NAMESPACE_STD_USING(isgreater)
#endif /* __std_isgreater_defined */
#ifdef __std_isgreaterequal_defined
__NAMESPACE_STD_USING(isgreaterequal)
#endif /* __std_isgreaterequal_defined */
#ifdef __std_isless_defined
__NAMESPACE_STD_USING(isless)
#endif /* __std_isless_defined */
#ifdef __std_islessequal_defined
__NAMESPACE_STD_USING(islessequal)
#endif /* __std_islessequal_defined */
#ifdef __std_islessgreater_defined
__NAMESPACE_STD_USING(islessgreater)
#endif /* __std_islessgreater_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __cplusplus && __CORRECT_ISO_CPP11_MATH_H_PROTO_FP */

/* Bitmasks for the math_errhandling macro. */
#define MATH_ERRNO     1 /* errno set by math functions. */
#define MATH_ERREXCEPT 2 /* Exceptions raised by math functions. */

/* By default all functions support both errno and exception handling.
 * In gcc's fast math mode and if inline functions are defined this might not be true. */
#ifndef __FAST_MATH__
#define math_errhandling (MATH_ERRNO | MATH_ERREXCEPT)
#endif /* !__FAST_MATH__ */
#endif /* __USE_ISOC99 */


#ifdef __USE_GNU
#ifndef issignaling
#define issignaling(x) __FPFUNC(x, __issignalingf, __issignaling, __issignalingl)
#endif /* !issignaling */
#endif /* __USE_GNU */


#ifdef __USE_MISC
/* Support for various different standard error handling behaviors. */
typedef enum {
	_IEEE_  = -1, /* According to IEEE 754/IEEE 854. */
	_SVID_  = 0,  /* According to System V, release 4. */
	_XOPEN_ = 1,  /* Nowadays also Unix98. */
	_POSIX_ = 2,
	_ISOC_  = 3   /* Actually this is ISO C99. */
} _LIB_VERSION_TYPE;

/* This variable can be changed at run-time to any of the values above to
 * affect floating point error handling behavior (it may also be necessary
 * to change the hardware FPU exception settings). */
#ifdef __CRT_HAVE__LIB_VERSION
}%[push_macro @undef { _LIB_VERSION }]%{
__LIBC _LIB_VERSION_TYPE _LIB_VERSION;
}%[pop_macro]%{
#endif /* __CRT_HAVE__LIB_VERSION */
#endif /* __USE_MISC */


#ifdef __USE_MISC

/* In SVID error handling, `matherr' is called with this description of the exceptional condition.
 * We have a problem when using C++ since `exception' is a reserved name in C++. */
#ifdef __cplusplus
struct __exception
#else /* __cplusplus */
}%[push_macro @undef { exception }]%{
struct exception
#endif /* !__cplusplus */
}%[push_macro @undef { type name arg1 arg2 retval err }]%{
{
	int    type;
	char  *name;
	double arg1;
	double arg2;
	double retval;
	int    err;
#ifdef __CRT_DOS
	int    __pad;
#endif /* __CRT_DOS */
};
}%[pop_macro]%{

#ifdef __CRT_HAVE_matherr
#ifdef __cplusplus
__CDECLARE(,int,__NOTHROW,matherr,(struct __exception *__exc),(__exc))
#else /* __cplusplus */
__CDECLARE(,int,__NOTHROW,matherr,(struct exception *__exc),(__exc))
}%[pop_macro]%{
#endif /* !__cplusplus */
#endif /* __CRT_HAVE_matherr */

#define X_TLOSS    1.41484755040568800000e+16

/* Types of exceptions in the `type' field. */
#define DOMAIN     1
#define SING       2
#define OVERFLOW   3
#define UNDERFLOW  4
#define TLOSS      5
#define PLOSS      6

/* SVID mode specifies returning this large value instead of infinity. */
#define HUGE       3.40282347e+38F

#else /* __USE_MISC */
#ifdef __USE_XOPEN
/* X/Open wants another strange constant. */
#define MAXFLOAT   3.40282347e+38F
#endif /* __USE_XOPEN */
#endif /* !__USE_MISC */

}


%{
#endif /* __CC__ */

__SYSDECL_END

}
%(c, ccompat)#endif /* !__NO_FPU */
