/* HASH CRC-32:0xe6974c80 */
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
#line 826 "kos/src/libc/magic/math.c"
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

#include <hybrid/typecore.h>

#include <libm/floor.h>
/* Largest integer not greater than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.floor") double
NOTHROW(LIBCCALL libc_floor)(double x) {
#line 861 "kos/src/libc/magic/math.c"
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
#line 900 "kos/src/libc/magic/math.c"
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

#include <hybrid/typecore.h>

#include <libm/floor.h>
/* Largest integer not greater than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.floorf") float
NOTHROW(LIBCCALL libc_floorf)(float x) {
#line 933 "kos/src/libc/magic/math.c"
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
#line 969 "kos/src/libc/magic/math.c"
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

#include <hybrid/typecore.h>

#include <libm/floor.h>
/* Largest integer not greater than X */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.floorl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_floorl)(__LONGDOUBLE x) {
#line 1002 "kos/src/libc/magic/math.c"
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

#include <bits/nan.h>
/* Return representation of qNaN for double type */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.nan") double
NOTHROW(LIBCCALL libc_nan)(char const *tagb) {
#line 1059 "kos/src/libc/magic/math.c"
	(void)tagb;
	return (double)NAN;
}

#include <bits/nan.h>
/* Return representation of qNaN for double type */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.nanf") float
NOTHROW(LIBCCALL libc_nanf)(char const *tagb) {
#line 1059 "kos/src/libc/magic/math.c"
	(void)tagb;
	return (float)NAN;
}

#include <bits/nan.h>
/* Return representation of qNaN for double type */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.nanl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_nanl)(char const *tagb) {
#line 1059 "kos/src/libc/magic/math.c"
	(void)tagb;
	return (__LONGDOUBLE)NAN;
}

/* Return maximum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmax") double
NOTHROW(LIBCCALL libc_fmax)(double x,
                            double y) {
#line 1461 "kos/src/libc/magic/math.c"
	return x < y ? y : x;
}

/* Return minimum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmin") double
NOTHROW(LIBCCALL libc_fmin)(double x,
                            double y) {
#line 1467 "kos/src/libc/magic/math.c"
	return x < y ? x : y;
}

/* Multiply-add function computed as a ternary operation */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fma") double
NOTHROW(LIBCCALL libc_fma)(double x,
                           double y,
                           double z) {
#line 1473 "kos/src/libc/magic/math.c"
	return (x * y) + z;
}

/* Return maximum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmaxf") float
NOTHROW(LIBCCALL libc_fmaxf)(float x,
                             float y) {
#line 1461 "kos/src/libc/magic/math.c"
	return x < y ? y : x;
}

/* Return minimum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fminf") float
NOTHROW(LIBCCALL libc_fminf)(float x,
                             float y) {
#line 1467 "kos/src/libc/magic/math.c"
	return x < y ? x : y;
}

/* Multiply-add function computed as a ternary operation */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmaf") float
NOTHROW(LIBCCALL libc_fmaf)(float x,
                            float y,
                            float z) {
#line 1473 "kos/src/libc/magic/math.c"
	return (x * y) + z;
}

/* Return maximum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmaxl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_fmaxl)(__LONGDOUBLE x,
                             __LONGDOUBLE y) {
#line 1461 "kos/src/libc/magic/math.c"
	return x < y ? y : x;
}

/* Return minimum numeric value from X and Y */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fminl") __LONGDOUBLE
NOTHROW(LIBCCALL libc_fminl)(__LONGDOUBLE x,
                             __LONGDOUBLE y) {
#line 1467 "kos/src/libc/magic/math.c"
	return x < y ? x : y;
}

/* Multiply-add function computed as a ternary operation */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.math.fmal") __LONGDOUBLE
NOTHROW(LIBCCALL libc_fmal)(__LONGDOUBLE x,
                            __LONGDOUBLE y,
                            __LONGDOUBLE z) {
#line 1473 "kos/src/libc/magic/math.c"
	return (x * y) + z;
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
DEFINE_PUBLIC_WEAK_ALIAS(fmax, libc_fmax);
DEFINE_PUBLIC_WEAK_ALIAS(__fmax, libc_fmax);
DEFINE_PUBLIC_WEAK_ALIAS(fmin, libc_fmin);
DEFINE_PUBLIC_WEAK_ALIAS(__fmin, libc_fmin);
DEFINE_PUBLIC_WEAK_ALIAS(fma, libc_fma);
DEFINE_PUBLIC_WEAK_ALIAS(__fma, libc_fma);
DEFINE_PUBLIC_WEAK_ALIAS(fmaxf, libc_fmaxf);
DEFINE_PUBLIC_WEAK_ALIAS(__fmaxf, libc_fmaxf);
DEFINE_PUBLIC_WEAK_ALIAS(fminf, libc_fminf);
DEFINE_PUBLIC_WEAK_ALIAS(__fminf, libc_fminf);
DEFINE_PUBLIC_WEAK_ALIAS(fmaf, libc_fmaf);
DEFINE_PUBLIC_WEAK_ALIAS(__fmaf, libc_fmaf);
DEFINE_PUBLIC_WEAK_ALIAS(fmaxl, libc_fmaxl);
DEFINE_PUBLIC_WEAK_ALIAS(__fmaxl, libc_fmaxl);
DEFINE_PUBLIC_WEAK_ALIAS(fminl, libc_fminl);
DEFINE_PUBLIC_WEAK_ALIAS(__fminl, libc_fminl);
DEFINE_PUBLIC_WEAK_ALIAS(fmal, libc_fmal);
DEFINE_PUBLIC_WEAK_ALIAS(__fmal, libc_fmal);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_MATH_C */
