/* HASH CRC-32:0xfb0816c1 */
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
#ifndef __local_csqrtf_defined
#define __local_csqrtf_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__CRT_HAVE_csqrt) || ((defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_cabs) || defined(__CRT_HAVE__cabs) || defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE__hypot) || defined(__CRT_HAVE___hypot) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___signbitf_defined
#define __local___localdep___signbitf_defined
#ifdef __CRT_HAVE___signbitf
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___signbitf,(float __x),__signbitf,(__x))
#elif defined(__CRT_HAVE__fdsign)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___signbitf,(float __x),_fdsign,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/__signbitf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep___signbitf __LIBC_LOCAL_NAME(__signbitf)
#endif /* !... */
#endif /* !__local___localdep___signbitf_defined */
#ifndef __local___localdep_cabsf_defined
#define __local___localdep_cabsf_defined
#ifdef __CRT_HAVE_cabsf
__CREDIRECT(,float,__NOTHROW_NCX,__localdep_cabsf,(float _Complex __z),cabsf,(__z))
#elif defined(__CRT_HAVE_cabs) || defined(__CRT_HAVE__cabs) || defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE__hypot) || defined(__CRT_HAVE___hypot) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/complex/cabsf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_cabsf __LIBC_LOCAL_NAME(cabsf)
#else /* ... */
#undef __local___localdep_cabsf_defined
#endif /* !... */
#endif /* !__local___localdep_cabsf_defined */
#ifndef __local___localdep_cimagf_defined
#define __local___localdep_cimagf_defined
#ifdef __CRT_HAVE_cimagf
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW_NCX,__localdep_cimagf,(float _Complex __z),cimagf,(__z))
#else /* __CRT_HAVE_cimagf */
__NAMESPACE_LOCAL_END
#include <libc/local/complex/cimagf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_cimagf __LIBC_LOCAL_NAME(cimagf)
#endif /* !__CRT_HAVE_cimagf */
#endif /* !__local___localdep_cimagf_defined */
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
#ifndef __local___localdep_copysignf_defined
#define __local___localdep_copysignf_defined
#if __has_builtin(__builtin_copysignf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysignf)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_copysignf,(float __num, float __sign),copysignf,{ return __builtin_copysignf(__num, __sign); })
#elif defined(__CRT_HAVE_copysignf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_copysignf,(float __num, float __sign),copysignf,(__num,__sign))
#elif defined(__CRT_HAVE__copysignf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_copysignf,(float __num, float __sign),_copysignf,(__num,__sign))
#elif defined(__CRT_HAVE___copysignf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_copysignf,(float __num, float __sign),__copysignf,(__num,__sign))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/copysignf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_copysignf __LIBC_LOCAL_NAME(copysignf)
#endif /* !... */
#endif /* !__local___localdep_copysignf_defined */
#ifndef __local___localdep_crealf_defined
#define __local___localdep_crealf_defined
#ifdef __CRT_HAVE_crealf
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW_NCX,__localdep_crealf,(float _Complex __z),crealf,(__z))
#else /* __CRT_HAVE_crealf */
__NAMESPACE_LOCAL_END
#include <libc/local/complex/crealf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_crealf __LIBC_LOCAL_NAME(crealf)
#endif /* !__CRT_HAVE_crealf */
#endif /* !__local___localdep_crealf_defined */
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
#elif (defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_cabs) || defined(__CRT_HAVE__cabs) || defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE__hypot) || defined(__CRT_HAVE___hypot) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))
__NAMESPACE_LOCAL_END
#include <libc/local/complex/csqrt.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_csqrt __LIBC_LOCAL_NAME(csqrt)
#else /* ... */
#undef __local___localdep_csqrt_defined
#endif /* !... */
#endif /* !__local___localdep_csqrt_defined */
#ifndef __local___localdep_fabsf_defined
#define __local___localdep_fabsf_defined
#if __has_builtin(__builtin_fabsf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsf)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_fabsf,(float __x),fabsf,{ return __builtin_fabsf(__x); })
#elif defined(__CRT_HAVE_fabsf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_fabsf,(float __x),fabsf,(__x))
#elif defined(__CRT_HAVE___fabsf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_fabsf,(float __x),__fabsf,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/fabsf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fabsf __LIBC_LOCAL_NAME(fabsf)
#endif /* !... */
#endif /* !__local___localdep_fabsf_defined */
#ifndef __local___localdep_hypotf_defined
#define __local___localdep_hypotf_defined
#if __has_builtin(__builtin_hypotf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_hypotf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__localdep_hypotf,(float __x, float __y),hypotf,{ return __builtin_hypotf(__x, __y); })
#elif defined(__CRT_HAVE_hypotf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__localdep_hypotf,(float __x, float __y),hypotf,(__x,__y))
#elif defined(__CRT_HAVE__hypotf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__localdep_hypotf,(float __x, float __y),_hypotf,(__x,__y))
#elif defined(__CRT_HAVE___hypotf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__localdep_hypotf,(float __x, float __y),__hypotf,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE__hypot) || defined(__CRT_HAVE___hypot) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/hypotf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_hypotf __LIBC_LOCAL_NAME(hypotf)
#else /* ... */
#undef __local___localdep_hypotf_defined
#endif /* !... */
#endif /* !__local___localdep_hypotf_defined */
#ifndef __local___localdep_isinff_defined
#define __local___localdep_isinff_defined
#if __has_builtin(__builtin_isinff) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinff)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinff,(float __x),isinff,{ return __builtin_isinff(__x); })
#elif defined(__CRT_HAVE_isinff)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinff,(float __x),isinff,(__x))
#elif defined(__CRT_HAVE___isinff)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinff,(float __x),__isinff,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <bits/math-constants.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__INFINITYF) || defined(__HUGE_VALF) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)
__NAMESPACE_LOCAL_END
#include <libc/local/math/isinff.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isinff __LIBC_LOCAL_NAME(isinff)
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __INFINITYF || __HUGE_VALF || __CRT_HAVE_isinf || __CRT_HAVE___isinf || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __INFINITY || __HUGE_VAL */
#undef __local___localdep_isinff_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__INFINITYF && !__HUGE_VALF && !__CRT_HAVE_isinf && !__CRT_HAVE___isinf && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && !__INFINITY && !__HUGE_VAL */
#endif /* !... */
#endif /* !__local___localdep_isinff_defined */
#ifndef __local___localdep_isnanf_defined
#define __local___localdep_isnanf_defined
#if __has_builtin(__builtin_isnanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnanf)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanf,(float __x),isnanf,{ return __builtin_isnanf(__x); })
#elif defined(__CRT_HAVE_isnanf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanf,(float __x),isnanf,(__x))
#elif defined(__CRT_HAVE___isnanf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanf,(float __x),__isnanf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/isnanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isnanf __LIBC_LOCAL_NAME(isnanf)
#else /* ... */
#undef __local___localdep_isnanf_defined
#endif /* !... */
#endif /* !__local___localdep_isnanf_defined */
#ifndef __local___localdep_sqrtf_defined
#define __local___localdep_sqrtf_defined
#if __has_builtin(__builtin_sqrtf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sqrtf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__localdep_sqrtf,(float __x),sqrtf,{ return __builtin_sqrtf(__x); })
#elif defined(__CRT_HAVE_sqrtf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__localdep_sqrtf,(float __x),sqrtf,(__x))
#elif defined(__CRT_HAVE___sqrtf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__localdep_sqrtf,(float __x),__sqrtf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/sqrtf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sqrtf __LIBC_LOCAL_NAME(sqrtf)
#else /* ... */
#undef __local___localdep_sqrtf_defined
#endif /* !... */
#endif /* !__local___localdep_sqrtf_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/floatcore.h>
#include <bits/math-constants.h>
#include <bits/crt/complex.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(csqrtf) __ATTR_WUNUSED float _Complex
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(csqrtf))(float _Complex __z) {
#if (defined(__CRT_HAVE_sqrtf) || defined(__CRT_HAVE___sqrtf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_cabsf) || defined(__CRT_HAVE_cabs) || defined(__CRT_HAVE__cabs) || defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE__hypot) || defined(__CRT_HAVE___hypot) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))
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

























































	float _Complex __w;
	float __x, __y, __r, __t, __scale;
	__x = (__NAMESPACE_LOCAL_SYM __localdep_crealf)(__z);
	__y = (__NAMESPACE_LOCAL_SYM __localdep_cimagf)(__z);
	/* input is a real number and imaginary part isn't -0.0.
	 * negative zero is on the branch cut. */
	if ((__y == 0.0f) && !(__NAMESPACE_LOCAL_SYM __localdep___signbitf)(__y)) {
		if (__x == 0.0f) {
			__w = __CMPLXF(0.0f, __y);
		} else {
			if (__x < 0.0f) {
				__r = (__NAMESPACE_LOCAL_SYM __localdep_sqrtf)(-__x);
				__w = __CMPLXF(0.0f, __r);
			} else {
				__r = (__NAMESPACE_LOCAL_SYM __localdep_sqrtf)(__x);
				__w = __r;
			}
		}
		return __w;
	}
	if (__x == 0.0f) {
		if (__y > 0) {
			__r = (__NAMESPACE_LOCAL_SYM __localdep_sqrtf)(0.5f * __y);
			__w = __CMPLXF(__r, __r);
		} else {
			__r = (__NAMESPACE_LOCAL_SYM __localdep_sqrtf)(-0.5f * __y);
			__w = __CMPLXF(__r, -__r);
		}
		return __w;
	}
	/* Rescale to avoid internal overflow or underflow.  */
	if (((__NAMESPACE_LOCAL_SYM __localdep_fabsf)(__x) > 4.0f) || ((__NAMESPACE_LOCAL_SYM __localdep_fabsf)(__y) > 4.0f)) {
		__x *= 0.25f;
		__y *= 0.25f;
		__scale = 2.0f;
	} else {

		__x *= 6.7108864e7f; /* 2^26 */
		__y *= 6.7108864e7f;
		__scale = 1.220703125e-4f; /* 2^-13 */









	}
	__w = __CMPLXF(__x, __y);
	__r = (__NAMESPACE_LOCAL_SYM __localdep_cabsf)(__w);
	if (__x > 0) {
		__t = (__NAMESPACE_LOCAL_SYM __localdep_sqrtf)(0.5f * __r + 0.5f * __x);
		__r = __scale * (__NAMESPACE_LOCAL_SYM __localdep_fabsf)((0.5f * __y) / __t );
		__t *= __scale;
	} else {
		__r = (__NAMESPACE_LOCAL_SYM __localdep_sqrtf)(0.5f * __r - 0.5f * __x);
		__t = __scale * (__NAMESPACE_LOCAL_SYM __localdep_fabsf)((0.5f * __y) / __r);
		__r *= __scale;
	}
	if (__y > 0) {
		__w = __CMPLXF(__t, __r);
	} else {
		__w = __CMPLXF(__t, -__r);
	}
	return __w;

#else /* (__CRT_HAVE_sqrtf || __CRT_HAVE___sqrtf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_sqrt || __CRT_HAVE___sqrt || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_cabsf || __CRT_HAVE_cabs || __CRT_HAVE__cabs || __CRT_HAVE_hypot || __CRT_HAVE__hypot || __CRT_HAVE___hypot || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) */
	return (float _Complex)(__NAMESPACE_LOCAL_SYM __localdep_csqrt)((double _Complex)__z);
#endif /* (!__CRT_HAVE_sqrtf && !__CRT_HAVE___sqrtf && !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_sqrt && !__CRT_HAVE___sqrt && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_cabsf && !__CRT_HAVE_cabs && !__CRT_HAVE__cabs && !__CRT_HAVE_hypot && !__CRT_HAVE__hypot && !__CRT_HAVE___hypot && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_csqrtf_defined
#define __local___localdep_csqrtf_defined
#define __localdep_csqrtf __LIBC_LOCAL_NAME(csqrtf)
#endif /* !__local___localdep_csqrtf_defined */
#else /* __CRT_HAVE_csqrt || ((__CRT_HAVE_sqrt || __CRT_HAVE___sqrt || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_cabs || __CRT_HAVE__cabs || __CRT_HAVE_hypot || __CRT_HAVE__hypot || __CRT_HAVE___hypot || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) */
#undef __local_csqrtf_defined
#endif /* !__CRT_HAVE_csqrt && ((!__CRT_HAVE_sqrt && !__CRT_HAVE___sqrt && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_cabs && !__CRT_HAVE__cabs && !__CRT_HAVE_hypot && !__CRT_HAVE__hypot && !__CRT_HAVE___hypot && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) */
#endif /* !__local_csqrtf_defined */
