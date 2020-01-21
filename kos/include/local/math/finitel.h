/* HASH CRC-32:0x143a6fb0 */
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
#ifndef __local_finitel_defined
#define __local_finitel_defined 1
#include <libm/finite.h>
/* Dependency: "finite" from "math" */
#ifndef ____localdep_finite_defined
#define ____localdep_finite_defined 1
#if __has_builtin(__builtin_finite) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_finite)
/* Return nonzero if VALUE is finite and not NaN */
__EXTERNINLINE __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_finite)(double __x) { return __builtin_finite(__x); }
#elif defined(__CRT_HAVE_finite)
/* Return nonzero if VALUE is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_finite,(double __x),finite,(__x))
#elif defined(__CRT_HAVE___finite)
/* Return nonzero if VALUE is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_finite,(double __x),__finite,(__x))
#elif defined(__CRT_HAVE__finite)
/* Return nonzero if VALUE is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_finite,(double __x),_finite,(__x))
#else /* LIBC: finite */
#include <local/math/finite.h>
/* Return nonzero if VALUE is finite and not NaN */
#define __localdep_finite (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(finite))
#endif /* finite... */
#endif /* !____localdep_finite_defined */

/* Dependency: "isinfl" from "math" */
#ifndef ____localdep_isinfl_defined
#define ____localdep_isinfl_defined 1
#if __has_builtin(__builtin_isinfl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinfl)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__EXTERNINLINE __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isinfl)(long double __x) { return __builtin_isinfl(__x); }
#elif defined(__CRT_HAVE_isinfl)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinfl,(long double __x),isinfl,(__x))
#elif defined(__CRT_HAVE___isinfl)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinfl,(long double __x),__isinfl,(__x))
#elif defined(__CRT_HAVE___isinf) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinfl,(long double __x),__isinf,(__x))
#elif defined(__CRT_HAVE_isinf) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinfl,(long double __x),isinf,(__x))
#else /* LIBC: isinfl */
#include <local/math/isinfl.h>
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
#define __localdep_isinfl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isinfl))
#endif /* isinfl... */
#endif /* !____localdep_isinfl_defined */

/* Dependency: "isnanl" from "math" */
#ifndef ____localdep_isnanl_defined
#define ____localdep_isnanl_defined 1
#if __has_builtin(__builtin_isnanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnanl)
/* Return nonzero if VALUE is not a number */
__EXTERNINLINE __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isnanl)(long double __x) { return __builtin_isnanl(__x); }
#elif defined(__CRT_HAVE_isnanl)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanl,(long double __x),isnanl,(__x))
#elif defined(__CRT_HAVE___isnanl)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanl,(long double __x),__isnanl,(__x))
#elif defined(__CRT_HAVE___isnan) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanl,(long double __x),__isnan,(__x))
#elif defined(__CRT_HAVE__isnan) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanl,(long double __x),_isnan,(__x))
#elif defined(__CRT_HAVE_isnan) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanl,(long double __x),isnan,(__x))
#else /* LIBC: isnanl */
#include <local/math/isnanl.h>
/* Return nonzero if VALUE is not a number */
#define __localdep_isnanl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isnanl))
#endif /* isnanl... */
#endif /* !____localdep_isnanl_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return nonzero if VALUE is finite and not NaN */
__LOCAL_LIBC(finitel) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(finitel))(long double __x) {
#line 1235 "kos/src/libc/magic/math.c"
#ifdef __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__
	return __ieee754_finitef((__IEEE754_FLOAT_TYPE__)__x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
	return __ieee754_finite((__IEEE754_DOUBLE_TYPE__)__x);
#elif 1
	return __localdep_finite((double)__x);
#else /* ... */
	return !__localdep_isinfl(__x) && !__localdep_isnanl(__x);
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_finitel_defined */
