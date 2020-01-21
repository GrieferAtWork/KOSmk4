/* HASH CRC-32:0xd724b84a */
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
#ifndef __local_remainderf_defined
#if defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE___remainder)
#define __local_remainderf_defined 1
/* Dependency: "remainder" */
#ifndef ____localdep_remainder_defined
#define ____localdep_remainder_defined 1
#if __has_builtin(__builtin_remainder) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainder)
/* Return the remainder of integer divison X / Y with infinite precision */
__EXTERNINLINE __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_remainder)(double __x, double __y) { return __builtin_remainder(__x, __y); }
#elif defined(__CRT_HAVE_remainder)
/* Return the remainder of integer divison X / Y with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_remainder,(double __x, double __y),remainder,(__x,__y))
#elif defined(__CRT_HAVE___remainder)
/* Return the remainder of integer divison X / Y with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_remainder,(double __x, double __y),__remainder,(__x,__y))
#else /* LIBC: remainder */
#undef ____localdep_remainder_defined
#endif /* remainder... */
#endif /* !____localdep_remainder_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return the remainder of integer divison X / Y with infinite precision */
__LOCAL_LIBC(remainderf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(remainderf))(float __x,
                                                    float __y) {
#line 690 "kos/src/libc/magic/math.c"
	return (float)__localdep_remainder((double)__x, (double)__y);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_remainder || __CRT_HAVE___remainder */
#endif /* !__local_remainderf_defined */
