/* HASH CRC-32:0x17b414c8 */
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
#ifndef __local_ldexpl_defined
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_ldexp) || defined(__CRT_HAVE___ldexp)
#define __local_ldexpl_defined 1
#include <parts/errno.h>

#include <libm/finite.h>

#include <libm/ldexp.h>
/* Dependency: "ldexp" from "math" */
#ifndef ____localdep_ldexp_defined
#define ____localdep_ldexp_defined 1
#if __has_builtin(__builtin_ldexp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ldexp)
/* X times (two to the EXP power) */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_ldexp,(double __x, int __exponent),ldexp,{ return __builtin_ldexp(__x, __exponent); })
#elif defined(__CRT_HAVE_ldexp)
/* X times (two to the EXP power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_ldexp,(double __x, int __exponent),ldexp,(__x,__exponent))
#elif defined(__CRT_HAVE___ldexp)
/* X times (two to the EXP power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_ldexp,(double __x, int __exponent),__ldexp,(__x,__exponent))
#else /* LIBC: ldexp */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/ldexp.h>
/* X times (two to the EXP power) */
#define __localdep_ldexp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ldexp))
#else /* CUSTOM: ldexp */
#undef ____localdep_ldexp_defined
#endif /* ldexp... */
#endif /* ldexp... */
#endif /* !____localdep_ldexp_defined */

__NAMESPACE_LOCAL_BEGIN
/* X times (two to the EXP power) */
__LOCAL_LIBC(ldexpl) __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(ldexpl))(__LONGDOUBLE __x,
                                                int __exponent) {
#line 412 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUN2L
	__LONGDOUBLE __result;
#ifdef __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__
	__result = (__LONGDOUBLE)__ieee754_ldexp((__IEEE754_DOUBLE_TYPE__)__x, __exponent);
	if __unlikely(!__ieee754_finite((__IEEE754_DOUBLE_TYPE__)__result) || __result == 0.0L)
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	__result = (__LONGDOUBLE)__ieee754_ldexpf((__IEEE754_FLOAT_TYPE__)__x, __exponent);
	if __unlikely(!__ieee754_finitef((__IEEE754_FLOAT_TYPE__)__result) || __result == 0.0L)
#else /* ... */
	__result = (__LONGDOUBLE)__ieee854_ldexpl((__IEEE854_LONG_DOUBLE_TYPE__)__x, __exponent);
	if __unlikely(!__ieee854_finitel((__IEEE854_LONG_DOUBLE_TYPE__)__result) || __result == 0.0L)
#endif /* !... */
	{
#ifdef __ERANGE
		__libc_seterrno(__ERANGE);
#endif /* __ERANGE */
	}
	return __result;
#else /* __LIBM_MATHFUN2L */
	return (__LONGDOUBLE)__localdep_ldexp((double)__x, __exponent);
#endif /* !__LIBM_MATHFUN2L */
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __CRT_HAVE_ldexp || __CRT_HAVE___ldexp */
#endif /* !__local_ldexpl_defined */
