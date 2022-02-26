/* HASH CRC-32:0xa4c9a6cc */
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
#ifndef __local__dpcomp_defined
#define __local__dpcomp_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libm/fcomp.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_dpcomp) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_dpcomp))(double __x, double __y) {
	int __result = 0;
	if (!__LIBM_MATHFUN2(isunordered, __x, __y)) {
		if (__LIBM_MATHFUN2(isgreater, __x, __y))
			__result |= 4;
		if (__LIBM_MATHFUN2(isgreaterequal, __x, __y))
			__result |= 2 | 4;
		if (__LIBM_MATHFUN2(isless, __x, __y))
			__result |= 1;
		if (__LIBM_MATHFUN2(islessequal, __x, __y))
			__result |= 1 | 2;
		if (__LIBM_MATHFUN2(islessgreater, __x, __y))
			__result |= 1 | 4;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__dpcomp_defined
#define __local___localdep__dpcomp_defined
#define __localdep__dpcomp __LIBC_LOCAL_NAME(_dpcomp)
#endif /* !__local___localdep__dpcomp_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local__dpcomp_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local__dpcomp_defined */
