/* HASH 0xb95c8b41 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef __local_asinhl_defined
#if ((__has_builtin(__builtin_asinh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinh)) || defined(__CRT_HAVE_asinh) || defined(__CRT_HAVE___asinh))
#define __local_asinhl_defined 1
/* Dependency: "asinh" */
#ifndef ____localdep_asinh_defined
#define ____localdep_asinh_defined 1
#if __has_builtin(__builtin_asinh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinh)
/* Hyperbolic arc sine of X */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_asinh)(double __x) { return __builtin_asinh(__x); }
#elif defined(__CRT_HAVE_asinh)
/* Hyperbolic arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_asinh,(double __x),asinh,(__x))
#elif defined(__CRT_HAVE___asinh)
/* Hyperbolic arc sine of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_asinh,(double __x),__asinh,(__x))
#else /* LIBC: asinh */
#undef ____localdep_asinh_defined
#endif /* asinh... */
#endif /* !____localdep_asinh_defined */

__NAMESPACE_LOCAL_BEGIN
/* Hyperbolic arc sine of X */
__LOCAL_LIBC(asinhl) __ATTR_WUNUSED long double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(asinhl))(long double __x) {
#line 192 "kos/src/libc/magic/math.c"
	return (long double)__localdep_asinh((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* ((__has_builtin(__builtin_asinh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinh)) || defined(__CRT_HAVE_asinh) || defined(__CRT_HAVE___asinh)) */
#endif /* !__local_asinhl_defined */
