/* HASH CRC-32:0x9de09bc */
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
#ifndef __local_exp10l_defined
#if defined(__CRT_HAVE_exp10) || defined(__CRT_HAVE___exp10)
#define __local_exp10l_defined 1
/* Dependency: "exp10" */
#ifndef ____localdep_exp10_defined
#define ____localdep_exp10_defined 1
#if __has_builtin(__builtin_exp10) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp10)
/* A function missing in all standards: compute exponent to base ten */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_exp10,(double __x),exp10,{ return __builtin_exp10(__x); })
#elif defined(__CRT_HAVE_exp10)
/* A function missing in all standards: compute exponent to base ten */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_exp10,(double __x),exp10,(__x))
#elif defined(__CRT_HAVE___exp10)
/* A function missing in all standards: compute exponent to base ten */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_exp10,(double __x),__exp10,(__x))
#else /* LIBC: exp10 */
#undef ____localdep_exp10_defined
#endif /* exp10... */
#endif /* !____localdep_exp10_defined */

__NAMESPACE_LOCAL_BEGIN
/* A function missing in all standards: compute exponent to base ten */
__LOCAL_LIBC(exp10l) __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(exp10l))(__LONGDOUBLE __x) {
#line 2098 "kos/src/libc/magic/math.c"
	return (__LONGDOUBLE)__localdep_exp10((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_exp10 || __CRT_HAVE___exp10 */
#endif /* !__local_exp10l_defined */
