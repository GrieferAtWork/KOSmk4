/* HASH CRC-32:0x4217444d */
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
#ifndef __local_copysignf_defined
#define __local_copysignf_defined 1
#include <libm/copysign.h>
/* Dependency: "copysign" from "math" */
#ifndef ____localdep_copysign_defined
#define ____localdep_copysign_defined 1
#if __has_builtin(__builtin_copysign) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysign)
/* Return X with its signed changed to Y's */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_copysign,(double __num, double __sign),copysign,{ return __builtin_copysign(__num, __sign); })
#elif defined(__CRT_HAVE_copysign)
/* Return X with its signed changed to Y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_copysign,(double __num, double __sign),copysign,(__num,__sign))
#elif defined(__CRT_HAVE___copysign)
/* Return X with its signed changed to Y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_copysign,(double __num, double __sign),__copysign,(__num,__sign))
#elif defined(__CRT_HAVE__copysign)
/* Return X with its signed changed to Y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_copysign,(double __num, double __sign),_copysign,(__num,__sign))
#else /* LIBC: copysign */
#include <local/math/copysign.h>
/* Return X with its signed changed to Y's */
#define __localdep_copysign (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(copysign))
#endif /* copysign... */
#endif /* !____localdep_copysign_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return X with its signed changed to Y's */
__LOCAL_LIBC(copysignf) __ATTR_CONST __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(copysignf))(float __num,
                                                   float __sign) {
#line 738 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUN2F
	#ifdef __LIBM_MATHFUN2F
	return __LIBM_MATHFUN2F(copysign, __num, __sign);
#else /* __LIBM_MATHFUN2 */
	if ((__num < 0.0f) != (__sign < 0.0f))
		__num = -__num;
	return __num;
#endif /* !__LIBM_MATHFUN2 */
#else /* __LIBM_MATHFUN2F */
	return (float)__localdep_copysign((double)__num, (double)__sign);
#endif /* !__LIBM_MATHFUN2F */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_copysignf_defined */
