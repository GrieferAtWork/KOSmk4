/* HASH CRC-32:0x4e53f3b2 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_MATH_C
#define GUARD_LIBC_AUTO_DOSABI_MATH_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/math.h"

DECL_BEGIN

/* Arc cosine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_acos)(double x) {
	return libc_acos(x);
}
/* Arc sine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_asin)(double x) {
	return libc_asin(x);
}
/* Arc tangent of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_atan)(double x) {
	return libc_atan(x);
}
/* Arc tangent of Y/X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_atan2)(double y,
                             double x) {
	return libc_atan2(y, x);
}
/* Cosine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __DECL_SIMD_cos double
NOTHROW(LIBDCALL libd_cos)(double x) {
	return libc_cos(x);
}
/* Sine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __DECL_SIMD_sin double
NOTHROW(LIBDCALL libd_sin)(double x) {
	return libc_sin(x);
}
/* Tangent of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_tan)(double x) {
	return libc_tan(x);
}
/* Arc cosine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_acosf)(float x) {
	return libc_acosf(x);
}
/* Arc sine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_asinf)(float x) {
	return libc_asinf(x);
}
/* Arc tangent of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_atanf)(float x) {
	return libc_atanf(x);
}
/* Arc tangent of Y/X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_atan2f)(float y,
                              float x) {
	return libc_atan2f(y, x);
}
/* Cosine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __DECL_SIMD_cosf float
NOTHROW(LIBDCALL libd_cosf)(float x) {
	return libc_cosf(x);
}
/* Sine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __DECL_SIMD_sinf float
NOTHROW(LIBDCALL libd_sinf)(float x) {
	return libc_sinf(x);
}
/* Tangent of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_tanf)(float x) {
	return libc_tanf(x);
}
/* Arc cosine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_acosl)(__LONGDOUBLE x) {
	return libc_acosl(x);
}
/* Arc sine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_asinl)(__LONGDOUBLE x) {
	return libc_asinl(x);
}
/* Arc tangent of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_atanl)(__LONGDOUBLE x) {
	return libc_atanl(x);
}
/* Arc tangent of Y/X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_atan2l)(__LONGDOUBLE y,
                              __LONGDOUBLE x) {
	return libc_atan2l(y, x);
}
/* Cosine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __DECL_SIMD_cosl __LONGDOUBLE
NOTHROW(LIBDCALL libd_cosl)(__LONGDOUBLE x) {
	return libc_cosl(x);
}
/* Sine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __DECL_SIMD_sinl __LONGDOUBLE
NOTHROW(LIBDCALL libd_sinl)(__LONGDOUBLE x) {
	return libc_sinl(x);
}
/* Tangent of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_tanl)(__LONGDOUBLE x) {
	return libc_tanl(x);
}
/* Hyperbolic cosine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_cosh)(double x) {
	return libc_cosh(x);
}
/* Hyperbolic sine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_sinh)(double x) {
	return libc_sinh(x);
}
/* Hyperbolic tangent of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_tanh)(double x) {
	return libc_tanh(x);
}
/* Hyperbolic cosine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_coshf)(float x) {
	return libc_coshf(x);
}
/* Hyperbolic sine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_sinhf)(float x) {
	return libc_sinhf(x);
}
/* Hyperbolic tangent of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_tanhf)(float x) {
	return libc_tanhf(x);
}
/* Hyperbolic cosine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_coshl)(__LONGDOUBLE x) {
	return libc_coshl(x);
}
/* Hyperbolic sine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_sinhl)(__LONGDOUBLE x) {
	return libc_sinhl(x);
}
/* Hyperbolic tangent of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_tanhl)(__LONGDOUBLE x) {
	return libc_tanhl(x);
}
/* Hyperbolic arc cosine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_acosh)(double x) {
	return libc_acosh(x);
}
/* Hyperbolic arc sine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_asinh)(double x) {
	return libc_asinh(x);
}
/* Hyperbolic arc tangent of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_atanh)(double x) {
	return libc_atanh(x);
}
/* Hyperbolic arc cosine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_acoshf)(float x) {
	return libc_acoshf(x);
}
/* Hyperbolic arc sine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_asinhf)(float x) {
	return libc_asinhf(x);
}
/* Hyperbolic arc tangent of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_atanhf)(float x) {
	return libc_atanhf(x);
}
/* Hyperbolic arc cosine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_acoshl)(__LONGDOUBLE x) {
	return libc_acoshl(x);
}
/* Hyperbolic arc sine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_asinhl)(__LONGDOUBLE x) {
	return libc_asinhl(x);
}
/* Hyperbolic arc tangent of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_atanhl)(__LONGDOUBLE x) {
	return libc_atanhl(x);
}
/* Exponential function of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __DECL_SIMD_exp double
NOTHROW(LIBDCALL libd_exp)(double x) {
	return libc_exp(x);
}
/* Break VALUE into a normalized fraction and an integral power of 2 */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED NONNULL((2)) double
NOTHROW_NCX(LIBDCALL libd_frexp)(double x,
                                 int *pexponent) {
	return libc_frexp(x, pexponent);
}
/* X times (two to the EXP power) */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_ldexp)(double x,
                             int exponent) {
	return libc_ldexp(x, exponent);
}
/* Natural logarithm of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __DECL_SIMD_log double
NOTHROW(LIBDCALL libd_log)(double x) {
	return libc_log(x);
}
/* Base-ten logarithm of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_log10)(double x) {
	return libc_log10(x);
}
/* Break VALUE into integral and fractional parts */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED NONNULL((2)) double
NOTHROW_NCX(LIBDCALL libd_modf)(double x,
                                double *iptr) {
	return libc_modf(x, iptr);
}
/* Exponential function of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __DECL_SIMD_expf float
NOTHROW(LIBDCALL libd_expf)(float x) {
	return libc_expf(x);
}
/* Break VALUE into a normalized fraction and an integral power of 2 */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED NONNULL((2)) float
NOTHROW_NCX(LIBDCALL libd_frexpf)(float x,
                                  int *pexponent) {
	return libc_frexpf(x, pexponent);
}
/* X times (two to the EXP power) */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_ldexpf)(float x,
                              int exponent) {
	return libc_ldexpf(x, exponent);
}
/* Natural logarithm of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __DECL_SIMD_logf float
NOTHROW(LIBDCALL libd_logf)(float x) {
	return libc_logf(x);
}
/* Base-ten logarithm of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_log10f)(float x) {
	return libc_log10f(x);
}
/* Break VALUE into integral and fractional parts */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED NONNULL((2)) float
NOTHROW_NCX(LIBDCALL libd_modff)(float x,
                                 float *iptr) {
	return libc_modff(x, iptr);
}
/* Exponential function of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __DECL_SIMD_expl __LONGDOUBLE
NOTHROW(LIBDCALL libd_expl)(__LONGDOUBLE x) {
	return libc_expl(x);
}
/* Break VALUE into a normalized fraction and an integral power of 2 */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED NONNULL((2)) __LONGDOUBLE
NOTHROW_NCX(LIBDCALL libd_frexpl)(__LONGDOUBLE x,
                                  int *pexponent) {
	return libc_frexpl(x, pexponent);
}
/* X times (two to the EXP power) */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_ldexpl)(__LONGDOUBLE x,
                              int exponent) {
	return libc_ldexpl(x, exponent);
}
/* Natural logarithm of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __DECL_SIMD_logl __LONGDOUBLE
NOTHROW(LIBDCALL libd_logl)(__LONGDOUBLE x) {
	return libc_logl(x);
}
/* Base-ten logarithm of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_log10l)(__LONGDOUBLE x) {
	return libc_log10l(x);
}
/* Break VALUE into integral and fractional parts */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED NONNULL((2)) __LONGDOUBLE
NOTHROW_NCX(LIBDCALL libd_modfl)(__LONGDOUBLE x,
                                 __LONGDOUBLE *iptr) {
	return libc_modfl(x, iptr);
}
/* Return exp(X) - 1 */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_expm1)(double x) {
	return libc_expm1(x);
}
/* Return log(1 + X) */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_log1p)(double x) {
	return libc_log1p(x);
}
/* Return the base 2 signed integral exponent of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_logb)(double x) {
	return libc_logb(x);
}
/* Return exp(X) - 1 */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_expm1f)(float x) {
	return libc_expm1f(x);
}
/* Return log(1 + X) */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_log1pf)(float x) {
	return libc_log1pf(x);
}
/* Return the base 2 signed integral exponent of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_logbf)(float x) {
	return libc_logbf(x);
}
/* Return exp(X) - 1 */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_expm1l)(__LONGDOUBLE x) {
	return libc_expm1l(x);
}
/* Return log(1 + X) */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_log1pl)(__LONGDOUBLE x) {
	return libc_log1pl(x);
}
/* Return the base 2 signed integral exponent of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_logbl)(__LONGDOUBLE x) {
	return libc_logbl(x);
}
/* Compute base-2 exponential of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_exp2)(double x) {
	return libc_exp2(x);
}
/* Compute base-2 logarithm of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_log2)(double x) {
	return libc_log2(x);
}
/* Compute base-2 exponential of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_exp2f)(float x) {
	return libc_exp2f(x);
}
/* Compute base-2 logarithm of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_log2f)(float x) {
	return libc_log2f(x);
}
/* Compute base-2 exponential of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_exp2l)(__LONGDOUBLE x) {
	return libc_exp2l(x);
}
/* Compute base-2 logarithm of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_log2l)(__LONGDOUBLE x) {
	return libc_log2l(x);
}
/* Return X to the Y power */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __DECL_SIMD_pow double
NOTHROW(LIBDCALL libd_pow)(double x,
                           double y) {
	return libc_pow(x, y);
}
/* Return the square root of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_sqrt)(double x) {
	return libc_sqrt(x);
}
/* Return X to the Y power */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __DECL_SIMD_powf float
NOTHROW(LIBDCALL libd_powf)(float x,
                            float y) {
	return libc_powf(x, y);
}
/* Return the square root of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_sqrtf)(float x) {
	return libc_sqrtf(x);
}
/* Return X to the Y power */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __DECL_SIMD_powl __LONGDOUBLE
NOTHROW(LIBDCALL libd_powl)(__LONGDOUBLE x,
                            __LONGDOUBLE y) {
	return libc_powl(x, y);
}
/* Return the square root of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_sqrtl)(__LONGDOUBLE x) {
	return libc_sqrtl(x);
}
/* Return `sqrt(X*X + Y*Y)' */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_hypot)(double x,
                             double y) {
	return libc_hypot(x, y);
}
/* Return `sqrt(X*X + Y*Y)' */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_hypotf)(float x,
                              float y) {
	return libc_hypotf(x, y);
}
/* Return `sqrt(X*X + Y*Y)' */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_hypotl)(__LONGDOUBLE x,
                              __LONGDOUBLE y) {
	return libc_hypotl(x, y);
}
/* Return the cube root of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBDCALL libd_cbrt)(double x) {
	return libc_cbrt(x);
}
/* Return the cube root of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBDCALL libd_cbrtf)(float x) {
	return libc_cbrtf(x);
}
/* Return the cube root of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_cbrtl)(__LONGDOUBLE x) {
	return libc_cbrtl(x);
}
/* Smallest integral value not less than X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBDCALL libd_ceil)(double x) {
	return libc_ceil(x);
}
/* Absolute value of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBDCALL libd_fabs)(double x) {
	return libc_fabs(x);
}
/* Largest integer not greater than X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBDCALL libd_floor)(double x) {
	return libc_floor(x);
}
/* Floating-point modulo remainder of X/Y */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_fmod)(double x,
                            double y) {
	return libc_fmod(x, y);
}
/* Smallest integral value not less than X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBDCALL libd_ceilf)(float x) {
	return libc_ceilf(x);
}
/* Absolute value of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBDCALL libd_fabsf)(float x) {
	return libc_fabsf(x);
}
/* Largest integer not greater than X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBDCALL libd_floorf)(float x) {
	return libc_floorf(x);
}
/* Floating-point modulo remainder of X/Y */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_fmodf)(float x,
                             float y) {
	return libc_fmodf(x, y);
}
/* Smallest integral value not less than X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_ceill)(__LONGDOUBLE x) {
	return libc_ceill(x);
}
/* Absolute value of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_fabsl)(__LONGDOUBLE x) {
	return libc_fabsl(x);
}
/* Largest integer not greater than X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_floorl)(__LONGDOUBLE x) {
	return libc_floorl(x);
}
/* Floating-point modulo remainder of X/Y */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_fmodl)(__LONGDOUBLE x,
                             __LONGDOUBLE y) {
	return libc_fmodl(x, y);
}
/* Return X with its signed changed to Y's */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBDCALL libd_copysign)(double num,
                                double sign) {
	return libc_copysign(num, sign);
}
/* Return representation of qNaN for double type */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBDCALL libd_nan)(char const *tagb) {
	return libc_nan(tagb);
}
/* Return X with its signed changed to Y's */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBDCALL libd_copysignf)(float num,
                                 float sign) {
	return libc_copysignf(num, sign);
}
/* Return representation of qNaN for double type */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBDCALL libd_nanf)(char const *tagb) {
	return libc_nanf(tagb);
}
/* Return X with its signed changed to Y's */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_copysignl)(__LONGDOUBLE num,
                                 __LONGDOUBLE sign) {
	return libc_copysignl(num, sign);
}
/* Return representation of qNaN for double type */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_nanl)(char const *tagb) {
	return libc_nanl(tagb);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_erf)(double x) {
	return libc_erf(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_erfc)(double x) {
	return libc_erfc(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_lgamma)(double x) {
	return libc_lgamma(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_erff)(float x) {
	return libc_erff(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_erfcf)(float x) {
	return libc_erfcf(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_lgammaf)(float x) {
	return libc_lgammaf(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_erfl)(__LONGDOUBLE x) {
	return libc_erfl(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_erfcl)(__LONGDOUBLE x) {
	return libc_erfcl(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_lgammal)(__LONGDOUBLE x) {
	return libc_lgammal(x);
}
/* True gamma function */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_tgamma)(double x) {
	return libc_tgamma(x);
}
/* True gamma function */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_tgammaf)(float x) {
	return libc_tgammaf(x);
}
/* True gamma function */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_tgammal)(__LONGDOUBLE x) {
	return libc_tgammal(x);
}
/* Return the integer nearest X in the direction of the prevailing rounding mode */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBDCALL libd_rint)(double x) {
	return libc_rint(x);
}
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBDCALL libd_nextafter)(double x,
                                 double y) {
	return libc_nextafter(x, y);
}
/* Return the remainder of integer division X/P with infinite precision */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_remainder)(double x,
                                 double p) {
	return libc_remainder(x, p);
}
/* Return the binary exponent of X, which must be nonzero */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED int
NOTHROW(LIBDCALL libd_ilogb)(double x) {
	return libc_ilogb(x);
}
/* Return the integer nearest X in the direction of the prevailing rounding mode */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBDCALL libd_rintf)(float x) {
	return libc_rintf(x);
}
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBDCALL libd_nextafterf)(float x,
                                  float y) {
	return libc_nextafterf(x, y);
}
/* Return the remainder of integer division X/P with infinite precision */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_remainderf)(float x,
                                  float p) {
	return libc_remainderf(x, p);
}
/* Return the binary exponent of X, which must be nonzero */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED int
NOTHROW(LIBDCALL libd_ilogbf)(float x) {
	return libc_ilogbf(x);
}
/* Return the integer nearest X in the direction of the prevailing rounding mode */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_rintl)(__LONGDOUBLE x) {
	return libc_rintl(x);
}
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_nextafterl)(__LONGDOUBLE x,
                                  __LONGDOUBLE y) {
	return libc_nextafterl(x, y);
}
/* Return the remainder of integer division X/P with infinite precision */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_remainderl)(__LONGDOUBLE x,
                                  __LONGDOUBLE p) {
	return libc_remainderl(x, p);
}
/* Return the binary exponent of X, which must be nonzero */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED int
NOTHROW(LIBDCALL libd_ilogbl)(__LONGDOUBLE x) {
	return libc_ilogbl(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBDCALL libd_nexttoward)(double x,
                                  __LONGDOUBLE y) {
	return libc_nexttoward(x, y);
}
/* Return X times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBDCALL libd_scalbn)(double x,
                              int n) {
	return libc_scalbn(x, n);
}
/* Return X times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBDCALL libd_scalbln)(double x,
                               long int n) {
	return libc_scalbln(x, n);
}
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBDCALL libd_round)(double x) {
	return libc_round(x);
}
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBDCALL libd_trunc)(double x) {
	return libc_trunc(x);
}
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_remquo)(double x,
                              double y,
                              int *pquo) {
	return libc_remquo(x, y, pquo);
}
/* Round X to nearest integral value according to current rounding direction */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED long int
NOTHROW(LIBDCALL libd_lrint)(double x) {
	return libc_lrint(x);
}
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED long int
NOTHROW(LIBDCALL libd_lround)(double x) {
	return libc_lround(x);
}
/* Return positive difference between X and Y */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBDCALL libd_fdim)(double x,
                            double y) {
	return libc_fdim(x, y);
}
/* Return maximum numeric value from X and Y */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBDCALL libd_fmax)(double x,
                            double y) {
	return libc_fmax(x, y);
}
/* Return minimum numeric value from X and Y */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBDCALL libd_fmin)(double x,
                            double y) {
	return libc_fmin(x, y);
}
/* Multiply-add function computed as a ternary operation */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBDCALL libd_fma)(double x,
                           double y,
                           double z) {
	return libc_fma(x, y, z);
}
/* Round X to nearest integral value according to current rounding direction */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGLONG
NOTHROW(LIBDCALL libd_llrint)(double x) {
	return libc_llrint(x);
}
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGLONG
NOTHROW(LIBDCALL libd_llround)(double x) {
	return libc_llround(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBDCALL libd_nexttowardf)(float x,
                                   __LONGDOUBLE y) {
	return libc_nexttowardf(x, y);
}
/* Return X times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBDCALL libd_scalbnf)(float x,
                               int n) {
	return libc_scalbnf(x, n);
}
/* Return X times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBDCALL libd_scalblnf)(float x,
                                long int n) {
	return libc_scalblnf(x, n);
}
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBDCALL libd_roundf)(float x) {
	return libc_roundf(x);
}
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBDCALL libd_truncf)(float x) {
	return libc_truncf(x);
}
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_remquof)(float x,
                               float y,
                               int *pquo) {
	return libc_remquof(x, y, pquo);
}
/* Round X to nearest integral value according to current rounding direction */
INTERN ATTR_SECTION(".text.crt.dos.math.math") long int
NOTHROW_NCX(LIBDCALL libd_lrintf)(float x) {
	return libc_lrintf(x);
}
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED long int
NOTHROW(LIBDCALL libd_lroundf)(float x) {
	return libc_lroundf(x);
}
/* Return positive difference between X and Y */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBDCALL libd_fdimf)(float x,
                             float y) {
	return libc_fdimf(x, y);
}
/* Return maximum numeric value from X and Y */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBDCALL libd_fmaxf)(float x,
                             float y) {
	return libc_fmaxf(x, y);
}
/* Return minimum numeric value from X and Y */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBDCALL libd_fminf)(float x,
                             float y) {
	return libc_fminf(x, y);
}
/* Multiply-add function computed as a ternary operation */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBDCALL libd_fmaf)(float x,
                            float y,
                            float z) {
	return libc_fmaf(x, y, z);
}
/* Round X to nearest integral value according to current rounding direction */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGLONG
NOTHROW(LIBDCALL libd_llrintf)(float x) {
	return libc_llrintf(x);
}
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGLONG
NOTHROW(LIBDCALL libd_llroundf)(float x) {
	return libc_llroundf(x);
}
/* Return X times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_scalbnl)(__LONGDOUBLE x,
                               int n) {
	return libc_scalbnl(x, n);
}
/* Return X times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_scalblnl)(__LONGDOUBLE x,
                                long int n) {
	return libc_scalblnl(x, n);
}
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_roundl)(__LONGDOUBLE x) {
	return libc_roundl(x);
}
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_truncl)(__LONGDOUBLE x) {
	return libc_truncl(x);
}
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_remquol)(__LONGDOUBLE x,
                               __LONGDOUBLE y,
                               int *pquo) {
	return libc_remquol(x, y, pquo);
}
/* Round X to nearest integral value according to current rounding direction */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED long int
NOTHROW(LIBDCALL libd_lrintl)(__LONGDOUBLE x) {
	return libc_lrintl(x);
}
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED long int
NOTHROW(LIBDCALL libd_lroundl)(__LONGDOUBLE x) {
	return libc_lroundl(x);
}
/* Return positive difference between X and Y */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_fdiml)(__LONGDOUBLE x,
                             __LONGDOUBLE y) {
	return libc_fdiml(x, y);
}
/* Return maximum numeric value from X and Y */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_fmaxl)(__LONGDOUBLE x,
                             __LONGDOUBLE y) {
	return libc_fmaxl(x, y);
}
/* Return minimum numeric value from X and Y */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_fminl)(__LONGDOUBLE x,
                             __LONGDOUBLE y) {
	return libc_fminl(x, y);
}
/* Multiply-add function computed as a ternary operation */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_fmal)(__LONGDOUBLE x,
                            __LONGDOUBLE y,
                            __LONGDOUBLE z) {
	return libc_fmal(x, y, z);
}
/* Round X to nearest integral value according to current rounding direction */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGLONG
NOTHROW(LIBDCALL libd_llrintl)(__LONGDOUBLE x) {
	return libc_llrintl(x);
}
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGLONG
NOTHROW(LIBDCALL libd_llroundl)(__LONGDOUBLE x) {
	return libc_llroundl(x);
}
/* Cosine and sine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") __DECL_SIMD_sincos NONNULL((2, 3)) void
NOTHROW(LIBDCALL libd_sincos)(double x,
                              double *psinx,
                              double *pcosx) {
	libc_sincos(x, psinx, pcosx);
}
/* A function missing in all standards: compute exponent to base ten */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_exp10)(double x) {
	return libc_exp10(x);
}
/* Another name occasionally used */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_pow10)(double x) {
	return libc_pow10(x);
}
/* Cosine and sine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") __DECL_SIMD_sincosf NONNULL((2, 3)) void
NOTHROW(LIBDCALL libd_sincosf)(float x,
                               float *psinx,
                               float *pcosx) {
	libc_sincosf(x, psinx, pcosx);
}
/* A function missing in all standards: compute exponent to base ten */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_exp10f)(float x) {
	return libc_exp10f(x);
}
/* Another name occasionally used */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_pow10f)(float x) {
	return libc_pow10f(x);
}
/* Cosine and sine of X */
INTERN ATTR_SECTION(".text.crt.dos.math.math") __DECL_SIMD_sincosl NONNULL((2, 3)) void
NOTHROW(LIBDCALL libd_sincosl)(__LONGDOUBLE x,
                               __LONGDOUBLE *psinx,
                               __LONGDOUBLE *pcosx) {
	libc_sincosl(x, psinx, pcosx);
}
/* A function missing in all standards: compute exponent to base ten */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_exp10l)(__LONGDOUBLE x) {
	return libc_exp10l(x);
}
/* Another name occasionally used */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_pow10l)(__LONGDOUBLE x) {
	return libc_pow10l(x);
}
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_isinf)(double x) {
	return libc_isinf(x);
}
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_isinff)(float x) {
	return libc_isinff(x);
}
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_isinfl)(__LONGDOUBLE x) {
	return libc_isinfl(x);
}
/* Return nonzero if VALUE is finite and not NaN */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_finite)(double x) {
	return libc_finite(x);
}
/* Return the fractional part of X after dividing out `ilogb(X)' */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED double
NOTHROW(LIBDCALL libd_significand)(double x) {
	return libc_significand(x);
}
/* Return nonzero if VALUE is finite and not NaN */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_finitef)(float x) {
	return libc_finitef(x);
}
/* Return the fractional part of X after dividing out `ilogb(X)' */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED float
NOTHROW(LIBDCALL libd_significandf)(float x) {
	return libc_significandf(x);
}
/* Return nonzero if VALUE is finite and not NaN */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_finitel)(__LONGDOUBLE x) {
	return libc_finitel(x);
}
/* Return the fractional part of X after dividing out `ilogb(X)' */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_significandl)(__LONGDOUBLE x) {
	return libc_significandl(x);
}
/* Return nonzero if VALUE is not a number */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_isnan)(double x) {
	return libc_isnan(x);
}
/* Return nonzero if VALUE is not a number */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_isnanf)(float x) {
	return libc_isnanf(x);
}
/* Return nonzero if VALUE is not a number */
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_isnanl)(__LONGDOUBLE x) {
	return libc_isnanl(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_j0)(double x) {
	return libc_j0(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_j1)(double x) {
	return libc_j1(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_jn)(int n,
                          double x) {
	return libc_jn(n, x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_y0)(double x) {
	return libc_y0(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_y1)(double x) {
	return libc_y1(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_yn)(int n,
                          double x) {
	return libc_yn(n, x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_j0f)(float x) {
	return libc_j0f(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_j1f)(float x) {
	return libc_j1f(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_jnf)(int n,
                           float x) {
	return libc_jnf(n, x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_y0f)(float x) {
	return libc_y0f(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_y1f)(float x) {
	return libc_y1f(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_ynf)(int n,
                           float x) {
	return libc_ynf(n, x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_j0l)(__LONGDOUBLE x) {
	return libc_j0l(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_j1l)(__LONGDOUBLE x) {
	return libc_j1l(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_jnl)(int n,
                           __LONGDOUBLE x) {
	return libc_jnl(n, x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_y0l)(__LONGDOUBLE x) {
	return libc_y0l(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_y1l)(__LONGDOUBLE x) {
	return libc_y1l(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_ynl)(int n,
                           __LONGDOUBLE x) {
	return libc_ynl(n, x);
}
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW_NCX(LIBDCALL libd_lgamma_r)(double x,
                                    int *signgamp) {
	return libc_lgamma_r(x, signgamp);
}
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW_NCX(LIBDCALL libd_lgammaf_r)(float x,
                                     int *signgamp) {
	return libc_lgammaf_r(x, signgamp);
}
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW_NCX(LIBDCALL libd_lgammal_r)(__LONGDOUBLE x,
                                     int *signgamp) {
	return libc_lgammal_r(x, signgamp);
}
/* Return X times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED double
NOTHROW(LIBDCALL libd_scalb)(double x,
                             double fn) {
	return libc_scalb(x, fn);
}
/* Return X times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED float
NOTHROW(LIBDCALL libd_scalbf)(float x,
                              float fn) {
	return libc_scalbf(x, fn);
}
/* Return X times (2 to the Nth power) */
INTERN ATTR_SECTION(".text.crt.dos.math.math") WUNUSED __LONGDOUBLE
NOTHROW(LIBDCALL libd_scalbl)(__LONGDOUBLE x,
                              __LONGDOUBLE fn) {
	return libc_scalbl(x, fn);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd___fpclassify)(double x) {
	return libc___fpclassify(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd___signbit)(double x) {
	return libc___signbit(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd___fpclassifyf)(float x) {
	return libc___fpclassifyf(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd___signbitf)(float x) {
	return libc___signbitf(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd___fpclassifyl)(__LONGDOUBLE x) {
	return libc___fpclassifyl(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd___signbitl)(__LONGDOUBLE x) {
	return libc___signbitl(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd___issignaling)(double x) {
	return libc___issignaling(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd___issignalingf)(float x) {
	return libc___issignalingf(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.math") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd___issignalingl)(__LONGDOUBLE x) {
	return libc___issignalingl(x);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$__acos, libd_acos);
DEFINE_PUBLIC_ALIAS(DOS$acos, libd_acos);
DEFINE_PUBLIC_ALIAS(DOS$__asin, libd_asin);
DEFINE_PUBLIC_ALIAS(DOS$asin, libd_asin);
DEFINE_PUBLIC_ALIAS(DOS$__atan, libd_atan);
DEFINE_PUBLIC_ALIAS(DOS$atan, libd_atan);
DEFINE_PUBLIC_ALIAS(DOS$__atan2, libd_atan2);
DEFINE_PUBLIC_ALIAS(DOS$atan2, libd_atan2);
DEFINE_PUBLIC_ALIAS(DOS$__cos, libd_cos);
DEFINE_PUBLIC_ALIAS(DOS$cos, libd_cos);
DEFINE_PUBLIC_ALIAS(DOS$__sin, libd_sin);
DEFINE_PUBLIC_ALIAS(DOS$sin, libd_sin);
DEFINE_PUBLIC_ALIAS(DOS$__tan, libd_tan);
DEFINE_PUBLIC_ALIAS(DOS$tan, libd_tan);
DEFINE_PUBLIC_ALIAS(DOS$__acosf, libd_acosf);
DEFINE_PUBLIC_ALIAS(DOS$acosf, libd_acosf);
DEFINE_PUBLIC_ALIAS(DOS$__asinf, libd_asinf);
DEFINE_PUBLIC_ALIAS(DOS$asinf, libd_asinf);
DEFINE_PUBLIC_ALIAS(DOS$__atanf, libd_atanf);
DEFINE_PUBLIC_ALIAS(DOS$atanf, libd_atanf);
DEFINE_PUBLIC_ALIAS(DOS$__atan2f, libd_atan2f);
DEFINE_PUBLIC_ALIAS(DOS$atan2f, libd_atan2f);
DEFINE_PUBLIC_ALIAS(DOS$__cosf, libd_cosf);
DEFINE_PUBLIC_ALIAS(DOS$cosf, libd_cosf);
DEFINE_PUBLIC_ALIAS(DOS$__sinf, libd_sinf);
DEFINE_PUBLIC_ALIAS(DOS$sinf, libd_sinf);
DEFINE_PUBLIC_ALIAS(DOS$__tanf, libd_tanf);
DEFINE_PUBLIC_ALIAS(DOS$tanf, libd_tanf);
DEFINE_PUBLIC_ALIAS(DOS$__acosl, libd_acosl);
DEFINE_PUBLIC_ALIAS(DOS$acosl, libd_acosl);
DEFINE_PUBLIC_ALIAS(DOS$__asinl, libd_asinl);
DEFINE_PUBLIC_ALIAS(DOS$asinl, libd_asinl);
DEFINE_PUBLIC_ALIAS(DOS$__atanl, libd_atanl);
DEFINE_PUBLIC_ALIAS(DOS$atanl, libd_atanl);
DEFINE_PUBLIC_ALIAS(DOS$__atan2l, libd_atan2l);
DEFINE_PUBLIC_ALIAS(DOS$atan2l, libd_atan2l);
DEFINE_PUBLIC_ALIAS(DOS$__cosl, libd_cosl);
DEFINE_PUBLIC_ALIAS(DOS$cosl, libd_cosl);
DEFINE_PUBLIC_ALIAS(DOS$__sinl, libd_sinl);
DEFINE_PUBLIC_ALIAS(DOS$sinl, libd_sinl);
DEFINE_PUBLIC_ALIAS(DOS$__tanl, libd_tanl);
DEFINE_PUBLIC_ALIAS(DOS$tanl, libd_tanl);
DEFINE_PUBLIC_ALIAS(DOS$__cosh, libd_cosh);
DEFINE_PUBLIC_ALIAS(DOS$cosh, libd_cosh);
DEFINE_PUBLIC_ALIAS(DOS$__sinh, libd_sinh);
DEFINE_PUBLIC_ALIAS(DOS$sinh, libd_sinh);
DEFINE_PUBLIC_ALIAS(DOS$__tanh, libd_tanh);
DEFINE_PUBLIC_ALIAS(DOS$tanh, libd_tanh);
DEFINE_PUBLIC_ALIAS(DOS$__coshf, libd_coshf);
DEFINE_PUBLIC_ALIAS(DOS$coshf, libd_coshf);
DEFINE_PUBLIC_ALIAS(DOS$__sinhf, libd_sinhf);
DEFINE_PUBLIC_ALIAS(DOS$sinhf, libd_sinhf);
DEFINE_PUBLIC_ALIAS(DOS$__tanhf, libd_tanhf);
DEFINE_PUBLIC_ALIAS(DOS$tanhf, libd_tanhf);
DEFINE_PUBLIC_ALIAS(DOS$__coshl, libd_coshl);
DEFINE_PUBLIC_ALIAS(DOS$coshl, libd_coshl);
DEFINE_PUBLIC_ALIAS(DOS$__sinhl, libd_sinhl);
DEFINE_PUBLIC_ALIAS(DOS$sinhl, libd_sinhl);
DEFINE_PUBLIC_ALIAS(DOS$__tanhl, libd_tanhl);
DEFINE_PUBLIC_ALIAS(DOS$tanhl, libd_tanhl);
DEFINE_PUBLIC_ALIAS(DOS$__acosh, libd_acosh);
DEFINE_PUBLIC_ALIAS(DOS$acosh, libd_acosh);
DEFINE_PUBLIC_ALIAS(DOS$__asinh, libd_asinh);
DEFINE_PUBLIC_ALIAS(DOS$asinh, libd_asinh);
DEFINE_PUBLIC_ALIAS(DOS$__atanh, libd_atanh);
DEFINE_PUBLIC_ALIAS(DOS$atanh, libd_atanh);
DEFINE_PUBLIC_ALIAS(DOS$__acoshf, libd_acoshf);
DEFINE_PUBLIC_ALIAS(DOS$acoshf, libd_acoshf);
DEFINE_PUBLIC_ALIAS(DOS$__asinhf, libd_asinhf);
DEFINE_PUBLIC_ALIAS(DOS$asinhf, libd_asinhf);
DEFINE_PUBLIC_ALIAS(DOS$__atanhf, libd_atanhf);
DEFINE_PUBLIC_ALIAS(DOS$atanhf, libd_atanhf);
DEFINE_PUBLIC_ALIAS(DOS$__acoshl, libd_acoshl);
DEFINE_PUBLIC_ALIAS(DOS$acoshl, libd_acoshl);
DEFINE_PUBLIC_ALIAS(DOS$__asinhl, libd_asinhl);
DEFINE_PUBLIC_ALIAS(DOS$asinhl, libd_asinhl);
DEFINE_PUBLIC_ALIAS(DOS$__atanhl, libd_atanhl);
DEFINE_PUBLIC_ALIAS(DOS$atanhl, libd_atanhl);
DEFINE_PUBLIC_ALIAS(DOS$__exp, libd_exp);
DEFINE_PUBLIC_ALIAS(DOS$exp, libd_exp);
DEFINE_PUBLIC_ALIAS(DOS$__frexp, libd_frexp);
DEFINE_PUBLIC_ALIAS(DOS$frexp, libd_frexp);
DEFINE_PUBLIC_ALIAS(DOS$__ldexp, libd_ldexp);
DEFINE_PUBLIC_ALIAS(DOS$ldexp, libd_ldexp);
DEFINE_PUBLIC_ALIAS(DOS$__log, libd_log);
DEFINE_PUBLIC_ALIAS(DOS$log, libd_log);
DEFINE_PUBLIC_ALIAS(DOS$__log10, libd_log10);
DEFINE_PUBLIC_ALIAS(DOS$log10, libd_log10);
DEFINE_PUBLIC_ALIAS(DOS$__modf, libd_modf);
DEFINE_PUBLIC_ALIAS(DOS$modf, libd_modf);
DEFINE_PUBLIC_ALIAS(DOS$__expf, libd_expf);
DEFINE_PUBLIC_ALIAS(DOS$expf, libd_expf);
DEFINE_PUBLIC_ALIAS(DOS$__frexpf, libd_frexpf);
DEFINE_PUBLIC_ALIAS(DOS$frexpf, libd_frexpf);
DEFINE_PUBLIC_ALIAS(DOS$__ldexpf, libd_ldexpf);
DEFINE_PUBLIC_ALIAS(DOS$ldexpf, libd_ldexpf);
DEFINE_PUBLIC_ALIAS(DOS$__logf, libd_logf);
DEFINE_PUBLIC_ALIAS(DOS$logf, libd_logf);
DEFINE_PUBLIC_ALIAS(DOS$__log10f, libd_log10f);
DEFINE_PUBLIC_ALIAS(DOS$log10f, libd_log10f);
DEFINE_PUBLIC_ALIAS(DOS$__modff, libd_modff);
DEFINE_PUBLIC_ALIAS(DOS$modff, libd_modff);
DEFINE_PUBLIC_ALIAS(DOS$__expl, libd_expl);
DEFINE_PUBLIC_ALIAS(DOS$expl, libd_expl);
DEFINE_PUBLIC_ALIAS(DOS$__frexpl, libd_frexpl);
DEFINE_PUBLIC_ALIAS(DOS$frexpl, libd_frexpl);
DEFINE_PUBLIC_ALIAS(DOS$__ldexpl, libd_ldexpl);
DEFINE_PUBLIC_ALIAS(DOS$ldexpl, libd_ldexpl);
DEFINE_PUBLIC_ALIAS(DOS$__logl, libd_logl);
DEFINE_PUBLIC_ALIAS(DOS$logl, libd_logl);
DEFINE_PUBLIC_ALIAS(DOS$__log10l, libd_log10l);
DEFINE_PUBLIC_ALIAS(DOS$log10l, libd_log10l);
DEFINE_PUBLIC_ALIAS(DOS$__modfl, libd_modfl);
DEFINE_PUBLIC_ALIAS(DOS$modfl, libd_modfl);
DEFINE_PUBLIC_ALIAS(DOS$__expm1, libd_expm1);
DEFINE_PUBLIC_ALIAS(DOS$expm1, libd_expm1);
DEFINE_PUBLIC_ALIAS(DOS$__log1p, libd_log1p);
DEFINE_PUBLIC_ALIAS(DOS$log1p, libd_log1p);
DEFINE_PUBLIC_ALIAS(DOS$__logb, libd_logb);
DEFINE_PUBLIC_ALIAS(DOS$_logb, libd_logb);
DEFINE_PUBLIC_ALIAS(DOS$logb, libd_logb);
DEFINE_PUBLIC_ALIAS(DOS$__expm1f, libd_expm1f);
DEFINE_PUBLIC_ALIAS(DOS$expm1f, libd_expm1f);
DEFINE_PUBLIC_ALIAS(DOS$__log1pf, libd_log1pf);
DEFINE_PUBLIC_ALIAS(DOS$log1pf, libd_log1pf);
DEFINE_PUBLIC_ALIAS(DOS$__logbf, libd_logbf);
DEFINE_PUBLIC_ALIAS(DOS$logbf, libd_logbf);
DEFINE_PUBLIC_ALIAS(DOS$__expm1l, libd_expm1l);
DEFINE_PUBLIC_ALIAS(DOS$expm1l, libd_expm1l);
DEFINE_PUBLIC_ALIAS(DOS$__log1pl, libd_log1pl);
DEFINE_PUBLIC_ALIAS(DOS$log1pl, libd_log1pl);
DEFINE_PUBLIC_ALIAS(DOS$__logbl, libd_logbl);
DEFINE_PUBLIC_ALIAS(DOS$logbl, libd_logbl);
DEFINE_PUBLIC_ALIAS(DOS$__exp2, libd_exp2);
DEFINE_PUBLIC_ALIAS(DOS$exp2, libd_exp2);
DEFINE_PUBLIC_ALIAS(DOS$__log2, libd_log2);
DEFINE_PUBLIC_ALIAS(DOS$log2, libd_log2);
DEFINE_PUBLIC_ALIAS(DOS$__exp2f, libd_exp2f);
DEFINE_PUBLIC_ALIAS(DOS$exp2f, libd_exp2f);
DEFINE_PUBLIC_ALIAS(DOS$__log2f, libd_log2f);
DEFINE_PUBLIC_ALIAS(DOS$log2f, libd_log2f);
DEFINE_PUBLIC_ALIAS(DOS$__exp2l, libd_exp2l);
DEFINE_PUBLIC_ALIAS(DOS$exp2l, libd_exp2l);
DEFINE_PUBLIC_ALIAS(DOS$__log2l, libd_log2l);
DEFINE_PUBLIC_ALIAS(DOS$log2l, libd_log2l);
DEFINE_PUBLIC_ALIAS(DOS$__pow, libd_pow);
DEFINE_PUBLIC_ALIAS(DOS$pow, libd_pow);
DEFINE_PUBLIC_ALIAS(DOS$__sqrt, libd_sqrt);
DEFINE_PUBLIC_ALIAS(DOS$sqrt, libd_sqrt);
DEFINE_PUBLIC_ALIAS(DOS$__powf, libd_powf);
DEFINE_PUBLIC_ALIAS(DOS$powf, libd_powf);
DEFINE_PUBLIC_ALIAS(DOS$__sqrtf, libd_sqrtf);
DEFINE_PUBLIC_ALIAS(DOS$sqrtf, libd_sqrtf);
DEFINE_PUBLIC_ALIAS(DOS$__powl, libd_powl);
DEFINE_PUBLIC_ALIAS(DOS$powl, libd_powl);
DEFINE_PUBLIC_ALIAS(DOS$__sqrtl, libd_sqrtl);
DEFINE_PUBLIC_ALIAS(DOS$sqrtl, libd_sqrtl);
DEFINE_PUBLIC_ALIAS(DOS$__hypot, libd_hypot);
DEFINE_PUBLIC_ALIAS(DOS$hypot, libd_hypot);
DEFINE_PUBLIC_ALIAS(DOS$__hypotf, libd_hypotf);
DEFINE_PUBLIC_ALIAS(DOS$hypotf, libd_hypotf);
DEFINE_PUBLIC_ALIAS(DOS$__hypotl, libd_hypotl);
DEFINE_PUBLIC_ALIAS(DOS$hypotl, libd_hypotl);
DEFINE_PUBLIC_ALIAS(DOS$__cbrt, libd_cbrt);
DEFINE_PUBLIC_ALIAS(DOS$cbrt, libd_cbrt);
DEFINE_PUBLIC_ALIAS(DOS$__cbrtf, libd_cbrtf);
DEFINE_PUBLIC_ALIAS(DOS$cbrtf, libd_cbrtf);
DEFINE_PUBLIC_ALIAS(DOS$__cbrtl, libd_cbrtl);
DEFINE_PUBLIC_ALIAS(DOS$cbrtl, libd_cbrtl);
DEFINE_PUBLIC_ALIAS(DOS$__ceil, libd_ceil);
DEFINE_PUBLIC_ALIAS(DOS$ceil, libd_ceil);
DEFINE_PUBLIC_ALIAS(DOS$__fabs, libd_fabs);
DEFINE_PUBLIC_ALIAS(DOS$fabs, libd_fabs);
DEFINE_PUBLIC_ALIAS(DOS$__floor, libd_floor);
DEFINE_PUBLIC_ALIAS(DOS$floor, libd_floor);
DEFINE_PUBLIC_ALIAS(DOS$__fmod, libd_fmod);
DEFINE_PUBLIC_ALIAS(DOS$fmod, libd_fmod);
DEFINE_PUBLIC_ALIAS(DOS$__ceilf, libd_ceilf);
DEFINE_PUBLIC_ALIAS(DOS$ceilf, libd_ceilf);
DEFINE_PUBLIC_ALIAS(DOS$__fabsf, libd_fabsf);
DEFINE_PUBLIC_ALIAS(DOS$fabsf, libd_fabsf);
DEFINE_PUBLIC_ALIAS(DOS$__floorf, libd_floorf);
DEFINE_PUBLIC_ALIAS(DOS$floorf, libd_floorf);
DEFINE_PUBLIC_ALIAS(DOS$__fmodf, libd_fmodf);
DEFINE_PUBLIC_ALIAS(DOS$fmodf, libd_fmodf);
DEFINE_PUBLIC_ALIAS(DOS$__ceill, libd_ceill);
DEFINE_PUBLIC_ALIAS(DOS$ceill, libd_ceill);
DEFINE_PUBLIC_ALIAS(DOS$__fabsl, libd_fabsl);
DEFINE_PUBLIC_ALIAS(DOS$fabsl, libd_fabsl);
DEFINE_PUBLIC_ALIAS(DOS$__floorl, libd_floorl);
DEFINE_PUBLIC_ALIAS(DOS$floorl, libd_floorl);
DEFINE_PUBLIC_ALIAS(DOS$__fmodl, libd_fmodl);
DEFINE_PUBLIC_ALIAS(DOS$fmodl, libd_fmodl);
DEFINE_PUBLIC_ALIAS(DOS$__copysign, libd_copysign);
DEFINE_PUBLIC_ALIAS(DOS$_copysign, libd_copysign);
DEFINE_PUBLIC_ALIAS(DOS$copysign, libd_copysign);
DEFINE_PUBLIC_ALIAS(DOS$__nan, libd_nan);
DEFINE_PUBLIC_ALIAS(DOS$nan, libd_nan);
DEFINE_PUBLIC_ALIAS(DOS$__copysignf, libd_copysignf);
DEFINE_PUBLIC_ALIAS(DOS$copysignf, libd_copysignf);
DEFINE_PUBLIC_ALIAS(DOS$__nanf, libd_nanf);
DEFINE_PUBLIC_ALIAS(DOS$nanf, libd_nanf);
DEFINE_PUBLIC_ALIAS(DOS$__copysignl, libd_copysignl);
DEFINE_PUBLIC_ALIAS(DOS$copysignl, libd_copysignl);
DEFINE_PUBLIC_ALIAS(DOS$__nanl, libd_nanl);
DEFINE_PUBLIC_ALIAS(DOS$nanl, libd_nanl);
DEFINE_PUBLIC_ALIAS(DOS$__erf, libd_erf);
DEFINE_PUBLIC_ALIAS(DOS$erf, libd_erf);
DEFINE_PUBLIC_ALIAS(DOS$__erfc, libd_erfc);
DEFINE_PUBLIC_ALIAS(DOS$erfc, libd_erfc);
DEFINE_PUBLIC_ALIAS(DOS$gamma, libd_lgamma);
DEFINE_PUBLIC_ALIAS(DOS$__lgamma, libd_lgamma);
DEFINE_PUBLIC_ALIAS(DOS$__gamma, libd_lgamma);
DEFINE_PUBLIC_ALIAS(DOS$lgamma, libd_lgamma);
DEFINE_PUBLIC_ALIAS(DOS$__erff, libd_erff);
DEFINE_PUBLIC_ALIAS(DOS$erff, libd_erff);
DEFINE_PUBLIC_ALIAS(DOS$__erfcf, libd_erfcf);
DEFINE_PUBLIC_ALIAS(DOS$erfcf, libd_erfcf);
DEFINE_PUBLIC_ALIAS(DOS$gammaf, libd_lgammaf);
DEFINE_PUBLIC_ALIAS(DOS$__lgammaf, libd_lgammaf);
DEFINE_PUBLIC_ALIAS(DOS$__gammaf, libd_lgammaf);
DEFINE_PUBLIC_ALIAS(DOS$lgammaf, libd_lgammaf);
DEFINE_PUBLIC_ALIAS(DOS$__erfl, libd_erfl);
DEFINE_PUBLIC_ALIAS(DOS$erfl, libd_erfl);
DEFINE_PUBLIC_ALIAS(DOS$__erfcl, libd_erfcl);
DEFINE_PUBLIC_ALIAS(DOS$erfcl, libd_erfcl);
DEFINE_PUBLIC_ALIAS(DOS$gammal, libd_lgammal);
DEFINE_PUBLIC_ALIAS(DOS$__lgammal, libd_lgammal);
DEFINE_PUBLIC_ALIAS(DOS$__gammal, libd_lgammal);
DEFINE_PUBLIC_ALIAS(DOS$lgammal, libd_lgammal);
DEFINE_PUBLIC_ALIAS(DOS$__tgamma, libd_tgamma);
DEFINE_PUBLIC_ALIAS(DOS$tgamma, libd_tgamma);
DEFINE_PUBLIC_ALIAS(DOS$__tgammaf, libd_tgammaf);
DEFINE_PUBLIC_ALIAS(DOS$tgammaf, libd_tgammaf);
DEFINE_PUBLIC_ALIAS(DOS$__tgammal, libd_tgammal);
DEFINE_PUBLIC_ALIAS(DOS$tgammal, libd_tgammal);
DEFINE_PUBLIC_ALIAS(DOS$nearbyint, libd_rint);
DEFINE_PUBLIC_ALIAS(DOS$__rint, libd_rint);
DEFINE_PUBLIC_ALIAS(DOS$__nearbyint, libd_rint);
DEFINE_PUBLIC_ALIAS(DOS$rint, libd_rint);
DEFINE_PUBLIC_ALIAS(DOS$nexttoward, libd_nextafter);
DEFINE_PUBLIC_ALIAS(DOS$__nextafter, libd_nextafter);
DEFINE_PUBLIC_ALIAS(DOS$_nextafter, libd_nextafter);
DEFINE_PUBLIC_ALIAS(DOS$__nexttoward, libd_nextafter);
DEFINE_PUBLIC_ALIAS(DOS$nextafter, libd_nextafter);
DEFINE_PUBLIC_ALIAS(DOS$drem, libd_remainder);
DEFINE_PUBLIC_ALIAS(DOS$__remainder, libd_remainder);
DEFINE_PUBLIC_ALIAS(DOS$__drem, libd_remainder);
DEFINE_PUBLIC_ALIAS(DOS$remainder, libd_remainder);
DEFINE_PUBLIC_ALIAS(DOS$__ilogb, libd_ilogb);
DEFINE_PUBLIC_ALIAS(DOS$ilogb, libd_ilogb);
DEFINE_PUBLIC_ALIAS(DOS$nearbyintf, libd_rintf);
DEFINE_PUBLIC_ALIAS(DOS$__rintf, libd_rintf);
DEFINE_PUBLIC_ALIAS(DOS$__nearbyintf, libd_rintf);
DEFINE_PUBLIC_ALIAS(DOS$rintf, libd_rintf);
DEFINE_PUBLIC_ALIAS(DOS$nexttowardf, libd_nextafterf);
DEFINE_PUBLIC_ALIAS(DOS$__nextafterf, libd_nextafterf);
DEFINE_PUBLIC_ALIAS(DOS$__nexttowardf, libd_nextafterf);
DEFINE_PUBLIC_ALIAS(DOS$nextafterf, libd_nextafterf);
DEFINE_PUBLIC_ALIAS(DOS$dremf, libd_remainderf);
DEFINE_PUBLIC_ALIAS(DOS$__remainderf, libd_remainderf);
DEFINE_PUBLIC_ALIAS(DOS$__dremf, libd_remainderf);
DEFINE_PUBLIC_ALIAS(DOS$remainderf, libd_remainderf);
DEFINE_PUBLIC_ALIAS(DOS$__ilogbf, libd_ilogbf);
DEFINE_PUBLIC_ALIAS(DOS$ilogbf, libd_ilogbf);
DEFINE_PUBLIC_ALIAS(DOS$nearbyintl, libd_rintl);
DEFINE_PUBLIC_ALIAS(DOS$__rintl, libd_rintl);
DEFINE_PUBLIC_ALIAS(DOS$__nearbyintl, libd_rintl);
DEFINE_PUBLIC_ALIAS(DOS$rintl, libd_rintl);
DEFINE_PUBLIC_ALIAS(DOS$nexttowardl, libd_nextafterl);
DEFINE_PUBLIC_ALIAS(DOS$__nextafterl, libd_nextafterl);
DEFINE_PUBLIC_ALIAS(DOS$__nexttowardl, libd_nextafterl);
DEFINE_PUBLIC_ALIAS(DOS$nextafterl, libd_nextafterl);
DEFINE_PUBLIC_ALIAS(DOS$dreml, libd_remainderl);
DEFINE_PUBLIC_ALIAS(DOS$__remainderl, libd_remainderl);
DEFINE_PUBLIC_ALIAS(DOS$__dreml, libd_remainderl);
DEFINE_PUBLIC_ALIAS(DOS$remainderl, libd_remainderl);
DEFINE_PUBLIC_ALIAS(DOS$__ilogbl, libd_ilogbl);
DEFINE_PUBLIC_ALIAS(DOS$ilogbl, libd_ilogbl);
DEFINE_PUBLIC_ALIAS(DOS$__nexttoward, libd_nexttoward);
DEFINE_PUBLIC_ALIAS(DOS$nexttoward, libd_nexttoward);
DEFINE_PUBLIC_ALIAS(DOS$__scalbn, libd_scalbn);
DEFINE_PUBLIC_ALIAS(DOS$scalbn, libd_scalbn);
DEFINE_PUBLIC_ALIAS(DOS$__scalbln, libd_scalbln);
DEFINE_PUBLIC_ALIAS(DOS$scalbln, libd_scalbln);
DEFINE_PUBLIC_ALIAS(DOS$__round, libd_round);
DEFINE_PUBLIC_ALIAS(DOS$round, libd_round);
DEFINE_PUBLIC_ALIAS(DOS$__trunc, libd_trunc);
DEFINE_PUBLIC_ALIAS(DOS$trunc, libd_trunc);
DEFINE_PUBLIC_ALIAS(DOS$__remquo, libd_remquo);
DEFINE_PUBLIC_ALIAS(DOS$remquo, libd_remquo);
DEFINE_PUBLIC_ALIAS(DOS$__lrint, libd_lrint);
DEFINE_PUBLIC_ALIAS(DOS$lrint, libd_lrint);
DEFINE_PUBLIC_ALIAS(DOS$__lround, libd_lround);
DEFINE_PUBLIC_ALIAS(DOS$lround, libd_lround);
DEFINE_PUBLIC_ALIAS(DOS$__fdim, libd_fdim);
DEFINE_PUBLIC_ALIAS(DOS$fdim, libd_fdim);
DEFINE_PUBLIC_ALIAS(DOS$__fmax, libd_fmax);
DEFINE_PUBLIC_ALIAS(DOS$fmax, libd_fmax);
DEFINE_PUBLIC_ALIAS(DOS$__fmin, libd_fmin);
DEFINE_PUBLIC_ALIAS(DOS$fmin, libd_fmin);
DEFINE_PUBLIC_ALIAS(DOS$__fma, libd_fma);
DEFINE_PUBLIC_ALIAS(DOS$fma, libd_fma);
DEFINE_PUBLIC_ALIAS(DOS$__llrint, libd_llrint);
DEFINE_PUBLIC_ALIAS(DOS$llrint, libd_llrint);
DEFINE_PUBLIC_ALIAS(DOS$__llround, libd_llround);
DEFINE_PUBLIC_ALIAS(DOS$llround, libd_llround);
DEFINE_PUBLIC_ALIAS(DOS$__nexttowardf, libd_nexttowardf);
DEFINE_PUBLIC_ALIAS(DOS$nexttowardf, libd_nexttowardf);
DEFINE_PUBLIC_ALIAS(DOS$__scalbnf, libd_scalbnf);
DEFINE_PUBLIC_ALIAS(DOS$scalbnf, libd_scalbnf);
DEFINE_PUBLIC_ALIAS(DOS$__scalblnf, libd_scalblnf);
DEFINE_PUBLIC_ALIAS(DOS$scalblnf, libd_scalblnf);
DEFINE_PUBLIC_ALIAS(DOS$__roundf, libd_roundf);
DEFINE_PUBLIC_ALIAS(DOS$roundf, libd_roundf);
DEFINE_PUBLIC_ALIAS(DOS$__truncf, libd_truncf);
DEFINE_PUBLIC_ALIAS(DOS$truncf, libd_truncf);
DEFINE_PUBLIC_ALIAS(DOS$__remquof, libd_remquof);
DEFINE_PUBLIC_ALIAS(DOS$remquof, libd_remquof);
DEFINE_PUBLIC_ALIAS(DOS$__lrintf, libd_lrintf);
DEFINE_PUBLIC_ALIAS(DOS$lrintf, libd_lrintf);
DEFINE_PUBLIC_ALIAS(DOS$__lroundf, libd_lroundf);
DEFINE_PUBLIC_ALIAS(DOS$lroundf, libd_lroundf);
DEFINE_PUBLIC_ALIAS(DOS$__fdimf, libd_fdimf);
DEFINE_PUBLIC_ALIAS(DOS$fdimf, libd_fdimf);
DEFINE_PUBLIC_ALIAS(DOS$__fmaxf, libd_fmaxf);
DEFINE_PUBLIC_ALIAS(DOS$fmaxf, libd_fmaxf);
DEFINE_PUBLIC_ALIAS(DOS$__fminf, libd_fminf);
DEFINE_PUBLIC_ALIAS(DOS$fminf, libd_fminf);
DEFINE_PUBLIC_ALIAS(DOS$__fmaf, libd_fmaf);
DEFINE_PUBLIC_ALIAS(DOS$fmaf, libd_fmaf);
DEFINE_PUBLIC_ALIAS(DOS$__llrintf, libd_llrintf);
DEFINE_PUBLIC_ALIAS(DOS$llrintf, libd_llrintf);
DEFINE_PUBLIC_ALIAS(DOS$__llroundf, libd_llroundf);
DEFINE_PUBLIC_ALIAS(DOS$llroundf, libd_llroundf);
DEFINE_PUBLIC_ALIAS(DOS$__scalbnl, libd_scalbnl);
DEFINE_PUBLIC_ALIAS(DOS$scalbnl, libd_scalbnl);
DEFINE_PUBLIC_ALIAS(DOS$__scalblnl, libd_scalblnl);
DEFINE_PUBLIC_ALIAS(DOS$scalblnl, libd_scalblnl);
DEFINE_PUBLIC_ALIAS(DOS$__roundl, libd_roundl);
DEFINE_PUBLIC_ALIAS(DOS$roundl, libd_roundl);
DEFINE_PUBLIC_ALIAS(DOS$__truncl, libd_truncl);
DEFINE_PUBLIC_ALIAS(DOS$truncl, libd_truncl);
DEFINE_PUBLIC_ALIAS(DOS$__remquol, libd_remquol);
DEFINE_PUBLIC_ALIAS(DOS$remquol, libd_remquol);
DEFINE_PUBLIC_ALIAS(DOS$__lrintl, libd_lrintl);
DEFINE_PUBLIC_ALIAS(DOS$lrintl, libd_lrintl);
DEFINE_PUBLIC_ALIAS(DOS$__lroundl, libd_lroundl);
DEFINE_PUBLIC_ALIAS(DOS$lroundl, libd_lroundl);
DEFINE_PUBLIC_ALIAS(DOS$__fdiml, libd_fdiml);
DEFINE_PUBLIC_ALIAS(DOS$fdiml, libd_fdiml);
DEFINE_PUBLIC_ALIAS(DOS$__fmaxl, libd_fmaxl);
DEFINE_PUBLIC_ALIAS(DOS$fmaxl, libd_fmaxl);
DEFINE_PUBLIC_ALIAS(DOS$__fminl, libd_fminl);
DEFINE_PUBLIC_ALIAS(DOS$fminl, libd_fminl);
DEFINE_PUBLIC_ALIAS(DOS$__fmal, libd_fmal);
DEFINE_PUBLIC_ALIAS(DOS$fmal, libd_fmal);
DEFINE_PUBLIC_ALIAS(DOS$__llrintl, libd_llrintl);
DEFINE_PUBLIC_ALIAS(DOS$llrintl, libd_llrintl);
DEFINE_PUBLIC_ALIAS(DOS$__llroundl, libd_llroundl);
DEFINE_PUBLIC_ALIAS(DOS$llroundl, libd_llroundl);
DEFINE_PUBLIC_ALIAS(DOS$__sincos, libd_sincos);
DEFINE_PUBLIC_ALIAS(DOS$sincos, libd_sincos);
DEFINE_PUBLIC_ALIAS(DOS$__exp10, libd_exp10);
DEFINE_PUBLIC_ALIAS(DOS$exp10, libd_exp10);
DEFINE_PUBLIC_ALIAS(DOS$__pow10, libd_pow10);
DEFINE_PUBLIC_ALIAS(DOS$pow10, libd_pow10);
DEFINE_PUBLIC_ALIAS(DOS$__sincosf, libd_sincosf);
DEFINE_PUBLIC_ALIAS(DOS$sincosf, libd_sincosf);
DEFINE_PUBLIC_ALIAS(DOS$__exp10f, libd_exp10f);
DEFINE_PUBLIC_ALIAS(DOS$exp10f, libd_exp10f);
DEFINE_PUBLIC_ALIAS(DOS$__pow10f, libd_pow10f);
DEFINE_PUBLIC_ALIAS(DOS$pow10f, libd_pow10f);
DEFINE_PUBLIC_ALIAS(DOS$__sincosl, libd_sincosl);
DEFINE_PUBLIC_ALIAS(DOS$sincosl, libd_sincosl);
DEFINE_PUBLIC_ALIAS(DOS$__exp10l, libd_exp10l);
DEFINE_PUBLIC_ALIAS(DOS$exp10l, libd_exp10l);
DEFINE_PUBLIC_ALIAS(DOS$__pow10l, libd_pow10l);
DEFINE_PUBLIC_ALIAS(DOS$pow10l, libd_pow10l);
DEFINE_PUBLIC_ALIAS(DOS$__isinf, libd_isinf);
DEFINE_PUBLIC_ALIAS(DOS$isinf, libd_isinf);
DEFINE_PUBLIC_ALIAS(DOS$__isinff, libd_isinff);
DEFINE_PUBLIC_ALIAS(DOS$isinff, libd_isinff);
DEFINE_PUBLIC_ALIAS(DOS$__isinfl, libd_isinfl);
DEFINE_PUBLIC_ALIAS(DOS$isinfl, libd_isinfl);
DEFINE_PUBLIC_ALIAS(DOS$__finite, libd_finite);
DEFINE_PUBLIC_ALIAS(DOS$_finite, libd_finite);
DEFINE_PUBLIC_ALIAS(DOS$finite, libd_finite);
DEFINE_PUBLIC_ALIAS(DOS$__significand, libd_significand);
DEFINE_PUBLIC_ALIAS(DOS$significand, libd_significand);
DEFINE_PUBLIC_ALIAS(DOS$__finitef, libd_finitef);
DEFINE_PUBLIC_ALIAS(DOS$finitef, libd_finitef);
DEFINE_PUBLIC_ALIAS(DOS$__significandf, libd_significandf);
DEFINE_PUBLIC_ALIAS(DOS$significandf, libd_significandf);
DEFINE_PUBLIC_ALIAS(DOS$__finitel, libd_finitel);
DEFINE_PUBLIC_ALIAS(DOS$finitel, libd_finitel);
DEFINE_PUBLIC_ALIAS(DOS$__significandl, libd_significandl);
DEFINE_PUBLIC_ALIAS(DOS$significandl, libd_significandl);
DEFINE_PUBLIC_ALIAS(DOS$__isnan, libd_isnan);
DEFINE_PUBLIC_ALIAS(DOS$_isnan, libd_isnan);
DEFINE_PUBLIC_ALIAS(DOS$isnan, libd_isnan);
DEFINE_PUBLIC_ALIAS(DOS$__isnanf, libd_isnanf);
DEFINE_PUBLIC_ALIAS(DOS$isnanf, libd_isnanf);
DEFINE_PUBLIC_ALIAS(DOS$__isnanl, libd_isnanl);
DEFINE_PUBLIC_ALIAS(DOS$isnanl, libd_isnanl);
DEFINE_PUBLIC_ALIAS(DOS$__j0, libd_j0);
DEFINE_PUBLIC_ALIAS(DOS$j0, libd_j0);
DEFINE_PUBLIC_ALIAS(DOS$__j1, libd_j1);
DEFINE_PUBLIC_ALIAS(DOS$j1, libd_j1);
DEFINE_PUBLIC_ALIAS(DOS$__jn, libd_jn);
DEFINE_PUBLIC_ALIAS(DOS$jn, libd_jn);
DEFINE_PUBLIC_ALIAS(DOS$__y0, libd_y0);
DEFINE_PUBLIC_ALIAS(DOS$y0, libd_y0);
DEFINE_PUBLIC_ALIAS(DOS$__y1, libd_y1);
DEFINE_PUBLIC_ALIAS(DOS$y1, libd_y1);
DEFINE_PUBLIC_ALIAS(DOS$__yn, libd_yn);
DEFINE_PUBLIC_ALIAS(DOS$yn, libd_yn);
DEFINE_PUBLIC_ALIAS(DOS$__j0f, libd_j0f);
DEFINE_PUBLIC_ALIAS(DOS$j0f, libd_j0f);
DEFINE_PUBLIC_ALIAS(DOS$__j1f, libd_j1f);
DEFINE_PUBLIC_ALIAS(DOS$j1f, libd_j1f);
DEFINE_PUBLIC_ALIAS(DOS$__jnf, libd_jnf);
DEFINE_PUBLIC_ALIAS(DOS$jnf, libd_jnf);
DEFINE_PUBLIC_ALIAS(DOS$__y0f, libd_y0f);
DEFINE_PUBLIC_ALIAS(DOS$y0f, libd_y0f);
DEFINE_PUBLIC_ALIAS(DOS$__y1f, libd_y1f);
DEFINE_PUBLIC_ALIAS(DOS$y1f, libd_y1f);
DEFINE_PUBLIC_ALIAS(DOS$__ynf, libd_ynf);
DEFINE_PUBLIC_ALIAS(DOS$ynf, libd_ynf);
DEFINE_PUBLIC_ALIAS(DOS$__j0l, libd_j0l);
DEFINE_PUBLIC_ALIAS(DOS$j0l, libd_j0l);
DEFINE_PUBLIC_ALIAS(DOS$__j1l, libd_j1l);
DEFINE_PUBLIC_ALIAS(DOS$j1l, libd_j1l);
DEFINE_PUBLIC_ALIAS(DOS$__jnl, libd_jnl);
DEFINE_PUBLIC_ALIAS(DOS$jnl, libd_jnl);
DEFINE_PUBLIC_ALIAS(DOS$__y0l, libd_y0l);
DEFINE_PUBLIC_ALIAS(DOS$y0l, libd_y0l);
DEFINE_PUBLIC_ALIAS(DOS$__y1l, libd_y1l);
DEFINE_PUBLIC_ALIAS(DOS$y1l, libd_y1l);
DEFINE_PUBLIC_ALIAS(DOS$__ynl, libd_ynl);
DEFINE_PUBLIC_ALIAS(DOS$ynl, libd_ynl);
DEFINE_PUBLIC_ALIAS(DOS$__lgamma_r, libd_lgamma_r);
DEFINE_PUBLIC_ALIAS(DOS$lgamma_r, libd_lgamma_r);
DEFINE_PUBLIC_ALIAS(DOS$__lgammaf_r, libd_lgammaf_r);
DEFINE_PUBLIC_ALIAS(DOS$lgammaf_r, libd_lgammaf_r);
DEFINE_PUBLIC_ALIAS(DOS$__lgammal_r, libd_lgammal_r);
DEFINE_PUBLIC_ALIAS(DOS$lgammal_r, libd_lgammal_r);
DEFINE_PUBLIC_ALIAS(DOS$__scalb, libd_scalb);
DEFINE_PUBLIC_ALIAS(DOS$_scalb, libd_scalb);
DEFINE_PUBLIC_ALIAS(DOS$scalb, libd_scalb);
DEFINE_PUBLIC_ALIAS(DOS$__scalbf, libd_scalbf);
DEFINE_PUBLIC_ALIAS(DOS$_scalbf, libd_scalbf);
DEFINE_PUBLIC_ALIAS(DOS$scalbf, libd_scalbf);
DEFINE_PUBLIC_ALIAS(DOS$__scalbl, libd_scalbl);
DEFINE_PUBLIC_ALIAS(DOS$scalbl, libd_scalbl);
DEFINE_PUBLIC_ALIAS(DOS$_dclass, libd___fpclassify);
DEFINE_PUBLIC_ALIAS(DOS$fpclassify, libd___fpclassify);
DEFINE_PUBLIC_ALIAS(DOS$__fpclassify, libd___fpclassify);
DEFINE_PUBLIC_ALIAS(DOS$_dsign, libd___signbit);
DEFINE_PUBLIC_ALIAS(DOS$__signbit, libd___signbit);
DEFINE_PUBLIC_ALIAS(DOS$_fdclass, libd___fpclassifyf);
DEFINE_PUBLIC_ALIAS(DOS$fpclassifyf, libd___fpclassifyf);
DEFINE_PUBLIC_ALIAS(DOS$__fpclassifyf, libd___fpclassifyf);
DEFINE_PUBLIC_ALIAS(DOS$_fdsign, libd___signbitf);
DEFINE_PUBLIC_ALIAS(DOS$__signbitf, libd___signbitf);
DEFINE_PUBLIC_ALIAS(DOS$_ldclass, libd___fpclassifyl);
DEFINE_PUBLIC_ALIAS(DOS$fpclassifyl, libd___fpclassifyl);
DEFINE_PUBLIC_ALIAS(DOS$__fpclassifyl, libd___fpclassifyl);
DEFINE_PUBLIC_ALIAS(DOS$_ldsign, libd___signbitl);
DEFINE_PUBLIC_ALIAS(DOS$__signbitl, libd___signbitl);
DEFINE_PUBLIC_ALIAS(DOS$issignaling, libd___issignaling);
DEFINE_PUBLIC_ALIAS(DOS$__issignaling, libd___issignaling);
DEFINE_PUBLIC_ALIAS(DOS$issignalingf, libd___issignalingf);
DEFINE_PUBLIC_ALIAS(DOS$__issignalingf, libd___issignalingf);
DEFINE_PUBLIC_ALIAS(DOS$issignalingl, libd___issignalingl);
DEFINE_PUBLIC_ALIAS(DOS$__issignalingl, libd___issignalingl);

#endif /* !GUARD_LIBC_AUTO_DOSABI_MATH_C */
