/* HASH CRC-32:0x83b5b707 */
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
#ifndef __local_finitef_defined
#define __local_finitef_defined 1
#include <libm/finite.h>
/* Dependency: "isinff" from "math" */
#ifndef ____localdep_isinff_defined
#define ____localdep_isinff_defined 1
#if __has_builtin(__builtin_isinff) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinff)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinff,(float __x),isinff,{ return __builtin_isinff(__x); })
#elif defined(__CRT_HAVE_isinff)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinff,(float __x),isinff,(__x))
#elif defined(__CRT_HAVE___isinff)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinff,(float __x),__isinff,(__x))
#else /* LIBC: isinff */
#include <local/math/isinff.h>
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
#define __localdep_isinff (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isinff))
#endif /* isinff... */
#endif /* !____localdep_isinff_defined */

/* Dependency: "isnanf" from "math" */
#ifndef ____localdep_isnanf_defined
#define ____localdep_isnanf_defined 1
#if __has_builtin(__builtin_isnanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnanf)
/* Return nonzero if VALUE is not a number */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanf,(float __x),isnanf,{ return __builtin_isnanf(__x); })
#elif defined(__CRT_HAVE_isnanf)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanf,(float __x),isnanf,(__x))
#elif defined(__CRT_HAVE___isnanf)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanf,(float __x),__isnanf,(__x))
#else /* LIBC: isnanf */
#include <local/math/isnanf.h>
/* Return nonzero if VALUE is not a number */
#define __localdep_isnanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isnanf))
#endif /* isnanf... */
#endif /* !____localdep_isnanf_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return nonzero if VALUE is finite and not NaN */
__LOCAL_LIBC(finitef) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(finitef))(float __x) {
#line 2109 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return __ieee754_finitef((__IEEE754_FLOAT_TYPE__)__x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
	return __ieee754_finite((__IEEE754_DOUBLE_TYPE__)__x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
	return __ieee854_finitel((__IEEE854_LONG_DOUBLE_TYPE__)__x);
#else /* ... */
	return !__localdep_isinff(__x) && !__localdep_isnanf(__x);
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_finitef_defined */
