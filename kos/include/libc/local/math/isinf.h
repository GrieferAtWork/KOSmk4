/* HASH CRC-32:0xb746ae49 */
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
#ifndef __local_isinf_defined
#define __local_isinf_defined
#include <__crt.h>
#include <ieee754.h>
#include <bits/math-constants.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)
#include <libm/isinf.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(isinf) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(isinf))(double __x) {
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(isinf, __x);
#elif defined(__INFINITY)
	return __x == __INFINITY;
#else /* ... */
	return __x == __HUGE_VAL;
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_isinf_defined
#define __local___localdep_isinf_defined
#define __localdep_isinf __LIBC_LOCAL_NAME(isinf)
#endif /* !__local___localdep_isinf_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __INFINITY || __HUGE_VAL */
#undef __local_isinf_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && !__INFINITY && !__HUGE_VAL */
#endif /* !__local_isinf_defined */
