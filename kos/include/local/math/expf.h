/* HASH CRC-32:0x1e19df3a */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_expf_defined
#if defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp)
#define __local_expf_defined 1
#include <bits/math-vector.h>
#include <bits/math-vector.h>
/* Dependency: "exp" */
#ifndef ____localdep_exp_defined
#define ____localdep_exp_defined 1
#if __has_builtin(__builtin_exp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp)
/* Exponential function of X */
__CEIREDIRECT(__DECL_SIMD_exp __ATTR_WUNUSED,double,__NOTHROW,__localdep_exp,(double __x),exp,{ return __builtin_exp(__x); })
#elif defined(__CRT_HAVE_exp)
/* Exponential function of X */
__CREDIRECT(__DECL_SIMD_exp __ATTR_WUNUSED,double,__NOTHROW,__localdep_exp,(double __x),exp,(__x))
#elif defined(__CRT_HAVE___exp)
/* Exponential function of X */
__CREDIRECT(__DECL_SIMD_exp __ATTR_WUNUSED,double,__NOTHROW,__localdep_exp,(double __x),__exp,(__x))
#else /* LIBC: exp */
#undef ____localdep_exp_defined
#endif /* exp... */
#endif /* !____localdep_exp_defined */

__NAMESPACE_LOCAL_BEGIN
/* Exponential function of X */
__LOCAL_LIBC(expf) __DECL_SIMD_expf __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(expf))(float __x) {
#line 437 "kos/src/libc/magic/math.c"
	return (float)__localdep_exp((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_exp || __CRT_HAVE___exp */
#endif /* !__local_expf_defined */
