/* HASH CRC-32:0x7befa274 */
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
#ifndef GUARD_LIBC_USER_MATH_H
#define GUARD_LIBC_USER_MATH_H 1

#include "../api.h"
#include "../auto/math.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <math.h>

DECL_BEGIN

/* Arc cosine of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_acos)(double x);
/* Arc sine of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_asin)(double x);
/* Arc tangent of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_atan)(double x);
/* Arc tangent of Y/X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_atan2)(double y, double x);
/* Cosine of X */
INTDEF __DECL_SIMD_cos WUNUSED double NOTHROW(LIBCCALL libc_cos)(double x);
/* Sine of X */
INTDEF __DECL_SIMD_sin WUNUSED double NOTHROW(LIBCCALL libc_sin)(double x);
/* Tangent of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_tan)(double x);
/* Arc cosine of X */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_acosf)(float x);
/* Arc sine of X */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_asinf)(float x);
/* Arc tangent of X */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_atanf)(float x);
/* Arc tangent of Y/X */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_atan2f)(float y, float x);
/* Cosine of X */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_cosf)(float x);
/* Sine of X */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_sinf)(float x);
/* Tangent of X */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_tanf)(float x);
/* Arc cosine of X */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_acosl)(__LONGDOUBLE x);
/* Arc sine of X */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_asinl)(__LONGDOUBLE x);
/* Arc tangent of X */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_atanl)(__LONGDOUBLE x);
/* Arc tangent of Y/X */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_atan2l)(__LONGDOUBLE y, __LONGDOUBLE x);
/* Cosine of X */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_cosl)(__LONGDOUBLE x);
/* Sine of X */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_sinl)(__LONGDOUBLE x);
/* Tangent of X */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_tanl)(__LONGDOUBLE x);
/* Hyperbolic cosine of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_cosh)(double x);
/* Hyperbolic sine of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_sinh)(double x);
/* Hyperbolic tangent of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_tanh)(double x);
/* Hyperbolic cosine of X */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_coshf)(float x);
/* Hyperbolic sine of X */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_sinhf)(float x);
/* Hyperbolic tangent of X */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_tanhf)(float x);
/* Hyperbolic cosine of X */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_coshl)(__LONGDOUBLE x);
/* Hyperbolic sine of X */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_sinhl)(__LONGDOUBLE x);
/* Hyperbolic tangent of X */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_tanhl)(__LONGDOUBLE x);
/* Hyperbolic arc cosine of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_acosh)(double x);
/* Hyperbolic arc sine of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_asinh)(double x);
/* Hyperbolic arc tangent of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_atanh)(double x);
/* Hyperbolic arc cosine of X */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_acoshf)(float x);
/* Hyperbolic arc sine of X */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_asinhf)(float x);
/* Hyperbolic arc tangent of X */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_atanhf)(float x);
/* Hyperbolic arc cosine of X */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_acoshl)(__LONGDOUBLE x);
/* Hyperbolic arc sine of X */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_asinhl)(__LONGDOUBLE x);
/* Hyperbolic arc tangent of X */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_atanhl)(__LONGDOUBLE x);
/* Exponential function of X */
INTDEF __DECL_SIMD_exp WUNUSED double NOTHROW(LIBCCALL libc_exp)(double x);
/* Break VALUE into a normalized fraction and an integral power of 2 */
INTDEF WUNUSED double NOTHROW_NCX(LIBCCALL libc_frexp)(double x, int *pexponent);
/* X times (two to the EXP power) */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_ldexp)(double x, int exponent);
/* Natural logarithm of X */
INTDEF __DECL_SIMD_log WUNUSED double NOTHROW(LIBCCALL libc_log)(double x);
/* Base-ten logarithm of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_log10)(double x);
/* Break VALUE into integral and fractional parts */
INTDEF WUNUSED NONNULL((2)) double NOTHROW_NCX(LIBCCALL libc_modf)(double x, double *iptr);
/* Exponential function of X */
INTDEF __DECL_SIMD_expf WUNUSED float NOTHROW(LIBCCALL libc_expf)(float x);
/* Break VALUE into a normalized fraction and an integral power of 2 */
INTDEF WUNUSED float NOTHROW_NCX(LIBCCALL libc_frexpf)(float x, int *pexponent);
/* X times (two to the EXP power) */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_ldexpf)(float x, int exponent);
/* Natural logarithm of X */
INTDEF __DECL_SIMD_logf WUNUSED float NOTHROW(LIBCCALL libc_logf)(float x);
/* Base-ten logarithm of X */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_log10f)(float x);
/* Break VALUE into integral and fractional parts */
INTDEF NONNULL((2)) float NOTHROW_NCX(LIBCCALL libc_modff)(float x, float *iptr);
/* Exponential function of X */
INTDEF __DECL_SIMD_expl WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_expl)(__LONGDOUBLE x);
/* Break VALUE into a normalized fraction and an integral power of 2 */
INTDEF WUNUSED __LONGDOUBLE NOTHROW_NCX(LIBCCALL libc_frexpl)(__LONGDOUBLE x, int *pexponent);
/* X times (two to the EXP power) */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_ldexpl)(__LONGDOUBLE x, int exponent);
/* Natural logarithm of X */
INTDEF __DECL_SIMD_logl WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_logl)(__LONGDOUBLE x);
/* Base-ten logarithm of X */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_log10l)(__LONGDOUBLE x);
/* Break VALUE into integral and fractional parts */
INTDEF NONNULL((2)) __LONGDOUBLE NOTHROW_NCX(LIBCCALL libc_modfl)(__LONGDOUBLE x, __LONGDOUBLE *iptr);
/* Return exp(X) - 1 */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_expm1)(double x);
/* Return log(1 + X) */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_log1p)(double x);
/* Return the base 2 signed integral exponent of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_logb)(double x);
/* Return exp(X) - 1 */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_expm1f)(float x);
/* Return log(1 + X) */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_log1pf)(float x);
/* Return the base 2 signed integral exponent of X */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_logbf)(float x);
/* Return exp(X) - 1 */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_expm1l)(__LONGDOUBLE x);
/* Return log(1 + X) */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_log1pl)(__LONGDOUBLE x);
/* Return the base 2 signed integral exponent of X */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_logbl)(__LONGDOUBLE x);
/* Compute base-2 exponential of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_exp2)(double x);
/* Compute base-2 logarithm of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_log2)(double x);
/* Compute base-2 exponential of X */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_exp2f)(float x);
/* Compute base-2 logarithm of X */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_log2f)(float x);
/* Compute base-2 exponential of X */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_exp2l)(__LONGDOUBLE x);
/* Compute base-2 logarithm of X */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_log2l)(__LONGDOUBLE x);
/* Return X to the Y power */
INTDEF __DECL_SIMD_pow WUNUSED double NOTHROW(LIBCCALL libc_pow)(double x, double y);
/* Return the square root of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_sqrt)(double x);
/* Return X to the Y power */
INTDEF __DECL_SIMD_powf WUNUSED float NOTHROW(LIBCCALL libc_powf)(float x, float y);
/* Return the square root of X */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_sqrtf)(float x);
/* Return X to the Y power */
INTDEF __DECL_SIMD_powl WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_powl)(__LONGDOUBLE x, __LONGDOUBLE y);
/* Return the square root of X */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_sqrtl)(__LONGDOUBLE x);
/* Return `sqrt(X*X + Y*Y)' */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_hypot)(double x, double y);
/* Return `sqrt(X*X + Y*Y)' */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_hypotf)(float x, float y);
/* Return `sqrt(X*X + Y*Y)' */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_hypotl)(__LONGDOUBLE x, __LONGDOUBLE y);
/* Return the cube root of X */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_cbrt)(double x);
/* Return the cube root of X */
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc_cbrtf)(float x);
/* Return the cube root of X */
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_cbrtl)(__LONGDOUBLE x);
/* Absolute value of X */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_fabs)(double x);
/* Floating-point modulo remainder of X/Y */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_fmod)(double x, double y);
/* Absolute value of X */
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc_fabsf)(float x);
/* Floating-point modulo remainder of X/Y */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_fmodf)(float x, float y);
/* Return X with its signed changed to Y's */
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_fabsl)(__LONGDOUBLE x);
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_fmodl)(__LONGDOUBLE x, __LONGDOUBLE y);
/* Return X with its signed changed to Y's */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_copysign)(double num, double sign);
/* Return X with its signed changed to Y's */
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc_copysignf)(float num, float sign);
/* Return X with its signed changed to Y's */
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_copysignl)(__LONGDOUBLE num, __LONGDOUBLE sign);
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_erf)(double x);
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_erfc)(double x);
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_lgamma)(double x);
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_erff)(float x);
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_erfcf)(float x);
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_lgammaf)(float x);
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_erfl)(__LONGDOUBLE x);
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_erfcl)(__LONGDOUBLE x);
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_lgammal)(__LONGDOUBLE x);
/* True gamma function */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_tgamma)(double x);
/* True gamma function */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_tgammaf)(float x);
/* True gamma function */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_tgammal)(__LONGDOUBLE x);
/* Return the integer nearest X in the direction of the prevailing rounding mode */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_rint)(double x);
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_nextafter)(double x, double y);
/* Return the remainder of integer divison X/P with infinite precision */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_remainder)(double x, double p);
/* Return the binary exponent of X, which must be nonzero */
INTDEF WUNUSED int NOTHROW(LIBCCALL libc_ilogb)(double x);
/* Return the integer nearest X in the direction of the prevailing rounding mode */
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc_rintf)(float x);
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc_nextafterf)(float x, float y);
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_remainderf)(float x, float p);
/* Return the binary exponent of X, which must be nonzero */
INTDEF WUNUSED int NOTHROW(LIBCCALL libc_ilogbf)(float x);
/* Return the integer nearest X in the direction of the prevailing rounding mode */
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_rintl)(__LONGDOUBLE x);
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_nextafterl)(__LONGDOUBLE x, __LONGDOUBLE y);
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_remainderl)(__LONGDOUBLE x, __LONGDOUBLE p);
/* Return the binary exponent of X, which must be nonzero */
INTDEF WUNUSED int NOTHROW(LIBCCALL libc_ilogbl)(__LONGDOUBLE x);
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_nexttoward)(double x, __LONGDOUBLE y);
/* Return X times (2 to the Nth power) */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_scalbn)(double x, int n);
/* Return X times (2 to the Nth power) */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_scalbln)(double x, long int n);
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_remquo)(double x, double y, int *pquo);
/* Round X to nearest integral value according to current rounding direction */
INTDEF WUNUSED long int NOTHROW(LIBCCALL libc_lrint)(double x);
/* Return positive difference between X and Y */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_fdim)(double x, double y);
/* Round X to nearest integral value according to current rounding direction */
INTDEF WUNUSED __LONGLONG NOTHROW(LIBCCALL libc_llrint)(double x);
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc_nexttowardf)(float x, __LONGDOUBLE y);
/* Return X times (2 to the Nth power) */
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc_scalbnf)(float x, int n);
/* Return X times (2 to the Nth power) */
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc_scalblnf)(float x, long int n);
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_remquof)(float x, float y, int *pquo);
/* Round X to nearest integral value according to current rounding direction */
INTDEF WUNUSED long int NOTHROW(LIBCCALL libc_lrintf)(float x);
/* Return positive difference between X and Y */
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc_fdimf)(float x, float y);
/* Round X to nearest integral value according to current rounding direction */
INTDEF ATTR_CONST WUNUSED __LONGLONG NOTHROW(LIBCCALL libc_llrintf)(float x);
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_nexttowardl)(__LONGDOUBLE x, __LONGDOUBLE y);
/* Return X times (2 to the Nth power) */
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_scalbnl)(__LONGDOUBLE x, int n);
/* Return X times (2 to the Nth power) */
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_scalblnl)(__LONGDOUBLE x, long int n);
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_remquol)(__LONGDOUBLE x, __LONGDOUBLE y, int *pquo);
/* Round X to nearest integral value according to current rounding direction */
INTDEF WUNUSED long int NOTHROW(LIBCCALL libc_lrintl)(__LONGDOUBLE x);
/* Return positive difference between X and Y */
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_fdiml)(__LONGDOUBLE x, __LONGDOUBLE y);
/* Round X to nearest integral value according to current rounding direction */
INTDEF WUNUSED __LONGLONG NOTHROW(LIBCCALL libc_llrintl)(__LONGDOUBLE x);
/* Cosine and sine of X */
INTDEF __DECL_SIMD_sincos NONNULL((2, 3)) void NOTHROW(LIBCCALL libc_sincos)(double x, double *psinx, double *pcosx);
/* A function missing in all standards: compute exponent to base ten */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_exp10)(double x);
/* Another name occasionally used */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_pow10)(double x);
/* Cosine and sine of X */
INTDEF __DECL_SIMD_sincosf NONNULL((2, 3)) void NOTHROW(LIBCCALL libc_sincosf)(float x, float *psinx, float *pcosx);
/* A function missing in all standards: compute exponent to base ten */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_exp10f)(float x);
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_pow10f)(float x);
/* Cosine and sine of X */
INTDEF __DECL_SIMD_sincosl NONNULL((2, 3)) void NOTHROW(LIBCCALL libc_sincosl)(__LONGDOUBLE x, __LONGDOUBLE *psinx, __LONGDOUBLE *pcosx);
/* A function missing in all standards: compute exponent to base ten */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_exp10l)(__LONGDOUBLE x);
/* Another name occasionally used */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_pow10l)(__LONGDOUBLE x);
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isinf)(double x);
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isinff)(float x);
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isinfl)(__LONGDOUBLE x);
/* Return nonzero if VALUE is finite and not NaN */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_finite)(double x);
/* Return the fractional part of X after dividing out `ilogb (X)' */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_significand)(double x);
/* Return nonzero if VALUE is finite and not NaN */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_finitef)(float x);
/* Return the fractional part of X after dividing out `ilogb (X)' */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_significandf)(float x);
/* Return nonzero if VALUE is finite and not NaN */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_finitel)(__LONGDOUBLE x);
/* Return the fractional part of X after dividing out `ilogb (X)' */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_significandl)(__LONGDOUBLE x);
/* Return nonzero if VALUE is not a number */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isnan)(double x);
/* Return nonzero if VALUE is not a number */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isnanf)(float x);
/* Return nonzero if VALUE is not a number */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isnanl)(__LONGDOUBLE x);
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_j0)(double x);
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_j1)(double x);
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_jn)(int n, double x);
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_y0)(double x);
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_y1)(double x);
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_yn)(int n, double x);
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_j0f)(float x);
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_j1f)(float x);
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_jnf)(int n, float x);
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_y0f)(float x);
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_y1f)(float x);
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_ynf)(int n, float x);
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_j0l)(__LONGDOUBLE x);
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_j1l)(__LONGDOUBLE x);
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_jnl)(int n, __LONGDOUBLE x);
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_y0l)(__LONGDOUBLE x);
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_y1l)(__LONGDOUBLE x);
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_ynl)(int n, __LONGDOUBLE x);
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
INTDEF WUNUSED double NOTHROW_NCX(LIBCCALL libc_lgamma_r)(double x, int *signgamp);
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
INTDEF WUNUSED float NOTHROW_NCX(LIBCCALL libc_lgammaf_r)(float x, int *signgamp);
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
INTDEF WUNUSED __LONGDOUBLE NOTHROW_NCX(LIBCCALL libc_lgammal_r)(__LONGDOUBLE x, int *signgamp);
/* Return X times (2 to the Nth power) */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_scalb)(double x, double fn);
/* Return X times (2 to the Nth power) */
INTDEF WUNUSED float NOTHROW(LIBCCALL libc_scalbf)(float x, float fn);
/* Return X times (2 to the Nth power) */
INTDEF WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_scalbl)(__LONGDOUBLE x, __LONGDOUBLE n);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc___fpclassify)(double x);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc___fpclassifyf)(float x);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc___fpclassifyl)(__LONGDOUBLE x);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc___issignaling)(double x);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc___issignalingf)(float x);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc___issignalingl)(__LONGDOUBLE x);

DECL_END

#endif /* !GUARD_LIBC_USER_MATH_H */
