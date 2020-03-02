/* HASH CRC-32:0x6b4ce3ae */
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
#ifndef __local_acosl_defined
#if defined(__CRT_HAVE_acos) || defined(__CRT_HAVE___acos)
#define __local_acosl_defined 1
/* Dependency: "acos" */
#ifndef ____localdep_acos_defined
#define ____localdep_acos_defined 1
#if __has_builtin(__builtin_acos) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acos)
/* Arc cosine of X */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_acos,(double __x),acos,{ return __builtin_acos(__x); })
#elif defined(__CRT_HAVE_acos)
/* Arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_acos,(double __x),acos,(__x))
#elif defined(__CRT_HAVE___acos)
/* Arc cosine of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_acos,(double __x),__acos,(__x))
#else /* LIBC: acos */
#undef ____localdep_acos_defined
#endif /* acos... */
#endif /* !____localdep_acos_defined */

__NAMESPACE_LOCAL_BEGIN
/* Arc cosine of X */
__LOCAL_LIBC(acosl) __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(acosl))(__LONGDOUBLE __x) {
#line 209 "kos/src/libc/magic/math.c"
	return (__LONGDOUBLE)__localdep_acos((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_acos || __CRT_HAVE___acos */
#endif /* !__local_acosl_defined */
