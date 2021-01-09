/* HASH CRC-32:0x6976c60c */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
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

#ifndef __KERNEL__
/* Arc cosine of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_acos)(double x);
/* Arc sine of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_asin)(double x);
/* Cosine of X */
INTDEF WUNUSED __DECL_SIMD_cos double NOTHROW(LIBCCALL libc_cos)(double x);
/* Sine of X */
INTDEF WUNUSED __DECL_SIMD_sin double NOTHROW(LIBCCALL libc_sin)(double x);
/* Tangent of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_tan)(double x);
/* Hyperbolic cosine of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_cosh)(double x);
/* Hyperbolic sine of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_sinh)(double x);
/* Hyperbolic tangent of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_tanh)(double x);
/* Hyperbolic arc cosine of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_acosh)(double x);
/* Hyperbolic arc sine of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_asinh)(double x);
/* Hyperbolic arc tangent of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_atanh)(double x);
/* Natural logarithm of X */
INTDEF WUNUSED __DECL_SIMD_log double NOTHROW(LIBCCALL libc_log)(double x);
/* Base-ten logarithm of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_log10)(double x);
/* Return log(1 + X) */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_log1p)(double x);
/* Return the base 2 signed integral exponent of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_logb)(double x);
/* Compute base-2 exponential of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_exp2)(double x);
/* Compute base-2 logarithm of X */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_log2)(double x);
/* Return `sqrt(X*X + Y*Y)' */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_hypot)(double x, double y);
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_erf)(double x);
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_erfc)(double x);
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_lgamma)(double x);
/* True gamma function */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_tgamma)(double x);
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_remquo)(double x, double y, int *pquo);
/* Cosine and sine of X */
INTDEF __DECL_SIMD_sincos NONNULL((2, 3)) void NOTHROW(LIBCCALL libc_sincos)(double x, double *psinx, double *pcosx);
/* A function missing in all standards: compute exponent to base ten */
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_exp10)(double x);
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_j0)(double x);
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_j1)(double x);
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_jn)(int n, double x);
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_y0)(double x);
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_y1)(double x);
INTDEF WUNUSED double NOTHROW(LIBCCALL libc_yn)(int n, double x);
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
INTDEF WUNUSED double NOTHROW_NCX(LIBCCALL libc_lgamma_r)(double x, int *signgamp);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_MATH_H */
