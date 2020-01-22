/* HASH CRC-32:0x7b977c48 */
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
#ifndef __local_roundl_defined
#define __local_roundl_defined 1
#include <hybrid/typecore.h>

#include <libm/round.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(roundl) __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(roundl))(__LONGDOUBLE __x) {
#line 1639 "kos/src/libc/magic/math.c"
#ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return (__LONGDOUBLE)__ieee854_roundl((__IEEE854_LONG_DOUBLE_TYPE__)__x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_round((__IEEE754_DOUBLE_TYPE__)__x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_roundf((__IEEE754_FLOAT_TYPE__)__x);
#else /* ... */
	__LONGDOUBLE __result;
	__result = (__LONGDOUBLE)(__INTMAX_TYPE__)__x;
	if (__x < 0.0L) {
		/* result >= x */
		if ((__result - __x) >= 0.5L)
			__result -= 1.0L;
	} else {
		/* result <= x */
		if ((__x - __result) >= 0.5L)
			__result += 1.0L;
	}
	return __result;
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_roundl_defined */
