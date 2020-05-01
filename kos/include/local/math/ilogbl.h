/* HASH CRC-32:0x50974bc2 */
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
#ifndef __local_ilogbl_defined
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb)
#define __local_ilogbl_defined 1
#include <__crt.h>
#include <libm/ilogb.h>

#include <libm/matherr.h>
/* Dependency: "ilogb" from "math" */
#ifndef ____localdep_ilogb_defined
#define ____localdep_ilogb_defined 1
#if __has_builtin(__builtin_ilogb) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ilogb)
/* Return the binary exponent of X, which must be nonzero */
__CEIREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogb,(double __x),ilogb,{ return __builtin_ilogb(__x); })
#elif defined(__CRT_HAVE_ilogb)
/* Return the binary exponent of X, which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogb,(double __x),ilogb,(__x))
#elif defined(__CRT_HAVE___ilogb)
/* Return the binary exponent of X, which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogb,(double __x),__ilogb,(__x))
#else /* LIBC: ilogb */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
#include <local/math/ilogb.h>
/* Return the binary exponent of X, which must be nonzero */
#define __localdep_ilogb (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ilogb))
#else /* CUSTOM: ilogb */
#undef ____localdep_ilogb_defined
#endif /* ilogb... */
#endif /* ilogb... */
#endif /* !____localdep_ilogb_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return the binary exponent of X, which must be nonzero */
__LOCAL_LIBC(ilogbl) __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(ilogbl))(__LONGDOUBLE __x) {
#line 913 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUNL
	int __result;
	__result = __LIBM_MATHFUNIL(ilogb, __x);
	if (__result == __LIBM_FP_ILOGB0 || __result == __LIBM_FP_ILOGBNAN || __result == __INT_MAX__)
		__kernel_standard_l(__x, __x, __x, __LIBM_KMATHERRF_ILOGB);
	return __result;
#else /* __LIBM_MATHFUNL */
	return __localdep_ilogb((double)__x);
#endif /* !__LIBM_MATHFUNL */
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __CRT_HAVE_ilogb || __CRT_HAVE___ilogb */
#endif /* !__local_ilogbl_defined */
