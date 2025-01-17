/* HASH CRC-32:0x4289f358 */
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
#ifndef __local_ilogbl_defined
#define __local_ilogbl_defined
#include <__crt.h>
#include <ieee754.h>
#include <hybrid/typecore.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_ilogb) || (defined(__CRT_HAVE_llogb) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__CRT_HAVE___ilogb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ilogb_defined
#define __local___localdep_ilogb_defined
#if __has_builtin(__builtin_ilogb) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ilogb)
__CEIREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogb,(double __x),ilogb,{ return __builtin_ilogb(__x); })
#elif defined(__CRT_HAVE_ilogb)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogb,(double __x),ilogb,(__x))
#elif defined(__CRT_HAVE_llogb) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogb,(double __x),llogb,(__x))
#elif defined(__CRT_HAVE___ilogb)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogb,(double __x),__ilogb,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/ilogb.h>
__NAMESPACE_LOCAL_BEGIN
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
__LOCAL_LIBC(ilogbl) __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(ilogbl))(__LONGDOUBLE __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)


	int __result;
	__result = __LIBM_MATHFUNIL(ilogb, __x);
	if (__result == __FP_ILOGB0 || __result == __FP_ILOGBNAN || __result == __INT_MAX__)
		__kernel_standard_l(__x, __x, __x, __LIBM_KMATHERRL_ILOGB);
	return __result;
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ */
	return (__NAMESPACE_LOCAL_SYM __localdep_ilogb)((double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ilogbl_defined
#define __local___localdep_ilogbl_defined
#define __localdep_ilogbl __LIBC_LOCAL_NAME(ilogbl)
#endif /* !__local___localdep_ilogbl_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_ilogb || (__CRT_HAVE_llogb && __SIZEOF_INT__ == __SIZEOF_LONG__) || __CRT_HAVE___ilogb || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
#undef __local_ilogbl_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__CRT_HAVE_ilogb && (!__CRT_HAVE_llogb || __SIZEOF_INT__ != __SIZEOF_LONG__) && !__CRT_HAVE___ilogb && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
#endif /* !__local_ilogbl_defined */
