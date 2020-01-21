/* HASH CRC-32:0x2fca6cf5 */
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
#ifndef __local_ynf_defined
#if defined(__CRT_HAVE_yn) || defined(__CRT_HAVE___yn)
#define __local_ynf_defined 1
/* Dependency: "yn" */
#ifndef ____localdep_yn_defined
#define ____localdep_yn_defined 1
#if __has_builtin(__builtin_yn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_yn)
__EXTERNINLINE __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_yn)(int __n, double __x) { return __builtin_yn(__n, __x); }
#elif defined(__CRT_HAVE_yn)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_yn,(int __n, double __x),yn,(__n,__x))
#elif defined(__CRT_HAVE___yn)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_yn,(int __n, double __x),__yn,(__n,__x))
#else /* LIBC: yn */
#undef ____localdep_yn_defined
#endif /* yn... */
#endif /* !____localdep_yn_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ynf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(ynf))(int __n,
                                             float __x) {
#line 1502 "kos/src/libc/magic/math.c"
	return (float)__localdep_yn(__n, (double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_yn || __CRT_HAVE___yn */
#endif /* !__local_ynf_defined */
