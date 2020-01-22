/* HASH CRC-32:0x97dc94b7 */
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
#ifndef __local_atanhl_defined
#if defined(__CRT_HAVE_atanh) || defined(__CRT_HAVE___atanh)
#define __local_atanhl_defined 1
/* Dependency: "atanh" */
#ifndef ____localdep_atanh_defined
#define ____localdep_atanh_defined 1
#if __has_builtin(__builtin_atanh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanh)
/* Hyperbolic arc tangent of X */
__EXTERNINLINE __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_atanh)(double __x) { return __builtin_atanh(__x); }
#elif defined(__CRT_HAVE_atanh)
/* Hyperbolic arc tangent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_atanh,(double __x),atanh,(__x))
#elif defined(__CRT_HAVE___atanh)
/* Hyperbolic arc tangent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_atanh,(double __x),__atanh,(__x))
#else /* LIBC: atanh */
#undef ____localdep_atanh_defined
#endif /* atanh... */
#endif /* !____localdep_atanh_defined */

__NAMESPACE_LOCAL_BEGIN
/* Hyperbolic arc tangent of X */
__LOCAL_LIBC(atanhl) __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(atanhl))(__LONGDOUBLE __x) {
#line 344 "kos/src/libc/magic/math.c"
	return (__LONGDOUBLE)__localdep_atanh((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_atanh || __CRT_HAVE___atanh */
#endif /* !__local_atanhl_defined */
