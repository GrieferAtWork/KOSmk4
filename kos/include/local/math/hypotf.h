/* HASH CRC-32:0xc13fc3a7 */
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
#ifndef __local_hypotf_defined
#if defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot)
#define __local_hypotf_defined 1
/* Dependency: "hypot" */
#ifndef ____localdep_hypot_defined
#define ____localdep_hypot_defined 1
#if __has_builtin(__builtin_hypot) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_hypot)
/* Return `sqrt(X*X + Y*Y)' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_hypot,(double __x, double __y),hypot,{ return __builtin_hypot(__x, __y); })
#elif defined(__CRT_HAVE_hypot)
/* Return `sqrt(X*X + Y*Y)' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_hypot,(double __x, double __y),hypot,(__x,__y))
#elif defined(__CRT_HAVE___hypot)
/* Return `sqrt(X*X + Y*Y)' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_hypot,(double __x, double __y),__hypot,(__x,__y))
#else /* LIBC: hypot */
#undef ____localdep_hypot_defined
#endif /* hypot... */
#endif /* !____localdep_hypot_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return `sqrt(X*X + Y*Y)' */
__LOCAL_LIBC(hypotf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(hypotf))(float __x,
                                                float __y) {
#line 592 "kos/src/libc/magic/math.c"
	return (float)__localdep_hypot((double)__x, (double)__y);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_hypot || __CRT_HAVE___hypot */
#endif /* !__local_hypotf_defined */
