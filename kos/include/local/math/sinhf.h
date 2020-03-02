/* HASH CRC-32:0x6d1f6705 */
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
#ifndef __local_sinhf_defined
#if defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh)
#define __local_sinhf_defined 1
/* Dependency: "sinh" */
#ifndef ____localdep_sinh_defined
#define ____localdep_sinh_defined 1
#if __has_builtin(__builtin_sinh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinh)
/* Hyperbolic sine of X */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_sinh,(double __x),sinh,{ return __builtin_sinh(__x); })
#elif defined(__CRT_HAVE_sinh)
/* Hyperbolic sine of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_sinh,(double __x),sinh,(__x))
#elif defined(__CRT_HAVE___sinh)
/* Hyperbolic sine of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_sinh,(double __x),__sinh,(__x))
#else /* LIBC: sinh */
#undef ____localdep_sinh_defined
#endif /* sinh... */
#endif /* !____localdep_sinh_defined */

__NAMESPACE_LOCAL_BEGIN
/* Hyperbolic sine of X */
__LOCAL_LIBC(sinhf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(sinhf))(float __x) {
#line 303 "kos/src/libc/magic/math.c"
	return (float)__localdep_sinh((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_sinh || __CRT_HAVE___sinh */
#endif /* !__local_sinhf_defined */
