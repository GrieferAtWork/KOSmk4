/* HASH CRC-32:0x14588452 */
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
#ifndef __local__cchsh_defined
#define __local__cchsh_defined
#include <__crt.h>
#include <ieee754.h>
#if (defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_cosh_defined
#define __local___localdep_cosh_defined
#if __has_builtin(__builtin_cosh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cosh)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_cosh,(double __x),cosh,{ return __builtin_cosh(__x); })
#elif defined(__CRT_HAVE_cosh)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_cosh,(double __x),cosh,(__x))
#elif defined(__CRT_HAVE___cosh)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_cosh,(double __x),__cosh,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/cosh.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_cosh __LIBC_LOCAL_NAME(cosh)
#else /* ... */
#undef __local___localdep_cosh_defined
#endif /* !... */
#endif /* !__local___localdep_cosh_defined */
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
#ifndef __local___localdep_sinh_defined
#define __local___localdep_sinh_defined
#if __has_builtin(__builtin_sinh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinh)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_sinh,(double __x),sinh,{ return __builtin_sinh(__x); })
#elif defined(__CRT_HAVE_sinh)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_sinh,(double __x),sinh,(__x))
#elif defined(__CRT_HAVE___sinh)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_sinh,(double __x),__sinh,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/sinh.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sinh __LIBC_LOCAL_NAME(sinh)
#else /* ... */
#undef __local___localdep_sinh_defined
#endif /* !... */
#endif /* !__local___localdep_sinh_defined */
__LOCAL_LIBC(_cchsh) __ATTR_OUT(2) __ATTR_OUT(3) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_cchsh))(double __x, double *__c, double *__s) {
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
	double __e, __ei;
	if ((__NAMESPACE_LOCAL_SYM __localdep_fabs)(__x) <= 0.5) {
		*__c = (__NAMESPACE_LOCAL_SYM __localdep_cosh)(__x);
		*__s = (__NAMESPACE_LOCAL_SYM __localdep_sinh)(__x);
	} else {
		__e = (__NAMESPACE_LOCAL_SYM __localdep_exp)(__x);
		__ei = 0.5 / __e;
		__e = 0.5 * __e;
		*__s = __e - __ei;
		*__c = __e + __ei;
	}
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__cchsh_defined
#define __local___localdep__cchsh_defined
#define __localdep__cchsh __LIBC_LOCAL_NAME(_cchsh)
#endif /* !__local___localdep__cchsh_defined */
#else /* (__CRT_HAVE_cosh || __CRT_HAVE___cosh || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_sinh || __CRT_HAVE___sinh || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_exp || __CRT_HAVE___exp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) */
#undef __local__cchsh_defined
#endif /* (!__CRT_HAVE_cosh && !__CRT_HAVE___cosh && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_sinh && !__CRT_HAVE___sinh && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_exp && !__CRT_HAVE___exp && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) */
#endif /* !__local__cchsh_defined */
