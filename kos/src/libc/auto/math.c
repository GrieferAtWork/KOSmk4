/* HASH CRC-32:0x24698c4b */
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
#include "math.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <hybrid/typecore.h>

#include <libm/ceil.h>
/* Smallest integral value not less than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.ceil") double
NOTHROW(LIBCCALL libc_ceil)(double x) {
#line 827 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_ceil((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (double)__ieee754_ceilf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
	return (double)__ieee854_ceill((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
	double result;
	result = (double)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result < x)
		result += 1.0;
	return result;
#endif /* !... */
}

#include <libm/fabs.h>
/* Absolute value of X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fabs") double
NOTHROW(LIBCCALL libc_fabs)(double x) {
#line 846 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_fabs((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (double)__ieee754_fabsf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
	return (double)__ieee854_fabsl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
	return x < 0.0 ? -x : x;
#endif /* !... */
}

#include <hybrid/typecore.h>

#include <libm/floor.h>
/* Largest integer not greater than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.floor") double
NOTHROW(LIBCCALL libc_floor)(double x) {
#line 862 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_floor((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (double)__ieee754_floorf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
	return (double)__ieee854_floorl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
	double result;
	result = (double)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result > x)
		result -= 1.0;
	return result;
#endif /* !... */
}

#include <hybrid/typecore.h>

#include <libm/ceil.h>
/* Smallest integral value not less than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.ceilf") float
NOTHROW(LIBCCALL libc_ceilf)(float x) {
#line 901 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (float)__ieee754_ceilf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
	return (float)__ieee754_ceil((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
	return (float)__ieee854_ceill((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
	float result;
	result = (float)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result < x)
		result += 1.0f;
	return result;
#endif /* !... */
}

#include <libm/fabs.h>
/* Absolute value of X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fabsf") float
NOTHROW(LIBCCALL libc_fabsf)(float x) {
#line 919 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (float)__ieee754_fabsf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (float)__ieee754_fabs((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
	return (float)__ieee854_fabsl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
	return x < 0.0f ? -x : x;
#endif /* !... */
}

#include <hybrid/typecore.h>

#include <libm/floor.h>
/* Largest integer not greater than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.floorf") float
NOTHROW(LIBCCALL libc_floorf)(float x) {
#line 934 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (float)__ieee754_floorf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
	return (float)__ieee754_floor((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
	return (float)__ieee854_floorl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
	float result;
	result = (float)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result > x)
		result -= 1.0f;
	return result;
#endif /* !... */
}

#include <hybrid/typecore.h>

#include <libm/ceil.h>
/* Smallest integral value not less than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.ceill") __LONGDOUBLE
NOTHROW(LIBCCALL libc_ceill)(__LONGDOUBLE x) {
#line 970 "kos/src/libc/magic/math.c"
#ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return (__LONGDOUBLE)__ieee854_ceill((__IEEE854_LONG_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_ceil((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_ceilf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	__LONGDOUBLE result;
	result = (__LONGDOUBLE)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result < x)
		result += 1.0L;
	return result;
#endif /* !... */
}

#include <libm/fabs.h>
/* Return X with its signed changed to Y's */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fabsl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_fabsl)(__LONGDOUBLE x) {
#line 988 "kos/src/libc/magic/math.c"
#ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return (__LONGDOUBLE)__ieee854_fabsl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#elif define(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_fabs((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_fabsf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	return x < 0.0L ? -x : x;
#endif /* !... */
}

#include <hybrid/typecore.h>

#include <libm/floor.h>
/* Largest integer not greater than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.floorl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_floorl)(__LONGDOUBLE x) {
#line 1003 "kos/src/libc/magic/math.c"
#ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return (__LONGDOUBLE)__ieee854_floorl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_floor((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_floorf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	__LONGDOUBLE result;
	result = (__LONGDOUBLE)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result > x)
		result -= 1.0L;
	return result;
#endif /* !... */
}

#include <libm/copysign.h>
/* Return X with its signed changed to Y's */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.copysign") double
NOTHROW(LIBCCALL libc_copysign)(double num,
                                double sign) {
#line 1043 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_copysign((__IEEE754_DOUBLE_TYPE__)num, (__IEEE754_DOUBLE_TYPE__)sign);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (double)__ieee754_copysignf((__IEEE754_FLOAT_TYPE__)num, (__IEEE754_FLOAT_TYPE__)sign);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
	return (double)__ieee854_copysignl((__IEEE854_LONG_DOUBLE_TYPE__)num, (__IEEE854_LONG_DOUBLE_TYPE__)sign);
#else /* ... */
	if ((num < 0.0) != (sign < 0.0))
		num = -num;
	return num;
#endif /* !... */
}

#include <libm/copysign.h>
/* Return X with its signed changed to Y's */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.copysignf") float
NOTHROW(LIBCCALL libc_copysignf)(float num,
                                 float sign) {
#line 1075 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (float)__ieee754_copysignf((__IEEE754_FLOAT_TYPE__)num, (__IEEE754_FLOAT_TYPE__)sign);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
	return (float)__ieee754_copysign((__IEEE754_DOUBLE_TYPE__)num, (__IEEE754_DOUBLE_TYPE__)sign);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
	return (float)__ieee854_copysignl((__IEEE854_LONG_DOUBLE_TYPE__)num, (__IEEE854_LONG_DOUBLE_TYPE__)sign);
#else /* ... */
	if ((num < 0.0f) != (sign < 0.0f))
		num = -num;
	return num;
#endif /* !... */
}

#include <libm/copysign.h>
/* Return X with its signed changed to Y's */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.copysignl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_copysignl)(__LONGDOUBLE num,
                                 __LONGDOUBLE sign) {
#line 1107 "kos/src/libc/magic/math.c"
#ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return (__LONGDOUBLE)__ieee854_copysignl((__IEEE854_LONG_DOUBLE_TYPE__)num, (__IEEE854_LONG_DOUBLE_TYPE__)sign);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_copysign((__IEEE754_DOUBLE_TYPE__)num, (__IEEE754_DOUBLE_TYPE__)sign);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_copysignf((__IEEE754_FLOAT_TYPE__)num, (__IEEE754_FLOAT_TYPE__)sign);
#else /* ... */
	if ((num < 0.0L) != (sign < 0.0L))
		num = -num;
	return num;
#endif /* !... */
}

#include <hybrid/typecore.h>

#include <libm/round.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.round") double
NOTHROW(LIBCCALL libc_round)(double x) {
#line 1431 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_round((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (double)__ieee754_roundf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
	return (double)__ieee854_roundl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
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
#endif /* !... */
}

#include <hybrid/typecore.h>

#include <libm/trunc.h>
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.trunc") double
NOTHROW(LIBCCALL libc_trunc)(double x) {
#line 1459 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_trunc((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (double)__ieee754_truncf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
	return (double)__ieee854_truncl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
	return (double)(__INTMAX_TYPE__)x;
#endif /* !... */
}

#include <hybrid/typecore.h>

#include <libm/lrint.h>
/* Round X to nearest integral value according to current rounding direction */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lrint") long int
NOTHROW(LIBCCALL libc_lrint)(double x) {
#line 1482 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return __ieee754_lrint((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return __ieee754_lrintf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
	return __ieee754_lrintl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
	return (long int)libc_rint(x);
#endif /* !... */
}

#include <hybrid/typecore.h>

#include <libm/lround.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lround") long int
NOTHROW(LIBCCALL libc_lround)(double x) {
#line 1499 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return __ieee754_lround((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return __ieee754_lroundf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
	return __ieee854_lroundl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
	return (long int)libc_round(x);
#endif /* !... */
}

/* Return positive difference between X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fdim") double
NOTHROW(LIBCCALL libc_fdim)(double x,
                            double y) {
#line 1513 "kos/src/libc/magic/math.c"
	return libc_fabs(y - x);
}

/* Return maximum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmax") double
NOTHROW(LIBCCALL libc_fmax)(double x,
                            double y) {
#line 1519 "kos/src/libc/magic/math.c"
	return x < y ? y : x;
}

/* Return minimum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmin") double
NOTHROW(LIBCCALL libc_fmin)(double x,
                            double y) {
#line 1525 "kos/src/libc/magic/math.c"
	return x < y ? x : y;
}

/* Multiply-add function computed as a ternary operation */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fma") double
NOTHROW(LIBCCALL libc_fma)(double x,
                           double y,
                           double z) {
#line 1531 "kos/src/libc/magic/math.c"
	return (x * y) + z;
}

#include <hybrid/typecore.h>

#include <libm/lrint.h>
/* Round X to nearest integral value according to current rounding direction */
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS(libc_llrint, libc_lrint);
#else
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.llrint") __LONGLONG
NOTHROW(LIBCCALL libc_llrint)(double x) {
#line 1541 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return __ieee754_llrint((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return __ieee754_llrintf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
	return __ieee754_llrintl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
	return (__LONGLONG)libc_rint(x);
#endif /* !... */
}
#endif /* MAGIC:alias */

#include <hybrid/typecore.h>

#include <libm/lround.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS(libc_llround, libc_lround);
#else
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.llround") __LONGLONG
NOTHROW(LIBCCALL libc_llround)(double x) {
#line 1558 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return __ieee754_llround((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return __ieee754_llroundf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
	return __ieee854_llroundl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
	return (__LONGLONG)libc_round(x);
#endif /* !... */
}
#endif /* MAGIC:alias */

#include <hybrid/typecore.h>

#include <libm/round.h>
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.roundf") float
NOTHROW(LIBCCALL libc_roundf)(float x) {
#line 1637 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (float)__ieee754_roundf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
	return (float)__ieee754_round((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
	return (float)__ieee854_roundl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
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
#endif /* !... */
}

#include <libm/trunc.h>
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.truncf") float
NOTHROW(LIBCCALL libc_truncf)(float x) {
#line 1662 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (float)__ieee754_truncf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
	return (float)__ieee754_trunc((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
	return (float)__ieee854_truncl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
	return (float)(__INTMAX_TYPE__)x;
#endif /* !... */
}

#include <hybrid/typecore.h>

#include <libm/lrint.h>
/* Round X to nearest integral value according to current rounding direction */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lrintf") long int
NOTHROW(LIBCCALL libc_lrintf)(float x) {
#line 1681 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return __ieee754_lrintf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
	return __ieee754_lrint((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
	return __ieee754_lrintl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
	return (long int)libc_rintf(x);
#endif /* !... */
}

#include <hybrid/typecore.h>

#include <libm/lround.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lroundf") long int
NOTHROW(LIBCCALL libc_lroundf)(float x) {
#line 1697 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return __ieee754_lroundf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
	return __ieee754_lround((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
	return __ieee854_lroundl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
	return (long int)libc_roundf(x);
#endif /* !... */
}

/* Return positive difference between X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fdimf") float
NOTHROW(LIBCCALL libc_fdimf)(float x,
                             float y) {
#line 1513 "kos/src/libc/magic/math.c"
	return libc_fabs(y - x);
}

/* Return maximum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmaxf") float
NOTHROW(LIBCCALL libc_fmaxf)(float x,
                             float y) {
#line 1519 "kos/src/libc/magic/math.c"
	return x < y ? y : x;
}

/* Return minimum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fminf") float
NOTHROW(LIBCCALL libc_fminf)(float x,
                             float y) {
#line 1525 "kos/src/libc/magic/math.c"
	return x < y ? x : y;
}

/* Multiply-add function computed as a ternary operation */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmaf") float
NOTHROW(LIBCCALL libc_fmaf)(float x,
                            float y,
                            float z) {
#line 1531 "kos/src/libc/magic/math.c"
	return (x * y) + z;
}

#include <hybrid/typecore.h>

#include <libm/lrint.h>
/* Round X to nearest integral value according to current rounding direction */
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS(libc_llrintf, libc_lrintf);
#else
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.llrintf") __LONGLONG
NOTHROW(LIBCCALL libc_llrintf)(float x) {
#line 1726 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return __ieee754_llrintf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
	return __ieee754_llrint((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
	return __ieee754_llrintl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
	return (__LONGLONG)libc_rintf(x);
#endif /* !... */
}
#endif /* MAGIC:alias */

#include <hybrid/typecore.h>

#include <libm/lround.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS(libc_llroundf, libc_lroundf);
#else
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.llroundf") __LONGLONG
NOTHROW(LIBCCALL libc_llroundf)(float x) {
#line 1742 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return __ieee754_llroundf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
	return __ieee754_llround((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
	return __ieee854_llroundl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
	return (__LONGLONG)libc_roundf(x);
#endif /* !... */
}
#endif /* MAGIC:alias */

#include <hybrid/typecore.h>

#include <libm/round.h>
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.roundl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_roundl)(__LONGDOUBLE x) {
#line 1805 "kos/src/libc/magic/math.c"
#ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return (__LONGDOUBLE)__ieee854_roundl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_round((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_roundf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
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
#endif /* !... */
}

#include <libm/trunc.h>
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.truncl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_truncl)(__LONGDOUBLE x) {
#line 1831 "kos/src/libc/magic/math.c"
#ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return (__LONGDOUBLE)__ieee854_truncl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_trunc((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_truncf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	return (__LONGDOUBLE)(__INTMAX_TYPE__)x;
#endif /* !... */
}

#include <hybrid/typecore.h>

#include <libm/lrint.h>
/* Round X to nearest integral value according to current rounding direction */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lrintl") long int
NOTHROW(LIBCCALL libc_lrintl)(__LONGDOUBLE x) {
#line 1850 "kos/src/libc/magic/math.c"
#ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return __ieee854_lrintl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return __ieee854_lrintf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
	return __ieee854_lrint((__IEEE754_DOUBLE_TYPE__)x);
#else /* ... */
	return (long int)libc_rintl(x);
#endif /* !... */
}

#include <hybrid/typecore.h>

#include <libm/lround.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lroundl") long int
NOTHROW(LIBCCALL libc_lroundl)(__LONGDOUBLE x) {
#line 1866 "kos/src/libc/magic/math.c"
#ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return __ieee854_lroundl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return __ieee754_lroundf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
	return __ieee754_lround((__IEEE754_DOUBLE_TYPE__)x);
#else /* ... */
	return (long int)libc_roundl(x);
#endif /* !... */
}

/* Return positive difference between X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fdiml") __LONGDOUBLE
NOTHROW(LIBCCALL libc_fdiml)(__LONGDOUBLE x,
                             __LONGDOUBLE y) {
#line 1513 "kos/src/libc/magic/math.c"
	return libc_fabs(y - x);
}

/* Return maximum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmaxl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_fmaxl)(__LONGDOUBLE x,
                             __LONGDOUBLE y) {
#line 1519 "kos/src/libc/magic/math.c"
	return x < y ? y : x;
}

/* Return minimum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fminl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_fminl)(__LONGDOUBLE x,
                             __LONGDOUBLE y) {
#line 1525 "kos/src/libc/magic/math.c"
	return x < y ? x : y;
}

/* Multiply-add function computed as a ternary operation */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmal") __LONGDOUBLE
NOTHROW(LIBCCALL libc_fmal)(__LONGDOUBLE x,
                            __LONGDOUBLE y,
                            __LONGDOUBLE z) {
#line 1531 "kos/src/libc/magic/math.c"
	return (x * y) + z;
}

#include <hybrid/typecore.h>

#include <libm/lrint.h>
/* Round X to nearest integral value according to current rounding direction */
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS(libc_llrintl, libc_lrintl);
#else
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.llrintl") __LONGLONG
NOTHROW(LIBCCALL libc_llrintl)(__LONGDOUBLE x) {
#line 1896 "kos/src/libc/magic/math.c"
#ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return __ieee854_llrintl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return __ieee854_llrintf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
	return __ieee854_llrint((__IEEE754_DOUBLE_TYPE__)x);
#else /* ... */
	return (__LONGLONG)libc_rintl(x);
#endif /* !... */
}
#endif /* MAGIC:alias */

#include <hybrid/typecore.h>

#include <libm/lround.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS(libc_llroundl, libc_lroundl);
#else
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.llroundl") __LONGLONG
NOTHROW(LIBCCALL libc_llroundl)(__LONGDOUBLE x) {
#line 1912 "kos/src/libc/magic/math.c"
#ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return __ieee854_llroundl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return __ieee754_llroundf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
	return __ieee754_llround((__IEEE754_DOUBLE_TYPE__)x);
#else /* ... */
	return (__LONGLONG)libc_roundl(x);
#endif /* !... */
}
#endif /* MAGIC:alias */

#include <libm/signbit.h>
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.__signbit") int
NOTHROW(LIBCCALL libc___signbit)(double x) {
#line 2882 "kos/src/libc/magic/math.c"
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

#include <libm/signbit.h>
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.__signbitf") int
NOTHROW(LIBCCALL libc___signbitf)(float x) {
#line 2916 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return __ieee754_signbitf((__IEEE754_FLOAT_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
	return __ieee754_signbit((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
	return __ieee854_signbitl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#else /* ... */
	return x < 0.0f;
#endif /* !... */
}

#include <libm/signbit.h>
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.__signbitl") int
NOTHROW(LIBCCALL libc___signbitl)(__LONGDOUBLE x) {
#line 2950 "kos/src/libc/magic/math.c"
#ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return __ieee854_signbitl((__IEEE854_LONG_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
	return __ieee754_signbit((__IEEE754_DOUBLE_TYPE__)x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return __ieee754_signbitf((__IEEE754_FLOAT_TYPE__)x);
#else /* ... */
	return x < 0.0L;
#endif /* !... */
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
DEFINE_PUBLIC_WEAK_ALIAS(copysignf, libc_copysignf);
DEFINE_PUBLIC_WEAK_ALIAS(__copysignf, libc_copysignf);
DEFINE_PUBLIC_WEAK_ALIAS(copysignl, libc_copysignl);
DEFINE_PUBLIC_WEAK_ALIAS(__copysignl, libc_copysignl);
DEFINE_PUBLIC_WEAK_ALIAS(round, libc_round);
DEFINE_PUBLIC_WEAK_ALIAS(__round, libc_round);
DEFINE_PUBLIC_WEAK_ALIAS(trunc, libc_trunc);
DEFINE_PUBLIC_WEAK_ALIAS(__trunc, libc_trunc);
DEFINE_PUBLIC_WEAK_ALIAS(lrint, libc_lrint);
DEFINE_PUBLIC_WEAK_ALIAS(__lrint, libc_lrint);
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
DEFINE_PUBLIC_WEAK_ALIAS(llrint, libc_llrint);
DEFINE_PUBLIC_WEAK_ALIAS(__llrint, libc_llrint);
DEFINE_PUBLIC_WEAK_ALIAS(llround, libc_llround);
DEFINE_PUBLIC_WEAK_ALIAS(__llround, libc_llround);
DEFINE_PUBLIC_WEAK_ALIAS(roundf, libc_roundf);
DEFINE_PUBLIC_WEAK_ALIAS(__roundf, libc_roundf);
DEFINE_PUBLIC_WEAK_ALIAS(truncf, libc_truncf);
DEFINE_PUBLIC_WEAK_ALIAS(__truncf, libc_truncf);
DEFINE_PUBLIC_WEAK_ALIAS(lrintf, libc_lrintf);
DEFINE_PUBLIC_WEAK_ALIAS(__lrintf, libc_lrintf);
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
DEFINE_PUBLIC_WEAK_ALIAS(llrintf, libc_llrintf);
DEFINE_PUBLIC_WEAK_ALIAS(__llrintf, libc_llrintf);
DEFINE_PUBLIC_WEAK_ALIAS(llroundf, libc_llroundf);
DEFINE_PUBLIC_WEAK_ALIAS(__llroundf, libc_llroundf);
DEFINE_PUBLIC_WEAK_ALIAS(roundl, libc_roundl);
DEFINE_PUBLIC_WEAK_ALIAS(__roundl, libc_roundl);
DEFINE_PUBLIC_WEAK_ALIAS(truncl, libc_truncl);
DEFINE_PUBLIC_WEAK_ALIAS(__truncl, libc_truncl);
DEFINE_PUBLIC_WEAK_ALIAS(lrintl, libc_lrintl);
DEFINE_PUBLIC_WEAK_ALIAS(__lrintl, libc_lrintl);
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
DEFINE_PUBLIC_WEAK_ALIAS(llrintl, libc_llrintl);
DEFINE_PUBLIC_WEAK_ALIAS(__llrintl, libc_llrintl);
DEFINE_PUBLIC_WEAK_ALIAS(llroundl, libc_llroundl);
DEFINE_PUBLIC_WEAK_ALIAS(__llroundl, libc_llroundl);
DEFINE_PUBLIC_WEAK_ALIAS(__signbit, libc___signbit);
DEFINE_PUBLIC_WEAK_ALIAS(_dsign, libc___signbit);
DEFINE_PUBLIC_WEAK_ALIAS(__signbitf, libc___signbitf);
DEFINE_PUBLIC_WEAK_ALIAS(_fdsign, libc___signbitf);
DEFINE_PUBLIC_WEAK_ALIAS(__signbitl, libc___signbitl);
DEFINE_PUBLIC_WEAK_ALIAS(_ldsign, libc___signbitl);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_MATH_C */
