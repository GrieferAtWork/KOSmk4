/* HASH CRC-32:0x7aa201d9 */
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
#ifndef __local_ilogb_defined
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
#define __local_ilogb_defined 1
#include <libm/ilogb.h>

#include <libm/matherr.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the binary exponent of X, which must be nonzero */
__LOCAL_LIBC(ilogb) __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(ilogb))(double __x) {
#line 1348 "kos/src/libc/magic/math.c"
	int __result;
	__result = __LIBM_MATHFUNI(ilogb, __x);
	if (__result == __LIBM_FP_ILOGB0 || __result == __LIBM_FP_ILOGBNAN || __result == __INT_MAX__)
		__kernel_standard(__x, __x, __x, __LIBM_KMATHERRF_ILOGB);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
#endif /* !__local_ilogb_defined */
