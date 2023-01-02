/* HASH CRC-32:0x39ee2a1d */
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
#ifndef __local_casin_defined
#define __local_casin_defined
#include <__crt.h>
#include <ieee754.h>
#if (defined(__CRT_HAVE_csqrt) || ((defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_cabs) || defined(__CRT_HAVE__cabs) || defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE__hypot) || defined(__CRT_HAVE___hypot) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)))) && (defined(__CRT_HAVE_clog) || ((defined(__CRT_HAVE_cabs) || defined(__CRT_HAVE__cabs) || defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE__hypot) || defined(__CRT_HAVE___hypot) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))))
__NAMESPACE_LOCAL_BEGIN
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
#ifndef __local___localdep_clog_defined
#define __local___localdep_clog_defined
#ifdef __CRT_HAVE_clog
__CREDIRECT(__ATTR_WUNUSED,double _Complex,__NOTHROW_NCX,__localdep_clog,(double _Complex __z),clog,(__z))
#elif (defined(__CRT_HAVE_cabs) || defined(__CRT_HAVE__cabs) || defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE__hypot) || defined(__CRT_HAVE___hypot) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))
__NAMESPACE_LOCAL_END
#include <libc/local/complex/clog.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_clog __LIBC_LOCAL_NAME(clog)
#else /* ... */
#undef __local___localdep_clog_defined
#endif /* !... */
#endif /* !__local___localdep_clog_defined */
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
__NAMESPACE_LOCAL_END
#include <bits/crt/complex.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(casin) __ATTR_WUNUSED double _Complex
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(casin))(double _Complex __z) {
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
	double _Complex __ca, __ct, __zz, __z2;
	double __x, __y;
	__x  = (__NAMESPACE_LOCAL_SYM __localdep_creal)(__z);
	__y  = (__NAMESPACE_LOCAL_SYM __localdep_cimag)(__z);
	__ca = __CMPLX(__x, __y);
	__ct = __CMPLX(0.0, __ca);
	/* sqrt( 1 - z*z) */
	/* cmul( &ca, &ca, &zz ) */
	/*x * x  -  y * y */
	__zz = __CMPLX((__x - __y) * (__x + __y), (2.0 * __x * __y));
	__zz = __CMPLX(1.0 - (__NAMESPACE_LOCAL_SYM __localdep_creal)(__zz), -(__NAMESPACE_LOCAL_SYM __localdep_cimag)(__zz));
	__z2 = (__NAMESPACE_LOCAL_SYM __localdep_csqrt)(__zz);
	__zz = __ct + __z2;
	__zz = (__NAMESPACE_LOCAL_SYM __localdep_clog)(__zz);
	/* multiply by 1/i = -i */
	__w = __zz * __CMPLX(0.0, -1.0);
	return __w;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_casin_defined
#define __local___localdep_casin_defined
#define __localdep_casin __LIBC_LOCAL_NAME(casin)
#endif /* !__local___localdep_casin_defined */
#else /* (__CRT_HAVE_csqrt || ((__CRT_HAVE_sqrt || __CRT_HAVE___sqrt || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_cabs || __CRT_HAVE__cabs || __CRT_HAVE_hypot || __CRT_HAVE__hypot || __CRT_HAVE___hypot || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))) && (__CRT_HAVE_clog || ((__CRT_HAVE_cabs || __CRT_HAVE__cabs || __CRT_HAVE_hypot || __CRT_HAVE__hypot || __CRT_HAVE___hypot || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_log || __CRT_HAVE___log || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_atan2 || __CRT_HAVE___atan2 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))) */
#undef __local_casin_defined
#endif /* (!__CRT_HAVE_csqrt && ((!__CRT_HAVE_sqrt && !__CRT_HAVE___sqrt && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_cabs && !__CRT_HAVE__cabs && !__CRT_HAVE_hypot && !__CRT_HAVE__hypot && !__CRT_HAVE___hypot && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))) || (!__CRT_HAVE_clog && ((!__CRT_HAVE_cabs && !__CRT_HAVE__cabs && !__CRT_HAVE_hypot && !__CRT_HAVE__hypot && !__CRT_HAVE___hypot && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_log && !__CRT_HAVE___log && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_atan2 && !__CRT_HAVE___atan2 && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))) */
#endif /* !__local_casin_defined */
