/* HASH CRC-32:0x1a3a790e */
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
#ifndef __local_expm1_defined
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#define __local_expm1_defined 1
#include <__crt.h>
#include <libm/matherr.h>

#include <libm/signbit.h>

#include <libm/finite.h>

#include <libm/expm1.h>
__NAMESPACE_LOCAL_BEGIN
/* Return exp(X) - 1 */
__LOCAL_LIBC(expm1) __ATTR_WUNUSED double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(expm1))(double __x) {
#line 450 "kos/src/libc/magic/math.c"
	double __result;
	__result = __LIBM_MATHFUN(expm1, __x);
	if ((!__LIBM_MATHFUN(finite, __result) || __result == -1.0) &&
	    __LIBM_MATHFUN(finite , __x) && __LIBM_LIB_VERSION != __LIBM_IEEE) {
		return __kernel_standard(__x, __x, __result,
		                         __LIBM_MATHFUN(signbit, __x)
		                         ? __LIBM_KMATHERRL_EXPM1_UNDERFLOW
		                         : __LIBM_KMATHERRL_EXPM1_OVERFLOW);
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_expm1_defined */
