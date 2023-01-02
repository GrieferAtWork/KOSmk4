/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_MATH_CONSTANTS_H
#define _BITS_MATH_CONSTANTS_H 1

#include <__stdinc.h>
#ifdef __CC__
#include <__crt.h> /* __NO_FPU */
#ifndef __NO_FPU

#if __has_builtin(__builtin_huge_val)
#define __HUGE_VAL __builtin_huge_val()
#else /* __has_builtin(__builtin_huge_val) */
#include <libm/inf.h>
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
#define __HUGE_VAL __ieee754_inf()
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
#define __HUGE_VAL __ieee754_inff()
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#define __HUGE_VAL __ieee854_infl()
#endif /* !... */
#endif /* !__has_builtin(__builtin_huge_val) */

#if __has_builtin(__builtin_huge_valf)
#define __HUGE_VALF __builtin_huge_valf()
#else /* __has_builtin(__builtin_huge_valf) */
#include <libm/inf.h>
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
#define __HUGE_VALF __ieee754_inff()
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
#define __HUGE_VALF __ieee754_inf()
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
#define __HUGE_VALF __ieee854_infl()
#endif /* !... */
#endif /* !__has_builtin(__builtin_huge_valf) */

#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_huge_vall)
#define __HUGE_VALL __builtin_huge_vall()
#else /* __has_builtin(__builtin_huge_vall) */
#include <libm/inf.h>
#ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__
#define __HUGE_VALL __ieee854_infl()
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
#define __HUGE_VALL __ieee754_inf()
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
#define __HUGE_VALL __ieee754_inff()
#endif /* !... */
#endif /* !__has_builtin(__builtin_huge_vall) */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#if __has_builtin(__builtin_inff)
#define __INFINITYF __builtin_inff()
#else /* __has_builtin(__builtin_inff) */
#include <libm/inf.h>
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
#define __INFINITYF __ieee754_inff()
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
#define __INFINITYF __ieee754_inf()
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
#define __INFINITYF __ieee854_infl()
#endif /* !... */
#endif /* !__has_builtin(__builtin_inff) */

#if __has_builtin(__builtin_inf)
#define __INFINITY __builtin_inf()
#else /* __has_builtin(__builtin_inf) */
#include <libm/inf.h>
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
#define __INFINITY __ieee754_inf()
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
#define __INFINITY __ieee754_inff()
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#define __INFINITY __ieee854_infl()
#endif /* !... */
#endif /* !__has_builtin(__builtin_inf) */

#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_infl)
#define __INFINITYL __builtin_infl()
#else /* __has_builtin(__builtin_infl) */
#include <libm/inf.h>
#ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__
#define __INFINITYL __ieee854_infl()
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
#define __INFINITYL __ieee754_inf()
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
#define __INFINITYL __ieee754_inff()
#endif /* !... */
#endif /* !__has_builtin(__builtin_infl) */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#if __has_builtin(__builtin_nanf)
#define __NANF __builtin_nanf("")
#else /* __has_builtin(__builtin_nanf) */
#include <libm/nan.h>
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
#define __NANF __ieee754_nanf("")
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
#define __NANF __ieee754_nan("")
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
#define __NANF __ieee854_nanl("")
#endif /* !... */
#endif /* !__has_builtin(__builtin_nanf) */

#if __has_builtin(__builtin_nan)
#define __NAN __builtin_nan("")
#else /* __has_builtin(__builtin_nan) */
#include <libm/nan.h>
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
#define __NAN __ieee754_nan("")
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
#define __NAN __ieee754_nanf("")
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#define __NAN __ieee854_nanl("")
#endif /* !... */
#endif /* !__has_builtin(__builtin_nan) */

#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_nanl)
#define __NANL __builtin_nanl("")
#else /* __has_builtin(__builtin_nanl) */
#include <libm/nan.h>
#ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__
#define __NANL __ieee854_nanl("")
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
#define __NANL __ieee754_nan("")
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
#define __NANL __ieee754_nanf("")
#endif /* !... */
#endif /* !__has_builtin(__builtin_nanl) */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#if __has_builtin(__builtin_nansf)
#define __SNANF __builtin_nansf("")
#else /* __has_builtin(__builtin_nansf) */
/* TODO */
#endif /* !__has_builtin(__builtin_nansf) */

#if __has_builtin(__builtin_nans)
#define __SNAN __builtin_nans("")
#else /* __has_builtin(__builtin_nans) */
/* TODO */
#endif /* !__has_builtin(__builtin_nans) */

#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_nansl)
#define __SNANL __builtin_nansl("")
#else /* __has_builtin(__builtin_nansl) */
/* TODO */
#endif /* !__has_builtin(__builtin_nansl) */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#endif /* !__NO_FPU */
#endif /* __CC__ */

#endif /* !_BITS_MATH_CONSTANTS_H */
