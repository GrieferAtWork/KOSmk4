/* HASH CRC-32:0x938a8b5c */
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
#ifndef __local_ctanf_defined
#define __local_ctanf_defined
#include <__crt.h>
#include <ieee754.h>
#if ((defined(__CRT_HAVE_sincosf) || defined(__CRT_HAVE___sincosf) || defined(__CRT_HAVE_sincos) || defined(__CRT_HAVE___sincos) || ((defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)) && (defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos))) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || ((defined(__CRT_HAVE_sinf) || defined(__CRT_HAVE___sinf) || defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)) && (defined(__CRT_HAVE_cosf) || defined(__CRT_HAVE___cosf) || defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos))) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)) && (defined(__CRT_HAVE_coshf) || defined(__CRT_HAVE___coshf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_sinhf) || defined(__CRT_HAVE___sinhf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))) || defined(__CRT_HAVE_ctan) || ((defined(__CRT_HAVE_sincos) || defined(__CRT_HAVE___sincos) || ((defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)) && (defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos))) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__ctansf_defined
#define __local___localdep__ctansf_defined
__NAMESPACE_LOCAL_END
#include <libc/local/complex/_ctansf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__ctansf __LIBC_LOCAL_NAME(_ctansf)
#endif /* !__local___localdep__ctansf_defined */
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
#ifndef __local___localdep_coshf_defined
#define __local___localdep_coshf_defined
#if __has_builtin(__builtin_coshf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_coshf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__localdep_coshf,(float __x),coshf,{ return __builtin_coshf(__x); })
#elif defined(__CRT_HAVE_coshf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__localdep_coshf,(float __x),coshf,(__x))
#elif defined(__CRT_HAVE___coshf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__localdep_coshf,(float __x),__coshf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/coshf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_coshf __LIBC_LOCAL_NAME(coshf)
#else /* ... */
#undef __local___localdep_coshf_defined
#endif /* !... */
#endif /* !__local___localdep_coshf_defined */
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
#ifndef __local___localdep_ctan_defined
#define __local___localdep_ctan_defined
#ifdef __CRT_HAVE_ctan
__CREDIRECT(__ATTR_WUNUSED,double _Complex,__NOTHROW_NCX,__localdep_ctan,(double _Complex __z),ctan,(__z))
#elif (defined(__CRT_HAVE_sincos) || defined(__CRT_HAVE___sincos) || ((defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)) && (defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos))) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))
__NAMESPACE_LOCAL_END
#include <libc/local/complex/ctan.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_ctan __LIBC_LOCAL_NAME(ctan)
#else /* ... */
#undef __local___localdep_ctan_defined
#endif /* !... */
#endif /* !__local___localdep_ctan_defined */
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
#ifndef __local___localdep_sincosf_defined
#define __local___localdep_sincosf_defined
#if __has_builtin(__builtin_sincosf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sincosf)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__DECL_SIMD_sincosf __ATTR_OUT(2) __ATTR_OUT(3),void,__NOTHROW,__localdep_sincosf,(float __x, float *__psinx, float *__pcosx),sincosf,{ __builtin_sincosf(__x, __psinx, __pcosx); })
#elif defined(__CRT_HAVE_sincosf)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__DECL_SIMD_sincosf __ATTR_OUT(2) __ATTR_OUT(3),__NOTHROW,__localdep_sincosf,(float __x, float *__psinx, float *__pcosx),sincosf,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE___sincosf)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__DECL_SIMD_sincosf __ATTR_OUT(2) __ATTR_OUT(3),__NOTHROW,__localdep_sincosf,(float __x, float *__psinx, float *__pcosx),__sincosf,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE_sincos) || defined(__CRT_HAVE___sincos) || ((defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)) && (defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos))) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || ((defined(__CRT_HAVE_sinf) || defined(__CRT_HAVE___sinf) || defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)) && (defined(__CRT_HAVE_cosf) || defined(__CRT_HAVE___cosf) || defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos))) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/sincosf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sincosf __LIBC_LOCAL_NAME(sincosf)
#else /* ... */
#undef __local___localdep_sincosf_defined
#endif /* !... */
#endif /* !__local___localdep_sincosf_defined */
#ifndef __local___localdep_sinhf_defined
#define __local___localdep_sinhf_defined
#if __has_builtin(__builtin_sinhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinhf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__localdep_sinhf,(float __x),sinhf,{ return __builtin_sinhf(__x); })
#elif defined(__CRT_HAVE_sinhf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__localdep_sinhf,(float __x),sinhf,(__x))
#elif defined(__CRT_HAVE___sinhf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__localdep_sinhf,(float __x),__sinhf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/sinhf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sinhf __LIBC_LOCAL_NAME(sinhf)
#else /* ... */
#undef __local___localdep_sinhf_defined
#endif /* !... */
#endif /* !__local___localdep_sinhf_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/complex.h>
#include <hybrid/floatcore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ctanf) __ATTR_WUNUSED float _Complex
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ctanf))(float _Complex __z) {
#if (defined(__CRT_HAVE_sincosf) || defined(__CRT_HAVE___sincosf) || defined(__CRT_HAVE_sincos) || defined(__CRT_HAVE___sincos) || ((defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)) && (defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos))) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || ((defined(__CRT_HAVE_sinf) || defined(__CRT_HAVE___sinf) || defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)) && (defined(__CRT_HAVE_cosf) || defined(__CRT_HAVE___cosf) || defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos))) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)) && (defined(__CRT_HAVE_coshf) || defined(__CRT_HAVE___coshf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && (defined(__CRT_HAVE_sinhf) || defined(__CRT_HAVE___sinhf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))
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
	float __d;
	float __sin_2_0_creal_z, __cos_2_0_creal_z;
	(__NAMESPACE_LOCAL_SYM __localdep_sincosf)(2.0f * (__NAMESPACE_LOCAL_SYM __localdep_crealf)(__z), &__sin_2_0_creal_z, &__cos_2_0_creal_z);
	__d = __cos_2_0_creal_z + (__NAMESPACE_LOCAL_SYM __localdep_coshf)(2.0f * (__NAMESPACE_LOCAL_SYM __localdep_cimagf)(__z));
	if ((__NAMESPACE_LOCAL_SYM __localdep_fabsf)(__d) < 0.25f)
		__d = (__NAMESPACE_LOCAL_SYM __localdep__ctansf)(__z);
	if (__d == 0.0f) {
		/* mtherr("ctan", OVERFLOW); */
		__w = __CMPLXF(__FLT_MAX__, __FLT_MAX__);
		return __w;
	}
	__w = __CMPLXF(__sin_2_0_creal_z / __d, (__NAMESPACE_LOCAL_SYM __localdep_sinhf)(2.0f * (__NAMESPACE_LOCAL_SYM __localdep_cimagf)(__z)) / __d);
	return __w;
#else /* (__CRT_HAVE_sincosf || __CRT_HAVE___sincosf || __CRT_HAVE_sincos || __CRT_HAVE___sincos || ((__CRT_HAVE_sin || __CRT_HAVE___sin) && (__CRT_HAVE_cos || __CRT_HAVE___cos)) || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || ((__CRT_HAVE_sinf || __CRT_HAVE___sinf || __CRT_HAVE_sin || __CRT_HAVE___sin) && (__CRT_HAVE_cosf || __CRT_HAVE___cosf || __CRT_HAVE_cos || __CRT_HAVE___cos)) || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) && (__CRT_HAVE_coshf || __CRT_HAVE___coshf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_cosh || __CRT_HAVE___cosh || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_sinhf || __CRT_HAVE___sinhf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_sinh || __CRT_HAVE___sinh || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) */
	return (float _Complex)(__NAMESPACE_LOCAL_SYM __localdep_ctan)((double _Complex)__z);
#endif /* (!__CRT_HAVE_sincosf && !__CRT_HAVE___sincosf && !__CRT_HAVE_sincos && !__CRT_HAVE___sincos && ((!__CRT_HAVE_sin && !__CRT_HAVE___sin) || (!__CRT_HAVE_cos && !__CRT_HAVE___cos)) && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && ((!__CRT_HAVE_sinf && !__CRT_HAVE___sinf && !__CRT_HAVE_sin && !__CRT_HAVE___sin) || (!__CRT_HAVE_cosf && !__CRT_HAVE___cosf && !__CRT_HAVE_cos && !__CRT_HAVE___cos)) && !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || (!__CRT_HAVE_coshf && !__CRT_HAVE___coshf && !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_cosh && !__CRT_HAVE___cosh && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_sinhf && !__CRT_HAVE___sinhf && !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_sinh && !__CRT_HAVE___sinh && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ctanf_defined
#define __local___localdep_ctanf_defined
#define __localdep_ctanf __LIBC_LOCAL_NAME(ctanf)
#endif /* !__local___localdep_ctanf_defined */
#else /* ((__CRT_HAVE_sincosf || __CRT_HAVE___sincosf || __CRT_HAVE_sincos || __CRT_HAVE___sincos || ((__CRT_HAVE_sin || __CRT_HAVE___sin) && (__CRT_HAVE_cos || __CRT_HAVE___cos)) || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || ((__CRT_HAVE_sinf || __CRT_HAVE___sinf || __CRT_HAVE_sin || __CRT_HAVE___sin) && (__CRT_HAVE_cosf || __CRT_HAVE___cosf || __CRT_HAVE_cos || __CRT_HAVE___cos)) || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) && (__CRT_HAVE_coshf || __CRT_HAVE___coshf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_cosh || __CRT_HAVE___cosh || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_sinhf || __CRT_HAVE___sinhf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_sinh || __CRT_HAVE___sinh || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) || __CRT_HAVE_ctan || ((__CRT_HAVE_sincos || __CRT_HAVE___sincos || ((__CRT_HAVE_sin || __CRT_HAVE___sin) && (__CRT_HAVE_cos || __CRT_HAVE___cos)) || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_cosh || __CRT_HAVE___cosh || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) && (__CRT_HAVE_sinh || __CRT_HAVE___sinh || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) */
#undef __local_ctanf_defined
#endif /* ((!__CRT_HAVE_sincosf && !__CRT_HAVE___sincosf && !__CRT_HAVE_sincos && !__CRT_HAVE___sincos && ((!__CRT_HAVE_sin && !__CRT_HAVE___sin) || (!__CRT_HAVE_cos && !__CRT_HAVE___cos)) && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && ((!__CRT_HAVE_sinf && !__CRT_HAVE___sinf && !__CRT_HAVE_sin && !__CRT_HAVE___sin) || (!__CRT_HAVE_cosf && !__CRT_HAVE___cosf && !__CRT_HAVE_cos && !__CRT_HAVE___cos)) && !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || (!__CRT_HAVE_coshf && !__CRT_HAVE___coshf && !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_cosh && !__CRT_HAVE___cosh && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_sinhf && !__CRT_HAVE___sinhf && !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_sinh && !__CRT_HAVE___sinh && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && !__CRT_HAVE_ctan && ((!__CRT_HAVE_sincos && !__CRT_HAVE___sincos && ((!__CRT_HAVE_sin && !__CRT_HAVE___sin) || (!__CRT_HAVE_cos && !__CRT_HAVE___cos)) && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_cosh && !__CRT_HAVE___cosh && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || (!__CRT_HAVE_sinh && !__CRT_HAVE___sinh && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) */
#endif /* !__local_ctanf_defined */
