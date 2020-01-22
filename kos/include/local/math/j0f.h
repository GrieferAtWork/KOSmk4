/* HASH CRC-32:0x44eafc43 */
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
#ifndef __local_j0f_defined
#if defined(__CRT_HAVE_j0) || defined(__CRT_HAVE___j0)
#define __local_j0f_defined 1
/* Dependency: "j0" */
#ifndef ____localdep_j0_defined
#define ____localdep_j0_defined 1
#if __has_builtin(__builtin_j0) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_j0)
__EXTERNINLINE __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_j0)(double __x) { return __builtin_j0(__x); }
#elif defined(__CRT_HAVE_j0)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_j0,(double __x),j0,(__x))
#elif defined(__CRT_HAVE___j0)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_j0,(double __x),__j0,(__x))
#else /* LIBC: j0 */
#undef ____localdep_j0_defined
#endif /* j0... */
#endif /* !____localdep_j0_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(j0f) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(j0f))(float __x) {
#line 2124 "kos/src/libc/magic/math.c"
	return (float)__localdep_j0((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_j0 || __CRT_HAVE___j0 */
#endif /* !__local_j0f_defined */
