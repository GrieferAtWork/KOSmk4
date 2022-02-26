/* HASH CRC-32:0x41d2b342 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__ldpcomp_defined
#define __local__ldpcomp_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE__dpcomp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__dpcomp_defined
#define __local___localdep__dpcomp_defined
#ifdef __CRT_HAVE__dpcomp
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__dpcomp,(double __x, double __y),_dpcomp,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/_dpcomp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__dpcomp __LIBC_LOCAL_NAME(_dpcomp)
#else /* ... */
#undef __local___localdep__dpcomp_defined
#endif /* !... */
#endif /* !__local___localdep__dpcomp_defined */
__NAMESPACE_LOCAL_END
#include <libm/fcomp.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_ldpcomp) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_ldpcomp))(__LONGDOUBLE __x, __LONGDOUBLE __y) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	int __result = 0;
	if (!__LIBM_MATHFUN2L(isunordered, __x, __y)) {
		if (__LIBM_MATHFUN2L(isgreater, __x, __y))
			__result |= 4;
		if (__LIBM_MATHFUN2L(isgreaterequal, __x, __y))
			__result |= 2 | 4;
		if (__LIBM_MATHFUN2L(isless, __x, __y))
			__result |= 1;
		if (__LIBM_MATHFUN2L(islessequal, __x, __y))
			__result |= 1 | 2;
		if (__LIBM_MATHFUN2L(islessgreater, __x, __y))
			__result |= 1 | 4;
	}
	return __result;
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__NAMESPACE_LOCAL_SYM __localdep__dpcomp)((double)__x, (double)__y);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__ldpcomp_defined
#define __local___localdep__ldpcomp_defined
#define __localdep__ldpcomp __LIBC_LOCAL_NAME(_ldpcomp)
#endif /* !__local___localdep__ldpcomp_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE__dpcomp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local__ldpcomp_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__CRT_HAVE__dpcomp && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local__ldpcomp_defined */
