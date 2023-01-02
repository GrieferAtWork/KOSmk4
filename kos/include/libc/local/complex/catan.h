/* HASH CRC-32:0x30025893 */
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
#ifndef __local_catan_defined
#define __local_catan_defined
#include <__crt.h>
#include <ieee754.h>
#if (defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__redupi_defined
#define __local___localdep__redupi_defined
__NAMESPACE_LOCAL_END
#include <libc/local/complex/_redupi.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__redupi __LIBC_LOCAL_NAME(_redupi)
#endif /* !__local___localdep__redupi_defined */
#ifndef __local___localdep_atan2_defined
#define __local___localdep_atan2_defined
#if __has_builtin(__builtin_atan2) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_atan2,(double __y, double __x),atan2,{ return __builtin_atan2(__y, __x); })
#elif defined(__CRT_HAVE_atan2)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_atan2,(double __y, double __x),atan2,(__y,__x))
#elif defined(__CRT_HAVE___atan2)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_atan2,(double __y, double __x),__atan2,(__y,__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/atan2.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_atan2 __LIBC_LOCAL_NAME(atan2)
#else /* ... */
#undef __local___localdep_atan2_defined
#endif /* !... */
#endif /* !__local___localdep_atan2_defined */
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
__NAMESPACE_LOCAL_END
#include <bits/crt/complex.h>
#include <hybrid/floatcore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(catan) __ATTR_WUNUSED double _Complex
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(catan))(double _Complex __z) {
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
	double __a, __t, __x, __x2, __y;
	__x = (__NAMESPACE_LOCAL_SYM __localdep_creal)(__z);
	__y = (__NAMESPACE_LOCAL_SYM __localdep_cimag)(__z);
	if ((__x == 0.0) && (__y > 1.0))
		goto __ovrf;
	__x2 = __x * __x;
	__a = 1.0 - __x2 - (__y * __y);
	if (__a == 0.0)
		goto __ovrf;
	__t = 0.5 * (__NAMESPACE_LOCAL_SYM __localdep_atan2)(2.0 * __x, __a);
	__w = (__NAMESPACE_LOCAL_SYM __localdep__redupi)(__t);
	__t = __y - 1.0;
	__a = __x2 + (__t * __t);
	if (__a == 0.0)
		goto __ovrf;
	__t = __y + 1.0;
	__a = (__x2 + (__t * __t))/__a;
	__w = __CMPLX(__w, (0.25 * (__NAMESPACE_LOCAL_SYM __localdep_log)(__a)));
	return __w;
__ovrf:
	/* matherr("catan", OVERFLOW); */
	__w = __CMPLX(__DBL_MAX__, __DBL_MAX__);
	return __w;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_catan_defined
#define __local___localdep_catan_defined
#define __localdep_catan __LIBC_LOCAL_NAME(catan)
#endif /* !__local___localdep_catan_defined */
#else /* (__CRT_HAVE_atan2 || __CRT_HAVE___atan2 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_log || __CRT_HAVE___log || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) */
#undef __local_catan_defined
#endif /* (!__CRT_HAVE_atan2 && !__CRT_HAVE___atan2 && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_log && !__CRT_HAVE___log && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) */
#endif /* !__local_catan_defined */
