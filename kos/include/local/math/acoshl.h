/* HASH CRC-32:0x3cdf04c */
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
#ifndef __local_acoshl_defined
#if defined(__CRT_HAVE_acosh) || defined(__CRT_HAVE___acosh)
#define __local_acoshl_defined 1
/* Dependency: "acosh" */
#ifndef ____localdep_acosh_defined
#define ____localdep_acosh_defined 1
#if __has_builtin(__builtin_acosh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acosh)
/* Hyperbolic arc cosine of X */
__EXTERNINLINE __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_acosh)(double __x) { return __builtin_acosh(__x); }
#elif defined(__CRT_HAVE_acosh)
/* Hyperbolic arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_acosh,(double __x),acosh,(__x))
#elif defined(__CRT_HAVE___acosh)
/* Hyperbolic arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_acosh,(double __x),__acosh,(__x))
#else /* LIBC: acosh */
#undef ____localdep_acosh_defined
#endif /* acosh... */
#endif /* !____localdep_acosh_defined */

__NAMESPACE_LOCAL_BEGIN
/* Hyperbolic arc cosine of X */
__LOCAL_LIBC(acoshl) __ATTR_WUNUSED long double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(acoshl))(long double __x) {
#line 192 "kos/src/libc/magic/math.c"
	return (long double)__localdep_acosh((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_acosh || __CRT_HAVE___acosh */
#endif /* !__local_acoshl_defined */
