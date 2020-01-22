/* HASH CRC-32:0xfaaed893 */
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
#ifndef __local_pow10f_defined
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_powf) || defined(__CRT_HAVE___powf)
#define __local_pow10f_defined 1
#include <bits/math-vector.h>
#include <libm/pow.h>
/* Dependency: "powf" from "math" */
#ifndef ____localdep_powf_defined
#define ____localdep_powf_defined 1
#if __has_builtin(__builtin_powf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_powf)
/* Return X to the Y power */
__EXTERNINLINE __DECL_SIMD_powf __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __localdep_powf)(float __x, float __y) { return __builtin_powf(__x, __y); }
#elif defined(__CRT_HAVE_powf)
/* Return X to the Y power */
__CREDIRECT(__DECL_SIMD_powf __ATTR_WUNUSED,float,__NOTHROW,__localdep_powf,(float __x, float __y),powf,(__x,__y))
#elif defined(__CRT_HAVE___powf)
/* Return X to the Y power */
__CREDIRECT(__DECL_SIMD_powf __ATTR_WUNUSED,float,__NOTHROW,__localdep_powf,(float __x, float __y),__powf,(__x,__y))
#else /* LIBC: powf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
#include <local/math/powf.h>
/* Return X to the Y power */
#define __localdep_powf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(powf))
#else /* CUSTOM: powf */
#undef ____localdep_powf_defined
#endif /* powf... */
#endif /* powf... */
#endif /* !____localdep_powf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(pow10f) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(pow10f))(float __x) {
#line 1420 "kos/src/libc/magic/math.c"
	return __localdep_powf(10.0f, __x);
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_powf || __CRT_HAVE___powf */
#endif /* !__local_pow10f_defined */
