/* HASH CRC-32:0x57970fd7 */
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
#ifndef __local_lrintf_defined
#define __local_lrintf_defined 1
#include <hybrid/typecore.h>

#include <libm/lrint.h>
/* Dependency: "rintf" from "math" */
#ifndef ____localdep_rintf_defined
#define ____localdep_rintf_defined 1
#if __has_builtin(__builtin_rintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintf)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_rintf,(float __x),rintf,{ return __builtin_rintf(__x); })
#elif defined(__CRT_HAVE_rintf)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_rintf,(float __x),rintf,(__x))
#elif defined(__CRT_HAVE___rintf)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_rintf,(float __x),__rintf,(__x))
#else /* LIBC: rintf */
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE___rint)
#include <local/math/rintf.h>
/* Return the integer nearest X in the direction of the prevailing rounding mode */
#define __localdep_rintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintf))
#else /* CUSTOM: rintf */
#undef ____localdep_rintf_defined
#endif /* rintf... */
#endif /* rintf... */
#endif /* !____localdep_rintf_defined */

__NAMESPACE_LOCAL_BEGIN
/* Round X to nearest integral value according to current rounding direction */
__LOCAL_LIBC(lrintf) __ATTR_CONST __ATTR_WUNUSED long int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(lrintf))(float __x) {
#line 1813 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return __ieee754_lrintf((__IEEE754_FLOAT_TYPE__)__x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
	return __ieee754_lrint((__IEEE754_DOUBLE_TYPE__)__x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
	return __ieee754_lrintl((__IEEE854_LONG_DOUBLE_TYPE__)__x);
#else /* ... */
	return (long int)__localdep_rintf(__x);
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_lrintf_defined */
