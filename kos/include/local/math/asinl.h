/* HASH CRC-32:0xf955bc7f */
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
#ifndef __local_asinl_defined
#if defined(__CRT_HAVE_asin) || defined(__CRT_HAVE___asin)
#define __local_asinl_defined 1
/* Dependency: "asin" */
#ifndef ____localdep_asin_defined
#define ____localdep_asin_defined 1
#if __has_builtin(__builtin_asin) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asin)
/* Arc sine of X */
__EXTERNINLINE __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_asin)(double __x) { return __builtin_asin(__x); }
#elif defined(__CRT_HAVE_asin)
/* Arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_asin,(double __x),asin,(__x))
#elif defined(__CRT_HAVE___asin)
/* Arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_asin,(double __x),__asin,(__x))
#else /* LIBC: asin */
#undef ____localdep_asin_defined
#endif /* asin... */
#endif /* !____localdep_asin_defined */

__NAMESPACE_LOCAL_BEGIN
/* Arc sine of X */
__LOCAL_LIBC(asinl) __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(asinl))(__LONGDOUBLE __x) {
#line 224 "kos/src/libc/magic/math.c"
	return (__LONGDOUBLE)__localdep_asin((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_asin || __CRT_HAVE___asin */
#endif /* !__local_asinl_defined */
