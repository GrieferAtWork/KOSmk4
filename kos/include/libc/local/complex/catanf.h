/* HASH CRC-32:0xa0a96296 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_catanf_defined
#define __local_catanf_defined
#include <__crt.h>
#include <ieee754.h>
#if ((defined(__CRT_HAVE_atan2f) || defined(__CRT_HAVE___atan2f) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_logf) || defined(__CRT_HAVE___logf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))) || defined(__CRT_HAVE_catan) || ((defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__redupif_defined
#define __local___localdep__redupif_defined
__NAMESPACE_LOCAL_END
#include <libc/local/complex/_redupif.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__redupif __LIBC_LOCAL_NAME(_redupif)
#endif /* !__local___localdep__redupif_defined */
#ifndef __local___localdep_atan2f_defined
#define __local___localdep_atan2f_defined
#if __has_builtin(__builtin_atan2f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2f)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__localdep_atan2f,(float __y, float __x),atan2f,{ return __builtin_atan2f(__y, __x); })
#elif defined(__CRT_HAVE_atan2f)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__localdep_atan2f,(float __y, float __x),atan2f,(__y,__x))
#elif defined(__CRT_HAVE___atan2f)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__localdep_atan2f,(float __y, float __x),__atan2f,(__y,__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/atan2f.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_atan2f __LIBC_LOCAL_NAME(atan2f)
#else /* ... */
#undef __local___localdep_atan2f_defined
#endif /* !... */
#endif /* !__local___localdep_atan2f_defined */
#ifndef __local___localdep_catan_defined
#define __local___localdep_catan_defined
#ifdef __CRT_HAVE_catan
__CREDIRECT(__ATTR_WUNUSED,double _Complex,__NOTHROW_NCX,__localdep_catan,(double _Complex __z),catan,(__z))
#elif (defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))
__NAMESPACE_LOCAL_END
#include <libc/local/complex/catan.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_catan __LIBC_LOCAL_NAME(catan)
#else /* ... */
#undef __local___localdep_catan_defined
#endif /* !... */
#endif /* !__local___localdep_catan_defined */
#ifndef __local___localdep_cimagf_defined
#define __local___localdep_cimagf_defined
#ifdef __CRT_HAVE_cimagf
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_cimagf,(float _Complex __z),cimagf,(__z))
#else /* __CRT_HAVE_cimagf */
__NAMESPACE_LOCAL_END
#include <libc/local/complex/cimagf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_cimagf __LIBC_LOCAL_NAME(cimagf)
#endif /* !__CRT_HAVE_cimagf */
#endif /* !__local___localdep_cimagf_defined */
#ifndef __local___localdep_crealf_defined
#define __local___localdep_crealf_defined
#ifdef __CRT_HAVE_crealf
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_crealf,(float _Complex __z),crealf,(__z))
#else /* __CRT_HAVE_crealf */
__NAMESPACE_LOCAL_END
#include <libc/local/complex/crealf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_crealf __LIBC_LOCAL_NAME(crealf)
#endif /* !__CRT_HAVE_crealf */
#endif /* !__local___localdep_crealf_defined */
#ifndef __local___localdep_logf_defined
#define __local___localdep_logf_defined
#if __has_builtin(__builtin_logf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logf)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_logf,float,__NOTHROW,__localdep_logf,(float __x),logf,{ return __builtin_logf(__x); })
#elif defined(__CRT_HAVE_logf)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_logf,float,__NOTHROW,__localdep_logf,(float __x),logf,(__x))
#elif defined(__CRT_HAVE___logf)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_logf,float,__NOTHROW,__localdep_logf,(float __x),__logf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/logf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_logf __LIBC_LOCAL_NAME(logf)
#else /* ... */
#undef __local___localdep_logf_defined
#endif /* !... */
#endif /* !__local___localdep_logf_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/complex.h>
#include <hybrid/floatcore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(catanf) __ATTR_WUNUSED float _Complex
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(catanf))(float _Complex __z) {
#if (defined(__CRT_HAVE_atan2f) || defined(__CRT_HAVE___atan2f) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_logf) || defined(__CRT_HAVE___logf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))
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
	float __a, __t, __x, __x2, __y;
	__x = (__NAMESPACE_LOCAL_SYM __localdep_crealf)(__z);
	__y = (__NAMESPACE_LOCAL_SYM __localdep_cimagf)(__z);
	if ((__x == 0.0f) && (__y > 1.0f))
		goto __ovrf;
	__x2 = __x * __x;
	__a = 1.0f - __x2 - (__y * __y);
	if (__a == 0.0f)
		goto __ovrf;
	__t = 0.5f * (__NAMESPACE_LOCAL_SYM __localdep_atan2f)(2.0f * __x, __a);
	__w = (__NAMESPACE_LOCAL_SYM __localdep__redupif)(__t);
	__t = __y - 1.0f;
	__a = __x2 + (__t * __t);
	if (__a == 0.0f)
		goto __ovrf;
	__t = __y + 1.0f;
	__a = (__x2 + (__t * __t))/__a;
	__w = __CMPLXF(__w, (0.25f * (__NAMESPACE_LOCAL_SYM __localdep_logf)(__a)));
	return __w;
__ovrf:
	/* matherr("catan", OVERFLOW); */
	__w = __CMPLXF(__FLT_MAX__, __FLT_MAX__);
	return __w;
#else /* (__CRT_HAVE_atan2f || __CRT_HAVE___atan2f || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_atan2 || __CRT_HAVE___atan2 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_logf || __CRT_HAVE___logf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_log || __CRT_HAVE___log || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) */
	return (float _Complex)(__NAMESPACE_LOCAL_SYM __localdep_catan)((double _Complex)__z);
#endif /* (!__CRT_HAVE_atan2f && !__CRT_HAVE___atan2f && !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_atan2 && !__CRT_HAVE___atan2 && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_logf && !__CRT_HAVE___logf && !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_log && !__CRT_HAVE___log && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_catanf_defined
#define __local___localdep_catanf_defined
#define __localdep_catanf __LIBC_LOCAL_NAME(catanf)
#endif /* !__local___localdep_catanf_defined */
#else /* ((__CRT_HAVE_atan2f || __CRT_HAVE___atan2f || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_atan2 || __CRT_HAVE___atan2 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_logf || __CRT_HAVE___logf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_log || __CRT_HAVE___log || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) || __CRT_HAVE_catan || ((__CRT_HAVE_atan2 || __CRT_HAVE___atan2 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_log || __CRT_HAVE___log || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) */
#undef __local_catanf_defined
#endif /* ((!__CRT_HAVE_atan2f && !__CRT_HAVE___atan2f && !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_atan2 && !__CRT_HAVE___atan2 && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_logf && !__CRT_HAVE___logf && !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_log && !__CRT_HAVE___log && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && !__CRT_HAVE_catan && ((!__CRT_HAVE_atan2 && !__CRT_HAVE___atan2 && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_log && !__CRT_HAVE___log && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) */
#endif /* !__local_catanf_defined */
