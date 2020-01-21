/* HASH CRC-32:0xd7a71749 */
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
#ifndef __local_lrintl_defined
#if defined(__CRT_HAVE_lrint) || defined(__CRT_HAVE___lrint)
#define __local_lrintl_defined 1
/* Dependency: "lrint" */
#ifndef ____localdep_lrint_defined
#define ____localdep_lrint_defined 1
#if __has_builtin(__builtin_lrint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lrint)
/* Round X to nearest integral value according to current rounding direction */
__EXTERNINLINE __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL __localdep_lrint)(double __x) { return __builtin_lrint(__x); }
#elif defined(__CRT_HAVE_lrint)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,__localdep_lrint,(double __x),lrint,(__x))
#elif defined(__CRT_HAVE___lrint)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,__localdep_lrint,(double __x),__lrint,(__x))
#else /* LIBC: lrint */
#undef ____localdep_lrint_defined
#endif /* lrint... */
#endif /* !____localdep_lrint_defined */

__NAMESPACE_LOCAL_BEGIN
/* Round X to nearest integral value according to current rounding direction */
__LOCAL_LIBC(lrintl) __ATTR_WUNUSED long int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(lrintl))(long double __x) {
#line 640 "kos/src/libc/magic/math.c"
	return (long int)__localdep_lrint((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_lrint || __CRT_HAVE___lrint */
#endif /* !__local_lrintl_defined */
