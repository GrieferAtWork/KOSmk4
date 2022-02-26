/* HASH CRC-32:0x4ff2dcbd */
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
#ifndef __local_fmaxf_defined
#define __local_fmaxf_defined
#include <__crt.h>
#include <ieee754.h>
#include <libm/fcomp.h>
#include <libm/isnan.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fmaxf) __ATTR_CONST __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(fmaxf))(float __x, float __y) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
	if (__LIBM_MATHFUNI2F(isgreaterequal, __x, __y))
		return __x;
	if (__LIBM_MATHFUNIF(isnan, __y))
		return __x;
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	if (__x >= __y)
		return __x;
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return __y;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fmaxf_defined
#define __local___localdep_fmaxf_defined
#define __localdep_fmaxf __LIBC_LOCAL_NAME(fmaxf)
#endif /* !__local___localdep_fmaxf_defined */
#endif /* !__local_fmaxf_defined */
