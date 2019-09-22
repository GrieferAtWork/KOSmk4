/* HASH CRC-32:0x81fa32d6 */
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
#ifndef __local_tanhl_defined
#if ((__has_builtin(__builtin_tanh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanh)) || defined(__CRT_HAVE_tanh) || defined(__CRT_HAVE___tanh))
#define __local_tanhl_defined 1
/* Dependency: "tanh" */
#ifndef ____localdep_tanh_defined
#define ____localdep_tanh_defined 1
#if __has_builtin(__builtin_tanh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanh)
/* Hyperbolic tangent of X */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_tanh)(double __x) { return __builtin_tanh(__x); }
#elif defined(__CRT_HAVE_tanh)
/* Hyperbolic tangent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_tanh,(double __x),tanh,(__x))
#elif defined(__CRT_HAVE___tanh)
/* Hyperbolic tangent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_tanh,(double __x),__tanh,(__x))
#else /* LIBC: tanh */
#undef ____localdep_tanh_defined
#endif /* tanh... */
#endif /* !____localdep_tanh_defined */

__NAMESPACE_LOCAL_BEGIN
/* Hyperbolic tangent of X */
__LOCAL_LIBC(tanhl) __ATTR_WUNUSED long double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(tanhl))(long double __x) {
#line 170 "kos/src/libc/magic/math.c"
	return (long double)__localdep_tanh((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* ((__has_builtin(__builtin_tanh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanh)) || defined(__CRT_HAVE_tanh) || defined(__CRT_HAVE___tanh)) */
#endif /* !__local_tanhl_defined */
