/* HASH CRC-32:0x80b12f3f */
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
#ifndef __local_remainder_defined
#define __local_remainder_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libm/matherr.h>
#include <libm/isnan.h>
#include <libm/isinf.h>
#include <libm/remainder.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(remainder) __ATTR_WUNUSED double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(remainder))(double __x, double __p) {
	if (((__p == 0.0 && !__LIBM_MATHFUNI(isnan, __x)) ||
	     (__LIBM_MATHFUNI(isinf, __x) && !__LIBM_MATHFUNI(isnan, __p))) &&
	    __LIBM_LIB_VERSION != __LIBM_IEEE)
		return __kernel_standard(__x, __p, __p, __LIBM_KMATHERR_REMAINDER); /* remainder domain */
	return __LIBM_MATHFUN2(remainder, __x, __p);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_remainder_defined
#define __local___localdep_remainder_defined
#define __localdep_remainder __LIBC_LOCAL_NAME(remainder)
#endif /* !__local___localdep_remainder_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_remainder_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_remainder_defined */
