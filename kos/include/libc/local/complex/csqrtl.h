/* HASH CRC-32:0x6356eced */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_csqrtl_defined
#define __local_csqrtl_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__CRT_HAVE_csqrt) || ((defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_cabs) || defined(__CRT_HAVE__cabs) || defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___signbitl_defined
#define __local___localdep___signbitl_defined
#ifdef __CRT_HAVE___signbitl
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___signbitl,(__LONGDOUBLE __x),__signbitl,(__x))
#elif defined(__CRT_HAVE__ldsign)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___signbitl,(__LONGDOUBLE __x),_ldsign,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/__signbitl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep___signbitl __LIBC_LOCAL_NAME(__signbitl)
#endif /* !... */
#endif /* !__local___localdep___signbitl_defined */
#ifndef __local___localdep_cabsl_defined
#define __local___localdep_cabsl_defined
#ifdef __CRT_HAVE_cabsl
__CREDIRECT(,__LONGDOUBLE,__NOTHROW_NCX,__localdep_cabsl,(long double _Complex __z),cabsl,(__z))
#elif defined(__CRT_HAVE_cabs) || defined(__CRT_HAVE__cabs) || defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/complex/cabsl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_cabsl __LIBC_LOCAL_NAME(cabsl)
#else /* ... */
#undef __local___localdep_cabsl_defined
#endif /* !... */
#endif /* !__local___localdep_cabsl_defined */
#ifndef __local___localdep_cimagl_defined
#define __local___localdep_cimagl_defined
#ifdef __CRT_HAVE_cimagl
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW_NCX,__localdep_cimagl,(long double _Complex __z),cimagl,(__z))
#else /* __CRT_HAVE_cimagl */
__NAMESPACE_LOCAL_END
#include <libc/local/complex/cimagl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_cimagl __LIBC_LOCAL_NAME(cimagl)
#endif /* !__CRT_HAVE_cimagl */
#endif /* !__local___localdep_cimagl_defined */
#ifndef __local___localdep_copysignl_defined
#define __local___localdep_copysignl_defined
#if __has_builtin(__builtin_copysignl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysignl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_copysignl,(__LONGDOUBLE __num, __LONGDOUBLE __sign),copysignl,{ return __builtin_copysignl(__num, __sign); })
#elif defined(__CRT_HAVE_copysignl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_copysignl,(__LONGDOUBLE __num, __LONGDOUBLE __sign),copysignl,(__num,__sign))
#elif defined(__CRT_HAVE___copysignl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_copysignl,(__LONGDOUBLE __num, __LONGDOUBLE __sign),__copysignl,(__num,__sign))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/copysignl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_copysignl __LIBC_LOCAL_NAME(copysignl)
#endif /* !... */
#endif /* !__local___localdep_copysignl_defined */
#ifndef __local___localdep_creall_defined
#define __local___localdep_creall_defined
#ifdef __CRT_HAVE_creall
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW_NCX,__localdep_creall,(long double _Complex __z),creall,(__z))
#else /* __CRT_HAVE_creall */
__NAMESPACE_LOCAL_END
#include <libc/local/complex/creall.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_creall __LIBC_LOCAL_NAME(creall)
#endif /* !__CRT_HAVE_creall */
#endif /* !__local___localdep_creall_defined */
#ifndef __local___localdep_csqrt_defined
#define __local___localdep_csqrt_defined
#ifdef __CRT_HAVE_csqrt
__CREDIRECT(__ATTR_WUNUSED,double _Complex,__NOTHROW_NCX,__localdep_csqrt,(double _Complex __z),csqrt,(__z))
#elif (defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_cabs) || defined(__CRT_HAVE__cabs) || defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))
__NAMESPACE_LOCAL_END
#include <libc/local/complex/csqrt.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_csqrt __LIBC_LOCAL_NAME(csqrt)
#else /* ... */
#undef __local___localdep_csqrt_defined
#endif /* !... */
#endif /* !__local___localdep_csqrt_defined */
#ifndef __local___localdep_fabsl_defined
#define __local___localdep_fabsl_defined
#if __has_builtin(__builtin_fabsl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_fabsl,(__LONGDOUBLE __x),fabsl,{ return __builtin_fabsl(__x); })
#elif defined(__CRT_HAVE_fabsl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_fabsl,(__LONGDOUBLE __x),fabsl,(__x))
#elif defined(__CRT_HAVE___fabsl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_fabsl,(__LONGDOUBLE __x),__fabsl,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/fabsl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fabsl __LIBC_LOCAL_NAME(fabsl)
#endif /* !... */
#endif /* !__local___localdep_fabsl_defined */
#ifndef __local___localdep_hypotl_defined
#define __local___localdep_hypotl_defined
#if __has_builtin(__builtin_hypotl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_hypotl)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_hypotl,(__LONGDOUBLE __x, __LONGDOUBLE __y),hypotl,{ return __builtin_hypotl(__x, __y); })
#elif defined(__CRT_HAVE_hypotl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_hypotl,(__LONGDOUBLE __x, __LONGDOUBLE __y),hypotl,(__x,__y))
#elif defined(__CRT_HAVE___hypotl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_hypotl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__hypotl,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/hypotl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_hypotl __LIBC_LOCAL_NAME(hypotl)
#else /* ... */
#undef __local___localdep_hypotl_defined
#endif /* !... */
#endif /* !__local___localdep_hypotl_defined */
#ifndef __local___localdep_isinfl_defined
#define __local___localdep_isinfl_defined
#if __has_builtin(__builtin_isinfl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinfl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinfl,(__LONGDOUBLE __x),isinfl,{ return __builtin_isinfl(__x); })
#elif defined(__CRT_HAVE_isinfl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinfl,(__LONGDOUBLE __x),isinfl,(__x))
#elif defined(__CRT_HAVE___isinfl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinfl,(__LONGDOUBLE __x),__isinfl,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <bits/math-constants.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__INFINITYL) || defined(__HUGE_VALL) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)
__NAMESPACE_LOCAL_END
#include <libc/local/math/isinfl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isinfl __LIBC_LOCAL_NAME(isinfl)
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __INFINITYL || __HUGE_VALL || __CRT_HAVE_isinf || __CRT_HAVE___isinf || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __INFINITY || __HUGE_VAL */
#undef __local___localdep_isinfl_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__INFINITYL && !__HUGE_VALL && !__CRT_HAVE_isinf && !__CRT_HAVE___isinf && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && !__INFINITY && !__HUGE_VAL */
#endif /* !... */
#endif /* !__local___localdep_isinfl_defined */
#ifndef __local___localdep_isnanl_defined
#define __local___localdep_isnanl_defined
#if __has_builtin(__builtin_isnanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnanl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanl,(__LONGDOUBLE __x),isnanl,{ return __builtin_isnanl(__x); })
#elif defined(__CRT_HAVE_isnanl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanl,(__LONGDOUBLE __x),isnanl,(__x))
#elif defined(__CRT_HAVE___isnanl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanl,(__LONGDOUBLE __x),__isnanl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/isnanl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isnanl __LIBC_LOCAL_NAME(isnanl)
#else /* ... */
#undef __local___localdep_isnanl_defined
#endif /* !... */
#endif /* !__local___localdep_isnanl_defined */
#ifndef __local___localdep_sqrtl_defined
#define __local___localdep_sqrtl_defined
#if __has_builtin(__builtin_sqrtl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sqrtl)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_sqrtl,(__LONGDOUBLE __x),sqrtl,{ return __builtin_sqrtl(__x); })
#elif defined(__CRT_HAVE_sqrtl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_sqrtl,(__LONGDOUBLE __x),sqrtl,(__x))
#elif defined(__CRT_HAVE___sqrtl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_sqrtl,(__LONGDOUBLE __x),__sqrtl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/sqrtl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sqrtl __LIBC_LOCAL_NAME(sqrtl)
#else /* ... */
#undef __local___localdep_sqrtl_defined
#endif /* !... */
#endif /* !__local___localdep_sqrtl_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/floatcore.h>
#include <bits/math-constants.h>
#include <bits/crt/complex.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(csqrtl) __ATTR_WUNUSED long double _Complex
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(csqrtl))(long double _Complex __z) {
#if (defined(__CRT_HAVE_sqrtl) || defined(__CRT_HAVE___sqrtl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_cabsl) || defined(__CRT_HAVE_cabs) || defined(__CRT_HAVE__cabs) || defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))
	/* Implementation derived from NetBSD. -- See the following copyright notice. */
	/*-
	 * Copyright (c) 2007 The NetBSD Foundation, Inc.
	 * All rights reserved.
	 *
	 * This code is derived from software written by Stephen L. Moshier.
	 * It is redistributed by the NetBSD Foundation by permission of the author.
	 *
	 * Redistribution and use in source and binary forms, with or without
	 * modification, are permitted provided that the following conditions
	 * are met:
	 * 1. Redistributions of source code must retain the above copyright
	 *    notice, this list of conditions and the following disclaimer.
	 * 2. Redistributions in binary form must reproduce the above copyright
	 *    notice, this list of conditions and the following disclaimer in the
	 *    documentation and/or other materials provided with the distribution.
	 *
	 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
	 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
	 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
	 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
	 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
	 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	 * POSSIBILITY OF SUCH DAMAGE.
	 */

	long double _Complex __result;
	__LONGDOUBLE __a, __b;
	__LONGDOUBLE __t;
	__BOOL __scale;
	__a = (__NAMESPACE_LOCAL_SYM __localdep_creall)(__z);
	__b = (__NAMESPACE_LOCAL_SYM __localdep_cimagl)(__z);

	/* Handle special cases. */
	if (__z == 0.0L)
		return __CMPLXL(0.0L, __b);
	if ((__NAMESPACE_LOCAL_SYM __localdep_isinfl)(__b))
		return __CMPLXL(__INFINITYL, __b);
	if ((__NAMESPACE_LOCAL_SYM __localdep_isnanl)(__a)) {
		__t = (__b - __b) / (__b - __b); /* raise invalid if b is not a NaN */
		return __CMPLXL(__a, __t);    /* return NaN + NaN i */
	}
	if ((__NAMESPACE_LOCAL_SYM __localdep_isinfl)(__a)) {
		/* csqrt(inf + NaN i)  = inf +  NaN i
		 * csqrt(inf + y i)    = inf +  0 i
		 * csqrt(-inf + NaN i) = NaN +- inf i
		 * csqrt(-inf + y i)   = 0   +  inf i */
		if ((__NAMESPACE_LOCAL_SYM __localdep___signbitl)(__a)) {
			return __CMPLXL((__NAMESPACE_LOCAL_SYM __localdep_fabsl)(__b - __b), (__NAMESPACE_LOCAL_SYM __localdep_copysignl)(__a, __b));
		} else {
			return __CMPLXL(__a, (__NAMESPACE_LOCAL_SYM __localdep_copysignl)(__b - __b, __b));
		}
	}

	/* The remaining special case (b is NaN) is handled just fine by
	 * the normal code path below. */

	/* Scale to avoid overflow. */
	if ((__NAMESPACE_LOCAL_SYM __localdep_fabsl)(__a) >= (__LDBL_MAX__ / 2.414213562373095048801688724209698L) ||
	    (__NAMESPACE_LOCAL_SYM __localdep_fabsl)(__b) >= (__LDBL_MAX__ / 2.414213562373095048801688724209698L)) {
		__a *= 0.25L;
		__b *= 0.25L;
		__scale = 1;
	} else {
		__scale = 0;
	}

	/* Algorithm 312, CACM vol 10, Oct 1967. */
	if (__a >= 0) {
		__t      = (__NAMESPACE_LOCAL_SYM __localdep_sqrtl)((__a + (__NAMESPACE_LOCAL_SYM __localdep_hypotl)(__a, __b)) * 0.5L);
		__result = __CMPLXL(__t, (__b / (2.0L * __t)));
	} else {
		__t      = (__NAMESPACE_LOCAL_SYM __localdep_sqrtl)((-__a + (__NAMESPACE_LOCAL_SYM __localdep_hypotl)(__a, __b)) * 0.5L);
		__result = __CMPLXL((__NAMESPACE_LOCAL_SYM __localdep_fabsl)(__b) / (2.0L * __t), (__NAMESPACE_LOCAL_SYM __localdep_copysignl)(__t, __b));
	}
	/* Rescale. */
	if (__scale) {
		return (__result * 2.0L);
	} else {
		return (__result);
	}





































































#else /* (__CRT_HAVE_sqrtl || __CRT_HAVE___sqrtl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_sqrt || __CRT_HAVE___sqrt || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_cabsl || __CRT_HAVE_cabs || __CRT_HAVE__cabs || __CRT_HAVE_hypot || __CRT_HAVE___hypot || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) */
	return (long double _Complex)(__NAMESPACE_LOCAL_SYM __localdep_csqrt)((double _Complex)__z);
#endif /* (!__CRT_HAVE_sqrtl && !__CRT_HAVE___sqrtl && !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__CRT_HAVE_sqrt && !__CRT_HAVE___sqrt && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_cabsl && !__CRT_HAVE_cabs && !__CRT_HAVE__cabs && !__CRT_HAVE_hypot && !__CRT_HAVE___hypot && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_csqrtl_defined
#define __local___localdep_csqrtl_defined
#define __localdep_csqrtl __LIBC_LOCAL_NAME(csqrtl)
#endif /* !__local___localdep_csqrtl_defined */
#else /* __CRT_HAVE_csqrt || ((__CRT_HAVE_sqrt || __CRT_HAVE___sqrt || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_cabs || __CRT_HAVE__cabs || __CRT_HAVE_hypot || __CRT_HAVE___hypot || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) */
#undef __local_csqrtl_defined
#endif /* !__CRT_HAVE_csqrt && ((!__CRT_HAVE_sqrt && !__CRT_HAVE___sqrt && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_cabs && !__CRT_HAVE__cabs && !__CRT_HAVE_hypot && !__CRT_HAVE___hypot && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) */
#endif /* !__local_csqrtl_defined */
