/* HASH CRC-32:0xf12eb870 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_MATH_C
#define GUARD_LIBC_AUTO_MATH_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "math.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <hybrid/typecore.h>
/* Smallest integral value not less than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.ceil") double
NOTHROW(LIBCCALL libc_ceil)(double x) {
#line 346 "kos/src/libc/magic/math.c"
	double result;
	result = (double)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result < x)
		result += 1.0;
	return (double)result;
}

/* Absolute value of X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fabs") double
NOTHROW(LIBCCALL libc_fabs)(double x) {
#line 356 "kos/src/libc/magic/math.c"
	return x < 0 ? -x : x;
}

#include <hybrid/typecore.h>
/* Largest integer not greater than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.floor") double
NOTHROW(LIBCCALL libc_floor)(double x) {
#line 363 "kos/src/libc/magic/math.c"
	double result;
	result = (double)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result > x)
		result -= 1.0;
	return (double)result;
}

#include <hybrid/typecore.h>
/* Smallest integral value not less than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.ceilf") float
NOTHROW(LIBCCALL libc_ceilf)(float x) {
#line 346 "kos/src/libc/magic/math.c"
	float result;
	result = (float)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result < x)
		result += 1.0;
	return (float)result;
}

/* Absolute value of X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fabsf") float
NOTHROW(LIBCCALL libc_fabsf)(float x) {
#line 356 "kos/src/libc/magic/math.c"
	return x < 0 ? -x : x;
}

#include <hybrid/typecore.h>
/* Largest integer not greater than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.floorf") float
NOTHROW(LIBCCALL libc_floorf)(float x) {
#line 363 "kos/src/libc/magic/math.c"
	float result;
	result = (float)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result > x)
		result -= 1.0;
	return (float)result;
}

#include <hybrid/typecore.h>
/* Smallest integral value not less than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.ceill") long double
NOTHROW(LIBCCALL libc_ceill)(long double x) {
#line 346 "kos/src/libc/magic/math.c"
	long double result;
	result = (long double)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result < x)
		result += 1.0;
	return (long double)result;
}

/* Absolute value of X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fabsl") long double
NOTHROW(LIBCCALL libc_fabsl)(long double x) {
#line 356 "kos/src/libc/magic/math.c"
	return x < 0 ? -x : x;
}

#include <hybrid/typecore.h>
/* Largest integer not greater than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.floorl") long double
NOTHROW(LIBCCALL libc_floorl)(long double x) {
#line 363 "kos/src/libc/magic/math.c"
	long double result;
	result = (long double)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result > x)
		result -= 1.0;
	return (long double)result;
}

/* Return X with its signed changed to Y's */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.copysign") double
NOTHROW(LIBCCALL libc_copysign)(double num,
                                double sign) {
#line 391 "kos/src/libc/magic/math.c"
	if ((num < 0.0) != (sign < 0.0))
		num = -num;
	return num;
}

#include <bits/nan.h>
/* Return representation of qNaN for double type */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.nan") double
NOTHROW(LIBCCALL libc_nan)(char const *tagb) {
#line 400 "kos/src/libc/magic/math.c"
	(void)tagb;
	return (double)NAN;
}

/* Return X with its signed changed to Y's */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.copysignf") float
NOTHROW(LIBCCALL libc_copysignf)(float num,
                                 float sign) {
#line 391 "kos/src/libc/magic/math.c"
	if ((num < 0.0) != (sign < 0.0))
		num = -num;
	return num;
}

#include <bits/nan.h>
/* Return representation of qNaN for double type */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.nanf") float
NOTHROW(LIBCCALL libc_nanf)(char const *tagb) {
#line 400 "kos/src/libc/magic/math.c"
	(void)tagb;
	return (float)NAN;
}

/* Return X with its signed changed to Y's */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.copysignl") long double
NOTHROW(LIBCCALL libc_copysignl)(long double num,
                                 long double sign) {
#line 391 "kos/src/libc/magic/math.c"
	if ((num < 0.0) != (sign < 0.0))
		num = -num;
	return num;
}

#include <bits/nan.h>
/* Return representation of qNaN for double type */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.nanl") long double
NOTHROW(LIBCCALL libc_nanl)(char const *tagb) {
#line 400 "kos/src/libc/magic/math.c"
	(void)tagb;
	return (long double)NAN;
}

#include <hybrid/typecore.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.round") double
NOTHROW(LIBCCALL libc_round)(double x) {
#line 487 "kos/src/libc/magic/math.c"
	double result;
	result = (double)(__INTMAX_TYPE__)x;
	if (x < 0) {
		/* result >= x */
		if ((result - x) >= 0.5)
			result += 1.0;
	} else {
		/* result <= x */
		if ((x - result) >= 0.5)
			result -= 1.0;
	}
	return result;
}

#include <hybrid/typecore.h>
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.trunc") double
NOTHROW(LIBCCALL libc_trunc)(double x) {
#line 506 "kos/src/libc/magic/math.c"
	return (double)(__INTMAX_TYPE__)x;
}

/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lround") long int
NOTHROW(LIBCCALL libc_lround)(double x) {
#line 521 "kos/src/libc/magic/math.c"
	return (long int)libc_round(x);
}

/* Return positive difference between X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fdim") double
NOTHROW(LIBCCALL libc_fdim)(double x,
                            double y) {
#line 527 "kos/src/libc/magic/math.c"
	return libc_fabs(y - x);
}

/* Return maximum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmax") double
NOTHROW(LIBCCALL libc_fmax)(double x,
                            double y) {
#line 533 "kos/src/libc/magic/math.c"
	return x < y ? y : x;
}

/* Return minimum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmin") double
NOTHROW(LIBCCALL libc_fmin)(double x,
                            double y) {
#line 539 "kos/src/libc/magic/math.c"
	return x < y ? x : y;
}

/* Multiply-add function computed as a ternary operation */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fma") double
NOTHROW(LIBCCALL libc_fma)(double x,
                           double y,
                           double z) {
#line 545 "kos/src/libc/magic/math.c"
	return (x * y) + z;
}

/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.llround") __LONGLONG
NOTHROW(LIBCCALL libc_llround)(double x) {
#line 556 "kos/src/libc/magic/math.c"
	return (__LONGLONG)libc_round(x);
}

#include <hybrid/typecore.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.roundf") float
NOTHROW(LIBCCALL libc_roundf)(float x) {
#line 487 "kos/src/libc/magic/math.c"
	float result;
	result = (float)(__INTMAX_TYPE__)x;
	if (x < 0) {
		/* result >= x */
		if ((result - x) >= 0.5)
			result += 1.0;
	} else {
		/* result <= x */
		if ((x - result) >= 0.5)
			result -= 1.0;
	}
	return result;
}

#include <hybrid/typecore.h>
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.truncf") float
NOTHROW(LIBCCALL libc_truncf)(float x) {
#line 506 "kos/src/libc/magic/math.c"
	return (float)(__INTMAX_TYPE__)x;
}

/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lroundf") long int
NOTHROW(LIBCCALL libc_lroundf)(float x) {
#line 521 "kos/src/libc/magic/math.c"
	return (long int)libc_roundf(x);
}

/* Return positive difference between X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fdimf") float
NOTHROW(LIBCCALL libc_fdimf)(float x,
                             float y) {
#line 527 "kos/src/libc/magic/math.c"
	return libc_fabsf(y - x);
}

/* Return maximum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmaxf") float
NOTHROW(LIBCCALL libc_fmaxf)(float x,
                             float y) {
#line 533 "kos/src/libc/magic/math.c"
	return x < y ? y : x;
}

/* Return minimum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fminf") float
NOTHROW(LIBCCALL libc_fminf)(float x,
                             float y) {
#line 539 "kos/src/libc/magic/math.c"
	return x < y ? x : y;
}

/* Multiply-add function computed as a ternary operation */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmaf") float
NOTHROW(LIBCCALL libc_fmaf)(float x,
                            float y,
                            float z) {
#line 545 "kos/src/libc/magic/math.c"
	return (x * y) + z;
}

/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.llroundf") __LONGLONG
NOTHROW(LIBCCALL libc_llroundf)(float x) {
#line 556 "kos/src/libc/magic/math.c"
	return (__LONGLONG)libc_roundf(x);
}

#include <hybrid/typecore.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.roundl") long double
NOTHROW(LIBCCALL libc_roundl)(long double x) {
#line 487 "kos/src/libc/magic/math.c"
	long double result;
	result = (long double)(__INTMAX_TYPE__)x;
	if (x < 0) {
		/* result >= x */
		if ((result - x) >= 0.5)
			result += 1.0;
	} else {
		/* result <= x */
		if ((x - result) >= 0.5)
			result -= 1.0;
	}
	return result;
}

#include <hybrid/typecore.h>
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.truncl") long double
NOTHROW(LIBCCALL libc_truncl)(long double x) {
#line 506 "kos/src/libc/magic/math.c"
	return (long double)(__INTMAX_TYPE__)x;
}

/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lroundl") long int
NOTHROW(LIBCCALL libc_lroundl)(long double x) {
#line 521 "kos/src/libc/magic/math.c"
	return (long int)libc_roundl(x);
}

/* Return positive difference between X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fdiml") long double
NOTHROW(LIBCCALL libc_fdiml)(long double x,
                             long double y) {
#line 527 "kos/src/libc/magic/math.c"
	return libc_fabsl(y - x);
}

/* Return maximum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmaxl") long double
NOTHROW(LIBCCALL libc_fmaxl)(long double x,
                             long double y) {
#line 533 "kos/src/libc/magic/math.c"
	return x < y ? y : x;
}

/* Return minimum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fminl") long double
NOTHROW(LIBCCALL libc_fminl)(long double x,
                             long double y) {
#line 539 "kos/src/libc/magic/math.c"
	return x < y ? x : y;
}

/* Multiply-add function computed as a ternary operation */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmal") long double
NOTHROW(LIBCCALL libc_fmal)(long double x,
                            long double y,
                            long double z) {
#line 545 "kos/src/libc/magic/math.c"
	return (x * y) + z;
}

/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.llroundl") __LONGLONG
NOTHROW(LIBCCALL libc_llroundl)(long double x) {
#line 556 "kos/src/libc/magic/math.c"
	return (__LONGLONG)libc_roundl(x);
}

#include <bits/huge_val.h>
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.isinf") int
NOTHROW(LIBCCALL libc_isinf)(double val) {
#line 802 "kos/src/libc/magic/math.c"
	return val == HUGE_VAL;
}

#include <bits/huge_valf.h>
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.isinff") int
NOTHROW(LIBCCALL libc_isinff)(float val) {
#line 808 "kos/src/libc/magic/math.c"
	return val == HUGE_VALF;
}

#include <bits/huge_vall.h>
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.isinfl") int
NOTHROW(LIBCCALL libc_isinfl)(long double val) {
#line 815 "kos/src/libc/magic/math.c"
	return val == HUGE_VALL;
}

/* Return nonzero if VALUE is finite and not NaN */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.finite") int
NOTHROW(LIBCCALL libc_finite)(double val) {
#line 822 "kos/src/libc/magic/math.c"
	return !libc_isinf(val) && !libc_isnan(val);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.finitef") int
NOTHROW(LIBCCALL libc_finitef)(float val) {
#line 833 "kos/src/libc/magic/math.c"
	return !libc_isinff(val) && !libc_isnanf(val);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.finitel") int
NOTHROW(LIBCCALL libc_finitel)(long double val) {
#line 843 "kos/src/libc/magic/math.c"
	return !libc_isinfl(val) && !libc_isnanl(val);
}

#include <bits/nan.h>
/* Return nonzero if VALUE is not a number */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.isnan") int
NOTHROW(LIBCCALL libc_isnan)(double val) {
#line 858 "kos/src/libc/magic/math.c"
	return val == (double)NAN;
}

#include <bits/nan.h>
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.isnanf") int
NOTHROW(LIBCCALL libc_isnanf)(float val) {
#line 864 "kos/src/libc/magic/math.c"
	return val == (float)NAN;
}

#include <bits/nan.h>
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.isnanl") int
NOTHROW(LIBCCALL libc_isnanl)(long double val) {
#line 871 "kos/src/libc/magic/math.c"
	return val == (long double)NAN;
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(ceil, libc_ceil);
DEFINE_PUBLIC_WEAK_ALIAS(__ceil, libc_ceil);
DEFINE_PUBLIC_WEAK_ALIAS(fabs, libc_fabs);
DEFINE_PUBLIC_WEAK_ALIAS(__fabs, libc_fabs);
DEFINE_PUBLIC_WEAK_ALIAS(floor, libc_floor);
DEFINE_PUBLIC_WEAK_ALIAS(__floor, libc_floor);
DEFINE_PUBLIC_WEAK_ALIAS(ceilf, libc_ceilf);
DEFINE_PUBLIC_WEAK_ALIAS(__ceilf, libc_ceilf);
DEFINE_PUBLIC_WEAK_ALIAS(fabsf, libc_fabsf);
DEFINE_PUBLIC_WEAK_ALIAS(__fabsf, libc_fabsf);
DEFINE_PUBLIC_WEAK_ALIAS(floorf, libc_floorf);
DEFINE_PUBLIC_WEAK_ALIAS(__floorf, libc_floorf);
DEFINE_PUBLIC_WEAK_ALIAS(ceill, libc_ceill);
DEFINE_PUBLIC_WEAK_ALIAS(__ceill, libc_ceill);
DEFINE_PUBLIC_WEAK_ALIAS(fabsl, libc_fabsl);
DEFINE_PUBLIC_WEAK_ALIAS(__fabsl, libc_fabsl);
DEFINE_PUBLIC_WEAK_ALIAS(floorl, libc_floorl);
DEFINE_PUBLIC_WEAK_ALIAS(__floorl, libc_floorl);
DEFINE_PUBLIC_WEAK_ALIAS(copysign, libc_copysign);
DEFINE_PUBLIC_WEAK_ALIAS(_copysign, libc_copysign);
DEFINE_PUBLIC_WEAK_ALIAS(__copysign, libc_copysign);
DEFINE_PUBLIC_WEAK_ALIAS(nan, libc_nan);
DEFINE_PUBLIC_WEAK_ALIAS(__nan, libc_nan);
DEFINE_PUBLIC_WEAK_ALIAS(copysignf, libc_copysignf);
DEFINE_PUBLIC_WEAK_ALIAS(__copysignf, libc_copysignf);
DEFINE_PUBLIC_WEAK_ALIAS(nanf, libc_nanf);
DEFINE_PUBLIC_WEAK_ALIAS(__nanf, libc_nanf);
DEFINE_PUBLIC_WEAK_ALIAS(copysignl, libc_copysignl);
DEFINE_PUBLIC_WEAK_ALIAS(__copysignl, libc_copysignl);
DEFINE_PUBLIC_WEAK_ALIAS(nanl, libc_nanl);
DEFINE_PUBLIC_WEAK_ALIAS(__nanl, libc_nanl);
DEFINE_PUBLIC_WEAK_ALIAS(round, libc_round);
DEFINE_PUBLIC_WEAK_ALIAS(__round, libc_round);
DEFINE_PUBLIC_WEAK_ALIAS(trunc, libc_trunc);
DEFINE_PUBLIC_WEAK_ALIAS(__trunc, libc_trunc);
DEFINE_PUBLIC_WEAK_ALIAS(lround, libc_lround);
DEFINE_PUBLIC_WEAK_ALIAS(__lround, libc_lround);
DEFINE_PUBLIC_WEAK_ALIAS(fdim, libc_fdim);
DEFINE_PUBLIC_WEAK_ALIAS(__fdim, libc_fdim);
DEFINE_PUBLIC_WEAK_ALIAS(fmax, libc_fmax);
DEFINE_PUBLIC_WEAK_ALIAS(__fmax, libc_fmax);
DEFINE_PUBLIC_WEAK_ALIAS(fmin, libc_fmin);
DEFINE_PUBLIC_WEAK_ALIAS(__fmin, libc_fmin);
DEFINE_PUBLIC_WEAK_ALIAS(fma, libc_fma);
DEFINE_PUBLIC_WEAK_ALIAS(__fma, libc_fma);
DEFINE_PUBLIC_WEAK_ALIAS(llround, libc_llround);
DEFINE_PUBLIC_WEAK_ALIAS(__llround, libc_llround);
DEFINE_PUBLIC_WEAK_ALIAS(roundf, libc_roundf);
DEFINE_PUBLIC_WEAK_ALIAS(__roundf, libc_roundf);
DEFINE_PUBLIC_WEAK_ALIAS(truncf, libc_truncf);
DEFINE_PUBLIC_WEAK_ALIAS(__truncf, libc_truncf);
DEFINE_PUBLIC_WEAK_ALIAS(lroundf, libc_lroundf);
DEFINE_PUBLIC_WEAK_ALIAS(__lroundf, libc_lroundf);
DEFINE_PUBLIC_WEAK_ALIAS(fdimf, libc_fdimf);
DEFINE_PUBLIC_WEAK_ALIAS(__fdimf, libc_fdimf);
DEFINE_PUBLIC_WEAK_ALIAS(fmaxf, libc_fmaxf);
DEFINE_PUBLIC_WEAK_ALIAS(__fmaxf, libc_fmaxf);
DEFINE_PUBLIC_WEAK_ALIAS(fminf, libc_fminf);
DEFINE_PUBLIC_WEAK_ALIAS(__fminf, libc_fminf);
DEFINE_PUBLIC_WEAK_ALIAS(fmaf, libc_fmaf);
DEFINE_PUBLIC_WEAK_ALIAS(__fmaf, libc_fmaf);
DEFINE_PUBLIC_WEAK_ALIAS(llroundf, libc_llroundf);
DEFINE_PUBLIC_WEAK_ALIAS(__llroundf, libc_llroundf);
DEFINE_PUBLIC_WEAK_ALIAS(roundl, libc_roundl);
DEFINE_PUBLIC_WEAK_ALIAS(__roundl, libc_roundl);
DEFINE_PUBLIC_WEAK_ALIAS(truncl, libc_truncl);
DEFINE_PUBLIC_WEAK_ALIAS(__truncl, libc_truncl);
DEFINE_PUBLIC_WEAK_ALIAS(lroundl, libc_lroundl);
DEFINE_PUBLIC_WEAK_ALIAS(__lroundl, libc_lroundl);
DEFINE_PUBLIC_WEAK_ALIAS(fdiml, libc_fdiml);
DEFINE_PUBLIC_WEAK_ALIAS(__fdiml, libc_fdiml);
DEFINE_PUBLIC_WEAK_ALIAS(fmaxl, libc_fmaxl);
DEFINE_PUBLIC_WEAK_ALIAS(__fmaxl, libc_fmaxl);
DEFINE_PUBLIC_WEAK_ALIAS(fminl, libc_fminl);
DEFINE_PUBLIC_WEAK_ALIAS(__fminl, libc_fminl);
DEFINE_PUBLIC_WEAK_ALIAS(fmal, libc_fmal);
DEFINE_PUBLIC_WEAK_ALIAS(__fmal, libc_fmal);
DEFINE_PUBLIC_WEAK_ALIAS(llroundl, libc_llroundl);
DEFINE_PUBLIC_WEAK_ALIAS(__llroundl, libc_llroundl);
DEFINE_PUBLIC_WEAK_ALIAS(isinf, libc_isinf);
DEFINE_PUBLIC_WEAK_ALIAS(__isinf, libc_isinf);
DEFINE_PUBLIC_WEAK_ALIAS(isinff, libc_isinff);
DEFINE_PUBLIC_WEAK_ALIAS(__isinff, libc_isinff);
DEFINE_PUBLIC_WEAK_ALIAS(isinfl, libc_isinfl);
DEFINE_PUBLIC_WEAK_ALIAS(__isinfl, libc_isinfl);
DEFINE_PUBLIC_WEAK_ALIAS(finite, libc_finite);
DEFINE_PUBLIC_WEAK_ALIAS(_finite, libc_finite);
DEFINE_PUBLIC_WEAK_ALIAS(__finite, libc_finite);
DEFINE_PUBLIC_WEAK_ALIAS(finitef, libc_finitef);
DEFINE_PUBLIC_WEAK_ALIAS(__finitef, libc_finitef);
DEFINE_PUBLIC_WEAK_ALIAS(finitel, libc_finitel);
DEFINE_PUBLIC_WEAK_ALIAS(__finitel, libc_finitel);
DEFINE_PUBLIC_WEAK_ALIAS(isnan, libc_isnan);
DEFINE_PUBLIC_WEAK_ALIAS(_isnan, libc_isnan);
DEFINE_PUBLIC_WEAK_ALIAS(__isnan, libc_isnan);
DEFINE_PUBLIC_WEAK_ALIAS(isnanf, libc_isnanf);
DEFINE_PUBLIC_WEAK_ALIAS(__isnanf, libc_isnanf);
DEFINE_PUBLIC_WEAK_ALIAS(isnanl, libc_isnanl);
DEFINE_PUBLIC_WEAK_ALIAS(__isnanl, libc_isnanl);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_MATH_C */
