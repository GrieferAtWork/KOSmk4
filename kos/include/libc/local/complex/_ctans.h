/* HASH CRC-32:0x9de7b5a */
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
#ifndef __local__ctans_defined
#define __local__ctans_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__redupi_defined
#define __local___localdep__redupi_defined
__NAMESPACE_LOCAL_END
#include <libc/local/complex/_redupi.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__redupi __LIBC_LOCAL_NAME(_redupi)
#endif /* !__local___localdep__redupi_defined */
#ifndef __local___localdep_cimag_defined
#define __local___localdep_cimag_defined
#ifdef __CRT_HAVE_cimag
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_cimag,(double _Complex __z),cimag,(__z))
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
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_creal,(double _Complex __z),creal,(__z))
#else /* __CRT_HAVE_creal */
__NAMESPACE_LOCAL_END
#include <libc/local/complex/creal.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_creal __LIBC_LOCAL_NAME(creal)
#endif /* !__CRT_HAVE_creal */
#endif /* !__local___localdep_creal_defined */
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
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_fabs) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_fabsl,(__LONGDOUBLE __x),fabs,(__x))
#elif defined(__CRT_HAVE___fabs) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_fabsl,(__LONGDOUBLE __x),__fabs,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/fabsl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fabsl __LIBC_LOCAL_NAME(fabsl)
#endif /* !... */
#endif /* !... */
#endif /* !__local___localdep_fabsl_defined */
__LOCAL_LIBC(_ctans) __ATTR_CONST __ATTR_WUNUSED double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(_ctans))(double _Complex __z) {
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
	double __f, __x, __x2, __y, __y2, __rn, __t, __d;
	__x  = (__NAMESPACE_LOCAL_SYM __localdep_fabs)(2.0 * (__NAMESPACE_LOCAL_SYM __localdep_creal)(__z));
	__y  = (__NAMESPACE_LOCAL_SYM __localdep_fabs)(2.0 * (__NAMESPACE_LOCAL_SYM __localdep_cimag)(__z));
	__x  = (__NAMESPACE_LOCAL_SYM __localdep__redupi)(__x);
	__x  = __x * __x;
	__y  = __y * __y;
	__x2 = 1.0;
	__y2 = 1.0;
	__f  = 1.0;
	__rn = 0.0;
	__d  = 0.0;
	do {
		__rn += 1.0;
		__f *= __rn;
		__rn += 1.0;
		__f *= __rn;
		__x2 *= __x;
		__y2 *= __y;
		__t = __y2 + __x2;
		__t /= __f;
		__d += __t;
		__rn += 1.0;
		__f *= __rn;
		__rn += 1.0;
		__f *= __rn;
		__x2 *= __x;
		__y2 *= __y;
		__t = __y2 - __x2;
		__t /= __f;
		__d += __t;
	}









	while ((__NAMESPACE_LOCAL_SYM __localdep_fabs)(__t/__d) > 1.1e-16);

	return __d;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__ctans_defined
#define __local___localdep__ctans_defined
#define __localdep__ctans __LIBC_LOCAL_NAME(_ctans)
#endif /* !__local___localdep__ctans_defined */
#endif /* !__local__ctans_defined */
