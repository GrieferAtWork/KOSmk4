/* HASH CRC-32:0x3afb3d57 */
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
#line 629 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUN
	return __LIBM_MATHFUN(ceil, x);
#else /* __LIBM_MATHFUN */
	double result;
	result = (double)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result < x)
		result += 1.0;
	return result;
#endif /* !__LIBM_MATHFUN */
}

#include <libm/fabs.h>
/* Absolute value of X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fabs") double
NOTHROW(LIBCCALL libc_fabs)(double x) {
#line 644 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUN
	return __LIBM_MATHFUN(fabs, x);
#else /* __LIBM_MATHFUN */
	return x < 0.0 ? -x : x;
#endif /* !__LIBM_MATHFUN */
}

#include <hybrid/typecore.h>

#include <libm/floor.h>
/* Largest integer not greater than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.floor") double
NOTHROW(LIBCCALL libc_floor)(double x) {
#line 656 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUN
	return __LIBM_MATHFUN(floor, x);
#else /* __LIBM_MATHFUN */
	double result;
	result = (double)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result > x)
		result -= 1.0;
	return result;
#endif /* !__LIBM_MATHFUN */
}

#include <libm/copysign.h>
/* Return X with its signed changed to Y's */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.copysign") double
NOTHROW(LIBCCALL libc_copysign)(double num,
                                double sign) {
#line 717 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUN2
	return __LIBM_MATHFUN2(copysign, num, sign);
#else /* __LIBM_MATHFUN2 */
	if ((num < 0.0) != (sign < 0.0))
		num = -num;
	return num;
#endif /* !__LIBM_MATHFUN2 */
}

#include <hybrid/typecore.h>

#include <libm/round.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.round") double
NOTHROW(LIBCCALL libc_round)(double x) {
#line 952 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUN
	return (double)__LIBM_MATHFUN(round, x);
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

#include <hybrid/typecore.h>

#include <libm/trunc.h>
/* Round X to the integral value in floating-point
 * format nearest but not larger in magnitude */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.trunc") double
NOTHROW(LIBCCALL libc_trunc)(double x) {
#line 976 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUN
	return __LIBM_MATHFUN(trunc, x);
#else /* __LIBM_MATHFUN */
	return (double)(__INTMAX_TYPE__)x;
#endif /* !__LIBM_MATHFUN */
}

#include <hybrid/typecore.h>

#include <libm/lrint.h>
/* Round X to nearest integral value according to current rounding direction */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lrint") long int
NOTHROW(LIBCCALL libc_lrint)(double x) {
#line 995 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(lrint, x);
#else /* __LIBM_MATHFUNI */
	return (long int)libc_rint(x);
#endif /* !__LIBM_MATHFUNI */
}

#include <hybrid/typecore.h>

#include <libm/lround.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.lround") long int
NOTHROW(LIBCCALL libc_lround)(double x) {
#line 1008 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(lround, x);
#else /* __LIBM_MATHFUNI */
	return (long int)libc_round(x);
#endif /* !__LIBM_MATHFUNI */
}

/* Return positive difference between X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fdim") double
NOTHROW(LIBCCALL libc_fdim)(double x,
                            double y) {
#line 1018 "kos/src/libc/magic/math.c"
	/* TODO: ieee754-specific function */
	return libc_fabs(y - x);
}

/* Return maximum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmax") double
NOTHROW(LIBCCALL libc_fmax)(double x,
                            double y) {
#line 1025 "kos/src/libc/magic/math.c"
	/* TODO: ieee754-specific function */
	return x < y ? y : x;
}

/* Return minimum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmin") double
NOTHROW(LIBCCALL libc_fmin)(double x,
                            double y) {
#line 1032 "kos/src/libc/magic/math.c"
	/* TODO: ieee754-specific function */
	return x < y ? x : y;
}

/* Multiply-add function computed as a ternary operation */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fma") double
NOTHROW(LIBCCALL libc_fma)(double x,
                           double y,
                           double z) {
#line 1039 "kos/src/libc/magic/math.c"
	/* TODO: ieee754-specific function */
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
#line 1050 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(llrint, x);
#else /* __LIBM_MATHFUNI */
	return (__LONGLONG)libc_rint(x);
#endif /* !__LIBM_MATHFUNI */
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
#line 1063 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(llround, x);
#else /* __LIBM_MATHFUNI */
	return (__LONGLONG)libc_round(x);
#endif /* !__LIBM_MATHFUNI */
}
#endif /* MAGIC:alias */

/* Return positive difference between X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fdimf") float
NOTHROW(LIBCCALL libc_fdimf)(float x,
                             float y) {
#line 1018 "kos/src/libc/magic/math.c"
	/* TODO: ieee754-specific function */
	return libc_fabs(y - x);
}

/* Return maximum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmaxf") float
NOTHROW(LIBCCALL libc_fmaxf)(float x,
                             float y) {
#line 1025 "kos/src/libc/magic/math.c"
	/* TODO: ieee754-specific function */
	return x < y ? y : x;
}

/* Return minimum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fminf") float
NOTHROW(LIBCCALL libc_fminf)(float x,
                             float y) {
#line 1032 "kos/src/libc/magic/math.c"
	/* TODO: ieee754-specific function */
	return x < y ? x : y;
}

/* Multiply-add function computed as a ternary operation */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmaf") float
NOTHROW(LIBCCALL libc_fmaf)(float x,
                            float y,
                            float z) {
#line 1039 "kos/src/libc/magic/math.c"
	/* TODO: ieee754-specific function */
	return (x * y) + z;
}

/* Return positive difference between X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fdiml") __LONGDOUBLE
NOTHROW(LIBCCALL libc_fdiml)(__LONGDOUBLE x,
                             __LONGDOUBLE y) {
#line 1018 "kos/src/libc/magic/math.c"
	/* TODO: ieee754-specific function */
	return libc_fabs(y - x);
}

/* Return maximum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmaxl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_fmaxl)(__LONGDOUBLE x,
                             __LONGDOUBLE y) {
#line 1025 "kos/src/libc/magic/math.c"
	/* TODO: ieee754-specific function */
	return x < y ? y : x;
}

/* Return minimum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fminl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_fminl)(__LONGDOUBLE x,
                             __LONGDOUBLE y) {
#line 1032 "kos/src/libc/magic/math.c"
	/* TODO: ieee754-specific function */
	return x < y ? x : y;
}

/* Multiply-add function computed as a ternary operation */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmal") __LONGDOUBLE
NOTHROW(LIBCCALL libc_fmal)(__LONGDOUBLE x,
                            __LONGDOUBLE y,
                            __LONGDOUBLE z) {
#line 1039 "kos/src/libc/magic/math.c"
	/* TODO: ieee754-specific function */
	return (x * y) + z;
}

#include <libm/signbit.h>
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.__signbit") int
NOTHROW(LIBCCALL libc___signbit)(double x) {
#line 2060 "kos/src/libc/magic/math.c"
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

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(ceil, libc_ceil);
DEFINE_PUBLIC_WEAK_ALIAS(__ceil, libc_ceil);
DEFINE_PUBLIC_WEAK_ALIAS(fabs, libc_fabs);
DEFINE_PUBLIC_WEAK_ALIAS(__fabs, libc_fabs);
DEFINE_PUBLIC_WEAK_ALIAS(floor, libc_floor);
DEFINE_PUBLIC_WEAK_ALIAS(__floor, libc_floor);
DEFINE_PUBLIC_WEAK_ALIAS(copysign, libc_copysign);
DEFINE_PUBLIC_WEAK_ALIAS(_copysign, libc_copysign);
DEFINE_PUBLIC_WEAK_ALIAS(__copysign, libc_copysign);
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
DEFINE_PUBLIC_WEAK_ALIAS(fdimf, libc_fdimf);
DEFINE_PUBLIC_WEAK_ALIAS(__fdimf, libc_fdimf);
DEFINE_PUBLIC_WEAK_ALIAS(fmaxf, libc_fmaxf);
DEFINE_PUBLIC_WEAK_ALIAS(__fmaxf, libc_fmaxf);
DEFINE_PUBLIC_WEAK_ALIAS(fminf, libc_fminf);
DEFINE_PUBLIC_WEAK_ALIAS(__fminf, libc_fminf);
DEFINE_PUBLIC_WEAK_ALIAS(fmaf, libc_fmaf);
DEFINE_PUBLIC_WEAK_ALIAS(__fmaf, libc_fmaf);
DEFINE_PUBLIC_WEAK_ALIAS(fdiml, libc_fdiml);
DEFINE_PUBLIC_WEAK_ALIAS(__fdiml, libc_fdiml);
DEFINE_PUBLIC_WEAK_ALIAS(fmaxl, libc_fmaxl);
DEFINE_PUBLIC_WEAK_ALIAS(__fmaxl, libc_fmaxl);
DEFINE_PUBLIC_WEAK_ALIAS(fminl, libc_fminl);
DEFINE_PUBLIC_WEAK_ALIAS(__fminl, libc_fminl);
DEFINE_PUBLIC_WEAK_ALIAS(fmal, libc_fmal);
DEFINE_PUBLIC_WEAK_ALIAS(__fmal, libc_fmal);
DEFINE_PUBLIC_WEAK_ALIAS(__signbit, libc___signbit);
DEFINE_PUBLIC_WEAK_ALIAS(_dsign, libc___signbit);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_MATH_C */
