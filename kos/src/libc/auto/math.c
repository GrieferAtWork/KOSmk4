/* HASH CRC-32:0x3e959089 */
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
/* Smallest integral value not less than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.ceil") double
NOTHROW(LIBCCALL libc_ceil)(double x) {
#line 570 "kos/src/libc/magic/math.c"
	double result;
	result = (double)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result < x)
		result += 1.0;
	return (double)result;
}

#include <hybrid/typecore.h>
/* Largest integer not greater than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.floor") double
NOTHROW(LIBCCALL libc_floor)(double x) {
#line 594 "kos/src/libc/magic/math.c"
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
#line 570 "kos/src/libc/magic/math.c"
	float result;
	result = (float)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result < x)
		result += 1.0;
	return (float)result;
}

#include <hybrid/typecore.h>
/* Largest integer not greater than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.floorf") float
NOTHROW(LIBCCALL libc_floorf)(float x) {
#line 594 "kos/src/libc/magic/math.c"
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
#line 570 "kos/src/libc/magic/math.c"
	long double result;
	result = (long double)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result < x)
		result += 1.0;
	return (long double)result;
}

#include <hybrid/typecore.h>
/* Largest integer not greater than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.floorl") long double
NOTHROW(LIBCCALL libc_floorl)(long double x) {
#line 594 "kos/src/libc/magic/math.c"
	long double result;
	result = (long double)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result > x)
		result -= 1.0;
	return (long double)result;
}

#include <bits/nan.h>
/* Return representation of qNaN for double type */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.nan") double
NOTHROW(LIBCCALL libc_nan)(char const *tagb) {
#line 689 "kos/src/libc/magic/math.c"
	(void)tagb;
	return (double)NAN;
}

#include <bits/nan.h>
/* Return representation of qNaN for double type */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.nanf") float
NOTHROW(LIBCCALL libc_nanf)(char const *tagb) {
#line 689 "kos/src/libc/magic/math.c"
	(void)tagb;
	return (float)NAN;
}

#include <bits/nan.h>
/* Return representation of qNaN for double type */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.nanl") long double
NOTHROW(LIBCCALL libc_nanl)(char const *tagb) {
#line 689 "kos/src/libc/magic/math.c"
	(void)tagb;
	return (long double)NAN;
}

#include <hybrid/typecore.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.round") double
NOTHROW(LIBCCALL libc_round)(double x) {
#line 899 "kos/src/libc/magic/math.c"
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

#include <hybrid/typecore.h>
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.trunc") double
NOTHROW(LIBCCALL libc_trunc)(double x) {
#line 918 "kos/src/libc/magic/math.c"
	return (double)(__INTMAX_TYPE__)x;
}

/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lround") long int
NOTHROW(LIBCCALL libc_lround)(double x) {
#line 934 "kos/src/libc/magic/math.c"
	return (long int)libc_round(x);
}

/* Return maximum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmax") double
NOTHROW(LIBCCALL libc_fmax)(double x,
                            double y) {
#line 946 "kos/src/libc/magic/math.c"
	return x < y ? y : x;
}

/* Return minimum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmin") double
NOTHROW(LIBCCALL libc_fmin)(double x,
                            double y) {
#line 952 "kos/src/libc/magic/math.c"
	return x < y ? x : y;
}

/* Multiply-add function computed as a ternary operation */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fma") double
NOTHROW(LIBCCALL libc_fma)(double x,
                           double y,
                           double z) {
#line 958 "kos/src/libc/magic/math.c"
	return (x * y) + z;
}

/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.llround") __LONGLONG
NOTHROW(LIBCCALL libc_llround)(double x) {
#line 969 "kos/src/libc/magic/math.c"
	return (__LONGLONG)libc_round(x);
}

#include <hybrid/typecore.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.roundf") float
NOTHROW(LIBCCALL libc_roundf)(float x) {
#line 899 "kos/src/libc/magic/math.c"
	float result;
	result = (float)(__INTMAX_TYPE__)x;
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

#include <hybrid/typecore.h>
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.truncf") float
NOTHROW(LIBCCALL libc_truncf)(float x) {
#line 918 "kos/src/libc/magic/math.c"
	return (float)(__INTMAX_TYPE__)x;
}

/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lroundf") long int
NOTHROW(LIBCCALL libc_lroundf)(float x) {
#line 934 "kos/src/libc/magic/math.c"
	return (long int)libc_roundf(x);
}

/* Return maximum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmaxf") float
NOTHROW(LIBCCALL libc_fmaxf)(float x,
                             float y) {
#line 946 "kos/src/libc/magic/math.c"
	return x < y ? y : x;
}

/* Return minimum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fminf") float
NOTHROW(LIBCCALL libc_fminf)(float x,
                             float y) {
#line 952 "kos/src/libc/magic/math.c"
	return x < y ? x : y;
}

/* Multiply-add function computed as a ternary operation */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmaf") float
NOTHROW(LIBCCALL libc_fmaf)(float x,
                            float y,
                            float z) {
#line 958 "kos/src/libc/magic/math.c"
	return (x * y) + z;
}

/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.llroundf") __LONGLONG
NOTHROW(LIBCCALL libc_llroundf)(float x) {
#line 969 "kos/src/libc/magic/math.c"
	return (__LONGLONG)libc_roundf(x);
}

#include <hybrid/typecore.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.roundl") long double
NOTHROW(LIBCCALL libc_roundl)(long double x) {
#line 899 "kos/src/libc/magic/math.c"
	long double result;
	result = (long double)(__INTMAX_TYPE__)x;
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

#include <hybrid/typecore.h>
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.truncl") long double
NOTHROW(LIBCCALL libc_truncl)(long double x) {
#line 918 "kos/src/libc/magic/math.c"
	return (long double)(__INTMAX_TYPE__)x;
}

/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lroundl") long int
NOTHROW(LIBCCALL libc_lroundl)(long double x) {
#line 934 "kos/src/libc/magic/math.c"
	return (long int)libc_roundl(x);
}

/* Return maximum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmaxl") long double
NOTHROW(LIBCCALL libc_fmaxl)(long double x,
                             long double y) {
#line 946 "kos/src/libc/magic/math.c"
	return x < y ? y : x;
}

/* Return minimum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fminl") long double
NOTHROW(LIBCCALL libc_fminl)(long double x,
                             long double y) {
#line 952 "kos/src/libc/magic/math.c"
	return x < y ? x : y;
}

/* Multiply-add function computed as a ternary operation */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmal") long double
NOTHROW(LIBCCALL libc_fmal)(long double x,
                            long double y,
                            long double z) {
#line 958 "kos/src/libc/magic/math.c"
	return (x * y) + z;
}

/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.llroundl") __LONGLONG
NOTHROW(LIBCCALL libc_llroundl)(long double x) {
#line 969 "kos/src/libc/magic/math.c"
	return (__LONGLONG)libc_roundl(x);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.__signbit") int
NOTHROW(LIBCCALL libc___signbit)(double x) {
#line 1966 "kos/src/libc/magic/math.c"
	return x < 0.0;
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.__signbitf") int
NOTHROW(LIBCCALL libc___signbitf)(float x) {
#line 1974 "kos/src/libc/magic/math.c"
	return x < 0.0f;
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.__signbitl") int
NOTHROW(LIBCCALL libc___signbitl)(long double x) {
#line 1982 "kos/src/libc/magic/math.c"
	return x < 0.0L;
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(ceil, libc_ceil);
DEFINE_PUBLIC_WEAK_ALIAS(__ceil, libc_ceil);
DEFINE_PUBLIC_WEAK_ALIAS(floor, libc_floor);
DEFINE_PUBLIC_WEAK_ALIAS(__floor, libc_floor);
DEFINE_PUBLIC_WEAK_ALIAS(ceilf, libc_ceilf);
DEFINE_PUBLIC_WEAK_ALIAS(__ceilf, libc_ceilf);
DEFINE_PUBLIC_WEAK_ALIAS(floorf, libc_floorf);
DEFINE_PUBLIC_WEAK_ALIAS(__floorf, libc_floorf);
DEFINE_PUBLIC_WEAK_ALIAS(ceill, libc_ceill);
DEFINE_PUBLIC_WEAK_ALIAS(__ceill, libc_ceill);
DEFINE_PUBLIC_WEAK_ALIAS(floorl, libc_floorl);
DEFINE_PUBLIC_WEAK_ALIAS(__floorl, libc_floorl);
DEFINE_PUBLIC_WEAK_ALIAS(nan, libc_nan);
DEFINE_PUBLIC_WEAK_ALIAS(__nan, libc_nan);
DEFINE_PUBLIC_WEAK_ALIAS(nanf, libc_nanf);
DEFINE_PUBLIC_WEAK_ALIAS(__nanf, libc_nanf);
DEFINE_PUBLIC_WEAK_ALIAS(nanl, libc_nanl);
DEFINE_PUBLIC_WEAK_ALIAS(__nanl, libc_nanl);
DEFINE_PUBLIC_WEAK_ALIAS(round, libc_round);
DEFINE_PUBLIC_WEAK_ALIAS(__round, libc_round);
DEFINE_PUBLIC_WEAK_ALIAS(trunc, libc_trunc);
DEFINE_PUBLIC_WEAK_ALIAS(__trunc, libc_trunc);
DEFINE_PUBLIC_WEAK_ALIAS(lround, libc_lround);
DEFINE_PUBLIC_WEAK_ALIAS(__lround, libc_lround);
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
DEFINE_PUBLIC_WEAK_ALIAS(fmaxl, libc_fmaxl);
DEFINE_PUBLIC_WEAK_ALIAS(__fmaxl, libc_fmaxl);
DEFINE_PUBLIC_WEAK_ALIAS(fminl, libc_fminl);
DEFINE_PUBLIC_WEAK_ALIAS(__fminl, libc_fminl);
DEFINE_PUBLIC_WEAK_ALIAS(fmal, libc_fmal);
DEFINE_PUBLIC_WEAK_ALIAS(__fmal, libc_fmal);
DEFINE_PUBLIC_WEAK_ALIAS(llroundl, libc_llroundl);
DEFINE_PUBLIC_WEAK_ALIAS(__llroundl, libc_llroundl);
DEFINE_PUBLIC_WEAK_ALIAS(__signbit, libc___signbit);
DEFINE_PUBLIC_WEAK_ALIAS(__signbitf, libc___signbitf);
DEFINE_PUBLIC_WEAK_ALIAS(__signbitl, libc___signbitl);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_MATH_C */
