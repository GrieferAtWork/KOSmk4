/* HASH CRC-32:0xb7679ce9 */
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
#ifndef __local_ceill_defined
#define __local_ceill_defined 1
#include <hybrid/typecore.h>

#include <libm/ceil.h>
/* Dependency: "ceil" from "math" */
#ifndef ____localdep_ceil_defined
#define ____localdep_ceil_defined 1
#if __has_builtin(__builtin_ceil) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ceil)
/* Smallest integral value not less than X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_ceil,(double __x),ceil,{ return __builtin_ceil(__x); })
#elif defined(__CRT_HAVE_ceil)
/* Smallest integral value not less than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_ceil,(double __x),ceil,(__x))
#elif defined(__CRT_HAVE___ceil)
/* Smallest integral value not less than X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_ceil,(double __x),__ceil,(__x))
#else /* LIBC: ceil */
#include <local/math/ceil.h>
/* Smallest integral value not less than X */
#define __localdep_ceil (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ceil))
#endif /* ceil... */
#endif /* !____localdep_ceil_defined */

__NAMESPACE_LOCAL_BEGIN
/* Smallest integral value not less than X */
__LOCAL_LIBC(ceill) __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(ceill))(__LONGDOUBLE __x) {
#line 699 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUNL
	#ifdef __LIBM_MATHFUNL
	return __LIBM_MATHFUNL(ceil, __x);
#else /* __LIBM_MATHFUN */
	__LONGDOUBLE __result;
	__result = (__LONGDOUBLE)(__INTMAX_TYPE__)__x; /* Round towards 0 */
	if (__result < __x)
		__result += 1.0L;
	return __result;
#endif /* !__LIBM_MATHFUN */
#else /* __LIBM_MATHFUNL */
	return (__LONGDOUBLE)__localdep_ceil((double)__x);
#endif /* !__LIBM_MATHFUNL */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_ceill_defined */
