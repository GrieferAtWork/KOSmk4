/* HASH CRC-32:0x9f4ae36a */
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
#ifndef __local_floorl_defined
#define __local_floorl_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>

#include <libm/floor.h>
/* Dependency: "floor" from "math" */
#ifndef ____localdep_floor_defined
#define ____localdep_floor_defined 1
#if __has_builtin(__builtin_floor) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_floor)
/* Largest integer not greater than X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_floor,(double __x),floor,{ return __builtin_floor(__x); })
#elif defined(__CRT_HAVE_floor)
/* Largest integer not greater than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_floor,(double __x),floor,(__x))
#elif defined(__CRT_HAVE___floor)
/* Largest integer not greater than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_floor,(double __x),__floor,(__x))
#else /* LIBC: floor */
#include <local/math/floor.h>
/* Largest integer not greater than X */
#define __localdep_floor (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(floor))
#endif /* floor... */
#endif /* !____localdep_floor_defined */

__NAMESPACE_LOCAL_BEGIN
/* Largest integer not greater than X */
__LOCAL_LIBC(floorl) __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(floorl))(__LONGDOUBLE __x) {
#line 736 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUNL
	#ifdef __LIBM_MATHFUNL
	return __LIBM_MATHFUNL(floor, __x);
#else /* __LIBM_MATHFUN */
	__LONGDOUBLE __result;
	__result = (__LONGDOUBLE)(__INTMAX_TYPE__)__x; /* Round towards 0 */
	if (__result > __x)
		__result -= 1.0L;
	return __result;
#endif /* !__LIBM_MATHFUN */
#else /* __LIBM_MATHFUNL */
	return (__LONGDOUBLE)__localdep_floor((double)__x);
#endif /* !__LIBM_MATHFUNL */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_floorl_defined */
