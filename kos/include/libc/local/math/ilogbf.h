/* HASH CRC-32:0x24385358 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_ilogbf_defined
#define __local_ilogbf_defined 1
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: ilogb from math */
#ifndef __local___localdep_ilogb_defined
#define __local___localdep_ilogb_defined 1
#if __has_builtin(__builtin_ilogb) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ilogb)
/* Return the binary exponent of `x', which must be nonzero */
__CEIREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogb,(double __x),ilogb,{ return __builtin_ilogb(__x); })
#elif defined(__CRT_HAVE_ilogb)
/* Return the binary exponent of `x', which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogb,(double __x),ilogb,(__x))
#elif defined(__CRT_HAVE___ilogb)
/* Return the binary exponent of `x', which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogb,(double __x),__ilogb,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/ilogb.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the binary exponent of `x', which must be nonzero */
#define __localdep_ilogb __LIBC_LOCAL_NAME(ilogb)
#else /* ... */
#undef __local___localdep_ilogb_defined
#endif /* !... */
#endif /* !__local___localdep_ilogb_defined */
__NAMESPACE_LOCAL_END
#include <libm/ilogb.h>
#include <libm/matherr.h>
#include <bits/crt/mathdef.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the binary exponent of `x', which must be nonzero */
__LOCAL_LIBC(ilogbf) __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(ilogbf))(float __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)


	int __result;
	__result = __LIBM_MATHFUNIF(ilogb, __x);
	if (__result == __FP_ILOGB0 || __result == __FP_ILOGBNAN || __result == __INT_MAX__)
		__kernel_standard_f(__x, __x, __x, __LIBM_KMATHERRF_ILOGB);
	return __result;
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ */
	return __localdep_ilogb((double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ilogbf_defined
#define __local___localdep_ilogbf_defined 1
#define __localdep_ilogbf __LIBC_LOCAL_NAME(ilogbf)
#endif /* !__local___localdep_ilogbf_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __CRT_HAVE_ilogb || __CRT_HAVE___ilogb || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
#undef __local_ilogbf_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__CRT_HAVE_ilogb && !__CRT_HAVE___ilogb && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
#endif /* !__local_ilogbf_defined */
