/* HASH CRC-32:0x191f4f1 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_lgamma_r_defined
#define __local_lgamma_r_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libm/lgamma.h>
#include <libm/matherr.h>
#include <libm/finite.h>
#include <libm/floor.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(lgamma_r) __ATTR_WUNUSED __ATTR_OUT(2) double
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(lgamma_r))(double __x, int *__signgamp) {
	double __result = __LIBM_MATHFUN2I(lgamma, __x, __signgamp);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    !__LIBM_MATHFUNI(finite, __result) && __LIBM_MATHFUNI(finite, __x)) {
		return __kernel_standard(__x, __x, __result,
		                         __LIBM_MATHFUN(floor, __x) == __x &&
		                         __x <= 0.0 ? __LIBM_KMATHERR_LGAMMA_MINUS      /* lgamma pole */
		                                  : __LIBM_KMATHERR_LGAMMA_OVERFLOW); /* lgamma overflow */
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_lgamma_r_defined
#define __local___localdep_lgamma_r_defined
#define __localdep_lgamma_r __LIBC_LOCAL_NAME(lgamma_r)
#endif /* !__local___localdep_lgamma_r_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_lgamma_r_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_lgamma_r_defined */
