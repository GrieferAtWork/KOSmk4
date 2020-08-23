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
%[default:section(".text.crt{|.dos}.math.math")]

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
%[define_double_replacement(__DECL_SIMD_cos = __DECL_SIMD_cosf, __DECL_SIMD_cosl)]
%[define_double_replacement(__DECL_SIMD_sin = __DECL_SIMD_sinf, __DECL_SIMD_sinl)]
%[define_double_replacement(__DECL_SIMD_sincos = __DECL_SIMD_sincosf, __DECL_SIMD_sincosl)]
%[define_double_replacement(__DECL_SIMD_log = __DECL_SIMD_logf, __DECL_SIMD_logl)]
%[define_double_replacement(__DECL_SIMD_exp = __DECL_SIMD_expf, __DECL_SIMD_expl)]
%[define_double_replacement(__DECL_SIMD_pow = __DECL_SIMD_powf, __DECL_SIMD_powl)]
%[define_double_replacement(HUGE_VAL = HUGE_VALF, HUGE_VALL)]
%[define_double_replacement(__HUGE_VAL = __HUGE_VALF, __HUGE_VALL)]
%[define_double_replacement(__INFINITY = __INFINITYF, __INFINITYL)]
%[define_double_replacement(__NAN = __NANF, __NANL)]

%(c, ccompat)#ifndef __NO_FPU
%{
#include <features.h>

}%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

}%[insert:prefix(
#include <bits/math-constants.h>
)]%[insert:prefix(
#include <bits/crt/math-vector.h>
)]%{

}%[insert:prefix(
#include <ieee754.h>
)]%{

#ifdef __USE_ISOC99
#include <asm/fp_type.h>  /* __FP_NAN, __FP_INFINITE, ... */
#include <bits/mathdef.h> /* __float_t, __double_t */
#endif /* __USE_ISOC99 */

#ifdef __USE_MISC
#include <asm/crt/math-exception.h>
#include <asm/crt/math-libc_version.h>
#endif /* __USE_MISC */

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


#ifdef __HUGE_VAL
#define HUGE_VAL __HUGE_VAL /* double HUGE_VAL; */
#endif /* __HUGE_VAL */

#ifdef __USE_ISOC99
#ifdef __HUGE_VALF
#define HUGE_VALF __HUGE_VALF /* double HUGE_VALF; */
#endif /* __HUGE_VALF */

#ifdef __HUGE_VALL
#define HUGE_VALL __HUGE_VALL /* double HUGE_VALL; */
#endif /* __HUGE_VALL */

#ifdef __INFINITYF
#define INFINITY __INFINITYF /* float INFINITY; */
#endif /* __INFINITYF */

#ifdef __NANF
#define NAN __NANF /* float NAN; */
#endif /* __NANF */

/* This value is returned by `ilogb(0)'. */
#ifdef __FP_ILOGB0
#define FP_ILOGB0 __FP_ILOGB0 /* int FP_ILOGB0; */
#endif /* __FP_ILOGB0 */

/* This value is returned by `ilogb(NAN)'. */
#ifdef __FP_ILOGBNAN
#define FP_ILOGBNAN __FP_ILOGBNAN /* int FP_ILOGBNAN; */
#endif /* __FP_ILOGBNAN */

/* Define if fma(x, y, z) is at least as ~fast~ as `x * y + z' */
#ifdef __FP_FAST_FMA
#define FP_FAST_FMA 1
#endif /* __FP_FAST_FMA */

/* Define if fmaf(x, y, z) is at least as ~fast~ as `x * y + z' */
#ifdef __FP_FAST_FMAF
#define FP_FAST_FMAF 1
#endif /* __FP_FAST_FMAF */

/* Define if fmal(x, y, z) is at least as ~fast~ as `x * y + z' */
#ifdef __FP_FAST_FMAL
#define FP_FAST_FMAL 1
#endif /* __FP_FAST_FMAL */

#endif /* __USE_ISOC99 */


#ifdef __CC__
}

%[insert:std]

@@Arc cosine of X
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__acos")]]
double acos(double x);

@@Arc sine of X
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__asin")]]
double asin(double x);

@@Arc tangent of X
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__atan")]]
[[impl_include("<libm/fcomp.h>", "<libm/fabs.h>", "<libm/matherr.h>")]]
[[impl_include("<libm/inf.h>", "<libm/atan.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double atan(double x) {
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
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__atan2")]]
[[impl_include("<bits/math-constants.h>", "<libm/matherr.h>")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/atan2.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double  atan2(double y, double x){
	if (__LIBM_LIB_VERSION == __LIBM_SVID && x == 0.0 && y == 0.0)
		return __kernel_standard(y, x, __HUGE_VAL, __LIBM_KMATHERR_ATAN2); /* atan2(+-0,+-0) */
	return __LIBM_MATHFUN2(@atan2@, y, x);
}

@@Cosine of X
[[attribute("__DECL_SIMD_cos"), decl_include("<bits/crt/math-vector.h>")]]
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__cos")]]
double cos(double x); /* TODO */

@@Sine of X
[[attribute("__DECL_SIMD_sin"), decl_include("<bits/crt/math-vector.h>")]]
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__sin")]]
double sin(double x); /* TODO */

@@Tangent of X
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__tan")]]
double tan(double x); /* TODO */


[[std, crtbuiltin, export_alias("__acosf")]] acosf(*) %{generate(double2float("acos"))}
[[std, crtbuiltin, export_alias("__asinf")]] asinf(*) %{generate(double2float("asin"))}
[[std, crtbuiltin, export_alias("__atanf")]] atanf(*) %{generate(double2float("atan"))}
[[std, crtbuiltin, export_alias("__atan2f")]] atan2f(*) %{generate(double2float("atan2"))}
[[std, crtbuiltin, export_alias("__cosf")]] cosf(*) %{generate(double2float("cos"))}
[[std, crtbuiltin, export_alias("__sinf")]] sinf(*) %{generate(double2float("sin"))}
[[std, crtbuiltin, export_alias("__tanf")]] tanf(*) %{generate(double2float("tan"))}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__acosl")]] acosl(*) %{generate(double2ldouble("acos"))}
[[std, crtbuiltin, export_alias("__asinl")]] asinl(*) %{generate(double2ldouble("asin"))}
[[std, crtbuiltin, export_alias("__atanl")]] atanl(*) %{generate(double2ldouble("atan"))}
[[std, crtbuiltin, export_alias("__atan2l")]] atan2l(*) %{generate(double2ldouble("atan2"))}
[[std, crtbuiltin, export_alias("__cosl")]] cosl(*) %{generate(double2ldouble("cos"))}
[[std, crtbuiltin, export_alias("__sinl")]] sinl(*) %{generate(double2ldouble("sin"))}
[[std, crtbuiltin, export_alias("__tanl")]] tanl(*) %{generate(double2ldouble("tan"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */

%(std, c)
%(std, c)/* Hyperbolic functions. */

@@Hyperbolic cosine of X
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__cosh")]]
double cosh(double x); /* TODO */

@@Hyperbolic sine of X
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__sinh")]]
double sinh(double x); /* TODO */

@@Hyperbolic tangent of X
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__tanh")]]
double tanh(double x); /* TODO */

[[std, crtbuiltin, export_alias("__coshf")]] coshf(*) %{generate(double2float("cosh"))}
[[std, crtbuiltin, export_alias("__sinhf")]] sinhf(*) %{generate(double2float("sinh"))}
[[std, crtbuiltin, export_alias("__tanhf")]] tanhf(*) %{generate(double2float("tanh"))}
%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__coshl")]] coshl(*) %{generate(double2ldouble("cosh"))}
[[std, crtbuiltin, export_alias("__sinhl")]] sinhl(*) %{generate(double2ldouble("sinh"))}
[[std, crtbuiltin, export_alias("__tanhl")]] tanhl(*) %{generate(double2ldouble("tanh"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */

%(std, c)
%(std, c, ccompat)#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
@@Hyperbolic arc cosine of X
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__acosh")]]
double acosh(double x); /* TODO */

@@Hyperbolic arc sine of X
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__asinh")]]
double asinh(double x); /* TODO */

@@Hyperbolic arc tangent of X
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__atanh")]]
double atanh(double x); /* TODO */

[[std, crtbuiltin, export_alias("__acoshf")]] acoshf(*) %{generate(double2float("acosh"))}
[[std, crtbuiltin, export_alias("__asinhf")]] asinhf(*) %{generate(double2float("asinh"))}
[[std, crtbuiltin, export_alias("__atanhf")]] atanhf(*) %{generate(double2float("atanh"))}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__acoshl")]] acoshl(*) %{generate(double2ldouble("acosh"))}
[[std, crtbuiltin, export_alias("__asinhl")]] asinhl(*) %{generate(double2ldouble("asinh"))}
[[std, crtbuiltin, export_alias("__atanhl")]] atanhl(*) %{generate(double2ldouble("atanh"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

%(std, c)
%(std, c)/* Exponential and logarithmic functions. */

@@Exponential function of X
[[attribute("__DECL_SIMD_exp"), decl_include("<bits/crt/math-vector.h>")]]
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__exp")]]
[[impl_include("<libm/signbit.h>", "<libm/finite.h>")]]
[[impl_include("<libm/matherr.h>", "<libm/exp.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double exp(double x) {
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
[[std, crtbuiltin, export_alias("__frexp")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/frexp.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double frexp(double x, [[nonnull]] int *pexponent) {
@@pp_ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__@@
	return (double)__ieee754_frexp((__IEEE754_DOUBLE_TYPE__)x, pexponent);
@@pp_elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)@@
	return (double)__ieee754_frexpf((__IEEE754_FLOAT_TYPE__)x, pexponent);
@@pp_else@@
	return (double)__ieee854_frexpl((__IEEE854_LONG_DOUBLE_TYPE__)x, pexponent);
@@pp_endif@@
}

@@X times (two to the EXP power)
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__ldexp")]]
[[impl_include("<parts/errno.h>", "<libm/finite.h>", "<libm/ldexp.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double ldexp(double x, int exponent) {
	double result;
@@pp_ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__@@
	result = (double)__ieee754_ldexp((__IEEE754_DOUBLE_TYPE__)x, exponent);
@@pp_elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)@@
	result = (double)__ieee754_ldexpf((__IEEE754_FLOAT_TYPE__)x, exponent);
@@pp_else@@
	result = (double)__ieee854_ldexpl((__IEEE854_LONG_DOUBLE_TYPE__)x, exponent);
@@pp_endif@@
@@pp_ifdef ERANGE@@
	if unlikely(!__LIBM_MATHFUN(@finite@, result) || result == 0.0)
		__libc_seterrno(ERANGE);
@@pp_endif@@
	return result;
}

@@Natural logarithm of X
[[attribute("__DECL_SIMD_log"), decl_include("<bits/crt/math-vector.h>")]]
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__log")]]
double log(double x); /* TODO */

@@Base-ten logarithm of X
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__log10")]]
double log10(double x); /* TODO */

@@Break VALUE into integral and fractional parts
[[std, wunused, crtbuiltin, export_alias("__modf")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/modf.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double modf(double x, [[nonnull]] double *iptr) {
@@pp_ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__@@
	return (double)__ieee754_modf((__IEEE754_DOUBLE_TYPE__)x, (__IEEE754_DOUBLE_TYPE__ *)iptr);
@@pp_elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)@@
	return (double)__ieee754_modff((__IEEE754_FLOAT_TYPE__)x, (__IEEE754_FLOAT_TYPE__ *)iptr);
@@pp_else@@
	return (double)__ieee854_modfl((__IEEE854_LONG_DOUBLE_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__ *)iptr);
@@pp_endif@@
}


[[std, crtbuiltin, export_alias("__expf")]]   expf(*)   %{generate(double2float("exp"))}
[[std, crtbuiltin, export_alias("__frexpf")]] frexpf(*) %{generate(double2float("frexp"))}
[[std, crtbuiltin, export_alias("__ldexpf")]] ldexpf(*) %{generate(double2float("ldexp"))}
[[std, crtbuiltin, export_alias("__logf")]]   logf(*)   %{generate(double2float("log"))}
[[std, crtbuiltin, export_alias("__log10f")]] log10f(*) %{generate(double2float("log10"))}
[[std, crtbuiltin, export_alias("__modff")]]  modff(*)  %{generate(double2float("modf"))}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__expl")]]   expl(*)   %{generate(double2ldouble("exp"))}
[[std, crtbuiltin, export_alias("__frexpl")]] frexpl(*) %{generate(double2ldouble("frexp"))}
[[std, crtbuiltin, export_alias("__ldexpl")]] ldexpl(*) %{generate(double2ldouble("ldexp"))}
[[std, crtbuiltin, export_alias("__logl")]]   logl(*)   %{generate(double2ldouble("log"))}
[[std, crtbuiltin, export_alias("__log10l")]] log10l(*) %{generate(double2ldouble("log10"))}
[[std, crtbuiltin, export_alias("__modfl")]]  modfl(*)  %{generate(double2ldouble("modf"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */

%(std, c)
%(std, c, ccompat)#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
@@Return exp(X) - 1
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__expm1")]]
[[impl_include("<libm/matherr.h>", "<libm/signbit.h>")]]
[[impl_include("<libm/finite.h>", "<libm/expm1.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double expm1(double x) {
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
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__log1p")]]
double log1p(double x); /* TODO */

@@Return the base 2 signed integral exponent of X
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__logb", "_logb")]]
double logb(double x); /* TODO */


[[std, crtbuiltin, export_alias("__expm1f")]] expm1f(*) %{generate(double2float("expm1"))}
[[std, crtbuiltin, export_alias("__log1pf")]] log1pf(*) %{generate(double2float("log1p"))}
[[std, crtbuiltin, export_alias("__logbf")]]  logbf(*)  %{generate(double2float("logb"))}
%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__expm1l")]] expm1l(*) %{generate(double2ldouble("expm1"))}
[[std, crtbuiltin, export_alias("__log1pl")]] log1pl(*) %{generate(double2ldouble("log1p"))}
[[std, crtbuiltin, export_alias("__logbl")]]  logbl(*)  %{generate(double2ldouble("logb"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

%(std, c)
%(std, c, ccompat)#ifdef __USE_ISOC99
@@Compute base-2 exponential of X
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__exp2")]]
double exp2(double x); /* TODO */

@@Compute base-2 logarithm of X
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__log2")]]
double log2(double x); /* TODO */


[[std, crtbuiltin, export_alias("__exp2f")]] exp2f(*) %{generate(double2float("exp2"))}
[[std, crtbuiltin, export_alias("__log2f")]] log2f(*) %{generate(double2float("log2"))}
%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__exp2l")]] exp2l(*) %{generate(double2ldouble("exp2"))}
[[std, crtbuiltin, export_alias("__log2l")]] log2l(*) %{generate(double2ldouble("log2"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_ISOC99 */

%(std, c)
%(std, c)/* Power functions. */

@@Return X to the Y power
[[attribute("__DECL_SIMD_pow"), decl_include("<bits/crt/math-vector.h>")]]
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__pow")]]
[[impl_include("<libm/finite.h>", "<libm/isnan.h>", "<libm/matherr.h>")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/pow.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double pow(double x, double y) {
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
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__sqrt")]]
[[impl_include("<libm/fcomp.h>", "<libm/nan.h>")]]
[[impl_include("<libm/matherr.h>", "<libm/sqrt.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double sqrt(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2(@isless@, x, 0.0))
		return __kernel_standard(x, x, __LIBM_MATHFUN1I(@nan@, ""), __LIBM_KMATHERR_SQRT); /* sqrt(negative) */
	return __LIBM_MATHFUN(@sqrt@, x);
}

[[std, crtbuiltin, export_alias("__powf")]]  powf(*)  %{generate(double2float("pow"))}
[[std, crtbuiltin, export_alias("__sqrtf")]] sqrtf(*) %{generate(double2float("sqrt"))}
%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__powl")]]  powl(*)  %{generate(double2ldouble("pow"))}
[[std, crtbuiltin, export_alias("__sqrtl")]] sqrtl(*) %{generate(double2ldouble("sqrt"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */

%(std, c)
%(std, c, ccompat)#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
@@Return `sqrt(X*X + Y*Y)'
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__hypot")]]
double hypot(double x, double y); /* TODO */

[[std, crtbuiltin, export_alias("__hypotf")]] hypotf(*) %{generate(double2float("hypot"))}
%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__hypotl")]] hypotl(*) %{generate(double2ldouble("hypot"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN || __USE_ISOC99 */


%(std, c)
%(std, c, ccompat)#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
@@Return the cube root of X
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__cbrt")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/cbrt.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double cbrt(double x) {
	return __LIBM_MATHFUN(@cbrt@, x);
}

[[std, crtbuiltin, export_alias("__cbrtf")]] cbrtf(*) %{generate(double2float("cbrt"))}
%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__cbrtl")]] cbrtl(*) %{generate(double2ldouble("cbrt"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

%(std, c)
%(std, c)/* Nearest integer, absolute value, and remainder functions. */

@@Smallest integral value not less than X
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__ceil")]]
[[impl_include("<hybrid/typecore.h>"), impl_include("<libm/ceil.h>")]]
double ceil(double x) {
@@pp_ifdef __LIBM_MATHFUN@@
	return __LIBM_MATHFUN(@ceil@, x);
@@pp_else@@
	double result;
	result = (double)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result < x)
		result += 1.0;
	return result;
@@pp_endif@@
}

@@Absolute value of X
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__fabs")]]
[[impl_include("<libm/fabs.h>")]]
double fabs(double x) {
@@pp_ifdef __LIBM_MATHFUN@@
	return __LIBM_MATHFUN(@fabs@, x);
@@pp_else@@
	return x < 0.0 ? -x : x;
@@pp_endif@@
}

@@Largest integer not greater than X
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__floor")]]
[[impl_include("<hybrid/typecore.h>", "<libm/floor.h>")]]
double floor(double x) {
@@pp_ifdef __LIBM_MATHFUN@@
	return __LIBM_MATHFUN(@floor@, x);
@@pp_else@@
	double result;
	result = (double)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result > x)
		result -= 1.0;
	return result;
@@pp_endif@@
}


@@Floating-point modulo remainder of X/Y
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__fmod")]]
[[impl_include("<libm/isinf.h>", "<libm/fcomp.h>")]]
[[impl_include("<libm/matherr.h>", "<libm/fmod.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double fmod(double x, double y) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUN(@isinf@, x) || y == 0.0) &&
	    !__LIBM_MATHFUN2(@isunordered@, x, y))
		return __kernel_standard(x, y, y, __LIBM_KMATHERR_FMOD); /* fmod(+-Inf,y) or fmod(x,0) */
	return __LIBM_MATHFUN2(@fmod@, x, y);
}
[[std, crtbuiltin, export_alias("__ceilf")]]  ceilf(*)  %{generate(double2float("ceil"))}
[[std, crtbuiltin, export_alias("__fabsf")]]  fabsf(*)  %{generate(double2float("fabs"))}
[[std, crtbuiltin, export_alias("__floorf")]] floorf(*) %{generate(double2float("floor"))}
[[std, crtbuiltin, export_alias("__fmodf")]]  fmodf(*)  %{generate(double2float("fmod"))}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__ceill")]]  ceill(*)  %{generate(double2ldouble("ceil"))}
[[std, crtbuiltin, export_alias("__fabsl")]]  fabsl(*)  %{generate(double2ldouble("fabs"))}
[[std, crtbuiltin, export_alias("__floorl")]] floorl(*) %{generate(double2ldouble("floor"))}
[[std, crtbuiltin, export_alias("__fmodl")]]  fmodl(*)  %{generate(double2ldouble("fmod"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */


%(std, c)
%(std, c, ccompat)#ifdef __USE_ISOC99
@@Return X with its signed changed to Y's
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__copysign", "_copysign")]]
[[impl_include("<libm/copysign.h>")]]
double copysign(double num, double sign) {
@@pp_ifdef __LIBM_MATHFUN2@@
	return __LIBM_MATHFUN2(@copysign@, num, sign);
@@pp_else@@
	if ((num < 0.0) != (sign < 0.0))
		num = -num;
	return num;
@@pp_endif@@
}

@@Return representation of qNaN for double type
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__nan")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/nan.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double nan(char const *tagb) {
	return __LIBM_MATHFUN1I(@nan@, tagb);
}

[[std, crtbuiltin, export_alias("__copysignf")]] copysignf(*) %{generate(double2float("copysign"))}
[[std, crtbuiltin, export_alias("__nanf")]]      nanf(*)      %{generate(double2float("nan"))}
%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__copysignl")]] copysignl(*) %{generate(double2ldouble("copysign"))}
[[std, crtbuiltin, export_alias("__nanl")]]      nanl(*)      %{generate(double2ldouble("nan"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_ISOC99 */



%(std, c)
%(std, c)/* Error and gamma functions. */
%(std, c, ccompat)#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__erf")]]
double erf(double x); /* TODO */

[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__erfc")]]
double erfc(double x); /* TODO */

[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("gamma", "__lgamma", "__gamma")]]
[[if(__has_builtin(__builtin_gamma) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("gamma", { return __builtin_gamma(x); })]]
double lgamma(double x); /* TODO */


[[std, crtbuiltin, export_alias("__erff")]]  erff(*)  %{generate(double2float("erf"))}
[[std, crtbuiltin, export_alias("__erfcf")]] erfcf(*) %{generate(double2float("erfc"))}

[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("gammaf", "__lgammaf", "__gammaf")]]
[[if(__has_builtin(__builtin_gammaf) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("gammaf", { return __builtin_gammaf(x); })]]
float lgammaf(float x) %{generate(double2float("lgamma"))}


%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__erfl")]]  erfl(*)  %{generate(double2ldouble("erf"))}
[[std, crtbuiltin, export_alias("__erfcl")]] erfcl(*) %{generate(double2ldouble("erfc"))}

[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("gammal", "__lgammal", "__gammal")]]
[[if(__has_builtin(__builtin_gammal) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("gammal", { return __builtin_gammal(x); })]]
__LONGDOUBLE lgammal(__LONGDOUBLE x) %{generate(double2ldouble("lgamma"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN || __USE_ISOC99 */

%(std, c, ccompat)#ifdef __USE_ISOC99
@@True gamma function
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__tgamma")]]
double tgamma(double x); /* TODO */

[[std, crtbuiltin, export_alias("__tgammaf")]] tgammaf(*) %{generate(double2float("tgamma"))}
%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__tgammal")]] tgammal(*) %{generate(double2ldouble("tgamma"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_ISOC99 */

%(std, c)
%(std, c, ccompat)#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)

@@Return the integer nearest X in the direction of the prevailing rounding mode
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("nearbyint", "__rint", "__nearbyint")]]
[[if(__has_builtin(__builtin_nearbyint) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("nearbyint", { return __builtin_nearbyint(x); })]]
[[requires_include("<ieee754.h>"), impl_include("<libm/rint.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double rint(double x) {
	return __LIBM_MATHFUN(@rint@, x);
}


@@Return X + epsilon if X < Y, X - epsilon if X > Y
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("nexttoward")]]
[[export_alias("__nextafter", "_nextafter", "__nexttoward")]]
[[if(__has_builtin(__builtin_nexttoward) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("nexttoward", { return __builtin_nexttoward(x); })]]
[[requires_include("<ieee754.h>"), impl_include("<libm/nextafter.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double nextafter(double x, double y) {
	return __LIBM_MATHFUN2(@nextafter@, x, y);
}

@@Return the remainder of integer division X/P with infinite precision
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("drem", "__remainder", "__drem")]]
[[if(__has_builtin(__builtin_drem) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("drem", { return __builtin_drem(x, p); })]]
[[impl_include("<libm/matherr.h>", "<libm/isnan.h>")]]
[[impl_include("<libm/isinf.h>", "<libm/remainder.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double remainder(double x, double p) {
	if (((p == 0.0 && !__LIBM_MATHFUN(@isnan@, x)) ||
	     (__LIBM_MATHFUN(@isinf@, x) && !__LIBM_MATHFUN(@isnan@, p))) &&
	    __LIBM_LIB_VERSION != __LIBM_IEEE)
		return __kernel_standard(x, p, p, __LIBM_KMATHERR_REMAINDER); /* remainder domain */
	return __LIBM_MATHFUN2(@remainder@, x, p);
}

@@Return the binary exponent of X, which must be nonzero
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__ilogb")]]
[[impl_include("<libm/ilogb.h>", "<libm/matherr.h>", "<bits/mathdef.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__))]]
int ilogb(double x) {
	int result;
	result = __LIBM_MATHFUNI(@ilogb@, x);
	if (result == __FP_ILOGB0 || result == __FP_ILOGBNAN || result == INT_MAX)
		__kernel_standard(x, x, x, __LIBM_KMATHERRF_ILOGB);
	return result;
}

[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("nearbyintf", "__rintf", "__nearbyintf")]]
[[if(__has_builtin(__builtin_nearbyintf) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("nearbyintf", { return __builtin_nearbyintf(x); })]]
float rintf(float x) %{generate(double2float("rint"))}

[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("nexttowardf", "__nextafterf", "__nexttowardf")]]
[[if(__has_builtin(__builtin_nexttowardf) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("nexttowardf", { return __builtin_nexttowardf(x); })]]
float nextafterf(float x, float y) %{generate(double2float("nextafter"))}

[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("dremf", "__remainderf", "__dremf")]]
[[if(__has_builtin(__builtin_dremf) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("dremf", { return __builtin_dremf(x, p); })]]
float remainderf(float x, float p) %{generate(double2float("remainder"))}

[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__ilogbf")]]
int ilogbf(float x) %{generate(double2float("ilogb"))}


%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("nearbyintl", "__rintl", "__nearbyintl")]]
[[if(__has_builtin(__builtin_nearbyintl) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("nearbyintl", { return __builtin_nearbyintl(x); })]]
__LONGDOUBLE rintl(__LONGDOUBLE x) %{generate(double2ldouble("rint"))}

[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("nexttowardl", "__nextafterl", "__nexttowardl")]]
[[if(__has_builtin(__builtin_nexttowardl) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("nexttowardl", { return __builtin_nexttowardl(x); })]]
__LONGDOUBLE nextafterl(__LONGDOUBLE x, __LONGDOUBLE y) %{generate(double2ldouble("nextafter"))}

[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("dreml", "__remainderl", "__dreml")]]
[[if(__has_builtin(__builtin_dreml) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("dreml", { return __builtin_dreml(x, p); })]]
__LONGDOUBLE remainderl(__LONGDOUBLE x, __LONGDOUBLE p) %{generate(double2ldouble("remainder"))}

[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__ilogbl")]]
int ilogbl(__LONGDOUBLE x) %{generate(double2ldouble("ilogb"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */



%(std, c)
%(std, c, ccompat)#ifdef __USE_ISOC99

[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__nexttoward")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/nexttoward.h>")]]
[[requires(((defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
             defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)) &&
            defined(__IEEE854_LONG_DOUBLE_TYPE__)) ||
            $has_function(nextafterl))]]
double nexttoward(double x, __LONGDOUBLE y) {
@@pp_ifdef __IEEE854_LONG_DOUBLE_TYPE__@@
@@pp_ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__@@
	return (double)__ieee754_nexttoward((__IEEE754_DOUBLE_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__)y);
@@pp_else@@
	return (double)__ieee754_nexttowardf((__IEEE754_FLOAT_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__)y);
@@pp_endif@@
@@pp_else@@
	return (double)nextafterl((__LONGDOUBLE)x, y);
@@pp_endif@@
}

@@Return X times (2 to the Nth power)
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__scalbn")]]
[[if(__SIZEOF_INT__ == __SIZEOF_LONG__), alias("scalbln", "__scalbln")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/scalbn.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double scalbn(double x, int n) {
@@pp_ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__@@
	return (double)__ieee754_scalbn((__IEEE754_DOUBLE_TYPE__)x, n);
@@pp_elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)@@
	return (double)__ieee754_scalbnf((__IEEE754_FLOAT_TYPE__)x, n);
@@pp_else@@
	return (double)__ieee854_scalbnl((__IEEE854_LONG_DOUBLE_TYPE__)x, n);
@@pp_endif@@
}

[[doc_alias("scalbn")]]
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__scalbln")]]
[[alt_variant_of(__SIZEOF_INT__ == __SIZEOF_LONG__, scalbn)]]
[[if(__SIZEOF_INT__ == __SIZEOF_LONG__), alias("__scalbn")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/scalbn.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double scalbln(double x, long int n) {
@@pp_ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__@@
	return (double)__ieee754_scalbln((__IEEE754_DOUBLE_TYPE__)x, n);
@@pp_elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)@@
	return (double)__ieee754_scalblnf((__IEEE754_FLOAT_TYPE__)x, n);
@@pp_else@@
	return (double)__ieee854_scalblnl((__IEEE854_LONG_DOUBLE_TYPE__)x, n);
@@pp_endif@@
}

@@Return the integer nearest X in the direction of the prevailing rounding mode
@@This function is similar to `rint()', but does not tend to produce wrong results (so use this one)
[[std, wunused, nothrow, ATTR_CONST, nocrt, alias("nearbyint", "__nearbyint", "rint", "__rint")]]
[[if(__has_builtin(__builtin_nearbyint) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("nearbyint", { return __builtin_nearbyint(x); })]]
[[if($extended_include_prefix("<ieee754.h>")defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
                                            defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
                                            defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)),
  bind_local_function(rint)]]
double nearbyint(double x);



@@Round X to nearest integral value, rounding halfway cases away from zero
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__round")]]
[[impl_include("<hybrid/typecore.h>", "<libm/round.h>")]]
double round(double x) {
@@pp_ifdef __LIBM_MATHFUN@@
	return (double)__LIBM_MATHFUN(@round@, x);
@@pp_else@@
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
@@pp_endif@@
}

@@Round X to the integral value in floating-point
@@format nearest but not larger in magnitude
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__trunc")]]
[[impl_include("<hybrid/typecore.h>", "<libm/trunc.h>")]]
double trunc(double x) {
@@pp_ifdef __LIBM_MATHFUN@@
	return __LIBM_MATHFUN(@trunc@, x);
@@pp_else@@
	return (double)(__INTMAX_TYPE__)x;
@@pp_endif@@
}

@@Compute remainder of X and Y and put in *QUO a value with sign
@@of x/y and magnitude congruent `mod 2^n' to the magnitude of
@@the integral quotient x/y, with n >= 3
[[std, wunused, nothrow, crtbuiltin, export_alias("__remquo")]]
double remquo(double x, double y, int *pquo); /* TODO */

@@Round X to nearest integral value according to current rounding direction
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__lrint")]]
[[impl_include("<hybrid/typecore.h>", "<libm/lrint.h>")]]
[[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("llrint")]]
long int lrint(double x) {
@@pp_ifdef __LIBM_MATHFUNI@@
	return __LIBM_MATHFUNI(@lrint@, x);
@@pp_else@@
	return (long int)rint(x);
@@pp_endif@@
}

@@Round X to nearest integral value, rounding halfway cases away from zero
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__lround")]]
[[impl_include("<hybrid/typecore.h>", "<libm/lround.h>")]]
[[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("llround")]]
long int lround(double x) {
@@pp_ifdef __LIBM_MATHFUNI@@
	return __LIBM_MATHFUNI(@lround@, x);
@@pp_else@@
	return (long int)round(x);
@@pp_endif@@
}

@@Return positive difference between X and Y
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__fdim")]]
double fdim(double x, double y) {
	/* TODO: ieee754-specific function */
	return fabs(y - x);
}

@@Return maximum numeric value from X and Y
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__fmax")]]
double fmax(double x, double y) {
	/* TODO: ieee754-specific function */
	return x < y ? y : x;
}

@@Return minimum numeric value from X and Y
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__fmin")]]
double fmin(double x, double y) {
	/* TODO: ieee754-specific function */
	return x < y ? x : y;
}

@@Multiply-add function computed as a ternary operation
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__fma")]]
double fma(double x, double y, double z) {
	/* TODO: ieee754-specific function */
	return (x * y) + z;
}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGLONG
@@Round X to nearest integral value according to current rounding direction
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__llrint")]]
[[impl_include("<hybrid/typecore.h>", "<libm/lrint.h>")]]
[[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__, lrint)]]
__LONGLONG llrint(double x) {
@@pp_ifdef __LIBM_MATHFUNI@@
	return __LIBM_MATHFUNI(@llrint@, x);
@@pp_else@@
	return (__LONGLONG)rint(x);
@@pp_endif@@
}

@@Round X to nearest integral value, rounding halfway cases away from zero
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__llround")]]
[[impl_include("<hybrid/typecore.h>", "<libm/lround.h>")]]
[[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__, lround)]]
__LONGLONG llround(double x) {
@@pp_ifdef __LIBM_MATHFUNI@@
	return __LIBM_MATHFUNI(@llround@, x);
@@pp_else@@
	return (__LONGLONG)round(x);
@@pp_endif@@
}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGLONG */

[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__nexttowardf")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/nexttoward.h>")]]
[[requires(((defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) ||
             defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)) &&
            defined(__IEEE854_LONG_DOUBLE_TYPE__)) ||
            $has_function(nextafterl))]]
float nexttowardf(float x, __LONGDOUBLE y) {
@@pp_ifdef __IEEE854_LONG_DOUBLE_TYPE__@@
@@pp_ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__@@
	return (float)__ieee754_nexttowardf((__IEEE754_FLOAT_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__)y);
@@pp_else@@
	return (float)__ieee754_nexttoward((__IEEE754_DOUBLE_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__)y);
@@pp_endif@@
@@pp_else@@
	return (float)nextafterl((__LONGDOUBLE)x, y);
@@pp_endif@@
}



[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__scalbnf")]]
[[if(__SIZEOF_INT__ == __SIZEOF_LONG__), alias("scalblnf", "__scalblnf")]]
float scalbnf(float x, int n) %{generate(double2float("scalbn"))}

[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__scalblnf")]]
[[alt_variant_of(__SIZEOF_INT__ == __SIZEOF_LONG__, scalbnf)]]
[[if(__SIZEOF_INT__ == __SIZEOF_LONG__), alias("__scalbnf")]]
float scalblnf(float x, long int n) %{generate(double2float("scalbln"))}

[[std, wunused, nothrow, ATTR_CONST, doc_alias(nearbyint)]]
[[nocrt, alias("nearbyintf", "__nearbyintf", "rintf", "__rintf")]]
[[if(__has_builtin(__builtin_nearbyintf) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("nearbyintf", { return __builtin_nearbyintf(x); })]]
[[if($extended_include_prefix("<ieee754.h>")defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) ||
                                            defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) ||
                                            defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)),
  bind_local_function(rintf)]]
float nearbyintf(float x);

[[std, crtbuiltin, export_alias("__roundf")]]  roundf(*)  %{generate(double2float("round"))}
[[std, crtbuiltin, export_alias("__truncf")]]  truncf(*)  %{generate(double2float("trunc"))}
[[std, crtbuiltin, export_alias("__remquof")]] remquof(*) %{generate(double2float("remquo"))}

[[std, crtbuiltin, export_alias("__lrintf")]]
[[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("llrintf", "__llrintf")]]
long int lrintf(float x) %{generate(double2float("lrint"))}

[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__lroundf")]]
[[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("llroundf", "__llroundf")]]
long int lroundf(float x) %{generate(double2float("lround"))}

[[std, crtbuiltin, export_alias("__fdimf")]] fdimf(*) %{generate(double2float("fdim"))}
[[std, crtbuiltin, export_alias("__fmaxf")]] fmaxf(*) %{generate(double2float("fmax"))}
[[std, crtbuiltin, export_alias("__fminf")]] fminf(*) %{generate(double2float("fmin"))}
[[std, crtbuiltin, export_alias("__fmaf")]]  fmaf(*)  %{generate(double2float("fma"))}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGLONG
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__llrintf")]]
[[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__, lrintf)]]
[[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("__lrintf")]]
__LONGLONG llrintf(float x) %{generate(double2float("llrint"))}

[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__llroundf")]]
[[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__, lroundf)]]
[[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("__lroundf")]]
__LONGLONG llroundf(float x) %{generate(double2float("llround"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGLONG */

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
nexttowardl(*) = nextafterl;

[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__scalbnl")]]
[[if(__SIZEOF_INT__ == __SIZEOF_LONG__), alias("scalblnl", "__scalblnl")]]
__LONGDOUBLE scalbnl(__LONGDOUBLE x, int n) %{generate(double2ldouble("scalbn"))}

[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__scalblnl")]]
[[alt_variant_of(__SIZEOF_INT__ == __SIZEOF_LONG__, scalbnl)]]
[[if(__SIZEOF_INT__ == __SIZEOF_LONG__), alias("__scalbnl")]]
__LONGDOUBLE scalblnl(__LONGDOUBLE x, long int n) %{generate(double2ldouble("scalbln"))}

[[std, wunused, nothrow, ATTR_CONST, doc_alias(nearbyint)]]
[[nocrt, alias("nearbyintl", "__nearbyintl", "rintl", "__rintl")]]
[[if(__has_builtin(__builtin_nearbyintl) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("nearbyintl", { return __builtin_nearbyintl(x); })]]
[[if($extended_include_prefix("<ieee754.h>")defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) ||
                                            defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) ||
                                            defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)),
  bind_local_function(rintl)]]
__LONGDOUBLE nearbyintl(__LONGDOUBLE x);

[[std, crtbuiltin, export_alias("__roundl")]]  roundl(*)  %{generate(double2ldouble("round"))}
[[std, crtbuiltin, export_alias("__truncl")]]  truncl(*)  %{generate(double2ldouble("trunc"))}
[[std, crtbuiltin, export_alias("__remquol")]] remquol(*) %{generate(double2ldouble("remquo"))}

[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__lrintl")]]
[[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("llrintl", "__llrintl")]]
long int lrintl(__LONGDOUBLE x) %{generate(double2ldouble("lrint"))}

[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__lroundl")]]
[[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("llroundl", "__llroundl")]]
long int lroundl(__LONGDOUBLE x) %{generate(double2ldouble("lround"))}

[[std, crtbuiltin, export_alias("__fdiml")]] fdiml(*) %{generate(double2ldouble("fdim"))}
[[std, crtbuiltin, export_alias("__fmaxl")]] fmaxl(*) %{generate(double2ldouble("fmax"))}
[[std, crtbuiltin, export_alias("__fminl")]] fminl(*) %{generate(double2ldouble("fmin"))}
[[std, crtbuiltin, export_alias("__fmal")]]  fmal(*)  %{generate(double2ldouble("fma"))}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGLONG
[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__llrintl")]]
[[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__, lrintl)]]
[[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("__lrintl")]]
__LONGLONG llrintl(__LONGDOUBLE x) %{generate(double2ldouble("llrint"))}

[[std, wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__llroundl")]]
[[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__, lroundl)]]
[[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("__lroundl")]]
__LONGLONG llroundl(__LONGDOUBLE x) %{generate(double2ldouble("llround"))}

%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGLONG */
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_ISOC99 */



/* C++ overload aliases */
%(std)#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_MATH_H_PROTO)
%[insert:std_function_nousing(acos = acosf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(asin = asinf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(atan = atanf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(atan2 = atan2f, externLinkageOverride: "C++")]
%[insert:std_function_nousing(cos = cosf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(sin = sinf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(tan = tanf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(cosh = coshf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(sinh = sinhf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(tanh = tanhf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(exp = expf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(frexp = frexpf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(ldexp = ldexpf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(log = logf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(log10 = log10f, externLinkageOverride: "C++")]
%[insert:std_function_nousing(modf = modff, externLinkageOverride: "C++")]
%[insert:std_function_nousing(pow = powf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(sqrt = sqrtf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(ceil = ceilf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fabs = fabsf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(floor = floorf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fmod = fmodf, externLinkageOverride: "C++")]

%(std)#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:std_function_nousing(acos = acosl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(asin = asinl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(atan = atanl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(atan2 = atan2l, externLinkageOverride: "C++")]
%[insert:std_function_nousing(cos = cosl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(sin = sinl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(tan = tanl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(cosh = coshl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(sinh = sinhl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(tanh = tanhl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(exp = expl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(frexp = frexpl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(ldexp = ldexpl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(log = logl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(log10 = log10l, externLinkageOverride: "C++")]
%[insert:std_function_nousing(modf = modfl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(pow = powl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(sqrt = sqrtl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(ceil = ceill, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fabs = fabsl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(floor = floorl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fmod = fmodl, externLinkageOverride: "C++")]
%(std)#endif /* __COMPILER_HAVE_LONGDOUBLE */


%(std)#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
%[insert:std_function_nousing(acosh = acoshf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(asinh = asinhf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(atanh = atanhf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(expm1 = expm1f, externLinkageOverride: "C++")]
%[insert:std_function_nousing(log1p = log1pf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(logb = logbf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(cbrt = cbrtf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(rint = rintf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(nextafter = nextafterf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(remainder = remainderf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(ilogb = ilogbf, externLinkageOverride: "C++")]
%(std)#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:std_function_nousing(acosh = acoshl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(asinh = asinhl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(atanh = atanhl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(expm1 = expm1l, externLinkageOverride: "C++")]
%[insert:std_function_nousing(log1p = log1pl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(logb = logbl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(cbrt = cbrtl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(rint = rintl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(nextafter = nextafterl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(remainder = remainderl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(ilogb = ilogbl, externLinkageOverride: "C++")]
%(std)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std)#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */


%(std)#ifdef __USE_ISOC99
%[insert:std_function_nousing(exp2 = exp2f, externLinkageOverride: "C++")]
%[insert:std_function_nousing(log2 = log2f, externLinkageOverride: "C++")]
%[insert:std_function_nousing(copysign = copysignf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(tgamma = tgammaf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(nexttoward = nexttowardf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(scalbn = scalbnf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(scalbln = scalblnf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(nearbyint = rintf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(round = roundf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(trunc = truncf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(remquo = remquof, externLinkageOverride: "C++")]
%[insert:std_function_nousing(lrint = lrintf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(lround = lroundf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fdim = fdimf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fmax = fmaxf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fmin = fminf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fma = fmaf, externLinkageOverride: "C++")]
%(std)#ifdef __COMPILER_HAVE_LONGLONG
%[insert:std_function_nousing(llrint = llrintf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(llround = llroundf, externLinkageOverride: "C++")]
%(std)#endif /* __COMPILER_HAVE_LONGLONG */
%(std)#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:std_function_nousing(exp2 = exp2l, externLinkageOverride: "C++")]
%[insert:std_function_nousing(log2 = log2l, externLinkageOverride: "C++")]
%[insert:std_function_nousing(copysign = copysignl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(tgamma = tgammal, externLinkageOverride: "C++")]
%[insert:std_function_nousing(nexttoward = nextafterl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(scalbn = scalbnl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(scalbln = scalblnl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(nearbyint = rintl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(round = roundl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(trunc = truncl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(remquo = remquol, externLinkageOverride: "C++")]
%[insert:std_function_nousing(lrint = lrintl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(lround = lroundl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fdim = fdiml, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fmax = fmaxl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fmin = fminl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fma = fmal, externLinkageOverride: "C++")]
%(std)#ifdef __COMPILER_HAVE_LONGLONG
%[insert:std_function_nousing(llrint = llrintl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(llround = llroundl, externLinkageOverride: "C++")]
%(std)#endif /* __COMPILER_HAVE_LONGLONG */
%(std)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std)#endif /* __USE_ISOC99 */


%(std)#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
%[insert:std_function_nousing(hypot = hypotf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(erf = erff, externLinkageOverride: "C++")]
%[insert:std_function_nousing(erfc = erfcf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(lgamma = lgammaf, externLinkageOverride: "C++")]
%(std)#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:std_function_nousing(hypot = hypotl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(erf = erfl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(erfc = erfcl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(lgamma = lgammal, externLinkageOverride: "C++")]
%(std)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std)#endif /* __USE_XOPEN || __USE_ISOC99 */
%(std)#endif /* __cplusplus && __CORRECT_ISO_CPP_MATH_H_PROTO */





%
%#ifdef __USE_GNU
@@Cosine and sine of X
[[nothrow, crtbuiltin, export_alias("__sincos")]]
[[attribute("__DECL_SIMD_sincos"), decl_include("<bits/crt/math-vector.h>")]]
void sincos(double x, [[nonnull]] double *psinx, [[nonnull]] double *pcosx); /* TODO */

@@A function missing in all standards: compute exponent to base ten
[[wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__exp10")]]
double exp10(double x); /* TODO */

@@Another name occasionally used
[[wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__pow10")]]
[[requires($has_function(pow))]]
double pow10(double x) {
	return pow(10.0, x);
}

[[crtbuiltin, export_alias("__sincosf"), nothrow, doc_alias(sincos)]]
[[attribute("__DECL_SIMD_sincosf"), decl_include("<bits/crt/math-vector.h>")]]
[[requires_function(sincos)]]
void sincosf(float x, [[nonnull]] float *psinx, [[nonnull]] float *pcosx) {
	double sinx, cosx;
	sincos((double)x, &sinx, &cosx);
	*psinx = (float)sinx;
	*pcosx = (float)cosx;
}

[[crtbuiltin, export_alias("__exp10f")]] exp10f(*) %{generate(double2float("exp10"))}
[[crtbuiltin, export_alias("__pow10f")]] pow10f(*) %{generate(double2float("pow10"))}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[nothrow, crtbuiltin, export_alias("__sincosl"), doc_alias(sincos)]]
[[attribute("__DECL_SIMD_sincosl"), decl_include("<bits/crt/math-vector.h>")]]
[[if(defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), alias("__sincos", "sincos")]]
[[requires_function(sincos)]]
void sincosl(__LONGDOUBLE x, [[nonnull]] __LONGDOUBLE *psinx, [[nonnull]] __LONGDOUBLE *pcosx) {
	double sinx, cosx;
	sincos((double)x, &sinx, &cosx);
	*psinx = (__LONGDOUBLE)sinx;
	*pcosx = (__LONGDOUBLE)cosx;
}

[[crtbuiltin, export_alias("__exp10l")]] exp10l(*) %{generate(double2ldouble("exp10"))}
[[crtbuiltin, export_alias("__pow10l")]] pow10l(*) %{generate(double2ldouble("pow10"))}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_GNU */


%
%#ifdef __USE_MISC

%#if !defined(__cplusplus) || !defined(__CORRECT_ISO_CPP11_MATH_H_PROTO_FP) /* isinf conflicts with C++11. */
@@Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity
[[wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__isinf")]]
[[impl_include("<libm/isinf.h>")]]
[[requires_include("<ieee754.h>", "<bits/math-constants.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__INFINITY) || defined(__HUGE_VAL))]]
int isinf(double x) {
@@pp_ifdef __LIBM_MATHFUNI@@
	return __LIBM_MATHFUNI(@isinf@, x);
@@pp_elif defined(__INFINITY)@@
	return x == __INFINITY;
@@pp_else@@
	return x == __HUGE_VAL;
@@pp_endif@@
}
%#endif /* !__cplusplus || !__CORRECT_ISO_CPP11_MATH_H_PROTO_FP */

[[crtbuiltin, export_alias("__isinff")]] isinff(*) %{generate(double2float("isinf"))}
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[crtbuiltin, export_alias("__isinfl")]] isinfl(*) %{generate(double2ldouble("isinf"))}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

@@Return nonzero if VALUE is finite and not NaN
[[wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__finite", "_finite")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/finite.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) ||
           ($has_function(isinf) && $has_function(isnan)))]]
int finite(double x) {
@@pp_ifdef __LIBM_MATHFUNI@@
	return __LIBM_MATHFUNI(@finite@, x);
@@pp_else@@
	return !isinf(x) && !isnan(x);
@@pp_endif@@
}

drem(*) = remainder;

@@Return the fractional part of X after dividing out `ilogb(X)'
[[wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__significand")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/significand.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double significand(double x) {
	return __LIBM_MATHFUN(@significand@, x);
}

[[crtbuiltin, export_alias("__finitef")]]
finitef(*) %{generate(double2float("finite"))}

dremf(*) = remainderf;

[[crtbuiltin, export_alias("__significandf")]]
significandf(*) %{generate(double2float("significand"))}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[crtbuiltin, export_alias("__finitel")]]
finitel(*) %{generate(double2ldouble("finite"))}

dreml(*) = remainderl;

[[crtbuiltin, export_alias("__significandl")]]
significandl(*) %{generate(double2ldouble("significand"))}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */

%
%#if defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
%#if !defined(__cplusplus) || !defined(__CORRECT_ISO_CPP11_MATH_H_PROTO_FP) /* isnan conflicts with C++11. */
@@Return nonzero if VALUE is not a number
[[wunused, nothrow, ATTR_CONST, crtbuiltin, export_alias("__isnan", "_isnan")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/isnan.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
int isnan(double x) {
	return __LIBM_MATHFUNI(@isnan@, x);
}
%#endif /* !cplusplus || !__CORRECT_ISO_CPP11_MATH_H_PROTO_FP */

[[crtbuiltin, export_alias("__isnanf")]]
isnanf(*) %{generate(double2float("isnan"))}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[crtbuiltin, export_alias("__isnanl")]]
isnanl(*) %{generate(double2ldouble("isnan"))}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

%#endif /* __USE_MISC || (__USE_XOPEN && !__USE_XOPEN2K) */

%
%/* Bessel functions. */
%#if defined(__USE_MISC) || (defined(__USE_XOPEN) && __MATH_DECLARING_DOUBLE)
[[wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__j0")]]
double j0(double x); /* TODO */

[[wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__j1")]]
double j1(double x); /* TODO */

[[wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__jn")]]
double jn(int n, double x); /* TODO */

[[wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__y0")]]
double y0(double x); /* TODO */

[[wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__y1")]]
double y1(double x); /* TODO */

[[wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__yn")]]
double yn(int n, double x); /* TODO */

[[crtbuiltin, export_alias("__j0f")]] j0f(*) %{generate(double2float("j0"))}
[[crtbuiltin, export_alias("__j1f")]] j1f(*) %{generate(double2float("j1"))}
[[crtbuiltin, export_alias("__jnf")]] jnf(*) %{generate(double2float("jn"))}
[[crtbuiltin, export_alias("__y0f")]] y0f(*) %{generate(double2float("y0"))}
[[crtbuiltin, export_alias("__y1f")]] y1f(*) %{generate(double2float("y1"))}
[[crtbuiltin, export_alias("__ynf")]] ynf(*) %{generate(double2float("yn"))}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[crtbuiltin, export_alias("__j0l")]] j0l(*) %{generate(double2ldouble("j0"))}
[[crtbuiltin, export_alias("__j1l")]] j1l(*) %{generate(double2ldouble("j1"))}
[[crtbuiltin, export_alias("__jnl")]] jnl(*) %{generate(double2ldouble("jn"))}
[[crtbuiltin, export_alias("__y0l")]] y0l(*) %{generate(double2ldouble("y0"))}
[[crtbuiltin, export_alias("__y1l")]] y1l(*) %{generate(double2ldouble("y1"))}
[[crtbuiltin, export_alias("__ynl")]] ynl(*) %{generate(double2ldouble("yn"))}
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
[[wunused, crtbuiltin, export_alias("__lgamma_r")]]
double lgamma_r(double x, int *signgamp); /* TODO */

[[crtbuiltin, export_alias("__lgammaf_r")]] lgammaf_r(*) %{generate(double2float("lgamma_r"))};
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[crtbuiltin, export_alias("__lgammal_r")]] lgammal_r(*) %{generate(double2ldouble("lgamma_r"))};
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */

%
%#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8))
@@Return X times (2 to the Nth power)
[[wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__scalb", "_scalb")]]
[[impl_include("<libm/isnan.h>", "<libm/finite.h>", "<libm/isinf.h>")]]
[[impl_include("<libm/matherr.h>", "<parts/errno.h>", "<libm/scalb.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double scalb(double x, double fn) {
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
[[crtbuiltin, export_alias("__scalbf", "_scalbf")]] scalbf(*) %{generate(double2float("scalb"))}
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[crtbuiltin, export_alias("__scalbl")]] scalbl(*) %{generate(double2ldouble("scalb"))}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */








%
%
%
%#if 1 /* GLIBc aliases */
%[insert:function(__acos = acos)]
%[insert:function(__asin = asin)]
%[insert:function(__atan = atan)]
%[insert:function(__atan2 = atan2)]
%[insert:function(__cos = cos)]
%[insert:function(__sin = sin)]
%[insert:function(__tan = tan)]
%[insert:function(__cosh = cosh)]
%[insert:function(__sinh = sinh)]
%[insert:function(__tanh = tanh)]
%[insert:function(__acosf = acosf)]
%[insert:function(__asinf = asinf)]
%[insert:function(__atanf = atanf)]
%[insert:function(__atan2f = atan2f)]
%[insert:function(__cosf = cosf)]
%[insert:function(__sinf = sinf)]
%[insert:function(__tanf = tanf)]
%[insert:function(__coshf = coshf)]
%[insert:function(__sinhf = sinhf)]
%[insert:function(__tanhf = tanhf)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__acosl = acosl)]
%[insert:function(__asinl = asinl)]
%[insert:function(__atanl = atanl)]
%[insert:function(__atan2l = atan2l)]
%[insert:function(__cosl = cosl)]
%[insert:function(__sinl = sinl)]
%[insert:function(__tanl = tanl)]
%[insert:function(__coshl = coshl)]
%[insert:function(__sinhl = sinhl)]
%[insert:function(__tanhl = tanhl)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#ifdef __USE_GNU
%[insert:function(__sincos = sincos)]
%[insert:function(__sincosf = sincosf)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__sincosl = sincosl)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_GNU */

%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
%[insert:function(__acosh = acosh)]
%[insert:function(__asinh = asinh)]
%[insert:function(__atanh = atanh)]
%[insert:function(__acoshf = acoshf)]
%[insert:function(__asinhf = asinhf)]
%[insert:function(__atanhf = atanhf)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__acoshl = acoshl)]
%[insert:function(__asinhl = asinhl)]
%[insert:function(__atanhl = atanhl)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

%[insert:function(__exp = exp)]
%[insert:function(__frexp = frexp)]
%[insert:function(__ldexp = ldexp)]
%[insert:function(__log = log)]
%[insert:function(__log10 = log10)]
%[insert:function(__modf = modf)]
%[insert:function(__expf = expf)]
%[insert:function(__frexpf = frexpf)]
%[insert:function(__ldexpf = ldexpf)]
%[insert:function(__logf = logf)]
%[insert:function(__log10f = log10f)]
%[insert:function(__modff = modff)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__expl = expl)]
%[insert:function(__frexpl = frexpl)]
%[insert:function(__ldexpl = ldexpl)]
%[insert:function(__logl = logl)]
%[insert:function(__log10l = log10l)]
%[insert:function(__modfl = modfl)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

%
%#ifdef __USE_GNU
%[insert:function(__exp10 = exp10)]
%[insert:function(__pow10 = pow10)]
%[insert:function(__exp10f = exp10f)]
%[insert:function(__pow10f = pow10f)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__exp10l = exp10l)]
%[insert:function(__pow10l = pow10l)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_GNU */

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
%[insert:function(__expm1 = expm1)]
%[insert:function(__log1p = log1p)]
%[insert:function(__logb = logb)]
%[insert:function(__expm1f = expm1f)]
%[insert:function(__log1pf = log1pf)]
%[insert:function(__logbf = logbf)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__expm1l = expm1l)]
%[insert:function(__log1pl = log1pl)]
%[insert:function(__logbl = logbl)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

%
%#ifdef __USE_ISOC99
%[insert:function(__exp2 = exp2)]
%[insert:function(__log2 = log2)]
%[insert:function(__exp2f = exp2f)]
%[insert:function(__log2f = log2f)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__exp2l = exp2l)]
%[insert:function(__log2l = log2l)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_ISOC99 */

%[insert:function(__pow = pow)]
%[insert:function(__sqrt = sqrt)]
%[insert:function(__powf = powf)]
%[insert:function(__sqrtf = sqrtf)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__powl = powl)]
%[insert:function(__sqrtl = sqrtl)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

%
%#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
%[insert:function(__hypot = hypot)]
%[insert:function(__hypotf = hypotf)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__hypotl = hypotl)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_XOPEN || __USE_ISOC99 */

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
%[insert:function(__cbrt = cbrt)]
%[insert:function(__cbrtf = cbrtf)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__cbrtl = cbrtl)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

%[insert:function(__ceil = ceil)]
%[insert:function(__fabs = fabs)]
%[insert:function(__floor = floor)]
%[insert:function(__fmod = fmod)]
%[insert:function(__isinf = isinf)]
%[insert:function(__finite = finite)]
%[insert:function(__ceilf = ceilf)]
%[insert:function(__fabsf = fabsf)]
%[insert:function(__floorf = floorf)]
%[insert:function(__fmodf = fmodf)]
%[insert:function(__isinff = isinff)]
%[insert:function(__finitef = finitef)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__ceill = ceill)]
%[insert:function(__fabsl = fabsl)]
%[insert:function(__floorl = floorl)]
%[insert:function(__fmodl = fmodl)]
%[insert:function(__isinfl = isinfl)]
%[insert:function(__finitel = finitel)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

%#ifdef __USE_MISC
%[insert:function(__drem = remainder)]
%[insert:function(__significand = significand)]
%[insert:function(__dremf = remainderf)]
%[insert:function(__significandf = significandf)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__dreml = remainderl)]
%[insert:function(__significandl = significandl)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */

%
%#ifdef __USE_ISOC99
%[insert:function(__copysign = copysign)]
%[insert:function(__nan = nan)]
%[insert:function(__copysignf = copysignf)]
%[insert:function(__nanf = nanf)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__copysignl = copysignl)]
%[insert:function(__nanl = nanl)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_ISOC99 */

%
%[insert:function(__isnan = isnan)]
%[insert:function(__isnanf = isnanf)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__isnanl = isnanl)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

%
%/* Bessel functions. */
%#if defined(__USE_MISC) || defined(__USE_XOPEN)
%[insert:function(__j0 = j0)]
%[insert:function(__j1 = j1)]
%[insert:function(__jn = jn)]
%[insert:function(__y0 = y0)]
%[insert:function(__y1 = y1)]
%[insert:function(__yn = yn)]
%#endif /* __USE_MISC || __USE_XOPEN */
%#ifdef __USE_MISC
%[insert:function(__j0f = j0f)]
%[insert:function(__j1f = j1f)]
%[insert:function(__jnf = jnf)]
%[insert:function(__y0f = y0f)]
%[insert:function(__y1f = y1f)]
%[insert:function(__ynf = ynf)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__j0l = j0l)]
%[insert:function(__j1l = j1l)]
%[insert:function(__jnl = jnl)]
%[insert:function(__y0l = y0l)]
%[insert:function(__y1l = y1l)]
%[insert:function(__ynl = ynl)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */

%
%#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
%[insert:function(__erf = erf)]
%[insert:function(__erfc = erfc)]
%[insert:function(__lgamma = lgamma)]
%[insert:function(__erff = erff)]
%[insert:function(__erfcf = erfcf)]
%[insert:function(__lgammaf = lgammaf)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__erfl = erfl)]
%[insert:function(__erfcl = erfcl)]
%[insert:function(__lgammal = lgammal)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_XOPEN || __USE_ISOC99 */

%
%#ifdef __USE_ISOC99
%[insert:function(__tgamma = tgamma)]
%[insert:function(__tgammaf = tgammaf)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__tgammal = tgammal)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_ISOC99 */

%
%#if defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
%[insert:function(__gamma = lgamma)]
%[insert:function(__gammaf = lgammaf)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__gammal = lgammal)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC || (__USE_XOPEN && !__USE_XOPEN2K) */

%#ifdef __USE_MISC
%[insert:function(__lgamma_r = lgamma_r)]
%[insert:function(__lgammaf_r = lgammaf_r)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__lgammal_r = lgammal_r)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
%[insert:function(__rint = rint)]
%[insert:function(__nextafter = nextafter)]
%[insert:function(__remainder = remainder)]
%[insert:function(__ilogb = ilogb)]
%[insert:function(__rintf = rintf)]
%[insert:function(__nextafterf = nextafterf)]
%[insert:function(__remainderf = remainderf)]
%[insert:function(__ilogbf = ilogbf)]

%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__rintl = rintl)]
%[insert:function(__nextafterl = nextafterl)]
%[insert:function(__remainderl = remainderl)]
%[insert:function(__ilogbl = ilogbl)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */


%
%#ifdef __USE_ISOC99
%[insert:function(__nexttoward = nexttoward)]
%[insert:function(__scalbn = scalbn)]
%[insert:function(__scalbln = scalbln)]
%[insert:function(__nearbyint = rint)]
%[insert:function(__round = round)]
%[insert:function(__trunc = trunc)]
%[insert:function(__remquo = remquo)]
%[insert:function(__lrint = lrint)]
%[insert:function(__lround = lround)]
%[insert:function(__fdim = fdim)]
%[insert:function(__fmax = fmax)]
%[insert:function(__fmin = fmin)]
%[insert:function(__fma = fma)]

%[insert:function(__nexttowardf = nexttowardf)]
%[insert:function(__scalbnf = scalbnf)]
%[insert:function(__scalblnf = scalblnf)]
%[insert:function(__nearbyintf = rintf)]
%[insert:function(__roundf = roundf)]
%[insert:function(__truncf = truncf)]
%[insert:function(__remquof = remquof)]
%[insert:function(__lrintf = lrintf)]
%[insert:function(__lroundf = lroundf)]
%[insert:function(__fdimf = fdimf)]
%[insert:function(__fmaxf = fmaxf)]
%[insert:function(__fminf = fminf)]
%[insert:function(__fmaf = fmaf)]

%#ifdef __COMPILER_HAVE_LONGLONG
%[insert:function(__llrint = llrint)]
%[insert:function(__llround = llround)]
%[insert:function(__llrintf = llrintf)]
%[insert:function(__llroundf = llroundf)]
%#endif /* __COMPILER_HAVE_LONGLONG */

%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__nexttowardl = nextafterl)]
%[insert:function(__scalbnl = scalbnl)]
%[insert:function(__scalblnl = scalblnl)]
%[insert:function(__nearbyintl = rintl)]
%[insert:function(__roundl = roundl)]
%[insert:function(__truncl = truncl)]
%[insert:function(__remquol = remquol)]
%[insert:function(__lrintl = lrintl)]
%[insert:function(__lroundl = lroundl)]
%[insert:function(__fdiml = fdiml)]
%[insert:function(__fmaxl = fmaxl)]
%[insert:function(__fminl = fminl)]
%[insert:function(__fmal = fmal)]
%#ifdef __COMPILER_HAVE_LONGLONG
%[insert:function(__llrintl = llrintl)]
%[insert:function(__llroundl = llroundl)]
%#endif /* __COMPILER_HAVE_LONGLONG */
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_ISOC99 */

%
%#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8))
%[insert:function(__scalb = scalb)]
%#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K8) */
%#ifdef __USE_MISC
%[insert:function(__scalbf = scalbf)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__scalbl = scalbl)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */
%#endif /* GLIBc aliases */



%
%
%/* Floating point classification */
%#ifdef __USE_ISOC99
[[wunused, nothrow, ATTR_CONST, export_alias("_dclass", "fpclassify")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/fpclassify.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
int __fpclassify(double x) {
@@pp_ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__@@
	return __ieee754_fpclassify((__IEEE754_DOUBLE_TYPE__)x);
@@pp_elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)@@
	return __ieee754_fpclassifyf((__IEEE754_FLOAT_TYPE__)x);
@@pp_else@@
	return __ieee854_fpclassifyl((__IEEE854_LONG_DOUBLE_TYPE__)x);
@@pp_endif@@
}


[[wunused, nothrow, ATTR_CONST, export_alias("_dsign")]]
[[impl_include("<libm/signbit.h>")]]
int __signbit(double x) {
@@pp_ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__@@
	return __ieee754_signbit((__IEEE754_DOUBLE_TYPE__)x);
@@pp_elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)@@
	return __ieee754_signbitf((__IEEE754_FLOAT_TYPE__)x);
@@pp_elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)@@
	return __ieee854_signbitl((__IEEE854_LONG_DOUBLE_TYPE__)x);
@@pp_else@@
	return x < 0.0;
@@pp_endif@@
}


[[export_alias("_fdclass", "fpclassifyf")]] __fpclassifyf(*) %{generate(double2float("__fpclassify"))}
[[export_alias("_fdsign")]]                 __signbitf(*) %{generate(double2float("__signbit"))}
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[export_alias("_ldclass", "fpclassifyl")]] __fpclassifyl(*) %{generate(double2ldouble("__fpclassify"))}
[[export_alias("_ldsign")]]                 __signbitl(*) %{generate(double2ldouble("__signbit"))}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_ISOC99 */

%
%#ifdef __USE_GNU
[[wunused, nothrow, ATTR_CONST, preferred_export_alias("issignaling")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/issignaling.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
int __issignaling(double x) {
@@pp_ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__@@
	return __ieee754_issignaling((__IEEE754_DOUBLE_TYPE__)x);
@@pp_elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)@@
	return __ieee754_issignalingf((__IEEE754_FLOAT_TYPE__)x);
@@pp_else@@
	return __ieee854_issignalingl((__IEEE854_LONG_DOUBLE_TYPE__)x);
@@pp_endif@@
}

[[preferred_export_alias("issignalingf")]]
__issignalingf(*) %{generate(double2float("__issignaling"))}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[preferred_export_alias("issignalingl")]]
__issignalingl(*) %{generate(double2ldouble("__issignaling"))}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_GNU */

[[wunused, ATTR_CONST, ignore, nocrt, alias("_dpcomp")]]
int _dpcomp(double x, double y) /* TODO */;

[[ignore, nocrt, alias("_fdpcomp")]] _fdpcomp(*) %{generate(double2float("_dpcomp"))}
[[ignore, nocrt, alias("_ldpcomp")]] _ldpcomp(*) %{generate(double2ldouble("_dpcomp"))}

%[insert:function(__dos_dpcomp = _dpcomp)]
%[insert:function(__dos_fdpcomp = _fdpcomp)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__dos_ldpcomp = _ldpcomp)]
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
#endif /* ... */

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

#if (defined(__FP_NAN) || defined(__FP_INFINITE) ||   \
     defined(__FP_ZERO) || defined(__FP_SUBNORMAL) || \
     defined(__FP_NORMAL))
/* All floating-point numbers can be put in one of these categories. */
/* NOTE: These values must match the declarations from <libm/fdlibm.h>! */
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __FP_NAN
	FP_NAN = __FP_NAN, /* ... */
#endif /* __FP_NAN */
#ifdef __FP_INFINITE
	FP_INFINITE = __FP_INFINITE, /* ... */
#endif /* __FP_INFINITE */
#ifdef __FP_ZERO
	FP_ZERO = __FP_ZERO, /* ... */
#endif /* __FP_ZERO */
#ifdef __FP_SUBNORMAL
	FP_SUBNORMAL = __FP_SUBNORMAL, /* ... */
#endif /* __FP_SUBNORMAL */
#ifdef __FP_NORMAL
	FP_NORMAL = __FP_NORMAL /* ... */
#endif /* __FP_NORMAL */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __FP_NAN
#define FP_NAN       FP_NAN       /* ... */
#endif /* __FP_NAN */
#ifdef __FP_INFINITE
#define FP_INFINITE  FP_INFINITE  /* ... */
#endif /* __FP_INFINITE */
#ifdef __FP_ZERO
#define FP_ZERO      FP_ZERO      /* ... */
#endif /* __FP_ZERO */
#ifdef __FP_SUBNORMAL
#define FP_SUBNORMAL FP_SUBNORMAL /* ... */
#endif /* __FP_SUBNORMAL */
#ifdef __FP_NORMAL
#define FP_NORMAL    FP_NORMAL    /* ... */
#endif /* __FP_NORMAL */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __FP_NAN
#define FP_NAN       __FP_NAN       /* ... */
#endif /* __FP_NAN */
#ifdef __FP_INFINITE
#define FP_INFINITE  __FP_INFINITE  /* ... */
#endif /* __FP_INFINITE */
#ifdef __FP_ZERO
#define FP_ZERO      __FP_ZERO      /* ... */
#endif /* __FP_ZERO */
#ifdef __FP_SUBNORMAL
#define FP_SUBNORMAL __FP_SUBNORMAL /* ... */
#endif /* __FP_SUBNORMAL */
#ifdef __FP_NORMAL
#define FP_NORMAL    __FP_NORMAL    /* ... */
#endif /* __FP_NORMAL */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */

/* `float' expressions are evaluated as this. */
typedef __float_t  float_t;

/* `double' expressions are evaluated as this. */
typedef __double_t double_t;


#ifndef __OPTIMIZE_SIZE__
#if __has_builtin(__builtin_signbitf) && __has_builtin(__builtin_signbit) && __has_builtin(__builtin_signbitl)
#define signbit(x) __FPFUNC(x, __builtin_signbitf, __builtin_signbit, __builtin_signbitl)
#endif /* __builtin_signbitf && __builtin_signbit && __builtin_signbitl */
#ifndef __SUPPORT_SNAN__
#if (__has_builtin(__builtin_fpclassify) &&             \
     defined(__FP_NAN) && defined(__FP_INFINITE) &&     \
     defined(__FP_NORMAL) && defined(__FP_SUBNORMAL) && \
     defined(__FP_ZERO))
#define fpclassify(x) __builtin_fpclassify(__FP_NAN, __FP_INFINITE, __FP_NORMAL, __FP_SUBNORMAL, __FP_ZERO, x)
#endif /* __builtin_fpclassify && defined(__FP_...) */
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
#ifdef __FP_NORMAL
#define isnormal(x) (fpclassify(x) == __FP_NORMAL)
#endif /* __FP_NORMAL */
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
#if defined(fpclassify) && defined(__FP_NAN)
#define isunordered(u, v) (fpclassify(u) == __FP_NAN || fpclassify(v) == __FP_NAN)
#else /* fpclassify && __FP_NAN */
#define isunordered(u, v) 0
#endif /* !fpclassify || !__FP_NAN */
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
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST int __NOTHROW(fpclassify)(float __x) { return fpclassify(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST int __NOTHROW(fpclassify)(double __x) { return fpclassify(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST int __NOTHROW(fpclassify)(__LONGDOUBLE __x) { return fpclassify(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_fpclassify_defined */
#undef fpclassify
#endif /* fpclassify */
#ifdef signbit
#ifndef __std_signbit_defined
#define __std_signbit_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(signbit)(float __x) { return signbit(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(signbit)(double __x) { return signbit(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(signbit)(__LONGDOUBLE __x) { return signbit(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_signbit_defined */
#undef signbit
#endif /* signbit */
#ifdef isnormal
#ifndef __std_isnormal_defined
#define __std_isnormal_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isnormal)(float __x) { return isnormal(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isnormal)(double __x) { return isnormal(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isnormal)(__LONGDOUBLE __x) { return isnormal(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isnormal_defined */
#undef isnormal
#endif /* isnormal */
#ifdef isfinite
#ifndef __std_isfinite_defined
#define __std_isfinite_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isfinite)(float __x) { return isfinite(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isfinite)(double __x) { return isfinite(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isfinite)(__LONGDOUBLE __x) { return isfinite(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isfinite_defined */
#undef isfinite
#endif /* isfinite */
#ifdef isnan
#ifndef __std_isnan_defined
#define __std_isnan_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isnan)(float __x) { return isnan(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isnan)(double __x) { return isnan(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isnan)(__LONGDOUBLE __x) { return isnan(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isnan_defined */
#undef isnan
#endif /* isnan */
#ifdef isinf
#ifndef __std_isinf_defined
#define __std_isinf_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isinf)(float __x) { return isinf(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isinf)(double __x) { return isinf(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isinf)(__LONGDOUBLE __x) { return isinf(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isinf_defined */
#undef isinf
#endif /* isinf */
#ifdef isunordered
#ifndef __std_isunordered_defined
#define __std_isunordered_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isunordered)(float __x, float __y) { return isunordered(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isunordered)(double __x, double __y) { return isunordered(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isunordered)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return isunordered(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isunordered_defined */
#undef isunordered
#endif /* isunordered */
#ifdef isgreater
#ifndef __std_isgreater_defined
#define __std_isgreater_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isgreater)(float __x, float __y) { return isgreater(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isgreater)(double __x, double __y) { return isgreater(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isgreater)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return isgreater(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isgreater_defined */
#undef isgreater
#endif /* isgreater */
#ifdef isgreaterequal
#ifndef __std_isgreaterequal_defined
#define __std_isgreaterequal_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isgreaterequal)(float __x, float __y) { return isgreaterequal(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isgreaterequal)(double __x, double __y) { return isgreaterequal(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isgreaterequal)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return isgreaterequal(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isgreaterequal_defined */
#undef isgreaterequal
#endif /* isgreaterequal */
#ifdef isless
#ifndef __std_isless_defined
#define __std_isless_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isless)(float __x, float __y) { return isless(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isless)(double __x, double __y) { return isless(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isless)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return isless(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isless_defined */
#undef isless
#endif /* isless */
#ifdef islessequal
#ifndef __std_islessequal_defined
#define __std_islessequal_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(islessequal)(float __x, float __y) { return islessequal(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(islessequal)(double __x, double __y) { return islessequal(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(islessequal)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return islessequal(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_islessequal_defined */
#undef islessequal
#endif /* islessequal */
#ifdef islessgreater
#ifndef __std_islessgreater_defined
#define __std_islessgreater_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(islessgreater)(float __x, float __y) { return islessgreater(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(islessgreater)(double __x, double __y) { return islessgreater(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(islessgreater)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return islessgreater(__x, __y); }
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
#if (defined(___IEEE_) || defined(___SVID_) ||   \
     defined(___XOPEN_) || defined(___POSIX_) || \
     defined(___ISOC_))
}%[push_macro @undef { _IEEE_ _SVID_ _XOPEN_ _POSIX_ _ISOC_ }]%{
/* Support for various different standard error handling behaviors. */
typedef enum {
#ifdef ___IEEE_
	_IEEE_ = ___IEEE_,   /* According to IEEE 754/IEEE 854. */
#endif /* ___IEEE_ */
#ifdef ___SVID_
	_SVID_ = ___SVID_,   /* According to System V, release 4. */
#endif /* ___SVID_ */
#ifdef ___XOPEN_
	_XOPEN_ = ___XOPEN_, /* Nowadays also Unix98. */
#endif /* ___XOPEN_ */
#ifdef ___POSIX_
	_POSIX_ = ___POSIX_, /* ... */
#endif /* ___POSIX_ */
#ifdef ___ISOC_
	_ISOC_ = ___ISOC_    /* Actually this is ISO C99. */
#endif /* ___ISOC_ */
} _LIB_VERSION_TYPE;
}%[pop_macro]%{

/* This variable can be changed at run-time to any of the values above to
 * affect floating point error handling behavior (it may also be necessary
 * to change the hardware FPU exception settings). */
#ifdef __CRT_HAVE__LIB_VERSION
}%[push_macro @undef { _LIB_VERSION }]%{
__LIBC _LIB_VERSION_TYPE _LIB_VERSION;
}%[pop_macro]%{
#endif /* __CRT_HAVE__LIB_VERSION */
#endif /* ... */


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

#define X_TLOSS 1.41484755040568800000e+16

/* Types of exceptions in the `type' field. */
#ifdef __MATH_EXCEPT_DOMAIN
#define DOMAIN __MATH_EXCEPT_DOMAIN /* ... */
#endif /* __MATH_EXCEPT_DOMAIN */
#ifdef __MATH_EXCEPT_SING
#define SING __MATH_EXCEPT_SING /* ... */
#endif /* __MATH_EXCEPT_SING */
#ifdef __MATH_EXCEPT_OVERFLOW
#define OVERFLOW __MATH_EXCEPT_OVERFLOW /* ... */
#endif /* __MATH_EXCEPT_OVERFLOW */
#ifdef __MATH_EXCEPT_UNDERFLOW
#define UNDERFLOW __MATH_EXCEPT_UNDERFLOW /* ... */
#endif /* __MATH_EXCEPT_UNDERFLOW */
#ifdef __MATH_EXCEPT_TLOSS
#define TLOSS __MATH_EXCEPT_TLOSS /* ... */
#endif /* __MATH_EXCEPT_TLOSS */
#ifdef __MATH_EXCEPT_PLOSS
#define PLOSS __MATH_EXCEPT_PLOSS /* ... */
#endif /* __MATH_EXCEPT_PLOSS */

/* SVID mode specifies returning this large value instead of infinity. */
#define HUGE 3.40282347e+38F

#else /* __USE_MISC */
#ifdef __USE_XOPEN
/* X/Open wants another strange constant. */
#define MAXFLOAT 3.40282347e+38F
#endif /* __USE_XOPEN */
#endif /* !__USE_MISC */

}


%{
#endif /* __CC__ */

__SYSDECL_END

}
%(c, ccompat)#endif /* !__NO_FPU */
