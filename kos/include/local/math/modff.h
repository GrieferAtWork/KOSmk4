/* HASH CRC-32:0x68e2dd69 */
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
#ifndef __local_modff_defined
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
#define __local_modff_defined 1
#include <libm/modf.h>
__NAMESPACE_LOCAL_BEGIN
/* Break VALUE into integral and fractional parts */
__LOCAL_LIBC(modff) __ATTR_NONNULL((2)) float
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(modff))(float __x,
                                                   float *__iptr) {
#line 412 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (float)__ieee754_modff((__IEEE754_FLOAT_TYPE__)__x, (__IEEE754_FLOAT_TYPE__ *)__iptr);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
	return (float)__ieee754_modf((__IEEE754_DOUBLE_TYPE__)__x, (__IEEE754_DOUBLE_TYPE__ *)__iptr);
#else /* ... */
	return (float)__ieee854_modfl((__IEEE854_LONG_DOUBLE_TYPE__)__x, (__IEEE854_LONG_DOUBLE_TYPE__ *)__iptr);
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
#endif /* !__local_modff_defined */
