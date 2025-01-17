/* HASH CRC-32:0x8fb0d50a */
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
#ifndef __local_ldexp_defined
#define __local_ldexp_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/errno.h>
#include <libm/finite.h>
#include <libm/ldexp.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ldexp) __ATTR_WUNUSED double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(ldexp))(double __x, int __exponent) {
	double __result;
	__result = __LIBM_MATHFUN2I(ldexp, __x, __exponent);
#ifdef __ERANGE
	if __unlikely(!__LIBM_MATHFUNI(finite, __result) || __result == 0.0)
		(void)__libc_seterrno(__ERANGE);
#endif /* __ERANGE */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ldexp_defined
#define __local___localdep_ldexp_defined
#define __localdep_ldexp __LIBC_LOCAL_NAME(ldexp)
#endif /* !__local___localdep_ldexp_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_ldexp_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_ldexp_defined */
