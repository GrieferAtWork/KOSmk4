/* HASH CRC-32:0x67cc6a86 */
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
#ifndef __local_cpow_defined
#define __local_cpow_defined
#include <__crt.h>
#include <ieee754.h>
#if (defined(__CRT_HAVE_cabs) || defined(__CRT_HAVE__cabs) || defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_carg) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_sincos) || defined(__CRT_HAVE___sincos) || ((defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)) && (defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos))) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_cabs_defined
#define __local___localdep_cabs_defined
#ifdef __CRT_HAVE_cabs
__CREDIRECT(,double,__NOTHROW_NCX,__localdep_cabs,(double _Complex __z),cabs,(__z))
#elif defined(__CRT_HAVE__cabs)
__CREDIRECT(,double,__NOTHROW_NCX,__localdep_cabs,(double _Complex __z),_cabs,(__z))
#elif defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/complex/cabs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_cabs __LIBC_LOCAL_NAME(cabs)
#else /* ... */
#undef __local___localdep_cabs_defined
#endif /* !... */
#endif /* !__local___localdep_cabs_defined */
#ifndef __local___localdep_carg_defined
#define __local___localdep_carg_defined
#ifdef __CRT_HAVE_carg
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW_NCX,__localdep_carg,(double _Complex __z),carg,(__z))
#elif defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/complex/carg.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_carg __LIBC_LOCAL_NAME(carg)
#else /* ... */
#undef __local___localdep_carg_defined
#endif /* !... */
#endif /* !__local___localdep_carg_defined */
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
#ifndef __local___localdep_exp_defined
#define __local___localdep_exp_defined
#if __has_builtin(__builtin_exp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_exp,double,__NOTHROW,__localdep_exp,(double __x),exp,{ return __builtin_exp(__x); })
#elif defined(__CRT_HAVE_exp)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_exp,double,__NOTHROW,__localdep_exp,(double __x),exp,(__x))
#elif defined(__CRT_HAVE___exp)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_exp,double,__NOTHROW,__localdep_exp,(double __x),__exp,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/exp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_exp __LIBC_LOCAL_NAME(exp)
#else /* ... */
#undef __local___localdep_exp_defined
#endif /* !... */
#endif /* !__local___localdep_exp_defined */
#ifndef __local___localdep_log_defined
#define __local___localdep_log_defined
#if __has_builtin(__builtin_log) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_log,double,__NOTHROW,__localdep_log,(double __x),log,{ return __builtin_log(__x); })
#elif defined(__CRT_HAVE_log)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_log,double,__NOTHROW,__localdep_log,(double __x),log,(__x))
#elif defined(__CRT_HAVE___log)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_log,double,__NOTHROW,__localdep_log,(double __x),__log,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/log.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_log __LIBC_LOCAL_NAME(log)
#else /* ... */
#undef __local___localdep_log_defined
#endif /* !... */
#endif /* !__local___localdep_log_defined */
#ifndef __local___localdep_pow_defined
#define __local___localdep_pow_defined
#if __has_builtin(__builtin_pow) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_pow,double,__NOTHROW,__localdep_pow,(double __x, double __y),pow,{ return __builtin_pow(__x, __y); })
#elif defined(__CRT_HAVE_pow)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_pow,double,__NOTHROW,__localdep_pow,(double __x, double __y),pow,(__x,__y))
#elif defined(__CRT_HAVE___pow)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_pow,double,__NOTHROW,__localdep_pow,(double __x, double __y),__pow,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/pow.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_pow __LIBC_LOCAL_NAME(pow)
#else /* ... */
#undef __local___localdep_pow_defined
#endif /* !... */
#endif /* !__local___localdep_pow_defined */
#ifndef __local___localdep_sincos_defined
#define __local___localdep_sincos_defined
#if __has_builtin(__builtin_sincos) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sincos)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__DECL_SIMD_sincos __ATTR_NONNULL((2, 3)),void,__NOTHROW,__localdep_sincos,(double __x, double *__psinx, double *__pcosx),sincos,{ __builtin_sincos(__x, __psinx, __pcosx); })
#elif defined(__CRT_HAVE_sincos)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__DECL_SIMD_sincos __ATTR_NONNULL((2, 3)),__NOTHROW,__localdep_sincos,(double __x, double *__psinx, double *__pcosx),sincos,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE___sincos)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__DECL_SIMD_sincos __ATTR_NONNULL((2, 3)),__NOTHROW,__localdep_sincos,(double __x, double *__psinx, double *__pcosx),__sincos,(__x,__psinx,__pcosx))
#elif ((defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)) && (defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos))) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/sincos.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sincos __LIBC_LOCAL_NAME(sincos)
#else /* ... */
#undef __local___localdep_sincos_defined
#endif /* !... */
#endif /* !__local___localdep_sincos_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/complex.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(cpow) __ATTR_WUNUSED double _Complex
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cpow))(double _Complex __a, double _Complex __z) {
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
	double __x, __y, __r, __theta, __absa, __arga;
	double __sin_theta, __cos_theta;
	__x    = (__NAMESPACE_LOCAL_SYM __localdep_creal)(__z);
	__y    = (__NAMESPACE_LOCAL_SYM __localdep_cimag)(__z);
	__absa = (__NAMESPACE_LOCAL_SYM __localdep_cabs)(__a);
	if (__absa == 0.0)
		return __CMPLX(0.0, 0.0);
	__arga  = (__NAMESPACE_LOCAL_SYM __localdep_carg)(__a);
	__r     = (__NAMESPACE_LOCAL_SYM __localdep_pow)(__absa, __x);
	__theta = __x * __arga;
	if (__y != 0.0) {
		__r     = __r * (__NAMESPACE_LOCAL_SYM __localdep_exp)(-__y * __arga);
		__theta = __theta + __y * (__NAMESPACE_LOCAL_SYM __localdep_log)(__absa);
	}
	(__NAMESPACE_LOCAL_SYM __localdep_sincos)(__theta, &__sin_theta, &__cos_theta);
	__w = __CMPLX(__r * __cos_theta, __r * __sin_theta);
	return __w;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cpow_defined
#define __local___localdep_cpow_defined
#define __localdep_cpow __LIBC_LOCAL_NAME(cpow)
#endif /* !__local___localdep_cpow_defined */
#else /* (__CRT_HAVE_cabs || __CRT_HAVE__cabs || __CRT_HAVE_hypot || __CRT_HAVE___hypot || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_log || __CRT_HAVE___log || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_carg || __CRT_HAVE_atan2 || __CRT_HAVE___atan2 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_pow || __CRT_HAVE___pow || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_exp || __CRT_HAVE___exp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_sincos || __CRT_HAVE___sincos || ((__CRT_HAVE_sin || __CRT_HAVE___sin) && (__CRT_HAVE_cos || __CRT_HAVE___cos)) || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) */
#undef __local_cpow_defined
#endif /* (!__CRT_HAVE_cabs && !__CRT_HAVE__cabs && !__CRT_HAVE_hypot && !__CRT_HAVE___hypot && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_log && !__CRT_HAVE___log && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_carg && !__CRT_HAVE_atan2 && !__CRT_HAVE___atan2 && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_pow && !__CRT_HAVE___pow && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_exp && !__CRT_HAVE___exp && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_sincos && !__CRT_HAVE___sincos && ((!__CRT_HAVE_sin && !__CRT_HAVE___sin) || (!__CRT_HAVE_cos && !__CRT_HAVE___cos)) && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) */
#endif /* !__local_cpow_defined */
