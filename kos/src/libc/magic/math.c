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

%[define_ccompat_header(cmath)]
%[default_impl_section(.text.crt.math.math)]

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
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__acos)][nothrow]
[crtbuiltin] acos:(double x) -> double; /* TODO */

@@Arc sine of X
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__asin)][nothrow]
[crtbuiltin] asin:(double x) -> double; /* TODO */

@@Arc tangent of X
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__atan)][nothrow][crtbuiltin]
[requires_include(<ieee754.h>)][decl_include(<libm/atan.h>)][userimpl]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__))]
atan:(double x) -> double {
	COMPILER_IMPURE(); /* XXX: Math error handling */
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_atan((__IEEE754_DOUBLE_TYPE__)x);
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
	return (double)__ieee754_atanf((__IEEE754_FLOAT_TYPE__)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
}

@@Arc tangent of Y/X
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__atan2)][nothrow][crtbuiltin]
[requires_include(<ieee754.h>)][decl_include(<libm/atan2.h>)][userimpl]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__))]
atan2:(double y, double x) -> double {
	COMPILER_IMPURE(); /* XXX: Math error handling */
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_atan2((__IEEE754_DOUBLE_TYPE__)y, (__IEEE754_DOUBLE_TYPE__)x);
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
	return (double)__ieee754_atan2f((__IEEE754_FLOAT_TYPE__)y, (__IEEE754_FLOAT_TYPE__)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
}

@@Cosine of X
[attribute(@__DECL_SIMD_cos@)][decl_include(<bits/math-vector.h>)]
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__cos)][nothrow]
[crtbuiltin] cos:(double x) -> double; /* TODO */

@@Sine of X
[attribute(@__DECL_SIMD_sin@)][decl_include(<bits/math-vector.h>)]
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__sin)][nothrow]
[crtbuiltin] sin:(double x) -> double; /* TODO */

@@Tangent of X
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__tan)][nothrow]
[crtbuiltin] tan:(double x) -> double; /* TODO */


[std][ATTR_WUNUSED][ATTR_MCONST][alias(__acosf)][nothrow][crtbuiltin]
acosf:(float x) -> float %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__asinf)][nothrow][crtbuiltin]
asinf:(float x) -> float %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__atanf)][nothrow][crtbuiltin]
[requires_include(<ieee754.h>)][decl_include(<libm/atan.h>)][userimpl][doc_alias(atan)]
[requires(defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__))]
atanf:(float x) -> float {
	COMPILER_IMPURE(); /* XXX: Math error handling */
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (float)__ieee754_atanf((__IEEE754_FLOAT_TYPE__)x);
#else /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ */
	return (float)__ieee754_atan((__IEEE754_DOUBLE_TYPE__)x);
#endif /* !__IEEE754_FLOAT_TYPE_IS_FLOAT__ */
}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__atan2f)][nothrow][crtbuiltin]
[requires_include(<ieee754.h>)][decl_include(<libm/atan2.h>)][userimpl][doc_alias(atan2)]
[requires(defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__))]
atan2f:(float y, float x) -> float {
	COMPILER_IMPURE(); /* XXX: Math error handling */
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (float)__ieee754_atan2f((__IEEE754_FLOAT_TYPE__)y, (__IEEE754_FLOAT_TYPE__)x);
#else /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ */
	return (float)__ieee754_atan2((__IEEE754_DOUBLE_TYPE__)y, (__IEEE754_DOUBLE_TYPE__)x);
#endif /* !__IEEE754_FLOAT_TYPE_IS_FLOAT__ */
}


[std][ATTR_WUNUSED][ATTR_MCONST][alias(__cosf)][nothrow][crtbuiltin]
cosf:(float x) -> float %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__sinf)][nothrow][crtbuiltin]
sinf:(float x) -> float %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__tanf)][nothrow][crtbuiltin]
tanf:(float x) -> float %{auto_block(math)}


%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__acosl)][nothrow][crtbuiltin]
acosl:(long double x) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__asinl)][nothrow][crtbuiltin]
asinl:(long double x) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__atanl)][nothrow][crtbuiltin]
atanl:(long double x) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__atan2l)][nothrow][crtbuiltin]
atan2l:(long double y, long double x) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__cosl)][nothrow][crtbuiltin]
cosl:(long double x) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__sinl)][nothrow][crtbuiltin]
sinl:(long double x) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__tanl)][nothrow][crtbuiltin]
tanl:(long double x) -> long double %{auto_block(math)}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */

%(std, c)
%(std, c)/* Hyperbolic functions. */

@@Hyperbolic cosine of X
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__cosh)][nothrow]
[crtbuiltin] cosh:(double x) -> double; /* TODO */

@@Hyperbolic sine of X
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__sinh)][nothrow]
[crtbuiltin] sinh:(double x) -> double; /* TODO */

@@Hyperbolic tangent of X
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__tanh)][nothrow]
[crtbuiltin] tanh:(double x) -> double; /* TODO */


[std][ATTR_WUNUSED][ATTR_MCONST][alias(__coshf)][nothrow][crtbuiltin]
coshf:(float x) -> float %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__sinhf)][nothrow][crtbuiltin]
sinhf:(float x) -> float %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__tanhf)][nothrow][crtbuiltin]
tanhf:(float x) -> float %{auto_block(math)}


%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__coshl)][nothrow][crtbuiltin]
coshl:(long double x) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__sinhl)][nothrow][crtbuiltin]
sinhl:(long double x) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__tanhl)][nothrow][crtbuiltin]
tanhl:(long double x) -> long double %{auto_block(math)}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */


%(std, c)
%(std, c, ccompat)#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
@@Hyperbolic arc cosine of X
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__acosh)][nothrow]
[crtbuiltin] acosh:(double x) -> double; /* TODO */

@@Hyperbolic arc sine of X
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__asinh)][nothrow]
[crtbuiltin] asinh:(double x) -> double; /* TODO */

@@Hyperbolic arc tangent of X
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__atanh)][nothrow]
[crtbuiltin] atanh:(double x) -> double; /* TODO */


[std][ATTR_WUNUSED][ATTR_MCONST][alias(__acoshf)][nothrow][crtbuiltin]
acoshf:(float x) -> float %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__asinhf)][nothrow][crtbuiltin]
asinhf:(float x) -> float %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__atanhf)][nothrow][crtbuiltin]
atanhf:(float x) -> float %{auto_block(math)}


%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__acoshl)][nothrow][crtbuiltin]
acoshl:(long double x) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__asinhl)][nothrow][crtbuiltin]
asinhl:(long double x) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__atanhl)][nothrow][crtbuiltin]
atanhl:(long double x) -> long double %{auto_block(math)}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

%(std, c)
%(std, c)/* Exponential and logarithmic functions. */

@@Exponential function of X
[attribute(@__DECL_SIMD_exp@)][decl_include(<bits/math-vector.h>)]
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__exp)][nothrow][crtbuiltin]
exp:(double x) -> double; /* TODO */

@@Break VALUE into a normalized fraction and an integral power of 2
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__frexp)][crtbuiltin]
frexp:(double x, int *pexponent) -> double; /* TODO */

@@X times (two to the EXP power)
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__ldexp)][nothrow][crtbuiltin]
ldexp:(double x, int exponent) -> double; /* TODO */

@@Natural logarithm of X
[attribute(@__DECL_SIMD_log@)][decl_include(<bits/math-vector.h>)]
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__log)][nothrow][crtbuiltin]
log:(double x) -> double; /* TODO */

@@Base-ten logarithm of X
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__log10)][nothrow][crtbuiltin]
log10:(double x) -> double; /* TODO */

@@Break VALUE into integral and fractional parts
[std][ATTR_WUNUSED][alias(__modf)][crtbuiltin]
modf:(double x, [nonnull] double *iptr) -> double; /* TODO */

[attribute(@__DECL_SIMD_expf@)][decl_include(<bits/math-vector.h>)]
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__expf)][nothrow][crtbuiltin]
expf:(float x) -> float %{auto_block(math)}

[std][ATTR_WUNUSED][alias(__frexpf)][crtbuiltin]
frexpf:(float x, int *pexponent) -> float %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__ldexpf)][nothrow][crtbuiltin]
ldexpf:(float x, int exponent) -> float %{auto_block(math)}

[attribute(@__DECL_SIMD_logf@)][decl_include(<bits/math-vector.h>)]
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__logf)][nothrow][crtbuiltin]
logf:(float x) -> float %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__log10f)][nothrow][crtbuiltin]
log10f:(float x) -> float %{auto_block(math)}

[std][alias(__modff)][doc_alias(modf)][requires($has_function(modf))][crtbuiltin]
modff:(float x, [nonnull] float *iptr) -> float
%{auto_block(any({
	double ipart;
	float result;
	result = (float)modf(x, &ipart);
	*iptr  = (float)ipart;
	return result;
}))}


%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(@__DECL_SIMD_expl@)][decl_include(<bits/math-vector.h>)]
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__expl)][nothrow][crtbuiltin]
expl:(long double x) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__frexpl)][crtbuiltin]
frexpl:(long double x, int *pexponent) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__ldexpl)][nothrow][crtbuiltin]
ldexpl:(long double x, int exponent) -> long double %{auto_block(math)}

[attribute(@__DECL_SIMD_logl@)][decl_include(<bits/math-vector.h>)]
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__logl)][nothrow][crtbuiltin]
logl:(long double x) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__log10l)][nothrow][crtbuiltin]
log10l:(long double x) -> long double %{auto_block(math)}

[std][alias(__modfl)]
[if(defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), alias(__modf, modf)]
[doc_alias(modf)][requires($has_function(modf))][crtbuiltin]
modfl:(long double x, [nonnull] long double *iptr) -> long double
%{auto_block(any({
	double ipart;
	long double result;
	result = (long double)modf(x, &ipart);
	*iptr  = (long double)ipart;
	return result;
}))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */


%(std, c)
%(std, c, ccompat)#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
@@Return exp(X) - 1
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__expm1)][nothrow][crtbuiltin]
expm1:(double x) -> double; /* TODO */

@@Return log(1 + X)
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__log1p)][nothrow][crtbuiltin]
log1p:(double x) -> double; /* TODO */

@@Return the base 2 signed integral exponent of X
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__logb, _logb)][nothrow][crtbuiltin]
logb:(double x) -> double; /* TODO */


[std][ATTR_WUNUSED][ATTR_MCONST][alias(__expm1f)][nothrow][crtbuiltin]
expm1f:(float x) -> float %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__log1pf)][nothrow][crtbuiltin]
log1pf:(float x) -> float %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__logbf)][nothrow][crtbuiltin]
logbf:(float x) -> float %{auto_block(math)}


%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__expm1l)][nothrow][crtbuiltin]
expm1l:(long double x) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__log1pl)][nothrow][crtbuiltin]
log1pl:(long double x) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__logbl)][nothrow][crtbuiltin]
logbl:(long double x) -> long double %{auto_block(math)}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

%(std, c)
%(std, c, ccompat)#ifdef __USE_ISOC99
@@Compute base-2 exponential of X
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__exp2)][nothrow][crtbuiltin]
exp2:(double x) -> double; /* TODO */

@@Compute base-2 logarithm of X
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__log2)][nothrow][crtbuiltin]
log2:(double x) -> double; /* TODO */


[std][ATTR_WUNUSED][ATTR_MCONST][alias(__exp2f)][nothrow][crtbuiltin]
exp2f:(float x) -> float %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__log2f)][nothrow][crtbuiltin]
log2f:(float x) -> float %{auto_block(math)}


%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__exp2l)][nothrow][crtbuiltin]
exp2l:(long double x) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__log2l)][nothrow][crtbuiltin]
log2l:(long double x) -> long double %{auto_block(math)}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_ISOC99 */

%(std, c)
%(std, c)/* Power functions. */

@@Return X to the Y power
[attribute(@__DECL_SIMD_pow@)][decl_include(<bits/math-vector.h>)]
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__pow)][nothrow][crtbuiltin]
[requires_include(<ieee754.h>)][decl_include(<libm/pow.h>)][userimpl]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__))]
pow:(double x, double y) -> double {
	COMPILER_IMPURE(); /* XXX: Math error handling */
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_pow((__IEEE754_DOUBLE_TYPE__)x, (__IEEE754_DOUBLE_TYPE__)y);
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
	return (double)__ieee754_powf((__IEEE754_FLOAT_TYPE__)x, (__IEEE754_FLOAT_TYPE__)y);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
}


@@Return the square root of X
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__sqrt)][nothrow][crtbuiltin]
[requires_include(<ieee754.h>)][decl_include(<libm/sqrt.h>)][userimpl]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__))]
sqrt:(double x) -> double {
	COMPILER_IMPURE(); /* XXX: Math error handling */
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_sqrt((__IEEE754_DOUBLE_TYPE__)x);
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
	return (double)__ieee754_sqrtf((__IEEE754_FLOAT_TYPE__)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
}

[attribute(@__DECL_SIMD_powf@)][decl_include(<bits/math-vector.h>)][doc_alias(pow)]
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__powf)][nothrow][crtbuiltin]
[requires_include(<ieee754.h>)][decl_include(<libm/pow.h>)][userimpl]
[requires(defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__))]
powf:(float x, float y) -> float {
	COMPILER_IMPURE(); /* XXX: Math error handling */
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (float)__ieee754_powf((__IEEE754_FLOAT_TYPE__)x, (__IEEE754_FLOAT_TYPE__)y);
#else /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ */
	return (float)__ieee754_pow((__IEEE754_DOUBLE_TYPE__)x, (__IEEE754_DOUBLE_TYPE__)y);
#endif /* !__IEEE754_FLOAT_TYPE_IS_FLOAT__ */
}


[std][ATTR_WUNUSED][ATTR_MCONST][alias(__sqrtf)][nothrow][crtbuiltin][doc_alias(sqrt)]
[requires_include(<ieee754.h>)][decl_include(<libm/sqrt.h>)][userimpl]
[requires(defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__))]
sqrtf:(float x) -> float {
	COMPILER_IMPURE(); /* XXX: Math error handling */
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (float)__ieee754_sqrtf((__IEEE754_FLOAT_TYPE__)x);
#else /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ */
	return (float)__ieee754_sqrt((__IEEE754_DOUBLE_TYPE__)x);
#endif /* !__IEEE754_FLOAT_TYPE_IS_FLOAT__ */
}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(@__DECL_SIMD_powl@)][decl_include(<bits/math-vector.h>)]
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__powl)][nothrow][crtbuiltin]
powl:(long double x, long double y) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__sqrtl)][nothrow][crtbuiltin]
sqrtl:(long double x) -> long double %{auto_block(math)}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */


%(std, c)
%(std, c, ccompat)#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
@@Return `sqrt(X*X + Y*Y)'
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__hypot)][nothrow][crtbuiltin]
hypot:(double x, double y) -> double; /* TODO */

[std][ATTR_WUNUSED][ATTR_MCONST][alias(__hypotf)][nothrow][crtbuiltin]
hypotf:(float x, float y) -> float %{auto_block(math)}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][ATTR_WUNUSED][ATTR_MCONST][alias(__hypotl)][nothrow][crtbuiltin]
hypotl:(long double x, long double y) -> long double %{auto_block(math)}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN || __USE_ISOC99 */


%(std, c)
%(std, c, ccompat)#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
@@Return the cube root of X
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__cbrt)][crtbuiltin]
[requires_include(<ieee754.h>)][decl_include(<libm/cbrt.h>)][userimpl]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__))]
cbrt:(double x) -> double {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_cbrt((__IEEE754_DOUBLE_TYPE__)x);
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
	return (double)__ieee754_cbrtf((__IEEE754_FLOAT_TYPE__)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__cbrtf)][crtbuiltin][doc_alias(cbrt)]
[requires_include(<ieee754.h>)][decl_include(<libm/cbrt.h>)][userimpl]
[requires(defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__))]
cbrtf:(float x) -> float {
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (float)__ieee754_cbrtf((__IEEE754_FLOAT_TYPE__)x);
#else /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ */
	return (float)__ieee754_cbrt((__IEEE754_DOUBLE_TYPE__)x);
#endif /* !__IEEE754_FLOAT_TYPE_IS_FLOAT__ */
}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__cbrtl)][crtbuiltin]
cbrtl:(long double x) -> long double %{auto_block(math)}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

%(std, c)
%(std, c)/* Nearest integer, absolute value, and remainder functions. */

@@Smallest integral value not less than X
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__ceil)]
[dependency_include(<hybrid/typecore.h>)][crtbuiltin]
ceil:(double x) -> double {
	double result;
	result = (double)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result < x)
		result += 1.0;
	return (double)result;
}

@@Absolute value of X
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__fabs)][crtbuiltin]
[decl_include(<libm/fabs.h>)][userimpl]
fabs:(double x) -> double {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_fabs((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (double)__ieee754_fabsf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	return x < 0.0 ? -x : x;
#endif /* !... */
}

@@Largest integer not greater than X
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__floor)]
[dependency_include(<hybrid/typecore.h>)][crtbuiltin]
floor:(double x) -> double {
	double result;
	result = (double)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result > x)
		result -= 1.0;
	return (double)result;
}

@@Floating-point modulo remainder of X/Y
[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__fmod)][crtbuiltin]
[requires_include(<ieee754.h>)][decl_include(<libm/fmod.h>)][userimpl]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__))]
fmod:(double x, double y) -> double {
	COMPILER_IMPURE(); /* XXX: Math error handling */
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_fmod((__IEEE754_DOUBLE_TYPE__)x, (__IEEE754_DOUBLE_TYPE__)y);
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
	return (double)__ieee754_fmodf((__IEEE754_FLOAT_TYPE__)x, (__IEEE754_FLOAT_TYPE__)y);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__ceilf)][crtbuiltin]
ceilf:(float x) -> float %{copy(%auto, math)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__fabsf)][crtbuiltin][doc_alias(fabs)]
[decl_include(<libm/fabs.h>)][userimpl]
fabsf:(float x) -> float {
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (float)__ieee754_fabsf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (float)__ieee754_fabs((__IEEE754_DOUBLE_TYPE__)x);
#else /* ... */
	return x < 0.0f ? -x : x;
#endif /* !... */
}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__floorf)][crtbuiltin]
floorf:(float x) -> float %{copy(%auto, math)}

[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__fmodf)][doc_alias(fmod)]
[requires_include(<ieee754.h>)][decl_include(<libm/fmod.h>)][userimpl][crtbuiltin]
[requires(defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__))]
fmodf:(float x, float y) -> float {
	COMPILER_IMPURE(); /* XXX: Math error handling */
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (float)__ieee754_fmodf((__IEEE754_FLOAT_TYPE__)x, (__IEEE754_FLOAT_TYPE__)y);
#else /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ */
	return (float)__ieee754_fmod((__IEEE754_DOUBLE_TYPE__)x, (__IEEE754_DOUBLE_TYPE__)y);
#endif /* !__IEEE754_FLOAT_TYPE_IS_FLOAT__ */
}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__ceill)][crtbuiltin]
ceill:(long double x) -> long double %{copy(%auto, math)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__fabsl)][crtbuiltin]
[decl_include(<libm/fabs.h>)][userimpl][doc_alias(copysign)]
fabsl:(long double x) -> long double {
#ifdef __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return (long double)__ieee754_fabs((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return (long double)__ieee754_fabsf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	return x < 0.0L ? -x : x;
#endif /* !... */
}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__floorl)][crtbuiltin]
floorl:(long double x) -> long double %{copy(%auto, math)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__fmodl)][crtbuiltin]
fmodl:(long double x, long double y) -> long double %{auto_block(math)}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */


%(std, c)
%(std, c, ccompat)#ifdef __USE_ISOC99
@@Return X with its signed changed to Y's
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__copysign, _copysign)]
[decl_include(<libm/copysign.h>)][userimpl][crtbuiltin]
copysign:(double num, double sign) -> double {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_copysign((__IEEE754_DOUBLE_TYPE__)num, (__IEEE754_DOUBLE_TYPE__)sign);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (double)__ieee754_copysignf((__IEEE754_FLOAT_TYPE__)num, (__IEEE754_FLOAT_TYPE__)sign);
#else /* ... */
	if ((num < 0.0) != (sign < 0.0))
		num = -num;
	return num;
#endif /* !... */
}

@@Return representation of qNaN for double type
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__nan)]
[dependency_include(<bits/nan.h>)][crtbuiltin]
nan:(char const *tagb) -> double {
	(void)tagb;
	return (double)@NAN@;
}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__copysignf)][crtbuiltin]
[decl_include(<libm/copysign.h>)][userimpl][doc_alias(copysign)]
copysignf:(float num, float sign) -> float {
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (float)__ieee754_copysignf((__IEEE754_FLOAT_TYPE__)num, (__IEEE754_FLOAT_TYPE__)sign);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (float)__ieee754_copysign((__IEEE754_DOUBLE_TYPE__)num, (__IEEE754_DOUBLE_TYPE__)sign);
#else /* ... */
	if ((num < 0.0f) != (sign < 0.0f))
		num = -num;
	return num;
#endif /* !... */
}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__nanf)][crtbuiltin]
nanf:(char const *tagb) -> float %{copy(%auto, math)}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__copysignl)][crtbuiltin]
[decl_include(<libm/copysign.h>)][userimpl][doc_alias(copysign)]
copysignl:(long double num, long double sign) -> long double {
#ifdef __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return (long double)__ieee754_copysign((__IEEE754_DOUBLE_TYPE__)num, (__IEEE754_DOUBLE_TYPE__)sign);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return (long double)__ieee754_copysignf((__IEEE754_FLOAT_TYPE__)num, (__IEEE754_FLOAT_TYPE__)sign);
#else /* ... */
	if ((num < 0.0L) != (sign < 0.0L))
		num = -num;
	return num;
#endif /* !... */
}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__nanl)][crtbuiltin]
nanl:(char const *tagb) -> long double %{copy(%auto, math)}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_ISOC99 */

%(std, c)
%(std, c)/* Error and gamma functions. */
%(std, c, ccompat)#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__erf)][crtbuiltin]
erf:(double x) -> double; /* TODO */

[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__erfc)][crtbuiltin]
erfc:(double x) -> double; /* TODO */

[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__lgamma, __gamma, gamma)][crtbuiltin]
lgamma:(double x) -> double; /* TODO */


[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__erff)][crtbuiltin]
erff:(float x) -> float %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__erfcf)][crtbuiltin]
erfcf:(float x) -> float %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__lgammaf, __gammaf, gammaf)][crtbuiltin]
lgammaf:(float x) -> float %{auto_block(math)}


%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__erfl)][crtbuiltin]
erfl:(long double x) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__erfcl)][crtbuiltin]
erfcl:(long double x) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__lgammal, __gammal, gammal)][crtbuiltin]
lgammal:(long double x) -> long double %{auto_block(math)}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN || __USE_ISOC99 */

%(std, c, ccompat)#ifdef __USE_ISOC99
@@True gamma function
[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__tgamma)][crtbuiltin]
tgamma:(double x) -> double; /* TODO */

[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__tgammaf)][crtbuiltin]
tgammaf:(float x) -> float %{auto_block(math)}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__tgammal)][crtbuiltin]
tgammal:(long double x) -> long double %{auto_block(math)}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_ISOC99 */

%(std, c)
%(std, c, ccompat)#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)

@@Return the integer nearest X in the direction of the prevailing rounding mode
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__rint)][crtbuiltin]
[requires_include(<ieee754.h>)][decl_include(<libm/rint.h>)][userimpl]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__))]
rint:(double x) -> double {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_rint((__IEEE754_DOUBLE_TYPE__)x);
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
	return (double)__ieee754_rintf((__IEEE754_FLOAT_TYPE__)x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
}


@@Return X + epsilon if X < Y, X - epsilon if X > Y
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__nextafter, _nextafter)][crtbuiltin]
nextafter:(double x, double y) -> double; /* TODO */

@@Return the remainder of integer divison X / Y with infinite precision
[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__remainder)][crtbuiltin]
remainder:(double x, double y) -> double; /* TODO */

@@Return the binary exponent of X, which must be nonzero
[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__ilogb)][crtbuiltin]
ilogb:(double x) -> int; /* TODO */

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__rintf)][crtbuiltin]
[requires_include(<ieee754.h>)][decl_include(<libm/rint.h>)][userimpl][doc_alias(rint)]
[requires(defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__))]
rintf:(float x) -> float {
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (double)__ieee754_rintf((__IEEE754_FLOAT_TYPE__)x);
#else /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ */
	return (double)__ieee754_rint((__IEEE754_DOUBLE_TYPE__)x);
#endif /* !__IEEE754_FLOAT_TYPE_IS_FLOAT__ */
}


[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__nextafterf)][crtbuiltin]
nextafterf:(float x, float y) -> float %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__remainderf)][crtbuiltin]
remainderf:(float x, float y) -> float %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__ilogbf)][crtbuiltin]
ilogbf:(float x) -> int %{auto_block(math)}


%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__rintl)][crtbuiltin]
rintl:(long double x) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__nextafterl)][crtbuiltin]
nextafterl:(long double x, long double y) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__remainderl)][crtbuiltin]
remainderl:(long double x, long double y) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__ilogbl)][crtbuiltin]
ilogbl:(long double x) -> int %{auto_block(math)}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */


%(std, c)
%(std, c, ccompat)#ifdef __USE_ISOC99

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__nexttoward)][crtbuiltin]
nexttoward:(double x, long double y) -> double; /* TODO */

@@Return X times (2 to the Nth power)
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__scalbn)][crtbuiltin]
[requires_include(<ieee754.h>)][decl_include(<libm/scalbn.h>)][userimpl]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__))]
scalbn:(double x, int n) -> double {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_scalbn((__IEEE754_DOUBLE_TYPE__)x, n);
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
	return (double)__ieee754_scalbnf((__IEEE754_FLOAT_TYPE__)x, n);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
}

@@Return X times (2 to the Nth power)
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__scalbln)][crtbuiltin]
[requires_include(<ieee754.h>)][decl_include(<libm/scalbn.h>)][userimpl]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__))]
scalbln:(double x, long int n) -> double {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_scalbln((__IEEE754_DOUBLE_TYPE__)x, n);
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
	return (double)__ieee754_scalblnf((__IEEE754_FLOAT_TYPE__)x, n);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
}

@@Round X to integral value in floating-point format using current
@@rounding direction, but do not raise inexact exception
[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__nearbyint)][crtbuiltin]
nearbyint:(double x) -> double; /* TODO */

@@Round X to nearest integral value, rounding halfway cases away from zero
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__round)]
[dependency_include(<hybrid/typecore.h>)][crtbuiltin]
round:(double x) -> double {
	double result;
	result = (double)(__INTMAX_TYPE__)x;
	if (x < 0) {
		/* result >= x */
		if ((result - x) >= 0.5)
			result -= 1.0;
	} else {
		/* result <= x */
		if ((x - result) >= 0.5)
			result += 1.0;
	}
	return result;
}

@@Round X to the integral value in floating-point
@@format nearest but not larger in magnitude
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__trunc)]
[dependency_include(<hybrid/typecore.h>)][crtbuiltin]
trunc:(double x) -> double {
	return (double)(__INTMAX_TYPE__)x;
}

@@Compute remainder of X and Y and put in *QUO a value with sign
@@of x/y and magnitude congruent `mod 2^n' to the magnitude of
@@the integral quotient x/y, with n >= 3
[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__remquo)][crtbuiltin]
remquo:(double x, double y, int *pquo) -> double; /* TODO */

@@Round X to nearest integral value according to current rounding direction
[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__lrint)][crtbuiltin]
lrint:(double x) -> long int; /* TODO */

@@Round X to nearest integral value, rounding halfway cases away from zero
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__lround)][crtbuiltin]
lround:(double x) -> long int {
	return (long int)round(x);
}

@@Return positive difference between X and Y
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__fdim)][crtbuiltin][userimpl]
fdim:(double x, double y) -> double {
	return fabs(y - x);
}

@@Return maximum numeric value from X and Y
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__fmax)][crtbuiltin]
fmax:(double x, double y) -> double {
	return x < y ? y : x;
}

@@Return minimum numeric value from X and Y
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__fmin)][crtbuiltin]
fmin:(double x, double y) -> double {
	return x < y ? x : y;
}

@@Multiply-add function computed as a ternary operation
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__fma)][crtbuiltin]
fma:(double x, double y, double z) -> double {
	return (x * y) + z;
}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGLONG
@@Round X to nearest integral value according to current rounding direction
[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__llrint)][crtbuiltin]
llrint:(double x) -> __LONGLONG; /* TODO */

@@Round X to nearest integral value, rounding halfway cases away from zero
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__llround)][crtbuiltin]
llround:(double x) -> __LONGLONG {
	return (__LONGLONG)round(x);
}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGLONG */

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__nexttowardf)][crtbuiltin]
nexttowardf:(float x, long double y) -> float %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__scalbnf)][crtbuiltin][doc_alias(scalbn)]
[requires_include(<ieee754.h>)][decl_include(<libm/scalbn.h>)][userimpl]
[requires(defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__))]
scalbnf:(float x, int n) -> float {
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (float)__ieee754_scalbnf((__IEEE754_FLOAT_TYPE__)x, n);
#else /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ */
	return (float)__ieee754_scalbn((__IEEE754_DOUBLE_TYPE__)x, n);
#endif /* !__IEEE754_FLOAT_TYPE_IS_FLOAT__ */
}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__scalblnf)][crtbuiltin][doc_alias(scalbln)]
[requires_include(<ieee754.h>)][decl_include(<libm/scalbn.h>)][userimpl]
[requires(defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__))]
scalblnf:(float x, long int n) -> float {
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (float)__ieee754_scalblnf((__IEEE754_FLOAT_TYPE__)x, n);
#else /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ */
	return (float)__ieee754_scalbln((__IEEE754_DOUBLE_TYPE__)x, n);
#endif /* !__IEEE754_FLOAT_TYPE_IS_FLOAT__ */
}

[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__nearbyintf)][crtbuiltin]
nearbyintf:(float x) -> float %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__roundf)][crtbuiltin]
roundf:(float x) -> float %{copy(%auto, double2float)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__truncf)][crtbuiltin]
truncf:(float x) -> float %{copy(%auto, double2float)}

[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__remquof)][crtbuiltin]
remquof:(float x, float y, int *pquo) -> float %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__lrintf)][crtbuiltin]
lrintf:(float x) -> long int %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__lroundf)][crtbuiltin]
lroundf:(float x) -> long int %{copy(%auto, double2float)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__fdimf)][crtbuiltin][userimpl]
fdimf:(float x, float y) -> float %{copy(%auto, math)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__fmaxf)][crtbuiltin]
fmaxf:(float x, float y) -> float %{copy(%auto, double2float)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__fminf)][crtbuiltin]
fminf:(float x, float y) -> float %{copy(%auto, double2float)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__fmaf)][crtbuiltin]
fmaf:(float x, float y, float z) -> float %{copy(%auto, double2float)}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGLONG
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__llrintf)][crtbuiltin]
llrintf:(float x) -> __LONGLONG %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__llroundf)][crtbuiltin]
llroundf:(float x) -> __LONGLONG %{copy(%auto, math)}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGLONG */

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__nexttowardl)][crtbuiltin]
nexttowardl:(long double x, long double y) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__scalbnl)][crtbuiltin]
scalbnl:(long double x, int n) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__scalblnl)][crtbuiltin]
scalblnl:(long double x, long int n) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__nearbyintl)][crtbuiltin]
nearbyintl:(long double x) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__roundl)][crtbuiltin]
roundl:(long double x) -> long double %{copy(%auto, math)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__truncl)][crtbuiltin]
truncl:(long double x) -> long double %{copy(%auto, math)}

[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__remquol)][crtbuiltin]
remquol:(long double x, long double y, int *pquo) -> long double %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__lrintl)][crtbuiltin]
lrintl:(long double x) -> long int %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__lroundl)][crtbuiltin]
lroundl:(long double x) -> long int %{copy(%auto, math)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__fdiml)][userimpl][crtbuiltin]
fdiml:(long double x, long double y) -> long double %{copy(%auto, math)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__fmaxl)][crtbuiltin]
fmaxl:(long double x, long double y) -> long double %{copy(%auto, math)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__fminl)][crtbuiltin]
fminl:(long double x, long double y) -> long double %{copy(%auto, math)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__fmal)][crtbuiltin]
fmal:(long double x, long double y, long double z) -> long double %{copy(%auto, math)}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGLONG
[std][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__llrintl)][crtbuiltin]
llrintl:(long double x) -> __LONGLONG %{auto_block(math)}

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__llroundl)][crtbuiltin]
llroundl:(long double x) -> __LONGLONG %{copy(%auto, math)}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGLONG */
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_ISOC99 */



/* C++ overload aliases */
%(std)#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_MATH_H_PROTO)
%(std)extern "C++" {
[std][overload_alias] acos:(*) = acosf;
[std][overload_alias] asin:(*) = asinf;
[std][overload_alias] atan:(*) = atanf;
[std][overload_alias] atan2:(*) = atan2f;
[std][overload_alias] cos:(*) = cosf;
[std][overload_alias] sin:(*) = sinf;
[std][overload_alias] tan:(*) = tanf;
[std][overload_alias] cosh:(*) = coshf;
[std][overload_alias] sinh:(*) = sinhf;
[std][overload_alias] tanh:(*) = tanhf;
[std][overload_alias] exp:(*) = expf;
[std][overload_alias] frexp:(*) = frexpf;
[std][overload_alias] ldexp:(*) = ldexpf;
[std][overload_alias] log:(*) = logf;
[std][overload_alias] log10:(*) = log10f;
[std][overload_alias] modf:(*) = modff;
[std][overload_alias] pow:(*) = powf;
[std][overload_alias] sqrt:(*) = sqrtf;
[std][overload_alias] ceil:(*) = ceilf;
[std][overload_alias] fabs:(*) = fabsf;
[std][overload_alias] floor:(*) = floorf;
[std][overload_alias] fmod:(*) = fmodf;

%(std, c)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][overload_alias] acos:(*) = acosl;
[std][overload_alias] asin:(*) = asinl;
[std][overload_alias] atan:(*) = atanl;
[std][overload_alias] atan2:(*) = atan2l;
[std][overload_alias] cos:(*) = cosl;
[std][overload_alias] sin:(*) = sinl;
[std][overload_alias] tan:(*) = tanl;
[std][overload_alias] cosh:(*) = coshl;
[std][overload_alias] sinh:(*) = sinhl;
[std][overload_alias] tanh:(*) = tanhl;
[std][overload_alias] exp:(*) = expl;
[std][overload_alias] frexp:(*) = frexpl;
[std][overload_alias] ldexp:(*) = ldexpl;
[std][overload_alias] log:(*) = logl;
[std][overload_alias] log10:(*) = log10l;
[std][overload_alias] modf:(*) = modfl;
[std][overload_alias] pow:(*) = powl;
[std][overload_alias] sqrt:(*) = sqrtl;
[std][overload_alias] ceil:(*) = ceill;
[std][overload_alias] fabs:(*) = fabsl;
[std][overload_alias] floor:(*) = floorl;
[std][overload_alias] fmod:(*) = fmodl;
%(std, c)#endif /* __COMPILER_HAVE_LONGDOUBLE */


%(std, c)#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
[std][overload_alias] acosh:(*) = acoshf;
[std][overload_alias] asinh:(*) = asinhf;
[std][overload_alias] atanh:(*) = atanhf;
[std][overload_alias] expm1:(*) = expm1f;
[std][overload_alias] log1p:(*) = log1pf;
[std][overload_alias] logb:(*) = logbf;
[std][overload_alias] cbrt:(*) = cbrtf;
[std][overload_alias] rint:(*) = rintf;
[std][overload_alias] nextafter:(*) = nextafterf;
[std][overload_alias] remainder:(*) = remainderf;
[std][overload_alias] ilogb:(*) = ilogbf;
%(std, c)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][overload_alias] acosh:(*) = acoshl;
[std][overload_alias] asinh:(*) = asinhl;
[std][overload_alias] atanh:(*) = atanhl;
[std][overload_alias] expm1:(*) = expm1l;
[std][overload_alias] log1p:(*) = log1pl;
[std][overload_alias] logb:(*) = logbl;
[std][overload_alias] cbrt:(*) = cbrtl;
[std][overload_alias] rint:(*) = rintl;
[std][overload_alias] nextafter:(*) = nextafterl;
[std][overload_alias] remainder:(*) = remainderl;
[std][overload_alias] ilogb:(*) = ilogbl;
%(std, c)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c)#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */


%(std, c)#ifdef __USE_ISOC99
[std][overload_alias] exp2:(*) = exp2f;
[std][overload_alias] log2:(*) = log2f;
[std][overload_alias] copysign:(*) = copysignf;
[std][overload_alias] tgamma:(*) = tgammaf;
[std][overload_alias] nexttoward:(*) = nexttowardf;
[std][overload_alias] scalbn:(*) = scalbnf;
[std][overload_alias] scalbln:(*) = scalblnf;
[std][overload_alias] nearbyint:(*) = nearbyintf;
[std][overload_alias] round:(*) = roundf;
[std][overload_alias] trunc:(*) = truncf;
[std][overload_alias] remquo:(*) = remquof;
[std][overload_alias] lrint:(*) = lrintf;
[std][overload_alias] lround:(*) = lroundf;
[std][overload_alias] fdim:(*) = fdimf;
[std][overload_alias] fmax:(*) = fmaxf;
[std][overload_alias] fmin:(*) = fminf;
[std][overload_alias] fma:(*) = fmaf;
%(std, c)#ifdef __COMPILER_HAVE_LONGLONG
[std][overload_alias] llrint:(*) = llrintf;
[std][overload_alias] llround:(*) = llroundf;
%(std, c)#endif /* __COMPILER_HAVE_LONGLONG */
%(std, c)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][overload_alias] exp2:(*) = exp2l;
[std][overload_alias] log2:(*) = log2l;
[std][overload_alias] copysign:(*) = copysignl;
[std][overload_alias] tgamma:(*) = tgammal;
[std][overload_alias] nexttoward:(*) = nexttowardl;
[std][overload_alias] scalbn:(*) = scalbnl;
[std][overload_alias] scalbln:(*) = scalblnl;
[std][overload_alias] nearbyint:(*) = nearbyintl;
[std][overload_alias] round:(*) = roundl;
[std][overload_alias] trunc:(*) = truncl;
[std][overload_alias] remquo:(*) = remquol;
[std][overload_alias] lrint:(*) = lrintl;
[std][overload_alias] lround:(*) = lroundl;
[std][overload_alias] fdim:(*) = fdiml;
[std][overload_alias] fmax:(*) = fmaxl;
[std][overload_alias] fmin:(*) = fminl;
[std][overload_alias] fma:(*) = fmal;
%(std, c)#ifdef __COMPILER_HAVE_LONGLONG
[std][overload_alias] llrint:(*) = llrintl;
[std][overload_alias] llround:(*) = llroundl;
%(std, c)#endif /* __COMPILER_HAVE_LONGLONG */
%(std, c)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c)#endif /* __USE_ISOC99 */


%(std, c)#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
[std][overload_alias] hypot:(*) = hypotf;
[std][overload_alias] erf:(*) = erff;
[std][overload_alias] erfc:(*) = erfcf;
[std][overload_alias] lgamma:(*) = lgammaf;
%(std, c)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][overload_alias] hypot:(*) = hypotl;
[std][overload_alias] erf:(*) = erfl;
[std][overload_alias] erfc:(*) = erfcl;
[std][overload_alias] lgamma:(*) = lgammal;
%(std, c)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c)#endif /* __USE_XOPEN || __USE_ISOC99 */


%(std)} /* extern "C++" */
%(std)#endif /* __cplusplus && __CORRECT_ISO_CPP_MATH_H_PROTO */





%
%#ifdef __USE_GNU
@@Cosine and sine of X
[alias(__sincos)][nothrow]
[attribute(@__DECL_SIMD_sincos@)][decl_include(<bits/math-vector.h>)][crtbuiltin]
sincos:(double x, [nonnull] double *psinx, [nonnull] double *pcosx); /* TODO */

@@A function missing in all standards: compute exponent to base ten
[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__exp10)][crtbuiltin]
exp10:(double x) -> double; /* TODO */

@@Another name occasionally used
[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__pow10)][crtbuiltin]
pow10:(double x) -> double; /* TODO */

[alias(__sincosf)][nothrow][doc_alias(sincos)]
[attribute(@__DECL_SIMD_sincosf@)][decl_include(<bits/math-vector.h>)]
[requires($has_function(sincos))][crtbuiltin]
sincosf:(float x, [nonnull] float *psinx, [nonnull] float *pcosx)
%{auto_block(any({
	double sinx, cosx;
	sincos((double)x, &sinx, &cosx);
	*psinx = (float)sinx;
	*pcosx = (float)cosx;
}))}

[crtbuiltin][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__exp10f)]
exp10f:(float x) -> float %{auto_block(math)}

[crtbuiltin][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__pow10f)]
pow10f:(float x) -> float %{auto_block(math)}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[alias(__sincosl)][nothrow][doc_alias(sincos)]
[attribute(@__DECL_SIMD_sincosl@)][decl_include(<bits/math-vector.h>)]
[if(defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), alias(__sincos, sincos)]
[requires($has_function(sincos))][crtbuiltin]
sincosl:(long double x, [nonnull] long double *psinx, [nonnull] long double *pcosx)
%{auto_block(any({
	double sinx, cosx;
	sincos((double)x, &sinx, &cosx);
	*psinx = (long double)sinx;
	*pcosx = (long double)cosx;
}))}

[crtbuiltin][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__exp10l)]
exp10l:(long double x) -> long double %{auto_block(math)}

[crtbuiltin][ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__pow10l)]
pow10l:(long double x) -> long double %{auto_block(math)}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_GNU */


%
%#ifdef __USE_MISC

%#if !defined(__cplusplus) || !defined(__CORRECT_ISO_CPP11_MATH_H_PROTO_FP) /* isinf conflicts with C++11. */
@@Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity
[ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__isinf)]
[dependency_include(<libm/isinf.h>)][userimpl]
[dependency_include(<bits/huge_val.h>)][crtbuiltin]
isinf:(double x) -> int {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return __ieee754_isinf((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return __ieee754_isinff((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	return x == @HUGE_VAL@;
#endif /* !... */
}
%#endif /* !__cplusplus || !__CORRECT_ISO_CPP11_MATH_H_PROTO_FP */

[ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__isinff)]
[dependency_include(<libm/isinf.h>)][userimpl][doc_alias(isinf)]
[dependency_include(<bits/huge_valf.h>)][crtbuiltin]
isinff:(float x) -> int {
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return __ieee754_isinff((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
	return __ieee754_isinf((__IEEE754_DOUBLE_TYPE__)x);
#else /* ... */
	return x == @HUGE_VALF@;
#endif /* !... */
}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__isinfl)]
[if(defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), alias(__isinf, isinf)]
[dependency_include(<libm/isinf.h>)][userimpl][doc_alias(isinf)]
[dependency_include(<bits/huge_vall.h>)][crtbuiltin]
isinfl:(long double x) -> int {
#ifdef __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__
	return __ieee754_isinff((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
	return __ieee754_isinf((__IEEE754_DOUBLE_TYPE__)x);
#elif 1
	return isinf((double)x);
#else /* ... */
	return x == @HUGE_VALL@;
#endif /* !... */
}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

@@Return nonzero if VALUE is finite and not NaN
[ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__finite, _finite)][crtbuiltin]
[dependency_include(<libm/finite.h>)][userimpl]
finite:(double x) -> int {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return __ieee754_finite((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return __ieee754_finitef((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	return !isinf(x) && !isnan(x);
#endif /* !... */
}

@@Return the remainder of X/Y
[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__drem)][crtbuiltin]
drem:(double x, double y) -> double; /* TODO */

@@Return the fractional part of X after dividing out `ilogb (X)'
[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__significand)][crtbuiltin]
significand:(double x) -> double; /* TODO */

[ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__finitef)][crtbuiltin]
[dependency_include(<libm/finite.h>)][userimpl][doc_alias(finite)]
finitef:(float x) -> int  {
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return __ieee754_finitef((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
	return __ieee754_finite((__IEEE754_DOUBLE_TYPE__)x);
#else /* ... */
	return !isinff(x) && !isnanf(x);
#endif /* !... */
}

[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__dremf)][crtbuiltin]
dremf:(float x, float y) -> float %{auto_block(math)}

[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__significandf)][crtbuiltin]
significandf:(float x) -> float %{auto_block(math)}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__finitel)][crtbuiltin]
[if(defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), alias(__finite, finite)]
[dependency_include(<libm/finite.h>)][userimpl][doc_alias(finite)]
finitel:(long double x) -> int {
#ifdef __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__
	return __ieee754_finitef((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
	return __ieee754_finite((__IEEE754_DOUBLE_TYPE__)x);
#elif 1
	return finite((double)x);
#else /* ... */
	return !isinfl(x) && !isnanl(x);
#endif /* !... */
}

[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__dreml)][crtbuiltin]
dreml:(long double x, long double y) -> long double %{auto_block(math)}

[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__significandl)][crtbuiltin]
significandl:(long double x) -> long double %{auto_block(math)}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */

%
%#if defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
%#if !defined(__cplusplus) || !defined(__CORRECT_ISO_CPP11_MATH_H_PROTO_FP) /* isnan conflicts with C++11. */
@@Return nonzero if VALUE is not a number
[ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__isnan, _isnan)]
[dependency_include(<libm/isnan.h>)][userimpl]
[dependency_include(<bits/nan.h>)][crtbuiltin]
isnan:(double x) -> int {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return __ieee754_isnan((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return __ieee754_isnanf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	return x == (double)@NAN@;
#endif /* !... */
}
%#endif /* !cplusplus || !__CORRECT_ISO_CPP11_MATH_H_PROTO_FP */

[ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__isnanf)]
[dependency_include(<libm/isnan.h>)][userimpl][doc_alias(isnan)]
[dependency_include(<bits/nan.h>)][crtbuiltin]
isnanf:(float x) -> int {
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return __ieee754_isnanf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
	return __ieee754_isnan((__IEEE754_DOUBLE_TYPE__)x);
#else /* ... */
	return x == (float)@NAN@;
#endif /* !... */
}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[ATTR_WUNUSED][ATTR_CONST][nothrow][alias(__isnanl)]
[if(defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), alias(__isnan, _isnan, isnan)]
[dependency_include(<libm/isnan.h>)][userimpl][doc_alias(isnan)]
[dependency_include(<bits/nan.h>)][crtbuiltin]
isnanl:(long double x) -> int {
#ifdef __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__
	return __ieee754_isnanf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
	return __ieee754_isnan((__IEEE754_DOUBLE_TYPE__)x);
#elif 1
	return isnan((double)x);
#else /* ... */
	return x == (long double)@NAN@;
#endif /* !... */
}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

%#endif /* __USE_MISC || (__USE_XOPEN && !__USE_XOPEN2K) */

%
%/* Bessel functions. */
%#if defined(__USE_MISC) || (defined(__USE_XOPEN) && __MATH_DECLARING_DOUBLE)
[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__j0)][crtbuiltin]
j0:(double x) -> double; /* TODO */

[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__j1)][crtbuiltin]
j1:(double x) -> double; /* TODO */

[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__jn)][crtbuiltin]
jn:(int n, double x) -> double; /* TODO */

[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__y0)][crtbuiltin]
y0:(double x) -> double; /* TODO */

[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__y1)][crtbuiltin]
y1:(double x) -> double; /* TODO */

[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__yn)][crtbuiltin]
yn:(int n, double x) -> double; /* TODO */


[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__j0f)][crtbuiltin]
j0f:(float x) -> float %{auto_block(math)}

[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__j1f)][crtbuiltin]
j1f:(float x) -> float %{auto_block(math)}

[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__jnf)][crtbuiltin]
jnf:(int n, float x) -> float %{auto_block(math)}

[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__y0f)][crtbuiltin]
y0f:(float x) -> float %{auto_block(math)}

[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__y1f)][crtbuiltin]
y1f:(float x) -> float %{auto_block(math)}

[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__ynf)][crtbuiltin]
ynf:(int n, float x) -> float %{auto_block(math)}


%#ifdef __COMPILER_HAVE_LONGDOUBLE
[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__j0l)][crtbuiltin]
j0l:(long double x) -> long double %{auto_block(math)}

[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__j1l)][crtbuiltin]
j1l:(long double x) -> long double %{auto_block(math)}

[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__jnl)][crtbuiltin]
jnl:(int n, long double x) -> long double %{auto_block(math)}

[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__y0l)][crtbuiltin]
y0l:(long double x) -> long double %{auto_block(math)}

[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__y1l)][crtbuiltin]
y1l:(long double x) -> long double %{auto_block(math)}

[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__ynl)][crtbuiltin]
ynl:(int n, long double x) -> long double %{auto_block(math)}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC || (__USE_XOPEN && __MATH_DECLARING_DOUBLE) */


%
%#if defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
@@Obsolete alias for `lgamma'
[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__gamma, __lgamma)][crtbuiltin]
gamma:(double x) -> double = lgamma;

[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__gammaf, __lgammaf)][crtbuiltin]
gammaf:(float x) -> float = lgammaf;

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__gammal, __lgammal)][crtbuiltin]
gammal:(long double x) -> long double = lgammal;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC || (__USE_XOPEN && !__USE_XOPEN2K) */

%#ifdef __USE_MISC
@@Reentrant version of lgamma. This function uses the global variable
@@`signgam'. The reentrant version instead takes a pointer and stores
@@the value through it
[ATTR_WUNUSED][alias(__lgamma_r)][crtbuiltin]
lgamma_r:(double x, int *signgamp) -> double; /* TODO */

[ATTR_WUNUSED][alias(__lgammaf_r)][crtbuiltin]
lgammaf_r:(float x, int *signgamp) -> float %{auto_block(math(float, lgamma_r))}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[ATTR_WUNUSED][alias(__lgammal_r)][crtbuiltin]
lgammal_r:(long double x, int *signgamp) -> long double %{auto_block(math(long double, lgamma_r))}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */

%
%#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8))
@@Return X times (2 to the Nth power)
[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__scalb, _scalb)][crtbuiltin]
[requires_include(<ieee754.h>)][decl_include(<libm/scalb.h>)][userimpl]
[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__))]
scalb:(double x, double fn) -> double {
	COMPILER_IMPURE(); /* XXX: Math error handling */
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_scalb((__IEEE754_DOUBLE_TYPE__)x, (__IEEE754_DOUBLE_TYPE__)fn);
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
	return (double)__ieee754_scalbf((__IEEE754_FLOAT_TYPE__)x, (__IEEE754_FLOAT_TYPE__)fn);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
}

%#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K8) */
%#ifdef __USE_MISC
[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__scalbf, _scalbf)][doc_alias(scalb)]
[requires_include(<ieee754.h>)][decl_include(<libm/scalb.h>)][userimpl][crtbuiltin]
[requires(defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__))]
scalbf:(float x, float fn) -> float {
	COMPILER_IMPURE(); /* XXX: Math error handling */
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (float)__ieee754_scalbf((__IEEE754_FLOAT_TYPE__)x, (__IEEE754_FLOAT_TYPE__)fn);
#else /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ */
	return (float)__ieee754_scalb((__IEEE754_DOUBLE_TYPE__)x, (__IEEE754_DOUBLE_TYPE__)fn);
#endif /* !__IEEE754_FLOAT_TYPE_IS_FLOAT__ */
}


%#ifdef __COMPILER_HAVE_LONGDOUBLE
[ATTR_WUNUSED][ATTR_MCONST][nothrow][alias(__scalbl)]
[if(defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), alias(_scalb)][crtbuiltin]
scalbl:(long double x, long double n) -> long double %{auto_block(math)}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */








%
%
%
%#if 1 /* GLIBc aliases */
[attribute(*)][alias(*)] __acos:(*) = acos;
[attribute(*)][alias(*)] __asin:(*) = asin;
[attribute(*)][alias(*)] __atan:(*) = atan;
[attribute(*)][alias(*)] __atan2:(*) = atan2;
[attribute(*)][alias(*)] __cos:(*) = cos;
[attribute(*)][alias(*)] __sin:(*) = sin;
[attribute(*)][alias(*)] __tan:(*) = tan;
[attribute(*)][alias(*)] __cosh:(*) = cosh;
[attribute(*)][alias(*)] __sinh:(*) = sinh;
[attribute(*)][alias(*)] __tanh:(*) = tanh;
[attribute(*)][alias(*)] __acosf:(*) = acosf;
[attribute(*)][alias(*)] __asinf:(*) = asinf;
[attribute(*)][alias(*)] __atanf:(*) = atanf;
[attribute(*)][alias(*)] __atan2f:(*) = atan2f;
[attribute(*)][alias(*)] __cosf:(*) = cosf;
[attribute(*)][alias(*)] __sinf:(*) = sinf;
[attribute(*)][alias(*)] __tanf:(*) = tanf;
[attribute(*)][alias(*)] __coshf:(*) = coshf;
[attribute(*)][alias(*)] __sinhf:(*) = sinhf;
[attribute(*)][alias(*)] __tanhf:(*) = tanhf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] __acosl:(*) = acosl;
[attribute(*)][alias(*)] __asinl:(*) = asinl;
[attribute(*)][alias(*)] __atanl:(*) = atanl;
[attribute(*)][alias(*)] __atan2l:(*) = atan2l;
[attribute(*)][alias(*)] __cosl:(*) = cosl;
[attribute(*)][alias(*)] __sinl:(*) = sinl;
[attribute(*)][alias(*)] __tanl:(*) = tanl;
[attribute(*)][alias(*)] __coshl:(*) = coshl;
[attribute(*)][alias(*)] __sinhl:(*) = sinhl;
[attribute(*)][alias(*)] __tanhl:(*) = tanhl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#ifdef __USE_GNU
[attribute(*)][alias(*)] __sincos:(*) = sincos;
[attribute(*)][alias(*)] __sincosf:(*) = sincosf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] __sincosl:(*) = sincosl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_GNU */

%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
[attribute(*)][alias(*)] __acosh:(*) = acosh;
[attribute(*)][alias(*)] __asinh:(*) = asinh;
[attribute(*)][alias(*)] __atanh:(*) = atanh;
[attribute(*)][alias(*)] __acoshf:(*) = acoshf;
[attribute(*)][alias(*)] __asinhf:(*) = asinhf;
[attribute(*)][alias(*)] __atanhf:(*) = atanhf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] __acoshl:(*) = acoshl;
[attribute(*)][alias(*)] __asinhl:(*) = asinhl;
[attribute(*)][alias(*)] __atanhl:(*) = atanhl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

[attribute(*)][alias(*)] __exp:(*) = exp;
[attribute(*)][alias(*)] __frexp:(*) = frexp;
[attribute(*)][alias(*)] __ldexp:(*) = ldexp;
[attribute(*)][alias(*)] __log:(*) = log;
[attribute(*)][alias(*)] __log10:(*) = log10;
[attribute(*)][alias(*)] __modf:(*) = modf;
[attribute(*)][alias(*)] __expf:(*) = expf;
[attribute(*)][alias(*)] __frexpf:(*) = frexpf;
[attribute(*)][alias(*)] __ldexpf:(*) = ldexpf;
[attribute(*)][alias(*)] __logf:(*) = logf;
[attribute(*)][alias(*)] __log10f:(*) = log10f;
[attribute(*)][alias(*)] __modff:(*) = modff;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] __expl:(*) = expl;
[attribute(*)][alias(*)] __frexpl:(*) = frexpl;
[attribute(*)][alias(*)] __ldexpl:(*) = ldexpl;
[attribute(*)][alias(*)] __logl:(*) = logl;
[attribute(*)][alias(*)] __log10l:(*) = log10l;
[attribute(*)][alias(*)] __modfl:(*) = modfl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

%
%#ifdef __USE_GNU
[attribute(*)][alias(*)] __exp10:(*) = exp10;
[attribute(*)][alias(*)] __pow10:(*) = pow10;
[attribute(*)][alias(*)] __exp10f:(*) = exp10f;
[attribute(*)][alias(*)] __pow10f:(*) = pow10f;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] __exp10l:(*) = exp10l;
[attribute(*)][alias(*)] __pow10l:(*) = pow10l;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_GNU */

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
[attribute(*)][alias(*)] __expm1:(*) = expm1;
[attribute(*)][alias(*)] __log1p:(*) = log1p;
[attribute(*)][alias(*)] __logb:(*) = logb;
[attribute(*)][alias(*)] __expm1f:(*) = expm1f;
[attribute(*)][alias(*)] __log1pf:(*) = log1pf;
[attribute(*)][alias(*)] __logbf:(*) = logbf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] __expm1l:(*) = expm1l;
[attribute(*)][alias(*)] __log1pl:(*) = log1pl;
[attribute(*)][alias(*)] __logbl:(*) = logbl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

%
%#ifdef __USE_ISOC99
[attribute(*)][alias(*)] __exp2:(*) = exp2;
[attribute(*)][alias(*)] __log2:(*) = log2;
[attribute(*)][alias(*)] __exp2f:(*) = exp2f;
[attribute(*)][alias(*)] __log2f:(*) = log2f;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] __exp2l:(*) = exp2l;
[attribute(*)][alias(*)] __log2l:(*) = log2l;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_ISOC99 */

[attribute(*)][alias(*)] __pow:(*) = pow;
[attribute(*)][alias(*)] __sqrt:(*) = sqrt;
[attribute(*)][alias(*)] __powf:(*) = powf;
[attribute(*)][alias(*)] __sqrtf:(*) = sqrtf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] __powl:(*) = powl;
[attribute(*)][alias(*)] __sqrtl:(*) = sqrtl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

%
%#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
[attribute(*)][alias(*)] __hypot:(*) = hypot;
[attribute(*)][alias(*)] __hypotf:(*) = hypotf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] __hypotl:(*) = hypotl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_XOPEN || __USE_ISOC99 */

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
[attribute(*)][alias(*)] __cbrt:(*) = cbrt;
[attribute(*)][alias(*)] __cbrtf:(*) = cbrtf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] __cbrtl:(*) = cbrtl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

[attribute(*)][alias(*)] __ceil:(*) = ceil;
[attribute(*)][alias(*)] __fabs:(*) = fabs;
[attribute(*)][alias(*)] __floor:(*) = floor;
[attribute(*)][alias(*)] __fmod:(*) = fmod;
[attribute(*)][alias(*)] __isinf:(*) = isinf;
[attribute(*)][alias(*)] __finite:(*) = finite;
[attribute(*)][alias(*)] __ceilf:(*) = ceilf;
[attribute(*)][alias(*)] __fabsf:(*) = fabsf;
[attribute(*)][alias(*)] __floorf:(*) = floorf;
[attribute(*)][alias(*)] __fmodf:(*) = fmodf;
[attribute(*)][alias(*)] __isinff:(*) = isinff;
[attribute(*)][alias(*)] __finitef:(*) = finitef;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] __ceill:(*) = ceill;
[attribute(*)][alias(*)] __fabsl:(*) = fabsl;
[attribute(*)][alias(*)] __floorl:(*) = floorl;
[attribute(*)][alias(*)] __fmodl:(*) = fmodl;
[attribute(*)][alias(*)] __isinfl:(*) = isinfl;
[attribute(*)][alias(*)] __finitel:(*) = finitel;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

%#ifdef __USE_MISC
[attribute(*)][alias(*)] __drem:(*) = drem;
[attribute(*)][alias(*)] __significand:(*) = significand;
[attribute(*)][alias(*)] __dremf:(*) = dremf;
[attribute(*)][alias(*)] __significandf:(*) = significandf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] __dreml:(*) = dreml;
[attribute(*)][alias(*)] __significandl:(*) = significandl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */

%
%#ifdef __USE_ISOC99
[attribute(*)][alias(*)] __copysign:(*) = copysign;
[attribute(*)][alias(*)] __nan:(*) = nan;
[attribute(*)][alias(*)] __copysignf:(*) = copysignf;
[attribute(*)][alias(*)] __nanf:(*) = nanf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] __copysignl:(*) = copysignl;
[attribute(*)][alias(*)] __nanl:(*) = nanl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_ISOC99 */

%
[attribute(*)][alias(*)] __isnan:(*) = isnan;
[attribute(*)][alias(*)] __isnanf:(*) = isnanf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] __isnanl:(*) = isnanl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

%
%/* Bessel functions. */
%#if defined(__USE_MISC) || defined(__USE_XOPEN)
[attribute(*)][alias(*)] __j0:(*) = j0;
[attribute(*)][alias(*)] __j1:(*) = j1;
[attribute(*)][alias(*)] __jn:(*) = jn;
[attribute(*)][alias(*)] __y0:(*) = y0;
[attribute(*)][alias(*)] __y1:(*) = y1;
[attribute(*)][alias(*)] __yn:(*) = yn;
%#endif /* __USE_MISC || __USE_XOPEN */
%#ifdef __USE_MISC
[attribute(*)][alias(*)] __j0f:(*) = j0f;
[attribute(*)][alias(*)] __j1f:(*) = j1f;
[attribute(*)][alias(*)] __jnf:(*) = jnf;
[attribute(*)][alias(*)] __y0f:(*) = y0f;
[attribute(*)][alias(*)] __y1f:(*) = y1f;
[attribute(*)][alias(*)] __ynf:(*) = ynf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] __j0l:(*) = j0l;
[attribute(*)][alias(*)] __j1l:(*) = j1l;
[attribute(*)][alias(*)] __jnl:(*) = jnl;
[attribute(*)][alias(*)] __y0l:(*) = y0l;
[attribute(*)][alias(*)] __y1l:(*) = y1l;
[attribute(*)][alias(*)] __ynl:(*) = ynl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */

%
%#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
[attribute(*)][alias(*)] __erf:(*) = erf;
[attribute(*)][alias(*)] __erfc:(*) = erfc;
[attribute(*)][alias(*)] __lgamma:(*) = lgamma;
[attribute(*)][alias(*)] __erff:(*) = erff;
[attribute(*)][alias(*)] __erfcf:(*) = erfcf;
[attribute(*)][alias(*)] __lgammaf:(*) = lgammaf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] __erfl:(*) = erfl;
[attribute(*)][alias(*)] __erfcl:(*) = erfcl;
[attribute(*)][alias(*)] __lgammal:(*) = lgammal;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_XOPEN || __USE_ISOC99 */

%
%#ifdef __USE_ISOC99
[attribute(*)][alias(*)] __tgamma:(*) = tgamma;
[attribute(*)][alias(*)] __tgammaf:(*) = tgammaf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] __tgammal:(*) = tgammal;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_ISOC99 */

%
%#if defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
[attribute(*)][alias(*)] __gamma:(*) = lgamma;
[attribute(*)][alias(*)] __gammaf:(*) = lgammaf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] __gammal:(*) = lgammal;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC || (__USE_XOPEN && !__USE_XOPEN2K) */

%#ifdef __USE_MISC
[attribute(*)][alias(*)] __lgamma_r:(*) = lgamma_r;
[attribute(*)][alias(*)] __lgammaf_r:(*) = lgammaf_r;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] __lgammal_r:(*) = lgammal_r;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
[attribute(*)][alias(*)] __rint:(*) = rint;
[attribute(*)][alias(*)] __nextafter:(*) = nextafter;
[attribute(*)][alias(*)] __remainder:(*) = remainder;
[attribute(*)][alias(*)] __ilogb:(*) = ilogb;
[attribute(*)][alias(*)] __rintf:(*) = rintf;
[attribute(*)][alias(*)] __nextafterf:(*) = nextafterf;
[attribute(*)][alias(*)] __remainderf:(*) = remainderf;
[attribute(*)][alias(*)] __ilogbf:(*) = ilogbf;

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] __rintl:(*) = rintl;
[attribute(*)][alias(*)] __nextafterl:(*) = nextafterl;
[attribute(*)][alias(*)] __remainderl:(*) = remainderl;
[attribute(*)][alias(*)] __ilogbl:(*) = ilogbl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */


%
%#ifdef __USE_ISOC99
[attribute(*)][alias(*)] __nexttoward:(*) = nexttoward;
[attribute(*)][alias(*)] __scalbn:(*) = scalbn;
[attribute(*)][alias(*)] __scalbln:(*) = scalbln;
[attribute(*)][alias(*)] __nearbyint:(*) = nearbyint;
[attribute(*)][alias(*)] __round:(*) = round;
[attribute(*)][alias(*)] __trunc:(*) = trunc;
[attribute(*)][alias(*)] __remquo:(*) = remquo;
[attribute(*)][alias(*)] __lrint:(*) = lrint;
[attribute(*)][alias(*)] __lround:(*) = lround;
[attribute(*)][alias(*)] __fdim:(*) = fdim;
[attribute(*)][alias(*)] __fmax:(*) = fmax;
[attribute(*)][alias(*)] __fmin:(*) = fmin;
[attribute(*)][alias(*)] __fma:(*) = fma;

[attribute(*)][alias(*)] __nexttowardf:(*) = nexttowardf;
[attribute(*)][alias(*)] __scalbnf:(*) = scalbnf;
[attribute(*)][alias(*)] __scalblnf:(*) = scalblnf;
[attribute(*)][alias(*)] __nearbyintf:(*) = nearbyintf;
[attribute(*)][alias(*)] __roundf:(*) = roundf;
[attribute(*)][alias(*)] __truncf:(*) = truncf;
[attribute(*)][alias(*)] __remquof:(*) = remquof;
[attribute(*)][alias(*)] __lrintf:(*) = lrintf;
[attribute(*)][alias(*)] __lroundf:(*) = lroundf;
[attribute(*)][alias(*)] __fdimf:(*) = fdimf;
[attribute(*)][alias(*)] __fmaxf:(*) = fmaxf;
[attribute(*)][alias(*)] __fminf:(*) = fminf;
[attribute(*)][alias(*)] __fmaf:(*) = fmaf;

%#ifdef __COMPILER_HAVE_LONGLONG
[attribute(*)][alias(*)] __llrint:(*) = llrint;
[attribute(*)][alias(*)] __llround:(*) = llround;
[attribute(*)][alias(*)] __llrintf:(*) = llrintf;
[attribute(*)][alias(*)] __llroundf:(*) = llroundf;
%#endif /* __COMPILER_HAVE_LONGLONG */

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] __nexttowardl:(*) = nexttowardl;
[attribute(*)][alias(*)] __scalbnl:(*) = scalbnl;
[attribute(*)][alias(*)] __scalblnl:(*) = scalblnl;
[attribute(*)][alias(*)] __nearbyintl:(*) = nearbyintl;
[attribute(*)][alias(*)] __roundl:(*) = roundl;
[attribute(*)][alias(*)] __truncl:(*) = truncl;
[attribute(*)][alias(*)] __remquol:(*) = remquol;
[attribute(*)][alias(*)] __lrintl:(*) = lrintl;
[attribute(*)][alias(*)] __lroundl:(*) = lroundl;
[attribute(*)][alias(*)] __fdiml:(*) = fdiml;
[attribute(*)][alias(*)] __fmaxl:(*) = fmaxl;
[attribute(*)][alias(*)] __fminl:(*) = fminl;
[attribute(*)][alias(*)] __fmal:(*) = fmal;
%#ifdef __COMPILER_HAVE_LONGLONG
[attribute(*)][alias(*)] __llrintl:(*) = llrintl;
[attribute(*)][alias(*)] __llroundl:(*) = llroundl;
%#endif /* __COMPILER_HAVE_LONGLONG */
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_ISOC99 */

%
%#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8))
[attribute(*)][alias(*)] __scalb:(*) = scalb;
%#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K8) */
%#ifdef __USE_MISC
[attribute(*)][alias(*)] __scalbf:(*) = scalbf;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] __scalbl:(*) = scalbl;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */
%#endif /* GLIBc aliases */



%
%
%/* Floating point classification */
%#ifdef __USE_ISOC99
[ATTR_WUNUSED][ATTR_CONST][nothrow][alias(_dclass)]
__fpclassify:(double x) -> int; /* TODO */

[ATTR_WUNUSED][ATTR_CONST][nothrow][alias(_dsign)]
__signbit:(double x) -> int {
	return x < 0.0;
}

[ATTR_WUNUSED][ATTR_CONST][nothrow][alias(_fdclass)]
__fpclassifyf:(float x) -> int %{auto_block(math)}

[ATTR_WUNUSED][ATTR_CONST][nothrow][alias(_fdsign)]
__signbitf:(float x) -> int  {
	return x < 0.0f;
}
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[ATTR_WUNUSED][ATTR_CONST][nothrow][alias(_ldclass)]
__fpclassifyl:(long double x) -> int %{auto_block(math)}

[ATTR_WUNUSED][ATTR_CONST][nothrow][alias(_ldsign)]
__signbitl:(long double x) -> int  {
	return x < 0.0L;
}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_ISOC99 */

%
%#ifdef __USE_GNU
[ATTR_WUNUSED][ATTR_CONST][nothrow]
__issignaling:(double x) -> int; /* TODO */

[ATTR_WUNUSED][ATTR_CONST][nothrow] __issignalingf:(float x) -> int %{auto_block(math)}
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[ATTR_WUNUSED][ATTR_CONST][nothrow] __issignalingl:(long double x) -> int %{auto_block(math)}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_GNU */

[ignore][nouser][noexport][ATTR_WUNUSED][ATTR_CONST]
_dpcomp:(double x, double y) -> int; /* TODO */

[ignore][nouser][noexport][ATTR_WUNUSED][ATTR_CONST]
_fdpcomp:(float x, float y) -> int %{auto_block(math(float, _dpcomp))}
[ignore][nouser][noexport][ATTR_WUNUSED][ATTR_CONST]
_ldpcomp:(long double x, long double y) -> int %{auto_block(math(long double, _dpcomp))}

[nocrt][nouser][noexport][attribute(*)] __dos_dpcomp:(*) = _dpcomp;
[nocrt][nouser][noexport][attribute(*)] __dos_fdpcomp:(*) = _fdpcomp;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[nocrt][nouser][noexport][attribute(*)] __dos_ldpcomp:(*) = _ldpcomp;
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
#elif !defined(__NO_builtin_choose_expr) && \
      !defined(__NO_builtin_types_compatible_p) && \
       defined(__COMPILER_HAVE_TYPEOF)
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __FPFUNC(x, f, d, l) \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (float)0), float), f(x), \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (double)0), double), d(x), l(x)))
#define __FPFUNC2(x, y, f, d, l) \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (y) + (float)0), float), f(x, y), \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (y) + (double)0), double), d(x, y), l(x, y)))
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __FPFUNC(x, f, d, l) \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (float)0), float), f(x), d(x))
#define __FPFUNC2(x, y, f, d, l) \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (y) + (float)0), float), f(x, y), d(x, y))
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#elif defined(__COMPILER_HAVE_LONGDOUBLE)
#define __FPFUNC(x, f, d, l)     (sizeof((x) + (float)0) == sizeof(float) ? f((float)(x)) : \
                                  sizeof((x) + (double)0) == sizeof(double) ? d((double)(x)) : l((long double)(x)))
#define __FPFUNC2(x, y, f, d, l) (sizeof((x) + (y) + (float)0) == sizeof(float) ? f((float)(x), (float)(y)) : \
                                  sizeof((x) + (y) + (double)0) == sizeof(double) ? d((double)(x), (double)(y)) : l((long double)(x), (long double)(y)))
#else /* ... */
#define __FPFUNC(x, f, d, l)     (sizeof((x) + (float)0) == sizeof(float) ? f((float)(x)) : d((double)(x)))
#define __FPFUNC2(x, y, f, d, l) (sizeof((x) + (y) + (float)0) == sizeof(float) ? f((float)(x), (float)(y)) : d((double)(x), (double)(y)))
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
 *  FP_ILOGB0    Expands to a value returned by `ilogb (0.0)'.
 *  FP_ILOGBNAN    Expands to a value returned by `ilogb (NAN)'.
 *
 *  DECIMAL_DIG    Number of decimal digits supported by conversion between
 *      decimal and all internal floating-point formats. */

/* All floating-point numbers can be put in one of these categories. */
}%[enum @undef @macro {
	FP_NAN       = 0,
	FP_INFINITE  = 1,
	FP_ZERO      = 2,
	FP_SUBNORMAL = 3,
	FP_NORMAL    = 4
}]%{




#ifndef __OPTIMIZE_SIZE__
#if __has_builtin(__builtin_signbitf) && \
    __has_builtin(__builtin_signbit) && \
    __has_builtin(__builtin_signbitl)
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
#if defined(__CRT_HAVE___fpclassify) || defined(__CRT_HAVE__dclass)
#define fpclassify(x) __FPFUNC(x, __fpclassifyf, __fpclassify, __fpclassifyl)
#endif /* __CRT_HAVE___fpclassify || __CRT_HAVE__dclass */
#endif /* !fpclassify */

#ifndef signbit
#if defined(__CRT_HAVE___signbit) || defined(__CRT_HAVE__dsign)
#define signbit(x) __FPFUNC(x, __signbitf, __signbit, __signbitl)
#endif /* __CRT_HAVE___signbit || __CRT_HAVE__dsign */
#endif /* !signbit */

#ifndef isnormal
#ifdef fpclassify
#define isnormal(x)  (fpclassify(x) == FP_NORMAL)
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
#define islessgreater(x, y) __XBLOCK({ __typeof__(x) __x = (x); __typeof__(y) __y = (y); __XRETURN !isunordered(__x, __y) &&(__x < __y || __y < __x); })
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
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST int __NOTHROW(__LIBCCALL fpclassify)(long double __x) { return fpclassify(__x); }
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
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL signbit)(long double __x) { return signbit(__x); }
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
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isnormal)(long double __x) { return isnormal(__x); }
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
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isfinite)(long double __x) { return isfinite(__x); }
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
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isnan)(long double __x) { return isnan(__x); }
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
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isinf)(long double __x) { return isinf(__x); }
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
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isunordered)(long double __x, long double __y) { return isunordered(__x, __y); }
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
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isgreater)(long double __x, long double __y) { return isgreater(__x, __y); }
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
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isgreaterequal)(long double __x, long double __y) { return isgreaterequal(__x, __y); }
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
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL isless)(long double __x, long double __y) { return isless(__x, __y); }
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
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL islessequal)(long double __x, long double __y) { return islessequal(__x, __y); }
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
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL islessgreater)(long double __x, long double __y) { return islessgreater(__x, __y); }
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
#ifdef __CRT_HAVE___issignaling
#define issignaling(x) __FPFUNC(x, __issignalingf, __issignaling, __issignalingl)
#endif /* __CRT_HAVE___issignaling */
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
#endif
#endif /* !__USE_MISC */

}


%{
#endif /* __CC__ */

__SYSDECL_END

}
%(c, ccompat)#endif /* !__NO_FPU */
