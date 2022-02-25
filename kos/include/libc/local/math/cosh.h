/* HASH CRC-32:0xec890750 */
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
#ifndef __local_cosh_defined
#define __local_cosh_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libm/finite.h>
#include <libm/cosh.h>
#include <libm/matherr.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(cosh) __ATTR_WUNUSED double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(cosh))(double __x) {
	double __result = __LIBM_MATHFUN(cosh, __x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
		!__LIBM_MATHFUNI(finite, __result) && __LIBM_MATHFUNI(finite, __x))
		__result = __kernel_standard(__x, __x, __result, __LIBM_KMATHERR_COSH);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cosh_defined
#define __local___localdep_cosh_defined
#define __localdep_cosh __LIBC_LOCAL_NAME(cosh)
#endif /* !__local___localdep_cosh_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_cosh_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_cosh_defined */
