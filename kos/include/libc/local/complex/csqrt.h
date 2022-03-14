/* HASH CRC-32:0x937c8245 */
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
#ifndef __local_csqrt_defined
#define __local_csqrt_defined
#include <__crt.h>
#include <ieee754.h>
#if (defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_cabs) || defined(__CRT_HAVE__cabs) || defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE__hypot) || defined(__CRT_HAVE___hypot) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___signbit_defined
#define __local___localdep___signbit_defined
#ifdef __CRT_HAVE___signbit
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___signbit,(double __x),__signbit,(__x))
#elif defined(__CRT_HAVE__dsign)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___signbit,(double __x),_dsign,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/__signbit.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep___signbit __LIBC_LOCAL_NAME(__signbit)
#endif /* !... */
#endif /* !__local___localdep___signbit_defined */
#ifndef __local___localdep_cabs_defined
#define __local___localdep_cabs_defined
#ifdef __CRT_HAVE_cabs
__CREDIRECT(,double,__NOTHROW_NCX,__localdep_cabs,(double _Complex __z),cabs,(__z))
#elif defined(__CRT_HAVE__cabs)
__CREDIRECT(,double,__NOTHROW_NCX,__localdep_cabs,(double _Complex __z),_cabs,(__z))
#elif defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE__hypot) || defined(__CRT_HAVE___hypot) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/complex/cabs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_cabs __LIBC_LOCAL_NAME(cabs)
#else /* ... */
#undef __local___localdep_cabs_defined
#endif /* !... */
#endif /* !__local___localdep_cabs_defined */
#ifndef __local___localdep_cimag_defined
#define __local___localdep_cimag_defined
#ifdef __CRT_HAVE_cimag
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,__localdep_cimag,(double _Complex __z),cimag,(__z))
#else /* __CRT_HAVE_cimag */
__NAMESPACE_LOCAL_END
#include <libc/local/complex/cimag.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_cimag __LIBC_LOCAL_NAME(cimag)
#endif /* !__CRT_HAVE_cimag */
#endif /* !__local___localdep_cimag_defined */
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
#ifndef __local___localdep_copysign_defined
#define __local___localdep_copysign_defined
#if __has_builtin(__builtin_copysign) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysign)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_copysign,(double __num, double __sign),copysign,{ return __builtin_copysign(__num, __sign); })
#elif defined(__CRT_HAVE_copysign)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_copysign,(double __num, double __sign),copysign,(__num,__sign))
#elif defined(__CRT_HAVE___copysign)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_copysign,(double __num, double __sign),__copysign,(__num,__sign))
#elif defined(__CRT_HAVE__copysign)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_copysign,(double __num, double __sign),_copysign,(__num,__sign))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/copysign.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_copysign __LIBC_LOCAL_NAME(copysign)
#endif /* !... */
#endif /* !__local___localdep_copysign_defined */
#ifndef __local___localdep_creal_defined
#define __local___localdep_creal_defined
#ifdef __CRT_HAVE_creal
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,__localdep_creal,(double _Complex __z),creal,(__z))
#else /* __CRT_HAVE_creal */
__NAMESPACE_LOCAL_END
#include <libc/local/complex/creal.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_creal __LIBC_LOCAL_NAME(creal)
#endif /* !__CRT_HAVE_creal */
#endif /* !__local___localdep_creal_defined */
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
#ifndef __local___localdep_fabs_defined
#define __local___localdep_fabs_defined
#if __has_builtin(__builtin_fabs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabs)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_fabs,(double __x),fabs,{ return __builtin_fabs(__x); })
#elif defined(__CRT_HAVE_fabs)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_fabs,(double __x),fabs,(__x))
#elif defined(__CRT_HAVE___fabs)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_fabs,(double __x),__fabs,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/fabs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fabs __LIBC_LOCAL_NAME(fabs)
#endif /* !... */
#endif /* !__local___localdep_fabs_defined */
#ifndef __local___localdep_hypot_defined
#define __local___localdep_hypot_defined
#if __has_builtin(__builtin_hypot) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_hypot)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_hypot,(double __x, double __y),hypot,{ return __builtin_hypot(__x, __y); })
#elif defined(__CRT_HAVE_hypot)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_hypot,(double __x, double __y),hypot,(__x,__y))
#elif defined(__CRT_HAVE__hypot)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_hypot,(double __x, double __y),_hypot,(__x,__y))
#elif defined(__CRT_HAVE___hypot)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_hypot,(double __x, double __y),__hypot,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/hypot.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_hypot __LIBC_LOCAL_NAME(hypot)
#else /* ... */
#undef __local___localdep_hypot_defined
#endif /* !... */
#endif /* !__local___localdep_hypot_defined */
#ifndef __local___localdep_isinf_defined
#define __local___localdep_isinf_defined
#if __has_builtin(__builtin_isinf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinf)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinf,(double __x),isinf,{ return __builtin_isinf(__x); })
#elif defined(__CRT_HAVE_isinf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinf,(double __x),isinf,(__x))
#elif defined(__CRT_HAVE___isinf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinf,(double __x),__isinf,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <bits/math-constants.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)
__NAMESPACE_LOCAL_END
#include <libc/local/math/isinf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isinf __LIBC_LOCAL_NAME(isinf)
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __INFINITY || __HUGE_VAL */
#undef __local___localdep_isinf_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && !__INFINITY && !__HUGE_VAL */
#endif /* !... */
#endif /* !__local___localdep_isinf_defined */
#ifndef __local___localdep_isnan_defined
#define __local___localdep_isnan_defined
#if __has_builtin(__builtin_isnan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnan)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnan,(double __x),isnan,{ return __builtin_isnan(__x); })
#elif defined(__CRT_HAVE_isnan)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnan,(double __x),isnan,(__x))
#elif defined(__CRT_HAVE__isnan)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnan,(double __x),_isnan,(__x))
#elif defined(__CRT_HAVE___isnan)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnan,(double __x),__isnan,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/isnan.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isnan __LIBC_LOCAL_NAME(isnan)
#else /* ... */
#undef __local___localdep_isnan_defined
#endif /* !... */
#endif /* !__local___localdep_isnan_defined */
#ifndef __local___localdep_sqrt_defined
#define __local___localdep_sqrt_defined
#if __has_builtin(__builtin_sqrt) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sqrt)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_sqrt,(double __x),sqrt,{ return __builtin_sqrt(__x); })
#elif defined(__CRT_HAVE_sqrt)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_sqrt,(double __x),sqrt,(__x))
#elif defined(__CRT_HAVE___sqrt)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_sqrt,(double __x),__sqrt,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/sqrt.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sqrt __LIBC_LOCAL_NAME(sqrt)
#else /* ... */
#undef __local___localdep_sqrt_defined
#endif /* !... */
#endif /* !__local___localdep_sqrt_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/floatcore.h>
#include <bits/math-constants.h>
#include <bits/crt/complex.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(csqrt) __ATTR_WUNUSED double _Complex
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(csqrt))(double _Complex __z) {
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

























































	double _Complex __w;
	double __x, __y, __r, __t, __scale;
	__x = (__NAMESPACE_LOCAL_SYM __localdep_creal)(__z);
	__y = (__NAMESPACE_LOCAL_SYM __localdep_cimag)(__z);
	/* input is a real number and imaginary part isn't -0.0.
	 * negative zero is on the branch cut. */
	if ((__y == 0.0) && !(__NAMESPACE_LOCAL_SYM __localdep___signbit)(__y)) {
		if (__x == 0.0) {
			__w = __CMPLX(0.0, __y);
		} else {
			if (__x < 0.0) {
				__r = (__NAMESPACE_LOCAL_SYM __localdep_sqrt)(-__x);
				__w = __CMPLX(0.0, __r);
			} else {
				__r = (__NAMESPACE_LOCAL_SYM __localdep_sqrt)(__x);
				__w = __r;
			}
		}
		return __w;
	}
	if (__x == 0.0) {
		if (__y > 0) {
			__r = (__NAMESPACE_LOCAL_SYM __localdep_sqrt)(0.5 * __y);
			__w = __CMPLX(__r, __r);
		} else {
			__r = (__NAMESPACE_LOCAL_SYM __localdep_sqrt)(-0.5 * __y);
			__w = __CMPLX(__r, -__r);
		}
		return __w;
	}
	/* Rescale to avoid internal overflow or underflow.  */
	if (((__NAMESPACE_LOCAL_SYM __localdep_fabs)(__x) > 4.0) || ((__NAMESPACE_LOCAL_SYM __localdep_fabs)(__y) > 4.0)) {
		__x *= 0.25;
		__y *= 0.25;
		__scale = 2.0;
	} else {





		__x *= 1.8014398509481984e16;  /* 2^54 */
		__y *= 1.8014398509481984e16;
		__scale = 7.450580596923828125e-9; /* 2^-27 */





	}
	__w = __CMPLX(__x, __y);
	__r = (__NAMESPACE_LOCAL_SYM __localdep_cabs)(__w);
	if (__x > 0) {
		__t = (__NAMESPACE_LOCAL_SYM __localdep_sqrt)(0.5 * __r + 0.5 * __x);
		__r = __scale * (__NAMESPACE_LOCAL_SYM __localdep_fabs)((0.5 * __y) / __t );
		__t *= __scale;
	} else {
		__r = (__NAMESPACE_LOCAL_SYM __localdep_sqrt)(0.5 * __r - 0.5 * __x);
		__t = __scale * (__NAMESPACE_LOCAL_SYM __localdep_fabs)((0.5 * __y) / __r);
		__r *= __scale;
	}
	if (__y > 0) {
		__w = __CMPLX(__t, __r);
	} else {
		__w = __CMPLX(__t, -__r);
	}
	return __w;

}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_csqrt_defined
#define __local___localdep_csqrt_defined
#define __localdep_csqrt __LIBC_LOCAL_NAME(csqrt)
#endif /* !__local___localdep_csqrt_defined */
#else /* (__CRT_HAVE_sqrt || __CRT_HAVE___sqrt || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_cabs || __CRT_HAVE__cabs || __CRT_HAVE_hypot || __CRT_HAVE__hypot || __CRT_HAVE___hypot || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) */
#undef __local_csqrt_defined
#endif /* (!__CRT_HAVE_sqrt && !__CRT_HAVE___sqrt && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_cabs && !__CRT_HAVE__cabs && !__CRT_HAVE_hypot && !__CRT_HAVE__hypot && !__CRT_HAVE___hypot && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) */
#endif /* !__local_csqrt_defined */
