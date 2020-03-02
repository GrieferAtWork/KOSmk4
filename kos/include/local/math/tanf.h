/* HASH CRC-32:0xd0aa4916 */
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
#ifndef __local_tanf_defined
#if defined(__CRT_HAVE_tan) || defined(__CRT_HAVE___tan)
#define __local_tanf_defined 1
/* Dependency: "tan" */
#ifndef ____localdep_tan_defined
#define ____localdep_tan_defined 1
#if __has_builtin(__builtin_tan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tan)
/* Tangent of X */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_tan,(double __x),tan,{ return __builtin_tan(__x); })
#elif defined(__CRT_HAVE_tan)
/* Tangent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_tan,(double __x),tan,(__x))
#elif defined(__CRT_HAVE___tan)
/* Tangent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_tan,(double __x),__tan,(__x))
#else /* LIBC: tan */
#undef ____localdep_tan_defined
#endif /* tan... */
#endif /* !____localdep_tan_defined */

__NAMESPACE_LOCAL_BEGIN
/* Tangent of X */
__LOCAL_LIBC(tanf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(tanf))(float __x) {
#line 217 "kos/src/libc/magic/math.c"
	return (float)__localdep_tan((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_tan || __CRT_HAVE___tan */
#endif /* !__local_tanf_defined */
