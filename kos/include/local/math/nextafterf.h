/* HASH CRC-32:0x7a0b930b */
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
#ifndef __local_nextafterf_defined
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
#define __local_nextafterf_defined 1
#include <libm/nextafter.h>
__NAMESPACE_LOCAL_BEGIN
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__LOCAL_LIBC(nextafterf) __ATTR_CONST __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(nextafterf))(float __x,
                                                    float __y) {
#line 830 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (double)__ieee754_nextafterf((__IEEE754_FLOAT_TYPE__)__x, (__IEEE754_FLOAT_TYPE__)__y);
#else /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ */
	return (double)__ieee754_nextafter((__IEEE754_DOUBLE_TYPE__)__x, (__IEEE754_DOUBLE_TYPE__)__y);
#endif /* !__IEEE754_FLOAT_TYPE_IS_FLOAT__ */
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ */
#endif /* !__local_nextafterf_defined */
