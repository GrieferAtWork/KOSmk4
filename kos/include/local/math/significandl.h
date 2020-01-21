/* HASH CRC-32:0xdd7efb0b */
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
#ifndef __local_significandl_defined
#if defined(__CRT_HAVE_significand) || defined(__CRT_HAVE___significand)
#define __local_significandl_defined 1
/* Dependency: "significand" */
#ifndef ____localdep_significand_defined
#define ____localdep_significand_defined 1
#if __has_builtin(__builtin_significand) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_significand)
/* Return the fractional part of X after dividing out `ilogb (X)' */
__EXTERNINLINE __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_significand)(double __x) { return __builtin_significand(__x); }
#elif defined(__CRT_HAVE_significand)
/* Return the fractional part of X after dividing out `ilogb (X)' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_significand,(double __x),significand,(__x))
#elif defined(__CRT_HAVE___significand)
/* Return the fractional part of X after dividing out `ilogb (X)' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_significand,(double __x),__significand,(__x))
#else /* LIBC: significand */
#undef ____localdep_significand_defined
#endif /* significand... */
#endif /* !____localdep_significand_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return the fractional part of X after dividing out `ilogb (X)' */
__LOCAL_LIBC(significandl) __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(significandl))(__LONGDOUBLE __x) {
#line 1415 "kos/src/libc/magic/math.c"
	return (__LONGDOUBLE)__localdep_significand((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_significand || __CRT_HAVE___significand */
#endif /* !__local_significandl_defined */
