/* HASH CRC-32:0xcb323eff */
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
#ifndef GUARD_LIBC_AUTO_MATH_H
#define GUARD_LIBC_AUTO_MATH_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <math.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Smallest integral value not less than X */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_ceil)(double x);
/* Absolute value of X */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_fabs)(double x);
/* Largest integer not greater than X */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_floor)(double x);
/* Smallest integral value not less than X */
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc_ceilf)(float x);
/* Absolute value of X */
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc_fabsf)(float x);
/* Largest integer not greater than X */
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc_floorf)(float x);
/* Smallest integral value not less than X */
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_ceill)(__LONGDOUBLE x);
/* Return X with its signed changed to Y's */
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_fabsl)(__LONGDOUBLE x);
/* Largest integer not greater than X */
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_floorl)(__LONGDOUBLE x);
/* Return X with its signed changed to Y's */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_copysign)(double num, double sign);
/* Return X with its signed changed to Y's */
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc_copysignf)(float num, float sign);
/* Return X with its signed changed to Y's */
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_copysignl)(__LONGDOUBLE num, __LONGDOUBLE sign);
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_round)(double x);
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_trunc)(double x);
/* Round X to nearest integral value according to current rounding direction */
INTDEF ATTR_CONST WUNUSED long int NOTHROW(LIBCCALL libc_lrint)(double x);
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTDEF ATTR_CONST WUNUSED long int NOTHROW(LIBCCALL libc_lround)(double x);
/* Return positive difference between X and Y */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_fdim)(double x, double y);
/* Return maximum numeric value from X and Y */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_fmax)(double x, double y);
/* Return minimum numeric value from X and Y */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_fmin)(double x, double y);
/* Multiply-add function computed as a ternary operation */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_fma)(double x, double y, double z);
/* Round X to nearest integral value according to current rounding direction */
INTDEF ATTR_CONST WUNUSED __LONGLONG NOTHROW(LIBCCALL libc_llrint)(double x);
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTDEF ATTR_CONST WUNUSED __LONGLONG NOTHROW(LIBCCALL libc_llround)(double x);
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc_roundf)(float x);
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc_truncf)(float x);
/* Round X to nearest integral value according to current rounding direction */
INTDEF ATTR_CONST WUNUSED long int NOTHROW(LIBCCALL libc_lrintf)(float x);
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTDEF ATTR_CONST WUNUSED long int NOTHROW(LIBCCALL libc_lroundf)(float x);
/* Return positive difference between X and Y */
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc_fdimf)(float x, float y);
/* Return maximum numeric value from X and Y */
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc_fmaxf)(float x, float y);
/* Return minimum numeric value from X and Y */
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc_fminf)(float x, float y);
/* Multiply-add function computed as a ternary operation */
INTDEF ATTR_CONST WUNUSED float NOTHROW(LIBCCALL libc_fmaf)(float x, float y, float z);
/* Round X to nearest integral value according to current rounding direction */
INTDEF ATTR_CONST WUNUSED __LONGLONG NOTHROW(LIBCCALL libc_llrintf)(float x);
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTDEF ATTR_CONST WUNUSED __LONGLONG NOTHROW(LIBCCALL libc_llroundf)(float x);
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_roundl)(__LONGDOUBLE x);
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_truncl)(__LONGDOUBLE x);
/* Round X to nearest integral value according to current rounding direction */
INTDEF ATTR_CONST WUNUSED long int NOTHROW(LIBCCALL libc_lrintl)(__LONGDOUBLE x);
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTDEF ATTR_CONST WUNUSED long int NOTHROW(LIBCCALL libc_lroundl)(__LONGDOUBLE x);
/* Return positive difference between X and Y */
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_fdiml)(__LONGDOUBLE x, __LONGDOUBLE y);
/* Return maximum numeric value from X and Y */
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_fmaxl)(__LONGDOUBLE x, __LONGDOUBLE y);
/* Return minimum numeric value from X and Y */
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_fminl)(__LONGDOUBLE x, __LONGDOUBLE y);
/* Multiply-add function computed as a ternary operation */
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBCCALL libc_fmal)(__LONGDOUBLE x, __LONGDOUBLE y, __LONGDOUBLE z);
/* Round X to nearest integral value according to current rounding direction */
INTDEF ATTR_CONST WUNUSED __LONGLONG NOTHROW(LIBCCALL libc_llrintl)(__LONGDOUBLE x);
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTDEF ATTR_CONST WUNUSED __LONGLONG NOTHROW(LIBCCALL libc_llroundl)(__LONGDOUBLE x);
/* Smallest integral value not less than X */
#define libc___ceil libc_ceil
/* Absolute value of X */
#define libc___fabs libc_fabs
/* Largest integer not greater than X */
#define libc___floor libc_floor
/* Smallest integral value not less than X */
#define libc___ceilf libc_ceilf
/* Absolute value of X */
#define libc___fabsf libc_fabsf
/* Largest integer not greater than X */
#define libc___floorf libc_floorf
/* Smallest integral value not less than X */
#define libc___ceill libc_ceill
/* Return X with its signed changed to Y's */
#define libc___fabsl libc_fabsl
/* Largest integer not greater than X */
#define libc___floorl libc_floorl
/* Return X with its signed changed to Y's */
#define libc___copysign libc_copysign
/* Return X with its signed changed to Y's */
#define libc___copysignf libc_copysignf
/* Return X with its signed changed to Y's */
#define libc___copysignl libc_copysignl
/* Round X to nearest integral value, rounding halfway cases away from zero */
#define libc___round libc_round
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
#define libc___trunc libc_trunc
/* Round X to nearest integral value according to current rounding direction */
#define libc___lrint libc_lrint
/* Round X to nearest integral value, rounding halfway cases away from zero */
#define libc___lround libc_lround
/* Return positive difference between X and Y */
#define libc___fdim libc_fdim
/* Return maximum numeric value from X and Y */
#define libc___fmax libc_fmax
/* Return minimum numeric value from X and Y */
#define libc___fmin libc_fmin
/* Multiply-add function computed as a ternary operation */
#define libc___fma libc_fma
#define libc___roundf libc_roundf
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
#define libc___truncf libc_truncf
/* Round X to nearest integral value according to current rounding direction */
#define libc___lrintf libc_lrintf
/* Round X to nearest integral value, rounding halfway cases away from zero */
#define libc___lroundf libc_lroundf
/* Return positive difference between X and Y */
#define libc___fdimf libc_fdimf
/* Return maximum numeric value from X and Y */
#define libc___fmaxf libc_fmaxf
/* Return minimum numeric value from X and Y */
#define libc___fminf libc_fminf
/* Multiply-add function computed as a ternary operation */
#define libc___fmaf libc_fmaf
/* Round X to nearest integral value according to current rounding direction */
#define libc___llrint libc_llrint
/* Round X to nearest integral value, rounding halfway cases away from zero */
#define libc___llround libc_llround
/* Round X to nearest integral value according to current rounding direction */
#define libc___llrintf libc_llrintf
/* Round X to nearest integral value, rounding halfway cases away from zero */
#define libc___llroundf libc_llroundf
#define libc___roundl libc_roundl
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
#define libc___truncl libc_truncl
/* Round X to nearest integral value according to current rounding direction */
#define libc___lrintl libc_lrintl
/* Round X to nearest integral value, rounding halfway cases away from zero */
#define libc___lroundl libc_lroundl
/* Return positive difference between X and Y */
#define libc___fdiml libc_fdiml
/* Return maximum numeric value from X and Y */
#define libc___fmaxl libc_fmaxl
/* Return minimum numeric value from X and Y */
#define libc___fminl libc_fminl
/* Multiply-add function computed as a ternary operation */
#define libc___fmal libc_fmal
/* Round X to nearest integral value according to current rounding direction */
#define libc___llrintl libc_llrintl
/* Round X to nearest integral value, rounding halfway cases away from zero */
#define libc___llroundl libc_llroundl
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc___signbit)(double x);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc___signbitf)(float x);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc___signbitl)(__LONGDOUBLE x);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_MATH_H */
