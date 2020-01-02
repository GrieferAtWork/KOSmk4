/* HASH CRC-32:0xd0d604f7 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_sqrtl_defined
#if defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt)
#define __local_sqrtl_defined 1
/* Dependency: "sqrt" */
#ifndef ____localdep_sqrt_defined
#define ____localdep_sqrt_defined 1
#if __has_builtin(__builtin_sqrt) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sqrt)
/* Return the square root of X */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_sqrt)(double __x) { return __builtin_sqrt(__x); }
#elif defined(__CRT_HAVE_sqrt)
/* Return the square root of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_sqrt,(double __x),sqrt,(__x))
#elif defined(__CRT_HAVE___sqrt)
/* Return the square root of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_sqrt,(double __x),__sqrt,(__x))
#else /* LIBC: sqrt */
#undef ____localdep_sqrt_defined
#endif /* sqrt... */
#endif /* !____localdep_sqrt_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return the square root of X */
__LOCAL_LIBC(sqrtl) __ATTR_WUNUSED long double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(sqrtl))(long double __x) {
#line 317 "kos/src/libc/magic/math.c"
	return (long double)__localdep_sqrt((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_sqrt || __CRT_HAVE___sqrt */
#endif /* !__local_sqrtl_defined */
