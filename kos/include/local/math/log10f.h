/* HASH CRC-32:0xe7f5a16d */
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
#ifndef __local_log10f_defined
#if defined(__CRT_HAVE_log10) || defined(__CRT_HAVE___log10)
#define __local_log10f_defined 1
/* Dependency: "log10" */
#ifndef ____localdep_log10_defined
#define ____localdep_log10_defined 1
#if __has_builtin(__builtin_log10) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log10)
/* Base-ten logarithm of X */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_log10)(double __x) { return __builtin_log10(__x); }
#elif defined(__CRT_HAVE_log10)
/* Base-ten logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_log10,(double __x),log10,(__x))
#elif defined(__CRT_HAVE___log10)
/* Base-ten logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_log10,(double __x),__log10,(__x))
#else /* LIBC: log10 */
#undef ____localdep_log10_defined
#endif /* log10... */
#endif /* !____localdep_log10_defined */

__NAMESPACE_LOCAL_BEGIN
/* Base-ten logarithm of X */
__LOCAL_LIBC(log10f) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(log10f))(float __x) {
#line 234 "kos/src/libc/magic/math.c"
	return (float)__localdep_log10((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_log10) || defined(__CRT_HAVE___log10) */
#endif /* !__local_log10f_defined */
