/* HASH CRC-32:0xc187cdd */
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
#ifndef __local_scalblnf_defined
#if ((__has_builtin(__builtin_scalbln) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbln)) || defined(__CRT_HAVE_scalbln) || defined(__CRT_HAVE___scalbln))
#define __local_scalblnf_defined 1
/* Dependency: "scalbln" */
#ifndef ____localdep_scalbln_defined
#define ____localdep_scalbln_defined 1
#if __has_builtin(__builtin_scalbln) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbln)
/* Return X times (2 to the Nth power) */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_scalbln)(double __x, long int __n) { return __builtin_scalbln(__x, __n); }
#elif defined(__CRT_HAVE_scalbln)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_scalbln,(double __x, long int __n),scalbln,(__x,__n))
#elif defined(__CRT_HAVE___scalbln)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_scalbln,(double __x, long int __n),__scalbln,(__x,__n))
#else /* LIBC: scalbln */
#undef ____localdep_scalbln_defined
#endif /* scalbln... */
#endif /* !____localdep_scalbln_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return X times (2 to the Nth power) */
__LOCAL_LIBC(scalblnf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(scalblnf))(float __x,
                                                  long int __n) {
#line 563 "kos/src/libc/magic/math.c"
	return (float)__localdep_scalbln((double)__x, __n);
}
__NAMESPACE_LOCAL_END
#endif /* ((__has_builtin(__builtin_scalbln) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbln)) || defined(__CRT_HAVE_scalbln) || defined(__CRT_HAVE___scalbln)) */
#endif /* !__local_scalblnf_defined */
